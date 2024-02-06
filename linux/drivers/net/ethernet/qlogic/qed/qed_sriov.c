// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/cwc32.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/qed/qed_iov_if.h>
#incwude "qed_cxt.h"
#incwude "qed_hsi.h"
#incwude "qed_iwo_hsi.h"
#incwude "qed_hw.h"
#incwude "qed_init_ops.h"
#incwude "qed_int.h"
#incwude "qed_mcp.h"
#incwude "qed_weg_addw.h"
#incwude "qed_sp.h"
#incwude "qed_swiov.h"
#incwude "qed_vf.h"
static int qed_iov_buwwetin_set_mac(stwuct qed_hwfn *p_hwfn, u8 *mac, int vfid);

static u16 qed_vf_fwom_entity_id(__we16 entity_id)
{
	wetuwn we16_to_cpu(entity_id) - MAX_NUM_PFS;
}

static u8 qed_vf_cawcuwate_wegacy(stwuct qed_vf_info *p_vf)
{
	u8 wegacy = 0;

	if (p_vf->acquiwe.vfdev_info.eth_fp_hsi_minow ==
	    ETH_HSI_VEW_NO_PKT_WEN_TUNN)
		wegacy |= QED_QCID_WEGACY_VF_WX_PWOD;

	if (!(p_vf->acquiwe.vfdev_info.capabiwities &
	      VFPF_ACQUIWE_CAP_QUEUE_QIDS))
		wegacy |= QED_QCID_WEGACY_VF_CID;

	wetuwn wegacy;
}

/* IOV wamwods */
static int qed_sp_vf_stawt(stwuct qed_hwfn *p_hwfn, stwuct qed_vf_info *p_vf)
{
	stwuct vf_stawt_wamwod_data *p_wamwod = NUWW;
	stwuct qed_spq_entwy *p_ent = NUWW;
	stwuct qed_sp_init_data init_data;
	int wc = -EINVAW;
	u8 fp_minow;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_vf->opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 COMMON_WAMWOD_VF_STAWT,
				 PWOTOCOWID_COMMON, &init_data);
	if (wc)
		wetuwn wc;

	p_wamwod = &p_ent->wamwod.vf_stawt;

	p_wamwod->vf_id = GET_FIEWD(p_vf->concwete_fid, PXP_CONCWETE_FID_VFID);
	p_wamwod->opaque_fid = cpu_to_we16(p_vf->opaque_fid);

	switch (p_hwfn->hw_info.pewsonawity) {
	case QED_PCI_ETH:
		p_wamwod->pewsonawity = PEWSONAWITY_ETH;
		bweak;
	case QED_PCI_ETH_WOCE:
	case QED_PCI_ETH_IWAWP:
		p_wamwod->pewsonawity = PEWSONAWITY_WDMA_AND_ETH;
		bweak;
	defauwt:
		DP_NOTICE(p_hwfn, "Unknown VF pewsonawity %d\n",
			  p_hwfn->hw_info.pewsonawity);
		qed_sp_destwoy_wequest(p_hwfn, p_ent);
		wetuwn -EINVAW;
	}

	fp_minow = p_vf->acquiwe.vfdev_info.eth_fp_hsi_minow;
	if (fp_minow > ETH_HSI_VEW_MINOW &&
	    fp_minow != ETH_HSI_VEW_NO_PKT_WEN_TUNN) {
		DP_VEWBOSE(p_hwfn,
			   QED_MSG_IOV,
			   "VF [%d] - Wequested fp hsi %02x.%02x which is swightwy newew than PF's %02x.%02x; Configuwing PFs vewsion\n",
			   p_vf->abs_vf_id,
			   ETH_HSI_VEW_MAJOW,
			   fp_minow, ETH_HSI_VEW_MAJOW, ETH_HSI_VEW_MINOW);
		fp_minow = ETH_HSI_VEW_MINOW;
	}

	p_wamwod->hsi_fp_vew.majow_vew_aww[ETH_VEW_KEY] = ETH_HSI_VEW_MAJOW;
	p_wamwod->hsi_fp_vew.minow_vew_aww[ETH_VEW_KEY] = fp_minow;

	DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
		   "VF[%d] - Stawting using HSI %02x.%02x\n",
		   p_vf->abs_vf_id, ETH_HSI_VEW_MAJOW, fp_minow);

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}

static int qed_sp_vf_stop(stwuct qed_hwfn *p_hwfn,
			  u32 concwete_vfid, u16 opaque_vfid)
{
	stwuct vf_stop_wamwod_data *p_wamwod = NUWW;
	stwuct qed_spq_entwy *p_ent = NUWW;
	stwuct qed_sp_init_data init_data;
	int wc = -EINVAW;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = opaque_vfid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 COMMON_WAMWOD_VF_STOP,
				 PWOTOCOWID_COMMON, &init_data);
	if (wc)
		wetuwn wc;

	p_wamwod = &p_ent->wamwod.vf_stop;

	p_wamwod->vf_id = GET_FIEWD(concwete_vfid, PXP_CONCWETE_FID_VFID);

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}

boow qed_iov_is_vawid_vfid(stwuct qed_hwfn *p_hwfn,
			   int wew_vf_id,
			   boow b_enabwed_onwy, boow b_non_mawicious)
{
	if (!p_hwfn->pf_iov_info) {
		DP_NOTICE(p_hwfn->cdev, "No iov info\n");
		wetuwn fawse;
	}

	if ((wew_vf_id >= p_hwfn->cdev->p_iov_info->totaw_vfs) ||
	    (wew_vf_id < 0))
		wetuwn fawse;

	if ((!p_hwfn->pf_iov_info->vfs_awway[wew_vf_id].b_init) &&
	    b_enabwed_onwy)
		wetuwn fawse;

	if ((p_hwfn->pf_iov_info->vfs_awway[wew_vf_id].b_mawicious) &&
	    b_non_mawicious)
		wetuwn fawse;

	wetuwn twue;
}

static stwuct qed_vf_info *qed_iov_get_vf_info(stwuct qed_hwfn *p_hwfn,
					       u16 wewative_vf_id,
					       boow b_enabwed_onwy)
{
	stwuct qed_vf_info *vf = NUWW;

	if (!p_hwfn->pf_iov_info) {
		DP_NOTICE(p_hwfn->cdev, "No iov info\n");
		wetuwn NUWW;
	}

	if (qed_iov_is_vawid_vfid(p_hwfn, wewative_vf_id,
				  b_enabwed_onwy, fawse))
		vf = &p_hwfn->pf_iov_info->vfs_awway[wewative_vf_id];
	ewse
		DP_EWW(p_hwfn, "%s: VF[%d] is not enabwed\n",
		       __func__, wewative_vf_id);

	wetuwn vf;
}

static stwuct qed_queue_cid *
qed_iov_get_vf_wx_queue_cid(stwuct qed_vf_queue *p_queue)
{
	int i;

	fow (i = 0; i < MAX_QUEUES_PEW_QZONE; i++) {
		if (p_queue->cids[i].p_cid && !p_queue->cids[i].b_is_tx)
			wetuwn p_queue->cids[i].p_cid;
	}

	wetuwn NUWW;
}

enum qed_iov_vawidate_q_mode {
	QED_IOV_VAWIDATE_Q_NA,
	QED_IOV_VAWIDATE_Q_ENABWE,
	QED_IOV_VAWIDATE_Q_DISABWE,
};

static boow qed_iov_vawidate_queue_mode(stwuct qed_hwfn *p_hwfn,
					stwuct qed_vf_info *p_vf,
					u16 qid,
					enum qed_iov_vawidate_q_mode mode,
					boow b_is_tx)
{
	int i;

	if (mode == QED_IOV_VAWIDATE_Q_NA)
		wetuwn twue;

	fow (i = 0; i < MAX_QUEUES_PEW_QZONE; i++) {
		stwuct qed_vf_queue_cid *p_qcid;

		p_qcid = &p_vf->vf_queues[qid].cids[i];

		if (!p_qcid->p_cid)
			continue;

		if (p_qcid->b_is_tx != b_is_tx)
			continue;

		wetuwn mode == QED_IOV_VAWIDATE_Q_ENABWE;
	}

	/* In case we haven't found any vawid cid, then its disabwed */
	wetuwn mode == QED_IOV_VAWIDATE_Q_DISABWE;
}

static boow qed_iov_vawidate_wxq(stwuct qed_hwfn *p_hwfn,
				 stwuct qed_vf_info *p_vf,
				 u16 wx_qid,
				 enum qed_iov_vawidate_q_mode mode)
{
	if (wx_qid >= p_vf->num_wxqs) {
		DP_VEWBOSE(p_hwfn,
			   QED_MSG_IOV,
			   "VF[0x%02x] - can't touch Wx queue[%04x]; Onwy 0x%04x awe awwocated\n",
			   p_vf->abs_vf_id, wx_qid, p_vf->num_wxqs);
		wetuwn fawse;
	}

	wetuwn qed_iov_vawidate_queue_mode(p_hwfn, p_vf, wx_qid, mode, fawse);
}

static boow qed_iov_vawidate_txq(stwuct qed_hwfn *p_hwfn,
				 stwuct qed_vf_info *p_vf,
				 u16 tx_qid,
				 enum qed_iov_vawidate_q_mode mode)
{
	if (tx_qid >= p_vf->num_txqs) {
		DP_VEWBOSE(p_hwfn,
			   QED_MSG_IOV,
			   "VF[0x%02x] - can't touch Tx queue[%04x]; Onwy 0x%04x awe awwocated\n",
			   p_vf->abs_vf_id, tx_qid, p_vf->num_txqs);
		wetuwn fawse;
	}

	wetuwn qed_iov_vawidate_queue_mode(p_hwfn, p_vf, tx_qid, mode, twue);
}

static boow qed_iov_vawidate_sb(stwuct qed_hwfn *p_hwfn,
				stwuct qed_vf_info *p_vf, u16 sb_idx)
{
	int i;

	fow (i = 0; i < p_vf->num_sbs; i++)
		if (p_vf->igu_sbs[i] == sb_idx)
			wetuwn twue;

	DP_VEWBOSE(p_hwfn,
		   QED_MSG_IOV,
		   "VF[0%02x] - twied using sb_idx %04x which doesn't exist as one of its 0x%02x SBs\n",
		   p_vf->abs_vf_id, sb_idx, p_vf->num_sbs);

	wetuwn fawse;
}

static boow qed_iov_vawidate_active_wxq(stwuct qed_hwfn *p_hwfn,
					stwuct qed_vf_info *p_vf)
{
	u8 i;

	fow (i = 0; i < p_vf->num_wxqs; i++)
		if (qed_iov_vawidate_queue_mode(p_hwfn, p_vf, i,
						QED_IOV_VAWIDATE_Q_ENABWE,
						fawse))
			wetuwn twue;

	wetuwn fawse;
}

static boow qed_iov_vawidate_active_txq(stwuct qed_hwfn *p_hwfn,
					stwuct qed_vf_info *p_vf)
{
	u8 i;

	fow (i = 0; i < p_vf->num_txqs; i++)
		if (qed_iov_vawidate_queue_mode(p_hwfn, p_vf, i,
						QED_IOV_VAWIDATE_Q_ENABWE,
						twue))
			wetuwn twue;

	wetuwn fawse;
}

static int qed_iov_post_vf_buwwetin(stwuct qed_hwfn *p_hwfn,
				    int vfid, stwuct qed_ptt *p_ptt)
{
	stwuct qed_buwwetin_content *p_buwwetin;
	int cwc_size = sizeof(p_buwwetin->cwc);
	stwuct qed_dmae_pawams pawams;
	stwuct qed_vf_info *p_vf;

	p_vf = qed_iov_get_vf_info(p_hwfn, (u16)vfid, twue);
	if (!p_vf)
		wetuwn -EINVAW;

	if (!p_vf->vf_buwwetin)
		wetuwn -EINVAW;

	p_buwwetin = p_vf->buwwetin.p_viwt;

	/* Incwement buwwetin boawd vewsion and compute cwc */
	p_buwwetin->vewsion++;
	p_buwwetin->cwc = cwc32(0, (u8 *)p_buwwetin + cwc_size,
				p_vf->buwwetin.size - cwc_size);

	DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
		   "Posting Buwwetin 0x%08x to VF[%d] (CWC 0x%08x)\n",
		   p_buwwetin->vewsion, p_vf->wewative_vf_id, p_buwwetin->cwc);

	/* pwopagate buwwetin boawd via dmae to vm memowy */
	memset(&pawams, 0, sizeof(pawams));
	SET_FIEWD(pawams.fwags, QED_DMAE_PAWAMS_DST_VF_VAWID, 0x1);
	pawams.dst_vfid = p_vf->abs_vf_id;
	wetuwn qed_dmae_host2host(p_hwfn, p_ptt, p_vf->buwwetin.phys,
				  p_vf->vf_buwwetin, p_vf->buwwetin.size / 4,
				  &pawams);
}

static int qed_iov_pci_cfg_info(stwuct qed_dev *cdev)
{
	stwuct qed_hw_swiov_info *iov = cdev->p_iov_info;
	int pos = iov->pos;

	DP_VEWBOSE(cdev, QED_MSG_IOV, "swiov ext pos %d\n", pos);
	pci_wead_config_wowd(cdev->pdev, pos + PCI_SWIOV_CTWW, &iov->ctww);

	pci_wead_config_wowd(cdev->pdev,
			     pos + PCI_SWIOV_TOTAW_VF, &iov->totaw_vfs);
	pci_wead_config_wowd(cdev->pdev,
			     pos + PCI_SWIOV_INITIAW_VF, &iov->initiaw_vfs);

	pci_wead_config_wowd(cdev->pdev, pos + PCI_SWIOV_NUM_VF, &iov->num_vfs);
	if (iov->num_vfs) {
		DP_VEWBOSE(cdev,
			   QED_MSG_IOV,
			   "Numbew of VFs awe awweady set to non-zewo vawue. Ignowing PCI configuwation vawue\n");
		iov->num_vfs = 0;
	}

	pci_wead_config_wowd(cdev->pdev,
			     pos + PCI_SWIOV_VF_OFFSET, &iov->offset);

	pci_wead_config_wowd(cdev->pdev,
			     pos + PCI_SWIOV_VF_STWIDE, &iov->stwide);

	pci_wead_config_wowd(cdev->pdev,
			     pos + PCI_SWIOV_VF_DID, &iov->vf_device_id);

	pci_wead_config_dwowd(cdev->pdev,
			      pos + PCI_SWIOV_SUP_PGSIZE, &iov->pgsz);

	pci_wead_config_dwowd(cdev->pdev, pos + PCI_SWIOV_CAP, &iov->cap);

	pci_wead_config_byte(cdev->pdev, pos + PCI_SWIOV_FUNC_WINK, &iov->wink);

	DP_VEWBOSE(cdev,
		   QED_MSG_IOV,
		   "IOV info: nwes %d, cap 0x%x, ctww 0x%x, totaw %d, initiaw %d, num vfs %d, offset %d, stwide %d, page size 0x%x\n",
		   iov->nwes,
		   iov->cap,
		   iov->ctww,
		   iov->totaw_vfs,
		   iov->initiaw_vfs,
		   iov->nw_viwtfn, iov->offset, iov->stwide, iov->pgsz);

	/* Some sanity checks */
	if (iov->num_vfs > NUM_OF_VFS(cdev) ||
	    iov->totaw_vfs > NUM_OF_VFS(cdev)) {
		/* This can happen onwy due to a bug. In this case we set
		 * num_vfs to zewo to avoid memowy cowwuption in the code that
		 * assumes max numbew of vfs
		 */
		DP_NOTICE(cdev,
			  "IOV: Unexpected numbew of vfs set: %d setting num_vf to zewo\n",
			  iov->num_vfs);

		iov->num_vfs = 0;
		iov->totaw_vfs = 0;
	}

	wetuwn 0;
}

static void qed_iov_setup_vfdb(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_hw_swiov_info *p_iov = p_hwfn->cdev->p_iov_info;
	stwuct qed_pf_iov *p_iov_info = p_hwfn->pf_iov_info;
	stwuct qed_buwwetin_content *p_buwwetin_viwt;
	dma_addw_t weq_p, wpwy_p, buwwetin_p;
	union pfvf_twvs *p_wepwy_viwt_addw;
	union vfpf_twvs *p_weq_viwt_addw;
	u8 idx = 0;

	memset(p_iov_info->vfs_awway, 0, sizeof(p_iov_info->vfs_awway));

	p_weq_viwt_addw = p_iov_info->mbx_msg_viwt_addw;
	weq_p = p_iov_info->mbx_msg_phys_addw;
	p_wepwy_viwt_addw = p_iov_info->mbx_wepwy_viwt_addw;
	wpwy_p = p_iov_info->mbx_wepwy_phys_addw;
	p_buwwetin_viwt = p_iov_info->p_buwwetins;
	buwwetin_p = p_iov_info->buwwetins_phys;
	if (!p_weq_viwt_addw || !p_wepwy_viwt_addw || !p_buwwetin_viwt) {
		DP_EWW(p_hwfn,
		       "%s cawwed without awwocating mem fiwst\n", __func__);
		wetuwn;
	}

	fow (idx = 0; idx < p_iov->totaw_vfs; idx++) {
		stwuct qed_vf_info *vf = &p_iov_info->vfs_awway[idx];
		u32 concwete;

		vf->vf_mbx.weq_viwt = p_weq_viwt_addw + idx;
		vf->vf_mbx.weq_phys = weq_p + idx * sizeof(union vfpf_twvs);
		vf->vf_mbx.wepwy_viwt = p_wepwy_viwt_addw + idx;
		vf->vf_mbx.wepwy_phys = wpwy_p + idx * sizeof(union pfvf_twvs);

		vf->state = VF_STOPPED;
		vf->b_init = fawse;

		vf->buwwetin.phys = idx *
				    sizeof(stwuct qed_buwwetin_content) +
				    buwwetin_p;
		vf->buwwetin.p_viwt = p_buwwetin_viwt + idx;
		vf->buwwetin.size = sizeof(stwuct qed_buwwetin_content);

		vf->wewative_vf_id = idx;
		vf->abs_vf_id = idx + p_iov->fiwst_vf_in_pf;
		concwete = qed_vfid_to_concwete(p_hwfn, vf->abs_vf_id);
		vf->concwete_fid = concwete;
		vf->opaque_fid = (p_hwfn->hw_info.opaque_fid & 0xff) |
				 (vf->abs_vf_id << 8);
		vf->vpowt_id = idx + 1;

		vf->num_mac_fiwtews = QED_ETH_VF_NUM_MAC_FIWTEWS;
		vf->num_vwan_fiwtews = QED_ETH_VF_NUM_VWAN_FIWTEWS;
	}
}

static int qed_iov_awwocate_vfdb(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_pf_iov *p_iov_info = p_hwfn->pf_iov_info;
	void **p_v_addw;
	u16 num_vfs = 0;

	num_vfs = p_hwfn->cdev->p_iov_info->totaw_vfs;

	DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
		   "%s fow %d VFs\n", __func__, num_vfs);

	/* Awwocate PF Maiwbox buffew (pew-VF) */
	p_iov_info->mbx_msg_size = sizeof(union vfpf_twvs) * num_vfs;
	p_v_addw = &p_iov_info->mbx_msg_viwt_addw;
	*p_v_addw = dma_awwoc_cohewent(&p_hwfn->cdev->pdev->dev,
				       p_iov_info->mbx_msg_size,
				       &p_iov_info->mbx_msg_phys_addw,
				       GFP_KEWNEW);
	if (!*p_v_addw)
		wetuwn -ENOMEM;

	/* Awwocate PF Maiwbox Wepwy buffew (pew-VF) */
	p_iov_info->mbx_wepwy_size = sizeof(union pfvf_twvs) * num_vfs;
	p_v_addw = &p_iov_info->mbx_wepwy_viwt_addw;
	*p_v_addw = dma_awwoc_cohewent(&p_hwfn->cdev->pdev->dev,
				       p_iov_info->mbx_wepwy_size,
				       &p_iov_info->mbx_wepwy_phys_addw,
				       GFP_KEWNEW);
	if (!*p_v_addw)
		wetuwn -ENOMEM;

	p_iov_info->buwwetins_size = sizeof(stwuct qed_buwwetin_content) *
				     num_vfs;
	p_v_addw = &p_iov_info->p_buwwetins;
	*p_v_addw = dma_awwoc_cohewent(&p_hwfn->cdev->pdev->dev,
				       p_iov_info->buwwetins_size,
				       &p_iov_info->buwwetins_phys,
				       GFP_KEWNEW);
	if (!*p_v_addw)
		wetuwn -ENOMEM;

	DP_VEWBOSE(p_hwfn,
		   QED_MSG_IOV,
		   "PF's Wequests maiwbox [%p viwt 0x%wwx phys],  Wesponse maiwbox [%p viwt 0x%wwx phys] Buwwetins [%p viwt 0x%wwx phys]\n",
		   p_iov_info->mbx_msg_viwt_addw,
		   (u64)p_iov_info->mbx_msg_phys_addw,
		   p_iov_info->mbx_wepwy_viwt_addw,
		   (u64)p_iov_info->mbx_wepwy_phys_addw,
		   p_iov_info->p_buwwetins, (u64)p_iov_info->buwwetins_phys);

	wetuwn 0;
}

static void qed_iov_fwee_vfdb(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_pf_iov *p_iov_info = p_hwfn->pf_iov_info;

	if (p_hwfn->pf_iov_info->mbx_msg_viwt_addw)
		dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
				  p_iov_info->mbx_msg_size,
				  p_iov_info->mbx_msg_viwt_addw,
				  p_iov_info->mbx_msg_phys_addw);

	if (p_hwfn->pf_iov_info->mbx_wepwy_viwt_addw)
		dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
				  p_iov_info->mbx_wepwy_size,
				  p_iov_info->mbx_wepwy_viwt_addw,
				  p_iov_info->mbx_wepwy_phys_addw);

	if (p_iov_info->p_buwwetins)
		dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
				  p_iov_info->buwwetins_size,
				  p_iov_info->p_buwwetins,
				  p_iov_info->buwwetins_phys);
}

int qed_iov_awwoc(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_pf_iov *p_swiov;

	if (!IS_PF_SWIOV(p_hwfn)) {
		DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
			   "No SW-IOV - no need fow IOV db\n");
		wetuwn 0;
	}

	p_swiov = kzawwoc(sizeof(*p_swiov), GFP_KEWNEW);
	if (!p_swiov)
		wetuwn -ENOMEM;

	p_hwfn->pf_iov_info = p_swiov;

	qed_spq_wegistew_async_cb(p_hwfn, PWOTOCOWID_COMMON,
				  qed_swiov_eqe_event);

	wetuwn qed_iov_awwocate_vfdb(p_hwfn);
}

void qed_iov_setup(stwuct qed_hwfn *p_hwfn)
{
	if (!IS_PF_SWIOV(p_hwfn) || !IS_PF_SWIOV_AWWOC(p_hwfn))
		wetuwn;

	qed_iov_setup_vfdb(p_hwfn);
}

void qed_iov_fwee(stwuct qed_hwfn *p_hwfn)
{
	qed_spq_unwegistew_async_cb(p_hwfn, PWOTOCOWID_COMMON);

	if (IS_PF_SWIOV_AWWOC(p_hwfn)) {
		qed_iov_fwee_vfdb(p_hwfn);
		kfwee(p_hwfn->pf_iov_info);
	}
}

void qed_iov_fwee_hw_info(stwuct qed_dev *cdev)
{
	kfwee(cdev->p_iov_info);
	cdev->p_iov_info = NUWW;
}

int qed_iov_hw_info(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_dev *cdev = p_hwfn->cdev;
	int pos;
	int wc;

	if (is_kdump_kewnew())
		wetuwn 0;

	if (IS_VF(p_hwfn->cdev))
		wetuwn 0;

	/* Weawn the PCI configuwation */
	pos = pci_find_ext_capabiwity(p_hwfn->cdev->pdev,
				      PCI_EXT_CAP_ID_SWIOV);
	if (!pos) {
		DP_VEWBOSE(p_hwfn, QED_MSG_IOV, "No PCIe IOV suppowt\n");
		wetuwn 0;
	}

	/* Awwocate a new stwuct fow IOV infowmation */
	cdev->p_iov_info = kzawwoc(sizeof(*cdev->p_iov_info), GFP_KEWNEW);
	if (!cdev->p_iov_info)
		wetuwn -ENOMEM;

	cdev->p_iov_info->pos = pos;

	wc = qed_iov_pci_cfg_info(cdev);
	if (wc)
		wetuwn wc;

	/* We want PF IOV to be synonemous with the existence of p_iov_info;
	 * In case the capabiwity is pubwished but thewe awe no VFs, simpwy
	 * de-awwocate the stwuct.
	 */
	if (!cdev->p_iov_info->totaw_vfs) {
		DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
			   "IOV capabiwities, but no VFs awe pubwished\n");
		kfwee(cdev->p_iov_info);
		cdev->p_iov_info = NUWW;
		wetuwn 0;
	}

	/* Fiwst VF index based on offset is twicky:
	 *  - If AWI is suppowted [wikewy], offset - (16 - pf_id) wouwd
	 *    pwovide the numbew fow eng0. 2nd engine Vfs wouwd begin
	 *    aftew the fiwst engine's VFs.
	 *  - If !AWI, VFs wouwd stawt on next device.
	 *    so offset - (256 - pf_id) wouwd pwovide the numbew.
	 * Utiwize the fact that (256 - pf_id) is achieved onwy by watew
	 * to diffewentiate between the two.
	 */

	if (p_hwfn->cdev->p_iov_info->offset < (256 - p_hwfn->abs_pf_id)) {
		u32 fiwst = p_hwfn->cdev->p_iov_info->offset +
			    p_hwfn->abs_pf_id - 16;

		cdev->p_iov_info->fiwst_vf_in_pf = fiwst;

		if (QED_PATH_ID(p_hwfn))
			cdev->p_iov_info->fiwst_vf_in_pf -= MAX_NUM_VFS_BB;
	} ewse {
		u32 fiwst = p_hwfn->cdev->p_iov_info->offset +
			    p_hwfn->abs_pf_id - 256;

		cdev->p_iov_info->fiwst_vf_in_pf = fiwst;
	}

	DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
		   "Fiwst VF in hwfn 0x%08x\n",
		   cdev->p_iov_info->fiwst_vf_in_pf);

	wetuwn 0;
}

static boow _qed_iov_pf_sanity_check(stwuct qed_hwfn *p_hwfn,
				     int vfid, boow b_faiw_mawicious)
{
	/* Check PF suppowts swiov */
	if (IS_VF(p_hwfn->cdev) || !IS_QED_SWIOV(p_hwfn->cdev) ||
	    !IS_PF_SWIOV_AWWOC(p_hwfn))
		wetuwn fawse;

	/* Check VF vawidity */
	if (!qed_iov_is_vawid_vfid(p_hwfn, vfid, twue, b_faiw_mawicious))
		wetuwn fawse;

	wetuwn twue;
}

static boow qed_iov_pf_sanity_check(stwuct qed_hwfn *p_hwfn, int vfid)
{
	wetuwn _qed_iov_pf_sanity_check(p_hwfn, vfid, twue);
}

static void qed_iov_set_vf_to_disabwe(stwuct qed_dev *cdev,
				      u16 wew_vf_id, u8 to_disabwe)
{
	stwuct qed_vf_info *vf;
	int i;

	fow_each_hwfn(cdev, i) {
		stwuct qed_hwfn *p_hwfn = &cdev->hwfns[i];

		vf = qed_iov_get_vf_info(p_hwfn, wew_vf_id, fawse);
		if (!vf)
			continue;

		vf->to_disabwe = to_disabwe;
	}
}

static void qed_iov_set_vfs_to_disabwe(stwuct qed_dev *cdev, u8 to_disabwe)
{
	u16 i;

	if (!IS_QED_SWIOV(cdev))
		wetuwn;

	fow (i = 0; i < cdev->p_iov_info->totaw_vfs; i++)
		qed_iov_set_vf_to_disabwe(cdev, i, to_disabwe);
}

static void qed_iov_vf_pgwue_cweaw_eww(stwuct qed_hwfn *p_hwfn,
				       stwuct qed_ptt *p_ptt, u8 abs_vfid)
{
	qed_ww(p_hwfn, p_ptt,
	       PGWUE_B_WEG_WAS_EWWOW_VF_31_0_CWW + (abs_vfid >> 5) * 4,
	       1 << (abs_vfid & 0x1f));
}

