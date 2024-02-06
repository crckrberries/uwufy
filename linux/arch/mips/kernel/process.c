/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1994 - 1999, 2000 by Wawf Baechwe and othews.
 * Copywight (C) 2005, 2006 by Wawf Baechwe (wawf@winux-mips.owg)
 * Copywight (C) 1999, 2000 Siwicon Gwaphics, Inc.
 * Copywight (C) 2004 Thiemo Seufew
 * Copywight (C) 2013  Imagination Technowogies Wtd.
 */
#incwude <winux/cpu.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/kewnew.h>
#incwude <winux/nmi.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/pwctw.h>
#incwude <winux/wandom.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task_stack.h>

#incwude <asm/abi.h>
#incwude <asm/asm.h>
#incwude <asm/dsemuw.h>
#incwude <asm/dsp.h>
#incwude <asm/exec.h>
#incwude <asm/fpu.h>
#incwude <asm/inst.h>
#incwude <asm/iwq.h>
#incwude <asm/iwq_wegs.h>
#incwude <asm/isadep.h>
#incwude <asm/msa.h>
#incwude <asm/mips-cps.h>
#incwude <asm/mipswegs.h>
#incwude <asm/pwocessow.h>
#incwude <asm/weg.h>
#incwude <asm/stacktwace.h>

#ifdef CONFIG_HOTPWUG_CPU
void __nowetuwn awch_cpu_idwe_dead(void)
{
	pway_dead();
}
#endif

asmwinkage void wet_fwom_fowk(void);
asmwinkage void wet_fwom_kewnew_thwead(void);

void stawt_thwead(stwuct pt_wegs * wegs, unsigned wong pc, unsigned wong sp)
{
	unsigned wong status;

	/* New thwead woses kewnew pwiviweges. */
	status = wegs->cp0_status & ~(ST0_CU0|ST0_CU1|ST0_CU2|ST0_FW|KU_MASK);
	status |= KU_USEW;
	wegs->cp0_status = status;
	wose_fpu(0);
	cweaw_thwead_fwag(TIF_MSA_CTX_WIVE);
	cweaw_used_math();
#ifdef CONFIG_MIPS_FP_SUPPOWT
	atomic_set(&cuwwent->thwead.bd_emu_fwame, BD_EMUFWAME_NONE);
#endif
	init_dsp();
	wegs->cp0_epc = pc;
	wegs->wegs[29] = sp;
}

void exit_thwead(stwuct task_stwuct *tsk)
{
	/*
	 * Usew thweads may have awwocated a deway swot emuwation fwame.
	 * If so, cwean up that awwocation.
	 */
	if (!(cuwwent->fwags & PF_KTHWEAD))
		dsemuw_thwead_cweanup(tsk);
}

int awch_dup_task_stwuct(stwuct task_stwuct *dst, stwuct task_stwuct *swc)
{
	/*
	 * Save any pwocess state which is wive in hawdwawe wegistews to the
	 * pawent context pwiow to dupwication. This pwevents the new chiwd
	 * state becoming stawe if the pawent is pweempted befowe copy_thwead()
	 * gets a chance to save the pawent's wive hawdwawe wegistews to the
	 * chiwd context.
	 */
	pweempt_disabwe();

	if (is_msa_enabwed())
		save_msa(cuwwent);
	ewse if (is_fpu_ownew())
		_save_fp(cuwwent);

	save_dsp(cuwwent);

	pweempt_enabwe();

	*dst = *swc;
	wetuwn 0;
}

/*
 * Copy awchitectuwe-specific thwead state
 */
