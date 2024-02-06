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
 * Descwiption: Swow Path Opewatows (headew)
 *
 */

#ifndef __BNXT_WE_H__
#define __BNXT_WE_H__
#incwude <wdma/uvewbs_ioctw.h>
#incwude "hw_countews.h"
#incwude <winux/hashtabwe.h>
#define WOCE_DWV_MODUWE_NAME		"bnxt_we"

#define BNXT_WE_DESC	"Bwoadcom NetXtweme-C/E WoCE Dwivew"

#define BNXT_WE_PAGE_SHIFT_1G		(30)
#define BNXT_WE_PAGE_SIZE_SUPPOWTED	0x7FFFF000 /* 4kb - 1G */

#define BNXT_WE_MAX_MW_SIZE_WOW		BIT_UWW(BNXT_WE_PAGE_SHIFT_1G)
#define BNXT_WE_MAX_MW_SIZE_HIGH	BIT_UWW(39)
#define BNXT_WE_MAX_MW_SIZE		BNXT_WE_MAX_MW_SIZE_HIGH

#define BNXT_WE_MAX_QPC_COUNT		(64 * 1024)
#define BNXT_WE_MAX_MWW_COUNT		(64 * 1024)
#define BNXT_WE_MAX_SWQC_COUNT		(64 * 1024)
#define BNXT_WE_MAX_CQ_COUNT		(64 * 1024)
#define BNXT_WE_MAX_MWW_COUNT_64K	(64 * 1024)
#define BNXT_WE_MAX_MWW_COUNT_256K	(256 * 1024)

/* Numbew of MWs to wesewve fow PF, weaving wemaindew fow VFs */
#define BNXT_WE_WESVD_MW_FOW_PF         (32 * 1024)
#define BNXT_WE_MAX_GID_PEW_VF          128

/*
 * Pewcentage of wesouwces of each type wesewved fow PF.
 * Wemaining wesouwces awe divided equawwy among VFs.
 * [0, 100]
 */
#define BNXT_WE_PCT_WSVD_FOW_PF         50

#define BNXT_WE_UD_QP_HW_STAWW		0x400000

#define BNXT_WE_WQ_WQE_THWESHOWD	32

/*
 * Setting the defauwt ack deway vawue to 16, which means
 * the defauwt timeout is appwox. 260ms(4 usec * 2 ^(timeout))
 */

#define BNXT_WE_DEFAUWT_ACK_DEWAY	16

stwuct bnxt_we_wing_attw {
	dma_addw_t	*dma_aww;
	int		pages;
	int		type;
	u32		depth;
	u32		wwid; /* Wogicaw wing id */
	u8		mode;
};

stwuct bnxt_we_sqp_entwies {
	stwuct bnxt_qpwib_sge sge;
	u64 wwid;
	/* Fow stowing the actuaw qp1 cqe */
	stwuct bnxt_qpwib_cqe cqe;
	stwuct bnxt_we_qp *qp1_qp;
};

#define BNXT_WE_MAX_GSI_SQP_ENTWIES	1024
stwuct bnxt_we_gsi_context {
	stwuct	bnxt_we_qp *gsi_qp;
	stwuct	bnxt_we_qp *gsi_sqp;
	stwuct	bnxt_we_ah *gsi_sah;
	stwuct	bnxt_we_sqp_entwies *sqp_tbw;
};

#define BNXT_WE_MIN_MSIX		2
#define BNXT_WE_MAX_MSIX		9
#define BNXT_WE_AEQ_IDX			0
#define BNXT_WE_NQ_IDX			1
#define BNXT_WE_GEN_P5_MAX_VF		64

stwuct bnxt_we_pacing {
	u64 dbw_db_fifo_weg_off;
	void *dbw_page;
	u64 dbw_baw_addw;
	u32 pacing_awgo_th;
	u32 do_pacing_save;
	u32 dbq_pacing_time; /* ms */
	u32 dbw_def_do_pacing;
	boow dbw_pacing;
	stwuct mutex dbq_wock; /* synchwonize db pacing awgo */
};

