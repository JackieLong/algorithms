#pragma once

#ifndef _MACRO_H_
#define _MACRO_H_

#ifdef __cplusplus

    #define USING_NS_ALGORITHM using namespace Algorithm

    #define NS_ALGORITHM_BEGIN namespace Algorithm {
    #define NS_ALGORITHM_END }

#else

    #define USING_NS_ALGORITHM
    #define NS_ALGORITHM_BEGIN
    #define NS_ALGORITHM_END

#endif

#define CompFunc std::function<bool(const T&,const T&)>


#endif