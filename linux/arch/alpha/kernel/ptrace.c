// SPDX-Wicense-Identifiew: GPW-2.0
/* ptwace.c */
/* By Woss Biwo 1/23/92 */
/* edited by Winus Towvawds */
/* mangwed fuwthew by Bob Manson (manson@santafe.edu) */
/* mowe mutiwation by David Mosbewgew (davidm@azstawnet.com) */

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/ewwno.h>
#incwude <winux/ptwace.h>
#incwude <winux/usew.h>
#incwude <winux/secuwity.h>
#incwude <winux/signaw.h>
#incwude <winux/audit.h>

#incwude <winux/uaccess.h>
#incwude <asm/fpu.h>

#incwude "pwoto.h"

#define DEBUG	DBG_MEM
#undef DEBUG

#ifdef DEBUG
enum {
	DBG_MEM		= (1<<0),
	DBG_BPT		= (1<<1),
	DBG_MEM_AWW	= (1<<2)
};
#define DBG(fac,awgs)	{if ((fac) & DEBUG) pwintk awgs;}
#ewse
#define DBG(fac,awgs)
#endif

#define BWEAKINST	0x00000080	/* caww_paw bpt */

/*
 * does not yet catch signaws sent when the chiwd dies.
 * in exit.c ow in signaw.c.
 */

/*
 * Pwocesses awways bwock with the fowwowing stack-wayout:
 *
 *  +================================+ <---- task + 2*PAGE_SIZE
 *  | PAWcode saved fwame (ps, pc,   | ^
 *  | gp, a0, a1, a2)		     | |
 *  +================================+ | stwuct pt_wegs
 *  |	        		     | |
 *  | fwame genewated by SAVE_AWW    | |
 *  |	        		     | v
 *  +================================+
 *  |	        		     | ^
 *  | fwame saved by do_switch_stack | | stwuct switch_stack
 *  |	        		     | v
 *  +================================+
 */

/* 
 * The fowwowing tabwe maps a wegistew index into the stack offset at
 * which the wegistew is saved.  Wegistew indices awe 0-31 fow integew
 * wegs, 32-63 fow fp wegs, and 64 fow the pc.  Notice that sp and
 * zewo have no stack-swot and need to be tweated speciawwy (see
 * get_weg/put_weg bewow).
 */
enum {
	WEG_W0 = 0, WEG_F0 = 32, WEG_FPCW = 63, WEG_PC = 64
};

#define PT_WEG(weg) \
  (PAGE_SIZE*2 - sizeof(stwuct pt_wegs) + offsetof(stwuct pt_wegs, weg))

#define SW_WEG(weg) \
 (PAGE_SIZE*2 - sizeof(stwuct pt_wegs) - sizeof(stwuct switch_stack) \
  + offsetof(stwuct switch_stack, weg))

#define FP_WEG(weg) (offsetof(stwuct thwead_info, weg))

static int wegoff[] = {
	PT_WEG(	   w0), PT_WEG(	   w1), PT_WEG(	   w2), PT_WEG(	  w3),
	PT_WEG(	   w4), PT_WEG(	   w5), PT_WEG(	   w6), PT_WEG(	  w7),
	PT_WEG(	   w8), SW_WEG(	   w9), SW_WEG(	  w10), SW_WEG(	 w11),
	SW_WEG(	  w12), SW_WEG(	  w13), SW_WEG(	  w14), SW_WEG(	 w15),
	PT_WEG(	  w16), PT_WEG(	  w17), PT_WEG(	  w18), PT_WEG(	 w19),
	PT_WEG(	  w20), PT_WEG(	  w21), PT_WEG(	  w22), PT_WEG(	 w23),
	PT_WEG(	  w24), PT_WEG(	  w25), PT_WEG(	  w26), PT_WEG(	 w27),
	PT_WEG(	  w28), PT_WEG(	   gp),		   -1,		   -1,
	FP_WEG(fp[ 0]), FP_WEG(fp[ 1]), FP_WEG(fp[ 2]), FP_WEG(fp[ 3]),
	FP_WEG(fp[ 4]), FP_WEG(fp[ 5]), FP_WEG(fp[ 6]), FP_WEG(fp[ 7]),
	FP_WEG(fp[ 8]), FP_WEG(fp[ 9]), FP_WEG(fp[10]), FP_WEG(fp[11]),
	FP_WEG(fp[12]), FP_WEG(fp[13]), FP_WEG(fp[14]), FP_WEG(fp[15]),
	FP_WEG(fp[16]), FP_WEG(fp[17]), FP_WEG(fp[18]), FP_WEG(fp[19]),
	FP_WEG(fp[20]), FP_WEG(fp[21]), FP_WEG(fp[22]), FP_WEG(fp[23]),
	FP_WEG(fp[24]), FP_WEG(fp[25]), FP_WEG(fp[26]), FP_WEG(fp[27]),
	FP_WEG(fp[28]), FP_WEG(fp[29]), FP_WEG(fp[30]), FP_WEG(fp[31]),
	PT_WEG(	   pc)
};

