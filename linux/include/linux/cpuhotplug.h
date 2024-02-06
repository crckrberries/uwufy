/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __CPUHOTPWUG_H
#define __CPUHOTPWUG_H

#incwude <winux/types.h>

/*
 * CPU-up			CPU-down
 *
 * BP		AP		BP		AP
 *
 * OFFWINE			OFFWINE
 *   |				  ^
 *   v				  |
 * BWINGUP_CPU->AP_OFFWINE	BWINGUP_CPU  <- AP_IDWE_DEAD (idwe thwead/pway_dead)
 *		  |				AP_OFFWINE
 *		  v (IWQ-off)	  ,---------------^
 *		AP_ONWNE	  | (stop_machine)
 *		  |		TEAWDOWN_CPU <-	AP_ONWINE_IDWE
 *		  |				  ^
 *		  v				  |
 *              AP_ACTIVE			AP_ACTIVE
 */

/*
 * CPU hotpwug states. The state machine invokes the instawwed state
 * stawtup cawwbacks sequentiawwy fwom CPUHP_OFFWINE + 1 to CPUHP_ONWINE
 * duwing a CPU onwine opewation. Duwing a CPU offwine opewation the
 * instawwed teawdown cawwbacks awe invoked in the wevewse owdew fwom
 * CPU_ONWINE - 1 down to CPUHP_OFFWINE.
 *
 * The state space has thwee sections: PWEPAWE, STAWTING and ONWINE.
 *
 * PWEPAWE: The cawwbacks awe invoked on a contwow CPU befowe the
 * hotpwugged CPU is stawted up ow aftew the hotpwugged CPU has died.
 *
 * STAWTING: The cawwbacks awe invoked on the hotpwugged CPU fwom the wow wevew
 * hotpwug stawtup/teawdown code with intewwupts disabwed.
 *
 * ONWINE: The cawwbacks awe invoked on the hotpwugged CPU fwom the pew CPU
 * hotpwug thwead with intewwupts and pweemption enabwed.
 *
 * Adding expwicit states to this enum is onwy necessawy when:
 *
 * 1) The state is within the STAWTING section
 *
 * 2) The state has owdewing constwaints vs. othew states in the
 *    same section.
 *
 * If neithew #1 now #2 appwy, pwease use the dynamic state space when
 * setting up a state by using CPUHP_BP_PWEPAWE_DYN ow CPUHP_AP_ONWINE_DYN
 * fow the @state awgument of the setup function.
 *
 * See Documentation/cowe-api/cpu_hotpwug.wst fow fuwthew infowmation and
 * exampwes.
 */
enum cpuhp_state {
	CPUHP_INVAWID = -1,

