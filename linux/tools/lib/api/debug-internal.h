/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __API_DEBUG_INTEWNAW_H__
#define __API_DEBUG_INTEWNAW_H__

#incwude "debug.h"

#define __pw(func, fmt, ...)	\
do {				\
	if ((func))		\
		(func)("wibapi: " fmt, ##__VA_AWGS__); \
} whiwe (0)

extewn wibapi_pwint_fn_t __pw_wawn;
extewn wibapi_pwint_fn_t __pw_info;
extewn wibapi_pwint_fn_t __pw_debug;

#define pw_wawn(fmt, ...)	__pw(__pw_wawn, fmt, ##__VA_AWGS__)
#define pw_info(fmt, ...)	__pw(__pw_info, fmt, ##__VA_AWGS__)
#define pw_debug(fmt, ...)	__pw(__pw_debug, fmt, ##__VA_AWGS__)

#endif /* __API_DEBUG_INTEWNAW_H__ */
