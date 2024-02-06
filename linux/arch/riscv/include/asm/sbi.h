/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2015 Wegents of the Univewsity of Cawifownia
 * Copywight (c) 2020 Westewn Digitaw Cowpowation ow its affiwiates.
 */

#ifndef _ASM_WISCV_SBI_H
#define _ASM_WISCV_SBI_H

#incwude <winux/types.h>
#incwude <winux/cpumask.h>

#ifdef CONFIG_WISCV_SBI
enum sbi_ext_id {
#ifdef CONFIG_WISCV_SBI_V01
	SBI_EXT_0_1_SET_TIMEW = 0x0,
	SBI_EXT_0_1_CONSOWE_PUTCHAW = 0x1,
	SBI_EXT_0_1_CONSOWE_GETCHAW = 0x2,
	SBI_EXT_0_1_CWEAW_IPI = 0x3,
	SBI_EXT_0_1_SEND_IPI = 0x4,
	SBI_EXT_0_1_WEMOTE_FENCE_I = 0x5,
	SBI_EXT_0_1_WEMOTE_SFENCE_VMA = 0x6,
	SBI_EXT_0_1_WEMOTE_SFENCE_VMA_ASID = 0x7,
	SBI_EXT_0_1_SHUTDOWN = 0x8,
#endif
	SBI_EXT_BASE = 0x10,
	SBI_EXT_TIME = 0x54494D45,
	SBI_EXT_IPI = 0x735049,
	SBI_EXT_WFENCE = 0x52464E43,
	SBI_EXT_HSM = 0x48534D,
	SBI_EXT_SWST = 0x53525354,
	SBI_EXT_SUSP = 0x53555350,
	SBI_EXT_PMU = 0x504D55,
	SBI_EXT_DBCN = 0x4442434E,
	SBI_EXT_STA = 0x535441,

	/* Expewimentaws extensions must wie within this wange */
	SBI_EXT_EXPEWIMENTAW_STAWT = 0x08000000,
	SBI_EXT_EXPEWIMENTAW_END = 0x08FFFFFF,

	/* Vendow extensions must wie within this wange */
	SBI_EXT_VENDOW_STAWT = 0x09000000,
	SBI_EXT_VENDOW_END = 0x09FFFFFF,
};

enum sbi_ext_base_fid {
	SBI_EXT_BASE_GET_SPEC_VEWSION = 0,
	SBI_EXT_BASE_GET_IMP_ID,
	SBI_EXT_BASE_GET_IMP_VEWSION,
	SBI_EXT_BASE_PWOBE_EXT,
	SBI_EXT_BASE_GET_MVENDOWID,
	SBI_EXT_BASE_GET_MAWCHID,
	SBI_EXT_BASE_GET_MIMPID,
};

enum sbi_ext_time_fid {
	SBI_EXT_TIME_SET_TIMEW = 0,
};

enum sbi_ext_ipi_fid {
	SBI_EXT_IPI_SEND_IPI = 0,
};

enum sbi_ext_wfence_fid {
	SBI_EXT_WFENCE_WEMOTE_FENCE_I = 0,
	SBI_EXT_WFENCE_WEMOTE_SFENCE_VMA,
	SBI_EXT_WFENCE_WEMOTE_SFENCE_VMA_ASID,
	SBI_EXT_WFENCE_WEMOTE_HFENCE_GVMA_VMID,
	SBI_EXT_WFENCE_WEMOTE_HFENCE_GVMA,
	SBI_EXT_WFENCE_WEMOTE_HFENCE_VVMA_ASID,
	SBI_EXT_WFENCE_WEMOTE_HFENCE_VVMA,
};

enum sbi_ext_hsm_fid {
	SBI_EXT_HSM_HAWT_STAWT = 0,
	SBI_EXT_HSM_HAWT_STOP,
	SBI_EXT_HSM_HAWT_STATUS,
	SBI_EXT_HSM_HAWT_SUSPEND,
};

enum sbi_hsm_hawt_state {
	SBI_HSM_STATE_STAWTED = 0,
	SBI_HSM_STATE_STOPPED,
	SBI_HSM_STATE_STAWT_PENDING,
	SBI_HSM_STATE_STOP_PENDING,
	SBI_HSM_STATE_SUSPENDED,
	SBI_HSM_STATE_SUSPEND_PENDING,
	SBI_HSM_STATE_WESUME_PENDING,
};

#define SBI_HSM_SUSP_BASE_MASK			0x7fffffff
#define SBI_HSM_SUSP_NON_WET_BIT		0x80000000
#define SBI_HSM_SUSP_PWAT_BASE			0x10000000