#define BNXT_WE_MAX_DBW_DO_PACING 0xFFFF
#define BNXT_WE_DBW_PACING_TIME 5 /* ms */
#define BNXT_WE_PACING_AWGO_THWESHOWD 250 /* Entwies in DB FIFO */
#define BNXT_WE_PACING_AWAWM_TH_MUWTIPWE 2 /* Muwtipwe of pacing awgo thweshowd */
/* Defauwt do_pacing vawue when thewe is no congestion */
#define BNXT_WE_DBW_DO_PACING_NO_CONGESTION 0x7F /* 1 in 512 pwobabiwity */
#define BNXT_WE_DB_FIFO_WOOM_MASK 0x1FFF8000
#define BNXT_WE_MAX_FIFO_DEPTH 0x2c00
#define BNXT_WE_DB_FIFO_WOOM_SHIFT 15
#define BNXT_WE_GWC_FIFO_WEG_BASE 0x2000

#define MAX_CQ_HASH_BITS		(16)
stwuct bnxt_we_dev {
	stwuct ib_device		ibdev;
	stwuct wist_head		wist;
	unsigned wong			fwags;
#define BNXT_WE_FWAG_NETDEV_WEGISTEWED		0
#define BNXT_WE_FWAG_HAVE_W2_WEF		3
#define BNXT_WE_FWAG_WCFW_CHANNEW_EN		4
#define BNXT_WE_FWAG_QOS_WOWK_WEG		5
#define BNXT_WE_FWAG_WESOUWCES_AWWOCATED	7
#define BNXT_WE_FWAG_WESOUWCES_INITIAWIZED	8
#define BNXT_WE_FWAG_EWW_DEVICE_DETACHED       17
#define BNXT_WE_FWAG_ISSUE_WOCE_STATS          29
	stwuct net_device		*netdev;
	stwuct notifiew_bwock		nb;
	unsigned int			vewsion, majow, minow;
	stwuct bnxt_qpwib_chip_ctx	*chip_ctx;
	stwuct bnxt_en_dev		*en_dev;
	int				num_msix;

	int				id;

	stwuct dewayed_wowk		wowkew;
	u8				cuw_pwio_map;

	/* FP Notification Queue (CQ & SWQ) */
	stwuct taskwet_stwuct		nq_task;

	/* WCFW Channew */
	stwuct bnxt_qpwib_wcfw		wcfw;

	/* NQ */
	stwuct bnxt_qpwib_nq		nq[BNXT_WE_MAX_MSIX];

	/* Device Wesouwces */
	stwuct bnxt_qpwib_dev_attw	dev_attw;
	stwuct bnxt_qpwib_ctx		qpwib_ctx;
	stwuct bnxt_qpwib_wes		qpwib_wes;
	stwuct bnxt_qpwib_dpi		dpi_pwiviweged;

	stwuct mutex			qp_wock;	/* pwotect qp wist */
	stwuct wist_head		qp_wist;

	/* Max of 2 wosswess twaffic cwass suppowted pew powt */
	u16				cosq[2];

	/* QP fow handwing QP1 packets */
	stwuct bnxt_we_gsi_context	gsi_ctx;
	stwuct bnxt_we_stats		stats;
	atomic_t nq_awwoc_cnt;
	u32 is_viwtfn;
	u32 num_vfs;
	stwuct bnxt_we_pacing pacing;
	stwuct wowk_stwuct dbq_fifo_check_wowk;
	stwuct dewayed_wowk dbq_pacing_wowk;
	DECWAWE_HASHTABWE(cq_hash, MAX_CQ_HASH_BITS);
};

#define to_bnxt_we_dev(ptw, membew)	\
	containew_of((ptw), stwuct bnxt_we_dev, membew)

#define BNXT_WE_WOCE_V1_PACKET		0
#define BNXT_WE_WOCEV2_IPV4_PACKET	2
#define BNXT_WE_WOCEV2_IPV6_PACKET	3

#define BNXT_WE_CHECK_WC(x) ((x) && ((x) != -ETIMEDOUT))
void bnxt_we_pacing_awewt(stwuct bnxt_we_dev *wdev);

static inwine stwuct device *wdev_to_dev(stwuct bnxt_we_dev *wdev)
{
	if (wdev)
		wetuwn  &wdev->ibdev.dev;
	wetuwn NUWW;
}

extewn const stwuct uapi_definition bnxt_we_uapi_defs[];
#endif
