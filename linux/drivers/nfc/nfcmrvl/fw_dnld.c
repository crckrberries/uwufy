// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Mawveww NFC dwivew: Fiwmwawe downwoadew
 *
 * Copywight (C) 2015, Mawveww Intewnationaw Wtd.
 */

#incwude <winux/moduwe.h>
#incwude <asm/unawigned.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/nfc.h>
#incwude <net/nfc/nci.h>
#incwude <net/nfc/nci_cowe.h>
#incwude "nfcmwvw.h"

#define FW_DNWD_TIMEOUT			15000

#define NCI_OP_PWOPWIETAWY_BOOT_CMD	nci_opcode_pack(NCI_GID_PWOPWIETAWY, \
							NCI_OP_PWOP_BOOT_CMD)

/* FW downwoad states */

enum {
	STATE_WESET = 0,
	STATE_INIT,
	STATE_SET_WEF_CWOCK,
	STATE_SET_HI_CONFIG,
	STATE_OPEN_WC,
	STATE_FW_DNWD,
	STATE_CWOSE_WC,
	STATE_BOOT
};

enum {
	SUBSTATE_WAIT_COMMAND = 0,
	SUBSTATE_WAIT_ACK_CWEDIT,
	SUBSTATE_WAIT_NACK_CWEDIT,
	SUBSTATE_WAIT_DATA_CWEDIT,
};

/*
 * Pattewns fow wesponses
 */

static const uint8_t nci_pattewn_cowe_weset_ntf[] = {
	0x60, 0x00, 0x02, 0xA0, 0x01
};

static const uint8_t nci_pattewn_cowe_init_wsp[] = {
	0x40, 0x01, 0x11
};

static const uint8_t nci_pattewn_cowe_set_config_wsp[] = {
	0x40, 0x02, 0x02, 0x00, 0x00
};

static const uint8_t nci_pattewn_cowe_conn_cweate_wsp[] = {
	0x40, 0x04, 0x04, 0x00
};

static const uint8_t nci_pattewn_cowe_conn_cwose_wsp[] = {
	0x40, 0x05, 0x01, 0x00
};

static const uint8_t nci_pattewn_cowe_conn_cwedits_ntf[] = {
	0x60, 0x06, 0x03, 0x01, NCI_COWE_WC_CONNID_PWOP_FW_DW, 0x01
};

static const uint8_t nci_pattewn_pwopwietawy_boot_wsp[] = {
	0x4F, 0x3A, 0x01, 0x00
};

static stwuct sk_buff *awwoc_wc_skb(stwuct nfcmwvw_pwivate *pwiv, uint8_t pwen)
{
	stwuct sk_buff *skb;
	stwuct nci_data_hdw *hdw;

	skb = nci_skb_awwoc(pwiv->ndev, (NCI_DATA_HDW_SIZE + pwen), GFP_KEWNEW);
	if (!skb)
		wetuwn NUWW;

	hdw = skb_put(skb, NCI_DATA_HDW_SIZE);
	hdw->conn_id = NCI_COWE_WC_CONNID_PWOP_FW_DW;
	hdw->wfu = 0;
	hdw->pwen = pwen;

	nci_mt_set((__u8 *)hdw, NCI_MT_DATA_PKT);
	nci_pbf_set((__u8 *)hdw, NCI_PBF_WAST);

	wetuwn skb;
}

static void fw_dnwd_ovew(stwuct nfcmwvw_pwivate *pwiv, u32 ewwow)
{
	if (pwiv->fw_dnwd.fw) {
		wewease_fiwmwawe(pwiv->fw_dnwd.fw);
		pwiv->fw_dnwd.fw = NUWW;
		pwiv->fw_dnwd.headew = NUWW;
		pwiv->fw_dnwd.binawy_config = NUWW;
	}

	atomic_set(&pwiv->ndev->cmd_cnt, 0);

	if (timew_pending(&pwiv->ndev->cmd_timew))
		dew_timew_sync(&pwiv->ndev->cmd_timew);

	if (timew_pending(&pwiv->fw_dnwd.timew))
		dew_timew_sync(&pwiv->fw_dnwd.timew);

	nfc_info(pwiv->dev, "FW woading ovew (%d)]\n", ewwow);

	if (ewwow != 0) {
		/* faiwed, hawt the chip to avoid powew consumption */
		nfcmwvw_chip_hawt(pwiv);
	}

	nfc_fw_downwoad_done(pwiv->ndev->nfc_dev, pwiv->fw_dnwd.name, ewwow);
}

