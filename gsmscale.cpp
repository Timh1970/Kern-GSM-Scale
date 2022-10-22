#include "gsmscale.h"
#include "ui_gsmscale.h"
#include "serial_comms.h"
#include <iostream>
#include <ctime>

/**
 * @brief gsmscale::gsmscale
 * @param parent
 *
 * Set up slots and initially create the threads that read and monitor
 * the serial port.  Also set default values for the user interface.
 */
gsmscale::gsmscale(QWidget *parent)
    :
      QMainWindow(parent),
      ui(new Ui::gsmscale) {

    ui->setupUi(this);

    for(PAGE_SIZE &it : m_pageSizeLUT) {
        ui->CB_PageSize->addItem(it.Name);
    }

    this->statusBar()->setSizeGripEnabled(false);

    ui->SPIN_Length->setDisabled(true);
    ui->SPIN_Width->setDisabled(true);

    ui->SPIN_Length->setValue(m_pageSizeLUT[0].L);
    ui->SPIN_Width->setValue(m_pageSizeLUT[0].W);
    ui->TXT_CUR_Weight->insertPlainText("Error");

    connect(ui->CB_PageSize, SIGNAL(currentIndexChanged(int)), this, SLOT(update_page_size(int)));

    m_t1Done = false;
    t1 = new std::thread([this] { this->monitor_measuring_device(); } );
    t1_handle = t1->native_handle();
    t1->detach();


    t_Monitor = new std::thread([this] { this->monitor_threads(); } );
    t_Monitor->detach();

    /**
     * @code startTimer() @endcode
     * is used to trigger the timerEvent() method that is used to update the
     * user interface.  It served no other purpose; the threads have thier own
     * timers.
     * */
    m_timerId = startTimer(300);

}


/**
 * @brief gsmscale::~gsmscale
 */
gsmscale::~gsmscale() {
    killTimer(m_timerId);
    m_t1Done = true;
    if(t1->joinable())
        t1->join();
    delete t1;
    if(t_Monitor->joinable())
        t_Monitor->join();
    delete t_Monitor;
    delete ui;
}

/**
 * @brief gsmscale::monitor_measuring_device
 *
 * CALLED BY THREAD t1
 *
 * Create an instance of the serial_comms class, check that we can
 * connect to the scale and if we can then try and read data from
 * the scale.
 *
 * @note read_serial() may block, a second thread is created to
 * kill off this thread (t1) if it blocks for too long.
 */
void gsmscale::monitor_measuring_device() {

    serial_comms s;
    while(!s.test_comms()) {
        t1_serialReadTime = time(nullptr);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        m_deviceMeasurement_MUTEX.lock();
        m_deviceMeasurement = "Error";
        m_deviceMeasurement_MUTEX.unlock();
    }

    while(!m_t1Done) {
        t1_serialReadTime = time(nullptr);
        m_deviceMeasurement_MUTEX.lock();
        m_deviceMeasurement = s.read_serial();
        m_deviceMeasurement_MUTEX.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

}


/**
 * @brief gsmscale::monitor_threads
 *
 * CALLED BY t_Monitor
 *
 * This is used to kill thread "t1" if the scale becomes disconnected
 * It will then attempt to recreated it to allow the applicatin to
 * continue if the scale is reconnected.
 */
void gsmscale::monitor_threads() {

    const int T1_TIMEOUT = 5;

    while (!m_t1Done) {
        if ((time(nullptr) - T1_TIMEOUT) > t1_serialReadTime ) {
            pthread_cancel(t1_handle);
            m_deviceMeasurement = "Timeout";
            m_deviceMeasurement_MUTEX.unlock();
            if(DEBUG_SERIAL) std::cout << "Thread killed due to being blocked by read()." << std::endl;
            t1 = new std::thread([this] { this->monitor_measuring_device(); } );
            t1_handle = t1->native_handle();  //USED SO WE CAN KILL THE THREAD.
            t1->detach();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

}



/**
 * @brief gsmscale::timerEvent
 * @param event
 *
 * Update the user interface.
 *
 * @attention The lock guard will block this method if the
 * m_deviceMeasurement_MUTEX is locked (see the monitor_measuring_device() method)
 */
void gsmscale::timerEvent(QTimerEvent *event) {

    event->accept();

    ui->TXT_CUR_Weight->clear();

    //WAIT FOR THE m_deviceMeasurement VALE TO BECOME STABLE
    std::lock_guard guard(m_deviceMeasurement_MUTEX);
    if(DEBUG_SERIAL) std::cout << __PRETTY_FUNCTION__ <<": Value received: " << m_deviceMeasurement << std::endl;
    ui->TXT_CUR_Weight->insertPlainText(QString::fromStdString(m_deviceMeasurement));

    double widthM, lengthM, weightG;

    widthM   = ui->SPIN_Width->value() / 1000;
    lengthM  = ui->SPIN_Length->value() / 1000;
    weightG  = ui->TXT_CUR_Weight->toPlainText().toInt();

    ui->LCD_GSM->display(round(weightG / (lengthM * widthM)));

}

/**
 * @brief gsmscale::update_page_size
 * @param index
 *
 * Update the user interface to reflect the selected page size based on the lookup
 * table m_pageSizeLUT.
 */
void gsmscale::update_page_size(int index) {

    ui->SPIN_Length->setValue(m_pageSizeLUT[index].L);
    ui->SPIN_Width->setValue(m_pageSizeLUT[index].W);

    if(m_pageSizeLUT[index].Name.compare("Custom") == 0) {
        ui->SPIN_Length->setDisabled(false);
        ui->SPIN_Width->setDisabled(false);
    } else {
        ui->SPIN_Length->setDisabled(true);
        ui->SPIN_Width->setDisabled(true);
    }
}


