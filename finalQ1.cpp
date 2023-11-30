#include <iostream>
#include <string>
#include <cstring>
using namespace std;

enum class ErrorLevel {SEVERE, ERROR, WARNING, INFO};
struct ErrorContext {
    ErrorLevel errlevel;
    const char* logmsg;
};
extern void SDAOSlogger(struct ErrorContext &logcontext);  

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }


    void log(ErrorLevel severity, const string& message) {
        const char* cstr = message.c_str();
        ErrorContext logContext{severity, strdup(cstr)};  
        logToOperatingSystem(logContext);
        free(const_cast<char*>(logContext.logmsg));
    }

private:
    Logger() {}

    void logToOperatingSystem(const ErrorContext& logContext) {
        cout<<"ErrorLevel: "<< static_cast<int>(logContext.errlevel)<<" Message: "<<logContext.logmsg<<endl;
    }
};

class SDALogger {
public:
    static void log(ErrorLevel severity, const string& message) {
        Logger::getInstance().log(severity, message);
    }

    static void Severe(const string& message) {
        log(ErrorLevel::SEVERE, message);
    }

    static void Error(const string& message) {
        log(ErrorLevel::ERROR, message);
    }

    static void Warning(const string& message) {
        log(ErrorLevel::WARNING, message);
    }

    static void Information(const string& message) {
        log(ErrorLevel::INFO, message);
    }
};

int main() {
    SDALogger::Severe("Severe error detected.");
    SDALogger::Error("Error detected.");
    SDALogger::Warning("Warning detected.");
    SDALogger::Information("Information found here.");
    return 0;
}