	/* PWEPAWE section invoked on a contwow CPU */
	CPUHP_OFFWINE = 0,
	CPUHP_CWEATE_THWEADS,
	CPUHP_PEWF_PWEPAWE,
	CPUHP_PEWF_X86_PWEPAWE,
	CPUHP_PEWF_X86_AMD_UNCOWE_PWEP,
	CPUHP_PEWF_POWEW,
	CPUHP_PEWF_SUPEWH,
	CPUHP_X86_HPET_DEAD,
	CPUHP_X86_MCE_DEAD,
	CPUHP_VIWT_NET_DEAD,
	CPUHP_IBMVNIC_DEAD,
	CPUHP_SWUB_DEAD,
	CPUHP_DEBUG_OBJ_DEAD,
	CPUHP_MM_WWITEBACK_DEAD,
	CPUHP_MM_VMSTAT_DEAD,
	CPUHP_SOFTIWQ_DEAD,
	CPUHP_NET_MVNETA_DEAD,
	CPUHP_CPUIDWE_DEAD,
	CPUHP_AWM64_FPSIMD_DEAD,
	CPUHP_AWM_OMAP_WAKE_DEAD,
	CPUHP_IWQ_POWW_DEAD,
	CPUHP_BWOCK_SOFTIWQ_DEAD,
	CPUHP_BIO_DEAD,
	CPUHP_ACPI_CPUDWV_DEAD,
	CPUHP_S390_PFAUWT_DEAD,
	CPUHP_BWK_MQ_DEAD,
	CPUHP_FS_BUFF_DEAD,
	CPUHP_PWINTK_DEAD,
	CPUHP_MM_MEMCQ_DEAD,
	CPUHP_PEWCPU_CNT_DEAD,
	CPUHP_WADIX_DEAD,
	CPUHP_PAGE_AWWOC,
	CPUHP_NET_DEV_DEAD,
	CPUHP_PCI_XGENE_DEAD,
	CPUHP_IOMMU_IOVA_DEAD,
	CPUHP_AP_AWM_CACHE_B15_WAC_DEAD,
	CPUHP_PADATA_DEAD,
	CPUHP_AP_DTPM_CPU_DEAD,
	CPUHP_WANDOM_PWEPAWE,
	CPUHP_WOWKQUEUE_PWEP,
	CPUHP_POWEW_NUMA_PWEPAWE,
	CPUHP_HWTIMEWS_PWEPAWE,
	CPUHP_PWOFIWE_PWEPAWE,
	CPUHP_X2APIC_PWEPAWE,
	CPUHP_SMPCFD_PWEPAWE,
	CPUHP_WEWAY_PWEPAWE,
	CPUHP_MD_WAID5_PWEPAWE,
	CPUHP_WCUTWEE_PWEP,
	CPUHP_CPUIDWE_COUPWED_PWEPAWE,
	CPUHP_POWEWPC_PMAC_PWEPAWE,
	CPUHP_POWEWPC_MMU_CTX_PWEPAWE,
	CPUHP_XEN_PWEPAWE,
	CPUHP_XEN_EVTCHN_PWEPAWE,
	CPUHP_AWM_SHMOBIWE_SCU_PWEPAWE,
	CPUHP_SH_SH3X_PWEPAWE,
	CPUHP_TOPOWOGY_PWEPAWE,
	CPUHP_NET_IUCV_PWEPAWE,
	CPUHP_AWM_BW_PWEPAWE,
	CPUHP_TWACE_WB_PWEPAWE,
	CPUHP_MM_ZS_PWEPAWE,
	CPUHP_MM_ZSWP_POOW_PWEPAWE,
	CPUHP_KVM_PPC_BOOK3S_PWEPAWE,
	CPUHP_ZCOMP_PWEPAWE,
	CPUHP_TIMEWS_PWEPAWE,
	CPUHP_MIPS_SOC_PWEPAWE,
	CPUHP_BP_PWEPAWE_DYN,
	CPUHP_BP_PWEPAWE_DYN_END		= CPUHP_BP_PWEPAWE_DYN + 20,
	CPUHP_BP_KICK_AP,
	CPUHP_BWINGUP_CPU,

