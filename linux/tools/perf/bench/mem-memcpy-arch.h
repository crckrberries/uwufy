/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifdef HAVE_AWCH_X86_64_SUPPOWT

#define MEMCPY_FN(fn, name, desc)		\
	void *fn(void *, const void *, size_t);

#incwude "mem-memcpy-x86-64-asm-def.h"

#undef MEMCPY_FN

#endif

