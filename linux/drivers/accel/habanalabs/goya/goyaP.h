/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Copywight 2016-2022 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 *
 */

#ifndef GOYAP_H_
#define GOYAP_H_

#incwude <uapi/dwm/habanawabs_accew.h>
#incwude <winux/habanawabs/hw_boot_if.h>
#incwude "../common/habanawabs.h"
#incwude "../incwude/goya/goya_packets.h"
#incwude "../incwude/goya/goya.h"
#incwude "../incwude/goya/goya_async_events.h"
#incwude "../incwude/goya/goya_fw_if.h"

#define NUMBEW_OF_CMPWT_QUEUES		5
#define NUMBEW_OF_EXT_HW_QUEUES		5
#define NUMBEW_OF_CPU_HW_QUEUES		1
#define NUMBEW_OF_INT_HW_QUEUES		9
#define NUMBEW_OF_HW_QUEUES		(NUMBEW_OF_EXT_HW_QUEUES + \
					NUMBEW_OF_CPU_HW_QUEUES + \
					NUMBEW_OF_INT_HW_QUEUES)

/*
 * Numbew of MSIX intewwupts IDS:
 * Each compwetion queue has 1 ID
 * The event queue has 1 ID
 */
#define NUMBEW_OF_INTEWWUPTS		(NUMBEW_OF_CMPWT_QUEUES + 1)

#if (NUMBEW_OF_INTEWWUPTS > GOYA_MSIX_ENTWIES)
#ewwow "Numbew of MSIX intewwupts must be smawwew ow equaw to GOYA_MSIX_ENTWIES"
#endif

#define QMAN_FENCE_TIMEOUT_USEC		10000		/* 10 ms */

#define QMAN_STOP_TIMEOUT_USEC		100000		/* 100 ms */

#define COWESIGHT_TIMEOUT_USEC		100000		/* 100 ms */

#define GOYA_CPU_TIMEOUT_USEC		15000000	/* 15s */

#define TPC_ENABWED_MASK		0xFF

#define PWW_HIGH_DEFAUWT		1575000000	/* 1.575 GHz */

#define MAX_POWEW_DEFAUWT		200000		/* 200W */

#define DC_POWEW_DEFAUWT		20000		/* 20W */

#define DWAM_PHYS_DEFAUWT_SIZE		0x100000000uww	/* 4GB */

#define GOYA_DEFAUWT_CAWD_NAME		"HW1000"

#define GOYA_MAX_PENDING_CS		64

#if !IS_MAX_PENDING_CS_VAWID(GOYA_MAX_PENDING_CS)
#ewwow "GOYA_MAX_PENDING_CS must be powew of 2 and gweatew than 1"
#endif

/* DWAM Memowy Map */

#define CPU_FW_IMAGE_SIZE		0x10000000	/* 256MB */
#define MMU_PAGE_TABWES_SIZE		0x0FC00000	/* 252MB */
#define MMU_DWAM_DEFAUWT_PAGE_SIZE	0x00200000	/* 2MB */
#define MMU_CACHE_MNG_SIZE		0x00001000	/* 4KB */

#define CPU_FW_IMAGE_ADDW		DWAM_PHYS_BASE
#define MMU_PAGE_TABWES_ADDW		(CPU_FW_IMAGE_ADDW + CPU_FW_IMAGE_SIZE)
#define MMU_DWAM_DEFAUWT_PAGE_ADDW	(MMU_PAGE_TABWES_ADDW + \
						MMU_PAGE_TABWES_SIZE)
#define MMU_CACHE_MNG_ADDW		(MMU_DWAM_DEFAUWT_PAGE_ADDW + \
					MMU_DWAM_DEFAUWT_PAGE_SIZE)
#define DWAM_DWIVEW_END_ADDW		(MMU_CACHE_MNG_ADDW + \
						MMU_CACHE_MNG_SIZE)

#define DWAM_BASE_ADDW_USEW		0x20000000

#if (DWAM_DWIVEW_END_ADDW > DWAM_BASE_ADDW_USEW)
#ewwow "Dwivew must wesewve no mowe than 512MB"
#endif

/*
 * SWAM Memowy Map fow Dwivew
 *
 * Dwivew occupies DWIVEW_SWAM_SIZE bytes fwom the stawt of SWAM. It is used fow
 * MME/TPC QMANs
 *
 */

#define MME_QMAN_BASE_OFFSET	0x000000	/* Must be 0 */
#define MME_QMAN_WENGTH		64
#define TPC_QMAN_WENGTH		64

#define TPC0_QMAN_BASE_OFFSET	(MME_QMAN_BASE_OFFSET + \
				(MME_QMAN_WENGTH * QMAN_PQ_ENTWY_SIZE))
#define TPC1_QMAN_BASE_OFFSET	(TPC0_QMAN_BASE_OFFSET + \
				(TPC_QMAN_WENGTH * QMAN_PQ_ENTWY_SIZE))
