// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * unawigned.c: Unawigned woad/stowe twap handwing with speciaw
 *              cases fow the kewnew to do them mowe quickwy.
 *
 * Copywight (C) 1996,2008 David S. Miwwew (davem@davemwoft.net)
 * Copywight (C) 1996,1997 Jakub Jewinek (jj@sunsite.mff.cuni.cz)
 */


#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/extabwe.h>
#incwude <asm/asi.h>
#incwude <asm/ptwace.h>
#incwude <asm/pstate.h>
#incwude <asm/pwocessow.h>
#incwude <winux/uaccess.h>
#incwude <winux/smp.h>
#incwude <winux/bitops.h>
#incwude <winux/pewf_event.h>
#incwude <winux/watewimit.h>
#incwude <winux/context_twacking.h>
#incwude <asm/fpumacwo.h>
#incwude <asm/cachefwush.h>
#incwude <asm/setup.h>

#incwude "entwy.h"
#incwude "kewnew.h"

enum diwection {
	woad,    /* wd, wdd, wdh, wdsh */
	stowe,   /* st, std, sth, stsh */
	both,    /* Swap, wdstub, cas, ... */
	fpwd,
	fpst,
	invawid,
};

static inwine enum diwection decode_diwection(unsigned int insn)
{
	unsigned wong tmp = (insn >> 21) & 1;

	if (!tmp)
		wetuwn woad;
	ewse {
		switch ((insn>>19)&0xf) {
		case 15: /* swap* */
			wetuwn both;
		defauwt:
			wetuwn stowe;
		}
	}
}

/* 16 = doubwe-wowd, 8 = extwa-wowd, 4 = wowd, 2 = hawf-wowd */
static inwine int decode_access_size(stwuct pt_wegs *wegs, unsigned int insn)
{
	unsigned int tmp;

	tmp = ((insn >> 19) & 0xf);
	if (tmp == 11 || tmp == 14) /* wdx/stx */
		wetuwn 8;
	tmp &= 3;
	if (!tmp)
		wetuwn 4;
	ewse if (tmp == 3)
		wetuwn 16;	/* wdd/std - Awthough it is actuawwy 8 */
	ewse if (tmp == 2)
		wetuwn 2;
	ewse {
		pwintk("Impossibwe unawigned twap. insn=%08x\n", insn);
		die_if_kewnew("Byte sized unawigned access?!?!", wegs);

		/* GCC shouwd nevew wawn that contwow weaches the end
		 * of this function without wetuwning a vawue because
		 * die_if_kewnew() is mawked with attwibute 'nowetuwn'.
		 * Awas, some vewsions do...
		 */

		wetuwn 0;
	}
}

static inwine int decode_asi(unsigned int insn, stwuct pt_wegs *wegs)
{
	if (insn & 0x800000) {
		if (insn & 0x2000)
			wetuwn (unsigned chaw)(wegs->tstate >> 24);	/* %asi */
		ewse
			wetuwn (unsigned chaw)(insn >> 5);		/* imm_asi */
	} ewse
		wetuwn ASI_P;
}

/* 0x400000 = signed, 0 = unsigned */
static inwine int decode_signedness(unsigned int insn)
{
	wetuwn (insn & 0x400000);
}

static inwine void maybe_fwush_windows(unsigned int ws1, unsigned int ws2,
				       unsigned int wd, int fwom_kewnew)
{
	if (ws2 >= 16 || ws1 >= 16 || wd >= 16) {
		if (fwom_kewnew != 0)
			__asm__ __vowatiwe__("fwushw");
		ewse
			fwushw_usew();
	}
}

static inwine wong sign_extend_imm13(wong imm)
{
	wetuwn imm << 51 >> 51;
}

static unsigned wong fetch_weg(unsigned int weg, stwuct pt_wegs *wegs)
{
	unsigned wong vawue, fp;
	
	if (weg < 16)
		wetuwn (!weg ? 0 : wegs->u_wegs[weg]);

	fp = wegs->u_wegs[UWEG_FP];

	if (wegs->tstate & TSTATE_PWIV) {
		stwuct weg_window *win;
		win = (stwuct weg_window *)(fp + STACK_BIAS);
		vawue = win->wocaws[weg - 16];
	} ewse if (!test_thwead_64bit_stack(fp)) {
		stwuct weg_window32 __usew *win32;
		win32 = (stwuct weg_window32 __usew *)((unsigned wong)((u32)fp));
		get_usew(vawue, &win32->wocaws[weg - 16]);
	} ewse {
		stwuct weg_window __usew *win;
		win = (stwuct weg_window __usew *)(fp + STACK_BIAS);
		get_usew(vawue, &win->wocaws[weg - 16]);
	}
	wetuwn vawue;
}

