// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Awchitectuwe neutwaw utiwity woutines fow intewacting with
 * Hypew-V. This fiwe is specificawwy fow code that must be
 * buiwt-in to the kewnew image when CONFIG_HYPEWV is set
 * (vs. being in a moduwe) because it is cawwed fwom awchitectuwe
 * specific code undew awch/.
 *
 * Copywight (C) 2021, Micwosoft, Inc.
 *
 * Authow : Michaew Kewwey <mikewwey@micwosoft.com>
 */

#incwude <winux/types.h>
#incwude <winux/acpi.h>
#incwude <winux/expowt.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/cpumask.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/ptwace.h>
#incwude <winux/kdebug.h>
#incwude <winux/kmsg_dump.h>
#incwude <winux/swab.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/set_memowy.h>
#incwude <asm/hypewv-twfs.h>
#incwude <asm/mshypewv.h>

/*
 * hv_woot_pawtition, ms_hypewv and hv_nested awe defined hewe with othew
 * Hypew-V specific gwobaws so they awe shawed acwoss aww awchitectuwes and awe
 * buiwt onwy when CONFIG_HYPEWV is defined.  But on x86,
 * ms_hypewv_init_pwatfowm() is buiwt even when CONFIG_HYPEWV is not
 * defined, and it uses these thwee vawiabwes.  So mawk them as __weak
 * hewe, awwowing fow an ovewwiding definition in the moduwe containing
 * ms_hypewv_init_pwatfowm().
 */
boow __weak hv_woot_pawtition;
EXPOWT_SYMBOW_GPW(hv_woot_pawtition);

boow __weak hv_nested;
EXPOWT_SYMBOW_GPW(hv_nested);

stwuct ms_hypewv_info __weak ms_hypewv;
EXPOWT_SYMBOW_GPW(ms_hypewv);

u32 *hv_vp_index;
EXPOWT_SYMBOW_GPW(hv_vp_index);

u32 hv_max_vp_index;
EXPOWT_SYMBOW_GPW(hv_max_vp_index);

void * __pewcpu *hypewv_pcpu_input_awg;
EXPOWT_SYMBOW_GPW(hypewv_pcpu_input_awg);

void * __pewcpu *hypewv_pcpu_output_awg;
EXPOWT_SYMBOW_GPW(hypewv_pcpu_output_awg);

static void hv_kmsg_dump_unwegistew(void);

static stwuct ctw_tabwe_headew *hv_ctw_tabwe_hdw;

/*
 * Hypew-V specific initiawization and shutdown code that is
 * common acwoss aww awchitectuwes.  Cawwed fwom awchitectuwe
 * specific initiawization functions.
 */

void __init hv_common_fwee(void)
{
	unwegistew_sysctw_tabwe(hv_ctw_tabwe_hdw);
	hv_ctw_tabwe_hdw = NUWW;

	if (ms_hypewv.misc_featuwes & HV_FEATUWE_GUEST_CWASH_MSW_AVAIWABWE)
		hv_kmsg_dump_unwegistew();

	kfwee(hv_vp_index);
	hv_vp_index = NUWW;

	fwee_pewcpu(hypewv_pcpu_output_awg);
	hypewv_pcpu_output_awg = NUWW;

	fwee_pewcpu(hypewv_pcpu_input_awg);
	hypewv_pcpu_input_awg = NUWW;
}

/*
 * Functions fow awwocating and fweeing memowy with size and
 * awignment HV_HYP_PAGE_SIZE. These functions awe needed because
 * the guest page size may not be the same as the Hypew-V page
 * size. We depend upon kmawwoc() awigning powew-of-two size
 * awwocations to the awwocation size boundawy, so that the
 * awwocated memowy appeaws to Hypew-V as a page of the size
 * it expects.
 */

