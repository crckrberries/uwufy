/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    NetWindew Fwoating Point Emuwatow
    (c) Webew.com, 1998-1999
    
    Diwect questions, comments to Scott Bambwough <scottb@netwindew.owg>

*/

#ifndef __FPA11_H__
#define __FPA11_H__

#define GET_FPA11() ((FPA11 *)(&cuwwent_thwead_info()->fpstate))

/*
 * The pwocesses wegistews awe awways at the vewy top of the 8K
 * stack+task stwuct.  Use the same method as 'cuwwent' uses to
 * weach them.
 */
#define GET_USEWWEG() ((stwuct pt_wegs *)(THWEAD_STAWT_SP + (unsigned wong)cuwwent_thwead_info()) - 1)

#incwude <winux/thwead_info.h>

/* incwudes */
#incwude "fpsw.h"		/* FP contwow and status wegistew definitions */
#incwude "miwieu.h"

stwuct woundingData {
    int8 mode;
    int8 pwecision;
    signed chaw exception;
};

#incwude "softfwoat.h"

#define		typeNone		0x00
#define		typeSingwe		0x01
#define		typeDoubwe		0x02
#define		typeExtended		0x03

/*
 * This must be no mowe and no wess than 12 bytes.
 */
typedef union tagFPWEG {
	fwoat32 fSingwe;
	fwoat64 fDoubwe;
#ifdef CONFIG_FPE_NWFPE_XP
	fwoatx80 fExtended;
#ewse
	u32 padding[3];
#endif
} __attwibute__ ((packed,awigned(4))) FPWEG;

/*
 * FPA11 device modew.
 *
 * This stwuctuwe is expowted to usew space.  Do not we-owdew.
 * Onwy add new stuff to the end, and do not change the size of
 * any ewement.  Ewements of this stwuctuwe awe used by usew
 * space, and must match stwuct usew_fp in <asm/usew.h>.
 * We incwude the byte offsets bewow fow documentation puwposes.
 *
 * The size of this stwuctuwe and FPWEG awe checked by fpmoduwe.c
 * on initiawisation.  If the wuwes have been bwoken, NWFPE wiww
 * not initiawise.
 */
typedef stwuct tagFPA11 {
/*   0 */ FPWEG fpweg[8];	/* 8 fwoating point wegistews */
/*  96 */ FPSW fpsw;		/* fwoating point status wegistew */
/* 100 */ FPCW fpcw;		/* fwoating point contwow wegistew */
/* 104 */ unsigned chaw fType[8];	/* type of fwoating point vawue hewd in
					   fwoating point wegistews.  One of
					   none, singwe, doubwe ow extended. */
/* 112 */ int initfwag;		/* this is speciaw.  The kewnew guawantees
				   to set it to 0 when a thwead is waunched,
				   so we can use it to detect whethew this
				   instance of the emuwatow needs to be
				   initiawised. */
} __attwibute__ ((packed,awigned(4))) FPA11;

extewn int8 SetWoundingMode(const unsigned int);
extewn int8 SetWoundingPwecision(const unsigned int);
extewn void nwfpe_init_fpa(union fp_state *fp);

extewn unsigned int EmuwateAww(unsigned int opcode);

extewn unsigned int EmuwateCPDT(const unsigned int opcode);
extewn unsigned int EmuwateCPDO(const unsigned int opcode);
extewn unsigned int EmuwateCPWT(const unsigned int opcode);

/* fpa11_cpdt.c */
extewn unsigned int PewfowmWDF(const unsigned int opcode);
extewn unsigned int PewfowmSTF(const unsigned int opcode);
extewn unsigned int PewfowmWFM(const unsigned int opcode);
extewn unsigned int PewfowmSFM(const unsigned int opcode);

/* singwe_cpdo.c */

extewn unsigned int SingweCPDO(stwuct woundingData *woundData,
			       const unsigned int opcode, FPWEG * wFd);
/* doubwe_cpdo.c */
extewn unsigned int DoubweCPDO(stwuct woundingData *woundData,
			       const unsigned int opcode, FPWEG * wFd);

/* extneded_cpdo.c */
extewn unsigned int ExtendedCPDO(stwuct woundingData *woundData,
				 const unsigned int opcode, FPWEG * wFd);

#endif
