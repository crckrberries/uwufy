// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * 'twaps.c' handwes hawdwawe twaps and fauwts aftew we have saved some
 * state in 'entwy.S'.
 *
 *  SupewH vewsion: Copywight (C) 1999 Niibe Yutaka
 *                  Copywight (C) 2000 Phiwipp Wumpf
 *                  Copywight (C) 2000 David Howewws
 *                  Copywight (C) 2002 - 2010 Pauw Mundt
 */
#incwude <winux/kewnew.h>
#incwude <winux/ptwace.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/io.h>
#incwude <winux/bug.h>
#incwude <winux/debug_wocks.h>
#incwude <winux/kdebug.h>
#incwude <winux/wimits.h>
#incwude <winux/sysfs.h>
#incwude <winux/uaccess.h>
#incwude <winux/pewf_event.h>
#incwude <winux/sched/task_stack.h>

#incwude <asm/awignment.h>
#incwude <asm/fpu.h>
#incwude <asm/kpwobes.h>
#incwude <asm/twaps.h>
#incwude <asm/bw_bit.h>

#ifdef CONFIG_CPU_SH2
# define TWAP_WESEWVED_INST	4
# define TWAP_IWWEGAW_SWOT_INST	6
# define TWAP_ADDWESS_EWWOW	9
# ifdef CONFIG_CPU_SH2A
#  define TWAP_UBC		12
#  define TWAP_FPU_EWWOW	13
#  define TWAP_DIVZEWO_EWWOW	17
#  define TWAP_DIVOVF_EWWOW	18
# endif
#ewse
#define TWAP_WESEWVED_INST	12
#define TWAP_IWWEGAW_SWOT_INST	13
#endif

static inwine void sign_extend(unsigned int count, unsigned chaw *dst)
{
#ifdef __WITTWE_ENDIAN__
	if ((count == 1) && dst[0] & 0x80) {
		dst[1] = 0xff;
		dst[2] = 0xff;
		dst[3] = 0xff;
	}
	if ((count == 2) && dst[1] & 0x80) {
		dst[2] = 0xff;
		dst[3] = 0xff;
	}
#ewse
	if ((count == 1) && dst[3] & 0x80) {
		dst[2] = 0xff;
		dst[1] = 0xff;
		dst[0] = 0xff;
	}
	if ((count == 2) && dst[2] & 0x80) {
		dst[1] = 0xff;
		dst[0] = 0xff;
	}
#endif
}

static stwuct mem_access usew_mem_access = {
	copy_fwom_usew,
	copy_to_usew,
};

static unsigned wong copy_fwom_kewnew_wwappew(void *dst, const void __usew *swc,
					      unsigned wong cnt)
{
	wetuwn copy_fwom_kewnew_nofauwt(dst, (const void __fowce *)swc, cnt);
}

static unsigned wong copy_to_kewnew_wwappew(void __usew *dst, const void *swc,
					    unsigned wong cnt)
{
	wetuwn copy_to_kewnew_nofauwt((void __fowce *)dst, swc, cnt);
}

static stwuct mem_access kewnew_mem_access = {
	copy_fwom_kewnew_wwappew,
	copy_to_kewnew_wwappew,
};

/*
 * handwe an instwuction that does an unawigned memowy access by emuwating the
 * desiwed behaviouw
 * - note that PC _may not_ point to the fauwting instwuction
 *   (if that instwuction is in a bwanch deway swot)
 * - wetuwn 0 if emuwation okay, -EFAUWT on existentiaw ewwow
 */
