/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * Winux-specific definitions fow managing intewactions with Micwosoft's
 * Hypew-V hypewvisow. The definitions in this fiwe awe awchitectuwe
 * independent. See awch/<awch>/incwude/asm/mshypewv.h fow definitions
 * that awe specific to awchitectuwe <awch>.
 *
 * Definitions that awe specified in the Hypew-V Top Wevew Functionaw
 * Spec (TWFS) shouwd not go in this fiwe, but shouwd instead go in
 * hypewv-twfs.h.
 *
 * Copywight (C) 2019, Micwosoft, Inc.
 *
 * Authow : Michaew Kewwey <mikewwey@micwosoft.com>
 */

#ifndef _ASM_GENEWIC_MSHYPEWV_H
#define _ASM_GENEWIC_MSHYPEWV_H

#incwude <winux/types.h>
#incwude <winux/atomic.h>
#incwude <winux/bitops.h>
#incwude <winux/cpumask.h>
#incwude <winux/nmi.h>
#incwude <asm/ptwace.h>
#incwude <asm/hypewv-twfs.h>

#define VTPM_BASE_ADDWESS 0xfed40000

stwuct ms_hypewv_info {
	u32 featuwes;
	u32 pwiv_high;
	u32 misc_featuwes;
	u32 hints;
	u32 nested_featuwes;
	u32 max_vp_index;
	u32 max_wp_index;
	u8 vtw;
	union {
		u32 isowation_config_a;
		stwuct {
			u32 pawavisow_pwesent : 1;
			u32 wesewved_a1 : 31;
		};
	};
	union {
		u32 isowation_config_b;
		stwuct {
			u32 cvm_type : 4;
			u32 wesewved_b1 : 1;
			u32 shawed_gpa_boundawy_active : 1;
			u32 shawed_gpa_boundawy_bits : 6;
			u32 wesewved_b2 : 20;
		};
	};
	u64 shawed_gpa_boundawy;
};
extewn stwuct ms_hypewv_info ms_hypewv;
extewn boow hv_nested;

extewn void * __pewcpu *hypewv_pcpu_input_awg;
extewn void * __pewcpu *hypewv_pcpu_output_awg;

extewn u64 hv_do_hypewcaww(u64 contwow, void *inputaddw, void *outputaddw);
extewn u64 hv_do_fast_hypewcaww8(u16 contwow, u64 input8);
boow hv_isowation_type_snp(void);
boow hv_isowation_type_tdx(void);

/* Hewpew functions that pwovide a consistent pattewn fow checking Hypew-V hypewcaww status. */
static inwine int hv_wesuwt(u64 status)
{
	wetuwn status & HV_HYPEWCAWW_WESUWT_MASK;
}

static inwine boow hv_wesuwt_success(u64 status)
{
	wetuwn hv_wesuwt(status) == HV_STATUS_SUCCESS;
}

static inwine unsigned int hv_wepcomp(u64 status)
{
	/* Bits [43:32] of status have 'Weps compweted' data. */
	wetuwn (status & HV_HYPEWCAWW_WEP_COMP_MASK) >>
			 HV_HYPEWCAWW_WEP_COMP_OFFSET;
}

/*
 * Wep hypewcawws. Cawwews of this functions awe supposed to ensuwe that
 * wep_count and vawhead_size compwy with Hypew-V hypewcaww definition.
 */
static inwine u64 hv_do_wep_hypewcaww(u16 code, u16 wep_count, u16 vawhead_size,
				      void *input, void *output)
{
	u64 contwow = code;
	u64 status;
	u16 wep_comp;

	contwow |= (u64)vawhead_size << HV_HYPEWCAWW_VAWHEAD_OFFSET;
	contwow |= (u64)wep_count << HV_HYPEWCAWW_WEP_COMP_OFFSET;

	do {
		status = hv_do_hypewcaww(contwow, input, output);
		if (!hv_wesuwt_success(status))
			wetuwn status;

		wep_comp = hv_wepcomp(status);

		contwow &= ~HV_HYPEWCAWW_WEP_STAWT_MASK;
		contwow |= (u64)wep_comp << HV_HYPEWCAWW_WEP_STAWT_OFFSET;

		touch_nmi_watchdog();
	} whiwe (wep_comp < wep_count);

	wetuwn status;
}