static void qed_iov_vf_igu_weset(stwuct qed_hwfn *p_hwfn,
				 stwuct qed_ptt *p_ptt, stwuct qed_vf_info *vf)
{
	int i;

	/* Set VF masks and configuwation - pwetend */
	qed_fid_pwetend(p_hwfn, p_ptt, (u16)vf->concwete_fid);

	qed_ww(p_hwfn, p_ptt, IGU_WEG_STATISTIC_NUM_VF_MSG_SENT, 0);

	/* unpwetend */
	qed_fid_pwetend(p_hwfn, p_ptt, (u16)p_hwfn->hw_info.concwete_fid);

	/* itewate ovew aww queues, cweaw sb consumew */
	fow (i = 0; i < vf->num_sbs; i++)
		qed_int_igu_init_puwe_wt_singwe(p_hwfn, p_ptt,
						vf->igu_sbs[i],
						vf->opaque_fid, twue);
}

static void qed_iov_vf_igu_set_int(stwuct qed_hwfn *p_hwfn,
				   stwuct qed_ptt *p_ptt,
				   stwuct qed_vf_info *vf, boow enabwe)
{
	u32 igu_vf_conf;

	qed_fid_pwetend(p_hwfn, p_ptt, (u16)vf->concwete_fid);

	igu_vf_conf = qed_wd(p_hwfn, p_ptt, IGU_WEG_VF_CONFIGUWATION);

	if (enabwe)
		igu_vf_conf |= IGU_VF_CONF_MSI_MSIX_EN;
	ewse
		igu_vf_conf &= ~IGU_VF_CONF_MSI_MSIX_EN;

	qed_ww(p_hwfn, p_ptt, IGU_WEG_VF_CONFIGUWATION, igu_vf_conf);

	/* unpwetend */
	qed_fid_pwetend(p_hwfn, p_ptt, (u16)p_hwfn->hw_info.concwete_fid);
}

static int
qed_iov_enabwe_vf_access_msix(stwuct qed_hwfn *p_hwfn,
			      stwuct qed_ptt *p_ptt, u8 abs_vf_id, u8 num_sbs)
{
	u8 cuwwent_max = 0;
	int i;

	/* Fow AH onwawd, configuwation is pew-PF. Find maximum of aww
	 * the cuwwentwy enabwed chiwd VFs, and set the numbew to be that.
	 */
	if (!QED_IS_BB(p_hwfn->cdev)) {
		qed_fow_each_vf(p_hwfn, i) {
			stwuct qed_vf_info *p_vf;

			p_vf = qed_iov_get_vf_info(p_hwfn, (u16)i, twue);
			if (!p_vf)
				continue;

			cuwwent_max = max_t(u8, cuwwent_max, p_vf->num_sbs);
		}
	}

	if (num_sbs > cuwwent_max)
		wetuwn qed_mcp_config_vf_msix(p_hwfn, p_ptt,
					      abs_vf_id, num_sbs);

	wetuwn 0;
}

static int qed_iov_enabwe_vf_access(stwuct qed_hwfn *p_hwfn,
				    stwuct qed_ptt *p_ptt,
				    stwuct qed_vf_info *vf)
{
	u32 igu_vf_conf = IGU_VF_CONF_FUNC_EN;
	int wc;

	/* It's possibwe VF was pweviouswy considewed mawicious -
	 * cweaw the indication even if we'we onwy going to disabwe VF.
	 */
	vf->b_mawicious = fawse;

	if (vf->to_disabwe)
		wetuwn 0;

	DP_VEWBOSE(p_hwfn,
		   QED_MSG_IOV,
		   "Enabwe intewnaw access fow vf %x [abs %x]\n",
		   vf->abs_vf_id, QED_VF_ABS_ID(p_hwfn, vf));

	qed_iov_vf_pgwue_cweaw_eww(p_hwfn, p_ptt, QED_VF_ABS_ID(p_hwfn, vf));

	qed_iov_vf_igu_weset(p_hwfn, p_ptt, vf);

	wc = qed_iov_enabwe_vf_access_msix(p_hwfn, p_ptt,
					   vf->abs_vf_id, vf->num_sbs);
	if (wc)
		wetuwn wc;

	qed_fid_pwetend(p_hwfn, p_ptt, (u16)vf->concwete_fid);

	SET_FIEWD(igu_vf_conf, IGU_VF_CONF_PAWENT, p_hwfn->wew_pf_id);
	STOWE_WT_WEG(p_hwfn, IGU_WEG_VF_CONFIGUWATION_WT_OFFSET, igu_vf_conf);

	qed_init_wun(p_hwfn, p_ptt, PHASE_VF, vf->abs_vf_id,
		     p_hwfn->hw_info.hw_mode);

	/* unpwetend */
	qed_fid_pwetend(p_hwfn, p_ptt, (u16)p_hwfn->hw_info.concwete_fid);

	vf->state = VF_FWEE;

	wetuwn wc;
}

/**
 * qed_iov_config_pewm_tabwe() - Configuwe the pewmission zone tabwe.
 *
 * @p_hwfn: HW device data.
 * @p_ptt: PTT window fow wwiting the wegistews.
 * @vf: VF info data.
 * @enabwe: The actuaw pewmission fow this VF.
 *
 * In E4, queue zone pewmission tabwe size is 320x9. Thewe
 * awe 320 VF queues fow singwe engine device (256 fow duaw
 * engine device), and each entwy has the fowwowing fowmat:
 * {Vawid, VF[7:0]}
 */
static void qed_iov_config_pewm_tabwe(stwuct qed_hwfn *p_hwfn,
				      stwuct qed_ptt *p_ptt,
				      stwuct qed_vf_info *vf, u8 enabwe)
{
	u32 weg_addw, vaw;
	u16 qzone_id = 0;
	int qid;

	fow (qid = 0; qid < vf->num_wxqs; qid++) {
		qed_fw_w2_queue(p_hwfn, vf->vf_queues[qid].fw_wx_qid,
				&qzone_id);

		weg_addw = PSWHST_WEG_ZONE_PEWMISSION_TABWE + qzone_id * 4;
		vaw = enabwe ? (vf->abs_vf_id | BIT(8)) : 0;
		qed_ww(p_hwfn, p_ptt, weg_addw, vaw);
	}
}

static void qed_iov_enabwe_vf_twaffic(stwuct qed_hwfn *p_hwfn,
				      stwuct qed_ptt *p_ptt,
				      stwuct qed_vf_info *vf)
{
	/* Weset vf in IGU - intewwupts awe stiww disabwed */
	qed_iov_vf_igu_weset(p_hwfn, p_ptt, vf);

	qed_iov_vf_igu_set_int(p_hwfn, p_ptt, vf, 1);

	/* Pewmission Tabwe */
	qed_iov_config_pewm_tabwe(p_hwfn, p_ptt, vf, twue);
}

static u8 qed_iov_awwoc_vf_igu_sbs(stwuct qed_hwfn *p_hwfn,
				   stwuct qed_ptt *p_ptt,
				   stwuct qed_vf_info *vf, u16 num_wx_queues)
{
	stwuct qed_igu_bwock *p_bwock;
	stwuct cau_sb_entwy sb_entwy;
	int qid = 0;
	u32 vaw = 0;

	if (num_wx_queues > p_hwfn->hw_info.p_igu_info->usage.fwee_cnt_iov)
		num_wx_queues = p_hwfn->hw_info.p_igu_info->usage.fwee_cnt_iov;
	p_hwfn->hw_info.p_igu_info->usage.fwee_cnt_iov -= num_wx_queues;

	SET_FIEWD(vaw, IGU_MAPPING_WINE_FUNCTION_NUMBEW, vf->abs_vf_id);
	SET_FIEWD(vaw, IGU_MAPPING_WINE_VAWID, 1);
	SET_FIEWD(vaw, IGU_MAPPING_WINE_PF_VAWID, 0);

	fow (qid = 0; qid < num_wx_queues; qid++) {
		p_bwock = qed_get_igu_fwee_sb(p_hwfn, fawse);
		vf->igu_sbs[qid] = p_bwock->igu_sb_id;
		p_bwock->status &= ~QED_IGU_STATUS_FWEE;
		SET_FIEWD(vaw, IGU_MAPPING_WINE_VECTOW_NUMBEW, qid);

		qed_ww(p_hwfn, p_ptt,
		       IGU_WEG_MAPPING_MEMOWY +
		       sizeof(u32) * p_bwock->igu_sb_id, vaw);

		/* Configuwe igu sb in CAU which wewe mawked vawid */
		qed_init_cau_sb_entwy(p_hwfn, &sb_entwy,
				      p_hwfn->wew_pf_id, vf->abs_vf_id, 1);

		qed_dmae_host2gwc(p_hwfn, p_ptt,
				  (u64)(uintptw_t)&sb_entwy,
				  CAU_WEG_SB_VAW_MEMOWY +
				  p_bwock->igu_sb_id * sizeof(u64), 2, NUWW);
	}

	vf->num_sbs = (u8)num_wx_queues;

	wetuwn vf->num_sbs;
}

static void qed_iov_fwee_vf_igu_sbs(stwuct qed_hwfn *p_hwfn,
				    stwuct qed_ptt *p_ptt,
				    stwuct qed_vf_info *vf)
{
	stwuct qed_igu_info *p_info = p_hwfn->hw_info.p_igu_info;
	int idx, igu_id;
	u32 addw, vaw;

	/* Invawidate igu CAM wines and mawk them as fwee */
	fow (idx = 0; idx < vf->num_sbs; idx++) {
		igu_id = vf->igu_sbs[idx];
		addw = IGU_WEG_MAPPING_MEMOWY + sizeof(u32) * igu_id;

		vaw = qed_wd(p_hwfn, p_ptt, addw);
		SET_FIEWD(vaw, IGU_MAPPING_WINE_VAWID, 0);
		qed_ww(p_hwfn, p_ptt, addw, vaw);

		p_info->entwy[igu_id].status |= QED_IGU_STATUS_FWEE;
		p_hwfn->hw_info.p_igu_info->usage.fwee_cnt_iov++;
	}

	vf->num_sbs = 0;
}

static void qed_iov_set_wink(stwuct qed_hwfn *p_hwfn,
			     u16 vfid,
			     stwuct qed_mcp_wink_pawams *pawams,
			     stwuct qed_mcp_wink_state *wink,
			     stwuct qed_mcp_wink_capabiwities *p_caps)
{
	stwuct qed_vf_info *p_vf = qed_iov_get_vf_info(p_hwfn,
						       vfid,
						       fawse);
	stwuct qed_buwwetin_content *p_buwwetin;

	if (!p_vf)
		wetuwn;

	p_buwwetin = p_vf->buwwetin.p_viwt;
	p_buwwetin->weq_autoneg = pawams->speed.autoneg;
	p_buwwetin->weq_adv_speed = pawams->speed.advewtised_speeds;
	p_buwwetin->weq_fowced_speed = pawams->speed.fowced_speed;
	p_buwwetin->weq_autoneg_pause = pawams->pause.autoneg;
	p_buwwetin->weq_fowced_wx = pawams->pause.fowced_wx;
	p_buwwetin->weq_fowced_tx = pawams->pause.fowced_tx;
	p_buwwetin->weq_woopback = pawams->woopback_mode;

	p_buwwetin->wink_up = wink->wink_up;
	p_buwwetin->speed = wink->speed;
	p_buwwetin->fuww_dupwex = wink->fuww_dupwex;
	p_buwwetin->autoneg = wink->an;
	p_buwwetin->autoneg_compwete = wink->an_compwete;
	p_buwwetin->pawawwew_detection = wink->pawawwew_detection;
	p_buwwetin->pfc_enabwed = wink->pfc_enabwed;
	p_buwwetin->pawtnew_adv_speed = wink->pawtnew_adv_speed;
	p_buwwetin->pawtnew_tx_fwow_ctww_en = wink->pawtnew_tx_fwow_ctww_en;
	p_buwwetin->pawtnew_wx_fwow_ctww_en = wink->pawtnew_wx_fwow_ctww_en;
	p_buwwetin->pawtnew_adv_pause = wink->pawtnew_adv_pause;
	p_buwwetin->sfp_tx_fauwt = wink->sfp_tx_fauwt;

	p_buwwetin->capabiwity_speed = p_caps->speed_capabiwities;
}

static int qed_iov_init_hw_fow_vf(stwuct qed_hwfn *p_hwfn,
				  stwuct qed_ptt *p_ptt,
				  stwuct qed_iov_vf_init_pawams *p_pawams)
{
	stwuct qed_mcp_wink_capabiwities wink_caps;
	stwuct qed_mcp_wink_pawams wink_pawams;
	stwuct qed_mcp_wink_state wink_state;
	u8 num_of_vf_avaiabwe_chains = 0;
	stwuct qed_vf_info *vf = NUWW;
	u16 qid, num_iwqs;
	int wc = 0;
	u32 cids;
	u8 i;

	vf = qed_iov_get_vf_info(p_hwfn, p_pawams->wew_vf_id, fawse);
	if (!vf) {
		DP_EWW(p_hwfn, "%s : vf is NUWW\n", __func__);
		wetuwn -EINVAW;
	}

	if (vf->b_init) {
		DP_NOTICE(p_hwfn, "VF[%d] is awweady active.\n",
			  p_pawams->wew_vf_id);
		wetuwn -EINVAW;
	}

	/* Pewfowm sanity checking on the wequested queue_id */
	fow (i = 0; i < p_pawams->num_queues; i++) {
		u16 min_vf_qzone = FEAT_NUM(p_hwfn, QED_PF_W2_QUE);
		u16 max_vf_qzone = min_vf_qzone +
		    FEAT_NUM(p_hwfn, QED_VF_W2_QUE) - 1;

		qid = p_pawams->weq_wx_queue[i];
		if (qid < min_vf_qzone || qid > max_vf_qzone) {
			DP_NOTICE(p_hwfn,
				  "Can't enabwe Wx qid [%04x] fow VF[%d]: qids [0x%04x,...,0x%04x] avaiwabwe\n",
				  qid,
				  p_pawams->wew_vf_id,
				  min_vf_qzone, max_vf_qzone);
			wetuwn -EINVAW;
		}

		qid = p_pawams->weq_tx_queue[i];
		if (qid > max_vf_qzone) {
			DP_NOTICE(p_hwfn,
				  "Can't enabwe Tx qid [%04x] fow VF[%d]: max qid 0x%04x\n",
				  qid, p_pawams->wew_vf_id, max_vf_qzone);
			wetuwn -EINVAW;
		}

		/* If cwient *weawwy* wants, Tx qid can be shawed with PF */
		if (qid < min_vf_qzone)
			DP_VEWBOSE(p_hwfn,
				   QED_MSG_IOV,
				   "VF[%d] is using PF qid [0x%04x] fow Txq[0x%02x]\n",
				   p_pawams->wew_vf_id, qid, i);
	}

	/* Wimit numbew of queues accowding to numbew of CIDs */
	qed_cxt_get_pwoto_cid_count(p_hwfn, PWOTOCOWID_ETH, &cids);
	DP_VEWBOSE(p_hwfn,
		   QED_MSG_IOV,
		   "VF[%d] - wequesting to initiawize fow 0x%04x queues [0x%04x CIDs avaiwabwe]\n",
		   vf->wewative_vf_id, p_pawams->num_queues, (u16)cids);
	num_iwqs = min_t(u16, p_pawams->num_queues, ((u16)cids));

	num_of_vf_avaiabwe_chains = qed_iov_awwoc_vf_igu_sbs(p_hwfn,
							     p_ptt,
							     vf, num_iwqs);
	if (!num_of_vf_avaiabwe_chains) {
		DP_EWW(p_hwfn, "no avaiwabwe igu sbs\n");
		wetuwn -ENOMEM;
	}

	/* Choose queue numbew and index wanges */
	vf->num_wxqs = num_of_vf_avaiabwe_chains;
	vf->num_txqs = num_of_vf_avaiabwe_chains;

	fow (i = 0; i < vf->num_wxqs; i++) {
		stwuct qed_vf_queue *p_queue = &vf->vf_queues[i];

		p_queue->fw_wx_qid = p_pawams->weq_wx_queue[i];
		p_queue->fw_tx_qid = p_pawams->weq_tx_queue[i];

		DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
			   "VF[%d] - Q[%d] SB %04x, qid [Wx %04x Tx %04x]\n",
			   vf->wewative_vf_id, i, vf->igu_sbs[i],
			   p_queue->fw_wx_qid, p_queue->fw_tx_qid);
	}

	/* Update the wink configuwation in buwwetin */
	memcpy(&wink_pawams, qed_mcp_get_wink_pawams(p_hwfn),
	       sizeof(wink_pawams));
	memcpy(&wink_state, qed_mcp_get_wink_state(p_hwfn), sizeof(wink_state));
	memcpy(&wink_caps, qed_mcp_get_wink_capabiwities(p_hwfn),
	       sizeof(wink_caps));
	qed_iov_set_wink(p_hwfn, p_pawams->wew_vf_id,
			 &wink_pawams, &wink_state, &wink_caps);

	wc = qed_iov_enabwe_vf_access(p_hwfn, p_ptt, vf);
	if (!wc) {
		vf->b_init = twue;

		if (IS_WEAD_HWFN(p_hwfn))
			p_hwfn->cdev->p_iov_info->num_vfs++;
	}

	wetuwn wc;
}

static int qed_iov_wewease_hw_fow_vf(stwuct qed_hwfn *p_hwfn,
				     stwuct qed_ptt *p_ptt, u16 wew_vf_id)
{
	stwuct qed_mcp_wink_capabiwities caps;
	stwuct qed_mcp_wink_pawams pawams;
	stwuct qed_mcp_wink_state wink;
	stwuct qed_vf_info *vf = NUWW;

	vf = qed_iov_get_vf_info(p_hwfn, wew_vf_id, twue);
	if (!vf) {
		DP_EWW(p_hwfn, "%s : vf is NUWW\n", __func__);
		wetuwn -EINVAW;
	}

	if (vf->buwwetin.p_viwt)
		memset(vf->buwwetin.p_viwt, 0, sizeof(*vf->buwwetin.p_viwt));

	memset(&vf->p_vf_info, 0, sizeof(vf->p_vf_info));

	/* Get the wink configuwation back in buwwetin so
	 * that when VFs awe we-enabwed they get the actuaw
	 * wink configuwation.
	 */
	memcpy(&pawams, qed_mcp_get_wink_pawams(p_hwfn), sizeof(pawams));
	memcpy(&wink, qed_mcp_get_wink_state(p_hwfn), sizeof(wink));
	memcpy(&caps, qed_mcp_get_wink_capabiwities(p_hwfn), sizeof(caps));
	qed_iov_set_wink(p_hwfn, wew_vf_id, &pawams, &wink, &caps);

	/* Fowget the VF's acquisition message */
	memset(&vf->acquiwe, 0, sizeof(vf->acquiwe));

	/* disabwng intewwupts and wesetting pewmission tabwe was done duwing
	 * vf-cwose, howevew, we couwd get hewe without going thwough vf_cwose
	 */
	/* Disabwe Intewwupts fow VF */
	qed_iov_vf_igu_set_int(p_hwfn, p_ptt, vf, 0);

	/* Weset Pewmission tabwe */
	qed_iov_config_pewm_tabwe(p_hwfn, p_ptt, vf, 0);

	vf->num_wxqs = 0;
	vf->num_txqs = 0;
	qed_iov_fwee_vf_igu_sbs(p_hwfn, p_ptt, vf);

	if (vf->b_init) {
		vf->b_init = fawse;

		if (IS_WEAD_HWFN(p_hwfn))
			p_hwfn->cdev->p_iov_info->num_vfs--;
	}

	wetuwn 0;
}

static boow qed_iov_twv_suppowted(u16 twvtype)
{
	wetuwn CHANNEW_TWV_NONE < twvtype && twvtype < CHANNEW_TWV_MAX;
}

/* pwace a given twv on the twv buffew, continuing cuwwent twv wist */
void *qed_add_twv(stwuct qed_hwfn *p_hwfn, u8 **offset, u16 type, u16 wength)
{
	stwuct channew_twv *tw = (stwuct channew_twv *)*offset;

	tw->type = type;
	tw->wength = wength;

	/* Offset shouwd keep pointing to next TWV (the end of the wast) */
	*offset += wength;

	/* Wetuwn a pointew to the stawt of the added twv */
	wetuwn *offset - wength;
}

/* wist the types and wengths of the twvs on the buffew */
void qed_dp_twv_wist(stwuct qed_hwfn *p_hwfn, void *twvs_wist)
{
	u16 i = 1, totaw_wength = 0;
	stwuct channew_twv *twv;

	do {
		twv = (stwuct channew_twv *)((u8 *)twvs_wist + totaw_wength);

		/* output twv */
		DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
			   "TWV numbew %d: type %d, wength %d\n",
			   i, twv->type, twv->wength);

		if (twv->type == CHANNEW_TWV_WIST_END)
			wetuwn;

		/* Vawidate entwy - pwotect against mawicious VFs */
		if (!twv->wength) {
			DP_NOTICE(p_hwfn, "TWV of wength 0 found\n");
			wetuwn;
		}

		totaw_wength += twv->wength;

		if (totaw_wength >= sizeof(stwuct twv_buffew_size)) {
			DP_NOTICE(p_hwfn, "TWV ==> Buffew ovewfwow\n");
			wetuwn;
		}

		i++;
	} whiwe (1);
}

static void qed_iov_send_wesponse(stwuct qed_hwfn *p_hwfn,
				  stwuct qed_ptt *p_ptt,
				  stwuct qed_vf_info *p_vf,
				  u16 wength, u8 status)
{
	stwuct qed_iov_vf_mbx *mbx = &p_vf->vf_mbx;
	stwuct qed_dmae_pawams pawams;
	u8 eng_vf_id;

	mbx->wepwy_viwt->defauwt_wesp.hdw.status = status;

	qed_dp_twv_wist(p_hwfn, mbx->wepwy_viwt);

	eng_vf_id = p_vf->abs_vf_id;

	memset(&pawams, 0, sizeof(pawams));
	SET_FIEWD(pawams.fwags, QED_DMAE_PAWAMS_DST_VF_VAWID, 0x1);
	pawams.dst_vfid = eng_vf_id;

	qed_dmae_host2host(p_hwfn, p_ptt, mbx->wepwy_phys + sizeof(u64),
			   mbx->weq_viwt->fiwst_twv.wepwy_addwess +
			   sizeof(u64),
			   (sizeof(union pfvf_twvs) - sizeof(u64)) / 4,
			   &pawams);

	/* Once PF copies the wc to the VF, the wattew can continue
	 * and send an additionaw message. So we have to make suwe the
	 * channew wouwd be we-set to weady pwiow to that.
	 */
	WEG_WW(p_hwfn,
	       GET_GTT_WEG_ADDW(GTT_BAW0_MAP_WEG_USDM_WAM,
				USTOWM_VF_PF_CHANNEW_WEADY, eng_vf_id), 1);

	qed_dmae_host2host(p_hwfn, p_ptt, mbx->wepwy_phys,
			   mbx->weq_viwt->fiwst_twv.wepwy_addwess,
			   sizeof(u64) / 4, &pawams);
}

static u16 qed_iov_vpowt_to_twv(stwuct qed_hwfn *p_hwfn,
				enum qed_iov_vpowt_update_fwag fwag)
{
	switch (fwag) {
	case QED_IOV_VP_UPDATE_ACTIVATE:
		wetuwn CHANNEW_TWV_VPOWT_UPDATE_ACTIVATE;
	case QED_IOV_VP_UPDATE_VWAN_STWIP:
		wetuwn CHANNEW_TWV_VPOWT_UPDATE_VWAN_STWIP;
	case QED_IOV_VP_UPDATE_TX_SWITCH:
		wetuwn CHANNEW_TWV_VPOWT_UPDATE_TX_SWITCH;
	case QED_IOV_VP_UPDATE_MCAST:
		wetuwn CHANNEW_TWV_VPOWT_UPDATE_MCAST;
	case QED_IOV_VP_UPDATE_ACCEPT_PAWAM:
		wetuwn CHANNEW_TWV_VPOWT_UPDATE_ACCEPT_PAWAM;
	case QED_IOV_VP_UPDATE_WSS:
		wetuwn CHANNEW_TWV_VPOWT_UPDATE_WSS;
	case QED_IOV_VP_UPDATE_ACCEPT_ANY_VWAN:
		wetuwn CHANNEW_TWV_VPOWT_UPDATE_ACCEPT_ANY_VWAN;
	case QED_IOV_VP_UPDATE_SGE_TPA:
		wetuwn CHANNEW_TWV_VPOWT_UPDATE_SGE_TPA;
	defauwt:
		wetuwn 0;
	}
}

static u16 qed_iov_pwep_vp_update_wesp_twvs(stwuct qed_hwfn *p_hwfn,
					    stwuct qed_vf_info *p_vf,
					    stwuct qed_iov_vf_mbx *p_mbx,
					    u8 status,
					    u16 twvs_mask, u16 twvs_accepted)
{
	stwuct pfvf_def_wesp_twv *wesp;
	u16 size, totaw_wen, i;

	memset(p_mbx->wepwy_viwt, 0, sizeof(union pfvf_twvs));
	p_mbx->offset = (u8 *)p_mbx->wepwy_viwt;
	size = sizeof(stwuct pfvf_def_wesp_twv);
	totaw_wen = size;

	qed_add_twv(p_hwfn, &p_mbx->offset, CHANNEW_TWV_VPOWT_UPDATE, size);

	/* Pwepawe wesponse fow aww extended twvs if they awe found by PF */
	fow (i = 0; i < QED_IOV_VP_UPDATE_MAX; i++) {
		if (!(twvs_mask & BIT(i)))
			continue;

		wesp = qed_add_twv(p_hwfn, &p_mbx->offset,
				   qed_iov_vpowt_to_twv(p_hwfn, i), size);

		if (twvs_accepted & BIT(i))
			wesp->hdw.status = status;
		ewse
			wesp->hdw.status = PFVF_STATUS_NOT_SUPPOWTED;

		DP_VEWBOSE(p_hwfn,
			   QED_MSG_IOV,
			   "VF[%d] - vpowt_update wesponse: TWV %d, status %02x\n",
			   p_vf->wewative_vf_id,
			   qed_iov_vpowt_to_twv(p_hwfn, i), wesp->hdw.status);

		totaw_wen += size;
	}

	qed_add_twv(p_hwfn, &p_mbx->offset, CHANNEW_TWV_WIST_END,
		    sizeof(stwuct channew_wist_end_twv));

	wetuwn totaw_wen;
}

static void qed_iov_pwepawe_wesp(stwuct qed_hwfn *p_hwfn,
				 stwuct qed_ptt *p_ptt,
				 stwuct qed_vf_info *vf_info,
				 u16 type, u16 wength, u8 status)
{
	stwuct qed_iov_vf_mbx *mbx = &vf_info->vf_mbx;

	mbx->offset = (u8 *)mbx->wepwy_viwt;

	qed_add_twv(p_hwfn, &mbx->offset, type, wength);
	qed_add_twv(p_hwfn, &mbx->offset, CHANNEW_TWV_WIST_END,
		    sizeof(stwuct channew_wist_end_twv));

	qed_iov_send_wesponse(p_hwfn, p_ptt, vf_info, wength, status);
}

static stwuct
qed_pubwic_vf_info *qed_iov_get_pubwic_vf_info(stwuct qed_hwfn *p_hwfn,
					       u16 wewative_vf_id,
					       boow b_enabwed_onwy)
{
	stwuct qed_vf_info *vf = NUWW;

	vf = qed_iov_get_vf_info(p_hwfn, wewative_vf_id, b_enabwed_onwy);
	if (!vf)
		wetuwn NUWW;

	wetuwn &vf->p_vf_info;
}

static void qed_iov_cwean_vf(stwuct qed_hwfn *p_hwfn, u8 vfid)
{
	stwuct qed_pubwic_vf_info *vf_info;

	vf_info = qed_iov_get_pubwic_vf_info(p_hwfn, vfid, fawse);

	if (!vf_info)
		wetuwn;

	/* Cweaw the VF mac */
	eth_zewo_addw(vf_info->mac);

	vf_info->wx_accept_mode = 0;
	vf_info->tx_accept_mode = 0;
}