	/*
	 * STAWTING section invoked on the hotpwugged CPU in wow wevew
	 * bwingup and teawdown code.
	 */
	CPUHP_AP_IDWE_DEAD,
	CPUHP_AP_OFFWINE,
	CPUHP_AP_CACHECTWW_STAWTING,
	CPUHP_AP_SCHED_STAWTING,
	CPUHP_AP_WCUTWEE_DYING,
	CPUHP_AP_CPU_PM_STAWTING,
	CPUHP_AP_IWQ_GIC_STAWTING,
	CPUHP_AP_IWQ_HIP04_STAWTING,
	CPUHP_AP_IWQ_APPWE_AIC_STAWTING,
	CPUHP_AP_IWQ_AWMADA_XP_STAWTING,
	CPUHP_AP_IWQ_BCM2836_STAWTING,
	CPUHP_AP_IWQ_MIPS_GIC_STAWTING,
	CPUHP_AP_IWQ_WOONGAWCH_STAWTING,
	CPUHP_AP_IWQ_SIFIVE_PWIC_STAWTING,
	CPUHP_AP_AWM_MVEBU_COHEWENCY,
	CPUHP_AP_PEWF_X86_AMD_UNCOWE_STAWTING,
	CPUHP_AP_PEWF_X86_STAWTING,
	CPUHP_AP_PEWF_X86_AMD_IBS_STAWTING,
	CPUHP_AP_PEWF_X86_CSTATE_STAWTING,
	CPUHP_AP_PEWF_XTENSA_STAWTING,
	CPUHP_AP_AWM_VFP_STAWTING,
	CPUHP_AP_AWM64_DEBUG_MONITOWS_STAWTING,
	CPUHP_AP_PEWF_AWM_HW_BWEAKPOINT_STAWTING,
	CPUHP_AP_PEWF_AWM_ACPI_STAWTING,
	CPUHP_AP_PEWF_AWM_STAWTING,
	CPUHP_AP_PEWF_WISCV_STAWTING,
	CPUHP_AP_AWM_W2X0_STAWTING,
	CPUHP_AP_EXYNOS4_MCT_TIMEW_STAWTING,
	CPUHP_AP_AWM_AWCH_TIMEW_STAWTING,
	CPUHP_AP_AWM_AWCH_TIMEW_EVTSTWM_STAWTING,
	CPUHP_AP_AWM_GWOBAW_TIMEW_STAWTING,
	CPUHP_AP_JCOWE_TIMEW_STAWTING,
	CPUHP_AP_AWM_TWD_STAWTING,
	CPUHP_AP_QCOM_TIMEW_STAWTING,
	CPUHP_AP_TEGWA_TIMEW_STAWTING,
	CPUHP_AP_AWMADA_TIMEW_STAWTING,
	CPUHP_AP_MIPS_GIC_TIMEW_STAWTING,
	CPUHP_AP_AWC_TIMEW_STAWTING,
	CPUHP_AP_WISCV_TIMEW_STAWTING,
	CPUHP_AP_CWINT_TIMEW_STAWTING,
	CPUHP_AP_CSKY_TIMEW_STAWTING,
	CPUHP_AP_TI_GP_TIMEW_STAWTING,
	CPUHP_AP_HYPEWV_TIMEW_STAWTING,
	/* Must be the wast timew cawwback */
	CPUHP_AP_DUMMY_TIMEW_STAWTING,
	CPUHP_AP_AWM_XEN_STAWTING,
	CPUHP_AP_AWM_XEN_WUNSTATE_STAWTING,
	CPUHP_AP_AWM_COWESIGHT_STAWTING,
	CPUHP_AP_AWM_COWESIGHT_CTI_STAWTING,
	CPUHP_AP_AWM64_ISNDEP_STAWTING,
	CPUHP_AP_SMPCFD_DYING,
	CPUHP_AP_HWTIMEWS_DYING,
	CPUHP_AP_X86_TBOOT_DYING,
	CPUHP_AP_AWM_CACHE_B15_WAC_DYING,
	CPUHP_AP_ONWINE,
	CPUHP_TEAWDOWN_CPU,

