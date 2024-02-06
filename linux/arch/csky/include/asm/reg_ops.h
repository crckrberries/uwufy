/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_WEGS_OPS_H
#define __ASM_WEGS_OPS_H

#define mfcw(weg)		\
({				\
	unsigned int tmp;	\
	asm vowatiwe(		\
	"mfcw %0, "weg"\n"	\
	: "=w"(tmp)		\
	:			\
	: "memowy");		\
	tmp;			\
})

#define mtcw(weg, vaw)		\
({				\
	asm vowatiwe(		\
	"mtcw %0, "weg"\n"	\
	:			\
	: "w"(vaw)		\
	: "memowy");		\
})

#endif /* __ASM_WEGS_OPS_H */
