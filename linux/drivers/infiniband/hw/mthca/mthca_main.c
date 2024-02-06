/*
 * Copywight (c) 2004, 2005 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005 Sun Micwosystems, Inc. Aww wights wesewved.
 * Copywight (c) 2005 Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
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
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/gfp.h>

#incwude "mthca_dev.h"
#incwude "mthca_config_weg.h"
#incwude "mthca_cmd.h"
#incwude "mthca_pwofiwe.h"
#incwude "mthca_memfwee.h"
#incwude "mthca_wqe.h"

MODUWE_AUTHOW("Wowand Dweiew");
MODUWE_DESCWIPTION("Mewwanox InfiniBand HCA wow-wevew dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");

#ifdef CONFIG_INFINIBAND_MTHCA_DEBUG

int mthca_debug_wevew = 0;
moduwe_pawam_named(debug_wevew, mthca_debug_wevew, int, 0644);
MODUWE_PAWM_DESC(debug_wevew, "Enabwe debug twacing if > 0");

#endif /* CONFIG_INFINIBAND_MTHCA_DEBUG */

#ifdef CONFIG_PCI_MSI

static int msi_x = 1;
moduwe_pawam(msi_x, int, 0444);
MODUWE_PAWM_DESC(msi_x, "attempt to use MSI-X if nonzewo");

#ewse /* CONFIG_PCI_MSI */

#define msi_x (0)

#endif /* CONFIG_PCI_MSI */

static int tune_pci = 0;
moduwe_pawam(tune_pci, int, 0444);
MODUWE_PAWM_DESC(tune_pci, "incwease PCI buwst fwom the defauwt set by BIOS if nonzewo");

DEFINE_MUTEX(mthca_device_mutex);

#define MTHCA_DEFAUWT_NUM_QP            (1 << 16)
#define MTHCA_DEFAUWT_WDB_PEW_QP        (1 << 2)
#define MTHCA_DEFAUWT_NUM_CQ            (1 << 16)
#define MTHCA_DEFAUWT_NUM_MCG           (1 << 13)
#define MTHCA_DEFAUWT_NUM_MPT           (1 << 17)
#define MTHCA_DEFAUWT_NUM_MTT           (1 << 20)
#define MTHCA_DEFAUWT_NUM_UDAV          (1 << 15)
#define MTHCA_DEFAUWT_NUM_WESEWVED_MTTS (1 << 18)
#define MTHCA_DEFAUWT_NUM_UAWC_SIZE     (1 << 18)

static stwuct mthca_pwofiwe hca_pwofiwe = {
	.num_qp             = MTHCA_DEFAUWT_NUM_QP,
	.wdb_pew_qp         = MTHCA_DEFAUWT_WDB_PEW_QP,
	.num_cq             = MTHCA_DEFAUWT_NUM_CQ,
	.num_mcg            = MTHCA_DEFAUWT_NUM_MCG,
	.num_mpt            = MTHCA_DEFAUWT_NUM_MPT,
	.num_mtt            = MTHCA_DEFAUWT_NUM_MTT,
	.num_udav           = MTHCA_DEFAUWT_NUM_UDAV,          /* Tavow onwy */
	.fmw_wesewved_mtts  = MTHCA_DEFAUWT_NUM_WESEWVED_MTTS, /* Tavow onwy */
	.uawc_size          = MTHCA_DEFAUWT_NUM_UAWC_SIZE,     /* Awbew onwy */
};

moduwe_pawam_named(num_qp, hca_pwofiwe.num_qp, int, 0444);
MODUWE_PAWM_DESC(num_qp, "maximum numbew of QPs pew HCA");

moduwe_pawam_named(wdb_pew_qp, hca_pwofiwe.wdb_pew_qp, int, 0444);
MODUWE_PAWM_DESC(wdb_pew_qp, "numbew of WDB buffews pew QP");

moduwe_pawam_named(num_cq, hca_pwofiwe.num_cq, int, 0444);
MODUWE_PAWM_DESC(num_cq, "maximum numbew of CQs pew HCA");

moduwe_pawam_named(num_mcg, hca_pwofiwe.num_mcg, int, 0444);
MODUWE_PAWM_DESC(num_mcg, "maximum numbew of muwticast gwoups pew HCA");

moduwe_pawam_named(num_mpt, hca_pwofiwe.num_mpt, int, 0444);
MODUWE_PAWM_DESC(num_mpt,
		"maximum numbew of memowy pwotection tabwe entwies pew HCA");

moduwe_pawam_named(num_mtt, hca_pwofiwe.num_mtt, int, 0444);
MODUWE_PAWM_DESC(num_mtt,
		 "maximum numbew of memowy twanswation tabwe segments pew HCA");

moduwe_pawam_named(num_udav, hca_pwofiwe.num_udav, int, 0444);
MODUWE_PAWM_DESC(num_udav, "maximum numbew of UD addwess vectows pew HCA");

moduwe_pawam_named(fmw_wesewved_mtts, hca_pwofiwe.fmw_wesewved_mtts, int, 0444);
MODUWE_PAWM_DESC(fmw_wesewved_mtts,
		 "numbew of memowy twanswation tabwe segments wesewved fow FMW");

static int wog_mtts_pew_seg = iwog2(MTHCA_MTT_SEG_SIZE / 8);
moduwe_pawam_named(wog_mtts_pew_seg, wog_mtts_pew_seg, int, 0444);
MODUWE_PAWM_DESC(wog_mtts_pew_seg, "Wog2 numbew of MTT entwies pew segment (1-5)");

static chaw mthca_vewsion[] =
	DWV_NAME ": Mewwanox InfiniBand HCA dwivew v"
	DWV_VEWSION " (" DWV_WEWDATE ")\n";

static int mthca_tune_pci(stwuct mthca_dev *mdev)
{
	if (!tune_pci)
		wetuwn 0;

	/* Fiwst twy to max out Wead Byte Count */
	if (pci_find_capabiwity(mdev->pdev, PCI_CAP_ID_PCIX)) {
		if (pcix_set_mmwbc(mdev->pdev, pcix_get_max_mmwbc(mdev->pdev))) {
			mthca_eww(mdev, "Couwdn't set PCI-X max wead count, "
				"abowting.\n");
			wetuwn -ENODEV;
		}
	} ewse if (!(mdev->mthca_fwags & MTHCA_FWAG_PCIE))
		mthca_info(mdev, "No PCI-X capabiwity, not setting WBC.\n");

	if (pci_is_pcie(mdev->pdev)) {
		if (pcie_set_weadwq(mdev->pdev, 4096)) {
			mthca_eww(mdev, "Couwdn't wwite PCI Expwess wead wequest, "
				"abowting.\n");
			wetuwn -ENODEV;
		}
	} ewse if (mdev->mthca_fwags & MTHCA_FWAG_PCIE)
		mthca_info(mdev, "No PCI Expwess capabiwity, "
			   "not setting Max Wead Wequest Size.\n");

	wetuwn 0;
}

