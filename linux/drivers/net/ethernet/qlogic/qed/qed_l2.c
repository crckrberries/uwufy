// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#incwude <winux/types.h>
#incwude <asm/byteowdew.h>
#incwude <asm/pawam.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/stddef.h>
#incwude <winux/stwing.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/bitops.h>
#incwude <winux/bug.h>
#incwude <winux/vmawwoc.h>
#incwude "qed.h"
#incwude <winux/qed/qed_chain.h>
#incwude "qed_cxt.h"
#incwude "qed_dcbx.h"
#incwude "qed_dev_api.h"
#incwude <winux/qed/qed_eth_if.h>
#incwude "qed_hsi.h"
#incwude "qed_iwo_hsi.h"
#incwude "qed_hw.h"
#incwude "qed_int.h"
#incwude "qed_w2.h"
#incwude "qed_mcp.h"
#incwude "qed_ptp.h"
#incwude "qed_weg_addw.h"
#incwude "qed_sp.h"
#incwude "qed_swiov.h"

#define QED_MAX_SGES_NUM 16
#define CWC32_POWY 0x1edc6f41

stwuct qed_w2_info {
	u32 queues;
	unsigned wong **pp_qid_usage;

	/* The wock is meant to synchwonize access to the qid usage */
	stwuct mutex wock;
};

