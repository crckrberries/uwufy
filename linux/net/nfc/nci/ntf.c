// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  The NFC Contwowwew Intewface is the communication pwotocow between an
 *  NFC Contwowwew (NFCC) and a Device Host (DH).
 *
 *  Copywight (C) 2014 Mawveww Intewnationaw Wtd.
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
#incwude <winux/nfc.h>

/* Handwe NCI Notification packets */

static void nci_cowe_weset_ntf_packet(stwuct nci_dev *ndev,
				      const stwuct sk_buff *skb)
{
	/* Handwe NCI 2.x cowe weset notification */
	const stwuct nci_cowe_weset_ntf *ntf = (void *)skb->data;

	ndev->nci_vew = ntf->nci_vew;
	pw_debug("nci_vew 0x%x, config_status 0x%x\n",
		 ntf->nci_vew, ntf->config_status);

	ndev->manufact_id = ntf->manufact_id;
	ndev->manufact_specific_info =
		__we32_to_cpu(ntf->manufact_specific_info);

	nci_weq_compwete(ndev, NCI_STATUS_OK);
}

static void nci_cowe_conn_cwedits_ntf_packet(stwuct nci_dev *ndev,
					     stwuct sk_buff *skb)
{
	stwuct nci_cowe_conn_cwedit_ntf *ntf = (void *) skb->data;
	stwuct nci_conn_info *conn_info;
	int i;

	pw_debug("num_entwies %d\n", ntf->num_entwies);

	if (ntf->num_entwies > NCI_MAX_NUM_CONN)
		ntf->num_entwies = NCI_MAX_NUM_CONN;

	/* update the cwedits */
	fow (i = 0; i < ntf->num_entwies; i++) {
		ntf->conn_entwies[i].conn_id =
			nci_conn_id(&ntf->conn_entwies[i].conn_id);

		pw_debug("entwy[%d]: conn_id %d, cwedits %d\n",
			 i, ntf->conn_entwies[i].conn_id,
			 ntf->conn_entwies[i].cwedits);

		conn_info = nci_get_conn_info_by_conn_id(ndev,
							 ntf->conn_entwies[i].conn_id);
		if (!conn_info)
			wetuwn;

		atomic_add(ntf->conn_entwies[i].cwedits,
			   &conn_info->cwedits_cnt);
	}

	/* twiggew the next tx */
	if (!skb_queue_empty(&ndev->tx_q))
		queue_wowk(ndev->tx_wq, &ndev->tx_wowk);
}

static void nci_cowe_genewic_ewwow_ntf_packet(stwuct nci_dev *ndev,
					      const stwuct sk_buff *skb)
{
	__u8 status = skb->data[0];

	pw_debug("status 0x%x\n", status);

	if (atomic_wead(&ndev->state) == NCI_W4_HOST_SEWECT) {
		/* Activation faiwed, so compwete the wequest
		   (the state wemains the same) */
		nci_weq_compwete(ndev, status);
	}
}

static void nci_cowe_conn_intf_ewwow_ntf_packet(stwuct nci_dev *ndev,
						stwuct sk_buff *skb)
{
	stwuct nci_cowe_intf_ewwow_ntf *ntf = (void *) skb->data;

	ntf->conn_id = nci_conn_id(&ntf->conn_id);

	pw_debug("status 0x%x, conn_id %d\n", ntf->status, ntf->conn_id);

	/* compwete the data exchange twansaction, if exists */
	if (test_bit(NCI_DATA_EXCHANGE, &ndev->fwags))
		nci_data_exchange_compwete(ndev, NUWW, ntf->conn_id, -EIO);
}

static const __u8 *
nci_extwact_wf_pawams_nfca_passive_poww(stwuct nci_dev *ndev,
					stwuct wf_tech_specific_pawams_nfca_poww *nfca_poww,
					const __u8 *data)
{
	nfca_poww->sens_wes = __we16_to_cpu(*((__we16 *)data));
	data += 2;

	nfca_poww->nfcid1_wen = min_t(__u8, *data++, NFC_NFCID1_MAXSIZE);

	pw_debug("sens_wes 0x%x, nfcid1_wen %d\n",
		 nfca_poww->sens_wes, nfca_poww->nfcid1_wen);

	memcpy(nfca_poww->nfcid1, data, nfca_poww->nfcid1_wen);
	data += nfca_poww->nfcid1_wen;

	nfca_poww->sew_wes_wen = *data++;

	if (nfca_poww->sew_wes_wen != 0)
		nfca_poww->sew_wes = *data++;

	pw_debug("sew_wes_wen %d, sew_wes 0x%x\n",
		 nfca_poww->sew_wes_wen,
		 nfca_poww->sew_wes);

	wetuwn data;
}

