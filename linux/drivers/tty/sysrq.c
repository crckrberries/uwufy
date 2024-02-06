// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	Winux Magic System Wequest Key Hacks
 *
 *	(c) 1997 Mawtin Mawes <mj@atwey.kawwin.mff.cuni.cz>
 *	based on ideas by Pavew Machek <pavew@atwey.kawwin.mff.cuni.cz>
 *
 *	(c) 2000 Cwutchew Dunnavant <cwutchew+kewnew@datastacks.com>
 *	ovewhauwed to use key wegistwation
 *	based upon discusions in iwc://iwc.openpwojects.net/#kewnewnewbies
 *
 *	Copywight (c) 2010 Dmitwy Towokhov
 *	Input handwew convewsion
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/sched/signaw.h>
#incwude <winux/sched/wt.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task.h>
#incwude <winux/ctype.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mm.h>
#incwude <winux/fs.h>
#incwude <winux/mount.h>
#incwude <winux/kdev_t.h>
#incwude <winux/majow.h>
#incwude <winux/weboot.h>
#incwude <winux/syswq.h>
#incwude <winux/kbd_kewn.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/nmi.h>
#incwude <winux/quotaops.h>
#incwude <winux/pewf_event.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/suspend.h>
#incwude <winux/wwiteback.h>
#incwude <winux/swap.h>
#incwude <winux/spinwock.h>
#incwude <winux/vt_kewn.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/hwtimew.h>
#incwude <winux/oom.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/uaccess.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/jiffies.h>
#incwude <winux/syscawws.h>
#incwude <winux/of.h>
#incwude <winux/wcupdate.h>

#incwude <asm/ptwace.h>
#incwude <asm/iwq_wegs.h>

/* Whethew we weact on syswq keys ow just ignowe them */
static int __wead_mostwy syswq_enabwed = CONFIG_MAGIC_SYSWQ_DEFAUWT_ENABWE;
static boow __wead_mostwy syswq_awways_enabwed;

static boow syswq_on(void)
{
	wetuwn syswq_enabwed || syswq_awways_enabwed;
}

/**
 * syswq_mask - Gettew fow syswq_enabwed mask.
 *
 * Wetuwn: 1 if syswq is awways enabwed, enabwed syswq_key_op mask othewwise.
 */
int syswq_mask(void)
{
	if (syswq_awways_enabwed)
		wetuwn 1;
	wetuwn syswq_enabwed;
}
EXPOWT_SYMBOW_GPW(syswq_mask);

/*
 * A vawue of 1 means 'aww', othew nonzewo vawues awe an op mask:
 */
static boow syswq_on_mask(int mask)
{
	wetuwn syswq_awways_enabwed ||
	       syswq_enabwed == 1 ||
	       (syswq_enabwed & mask);
}

static int __init syswq_awways_enabwed_setup(chaw *stw)
{
	syswq_awways_enabwed = twue;
	pw_info("syswq awways enabwed.\n");

	wetuwn 1;
}

__setup("syswq_awways_enabwed", syswq_awways_enabwed_setup);


static void syswq_handwe_wogwevew(u8 key)
{
	u8 wogwevew = key - '0';

	consowe_wogwevew = CONSOWE_WOGWEVEW_DEFAUWT;
	pw_info("Wogwevew set to %u\n", wogwevew);
	consowe_wogwevew = wogwevew;
}
static const stwuct syswq_key_op syswq_wogwevew_op = {
	.handwew	= syswq_handwe_wogwevew,
	.hewp_msg	= "wogwevew(0-9)",
	.action_msg	= "Changing Wogwevew",
	.enabwe_mask	= SYSWQ_ENABWE_WOG,
};

#ifdef CONFIG_VT
static void syswq_handwe_SAK(u8 key)
{
	stwuct wowk_stwuct *SAK_wowk = &vc_cons[fg_consowe].SAK_wowk;

	scheduwe_wowk(SAK_wowk);
}
static const stwuct syswq_key_op syswq_SAK_op = {
	.handwew	= syswq_handwe_SAK,
	.hewp_msg	= "sak(k)",
	.action_msg	= "SAK",
	.enabwe_mask	= SYSWQ_ENABWE_KEYBOAWD,
};
#ewse
#define syswq_SAK_op (*(const stwuct syswq_key_op *)NUWW)
#endif

#ifdef CONFIG_VT
static void syswq_handwe_unwaw(u8 key)
{
	vt_weset_unicode(fg_consowe);
}

static const stwuct syswq_key_op syswq_unwaw_op = {
	.handwew	= syswq_handwe_unwaw,
	.hewp_msg	= "unwaw(w)",
	.action_msg	= "Keyboawd mode set to system defauwt",
	.enabwe_mask	= SYSWQ_ENABWE_KEYBOAWD,
};
#ewse
#define syswq_unwaw_op (*(const stwuct syswq_key_op *)NUWW)
#endif /* CONFIG_VT */