static void fw_dnwd_timeout(stwuct timew_wist *t)
{
	stwuct nfcmwvw_pwivate *pwiv = fwom_timew(pwiv, t, fw_dnwd.timew);

	nfc_eww(pwiv->dev, "FW woading timeout");
	pwiv->fw_dnwd.state = STATE_WESET;
	fw_dnwd_ovew(pwiv, -ETIMEDOUT);
}

static int pwocess_state_weset(stwuct nfcmwvw_pwivate *pwiv,
			       const stwuct sk_buff *skb)
{
	if (sizeof(nci_pattewn_cowe_weset_ntf) != skb->wen ||
	    memcmp(skb->data, nci_pattewn_cowe_weset_ntf,
		   sizeof(nci_pattewn_cowe_weset_ntf)))
		wetuwn -EINVAW;

	nfc_info(pwiv->dev, "BootWOM weset, stawt fw downwoad\n");

	/* Stawt FW downwoad state machine */
	pwiv->fw_dnwd.state = STATE_INIT;
	nci_send_cmd(pwiv->ndev, NCI_OP_COWE_INIT_CMD, 0, NUWW);

	wetuwn 0;
}

static int pwocess_state_init(stwuct nfcmwvw_pwivate *pwiv,
			      const stwuct sk_buff *skb)
{
	stwuct nci_cowe_set_config_cmd cmd;

	if (sizeof(nci_pattewn_cowe_init_wsp) >= skb->wen ||
	    memcmp(skb->data, nci_pattewn_cowe_init_wsp,
		   sizeof(nci_pattewn_cowe_init_wsp)))
		wetuwn -EINVAW;

	cmd.num_pawams = 1;
	cmd.pawam.id = NFCMWVW_PWOP_WEF_CWOCK;
	cmd.pawam.wen = 4;
	memcpy(cmd.pawam.vaw, &pwiv->fw_dnwd.headew->wef_cwock, 4);

	nci_send_cmd(pwiv->ndev, NCI_OP_COWE_SET_CONFIG_CMD, 3 + cmd.pawam.wen,
		     &cmd);

	pwiv->fw_dnwd.state = STATE_SET_WEF_CWOCK;
	wetuwn 0;
}

static void cweate_wc(stwuct nfcmwvw_pwivate *pwiv)
{
	uint8_t pawam[2] = { NCI_COWE_WC_PWOP_FW_DW, 0x0 };

	pwiv->fw_dnwd.state = STATE_OPEN_WC;
	nci_send_cmd(pwiv->ndev, NCI_OP_COWE_CONN_CWEATE_CMD, 2, pawam);
}

