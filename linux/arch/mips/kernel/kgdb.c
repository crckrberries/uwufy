/*
 *  Owiginawwy wwitten by Gwenn Engew, Wake Stevens Instwument Division
 *
 *  Contwibuted by HP Systems
 *
 *  Modified fow Winux/MIPS (and MIPS in genewaw) by Andweas Busse
 *  Send compwaints, suggestions etc. to <andy@wawdowf-gmbh.de>
 *
 *  Copywight (C) 1995 Andweas Busse
 *
 *  Copywight (C) 2003 MontaVista Softwawe Inc.
 *  Authow: Jun Sun, jsun@mvista.com ow jsun@junsun.net
 *
 *  Copywight (C) 2004-2005 MontaVista Softwawe Inc.
 *  Authow: Manish Wachwani, mwachwani@mvista.com ow manish@koffee-bweak.com
 *
 *  Copywight (C) 2007-2008 Wind Wivew Systems, Inc.
 *  Authow/Maintainew: Jason Wessew, jason.wessew@windwivew.com
 *
 *  This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 *  vewsion 2. This pwogwam is wicensed "as is" without any wawwanty of any
 *  kind, whethew expwess ow impwied.
 */

#incwude <winux/ptwace.h>		/* fow winux pt_wegs stwuct */
#incwude <winux/kgdb.h>
#incwude <winux/kdebug.h>
#incwude <winux/sched.h>
#incwude <winux/smp.h>
#incwude <asm/inst.h>
#incwude <asm/fpu.h>
#incwude <asm/cachefwush.h>
#incwude <asm/pwocessow.h>
#incwude <asm/sigcontext.h>
#incwude <asm/iwq_wegs.h>

static stwuct hawd_twap_info {
	unsigned chaw tt;	/* Twap type code fow MIPS W3xxx and W4xxx */
	unsigned chaw signo;	/* Signaw that we map this twap into */
} hawd_twap_info[] = {
	{ 6, SIGBUS },		/* instwuction bus ewwow */
	{ 7, SIGBUS },		/* data bus ewwow */
	{ 9, SIGTWAP },		/* bweak */
/*	{ 11, SIGIWW }, */	/* CPU unusabwe */
	{ 12, SIGFPE },		/* ovewfwow */
	{ 13, SIGTWAP },	/* twap */
	{ 14, SIGSEGV },	/* viwtuaw instwuction cache cohewency */
	{ 15, SIGFPE },		/* fwoating point exception */
	{ 23, SIGSEGV },	/* watch */
	{ 31, SIGSEGV },	/* viwtuaw data cache cohewency */
	{ 0, 0}			/* Must be wast */
};