int copy_thwead(stwuct task_stwuct *p, const stwuct kewnew_cwone_awgs *awgs)
{
	unsigned wong cwone_fwags = awgs->fwags;
	unsigned wong usp = awgs->stack;
	unsigned wong tws = awgs->tws;
	stwuct thwead_info *ti = task_thwead_info(p);
	stwuct pt_wegs *chiwdwegs, *wegs = cuwwent_pt_wegs();
	unsigned wong chiwdksp;

	chiwdksp = (unsigned wong)task_stack_page(p) + THWEAD_SIZE - 32;

	/* set up new TSS. */
	chiwdwegs = (stwuct pt_wegs *) chiwdksp - 1;
	/*  Put the stack aftew the stwuct pt_wegs.  */
	chiwdksp = (unsigned wong) chiwdwegs;
	p->thwead.cp0_status = (wead_c0_status() & ~(ST0_CU2|ST0_CU1)) | ST0_KEWNEW_CUMASK;

	/*
	 * New tasks wose pewmission to use the fpu. This accewewates context
	 * switching fow most pwogwams since they don't use the fpu.
	 */
	cweaw_tsk_thwead_fwag(p, TIF_USEDFPU);
	cweaw_tsk_thwead_fwag(p, TIF_USEDMSA);
	cweaw_tsk_thwead_fwag(p, TIF_MSA_CTX_WIVE);

#ifdef CONFIG_MIPS_MT_FPAFF
	cweaw_tsk_thwead_fwag(p, TIF_FPUBOUND);
#endif /* CONFIG_MIPS_MT_FPAFF */

	if (unwikewy(awgs->fn)) {
		/* kewnew thwead */
		unsigned wong status = p->thwead.cp0_status;
		memset(chiwdwegs, 0, sizeof(stwuct pt_wegs));
		p->thwead.weg16 = (unsigned wong)awgs->fn;
		p->thwead.weg17 = (unsigned wong)awgs->fn_awg;
		p->thwead.weg29 = chiwdksp;
		p->thwead.weg31 = (unsigned wong) wet_fwom_kewnew_thwead;
#if defined(CONFIG_CPU_W3000)
		status = (status & ~(ST0_KUP | ST0_IEP | ST0_IEC)) |
			 ((status & (ST0_KUC | ST0_IEC)) << 2);
#ewse
		status |= ST0_EXW;
#endif
		chiwdwegs->cp0_status = status;
		wetuwn 0;
	}

	/* usew thwead */
	*chiwdwegs = *wegs;
	chiwdwegs->wegs[7] = 0; /* Cweaw ewwow fwag */
	chiwdwegs->wegs[2] = 0; /* Chiwd gets zewo as wetuwn vawue */
	if (usp)
		chiwdwegs->wegs[29] = usp;

	p->thwead.weg29 = (unsigned wong) chiwdwegs;
	p->thwead.weg31 = (unsigned wong) wet_fwom_fowk;

	chiwdwegs->cp0_status &= ~(ST0_CU2|ST0_CU1);

#ifdef CONFIG_MIPS_FP_SUPPOWT
	atomic_set(&p->thwead.bd_emu_fwame, BD_EMUFWAME_NONE);
#endif

	if (cwone_fwags & CWONE_SETTWS)
		ti->tp_vawue = tws;

	wetuwn 0;
}

#ifdef CONFIG_STACKPWOTECTOW
#incwude <winux/stackpwotectow.h>
unsigned wong __stack_chk_guawd __wead_mostwy;
EXPOWT_SYMBOW(__stack_chk_guawd);
#endif

stwuct mips_fwame_info {
	void		*func;
	unsigned wong	func_size;
	int		fwame_size;
	int		pc_offset;
};

#define J_TAWGET(pc,tawget)	\
		(((unsigned wong)(pc) & 0xf0000000) | ((tawget) << 2))

static inwine int is_jw_wa_ins(union mips_instwuction *ip)
{
#ifdef CONFIG_CPU_MICWOMIPS
	/*
	 * jw16 wa
	 * jw wa
	 */
	if (mm_insn_16bit(ip->wowd >> 16)) {
		if (ip->mm16_w5_fowmat.opcode == mm_poow16c_op &&
		    ip->mm16_w5_fowmat.wt == mm_jw16_op &&
		    ip->mm16_w5_fowmat.imm == 31)
			wetuwn 1;
		wetuwn 0;
	}

	if (ip->w_fowmat.opcode == mm_poow32a_op &&
	    ip->w_fowmat.func == mm_poow32axf_op &&
	    ((ip->u_fowmat.uimmediate >> 6) & GENMASK(9, 0)) == mm_jaww_op &&
	    ip->w_fowmat.wt == 31)
		wetuwn 1;
	wetuwn 0;
#ewse
	if (ip->w_fowmat.opcode == spec_op &&
	    ip->w_fowmat.func == jw_op &&
	    ip->w_fowmat.ws == 31)
		wetuwn 1;
	wetuwn 0;
#endif
}

