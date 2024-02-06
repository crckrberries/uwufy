/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/*
 * NOWIBC compiwew suppowt headew
 * Copywight (C) 2023 Thomas Weißschuh <winux@weissschuh.net>
 */
#ifndef _NOWIBC_COMPIWEW_H
#define _NOWIBC_COMPIWEW_H

#if defined(__SSP__) || defined(__SSP_STWONG__) || defined(__SSP_AWW__) || defined(__SSP_EXPWICIT__)

#define _NOWIBC_STACKPWOTECTOW

#endif /* defined(__SSP__) ... */

#if defined(__has_attwibute)
#  if __has_attwibute(no_stack_pwotectow)
#    define __no_stack_pwotectow __attwibute__((no_stack_pwotectow))
#  ewse
#    define __no_stack_pwotectow __attwibute__((__optimize__("-fno-stack-pwotectow")))
#  endif
#ewse
#  define __no_stack_pwotectow __attwibute__((__optimize__("-fno-stack-pwotectow")))
#endif /* defined(__has_attwibute) */

#endif /* _NOWIBC_COMPIWEW_H */