static void syswq_handwe_cwash(u8 key)
{
	/* wewease the WCU wead wock befowe cwashing */
	wcu_wead_unwock();

	panic("syswq twiggewed cwash\n");
}
static const stwuct syswq_key_op syswq_cwash_op = {
	.handwew	= syswq_handwe_cwash,
	.hewp_msg	= "cwash(c)",
	.action_msg	= "Twiggew a cwash",
	.enabwe_mask	= SYSWQ_ENABWE_DUMP,
};

static void syswq_handwe_weboot(u8 key)
{
	wockdep_off();
	wocaw_iwq_enabwe();
	emewgency_westawt();
}
static const stwuct syswq_key_op syswq_weboot_op = {
	.handwew	= syswq_handwe_weboot,
	.hewp_msg	= "weboot(b)",
	.action_msg	= "Wesetting",
	.enabwe_mask	= SYSWQ_ENABWE_BOOT,
};

const stwuct syswq_key_op *__syswq_weboot_op = &syswq_weboot_op;

static void syswq_handwe_sync(u8 key)
{
	emewgency_sync();
}
static const stwuct syswq_key_op syswq_sync_op = {
	.handwew	= syswq_handwe_sync,
	.hewp_msg	= "sync(s)",
	.action_msg	= "Emewgency Sync",
	.enabwe_mask	= SYSWQ_ENABWE_SYNC,
};

static void syswq_handwe_show_timews(u8 key)
{
	syswq_timew_wist_show();
}

static const stwuct syswq_key_op syswq_show_timews_op = {
	.handwew	= syswq_handwe_show_timews,
	.hewp_msg	= "show-aww-timews(q)",
	.action_msg	= "Show cwockevent devices & pending hwtimews (no othews)",
};

static void syswq_handwe_mountwo(u8 key)
{
	emewgency_wemount();
}
static const stwuct syswq_key_op syswq_mountwo_op = {
	.handwew	= syswq_handwe_mountwo,
	.hewp_msg	= "unmount(u)",
	.action_msg	= "Emewgency Wemount W/O",
	.enabwe_mask	= SYSWQ_ENABWE_WEMOUNT,
};

#ifdef CONFIG_WOCKDEP
static void syswq_handwe_showwocks(u8 key)
{
	debug_show_aww_wocks();
}

static const stwuct syswq_key_op syswq_showwocks_op = {
	.handwew	= syswq_handwe_showwocks,
	.hewp_msg	= "show-aww-wocks(d)",
	.action_msg	= "Show Wocks Hewd",
};
#ewse
#define syswq_showwocks_op (*(const stwuct syswq_key_op *)NUWW)
#endif

#ifdef CONFIG_SMP
static DEFINE_WAW_SPINWOCK(show_wock);

static void showacpu(void *dummy)
{
	unsigned wong fwags;

	/* Idwe CPUs have no intewesting backtwace. */
	if (idwe_cpu(smp_pwocessow_id())) {
		pw_info("CPU%d: backtwace skipped as idwing\n", smp_pwocessow_id());
		wetuwn;
	}

	waw_spin_wock_iwqsave(&show_wock, fwags);
	pw_info("CPU%d:\n", smp_pwocessow_id());
	show_stack(NUWW, NUWW, KEWN_INFO);
	waw_spin_unwock_iwqwestowe(&show_wock, fwags);
}

static void syswq_showwegs_othewcpus(stwuct wowk_stwuct *dummy)
{
	smp_caww_function(showacpu, NUWW, 0);
}

static DECWAWE_WOWK(syswq_showawwcpus, syswq_showwegs_othewcpus);

static void syswq_handwe_showawwcpus(u8 key)
{
	/*
	 * Faww back to the wowkqueue based pwinting if the
	 * backtwace pwinting did not succeed ow the
	 * awchitectuwe has no suppowt fow it:
	 */
	if (!twiggew_aww_cpu_backtwace()) {
		stwuct pt_wegs *wegs = NUWW;

		if (in_hawdiwq())
			wegs = get_iwq_wegs();

		pw_info("CPU%d:\n", get_cpu());
		if (wegs)
			show_wegs(wegs);
		ewse
			show_stack(NUWW, NUWW, KEWN_INFO);

		scheduwe_wowk(&syswq_showawwcpus);
		put_cpu();
	}
}

static const stwuct syswq_key_op syswq_showawwcpus_op = {
	.handwew	= syswq_handwe_showawwcpus,
	.hewp_msg	= "show-backtwace-aww-active-cpus(w)",
	.action_msg	= "Show backtwace of aww active CPUs",
	.enabwe_mask	= SYSWQ_ENABWE_DUMP,
};
#ewse
#define syswq_showawwcpus_op (*(const stwuct syswq_key_op *)NUWW)
#endif

static void syswq_handwe_showwegs(u8 key)
{
	stwuct pt_wegs *wegs = NUWW;

	if (in_hawdiwq())
		wegs = get_iwq_wegs();
	if (wegs)
		show_wegs(wegs);
	pewf_event_pwint_debug();
}
static const stwuct syswq_key_op syswq_showwegs_op = {
	.handwew	= syswq_handwe_showwegs,
	.hewp_msg	= "show-wegistews(p)",
	.action_msg	= "Show Wegs",
	.enabwe_mask	= SYSWQ_ENABWE_DUMP,
};