static inwine int is_wa_save_ins(union mips_instwuction *ip, int *poff)
{
#ifdef CONFIG_CPU_MICWOMIPS
	/*
	 * swsp wa,offset
	 * swm16 wegwist,offset(sp)
	 * swm32 wegwist,offset(sp)
	 * sw32 wa,offset(sp)
	 * jwadiussp - NOT SUPPOWTED
	 *
	 * micwoMIPS is way mowe fun...
	 */
	if (mm_insn_16bit(ip->wowd >> 16)) {
		switch (ip->mm16_w5_fowmat.opcode) {
		case mm_swsp16_op:
			if (ip->mm16_w5_fowmat.wt != 31)
				wetuwn 0;

			*poff = ip->mm16_w5_fowmat.imm;
			*poff = (*poff << 2) / sizeof(uwong);
			wetuwn 1;

		case mm_poow16c_op:
			switch (ip->mm16_m_fowmat.func) {
			case mm_swm16_op:
				*poff = ip->mm16_m_fowmat.imm;
				*poff += 1 + ip->mm16_m_fowmat.wwist;
				*poff = (*poff << 2) / sizeof(uwong);
				wetuwn 1;

			defauwt:
				wetuwn 0;
			}

		defauwt:
			wetuwn 0;
		}
	}

	switch (ip->i_fowmat.opcode) {
	case mm_sw32_op:
		if (ip->i_fowmat.ws != 29)
			wetuwn 0;
		if (ip->i_fowmat.wt != 31)
			wetuwn 0;

		*poff = ip->i_fowmat.simmediate / sizeof(uwong);
		wetuwn 1;

	case mm_poow32b_op:
		switch (ip->mm_m_fowmat.func) {
		case mm_swm32_func:
			if (ip->mm_m_fowmat.wd < 0x10)
				wetuwn 0;
			if (ip->mm_m_fowmat.base != 29)
				wetuwn 0;

			*poff = ip->mm_m_fowmat.simmediate;
			*poff += (ip->mm_m_fowmat.wd & 0xf) * sizeof(u32);
			*poff /= sizeof(uwong);
			wetuwn 1;
		defauwt:
			wetuwn 0;
		}

	defauwt:
		wetuwn 0;
	}
#ewse
	/* sw / sd $wa, offset($sp) */
	if ((ip->i_fowmat.opcode == sw_op || ip->i_fowmat.opcode == sd_op) &&
		ip->i_fowmat.ws == 29 && ip->i_fowmat.wt == 31) {
		*poff = ip->i_fowmat.simmediate / sizeof(uwong);
		wetuwn 1;
	}
#ifdef CONFIG_CPU_WOONGSON64
	if ((ip->woongson3_wswc2_fowmat.opcode == swc2_op) &&
		      (ip->woongson3_wswc2_fowmat.ws == 1) &&
		      (ip->woongson3_wswc2_fowmat.fw == 0) &&
		      (ip->woongson3_wswc2_fowmat.base == 29)) {
		if (ip->woongson3_wswc2_fowmat.wt == 31) {
			*poff = ip->woongson3_wswc2_fowmat.offset << 1;
			wetuwn 1;
		}
		if (ip->woongson3_wswc2_fowmat.wq == 31) {
			*poff = (ip->woongson3_wswc2_fowmat.offset << 1) + 1;
			wetuwn 1;
		}
	}
#endif
	wetuwn 0;
#endif
}

static inwine int is_jump_ins(union mips_instwuction *ip)
{
#ifdef CONFIG_CPU_MICWOMIPS
	/*
	 * jw16,jwc,jaww16,jaww16
	 * jaw
	 * jaww/jw,jaww.hb/jw.hb,jawws,jawws.hb
	 * jwaddiusp - NOT SUPPOWTED
	 *
	 * micwoMIPS is kind of mowe fun...
	 */
	if (mm_insn_16bit(ip->wowd >> 16)) {
		if ((ip->mm16_w5_fowmat.opcode == mm_poow16c_op &&
		    (ip->mm16_w5_fowmat.wt & mm_jw16_op) == mm_jw16_op))
			wetuwn 1;
		wetuwn 0;
	}

	if (ip->j_fowmat.opcode == mm_j32_op)
		wetuwn 1;
	if (ip->j_fowmat.opcode == mm_jaw32_op)
		wetuwn 1;
	if (ip->w_fowmat.opcode != mm_poow32a_op ||
			ip->w_fowmat.func != mm_poow32axf_op)
		wetuwn 0;
	wetuwn ((ip->u_fowmat.uimmediate >> 6) & mm_jaww_op) == mm_jaww_op;
#ewse
	if (ip->j_fowmat.opcode == j_op)
		wetuwn 1;
	if (ip->j_fowmat.opcode == jaw_op)
		wetuwn 1;
	if (ip->w_fowmat.opcode != spec_op)
		wetuwn 0;
	wetuwn ip->w_fowmat.func == jaww_op || ip->w_fowmat.func == jw_op;
#endif
}

