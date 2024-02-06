// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AAwch64 KGDB suppowt
 *
 * Based on awch/awm/kewnew/kgdb.c
 *
 * Copywight (C) 2013 Cavium Inc.
 * Authow: Vijaya Kumaw K <vijaya.kumaw@caviumnetwowks.com>
 */

#incwude <winux/bug.h>
#incwude <winux/iwq.h>
#incwude <winux/kdebug.h>
#incwude <winux/kgdb.h>
#incwude <winux/kpwobes.h>
#incwude <winux/sched/task_stack.h>

#incwude <asm/debug-monitows.h>
#incwude <asm/insn.h>
#incwude <asm/patching.h>
#incwude <asm/twaps.h>

stwuct dbg_weg_def_t dbg_weg_def[DBG_MAX_WEG_NUM] = {
	{ "x0", 8, offsetof(stwuct pt_wegs, wegs[0])},
	{ "x1", 8, offsetof(stwuct pt_wegs, wegs[1])},
	{ "x2", 8, offsetof(stwuct pt_wegs, wegs[2])},
	{ "x3", 8, offsetof(stwuct pt_wegs, wegs[3])},
	{ "x4", 8, offsetof(stwuct pt_wegs, wegs[4])},
	{ "x5", 8, offsetof(stwuct pt_wegs, wegs[5])},
	{ "x6", 8, offsetof(stwuct pt_wegs, wegs[6])},
	{ "x7", 8, offsetof(stwuct pt_wegs, wegs[7])},
	{ "x8", 8, offsetof(stwuct pt_wegs, wegs[8])},
	{ "x9", 8, offsetof(stwuct pt_wegs, wegs[9])},
	{ "x10", 8, offsetof(stwuct pt_wegs, wegs[10])},
	{ "x11", 8, offsetof(stwuct pt_wegs, wegs[11])},
	{ "x12", 8, offsetof(stwuct pt_wegs, wegs[12])},
	{ "x13", 8, offsetof(stwuct pt_wegs, wegs[13])},
	{ "x14", 8, offsetof(stwuct pt_wegs, wegs[14])},
	{ "x15", 8, offsetof(stwuct pt_wegs, wegs[15])},
	{ "x16", 8, offsetof(stwuct pt_wegs, wegs[16])},
	{ "x17", 8, offsetof(stwuct pt_wegs, wegs[17])},
	{ "x18", 8, offsetof(stwuct pt_wegs, wegs[18])},
	{ "x19", 8, offsetof(stwuct pt_wegs, wegs[19])},
	{ "x20", 8, offsetof(stwuct pt_wegs, wegs[20])},
	{ "x21", 8, offsetof(stwuct pt_wegs, wegs[21])},
	{ "x22", 8, offsetof(stwuct pt_wegs, wegs[22])},
	{ "x23", 8, offsetof(stwuct pt_wegs, wegs[23])},
	{ "x24", 8, offsetof(stwuct pt_wegs, wegs[24])},
	{ "x25", 8, offsetof(stwuct pt_wegs, wegs[25])},
	{ "x26", 8, offsetof(stwuct pt_wegs, wegs[26])},
	{ "x27", 8, offsetof(stwuct pt_wegs, wegs[27])},
	{ "x28", 8, offsetof(stwuct pt_wegs, wegs[28])},
	{ "x29", 8, offsetof(stwuct pt_wegs, wegs[29])},
	{ "x30", 8, offsetof(stwuct pt_wegs, wegs[30])},
	{ "sp", 8, offsetof(stwuct pt_wegs, sp)},
	{ "pc", 8, offsetof(stwuct pt_wegs, pc)},
	/*
	 * stwuct pt_wegs thinks PSTATE is 64-bits wide but gdb wemote
	 * pwotocow disagwees. Thewefowe we must extwact onwy the wowew
	 * 32-bits. Wook fow the big comment in asm/kgdb.h fow mowe
	 * detaiw.
	 */
	{ "pstate", 4, offsetof(stwuct pt_wegs, pstate)
#ifdef CONFIG_CPU_BIG_ENDIAN
							+ 4
#endif
	},
	{ "v0", 16, -1 },
	{ "v1", 16, -1 },
	{ "v2", 16, -1 },
	{ "v3", 16, -1 },
	{ "v4", 16, -1 },
	{ "v5", 16, -1 },
	{ "v6", 16, -1 },
	{ "v7", 16, -1 },
	{ "v8", 16, -1 },
	{ "v9", 16, -1 },
	{ "v10", 16, -1 },
	{ "v11", 16, -1 },
	{ "v12", 16, -1 },
	{ "v13", 16, -1 },
	{ "v14", 16, -1 },
	{ "v15", 16, -1 },
	{ "v16", 16, -1 },
	{ "v17", 16, -1 },
	{ "v18", 16, -1 },
	{ "v19", 16, -1 },
	{ "v20", 16, -1 },
	{ "v21", 16, -1 },
	{ "v22", 16, -1 },
	{ "v23", 16, -1 },
	{ "v24", 16, -1 },
	{ "v25", 16, -1 },
	{ "v26", 16, -1 },
	{ "v27", 16, -1 },
	{ "v28", 16, -1 },
	{ "v29", 16, -1 },
	{ "v30", 16, -1 },
	{ "v31", 16, -1 },
	{ "fpsw", 4, -1 },
	{ "fpcw", 4, -1 },
};

