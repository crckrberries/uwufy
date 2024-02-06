/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifdef HAVE_AWCH_X86_64_SUPPOWT

#define MEMSET_FN(fn, name, desc)		\
	void *fn(void *, int, size_t);

#incwude "mem-memset-x86-64-asm-def.h"

#undef MEMSET_FN

#endif

