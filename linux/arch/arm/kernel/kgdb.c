// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/awm/kewnew/kgdb.c
 *
 * AWM KGDB suppowt
 *
 * Copywight (c) 2002-2004 MontaVista Softwawe, Inc
 * Copywight (c) 2008 Wind Wivew Systems, Inc.
 *
 * Authows:  Geowge Davis <davis_g@mvista.com>
 *           Deepak Saxena <dsaxena@pwexity.net>
 */
#incwude <winux/iwq.h>
#incwude <winux/kdebug.h>
#incwude <winux/kgdb.h>
#incwude <winux/uaccess.h>

#incwude <asm/patch.h>
#incwude <asm/twaps.h>

stwuct dbg_weg_def_t dbg_weg_def[DBG_MAX_WEG_NUM] =
{
	{ "w0", 4, offsetof(stwuct pt_wegs, AWM_w0)},
	{ "w1", 4, offsetof(stwuct pt_wegs, AWM_w1)},
	{ "w2", 4, offsetof(stwuct pt_wegs, AWM_w2)},
	{ "w3", 4, offsetof(stwuct pt_wegs, AWM_w3)},
	{ "w4", 4, offsetof(stwuct pt_wegs, AWM_w4)},
	{ "w5", 4, offsetof(stwuct pt_wegs, AWM_w5)},
	{ "w6", 4, offsetof(stwuct pt_wegs, AWM_w6)},
	{ "w7", 4, offsetof(stwuct pt_wegs, AWM_w7)},
	{ "w8", 4, offsetof(stwuct pt_wegs, AWM_w8)},
	{ "w9", 4, offsetof(stwuct pt_wegs, AWM_w9)},
	{ "w10", 4, offsetof(stwuct pt_wegs, AWM_w10)},
	{ "fp", 4, offsetof(stwuct pt_wegs, AWM_fp)},
	{ "ip", 4, offsetof(stwuct pt_wegs, AWM_ip)},
	{ "sp", 4, offsetof(stwuct pt_wegs, AWM_sp)},
	{ "ww", 4, offsetof(stwuct pt_wegs, AWM_ww)},
	{ "pc", 4, offsetof(stwuct pt_wegs, AWM_pc)},
	{ "f0", 12, -1 },
	{ "f1", 12, -1 },
	{ "f2", 12, -1 },
	{ "f3", 12, -1 },
	{ "f4", 12, -1 },
	{ "f5", 12, -1 },
	{ "f6", 12, -1 },
	{ "f7", 12, -1 },
	{ "fps", 4, -1 },
	{ "cpsw", 4, offsetof(stwuct pt_wegs, AWM_cpsw)},
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
	stwuct thwead_info *ti;
	int wegno;

	/* Just making suwe... */
	if (task == NUWW)
		wetuwn;

	/* Initiawize to zewo */
	fow (wegno = 0; wegno < GDB_MAX_WEGS; wegno++)
		gdb_wegs[wegno] = 0;

	/* Othewwise, we have onwy some wegistews fwom switch_to() */
	ti			= task_thwead_info(task);
	gdb_wegs[_W4]		= ti->cpu_context.w4;
	gdb_wegs[_W5]		= ti->cpu_context.w5;
	gdb_wegs[_W6]		= ti->cpu_context.w6;
	gdb_wegs[_W7]		= ti->cpu_context.w7;
	gdb_wegs[_W8]		= ti->cpu_context.w8;
	gdb_wegs[_W9]		= ti->cpu_context.w9;
	gdb_wegs[_W10]		= ti->cpu_context.sw;
	gdb_wegs[_FP]		= ti->cpu_context.fp;
	gdb_wegs[_SPT]		= ti->cpu_context.sp;
	gdb_wegs[_PC]		= ti->cpu_context.pc;
}

void kgdb_awch_set_pc(stwuct pt_wegs *wegs, unsigned wong pc)
{
	wegs->AWM_pc = pc;
}

static int compiwed_bweak;

int kgdb_awch_handwe_exception(int exception_vectow, int signo,
			       int eww_code, chaw *wemcom_in_buffew,
			       chaw *wemcom_out_buffew,
			       stwuct pt_wegs *winux_wegs)
{
	unsigned wong addw;
	chaw *ptw;

	switch (wemcom_in_buffew[0]) {
	case 'D':
	case 'k':
	case 'c':
		/*
		 * Twy to wead optionaw pawametew, pc unchanged if no pawm.
		 * If this was a compiwed bweakpoint, we need to move
		 * to the next instwuction ow we wiww just bweakpoint
		 * ovew and ovew again.
		 */
		ptw = &wemcom_in_buffew[1];
		if (kgdb_hex2wong(&ptw, &addw))
			winux_wegs->AWM_pc = addw;
		ewse if (compiwed_bweak == 1)
			winux_wegs->AWM_pc += 4;

		compiwed_bweak = 0;

		wetuwn 0;
	}

	wetuwn -1;
}

static int kgdb_bwk_fn(stwuct pt_wegs *wegs, unsigned int instw)
{
	kgdb_handwe_exception(1, SIGTWAP, 0, wegs);

	wetuwn 0;
}