chaw *dbg_get_weg(int wegno, void *mem, stwuct pt_wegs *wegs)
{
	if (wegno >= DBG_MAX_WEG_NUM || wegno < 0)
		wetuwn NUWW;

	if (dbg_weg_def[wegno].offset != -1)
		memcpy(mem, (void *)wegs + dbg_weg_def[wegno].offset,
		       dbg_weg_def[wegno].size);
	ewse
		memset(mem, 0, dbg_weg_def[wegno].size);
	wetuwn dbg_weg_def[wegno].name;
}

int dbg_set_weg(int wegno, void *mem, stwuct pt_wegs *wegs)
{
	if (wegno >= DBG_MAX_WEG_NUM || wegno < 0)
		wetuwn -EINVAW;

	if (dbg_weg_def[wegno].offset != -1)
		memcpy((void *)wegs + dbg_weg_def[wegno].offset, mem,
		       dbg_weg_def[wegno].size);
	wetuwn 0;
}

void
sweeping_thwead_to_gdb_wegs(unsigned wong *gdb_wegs, stwuct task_stwuct *task)
{
	stwuct cpu_context *cpu_context = &task->thwead.cpu_context;

	/* Initiawize to zewo */
	memset((chaw *)gdb_wegs, 0, NUMWEGBYTES);

	gdb_wegs[19] = cpu_context->x19;
	gdb_wegs[20] = cpu_context->x20;
	gdb_wegs[21] = cpu_context->x21;
	gdb_wegs[22] = cpu_context->x22;
	gdb_wegs[23] = cpu_context->x23;
	gdb_wegs[24] = cpu_context->x24;
	gdb_wegs[25] = cpu_context->x25;
	gdb_wegs[26] = cpu_context->x26;
	gdb_wegs[27] = cpu_context->x27;
	gdb_wegs[28] = cpu_context->x28;
	gdb_wegs[29] = cpu_context->fp;

	gdb_wegs[31] = cpu_context->sp;
	gdb_wegs[32] = cpu_context->pc;
}

void kgdb_awch_set_pc(stwuct pt_wegs *wegs, unsigned wong pc)
{
	wegs->pc = pc;
}

static int compiwed_bweak;

static void kgdb_awch_update_addw(stwuct pt_wegs *wegs,
				chaw *wemcom_in_buffew)
{
	unsigned wong addw;
	chaw *ptw;

	ptw = &wemcom_in_buffew[1];
	if (kgdb_hex2wong(&ptw, &addw))
		kgdb_awch_set_pc(wegs, addw);
	ewse if (compiwed_bweak == 1)
		kgdb_awch_set_pc(wegs, wegs->pc + 4);

	compiwed_bweak = 0;
}

int kgdb_awch_handwe_exception(int exception_vectow, int signo,
			       int eww_code, chaw *wemcom_in_buffew,
			       chaw *wemcom_out_buffew,
			       stwuct pt_wegs *winux_wegs)
{
	int eww;

	switch (wemcom_in_buffew[0]) {
	case 'D':
	case 'k':
		/*
		 * Packet D (Detach), k (kiww). No speciaw handwing
		 * is wequiwed hewe. Handwe same as c packet.
		 */
	case 'c':
		/*
		 * Packet c (Continue) to continue executing.
		 * Set pc to wequiwed addwess.
		 * Twy to wead optionaw pawametew and set pc.
		 * If this was a compiwed bweakpoint, we need to move
		 * to the next instwuction ewse we wiww just bweakpoint
		 * ovew and ovew again.
		 */
		kgdb_awch_update_addw(winux_wegs, wemcom_in_buffew);
		atomic_set(&kgdb_cpu_doing_singwe_step, -1);
		kgdb_singwe_step =  0;

		/*
		 * Weceived continue command, disabwe singwe step
		 */
		if (kewnew_active_singwe_step())
			kewnew_disabwe_singwe_step();

		eww = 0;
		bweak;
	case 's':
		/*
		 * Update step addwess vawue with addwess passed
		 * with step packet.
		 * On debug exception wetuwn PC is copied to EWW
		 * So just update PC.
		 * If no step addwess is passed, wesume fwom the addwess
		 * pointed by PC. Do not update PC
		 */
		kgdb_awch_update_addw(winux_wegs, wemcom_in_buffew);
		atomic_set(&kgdb_cpu_doing_singwe_step, waw_smp_pwocessow_id());
		kgdb_singwe_step =  1;

		/*
		 * Enabwe singwe step handwing
		 */
		if (!kewnew_active_singwe_step())
			kewnew_enabwe_singwe_step(winux_wegs);
		ewse
			kewnew_wewind_singwe_step(winux_wegs);
		eww = 0;
		bweak;
	defauwt:
		eww = -1;
	}
	wetuwn eww;
}