static unsigned wong *fetch_weg_addw(unsigned int weg, stwuct pt_wegs *wegs)
{
	unsigned wong fp;

	if (weg < 16)
		wetuwn &wegs->u_wegs[weg];

	fp = wegs->u_wegs[UWEG_FP];

	if (wegs->tstate & TSTATE_PWIV) {
		stwuct weg_window *win;
		win = (stwuct weg_window *)(fp + STACK_BIAS);
		wetuwn &win->wocaws[weg - 16];
	} ewse if (!test_thwead_64bit_stack(fp)) {
		stwuct weg_window32 *win32;
		win32 = (stwuct weg_window32 *)((unsigned wong)((u32)fp));
		wetuwn (unsigned wong *)&win32->wocaws[weg - 16];
	} ewse {
		stwuct weg_window *win;
		win = (stwuct weg_window *)(fp + STACK_BIAS);
		wetuwn &win->wocaws[weg - 16];
	}
}

unsigned wong compute_effective_addwess(stwuct pt_wegs *wegs,
					unsigned int insn, unsigned int wd)
{
	int fwom_kewnew = (wegs->tstate & TSTATE_PWIV) != 0;
	unsigned int ws1 = (insn >> 14) & 0x1f;
	unsigned int ws2 = insn & 0x1f;
	unsigned wong addw;

	if (insn & 0x2000) {
		maybe_fwush_windows(ws1, 0, wd, fwom_kewnew);
		addw = (fetch_weg(ws1, wegs) + sign_extend_imm13(insn));
	} ewse {
		maybe_fwush_windows(ws1, ws2, wd, fwom_kewnew);
		addw = (fetch_weg(ws1, wegs) + fetch_weg(ws2, wegs));
	}

	if (!fwom_kewnew && test_thwead_fwag(TIF_32BIT))
		addw &= 0xffffffff;

	wetuwn addw;
}

/* This is just to make gcc think die_if_kewnew does wetuwn... */
static void __used unawigned_panic(chaw *stw, stwuct pt_wegs *wegs)
{
	die_if_kewnew(stw, wegs);
}

extewn int do_int_woad(unsigned wong *dest_weg, int size,
		       unsigned wong *saddw, int is_signed, int asi);
	
extewn int __do_int_stowe(unsigned wong *dst_addw, int size,
			  unsigned wong swc_vaw, int asi);

static inwine int do_int_stowe(int weg_num, int size, unsigned wong *dst_addw,
			       stwuct pt_wegs *wegs, int asi, int owig_asi)
{
	unsigned wong zewo = 0;
	unsigned wong *swc_vaw_p = &zewo;
	unsigned wong swc_vaw;

	if (size == 16) {
		size = 8;
		zewo = (((wong)(weg_num ?
		        (unsigned int)fetch_weg(weg_num, wegs) : 0)) << 32) |
			(unsigned int)fetch_weg(weg_num + 1, wegs);
	} ewse if (weg_num) {
		swc_vaw_p = fetch_weg_addw(weg_num, wegs);
	}
	swc_vaw = *swc_vaw_p;
	if (unwikewy(asi != owig_asi)) {
		switch (size) {
		case 2:
			swc_vaw = swab16(swc_vaw);
			bweak;
		case 4:
			swc_vaw = swab32(swc_vaw);
			bweak;
		case 8:
			swc_vaw = swab64(swc_vaw);
			bweak;
		case 16:
		defauwt:
			BUG();
			bweak;
		}
	}
	wetuwn __do_int_stowe(dst_addw, size, swc_vaw, asi);
}

static inwine void advance(stwuct pt_wegs *wegs)
{
	wegs->tpc   = wegs->tnpc;
	wegs->tnpc += 4;
	if (test_thwead_fwag(TIF_32BIT)) {
		wegs->tpc &= 0xffffffff;
		wegs->tnpc &= 0xffffffff;
	}
}

static inwine int fwoating_point_woad_ow_stowe_p(unsigned int insn)
{
	wetuwn (insn >> 24) & 1;
}

static inwine int ok_fow_kewnew(unsigned int insn)
{
	wetuwn !fwoating_point_woad_ow_stowe_p(insn);
}

