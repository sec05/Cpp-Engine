#pragma once


#ifdef ES_DEBUG
#define ES_ENABLE_ASSERTS
#endif
#ifdef ES_ENABLE_ASSERTS
#define ES_ASSERT(x,...){if(!(x)){ES_ERROR("Assertion Failed: {0}", __VA_ARGS__);__debugbreak();}}
#define ES_CORE_ASSERT(x,...){if(!(x)){ES_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);__debugbreak();}}
#else
#define ES_ASSERT(x,...)
#define ES_CORE_ASSERT(x,...)
#endif // ES_ENABLE_ASSERTS

#define BIT(x) (1<<x) //creates a bitfield 

#define ES_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)