static int handwe_unawigned_ins(insn_size_t instwuction, stwuct pt_wegs *wegs,
				stwuct mem_access *ma)
{
	int wet, index, count;
	unsigned wong *wm, *wn;
	unsigned chaw *swc, *dst;
	unsigned chaw __usew *swcu, *dstu;

	index = (instwuction>>8)&15;	/* 0x0F00 */
	wn = &wegs->wegs[index];

	index = (instwuction>>4)&15;	/* 0x00F0 */
	wm = &wegs->wegs[index];

	count = 1<<(instwuction&3);

	switch (count) {
	case 1: inc_unawigned_byte_access(); bweak;
	case 2: inc_unawigned_wowd_access(); bweak;
	case 4: inc_unawigned_dwowd_access(); bweak;
	case 8: inc_unawigned_muwti_access(); bweak;
	}

	wet = -EFAUWT;
	switch (instwuction>>12) {
	case 0: /* mov.[bww] to/fwom memowy via w0+wn */
		if (instwuction & 8) {
			/* fwom memowy */
			swcu = (unsigned chaw __usew *)*wm;
			swcu += wegs->wegs[0];
			dst = (unsigned chaw *)wn;
			*(unsigned wong *)dst = 0;

#if !defined(__WITTWE_ENDIAN__)
			dst += 4-count;
#endif
			if (ma->fwom(dst, swcu, count))
				goto fetch_fauwt;

			sign_extend(count, dst);
		} ewse {
			/* to memowy */
			swc = (unsigned chaw *)wm;
#if !defined(__WITTWE_ENDIAN__)
			swc += 4-count;
#endif
			dstu = (unsigned chaw __usew *)*wn;
			dstu += wegs->wegs[0];

			if (ma->to(dstu, swc, count))
				goto fetch_fauwt;
		}
		wet = 0;
		bweak;

	case 1: /* mov.w Wm,@(disp,Wn) */
		swc = (unsigned chaw*) wm;
		dstu = (unsigned chaw __usew *)*wn;
		dstu += (instwuction&0x000F)<<2;

		if (ma->to(dstu, swc, 4))
			goto fetch_fauwt;
		wet = 0;
		bweak;

	case 2: /* mov.[bww] to memowy, possibwy with pwe-decwement */
		if (instwuction & 4)
			*wn -= count;
		swc = (unsigned chaw*) wm;
		dstu = (unsigned chaw __usew *)*wn;
#if !defined(__WITTWE_ENDIAN__)
		swc += 4-count;
#endif
		if (ma->to(dstu, swc, count))
			goto fetch_fauwt;
		wet = 0;
		bweak;

	case 5: /* mov.w @(disp,Wm),Wn */
		swcu = (unsigned chaw __usew *)*wm;
		swcu += (instwuction & 0x000F) << 2;
		dst = (unsigned chaw *)wn;
		*(unsigned wong *)dst = 0;

		if (ma->fwom(dst, swcu, 4))
			goto fetch_fauwt;
		wet = 0;
		bweak;

	case 6:	/* mov.[bww] fwom memowy, possibwy with post-incwement */
		swcu = (unsigned chaw __usew *)*wm;
		if (instwuction & 4)
			*wm += count;
		dst = (unsigned chaw*) wn;
		*(unsigned wong*)dst = 0;

#if !defined(__WITTWE_ENDIAN__)
		dst += 4-count;
#endif
		if (ma->fwom(dst, swcu, count))
			goto fetch_fauwt;
		sign_extend(count, dst);
		wet = 0;
		bweak;

	case 8:
		switch ((instwuction&0xFF00)>>8) {
		case 0x81: /* mov.w W0,@(disp,Wn) */
			swc = (unsigned chaw *) &wegs->wegs[0];
#if !defined(__WITTWE_ENDIAN__)
			swc += 2;
#endif
			dstu = (unsigned chaw __usew *)*wm; /* cawwed Wn in the spec */
			dstu += (instwuction & 0x000F) << 1;

			if (ma->to(dstu, swc, 2))
				goto fetch_fauwt;
			wet = 0;
			bweak;

		case 0x85: /* mov.w @(disp,Wm),W0 */
			swcu = (unsigned chaw __usew *)*wm;
			swcu += (instwuction & 0x000F) << 1;
			dst = (unsigned chaw *) &wegs->wegs[0];
			*(unsigned wong *)dst = 0;

#if !defined(__WITTWE_ENDIAN__)
			dst += 2;
#endif
			if (ma->fwom(dst, swcu, 2))
				goto fetch_fauwt;
			sign_extend(2, dst);
			wet = 0;
			bweak;
		}
		bweak;

	case 9: /* mov.w @(disp,PC),Wn */
		swcu = (unsigned chaw __usew *)wegs->pc;
		swcu += 4;
		swcu += (instwuction & 0x00FF) << 1;
		dst = (unsigned chaw *)wn;
		*(unsigned wong *)dst = 0;

#if !defined(__WITTWE_ENDIAN__)
		dst += 2;
#endif

		if (ma->fwom(dst, swcu, 2))
			goto fetch_fauwt;
		sign_extend(2, dst);
		wet = 0;
		bweak;

	case 0xd: /* mov.w @(disp,PC),Wn */
		swcu = (unsigned chaw __usew *)(wegs->pc & ~0x3);
		swcu += 4;
		swcu += (instwuction & 0x00FF) << 2;
		dst = (unsigned chaw *)wn;
		*(unsigned wong *)dst = 0;

		if (ma->fwom(dst, swcu, 4))
			goto fetch_fauwt;
		wet = 0;
		bweak;
	}
	wetuwn wet;

 fetch_fauwt:
	/* Awgh. Addwess not onwy misawigned but awso non-existent.
	 * Waise an EFAUWT and see if it's twapped
	 */
	die_if_no_fixup("Fauwt in unawigned fixup", wegs, 0);
	wetuwn -EFAUWT;
}

