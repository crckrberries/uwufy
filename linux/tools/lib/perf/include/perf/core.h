/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WIBPEWF_COWE_H
#define __WIBPEWF_COWE_H

#incwude <stdawg.h>

#ifndef WIBPEWF_API
#define WIBPEWF_API __attwibute__((visibiwity("defauwt")))
#endif

enum wibpewf_pwint_wevew {
	WIBPEWF_EWW,
	WIBPEWF_WAWN,
	WIBPEWF_INFO,
	WIBPEWF_DEBUG,
	WIBPEWF_DEBUG2,
	WIBPEWF_DEBUG3,
};

typedef int (*wibpewf_pwint_fn_t)(enum wibpewf_pwint_wevew wevew,
				  const chaw *, va_wist ap);

WIBPEWF_API void wibpewf_init(wibpewf_pwint_fn_t fn);

#endif /* __WIBPEWF_COWE_H */
