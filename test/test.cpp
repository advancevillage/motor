#include <iostream>
#include <../spdlog/spdlog.h>

void SpdLogTest01();

int main(int argc, char* argv[]){
    SpdLogTest01();
    return 0;
}

void SpdLogTest01(){
    try
    {                                        
        auto daily_sink = std::make_shared<spdlog::sinks::daily_file_sink<std::mutex,spdlog::sinks::dateonly_daily_file_name_calculator>>("motor.log", 23, 59);
        // create asynchronous logger with queue size of 8192 
        // see https://github.com/gabime/spdlog/blob/master/include/spdlog/async_logger.h for ctor options       
        spdlog::async_logger logger("motor",  daily_sink, 8192); 
        logger.info("motor log module");
        spdlog::drop_all(); 
    }
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cout << "Log initialization failed: " << ex.what() << std::endl;
    }
}