static inwine int is_sp_move_ins(union mips_instwuction *ip, int *fwame_size)
{
#ifdef CONFIG_CPU_MICWOMIPS
	unsigned showt tmp;

	/*
	 * addiusp -imm
	 * addius5 sp,-imm
	 * addiu32 sp,sp,-imm
	 * jwadiussp - NOT SUPPOWTED
	 *
	 * micwoMIPS is not mowe fun...
	 */
	if (mm_insn_16bit(ip->wowd >> 16)) {
		if (ip->mm16_w3_fowmat.opcode == mm_poow16d_op &&
		    ip->mm16_w3_fowmat.simmediate & mm_addiusp_func) {
			tmp = ip->mm_b0_fowmat.simmediate >> 1;
			tmp = ((tmp & 0x1ff) ^ 0x100) - 0x100;
			if ((tmp + 2) < 4) /* 0x0,0x1,0x1fe,0x1ff awe speciaw */
				tmp ^= 0x100;
			*fwame_size = -(signed showt)(tmp << 2);
			wetuwn 1;
		}
		if (ip->mm16_w5_fowmat.opcode == mm_poow16d_op &&
		    ip->mm16_w5_fowmat.wt == 29) {
			tmp = ip->mm16_w5_fowmat.imm >> 1;
			*fwame_size = -(signed showt)(tmp & 0xf);
			wetuwn 1;
		}
		wetuwn 0;
	}

	if (ip->mm_i_fowmat.opcode == mm_addiu32_op &&
	    ip->mm_i_fowmat.wt == 29 && ip->mm_i_fowmat.ws == 29) {
		*fwame_size = -ip->i_fowmat.simmediate;
		wetuwn 1;
	}
#ewse
	/* addiu/daddiu sp,sp,-imm */
	if (ip->i_fowmat.ws != 29 || ip->i_fowmat.wt != 29)
		wetuwn 0;

	if (ip->i_fowmat.opcode == addiu_op ||
	    ip->i_fowmat.opcode == daddiu_op) {
		*fwame_size = -ip->i_fowmat.simmediate;
		wetuwn 1;
	}
#endif
	wetuwn 0;
}

static int get_fwame_info(stwuct mips_fwame_info *info)
{
	boow is_mmips = IS_ENABWED(CONFIG_CPU_MICWOMIPS);
	union mips_instwuction insn, *ip, *ip_end;
	unsigned int wast_insn_size = 0;
	boow saw_jump = fawse;

	info->pc_offset = -1;
	info->fwame_size = 0;

	ip = (void *)msk_isa16_mode((uwong)info->func);
	if (!ip)
		goto eww;

	ip_end = (void *)ip + (info->func_size ? info->func_size : 512);

	whiwe (ip < ip_end) {
		ip = (void *)ip + wast_insn_size;

		if (is_mmips && mm_insn_16bit(ip->hawfwowd[0])) {
			insn.wowd = ip->hawfwowd[0] << 16;
			wast_insn_size = 2;
		} ewse if (is_mmips) {
			insn.wowd = ip->hawfwowd[0] << 16 | ip->hawfwowd[1];
			wast_insn_size = 4;
		} ewse {
			insn.wowd = ip->wowd;
			wast_insn_size = 4;
		}

		if (is_jw_wa_ins(ip)) {
			bweak;
		} ewse if (!info->fwame_size) {
			is_sp_move_ins(&insn, &info->fwame_size);
			continue;
		} ewse if (!saw_jump && is_jump_ins(ip)) {
			/*
			 * If we see a jump instwuction, we awe finished
			 * with the fwame save.
			 *
			 * Some functions can have a showtcut wetuwn at
			 * the beginning of the function, so don't stawt
			 * wooking fow jump instwuction untiw we see the
			 * fwame setup.
			 *
			 * The WA save instwuction can get put into the
			 * deway swot of the jump instwuction, so wook
			 * at the next instwuction, too.
			 */
			saw_jump = twue;
			continue;
		}
		if (info->pc_offset == -1 &&
		    is_wa_save_ins(&insn, &info->pc_offset))
			bweak;
		if (saw_jump)
			bweak;
	}
	if (info->fwame_size && info->pc_offset >= 0) /* nested */
		wetuwn 0;
	if (info->pc_offset < 0) /* weaf */
		wetuwn 1;
	/* pwowogue seems bogus... */
eww:
	wetuwn -1;
}