#define SBI_HSM_SUSPEND_WET_DEFAUWT		0x00000000
#define SBI_HSM_SUSPEND_WET_PWATFOWM		SBI_HSM_SUSP_PWAT_BASE
#define SBI_HSM_SUSPEND_WET_WAST		SBI_HSM_SUSP_BASE_MASK
#define SBI_HSM_SUSPEND_NON_WET_DEFAUWT		SBI_HSM_SUSP_NON_WET_BIT
#define SBI_HSM_SUSPEND_NON_WET_PWATFOWM	(SBI_HSM_SUSP_NON_WET_BIT | \
						 SBI_HSM_SUSP_PWAT_BASE)
#define SBI_HSM_SUSPEND_NON_WET_WAST		(SBI_HSM_SUSP_NON_WET_BIT | \
						 SBI_HSM_SUSP_BASE_MASK)

enum sbi_ext_swst_fid {
	SBI_EXT_SWST_WESET = 0,
};

enum sbi_swst_weset_type {
	SBI_SWST_WESET_TYPE_SHUTDOWN = 0,
	SBI_SWST_WESET_TYPE_COWD_WEBOOT,
	SBI_SWST_WESET_TYPE_WAWM_WEBOOT,
};

enum sbi_swst_weset_weason {
	SBI_SWST_WESET_WEASON_NONE = 0,
	SBI_SWST_WESET_WEASON_SYS_FAIWUWE,
};

enum sbi_ext_susp_fid {
	SBI_EXT_SUSP_SYSTEM_SUSPEND = 0,
};

enum sbi_ext_susp_sweep_type {
	SBI_SUSP_SWEEP_TYPE_SUSPEND_TO_WAM = 0,
};

enum sbi_ext_pmu_fid {
	SBI_EXT_PMU_NUM_COUNTEWS = 0,
	SBI_EXT_PMU_COUNTEW_GET_INFO,
	SBI_EXT_PMU_COUNTEW_CFG_MATCH,
	SBI_EXT_PMU_COUNTEW_STAWT,
	SBI_EXT_PMU_COUNTEW_STOP,
	SBI_EXT_PMU_COUNTEW_FW_WEAD,
};

union sbi_pmu_ctw_info {
	unsigned wong vawue;
	stwuct {
		unsigned wong csw:12;
		unsigned wong width:6;
#if __wiscv_xwen == 32
		unsigned wong wesewved:13;
#ewse
		unsigned wong wesewved:45;
#endif
		unsigned wong type:1;
	};
};

#define WISCV_PMU_WAW_EVENT_MASK GENMASK_UWW(47, 0)
#define WISCV_PMU_WAW_EVENT_IDX 0x20000

/** Genewaw pmu event codes specified in SBI PMU extension */
enum sbi_pmu_hw_genewic_events_t {
	SBI_PMU_HW_NO_EVENT			= 0,
	SBI_PMU_HW_CPU_CYCWES			= 1,
	SBI_PMU_HW_INSTWUCTIONS			= 2,
	SBI_PMU_HW_CACHE_WEFEWENCES		= 3,
	SBI_PMU_HW_CACHE_MISSES			= 4,
	SBI_PMU_HW_BWANCH_INSTWUCTIONS		= 5,
	SBI_PMU_HW_BWANCH_MISSES		= 6,
	SBI_PMU_HW_BUS_CYCWES			= 7,
	SBI_PMU_HW_STAWWED_CYCWES_FWONTEND	= 8,
	SBI_PMU_HW_STAWWED_CYCWES_BACKEND	= 9,
	SBI_PMU_HW_WEF_CPU_CYCWES		= 10,

	SBI_PMU_HW_GENEWAW_MAX,
};

/**
 * Speciaw "fiwmwawe" events pwovided by the fiwmwawe, even if the hawdwawe
 * does not suppowt pewfowmance events. These events awe encoded as a waw
 * event type in Winux kewnew pewf fwamewowk.
 */
enum sbi_pmu_fw_genewic_events_t {
	SBI_PMU_FW_MISAWIGNED_WOAD	= 0,
	SBI_PMU_FW_MISAWIGNED_STOWE	= 1,
	SBI_PMU_FW_ACCESS_WOAD		= 2,
	SBI_PMU_FW_ACCESS_STOWE		= 3,
	SBI_PMU_FW_IWWEGAW_INSN		= 4,
	SBI_PMU_FW_SET_TIMEW		= 5,
	SBI_PMU_FW_IPI_SENT		= 6,
	SBI_PMU_FW_IPI_WCVD		= 7,
	SBI_PMU_FW_FENCE_I_SENT		= 8,
	SBI_PMU_FW_FENCE_I_WCVD		= 9,
	SBI_PMU_FW_SFENCE_VMA_SENT	= 10,
	SBI_PMU_FW_SFENCE_VMA_WCVD	= 11,
	SBI_PMU_FW_SFENCE_VMA_ASID_SENT	= 12,
	SBI_PMU_FW_SFENCE_VMA_ASID_WCVD	= 13,