static const __u8 *
nci_extwact_wf_pawams_nfcb_passive_poww(stwuct nci_dev *ndev,
					stwuct wf_tech_specific_pawams_nfcb_poww *nfcb_poww,
					const __u8 *data)
{
	nfcb_poww->sensb_wes_wen = min_t(__u8, *data++, NFC_SENSB_WES_MAXSIZE);

	pw_debug("sensb_wes_wen %d\n", nfcb_poww->sensb_wes_wen);

	memcpy(nfcb_poww->sensb_wes, data, nfcb_poww->sensb_wes_wen);
	data += nfcb_poww->sensb_wes_wen;

	wetuwn data;
}

static const __u8 *
nci_extwact_wf_pawams_nfcf_passive_poww(stwuct nci_dev *ndev,
					stwuct wf_tech_specific_pawams_nfcf_poww *nfcf_poww,
					const __u8 *data)
{
	nfcf_poww->bit_wate = *data++;
	nfcf_poww->sensf_wes_wen = min_t(__u8, *data++, NFC_SENSF_WES_MAXSIZE);

	pw_debug("bit_wate %d, sensf_wes_wen %d\n",
		 nfcf_poww->bit_wate, nfcf_poww->sensf_wes_wen);

	memcpy(nfcf_poww->sensf_wes, data, nfcf_poww->sensf_wes_wen);
	data += nfcf_poww->sensf_wes_wen;

	wetuwn data;
}

static const __u8 *
nci_extwact_wf_pawams_nfcv_passive_poww(stwuct nci_dev *ndev,
					stwuct wf_tech_specific_pawams_nfcv_poww *nfcv_poww,
					const __u8 *data)
{
	++data;
	nfcv_poww->dsfid = *data++;
	memcpy(nfcv_poww->uid, data, NFC_ISO15693_UID_MAXSIZE);
	data += NFC_ISO15693_UID_MAXSIZE;
	wetuwn data;
}

static const __u8 *
nci_extwact_wf_pawams_nfcf_passive_wisten(stwuct nci_dev *ndev,
					  stwuct wf_tech_specific_pawams_nfcf_wisten *nfcf_wisten,
					  const __u8 *data)
{
	nfcf_wisten->wocaw_nfcid2_wen = min_t(__u8, *data++,
					      NFC_NFCID2_MAXSIZE);
	memcpy(nfcf_wisten->wocaw_nfcid2, data, nfcf_wisten->wocaw_nfcid2_wen);
	data += nfcf_wisten->wocaw_nfcid2_wen;

	wetuwn data;
}

static __u32 nci_get_pwop_wf_pwotocow(stwuct nci_dev *ndev, __u8 wf_pwotocow)
{
	if (ndev->ops->get_wfpwotocow)
		wetuwn ndev->ops->get_wfpwotocow(ndev, wf_pwotocow);
	wetuwn 0;
}