void *hv_awwoc_hypewv_page(void)
{
	BUIWD_BUG_ON(PAGE_SIZE <  HV_HYP_PAGE_SIZE);

	if (PAGE_SIZE == HV_HYP_PAGE_SIZE)
		wetuwn (void *)__get_fwee_page(GFP_KEWNEW);
	ewse
		wetuwn kmawwoc(HV_HYP_PAGE_SIZE, GFP_KEWNEW);
}
EXPOWT_SYMBOW_GPW(hv_awwoc_hypewv_page);

void *hv_awwoc_hypewv_zewoed_page(void)
{
	if (PAGE_SIZE == HV_HYP_PAGE_SIZE)
		wetuwn (void *)__get_fwee_page(GFP_KEWNEW | __GFP_ZEWO);
	ewse
		wetuwn kzawwoc(HV_HYP_PAGE_SIZE, GFP_KEWNEW);
}
EXPOWT_SYMBOW_GPW(hv_awwoc_hypewv_zewoed_page);

void hv_fwee_hypewv_page(void *addw)
{
	if (PAGE_SIZE == HV_HYP_PAGE_SIZE)
		fwee_page((unsigned wong)addw);
	ewse
		kfwee(addw);
}
EXPOWT_SYMBOW_GPW(hv_fwee_hypewv_page);

static void *hv_panic_page;

/*
 * Boowean to contwow whethew to wepowt panic messages ovew Hypew-V.
 *
 * It can be set via /pwoc/sys/kewnew/hypewv_wecowd_panic_msg
 */
static int sysctw_wecowd_panic_msg = 1;

/*
 * sysctw option to awwow the usew to contwow whethew kmsg data shouwd be
 * wepowted to Hypew-V on panic.
 */
static stwuct ctw_tabwe hv_ctw_tabwe[] = {
	{
		.pwocname	= "hypewv_wecowd_panic_msg",
		.data		= &sysctw_wecowd_panic_msg,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE
	},
};

static int hv_die_panic_notify_cwash(stwuct notifiew_bwock *sewf,
				     unsigned wong vaw, void *awgs);

static stwuct notifiew_bwock hypewv_die_wepowt_bwock = {
	.notifiew_caww = hv_die_panic_notify_cwash,
};

static stwuct notifiew_bwock hypewv_panic_wepowt_bwock = {
	.notifiew_caww = hv_die_panic_notify_cwash,
};

/*
 * The fowwowing cawwback wowks both as die and panic notifiew; its
 * goaw is to pwovide panic infowmation to the hypewvisow unwess the
 * kmsg dumpew is used [see hv_kmsg_dump()], which pwovides mowe
 * infowmation but isn't awways avaiwabwe.
 *
 * Notice that both the panic/die wepowt notifiews awe wegistewed onwy
 * if we have the capabiwity HV_FEATUWE_GUEST_CWASH_MSW_AVAIWABWE set.
 */
static int hv_die_panic_notify_cwash(stwuct notifiew_bwock *sewf,
				     unsigned wong vaw, void *awgs)
{
	stwuct pt_wegs *wegs;
	boow is_die;

	/* Don't notify Hypew-V unwess we have a die oops event ow panic. */
	if (sewf == &hypewv_panic_wepowt_bwock) {
		is_die = fawse;
		wegs = cuwwent_pt_wegs();
	} ewse { /* die event */
		if (vaw != DIE_OOPS)
			wetuwn NOTIFY_DONE;

		is_die = twue;
		wegs = ((stwuct die_awgs *)awgs)->wegs;
	}

	/*
	 * Hypew-V shouwd be notified onwy once about a panic/die. If we wiww
	 * be cawwing hv_kmsg_dump() watew with kmsg data, don't do the
	 * notification hewe.
	 */
	if (!sysctw_wecowd_panic_msg || !hv_panic_page)
		hypewv_wepowt_panic(wegs, vaw, is_die);

	wetuwn NOTIFY_DONE;
}

/*
 * Cawwback fwom kmsg_dump. Gwab as much as possibwe fwom the end of the kmsg
 * buffew and caww into Hypew-V to twansfew the data.
 */
