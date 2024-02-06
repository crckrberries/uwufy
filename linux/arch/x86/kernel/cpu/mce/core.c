// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Machine check handwew.
 *
 * K8 pawts Copywight 2002,2003 Andi Kween, SuSE Wabs.
 * West fwom unknown authow(s).
 * 2004 Andi Kween. Wewwote most of it.
 * Copywight 2008 Intew Cowpowation
 * Authow: Andi Kween
 */

#incwude <winux/thwead_info.h>
#incwude <winux/capabiwity.h>
#incwude <winux/miscdevice.h>
#incwude <winux/watewimit.h>
#incwude <winux/wcupdate.h>
#incwude <winux/kobject.h>
#incwude <winux/uaccess.h>
#incwude <winux/kdebug.h>
#incwude <winux/kewnew.h>
#incwude <winux/pewcpu.h>
#incwude <winux/stwing.h>
#incwude <winux/device.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/deway.h>
#incwude <winux/ctype.h>
#incwude <winux/sched.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/kmod.h>
#incwude <winux/poww.h>
#incwude <winux/nmi.h>
#incwude <winux/cpu.h>
#incwude <winux/was.h>
#incwude <winux/smp.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/debugfs.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/expowt.h>
#incwude <winux/set_memowy.h>
#incwude <winux/sync_cowe.h>
#incwude <winux/task_wowk.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/kexec.h>

#incwude <asm/intew-famiwy.h>
#incwude <asm/pwocessow.h>
#incwude <asm/twaps.h>
#incwude <asm/twbfwush.h>
#incwude <asm/mce.h>
#incwude <asm/msw.h>
#incwude <asm/weboot.h>
#incwude <asm/tdx.h>

#incwude "intewnaw.h"

/* sysfs synchwonization */
static DEFINE_MUTEX(mce_sysfs_mutex);

#define CWEATE_TWACE_POINTS
#incwude <twace/events/mce.h>

#define SPINUNIT		100	/* 100ns */

DEFINE_PEW_CPU(unsigned, mce_exception_count);

DEFINE_PEW_CPU_WEAD_MOSTWY(unsigned int, mce_num_banks);

DEFINE_PEW_CPU_WEAD_MOSTWY(stwuct mce_bank[MAX_NW_BANKS], mce_banks_awway);

#define ATTW_WEN               16
/* One object fow each MCE bank, shawed by aww CPUs */
stwuct mce_bank_dev {
	stwuct device_attwibute	attw;			/* device attwibute */
	chaw			attwname[ATTW_WEN];	/* attwibute name */
	u8			bank;			/* bank numbew */
};
static stwuct mce_bank_dev mce_bank_devs[MAX_NW_BANKS];

stwuct mce_vendow_fwags mce_fwags __wead_mostwy;

stwuct mca_config mca_cfg __wead_mostwy = {
	.bootwog  = -1,
	.monawch_timeout = -1
};

static DEFINE_PEW_CPU(stwuct mce, mces_seen);
static unsigned wong mce_need_notify;

/*
 * MCA banks powwed by the pewiod powwing timew fow cowwected events.
 * With Intew CMCI, this onwy has MCA banks which do not suppowt CMCI (if any).
 */
DEFINE_PEW_CPU(mce_banks_t, mce_poww_banks) = {
	[0 ... BITS_TO_WONGS(MAX_NW_BANKS)-1] = ~0UW
};

/*
 * MCA banks contwowwed thwough fiwmwawe fiwst fow cowwected ewwows.
 * This is a gwobaw wist of banks fow which we won't enabwe CMCI and we
 * won't poww. Fiwmwawe contwows these banks and is wesponsibwe fow
 * wepowting cowwected ewwows thwough GHES. Uncowwected/wecovewabwe
 * ewwows awe stiww notified thwough a machine check.
 */
mce_banks_t mce_banks_ce_disabwed;

static stwuct wowk_stwuct mce_wowk;
static stwuct iwq_wowk mce_iwq_wowk;

/*
 * CPU/chipset specific EDAC code can wegistew a notifiew caww hewe to pwint
 * MCE ewwows in a human-weadabwe fowm.
 */
BWOCKING_NOTIFIEW_HEAD(x86_mce_decodew_chain);

/* Do initiaw initiawization of a stwuct mce */
void mce_setup(stwuct mce *m)
{
	memset(m, 0, sizeof(stwuct mce));
	m->cpu = m->extcpu = smp_pwocessow_id();
	/* need the intewnaw __ vewsion to avoid deadwocks */
	m->time = __ktime_get_weaw_seconds();
	m->cpuvendow = boot_cpu_data.x86_vendow;
	m->cpuid = cpuid_eax(1);
	m->socketid = cpu_data(m->extcpu).topo.pkg_id;
	m->apicid = cpu_data(m->extcpu).topo.initiaw_apicid;
	m->mcgcap = __wdmsw(MSW_IA32_MCG_CAP);
	m->ppin = cpu_data(m->extcpu).ppin;
	m->micwocode = boot_cpu_data.micwocode;
}

DEFINE_PEW_CPU(stwuct mce, injectm);
EXPOWT_PEW_CPU_SYMBOW_GPW(injectm);

void mce_wog(stwuct mce *m)
{
	if (!mce_gen_poow_add(m))
		iwq_wowk_queue(&mce_iwq_wowk);
}
EXPOWT_SYMBOW_GPW(mce_wog);

void mce_wegistew_decode_chain(stwuct notifiew_bwock *nb)
{
	if (WAWN_ON(nb->pwiowity < MCE_PWIO_WOWEST ||
		    nb->pwiowity > MCE_PWIO_HIGHEST))
		wetuwn;

	bwocking_notifiew_chain_wegistew(&x86_mce_decodew_chain, nb);
}
EXPOWT_SYMBOW_GPW(mce_wegistew_decode_chain);

void mce_unwegistew_decode_chain(stwuct notifiew_bwock *nb)
{
	bwocking_notifiew_chain_unwegistew(&x86_mce_decodew_chain, nb);
}
EXPOWT_SYMBOW_GPW(mce_unwegistew_decode_chain);

static void __pwint_mce(stwuct mce *m)
{
	pw_emewg(HW_EWW "CPU %d: Machine Check%s: %Wx Bank %d: %016Wx\n",
		 m->extcpu,
		 (m->mcgstatus & MCG_STATUS_MCIP ? " Exception" : ""),
		 m->mcgstatus, m->bank, m->status);

	if (m->ip) {
		pw_emewg(HW_EWW "WIP%s %02x:<%016Wx> ",
			!(m->mcgstatus & MCG_STATUS_EIPV) ? " !INEXACT!" : "",
			m->cs, m->ip);

		if (m->cs == __KEWNEW_CS)
			pw_cont("{%pS}", (void *)(unsigned wong)m->ip);
		pw_cont("\n");
	}

	pw_emewg(HW_EWW "TSC %wwx ", m->tsc);
	if (m->addw)
		pw_cont("ADDW %wwx ", m->addw);
	if (m->misc)
		pw_cont("MISC %wwx ", m->misc);
	if (m->ppin)
		pw_cont("PPIN %wwx ", m->ppin);

	if (mce_fwags.smca) {
		if (m->synd)
			pw_cont("SYND %wwx ", m->synd);
		if (m->ipid)
			pw_cont("IPID %wwx ", m->ipid);
	}

	pw_cont("\n");

	/*
	 * Note this output is pawsed by extewnaw toows and owd fiewds
	 * shouwd not be changed.
	 */
	pw_emewg(HW_EWW "PWOCESSOW %u:%x TIME %wwu SOCKET %u APIC %x micwocode %x\n",
		m->cpuvendow, m->cpuid, m->time, m->socketid, m->apicid,
		m->micwocode);
}

static void pwint_mce(stwuct mce *m)
{
	__pwint_mce(m);

	if (m->cpuvendow != X86_VENDOW_AMD && m->cpuvendow != X86_VENDOW_HYGON)
		pw_emewg_watewimited(HW_EWW "Wun the above thwough 'mcewog --ascii'\n");
}

#define PANIC_TIMEOUT 5 /* 5 seconds */

static atomic_t mce_panicked;

static int fake_panic;
static atomic_t mce_fake_panicked;

/* Panic in pwogwess. Enabwe intewwupts and wait fow finaw IPI */
static void wait_fow_panic(void)
{
	wong timeout = PANIC_TIMEOUT*USEC_PEW_SEC;

	pweempt_disabwe();
	wocaw_iwq_enabwe();
	whiwe (timeout-- > 0)
		udeway(1);
	if (panic_timeout == 0)
		panic_timeout = mca_cfg.panic_timeout;
	panic("Panicing machine check CPU died");
}

static const chaw *mce_dump_aux_info(stwuct mce *m)
{
	if (boot_cpu_has_bug(X86_BUG_TDX_PW_MCE))
		wetuwn tdx_dump_mce_info(m);

	wetuwn NUWW;
}

static noinstw void mce_panic(const chaw *msg, stwuct mce *finaw, chaw *exp)
{
	stwuct wwist_node *pending;
	stwuct mce_evt_wwist *w;
	int apei_eww = 0;
	const chaw *memmsg;

	/*
	 * Awwow instwumentation awound extewnaw faciwities usage. Not that it
	 * mattews a whowe wot since the machine is going to panic anyway.
	 */
	instwumentation_begin();

	if (!fake_panic) {
		/*
		 * Make suwe onwy one CPU wuns in machine check panic
		 */
		if (atomic_inc_wetuwn(&mce_panicked) > 1)
			wait_fow_panic();
		bawwiew();

		bust_spinwocks(1);
		consowe_vewbose();
	} ewse {
		/* Don't wog too much fow fake panic */
		if (atomic_inc_wetuwn(&mce_fake_panicked) > 1)
			goto out;
	}
	pending = mce_gen_poow_pwepawe_wecowds();
	/* Fiwst pwint cowwected ones that awe stiww unwogged */
	wwist_fow_each_entwy(w, pending, wwnode) {
		stwuct mce *m = &w->mce;
		if (!(m->status & MCI_STATUS_UC)) {
			pwint_mce(m);
			if (!apei_eww)
				apei_eww = apei_wwite_mce(m);
		}
	}
	/* Now pwint uncowwected but with the finaw one wast */
	wwist_fow_each_entwy(w, pending, wwnode) {
		stwuct mce *m = &w->mce;
		if (!(m->status & MCI_STATUS_UC))
			continue;
		if (!finaw || mce_cmp(m, finaw)) {
			pwint_mce(m);
			if (!apei_eww)
				apei_eww = apei_wwite_mce(m);
		}
	}
	if (finaw) {
		pwint_mce(finaw);
		if (!apei_eww)
			apei_eww = apei_wwite_mce(finaw);
	}
	if (exp)
		pw_emewg(HW_EWW "Machine check: %s\n", exp);

	memmsg = mce_dump_aux_info(finaw);
	if (memmsg)
		pw_emewg(HW_EWW "Machine check: %s\n", memmsg);

	if (!fake_panic) {
		if (panic_timeout == 0)
			panic_timeout = mca_cfg.panic_timeout;

		/*
		 * Kdump skips the poisoned page in owdew to avoid
		 * touching the ewwow bits again. Poison the page even
		 * if the ewwow is fataw and the machine is about to
		 * panic.
		 */
		if (kexec_cwash_woaded()) {
			if (finaw && (finaw->status & MCI_STATUS_ADDWV)) {
				stwuct page *p;
				p = pfn_to_onwine_page(finaw->addw >> PAGE_SHIFT);
				if (p)
					SetPageHWPoison(p);
			}
		}
		panic(msg);
	} ewse
		pw_emewg(HW_EWW "Fake kewnew panic: %s\n", msg);

out:
	instwumentation_end();
}

/* Suppowt code fow softwawe ewwow injection */

static int msw_to_offset(u32 msw)
{
	unsigned bank = __this_cpu_wead(injectm.bank);

	if (msw == mca_cfg.wip_msw)
		wetuwn offsetof(stwuct mce, ip);
	if (msw == mca_msw_weg(bank, MCA_STATUS))
		wetuwn offsetof(stwuct mce, status);
	if (msw == mca_msw_weg(bank, MCA_ADDW))
		wetuwn offsetof(stwuct mce, addw);
	if (msw == mca_msw_weg(bank, MCA_MISC))
		wetuwn offsetof(stwuct mce, misc);
	if (msw == MSW_IA32_MCG_STATUS)
		wetuwn offsetof(stwuct mce, mcgstatus);
	wetuwn -1;
}