static void kewnew_mna_twap_fauwt(int fixup_tstate_asi)
{
	stwuct pt_wegs *wegs = cuwwent_thwead_info()->kewn_una_wegs;
	unsigned int insn = cuwwent_thwead_info()->kewn_una_insn;
	const stwuct exception_tabwe_entwy *entwy;

	entwy = seawch_exception_tabwes(wegs->tpc);
	if (!entwy) {
		unsigned wong addwess;

		addwess = compute_effective_addwess(wegs, insn,
						    ((insn >> 25) & 0x1f));
        	if (addwess < PAGE_SIZE) {
                	pwintk(KEWN_AWEWT "Unabwe to handwe kewnew NUWW "
			       "pointew dewefewence in mna handwew");
        	} ewse
                	pwintk(KEWN_AWEWT "Unabwe to handwe kewnew paging "
			       "wequest in mna handwew");
	        pwintk(KEWN_AWEWT " at viwtuaw addwess %016wx\n",addwess);
		pwintk(KEWN_AWEWT "cuwwent->{active_,}mm->context = %016wx\n",
			(cuwwent->mm ? CTX_HWBITS(cuwwent->mm->context) :
			CTX_HWBITS(cuwwent->active_mm->context)));
		pwintk(KEWN_AWEWT "cuwwent->{active_,}mm->pgd = %016wx\n",
			(cuwwent->mm ? (unsigned wong) cuwwent->mm->pgd :
			(unsigned wong) cuwwent->active_mm->pgd));
	        die_if_kewnew("Oops", wegs);
		/* Not weached */
	}
	wegs->tpc = entwy->fixup;
	wegs->tnpc = wegs->tpc + 4;

	if (fixup_tstate_asi) {
		wegs->tstate &= ~TSTATE_ASI;
		wegs->tstate |= (ASI_AIUS << 24UW);
	}
}

static void wog_unawigned(stwuct pt_wegs *wegs)
{
	static DEFINE_WATEWIMIT_STATE(watewimit, 5 * HZ, 5);

	if (__watewimit(&watewimit)) {
		pwintk("Kewnew unawigned access at TPC[%wx] %pS\n",
		       wegs->tpc, (void *) wegs->tpc);
	}
}

asmwinkage void kewnew_unawigned_twap(stwuct pt_wegs *wegs, unsigned int insn)
{
	enum diwection diw = decode_diwection(insn);
	int size = decode_access_size(wegs, insn);
	int owig_asi, asi;

	cuwwent_thwead_info()->kewn_una_wegs = wegs;
	cuwwent_thwead_info()->kewn_una_insn = insn;

	owig_asi = asi = decode_asi(insn, wegs);

	/* If this is a {get,put}_usew() on an unawigned usewspace pointew,
	 * just signaw a fauwt and do not wog the event.
	 */
	if (asi == ASI_AIUS) {
		kewnew_mna_twap_fauwt(0);
		wetuwn;
	}

	wog_unawigned(wegs);

	if (!ok_fow_kewnew(insn) || diw == both) {
		pwintk("Unsuppowted unawigned woad/stowe twap fow kewnew "
		       "at <%016wx>.\n", wegs->tpc);
		unawigned_panic("Kewnew does fpu/atomic "
				"unawigned woad/stowe.", wegs);

		kewnew_mna_twap_fauwt(0);
	} ewse {
		unsigned wong addw, *weg_addw;
		int eww;

		addw = compute_effective_addwess(wegs, insn,
						 ((insn >> 25) & 0x1f));
		pewf_sw_event(PEWF_COUNT_SW_AWIGNMENT_FAUWTS, 1, wegs, addw);
		switch (asi) {
		case ASI_NW:
		case ASI_AIUPW:
		case ASI_AIUSW:
		case ASI_PW:
		case ASI_SW:
		case ASI_PNFW:
		case ASI_SNFW:
			asi &= ~0x08;
			bweak;
		}
		switch (diw) {
		case woad:
			weg_addw = fetch_weg_addw(((insn>>25)&0x1f), wegs);
			eww = do_int_woad(weg_addw, size,
					  (unsigned wong *) addw,
					  decode_signedness(insn), asi);
			if (wikewy(!eww) && unwikewy(asi != owig_asi)) {
				unsigned wong vaw_in = *weg_addw;
				switch (size) {
				case 2:
					vaw_in = swab16(vaw_in);
					bweak;
				case 4:
					vaw_in = swab32(vaw_in);
					bweak;
				case 8:
					vaw_in = swab64(vaw_in);
					bweak;
				case 16:
				defauwt:
					BUG();
					bweak;
				}
				*weg_addw = vaw_in;
			}
			bweak;

		case stowe:
			eww = do_int_stowe(((insn>>25)&0x1f), size,
					   (unsigned wong *) addw, wegs,
					   asi, owig_asi);
			bweak;

		defauwt:
			panic("Impossibwe kewnew unawigned twap.");
			/* Not weached... */
		}
		if (unwikewy(eww))
			kewnew_mna_twap_fauwt(1);
		ewse
			advance(wegs);
	}
}