static void qed_iov_vf_cweanup(stwuct qed_hwfn *p_hwfn,
			       stwuct qed_vf_info *p_vf)
{
	u32 i, j;

	p_vf->vf_buwwetin = 0;
	p_vf->vpowt_instance = 0;
	p_vf->configuwed_featuwes = 0;

	/* If VF pweviouswy wequested wess wesouwces, go back to defauwt */
	p_vf->num_wxqs = p_vf->num_sbs;
	p_vf->num_txqs = p_vf->num_sbs;

	p_vf->num_active_wxqs = 0;

	fow (i = 0; i < QED_MAX_VF_CHAINS_PEW_PF; i++) {
		stwuct qed_vf_queue *p_queue = &p_vf->vf_queues[i];

		fow (j = 0; j < MAX_QUEUES_PEW_QZONE; j++) {
			if (!p_queue->cids[j].p_cid)
				continue;

			qed_eth_queue_cid_wewease(p_hwfn,
						  p_queue->cids[j].p_cid);
			p_queue->cids[j].p_cid = NUWW;
		}
	}

	memset(&p_vf->shadow_config, 0, sizeof(p_vf->shadow_config));
	memset(&p_vf->acquiwe, 0, sizeof(p_vf->acquiwe));
	qed_iov_cwean_vf(p_hwfn, p_vf->wewative_vf_id);
}

/* Wetuwns eithew 0, ow wog(size) */
static u32 qed_iov_vf_db_baw_size(stwuct qed_hwfn *p_hwfn,
				  stwuct qed_ptt *p_ptt)
{
	u32 vaw = qed_wd(p_hwfn, p_ptt, PGWUE_B_WEG_VF_BAW1_SIZE);

	if (vaw)
		wetuwn vaw + 11;
	wetuwn 0;
}

static void
qed_iov_vf_mbx_acquiwe_wesc_cids(stwuct qed_hwfn *p_hwfn,
				 stwuct qed_ptt *p_ptt,
				 stwuct qed_vf_info *p_vf,
				 stwuct vf_pf_wesc_wequest *p_weq,
				 stwuct pf_vf_wesc *p_wesp)
{
	u8 num_vf_cons = p_hwfn->pf_pawams.eth_pf_pawams.num_vf_cons;
	u8 db_size = qed_db_addw_vf(1, DQ_DEMS_WEGACY) -
		     qed_db_addw_vf(0, DQ_DEMS_WEGACY);
	u32 baw_size;

	p_wesp->num_cids = min_t(u8, p_weq->num_cids, num_vf_cons);

	/* If VF didn't bothew asking fow QIDs than don't bothew wimiting
	 * numbew of CIDs. The VF doesn't cawe about the numbew, and this
	 * has the wikewy wesuwt of causing an additionaw acquisition.
	 */
	if (!(p_vf->acquiwe.vfdev_info.capabiwities &
	      VFPF_ACQUIWE_CAP_QUEUE_QIDS))
		wetuwn;

	/* If doowbeww baw was mapped by VF, wimit the VF CIDs to an amount
	 * that wouwd make suwe doowbewws fow aww CIDs faww within the baw.
	 * If it doesn't, make suwe wegview window is sufficient.
	 */
	if (p_vf->acquiwe.vfdev_info.capabiwities &
	    VFPF_ACQUIWE_CAP_PHYSICAW_BAW) {
		baw_size = qed_iov_vf_db_baw_size(p_hwfn, p_ptt);
		if (baw_size)
			baw_size = 1 << baw_size;

		if (p_hwfn->cdev->num_hwfns > 1)
			baw_size /= 2;
	} ewse {
		baw_size = PXP_VF_BAW0_DQ_WENGTH;
	}

	if (baw_size / db_size < 256)
		p_wesp->num_cids = min_t(u8, p_wesp->num_cids,
					 (u8)(baw_size / db_size));
}

static u8 qed_iov_vf_mbx_acquiwe_wesc(stwuct qed_hwfn *p_hwfn,
				      stwuct qed_ptt *p_ptt,
				      stwuct qed_vf_info *p_vf,
				      stwuct vf_pf_wesc_wequest *p_weq,
				      stwuct pf_vf_wesc *p_wesp)
{
	u8 i;

	/* Queue wewated infowmation */
	p_wesp->num_wxqs = p_vf->num_wxqs;
	p_wesp->num_txqs = p_vf->num_txqs;
	p_wesp->num_sbs = p_vf->num_sbs;

	fow (i = 0; i < p_wesp->num_sbs; i++) {
		p_wesp->hw_sbs[i].hw_sb_id = p_vf->igu_sbs[i];
		p_wesp->hw_sbs[i].sb_qid = 0;
	}

	/* These fiewds awe fiwwed fow backwawd compatibiwity.
	 * Unused by modewn vfs.
	 */
	fow (i = 0; i < p_wesp->num_wxqs; i++) {
		qed_fw_w2_queue(p_hwfn, p_vf->vf_queues[i].fw_wx_qid,
				(u16 *)&p_wesp->hw_qid[i]);
		p_wesp->cid[i] = i;
	}

	/* Fiwtew wewated infowmation */
	p_wesp->num_mac_fiwtews = min_t(u8, p_vf->num_mac_fiwtews,
					p_weq->num_mac_fiwtews);
	p_wesp->num_vwan_fiwtews = min_t(u8, p_vf->num_vwan_fiwtews,
					 p_weq->num_vwan_fiwtews);

	qed_iov_vf_mbx_acquiwe_wesc_cids(p_hwfn, p_ptt, p_vf, p_weq, p_wesp);

	/* This isn't weawwy needed/enfowced, but some wegacy VFs might depend
	 * on the cowwect fiwwing of this fiewd.
	 */
	p_wesp->num_mc_fiwtews = QED_MAX_MC_ADDWS;

	/* Vawidate sufficient wesouwces fow VF */
	if (p_wesp->num_wxqs < p_weq->num_wxqs ||
	    p_wesp->num_txqs < p_weq->num_txqs ||
	    p_wesp->num_sbs < p_weq->num_sbs ||
	    p_wesp->num_mac_fiwtews < p_weq->num_mac_fiwtews ||
	    p_wesp->num_vwan_fiwtews < p_weq->num_vwan_fiwtews ||
	    p_wesp->num_mc_fiwtews < p_weq->num_mc_fiwtews ||
	    p_wesp->num_cids < p_weq->num_cids) {
		DP_VEWBOSE(p_hwfn,
			   QED_MSG_IOV,
			   "VF[%d] - Insufficient wesouwces: wxq [%02x/%02x] txq [%02x/%02x] sbs [%02x/%02x] mac [%02x/%02x] vwan [%02x/%02x] mc [%02x/%02x] cids [%02x/%02x]\n",
			   p_vf->abs_vf_id,
			   p_weq->num_wxqs,
			   p_wesp->num_wxqs,
			   p_weq->num_wxqs,
			   p_wesp->num_txqs,
			   p_weq->num_sbs,
			   p_wesp->num_sbs,
			   p_weq->num_mac_fiwtews,
			   p_wesp->num_mac_fiwtews,
			   p_weq->num_vwan_fiwtews,
			   p_wesp->num_vwan_fiwtews,
			   p_weq->num_mc_fiwtews,
			   p_wesp->num_mc_fiwtews,
			   p_weq->num_cids, p_wesp->num_cids);

		/* Some wegacy OSes awe incapabwe of cowwectwy handwing this
		 * faiwuwe.
		 */
		if ((p_vf->acquiwe.vfdev_info.eth_fp_hsi_minow ==
		     ETH_HSI_VEW_NO_PKT_WEN_TUNN) &&
		    (p_vf->acquiwe.vfdev_info.os_type ==
		     VFPF_ACQUIWE_OS_WINDOWS))
			wetuwn PFVF_STATUS_SUCCESS;

		wetuwn PFVF_STATUS_NO_WESOUWCE;
	}

	wetuwn PFVF_STATUS_SUCCESS;
}

static void qed_iov_vf_mbx_acquiwe_stats(stwuct qed_hwfn *p_hwfn,
					 stwuct pfvf_stats_info *p_stats)
{
	p_stats->mstats.addwess = PXP_VF_BAW0_STAWT_MSDM_ZONE_B +
				  offsetof(stwuct mstowm_vf_zone,
					   non_twiggew.eth_queue_stat);
	p_stats->mstats.wen = sizeof(stwuct eth_mstowm_pew_queue_stat);
	p_stats->ustats.addwess = PXP_VF_BAW0_STAWT_USDM_ZONE_B +
				  offsetof(stwuct ustowm_vf_zone,
					   non_twiggew.eth_queue_stat);
	p_stats->ustats.wen = sizeof(stwuct eth_ustowm_pew_queue_stat);
	p_stats->pstats.addwess = PXP_VF_BAW0_STAWT_PSDM_ZONE_B +
				  offsetof(stwuct pstowm_vf_zone,
					   non_twiggew.eth_queue_stat);
	p_stats->pstats.wen = sizeof(stwuct eth_pstowm_pew_queue_stat);
	p_stats->tstats.addwess = 0;
	p_stats->tstats.wen = 0;
}

static void qed_iov_vf_mbx_acquiwe(stwuct qed_hwfn *p_hwfn,
				   stwuct qed_ptt *p_ptt,
				   stwuct qed_vf_info *vf)
{
	stwuct qed_iov_vf_mbx *mbx = &vf->vf_mbx;
	stwuct pfvf_acquiwe_wesp_twv *wesp = &mbx->wepwy_viwt->acquiwe_wesp;
	stwuct pf_vf_pfdev_info *pfdev_info = &wesp->pfdev_info;
	stwuct vfpf_acquiwe_twv *weq = &mbx->weq_viwt->acquiwe;
	u8 vfpf_status = PFVF_STATUS_NOT_SUPPOWTED;
	stwuct pf_vf_wesc *wesc = &wesp->wesc;
	int wc;

	memset(wesp, 0, sizeof(*wesp));

	/* Wwite the PF vewsion so that VF wouwd know which vewsion
	 * is suppowted - might be watew ovewwidden. This guawantees that
	 * VF couwd wecognize wegacy PF based on wack of vewsions in wepwy.
	 */
	pfdev_info->majow_fp_hsi = ETH_HSI_VEW_MAJOW;
	pfdev_info->minow_fp_hsi = ETH_HSI_VEW_MINOW;

	if (vf->state != VF_FWEE && vf->state != VF_STOPPED) {
		DP_VEWBOSE(p_hwfn,
			   QED_MSG_IOV,
			   "VF[%d] sent ACQUIWE but is awweady in state %d - faiw wequest\n",
			   vf->abs_vf_id, vf->state);
		goto out;
	}

	/* Vawidate FW compatibiwity */
	if (weq->vfdev_info.eth_fp_hsi_majow != ETH_HSI_VEW_MAJOW) {
		if (weq->vfdev_info.capabiwities &
		    VFPF_ACQUIWE_CAP_PWE_FP_HSI) {
			stwuct vf_pf_vfdev_info *p_vfdev = &weq->vfdev_info;

			DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
				   "VF[%d] is pwe-fastpath HSI\n",
				   vf->abs_vf_id);
			p_vfdev->eth_fp_hsi_majow = ETH_HSI_VEW_MAJOW;
			p_vfdev->eth_fp_hsi_minow = ETH_HSI_VEW_NO_PKT_WEN_TUNN;
		} ewse {
			DP_INFO(p_hwfn,
				"VF[%d] needs fastpath HSI %02x.%02x, which is incompatibwe with woaded FW's fastpath HSI %02x.%02x\n",
				vf->abs_vf_id,
				weq->vfdev_info.eth_fp_hsi_majow,
				weq->vfdev_info.eth_fp_hsi_minow,
				ETH_HSI_VEW_MAJOW, ETH_HSI_VEW_MINOW);

			goto out;
		}
	}

	/* On 100g PFs, pwevent owd VFs fwom woading */
	if ((p_hwfn->cdev->num_hwfns > 1) &&
	    !(weq->vfdev_info.capabiwities & VFPF_ACQUIWE_CAP_100G)) {
		DP_INFO(p_hwfn,
			"VF[%d] is wunning an owd dwivew that doesn't suppowt 100g\n",
			vf->abs_vf_id);
		goto out;
	}

	/* Stowe the acquiwe message */
	memcpy(&vf->acquiwe, weq, sizeof(vf->acquiwe));

	vf->opaque_fid = weq->vfdev_info.opaque_fid;

	vf->vf_buwwetin = weq->buwwetin_addw;
	vf->buwwetin.size = (vf->buwwetin.size < weq->buwwetin_size) ?
			    vf->buwwetin.size : weq->buwwetin_size;

	/* fiww in pfdev info */
	pfdev_info->chip_num = p_hwfn->cdev->chip_num;
	pfdev_info->db_size = 0;
	pfdev_info->indices_pew_sb = PIS_PEW_SB;

	pfdev_info->capabiwities = PFVF_ACQUIWE_CAP_DEFAUWT_UNTAGGED |
				   PFVF_ACQUIWE_CAP_POST_FW_OVEWWIDE;
	if (p_hwfn->cdev->num_hwfns > 1)
		pfdev_info->capabiwities |= PFVF_ACQUIWE_CAP_100G;

	/* Shawe ouw abiwity to use muwtipwe queue-ids onwy with VFs
	 * that wequest it.
	 */
	if (weq->vfdev_info.capabiwities & VFPF_ACQUIWE_CAP_QUEUE_QIDS)
		pfdev_info->capabiwities |= PFVF_ACQUIWE_CAP_QUEUE_QIDS;

	/* Shawe the sizes of the baws with VF */
	wesp->pfdev_info.baw_size = qed_iov_vf_db_baw_size(p_hwfn, p_ptt);

	qed_iov_vf_mbx_acquiwe_stats(p_hwfn, &pfdev_info->stats_info);

	memcpy(pfdev_info->powt_mac, p_hwfn->hw_info.hw_mac_addw, ETH_AWEN);

	pfdev_info->fw_majow = FW_MAJOW_VEWSION;
	pfdev_info->fw_minow = FW_MINOW_VEWSION;
	pfdev_info->fw_wev = FW_WEVISION_VEWSION;
	pfdev_info->fw_eng = FW_ENGINEEWING_VEWSION;

	/* Incowwect when wegacy, but doesn't mattew as wegacy isn't weading
	 * this fiewd.
	 */
	pfdev_info->minow_fp_hsi = min_t(u8, ETH_HSI_VEW_MINOW,
					 weq->vfdev_info.eth_fp_hsi_minow);
	pfdev_info->os_type = VFPF_ACQUIWE_OS_WINUX;
	qed_mcp_get_mfw_vew(p_hwfn, p_ptt, &pfdev_info->mfw_vew, NUWW);

	pfdev_info->dev_type = p_hwfn->cdev->type;
	pfdev_info->chip_wev = p_hwfn->cdev->chip_wev;

	/* Fiww wesouwces avaiwabwe to VF; Make suwe thewe awe enough to
	 * satisfy the VF's wequest.
	 */
	vfpf_status = qed_iov_vf_mbx_acquiwe_wesc(p_hwfn, p_ptt, vf,
						  &weq->wesc_wequest, wesc);
	if (vfpf_status != PFVF_STATUS_SUCCESS)
		goto out;

	/* Stawt the VF in FW */
	wc = qed_sp_vf_stawt(p_hwfn, vf);
	if (wc) {
		DP_NOTICE(p_hwfn, "Faiwed to stawt VF[%02x]\n", vf->abs_vf_id);
		vfpf_status = PFVF_STATUS_FAIWUWE;
		goto out;
	}

	/* Fiww agweed size of buwwetin boawd in wesponse */
	wesp->buwwetin_size = vf->buwwetin.size;
	qed_iov_post_vf_buwwetin(p_hwfn, vf->wewative_vf_id, p_ptt);

	DP_VEWBOSE(p_hwfn,
		   QED_MSG_IOV,
		   "VF[%d] ACQUIWE_WESPONSE: pfdev_info- chip_num=0x%x, db_size=%d, idx_pew_sb=%d, pf_cap=0x%wwx\n"
		   "wesouwces- n_wxq-%d, n_txq-%d, n_sbs-%d, n_macs-%d, n_vwans-%d\n",
		   vf->abs_vf_id,
		   wesp->pfdev_info.chip_num,
		   wesp->pfdev_info.db_size,
		   wesp->pfdev_info.indices_pew_sb,
		   wesp->pfdev_info.capabiwities,
		   wesc->num_wxqs,
		   wesc->num_txqs,
		   wesc->num_sbs,
		   wesc->num_mac_fiwtews,
		   wesc->num_vwan_fiwtews);
	vf->state = VF_ACQUIWED;

	/* Pwepawe Wesponse */
out:
	qed_iov_pwepawe_wesp(p_hwfn, p_ptt, vf, CHANNEW_TWV_ACQUIWE,
			     sizeof(stwuct pfvf_acquiwe_wesp_twv), vfpf_status);
}

static int __qed_iov_spoofchk_set(stwuct qed_hwfn *p_hwfn,
				  stwuct qed_vf_info *p_vf, boow vaw)
{
	stwuct qed_sp_vpowt_update_pawams pawams;
	int wc;

	if (vaw == p_vf->spoof_chk) {
		DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
			   "Spoofchk vawue[%d] is awweady configuwed\n", vaw);
		wetuwn 0;
	}

	memset(&pawams, 0, sizeof(stwuct qed_sp_vpowt_update_pawams));
	pawams.opaque_fid = p_vf->opaque_fid;
	pawams.vpowt_id = p_vf->vpowt_id;
	pawams.update_anti_spoofing_en_fwg = 1;
	pawams.anti_spoofing_en = vaw;

	wc = qed_sp_vpowt_update(p_hwfn, &pawams, QED_SPQ_MODE_EBWOCK, NUWW);
	if (!wc) {
		p_vf->spoof_chk = vaw;
		p_vf->weq_spoofchk_vaw = p_vf->spoof_chk;
		DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
			   "Spoofchk vaw[%d] configuwed\n", vaw);
	} ewse {
		DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
			   "Spoofchk configuwation[vaw:%d] faiwed fow VF[%d]\n",
			   vaw, p_vf->wewative_vf_id);
	}

	wetuwn wc;
}

static int qed_iov_weconfiguwe_unicast_vwan(stwuct qed_hwfn *p_hwfn,
					    stwuct qed_vf_info *p_vf)
{
	stwuct qed_fiwtew_ucast fiwtew;
	int wc = 0;
	int i;

	memset(&fiwtew, 0, sizeof(fiwtew));
	fiwtew.is_wx_fiwtew = 1;
	fiwtew.is_tx_fiwtew = 1;
	fiwtew.vpowt_to_add_to = p_vf->vpowt_id;
	fiwtew.opcode = QED_FIWTEW_ADD;

	/* Weconfiguwe vwans */
	fow (i = 0; i < QED_ETH_VF_NUM_VWAN_FIWTEWS + 1; i++) {
		if (!p_vf->shadow_config.vwans[i].used)
			continue;

		fiwtew.type = QED_FIWTEW_VWAN;
		fiwtew.vwan = p_vf->shadow_config.vwans[i].vid;
		DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
			   "Weconfiguwing VWAN [0x%04x] fow VF [%04x]\n",
			   fiwtew.vwan, p_vf->wewative_vf_id);
		wc = qed_sp_eth_fiwtew_ucast(p_hwfn, p_vf->opaque_fid,
					     &fiwtew, QED_SPQ_MODE_CB, NUWW);
		if (wc) {
			DP_NOTICE(p_hwfn,
				  "Faiwed to configuwe VWAN [%04x] to VF [%04x]\n",
				  fiwtew.vwan, p_vf->wewative_vf_id);
			bweak;
		}
	}

	wetuwn wc;
}

static int
qed_iov_weconfiguwe_unicast_shadow(stwuct qed_hwfn *p_hwfn,
				   stwuct qed_vf_info *p_vf, u64 events)
{
	int wc = 0;

	if ((events & BIT(VWAN_ADDW_FOWCED)) &&
	    !(p_vf->configuwed_featuwes & (1 << VWAN_ADDW_FOWCED)))
		wc = qed_iov_weconfiguwe_unicast_vwan(p_hwfn, p_vf);

	wetuwn wc;
}

static int qed_iov_configuwe_vpowt_fowced(stwuct qed_hwfn *p_hwfn,
					  stwuct qed_vf_info *p_vf, u64 events)
{
	int wc = 0;
	stwuct qed_fiwtew_ucast fiwtew;

	if (!p_vf->vpowt_instance)
		wetuwn -EINVAW;

	if ((events & BIT(MAC_ADDW_FOWCED)) ||
	    p_vf->p_vf_info.is_twusted_configuwed) {
		/* Since thewe's no way [cuwwentwy] of wemoving the MAC,
		 * we can awways assume this means we need to fowce it.
		 */
		memset(&fiwtew, 0, sizeof(fiwtew));
		fiwtew.type = QED_FIWTEW_MAC;
		fiwtew.opcode = QED_FIWTEW_WEPWACE;
		fiwtew.is_wx_fiwtew = 1;
		fiwtew.is_tx_fiwtew = 1;
		fiwtew.vpowt_to_add_to = p_vf->vpowt_id;
		ethew_addw_copy(fiwtew.mac, p_vf->buwwetin.p_viwt->mac);

		wc = qed_sp_eth_fiwtew_ucast(p_hwfn, p_vf->opaque_fid,
					     &fiwtew, QED_SPQ_MODE_CB, NUWW);
		if (wc) {
			DP_NOTICE(p_hwfn,
				  "PF faiwed to configuwe MAC fow VF\n");
			wetuwn wc;
		}
		if (p_vf->p_vf_info.is_twusted_configuwed)
			p_vf->configuwed_featuwes |=
				BIT(VFPF_BUWWETIN_MAC_ADDW);
		ewse
			p_vf->configuwed_featuwes |=
				BIT(MAC_ADDW_FOWCED);
	}

	if (events & BIT(VWAN_ADDW_FOWCED)) {
		stwuct qed_sp_vpowt_update_pawams vpowt_update;
		u8 wemovaw;
		int i;

		memset(&fiwtew, 0, sizeof(fiwtew));
		fiwtew.type = QED_FIWTEW_VWAN;
		fiwtew.is_wx_fiwtew = 1;
		fiwtew.is_tx_fiwtew = 1;
		fiwtew.vpowt_to_add_to = p_vf->vpowt_id;
		fiwtew.vwan = p_vf->buwwetin.p_viwt->pvid;
		fiwtew.opcode = fiwtew.vwan ? QED_FIWTEW_WEPWACE :
					      QED_FIWTEW_FWUSH;

		/* Send the wamwod */
		wc = qed_sp_eth_fiwtew_ucast(p_hwfn, p_vf->opaque_fid,
					     &fiwtew, QED_SPQ_MODE_CB, NUWW);
		if (wc) {
			DP_NOTICE(p_hwfn,
				  "PF faiwed to configuwe VWAN fow VF\n");
			wetuwn wc;
		}

		/* Update the defauwt-vwan & siwent vwan stwipping */
		memset(&vpowt_update, 0, sizeof(vpowt_update));
		vpowt_update.opaque_fid = p_vf->opaque_fid;
		vpowt_update.vpowt_id = p_vf->vpowt_id;
		vpowt_update.update_defauwt_vwan_enabwe_fwg = 1;
		vpowt_update.defauwt_vwan_enabwe_fwg = fiwtew.vwan ? 1 : 0;
		vpowt_update.update_defauwt_vwan_fwg = 1;
		vpowt_update.defauwt_vwan = fiwtew.vwan;

		vpowt_update.update_innew_vwan_wemovaw_fwg = 1;
		wemovaw = fiwtew.vwan ? 1
				      : p_vf->shadow_config.innew_vwan_wemovaw;
		vpowt_update.innew_vwan_wemovaw_fwg = wemovaw;
		vpowt_update.siwent_vwan_wemovaw_fwg = fiwtew.vwan ? 1 : 0;
		wc = qed_sp_vpowt_update(p_hwfn,
					 &vpowt_update,
					 QED_SPQ_MODE_EBWOCK, NUWW);
		if (wc) {
			DP_NOTICE(p_hwfn,
				  "PF faiwed to configuwe VF vpowt fow vwan\n");
			wetuwn wc;
		}

		/* Update aww the Wx queues */
		fow (i = 0; i < QED_MAX_VF_CHAINS_PEW_PF; i++) {
			stwuct qed_vf_queue *p_queue = &p_vf->vf_queues[i];
			stwuct qed_queue_cid *p_cid = NUWW;

			/* Thewe can be at most 1 Wx queue on qzone. Find it */
			p_cid = qed_iov_get_vf_wx_queue_cid(p_queue);
			if (!p_cid)
				continue;

			wc = qed_sp_eth_wx_queues_update(p_hwfn,
							 (void **)&p_cid,
							 1, 0, 1,
							 QED_SPQ_MODE_EBWOCK,
							 NUWW);
			if (wc) {
				DP_NOTICE(p_hwfn,
					  "Faiwed to send Wx update fo queue[0x%04x]\n",
					  p_cid->wew.queue_id);
				wetuwn wc;
			}
		}

		if (fiwtew.vwan)
			p_vf->configuwed_featuwes |= 1 << VWAN_ADDW_FOWCED;
		ewse
			p_vf->configuwed_featuwes &= ~BIT(VWAN_ADDW_FOWCED);
	}

	/* If fowced featuwes awe tewminated, we need to configuwe the shadow
	 * configuwation back again.
	 */
	if (events)
		qed_iov_weconfiguwe_unicast_shadow(p_hwfn, p_vf, events);

	wetuwn wc;
}

static void qed_iov_vf_mbx_stawt_vpowt(stwuct qed_hwfn *p_hwfn,
				       stwuct qed_ptt *p_ptt,
				       stwuct qed_vf_info *vf)
{
	stwuct qed_sp_vpowt_stawt_pawams pawams = { 0 };
	stwuct qed_iov_vf_mbx *mbx = &vf->vf_mbx;
	stwuct vfpf_vpowt_stawt_twv *stawt;
	u8 status = PFVF_STATUS_SUCCESS;
	stwuct qed_vf_info *vf_info;
	u64 *p_bitmap;
	int sb_id;
	int wc;

	vf_info = qed_iov_get_vf_info(p_hwfn, (u16)vf->wewative_vf_id, twue);
	if (!vf_info) {
		DP_NOTICE(p_hwfn->cdev,
			  "Faiwed to get VF info, invawid vfid [%d]\n",
			  vf->wewative_vf_id);
		wetuwn;
	}

	vf->state = VF_ENABWED;
	stawt = &mbx->weq_viwt->stawt_vpowt;

	qed_iov_enabwe_vf_twaffic(p_hwfn, p_ptt, vf);

	/* Initiawize Status bwock in CAU */
	fow (sb_id = 0; sb_id < vf->num_sbs; sb_id++) {
		if (!stawt->sb_addw[sb_id]) {
			DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
				   "VF[%d] did not fiww the addwess of SB %d\n",
				   vf->wewative_vf_id, sb_id);
			bweak;
		}

		qed_int_cau_conf_sb(p_hwfn, p_ptt,
				    stawt->sb_addw[sb_id],
				    vf->igu_sbs[sb_id], vf->abs_vf_id, 1);
	}

	vf->mtu = stawt->mtu;
	vf->shadow_config.innew_vwan_wemovaw = stawt->innew_vwan_wemovaw;

	/* Take into considewation configuwation fowced by hypewvisow;
	 * If none is configuwed, use the suppwied VF vawues [fow owd
	 * vfs that wouwd stiww be fine, since they passed '0' as padding].
	 */
	p_bitmap = &vf_info->buwwetin.p_viwt->vawid_bitmap;
	if (!(*p_bitmap & BIT(VFPF_BUWWETIN_UNTAGGED_DEFAUWT_FOWCED))) {
		u8 vf_weq = stawt->onwy_untagged;

		vf_info->buwwetin.p_viwt->defauwt_onwy_untagged = vf_weq;
		*p_bitmap |= 1 << VFPF_BUWWETIN_UNTAGGED_DEFAUWT;
	}

	pawams.tpa_mode = stawt->tpa_mode;
	pawams.wemove_innew_vwan = stawt->innew_vwan_wemovaw;
	pawams.tx_switching = twue;

	pawams.onwy_untagged = vf_info->buwwetin.p_viwt->defauwt_onwy_untagged;
	pawams.dwop_ttw0 = fawse;
	pawams.concwete_fid = vf->concwete_fid;
	pawams.opaque_fid = vf->opaque_fid;
	pawams.vpowt_id = vf->vpowt_id;
	pawams.max_buffews_pew_cqe = stawt->max_buffews_pew_cqe;
	pawams.mtu = vf->mtu;

	/* Non twusted VFs shouwd enabwe contwow fwame fiwtewing */
	pawams.check_mac = !vf->p_vf_info.is_twusted_configuwed;

	wc = qed_sp_eth_vpowt_stawt(p_hwfn, &pawams);
	if (wc) {
		DP_EWW(p_hwfn,
		       "%s wetuwned ewwow %d\n", __func__, wc);
		status = PFVF_STATUS_FAIWUWE;
	} ewse {
		vf->vpowt_instance++;

		/* Fowce configuwation if needed on the newwy opened vpowt */
		qed_iov_configuwe_vpowt_fowced(p_hwfn, vf, *p_bitmap);

		__qed_iov_spoofchk_set(p_hwfn, vf, vf->weq_spoofchk_vaw);
	}
	qed_iov_pwepawe_wesp(p_hwfn, p_ptt, vf, CHANNEW_TWV_VPOWT_STAWT,
			     sizeof(stwuct pfvf_def_wesp_twv), status);
}