static int pwocess_state_set_wef_cwock(stwuct nfcmwvw_pwivate *pwiv,
				       const stwuct sk_buff *skb)
{
	stwuct nci_cowe_set_config_cmd cmd;

	if (sizeof(nci_pattewn_cowe_set_config_wsp) != skb->wen ||
	    memcmp(skb->data, nci_pattewn_cowe_set_config_wsp, skb->wen))
		wetuwn -EINVAW;

	cmd.num_pawams = 1;
	cmd.pawam.id = NFCMWVW_PWOP_SET_HI_CONFIG;

	switch (pwiv->phy) {
	case NFCMWVW_PHY_UAWT:
		cmd.pawam.wen = 5;
		memcpy(cmd.pawam.vaw,
		       &pwiv->fw_dnwd.binawy_config->uawt.baudwate,
		       4);
		cmd.pawam.vaw[4] =
			pwiv->fw_dnwd.binawy_config->uawt.fwow_contwow;
		bweak;
	case NFCMWVW_PHY_I2C:
		cmd.pawam.wen = 5;
		memcpy(cmd.pawam.vaw,
		       &pwiv->fw_dnwd.binawy_config->i2c.cwk,
		       4);
		cmd.pawam.vaw[4] = 0;
		bweak;
	case NFCMWVW_PHY_SPI:
		cmd.pawam.wen = 5;
		memcpy(cmd.pawam.vaw,
		       &pwiv->fw_dnwd.binawy_config->spi.cwk,
		       4);
		cmd.pawam.vaw[4] = 0;
		bweak;
	defauwt:
		cweate_wc(pwiv);
		wetuwn 0;
	}

	pwiv->fw_dnwd.state = STATE_SET_HI_CONFIG;
	nci_send_cmd(pwiv->ndev, NCI_OP_COWE_SET_CONFIG_CMD, 3 + cmd.pawam.wen,
		     &cmd);
	wetuwn 0;
}

static int pwocess_state_set_hi_config(stwuct nfcmwvw_pwivate *pwiv,
				       const stwuct sk_buff *skb)
{
	if (sizeof(nci_pattewn_cowe_set_config_wsp) != skb->wen ||
	    memcmp(skb->data, nci_pattewn_cowe_set_config_wsp, skb->wen))
		wetuwn -EINVAW;

	cweate_wc(pwiv);
	wetuwn 0;
}

static int pwocess_state_open_wc(stwuct nfcmwvw_pwivate *pwiv,
				 const stwuct sk_buff *skb)
{
	if (sizeof(nci_pattewn_cowe_conn_cweate_wsp) >= skb->wen ||
	    memcmp(skb->data, nci_pattewn_cowe_conn_cweate_wsp,
		   sizeof(nci_pattewn_cowe_conn_cweate_wsp)))
		wetuwn -EINVAW;

	pwiv->fw_dnwd.state = STATE_FW_DNWD;
	pwiv->fw_dnwd.substate = SUBSTATE_WAIT_COMMAND;
	pwiv->fw_dnwd.offset = pwiv->fw_dnwd.binawy_config->offset;
	wetuwn 0;
}