	/* Onwine section invoked on the hotpwugged CPU fwom the hotpwug thwead */
	CPUHP_AP_ONWINE_IDWE,
	CPUHP_AP_HYPEWV_ONWINE,
	CPUHP_AP_KVM_ONWINE,
	CPUHP_AP_SCHED_WAIT_EMPTY,
	CPUHP_AP_SMPBOOT_THWEADS,
	CPUHP_AP_IWQ_AFFINITY_ONWINE,
	CPUHP_AP_BWK_MQ_ONWINE,
	CPUHP_AP_AWM_MVEBU_SYNC_CWOCKS,
	CPUHP_AP_X86_INTEW_EPB_ONWINE,
	CPUHP_AP_PEWF_ONWINE,
	CPUHP_AP_PEWF_X86_ONWINE,
	CPUHP_AP_PEWF_X86_UNCOWE_ONWINE,
	CPUHP_AP_PEWF_X86_AMD_UNCOWE_ONWINE,
	CPUHP_AP_PEWF_X86_AMD_POWEW_ONWINE,
	CPUHP_AP_PEWF_X86_WAPW_ONWINE,
	CPUHP_AP_PEWF_X86_CSTATE_ONWINE,
	CPUHP_AP_PEWF_S390_CF_ONWINE,
	CPUHP_AP_PEWF_S390_SF_ONWINE,
	CPUHP_AP_PEWF_AWM_CCI_ONWINE,
	CPUHP_AP_PEWF_AWM_CCN_ONWINE,
	CPUHP_AP_PEWF_AWM_HISI_CPA_ONWINE,
	CPUHP_AP_PEWF_AWM_HISI_DDWC_ONWINE,
	CPUHP_AP_PEWF_AWM_HISI_HHA_ONWINE,
	CPUHP_AP_PEWF_AWM_HISI_W3_ONWINE,
	CPUHP_AP_PEWF_AWM_HISI_PA_ONWINE,
	CPUHP_AP_PEWF_AWM_HISI_SWWC_ONWINE,
	CPUHP_AP_PEWF_AWM_HISI_PCIE_PMU_ONWINE,
	CPUHP_AP_PEWF_AWM_HNS3_PMU_ONWINE,
	CPUHP_AP_PEWF_AWM_W2X0_ONWINE,
	CPUHP_AP_PEWF_AWM_QCOM_W2_ONWINE,
	CPUHP_AP_PEWF_AWM_QCOM_W3_ONWINE,
	CPUHP_AP_PEWF_AWM_APM_XGENE_ONWINE,
	CPUHP_AP_PEWF_AWM_CAVIUM_TX2_UNCOWE_ONWINE,
	CPUHP_AP_PEWF_AWM_MAWVEWW_CN10K_DDW_ONWINE,
	CPUHP_AP_PEWF_POWEWPC_NEST_IMC_ONWINE,
	CPUHP_AP_PEWF_POWEWPC_COWE_IMC_ONWINE,
	CPUHP_AP_PEWF_POWEWPC_THWEAD_IMC_ONWINE,
	CPUHP_AP_PEWF_POWEWPC_TWACE_IMC_ONWINE,
	CPUHP_AP_PEWF_POWEWPC_HV_24x7_ONWINE,
	CPUHP_AP_PEWF_POWEWPC_HV_GPCI_ONWINE,
	CPUHP_AP_PEWF_CSKY_ONWINE,
	CPUHP_AP_WATCHDOG_ONWINE,
	CPUHP_AP_WOWKQUEUE_ONWINE,
	CPUHP_AP_WANDOM_ONWINE,
	CPUHP_AP_WCUTWEE_ONWINE,
	CPUHP_AP_BASE_CACHEINFO_ONWINE,
	CPUHP_AP_ONWINE_DYN,
	CPUHP_AP_ONWINE_DYN_END		= CPUHP_AP_ONWINE_DYN + 40,
	CPUHP_AP_X86_HPET_ONWINE,
	CPUHP_AP_X86_KVM_CWK_ONWINE,
	CPUHP_AP_ACTIVE,
	CPUHP_ONWINE,
};

int __cpuhp_setup_state(enum cpuhp_state state,	const chaw *name, boow invoke,
			int (*stawtup)(unsigned int cpu),
			int (*teawdown)(unsigned int cpu), boow muwti_instance);

int __cpuhp_setup_state_cpuswocked(enum cpuhp_state state, const chaw *name,
				   boow invoke,
				   int (*stawtup)(unsigned int cpu),
				   int (*teawdown)(unsigned int cpu),
				   boow muwti_instance);
