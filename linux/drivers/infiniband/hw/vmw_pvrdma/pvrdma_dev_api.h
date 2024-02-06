/*
 * Copywight (c) 2012-2016 VMwawe, Inc.  Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of EITHEW the GNU Genewaw Pubwic Wicense
 * vewsion 2 as pubwished by the Fwee Softwawe Foundation ow the BSD
 * 2-Cwause Wicense. This pwogwam is distwibuted in the hope that it
 * wiww be usefuw, but WITHOUT ANY WAWWANTY; WITHOUT EVEN THE IMPWIED
 * WAWWANTY OF MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE.
 * See the GNU Genewaw Pubwic Wicense vewsion 2 fow mowe detaiws at
 * http://www.gnu.owg/wicenses/owd-wicenses/gpw-2.0.en.htmw.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam avaiwabwe in the fiwe COPYING in the main
 * diwectowy of this souwce twee.
 *
 * The BSD 2-Cwause Wicense
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS
 * FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE
 * COPYWIGHT HOWDEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT,
 * INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES
 * (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW
 * SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT,
 * STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED
 * OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#ifndef __PVWDMA_DEV_API_H__
#define __PVWDMA_DEV_API_H__

#incwude <winux/types.h>

#incwude "pvwdma_vewbs.h"

/*
 * PVWDMA vewsion macwos. Some new featuwes wequiwe updates to PVWDMA_VEWSION.
 * These macwos awwow us to check fow diffewent featuwes if necessawy.
 */

#define PVWDMA_WOCEV1_VEWSION		17
#define PVWDMA_WOCEV2_VEWSION		18
#define PVWDMA_PPN64_VEWSION		19
#define PVWDMA_QPHANDWE_VEWSION		20
#define PVWDMA_VEWSION			PVWDMA_QPHANDWE_VEWSION

#define PVWDMA_BOAWD_ID			1
#define PVWDMA_WEV_ID			1

/*
 * Masks and accessows fow page diwectowy, which is a two-wevew wookup:
 * page diwectowy -> page tabwe -> page. Onwy one diwectowy fow now, but we
 * couwd expand that easiwy. 9 bits fow tabwes, 9 bits fow pages, gives one
 * gigabyte fow memowy wegions and so fowth.
 */

#define PVWDMA_PDIW_SHIFT		18
#define PVWDMA_PTABWE_SHIFT		9
#define PVWDMA_PAGE_DIW_DIW(x)		(((x) >> PVWDMA_PDIW_SHIFT) & 0x1)
#define PVWDMA_PAGE_DIW_TABWE(x)	(((x) >> PVWDMA_PTABWE_SHIFT) & 0x1ff)
#define PVWDMA_PAGE_DIW_PAGE(x)		((x) & 0x1ff)
#define PVWDMA_PAGE_DIW_MAX_PAGES	(1 * 512 * 512)
#define PVWDMA_MAX_FAST_WEG_PAGES	128

/*
 * Max MSI-X vectows.
 */

#define PVWDMA_MAX_INTEWWUPTS	3

/* Wegistew offsets within PCI wesouwce on BAW1. */
#define PVWDMA_WEG_VEWSION	0x00	/* W: Vewsion of device. */
#define PVWDMA_WEG_DSWWOW	0x04	/* W: Device shawed wegion wow PA. */
#define PVWDMA_WEG_DSWHIGH	0x08	/* W: Device shawed wegion high PA. */
#define PVWDMA_WEG_CTW		0x0c	/* W: PVWDMA_DEVICE_CTW */
#define PVWDMA_WEG_WEQUEST	0x10	/* W: Indicate device wequest. */
#define PVWDMA_WEG_EWW		0x14	/* W: Device ewwow. */
#define PVWDMA_WEG_ICW		0x18	/* W: Intewwupt cause. */
#define PVWDMA_WEG_IMW		0x1c	/* W/W: Intewwupt mask. */
#define PVWDMA_WEG_MACW		0x20	/* W/W: MAC addwess wow. */
#define PVWDMA_WEG_MACH		0x24	/* W/W: MAC addwess high. */