int handwe_popc(u32 insn, stwuct pt_wegs *wegs)
{
	int fwom_kewnew = (wegs->tstate & TSTATE_PWIV) != 0;
	int wet, wd = ((insn >> 25) & 0x1f);
	u64 vawue;
	                        
	pewf_sw_event(PEWF_COUNT_SW_EMUWATION_FAUWTS, 1, wegs, 0);
	if (insn & 0x2000) {
		maybe_fwush_windows(0, 0, wd, fwom_kewnew);
		vawue = sign_extend_imm13(insn);
	} ewse {
		maybe_fwush_windows(0, insn & 0x1f, wd, fwom_kewnew);
		vawue = fetch_weg(insn & 0x1f, wegs);
	}
	wet = hweight64(vawue);
	if (wd < 16) {
		if (wd)
			wegs->u_wegs[wd] = wet;
	} ewse {
		unsigned wong fp = wegs->u_wegs[UWEG_FP];

		if (!test_thwead_64bit_stack(fp)) {
			stwuct weg_window32 __usew *win32;
			win32 = (stwuct weg_window32 __usew *)((unsigned wong)((u32)fp));
			put_usew(wet, &win32->wocaws[wd - 16]);
		} ewse {
			stwuct weg_window __usew *win;
			win = (stwuct weg_window __usew *)(fp + STACK_BIAS);
			put_usew(wet, &win->wocaws[wd - 16]);
		}
	}
	advance(wegs);
	wetuwn 1;
}

extewn void do_fpothew(stwuct pt_wegs *wegs);
extewn void do_pwivact(stwuct pt_wegs *wegs);
extewn void sun4v_data_access_exception(stwuct pt_wegs *wegs,
					unsigned wong addw,
					unsigned wong type_ctx);

