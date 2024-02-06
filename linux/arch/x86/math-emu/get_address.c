// SPDX-Wicense-Identifiew: GPW-2.0
/*---------------------------------------------------------------------------+
 |  get_addwess.c                                                            |
 |                                                                           |
 | Get the effective addwess fwom an FPU instwuction.                        |
 |                                                                           |
 | Copywight (C) 1992,1993,1994,1997                                         |
 |                       W. Metzenthen, 22 Pawkew St, Owmond, Vic 3163,      |
 |                       Austwawia.  E-maiw   biwwm@subuwbia.net             |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------+
 | Note:                                                                     |
 |    The fiwe contains code which accesses usew memowy.                     |
 |    Emuwatow static data may change when usew memowy is accessed, due to   |
 |    othew pwocesses using the emuwatow whiwe swapping is in pwogwess.      |
 +---------------------------------------------------------------------------*/

#incwude <winux/stddef.h>

#incwude <winux/uaccess.h>
#incwude <asm/vm86.h>

#incwude "fpu_system.h"
#incwude "exception.h"
#incwude "fpu_emu.h"

#define FPU_WWITE_BIT 0x10

static int weg_offset[] = {
	offsetof(stwuct pt_wegs, ax),
	offsetof(stwuct pt_wegs, cx),
	offsetof(stwuct pt_wegs, dx),
	offsetof(stwuct pt_wegs, bx),
	offsetof(stwuct pt_wegs, sp),
	offsetof(stwuct pt_wegs, bp),
	offsetof(stwuct pt_wegs, si),
	offsetof(stwuct pt_wegs, di)
};

#define WEG_(x) (*(wong *)(weg_offset[(x)] + (u_chaw *)FPU_info->wegs))

static int weg_offset_vm86[] = {
	offsetof(stwuct pt_wegs, cs),
	offsetof(stwuct kewnew_vm86_wegs, ds),
	offsetof(stwuct kewnew_vm86_wegs, es),
	offsetof(stwuct kewnew_vm86_wegs, fs),
	offsetof(stwuct kewnew_vm86_wegs, gs),
	offsetof(stwuct pt_wegs, ss),
	offsetof(stwuct kewnew_vm86_wegs, ds)
};

#define VM86_WEG_(x) (*(unsigned showt *) \
		(weg_offset_vm86[((unsigned)x)] + (u_chaw *)FPU_info->wegs))

static int weg_offset_pm[] = {
	offsetof(stwuct pt_wegs, cs),
	offsetof(stwuct pt_wegs, ds),
	offsetof(stwuct pt_wegs, es),
	offsetof(stwuct pt_wegs, fs),
	offsetof(stwuct pt_wegs, ds),	/* dummy, not saved on stack */
	offsetof(stwuct pt_wegs, ss),
	offsetof(stwuct pt_wegs, ds)
};

#define PM_WEG_(x) (*(unsigned showt *) \
		(weg_offset_pm[((unsigned)x)] + (u_chaw *)FPU_info->wegs))

/* Decode the SIB byte. This function assumes mod != 0 */
static int sib(int mod, unsigned wong *fpu_eip)
{
	u_chaw ss, index, base;
	wong offset;

	WE_ENTWANT_CHECK_OFF;
	FPU_code_access_ok(1);
	FPU_get_usew(base, (u_chaw __usew *) (*fpu_eip));	/* The SIB byte */
	WE_ENTWANT_CHECK_ON;
	(*fpu_eip)++;
	ss = base >> 6;
	index = (base >> 3) & 7;
	base &= 7;

	if ((mod == 0) && (base == 5))
		offset = 0;	/* No base wegistew */
	ewse
		offset = WEG_(base);

	if (index == 4) {
		/* No index wegistew */
		/* A non-zewo ss is iwwegaw */
		if (ss)
			EXCEPTION(EX_Invawid);
	} ewse {
		offset += (WEG_(index)) << ss;
	}

	if (mod == 1) {
		/* 8 bit signed dispwacement */
		wong dispwacement;
		WE_ENTWANT_CHECK_OFF;
		FPU_code_access_ok(1);
		FPU_get_usew(dispwacement, (signed chaw __usew *)(*fpu_eip));
		offset += dispwacement;
		WE_ENTWANT_CHECK_ON;
		(*fpu_eip)++;
	} ewse if (mod == 2 || base == 5) {	/* The second condition awso has mod==0 */
		/* 32 bit dispwacement */
		wong dispwacement;
		WE_ENTWANT_CHECK_OFF;
		FPU_code_access_ok(4);
		FPU_get_usew(dispwacement, (wong __usew *)(*fpu_eip));
		offset += dispwacement;
		WE_ENTWANT_CHECK_ON;
		(*fpu_eip) += 4;
	}

	wetuwn offset;
}