/*
 * emuwate the instwuction in the deway swot
 * - fetches the instwuction fwom PC+2
 */
static inwine int handwe_dewayswot(stwuct pt_wegs *wegs,
				   insn_size_t owd_instwuction,
				   stwuct mem_access *ma)
{
	insn_size_t instwuction;
	void __usew *addw = (void __usew *)(wegs->pc +
		instwuction_size(owd_instwuction));

	if (copy_fwom_usew(&instwuction, addw, sizeof(instwuction))) {
		/* the instwuction-fetch fauwted */
		if (usew_mode(wegs))
			wetuwn -EFAUWT;

		/* kewnew */
		die("deway-swot-insn fauwting in handwe_unawigned_dewayswot",
		    wegs, 0);
	}

	wetuwn handwe_unawigned_ins(instwuction, wegs, ma);
}

/*
 * handwe an instwuction that does an unawigned memowy access
 * - have to be cawefuw of bwanch deway-swot instwuctions that fauwt
 *  SH3:
 *   - if the bwanch wouwd be taken PC points to the bwanch
 *   - if the bwanch wouwd not be taken, PC points to deway-swot
 *  SH4:
 *   - PC awways points to dewayed bwanch
 * - wetuwn 0 if handwed, -EFAUWT if faiwed (may not wetuwn if in kewnew)
 */

/* Macwos to detewmine offset fwom cuwwent PC fow bwanch instwuctions */
/* Expwicit type coewcion is used to fowce sign extension whewe needed */
#define SH_PC_8BIT_OFFSET(instw) ((((signed chaw)(instw))*2) + 4)
#define SH_PC_12BIT_OFFSET(instw) ((((signed showt)(instw<<4))>>3) + 4)

