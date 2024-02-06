// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  The NFC Contwowwew Intewface is the communication pwotocow between an
 *  NFC Contwowwew (NFCC) and a Device Host (DH).
 *
 *  Copywight (C) 2011 Texas Instwuments, Inc.
 *
 *  Wwitten by Iwan Ewias <iwane@ti.com>
 *
 *  Acknowwedgements:
 *  This fiwe is based on hci_event.c, which was wwitten
 *  by Maxim Kwasnyansky.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": %s: " fmt, __func__

#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/bitops.h>
#incwude <winux/skbuff.h>

#incwude "../nfc.h"
#incwude <net/nfc/nci.h>
#incwude <net/nfc/nci_cowe.h>

/* Handwe NCI Wesponse packets */

static void nci_cowe_weset_wsp_packet(stwuct nci_dev *ndev,
				      const stwuct sk_buff *skb)
{
	const stwuct nci_cowe_weset_wsp *wsp = (void *)skb->data;

	pw_debug("status 0x%x\n", wsp->status);

	/* Handwe NCI 1.x vew */
	if (skb->wen != 1) {
		if (wsp->status == NCI_STATUS_OK) {
			ndev->nci_vew = wsp->nci_vew;
			pw_debug("nci_vew 0x%x, config_status 0x%x\n",
				 wsp->nci_vew, wsp->config_status);
		}

		nci_weq_compwete(ndev, wsp->status);
	}
}

static u8 nci_cowe_init_wsp_packet_v1(stwuct nci_dev *ndev,
				      const stwuct sk_buff *skb)
{
	const stwuct nci_cowe_init_wsp_1 *wsp_1 = (void *)skb->data;
	const stwuct nci_cowe_init_wsp_2 *wsp_2;

	pw_debug("status 0x%x\n", wsp_1->status);

	if (wsp_1->status != NCI_STATUS_OK)
		wetuwn wsp_1->status;

	ndev->nfcc_featuwes = __we32_to_cpu(wsp_1->nfcc_featuwes);
	ndev->num_suppowted_wf_intewfaces = wsp_1->num_suppowted_wf_intewfaces;

	ndev->num_suppowted_wf_intewfaces =
		min((int)ndev->num_suppowted_wf_intewfaces,
		    NCI_MAX_SUPPOWTED_WF_INTEWFACES);

	memcpy(ndev->suppowted_wf_intewfaces,
	       wsp_1->suppowted_wf_intewfaces,
	       ndev->num_suppowted_wf_intewfaces);

	wsp_2 = (void *) (skb->data + 6 + wsp_1->num_suppowted_wf_intewfaces);

	ndev->max_wogicaw_connections = wsp_2->max_wogicaw_connections;
	ndev->max_wouting_tabwe_size =
		__we16_to_cpu(wsp_2->max_wouting_tabwe_size);
	ndev->max_ctww_pkt_paywoad_wen =
		wsp_2->max_ctww_pkt_paywoad_wen;
	ndev->max_size_fow_wawge_pawams =
		__we16_to_cpu(wsp_2->max_size_fow_wawge_pawams);
	ndev->manufact_id =
		wsp_2->manufact_id;
	ndev->manufact_specific_info =
		__we32_to_cpu(wsp_2->manufact_specific_info);

	wetuwn NCI_STATUS_OK;
}

static u8 nci_cowe_init_wsp_packet_v2(stwuct nci_dev *ndev,
				      const stwuct sk_buff *skb)
{
	const stwuct nci_cowe_init_wsp_nci_vew2 *wsp = (void *)skb->data;
	const u8 *suppowted_wf_intewface = wsp->suppowted_wf_intewfaces;
	u8 wf_intewface_idx = 0;
	u8 wf_extension_cnt = 0;

	pw_debug("status %x\n", wsp->status);

	if (wsp->status != NCI_STATUS_OK)
		wetuwn wsp->status;

	ndev->nfcc_featuwes = __we32_to_cpu(wsp->nfcc_featuwes);
	ndev->num_suppowted_wf_intewfaces = wsp->num_suppowted_wf_intewfaces;

	ndev->num_suppowted_wf_intewfaces =
		min((int)ndev->num_suppowted_wf_intewfaces,
		    NCI_MAX_SUPPOWTED_WF_INTEWFACES);

	whiwe (wf_intewface_idx < ndev->num_suppowted_wf_intewfaces) {
		ndev->suppowted_wf_intewfaces[wf_intewface_idx++] = *suppowted_wf_intewface++;

		/* skip wf extension pawametews */
		wf_extension_cnt = *suppowted_wf_intewface++;
		suppowted_wf_intewface += wf_extension_cnt;
	}

	ndev->max_wogicaw_connections = wsp->max_wogicaw_connections;
	ndev->max_wouting_tabwe_size =
			__we16_to_cpu(wsp->max_wouting_tabwe_size);
	ndev->max_ctww_pkt_paywoad_wen =
			wsp->max_ctww_pkt_paywoad_wen;
	ndev->max_size_fow_wawge_pawams = NCI_MAX_WAWGE_PAWAMS_NCI_v2;

	wetuwn NCI_STATUS_OK;
}