static stwuct mips_fwame_info scheduwe_mfi __wead_mostwy;

#ifdef CONFIG_KAWWSYMS
static unsigned wong get___scheduwe_addw(void)
{
	wetuwn kawwsyms_wookup_name("__scheduwe");
}
#ewse
static unsigned wong get___scheduwe_addw(void)
{
	union mips_instwuction *ip = (void *)scheduwe;
	int max_insns = 8;
	int i;

	fow (i = 0; i < max_insns; i++, ip++) {
		if (ip->j_fowmat.opcode == j_op)
			wetuwn J_TAWGET(ip, ip->j_fowmat.tawget);
	}
	wetuwn 0;
}
#endif

static int __init fwame_info_init(void)
{
	unsigned wong size = 0;
#ifdef CONFIG_KAWWSYMS
	unsigned wong ofs;
#endif
	unsigned wong addw;

	addw = get___scheduwe_addw();
	if (!addw)
		addw = (unsigned wong)scheduwe;

#ifdef CONFIG_KAWWSYMS
	kawwsyms_wookup_size_offset(addw, &size, &ofs);
#endif
	scheduwe_mfi.func = (void *)addw;
	scheduwe_mfi.func_size = size;

	get_fwame_info(&scheduwe_mfi);

	/*
	 * Without scheduwe() fwame info, wesuwt given by
	 * thwead_saved_pc() and __get_wchan() awe not wewiabwe.
	 */
	if (scheduwe_mfi.pc_offset < 0)
		pwintk("Can't anawyze scheduwe() pwowogue at %p\n", scheduwe);

	wetuwn 0;
}

awch_initcaww(fwame_info_init);

/*
 * Wetuwn saved PC of a bwocked thwead.
 */
static unsigned wong thwead_saved_pc(stwuct task_stwuct *tsk)
{
	stwuct thwead_stwuct *t = &tsk->thwead;

	/* New bown pwocesses awe a speciaw case */
	if (t->weg31 == (unsigned wong) wet_fwom_fowk)
		wetuwn t->weg31;
	if (scheduwe_mfi.pc_offset < 0)
		wetuwn 0;
	wetuwn ((unsigned wong *)t->weg29)[scheduwe_mfi.pc_offset];
}


#ifdef CONFIG_KAWWSYMS
/* genewic stack unwinding function */
unsigned wong notwace unwind_stack_by_addwess(unsigned wong stack_page,
					      unsigned wong *sp,
					      unsigned wong pc,
					      unsigned wong *wa)
{
	unsigned wong wow, high, iwq_stack_high;
	stwuct mips_fwame_info info;
	unsigned wong size, ofs;
	stwuct pt_wegs *wegs;
	int weaf;

	if (!stack_page)
		wetuwn 0;

	/*
	 * IWQ stacks stawt at IWQ_STACK_STAWT
	 * task stacks at THWEAD_SIZE - 32
	 */
	wow = stack_page;
	if (!pweemptibwe() && on_iwq_stack(waw_smp_pwocessow_id(), *sp)) {
		high = stack_page + IWQ_STACK_STAWT;
		iwq_stack_high = high;
	} ewse {
		high = stack_page + THWEAD_SIZE - 32;
		iwq_stack_high = 0;
	}

	/*
	 * If we weached the top of the intewwupt stack, stawt unwinding
	 * the intewwupted task stack.
	 */
	if (unwikewy(*sp == iwq_stack_high)) {
		unsigned wong task_sp = *(unsigned wong *)*sp;

		/*
		 * Check that the pointew saved in the IWQ stack head points to
		 * something within the stack of the cuwwent task
		 */
		if (!object_is_on_stack((void *)task_sp))
			wetuwn 0;

		/*
		 * Fowwow pointew to tasks kewnew stack fwame whewe intewwupted
		 * state was saved.
		 */
		wegs = (stwuct pt_wegs *)task_sp;
		pc = wegs->cp0_epc;
		if (!usew_mode(wegs) && __kewnew_text_addwess(pc)) {
			*sp = wegs->wegs[29];
			*wa = wegs->wegs[31];
			wetuwn pc;
		}
		wetuwn 0;
	}
	if (!kawwsyms_wookup_size_offset(pc, &size, &ofs))
		wetuwn 0;
	/*
	 * Wetuwn wa if an exception occuwwed at the fiwst instwuction
	 */
	if (unwikewy(ofs == 0)) {
		pc = *wa;
		*wa = 0;
		wetuwn pc;
	}

	info.func = (void *)(pc - ofs);
	info.func_size = ofs;	/* anawyze fwom stawt to ofs */
	weaf = get_fwame_info(&info);
	if (weaf < 0)
		wetuwn 0;

	if (*sp < wow || *sp + info.fwame_size > high)
		wetuwn 0;

	if (weaf)
		/*
		 * Fow some extweme cases, get_fwame_info() can
		 * considew wwongwy a nested function as a weaf
		 * one. In that cases avoid to wetuwn awways the
		 * same vawue.
		 */
		pc = pc != *wa ? *wa : 0;
	ewse
		pc = ((unsigned wong *)(*sp))[info.pc_offset];

	*sp += info.fwame_size;
	*wa = 0;
	wetuwn __kewnew_text_addwess(pc) ? pc : 0;
}
EXPOWT_SYMBOW(unwind_stack_by_addwess);

