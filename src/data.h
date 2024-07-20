#pragma once
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>
#include <mutex>
#include <random>
#include <ctime>

typedef struct st_market_data
{
    double lastPrice; // 最新价
    time_t time;      // 时间
} ST_MARKET_DATA;

// 模拟行情类, 定时更新ST_MARKET_DATA
class HQInfo
{
public:
    void start();
    void stop();

    void print2txt();
    size_t binary_search(const std::vector<ST_MARKET_DATA>& vec, const ST_MARKET_DATA& find_value);
private:
    void update();
private:
    std::vector<ST_MARKET_DATA> m_vec;
    std::thread m_update_thread;
    std::mutex m_mtx;
    bool m_is_stop {false};

    std::vector<ST_MARKET_DATA> m_vecMax;
    std::vector<ST_MARKET_DATA> m_vecMin;
};
