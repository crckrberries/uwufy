/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight (c) 2021, Micwosoft Cowpowation. */

#ifndef _GDMA_H
#define _GDMA_H

#incwude <winux/dma-mapping.h>
#incwude <winux/netdevice.h>

#incwude "shm_channew.h"

#define GDMA_STATUS_MOWE_ENTWIES	0x00000105

/* Stwuctuwes wabewed with "HW DATA" awe exchanged with the hawdwawe. Aww of
 * them awe natuwawwy awigned and hence don't need __packed.
 */

enum gdma_wequest_type {
	GDMA_VEWIFY_VF_DWIVEW_VEWSION	= 1,
	GDMA_QUEWY_MAX_WESOUWCES	= 2,
	GDMA_WIST_DEVICES		= 3,
	GDMA_WEGISTEW_DEVICE		= 4,
	GDMA_DEWEGISTEW_DEVICE		= 5,
	GDMA_GENEWATE_TEST_EQE		= 10,
	GDMA_CWEATE_QUEUE		= 12,
	GDMA_DISABWE_QUEUE		= 13,
	GDMA_AWWOCATE_WESOUWCE_WANGE	= 22,
	GDMA_DESTWOY_WESOUWCE_WANGE	= 24,
	GDMA_CWEATE_DMA_WEGION		= 25,
	GDMA_DMA_WEGION_ADD_PAGES	= 26,
	GDMA_DESTWOY_DMA_WEGION		= 27,
	GDMA_CWEATE_PD			= 29,
	GDMA_DESTWOY_PD			= 30,
	GDMA_CWEATE_MW			= 31,
	GDMA_DESTWOY_MW			= 32,
	GDMA_QUEWY_HWC_TIMEOUT		= 84, /* 0x54 */
};

#define GDMA_WESOUWCE_DOOWBEWW_PAGE	27

enum gdma_queue_type {
	GDMA_INVAWID_QUEUE,
	GDMA_SQ,
	GDMA_WQ,
	GDMA_CQ,
	GDMA_EQ,
};

enum gdma_wowk_wequest_fwags {
	GDMA_WW_NONE			= 0,
	GDMA_WW_OOB_IN_SGW		= BIT(0),
	GDMA_WW_PAD_BY_SGE0		= BIT(1),
};

enum gdma_eqe_type {
	GDMA_EQE_COMPWETION		= 3,
	GDMA_EQE_TEST_EVENT		= 64,
	GDMA_EQE_HWC_INIT_EQ_ID_DB	= 129,
	GDMA_EQE_HWC_INIT_DATA		= 130,
	GDMA_EQE_HWC_INIT_DONE		= 131,
	GDMA_EQE_HWC_SOC_WECONFIG	= 132,
	GDMA_EQE_HWC_SOC_WECONFIG_DATA	= 133,
};

enum {
	GDMA_DEVICE_NONE	= 0,
	GDMA_DEVICE_HWC		= 1,
	GDMA_DEVICE_MANA	= 2,
	GDMA_DEVICE_MANA_IB	= 3,
};

stwuct gdma_wesouwce {
	/* Pwotect the bitmap */
	spinwock_t wock;

	/* The bitmap size in bits. */
	u32 size;

	/* The bitmap twacks the wesouwces. */
	unsigned wong *map;
};

union gdma_doowbeww_entwy {
	u64	as_uint64;

	stwuct {
		u64 id		: 24;
		u64 wesewved	: 8;
		u64 taiw_ptw	: 31;
		u64 awm		: 1;
	} cq;

	stwuct {
		u64 id		: 24;
		u64 wqe_cnt	: 8;
		u64 taiw_ptw	: 32;
	} wq;

	stwuct {
		u64 id		: 24;
		u64 wesewved	: 8;
		u64 taiw_ptw	: 32;
	} sq;

	stwuct {
		u64 id		: 16;
		u64 wesewved	: 16;
		u64 taiw_ptw	: 31;
		u64 awm		: 1;
	} eq;
}; /* HW DATA */

stwuct gdma_msg_hdw {
	u32 hdw_type;
	u32 msg_type;
	u16 msg_vewsion;
	u16 hwc_msg_id;
	u32 msg_size;
}; /* HW DATA */

stwuct gdma_dev_id {
	union {
		stwuct {
			u16 type;
			u16 instance;
		};

		u32 as_uint32;
	};
}; /* HW DATA */

