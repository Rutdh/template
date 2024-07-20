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
    SepNote 使用随机数生成器来生成随机数
    */
    default_random_engine generator(time(nullptr));
    /*
    SepNote https://www.apiref.com/cpp-zh/cpp/numeric/random/uniform_real_distribution.html 这里的实例化类型一定要是double, float, 或者long double之一, 否则是UB.
     */
    uniform_real_distribution<double> distribution(100.0, 1000.0);

    while (m_is_stop != true)
    {
        unique_lock<mutex> lock(m_mtx);
        auto now = chrono::system_clock::now();
        time_t timestamp = chrono::system_clock::to_time_t(now);
        /* SepNote 这里其实是一个重载的(),  接受一个默认的随机数生成器, 生成一个均匀分布的随机数, 区间由创建均匀分布时的参数给定, 依然是经典的左开右闭*/
        double price = distribution(generator);
        // SepNote 记录一个现象, 这里使用emplace_back会报错
        ST_MARKET_DATA tmp_data = {price, timestamp};
        m_vec.push_back(tmp_data);

        // SepNote lower_bound底层是基于二分查找的, 第三个参数是要查找的元素, 第四个参数是个二元谓词, 二元谓词的第一个参数接受迭代器区间内的每个迭代器, 所以要求能用迭代器在解引用后能隐式转换, 二元谓词的第二个参数要求能用第三个参数隐式转换. 二位谓词的作用是提供一个能在迭代器和查找元素之间比较先序关系(即< )的函数, 注意不包含等于
        auto it = lower_bound(m_vecMax.begin(), m_vecMax.end(), tmp_data, [](const ST_MARKET_DATA &a, const ST_MARKET_DATA &b)
                              { return a.lastPrice < b.lastPrice; });
        if (it != m_vecMax.end())
        {
            m_vecMax.resize(it - m_vecMax.begin());
        }
        m_vecMax.push_back(tmp_data);

        auto it1 = upper_bound(m_vecMin.begin(), m_vecMin.end(), tmp_data, [](const ST_MARKET_DATA &a, const ST_MARKET_DATA &b)
                               { return a.lastPrice > b.lastPrice; });
        if (it1 != m_vecMin.end())
        {
            m_vecMin.resize(it1 - m_vecMin.begin());
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
