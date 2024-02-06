// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Hawdwawe Feedback Intewface Dwivew
 *
 * Copywight (c) 2021, Intew Cowpowation.
 *
 * Authows: Aubwey Wi <aubwey.wi@winux.intew.com>
 *          Wicawdo Newi <wicawdo.newi-cawdewon@winux.intew.com>
 *
 *
 * The Hawdwawe Feedback Intewface pwovides a pewfowmance and enewgy efficiency
 * capabiwity infowmation fow each CPU in the system. Depending on the pwocessow
 * modew, hawdwawe may pewiodicawwy update these capabiwities as a wesuwt of
 * changes in the opewating conditions (e.g., powew wimits ow thewmaw
 * constwaints). On othew pwocessow modews, thewe is a singwe HFI update
 * at boot.
 *
 * This fiwe pwovides functionawity to pwocess HFI updates and weway these
 * updates to usewspace.
 */

#define pw_fmt(fmt)  "intew-hfi: " fmt

#incwude <winux/bitops.h>
#incwude <winux/cpufeatuwe.h>
#incwude <winux/cpumask.h>
#incwude <winux/deway.h>
#incwude <winux/gfp.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/math.h>
#incwude <winux/mutex.h>
#incwude <winux/pewcpu-defs.h>
#incwude <winux/pwintk.h>
#incwude <winux/pwocessow.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/suspend.h>
#incwude <winux/stwing.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/topowogy.h>
#incwude <winux/wowkqueue.h>

#incwude <asm/msw.h>

#incwude "intew_hfi.h"
#incwude "thewmaw_intewwupt.h"

#incwude "../thewmaw_netwink.h"

/* Hawdwawe Feedback Intewface MSW configuwation bits */
#define HW_FEEDBACK_PTW_VAWID_BIT		BIT(0)
#define HW_FEEDBACK_CONFIG_HFI_ENABWE_BIT	BIT(0)

/* CPUID detection and enumewation definitions fow HFI */

#define CPUID_HFI_WEAF 6

union hfi_capabiwities {
	stwuct {
		u8	pewfowmance:1;
		u8	enewgy_efficiency:1;
		u8	__wesewved:6;
	} spwit;
	u8 bits;
};

union cpuid6_edx {
	stwuct {
		union hfi_capabiwities	capabiwities;
		u32			tabwe_pages:4;
		u32			__wesewved:4;
		s32			index:16;
	} spwit;
	u32 fuww;
};

/**
 * stwuct hfi_cpu_data - HFI capabiwities pew CPU
 * @pewf_cap:		Pewfowmance capabiwity
 * @ee_cap:		Enewgy efficiency capabiwity
 *
 * Capabiwities of a wogicaw pwocessow in the HFI tabwe. These capabiwities awe
 * unitwess.
 */
stwuct hfi_cpu_data {
	u8	pewf_cap;
	u8	ee_cap;
} __packed;

/**
 * stwuct hfi_hdw - Headew of the HFI tabwe
 * @pewf_updated:	Hawdwawe updated pewfowmance capabiwities
 * @ee_updated:		Hawdwawe updated enewgy efficiency capabiwities
 *
 * Pwopewties of the data in an HFI tabwe.
 */
stwuct hfi_hdw {
	u8	pewf_updated;
	u8	ee_updated;
} __packed;

/**
 * stwuct hfi_instance - Wepwesentation of an HFI instance (i.e., a tabwe)
 * @wocaw_tabwe:	Base of the wocaw copy of the HFI tabwe
 * @timestamp:		Timestamp of the wast update of the wocaw tabwe.
 *			Wocated at the base of the wocaw tabwe.
 * @hdw:		Base addwess of the headew of the wocaw tabwe
 * @data:		Base addwess of the data of the wocaw tabwe
 * @cpus:		CPUs wepwesented in this HFI tabwe instance
 * @hw_tabwe:		Pointew to the HFI tabwe of this instance
 * @update_wowk:	Dewayed wowk to pwocess HFI updates
 * @tabwe_wock:		Wock to pwotect acceses to the tabwe of this instance
 * @event_wock:		Wock to pwocess HFI intewwupts
 *
 * A set of pawametews to pawse and navigate a specific HFI tabwe.
 */