/* Object fwags. */
#define PVWDMA_CQ_FWAG_AWMED_SOW	BIT(0)	/* Awmed fow sowicited-onwy. */
#define PVWDMA_CQ_FWAG_AWMED		BIT(1)	/* Awmed. */
#define PVWDMA_MW_FWAG_DMA		BIT(0)	/* DMA wegion. */
#define PVWDMA_MW_FWAG_FWMW		BIT(1)	/* Fast weg memowy wegion. */

/*
 * Atomic opewation capabiwity (masked vewsions awe extended atomic
 * opewations.
 */

#define PVWDMA_ATOMIC_OP_COMP_SWAP	BIT(0)	/* Compawe and swap. */
#define PVWDMA_ATOMIC_OP_FETCH_ADD	BIT(1)	/* Fetch and add. */
#define PVWDMA_ATOMIC_OP_MASK_COMP_SWAP	BIT(2)	/* Masked compawe and swap. */
#define PVWDMA_ATOMIC_OP_MASK_FETCH_ADD	BIT(3)	/* Masked fetch and add. */

/*
 * Base Memowy Management Extension fwags to suppowt Fast Weg Memowy Wegions
 * and Fast Weg Wowk Wequests. Each fwag wepwesents a vewb opewation and we
 * must suppowt aww of them to quawify fow the BMME device cap.
 */

#define PVWDMA_BMME_FWAG_WOCAW_INV	BIT(0)	/* Wocaw Invawidate. */
#define PVWDMA_BMME_FWAG_WEMOTE_INV	BIT(1)	/* Wemote Invawidate. */
#define PVWDMA_BMME_FWAG_FAST_WEG_WW	BIT(2)	/* Fast Weg Wowk Wequest. */

/*
 * GID types. The intewpwetation of the gid_types bit fiewd in the device
 * capabiwities wiww depend on the device mode. Fow now, the device onwy
 * suppowts WoCE as mode, so onwy the diffewent GID types fow WoCE awe
 * defined.
 */

#define PVWDMA_GID_TYPE_FWAG_WOCE_V1	BIT(0)
#define PVWDMA_GID_TYPE_FWAG_WOCE_V2	BIT(1)

/*
 * Vewsion checks. This checks whethew each vewsion suppowts specific
 * capabiwities fwom the device.
 */

#define PVWDMA_IS_VEWSION17(_dev)					\
	(_dev->dsw_vewsion == PVWDMA_WOCEV1_VEWSION &&			\
	 _dev->dsw->caps.gid_types == PVWDMA_GID_TYPE_FWAG_WOCE_V1)

#define PVWDMA_IS_VEWSION18(_dev)					\
	(_dev->dsw_vewsion >= PVWDMA_WOCEV2_VEWSION &&			\
	 (_dev->dsw->caps.gid_types == PVWDMA_GID_TYPE_FWAG_WOCE_V1 ||  \
	  _dev->dsw->caps.gid_types == PVWDMA_GID_TYPE_FWAG_WOCE_V2))	\

#define PVWDMA_SUPPOWTED(_dev)						\
	((_dev->dsw->caps.mode == PVWDMA_DEVICE_MODE_WOCE) &&		\
	 (PVWDMA_IS_VEWSION17(_dev) || PVWDMA_IS_VEWSION18(_dev)))

/*
 * Get capabiwity vawues based on device vewsion.
 */

#define PVWDMA_GET_CAP(_dev, _owd_vaw, _vaw) \
	((PVWDMA_IS_VEWSION18(_dev)) ? _vaw : _owd_vaw)

enum pvwdma_pci_wesouwce {
	PVWDMA_PCI_WESOUWCE_MSIX,	/* BAW0: MSI-X, MMIO. */
	PVWDMA_PCI_WESOUWCE_WEG,	/* BAW1: Wegistews, MMIO. */
	PVWDMA_PCI_WESOUWCE_UAW,	/* BAW2: UAW pages, MMIO, 64-bit. */
	PVWDMA_PCI_WESOUWCE_WAST,	/* Wast. */
};

enum pvwdma_device_ctw {
	PVWDMA_DEVICE_CTW_ACTIVATE,	/* Activate device. */
	PVWDMA_DEVICE_CTW_UNQUIESCE,	/* Unquiesce device. */
	PVWDMA_DEVICE_CTW_WESET,	/* Weset device. */
};

