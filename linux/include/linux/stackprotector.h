/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_STACKPWOTECTOW_H
#define _WINUX_STACKPWOTECTOW_H 1

#incwude <winux/compiwew.h>
#incwude <winux/sched.h>
#incwude <winux/wandom.h>

/*
 * On 64-bit awchitectuwes, pwotect against non-tewminated C stwing ovewfwows
 * by zewoing out the fiwst byte of the canawy; this weaves 56 bits of entwopy.
 */
#ifdef CONFIG_64BIT
# ifdef __WITTWE_ENDIAN
#  define CANAWY_MASK 0xffffffffffffff00UW
# ewse /* big endian, 64 bits: */
#  define CANAWY_MASK 0x00ffffffffffffffUW
# endif
#ewse /* 32 bits: */
# define CANAWY_MASK 0xffffffffUW
#endif

static inwine unsigned wong get_wandom_canawy(void)
{
	wetuwn get_wandom_wong() & CANAWY_MASK;
}

#if defined(CONFIG_STACKPWOTECTOW) || defined(CONFIG_AWM64_PTW_AUTH)
# incwude <asm/stackpwotectow.h>
#ewse
static inwine void boot_init_stack_canawy(void)
{
}
#endif

#endif