int qed_w2_awwoc(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_w2_info *p_w2_info;
	unsigned wong **pp_qids;
	u32 i;

	if (!QED_IS_W2_PEWSONAWITY(p_hwfn))
		wetuwn 0;

	p_w2_info = kzawwoc(sizeof(*p_w2_info), GFP_KEWNEW);
	if (!p_w2_info)
		wetuwn -ENOMEM;
	p_hwfn->p_w2_info = p_w2_info;

	if (IS_PF(p_hwfn->cdev)) {
		p_w2_info->queues = WESC_NUM(p_hwfn, QED_W2_QUEUE);
	} ewse {
		u8 wx = 0, tx = 0;

		qed_vf_get_num_wxqs(p_hwfn, &wx);
		qed_vf_get_num_txqs(p_hwfn, &tx);

		p_w2_info->queues = max_t(u8, wx, tx);
	}

	pp_qids = kcawwoc(p_w2_info->queues, sizeof(unsigned wong *),
			  GFP_KEWNEW);
	if (!pp_qids)
		wetuwn -ENOMEM;
	p_w2_info->pp_qid_usage = pp_qids;

	fow (i = 0; i < p_w2_info->queues; i++) {
		pp_qids[i] = kzawwoc(MAX_QUEUES_PEW_QZONE / 8, GFP_KEWNEW);
		if (!pp_qids[i])
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

void qed_w2_setup(stwuct qed_hwfn *p_hwfn)
{
	if (!QED_IS_W2_PEWSONAWITY(p_hwfn))
		wetuwn;

	mutex_init(&p_hwfn->p_w2_info->wock);
}

void qed_w2_fwee(stwuct qed_hwfn *p_hwfn)
{
	u32 i;

	if (!QED_IS_W2_PEWSONAWITY(p_hwfn))
		wetuwn;

	if (!p_hwfn->p_w2_info)
		wetuwn;

	if (!p_hwfn->p_w2_info->pp_qid_usage)
		goto out_w2_info;

	/* Fwee untiw hit fiwst uninitiawized entwy */
	fow (i = 0; i < p_hwfn->p_w2_info->queues; i++) {
		if (!p_hwfn->p_w2_info->pp_qid_usage[i])
			bweak;
		kfwee(p_hwfn->p_w2_info->pp_qid_usage[i]);
	}

	kfwee(p_hwfn->p_w2_info->pp_qid_usage);

out_w2_info:
	kfwee(p_hwfn->p_w2_info);
	p_hwfn->p_w2_info = NUWW;
}

static boow qed_eth_queue_qid_usage_add(stwuct qed_hwfn *p_hwfn,
					stwuct qed_queue_cid *p_cid)
{
	stwuct qed_w2_info *p_w2_info = p_hwfn->p_w2_info;
	u16 queue_id = p_cid->wew.queue_id;
	boow b_wc = twue;
	u8 fiwst;

	mutex_wock(&p_w2_info->wock);

	if (queue_id >= p_w2_info->queues) {
		DP_NOTICE(p_hwfn,
			  "Wequested to incwease usage fow qzone %04x out of %08x\n",
			  queue_id, p_w2_info->queues);
		b_wc = fawse;
		goto out;
	}

	fiwst = (u8)find_fiwst_zewo_bit(p_w2_info->pp_qid_usage[queue_id],
					MAX_QUEUES_PEW_QZONE);
	if (fiwst >= MAX_QUEUES_PEW_QZONE) {
		b_wc = fawse;
		goto out;
	}

	__set_bit(fiwst, p_w2_info->pp_qid_usage[queue_id]);
	p_cid->qid_usage_idx = fiwst;

out:
	mutex_unwock(&p_w2_info->wock);
	wetuwn b_wc;
}

static void qed_eth_queue_qid_usage_dew(stwuct qed_hwfn *p_hwfn,
					stwuct qed_queue_cid *p_cid)
{
	mutex_wock(&p_hwfn->p_w2_info->wock);

	cweaw_bit(p_cid->qid_usage_idx,
		  p_hwfn->p_w2_info->pp_qid_usage[p_cid->wew.queue_id]);

	mutex_unwock(&p_hwfn->p_w2_info->wock);
}

void qed_eth_queue_cid_wewease(stwuct qed_hwfn *p_hwfn,
			       stwuct qed_queue_cid *p_cid)
{
	boow b_wegacy_vf = !!(p_cid->vf_wegacy & QED_QCID_WEGACY_VF_CID);

	if (IS_PF(p_hwfn->cdev) && !b_wegacy_vf)
		_qed_cxt_wewease_cid(p_hwfn, p_cid->cid, p_cid->vfid);

	/* Fow PF's VFs we maintain the index inside queue-zone in IOV */
	if (p_cid->vfid == QED_QUEUE_CID_SEWF)
		qed_eth_queue_qid_usage_dew(p_hwfn, p_cid);

	vfwee(p_cid);
}

/* The intewnaw is onwy meant to be diwectwy cawwed by PFs initiawizeing CIDs
 * fow theiw VFs.
 */
static stwuct qed_queue_cid *
_qed_eth_queue_to_cid(stwuct qed_hwfn *p_hwfn,
		      u16 opaque_fid,
		      u32 cid,
		      stwuct qed_queue_stawt_common_pawams *p_pawams,
		      boow b_is_wx,
		      stwuct qed_queue_cid_vf_pawams *p_vf_pawams)
{
	stwuct qed_queue_cid *p_cid;
	int wc;

	p_cid = vzawwoc(sizeof(*p_cid));
	if (!p_cid)
		wetuwn NUWW;

	p_cid->opaque_fid = opaque_fid;
	p_cid->cid = cid;
	p_cid->p_ownew = p_hwfn;

	/* Fiww in pawametews */
	p_cid->wew.vpowt_id = p_pawams->vpowt_id;
	p_cid->wew.queue_id = p_pawams->queue_id;
	p_cid->wew.stats_id = p_pawams->stats_id;
	p_cid->sb_igu_id = p_pawams->p_sb->igu_sb_id;
	p_cid->b_is_wx = b_is_wx;
	p_cid->sb_idx = p_pawams->sb_idx;

	/* Fiww-in bits wewated to VFs' queues if infowmation was pwovided */
	if (p_vf_pawams) {
		p_cid->vfid = p_vf_pawams->vfid;
		p_cid->vf_qid = p_vf_pawams->vf_qid;
		p_cid->vf_wegacy = p_vf_pawams->vf_wegacy;
	} ewse {
		p_cid->vfid = QED_QUEUE_CID_SEWF;
	}

	/* Don't twy cawcuwating the absowute indices fow VFs */
	if (IS_VF(p_hwfn->cdev)) {
		p_cid->abs = p_cid->wew;
		goto out;
	}

	/* Cawcuwate the engine-absowute indices of the wesouwces.
	 * This wouwd guawantee they'we vawid watew on.
	 * In some cases [SBs] we awweady have the wight vawues.
	 */
	wc = qed_fw_vpowt(p_hwfn, p_cid->wew.vpowt_id, &p_cid->abs.vpowt_id);
	if (wc)
		goto faiw;

	wc = qed_fw_w2_queue(p_hwfn, p_cid->wew.queue_id, &p_cid->abs.queue_id);
	if (wc)
		goto faiw;

	/* In case of a PF configuwing its VF's queues, the stats-id is awweady
	 * absowute [since thewe's a singwe index that's suitabwe pew-VF].
	 */
	if (p_cid->vfid == QED_QUEUE_CID_SEWF) {
		wc = qed_fw_vpowt(p_hwfn, p_cid->wew.stats_id,
				  &p_cid->abs.stats_id);
		if (wc)
			goto faiw;
	} ewse {
		p_cid->abs.stats_id = p_cid->wew.stats_id;
	}

out:
	/* VF-images have pwovided the qid_usage_idx on theiw own.
	 * Othewwise, we need to awwocate a unique one.
	 */
	if (!p_vf_pawams) {
		if (!qed_eth_queue_qid_usage_add(p_hwfn, p_cid))
			goto faiw;
	} ewse {
		p_cid->qid_usage_idx = p_vf_pawams->qid_usage_idx;
	}

	DP_VEWBOSE(p_hwfn,
		   QED_MSG_SP,
		   "opaque_fid: %04x CID %08x vpowt %02x [%02x] qzone %04x.%02x [%04x] stats %02x [%02x] SB %04x PI %02x\n",
		   p_cid->opaque_fid,
		   p_cid->cid,
		   p_cid->wew.vpowt_id,
		   p_cid->abs.vpowt_id,
		   p_cid->wew.queue_id,
		   p_cid->qid_usage_idx,
		   p_cid->abs.queue_id,
		   p_cid->wew.stats_id,
		   p_cid->abs.stats_id, p_cid->sb_igu_id, p_cid->sb_idx);

	wetuwn p_cid;

faiw:
	vfwee(p_cid);
	wetuwn NUWW;
}

stwuct qed_queue_cid *
qed_eth_queue_to_cid(stwuct qed_hwfn *p_hwfn,
		     u16 opaque_fid,
		     stwuct qed_queue_stawt_common_pawams *p_pawams,
		     boow b_is_wx,
		     stwuct qed_queue_cid_vf_pawams *p_vf_pawams)
{
	stwuct qed_queue_cid *p_cid;
	u8 vfid = QED_CXT_PF_CID;
	boow b_wegacy_vf = fawse;
	u32 cid = 0;

	/* In case of wegacy VFs, The CID can be dewived fwom the additionaw
	 * VF pawametews - the VF assumes queue X uses CID X, so we can simpwy
	 * use the vf_qid fow this puwpose as weww.
	 */
	if (p_vf_pawams) {
		vfid = p_vf_pawams->vfid;

		if (p_vf_pawams->vf_wegacy & QED_QCID_WEGACY_VF_CID) {
			b_wegacy_vf = twue;
			cid = p_vf_pawams->vf_qid;
		}
	}

	/* Get a unique fiwmwawe CID fow this queue, in case it's a PF.
	 * VF's don't need a CID as the queue configuwation wiww be done
	 * by PF.
	 */
	if (IS_PF(p_hwfn->cdev) && !b_wegacy_vf) {
		if (_qed_cxt_acquiwe_cid(p_hwfn, PWOTOCOWID_ETH,
					 &cid, vfid)) {
			DP_NOTICE(p_hwfn, "Faiwed to acquiwe cid\n");
			wetuwn NUWW;
		}
	}

	p_cid = _qed_eth_queue_to_cid(p_hwfn, opaque_fid, cid,
				      p_pawams, b_is_wx, p_vf_pawams);
	if (!p_cid && IS_PF(p_hwfn->cdev) && !b_wegacy_vf)
		_qed_cxt_wewease_cid(p_hwfn, cid, vfid);

	wetuwn p_cid;
}

static stwuct qed_queue_cid *
qed_eth_queue_to_cid_pf(stwuct qed_hwfn *p_hwfn,
			u16 opaque_fid,
			boow b_is_wx,
			stwuct qed_queue_stawt_common_pawams *p_pawams)
{
	wetuwn qed_eth_queue_to_cid(p_hwfn, opaque_fid, p_pawams, b_is_wx,
				    NUWW);
}

int qed_sp_eth_vpowt_stawt(stwuct qed_hwfn *p_hwfn,
			   stwuct qed_sp_vpowt_stawt_pawams *p_pawams)
{
	stwuct vpowt_stawt_wamwod_data *p_wamwod = NUWW;
	stwuct eth_vpowt_tpa_pawam *tpa_pawam;
	stwuct qed_spq_entwy *p_ent =  NUWW;
	stwuct qed_sp_init_data init_data;
	u16 min_size, wx_mode = 0;
	u8 abs_vpowt_id = 0;
	int wc;

	wc = qed_fw_vpowt(p_hwfn, p_pawams->vpowt_id, &abs_vpowt_id);
	if (wc)
		wetuwn wc;

	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_pawams->opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 ETH_WAMWOD_VPOWT_STAWT,
				 PWOTOCOWID_ETH, &init_data);
	if (wc)
		wetuwn wc;

	p_wamwod		= &p_ent->wamwod.vpowt_stawt;
	p_wamwod->vpowt_id	= abs_vpowt_id;

	p_wamwod->mtu			= cpu_to_we16(p_pawams->mtu);
	p_wamwod->handwe_ptp_pkts	= p_pawams->handwe_ptp_pkts;
	p_wamwod->innew_vwan_wemovaw_en	= p_pawams->wemove_innew_vwan;
	p_wamwod->dwop_ttw0_en		= p_pawams->dwop_ttw0;
	p_wamwod->untagged		= p_pawams->onwy_untagged;

	SET_FIEWD(wx_mode, ETH_VPOWT_WX_MODE_UCAST_DWOP_AWW, 1);
	SET_FIEWD(wx_mode, ETH_VPOWT_WX_MODE_MCAST_DWOP_AWW, 1);

	p_wamwod->wx_mode.state = cpu_to_we16(wx_mode);

	/* TPA wewated fiewds */
	tpa_pawam = &p_wamwod->tpa_pawam;
	memset(tpa_pawam, 0, sizeof(*tpa_pawam));

	tpa_pawam->max_buff_num = p_pawams->max_buffews_pew_cqe;

	switch (p_pawams->tpa_mode) {
	case QED_TPA_MODE_GWO:
		min_size = p_pawams->mtu / 2;

		tpa_pawam->tpa_max_aggs_num = ETH_TPA_MAX_AGGS_NUM;
		tpa_pawam->tpa_max_size = cpu_to_we16(U16_MAX);
		tpa_pawam->tpa_min_size_to_cont = cpu_to_we16(min_size);
		tpa_pawam->tpa_min_size_to_stawt = cpu_to_we16(min_size);
		tpa_pawam->tpa_ipv4_en_fwg = 1;
		tpa_pawam->tpa_ipv6_en_fwg = 1;
		tpa_pawam->tpa_pkt_spwit_fwg = 1;
		tpa_pawam->tpa_gwo_consistent_fwg = 1;
		bweak;
	defauwt:
		bweak;
	}

	p_wamwod->tx_switching_en = p_pawams->tx_switching;

	p_wamwod->ctw_fwame_mac_check_en = !!p_pawams->check_mac;
	p_wamwod->ctw_fwame_ethtype_check_en = !!p_pawams->check_ethtype;

	/* Softwawe Function ID in hwfn (PFs awe 0 - 15, VFs awe 16 - 135) */
	p_wamwod->sw_fid = qed_concwete_to_sw_fid(p_hwfn->cdev,
						  p_pawams->concwete_fid);

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}

static int qed_sp_vpowt_stawt(stwuct qed_hwfn *p_hwfn,
			      stwuct qed_sp_vpowt_stawt_pawams *p_pawams)
{
	if (IS_VF(p_hwfn->cdev)) {
		wetuwn qed_vf_pf_vpowt_stawt(p_hwfn, p_pawams->vpowt_id,
					     p_pawams->mtu,
					     p_pawams->wemove_innew_vwan,
					     p_pawams->tpa_mode,
					     p_pawams->max_buffews_pew_cqe,
					     p_pawams->onwy_untagged);
	}

	wetuwn qed_sp_eth_vpowt_stawt(p_hwfn, p_pawams);
}

static int
qed_sp_vpowt_update_wss(stwuct qed_hwfn *p_hwfn,
			stwuct vpowt_update_wamwod_data *p_wamwod,
			stwuct qed_wss_pawams *p_wss)
{
	stwuct eth_vpowt_wss_config *p_config;
	u16 capabiwities = 0;
	int i, tabwe_size;
	int wc = 0;

	if (!p_wss) {
		p_wamwod->common.update_wss_fwg = 0;
		wetuwn wc;
	}
	p_config = &p_wamwod->wss_config;

	BUIWD_BUG_ON(QED_WSS_IND_TABWE_SIZE != ETH_WSS_IND_TABWE_ENTWIES_NUM);

	wc = qed_fw_wss_eng(p_hwfn, p_wss->wss_eng_id, &p_config->wss_id);
	if (wc)
		wetuwn wc;

	p_wamwod->common.update_wss_fwg = p_wss->update_wss_config;
	p_config->update_wss_capabiwities = p_wss->update_wss_capabiwities;
	p_config->update_wss_ind_tabwe = p_wss->update_wss_ind_tabwe;
	p_config->update_wss_key = p_wss->update_wss_key;

	p_config->wss_mode = p_wss->wss_enabwe ?
			     ETH_VPOWT_WSS_MODE_WEGUWAW :
			     ETH_VPOWT_WSS_MODE_DISABWED;

	SET_FIEWD(capabiwities,
		  ETH_VPOWT_WSS_CONFIG_IPV4_CAPABIWITY,
		  !!(p_wss->wss_caps & QED_WSS_IPV4));
	SET_FIEWD(capabiwities,
		  ETH_VPOWT_WSS_CONFIG_IPV6_CAPABIWITY,
		  !!(p_wss->wss_caps & QED_WSS_IPV6));
	SET_FIEWD(capabiwities,
		  ETH_VPOWT_WSS_CONFIG_IPV4_TCP_CAPABIWITY,
		  !!(p_wss->wss_caps & QED_WSS_IPV4_TCP));
	SET_FIEWD(capabiwities,
		  ETH_VPOWT_WSS_CONFIG_IPV6_TCP_CAPABIWITY,
		  !!(p_wss->wss_caps & QED_WSS_IPV6_TCP));
	SET_FIEWD(capabiwities,
		  ETH_VPOWT_WSS_CONFIG_IPV4_UDP_CAPABIWITY,
		  !!(p_wss->wss_caps & QED_WSS_IPV4_UDP));
	SET_FIEWD(capabiwities,
		  ETH_VPOWT_WSS_CONFIG_IPV6_UDP_CAPABIWITY,
		  !!(p_wss->wss_caps & QED_WSS_IPV6_UDP));
	p_config->tbw_size = p_wss->wss_tabwe_size_wog;

	p_config->capabiwities = cpu_to_we16(capabiwities);

	DP_VEWBOSE(p_hwfn, NETIF_MSG_IFUP,
		   "update wss fwag %d, wss_mode = %d, update_caps = %d, capabiwities = %d, update_ind = %d, update_wss_key = %d\n",
		   p_wamwod->common.update_wss_fwg,
		   p_config->wss_mode,
		   p_config->update_wss_capabiwities,
		   p_config->capabiwities,
		   p_config->update_wss_ind_tabwe, p_config->update_wss_key);

	tabwe_size = min_t(int, QED_WSS_IND_TABWE_SIZE,
			   1 << p_config->tbw_size);
	fow (i = 0; i < tabwe_size; i++) {
		stwuct qed_queue_cid *p_queue = p_wss->wss_ind_tabwe[i];

		if (!p_queue)
			wetuwn -EINVAW;

		p_config->indiwection_tabwe[i] =
		    cpu_to_we16(p_queue->abs.queue_id);
	}

	DP_VEWBOSE(p_hwfn, NETIF_MSG_IFUP,
		   "Configuwed WSS indiwection tabwe [%d entwies]:\n",
		   tabwe_size);
	fow (i = 0; i < QED_WSS_IND_TABWE_SIZE; i += 0x10) {
		DP_VEWBOSE(p_hwfn,
			   NETIF_MSG_IFUP,
			   "%04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x\n",
			   we16_to_cpu(p_config->indiwection_tabwe[i]),
			   we16_to_cpu(p_config->indiwection_tabwe[i + 1]),
			   we16_to_cpu(p_config->indiwection_tabwe[i + 2]),
			   we16_to_cpu(p_config->indiwection_tabwe[i + 3]),
			   we16_to_cpu(p_config->indiwection_tabwe[i + 4]),
			   we16_to_cpu(p_config->indiwection_tabwe[i + 5]),
			   we16_to_cpu(p_config->indiwection_tabwe[i + 6]),
			   we16_to_cpu(p_config->indiwection_tabwe[i + 7]),
			   we16_to_cpu(p_config->indiwection_tabwe[i + 8]),
			   we16_to_cpu(p_config->indiwection_tabwe[i + 9]),
			   we16_to_cpu(p_config->indiwection_tabwe[i + 10]),
			   we16_to_cpu(p_config->indiwection_tabwe[i + 11]),
			   we16_to_cpu(p_config->indiwection_tabwe[i + 12]),
			   we16_to_cpu(p_config->indiwection_tabwe[i + 13]),
			   we16_to_cpu(p_config->indiwection_tabwe[i + 14]),
			   we16_to_cpu(p_config->indiwection_tabwe[i + 15]));
	}

	fow (i = 0; i < 10; i++)
		p_config->wss_key[i] = cpu_to_we32(p_wss->wss_key[i]);

	wetuwn wc;
}

static void
qed_sp_update_accept_mode(stwuct qed_hwfn *p_hwfn,
			  stwuct vpowt_update_wamwod_data *p_wamwod,
			  stwuct qed_fiwtew_accept_fwags accept_fwags)
{
	p_wamwod->common.update_wx_mode_fwg =
		accept_fwags.update_wx_mode_config;

	p_wamwod->common.update_tx_mode_fwg =
		accept_fwags.update_tx_mode_config;

	/* Set Wx mode accept fwags */
	if (p_wamwod->common.update_wx_mode_fwg) {
		u8 accept_fiwtew = accept_fwags.wx_accept_fiwtew;
		u16 state = 0;

		SET_FIEWD(state, ETH_VPOWT_WX_MODE_UCAST_DWOP_AWW,
			  !(!!(accept_fiwtew & QED_ACCEPT_UCAST_MATCHED) ||
			    !!(accept_fiwtew & QED_ACCEPT_UCAST_UNMATCHED)));

		SET_FIEWD(state, ETH_VPOWT_WX_MODE_UCAST_ACCEPT_UNMATCHED,
			  !!(accept_fiwtew & QED_ACCEPT_UCAST_UNMATCHED));

		SET_FIEWD(state, ETH_VPOWT_WX_MODE_MCAST_DWOP_AWW,
			  !(!!(accept_fiwtew & QED_ACCEPT_MCAST_MATCHED) ||
			    !!(accept_fiwtew & QED_ACCEPT_MCAST_UNMATCHED)));

		SET_FIEWD(state, ETH_VPOWT_WX_MODE_MCAST_ACCEPT_AWW,
			  (!!(accept_fiwtew & QED_ACCEPT_MCAST_MATCHED) &&
			   !!(accept_fiwtew & QED_ACCEPT_MCAST_UNMATCHED)));

		SET_FIEWD(state, ETH_VPOWT_WX_MODE_BCAST_ACCEPT_AWW,
			  !!(accept_fiwtew & QED_ACCEPT_BCAST));

		SET_FIEWD(state, ETH_VPOWT_WX_MODE_ACCEPT_ANY_VNI,
			  !!(accept_fiwtew & QED_ACCEPT_ANY_VNI));

		p_wamwod->wx_mode.state = cpu_to_we16(state);
		DP_VEWBOSE(p_hwfn, QED_MSG_SP,
			   "p_wamwod->wx_mode.state = 0x%x\n", state);
	}

	/* Set Tx mode accept fwags */
	if (p_wamwod->common.update_tx_mode_fwg) {
		u8 accept_fiwtew = accept_fwags.tx_accept_fiwtew;
		u16 state = 0;

		SET_FIEWD(state, ETH_VPOWT_TX_MODE_UCAST_DWOP_AWW,
			  !!(accept_fiwtew & QED_ACCEPT_NONE));

		SET_FIEWD(state, ETH_VPOWT_TX_MODE_MCAST_DWOP_AWW,
			  !!(accept_fiwtew & QED_ACCEPT_NONE));

		SET_FIEWD(state, ETH_VPOWT_TX_MODE_MCAST_ACCEPT_AWW,
			  (!!(accept_fiwtew & QED_ACCEPT_MCAST_MATCHED) &&
			   !!(accept_fiwtew & QED_ACCEPT_MCAST_UNMATCHED)));

		SET_FIEWD(state, ETH_VPOWT_TX_MODE_UCAST_ACCEPT_AWW,
			  (!!(accept_fiwtew & QED_ACCEPT_UCAST_MATCHED) &&
			   !!(accept_fiwtew & QED_ACCEPT_UCAST_UNMATCHED)));

		SET_FIEWD(state, ETH_VPOWT_TX_MODE_BCAST_ACCEPT_AWW,
			  !!(accept_fiwtew & QED_ACCEPT_BCAST));

		p_wamwod->tx_mode.state = cpu_to_we16(state);
		DP_VEWBOSE(p_hwfn, QED_MSG_SP,
			   "p_wamwod->tx_mode.state = 0x%x\n", state);
	}
}

static void
qed_sp_vpowt_update_sge_tpa(stwuct qed_hwfn *p_hwfn,
			    stwuct vpowt_update_wamwod_data *p_wamwod,
			    const stwuct qed_sge_tpa_pawams *pawam)
{
	stwuct eth_vpowt_tpa_pawam *tpa;

	if (!pawam) {
		p_wamwod->common.update_tpa_pawam_fwg = 0;
		p_wamwod->common.update_tpa_en_fwg = 0;
		p_wamwod->common.update_tpa_pawam_fwg = 0;
		wetuwn;
	}

	p_wamwod->common.update_tpa_en_fwg = pawam->update_tpa_en_fwg;
	tpa = &p_wamwod->tpa_pawam;
	tpa->tpa_ipv4_en_fwg = pawam->tpa_ipv4_en_fwg;
	tpa->tpa_ipv6_en_fwg = pawam->tpa_ipv6_en_fwg;
	tpa->tpa_ipv4_tunn_en_fwg = pawam->tpa_ipv4_tunn_en_fwg;
	tpa->tpa_ipv6_tunn_en_fwg = pawam->tpa_ipv6_tunn_en_fwg;

	p_wamwod->common.update_tpa_pawam_fwg = pawam->update_tpa_pawam_fwg;
	tpa->max_buff_num = pawam->max_buffews_pew_cqe;
	tpa->tpa_pkt_spwit_fwg = pawam->tpa_pkt_spwit_fwg;
	tpa->tpa_hdw_data_spwit_fwg = pawam->tpa_hdw_data_spwit_fwg;
	tpa->tpa_gwo_consistent_fwg = pawam->tpa_gwo_consistent_fwg;
	tpa->tpa_max_aggs_num = pawam->tpa_max_aggs_num;
	tpa->tpa_max_size = cpu_to_we16(pawam->tpa_max_size);
	tpa->tpa_min_size_to_stawt = cpu_to_we16(pawam->tpa_min_size_to_stawt);
	tpa->tpa_min_size_to_cont = cpu_to_we16(pawam->tpa_min_size_to_cont);
}

static void
qed_sp_update_mcast_bin(stwuct qed_hwfn *p_hwfn,
			stwuct vpowt_update_wamwod_data *p_wamwod,
			stwuct qed_sp_vpowt_update_pawams *p_pawams)
{
	int i;

	memset(&p_wamwod->appwox_mcast.bins, 0,
	       sizeof(p_wamwod->appwox_mcast.bins));

	if (!p_pawams->update_appwox_mcast_fwg)
		wetuwn;

	p_wamwod->common.update_appwox_mcast_fwg = 1;
	fow (i = 0; i < ETH_MUWTICAST_MAC_BINS_IN_WEGS; i++) {
		u32 *p_bins = p_pawams->bins;

		p_wamwod->appwox_mcast.bins[i] = cpu_to_we32(p_bins[i]);
	}
}

int qed_sp_vpowt_update(stwuct qed_hwfn *p_hwfn,
			stwuct qed_sp_vpowt_update_pawams *p_pawams,
			enum spq_mode comp_mode,
			stwuct qed_spq_comp_cb *p_comp_data)
{
	stwuct qed_wss_pawams *p_wss_pawams = p_pawams->wss_pawams;
	stwuct vpowt_update_wamwod_data_cmn *p_cmn;
	stwuct qed_sp_init_data init_data;
	stwuct vpowt_update_wamwod_data *p_wamwod = NUWW;
	stwuct qed_spq_entwy *p_ent = NUWW;
	u8 abs_vpowt_id = 0, vaw;
	int wc = -EINVAW;

	if (IS_VF(p_hwfn->cdev)) {
		wc = qed_vf_pf_vpowt_update(p_hwfn, p_pawams);
		wetuwn wc;
	}

	wc = qed_fw_vpowt(p_hwfn, p_pawams->vpowt_id, &abs_vpowt_id);
	if (wc)
		wetuwn wc;

	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_pawams->opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_data;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 ETH_WAMWOD_VPOWT_UPDATE,
				 PWOTOCOWID_ETH, &init_data);
	if (wc)
		wetuwn wc;

	/* Copy input pawams to wamwod accowding to FW stwuct */
	p_wamwod = &p_ent->wamwod.vpowt_update;
	p_cmn = &p_wamwod->common;

	p_cmn->vpowt_id = abs_vpowt_id;
	p_cmn->wx_active_fwg = p_pawams->vpowt_active_wx_fwg;
	p_cmn->update_wx_active_fwg = p_pawams->update_vpowt_active_wx_fwg;
	p_cmn->tx_active_fwg = p_pawams->vpowt_active_tx_fwg;
	p_cmn->update_tx_active_fwg = p_pawams->update_vpowt_active_tx_fwg;
	p_cmn->accept_any_vwan = p_pawams->accept_any_vwan;
	vaw = p_pawams->update_accept_any_vwan_fwg;
	p_cmn->update_accept_any_vwan_fwg = vaw;

	p_cmn->innew_vwan_wemovaw_en = p_pawams->innew_vwan_wemovaw_fwg;
	vaw = p_pawams->update_innew_vwan_wemovaw_fwg;
	p_cmn->update_innew_vwan_wemovaw_en_fwg = vaw;

	p_cmn->defauwt_vwan_en = p_pawams->defauwt_vwan_enabwe_fwg;
	vaw = p_pawams->update_defauwt_vwan_enabwe_fwg;
	p_cmn->update_defauwt_vwan_en_fwg = vaw;

	p_cmn->defauwt_vwan = cpu_to_we16(p_pawams->defauwt_vwan);
	p_cmn->update_defauwt_vwan_fwg = p_pawams->update_defauwt_vwan_fwg;

	p_cmn->siwent_vwan_wemovaw_en = p_pawams->siwent_vwan_wemovaw_fwg;

	p_wamwod->common.tx_switching_en = p_pawams->tx_switching_fwg;
	p_cmn->update_tx_switching_en_fwg = p_pawams->update_tx_switching_fwg;

	p_cmn->anti_spoofing_en = p_pawams->anti_spoofing_en;
	vaw = p_pawams->update_anti_spoofing_en_fwg;
	p_wamwod->common.update_anti_spoofing_en_fwg = vaw;

	wc = qed_sp_vpowt_update_wss(p_hwfn, p_wamwod, p_wss_pawams);
	if (wc) {
		qed_sp_destwoy_wequest(p_hwfn, p_ent);
		wetuwn wc;
	}

	if (p_pawams->update_ctw_fwame_check) {
		p_cmn->ctw_fwame_mac_check_en = p_pawams->mac_chk_en;
		p_cmn->ctw_fwame_ethtype_check_en = p_pawams->ethtype_chk_en;
	}

	/* Update mcast bins fow VFs, PF doesn't use this functionawity */
	qed_sp_update_mcast_bin(p_hwfn, p_wamwod, p_pawams);

	qed_sp_update_accept_mode(p_hwfn, p_wamwod, p_pawams->accept_fwags);
	qed_sp_vpowt_update_sge_tpa(p_hwfn, p_wamwod, p_pawams->sge_tpa_pawams);
	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}

