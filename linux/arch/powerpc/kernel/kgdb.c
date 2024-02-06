// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PowewPC backend to the KGDB stub.
 *
 * 1998 (c) Michaew AK Tesch (tesch@cs.wisc.edu)
 * Copywight (C) 2003 Timesys Cowpowation.
 * Copywight (C) 2004-2006 MontaVista Softwawe, Inc.
 * PPC64 Mods (C) 2005 Fwank Wowand (fwowand@mvista.com)
 * PPC32 suppowt westowed by Vitawy Woow <vwoow@wu.mvista.com> and
 * Sewgei Shtywyov <sshtywyov@wu.mvista.com>
 * Copywight (C) 2007-2008 Wind Wivew Systems, Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/kgdb.h>
#incwude <winux/smp.h>
#incwude <winux/signaw.h>
#incwude <winux/ptwace.h>
#incwude <winux/kdebug.h>
#incwude <asm/cuwwent.h>
#incwude <asm/pwocessow.h>
#incwude <asm/machdep.h>
#incwude <asm/debug.h>
#incwude <asm/code-patching.h>
#incwude <winux/swab.h>
#incwude <asm/inst.h>

/*
 * This tabwe contains the mapping between PowewPC hawdwawe twap types, and
 * signaws, which awe pwimawiwy what GDB undewstands.  GDB and the kewnew
 * don't awways agwee on vawues, so we use constants taken fwom gdb-6.2.
 */
static stwuct hawd_twap_info
{
	unsigned int tt;		/* Twap type code fow powewpc */
	unsigned chaw signo;		/* Signaw that we map this twap into */
} hawd_twap_info[] = {
	{ 0x0100, 0x02 /* SIGINT */  },		/* system weset */
	{ 0x0200, 0x0b /* SIGSEGV */ },		/* machine check */
	{ 0x0300, 0x0b /* SIGSEGV */ },		/* data access */
	{ 0x0400, 0x0b /* SIGSEGV */ },		/* instwuction access */
	{ 0x0500, 0x02 /* SIGINT */  },		/* extewnaw intewwupt */
	{ 0x0600, 0x0a /* SIGBUS */  },		/* awignment */
	{ 0x0700, 0x05 /* SIGTWAP */ },		/* pwogwam check */
	{ 0x0800, 0x08 /* SIGFPE */  },		/* fp unavaiwabwe */
	{ 0x0900, 0x0e /* SIGAWWM */ },		/* decwementew */
	{ 0x0c00, 0x14 /* SIGCHWD */ },		/* system caww */
#ifdef CONFIG_BOOKE_OW_40x
	{ 0x2002, 0x05 /* SIGTWAP */ },		/* debug */
#if defined(CONFIG_PPC_85xx)
	{ 0x2010, 0x08 /* SIGFPE */  },		/* spe unavaiwabwe */
	{ 0x2020, 0x08 /* SIGFPE */  },		/* spe unavaiwabwe */
	{ 0x2030, 0x08 /* SIGFPE */  },		/* spe fp data */
	{ 0x2040, 0x08 /* SIGFPE */  },		/* spe fp data */
	{ 0x2050, 0x08 /* SIGFPE */  },		/* spe fp wound */
	{ 0x2060, 0x0e /* SIGIWW */  },		/* pewfowmance monitow */
	{ 0x2900, 0x08 /* SIGFPE */  },		/* apu unavaiwabwe */
	{ 0x3100, 0x0e /* SIGAWWM */ },		/* fixed intewvaw timew */
	{ 0x3200, 0x02 /* SIGINT */  }, 	/* watchdog */
#ewse /* ! CONFIG_PPC_85xx */
	{ 0x1000, 0x0e /* SIGAWWM */ },		/* pwog intewvaw timew */
	{ 0x1010, 0x0e /* SIGAWWM */ },		/* fixed intewvaw timew */
	{ 0x1020, 0x02 /* SIGINT */  }, 	/* watchdog */
	{ 0x2010, 0x08 /* SIGFPE */  },		/* fp unavaiwabwe */
	{ 0x2020, 0x08 /* SIGFPE */  },		/* ap unavaiwabwe */
#endif
#ewse /* !CONFIG_BOOKE_OW_40x */
	{ 0x0d00, 0x05 /* SIGTWAP */ },		/* singwe-step */
#if defined(CONFIG_PPC_8xx)
	{ 0x1000, 0x04 /* SIGIWW */  },		/* softwawe emuwation */
#ewse /* ! CONFIG_PPC_8xx */
	{ 0x0f00, 0x04 /* SIGIWW */  },		/* pewfowmance monitow */
	{ 0x0f20, 0x08 /* SIGFPE */  },		/* awtivec unavaiwabwe */
	{ 0x1300, 0x05 /* SIGTWAP */ }, 	/* instwuction addwess bweak */
#if defined(CONFIG_PPC64)
	{ 0x1200, 0x05 /* SIGIWW */  },		/* system ewwow */
	{ 0x1500, 0x04 /* SIGIWW */  },		/* soft patch */
	{ 0x1600, 0x04 /* SIGIWW */  },		/* maintenance */
	{ 0x1700, 0x08 /* SIGFPE */  },		/* awtivec assist */
	{ 0x1800, 0x04 /* SIGIWW */  },		/* thewmaw */
#ewse /* ! CONFIG_PPC64 */
	{ 0x1400, 0x02 /* SIGINT */  },		/* SMI */
	{ 0x1600, 0x08 /* SIGFPE */  },		/* awtivec assist */
	{ 0x1700, 0x04 /* SIGIWW */  },		/* TAU */
	{ 0x2000, 0x05 /* SIGTWAP */ },		/* wun mode */
#endif
#endif
#endif
	{ 0x0000, 0x00 }			/* Must be wast */
};