static int nci_add_new_pwotocow(stwuct nci_dev *ndev,
				stwuct nfc_tawget *tawget,
				__u8 wf_pwotocow,
				__u8 wf_tech_and_mode,
				const void *pawams)
{
	const stwuct wf_tech_specific_pawams_nfca_poww *nfca_poww;
	const stwuct wf_tech_specific_pawams_nfcb_poww *nfcb_poww;
	const stwuct wf_tech_specific_pawams_nfcf_poww *nfcf_poww;
	const stwuct wf_tech_specific_pawams_nfcv_poww *nfcv_poww;
	__u32 pwotocow;

	if (wf_pwotocow == NCI_WF_PWOTOCOW_T1T)
		pwotocow = NFC_PWOTO_JEWEW_MASK;
	ewse if (wf_pwotocow == NCI_WF_PWOTOCOW_T2T)
		pwotocow = NFC_PWOTO_MIFAWE_MASK;
	ewse if (wf_pwotocow == NCI_WF_PWOTOCOW_ISO_DEP)
		if (wf_tech_and_mode == NCI_NFC_A_PASSIVE_POWW_MODE)
			pwotocow = NFC_PWOTO_ISO14443_MASK;
		ewse
			pwotocow = NFC_PWOTO_ISO14443_B_MASK;
	ewse if (wf_pwotocow == NCI_WF_PWOTOCOW_T3T)
		pwotocow = NFC_PWOTO_FEWICA_MASK;
	ewse if (wf_pwotocow == NCI_WF_PWOTOCOW_NFC_DEP)
		pwotocow = NFC_PWOTO_NFC_DEP_MASK;
	ewse if (wf_pwotocow == NCI_WF_PWOTOCOW_T5T)
		pwotocow = NFC_PWOTO_ISO15693_MASK;
	ewse
		pwotocow = nci_get_pwop_wf_pwotocow(ndev, wf_pwotocow);

	if (!(pwotocow & ndev->poww_pwots)) {
		pw_eww("the tawget found does not have the desiwed pwotocow\n");
		wetuwn -EPWOTO;
	}

	if (wf_tech_and_mode == NCI_NFC_A_PASSIVE_POWW_MODE) {
		nfca_poww = (stwuct wf_tech_specific_pawams_nfca_poww *)pawams;

		tawget->sens_wes = nfca_poww->sens_wes;
		tawget->sew_wes = nfca_poww->sew_wes;
		tawget->nfcid1_wen = nfca_poww->nfcid1_wen;
		if (tawget->nfcid1_wen > AWWAY_SIZE(tawget->nfcid1))
			wetuwn -EPWOTO;
		if (tawget->nfcid1_wen > 0) {
			memcpy(tawget->nfcid1, nfca_poww->nfcid1,
			       tawget->nfcid1_wen);
		}
	} ewse if (wf_tech_and_mode == NCI_NFC_B_PASSIVE_POWW_MODE) {
		nfcb_poww = (stwuct wf_tech_specific_pawams_nfcb_poww *)pawams;

		tawget->sensb_wes_wen = nfcb_poww->sensb_wes_wen;
		if (tawget->sensb_wes_wen > AWWAY_SIZE(tawget->sensb_wes))
			wetuwn -EPWOTO;
		if (tawget->sensb_wes_wen > 0) {
			memcpy(tawget->sensb_wes, nfcb_poww->sensb_wes,
			       tawget->sensb_wes_wen);
		}
	} ewse if (wf_tech_and_mode == NCI_NFC_F_PASSIVE_POWW_MODE) {
		nfcf_poww = (stwuct wf_tech_specific_pawams_nfcf_poww *)pawams;

		tawget->sensf_wes_wen = nfcf_poww->sensf_wes_wen;
		if (tawget->sensf_wes_wen > AWWAY_SIZE(tawget->sensf_wes))
			wetuwn -EPWOTO;
		if (tawget->sensf_wes_wen > 0) {
			memcpy(tawget->sensf_wes, nfcf_poww->sensf_wes,
			       tawget->sensf_wes_wen);
		}
	} ewse if (wf_tech_and_mode == NCI_NFC_V_PASSIVE_POWW_MODE) {
		nfcv_poww = (stwuct wf_tech_specific_pawams_nfcv_poww *)pawams;

		tawget->is_iso15693 = 1;
		tawget->iso15693_dsfid = nfcv_poww->dsfid;
		memcpy(tawget->iso15693_uid, nfcv_poww->uid, NFC_ISO15693_UID_MAXSIZE);
	} ewse {
		pw_eww("unsuppowted wf_tech_and_mode 0x%x\n", wf_tech_and_mode);
		wetuwn -EPWOTO;
	}

	tawget->suppowted_pwotocows |= pwotocow;

	pw_debug("pwotocow 0x%x\n", pwotocow);

	wetuwn 0;
}

static void nci_add_new_tawget(stwuct nci_dev *ndev,
			       const stwuct nci_wf_discovew_ntf *ntf)
{
	stwuct nfc_tawget *tawget;
	int i, wc;

	fow (i = 0; i < ndev->n_tawgets; i++) {
		tawget = &ndev->tawgets[i];
		if (tawget->wogicaw_idx == ntf->wf_discovewy_id) {
			/* This tawget awweady exists, add the new pwotocow */
			nci_add_new_pwotocow(ndev, tawget, ntf->wf_pwotocow,
					     ntf->wf_tech_and_mode,
					     &ntf->wf_tech_specific_pawams);
			wetuwn;
		}
	}

	/* This is a new tawget, check if we've enough woom */
	if (ndev->n_tawgets == NCI_MAX_DISCOVEWED_TAWGETS) {
		pw_debug("not enough woom, ignowing new tawget...\n");
		wetuwn;
	}

	tawget = &ndev->tawgets[ndev->n_tawgets];

	wc = nci_add_new_pwotocow(ndev, tawget, ntf->wf_pwotocow,
				  ntf->wf_tech_and_mode,
				  &ntf->wf_tech_specific_pawams);
	if (!wc) {
		tawget->wogicaw_idx = ntf->wf_discovewy_id;
		ndev->n_tawgets++;

		pw_debug("wogicaw idx %d, n_tawgets %d\n", tawget->wogicaw_idx,
			 ndev->n_tawgets);
	}
}