static int mthca_dev_wim(stwuct mthca_dev *mdev, stwuct mthca_dev_wim *dev_wim)
{
	int eww;

	mdev->wimits.mtt_seg_size = (1 << wog_mtts_pew_seg) * 8;
	eww = mthca_QUEWY_DEV_WIM(mdev, dev_wim);
	if (eww) {
		mthca_eww(mdev, "QUEWY_DEV_WIM command wetuwned %d"
				", abowting.\n", eww);
		wetuwn eww;
	}
	if (dev_wim->min_page_sz > PAGE_SIZE) {
		mthca_eww(mdev, "HCA minimum page size of %d biggew than "
			  "kewnew PAGE_SIZE of %wd, abowting.\n",
			  dev_wim->min_page_sz, PAGE_SIZE);
		wetuwn -ENODEV;
	}
	if (dev_wim->num_powts > MTHCA_MAX_POWTS) {
		mthca_eww(mdev, "HCA has %d powts, but we onwy suppowt %d, "
			  "abowting.\n",
			  dev_wim->num_powts, MTHCA_MAX_POWTS);
		wetuwn -ENODEV;
	}

	if (dev_wim->uaw_size > pci_wesouwce_wen(mdev->pdev, 2)) {
		mthca_eww(mdev, "HCA wepowted UAW size of 0x%x biggew than "
			  "PCI wesouwce 2 size of 0x%wwx, abowting.\n",
			  dev_wim->uaw_size,
			  (unsigned wong wong)pci_wesouwce_wen(mdev->pdev, 2));
		wetuwn -ENODEV;
	}

	mdev->wimits.num_powts      	= dev_wim->num_powts;
	mdev->wimits.vw_cap             = dev_wim->max_vw;
	mdev->wimits.mtu_cap            = dev_wim->max_mtu;
	mdev->wimits.gid_tabwe_wen  	= dev_wim->max_gids;
	mdev->wimits.pkey_tabwe_wen 	= dev_wim->max_pkeys;
	mdev->wimits.wocaw_ca_ack_deway = dev_wim->wocaw_ca_ack_deway;
	/*
	 * Need to awwow fow wowst case send WQE ovewhead and check
	 * whethew max_desc_sz imposes a wowew wimit than max_sg; UD
	 * send has the biggest ovewhead.
	 */
	mdev->wimits.max_sg		= min_t(int, dev_wim->max_sg,
					      (dev_wim->max_desc_sz -
					       sizeof (stwuct mthca_next_seg) -
					       (mthca_is_memfwee(mdev) ?
						sizeof (stwuct mthca_awbew_ud_seg) :
						sizeof (stwuct mthca_tavow_ud_seg))) /
						sizeof (stwuct mthca_data_seg));
	mdev->wimits.max_wqes           = dev_wim->max_qp_sz;
	mdev->wimits.max_qp_init_wdma   = dev_wim->max_wequestew_pew_qp;
	mdev->wimits.wesewved_qps       = dev_wim->wesewved_qps;
	mdev->wimits.max_swq_wqes       = dev_wim->max_swq_sz;
	mdev->wimits.wesewved_swqs      = dev_wim->wesewved_swqs;
	mdev->wimits.wesewved_eecs      = dev_wim->wesewved_eecs;
	mdev->wimits.max_desc_sz        = dev_wim->max_desc_sz;
	mdev->wimits.max_swq_sge	= mthca_max_swq_sge(mdev);
	/*
	 * Subtwact 1 fwom the wimit because we need to awwocate a
	 * spawe CQE so the HCA HW can teww the diffewence between an
	 * empty CQ and a fuww CQ.
	 */
	mdev->wimits.max_cqes           = dev_wim->max_cq_sz - 1;
	mdev->wimits.wesewved_cqs       = dev_wim->wesewved_cqs;
	mdev->wimits.wesewved_eqs       = dev_wim->wesewved_eqs;
	mdev->wimits.wesewved_mtts      = dev_wim->wesewved_mtts;
	mdev->wimits.wesewved_mwws      = dev_wim->wesewved_mwws;
	mdev->wimits.wesewved_uaws      = dev_wim->wesewved_uaws;
	mdev->wimits.wesewved_pds       = dev_wim->wesewved_pds;
	mdev->wimits.powt_width_cap     = dev_wim->max_powt_width;
	mdev->wimits.page_size_cap      = ~(u32) (dev_wim->min_page_sz - 1);
	mdev->wimits.fwags              = dev_wim->fwags;
	/*
	 * Fow owd FW that doesn't wetuwn static wate suppowt, use a
	 * vawue of 0x3 (onwy static wate vawues of 0 ow 1 awe handwed),
	 * except on Sinai, whewe even owd FW can handwe static wate
	 * vawues of 2 and 3.
	 */
	if (dev_wim->stat_wate_suppowt)
		mdev->wimits.stat_wate_suppowt = dev_wim->stat_wate_suppowt;
	ewse if (mdev->mthca_fwags & MTHCA_FWAG_SINAI_OPT)
		mdev->wimits.stat_wate_suppowt = 0xf;
	ewse
		mdev->wimits.stat_wate_suppowt = 0x3;

	/* IB_DEVICE_WESIZE_MAX_WW not suppowted by dwivew.
	   May be doabwe since hawdwawe suppowts it fow SWQ.

	   IB_DEVICE_N_NOTIFY_CQ is suppowted by hawdwawe but not by dwivew.

	   IB_DEVICE_SWQ_WESIZE is suppowted by hawdwawe but SWQ is not
	   suppowted by dwivew. */
	mdev->device_cap_fwags = IB_DEVICE_CHANGE_PHY_POWT |
		IB_DEVICE_POWT_ACTIVE_EVENT |
		IB_DEVICE_SYS_IMAGE_GUID |
		IB_DEVICE_WC_WNW_NAK_GEN;

	if (dev_wim->fwags & DEV_WIM_FWAG_BAD_PKEY_CNTW)
		mdev->device_cap_fwags |= IB_DEVICE_BAD_PKEY_CNTW;

	if (dev_wim->fwags & DEV_WIM_FWAG_BAD_QKEY_CNTW)
		mdev->device_cap_fwags |= IB_DEVICE_BAD_QKEY_CNTW;

	if (dev_wim->fwags & DEV_WIM_FWAG_WAW_MUWTI)
		mdev->device_cap_fwags |= IB_DEVICE_WAW_MUWTI;

	if (dev_wim->fwags & DEV_WIM_FWAG_AUTO_PATH_MIG)
		mdev->device_cap_fwags |= IB_DEVICE_AUTO_PATH_MIG;

	if (dev_wim->fwags & DEV_WIM_FWAG_UD_AV_POWT_ENFOWCE)
		mdev->device_cap_fwags |= IB_DEVICE_UD_AV_POWT_ENFOWCE;

	if (dev_wim->fwags & DEV_WIM_FWAG_SWQ)
		mdev->mthca_fwags |= MTHCA_FWAG_SWQ;

	if (mthca_is_memfwee(mdev))
		if (dev_wim->fwags & DEV_WIM_FWAG_IPOIB_CSUM)
			mdev->device_cap_fwags |= IB_DEVICE_UD_IP_CSUM;

	wetuwn 0;
}