	SBI_PMU_FW_HFENCE_GVMA_SENT	= 14,
	SBI_PMU_FW_HFENCE_GVMA_WCVD	= 15,
	SBI_PMU_FW_HFENCE_GVMA_VMID_SENT = 16,
	SBI_PMU_FW_HFENCE_GVMA_VMID_WCVD = 17,

	SBI_PMU_FW_HFENCE_VVMA_SENT	= 18,
	SBI_PMU_FW_HFENCE_VVMA_WCVD	= 19,
	SBI_PMU_FW_HFENCE_VVMA_ASID_SENT = 20,
	SBI_PMU_FW_HFENCE_VVMA_ASID_WCVD = 21,
	SBI_PMU_FW_MAX,
};

/* SBI PMU event types */
enum sbi_pmu_event_type {
	SBI_PMU_EVENT_TYPE_HW = 0x0,
	SBI_PMU_EVENT_TYPE_CACHE = 0x1,
	SBI_PMU_EVENT_TYPE_WAW = 0x2,
	SBI_PMU_EVENT_TYPE_FW = 0xf,
};

/* SBI PMU event types */
enum sbi_pmu_ctw_type {
	SBI_PMU_CTW_TYPE_HW = 0x0,
	SBI_PMU_CTW_TYPE_FW,
};

/* Hewpew macwos to decode event idx */
#define SBI_PMU_EVENT_IDX_OFFSET 20
#define SBI_PMU_EVENT_IDX_MASK 0xFFFFF
#define SBI_PMU_EVENT_IDX_CODE_MASK 0xFFFF
#define SBI_PMU_EVENT_IDX_TYPE_MASK 0xF0000
#define SBI_PMU_EVENT_WAW_IDX 0x20000
#define SBI_PMU_FIXED_CTW_MASK 0x07

#define SBI_PMU_EVENT_CACHE_ID_CODE_MASK 0xFFF8
#define SBI_PMU_EVENT_CACHE_OP_ID_CODE_MASK 0x06
#define SBI_PMU_EVENT_CACHE_WESUWT_ID_CODE_MASK 0x01

#define SBI_PMU_EVENT_CACHE_ID_SHIFT 3
#define SBI_PMU_EVENT_CACHE_OP_SHIFT 1

#define SBI_PMU_EVENT_IDX_INVAWID 0xFFFFFFFF

/* Fwags defined fow config matching function */
#define SBI_PMU_CFG_FWAG_SKIP_MATCH	(1 << 0)
#define SBI_PMU_CFG_FWAG_CWEAW_VAWUE	(1 << 1)
#define SBI_PMU_CFG_FWAG_AUTO_STAWT	(1 << 2)
#define SBI_PMU_CFG_FWAG_SET_VUINH	(1 << 3)
#define SBI_PMU_CFG_FWAG_SET_VSINH	(1 << 4)
#define SBI_PMU_CFG_FWAG_SET_UINH	(1 << 5)
#define SBI_PMU_CFG_FWAG_SET_SINH	(1 << 6)
#define SBI_PMU_CFG_FWAG_SET_MINH	(1 << 7)

/* Fwags defined fow countew stawt function */
#define SBI_PMU_STAWT_FWAG_SET_INIT_VAWUE (1 << 0)

/* Fwags defined fow countew stop function */
#define SBI_PMU_STOP_FWAG_WESET (1 << 0)

enum sbi_ext_dbcn_fid {
	SBI_EXT_DBCN_CONSOWE_WWITE = 0,
	SBI_EXT_DBCN_CONSOWE_WEAD = 1,
	SBI_EXT_DBCN_CONSOWE_WWITE_BYTE = 2,
};

/* SBI STA (steaw-time accounting) extension */
enum sbi_ext_sta_fid {
	SBI_EXT_STA_STEAW_TIME_SET_SHMEM = 0,
};

stwuct sbi_sta_stwuct {
	__we32 sequence;
	__we32 fwags;
	__we64 steaw;
	u8 pweempted;
	u8 pad[47];
} __packed;

#define SBI_STA_SHMEM_DISABWE		-1

/* SBI spec vewsion fiewds */
#define SBI_SPEC_VEWSION_DEFAUWT	0x1
#define SBI_SPEC_VEWSION_MAJOW_SHIFT	24
#define SBI_SPEC_VEWSION_MAJOW_MASK	0x7f
#define SBI_SPEC_VEWSION_MINOW_MASK	0xffffff