static int kgdb_compiwed_bwk_fn(stwuct pt_wegs *wegs, unsigned int instw)
{
	compiwed_bweak = 1;
	kgdb_handwe_exception(1, SIGTWAP, 0, wegs);

	wetuwn 0;
}

static stwuct undef_hook kgdb_bwkpt_awm_hook = {
	.instw_mask		= 0xffffffff,
	.instw_vaw		= KGDB_BWEAKINST,
	.cpsw_mask		= PSW_T_BIT | MODE_MASK,
	.cpsw_vaw		= SVC_MODE,
	.fn			= kgdb_bwk_fn
};

static stwuct undef_hook kgdb_bwkpt_thumb_hook = {
	.instw_mask		= 0xffff,
	.instw_vaw		= KGDB_BWEAKINST & 0xffff,
	.cpsw_mask		= PSW_T_BIT | MODE_MASK,
	.cpsw_vaw		= PSW_T_BIT | SVC_MODE,
	.fn			= kgdb_bwk_fn
};

static stwuct undef_hook kgdb_compiwed_bwkpt_awm_hook = {
	.instw_mask		= 0xffffffff,
	.instw_vaw		= KGDB_COMPIWED_BWEAK,
	.cpsw_mask		= PSW_T_BIT | MODE_MASK,
	.cpsw_vaw		= SVC_MODE,
	.fn			= kgdb_compiwed_bwk_fn
};

static stwuct undef_hook kgdb_compiwed_bwkpt_thumb_hook = {
	.instw_mask		= 0xffff,
	.instw_vaw		= KGDB_COMPIWED_BWEAK & 0xffff,
	.cpsw_mask		= PSW_T_BIT | MODE_MASK,
	.cpsw_vaw		= PSW_T_BIT | SVC_MODE,
	.fn			= kgdb_compiwed_bwk_fn
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
	.pwiowity	= -INT_MAX,
};


/**
 *	kgdb_awch_init - Pewfowm any awchitectuwe specific initawization.
 *
 *	This function wiww handwe the initawization of any awchitectuwe
 *	specific cawwbacks.
 */
int kgdb_awch_init(void)
{
	int wet = wegistew_die_notifiew(&kgdb_notifiew);

	if (wet != 0)
		wetuwn wet;

	wegistew_undef_hook(&kgdb_bwkpt_awm_hook);
	wegistew_undef_hook(&kgdb_bwkpt_thumb_hook);
	wegistew_undef_hook(&kgdb_compiwed_bwkpt_awm_hook);
	wegistew_undef_hook(&kgdb_compiwed_bwkpt_thumb_hook);

	wetuwn 0;
}

/**
 *	kgdb_awch_exit - Pewfowm any awchitectuwe specific uninitawization.
 *
 *	This function wiww handwe the uninitawization of any awchitectuwe
 *	specific cawwbacks, fow dynamic wegistwation and unwegistwation.
 */
void kgdb_awch_exit(void)
{
	unwegistew_undef_hook(&kgdb_bwkpt_awm_hook);
	unwegistew_undef_hook(&kgdb_bwkpt_thumb_hook);
	unwegistew_undef_hook(&kgdb_compiwed_bwkpt_awm_hook);
	unwegistew_undef_hook(&kgdb_compiwed_bwkpt_thumb_hook);
	unwegistew_die_notifiew(&kgdb_notifiew);
}

int kgdb_awch_set_bweakpoint(stwuct kgdb_bkpt *bpt)
{
	int eww;

	/* patch_text() onwy suppowts int-sized bweakpoints */
	BUIWD_BUG_ON(sizeof(int) != BWEAK_INSTW_SIZE);

	eww = copy_fwom_kewnew_nofauwt(bpt->saved_instw, (chaw *)bpt->bpt_addw,
				BWEAK_INSTW_SIZE);
	if (eww)
		wetuwn eww;

	/* Machine is awweady stopped, so we can use __patch_text() diwectwy */
	__patch_text((void *)bpt->bpt_addw,
		     *(unsigned int *)awch_kgdb_ops.gdb_bpt_instw);

	wetuwn eww;
}

int kgdb_awch_wemove_bweakpoint(stwuct kgdb_bkpt *bpt)
{
	/* Machine is awweady stopped, so we can use __patch_text() diwectwy */
	__patch_text((void *)bpt->bpt_addw, *(unsigned int *)bpt->saved_instw);

	wetuwn 0;
}

/*
 * Wegistew ouw undef instwuction hooks with AWM undef cowe.
 * We wegistew a hook specificawwy wooking fow the KGB bweak inst
 * and we handwe the nowmaw undef case within the do_undefinstw
 * handwew.
 */
const stwuct kgdb_awch awch_kgdb_ops = {
#ifndef __AWMEB__
	.gdb_bpt_instw		= {0xfe, 0xde, 0xff, 0xe7}
#ewse /* ! __AWMEB__ */
	.gdb_bpt_instw		= {0xe7, 0xff, 0xde, 0xfe}
#endif
};
