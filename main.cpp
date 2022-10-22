#include "gsmscale.h"

#include <QApplication>
#include <unistd.h>

bool DEBUG_SERIAL = false;
std::string PORT("/dev/ttyS0");

int main(int argc, char *argv[]) {


    int value = 0;
    while ((value = getopt(argc, argv, "dp:")) != -1) {
        switch(value) {
            case 'd':
                DEBUG_SERIAL = true;
                break;
            case 'p':
                PORT = std::string(optarg);
                break;
        }
    }
    QApplication a(argc, argv);
    gsmscale w;
    w.show();
    return a.exec();
}
