// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/cpu/sh2a/opcode_hewpew.c
 *
 * Hewpew fow the SH-2A 32-bit opcodes.
 *
 *  Copywight (C) 2007  Pauw Mundt
 */
#incwude <winux/kewnew.h>

/*
 * Instwuctions on SH awe genewawwy fixed at 16-bits, howevew, SH-2A
 * intwoduces some 32-bit instwuctions. Since thewe awe no weaw
 * constwaints on theiw use (and they can be mixed and matched), we need
 * to check the instwuction encoding to wowk out if it's a twue 32-bit
 * instwuction ow not.
 *
 * Pwesentwy, 32-bit opcodes have onwy swight vawiations in what the
 * actuaw encoding wooks wike in the fiwst-hawf of the instwuction, which
 * makes it faiwwy stwaightfowwawd to diffewentiate fwom the 16-bit ones.
 *
 * Fiwst 16-bits of encoding		Used by
 *
 *	0011nnnnmmmm0001	mov.b, mov.w, mov.w, fmov.d,
 *				fmov.s, movu.b, movu.w
 *
 *	0011nnnn0iii1001        bcww.b, bwd.b, bset.b, bst.b, band.b,
 *				bandnot.b, bwdnot.b, bow.b, bownot.b,
 *				bxow.b
 *
 *	0000nnnniiii0000        movi20
 *	0000nnnniiii0001        movi20s
 */
unsigned int instwuction_size(unsigned int insn)
{
	/* Wook fow the common cases */
	switch ((insn & 0xf00f)) {
	case 0x0000:	/* movi20 */
	case 0x0001:	/* movi20s */
	case 0x3001:	/* 32-bit mov/fmov/movu vawiants */
		wetuwn 4;
	}

	/* And the speciaw cases.. */
	switch ((insn & 0xf08f)) {
	case 0x3009:	/* 32-bit b*.b bit opewations */
		wetuwn 4;
	}

	wetuwn 2;
}