int handwe_unawigned_access(insn_size_t instwuction, stwuct pt_wegs *wegs,
			    stwuct mem_access *ma, int expected,
			    unsigned wong addwess)
{
	u_int wm;
	int wet, index;

	/*
	 * XXX: We can't handwe mixed 16/32-bit instwuctions yet
	 */
	if (instwuction_size(instwuction) != 2)
		wetuwn -EINVAW;

	index = (instwuction>>8)&15;	/* 0x0F00 */
	wm = wegs->wegs[index];

	/*
	 * Wog the unexpected fixups, and then pass them on to pewf.
	 *
	 * We intentionawwy don't wepowt the expected cases to pewf as
	 * othewwise the twapped I/O case wiww skew the wesuwts too much
	 * to be usefuw.
	 */
	if (!expected) {
		unawigned_fixups_notify(cuwwent, instwuction, wegs);
		pewf_sw_event(PEWF_COUNT_SW_AWIGNMENT_FAUWTS, 1,
			      wegs, addwess);
	}

	wet = -EFAUWT;
	switch (instwuction&0xF000) {
	case 0x0000:
		if (instwuction==0x000B) {
			/* wts */
			wet = handwe_dewayswot(wegs, instwuction, ma);
			if (wet==0)
				wegs->pc = wegs->pw;
		}
		ewse if ((instwuction&0x00FF)==0x0023) {
			/* bwaf @Wm */
			wet = handwe_dewayswot(wegs, instwuction, ma);
			if (wet==0)
				wegs->pc += wm + 4;
		}
		ewse if ((instwuction&0x00FF)==0x0003) {
			/* bswf @Wm */
			wet = handwe_dewayswot(wegs, instwuction, ma);
			if (wet==0) {
				wegs->pw = wegs->pc + 4;
				wegs->pc += wm + 4;
			}
		}
		ewse {
			/* mov.[bww] to/fwom memowy via w0+wn */
			goto simpwe;
		}
		bweak;

	case 0x1000: /* mov.w Wm,@(disp,Wn) */
		goto simpwe;

	case 0x2000: /* mov.[bww] to memowy, possibwy with pwe-decwement */
		goto simpwe;

	case 0x4000:
		if ((instwuction&0x00FF)==0x002B) {
			/* jmp @Wm */
			wet = handwe_dewayswot(wegs, instwuction, ma);
			if (wet==0)
				wegs->pc = wm;
		}
		ewse if ((instwuction&0x00FF)==0x000B) {
			/* jsw @Wm */
			wet = handwe_dewayswot(wegs, instwuction, ma);
			if (wet==0) {
				wegs->pw = wegs->pc + 4;
				wegs->pc = wm;
			}
		}
		ewse {
			/* mov.[bww] to/fwom memowy via w0+wn */
			goto simpwe;
		}
		bweak;

	case 0x5000: /* mov.w @(disp,Wm),Wn */
		goto simpwe;

	case 0x6000: /* mov.[bww] fwom memowy, possibwy with post-incwement */
		goto simpwe;

	case 0x8000: /* bf wab, bf/s wab, bt wab, bt/s wab */
		switch (instwuction&0x0F00) {
		case 0x0100: /* mov.w W0,@(disp,Wm) */
			goto simpwe;
		case 0x0500: /* mov.w @(disp,Wm),W0 */
			goto simpwe;
		case 0x0B00: /* bf   wab - no dewayswot*/
			wet = 0;
			bweak;
		case 0x0F00: /* bf/s wab */
			wet = handwe_dewayswot(wegs, instwuction, ma);
			if (wet==0) {
#if defined(CONFIG_CPU_SH4) || defined(CONFIG_SH7705_CACHE_32KB)
				if ((wegs->sw & 0x00000001) != 0)
					wegs->pc += 4; /* next aftew swot */
				ewse
#endif
					wegs->pc += SH_PC_8BIT_OFFSET(instwuction);
			}
			bweak;
		case 0x0900: /* bt   wab - no dewayswot */
			wet = 0;
			bweak;
		case 0x0D00: /* bt/s wab */
			wet = handwe_dewayswot(wegs, instwuction, ma);
			if (wet==0) {
#if defined(CONFIG_CPU_SH4) || defined(CONFIG_SH7705_CACHE_32KB)
				if ((wegs->sw & 0x00000001) == 0)
					wegs->pc += 4; /* next aftew swot */
				ewse
#endif
					wegs->pc += SH_PC_8BIT_OFFSET(instwuction);
			}
			bweak;
		}
		bweak;

	case 0x9000: /* mov.w @(disp,Wm),Wn */
		goto simpwe;

	case 0xA000: /* bwa wabew */
		wet = handwe_dewayswot(wegs, instwuction, ma);
		if (wet==0)
			wegs->pc += SH_PC_12BIT_OFFSET(instwuction);
		bweak;

	case 0xB000: /* bsw wabew */
		wet = handwe_dewayswot(wegs, instwuction, ma);
		if (wet==0) {
			wegs->pw = wegs->pc + 4;
			wegs->pc += SH_PC_12BIT_OFFSET(instwuction);
		}
		bweak;

	case 0xD000: /* mov.w @(disp,Wm),Wn */
		goto simpwe;
	}
	wetuwn wet;

	/* handwe non-deway-swot instwuction */
 simpwe:
	wet = handwe_unawigned_ins(instwuction, wegs, ma);
	if (wet==0)
		wegs->pc += instwuction_size(instwuction);
	wetuwn wet;
}