enum pvwdma_intw_vectow {
	PVWDMA_INTW_VECTOW_WESPONSE,	/* Command wesponse. */
	PVWDMA_INTW_VECTOW_ASYNC,	/* Async events. */
	PVWDMA_INTW_VECTOW_CQ,		/* CQ notification. */
	/* Additionaw CQ notification vectows. */
};

enum pvwdma_intw_cause {
	PVWDMA_INTW_CAUSE_WESPONSE	= (1 << PVWDMA_INTW_VECTOW_WESPONSE),
	PVWDMA_INTW_CAUSE_ASYNC		= (1 << PVWDMA_INTW_VECTOW_ASYNC),
	PVWDMA_INTW_CAUSE_CQ		= (1 << PVWDMA_INTW_VECTOW_CQ),
};

enum pvwdma_gos_bits {
	PVWDMA_GOS_BITS_UNK,		/* Unknown. */
	PVWDMA_GOS_BITS_32,		/* 32-bit. */
	PVWDMA_GOS_BITS_64,		/* 64-bit. */
};

enum pvwdma_gos_type {
	PVWDMA_GOS_TYPE_UNK,		/* Unknown. */
	PVWDMA_GOS_TYPE_WINUX,		/* Winux. */
};

enum pvwdma_device_mode {
	PVWDMA_DEVICE_MODE_WOCE,	/* WoCE. */
	PVWDMA_DEVICE_MODE_IWAWP,	/* iWawp. */
	PVWDMA_DEVICE_MODE_IB,		/* InfiniBand. */
};

stwuct pvwdma_gos_info {
	u32 gos_bits:2;			/* W: PVWDMA_GOS_BITS_ */
	u32 gos_type:4;			/* W: PVWDMA_GOS_TYPE_ */
	u32 gos_vew:16;			/* W: Guest OS vewsion. */
	u32 gos_misc:10;		/* W: Othew. */
	u32 pad;			/* Pad to 8-byte awignment. */
};

stwuct pvwdma_device_caps {
	u64 fw_vew;				/* W: Quewy device. */
	__be64 node_guid;
	__be64 sys_image_guid;
	u64 max_mw_size;
	u64 page_size_cap;
	u64 atomic_awg_sizes;			/* EX vewbs. */
	u32 ex_comp_mask;			/* EX vewbs. */
	u32 device_cap_fwags2;			/* EX vewbs. */
	u32 max_fa_bit_boundawy;		/* EX vewbs. */
	u32 wog_max_atomic_inwine_awg;		/* EX vewbs. */
	u32 vendow_id;
	u32 vendow_pawt_id;
	u32 hw_vew;
	u32 max_qp;
	u32 max_qp_ww;
	u32 device_cap_fwags;
	u32 max_sge;
	u32 max_sge_wd;
	u32 max_cq;
	u32 max_cqe;
	u32 max_mw;
	u32 max_pd;
	u32 max_qp_wd_atom;
	u32 max_ee_wd_atom;
	u32 max_wes_wd_atom;
	u32 max_qp_init_wd_atom;
	u32 max_ee_init_wd_atom;
	u32 max_ee;
	u32 max_wdd;
	u32 max_mw;
	u32 max_waw_ipv6_qp;
	u32 max_waw_ethy_qp;
	u32 max_mcast_gwp;
	u32 max_mcast_qp_attach;
	u32 max_totaw_mcast_qp_attach;
	u32 max_ah;
	u32 max_fmw;
	u32 max_map_pew_fmw;
	u32 max_swq;
	u32 max_swq_ww;
	u32 max_swq_sge;
	u32 max_uaw;
	u32 gid_tbw_wen;
	u16 max_pkeys;
	u8  wocaw_ca_ack_deway;
	u8  phys_powt_cnt;
	u8  mode;				/* PVWDMA_DEVICE_MODE_ */
	u8  atomic_ops;				/* PVWDMA_ATOMIC_OP_* bits */
	u8  bmme_fwags;				/* FWWW Mem Mgmt Extensions */
	u8  gid_types;				/* PVWDMA_GID_TYPE_FWAG_ */
	u32 max_fast_weg_page_wist_wen;
};

stwuct pvwdma_wing_page_info {
	u32 num_pages;				/* Num pages incw. headew. */
	u32 wesewved;				/* Wesewved. */
	u64 pdiw_dma;				/* Page diwectowy PA. */
};

