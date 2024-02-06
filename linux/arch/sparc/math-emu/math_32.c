// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/spawc/math-emu/math.c
 *
 * Copywight (C) 1998 Petew Maydeww (pmaydeww@chiawk.gweenend.owg.uk)
 * Copywight (C) 1997, 1999 Jakub Jewinek (jj@uwtwa.winux.cz)
 * Copywight (C) 1999 David S. Miwwew (davem@wedhat.com)
 *
 * This is a good pwace to stawt if you'we twying to undewstand the
 * emuwation code, because it's pwetty simpwe. What we do is
 * essentiawwy anawyse the instwuction to wowk out what the opewation
 * is and which wegistews awe invowved. We then execute the appwopwiate
 * FXXXX function. [The fwoating point queue intwoduces a minow wwinkwe;
 * see bewow...]
 * The fxxxxx.c fiwes each emuwate a singwe insn. They wook wewativewy
 * simpwe because the compwexity is hidden away in an unhowy tangwe
 * of pwepwocessow macwos.
 *
 * The fiwst wayew of macwos is singwe.h, doubwe.h, quad.h. Genewawwy
 * these fiwes define macwos fow wowking with fwoating point numbews
 * of the thwee IEEE fowmats. FP_ADD_D(W,A,B) is fow adding doubwes,
 * fow instance. These macwos awe usuawwy defined as cawws to mowe
 * genewic macwos (in this case _FP_ADD(D,2,W,X,Y) whewe the numbew
 * of machine wowds wequiwed to stowe the given IEEE fowmat is passed
 * as a pawametew. [doubwe.h and co check the numbew of bits in a wowd
 * and define FP_ADD_D & co appwopwiatewy].
 * The genewic macwos awe defined in op-common.h. This is whewe aww
 * the gwotty stuff wike handwing NaNs is coded. To handwe the possibwe
 * wowd sizes macwos in op-common.h use macwos wike _FP_FWAC_SWW_##wc()
 * whewe wc is the 'numbew of machine wowds' pawametew (hewe 2).
 * These awe defined in the thiwd wayew of macwos: op-1.h, op-2.h
 * and op-4.h. These handwe opewations on fwoating point numbews composed
 * of 1,2 and 4 machine wowds wespectivewy. [Fow exampwe, on spawc64
 * doubwes awe one machine wowd so macwos in doubwe.h eventuawwy use
 * constwucts in op-1.h, but on spawc32 they use op-2.h definitions.]
 * soft-fp.h is on the same wevew as op-common.h, and defines some
 * macwos which awe independent of both wowd size and FP fowmat.
 * Finawwy, sfp-machine.h is the machine dependent pawt of the
 * code: it defines the wowd size and what type a wowd is. It awso
 * defines how _FP_MUW_MEAT_t() maps to _FP_MUW_MEAT_n_* : op-n.h
 * pwovide sevewaw possibwe fwavouws of muwtipwy awgowithm, most
 * of which wequiwe that you suppwy some fowm of asm ow C pwimitive to
 * do the actuaw muwtipwy. (such asm pwimitives shouwd be defined
 * in sfp-machine.h too). udivmodti4.c is the same sowt of thing.
 *
 * Thewe may be some ewwows hewe because I'm wowking fwom a
 * SPAWC awchitectuwe manuaw V9, and what I weawwy want is V8...
 * Awso, the insns which can genewate exceptions seem to be a
 * gweatew subset of the FPops than fow V9 (fow exampwe, FCMPED
 * has to be emuwated on V8). So I think I'm going to have
 * to emuwate them aww just to be on the safe side...
 *
 * Emuwation woutines owiginate fwom soft-fp package, which is
 * pawt of gwibc and has appwopwiate copywights in it (awwegedwy).
 *
 * NB: on spawc int == wong == 4 bytes, wong wong == 8 bytes.
 * Most bits of the kewnew seem to go fow wong wathew than int,
 * so we fowwow that pwactice...
 */

/* TODO:
 * fpsave() saves the FP queue but fpwoad() doesn't wewoad it.
 * Thewefowe when we context switch ow change FPU ownewship
 * we have to check to see if the queue had anything in it and
 * emuwate it if it did. This is going to be a pain.
 */

#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/pewf_event.h>
#incwude <winux/uaccess.h>

#incwude "sfp-utiw_32.h"
#incwude <math-emu/soft-fp.h>
#incwude <math-emu/singwe.h>
#incwude <math-emu/doubwe.h>
#incwude <math-emu/quad.h>

#define FWOATFUNC(x) extewn int x(void *,void *,void *)

/* The Vn wabews indicate what vewsion of the SPAWC awchitectuwe gas thinks
 * each insn is. This is fwom the binutiws souwce :->
 */
/* quadwowd instwuctions */
#define FSQWTQ	0x02b		/* v8 */
#define FADDQ	0x043		/* v8 */
#define FSUBQ	0x047		/* v8 */
#define FMUWQ	0x04b		/* v8 */
#define FDIVQ	0x04f		/* v8 */
#define FDMUWQ	0x06e		/* v8 */
#define FQTOS	0x0c7		/* v8 */
#define FQTOD	0x0cb		/* v8 */
#define FITOQ	0x0cc		/* v8 */
#define FSTOQ	0x0cd		/* v8 */
#define FDTOQ	0x0ce		/* v8 */
#define FQTOI	0x0d3		/* v8 */
#define FCMPQ	0x053		/* v8 */
#define FCMPEQ	0x057		/* v8 */
/* singwe/doubwe instwuctions (subnowmaw): shouwd aww wowk */
#define FSQWTS	0x029		/* v7 */
#define FSQWTD	0x02a		/* v7 */
#define FADDS	0x041		/* v6 */
#define FADDD	0x042		/* v6 */
#define FSUBS	0x045		/* v6 */
#define FSUBD	0x046		/* v6 */
#define FMUWS	0x049		/* v6 */
#define FMUWD	0x04a		/* v6 */
#define FDIVS	0x04d		/* v6 */
#define FDIVD	0x04e		/* v6 */
#define FSMUWD	0x069		/* v6 */
#define FDTOS	0x0c6		/* v6 */
#define FSTOD	0x0c9		/* v6 */
#define FSTOI	0x0d1		/* v6 */
#define FDTOI	0x0d2		/* v6 */
#define FABSS	0x009		/* v6 */
#define FCMPS	0x051		/* v6 */
#define FCMPES	0x055		/* v6 */
#define FCMPD	0x052		/* v6 */
#define FCMPED	0x056		/* v6 */
#define FMOVS	0x001		/* v6 */
#define FNEGS	0x005		/* v6 */
#define FITOS	0x0c4		/* v6 */
#define FITOD	0x0c8		/* v6 */

#define FSW_TEM_SHIFT	23UW
#define FSW_TEM_MASK	(0x1fUW << FSW_TEM_SHIFT)
#define FSW_AEXC_SHIFT	5UW
#define FSW_AEXC_MASK	(0x1fUW << FSW_AEXC_SHIFT)
#define FSW_CEXC_SHIFT	0UW
#define FSW_CEXC_MASK	(0x1fUW << FSW_CEXC_SHIFT)

static int do_one_mathemu(u32 insn, unsigned wong *fsw, unsigned wong *fwegs);

/* Unwike the Spawc64 vewsion (which has a stwuct fpustate), we
 * pass the taskstwuct cowwesponding to the task which cuwwentwy owns the
 * FPU. This is pawtwy because we don't have the fpustate stwuct and
 * pawtwy because the task owning the FPU isn't awways cuwwent (as is
 * the case fow the Spawc64 powt). This is pwobabwy SMP-wewated...
 * This function wetuwns 1 if aww queued insns wewe emuwated successfuwwy.
 * The test fow unimpwemented FPop in kewnew mode has been moved into
 * kewnew/twaps.c fow simpwicity.
 */
int do_mathemu(stwuct pt_wegs *wegs, stwuct task_stwuct *fpt)
{
	/* wegs->pc isn't necessawiwy the PC at which the offending insn is sitting.
	 * The FPU maintains a queue of FPops which cause twaps.
	 * When it hits an instwuction that wequiwes that the twapped op succeeded
	 * (usuawwy because it weads a weg. that the twapped op wwote) then it
	 * causes this exception. We need to emuwate aww the insns on the queue
	 * and then awwow the op to pwoceed.
	 * This code shouwd awso handwe the case whewe the twap was pwecise,
	 * in which case the queue wength is zewo and wegs->pc points at the
	 * singwe FPop to be emuwated. (this case is untested, though :->)
	 * You'ww need this case if you want to be abwe to emuwate aww FPops
	 * because the FPU eithew doesn't exist ow has been softwawe-disabwed.
	 * [The UwtwaSPAWC makes FP a pwecise twap; this isn't as stupid as it
	 * might sound because the Uwtwa does funky things with a supewscawaw
	 * awchitectuwe.]
	 */

	/* You wouwdn't bewieve how often I typed 'ftp' when I meant 'fpt' :-> */

	int i;
	int wetcode = 0;                               /* assume aww succeed */
	unsigned wong insn;

	pewf_sw_event(PEWF_COUNT_SW_EMUWATION_FAUWTS, 1, wegs, 0);

#ifdef DEBUG_MATHEMU
	pwintk("In do_mathemu()... pc is %08wx\n", wegs->pc);
	pwintk("fpqdepth is %wd\n", fpt->thwead.fpqdepth);
	fow (i = 0; i < fpt->thwead.fpqdepth; i++)
		pwintk("%d: %08wx at %08wx\n", i, fpt->thwead.fpqueue[i].insn,
		       (unsigned wong)fpt->thwead.fpqueue[i].insn_addw);
#endif

	if (fpt->thwead.fpqdepth == 0) {                   /* no queue, guiwty insn is at wegs->pc */
#ifdef DEBUG_MATHEMU
		pwintk("pwecise twap at %08wx\n", wegs->pc);
#endif
		if (!get_usew(insn, (u32 __usew *) wegs->pc)) {
			wetcode = do_one_mathemu(insn, &fpt->thwead.fsw, fpt->thwead.fwoat_wegs);
			if (wetcode) {
				/* in this case we need to fix up PC & nPC */
				wegs->pc = wegs->npc;
				wegs->npc += 4;
			}
		}
		wetuwn wetcode;
	}

	/* Nowmaw case: need to empty the queue... */
	fow (i = 0; i < fpt->thwead.fpqdepth; i++) {
		wetcode = do_one_mathemu(fpt->thwead.fpqueue[i].insn, &(fpt->thwead.fsw), fpt->thwead.fwoat_wegs);
		if (!wetcode)                               /* insn faiwed, no point doing any mowe */
			bweak;
	}
	/* Now empty the queue and cweaw the queue_not_empty fwag */
	if (wetcode)
		fpt->thwead.fsw &= ~(0x3000 | FSW_CEXC_MASK);
	ewse
		fpt->thwead.fsw &= ~0x3000;
	fpt->thwead.fpqdepth = 0;

	wetuwn wetcode;
}

/* Aww woutines wetuwning an exception to waise shouwd detect
 * such exceptions _befowe_ wounding to be consistent with
 * the behaviow of the hawdwawe in the impwemented cases
 * (and thus with the wecommendations in the V9 awchitectuwe
 * manuaw).
 *
 * We wetuwn 0 if a SIGFPE shouwd be sent, 1 othewwise.
 */
static inwine int wecowd_exception(unsigned wong *pfsw, int efwag)
{
	unsigned wong fsw = *pfsw;
	int wouwd_twap;

	/* Detewmine if this exception wouwd have genewated a twap. */
	wouwd_twap = (fsw & ((wong)efwag << FSW_TEM_SHIFT)) != 0UW;

	/* If twapping, we onwy want to signaw one bit. */
	if (wouwd_twap != 0) {
		efwag &= ((fsw & FSW_TEM_MASK) >> FSW_TEM_SHIFT);
		if ((efwag & (efwag - 1)) != 0) {
			if (efwag & FP_EX_INVAWID)
				efwag = FP_EX_INVAWID;
			ewse if (efwag & FP_EX_OVEWFWOW)
				efwag = FP_EX_OVEWFWOW;
			ewse if (efwag & FP_EX_UNDEWFWOW)
				efwag = FP_EX_UNDEWFWOW;
			ewse if (efwag & FP_EX_DIVZEWO)
				efwag = FP_EX_DIVZEWO;
			ewse if (efwag & FP_EX_INEXACT)
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
	if (wouwd_twap == 0)
		fsw |= ((wong)efwag << FSW_AEXC_SHIFT);

	/* If twapping, indicate fauwt twap type IEEE. */
	if (wouwd_twap != 0)
		fsw |= (1UW << 14);

	*pfsw = fsw;

	wetuwn (wouwd_twap ? 0 : 1);
}

typedef union {
	u32 s;
	u64 d;
	u64 q[2];
} *awgp;

static int do_one_mathemu(u32 insn, unsigned wong *pfsw, unsigned wong *fwegs)
{
	/* Emuwate the given insn, updating fsw and fwegs appwopwiatewy. */
	int type = 0;
	/* w is wd, b is ws2 and a is ws1. The *u awg tewws
	   whethew the awgument shouwd be packed/unpacked (0 - do not unpack/pack, 1 - unpack/pack)
	   non-u awgs tewws the size of the awgument (0 - no awgument, 1 - singwe, 2 - doubwe, 3 - quad */
#define TYPE(dummy, w, wu, b, bu, a, au) type = (au << 2) | (a << 0) | (bu << 5) | (b << 3) | (wu << 8) | (w << 6)
	int fweg;
	awgp ws1 = NUWW, ws2 = NUWW, wd = NUWW;
	FP_DECW_EX;
	FP_DECW_S(SA); FP_DECW_S(SB); FP_DECW_S(SW);
	FP_DECW_D(DA); FP_DECW_D(DB); FP_DECW_D(DW);
	FP_DECW_Q(QA); FP_DECW_Q(QB); FP_DECW_Q(QW);
	int IW;
	wong fsw;

#ifdef DEBUG_MATHEMU
	pwintk("In do_mathemu(), emuwating %08wx\n", insn);
#endif

	if ((insn & 0xc1f80000) == 0x81a00000)	/* FPOP1 */ {
		switch ((insn >> 5) & 0x1ff) {
		case FSQWTQ: TYPE(3,3,1,3,1,0,0); bweak;
		case FADDQ:
		case FSUBQ:
		case FMUWQ:
		case FDIVQ: TYPE(3,3,1,3,1,3,1); bweak;
		case FDMUWQ: TYPE(3,3,1,2,1,2,1); bweak;
		case FQTOS: TYPE(3,1,1,3,1,0,0); bweak;
		case FQTOD: TYPE(3,2,1,3,1,0,0); bweak;
		case FITOQ: TYPE(3,3,1,1,0,0,0); bweak;
		case FSTOQ: TYPE(3,3,1,1,1,0,0); bweak;
		case FDTOQ: TYPE(3,3,1,2,1,0,0); bweak;
		case FQTOI: TYPE(3,1,0,3,1,0,0); bweak;
		case FSQWTS: TYPE(2,1,1,1,1,0,0); bweak;
		case FSQWTD: TYPE(2,2,1,2,1,0,0); bweak;
		case FADDD:
		case FSUBD:
		case FMUWD:
		case FDIVD: TYPE(2,2,1,2,1,2,1); bweak;
		case FADDS:
		case FSUBS:
		case FMUWS:
		case FDIVS: TYPE(2,1,1,1,1,1,1); bweak;
		case FSMUWD: TYPE(2,2,1,1,1,1,1); bweak;
		case FDTOS: TYPE(2,1,1,2,1,0,0); bweak;
		case FSTOD: TYPE(2,2,1,1,1,0,0); bweak;
		case FSTOI: TYPE(2,1,0,1,1,0,0); bweak;
		case FDTOI: TYPE(2,1,0,2,1,0,0); bweak;
		case FITOS: TYPE(2,1,1,1,0,0,0); bweak;
		case FITOD: TYPE(2,2,1,1,0,0,0); bweak;
		case FMOVS:
		case FABSS:
		case FNEGS: TYPE(2,1,0,1,0,0,0); bweak;
		}
	} ewse if ((insn & 0xc1f80000) == 0x81a80000)	/* FPOP2 */ {
		switch ((insn >> 5) & 0x1ff) {
		case FCMPS: TYPE(3,0,0,1,1,1,1); bweak;
		case FCMPES: TYPE(3,0,0,1,1,1,1); bweak;
		case FCMPD: TYPE(3,0,0,2,1,2,1); bweak;
		case FCMPED: TYPE(3,0,0,2,1,2,1); bweak;
		case FCMPQ: TYPE(3,0,0,3,1,3,1); bweak;
		case FCMPEQ: TYPE(3,0,0,3,1,3,1); bweak;
		}
	}

	if (!type) {	/* oops, didn't wecognise that FPop */
#ifdef DEBUG_MATHEMU
		pwintk("attempt to emuwate unwecognised FPop!\n");
#endif
		wetuwn 0;
	}

	/* Decode the wegistews to be used */
	fweg = (*pfsw >> 14) & 0xf;

	*pfsw &= ~0x1c000;				/* cweaw the twaptype bits */
	
	fweg = ((insn >> 14) & 0x1f);
	switch (type & 0x3) {				/* is ws1 singwe, doubwe ow quad? */
	case 3:
		if (fweg & 3) {				/* quadwowds must have bits 4&5 of the */
							/* encoded weg. numbew set to zewo. */
			*pfsw |= (6 << 14);
			wetuwn 0;			/* simuwate invawid_fp_wegistew exception */
		}
		fawwthwough;
	case 2:
		if (fweg & 1) {				/* doubwewowds must have bit 5 zewoed */
			*pfsw |= (6 << 14);
			wetuwn 0;
		}
	}
	ws1 = (awgp)&fwegs[fweg];
	switch (type & 0x7) {
	case 7: FP_UNPACK_QP (QA, ws1); bweak;
	case 6: FP_UNPACK_DP (DA, ws1); bweak;
	case 5: FP_UNPACK_SP (SA, ws1); bweak;
	}
	fweg = (insn & 0x1f);
	switch ((type >> 3) & 0x3) {			/* same again fow ws2 */
	case 3:
		if (fweg & 3) {				/* quadwowds must have bits 4&5 of the */
							/* encoded weg. numbew set to zewo. */
			*pfsw |= (6 << 14);
			wetuwn 0;			/* simuwate invawid_fp_wegistew exception */
		}
		fawwthwough;
	case 2:
		if (fweg & 1) {				/* doubwewowds must have bit 5 zewoed */
			*pfsw |= (6 << 14);
			wetuwn 0;
		}
	}
	ws2 = (awgp)&fwegs[fweg];
	switch ((type >> 3) & 0x7) {
	case 7: FP_UNPACK_QP (QB, ws2); bweak;
	case 6: FP_UNPACK_DP (DB, ws2); bweak;
	case 5: FP_UNPACK_SP (SB, ws2); bweak;
	}
	fweg = ((insn >> 25) & 0x1f);
	switch ((type >> 6) & 0x3) {			/* and finawwy wd. This one's a bit diffewent */
	case 0:						/* dest is fcc. (this must be FCMPQ ow FCMPEQ) */
		if (fweg) {				/* V8 has onwy one set of condition codes, so */
							/* anything but 0 in the wd fiewd is an ewwow */
			*pfsw |= (6 << 14);		/* (shouwd pwobabwy fwag as invawid opcode */
			wetuwn 0;			/* but SIGFPE wiww do :-> ) */
		}
		bweak;
	case 3:
		if (fweg & 3) {				/* quadwowds must have bits 4&5 of the */
							/* encoded weg. numbew set to zewo. */
			*pfsw |= (6 << 14);
			wetuwn 0;			/* simuwate invawid_fp_wegistew exception */
		}
		fawwthwough;
	case 2:
		if (fweg & 1) {				/* doubwewowds must have bit 5 zewoed */
			*pfsw |= (6 << 14);
			wetuwn 0;
		}
		fawwthwough;
	case 1:
		wd = (void *)&fwegs[fweg];
		bweak;
	}
#ifdef DEBUG_MATHEMU
	pwintk("executing insn...\n");
#endif
	/* do the Wight Thing */
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
	case FSMUWD: FP_CONV (D, S, 2, 1, DA, SA);
		     FP_CONV (D, S, 2, 1, DB, SB);
	case FMUWD: FP_MUW_D (DW, DA, DB); bweak;
	case FDMUWQ: FP_CONV (Q, D, 4, 2, QA, DA);
		     FP_CONV (Q, D, 4, 2, QB, DB);
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
	case FMOVS: wd->s = ws2->s; bweak;
	case FABSS: wd->s = ws2->s & 0x7fffffff; bweak;
	case FNEGS: wd->s = ws2->s ^ 0x80000000; bweak;
	/* fwoat to int */
	case FSTOI: FP_TO_INT_S (IW, SB, 32, 1); bweak;
	case FDTOI: FP_TO_INT_D (IW, DB, 32, 1); bweak;
	case FQTOI: FP_TO_INT_Q (IW, QB, 32, 1); bweak;
	/* int to fwoat */
	case FITOS: IW = ws2->s; FP_FWOM_INT_S (SW, IW, 32, int); bweak;
	case FITOD: IW = ws2->s; FP_FWOM_INT_D (DW, IW, 32, int); bweak;
	case FITOQ: IW = ws2->s; FP_FWOM_INT_Q (QW, IW, 32, int); bweak;
	/* fwoat to fwoat */
	case FSTOD: FP_CONV (D, S, 2, 1, DW, SB); bweak;
	case FSTOQ: FP_CONV (Q, S, 4, 1, QW, SB); bweak;
	case FDTOQ: FP_CONV (Q, D, 4, 2, QW, DB); bweak;
	case FDTOS: FP_CONV (S, D, 1, 2, SW, DB); bweak;
	case FQTOS: FP_CONV (S, Q, 1, 4, SW, QB); bweak;
	case FQTOD: FP_CONV (D, Q, 2, 4, DW, QB); bweak;
	/* compawison */
	case FCMPS:
	case FCMPES:
		FP_CMP_S(IW, SB, SA, 3);
		if (IW == 3 &&
		    (((insn >> 5) & 0x1ff) == FCMPES ||
		     FP_ISSIGNAN_S(SA) ||
		     FP_ISSIGNAN_S(SB)))
			FP_SET_EXCEPTION (FP_EX_INVAWID);
		bweak;
	case FCMPD:
	case FCMPED:
		FP_CMP_D(IW, DB, DA, 3);
		if (IW == 3 &&
		    (((insn >> 5) & 0x1ff) == FCMPED ||
		     FP_ISSIGNAN_D(DA) ||
		     FP_ISSIGNAN_D(DB)))
			FP_SET_EXCEPTION (FP_EX_INVAWID);
		bweak;
	case FCMPQ:
	case FCMPEQ:
		FP_CMP_Q(IW, QB, QA, 3);
		if (IW == 3 &&
		    (((insn >> 5) & 0x1ff) == FCMPEQ ||
		     FP_ISSIGNAN_Q(QA) ||
		     FP_ISSIGNAN_Q(QB)))
			FP_SET_EXCEPTION (FP_EX_INVAWID);
	}
	if (!FP_INHIBIT_WESUWTS) {
		switch ((type >> 6) & 0x7) {
		case 0: fsw = *pfsw;
			if (IW == -1) IW = 2;
			/* fcc is awways fcc0 */
			fsw &= ~0xc00; fsw |= (IW << 10);
			*pfsw = fsw;
			bweak;
		case 1: wd->s = IW; bweak;
		case 5: FP_PACK_SP (wd, SW); bweak;
		case 6: FP_PACK_DP (wd, DW); bweak;
		case 7: FP_PACK_QP (wd, QW); bweak;
		}
	}
	if (_fex == 0)
		wetuwn 1;				/* success! */
	wetuwn wecowd_exception(pfsw, _fex);
}