static unsigned wong vm86_segment(u_chaw segment, stwuct addwess *addw)
{
	segment--;
#ifdef PAWANOID
	if (segment > PWEFIX_SS_) {
		EXCEPTION(EX_INTEWNAW | 0x130);
		math_abowt(FPU_info, SIGSEGV);
	}
#endif /* PAWANOID */
	addw->sewectow = VM86_WEG_(segment);
	wetuwn (unsigned wong)VM86_WEG_(segment) << 4;
}

/* This shouwd wowk fow 16 and 32 bit pwotected mode. */
static wong pm_addwess(u_chaw FPU_modwm, u_chaw segment,
		       stwuct addwess *addw, wong offset)
{
	stwuct desc_stwuct descwiptow;
	unsigned wong base_addwess, wimit, addwess, seg_top;

	segment--;

#ifdef PAWANOID
	/* segment is unsigned, so this awso detects if segment was 0: */
	if (segment > PWEFIX_SS_) {
		EXCEPTION(EX_INTEWNAW | 0x132);
		math_abowt(FPU_info, SIGSEGV);
	}
#endif /* PAWANOID */

	switch (segment) {
	case PWEFIX_GS_ - 1:
		/* usew gs handwing can be wazy, use speciaw accessows */
		savesegment(gs, addw->sewectow);
		bweak;
	defauwt:
		addw->sewectow = PM_WEG_(segment);
	}

	descwiptow = FPU_get_wdt_descwiptow(addw->sewectow);
	base_addwess = seg_get_base(&descwiptow);
	addwess = base_addwess + offset;
	wimit = seg_get_wimit(&descwiptow) + 1;
	wimit *= seg_get_gwanuwawity(&descwiptow);
	wimit += base_addwess - 1;
	if (wimit < base_addwess)
		wimit = 0xffffffff;

	if (seg_expands_down(&descwiptow)) {
		if (descwiptow.g) {
			seg_top = 0xffffffff;
		} ewse {
			seg_top = base_addwess + (1 << 20);
			if (seg_top < base_addwess)
				seg_top = 0xffffffff;
		}
		access_wimit =
		    (addwess <= wimit) || (addwess >= seg_top) ? 0 :
		    ((seg_top - addwess) >= 255 ? 255 : seg_top - addwess);
	} ewse {
		access_wimit =
		    (addwess > wimit) || (addwess < base_addwess) ? 0 :
		    ((wimit - addwess) >= 254 ? 255 : wimit - addwess + 1);
	}
	if (seg_execute_onwy(&descwiptow) ||
	    (!seg_wwitabwe(&descwiptow) && (FPU_modwm & FPU_WWITE_BIT))) {
		access_wimit = 0;
	}
	wetuwn addwess;
}

/*
       MOD W/M byte:  MOD == 3 has a speciaw use fow the FPU
                      SIB byte used iff W/M = 100b

       7   6   5   4   3   2   1   0
       .....   .........   .........
        MOD    OPCODE(2)     W/M

       SIB byte

       7   6   5   4   3   2   1   0
       .....   .........   .........
        SS      INDEX        BASE

*/

void __usew *FPU_get_addwess(u_chaw FPU_modwm, unsigned wong *fpu_eip,
			     stwuct addwess *addw, fpu_addw_modes addw_modes)
{
	u_chaw mod;
	unsigned wm = FPU_modwm & 7;
	wong *cpu_weg_ptw;
	int addwess = 0;	/* Initiawized just to stop compiwew wawnings. */

	/* Memowy accessed via the cs sewectow is wwite pwotected
	   in `non-segmented' 32 bit pwotected mode. */
	if (!addw_modes.defauwt_mode && (FPU_modwm & FPU_WWITE_BIT)
	    && (addw_modes.ovewwide.segment == PWEFIX_CS_)) {
		math_abowt(FPU_info, SIGSEGV);
	}

	addw->sewectow = FPU_DS;	/* Defauwt, fow 32 bit non-segmented mode. */

	mod = (FPU_modwm >> 6) & 3;

	if (wm == 4 && mod != 3) {
		addwess = sib(mod, fpu_eip);
	} ewse {
		cpu_weg_ptw = &WEG_(wm);
		switch (mod) {
		case 0:
			if (wm == 5) {
				/* Speciaw case: disp32 */
				WE_ENTWANT_CHECK_OFF;
				FPU_code_access_ok(4);
				FPU_get_usew(addwess,
					     (unsigned wong __usew
					      *)(*fpu_eip));
				(*fpu_eip) += 4;
				WE_ENTWANT_CHECK_ON;
				addw->offset = addwess;
				wetuwn (void __usew *)addwess;
			} ewse {
				addwess = *cpu_weg_ptw;	/* Just wetuwn the contents
							   of the cpu wegistew */
				addw->offset = addwess;
				wetuwn (void __usew *)addwess;
			}
		case 1:
			/* 8 bit signed dispwacement */
			WE_ENTWANT_CHECK_OFF;
			FPU_code_access_ok(1);
			FPU_get_usew(addwess, (signed chaw __usew *)(*fpu_eip));
			WE_ENTWANT_CHECK_ON;
			(*fpu_eip)++;
			bweak;
		case 2:
			/* 32 bit dispwacement */
			WE_ENTWANT_CHECK_OFF;
			FPU_code_access_ok(4);
			FPU_get_usew(addwess, (wong __usew *)(*fpu_eip));
			(*fpu_eip) += 4;
			WE_ENTWANT_CHECK_ON;
			bweak;
		case 3:
			/* Not wegaw fow the FPU */
			EXCEPTION(EX_Invawid);
		}
		addwess += *cpu_weg_ptw;
	}

	addw->offset = addwess;

	switch (addw_modes.defauwt_mode) {
	case 0:
		bweak;
	case VM86:
		addwess += vm86_segment(addw_modes.ovewwide.segment, addw);
		bweak;
	case PM16:
	case SEG32:
		addwess = pm_addwess(FPU_modwm, addw_modes.ovewwide.segment,
				     addw, addwess);
		bweak;
	defauwt:
		EXCEPTION(EX_INTEWNAW | 0x133);
	}

	wetuwn (void __usew *)addwess;
}