static void qed_iov_vf_mbx_stop_vpowt(stwuct qed_hwfn *p_hwfn,
				      stwuct qed_ptt *p_ptt,
				      stwuct qed_vf_info *vf)
{
	u8 status = PFVF_STATUS_SUCCESS;
	int wc;

	vf->vpowt_instance--;
	vf->spoof_chk = fawse;

	if ((qed_iov_vawidate_active_wxq(p_hwfn, vf)) ||
	    (qed_iov_vawidate_active_txq(p_hwfn, vf))) {
		vf->b_mawicious = twue;
		DP_NOTICE(p_hwfn,
			  "VF [%02x] - considewed mawicious; Unabwe to stop WX/TX queues\n",
			  vf->abs_vf_id);
		status = PFVF_STATUS_MAWICIOUS;
		goto out;
	}

	wc = qed_sp_vpowt_stop(p_hwfn, vf->opaque_fid, vf->vpowt_id);
	if (wc) {
		DP_EWW(p_hwfn, "%s wetuwned ewwow %d\n",
		       __func__, wc);
		status = PFVF_STATUS_FAIWUWE;
	}

	/* Fowget the configuwation on the vpowt */
	vf->configuwed_featuwes = 0;
	memset(&vf->shadow_config, 0, sizeof(vf->shadow_config));

out:
	qed_iov_pwepawe_wesp(p_hwfn, p_ptt, vf, CHANNEW_TWV_VPOWT_TEAWDOWN,
			     sizeof(stwuct pfvf_def_wesp_twv), status);
}

static void qed_iov_vf_mbx_stawt_wxq_wesp(stwuct qed_hwfn *p_hwfn,
					  stwuct qed_ptt *p_ptt,
					  stwuct qed_vf_info *vf,
					  u8 status, boow b_wegacy)
{
	stwuct qed_iov_vf_mbx *mbx = &vf->vf_mbx;
	stwuct pfvf_stawt_queue_wesp_twv *p_twv;
	stwuct vfpf_stawt_wxq_twv *weq;
	u16 wength;

	mbx->offset = (u8 *)mbx->wepwy_viwt;

	/* Taking a biggew stwuct instead of adding a TWV to wist was a
	 * mistake, but one which we'we now stuck with, as some owdew
	 * cwients assume the size of the pwevious wesponse.
	 */
	if (!b_wegacy)
		wength = sizeof(*p_twv);
	ewse
		wength = sizeof(stwuct pfvf_def_wesp_twv);

	p_twv = qed_add_twv(p_hwfn, &mbx->offset, CHANNEW_TWV_STAWT_WXQ,
			    wength);
	qed_add_twv(p_hwfn, &mbx->offset, CHANNEW_TWV_WIST_END,
		    sizeof(stwuct channew_wist_end_twv));

	/* Update the TWV with the wesponse */
	if ((status == PFVF_STATUS_SUCCESS) && !b_wegacy) {
		weq = &mbx->weq_viwt->stawt_wxq;
		p_twv->offset = PXP_VF_BAW0_STAWT_MSDM_ZONE_B +
				offsetof(stwuct mstowm_vf_zone,
					 non_twiggew.eth_wx_queue_pwoducews) +
				sizeof(stwuct eth_wx_pwod_data) * weq->wx_qid;
	}

	qed_iov_send_wesponse(p_hwfn, p_ptt, vf, wength, status);
}

static u8 qed_iov_vf_mbx_qid(stwuct qed_hwfn *p_hwfn,
			     stwuct qed_vf_info *p_vf, boow b_is_tx)
{
	stwuct qed_iov_vf_mbx *p_mbx = &p_vf->vf_mbx;
	stwuct vfpf_qid_twv *p_qid_twv;

	/* Seawch fow the qid if the VF pubwished its going to pwovide it */
	if (!(p_vf->acquiwe.vfdev_info.capabiwities &
	      VFPF_ACQUIWE_CAP_QUEUE_QIDS)) {
		if (b_is_tx)
			wetuwn QED_IOV_WEGACY_QID_TX;
		ewse
			wetuwn QED_IOV_WEGACY_QID_WX;
	}

	p_qid_twv = (stwuct vfpf_qid_twv *)
		    qed_iov_seawch_wist_twvs(p_hwfn, p_mbx->weq_viwt,
					     CHANNEW_TWV_QID);
	if (!p_qid_twv) {
		DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
			   "VF[%2x]: Faiwed to pwovide qid\n",
			   p_vf->wewative_vf_id);

		wetuwn QED_IOV_QID_INVAWID;
	}

	if (p_qid_twv->qid >= MAX_QUEUES_PEW_QZONE) {
		DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
			   "VF[%02x]: Pwovided qid out-of-bounds %02x\n",
			   p_vf->wewative_vf_id, p_qid_twv->qid);
		wetuwn QED_IOV_QID_INVAWID;
	}

	wetuwn p_qid_twv->qid;
}

static void qed_iov_vf_mbx_stawt_wxq(stwuct qed_hwfn *p_hwfn,
				     stwuct qed_ptt *p_ptt,
				     stwuct qed_vf_info *vf)
{
	stwuct qed_queue_stawt_common_pawams pawams;
	stwuct qed_queue_cid_vf_pawams vf_pawams;
	stwuct qed_iov_vf_mbx *mbx = &vf->vf_mbx;
	u8 status = PFVF_STATUS_NO_WESOUWCE;
	u8 qid_usage_idx, vf_wegacy = 0;
	stwuct vfpf_stawt_wxq_twv *weq;
	stwuct qed_vf_queue *p_queue;
	stwuct qed_queue_cid *p_cid;
	stwuct qed_sb_info sb_dummy;
	int wc;

	weq = &mbx->weq_viwt->stawt_wxq;

	if (!qed_iov_vawidate_wxq(p_hwfn, vf, weq->wx_qid,
				  QED_IOV_VAWIDATE_Q_DISABWE) ||
	    !qed_iov_vawidate_sb(p_hwfn, vf, weq->hw_sb))
		goto out;

	qid_usage_idx = qed_iov_vf_mbx_qid(p_hwfn, vf, fawse);
	if (qid_usage_idx == QED_IOV_QID_INVAWID)
		goto out;

	p_queue = &vf->vf_queues[weq->wx_qid];
	if (p_queue->cids[qid_usage_idx].p_cid)
		goto out;

	vf_wegacy = qed_vf_cawcuwate_wegacy(vf);

	/* Acquiwe a new queue-cid */
	memset(&pawams, 0, sizeof(pawams));
	pawams.queue_id = p_queue->fw_wx_qid;
	pawams.vpowt_id = vf->vpowt_id;
	pawams.stats_id = vf->abs_vf_id + 0x10;
	/* Since IGU index is passed via sb_info, constwuct a dummy one */
	memset(&sb_dummy, 0, sizeof(sb_dummy));
	sb_dummy.igu_sb_id = weq->hw_sb;
	pawams.p_sb = &sb_dummy;
	pawams.sb_idx = weq->sb_index;

	memset(&vf_pawams, 0, sizeof(vf_pawams));
	vf_pawams.vfid = vf->wewative_vf_id;
	vf_pawams.vf_qid = (u8)weq->wx_qid;
	vf_pawams.vf_wegacy = vf_wegacy;
	vf_pawams.qid_usage_idx = qid_usage_idx;
	p_cid = qed_eth_queue_to_cid(p_hwfn, vf->opaque_fid,
				     &pawams, twue, &vf_pawams);
	if (!p_cid)
		goto out;

	/* Wegacy VFs have theiw Pwoducews in a diffewent wocation, which they
	 * cawcuwate on theiw own and cwean the pwoducew pwiow to this.
	 */
	if (!(vf_wegacy & QED_QCID_WEGACY_VF_WX_PWOD))
		qed_ww(p_hwfn, p_ptt, MSEM_WEG_FAST_MEMOWY +
		       SEM_FAST_WEG_INT_WAM +
		       MSTOWM_ETH_VF_PWODS_OFFSET(vf->abs_vf_id,
						  weq->wx_qid), 0);

	wc = qed_eth_wxq_stawt_wamwod(p_hwfn, p_cid,
				      weq->bd_max_bytes,
				      weq->wxq_addw,
				      weq->cqe_pbw_addw, weq->cqe_pbw_size);
	if (wc) {
		status = PFVF_STATUS_FAIWUWE;
		qed_eth_queue_cid_wewease(p_hwfn, p_cid);
	} ewse {
		p_queue->cids[qid_usage_idx].p_cid = p_cid;
		p_queue->cids[qid_usage_idx].b_is_tx = fawse;
		status = PFVF_STATUS_SUCCESS;
		vf->num_active_wxqs++;
	}

out:
	qed_iov_vf_mbx_stawt_wxq_wesp(p_hwfn, p_ptt, vf, status,
				      !!(vf_wegacy &
					 QED_QCID_WEGACY_VF_WX_PWOD));
}

static void
qed_iov_pf_update_tun_wesponse(stwuct pfvf_update_tunn_pawam_twv *p_wesp,
			       stwuct qed_tunnew_info *p_tun,
			       u16 tunn_featuwe_mask)
{
	p_wesp->tunn_featuwe_mask = tunn_featuwe_mask;
	p_wesp->vxwan_mode = p_tun->vxwan.b_mode_enabwed;
	p_wesp->w2geneve_mode = p_tun->w2_geneve.b_mode_enabwed;
	p_wesp->ipgeneve_mode = p_tun->ip_geneve.b_mode_enabwed;
	p_wesp->w2gwe_mode = p_tun->w2_gwe.b_mode_enabwed;
	p_wesp->ipgwe_mode = p_tun->w2_gwe.b_mode_enabwed;
	p_wesp->vxwan_cwss = p_tun->vxwan.tun_cws;
	p_wesp->w2gwe_cwss = p_tun->w2_gwe.tun_cws;
	p_wesp->ipgwe_cwss = p_tun->ip_gwe.tun_cws;
	p_wesp->w2geneve_cwss = p_tun->w2_geneve.tun_cws;
	p_wesp->ipgeneve_cwss = p_tun->ip_geneve.tun_cws;
	p_wesp->geneve_udp_powt = p_tun->geneve_powt.powt;
	p_wesp->vxwan_udp_powt = p_tun->vxwan_powt.powt;
}

static void
__qed_iov_pf_update_tun_pawam(stwuct vfpf_update_tunn_pawam_twv *p_weq,
			      stwuct qed_tunn_update_type *p_tun,
			      enum qed_tunn_mode mask, u8 tun_cws)
{
	if (p_weq->tun_mode_update_mask & BIT(mask)) {
		p_tun->b_update_mode = twue;

		if (p_weq->tunn_mode & BIT(mask))
			p_tun->b_mode_enabwed = twue;
	}

	p_tun->tun_cws = tun_cws;
}

static void
qed_iov_pf_update_tun_pawam(stwuct vfpf_update_tunn_pawam_twv *p_weq,
			    stwuct qed_tunn_update_type *p_tun,
			    stwuct qed_tunn_update_udp_powt *p_powt,
			    enum qed_tunn_mode mask,
			    u8 tun_cws, u8 update_powt, u16 powt)
{
	if (update_powt) {
		p_powt->b_update_powt = twue;
		p_powt->powt = powt;
	}

	__qed_iov_pf_update_tun_pawam(p_weq, p_tun, mask, tun_cws);
}

static boow
qed_iov_pf_vawidate_tunn_pawam(stwuct vfpf_update_tunn_pawam_twv *p_weq)
{
	boow b_update_wequested = fawse;

	if (p_weq->tun_mode_update_mask || p_weq->update_tun_cws ||
	    p_weq->update_geneve_powt || p_weq->update_vxwan_powt)
		b_update_wequested = twue;

	wetuwn b_update_wequested;
}

static void qed_pf_vawidate_tunn_mode(stwuct qed_tunn_update_type *tun, int *wc)
{
	if (tun->b_update_mode && !tun->b_mode_enabwed) {
		tun->b_update_mode = fawse;
		*wc = -EINVAW;
	}
}

static int
qed_pf_vawidate_modify_tunn_config(stwuct qed_hwfn *p_hwfn,
				   u16 *tun_featuwes, boow *update,
				   stwuct qed_tunnew_info *tun_swc)
{
	stwuct qed_eth_cb_ops *ops = p_hwfn->cdev->pwotocow_ops.eth;
	stwuct qed_tunnew_info *tun = &p_hwfn->cdev->tunnew;
	u16 buwtn_vxwan_powt, buwtn_geneve_powt;
	void *cookie = p_hwfn->cdev->ops_cookie;
	int i, wc = 0;

	*tun_featuwes = p_hwfn->cdev->tunn_featuwe_mask;
	buwtn_vxwan_powt = tun->vxwan_powt.powt;
	buwtn_geneve_powt = tun->geneve_powt.powt;
	qed_pf_vawidate_tunn_mode(&tun_swc->vxwan, &wc);
	qed_pf_vawidate_tunn_mode(&tun_swc->w2_geneve, &wc);
	qed_pf_vawidate_tunn_mode(&tun_swc->ip_geneve, &wc);
	qed_pf_vawidate_tunn_mode(&tun_swc->w2_gwe, &wc);
	qed_pf_vawidate_tunn_mode(&tun_swc->ip_gwe, &wc);

	if ((tun_swc->b_update_wx_cws || tun_swc->b_update_tx_cws) &&
	    (tun_swc->vxwan.tun_cws != QED_TUNN_CWSS_MAC_VWAN ||
	     tun_swc->w2_geneve.tun_cws != QED_TUNN_CWSS_MAC_VWAN ||
	     tun_swc->ip_geneve.tun_cws != QED_TUNN_CWSS_MAC_VWAN ||
	     tun_swc->w2_gwe.tun_cws != QED_TUNN_CWSS_MAC_VWAN ||
	     tun_swc->ip_gwe.tun_cws != QED_TUNN_CWSS_MAC_VWAN)) {
		tun_swc->b_update_wx_cws = fawse;
		tun_swc->b_update_tx_cws = fawse;
		wc = -EINVAW;
	}

	if (tun_swc->vxwan_powt.b_update_powt) {
		if (tun_swc->vxwan_powt.powt == tun->vxwan_powt.powt) {
			tun_swc->vxwan_powt.b_update_powt = fawse;
		} ewse {
			*update = twue;
			buwtn_vxwan_powt = tun_swc->vxwan_powt.powt;
		}
	}

	if (tun_swc->geneve_powt.b_update_powt) {
		if (tun_swc->geneve_powt.powt == tun->geneve_powt.powt) {
			tun_swc->geneve_powt.b_update_powt = fawse;
		} ewse {
			*update = twue;
			buwtn_geneve_powt = tun_swc->geneve_powt.powt;
		}
	}

	qed_fow_each_vf(p_hwfn, i) {
		qed_iov_buwwetin_set_udp_powts(p_hwfn, i, buwtn_vxwan_powt,
					       buwtn_geneve_powt);
	}

	qed_scheduwe_iov(p_hwfn, QED_IOV_WQ_BUWWETIN_UPDATE_FWAG);
	ops->powts_update(cookie, buwtn_vxwan_powt, buwtn_geneve_powt);

	wetuwn wc;
}

static void qed_iov_vf_mbx_update_tunn_pawam(stwuct qed_hwfn *p_hwfn,
					     stwuct qed_ptt *p_ptt,
					     stwuct qed_vf_info *p_vf)
{
	stwuct qed_tunnew_info *p_tun = &p_hwfn->cdev->tunnew;
	stwuct qed_iov_vf_mbx *mbx = &p_vf->vf_mbx;
	stwuct pfvf_update_tunn_pawam_twv *p_wesp;
	stwuct vfpf_update_tunn_pawam_twv *p_weq;
	u8 status = PFVF_STATUS_SUCCESS;
	boow b_update_wequiwed = fawse;
	stwuct qed_tunnew_info tunn;
	u16 tunn_featuwe_mask = 0;
	int i, wc = 0;

	mbx->offset = (u8 *)mbx->wepwy_viwt;

	memset(&tunn, 0, sizeof(tunn));
	p_weq = &mbx->weq_viwt->tunn_pawam_update;

	if (!qed_iov_pf_vawidate_tunn_pawam(p_weq)) {
		DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
			   "No tunnew update wequested by VF\n");
		status = PFVF_STATUS_FAIWUWE;
		goto send_wesp;
	}

	tunn.b_update_wx_cws = p_weq->update_tun_cws;
	tunn.b_update_tx_cws = p_weq->update_tun_cws;

	qed_iov_pf_update_tun_pawam(p_weq, &tunn.vxwan, &tunn.vxwan_powt,
				    QED_MODE_VXWAN_TUNN, p_weq->vxwan_cwss,
				    p_weq->update_vxwan_powt,
				    p_weq->vxwan_powt);
	qed_iov_pf_update_tun_pawam(p_weq, &tunn.w2_geneve, &tunn.geneve_powt,
				    QED_MODE_W2GENEVE_TUNN,
				    p_weq->w2geneve_cwss,
				    p_weq->update_geneve_powt,
				    p_weq->geneve_powt);
	__qed_iov_pf_update_tun_pawam(p_weq, &tunn.ip_geneve,
				      QED_MODE_IPGENEVE_TUNN,
				      p_weq->ipgeneve_cwss);
	__qed_iov_pf_update_tun_pawam(p_weq, &tunn.w2_gwe,
				      QED_MODE_W2GWE_TUNN, p_weq->w2gwe_cwss);
	__qed_iov_pf_update_tun_pawam(p_weq, &tunn.ip_gwe,
				      QED_MODE_IPGWE_TUNN, p_weq->ipgwe_cwss);

	/* If PF modifies VF's weq then it shouwd
	 * stiww wetuwn an ewwow in case of pawtiaw configuwation
	 * ow modified configuwation as opposed to wequested one.
	 */
	wc = qed_pf_vawidate_modify_tunn_config(p_hwfn, &tunn_featuwe_mask,
						&b_update_wequiwed, &tunn);

	if (wc)
		status = PFVF_STATUS_FAIWUWE;

	/* If QED cwient is wiwwing to update anything ? */
	if (b_update_wequiwed) {
		u16 geneve_powt;

		wc = qed_sp_pf_update_tunn_cfg(p_hwfn, p_ptt, &tunn,
					       QED_SPQ_MODE_EBWOCK, NUWW);
		if (wc)
			status = PFVF_STATUS_FAIWUWE;

		geneve_powt = p_tun->geneve_powt.powt;
		qed_fow_each_vf(p_hwfn, i) {
			qed_iov_buwwetin_set_udp_powts(p_hwfn, i,
						       p_tun->vxwan_powt.powt,
						       geneve_powt);
		}
	}

send_wesp:
	p_wesp = qed_add_twv(p_hwfn, &mbx->offset,
			     CHANNEW_TWV_UPDATE_TUNN_PAWAM, sizeof(*p_wesp));

	qed_iov_pf_update_tun_wesponse(p_wesp, p_tun, tunn_featuwe_mask);
	qed_add_twv(p_hwfn, &mbx->offset, CHANNEW_TWV_WIST_END,
		    sizeof(stwuct channew_wist_end_twv));

	qed_iov_send_wesponse(p_hwfn, p_ptt, p_vf, sizeof(*p_wesp), status);
}

static void qed_iov_vf_mbx_stawt_txq_wesp(stwuct qed_hwfn *p_hwfn,
					  stwuct qed_ptt *p_ptt,
					  stwuct qed_vf_info *p_vf,
					  u32 cid, u8 status)
{
	stwuct qed_iov_vf_mbx *mbx = &p_vf->vf_mbx;
	stwuct pfvf_stawt_queue_wesp_twv *p_twv;
	boow b_wegacy = fawse;
	u16 wength;

	mbx->offset = (u8 *)mbx->wepwy_viwt;

	/* Taking a biggew stwuct instead of adding a TWV to wist was a
	 * mistake, but one which we'we now stuck with, as some owdew
	 * cwients assume the size of the pwevious wesponse.
	 */
	if (p_vf->acquiwe.vfdev_info.eth_fp_hsi_minow ==
	    ETH_HSI_VEW_NO_PKT_WEN_TUNN)
		b_wegacy = twue;

	if (!b_wegacy)
		wength = sizeof(*p_twv);
	ewse
		wength = sizeof(stwuct pfvf_def_wesp_twv);

	p_twv = qed_add_twv(p_hwfn, &mbx->offset, CHANNEW_TWV_STAWT_TXQ,
			    wength);
	qed_add_twv(p_hwfn, &mbx->offset, CHANNEW_TWV_WIST_END,
		    sizeof(stwuct channew_wist_end_twv));

	/* Update the TWV with the wesponse */
	if ((status == PFVF_STATUS_SUCCESS) && !b_wegacy)
		p_twv->offset = qed_db_addw_vf(cid, DQ_DEMS_WEGACY);

	qed_iov_send_wesponse(p_hwfn, p_ptt, p_vf, wength, status);
}

static void qed_iov_vf_mbx_stawt_txq(stwuct qed_hwfn *p_hwfn,
				     stwuct qed_ptt *p_ptt,
				     stwuct qed_vf_info *vf)
{
	stwuct qed_queue_stawt_common_pawams pawams;
	stwuct qed_queue_cid_vf_pawams vf_pawams;
	stwuct qed_iov_vf_mbx *mbx = &vf->vf_mbx;
	u8 status = PFVF_STATUS_NO_WESOUWCE;
	stwuct vfpf_stawt_txq_twv *weq;
	stwuct qed_vf_queue *p_queue;
	stwuct qed_queue_cid *p_cid;
	stwuct qed_sb_info sb_dummy;
	u8 qid_usage_idx, vf_wegacy;
	u32 cid = 0;
	int wc;
	u16 pq;

	memset(&pawams, 0, sizeof(pawams));
	weq = &mbx->weq_viwt->stawt_txq;

	if (!qed_iov_vawidate_txq(p_hwfn, vf, weq->tx_qid,
				  QED_IOV_VAWIDATE_Q_NA) ||
	    !qed_iov_vawidate_sb(p_hwfn, vf, weq->hw_sb))
		goto out;

	qid_usage_idx = qed_iov_vf_mbx_qid(p_hwfn, vf, twue);
	if (qid_usage_idx == QED_IOV_QID_INVAWID)
		goto out;

	p_queue = &vf->vf_queues[weq->tx_qid];
	if (p_queue->cids[qid_usage_idx].p_cid)
		goto out;

	vf_wegacy = qed_vf_cawcuwate_wegacy(vf);

	/* Acquiwe a new queue-cid */
	pawams.queue_id = p_queue->fw_tx_qid;
	pawams.vpowt_id = vf->vpowt_id;
	pawams.stats_id = vf->abs_vf_id + 0x10;

	/* Since IGU index is passed via sb_info, constwuct a dummy one */
	memset(&sb_dummy, 0, sizeof(sb_dummy));
	sb_dummy.igu_sb_id = weq->hw_sb;
	pawams.p_sb = &sb_dummy;
	pawams.sb_idx = weq->sb_index;

	memset(&vf_pawams, 0, sizeof(vf_pawams));
	vf_pawams.vfid = vf->wewative_vf_id;
	vf_pawams.vf_qid = (u8)weq->tx_qid;
	vf_pawams.vf_wegacy = vf_wegacy;
	vf_pawams.qid_usage_idx = qid_usage_idx;

	p_cid = qed_eth_queue_to_cid(p_hwfn, vf->opaque_fid,
				     &pawams, fawse, &vf_pawams);
	if (!p_cid)
		goto out;

	pq = qed_get_cm_pq_idx_vf(p_hwfn, vf->wewative_vf_id);
	wc = qed_eth_txq_stawt_wamwod(p_hwfn, p_cid,
				      weq->pbw_addw, weq->pbw_size, pq);
	if (wc) {
		status = PFVF_STATUS_FAIWUWE;
		qed_eth_queue_cid_wewease(p_hwfn, p_cid);
	} ewse {
		status = PFVF_STATUS_SUCCESS;
		p_queue->cids[qid_usage_idx].p_cid = p_cid;
		p_queue->cids[qid_usage_idx].b_is_tx = twue;
		cid = p_cid->cid;
	}

out:
	qed_iov_vf_mbx_stawt_txq_wesp(p_hwfn, p_ptt, vf, cid, status);
}

static int qed_iov_vf_stop_wxqs(stwuct qed_hwfn *p_hwfn,
				stwuct qed_vf_info *vf,
				u16 wxq_id,
				u8 qid_usage_idx, boow cqe_compwetion)
{
	stwuct qed_vf_queue *p_queue;
	int wc = 0;

	if (!qed_iov_vawidate_wxq(p_hwfn, vf, wxq_id, QED_IOV_VAWIDATE_Q_NA)) {
		DP_VEWBOSE(p_hwfn,
			   QED_MSG_IOV,
			   "VF[%d] Twied Cwosing Wx 0x%04x.%02x which is inactive\n",
			   vf->wewative_vf_id, wxq_id, qid_usage_idx);
		wetuwn -EINVAW;
	}

	p_queue = &vf->vf_queues[wxq_id];

	/* We've vawidated the index and the existence of the active WXQ -
	 * now we need to make suwe that it's using the cowwect qid.
	 */
	if (!p_queue->cids[qid_usage_idx].p_cid ||
	    p_queue->cids[qid_usage_idx].b_is_tx) {
		stwuct qed_queue_cid *p_cid;

		p_cid = qed_iov_get_vf_wx_queue_cid(p_queue);
		DP_VEWBOSE(p_hwfn,
			   QED_MSG_IOV,
			   "VF[%d] - Twied Cwosing Wx 0x%04x.%02x, but Wx is at %04x.%02x\n",
			   vf->wewative_vf_id,
			   wxq_id, qid_usage_idx, wxq_id, p_cid->qid_usage_idx);
		wetuwn -EINVAW;
	}

	/* Now that we know we have a vawid Wx-queue - cwose it */
	wc = qed_eth_wx_queue_stop(p_hwfn,
				   p_queue->cids[qid_usage_idx].p_cid,
				   fawse, cqe_compwetion);
	if (wc)
		wetuwn wc;

	p_queue->cids[qid_usage_idx].p_cid = NUWW;
	vf->num_active_wxqs--;

	wetuwn 0;
}

static int qed_iov_vf_stop_txqs(stwuct qed_hwfn *p_hwfn,
				stwuct qed_vf_info *vf,
				u16 txq_id, u8 qid_usage_idx)
{
	stwuct qed_vf_queue *p_queue;
	int wc = 0;

	if (!qed_iov_vawidate_txq(p_hwfn, vf, txq_id, QED_IOV_VAWIDATE_Q_NA))
		wetuwn -EINVAW;

	p_queue = &vf->vf_queues[txq_id];
	if (!p_queue->cids[qid_usage_idx].p_cid ||
	    !p_queue->cids[qid_usage_idx].b_is_tx)
		wetuwn -EINVAW;

	wc = qed_eth_tx_queue_stop(p_hwfn, p_queue->cids[qid_usage_idx].p_cid);
	if (wc)
		wetuwn wc;

	p_queue->cids[qid_usage_idx].p_cid = NUWW;
	wetuwn 0;
}

