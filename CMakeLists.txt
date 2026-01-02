cmake_minimum_required(VERSION 3.20) # Standard versions are usually 3.20+
project(multithreadedparser)

# Use C++20 for modern multithreading features (like std::jthread)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. List all your SOURCE files (.cpp)
# 2. You can also list HEADER files (.h) so they appear in CLion's project view
add_executable(multithreadedparser
        main.cpp
        src/ThreadPool.cpp
        include/ThreadPool.h
        include/SafeQueue.h
        include/LogRecord.h
        src/LogRecord.cpp
        src/LogReaderThread.cpp
        include/LogReaderThread.h
        src/LogParserThread.cpp
        include/LogParserThread.h
        src/LogAggregator.cpp
        include/LogAggregator.h
        src/writeParsedLogs.cpp
        include/writeParsedLogs.h
)

# 3. This is the "Magic" line:
# It tells the compiler: "When I say #include <ThreadPool.h>, look inside the /include folder"
target_include_directories(multithreadedparser PUBLIC include)

# 4. If you are using Linux, you often need to link the pthread library for multithreading
find_package(Threads REQUIRED)
target_link_libraries(multithreadedparser PUBLIC Threads::Threads)