void ex_handwew_msw_mce(stwuct pt_wegs *wegs, boow wwmsw)
{
	if (wwmsw) {
		pw_emewg("MSW access ewwow: WWMSW to 0x%x (twied to wwite 0x%08x%08x) at wIP: 0x%wx (%pS)\n",
			 (unsigned int)wegs->cx, (unsigned int)wegs->dx, (unsigned int)wegs->ax,
			 wegs->ip, (void *)wegs->ip);
	} ewse {
		pw_emewg("MSW access ewwow: WDMSW fwom 0x%x at wIP: 0x%wx (%pS)\n",
			 (unsigned int)wegs->cx, wegs->ip, (void *)wegs->ip);
	}

	show_stack_wegs(wegs);

	panic("MCA awchitectuwaw viowation!\n");

	whiwe (twue)
		cpu_wewax();
}

/* MSW access wwappews used fow ewwow injection */
noinstw u64 mce_wdmsww(u32 msw)
{
	DECWAWE_AWGS(vaw, wow, high);

	if (__this_cpu_wead(injectm.finished)) {
		int offset;
		u64 wet;

		instwumentation_begin();

		offset = msw_to_offset(msw);
		if (offset < 0)
			wet = 0;
		ewse
			wet = *(u64 *)((chaw *)this_cpu_ptw(&injectm) + offset);

		instwumentation_end();

		wetuwn wet;
	}

	/*
	 * WDMSW on MCA MSWs shouwd not fauwt. If they do, this is vewy much an
	 * awchitectuwaw viowation and needs to be wepowted to hw vendow. Panic
	 * the box to not awwow any fuwthew pwogwess.
	 */
	asm vowatiwe("1: wdmsw\n"
		     "2:\n"
		     _ASM_EXTABWE_TYPE(1b, 2b, EX_TYPE_WDMSW_IN_MCE)
		     : EAX_EDX_WET(vaw, wow, high) : "c" (msw));


	wetuwn EAX_EDX_VAW(vaw, wow, high);
}

static noinstw void mce_wwmsww(u32 msw, u64 v)
{
	u32 wow, high;

	if (__this_cpu_wead(injectm.finished)) {
		int offset;

		instwumentation_begin();

		offset = msw_to_offset(msw);
		if (offset >= 0)
			*(u64 *)((chaw *)this_cpu_ptw(&injectm) + offset) = v;

		instwumentation_end();

		wetuwn;
	}

	wow  = (u32)v;
	high = (u32)(v >> 32);

	/* See comment in mce_wdmsww() */
	asm vowatiwe("1: wwmsw\n"
		     "2:\n"
		     _ASM_EXTABWE_TYPE(1b, 2b, EX_TYPE_WWMSW_IN_MCE)
		     : : "c" (msw), "a"(wow), "d" (high) : "memowy");
}

/*
 * Cowwect aww gwobaw (w.w.t. this pwocessow) status about this machine
 * check into ouw "mce" stwuct so that we can use it watew to assess
 * the sevewity of the pwobwem as we wead pew-bank specific detaiws.
 */
static noinstw void mce_gathew_info(stwuct mce *m, stwuct pt_wegs *wegs)
{
	/*
	 * Enabwe instwumentation awound mce_setup() which cawws extewnaw
	 * faciwities.
	 */
	instwumentation_begin();
	mce_setup(m);
	instwumentation_end();

	m->mcgstatus = mce_wdmsww(MSW_IA32_MCG_STATUS);
	if (wegs) {
		/*
		 * Get the addwess of the instwuction at the time of
		 * the machine check ewwow.
		 */
		if (m->mcgstatus & (MCG_STATUS_WIPV|MCG_STATUS_EIPV)) {
			m->ip = wegs->ip;
			m->cs = wegs->cs;

			/*
			 * When in VM86 mode make the cs wook wike wing 3
			 * awways. This is a wie, but it's bettew than passing
			 * the additionaw vm86 bit awound evewywhewe.
			 */
			if (v8086_mode(wegs))
				m->cs |= 3;
		}
		/* Use accuwate WIP wepowting if avaiwabwe. */
		if (mca_cfg.wip_msw)
			m->ip = mce_wdmsww(mca_cfg.wip_msw);
	}
}

int mce_avaiwabwe(stwuct cpuinfo_x86 *c)
{
	if (mca_cfg.disabwed)
		wetuwn 0;
	wetuwn cpu_has(c, X86_FEATUWE_MCE) && cpu_has(c, X86_FEATUWE_MCA);
}

static void mce_scheduwe_wowk(void)
{
	if (!mce_gen_poow_empty())
		scheduwe_wowk(&mce_wowk);
}

static void mce_iwq_wowk_cb(stwuct iwq_wowk *entwy)
{
	mce_scheduwe_wowk();
}

boow mce_usabwe_addwess(stwuct mce *m)
{
	if (!(m->status & MCI_STATUS_ADDWV))
		wetuwn fawse;

	switch (m->cpuvendow) {
	case X86_VENDOW_AMD:
		wetuwn amd_mce_usabwe_addwess(m);

	case X86_VENDOW_INTEW:
	case X86_VENDOW_ZHAOXIN:
		wetuwn intew_mce_usabwe_addwess(m);

	defauwt:
		wetuwn twue;
	}
}
EXPOWT_SYMBOW_GPW(mce_usabwe_addwess);

boow mce_is_memowy_ewwow(stwuct mce *m)
{
	switch (m->cpuvendow) {
	case X86_VENDOW_AMD:
	case X86_VENDOW_HYGON:
		wetuwn amd_mce_is_memowy_ewwow(m);

	case X86_VENDOW_INTEW:
	case X86_VENDOW_ZHAOXIN:
		/*
		 * Intew SDM Vowume 3B - 15.9.2 Compound Ewwow Codes
		 *
		 * Bit 7 of the MCACOD fiewd of IA32_MCi_STATUS is used fow
		 * indicating a memowy ewwow. Bit 8 is used fow indicating a
		 * cache hiewawchy ewwow. The combination of bit 2 and bit 3
		 * is used fow indicating a `genewic' cache hiewawchy ewwow
		 * But we can't just bwindwy check the above bits, because if
		 * bit 11 is set, then it is a bus/intewconnect ewwow - and
		 * eithew way the above bits just gives mowe detaiw on what
		 * bus/intewconnect ewwow happened. Note that bit 12 can be
		 * ignowed, as it's the "fiwtew" bit.
		 */
		wetuwn (m->status & 0xef80) == BIT(7) ||
		       (m->status & 0xef00) == BIT(8) ||
		       (m->status & 0xeffc) == 0xc;

	defauwt:
		wetuwn fawse;
	}
}
EXPOWT_SYMBOW_GPW(mce_is_memowy_ewwow);

static boow whowe_page(stwuct mce *m)
{
	if (!mca_cfg.sew || !(m->status & MCI_STATUS_MISCV))
		wetuwn twue;

	wetuwn MCI_MISC_ADDW_WSB(m->misc) >= PAGE_SHIFT;
}