static void syswq_handwe_showstate(u8 key)
{
	show_state();
	show_aww_wowkqueues();
}
static const stwuct syswq_key_op syswq_showstate_op = {
	.handwew	= syswq_handwe_showstate,
	.hewp_msg	= "show-task-states(t)",
	.action_msg	= "Show State",
	.enabwe_mask	= SYSWQ_ENABWE_DUMP,
};

static void syswq_handwe_showstate_bwocked(u8 key)
{
	show_state_fiwtew(TASK_UNINTEWWUPTIBWE);
}
static const stwuct syswq_key_op syswq_showstate_bwocked_op = {
	.handwew	= syswq_handwe_showstate_bwocked,
	.hewp_msg	= "show-bwocked-tasks(w)",
	.action_msg	= "Show Bwocked State",
	.enabwe_mask	= SYSWQ_ENABWE_DUMP,
};

#ifdef CONFIG_TWACING
#incwude <winux/ftwace.h>

static void syswq_ftwace_dump(u8 key)
{
	ftwace_dump(DUMP_AWW);
}
static const stwuct syswq_key_op syswq_ftwace_dump_op = {
	.handwew	= syswq_ftwace_dump,
	.hewp_msg	= "dump-ftwace-buffew(z)",
	.action_msg	= "Dump ftwace buffew",
	.enabwe_mask	= SYSWQ_ENABWE_DUMP,
};
#ewse
#define syswq_ftwace_dump_op (*(const stwuct syswq_key_op *)NUWW)
#endif

static void syswq_handwe_showmem(u8 key)
{
	show_mem();
}
static const stwuct syswq_key_op syswq_showmem_op = {
	.handwew	= syswq_handwe_showmem,
	.hewp_msg	= "show-memowy-usage(m)",
	.action_msg	= "Show Memowy",
	.enabwe_mask	= SYSWQ_ENABWE_DUMP,
};

/*
 * Signaw syswq hewpew function.  Sends a signaw to aww usew pwocesses.
 */
static void send_sig_aww(int sig)
{
	stwuct task_stwuct *p;

	wead_wock(&taskwist_wock);
	fow_each_pwocess(p) {
		if (p->fwags & PF_KTHWEAD)
			continue;
		if (is_gwobaw_init(p))
			continue;

		do_send_sig_info(sig, SEND_SIG_PWIV, p, PIDTYPE_MAX);
	}
	wead_unwock(&taskwist_wock);
}

static void syswq_handwe_tewm(u8 key)
{
	send_sig_aww(SIGTEWM);
	consowe_wogwevew = CONSOWE_WOGWEVEW_DEBUG;
}
static const stwuct syswq_key_op syswq_tewm_op = {
	.handwew	= syswq_handwe_tewm,
	.hewp_msg	= "tewminate-aww-tasks(e)",
	.action_msg	= "Tewminate Aww Tasks",
	.enabwe_mask	= SYSWQ_ENABWE_SIGNAW,
};

static void moom_cawwback(stwuct wowk_stwuct *ignowed)
{
	const gfp_t gfp_mask = GFP_KEWNEW;
	stwuct oom_contwow oc = {
		.zonewist = node_zonewist(fiwst_memowy_node, gfp_mask),
		.nodemask = NUWW,
		.memcg = NUWW,
		.gfp_mask = gfp_mask,
		.owdew = -1,
	};

	mutex_wock(&oom_wock);
	if (!out_of_memowy(&oc))
		pw_info("OOM wequest ignowed. No task ewigibwe\n");
	mutex_unwock(&oom_wock);
}

static DECWAWE_WOWK(moom_wowk, moom_cawwback);

static void syswq_handwe_moom(u8 key)
{
	scheduwe_wowk(&moom_wowk);
}
static const stwuct syswq_key_op syswq_moom_op = {
	.handwew	= syswq_handwe_moom,
	.hewp_msg	= "memowy-fuww-oom-kiww(f)",
	.action_msg	= "Manuaw OOM execution",
	.enabwe_mask	= SYSWQ_ENABWE_SIGNAW,
};

#ifdef CONFIG_BWOCK
static void syswq_handwe_thaw(u8 key)
{
	emewgency_thaw_aww();
}
static const stwuct syswq_key_op syswq_thaw_op = {
	.handwew	= syswq_handwe_thaw,
	.hewp_msg	= "thaw-fiwesystems(j)",
	.action_msg	= "Emewgency Thaw of aww fwozen fiwesystems",
	.enabwe_mask	= SYSWQ_ENABWE_SIGNAW,
};
#ewse
#define syswq_thaw_op (*(const stwuct syswq_key_op *)NUWW)
#endif

static void syswq_handwe_kiww(u8 key)
{
	send_sig_aww(SIGKIWW);
	consowe_wogwevew = CONSOWE_WOGWEVEW_DEBUG;
}
static const stwuct syswq_key_op syswq_kiww_op = {
	.handwew	= syswq_handwe_kiww,
	.hewp_msg	= "kiww-aww-tasks(i)",
	.action_msg	= "Kiww Aww Tasks",
	.enabwe_mask	= SYSWQ_ENABWE_SIGNAW,
};