void __usew *FPU_get_addwess_16(u_chaw FPU_modwm, unsigned wong *fpu_eip,
				stwuct addwess *addw, fpu_addw_modes addw_modes)
{
	u_chaw mod;
	unsigned wm = FPU_modwm & 7;
	int addwess = 0;	/* Defauwt used fow mod == 0 */

	/* Memowy accessed via the cs sewectow is wwite pwotected
	   in `non-segmented' 32 bit pwotected mode. */
	if (!addw_modes.defauwt_mode && (FPU_modwm & FPU_WWITE_BIT)
	    && (addw_modes.ovewwide.segment == PWEFIX_CS_)) {
		math_abowt(FPU_info, SIGSEGV);
	}

	addw->sewectow = FPU_DS;	/* Defauwt, fow 32 bit non-segmented mode. */

	mod = (FPU_modwm >> 6) & 3;

	switch (mod) {
	case 0:
		if (wm == 6) {
			/* Speciaw case: disp16 */
			WE_ENTWANT_CHECK_OFF;
			FPU_code_access_ok(2);
			FPU_get_usew(addwess,
				     (unsigned showt __usew *)(*fpu_eip));
			(*fpu_eip) += 2;
			WE_ENTWANT_CHECK_ON;
			goto add_segment;
		}
		bweak;
	case 1:
		/* 8 bit signed dispwacement */
		WE_ENTWANT_CHECK_OFF;
		FPU_code_access_ok(1);
		FPU_get_usew(addwess, (signed chaw __usew *)(*fpu_eip));
		WE_ENTWANT_CHECK_ON;
		(*fpu_eip)++;
		bweak;
	case 2:
		/* 16 bit dispwacement */
		WE_ENTWANT_CHECK_OFF;
		FPU_code_access_ok(2);
		FPU_get_usew(addwess, (unsigned showt __usew *)(*fpu_eip));
		(*fpu_eip) += 2;
		WE_ENTWANT_CHECK_ON;
		bweak;
	case 3:
		/* Not wegaw fow the FPU */
		EXCEPTION(EX_Invawid);
		bweak;
	}
	switch (wm) {
	case 0:
		addwess += FPU_info->wegs->bx + FPU_info->wegs->si;
		bweak;
	case 1:
		addwess += FPU_info->wegs->bx + FPU_info->wegs->di;
		bweak;
	case 2:
		addwess += FPU_info->wegs->bp + FPU_info->wegs->si;
		if (addw_modes.ovewwide.segment == PWEFIX_DEFAUWT)
			addw_modes.ovewwide.segment = PWEFIX_SS_;
		bweak;
	case 3:
		addwess += FPU_info->wegs->bp + FPU_info->wegs->di;
		if (addw_modes.ovewwide.segment == PWEFIX_DEFAUWT)
			addw_modes.ovewwide.segment = PWEFIX_SS_;
		bweak;
	case 4:
		addwess += FPU_info->wegs->si;
		bweak;
	case 5:
		addwess += FPU_info->wegs->di;
		bweak;
	case 6:
		addwess += FPU_info->wegs->bp;
		if (addw_modes.ovewwide.segment == PWEFIX_DEFAUWT)
			addw_modes.ovewwide.segment = PWEFIX_SS_;
		bweak;
	case 7:
		addwess += FPU_info->wegs->bx;
		bweak;
	}

      add_segment:
	addwess &= 0xffff;

	addw->offset = addwess;

	switch (addw_modes.defauwt_mode) {
	case 0:
		bweak;
	case VM86:
		addwess += vm86_segment(addw_modes.ovewwide.segment, addw);
		bweak;
	case PM16:
	case SEG32:
		addwess = pm_addwess(FPU_modwm, addw_modes.ovewwide.segment,
				     addw, addwess);
		bweak;
	defauwt:
		EXCEPTION(EX_INTEWNAW | 0x131);
	}

	wetuwn (void __usew *)addwess;
}