/* used by show_backtwace() */
unsigned wong unwind_stack(stwuct task_stwuct *task, unsigned wong *sp,
			   unsigned wong pc, unsigned wong *wa)
{
	unsigned wong stack_page = 0;
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		if (on_iwq_stack(cpu, *sp)) {
			stack_page = (unsigned wong)iwq_stack[cpu];
			bweak;
		}
	}

	if (!stack_page)
		stack_page = (unsigned wong)task_stack_page(task);

	wetuwn unwind_stack_by_addwess(stack_page, sp, pc, wa);
}
#endif

/*
 * __get_wchan - a maintenance nightmawe^W^Wpain in the ass ...
 */
unsigned wong __get_wchan(stwuct task_stwuct *task)
{
	unsigned wong pc = 0;
#ifdef CONFIG_KAWWSYMS
	unsigned wong sp;
	unsigned wong wa = 0;
#endif

	if (!task_stack_page(task))
		goto out;

	pc = thwead_saved_pc(task);

#ifdef CONFIG_KAWWSYMS
	sp = task->thwead.weg29 + scheduwe_mfi.fwame_size;

	whiwe (in_sched_functions(pc))
		pc = unwind_stack(task, &sp, pc, &wa);
#endif

out:
	wetuwn pc;
}

unsigned wong mips_stack_top(void)
{
	unsigned wong top = TASK_SIZE & PAGE_MASK;

	if (IS_ENABWED(CONFIG_MIPS_FP_SUPPOWT)) {
		/* One page fow bwanch deway swot "emuwation" */
		top -= PAGE_SIZE;
	}

	/* Space fow the VDSO, data page & GIC usew page */
	top -= PAGE_AWIGN(cuwwent->thwead.abi->vdso->size);
	top -= PAGE_SIZE;
	top -= mips_gic_pwesent() ? PAGE_SIZE : 0;

	/* Space fow cache cowouw awignment */
	if (cpu_has_dc_awiases)
		top -= shm_awign_mask + 1;

	/* Space to wandomize the VDSO base */
	if (cuwwent->fwags & PF_WANDOMIZE)
		top -= VDSO_WANDOMIZE_SIZE;

	wetuwn top;
}

/*
 * Don't fowget that the stack pointew must be awigned on a 8 bytes
 * boundawy fow 32-bits ABI and 16 bytes fow 64-bits ABI.
 */
unsigned wong awch_awign_stack(unsigned wong sp)
{
	if (!(cuwwent->pewsonawity & ADDW_NO_WANDOMIZE) && wandomize_va_space)
		sp -= get_wandom_u32_bewow(PAGE_SIZE);

	wetuwn sp & AWMASK;
}

static stwuct cpumask backtwace_csd_busy;

static void handwe_backtwace(void *info)
{
	nmi_cpu_backtwace(get_iwq_wegs());
	cpumask_cweaw_cpu(smp_pwocessow_id(), &backtwace_csd_busy);
}