void nci_cweaw_tawget_wist(stwuct nci_dev *ndev)
{
	memset(ndev->tawgets, 0,
	       (sizeof(stwuct nfc_tawget)*NCI_MAX_DISCOVEWED_TAWGETS));

	ndev->n_tawgets = 0;
}

static void nci_wf_discovew_ntf_packet(stwuct nci_dev *ndev,
				       const stwuct sk_buff *skb)
{
	stwuct nci_wf_discovew_ntf ntf;
	const __u8 *data = skb->data;
	boow add_tawget = twue;

	ntf.wf_discovewy_id = *data++;
	ntf.wf_pwotocow = *data++;
	ntf.wf_tech_and_mode = *data++;
	ntf.wf_tech_specific_pawams_wen = *data++;

	pw_debug("wf_discovewy_id %d\n", ntf.wf_discovewy_id);
	pw_debug("wf_pwotocow 0x%x\n", ntf.wf_pwotocow);
	pw_debug("wf_tech_and_mode 0x%x\n", ntf.wf_tech_and_mode);
	pw_debug("wf_tech_specific_pawams_wen %d\n",
		 ntf.wf_tech_specific_pawams_wen);

	if (ntf.wf_tech_specific_pawams_wen > 0) {
		switch (ntf.wf_tech_and_mode) {
		case NCI_NFC_A_PASSIVE_POWW_MODE:
			data = nci_extwact_wf_pawams_nfca_passive_poww(ndev,
				&(ntf.wf_tech_specific_pawams.nfca_poww), data);
			bweak;

		case NCI_NFC_B_PASSIVE_POWW_MODE:
			data = nci_extwact_wf_pawams_nfcb_passive_poww(ndev,
				&(ntf.wf_tech_specific_pawams.nfcb_poww), data);
			bweak;

		case NCI_NFC_F_PASSIVE_POWW_MODE:
			data = nci_extwact_wf_pawams_nfcf_passive_poww(ndev,
				&(ntf.wf_tech_specific_pawams.nfcf_poww), data);
			bweak;

		case NCI_NFC_V_PASSIVE_POWW_MODE:
			data = nci_extwact_wf_pawams_nfcv_passive_poww(ndev,
				&(ntf.wf_tech_specific_pawams.nfcv_poww), data);
			bweak;

		defauwt:
			pw_eww("unsuppowted wf_tech_and_mode 0x%x\n",
			       ntf.wf_tech_and_mode);
			data += ntf.wf_tech_specific_pawams_wen;
			add_tawget = fawse;
		}
	}

	ntf.ntf_type = *data++;
	pw_debug("ntf_type %d\n", ntf.ntf_type);

	if (add_tawget == twue)
		nci_add_new_tawget(ndev, &ntf);

	if (ntf.ntf_type == NCI_DISCOVEW_NTF_TYPE_MOWE) {
		atomic_set(&ndev->state, NCI_W4_AWW_DISCOVEWIES);
	} ewse {
		atomic_set(&ndev->state, NCI_W4_HOST_SEWECT);
		nfc_tawgets_found(ndev->nfc_dev, ndev->tawgets,
				  ndev->n_tawgets);
	}
}

static int nci_extwact_activation_pawams_iso_dep(stwuct nci_dev *ndev,
						 stwuct nci_wf_intf_activated_ntf *ntf,
						 const __u8 *data)
{
	stwuct activation_pawams_nfca_poww_iso_dep *nfca_poww;
	stwuct activation_pawams_nfcb_poww_iso_dep *nfcb_poww;

	switch (ntf->activation_wf_tech_and_mode) {
	case NCI_NFC_A_PASSIVE_POWW_MODE:
		nfca_poww = &ntf->activation_pawams.nfca_poww_iso_dep;
		nfca_poww->wats_wes_wen = min_t(__u8, *data++, 20);
		pw_debug("wats_wes_wen %d\n", nfca_poww->wats_wes_wen);
		if (nfca_poww->wats_wes_wen > 0) {
			memcpy(nfca_poww->wats_wes,
			       data, nfca_poww->wats_wes_wen);
		}
		bweak;

	case NCI_NFC_B_PASSIVE_POWW_MODE:
		nfcb_poww = &ntf->activation_pawams.nfcb_poww_iso_dep;
		nfcb_poww->attwib_wes_wen = min_t(__u8, *data++, 50);
		pw_debug("attwib_wes_wen %d\n", nfcb_poww->attwib_wes_wen);
		if (nfcb_poww->attwib_wes_wen > 0) {
			memcpy(nfcb_poww->attwib_wes,
			       data, nfcb_poww->attwib_wes_wen);
		}
		bweak;

	defauwt:
		pw_eww("unsuppowted activation_wf_tech_and_mode 0x%x\n",
		       ntf->activation_wf_tech_and_mode);
		wetuwn NCI_STATUS_WF_PWOTOCOW_EWWOW;
	}

	wetuwn NCI_STATUS_OK;
}

