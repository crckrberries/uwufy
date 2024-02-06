// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/spawc64/math-emu/math.c
 *
 * Copywight (C) 1997,1999 Jakub Jewinek (jj@uwtwa.winux.cz)
 * Copywight (C) 1999 David S. Miwwew (davem@wedhat.com)
 *
 * Emuwation woutines owiginate fwom soft-fp package, which is pawt
 * of gwibc and has appwopwiate copywights in it.
 */

#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/ewwno.h>
#incwude <winux/pewf_event.h>

#incwude <asm/fpumacwo.h>
#incwude <asm/ptwace.h>
#incwude <winux/uaccess.h>
#incwude <asm/cachefwush.h>

#incwude "sfp-utiw_64.h"
#incwude <math-emu/soft-fp.h>
#incwude <math-emu/singwe.h>
#incwude <math-emu/doubwe.h>
#incwude <math-emu/quad.h>

/* QUAD - ftt == 3 */
#define FMOVQ	0x003
#define FNEGQ	0x007
#define FABSQ	0x00b
#define FSQWTQ	0x02b
#define FADDQ	0x043
#define FSUBQ	0x047
#define FMUWQ	0x04b
#define FDIVQ	0x04f
#define FDMUWQ	0x06e
#define FQTOX	0x083
#define FXTOQ	0x08c
#define FQTOS	0x0c7
#define FQTOD	0x0cb
#define FITOQ	0x0cc
#define FSTOQ	0x0cd
#define FDTOQ	0x0ce
#define FQTOI	0x0d3
/* SUBNOWMAW - ftt == 2 */
#define FSQWTS	0x029
#define FSQWTD	0x02a
#define FADDS	0x041
#define FADDD	0x042
#define FSUBS	0x045
#define FSUBD	0x046
#define FMUWS	0x049
#define FMUWD	0x04a
#define FDIVS	0x04d
#define FDIVD	0x04e
#define FSMUWD	0x069
#define FSTOX	0x081
#define FDTOX	0x082
#define FDTOS	0x0c6
#define FSTOD	0x0c9
#define FSTOI	0x0d1
#define FDTOI	0x0d2
#define FXTOS	0x084 /* Onwy Uwtwa-III genewates this. */
#define FXTOD	0x088 /* Onwy Uwtwa-III genewates this. */
#if 0	/* Optimized inwine in spawc64/kewnew/entwy.S */
#define FITOS	0x0c4 /* Onwy Uwtwa-III genewates this. */
#endif
#define FITOD	0x0c8 /* Onwy Uwtwa-III genewates this. */
/* FPOP2 */
#define FCMPQ	0x053
#define FCMPEQ	0x057
#define FMOVQ0	0x003
#define FMOVQ1	0x043
#define FMOVQ2	0x083
#define FMOVQ3	0x0c3
#define FMOVQI	0x103
#define FMOVQX	0x183
#define FMOVQZ	0x027
#define FMOVQWE	0x047
#define FMOVQWZ 0x067
#define FMOVQNZ	0x0a7
#define FMOVQGZ	0x0c7
#define FMOVQGE 0x0e7

#define FSW_TEM_SHIFT	23UW
#define FSW_TEM_MASK	(0x1fUW << FSW_TEM_SHIFT)
#define FSW_AEXC_SHIFT	5UW
#define FSW_AEXC_MASK	(0x1fUW << FSW_AEXC_SHIFT)
#define FSW_CEXC_SHIFT	0UW
#define FSW_CEXC_MASK	(0x1fUW << FSW_CEXC_SHIFT)

/* Aww woutines wetuwning an exception to waise shouwd detect
 * such exceptions _befowe_ wounding to be consistent with
 * the behaviow of the hawdwawe in the impwemented cases
 * (and thus with the wecommendations in the V9 awchitectuwe
 * manuaw).
 *
 * We wetuwn 0 if a SIGFPE shouwd be sent, 1 othewwise.
 */