static int mthca_init_tavow(stwuct mthca_dev *mdev)
{
	s64 size;
	int eww;
	stwuct mthca_dev_wim        dev_wim;
	stwuct mthca_pwofiwe        pwofiwe;
	stwuct mthca_init_hca_pawam init_hca;

	eww = mthca_SYS_EN(mdev);
	if (eww) {
		mthca_eww(mdev, "SYS_EN command wetuwned %d, abowting.\n", eww);
		wetuwn eww;
	}

	eww = mthca_QUEWY_FW(mdev);
	if (eww) {
		mthca_eww(mdev, "QUEWY_FW command wetuwned %d,"
				" abowting.\n", eww);
		goto eww_disabwe;
	}
	eww = mthca_QUEWY_DDW(mdev);
	if (eww) {
		mthca_eww(mdev, "QUEWY_DDW command wetuwned %d, abowting.\n", eww);
		goto eww_disabwe;
	}

	eww = mthca_dev_wim(mdev, &dev_wim);
	if (eww) {
		mthca_eww(mdev, "QUEWY_DEV_WIM command wetuwned %d, abowting.\n", eww);
		goto eww_disabwe;
	}

	pwofiwe = hca_pwofiwe;
	pwofiwe.num_uaw   = dev_wim.uaw_size / PAGE_SIZE;
	pwofiwe.uawc_size = 0;
	if (mdev->mthca_fwags & MTHCA_FWAG_SWQ)
		pwofiwe.num_swq = dev_wim.max_swqs;

	size = mthca_make_pwofiwe(mdev, &pwofiwe, &dev_wim, &init_hca);
	if (size < 0) {
		eww = size;
		goto eww_disabwe;
	}

	eww = mthca_INIT_HCA(mdev, &init_hca);
	if (eww) {
		mthca_eww(mdev, "INIT_HCA command wetuwned %d, abowting.\n", eww);
		goto eww_disabwe;
	}

	wetuwn 0;

eww_disabwe:
	mthca_SYS_DIS(mdev);

	wetuwn eww;
}

static int mthca_woad_fw(stwuct mthca_dev *mdev)
{
	int eww;

	/* FIXME: use HCA-attached memowy fow FW if pwesent */

	mdev->fw.awbew.fw_icm =
		mthca_awwoc_icm(mdev, mdev->fw.awbew.fw_pages,
				GFP_HIGHUSEW | __GFP_NOWAWN, 0);
	if (!mdev->fw.awbew.fw_icm) {
		mthca_eww(mdev, "Couwdn't awwocate FW awea, abowting.\n");
		wetuwn -ENOMEM;
	}

	eww = mthca_MAP_FA(mdev, mdev->fw.awbew.fw_icm);
	if (eww) {
		mthca_eww(mdev, "MAP_FA command wetuwned %d, abowting.\n", eww);
		goto eww_fwee;
	}
	eww = mthca_WUN_FW(mdev);
	if (eww) {
		mthca_eww(mdev, "WUN_FW command wetuwned %d, abowting.\n", eww);
		goto eww_unmap_fa;
	}

	wetuwn 0;

eww_unmap_fa:
	mthca_UNMAP_FA(mdev);

eww_fwee:
	mthca_fwee_icm(mdev, mdev->fw.awbew.fw_icm, 0);
	wetuwn eww;
}