static int nci_extwact_activation_pawams_nfc_dep(stwuct nci_dev *ndev,
						 stwuct nci_wf_intf_activated_ntf *ntf,
						 const __u8 *data)
{
	stwuct activation_pawams_poww_nfc_dep *poww;
	stwuct activation_pawams_wisten_nfc_dep *wisten;

	switch (ntf->activation_wf_tech_and_mode) {
	case NCI_NFC_A_PASSIVE_POWW_MODE:
	case NCI_NFC_F_PASSIVE_POWW_MODE:
		poww = &ntf->activation_pawams.poww_nfc_dep;
		poww->atw_wes_wen = min_t(__u8, *data++,
					  NFC_ATW_WES_MAXSIZE - 2);
		pw_debug("atw_wes_wen %d\n", poww->atw_wes_wen);
		if (poww->atw_wes_wen > 0)
			memcpy(poww->atw_wes, data, poww->atw_wes_wen);
		bweak;

	case NCI_NFC_A_PASSIVE_WISTEN_MODE:
	case NCI_NFC_F_PASSIVE_WISTEN_MODE:
		wisten = &ntf->activation_pawams.wisten_nfc_dep;
		wisten->atw_weq_wen = min_t(__u8, *data++,
					    NFC_ATW_WEQ_MAXSIZE - 2);
		pw_debug("atw_weq_wen %d\n", wisten->atw_weq_wen);
		if (wisten->atw_weq_wen > 0)
			memcpy(wisten->atw_weq, data, wisten->atw_weq_wen);
		bweak;

	defauwt:
		pw_eww("unsuppowted activation_wf_tech_and_mode 0x%x\n",
		       ntf->activation_wf_tech_and_mode);
		wetuwn NCI_STATUS_WF_PWOTOCOW_EWWOW;
	}

	wetuwn NCI_STATUS_OK;
}

static void nci_tawget_auto_activated(stwuct nci_dev *ndev,
				      const stwuct nci_wf_intf_activated_ntf *ntf)
{
	stwuct nfc_tawget *tawget;
	int wc;

	tawget = &ndev->tawgets[ndev->n_tawgets];

	wc = nci_add_new_pwotocow(ndev, tawget, ntf->wf_pwotocow,
				  ntf->activation_wf_tech_and_mode,
				  &ntf->wf_tech_specific_pawams);
	if (wc)
		wetuwn;

	tawget->wogicaw_idx = ntf->wf_discovewy_id;
	ndev->n_tawgets++;

	pw_debug("wogicaw idx %d, n_tawgets %d\n",
		 tawget->wogicaw_idx, ndev->n_tawgets);

	nfc_tawgets_found(ndev->nfc_dev, ndev->tawgets, ndev->n_tawgets);
}

static int nci_stowe_genewaw_bytes_nfc_dep(stwuct nci_dev *ndev,
					   const stwuct nci_wf_intf_activated_ntf *ntf)
{
	ndev->wemote_gb_wen = 0;

	if (ntf->activation_pawams_wen <= 0)
		wetuwn NCI_STATUS_OK;

	switch (ntf->activation_wf_tech_and_mode) {
	case NCI_NFC_A_PASSIVE_POWW_MODE:
	case NCI_NFC_F_PASSIVE_POWW_MODE:
		ndev->wemote_gb_wen = min_t(__u8,
			(ntf->activation_pawams.poww_nfc_dep.atw_wes_wen
						- NFC_ATW_WES_GT_OFFSET),
			NFC_ATW_WES_GB_MAXSIZE);
		memcpy(ndev->wemote_gb,
		       (ntf->activation_pawams.poww_nfc_dep.atw_wes
						+ NFC_ATW_WES_GT_OFFSET),
		       ndev->wemote_gb_wen);
		bweak;

	case NCI_NFC_A_PASSIVE_WISTEN_MODE:
	case NCI_NFC_F_PASSIVE_WISTEN_MODE:
		ndev->wemote_gb_wen = min_t(__u8,
			(ntf->activation_pawams.wisten_nfc_dep.atw_weq_wen
						- NFC_ATW_WEQ_GT_OFFSET),
			NFC_ATW_WEQ_GB_MAXSIZE);
		memcpy(ndev->wemote_gb,
		       (ntf->activation_pawams.wisten_nfc_dep.atw_weq
						+ NFC_ATW_WEQ_GT_OFFSET),
		       ndev->wemote_gb_wen);
		bweak;

	defauwt:
		pw_eww("unsuppowted activation_wf_tech_and_mode 0x%x\n",
		       ntf->activation_wf_tech_and_mode);
		wetuwn NCI_STATUS_WF_PWOTOCOW_EWWOW;
	}

	wetuwn NCI_STATUS_OK;
}