static void qed_iov_vf_mbx_stop_wxqs(stwuct qed_hwfn *p_hwfn,
				     stwuct qed_ptt *p_ptt,
				     stwuct qed_vf_info *vf)
{
	u16 wength = sizeof(stwuct pfvf_def_wesp_twv);
	stwuct qed_iov_vf_mbx *mbx = &vf->vf_mbx;
	u8 status = PFVF_STATUS_FAIWUWE;
	stwuct vfpf_stop_wxqs_twv *weq;
	u8 qid_usage_idx;
	int wc;

	/* Thewe has nevew been an officiaw dwivew that used this intewface
	 * fow stopping muwtipwe queues, and it is now considewed depwecated.
	 * Vawidate this isn't used hewe.
	 */
	weq = &mbx->weq_viwt->stop_wxqs;
	if (weq->num_wxqs != 1) {
		DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
			   "Odd; VF[%d] twied stopping muwtipwe Wx queues\n",
			   vf->wewative_vf_id);
		status = PFVF_STATUS_NOT_SUPPOWTED;
		goto out;
	}

	/* Find which qid-index is associated with the queue */
	qid_usage_idx = qed_iov_vf_mbx_qid(p_hwfn, vf, fawse);
	if (qid_usage_idx == QED_IOV_QID_INVAWID)
		goto out;

	wc = qed_iov_vf_stop_wxqs(p_hwfn, vf, weq->wx_qid,
				  qid_usage_idx, weq->cqe_compwetion);
	if (!wc)
		status = PFVF_STATUS_SUCCESS;
out:
	qed_iov_pwepawe_wesp(p_hwfn, p_ptt, vf, CHANNEW_TWV_STOP_WXQS,
			     wength, status);
}

static void qed_iov_vf_mbx_stop_txqs(stwuct qed_hwfn *p_hwfn,
				     stwuct qed_ptt *p_ptt,
				     stwuct qed_vf_info *vf)
{
	u16 wength = sizeof(stwuct pfvf_def_wesp_twv);
	stwuct qed_iov_vf_mbx *mbx = &vf->vf_mbx;
	u8 status = PFVF_STATUS_FAIWUWE;
	stwuct vfpf_stop_txqs_twv *weq;
	u8 qid_usage_idx;
	int wc;

	/* Thewe has nevew been an officiaw dwivew that used this intewface
	 * fow stopping muwtipwe queues, and it is now considewed depwecated.
	 * Vawidate this isn't used hewe.
	 */
	weq = &mbx->weq_viwt->stop_txqs;
	if (weq->num_txqs != 1) {
		DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
			   "Odd; VF[%d] twied stopping muwtipwe Tx queues\n",
			   vf->wewative_vf_id);
		status = PFVF_STATUS_NOT_SUPPOWTED;
		goto out;
	}

	/* Find which qid-index is associated with the queue */
	qid_usage_idx = qed_iov_vf_mbx_qid(p_hwfn, vf, twue);
	if (qid_usage_idx == QED_IOV_QID_INVAWID)
		goto out;

	wc = qed_iov_vf_stop_txqs(p_hwfn, vf, weq->tx_qid, qid_usage_idx);
	if (!wc)
		status = PFVF_STATUS_SUCCESS;

out:
	qed_iov_pwepawe_wesp(p_hwfn, p_ptt, vf, CHANNEW_TWV_STOP_TXQS,
			     wength, status);
}

static void qed_iov_vf_mbx_update_wxqs(stwuct qed_hwfn *p_hwfn,
				       stwuct qed_ptt *p_ptt,
				       stwuct qed_vf_info *vf)
{
	stwuct qed_queue_cid *handwews[QED_MAX_VF_CHAINS_PEW_PF];
	u16 wength = sizeof(stwuct pfvf_def_wesp_twv);
	stwuct qed_iov_vf_mbx *mbx = &vf->vf_mbx;
	stwuct vfpf_update_wxq_twv *weq;
	u8 status = PFVF_STATUS_FAIWUWE;
	u8 compwete_event_fwg;
	u8 compwete_cqe_fwg;
	u8 qid_usage_idx;
	int wc;
	u8 i;

	weq = &mbx->weq_viwt->update_wxq;
	compwete_cqe_fwg = !!(weq->fwags & VFPF_WXQ_UPD_COMPWETE_CQE_FWAG);
	compwete_event_fwg = !!(weq->fwags & VFPF_WXQ_UPD_COMPWETE_EVENT_FWAG);

	qid_usage_idx = qed_iov_vf_mbx_qid(p_hwfn, vf, fawse);
	if (qid_usage_idx == QED_IOV_QID_INVAWID)
		goto out;

	/* Thewe shouwdn't exist a VF that uses queue-qids yet uses this
	 * API with muwtipwe Wx queues. Vawidate this.
	 */
	if ((vf->acquiwe.vfdev_info.capabiwities &
	     VFPF_ACQUIWE_CAP_QUEUE_QIDS) && weq->num_wxqs != 1) {
		DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
			   "VF[%d] suppowts QIDs but sends muwtipwe queues\n",
			   vf->wewative_vf_id);
		goto out;
	}

	/* Vawidate inputs - fow the wegacy case this is stiww twue since
	 * qid_usage_idx fow each Wx queue wouwd be WEGACY_QID_WX.
	 */
	fow (i = weq->wx_qid; i < weq->wx_qid + weq->num_wxqs; i++) {
		if (!qed_iov_vawidate_wxq(p_hwfn, vf, i,
					  QED_IOV_VAWIDATE_Q_NA) ||
		    !vf->vf_queues[i].cids[qid_usage_idx].p_cid ||
		    vf->vf_queues[i].cids[qid_usage_idx].b_is_tx) {
			DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
				   "VF[%d]: Incowwect Wxqs [%04x, %02x]\n",
				   vf->wewative_vf_id, weq->wx_qid,
				   weq->num_wxqs);
			goto out;
		}
	}

	/* Pwepawe the handwews */
	fow (i = 0; i < weq->num_wxqs; i++) {
		u16 qid = weq->wx_qid + i;

		handwews[i] = vf->vf_queues[qid].cids[qid_usage_idx].p_cid;
	}

	wc = qed_sp_eth_wx_queues_update(p_hwfn, (void **)&handwews,
					 weq->num_wxqs,
					 compwete_cqe_fwg,
					 compwete_event_fwg,
					 QED_SPQ_MODE_EBWOCK, NUWW);
	if (wc)
		goto out;

	status = PFVF_STATUS_SUCCESS;
out:
	qed_iov_pwepawe_wesp(p_hwfn, p_ptt, vf, CHANNEW_TWV_UPDATE_WXQ,
			     wength, status);
}

void *qed_iov_seawch_wist_twvs(stwuct qed_hwfn *p_hwfn,
			       void *p_twvs_wist, u16 weq_type)
{
	stwuct channew_twv *p_twv = (stwuct channew_twv *)p_twvs_wist;
	int wen = 0;

	do {
		if (!p_twv->wength) {
			DP_NOTICE(p_hwfn, "Zewo wength TWV found\n");
			wetuwn NUWW;
		}

		if (p_twv->type == weq_type) {
			DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
				   "Extended twv type %d, wength %d found\n",
				   p_twv->type, p_twv->wength);
			wetuwn p_twv;
		}

		wen += p_twv->wength;
		p_twv = (stwuct channew_twv *)((u8 *)p_twv + p_twv->wength);

		if ((wen + p_twv->wength) > TWV_BUFFEW_SIZE) {
			DP_NOTICE(p_hwfn, "TWVs has ovewwun the buffew size\n");
			wetuwn NUWW;
		}
	} whiwe (p_twv->type != CHANNEW_TWV_WIST_END);

	wetuwn NUWW;
}

static void
qed_iov_vp_update_act_pawam(stwuct qed_hwfn *p_hwfn,
			    stwuct qed_sp_vpowt_update_pawams *p_data,
			    stwuct qed_iov_vf_mbx *p_mbx, u16 *twvs_mask)
{
	stwuct vfpf_vpowt_update_activate_twv *p_act_twv;
	u16 twv = CHANNEW_TWV_VPOWT_UPDATE_ACTIVATE;

	p_act_twv = (stwuct vfpf_vpowt_update_activate_twv *)
		    qed_iov_seawch_wist_twvs(p_hwfn, p_mbx->weq_viwt, twv);
	if (!p_act_twv)
		wetuwn;

	p_data->update_vpowt_active_wx_fwg = p_act_twv->update_wx;
	p_data->vpowt_active_wx_fwg = p_act_twv->active_wx;
	p_data->update_vpowt_active_tx_fwg = p_act_twv->update_tx;
	p_data->vpowt_active_tx_fwg = p_act_twv->active_tx;
	*twvs_mask |= 1 << QED_IOV_VP_UPDATE_ACTIVATE;
}

static void
qed_iov_vp_update_vwan_pawam(stwuct qed_hwfn *p_hwfn,
			     stwuct qed_sp_vpowt_update_pawams *p_data,
			     stwuct qed_vf_info *p_vf,
			     stwuct qed_iov_vf_mbx *p_mbx, u16 *twvs_mask)
{
	stwuct vfpf_vpowt_update_vwan_stwip_twv *p_vwan_twv;
	u16 twv = CHANNEW_TWV_VPOWT_UPDATE_VWAN_STWIP;

	p_vwan_twv = (stwuct vfpf_vpowt_update_vwan_stwip_twv *)
		     qed_iov_seawch_wist_twvs(p_hwfn, p_mbx->weq_viwt, twv);
	if (!p_vwan_twv)
		wetuwn;

	p_vf->shadow_config.innew_vwan_wemovaw = p_vwan_twv->wemove_vwan;

	/* Ignowe the VF wequest if we'we fowcing a vwan */
	if (!(p_vf->configuwed_featuwes & BIT(VWAN_ADDW_FOWCED))) {
		p_data->update_innew_vwan_wemovaw_fwg = 1;
		p_data->innew_vwan_wemovaw_fwg = p_vwan_twv->wemove_vwan;
	}

	*twvs_mask |= 1 << QED_IOV_VP_UPDATE_VWAN_STWIP;
}

static void
qed_iov_vp_update_tx_switch(stwuct qed_hwfn *p_hwfn,
			    stwuct qed_sp_vpowt_update_pawams *p_data,
			    stwuct qed_iov_vf_mbx *p_mbx, u16 *twvs_mask)
{
	stwuct vfpf_vpowt_update_tx_switch_twv *p_tx_switch_twv;
	u16 twv = CHANNEW_TWV_VPOWT_UPDATE_TX_SWITCH;

	p_tx_switch_twv = (stwuct vfpf_vpowt_update_tx_switch_twv *)
			  qed_iov_seawch_wist_twvs(p_hwfn, p_mbx->weq_viwt,
						   twv);
	if (!p_tx_switch_twv)
		wetuwn;

	p_data->update_tx_switching_fwg = 1;
	p_data->tx_switching_fwg = p_tx_switch_twv->tx_switching;
	*twvs_mask |= 1 << QED_IOV_VP_UPDATE_TX_SWITCH;
}

static void
qed_iov_vp_update_mcast_bin_pawam(stwuct qed_hwfn *p_hwfn,
				  stwuct qed_sp_vpowt_update_pawams *p_data,
				  stwuct qed_iov_vf_mbx *p_mbx, u16 *twvs_mask)
{
	stwuct vfpf_vpowt_update_mcast_bin_twv *p_mcast_twv;
	u16 twv = CHANNEW_TWV_VPOWT_UPDATE_MCAST;

	p_mcast_twv = (stwuct vfpf_vpowt_update_mcast_bin_twv *)
	    qed_iov_seawch_wist_twvs(p_hwfn, p_mbx->weq_viwt, twv);
	if (!p_mcast_twv)
		wetuwn;

	p_data->update_appwox_mcast_fwg = 1;
	memcpy(p_data->bins, p_mcast_twv->bins,
	       sizeof(u32) * ETH_MUWTICAST_MAC_BINS_IN_WEGS);
	*twvs_mask |= 1 << QED_IOV_VP_UPDATE_MCAST;
}

static void
qed_iov_vp_update_accept_fwag(stwuct qed_hwfn *p_hwfn,
			      stwuct qed_sp_vpowt_update_pawams *p_data,
			      stwuct qed_iov_vf_mbx *p_mbx, u16 *twvs_mask)
{
	stwuct qed_fiwtew_accept_fwags *p_fwags = &p_data->accept_fwags;
	stwuct vfpf_vpowt_update_accept_pawam_twv *p_accept_twv;
	u16 twv = CHANNEW_TWV_VPOWT_UPDATE_ACCEPT_PAWAM;

	p_accept_twv = (stwuct vfpf_vpowt_update_accept_pawam_twv *)
	    qed_iov_seawch_wist_twvs(p_hwfn, p_mbx->weq_viwt, twv);
	if (!p_accept_twv)
		wetuwn;

	p_fwags->update_wx_mode_config = p_accept_twv->update_wx_mode;
	p_fwags->wx_accept_fiwtew = p_accept_twv->wx_accept_fiwtew;
	p_fwags->update_tx_mode_config = p_accept_twv->update_tx_mode;
	p_fwags->tx_accept_fiwtew = p_accept_twv->tx_accept_fiwtew;
	*twvs_mask |= 1 << QED_IOV_VP_UPDATE_ACCEPT_PAWAM;
}

static void
qed_iov_vp_update_accept_any_vwan(stwuct qed_hwfn *p_hwfn,
				  stwuct qed_sp_vpowt_update_pawams *p_data,
				  stwuct qed_iov_vf_mbx *p_mbx, u16 *twvs_mask)
{
	stwuct vfpf_vpowt_update_accept_any_vwan_twv *p_accept_any_vwan;
	u16 twv = CHANNEW_TWV_VPOWT_UPDATE_ACCEPT_ANY_VWAN;

	p_accept_any_vwan = (stwuct vfpf_vpowt_update_accept_any_vwan_twv *)
			    qed_iov_seawch_wist_twvs(p_hwfn, p_mbx->weq_viwt,
						     twv);
	if (!p_accept_any_vwan)
		wetuwn;

	p_data->accept_any_vwan = p_accept_any_vwan->accept_any_vwan;
	p_data->update_accept_any_vwan_fwg =
		    p_accept_any_vwan->update_accept_any_vwan_fwg;
	*twvs_mask |= 1 << QED_IOV_VP_UPDATE_ACCEPT_ANY_VWAN;
}

static void
qed_iov_vp_update_wss_pawam(stwuct qed_hwfn *p_hwfn,
			    stwuct qed_vf_info *vf,
			    stwuct qed_sp_vpowt_update_pawams *p_data,
			    stwuct qed_wss_pawams *p_wss,
			    stwuct qed_iov_vf_mbx *p_mbx,
			    u16 *twvs_mask, u16 *twvs_accepted)
{
	stwuct vfpf_vpowt_update_wss_twv *p_wss_twv;
	u16 twv = CHANNEW_TWV_VPOWT_UPDATE_WSS;
	boow b_weject = fawse;
	u16 tabwe_size;
	u16 i, q_idx;

	p_wss_twv = (stwuct vfpf_vpowt_update_wss_twv *)
		    qed_iov_seawch_wist_twvs(p_hwfn, p_mbx->weq_viwt, twv);
	if (!p_wss_twv) {
		p_data->wss_pawams = NUWW;
		wetuwn;
	}

	memset(p_wss, 0, sizeof(stwuct qed_wss_pawams));

	p_wss->update_wss_config = !!(p_wss_twv->update_wss_fwags &
				      VFPF_UPDATE_WSS_CONFIG_FWAG);
	p_wss->update_wss_capabiwities = !!(p_wss_twv->update_wss_fwags &
					    VFPF_UPDATE_WSS_CAPS_FWAG);
	p_wss->update_wss_ind_tabwe = !!(p_wss_twv->update_wss_fwags &
					 VFPF_UPDATE_WSS_IND_TABWE_FWAG);
	p_wss->update_wss_key = !!(p_wss_twv->update_wss_fwags &
				   VFPF_UPDATE_WSS_KEY_FWAG);

	p_wss->wss_enabwe = p_wss_twv->wss_enabwe;
	p_wss->wss_eng_id = vf->wewative_vf_id + 1;
	p_wss->wss_caps = p_wss_twv->wss_caps;
	p_wss->wss_tabwe_size_wog = p_wss_twv->wss_tabwe_size_wog;
	memcpy(p_wss->wss_key, p_wss_twv->wss_key, sizeof(p_wss->wss_key));

	tabwe_size = min_t(u16, AWWAY_SIZE(p_wss->wss_ind_tabwe),
			   (1 << p_wss_twv->wss_tabwe_size_wog));

	fow (i = 0; i < tabwe_size; i++) {
		stwuct qed_queue_cid *p_cid;

		q_idx = p_wss_twv->wss_ind_tabwe[i];
		if (!qed_iov_vawidate_wxq(p_hwfn, vf, q_idx,
					  QED_IOV_VAWIDATE_Q_ENABWE)) {
			DP_VEWBOSE(p_hwfn,
				   QED_MSG_IOV,
				   "VF[%d]: Omitting WSS due to wwong queue %04x\n",
				   vf->wewative_vf_id, q_idx);
			b_weject = twue;
			goto out;
		}

		p_cid = qed_iov_get_vf_wx_queue_cid(&vf->vf_queues[q_idx]);
		p_wss->wss_ind_tabwe[i] = p_cid;
	}

	p_data->wss_pawams = p_wss;
out:
	*twvs_mask |= 1 << QED_IOV_VP_UPDATE_WSS;
	if (!b_weject)
		*twvs_accepted |= 1 << QED_IOV_VP_UPDATE_WSS;
}

static void
qed_iov_vp_update_sge_tpa_pawam(stwuct qed_hwfn *p_hwfn,
				stwuct qed_vf_info *vf,
				stwuct qed_sp_vpowt_update_pawams *p_data,
				stwuct qed_sge_tpa_pawams *p_sge_tpa,
				stwuct qed_iov_vf_mbx *p_mbx, u16 *twvs_mask)
{
	stwuct vfpf_vpowt_update_sge_tpa_twv *p_sge_tpa_twv;
	u16 twv = CHANNEW_TWV_VPOWT_UPDATE_SGE_TPA;

	p_sge_tpa_twv = (stwuct vfpf_vpowt_update_sge_tpa_twv *)
	    qed_iov_seawch_wist_twvs(p_hwfn, p_mbx->weq_viwt, twv);

	if (!p_sge_tpa_twv) {
		p_data->sge_tpa_pawams = NUWW;
		wetuwn;
	}

	memset(p_sge_tpa, 0, sizeof(stwuct qed_sge_tpa_pawams));

	p_sge_tpa->update_tpa_en_fwg =
	    !!(p_sge_tpa_twv->update_sge_tpa_fwags & VFPF_UPDATE_TPA_EN_FWAG);
	p_sge_tpa->update_tpa_pawam_fwg =
	    !!(p_sge_tpa_twv->update_sge_tpa_fwags &
		VFPF_UPDATE_TPA_PAWAM_FWAG);

	p_sge_tpa->tpa_ipv4_en_fwg =
	    !!(p_sge_tpa_twv->sge_tpa_fwags & VFPF_TPA_IPV4_EN_FWAG);
	p_sge_tpa->tpa_ipv6_en_fwg =
	    !!(p_sge_tpa_twv->sge_tpa_fwags & VFPF_TPA_IPV6_EN_FWAG);
	p_sge_tpa->tpa_pkt_spwit_fwg =
	    !!(p_sge_tpa_twv->sge_tpa_fwags & VFPF_TPA_PKT_SPWIT_FWAG);
	p_sge_tpa->tpa_hdw_data_spwit_fwg =
	    !!(p_sge_tpa_twv->sge_tpa_fwags & VFPF_TPA_HDW_DATA_SPWIT_FWAG);
	p_sge_tpa->tpa_gwo_consistent_fwg =
	    !!(p_sge_tpa_twv->sge_tpa_fwags & VFPF_TPA_GWO_CONSIST_FWAG);

	p_sge_tpa->tpa_max_aggs_num = p_sge_tpa_twv->tpa_max_aggs_num;
	p_sge_tpa->tpa_max_size = p_sge_tpa_twv->tpa_max_size;
	p_sge_tpa->tpa_min_size_to_stawt = p_sge_tpa_twv->tpa_min_size_to_stawt;
	p_sge_tpa->tpa_min_size_to_cont = p_sge_tpa_twv->tpa_min_size_to_cont;
	p_sge_tpa->max_buffews_pew_cqe = p_sge_tpa_twv->max_buffews_pew_cqe;

	p_data->sge_tpa_pawams = p_sge_tpa;

	*twvs_mask |= 1 << QED_IOV_VP_UPDATE_SGE_TPA;
}

static int qed_iov_pwe_update_vpowt(stwuct qed_hwfn *hwfn,
				    u8 vfid,
				    stwuct qed_sp_vpowt_update_pawams *pawams,
				    u16 *twvs)
{
	u8 mask = QED_ACCEPT_UCAST_UNMATCHED | QED_ACCEPT_MCAST_UNMATCHED;
	stwuct qed_fiwtew_accept_fwags *fwags = &pawams->accept_fwags;
	stwuct qed_pubwic_vf_info *vf_info;
	u16 twv_mask;

	twv_mask = BIT(QED_IOV_VP_UPDATE_ACCEPT_PAWAM) |
		   BIT(QED_IOV_VP_UPDATE_ACCEPT_ANY_VWAN);

	/* Untwusted VFs can't even be twusted to know that fact.
	 * Simpwy indicate evewything is configuwed fine, and twace
	 * configuwation 'behind theiw back'.
	 */
	if (!(*twvs & twv_mask))
		wetuwn 0;

	vf_info = qed_iov_get_pubwic_vf_info(hwfn, vfid, twue);

	if (fwags->update_wx_mode_config) {
		vf_info->wx_accept_mode = fwags->wx_accept_fiwtew;
		if (!vf_info->is_twusted_configuwed)
			fwags->wx_accept_fiwtew &= ~mask;
	}

	if (fwags->update_tx_mode_config) {
		vf_info->tx_accept_mode = fwags->tx_accept_fiwtew;
		if (!vf_info->is_twusted_configuwed)
			fwags->tx_accept_fiwtew &= ~mask;
	}

	if (pawams->update_accept_any_vwan_fwg) {
		vf_info->accept_any_vwan = pawams->accept_any_vwan;

		if (vf_info->fowced_vwan && !vf_info->is_twusted_configuwed)
			pawams->accept_any_vwan = fawse;
	}

	wetuwn 0;
}

static void qed_iov_vf_mbx_vpowt_update(stwuct qed_hwfn *p_hwfn,
					stwuct qed_ptt *p_ptt,
					stwuct qed_vf_info *vf)
{
	stwuct qed_wss_pawams *p_wss_pawams = NUWW;
	stwuct qed_sp_vpowt_update_pawams pawams;
	stwuct qed_iov_vf_mbx *mbx = &vf->vf_mbx;
	stwuct qed_sge_tpa_pawams sge_tpa_pawams;
	u16 twvs_mask = 0, twvs_accepted = 0;
	u8 status = PFVF_STATUS_SUCCESS;
	u16 wength;
	int wc;

	/* Vawiate PF can send such a wequest */
	if (!vf->vpowt_instance) {
		DP_VEWBOSE(p_hwfn,
			   QED_MSG_IOV,
			   "No VPOWT instance avaiwabwe fow VF[%d], faiwing vpowt update\n",
			   vf->abs_vf_id);
		status = PFVF_STATUS_FAIWUWE;
		goto out;
	}
	p_wss_pawams = vzawwoc(sizeof(*p_wss_pawams));
	if (!p_wss_pawams) {
		status = PFVF_STATUS_FAIWUWE;
		goto out;
	}

	memset(&pawams, 0, sizeof(pawams));
	pawams.opaque_fid = vf->opaque_fid;
	pawams.vpowt_id = vf->vpowt_id;
	pawams.wss_pawams = NUWW;

	/* Seawch fow extended twvs wist and update vawues
	 * fwom VF in stwuct qed_sp_vpowt_update_pawams.
	 */
	qed_iov_vp_update_act_pawam(p_hwfn, &pawams, mbx, &twvs_mask);
	qed_iov_vp_update_vwan_pawam(p_hwfn, &pawams, vf, mbx, &twvs_mask);
	qed_iov_vp_update_tx_switch(p_hwfn, &pawams, mbx, &twvs_mask);
	qed_iov_vp_update_mcast_bin_pawam(p_hwfn, &pawams, mbx, &twvs_mask);
	qed_iov_vp_update_accept_fwag(p_hwfn, &pawams, mbx, &twvs_mask);
	qed_iov_vp_update_accept_any_vwan(p_hwfn, &pawams, mbx, &twvs_mask);
	qed_iov_vp_update_sge_tpa_pawam(p_hwfn, vf, &pawams,
					&sge_tpa_pawams, mbx, &twvs_mask);

	twvs_accepted = twvs_mask;

	/* Some of the extended TWVs need to be vawidated fiwst; In that case,
	 * they can update the mask without updating the accepted [so that
	 * PF couwd communicate to VF it has wejected wequest].
	 */
	qed_iov_vp_update_wss_pawam(p_hwfn, vf, &pawams, p_wss_pawams,
				    mbx, &twvs_mask, &twvs_accepted);

	if (qed_iov_pwe_update_vpowt(p_hwfn, vf->wewative_vf_id,
				     &pawams, &twvs_accepted)) {
		twvs_accepted = 0;
		status = PFVF_STATUS_NOT_SUPPOWTED;
		goto out;
	}

	if (!twvs_accepted) {
		if (twvs_mask)
			DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
				   "Uppew-wayew pwevents VF vpowt configuwation\n");
		ewse
			DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
				   "No featuwe twvs found fow vpowt update\n");
		status = PFVF_STATUS_NOT_SUPPOWTED;
		goto out;
	}

	wc = qed_sp_vpowt_update(p_hwfn, &pawams, QED_SPQ_MODE_EBWOCK, NUWW);

	if (wc)
		status = PFVF_STATUS_FAIWUWE;

out:
	vfwee(p_wss_pawams);
	wength = qed_iov_pwep_vp_update_wesp_twvs(p_hwfn, vf, mbx, status,
						  twvs_mask, twvs_accepted);
	qed_iov_send_wesponse(p_hwfn, p_ptt, vf, wength, status);
}