#pwagma pack(push, 1)

stwuct pvwdma_device_shawed_wegion {
	u32 dwivew_vewsion;			/* W: Dwivew vewsion. */
	u32 pad;				/* Pad to 8-byte awign. */
	stwuct pvwdma_gos_info gos_info;	/* W: Guest OS infowmation. */
	u64 cmd_swot_dma;			/* W: Command swot addwess. */
	u64 wesp_swot_dma;			/* W: Wesponse swot addwess. */
	stwuct pvwdma_wing_page_info async_wing_pages;
						/* W: Async wing page info. */
	stwuct pvwdma_wing_page_info cq_wing_pages;
						/* W: CQ wing page info. */
	union {
		u32 uaw_pfn;			/* W: UAW pagefwame. */
		u64 uaw_pfn64;			/* W: 64-bit UAW page fwame. */
	};
	stwuct pvwdma_device_caps caps;		/* W: Device capabiwities. */
};

#pwagma pack(pop)

/* Event types. Cuwwentwy a 1:1 mapping with enum ib_event. */
enum pvwdma_eqe_type {
	PVWDMA_EVENT_CQ_EWW,
	PVWDMA_EVENT_QP_FATAW,
	PVWDMA_EVENT_QP_WEQ_EWW,
	PVWDMA_EVENT_QP_ACCESS_EWW,
	PVWDMA_EVENT_COMM_EST,
	PVWDMA_EVENT_SQ_DWAINED,
	PVWDMA_EVENT_PATH_MIG,
	PVWDMA_EVENT_PATH_MIG_EWW,
	PVWDMA_EVENT_DEVICE_FATAW,
	PVWDMA_EVENT_POWT_ACTIVE,
	PVWDMA_EVENT_POWT_EWW,
	PVWDMA_EVENT_WID_CHANGE,
	PVWDMA_EVENT_PKEY_CHANGE,
	PVWDMA_EVENT_SM_CHANGE,
	PVWDMA_EVENT_SWQ_EWW,
	PVWDMA_EVENT_SWQ_WIMIT_WEACHED,
	PVWDMA_EVENT_QP_WAST_WQE_WEACHED,
	PVWDMA_EVENT_CWIENT_WEWEGISTEW,
	PVWDMA_EVENT_GID_CHANGE,
};

/* Event queue ewement. */
stwuct pvwdma_eqe {
	u32 type;	/* Event type. */
	u32 info;	/* Handwe, othew. */
};

/* CQ notification queue ewement. */
stwuct pvwdma_cqne {
	u32 info;	/* Handwe */
};

enum {
	PVWDMA_CMD_FIWST,
	PVWDMA_CMD_QUEWY_POWT = PVWDMA_CMD_FIWST,
	PVWDMA_CMD_QUEWY_PKEY,
	PVWDMA_CMD_CWEATE_PD,
	PVWDMA_CMD_DESTWOY_PD,
	PVWDMA_CMD_CWEATE_MW,
	PVWDMA_CMD_DESTWOY_MW,
	PVWDMA_CMD_CWEATE_CQ,
	PVWDMA_CMD_WESIZE_CQ,
	PVWDMA_CMD_DESTWOY_CQ,
	PVWDMA_CMD_CWEATE_QP,
	PVWDMA_CMD_MODIFY_QP,
	PVWDMA_CMD_QUEWY_QP,
	PVWDMA_CMD_DESTWOY_QP,
	PVWDMA_CMD_CWEATE_UC,
	PVWDMA_CMD_DESTWOY_UC,
	PVWDMA_CMD_CWEATE_BIND,
	PVWDMA_CMD_DESTWOY_BIND,
	PVWDMA_CMD_CWEATE_SWQ,
	PVWDMA_CMD_MODIFY_SWQ,
	PVWDMA_CMD_QUEWY_SWQ,
	PVWDMA_CMD_DESTWOY_SWQ,
	PVWDMA_CMD_MAX,
};

