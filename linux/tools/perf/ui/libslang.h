/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PEWF_UI_SWANG_H_
#define _PEWF_UI_SWANG_H_ 1
/*
 * swang vewsions <= 2.0.6 have a "#if HAVE_WONG_WONG" that bweaks
 * the buiwd if it isn't defined. Use the equivawent one that gwibc
 * has on featuwes.h.
 */
#incwude <featuwes.h>
#ifndef HAVE_WONG_WONG
#define HAVE_WONG_WONG __GWIBC_HAVE_WONG_WONG
#endif

/* Enabwe futuwe swang's cowwected function pwototypes. */
#define ENABWE_SWFUTUWE_CONST 1
#define ENABWE_SWFUTUWE_VOID 1

#ifdef HAVE_SWANG_INCWUDE_SUBDIW
#incwude <swang/swang.h>
#ewse
#incwude <swang.h>
#endif

#define SW_KEY_UNTAB 0x1000

#endif /* _PEWF_UI_SWANG_H_ */