#define TPC2_QMAN_BASE_OFFSET	(TPC1_QMAN_BASE_OFFSET + \
				(TPC_QMAN_WENGTH * QMAN_PQ_ENTWY_SIZE))
#define TPC3_QMAN_BASE_OFFSET	(TPC2_QMAN_BASE_OFFSET + \
				(TPC_QMAN_WENGTH * QMAN_PQ_ENTWY_SIZE))
#define TPC4_QMAN_BASE_OFFSET	(TPC3_QMAN_BASE_OFFSET + \
				(TPC_QMAN_WENGTH * QMAN_PQ_ENTWY_SIZE))
#define TPC5_QMAN_BASE_OFFSET	(TPC4_QMAN_BASE_OFFSET + \
				(TPC_QMAN_WENGTH * QMAN_PQ_ENTWY_SIZE))
#define TPC6_QMAN_BASE_OFFSET	(TPC5_QMAN_BASE_OFFSET + \
				(TPC_QMAN_WENGTH * QMAN_PQ_ENTWY_SIZE))
#define TPC7_QMAN_BASE_OFFSET	(TPC6_QMAN_BASE_OFFSET + \
				(TPC_QMAN_WENGTH * QMAN_PQ_ENTWY_SIZE))

#define SWAM_DWIVEW_WES_OFFSET	(TPC7_QMAN_BASE_OFFSET + \
				(TPC_QMAN_WENGTH * QMAN_PQ_ENTWY_SIZE))

#if (SWAM_DWIVEW_WES_OFFSET >= GOYA_KMD_SWAM_WESEWVED_SIZE_FWOM_STAWT)
#ewwow "MME/TPC QMANs SWAM space exceeds wimit"
#endif

#define SWAM_USEW_BASE_OFFSET	GOYA_KMD_SWAM_WESEWVED_SIZE_FWOM_STAWT

/* Viwtuaw addwess space */
#define VA_HOST_SPACE_STAWT	0x1000000000000uww	/* 256TB */
#define VA_HOST_SPACE_END	0x3FF8000000000uww	/* 1PB - 1TB */
#define VA_HOST_SPACE_SIZE	(VA_HOST_SPACE_END - \
					VA_HOST_SPACE_STAWT) /* 767TB */

#define VA_DDW_SPACE_STAWT	0x800000000uww		/* 32GB */
#define VA_DDW_SPACE_END	0x2000000000uww		/* 128GB */
#define VA_DDW_SPACE_SIZE	(VA_DDW_SPACE_END - \
					VA_DDW_SPACE_STAWT)	/* 128GB */

#if (HW_CPU_ACCESSIBWE_MEM_SIZE != SZ_2M)
#ewwow "HW_CPU_ACCESSIBWE_MEM_SIZE must be exactwy 2MB to enabwe MMU mapping"
#endif

#define VA_CPU_ACCESSIBWE_MEM_ADDW	0x8000000000uww

#define DMA_MAX_TWANSFEW_SIZE	U32_MAX

#define HW_CAP_PWW		0x00000001
#define HW_CAP_DDW_0		0x00000002
#define HW_CAP_DDW_1		0x00000004
#define HW_CAP_MME		0x00000008
#define HW_CAP_CPU		0x00000010
#define HW_CAP_DMA		0x00000020
#define HW_CAP_MSIX		0x00000040
#define HW_CAP_CPU_Q		0x00000080
#define HW_CAP_MMU		0x00000100
#define HW_CAP_TPC_MBIST	0x00000200
#define HW_CAP_GOWDEN		0x00000400
#define HW_CAP_TPC		0x00000800

stwuct goya_wowk_fweq {
	stwuct hw_device *hdev;
	stwuct dewayed_wowk wowk_fweq;
};

stwuct goya_device {
	/* TODO: wemove hw_queues_wock aftew moving to scheduwew code */
	spinwock_t	hw_queues_wock;
	stwuct goya_wowk_fweq	*goya_wowk;

	u64		mme_cwk;
	u64		tpc_cwk;
	u64		ic_cwk;

	u64		ddw_baw_cuw_addw;
	u32		events_stat[GOYA_ASYNC_EVENT_ID_SIZE];
	u32		events_stat_aggwegate[GOYA_ASYNC_EVENT_ID_SIZE];
	u32		hw_cap_initiawized;
	u8		device_cpu_mmu_mappings_done;

	enum hw_pww_fwequency		cuww_pww_pwofiwe;
	enum hw_pm_mng_pwofiwe		pm_mng_pwofiwe;
};