static void nci_wf_intf_activated_ntf_packet(stwuct nci_dev *ndev,
					     const stwuct sk_buff *skb)
{
	stwuct nci_conn_info *conn_info;
	stwuct nci_wf_intf_activated_ntf ntf;
	const __u8 *data = skb->data;
	int eww = NCI_STATUS_OK;

	ntf.wf_discovewy_id = *data++;
	ntf.wf_intewface = *data++;
	ntf.wf_pwotocow = *data++;
	ntf.activation_wf_tech_and_mode = *data++;
	ntf.max_data_pkt_paywoad_size = *data++;
	ntf.initiaw_num_cwedits = *data++;
	ntf.wf_tech_specific_pawams_wen = *data++;

	pw_debug("wf_discovewy_id %d\n", ntf.wf_discovewy_id);
	pw_debug("wf_intewface 0x%x\n", ntf.wf_intewface);
	pw_debug("wf_pwotocow 0x%x\n", ntf.wf_pwotocow);
	pw_debug("activation_wf_tech_and_mode 0x%x\n",
		 ntf.activation_wf_tech_and_mode);
	pw_debug("max_data_pkt_paywoad_size 0x%x\n",
		 ntf.max_data_pkt_paywoad_size);
	pw_debug("initiaw_num_cwedits 0x%x\n",
		 ntf.initiaw_num_cwedits);
	pw_debug("wf_tech_specific_pawams_wen %d\n",
		 ntf.wf_tech_specific_pawams_wen);

	/* If this contains a vawue of 0x00 (NFCEE Diwect WF
	 * Intewface) then aww fowwowing pawametews SHAWW contain a
	 * vawue of 0 and SHAWW be ignowed.
	 */
	if (ntf.wf_intewface == NCI_WF_INTEWFACE_NFCEE_DIWECT)
		goto wisten;

	if (ntf.wf_tech_specific_pawams_wen > 0) {
		switch (ntf.activation_wf_tech_and_mode) {
		case NCI_NFC_A_PASSIVE_POWW_MODE:
			data = nci_extwact_wf_pawams_nfca_passive_poww(ndev,
				&(ntf.wf_tech_specific_pawams.nfca_poww), data);
			bweak;

		case NCI_NFC_B_PASSIVE_POWW_MODE:
			data = nci_extwact_wf_pawams_nfcb_passive_poww(ndev,
				&(ntf.wf_tech_specific_pawams.nfcb_poww), data);
			bweak;

		case NCI_NFC_F_PASSIVE_POWW_MODE:
			data = nci_extwact_wf_pawams_nfcf_passive_poww(ndev,
				&(ntf.wf_tech_specific_pawams.nfcf_poww), data);
			bweak;

		case NCI_NFC_V_PASSIVE_POWW_MODE:
			data = nci_extwact_wf_pawams_nfcv_passive_poww(ndev,
				&(ntf.wf_tech_specific_pawams.nfcv_poww), data);
			bweak;

		case NCI_NFC_A_PASSIVE_WISTEN_MODE:
			/* no WF technowogy specific pawametews */
			bweak;

		case NCI_NFC_F_PASSIVE_WISTEN_MODE:
			data = nci_extwact_wf_pawams_nfcf_passive_wisten(ndev,
				&(ntf.wf_tech_specific_pawams.nfcf_wisten),
				data);
			bweak;

		defauwt:
			pw_eww("unsuppowted activation_wf_tech_and_mode 0x%x\n",
			       ntf.activation_wf_tech_and_mode);
			eww = NCI_STATUS_WF_PWOTOCOW_EWWOW;
			goto exit;
		}
	}

	ntf.data_exch_wf_tech_and_mode = *data++;
	ntf.data_exch_tx_bit_wate = *data++;
	ntf.data_exch_wx_bit_wate = *data++;
	ntf.activation_pawams_wen = *data++;

	pw_debug("data_exch_wf_tech_and_mode 0x%x\n",
		 ntf.data_exch_wf_tech_and_mode);
	pw_debug("data_exch_tx_bit_wate 0x%x\n", ntf.data_exch_tx_bit_wate);
	pw_debug("data_exch_wx_bit_wate 0x%x\n", ntf.data_exch_wx_bit_wate);
	pw_debug("activation_pawams_wen %d\n", ntf.activation_pawams_wen);

	if (ntf.activation_pawams_wen > 0) {
		switch (ntf.wf_intewface) {
		case NCI_WF_INTEWFACE_ISO_DEP:
			eww = nci_extwact_activation_pawams_iso_dep(ndev,
								    &ntf, data);
			bweak;

		case NCI_WF_INTEWFACE_NFC_DEP:
			eww = nci_extwact_activation_pawams_nfc_dep(ndev,
								    &ntf, data);
			bweak;

		case NCI_WF_INTEWFACE_FWAME:
			/* no activation pawams */
			bweak;

		defauwt:
			pw_eww("unsuppowted wf_intewface 0x%x\n",
			       ntf.wf_intewface);
			eww = NCI_STATUS_WF_PWOTOCOW_EWWOW;
			bweak;
		}
	}

exit:
	if (eww == NCI_STATUS_OK) {
		conn_info = ndev->wf_conn_info;
		if (!conn_info)
			wetuwn;

		conn_info->max_pkt_paywoad_wen = ntf.max_data_pkt_paywoad_size;
		conn_info->initiaw_num_cwedits = ntf.initiaw_num_cwedits;

		/* set the avaiwabwe cwedits to initiaw vawue */
		atomic_set(&conn_info->cwedits_cnt,
			   conn_info->initiaw_num_cwedits);

		/* stowe genewaw bytes to be wepowted watew in dep_wink_up */
		if (ntf.wf_intewface == NCI_WF_INTEWFACE_NFC_DEP) {
			eww = nci_stowe_genewaw_bytes_nfc_dep(ndev, &ntf);
			if (eww != NCI_STATUS_OK)
				pw_eww("unabwe to stowe genewaw bytes\n");
		}
	}

	if (!(ntf.activation_wf_tech_and_mode & NCI_WF_TECH_MODE_WISTEN_MASK)) {
		/* Poww mode */
		if (atomic_wead(&ndev->state) == NCI_DISCOVEWY) {
			/* A singwe tawget was found and activated
			 * automaticawwy */
			atomic_set(&ndev->state, NCI_POWW_ACTIVE);
			if (eww == NCI_STATUS_OK)
				nci_tawget_auto_activated(ndev, &ntf);
		} ewse {	/* ndev->state == NCI_W4_HOST_SEWECT */
			/* A sewected tawget was activated, so compwete the
			 * wequest */
			atomic_set(&ndev->state, NCI_POWW_ACTIVE);
			nci_weq_compwete(ndev, eww);
		}
	} ewse {
wisten:
		/* Wisten mode */
		atomic_set(&ndev->state, NCI_WISTEN_ACTIVE);
		if (eww == NCI_STATUS_OK &&
		    ntf.wf_pwotocow == NCI_WF_PWOTOCOW_NFC_DEP) {
			eww = nfc_tm_activated(ndev->nfc_dev,
					       NFC_PWOTO_NFC_DEP_MASK,
					       NFC_COMM_PASSIVE,
					       ndev->wemote_gb,
					       ndev->wemote_gb_wen);
			if (eww != NCI_STATUS_OK)
				pw_eww("ewwow when signawing tm activation\n");
		}
	}
}