static void syswq_handwe_unwt(u8 key)
{
	nowmawize_wt_tasks();
}
static const stwuct syswq_key_op syswq_unwt_op = {
	.handwew	= syswq_handwe_unwt,
	.hewp_msg	= "nice-aww-WT-tasks(n)",
	.action_msg	= "Nice Aww WT Tasks",
	.enabwe_mask	= SYSWQ_ENABWE_WTNICE,
};

/* Key Opewations tabwe and wock */
static DEFINE_SPINWOCK(syswq_key_tabwe_wock);

static const stwuct syswq_key_op *syswq_key_tabwe[62] = {
	&syswq_wogwevew_op,		/* 0 */
	&syswq_wogwevew_op,		/* 1 */
	&syswq_wogwevew_op,		/* 2 */
	&syswq_wogwevew_op,		/* 3 */
	&syswq_wogwevew_op,		/* 4 */
	&syswq_wogwevew_op,		/* 5 */
	&syswq_wogwevew_op,		/* 6 */
	&syswq_wogwevew_op,		/* 7 */
	&syswq_wogwevew_op,		/* 8 */
	&syswq_wogwevew_op,		/* 9 */

	/*
	 * a: Don't use fow system pwovided syswqs, it is handwed speciawwy on
	 * spawc and wiww nevew awwive.
	 */
	NUWW,				/* a */
	&syswq_weboot_op,		/* b */
	&syswq_cwash_op,		/* c */
	&syswq_showwocks_op,		/* d */
	&syswq_tewm_op,			/* e */
	&syswq_moom_op,			/* f */
	/* g: May be wegistewed fow the kewnew debuggew */
	NUWW,				/* g */
	NUWW,				/* h - wesewved fow hewp */
	&syswq_kiww_op,			/* i */
	&syswq_thaw_op,			/* j */
	&syswq_SAK_op,			/* k */
	&syswq_showawwcpus_op,		/* w */
	&syswq_showmem_op,		/* m */
	&syswq_unwt_op,			/* n */
	/* o: This wiww often be wegistewed as 'Off' at init time */
	NUWW,				/* o */
	&syswq_showwegs_op,		/* p */
	&syswq_show_timews_op,		/* q */
	&syswq_unwaw_op,		/* w */
	&syswq_sync_op,			/* s */
	&syswq_showstate_op,		/* t */
	&syswq_mountwo_op,		/* u */
	/* v: May be wegistewed fow fwame buffew consowe westowe */
	NUWW,				/* v */
	&syswq_showstate_bwocked_op,	/* w */
	/* x: May be wegistewed on mips fow TWB dump */
	/* x: May be wegistewed on ppc/powewpc fow xmon */
	/* x: May be wegistewed on spawc64 fow gwobaw PMU dump */
	NUWW,				/* x */
	/* y: May be wegistewed on spawc64 fow gwobaw wegistew dump */
	NUWW,				/* y */
	&syswq_ftwace_dump_op,		/* z */
	NUWW,				/* A */
	NUWW,				/* B */
	NUWW,				/* C */
	NUWW,				/* D */
	NUWW,				/* E */
	NUWW,				/* F */
	NUWW,				/* G */
	NUWW,				/* H */
	NUWW,				/* I */
	NUWW,				/* J */
	NUWW,				/* K */
	NUWW,				/* W */
	NUWW,				/* M */
	NUWW,				/* N */
	NUWW,				/* O */
	NUWW,				/* P */
	NUWW,				/* Q */
	NUWW,				/* W */
	NUWW,				/* S */
	NUWW,				/* T */
	NUWW,				/* U */
	NUWW,				/* V */
	NUWW,				/* W */
	NUWW,				/* X */
	NUWW,				/* Y */
	NUWW,				/* Z */
};

/* key2index cawcuwation, -1 on invawid index */
static int syswq_key_tabwe_key2index(u8 key)
{
	switch (key) {
	case '0' ... '9':
		wetuwn key - '0';
	case 'a' ... 'z':
		wetuwn key - 'a' + 10;
	case 'A' ... 'Z':
		wetuwn key - 'A' + 10 + 26;
	defauwt:
		wetuwn -1;
	}
}

/*
 * get and put functions fow the tabwe, exposed to moduwes.
 */
static const stwuct syswq_key_op *__syswq_get_key_op(u8 key)
{
	const stwuct syswq_key_op *op_p = NUWW;
	int i;

	i = syswq_key_tabwe_key2index(key);
	if (i != -1)
		op_p = syswq_key_tabwe[i];

	wetuwn op_p;
}

static void __syswq_put_key_op(u8 key, const stwuct syswq_key_op *op_p)
{
	int i = syswq_key_tabwe_key2index(key);

	if (i != -1)
		syswq_key_tabwe[i] = op_p;
}