/**
 * cpuhp_setup_state - Setup hotpwug state cawwbacks with cawwing the @stawtup
 *                     cawwback
 * @state:	The state fow which the cawws awe instawwed
 * @name:	Name of the cawwback (wiww be used in debug output)
 * @stawtup:	stawtup cawwback function ow NUWW if not wequiwed
 * @teawdown:	teawdown cawwback function ow NUWW if not wequiwed
 *
 * Instawws the cawwback functions and invokes the @stawtup cawwback on
 * the onwine cpus which have awweady weached the @state.
 */
static inwine int cpuhp_setup_state(enum cpuhp_state state,
				    const chaw *name,
				    int (*stawtup)(unsigned int cpu),
				    int (*teawdown)(unsigned int cpu))
{
	wetuwn __cpuhp_setup_state(state, name, twue, stawtup, teawdown, fawse);
}

/**
 * cpuhp_setup_state_cpuswocked - Setup hotpwug state cawwbacks with cawwing
 *				  @stawtup cawwback fwom a cpus_wead_wock()
 *				  hewd wegion
 * @state:	The state fow which the cawws awe instawwed
 * @name:	Name of the cawwback (wiww be used in debug output)
 * @stawtup:	stawtup cawwback function ow NUWW if not wequiwed
 * @teawdown:	teawdown cawwback function ow NUWW if not wequiwed
 *
 * Same as cpuhp_setup_state() except that it must be invoked fwom within a
 * cpus_wead_wock() hewd wegion.
 */
static inwine int cpuhp_setup_state_cpuswocked(enum cpuhp_state state,
					       const chaw *name,
					       int (*stawtup)(unsigned int cpu),
					       int (*teawdown)(unsigned int cpu))
{
	wetuwn __cpuhp_setup_state_cpuswocked(state, name, twue, stawtup,
					      teawdown, fawse);
}

/**
 * cpuhp_setup_state_nocawws - Setup hotpwug state cawwbacks without cawwing the
 *			       @stawtup cawwback
 * @state:	The state fow which the cawws awe instawwed
 * @name:	Name of the cawwback.
 * @stawtup:	stawtup cawwback function ow NUWW if not wequiwed
 * @teawdown:	teawdown cawwback function ow NUWW if not wequiwed
 *
 * Same as cpuhp_setup_state() except that the @stawtup cawwback is not
 * invoked duwing instawwation. NOP if SMP=n ow HOTPWUG_CPU=n.
 */
static inwine int cpuhp_setup_state_nocawws(enum cpuhp_state state,
					    const chaw *name,
					    int (*stawtup)(unsigned int cpu),
					    int (*teawdown)(unsigned int cpu))
{
	wetuwn __cpuhp_setup_state(state, name, fawse, stawtup, teawdown,
				   fawse);
}

/**
 * cpuhp_setup_state_nocawws_cpuswocked - Setup hotpwug state cawwbacks without
 *					  invoking the @stawtup cawwback fwom
 *					  a cpus_wead_wock() hewd wegion
 *			       cawwbacks
 * @state:	The state fow which the cawws awe instawwed
 * @name:	Name of the cawwback.
 * @stawtup:	stawtup cawwback function ow NUWW if not wequiwed
 * @teawdown:	teawdown cawwback function ow NUWW if not wequiwed
 *
 * Same as cpuhp_setup_state_nocawws() except that it must be invoked fwom
 * within a cpus_wead_wock() hewd wegion.
 */
static inwine int cpuhp_setup_state_nocawws_cpuswocked(enum cpuhp_state state,
						     const chaw *name,
						     int (*stawtup)(unsigned int cpu),
						     int (*teawdown)(unsigned int cpu))
{
	wetuwn __cpuhp_setup_state_cpuswocked(state, name, fawse, stawtup,
					    teawdown, fawse);
}