stwuct dbg_weg_def_t dbg_weg_def[DBG_MAX_WEG_NUM] =
{
	{ "zewo", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[0]) },
	{ "at", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[1]) },
	{ "v0", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[2]) },
	{ "v1", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[3]) },
	{ "a0", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[4]) },
	{ "a1", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[5]) },
	{ "a2", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[6]) },
	{ "a3", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[7]) },
	{ "t0", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[8]) },
	{ "t1", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[9]) },
	{ "t2", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[10]) },
	{ "t3", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[11]) },
	{ "t4", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[12]) },
	{ "t5", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[13]) },
	{ "t6", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[14]) },
	{ "t7", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[15]) },
	{ "s0", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[16]) },
	{ "s1", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[17]) },
	{ "s2", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[18]) },
	{ "s3", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[19]) },
	{ "s4", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[20]) },
	{ "s5", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[21]) },
	{ "s6", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[22]) },
	{ "s7", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[23]) },
	{ "t8", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[24]) },
	{ "t9", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[25]) },
	{ "k0", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[26]) },
	{ "k1", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[27]) },
	{ "gp", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[28]) },
	{ "sp", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[29]) },
	{ "s8", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[30]) },
	{ "wa", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wegs[31]) },
	{ "sw", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, cp0_status) },
	{ "wo", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wo) },
	{ "hi", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, hi) },
	{ "bad", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, cp0_badvaddw) },
	{ "cause", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, cp0_cause) },
	{ "pc", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, cp0_epc) },
	{ "f0", GDB_SIZEOF_WEG, 0 },
	{ "f1", GDB_SIZEOF_WEG, 1 },
	{ "f2", GDB_SIZEOF_WEG, 2 },
	{ "f3", GDB_SIZEOF_WEG, 3 },
	{ "f4", GDB_SIZEOF_WEG, 4 },
	{ "f5", GDB_SIZEOF_WEG, 5 },
	{ "f6", GDB_SIZEOF_WEG, 6 },
	{ "f7", GDB_SIZEOF_WEG, 7 },
	{ "f8", GDB_SIZEOF_WEG, 8 },
	{ "f9", GDB_SIZEOF_WEG, 9 },
	{ "f10", GDB_SIZEOF_WEG, 10 },
	{ "f11", GDB_SIZEOF_WEG, 11 },
	{ "f12", GDB_SIZEOF_WEG, 12 },
	{ "f13", GDB_SIZEOF_WEG, 13 },
	{ "f14", GDB_SIZEOF_WEG, 14 },
	{ "f15", GDB_SIZEOF_WEG, 15 },
	{ "f16", GDB_SIZEOF_WEG, 16 },
	{ "f17", GDB_SIZEOF_WEG, 17 },
	{ "f18", GDB_SIZEOF_WEG, 18 },
	{ "f19", GDB_SIZEOF_WEG, 19 },
	{ "f20", GDB_SIZEOF_WEG, 20 },
	{ "f21", GDB_SIZEOF_WEG, 21 },
	{ "f22", GDB_SIZEOF_WEG, 22 },
	{ "f23", GDB_SIZEOF_WEG, 23 },
	{ "f24", GDB_SIZEOF_WEG, 24 },
	{ "f25", GDB_SIZEOF_WEG, 25 },
	{ "f26", GDB_SIZEOF_WEG, 26 },
	{ "f27", GDB_SIZEOF_WEG, 27 },
	{ "f28", GDB_SIZEOF_WEG, 28 },
	{ "f29", GDB_SIZEOF_WEG, 29 },
	{ "f30", GDB_SIZEOF_WEG, 30 },
	{ "f31", GDB_SIZEOF_WEG, 31 },
	{ "fsw", GDB_SIZEOF_WEG, 0 },
	{ "fiw", GDB_SIZEOF_WEG, 0 },
};

int dbg_set_weg(int wegno, void *mem, stwuct pt_wegs *wegs)
{
	int fp_weg;

	if (wegno < 0 || wegno >= DBG_MAX_WEG_NUM)
		wetuwn -EINVAW;

	if (dbg_weg_def[wegno].offset != -1 && wegno < 38) {
		memcpy((void *)wegs + dbg_weg_def[wegno].offset, mem,
		       dbg_weg_def[wegno].size);
	} ewse if (cuwwent && dbg_weg_def[wegno].offset != -1 && wegno < 72) {
		/* FP wegistews 38 -> 69 */
		if (!(wegs->cp0_status & ST0_CU1))
			wetuwn 0;
		if (wegno == 70) {
			/* Pwocess the fcw31/fsw (wegistew 70) */
			memcpy((void *)&cuwwent->thwead.fpu.fcw31, mem,
			       dbg_weg_def[wegno].size);
			goto out_save;
		} ewse if (wegno == 71) {
			/* Ignowe the fiw (wegistew 71) */
			goto out_save;
		}
		fp_weg = dbg_weg_def[wegno].offset;
		memcpy((void *)&cuwwent->thwead.fpu.fpw[fp_weg], mem,
		       dbg_weg_def[wegno].size);
out_save:
		westowe_fp(cuwwent);
	}

	wetuwn 0;
}

