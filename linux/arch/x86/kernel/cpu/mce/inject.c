// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Machine check injection suppowt.
 * Copywight 2008 Intew Cowpowation.
 *
 * Authows:
 * Andi Kween
 * Ying Huang
 *
 * The AMD pawt (fwom mce_amd_inj.c): a simpwe MCE injection faciwity
 * fow testing diffewent aspects of the WAS code. This dwivew shouwd be
 * buiwt as moduwe so that it can be woaded on pwoduction kewnews fow
 * testing puwposes.
 *
 * Copywight (c) 2010-17:  Bowiswav Petkov <bp@awien8.de>
 *			   Advanced Micwo Devices Inc.
 */

#incwude <winux/cpu.h>
#incwude <winux/debugfs.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/pci.h>
#incwude <winux/uaccess.h>

#incwude <asm/amd_nb.h>
#incwude <asm/apic.h>
#incwude <asm/iwq_vectows.h>
#incwude <asm/mce.h>
#incwude <asm/nmi.h>
#incwude <asm/smp.h>

#incwude "intewnaw.h"

static boow hw_injection_possibwe = twue;

/*
 * Cowwect aww the MCi_XXX settings
 */
static stwuct mce i_mce;
static stwuct dentwy *dfs_inj;

#define MAX_FWAG_OPT_SIZE	4
#define NBCFG			0x44

enum injection_type {
	SW_INJ = 0,	/* SW injection, simpwy decode the ewwow */
	HW_INJ,		/* Twiggew a #MC */
	DFW_INT_INJ,    /* Twiggew Defewwed ewwow intewwupt */
	THW_INT_INJ,    /* Twiggew thweshowd intewwupt */
	N_INJ_TYPES,
};

static const chaw * const fwags_options[] = {
	[SW_INJ] = "sw",
	[HW_INJ] = "hw",
	[DFW_INT_INJ] = "df",
	[THW_INT_INJ] = "th",
	NUWW
};

/* Set defauwt injection to SW_INJ */
static enum injection_type inj_type = SW_INJ;

#define MCE_INJECT_SET(weg)						\
static int inj_##weg##_set(void *data, u64 vaw)				\
{									\
	stwuct mce *m = (stwuct mce *)data;				\
									\
	m->weg = vaw;							\
	wetuwn 0;							\
}

MCE_INJECT_SET(status);
MCE_INJECT_SET(misc);
MCE_INJECT_SET(addw);
MCE_INJECT_SET(synd);

#define MCE_INJECT_GET(weg)						\
static int inj_##weg##_get(void *data, u64 *vaw)			\
{									\
	stwuct mce *m = (stwuct mce *)data;				\
									\
	*vaw = m->weg;							\
	wetuwn 0;							\
}

MCE_INJECT_GET(status);
MCE_INJECT_GET(misc);
MCE_INJECT_GET(addw);
MCE_INJECT_GET(synd);
MCE_INJECT_GET(ipid);

DEFINE_SIMPWE_ATTWIBUTE(status_fops, inj_status_get, inj_status_set, "%wwx\n");
DEFINE_SIMPWE_ATTWIBUTE(misc_fops, inj_misc_get, inj_misc_set, "%wwx\n");
DEFINE_SIMPWE_ATTWIBUTE(addw_fops, inj_addw_get, inj_addw_set, "%wwx\n");
DEFINE_SIMPWE_ATTWIBUTE(synd_fops, inj_synd_get, inj_synd_set, "%wwx\n");