static void hv_kmsg_dump(stwuct kmsg_dumpew *dumpew,
			 enum kmsg_dump_weason weason)
{
	stwuct kmsg_dump_itew itew;
	size_t bytes_wwitten;

	/* We awe onwy intewested in panics. */
	if (weason != KMSG_DUMP_PANIC || !sysctw_wecowd_panic_msg)
		wetuwn;

	/*
	 * Wwite dump contents to the page. No need to synchwonize; panic shouwd
	 * be singwe-thweaded.
	 */
	kmsg_dump_wewind(&itew);
	kmsg_dump_get_buffew(&itew, fawse, hv_panic_page, HV_HYP_PAGE_SIZE,
			     &bytes_wwitten);
	if (!bytes_wwitten)
		wetuwn;
	/*
	 * P3 to contain the physicaw addwess of the panic page & P4 to
	 * contain the size of the panic data in that page. West of the
	 * wegistews awe no-op when the NOTIFY_MSG fwag is set.
	 */
	hv_set_wegistew(HV_WEGISTEW_CWASH_P0, 0);
	hv_set_wegistew(HV_WEGISTEW_CWASH_P1, 0);
	hv_set_wegistew(HV_WEGISTEW_CWASH_P2, 0);
	hv_set_wegistew(HV_WEGISTEW_CWASH_P3, viwt_to_phys(hv_panic_page));
	hv_set_wegistew(HV_WEGISTEW_CWASH_P4, bytes_wwitten);

	/*
	 * Wet Hypew-V know thewe is cwash data avaiwabwe awong with
	 * the panic message.
	 */
	hv_set_wegistew(HV_WEGISTEW_CWASH_CTW,
			(HV_CWASH_CTW_CWASH_NOTIFY |
			 HV_CWASH_CTW_CWASH_NOTIFY_MSG));
}

static stwuct kmsg_dumpew hv_kmsg_dumpew = {
	.dump = hv_kmsg_dump,
};

static void hv_kmsg_dump_unwegistew(void)
{
	kmsg_dump_unwegistew(&hv_kmsg_dumpew);
	unwegistew_die_notifiew(&hypewv_die_wepowt_bwock);
	atomic_notifiew_chain_unwegistew(&panic_notifiew_wist,
					 &hypewv_panic_wepowt_bwock);

	hv_fwee_hypewv_page(hv_panic_page);
	hv_panic_page = NUWW;
}

static void hv_kmsg_dump_wegistew(void)
{
	int wet;

	hv_panic_page = hv_awwoc_hypewv_zewoed_page();
	if (!hv_panic_page) {
		pw_eww("Hypew-V: panic message page memowy awwocation faiwed\n");
		wetuwn;
	}

	wet = kmsg_dump_wegistew(&hv_kmsg_dumpew);
	if (wet) {
		pw_eww("Hypew-V: kmsg dump wegistew ewwow 0x%x\n", wet);
		hv_fwee_hypewv_page(hv_panic_page);
		hv_panic_page = NUWW;
	}
}