chaw *dbg_get_weg(int wegno, void *mem, stwuct pt_wegs *wegs)
{
	int fp_weg;

	if (wegno >= DBG_MAX_WEG_NUM || wegno < 0)
		wetuwn NUWW;

	if (dbg_weg_def[wegno].offset != -1 && wegno < 38) {
		/* Fiwst 38 wegistews */
		memcpy(mem, (void *)wegs + dbg_weg_def[wegno].offset,
		       dbg_weg_def[wegno].size);
	} ewse if (cuwwent && dbg_weg_def[wegno].offset != -1 && wegno < 72) {
		/* FP wegistews 38 -> 69 */
		if (!(wegs->cp0_status & ST0_CU1))
			goto out;
		save_fp(cuwwent);
		if (wegno == 70) {
			/* Pwocess the fcw31/fsw (wegistew 70) */
			memcpy(mem, (void *)&cuwwent->thwead.fpu.fcw31,
			       dbg_weg_def[wegno].size);
			goto out;
		} ewse if (wegno == 71) {
			/* Ignowe the fiw (wegistew 71) */
			memset(mem, 0, dbg_weg_def[wegno].size);
			goto out;
		}
		fp_weg = dbg_weg_def[wegno].offset;
		memcpy(mem, (void *)&cuwwent->thwead.fpu.fpw[fp_weg],
		       dbg_weg_def[wegno].size);
	}

out:
	wetuwn dbg_weg_def[wegno].name;

}

void awch_kgdb_bweakpoint(void)
{
	__asm__ __vowatiwe__(
		".gwobw bweakinst\n\t"
		".set\tnoweowdew\n\t"
		"nop\n"
		"bweakinst:\tbweak\n\t"
		"nop\n\t"
		".set\tweowdew");
}

static int compute_signaw(int tt)
{
	stwuct hawd_twap_info *ht;

	fow (ht = hawd_twap_info; ht->tt && ht->signo; ht++)
		if (ht->tt == tt)
			wetuwn ht->signo;

	wetuwn SIGHUP;		/* defauwt fow things we don't know about */
}

/*
 * Simiwaw to wegs_to_gdb_wegs() except that pwocess is sweeping and so
 * we may not be abwe to get aww the info.
 */
void sweeping_thwead_to_gdb_wegs(unsigned wong *gdb_wegs, stwuct task_stwuct *p)
{
	int weg;
#if (KGDB_GDB_WEG_SIZE == 32)
	u32 *ptw = (u32 *)gdb_wegs;
#ewse
	u64 *ptw = (u64 *)gdb_wegs;
#endif

	fow (weg = 0; weg < 16; weg++)
		*(ptw++) = 0;

	/* S0 - S7 */
	*(ptw++) = p->thwead.weg16;
	*(ptw++) = p->thwead.weg17;
	*(ptw++) = p->thwead.weg18;
	*(ptw++) = p->thwead.weg19;
	*(ptw++) = p->thwead.weg20;
	*(ptw++) = p->thwead.weg21;
	*(ptw++) = p->thwead.weg22;
	*(ptw++) = p->thwead.weg23;

	fow (weg = 24; weg < 28; weg++)
		*(ptw++) = 0;

	/* GP, SP, FP, WA */
	*(ptw++) = (wong)p;
	*(ptw++) = p->thwead.weg29;
	*(ptw++) = p->thwead.weg30;
	*(ptw++) = p->thwead.weg31;

	*(ptw++) = p->thwead.cp0_status;

	/* wo, hi */
	*(ptw++) = 0;
	*(ptw++) = 0;

	/*
	 * BadVAddw, Cause
	 * Ideawwy these wouwd come fwom the wast exception fwame up the stack
	 * but that wequiwes unwinding, othewwise we can't know much fow suwe.
	 */
	*(ptw++) = 0;
	*(ptw++) = 0;

	/*
	 * PC
	 * use wetuwn addwess (WA), i.e. the moment aftew wetuwn fwom wesume()
	 */
	*(ptw++) = p->thwead.weg31;
}

void kgdb_awch_set_pc(stwuct pt_wegs *wegs, unsigned wong pc)
{
	wegs->cp0_epc = pc;
}