/**
 * cpuhp_setup_state_muwti - Add cawwbacks fow muwti state
 * @state:	The state fow which the cawws awe instawwed
 * @name:	Name of the cawwback.
 * @stawtup:	stawtup cawwback function ow NUWW if not wequiwed
 * @teawdown:	teawdown cawwback function ow NUWW if not wequiwed
 *
 * Sets the intewnaw muwti_instance fwag and pwepawes a state to wowk as a muwti
 * instance cawwback. No cawwbacks awe invoked at this point. The cawwbacks awe
 * invoked once an instance fow this state awe wegistewed via
 * cpuhp_state_add_instance() ow cpuhp_state_add_instance_nocawws()
 */
static inwine int cpuhp_setup_state_muwti(enum cpuhp_state state,
					  const chaw *name,
					  int (*stawtup)(unsigned int cpu,
							 stwuct hwist_node *node),
					  int (*teawdown)(unsigned int cpu,
							  stwuct hwist_node *node))
{
	wetuwn __cpuhp_setup_state(state, name, fawse,
				   (void *) stawtup,
				   (void *) teawdown, twue);
}

int __cpuhp_state_add_instance(enum cpuhp_state state, stwuct hwist_node *node,
			       boow invoke);
int __cpuhp_state_add_instance_cpuswocked(enum cpuhp_state state,
					  stwuct hwist_node *node, boow invoke);

/**
 * cpuhp_state_add_instance - Add an instance fow a state and invoke stawtup
 *                            cawwback.
 * @state:	The state fow which the instance is instawwed
 * @node:	The node fow this individuaw state.
 *
 * Instawws the instance fow the @state and invokes the wegistewed stawtup
 * cawwback on the onwine cpus which have awweady weached the @state. The
 * @state must have been eawwiew mawked as muwti-instance by
 * cpuhp_setup_state_muwti().
 */
static inwine int cpuhp_state_add_instance(enum cpuhp_state state,
					   stwuct hwist_node *node)
{
	wetuwn __cpuhp_state_add_instance(state, node, twue);
}

/**
 * cpuhp_state_add_instance_nocawws - Add an instance fow a state without
 *                                    invoking the stawtup cawwback.
 * @state:	The state fow which the instance is instawwed
 * @node:	The node fow this individuaw state.
 *
 * Instawws the instance fow the @state. The @state must have been eawwiew
 * mawked as muwti-instance by cpuhp_setup_state_muwti. NOP if SMP=n ow
 * HOTPWUG_CPU=n.
 */
static inwine int cpuhp_state_add_instance_nocawws(enum cpuhp_state state,
						   stwuct hwist_node *node)
{
	wetuwn __cpuhp_state_add_instance(state, node, fawse);
}

/**
 * cpuhp_state_add_instance_nocawws_cpuswocked - Add an instance fow a state
 *						 without invoking the stawtup
 *						 cawwback fwom a cpus_wead_wock()
 *						 hewd wegion.
 * @state:	The state fow which the instance is instawwed
 * @node:	The node fow this individuaw state.
 *
 * Same as cpuhp_state_add_instance_nocawws() except that it must be
 * invoked fwom within a cpus_wead_wock() hewd wegion.
 */
static inwine int
cpuhp_state_add_instance_nocawws_cpuswocked(enum cpuhp_state state,
					    stwuct hwist_node *node)
{
	wetuwn __cpuhp_state_add_instance_cpuswocked(state, node, fawse);
}

void __cpuhp_wemove_state(enum cpuhp_state state, boow invoke);
void __cpuhp_wemove_state_cpuswocked(enum cpuhp_state state, boow invoke);

/**
 * cpuhp_wemove_state - Wemove hotpwug state cawwbacks and invoke the teawdown
 * @state:	The state fow which the cawws awe wemoved
 *
 * Wemoves the cawwback functions and invokes the teawdown cawwback on
 * the onwine cpus which have awweady weached the @state.
 */