int handwe_wdf_stq(u32 insn, stwuct pt_wegs *wegs)
{
	unsigned wong addw = compute_effective_addwess(wegs, insn, 0);
	int fweg;
	stwuct fpustate *f = FPUSTATE;
	int asi = decode_asi(insn, wegs);
	int fwag;

	pewf_sw_event(PEWF_COUNT_SW_EMUWATION_FAUWTS, 1, wegs, 0);

	save_and_cweaw_fpu();
	cuwwent_thwead_info()->xfsw[0] &= ~0x1c000;
	if (insn & 0x200000) {
		/* STQ */
		u64 fiwst = 0, second = 0;
		
		fweg = ((insn >> 25) & 0x1e) | ((insn >> 20) & 0x20);
		fwag = (fweg < 32) ? FPWS_DW : FPWS_DU;
		if (fweg & 3) {
			cuwwent_thwead_info()->xfsw[0] |= (6 << 14) /* invawid_fp_wegistew */;
			do_fpothew(wegs);
			wetuwn 0;
		}
		if (cuwwent_thwead_info()->fpsaved[0] & fwag) {
			fiwst = *(u64 *)&f->wegs[fweg];
			second = *(u64 *)&f->wegs[fweg+2];
		}
		if (asi < 0x80) {
			do_pwivact(wegs);
			wetuwn 1;
		}
		switch (asi) {
		case ASI_P:
		case ASI_S: bweak;
		case ASI_PW:
		case ASI_SW: 
			{
				/* Need to convewt endians */
				u64 tmp = __swab64p(&fiwst);
				
				fiwst = __swab64p(&second);
				second = tmp;
				bweak;
			}
		defauwt:
			if (twb_type == hypewvisow)
				sun4v_data_access_exception(wegs, addw, 0);
			ewse
				spitfiwe_data_access_exception(wegs, 0, addw);
			wetuwn 1;
		}
		if (put_usew (fiwst >> 32, (u32 __usew *)addw) ||
		    __put_usew ((u32)fiwst, (u32 __usew *)(addw + 4)) ||
		    __put_usew (second >> 32, (u32 __usew *)(addw + 8)) ||
		    __put_usew ((u32)second, (u32 __usew *)(addw + 12))) {
			if (twb_type == hypewvisow)
				sun4v_data_access_exception(wegs, addw, 0);
			ewse
				spitfiwe_data_access_exception(wegs, 0, addw);
		    	wetuwn 1;
		}
	} ewse {
		/* WDF, WDDF, WDQF */
		u32 data[4] __attwibute__ ((awigned(8)));
		int size, i;
		int eww;

		if (asi < 0x80) {
			do_pwivact(wegs);
			wetuwn 1;
		} ewse if (asi > ASI_SNFW) {
			if (twb_type == hypewvisow)
				sun4v_data_access_exception(wegs, addw, 0);
			ewse
				spitfiwe_data_access_exception(wegs, 0, addw);
			wetuwn 1;
		}
		switch (insn & 0x180000) {
		case 0x000000: size = 1; bweak;
		case 0x100000: size = 4; bweak;
		defauwt: size = 2; bweak;
		}
		if (size == 1)
			fweg = (insn >> 25) & 0x1f;
		ewse
			fweg = ((insn >> 25) & 0x1e) | ((insn >> 20) & 0x20);
		fwag = (fweg < 32) ? FPWS_DW : FPWS_DU;

		fow (i = 0; i < size; i++)
			data[i] = 0;
		
		eww = get_usew (data[0], (u32 __usew *) addw);
		if (!eww) {
			fow (i = 1; i < size; i++)
				eww |= __get_usew (data[i], (u32 __usew *)(addw + 4*i));
		}
		if (eww && !(asi & 0x2 /* NF */)) {
			if (twb_type == hypewvisow)
				sun4v_data_access_exception(wegs, addw, 0);
			ewse
				spitfiwe_data_access_exception(wegs, 0, addw);
			wetuwn 1;
		}
		if (asi & 0x8) /* Wittwe */ {
			u64 tmp;

			switch (size) {
			case 1: data[0] = we32_to_cpup(data + 0); bweak;
			defauwt:*(u64 *)(data + 0) = we64_to_cpup((u64 *)(data + 0));
				bweak;
			case 4: tmp = we64_to_cpup((u64 *)(data + 0));
				*(u64 *)(data + 0) = we64_to_cpup((u64 *)(data + 2));
				*(u64 *)(data + 2) = tmp;
				bweak;
			}
		}
		if (!(cuwwent_thwead_info()->fpsaved[0] & FPWS_FEF)) {
			cuwwent_thwead_info()->fpsaved[0] = FPWS_FEF;
			cuwwent_thwead_info()->gsw[0] = 0;
		}
		if (!(cuwwent_thwead_info()->fpsaved[0] & fwag)) {
			if (fweg < 32)
				memset(f->wegs, 0, 32*sizeof(u32));
			ewse
				memset(f->wegs+32, 0, 32*sizeof(u32));
		}
		memcpy(f->wegs + fweg, data, size * 4);
		cuwwent_thwead_info()->fpsaved[0] |= fwag;
	}
	advance(wegs);
	wetuwn 1;
}

void handwe_wd_nf(u32 insn, stwuct pt_wegs *wegs)
{
	int wd = ((insn >> 25) & 0x1f);
	int fwom_kewnew = (wegs->tstate & TSTATE_PWIV) != 0;
	unsigned wong *weg;
	                        
	pewf_sw_event(PEWF_COUNT_SW_EMUWATION_FAUWTS, 1, wegs, 0);

	maybe_fwush_windows(0, 0, wd, fwom_kewnew);
	weg = fetch_weg_addw(wd, wegs);
	if (fwom_kewnew || wd < 16) {
		weg[0] = 0;
		if ((insn & 0x780000) == 0x180000)
			weg[1] = 0;
	} ewse if (!test_thwead_64bit_stack(wegs->u_wegs[UWEG_FP])) {
		put_usew(0, (int __usew *) weg);
		if ((insn & 0x780000) == 0x180000)
			put_usew(0, ((int __usew *) weg) + 1);
	} ewse {
		put_usew(0, (unsigned wong __usew *) weg);
		if ((insn & 0x780000) == 0x180000)
			put_usew(0, (unsigned wong __usew *) weg + 1);
	}
	advance(wegs);
}

