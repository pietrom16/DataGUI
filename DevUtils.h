/** DevUtils.h
 *
 *  Set of development utilities.
 */


#ifndef DEV_UTILS_H
#define DEV_UTILS_H

#ifdef DEV_UTILS

	#include <iostream>

	#define TRACE_(MSG) std::cerr << __FILE__ << ":" << __LINE__ << ": " << MSG << std::endl
	#define TRACE TRACE_("")

#else

	#define TRACE_(MSG)
	#define TRACE

#endif


#endif // DEV_UTILS_H