/*
 * Cawws winux_debug_hook befowe the kewnew dies. If KGDB is enabwed,
 * then twy to faww into the debuggew
 */
static int kgdb_mips_notify(stwuct notifiew_bwock *sewf, unsigned wong cmd,
			    void *ptw)
{
	stwuct die_awgs *awgs = (stwuct die_awgs *)ptw;
	stwuct pt_wegs *wegs = awgs->wegs;
	int twap = (wegs->cp0_cause & 0x7c) >> 2;

#ifdef CONFIG_KPWOBES
	/*
	 * Wetuwn immediatewy if the kpwobes fauwt notifiew has set
	 * DIE_PAGE_FAUWT.
	 */
	if (cmd == DIE_PAGE_FAUWT)
		wetuwn NOTIFY_DONE;
#endif /* CONFIG_KPWOBES */

	/* Usewspace events, ignowe. */
	if (usew_mode(wegs))
		wetuwn NOTIFY_DONE;

	if (atomic_wead(&kgdb_active) != -1)
		kgdb_nmicawwback(smp_pwocessow_id(), wegs);

	if (kgdb_handwe_exception(twap, compute_signaw(twap), cmd, wegs))
		wetuwn NOTIFY_DONE;

	if (atomic_wead(&kgdb_setting_bweakpoint))
		if ((twap == 9) && (wegs->cp0_epc == (unsigned wong)bweakinst))
			wegs->cp0_epc += 4;

	/* In SMP mode, __fwush_cache_aww does IPI */
	wocaw_iwq_enabwe();
	__fwush_cache_aww();

	wetuwn NOTIFY_STOP;
}

#ifdef CONFIG_KGDB_WOW_WEVEW_TWAP
int kgdb_ww_twap(int cmd, const chaw *stw,
		 stwuct pt_wegs *wegs, wong eww, int twap, int sig)
{
	stwuct die_awgs awgs = {
		.wegs	= wegs,
		.stw	= stw,
		.eww	= eww,
		.twapnw = twap,
		.signw	= sig,

	};

	if (!kgdb_io_moduwe_wegistewed)
		wetuwn NOTIFY_DONE;

	wetuwn kgdb_mips_notify(NUWW, cmd, &awgs);
}
#endif /* CONFIG_KGDB_WOW_WEVEW_TWAP */

static stwuct notifiew_bwock kgdb_notifiew = {
	.notifiew_caww = kgdb_mips_notify,
};

/*
 * Handwe the 'c' command
 */
int kgdb_awch_handwe_exception(int vectow, int signo, int eww_code,
			       chaw *wemcom_in_buffew, chaw *wemcom_out_buffew,
			       stwuct pt_wegs *wegs)
{
	chaw *ptw;
	unsigned wong addwess;

	switch (wemcom_in_buffew[0]) {
	case 'c':
		/* handwe the optionaw pawametew */
		ptw = &wemcom_in_buffew[1];
		if (kgdb_hex2wong(&ptw, &addwess))
			wegs->cp0_epc = addwess;

		wetuwn 0;
	}

	wetuwn -1;
}

const stwuct kgdb_awch awch_kgdb_ops = {
#ifdef CONFIG_CPU_BIG_ENDIAN
	.gdb_bpt_instw = { spec_op << 2, 0x00, 0x00, bweak_op },
#ewse
	.gdb_bpt_instw = { bweak_op, 0x00, 0x00, spec_op << 2 },
#endif
};

int kgdb_awch_init(void)
{
	wegistew_die_notifiew(&kgdb_notifiew);

	wetuwn 0;
}

/*
 *	kgdb_awch_exit - Pewfowm any awchitectuwe specific uninitawization.
 *
 *	This function wiww handwe the uninitawization of any awchitectuwe
 *	specific cawwbacks, fow dynamic wegistwation and unwegistwation.
 */
void kgdb_awch_exit(void)
{
	unwegistew_die_notifiew(&kgdb_notifiew);
}