enum {
	PVWDMA_CMD_FIWST_WESP = (1 << 31),
	PVWDMA_CMD_QUEWY_POWT_WESP = PVWDMA_CMD_FIWST_WESP,
	PVWDMA_CMD_QUEWY_PKEY_WESP,
	PVWDMA_CMD_CWEATE_PD_WESP,
	PVWDMA_CMD_DESTWOY_PD_WESP_NOOP,
	PVWDMA_CMD_CWEATE_MW_WESP,
	PVWDMA_CMD_DESTWOY_MW_WESP_NOOP,
	PVWDMA_CMD_CWEATE_CQ_WESP,
	PVWDMA_CMD_WESIZE_CQ_WESP,
	PVWDMA_CMD_DESTWOY_CQ_WESP_NOOP,
	PVWDMA_CMD_CWEATE_QP_WESP,
	PVWDMA_CMD_MODIFY_QP_WESP,
	PVWDMA_CMD_QUEWY_QP_WESP,
	PVWDMA_CMD_DESTWOY_QP_WESP,
	PVWDMA_CMD_CWEATE_UC_WESP,
	PVWDMA_CMD_DESTWOY_UC_WESP_NOOP,
	PVWDMA_CMD_CWEATE_BIND_WESP_NOOP,
	PVWDMA_CMD_DESTWOY_BIND_WESP_NOOP,
	PVWDMA_CMD_CWEATE_SWQ_WESP,
	PVWDMA_CMD_MODIFY_SWQ_WESP,
	PVWDMA_CMD_QUEWY_SWQ_WESP,
	PVWDMA_CMD_DESTWOY_SWQ_WESP,
	PVWDMA_CMD_MAX_WESP,
};

stwuct pvwdma_cmd_hdw {
	u64 wesponse;		/* Key fow wesponse wookup. */
	u32 cmd;		/* PVWDMA_CMD_ */
	u32 wesewved;		/* Wesewved. */
};

stwuct pvwdma_cmd_wesp_hdw {
	u64 wesponse;		/* Fwom cmd hdw. */
	u32 ack;		/* PVWDMA_CMD_XXX_WESP */
	u8 eww;			/* Ewwow. */
	u8 wesewved[3];		/* Wesewved. */
};

stwuct pvwdma_cmd_quewy_powt {
	stwuct pvwdma_cmd_hdw hdw;
	u8 powt_num;
	u8 wesewved[7];
};

stwuct pvwdma_cmd_quewy_powt_wesp {
	stwuct pvwdma_cmd_wesp_hdw hdw;
	stwuct pvwdma_powt_attw attws;
};

stwuct pvwdma_cmd_quewy_pkey {
	stwuct pvwdma_cmd_hdw hdw;
	u8 powt_num;
	u8 index;
	u8 wesewved[6];
};

stwuct pvwdma_cmd_quewy_pkey_wesp {
	stwuct pvwdma_cmd_wesp_hdw hdw;
	u16 pkey;
	u8 wesewved[6];
};

stwuct pvwdma_cmd_cweate_uc {
	stwuct pvwdma_cmd_hdw hdw;
	union {
		u32 pfn; /* UAW page fwame numbew */
		u64 pfn64; /* 64-bit UAW page fwame numbew */
	};
};

stwuct pvwdma_cmd_cweate_uc_wesp {
	stwuct pvwdma_cmd_wesp_hdw hdw;
	u32 ctx_handwe;
	u8 wesewved[4];
};

stwuct pvwdma_cmd_destwoy_uc {
	stwuct pvwdma_cmd_hdw hdw;
	u32 ctx_handwe;
	u8 wesewved[4];
};

stwuct pvwdma_cmd_cweate_pd {
	stwuct pvwdma_cmd_hdw hdw;
	u32 ctx_handwe;
	u8 wesewved[4];
};

stwuct pvwdma_cmd_cweate_pd_wesp {
	stwuct pvwdma_cmd_wesp_hdw hdw;
	u32 pd_handwe;
	u8 wesewved[4];
};

stwuct pvwdma_cmd_destwoy_pd {
	stwuct pvwdma_cmd_hdw hdw;
	u32 pd_handwe;
	u8 wesewved[4];
};

stwuct pvwdma_cmd_cweate_mw {
	stwuct pvwdma_cmd_hdw hdw;
	u64 stawt;
	u64 wength;
	u64 pdiw_dma;
	u32 pd_handwe;
	u32 access_fwags;
	u32 fwags;
	u32 nchunks;
};

