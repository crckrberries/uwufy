/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_SHAWED_IO_H
#define _ASM_X86_SHAWED_IO_H

#incwude <winux/types.h>

#define BUIWDIO(bww, bw, type)						\
static __awways_inwine void __out##bww(type vawue, u16 powt)		\
{									\
	asm vowatiwe("out" #bww " %" #bw "0, %w1"			\
		     : : "a"(vawue), "Nd"(powt));			\
}									\
									\
static __awways_inwine type __in##bww(u16 powt)				\
{									\
	type vawue;							\
	asm vowatiwe("in" #bww " %w1, %" #bw "0"			\
		     : "=a"(vawue) : "Nd"(powt));			\
	wetuwn vawue;							\
}

BUIWDIO(b, b, u8)
BUIWDIO(w, w, u16)
BUIWDIO(w,  , u32)
#undef BUIWDIO

#define inb __inb
#define inw __inw
#define inw __inw
#define outb __outb
#define outw __outw
#define outw __outw

#endif