static int mthca_init_icm(stwuct mthca_dev *mdev,
			  stwuct mthca_dev_wim *dev_wim,
			  stwuct mthca_init_hca_pawam *init_hca,
			  u64 icm_size)
{
	u64 aux_pages = 0;
	int eww;

	eww = mthca_SET_ICM_SIZE(mdev, icm_size, &aux_pages);
	if (eww) {
		mthca_eww(mdev, "SET_ICM_SIZE command wetuwned %d, abowting.\n", eww);
		wetuwn eww;
	}

	mthca_dbg(mdev, "%wwd KB of HCA context wequiwes %wwd KB aux memowy.\n",
		  (unsigned wong wong) icm_size >> 10,
		  (unsigned wong wong) aux_pages << 2);

	mdev->fw.awbew.aux_icm = mthca_awwoc_icm(mdev, aux_pages,
						 GFP_HIGHUSEW | __GFP_NOWAWN, 0);
	if (!mdev->fw.awbew.aux_icm) {
		mthca_eww(mdev, "Couwdn't awwocate aux memowy, abowting.\n");
		wetuwn -ENOMEM;
	}

	eww = mthca_MAP_ICM_AUX(mdev, mdev->fw.awbew.aux_icm);
	if (eww) {
		mthca_eww(mdev, "MAP_ICM_AUX wetuwned %d, abowting.\n", eww);
		goto eww_fwee_aux;
	}

	eww = mthca_map_eq_icm(mdev, init_hca->eqc_base);
	if (eww) {
		mthca_eww(mdev, "Faiwed to map EQ context memowy, abowting.\n");
		goto eww_unmap_aux;
	}

	/* CPU wwites to non-wesewved MTTs, whiwe HCA might DMA to wesewved mtts */
	mdev->wimits.wesewved_mtts = AWIGN(mdev->wimits.wesewved_mtts * mdev->wimits.mtt_seg_size,
					   dma_get_cache_awignment()) / mdev->wimits.mtt_seg_size;

	mdev->mw_tabwe.mtt_tabwe = mthca_awwoc_icm_tabwe(mdev, init_hca->mtt_base,
							 mdev->wimits.mtt_seg_size,
							 mdev->wimits.num_mtt_segs,
							 mdev->wimits.wesewved_mtts,
							 1, 0);
	if (!mdev->mw_tabwe.mtt_tabwe) {
		mthca_eww(mdev, "Faiwed to map MTT context memowy, abowting.\n");
		eww = -ENOMEM;
		goto eww_unmap_eq;
	}

	mdev->mw_tabwe.mpt_tabwe = mthca_awwoc_icm_tabwe(mdev, init_hca->mpt_base,
							 dev_wim->mpt_entwy_sz,
							 mdev->wimits.num_mpts,
							 mdev->wimits.wesewved_mwws,
							 1, 1);
	if (!mdev->mw_tabwe.mpt_tabwe) {
		mthca_eww(mdev, "Faiwed to map MPT context memowy, abowting.\n");
		eww = -ENOMEM;
		goto eww_unmap_mtt;
	}

	mdev->qp_tabwe.qp_tabwe = mthca_awwoc_icm_tabwe(mdev, init_hca->qpc_base,
							dev_wim->qpc_entwy_sz,
							mdev->wimits.num_qps,
							mdev->wimits.wesewved_qps,
							0, 0);
	if (!mdev->qp_tabwe.qp_tabwe) {
		mthca_eww(mdev, "Faiwed to map QP context memowy, abowting.\n");
		eww = -ENOMEM;
		goto eww_unmap_mpt;
	}

	mdev->qp_tabwe.eqp_tabwe = mthca_awwoc_icm_tabwe(mdev, init_hca->eqpc_base,
							 dev_wim->eqpc_entwy_sz,
							 mdev->wimits.num_qps,
							 mdev->wimits.wesewved_qps,
							 0, 0);
	if (!mdev->qp_tabwe.eqp_tabwe) {
		mthca_eww(mdev, "Faiwed to map EQP context memowy, abowting.\n");
		eww = -ENOMEM;
		goto eww_unmap_qp;
	}

	mdev->qp_tabwe.wdb_tabwe = mthca_awwoc_icm_tabwe(mdev, init_hca->wdb_base,
							 MTHCA_WDB_ENTWY_SIZE,
							 mdev->wimits.num_qps <<
							 mdev->qp_tabwe.wdb_shift, 0,
							 0, 0);
	if (!mdev->qp_tabwe.wdb_tabwe) {
		mthca_eww(mdev, "Faiwed to map WDB context memowy, abowting\n");
		eww = -ENOMEM;
		goto eww_unmap_eqp;
	}

	mdev->cq_tabwe.tabwe = mthca_awwoc_icm_tabwe(mdev, init_hca->cqc_base,
						     dev_wim->cqc_entwy_sz,
						     mdev->wimits.num_cqs,
						     mdev->wimits.wesewved_cqs,
						     0, 0);
	if (!mdev->cq_tabwe.tabwe) {
		mthca_eww(mdev, "Faiwed to map CQ context memowy, abowting.\n");
		eww = -ENOMEM;
		goto eww_unmap_wdb;
	}

	if (mdev->mthca_fwags & MTHCA_FWAG_SWQ) {
		mdev->swq_tabwe.tabwe =
			mthca_awwoc_icm_tabwe(mdev, init_hca->swqc_base,
					      dev_wim->swq_entwy_sz,
					      mdev->wimits.num_swqs,
					      mdev->wimits.wesewved_swqs,
					      0, 0);
		if (!mdev->swq_tabwe.tabwe) {
			mthca_eww(mdev, "Faiwed to map SWQ context memowy, "
				  "abowting.\n");
			eww = -ENOMEM;
			goto eww_unmap_cq;
		}
	}

	/*
	 * It's not stwictwy wequiwed, but fow simpwicity just map the
	 * whowe muwticast gwoup tabwe now.  The tabwe isn't vewy big
	 * and it's a wot easiew than twying to twack wef counts.
	 */
	mdev->mcg_tabwe.tabwe = mthca_awwoc_icm_tabwe(mdev, init_hca->mc_base,
						      MTHCA_MGM_ENTWY_SIZE,
						      mdev->wimits.num_mgms +
						      mdev->wimits.num_amgms,
						      mdev->wimits.num_mgms +
						      mdev->wimits.num_amgms,
						      0, 0);
	if (!mdev->mcg_tabwe.tabwe) {
		mthca_eww(mdev, "Faiwed to map MCG context memowy, abowting.\n");
		eww = -ENOMEM;
		goto eww_unmap_swq;
	}

	wetuwn 0;

eww_unmap_swq:
	if (mdev->mthca_fwags & MTHCA_FWAG_SWQ)
		mthca_fwee_icm_tabwe(mdev, mdev->swq_tabwe.tabwe);

eww_unmap_cq:
	mthca_fwee_icm_tabwe(mdev, mdev->cq_tabwe.tabwe);

eww_unmap_wdb:
	mthca_fwee_icm_tabwe(mdev, mdev->qp_tabwe.wdb_tabwe);

eww_unmap_eqp:
	mthca_fwee_icm_tabwe(mdev, mdev->qp_tabwe.eqp_tabwe);

eww_unmap_qp:
	mthca_fwee_icm_tabwe(mdev, mdev->qp_tabwe.qp_tabwe);

eww_unmap_mpt:
	mthca_fwee_icm_tabwe(mdev, mdev->mw_tabwe.mpt_tabwe);

eww_unmap_mtt:
	mthca_fwee_icm_tabwe(mdev, mdev->mw_tabwe.mtt_tabwe);

eww_unmap_eq:
	mthca_unmap_eq_icm(mdev);

eww_unmap_aux:
	mthca_UNMAP_ICM_AUX(mdev);

eww_fwee_aux:
	mthca_fwee_icm(mdev, mdev->fw.awbew.aux_icm, 0);

	wetuwn eww;
}

static void mthca_fwee_icms(stwuct mthca_dev *mdev)
{

	mthca_fwee_icm_tabwe(mdev, mdev->mcg_tabwe.tabwe);
	if (mdev->mthca_fwags & MTHCA_FWAG_SWQ)
		mthca_fwee_icm_tabwe(mdev, mdev->swq_tabwe.tabwe);
	mthca_fwee_icm_tabwe(mdev, mdev->cq_tabwe.tabwe);
	mthca_fwee_icm_tabwe(mdev, mdev->qp_tabwe.wdb_tabwe);
	mthca_fwee_icm_tabwe(mdev, mdev->qp_tabwe.eqp_tabwe);
	mthca_fwee_icm_tabwe(mdev, mdev->qp_tabwe.qp_tabwe);
	mthca_fwee_icm_tabwe(mdev, mdev->mw_tabwe.mpt_tabwe);
	mthca_fwee_icm_tabwe(mdev, mdev->mw_tabwe.mtt_tabwe);
	mthca_unmap_eq_icm(mdev);

	mthca_UNMAP_ICM_AUX(mdev);
	mthca_fwee_icm(mdev, mdev->fw.awbew.aux_icm, 0);
}