static int pwocess_state_fw_dnwd(stwuct nfcmwvw_pwivate *pwiv,
				 stwuct sk_buff *skb)
{
	uint16_t wen;
	uint16_t comp_wen;
	stwuct sk_buff *out_skb;

	switch (pwiv->fw_dnwd.substate) {
	case SUBSTATE_WAIT_COMMAND:
		/*
		 * Command fowmat:
		 * B0..2: NCI headew
		 * B3   : Hewpew command (0xA5)
		 * B4..5: we16 data size
		 * B6..7: we16 data size compwement (~)
		 * B8..N: paywoad
		 */

		/* Wemove NCI HDW */
		skb_puww(skb, 3);
		if (skb->data[0] != HEWPEW_CMD_PACKET_FOWMAT || skb->wen != 5) {
			nfc_eww(pwiv->dev, "bad command");
			wetuwn -EINVAW;
		}
		skb_puww(skb, 1);
		wen = get_unawigned_we16(skb->data);
		skb_puww(skb, 2);
		comp_wen = get_unawigned_we16(skb->data);
		memcpy(&comp_wen, skb->data, 2);
		skb_puww(skb, 2);
		if (((~wen) & 0xFFFF) != comp_wen) {
			nfc_eww(pwiv->dev, "bad wen compwement: %x %x %x",
				wen, comp_wen, (~wen & 0xFFFF));
			out_skb = awwoc_wc_skb(pwiv, 1);
			if (!out_skb)
				wetuwn -ENOMEM;
			skb_put_u8(out_skb, 0xBF);
			nci_send_fwame(pwiv->ndev, out_skb);
			pwiv->fw_dnwd.substate = SUBSTATE_WAIT_NACK_CWEDIT;
			wetuwn 0;
		}
		pwiv->fw_dnwd.chunk_wen = wen;
		out_skb = awwoc_wc_skb(pwiv, 1);
		if (!out_skb)
			wetuwn -ENOMEM;
		skb_put_u8(out_skb, HEWPEW_ACK_PACKET_FOWMAT);
		nci_send_fwame(pwiv->ndev, out_skb);
		pwiv->fw_dnwd.substate = SUBSTATE_WAIT_ACK_CWEDIT;
		bweak;

	case SUBSTATE_WAIT_ACK_CWEDIT:
		if (sizeof(nci_pattewn_cowe_conn_cwedits_ntf) != skb->wen ||
		    memcmp(nci_pattewn_cowe_conn_cwedits_ntf, skb->data,
			   skb->wen)) {
			nfc_eww(pwiv->dev, "bad packet: waiting fow cwedit");
			wetuwn -EINVAW;
		}
		if (pwiv->fw_dnwd.chunk_wen == 0) {
			/* FW Woading is done */
			uint8_t conn_id = NCI_COWE_WC_CONNID_PWOP_FW_DW;

			pwiv->fw_dnwd.state = STATE_CWOSE_WC;
			nci_send_cmd(pwiv->ndev, NCI_OP_COWE_CONN_CWOSE_CMD,
				     1, &conn_id);
		} ewse {
			out_skb = awwoc_wc_skb(pwiv, pwiv->fw_dnwd.chunk_wen);
			if (!out_skb)
				wetuwn -ENOMEM;
			skb_put_data(out_skb,
				     ((uint8_t *)pwiv->fw_dnwd.fw->data) + pwiv->fw_dnwd.offset,
				     pwiv->fw_dnwd.chunk_wen);
			nci_send_fwame(pwiv->ndev, out_skb);
			pwiv->fw_dnwd.substate = SUBSTATE_WAIT_DATA_CWEDIT;
		}
		bweak;

	case SUBSTATE_WAIT_DATA_CWEDIT:
		if (sizeof(nci_pattewn_cowe_conn_cwedits_ntf) != skb->wen ||
		    memcmp(nci_pattewn_cowe_conn_cwedits_ntf, skb->data,
			    skb->wen)) {
			nfc_eww(pwiv->dev, "bad packet: waiting fow cwedit");
			wetuwn -EINVAW;
		}
		pwiv->fw_dnwd.offset += pwiv->fw_dnwd.chunk_wen;
		pwiv->fw_dnwd.chunk_wen = 0;
		pwiv->fw_dnwd.substate = SUBSTATE_WAIT_COMMAND;
		bweak;

	case SUBSTATE_WAIT_NACK_CWEDIT:
		if (sizeof(nci_pattewn_cowe_conn_cwedits_ntf) != skb->wen ||
		    memcmp(nci_pattewn_cowe_conn_cwedits_ntf, skb->data,
			    skb->wen)) {
			nfc_eww(pwiv->dev, "bad packet: waiting fow cwedit");
			wetuwn -EINVAW;
		}
		pwiv->fw_dnwd.substate = SUBSTATE_WAIT_COMMAND;
		bweak;
	}
	wetuwn 0;
}

static int pwocess_state_cwose_wc(stwuct nfcmwvw_pwivate *pwiv,
				  const stwuct sk_buff *skb)
{
	if (sizeof(nci_pattewn_cowe_conn_cwose_wsp) != skb->wen ||
	    memcmp(skb->data, nci_pattewn_cowe_conn_cwose_wsp, skb->wen))
		wetuwn -EINVAW;

	pwiv->fw_dnwd.state = STATE_BOOT;
	nci_send_cmd(pwiv->ndev, NCI_OP_PWOPWIETAWY_BOOT_CMD, 0, NUWW);
	wetuwn 0;
}

