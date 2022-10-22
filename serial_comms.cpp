#include "serial_comms.h"
#include <cstring>
#include <cstdio>
#include <iostream>
#include <fcntl.h>      // Contains file controls like O_RDWR
#include <errno.h>      // Error integer and strerror() function
#include <unistd.h>     // write(), read(), close()
#include <algorithm>
#include <functional>
#include <thread>
#include <cstdlib>

using std::string;

/**
 * @brief serial_comms::serial_comms
 *
 * The constructor sets up the initail values of the serial port.
 */
serial_comms::serial_comms()
    :
      serial_port(open(PORT.c_str(), O_RDWR | O_NOCTTY | O_SYNC)) {

    if(DEBUG_SERIAL) printf("Serial port %i open.\n", serial_port);


    /**
     *  Read in existing settings so we have a meaningful set of defaults and change the following to
     *  our preferred setting:
     *  */
    if(tcgetattr(serial_port, &tty) != 0) {
        if(DEBUG_SERIAL) std::cout << "Error: " << errno << " from tcsetattr: " << strerror(errno) << std::endl;
    }

    tty.c_cflag &= ~PARENB;         /// - Clear parity bit, disabling parity (most common)
    tty.c_cflag &= ~CSTOPB;         /// - Clear stop field, only one stop bit used in communication (most common)
    tty.c_cflag &= ~CSIZE;          /// - Clear all bits that set the data size
    tty.c_cflag |= CS8;             /// - 8 bits per byte (most common)
    tty.c_cflag &= ~CRTSCTS;        /// - Disable RTS/CTS hardware flow control (most common)
    tty.c_cflag |= CREAD | CLOCAL;  /// - Turn on READ & ignore ctrl lines (CLOCAL = 1)

    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO;           /// - Disable echo
    tty.c_lflag &= ~ECHOE;          /// - Disable erasure
    //tty.c_lflag &= ~ECHONL;       /// - Disable new-line echo
    tty.c_lflag &= ~ISIG;           /// - Disable interpretation of INTR, QUIT and SUSP
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); /// - Turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); /// - Disable any special handling of received bytes
    tty.c_oflag &= ~OPOST;          /// - Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR;          /// - Prevent conversion of newline to carriage return/line feed
    // tty.c_oflag &= ~OXTABS;      /// - Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
    // tty.c_oflag &= ~ONOEOT;      /// - Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)

    tty.c_cc[VTIME] = 10;           /// - Time to wait for a charcter to enter the stream
    tty.c_cc[VMIN] = 0;             /// - Read a minimum of VMIN bytes from the stream

    cfsetispeed(&tty, B19200);      /// - Set read baud rate
    cfsetospeed(&tty, B19200);      /// - Set write baud rate

    /// Save tty settings, also checking for error
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        if(DEBUG_SERIAL) std::cout << "Error: " << errno << " from tcsetattr: " << strerror(errno) << std::endl;
    } else {
        if(DEBUG_SERIAL) std::cout << "Setting up port: Success (This does not guarantee connection)" << std::endl;
    }

}

/**
 * @brief serial_comms::test_comms
 *
 * If we can talk to the device properly and get a response then we can set the port into blocking mode
 * so that it waits for 18 bytes of data.
 **/
bool serial_comms::test_comms() {

    bool okay = false;

    /**
     * For the device to function correctly we need it in **rECR** (remote control) mode
     * (see device manual) we then issue a "w" to it in order to inform it that we wish
     * to obtain a measurement.
     *
     * @code write(serial_port, "w", sizeof("w")); @endcode
     *
     * @note This is specific to the Kern scale, if you modify this application to use an
     * alternative device then it is highly likley that it will use different control codes.
     * */
     write(serial_port, "w", sizeof("w"));

    /**
     * **read()** Attempts to read the response (if any)
     *
     * @param buf[32]
     * We read the entire response here as it is the easiest way to flush it from the stream
     * however we are only really interested in the first character as that will determine whether
     * the device has responded or not.
     * */

    char buf[32] {'\0'};
    read(serial_port, &buf, sizeof(buf));



    if(buf[0] == '\0') {
        if(DEBUG_SERIAL) std::cout << "ERROR: Testing Comms - Cannot read from device/device not ready" << std::endl;
    } else {
        tty.c_cc[VTIME] = 0;
        /**
         * @param VMIN
         * Once we are sure that we can communicate with the device we can update the serial port
         * settings to inform read() that we wish to receive 18 bytes of data (See the scale manual)
         *
         * @note  The scale manual declares that it only sends 16 bytes on error, but this is not
         * correct.  Even if it returns "Error" it still sends 18 bytes which is why this is okay
         * in this instance.
         *
         * @code tty.c_cc[VMIN] = 18; @endcode
         *
         * <b>If at some point you try to make this compatible with another device then this, along
         * with the control character may stop it from working</b>
         **/
        tty.c_cc[VMIN] = 18;
        tcsetattr(serial_port, TCSANOW, &tty);
        okay = true;
    }

    return(okay);

}

/**
 * @brief serial_comms::~serial_comms
 *
 * Just closes the serial port when we are done.
 */
serial_comms::~serial_comms() {
    close(serial_port);
}


string serial_comms::read_serial() {

    //READ BUFFER
    char read_buf[18];

    //ZERO OUT THE READ BUFFER
    memset(&read_buf, '\0', sizeof(read_buf));

    //REQUEST DATA
    if(write(serial_port, "w", sizeof("w")) == -1) {
        if(DEBUG_SERIAL) std::cout << "Error: Device probably not connected!" << std::endl;
        return("Error");
    }
    else
        if(DEBUG_SERIAL) std::cout << "Request for data made" << std::endl;

    int num_bytes =  read(serial_port, read_buf, sizeof(read_buf));

    if(DEBUG_SERIAL) std::cout << "Read " << num_bytes << " bytes. Received message: " << read_buf << std::endl;

    return(std::to_string(atoi(read_buf)));



}