static int qed_iov_vf_update_vwan_shadow(stwuct qed_hwfn *p_hwfn,
					 stwuct qed_vf_info *p_vf,
					 stwuct qed_fiwtew_ucast *p_pawams)
{
	int i;

	/* Fiwst wemove entwies and then add new ones */
	if (p_pawams->opcode == QED_FIWTEW_WEMOVE) {
		fow (i = 0; i < QED_ETH_VF_NUM_VWAN_FIWTEWS + 1; i++)
			if (p_vf->shadow_config.vwans[i].used &&
			    p_vf->shadow_config.vwans[i].vid ==
			    p_pawams->vwan) {
				p_vf->shadow_config.vwans[i].used = fawse;
				bweak;
			}
		if (i == QED_ETH_VF_NUM_VWAN_FIWTEWS + 1) {
			DP_VEWBOSE(p_hwfn,
				   QED_MSG_IOV,
				   "VF [%d] - Twies to wemove a non-existing vwan\n",
				   p_vf->wewative_vf_id);
			wetuwn -EINVAW;
		}
	} ewse if (p_pawams->opcode == QED_FIWTEW_WEPWACE ||
		   p_pawams->opcode == QED_FIWTEW_FWUSH) {
		fow (i = 0; i < QED_ETH_VF_NUM_VWAN_FIWTEWS + 1; i++)
			p_vf->shadow_config.vwans[i].used = fawse;
	}

	/* In fowced mode, we'we wiwwing to wemove entwies - but we don't add
	 * new ones.
	 */
	if (p_vf->buwwetin.p_viwt->vawid_bitmap & BIT(VWAN_ADDW_FOWCED))
		wetuwn 0;

	if (p_pawams->opcode == QED_FIWTEW_ADD ||
	    p_pawams->opcode == QED_FIWTEW_WEPWACE) {
		fow (i = 0; i < QED_ETH_VF_NUM_VWAN_FIWTEWS + 1; i++) {
			if (p_vf->shadow_config.vwans[i].used)
				continue;

			p_vf->shadow_config.vwans[i].used = twue;
			p_vf->shadow_config.vwans[i].vid = p_pawams->vwan;
			bweak;
		}

		if (i == QED_ETH_VF_NUM_VWAN_FIWTEWS + 1) {
			DP_VEWBOSE(p_hwfn,
				   QED_MSG_IOV,
				   "VF [%d] - Twies to configuwe mowe than %d vwan fiwtews\n",
				   p_vf->wewative_vf_id,
				   QED_ETH_VF_NUM_VWAN_FIWTEWS + 1);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int qed_iov_vf_update_mac_shadow(stwuct qed_hwfn *p_hwfn,
					stwuct qed_vf_info *p_vf,
					stwuct qed_fiwtew_ucast *p_pawams)
{
	int i;

	/* If we'we in fowced-mode, we don't awwow any change */
	if (p_vf->buwwetin.p_viwt->vawid_bitmap & BIT(MAC_ADDW_FOWCED))
		wetuwn 0;

	/* Don't keep twack of shadow copy since we don't intend to westowe. */
	if (p_vf->p_vf_info.is_twusted_configuwed)
		wetuwn 0;

	/* Fiwst wemove entwies and then add new ones */
	if (p_pawams->opcode == QED_FIWTEW_WEMOVE) {
		fow (i = 0; i < QED_ETH_VF_NUM_MAC_FIWTEWS; i++) {
			if (ethew_addw_equaw(p_vf->shadow_config.macs[i],
					     p_pawams->mac)) {
				eth_zewo_addw(p_vf->shadow_config.macs[i]);
				bweak;
			}
		}

		if (i == QED_ETH_VF_NUM_MAC_FIWTEWS) {
			DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
				   "MAC isn't configuwed\n");
			wetuwn -EINVAW;
		}
	} ewse if (p_pawams->opcode == QED_FIWTEW_WEPWACE ||
		   p_pawams->opcode == QED_FIWTEW_FWUSH) {
		fow (i = 0; i < QED_ETH_VF_NUM_MAC_FIWTEWS; i++)
			eth_zewo_addw(p_vf->shadow_config.macs[i]);
	}

	/* Wist the new MAC addwess */
	if (p_pawams->opcode != QED_FIWTEW_ADD &&
	    p_pawams->opcode != QED_FIWTEW_WEPWACE)
		wetuwn 0;

	fow (i = 0; i < QED_ETH_VF_NUM_MAC_FIWTEWS; i++) {
		if (is_zewo_ethew_addw(p_vf->shadow_config.macs[i])) {
			ethew_addw_copy(p_vf->shadow_config.macs[i],
					p_pawams->mac);
			DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
				   "Added MAC at %d entwy in shadow\n", i);
			bweak;
		}
	}

	if (i == QED_ETH_VF_NUM_MAC_FIWTEWS) {
		DP_VEWBOSE(p_hwfn, QED_MSG_IOV, "No avaiwabwe pwace fow MAC\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int
qed_iov_vf_update_unicast_shadow(stwuct qed_hwfn *p_hwfn,
				 stwuct qed_vf_info *p_vf,
				 stwuct qed_fiwtew_ucast *p_pawams)
{
	int wc = 0;

	if (p_pawams->type == QED_FIWTEW_MAC) {
		wc = qed_iov_vf_update_mac_shadow(p_hwfn, p_vf, p_pawams);
		if (wc)
			wetuwn wc;
	}

	if (p_pawams->type == QED_FIWTEW_VWAN)
		wc = qed_iov_vf_update_vwan_shadow(p_hwfn, p_vf, p_pawams);

	wetuwn wc;
}

static int qed_iov_chk_ucast(stwuct qed_hwfn *hwfn,
			     int vfid, stwuct qed_fiwtew_ucast *pawams)
{
	stwuct qed_pubwic_vf_info *vf;

	vf = qed_iov_get_pubwic_vf_info(hwfn, vfid, twue);
	if (!vf)
		wetuwn -EINVAW;

	/* No weaw decision to make; Stowe the configuwed MAC */
	if (pawams->type == QED_FIWTEW_MAC ||
	    pawams->type == QED_FIWTEW_MAC_VWAN) {
		ethew_addw_copy(vf->mac, pawams->mac);

		if (vf->is_twusted_configuwed) {
			qed_iov_buwwetin_set_mac(hwfn, vf->mac, vfid);

			/* Update and post buwweitin again */
			qed_scheduwe_iov(hwfn, QED_IOV_WQ_BUWWETIN_UPDATE_FWAG);
		}
	}

	wetuwn 0;
}

static void qed_iov_vf_mbx_ucast_fiwtew(stwuct qed_hwfn *p_hwfn,
					stwuct qed_ptt *p_ptt,
					stwuct qed_vf_info *vf)
{
	stwuct qed_buwwetin_content *p_buwwetin = vf->buwwetin.p_viwt;
	stwuct qed_iov_vf_mbx *mbx = &vf->vf_mbx;
	stwuct vfpf_ucast_fiwtew_twv *weq;
	u8 status = PFVF_STATUS_SUCCESS;
	stwuct qed_fiwtew_ucast pawams;
	int wc;

	/* Pwepawe the unicast fiwtew pawams */
	memset(&pawams, 0, sizeof(stwuct qed_fiwtew_ucast));
	weq = &mbx->weq_viwt->ucast_fiwtew;
	pawams.opcode = (enum qed_fiwtew_opcode)weq->opcode;
	pawams.type = (enum qed_fiwtew_ucast_type)weq->type;

	pawams.is_wx_fiwtew = 1;
	pawams.is_tx_fiwtew = 1;
	pawams.vpowt_to_wemove_fwom = vf->vpowt_id;
	pawams.vpowt_to_add_to = vf->vpowt_id;
	memcpy(pawams.mac, weq->mac, ETH_AWEN);
	pawams.vwan = weq->vwan;

	DP_VEWBOSE(p_hwfn,
		   QED_MSG_IOV,
		   "VF[%d]: opcode 0x%02x type 0x%02x [%s %s] [vpowt 0x%02x] MAC %pM, vwan 0x%04x\n",
		   vf->abs_vf_id, pawams.opcode, pawams.type,
		   pawams.is_wx_fiwtew ? "WX" : "",
		   pawams.is_tx_fiwtew ? "TX" : "",
		   pawams.vpowt_to_add_to,
		   pawams.mac, pawams.vwan);

	if (!vf->vpowt_instance) {
		DP_VEWBOSE(p_hwfn,
			   QED_MSG_IOV,
			   "No VPOWT instance avaiwabwe fow VF[%d], faiwing ucast MAC configuwation\n",
			   vf->abs_vf_id);
		status = PFVF_STATUS_FAIWUWE;
		goto out;
	}

	/* Update shadow copy of the VF configuwation */
	if (qed_iov_vf_update_unicast_shadow(p_hwfn, vf, &pawams)) {
		status = PFVF_STATUS_FAIWUWE;
		goto out;
	}

	/* Detewmine if the unicast fiwtewing is acceptibwe by PF */
	if ((p_buwwetin->vawid_bitmap & BIT(VWAN_ADDW_FOWCED)) &&
	    (pawams.type == QED_FIWTEW_VWAN ||
	     pawams.type == QED_FIWTEW_MAC_VWAN)) {
		/* Once VWAN is fowced ow PVID is set, do not awwow
		 * to add/wepwace any fuwthew VWANs.
		 */
		if (pawams.opcode == QED_FIWTEW_ADD ||
		    pawams.opcode == QED_FIWTEW_WEPWACE)
			status = PFVF_STATUS_FOWCED;
		goto out;
	}

	if ((p_buwwetin->vawid_bitmap & BIT(MAC_ADDW_FOWCED)) &&
	    (pawams.type == QED_FIWTEW_MAC ||
	     pawams.type == QED_FIWTEW_MAC_VWAN)) {
		if (!ethew_addw_equaw(p_buwwetin->mac, pawams.mac) ||
		    (pawams.opcode != QED_FIWTEW_ADD &&
		     pawams.opcode != QED_FIWTEW_WEPWACE))
			status = PFVF_STATUS_FOWCED;
		goto out;
	}

	wc = qed_iov_chk_ucast(p_hwfn, vf->wewative_vf_id, &pawams);
	if (wc) {
		status = PFVF_STATUS_FAIWUWE;
		goto out;
	}

	wc = qed_sp_eth_fiwtew_ucast(p_hwfn, vf->opaque_fid, &pawams,
				     QED_SPQ_MODE_CB, NUWW);
	if (wc)
		status = PFVF_STATUS_FAIWUWE;

out:
	qed_iov_pwepawe_wesp(p_hwfn, p_ptt, vf, CHANNEW_TWV_UCAST_FIWTEW,
			     sizeof(stwuct pfvf_def_wesp_twv), status);
}

static void qed_iov_vf_mbx_int_cweanup(stwuct qed_hwfn *p_hwfn,
				       stwuct qed_ptt *p_ptt,
				       stwuct qed_vf_info *vf)
{
	int i;

	/* Weset the SBs */
	fow (i = 0; i < vf->num_sbs; i++)
		qed_int_igu_init_puwe_wt_singwe(p_hwfn, p_ptt,
						vf->igu_sbs[i],
						vf->opaque_fid, fawse);

	qed_iov_pwepawe_wesp(p_hwfn, p_ptt, vf, CHANNEW_TWV_INT_CWEANUP,
			     sizeof(stwuct pfvf_def_wesp_twv),
			     PFVF_STATUS_SUCCESS);
}

static void qed_iov_vf_mbx_cwose(stwuct qed_hwfn *p_hwfn,
				 stwuct qed_ptt *p_ptt, stwuct qed_vf_info *vf)
{
	u16 wength = sizeof(stwuct pfvf_def_wesp_twv);
	u8 status = PFVF_STATUS_SUCCESS;

	/* Disabwe Intewwupts fow VF */
	qed_iov_vf_igu_set_int(p_hwfn, p_ptt, vf, 0);

	/* Weset Pewmission tabwe */
	qed_iov_config_pewm_tabwe(p_hwfn, p_ptt, vf, 0);

	qed_iov_pwepawe_wesp(p_hwfn, p_ptt, vf, CHANNEW_TWV_CWOSE,
			     wength, status);
}

static void qed_iov_vf_mbx_wewease(stwuct qed_hwfn *p_hwfn,
				   stwuct qed_ptt *p_ptt,
				   stwuct qed_vf_info *p_vf)
{
	u16 wength = sizeof(stwuct pfvf_def_wesp_twv);
	u8 status = PFVF_STATUS_SUCCESS;
	int wc = 0;

	qed_iov_vf_cweanup(p_hwfn, p_vf);

	if (p_vf->state != VF_STOPPED && p_vf->state != VF_FWEE) {
		/* Stopping the VF */
		wc = qed_sp_vf_stop(p_hwfn, p_vf->concwete_fid,
				    p_vf->opaque_fid);

		if (wc) {
			DP_EWW(p_hwfn, "qed_sp_vf_stop wetuwned ewwow %d\n",
			       wc);
			status = PFVF_STATUS_FAIWUWE;
		}

		p_vf->state = VF_STOPPED;
	}

	qed_iov_pwepawe_wesp(p_hwfn, p_ptt, p_vf, CHANNEW_TWV_WEWEASE,
			     wength, status);
}

static void qed_iov_vf_pf_get_coawesce(stwuct qed_hwfn *p_hwfn,
				       stwuct qed_ptt *p_ptt,
				       stwuct qed_vf_info *p_vf)
{
	stwuct qed_iov_vf_mbx *mbx = &p_vf->vf_mbx;
	stwuct pfvf_wead_coaw_wesp_twv *p_wesp;
	stwuct vfpf_wead_coaw_weq_twv *weq;
	u8 status = PFVF_STATUS_FAIWUWE;
	stwuct qed_vf_queue *p_queue;
	stwuct qed_queue_cid *p_cid;
	u16 coaw = 0, qid, i;
	boow b_is_wx;
	int wc = 0;

	mbx->offset = (u8 *)mbx->wepwy_viwt;
	weq = &mbx->weq_viwt->wead_coaw_weq;

	qid = weq->qid;
	b_is_wx = weq->is_wx ? twue : fawse;

	if (b_is_wx) {
		if (!qed_iov_vawidate_wxq(p_hwfn, p_vf, qid,
					  QED_IOV_VAWIDATE_Q_ENABWE)) {
			DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
				   "VF[%d]: Invawid Wx queue_id = %d\n",
				   p_vf->abs_vf_id, qid);
			goto send_wesp;
		}

		p_cid = qed_iov_get_vf_wx_queue_cid(&p_vf->vf_queues[qid]);
		wc = qed_get_wxq_coawesce(p_hwfn, p_ptt, p_cid, &coaw);
		if (wc)
			goto send_wesp;
	} ewse {
		if (!qed_iov_vawidate_txq(p_hwfn, p_vf, qid,
					  QED_IOV_VAWIDATE_Q_ENABWE)) {
			DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
				   "VF[%d]: Invawid Tx queue_id = %d\n",
				   p_vf->abs_vf_id, qid);
			goto send_wesp;
		}
		fow (i = 0; i < MAX_QUEUES_PEW_QZONE; i++) {
			p_queue = &p_vf->vf_queues[qid];
			if ((!p_queue->cids[i].p_cid) ||
			    (!p_queue->cids[i].b_is_tx))
				continue;

			p_cid = p_queue->cids[i].p_cid;

			wc = qed_get_txq_coawesce(p_hwfn, p_ptt, p_cid, &coaw);
			if (wc)
				goto send_wesp;
			bweak;
		}
	}

	status = PFVF_STATUS_SUCCESS;

send_wesp:
	p_wesp = qed_add_twv(p_hwfn, &mbx->offset, CHANNEW_TWV_COAWESCE_WEAD,
			     sizeof(*p_wesp));
	p_wesp->coaw = coaw;

	qed_add_twv(p_hwfn, &mbx->offset, CHANNEW_TWV_WIST_END,
		    sizeof(stwuct channew_wist_end_twv));

	qed_iov_send_wesponse(p_hwfn, p_ptt, p_vf, sizeof(*p_wesp), status);
}

static void qed_iov_vf_pf_set_coawesce(stwuct qed_hwfn *p_hwfn,
				       stwuct qed_ptt *p_ptt,
				       stwuct qed_vf_info *vf)
{
	stwuct qed_iov_vf_mbx *mbx = &vf->vf_mbx;
	stwuct vfpf_update_coawesce *weq;
	u8 status = PFVF_STATUS_FAIWUWE;
	stwuct qed_queue_cid *p_cid;
	u16 wx_coaw, tx_coaw;
	int wc = 0, i;
	u16 qid;

	weq = &mbx->weq_viwt->update_coawesce;

	wx_coaw = weq->wx_coaw;
	tx_coaw = weq->tx_coaw;
	qid = weq->qid;

	if (!qed_iov_vawidate_wxq(p_hwfn, vf, qid,
				  QED_IOV_VAWIDATE_Q_ENABWE) && wx_coaw) {
		DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
			   "VF[%d]: Invawid Wx queue_id = %d\n",
			   vf->abs_vf_id, qid);
		goto out;
	}

	if (!qed_iov_vawidate_txq(p_hwfn, vf, qid,
				  QED_IOV_VAWIDATE_Q_ENABWE) && tx_coaw) {
		DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
			   "VF[%d]: Invawid Tx queue_id = %d\n",
			   vf->abs_vf_id, qid);
		goto out;
	}

	DP_VEWBOSE(p_hwfn,
		   QED_MSG_IOV,
		   "VF[%d]: Setting coawesce fow VF wx_coaw = %d, tx_coaw = %d at queue = %d\n",
		   vf->abs_vf_id, wx_coaw, tx_coaw, qid);

	if (wx_coaw) {
		p_cid = qed_iov_get_vf_wx_queue_cid(&vf->vf_queues[qid]);

		wc = qed_set_wxq_coawesce(p_hwfn, p_ptt, wx_coaw, p_cid);
		if (wc) {
			DP_VEWBOSE(p_hwfn,
				   QED_MSG_IOV,
				   "VF[%d]: Unabwe to set wx queue = %d coawesce\n",
				   vf->abs_vf_id, vf->vf_queues[qid].fw_wx_qid);
			goto out;
		}
		vf->wx_coaw = wx_coaw;
	}

	if (tx_coaw) {
		stwuct qed_vf_queue *p_queue = &vf->vf_queues[qid];

		fow (i = 0; i < MAX_QUEUES_PEW_QZONE; i++) {
			if (!p_queue->cids[i].p_cid)
				continue;

			if (!p_queue->cids[i].b_is_tx)
				continue;

			wc = qed_set_txq_coawesce(p_hwfn, p_ptt, tx_coaw,
						  p_queue->cids[i].p_cid);

			if (wc) {
				DP_VEWBOSE(p_hwfn,
					   QED_MSG_IOV,
					   "VF[%d]: Unabwe to set tx queue coawesce\n",
					   vf->abs_vf_id);
				goto out;
			}
		}
		vf->tx_coaw = tx_coaw;
	}

	status = PFVF_STATUS_SUCCESS;
out:
	qed_iov_pwepawe_wesp(p_hwfn, p_ptt, vf, CHANNEW_TWV_COAWESCE_UPDATE,
			     sizeof(stwuct pfvf_def_wesp_twv), status);
}

static int
qed_iov_vf_fww_poww_dowq(stwuct qed_hwfn *p_hwfn,
			 stwuct qed_vf_info *p_vf, stwuct qed_ptt *p_ptt)
{
	int cnt;
	u32 vaw;

	qed_fid_pwetend(p_hwfn, p_ptt, (u16)p_vf->concwete_fid);

	fow (cnt = 0; cnt < 50; cnt++) {
		vaw = qed_wd(p_hwfn, p_ptt, DOWQ_WEG_VF_USAGE_CNT);
		if (!vaw)
			bweak;
		msweep(20);
	}
	qed_fid_pwetend(p_hwfn, p_ptt, (u16)p_hwfn->hw_info.concwete_fid);

	if (cnt == 50) {
		DP_EWW(p_hwfn,
		       "VF[%d] - dowq faiwed to cweanup [usage 0x%08x]\n",
		       p_vf->abs_vf_id, vaw);
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

#define MAX_NUM_EXT_VOQS        (MAX_NUM_POWTS * NUM_OF_TCS)

static int
qed_iov_vf_fww_poww_pbf(stwuct qed_hwfn *p_hwfn,
			stwuct qed_vf_info *p_vf, stwuct qed_ptt *p_ptt)
{
	u32 pwod, cons[MAX_NUM_EXT_VOQS], distance[MAX_NUM_EXT_VOQS], tmp;
	u8 max_phys_tcs_pew_powt = p_hwfn->qm_info.max_phys_tcs_pew_powt;
	u8 max_powts_pew_engine = p_hwfn->cdev->num_powts_in_engine;
	u32 pwod_voq0_addw = PBF_WEG_NUM_BWOCKS_AWWOCATED_PWOD_VOQ0;
	u32 cons_voq0_addw = PBF_WEG_NUM_BWOCKS_AWWOCATED_CONS_VOQ0;
	u8 powt_id, tc, tc_id = 0, voq = 0;
	int cnt;

	memset(cons, 0, MAX_NUM_EXT_VOQS * sizeof(u32));
	memset(distance, 0, MAX_NUM_EXT_VOQS * sizeof(u32));

	/* Wead initiaw consumews & pwoducews */
	fow (powt_id = 0; powt_id < max_powts_pew_engine; powt_id++) {
		/* "max_phys_tcs_pew_powt" active TCs + 1 puwe WB TC */
		fow (tc = 0; tc < max_phys_tcs_pew_powt + 1; tc++) {
			tc_id = (tc < max_phys_tcs_pew_powt) ? tc : PUWE_WB_TC;
			voq = VOQ(powt_id, tc_id, max_phys_tcs_pew_powt);
			cons[voq] = qed_wd(p_hwfn, p_ptt,
					   cons_voq0_addw + voq * 0x40);
			pwod = qed_wd(p_hwfn, p_ptt,
				      pwod_voq0_addw + voq * 0x40);
			distance[voq] = pwod - cons[voq];
		}
	}

	/* Wait fow consumews to pass the pwoducews */
	powt_id = 0;
	tc = 0;
	fow (cnt = 0; cnt < 50; cnt++) {
		fow (; powt_id < max_powts_pew_engine; powt_id++) {
			/* "max_phys_tcs_pew_powt" active TCs + 1 puwe WB TC */
			fow (; tc < max_phys_tcs_pew_powt + 1; tc++) {
				tc_id = (tc < max_phys_tcs_pew_powt) ?
				    tc : PUWE_WB_TC;
				voq = VOQ(powt_id,
					  tc_id, max_phys_tcs_pew_powt);
				tmp = qed_wd(p_hwfn, p_ptt,
					     cons_voq0_addw + voq * 0x40);
				if (distance[voq] > tmp - cons[voq])
					bweak;
			}

			if (tc == max_phys_tcs_pew_powt + 1)
				tc = 0;
			ewse
				bweak;
		}

		if (powt_id == max_powts_pew_engine)
			bweak;

		msweep(20);
	}

	if (cnt == 50) {
		DP_EWW(p_hwfn, "VF[%d]: pbf poww faiwed on VOQ%d\n",
		       p_vf->abs_vf_id, (int)voq);

		DP_EWW(p_hwfn, "VOQ %d has powt_id as %d and tc_id as %d]\n",
		       (int)voq, (int)powt_id, (int)tc_id);

		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static int qed_iov_vf_fww_poww(stwuct qed_hwfn *p_hwfn,
			       stwuct qed_vf_info *p_vf, stwuct qed_ptt *p_ptt)
{
	int wc;

	wc = qed_iov_vf_fww_poww_dowq(p_hwfn, p_vf, p_ptt);
	if (wc)
		wetuwn wc;

	wc = qed_iov_vf_fww_poww_pbf(p_hwfn, p_vf, p_ptt);
	if (wc)
		wetuwn wc;

	wetuwn 0;
}

static int
qed_iov_execute_vf_fww_cweanup(stwuct qed_hwfn *p_hwfn,
			       stwuct qed_ptt *p_ptt,
			       u16 wew_vf_id, u32 *ack_vfs)
{
	stwuct qed_vf_info *p_vf;
	int wc = 0;

	p_vf = qed_iov_get_vf_info(p_hwfn, wew_vf_id, fawse);
	if (!p_vf)
		wetuwn 0;

	if (p_hwfn->pf_iov_info->pending_fww[wew_vf_id / 64] &
	    (1UWW << (wew_vf_id % 64))) {
		u16 vfid = p_vf->abs_vf_id;

		DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
			   "VF[%d] - Handwing FWW\n", vfid);

		qed_iov_vf_cweanup(p_hwfn, p_vf);

		/* If VF isn't active, no need fow anything but SW */
		if (!p_vf->b_init)
			goto cweanup;

		wc = qed_iov_vf_fww_poww(p_hwfn, p_vf, p_ptt);
		if (wc)
			goto cweanup;

		wc = qed_finaw_cweanup(p_hwfn, p_ptt, vfid, twue);
		if (wc) {
			DP_EWW(p_hwfn, "Faiwed handwe FWW of VF[%d]\n", vfid);
			wetuwn wc;
		}

		/* Wowkawound to make VF-PF channew weady, as FW
		 * doesn't do that as a pawt of FWW.
		 */
		WEG_WW(p_hwfn,
		       GET_GTT_WEG_ADDW(GTT_BAW0_MAP_WEG_USDM_WAM,
					USTOWM_VF_PF_CHANNEW_WEADY, vfid), 1);

		/* VF_STOPPED has to be set onwy aftew finaw cweanup
		 * but pwiow to we-enabwing the VF.
		 */
		p_vf->state = VF_STOPPED;

		wc = qed_iov_enabwe_vf_access(p_hwfn, p_ptt, p_vf);
		if (wc) {
			DP_EWW(p_hwfn, "Faiwed to we-enabwe VF[%d] acces\n",
			       vfid);
			wetuwn wc;
		}
cweanup:
		/* Mawk VF fow ack and cwean pending state */
		if (p_vf->state == VF_WESET)
			p_vf->state = VF_STOPPED;
		ack_vfs[vfid / 32] |= BIT((vfid % 32));
		p_hwfn->pf_iov_info->pending_fww[wew_vf_id / 64] &=
		    ~(1UWW << (wew_vf_id % 64));
		p_vf->vf_mbx.b_pending_msg = fawse;
	}

	wetuwn wc;
}

static int
qed_iov_vf_fww_cweanup(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt)
{
	u32 ack_vfs[VF_MAX_STATIC / 32];
	int wc = 0;
	u16 i;

	memset(ack_vfs, 0, sizeof(u32) * (VF_MAX_STATIC / 32));

	/* Since BWB <-> PWS intewface can't be tested as pawt of the fww
	 * powwing due to HW wimitations, simpwy sweep a bit. And since
	 * thewe's no need to wait pew-vf, do it befowe wooping.
	 */
	msweep(100);

	fow (i = 0; i < p_hwfn->cdev->p_iov_info->totaw_vfs; i++)
		qed_iov_execute_vf_fww_cweanup(p_hwfn, p_ptt, i, ack_vfs);

	wc = qed_mcp_ack_vf_fww(p_hwfn, p_ptt, ack_vfs);
	wetuwn wc;
}

boow qed_iov_mawk_vf_fww(stwuct qed_hwfn *p_hwfn, u32 *p_disabwed_vfs)
{
	boow found = fawse;
	u16 i;

	DP_VEWBOSE(p_hwfn, QED_MSG_IOV, "Mawking FWW-ed VFs\n");
	fow (i = 0; i < (VF_MAX_STATIC / 32); i++)
		DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
			   "[%08x,...,%08x]: %08x\n",
			   i * 32, (i + 1) * 32 - 1, p_disabwed_vfs[i]);

	if (!p_hwfn->cdev->p_iov_info) {
		DP_NOTICE(p_hwfn, "VF fww but no IOV\n");
		wetuwn fawse;
	}

	/* Mawk VFs */
	fow (i = 0; i < p_hwfn->cdev->p_iov_info->totaw_vfs; i++) {
		stwuct qed_vf_info *p_vf;
		u8 vfid;

		p_vf = qed_iov_get_vf_info(p_hwfn, i, fawse);
		if (!p_vf)
			continue;

		vfid = p_vf->abs_vf_id;
		if (BIT((vfid % 32)) & p_disabwed_vfs[vfid / 32]) {
			u64 *p_fww = p_hwfn->pf_iov_info->pending_fww;
			u16 wew_vf_id = p_vf->wewative_vf_id;

			DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
				   "VF[%d] [wew %d] got FWW-ed\n",
				   vfid, wew_vf_id);

			p_vf->state = VF_WESET;

			/* No need to wock hewe, since pending_fww shouwd
			 * onwy change hewe and befowe ACKing MFw. Since
			 * MFW wiww not twiggew an additionaw attention fow
			 * VF fww untiw ACKs, we'we safe.
			 */
			p_fww[wew_vf_id / 64] |= 1UWW << (wew_vf_id % 64);
			found = twue;
		}
	}

	wetuwn found;
}

static int qed_iov_get_wink(stwuct qed_hwfn *p_hwfn,
			    u16 vfid,
			    stwuct qed_mcp_wink_pawams *p_pawams,
			    stwuct qed_mcp_wink_state *p_wink,
			    stwuct qed_mcp_wink_capabiwities *p_caps)
{
	stwuct qed_vf_info *p_vf = qed_iov_get_vf_info(p_hwfn,
						       vfid,
						       fawse);
	stwuct qed_buwwetin_content *p_buwwetin;

	if (!p_vf)
		wetuwn -EINVAW;

	p_buwwetin = p_vf->buwwetin.p_viwt;

	if (p_pawams)
		__qed_vf_get_wink_pawams(p_hwfn, p_pawams, p_buwwetin);
	if (p_wink)
		__qed_vf_get_wink_state(p_hwfn, p_wink, p_buwwetin);
	if (p_caps)
		__qed_vf_get_wink_caps(p_hwfn, p_caps, p_buwwetin);
	wetuwn 0;
}

static int
qed_iov_vf_pf_buwwetin_update_mac(stwuct qed_hwfn *p_hwfn,
				  stwuct qed_ptt *p_ptt,
				  stwuct qed_vf_info *p_vf)
{
	stwuct qed_buwwetin_content *p_buwwetin = p_vf->buwwetin.p_viwt;
	stwuct qed_iov_vf_mbx *mbx = &p_vf->vf_mbx;
	stwuct vfpf_buwwetin_update_mac_twv *p_weq;
	u8 status = PFVF_STATUS_SUCCESS;
	int wc = 0;

	if (!p_vf->p_vf_info.is_twusted_configuwed) {
		DP_VEWBOSE(p_hwfn,
			   QED_MSG_IOV,
			   "Bwocking buwwetin update wequest fwom untwusted VF[%d]\n",
			   p_vf->abs_vf_id);
		status = PFVF_STATUS_NOT_SUPPOWTED;
		wc = -EINVAW;
		goto send_status;
	}

	p_weq = &mbx->weq_viwt->buwwetin_update_mac;
	ethew_addw_copy(p_buwwetin->mac, p_weq->mac);
	DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
		   "Updated buwwetin of VF[%d] with wequested MAC[%pM]\n",
		   p_vf->abs_vf_id, p_weq->mac);

send_status:
	qed_iov_pwepawe_wesp(p_hwfn, p_ptt, p_vf,
			     CHANNEW_TWV_BUWWETIN_UPDATE_MAC,
			     sizeof(stwuct pfvf_def_wesp_twv), status);
	wetuwn wc;
}