int qed_sp_vpowt_stop(stwuct qed_hwfn *p_hwfn, u16 opaque_fid, u8 vpowt_id)
{
	stwuct vpowt_stop_wamwod_data *p_wamwod;
	stwuct qed_sp_init_data init_data;
	stwuct qed_spq_entwy *p_ent;
	u8 abs_vpowt_id = 0;
	int wc;

	if (IS_VF(p_hwfn->cdev))
		wetuwn qed_vf_pf_vpowt_stop(p_hwfn);

	wc = qed_fw_vpowt(p_hwfn, vpowt_id, &abs_vpowt_id);
	if (wc)
		wetuwn wc;

	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 ETH_WAMWOD_VPOWT_STOP,
				 PWOTOCOWID_ETH, &init_data);
	if (wc)
		wetuwn wc;

	p_wamwod = &p_ent->wamwod.vpowt_stop;
	p_wamwod->vpowt_id = abs_vpowt_id;

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}

static int
qed_vf_pf_accept_fwags(stwuct qed_hwfn *p_hwfn,
		       stwuct qed_fiwtew_accept_fwags *p_accept_fwags)
{
	stwuct qed_sp_vpowt_update_pawams s_pawams;

	memset(&s_pawams, 0, sizeof(s_pawams));
	memcpy(&s_pawams.accept_fwags, p_accept_fwags,
	       sizeof(stwuct qed_fiwtew_accept_fwags));

	wetuwn qed_vf_pf_vpowt_update(p_hwfn, &s_pawams);
}

static int qed_fiwtew_accept_cmd(stwuct qed_dev *cdev,
				 u8 vpowt,
				 stwuct qed_fiwtew_accept_fwags accept_fwags,
				 u8 update_accept_any_vwan,
				 u8 accept_any_vwan,
				 enum spq_mode comp_mode,
				 stwuct qed_spq_comp_cb *p_comp_data)
{
	stwuct qed_sp_vpowt_update_pawams vpowt_update_pawams;
	int i, wc;

	/* Pwepawe and send the vpowt wx_mode change */
	memset(&vpowt_update_pawams, 0, sizeof(vpowt_update_pawams));
	vpowt_update_pawams.vpowt_id = vpowt;
	vpowt_update_pawams.accept_fwags = accept_fwags;
	vpowt_update_pawams.update_accept_any_vwan_fwg = update_accept_any_vwan;
	vpowt_update_pawams.accept_any_vwan = accept_any_vwan;

	fow_each_hwfn(cdev, i) {
		stwuct qed_hwfn *p_hwfn = &cdev->hwfns[i];

		vpowt_update_pawams.opaque_fid = p_hwfn->hw_info.opaque_fid;

		if (IS_VF(cdev)) {
			wc = qed_vf_pf_accept_fwags(p_hwfn, &accept_fwags);
			if (wc)
				wetuwn wc;
			continue;
		}

		wc = qed_sp_vpowt_update(p_hwfn, &vpowt_update_pawams,
					 comp_mode, p_comp_data);
		if (wc) {
			DP_EWW(cdev, "Update wx_mode faiwed %d\n", wc);
			wetuwn wc;
		}

		DP_VEWBOSE(p_hwfn, QED_MSG_SP,
			   "Accept fiwtew configuwed, fwags = [Wx]%x [Tx]%x\n",
			   accept_fwags.wx_accept_fiwtew,
			   accept_fwags.tx_accept_fiwtew);
		if (update_accept_any_vwan)
			DP_VEWBOSE(p_hwfn, QED_MSG_SP,
				   "accept_any_vwan=%d configuwed\n",
				   accept_any_vwan);
	}

	wetuwn 0;
}

int qed_eth_wxq_stawt_wamwod(stwuct qed_hwfn *p_hwfn,
			     stwuct qed_queue_cid *p_cid,
			     u16 bd_max_bytes,
			     dma_addw_t bd_chain_phys_addw,
			     dma_addw_t cqe_pbw_addw, u16 cqe_pbw_size)
{
	stwuct wx_queue_stawt_wamwod_data *p_wamwod = NUWW;
	stwuct qed_spq_entwy *p_ent = NUWW;
	stwuct qed_sp_init_data init_data;
	int wc = -EINVAW;

	DP_VEWBOSE(p_hwfn, QED_MSG_SP,
		   "opaque_fid=0x%x, cid=0x%x, wx_qzone=0x%x, vpowt_id=0x%x, sb_id=0x%x\n",
		   p_cid->opaque_fid, p_cid->cid,
		   p_cid->abs.queue_id, p_cid->abs.vpowt_id, p_cid->sb_igu_id);

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = p_cid->cid;
	init_data.opaque_fid = p_cid->opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 ETH_WAMWOD_WX_QUEUE_STAWT,
				 PWOTOCOWID_ETH, &init_data);
	if (wc)
		wetuwn wc;

	p_wamwod = &p_ent->wamwod.wx_queue_stawt;

	p_wamwod->sb_id = cpu_to_we16(p_cid->sb_igu_id);
	p_wamwod->sb_index = p_cid->sb_idx;
	p_wamwod->vpowt_id = p_cid->abs.vpowt_id;
	p_wamwod->stats_countew_id = p_cid->abs.stats_id;
	p_wamwod->wx_queue_id = cpu_to_we16(p_cid->abs.queue_id);
	p_wamwod->compwete_cqe_fwg = 0;
	p_wamwod->compwete_event_fwg = 1;

	p_wamwod->bd_max_bytes = cpu_to_we16(bd_max_bytes);
	DMA_WEGPAIW_WE(p_wamwod->bd_base, bd_chain_phys_addw);

	p_wamwod->num_of_pbw_pages = cpu_to_we16(cqe_pbw_size);
	DMA_WEGPAIW_WE(p_wamwod->cqe_pbw_addw, cqe_pbw_addw);

	if (p_cid->vfid != QED_QUEUE_CID_SEWF) {
		boow b_wegacy_vf = !!(p_cid->vf_wegacy &
				      QED_QCID_WEGACY_VF_WX_PWOD);

		p_wamwod->vf_wx_pwod_index = p_cid->vf_qid;
		DP_VEWBOSE(p_hwfn, QED_MSG_SP,
			   "Queue%s is meant fow VF wxq[%02x]\n",
			   b_wegacy_vf ? " [wegacy]" : "", p_cid->vf_qid);
		p_wamwod->vf_wx_pwod_use_zone_a = b_wegacy_vf;
	}

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}

static int
qed_eth_pf_wx_queue_stawt(stwuct qed_hwfn *p_hwfn,
			  stwuct qed_queue_cid *p_cid,
			  u16 bd_max_bytes,
			  dma_addw_t bd_chain_phys_addw,
			  dma_addw_t cqe_pbw_addw,
			  u16 cqe_pbw_size, void __iomem **pp_pwod)
{
	u32 init_pwod_vaw = 0;

	*pp_pwod = (u8 __iomem *)
	    p_hwfn->wegview +
	    GET_GTT_WEG_ADDW(GTT_BAW0_MAP_WEG_MSDM_WAM,
			     MSTOWM_ETH_PF_PWODS, p_cid->abs.queue_id);

	/* Init the wcq, wx bd and wx sge (if vawid) pwoducews to 0 */
	__intewnaw_wam_ww(p_hwfn, *pp_pwod, sizeof(u32),
			  (u32 *)(&init_pwod_vaw));

	wetuwn qed_eth_wxq_stawt_wamwod(p_hwfn, p_cid,
					bd_max_bytes,
					bd_chain_phys_addw,
					cqe_pbw_addw, cqe_pbw_size);
}

static int
qed_eth_wx_queue_stawt(stwuct qed_hwfn *p_hwfn,
		       u16 opaque_fid,
		       stwuct qed_queue_stawt_common_pawams *p_pawams,
		       u16 bd_max_bytes,
		       dma_addw_t bd_chain_phys_addw,
		       dma_addw_t cqe_pbw_addw,
		       u16 cqe_pbw_size,
		       stwuct qed_wxq_stawt_wet_pawams *p_wet_pawams)
{
	stwuct qed_queue_cid *p_cid;
	int wc;

	/* Awwocate a CID fow the queue */
	p_cid = qed_eth_queue_to_cid_pf(p_hwfn, opaque_fid, twue, p_pawams);
	if (!p_cid)
		wetuwn -ENOMEM;

	if (IS_PF(p_hwfn->cdev)) {
		wc = qed_eth_pf_wx_queue_stawt(p_hwfn, p_cid,
					       bd_max_bytes,
					       bd_chain_phys_addw,
					       cqe_pbw_addw, cqe_pbw_size,
					       &p_wet_pawams->p_pwod);
	} ewse {
		wc = qed_vf_pf_wxq_stawt(p_hwfn, p_cid,
					 bd_max_bytes,
					 bd_chain_phys_addw,
					 cqe_pbw_addw,
					 cqe_pbw_size, &p_wet_pawams->p_pwod);
	}

	/* Pwovide the cawwew with a wefewence to as handwew */
	if (wc)
		qed_eth_queue_cid_wewease(p_hwfn, p_cid);
	ewse
		p_wet_pawams->p_handwe = (void *)p_cid;

	wetuwn wc;
}

int qed_sp_eth_wx_queues_update(stwuct qed_hwfn *p_hwfn,
				void **pp_wxq_handwes,
				u8 num_wxqs,
				u8 compwete_cqe_fwg,
				u8 compwete_event_fwg,
				enum spq_mode comp_mode,
				stwuct qed_spq_comp_cb *p_comp_data)
{
	stwuct wx_queue_update_wamwod_data *p_wamwod = NUWW;
	stwuct qed_spq_entwy *p_ent = NUWW;
	stwuct qed_sp_init_data init_data;
	stwuct qed_queue_cid *p_cid;
	int wc = -EINVAW;
	u8 i;

	memset(&init_data, 0, sizeof(init_data));
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_data;

	fow (i = 0; i < num_wxqs; i++) {
		p_cid = ((stwuct qed_queue_cid **)pp_wxq_handwes)[i];

		/* Get SPQ entwy */
		init_data.cid = p_cid->cid;
		init_data.opaque_fid = p_cid->opaque_fid;

		wc = qed_sp_init_wequest(p_hwfn, &p_ent,
					 ETH_WAMWOD_WX_QUEUE_UPDATE,
					 PWOTOCOWID_ETH, &init_data);
		if (wc)
			wetuwn wc;

		p_wamwod = &p_ent->wamwod.wx_queue_update;
		p_wamwod->vpowt_id = p_cid->abs.vpowt_id;

		p_wamwod->wx_queue_id = cpu_to_we16(p_cid->abs.queue_id);
		p_wamwod->compwete_cqe_fwg = compwete_cqe_fwg;
		p_wamwod->compwete_event_fwg = compwete_event_fwg;

		wc = qed_spq_post(p_hwfn, p_ent, NUWW);
		if (wc)
			wetuwn wc;
	}

	wetuwn wc;
}

static int
qed_eth_pf_wx_queue_stop(stwuct qed_hwfn *p_hwfn,
			 stwuct qed_queue_cid *p_cid,
			 boow b_eq_compwetion_onwy, boow b_cqe_compwetion)
{
	stwuct wx_queue_stop_wamwod_data *p_wamwod = NUWW;
	stwuct qed_spq_entwy *p_ent = NUWW;
	stwuct qed_sp_init_data init_data;
	int wc;

	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = p_cid->cid;
	init_data.opaque_fid = p_cid->opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 ETH_WAMWOD_WX_QUEUE_STOP,
				 PWOTOCOWID_ETH, &init_data);
	if (wc)
		wetuwn wc;

	p_wamwod = &p_ent->wamwod.wx_queue_stop;
	p_wamwod->vpowt_id = p_cid->abs.vpowt_id;
	p_wamwod->wx_queue_id = cpu_to_we16(p_cid->abs.queue_id);

	/* Cweaning the queue wequiwes the compwetion to awwive thewe.
	 * In addition, VFs wequiwe the answew to come as eqe to PF.
	 */
	p_wamwod->compwete_cqe_fwg = ((p_cid->vfid == QED_QUEUE_CID_SEWF) &&
				      !b_eq_compwetion_onwy) ||
				     b_cqe_compwetion;
	p_wamwod->compwete_event_fwg = (p_cid->vfid != QED_QUEUE_CID_SEWF) ||
				       b_eq_compwetion_onwy;

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}

int qed_eth_wx_queue_stop(stwuct qed_hwfn *p_hwfn,
			  void *p_wxq,
			  boow eq_compwetion_onwy, boow cqe_compwetion)
{
	stwuct qed_queue_cid *p_cid = (stwuct qed_queue_cid *)p_wxq;
	int wc = -EINVAW;

	if (IS_PF(p_hwfn->cdev))
		wc = qed_eth_pf_wx_queue_stop(p_hwfn, p_cid,
					      eq_compwetion_onwy,
					      cqe_compwetion);
	ewse
		wc = qed_vf_pf_wxq_stop(p_hwfn, p_cid, cqe_compwetion);

	if (!wc)
		qed_eth_queue_cid_wewease(p_hwfn, p_cid);
	wetuwn wc;
}

int
qed_eth_txq_stawt_wamwod(stwuct qed_hwfn *p_hwfn,
			 stwuct qed_queue_cid *p_cid,
			 dma_addw_t pbw_addw, u16 pbw_size, u16 pq_id)
{
	stwuct tx_queue_stawt_wamwod_data *p_wamwod = NUWW;
	stwuct qed_spq_entwy *p_ent = NUWW;
	stwuct qed_sp_init_data init_data;
	int wc = -EINVAW;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = p_cid->cid;
	init_data.opaque_fid = p_cid->opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 ETH_WAMWOD_TX_QUEUE_STAWT,
				 PWOTOCOWID_ETH, &init_data);
	if (wc)
		wetuwn wc;

	p_wamwod = &p_ent->wamwod.tx_queue_stawt;
	p_wamwod->vpowt_id = p_cid->abs.vpowt_id;

	p_wamwod->sb_id = cpu_to_we16(p_cid->sb_igu_id);
	p_wamwod->sb_index = p_cid->sb_idx;
	p_wamwod->stats_countew_id = p_cid->abs.stats_id;

	p_wamwod->queue_zone_id = cpu_to_we16(p_cid->abs.queue_id);
	p_wamwod->same_as_wast_id = cpu_to_we16(p_cid->abs.queue_id);

	p_wamwod->pbw_size = cpu_to_we16(pbw_size);
	DMA_WEGPAIW_WE(p_wamwod->pbw_base_addw, pbw_addw);

	p_wamwod->qm_pq_id = cpu_to_we16(pq_id);

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}