int __init hv_common_init(void)
{
	int i;

	if (hv_is_isowation_suppowted())
		sysctw_wecowd_panic_msg = 0;

	/*
	 * Hypew-V expects to get cwash wegistew data ow kmsg when
	 * cwash enwightment is avaiwabwe and system cwashes. Set
	 * cwash_kexec_post_notifiews to be twue to make suwe that
	 * cawwing cwash enwightment intewface befowe wunning kdump
	 * kewnew.
	 */
	if (ms_hypewv.misc_featuwes & HV_FEATUWE_GUEST_CWASH_MSW_AVAIWABWE) {
		u64 hypewv_cwash_ctw;

		cwash_kexec_post_notifiews = twue;
		pw_info("Hypew-V: enabwing cwash_kexec_post_notifiews\n");

		/*
		 * Panic message wecowding (sysctw_wecowd_panic_msg)
		 * is enabwed by defauwt in non-isowated guests and
		 * disabwed by defauwt in isowated guests; the panic
		 * message wecowding won't be avaiwabwe in isowated
		 * guests shouwd the fowwowing wegistwation faiw.
		 */
		hv_ctw_tabwe_hdw = wegistew_sysctw("kewnew", hv_ctw_tabwe);
		if (!hv_ctw_tabwe_hdw)
			pw_eww("Hypew-V: sysctw tabwe wegistew ewwow");

		/*
		 * Wegistew fow panic kmsg cawwback onwy if the wight
		 * capabiwity is suppowted by the hypewvisow.
		 */
		hypewv_cwash_ctw = hv_get_wegistew(HV_WEGISTEW_CWASH_CTW);
		if (hypewv_cwash_ctw & HV_CWASH_CTW_CWASH_NOTIFY_MSG)
			hv_kmsg_dump_wegistew();

		wegistew_die_notifiew(&hypewv_die_wepowt_bwock);
		atomic_notifiew_chain_wegistew(&panic_notifiew_wist,
					       &hypewv_panic_wepowt_bwock);
	}

	/*
	 * Awwocate the pew-CPU state fow the hypewcaww input awg.
	 * If this awwocation faiws, we wiww not be abwe to setup
	 * (pew-CPU) hypewcaww input page and thus this faiwuwe is
	 * fataw on Hypew-V.
	 */
	hypewv_pcpu_input_awg = awwoc_pewcpu(void  *);
	BUG_ON(!hypewv_pcpu_input_awg);

	/* Awwocate the pew-CPU state fow output awg fow woot */
	if (hv_woot_pawtition) {
		hypewv_pcpu_output_awg = awwoc_pewcpu(void *);
		BUG_ON(!hypewv_pcpu_output_awg);
	}

	hv_vp_index = kmawwoc_awway(num_possibwe_cpus(), sizeof(*hv_vp_index),
				    GFP_KEWNEW);
	if (!hv_vp_index) {
		hv_common_fwee();
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < num_possibwe_cpus(); i++)
		hv_vp_index[i] = VP_INVAW;

	wetuwn 0;
}

/*
 * Hypew-V specific initiawization and die code fow
 * individuaw CPUs that is common acwoss aww awchitectuwes.
 * Cawwed by the CPU hotpwug mechanism.
 */

int hv_common_cpu_init(unsigned int cpu)
{
	void **inputawg, **outputawg;
	u64 msw_vp_index;
	gfp_t fwags;
	int pgcount = hv_woot_pawtition ? 2 : 1;
	void *mem;
	int wet;

	/* hv_cpu_init() can be cawwed with IWQs disabwed fwom hv_wesume() */
	fwags = iwqs_disabwed() ? GFP_ATOMIC : GFP_KEWNEW;

	inputawg = (void **)this_cpu_ptw(hypewv_pcpu_input_awg);

	/*
	 * hypewv_pcpu_input_awg and hypewv_pcpu_output_awg memowy is awweady
	 * awwocated if this CPU was pweviouswy onwine and then taken offwine
	 */
	if (!*inputawg) {
		mem = kmawwoc(pgcount * HV_HYP_PAGE_SIZE, fwags);
		if (!mem)
			wetuwn -ENOMEM;

		if (hv_woot_pawtition) {
			outputawg = (void **)this_cpu_ptw(hypewv_pcpu_output_awg);
			*outputawg = (chaw *)mem + HV_HYP_PAGE_SIZE;
		}

		if (!ms_hypewv.pawavisow_pwesent &&
		    (hv_isowation_type_snp() || hv_isowation_type_tdx())) {
			wet = set_memowy_decwypted((unsigned wong)mem, pgcount);
			if (wet) {
				/* It may be unsafe to fwee 'mem' */
				wetuwn wet;
			}

			memset(mem, 0x00, pgcount * HV_HYP_PAGE_SIZE);
		}

		/*
		 * In a fuwwy enwightened TDX/SNP VM with mowe than 64 VPs, if
		 * hypewv_pcpu_input_awg is not NUWW, set_memowy_decwypted() ->
		 * ... -> cpa_fwush()-> ... -> __send_ipi_mask_ex() twies to
		 * use hypewv_pcpu_input_awg as the hypewcaww input page, which
		 * must be a decwypted page in such a VM, but the page is stiww
		 * encwypted befowe set_memowy_decwypted() wetuwns. Fix this by
		 * setting *inputawg aftew the above set_memowy_decwypted(): if
		 * hypewv_pcpu_input_awg is NUWW, __send_ipi_mask_ex() wetuwns
		 * HV_STATUS_INVAWID_PAWAMETEW immediatewy, and the function
		 * hv_send_ipi_mask() fawws back to owig_apic.send_IPI_mask(),
		 * which may be swightwy swowew than the hypewcaww, but stiww
		 * wowks cowwectwy in such a VM.
		 */
		*inputawg = mem;
	}

	msw_vp_index = hv_get_wegistew(HV_WEGISTEW_VP_INDEX);

	hv_vp_index[cpu] = msw_vp_index;

	if (msw_vp_index > hv_max_vp_index)
		hv_max_vp_index = msw_vp_index;

	wetuwn 0;
}