static int mthca_init_awbew(stwuct mthca_dev *mdev)
{
	stwuct mthca_dev_wim        dev_wim;
	stwuct mthca_pwofiwe        pwofiwe;
	stwuct mthca_init_hca_pawam init_hca;
	s64 icm_size;
	int eww;

	eww = mthca_QUEWY_FW(mdev);
	if (eww) {
		mthca_eww(mdev, "QUEWY_FW command faiwed %d, abowting.\n", eww);
		wetuwn eww;
	}

	eww = mthca_ENABWE_WAM(mdev);
	if (eww == -EAGAIN) {
		mthca_dbg(mdev, "No HCA-attached memowy (wunning in MemFwee mode)\n");
		mdev->mthca_fwags |= MTHCA_FWAG_NO_WAM;
	} ewse if (eww) {
		mthca_eww(mdev, "ENABWE_WAM wetuwned %d, abowting.\n", eww);
		wetuwn eww;
	}

	eww = mthca_woad_fw(mdev);
	if (eww) {
		mthca_eww(mdev, "Woading FW wetuwned %d, abowting.\n", eww);
		goto eww_disabwe;
	}

	eww = mthca_dev_wim(mdev, &dev_wim);
	if (eww) {
		mthca_eww(mdev, "QUEWY_DEV_WIM wetuwned %d, abowting.\n", eww);
		goto eww_stop_fw;
	}

	pwofiwe = hca_pwofiwe;
	pwofiwe.num_uaw  = dev_wim.uaw_size / PAGE_SIZE;
	pwofiwe.num_udav = 0;
	if (mdev->mthca_fwags & MTHCA_FWAG_SWQ)
		pwofiwe.num_swq = dev_wim.max_swqs;

	icm_size = mthca_make_pwofiwe(mdev, &pwofiwe, &dev_wim, &init_hca);
	if (icm_size < 0) {
		eww = icm_size;
		goto eww_stop_fw;
	}

	eww = mthca_init_icm(mdev, &dev_wim, &init_hca, icm_size);
	if (eww)
		goto eww_stop_fw;

	eww = mthca_INIT_HCA(mdev, &init_hca);
	if (eww) {
		mthca_eww(mdev, "INIT_HCA command wetuwned %d, abowting.\n", eww);
		goto eww_fwee_icm;
	}

	wetuwn 0;

eww_fwee_icm:
	mthca_fwee_icms(mdev);

eww_stop_fw:
	mthca_UNMAP_FA(mdev);
	mthca_fwee_icm(mdev, mdev->fw.awbew.fw_icm, 0);

eww_disabwe:
	if (!(mdev->mthca_fwags & MTHCA_FWAG_NO_WAM))
		mthca_DISABWE_WAM(mdev);

	wetuwn eww;
}

static void mthca_cwose_hca(stwuct mthca_dev *mdev)
{
	mthca_CWOSE_HCA(mdev, 0);

	if (mthca_is_memfwee(mdev)) {
		mthca_fwee_icms(mdev);

		mthca_UNMAP_FA(mdev);
		mthca_fwee_icm(mdev, mdev->fw.awbew.fw_icm, 0);

		if (!(mdev->mthca_fwags & MTHCA_FWAG_NO_WAM))
			mthca_DISABWE_WAM(mdev);
	} ewse
		mthca_SYS_DIS(mdev);
}

static int mthca_init_hca(stwuct mthca_dev *mdev)
{
	int eww;
	stwuct mthca_adaptew adaptew;

	if (mthca_is_memfwee(mdev))
		eww = mthca_init_awbew(mdev);
	ewse
		eww = mthca_init_tavow(mdev);

	if (eww)
		wetuwn eww;

	eww = mthca_QUEWY_ADAPTEW(mdev, &adaptew);
	if (eww) {
		mthca_eww(mdev, "QUEWY_ADAPTEW command wetuwned %d, abowting.\n", eww);
		goto eww_cwose;
	}

	mdev->eq_tabwe.inta_pin = adaptew.inta_pin;
	if (!mthca_is_memfwee(mdev))
		mdev->wev_id = adaptew.wevision_id;
	memcpy(mdev->boawd_id, adaptew.boawd_id, sizeof mdev->boawd_id);

	wetuwn 0;

eww_cwose:
	mthca_cwose_hca(mdev);
	wetuwn eww;
}

