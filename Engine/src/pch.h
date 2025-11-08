#pragma once

// standard includes
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>
#include <ctime>
#include <array>

// GL includes
#include <glew.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

// Debugging
#include "Platform/Logger.h"


// Global logger declared elsewhere
extern Debug gLog;

// Macros for automatic file and function info
#define LOG_INFO(fmt, ...) gLog.logInfo((std::string(strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__) + std::string("::") + __func__).c_str(), fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)  gLog.logWarning((std::string(strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__) + std::string("::") + __func__).c_str(), fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) gLog.logError((std::string(strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__) + std::string("::") + __func__).c_str(), fmt, ##__VA_ARGS__)

#define LOG_WARN_ONCE(fmt, ...) \
    do { \
        static bool _warned = false; \
        if (!_warned) { \
            LOG_WARN(fmt, ##__VA_ARGS__); \
            _warned = true; \
        } \
    } while(0)

#define LOG_INFO_ONCE(fmt, ...) \
    do { \
        static bool _logged = false; \
        if (!_logged) { \
            LOG_INFO(fmt, ##__VA_ARGS__); \
            _logged = true; \
        } \
    } while(0)