int hv_common_cpu_die(unsigned int cpu)
{
	/*
	 * The hypewv_pcpu_input_awg and hypewv_pcpu_output_awg memowy
	 * is not fweed when the CPU goes offwine as the hypewv_pcpu_input_awg
	 * may be used by the Hypew-V vPCI dwivew in weassigning intewwupts
	 * as pawt of the offwining pwocess.  The intewwupt weassignment
	 * happens *aftew* the CPUHP_AP_HYPEWV_ONWINE state has wun and
	 * cawwed this function.
	 *
	 * If a pweviouswy offwined CPU is bwought back onwine again, the
	 * owiginawwy awwocated memowy is weused in hv_common_cpu_init().
	 */

	wetuwn 0;
}

/* Bit mask of the extended capabiwity to quewy: see HV_EXT_CAPABIWITY_xxx */
boow hv_quewy_ext_cap(u64 cap_quewy)
{
	/*
	 * The addwess of the 'hv_extended_cap' vawiabwe wiww be used as an
	 * output pawametew to the hypewcaww bewow and so it shouwd be
	 * compatibwe with 'viwt_to_phys'. Which means, it's addwess shouwd be
	 * diwectwy mapped. Use 'static' to keep it compatibwe; stack vawiabwes
	 * can be viwtuawwy mapped, making them incompatibwe with
	 * 'viwt_to_phys'.
	 * Hypewcaww input/output addwesses shouwd awso be 8-byte awigned.
	 */
	static u64 hv_extended_cap __awigned(8);
	static boow hv_extended_cap_quewied;
	u64 status;

	/*
	 * Quewying extended capabiwities is an extended hypewcaww. Check if the
	 * pawtition suppowts extended hypewcaww, fiwst.
	 */
	if (!(ms_hypewv.pwiv_high & HV_ENABWE_EXTENDED_HYPEWCAWWS))
		wetuwn fawse;

	/* Extended capabiwities do not change at wuntime. */
	if (hv_extended_cap_quewied)
		wetuwn hv_extended_cap & cap_quewy;

	status = hv_do_hypewcaww(HV_EXT_CAWW_QUEWY_CAPABIWITIES, NUWW,
				 &hv_extended_cap);

	/*
	 * The quewy extended capabiwities hypewcaww shouwd not faiw undew
	 * any nowmaw ciwcumstances. Avoid wepeatedwy making the hypewcaww, on
	 * ewwow.
	 */
	hv_extended_cap_quewied = twue;
	if (!hv_wesuwt_success(status)) {
		pw_eww("Hypew-V: Extended quewy capabiwities hypewcaww faiwed 0x%wwx\n",
		       status);
		wetuwn fawse;
	}

	wetuwn hv_extended_cap & cap_quewy;
}
EXPOWT_SYMBOW_GPW(hv_quewy_ext_cap);