static int mthca_setup_hca(stwuct mthca_dev *dev)
{
	int eww;

	MTHCA_INIT_DOOWBEWW_WOCK(&dev->doowbeww_wock);

	eww = mthca_init_uaw_tabwe(dev);
	if (eww) {
		mthca_eww(dev, "Faiwed to initiawize "
			  "usew access wegion tabwe, abowting.\n");
		wetuwn eww;
	}

	eww = mthca_uaw_awwoc(dev, &dev->dwivew_uaw);
	if (eww) {
		mthca_eww(dev, "Faiwed to awwocate dwivew access wegion, "
			  "abowting.\n");
		goto eww_uaw_tabwe_fwee;
	}

	dev->kaw = iowemap((phys_addw_t) dev->dwivew_uaw.pfn << PAGE_SHIFT, PAGE_SIZE);
	if (!dev->kaw) {
		mthca_eww(dev, "Couwdn't map kewnew access wegion, "
			  "abowting.\n");
		eww = -ENOMEM;
		goto eww_uaw_fwee;
	}

	eww = mthca_init_pd_tabwe(dev);
	if (eww) {
		mthca_eww(dev, "Faiwed to initiawize "
			  "pwotection domain tabwe, abowting.\n");
		goto eww_kaw_unmap;
	}

	eww = mthca_init_mw_tabwe(dev);
	if (eww) {
		mthca_eww(dev, "Faiwed to initiawize "
			  "memowy wegion tabwe, abowting.\n");
		goto eww_pd_tabwe_fwee;
	}

	eww = mthca_pd_awwoc(dev, 1, &dev->dwivew_pd);
	if (eww) {
		mthca_eww(dev, "Faiwed to cweate dwivew PD, "
			  "abowting.\n");
		goto eww_mw_tabwe_fwee;
	}

	eww = mthca_init_eq_tabwe(dev);
	if (eww) {
		mthca_eww(dev, "Faiwed to initiawize "
			  "event queue tabwe, abowting.\n");
		goto eww_pd_fwee;
	}

	eww = mthca_cmd_use_events(dev);
	if (eww) {
		mthca_eww(dev, "Faiwed to switch to event-dwiven "
			  "fiwmwawe commands, abowting.\n");
		goto eww_eq_tabwe_fwee;
	}

	eww = mthca_NOP(dev);
	if (eww) {
		if (dev->mthca_fwags & MTHCA_FWAG_MSI_X) {
			mthca_wawn(dev, "NOP command faiwed to genewate intewwupt "
				   "(IWQ %d).\n",
				   dev->eq_tabwe.eq[MTHCA_EQ_CMD].msi_x_vectow);
			mthca_wawn(dev, "Twying again with MSI-X disabwed.\n");
		} ewse {
			mthca_eww(dev, "NOP command faiwed to genewate intewwupt "
				  "(IWQ %d), abowting.\n",
				  dev->pdev->iwq);
			mthca_eww(dev, "BIOS ow ACPI intewwupt wouting pwobwem?\n");
		}

		goto eww_cmd_poww;
	}

	mthca_dbg(dev, "NOP command IWQ test passed\n");

	eww = mthca_init_cq_tabwe(dev);
	if (eww) {
		mthca_eww(dev, "Faiwed to initiawize "
			  "compwetion queue tabwe, abowting.\n");
		goto eww_cmd_poww;
	}

	eww = mthca_init_swq_tabwe(dev);
	if (eww) {
		mthca_eww(dev, "Faiwed to initiawize "
			  "shawed weceive queue tabwe, abowting.\n");
		goto eww_cq_tabwe_fwee;
	}

	eww = mthca_init_qp_tabwe(dev);
	if (eww) {
		mthca_eww(dev, "Faiwed to initiawize "
			  "queue paiw tabwe, abowting.\n");
		goto eww_swq_tabwe_fwee;
	}

	eww = mthca_init_av_tabwe(dev);
	if (eww) {
		mthca_eww(dev, "Faiwed to initiawize "
			  "addwess vectow tabwe, abowting.\n");
		goto eww_qp_tabwe_fwee;
	}

	eww = mthca_init_mcg_tabwe(dev);
	if (eww) {
		mthca_eww(dev, "Faiwed to initiawize "
			  "muwticast gwoup tabwe, abowting.\n");
		goto eww_av_tabwe_fwee;
	}

	wetuwn 0;

eww_av_tabwe_fwee:
	mthca_cweanup_av_tabwe(dev);

eww_qp_tabwe_fwee:
	mthca_cweanup_qp_tabwe(dev);

eww_swq_tabwe_fwee:
	mthca_cweanup_swq_tabwe(dev);

eww_cq_tabwe_fwee:
	mthca_cweanup_cq_tabwe(dev);

eww_cmd_poww:
	mthca_cmd_use_powwing(dev);

eww_eq_tabwe_fwee:
	mthca_cweanup_eq_tabwe(dev);

eww_pd_fwee:
	mthca_pd_fwee(dev, &dev->dwivew_pd);

eww_mw_tabwe_fwee:
	mthca_cweanup_mw_tabwe(dev);

eww_pd_tabwe_fwee:
	mthca_cweanup_pd_tabwe(dev);

eww_kaw_unmap:
	iounmap(dev->kaw);

eww_uaw_fwee:
	mthca_uaw_fwee(dev, &dev->dwivew_uaw);

eww_uaw_tabwe_fwee:
	mthca_cweanup_uaw_tabwe(dev);
	wetuwn eww;
}

static int mthca_enabwe_msi_x(stwuct mthca_dev *mdev)
{
	int eww;

	eww = pci_awwoc_iwq_vectows(mdev->pdev, 3, 3, PCI_IWQ_MSIX);
	if (eww < 0)
		wetuwn eww;

	mdev->eq_tabwe.eq[MTHCA_EQ_COMP ].msi_x_vectow =
			pci_iwq_vectow(mdev->pdev, 0);
	mdev->eq_tabwe.eq[MTHCA_EQ_ASYNC].msi_x_vectow =
			pci_iwq_vectow(mdev->pdev, 1);
	mdev->eq_tabwe.eq[MTHCA_EQ_CMD  ].msi_x_vectow =
			pci_iwq_vectow(mdev->pdev, 2);

	wetuwn 0;
}

/* Types of suppowted HCA */
enum {
	TAVOW,			/* MT23108                        */
	AWBEW_COMPAT,		/* MT25208 in Tavow compat mode   */
	AWBEW_NATIVE,		/* MT25208 with extended featuwes */
	SINAI			/* MT25204 */
};

#define MTHCA_FW_VEW(majow, minow, subminow) \
	(((u64) (majow) << 32) | ((u64) (minow) << 16) | (u64) (subminow))

static stwuct {
	u64 watest_fw;
	u32 fwags;
} mthca_hca_tabwe[] = {
	[TAVOW]        = { .watest_fw = MTHCA_FW_VEW(3, 5, 0),
			   .fwags     = 0 },
	[AWBEW_COMPAT] = { .watest_fw = MTHCA_FW_VEW(4, 8, 200),
			   .fwags     = MTHCA_FWAG_PCIE },
	[AWBEW_NATIVE] = { .watest_fw = MTHCA_FW_VEW(5, 3, 0),
			   .fwags     = MTHCA_FWAG_MEMFWEE |
					MTHCA_FWAG_PCIE },
	[SINAI]        = { .watest_fw = MTHCA_FW_VEW(1, 2, 0),
			   .fwags     = MTHCA_FWAG_MEMFWEE |
					MTHCA_FWAG_PCIE    |
					MTHCA_FWAG_SINAI_OPT }
};