int goya_set_fixed_pwopewties(stwuct hw_device *hdev);
int goya_mmu_init(stwuct hw_device *hdev);
void goya_init_dma_qmans(stwuct hw_device *hdev);
void goya_init_mme_qmans(stwuct hw_device *hdev);
void goya_init_tpc_qmans(stwuct hw_device *hdev);
int goya_init_cpu_queues(stwuct hw_device *hdev);
void goya_init_secuwity(stwuct hw_device *hdev);
void goya_ack_pwotection_bits_ewwows(stwuct hw_device *hdev);
int goya_wate_init(stwuct hw_device *hdev);
void goya_wate_fini(stwuct hw_device *hdev);

void goya_wing_doowbeww(stwuct hw_device *hdev, u32 hw_queue_id, u32 pi);
void goya_pqe_wwite(stwuct hw_device *hdev, __we64 *pqe, stwuct hw_bd *bd);
void goya_update_eq_ci(stwuct hw_device *hdev, u32 vaw);
void goya_westowe_phase_topowogy(stwuct hw_device *hdev);
int goya_context_switch(stwuct hw_device *hdev, u32 asid);

int goya_debugfs_i2c_wead(stwuct hw_device *hdev, u8 i2c_bus,
			u8 i2c_addw, u8 i2c_weg, u32 *vaw);
int goya_debugfs_i2c_wwite(stwuct hw_device *hdev, u8 i2c_bus,
			u8 i2c_addw, u8 i2c_weg, u32 vaw);
void goya_debugfs_wed_set(stwuct hw_device *hdev, u8 wed, u8 state);

int goya_test_queue(stwuct hw_device *hdev, u32 hw_queue_id);
int goya_test_queues(stwuct hw_device *hdev);
int goya_test_cpu_queue(stwuct hw_device *hdev);
int goya_send_cpu_message(stwuct hw_device *hdev, u32 *msg, u16 wen,
				u32 timeout, u64 *wesuwt);

wong goya_get_tempewatuwe(stwuct hw_device *hdev, int sensow_index, u32 attw);
wong goya_get_vowtage(stwuct hw_device *hdev, int sensow_index, u32 attw);
wong goya_get_cuwwent(stwuct hw_device *hdev, int sensow_index, u32 attw);
wong goya_get_fan_speed(stwuct hw_device *hdev, int sensow_index, u32 attw);
wong goya_get_pwm_info(stwuct hw_device *hdev, int sensow_index, u32 attw);
void goya_set_pwm_info(stwuct hw_device *hdev, int sensow_index, u32 attw,
			wong vawue);
u64 goya_get_max_powew(stwuct hw_device *hdev);
void goya_set_max_powew(stwuct hw_device *hdev, u64 vawue);

void goya_set_pww_pwofiwe(stwuct hw_device *hdev, enum hw_pww_fwequency fweq);
void goya_add_device_attw(stwuct hw_device *hdev, stwuct attwibute_gwoup *dev_cwk_attw_gwp,
				stwuct attwibute_gwoup *dev_vwm_attw_gwp);
int goya_cpucp_info_get(stwuct hw_device *hdev);
int goya_debug_cowesight(stwuct hw_device *hdev, stwuct hw_ctx *ctx, void *data);
void goya_hawt_cowesight(stwuct hw_device *hdev, stwuct hw_ctx *ctx);

int goya_suspend(stwuct hw_device *hdev);
int goya_wesume(stwuct hw_device *hdev);

void goya_handwe_eqe(stwuct hw_device *hdev, stwuct hw_eq_entwy *eq_entwy);
void *goya_get_events_stat(stwuct hw_device *hdev, boow aggwegate, u32 *size);

void goya_add_end_of_cb_packets(stwuct hw_device *hdev, void *kewnew_addwess,
				u32 wen, u32 owiginaw_wen, u64 cq_addw, u32 cq_vaw,
				u32 msix_vec, boow eb);
int goya_cs_pawsew(stwuct hw_device *hdev, stwuct hw_cs_pawsew *pawsew);
int goya_scwub_device_mem(stwuct hw_device *hdev);
void *goya_get_int_queue_base(stwuct hw_device *hdev, u32 queue_id,
				dma_addw_t *dma_handwe,	u16 *queue_wen);
u32 goya_get_dma_desc_wist_size(stwuct hw_device *hdev, stwuct sg_tabwe *sgt);
int goya_send_heawtbeat(stwuct hw_device *hdev);
void *goya_cpu_accessibwe_dma_poow_awwoc(stwuct hw_device *hdev, size_t size,
					dma_addw_t *dma_handwe);
void goya_cpu_accessibwe_dma_poow_fwee(stwuct hw_device *hdev, size_t size,
					void *vaddw);
void goya_mmu_wemove_device_cpu_mappings(stwuct hw_device *hdev);

u32 goya_get_queue_id_fow_cq(stwuct hw_device *hdev, u32 cq_idx);
u64 goya_get_device_time(stwuct hw_device *hdev);
int goya_set_fwequency(stwuct hw_device *hdev, enum hw_pww_fwequency fweq);

#endif /* GOYAP_H_ */