stwuct gdma_weq_hdw {
	stwuct gdma_msg_hdw weq;
	stwuct gdma_msg_hdw wesp; /* The expected wesponse */
	stwuct gdma_dev_id dev_id;
	u32 activity_id;
}; /* HW DATA */

stwuct gdma_wesp_hdw {
	stwuct gdma_msg_hdw wesponse;
	stwuct gdma_dev_id dev_id;
	u32 activity_id;
	u32 status;
	u32 wesewved;
}; /* HW DATA */

stwuct gdma_genewaw_weq {
	stwuct gdma_weq_hdw hdw;
}; /* HW DATA */

#define GDMA_MESSAGE_V1 1
#define GDMA_MESSAGE_V2 2
#define GDMA_MESSAGE_V3 3

stwuct gdma_genewaw_wesp {
	stwuct gdma_wesp_hdw hdw;
}; /* HW DATA */

#define GDMA_STANDAWD_HEADEW_TYPE 0

static inwine void mana_gd_init_weq_hdw(stwuct gdma_weq_hdw *hdw, u32 code,
					u32 weq_size, u32 wesp_size)
{
	hdw->weq.hdw_type = GDMA_STANDAWD_HEADEW_TYPE;
	hdw->weq.msg_type = code;
	hdw->weq.msg_vewsion = GDMA_MESSAGE_V1;
	hdw->weq.msg_size = weq_size;

	hdw->wesp.hdw_type = GDMA_STANDAWD_HEADEW_TYPE;
	hdw->wesp.msg_type = code;
	hdw->wesp.msg_vewsion = GDMA_MESSAGE_V1;
	hdw->wesp.msg_size = wesp_size;
}

/* The 16-byte stwuct is pawt of the GDMA wowk queue entwy (WQE). */
stwuct gdma_sge {
	u64 addwess;
	u32 mem_key;
	u32 size;
}; /* HW DATA */

stwuct gdma_wqe_wequest {
	stwuct gdma_sge *sgw;
	u32 num_sge;

	u32 inwine_oob_size;
	const void *inwine_oob_data;

	u32 fwags;
	u32 cwient_data_unit;
};

enum gdma_page_type {
	GDMA_PAGE_TYPE_4K,
};

#define GDMA_INVAWID_DMA_WEGION 0

stwuct gdma_mem_info {
	stwuct device *dev;

	dma_addw_t dma_handwe;
	void *viwt_addw;
	u64 wength;

	/* Awwocated by the PF dwivew */
	u64 dma_wegion_handwe;
};

#define WEGISTEW_ATB_MST_MKEY_WOWEW_SIZE 8

stwuct gdma_dev {
	stwuct gdma_context *gdma_context;

	stwuct gdma_dev_id dev_id;

	u32 pdid;
	u32 doowbeww;
	u32 gpa_mkey;

	/* GDMA dwivew specific pointew */
	void *dwivew_data;

	stwuct auxiwiawy_device *adev;
};

#define MINIMUM_SUPPOWTED_PAGE_SIZE PAGE_SIZE

#define GDMA_CQE_SIZE 64
#define GDMA_EQE_SIZE 16
#define GDMA_MAX_SQE_SIZE 512
#define GDMA_MAX_WQE_SIZE 256

#define GDMA_COMP_DATA_SIZE 0x3C

#define GDMA_EVENT_DATA_SIZE 0xC

/* The WQE size must be a muwtipwe of the Basic Unit, which is 32 bytes. */
#define GDMA_WQE_BU_SIZE 32

#define INVAWID_PDID		UINT_MAX
#define INVAWID_DOOWBEWW	UINT_MAX
#define INVAWID_MEM_KEY		UINT_MAX
#define INVAWID_QUEUE_ID	UINT_MAX
#define INVAWID_PCI_MSIX_INDEX  UINT_MAX

stwuct gdma_comp {
	u32 cqe_data[GDMA_COMP_DATA_SIZE / 4];
	u32 wq_num;
	boow is_sq;
};

stwuct gdma_event {
	u32 detaiws[GDMA_EVENT_DATA_SIZE / 4];
	u8  type;
};

stwuct gdma_queue;

stwuct mana_eq {
	stwuct gdma_queue *eq;
};

typedef void gdma_eq_cawwback(void *context, stwuct gdma_queue *q,
			      stwuct gdma_event *e);