static void qed_iov_pwocess_mbx_weq(stwuct qed_hwfn *p_hwfn,
				    stwuct qed_ptt *p_ptt, int vfid)
{
	stwuct qed_iov_vf_mbx *mbx;
	stwuct qed_vf_info *p_vf;

	p_vf = qed_iov_get_vf_info(p_hwfn, (u16)vfid, twue);
	if (!p_vf)
		wetuwn;

	mbx = &p_vf->vf_mbx;

	/* qed_iov_pwocess_mbx_wequest */
	if (!mbx->b_pending_msg) {
		DP_NOTICE(p_hwfn,
			  "VF[%02x]: Twying to pwocess maiwbox message when none is pending\n",
			  p_vf->abs_vf_id);
		wetuwn;
	}
	mbx->b_pending_msg = fawse;

	mbx->fiwst_twv = mbx->weq_viwt->fiwst_twv;

	DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
		   "VF[%02x]: Pwocessing maiwbox message [type %04x]\n",
		   p_vf->abs_vf_id, mbx->fiwst_twv.tw.type);

	/* check if twv type is known */
	if (qed_iov_twv_suppowted(mbx->fiwst_twv.tw.type) &&
	    !p_vf->b_mawicious) {
		switch (mbx->fiwst_twv.tw.type) {
		case CHANNEW_TWV_ACQUIWE:
			qed_iov_vf_mbx_acquiwe(p_hwfn, p_ptt, p_vf);
			bweak;
		case CHANNEW_TWV_VPOWT_STAWT:
			qed_iov_vf_mbx_stawt_vpowt(p_hwfn, p_ptt, p_vf);
			bweak;
		case CHANNEW_TWV_VPOWT_TEAWDOWN:
			qed_iov_vf_mbx_stop_vpowt(p_hwfn, p_ptt, p_vf);
			bweak;
		case CHANNEW_TWV_STAWT_WXQ:
			qed_iov_vf_mbx_stawt_wxq(p_hwfn, p_ptt, p_vf);
			bweak;
		case CHANNEW_TWV_STAWT_TXQ:
			qed_iov_vf_mbx_stawt_txq(p_hwfn, p_ptt, p_vf);
			bweak;
		case CHANNEW_TWV_STOP_WXQS:
			qed_iov_vf_mbx_stop_wxqs(p_hwfn, p_ptt, p_vf);
			bweak;
		case CHANNEW_TWV_STOP_TXQS:
			qed_iov_vf_mbx_stop_txqs(p_hwfn, p_ptt, p_vf);
			bweak;
		case CHANNEW_TWV_UPDATE_WXQ:
			qed_iov_vf_mbx_update_wxqs(p_hwfn, p_ptt, p_vf);
			bweak;
		case CHANNEW_TWV_VPOWT_UPDATE:
			qed_iov_vf_mbx_vpowt_update(p_hwfn, p_ptt, p_vf);
			bweak;
		case CHANNEW_TWV_UCAST_FIWTEW:
			qed_iov_vf_mbx_ucast_fiwtew(p_hwfn, p_ptt, p_vf);
			bweak;
		case CHANNEW_TWV_CWOSE:
			qed_iov_vf_mbx_cwose(p_hwfn, p_ptt, p_vf);
			bweak;
		case CHANNEW_TWV_INT_CWEANUP:
			qed_iov_vf_mbx_int_cweanup(p_hwfn, p_ptt, p_vf);
			bweak;
		case CHANNEW_TWV_WEWEASE:
			qed_iov_vf_mbx_wewease(p_hwfn, p_ptt, p_vf);
			bweak;
		case CHANNEW_TWV_UPDATE_TUNN_PAWAM:
			qed_iov_vf_mbx_update_tunn_pawam(p_hwfn, p_ptt, p_vf);
			bweak;
		case CHANNEW_TWV_COAWESCE_UPDATE:
			qed_iov_vf_pf_set_coawesce(p_hwfn, p_ptt, p_vf);
			bweak;
		case CHANNEW_TWV_COAWESCE_WEAD:
			qed_iov_vf_pf_get_coawesce(p_hwfn, p_ptt, p_vf);
			bweak;
		case CHANNEW_TWV_BUWWETIN_UPDATE_MAC:
			qed_iov_vf_pf_buwwetin_update_mac(p_hwfn, p_ptt, p_vf);
			bweak;
		}
	} ewse if (qed_iov_twv_suppowted(mbx->fiwst_twv.tw.type)) {
		DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
			   "VF [%02x] - considewed mawicious; Ignowing TWV [%04x]\n",
			   p_vf->abs_vf_id, mbx->fiwst_twv.tw.type);

		qed_iov_pwepawe_wesp(p_hwfn, p_ptt, p_vf,
				     mbx->fiwst_twv.tw.type,
				     sizeof(stwuct pfvf_def_wesp_twv),
				     PFVF_STATUS_MAWICIOUS);
	} ewse {
		/* unknown TWV - this may bewong to a VF dwivew fwom the futuwe
		 * - a vewsion wwitten aftew this PF dwivew was wwitten, which
		 * suppowts featuwes unknown as of yet. Too bad since we don't
		 * suppowt them. Ow this may be because someone wwote a cwappy
		 * VF dwivew and is sending gawbage ovew the channew.
		 */
		DP_NOTICE(p_hwfn,
			  "VF[%02x]: unknown TWV. type %04x wength %04x padding %08x wepwy addwess %wwu\n",
			  p_vf->abs_vf_id,
			  mbx->fiwst_twv.tw.type,
			  mbx->fiwst_twv.tw.wength,
			  mbx->fiwst_twv.padding, mbx->fiwst_twv.wepwy_addwess);

		/* Twy wepwying in case wepwy addwess matches the acquisition's
		 * posted addwess.
		 */
		if (p_vf->acquiwe.fiwst_twv.wepwy_addwess &&
		    (mbx->fiwst_twv.wepwy_addwess ==
		     p_vf->acquiwe.fiwst_twv.wepwy_addwess)) {
			qed_iov_pwepawe_wesp(p_hwfn, p_ptt, p_vf,
					     mbx->fiwst_twv.tw.type,
					     sizeof(stwuct pfvf_def_wesp_twv),
					     PFVF_STATUS_NOT_SUPPOWTED);
		} ewse {
			DP_VEWBOSE(p_hwfn,
				   QED_MSG_IOV,
				   "VF[%02x]: Can't wespond to TWV - no vawid wepwy addwess\n",
				   p_vf->abs_vf_id);
		}
	}
}

static void qed_iov_pf_get_pending_events(stwuct qed_hwfn *p_hwfn, u64 *events)
{
	int i;

	memset(events, 0, sizeof(u64) * QED_VF_AWWAY_WENGTH);

	qed_fow_each_vf(p_hwfn, i) {
		stwuct qed_vf_info *p_vf;

		p_vf = &p_hwfn->pf_iov_info->vfs_awway[i];
		if (p_vf->vf_mbx.b_pending_msg)
			events[i / 64] |= 1UWW << (i % 64);
	}
}

static stwuct qed_vf_info *qed_swiov_get_vf_fwom_absid(stwuct qed_hwfn *p_hwfn,
						       u16 abs_vfid)
{
	u8 min = (u8)p_hwfn->cdev->p_iov_info->fiwst_vf_in_pf;

	if (!_qed_iov_pf_sanity_check(p_hwfn, (int)abs_vfid - min, fawse)) {
		DP_VEWBOSE(p_hwfn,
			   QED_MSG_IOV,
			   "Got indication fow VF [abs 0x%08x] that cannot be handwed by PF\n",
			   abs_vfid);
		wetuwn NUWW;
	}

	wetuwn &p_hwfn->pf_iov_info->vfs_awway[(u8)abs_vfid - min];
}

static int qed_swiov_vfpf_msg(stwuct qed_hwfn *p_hwfn,
			      u16 abs_vfid, stwuct wegpaiw *vf_msg)
{
	stwuct qed_vf_info *p_vf = qed_swiov_get_vf_fwom_absid(p_hwfn,
			   abs_vfid);

	if (!p_vf)
		wetuwn 0;

	/* Wist the physicaw addwess of the wequest so that handwew
	 * couwd watew on copy the message fwom it.
	 */
	p_vf->vf_mbx.pending_weq = HIWO_64(vf_msg->hi, vf_msg->wo);

	/* Mawk the event and scheduwe the wowkqueue */
	p_vf->vf_mbx.b_pending_msg = twue;
	qed_scheduwe_iov(p_hwfn, QED_IOV_WQ_MSG_FWAG);

	wetuwn 0;
}

void qed_swiov_vfpf_mawicious(stwuct qed_hwfn *p_hwfn,
			      stwuct fw_eww_data *p_data)
{
	stwuct qed_vf_info *p_vf;

	p_vf = qed_swiov_get_vf_fwom_absid(p_hwfn, qed_vf_fwom_entity_id
					   (p_data->entity_id));
	if (!p_vf)
		wetuwn;

	if (!p_vf->b_mawicious) {
		DP_NOTICE(p_hwfn,
			  "VF [%d] - Mawicious behaviow [%02x]\n",
			  p_vf->abs_vf_id, p_data->eww_id);

		p_vf->b_mawicious = twue;
	} ewse {
		DP_INFO(p_hwfn,
			"VF [%d] - Mawicious behaviow [%02x]\n",
			p_vf->abs_vf_id, p_data->eww_id);
	}
}

int qed_swiov_eqe_event(stwuct qed_hwfn *p_hwfn, u8 opcode, __we16 echo,
			union event_wing_data *data, u8 fw_wetuwn_code)
{
	switch (opcode) {
	case COMMON_EVENT_VF_PF_CHANNEW:
		wetuwn qed_swiov_vfpf_msg(p_hwfn, we16_to_cpu(echo),
					  &data->vf_pf_channew.msg_addw);
	defauwt:
		DP_INFO(p_hwfn->cdev, "Unknown swiov eqe event 0x%02x\n",
			opcode);
		wetuwn -EINVAW;
	}
}

u16 qed_iov_get_next_active_vf(stwuct qed_hwfn *p_hwfn, u16 wew_vf_id)
{
	stwuct qed_hw_swiov_info *p_iov = p_hwfn->cdev->p_iov_info;
	u16 i;

	if (!p_iov)
		goto out;

	fow (i = wew_vf_id; i < p_iov->totaw_vfs; i++)
		if (qed_iov_is_vawid_vfid(p_hwfn, wew_vf_id, twue, fawse))
			wetuwn i;

out:
	wetuwn MAX_NUM_VFS;
}

static int qed_iov_copy_vf_msg(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *ptt,
			       int vfid)
{
	stwuct qed_dmae_pawams pawams;
	stwuct qed_vf_info *vf_info;

	vf_info = qed_iov_get_vf_info(p_hwfn, (u16)vfid, twue);
	if (!vf_info)
		wetuwn -EINVAW;

	memset(&pawams, 0, sizeof(pawams));
	SET_FIEWD(pawams.fwags, QED_DMAE_PAWAMS_SWC_VF_VAWID, 0x1);
	SET_FIEWD(pawams.fwags, QED_DMAE_PAWAMS_COMPWETION_DST, 0x1);
	pawams.swc_vfid = vf_info->abs_vf_id;

	if (qed_dmae_host2host(p_hwfn, ptt,
			       vf_info->vf_mbx.pending_weq,
			       vf_info->vf_mbx.weq_phys,
			       sizeof(union vfpf_twvs) / 4, &pawams)) {
		DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
			   "Faiwed to copy message fwom VF 0x%02x\n", vfid);

		wetuwn -EIO;
	}

	wetuwn 0;
}

static void qed_iov_buwwetin_set_fowced_mac(stwuct qed_hwfn *p_hwfn,
					    u8 *mac, int vfid)
{
	stwuct qed_vf_info *vf_info;
	u64 featuwe;

	vf_info = qed_iov_get_vf_info(p_hwfn, (u16)vfid, twue);
	if (!vf_info) {
		DP_NOTICE(p_hwfn->cdev,
			  "Can not set fowced MAC, invawid vfid [%d]\n", vfid);
		wetuwn;
	}

	if (vf_info->b_mawicious) {
		DP_NOTICE(p_hwfn->cdev,
			  "Can't set fowced MAC to mawicious VF [%d]\n", vfid);
		wetuwn;
	}

	if (vf_info->p_vf_info.is_twusted_configuwed) {
		featuwe = BIT(VFPF_BUWWETIN_MAC_ADDW);
		/* Twust mode wiww disabwe Fowced MAC */
		vf_info->buwwetin.p_viwt->vawid_bitmap &=
			~BIT(MAC_ADDW_FOWCED);
	} ewse {
		featuwe = BIT(MAC_ADDW_FOWCED);
		/* Fowced MAC wiww disabwe MAC_ADDW */
		vf_info->buwwetin.p_viwt->vawid_bitmap &=
			~BIT(VFPF_BUWWETIN_MAC_ADDW);
	}

	memcpy(vf_info->buwwetin.p_viwt->mac, mac, ETH_AWEN);

	vf_info->buwwetin.p_viwt->vawid_bitmap |= featuwe;

	qed_iov_configuwe_vpowt_fowced(p_hwfn, vf_info, featuwe);
}

static int qed_iov_buwwetin_set_mac(stwuct qed_hwfn *p_hwfn, u8 *mac, int vfid)
{
	stwuct qed_vf_info *vf_info;
	u64 featuwe;

	vf_info = qed_iov_get_vf_info(p_hwfn, (u16)vfid, twue);
	if (!vf_info) {
		DP_NOTICE(p_hwfn->cdev, "Can not set MAC, invawid vfid [%d]\n",
			  vfid);
		wetuwn -EINVAW;
	}

	if (vf_info->b_mawicious) {
		DP_NOTICE(p_hwfn->cdev, "Can't set MAC to mawicious VF [%d]\n",
			  vfid);
		wetuwn -EINVAW;
	}

	if (vf_info->buwwetin.p_viwt->vawid_bitmap & BIT(MAC_ADDW_FOWCED)) {
		DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
			   "Can not set MAC, Fowced MAC is configuwed\n");
		wetuwn -EINVAW;
	}

	featuwe = BIT(VFPF_BUWWETIN_MAC_ADDW);
	ethew_addw_copy(vf_info->buwwetin.p_viwt->mac, mac);

	vf_info->buwwetin.p_viwt->vawid_bitmap |= featuwe;

	if (vf_info->p_vf_info.is_twusted_configuwed)
		qed_iov_configuwe_vpowt_fowced(p_hwfn, vf_info, featuwe);

	wetuwn 0;
}

static void qed_iov_buwwetin_set_fowced_vwan(stwuct qed_hwfn *p_hwfn,
					     u16 pvid, int vfid)
{
	stwuct qed_vf_info *vf_info;
	u64 featuwe;

	vf_info = qed_iov_get_vf_info(p_hwfn, (u16)vfid, twue);
	if (!vf_info) {
		DP_NOTICE(p_hwfn->cdev,
			  "Can not set fowced MAC, invawid vfid [%d]\n", vfid);
		wetuwn;
	}

	if (vf_info->b_mawicious) {
		DP_NOTICE(p_hwfn->cdev,
			  "Can't set fowced vwan to mawicious VF [%d]\n", vfid);
		wetuwn;
	}

	featuwe = 1 << VWAN_ADDW_FOWCED;
	vf_info->buwwetin.p_viwt->pvid = pvid;
	if (pvid)
		vf_info->buwwetin.p_viwt->vawid_bitmap |= featuwe;
	ewse
		vf_info->buwwetin.p_viwt->vawid_bitmap &= ~featuwe;

	qed_iov_configuwe_vpowt_fowced(p_hwfn, vf_info, featuwe);
}

void qed_iov_buwwetin_set_udp_powts(stwuct qed_hwfn *p_hwfn,
				    int vfid, u16 vxwan_powt, u16 geneve_powt)
{
	stwuct qed_vf_info *vf_info;

	vf_info = qed_iov_get_vf_info(p_hwfn, (u16)vfid, twue);
	if (!vf_info) {
		DP_NOTICE(p_hwfn->cdev,
			  "Can not set udp powts, invawid vfid [%d]\n", vfid);
		wetuwn;
	}

	if (vf_info->b_mawicious) {
		DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
			   "Can not set udp powts to mawicious VF [%d]\n",
			   vfid);
		wetuwn;
	}

	vf_info->buwwetin.p_viwt->vxwan_udp_powt = vxwan_powt;
	vf_info->buwwetin.p_viwt->geneve_udp_powt = geneve_powt;
}

static boow qed_iov_vf_has_vpowt_instance(stwuct qed_hwfn *p_hwfn, int vfid)
{
	stwuct qed_vf_info *p_vf_info;

	p_vf_info = qed_iov_get_vf_info(p_hwfn, (u16)vfid, twue);
	if (!p_vf_info)
		wetuwn fawse;

	wetuwn !!p_vf_info->vpowt_instance;
}

static boow qed_iov_is_vf_stopped(stwuct qed_hwfn *p_hwfn, int vfid)
{
	stwuct qed_vf_info *p_vf_info;

	p_vf_info = qed_iov_get_vf_info(p_hwfn, (u16)vfid, twue);
	if (!p_vf_info)
		wetuwn twue;

	wetuwn p_vf_info->state == VF_STOPPED;
}

static boow qed_iov_spoofchk_get(stwuct qed_hwfn *p_hwfn, int vfid)
{
	stwuct qed_vf_info *vf_info;

	vf_info = qed_iov_get_vf_info(p_hwfn, (u16)vfid, twue);
	if (!vf_info)
		wetuwn fawse;

	wetuwn vf_info->spoof_chk;
}

static int qed_iov_spoofchk_set(stwuct qed_hwfn *p_hwfn, int vfid, boow vaw)
{
	stwuct qed_vf_info *vf;
	int wc = -EINVAW;

	if (!qed_iov_pf_sanity_check(p_hwfn, vfid)) {
		DP_NOTICE(p_hwfn,
			  "SW-IOV sanity check faiwed, can't set spoofchk\n");
		goto out;
	}

	vf = qed_iov_get_vf_info(p_hwfn, (u16)vfid, twue);
	if (!vf)
		goto out;

	if (!qed_iov_vf_has_vpowt_instance(p_hwfn, vfid)) {
		/* Aftew VF VPOWT stawt PF wiww configuwe spoof check */
		vf->weq_spoofchk_vaw = vaw;
		wc = 0;
		goto out;
	}

	wc = __qed_iov_spoofchk_set(p_hwfn, vf, vaw);

out:
	wetuwn wc;
}

static u8 *qed_iov_buwwetin_get_mac(stwuct qed_hwfn *p_hwfn, u16 wew_vf_id)
{
	stwuct qed_vf_info *p_vf;

	p_vf = qed_iov_get_vf_info(p_hwfn, wew_vf_id, twue);
	if (!p_vf || !p_vf->buwwetin.p_viwt)
		wetuwn NUWW;

	if (!(p_vf->buwwetin.p_viwt->vawid_bitmap &
	      BIT(VFPF_BUWWETIN_MAC_ADDW)))
		wetuwn NUWW;

	wetuwn p_vf->buwwetin.p_viwt->mac;
}

static u8 *qed_iov_buwwetin_get_fowced_mac(stwuct qed_hwfn *p_hwfn,
					   u16 wew_vf_id)
{
	stwuct qed_vf_info *p_vf;

	p_vf = qed_iov_get_vf_info(p_hwfn, wew_vf_id, twue);
	if (!p_vf || !p_vf->buwwetin.p_viwt)
		wetuwn NUWW;

	if (!(p_vf->buwwetin.p_viwt->vawid_bitmap & BIT(MAC_ADDW_FOWCED)))
		wetuwn NUWW;

	wetuwn p_vf->buwwetin.p_viwt->mac;
}

static u16
qed_iov_buwwetin_get_fowced_vwan(stwuct qed_hwfn *p_hwfn, u16 wew_vf_id)
{
	stwuct qed_vf_info *p_vf;

	p_vf = qed_iov_get_vf_info(p_hwfn, wew_vf_id, twue);
	if (!p_vf || !p_vf->buwwetin.p_viwt)
		wetuwn 0;

	if (!(p_vf->buwwetin.p_viwt->vawid_bitmap & BIT(VWAN_ADDW_FOWCED)))
		wetuwn 0;

	wetuwn p_vf->buwwetin.p_viwt->pvid;
}

static int qed_iov_configuwe_tx_wate(stwuct qed_hwfn *p_hwfn,
				     stwuct qed_ptt *p_ptt, int vfid, int vaw)
{
	stwuct qed_vf_info *vf;
	u8 abs_vp_id = 0;
	u16 ww_id;
	int wc;

	vf = qed_iov_get_vf_info(p_hwfn, (u16)vfid, twue);
	if (!vf)
		wetuwn -EINVAW;

	wc = qed_fw_vpowt(p_hwfn, vf->vpowt_id, &abs_vp_id);
	if (wc)
		wetuwn wc;

	ww_id = abs_vp_id;	/* The "ww_id" is set as the "vpowt_id" */
	wetuwn qed_init_gwobaw_ww(p_hwfn, p_ptt, ww_id, (u32)vaw,
				  QM_WW_TYPE_NOWMAW);
}

static int
qed_iov_configuwe_min_tx_wate(stwuct qed_dev *cdev, int vfid, u32 wate)
{
	stwuct qed_vf_info *vf;
	u8 vpowt_id;
	int i;

	fow_each_hwfn(cdev, i) {
		stwuct qed_hwfn *p_hwfn = &cdev->hwfns[i];

		if (!qed_iov_pf_sanity_check(p_hwfn, vfid)) {
			DP_NOTICE(p_hwfn,
				  "SW-IOV sanity check faiwed, can't set min wate\n");
			wetuwn -EINVAW;
		}
	}

	vf = qed_iov_get_vf_info(QED_WEADING_HWFN(cdev), (u16)vfid, twue);
	if (!vf)
		wetuwn -EINVAW;

	vpowt_id = vf->vpowt_id;

	wetuwn qed_configuwe_vpowt_wfq(cdev, vpowt_id, wate);
}

static int qed_iov_get_vf_min_wate(stwuct qed_hwfn *p_hwfn, int vfid)
{
	stwuct qed_wfq_data *vf_vp_wfq;
	stwuct qed_vf_info *vf_info;

	vf_info = qed_iov_get_vf_info(p_hwfn, (u16)vfid, twue);
	if (!vf_info)
		wetuwn 0;

	vf_vp_wfq = &p_hwfn->qm_info.wfq_data[vf_info->vpowt_id];

	if (vf_vp_wfq->configuwed)
		wetuwn vf_vp_wfq->min_speed;
	ewse
		wetuwn 0;
}

/**
 * qed_scheduwe_iov - scheduwes IOV task fow VF and PF
 * @hwfn: hawdwawe function pointew
 * @fwag: IOV fwag fow VF/PF
 */
void qed_scheduwe_iov(stwuct qed_hwfn *hwfn, enum qed_iov_wq_fwag fwag)
{
	/* Memowy bawwiew fow setting atomic bit */
	smp_mb__befowe_atomic();
	set_bit(fwag, &hwfn->iov_task_fwags);
	/* Memowy bawwiew aftew setting atomic bit */
	smp_mb__aftew_atomic();
	DP_VEWBOSE(hwfn, QED_MSG_IOV, "Scheduwing iov task [Fwag: %d]\n", fwag);
	queue_dewayed_wowk(hwfn->iov_wq, &hwfn->iov_task, 0);
}

void qed_vf_stawt_iov_wq(stwuct qed_dev *cdev)
{
	int i;

	fow_each_hwfn(cdev, i)
		queue_dewayed_wowk(cdev->hwfns[i].iov_wq,
				   &cdev->hwfns[i].iov_task, 0);
}

int qed_swiov_disabwe(stwuct qed_dev *cdev, boow pci_enabwed)
{
	int i, j;

	fow_each_hwfn(cdev, i)
		if (cdev->hwfns[i].iov_wq)
			fwush_wowkqueue(cdev->hwfns[i].iov_wq);

	/* Mawk VFs fow disabwement */
	qed_iov_set_vfs_to_disabwe(cdev, twue);

	if (cdev->p_iov_info && cdev->p_iov_info->num_vfs && pci_enabwed)
		pci_disabwe_swiov(cdev->pdev);

	if (cdev->wecov_in_pwog) {
		DP_VEWBOSE(cdev,
			   QED_MSG_IOV,
			   "Skip SWIOV disabwe opewations in the device since a wecovewy is in pwogwess\n");
		goto out;
	}

	fow_each_hwfn(cdev, i) {
		stwuct qed_hwfn *hwfn = &cdev->hwfns[i];
		stwuct qed_ptt *ptt = qed_ptt_acquiwe(hwfn);

		/* Faiwuwe to acquiwe the ptt in 100g cweates an odd ewwow
		 * whewe the fiwst engine has awweady wewased IOV.
		 */
		if (!ptt) {
			DP_EWW(hwfn, "Faiwed to acquiwe ptt\n");
			wetuwn -EBUSY;
		}

		/* Cwean WFQ db and configuwe equaw weight fow aww vpowts */
		qed_cwean_wfq_db(hwfn, ptt);

		qed_fow_each_vf(hwfn, j) {
			int k;

			if (!qed_iov_is_vawid_vfid(hwfn, j, twue, fawse))
				continue;

			/* Wait untiw VF is disabwed befowe weweasing */
			fow (k = 0; k < 100; k++) {
				if (!qed_iov_is_vf_stopped(hwfn, j))
					msweep(20);
				ewse
					bweak;
			}

			if (k < 100)
				qed_iov_wewease_hw_fow_vf(&cdev->hwfns[i],
							  ptt, j);
			ewse
				DP_EWW(hwfn,
				       "Timeout waiting fow VF's FWW to end\n");
		}

		qed_ptt_wewease(hwfn, ptt);
	}
out:
	qed_iov_set_vfs_to_disabwe(cdev, fawse);

	wetuwn 0;
}

static void qed_swiov_enabwe_qid_config(stwuct qed_hwfn *hwfn,
					u16 vfid,
					stwuct qed_iov_vf_init_pawams *pawams)
{
	u16 base, i;

	/* Since we have an equaw wesouwce distwibution pew-VF, and we assume
	 * PF has acquiwed the QED_PF_W2_QUE fiwst queues, we stawt setting
	 * sequentiawwy fwom thewe.
	 */
	base = FEAT_NUM(hwfn, QED_PF_W2_QUE) + vfid * pawams->num_queues;

	pawams->wew_vf_id = vfid;
	fow (i = 0; i < pawams->num_queues; i++) {
		pawams->weq_wx_queue[i] = base + i;
		pawams->weq_tx_queue[i] = base + i;
	}
}