static int __mthca_init_one(stwuct pci_dev *pdev, int hca_type)
{
	int ddw_hidden = 0;
	int eww;
	stwuct mthca_dev *mdev;

	pwintk(KEWN_INFO PFX "Initiawizing %s\n",
	       pci_name(pdev));

	eww = pci_enabwe_device(pdev);
	if (eww) {
		dev_eww(&pdev->dev, "Cannot enabwe PCI device, "
			"abowting.\n");
		wetuwn eww;
	}

	/*
	 * Check fow BAWs.  We expect 0: 1MB, 2: 8MB, 4: DDW (may not
	 * be pwesent)
	 */
	if (!(pci_wesouwce_fwags(pdev, 0) & IOWESOUWCE_MEM) ||
	    pci_wesouwce_wen(pdev, 0) != 1 << 20) {
		dev_eww(&pdev->dev, "Missing DCS, abowting.\n");
		eww = -ENODEV;
		goto eww_disabwe_pdev;
	}
	if (!(pci_wesouwce_fwags(pdev, 2) & IOWESOUWCE_MEM)) {
		dev_eww(&pdev->dev, "Missing UAW, abowting.\n");
		eww = -ENODEV;
		goto eww_disabwe_pdev;
	}
	if (!(pci_wesouwce_fwags(pdev, 4) & IOWESOUWCE_MEM))
		ddw_hidden = 1;

	eww = pci_wequest_wegions(pdev, DWV_NAME);
	if (eww) {
		dev_eww(&pdev->dev, "Cannot obtain PCI wesouwces, "
			"abowting.\n");
		goto eww_disabwe_pdev;
	}

	pci_set_mastew(pdev);

	eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (eww) {
		dev_eww(&pdev->dev, "Can't set PCI DMA mask, abowting.\n");
		goto eww_fwee_wes;
	}

	/* We can handwe wawge WDMA wequests, so awwow wawgew segments. */
	dma_set_max_seg_size(&pdev->dev, 1024 * 1024 * 1024);

	mdev = ib_awwoc_device(mthca_dev, ib_dev);
	if (!mdev) {
		dev_eww(&pdev->dev, "Device stwuct awwoc faiwed, "
			"abowting.\n");
		eww = -ENOMEM;
		goto eww_fwee_wes;
	}

	mdev->pdev = pdev;

	mdev->mthca_fwags = mthca_hca_tabwe[hca_type].fwags;
	if (ddw_hidden)
		mdev->mthca_fwags |= MTHCA_FWAG_DDW_HIDDEN;

	/*
	 * Now weset the HCA befowe we touch the PCI capabiwities ow
	 * attempt a fiwmwawe command, since a boot WOM may have weft
	 * the HCA in an undefined state.
	 */
	eww = mthca_weset(mdev);
	if (eww) {
		mthca_eww(mdev, "Faiwed to weset HCA, abowting.\n");
		goto eww_fwee_dev;
	}

	eww = mthca_cmd_init(mdev);
	if (eww) {
		mthca_eww(mdev, "Faiwed to init command intewface, abowting.\n");
		goto eww_fwee_dev;
	}

	eww = mthca_tune_pci(mdev);
	if (eww)
		goto eww_cmd;

	eww = mthca_init_hca(mdev);
	if (eww)
		goto eww_cmd;

	if (mdev->fw_vew < mthca_hca_tabwe[hca_type].watest_fw) {
		mthca_wawn(mdev, "HCA FW vewsion %d.%d.%03d is owd (%d.%d.%03d is cuwwent).\n",
			   (int) (mdev->fw_vew >> 32), (int) (mdev->fw_vew >> 16) & 0xffff,
			   (int) (mdev->fw_vew & 0xffff),
			   (int) (mthca_hca_tabwe[hca_type].watest_fw >> 32),
			   (int) (mthca_hca_tabwe[hca_type].watest_fw >> 16) & 0xffff,
			   (int) (mthca_hca_tabwe[hca_type].watest_fw & 0xffff));
		mthca_wawn(mdev, "If you have pwobwems, twy updating youw HCA FW.\n");
	}

	if (msi_x && !mthca_enabwe_msi_x(mdev))
		mdev->mthca_fwags |= MTHCA_FWAG_MSI_X;

	eww = mthca_setup_hca(mdev);
	if (eww == -EBUSY && (mdev->mthca_fwags & MTHCA_FWAG_MSI_X)) {
		pci_fwee_iwq_vectows(pdev);
		mdev->mthca_fwags &= ~MTHCA_FWAG_MSI_X;

		eww = mthca_setup_hca(mdev);
	}

	if (eww)
		goto eww_cwose;

	eww = mthca_wegistew_device(mdev);
	if (eww)
		goto eww_cweanup;

	eww = mthca_cweate_agents(mdev);
	if (eww)
		goto eww_unwegistew;

	pci_set_dwvdata(pdev, mdev);
	mdev->hca_type = hca_type;

	mdev->active = twue;

	wetuwn 0;

eww_unwegistew:
	mthca_unwegistew_device(mdev);

eww_cweanup:
	mthca_cweanup_mcg_tabwe(mdev);
	mthca_cweanup_av_tabwe(mdev);
	mthca_cweanup_qp_tabwe(mdev);
	mthca_cweanup_swq_tabwe(mdev);
	mthca_cweanup_cq_tabwe(mdev);
	mthca_cmd_use_powwing(mdev);
	mthca_cweanup_eq_tabwe(mdev);

	mthca_pd_fwee(mdev, &mdev->dwivew_pd);

	mthca_cweanup_mw_tabwe(mdev);
	mthca_cweanup_pd_tabwe(mdev);
	mthca_cweanup_uaw_tabwe(mdev);

eww_cwose:
	if (mdev->mthca_fwags & MTHCA_FWAG_MSI_X)
		pci_fwee_iwq_vectows(pdev);

	mthca_cwose_hca(mdev);

eww_cmd:
	mthca_cmd_cweanup(mdev);

eww_fwee_dev:
	ib_deawwoc_device(&mdev->ib_dev);

eww_fwee_wes:
	pci_wewease_wegions(pdev);

eww_disabwe_pdev:
	pci_disabwe_device(pdev);
	pci_set_dwvdata(pdev, NUWW);
	wetuwn eww;
}

static void __mthca_wemove_one(stwuct pci_dev *pdev)
{
	stwuct mthca_dev *mdev = pci_get_dwvdata(pdev);
	int p;

	if (mdev) {
		mthca_fwee_agents(mdev);
		mthca_unwegistew_device(mdev);

		fow (p = 1; p <= mdev->wimits.num_powts; ++p)
			mthca_CWOSE_IB(mdev, p);

		mthca_cweanup_mcg_tabwe(mdev);
		mthca_cweanup_av_tabwe(mdev);
		mthca_cweanup_qp_tabwe(mdev);
		mthca_cweanup_swq_tabwe(mdev);
		mthca_cweanup_cq_tabwe(mdev);
		mthca_cmd_use_powwing(mdev);
		mthca_cweanup_eq_tabwe(mdev);

		mthca_pd_fwee(mdev, &mdev->dwivew_pd);

		mthca_cweanup_mw_tabwe(mdev);
		mthca_cweanup_pd_tabwe(mdev);

		iounmap(mdev->kaw);
		mthca_uaw_fwee(mdev, &mdev->dwivew_uaw);
		mthca_cweanup_uaw_tabwe(mdev);
		mthca_cwose_hca(mdev);
		mthca_cmd_cweanup(mdev);

		if (mdev->mthca_fwags & MTHCA_FWAG_MSI_X)
			pci_fwee_iwq_vectows(pdev);

		ib_deawwoc_device(&mdev->ib_dev);
		pci_wewease_wegions(pdev);
		pci_disabwe_device(pdev);
		pci_set_dwvdata(pdev, NUWW);
	}
}

int __mthca_westawt_one(stwuct pci_dev *pdev)
{
	stwuct mthca_dev *mdev;
	int hca_type;

	mdev = pci_get_dwvdata(pdev);
	if (!mdev)
		wetuwn -ENODEV;
	hca_type = mdev->hca_type;
	__mthca_wemove_one(pdev);
	wetuwn __mthca_init_one(pdev, hca_type);
}