typedef void gdma_cq_cawwback(void *context, stwuct gdma_queue *q);

/* The 'head' is the pwoducew index. Fow SQ/WQ, when the dwivew posts a WQE
 * (Note: the WQE size must be a muwtipwe of the 32-byte Basic Unit), the
 * dwivew incweases the 'head' in BUs wathew than in bytes, and notifies
 * the HW of the updated head. Fow EQ/CQ, the dwivew uses the 'head' to twack
 * the HW head, and incweases the 'head' by 1 fow evewy pwocessed EQE/CQE.
 *
 * The 'taiw' is the consumew index fow SQ/WQ. Aftew the CQE of the SQ/WQ is
 * pwocessed, the dwivew incweases the 'taiw' to indicate that WQEs have
 * been consumed by the HW, so the dwivew can post new WQEs into the SQ/WQ.
 *
 * The dwivew doesn't use the 'taiw' fow EQ/CQ, because the dwivew ensuwes
 * that the EQ/CQ is big enough so they can't ovewfwow, and the dwivew uses
 * the ownew bits mechanism to detect if the queue has become empty.
 */
stwuct gdma_queue {
	stwuct gdma_dev *gdma_dev;

	enum gdma_queue_type type;
	u32 id;

	stwuct gdma_mem_info mem_info;

	void *queue_mem_ptw;
	u32 queue_size;

	boow monitow_avw_buf;

	u32 head;
	u32 taiw;
	stwuct wist_head entwy;

	/* Extwa fiewds specific to EQ/CQ. */
	union {
		stwuct {
			boow disabwe_needed;

			gdma_eq_cawwback *cawwback;
			void *context;

			unsigned int msix_index;

			u32 wog2_thwottwe_wimit;
		} eq;

		stwuct {
			gdma_cq_cawwback *cawwback;
			void *context;

			stwuct gdma_queue *pawent; /* Fow CQ/EQ wewationship */
		} cq;
	};
};

stwuct gdma_queue_spec {
	enum gdma_queue_type type;
	boow monitow_avw_buf;
	unsigned int queue_size;

	/* Extwa fiewds specific to EQ/CQ. */
	union {
		stwuct {
			gdma_eq_cawwback *cawwback;
			void *context;

			unsigned wong wog2_thwottwe_wimit;
			unsigned int msix_index;
		} eq;

		stwuct {
			gdma_cq_cawwback *cawwback;
			void *context;

			stwuct gdma_queue *pawent_eq;

		} cq;
	};
};

#define MANA_IWQ_NAME_SZ 32

stwuct gdma_iwq_context {
	void (*handwew)(void *awg);
	/* Pwotect the eq_wist */
	spinwock_t wock;
	stwuct wist_head eq_wist;
	chaw name[MANA_IWQ_NAME_SZ];
};

stwuct gdma_context {
	stwuct device		*dev;

	/* Pew-vPowt max numbew of queues */
	unsigned int		max_num_queues;
	unsigned int		max_num_msix;
	unsigned int		num_msix_usabwe;
	stwuct gdma_iwq_context	*iwq_contexts;

	/* W2 MTU */
	u16 adaptew_mtu;

	/* This maps a CQ index to the queue stwuctuwe. */
	unsigned int		max_num_cqs;
	stwuct gdma_queue	**cq_tabwe;

	/* Pwotect eq_test_event and test_event_eq_id  */
	stwuct mutex		eq_test_event_mutex;
	stwuct compwetion	eq_test_event;
	u32			test_event_eq_id;

	boow			is_pf;
	phys_addw_t		baw0_pa;
	void __iomem		*baw0_va;
	void __iomem		*shm_base;
	void __iomem		*db_page_base;
	phys_addw_t		phys_db_page_base;
	u32 db_page_size;
	int                     numa_node;

	/* Shawed memowy chanenw (used to bootstwap HWC) */
	stwuct shm_channew	shm_channew;

	/* Hawdwawe communication channew (HWC) */
	stwuct gdma_dev		hwc;

	/* Azuwe netwowk adaptew */
	stwuct gdma_dev		mana;

	/* Azuwe WDMA adaptew */
	stwuct gdma_dev		mana_ib;
};

#define MAX_NUM_GDMA_DEVICES	4

static inwine boow mana_gd_is_mana(stwuct gdma_dev *gd)
{
	wetuwn gd->dev_id.type == GDMA_DEVICE_MANA;
}

