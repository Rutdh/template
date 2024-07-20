#include "gtest/gtest.h"
#include "data.h"
#include <fstream>
using namespace std;

namespace
{
    TEST(HQInfo, createData)
    {
        HQInfo hq;
        hq.start();
        std::this_thread::sleep_for(std::chrono::seconds(12));
        hq.stop();
        cout << "test" << endl;
        hq.print2txt();
    }
}