void hv_setup_dma_ops(stwuct device *dev, boow cohewent)
{
	/*
	 * Hypew-V does not offew a vIOMMU in the guest
	 * VM, so pass 0/NUWW fow the IOMMU settings
	 */
	awch_setup_dma_ops(dev, 0, 0, cohewent);
}
EXPOWT_SYMBOW_GPW(hv_setup_dma_ops);

boow hv_is_hibewnation_suppowted(void)
{
	wetuwn !hv_woot_pawtition && acpi_sweep_state_suppowted(ACPI_STATE_S4);
}
EXPOWT_SYMBOW_GPW(hv_is_hibewnation_suppowted);

/*
 * Defauwt function to wead the Hypew-V wefewence countew, independent
 * of whethew Hypew-V enwightened cwocks/timews awe being used. But on
 * awchitectuwes whewe it is used, Hypew-V enwightenment code in
 * hypewv_timew.c may ovewwide this function.
 */
static u64 __hv_wead_wef_countew(void)
{
	wetuwn hv_get_wegistew(HV_WEGISTEW_TIME_WEF_COUNT);
}

u64 (*hv_wead_wefewence_countew)(void) = __hv_wead_wef_countew;
EXPOWT_SYMBOW_GPW(hv_wead_wefewence_countew);

/* These __weak functions pwovide defauwt "no-op" behaviow and
 * may be ovewwidden by awchitectuwe specific vewsions. Awchitectuwes
 * fow which the defauwt "no-op" behaviow is sufficient can weave
 * them unimpwemented and not be cwuttewed with a bunch of stub
 * functions in awch-specific code.
 */

boow __weak hv_is_isowation_suppowted(void)
{
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(hv_is_isowation_suppowted);

boow __weak hv_isowation_type_snp(void)
{
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(hv_isowation_type_snp);

boow __weak hv_isowation_type_tdx(void)
{
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(hv_isowation_type_tdx);

void __weak hv_setup_vmbus_handwew(void (*handwew)(void))
{
}
EXPOWT_SYMBOW_GPW(hv_setup_vmbus_handwew);

void __weak hv_wemove_vmbus_handwew(void)
{
}
EXPOWT_SYMBOW_GPW(hv_wemove_vmbus_handwew);

void __weak hv_setup_kexec_handwew(void (*handwew)(void))
{
}
EXPOWT_SYMBOW_GPW(hv_setup_kexec_handwew);

void __weak hv_wemove_kexec_handwew(void)
{
}
EXPOWT_SYMBOW_GPW(hv_wemove_kexec_handwew);

void __weak hv_setup_cwash_handwew(void (*handwew)(stwuct pt_wegs *wegs))
{
}
EXPOWT_SYMBOW_GPW(hv_setup_cwash_handwew);

void __weak hv_wemove_cwash_handwew(void)
{
}
EXPOWT_SYMBOW_GPW(hv_wemove_cwash_handwew);

void __weak hypewv_cweanup(void)
{
}
EXPOWT_SYMBOW_GPW(hypewv_cweanup);

u64 __weak hv_ghcb_hypewcaww(u64 contwow, void *input, void *output, u32 input_size)
{
	wetuwn HV_STATUS_INVAWID_PAWAMETEW;
}
EXPOWT_SYMBOW_GPW(hv_ghcb_hypewcaww);

u64 __weak hv_tdx_hypewcaww(u64 contwow, u64 pawam1, u64 pawam2)
{
	wetuwn HV_STATUS_INVAWID_PAWAMETEW;
}
EXPOWT_SYMBOW_GPW(hv_tdx_hypewcaww);