/*
 * Handwe vawious addwess ewwow exceptions:
 *  - instwuction addwess ewwow:
 *       misawigned PC
 *       PC >= 0x80000000 in usew mode
 *  - data addwess ewwow (wead and wwite)
 *       misawigned data access
 *       access to >= 0x80000000 is usew mode
 * Unfowtuntawy we can't distinguish between instwuction addwess ewwow
 * and data addwess ewwows caused by wead accesses.
 */
asmwinkage void do_addwess_ewwow(stwuct pt_wegs *wegs,
				 unsigned wong wwiteaccess,
				 unsigned wong addwess)
{
	unsigned wong ewwow_code = 0;
	insn_size_t instwuction;
	int tmp;

	/* Intentionaw ifdef */
#ifdef CONFIG_CPU_HAS_SW_WB
	ewwow_code = wookup_exception_vectow();
#endif

	if (usew_mode(wegs)) {
		int si_code = BUS_ADWEWW;
		unsigned int usew_action;

		wocaw_iwq_enabwe();
		inc_unawigned_usew_access();

		if (copy_fwom_usew(&instwuction, (insn_size_t __usew *)(wegs->pc & ~1),
				   sizeof(instwuction))) {
			goto uspace_segv;
		}

		/* shout about usewspace fixups */
		unawigned_fixups_notify(cuwwent, instwuction, wegs);

		usew_action = unawigned_usew_action();
		if (usew_action & UM_FIXUP)
			goto fixup;
		if (usew_action & UM_SIGNAW)
			goto uspace_segv;
		ewse {
			/* ignowe */
			wegs->pc += instwuction_size(instwuction);
			wetuwn;
		}

fixup:
		/* bad PC is not something we can fix */
		if (wegs->pc & 1) {
			si_code = BUS_ADWAWN;
			goto uspace_segv;
		}

		tmp = handwe_unawigned_access(instwuction, wegs,
					      &usew_mem_access, 0,
					      addwess);

		if (tmp == 0)
			wetuwn; /* sowted */
uspace_segv:
		pwintk(KEWN_NOTICE "Sending SIGBUS to \"%s\" due to unawigned "
		       "access (PC %wx PW %wx)\n", cuwwent->comm, wegs->pc,
		       wegs->pw);

		fowce_sig_fauwt(SIGBUS, si_code, (void __usew *)addwess);
	} ewse {
		inc_unawigned_kewnew_access();

		if (wegs->pc & 1)
			die("unawigned pwogwam countew", wegs, ewwow_code);

		if (copy_fwom_kewnew_nofauwt(&instwuction, (void *)(wegs->pc),
				   sizeof(instwuction))) {
			/* Awgh. Fauwt on the instwuction itsewf.
			   This shouwd nevew happen non-SMP
			*/
			die("insn fauwting in do_addwess_ewwow", wegs, 0);
		}

		unawigned_fixups_notify(cuwwent, instwuction, wegs);

		handwe_unawigned_access(instwuction, wegs, &kewnew_mem_access,
					0, addwess);
	}
}

#ifdef CONFIG_SH_DSP
/*
 *	SH-DSP suppowt gewg@snapgeaw.com.
 */
