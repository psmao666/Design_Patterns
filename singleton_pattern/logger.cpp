#include <iostream>
#include <vector>
/*
Task:
To create a logger system, supports insert, deletion, check log
*/

class Logger{
public:
    void addLog(const std::string& msg) {
        logs.push_back(msg);
    }
    void rmvLog() {
        logs.pop_back();
    }
    std::vector<std::string> fetchLastKLogs(int k) {
        k = std::min(k, static_cast<int>(logs.size()));
        std::vector<std::string> results{};
        while (k > 0) {
            -- k;
            results.push_back(logs[k]);
        }
        return results;
    }
private:
    std::vector<std::string> logs;
};

class LoggerSingleton{
public:
    static LoggerSingleton& getInstance() {
        static LoggerSingleton obj;
        return obj;
    }
    void addLog(const std::string& log) {
        logbook.addLog(log);
    }
    void rmvLog() {
        logbook.rmvLog();
    }
    std::vector<std::string> fetchLog(int k) {
        return logbook.fetchLastKLogs(k);
    }
private:
    LoggerSingleton() = default;
    Logger logbook;
};

int main() {
    // testing starts....
    LoggerSingleton& logger = LoggerSingleton::getInstance();
    logger.addLog("user A opened a file");
    logger.addLog("user B deleted a critical file");
    auto records = logger.fetchLog(3);
    for (const auto& log: records) {
        std::cout << log << std::endl;
    }
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~\n";
    LoggerSingleton& logger2 = LoggerSingleton::getInstance();
    logger2.rmvLog();
    records = logger.fetchLog(3);
    for (const auto& log: records) {
        std::cout << log << std::endl;
    }
    return 0;
}