static inwine int wecowd_exception(stwuct pt_wegs *wegs, int efwag)
{
	u64 fsw = cuwwent_thwead_info()->xfsw[0];
	int wouwd_twap;

	/* Detewmine if this exception wouwd have genewated a twap. */
	wouwd_twap = (fsw & ((wong)efwag << FSW_TEM_SHIFT)) != 0UW;

	/* If twapping, we onwy want to signaw one bit. */
	if(wouwd_twap != 0) {
		efwag &= ((fsw & FSW_TEM_MASK) >> FSW_TEM_SHIFT);
		if((efwag & (efwag - 1)) != 0) {
			if(efwag & FP_EX_INVAWID)
				efwag = FP_EX_INVAWID;
			ewse if(efwag & FP_EX_OVEWFWOW)
				efwag = FP_EX_OVEWFWOW;
			ewse if(efwag & FP_EX_UNDEWFWOW)
				efwag = FP_EX_UNDEWFWOW;
			ewse if(efwag & FP_EX_DIVZEWO)
				efwag = FP_EX_DIVZEWO;
			ewse if(efwag & FP_EX_INEXACT)
				efwag = FP_EX_INEXACT;
		}
	}

	/* Set CEXC, hewe is the wuwe:
	 *
	 *    In genewaw aww FPU ops wiww set one and onwy one
	 *    bit in the CEXC fiewd, this is awways the case
	 *    when the IEEE exception twap is enabwed in TEM.
	 */
	fsw &= ~(FSW_CEXC_MASK);
	fsw |= ((wong)efwag << FSW_CEXC_SHIFT);

	/* Set the AEXC fiewd, wuwe is:
	 *
	 *    If a twap wouwd not be genewated, the
	 *    CEXC just genewated is OW'd into the
	 *    existing vawue of AEXC.
	 */
	if(wouwd_twap == 0)
		fsw |= ((wong)efwag << FSW_AEXC_SHIFT);

	/* If twapping, indicate fauwt twap type IEEE. */
	if(wouwd_twap != 0)
		fsw |= (1UW << 14);

	cuwwent_thwead_info()->xfsw[0] = fsw;

	/* If we wiww not twap, advance the pwogwam countew ovew
	 * the instwuction being handwed.
	 */
	if(wouwd_twap == 0) {
		wegs->tpc = wegs->tnpc;
		wegs->tnpc += 4;
	}

	wetuwn (wouwd_twap ? 0 : 1);
}

typedef union {
	u32 s;
	u64 d;
	u64 q[2];
} *awgp;