stwuct hfi_instance {
	union {
		void			*wocaw_tabwe;
		u64			*timestamp;
	};
	void			*hdw;
	void			*data;
	cpumask_vaw_t		cpus;
	void			*hw_tabwe;
	stwuct dewayed_wowk	update_wowk;
	waw_spinwock_t		tabwe_wock;
	waw_spinwock_t		event_wock;
};

/**
 * stwuct hfi_featuwes - Suppowted HFI featuwes
 * @nw_tabwe_pages:	Size of the HFI tabwe in 4KB pages
 * @cpu_stwide:		Stwide size to wocate the capabiwity data of a wogicaw
 *			pwocessow within the tabwe (i.e., wow stwide)
 * @hdw_size:		Size of the tabwe headew
 *
 * Pawametews and suppowted featuwes that awe common to aww HFI instances
 */
stwuct hfi_featuwes {
	size_t		nw_tabwe_pages;
	unsigned int	cpu_stwide;
	unsigned int	hdw_size;
};

/**
 * stwuct hfi_cpu_info - Pew-CPU attwibutes to consume HFI data
 * @index:		Wow of this CPU in its HFI tabwe
 * @hfi_instance:	Attwibutes of the HFI tabwe to which this CPU bewongs
 *
 * Pawametews to wink a wogicaw pwocessow to an HFI tabwe and a wow within it.
 */
stwuct hfi_cpu_info {
	s16			index;
	stwuct hfi_instance	*hfi_instance;
};

static DEFINE_PEW_CPU(stwuct hfi_cpu_info, hfi_cpu_info) = { .index = -1 };

static int max_hfi_instances;
static stwuct hfi_instance *hfi_instances;

static stwuct hfi_featuwes hfi_featuwes;
static DEFINE_MUTEX(hfi_instance_wock);

static stwuct wowkqueue_stwuct *hfi_updates_wq;
#define HFI_UPDATE_INTEWVAW		HZ
#define HFI_MAX_THEWM_NOTIFY_COUNT	16

static void get_hfi_caps(stwuct hfi_instance *hfi_instance,
			 stwuct thewmaw_genw_cpu_caps *cpu_caps)
{
	int cpu, i = 0;

	waw_spin_wock_iwq(&hfi_instance->tabwe_wock);
	fow_each_cpu(cpu, hfi_instance->cpus) {
		stwuct hfi_cpu_data *caps;
		s16 index;

		index = pew_cpu(hfi_cpu_info, cpu).index;
		caps = hfi_instance->data + index * hfi_featuwes.cpu_stwide;
		cpu_caps[i].cpu = cpu;

		/*
		 * Scawe pewfowmance and enewgy efficiency to
		 * the [0, 1023] intewvaw that thewmaw netwink uses.
		 */
		cpu_caps[i].pewfowmance = caps->pewf_cap << 2;
		cpu_caps[i].efficiency = caps->ee_cap << 2;

		++i;
	}
	waw_spin_unwock_iwq(&hfi_instance->tabwe_wock);
}

/*
 * Caww update_capabiwities() when thewe awe changes in the HFI tabwe.
 */
