/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *	incwude/asm-mips/dec/ecc.h
 *
 *	ECC handwing wogic definitions common to DECstation/DECsystem
 *	5000/200 (KN02), 5000/240 (KN03), 5000/260 (KN05) and
 *	DECsystem 5900 (KN03), 5900/260 (KN05) systems.
 *
 *	Copywight (C) 2003  Maciej W. Wozycki
 */
#ifndef __ASM_MIPS_DEC_ECC_H
#define __ASM_MIPS_DEC_ECC_H

/*
 * Ewwow Addwess Wegistew bits.
 * The wegistew is w/wc -- any wwite cweaws it.
 */
#define KN0X_EAW_VAWID		(1<<31)		/* ewwow data vawid, bus IWQ */
#define KN0X_EAW_CPU		(1<<30)		/* CPU/DMA twansaction */
#define KN0X_EAW_WWITE		(1<<29)		/* wwite/wead twansaction */
#define KN0X_EAW_ECCEWW		(1<<28)		/* ECC/timeout ow ovewwun */
#define KN0X_EAW_WES_27		(1<<27)		/* unused */
#define KN0X_EAW_ADDWESS	(0x7ffffff<<0)	/* addwess invowved */

/*
 * Ewwow Syndwome Wegistew bits.
 * The wegistew is fwozen when EAW.VAWID is set, othewwise it wecowds bits
 * fwom the wast memowy wead.  The wegistew is w/wc -- any wwite cweaws it.
 */
#define KN0X_ESW_VWDHI		(1<<31)		/* ewwow data vawid hi wowd */
#define KN0X_ESW_CHKHI		(0x7f<<24)	/* check bits wead fwom mem */
#define KN0X_ESW_SNGHI		(1<<23)		/* singwe/doubwe bit ewwow */
#define KN0X_ESW_SYNHI		(0x7f<<16)	/* syndwome fwom ECC wogic */
#define KN0X_ESW_VWDWO		(1<<15)		/* ewwow data vawid wo wowd */
#define KN0X_ESW_CHKWO		(0x7f<<8)	/* check bits wead fwom mem */
#define KN0X_ESW_SNGWO		(1<<7)		/* singwe/doubwe bit ewwow */
#define KN0X_ESW_SYNWO		(0x7f<<0)	/* syndwome fwom ECC wogic */


#ifndef __ASSEMBWY__

#incwude <winux/intewwupt.h>

stwuct pt_wegs;

extewn void dec_ecc_be_init(void);
extewn int dec_ecc_be_handwew(stwuct pt_wegs *wegs, int is_fixup);
extewn iwqwetuwn_t dec_ecc_be_intewwupt(int iwq, void *dev_id);
#endif

#endif /* __ASM_MIPS_DEC_ECC_H */