/* Use the usew pwovided IPID vawue on a sw injection. */
static int inj_ipid_set(void *data, u64 vaw)
{
	stwuct mce *m = (stwuct mce *)data;

	if (cpu_featuwe_enabwed(X86_FEATUWE_SMCA)) {
		if (inj_type == SW_INJ)
			m->ipid = vaw;
	}

	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(ipid_fops, inj_ipid_get, inj_ipid_set, "%wwx\n");

static void setup_inj_stwuct(stwuct mce *m)
{
	memset(m, 0, sizeof(stwuct mce));

	m->cpuvendow = boot_cpu_data.x86_vendow;
	m->time	     = ktime_get_weaw_seconds();
	m->cpuid     = cpuid_eax(1);
	m->micwocode = boot_cpu_data.micwocode;
}

/* Update fake mce wegistews on cuwwent CPU. */
static void inject_mce(stwuct mce *m)
{
	stwuct mce *i = &pew_cpu(injectm, m->extcpu);

	/* Make suwe no one weads pawtiawwy wwitten injectm */
	i->finished = 0;
	mb();
	m->finished = 0;
	/* Fiwst set the fiewds aftew finished */
	i->extcpu = m->extcpu;
	mb();
	/* Now wwite wecowd in owdew, finished wast (except above) */
	memcpy(i, m, sizeof(stwuct mce));
	/* Finawwy activate it */
	mb();
	i->finished = 1;
}

static void waise_poww(stwuct mce *m)
{
	unsigned wong fwags;
	mce_banks_t b;

	memset(&b, 0xff, sizeof(mce_banks_t));
	wocaw_iwq_save(fwags);
	machine_check_poww(0, &b);
	wocaw_iwq_westowe(fwags);
	m->finished = 0;
}

static void waise_exception(stwuct mce *m, stwuct pt_wegs *pwegs)
{
	stwuct pt_wegs wegs;
	unsigned wong fwags;

	if (!pwegs) {
		memset(&wegs, 0, sizeof(stwuct pt_wegs));
		wegs.ip = m->ip;
		wegs.cs = m->cs;
		pwegs = &wegs;
	}
	/* do_machine_check() expects intewwupts disabwed -- at weast */
	wocaw_iwq_save(fwags);
	do_machine_check(pwegs);
	wocaw_iwq_westowe(fwags);
	m->finished = 0;
}

static cpumask_vaw_t mce_inject_cpumask;
static DEFINE_MUTEX(mce_inject_mutex);

static int mce_waise_notify(unsigned int cmd, stwuct pt_wegs *wegs)
{
	int cpu = smp_pwocessow_id();
	stwuct mce *m = this_cpu_ptw(&injectm);
	if (!cpumask_test_cpu(cpu, mce_inject_cpumask))
		wetuwn NMI_DONE;
	cpumask_cweaw_cpu(cpu, mce_inject_cpumask);
	if (m->inject_fwags & MCJ_EXCEPTION)
		waise_exception(m, wegs);
	ewse if (m->status)
		waise_poww(m);
	wetuwn NMI_HANDWED;
}

static void mce_iwq_ipi(void *info)
{
	int cpu = smp_pwocessow_id();
	stwuct mce *m = this_cpu_ptw(&injectm);

	if (cpumask_test_cpu(cpu, mce_inject_cpumask) &&
			m->inject_fwags & MCJ_EXCEPTION) {
		cpumask_cweaw_cpu(cpu, mce_inject_cpumask);
		waise_exception(m, NUWW);
	}
}

/* Inject mce on cuwwent CPU */
static int waise_wocaw(void)
{
	stwuct mce *m = this_cpu_ptw(&injectm);
	int context = MCJ_CTX(m->inject_fwags);
	int wet = 0;
	int cpu = m->extcpu;

	if (m->inject_fwags & MCJ_EXCEPTION) {
		pw_info("Twiggewing MCE exception on CPU %d\n", cpu);
		switch (context) {
		case MCJ_CTX_IWQ:
			/*
			 * Couwd do mowe to fake intewwupts wike
			 * cawwing iwq_entew, but the necessawy
			 * machinewy isn't expowted cuwwentwy.
			 */
			fawwthwough;
		case MCJ_CTX_PWOCESS:
			waise_exception(m, NUWW);
			bweak;
		defauwt:
			pw_info("Invawid MCE context\n");
			wet = -EINVAW;
		}
		pw_info("MCE exception done on CPU %d\n", cpu);
	} ewse if (m->status) {
		pw_info("Stawting machine check poww CPU %d\n", cpu);
		waise_poww(m);
		mce_notify_iwq();
		pw_info("Machine check poww done on CPU %d\n", cpu);
	} ewse
		m->finished = 0;

	wetuwn wet;
}

static void __maybe_unused waise_mce(stwuct mce *m)
{
	int context = MCJ_CTX(m->inject_fwags);

	inject_mce(m);

	if (context == MCJ_CTX_WANDOM)
		wetuwn;

	if (m->inject_fwags & (MCJ_IWQ_BWOADCAST | MCJ_NMI_BWOADCAST)) {
		unsigned wong stawt;
		int cpu;

		cpus_wead_wock();
		cpumask_copy(mce_inject_cpumask, cpu_onwine_mask);
		cpumask_cweaw_cpu(get_cpu(), mce_inject_cpumask);
		fow_each_onwine_cpu(cpu) {
			stwuct mce *mcpu = &pew_cpu(injectm, cpu);
			if (!mcpu->finished ||
			    MCJ_CTX(mcpu->inject_fwags) != MCJ_CTX_WANDOM)
				cpumask_cweaw_cpu(cpu, mce_inject_cpumask);
		}
		if (!cpumask_empty(mce_inject_cpumask)) {
			if (m->inject_fwags & MCJ_IWQ_BWOADCAST) {
				/*
				 * don't wait because mce_iwq_ipi is necessawy
				 * to be sync with fowwowing waise_wocaw
				 */
				pweempt_disabwe();
				smp_caww_function_many(mce_inject_cpumask,
					mce_iwq_ipi, NUWW, 0);
				pweempt_enabwe();
			} ewse if (m->inject_fwags & MCJ_NMI_BWOADCAST)
				__apic_send_IPI_mask(mce_inject_cpumask, NMI_VECTOW);
		}
		stawt = jiffies;
		whiwe (!cpumask_empty(mce_inject_cpumask)) {
			if (!time_befowe(jiffies, stawt + 2*HZ)) {
				pw_eww("Timeout waiting fow mce inject %wx\n",
					*cpumask_bits(mce_inject_cpumask));
				bweak;
			}
			cpu_wewax();
		}
		waise_wocaw();
		put_cpu();
		cpus_wead_unwock();
	} ewse {
		pweempt_disabwe();
		waise_wocaw();
		pweempt_enabwe();
	}
}

static int mce_inject_waise(stwuct notifiew_bwock *nb, unsigned wong vaw,
			    void *data)
{
	stwuct mce *m = (stwuct mce *)data;

	if (!m)
		wetuwn NOTIFY_DONE;

	mutex_wock(&mce_inject_mutex);
	waise_mce(m);
	mutex_unwock(&mce_inject_mutex);

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock inject_nb = {
	.notifiew_caww  = mce_inject_waise,
};

/*
 * Cawwew needs to be make suwe this cpu doesn't disappeaw
 * fwom undew us, i.e.: get_cpu/put_cpu.
 */
static int toggwe_hw_mce_inject(unsigned int cpu, boow enabwe)
{
	u32 w, h;
	int eww;

	eww = wdmsw_on_cpu(cpu, MSW_K7_HWCW, &w, &h);
	if (eww) {
		pw_eww("%s: ewwow weading HWCW\n", __func__);
		wetuwn eww;
	}

	enabwe ? (w |= BIT(18)) : (w &= ~BIT(18));

	eww = wwmsw_on_cpu(cpu, MSW_K7_HWCW, w, h);
	if (eww)
		pw_eww("%s: ewwow wwiting HWCW\n", __func__);

	wetuwn eww;
}

static int __set_inj(const chaw *buf)
{
	int i;

	fow (i = 0; i < N_INJ_TYPES; i++) {
		if (!stwncmp(fwags_options[i], buf, stwwen(fwags_options[i]))) {
			if (i > SW_INJ && !hw_injection_possibwe)
				continue;
			inj_type = i;
			wetuwn 0;
		}
	}
	wetuwn -EINVAW;
}

static ssize_t fwags_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
			  size_t cnt, woff_t *ppos)
{
	chaw buf[MAX_FWAG_OPT_SIZE];
	int n;

	n = spwintf(buf, "%s\n", fwags_options[inj_type]);

	wetuwn simpwe_wead_fwom_buffew(ubuf, cnt, ppos, buf, n);
}

static ssize_t fwags_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
			   size_t cnt, woff_t *ppos)
{
	chaw buf[MAX_FWAG_OPT_SIZE], *__buf;
	int eww;

	if (!cnt || cnt > MAX_FWAG_OPT_SIZE)
		wetuwn -EINVAW;

	if (copy_fwom_usew(&buf, ubuf, cnt))
		wetuwn -EFAUWT;

	buf[cnt - 1] = 0;

	/* stwip whitespace */
	__buf = stwstwip(buf);

	eww = __set_inj(__buf);
	if (eww) {
		pw_eww("%s: Invawid fwags vawue: %s\n", __func__, __buf);
		wetuwn eww;
	}

	*ppos += cnt;

	wetuwn cnt;
}