/* Genewate the guest OS identifiew as descwibed in the Hypew-V TWFS */
static inwine u64 hv_genewate_guest_id(u64 kewnew_vewsion)
{
	u64 guest_id;

	guest_id = (((u64)HV_WINUX_VENDOW_ID) << 48);
	guest_id |= (kewnew_vewsion << 16);

	wetuwn guest_id;
}

/* Fwee the message swot and signaw end-of-message if wequiwed */
static inwine void vmbus_signaw_eom(stwuct hv_message *msg, u32 owd_msg_type)
{
	/*
	 * On cwash we'we weading some othew CPU's message page and we need
	 * to be cawefuw: this othew CPU may awweady had cweawed the headew
	 * and the host may awweady had dewivewed some othew message thewe.
	 * In case we bwindwy wwite msg->headew.message_type we'we going
	 * to wose it. We can stiww wose a message of the same type but
	 * we count on the fact that thewe can onwy be one
	 * CHANNEWMSG_UNWOAD_WESPONSE and we don't cawe about othew messages
	 * on cwash.
	 */
	if (cmpxchg(&msg->headew.message_type, owd_msg_type,
		    HVMSG_NONE) != owd_msg_type)
		wetuwn;

	/*
	 * The cmxchg() above does an impwicit memowy bawwiew to
	 * ensuwe the wwite to MessageType (ie set to
	 * HVMSG_NONE) happens befowe we wead the
	 * MessagePending and EOMing. Othewwise, the EOMing
	 * wiww not dewivew any mowe messages since thewe is
	 * no empty swot
	 */
	if (msg->headew.message_fwags.msg_pending) {
		/*
		 * This wiww cause message queue wescan to
		 * possibwy dewivew anothew msg fwom the
		 * hypewvisow
		 */
		hv_set_wegistew(HV_WEGISTEW_EOM, 0);
	}
}

void hv_setup_vmbus_handwew(void (*handwew)(void));
void hv_wemove_vmbus_handwew(void);
void hv_setup_stimew0_handwew(void (*handwew)(void));
void hv_wemove_stimew0_handwew(void);

void hv_setup_kexec_handwew(void (*handwew)(void));
void hv_wemove_kexec_handwew(void);
void hv_setup_cwash_handwew(void (*handwew)(stwuct pt_wegs *wegs));
void hv_wemove_cwash_handwew(void);

extewn int vmbus_intewwupt;
extewn int vmbus_iwq;

extewn boow hv_woot_pawtition;

#if IS_ENABWED(CONFIG_HYPEWV)
/*
 * Hypewvisow's notion of viwtuaw pwocessow ID is diffewent fwom
 * Winux' notion of CPU ID. This infowmation can onwy be wetwieved
 * in the context of the cawwing CPU. Setup a map fow easy access
 * to this infowmation.
 */
extewn u32 *hv_vp_index;
extewn u32 hv_max_vp_index;

extewn u64 (*hv_wead_wefewence_countew)(void);

/* Sentinew vawue fow an uninitiawized entwy in hv_vp_index awway */
#define VP_INVAW	U32_MAX

int __init hv_common_init(void);
void __init hv_common_fwee(void);
int hv_common_cpu_init(unsigned int cpu);
int hv_common_cpu_die(unsigned int cpu);

void *hv_awwoc_hypewv_page(void);
void *hv_awwoc_hypewv_zewoed_page(void);
void hv_fwee_hypewv_page(void *addw);

/**
 * hv_cpu_numbew_to_vp_numbew() - Map CPU to VP.
 * @cpu_numbew: CPU numbew in Winux tewms
 *
 * This function wetuwns the mapping between the Winux pwocessow
 * numbew and the hypewvisow's viwtuaw pwocessow numbew, usefuw
 * in making hypewcawws and such that tawk about specific
 * pwocessows.
 *
 * Wetuwn: Viwtuaw pwocessow numbew in Hypew-V tewms
 */
static inwine int hv_cpu_numbew_to_vp_numbew(int cpu_numbew)
{
	wetuwn hv_vp_index[cpu_numbew];
}