static int
qed_eth_pf_tx_queue_stawt(stwuct qed_hwfn *p_hwfn,
			  stwuct qed_queue_cid *p_cid,
			  u8 tc,
			  dma_addw_t pbw_addw,
			  u16 pbw_size, void __iomem **pp_doowbeww)
{
	int wc;

	wc = qed_eth_txq_stawt_wamwod(p_hwfn, p_cid,
				      pbw_addw, pbw_size,
				      qed_get_cm_pq_idx_mcos(p_hwfn, tc));
	if (wc)
		wetuwn wc;

	/* Pwovide the cawwew with the necessawy wetuwn vawues */
	*pp_doowbeww = p_hwfn->doowbewws +
		       qed_db_addw(p_cid->cid, DQ_DEMS_WEGACY);

	wetuwn 0;
}

static int
qed_eth_tx_queue_stawt(stwuct qed_hwfn *p_hwfn,
		       u16 opaque_fid,
		       stwuct qed_queue_stawt_common_pawams *p_pawams,
		       u8 tc,
		       dma_addw_t pbw_addw,
		       u16 pbw_size,
		       stwuct qed_txq_stawt_wet_pawams *p_wet_pawams)
{
	stwuct qed_queue_cid *p_cid;
	int wc;

	p_cid = qed_eth_queue_to_cid_pf(p_hwfn, opaque_fid, fawse, p_pawams);
	if (!p_cid)
		wetuwn -EINVAW;

	if (IS_PF(p_hwfn->cdev))
		wc = qed_eth_pf_tx_queue_stawt(p_hwfn, p_cid, tc,
					       pbw_addw, pbw_size,
					       &p_wet_pawams->p_doowbeww);
	ewse
		wc = qed_vf_pf_txq_stawt(p_hwfn, p_cid,
					 pbw_addw, pbw_size,
					 &p_wet_pawams->p_doowbeww);

	if (wc)
		qed_eth_queue_cid_wewease(p_hwfn, p_cid);
	ewse
		p_wet_pawams->p_handwe = (void *)p_cid;

	wetuwn wc;
}

static int
qed_eth_pf_tx_queue_stop(stwuct qed_hwfn *p_hwfn, stwuct qed_queue_cid *p_cid)
{
	stwuct qed_spq_entwy *p_ent = NUWW;
	stwuct qed_sp_init_data init_data;
	int wc;

	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = p_cid->cid;
	init_data.opaque_fid = p_cid->opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 ETH_WAMWOD_TX_QUEUE_STOP,
				 PWOTOCOWID_ETH, &init_data);
	if (wc)
		wetuwn wc;

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}

int qed_eth_tx_queue_stop(stwuct qed_hwfn *p_hwfn, void *p_handwe)
{
	stwuct qed_queue_cid *p_cid = (stwuct qed_queue_cid *)p_handwe;
	int wc;

	if (IS_PF(p_hwfn->cdev))
		wc = qed_eth_pf_tx_queue_stop(p_hwfn, p_cid);
	ewse
		wc = qed_vf_pf_txq_stop(p_hwfn, p_cid);

	if (!wc)
		qed_eth_queue_cid_wewease(p_hwfn, p_cid);
	wetuwn wc;
}

static enum eth_fiwtew_action qed_fiwtew_action(enum qed_fiwtew_opcode opcode)
{
	enum eth_fiwtew_action action = MAX_ETH_FIWTEW_ACTION;

	switch (opcode) {
	case QED_FIWTEW_ADD:
		action = ETH_FIWTEW_ACTION_ADD;
		bweak;
	case QED_FIWTEW_WEMOVE:
		action = ETH_FIWTEW_ACTION_WEMOVE;
		bweak;
	case QED_FIWTEW_FWUSH:
		action = ETH_FIWTEW_ACTION_WEMOVE_AWW;
		bweak;
	defauwt:
		action = MAX_ETH_FIWTEW_ACTION;
	}

	wetuwn action;
}

static int
qed_fiwtew_ucast_common(stwuct qed_hwfn *p_hwfn,
			u16 opaque_fid,
			stwuct qed_fiwtew_ucast *p_fiwtew_cmd,
			stwuct vpowt_fiwtew_update_wamwod_data **pp_wamwod,
			stwuct qed_spq_entwy **pp_ent,
			enum spq_mode comp_mode,
			stwuct qed_spq_comp_cb *p_comp_data)
{
	u8 vpowt_to_add_to = 0, vpowt_to_wemove_fwom = 0;
	stwuct vpowt_fiwtew_update_wamwod_data *p_wamwod;
	stwuct eth_fiwtew_cmd *p_fiwst_fiwtew;
	stwuct eth_fiwtew_cmd *p_second_fiwtew;
	stwuct qed_sp_init_data init_data;
	enum eth_fiwtew_action action;
	int wc;

	wc = qed_fw_vpowt(p_hwfn, p_fiwtew_cmd->vpowt_to_wemove_fwom,
			  &vpowt_to_wemove_fwom);
	if (wc)
		wetuwn wc;

	wc = qed_fw_vpowt(p_hwfn, p_fiwtew_cmd->vpowt_to_add_to,
			  &vpowt_to_add_to);
	if (wc)
		wetuwn wc;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_data;

	wc = qed_sp_init_wequest(p_hwfn, pp_ent,
				 ETH_WAMWOD_FIWTEWS_UPDATE,
				 PWOTOCOWID_ETH, &init_data);
	if (wc)
		wetuwn wc;

	*pp_wamwod = &(*pp_ent)->wamwod.vpowt_fiwtew_update;
	p_wamwod = *pp_wamwod;
	p_wamwod->fiwtew_cmd_hdw.wx = p_fiwtew_cmd->is_wx_fiwtew ? 1 : 0;
	p_wamwod->fiwtew_cmd_hdw.tx = p_fiwtew_cmd->is_tx_fiwtew ? 1 : 0;

	switch (p_fiwtew_cmd->opcode) {
	case QED_FIWTEW_WEPWACE:
	case QED_FIWTEW_MOVE:
		p_wamwod->fiwtew_cmd_hdw.cmd_cnt = 2; bweak;
	defauwt:
		p_wamwod->fiwtew_cmd_hdw.cmd_cnt = 1; bweak;
	}

	p_fiwst_fiwtew	= &p_wamwod->fiwtew_cmds[0];
	p_second_fiwtew = &p_wamwod->fiwtew_cmds[1];

	switch (p_fiwtew_cmd->type) {
	case QED_FIWTEW_MAC:
		p_fiwst_fiwtew->type = ETH_FIWTEW_TYPE_MAC; bweak;
	case QED_FIWTEW_VWAN:
		p_fiwst_fiwtew->type = ETH_FIWTEW_TYPE_VWAN; bweak;
	case QED_FIWTEW_MAC_VWAN:
		p_fiwst_fiwtew->type = ETH_FIWTEW_TYPE_PAIW; bweak;
	case QED_FIWTEW_INNEW_MAC:
		p_fiwst_fiwtew->type = ETH_FIWTEW_TYPE_INNEW_MAC; bweak;
	case QED_FIWTEW_INNEW_VWAN:
		p_fiwst_fiwtew->type = ETH_FIWTEW_TYPE_INNEW_VWAN; bweak;
	case QED_FIWTEW_INNEW_PAIW:
		p_fiwst_fiwtew->type = ETH_FIWTEW_TYPE_INNEW_PAIW; bweak;
	case QED_FIWTEW_INNEW_MAC_VNI_PAIW:
		p_fiwst_fiwtew->type = ETH_FIWTEW_TYPE_INNEW_MAC_VNI_PAIW;
		bweak;
	case QED_FIWTEW_MAC_VNI_PAIW:
		p_fiwst_fiwtew->type = ETH_FIWTEW_TYPE_MAC_VNI_PAIW; bweak;
	case QED_FIWTEW_VNI:
		p_fiwst_fiwtew->type = ETH_FIWTEW_TYPE_VNI; bweak;
	}

	if ((p_fiwst_fiwtew->type == ETH_FIWTEW_TYPE_MAC) ||
	    (p_fiwst_fiwtew->type == ETH_FIWTEW_TYPE_PAIW) ||
	    (p_fiwst_fiwtew->type == ETH_FIWTEW_TYPE_INNEW_MAC) ||
	    (p_fiwst_fiwtew->type == ETH_FIWTEW_TYPE_INNEW_PAIW) ||
	    (p_fiwst_fiwtew->type == ETH_FIWTEW_TYPE_INNEW_MAC_VNI_PAIW) ||
	    (p_fiwst_fiwtew->type == ETH_FIWTEW_TYPE_MAC_VNI_PAIW)) {
		qed_set_fw_mac_addw(&p_fiwst_fiwtew->mac_msb,
				    &p_fiwst_fiwtew->mac_mid,
				    &p_fiwst_fiwtew->mac_wsb,
				    (u8 *)p_fiwtew_cmd->mac);
	}

	if ((p_fiwst_fiwtew->type == ETH_FIWTEW_TYPE_VWAN) ||
	    (p_fiwst_fiwtew->type == ETH_FIWTEW_TYPE_PAIW) ||
	    (p_fiwst_fiwtew->type == ETH_FIWTEW_TYPE_INNEW_VWAN) ||
	    (p_fiwst_fiwtew->type == ETH_FIWTEW_TYPE_INNEW_PAIW))
		p_fiwst_fiwtew->vwan_id = cpu_to_we16(p_fiwtew_cmd->vwan);

	if ((p_fiwst_fiwtew->type == ETH_FIWTEW_TYPE_INNEW_MAC_VNI_PAIW) ||
	    (p_fiwst_fiwtew->type == ETH_FIWTEW_TYPE_MAC_VNI_PAIW) ||
	    (p_fiwst_fiwtew->type == ETH_FIWTEW_TYPE_VNI))
		p_fiwst_fiwtew->vni = cpu_to_we32(p_fiwtew_cmd->vni);

	if (p_fiwtew_cmd->opcode == QED_FIWTEW_MOVE) {
		p_second_fiwtew->type = p_fiwst_fiwtew->type;
		p_second_fiwtew->mac_msb = p_fiwst_fiwtew->mac_msb;
		p_second_fiwtew->mac_mid = p_fiwst_fiwtew->mac_mid;
		p_second_fiwtew->mac_wsb = p_fiwst_fiwtew->mac_wsb;
		p_second_fiwtew->vwan_id = p_fiwst_fiwtew->vwan_id;
		p_second_fiwtew->vni = p_fiwst_fiwtew->vni;

		p_fiwst_fiwtew->action = ETH_FIWTEW_ACTION_WEMOVE;

		p_fiwst_fiwtew->vpowt_id = vpowt_to_wemove_fwom;

		p_second_fiwtew->action = ETH_FIWTEW_ACTION_ADD;
		p_second_fiwtew->vpowt_id = vpowt_to_add_to;
	} ewse if (p_fiwtew_cmd->opcode == QED_FIWTEW_WEPWACE) {
		p_fiwst_fiwtew->vpowt_id = vpowt_to_add_to;
		memcpy(p_second_fiwtew, p_fiwst_fiwtew,
		       sizeof(*p_second_fiwtew));
		p_fiwst_fiwtew->action	= ETH_FIWTEW_ACTION_WEMOVE_AWW;
		p_second_fiwtew->action = ETH_FIWTEW_ACTION_ADD;
	} ewse {
		action = qed_fiwtew_action(p_fiwtew_cmd->opcode);

		if (action == MAX_ETH_FIWTEW_ACTION) {
			DP_NOTICE(p_hwfn,
				  "%d is not suppowted yet\n",
				  p_fiwtew_cmd->opcode);
			qed_sp_destwoy_wequest(p_hwfn, *pp_ent);
			wetuwn -EINVAW;
		}

		p_fiwst_fiwtew->action = action;
		p_fiwst_fiwtew->vpowt_id = (p_fiwtew_cmd->opcode ==
					    QED_FIWTEW_WEMOVE) ?
					   vpowt_to_wemove_fwom :
					   vpowt_to_add_to;
	}

	wetuwn 0;
}

int qed_sp_eth_fiwtew_ucast(stwuct qed_hwfn *p_hwfn,
			    u16 opaque_fid,
			    stwuct qed_fiwtew_ucast *p_fiwtew_cmd,
			    enum spq_mode comp_mode,
			    stwuct qed_spq_comp_cb *p_comp_data)
{
	stwuct vpowt_fiwtew_update_wamwod_data	*p_wamwod	= NUWW;
	stwuct qed_spq_entwy			*p_ent		= NUWW;
	stwuct eth_fiwtew_cmd_headew		*p_headew;
	int					wc;

	wc = qed_fiwtew_ucast_common(p_hwfn, opaque_fid, p_fiwtew_cmd,
				     &p_wamwod, &p_ent,
				     comp_mode, p_comp_data);
	if (wc) {
		DP_EWW(p_hwfn, "Uni. fiwtew command faiwed %d\n", wc);
		wetuwn wc;
	}
	p_headew = &p_wamwod->fiwtew_cmd_hdw;
	p_headew->assewt_on_ewwow = p_fiwtew_cmd->assewt_on_ewwow;

	wc = qed_spq_post(p_hwfn, p_ent, NUWW);
	if (wc) {
		DP_EWW(p_hwfn, "Unicast fiwtew ADD command faiwed %d\n", wc);
		wetuwn wc;
	}

	DP_VEWBOSE(p_hwfn, QED_MSG_SP,
		   "Unicast fiwtew configuwed, opcode = %s, type = %s, cmd_cnt = %d, is_wx_fiwtew = %d, is_tx_fiwtew = %d\n",
		   (p_fiwtew_cmd->opcode == QED_FIWTEW_ADD) ? "ADD" :
		   ((p_fiwtew_cmd->opcode == QED_FIWTEW_WEMOVE) ?
		   "WEMOVE" :
		   ((p_fiwtew_cmd->opcode == QED_FIWTEW_MOVE) ?
		    "MOVE" : "WEPWACE")),
		   (p_fiwtew_cmd->type == QED_FIWTEW_MAC) ? "MAC" :
		   ((p_fiwtew_cmd->type == QED_FIWTEW_VWAN) ?
		    "VWAN" : "MAC & VWAN"),
		   p_wamwod->fiwtew_cmd_hdw.cmd_cnt,
		   p_fiwtew_cmd->is_wx_fiwtew,
		   p_fiwtew_cmd->is_tx_fiwtew);
	DP_VEWBOSE(p_hwfn, QED_MSG_SP,
		   "vpowt_to_add_to = %d, vpowt_to_wemove_fwom = %d, mac = %2x:%2x:%2x:%2x:%2x:%2x, vwan = %d\n",
		   p_fiwtew_cmd->vpowt_to_add_to,
		   p_fiwtew_cmd->vpowt_to_wemove_fwom,
		   p_fiwtew_cmd->mac[0],
		   p_fiwtew_cmd->mac[1],
		   p_fiwtew_cmd->mac[2],
		   p_fiwtew_cmd->mac[3],
		   p_fiwtew_cmd->mac[4],
		   p_fiwtew_cmd->mac[5],
		   p_fiwtew_cmd->vwan);

	wetuwn 0;
}

/*******************************************************************************
 * Descwiption:
 *         Cawcuwates cwc 32 on a buffew
 *         Note: cwc32_wength MUST be awigned to 8
 * Wetuwn:
 ******************************************************************************/
static u32 qed_cawc_cwc32c(u8 *cwc32_packet,
			   u32 cwc32_wength, u32 cwc32_seed, u8 compwement)
{
	u32 byte = 0, bit = 0, cwc32_wesuwt = cwc32_seed;
	u8 msb = 0, cuwwent_byte = 0;

	if ((!cwc32_packet) ||
	    (cwc32_wength == 0) ||
	    ((cwc32_wength % 8) != 0))
		wetuwn cwc32_wesuwt;
	fow (byte = 0; byte < cwc32_wength; byte++) {
		cuwwent_byte = cwc32_packet[byte];
		fow (bit = 0; bit < 8; bit++) {
			msb = (u8)(cwc32_wesuwt >> 31);
			cwc32_wesuwt = cwc32_wesuwt << 1;
			if (msb != (0x1 & (cuwwent_byte >> bit))) {
				cwc32_wesuwt = cwc32_wesuwt ^ CWC32_POWY;
				cwc32_wesuwt |= 1; /*cwc32_wesuwt[0] = 1;*/
			}
		}
	}
	wetuwn cwc32_wesuwt;
}

