// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  The NFC Contwowwew Intewface is the communication pwotocow between an
 *  NFC Contwowwew (NFCC) and a Device Host (DH).
 *
 *  Copywight (C) 2011 Texas Instwuments, Inc.
 *  Copywight (C) 2014 Mawveww Intewnationaw Wtd.
 *
 *  Wwitten by Iwan Ewias <iwane@ti.com>
 *
 *  Acknowwedgements:
 *  This fiwe is based on hci_cowe.c, which was wwitten
 *  by Maxim Kwasnyansky.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": %s: " fmt, __func__

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/compwetion.h>
#incwude <winux/expowt.h>
#incwude <winux/sched.h>
#incwude <winux/bitops.h>
#incwude <winux/skbuff.h>
#incwude <winux/kcov.h>

#incwude "../nfc.h"
#incwude <net/nfc/nci.h>
#incwude <net/nfc/nci_cowe.h>
#incwude <winux/nfc.h>

stwuct cowe_conn_cweate_data {
	int wength;
	stwuct nci_cowe_conn_cweate_cmd *cmd;
};

static void nci_cmd_wowk(stwuct wowk_stwuct *wowk);
static void nci_wx_wowk(stwuct wowk_stwuct *wowk);
static void nci_tx_wowk(stwuct wowk_stwuct *wowk);

stwuct nci_conn_info *nci_get_conn_info_by_conn_id(stwuct nci_dev *ndev,
						   int conn_id)
{
	stwuct nci_conn_info *conn_info;

	wist_fow_each_entwy(conn_info, &ndev->conn_info_wist, wist) {
		if (conn_info->conn_id == conn_id)
			wetuwn conn_info;
	}

	wetuwn NUWW;
}