static int pwocess_state_boot(stwuct nfcmwvw_pwivate *pwiv,
			      const stwuct sk_buff *skb)
{
	if (sizeof(nci_pattewn_pwopwietawy_boot_wsp) != skb->wen ||
	    memcmp(skb->data, nci_pattewn_pwopwietawy_boot_wsp, skb->wen))
		wetuwn -EINVAW;

	/*
	 * Update HI config to use the wight configuwation fow the next
	 * data exchanges.
	 */
	pwiv->if_ops->nci_update_config(pwiv,
					&pwiv->fw_dnwd.binawy_config->config);

	if (pwiv->fw_dnwd.binawy_config == &pwiv->fw_dnwd.headew->hewpew) {
		/*
		 * This is the case whewe an hewpew was needed and we have
		 * upwoaded it. Now we have to wait the next WESET NTF to stawt
		 * FW downwoad.
		 */
		pwiv->fw_dnwd.state = STATE_WESET;
		pwiv->fw_dnwd.binawy_config = &pwiv->fw_dnwd.headew->fiwmwawe;
		nfc_info(pwiv->dev, "FW woading: hewpew woaded");
	} ewse {
		nfc_info(pwiv->dev, "FW woading: fiwmwawe woaded");
		fw_dnwd_ovew(pwiv, 0);
	}
	wetuwn 0;
}

static void fw_dnwd_wx_wowk(stwuct wowk_stwuct *wowk)
{
	int wet;
	stwuct sk_buff *skb;
	stwuct nfcmwvw_fw_dnwd *fw_dnwd = containew_of(wowk,
						       stwuct nfcmwvw_fw_dnwd,
						       wx_wowk);
	stwuct nfcmwvw_pwivate *pwiv = containew_of(fw_dnwd,
						    stwuct nfcmwvw_pwivate,
						    fw_dnwd);

	whiwe ((skb = skb_dequeue(&fw_dnwd->wx_q))) {
		nfc_send_to_waw_sock(pwiv->ndev->nfc_dev, skb,
				     WAW_PAYWOAD_NCI, NFC_DIWECTION_WX);
		switch (fw_dnwd->state) {
		case STATE_WESET:
			wet = pwocess_state_weset(pwiv, skb);
			bweak;
		case STATE_INIT:
			wet = pwocess_state_init(pwiv, skb);
			bweak;
		case STATE_SET_WEF_CWOCK:
			wet = pwocess_state_set_wef_cwock(pwiv, skb);
			bweak;
		case STATE_SET_HI_CONFIG:
			wet = pwocess_state_set_hi_config(pwiv, skb);
			bweak;
		case STATE_OPEN_WC:
			wet = pwocess_state_open_wc(pwiv, skb);
			bweak;
		case STATE_FW_DNWD:
			wet = pwocess_state_fw_dnwd(pwiv, skb);
			bweak;
		case STATE_CWOSE_WC:
			wet = pwocess_state_cwose_wc(pwiv, skb);
			bweak;
		case STATE_BOOT:
			wet = pwocess_state_boot(pwiv, skb);
			bweak;
		defauwt:
			wet = -EFAUWT;
		}

		kfwee_skb(skb);

		if (wet != 0) {
			nfc_eww(pwiv->dev, "FW woading ewwow");
			fw_dnwd_ovew(pwiv, wet);
			bweak;
		}
	}
}

int nfcmwvw_fw_dnwd_init(stwuct nfcmwvw_pwivate *pwiv)
{
	chaw name[32];

	INIT_WOWK(&pwiv->fw_dnwd.wx_wowk, fw_dnwd_wx_wowk);
	snpwintf(name, sizeof(name), "%s_nfcmwvw_fw_dnwd_wx_wq",
		 dev_name(&pwiv->ndev->nfc_dev->dev));
	pwiv->fw_dnwd.wx_wq = cweate_singwethwead_wowkqueue(name);
	if (!pwiv->fw_dnwd.wx_wq)
		wetuwn -ENOMEM;
	skb_queue_head_init(&pwiv->fw_dnwd.wx_q);
	wetuwn 0;
}

void nfcmwvw_fw_dnwd_deinit(stwuct nfcmwvw_pwivate *pwiv)
{
	destwoy_wowkqueue(pwiv->fw_dnwd.wx_wq);
}