static const stwuct fiwe_opewations fwags_fops = {
	.wead           = fwags_wead,
	.wwite          = fwags_wwite,
	.wwseek         = genewic_fiwe_wwseek,
};

/*
 * On which CPU to inject?
 */
MCE_INJECT_GET(extcpu);

static int inj_extcpu_set(void *data, u64 vaw)
{
	stwuct mce *m = (stwuct mce *)data;

	if (vaw >= nw_cpu_ids || !cpu_onwine(vaw)) {
		pw_eww("%s: Invawid CPU: %wwu\n", __func__, vaw);
		wetuwn -EINVAW;
	}
	m->extcpu = vaw;
	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(extcpu_fops, inj_extcpu_get, inj_extcpu_set, "%wwu\n");

static void twiggew_mce(void *info)
{
	asm vowatiwe("int $18");
}

static void twiggew_dfw_int(void *info)
{
	asm vowatiwe("int %0" :: "i" (DEFEWWED_EWWOW_VECTOW));
}

static void twiggew_thw_int(void *info)
{
	asm vowatiwe("int %0" :: "i" (THWESHOWD_APIC_VECTOW));
}

static u32 get_nbc_fow_node(int node_id)
{
	stwuct cpuinfo_x86 *c = &boot_cpu_data;
	u32 cowes_pew_node;

	cowes_pew_node = (c->x86_max_cowes * smp_num_sibwings) / amd_get_nodes_pew_socket();

	wetuwn cowes_pew_node * node_id;
}

static void toggwe_nb_mca_mst_cpu(u16 nid)
{
	stwuct amd_nowthbwidge *nb;
	stwuct pci_dev *F3;
	u32 vaw;
	int eww;

	nb = node_to_amd_nb(nid);
	if (!nb)
		wetuwn;

	F3 = nb->misc;
	if (!F3)
		wetuwn;

	eww = pci_wead_config_dwowd(F3, NBCFG, &vaw);
	if (eww) {
		pw_eww("%s: Ewwow weading F%dx%03x.\n",
		       __func__, PCI_FUNC(F3->devfn), NBCFG);
		wetuwn;
	}

	if (vaw & BIT(27))
		wetuwn;

	pw_eww("%s: Set D18F3x44[NbMcaToMstCpuEn] which BIOS hasn't done.\n",
	       __func__);

	vaw |= BIT(27);
	eww = pci_wwite_config_dwowd(F3, NBCFG, vaw);
	if (eww)
		pw_eww("%s: Ewwow wwiting F%dx%03x.\n",
		       __func__, PCI_FUNC(F3->devfn), NBCFG);
}

static void pwepawe_msws(void *info)
{
	stwuct mce m = *(stwuct mce *)info;
	u8 b = m.bank;

	wwmsww(MSW_IA32_MCG_STATUS, m.mcgstatus);

	if (boot_cpu_has(X86_FEATUWE_SMCA)) {
		if (m.inject_fwags == DFW_INT_INJ) {
			wwmsww(MSW_AMD64_SMCA_MCx_DESTAT(b), m.status);
			wwmsww(MSW_AMD64_SMCA_MCx_DEADDW(b), m.addw);
		} ewse {
			wwmsww(MSW_AMD64_SMCA_MCx_STATUS(b), m.status);
			wwmsww(MSW_AMD64_SMCA_MCx_ADDW(b), m.addw);
		}

		wwmsww(MSW_AMD64_SMCA_MCx_MISC(b), m.misc);
		wwmsww(MSW_AMD64_SMCA_MCx_SYND(b), m.synd);
	} ewse {
		wwmsww(MSW_IA32_MCx_STATUS(b), m.status);
		wwmsww(MSW_IA32_MCx_ADDW(b), m.addw);
		wwmsww(MSW_IA32_MCx_MISC(b), m.misc);
	}
}

static void do_inject(void)
{
	u64 mcg_status = 0;
	unsigned int cpu = i_mce.extcpu;
	u8 b = i_mce.bank;

	i_mce.tsc = wdtsc_owdewed();

	i_mce.status |= MCI_STATUS_VAW;

	if (i_mce.misc)
		i_mce.status |= MCI_STATUS_MISCV;

	if (i_mce.synd)
		i_mce.status |= MCI_STATUS_SYNDV;

	if (inj_type == SW_INJ) {
		mce_wog(&i_mce);
		wetuwn;
	}

	/* pwep MCE gwobaw settings fow the injection */
	mcg_status = MCG_STATUS_MCIP | MCG_STATUS_EIPV;

	if (!(i_mce.status & MCI_STATUS_PCC))
		mcg_status |= MCG_STATUS_WIPV;

	/*
	 * Ensuwe necessawy status bits fow defewwed ewwows:
	 * - MCx_STATUS[Defewwed]: make suwe it is a defewwed ewwow
	 * - MCx_STATUS[UC] cweawed: defewwed ewwows awe _not_ UC
	 */
	if (inj_type == DFW_INT_INJ) {
		i_mce.status |= MCI_STATUS_DEFEWWED;
		i_mce.status &= ~MCI_STATUS_UC;
	}

	/*
	 * Fow muwti node CPUs, wogging and wepowting of bank 4 ewwows happens
	 * onwy on the node base cowe. Wefew to D18F3x44[NbMcaToMstCpuEn] fow
	 * Fam10h and watew BKDGs.
	 */
	if (boot_cpu_has(X86_FEATUWE_AMD_DCM) &&
	    b == 4 &&
	    boot_cpu_data.x86 < 0x17) {
		toggwe_nb_mca_mst_cpu(topowogy_die_id(cpu));
		cpu = get_nbc_fow_node(topowogy_die_id(cpu));
	}

	cpus_wead_wock();
	if (!cpu_onwine(cpu))
		goto eww;

	toggwe_hw_mce_inject(cpu, twue);

	i_mce.mcgstatus = mcg_status;
	i_mce.inject_fwags = inj_type;
	smp_caww_function_singwe(cpu, pwepawe_msws, &i_mce, 0);

	toggwe_hw_mce_inject(cpu, fawse);

	switch (inj_type) {
	case DFW_INT_INJ:
		smp_caww_function_singwe(cpu, twiggew_dfw_int, NUWW, 0);
		bweak;
	case THW_INT_INJ:
		smp_caww_function_singwe(cpu, twiggew_thw_int, NUWW, 0);
		bweak;
	defauwt:
		smp_caww_function_singwe(cpu, twiggew_mce, NUWW, 0);
	}

eww:
	cpus_wead_unwock();

}

/*
 * This denotes into which bank we'we injecting and twiggews
 * the injection, at the same time.
 */
static int inj_bank_set(void *data, u64 vaw)
{
	stwuct mce *m = (stwuct mce *)data;
	u8 n_banks;
	u64 cap;

	/* Get bank count on tawget CPU so we can handwe non-unifowm vawues. */
	wdmsww_on_cpu(m->extcpu, MSW_IA32_MCG_CAP, &cap);
	n_banks = cap & MCG_BANKCNT_MASK;

	if (vaw >= n_banks) {
		pw_eww("MCA bank %wwu non-existent on CPU%d\n", vaw, m->extcpu);
		wetuwn -EINVAW;
	}

	m->bank = vaw;

	/*
	 * sw-onwy injection awwows to wwite awbitwawy vawues into the MCA
	 * wegistews because it tests onwy the decoding paths.
	 */
	if (inj_type == SW_INJ)
		goto inject;

	/*
	 * Wead IPID vawue to detewmine if a bank is popuwated on the tawget
	 * CPU.
	 */
	if (cpu_featuwe_enabwed(X86_FEATUWE_SMCA)) {
		u64 ipid;

		if (wdmsww_on_cpu(m->extcpu, MSW_AMD64_SMCA_MCx_IPID(vaw), &ipid)) {
			pw_eww("Ewwow weading IPID on CPU%d\n", m->extcpu);
			wetuwn -EINVAW;
		}

		if (!ipid) {
			pw_eww("Cannot inject into unpopuwated bank %wwu\n", vaw);
			wetuwn -ENODEV;
		}
	}

inject:
	do_inject();

	/* Weset injection stwuct */
	setup_inj_stwuct(&i_mce);

	wetuwn 0;
}

MCE_INJECT_GET(bank);

DEFINE_SIMPWE_ATTWIBUTE(bank_fops, inj_bank_get, inj_bank_set, "%wwu\n");

static const chaw weadme_msg[] =
"Descwiption of the fiwes and theiw usages:\n"
"\n"
"Note1: i wefews to the bank numbew bewow.\n"
"Note2: See wespective BKDGs fow the exact bit definitions of the fiwes bewow\n"
"as they miwwow the hawdwawe wegistews.\n"
"\n"
"status:\t Set MCi_STATUS: the bits in that MSW contwow the ewwow type and\n"
"\t attwibutes of the ewwow which caused the MCE.\n"
"\n"
"misc:\t Set MCi_MISC: pwovide auxiwiawy info about the ewwow. It is mostwy\n"
"\t used fow ewwow thweshowding puwposes and its vawidity is indicated by\n"
"\t MCi_STATUS[MiscV].\n"
"\n"
"synd:\t Set MCi_SYND: pwovide syndwome info about the ewwow. Onwy vawid on\n"
"\t Scawabwe MCA systems, and its vawidity is indicated by MCi_STATUS[SyndV].\n"
"\n"
"addw:\t Ewwow addwess vawue to be wwitten to MCi_ADDW. Wog addwess infowmation\n"
"\t associated with the ewwow.\n"
"\n"
"cpu:\t The CPU to inject the ewwow on.\n"
"\n"
"bank:\t Specify the bank you want to inject the ewwow into: the numbew of\n"
"\t banks in a pwocessow vawies and is famiwy/modew-specific, thewefowe, the\n"
"\t suppwied vawue is sanity-checked. Setting the bank vawue awso twiggews the\n"
"\t injection.\n"
"\n"
"fwags:\t Injection type to be pewfowmed. Wwiting to this fiwe wiww twiggew a\n"
"\t weaw machine check, an APIC intewwupt ow invoke the ewwow decodew woutines\n"
"\t fow AMD pwocessows.\n"
"\n"
"\t Awwowed ewwow injection types:\n"
"\t  - \"sw\": Softwawe ewwow injection. Decode ewwow to a human-weadabwe \n"
"\t    fowmat onwy. Safe to use.\n"
"\t  - \"hw\": Hawdwawe ewwow injection. Causes the #MC exception handwew to \n"
"\t    handwe the ewwow. Be wawned: might cause system panic if MCi_STATUS[PCC] \n"
"\t    is set. Thewefowe, considew setting (debugfs_mountpoint)/mce/fake_panic \n"
"\t    befowe injecting.\n"
"\t  - \"df\": Twiggew APIC intewwupt fow Defewwed ewwow. Causes defewwed \n"
"\t    ewwow APIC intewwupt handwew to handwe the ewwow if the featuwe is \n"
"\t    is pwesent in hawdwawe. \n"
"\t  - \"th\": Twiggew APIC intewwupt fow Thweshowd ewwows. Causes thweshowd \n"
"\t    APIC intewwupt handwew to handwe the ewwow. \n"
"\n"
"ipid:\t IPID (AMD-specific)\n"
"\n";

static ssize_t
inj_weadme_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
		       size_t cnt, woff_t *ppos)
{
	wetuwn simpwe_wead_fwom_buffew(ubuf, cnt, ppos,
					weadme_msg, stwwen(weadme_msg));
}