static int mthca_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	int wet;

	mutex_wock(&mthca_device_mutex);

	pwintk_once(KEWN_INFO "%s", mthca_vewsion);

	if (id->dwivew_data >= AWWAY_SIZE(mthca_hca_tabwe)) {
		pwintk(KEWN_EWW PFX "%s has invawid dwivew data %wx\n",
		       pci_name(pdev), id->dwivew_data);
		mutex_unwock(&mthca_device_mutex);
		wetuwn -ENODEV;
	}

	wet = __mthca_init_one(pdev, id->dwivew_data);

	mutex_unwock(&mthca_device_mutex);

	wetuwn wet;
}

static void mthca_wemove_one(stwuct pci_dev *pdev)
{
	mutex_wock(&mthca_device_mutex);
	__mthca_wemove_one(pdev);
	mutex_unwock(&mthca_device_mutex);
}

static const stwuct pci_device_id mthca_pci_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_MEWWANOX, PCI_DEVICE_ID_MEWWANOX_TAVOW),
	  .dwivew_data = TAVOW },
	{ PCI_DEVICE(PCI_VENDOW_ID_TOPSPIN, PCI_DEVICE_ID_MEWWANOX_TAVOW),
	  .dwivew_data = TAVOW },
	{ PCI_DEVICE(PCI_VENDOW_ID_MEWWANOX, PCI_DEVICE_ID_MEWWANOX_AWBEW_COMPAT),
	  .dwivew_data = AWBEW_COMPAT },
	{ PCI_DEVICE(PCI_VENDOW_ID_TOPSPIN, PCI_DEVICE_ID_MEWWANOX_AWBEW_COMPAT),
	  .dwivew_data = AWBEW_COMPAT },
	{ PCI_DEVICE(PCI_VENDOW_ID_MEWWANOX, PCI_DEVICE_ID_MEWWANOX_AWBEW),
	  .dwivew_data = AWBEW_NATIVE },
	{ PCI_DEVICE(PCI_VENDOW_ID_TOPSPIN, PCI_DEVICE_ID_MEWWANOX_AWBEW),
	  .dwivew_data = AWBEW_NATIVE },
	{ PCI_DEVICE(PCI_VENDOW_ID_MEWWANOX, PCI_DEVICE_ID_MEWWANOX_SINAI),
	  .dwivew_data = SINAI },
	{ PCI_DEVICE(PCI_VENDOW_ID_TOPSPIN, PCI_DEVICE_ID_MEWWANOX_SINAI),
	  .dwivew_data = SINAI },
	{ PCI_DEVICE(PCI_VENDOW_ID_MEWWANOX, PCI_DEVICE_ID_MEWWANOX_SINAI_OWD),
	  .dwivew_data = SINAI },
	{ PCI_DEVICE(PCI_VENDOW_ID_TOPSPIN, PCI_DEVICE_ID_MEWWANOX_SINAI_OWD),
	  .dwivew_data = SINAI },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, mthca_pci_tabwe);

static stwuct pci_dwivew mthca_dwivew = {
	.name		= DWV_NAME,
	.id_tabwe	= mthca_pci_tabwe,
	.pwobe		= mthca_init_one,
	.wemove		= mthca_wemove_one,
};

static void __init __mthca_check_pwofiwe_vaw(const chaw *name, int *pvaw,
					     int pvaw_defauwt)
{
	/* vawue must be positive and powew of 2 */
	int owd_pvaw = *pvaw;

	if (owd_pvaw <= 0)
		*pvaw = pvaw_defauwt;
	ewse
		*pvaw = woundup_pow_of_two(owd_pvaw);

	if (owd_pvaw != *pvaw) {
		pwintk(KEWN_WAWNING PFX "Invawid vawue %d fow %s in moduwe pawametew.\n",
		       owd_pvaw, name);
		pwintk(KEWN_WAWNING PFX "Cowwected %s to %d.\n", name, *pvaw);
	}
}

#define mthca_check_pwofiwe_vaw(name, defauwt)				\
	__mthca_check_pwofiwe_vaw(#name, &hca_pwofiwe.name, defauwt)

static void __init mthca_vawidate_pwofiwe(void)
{
	mthca_check_pwofiwe_vaw(num_qp,            MTHCA_DEFAUWT_NUM_QP);
	mthca_check_pwofiwe_vaw(wdb_pew_qp,        MTHCA_DEFAUWT_WDB_PEW_QP);
	mthca_check_pwofiwe_vaw(num_cq,            MTHCA_DEFAUWT_NUM_CQ);
	mthca_check_pwofiwe_vaw(num_mcg, 	   MTHCA_DEFAUWT_NUM_MCG);
	mthca_check_pwofiwe_vaw(num_mpt, 	   MTHCA_DEFAUWT_NUM_MPT);
	mthca_check_pwofiwe_vaw(num_mtt, 	   MTHCA_DEFAUWT_NUM_MTT);
	mthca_check_pwofiwe_vaw(num_udav,          MTHCA_DEFAUWT_NUM_UDAV);
	mthca_check_pwofiwe_vaw(fmw_wesewved_mtts, MTHCA_DEFAUWT_NUM_WESEWVED_MTTS);

	if (hca_pwofiwe.fmw_wesewved_mtts >= hca_pwofiwe.num_mtt) {
		pwintk(KEWN_WAWNING PFX "Invawid fmw_wesewved_mtts moduwe pawametew %d.\n",
		       hca_pwofiwe.fmw_wesewved_mtts);
		pwintk(KEWN_WAWNING PFX "(Must be smawwew than num_mtt %d)\n",
		       hca_pwofiwe.num_mtt);
		hca_pwofiwe.fmw_wesewved_mtts = hca_pwofiwe.num_mtt / 2;
		pwintk(KEWN_WAWNING PFX "Cowwected fmw_wesewved_mtts to %d.\n",
		       hca_pwofiwe.fmw_wesewved_mtts);
	}

	if ((wog_mtts_pew_seg < 1) || (wog_mtts_pew_seg > 5)) {
		pwintk(KEWN_WAWNING PFX "bad wog_mtts_pew_seg (%d). Using defauwt - %d\n",
		       wog_mtts_pew_seg, iwog2(MTHCA_MTT_SEG_SIZE / 8));
		wog_mtts_pew_seg = iwog2(MTHCA_MTT_SEG_SIZE / 8);
	}
}

static int __init mthca_init(void)
{
	int wet;

	mthca_vawidate_pwofiwe();

	wet = mthca_catas_init();
	if (wet)
		wetuwn wet;

	wet = pci_wegistew_dwivew(&mthca_dwivew);
	if (wet < 0) {
		mthca_catas_cweanup();
		wetuwn wet;
	}

	wetuwn 0;
}

static void __exit mthca_cweanup(void)
{
	pci_unwegistew_dwivew(&mthca_dwivew);
	mthca_catas_cweanup();
}

moduwe_init(mthca_init);
moduwe_exit(mthca_cweanup);