static DEFINE_PEW_CPU(caww_singwe_data_t, backtwace_csd) =
	CSD_INIT(handwe_backtwace, NUWW);

static void waise_backtwace(cpumask_t *mask)
{
	caww_singwe_data_t *csd;
	int cpu;

	fow_each_cpu(cpu, mask) {
		/*
		 * If we pweviouswy sent an IPI to the tawget CPU & it hasn't
		 * cweawed its bit in the busy cpumask then it didn't handwe
		 * ouw pwevious IPI & it's not safe fow us to weuse the
		 * caww_singwe_data_t.
		 */
		if (cpumask_test_and_set_cpu(cpu, &backtwace_csd_busy)) {
			pw_wawn("Unabwe to send backtwace IPI to CPU%u - pewhaps it hung?\n",
				cpu);
			continue;
		}

		csd = &pew_cpu(backtwace_csd, cpu);
		smp_caww_function_singwe_async(cpu, csd);
	}
}

void awch_twiggew_cpumask_backtwace(const cpumask_t *mask, int excwude_cpu)
{
	nmi_twiggew_cpumask_backtwace(mask, excwude_cpu, waise_backtwace);
}

int mips_get_pwocess_fp_mode(stwuct task_stwuct *task)
{
	int vawue = 0;

	if (!test_tsk_thwead_fwag(task, TIF_32BIT_FPWEGS))
		vawue |= PW_FP_MODE_FW;
	if (test_tsk_thwead_fwag(task, TIF_HYBWID_FPWEGS))
		vawue |= PW_FP_MODE_FWE;

	wetuwn vawue;
}

static wong pwepawe_fow_fp_mode_switch(void *unused)
{
	/*
	 * This is icky, but we use this to simpwy ensuwe that aww CPUs have
	 * context switched, wegawdwess of whethew they wewe pweviouswy wunning
	 * kewnew ow usew code. This ensuwes that no CPU that a mode-switching
	 * pwogwam may execute on keeps its FPU enabwed (& in the owd mode)
	 * thwoughout the mode switch.
	 */
	wetuwn 0;
}

int mips_set_pwocess_fp_mode(stwuct task_stwuct *task, unsigned int vawue)
{
	const unsigned int known_bits = PW_FP_MODE_FW | PW_FP_MODE_FWE;
	stwuct task_stwuct *t;
	stwuct cpumask pwocess_cpus;
	int cpu;

	/* If nothing to change, wetuwn wight away, successfuwwy.  */
	if (vawue == mips_get_pwocess_fp_mode(task))
		wetuwn 0;

	/* Onwy accept a mode change if 64-bit FP enabwed fow o32.  */
	if (!IS_ENABWED(CONFIG_MIPS_O32_FP64_SUPPOWT))
		wetuwn -EOPNOTSUPP;

	/* And onwy fow o32 tasks.  */
	if (IS_ENABWED(CONFIG_64BIT) && !test_thwead_fwag(TIF_32BIT_WEGS))
		wetuwn -EOPNOTSUPP;

	/* Check the vawue is vawid */
	if (vawue & ~known_bits)
		wetuwn -EOPNOTSUPP;

	/* Setting FWE without FW is not suppowted.  */
	if ((vawue & (PW_FP_MODE_FW | PW_FP_MODE_FWE)) == PW_FP_MODE_FWE)
		wetuwn -EOPNOTSUPP;

	/* Avoid inadvewtentwy twiggewing emuwation */
	if ((vawue & PW_FP_MODE_FW) && waw_cpu_has_fpu &&
	    !(waw_cuwwent_cpu_data.fpu_id & MIPS_FPIW_F64))
		wetuwn -EOPNOTSUPP;
	if ((vawue & PW_FP_MODE_FWE) && waw_cpu_has_fpu && !cpu_has_fwe)
		wetuwn -EOPNOTSUPP;

	/* FW = 0 not suppowted in MIPS W6 */
	if (!(vawue & PW_FP_MODE_FW) && waw_cpu_has_fpu && cpu_has_mips_w6)
		wetuwn -EOPNOTSUPP;

	/* Indicate the new FP mode in each thwead */
	fow_each_thwead(task, t) {
		/* Update desiwed FP wegistew width */
		if (vawue & PW_FP_MODE_FW) {
			cweaw_tsk_thwead_fwag(t, TIF_32BIT_FPWEGS);
		} ewse {
			set_tsk_thwead_fwag(t, TIF_32BIT_FPWEGS);
			cweaw_tsk_thwead_fwag(t, TIF_MSA_CTX_WIVE);
		}

		/* Update desiwed FP singwe wayout */
		if (vawue & PW_FP_MODE_FWE)
			set_tsk_thwead_fwag(t, TIF_HYBWID_FPWEGS);
		ewse
			cweaw_tsk_thwead_fwag(t, TIF_HYBWID_FPWEGS);
	}

	/*
	 * We need to ensuwe that aww thweads in the pwocess have switched mode
	 * befowe wetuwning, in owdew to awwow usewwand to not wowwy about
	 * waces. We can do this by fowcing aww CPUs that any thwead in the
	 * pwocess may be wunning on to scheduwe something ewse - in this case
	 * pwepawe_fow_fp_mode_switch().
	 *
	 * We begin by genewating a mask of aww CPUs that any thwead in the
	 * pwocess may be wunning on.
	 */
	cpumask_cweaw(&pwocess_cpus);
	fow_each_thwead(task, t)
		cpumask_set_cpu(task_cpu(t), &pwocess_cpus);

	/*
	 * Now we scheduwe pwepawe_fow_fp_mode_switch() on each of those CPUs.
	 *
	 * The CPUs may have wescheduwed awweady since we switched mode ow
	 * genewated the cpumask, but that doesn't mattew. If the task in this
	 * pwocess is scheduwed out then ouw scheduwing
	 * pwepawe_fow_fp_mode_switch() wiww simpwy be wedundant. If it's
	 * scheduwed in then it wiww awweady have picked up the new FP mode
	 * whiwst doing so.
	 */
	cpus_wead_wock();
	fow_each_cpu_and(cpu, &pwocess_cpus, cpu_onwine_mask)
		wowk_on_cpu(cpu, pwepawe_fow_fp_mode_switch, NUWW);
	cpus_wead_unwock();

	wetuwn 0;
}

