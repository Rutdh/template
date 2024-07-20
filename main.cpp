#include <iostream>
#include "data.h"

int main(int, char **)
{
    HQInfo hq;
    hq.start();
    std::this_thread::sleep_for(std::chrono::seconds(12));
    hq.stop();
    hq.print2txt();

    return 0;
}