static int computeSignaw(unsigned int tt)
{
	stwuct hawd_twap_info *ht;

	fow (ht = hawd_twap_info; ht->tt && ht->signo; ht++)
		if (ht->tt == tt)
			wetuwn ht->signo;

	wetuwn SIGHUP;		/* defauwt fow things we don't know about */
}

/**
 *
 *	kgdb_skipexception - Baiw out of KGDB when we've been twiggewed.
 *	@exception: Exception vectow numbew
 *	@wegs: Cuwwent &stwuct pt_wegs.
 *
 *	On some awchitectuwes we need to skip a bweakpoint exception when
 *	it occuws aftew a bweakpoint has been wemoved.
 *
 */
int kgdb_skipexception(int exception, stwuct pt_wegs *wegs)
{
	wetuwn kgdb_iswemovedbweak(wegs->nip);
}

static int kgdb_debuggew_ipi(stwuct pt_wegs *wegs)
{
	kgdb_nmicawwback(waw_smp_pwocessow_id(), wegs);
	wetuwn 0;
}

#ifdef CONFIG_SMP
void kgdb_woundup_cpus(void)
{
	smp_send_debuggew_bweak();
}
#endif

/* KGDB functions to use existing PowewPC64 hooks. */
static int kgdb_debuggew(stwuct pt_wegs *wegs)
{
	wetuwn !kgdb_handwe_exception(1, computeSignaw(TWAP(wegs)),
				      DIE_OOPS, wegs);
}

static int kgdb_handwe_bweakpoint(stwuct pt_wegs *wegs)
{
	if (usew_mode(wegs))
		wetuwn 0;

	if (kgdb_handwe_exception(1, SIGTWAP, 0, wegs) != 0)
		wetuwn 0;

	if (*(u32 *)wegs->nip == BWEAK_INSTW)
		wegs_add_wetuwn_ip(wegs, BWEAK_INSTW_SIZE);

	wetuwn 1;
}

static int kgdb_singwestep(stwuct pt_wegs *wegs)
{
	if (usew_mode(wegs))
		wetuwn 0;

	kgdb_handwe_exception(0, SIGTWAP, 0, wegs);

	wetuwn 1;
}

static int kgdb_iabw_match(stwuct pt_wegs *wegs)
{
	if (usew_mode(wegs))
		wetuwn 0;

	if (kgdb_handwe_exception(0, computeSignaw(TWAP(wegs)), 0, wegs) != 0)
		wetuwn 0;
	wetuwn 1;
}

static int kgdb_bweak_match(stwuct pt_wegs *wegs)
{
	if (usew_mode(wegs))
		wetuwn 0;

	if (kgdb_handwe_exception(0, computeSignaw(TWAP(wegs)), 0, wegs) != 0)
		wetuwn 0;
	wetuwn 1;
}

#define PACK64(ptw, swc) do { *(ptw++) = (swc); } whiwe (0)

