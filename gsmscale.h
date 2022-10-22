#ifndef GSMSCALE_H
#define GSMSCALE_H

#include <QMainWindow>
#include <vector>
#include <qtextedit.h>
#include "serial_comms.h"
#include <mutex>
#include <thread>


QT_BEGIN_NAMESPACE
namespace Ui { class gsmscale; }
QT_END_NAMESPACE

class gsmscale : public QMainWindow
{
        Q_OBJECT

    public:

        /**
         * @brief gsmscale
         * @param parent
         *
         * CONSTRUCTOR
         */
        gsmscale(QWidget *parent = nullptr);

        /**
         * DESTRUCTOR
         * */
        ~gsmscale();

    private:

        /**
         * @brief The PAGE_SIZE class
         *
         * Paper size attibutes.
         */
        struct PAGE_SIZE {
            QString Name;   ///< Reference/Display Name eg. ISO A4
            int     L;      ///< Length (mm)
            int     W;      ///< Width (mm)
        };

        /**
         * @brief m_pageSizeLUT
         *
         * A list of various predefined page sizes plus a special
         * "Custom" page size that when selected will enable the
         * spin boxes to allow manual user input.
         * */
        std::vector<PAGE_SIZE> m_pageSizeLUT = {
            { "A4",         297,        210 },
            { "A3",         420,        297 },
            { "SRA3",       450,        320 },
            { "Custom",     0,          0   }
        };

        //A USER INTERFACE OBJECT
        Ui::gsmscale *ui;

        /**
         * @brief m_timerId
         *
         * The id of the event timer used for periodically updating
         * the user interface.
         */
        int m_timerId;

        /**
         * @brief m_deviceMeasurement
         *
         * The measurement reported by the scale/balance.
         */
        std::string m_deviceMeasurement;

        /**
         * @brief m_deviceMeasurement_MUTEX
         *
         * Prevent the thread t1 and the main thread from accessing
         * m_deviceMeasurement at the same time.
         */
        std::mutex m_deviceMeasurement_MUTEX;

        /**
         * @brief m_t1Done
         *
         * Terminate the loop in the thread "t1" so that we can perform an
         * orderly shutdown.
         */
        bool m_t1Done;

        /**
         * @brief t1
         *
         * The thread used to monitor the serial port.
         */
        std::thread *t1;

        /**
         * @brief t1_handle
         *
         * The thread handle, this is used to kill the thread that reads the
         * serial data if it is locked for a given period of time
         */
        pthread_t t1_handle;

        /**
         * @brief t1_serialReadTime
         *
         * The last time that an attempt to perform a read(); on the serial port
         * was initiated.
         *
         * Used so we can determine if read(); has been blocking for too long.
         */
        time_t t1_serialReadTime;

        /**
         * @brief t_Monitor
         *
         * A second thread used to monitor thread "t1" so that it can be killed
         * if it blocks for too long.
         */
        std::thread *t_Monitor;

        /**
         * @brief monitor_measuring_device
         *
         * Called by thread "t1" to monitor the serial device
         */
        void monitor_measuring_device();

        /**
         * @brief monitor_threads
         *
         * Called by thread "t_monitor" this may uncerimoneousl kill thread
         * "t1" and recreate it if for some reason "t1" has been blocking for
         * too long.
         */
        void monitor_threads();


    protected:
        /**
         * @brief timerEvent
         * @param event
         *
         * Periodically update the user interface.
         */
        void timerEvent(QTimerEvent *event);

    private slots:
        /**
         * @brief update_page_size
         * @param index
         *
         * Update the GUI when a page size is seleced from the combo box.
         */
        void update_page_size(int index);
};
#endif // GSMSCALE_H