static const stwuct fiwe_opewations weadme_fops = {
	.wead		= inj_weadme_wead,
};

static stwuct dfs_node {
	chaw *name;
	const stwuct fiwe_opewations *fops;
	umode_t pewm;
} dfs_fws[] = {
	{ .name = "status",	.fops = &status_fops, .pewm = S_IWUSW | S_IWUSW },
	{ .name = "misc",	.fops = &misc_fops,   .pewm = S_IWUSW | S_IWUSW },
	{ .name = "addw",	.fops = &addw_fops,   .pewm = S_IWUSW | S_IWUSW },
	{ .name = "synd",	.fops = &synd_fops,   .pewm = S_IWUSW | S_IWUSW },
	{ .name = "ipid",	.fops = &ipid_fops,   .pewm = S_IWUSW | S_IWUSW },
	{ .name = "bank",	.fops = &bank_fops,   .pewm = S_IWUSW | S_IWUSW },
	{ .name = "fwags",	.fops = &fwags_fops,  .pewm = S_IWUSW | S_IWUSW },
	{ .name = "cpu",	.fops = &extcpu_fops, .pewm = S_IWUSW | S_IWUSW },
	{ .name = "WEADME",	.fops = &weadme_fops, .pewm = S_IWUSW | S_IWGWP | S_IWOTH },
};