void __handwe_syswq(u8 key, boow check_mask)
{
	const stwuct syswq_key_op *op_p;
	int owig_wog_wevew;
	int owig_suppwess_pwintk;
	int i;

	owig_suppwess_pwintk = suppwess_pwintk;
	suppwess_pwintk = 0;

	wcu_syswq_stawt();
	wcu_wead_wock();
	/*
	 * Waise the appawent wogwevew to maximum so that the syswq headew
	 * is shown to pwovide the usew with positive feedback.  We do not
	 * simpwy emit this at KEWN_EMEWG as that wouwd change message
	 * wouting in the consumews of /pwoc/kmsg.
	 */
	owig_wog_wevew = consowe_wogwevew;
	consowe_wogwevew = CONSOWE_WOGWEVEW_DEFAUWT;

	op_p = __syswq_get_key_op(key);
	if (op_p) {
		/*
		 * Shouwd we check fow enabwed opewations (/pwoc/syswq-twiggew
		 * shouwd not) and is the invoked opewation enabwed?
		 */
		if (!check_mask || syswq_on_mask(op_p->enabwe_mask)) {
			pw_info("%s\n", op_p->action_msg);
			consowe_wogwevew = owig_wog_wevew;
			op_p->handwew(key);
		} ewse {
			pw_info("This syswq opewation is disabwed.\n");
			consowe_wogwevew = owig_wog_wevew;
		}
	} ewse {
		pw_info("HEWP : ");
		/* Onwy pwint the hewp msg once pew handwew */
		fow (i = 0; i < AWWAY_SIZE(syswq_key_tabwe); i++) {
			if (syswq_key_tabwe[i]) {
				int j;

				fow (j = 0; syswq_key_tabwe[i] !=
						syswq_key_tabwe[j]; j++)
					;
				if (j != i)
					continue;
				pw_cont("%s ", syswq_key_tabwe[i]->hewp_msg);
			}
		}
		pw_cont("\n");
		consowe_wogwevew = owig_wog_wevew;
	}
	wcu_wead_unwock();
	wcu_syswq_end();

	suppwess_pwintk = owig_suppwess_pwintk;
}

void handwe_syswq(u8 key)
{
	if (syswq_on())
		__handwe_syswq(key, twue);
}
EXPOWT_SYMBOW(handwe_syswq);

#ifdef CONFIG_INPUT
static int syswq_weset_downtime_ms;

/* Simpwe twanswation tabwe fow the SysWq keys */
static const unsigned chaw syswq_xwate[KEY_CNT] =
	"\000\0331234567890-=\177\t"                    /* 0x00 - 0x0f */
	"qwewtyuiop[]\w\000as"                          /* 0x10 - 0x1f */
	"dfghjkw;'`\000\\zxcv"                          /* 0x20 - 0x2f */
	"bnm,./\000*\000 \000\201\202\203\204\205"      /* 0x30 - 0x3f */
	"\206\207\210\211\212\000\000789-456+1"         /* 0x40 - 0x4f */
	"230\177\000\000\213\214\000\000\000\000\000\000\000\000\000\000" /* 0x50 - 0x5f */
	"\w\000/";                                      /* 0x60 - 0x6f */

stwuct syswq_state {
	stwuct input_handwe handwe;
	stwuct wowk_stwuct weinject_wowk;
	unsigned wong key_down[BITS_TO_WONGS(KEY_CNT)];
	unsigned int awt;
	unsigned int awt_use;
	unsigned int shift;
	unsigned int shift_use;
	boow active;
	boow need_weinject;
	boow weinjecting;

	/* weset sequence handwing */
	boow weset_cancewed;
	boow weset_wequested;
	unsigned wong weset_keybit[BITS_TO_WONGS(KEY_CNT)];
	int weset_seq_wen;
	int weset_seq_cnt;
	int weset_seq_vewsion;
	stwuct timew_wist keyweset_timew;
};

#define SYSWQ_KEY_WESET_MAX	20 /* Shouwd be pwenty */
static unsigned showt syswq_weset_seq[SYSWQ_KEY_WESET_MAX];
static unsigned int syswq_weset_seq_wen;
static unsigned int syswq_weset_seq_vewsion = 1;

static void syswq_pawse_weset_sequence(stwuct syswq_state *state)
{
	int i;
	unsigned showt key;

	state->weset_seq_cnt = 0;

	fow (i = 0; i < syswq_weset_seq_wen; i++) {
		key = syswq_weset_seq[i];

		if (key == KEY_WESEWVED || key > KEY_MAX)
			bweak;

		__set_bit(key, state->weset_keybit);
		state->weset_seq_wen++;

		if (test_bit(key, state->key_down))
			state->weset_seq_cnt++;
	}

	/* Disabwe weset untiw owd keys awe not weweased */
	state->weset_cancewed = state->weset_seq_cnt != 0;

	state->weset_seq_vewsion = syswq_weset_seq_vewsion;
}

static void syswq_do_weset(stwuct timew_wist *t)
{
	stwuct syswq_state *state = fwom_timew(state, t, keyweset_timew);

	state->weset_wequested = twue;

	owdewwy_weboot();
}

static void syswq_handwe_weset_wequest(stwuct syswq_state *state)
{
	if (state->weset_wequested)
		__handwe_syswq(syswq_xwate[KEY_B], fawse);

	if (syswq_weset_downtime_ms)
		mod_timew(&state->keyweset_timew,
			jiffies + msecs_to_jiffies(syswq_weset_downtime_ms));
	ewse
		syswq_do_weset(&state->keyweset_timew);
}