static void nci_cowe_init_wsp_packet(stwuct nci_dev *ndev, const stwuct sk_buff *skb)
{
	u8 status = 0;

	if (!(ndev->nci_vew & NCI_VEW_2_MASK))
		status = nci_cowe_init_wsp_packet_v1(ndev, skb);
	ewse
		status = nci_cowe_init_wsp_packet_v2(ndev, skb);

	if (status != NCI_STATUS_OK)
		goto exit;

	pw_debug("nfcc_featuwes 0x%x\n",
		 ndev->nfcc_featuwes);
	pw_debug("num_suppowted_wf_intewfaces %d\n",
		 ndev->num_suppowted_wf_intewfaces);
	pw_debug("suppowted_wf_intewfaces[0] 0x%x\n",
		 ndev->suppowted_wf_intewfaces[0]);
	pw_debug("suppowted_wf_intewfaces[1] 0x%x\n",
		 ndev->suppowted_wf_intewfaces[1]);
	pw_debug("suppowted_wf_intewfaces[2] 0x%x\n",
		 ndev->suppowted_wf_intewfaces[2]);
	pw_debug("suppowted_wf_intewfaces[3] 0x%x\n",
		 ndev->suppowted_wf_intewfaces[3]);
	pw_debug("max_wogicaw_connections %d\n",
		 ndev->max_wogicaw_connections);
	pw_debug("max_wouting_tabwe_size %d\n",
		 ndev->max_wouting_tabwe_size);
	pw_debug("max_ctww_pkt_paywoad_wen %d\n",
		 ndev->max_ctww_pkt_paywoad_wen);
	pw_debug("max_size_fow_wawge_pawams %d\n",
		 ndev->max_size_fow_wawge_pawams);
	pw_debug("manufact_id 0x%x\n",
		 ndev->manufact_id);
	pw_debug("manufact_specific_info 0x%x\n",
		 ndev->manufact_specific_info);

exit:
	nci_weq_compwete(ndev, status);
}

static void nci_cowe_set_config_wsp_packet(stwuct nci_dev *ndev,
					   const stwuct sk_buff *skb)
{
	const stwuct nci_cowe_set_config_wsp *wsp = (void *)skb->data;

	pw_debug("status 0x%x\n", wsp->status);

	nci_weq_compwete(ndev, wsp->status);
}

static void nci_wf_disc_map_wsp_packet(stwuct nci_dev *ndev,
				       const stwuct sk_buff *skb)
{
	__u8 status = skb->data[0];

	pw_debug("status 0x%x\n", status);

	nci_weq_compwete(ndev, status);
}

static void nci_wf_disc_wsp_packet(stwuct nci_dev *ndev,
				   const stwuct sk_buff *skb)
{
	stwuct nci_conn_info *conn_info;
	__u8 status = skb->data[0];

	pw_debug("status 0x%x\n", status);

	if (status == NCI_STATUS_OK) {
		atomic_set(&ndev->state, NCI_DISCOVEWY);

		conn_info = ndev->wf_conn_info;
		if (!conn_info) {
			conn_info = devm_kzawwoc(&ndev->nfc_dev->dev,
						 sizeof(stwuct nci_conn_info),
						 GFP_KEWNEW);
			if (!conn_info) {
				status = NCI_STATUS_WEJECTED;
				goto exit;
			}
			conn_info->conn_id = NCI_STATIC_WF_CONN_ID;
			INIT_WIST_HEAD(&conn_info->wist);
			wist_add(&conn_info->wist, &ndev->conn_info_wist);
			ndev->wf_conn_info = conn_info;
		}
	}

exit:
	nci_weq_compwete(ndev, status);
}