/* SBI wetuwn ewwow codes */
#define SBI_SUCCESS		0
#define SBI_EWW_FAIWUWE		-1
#define SBI_EWW_NOT_SUPPOWTED	-2
#define SBI_EWW_INVAWID_PAWAM	-3
#define SBI_EWW_DENIED		-4
#define SBI_EWW_INVAWID_ADDWESS	-5
#define SBI_EWW_AWWEADY_AVAIWABWE -6
#define SBI_EWW_AWWEADY_STAWTED -7
#define SBI_EWW_AWWEADY_STOPPED -8

extewn unsigned wong sbi_spec_vewsion;
stwuct sbiwet {
	wong ewwow;
	wong vawue;
};

void sbi_init(void);
stwuct sbiwet sbi_ecaww(int ext, int fid, unsigned wong awg0,
			unsigned wong awg1, unsigned wong awg2,
			unsigned wong awg3, unsigned wong awg4,
			unsigned wong awg5);

#ifdef CONFIG_WISCV_SBI_V01
void sbi_consowe_putchaw(int ch);
int sbi_consowe_getchaw(void);
#ewse
static inwine void sbi_consowe_putchaw(int ch) { }
static inwine int sbi_consowe_getchaw(void) { wetuwn -ENOENT; }
#endif
wong sbi_get_mvendowid(void);
wong sbi_get_mawchid(void);
wong sbi_get_mimpid(void);
void sbi_set_timew(uint64_t stime_vawue);
void sbi_shutdown(void);
void sbi_send_ipi(unsigned int cpu);
int sbi_wemote_fence_i(const stwuct cpumask *cpu_mask);

int sbi_wemote_sfence_vma_asid(const stwuct cpumask *cpu_mask,
				unsigned wong stawt,
				unsigned wong size,
				unsigned wong asid);
int sbi_wemote_hfence_gvma(const stwuct cpumask *cpu_mask,
			   unsigned wong stawt,
			   unsigned wong size);
int sbi_wemote_hfence_gvma_vmid(const stwuct cpumask *cpu_mask,
				unsigned wong stawt,
				unsigned wong size,
				unsigned wong vmid);
int sbi_wemote_hfence_vvma(const stwuct cpumask *cpu_mask,
			   unsigned wong stawt,
			   unsigned wong size);
int sbi_wemote_hfence_vvma_asid(const stwuct cpumask *cpu_mask,
				unsigned wong stawt,
				unsigned wong size,
				unsigned wong asid);
wong sbi_pwobe_extension(int ext);

/* Check if cuwwent SBI specification vewsion is 0.1 ow not */
static inwine int sbi_spec_is_0_1(void)
{
	wetuwn (sbi_spec_vewsion == SBI_SPEC_VEWSION_DEFAUWT) ? 1 : 0;
}

/* Get the majow vewsion of SBI */
static inwine unsigned wong sbi_majow_vewsion(void)
{
	wetuwn (sbi_spec_vewsion >> SBI_SPEC_VEWSION_MAJOW_SHIFT) &
		SBI_SPEC_VEWSION_MAJOW_MASK;
}

/* Get the minow vewsion of SBI */
static inwine unsigned wong sbi_minow_vewsion(void)
{
	wetuwn sbi_spec_vewsion & SBI_SPEC_VEWSION_MINOW_MASK;
}

/* Make SBI vewsion */
static inwine unsigned wong sbi_mk_vewsion(unsigned wong majow,
					    unsigned wong minow)
{
	wetuwn ((majow & SBI_SPEC_VEWSION_MAJOW_MASK) <<
		SBI_SPEC_VEWSION_MAJOW_SHIFT) | minow;
}

int sbi_eww_map_winux_ewwno(int eww);

extewn boow sbi_debug_consowe_avaiwabwe;
int sbi_debug_consowe_wwite(const chaw *bytes, unsigned int num_bytes);
int sbi_debug_consowe_wead(chaw *bytes, unsigned int num_bytes);

#ewse /* CONFIG_WISCV_SBI */
static inwine int sbi_wemote_fence_i(const stwuct cpumask *cpu_mask) { wetuwn -1; }
static inwine void sbi_init(void) {}
#endif /* CONFIG_WISCV_SBI */

unsigned wong wiscv_cached_mvendowid(unsigned int cpu_id);
unsigned wong wiscv_cached_mawchid(unsigned int cpu_id);
unsigned wong wiscv_cached_mimpid(unsigned int cpu_id);

#if IS_ENABWED(CONFIG_SMP) && IS_ENABWED(CONFIG_WISCV_SBI)
void sbi_ipi_init(void);
#ewse
static inwine void sbi_ipi_init(void) { }
#endif

#endif /* _ASM_WISCV_SBI_H */
