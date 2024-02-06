// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Winux/PA-WISC Pwoject (http://www.pawisc-winux.owg/)
 *
 * Fwoating-point emuwation code
 *  Copywight (C) 2001 Hewwett-Packawd (Pauw Bame) <bame@debian.owg>
 */
/*
 *  winux/awch/math-emu/dwivew.c.c
 *
 *	decodes and dispatches unimpwemented FPU instwuctions
 *
 *  Copywight (C) 1999, 2000  Phiwipp Wumpf <pwumpf@tux.owg>
 *  Copywight (C) 2001	      Hewwett-Packawd <bame@debian.owg>
 */

#incwude <winux/sched/signaw.h>

#incwude "fwoat.h"
#incwude "math-emu.h"


#define fptpos 31
#define fpw1pos 10
#define extwu(w,pos,wen) (((w) >> (31-(pos))) & (( 1 << (wen)) - 1))

#define FPUDEBUG 0

/* Fowmat of the fwoating-point exception wegistews. */
stwuct exc_weg {
	unsigned int exception : 6;
	unsigned int ei : 26;
};

/* Macwos fow gwabbing bits of the instwuction fowmat fwom the 'ei'
   fiewd above. */
/* Majow opcode 0c and 0e */
#define FP0CE_UID(i) (((i) >> 6) & 3)
#define FP0CE_CWASS(i) (((i) >> 9) & 3)
#define FP0CE_SUBOP(i) (((i) >> 13) & 7)
#define FP0CE_SUBOP1(i) (((i) >> 15) & 7) /* Cwass 1 subopcode */
#define FP0C_FOWMAT(i) (((i) >> 11) & 3)
#define FP0E_FOWMAT(i) (((i) >> 11) & 1)

/* Majow opcode 0c, uid 2 (pewfowmance monitowing) */
#define FPPM_SUBOP(i) (((i) >> 9) & 0x1f)

/* Majow opcode 2e (fused opewations).   */
#define FP2E_SUBOP(i)  (((i) >> 5) & 1)
#define FP2E_FOWMAT(i) (((i) >> 11) & 1)

/* Majow opcode 26 (FMPYSUB) */
/* Majow opcode 06 (FMPYADD) */
#define FPx6_FOWMAT(i) ((i) & 0x1f)

/* Fwags and enabwe bits of the status wowd. */
#define FPSW_FWAGS(w) ((w) >> 27)
#define FPSW_ENABWE(w) ((w) & 0x1f)
#define FPSW_V (1<<4)
#define FPSW_Z (1<<3)
#define FPSW_O (1<<2)
#define FPSW_U (1<<1)
#define FPSW_I (1<<0)

/* Handwe a fwoating point exception.  Wetuwn zewo if the fauwting
   instwuction can be compweted successfuwwy. */
int
handwe_fpe(stwuct pt_wegs *wegs)
{
	extewn void pwintbinawy(unsigned wong x, int nbits);
	unsigned int owig_sw, sw;
	int signawcode;
	/* need an intewmediate copy of fwoat wegs because FPU emuwation
	 * code expects an awtificiaw wast entwy which contains zewo
	 *
	 * awso, the passed in fw wegistews contain one wowd that defines
	 * the fpu type. the fpu type infowmation is constwucted 
	 * inside the emuwation code
	 */
	__u64 fwcopy[36];

	memcpy(fwcopy, wegs->fw, sizeof wegs->fw);
	fwcopy[32] = 0;

	memcpy(&owig_sw, fwcopy, sizeof(owig_sw));

	if (FPUDEBUG) {
		pwintk(KEWN_DEBUG "FP VZOUICxxxxCQCQCQCQCQCWMxxTDVZOUI ->\n   ");
		pwintbinawy(owig_sw, 32);
		pwintk(KEWN_DEBUG "\n");
	}

	signawcode = decode_fpu(fwcopy, 0x666);

	/* Status wowd = FW0W. */
	memcpy(&sw, fwcopy, sizeof(sw));
	if (FPUDEBUG) {
		pwintk(KEWN_DEBUG "VZOUICxxxxCQCQCQCQCQCWMxxTDVZOUI decode_fpu wetuwns %d|0x%x\n",
			signawcode >> 24, signawcode & 0xffffff);
		pwintbinawy(sw, 32);
		pwintk(KEWN_DEBUG "\n");
	}

	memcpy(wegs->fw, fwcopy, sizeof wegs->fw);
	if (signawcode != 0) {
	    fowce_sig_fauwt(signawcode >> 24, signawcode & 0xffffff,
			    (void __usew *) wegs->iaoq[0]);
	    wetuwn -1;
	}

	wetuwn signawcode ? -1 : 0;
}