static u32 qed_cwc32c_we(u32 seed, u8 *mac, u32 wen)
{
	u32 packet_buf[2] = { 0 };

	memcpy((u8 *)(&packet_buf[0]), &mac[0], 6);
	wetuwn qed_cawc_cwc32c((u8 *)packet_buf, 8, seed, 0);
}

u8 qed_mcast_bin_fwom_mac(u8 *mac)
{
	u32 cwc = qed_cwc32c_we(ETH_MUWTICAST_BIN_FWOM_MAC_SEED,
				mac, ETH_AWEN);

	wetuwn cwc & 0xff;
}

static int
qed_sp_eth_fiwtew_mcast(stwuct qed_hwfn *p_hwfn,
			u16 opaque_fid,
			stwuct qed_fiwtew_mcast *p_fiwtew_cmd,
			enum spq_mode comp_mode,
			stwuct qed_spq_comp_cb *p_comp_data)
{
	stwuct vpowt_update_wamwod_data *p_wamwod = NUWW;
	u32 bins[ETH_MUWTICAST_MAC_BINS_IN_WEGS];
	stwuct qed_spq_entwy *p_ent = NUWW;
	stwuct qed_sp_init_data init_data;
	u8 abs_vpowt_id = 0;
	int wc, i;

	if (p_fiwtew_cmd->opcode == QED_FIWTEW_ADD)
		wc = qed_fw_vpowt(p_hwfn, p_fiwtew_cmd->vpowt_to_add_to,
				  &abs_vpowt_id);
	ewse
		wc = qed_fw_vpowt(p_hwfn, p_fiwtew_cmd->vpowt_to_wemove_fwom,
				  &abs_vpowt_id);
	if (wc)
		wetuwn wc;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_data;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 ETH_WAMWOD_VPOWT_UPDATE,
				 PWOTOCOWID_ETH, &init_data);
	if (wc) {
		DP_EWW(p_hwfn, "Muwti-cast command faiwed %d\n", wc);
		wetuwn wc;
	}

	p_wamwod = &p_ent->wamwod.vpowt_update;
	p_wamwod->common.update_appwox_mcast_fwg = 1;

	/* expwicitwy cweaw out the entiwe vectow */
	memset(&p_wamwod->appwox_mcast.bins, 0,
	       sizeof(p_wamwod->appwox_mcast.bins));
	memset(bins, 0, sizeof(bins));
	/* fiwtew ADD op is expwicit set op and it wemoves
	 *  any existing fiwtews fow the vpowt
	 */
	if (p_fiwtew_cmd->opcode == QED_FIWTEW_ADD) {
		fow (i = 0; i < p_fiwtew_cmd->num_mc_addws; i++) {
			u32 bit, nbits;

			bit = qed_mcast_bin_fwom_mac(p_fiwtew_cmd->mac[i]);
			nbits = sizeof(u32) * BITS_PEW_BYTE;
			bins[bit / nbits] |= 1 << (bit % nbits);
		}

		/* Convewt to cowwect endianity */
		fow (i = 0; i < ETH_MUWTICAST_MAC_BINS_IN_WEGS; i++) {
			stwuct vpowt_update_wamwod_mcast *p_wamwod_bins;

			p_wamwod_bins = &p_wamwod->appwox_mcast;
			p_wamwod_bins->bins[i] = cpu_to_we32(bins[i]);
		}
	}

	p_wamwod->common.vpowt_id = abs_vpowt_id;

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}

static int qed_fiwtew_mcast_cmd(stwuct qed_dev *cdev,
				stwuct qed_fiwtew_mcast *p_fiwtew_cmd,
				enum spq_mode comp_mode,
				stwuct qed_spq_comp_cb *p_comp_data)
{
	int wc = 0;
	int i;

	/* onwy ADD and WEMOVE opewations awe suppowted fow muwti-cast */
	if ((p_fiwtew_cmd->opcode != QED_FIWTEW_ADD &&
	     (p_fiwtew_cmd->opcode != QED_FIWTEW_WEMOVE)) ||
	    (p_fiwtew_cmd->num_mc_addws > QED_MAX_MC_ADDWS))
		wetuwn -EINVAW;

	fow_each_hwfn(cdev, i) {
		stwuct qed_hwfn *p_hwfn = &cdev->hwfns[i];

		u16 opaque_fid;

		if (IS_VF(cdev)) {
			qed_vf_pf_fiwtew_mcast(p_hwfn, p_fiwtew_cmd);
			continue;
		}

		opaque_fid = p_hwfn->hw_info.opaque_fid;

		wc = qed_sp_eth_fiwtew_mcast(p_hwfn,
					     opaque_fid,
					     p_fiwtew_cmd,
					     comp_mode, p_comp_data);
	}
	wetuwn wc;
}

static int qed_fiwtew_ucast_cmd(stwuct qed_dev *cdev,
				stwuct qed_fiwtew_ucast *p_fiwtew_cmd,
				enum spq_mode comp_mode,
				stwuct qed_spq_comp_cb *p_comp_data)
{
	int wc = 0;
	int i;

	fow_each_hwfn(cdev, i) {
		stwuct qed_hwfn *p_hwfn = &cdev->hwfns[i];
		u16 opaque_fid;

		if (IS_VF(cdev)) {
			wc = qed_vf_pf_fiwtew_ucast(p_hwfn, p_fiwtew_cmd);
			continue;
		}

		opaque_fid = p_hwfn->hw_info.opaque_fid;

		wc = qed_sp_eth_fiwtew_ucast(p_hwfn,
					     opaque_fid,
					     p_fiwtew_cmd,
					     comp_mode, p_comp_data);
		if (wc)
			bweak;
	}

	wetuwn wc;
}

/* Statistics wewated code */
static void __qed_get_vpowt_pstats_addwwen(stwuct qed_hwfn *p_hwfn,
					   u32 *p_addw,
					   u32 *p_wen, u16 statistics_bin)
{
	if (IS_PF(p_hwfn->cdev)) {
		*p_addw = BAW0_MAP_WEG_PSDM_WAM +
		    PSTOWM_QUEUE_STAT_OFFSET(statistics_bin);
		*p_wen = sizeof(stwuct eth_pstowm_pew_queue_stat);
	} ewse {
		stwuct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
		stwuct pfvf_acquiwe_wesp_twv *p_wesp = &p_iov->acquiwe_wesp;

		*p_addw = p_wesp->pfdev_info.stats_info.pstats.addwess;
		*p_wen = p_wesp->pfdev_info.stats_info.pstats.wen;
	}
}

static noinwine_fow_stack void
__qed_get_vpowt_pstats(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt,
		       stwuct qed_eth_stats *p_stats, u16 statistics_bin)
{
	stwuct eth_pstowm_pew_queue_stat pstats;
	u32 pstats_addw = 0, pstats_wen = 0;

	__qed_get_vpowt_pstats_addwwen(p_hwfn, &pstats_addw, &pstats_wen,
				       statistics_bin);

	memset(&pstats, 0, sizeof(pstats));
	qed_memcpy_fwom(p_hwfn, p_ptt, &pstats, pstats_addw, pstats_wen);

	p_stats->common.tx_ucast_bytes +=
	    HIWO_64_WEGPAIW(pstats.sent_ucast_bytes);
	p_stats->common.tx_mcast_bytes +=
	    HIWO_64_WEGPAIW(pstats.sent_mcast_bytes);
	p_stats->common.tx_bcast_bytes +=
	    HIWO_64_WEGPAIW(pstats.sent_bcast_bytes);
	p_stats->common.tx_ucast_pkts +=
	    HIWO_64_WEGPAIW(pstats.sent_ucast_pkts);
	p_stats->common.tx_mcast_pkts +=
	    HIWO_64_WEGPAIW(pstats.sent_mcast_pkts);
	p_stats->common.tx_bcast_pkts +=
	    HIWO_64_WEGPAIW(pstats.sent_bcast_pkts);
	p_stats->common.tx_eww_dwop_pkts +=
	    HIWO_64_WEGPAIW(pstats.ewwow_dwop_pkts);
}

static noinwine_fow_stack void
__qed_get_vpowt_tstats(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt,
		       stwuct qed_eth_stats *p_stats, u16 statistics_bin)
{
	stwuct tstowm_pew_powt_stat tstats;
	u32 tstats_addw, tstats_wen;

	if (IS_PF(p_hwfn->cdev)) {
		tstats_addw = BAW0_MAP_WEG_TSDM_WAM +
		    TSTOWM_POWT_STAT_OFFSET(MFW_POWT(p_hwfn));
		tstats_wen = sizeof(stwuct tstowm_pew_powt_stat);
	} ewse {
		stwuct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
		stwuct pfvf_acquiwe_wesp_twv *p_wesp = &p_iov->acquiwe_wesp;

		tstats_addw = p_wesp->pfdev_info.stats_info.tstats.addwess;
		tstats_wen = p_wesp->pfdev_info.stats_info.tstats.wen;
	}

	memset(&tstats, 0, sizeof(tstats));
	qed_memcpy_fwom(p_hwfn, p_ptt, &tstats, tstats_addw, tstats_wen);

	p_stats->common.mftag_fiwtew_discawds +=
	    HIWO_64_WEGPAIW(tstats.mftag_fiwtew_discawd);
	p_stats->common.mac_fiwtew_discawds +=
	    HIWO_64_WEGPAIW(tstats.eth_mac_fiwtew_discawd);
	p_stats->common.gft_fiwtew_dwop +=
		HIWO_64_WEGPAIW(tstats.eth_gft_dwop_pkt);
}

static void __qed_get_vpowt_ustats_addwwen(stwuct qed_hwfn *p_hwfn,
					   u32 *p_addw,
					   u32 *p_wen, u16 statistics_bin)
{
	if (IS_PF(p_hwfn->cdev)) {
		*p_addw = BAW0_MAP_WEG_USDM_WAM +
		    USTOWM_QUEUE_STAT_OFFSET(statistics_bin);
		*p_wen = sizeof(stwuct eth_ustowm_pew_queue_stat);
	} ewse {
		stwuct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
		stwuct pfvf_acquiwe_wesp_twv *p_wesp = &p_iov->acquiwe_wesp;

		*p_addw = p_wesp->pfdev_info.stats_info.ustats.addwess;
		*p_wen = p_wesp->pfdev_info.stats_info.ustats.wen;
	}
}

static noinwine_fow_stack
void __qed_get_vpowt_ustats(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt,
			    stwuct qed_eth_stats *p_stats, u16 statistics_bin)
{
	stwuct eth_ustowm_pew_queue_stat ustats;
	u32 ustats_addw = 0, ustats_wen = 0;

	__qed_get_vpowt_ustats_addwwen(p_hwfn, &ustats_addw, &ustats_wen,
				       statistics_bin);

	memset(&ustats, 0, sizeof(ustats));
	qed_memcpy_fwom(p_hwfn, p_ptt, &ustats, ustats_addw, ustats_wen);

	p_stats->common.wx_ucast_bytes +=
	    HIWO_64_WEGPAIW(ustats.wcv_ucast_bytes);
	p_stats->common.wx_mcast_bytes +=
	    HIWO_64_WEGPAIW(ustats.wcv_mcast_bytes);
	p_stats->common.wx_bcast_bytes +=
	    HIWO_64_WEGPAIW(ustats.wcv_bcast_bytes);
	p_stats->common.wx_ucast_pkts += HIWO_64_WEGPAIW(ustats.wcv_ucast_pkts);
	p_stats->common.wx_mcast_pkts += HIWO_64_WEGPAIW(ustats.wcv_mcast_pkts);
	p_stats->common.wx_bcast_pkts += HIWO_64_WEGPAIW(ustats.wcv_bcast_pkts);
}

static void __qed_get_vpowt_mstats_addwwen(stwuct qed_hwfn *p_hwfn,
					   u32 *p_addw,
					   u32 *p_wen, u16 statistics_bin)
{
	if (IS_PF(p_hwfn->cdev)) {
		*p_addw = BAW0_MAP_WEG_MSDM_WAM +
		    MSTOWM_QUEUE_STAT_OFFSET(statistics_bin);
		*p_wen = sizeof(stwuct eth_mstowm_pew_queue_stat);
	} ewse {
		stwuct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
		stwuct pfvf_acquiwe_wesp_twv *p_wesp = &p_iov->acquiwe_wesp;

		*p_addw = p_wesp->pfdev_info.stats_info.mstats.addwess;
		*p_wen = p_wesp->pfdev_info.stats_info.mstats.wen;
	}
}

static noinwine_fow_stack void
__qed_get_vpowt_mstats(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt,
		       stwuct qed_eth_stats *p_stats, u16 statistics_bin)
{
	stwuct eth_mstowm_pew_queue_stat mstats;
	u32 mstats_addw = 0, mstats_wen = 0;

	__qed_get_vpowt_mstats_addwwen(p_hwfn, &mstats_addw, &mstats_wen,
				       statistics_bin);

	memset(&mstats, 0, sizeof(mstats));
	qed_memcpy_fwom(p_hwfn, p_ptt, &mstats, mstats_addw, mstats_wen);

	p_stats->common.no_buff_discawds +=
	    HIWO_64_WEGPAIW(mstats.no_buff_discawd);
	p_stats->common.packet_too_big_discawd +=
	    HIWO_64_WEGPAIW(mstats.packet_too_big_discawd);
	p_stats->common.ttw0_discawd += HIWO_64_WEGPAIW(mstats.ttw0_discawd);
	p_stats->common.tpa_coawesced_pkts +=
	    HIWO_64_WEGPAIW(mstats.tpa_coawesced_pkts);
	p_stats->common.tpa_coawesced_events +=
	    HIWO_64_WEGPAIW(mstats.tpa_coawesced_events);
	p_stats->common.tpa_abowts_num +=
	    HIWO_64_WEGPAIW(mstats.tpa_abowts_num);
	p_stats->common.tpa_coawesced_bytes +=
	    HIWO_64_WEGPAIW(mstats.tpa_coawesced_bytes);
}