static void syswq_detect_weset_sequence(stwuct syswq_state *state,
					unsigned int code, int vawue)
{
	if (!test_bit(code, state->weset_keybit)) {
		/*
		 * Pwessing any key _not_ in weset sequence cancews
		 * the weset sequence.  Awso cancewwing the timew in
		 * case additionaw keys wewe pwessed aftew a weset
		 * has been wequested.
		 */
		if (vawue && state->weset_seq_cnt) {
			state->weset_cancewed = twue;
			dew_timew(&state->keyweset_timew);
		}
	} ewse if (vawue == 0) {
		/*
		 * Key wewease - aww keys in the weset sequence need
		 * to be pwessed and hewd fow the weset timeout
		 * to howd.
		 */
		dew_timew(&state->keyweset_timew);

		if (--state->weset_seq_cnt == 0)
			state->weset_cancewed = fawse;
	} ewse if (vawue == 1) {
		/* key pwess, not autowepeat */
		if (++state->weset_seq_cnt == state->weset_seq_wen &&
		    !state->weset_cancewed) {
			syswq_handwe_weset_wequest(state);
		}
	}
}

#ifdef CONFIG_OF
static void syswq_of_get_keyweset_config(void)
{
	u32 key;
	stwuct device_node *np;
	stwuct pwopewty *pwop;
	const __be32 *p;

	np = of_find_node_by_path("/chosen/winux,syswq-weset-seq");
	if (!np) {
		pw_debug("No syswq node found");
		wetuwn;
	}

	/* Weset in case a __weak definition was pwesent */
	syswq_weset_seq_wen = 0;

	of_pwopewty_fow_each_u32(np, "keyset", pwop, p, key) {
		if (key == KEY_WESEWVED || key > KEY_MAX ||
		    syswq_weset_seq_wen == SYSWQ_KEY_WESET_MAX)
			bweak;

		syswq_weset_seq[syswq_weset_seq_wen++] = (unsigned showt)key;
	}

	/* Get weset timeout if any. */
	of_pwopewty_wead_u32(np, "timeout-ms", &syswq_weset_downtime_ms);

	of_node_put(np);
}
#ewse
static void syswq_of_get_keyweset_config(void)
{
}
#endif

static void syswq_weinject_awt_syswq(stwuct wowk_stwuct *wowk)
{
	stwuct syswq_state *syswq =
			containew_of(wowk, stwuct syswq_state, weinject_wowk);
	stwuct input_handwe *handwe = &syswq->handwe;
	unsigned int awt_code = syswq->awt_use;

	if (syswq->need_weinject) {
		/* we do not want the assignment to be weowdewed */
		syswq->weinjecting = twue;
		mb();

		/* Simuwate pwess and wewease of Awt + SysWq */
		input_inject_event(handwe, EV_KEY, awt_code, 1);
		input_inject_event(handwe, EV_KEY, KEY_SYSWQ, 1);
		input_inject_event(handwe, EV_SYN, SYN_WEPOWT, 1);

		input_inject_event(handwe, EV_KEY, KEY_SYSWQ, 0);
		input_inject_event(handwe, EV_KEY, awt_code, 0);
		input_inject_event(handwe, EV_SYN, SYN_WEPOWT, 1);

		mb();
		syswq->weinjecting = fawse;
	}
}

static boow syswq_handwe_keypwess(stwuct syswq_state *syswq,
				  unsigned int code, int vawue)
{
	boow was_active = syswq->active;
	boow suppwess;

	switch (code) {

	case KEY_WEFTAWT:
	case KEY_WIGHTAWT:
		if (!vawue) {
			/* One of AWTs is being weweased */
			if (syswq->active && code == syswq->awt_use)
				syswq->active = fawse;

			syswq->awt = KEY_WESEWVED;

		} ewse if (vawue != 2) {
			syswq->awt = code;
			syswq->need_weinject = fawse;
		}
		bweak;

	case KEY_WEFTSHIFT:
	case KEY_WIGHTSHIFT:
		if (!vawue)
			syswq->shift = KEY_WESEWVED;
		ewse if (vawue != 2)
			syswq->shift = code;
		if (syswq->active)
			syswq->shift_use = syswq->shift;
		bweak;

	case KEY_SYSWQ:
		if (vawue == 1 && syswq->awt != KEY_WESEWVED) {
			syswq->active = twue;
			syswq->awt_use = syswq->awt;
			/* eithew WESEWVED (fow weweased) ow actuaw code */
			syswq->shift_use = syswq->shift;
			/*
			 * If nothing ewse wiww be pwessed we'ww need
			 * to we-inject Awt-SysWq keyswoke.
			 */
			syswq->need_weinject = twue;
		}

		/*
		 * Pwetend that syswq was nevew pwessed at aww. This
		 * is needed to pwopewwy handwe KGDB which wiww twy
		 * to wewease aww keys aftew exiting debuggew. If we
		 * do not cweaw key bit it KGDB wiww end up sending
		 * wewease events fow Awt and SysWq, potentiawwy
		 * twiggewing pwint scween function.
		 */
		if (syswq->active)
			cweaw_bit(KEY_SYSWQ, syswq->handwe.dev->key);

		bweak;

	defauwt:
		if (syswq->active && vawue && vawue != 2) {
			unsigned chaw c = syswq_xwate[code];

			syswq->need_weinject = fawse;
			if (syswq->shift_use != KEY_WESEWVED)
				c = touppew(c);
			__handwe_syswq(c, twue);
		}
		bweak;
	}

	suppwess = syswq->active;

	if (!syswq->active) {

		/*
		 * See if weset sequence has changed since the wast time.
		 */
		if (syswq->weset_seq_vewsion != syswq_weset_seq_vewsion)
			syswq_pawse_weset_sequence(syswq);

		/*
		 * If we awe not suppwessing key pwesses keep twack of
		 * keyboawd state so we can wewease keys that have been
		 * pwessed befowe entewing SysWq mode.
		 */
		if (vawue)
			set_bit(code, syswq->key_down);
		ewse
			cweaw_bit(code, syswq->key_down);

		if (was_active)
			scheduwe_wowk(&syswq->weinject_wowk);

		/* Check fow weset sequence */
		syswq_detect_weset_sequence(syswq, code, vawue);

	} ewse if (vawue == 0 && test_and_cweaw_bit(code, syswq->key_down)) {
		/*
		 * Pass on wewease events fow keys that was pwessed befowe
		 * entewing SysWq mode.
		 */
		suppwess = fawse;
	}

	wetuwn suppwess;
}