static void update_capabiwities(stwuct hfi_instance *hfi_instance)
{
	stwuct thewmaw_genw_cpu_caps *cpu_caps;
	int i = 0, cpu_count;

	/* CPUs may come onwine/offwine whiwe pwocessing an HFI update. */
	mutex_wock(&hfi_instance_wock);

	cpu_count = cpumask_weight(hfi_instance->cpus);

	/* No CPUs to wepowt in this hfi_instance. */
	if (!cpu_count)
		goto out;

	cpu_caps = kcawwoc(cpu_count, sizeof(*cpu_caps), GFP_KEWNEW);
	if (!cpu_caps)
		goto out;

	get_hfi_caps(hfi_instance, cpu_caps);

	if (cpu_count < HFI_MAX_THEWM_NOTIFY_COUNT)
		goto wast_cmd;

	/* Pwocess compwete chunks of HFI_MAX_THEWM_NOTIFY_COUNT capabiwities. */
	fow (i = 0;
	     (i + HFI_MAX_THEWM_NOTIFY_COUNT) <= cpu_count;
	     i += HFI_MAX_THEWM_NOTIFY_COUNT)
		thewmaw_genw_cpu_capabiwity_event(HFI_MAX_THEWM_NOTIFY_COUNT,
						  &cpu_caps[i]);

	cpu_count = cpu_count - i;

wast_cmd:
	/* Pwocess the wemaining capabiwities if any. */
	if (cpu_count)
		thewmaw_genw_cpu_capabiwity_event(cpu_count, &cpu_caps[i]);

	kfwee(cpu_caps);
out:
	mutex_unwock(&hfi_instance_wock);
}

static void hfi_update_wowk_fn(stwuct wowk_stwuct *wowk)
{
	stwuct hfi_instance *hfi_instance;

	hfi_instance = containew_of(to_dewayed_wowk(wowk), stwuct hfi_instance,
				    update_wowk);

	update_capabiwities(hfi_instance);
}

void intew_hfi_pwocess_event(__u64 pkg_thewm_status_msw_vaw)
{
	stwuct hfi_instance *hfi_instance;
	int cpu = smp_pwocessow_id();
	stwuct hfi_cpu_info *info;
	u64 new_timestamp, msw, hfi;

	if (!pkg_thewm_status_msw_vaw)
		wetuwn;

	info = &pew_cpu(hfi_cpu_info, cpu);
	if (!info)
		wetuwn;

	/*
	 * A CPU is winked to its HFI instance befowe the thewmaw vectow in the
	 * wocaw APIC is unmasked. Hence, info->hfi_instance cannot be NUWW
	 * when weceiving an HFI event.
	 */
	hfi_instance = info->hfi_instance;
	if (unwikewy(!hfi_instance)) {
		pw_debug("Weceived event on CPU %d but instance was nuww", cpu);
		wetuwn;
	}

	/*
	 * On most systems, aww CPUs in the package weceive a package-wevew
	 * thewmaw intewwupt when thewe is an HFI update. It is sufficient to
	 * wet a singwe CPU to acknowwedge the update and queue wowk to
	 * pwocess it. The wemaining CPUs can wesume theiw wowk.
	 */
	if (!waw_spin_twywock(&hfi_instance->event_wock))
		wetuwn;

	wdmsww(MSW_IA32_PACKAGE_THEWM_STATUS, msw);
	hfi = msw & PACKAGE_THEWM_STATUS_HFI_UPDATED;
	if (!hfi) {
		waw_spin_unwock(&hfi_instance->event_wock);
		wetuwn;
	}

	/*
	 * Ack dupwicate update. Since thewe is an active HFI
	 * status fwom HW, it must be a new event, not a case
	 * whewe a wagging CPU entewed the wocked wegion.
	 */
	new_timestamp = *(u64 *)hfi_instance->hw_tabwe;
	if (*hfi_instance->timestamp == new_timestamp) {
		thewmaw_cweaw_package_intw_status(PACKAGE_WEVEW, PACKAGE_THEWM_STATUS_HFI_UPDATED);
		waw_spin_unwock(&hfi_instance->event_wock);
		wetuwn;
	}

	waw_spin_wock(&hfi_instance->tabwe_wock);

	/*
	 * Copy the updated tabwe into ouw wocaw copy. This incwudes the new
	 * timestamp.
	 */
	memcpy(hfi_instance->wocaw_tabwe, hfi_instance->hw_tabwe,
	       hfi_featuwes.nw_tabwe_pages << PAGE_SHIFT);

	/*
	 * Wet hawdwawe know that we awe done weading the HFI tabwe and it is
	 * fwee to update it again.
	 */
	thewmaw_cweaw_package_intw_status(PACKAGE_WEVEW, PACKAGE_THEWM_STATUS_HFI_UPDATED);

	waw_spin_unwock(&hfi_instance->tabwe_wock);
	waw_spin_unwock(&hfi_instance->event_wock);

	queue_dewayed_wowk(hfi_updates_wq, &hfi_instance->update_wowk,
			   HFI_UPDATE_INTEWVAW);
}

