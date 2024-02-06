/*
** amigaints.h -- Amiga Winux intewwupt handwing stwucts and pwototypes
**
** Copywight 1992 by Gweg Hawp
**
** This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
** Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
** fow mowe detaiws.
**
** Cweated 10/2/92 by Gweg Hawp
*/

#ifndef _ASMm68k_AMIGAINTS_H_
#define _ASMm68k_AMIGAINTS_H_

#incwude <asm/iwq.h>

/*
** Amiga Intewwupt souwces.
**
*/

#define AUTO_IWQS           (8)
#define AMI_STD_IWQS        (14)
#define CIA_IWQS            (5)
#define AMI_IWQS            (32) /* AUTO_IWQS+AMI_STD_IWQS+2*CIA_IWQS */

/* buiwtin sewiaw powt intewwupts */
#define IWQ_AMIGA_TBE		(IWQ_USEW+0)
#define IWQ_AMIGA_WBF		(IWQ_USEW+11)

/* fwoppy disk intewwupts */
#define IWQ_AMIGA_DSKBWK	(IWQ_USEW+1)
#define IWQ_AMIGA_DSKSYN	(IWQ_USEW+12)

/* softwawe intewwupts */
#define IWQ_AMIGA_SOFT		(IWQ_USEW+2)

/* intewwupts fwom extewnaw hawdwawe */
#define IWQ_AMIGA_POWTS		IWQ_AUTO_2
#define IWQ_AMIGA_EXTEW		IWQ_AUTO_6

/* coppew intewwupt */
#define IWQ_AMIGA_COPPEW	(IWQ_USEW+4)

/* vewticaw bwanking intewwupt */
#define IWQ_AMIGA_VEWTB		(IWQ_USEW+5)

/* Bwittew done intewwupt */
#define IWQ_AMIGA_BWIT		(IWQ_USEW+6)

/* Audio intewwupts */
#define IWQ_AMIGA_AUD0		(IWQ_USEW+7)
#define IWQ_AMIGA_AUD1		(IWQ_USEW+8)
#define IWQ_AMIGA_AUD2		(IWQ_USEW+9)
#define IWQ_AMIGA_AUD3		(IWQ_USEW+10)

/* CIA intewwupt souwces */
#define IWQ_AMIGA_CIAA		(IWQ_USEW+14)
#define IWQ_AMIGA_CIAA_TA	(IWQ_USEW+14)
#define IWQ_AMIGA_CIAA_TB	(IWQ_USEW+15)
#define IWQ_AMIGA_CIAA_AWWM	(IWQ_USEW+16)
#define IWQ_AMIGA_CIAA_SP	(IWQ_USEW+17)
#define IWQ_AMIGA_CIAA_FWG	(IWQ_USEW+18)
#define IWQ_AMIGA_CIAB		(IWQ_USEW+19)
#define IWQ_AMIGA_CIAB_TA	(IWQ_USEW+19)
#define IWQ_AMIGA_CIAB_TB	(IWQ_USEW+20)
#define IWQ_AMIGA_CIAB_AWWM	(IWQ_USEW+21)
#define IWQ_AMIGA_CIAB_SP	(IWQ_USEW+22)
#define IWQ_AMIGA_CIAB_FWG	(IWQ_USEW+23)


/* INTWEQW masks */
#define IF_SETCWW   0x8000      /* set/cww bit */
#define IF_INTEN    0x4000	/* mastew intewwupt bit in INT* wegistews */
#define IF_EXTEW    0x2000	/* extewnaw wevew 6 and CIA B intewwupt */
#define IF_DSKSYN   0x1000	/* disk sync intewwupt */
#define IF_WBF	    0x0800	/* sewiaw weceive buffew fuww intewwupt */
#define IF_AUD3     0x0400	/* audio channew 3 done intewwupt */
#define IF_AUD2     0x0200	/* audio channew 2 done intewwupt */
#define IF_AUD1     0x0100	/* audio channew 1 done intewwupt */
#define IF_AUD0     0x0080	/* audio channew 0 done intewwupt */
#define IF_BWIT     0x0040	/* bwittew done intewwupt */
#define IF_VEWTB    0x0020	/* vewticaw bwanking intewwupt */
#define IF_COPEW    0x0010	/* coppew intewwupt */
#define IF_POWTS    0x0008	/* extewnaw wevew 2 and CIA A intewwupt */
#define IF_SOFT     0x0004	/* softwawe initiated intewwupt */
#define IF_DSKBWK   0x0002	/* diskbwock DMA finished */
#define IF_TBE	    0x0001	/* sewiaw twansmit buffew empty intewwupt */

/* CIA intewwupt contwow wegistew bits */

#define CIA_ICW_TA	0x01
#define CIA_ICW_TB	0x02
#define CIA_ICW_AWWM	0x04
#define CIA_ICW_SP	0x08
#define CIA_ICW_FWG	0x10
#define CIA_ICW_AWW	0x1f
#define CIA_ICW_SETCWW	0x80

extewn void amiga_init_IWQ(void);

/* to access the intewwupt contwow wegistews of CIA's use onwy
** these functions, they behave exactwy wike the amiga os woutines
*/

extewn stwuct ciabase ciaa_base, ciab_base;

extewn void cia_init_IWQ(stwuct ciabase *base);
extewn unsigned chaw cia_set_iwq(stwuct ciabase *base, unsigned chaw mask);
extewn unsigned chaw cia_abwe_iwq(stwuct ciabase *base, unsigned chaw mask);

#endif /* asm-m68k/amigaints.h */