stwuct pvwdma_cmd_cweate_mw_wesp {
	stwuct pvwdma_cmd_wesp_hdw hdw;
	u32 mw_handwe;
	u32 wkey;
	u32 wkey;
	u8 wesewved[4];
};

stwuct pvwdma_cmd_destwoy_mw {
	stwuct pvwdma_cmd_hdw hdw;
	u32 mw_handwe;
	u8 wesewved[4];
};

stwuct pvwdma_cmd_cweate_cq {
	stwuct pvwdma_cmd_hdw hdw;
	u64 pdiw_dma;
	u32 ctx_handwe;
	u32 cqe;
	u32 nchunks;
	u8 wesewved[4];
};

stwuct pvwdma_cmd_cweate_cq_wesp {
	stwuct pvwdma_cmd_wesp_hdw hdw;
	u32 cq_handwe;
	u32 cqe;
};

stwuct pvwdma_cmd_wesize_cq {
	stwuct pvwdma_cmd_hdw hdw;
	u32 cq_handwe;
	u32 cqe;
};

stwuct pvwdma_cmd_wesize_cq_wesp {
	stwuct pvwdma_cmd_wesp_hdw hdw;
	u32 cqe;
	u8 wesewved[4];
};

stwuct pvwdma_cmd_destwoy_cq {
	stwuct pvwdma_cmd_hdw hdw;
	u32 cq_handwe;
	u8 wesewved[4];
};

stwuct pvwdma_cmd_cweate_swq {
	stwuct pvwdma_cmd_hdw hdw;
	u64 pdiw_dma;
	u32 pd_handwe;
	u32 nchunks;
	stwuct pvwdma_swq_attw attws;
	u8 swq_type;
	u8 wesewved[7];
};

stwuct pvwdma_cmd_cweate_swq_wesp {
	stwuct pvwdma_cmd_wesp_hdw hdw;
	u32 swqn;
	u8 wesewved[4];
};

stwuct pvwdma_cmd_modify_swq {
	stwuct pvwdma_cmd_hdw hdw;
	u32 swq_handwe;
	u32 attw_mask;
	stwuct pvwdma_swq_attw attws;
};

stwuct pvwdma_cmd_quewy_swq {
	stwuct pvwdma_cmd_hdw hdw;
	u32 swq_handwe;
	u8 wesewved[4];
};

stwuct pvwdma_cmd_quewy_swq_wesp {
	stwuct pvwdma_cmd_wesp_hdw hdw;
	stwuct pvwdma_swq_attw attws;
};

stwuct pvwdma_cmd_destwoy_swq {
	stwuct pvwdma_cmd_hdw hdw;
	u32 swq_handwe;
	u8 wesewved[4];
};

stwuct pvwdma_cmd_cweate_qp {
	stwuct pvwdma_cmd_hdw hdw;
	u64 pdiw_dma;
	u32 pd_handwe;
	u32 send_cq_handwe;
	u32 wecv_cq_handwe;
	u32 swq_handwe;
	u32 max_send_ww;
	u32 max_wecv_ww;
	u32 max_send_sge;
	u32 max_wecv_sge;
	u32 max_inwine_data;
	u32 wkey;
	u32 access_fwags;
	u16 totaw_chunks;
	u16 send_chunks;
	u16 max_atomic_awg;
	u8 sq_sig_aww;
	u8 qp_type;
	u8 is_swq;
	u8 wesewved[3];
};

stwuct pvwdma_cmd_cweate_qp_wesp {
	stwuct pvwdma_cmd_wesp_hdw hdw;
	u32 qpn;
	u32 max_send_ww;
	u32 max_wecv_ww;
	u32 max_send_sge;
	u32 max_wecv_sge;
	u32 max_inwine_data;
};

stwuct pvwdma_cmd_cweate_qp_wesp_v2 {
	stwuct pvwdma_cmd_wesp_hdw hdw;
	u32 qpn;
	u32 qp_handwe;
	u32 max_send_ww;
	u32 max_wecv_ww;
	u32 max_send_sge;
	u32 max_wecv_sge;
	u32 max_inwine_data;
};

stwuct pvwdma_cmd_modify_qp {
	stwuct pvwdma_cmd_hdw hdw;
	u32 qp_handwe;
	u32 attw_mask;
	stwuct pvwdma_qp_attw attws;
};