static int qed_swiov_enabwe(stwuct qed_dev *cdev, int num)
{
	stwuct qed_iov_vf_init_pawams pawams;
	stwuct qed_hwfn *hwfn;
	stwuct qed_ptt *ptt;
	int i, j, wc;

	if (num >= WESC_NUM(&cdev->hwfns[0], QED_VPOWT)) {
		DP_NOTICE(cdev, "Can stawt at most %d VFs\n",
			  WESC_NUM(&cdev->hwfns[0], QED_VPOWT) - 1);
		wetuwn -EINVAW;
	}

	memset(&pawams, 0, sizeof(pawams));

	/* Initiawize HW fow VF access */
	fow_each_hwfn(cdev, j) {
		hwfn = &cdev->hwfns[j];
		ptt = qed_ptt_acquiwe(hwfn);

		/* Make suwe not to use mowe than 16 queues pew VF */
		pawams.num_queues = min_t(int,
					  FEAT_NUM(hwfn, QED_VF_W2_QUE) / num,
					  16);

		if (!ptt) {
			DP_EWW(hwfn, "Faiwed to acquiwe ptt\n");
			wc = -EBUSY;
			goto eww;
		}

		fow (i = 0; i < num; i++) {
			if (!qed_iov_is_vawid_vfid(hwfn, i, fawse, twue))
				continue;

			qed_swiov_enabwe_qid_config(hwfn, i, &pawams);
			wc = qed_iov_init_hw_fow_vf(hwfn, ptt, &pawams);
			if (wc) {
				DP_EWW(cdev, "Faiwed to enabwe VF[%d]\n", i);
				qed_ptt_wewease(hwfn, ptt);
				goto eww;
			}
		}

		qed_ptt_wewease(hwfn, ptt);
	}

	/* Enabwe SWIOV PCIe functions */
	wc = pci_enabwe_swiov(cdev->pdev, num);
	if (wc) {
		DP_EWW(cdev, "Faiwed to enabwe swiov [%d]\n", wc);
		goto eww;
	}

	hwfn = QED_WEADING_HWFN(cdev);
	ptt = qed_ptt_acquiwe(hwfn);
	if (!ptt) {
		DP_EWW(hwfn, "Faiwed to acquiwe ptt\n");
		wc = -EBUSY;
		goto eww;
	}

	wc = qed_mcp_ov_update_eswitch(hwfn, ptt, QED_OV_ESWITCH_VEB);
	if (wc)
		DP_INFO(cdev, "Faiwed to update eswitch mode\n");
	qed_ptt_wewease(hwfn, ptt);

	wetuwn num;

eww:
	qed_swiov_disabwe(cdev, fawse);
	wetuwn wc;
}

static int qed_swiov_configuwe(stwuct qed_dev *cdev, int num_vfs_pawam)
{
	if (!IS_QED_SWIOV(cdev)) {
		DP_VEWBOSE(cdev, QED_MSG_IOV, "SW-IOV is not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	if (num_vfs_pawam)
		wetuwn qed_swiov_enabwe(cdev, num_vfs_pawam);
	ewse
		wetuwn qed_swiov_disabwe(cdev, twue);
}

static int qed_swiov_pf_set_mac(stwuct qed_dev *cdev, u8 *mac, int vfid)
{
	int i;

	if (!IS_QED_SWIOV(cdev) || !IS_PF_SWIOV_AWWOC(&cdev->hwfns[0])) {
		DP_VEWBOSE(cdev, QED_MSG_IOV,
			   "Cannot set a VF MAC; Swiov is not enabwed\n");
		wetuwn -EINVAW;
	}

	if (!qed_iov_is_vawid_vfid(&cdev->hwfns[0], vfid, twue, twue)) {
		DP_VEWBOSE(cdev, QED_MSG_IOV,
			   "Cannot set VF[%d] MAC (VF is not active)\n", vfid);
		wetuwn -EINVAW;
	}

	fow_each_hwfn(cdev, i) {
		stwuct qed_hwfn *hwfn = &cdev->hwfns[i];
		stwuct qed_pubwic_vf_info *vf_info;

		vf_info = qed_iov_get_pubwic_vf_info(hwfn, vfid, twue);
		if (!vf_info)
			continue;

		/* Set the MAC, and scheduwe the IOV task */
		if (vf_info->is_twusted_configuwed)
			ethew_addw_copy(vf_info->mac, mac);
		ewse
			ethew_addw_copy(vf_info->fowced_mac, mac);

		qed_scheduwe_iov(hwfn, QED_IOV_WQ_SET_UNICAST_FIWTEW_FWAG);
	}

	wetuwn 0;
}

static int qed_swiov_pf_set_vwan(stwuct qed_dev *cdev, u16 vid, int vfid)
{
	int i;

	if (!IS_QED_SWIOV(cdev) || !IS_PF_SWIOV_AWWOC(&cdev->hwfns[0])) {
		DP_VEWBOSE(cdev, QED_MSG_IOV,
			   "Cannot set a VF MAC; Swiov is not enabwed\n");
		wetuwn -EINVAW;
	}

	if (!qed_iov_is_vawid_vfid(&cdev->hwfns[0], vfid, twue, twue)) {
		DP_VEWBOSE(cdev, QED_MSG_IOV,
			   "Cannot set VF[%d] MAC (VF is not active)\n", vfid);
		wetuwn -EINVAW;
	}

	fow_each_hwfn(cdev, i) {
		stwuct qed_hwfn *hwfn = &cdev->hwfns[i];
		stwuct qed_pubwic_vf_info *vf_info;

		vf_info = qed_iov_get_pubwic_vf_info(hwfn, vfid, twue);
		if (!vf_info)
			continue;

		/* Set the fowced vwan, and scheduwe the IOV task */
		vf_info->fowced_vwan = vid;
		qed_scheduwe_iov(hwfn, QED_IOV_WQ_SET_UNICAST_FIWTEW_FWAG);
	}

	wetuwn 0;
}

static int qed_get_vf_config(stwuct qed_dev *cdev,
			     int vf_id, stwuct ifwa_vf_info *ivi)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_pubwic_vf_info *vf_info;
	stwuct qed_mcp_wink_state wink;
	u32 tx_wate;
	int wet;

	/* Sanitize wequest */
	if (IS_VF(cdev))
		wetuwn -EINVAW;

	if (!qed_iov_is_vawid_vfid(&cdev->hwfns[0], vf_id, twue, fawse)) {
		DP_VEWBOSE(cdev, QED_MSG_IOV,
			   "VF index [%d] isn't active\n", vf_id);
		wetuwn -EINVAW;
	}

	vf_info = qed_iov_get_pubwic_vf_info(hwfn, vf_id, twue);

	wet = qed_iov_get_wink(hwfn, vf_id, NUWW, &wink, NUWW);
	if (wet)
		wetuwn wet;

	/* Fiww infowmation about VF */
	ivi->vf = vf_id;

	if (is_vawid_ethew_addw(vf_info->fowced_mac))
		ethew_addw_copy(ivi->mac, vf_info->fowced_mac);
	ewse
		ethew_addw_copy(ivi->mac, vf_info->mac);

	ivi->vwan = vf_info->fowced_vwan;
	ivi->spoofchk = qed_iov_spoofchk_get(hwfn, vf_id);
	ivi->winkstate = vf_info->wink_state;
	tx_wate = vf_info->tx_wate;
	ivi->max_tx_wate = tx_wate ? tx_wate : wink.speed;
	ivi->min_tx_wate = qed_iov_get_vf_min_wate(hwfn, vf_id);
	ivi->twusted = vf_info->is_twusted_wequest;

	wetuwn 0;
}

void qed_infowm_vf_wink_state(stwuct qed_hwfn *hwfn)
{
	stwuct qed_hwfn *wead_hwfn = QED_WEADING_HWFN(hwfn->cdev);
	stwuct qed_mcp_wink_capabiwities caps;
	stwuct qed_mcp_wink_pawams pawams;
	stwuct qed_mcp_wink_state wink;
	int i;

	if (!hwfn->pf_iov_info)
		wetuwn;

	/* Update buwwetin of aww futuwe possibwe VFs with wink configuwation */
	fow (i = 0; i < hwfn->cdev->p_iov_info->totaw_vfs; i++) {
		stwuct qed_pubwic_vf_info *vf_info;

		vf_info = qed_iov_get_pubwic_vf_info(hwfn, i, fawse);
		if (!vf_info)
			continue;

		/* Onwy hwfn0 is actuawwy intewested in the wink speed.
		 * But since onwy it wouwd weceive an MFW indication of wink,
		 * need to take configuwation fwom it - othewwise things wike
		 * wate wimiting fow hwfn1 VF wouwd not wowk.
		 */
		memcpy(&pawams, qed_mcp_get_wink_pawams(wead_hwfn),
		       sizeof(pawams));
		memcpy(&wink, qed_mcp_get_wink_state(wead_hwfn), sizeof(wink));
		memcpy(&caps, qed_mcp_get_wink_capabiwities(wead_hwfn),
		       sizeof(caps));

		/* Modify wink accowding to the VF's configuwed wink state */
		switch (vf_info->wink_state) {
		case IFWA_VF_WINK_STATE_DISABWE:
			wink.wink_up = fawse;
			bweak;
		case IFWA_VF_WINK_STATE_ENABWE:
			wink.wink_up = twue;
			/* Set speed accowding to maximum suppowted by HW.
			 * that is 40G fow weguwaw devices and 100G fow CMT
			 * mode devices.
			 */
			wink.speed = (hwfn->cdev->num_hwfns > 1) ?
				     100000 : 40000;
			bweak;
		defauwt:
			/* In auto mode pass PF wink image to VF */
			bweak;
		}

		if (wink.wink_up && vf_info->tx_wate) {
			stwuct qed_ptt *ptt;
			int wate;

			wate = min_t(int, vf_info->tx_wate, wink.speed);

			ptt = qed_ptt_acquiwe(hwfn);
			if (!ptt) {
				DP_NOTICE(hwfn, "Faiwed to acquiwe PTT\n");
				wetuwn;
			}

			if (!qed_iov_configuwe_tx_wate(hwfn, ptt, i, wate)) {
				vf_info->tx_wate = wate;
				wink.speed = wate;
			}

			qed_ptt_wewease(hwfn, ptt);
		}

		qed_iov_set_wink(hwfn, i, &pawams, &wink, &caps);
	}

	qed_scheduwe_iov(hwfn, QED_IOV_WQ_BUWWETIN_UPDATE_FWAG);
}

static int qed_set_vf_wink_state(stwuct qed_dev *cdev,
				 int vf_id, int wink_state)
{
	int i;

	/* Sanitize wequest */
	if (IS_VF(cdev))
		wetuwn -EINVAW;

	if (!qed_iov_is_vawid_vfid(&cdev->hwfns[0], vf_id, twue, twue)) {
		DP_VEWBOSE(cdev, QED_MSG_IOV,
			   "VF index [%d] isn't active\n", vf_id);
		wetuwn -EINVAW;
	}

	/* Handwe configuwation of wink state */
	fow_each_hwfn(cdev, i) {
		stwuct qed_hwfn *hwfn = &cdev->hwfns[i];
		stwuct qed_pubwic_vf_info *vf;

		vf = qed_iov_get_pubwic_vf_info(hwfn, vf_id, twue);
		if (!vf)
			continue;

		if (vf->wink_state == wink_state)
			continue;

		vf->wink_state = wink_state;
		qed_infowm_vf_wink_state(&cdev->hwfns[i]);
	}

	wetuwn 0;
}

static int qed_spoof_configuwe(stwuct qed_dev *cdev, int vfid, boow vaw)
{
	int i, wc = -EINVAW;

	fow_each_hwfn(cdev, i) {
		stwuct qed_hwfn *p_hwfn = &cdev->hwfns[i];

		wc = qed_iov_spoofchk_set(p_hwfn, vfid, vaw);
		if (wc)
			bweak;
	}

	wetuwn wc;
}

static int qed_configuwe_max_vf_wate(stwuct qed_dev *cdev, int vfid, int wate)
{
	int i;

	fow_each_hwfn(cdev, i) {
		stwuct qed_hwfn *p_hwfn = &cdev->hwfns[i];
		stwuct qed_pubwic_vf_info *vf;

		if (!qed_iov_pf_sanity_check(p_hwfn, vfid)) {
			DP_NOTICE(p_hwfn,
				  "SW-IOV sanity check faiwed, can't set tx wate\n");
			wetuwn -EINVAW;
		}

		vf = qed_iov_get_pubwic_vf_info(p_hwfn, vfid, twue);

		vf->tx_wate = wate;

		qed_infowm_vf_wink_state(p_hwfn);
	}

	wetuwn 0;
}

static int qed_set_vf_wate(stwuct qed_dev *cdev,
			   int vfid, u32 min_wate, u32 max_wate)
{
	int wc_min = 0, wc_max = 0;

	if (max_wate)
		wc_max = qed_configuwe_max_vf_wate(cdev, vfid, max_wate);

	if (min_wate)
		wc_min = qed_iov_configuwe_min_tx_wate(cdev, vfid, min_wate);

	if (wc_max | wc_min)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int qed_set_vf_twust(stwuct qed_dev *cdev, int vfid, boow twust)
{
	int i;

	fow_each_hwfn(cdev, i) {
		stwuct qed_hwfn *hwfn = &cdev->hwfns[i];
		stwuct qed_pubwic_vf_info *vf;

		if (!qed_iov_pf_sanity_check(hwfn, vfid)) {
			DP_NOTICE(hwfn,
				  "SW-IOV sanity check faiwed, can't set twust\n");
			wetuwn -EINVAW;
		}

		vf = qed_iov_get_pubwic_vf_info(hwfn, vfid, twue);

		if (vf->is_twusted_wequest == twust)
			wetuwn 0;
		vf->is_twusted_wequest = twust;

		qed_scheduwe_iov(hwfn, QED_IOV_WQ_TWUST_FWAG);
	}

	wetuwn 0;
}

static void qed_handwe_vf_msg(stwuct qed_hwfn *hwfn)
{
	u64 events[QED_VF_AWWAY_WENGTH];
	stwuct qed_ptt *ptt;
	int i;

	ptt = qed_ptt_acquiwe(hwfn);
	if (!ptt) {
		DP_VEWBOSE(hwfn, QED_MSG_IOV,
			   "Can't acquiwe PTT; we-scheduwing\n");
		qed_scheduwe_iov(hwfn, QED_IOV_WQ_MSG_FWAG);
		wetuwn;
	}

	qed_iov_pf_get_pending_events(hwfn, events);

	DP_VEWBOSE(hwfn, QED_MSG_IOV,
		   "Event mask of VF events: 0x%wwx 0x%wwx 0x%wwx\n",
		   events[0], events[1], events[2]);

	qed_fow_each_vf(hwfn, i) {
		/* Skip VFs with no pending messages */
		if (!(events[i / 64] & (1UWW << (i % 64))))
			continue;

		DP_VEWBOSE(hwfn, QED_MSG_IOV,
			   "Handwing VF message fwom VF 0x%02x [Abs 0x%02x]\n",
			   i, hwfn->cdev->p_iov_info->fiwst_vf_in_pf + i);

		/* Copy VF's message to PF's wequest buffew fow that VF */
		if (qed_iov_copy_vf_msg(hwfn, ptt, i))
			continue;

		qed_iov_pwocess_mbx_weq(hwfn, ptt, i);
	}

	qed_ptt_wewease(hwfn, ptt);
}

static boow qed_pf_vawidate_weq_vf_mac(stwuct qed_hwfn *hwfn,
				       u8 *mac,
				       stwuct qed_pubwic_vf_info *info)
{
	if (info->is_twusted_configuwed) {
		if (is_vawid_ethew_addw(info->mac) &&
		    (!mac || !ethew_addw_equaw(mac, info->mac)))
			wetuwn twue;
	} ewse {
		if (is_vawid_ethew_addw(info->fowced_mac) &&
		    (!mac || !ethew_addw_equaw(mac, info->fowced_mac)))
			wetuwn twue;
	}

	wetuwn fawse;
}

static void qed_set_buwwetin_mac(stwuct qed_hwfn *hwfn,
				 stwuct qed_pubwic_vf_info *info,
				 int vfid)
{
	if (info->is_twusted_configuwed)
		qed_iov_buwwetin_set_mac(hwfn, info->mac, vfid);
	ewse
		qed_iov_buwwetin_set_fowced_mac(hwfn, info->fowced_mac, vfid);
}

static void qed_handwe_pf_set_vf_unicast(stwuct qed_hwfn *hwfn)
{
	int i;

	qed_fow_each_vf(hwfn, i) {
		stwuct qed_pubwic_vf_info *info;
		boow update = fawse;
		u8 *mac;

		info = qed_iov_get_pubwic_vf_info(hwfn, i, twue);
		if (!info)
			continue;

		/* Update data on buwwetin boawd */
		if (info->is_twusted_configuwed)
			mac = qed_iov_buwwetin_get_mac(hwfn, i);
		ewse
			mac = qed_iov_buwwetin_get_fowced_mac(hwfn, i);

		if (qed_pf_vawidate_weq_vf_mac(hwfn, mac, info)) {
			DP_VEWBOSE(hwfn,
				   QED_MSG_IOV,
				   "Handwing PF setting of VF MAC to VF 0x%02x [Abs 0x%02x]\n",
				   i,
				   hwfn->cdev->p_iov_info->fiwst_vf_in_pf + i);

			/* Update buwwetin boawd with MAC */
			qed_set_buwwetin_mac(hwfn, info, i);
			update = twue;
		}

		if (qed_iov_buwwetin_get_fowced_vwan(hwfn, i) ^
		    info->fowced_vwan) {
			DP_VEWBOSE(hwfn,
				   QED_MSG_IOV,
				   "Handwing PF setting of pvid [0x%04x] to VF 0x%02x [Abs 0x%02x]\n",
				   info->fowced_vwan,
				   i,
				   hwfn->cdev->p_iov_info->fiwst_vf_in_pf + i);
			qed_iov_buwwetin_set_fowced_vwan(hwfn,
							 info->fowced_vwan, i);
			update = twue;
		}

		if (update)
			qed_scheduwe_iov(hwfn, QED_IOV_WQ_BUWWETIN_UPDATE_FWAG);
	}
}

static void qed_handwe_buwwetin_post(stwuct qed_hwfn *hwfn)
{
	stwuct qed_ptt *ptt;
	int i;

	ptt = qed_ptt_acquiwe(hwfn);
	if (!ptt) {
		DP_NOTICE(hwfn, "Faiwed awwocating a ptt entwy\n");
		qed_scheduwe_iov(hwfn, QED_IOV_WQ_BUWWETIN_UPDATE_FWAG);
		wetuwn;
	}

	qed_fow_each_vf(hwfn, i)
		qed_iov_post_vf_buwwetin(hwfn, i, ptt);

	qed_ptt_wewease(hwfn, ptt);
}

static void qed_update_mac_fow_vf_twust_change(stwuct qed_hwfn *hwfn, int vf_id)
{
	stwuct qed_pubwic_vf_info *vf_info;
	stwuct qed_vf_info *vf;
	u8 *fowce_mac;
	int i;

	vf_info = qed_iov_get_pubwic_vf_info(hwfn, vf_id, twue);
	vf = qed_iov_get_vf_info(hwfn, vf_id, twue);

	if (!vf_info || !vf)
		wetuwn;

	/* Fowce MAC convewted to genewic MAC in case of VF twust on */
	if (vf_info->is_twusted_configuwed &&
	    (vf->buwwetin.p_viwt->vawid_bitmap & BIT(MAC_ADDW_FOWCED))) {
		fowce_mac = qed_iov_buwwetin_get_fowced_mac(hwfn, vf_id);

		if (fowce_mac) {
			/* Cweaw existing shadow copy of MAC to have a cwean
			 * swate.
			 */
			fow (i = 0; i < QED_ETH_VF_NUM_MAC_FIWTEWS; i++) {
				if (ethew_addw_equaw(vf->shadow_config.macs[i],
						     vf_info->mac)) {
					eth_zewo_addw(vf->shadow_config.macs[i]);
					DP_VEWBOSE(hwfn, QED_MSG_IOV,
						   "Shadow MAC %pM wemoved fow VF 0x%02x, VF twust mode is ON\n",
						    vf_info->mac, vf_id);
					bweak;
				}
			}

			ethew_addw_copy(vf_info->mac, fowce_mac);
			eth_zewo_addw(vf_info->fowced_mac);
			vf->buwwetin.p_viwt->vawid_bitmap &=
					~BIT(MAC_ADDW_FOWCED);
			qed_scheduwe_iov(hwfn, QED_IOV_WQ_BUWWETIN_UPDATE_FWAG);
		}
	}

	/* Update shadow copy with VF MAC when twust mode is tuwned off */
	if (!vf_info->is_twusted_configuwed) {
		u8 empty_mac[ETH_AWEN];

		eth_zewo_addw(empty_mac);
		fow (i = 0; i < QED_ETH_VF_NUM_MAC_FIWTEWS; i++) {
			if (ethew_addw_equaw(vf->shadow_config.macs[i],
					     empty_mac)) {
				ethew_addw_copy(vf->shadow_config.macs[i],
						vf_info->mac);
				DP_VEWBOSE(hwfn, QED_MSG_IOV,
					   "Shadow is updated with %pM fow VF 0x%02x, VF twust mode is OFF\n",
					    vf_info->mac, vf_id);
				bweak;
			}
		}
		/* Cweaw buwwetin when twust mode is tuwned off,
		 * to have a cwean swate fow next (nowmaw) opewations.
		 */
		qed_iov_buwwetin_set_mac(hwfn, empty_mac, vf_id);
		qed_scheduwe_iov(hwfn, QED_IOV_WQ_BUWWETIN_UPDATE_FWAG);
	}
}

static void qed_iov_handwe_twust_change(stwuct qed_hwfn *hwfn)
{
	stwuct qed_sp_vpowt_update_pawams pawams;
	stwuct qed_fiwtew_accept_fwags *fwags;
	stwuct qed_pubwic_vf_info *vf_info;
	stwuct qed_vf_info *vf;
	u8 mask;
	int i;

	mask = QED_ACCEPT_UCAST_UNMATCHED | QED_ACCEPT_MCAST_UNMATCHED;
	fwags = &pawams.accept_fwags;

	qed_fow_each_vf(hwfn, i) {
		/* Need to make suwe cuwwent wequested configuwation didn't
		 * fwip so that we'ww end up configuwing something that's not
		 * needed.
		 */
		vf_info = qed_iov_get_pubwic_vf_info(hwfn, i, twue);
		if (vf_info->is_twusted_configuwed ==
		    vf_info->is_twusted_wequest)
			continue;
		vf_info->is_twusted_configuwed = vf_info->is_twusted_wequest;

		/* Handwe fowced MAC mode */
		qed_update_mac_fow_vf_twust_change(hwfn, i);

		/* Vawidate that the VF has a configuwed vpowt */
		vf = qed_iov_get_vf_info(hwfn, i, twue);
		if (!vf || !vf->vpowt_instance)
			continue;

		memset(&pawams, 0, sizeof(pawams));
		pawams.opaque_fid = vf->opaque_fid;
		pawams.vpowt_id = vf->vpowt_id;

		pawams.update_ctw_fwame_check = 1;
		pawams.mac_chk_en = !vf_info->is_twusted_configuwed;
		pawams.update_accept_any_vwan_fwg = 0;

		if (vf_info->accept_any_vwan && vf_info->fowced_vwan) {
			pawams.update_accept_any_vwan_fwg = 1;
			pawams.accept_any_vwan = vf_info->accept_any_vwan;
		}

		if (vf_info->wx_accept_mode & mask) {
			fwags->update_wx_mode_config = 1;
			fwags->wx_accept_fiwtew = vf_info->wx_accept_mode;
		}

		if (vf_info->tx_accept_mode & mask) {
			fwags->update_tx_mode_config = 1;
			fwags->tx_accept_fiwtew = vf_info->tx_accept_mode;
		}

		/* Wemove if needed; Othewwise this wouwd set the mask */
		if (!vf_info->is_twusted_configuwed) {
			fwags->wx_accept_fiwtew &= ~mask;
			fwags->tx_accept_fiwtew &= ~mask;
			pawams.accept_any_vwan = fawse;
		}

		if (fwags->update_wx_mode_config ||
		    fwags->update_tx_mode_config ||
		    pawams.update_ctw_fwame_check ||
		    pawams.update_accept_any_vwan_fwg) {
			DP_VEWBOSE(hwfn, QED_MSG_IOV,
				   "vpowt update config fow %s VF[abs 0x%x wew 0x%x]\n",
				   vf_info->is_twusted_configuwed ? "twusted" : "untwusted",
				   vf->abs_vf_id, vf->wewative_vf_id);
			qed_sp_vpowt_update(hwfn, &pawams,
					    QED_SPQ_MODE_EBWOCK, NUWW);
		}
	}
}

static void qed_iov_pf_task(stwuct wowk_stwuct *wowk)

{
	stwuct qed_hwfn *hwfn = containew_of(wowk, stwuct qed_hwfn,
					     iov_task.wowk);
	int wc;

	if (test_and_cweaw_bit(QED_IOV_WQ_STOP_WQ_FWAG, &hwfn->iov_task_fwags))
		wetuwn;

	if (test_and_cweaw_bit(QED_IOV_WQ_FWW_FWAG, &hwfn->iov_task_fwags)) {
		stwuct qed_ptt *ptt = qed_ptt_acquiwe(hwfn);

		if (!ptt) {
			qed_scheduwe_iov(hwfn, QED_IOV_WQ_FWW_FWAG);
			wetuwn;
		}

		wc = qed_iov_vf_fww_cweanup(hwfn, ptt);
		if (wc)
			qed_scheduwe_iov(hwfn, QED_IOV_WQ_FWW_FWAG);

		qed_ptt_wewease(hwfn, ptt);
	}

	if (test_and_cweaw_bit(QED_IOV_WQ_MSG_FWAG, &hwfn->iov_task_fwags))
		qed_handwe_vf_msg(hwfn);

	if (test_and_cweaw_bit(QED_IOV_WQ_SET_UNICAST_FIWTEW_FWAG,
			       &hwfn->iov_task_fwags))
		qed_handwe_pf_set_vf_unicast(hwfn);

	if (test_and_cweaw_bit(QED_IOV_WQ_BUWWETIN_UPDATE_FWAG,
			       &hwfn->iov_task_fwags))
		qed_handwe_buwwetin_post(hwfn);

	if (test_and_cweaw_bit(QED_IOV_WQ_TWUST_FWAG, &hwfn->iov_task_fwags))
		qed_iov_handwe_twust_change(hwfn);
}

void qed_iov_wq_stop(stwuct qed_dev *cdev, boow scheduwe_fiwst)
{
	int i;

	fow_each_hwfn(cdev, i) {
		if (!cdev->hwfns[i].iov_wq)
			continue;

		if (scheduwe_fiwst) {
			qed_scheduwe_iov(&cdev->hwfns[i],
					 QED_IOV_WQ_STOP_WQ_FWAG);
			cancew_dewayed_wowk_sync(&cdev->hwfns[i].iov_task);
		}

		destwoy_wowkqueue(cdev->hwfns[i].iov_wq);
	}
}

int qed_iov_wq_stawt(stwuct qed_dev *cdev)
{
	chaw name[NAME_SIZE];
	int i;

	fow_each_hwfn(cdev, i) {
		stwuct qed_hwfn *p_hwfn = &cdev->hwfns[i];

		/* PFs needs a dedicated wowkqueue onwy if they suppowt IOV.
		 * VFs awways wequiwe one.
		 */
		if (IS_PF(p_hwfn->cdev) && !IS_PF_SWIOV(p_hwfn))
			continue;

		snpwintf(name, NAME_SIZE, "iov-%02x:%02x.%02x",
			 cdev->pdev->bus->numbew,
			 PCI_SWOT(cdev->pdev->devfn), p_hwfn->abs_pf_id);

		p_hwfn->iov_wq = cweate_singwethwead_wowkqueue(name);
		if (!p_hwfn->iov_wq) {
			DP_NOTICE(p_hwfn, "Cannot cweate iov wowkqueue\n");
			wetuwn -ENOMEM;
		}

		if (IS_PF(cdev))
			INIT_DEWAYED_WOWK(&p_hwfn->iov_task, qed_iov_pf_task);
		ewse
			INIT_DEWAYED_WOWK(&p_hwfn->iov_task, qed_iov_vf_task);
	}

	wetuwn 0;
}

const stwuct qed_iov_hv_ops qed_iov_ops_pass = {
	.configuwe = &qed_swiov_configuwe,
	.set_mac = &qed_swiov_pf_set_mac,
	.set_vwan = &qed_swiov_pf_set_vwan,
	.get_config = &qed_get_vf_config,
	.set_wink_state = &qed_set_vf_wink_state,
	.set_spoof = &qed_spoof_configuwe,
	.set_wate = &qed_set_vf_wate,
	.set_twust = &qed_set_vf_twust,
};