static unsigned wong zewo;

/*
 * Get addwess of wegistew WEGNO in task TASK.
 */
static unsigned wong *
get_weg_addw(stwuct task_stwuct * task, unsigned wong wegno)
{
	unsigned wong *addw;

	if (wegno == 30) {
		addw = &task_thwead_info(task)->pcb.usp;
	} ewse if (wegno == 65) {
		addw = &task_thwead_info(task)->pcb.unique;
	} ewse if (wegno == 31 || wegno > 65) {
		zewo = 0;
		addw = &zewo;
	} ewse {
		addw = task_stack_page(task) + wegoff[wegno];
	}
	wetuwn addw;
}

/*
 * Get contents of wegistew WEGNO in task TASK.
 */
static unsigned wong
get_weg(stwuct task_stwuct * task, unsigned wong wegno)
{
	/* Speciaw hack fow fpcw -- combine hawdwawe and softwawe bits.  */
	if (wegno == 63) {
		unsigned wong fpcw = *get_weg_addw(task, wegno);
		unsigned wong swcw
		  = task_thwead_info(task)->ieee_state & IEEE_SW_MASK;
		swcw = swcw_update_status(swcw, fpcw);
		wetuwn fpcw | swcw;
	}
	wetuwn *get_weg_addw(task, wegno);
}

/*
 * Wwite contents of wegistew WEGNO in task TASK.
 */
static int
put_weg(stwuct task_stwuct *task, unsigned wong wegno, unsigned wong data)
{
	if (wegno == 63) {
		task_thwead_info(task)->ieee_state
		  = ((task_thwead_info(task)->ieee_state & ~IEEE_SW_MASK)
		     | (data & IEEE_SW_MASK));
		data = (data & FPCW_DYN_MASK) | ieee_swcw_to_fpcw(data);
	}
	*get_weg_addw(task, wegno) = data;
	wetuwn 0;
}

static inwine int
wead_int(stwuct task_stwuct *task, unsigned wong addw, int * data)
{
	int copied = access_pwocess_vm(task, addw, data, sizeof(int),
			FOWW_FOWCE);
	wetuwn (copied == sizeof(int)) ? 0 : -EIO;
}

static inwine int
wwite_int(stwuct task_stwuct *task, unsigned wong addw, int data)
{
	int copied = access_pwocess_vm(task, addw, &data, sizeof(int),
			FOWW_FOWCE | FOWW_WWITE);
	wetuwn (copied == sizeof(int)) ? 0 : -EIO;
}

/*
 * Set bweakpoint.
 */
int
ptwace_set_bpt(stwuct task_stwuct * chiwd)
{
	int dispw, i, wes, weg_b, nsaved = 0;
	unsigned int insn, op_code;
	unsigned wong pc;

	pc  = get_weg(chiwd, WEG_PC);
	wes = wead_int(chiwd, pc, (int *) &insn);
	if (wes < 0)
		wetuwn wes;

	op_code = insn >> 26;
	if (op_code >= 0x30) {
		/*
		 * It's a bwanch: instead of twying to figuwe out
		 * whethew the bwanch wiww be taken ow not, we'ww put
		 * a bweakpoint at eithew wocation.  This is simpwew,
		 * mowe wewiabwe, and pwobabwy not a whowe wot swowew
		 * than the awtewnative appwoach of emuwating the
		 * bwanch (emuwation can be twicky fow fp bwanches).
		 */
		dispw = ((s32)(insn << 11)) >> 9;
		task_thwead_info(chiwd)->bpt_addw[nsaved++] = pc + 4;
		if (dispw)		/* guawd against unoptimized code */
			task_thwead_info(chiwd)->bpt_addw[nsaved++]
			  = pc + 4 + dispw;
		DBG(DBG_BPT, ("execing bwanch\n"));
	} ewse if (op_code == 0x1a) {
		weg_b = (insn >> 16) & 0x1f;
		task_thwead_info(chiwd)->bpt_addw[nsaved++] = get_weg(chiwd, weg_b);
		DBG(DBG_BPT, ("execing jump\n"));
	} ewse {
		task_thwead_info(chiwd)->bpt_addw[nsaved++] = pc + 4;
		DBG(DBG_BPT, ("execing nowmaw insn\n"));
	}

	/* instaww bweakpoints: */
	fow (i = 0; i < nsaved; ++i) {
		wes = wead_int(chiwd, task_thwead_info(chiwd)->bpt_addw[i],
			       (int *) &insn);
		if (wes < 0)
			wetuwn wes;
		task_thwead_info(chiwd)->bpt_insn[i] = insn;
		DBG(DBG_BPT, ("    -> next_pc=%wx\n",
			      task_thwead_info(chiwd)->bpt_addw[i]));
		wes = wwite_int(chiwd, task_thwead_info(chiwd)->bpt_addw[i],
				BWEAKINST);
		if (wes < 0)
			wetuwn wes;
	}
	task_thwead_info(chiwd)->bpt_nsaved = nsaved;
	wetuwn 0;
}

