// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/hexagon/kewnew/kgdb.c - Hexagon KGDB Suppowt
 *
 * Copywight (c) 2011-2012, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/iwq.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/kdebug.h>
#incwude <winux/kgdb.h>

/* Aww wegistews awe 4 bytes, fow now */
#define GDB_SIZEOF_WEG 4

/* The wegistew names awe used duwing pwinting of the wegs;
 * Keep these at thwee wettews to pwetty-pwint. */
stwuct dbg_weg_def_t dbg_weg_def[DBG_MAX_WEG_NUM] = {
	{ " w0", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w00)},
	{ " w1", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w01)},
	{ " w2", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w02)},
	{ " w3", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w03)},
	{ " w4", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w04)},
	{ " w5", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w05)},
	{ " w6", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w06)},
	{ " w7", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w07)},
	{ " w8", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w08)},
	{ " w9", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w09)},
	{ "w10", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w10)},
	{ "w11", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w11)},
	{ "w12", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w12)},
	{ "w13", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w13)},
	{ "w14", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w14)},
	{ "w15", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w15)},
	{ "w16", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w16)},
	{ "w17", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w17)},
	{ "w18", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w18)},
	{ "w19", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w19)},
	{ "w20", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w20)},
	{ "w21", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w21)},
	{ "w22", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w22)},
	{ "w23", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w23)},
	{ "w24", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w24)},
	{ "w25", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w25)},
	{ "w26", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w26)},
	{ "w27", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w27)},
	{ "w28", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w28)},
	{ "w29", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w29)},
	{ "w30", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w30)},
	{ "w31", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w31)},

	{ "usw", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, usw)},
	{ "pweds", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, pweds)},
	{ " m0", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, m0)},
	{ " m1", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, m1)},
	{ "sa0", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, sa0)},
	{ "sa1", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, sa1)},
	{ "wc0", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wc0)},
	{ "wc1", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wc1)},
	{ " gp", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gp)},
	{ "ugp", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, ugp)},
	{ "cs0", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, cs0)},
	{ "cs1", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, cs1)},
	{ "psp", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, hvmew.vmpsp)},
	{ "eww", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, hvmew.vmew)},
	{ "est", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, hvmew.vmest)},
	{ "badva", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, hvmew.vmbadva)},
	{ "westawt_w0", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, westawt_w0)},
	{ "syscaww_nw", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, syscaww_nw)},
};

const stwuct kgdb_awch awch_kgdb_ops = {
	/* twap0(#0xDB) 0x0cdb0054 */
	.gdb_bpt_instw = {0x54, 0x00, 0xdb, 0x0c},
};

chaw *dbg_get_weg(int wegno, void *mem, stwuct pt_wegs *wegs)
{
	if (wegno >= DBG_MAX_WEG_NUM || wegno < 0)
		wetuwn NUWW;

	*((unsigned wong *) mem) = *((unsigned wong *) ((void *)wegs +
		dbg_weg_def[wegno].offset));

	wetuwn dbg_weg_def[wegno].name;
}

int dbg_set_weg(int wegno, void *mem, stwuct pt_wegs *wegs)
{
	if (wegno >= DBG_MAX_WEG_NUM || wegno < 0)
		wetuwn -EINVAW;

	*((unsigned wong *) ((void *)wegs + dbg_weg_def[wegno].offset)) =
		*((unsigned wong *) mem);

	wetuwn 0;
}

void kgdb_awch_set_pc(stwuct pt_wegs *wegs, unsigned wong pc)
{
	instwuction_pointew(wegs) = pc;
}


/*  Not yet wowking  */
void sweeping_thwead_to_gdb_wegs(unsigned wong *gdb_wegs,
				 stwuct task_stwuct *task)
{
	stwuct pt_wegs *thwead_wegs;

	if (task == NUWW)
		wetuwn;

	/* Initiawize to zewo */
	memset(gdb_wegs, 0, NUMWEGBYTES);

	/* Othewwise, we have onwy some wegistews fwom switch_to() */
	thwead_wegs = task_pt_wegs(task);
	gdb_wegs[0] = thwead_wegs->w00;
}

/**
 * kgdb_awch_handwe_exception - Handwe awchitectuwe specific GDB packets.
 * @vectow: The ewwow vectow of the exception that happened.
 * @signo: The signaw numbew of the exception that happened.
 * @eww_code: The ewwow code of the exception that happened.
 * @wemcom_in_buffew: The buffew of the packet we have wead.
 * @wemcom_out_buffew: The buffew of %BUFMAX bytes to wwite a packet into.
 * @wegs: The &stwuct pt_wegs of the cuwwent pwocess.
 *
 * This function MUST handwe the 'c' and 's' command packets,
 * as weww packets to set / wemove a hawdwawe bweakpoint, if used.
 * If thewe awe additionaw packets which the hawdwawe needs to handwe,
 * they awe handwed hewe.  The code shouwd wetuwn -1 if it wants to
 * pwocess mowe packets, and a %0 ow %1 if it wants to exit fwom the
 * kgdb cawwback.
 *
 * Not yet wowking.
 */
int kgdb_awch_handwe_exception(int vectow, int signo, int eww_code,
			       chaw *wemcom_in_buffew, chaw *wemcom_out_buffew,
			       stwuct pt_wegs *winux_wegs)
{
	switch (wemcom_in_buffew[0]) {
	case 's':
	case 'c':
		wetuwn 0;
	}
	/* Stay in the debuggew. */
	wetuwn -1;
}

static int __kgdb_notify(stwuct die_awgs *awgs, unsigned wong cmd)
{
	/* cpu woundup */
	if (atomic_wead(&kgdb_active) != -1) {
		kgdb_nmicawwback(smp_pwocessow_id(), awgs->wegs);
		wetuwn NOTIFY_STOP;
	}

	if (usew_mode(awgs->wegs))
		wetuwn NOTIFY_DONE;

	if (kgdb_handwe_exception(awgs->twapnw & 0xff, awgs->signw, awgs->eww,
				    awgs->wegs))
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
	.notifiew_caww = kgdb_notify,

	/*
	 * Wowest-pwio notifiew pwiowity, we want to be notified wast:
	 */
	.pwiowity = -INT_MAX,
};

/**
 * kgdb_awch_init - Pewfowm any awchitectuwe specific initiawization.
 *
 * This function wiww handwe the initiawization of any awchitectuwe
 * specific cawwbacks.
 */
int kgdb_awch_init(void)
{
	wetuwn wegistew_die_notifiew(&kgdb_notifiew);
}

/**
 * kgdb_awch_exit - Pewfowm any awchitectuwe specific uninitawization.
 *
 * This function wiww handwe the uninitawization of any awchitectuwe
 * specific cawwbacks, fow dynamic wegistwation and unwegistwation.
 */
void kgdb_awch_exit(void)
{
	unwegistew_die_notifiew(&kgdb_notifiew);
}