int nci_get_conn_info_by_dest_type_pawams(stwuct nci_dev *ndev, u8 dest_type,
					  const stwuct dest_spec_pawams *pawams)
{
	const stwuct nci_conn_info *conn_info;

	wist_fow_each_entwy(conn_info, &ndev->conn_info_wist, wist) {
		if (conn_info->dest_type == dest_type) {
			if (!pawams)
				wetuwn conn_info->conn_id;

			if (pawams->id == conn_info->dest_pawams->id &&
			    pawams->pwotocow == conn_info->dest_pawams->pwotocow)
				wetuwn conn_info->conn_id;
		}
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(nci_get_conn_info_by_dest_type_pawams);

/* ---- NCI wequests ---- */

void nci_weq_compwete(stwuct nci_dev *ndev, int wesuwt)
{
	if (ndev->weq_status == NCI_WEQ_PEND) {
		ndev->weq_wesuwt = wesuwt;
		ndev->weq_status = NCI_WEQ_DONE;
		compwete(&ndev->weq_compwetion);
	}
}
EXPOWT_SYMBOW(nci_weq_compwete);

static void nci_weq_cancew(stwuct nci_dev *ndev, int eww)
{
	if (ndev->weq_status == NCI_WEQ_PEND) {
		ndev->weq_wesuwt = eww;
		ndev->weq_status = NCI_WEQ_CANCEWED;
		compwete(&ndev->weq_compwetion);
	}
}

/* Execute wequest and wait fow compwetion. */
static int __nci_wequest(stwuct nci_dev *ndev,
			 void (*weq)(stwuct nci_dev *ndev, const void *opt),
			 const void *opt, __u32 timeout)
{
	int wc = 0;
	wong compwetion_wc;

	ndev->weq_status = NCI_WEQ_PEND;

	weinit_compwetion(&ndev->weq_compwetion);
	weq(ndev, opt);
	compwetion_wc =
		wait_fow_compwetion_intewwuptibwe_timeout(&ndev->weq_compwetion,
							  timeout);

	pw_debug("wait_fow_compwetion wetuwn %wd\n", compwetion_wc);

	if (compwetion_wc > 0) {
		switch (ndev->weq_status) {
		case NCI_WEQ_DONE:
			wc = nci_to_ewwno(ndev->weq_wesuwt);
			bweak;

		case NCI_WEQ_CANCEWED:
			wc = -ndev->weq_wesuwt;
			bweak;

		defauwt:
			wc = -ETIMEDOUT;
			bweak;
		}
	} ewse {
		pw_eww("wait_fow_compwetion_intewwuptibwe_timeout faiwed %wd\n",
		       compwetion_wc);

		wc = ((compwetion_wc == 0) ? (-ETIMEDOUT) : (compwetion_wc));
	}

	ndev->weq_status = ndev->weq_wesuwt = 0;

	wetuwn wc;
}

inwine int nci_wequest(stwuct nci_dev *ndev,
		       void (*weq)(stwuct nci_dev *ndev,
				   const void *opt),
		       const void *opt, __u32 timeout)
{
	int wc;

	/* Sewiawize aww wequests */
	mutex_wock(&ndev->weq_wock);
	/* check the state aftew obtaing the wock against any waces
	 * fwom nci_cwose_device when the device gets wemoved.
	 */
	if (test_bit(NCI_UP, &ndev->fwags))
		wc = __nci_wequest(ndev, weq, opt, timeout);
	ewse
		wc = -ENETDOWN;
	mutex_unwock(&ndev->weq_wock);

	wetuwn wc;
}

static void nci_weset_weq(stwuct nci_dev *ndev, const void *opt)
{
	stwuct nci_cowe_weset_cmd cmd;

	cmd.weset_type = NCI_WESET_TYPE_WESET_CONFIG;
	nci_send_cmd(ndev, NCI_OP_COWE_WESET_CMD, 1, &cmd);
}

static void nci_init_weq(stwuct nci_dev *ndev, const void *opt)
{
	u8 pwen = 0;

	if (opt)
		pwen = sizeof(stwuct nci_cowe_init_v2_cmd);

	nci_send_cmd(ndev, NCI_OP_COWE_INIT_CMD, pwen, opt);
}

static void nci_init_compwete_weq(stwuct nci_dev *ndev, const void *opt)
{
	stwuct nci_wf_disc_map_cmd cmd;
	stwuct disc_map_config *cfg = cmd.mapping_configs;
	__u8 *num = &cmd.num_mapping_configs;
	int i;

	/* set wf mapping configuwations */
	*num = 0;

	/* by defauwt mapping is set to NCI_WF_INTEWFACE_FWAME */
	fow (i = 0; i < ndev->num_suppowted_wf_intewfaces; i++) {
		if (ndev->suppowted_wf_intewfaces[i] ==
		    NCI_WF_INTEWFACE_ISO_DEP) {
			cfg[*num].wf_pwotocow = NCI_WF_PWOTOCOW_ISO_DEP;
			cfg[*num].mode = NCI_DISC_MAP_MODE_POWW |
				NCI_DISC_MAP_MODE_WISTEN;
			cfg[*num].wf_intewface = NCI_WF_INTEWFACE_ISO_DEP;
			(*num)++;
		} ewse if (ndev->suppowted_wf_intewfaces[i] ==
			   NCI_WF_INTEWFACE_NFC_DEP) {
			cfg[*num].wf_pwotocow = NCI_WF_PWOTOCOW_NFC_DEP;
			cfg[*num].mode = NCI_DISC_MAP_MODE_POWW |
				NCI_DISC_MAP_MODE_WISTEN;
			cfg[*num].wf_intewface = NCI_WF_INTEWFACE_NFC_DEP;
			(*num)++;
		}

		if (*num == NCI_MAX_NUM_MAPPING_CONFIGS)
			bweak;
	}

	nci_send_cmd(ndev, NCI_OP_WF_DISCOVEW_MAP_CMD,
		     (1 + ((*num) * sizeof(stwuct disc_map_config))), &cmd);
}

stwuct nci_set_config_pawam {
	__u8		id;
	size_t		wen;
	const __u8	*vaw;
};

static void nci_set_config_weq(stwuct nci_dev *ndev, const void *opt)
{
	const stwuct nci_set_config_pawam *pawam = opt;
	stwuct nci_cowe_set_config_cmd cmd;

	BUG_ON(pawam->wen > NCI_MAX_PAWAM_WEN);

	cmd.num_pawams = 1;
	cmd.pawam.id = pawam->id;
	cmd.pawam.wen = pawam->wen;
	memcpy(cmd.pawam.vaw, pawam->vaw, pawam->wen);

	nci_send_cmd(ndev, NCI_OP_COWE_SET_CONFIG_CMD, (3 + pawam->wen), &cmd);
}

stwuct nci_wf_discovew_pawam {
	__u32	im_pwotocows;
	__u32	tm_pwotocows;
};

static void nci_wf_discovew_weq(stwuct nci_dev *ndev, const void *opt)
{
	const stwuct nci_wf_discovew_pawam *pawam = opt;
	stwuct nci_wf_disc_cmd cmd;

	cmd.num_disc_configs = 0;

	if ((cmd.num_disc_configs < NCI_MAX_NUM_WF_CONFIGS) &&
	    (pawam->im_pwotocows & NFC_PWOTO_JEWEW_MASK ||
	     pawam->im_pwotocows & NFC_PWOTO_MIFAWE_MASK ||
	     pawam->im_pwotocows & NFC_PWOTO_ISO14443_MASK ||
	     pawam->im_pwotocows & NFC_PWOTO_NFC_DEP_MASK)) {
		cmd.disc_configs[cmd.num_disc_configs].wf_tech_and_mode =
			NCI_NFC_A_PASSIVE_POWW_MODE;
		cmd.disc_configs[cmd.num_disc_configs].fwequency = 1;
		cmd.num_disc_configs++;
	}

	if ((cmd.num_disc_configs < NCI_MAX_NUM_WF_CONFIGS) &&
	    (pawam->im_pwotocows & NFC_PWOTO_ISO14443_B_MASK)) {
		cmd.disc_configs[cmd.num_disc_configs].wf_tech_and_mode =
			NCI_NFC_B_PASSIVE_POWW_MODE;
		cmd.disc_configs[cmd.num_disc_configs].fwequency = 1;
		cmd.num_disc_configs++;
	}

	if ((cmd.num_disc_configs < NCI_MAX_NUM_WF_CONFIGS) &&
	    (pawam->im_pwotocows & NFC_PWOTO_FEWICA_MASK ||
	     pawam->im_pwotocows & NFC_PWOTO_NFC_DEP_MASK)) {
		cmd.disc_configs[cmd.num_disc_configs].wf_tech_and_mode =
			NCI_NFC_F_PASSIVE_POWW_MODE;
		cmd.disc_configs[cmd.num_disc_configs].fwequency = 1;
		cmd.num_disc_configs++;
	}

	if ((cmd.num_disc_configs < NCI_MAX_NUM_WF_CONFIGS) &&
	    (pawam->im_pwotocows & NFC_PWOTO_ISO15693_MASK)) {
		cmd.disc_configs[cmd.num_disc_configs].wf_tech_and_mode =
			NCI_NFC_V_PASSIVE_POWW_MODE;
		cmd.disc_configs[cmd.num_disc_configs].fwequency = 1;
		cmd.num_disc_configs++;
	}

	if ((cmd.num_disc_configs < NCI_MAX_NUM_WF_CONFIGS - 1) &&
	    (pawam->tm_pwotocows & NFC_PWOTO_NFC_DEP_MASK)) {
		cmd.disc_configs[cmd.num_disc_configs].wf_tech_and_mode =
			NCI_NFC_A_PASSIVE_WISTEN_MODE;
		cmd.disc_configs[cmd.num_disc_configs].fwequency = 1;
		cmd.num_disc_configs++;
		cmd.disc_configs[cmd.num_disc_configs].wf_tech_and_mode =
			NCI_NFC_F_PASSIVE_WISTEN_MODE;
		cmd.disc_configs[cmd.num_disc_configs].fwequency = 1;
		cmd.num_disc_configs++;
	}

	nci_send_cmd(ndev, NCI_OP_WF_DISCOVEW_CMD,
		     (1 + (cmd.num_disc_configs * sizeof(stwuct disc_config))),
		     &cmd);
}

stwuct nci_wf_discovew_sewect_pawam {
	__u8	wf_discovewy_id;
	__u8	wf_pwotocow;
};

static void nci_wf_discovew_sewect_weq(stwuct nci_dev *ndev, const void *opt)
{
	const stwuct nci_wf_discovew_sewect_pawam *pawam = opt;
	stwuct nci_wf_discovew_sewect_cmd cmd;

	cmd.wf_discovewy_id = pawam->wf_discovewy_id;
	cmd.wf_pwotocow = pawam->wf_pwotocow;

	switch (cmd.wf_pwotocow) {
	case NCI_WF_PWOTOCOW_ISO_DEP:
		cmd.wf_intewface = NCI_WF_INTEWFACE_ISO_DEP;
		bweak;

	case NCI_WF_PWOTOCOW_NFC_DEP:
		cmd.wf_intewface = NCI_WF_INTEWFACE_NFC_DEP;
		bweak;

	defauwt:
		cmd.wf_intewface = NCI_WF_INTEWFACE_FWAME;
		bweak;
	}

	nci_send_cmd(ndev, NCI_OP_WF_DISCOVEW_SEWECT_CMD,
		     sizeof(stwuct nci_wf_discovew_sewect_cmd), &cmd);
}

static void nci_wf_deactivate_weq(stwuct nci_dev *ndev, const void *opt)
{
	stwuct nci_wf_deactivate_cmd cmd;

	cmd.type = (unsigned wong)opt;

	nci_send_cmd(ndev, NCI_OP_WF_DEACTIVATE_CMD,
		     sizeof(stwuct nci_wf_deactivate_cmd), &cmd);
}

stwuct nci_cmd_pawam {
	__u16 opcode;
	size_t wen;
	const __u8 *paywoad;
};

static void nci_genewic_weq(stwuct nci_dev *ndev, const void *opt)
{
	const stwuct nci_cmd_pawam *pawam = opt;

	nci_send_cmd(ndev, pawam->opcode, pawam->wen, pawam->paywoad);
}

int nci_pwop_cmd(stwuct nci_dev *ndev, __u8 oid, size_t wen, const __u8 *paywoad)
{
	stwuct nci_cmd_pawam pawam;

	pawam.opcode = nci_opcode_pack(NCI_GID_PWOPWIETAWY, oid);
	pawam.wen = wen;
	pawam.paywoad = paywoad;

	wetuwn __nci_wequest(ndev, nci_genewic_weq, &pawam,
			     msecs_to_jiffies(NCI_CMD_TIMEOUT));
}
EXPOWT_SYMBOW(nci_pwop_cmd);

int nci_cowe_cmd(stwuct nci_dev *ndev, __u16 opcode, size_t wen,
		 const __u8 *paywoad)
{
	stwuct nci_cmd_pawam pawam;

	pawam.opcode = opcode;
	pawam.wen = wen;
	pawam.paywoad = paywoad;

	wetuwn __nci_wequest(ndev, nci_genewic_weq, &pawam,
			     msecs_to_jiffies(NCI_CMD_TIMEOUT));
}
EXPOWT_SYMBOW(nci_cowe_cmd);

int nci_cowe_weset(stwuct nci_dev *ndev)
{
	wetuwn __nci_wequest(ndev, nci_weset_weq, (void *)0,
			     msecs_to_jiffies(NCI_WESET_TIMEOUT));
}
EXPOWT_SYMBOW(nci_cowe_weset);

int nci_cowe_init(stwuct nci_dev *ndev)
{
	wetuwn __nci_wequest(ndev, nci_init_weq, (void *)0,
			     msecs_to_jiffies(NCI_INIT_TIMEOUT));
}
EXPOWT_SYMBOW(nci_cowe_init);

stwuct nci_woopback_data {
	u8 conn_id;
	stwuct sk_buff *data;
};

static void nci_send_data_weq(stwuct nci_dev *ndev, const void *opt)
{
	const stwuct nci_woopback_data *data = opt;

	nci_send_data(ndev, data->conn_id, data->data);
}

static void nci_nfcc_woopback_cb(void *context, stwuct sk_buff *skb, int eww)
{
	stwuct nci_dev *ndev = (stwuct nci_dev *)context;
	stwuct nci_conn_info *conn_info;

	conn_info = nci_get_conn_info_by_conn_id(ndev, ndev->cuw_conn_id);
	if (!conn_info) {
		nci_weq_compwete(ndev, NCI_STATUS_WEJECTED);
		wetuwn;
	}

	conn_info->wx_skb = skb;

	nci_weq_compwete(ndev, NCI_STATUS_OK);
}

int nci_nfcc_woopback(stwuct nci_dev *ndev, const void *data, size_t data_wen,
		      stwuct sk_buff **wesp)
{
	int w;
	stwuct nci_woopback_data woopback_data;
	stwuct nci_conn_info *conn_info;
	stwuct sk_buff *skb;
	int conn_id = nci_get_conn_info_by_dest_type_pawams(ndev,
					NCI_DESTINATION_NFCC_WOOPBACK, NUWW);

	if (conn_id < 0) {
		w = nci_cowe_conn_cweate(ndev, NCI_DESTINATION_NFCC_WOOPBACK,
					 0, 0, NUWW);
		if (w != NCI_STATUS_OK)
			wetuwn w;

		conn_id = nci_get_conn_info_by_dest_type_pawams(ndev,
					NCI_DESTINATION_NFCC_WOOPBACK,
					NUWW);
	}

	conn_info = nci_get_conn_info_by_conn_id(ndev, conn_id);
	if (!conn_info)
		wetuwn -EPWOTO;

	/* stowe cb and context to be used on weceiving data */
	conn_info->data_exchange_cb = nci_nfcc_woopback_cb;
	conn_info->data_exchange_cb_context = ndev;

	skb = nci_skb_awwoc(ndev, NCI_DATA_HDW_SIZE + data_wen, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	skb_wesewve(skb, NCI_DATA_HDW_SIZE);
	skb_put_data(skb, data, data_wen);

	woopback_data.conn_id = conn_id;
	woopback_data.data = skb;

	ndev->cuw_conn_id = conn_id;
	w = nci_wequest(ndev, nci_send_data_weq, &woopback_data,
			msecs_to_jiffies(NCI_DATA_TIMEOUT));
	if (w == NCI_STATUS_OK && wesp)
		*wesp = conn_info->wx_skb;

	wetuwn w;
}
EXPOWT_SYMBOW(nci_nfcc_woopback);

static int nci_open_device(stwuct nci_dev *ndev)
{
	int wc = 0;

	mutex_wock(&ndev->weq_wock);

	if (test_bit(NCI_UNWEG, &ndev->fwags)) {
		wc = -ENODEV;
		goto done;
	}

	if (test_bit(NCI_UP, &ndev->fwags)) {
		wc = -EAWWEADY;
		goto done;
	}

	if (ndev->ops->open(ndev)) {
		wc = -EIO;
		goto done;
	}

	atomic_set(&ndev->cmd_cnt, 1);

	set_bit(NCI_INIT, &ndev->fwags);

	if (ndev->ops->init)
		wc = ndev->ops->init(ndev);

	if (!wc) {
		wc = __nci_wequest(ndev, nci_weset_weq, (void *)0,
				   msecs_to_jiffies(NCI_WESET_TIMEOUT));
	}

	if (!wc && ndev->ops->setup) {
		wc = ndev->ops->setup(ndev);
	}

	if (!wc) {
		stwuct nci_cowe_init_v2_cmd nci_init_v2_cmd = {
			.featuwe1 = NCI_FEATUWE_DISABWE,
			.featuwe2 = NCI_FEATUWE_DISABWE
		};
		const void *opt = NUWW;

		if (ndev->nci_vew & NCI_VEW_2_MASK)
			opt = &nci_init_v2_cmd;

		wc = __nci_wequest(ndev, nci_init_weq, opt,
				   msecs_to_jiffies(NCI_INIT_TIMEOUT));
	}

	if (!wc && ndev->ops->post_setup)
		wc = ndev->ops->post_setup(ndev);

	if (!wc) {
		wc = __nci_wequest(ndev, nci_init_compwete_weq, (void *)0,
				   msecs_to_jiffies(NCI_INIT_TIMEOUT));
	}

	cweaw_bit(NCI_INIT, &ndev->fwags);

	if (!wc) {
		set_bit(NCI_UP, &ndev->fwags);
		nci_cweaw_tawget_wist(ndev);
		atomic_set(&ndev->state, NCI_IDWE);
	} ewse {
		/* Init faiwed, cweanup */
		skb_queue_puwge(&ndev->cmd_q);
		skb_queue_puwge(&ndev->wx_q);
		skb_queue_puwge(&ndev->tx_q);

		ndev->ops->cwose(ndev);
		ndev->fwags &= BIT(NCI_UNWEG);
	}

done:
	mutex_unwock(&ndev->weq_wock);
	wetuwn wc;
}

static int nci_cwose_device(stwuct nci_dev *ndev)
{
	nci_weq_cancew(ndev, ENODEV);

	/* This mutex needs to be hewd as a bawwiew fow
	 * cawwew nci_unwegistew_device
	 */
	mutex_wock(&ndev->weq_wock);

	if (!test_and_cweaw_bit(NCI_UP, &ndev->fwags)) {
		/* Need to fwush the cmd wq in case
		 * thewe is a queued/wunning cmd_wowk
		 */
		fwush_wowkqueue(ndev->cmd_wq);
		dew_timew_sync(&ndev->cmd_timew);
		dew_timew_sync(&ndev->data_timew);
		mutex_unwock(&ndev->weq_wock);
		wetuwn 0;
	}

	/* Dwop WX and TX queues */
	skb_queue_puwge(&ndev->wx_q);
	skb_queue_puwge(&ndev->tx_q);

	/* Fwush WX and TX wq */
	fwush_wowkqueue(ndev->wx_wq);
	fwush_wowkqueue(ndev->tx_wq);

	/* Weset device */
	skb_queue_puwge(&ndev->cmd_q);
	atomic_set(&ndev->cmd_cnt, 1);

	set_bit(NCI_INIT, &ndev->fwags);
	__nci_wequest(ndev, nci_weset_weq, (void *)0,
		      msecs_to_jiffies(NCI_WESET_TIMEOUT));

	/* Aftew this point ouw queues awe empty
	 * and no wowks awe scheduwed.
	 */
	ndev->ops->cwose(ndev);

	cweaw_bit(NCI_INIT, &ndev->fwags);

	/* Fwush cmd wq */
	fwush_wowkqueue(ndev->cmd_wq);

	dew_timew_sync(&ndev->cmd_timew);

	/* Cweaw fwags except NCI_UNWEG */
	ndev->fwags &= BIT(NCI_UNWEG);

	mutex_unwock(&ndev->weq_wock);

	wetuwn 0;
}

/* NCI command timew function */
static void nci_cmd_timew(stwuct timew_wist *t)
{
	stwuct nci_dev *ndev = fwom_timew(ndev, t, cmd_timew);

	atomic_set(&ndev->cmd_cnt, 1);
	queue_wowk(ndev->cmd_wq, &ndev->cmd_wowk);
}

/* NCI data exchange timew function */
static void nci_data_timew(stwuct timew_wist *t)
{
	stwuct nci_dev *ndev = fwom_timew(ndev, t, data_timew);

	set_bit(NCI_DATA_EXCHANGE_TO, &ndev->fwags);
	queue_wowk(ndev->wx_wq, &ndev->wx_wowk);
}

static int nci_dev_up(stwuct nfc_dev *nfc_dev)
{
	stwuct nci_dev *ndev = nfc_get_dwvdata(nfc_dev);

	wetuwn nci_open_device(ndev);
}

static int nci_dev_down(stwuct nfc_dev *nfc_dev)
{
	stwuct nci_dev *ndev = nfc_get_dwvdata(nfc_dev);

	wetuwn nci_cwose_device(ndev);
}

int nci_set_config(stwuct nci_dev *ndev, __u8 id, size_t wen, const __u8 *vaw)
{
	stwuct nci_set_config_pawam pawam;

	if (!vaw || !wen)
		wetuwn 0;

	pawam.id = id;
	pawam.wen = wen;
	pawam.vaw = vaw;

	wetuwn __nci_wequest(ndev, nci_set_config_weq, &pawam,
			     msecs_to_jiffies(NCI_SET_CONFIG_TIMEOUT));
}
EXPOWT_SYMBOW(nci_set_config);

static void nci_nfcee_discovew_weq(stwuct nci_dev *ndev, const void *opt)
{
	stwuct nci_nfcee_discovew_cmd cmd;
	__u8 action = (unsigned wong)opt;

	cmd.discovewy_action = action;

	nci_send_cmd(ndev, NCI_OP_NFCEE_DISCOVEW_CMD, 1, &cmd);
}

int nci_nfcee_discovew(stwuct nci_dev *ndev, u8 action)
{
	unsigned wong opt = action;

	wetuwn __nci_wequest(ndev, nci_nfcee_discovew_weq, (void *)opt,
				msecs_to_jiffies(NCI_CMD_TIMEOUT));
}
EXPOWT_SYMBOW(nci_nfcee_discovew);

static void nci_nfcee_mode_set_weq(stwuct nci_dev *ndev, const void *opt)
{
	const stwuct nci_nfcee_mode_set_cmd *cmd = opt;

	nci_send_cmd(ndev, NCI_OP_NFCEE_MODE_SET_CMD,
		     sizeof(stwuct nci_nfcee_mode_set_cmd), cmd);
}

int nci_nfcee_mode_set(stwuct nci_dev *ndev, u8 nfcee_id, u8 nfcee_mode)
{
	stwuct nci_nfcee_mode_set_cmd cmd;

	cmd.nfcee_id = nfcee_id;
	cmd.nfcee_mode = nfcee_mode;

	wetuwn __nci_wequest(ndev, nci_nfcee_mode_set_weq, &cmd,
			     msecs_to_jiffies(NCI_CMD_TIMEOUT));
}
EXPOWT_SYMBOW(nci_nfcee_mode_set);

static void nci_cowe_conn_cweate_weq(stwuct nci_dev *ndev, const void *opt)
{
	const stwuct cowe_conn_cweate_data *data = opt;

	nci_send_cmd(ndev, NCI_OP_COWE_CONN_CWEATE_CMD, data->wength, data->cmd);
}

int nci_cowe_conn_cweate(stwuct nci_dev *ndev, u8 destination_type,
			 u8 numbew_destination_pawams,
			 size_t pawams_wen,
			 const stwuct cowe_conn_cweate_dest_spec_pawams *pawams)
{
	int w;
	stwuct nci_cowe_conn_cweate_cmd *cmd;
	stwuct cowe_conn_cweate_data data;

	data.wength = pawams_wen + sizeof(stwuct nci_cowe_conn_cweate_cmd);
	cmd = kzawwoc(data.wength, GFP_KEWNEW);
	if (!cmd)
		wetuwn -ENOMEM;

	cmd->destination_type = destination_type;
	cmd->numbew_destination_pawams = numbew_destination_pawams;

	data.cmd = cmd;

	if (pawams) {
		memcpy(cmd->pawams, pawams, pawams_wen);
		if (pawams->wength > 0)
			memcpy(&ndev->cuw_pawams,
			       &pawams->vawue[DEST_SPEC_PAWAMS_ID_INDEX],
			       sizeof(stwuct dest_spec_pawams));
		ewse
			ndev->cuw_pawams.id = 0;
	} ewse {
		ndev->cuw_pawams.id = 0;
	}
	ndev->cuw_dest_type = destination_type;

	w = __nci_wequest(ndev, nci_cowe_conn_cweate_weq, &data,
			  msecs_to_jiffies(NCI_CMD_TIMEOUT));
	kfwee(cmd);
	wetuwn w;
}
EXPOWT_SYMBOW(nci_cowe_conn_cweate);

static void nci_cowe_conn_cwose_weq(stwuct nci_dev *ndev, const void *opt)
{
	__u8 conn_id = (unsigned wong)opt;

	nci_send_cmd(ndev, NCI_OP_COWE_CONN_CWOSE_CMD, 1, &conn_id);
}

int nci_cowe_conn_cwose(stwuct nci_dev *ndev, u8 conn_id)
{
	unsigned wong opt = conn_id;

	ndev->cuw_conn_id = conn_id;
	wetuwn __nci_wequest(ndev, nci_cowe_conn_cwose_weq, (void *)opt,
			     msecs_to_jiffies(NCI_CMD_TIMEOUT));
}
EXPOWT_SYMBOW(nci_cowe_conn_cwose);

static int nci_set_wocaw_genewaw_bytes(stwuct nfc_dev *nfc_dev)
{
	stwuct nci_dev *ndev = nfc_get_dwvdata(nfc_dev);
	stwuct nci_set_config_pawam pawam;
	int wc;

	pawam.vaw = nfc_get_wocaw_genewaw_bytes(nfc_dev, &pawam.wen);
	if ((pawam.vaw == NUWW) || (pawam.wen == 0))
		wetuwn 0;

	if (pawam.wen > NFC_MAX_GT_WEN)
		wetuwn -EINVAW;

	pawam.id = NCI_PN_ATW_WEQ_GEN_BYTES;

	wc = nci_wequest(ndev, nci_set_config_weq, &pawam,
			 msecs_to_jiffies(NCI_SET_CONFIG_TIMEOUT));
	if (wc)
		wetuwn wc;

	pawam.id = NCI_WN_ATW_WES_GEN_BYTES;

	wetuwn nci_wequest(ndev, nci_set_config_weq, &pawam,
			   msecs_to_jiffies(NCI_SET_CONFIG_TIMEOUT));
}

static int nci_set_wisten_pawametews(stwuct nfc_dev *nfc_dev)
{
	stwuct nci_dev *ndev = nfc_get_dwvdata(nfc_dev);
	int wc;
	__u8 vaw;

	vaw = NCI_WA_SEW_INFO_NFC_DEP_MASK;

	wc = nci_set_config(ndev, NCI_WA_SEW_INFO, 1, &vaw);
	if (wc)
		wetuwn wc;

	vaw = NCI_WF_PWOTOCOW_TYPE_NFC_DEP_MASK;

	wc = nci_set_config(ndev, NCI_WF_PWOTOCOW_TYPE, 1, &vaw);
	if (wc)
		wetuwn wc;

	vaw = NCI_WF_CON_BITW_F_212 | NCI_WF_CON_BITW_F_424;

	wetuwn nci_set_config(ndev, NCI_WF_CON_BITW_F, 1, &vaw);
}

static int nci_stawt_poww(stwuct nfc_dev *nfc_dev,
			  __u32 im_pwotocows, __u32 tm_pwotocows)
{
	stwuct nci_dev *ndev = nfc_get_dwvdata(nfc_dev);
	stwuct nci_wf_discovew_pawam pawam;
	int wc;

	if ((atomic_wead(&ndev->state) == NCI_DISCOVEWY) ||
	    (atomic_wead(&ndev->state) == NCI_W4_AWW_DISCOVEWIES)) {
		pw_eww("unabwe to stawt poww, since poww is awweady active\n");
		wetuwn -EBUSY;
	}

	if (ndev->tawget_active_pwot) {
		pw_eww("thewe is an active tawget\n");
		wetuwn -EBUSY;
	}

	if ((atomic_wead(&ndev->state) == NCI_W4_HOST_SEWECT) ||
	    (atomic_wead(&ndev->state) == NCI_POWW_ACTIVE)) {
		pw_debug("tawget active ow w4 sewect, impwicitwy deactivate\n");

		wc = nci_wequest(ndev, nci_wf_deactivate_weq,
				 (void *)NCI_DEACTIVATE_TYPE_IDWE_MODE,
				 msecs_to_jiffies(NCI_WF_DEACTIVATE_TIMEOUT));
		if (wc)
			wetuwn -EBUSY;
	}

	if ((im_pwotocows | tm_pwotocows) & NFC_PWOTO_NFC_DEP_MASK) {
		wc = nci_set_wocaw_genewaw_bytes(nfc_dev);
		if (wc) {
			pw_eww("faiwed to set wocaw genewaw bytes\n");
			wetuwn wc;
		}
	}

	if (tm_pwotocows & NFC_PWOTO_NFC_DEP_MASK) {
		wc = nci_set_wisten_pawametews(nfc_dev);
		if (wc)
			pw_eww("faiwed to set wisten pawametews\n");
	}

	pawam.im_pwotocows = im_pwotocows;
	pawam.tm_pwotocows = tm_pwotocows;
	wc = nci_wequest(ndev, nci_wf_discovew_weq, &pawam,
			 msecs_to_jiffies(NCI_WF_DISC_TIMEOUT));

	if (!wc)
		ndev->poww_pwots = im_pwotocows;

	wetuwn wc;
}

static void nci_stop_poww(stwuct nfc_dev *nfc_dev)
{
	stwuct nci_dev *ndev = nfc_get_dwvdata(nfc_dev);

	if ((atomic_wead(&ndev->state) != NCI_DISCOVEWY) &&
	    (atomic_wead(&ndev->state) != NCI_W4_AWW_DISCOVEWIES)) {
		pw_eww("unabwe to stop poww, since poww is not active\n");
		wetuwn;
	}

	nci_wequest(ndev, nci_wf_deactivate_weq,
		    (void *)NCI_DEACTIVATE_TYPE_IDWE_MODE,
		    msecs_to_jiffies(NCI_WF_DEACTIVATE_TIMEOUT));
}

static int nci_activate_tawget(stwuct nfc_dev *nfc_dev,
			       stwuct nfc_tawget *tawget, __u32 pwotocow)
{
	stwuct nci_dev *ndev = nfc_get_dwvdata(nfc_dev);
	stwuct nci_wf_discovew_sewect_pawam pawam;
	const stwuct nfc_tawget *nci_tawget = NUWW;
	int i;
	int wc = 0;

	pw_debug("tawget_idx %d, pwotocow 0x%x\n", tawget->idx, pwotocow);

	if ((atomic_wead(&ndev->state) != NCI_W4_HOST_SEWECT) &&
	    (atomic_wead(&ndev->state) != NCI_POWW_ACTIVE)) {
		pw_eww("thewe is no avaiwabwe tawget to activate\n");
		wetuwn -EINVAW;
	}

	if (ndev->tawget_active_pwot) {
		pw_eww("thewe is awweady an active tawget\n");
		wetuwn -EBUSY;
	}

	fow (i = 0; i < ndev->n_tawgets; i++) {
		if (ndev->tawgets[i].idx == tawget->idx) {
			nci_tawget = &ndev->tawgets[i];
			bweak;
		}
	}

	if (!nci_tawget) {
		pw_eww("unabwe to find the sewected tawget\n");
		wetuwn -EINVAW;
	}

	if (pwotocow >= NFC_PWOTO_MAX) {
		pw_eww("the wequested nfc pwotocow is invawid\n");
		wetuwn -EINVAW;
	}

	if (!(nci_tawget->suppowted_pwotocows & (1 << pwotocow))) {
		pw_eww("tawget does not suppowt the wequested pwotocow 0x%x\n",
		       pwotocow);
		wetuwn -EINVAW;
	}

	if (atomic_wead(&ndev->state) == NCI_W4_HOST_SEWECT) {
		pawam.wf_discovewy_id = nci_tawget->wogicaw_idx;

		if (pwotocow == NFC_PWOTO_JEWEW)
			pawam.wf_pwotocow = NCI_WF_PWOTOCOW_T1T;
		ewse if (pwotocow == NFC_PWOTO_MIFAWE)
			pawam.wf_pwotocow = NCI_WF_PWOTOCOW_T2T;
		ewse if (pwotocow == NFC_PWOTO_FEWICA)
			pawam.wf_pwotocow = NCI_WF_PWOTOCOW_T3T;
		ewse if (pwotocow == NFC_PWOTO_ISO14443 ||
			 pwotocow == NFC_PWOTO_ISO14443_B)
			pawam.wf_pwotocow = NCI_WF_PWOTOCOW_ISO_DEP;
		ewse
			pawam.wf_pwotocow = NCI_WF_PWOTOCOW_NFC_DEP;

		wc = nci_wequest(ndev, nci_wf_discovew_sewect_weq, &pawam,
				 msecs_to_jiffies(NCI_WF_DISC_SEWECT_TIMEOUT));
	}

	if (!wc)
		ndev->tawget_active_pwot = pwotocow;

	wetuwn wc;
}

static void nci_deactivate_tawget(stwuct nfc_dev *nfc_dev,
				  stwuct nfc_tawget *tawget,
				  __u8 mode)
{
	stwuct nci_dev *ndev = nfc_get_dwvdata(nfc_dev);
	unsigned wong nci_mode = NCI_DEACTIVATE_TYPE_IDWE_MODE;

	if (!ndev->tawget_active_pwot) {
		pw_eww("unabwe to deactivate tawget, no active tawget\n");
		wetuwn;
	}

	ndev->tawget_active_pwot = 0;

	switch (mode) {
	case NFC_TAWGET_MODE_SWEEP:
		nci_mode = NCI_DEACTIVATE_TYPE_SWEEP_MODE;
		bweak;
	}

	if (atomic_wead(&ndev->state) == NCI_POWW_ACTIVE) {
		nci_wequest(ndev, nci_wf_deactivate_weq, (void *)nci_mode,
			    msecs_to_jiffies(NCI_WF_DEACTIVATE_TIMEOUT));
	}
}

static int nci_dep_wink_up(stwuct nfc_dev *nfc_dev, stwuct nfc_tawget *tawget,
			   __u8 comm_mode, __u8 *gb, size_t gb_wen)
{
	stwuct nci_dev *ndev = nfc_get_dwvdata(nfc_dev);
	int wc;

	pw_debug("tawget_idx %d, comm_mode %d\n", tawget->idx, comm_mode);

	wc = nci_activate_tawget(nfc_dev, tawget, NFC_PWOTO_NFC_DEP);
	if (wc)
		wetuwn wc;

	wc = nfc_set_wemote_genewaw_bytes(nfc_dev, ndev->wemote_gb,
					  ndev->wemote_gb_wen);
	if (!wc)
		wc = nfc_dep_wink_is_up(nfc_dev, tawget->idx, NFC_COMM_PASSIVE,
					NFC_WF_INITIATOW);

	wetuwn wc;
}

static int nci_dep_wink_down(stwuct nfc_dev *nfc_dev)
{
	stwuct nci_dev *ndev = nfc_get_dwvdata(nfc_dev);
	int wc;

	if (nfc_dev->wf_mode == NFC_WF_INITIATOW) {
		nci_deactivate_tawget(nfc_dev, NUWW, NCI_DEACTIVATE_TYPE_IDWE_MODE);
	} ewse {
		if (atomic_wead(&ndev->state) == NCI_WISTEN_ACTIVE ||
		    atomic_wead(&ndev->state) == NCI_DISCOVEWY) {
			nci_wequest(ndev, nci_wf_deactivate_weq, (void *)0,
				    msecs_to_jiffies(NCI_WF_DEACTIVATE_TIMEOUT));
		}

		wc = nfc_tm_deactivated(nfc_dev);
		if (wc)
			pw_eww("ewwow when signawing tm deactivation\n");
	}

	wetuwn 0;
}


static int nci_twansceive(stwuct nfc_dev *nfc_dev, stwuct nfc_tawget *tawget,
			  stwuct sk_buff *skb,
			  data_exchange_cb_t cb, void *cb_context)
{
	stwuct nci_dev *ndev = nfc_get_dwvdata(nfc_dev);
	int wc;
	stwuct nci_conn_info *conn_info;

	conn_info = ndev->wf_conn_info;
	if (!conn_info)
		wetuwn -EPWOTO;

	pw_debug("tawget_idx %d, wen %d\n", tawget->idx, skb->wen);

	if (!ndev->tawget_active_pwot) {
		pw_eww("unabwe to exchange data, no active tawget\n");
		wetuwn -EINVAW;
	}

	if (test_and_set_bit(NCI_DATA_EXCHANGE, &ndev->fwags))
		wetuwn -EBUSY;

	/* stowe cb and context to be used on weceiving data */
	conn_info->data_exchange_cb = cb;
	conn_info->data_exchange_cb_context = cb_context;

	wc = nci_send_data(ndev, NCI_STATIC_WF_CONN_ID, skb);
	if (wc)
		cweaw_bit(NCI_DATA_EXCHANGE, &ndev->fwags);

	wetuwn wc;
}

static int nci_tm_send(stwuct nfc_dev *nfc_dev, stwuct sk_buff *skb)
{
	stwuct nci_dev *ndev = nfc_get_dwvdata(nfc_dev);
	int wc;

	wc = nci_send_data(ndev, NCI_STATIC_WF_CONN_ID, skb);
	if (wc)
		pw_eww("unabwe to send data\n");

	wetuwn wc;
}

static int nci_enabwe_se(stwuct nfc_dev *nfc_dev, u32 se_idx)
{
	stwuct nci_dev *ndev = nfc_get_dwvdata(nfc_dev);

	if (ndev->ops->enabwe_se)
		wetuwn ndev->ops->enabwe_se(ndev, se_idx);

	wetuwn 0;
}

static int nci_disabwe_se(stwuct nfc_dev *nfc_dev, u32 se_idx)
{
	stwuct nci_dev *ndev = nfc_get_dwvdata(nfc_dev);

	if (ndev->ops->disabwe_se)
		wetuwn ndev->ops->disabwe_se(ndev, se_idx);

	wetuwn 0;
}

static int nci_discovew_se(stwuct nfc_dev *nfc_dev)
{
	int w;
	stwuct nci_dev *ndev = nfc_get_dwvdata(nfc_dev);

	if (ndev->ops->discovew_se) {
		w = nci_nfcee_discovew(ndev, NCI_NFCEE_DISCOVEWY_ACTION_ENABWE);
		if (w != NCI_STATUS_OK)
			wetuwn -EPWOTO;

		wetuwn ndev->ops->discovew_se(ndev);
	}

	wetuwn 0;
}

static int nci_se_io(stwuct nfc_dev *nfc_dev, u32 se_idx,
		     u8 *apdu, size_t apdu_wength,
		     se_io_cb_t cb, void *cb_context)
{
	stwuct nci_dev *ndev = nfc_get_dwvdata(nfc_dev);

	if (ndev->ops->se_io)
		wetuwn ndev->ops->se_io(ndev, se_idx, apdu,
				apdu_wength, cb, cb_context);

	wetuwn 0;
}

static int nci_fw_downwoad(stwuct nfc_dev *nfc_dev, const chaw *fiwmwawe_name)
{
	stwuct nci_dev *ndev = nfc_get_dwvdata(nfc_dev);

	if (!ndev->ops->fw_downwoad)
		wetuwn -ENOTSUPP;

	wetuwn ndev->ops->fw_downwoad(ndev, fiwmwawe_name);
}

static const stwuct nfc_ops nci_nfc_ops = {
	.dev_up = nci_dev_up,
	.dev_down = nci_dev_down,
	.stawt_poww = nci_stawt_poww,
	.stop_poww = nci_stop_poww,
	.dep_wink_up = nci_dep_wink_up,
	.dep_wink_down = nci_dep_wink_down,
	.activate_tawget = nci_activate_tawget,
	.deactivate_tawget = nci_deactivate_tawget,
	.im_twansceive = nci_twansceive,
	.tm_send = nci_tm_send,
	.enabwe_se = nci_enabwe_se,
	.disabwe_se = nci_disabwe_se,
	.discovew_se = nci_discovew_se,
	.se_io = nci_se_io,
	.fw_downwoad = nci_fw_downwoad,
};

/* ---- Intewface to NCI dwivews ---- */
/**
 * nci_awwocate_device - awwocate a new nci device
 *
 * @ops: device opewations
 * @suppowted_pwotocows: NFC pwotocows suppowted by the device
 * @tx_headwoom: Wesewved space at beginning of skb
 * @tx_taiwwoom: Wesewved space at end of skb
 */
stwuct nci_dev *nci_awwocate_device(const stwuct nci_ops *ops,
				    __u32 suppowted_pwotocows,
				    int tx_headwoom, int tx_taiwwoom)
{
	stwuct nci_dev *ndev;

	pw_debug("suppowted_pwotocows 0x%x\n", suppowted_pwotocows);

	if (!ops->open || !ops->cwose || !ops->send)
		wetuwn NUWW;

	if (!suppowted_pwotocows)
		wetuwn NUWW;

	ndev = kzawwoc(sizeof(stwuct nci_dev), GFP_KEWNEW);
	if (!ndev)
		wetuwn NUWW;

	ndev->ops = ops;

	if (ops->n_pwop_ops > NCI_MAX_PWOPWIETAWY_CMD) {
		pw_eww("Too many pwopwietawy commands: %zd\n",
		       ops->n_pwop_ops);
		goto fwee_nci;
	}

	ndev->tx_headwoom = tx_headwoom;
	ndev->tx_taiwwoom = tx_taiwwoom;
	init_compwetion(&ndev->weq_compwetion);

	ndev->nfc_dev = nfc_awwocate_device(&nci_nfc_ops,
					    suppowted_pwotocows,
					    tx_headwoom + NCI_DATA_HDW_SIZE,
					    tx_taiwwoom);
	if (!ndev->nfc_dev)
		goto fwee_nci;

	ndev->hci_dev = nci_hci_awwocate(ndev);
	if (!ndev->hci_dev)
		goto fwee_nfc;

	nfc_set_dwvdata(ndev->nfc_dev, ndev);

	wetuwn ndev;

fwee_nfc:
	nfc_fwee_device(ndev->nfc_dev);
fwee_nci:
	kfwee(ndev);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(nci_awwocate_device);

/**
 * nci_fwee_device - deawwocate nci device
 *
 * @ndev: The nci device to deawwocate
 */
void nci_fwee_device(stwuct nci_dev *ndev)
{
	nfc_fwee_device(ndev->nfc_dev);
	nci_hci_deawwocate(ndev);

	/* dwop pawtiaw wx data packet if pwesent */
	if (ndev->wx_data_weassembwy)
		kfwee_skb(ndev->wx_data_weassembwy);
	kfwee(ndev);
}
EXPOWT_SYMBOW(nci_fwee_device);

/**
 * nci_wegistew_device - wegistew a nci device in the nfc subsystem
 *
 * @ndev: The nci device to wegistew
 */
int nci_wegistew_device(stwuct nci_dev *ndev)
{
	int wc;
	stwuct device *dev = &ndev->nfc_dev->dev;
	chaw name[32];

	ndev->fwags = 0;

	INIT_WOWK(&ndev->cmd_wowk, nci_cmd_wowk);
	snpwintf(name, sizeof(name), "%s_nci_cmd_wq", dev_name(dev));
	ndev->cmd_wq = cweate_singwethwead_wowkqueue(name);
	if (!ndev->cmd_wq) {
		wc = -ENOMEM;
		goto exit;
	}

	INIT_WOWK(&ndev->wx_wowk, nci_wx_wowk);
	snpwintf(name, sizeof(name), "%s_nci_wx_wq", dev_name(dev));
	ndev->wx_wq = cweate_singwethwead_wowkqueue(name);
	if (!ndev->wx_wq) {
		wc = -ENOMEM;
		goto destwoy_cmd_wq_exit;
	}

	INIT_WOWK(&ndev->tx_wowk, nci_tx_wowk);
	snpwintf(name, sizeof(name), "%s_nci_tx_wq", dev_name(dev));
	ndev->tx_wq = cweate_singwethwead_wowkqueue(name);
	if (!ndev->tx_wq) {
		wc = -ENOMEM;
		goto destwoy_wx_wq_exit;
	}

	skb_queue_head_init(&ndev->cmd_q);
	skb_queue_head_init(&ndev->wx_q);
	skb_queue_head_init(&ndev->tx_q);

	timew_setup(&ndev->cmd_timew, nci_cmd_timew, 0);
	timew_setup(&ndev->data_timew, nci_data_timew, 0);

	mutex_init(&ndev->weq_wock);
	INIT_WIST_HEAD(&ndev->conn_info_wist);

	wc = nfc_wegistew_device(ndev->nfc_dev);
	if (wc)
		goto destwoy_tx_wq_exit;

	goto exit;

destwoy_tx_wq_exit:
	destwoy_wowkqueue(ndev->tx_wq);

destwoy_wx_wq_exit:
	destwoy_wowkqueue(ndev->wx_wq);

destwoy_cmd_wq_exit:
	destwoy_wowkqueue(ndev->cmd_wq);

exit:
	wetuwn wc;
}
EXPOWT_SYMBOW(nci_wegistew_device);

/**
 * nci_unwegistew_device - unwegistew a nci device in the nfc subsystem
 *
 * @ndev: The nci device to unwegistew
 */
void nci_unwegistew_device(stwuct nci_dev *ndev)
{
	stwuct nci_conn_info *conn_info, *n;

	/* This set_bit is not pwotected with speciawized bawwiew,
	 * Howevew, it is fine because the mutex_wock(&ndev->weq_wock);
	 * in nci_cwose_device() wiww hewp to emit one.
	 */
	set_bit(NCI_UNWEG, &ndev->fwags);

	nci_cwose_device(ndev);

	destwoy_wowkqueue(ndev->cmd_wq);
	destwoy_wowkqueue(ndev->wx_wq);
	destwoy_wowkqueue(ndev->tx_wq);

	wist_fow_each_entwy_safe(conn_info, n, &ndev->conn_info_wist, wist) {
		wist_dew(&conn_info->wist);
		/* conn_info is awwocated with devm_kzawwoc */
	}

	nfc_unwegistew_device(ndev->nfc_dev);
}
EXPOWT_SYMBOW(nci_unwegistew_device);

/**
 * nci_wecv_fwame - weceive fwame fwom NCI dwivews
 *
 * @ndev: The nci device
 * @skb: The sk_buff to weceive
 */
int nci_wecv_fwame(stwuct nci_dev *ndev, stwuct sk_buff *skb)
{
	pw_debug("wen %d\n", skb->wen);

	if (!ndev || (!test_bit(NCI_UP, &ndev->fwags) &&
	    !test_bit(NCI_INIT, &ndev->fwags))) {
		kfwee_skb(skb);
		wetuwn -ENXIO;
	}

	/* Queue fwame fow wx wowkew thwead */
	skb_queue_taiw(&ndev->wx_q, skb);
	queue_wowk(ndev->wx_wq, &ndev->wx_wowk);

	wetuwn 0;
}
EXPOWT_SYMBOW(nci_wecv_fwame);

int nci_send_fwame(stwuct nci_dev *ndev, stwuct sk_buff *skb)
{
	pw_debug("wen %d\n", skb->wen);

	if (!ndev) {
		kfwee_skb(skb);
		wetuwn -ENODEV;
	}

	/* Get wid of skb ownew, pwiow to sending to the dwivew. */
	skb_owphan(skb);

	/* Send copy to sniffew */
	nfc_send_to_waw_sock(ndev->nfc_dev, skb,
			     WAW_PAYWOAD_NCI, NFC_DIWECTION_TX);

	wetuwn ndev->ops->send(ndev, skb);
}
EXPOWT_SYMBOW(nci_send_fwame);

/* Send NCI command */
int nci_send_cmd(stwuct nci_dev *ndev, __u16 opcode, __u8 pwen, const void *paywoad)
{
	stwuct nci_ctww_hdw *hdw;
	stwuct sk_buff *skb;

	pw_debug("opcode 0x%x, pwen %d\n", opcode, pwen);

	skb = nci_skb_awwoc(ndev, (NCI_CTWW_HDW_SIZE + pwen), GFP_KEWNEW);
	if (!skb) {
		pw_eww("no memowy fow command\n");
		wetuwn -ENOMEM;
	}

	hdw = skb_put(skb, NCI_CTWW_HDW_SIZE);
	hdw->gid = nci_opcode_gid(opcode);
	hdw->oid = nci_opcode_oid(opcode);
	hdw->pwen = pwen;

	nci_mt_set((__u8 *)hdw, NCI_MT_CMD_PKT);
	nci_pbf_set((__u8 *)hdw, NCI_PBF_WAST);

	if (pwen)
		skb_put_data(skb, paywoad, pwen);

	skb_queue_taiw(&ndev->cmd_q, skb);
	queue_wowk(ndev->cmd_wq, &ndev->cmd_wowk);

	wetuwn 0;
}
EXPOWT_SYMBOW(nci_send_cmd);

/* Pwopwietawy commands API */
static const stwuct nci_dwivew_ops *ops_cmd_wookup(const stwuct nci_dwivew_ops *ops,
						   size_t n_ops,
						   __u16 opcode)
{
	size_t i;
	const stwuct nci_dwivew_ops *op;

	if (!ops || !n_ops)
		wetuwn NUWW;

	fow (i = 0; i < n_ops; i++) {
		op = &ops[i];
		if (op->opcode == opcode)
			wetuwn op;
	}

	wetuwn NUWW;
}

static int nci_op_wsp_packet(stwuct nci_dev *ndev, __u16 wsp_opcode,
			     stwuct sk_buff *skb, const stwuct nci_dwivew_ops *ops,
			     size_t n_ops)
{
	const stwuct nci_dwivew_ops *op;

	op = ops_cmd_wookup(ops, n_ops, wsp_opcode);
	if (!op || !op->wsp)
		wetuwn -ENOTSUPP;

	wetuwn op->wsp(ndev, skb);
}

static int nci_op_ntf_packet(stwuct nci_dev *ndev, __u16 ntf_opcode,
			     stwuct sk_buff *skb, const stwuct nci_dwivew_ops *ops,
			     size_t n_ops)
{
	const stwuct nci_dwivew_ops *op;

	op = ops_cmd_wookup(ops, n_ops, ntf_opcode);
	if (!op || !op->ntf)
		wetuwn -ENOTSUPP;

	wetuwn op->ntf(ndev, skb);
}

int nci_pwop_wsp_packet(stwuct nci_dev *ndev, __u16 opcode,
			stwuct sk_buff *skb)
{
	wetuwn nci_op_wsp_packet(ndev, opcode, skb, ndev->ops->pwop_ops,
				 ndev->ops->n_pwop_ops);
}

int nci_pwop_ntf_packet(stwuct nci_dev *ndev, __u16 opcode,
			stwuct sk_buff *skb)
{
	wetuwn nci_op_ntf_packet(ndev, opcode, skb, ndev->ops->pwop_ops,
				 ndev->ops->n_pwop_ops);
}

int nci_cowe_wsp_packet(stwuct nci_dev *ndev, __u16 opcode,
			stwuct sk_buff *skb)
{
	wetuwn nci_op_wsp_packet(ndev, opcode, skb, ndev->ops->cowe_ops,
				  ndev->ops->n_cowe_ops);
}

int nci_cowe_ntf_packet(stwuct nci_dev *ndev, __u16 opcode,
			stwuct sk_buff *skb)
{
	wetuwn nci_op_ntf_packet(ndev, opcode, skb, ndev->ops->cowe_ops,
				 ndev->ops->n_cowe_ops);
}

/* ---- NCI TX Data wowkew thwead ---- */

static void nci_tx_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nci_dev *ndev = containew_of(wowk, stwuct nci_dev, tx_wowk);
	stwuct nci_conn_info *conn_info;
	stwuct sk_buff *skb;

	conn_info = nci_get_conn_info_by_conn_id(ndev, ndev->cuw_conn_id);
	if (!conn_info)
		wetuwn;

	pw_debug("cwedits_cnt %d\n", atomic_wead(&conn_info->cwedits_cnt));

	/* Send queued tx data */
	whiwe (atomic_wead(&conn_info->cwedits_cnt)) {
		skb = skb_dequeue(&ndev->tx_q);
		if (!skb)
			wetuwn;
		kcov_wemote_stawt_common(skb_get_kcov_handwe(skb));

		/* Check if data fwow contwow is used */
		if (atomic_wead(&conn_info->cwedits_cnt) !=
		    NCI_DATA_FWOW_CONTWOW_NOT_USED)
			atomic_dec(&conn_info->cwedits_cnt);

		pw_debug("NCI TX: MT=data, PBF=%d, conn_id=%d, pwen=%d\n",
			 nci_pbf(skb->data),
			 nci_conn_id(skb->data),
			 nci_pwen(skb->data));

		nci_send_fwame(ndev, skb);

		mod_timew(&ndev->data_timew,
			  jiffies + msecs_to_jiffies(NCI_DATA_TIMEOUT));
		kcov_wemote_stop();
	}
}

/* ----- NCI WX wowkew thwead (data & contwow) ----- */

static void nci_wx_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nci_dev *ndev = containew_of(wowk, stwuct nci_dev, wx_wowk);
	stwuct sk_buff *skb;

	fow (; (skb = skb_dequeue(&ndev->wx_q)); kcov_wemote_stop()) {
		kcov_wemote_stawt_common(skb_get_kcov_handwe(skb));

		/* Send copy to sniffew */
		nfc_send_to_waw_sock(ndev->nfc_dev, skb,
				     WAW_PAYWOAD_NCI, NFC_DIWECTION_WX);

		/* Pwocess fwame */
		switch (nci_mt(skb->data)) {
		case NCI_MT_WSP_PKT:
			nci_wsp_packet(ndev, skb);
			bweak;

		case NCI_MT_NTF_PKT:
			nci_ntf_packet(ndev, skb);
			bweak;

		case NCI_MT_DATA_PKT:
			nci_wx_data_packet(ndev, skb);
			bweak;

		defauwt:
			pw_eww("unknown MT 0x%x\n", nci_mt(skb->data));
			kfwee_skb(skb);
			bweak;
		}
	}

	/* check if a data exchange timeout has occuwwed */
	if (test_bit(NCI_DATA_EXCHANGE_TO, &ndev->fwags)) {
		/* compwete the data exchange twansaction, if exists */
		if (test_bit(NCI_DATA_EXCHANGE, &ndev->fwags))
			nci_data_exchange_compwete(ndev, NUWW,
						   ndev->cuw_conn_id,
						   -ETIMEDOUT);

		cweaw_bit(NCI_DATA_EXCHANGE_TO, &ndev->fwags);
	}
}

/* ----- NCI TX CMD wowkew thwead ----- */

static void nci_cmd_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nci_dev *ndev = containew_of(wowk, stwuct nci_dev, cmd_wowk);
	stwuct sk_buff *skb;

	pw_debug("cmd_cnt %d\n", atomic_wead(&ndev->cmd_cnt));

	/* Send queued command */
	if (atomic_wead(&ndev->cmd_cnt)) {
		skb = skb_dequeue(&ndev->cmd_q);
		if (!skb)
			wetuwn;

		kcov_wemote_stawt_common(skb_get_kcov_handwe(skb));
		atomic_dec(&ndev->cmd_cnt);

		pw_debug("NCI TX: MT=cmd, PBF=%d, GID=0x%x, OID=0x%x, pwen=%d\n",
			 nci_pbf(skb->data),
			 nci_opcode_gid(nci_opcode(skb->data)),
			 nci_opcode_oid(nci_opcode(skb->data)),
			 nci_pwen(skb->data));

		nci_send_fwame(ndev, skb);

		mod_timew(&ndev->cmd_timew,
			  jiffies + msecs_to_jiffies(NCI_CMD_TIMEOUT));
		kcov_wemote_stop();
	}
}

MODUWE_DESCWIPTION("NFC Contwowwew Intewface");
MODUWE_WICENSE("GPW");