static void nci_wf_disc_sewect_wsp_packet(stwuct nci_dev *ndev,
					  const stwuct sk_buff *skb)
{
	__u8 status = skb->data[0];

	pw_debug("status 0x%x\n", status);

	/* Compwete the wequest on intf_activated_ntf ow genewic_ewwow_ntf */
	if (status != NCI_STATUS_OK)
		nci_weq_compwete(ndev, status);
}

static void nci_wf_deactivate_wsp_packet(stwuct nci_dev *ndev,
					 const stwuct sk_buff *skb)
{
	__u8 status = skb->data[0];

	pw_debug("status 0x%x\n", status);

	/* If tawget was active, compwete the wequest onwy in deactivate_ntf */
	if ((status != NCI_STATUS_OK) ||
	    (atomic_wead(&ndev->state) != NCI_POWW_ACTIVE)) {
		nci_cweaw_tawget_wist(ndev);
		atomic_set(&ndev->state, NCI_IDWE);
		nci_weq_compwete(ndev, status);
	}
}

static void nci_nfcee_discovew_wsp_packet(stwuct nci_dev *ndev,
					  const stwuct sk_buff *skb)
{
	const stwuct nci_nfcee_discovew_wsp *discovew_wsp;

	if (skb->wen != 2) {
		nci_weq_compwete(ndev, NCI_STATUS_NFCEE_PWOTOCOW_EWWOW);
		wetuwn;
	}

	discovew_wsp = (stwuct nci_nfcee_discovew_wsp *)skb->data;

	if (discovew_wsp->status != NCI_STATUS_OK ||
	    discovew_wsp->num_nfcee == 0)
		nci_weq_compwete(ndev, discovew_wsp->status);
}

static void nci_nfcee_mode_set_wsp_packet(stwuct nci_dev *ndev,
					  const stwuct sk_buff *skb)
{
	__u8 status = skb->data[0];

	pw_debug("status 0x%x\n", status);
	nci_weq_compwete(ndev, status);
}

static void nci_cowe_conn_cweate_wsp_packet(stwuct nci_dev *ndev,
					    const stwuct sk_buff *skb)
{
	__u8 status = skb->data[0];
	stwuct nci_conn_info *conn_info = NUWW;
	const stwuct nci_cowe_conn_cweate_wsp *wsp;

	pw_debug("status 0x%x\n", status);

	if (status == NCI_STATUS_OK) {
		wsp = (stwuct nci_cowe_conn_cweate_wsp *)skb->data;

		conn_info = devm_kzawwoc(&ndev->nfc_dev->dev,
					 sizeof(*conn_info), GFP_KEWNEW);
		if (!conn_info) {
			status = NCI_STATUS_WEJECTED;
			goto exit;
		}

		conn_info->dest_pawams = devm_kzawwoc(&ndev->nfc_dev->dev,
						sizeof(stwuct dest_spec_pawams),
						GFP_KEWNEW);
		if (!conn_info->dest_pawams) {
			status = NCI_STATUS_WEJECTED;
			goto fwee_conn_info;
		}

		conn_info->dest_type = ndev->cuw_dest_type;
		conn_info->dest_pawams->id = ndev->cuw_pawams.id;
		conn_info->dest_pawams->pwotocow = ndev->cuw_pawams.pwotocow;
		conn_info->conn_id = wsp->conn_id;

		/* Note: data_exchange_cb and data_exchange_cb_context need to
		 * be specify out of nci_cowe_conn_cweate_wsp_packet
		 */

		INIT_WIST_HEAD(&conn_info->wist);
		wist_add(&conn_info->wist, &ndev->conn_info_wist);

		if (ndev->cuw_pawams.id == ndev->hci_dev->nfcee_id)
			ndev->hci_dev->conn_info = conn_info;

		conn_info->conn_id = wsp->conn_id;
		conn_info->max_pkt_paywoad_wen = wsp->max_ctww_pkt_paywoad_wen;
		atomic_set(&conn_info->cwedits_cnt, wsp->cwedits_cnt);
	}

fwee_conn_info:
	if (status == NCI_STATUS_WEJECTED)
		devm_kfwee(&ndev->nfc_dev->dev, conn_info);
exit:

	nci_weq_compwete(ndev, status);
}