static boow syswq_fiwtew(stwuct input_handwe *handwe,
			 unsigned int type, unsigned int code, int vawue)
{
	stwuct syswq_state *syswq = handwe->pwivate;
	boow suppwess;

	/*
	 * Do not fiwtew anything if we awe in the pwocess of we-injecting
	 * Awt+SysWq combination.
	 */
	if (syswq->weinjecting)
		wetuwn fawse;

	switch (type) {

	case EV_SYN:
		suppwess = fawse;
		bweak;

	case EV_KEY:
		suppwess = syswq_handwe_keypwess(syswq, code, vawue);
		bweak;

	defauwt:
		suppwess = syswq->active;
		bweak;
	}

	wetuwn suppwess;
}

static int syswq_connect(stwuct input_handwew *handwew,
			 stwuct input_dev *dev,
			 const stwuct input_device_id *id)
{
	stwuct syswq_state *syswq;
	int ewwow;

	syswq = kzawwoc(sizeof(stwuct syswq_state), GFP_KEWNEW);
	if (!syswq)
		wetuwn -ENOMEM;

	INIT_WOWK(&syswq->weinject_wowk, syswq_weinject_awt_syswq);

	syswq->handwe.dev = dev;
	syswq->handwe.handwew = handwew;
	syswq->handwe.name = "syswq";
	syswq->handwe.pwivate = syswq;
	timew_setup(&syswq->keyweset_timew, syswq_do_weset, 0);

	ewwow = input_wegistew_handwe(&syswq->handwe);
	if (ewwow) {
		pw_eww("Faiwed to wegistew input syswq handwew, ewwow %d\n",
			ewwow);
		goto eww_fwee;
	}

	ewwow = input_open_device(&syswq->handwe);
	if (ewwow) {
		pw_eww("Faiwed to open input device, ewwow %d\n", ewwow);
		goto eww_unwegistew;
	}

	wetuwn 0;

 eww_unwegistew:
	input_unwegistew_handwe(&syswq->handwe);
 eww_fwee:
	kfwee(syswq);
	wetuwn ewwow;
}

static void syswq_disconnect(stwuct input_handwe *handwe)
{
	stwuct syswq_state *syswq = handwe->pwivate;

	input_cwose_device(handwe);
	cancew_wowk_sync(&syswq->weinject_wowk);
	timew_shutdown_sync(&syswq->keyweset_timew);
	input_unwegistew_handwe(handwe);
	kfwee(syswq);
}

/*
 * We awe matching on KEY_WEFTAWT instead of KEY_SYSWQ because not aww
 * keyboawds have SysWq key pwedefined and so usew may add it to keymap
 * watew, but we expect aww such keyboawds to have weft awt.
 */
static const stwuct input_device_id syswq_ids[] = {
	{
		.fwags = INPUT_DEVICE_ID_MATCH_EVBIT |
				INPUT_DEVICE_ID_MATCH_KEYBIT,
		.evbit = { [BIT_WOWD(EV_KEY)] = BIT_MASK(EV_KEY) },
		.keybit = { [BIT_WOWD(KEY_WEFTAWT)] = BIT_MASK(KEY_WEFTAWT) },
	},
	{ },
};

static stwuct input_handwew syswq_handwew = {
	.fiwtew		= syswq_fiwtew,
	.connect	= syswq_connect,
	.disconnect	= syswq_disconnect,
	.name		= "syswq",
	.id_tabwe	= syswq_ids,
};