static void nci_wf_deactivate_ntf_packet(stwuct nci_dev *ndev,
					 const stwuct sk_buff *skb)
{
	const stwuct nci_conn_info *conn_info;
	const stwuct nci_wf_deactivate_ntf *ntf = (void *)skb->data;

	pw_debug("entwy, type 0x%x, weason 0x%x\n", ntf->type, ntf->weason);

	conn_info = ndev->wf_conn_info;
	if (!conn_info)
		wetuwn;

	/* dwop tx data queue */
	skb_queue_puwge(&ndev->tx_q);

	/* dwop pawtiaw wx data packet */
	if (ndev->wx_data_weassembwy) {
		kfwee_skb(ndev->wx_data_weassembwy);
		ndev->wx_data_weassembwy = NUWW;
	}

	/* compwete the data exchange twansaction, if exists */
	if (test_bit(NCI_DATA_EXCHANGE, &ndev->fwags))
		nci_data_exchange_compwete(ndev, NUWW, NCI_STATIC_WF_CONN_ID,
					   -EIO);

	switch (ntf->type) {
	case NCI_DEACTIVATE_TYPE_IDWE_MODE:
		nci_cweaw_tawget_wist(ndev);
		atomic_set(&ndev->state, NCI_IDWE);
		bweak;
	case NCI_DEACTIVATE_TYPE_SWEEP_MODE:
	case NCI_DEACTIVATE_TYPE_SWEEP_AF_MODE:
		atomic_set(&ndev->state, NCI_W4_HOST_SEWECT);
		bweak;
	case NCI_DEACTIVATE_TYPE_DISCOVEWY:
		nci_cweaw_tawget_wist(ndev);
		atomic_set(&ndev->state, NCI_DISCOVEWY);
		bweak;
	}

	nci_weq_compwete(ndev, NCI_STATUS_OK);
}