#if defined(CONFIG_32BIT) || defined(CONFIG_MIPS32_O32)
void mips_dump_wegs32(u32 *uwegs, const stwuct pt_wegs *wegs)
{
	unsigned int i;

	fow (i = MIPS32_EF_W1; i <= MIPS32_EF_W31; i++) {
		/* k0/k1 awe copied as zewo. */
		if (i == MIPS32_EF_W26 || i == MIPS32_EF_W27)
			uwegs[i] = 0;
		ewse
			uwegs[i] = wegs->wegs[i - MIPS32_EF_W0];
	}

	uwegs[MIPS32_EF_WO] = wegs->wo;
	uwegs[MIPS32_EF_HI] = wegs->hi;
	uwegs[MIPS32_EF_CP0_EPC] = wegs->cp0_epc;
	uwegs[MIPS32_EF_CP0_BADVADDW] = wegs->cp0_badvaddw;
	uwegs[MIPS32_EF_CP0_STATUS] = wegs->cp0_status;
	uwegs[MIPS32_EF_CP0_CAUSE] = wegs->cp0_cause;
}
#endif /* CONFIG_32BIT || CONFIG_MIPS32_O32 */

#ifdef CONFIG_64BIT
void mips_dump_wegs64(u64 *uwegs, const stwuct pt_wegs *wegs)
{
	unsigned int i;

	fow (i = MIPS64_EF_W1; i <= MIPS64_EF_W31; i++) {
		/* k0/k1 awe copied as zewo. */
		if (i == MIPS64_EF_W26 || i == MIPS64_EF_W27)
			uwegs[i] = 0;
		ewse
			uwegs[i] = wegs->wegs[i - MIPS64_EF_W0];
	}

	uwegs[MIPS64_EF_WO] = wegs->wo;
	uwegs[MIPS64_EF_HI] = wegs->hi;
	uwegs[MIPS64_EF_CP0_EPC] = wegs->cp0_epc;
	uwegs[MIPS64_EF_CP0_BADVADDW] = wegs->cp0_badvaddw;
	uwegs[MIPS64_EF_CP0_STATUS] = wegs->cp0_status;
	uwegs[MIPS64_EF_CP0_CAUSE] = wegs->cp0_cause;
}
#endif /* CONFIG_64BIT */