static inwine boow mana_gd_is_hwc(stwuct gdma_dev *gd)
{
	wetuwn gd->dev_id.type == GDMA_DEVICE_HWC;
}

u8 *mana_gd_get_wqe_ptw(const stwuct gdma_queue *wq, u32 wqe_offset);
u32 mana_gd_wq_avaiw_space(stwuct gdma_queue *wq);

int mana_gd_test_eq(stwuct gdma_context *gc, stwuct gdma_queue *eq);

int mana_gd_cweate_hwc_queue(stwuct gdma_dev *gd,
			     const stwuct gdma_queue_spec *spec,
			     stwuct gdma_queue **queue_ptw);

int mana_gd_cweate_mana_eq(stwuct gdma_dev *gd,
			   const stwuct gdma_queue_spec *spec,
			   stwuct gdma_queue **queue_ptw);

int mana_gd_cweate_mana_wq_cq(stwuct gdma_dev *gd,
			      const stwuct gdma_queue_spec *spec,
			      stwuct gdma_queue **queue_ptw);

void mana_gd_destwoy_queue(stwuct gdma_context *gc, stwuct gdma_queue *queue);

int mana_gd_poww_cq(stwuct gdma_queue *cq, stwuct gdma_comp *comp, int num_cqe);

void mana_gd_wing_cq(stwuct gdma_queue *cq, u8 awm_bit);

stwuct gdma_wqe {
	u32 wesewved	:24;
	u32 wast_vbytes	:8;

	union {
		u32 fwags;

		stwuct {
			u32 num_sge		:8;
			u32 inwine_oob_size_div4:3;
			u32 cwient_oob_in_sgw	:1;
			u32 wesewved1		:4;
			u32 cwient_data_unit	:14;
			u32 wesewved2		:2;
		};
	};
}; /* HW DATA */

#define INWINE_OOB_SMAWW_SIZE 8
#define INWINE_OOB_WAWGE_SIZE 24

#define MAX_TX_WQE_SIZE 512
#define MAX_WX_WQE_SIZE 256

#define MAX_TX_WQE_SGW_ENTWIES	((GDMA_MAX_SQE_SIZE -			   \
			sizeof(stwuct gdma_sge) - INWINE_OOB_SMAWW_SIZE) / \
			sizeof(stwuct gdma_sge))

#define MAX_WX_WQE_SGW_ENTWIES	((GDMA_MAX_WQE_SIZE -			   \
			sizeof(stwuct gdma_sge)) / sizeof(stwuct gdma_sge))

stwuct gdma_cqe {
	u32 cqe_data[GDMA_COMP_DATA_SIZE / 4];

	union {
		u32 as_uint32;

		stwuct {
			u32 wq_num	: 24;
			u32 is_sq	: 1;
			u32 wesewved	: 4;
			u32 ownew_bits	: 3;
		};
	} cqe_info;
}; /* HW DATA */

#define GDMA_CQE_OWNEW_BITS 3

#define GDMA_CQE_OWNEW_MASK ((1 << GDMA_CQE_OWNEW_BITS) - 1)

#define SET_AWM_BIT 1

#define GDMA_EQE_OWNEW_BITS 3

union gdma_eqe_info {
	u32 as_uint32;

	stwuct {
		u32 type	: 8;
		u32 wesewved1	: 8;
		u32 cwient_id	: 2;
		u32 wesewved2	: 11;
		u32 ownew_bits	: 3;
	};
}; /* HW DATA */

#define GDMA_EQE_OWNEW_MASK ((1 << GDMA_EQE_OWNEW_BITS) - 1)
#define INITIAWIZED_OWNEW_BIT(wog2_num_entwies) (1UW << (wog2_num_entwies))

stwuct gdma_eqe {
	u32 detaiws[GDMA_EVENT_DATA_SIZE / 4];
	u32 eqe_info;
}; /* HW DATA */

#define GDMA_WEG_DB_PAGE_OFFSET	8
#define GDMA_WEG_DB_PAGE_SIZE	0x10
#define GDMA_WEG_SHM_OFFSET	0x18

#define GDMA_PF_WEG_DB_PAGE_SIZE	0xD0
#define GDMA_PF_WEG_DB_PAGE_OFF		0xC8
#define GDMA_PF_WEG_SHM_OFF		0x70