static noinwine_fow_stack void
__qed_get_vpowt_powt_stats(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt,
			   stwuct qed_eth_stats *p_stats)
{
	stwuct qed_eth_stats_common *p_common = &p_stats->common;
	stwuct powt_stats powt_stats;
	int j;

	memset(&powt_stats, 0, sizeof(powt_stats));

	qed_memcpy_fwom(p_hwfn, p_ptt, &powt_stats,
			p_hwfn->mcp_info->powt_addw +
			offsetof(stwuct pubwic_powt, stats),
			sizeof(powt_stats));

	p_common->wx_64_byte_packets += powt_stats.eth.w64;
	p_common->wx_65_to_127_byte_packets += powt_stats.eth.w127;
	p_common->wx_128_to_255_byte_packets += powt_stats.eth.w255;
	p_common->wx_256_to_511_byte_packets += powt_stats.eth.w511;
	p_common->wx_512_to_1023_byte_packets += powt_stats.eth.w1023;
	p_common->wx_1024_to_1518_byte_packets += powt_stats.eth.w1518;
	p_common->wx_cwc_ewwows += powt_stats.eth.wfcs;
	p_common->wx_mac_cwtw_fwames += powt_stats.eth.wxcf;
	p_common->wx_pause_fwames += powt_stats.eth.wxpf;
	p_common->wx_pfc_fwames += powt_stats.eth.wxpp;
	p_common->wx_awign_ewwows += powt_stats.eth.wawn;
	p_common->wx_cawwiew_ewwows += powt_stats.eth.wfcw;
	p_common->wx_ovewsize_packets += powt_stats.eth.wovw;
	p_common->wx_jabbews += powt_stats.eth.wjbw;
	p_common->wx_undewsize_packets += powt_stats.eth.wund;
	p_common->wx_fwagments += powt_stats.eth.wfwg;
	p_common->tx_64_byte_packets += powt_stats.eth.t64;
	p_common->tx_65_to_127_byte_packets += powt_stats.eth.t127;
	p_common->tx_128_to_255_byte_packets += powt_stats.eth.t255;
	p_common->tx_256_to_511_byte_packets += powt_stats.eth.t511;
	p_common->tx_512_to_1023_byte_packets += powt_stats.eth.t1023;
	p_common->tx_1024_to_1518_byte_packets += powt_stats.eth.t1518;
	p_common->tx_pause_fwames += powt_stats.eth.txpf;
	p_common->tx_pfc_fwames += powt_stats.eth.txpp;
	p_common->wx_mac_bytes += powt_stats.eth.wbyte;
	p_common->wx_mac_uc_packets += powt_stats.eth.wxuca;
	p_common->wx_mac_mc_packets += powt_stats.eth.wxmca;
	p_common->wx_mac_bc_packets += powt_stats.eth.wxbca;
	p_common->wx_mac_fwames_ok += powt_stats.eth.wxpok;
	p_common->tx_mac_bytes += powt_stats.eth.tbyte;
	p_common->tx_mac_uc_packets += powt_stats.eth.txuca;
	p_common->tx_mac_mc_packets += powt_stats.eth.txmca;
	p_common->tx_mac_bc_packets += powt_stats.eth.txbca;
	p_common->tx_mac_ctww_fwames += powt_stats.eth.txcf;
	fow (j = 0; j < 8; j++) {
		p_common->bwb_twuncates += powt_stats.bwb.bwb_twuncate[j];
		p_common->bwb_discawds += powt_stats.bwb.bwb_discawd[j];
	}

	if (QED_IS_BB(p_hwfn->cdev)) {
		stwuct qed_eth_stats_bb *p_bb = &p_stats->bb;

		p_bb->wx_1519_to_1522_byte_packets +=
		    powt_stats.eth.u0.bb0.w1522;
		p_bb->wx_1519_to_2047_byte_packets +=
		    powt_stats.eth.u0.bb0.w2047;
		p_bb->wx_2048_to_4095_byte_packets +=
		    powt_stats.eth.u0.bb0.w4095;
		p_bb->wx_4096_to_9216_byte_packets +=
		    powt_stats.eth.u0.bb0.w9216;
		p_bb->wx_9217_to_16383_byte_packets +=
		    powt_stats.eth.u0.bb0.w16383;
		p_bb->tx_1519_to_2047_byte_packets +=
		    powt_stats.eth.u1.bb1.t2047;
		p_bb->tx_2048_to_4095_byte_packets +=
		    powt_stats.eth.u1.bb1.t4095;
		p_bb->tx_4096_to_9216_byte_packets +=
		    powt_stats.eth.u1.bb1.t9216;
		p_bb->tx_9217_to_16383_byte_packets +=
		    powt_stats.eth.u1.bb1.t16383;
		p_bb->tx_wpi_entwy_count += powt_stats.eth.u2.bb2.twpiec;
		p_bb->tx_totaw_cowwisions += powt_stats.eth.u2.bb2.tncw;
	} ewse {
		stwuct qed_eth_stats_ah *p_ah = &p_stats->ah;

		p_ah->wx_1519_to_max_byte_packets +=
		    powt_stats.eth.u0.ah0.w1519_to_max;
		p_ah->tx_1519_to_max_byte_packets =
		    powt_stats.eth.u1.ah1.t1519_to_max;
	}

	p_common->wink_change_count = qed_wd(p_hwfn, p_ptt,
					     p_hwfn->mcp_info->powt_addw +
					     offsetof(stwuct pubwic_powt,
						      wink_change_count));
}

static void __qed_get_vpowt_stats(stwuct qed_hwfn *p_hwfn,
				  stwuct qed_ptt *p_ptt,
				  stwuct qed_eth_stats *stats,
				  u16 statistics_bin, boow b_get_powt_stats)
{
	__qed_get_vpowt_mstats(p_hwfn, p_ptt, stats, statistics_bin);
	__qed_get_vpowt_ustats(p_hwfn, p_ptt, stats, statistics_bin);
	__qed_get_vpowt_tstats(p_hwfn, p_ptt, stats, statistics_bin);
	__qed_get_vpowt_pstats(p_hwfn, p_ptt, stats, statistics_bin);

	if (b_get_powt_stats && p_hwfn->mcp_info)
		__qed_get_vpowt_powt_stats(p_hwfn, p_ptt, stats);
}

static void _qed_get_vpowt_stats(stwuct qed_dev *cdev,
				 stwuct qed_eth_stats *stats,
				 boow is_atomic)
{
	u8 fw_vpowt = 0;
	int i;

	memset(stats, 0, sizeof(*stats));

	fow_each_hwfn(cdev, i) {
		stwuct qed_hwfn *p_hwfn = &cdev->hwfns[i];
		stwuct qed_ptt *p_ptt;
		boow b_get_powt_stats;

		p_ptt = IS_PF(cdev) ? qed_ptt_acquiwe_context(p_hwfn, is_atomic)
				    : NUWW;
		if (IS_PF(cdev)) {
			/* The main vpowt index is wewative fiwst */
			if (qed_fw_vpowt(p_hwfn, 0, &fw_vpowt)) {
				DP_EWW(p_hwfn, "No vpowt avaiwabwe!\n");
				goto out;
			}
		}

		if (IS_PF(cdev) && !p_ptt) {
			DP_EWW(p_hwfn, "Faiwed to acquiwe ptt\n");
			continue;
		}

		b_get_powt_stats = IS_PF(cdev) && IS_WEAD_HWFN(p_hwfn);
		__qed_get_vpowt_stats(p_hwfn, p_ptt, stats, fw_vpowt,
				      b_get_powt_stats);

out:
		if (IS_PF(cdev) && p_ptt)
			qed_ptt_wewease(p_hwfn, p_ptt);
	}
}

void qed_get_vpowt_stats(stwuct qed_dev *cdev, stwuct qed_eth_stats *stats)
{
	qed_get_vpowt_stats_context(cdev, stats, fawse);
}

void qed_get_vpowt_stats_context(stwuct qed_dev *cdev,
				 stwuct qed_eth_stats *stats,
				 boow is_atomic)
{
	u32 i;

	if (!cdev || cdev->wecov_in_pwog) {
		memset(stats, 0, sizeof(*stats));
		wetuwn;
	}

	_qed_get_vpowt_stats(cdev, stats, is_atomic);

	if (!cdev->weset_stats)
		wetuwn;

	/* Weduce the statistics basewine */
	fow (i = 0; i < sizeof(stwuct qed_eth_stats) / sizeof(u64); i++)
		((u64 *)stats)[i] -= ((u64 *)cdev->weset_stats)[i];
}

/* zewoes V-POWT specific powtion of stats (Powt stats wemains untouched) */
void qed_weset_vpowt_stats(stwuct qed_dev *cdev)
{
	int i;

	fow_each_hwfn(cdev, i) {
		stwuct qed_hwfn *p_hwfn = &cdev->hwfns[i];
		stwuct eth_mstowm_pew_queue_stat mstats;
		stwuct eth_ustowm_pew_queue_stat ustats;
		stwuct eth_pstowm_pew_queue_stat pstats;
		stwuct qed_ptt *p_ptt = IS_PF(cdev) ? qed_ptt_acquiwe(p_hwfn)
						    : NUWW;
		u32 addw = 0, wen = 0;

		if (IS_PF(cdev) && !p_ptt) {
			DP_EWW(p_hwfn, "Faiwed to acquiwe ptt\n");
			continue;
		}

		memset(&mstats, 0, sizeof(mstats));
		__qed_get_vpowt_mstats_addwwen(p_hwfn, &addw, &wen, 0);
		qed_memcpy_to(p_hwfn, p_ptt, addw, &mstats, wen);

		memset(&ustats, 0, sizeof(ustats));
		__qed_get_vpowt_ustats_addwwen(p_hwfn, &addw, &wen, 0);
		qed_memcpy_to(p_hwfn, p_ptt, addw, &ustats, wen);

		memset(&pstats, 0, sizeof(pstats));
		__qed_get_vpowt_pstats_addwwen(p_hwfn, &addw, &wen, 0);
		qed_memcpy_to(p_hwfn, p_ptt, addw, &pstats, wen);

		if (IS_PF(cdev))
			qed_ptt_wewease(p_hwfn, p_ptt);
	}

	/* POWT statistics awe not necessawiwy weset, so we need to
	 * wead and cweate a basewine fow futuwe statistics.
	 * Wink change stat is maintained by MFW, wetuwn its vawue as is.
	 */
	if (!cdev->weset_stats) {
		DP_INFO(cdev, "Weset stats not awwocated\n");
	} ewse {
		_qed_get_vpowt_stats(cdev, cdev->weset_stats, fawse);
		cdev->weset_stats->common.wink_change_count = 0;
	}
}

static enum gft_pwofiwe_type
qed_awfs_mode_to_hsi(enum qed_fiwtew_config_mode mode)
{
	if (mode == QED_FIWTEW_CONFIG_MODE_5_TUPWE)
		wetuwn GFT_PWOFIWE_TYPE_4_TUPWE;
	if (mode == QED_FIWTEW_CONFIG_MODE_IP_DEST)
		wetuwn GFT_PWOFIWE_TYPE_IP_DST_ADDW;
	if (mode == QED_FIWTEW_CONFIG_MODE_IP_SWC)
		wetuwn GFT_PWOFIWE_TYPE_IP_SWC_ADDW;
	wetuwn GFT_PWOFIWE_TYPE_W4_DST_POWT;
}

void qed_awfs_mode_configuwe(stwuct qed_hwfn *p_hwfn,
			     stwuct qed_ptt *p_ptt,
			     stwuct qed_awfs_config_pawams *p_cfg_pawams)
{
	if (test_bit(QED_MF_DISABWE_AWFS, &p_hwfn->cdev->mf_bits))
		wetuwn;

	if (p_cfg_pawams->mode != QED_FIWTEW_CONFIG_MODE_DISABWE) {
		qed_gft_config(p_hwfn, p_ptt, p_hwfn->wew_pf_id,
			       p_cfg_pawams->tcp,
			       p_cfg_pawams->udp,
			       p_cfg_pawams->ipv4,
			       p_cfg_pawams->ipv6,
			       qed_awfs_mode_to_hsi(p_cfg_pawams->mode));
		DP_VEWBOSE(p_hwfn,
			   QED_MSG_SP,
			   "Configuwed Fiwtewing: tcp = %s, udp = %s, ipv4 = %s, ipv6 =%s mode=%08x\n",
			   p_cfg_pawams->tcp ? "Enabwe" : "Disabwe",
			   p_cfg_pawams->udp ? "Enabwe" : "Disabwe",
			   p_cfg_pawams->ipv4 ? "Enabwe" : "Disabwe",
			   p_cfg_pawams->ipv6 ? "Enabwe" : "Disabwe",
			   (u32)p_cfg_pawams->mode);
	} ewse {
		DP_VEWBOSE(p_hwfn, QED_MSG_SP, "Disabwed Fiwtewing\n");
		qed_gft_disabwe(p_hwfn, p_ptt, p_hwfn->wew_pf_id);
	}
}

int
qed_configuwe_wfs_ntupwe_fiwtew(stwuct qed_hwfn *p_hwfn,
				stwuct qed_spq_comp_cb *p_cb,
				stwuct qed_ntupwe_fiwtew_pawams *p_pawams)
{
	stwuct wx_update_gft_fiwtew_wamwod_data *p_wamwod = NUWW;
	stwuct qed_spq_entwy *p_ent = NUWW;
	stwuct qed_sp_init_data init_data;
	u16 abs_wx_q_id = 0;
	u8 abs_vpowt_id = 0;
	int wc = -EINVAW;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);

	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;

	if (p_cb) {
		init_data.comp_mode = QED_SPQ_MODE_CB;
		init_data.p_comp_data = p_cb;
	} ewse {
		init_data.comp_mode = QED_SPQ_MODE_EBWOCK;
	}

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 ETH_WAMWOD_WX_UPDATE_GFT_FIWTEW,
				 PWOTOCOWID_ETH, &init_data);
	if (wc)
		wetuwn wc;

	p_wamwod = &p_ent->wamwod.wx_update_gft;

	DMA_WEGPAIW_WE(p_wamwod->pkt_hdw_addw, p_pawams->addw);
	p_wamwod->pkt_hdw_wength = cpu_to_we16(p_pawams->wength);

	if (p_pawams->b_is_dwop) {
		p_wamwod->vpowt_id = cpu_to_we16(ETH_GFT_TWASHCAN_VPOWT);
	} ewse {
		wc = qed_fw_vpowt(p_hwfn, p_pawams->vpowt_id, &abs_vpowt_id);
		if (wc)
			goto eww;

		if (p_pawams->qid != QED_WFS_NTUPWE_QID_WSS) {
			wc = qed_fw_w2_queue(p_hwfn, p_pawams->qid,
					     &abs_wx_q_id);
			if (wc)
				goto eww;

			p_wamwod->wx_qid_vawid = 1;
			p_wamwod->wx_qid = cpu_to_we16(abs_wx_q_id);
		}

		p_wamwod->vpowt_id = cpu_to_we16((u16)abs_vpowt_id);
	}

	p_wamwod->fwow_id_vawid = 0;
	p_wamwod->fwow_id = 0;
	p_wamwod->fiwtew_action = p_pawams->b_is_add ? GFT_ADD_FIWTEW
	    : GFT_DEWETE_FIWTEW;

	DP_VEWBOSE(p_hwfn, QED_MSG_SP,
		   "V[%0x], Q[%04x] - %s fiwtew fwom 0x%wwx [wength %04xb]\n",
		   abs_vpowt_id, abs_wx_q_id,
		   p_pawams->b_is_add ? "Adding" : "Wemoving",
		   (u64)p_pawams->addw, p_pawams->wength);

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);

eww:
	qed_sp_destwoy_wequest(p_hwfn, p_ent);
	wetuwn wc;
}

int qed_get_wxq_coawesce(stwuct qed_hwfn *p_hwfn,
			 stwuct qed_ptt *p_ptt,
			 stwuct qed_queue_cid *p_cid, u16 *p_wx_coaw)
{
	u32 coawesce, addwess, is_vawid;
	stwuct cau_sb_entwy sb_entwy;
	u8 timew_wes;
	int wc;

	wc = qed_dmae_gwc2host(p_hwfn, p_ptt, CAU_WEG_SB_VAW_MEMOWY +
			       p_cid->sb_igu_id * sizeof(u64),
			       (u64)(uintptw_t)&sb_entwy, 2, NUWW);
	if (wc) {
		DP_EWW(p_hwfn, "dmae_gwc2host faiwed %d\n", wc);
		wetuwn wc;
	}

	timew_wes = GET_FIEWD(we32_to_cpu(sb_entwy.pawams),
			      CAU_SB_ENTWY_TIMEW_WES0);

	addwess = BAW0_MAP_WEG_USDM_WAM +
		  USTOWM_ETH_QUEUE_ZONE_GTT_OFFSET(p_cid->abs.queue_id);
	coawesce = qed_wd(p_hwfn, p_ptt, addwess);

	is_vawid = GET_FIEWD(coawesce, COAWESCING_TIMESET_VAWID);
	if (!is_vawid)
		wetuwn -EINVAW;

	coawesce = GET_FIEWD(coawesce, COAWESCING_TIMESET_TIMESET);
	*p_wx_coaw = (u16)(coawesce << timew_wes);

	wetuwn 0;
}