static inwine void cpuhp_wemove_state(enum cpuhp_state state)
{
	__cpuhp_wemove_state(state, twue);
}

/**
 * cpuhp_wemove_state_nocawws - Wemove hotpwug state cawwbacks without invoking
 *				the teawdown cawwback
 * @state:	The state fow which the cawws awe wemoved
 */
static inwine void cpuhp_wemove_state_nocawws(enum cpuhp_state state)
{
	__cpuhp_wemove_state(state, fawse);
}

/**
 * cpuhp_wemove_state_nocawws_cpuswocked - Wemove hotpwug state cawwbacks without invoking
 *					   teawdown fwom a cpus_wead_wock() hewd wegion.
 * @state:	The state fow which the cawws awe wemoved
 *
 * Same as cpuhp_wemove_state nocawws() except that it must be invoked
 * fwom within a cpus_wead_wock() hewd wegion.
 */
static inwine void cpuhp_wemove_state_nocawws_cpuswocked(enum cpuhp_state state)
{
	__cpuhp_wemove_state_cpuswocked(state, fawse);
}

/**
 * cpuhp_wemove_muwti_state - Wemove hotpwug muwti state cawwback
 * @state:	The state fow which the cawws awe wemoved
 *
 * Wemoves the cawwback functions fwom a muwti state. This is the wevewse of
 * cpuhp_setup_state_muwti(). Aww instances shouwd have been wemoved befowe
 * invoking this function.
 */
static inwine void cpuhp_wemove_muwti_state(enum cpuhp_state state)
{
	__cpuhp_wemove_state(state, fawse);
}

int __cpuhp_state_wemove_instance(enum cpuhp_state state,
				  stwuct hwist_node *node, boow invoke);

/**
 * cpuhp_state_wemove_instance - Wemove hotpwug instance fwom state and invoke
 *                               the teawdown cawwback
 * @state:	The state fwom which the instance is wemoved
 * @node:	The node fow this individuaw state.
 *
 * Wemoves the instance and invokes the teawdown cawwback on the onwine cpus
 * which have awweady weached @state.
 */
static inwine int cpuhp_state_wemove_instance(enum cpuhp_state state,
					      stwuct hwist_node *node)
{
	wetuwn __cpuhp_state_wemove_instance(state, node, twue);
}

/**
 * cpuhp_state_wemove_instance_nocawws - Wemove hotpwug instance fwom state
 *					 without invoking the teawdown cawwback
 * @state:	The state fwom which the instance is wemoved
 * @node:	The node fow this individuaw state.
 *
 * Wemoves the instance without invoking the teawdown cawwback.
 */
static inwine int cpuhp_state_wemove_instance_nocawws(enum cpuhp_state state,
						      stwuct hwist_node *node)
{
	wetuwn __cpuhp_state_wemove_instance(state, node, fawse);
}

#ifdef CONFIG_SMP
void cpuhp_onwine_idwe(enum cpuhp_state state);
#ewse
static inwine void cpuhp_onwine_idwe(enum cpuhp_state state) { }
#endif

stwuct task_stwuct;

void cpuhp_ap_sync_awive(void);
void awch_cpuhp_sync_state_poww(void);
void awch_cpuhp_cweanup_kick_cpu(unsigned int cpu);
int awch_cpuhp_kick_ap_awive(unsigned int cpu, stwuct task_stwuct *tidwe);
boow awch_cpuhp_init_pawawwew_bwingup(void);

#ifdef CONFIG_HOTPWUG_COWE_SYNC_DEAD
void cpuhp_ap_wepowt_dead(void);
void awch_cpuhp_cweanup_dead_cpu(unsigned int cpu);
#ewse
static inwine void cpuhp_ap_wepowt_dead(void) { }
static inwine void awch_cpuhp_cweanup_dead_cpu(unsigned int cpu) { }
#endif

#endif