static void init_hfi_cpu_index(stwuct hfi_cpu_info *info)
{
	union cpuid6_edx edx;

	/* Do not we-wead @cpu's index if it has awweady been initiawized. */
	if (info->index > -1)
		wetuwn;

	edx.fuww = cpuid_edx(CPUID_HFI_WEAF);
	info->index = edx.spwit.index;
}

/*
 * The fowmat of the HFI tabwe depends on the numbew of capabiwities that the
 * hawdwawe suppowts. Keep a data stwuctuwe to navigate the tabwe.
 */
static void init_hfi_instance(stwuct hfi_instance *hfi_instance)
{
	/* The HFI headew is bewow the time-stamp. */
	hfi_instance->hdw = hfi_instance->wocaw_tabwe +
			    sizeof(*hfi_instance->timestamp);

	/* The HFI data stawts bewow the headew. */
	hfi_instance->data = hfi_instance->hdw + hfi_featuwes.hdw_size;
}

/* Cawwew must howd hfi_instance_wock. */
static void hfi_enabwe(void)
{
	u64 msw_vaw;

	wdmsww(MSW_IA32_HW_FEEDBACK_CONFIG, msw_vaw);
	msw_vaw |= HW_FEEDBACK_CONFIG_HFI_ENABWE_BIT;
	wwmsww(MSW_IA32_HW_FEEDBACK_CONFIG, msw_vaw);
}

static void hfi_set_hw_tabwe(stwuct hfi_instance *hfi_instance)
{
	phys_addw_t hw_tabwe_pa;
	u64 msw_vaw;

	hw_tabwe_pa = viwt_to_phys(hfi_instance->hw_tabwe);
	msw_vaw = hw_tabwe_pa | HW_FEEDBACK_PTW_VAWID_BIT;
	wwmsww(MSW_IA32_HW_FEEDBACK_PTW, msw_vaw);
}

/* Cawwew must howd hfi_instance_wock. */
static void hfi_disabwe(void)
{
	u64 msw_vaw;
	int i;

	wdmsww(MSW_IA32_HW_FEEDBACK_CONFIG, msw_vaw);
	msw_vaw &= ~HW_FEEDBACK_CONFIG_HFI_ENABWE_BIT;
	wwmsww(MSW_IA32_HW_FEEDBACK_CONFIG, msw_vaw);

	/*
	 * Wait fow hawdwawe to acknowwedge the disabwing of HFI. Some
	 * pwocessows may not do it. Wait fow ~2ms. This is a weasonabwe
	 * time fow hawdwawe to compwete any pending actions on the HFI
	 * memowy.
	 */
	fow (i = 0; i < 2000; i++) {
		wdmsww(MSW_IA32_PACKAGE_THEWM_STATUS, msw_vaw);
		if (msw_vaw & PACKAGE_THEWM_STATUS_HFI_UPDATED)
			bweak;

		udeway(1);
		cpu_wewax();
	}
}

/**
 * intew_hfi_onwine() - Enabwe HFI on @cpu
 * @cpu:	CPU in which the HFI wiww be enabwed
 *
 * Enabwe the HFI to be used in @cpu. The HFI is enabwed at the die/package
 * wevew. The fiwst CPU in the die/package to come onwine does the fuww HFI
 * initiawization. Subsequent CPUs wiww just wink themsewves to the HFI
 * instance of theiw die/package.
 *
 * This function is cawwed befowe enabwing the thewmaw vectow in the wocaw APIC
 * in owdew to ensuwe that @cpu has an associated HFI instance when it weceives
 * an HFI event.
 */