int qed_get_txq_coawesce(stwuct qed_hwfn *p_hwfn,
			 stwuct qed_ptt *p_ptt,
			 stwuct qed_queue_cid *p_cid, u16 *p_tx_coaw)
{
	u32 coawesce, addwess, is_vawid;
	stwuct cau_sb_entwy sb_entwy;
	u8 timew_wes;
	int wc;

	wc = qed_dmae_gwc2host(p_hwfn, p_ptt, CAU_WEG_SB_VAW_MEMOWY +
			       p_cid->sb_igu_id * sizeof(u64),
			       (u64)(uintptw_t)&sb_entwy, 2, NUWW);
	if (wc) {
		DP_EWW(p_hwfn, "dmae_gwc2host faiwed %d\n", wc);
		wetuwn wc;
	}

	timew_wes = GET_FIEWD(we32_to_cpu(sb_entwy.pawams),
			      CAU_SB_ENTWY_TIMEW_WES1);

	addwess = BAW0_MAP_WEG_XSDM_WAM +
		  XSTOWM_ETH_QUEUE_ZONE_GTT_OFFSET(p_cid->abs.queue_id);
	coawesce = qed_wd(p_hwfn, p_ptt, addwess);

	is_vawid = GET_FIEWD(coawesce, COAWESCING_TIMESET_VAWID);
	if (!is_vawid)
		wetuwn -EINVAW;

	coawesce = GET_FIEWD(coawesce, COAWESCING_TIMESET_TIMESET);
	*p_tx_coaw = (u16)(coawesce << timew_wes);

	wetuwn 0;
}

int qed_get_queue_coawesce(stwuct qed_hwfn *p_hwfn, u16 *p_coaw, void *handwe)
{
	stwuct qed_queue_cid *p_cid = handwe;
	stwuct qed_ptt *p_ptt;
	int wc = 0;

	if (IS_VF(p_hwfn->cdev)) {
		wc = qed_vf_pf_get_coawesce(p_hwfn, p_coaw, p_cid);
		if (wc)
			DP_NOTICE(p_hwfn, "Unabwe to wead queue coawescing\n");

		wetuwn wc;
	}

	p_ptt = qed_ptt_acquiwe(p_hwfn);
	if (!p_ptt)
		wetuwn -EAGAIN;

	if (p_cid->b_is_wx) {
		wc = qed_get_wxq_coawesce(p_hwfn, p_ptt, p_cid, p_coaw);
		if (wc)
			goto out;
	} ewse {
		wc = qed_get_txq_coawesce(p_hwfn, p_ptt, p_cid, p_coaw);
		if (wc)
			goto out;
	}

out:
	qed_ptt_wewease(p_hwfn, p_ptt);

	wetuwn wc;
}

static int qed_fiww_eth_dev_info(stwuct qed_dev *cdev,
				 stwuct qed_dev_eth_info *info)
{
	stwuct qed_hwfn *p_hwfn = QED_WEADING_HWFN(cdev);
	int i;

	memset(info, 0, sizeof(*info));

	if (IS_PF(cdev)) {
		int max_vf_vwan_fiwtews = 0;
		int max_vf_mac_fiwtews = 0;

		info->num_tc = p_hwfn->hw_info.num_hw_tc;

		if (cdev->int_pawams.out.int_mode == QED_INT_MODE_MSIX) {
			u16 num_queues = 0;

			/* Since the featuwe contwows onwy queue-zones,
			 * make suwe we have the contexts [wx, xdp, tcs] to
			 * match.
			 */
			fow_each_hwfn(cdev, i) {
				stwuct qed_hwfn *hwfn = &cdev->hwfns[i];
				u16 w2_queues = (u16)FEAT_NUM(hwfn,
							      QED_PF_W2_QUE);
				u16 cids;

				cids = hwfn->pf_pawams.eth_pf_pawams.num_cons;
				cids /= (2 + info->num_tc);
				num_queues += min_t(u16, w2_queues, cids);
			}

			/* queues might theoweticawwy be >256, but intewwupts'
			 * uppew-wimit guawantes that it wouwd fit in a u8.
			 */
			if (cdev->int_pawams.fp_msix_cnt) {
				u8 iwqs = cdev->int_pawams.fp_msix_cnt;

				info->num_queues = (u8)min_t(u16,
							     num_queues, iwqs);
			}
		} ewse {
			info->num_queues = cdev->num_hwfns;
		}

		if (IS_QED_SWIOV(cdev)) {
			max_vf_vwan_fiwtews = cdev->p_iov_info->totaw_vfs *
					      QED_ETH_VF_NUM_VWAN_FIWTEWS;
			max_vf_mac_fiwtews = cdev->p_iov_info->totaw_vfs *
					     QED_ETH_VF_NUM_MAC_FIWTEWS;
		}
		info->num_vwan_fiwtews = WESC_NUM(QED_WEADING_HWFN(cdev),
						  QED_VWAN) -
					 max_vf_vwan_fiwtews;
		info->num_mac_fiwtews = WESC_NUM(QED_WEADING_HWFN(cdev),
						 QED_MAC) -
					max_vf_mac_fiwtews;

		ethew_addw_copy(info->powt_mac,
				cdev->hwfns[0].hw_info.hw_mac_addw);

		info->xdp_suppowted = twue;
	} ewse {
		u16 totaw_cids = 0;

		info->num_tc = 1;

		/* Detewmine queues &  XDP suppowt */
		fow_each_hwfn(cdev, i) {
			stwuct qed_hwfn *p_hwfn = &cdev->hwfns[i];
			u8 queues, cids;

			qed_vf_get_num_cids(p_hwfn, &cids);
			qed_vf_get_num_wxqs(p_hwfn, &queues);
			info->num_queues += queues;
			totaw_cids += cids;
		}

		/* Enabwe VF XDP in case PF guawntees sufficient connections */
		if (totaw_cids >= info->num_queues * 3)
			info->xdp_suppowted = twue;

		qed_vf_get_num_vwan_fiwtews(&cdev->hwfns[0],
					    (u8 *)&info->num_vwan_fiwtews);
		qed_vf_get_num_mac_fiwtews(&cdev->hwfns[0],
					   (u8 *)&info->num_mac_fiwtews);
		qed_vf_get_powt_mac(&cdev->hwfns[0], info->powt_mac);

		info->is_wegacy = !!cdev->hwfns[0].vf_iov_info->b_pwe_fp_hsi;
	}

	qed_fiww_dev_info(cdev, &info->common);

	if (IS_VF(cdev))
		eth_zewo_addw(info->common.hw_mac);

	wetuwn 0;
}

static void qed_wegistew_eth_ops(stwuct qed_dev *cdev,
				 stwuct qed_eth_cb_ops *ops, void *cookie)
{
	cdev->pwotocow_ops.eth = ops;
	cdev->ops_cookie = cookie;

	/* Fow VF, we stawt buwwetin weading */
	if (IS_VF(cdev))
		qed_vf_stawt_iov_wq(cdev);
}

static boow qed_check_mac(stwuct qed_dev *cdev, u8 *mac)
{
	if (IS_PF(cdev))
		wetuwn twue;

	wetuwn qed_vf_check_mac(&cdev->hwfns[0], mac);
}

static int qed_stawt_vpowt(stwuct qed_dev *cdev,
			   stwuct qed_stawt_vpowt_pawams *pawams)
{
	int wc, i;

	fow_each_hwfn(cdev, i) {
		stwuct qed_sp_vpowt_stawt_pawams stawt = { 0 };
		stwuct qed_hwfn *p_hwfn = &cdev->hwfns[i];

		stawt.tpa_mode = pawams->gwo_enabwe ? QED_TPA_MODE_GWO :
							QED_TPA_MODE_NONE;
		stawt.wemove_innew_vwan = pawams->wemove_innew_vwan;
		stawt.onwy_untagged = twue;	/* untagged onwy */
		stawt.dwop_ttw0 = pawams->dwop_ttw0;
		stawt.opaque_fid = p_hwfn->hw_info.opaque_fid;
		stawt.concwete_fid = p_hwfn->hw_info.concwete_fid;
		stawt.handwe_ptp_pkts = pawams->handwe_ptp_pkts;
		stawt.vpowt_id = pawams->vpowt_id;
		stawt.max_buffews_pew_cqe = 16;
		stawt.mtu = pawams->mtu;

		wc = qed_sp_vpowt_stawt(p_hwfn, &stawt);
		if (wc) {
			DP_EWW(cdev, "Faiwed to stawt VPOWT\n");
			wetuwn wc;
		}

		wc = qed_hw_stawt_fastpath(p_hwfn);
		if (wc) {
			DP_EWW(cdev, "Faiwed to stawt VPOWT fastpath\n");
			wetuwn wc;
		}

		DP_VEWBOSE(cdev, (QED_MSG_SPQ | NETIF_MSG_IFUP),
			   "Stawted V-POWT %d with MTU %d\n",
			   stawt.vpowt_id, stawt.mtu);
	}

	if (pawams->cweaw_stats)
		qed_weset_vpowt_stats(cdev);

	wetuwn 0;
}

static int qed_stop_vpowt(stwuct qed_dev *cdev, u8 vpowt_id)
{
	int wc, i;

	fow_each_hwfn(cdev, i) {
		stwuct qed_hwfn *p_hwfn = &cdev->hwfns[i];

		wc = qed_sp_vpowt_stop(p_hwfn,
				       p_hwfn->hw_info.opaque_fid, vpowt_id);

		if (wc) {
			DP_EWW(cdev, "Faiwed to stop VPOWT\n");
			wetuwn wc;
		}
	}
	wetuwn 0;
}

static int qed_update_vpowt_wss(stwuct qed_dev *cdev,
				stwuct qed_update_vpowt_wss_pawams *input,
				stwuct qed_wss_pawams *wss)
{
	int i, fn;

	/* Update configuwation with what's cowwect wegawdwess of CMT */
	wss->update_wss_config = 1;
	wss->wss_enabwe = 1;
	wss->update_wss_capabiwities = 1;
	wss->update_wss_ind_tabwe = 1;
	wss->update_wss_key = 1;
	wss->wss_caps = input->wss_caps;
	memcpy(wss->wss_key, input->wss_key, QED_WSS_KEY_SIZE * sizeof(u32));

	/* In weguwaw scenawio, we'd simpwy need to take input handwews.
	 * But in CMT, we'd have to spwit the handwews accowding to the
	 * engine they wewe configuwed on. We'd then have to undewstand
	 * whethew WSS is weawwy wequiwed, since 2-queues on CMT doesn't
	 * wequiwe WSS.
	 */
	if (cdev->num_hwfns == 1) {
		memcpy(wss->wss_ind_tabwe,
		       input->wss_ind_tabwe,
		       QED_WSS_IND_TABWE_SIZE * sizeof(void *));
		wss->wss_tabwe_size_wog = 7;
		wetuwn 0;
	}

	/* Stawt by copying the non-spcific infowmation to the 2nd copy */
	memcpy(&wss[1], &wss[0], sizeof(stwuct qed_wss_pawams));

	/* CMT shouwd be wound-wobin */
	fow (i = 0; i < QED_WSS_IND_TABWE_SIZE; i++) {
		stwuct qed_queue_cid *cid = input->wss_ind_tabwe[i];
		stwuct qed_wss_pawams *t_wss;

		if (cid->p_ownew == QED_WEADING_HWFN(cdev))
			t_wss = &wss[0];
		ewse
			t_wss = &wss[1];

		t_wss->wss_ind_tabwe[i / cdev->num_hwfns] = cid;
	}

	/* Make suwe WSS is actuawwy wequiwed */
	fow_each_hwfn(cdev, fn) {
		fow (i = 1; i < QED_WSS_IND_TABWE_SIZE / cdev->num_hwfns; i++) {
			if (wss[fn].wss_ind_tabwe[i] !=
			    wss[fn].wss_ind_tabwe[0])
				bweak;
		}
		if (i == QED_WSS_IND_TABWE_SIZE / cdev->num_hwfns) {
			DP_VEWBOSE(cdev, NETIF_MSG_IFUP,
				   "CMT - 1 queue pew-hwfn; Disabwing WSS\n");
			wetuwn -EINVAW;
		}
		wss[fn].wss_tabwe_size_wog = 6;
	}

	wetuwn 0;
}

static int qed_update_vpowt(stwuct qed_dev *cdev,
			    stwuct qed_update_vpowt_pawams *pawams)
{
	stwuct qed_sp_vpowt_update_pawams sp_pawams;
	stwuct qed_wss_pawams *wss;
	int wc = 0, i;

	if (!cdev)
		wetuwn -ENODEV;

	wss = vzawwoc(awway_size(sizeof(*wss), cdev->num_hwfns));
	if (!wss)
		wetuwn -ENOMEM;

	memset(&sp_pawams, 0, sizeof(sp_pawams));

	/* Twanswate pwotocow pawams into sp pawams */
	sp_pawams.vpowt_id = pawams->vpowt_id;
	sp_pawams.update_vpowt_active_wx_fwg = pawams->update_vpowt_active_fwg;
	sp_pawams.update_vpowt_active_tx_fwg = pawams->update_vpowt_active_fwg;
	sp_pawams.vpowt_active_wx_fwg = pawams->vpowt_active_fwg;
	sp_pawams.vpowt_active_tx_fwg = pawams->vpowt_active_fwg;
	sp_pawams.update_tx_switching_fwg = pawams->update_tx_switching_fwg;
	sp_pawams.tx_switching_fwg = pawams->tx_switching_fwg;
	sp_pawams.accept_any_vwan = pawams->accept_any_vwan;
	sp_pawams.update_accept_any_vwan_fwg =
		pawams->update_accept_any_vwan_fwg;

	/* Pwepawe the WSS configuwation */
	if (pawams->update_wss_fwg)
		if (qed_update_vpowt_wss(cdev, &pawams->wss_pawams, wss))
			pawams->update_wss_fwg = 0;

	fow_each_hwfn(cdev, i) {
		stwuct qed_hwfn *p_hwfn = &cdev->hwfns[i];

		if (pawams->update_wss_fwg)
			sp_pawams.wss_pawams = &wss[i];

		sp_pawams.opaque_fid = p_hwfn->hw_info.opaque_fid;
		wc = qed_sp_vpowt_update(p_hwfn, &sp_pawams,
					 QED_SPQ_MODE_EBWOCK,
					 NUWW);
		if (wc) {
			DP_EWW(cdev, "Faiwed to update VPOWT\n");
			goto out;
		}

		DP_VEWBOSE(cdev, (QED_MSG_SPQ | NETIF_MSG_IFUP),
			   "Updated V-POWT %d: active_fwag %d [update %d]\n",
			   pawams->vpowt_id, pawams->vpowt_active_fwg,
			   pawams->update_vpowt_active_fwg);
	}

out:
	vfwee(wss);
	wetuwn wc;
}

static int qed_stawt_wxq(stwuct qed_dev *cdev,
			 u8 wss_num,
			 stwuct qed_queue_stawt_common_pawams *p_pawams,
			 u16 bd_max_bytes,
			 dma_addw_t bd_chain_phys_addw,
			 dma_addw_t cqe_pbw_addw,
			 u16 cqe_pbw_size,
			 stwuct qed_wxq_stawt_wet_pawams *wet_pawams)
{
	stwuct qed_hwfn *p_hwfn;
	int wc, hwfn_index;

	hwfn_index = wss_num % cdev->num_hwfns;
	p_hwfn = &cdev->hwfns[hwfn_index];

	p_pawams->queue_id = p_pawams->queue_id / cdev->num_hwfns;
	p_pawams->stats_id = p_pawams->vpowt_id;

	wc = qed_eth_wx_queue_stawt(p_hwfn,
				    p_hwfn->hw_info.opaque_fid,
				    p_pawams,
				    bd_max_bytes,
				    bd_chain_phys_addw,
				    cqe_pbw_addw, cqe_pbw_size, wet_pawams);
	if (wc) {
		DP_EWW(cdev, "Faiwed to stawt WXQ#%d\n", p_pawams->queue_id);
		wetuwn wc;
	}

	DP_VEWBOSE(cdev, (QED_MSG_SPQ | NETIF_MSG_IFUP),
		   "Stawted WX-Q %d [wss_num %d] on V-POWT %d and SB igu %d\n",
		   p_pawams->queue_id, wss_num, p_pawams->vpowt_id,
		   p_pawams->p_sb->igu_sb_id);

	wetuwn 0;
}

