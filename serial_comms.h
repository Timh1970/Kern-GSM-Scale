#ifndef SERIAL_COMMS_H
#define SERIAL_COMMS_H
#include <string>
#include <termios.h> // Contains POSIX terminal control definitions

extern bool DEBUG_SERIAL;

/**
 * @brief PORT
 *
 * The port can be set by passing a command line argument using the
 * "-p" flag.
 *
 * eg. -p /dev/ttyS1
 */
extern std::string PORT;

class serial_comms
{

    private:
        /**
         * @brief serial_port
         * The id of the serial port (Fixed by the constructor)
         */
        const int serial_port;

        /**
         * @brief tty
         *
         * The configuration of the serial port
         */
        struct termios tty;


    public:
        /**
         * @brief serial_comms
         * CONSTRUCTOR
         */
        serial_comms();

        /**
         * @brief
         * DESTRUCTOR
         * */
        ~serial_comms();

        /**
         * @brief read_serial
         * @return The numeric weight in grams (g).
         * @note The string returned by the device will have some whitespace and could
         * potentially be appended with a "g" character. As we are only interrested
         * in the number we can simply use atoi to discard everything else and then
         * convert it back to a string.
         *
         * Request data from the serial port and attempt to read any response.
         *
         * @warning This may block indefinitely if the device doesn't return "VMIN" bytes.
         *
         * @note **The Scale must be in rECR mode (See Manual) for this method to function
         * correctly**
         */
        std::string read_serial();

        /**
         * @brief test_comms
         * @return true if we can read and write to the serial port.
         *
         * This tests the serial port to see if it can write to and
         * read from the scale.
         *
         * If successful it updates the value of VMIN so that read()
         * will obtain 18 bytes of data from the scle before returning.
         */
        bool test_comms();
};

#endif // SERIAL_COMMS_H