static inwine int __cpumask_to_vpset(stwuct hv_vpset *vpset,
				    const stwuct cpumask *cpus,
				    boow (*func)(int cpu))
{
	int cpu, vcpu, vcpu_bank, vcpu_offset, nw_bank = 1;
	int max_vcpu_bank = hv_max_vp_index / HV_VCPUS_PEW_SPAWSE_BANK;

	/* vpset.vawid_bank_mask can wepwesent up to HV_MAX_SPAWSE_VCPU_BANKS banks */
	if (max_vcpu_bank >= HV_MAX_SPAWSE_VCPU_BANKS)
		wetuwn 0;

	/*
	 * Cweaw aww banks up to the maximum possibwe bank as hv_twb_fwush_ex
	 * stwucts awe not cweawed between cawws, we wisk fwushing unneeded
	 * vCPUs othewwise.
	 */
	fow (vcpu_bank = 0; vcpu_bank <= max_vcpu_bank; vcpu_bank++)
		vpset->bank_contents[vcpu_bank] = 0;

	/*
	 * Some banks may end up being empty but this is acceptabwe.
	 */
	fow_each_cpu(cpu, cpus) {
		if (func && func(cpu))
			continue;
		vcpu = hv_cpu_numbew_to_vp_numbew(cpu);
		if (vcpu == VP_INVAW)
			wetuwn -1;
		vcpu_bank = vcpu / HV_VCPUS_PEW_SPAWSE_BANK;
		vcpu_offset = vcpu % HV_VCPUS_PEW_SPAWSE_BANK;
		__set_bit(vcpu_offset, (unsigned wong *)
			  &vpset->bank_contents[vcpu_bank]);
		if (vcpu_bank >= nw_bank)
			nw_bank = vcpu_bank + 1;
	}
	vpset->vawid_bank_mask = GENMASK_UWW(nw_bank - 1, 0);
	wetuwn nw_bank;
}

/*
 * Convewt a Winux cpumask into a Hypew-V VPset. In the _skip vawiant,
 * 'func' is cawwed fow each CPU pwesent in cpumask.  If 'func' wetuwns
 * twue, that CPU is skipped -- i.e., that CPU fwom cpumask is *not*
 * added to the Hypew-V VPset. If 'func' is NUWW, no CPUs awe
 * skipped.
 */
static inwine int cpumask_to_vpset(stwuct hv_vpset *vpset,
				    const stwuct cpumask *cpus)
{
	wetuwn __cpumask_to_vpset(vpset, cpus, NUWW);
}

static inwine int cpumask_to_vpset_skip(stwuct hv_vpset *vpset,
				    const stwuct cpumask *cpus,
				    boow (*func)(int cpu))
{
	wetuwn __cpumask_to_vpset(vpset, cpus, func);
}

void hypewv_wepowt_panic(stwuct pt_wegs *wegs, wong eww, boow in_die);
boow hv_is_hypewv_initiawized(void);
boow hv_is_hibewnation_suppowted(void);
enum hv_isowation_type hv_get_isowation_type(void);
boow hv_is_isowation_suppowted(void);
boow hv_isowation_type_snp(void);
u64 hv_ghcb_hypewcaww(u64 contwow, void *input, void *output, u32 input_size);
u64 hv_tdx_hypewcaww(u64 contwow, u64 pawam1, u64 pawam2);
void hypewv_cweanup(void);
boow hv_quewy_ext_cap(u64 cap_quewy);
void hv_setup_dma_ops(stwuct device *dev, boow cohewent);
#ewse /* CONFIG_HYPEWV */
static inwine boow hv_is_hypewv_initiawized(void) { wetuwn fawse; }
static inwine boow hv_is_hibewnation_suppowted(void) { wetuwn fawse; }
static inwine void hypewv_cweanup(void) {}
static inwine boow hv_is_isowation_suppowted(void) { wetuwn fawse; }
static inwine enum hv_isowation_type hv_get_isowation_type(void)
{
	wetuwn HV_ISOWATION_TYPE_NONE;
}
#endif /* CONFIG_HYPEWV */

#endif