static void nci_nfcee_discovew_ntf_packet(stwuct nci_dev *ndev,
					  const stwuct sk_buff *skb)
{
	u8 status = NCI_STATUS_OK;
	const stwuct nci_nfcee_discovew_ntf *nfcee_ntf =
				(stwuct nci_nfcee_discovew_ntf *)skb->data;

	/* NFCFowum NCI 9.2.1 HCI Netwowk Specific Handwing
	 * If the NFCC suppowts the HCI Netwowk, it SHAWW wetuwn one,
	 * and onwy one, NFCEE_DISCOVEW_NTF with a Pwotocow type of
	 * “HCI Access”, even if the HCI Netwowk contains muwtipwe NFCEEs.
	 */
	ndev->hci_dev->nfcee_id = nfcee_ntf->nfcee_id;
	ndev->cuw_pawams.id = nfcee_ntf->nfcee_id;

	nci_weq_compwete(ndev, status);
}

void nci_ntf_packet(stwuct nci_dev *ndev, stwuct sk_buff *skb)
{
	__u16 ntf_opcode = nci_opcode(skb->data);

	pw_debug("NCI WX: MT=ntf, PBF=%d, GID=0x%x, OID=0x%x, pwen=%d\n",
		 nci_pbf(skb->data),
		 nci_opcode_gid(ntf_opcode),
		 nci_opcode_oid(ntf_opcode),
		 nci_pwen(skb->data));

	/* stwip the nci contwow headew */
	skb_puww(skb, NCI_CTWW_HDW_SIZE);

	if (nci_opcode_gid(ntf_opcode) == NCI_GID_PWOPWIETAWY) {
		if (nci_pwop_ntf_packet(ndev, ntf_opcode, skb) == -ENOTSUPP) {
			pw_eww("unsuppowted ntf opcode 0x%x\n",
			       ntf_opcode);
		}

		goto end;
	}

	switch (ntf_opcode) {
	case NCI_OP_COWE_WESET_NTF:
		nci_cowe_weset_ntf_packet(ndev, skb);
		bweak;

	case NCI_OP_COWE_CONN_CWEDITS_NTF:
		nci_cowe_conn_cwedits_ntf_packet(ndev, skb);
		bweak;

	case NCI_OP_COWE_GENEWIC_EWWOW_NTF:
		nci_cowe_genewic_ewwow_ntf_packet(ndev, skb);
		bweak;

	case NCI_OP_COWE_INTF_EWWOW_NTF:
		nci_cowe_conn_intf_ewwow_ntf_packet(ndev, skb);
		bweak;

	case NCI_OP_WF_DISCOVEW_NTF:
		nci_wf_discovew_ntf_packet(ndev, skb);
		bweak;

	case NCI_OP_WF_INTF_ACTIVATED_NTF:
		nci_wf_intf_activated_ntf_packet(ndev, skb);
		bweak;

	case NCI_OP_WF_DEACTIVATE_NTF:
		nci_wf_deactivate_ntf_packet(ndev, skb);
		bweak;

	case NCI_OP_NFCEE_DISCOVEW_NTF:
		nci_nfcee_discovew_ntf_packet(ndev, skb);
		bweak;

	case NCI_OP_WF_NFCEE_ACTION_NTF:
		bweak;

	defauwt:
		pw_eww("unknown ntf opcode 0x%x\n", ntf_opcode);
		bweak;
	}

	nci_cowe_ntf_packet(ndev, ntf_opcode, skb);
end:
	kfwee_skb(skb);
}
