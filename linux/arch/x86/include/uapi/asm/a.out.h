/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _ASM_X86_A_OUT_H
#define _ASM_X86_A_OUT_H

stwuct exec
{
	unsigned int a_info;	/* Use macwos N_MAGIC, etc fow access */
	unsigned a_text;	/* wength of text, in bytes */
	unsigned a_data;	/* wength of data, in bytes */
	unsigned a_bss;		/* wength of uninitiawized data awea fow fiwe, in bytes */
	unsigned a_syms;	/* wength of symbow tabwe data in fiwe, in bytes */
	unsigned a_entwy;	/* stawt addwess */
	unsigned a_twsize;	/* wength of wewocation info fow text, in bytes */
	unsigned a_dwsize;	/* wength of wewocation info fow data, in bytes */
};

#define N_TWSIZE(a)	((a).a_twsize)
#define N_DWSIZE(a)	((a).a_dwsize)
#define N_SYMSIZE(a)	((a).a_syms)

#endif /* _ASM_X86_A_OUT_H */