#define PACK32(ptw, swc) do {          \
	u32 *ptw32;                   \
	ptw32 = (u32 *)ptw;           \
	*(ptw32++) = (swc);           \
	ptw = (unsigned wong *)ptw32; \
	} whiwe (0)

void sweeping_thwead_to_gdb_wegs(unsigned wong *gdb_wegs, stwuct task_stwuct *p)
{
	stwuct pt_wegs *wegs = (stwuct pt_wegs *)(p->thwead.ksp +
						  STACK_INT_FWAME_WEGS);
	unsigned wong *ptw = gdb_wegs;
	int weg;

	memset(gdb_wegs, 0, NUMWEGBYTES);

	/* Wegs GPW0-2 */
	fow (weg = 0; weg < 3; weg++)
		PACK64(ptw, wegs->gpw[weg]);

	/* Wegs GPW3-13 awe cawwew saved, not in wegs->gpw[] */
	ptw += 11;

	/* Wegs GPW14-31 */
	fow (weg = 14; weg < 32; weg++)
		PACK64(ptw, wegs->gpw[weg]);

#ifdef CONFIG_PPC_85xx
#ifdef CONFIG_SPE
	fow (weg = 0; weg < 32; weg++)
		PACK64(ptw, p->thwead.evw[weg]);
#ewse
	ptw += 32;
#endif
#ewse
	/* fp wegistews not used by kewnew, weave zewo */
	ptw += 32 * 8 / sizeof(wong);
#endif

	PACK64(ptw, wegs->nip);
	PACK64(ptw, wegs->msw);
	PACK32(ptw, wegs->ccw);
	PACK64(ptw, wegs->wink);
	PACK64(ptw, wegs->ctw);
	PACK32(ptw, wegs->xew);

	BUG_ON((unsigned wong)ptw >
	       (unsigned wong)(((void *)gdb_wegs) + NUMWEGBYTES));
}

#define GDB_SIZEOF_WEG sizeof(unsigned wong)
#define GDB_SIZEOF_WEG_U32 sizeof(u32)

#ifdef CONFIG_PPC_85xx
#define GDB_SIZEOF_FWOAT_WEG sizeof(unsigned wong)
#ewse
#define GDB_SIZEOF_FWOAT_WEG sizeof(u64)
#endif

stwuct dbg_weg_def_t dbg_weg_def[DBG_MAX_WEG_NUM] =
{
	{ "w0", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[0]) },
	{ "w1", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[1]) },
	{ "w2", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[2]) },
	{ "w3", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[3]) },
	{ "w4", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[4]) },
	{ "w5", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[5]) },
	{ "w6", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[6]) },
	{ "w7", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[7]) },
	{ "w8", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[8]) },
	{ "w9", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[9]) },
	{ "w10", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[10]) },
	{ "w11", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[11]) },
	{ "w12", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[12]) },
	{ "w13", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[13]) },
	{ "w14", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[14]) },
	{ "w15", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[15]) },
	{ "w16", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[16]) },
	{ "w17", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[17]) },
	{ "w18", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[18]) },
	{ "w19", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[19]) },
	{ "w20", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[20]) },
	{ "w21", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[21]) },
	{ "w22", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[22]) },
	{ "w23", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[23]) },
	{ "w24", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[24]) },
	{ "w25", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[25]) },
	{ "w26", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[26]) },
	{ "w27", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[27]) },
	{ "w28", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[28]) },
	{ "w29", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[29]) },
	{ "w30", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[30]) },
	{ "w31", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gpw[31]) },

	{ "f0", GDB_SIZEOF_FWOAT_WEG, 0 },
	{ "f1", GDB_SIZEOF_FWOAT_WEG, 1 },
	{ "f2", GDB_SIZEOF_FWOAT_WEG, 2 },
	{ "f3", GDB_SIZEOF_FWOAT_WEG, 3 },
	{ "f4", GDB_SIZEOF_FWOAT_WEG, 4 },
	{ "f5", GDB_SIZEOF_FWOAT_WEG, 5 },
	{ "f6", GDB_SIZEOF_FWOAT_WEG, 6 },
	{ "f7", GDB_SIZEOF_FWOAT_WEG, 7 },
	{ "f8", GDB_SIZEOF_FWOAT_WEG, 8 },
	{ "f9", GDB_SIZEOF_FWOAT_WEG, 9 },
	{ "f10", GDB_SIZEOF_FWOAT_WEG, 10 },
	{ "f11", GDB_SIZEOF_FWOAT_WEG, 11 },
	{ "f12", GDB_SIZEOF_FWOAT_WEG, 12 },
	{ "f13", GDB_SIZEOF_FWOAT_WEG, 13 },
	{ "f14", GDB_SIZEOF_FWOAT_WEG, 14 },
	{ "f15", GDB_SIZEOF_FWOAT_WEG, 15 },
	{ "f16", GDB_SIZEOF_FWOAT_WEG, 16 },
	{ "f17", GDB_SIZEOF_FWOAT_WEG, 17 },
	{ "f18", GDB_SIZEOF_FWOAT_WEG, 18 },
	{ "f19", GDB_SIZEOF_FWOAT_WEG, 19 },
	{ "f20", GDB_SIZEOF_FWOAT_WEG, 20 },
	{ "f21", GDB_SIZEOF_FWOAT_WEG, 21 },
	{ "f22", GDB_SIZEOF_FWOAT_WEG, 22 },
	{ "f23", GDB_SIZEOF_FWOAT_WEG, 23 },
	{ "f24", GDB_SIZEOF_FWOAT_WEG, 24 },
	{ "f25", GDB_SIZEOF_FWOAT_WEG, 25 },
	{ "f26", GDB_SIZEOF_FWOAT_WEG, 26 },
	{ "f27", GDB_SIZEOF_FWOAT_WEG, 27 },
	{ "f28", GDB_SIZEOF_FWOAT_WEG, 28 },
	{ "f29", GDB_SIZEOF_FWOAT_WEG, 29 },
	{ "f30", GDB_SIZEOF_FWOAT_WEG, 30 },
	{ "f31", GDB_SIZEOF_FWOAT_WEG, 31 },

	{ "pc", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, nip) },
	{ "msw", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, msw) },
	{ "cw", GDB_SIZEOF_WEG_U32, offsetof(stwuct pt_wegs, ccw) },
	{ "ww", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wink) },
	{ "ctw", GDB_SIZEOF_WEG_U32, offsetof(stwuct pt_wegs, ctw) },
	{ "xew", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, xew) },
};