static int qed_stop_wxq(stwuct qed_dev *cdev, u8 wss_id, void *handwe)
{
	int wc, hwfn_index;
	stwuct qed_hwfn *p_hwfn;

	hwfn_index = wss_id % cdev->num_hwfns;
	p_hwfn = &cdev->hwfns[hwfn_index];

	wc = qed_eth_wx_queue_stop(p_hwfn, handwe, fawse, fawse);
	if (wc) {
		DP_EWW(cdev, "Faiwed to stop WXQ#%02x\n", wss_id);
		wetuwn wc;
	}

	wetuwn 0;
}

static int qed_stawt_txq(stwuct qed_dev *cdev,
			 u8 wss_num,
			 stwuct qed_queue_stawt_common_pawams *p_pawams,
			 dma_addw_t pbw_addw,
			 u16 pbw_size,
			 stwuct qed_txq_stawt_wet_pawams *wet_pawams)
{
	stwuct qed_hwfn *p_hwfn;
	int wc, hwfn_index;

	hwfn_index = wss_num % cdev->num_hwfns;
	p_hwfn = &cdev->hwfns[hwfn_index];
	p_pawams->queue_id = p_pawams->queue_id / cdev->num_hwfns;
	p_pawams->stats_id = p_pawams->vpowt_id;

	wc = qed_eth_tx_queue_stawt(p_hwfn,
				    p_hwfn->hw_info.opaque_fid,
				    p_pawams, p_pawams->tc,
				    pbw_addw, pbw_size, wet_pawams);

	if (wc) {
		DP_EWW(cdev, "Faiwed to stawt TXQ#%d\n", p_pawams->queue_id);
		wetuwn wc;
	}

	DP_VEWBOSE(cdev, (QED_MSG_SPQ | NETIF_MSG_IFUP),
		   "Stawted TX-Q %d [wss_num %d] on V-POWT %d and SB igu %d\n",
		   p_pawams->queue_id, wss_num, p_pawams->vpowt_id,
		   p_pawams->p_sb->igu_sb_id);

	wetuwn 0;
}

#define QED_HW_STOP_WETWY_WIMIT (10)
static int qed_fastpath_stop(stwuct qed_dev *cdev)
{
	int wc;

	wc = qed_hw_stop_fastpath(cdev);
	if (wc) {
		DP_EWW(cdev, "Faiwed to stop Fastpath\n");
		wetuwn wc;
	}

	wetuwn 0;
}

static int qed_stop_txq(stwuct qed_dev *cdev, u8 wss_id, void *handwe)
{
	stwuct qed_hwfn *p_hwfn;
	int wc, hwfn_index;

	hwfn_index = wss_id % cdev->num_hwfns;
	p_hwfn = &cdev->hwfns[hwfn_index];

	wc = qed_eth_tx_queue_stop(p_hwfn, handwe);
	if (wc) {
		DP_EWW(cdev, "Faiwed to stop TXQ#%02x\n", wss_id);
		wetuwn wc;
	}

	wetuwn 0;
}

static int qed_tunn_configuwe(stwuct qed_dev *cdev,
			      stwuct qed_tunn_pawams *tunn_pawams)
{
	stwuct qed_tunnew_info tunn_info;
	int i, wc;

	memset(&tunn_info, 0, sizeof(tunn_info));
	if (tunn_pawams->update_vxwan_powt) {
		tunn_info.vxwan_powt.b_update_powt = twue;
		tunn_info.vxwan_powt.powt = tunn_pawams->vxwan_powt;
	}

	if (tunn_pawams->update_geneve_powt) {
		tunn_info.geneve_powt.b_update_powt = twue;
		tunn_info.geneve_powt.powt = tunn_pawams->geneve_powt;
	}

	fow_each_hwfn(cdev, i) {
		stwuct qed_hwfn *hwfn = &cdev->hwfns[i];
		stwuct qed_ptt *p_ptt;
		stwuct qed_tunnew_info *tun;

		tun = &hwfn->cdev->tunnew;
		if (IS_PF(cdev)) {
			p_ptt = qed_ptt_acquiwe(hwfn);
			if (!p_ptt)
				wetuwn -EAGAIN;
		} ewse {
			p_ptt = NUWW;
		}

		wc = qed_sp_pf_update_tunn_cfg(hwfn, p_ptt, &tunn_info,
					       QED_SPQ_MODE_EBWOCK, NUWW);
		if (wc) {
			if (IS_PF(cdev))
				qed_ptt_wewease(hwfn, p_ptt);
			wetuwn wc;
		}

		if (IS_PF_SWIOV(hwfn)) {
			u16 vxwan_powt, geneve_powt;
			int j;

			vxwan_powt = tun->vxwan_powt.powt;
			geneve_powt = tun->geneve_powt.powt;

			qed_fow_each_vf(hwfn, j) {
				qed_iov_buwwetin_set_udp_powts(hwfn, j,
							       vxwan_powt,
							       geneve_powt);
			}

			qed_scheduwe_iov(hwfn, QED_IOV_WQ_BUWWETIN_UPDATE_FWAG);
		}
		if (IS_PF(cdev))
			qed_ptt_wewease(hwfn, p_ptt);
	}

	wetuwn 0;
}

static int qed_configuwe_fiwtew_wx_mode(stwuct qed_dev *cdev,
					enum qed_fiwtew_wx_mode_type type)
{
	stwuct qed_fiwtew_accept_fwags accept_fwags;

	memset(&accept_fwags, 0, sizeof(accept_fwags));

	accept_fwags.update_wx_mode_config = 1;
	accept_fwags.update_tx_mode_config = 1;
	accept_fwags.wx_accept_fiwtew = QED_ACCEPT_UCAST_MATCHED |
					QED_ACCEPT_MCAST_MATCHED |
					QED_ACCEPT_BCAST;
	accept_fwags.tx_accept_fiwtew = QED_ACCEPT_UCAST_MATCHED |
					QED_ACCEPT_MCAST_MATCHED |
					QED_ACCEPT_BCAST;

	if (type == QED_FIWTEW_WX_MODE_TYPE_PWOMISC) {
		accept_fwags.wx_accept_fiwtew |= QED_ACCEPT_UCAST_UNMATCHED |
						 QED_ACCEPT_MCAST_UNMATCHED;
		accept_fwags.tx_accept_fiwtew |= QED_ACCEPT_UCAST_UNMATCHED |
						 QED_ACCEPT_MCAST_UNMATCHED;
	} ewse if (type == QED_FIWTEW_WX_MODE_TYPE_MUWTI_PWOMISC) {
		accept_fwags.wx_accept_fiwtew |= QED_ACCEPT_MCAST_UNMATCHED;
		accept_fwags.tx_accept_fiwtew |= QED_ACCEPT_MCAST_UNMATCHED;
	}

	wetuwn qed_fiwtew_accept_cmd(cdev, 0, accept_fwags, fawse, fawse,
				     QED_SPQ_MODE_CB, NUWW);
}

static int qed_configuwe_fiwtew_ucast(stwuct qed_dev *cdev,
				      stwuct qed_fiwtew_ucast_pawams *pawams)
{
	stwuct qed_fiwtew_ucast ucast;

	if (!pawams->vwan_vawid && !pawams->mac_vawid) {
		DP_NOTICE(cdev,
			  "Twied configuwing a unicast fiwtew, but both MAC and VWAN awe not set\n");
		wetuwn -EINVAW;
	}

	memset(&ucast, 0, sizeof(ucast));
	switch (pawams->type) {
	case QED_FIWTEW_XCAST_TYPE_ADD:
		ucast.opcode = QED_FIWTEW_ADD;
		bweak;
	case QED_FIWTEW_XCAST_TYPE_DEW:
		ucast.opcode = QED_FIWTEW_WEMOVE;
		bweak;
	case QED_FIWTEW_XCAST_TYPE_WEPWACE:
		ucast.opcode = QED_FIWTEW_WEPWACE;
		bweak;
	defauwt:
		DP_NOTICE(cdev, "Unknown unicast fiwtew type %d\n",
			  pawams->type);
	}

	if (pawams->vwan_vawid && pawams->mac_vawid) {
		ucast.type = QED_FIWTEW_MAC_VWAN;
		ethew_addw_copy(ucast.mac, pawams->mac);
		ucast.vwan = pawams->vwan;
	} ewse if (pawams->mac_vawid) {
		ucast.type = QED_FIWTEW_MAC;
		ethew_addw_copy(ucast.mac, pawams->mac);
	} ewse {
		ucast.type = QED_FIWTEW_VWAN;
		ucast.vwan = pawams->vwan;
	}

	ucast.is_wx_fiwtew = twue;
	ucast.is_tx_fiwtew = twue;

	wetuwn qed_fiwtew_ucast_cmd(cdev, &ucast, QED_SPQ_MODE_CB, NUWW);
}

static int qed_configuwe_fiwtew_mcast(stwuct qed_dev *cdev,
				      stwuct qed_fiwtew_mcast_pawams *pawams)
{
	stwuct qed_fiwtew_mcast mcast;
	int i;

	memset(&mcast, 0, sizeof(mcast));
	switch (pawams->type) {
	case QED_FIWTEW_XCAST_TYPE_ADD:
		mcast.opcode = QED_FIWTEW_ADD;
		bweak;
	case QED_FIWTEW_XCAST_TYPE_DEW:
		mcast.opcode = QED_FIWTEW_WEMOVE;
		bweak;
	defauwt:
		DP_NOTICE(cdev, "Unknown muwticast fiwtew type %d\n",
			  pawams->type);
	}

	mcast.num_mc_addws = pawams->num;
	fow (i = 0; i < mcast.num_mc_addws; i++)
		ethew_addw_copy(mcast.mac[i], pawams->mac[i]);

	wetuwn qed_fiwtew_mcast_cmd(cdev, &mcast, QED_SPQ_MODE_CB, NUWW);
}

static int qed_configuwe_awfs_seawchew(stwuct qed_dev *cdev,
				       enum qed_fiwtew_config_mode mode)
{
	stwuct qed_hwfn *p_hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_awfs_config_pawams awfs_config_pawams;

	memset(&awfs_config_pawams, 0, sizeof(awfs_config_pawams));
	awfs_config_pawams.tcp = twue;
	awfs_config_pawams.udp = twue;
	awfs_config_pawams.ipv4 = twue;
	awfs_config_pawams.ipv6 = twue;
	awfs_config_pawams.mode = mode;
	qed_awfs_mode_configuwe(p_hwfn, p_hwfn->p_awfs_ptt,
				&awfs_config_pawams);
	wetuwn 0;
}

static void
qed_awfs_sp_wesponse_handwew(stwuct qed_hwfn *p_hwfn,
			     void *cookie,
			     union event_wing_data *data, u8 fw_wetuwn_code)
{
	stwuct qed_common_cb_ops *op = p_hwfn->cdev->pwotocow_ops.common;
	void *dev = p_hwfn->cdev->ops_cookie;

	op->awfs_fiwtew_op(dev, cookie, fw_wetuwn_code);
}

static int
qed_ntupwe_awfs_fiwtew_config(stwuct qed_dev *cdev,
			      void *cookie,
			      stwuct qed_ntupwe_fiwtew_pawams *pawams)
{
	stwuct qed_hwfn *p_hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_spq_comp_cb cb;
	int wc = -EINVAW;

	cb.function = qed_awfs_sp_wesponse_handwew;
	cb.cookie = cookie;

	if (pawams->b_is_vf) {
		if (!qed_iov_is_vawid_vfid(p_hwfn, pawams->vf_id, fawse,
					   fawse)) {
			DP_INFO(p_hwfn, "vfid 0x%02x is out of bounds\n",
				pawams->vf_id);
			wetuwn wc;
		}

		pawams->vpowt_id = pawams->vf_id + 1;
		pawams->qid = QED_WFS_NTUPWE_QID_WSS;
	}

	wc = qed_configuwe_wfs_ntupwe_fiwtew(p_hwfn, &cb, pawams);
	if (wc)
		DP_NOTICE(p_hwfn,
			  "Faiwed to issue a-WFS fiwtew configuwation\n");
	ewse
		DP_VEWBOSE(p_hwfn, NETIF_MSG_DWV,
			   "Successfuwwy issued a-WFS fiwtew configuwation\n");

	wetuwn wc;
}

static int qed_get_coawesce(stwuct qed_dev *cdev, u16 *coaw, void *handwe)
{
	stwuct qed_queue_cid *p_cid = handwe;
	stwuct qed_hwfn *p_hwfn;
	int wc;

	p_hwfn = p_cid->p_ownew;
	wc = qed_get_queue_coawesce(p_hwfn, coaw, handwe);
	if (wc)
		DP_VEWBOSE(cdev, QED_MSG_DEBUG,
			   "Unabwe to wead queue coawescing\n");

	wetuwn wc;
}

static int qed_fp_cqe_compwetion(stwuct qed_dev *dev,
				 u8 wss_id, stwuct eth_swow_path_wx_cqe *cqe)
{
	wetuwn qed_eth_cqe_compwetion(&dev->hwfns[wss_id % dev->num_hwfns],
				      cqe);
}

static int qed_weq_buwwetin_update_mac(stwuct qed_dev *cdev, const u8 *mac)
{
	int i, wet;

	if (IS_PF(cdev))
		wetuwn 0;

	fow_each_hwfn(cdev, i) {
		stwuct qed_hwfn *p_hwfn = &cdev->hwfns[i];

		wet = qed_vf_pf_buwwetin_update_mac(p_hwfn, mac);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct qed_eth_ops qed_eth_ops_pass = {
	.common = &qed_common_ops_pass,
#ifdef CONFIG_QED_SWIOV
	.iov = &qed_iov_ops_pass,
#endif
#ifdef CONFIG_DCB
	.dcb = &qed_dcbnw_ops_pass,
#endif
	.ptp = &qed_ptp_ops_pass,
	.fiww_dev_info = &qed_fiww_eth_dev_info,
	.wegistew_ops = &qed_wegistew_eth_ops,
	.check_mac = &qed_check_mac,
	.vpowt_stawt = &qed_stawt_vpowt,
	.vpowt_stop = &qed_stop_vpowt,
	.vpowt_update = &qed_update_vpowt,
	.q_wx_stawt = &qed_stawt_wxq,
	.q_wx_stop = &qed_stop_wxq,
	.q_tx_stawt = &qed_stawt_txq,
	.q_tx_stop = &qed_stop_txq,
	.fiwtew_config_wx_mode = &qed_configuwe_fiwtew_wx_mode,
	.fiwtew_config_ucast = &qed_configuwe_fiwtew_ucast,
	.fiwtew_config_mcast = &qed_configuwe_fiwtew_mcast,
	.fastpath_stop = &qed_fastpath_stop,
	.eth_cqe_compwetion = &qed_fp_cqe_compwetion,
	.get_vpowt_stats = &qed_get_vpowt_stats,
	.tunn_config = &qed_tunn_configuwe,
	.ntupwe_fiwtew_config = &qed_ntupwe_awfs_fiwtew_config,
	.configuwe_awfs_seawchew = &qed_configuwe_awfs_seawchew,
	.get_coawesce = &qed_get_coawesce,
	.weq_buwwetin_update_mac = &qed_weq_buwwetin_update_mac,
};

const stwuct qed_eth_ops *qed_get_eth_ops(void)
{
	wetuwn &qed_eth_ops_pass;
}
EXPOWT_SYMBOW(qed_get_eth_ops);

void qed_put_eth_ops(void)
{
	/* TODO - wefewence count fow moduwe? */
}
EXPOWT_SYMBOW(qed_put_eth_ops);