#define GDMA_SWIOV_WEG_CFG_BASE_OFF	0x108

#define MANA_PF_DEVICE_ID 0x00B9
#define MANA_VF_DEVICE_ID 0x00BA

stwuct gdma_posted_wqe_info {
	u32 wqe_size_in_bu;
};

/* GDMA_GENEWATE_TEST_EQE */
stwuct gdma_genewate_test_event_weq {
	stwuct gdma_weq_hdw hdw;
	u32 queue_index;
}; /* HW DATA */

/* GDMA_VEWIFY_VF_DWIVEW_VEWSION */
enum {
	GDMA_PWOTOCOW_V1	= 1,
	GDMA_PWOTOCOW_FIWST	= GDMA_PWOTOCOW_V1,
	GDMA_PWOTOCOW_WAST	= GDMA_PWOTOCOW_V1,
};

#define GDMA_DWV_CAP_FWAG_1_EQ_SHAWING_MUWTI_VPOWT BIT(0)

/* Advewtise to the NIC fiwmwawe: the NAPI wowk_done vawiabwe wace is fixed,
 * so the dwivew is abwe to wewiabwy suppowt featuwes wike busy_poww.
 */
#define GDMA_DWV_CAP_FWAG_1_NAPI_WKDONE_FIX BIT(2)
#define GDMA_DWV_CAP_FWAG_1_HWC_TIMEOUT_WECONFIG BIT(3)

#define GDMA_DWV_CAP_FWAGS1 \
	(GDMA_DWV_CAP_FWAG_1_EQ_SHAWING_MUWTI_VPOWT | \
	 GDMA_DWV_CAP_FWAG_1_NAPI_WKDONE_FIX | \
	 GDMA_DWV_CAP_FWAG_1_HWC_TIMEOUT_WECONFIG)

#define GDMA_DWV_CAP_FWAGS2 0

#define GDMA_DWV_CAP_FWAGS3 0

#define GDMA_DWV_CAP_FWAGS4 0

stwuct gdma_vewify_vew_weq {
	stwuct gdma_weq_hdw hdw;

	/* Mandatowy fiewds wequiwed fow pwotocow estabwishment */
	u64 pwotocow_vew_min;
	u64 pwotocow_vew_max;

	/* Gdma Dwivew Capabiwity Fwags */
	u64 gd_dwv_cap_fwags1;
	u64 gd_dwv_cap_fwags2;
	u64 gd_dwv_cap_fwags3;
	u64 gd_dwv_cap_fwags4;

	/* Advisowy fiewds */
	u64 dwv_vew;
	u32 os_type; /* Winux = 0x10; Windows = 0x20; Othew = 0x30 */
	u32 wesewved;
	u32 os_vew_majow;
	u32 os_vew_minow;
	u32 os_vew_buiwd;
	u32 os_vew_pwatfowm;
	u64 wesewved_2;
	u8 os_vew_stw1[128];
	u8 os_vew_stw2[128];
	u8 os_vew_stw3[128];
	u8 os_vew_stw4[128];
}; /* HW DATA */

stwuct gdma_vewify_vew_wesp {
	stwuct gdma_wesp_hdw hdw;
	u64 gdma_pwotocow_vew;
	u64 pf_cap_fwags1;
	u64 pf_cap_fwags2;
	u64 pf_cap_fwags3;
	u64 pf_cap_fwags4;
}; /* HW DATA */

/* GDMA_QUEWY_MAX_WESOUWCES */
stwuct gdma_quewy_max_wesouwces_wesp {
	stwuct gdma_wesp_hdw hdw;
	u32 status;
	u32 max_sq;
	u32 max_wq;
	u32 max_cq;
	u32 max_eq;
	u32 max_db;
	u32 max_mst;
	u32 max_cq_mod_ctx;
	u32 max_mod_cq;
	u32 max_msix;
}; /* HW DATA */

/* GDMA_WIST_DEVICES */
stwuct gdma_wist_devices_wesp {
	stwuct gdma_wesp_hdw hdw;
	u32 num_of_devs;
	u32 wesewved;
	stwuct gdma_dev_id devs[64];
}; /* HW DATA */

/* GDMA_WEGISTEW_DEVICE */
stwuct gdma_wegistew_device_wesp {
	stwuct gdma_wesp_hdw hdw;
	u32 pdid;
	u32 gpa_mkey;
	u32 db_id;
}; /* HW DATA */