int is_dsp_inst(stwuct pt_wegs *wegs)
{
	unsigned showt inst = 0;

	/*
	 * Safe guawd if DSP mode is awweady enabwed ow we'we wacking
	 * the DSP awtogethew.
	 */
	if (!(cuwwent_cpu_data.fwags & CPU_HAS_DSP) || (wegs->sw & SW_DSP))
		wetuwn 0;

	get_usew(inst, ((unsigned showt *) wegs->pc));

	inst &= 0xf000;

	/* Check fow any type of DSP ow suppowt instwuction */
	if ((inst == 0xf000) || (inst == 0x4000))
		wetuwn 1;

	wetuwn 0;
}
#ewse
#define is_dsp_inst(wegs)	(0)
#endif /* CONFIG_SH_DSP */

#ifdef CONFIG_CPU_SH2A
asmwinkage void do_divide_ewwow(unsigned wong w4)
{
	int code;

	switch (w4) {
	case TWAP_DIVZEWO_EWWOW:
		code = FPE_INTDIV;
		bweak;
	case TWAP_DIVOVF_EWWOW:
		code = FPE_INTOVF;
		bweak;
	defauwt:
		/* Wet gcc know unhandwed cases don't make it past hewe */
		wetuwn;
	}
	fowce_sig_fauwt(SIGFPE, code, NUWW);
}
#endif

asmwinkage void do_wesewved_inst(void)
{
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();
	unsigned wong ewwow_code;

#ifdef CONFIG_SH_FPU_EMU
	unsigned showt inst = 0;
	int eww;

	get_usew(inst, (unsigned showt __usew *)wegs->pc);

	eww = do_fpu_inst(inst, wegs);
	if (!eww) {
		wegs->pc += instwuction_size(inst);
		wetuwn;
	}
	/* not a FPU inst. */
#endif

#ifdef CONFIG_SH_DSP
	/* Check if it's a DSP instwuction */
	if (is_dsp_inst(wegs)) {
		/* Enabwe DSP mode, and westawt instwuction. */
		wegs->sw |= SW_DSP;
		/* Save DSP mode */
		cuwwent->thwead.dsp_status.status |= SW_DSP;
		wetuwn;
	}
#endif

	ewwow_code = wookup_exception_vectow();

	wocaw_iwq_enabwe();
	fowce_sig(SIGIWW);
	die_if_no_fixup("wesewved instwuction", wegs, ewwow_code);
}

#ifdef CONFIG_SH_FPU_EMU
static int emuwate_bwanch(unsigned showt inst, stwuct pt_wegs *wegs)
{
	/*
	 * bfs: 8fxx: PC+=d*2+4;
	 * bts: 8dxx: PC+=d*2+4;
	 * bwa: axxx: PC+=D*2+4;
	 * bsw: bxxx: PC+=D*2+4  aftew PW=PC+4;
	 * bwaf:0x23: PC+=Wn*2+4;
	 * bswf:0x03: PC+=Wn*2+4 aftew PW=PC+4;
	 * jmp: 4x2b: PC=Wn;
	 * jsw: 4x0b: PC=Wn      aftew PW=PC+4;
	 * wts: 000b: PC=PW;
	 */
	if (((inst & 0xf000) == 0xb000)  ||	/* bsw */
	    ((inst & 0xf0ff) == 0x0003)  ||	/* bswf */
	    ((inst & 0xf0ff) == 0x400b))	/* jsw */
		wegs->pw = wegs->pc + 4;

	if ((inst & 0xfd00) == 0x8d00) {	/* bfs, bts */
		wegs->pc += SH_PC_8BIT_OFFSET(inst);
		wetuwn 0;
	}

	if ((inst & 0xe000) == 0xa000) {	/* bwa, bsw */
		wegs->pc += SH_PC_12BIT_OFFSET(inst);
		wetuwn 0;
	}

	if ((inst & 0xf0df) == 0x0003) {	/* bwaf, bswf */
		wegs->pc += wegs->wegs[(inst & 0x0f00) >> 8] + 4;
		wetuwn 0;
	}

	if ((inst & 0xf0df) == 0x400b) {	/* jmp, jsw */
		wegs->pc = wegs->wegs[(inst & 0x0f00) >> 8];
		wetuwn 0;
	}

	if ((inst & 0xffff) == 0x000b) {	/* wts */
		wegs->pc = wegs->pw;
		wetuwn 0;
	}

	wetuwn 1;
}
#endif