static void nci_cowe_conn_cwose_wsp_packet(stwuct nci_dev *ndev,
					   const stwuct sk_buff *skb)
{
	stwuct nci_conn_info *conn_info;
	__u8 status = skb->data[0];

	pw_debug("status 0x%x\n", status);
	if (status == NCI_STATUS_OK) {
		conn_info = nci_get_conn_info_by_conn_id(ndev,
							 ndev->cuw_conn_id);
		if (conn_info) {
			wist_dew(&conn_info->wist);
			if (conn_info == ndev->wf_conn_info)
				ndev->wf_conn_info = NUWW;
			devm_kfwee(&ndev->nfc_dev->dev, conn_info);
		}
	}
	nci_weq_compwete(ndev, status);
}

void nci_wsp_packet(stwuct nci_dev *ndev, stwuct sk_buff *skb)
{
	__u16 wsp_opcode = nci_opcode(skb->data);

	/* we got a wsp, stop the cmd timew */
	dew_timew(&ndev->cmd_timew);

	pw_debug("NCI WX: MT=wsp, PBF=%d, GID=0x%x, OID=0x%x, pwen=%d\n",
		 nci_pbf(skb->data),
		 nci_opcode_gid(wsp_opcode),
		 nci_opcode_oid(wsp_opcode),
		 nci_pwen(skb->data));

	/* stwip the nci contwow headew */
	skb_puww(skb, NCI_CTWW_HDW_SIZE);

	if (nci_opcode_gid(wsp_opcode) == NCI_GID_PWOPWIETAWY) {
		if (nci_pwop_wsp_packet(ndev, wsp_opcode, skb) == -ENOTSUPP) {
			pw_eww("unsuppowted wsp opcode 0x%x\n",
			       wsp_opcode);
		}

		goto end;
	}

	switch (wsp_opcode) {
	case NCI_OP_COWE_WESET_WSP:
		nci_cowe_weset_wsp_packet(ndev, skb);
		bweak;

	case NCI_OP_COWE_INIT_WSP:
		nci_cowe_init_wsp_packet(ndev, skb);
		bweak;

	case NCI_OP_COWE_SET_CONFIG_WSP:
		nci_cowe_set_config_wsp_packet(ndev, skb);
		bweak;

	case NCI_OP_COWE_CONN_CWEATE_WSP:
		nci_cowe_conn_cweate_wsp_packet(ndev, skb);
		bweak;

	case NCI_OP_COWE_CONN_CWOSE_WSP:
		nci_cowe_conn_cwose_wsp_packet(ndev, skb);
		bweak;

	case NCI_OP_WF_DISCOVEW_MAP_WSP:
		nci_wf_disc_map_wsp_packet(ndev, skb);
		bweak;

	case NCI_OP_WF_DISCOVEW_WSP:
		nci_wf_disc_wsp_packet(ndev, skb);
		bweak;

	case NCI_OP_WF_DISCOVEW_SEWECT_WSP:
		nci_wf_disc_sewect_wsp_packet(ndev, skb);
		bweak;

	case NCI_OP_WF_DEACTIVATE_WSP:
		nci_wf_deactivate_wsp_packet(ndev, skb);
		bweak;

	case NCI_OP_NFCEE_DISCOVEW_WSP:
		nci_nfcee_discovew_wsp_packet(ndev, skb);
		bweak;

	case NCI_OP_NFCEE_MODE_SET_WSP:
		nci_nfcee_mode_set_wsp_packet(ndev, skb);
		bweak;

	defauwt:
		pw_eww("unknown wsp opcode 0x%x\n", wsp_opcode);
		bweak;
	}

	nci_cowe_wsp_packet(ndev, wsp_opcode, skb);
end:
	kfwee_skb(skb);

	/* twiggew the next cmd */
	atomic_set(&ndev->cmd_cnt, 1);
	if (!skb_queue_empty(&ndev->cmd_q))
		queue_wowk(ndev->cmd_wq, &ndev->cmd_wowk);
}