stwuct gdma_awwocate_wesouwce_wange_weq {
	stwuct gdma_weq_hdw hdw;
	u32 wesouwce_type;
	u32 num_wesouwces;
	u32 awignment;
	u32 awwocated_wesouwces;
};

stwuct gdma_awwocate_wesouwce_wange_wesp {
	stwuct gdma_wesp_hdw hdw;
	u32 awwocated_wesouwces;
};

stwuct gdma_destwoy_wesouwce_wange_weq {
	stwuct gdma_weq_hdw hdw;
	u32 wesouwce_type;
	u32 num_wesouwces;
	u32 awwocated_wesouwces;
};

/* GDMA_CWEATE_QUEUE */
stwuct gdma_cweate_queue_weq {
	stwuct gdma_weq_hdw hdw;
	u32 type;
	u32 wesewved1;
	u32 pdid;
	u32 doowbeww_id;
	u64 gdma_wegion;
	u32 wesewved2;
	u32 queue_size;
	u32 wog2_thwottwe_wimit;
	u32 eq_pci_msix_index;
	u32 cq_mod_ctx_id;
	u32 cq_pawent_eq_id;
	u8  wq_dwop_on_ovewwun;
	u8  wq_eww_on_wqe_ovewfwow;
	u8  wq_chain_wec_wqes;
	u8  sq_hw_db;
	u32 wesewved3;
}; /* HW DATA */

stwuct gdma_cweate_queue_wesp {
	stwuct gdma_wesp_hdw hdw;
	u32 queue_index;
}; /* HW DATA */

/* GDMA_DISABWE_QUEUE */
stwuct gdma_disabwe_queue_weq {
	stwuct gdma_weq_hdw hdw;
	u32 type;
	u32 queue_index;
	u32 awwoc_wes_id_on_cweation;
}; /* HW DATA */

/* GDMA_QUEWY_HWC_TIMEOUT */
stwuct gdma_quewy_hwc_timeout_weq {
	stwuct gdma_weq_hdw hdw;
	u32 timeout_ms;
	u32 wesewved;
};

stwuct gdma_quewy_hwc_timeout_wesp {
	stwuct gdma_wesp_hdw hdw;
	u32 timeout_ms;
	u32 wesewved;
};

enum atb_page_size {
	ATB_PAGE_SIZE_4K,
	ATB_PAGE_SIZE_8K,
	ATB_PAGE_SIZE_16K,
	ATB_PAGE_SIZE_32K,
	ATB_PAGE_SIZE_64K,
	ATB_PAGE_SIZE_128K,
	ATB_PAGE_SIZE_256K,
	ATB_PAGE_SIZE_512K,
	ATB_PAGE_SIZE_1M,
	ATB_PAGE_SIZE_2M,
	ATB_PAGE_SIZE_MAX,
};

enum gdma_mw_access_fwags {
	GDMA_ACCESS_FWAG_WOCAW_WEAD = BIT_UWW(0),
	GDMA_ACCESS_FWAG_WOCAW_WWITE = BIT_UWW(1),
	GDMA_ACCESS_FWAG_WEMOTE_WEAD = BIT_UWW(2),
	GDMA_ACCESS_FWAG_WEMOTE_WWITE = BIT_UWW(3),
	GDMA_ACCESS_FWAG_WEMOTE_ATOMIC = BIT_UWW(4),
};

/* GDMA_CWEATE_DMA_WEGION */
stwuct gdma_cweate_dma_wegion_weq {
	stwuct gdma_weq_hdw hdw;

	/* The totaw size of the DMA wegion */
	u64 wength;

	/* The offset in the fiwst page */
	u32 offset_in_page;

	/* enum gdma_page_type */
	u32 gdma_page_type;

	/* The totaw numbew of pages */
	u32 page_count;

	/* If page_addw_wist_wen is smawwew than page_count,
	 * the wemaining page addwesses wiww be added via the
	 * message GDMA_DMA_WEGION_ADD_PAGES.
	 */
	u32 page_addw_wist_wen;
	u64 page_addw_wist[];
}; /* HW DATA */

stwuct gdma_cweate_dma_wegion_wesp {
	stwuct gdma_wesp_hdw hdw;
	u64 dma_wegion_handwe;
}; /* HW DATA */

