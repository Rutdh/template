#include "data.h"
using namespace std;

void HQInfo::start()
{
    m_update_thread = thread(&HQInfo::update, this);
}

void HQInfo::stop()
{
    m_is_stop = true;
    if (m_update_thread.joinable())
    {
        m_update_thread.join();
    }
}

void HQInfo::update()
{
    /*
    */
    default_random_engine generator(time(nullptr));
    /*
     */
    uniform_real_distribution<double> distribution(100.0, 1000.0);

    while (m_is_stop != true)
    {
        unique_lock<mutex> lock(m_mtx);
        auto now = chrono::system_clock::now();
        time_t timestamp = chrono::system_clock::to_time_t(now);
        double price = distribution(generator);
        ST_MARKET_DATA tmp_data = {price, timestamp};
        m_vec.push_back(tmp_data);

        auto it = lower_bound(m_vecMax.begin(), m_vecMax.end(), tmp_data, [](const ST_MARKET_DATA &a, const ST_MARKET_DATA &b)
                              { return a.lastPrice < b.lastPrice; });
        if (it != m_vecMax.end())
        {
            m_vecMax.resize(it - m_vecMax.begin() - 1);
        }
        m_vecMax.push_back(tmp_data);

        auto it1 = upper_bound(m_vecMin.begin(), m_vecMin.end(), tmp_data, [](const ST_MARKET_DATA &a, const ST_MARKET_DATA &b)
                               { return a.lastPrice > b.lastPrice; });
        if (it != m_vecMin.end())
        {
            m_vecMin.resize(it - m_vecMin.begin() - 1);
        }
        m_vecMin.push_back(tmp_data);

        lock.unlock();

        this_thread::sleep_for(chrono::seconds(1));
    }

    return;
}

void HQInfo::print2txt()
{
    ofstream osf("hq.txt");
    for (const auto &v : m_vec)
    {
        osf << v.lastPrice << "   " << v.time << endl;
    }

    osf << "vecMax" << endl;
    for (const auto &v : m_vecMax)
    {
        osf << v.lastPrice << "   " << v.time << endl;
    }

    osf << "vecMin" << endl;
    for (const auto &v : m_vecMin)
    {
        osf << v.lastPrice << "   " << v.time << endl;
    }
}

/// @brief 二分查找, 左闭右开模式查找, 找到返回要找元素的下标, 否则-1
/// @param vec 被查找的数组
/// @param find_value 要找的元素
/// @return -1:失败; 其他成功且是下标
size_t HQInfo::binary_search(const std::vector<ST_MARKET_DATA> &vec, const ST_MARKET_DATA &find_value)
{
    size_t begin = 0, end = vec.size(), mid = (begin + end) / 2;

    while (begin != end)
    {
        
    }

    return 0;
}