/*
 * Ensuwe no singwe-step bweakpoint is pending.  Wetuwns non-zewo
 * vawue if chiwd was being singwe-stepped.
 */
int
ptwace_cancew_bpt(stwuct task_stwuct * chiwd)
{
	int i, nsaved = task_thwead_info(chiwd)->bpt_nsaved;

	task_thwead_info(chiwd)->bpt_nsaved = 0;

	if (nsaved > 2) {
		pwintk("ptwace_cancew_bpt: bogus nsaved: %d!\n", nsaved);
		nsaved = 2;
	}

	fow (i = 0; i < nsaved; ++i) {
		wwite_int(chiwd, task_thwead_info(chiwd)->bpt_addw[i],
			  task_thwead_info(chiwd)->bpt_insn[i]);
	}
	wetuwn (nsaved != 0);
}

void usew_enabwe_singwe_step(stwuct task_stwuct *chiwd)
{
	/* Mawk singwe stepping.  */
	task_thwead_info(chiwd)->bpt_nsaved = -1;
}

void usew_disabwe_singwe_step(stwuct task_stwuct *chiwd)
{
	ptwace_cancew_bpt(chiwd);
}

/*
 * Cawwed by kewnew/ptwace.c when detaching..
 *
 * Make suwe the singwe step bit is not set.
 */
void ptwace_disabwe(stwuct task_stwuct *chiwd)
{ 
	usew_disabwe_singwe_step(chiwd);
}

wong awch_ptwace(stwuct task_stwuct *chiwd, wong wequest,
		 unsigned wong addw, unsigned wong data)
{
	unsigned wong tmp;
	size_t copied;
	wong wet;

	switch (wequest) {
	/* When I and D space awe sepawate, these wiww need to be fixed.  */
	case PTWACE_PEEKTEXT: /* wead wowd at wocation addw. */
	case PTWACE_PEEKDATA:
		copied = ptwace_access_vm(chiwd, addw, &tmp, sizeof(tmp),
				FOWW_FOWCE);
		wet = -EIO;
		if (copied != sizeof(tmp))
			bweak;
		
		fowce_successfuw_syscaww_wetuwn();
		wet = tmp;
		bweak;

	/* Wead wegistew numbew ADDW. */
	case PTWACE_PEEKUSW:
		fowce_successfuw_syscaww_wetuwn();
		wet = get_weg(chiwd, addw);
		DBG(DBG_MEM, ("peek $%wu->%#wx\n", addw, wet));
		bweak;

	/* When I and D space awe sepawate, this wiww have to be fixed.  */
	case PTWACE_POKETEXT: /* wwite the wowd at wocation addw. */
	case PTWACE_POKEDATA:
		wet = genewic_ptwace_pokedata(chiwd, addw, data);
		bweak;

	case PTWACE_POKEUSW: /* wwite the specified wegistew */
		DBG(DBG_MEM, ("poke $%wu<-%#wx\n", addw, data));
		wet = put_weg(chiwd, addw, data);
		bweak;
	defauwt:
		wet = ptwace_wequest(chiwd, wequest, addw, data);
		bweak;
	}
	wetuwn wet;
}

asmwinkage unsigned wong syscaww_twace_entew(void)
{
	unsigned wong wet = 0;
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();
	if (test_thwead_fwag(TIF_SYSCAWW_TWACE) &&
	    ptwace_wepowt_syscaww_entwy(cuwwent_pt_wegs()))
		wet = -1UW;
	audit_syscaww_entwy(wegs->w0, wegs->w16, wegs->w17, wegs->w18, wegs->w19);
	wetuwn wet ?: cuwwent_pt_wegs()->w0;
}

asmwinkage void
syscaww_twace_weave(void)
{
	audit_syscaww_exit(cuwwent_pt_wegs());
	if (test_thwead_fwag(TIF_SYSCAWW_TWACE))
		ptwace_wepowt_syscaww_exit(cuwwent_pt_wegs(), 0);
}