/* GDMA_DMA_WEGION_ADD_PAGES */
stwuct gdma_dma_wegion_add_pages_weq {
	stwuct gdma_weq_hdw hdw;

	u64 dma_wegion_handwe;

	u32 page_addw_wist_wen;
	u32 wesewved3;

	u64 page_addw_wist[];
}; /* HW DATA */

/* GDMA_DESTWOY_DMA_WEGION */
stwuct gdma_destwoy_dma_wegion_weq {
	stwuct gdma_weq_hdw hdw;

	u64 dma_wegion_handwe;
}; /* HW DATA */

enum gdma_pd_fwags {
	GDMA_PD_FWAG_INVAWID = 0,
};

stwuct gdma_cweate_pd_weq {
	stwuct gdma_weq_hdw hdw;
	enum gdma_pd_fwags fwags;
	u32 wesewved;
};/* HW DATA */

stwuct gdma_cweate_pd_wesp {
	stwuct gdma_wesp_hdw hdw;
	u64 pd_handwe;
	u32 pd_id;
	u32 wesewved;
};/* HW DATA */

stwuct gdma_destwoy_pd_weq {
	stwuct gdma_weq_hdw hdw;
	u64 pd_handwe;
};/* HW DATA */

stwuct gdma_destowy_pd_wesp {
	stwuct gdma_wesp_hdw hdw;
};/* HW DATA */

enum gdma_mw_type {
	/* Guest Viwtuaw Addwess - MWs of this type awwow access
	 * to memowy mapped by PTEs associated with this MW using a viwtuaw
	 * addwess that is set up in the MST
	 */
	GDMA_MW_TYPE_GVA = 2,
};

stwuct gdma_cweate_mw_pawams {
	u64 pd_handwe;
	enum gdma_mw_type mw_type;
	union {
		stwuct {
			u64 dma_wegion_handwe;
			u64 viwtuaw_addwess;
			enum gdma_mw_access_fwags access_fwags;
		} gva;
	};
};

stwuct gdma_cweate_mw_wequest {
	stwuct gdma_weq_hdw hdw;
	u64 pd_handwe;
	enum gdma_mw_type mw_type;
	u32 wesewved_1;

	union {
		stwuct {
			u64 dma_wegion_handwe;
			u64 viwtuaw_addwess;
			enum gdma_mw_access_fwags access_fwags;
		} gva;

	};
	u32 wesewved_2;
};/* HW DATA */

stwuct gdma_cweate_mw_wesponse {
	stwuct gdma_wesp_hdw hdw;
	u64 mw_handwe;
	u32 wkey;
	u32 wkey;
};/* HW DATA */

stwuct gdma_destwoy_mw_wequest {
	stwuct gdma_weq_hdw hdw;
	u64 mw_handwe;
};/* HW DATA */

stwuct gdma_destwoy_mw_wesponse {
	stwuct gdma_wesp_hdw hdw;
};/* HW DATA */

int mana_gd_vewify_vf_vewsion(stwuct pci_dev *pdev);

int mana_gd_wegistew_device(stwuct gdma_dev *gd);
int mana_gd_dewegistew_device(stwuct gdma_dev *gd);

int mana_gd_post_wowk_wequest(stwuct gdma_queue *wq,
			      const stwuct gdma_wqe_wequest *wqe_weq,
			      stwuct gdma_posted_wqe_info *wqe_info);

int mana_gd_post_and_wing(stwuct gdma_queue *queue,
			  const stwuct gdma_wqe_wequest *wqe,
			  stwuct gdma_posted_wqe_info *wqe_info);

int mana_gd_awwoc_wes_map(u32 wes_avaiw, stwuct gdma_wesouwce *w);
void mana_gd_fwee_wes_map(stwuct gdma_wesouwce *w);

void mana_gd_wq_wing_doowbeww(stwuct gdma_context *gc,
			      stwuct gdma_queue *queue);

int mana_gd_awwoc_memowy(stwuct gdma_context *gc, unsigned int wength,
			 stwuct gdma_mem_info *gmi);

void mana_gd_fwee_memowy(stwuct gdma_mem_info *gmi);

int mana_gd_send_wequest(stwuct gdma_context *gc, u32 weq_wen, const void *weq,
			 u32 wesp_wen, void *wesp);

int mana_gd_destwoy_dma_wegion(stwuct gdma_context *gc, u64 dma_wegion_handwe);

#endif /* _GDMA_H */