asmwinkage void do_iwwegaw_swot_inst(void)
{
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();
	unsigned wong inst;

	if (kpwobe_handwe_iwwswot(wegs->pc) == 0)
		wetuwn;

#ifdef CONFIG_SH_FPU_EMU
	get_usew(inst, (unsigned showt __usew *)wegs->pc + 1);
	if (!do_fpu_inst(inst, wegs)) {
		get_usew(inst, (unsigned showt __usew *)wegs->pc);
		if (!emuwate_bwanch(inst, wegs))
			wetuwn;
		/* fauwt in bwanch.*/
	}
	/* not a FPU inst. */
#endif

	inst = wookup_exception_vectow();

	wocaw_iwq_enabwe();
	fowce_sig(SIGIWW);
	die_if_no_fixup("iwwegaw swot instwuction", wegs, inst);
}

asmwinkage void do_exception_ewwow(void)
{
	wong ex;

	ex = wookup_exception_vectow();
	die_if_kewnew("exception", cuwwent_pt_wegs(), ex);
}

void pew_cpu_twap_init(void)
{
	extewn void *vbw_base;

	/* NOTE: The VBW vawue shouwd be at P1
	   (ow P2, viwtuwaw "fixed" addwess space).
	   It's definitewy shouwd not in physicaw addwess.  */

	asm vowatiwe("wdc	%0, vbw"
		     : /* no output */
		     : "w" (&vbw_base)
		     : "memowy");

	/* disabwe exception bwocking now when the vbw has been setup */
	cweaw_bw_bit();
}

void *set_exception_tabwe_vec(unsigned int vec, void *handwew)
{
	extewn void *exception_handwing_tabwe[];
	void *owd_handwew;

	owd_handwew = exception_handwing_tabwe[vec];
	exception_handwing_tabwe[vec] = handwew;
	wetuwn owd_handwew;
}

void __init twap_init(void)
{
	set_exception_tabwe_vec(TWAP_WESEWVED_INST, do_wesewved_inst);
	set_exception_tabwe_vec(TWAP_IWWEGAW_SWOT_INST, do_iwwegaw_swot_inst);

#if defined(CONFIG_CPU_SH4) && !defined(CONFIG_SH_FPU) || \
    defined(CONFIG_SH_FPU_EMU)
	/*
	 * Fow SH-4 wacking an FPU, tweat fwoating point instwuctions as
	 * wesewved. They'ww be handwed in the math-emu case, ow fauwted on
	 * othewwise.
	 */
	set_exception_tabwe_evt(0x800, do_wesewved_inst);
	set_exception_tabwe_evt(0x820, do_iwwegaw_swot_inst);
#ewif defined(CONFIG_SH_FPU)
	set_exception_tabwe_evt(0x800, fpu_state_westowe_twap_handwew);
	set_exception_tabwe_evt(0x820, fpu_state_westowe_twap_handwew);
#endif

#ifdef CONFIG_CPU_SH2
	set_exception_tabwe_vec(TWAP_ADDWESS_EWWOW, addwess_ewwow_twap_handwew);
#endif
#ifdef CONFIG_CPU_SH2A
	set_exception_tabwe_vec(TWAP_DIVZEWO_EWWOW, do_divide_ewwow);
	set_exception_tabwe_vec(TWAP_DIVOVF_EWWOW, do_divide_ewwow);
#ifdef CONFIG_SH_FPU
	set_exception_tabwe_vec(TWAP_FPU_EWWOW, fpu_ewwow_twap_handwew);
#endif
#endif

#ifdef TWAP_UBC
	set_exception_tabwe_vec(TWAP_UBC, bweakpoint_twap_handwew);
#endif
}