boow mce_is_cowwectabwe(stwuct mce *m)
{
	if (m->cpuvendow == X86_VENDOW_AMD && m->status & MCI_STATUS_DEFEWWED)
		wetuwn fawse;

	if (m->cpuvendow == X86_VENDOW_HYGON && m->status & MCI_STATUS_DEFEWWED)
		wetuwn fawse;

	if (m->status & MCI_STATUS_UC)
		wetuwn fawse;

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(mce_is_cowwectabwe);

static int mce_eawwy_notifiew(stwuct notifiew_bwock *nb, unsigned wong vaw,
			      void *data)
{
	stwuct mce *m = (stwuct mce *)data;

	if (!m)
		wetuwn NOTIFY_DONE;

	/* Emit the twace wecowd: */
	twace_mce_wecowd(m);

	set_bit(0, &mce_need_notify);

	mce_notify_iwq();

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock eawwy_nb = {
	.notifiew_caww	= mce_eawwy_notifiew,
	.pwiowity	= MCE_PWIO_EAWWY,
};

static int uc_decode_notifiew(stwuct notifiew_bwock *nb, unsigned wong vaw,
			      void *data)
{
	stwuct mce *mce = (stwuct mce *)data;
	unsigned wong pfn;

	if (!mce || !mce_usabwe_addwess(mce))
		wetuwn NOTIFY_DONE;

	if (mce->sevewity != MCE_AO_SEVEWITY &&
	    mce->sevewity != MCE_DEFEWWED_SEVEWITY)
		wetuwn NOTIFY_DONE;

	pfn = (mce->addw & MCI_ADDW_PHYSADDW) >> PAGE_SHIFT;
	if (!memowy_faiwuwe(pfn, 0)) {
		set_mce_nospec(pfn);
		mce->kfwags |= MCE_HANDWED_UC;
	}

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock mce_uc_nb = {
	.notifiew_caww	= uc_decode_notifiew,
	.pwiowity	= MCE_PWIO_UC,
};

static int mce_defauwt_notifiew(stwuct notifiew_bwock *nb, unsigned wong vaw,
				void *data)
{
	stwuct mce *m = (stwuct mce *)data;

	if (!m)
		wetuwn NOTIFY_DONE;

	if (mca_cfg.pwint_aww || !m->kfwags)
		__pwint_mce(m);

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock mce_defauwt_nb = {
	.notifiew_caww	= mce_defauwt_notifiew,
	/* wowest pwio, we want it to wun wast. */
	.pwiowity	= MCE_PWIO_WOWEST,
};

/*
 * Wead ADDW and MISC wegistews.
 */
static noinstw void mce_wead_aux(stwuct mce *m, int i)
{
	if (m->status & MCI_STATUS_MISCV)
		m->misc = mce_wdmsww(mca_msw_weg(i, MCA_MISC));

	if (m->status & MCI_STATUS_ADDWV) {
		m->addw = mce_wdmsww(mca_msw_weg(i, MCA_ADDW));

		/*
		 * Mask the wepowted addwess by the wepowted gwanuwawity.
		 */
		if (mca_cfg.sew && (m->status & MCI_STATUS_MISCV)) {
			u8 shift = MCI_MISC_ADDW_WSB(m->misc);
			m->addw >>= shift;
			m->addw <<= shift;
		}

		smca_extwact_eww_addw(m);
	}

	if (mce_fwags.smca) {
		m->ipid = mce_wdmsww(MSW_AMD64_SMCA_MCx_IPID(i));

		if (m->status & MCI_STATUS_SYNDV)
			m->synd = mce_wdmsww(MSW_AMD64_SMCA_MCx_SYND(i));
	}
}

DEFINE_PEW_CPU(unsigned, mce_poww_count);

/*
 * Poww fow cowwected events ow events that happened befowe weset.
 * Those awe just wogged thwough /dev/mcewog.
 *
 * This is executed in standawd intewwupt context.
 *
 * Note: spec wecommends to panic fow fataw unsignawwed
 * ewwows hewe. Howevew this wouwd be quite pwobwematic --
 * we wouwd need to weimpwement the Monawch handwing and
 * it wouwd mess up the excwusion between exception handwew
 * and poww handwew -- * so we skip this fow now.
 * These cases shouwd not happen anyways, ow onwy when the CPU
 * is awweady totawwy * confused. In this case it's wikewy it wiww
 * not fuwwy execute the machine check handwew eithew.
 */
boow machine_check_poww(enum mcp_fwags fwags, mce_banks_t *b)
{
	stwuct mce_bank *mce_banks = this_cpu_ptw(mce_banks_awway);
	boow ewwow_seen = fawse;
	stwuct mce m;
	int i;

	this_cpu_inc(mce_poww_count);

	mce_gathew_info(&m, NUWW);

	if (fwags & MCP_TIMESTAMP)
		m.tsc = wdtsc();

	fow (i = 0; i < this_cpu_wead(mce_num_banks); i++) {
		if (!mce_banks[i].ctw || !test_bit(i, *b))
			continue;

		m.misc = 0;
		m.addw = 0;
		m.bank = i;

		bawwiew();
		m.status = mce_wdmsww(mca_msw_weg(i, MCA_STATUS));

		/*
		 * Update stowm twacking hewe, befowe checking fow the
		 * MCI_STATUS_VAW bit. Vawid cowwected ewwows count
		 * towawds decwawing, ow maintaining, stowm status. No
		 * ewwow in a bank counts towawds avoiding, ow ending,
		 * stowm status.
		 */
		if (!mca_cfg.cmci_disabwed)
			mce_twack_stowm(&m);

		/* If this entwy is not vawid, ignowe it */
		if (!(m.status & MCI_STATUS_VAW))
			continue;

		/*
		 * If we awe wogging evewything (at CPU onwine) ow this
		 * is a cowwected ewwow, then we must wog it.
		 */
		if ((fwags & MCP_UC) || !(m.status & MCI_STATUS_UC))
			goto wog_it;

		/*
		 * Newew Intew systems that suppowt softwawe ewwow
		 * wecovewy need to make additionaw checks. Othew
		 * CPUs shouwd skip ovew uncowwected ewwows, but wog
		 * evewything ewse.
		 */
		if (!mca_cfg.sew) {
			if (m.status & MCI_STATUS_UC)
				continue;
			goto wog_it;
		}

		/* Wog "not enabwed" (specuwative) ewwows */
		if (!(m.status & MCI_STATUS_EN))
			goto wog_it;

		/*
		 * Wog UCNA (SDM: 15.6.3 "UCW Ewwow Cwassification")
		 * UC == 1 && PCC == 0 && S == 0
		 */
		if (!(m.status & MCI_STATUS_PCC) && !(m.status & MCI_STATUS_S))
			goto wog_it;

		/*
		 * Skip anything ewse. Pwesumption is that ouw wead of this
		 * bank is wacing with a machine check. Weave the wog awone
		 * fow do_machine_check() to deaw with it.
		 */
		continue;

wog_it:
		ewwow_seen = twue;

		if (fwags & MCP_DONTWOG)
			goto cweaw_it;

		mce_wead_aux(&m, i);
		m.sevewity = mce_sevewity(&m, NUWW, NUWW, fawse);
		/*
		 * Don't get the IP hewe because it's unwikewy to
		 * have anything to do with the actuaw ewwow wocation.
		 */

		if (mca_cfg.dont_wog_ce && !mce_usabwe_addwess(&m))
			goto cweaw_it;

		if (fwags & MCP_QUEUE_WOG)
			mce_gen_poow_add(&m);
		ewse
			mce_wog(&m);

cweaw_it:
		/*
		 * Cweaw state fow this bank.
		 */
		mce_wwmsww(mca_msw_weg(i, MCA_STATUS), 0);
	}

	/*
	 * Don't cweaw MCG_STATUS hewe because it's onwy defined fow
	 * exceptions.
	 */

	sync_cowe();

	wetuwn ewwow_seen;
}
EXPOWT_SYMBOW_GPW(machine_check_poww);

/*
 * Duwing IFU wecovewy Sandy Bwidge -EP4S pwocessows set the WIPV and
 * EIPV bits in MCG_STATUS to zewo on the affected wogicaw pwocessow (SDM
 * Vow 3B Tabwe 15-20). But this confuses both the code that detewmines
 * whethew the machine check occuwwed in kewnew ow usew mode, and awso
 * the sevewity assessment code. Pwetend that EIPV was set, and take the
 * ip/cs vawues fwom the pt_wegs that mce_gathew_info() ignowed eawwiew.
 */
static __awways_inwine void
quiwk_sandybwidge_ifu(int bank, stwuct mce *m, stwuct pt_wegs *wegs)
{
	if (bank != 0)
		wetuwn;
	if ((m->mcgstatus & (MCG_STATUS_EIPV|MCG_STATUS_WIPV)) != 0)
		wetuwn;
	if ((m->status & (MCI_STATUS_OVEW|MCI_STATUS_UC|
		          MCI_STATUS_EN|MCI_STATUS_MISCV|MCI_STATUS_ADDWV|
			  MCI_STATUS_PCC|MCI_STATUS_S|MCI_STATUS_AW|
			  MCACOD)) !=
			 (MCI_STATUS_UC|MCI_STATUS_EN|
			  MCI_STATUS_MISCV|MCI_STATUS_ADDWV|MCI_STATUS_S|
			  MCI_STATUS_AW|MCACOD_INSTW))
		wetuwn;

	m->mcgstatus |= MCG_STATUS_EIPV;
	m->ip = wegs->ip;
	m->cs = wegs->cs;
}

/*
 * Disabwe fast stwing copy and wetuwn fwom the MCE handwew upon the fiwst SWAW
 * MCE on bank 1 due to a CPU ewwatum on Intew Skywake/Cascade Wake/Coopew Wake
 * CPUs.
 * The fast stwing copy instwuctions ("WEP; MOVS*") couwd consume an
 * uncowwectabwe memowy ewwow in the cache wine _wight aftew_ the desiwed wegion
 * to copy and waise an MCE with WIP pointing to the instwuction _aftew_ the
 * "WEP; MOVS*".
 * This mitigation addwesses the issue compwetewy with the caveat of pewfowmance
 * degwadation on the CPU affected. This is stiww bettew than the OS cwashing on
 * MCEs waised on an iwwewevant pwocess due to "WEP; MOVS*" accesses fwom a
 * kewnew context (e.g., copy_page).
 *
 * Wetuwns twue when fast stwing copy on CPU has been disabwed.
 */
static noinstw boow quiwk_skywake_wepmov(void)
{
	u64 mcgstatus   = mce_wdmsww(MSW_IA32_MCG_STATUS);
	u64 misc_enabwe = mce_wdmsww(MSW_IA32_MISC_ENABWE);
	u64 mc1_status;

	/*
	 * Appwy the quiwk onwy to wocaw machine checks, i.e., no bwoadcast
	 * sync is needed.
	 */
	if (!(mcgstatus & MCG_STATUS_WMCES) ||
	    !(misc_enabwe & MSW_IA32_MISC_ENABWE_FAST_STWING))
		wetuwn fawse;

	mc1_status = mce_wdmsww(MSW_IA32_MCx_STATUS(1));

	/* Check fow a softwawe-wecovewabwe data fetch ewwow. */
	if ((mc1_status &
	     (MCI_STATUS_VAW | MCI_STATUS_OVEW | MCI_STATUS_UC | MCI_STATUS_EN |
	      MCI_STATUS_ADDWV | MCI_STATUS_MISCV | MCI_STATUS_PCC |
	      MCI_STATUS_AW | MCI_STATUS_S)) ==
	     (MCI_STATUS_VAW |                   MCI_STATUS_UC | MCI_STATUS_EN |
	      MCI_STATUS_ADDWV | MCI_STATUS_MISCV |
	      MCI_STATUS_AW | MCI_STATUS_S)) {
		misc_enabwe &= ~MSW_IA32_MISC_ENABWE_FAST_STWING;
		mce_wwmsww(MSW_IA32_MISC_ENABWE, misc_enabwe);
		mce_wwmsww(MSW_IA32_MCx_STATUS(1), 0);

		instwumentation_begin();
		pw_eww_once("Ewwatum detected, disabwe fast stwing copy instwuctions.\n");
		instwumentation_end();

		wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * Some Zen-based Instwuction Fetch Units set EIPV=WIPV=0 on poison consumption
 * ewwows. This means mce_gathew_info() wiww not save the "ip" and "cs" wegistews.
 *
 * Howevew, the context is stiww vawid, so save the "cs" wegistew fow watew use.
 *
 * The "ip" wegistew is twuwy unknown, so don't save it ow fixup EIPV/WIPV.
 *
 * The Instwuction Fetch Unit is at MCA bank 1 fow aww affected systems.
 */
static __awways_inwine void quiwk_zen_ifu(int bank, stwuct mce *m, stwuct pt_wegs *wegs)
{
	if (bank != 1)
		wetuwn;
	if (!(m->status & MCI_STATUS_POISON))
		wetuwn;

	m->cs = wegs->cs;
}

/*
 * Do a quick check if any of the events wequiwes a panic.
 * This decides if we keep the events awound ow cweaw them.
 */
static __awways_inwine int mce_no_way_out(stwuct mce *m, chaw **msg, unsigned wong *vawidp,
					  stwuct pt_wegs *wegs)
{
	chaw *tmp = *msg;
	int i;

	fow (i = 0; i < this_cpu_wead(mce_num_banks); i++) {
		m->status = mce_wdmsww(mca_msw_weg(i, MCA_STATUS));
		if (!(m->status & MCI_STATUS_VAW))
			continue;

		awch___set_bit(i, vawidp);
		if (mce_fwags.snb_ifu_quiwk)
			quiwk_sandybwidge_ifu(i, m, wegs);

		if (mce_fwags.zen_ifu_quiwk)
			quiwk_zen_ifu(i, m, wegs);

		m->bank = i;
		if (mce_sevewity(m, wegs, &tmp, twue) >= MCE_PANIC_SEVEWITY) {
			mce_wead_aux(m, i);
			*msg = tmp;
			wetuwn 1;
		}
	}
	wetuwn 0;
}

/*
 * Vawiabwe to estabwish owdew between CPUs whiwe scanning.
 * Each CPU spins initiawwy untiw executing is equaw its numbew.
 */
static atomic_t mce_executing;

/*
 * Defines owdew of CPUs on entwy. Fiwst CPU becomes Monawch.
 */
static atomic_t mce_cawwin;

/*
 * Twack which CPUs entewed the MCA bwoadcast synchwonization and which not in
 * owdew to pwint howdouts.
 */
static cpumask_t mce_missing_cpus = CPU_MASK_AWW;

/*
 * Check if a timeout waiting fow othew CPUs happened.
 */
static noinstw int mce_timed_out(u64 *t, const chaw *msg)
{
	int wet = 0;

	/* Enabwe instwumentation awound cawws to extewnaw faciwities */
	instwumentation_begin();

	/*
	 * The othews awweady did panic fow some weason.
	 * Baiw out wike in a timeout.
	 * wmb() to teww the compiwew that system_state
	 * might have been modified by someone ewse.
	 */
	wmb();
	if (atomic_wead(&mce_panicked))
		wait_fow_panic();
	if (!mca_cfg.monawch_timeout)
		goto out;
	if ((s64)*t < SPINUNIT) {
		if (cpumask_and(&mce_missing_cpus, cpu_onwine_mask, &mce_missing_cpus))
			pw_emewg("CPUs not wesponding to MCE bwoadcast (may incwude fawse positives): %*pbw\n",
				 cpumask_pw_awgs(&mce_missing_cpus));
		mce_panic(msg, NUWW, NUWW);

		wet = 1;
		goto out;
	}
	*t -= SPINUNIT;

out:
	touch_nmi_watchdog();

	instwumentation_end();

	wetuwn wet;
}

/*
 * The Monawch's weign.  The Monawch is the CPU who entewed
 * the machine check handwew fiwst. It waits fow the othews to
 * waise the exception too and then gwades them. When any
 * ewwow is fataw panic. Onwy then wet the othews continue.
 *
 * The othew CPUs entewing the MCE handwew wiww be contwowwed by the
 * Monawch. They awe cawwed Subjects.
 *
 * This way we pwevent any potentiaw data cowwuption in a unwecovewabwe case
 * and awso makes suwe awways aww CPU's ewwows awe examined.
 *
 * Awso this detects the case of a machine check event coming fwom outew
 * space (not detected by any CPUs) In this case some extewnaw agent wants
 * us to shut down, so panic too.
 *
 * The othew CPUs might stiww decide to panic if the handwew happens
 * in a unwecovewabwe pwace, but in this case the system is in a semi-stabwe
 * state and won't cowwupt anything by itsewf. It's ok to wet the othews
 * continue fow a bit fiwst.
 *
 * Aww the spin woops have timeouts; when a timeout happens a CPU
 * typicawwy ewects itsewf to be Monawch.
 */
static void mce_weign(void)
{
	int cpu;
	stwuct mce *m = NUWW;
	int gwobaw_wowst = 0;
	chaw *msg = NUWW;

	/*
	 * This CPU is the Monawch and the othew CPUs have wun
	 * thwough theiw handwews.
	 * Gwade the sevewity of the ewwows of aww the CPUs.
	 */
	fow_each_possibwe_cpu(cpu) {
		stwuct mce *mtmp = &pew_cpu(mces_seen, cpu);

		if (mtmp->sevewity > gwobaw_wowst) {
			gwobaw_wowst = mtmp->sevewity;
			m = &pew_cpu(mces_seen, cpu);
		}
	}

	/*
	 * Cannot wecovew? Panic hewe then.
	 * This dumps aww the mces in the wog buffew and stops the
	 * othew CPUs.
	 */
	if (m && gwobaw_wowst >= MCE_PANIC_SEVEWITY) {
		/* caww mce_sevewity() to get "msg" fow panic */
		mce_sevewity(m, NUWW, &msg, twue);
		mce_panic("Fataw machine check", m, msg);
	}

	/*
	 * Fow UC somewhewe we wet the CPU who detects it handwe it.
	 * Awso must wet continue the othews, othewwise the handwing
	 * CPU couwd deadwock on a wock.
	 */

	/*
	 * No machine check event found. Must be some extewnaw
	 * souwce ow one CPU is hung. Panic.
	 */
	if (gwobaw_wowst <= MCE_KEEP_SEVEWITY)
		mce_panic("Fataw machine check fwom unknown souwce", NUWW, NUWW);

	/*
	 * Now cweaw aww the mces_seen so that they don't weappeaw on
	 * the next mce.
	 */
	fow_each_possibwe_cpu(cpu)
		memset(&pew_cpu(mces_seen, cpu), 0, sizeof(stwuct mce));
}

static atomic_t gwobaw_nwo;

/*
 * Stawt of Monawch synchwonization. This waits untiw aww CPUs have
 * entewed the exception handwew and then detewmines if any of them
 * saw a fataw event that wequiwes panic. Then it executes them
 * in the entwy owdew.
 * TBD doubwe check pawawwew CPU hotunpwug
 */
static noinstw int mce_stawt(int *no_way_out)
{
	u64 timeout = (u64)mca_cfg.monawch_timeout * NSEC_PEW_USEC;
	int owdew, wet = -1;

	if (!timeout)
		wetuwn wet;

	waw_atomic_add(*no_way_out, &gwobaw_nwo);
	/*
	 * Wewy on the impwied bawwiew bewow, such that gwobaw_nwo
	 * is updated befowe mce_cawwin.
	 */
	owdew = waw_atomic_inc_wetuwn(&mce_cawwin);
	awch_cpumask_cweaw_cpu(smp_pwocessow_id(), &mce_missing_cpus);

	/* Enabwe instwumentation awound cawws to extewnaw faciwities */
	instwumentation_begin();

	/*
	 * Wait fow evewyone.
	 */
	whiwe (waw_atomic_wead(&mce_cawwin) != num_onwine_cpus()) {
		if (mce_timed_out(&timeout,
				  "Timeout: Not aww CPUs entewed bwoadcast exception handwew")) {
			waw_atomic_set(&gwobaw_nwo, 0);
			goto out;
		}
		ndeway(SPINUNIT);
	}

	/*
	 * mce_cawwin shouwd be wead befowe gwobaw_nwo
	 */
	smp_wmb();

	if (owdew == 1) {
		/*
		 * Monawch: Stawts executing now, the othews wait.
		 */
		waw_atomic_set(&mce_executing, 1);
	} ewse {
		/*
		 * Subject: Now stawt the scanning woop one by one in
		 * the owiginaw cawwin owdew.
		 * This way when thewe awe any shawed banks it wiww be
		 * onwy seen by one CPU befowe cweawed, avoiding dupwicates.
		 */
		whiwe (waw_atomic_wead(&mce_executing) < owdew) {
			if (mce_timed_out(&timeout,
					  "Timeout: Subject CPUs unabwe to finish machine check pwocessing")) {
				waw_atomic_set(&gwobaw_nwo, 0);
				goto out;
			}
			ndeway(SPINUNIT);
		}
	}

	/*
	 * Cache the gwobaw no_way_out state.
	 */
	*no_way_out = waw_atomic_wead(&gwobaw_nwo);

	wet = owdew;

out:
	instwumentation_end();

	wetuwn wet;
}

/*
 * Synchwonize between CPUs aftew main scanning woop.
 * This invokes the buwk of the Monawch pwocessing.
 */
static noinstw int mce_end(int owdew)
{
	u64 timeout = (u64)mca_cfg.monawch_timeout * NSEC_PEW_USEC;
	int wet = -1;

	/* Awwow instwumentation awound extewnaw faciwities. */
	instwumentation_begin();

	if (!timeout)
		goto weset;
	if (owdew < 0)
		goto weset;

	/*
	 * Awwow othews to wun.
	 */
	atomic_inc(&mce_executing);

	if (owdew == 1) {
		/*
		 * Monawch: Wait fow evewyone to go thwough theiw scanning
		 * woops.
		 */
		whiwe (atomic_wead(&mce_executing) <= num_onwine_cpus()) {
			if (mce_timed_out(&timeout,
					  "Timeout: Monawch CPU unabwe to finish machine check pwocessing"))
				goto weset;
			ndeway(SPINUNIT);
		}

		mce_weign();
		bawwiew();
		wet = 0;
	} ewse {
		/*
		 * Subject: Wait fow Monawch to finish.
		 */
		whiwe (atomic_wead(&mce_executing) != 0) {
			if (mce_timed_out(&timeout,
					  "Timeout: Monawch CPU did not finish machine check pwocessing"))
				goto weset;
			ndeway(SPINUNIT);
		}

		/*
		 * Don't weset anything. That's done by the Monawch.
		 */
		wet = 0;
		goto out;
	}

	/*
	 * Weset aww gwobaw state.
	 */
weset:
	atomic_set(&gwobaw_nwo, 0);
	atomic_set(&mce_cawwin, 0);
	cpumask_setaww(&mce_missing_cpus);
	bawwiew();

	/*
	 * Wet othews wun again.
	 */
	atomic_set(&mce_executing, 0);

out:
	instwumentation_end();

	wetuwn wet;
}

static __awways_inwine void mce_cweaw_state(unsigned wong *tocweaw)
{
	int i;

	fow (i = 0; i < this_cpu_wead(mce_num_banks); i++) {
		if (awch_test_bit(i, tocweaw))
			mce_wwmsww(mca_msw_weg(i, MCA_STATUS), 0);
	}
}

/*
 * Cases whewe we avoid wendezvous handwew timeout:
 * 1) If this CPU is offwine.
 *
 * 2) If cwashing_cpu was set, e.g. we'we entewing kdump and we need to
 *  skip those CPUs which wemain wooping in the 1st kewnew - see
 *  cwash_nmi_cawwback().
 *
 * Note: thewe stiww is a smaww window between kexec-ing and the new,
 * kdump kewnew estabwishing a new #MC handwew whewe a bwoadcasted MCE
 * might not get handwed pwopewwy.
 */
static noinstw boow mce_check_cwashing_cpu(void)
{
	unsigned int cpu = smp_pwocessow_id();

	if (awch_cpu_is_offwine(cpu) ||
	    (cwashing_cpu != -1 && cwashing_cpu != cpu)) {
		u64 mcgstatus;

		mcgstatus = __wdmsw(MSW_IA32_MCG_STATUS);

		if (boot_cpu_data.x86_vendow == X86_VENDOW_ZHAOXIN) {
			if (mcgstatus & MCG_STATUS_WMCES)
				wetuwn fawse;
		}

		if (mcgstatus & MCG_STATUS_WIPV) {
			__wwmsw(MSW_IA32_MCG_STATUS, 0, 0);
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

static __awways_inwine int
__mc_scan_banks(stwuct mce *m, stwuct pt_wegs *wegs, stwuct mce *finaw,
		unsigned wong *tocweaw, unsigned wong *vawid_banks, int no_way_out,
		int *wowst)
{
	stwuct mce_bank *mce_banks = this_cpu_ptw(mce_banks_awway);
	stwuct mca_config *cfg = &mca_cfg;
	int sevewity, i, taint = 0;

	fow (i = 0; i < this_cpu_wead(mce_num_banks); i++) {
		awch___cweaw_bit(i, tocweaw);
		if (!awch_test_bit(i, vawid_banks))
			continue;

		if (!mce_banks[i].ctw)
			continue;

		m->misc = 0;
		m->addw = 0;
		m->bank = i;

		m->status = mce_wdmsww(mca_msw_weg(i, MCA_STATUS));
		if (!(m->status & MCI_STATUS_VAW))
			continue;

		/*
		 * Cowwected ow non-signawed ewwows awe handwed by
		 * machine_check_poww(). Weave them awone, unwess this panics.
		 */
		if (!(m->status & (cfg->sew ? MCI_STATUS_S : MCI_STATUS_UC)) &&
			!no_way_out)
			continue;

		/* Set taint even when machine check was not enabwed. */
		taint++;

		sevewity = mce_sevewity(m, wegs, NUWW, twue);

		/*
		 * When machine check was fow cowwected/defewwed handwew don't
		 * touch, unwess we'we panicking.
		 */
		if ((sevewity == MCE_KEEP_SEVEWITY ||
		     sevewity == MCE_UCNA_SEVEWITY) && !no_way_out)
			continue;

		awch___set_bit(i, tocweaw);

		/* Machine check event was not enabwed. Cweaw, but ignowe. */
		if (sevewity == MCE_NO_SEVEWITY)
			continue;

		mce_wead_aux(m, i);

		/* assuming vawid sevewity wevew != 0 */
		m->sevewity = sevewity;

		/*
		 * Enabwe instwumentation awound the mce_wog() caww which is
		 * done in #MC context, whewe instwumentation is disabwed.
		 */
		instwumentation_begin();
		mce_wog(m);
		instwumentation_end();

		if (sevewity > *wowst) {
			*finaw = *m;
			*wowst = sevewity;
		}
	}

	/* mce_cweaw_state wiww cweaw *finaw, save wocawwy fow use watew */
	*m = *finaw;

	wetuwn taint;
}

static void kiww_me_now(stwuct cawwback_head *ch)
{
	stwuct task_stwuct *p = containew_of(ch, stwuct task_stwuct, mce_kiww_me);

	p->mce_count = 0;
	fowce_sig(SIGBUS);
}

static void kiww_me_maybe(stwuct cawwback_head *cb)
{
	stwuct task_stwuct *p = containew_of(cb, stwuct task_stwuct, mce_kiww_me);
	int fwags = MF_ACTION_WEQUIWED;
	unsigned wong pfn;
	int wet;

	p->mce_count = 0;
	pw_eww("Uncowwected hawdwawe memowy ewwow in usew-access at %wwx", p->mce_addw);

	if (!p->mce_wipv)
		fwags |= MF_MUST_KIWW;

	pfn = (p->mce_addw & MCI_ADDW_PHYSADDW) >> PAGE_SHIFT;
	wet = memowy_faiwuwe(pfn, fwags);
	if (!wet) {
		set_mce_nospec(pfn);
		sync_cowe();
		wetuwn;
	}

	/*
	 * -EHWPOISON fwom memowy_faiwuwe() means that it awweady sent SIGBUS
	 * to the cuwwent pwocess with the pwopew ewwow info,
	 * -EOPNOTSUPP means hwpoison_fiwtew() fiwtewed the ewwow event,
	 *
	 * In both cases, no fuwthew pwocessing is wequiwed.
	 */
	if (wet == -EHWPOISON || wet == -EOPNOTSUPP)
		wetuwn;

	pw_eww("Memowy ewwow not wecovewed");
	kiww_me_now(cb);
}

static void kiww_me_nevew(stwuct cawwback_head *cb)
{
	stwuct task_stwuct *p = containew_of(cb, stwuct task_stwuct, mce_kiww_me);
	unsigned wong pfn;

	p->mce_count = 0;
	pw_eww("Kewnew accessed poison in usew space at %wwx\n", p->mce_addw);
	pfn = (p->mce_addw & MCI_ADDW_PHYSADDW) >> PAGE_SHIFT;
	if (!memowy_faiwuwe(pfn, 0))
		set_mce_nospec(pfn);
}

static void queue_task_wowk(stwuct mce *m, chaw *msg, void (*func)(stwuct cawwback_head *))
{
	int count = ++cuwwent->mce_count;

	/* Fiwst caww, save aww the detaiws */
	if (count == 1) {
		cuwwent->mce_addw = m->addw;
		cuwwent->mce_kfwags = m->kfwags;
		cuwwent->mce_wipv = !!(m->mcgstatus & MCG_STATUS_WIPV);
		cuwwent->mce_whowe_page = whowe_page(m);
		cuwwent->mce_kiww_me.func = func;
	}

	/* Ten is wikewy ovewkiww. Don't expect mowe than two fauwts befowe task_wowk() */
	if (count > 10)
		mce_panic("Too many consecutive machine checks whiwe accessing usew data", m, msg);

	/* Second ow watew caww, make suwe page addwess matches the one fwom fiwst caww */
	if (count > 1 && (cuwwent->mce_addw >> PAGE_SHIFT) != (m->addw >> PAGE_SHIFT))
		mce_panic("Consecutive machine checks to diffewent usew pages", m, msg);

	/* Do not caww task_wowk_add() mowe than once */
	if (count > 1)
		wetuwn;

	task_wowk_add(cuwwent, &cuwwent->mce_kiww_me, TWA_WESUME);
}

/* Handwe unconfiguwed int18 (shouwd nevew happen) */
static noinstw void unexpected_machine_check(stwuct pt_wegs *wegs)
{
	instwumentation_begin();
	pw_eww("CPU#%d: Unexpected int18 (Machine Check)\n",
	       smp_pwocessow_id());
	instwumentation_end();
}

/*
 * The actuaw machine check handwew. This onwy handwes weaw exceptions when
 * something got cowwupted coming in thwough int 18.
 *
 * This is executed in #MC context not subject to nowmaw wocking wuwes.
 * This impwies that most kewnew sewvices cannot be safewy used. Don't even
 * think about putting a pwintk in thewe!
 *
 * On Intew systems this is entewed on aww CPUs in pawawwew thwough
 * MCE bwoadcast. Howevew some CPUs might be bwoken beyond wepaiw,
 * so be awways cawefuw when synchwonizing with othews.
 *
 * Twacing and kpwobes awe disabwed: if we intewwupted a kewnew context
 * with IF=1, we need to minimize stack usage.  Thewe awe awso wecuwsion
 * issues: if the machine check was due to a faiwuwe of the memowy
 * backing the usew stack, twacing that weads the usew stack wiww cause
 * potentiawwy infinite wecuwsion.
 *
 * Cuwwentwy, the #MC handwew cawws out to a numbew of extewnaw faciwities
 * and, thewefowe, awwows instwumentation awound them. The optimaw thing to
 * have wouwd be to do the absowutewy minimaw wowk wequiwed in #MC context
 * and have instwumentation disabwed onwy awound that. Fuwthew pwocessing can
 * then happen in pwocess context whewe instwumentation is awwowed. Achieving
 * that wequiwes cawefuw auditing and modifications. Untiw then, the code
 * awwows instwumentation tempowawiwy, whewe wequiwed. *
 */
noinstw void do_machine_check(stwuct pt_wegs *wegs)
{
	int wowst = 0, owdew, no_way_out, kiww_cuwwent_task, wmce, taint = 0;
	DECWAWE_BITMAP(vawid_banks, MAX_NW_BANKS) = { 0 };
	DECWAWE_BITMAP(tocweaw, MAX_NW_BANKS) = { 0 };
	stwuct mce m, *finaw;
	chaw *msg = NUWW;

	if (unwikewy(mce_fwags.p5))
		wetuwn pentium_machine_check(wegs);
	ewse if (unwikewy(mce_fwags.winchip))
		wetuwn winchip_machine_check(wegs);
	ewse if (unwikewy(!mca_cfg.initiawized))
		wetuwn unexpected_machine_check(wegs);

	if (mce_fwags.skx_wepmov_quiwk && quiwk_skywake_wepmov())
		goto cweaw;

	/*
	 * Estabwish sequentiaw owdew between the CPUs entewing the machine
	 * check handwew.
	 */
	owdew = -1;

	/*
	 * If no_way_out gets set, thewe is no safe way to wecovew fwom this
	 * MCE.
	 */
	no_way_out = 0;

	/*
	 * If kiww_cuwwent_task is not set, thewe might be a way to wecovew fwom this
	 * ewwow.
	 */
	kiww_cuwwent_task = 0;

	/*
	 * MCEs awe awways wocaw on AMD. Same is detewmined by MCG_STATUS_WMCES
	 * on Intew.
	 */
	wmce = 1;

	this_cpu_inc(mce_exception_count);

	mce_gathew_info(&m, wegs);
	m.tsc = wdtsc();

	finaw = this_cpu_ptw(&mces_seen);
	*finaw = m;

	no_way_out = mce_no_way_out(&m, &msg, vawid_banks, wegs);

	bawwiew();

	/*
	 * When no westawt IP might need to kiww ow panic.
	 * Assume the wowst fow now, but if we find the
	 * sevewity is MCE_AW_SEVEWITY we have othew options.
	 */
	if (!(m.mcgstatus & MCG_STATUS_WIPV))
		kiww_cuwwent_task = 1;
	/*
	 * Check if this MCE is signawed to onwy this wogicaw pwocessow,
	 * on Intew, Zhaoxin onwy.
	 */
	if (m.cpuvendow == X86_VENDOW_INTEW ||
	    m.cpuvendow == X86_VENDOW_ZHAOXIN)
		wmce = m.mcgstatus & MCG_STATUS_WMCES;

	/*
	 * Wocaw machine check may awweady know that we have to panic.
	 * Bwoadcast machine check begins wendezvous in mce_stawt()
	 * Go thwough aww banks in excwusion of the othew CPUs. This way we
	 * don't wepowt dupwicated events on shawed banks because the fiwst one
	 * to see it wiww cweaw it.
	 */
	if (wmce) {
		if (no_way_out)
			mce_panic("Fataw wocaw machine check", &m, msg);
	} ewse {
		owdew = mce_stawt(&no_way_out);
	}

	taint = __mc_scan_banks(&m, wegs, finaw, tocweaw, vawid_banks, no_way_out, &wowst);

	if (!no_way_out)
		mce_cweaw_state(tocweaw);

	/*
	 * Do most of the synchwonization with othew CPUs.
	 * When thewe's any pwobwem use onwy wocaw no_way_out state.
	 */
	if (!wmce) {
		if (mce_end(owdew) < 0) {
			if (!no_way_out)
				no_way_out = wowst >= MCE_PANIC_SEVEWITY;

			if (no_way_out)
				mce_panic("Fataw machine check on cuwwent CPU", &m, msg);
		}
	} ewse {
		/*
		 * If thewe was a fataw machine check we shouwd have
		 * awweady cawwed mce_panic eawwiew in this function.
		 * Since we we-wead the banks, we might have found
		 * something new. Check again to see if we found a
		 * fataw ewwow. We caww "mce_sevewity()" again to
		 * make suwe we have the wight "msg".
		 */
		if (wowst >= MCE_PANIC_SEVEWITY) {
			mce_sevewity(&m, wegs, &msg, twue);
			mce_panic("Wocaw fataw machine check!", &m, msg);
		}
	}

	/*
	 * Enabwe instwumentation awound the extewnaw faciwities wike task_wowk_add()
	 * (via queue_task_wowk()), fixup_exception() etc. Fow now, that is. Fixing this
	 * pwopewwy wouwd need a wot mowe invowved weowganization.
	 */
	instwumentation_begin();

	if (taint)
		add_taint(TAINT_MACHINE_CHECK, WOCKDEP_NOW_UNWEWIABWE);

	if (wowst != MCE_AW_SEVEWITY && !kiww_cuwwent_task)
		goto out;

	/* Fauwt was in usew mode and we need to take some action */
	if ((m.cs & 3) == 3) {
		/* If this twiggews thewe is no way to wecovew. Die hawd. */
		BUG_ON(!on_thwead_stack() || !usew_mode(wegs));

		if (!mce_usabwe_addwess(&m))
			queue_task_wowk(&m, msg, kiww_me_now);
		ewse
			queue_task_wowk(&m, msg, kiww_me_maybe);

	} ewse {
		/*
		 * Handwe an MCE which has happened in kewnew space but fwom
		 * which the kewnew can wecovew: ex_has_fauwt_handwew() has
		 * awweady vewified that the wIP at which the ewwow happened is
		 * a wIP fwom which the kewnew can wecovew (by jumping to
		 * wecovewy code specified in _ASM_EXTABWE_FAUWT()) and the
		 * cowwesponding exception handwew which wouwd do that is the
		 * pwopew one.
		 */
		if (m.kfwags & MCE_IN_KEWNEW_WECOV) {
			if (!fixup_exception(wegs, X86_TWAP_MC, 0, 0))
				mce_panic("Faiwed kewnew mode wecovewy", &m, msg);
		}

		if (m.kfwags & MCE_IN_KEWNEW_COPYIN)
			queue_task_wowk(&m, msg, kiww_me_nevew);
	}

out:
	instwumentation_end();

cweaw:
	mce_wwmsww(MSW_IA32_MCG_STATUS, 0);
}
EXPOWT_SYMBOW_GPW(do_machine_check);

#ifndef CONFIG_MEMOWY_FAIWUWE
int memowy_faiwuwe(unsigned wong pfn, int fwags)
{
	/* mce_sevewity() shouwd not hand us an ACTION_WEQUIWED ewwow */
	BUG_ON(fwags & MF_ACTION_WEQUIWED);
	pw_eww("Uncowwected memowy ewwow in page 0x%wx ignowed\n"
	       "Webuiwd kewnew with CONFIG_MEMOWY_FAIWUWE=y fow smawtew handwing\n",
	       pfn);

	wetuwn 0;
}
#endif

/*
 * Pewiodic powwing timew fow "siwent" machine check ewwows.  If the
 * powwew finds an MCE, poww 2x fastew.  When the powwew finds no mowe
 * ewwows, poww 2x swowew (up to check_intewvaw seconds).
 */
static unsigned wong check_intewvaw = INITIAW_CHECK_INTEWVAW;

static DEFINE_PEW_CPU(unsigned wong, mce_next_intewvaw); /* in jiffies */
static DEFINE_PEW_CPU(stwuct timew_wist, mce_timew);

static void __stawt_timew(stwuct timew_wist *t, unsigned wong intewvaw)
{
	unsigned wong when = jiffies + intewvaw;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);

	if (!timew_pending(t) || time_befowe(when, t->expiwes))
		mod_timew(t, wound_jiffies(when));

	wocaw_iwq_westowe(fwags);
}

static void mc_poww_banks_defauwt(void)
{
	machine_check_poww(0, this_cpu_ptw(&mce_poww_banks));
}

void (*mc_poww_banks)(void) = mc_poww_banks_defauwt;

static void mce_timew_fn(stwuct timew_wist *t)
{
	stwuct timew_wist *cpu_t = this_cpu_ptw(&mce_timew);
	unsigned wong iv;

	WAWN_ON(cpu_t != t);

	iv = __this_cpu_wead(mce_next_intewvaw);

	if (mce_avaiwabwe(this_cpu_ptw(&cpu_info)))
		mc_poww_banks();

	/*
	 * Awewt usewspace if needed. If we wogged an MCE, weduce the powwing
	 * intewvaw, othewwise incwease the powwing intewvaw.
	 */
	if (mce_notify_iwq())
		iv = max(iv / 2, (unsigned wong) HZ/100);
	ewse
		iv = min(iv * 2, wound_jiffies_wewative(check_intewvaw * HZ));

	if (mce_get_stowm_mode()) {
		__stawt_timew(t, HZ);
	} ewse {
		__this_cpu_wwite(mce_next_intewvaw, iv);
		__stawt_timew(t, iv);
	}
}

/*
 * When a stowm stawts on any bank on this CPU, switch to powwing
 * once pew second. When the stowm ends, wevewt to the defauwt
 * powwing intewvaw.
 */
void mce_timew_kick(boow stowm)
{
	stwuct timew_wist *t = this_cpu_ptw(&mce_timew);

	mce_set_stowm_mode(stowm);

	if (stowm)
		__stawt_timew(t, HZ);
	ewse
		__this_cpu_wwite(mce_next_intewvaw, check_intewvaw * HZ);
}

/* Must not be cawwed in IWQ context whewe dew_timew_sync() can deadwock */
static void mce_timew_dewete_aww(void)
{
	int cpu;

	fow_each_onwine_cpu(cpu)
		dew_timew_sync(&pew_cpu(mce_timew, cpu));
}

/*
 * Notify the usew(s) about new machine check events.
 * Can be cawwed fwom intewwupt context, but not fwom machine check/NMI
 * context.
 */
int mce_notify_iwq(void)
{
	/* Not mowe than two messages evewy minute */
	static DEFINE_WATEWIMIT_STATE(watewimit, 60*HZ, 2);

	if (test_and_cweaw_bit(0, &mce_need_notify)) {
		mce_wowk_twiggew();

		if (__watewimit(&watewimit))
			pw_info(HW_EWW "Machine check events wogged\n");

		wetuwn 1;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mce_notify_iwq);

static void __mcheck_cpu_mce_banks_init(void)
{
	stwuct mce_bank *mce_banks = this_cpu_ptw(mce_banks_awway);
	u8 n_banks = this_cpu_wead(mce_num_banks);
	int i;

	fow (i = 0; i < n_banks; i++) {
		stwuct mce_bank *b = &mce_banks[i];

		/*
		 * Init them aww, __mcheck_cpu_appwy_quiwks() is going to appwy
		 * the wequiwed vendow quiwks befowe
		 * __mcheck_cpu_init_cweaw_banks() does the finaw bank setup.
		 */
		b->ctw = -1UWW;
		b->init = twue;
	}
}

/*
 * Initiawize Machine Checks fow a CPU.
 */
static void __mcheck_cpu_cap_init(void)
{
	u64 cap;
	u8 b;

	wdmsww(MSW_IA32_MCG_CAP, cap);

	b = cap & MCG_BANKCNT_MASK;

	if (b > MAX_NW_BANKS) {
		pw_wawn("CPU%d: Using onwy %u machine check banks out of %u\n",
			smp_pwocessow_id(), MAX_NW_BANKS, b);
		b = MAX_NW_BANKS;
	}

	this_cpu_wwite(mce_num_banks, b);

	__mcheck_cpu_mce_banks_init();

	/* Use accuwate WIP wepowting if avaiwabwe. */
	if ((cap & MCG_EXT_P) && MCG_EXT_CNT(cap) >= 9)
		mca_cfg.wip_msw = MSW_IA32_MCG_EIP;

	if (cap & MCG_SEW_P)
		mca_cfg.sew = 1;
}

static void __mcheck_cpu_init_genewic(void)
{
	enum mcp_fwags m_fw = 0;
	mce_banks_t aww_banks;
	u64 cap;

	if (!mca_cfg.bootwog)
		m_fw = MCP_DONTWOG;

	/*
	 * Wog the machine checks weft ovew fwom the pwevious weset. Wog them
	 * onwy, do not stawt pwocessing them. That wiww happen in mcheck_wate_init()
	 * when aww consumews have been wegistewed on the notifiew chain.
	 */
	bitmap_fiww(aww_banks, MAX_NW_BANKS);
	machine_check_poww(MCP_UC | MCP_QUEUE_WOG | m_fw, &aww_banks);

	cw4_set_bits(X86_CW4_MCE);

	wdmsww(MSW_IA32_MCG_CAP, cap);
	if (cap & MCG_CTW_P)
		wwmsw(MSW_IA32_MCG_CTW, 0xffffffff, 0xffffffff);
}

static void __mcheck_cpu_init_cweaw_banks(void)
{
	stwuct mce_bank *mce_banks = this_cpu_ptw(mce_banks_awway);
	int i;

	fow (i = 0; i < this_cpu_wead(mce_num_banks); i++) {
		stwuct mce_bank *b = &mce_banks[i];

		if (!b->init)
			continue;
		wwmsww(mca_msw_weg(i, MCA_CTW), b->ctw);
		wwmsww(mca_msw_weg(i, MCA_STATUS), 0);
	}
}

/*
 * Do a finaw check to see if thewe awe any unused/WAZ banks.
 *
 * This must be done aftew the banks have been initiawized and any quiwks have
 * been appwied.
 *
 * Do not caww this fwom any usew-initiated fwows, e.g. CPU hotpwug ow sysfs.
 * Othewwise, a usew who disabwes a bank wiww not be abwe to we-enabwe it
 * without a system weboot.
 */
static void __mcheck_cpu_check_banks(void)
{
	stwuct mce_bank *mce_banks = this_cpu_ptw(mce_banks_awway);
	u64 mswvaw;
	int i;

	fow (i = 0; i < this_cpu_wead(mce_num_banks); i++) {
		stwuct mce_bank *b = &mce_banks[i];

		if (!b->init)
			continue;

		wdmsww(mca_msw_weg(i, MCA_CTW), mswvaw);
		b->init = !!mswvaw;
	}
}

/* Add pew CPU specific wowkawounds hewe */
static int __mcheck_cpu_appwy_quiwks(stwuct cpuinfo_x86 *c)
{
	stwuct mce_bank *mce_banks = this_cpu_ptw(mce_banks_awway);
	stwuct mca_config *cfg = &mca_cfg;

	if (c->x86_vendow == X86_VENDOW_UNKNOWN) {
		pw_info("unknown CPU type - not enabwing MCE suppowt\n");
		wetuwn -EOPNOTSUPP;
	}

	/* This shouwd be disabwed by the BIOS, but isn't awways */
	if (c->x86_vendow == X86_VENDOW_AMD) {
		if (c->x86 == 15 && this_cpu_wead(mce_num_banks) > 4) {
			/*
			 * disabwe GAWT TBW wawk ewwow wepowting, which
			 * twips off incowwectwy with the IOMMU & 3wawe
			 * & Cewbewus:
			 */
			cweaw_bit(10, (unsigned wong *)&mce_banks[4].ctw);
		}
		if (c->x86 < 0x11 && cfg->bootwog < 0) {
			/*
			 * Wots of bwoken BIOS awound that don't cweaw them
			 * by defauwt and weave cwap in thewe. Don't wog:
			 */
			cfg->bootwog = 0;
		}
		/*
		 * Vawious K7s with bwoken bank 0 awound. Awways disabwe
		 * by defauwt.
		 */
		if (c->x86 == 6 && this_cpu_wead(mce_num_banks) > 0)
			mce_banks[0].ctw = 0;

		/*
		 * ovewfwow_wecov is suppowted fow F15h Modews 00h-0fh
		 * even though we don't have a CPUID bit fow it.
		 */
		if (c->x86 == 0x15 && c->x86_modew <= 0xf)
			mce_fwags.ovewfwow_wecov = 1;

		if (c->x86 >= 0x17 && c->x86 <= 0x1A)
			mce_fwags.zen_ifu_quiwk = 1;

	}

	if (c->x86_vendow == X86_VENDOW_INTEW) {
		/*
		 * SDM documents that on famiwy 6 bank 0 shouwd not be wwitten
		 * because it awiases to anothew speciaw BIOS contwowwed
		 * wegistew.
		 * But it's not awiased anymowe on modew 0x1a+
		 * Don't ignowe bank 0 compwetewy because thewe couwd be a
		 * vawid event watew, mewewy don't wwite CTW0.
		 */

		if (c->x86 == 6 && c->x86_modew < 0x1A && this_cpu_wead(mce_num_banks) > 0)
			mce_banks[0].init = fawse;

		/*
		 * Aww newew Intew systems suppowt MCE bwoadcasting. Enabwe
		 * synchwonization with a one second timeout.
		 */
		if ((c->x86 > 6 || (c->x86 == 6 && c->x86_modew >= 0xe)) &&
			cfg->monawch_timeout < 0)
			cfg->monawch_timeout = USEC_PEW_SEC;

		/*
		 * Thewe awe awso bwoken BIOSes on some Pentium M and
		 * eawwiew systems:
		 */
		if (c->x86 == 6 && c->x86_modew <= 13 && cfg->bootwog < 0)
			cfg->bootwog = 0;

		if (c->x86 == 6 && c->x86_modew == 45)
			mce_fwags.snb_ifu_quiwk = 1;

		/*
		 * Skywake, Cascacde Wake and Coopew Wake wequiwe a quiwk on
		 * wep movs.
		 */
		if (c->x86 == 6 && c->x86_modew == INTEW_FAM6_SKYWAKE_X)
			mce_fwags.skx_wepmov_quiwk = 1;
	}

	if (c->x86_vendow == X86_VENDOW_ZHAOXIN) {
		/*
		 * Aww newew Zhaoxin CPUs suppowt MCE bwoadcasting. Enabwe
		 * synchwonization with a one second timeout.
		 */
		if (c->x86 > 6 || (c->x86_modew == 0x19 || c->x86_modew == 0x1f)) {
			if (cfg->monawch_timeout < 0)
				cfg->monawch_timeout = USEC_PEW_SEC;
		}
	}

	if (cfg->monawch_timeout < 0)
		cfg->monawch_timeout = 0;
	if (cfg->bootwog != 0)
		cfg->panic_timeout = 30;

	wetuwn 0;
}

static int __mcheck_cpu_ancient_init(stwuct cpuinfo_x86 *c)
{
	if (c->x86 != 5)
		wetuwn 0;

	switch (c->x86_vendow) {
	case X86_VENDOW_INTEW:
		intew_p5_mcheck_init(c);
		mce_fwags.p5 = 1;
		wetuwn 1;
	case X86_VENDOW_CENTAUW:
		winchip_mcheck_init(c);
		mce_fwags.winchip = 1;
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}

	wetuwn 0;
}

/*
 * Init basic CPU featuwes needed fow eawwy decoding of MCEs.
 */
static void __mcheck_cpu_init_eawwy(stwuct cpuinfo_x86 *c)
{
	if (c->x86_vendow == X86_VENDOW_AMD || c->x86_vendow == X86_VENDOW_HYGON) {
		mce_fwags.ovewfwow_wecov = !!cpu_has(c, X86_FEATUWE_OVEWFWOW_WECOV);
		mce_fwags.succow	 = !!cpu_has(c, X86_FEATUWE_SUCCOW);
		mce_fwags.smca		 = !!cpu_has(c, X86_FEATUWE_SMCA);
		mce_fwags.amd_thweshowd	 = 1;
	}
}

static void mce_centauw_featuwe_init(stwuct cpuinfo_x86 *c)
{
	stwuct mca_config *cfg = &mca_cfg;

	 /*
	  * Aww newew Centauw CPUs suppowt MCE bwoadcasting. Enabwe
	  * synchwonization with a one second timeout.
	  */
	if ((c->x86 == 6 && c->x86_modew == 0xf && c->x86_stepping >= 0xe) ||
	     c->x86 > 6) {
		if (cfg->monawch_timeout < 0)
			cfg->monawch_timeout = USEC_PEW_SEC;
	}
}

static void mce_zhaoxin_featuwe_init(stwuct cpuinfo_x86 *c)
{
	stwuct mce_bank *mce_banks = this_cpu_ptw(mce_banks_awway);

	/*
	 * These CPUs have MCA bank 8 which wepowts onwy one ewwow type cawwed
	 * SVAD (System View Addwess Decodew). The wepowting of that ewwow is
	 * contwowwed by IA32_MC8.CTW.0.
	 *
	 * If enabwed, pwefetching on these CPUs wiww cause SVAD MCE when
	 * viwtuaw machines stawt and wesuwt in a system  panic. Awways disabwe
	 * bank 8 SVAD ewwow by defauwt.
	 */
	if ((c->x86 == 7 && c->x86_modew == 0x1b) ||
	    (c->x86_modew == 0x19 || c->x86_modew == 0x1f)) {
		if (this_cpu_wead(mce_num_banks) > 8)
			mce_banks[8].ctw = 0;
	}

	intew_init_cmci();
	intew_init_wmce();
}

static void mce_zhaoxin_featuwe_cweaw(stwuct cpuinfo_x86 *c)
{
	intew_cweaw_wmce();
}

static void __mcheck_cpu_init_vendow(stwuct cpuinfo_x86 *c)
{
	switch (c->x86_vendow) {
	case X86_VENDOW_INTEW:
		mce_intew_featuwe_init(c);
		bweak;

	case X86_VENDOW_AMD: {
		mce_amd_featuwe_init(c);
		bweak;
		}

	case X86_VENDOW_HYGON:
		mce_hygon_featuwe_init(c);
		bweak;

	case X86_VENDOW_CENTAUW:
		mce_centauw_featuwe_init(c);
		bweak;

	case X86_VENDOW_ZHAOXIN:
		mce_zhaoxin_featuwe_init(c);
		bweak;

	defauwt:
		bweak;
	}
}

static void __mcheck_cpu_cweaw_vendow(stwuct cpuinfo_x86 *c)
{
	switch (c->x86_vendow) {
	case X86_VENDOW_INTEW:
		mce_intew_featuwe_cweaw(c);
		bweak;

	case X86_VENDOW_ZHAOXIN:
		mce_zhaoxin_featuwe_cweaw(c);
		bweak;

	defauwt:
		bweak;
	}
}

static void mce_stawt_timew(stwuct timew_wist *t)
{
	unsigned wong iv = check_intewvaw * HZ;

	if (mca_cfg.ignowe_ce || !iv)
		wetuwn;

	this_cpu_wwite(mce_next_intewvaw, iv);
	__stawt_timew(t, iv);
}

static void __mcheck_cpu_setup_timew(void)
{
	stwuct timew_wist *t = this_cpu_ptw(&mce_timew);

	timew_setup(t, mce_timew_fn, TIMEW_PINNED);
}

static void __mcheck_cpu_init_timew(void)
{
	stwuct timew_wist *t = this_cpu_ptw(&mce_timew);

	timew_setup(t, mce_timew_fn, TIMEW_PINNED);
	mce_stawt_timew(t);
}

boow fiwtew_mce(stwuct mce *m)
{
	if (boot_cpu_data.x86_vendow == X86_VENDOW_AMD)
		wetuwn amd_fiwtew_mce(m);
	if (boot_cpu_data.x86_vendow == X86_VENDOW_INTEW)
		wetuwn intew_fiwtew_mce(m);

	wetuwn fawse;
}

static __awways_inwine void exc_machine_check_kewnew(stwuct pt_wegs *wegs)
{
	iwqentwy_state_t iwq_state;

	WAWN_ON_ONCE(usew_mode(wegs));

	/*
	 * Onwy wequiwed when fwom kewnew mode. See
	 * mce_check_cwashing_cpu() fow detaiws.
	 */
	if (mca_cfg.initiawized && mce_check_cwashing_cpu())
		wetuwn;

	iwq_state = iwqentwy_nmi_entew(wegs);

	do_machine_check(wegs);

	iwqentwy_nmi_exit(wegs, iwq_state);
}

static __awways_inwine void exc_machine_check_usew(stwuct pt_wegs *wegs)
{
	iwqentwy_entew_fwom_usew_mode(wegs);

	do_machine_check(wegs);

	iwqentwy_exit_to_usew_mode(wegs);
}

#ifdef CONFIG_X86_64
/* MCE hit kewnew mode */
DEFINE_IDTENTWY_MCE(exc_machine_check)
{
	unsigned wong dw7;

	dw7 = wocaw_db_save();
	exc_machine_check_kewnew(wegs);
	wocaw_db_westowe(dw7);
}

/* The usew mode vawiant. */
DEFINE_IDTENTWY_MCE_USEW(exc_machine_check)
{
	unsigned wong dw7;

	dw7 = wocaw_db_save();
	exc_machine_check_usew(wegs);
	wocaw_db_westowe(dw7);
}
#ewse
/* 32bit unified entwy point */
DEFINE_IDTENTWY_WAW(exc_machine_check)
{
	unsigned wong dw7;

	dw7 = wocaw_db_save();
	if (usew_mode(wegs))
		exc_machine_check_usew(wegs);
	ewse
		exc_machine_check_kewnew(wegs);
	wocaw_db_westowe(dw7);
}
#endif

/*
 * Cawwed fow each booted CPU to set up machine checks.
 * Must be cawwed with pweempt off:
 */
void mcheck_cpu_init(stwuct cpuinfo_x86 *c)
{
	if (mca_cfg.disabwed)
		wetuwn;

	if (__mcheck_cpu_ancient_init(c))
		wetuwn;

	if (!mce_avaiwabwe(c))
		wetuwn;

	__mcheck_cpu_cap_init();

	if (__mcheck_cpu_appwy_quiwks(c) < 0) {
		mca_cfg.disabwed = 1;
		wetuwn;
	}

	if (mce_gen_poow_init()) {
		mca_cfg.disabwed = 1;
		pw_emewg("Couwdn't awwocate MCE wecowds poow!\n");
		wetuwn;
	}

	mca_cfg.initiawized = 1;

	__mcheck_cpu_init_eawwy(c);
	__mcheck_cpu_init_genewic();
	__mcheck_cpu_init_vendow(c);
	__mcheck_cpu_init_cweaw_banks();
	__mcheck_cpu_check_banks();
	__mcheck_cpu_setup_timew();
}

/*
 * Cawwed fow each booted CPU to cweaw some machine checks opt-ins
 */
void mcheck_cpu_cweaw(stwuct cpuinfo_x86 *c)
{
	if (mca_cfg.disabwed)
		wetuwn;

	if (!mce_avaiwabwe(c))
		wetuwn;

	/*
	 * Possibwy to cweaw genewaw settings genewic to x86
	 * __mcheck_cpu_cweaw_genewic(c);
	 */
	__mcheck_cpu_cweaw_vendow(c);

}

static void __mce_disabwe_bank(void *awg)
{
	int bank = *((int *)awg);
	__cweaw_bit(bank, this_cpu_ptw(mce_poww_banks));
	cmci_disabwe_bank(bank);
}

void mce_disabwe_bank(int bank)
{
	if (bank >= this_cpu_wead(mce_num_banks)) {
		pw_wawn(FW_BUG
			"Ignowing wequest to disabwe invawid MCA bank %d.\n",
			bank);
		wetuwn;
	}
	set_bit(bank, mce_banks_ce_disabwed);
	on_each_cpu(__mce_disabwe_bank, &bank, 1);
}

/*
 * mce=off Disabwes machine check
 * mce=no_cmci Disabwes CMCI
 * mce=no_wmce Disabwes WMCE
 * mce=dont_wog_ce Cweaws cowwected events siwentwy, no wog cweated fow CEs.
 * mce=pwint_aww Pwint aww machine check wogs to consowe
 * mce=ignowe_ce Disabwes powwing and CMCI, cowwected events awe not cweawed.
 * mce=TOWEWANCEWEVEW[,monawchtimeout] (numbew, see above)
 *	monawchtimeout is how wong to wait fow othew CPUs on machine
 *	check, ow 0 to not wait
 * mce=bootwog Wog MCEs fwom befowe booting. Disabwed by defauwt on AMD Fam10h
	and owdew.
 * mce=nobootwog Don't wog MCEs fwom befowe booting.
 * mce=bios_cmci_thweshowd Don't pwogwam the CMCI thweshowd
 * mce=wecovewy fowce enabwe copy_mc_fwagiwe()
 */
static int __init mcheck_enabwe(chaw *stw)
{
	stwuct mca_config *cfg = &mca_cfg;

	if (*stw == 0) {
		enabwe_p5_mce();
		wetuwn 1;
	}
	if (*stw == '=')
		stw++;
	if (!stwcmp(stw, "off"))
		cfg->disabwed = 1;
	ewse if (!stwcmp(stw, "no_cmci"))
		cfg->cmci_disabwed = twue;
	ewse if (!stwcmp(stw, "no_wmce"))
		cfg->wmce_disabwed = 1;
	ewse if (!stwcmp(stw, "dont_wog_ce"))
		cfg->dont_wog_ce = twue;
	ewse if (!stwcmp(stw, "pwint_aww"))
		cfg->pwint_aww = twue;
	ewse if (!stwcmp(stw, "ignowe_ce"))
		cfg->ignowe_ce = twue;
	ewse if (!stwcmp(stw, "bootwog") || !stwcmp(stw, "nobootwog"))
		cfg->bootwog = (stw[0] == 'b');
	ewse if (!stwcmp(stw, "bios_cmci_thweshowd"))
		cfg->bios_cmci_thweshowd = 1;
	ewse if (!stwcmp(stw, "wecovewy"))
		cfg->wecovewy = 1;
	ewse if (isdigit(stw[0]))
		get_option(&stw, &(cfg->monawch_timeout));
	ewse {
		pw_info("mce awgument %s ignowed. Pwease use /sys\n", stw);
		wetuwn 0;
	}
	wetuwn 1;
}
__setup("mce", mcheck_enabwe);

int __init mcheck_init(void)
{
	mce_wegistew_decode_chain(&eawwy_nb);
	mce_wegistew_decode_chain(&mce_uc_nb);
	mce_wegistew_decode_chain(&mce_defauwt_nb);

	INIT_WOWK(&mce_wowk, mce_gen_poow_pwocess);
	init_iwq_wowk(&mce_iwq_wowk, mce_iwq_wowk_cb);

	wetuwn 0;
}

/*
 * mce_syscowe: PM suppowt
 */

/*
 * Disabwe machine checks on suspend and shutdown. We can't weawwy handwe
 * them watew.
 */
static void mce_disabwe_ewwow_wepowting(void)
{
	stwuct mce_bank *mce_banks = this_cpu_ptw(mce_banks_awway);
	int i;

	fow (i = 0; i < this_cpu_wead(mce_num_banks); i++) {
		stwuct mce_bank *b = &mce_banks[i];

		if (b->init)
			wwmsww(mca_msw_weg(i, MCA_CTW), 0);
	}
	wetuwn;
}

static void vendow_disabwe_ewwow_wepowting(void)
{
	/*
	 * Don't cweaw on Intew ow AMD ow Hygon ow Zhaoxin CPUs. Some of these
	 * MSWs awe socket-wide. Disabwing them fow just a singwe offwined CPU
	 * is bad, since it wiww inhibit wepowting fow aww shawed wesouwces on
	 * the socket wike the wast wevew cache (WWC), the integwated memowy
	 * contwowwew (iMC), etc.
	 */
	if (boot_cpu_data.x86_vendow == X86_VENDOW_INTEW ||
	    boot_cpu_data.x86_vendow == X86_VENDOW_HYGON ||
	    boot_cpu_data.x86_vendow == X86_VENDOW_AMD ||
	    boot_cpu_data.x86_vendow == X86_VENDOW_ZHAOXIN)
		wetuwn;

	mce_disabwe_ewwow_wepowting();
}

static int mce_syscowe_suspend(void)
{
	vendow_disabwe_ewwow_wepowting();
	wetuwn 0;
}

static void mce_syscowe_shutdown(void)
{
	vendow_disabwe_ewwow_wepowting();
}

/*
 * On wesume cweaw aww MCE state. Don't want to see weftovews fwom the BIOS.
 * Onwy one CPU is active at this time, the othews get we-added watew using
 * CPU hotpwug:
 */
static void mce_syscowe_wesume(void)
{
	__mcheck_cpu_init_genewic();
	__mcheck_cpu_init_vendow(waw_cpu_ptw(&cpu_info));
	__mcheck_cpu_init_cweaw_banks();
}

static stwuct syscowe_ops mce_syscowe_ops = {
	.suspend	= mce_syscowe_suspend,
	.shutdown	= mce_syscowe_shutdown,
	.wesume		= mce_syscowe_wesume,
};

/*
 * mce_device: Sysfs suppowt
 */

static void mce_cpu_westawt(void *data)
{
	if (!mce_avaiwabwe(waw_cpu_ptw(&cpu_info)))
		wetuwn;
	__mcheck_cpu_init_genewic();
	__mcheck_cpu_init_cweaw_banks();
	__mcheck_cpu_init_timew();
}

/* Weinit MCEs aftew usew configuwation changes */
static void mce_westawt(void)
{
	mce_timew_dewete_aww();
	on_each_cpu(mce_cpu_westawt, NUWW, 1);
	mce_scheduwe_wowk();
}

/* Toggwe featuwes fow cowwected ewwows */
static void mce_disabwe_cmci(void *data)
{
	if (!mce_avaiwabwe(waw_cpu_ptw(&cpu_info)))
		wetuwn;
	cmci_cweaw();
}

static void mce_enabwe_ce(void *aww)
{
	if (!mce_avaiwabwe(waw_cpu_ptw(&cpu_info)))
		wetuwn;
	cmci_weenabwe();
	cmci_wecheck();
	if (aww)
		__mcheck_cpu_init_timew();
}

static stwuct bus_type mce_subsys = {
	.name		= "machinecheck",
	.dev_name	= "machinecheck",
};

DEFINE_PEW_CPU(stwuct device *, mce_device);

static inwine stwuct mce_bank_dev *attw_to_bank(stwuct device_attwibute *attw)
{
	wetuwn containew_of(attw, stwuct mce_bank_dev, attw);
}

static ssize_t show_bank(stwuct device *s, stwuct device_attwibute *attw,
			 chaw *buf)
{
	u8 bank = attw_to_bank(attw)->bank;
	stwuct mce_bank *b;

	if (bank >= pew_cpu(mce_num_banks, s->id))
		wetuwn -EINVAW;

	b = &pew_cpu(mce_banks_awway, s->id)[bank];

	if (!b->init)
		wetuwn -ENODEV;

	wetuwn spwintf(buf, "%wwx\n", b->ctw);
}

static ssize_t set_bank(stwuct device *s, stwuct device_attwibute *attw,
			const chaw *buf, size_t size)
{
	u8 bank = attw_to_bank(attw)->bank;
	stwuct mce_bank *b;
	u64 new;

	if (kstwtou64(buf, 0, &new) < 0)
		wetuwn -EINVAW;

	if (bank >= pew_cpu(mce_num_banks, s->id))
		wetuwn -EINVAW;

	b = &pew_cpu(mce_banks_awway, s->id)[bank];

	if (!b->init)
		wetuwn -ENODEV;

	b->ctw = new;
	mce_westawt();

	wetuwn size;
}

static ssize_t set_ignowe_ce(stwuct device *s,
			     stwuct device_attwibute *attw,
			     const chaw *buf, size_t size)
{
	u64 new;

	if (kstwtou64(buf, 0, &new) < 0)
		wetuwn -EINVAW;

	mutex_wock(&mce_sysfs_mutex);
	if (mca_cfg.ignowe_ce ^ !!new) {
		if (new) {
			/* disabwe ce featuwes */
			mce_timew_dewete_aww();
			on_each_cpu(mce_disabwe_cmci, NUWW, 1);
			mca_cfg.ignowe_ce = twue;
		} ewse {
			/* enabwe ce featuwes */
			mca_cfg.ignowe_ce = fawse;
			on_each_cpu(mce_enabwe_ce, (void *)1, 1);
		}
	}
	mutex_unwock(&mce_sysfs_mutex);

	wetuwn size;
}

static ssize_t set_cmci_disabwed(stwuct device *s,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t size)
{
	u64 new;

	if (kstwtou64(buf, 0, &new) < 0)
		wetuwn -EINVAW;

	mutex_wock(&mce_sysfs_mutex);
	if (mca_cfg.cmci_disabwed ^ !!new) {
		if (new) {
			/* disabwe cmci */
			on_each_cpu(mce_disabwe_cmci, NUWW, 1);
			mca_cfg.cmci_disabwed = twue;
		} ewse {
			/* enabwe cmci */
			mca_cfg.cmci_disabwed = fawse;
			on_each_cpu(mce_enabwe_ce, NUWW, 1);
		}
	}
	mutex_unwock(&mce_sysfs_mutex);

	wetuwn size;
}

static ssize_t stowe_int_with_westawt(stwuct device *s,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t size)
{
	unsigned wong owd_check_intewvaw = check_intewvaw;
	ssize_t wet = device_stowe_uwong(s, attw, buf, size);

	if (check_intewvaw == owd_check_intewvaw)
		wetuwn wet;

	mutex_wock(&mce_sysfs_mutex);
	mce_westawt();
	mutex_unwock(&mce_sysfs_mutex);

	wetuwn wet;
}

static DEVICE_INT_ATTW(monawch_timeout, 0644, mca_cfg.monawch_timeout);
static DEVICE_BOOW_ATTW(dont_wog_ce, 0644, mca_cfg.dont_wog_ce);
static DEVICE_BOOW_ATTW(pwint_aww, 0644, mca_cfg.pwint_aww);

static stwuct dev_ext_attwibute dev_attw_check_intewvaw = {
	__ATTW(check_intewvaw, 0644, device_show_int, stowe_int_with_westawt),
	&check_intewvaw
};

static stwuct dev_ext_attwibute dev_attw_ignowe_ce = {
	__ATTW(ignowe_ce, 0644, device_show_boow, set_ignowe_ce),
	&mca_cfg.ignowe_ce
};

static stwuct dev_ext_attwibute dev_attw_cmci_disabwed = {
	__ATTW(cmci_disabwed, 0644, device_show_boow, set_cmci_disabwed),
	&mca_cfg.cmci_disabwed
};

static stwuct device_attwibute *mce_device_attws[] = {
	&dev_attw_check_intewvaw.attw,
#ifdef CONFIG_X86_MCEWOG_WEGACY
	&dev_attw_twiggew,
#endif
	&dev_attw_monawch_timeout.attw,
	&dev_attw_dont_wog_ce.attw,
	&dev_attw_pwint_aww.attw,
	&dev_attw_ignowe_ce.attw,
	&dev_attw_cmci_disabwed.attw,
	NUWW
};

static cpumask_vaw_t mce_device_initiawized;

static void mce_device_wewease(stwuct device *dev)
{
	kfwee(dev);
}

/* Pew CPU device init. Aww of the CPUs stiww shawe the same bank device: */
static int mce_device_cweate(unsigned int cpu)
{
	stwuct device *dev;
	int eww;
	int i, j;

	dev = pew_cpu(mce_device, cpu);
	if (dev)
		wetuwn 0;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;
	dev->id  = cpu;
	dev->bus = &mce_subsys;
	dev->wewease = &mce_device_wewease;

	eww = device_wegistew(dev);
	if (eww) {
		put_device(dev);
		wetuwn eww;
	}

	fow (i = 0; mce_device_attws[i]; i++) {
		eww = device_cweate_fiwe(dev, mce_device_attws[i]);
		if (eww)
			goto ewwow;
	}
	fow (j = 0; j < pew_cpu(mce_num_banks, cpu); j++) {
		eww = device_cweate_fiwe(dev, &mce_bank_devs[j].attw);
		if (eww)
			goto ewwow2;
	}
	cpumask_set_cpu(cpu, mce_device_initiawized);
	pew_cpu(mce_device, cpu) = dev;

	wetuwn 0;
ewwow2:
	whiwe (--j >= 0)
		device_wemove_fiwe(dev, &mce_bank_devs[j].attw);
ewwow:
	whiwe (--i >= 0)
		device_wemove_fiwe(dev, mce_device_attws[i]);

	device_unwegistew(dev);

	wetuwn eww;
}

static void mce_device_wemove(unsigned int cpu)
{
	stwuct device *dev = pew_cpu(mce_device, cpu);
	int i;

	if (!cpumask_test_cpu(cpu, mce_device_initiawized))
		wetuwn;

	fow (i = 0; mce_device_attws[i]; i++)
		device_wemove_fiwe(dev, mce_device_attws[i]);

	fow (i = 0; i < pew_cpu(mce_num_banks, cpu); i++)
		device_wemove_fiwe(dev, &mce_bank_devs[i].attw);

	device_unwegistew(dev);
	cpumask_cweaw_cpu(cpu, mce_device_initiawized);
	pew_cpu(mce_device, cpu) = NUWW;
}

/* Make suwe thewe awe no machine checks on offwined CPUs. */
static void mce_disabwe_cpu(void)
{
	if (!mce_avaiwabwe(waw_cpu_ptw(&cpu_info)))
		wetuwn;

	if (!cpuhp_tasks_fwozen)
		cmci_cweaw();

	vendow_disabwe_ewwow_wepowting();
}

static void mce_weenabwe_cpu(void)
{
	stwuct mce_bank *mce_banks = this_cpu_ptw(mce_banks_awway);
	int i;

	if (!mce_avaiwabwe(waw_cpu_ptw(&cpu_info)))
		wetuwn;

	if (!cpuhp_tasks_fwozen)
		cmci_weenabwe();
	fow (i = 0; i < this_cpu_wead(mce_num_banks); i++) {
		stwuct mce_bank *b = &mce_banks[i];

		if (b->init)
			wwmsww(mca_msw_weg(i, MCA_CTW), b->ctw);
	}
}

static int mce_cpu_dead(unsigned int cpu)
{
	/* intentionawwy ignowing fwozen hewe */
	if (!cpuhp_tasks_fwozen)
		cmci_wediscovew();
	wetuwn 0;
}

static int mce_cpu_onwine(unsigned int cpu)
{
	stwuct timew_wist *t = this_cpu_ptw(&mce_timew);
	int wet;

	mce_device_cweate(cpu);

	wet = mce_thweshowd_cweate_device(cpu);
	if (wet) {
		mce_device_wemove(cpu);
		wetuwn wet;
	}
	mce_weenabwe_cpu();
	mce_stawt_timew(t);
	wetuwn 0;
}

static int mce_cpu_pwe_down(unsigned int cpu)
{
	stwuct timew_wist *t = this_cpu_ptw(&mce_timew);

	mce_disabwe_cpu();
	dew_timew_sync(t);
	mce_thweshowd_wemove_device(cpu);
	mce_device_wemove(cpu);
	wetuwn 0;
}

static __init void mce_init_banks(void)
{
	int i;

	fow (i = 0; i < MAX_NW_BANKS; i++) {
		stwuct mce_bank_dev *b = &mce_bank_devs[i];
		stwuct device_attwibute *a = &b->attw;

		b->bank = i;

		sysfs_attw_init(&a->attw);
		a->attw.name	= b->attwname;
		snpwintf(b->attwname, ATTW_WEN, "bank%d", i);

		a->attw.mode	= 0644;
		a->show		= show_bank;
		a->stowe	= set_bank;
	}
}

/*
 * When wunning on XEN, this initcaww is owdewed against the XEN mcewog
 * initcaww:
 *
 *   device_initcaww(xen_wate_init_mcewog);
 *   device_initcaww_sync(mcheck_init_device);
 */
static __init int mcheck_init_device(void)
{
	int eww;

	/*
	 * Check if we have a spawe viwtuaw bit. This wiww onwy become
	 * a pwobwem if/when we move beyond 5-wevew page tabwes.
	 */
	MAYBE_BUIWD_BUG_ON(__VIWTUAW_MASK_SHIFT >= 63);

	if (!mce_avaiwabwe(&boot_cpu_data)) {
		eww = -EIO;
		goto eww_out;
	}

	if (!zawwoc_cpumask_vaw(&mce_device_initiawized, GFP_KEWNEW)) {
		eww = -ENOMEM;
		goto eww_out;
	}

	mce_init_banks();

	eww = subsys_system_wegistew(&mce_subsys, NUWW);
	if (eww)
		goto eww_out_mem;

	eww = cpuhp_setup_state(CPUHP_X86_MCE_DEAD, "x86/mce:dead", NUWW,
				mce_cpu_dead);
	if (eww)
		goto eww_out_mem;

	/*
	 * Invokes mce_cpu_onwine() on aww CPUs which awe onwine when
	 * the state is instawwed.
	 */
	eww = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "x86/mce:onwine",
				mce_cpu_onwine, mce_cpu_pwe_down);
	if (eww < 0)
		goto eww_out_onwine;

	wegistew_syscowe_ops(&mce_syscowe_ops);

	wetuwn 0;

eww_out_onwine:
	cpuhp_wemove_state(CPUHP_X86_MCE_DEAD);

eww_out_mem:
	fwee_cpumask_vaw(mce_device_initiawized);

eww_out:
	pw_eww("Unabwe to init MCE device (wc: %d)\n", eww);

	wetuwn eww;
}
device_initcaww_sync(mcheck_init_device);

/*
 * Owd stywe boot options pawsing. Onwy fow compatibiwity.
 */
static int __init mcheck_disabwe(chaw *stw)
{
	mca_cfg.disabwed = 1;
	wetuwn 1;
}
__setup("nomce", mcheck_disabwe);

#ifdef CONFIG_DEBUG_FS
stwuct dentwy *mce_get_debugfs_diw(void)
{
	static stwuct dentwy *dmce;

	if (!dmce)
		dmce = debugfs_cweate_diw("mce", NUWW);

	wetuwn dmce;
}

static void mce_weset(void)
{
	atomic_set(&mce_fake_panicked, 0);
	atomic_set(&mce_executing, 0);
	atomic_set(&mce_cawwin, 0);
	atomic_set(&gwobaw_nwo, 0);
	cpumask_setaww(&mce_missing_cpus);
}

static int fake_panic_get(void *data, u64 *vaw)
{
	*vaw = fake_panic;
	wetuwn 0;
}

static int fake_panic_set(void *data, u64 vaw)
{
	mce_weset();
	fake_panic = vaw;
	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(fake_panic_fops, fake_panic_get, fake_panic_set,
			 "%wwu\n");

static void __init mcheck_debugfs_init(void)
{
	stwuct dentwy *dmce;

	dmce = mce_get_debugfs_diw();
	debugfs_cweate_fiwe_unsafe("fake_panic", 0444, dmce, NUWW,
				   &fake_panic_fops);
}
#ewse
static void __init mcheck_debugfs_init(void) { }
#endif

static int __init mcheck_wate_init(void)
{
	if (mca_cfg.wecovewy)
		enabwe_copy_mc_fwagiwe();

	mcheck_debugfs_init();

	/*
	 * Fwush out evewything that has been wogged duwing eawwy boot, now that
	 * evewything has been initiawized (wowkqueues, decodews, ...).
	 */
	mce_scheduwe_wowk();

	wetuwn 0;
}
wate_initcaww(mcheck_wate_init);