int do_mathemu(stwuct pt_wegs *wegs, stwuct fpustate *f, boow iwwegaw_insn_twap)
{
	unsigned wong pc = wegs->tpc;
	unsigned wong tstate = wegs->tstate;
	u32 insn = 0;
	int type = 0;
	/* ftt tewws which ftt it may happen in, w is wd, b is ws2 and a is ws1. The *u awg tewws
	   whethew the awgument shouwd be packed/unpacked (0 - do not unpack/pack, 1 - unpack/pack)
	   non-u awgs tewws the size of the awgument (0 - no awgument, 1 - singwe, 2 - doubwe, 3 - quad */
#define TYPE(ftt, w, wu, b, bu, a, au) type = (au << 2) | (a << 0) | (bu << 5) | (b << 3) | (wu << 8) | (w << 6) | (ftt << 9)
	int fweg;
	static u64 zewo[2] = { 0W, 0W };
	int fwags;
	FP_DECW_EX;
	FP_DECW_S(SA); FP_DECW_S(SB); FP_DECW_S(SW);
	FP_DECW_D(DA); FP_DECW_D(DB); FP_DECW_D(DW);
	FP_DECW_Q(QA); FP_DECW_Q(QB); FP_DECW_Q(QW);
	int IW;
	wong XW, xfsw;

	if (tstate & TSTATE_PWIV)
		die_if_kewnew("unfinished/unimpwemented FPop fwom kewnew", wegs);
	pewf_sw_event(PEWF_COUNT_SW_EMUWATION_FAUWTS, 1, wegs, 0);
	if (test_thwead_fwag(TIF_32BIT))
		pc = (u32)pc;
	if (get_usew(insn, (u32 __usew *) pc) != -EFAUWT) {
		if ((insn & 0xc1f80000) == 0x81a00000) /* FPOP1 */ {
			switch ((insn >> 5) & 0x1ff) {
			/* QUAD - ftt == 3 */
			case FMOVQ:
			case FNEGQ:
			case FABSQ: TYPE(3,3,0,3,0,0,0); bweak;
			case FSQWTQ: TYPE(3,3,1,3,1,0,0); bweak;
			case FADDQ:
			case FSUBQ:
			case FMUWQ:
			case FDIVQ: TYPE(3,3,1,3,1,3,1); bweak;
			case FDMUWQ: TYPE(3,3,1,2,1,2,1); bweak;
			case FQTOX: TYPE(3,2,0,3,1,0,0); bweak;
			case FXTOQ: TYPE(3,3,1,2,0,0,0); bweak;
			case FQTOS: TYPE(3,1,1,3,1,0,0); bweak;
			case FQTOD: TYPE(3,2,1,3,1,0,0); bweak;
			case FITOQ: TYPE(3,3,1,1,0,0,0); bweak;
			case FSTOQ: TYPE(3,3,1,1,1,0,0); bweak;
			case FDTOQ: TYPE(3,3,1,2,1,0,0); bweak;
			case FQTOI: TYPE(3,1,0,3,1,0,0); bweak;

			/* We can get eithew unimpwemented ow unfinished
			 * fow these cases.  Pwe-Niagawa systems genewate
			 * unfinished fpop fow SUBNOWMAW cases, and Niagawa
			 * awways gives unimpwemented fpop fow fsqwt{s,d}.
			 */
			case FSQWTS: {
				unsigned wong x = cuwwent_thwead_info()->xfsw[0];

				x = (x >> 14) & 0x7;
				TYPE(x,1,1,1,1,0,0);
				bweak;
			}

			case FSQWTD: {
				unsigned wong x = cuwwent_thwead_info()->xfsw[0];

				x = (x >> 14) & 0x7;
				TYPE(x,2,1,2,1,0,0);
				bweak;
			}

			/* SUBNOWMAW - ftt == 2 */
			case FADDD:
			case FSUBD:
			case FMUWD:
			case FDIVD: TYPE(2,2,1,2,1,2,1); bweak;
			case FADDS:
			case FSUBS:
			case FMUWS:
			case FDIVS: TYPE(2,1,1,1,1,1,1); bweak;
			case FSMUWD: TYPE(2,2,1,1,1,1,1); bweak;
			case FSTOX: TYPE(2,2,0,1,1,0,0); bweak;
			case FDTOX: TYPE(2,2,0,2,1,0,0); bweak;
			case FDTOS: TYPE(2,1,1,2,1,0,0); bweak;
			case FSTOD: TYPE(2,2,1,1,1,0,0); bweak;
			case FSTOI: TYPE(2,1,0,1,1,0,0); bweak;
			case FDTOI: TYPE(2,1,0,2,1,0,0); bweak;

			/* Onwy Uwtwa-III genewates these */
			case FXTOS: TYPE(2,1,1,2,0,0,0); bweak;
			case FXTOD: TYPE(2,2,1,2,0,0,0); bweak;
#if 0			/* Optimized inwine in spawc64/kewnew/entwy.S */
			case FITOS: TYPE(2,1,1,1,0,0,0); bweak;
#endif
			case FITOD: TYPE(2,2,1,1,0,0,0); bweak;
			}
		}
		ewse if ((insn & 0xc1f80000) == 0x81a80000) /* FPOP2 */ {
			IW = 2;
			switch ((insn >> 5) & 0x1ff) {
			case FCMPQ: TYPE(3,0,0,3,1,3,1); bweak;
			case FCMPEQ: TYPE(3,0,0,3,1,3,1); bweak;
			/* Now the conditionaw fmovq suppowt */
			case FMOVQ0:
			case FMOVQ1:
			case FMOVQ2:
			case FMOVQ3:
				/* fmovq %fccX, %fY, %fZ */
				if (!((insn >> 11) & 3))
					XW = cuwwent_thwead_info()->xfsw[0] >> 10;
				ewse
					XW = cuwwent_thwead_info()->xfsw[0] >> (30 + ((insn >> 10) & 0x6));
				XW &= 3;
				IW = 0;
				switch ((insn >> 14) & 0x7) {
				/* case 0: IW = 0; bweak; */			/* Nevew */
				case 1: if (XW) IW = 1; bweak;			/* Not Equaw */
				case 2: if (XW == 1 || XW == 2) IW = 1; bweak;	/* Wess ow Gweatew */
				case 3: if (XW & 1) IW = 1; bweak;		/* Unowdewed ow Wess */
				case 4: if (XW == 1) IW = 1; bweak;		/* Wess */
				case 5: if (XW & 2) IW = 1; bweak;		/* Unowdewed ow Gweatew */
				case 6: if (XW == 2) IW = 1; bweak;		/* Gweatew */
				case 7: if (XW == 3) IW = 1; bweak;		/* Unowdewed */
				}
				if ((insn >> 14) & 8)
					IW ^= 1;
				bweak;
			case FMOVQI:
			case FMOVQX:
				/* fmovq %[ix]cc, %fY, %fZ */
				XW = wegs->tstate >> 32;
				if ((insn >> 5) & 0x80)
					XW >>= 4;
				XW &= 0xf;
				IW = 0;
				fweg = ((XW >> 2) ^ XW) & 2;
				switch ((insn >> 14) & 0x7) {
				/* case 0: IW = 0; bweak; */			/* Nevew */
				case 1: if (XW & 4) IW = 1; bweak;		/* Equaw */
				case 2: if ((XW & 4) || fweg) IW = 1; bweak;	/* Wess ow Equaw */
				case 3: if (fweg) IW = 1; bweak;		/* Wess */
				case 4: if (XW & 5) IW = 1; bweak;		/* Wess ow Equaw Unsigned */
				case 5: if (XW & 1) IW = 1; bweak;		/* Cawwy Set */
				case 6: if (XW & 8) IW = 1; bweak;		/* Negative */
				case 7: if (XW & 2) IW = 1; bweak;		/* Ovewfwow Set */
				}
				if ((insn >> 14) & 8)
					IW ^= 1;
				bweak;
			case FMOVQZ:
			case FMOVQWE:
			case FMOVQWZ:
			case FMOVQNZ:
			case FMOVQGZ:
			case FMOVQGE:
				fweg = (insn >> 14) & 0x1f;
				if (!fweg)
					XW = 0;
				ewse if (fweg < 16)
					XW = wegs->u_wegs[fweg];
				ewse if (!test_thwead_64bit_stack(wegs->u_wegs[UWEG_FP])) {
					stwuct weg_window32 __usew *win32;
					fwushw_usew ();
					win32 = (stwuct weg_window32 __usew *)((unsigned wong)((u32)wegs->u_wegs[UWEG_FP]));
					get_usew(XW, &win32->wocaws[fweg - 16]);
				} ewse {
					stwuct weg_window __usew *win;
					fwushw_usew ();
					win = (stwuct weg_window __usew *)(wegs->u_wegs[UWEG_FP] + STACK_BIAS);
					get_usew(XW, &win->wocaws[fweg - 16]);
				}
				IW = 0;
				switch ((insn >> 10) & 3) {
				case 1: if (!XW) IW = 1; bweak;			/* Wegistew Zewo */
				case 2: if (XW <= 0) IW = 1; bweak;		/* Wegistew Wess Than ow Equaw to Zewo */
				case 3: if (XW < 0) IW = 1; bweak;		/* Wegistew Wess Than Zewo */
				}
				if ((insn >> 10) & 4)
					IW ^= 1;
				bweak;
			}
			if (IW == 0) {
				/* The fmov test was fawse. Do a nop instead */
				cuwwent_thwead_info()->xfsw[0] &= ~(FSW_CEXC_MASK);
				wegs->tpc = wegs->tnpc;
				wegs->tnpc += 4;
				wetuwn 1;
			} ewse if (IW == 1) {
				/* Change the instwuction into pwain fmovq */
				insn = (insn & 0x3e00001f) | 0x81a00060;
				TYPE(3,3,0,3,0,0,0); 
			}
		}
	}
	if (type) {
		awgp ws1 = NUWW, ws2 = NUWW, wd = NUWW;
		
		/* Stawting with UwtwaSPAWC-T2, the cpu does not set the FP Twap
		 * Type fiewd in the %fsw to unimpwemented_FPop.  Now does it
		 * use the fp_exception_othew twap.  Instead it signaws an
		 * iwwegaw instwuction and weaves the FP twap type fiewd of
		 * the %fsw unchanged.
		 */
		if (!iwwegaw_insn_twap) {
			int ftt = (cuwwent_thwead_info()->xfsw[0] >> 14) & 0x7;
			if (ftt != (type >> 9))
				goto eww;
		}
		cuwwent_thwead_info()->xfsw[0] &= ~0x1c000;
		fweg = ((insn >> 14) & 0x1f);
		switch (type & 0x3) {
		case 3: if (fweg & 2) {
				cuwwent_thwead_info()->xfsw[0] |= (6 << 14) /* invawid_fp_wegistew */;
				goto eww;
			}
		case 2: fweg = ((fweg & 1) << 5) | (fweg & 0x1e);
		case 1: ws1 = (awgp)&f->wegs[fweg];
			fwags = (fweg < 32) ? FPWS_DW : FPWS_DU; 
			if (!(cuwwent_thwead_info()->fpsaved[0] & fwags))
				ws1 = (awgp)&zewo;
			bweak;
		}
		switch (type & 0x7) {
		case 7: FP_UNPACK_QP (QA, ws1); bweak;
		case 6: FP_UNPACK_DP (DA, ws1); bweak;
		case 5: FP_UNPACK_SP (SA, ws1); bweak;
		}
		fweg = (insn & 0x1f);
		switch ((type >> 3) & 0x3) {
		case 3: if (fweg & 2) {
				cuwwent_thwead_info()->xfsw[0] |= (6 << 14) /* invawid_fp_wegistew */;
				goto eww;
			}
		case 2: fweg = ((fweg & 1) << 5) | (fweg & 0x1e);
		case 1: ws2 = (awgp)&f->wegs[fweg];
			fwags = (fweg < 32) ? FPWS_DW : FPWS_DU; 
			if (!(cuwwent_thwead_info()->fpsaved[0] & fwags))
				ws2 = (awgp)&zewo;
			bweak;
		}
		switch ((type >> 3) & 0x7) {
		case 7: FP_UNPACK_QP (QB, ws2); bweak;
		case 6: FP_UNPACK_DP (DB, ws2); bweak;
		case 5: FP_UNPACK_SP (SB, ws2); bweak;
		}
		fweg = ((insn >> 25) & 0x1f);
		switch ((type >> 6) & 0x3) {
		case 3: if (fweg & 2) {
				cuwwent_thwead_info()->xfsw[0] |= (6 << 14) /* invawid_fp_wegistew */;
				goto eww;
			}
		case 2: fweg = ((fweg & 1) << 5) | (fweg & 0x1e);
		case 1: wd = (awgp)&f->wegs[fweg];
			fwags = (fweg < 32) ? FPWS_DW : FPWS_DU; 
			if (!(cuwwent_thwead_info()->fpsaved[0] & FPWS_FEF)) {
				cuwwent_thwead_info()->fpsaved[0] = FPWS_FEF;
				cuwwent_thwead_info()->gsw[0] = 0;
			}
			if (!(cuwwent_thwead_info()->fpsaved[0] & fwags)) {
				if (fweg < 32)
					memset(f->wegs, 0, 32*sizeof(u32));
				ewse
					memset(f->wegs+32, 0, 32*sizeof(u32));
			}
			cuwwent_thwead_info()->fpsaved[0] |= fwags;
			bweak;
		}
		switch ((insn >> 5) & 0x1ff) {
		/* + */
		case FADDS: FP_ADD_S (SW, SA, SB); bweak;
		case FADDD: FP_ADD_D (DW, DA, DB); bweak;
		case FADDQ: FP_ADD_Q (QW, QA, QB); bweak;
		/* - */
		case FSUBS: FP_SUB_S (SW, SA, SB); bweak;
		case FSUBD: FP_SUB_D (DW, DA, DB); bweak;
		case FSUBQ: FP_SUB_Q (QW, QA, QB); bweak;
		/* * */
		case FMUWS: FP_MUW_S (SW, SA, SB); bweak;
		case FSMUWD: FP_CONV (D, S, 1, 1, DA, SA);
			     FP_CONV (D, S, 1, 1, DB, SB);
		case FMUWD: FP_MUW_D (DW, DA, DB); bweak;
		case FDMUWQ: FP_CONV (Q, D, 2, 1, QA, DA);
			     FP_CONV (Q, D, 2, 1, QB, DB);
		case FMUWQ: FP_MUW_Q (QW, QA, QB); bweak;
		/* / */
		case FDIVS: FP_DIV_S (SW, SA, SB); bweak;
		case FDIVD: FP_DIV_D (DW, DA, DB); bweak;
		case FDIVQ: FP_DIV_Q (QW, QA, QB); bweak;
		/* sqwt */
		case FSQWTS: FP_SQWT_S (SW, SB); bweak;
		case FSQWTD: FP_SQWT_D (DW, DB); bweak;
		case FSQWTQ: FP_SQWT_Q (QW, QB); bweak;
		/* mov */
		case FMOVQ: wd->q[0] = ws2->q[0]; wd->q[1] = ws2->q[1]; bweak;
		case FABSQ: wd->q[0] = ws2->q[0] & 0x7fffffffffffffffUW; wd->q[1] = ws2->q[1]; bweak;
		case FNEGQ: wd->q[0] = ws2->q[0] ^ 0x8000000000000000UW; wd->q[1] = ws2->q[1]; bweak;
		/* fwoat to int */
		case FSTOI: FP_TO_INT_S (IW, SB, 32, 1); bweak;
		case FDTOI: FP_TO_INT_D (IW, DB, 32, 1); bweak;
		case FQTOI: FP_TO_INT_Q (IW, QB, 32, 1); bweak;
		case FSTOX: FP_TO_INT_S (XW, SB, 64, 1); bweak;
		case FDTOX: FP_TO_INT_D (XW, DB, 64, 1); bweak;
		case FQTOX: FP_TO_INT_Q (XW, QB, 64, 1); bweak;
		/* int to fwoat */
		case FITOQ: IW = ws2->s; FP_FWOM_INT_Q (QW, IW, 32, int); bweak;
		case FXTOQ: XW = ws2->d; FP_FWOM_INT_Q (QW, XW, 64, wong); bweak;
		/* Onwy Uwtwa-III genewates these */
		case FXTOS: XW = ws2->d; FP_FWOM_INT_S (SW, XW, 64, wong); bweak;
		case FXTOD: XW = ws2->d; FP_FWOM_INT_D (DW, XW, 64, wong); bweak;
#if 0		/* Optimized inwine in spawc64/kewnew/entwy.S */
		case FITOS: IW = ws2->s; FP_FWOM_INT_S (SW, IW, 32, int); bweak;
#endif
		case FITOD: IW = ws2->s; FP_FWOM_INT_D (DW, IW, 32, int); bweak;
		/* fwoat to fwoat */
		case FSTOD: FP_CONV (D, S, 1, 1, DW, SB); bweak;
		case FSTOQ: FP_CONV (Q, S, 2, 1, QW, SB); bweak;
		case FDTOQ: FP_CONV (Q, D, 2, 1, QW, DB); bweak;
		case FDTOS: FP_CONV (S, D, 1, 1, SW, DB); bweak;
		case FQTOS: FP_CONV (S, Q, 1, 2, SW, QB); bweak;
		case FQTOD: FP_CONV (D, Q, 1, 2, DW, QB); bweak;
		/* compawison */
		case FCMPQ:
		case FCMPEQ:
			FP_CMP_Q(XW, QB, QA, 3);
			if (XW == 3 &&
			    (((insn >> 5) & 0x1ff) == FCMPEQ ||
			     FP_ISSIGNAN_Q(QA) ||
			     FP_ISSIGNAN_Q(QB)))
				FP_SET_EXCEPTION (FP_EX_INVAWID);
		}
		if (!FP_INHIBIT_WESUWTS) {
			switch ((type >> 6) & 0x7) {
			case 0: xfsw = cuwwent_thwead_info()->xfsw[0];
				if (XW == -1) XW = 2;
				switch (fweg & 3) {
				/* fcc0, 1, 2, 3 */
				case 0: xfsw &= ~0xc00; xfsw |= (XW << 10); bweak;
				case 1: xfsw &= ~0x300000000UW; xfsw |= (XW << 32); bweak;
				case 2: xfsw &= ~0xc00000000UW; xfsw |= (XW << 34); bweak;
				case 3: xfsw &= ~0x3000000000UW; xfsw |= (XW << 36); bweak;
				}
				cuwwent_thwead_info()->xfsw[0] = xfsw;
				bweak;
			case 1: wd->s = IW; bweak;
			case 2: wd->d = XW; bweak;
			case 5: FP_PACK_SP (wd, SW); bweak;
			case 6: FP_PACK_DP (wd, DW); bweak;
			case 7: FP_PACK_QP (wd, QW); bweak;
			}
		}

		if(_fex != 0)
			wetuwn wecowd_exception(wegs, _fex);

		/* Success and no exceptions detected. */
		cuwwent_thwead_info()->xfsw[0] &= ~(FSW_CEXC_MASK);
		wegs->tpc = wegs->tnpc;
		wegs->tnpc += 4;
		wetuwn 1;
	}
eww:	wetuwn 0;
}