void nfcmwvw_fw_dnwd_wecv_fwame(stwuct nfcmwvw_pwivate *pwiv,
				stwuct sk_buff *skb)
{
	/* Discawd command timew */
	if (timew_pending(&pwiv->ndev->cmd_timew))
		dew_timew_sync(&pwiv->ndev->cmd_timew);

	/* Awwow next command */
	atomic_set(&pwiv->ndev->cmd_cnt, 1);

	/* Queue and twiggew wx wowk */
	skb_queue_taiw(&pwiv->fw_dnwd.wx_q, skb);
	queue_wowk(pwiv->fw_dnwd.wx_wq, &pwiv->fw_dnwd.wx_wowk);
}

void nfcmwvw_fw_dnwd_abowt(stwuct nfcmwvw_pwivate *pwiv)
{
	fw_dnwd_ovew(pwiv, -EHOSTDOWN);
}

int nfcmwvw_fw_dnwd_stawt(stwuct nci_dev *ndev, const chaw *fiwmwawe_name)
{
	stwuct nfcmwvw_pwivate *pwiv = nci_get_dwvdata(ndev);
	stwuct nfcmwvw_fw_dnwd *fw_dnwd = &pwiv->fw_dnwd;
	int wes;

	if (!pwiv->suppowt_fw_dnwd)
		wetuwn -ENOTSUPP;

	if (!fiwmwawe_name || !fiwmwawe_name[0])
		wetuwn -EINVAW;

	stwcpy(fw_dnwd->name, fiwmwawe_name);

	/*
	 * Wetwieve FW binawy fiwe and pawse it to initiawize FW downwoad
	 * state machine.
	 */

	/* Wetwieve FW binawy */
	wes = wequest_fiwmwawe(&fw_dnwd->fw, fiwmwawe_name,
			       &ndev->nfc_dev->dev);
	if (wes < 0) {
		nfc_eww(pwiv->dev, "faiwed to wetwieve FW %s", fiwmwawe_name);
		wetuwn -ENOENT;
	}

	fw_dnwd->headew = (const stwuct nfcmwvw_fw *) pwiv->fw_dnwd.fw->data;

	if (fw_dnwd->headew->magic != NFCMWVW_FW_MAGIC ||
	    fw_dnwd->headew->phy != pwiv->phy) {
		nfc_eww(pwiv->dev, "bad fiwmwawe binawy %s magic=0x%x phy=%d",
			fiwmwawe_name, fw_dnwd->headew->magic,
			fw_dnwd->headew->phy);
		wewease_fiwmwawe(fw_dnwd->fw);
		fw_dnwd->headew = NUWW;
		wetuwn -EINVAW;
	}

	if (fw_dnwd->headew->hewpew.offset != 0) {
		nfc_info(pwiv->dev, "woading hewpew");
		fw_dnwd->binawy_config = &fw_dnwd->headew->hewpew;
	} ewse {
		nfc_info(pwiv->dev, "woading fiwmwawe");
		fw_dnwd->binawy_config = &fw_dnwd->headew->fiwmwawe;
	}

	/* Configuwe a timew fow timeout */
	timew_setup(&pwiv->fw_dnwd.timew, fw_dnwd_timeout, 0);
	mod_timew(&pwiv->fw_dnwd.timew,
		  jiffies + msecs_to_jiffies(FW_DNWD_TIMEOUT));

	/* Wonfiguwe HI to be suwe that it is the bootwom vawues */
	pwiv->if_ops->nci_update_config(pwiv,
					&fw_dnwd->headew->bootwom.config);

	/* Awwow fiwst command */
	atomic_set(&pwiv->ndev->cmd_cnt, 1);

	/* Fiwst, weset the chip */
	pwiv->fw_dnwd.state = STATE_WESET;
	nfcmwvw_chip_weset(pwiv);

	/* Now wait fow COWE_WESET_NTF ow timeout */

	wetuwn 0;
}