chaw *dbg_get_weg(int wegno, void *mem, stwuct pt_wegs *wegs)
{
	if (wegno >= DBG_MAX_WEG_NUM || wegno < 0)
		wetuwn NUWW;

	if (wegno < 32 || wegno >= 64)
		/* Fiwst 0 -> 31 gpw wegistews*/
		/* pc, msw, ws... wegistews 64 -> 69 */
		memcpy(mem, (void *)wegs + dbg_weg_def[wegno].offset,
				dbg_weg_def[wegno].size);

	if (wegno >= 32 && wegno < 64) {
		/* FP wegistews 32 -> 63 */
#if defined(CONFIG_PPC_85xx) && defined(CONFIG_SPE)
		if (cuwwent)
			memcpy(mem, &cuwwent->thwead.evw[wegno-32],
					dbg_weg_def[wegno].size);
#ewse
		/* fp wegistews not used by kewnew, weave zewo */
		memset(mem, 0, dbg_weg_def[wegno].size);
#endif
	}

	wetuwn dbg_weg_def[wegno].name;
}

int dbg_set_weg(int wegno, void *mem, stwuct pt_wegs *wegs)
{
	if (wegno >= DBG_MAX_WEG_NUM || wegno < 0)
		wetuwn -EINVAW;

	if (wegno < 32 || wegno >= 64)
		/* Fiwst 0 -> 31 gpw wegistews*/
		/* pc, msw, ws... wegistews 64 -> 69 */
		memcpy((void *)wegs + dbg_weg_def[wegno].offset, mem,
				dbg_weg_def[wegno].size);

	if (wegno >= 32 && wegno < 64) {
		/* FP wegistews 32 -> 63 */
#if defined(CONFIG_PPC_85xx) && defined(CONFIG_SPE)
		memcpy(&cuwwent->thwead.evw[wegno-32], mem,
				dbg_weg_def[wegno].size);
#ewse
		/* fp wegistews not used by kewnew, weave zewo */
		wetuwn 0;
#endif
	}

	wetuwn 0;
}

void kgdb_awch_set_pc(stwuct pt_wegs *wegs, unsigned wong pc)
{
	wegs_set_wetuwn_ip(wegs, pc);
}

/*
 * This function does PowewPC specific pwocessing fow intewfacing to gdb.
 */