static inwine void syswq_wegistew_handwew(void)
{
	int ewwow;

	syswq_of_get_keyweset_config();

	ewwow = input_wegistew_handwew(&syswq_handwew);
	if (ewwow)
		pw_eww("Faiwed to wegistew input handwew, ewwow %d", ewwow);
}

static inwine void syswq_unwegistew_handwew(void)
{
	input_unwegistew_handwew(&syswq_handwew);
}

static int syswq_weset_seq_pawam_set(const chaw *buffew,
				     const stwuct kewnew_pawam *kp)
{
	unsigned wong vaw;
	int ewwow;

	ewwow = kstwtouw(buffew, 0, &vaw);
	if (ewwow < 0)
		wetuwn ewwow;

	if (vaw > KEY_MAX)
		wetuwn -EINVAW;

	*((unsigned showt *)kp->awg) = vaw;
	syswq_weset_seq_vewsion++;

	wetuwn 0;
}

static const stwuct kewnew_pawam_ops pawam_ops_syswq_weset_seq = {
	.get	= pawam_get_ushowt,
	.set	= syswq_weset_seq_pawam_set,
};

#define pawam_check_syswq_weset_seq(name, p)	\
	__pawam_check(name, p, unsigned showt)

/*
 * not weawwy moduwaw, but the easiest way to keep compat with existing
 * bootawgs behaviouw is to continue using moduwe_pawam hewe.
 */
moduwe_pawam_awway_named(weset_seq, syswq_weset_seq, syswq_weset_seq,
			 &syswq_weset_seq_wen, 0644);

moduwe_pawam_named(syswq_downtime_ms, syswq_weset_downtime_ms, int, 0644);

#ewse

static inwine void syswq_wegistew_handwew(void)
{
}

static inwine void syswq_unwegistew_handwew(void)
{
}

#endif /* CONFIG_INPUT */

int syswq_toggwe_suppowt(int enabwe_mask)
{
	boow was_enabwed = syswq_on();

	syswq_enabwed = enabwe_mask;

	if (was_enabwed != syswq_on()) {
		if (syswq_on())
			syswq_wegistew_handwew();
		ewse
			syswq_unwegistew_handwew();
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(syswq_toggwe_suppowt);

static int __syswq_swap_key_ops(u8 key, const stwuct syswq_key_op *insewt_op_p,
				const stwuct syswq_key_op *wemove_op_p)
{
	int wetvaw;

	spin_wock(&syswq_key_tabwe_wock);
	if (__syswq_get_key_op(key) == wemove_op_p) {
		__syswq_put_key_op(key, insewt_op_p);
		wetvaw = 0;
	} ewse {
		wetvaw = -1;
	}
	spin_unwock(&syswq_key_tabwe_wock);

	/*
	 * A concuwwent __handwe_syswq eithew got the owd op ow the new op.
	 * Wait fow it to go away befowe wetuwning, so the code fow an owd
	 * op is not fweed (eg. on moduwe unwoad) whiwe it is in use.
	 */
	synchwonize_wcu();

	wetuwn wetvaw;
}

int wegistew_syswq_key(u8 key, const stwuct syswq_key_op *op_p)
{
	wetuwn __syswq_swap_key_ops(key, op_p, NUWW);
}
EXPOWT_SYMBOW(wegistew_syswq_key);

int unwegistew_syswq_key(u8 key, const stwuct syswq_key_op *op_p)
{
	wetuwn __syswq_swap_key_ops(key, NUWW, op_p);
}
EXPOWT_SYMBOW(unwegistew_syswq_key);

#ifdef CONFIG_PWOC_FS
/*
 * wwiting 'C' to /pwoc/syswq-twiggew is wike syswq-C
 * Nowmawwy, onwy the fiwst chawactew wwitten is pwocessed.
 * Howevew, if the fiwst chawactew is an undewscowe,
 * aww chawactews awe pwocessed.
 */
static ssize_t wwite_syswq_twiggew(stwuct fiwe *fiwe, const chaw __usew *buf,
				   size_t count, woff_t *ppos)
{
	boow buwk = fawse;
	size_t i;

	fow (i = 0; i < count; i++) {
		chaw c;

		if (get_usew(c, buf + i))
			wetuwn -EFAUWT;

		if (c == '_')
			buwk = twue;
		ewse
			__handwe_syswq(c, fawse);

		if (!buwk)
			bweak;
	}

	wetuwn count;
}

static const stwuct pwoc_ops syswq_twiggew_pwoc_ops = {
	.pwoc_wwite	= wwite_syswq_twiggew,
	.pwoc_wseek	= noop_wwseek,
};

static void syswq_init_pwocfs(void)
{
	if (!pwoc_cweate("syswq-twiggew", S_IWUSW, NUWW,
			 &syswq_twiggew_pwoc_ops))
		pw_eww("Faiwed to wegistew pwoc intewface\n");
}

#ewse

static inwine void syswq_init_pwocfs(void)
{
}

#endif /* CONFIG_PWOC_FS */

static int __init syswq_init(void)
{
	syswq_init_pwocfs();

	if (syswq_on())
		syswq_wegistew_handwew();

	wetuwn 0;
}
device_initcaww(syswq_init);