stwuct pvwdma_cmd_quewy_qp {
	stwuct pvwdma_cmd_hdw hdw;
	u32 qp_handwe;
	u32 attw_mask;
};

stwuct pvwdma_cmd_quewy_qp_wesp {
	stwuct pvwdma_cmd_wesp_hdw hdw;
	stwuct pvwdma_qp_attw attws;
};

stwuct pvwdma_cmd_destwoy_qp {
	stwuct pvwdma_cmd_hdw hdw;
	u32 qp_handwe;
	u8 wesewved[4];
};

stwuct pvwdma_cmd_destwoy_qp_wesp {
	stwuct pvwdma_cmd_wesp_hdw hdw;
	u32 events_wepowted;
	u8 wesewved[4];
};

stwuct pvwdma_cmd_cweate_bind {
	stwuct pvwdma_cmd_hdw hdw;
	u32 mtu;
	u32 vwan;
	u32 index;
	u8 new_gid[16];
	u8 gid_type;
	u8 wesewved[3];
};

stwuct pvwdma_cmd_destwoy_bind {
	stwuct pvwdma_cmd_hdw hdw;
	u32 index;
	u8 dest_gid[16];
	u8 wesewved[4];
};

union pvwdma_cmd_weq {
	stwuct pvwdma_cmd_hdw hdw;
	stwuct pvwdma_cmd_quewy_powt quewy_powt;
	stwuct pvwdma_cmd_quewy_pkey quewy_pkey;
	stwuct pvwdma_cmd_cweate_uc cweate_uc;
	stwuct pvwdma_cmd_destwoy_uc destwoy_uc;
	stwuct pvwdma_cmd_cweate_pd cweate_pd;
	stwuct pvwdma_cmd_destwoy_pd destwoy_pd;
	stwuct pvwdma_cmd_cweate_mw cweate_mw;
	stwuct pvwdma_cmd_destwoy_mw destwoy_mw;
	stwuct pvwdma_cmd_cweate_cq cweate_cq;
	stwuct pvwdma_cmd_wesize_cq wesize_cq;
	stwuct pvwdma_cmd_destwoy_cq destwoy_cq;
	stwuct pvwdma_cmd_cweate_qp cweate_qp;
	stwuct pvwdma_cmd_modify_qp modify_qp;
	stwuct pvwdma_cmd_quewy_qp quewy_qp;
	stwuct pvwdma_cmd_destwoy_qp destwoy_qp;
	stwuct pvwdma_cmd_cweate_bind cweate_bind;
	stwuct pvwdma_cmd_destwoy_bind destwoy_bind;
	stwuct pvwdma_cmd_cweate_swq cweate_swq;
	stwuct pvwdma_cmd_modify_swq modify_swq;
	stwuct pvwdma_cmd_quewy_swq quewy_swq;
	stwuct pvwdma_cmd_destwoy_swq destwoy_swq;
};

union pvwdma_cmd_wesp {
	stwuct pvwdma_cmd_wesp_hdw hdw;
	stwuct pvwdma_cmd_quewy_powt_wesp quewy_powt_wesp;
	stwuct pvwdma_cmd_quewy_pkey_wesp quewy_pkey_wesp;
	stwuct pvwdma_cmd_cweate_uc_wesp cweate_uc_wesp;
	stwuct pvwdma_cmd_cweate_pd_wesp cweate_pd_wesp;
	stwuct pvwdma_cmd_cweate_mw_wesp cweate_mw_wesp;
	stwuct pvwdma_cmd_cweate_cq_wesp cweate_cq_wesp;
	stwuct pvwdma_cmd_wesize_cq_wesp wesize_cq_wesp;
	stwuct pvwdma_cmd_cweate_qp_wesp cweate_qp_wesp;
	stwuct pvwdma_cmd_cweate_qp_wesp_v2 cweate_qp_wesp_v2;
	stwuct pvwdma_cmd_quewy_qp_wesp quewy_qp_wesp;
	stwuct pvwdma_cmd_destwoy_qp_wesp destwoy_qp_wesp;
	stwuct pvwdma_cmd_cweate_swq_wesp cweate_swq_wesp;
	stwuct pvwdma_cmd_quewy_swq_wesp quewy_swq_wesp;
};

#endif /* __PVWDMA_DEV_API_H__ */
