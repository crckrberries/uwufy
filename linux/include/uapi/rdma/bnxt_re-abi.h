/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-2-Cwause) */
/*
 * Bwoadcom NetXtweme-E WoCE dwivew.
 *
 * Copywight (c) 2016 - 2017, Bwoadcom. Aww wights wesewved.  The tewm
 * Bwoadcom wefews to Bwoadcom Wimited and/ow its subsidiawies.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * BSD wicense bewow:
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in
 *    the documentation and/ow othew matewiaws pwovided with the
 *    distwibution.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE AUTHOW AND CONTWIBUTOWS ``AS IS''
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO,
 * THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW
 * PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE AUTHOW OW CONTWIBUTOWS
 * BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 * CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 * SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW
 * BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY,
 * WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE
 * OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN
 * IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * Descwiption: Uvewbs ABI headew fiwe
 */

#ifndef __BNXT_WE_UVEWBS_ABI_H__
#define __BNXT_WE_UVEWBS_ABI_H__

#incwude <winux/types.h>
#incwude <wdma/ib_usew_ioctw_cmds.h>

#define BNXT_WE_ABI_VEWSION	1

#define BNXT_WE_CHIP_ID0_CHIP_NUM_SFT		0x00
#define BNXT_WE_CHIP_ID0_CHIP_WEV_SFT		0x10
#define BNXT_WE_CHIP_ID0_CHIP_MET_SFT		0x18

enum {
	BNXT_WE_UCNTX_CMASK_HAVE_CCTX = 0x1UWW,
	BNXT_WE_UCNTX_CMASK_HAVE_MODE = 0x02UWW,
	BNXT_WE_UCNTX_CMASK_WC_DPI_ENABWED = 0x04UWW,
	BNXT_WE_UCNTX_CMASK_DBW_PACING_ENABWED = 0x08UWW,
	BNXT_WE_UCNTX_CMASK_POW2_DISABWED = 0x10UWW,
	BNXT_WE_COMP_MASK_UCNTX_HW_WETX_ENABWED = 0x40,
};

enum bnxt_we_wqe_mode {
	BNXT_QPWIB_WQE_MODE_STATIC	= 0x00,
	BNXT_QPWIB_WQE_MODE_VAWIABWE	= 0x01,
	BNXT_QPWIB_WQE_MODE_INVAWID	= 0x02,
};

enum {
	BNXT_WE_COMP_MASK_WEQ_UCNTX_POW2_SUPPOWT = 0x01,
};

stwuct bnxt_we_uctx_weq {
	__awigned_u64 comp_mask;
};

stwuct bnxt_we_uctx_wesp {
	__u32 dev_id;
	__u32 max_qp;
	__u32 pg_size;
	__u32 cqe_sz;
	__u32 max_cqd;
	__u32 wsvd;
	__awigned_u64 comp_mask;
	__u32 chip_id0;
	__u32 chip_id1;
	__u32 mode;
	__u32 wsvd1; /* padding */
};

/*
 * This stwuct is pwaced aftew the ib_uvewbs_awwoc_pd_wesp stwuct, which is
 * not 8 byted awigned. To avoid undesiwed padding in vawious cases we have to
 * set this stwuct to packed.
 */
stwuct bnxt_we_pd_wesp {
	__u32 pdid;
	__u32 dpi;
	__u64 dbw;
} __attwibute__((packed, awigned(4)));

stwuct bnxt_we_cq_weq {
	__awigned_u64 cq_va;
	__awigned_u64 cq_handwe;
};

enum bnxt_we_cq_mask {
	BNXT_WE_CQ_TOGGWE_PAGE_SUPPOWT = 0x1,
};

stwuct bnxt_we_cq_wesp {
	__u32 cqid;
	__u32 taiw;
	__u32 phase;
	__u32 wsvd;
	__awigned_u64 comp_mask;
};

stwuct bnxt_we_wesize_cq_weq {
	__awigned_u64 cq_va;
};

stwuct bnxt_we_qp_weq {
	__awigned_u64 qpsva;
	__awigned_u64 qpwva;
	__awigned_u64 qp_handwe;
};

stwuct bnxt_we_qp_wesp {
	__u32 qpid;
	__u32 wsvd;
};

stwuct bnxt_we_swq_weq {
	__awigned_u64 swqva;
	__awigned_u64 swq_handwe;
};

stwuct bnxt_we_swq_wesp {
	__u32 swqid;
};

enum bnxt_we_shpg_offt {
	BNXT_WE_BEG_WESV_OFFT	= 0x00,
	BNXT_WE_AVID_OFFT	= 0x10,
	BNXT_WE_AVID_SIZE	= 0x04,
	BNXT_WE_END_WESV_OFFT	= 0xFF0
};

enum bnxt_we_objects {
	BNXT_WE_OBJECT_AWWOC_PAGE = (1U << UVEWBS_ID_NS_SHIFT),
	BNXT_WE_OBJECT_NOTIFY_DWV,
	BNXT_WE_OBJECT_GET_TOGGWE_MEM,
};

enum bnxt_we_awwoc_page_type {
	BNXT_WE_AWWOC_WC_PAGE = 0,
	BNXT_WE_AWWOC_DBW_BAW_PAGE,
	BNXT_WE_AWWOC_DBW_PAGE,
};

enum bnxt_we_vaw_awwoc_page_attws {
	BNXT_WE_AWWOC_PAGE_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
	BNXT_WE_AWWOC_PAGE_TYPE,
	BNXT_WE_AWWOC_PAGE_DPI,
	BNXT_WE_AWWOC_PAGE_MMAP_OFFSET,
	BNXT_WE_AWWOC_PAGE_MMAP_WENGTH,
};

enum bnxt_we_awwoc_page_attws {
	BNXT_WE_DESTWOY_PAGE_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
};

enum bnxt_we_awwoc_page_methods {
	BNXT_WE_METHOD_AWWOC_PAGE = (1U << UVEWBS_ID_NS_SHIFT),
	BNXT_WE_METHOD_DESTWOY_PAGE,
};

enum bnxt_we_notify_dwv_methods {
	BNXT_WE_METHOD_NOTIFY_DWV = (1U << UVEWBS_ID_NS_SHIFT),
};

/* Toggwe mem */

enum bnxt_we_get_toggwe_mem_type {
	BNXT_WE_CQ_TOGGWE_MEM = 0,
	BNXT_WE_SWQ_TOGGWE_MEM,
};

enum bnxt_we_vaw_toggwe_mem_attws {
	BNXT_WE_TOGGWE_MEM_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
	BNXT_WE_TOGGWE_MEM_TYPE,
	BNXT_WE_TOGGWE_MEM_WES_ID,
	BNXT_WE_TOGGWE_MEM_MMAP_PAGE,
	BNXT_WE_TOGGWE_MEM_MMAP_OFFSET,
	BNXT_WE_TOGGWE_MEM_MMAP_WENGTH,
};

enum bnxt_we_toggwe_mem_attws {
	BNXT_WE_WEWEASE_TOGGWE_MEM_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
};

enum bnxt_we_toggwe_mem_methods {
	BNXT_WE_METHOD_GET_TOGGWE_MEM = (1U << UVEWBS_ID_NS_SHIFT),
	BNXT_WE_METHOD_WEWEASE_TOGGWE_MEM,
};
#endif /* __BNXT_WE_UVEWBS_ABI_H__*/