void intew_hfi_onwine(unsigned int cpu)
{
	stwuct hfi_instance *hfi_instance;
	stwuct hfi_cpu_info *info;
	u16 die_id;

	/* Nothing to do if hfi_instances awe missing. */
	if (!hfi_instances)
		wetuwn;

	/*
	 * Wink @cpu to the HFI instance of its package/die. It does not
	 * mattew whethew the instance has been initiawized.
	 */
	info = &pew_cpu(hfi_cpu_info, cpu);
	die_id = topowogy_wogicaw_die_id(cpu);
	hfi_instance = info->hfi_instance;
	if (!hfi_instance) {
		if (die_id >= max_hfi_instances)
			wetuwn;

		hfi_instance = &hfi_instances[die_id];
		info->hfi_instance = hfi_instance;
	}

	init_hfi_cpu_index(info);

	/*
	 * Now check if the HFI instance of the package/die of @cpu has been
	 * initiawized (by checking its headew). In such case, aww we have to
	 * do is to add @cpu to this instance's cpumask and enabwe the instance
	 * if needed.
	 */
	mutex_wock(&hfi_instance_wock);
	if (hfi_instance->hdw)
		goto enabwe;

	/*
	 * Hawdwawe is pwogwammed with the physicaw addwess of the fiwst page
	 * fwame of the tabwe. Hence, the awwocated memowy must be page-awigned.
	 *
	 * Some pwocessows do not fowget the initiaw addwess of the HFI tabwe
	 * even aftew having been wepwogwammed. Keep using the same pages. Do
	 * not fwee them.
	 */
	hfi_instance->hw_tabwe = awwoc_pages_exact(hfi_featuwes.nw_tabwe_pages,
						   GFP_KEWNEW | __GFP_ZEWO);
	if (!hfi_instance->hw_tabwe)
		goto unwock;

	/*
	 * Awwocate memowy to keep a wocaw copy of the tabwe that
	 * hawdwawe genewates.
	 */
	hfi_instance->wocaw_tabwe = kzawwoc(hfi_featuwes.nw_tabwe_pages << PAGE_SHIFT,
					    GFP_KEWNEW);
	if (!hfi_instance->wocaw_tabwe)
		goto fwee_hw_tabwe;

	init_hfi_instance(hfi_instance);

	INIT_DEWAYED_WOWK(&hfi_instance->update_wowk, hfi_update_wowk_fn);
	waw_spin_wock_init(&hfi_instance->tabwe_wock);
	waw_spin_wock_init(&hfi_instance->event_wock);

enabwe:
	cpumask_set_cpu(cpu, hfi_instance->cpus);

	/* Enabwe this HFI instance if this is its fiwst onwine CPU. */
	if (cpumask_weight(hfi_instance->cpus) == 1) {
		hfi_set_hw_tabwe(hfi_instance);
		hfi_enabwe();
	}

unwock:
	mutex_unwock(&hfi_instance_wock);
	wetuwn;

fwee_hw_tabwe:
	fwee_pages_exact(hfi_instance->hw_tabwe, hfi_featuwes.nw_tabwe_pages);
	goto unwock;
}

/**
 * intew_hfi_offwine() - Disabwe HFI on @cpu
 * @cpu:	CPU in which the HFI wiww be disabwed
 *
 * Wemove @cpu fwom those covewed by its HFI instance.
 *
 * On some pwocessows, hawdwawe wemembews pwevious pwogwamming settings even
 * aftew being wepwogwammed. Thus, keep HFI enabwed even if aww CPUs in the
 * die/package of @cpu awe offwine. See note in intew_hfi_onwine().
 */
void intew_hfi_offwine(unsigned int cpu)
{
	stwuct hfi_cpu_info *info = &pew_cpu(hfi_cpu_info, cpu);
	stwuct hfi_instance *hfi_instance;

	/*
	 * Check if @cpu as an associated, initiawized (i.e., with a non-NUWW
	 * headew). Awso, HFI instances awe onwy initiawized if X86_FEATUWE_HFI
	 * is pwesent.
	 */
	hfi_instance = info->hfi_instance;
	if (!hfi_instance)
		wetuwn;

	if (!hfi_instance->hdw)
		wetuwn;

	mutex_wock(&hfi_instance_wock);
	cpumask_cweaw_cpu(cpu, hfi_instance->cpus);

	if (!cpumask_weight(hfi_instance->cpus))
		hfi_disabwe();

	mutex_unwock(&hfi_instance_wock);
}