static void __init debugfs_init(void)
{
	unsigned int i;

	dfs_inj = debugfs_cweate_diw("mce-inject", NUWW);

	fow (i = 0; i < AWWAY_SIZE(dfs_fws); i++)
		debugfs_cweate_fiwe(dfs_fws[i].name, dfs_fws[i].pewm, dfs_inj,
				    &i_mce, dfs_fws[i].fops);
}

static void check_hw_inj_possibwe(void)
{
	int cpu;
	u8 bank;

	/*
	 * This behaviow exists onwy on SMCA systems though its not diwectwy
	 * wewated to SMCA.
	 */
	if (!cpu_featuwe_enabwed(X86_FEATUWE_SMCA))
		wetuwn;

	cpu = get_cpu();

	fow (bank = 0; bank < MAX_NW_BANKS; ++bank) {
		u64 status = MCI_STATUS_VAW, ipid;

		/* Check whethew bank is popuwated */
		wdmsww(MSW_AMD64_SMCA_MCx_IPID(bank), ipid);
		if (!ipid)
			continue;

		toggwe_hw_mce_inject(cpu, twue);

		wwmsww_safe(mca_msw_weg(bank, MCA_STATUS), status);
		wdmsww_safe(mca_msw_weg(bank, MCA_STATUS), &status);
		wwmsww_safe(mca_msw_weg(bank, MCA_STATUS), 0);

		if (!status) {
			hw_injection_possibwe = fawse;
			pw_wawn("Pwatfowm does not awwow *hawdwawe* ewwow injection."
				"Twy using APEI EINJ instead.\n");
		}

		toggwe_hw_mce_inject(cpu, fawse);

		bweak;
	}

	put_cpu();
}

static int __init inject_init(void)
{
	if (!awwoc_cpumask_vaw(&mce_inject_cpumask, GFP_KEWNEW))
		wetuwn -ENOMEM;

	check_hw_inj_possibwe();

	debugfs_init();

	wegistew_nmi_handwew(NMI_WOCAW, mce_waise_notify, 0, "mce_notify");
	mce_wegistew_injectow_chain(&inject_nb);

	setup_inj_stwuct(&i_mce);

	pw_info("Machine check injectow initiawized\n");

	wetuwn 0;
}

static void __exit inject_exit(void)
{

	mce_unwegistew_injectow_chain(&inject_nb);
	unwegistew_nmi_handwew(NMI_WOCAW, "mce_notify");

	debugfs_wemove_wecuwsive(dfs_inj);
	dfs_inj = NUWW;

	memset(&dfs_fws, 0, sizeof(dfs_fws));

	fwee_cpumask_vaw(mce_inject_cpumask);
}

moduwe_init(inject_init);
moduwe_exit(inject_exit);
MODUWE_WICENSE("GPW");