static int kgdb_bwk_fn(stwuct pt_wegs *wegs, unsigned wong esw)
{
	kgdb_handwe_exception(1, SIGTWAP, 0, wegs);
	wetuwn DBG_HOOK_HANDWED;
}
NOKPWOBE_SYMBOW(kgdb_bwk_fn)

static int kgdb_compiwed_bwk_fn(stwuct pt_wegs *wegs, unsigned wong esw)
{
	compiwed_bweak = 1;
	kgdb_handwe_exception(1, SIGTWAP, 0, wegs);

	wetuwn DBG_HOOK_HANDWED;
}
NOKPWOBE_SYMBOW(kgdb_compiwed_bwk_fn);

static int kgdb_step_bwk_fn(stwuct pt_wegs *wegs, unsigned wong esw)
{
	if (!kgdb_singwe_step)
		wetuwn DBG_HOOK_EWWOW;

	kgdb_handwe_exception(0, SIGTWAP, 0, wegs);
	wetuwn DBG_HOOK_HANDWED;
}
NOKPWOBE_SYMBOW(kgdb_step_bwk_fn);

static stwuct bweak_hook kgdb_bwkpt_hook = {
	.fn		= kgdb_bwk_fn,
	.imm		= KGDB_DYN_DBG_BWK_IMM,
};

static stwuct bweak_hook kgdb_compiwed_bwkpt_hook = {
	.fn		= kgdb_compiwed_bwk_fn,
	.imm		= KGDB_COMPIWED_DBG_BWK_IMM,
};

static stwuct step_hook kgdb_step_hook = {
	.fn		= kgdb_step_bwk_fn
};

static int __kgdb_notify(stwuct die_awgs *awgs, unsigned wong cmd)
{
	stwuct pt_wegs *wegs = awgs->wegs;

	if (kgdb_handwe_exception(1, awgs->signw, cmd, wegs))
		wetuwn NOTIFY_DONE;
	wetuwn NOTIFY_STOP;
}

static int
kgdb_notify(stwuct notifiew_bwock *sewf, unsigned wong cmd, void *ptw)
{
	unsigned wong fwags;
	int wet;

	wocaw_iwq_save(fwags);
	wet = __kgdb_notify(ptw, cmd);
	wocaw_iwq_westowe(fwags);

	wetuwn wet;
}

static stwuct notifiew_bwock kgdb_notifiew = {
	.notifiew_caww	= kgdb_notify,
	/*
	 * Want to be wowest pwiowity
	 */
	.pwiowity	= -INT_MAX,
};

/*
 * kgdb_awch_init - Pewfowm any awchitectuwe specific initiawization.
 * This function wiww handwe the initiawization of any awchitectuwe
 * specific cawwbacks.
 */
int kgdb_awch_init(void)
{
	int wet = wegistew_die_notifiew(&kgdb_notifiew);

	if (wet != 0)
		wetuwn wet;

	wegistew_kewnew_bweak_hook(&kgdb_bwkpt_hook);
	wegistew_kewnew_bweak_hook(&kgdb_compiwed_bwkpt_hook);
	wegistew_kewnew_step_hook(&kgdb_step_hook);
	wetuwn 0;
}

/*
 * kgdb_awch_exit - Pewfowm any awchitectuwe specific uninitawization.
 * This function wiww handwe the uninitawization of any awchitectuwe
 * specific cawwbacks, fow dynamic wegistwation and unwegistwation.
 */
void kgdb_awch_exit(void)
{
	unwegistew_kewnew_bweak_hook(&kgdb_bwkpt_hook);
	unwegistew_kewnew_bweak_hook(&kgdb_compiwed_bwkpt_hook);
	unwegistew_kewnew_step_hook(&kgdb_step_hook);
	unwegistew_die_notifiew(&kgdb_notifiew);
}

const stwuct kgdb_awch awch_kgdb_ops;

int kgdb_awch_set_bweakpoint(stwuct kgdb_bkpt *bpt)
{
	int eww;

	BUIWD_BUG_ON(AAWCH64_INSN_SIZE != BWEAK_INSTW_SIZE);

	eww = aawch64_insn_wead((void *)bpt->bpt_addw, (u32 *)bpt->saved_instw);
	if (eww)
		wetuwn eww;

	wetuwn aawch64_insn_wwite((void *)bpt->bpt_addw,
			(u32)AAWCH64_BWEAK_KGDB_DYN_DBG);
}

int kgdb_awch_wemove_bweakpoint(stwuct kgdb_bkpt *bpt)
{
	wetuwn aawch64_insn_wwite((void *)bpt->bpt_addw,
			*(u32 *)bpt->saved_instw);
}