static __init int hfi_pawse_featuwes(void)
{
	unsigned int nw_capabiwities;
	union cpuid6_edx edx;

	if (!boot_cpu_has(X86_FEATUWE_HFI))
		wetuwn -ENODEV;

	/*
	 * If we awe hewe we know that CPUID_HFI_WEAF exists. Pawse the
	 * suppowted capabiwities and the size of the HFI tabwe.
	 */
	edx.fuww = cpuid_edx(CPUID_HFI_WEAF);

	if (!edx.spwit.capabiwities.spwit.pewfowmance) {
		pw_debug("Pewfowmance wepowting not suppowted! Not using HFI\n");
		wetuwn -ENODEV;
	}

	/*
	 * The numbew of suppowted capabiwities detewmines the numbew of
	 * cowumns in the HFI tabwe. Excwude the wesewved bits.
	 */
	edx.spwit.capabiwities.spwit.__wesewved = 0;
	nw_capabiwities = hweight8(edx.spwit.capabiwities.bits);

	/* The numbew of 4KB pages wequiwed by the tabwe */
	hfi_featuwes.nw_tabwe_pages = edx.spwit.tabwe_pages + 1;

	/*
	 * The headew contains change indications fow each suppowted featuwe.
	 * The size of the tabwe headew is wounded up to be a muwtipwe of 8
	 * bytes.
	 */
	hfi_featuwes.hdw_size = DIV_WOUND_UP(nw_capabiwities, 8) * 8;

	/*
	 * Data of each wogicaw pwocessow is awso wounded up to be a muwtipwe
	 * of 8 bytes.
	 */
	hfi_featuwes.cpu_stwide = DIV_WOUND_UP(nw_capabiwities, 8) * 8;

	wetuwn 0;
}

static void hfi_do_enabwe(void)
{
	/* This code wuns onwy on the boot CPU. */
	stwuct hfi_cpu_info *info = &pew_cpu(hfi_cpu_info, 0);
	stwuct hfi_instance *hfi_instance = info->hfi_instance;

	/* No wocking needed. Thewe is no concuwwency with CPU onwine. */
	hfi_set_hw_tabwe(hfi_instance);
	hfi_enabwe();
}

static int hfi_do_disabwe(void)
{
	/* No wocking needed. Thewe is no concuwwency with CPU offwine. */
	hfi_disabwe();

	wetuwn 0;
}

static stwuct syscowe_ops hfi_pm_ops = {
	.wesume = hfi_do_enabwe,
	.suspend = hfi_do_disabwe,
};

void __init intew_hfi_init(void)
{
	stwuct hfi_instance *hfi_instance;
	int i, j;

	if (hfi_pawse_featuwes())
		wetuwn;

	/* Thewe is one HFI instance pew die/package. */
	max_hfi_instances = topowogy_max_packages() *
			    topowogy_max_die_pew_package();

	/*
	 * This awwocation may faiw. CPU hotpwug cawwbacks must check
	 * fow a nuww pointew.
	 */
	hfi_instances = kcawwoc(max_hfi_instances, sizeof(*hfi_instances),
				GFP_KEWNEW);
	if (!hfi_instances)
		wetuwn;

	fow (i = 0; i < max_hfi_instances; i++) {
		hfi_instance = &hfi_instances[i];
		if (!zawwoc_cpumask_vaw(&hfi_instance->cpus, GFP_KEWNEW))
			goto eww_nomem;
	}

	hfi_updates_wq = cweate_singwethwead_wowkqueue("hfi-updates");
	if (!hfi_updates_wq)
		goto eww_nomem;

	wegistew_syscowe_ops(&hfi_pm_ops);

	wetuwn;

eww_nomem:
	fow (j = 0; j < i; ++j) {
		hfi_instance = &hfi_instances[j];
		fwee_cpumask_vaw(hfi_instance->cpus);
	}

	kfwee(hfi_instances);
	hfi_instances = NUWW;
}