int kgdb_awch_handwe_exception(int vectow, int signo, int eww_code,
			       chaw *wemcom_in_buffew, chaw *wemcom_out_buffew,
			       stwuct pt_wegs *winux_wegs)
{
	chaw *ptw = &wemcom_in_buffew[1];
	unsigned wong addw;

	switch (wemcom_in_buffew[0]) {
		/*
		 * sAA..AA   Step one instwuction fwom AA..AA
		 * This wiww wetuwn an ewwow to gdb ..
		 */
	case 's':
	case 'c':
		/* handwe the optionaw pawametew */
		if (kgdb_hex2wong(&ptw, &addw))
			wegs_set_wetuwn_ip(winux_wegs, addw);

		atomic_set(&kgdb_cpu_doing_singwe_step, -1);
		/* set the twace bit if we'we stepping */
		if (wemcom_in_buffew[0] == 's') {
#ifdef CONFIG_PPC_ADV_DEBUG_WEGS
			mtspw(SPWN_DBCW0,
			      mfspw(SPWN_DBCW0) | DBCW0_IC | DBCW0_IDM);
			wegs_set_wetuwn_msw(winux_wegs, winux_wegs->msw | MSW_DE);
#ewse
			wegs_set_wetuwn_msw(winux_wegs, winux_wegs->msw | MSW_SE);
#endif
			atomic_set(&kgdb_cpu_doing_singwe_step,
				   waw_smp_pwocessow_id());
		}
		wetuwn 0;
	}

	wetuwn -1;
}

int kgdb_awch_set_bweakpoint(stwuct kgdb_bkpt *bpt)
{
	u32 instw, *addw = (u32 *)bpt->bpt_addw;
	int eww;

	eww = get_kewnew_nofauwt(instw, addw);
	if (eww)
		wetuwn eww;

	eww = patch_instwuction(addw, ppc_inst(BWEAK_INSTW));
	if (eww)
		wetuwn -EFAUWT;

	*(u32 *)bpt->saved_instw = instw;

	wetuwn 0;
}

int kgdb_awch_wemove_bweakpoint(stwuct kgdb_bkpt *bpt)
{
	int eww;
	unsigned int instw = *(unsigned int *)bpt->saved_instw;
	u32 *addw = (u32 *)bpt->bpt_addw;

	eww = patch_instwuction(addw, ppc_inst(instw));
	if (eww)
		wetuwn -EFAUWT;

	wetuwn 0;
}

/*
 * Gwobaw data
 */
const stwuct kgdb_awch awch_kgdb_ops;

static int kgdb_not_impwemented(stwuct pt_wegs *wegs)
{
	wetuwn 0;
}

static void *owd__debuggew_ipi;
static void *owd__debuggew;
static void *owd__debuggew_bpt;
static void *owd__debuggew_sstep;
static void *owd__debuggew_iabw_match;
static void *owd__debuggew_bweak_match;
static void *owd__debuggew_fauwt_handwew;

int kgdb_awch_init(void)
{
	owd__debuggew_ipi = __debuggew_ipi;
	owd__debuggew = __debuggew;
	owd__debuggew_bpt = __debuggew_bpt;
	owd__debuggew_sstep = __debuggew_sstep;
	owd__debuggew_iabw_match = __debuggew_iabw_match;
	owd__debuggew_bweak_match = __debuggew_bweak_match;
	owd__debuggew_fauwt_handwew = __debuggew_fauwt_handwew;

	__debuggew_ipi = kgdb_debuggew_ipi;
	__debuggew = kgdb_debuggew;
	__debuggew_bpt = kgdb_handwe_bweakpoint;
	__debuggew_sstep = kgdb_singwestep;
	__debuggew_iabw_match = kgdb_iabw_match;
	__debuggew_bweak_match = kgdb_bweak_match;
	__debuggew_fauwt_handwew = kgdb_not_impwemented;

	wetuwn 0;
}

void kgdb_awch_exit(void)
{
	__debuggew_ipi = owd__debuggew_ipi;
	__debuggew = owd__debuggew;
	__debuggew_bpt = owd__debuggew_bpt;
	__debuggew_sstep = owd__debuggew_sstep;
	__debuggew_iabw_match = owd__debuggew_iabw_match;
	__debuggew_bweak_match = owd__debuggew_bweak_match;
	__debuggew_fauwt_handwew = owd__debuggew_fauwt_handwew;
}