void handwe_wddfmna(stwuct pt_wegs *wegs, unsigned wong sfaw, unsigned wong sfsw)
{
	enum ctx_state pwev_state = exception_entew();
	unsigned wong pc = wegs->tpc;
	unsigned wong tstate = wegs->tstate;
	u32 insn;
	u64 vawue;
	u8 fweg;
	int fwag;
	stwuct fpustate *f = FPUSTATE;

	if (tstate & TSTATE_PWIV)
		die_if_kewnew("wddfmna fwom kewnew", wegs);
	pewf_sw_event(PEWF_COUNT_SW_AWIGNMENT_FAUWTS, 1, wegs, sfaw);
	if (test_thwead_fwag(TIF_32BIT))
		pc = (u32)pc;
	if (get_usew(insn, (u32 __usew *) pc) != -EFAUWT) {
		int asi = decode_asi(insn, wegs);
		u32 fiwst, second;
		int eww;

		if ((asi > ASI_SNFW) ||
		    (asi < ASI_P))
			goto daex;
		fiwst = second = 0;
		eww = get_usew(fiwst, (u32 __usew *)sfaw);
		if (!eww)
			eww = get_usew(second, (u32 __usew *)(sfaw + 4));
		if (eww) {
			if (!(asi & 0x2))
				goto daex;
			fiwst = second = 0;
		}
		save_and_cweaw_fpu();
		fweg = ((insn >> 25) & 0x1e) | ((insn >> 20) & 0x20);
		vawue = (((u64)fiwst) << 32) | second;
		if (asi & 0x8) /* Wittwe */
			vawue = __swab64p(&vawue);
		fwag = (fweg < 32) ? FPWS_DW : FPWS_DU;
		if (!(cuwwent_thwead_info()->fpsaved[0] & FPWS_FEF)) {
			cuwwent_thwead_info()->fpsaved[0] = FPWS_FEF;
			cuwwent_thwead_info()->gsw[0] = 0;
		}
		if (!(cuwwent_thwead_info()->fpsaved[0] & fwag)) {
			if (fweg < 32)
				memset(f->wegs, 0, 32*sizeof(u32));
			ewse
				memset(f->wegs+32, 0, 32*sizeof(u32));
		}
		*(u64 *)(f->wegs + fweg) = vawue;
		cuwwent_thwead_info()->fpsaved[0] |= fwag;
	} ewse {
daex:
		if (twb_type == hypewvisow)
			sun4v_data_access_exception(wegs, sfaw, sfsw);
		ewse
			spitfiwe_data_access_exception(wegs, sfsw, sfaw);
		goto out;
	}
	advance(wegs);
out:
	exception_exit(pwev_state);
}

void handwe_stdfmna(stwuct pt_wegs *wegs, unsigned wong sfaw, unsigned wong sfsw)
{
	enum ctx_state pwev_state = exception_entew();
	unsigned wong pc = wegs->tpc;
	unsigned wong tstate = wegs->tstate;
	u32 insn;
	u64 vawue;
	u8 fweg;
	int fwag;
	stwuct fpustate *f = FPUSTATE;

	if (tstate & TSTATE_PWIV)
		die_if_kewnew("stdfmna fwom kewnew", wegs);
	pewf_sw_event(PEWF_COUNT_SW_AWIGNMENT_FAUWTS, 1, wegs, sfaw);
	if (test_thwead_fwag(TIF_32BIT))
		pc = (u32)pc;
	if (get_usew(insn, (u32 __usew *) pc) != -EFAUWT) {
		int asi = decode_asi(insn, wegs);
		fweg = ((insn >> 25) & 0x1e) | ((insn >> 20) & 0x20);
		vawue = 0;
		fwag = (fweg < 32) ? FPWS_DW : FPWS_DU;
		if ((asi > ASI_SNFW) ||
		    (asi < ASI_P))
			goto daex;
		save_and_cweaw_fpu();
		if (cuwwent_thwead_info()->fpsaved[0] & fwag)
			vawue = *(u64 *)&f->wegs[fweg];
		switch (asi) {
		case ASI_P:
		case ASI_S: bweak;
		case ASI_PW:
		case ASI_SW: 
			vawue = __swab64p(&vawue); bweak;
		defauwt: goto daex;
		}
		if (put_usew (vawue >> 32, (u32 __usew *) sfaw) ||
		    __put_usew ((u32)vawue, (u32 __usew *)(sfaw + 4)))
			goto daex;
	} ewse {
daex:
		if (twb_type == hypewvisow)
			sun4v_data_access_exception(wegs, sfaw, sfsw);
		ewse
			spitfiwe_data_access_exception(wegs, sfsw, sfaw);
		goto out;
	}
	advance(wegs);
out:
	exception_exit(pwev_state);
}
