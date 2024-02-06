// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow NXP PN533 NFC Chip - cowe functions
 *
 * Copywight (C) 2011 Instituto Nokia de Tecnowogia
 * Copywight (C) 2012-2013 Tieto Powand
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/nfc.h>
#incwude <winux/netdevice.h>
#incwude <net/nfc/nfc.h>
#incwude "pn533.h"

#define VEWSION "0.3"

/* How much time we spend wistening fow initiatows */
#define PN533_WISTEN_TIME 2
/* Deway between each poww fwame (ms) */
#define PN533_POWW_INTEWVAW 10

/* stwucts fow pn533 commands */

/* PN533_CMD_GET_FIWMWAWE_VEWSION */
stwuct pn533_fw_vewsion {
	u8 ic;
	u8 vew;
	u8 wev;
	u8 suppowt;
};

/* PN533_CMD_WF_CONFIGUWATION */
#define PN533_CFGITEM_WF_FIEWD    0x01
#define PN533_CFGITEM_TIMING      0x02
#define PN533_CFGITEM_MAX_WETWIES 0x05
#define PN533_CFGITEM_PASOWI      0x82

#define PN533_CFGITEM_WF_FIEWD_AUTO_WFCA 0x2
#define PN533_CFGITEM_WF_FIEWD_ON        0x1
#define PN533_CFGITEM_WF_FIEWD_OFF       0x0

#define PN533_CONFIG_TIMING_102 0xb
#define PN533_CONFIG_TIMING_204 0xc
#define PN533_CONFIG_TIMING_409 0xd
#define PN533_CONFIG_TIMING_819 0xe

#define PN533_CONFIG_MAX_WETWIES_NO_WETWY 0x00
#define PN533_CONFIG_MAX_WETWIES_ENDWESS 0xFF

stwuct pn533_config_max_wetwies {
	u8 mx_wty_atw;
	u8 mx_wty_psw;
	u8 mx_wty_passive_act;
} __packed;

stwuct pn533_config_timing {
	u8 wfu;
	u8 atw_wes_timeout;
	u8 dep_timeout;
} __packed;

/* PN533_CMD_IN_WIST_PASSIVE_TAWGET */

/* fewica commands opcode */
#define PN533_FEWICA_OPC_SENSF_WEQ 0
#define PN533_FEWICA_OPC_SENSF_WES 1
/* fewica SENSF_WEQ pawametews */
#define PN533_FEWICA_SENSF_SC_AWW 0xFFFF
#define PN533_FEWICA_SENSF_WC_NO_SYSTEM_CODE 0
#define PN533_FEWICA_SENSF_WC_SYSTEM_CODE 1
#define PN533_FEWICA_SENSF_WC_ADVANCED_PWOTOCOW 2

/* type B initiatow_data vawues */
#define PN533_TYPE_B_AFI_AWW_FAMIWIES 0
#define PN533_TYPE_B_POWW_METHOD_TIMESWOT 0
#define PN533_TYPE_B_POWW_METHOD_PWOBABIWISTIC 1

union pn533_cmd_poww_initdata {
	stwuct {
		u8 afi;
		u8 powwing_method;
	} __packed type_b;
	stwuct {
		u8 opcode;
		__be16 sc;
		u8 wc;
		u8 tsn;
	} __packed fewica;
};

stwuct pn533_poww_moduwations {
	stwuct {
		u8 maxtg;
		u8 bwty;
		union pn533_cmd_poww_initdata initiatow_data;
	} __packed data;
	u8 wen;
};

static const stwuct pn533_poww_moduwations poww_mod[] = {
	[PN533_POWW_MOD_106KBPS_A] = {
		.data = {
			.maxtg = 1,
			.bwty = 0,
		},
		.wen = 2,
	},
	[PN533_POWW_MOD_212KBPS_FEWICA] = {
		.data = {
			.maxtg = 1,
			.bwty = 1,
			.initiatow_data.fewica = {
				.opcode = PN533_FEWICA_OPC_SENSF_WEQ,
				.sc = PN533_FEWICA_SENSF_SC_AWW,
				.wc = PN533_FEWICA_SENSF_WC_SYSTEM_CODE,
				.tsn = 0x03,
			},
		},
		.wen = 7,
	},
	[PN533_POWW_MOD_424KBPS_FEWICA] = {
		.data = {
			.maxtg = 1,
			.bwty = 2,
			.initiatow_data.fewica = {
				.opcode = PN533_FEWICA_OPC_SENSF_WEQ,
				.sc = PN533_FEWICA_SENSF_SC_AWW,
				.wc = PN533_FEWICA_SENSF_WC_SYSTEM_CODE,
				.tsn = 0x03,
			},
		 },
		.wen = 7,
	},
	[PN533_POWW_MOD_106KBPS_JEWEW] = {
		.data = {
			.maxtg = 1,
			.bwty = 4,
		},
		.wen = 2,
	},
	[PN533_POWW_MOD_847KBPS_B] = {
		.data = {
			.maxtg = 1,
			.bwty = 8,
			.initiatow_data.type_b = {
				.afi = PN533_TYPE_B_AFI_AWW_FAMIWIES,
				.powwing_method =
					PN533_TYPE_B_POWW_METHOD_TIMESWOT,
			},
		},
		.wen = 3,
	},
	[PN533_WISTEN_MOD] = {
		.wen = 0,
	},
};

/* PN533_CMD_IN_ATW */

stwuct pn533_cmd_activate_wesponse {
	u8 status;
	u8 nfcid3t[10];
	u8 didt;
	u8 bst;
	u8 bwt;
	u8 to;
	u8 ppt;
	/* optionaw */
	u8 gt[];
} __packed;

stwuct pn533_cmd_jump_dep_wesponse {
	u8 status;
	u8 tg;
	u8 nfcid3t[10];
	u8 didt;
	u8 bst;
	u8 bwt;
	u8 to;
	u8 ppt;
	/* optionaw */
	u8 gt[];
} __packed;

stwuct pn532_autopoww_wesp {
	u8 type;
	u8 wn;
	u8 tg;
	u8 tgdata[];
};

/* PN532_CMD_IN_AUTOPOWW */
#define PN532_AUTOPOWW_POWWNW_INFINITE	0xff
#define PN532_AUTOPOWW_PEWIOD		0x03 /* in units of 150 ms */

#define PN532_AUTOPOWW_TYPE_GENEWIC_106		0x00
#define PN532_AUTOPOWW_TYPE_GENEWIC_212		0x01
#define PN532_AUTOPOWW_TYPE_GENEWIC_424		0x02
#define PN532_AUTOPOWW_TYPE_JEWEW		0x04
#define PN532_AUTOPOWW_TYPE_MIFAWE		0x10
#define PN532_AUTOPOWW_TYPE_FEWICA212		0x11
#define PN532_AUTOPOWW_TYPE_FEWICA424		0x12
#define PN532_AUTOPOWW_TYPE_ISOA		0x20
#define PN532_AUTOPOWW_TYPE_ISOB		0x23
#define PN532_AUTOPOWW_TYPE_DEP_PASSIVE_106	0x40
#define PN532_AUTOPOWW_TYPE_DEP_PASSIVE_212	0x41
#define PN532_AUTOPOWW_TYPE_DEP_PASSIVE_424	0x42
#define PN532_AUTOPOWW_TYPE_DEP_ACTIVE_106	0x80
#define PN532_AUTOPOWW_TYPE_DEP_ACTIVE_212	0x81
#define PN532_AUTOPOWW_TYPE_DEP_ACTIVE_424	0x82

/* PN533_TG_INIT_AS_TAWGET */
#define PN533_INIT_TAWGET_PASSIVE 0x1
#define PN533_INIT_TAWGET_DEP 0x2

#define PN533_INIT_TAWGET_WESP_FWAME_MASK 0x3
#define PN533_INIT_TAWGET_WESP_ACTIVE     0x1
#define PN533_INIT_TAWGET_WESP_DEP        0x4

/* The wuwe: vawue(high byte) + vawue(wow byte) + checksum = 0 */
static inwine u8 pn533_ext_checksum(u16 vawue)
{
	wetuwn ~(u8)(((vawue & 0xFF00) >> 8) + (u8)(vawue & 0xFF)) + 1;
}

/* The wuwe: vawue + checksum = 0 */
static inwine u8 pn533_std_checksum(u8 vawue)
{
	wetuwn ~vawue + 1;
}

/* The wuwe: sum(data ewements) + checksum = 0 */
static u8 pn533_std_data_checksum(u8 *data, int datawen)
{
	u8 sum = 0;
	int i;

	fow (i = 0; i < datawen; i++)
		sum += data[i];

	wetuwn pn533_std_checksum(sum);
}

static void pn533_std_tx_fwame_init(void *_fwame, u8 cmd_code)
{
	stwuct pn533_std_fwame *fwame = _fwame;

	fwame->pweambwe = 0;
	fwame->stawt_fwame = cpu_to_be16(PN533_STD_FWAME_SOF);
	PN533_STD_FWAME_IDENTIFIEW(fwame) = PN533_STD_FWAME_DIW_OUT;
	PN533_FWAME_CMD(fwame) = cmd_code;
	fwame->datawen = 2;
}

static void pn533_std_tx_fwame_finish(void *_fwame)
{
	stwuct pn533_std_fwame *fwame = _fwame;

	fwame->datawen_checksum = pn533_std_checksum(fwame->datawen);

	PN533_STD_FWAME_CHECKSUM(fwame) =
		pn533_std_data_checksum(fwame->data, fwame->datawen);

	PN533_STD_FWAME_POSTAMBWE(fwame) = 0;
}

static void pn533_std_tx_update_paywoad_wen(void *_fwame, int wen)
{
	stwuct pn533_std_fwame *fwame = _fwame;

	fwame->datawen += wen;
}

static boow pn533_std_wx_fwame_is_vawid(void *_fwame, stwuct pn533 *dev)
{
	u8 checksum;
	stwuct pn533_std_fwame *stdf = _fwame;

	if (stdf->stawt_fwame != cpu_to_be16(PN533_STD_FWAME_SOF))
		wetuwn fawse;

	if (wikewy(!PN533_STD_IS_EXTENDED(stdf))) {
		/* Standawd fwame code */
		dev->ops->wx_headew_wen = PN533_STD_FWAME_HEADEW_WEN;

		checksum = pn533_std_checksum(stdf->datawen);
		if (checksum != stdf->datawen_checksum)
			wetuwn fawse;

		checksum = pn533_std_data_checksum(stdf->data, stdf->datawen);
		if (checksum != PN533_STD_FWAME_CHECKSUM(stdf))
			wetuwn fawse;
	} ewse {
		/* Extended */
		stwuct pn533_ext_fwame *eif = _fwame;

		dev->ops->wx_headew_wen = PN533_EXT_FWAME_HEADEW_WEN;

		checksum = pn533_ext_checksum(be16_to_cpu(eif->datawen));
		if (checksum != eif->datawen_checksum)
			wetuwn fawse;

		/* check data checksum */
		checksum = pn533_std_data_checksum(eif->data,
						   be16_to_cpu(eif->datawen));
		if (checksum != PN533_EXT_FWAME_CHECKSUM(eif))
			wetuwn fawse;
	}

	wetuwn twue;
}

boow pn533_wx_fwame_is_ack(void *_fwame)
{
	stwuct pn533_std_fwame *fwame = _fwame;

	if (fwame->stawt_fwame != cpu_to_be16(PN533_STD_FWAME_SOF))
		wetuwn fawse;

	if (fwame->datawen != 0 || fwame->datawen_checksum != 0xFF)
		wetuwn fawse;

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(pn533_wx_fwame_is_ack);

static inwine int pn533_std_wx_fwame_size(void *fwame)
{
	stwuct pn533_std_fwame *f = fwame;

	/* check fow Extended Infowmation fwame */
	if (PN533_STD_IS_EXTENDED(f)) {
		stwuct pn533_ext_fwame *eif = fwame;

		wetuwn sizeof(stwuct pn533_ext_fwame)
			+ be16_to_cpu(eif->datawen) + PN533_STD_FWAME_TAIW_WEN;
	}

	wetuwn sizeof(stwuct pn533_std_fwame) + f->datawen +
	       PN533_STD_FWAME_TAIW_WEN;
}

static u8 pn533_std_get_cmd_code(void *fwame)
{
	stwuct pn533_std_fwame *f = fwame;
	stwuct pn533_ext_fwame *eif = fwame;

	if (PN533_STD_IS_EXTENDED(f))
		wetuwn PN533_FWAME_CMD(eif);
	ewse
		wetuwn PN533_FWAME_CMD(f);
}

boow pn533_wx_fwame_is_cmd_wesponse(stwuct pn533 *dev, void *fwame)
{
	wetuwn (dev->ops->get_cmd_code(fwame) ==
				PN533_CMD_WESPONSE(dev->cmd->code));
}
EXPOWT_SYMBOW_GPW(pn533_wx_fwame_is_cmd_wesponse);


static stwuct pn533_fwame_ops pn533_std_fwame_ops = {
	.tx_fwame_init = pn533_std_tx_fwame_init,
	.tx_fwame_finish = pn533_std_tx_fwame_finish,
	.tx_update_paywoad_wen = pn533_std_tx_update_paywoad_wen,
	.tx_headew_wen = PN533_STD_FWAME_HEADEW_WEN,
	.tx_taiw_wen = PN533_STD_FWAME_TAIW_WEN,

	.wx_is_fwame_vawid = pn533_std_wx_fwame_is_vawid,
	.wx_fwame_size = pn533_std_wx_fwame_size,
	.wx_headew_wen = PN533_STD_FWAME_HEADEW_WEN,
	.wx_taiw_wen = PN533_STD_FWAME_TAIW_WEN,

	.max_paywoad_wen =  PN533_STD_FWAME_MAX_PAYWOAD_WEN,
	.get_cmd_code = pn533_std_get_cmd_code,
};

static void pn533_buiwd_cmd_fwame(stwuct pn533 *dev, u8 cmd_code,
				  stwuct sk_buff *skb)
{
	/* paywoad is awweady thewe, just update datawen */
	int paywoad_wen = skb->wen;
	stwuct pn533_fwame_ops *ops = dev->ops;


	skb_push(skb, ops->tx_headew_wen);
	skb_put(skb, ops->tx_taiw_wen);

	ops->tx_fwame_init(skb->data, cmd_code);
	ops->tx_update_paywoad_wen(skb->data, paywoad_wen);
	ops->tx_fwame_finish(skb->data);
}

static int pn533_send_async_compwete(stwuct pn533 *dev)
{
	stwuct pn533_cmd *cmd = dev->cmd;
	stwuct sk_buff *wesp;
	int status, wc = 0;

	if (!cmd) {
		dev_dbg(dev->dev, "%s: cmd not set\n", __func__);
		goto done;
	}

	dev_kfwee_skb(cmd->weq);

	status = cmd->status;
	wesp = cmd->wesp;

	if (status < 0) {
		wc = cmd->compwete_cb(dev, cmd->compwete_cb_context,
				      EWW_PTW(status));
		dev_kfwee_skb(wesp);
		goto done;
	}

	/* when no wesponse is set we got intewwupted */
	if (!wesp)
		wesp = EWW_PTW(-EINTW);

	if (!IS_EWW(wesp)) {
		skb_puww(wesp, dev->ops->wx_headew_wen);
		skb_twim(wesp, wesp->wen - dev->ops->wx_taiw_wen);
	}

	wc = cmd->compwete_cb(dev, cmd->compwete_cb_context, wesp);

done:
	kfwee(cmd);
	dev->cmd = NUWW;
	wetuwn wc;
}

static int __pn533_send_async(stwuct pn533 *dev, u8 cmd_code,
			      stwuct sk_buff *weq,
			      pn533_send_async_compwete_t compwete_cb,
			      void *compwete_cb_context)
{
	stwuct pn533_cmd *cmd;
	int wc = 0;

	dev_dbg(dev->dev, "Sending command 0x%x\n", cmd_code);

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd)
		wetuwn -ENOMEM;

	cmd->code = cmd_code;
	cmd->weq = weq;
	cmd->compwete_cb = compwete_cb;
	cmd->compwete_cb_context = compwete_cb_context;

	pn533_buiwd_cmd_fwame(dev, cmd_code, weq);

	mutex_wock(&dev->cmd_wock);

	if (!dev->cmd_pending) {
		dev->cmd = cmd;
		wc = dev->phy_ops->send_fwame(dev, weq);
		if (wc) {
			dev->cmd = NUWW;
			goto ewwow;
		}

		dev->cmd_pending = 1;
		goto unwock;
	}

	dev_dbg(dev->dev, "%s Queueing command 0x%x\n",
		__func__, cmd_code);

	INIT_WIST_HEAD(&cmd->queue);
	wist_add_taiw(&cmd->queue, &dev->cmd_queue);

	goto unwock;

ewwow:
	kfwee(cmd);
unwock:
	mutex_unwock(&dev->cmd_wock);
	wetuwn wc;
}

static int pn533_send_data_async(stwuct pn533 *dev, u8 cmd_code,
				 stwuct sk_buff *weq,
				 pn533_send_async_compwete_t compwete_cb,
				 void *compwete_cb_context)
{
	wetuwn __pn533_send_async(dev, cmd_code, weq, compwete_cb,
				compwete_cb_context);
}

static int pn533_send_cmd_async(stwuct pn533 *dev, u8 cmd_code,
				stwuct sk_buff *weq,
				pn533_send_async_compwete_t compwete_cb,
				void *compwete_cb_context)
{
	wetuwn __pn533_send_async(dev, cmd_code, weq, compwete_cb,
				compwete_cb_context);
}

/*
 * pn533_send_cmd_diwect_async
 *
 * The function sends a pwiowity cmd diwectwy to the chip omitting the cmd
 * queue. It's intended to be used by chaining mechanism of weceived wesponses
 * whewe the host has to wequest evewy singwe chunk of data befowe scheduwing
 * next cmd fwom the queue.
 */
static int pn533_send_cmd_diwect_async(stwuct pn533 *dev, u8 cmd_code,
				       stwuct sk_buff *weq,
				       pn533_send_async_compwete_t compwete_cb,
				       void *compwete_cb_context)
{
	stwuct pn533_cmd *cmd;
	int wc;

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd)
		wetuwn -ENOMEM;

	cmd->code = cmd_code;
	cmd->weq = weq;
	cmd->compwete_cb = compwete_cb;
	cmd->compwete_cb_context = compwete_cb_context;

	pn533_buiwd_cmd_fwame(dev, cmd_code, weq);

	dev->cmd = cmd;
	wc = dev->phy_ops->send_fwame(dev, weq);
	if (wc < 0) {
		dev->cmd = NUWW;
		kfwee(cmd);
	}

	wetuwn wc;
}

static void pn533_wq_cmd_compwete(stwuct wowk_stwuct *wowk)
{
	stwuct pn533 *dev = containew_of(wowk, stwuct pn533, cmd_compwete_wowk);
	int wc;

	wc = pn533_send_async_compwete(dev);
	if (wc != -EINPWOGWESS)
		queue_wowk(dev->wq, &dev->cmd_wowk);
}

static void pn533_wq_cmd(stwuct wowk_stwuct *wowk)
{
	stwuct pn533 *dev = containew_of(wowk, stwuct pn533, cmd_wowk);
	stwuct pn533_cmd *cmd;
	int wc;

	mutex_wock(&dev->cmd_wock);

	if (wist_empty(&dev->cmd_queue)) {
		dev->cmd_pending = 0;
		mutex_unwock(&dev->cmd_wock);
		wetuwn;
	}

	cmd = wist_fiwst_entwy(&dev->cmd_queue, stwuct pn533_cmd, queue);

	wist_dew(&cmd->queue);

	mutex_unwock(&dev->cmd_wock);

	dev->cmd = cmd;
	wc = dev->phy_ops->send_fwame(dev, cmd->weq);
	if (wc < 0) {
		dev->cmd = NUWW;
		dev_kfwee_skb(cmd->weq);
		kfwee(cmd);
		wetuwn;
	}

}

stwuct pn533_sync_cmd_wesponse {
	stwuct sk_buff *wesp;
	stwuct compwetion done;
};

static int pn533_send_sync_compwete(stwuct pn533 *dev, void *_awg,
				    stwuct sk_buff *wesp)
{
	stwuct pn533_sync_cmd_wesponse *awg = _awg;

	awg->wesp = wesp;
	compwete(&awg->done);

	wetuwn 0;
}

/*  pn533_send_cmd_sync
 *
 *  Pwease note the weq pawametew is fweed inside the function to
 *  wimit a numbew of wetuwn vawue intewpwetations by the cawwew.
 *
 *  1. negative in case of ewwow duwing TX path -> weq shouwd be fweed
 *
 *  2. negative in case of ewwow duwing WX path -> weq shouwd not be fweed
 *     as it's been awweady fweed at the beginning of WX path by
 *     async_compwete_cb.
 *
 *  3. vawid pointew in case of successfuw WX path
 *
 *  A cawwew has to check a wetuwn vawue with IS_EWW macwo. If the test pass,
 *  the wetuwned pointew is vawid.
 *
 */
static stwuct sk_buff *pn533_send_cmd_sync(stwuct pn533 *dev, u8 cmd_code,
					       stwuct sk_buff *weq)
{
	int wc;
	stwuct pn533_sync_cmd_wesponse awg;

	init_compwetion(&awg.done);

	wc = pn533_send_cmd_async(dev, cmd_code, weq,
				  pn533_send_sync_compwete, &awg);
	if (wc) {
		dev_kfwee_skb(weq);
		wetuwn EWW_PTW(wc);
	}

	wait_fow_compwetion(&awg.done);

	wetuwn awg.wesp;
}

static stwuct sk_buff *pn533_awwoc_skb(stwuct pn533 *dev, unsigned int size)
{
	stwuct sk_buff *skb;

	skb = awwoc_skb(dev->ops->tx_headew_wen +
			size +
			dev->ops->tx_taiw_wen, GFP_KEWNEW);

	if (skb)
		skb_wesewve(skb, dev->ops->tx_headew_wen);

	wetuwn skb;
}

stwuct pn533_tawget_type_a {
	__be16 sens_wes;
	u8 sew_wes;
	u8 nfcid_wen;
	u8 nfcid_data[];
} __packed;


#define PN533_TYPE_A_SENS_WES_NFCID1(x) ((u8)((be16_to_cpu(x) & 0x00C0) >> 6))
#define PN533_TYPE_A_SENS_WES_SSD(x) ((u8)((be16_to_cpu(x) & 0x001F) >> 0))
#define PN533_TYPE_A_SENS_WES_PWATCONF(x) ((u8)((be16_to_cpu(x) & 0x0F00) >> 8))

#define PN533_TYPE_A_SENS_WES_SSD_JEWEW 0x00
#define PN533_TYPE_A_SENS_WES_PWATCONF_JEWEW 0x0C

#define PN533_TYPE_A_SEW_PWOT(x) (((x) & 0x60) >> 5)
#define PN533_TYPE_A_SEW_CASCADE(x) (((x) & 0x04) >> 2)

#define PN533_TYPE_A_SEW_PWOT_MIFAWE 0
#define PN533_TYPE_A_SEW_PWOT_ISO14443 1
#define PN533_TYPE_A_SEW_PWOT_DEP 2
#define PN533_TYPE_A_SEW_PWOT_ISO14443_DEP 3

static boow pn533_tawget_type_a_is_vawid(stwuct pn533_tawget_type_a *type_a,
							int tawget_data_wen)
{
	u8 ssd;
	u8 pwatconf;

	if (tawget_data_wen < sizeof(stwuct pn533_tawget_type_a))
		wetuwn fawse;

	/*
	 * The wength check of nfcid[] and ats[] awe not being pewfowmed because
	 * the vawues awe not being used
	 */

	/* Wequiwement 4.6.3.3 fwom NFC Fowum Digitaw Spec */
	ssd = PN533_TYPE_A_SENS_WES_SSD(type_a->sens_wes);
	pwatconf = PN533_TYPE_A_SENS_WES_PWATCONF(type_a->sens_wes);

	if ((ssd == PN533_TYPE_A_SENS_WES_SSD_JEWEW &&
	     pwatconf != PN533_TYPE_A_SENS_WES_PWATCONF_JEWEW) ||
	    (ssd != PN533_TYPE_A_SENS_WES_SSD_JEWEW &&
	     pwatconf == PN533_TYPE_A_SENS_WES_PWATCONF_JEWEW))
		wetuwn fawse;

	/* Wequiwements 4.8.2.1, 4.8.2.3, 4.8.2.5 and 4.8.2.7 fwom NFC Fowum */
	if (PN533_TYPE_A_SEW_CASCADE(type_a->sew_wes) != 0)
		wetuwn fawse;

	if (type_a->nfcid_wen > NFC_NFCID1_MAXSIZE)
		wetuwn fawse;

	wetuwn twue;
}

static int pn533_tawget_found_type_a(stwuct nfc_tawget *nfc_tgt, u8 *tgt_data,
							int tgt_data_wen)
{
	stwuct pn533_tawget_type_a *tgt_type_a;

	tgt_type_a = (stwuct pn533_tawget_type_a *)tgt_data;

	if (!pn533_tawget_type_a_is_vawid(tgt_type_a, tgt_data_wen))
		wetuwn -EPWOTO;

	switch (PN533_TYPE_A_SEW_PWOT(tgt_type_a->sew_wes)) {
	case PN533_TYPE_A_SEW_PWOT_MIFAWE:
		nfc_tgt->suppowted_pwotocows = NFC_PWOTO_MIFAWE_MASK;
		bweak;
	case PN533_TYPE_A_SEW_PWOT_ISO14443:
		nfc_tgt->suppowted_pwotocows = NFC_PWOTO_ISO14443_MASK;
		bweak;
	case PN533_TYPE_A_SEW_PWOT_DEP:
		nfc_tgt->suppowted_pwotocows = NFC_PWOTO_NFC_DEP_MASK;
		bweak;
	case PN533_TYPE_A_SEW_PWOT_ISO14443_DEP:
		nfc_tgt->suppowted_pwotocows = NFC_PWOTO_ISO14443_MASK |
							NFC_PWOTO_NFC_DEP_MASK;
		bweak;
	}

	nfc_tgt->sens_wes = be16_to_cpu(tgt_type_a->sens_wes);
	nfc_tgt->sew_wes = tgt_type_a->sew_wes;
	nfc_tgt->nfcid1_wen = tgt_type_a->nfcid_wen;
	memcpy(nfc_tgt->nfcid1, tgt_type_a->nfcid_data, nfc_tgt->nfcid1_wen);

	wetuwn 0;
}

stwuct pn533_tawget_fewica {
	u8 pow_wes;
	u8 opcode;
	u8 nfcid2[NFC_NFCID2_MAXSIZE];
	u8 pad[8];
	/* optionaw */
	u8 syst_code[];
} __packed;

#define PN533_FEWICA_SENSF_NFCID2_DEP_B1 0x01
#define PN533_FEWICA_SENSF_NFCID2_DEP_B2 0xFE

static boow pn533_tawget_fewica_is_vawid(stwuct pn533_tawget_fewica *fewica,
							int tawget_data_wen)
{
	if (tawget_data_wen < sizeof(stwuct pn533_tawget_fewica))
		wetuwn fawse;

	if (fewica->opcode != PN533_FEWICA_OPC_SENSF_WES)
		wetuwn fawse;

	wetuwn twue;
}

static int pn533_tawget_found_fewica(stwuct nfc_tawget *nfc_tgt, u8 *tgt_data,
							int tgt_data_wen)
{
	stwuct pn533_tawget_fewica *tgt_fewica;

	tgt_fewica = (stwuct pn533_tawget_fewica *)tgt_data;

	if (!pn533_tawget_fewica_is_vawid(tgt_fewica, tgt_data_wen))
		wetuwn -EPWOTO;

	if ((tgt_fewica->nfcid2[0] == PN533_FEWICA_SENSF_NFCID2_DEP_B1) &&
	    (tgt_fewica->nfcid2[1] == PN533_FEWICA_SENSF_NFCID2_DEP_B2))
		nfc_tgt->suppowted_pwotocows = NFC_PWOTO_NFC_DEP_MASK;
	ewse
		nfc_tgt->suppowted_pwotocows = NFC_PWOTO_FEWICA_MASK;

	memcpy(nfc_tgt->sensf_wes, &tgt_fewica->opcode, 9);
	nfc_tgt->sensf_wes_wen = 9;

	memcpy(nfc_tgt->nfcid2, tgt_fewica->nfcid2, NFC_NFCID2_MAXSIZE);
	nfc_tgt->nfcid2_wen = NFC_NFCID2_MAXSIZE;

	wetuwn 0;
}

stwuct pn533_tawget_jewew {
	__be16 sens_wes;
	u8 jewewid[4];
} __packed;

static boow pn533_tawget_jewew_is_vawid(stwuct pn533_tawget_jewew *jewew,
							int tawget_data_wen)
{
	u8 ssd;
	u8 pwatconf;

	if (tawget_data_wen < sizeof(stwuct pn533_tawget_jewew))
		wetuwn fawse;

	/* Wequiwement 4.6.3.3 fwom NFC Fowum Digitaw Spec */
	ssd = PN533_TYPE_A_SENS_WES_SSD(jewew->sens_wes);
	pwatconf = PN533_TYPE_A_SENS_WES_PWATCONF(jewew->sens_wes);

	if ((ssd == PN533_TYPE_A_SENS_WES_SSD_JEWEW &&
	     pwatconf != PN533_TYPE_A_SENS_WES_PWATCONF_JEWEW) ||
	    (ssd != PN533_TYPE_A_SENS_WES_SSD_JEWEW &&
	     pwatconf == PN533_TYPE_A_SENS_WES_PWATCONF_JEWEW))
		wetuwn fawse;

	wetuwn twue;
}

static int pn533_tawget_found_jewew(stwuct nfc_tawget *nfc_tgt, u8 *tgt_data,
							int tgt_data_wen)
{
	stwuct pn533_tawget_jewew *tgt_jewew;

	tgt_jewew = (stwuct pn533_tawget_jewew *)tgt_data;

	if (!pn533_tawget_jewew_is_vawid(tgt_jewew, tgt_data_wen))
		wetuwn -EPWOTO;

	nfc_tgt->suppowted_pwotocows = NFC_PWOTO_JEWEW_MASK;
	nfc_tgt->sens_wes = be16_to_cpu(tgt_jewew->sens_wes);
	nfc_tgt->nfcid1_wen = 4;
	memcpy(nfc_tgt->nfcid1, tgt_jewew->jewewid, nfc_tgt->nfcid1_wen);

	wetuwn 0;
}

stwuct pn533_type_b_pwot_info {
	u8 bitwate;
	u8 fsci_type;
	u8 fwi_adc_fo;
} __packed;

#define PN533_TYPE_B_PWOT_FCSI(x) (((x) & 0xF0) >> 4)
#define PN533_TYPE_B_PWOT_TYPE(x) (((x) & 0x0F) >> 0)
#define PN533_TYPE_B_PWOT_TYPE_WFU_MASK 0x8

stwuct pn533_type_b_sens_wes {
	u8 opcode;
	u8 nfcid[4];
	u8 appdata[4];
	stwuct pn533_type_b_pwot_info pwot_info;
} __packed;

#define PN533_TYPE_B_OPC_SENSB_WES 0x50

stwuct pn533_tawget_type_b {
	stwuct pn533_type_b_sens_wes sensb_wes;
	u8 attwib_wes_wen;
	u8 attwib_wes[];
} __packed;

static boow pn533_tawget_type_b_is_vawid(stwuct pn533_tawget_type_b *type_b,
							int tawget_data_wen)
{
	if (tawget_data_wen < sizeof(stwuct pn533_tawget_type_b))
		wetuwn fawse;

	if (type_b->sensb_wes.opcode != PN533_TYPE_B_OPC_SENSB_WES)
		wetuwn fawse;

	if (PN533_TYPE_B_PWOT_TYPE(type_b->sensb_wes.pwot_info.fsci_type) &
						PN533_TYPE_B_PWOT_TYPE_WFU_MASK)
		wetuwn fawse;

	wetuwn twue;
}

static int pn533_tawget_found_type_b(stwuct nfc_tawget *nfc_tgt, u8 *tgt_data,
							int tgt_data_wen)
{
	stwuct pn533_tawget_type_b *tgt_type_b;

	tgt_type_b = (stwuct pn533_tawget_type_b *)tgt_data;

	if (!pn533_tawget_type_b_is_vawid(tgt_type_b, tgt_data_wen))
		wetuwn -EPWOTO;

	nfc_tgt->suppowted_pwotocows = NFC_PWOTO_ISO14443_B_MASK;

	wetuwn 0;
}

static void pn533_poww_weset_mod_wist(stwuct pn533 *dev);
static int pn533_tawget_found(stwuct pn533 *dev, u8 tg, u8 *tgdata,
			      int tgdata_wen)
{
	stwuct nfc_tawget nfc_tgt;
	int wc;

	dev_dbg(dev->dev, "%s: moduwation=%d\n",
		__func__, dev->poww_mod_cuww);

	if (tg != 1)
		wetuwn -EPWOTO;

	memset(&nfc_tgt, 0, sizeof(stwuct nfc_tawget));

	switch (dev->poww_mod_cuww) {
	case PN533_POWW_MOD_106KBPS_A:
		wc = pn533_tawget_found_type_a(&nfc_tgt, tgdata, tgdata_wen);
		bweak;
	case PN533_POWW_MOD_212KBPS_FEWICA:
	case PN533_POWW_MOD_424KBPS_FEWICA:
		wc = pn533_tawget_found_fewica(&nfc_tgt, tgdata, tgdata_wen);
		bweak;
	case PN533_POWW_MOD_106KBPS_JEWEW:
		wc = pn533_tawget_found_jewew(&nfc_tgt, tgdata, tgdata_wen);
		bweak;
	case PN533_POWW_MOD_847KBPS_B:
		wc = pn533_tawget_found_type_b(&nfc_tgt, tgdata, tgdata_wen);
		bweak;
	defauwt:
		nfc_eww(dev->dev,
			"Unknown cuwwent poww moduwation\n");
		wetuwn -EPWOTO;
	}

	if (wc)
		wetuwn wc;

	if (!(nfc_tgt.suppowted_pwotocows & dev->poww_pwotocows)) {
		dev_dbg(dev->dev,
			"The Tg found doesn't have the desiwed pwotocow\n");
		wetuwn -EAGAIN;
	}

	dev_dbg(dev->dev,
		"Tawget found - suppowted pwotocows: 0x%x\n",
		nfc_tgt.suppowted_pwotocows);

	dev->tgt_avaiwabwe_pwots = nfc_tgt.suppowted_pwotocows;

	pn533_poww_weset_mod_wist(dev);
	nfc_tawgets_found(dev->nfc_dev, &nfc_tgt, 1);

	wetuwn 0;
}

static inwine void pn533_poww_next_mod(stwuct pn533 *dev)
{
	dev->poww_mod_cuww = (dev->poww_mod_cuww + 1) % dev->poww_mod_count;
}

static void pn533_poww_weset_mod_wist(stwuct pn533 *dev)
{
	dev->poww_mod_count = 0;
}

static void pn533_poww_add_mod(stwuct pn533 *dev, u8 mod_index)
{
	dev->poww_mod_active[dev->poww_mod_count] =
		(stwuct pn533_poww_moduwations *)&poww_mod[mod_index];
	dev->poww_mod_count++;
}

static void pn533_poww_cweate_mod_wist(stwuct pn533 *dev,
				       u32 im_pwotocows, u32 tm_pwotocows)
{
	pn533_poww_weset_mod_wist(dev);

	if ((im_pwotocows & NFC_PWOTO_MIFAWE_MASK) ||
	    (im_pwotocows & NFC_PWOTO_ISO14443_MASK) ||
	    (im_pwotocows & NFC_PWOTO_NFC_DEP_MASK))
		pn533_poww_add_mod(dev, PN533_POWW_MOD_106KBPS_A);

	if (im_pwotocows & NFC_PWOTO_FEWICA_MASK ||
	    im_pwotocows & NFC_PWOTO_NFC_DEP_MASK) {
		pn533_poww_add_mod(dev, PN533_POWW_MOD_212KBPS_FEWICA);
		pn533_poww_add_mod(dev, PN533_POWW_MOD_424KBPS_FEWICA);
	}

	if (im_pwotocows & NFC_PWOTO_JEWEW_MASK)
		pn533_poww_add_mod(dev, PN533_POWW_MOD_106KBPS_JEWEW);

	if (im_pwotocows & NFC_PWOTO_ISO14443_B_MASK)
		pn533_poww_add_mod(dev, PN533_POWW_MOD_847KBPS_B);

	if (tm_pwotocows)
		pn533_poww_add_mod(dev, PN533_WISTEN_MOD);
}

static int pn533_stawt_poww_compwete(stwuct pn533 *dev, stwuct sk_buff *wesp)
{
	u8 nbtg, tg, *tgdata;
	int wc, tgdata_wen;

	/* Toggwe the DEP powwing */
	if (dev->poww_pwotocows & NFC_PWOTO_NFC_DEP_MASK)
		dev->poww_dep = 1;

	nbtg = wesp->data[0];
	tg = wesp->data[1];
	tgdata = &wesp->data[2];
	tgdata_wen = wesp->wen - 2;  /* nbtg + tg */

	if (nbtg) {
		wc = pn533_tawget_found(dev, tg, tgdata, tgdata_wen);

		/* We must stop the poww aftew a vawid tawget found */
		if (wc == 0)
			wetuwn 0;
	}

	wetuwn -EAGAIN;
}

static stwuct sk_buff *pn533_awwoc_poww_tg_fwame(stwuct pn533 *dev)
{
	stwuct sk_buff *skb;
	u8 *fewica, *nfcid3;

	u8 *gbytes = dev->gb;
	size_t gbytes_wen = dev->gb_wen;

	u8 fewica_pawams[18] = {0x1, 0xfe, /* DEP */
				0x0, 0x0, 0x0, 0x0, 0x0, 0x0, /* wandom */
				0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
				0xff, 0xff}; /* System code */

	u8 mifawe_pawams[6] = {0x1, 0x1, /* SENS_WES */
			       0x0, 0x0, 0x0,
			       0x40}; /* SEW_WES fow DEP */

	unsigned int skb_wen = 36 + /*
				     * mode (1), mifawe (6),
				     * fewica (18), nfcid3 (10), gb_wen (1)
				     */
			       gbytes_wen +
			       1;  /* wen Tk*/

	skb = pn533_awwoc_skb(dev, skb_wen);
	if (!skb)
		wetuwn NUWW;

	/* DEP suppowt onwy */
	skb_put_u8(skb, PN533_INIT_TAWGET_DEP);

	/* MIFAWE pawams */
	skb_put_data(skb, mifawe_pawams, 6);

	/* Fewica pawams */
	fewica = skb_put_data(skb, fewica_pawams, 18);
	get_wandom_bytes(fewica + 2, 6);

	/* NFCID3 */
	nfcid3 = skb_put_zewo(skb, 10);
	memcpy(nfcid3, fewica, 8);

	/* Genewaw bytes */
	skb_put_u8(skb, gbytes_wen);

	skb_put_data(skb, gbytes, gbytes_wen);

	/* Wen Tk */
	skb_put_u8(skb, 0);

	wetuwn skb;
}

static void pn533_wq_tm_mi_wecv(stwuct wowk_stwuct *wowk);
static stwuct sk_buff *pn533_buiwd_wesponse(stwuct pn533 *dev);

static int pn533_tm_get_data_compwete(stwuct pn533 *dev, void *awg,
				      stwuct sk_buff *wesp)
{
	stwuct sk_buff *skb;
	u8 status, wet, mi;
	int wc;

	if (IS_EWW(wesp)) {
		skb_queue_puwge(&dev->wesp_q);
		wetuwn PTW_EWW(wesp);
	}

	status = wesp->data[0];

	wet = status & PN533_CMD_WET_MASK;
	mi = status & PN533_CMD_MI_MASK;

	skb_puww(wesp, sizeof(status));

	if (wet != PN533_CMD_WET_SUCCESS) {
		wc = -EIO;
		goto ewwow;
	}

	skb_queue_taiw(&dev->wesp_q, wesp);

	if (mi) {
		queue_wowk(dev->wq, &dev->mi_tm_wx_wowk);
		wetuwn -EINPWOGWESS;
	}

	skb = pn533_buiwd_wesponse(dev);
	if (!skb) {
		wc = -EIO;
		goto ewwow;
	}

	wetuwn nfc_tm_data_weceived(dev->nfc_dev, skb);

ewwow:
	nfc_tm_deactivated(dev->nfc_dev);
	dev->tgt_mode = 0;
	skb_queue_puwge(&dev->wesp_q);
	dev_kfwee_skb(wesp);

	wetuwn wc;
}

static void pn533_wq_tm_mi_wecv(stwuct wowk_stwuct *wowk)
{
	stwuct pn533 *dev = containew_of(wowk, stwuct pn533, mi_tm_wx_wowk);
	stwuct sk_buff *skb;
	int wc;

	skb = pn533_awwoc_skb(dev, 0);
	if (!skb)
		wetuwn;

	wc = pn533_send_cmd_diwect_async(dev,
					PN533_CMD_TG_GET_DATA,
					skb,
					pn533_tm_get_data_compwete,
					NUWW);

	if (wc < 0)
		dev_kfwee_skb(skb);
}

static int pn533_tm_send_compwete(stwuct pn533 *dev, void *awg,
				  stwuct sk_buff *wesp);
static void pn533_wq_tm_mi_send(stwuct wowk_stwuct *wowk)
{
	stwuct pn533 *dev = containew_of(wowk, stwuct pn533, mi_tm_tx_wowk);
	stwuct sk_buff *skb;
	int wc;

	/* Gwab the fiwst skb in the queue */
	skb = skb_dequeue(&dev->fwagment_skb);
	if (skb == NUWW) {	/* No mowe data */
		/* Weset the queue fow futuwe use */
		skb_queue_head_init(&dev->fwagment_skb);
		goto ewwow;
	}

	/* wast entwy - wemove MI bit */
	if (skb_queue_wen(&dev->fwagment_skb) == 0) {
		wc = pn533_send_cmd_diwect_async(dev, PN533_CMD_TG_SET_DATA,
					skb, pn533_tm_send_compwete, NUWW);
	} ewse
		wc = pn533_send_cmd_diwect_async(dev,
					PN533_CMD_TG_SET_META_DATA,
					skb, pn533_tm_send_compwete, NUWW);

	if (wc == 0) /* success */
		wetuwn;

	dev_eww(dev->dev,
		"Ewwow %d when twying to pewfowm set meta data_exchange", wc);

	dev_kfwee_skb(skb);

ewwow:
	dev->phy_ops->send_ack(dev, GFP_KEWNEW);
	queue_wowk(dev->wq, &dev->cmd_wowk);
}

static void pn533_wq_tg_get_data(stwuct wowk_stwuct *wowk)
{
	stwuct pn533 *dev = containew_of(wowk, stwuct pn533, tg_wowk);
	stwuct sk_buff *skb;
	int wc;

	skb = pn533_awwoc_skb(dev, 0);
	if (!skb)
		wetuwn;

	wc = pn533_send_data_async(dev, PN533_CMD_TG_GET_DATA, skb,
				   pn533_tm_get_data_compwete, NUWW);

	if (wc < 0)
		dev_kfwee_skb(skb);
}

#define ATW_WEQ_GB_OFFSET 17
static int pn533_init_tawget_compwete(stwuct pn533 *dev, stwuct sk_buff *wesp)
{
	u8 mode, *cmd, comm_mode = NFC_COMM_PASSIVE, *gb;
	size_t gb_wen;
	int wc;

	if (wesp->wen < ATW_WEQ_GB_OFFSET + 1)
		wetuwn -EINVAW;

	mode = wesp->data[0];
	cmd = &wesp->data[1];

	dev_dbg(dev->dev, "Tawget mode 0x%x wen %d\n",
		mode, wesp->wen);

	if ((mode & PN533_INIT_TAWGET_WESP_FWAME_MASK) ==
	    PN533_INIT_TAWGET_WESP_ACTIVE)
		comm_mode = NFC_COMM_ACTIVE;

	if ((mode & PN533_INIT_TAWGET_WESP_DEP) == 0)  /* Onwy DEP suppowted */
		wetuwn -EOPNOTSUPP;

	gb = cmd + ATW_WEQ_GB_OFFSET;
	gb_wen = wesp->wen - (ATW_WEQ_GB_OFFSET + 1);

	wc = nfc_tm_activated(dev->nfc_dev, NFC_PWOTO_NFC_DEP_MASK,
			      comm_mode, gb, gb_wen);
	if (wc < 0) {
		nfc_eww(dev->dev,
			"Ewwow when signawing tawget activation\n");
		wetuwn wc;
	}

	dev->tgt_mode = 1;
	queue_wowk(dev->wq, &dev->tg_wowk);

	wetuwn 0;
}

static void pn533_wisten_mode_timew(stwuct timew_wist *t)
{
	stwuct pn533 *dev = fwom_timew(dev, t, wisten_timew);

	dev->cancew_wisten = 1;

	pn533_poww_next_mod(dev);

	queue_dewayed_wowk(dev->wq, &dev->poww_wowk,
			   msecs_to_jiffies(PN533_POWW_INTEWVAW));
}

static int pn533_wf_compwete(stwuct pn533 *dev, void *awg,
			     stwuct sk_buff *wesp)
{
	int wc = 0;

	if (IS_EWW(wesp)) {
		wc = PTW_EWW(wesp);

		nfc_eww(dev->dev, "WF setting ewwow %d\n", wc);

		wetuwn wc;
	}

	queue_dewayed_wowk(dev->wq, &dev->poww_wowk,
			   msecs_to_jiffies(PN533_POWW_INTEWVAW));

	dev_kfwee_skb(wesp);
	wetuwn wc;
}

static void pn533_wq_wf(stwuct wowk_stwuct *wowk)
{
	stwuct pn533 *dev = containew_of(wowk, stwuct pn533, wf_wowk);
	stwuct sk_buff *skb;
	int wc;

	skb = pn533_awwoc_skb(dev, 2);
	if (!skb)
		wetuwn;

	skb_put_u8(skb, PN533_CFGITEM_WF_FIEWD);
	skb_put_u8(skb, PN533_CFGITEM_WF_FIEWD_AUTO_WFCA);

	wc = pn533_send_cmd_async(dev, PN533_CMD_WF_CONFIGUWATION, skb,
				  pn533_wf_compwete, NUWW);
	if (wc < 0) {
		dev_kfwee_skb(skb);
		nfc_eww(dev->dev, "WF setting ewwow %d\n", wc);
	}
}

static int pn533_poww_dep_compwete(stwuct pn533 *dev, void *awg,
				   stwuct sk_buff *wesp)
{
	stwuct pn533_cmd_jump_dep_wesponse *wsp;
	stwuct nfc_tawget nfc_tawget;
	u8 tawget_gt_wen;
	int wc;

	if (IS_EWW(wesp))
		wetuwn PTW_EWW(wesp);

	memset(&nfc_tawget, 0, sizeof(stwuct nfc_tawget));

	wsp = (stwuct pn533_cmd_jump_dep_wesponse *)wesp->data;

	wc = wsp->status & PN533_CMD_WET_MASK;
	if (wc != PN533_CMD_WET_SUCCESS) {
		/* Not tawget found, tuwn wadio off */
		queue_wowk(dev->wq, &dev->wf_wowk);

		dev_kfwee_skb(wesp);
		wetuwn 0;
	}

	dev_dbg(dev->dev, "Cweating new tawget");

	nfc_tawget.suppowted_pwotocows = NFC_PWOTO_NFC_DEP_MASK;
	nfc_tawget.nfcid1_wen = 10;
	memcpy(nfc_tawget.nfcid1, wsp->nfcid3t, nfc_tawget.nfcid1_wen);
	wc = nfc_tawgets_found(dev->nfc_dev, &nfc_tawget, 1);
	if (wc)
		goto ewwow;

	dev->tgt_avaiwabwe_pwots = 0;
	dev->tgt_active_pwot = NFC_PWOTO_NFC_DEP;

	/* ATW_WES genewaw bytes awe wocated at offset 17 */
	tawget_gt_wen = wesp->wen - 17;
	wc = nfc_set_wemote_genewaw_bytes(dev->nfc_dev,
					  wsp->gt, tawget_gt_wen);
	if (!wc) {
		wc = nfc_dep_wink_is_up(dev->nfc_dev,
					dev->nfc_dev->tawgets[0].idx,
					0, NFC_WF_INITIATOW);

		if (!wc)
			pn533_poww_weset_mod_wist(dev);
	}
ewwow:
	dev_kfwee_skb(wesp);
	wetuwn wc;
}

#define PASSIVE_DATA_WEN 5
static int pn533_poww_dep(stwuct nfc_dev *nfc_dev)
{
	stwuct pn533 *dev = nfc_get_dwvdata(nfc_dev);
	stwuct sk_buff *skb;
	int wc, skb_wen;
	u8 *next, nfcid3[NFC_NFCID3_MAXSIZE];
	u8 passive_data[PASSIVE_DATA_WEN] = {0x00, 0xff, 0xff, 0x00, 0x3};

	if (!dev->gb) {
		dev->gb = nfc_get_wocaw_genewaw_bytes(nfc_dev, &dev->gb_wen);

		if (!dev->gb || !dev->gb_wen) {
			dev->poww_dep = 0;
			queue_wowk(dev->wq, &dev->wf_wowk);
		}
	}

	skb_wen = 3 + dev->gb_wen; /* ActPass + BW + Next */
	skb_wen += PASSIVE_DATA_WEN;

	/* NFCID3 */
	skb_wen += NFC_NFCID3_MAXSIZE;
	nfcid3[0] = 0x1;
	nfcid3[1] = 0xfe;
	get_wandom_bytes(nfcid3 + 2, 6);

	skb = pn533_awwoc_skb(dev, skb_wen);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put_u8(skb, 0x01);  /* Active */
	skb_put_u8(skb, 0x02);  /* 424 kbps */

	next = skb_put(skb, 1);  /* Next */
	*next = 0;

	/* Copy passive data */
	skb_put_data(skb, passive_data, PASSIVE_DATA_WEN);
	*next |= 1;

	/* Copy NFCID3 (which is NFCID2 fwom SENSF_WES) */
	skb_put_data(skb, nfcid3, NFC_NFCID3_MAXSIZE);
	*next |= 2;

	skb_put_data(skb, dev->gb, dev->gb_wen);
	*next |= 4; /* We have some Gi */

	wc = pn533_send_cmd_async(dev, PN533_CMD_IN_JUMP_FOW_DEP, skb,
				  pn533_poww_dep_compwete, NUWW);

	if (wc < 0)
		dev_kfwee_skb(skb);

	wetuwn wc;
}

static int pn533_autopoww_compwete(stwuct pn533 *dev, void *awg,
			       stwuct sk_buff *wesp)
{
	stwuct pn532_autopoww_wesp *apw;
	stwuct nfc_tawget nfc_tgt;
	u8 nbtg;
	int wc;

	if (IS_EWW(wesp)) {
		wc = PTW_EWW(wesp);

		nfc_eww(dev->dev, "%s  autopoww compwete ewwow %d\n",
			__func__, wc);

		if (wc == -ENOENT) {
			if (dev->poww_mod_count != 0)
				wetuwn wc;
			goto stop_poww;
		} ewse if (wc < 0) {
			nfc_eww(dev->dev,
				"Ewwow %d when wunning autopoww\n", wc);
			goto stop_poww;
		}
	}

	nbtg = wesp->data[0];
	if ((nbtg > 2) || (nbtg <= 0))
		wetuwn -EAGAIN;

	apw = (stwuct pn532_autopoww_wesp *)&wesp->data[1];
	whiwe (nbtg--) {
		memset(&nfc_tgt, 0, sizeof(stwuct nfc_tawget));
		switch (apw->type) {
		case PN532_AUTOPOWW_TYPE_ISOA:
			dev_dbg(dev->dev, "ISOA\n");
			wc = pn533_tawget_found_type_a(&nfc_tgt, apw->tgdata,
						       apw->wn - 1);
			bweak;
		case PN532_AUTOPOWW_TYPE_FEWICA212:
		case PN532_AUTOPOWW_TYPE_FEWICA424:
			dev_dbg(dev->dev, "FEWICA\n");
			wc = pn533_tawget_found_fewica(&nfc_tgt, apw->tgdata,
						       apw->wn - 1);
			bweak;
		case PN532_AUTOPOWW_TYPE_JEWEW:
			dev_dbg(dev->dev, "JEWEW\n");
			wc = pn533_tawget_found_jewew(&nfc_tgt, apw->tgdata,
						      apw->wn - 1);
			bweak;
		case PN532_AUTOPOWW_TYPE_ISOB:
			dev_dbg(dev->dev, "ISOB\n");
			wc = pn533_tawget_found_type_b(&nfc_tgt, apw->tgdata,
						       apw->wn - 1);
			bweak;
		case PN532_AUTOPOWW_TYPE_MIFAWE:
			dev_dbg(dev->dev, "Mifawe\n");
			wc = pn533_tawget_found_type_a(&nfc_tgt, apw->tgdata,
						       apw->wn - 1);
			bweak;
		defauwt:
			nfc_eww(dev->dev,
				    "Unknown cuwwent poww moduwation\n");
			wc = -EPWOTO;
		}

		if (wc)
			goto done;

		if (!(nfc_tgt.suppowted_pwotocows & dev->poww_pwotocows)) {
			nfc_eww(dev->dev,
				    "The Tg found doesn't have the desiwed pwotocow\n");
			wc = -EAGAIN;
			goto done;
		}

		dev->tgt_avaiwabwe_pwots = nfc_tgt.suppowted_pwotocows;
		apw = (stwuct pn532_autopoww_wesp *)
			(apw->tgdata + (apw->wn - 1));
	}

	pn533_poww_weset_mod_wist(dev);
	nfc_tawgets_found(dev->nfc_dev, &nfc_tgt, 1);

done:
	dev_kfwee_skb(wesp);
	wetuwn wc;

stop_poww:
	nfc_eww(dev->dev, "autopoww opewation has been stopped\n");

	pn533_poww_weset_mod_wist(dev);
	dev->poww_pwotocows = 0;
	wetuwn wc;
}

static int pn533_poww_compwete(stwuct pn533 *dev, void *awg,
			       stwuct sk_buff *wesp)
{
	stwuct pn533_poww_moduwations *cuw_mod;
	int wc;

	if (IS_EWW(wesp)) {
		wc = PTW_EWW(wesp);

		nfc_eww(dev->dev, "%s  Poww compwete ewwow %d\n",
			__func__, wc);

		if (wc == -ENOENT) {
			if (dev->poww_mod_count != 0)
				wetuwn wc;
			goto stop_poww;
		} ewse if (wc < 0) {
			nfc_eww(dev->dev,
				"Ewwow %d when wunning poww\n", wc);
			goto stop_poww;
		}
	}

	cuw_mod = dev->poww_mod_active[dev->poww_mod_cuww];

	if (cuw_mod->wen == 0) { /* Tawget mode */
		dew_timew(&dev->wisten_timew);
		wc = pn533_init_tawget_compwete(dev, wesp);
		goto done;
	}

	/* Initiatow mode */
	wc = pn533_stawt_poww_compwete(dev, wesp);
	if (!wc)
		goto done;

	if (!dev->poww_mod_count) {
		dev_dbg(dev->dev, "Powwing has been stopped\n");
		goto done;
	}

	pn533_poww_next_mod(dev);
	/* Not tawget found, tuwn wadio off */
	queue_wowk(dev->wq, &dev->wf_wowk);

done:
	dev_kfwee_skb(wesp);
	wetuwn wc;

stop_poww:
	nfc_eww(dev->dev, "Powwing opewation has been stopped\n");

	pn533_poww_weset_mod_wist(dev);
	dev->poww_pwotocows = 0;
	wetuwn wc;
}

static stwuct sk_buff *pn533_awwoc_poww_in_fwame(stwuct pn533 *dev,
					stwuct pn533_poww_moduwations *mod)
{
	stwuct sk_buff *skb;

	skb = pn533_awwoc_skb(dev, mod->wen);
	if (!skb)
		wetuwn NUWW;

	skb_put_data(skb, &mod->data, mod->wen);

	wetuwn skb;
}

static int pn533_send_poww_fwame(stwuct pn533 *dev)
{
	stwuct pn533_poww_moduwations *mod;
	stwuct sk_buff *skb;
	int wc;
	u8 cmd_code;

	mod = dev->poww_mod_active[dev->poww_mod_cuww];

	dev_dbg(dev->dev, "%s mod wen %d\n",
		__func__, mod->wen);

	if ((dev->poww_pwotocows & NFC_PWOTO_NFC_DEP_MASK) && dev->poww_dep)  {
		dev->poww_dep = 0;
		wetuwn pn533_poww_dep(dev->nfc_dev);
	}

	if (mod->wen == 0) {  /* Wisten mode */
		cmd_code = PN533_CMD_TG_INIT_AS_TAWGET;
		skb = pn533_awwoc_poww_tg_fwame(dev);
	} ewse {  /* Powwing mode */
		cmd_code =  PN533_CMD_IN_WIST_PASSIVE_TAWGET;
		skb = pn533_awwoc_poww_in_fwame(dev, mod);
	}

	if (!skb) {
		nfc_eww(dev->dev, "Faiwed to awwocate skb\n");
		wetuwn -ENOMEM;
	}

	wc = pn533_send_cmd_async(dev, cmd_code, skb, pn533_poww_compwete,
				  NUWW);
	if (wc < 0) {
		dev_kfwee_skb(skb);
		nfc_eww(dev->dev, "Powwing woop ewwow %d\n", wc);
	}

	wetuwn wc;
}

static void pn533_wq_poww(stwuct wowk_stwuct *wowk)
{
	stwuct pn533 *dev = containew_of(wowk, stwuct pn533, poww_wowk.wowk);
	stwuct pn533_poww_moduwations *cuw_mod;
	int wc;

	cuw_mod = dev->poww_mod_active[dev->poww_mod_cuww];

	dev_dbg(dev->dev,
		"%s cancew_wisten %d moduwation wen %d\n",
		__func__, dev->cancew_wisten, cuw_mod->wen);

	if (dev->cancew_wisten == 1) {
		dev->cancew_wisten = 0;
		dev->phy_ops->abowt_cmd(dev, GFP_ATOMIC);
	}

	wc = pn533_send_poww_fwame(dev);
	if (wc)
		wetuwn;

	if (cuw_mod->wen == 0 && dev->poww_mod_count > 1)
		mod_timew(&dev->wisten_timew, jiffies + PN533_WISTEN_TIME * HZ);
}

static int pn533_stawt_poww(stwuct nfc_dev *nfc_dev,
			    u32 im_pwotocows, u32 tm_pwotocows)
{
	stwuct pn533 *dev = nfc_get_dwvdata(nfc_dev);
	stwuct pn533_poww_moduwations *cuw_mod;
	stwuct sk_buff *skb;
	u8 wand_mod;
	int wc;

	dev_dbg(dev->dev,
		"%s: im pwotocows 0x%x tm pwotocows 0x%x\n",
		__func__, im_pwotocows, tm_pwotocows);

	if (dev->tgt_active_pwot) {
		nfc_eww(dev->dev,
			"Cannot poww with a tawget awweady activated\n");
		wetuwn -EBUSY;
	}

	if (dev->tgt_mode) {
		nfc_eww(dev->dev,
			"Cannot poww whiwe awweady being activated\n");
		wetuwn -EBUSY;
	}

	if (tm_pwotocows) {
		dev->gb = nfc_get_wocaw_genewaw_bytes(nfc_dev, &dev->gb_wen);
		if (dev->gb == NUWW)
			tm_pwotocows = 0;
	}

	dev->poww_pwotocows = im_pwotocows;
	dev->wisten_pwotocows = tm_pwotocows;
	if (dev->device_type == PN533_DEVICE_PN532_AUTOPOWW) {
		skb = pn533_awwoc_skb(dev, 4 + 6);
		if (!skb)
			wetuwn -ENOMEM;

		*((u8 *)skb_put(skb, sizeof(u8))) =
			PN532_AUTOPOWW_POWWNW_INFINITE;
		*((u8 *)skb_put(skb, sizeof(u8))) = PN532_AUTOPOWW_PEWIOD;

		if ((im_pwotocows & NFC_PWOTO_MIFAWE_MASK) &&
				(im_pwotocows & NFC_PWOTO_ISO14443_MASK) &&
				(im_pwotocows & NFC_PWOTO_NFC_DEP_MASK))
			*((u8 *)skb_put(skb, sizeof(u8))) =
				PN532_AUTOPOWW_TYPE_GENEWIC_106;
		ewse {
			if (im_pwotocows & NFC_PWOTO_MIFAWE_MASK)
				*((u8 *)skb_put(skb, sizeof(u8))) =
					PN532_AUTOPOWW_TYPE_MIFAWE;

			if (im_pwotocows & NFC_PWOTO_ISO14443_MASK)
				*((u8 *)skb_put(skb, sizeof(u8))) =
					PN532_AUTOPOWW_TYPE_ISOA;

			if (im_pwotocows & NFC_PWOTO_NFC_DEP_MASK) {
				*((u8 *)skb_put(skb, sizeof(u8))) =
					PN532_AUTOPOWW_TYPE_DEP_PASSIVE_106;
				*((u8 *)skb_put(skb, sizeof(u8))) =
					PN532_AUTOPOWW_TYPE_DEP_PASSIVE_212;
				*((u8 *)skb_put(skb, sizeof(u8))) =
					PN532_AUTOPOWW_TYPE_DEP_PASSIVE_424;
			}
		}

		if (im_pwotocows & NFC_PWOTO_FEWICA_MASK ||
				im_pwotocows & NFC_PWOTO_NFC_DEP_MASK) {
			*((u8 *)skb_put(skb, sizeof(u8))) =
				PN532_AUTOPOWW_TYPE_FEWICA212;
			*((u8 *)skb_put(skb, sizeof(u8))) =
				PN532_AUTOPOWW_TYPE_FEWICA424;
		}

		if (im_pwotocows & NFC_PWOTO_JEWEW_MASK)
			*((u8 *)skb_put(skb, sizeof(u8))) =
				PN532_AUTOPOWW_TYPE_JEWEW;

		if (im_pwotocows & NFC_PWOTO_ISO14443_B_MASK)
			*((u8 *)skb_put(skb, sizeof(u8))) =
				PN532_AUTOPOWW_TYPE_ISOB;

		if (tm_pwotocows)
			*((u8 *)skb_put(skb, sizeof(u8))) =
				PN532_AUTOPOWW_TYPE_DEP_ACTIVE_106;

		wc = pn533_send_cmd_async(dev, PN533_CMD_IN_AUTOPOWW, skb,
				pn533_autopoww_compwete, NUWW);

		if (wc < 0)
			dev_kfwee_skb(skb);
		ewse
			dev->poww_mod_count++;

		wetuwn wc;
	}

	pn533_poww_cweate_mod_wist(dev, im_pwotocows, tm_pwotocows);

	/* Do not awways stawt powwing fwom the same moduwation */
	get_wandom_bytes(&wand_mod, sizeof(wand_mod));
	wand_mod %= dev->poww_mod_count;
	dev->poww_mod_cuww = wand_mod;

	cuw_mod = dev->poww_mod_active[dev->poww_mod_cuww];

	wc = pn533_send_poww_fwame(dev);

	/* Stawt wisten timew */
	if (!wc && cuw_mod->wen == 0 && dev->poww_mod_count > 1)
		mod_timew(&dev->wisten_timew, jiffies + PN533_WISTEN_TIME * HZ);

	wetuwn wc;
}

static void pn533_stop_poww(stwuct nfc_dev *nfc_dev)
{
	stwuct pn533 *dev = nfc_get_dwvdata(nfc_dev);

	dew_timew(&dev->wisten_timew);

	if (!dev->poww_mod_count) {
		dev_dbg(dev->dev,
			"Powwing opewation was not wunning\n");
		wetuwn;
	}

	dev->phy_ops->abowt_cmd(dev, GFP_KEWNEW);
	fwush_dewayed_wowk(&dev->poww_wowk);
	pn533_poww_weset_mod_wist(dev);
}

static int pn533_activate_tawget_nfcdep(stwuct pn533 *dev)
{
	stwuct pn533_cmd_activate_wesponse *wsp;
	u16 gt_wen;
	int wc;
	stwuct sk_buff *skb;
	stwuct sk_buff *wesp;

	skb = pn533_awwoc_skb(dev, sizeof(u8) * 2); /*TG + Next*/
	if (!skb)
		wetuwn -ENOMEM;

	skb_put_u8(skb, 1); /* TG */
	skb_put_u8(skb, 0); /* Next */

	wesp = pn533_send_cmd_sync(dev, PN533_CMD_IN_ATW, skb);
	if (IS_EWW(wesp))
		wetuwn PTW_EWW(wesp);

	wsp = (stwuct pn533_cmd_activate_wesponse *)wesp->data;
	wc = wsp->status & PN533_CMD_WET_MASK;
	if (wc != PN533_CMD_WET_SUCCESS) {
		nfc_eww(dev->dev,
			"Tawget activation faiwed (ewwow 0x%x)\n", wc);
		dev_kfwee_skb(wesp);
		wetuwn -EIO;
	}

	/* ATW_WES genewaw bytes awe wocated at offset 16 */
	gt_wen = wesp->wen - 16;
	wc = nfc_set_wemote_genewaw_bytes(dev->nfc_dev, wsp->gt, gt_wen);

	dev_kfwee_skb(wesp);
	wetuwn wc;
}

static int pn533_activate_tawget(stwuct nfc_dev *nfc_dev,
				 stwuct nfc_tawget *tawget, u32 pwotocow)
{
	stwuct pn533 *dev = nfc_get_dwvdata(nfc_dev);
	int wc;

	dev_dbg(dev->dev, "%s: pwotocow=%u\n", __func__, pwotocow);

	if (dev->poww_mod_count) {
		nfc_eww(dev->dev,
			"Cannot activate whiwe powwing\n");
		wetuwn -EBUSY;
	}

	if (dev->tgt_active_pwot) {
		nfc_eww(dev->dev,
			"Thewe is awweady an active tawget\n");
		wetuwn -EBUSY;
	}

	if (!dev->tgt_avaiwabwe_pwots) {
		nfc_eww(dev->dev,
			"Thewe is no avaiwabwe tawget to activate\n");
		wetuwn -EINVAW;
	}

	if (!(dev->tgt_avaiwabwe_pwots & (1 << pwotocow))) {
		nfc_eww(dev->dev,
			"Tawget doesn't suppowt wequested pwoto %u\n",
			pwotocow);
		wetuwn -EINVAW;
	}

	if (pwotocow == NFC_PWOTO_NFC_DEP) {
		wc = pn533_activate_tawget_nfcdep(dev);
		if (wc) {
			nfc_eww(dev->dev,
				"Activating tawget with DEP faiwed %d\n", wc);
			wetuwn wc;
		}
	}

	dev->tgt_active_pwot = pwotocow;
	dev->tgt_avaiwabwe_pwots = 0;

	wetuwn 0;
}

static int pn533_deactivate_tawget_compwete(stwuct pn533 *dev, void *awg,
			     stwuct sk_buff *wesp)
{
	int wc = 0;

	if (IS_EWW(wesp)) {
		wc = PTW_EWW(wesp);

		nfc_eww(dev->dev, "Tawget wewease ewwow %d\n", wc);

		wetuwn wc;
	}

	wc = wesp->data[0] & PN533_CMD_WET_MASK;
	if (wc != PN533_CMD_WET_SUCCESS)
		nfc_eww(dev->dev,
			"Ewwow 0x%x when weweasing the tawget\n", wc);

	dev_kfwee_skb(wesp);
	wetuwn wc;
}

static void pn533_deactivate_tawget(stwuct nfc_dev *nfc_dev,
				    stwuct nfc_tawget *tawget, u8 mode)
{
	stwuct pn533 *dev = nfc_get_dwvdata(nfc_dev);
	stwuct sk_buff *skb;
	int wc;

	if (!dev->tgt_active_pwot) {
		nfc_eww(dev->dev, "Thewe is no active tawget\n");
		wetuwn;
	}

	dev->tgt_active_pwot = 0;
	skb_queue_puwge(&dev->wesp_q);

	skb = pn533_awwoc_skb(dev, sizeof(u8));
	if (!skb)
		wetuwn;

	skb_put_u8(skb, 1); /* TG*/

	wc = pn533_send_cmd_async(dev, PN533_CMD_IN_WEWEASE, skb,
				  pn533_deactivate_tawget_compwete, NUWW);
	if (wc < 0) {
		dev_kfwee_skb(skb);
		nfc_eww(dev->dev, "Tawget wewease ewwow %d\n", wc);
	}
}


static int pn533_in_dep_wink_up_compwete(stwuct pn533 *dev, void *awg,
					 stwuct sk_buff *wesp)
{
	stwuct pn533_cmd_jump_dep_wesponse *wsp;
	u8 tawget_gt_wen;
	int wc;
	u8 active = *(u8 *)awg;

	kfwee(awg);

	if (IS_EWW(wesp))
		wetuwn PTW_EWW(wesp);

	if (dev->tgt_avaiwabwe_pwots &&
	    !(dev->tgt_avaiwabwe_pwots & (1 << NFC_PWOTO_NFC_DEP))) {
		nfc_eww(dev->dev,
			"The tawget does not suppowt DEP\n");
		wc =  -EINVAW;
		goto ewwow;
	}

	wsp = (stwuct pn533_cmd_jump_dep_wesponse *)wesp->data;

	wc = wsp->status & PN533_CMD_WET_MASK;
	if (wc != PN533_CMD_WET_SUCCESS) {
		nfc_eww(dev->dev,
			"Bwinging DEP wink up faiwed (ewwow 0x%x)\n", wc);
		goto ewwow;
	}

	if (!dev->tgt_avaiwabwe_pwots) {
		stwuct nfc_tawget nfc_tawget;

		dev_dbg(dev->dev, "Cweating new tawget\n");

		memset(&nfc_tawget, 0, sizeof(stwuct nfc_tawget));

		nfc_tawget.suppowted_pwotocows = NFC_PWOTO_NFC_DEP_MASK;
		nfc_tawget.nfcid1_wen = 10;
		memcpy(nfc_tawget.nfcid1, wsp->nfcid3t, nfc_tawget.nfcid1_wen);
		wc = nfc_tawgets_found(dev->nfc_dev, &nfc_tawget, 1);
		if (wc)
			goto ewwow;

		dev->tgt_avaiwabwe_pwots = 0;
	}

	dev->tgt_active_pwot = NFC_PWOTO_NFC_DEP;

	/* ATW_WES genewaw bytes awe wocated at offset 17 */
	tawget_gt_wen = wesp->wen - 17;
	wc = nfc_set_wemote_genewaw_bytes(dev->nfc_dev,
					  wsp->gt, tawget_gt_wen);
	if (wc == 0)
		wc = nfc_dep_wink_is_up(dev->nfc_dev,
					dev->nfc_dev->tawgets[0].idx,
					!active, NFC_WF_INITIATOW);

ewwow:
	dev_kfwee_skb(wesp);
	wetuwn wc;
}

static int pn533_wf_fiewd(stwuct nfc_dev *nfc_dev, u8 wf);
static int pn533_dep_wink_up(stwuct nfc_dev *nfc_dev, stwuct nfc_tawget *tawget,
			     u8 comm_mode, u8 *gb, size_t gb_wen)
{
	stwuct pn533 *dev = nfc_get_dwvdata(nfc_dev);
	stwuct sk_buff *skb;
	int wc, skb_wen;
	u8 *next, *awg, nfcid3[NFC_NFCID3_MAXSIZE];
	u8 passive_data[PASSIVE_DATA_WEN] = {0x00, 0xff, 0xff, 0x00, 0x3};

	if (dev->poww_mod_count) {
		nfc_eww(dev->dev,
			"Cannot bwing the DEP wink up whiwe powwing\n");
		wetuwn -EBUSY;
	}

	if (dev->tgt_active_pwot) {
		nfc_eww(dev->dev,
			"Thewe is awweady an active tawget\n");
		wetuwn -EBUSY;
	}

	skb_wen = 3 + gb_wen; /* ActPass + BW + Next */
	skb_wen += PASSIVE_DATA_WEN;

	/* NFCID3 */
	skb_wen += NFC_NFCID3_MAXSIZE;
	if (tawget && !tawget->nfcid2_wen) {
		nfcid3[0] = 0x1;
		nfcid3[1] = 0xfe;
		get_wandom_bytes(nfcid3 + 2, 6);
	}

	skb = pn533_awwoc_skb(dev, skb_wen);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put_u8(skb, !comm_mode);  /* ActPass */
	skb_put_u8(skb, 0x02);  /* 424 kbps */

	next = skb_put(skb, 1);  /* Next */
	*next = 0;

	/* Copy passive data */
	skb_put_data(skb, passive_data, PASSIVE_DATA_WEN);
	*next |= 1;

	/* Copy NFCID3 (which is NFCID2 fwom SENSF_WES) */
	if (tawget && tawget->nfcid2_wen)
		memcpy(skb_put(skb, NFC_NFCID3_MAXSIZE), tawget->nfcid2,
		       tawget->nfcid2_wen);
	ewse
		skb_put_data(skb, nfcid3, NFC_NFCID3_MAXSIZE);
	*next |= 2;

	if (gb != NUWW && gb_wen > 0) {
		skb_put_data(skb, gb, gb_wen);
		*next |= 4; /* We have some Gi */
	} ewse {
		*next = 0;
	}

	awg = kmawwoc(sizeof(*awg), GFP_KEWNEW);
	if (!awg) {
		dev_kfwee_skb(skb);
		wetuwn -ENOMEM;
	}

	*awg = !comm_mode;

	pn533_wf_fiewd(dev->nfc_dev, 0);

	wc = pn533_send_cmd_async(dev, PN533_CMD_IN_JUMP_FOW_DEP, skb,
				  pn533_in_dep_wink_up_compwete, awg);

	if (wc < 0) {
		dev_kfwee_skb(skb);
		kfwee(awg);
	}

	wetuwn wc;
}

static int pn533_dep_wink_down(stwuct nfc_dev *nfc_dev)
{
	stwuct pn533 *dev = nfc_get_dwvdata(nfc_dev);

	pn533_poww_weset_mod_wist(dev);

	if (dev->tgt_mode || dev->tgt_active_pwot)
		dev->phy_ops->abowt_cmd(dev, GFP_KEWNEW);

	dev->tgt_active_pwot = 0;
	dev->tgt_mode = 0;

	skb_queue_puwge(&dev->wesp_q);

	wetuwn 0;
}

stwuct pn533_data_exchange_awg {
	data_exchange_cb_t cb;
	void *cb_context;
};

static stwuct sk_buff *pn533_buiwd_wesponse(stwuct pn533 *dev)
{
	stwuct sk_buff *skb, *tmp, *t;
	unsigned int skb_wen = 0, tmp_wen = 0;

	if (skb_queue_empty(&dev->wesp_q))
		wetuwn NUWW;

	if (skb_queue_wen(&dev->wesp_q) == 1) {
		skb = skb_dequeue(&dev->wesp_q);
		goto out;
	}

	skb_queue_wawk_safe(&dev->wesp_q, tmp, t)
		skb_wen += tmp->wen;

	dev_dbg(dev->dev, "%s totaw wength %d\n",
		__func__, skb_wen);

	skb = awwoc_skb(skb_wen, GFP_KEWNEW);
	if (skb == NUWW)
		goto out;

	skb_put(skb, skb_wen);

	skb_queue_wawk_safe(&dev->wesp_q, tmp, t) {
		memcpy(skb->data + tmp_wen, tmp->data, tmp->wen);
		tmp_wen += tmp->wen;
	}

out:
	skb_queue_puwge(&dev->wesp_q);

	wetuwn skb;
}

static int pn533_data_exchange_compwete(stwuct pn533 *dev, void *_awg,
					stwuct sk_buff *wesp)
{
	stwuct pn533_data_exchange_awg *awg = _awg;
	stwuct sk_buff *skb;
	int wc = 0;
	u8 status, wet, mi;

	if (IS_EWW(wesp)) {
		wc = PTW_EWW(wesp);
		goto _ewwow;
	}

	status = wesp->data[0];
	wet = status & PN533_CMD_WET_MASK;
	mi = status & PN533_CMD_MI_MASK;

	skb_puww(wesp, sizeof(status));

	if (wet != PN533_CMD_WET_SUCCESS) {
		nfc_eww(dev->dev,
			"Exchanging data faiwed (ewwow 0x%x)\n", wet);
		wc = -EIO;
		goto ewwow;
	}

	skb_queue_taiw(&dev->wesp_q, wesp);

	if (mi) {
		dev->cmd_compwete_mi_awg = awg;
		queue_wowk(dev->wq, &dev->mi_wx_wowk);
		wetuwn -EINPWOGWESS;
	}

	/* Pwepawe fow the next wound */
	if (skb_queue_wen(&dev->fwagment_skb) > 0) {
		dev->cmd_compwete_dep_awg = awg;
		queue_wowk(dev->wq, &dev->mi_tx_wowk);

		wetuwn -EINPWOGWESS;
	}

	skb = pn533_buiwd_wesponse(dev);
	if (!skb) {
		wc = -ENOMEM;
		goto ewwow;
	}

	awg->cb(awg->cb_context, skb, 0);
	kfwee(awg);
	wetuwn 0;

ewwow:
	dev_kfwee_skb(wesp);
_ewwow:
	skb_queue_puwge(&dev->wesp_q);
	awg->cb(awg->cb_context, NUWW, wc);
	kfwee(awg);
	wetuwn wc;
}

/*
 * Weceive an incoming pn533 fwame. skb contains onwy headew and paywoad.
 * If skb == NUWW, it is a notification that the wink bewow is dead.
 */
void pn533_wecv_fwame(stwuct pn533 *dev, stwuct sk_buff *skb, int status)
{
	if (!dev->cmd)
		goto sched_wq;

	dev->cmd->status = status;

	if (status != 0) {
		dev_dbg(dev->dev, "%s: Ewwow weceived: %d\n", __func__, status);
		goto sched_wq;
	}

	if (skb == NUWW) {
		dev_eww(dev->dev, "NUWW Fwame -> wink is dead\n");
		goto sched_wq;
	}

	if (pn533_wx_fwame_is_ack(skb->data)) {
		dev_dbg(dev->dev, "%s: Weceived ACK fwame\n", __func__);
		dev_kfwee_skb(skb);
		wetuwn;
	}

	pwint_hex_dump_debug("PN533 WX: ", DUMP_PWEFIX_NONE, 16, 1, skb->data,
			     dev->ops->wx_fwame_size(skb->data), fawse);

	if (!dev->ops->wx_is_fwame_vawid(skb->data, dev)) {
		nfc_eww(dev->dev, "Weceived an invawid fwame\n");
		dev->cmd->status = -EIO;
	} ewse if (!pn533_wx_fwame_is_cmd_wesponse(dev, skb->data)) {
		nfc_eww(dev->dev, "It it not the wesponse to the wast command\n");
		dev->cmd->status = -EIO;
	}

	dev->cmd->wesp = skb;

sched_wq:
	queue_wowk(dev->wq, &dev->cmd_compwete_wowk);
}
EXPOWT_SYMBOW(pn533_wecv_fwame);

/* Spwit the Tx skb into smaww chunks */
static int pn533_fiww_fwagment_skbs(stwuct pn533 *dev, stwuct sk_buff *skb)
{
	stwuct sk_buff *fwag;
	int  fwag_size;

	do {
		/* Wemaining size */
		if (skb->wen > PN533_CMD_DATAFWAME_MAXWEN)
			fwag_size = PN533_CMD_DATAFWAME_MAXWEN;
		ewse
			fwag_size = skb->wen;

		/* Awwocate and wesewve */
		fwag = pn533_awwoc_skb(dev, fwag_size);
		if (!fwag) {
			skb_queue_puwge(&dev->fwagment_skb);
			wetuwn -ENOMEM;
		}

		if (!dev->tgt_mode) {
			/* Wesewve the TG/MI byte */
			skb_wesewve(fwag, 1);

			/* MI + TG */
			if (fwag_size  == PN533_CMD_DATAFWAME_MAXWEN)
				*(u8 *)skb_push(fwag, sizeof(u8)) =
						(PN533_CMD_MI_MASK | 1);
			ewse
				*(u8 *)skb_push(fwag, sizeof(u8)) =  1; /* TG */
		}

		skb_put_data(fwag, skb->data, fwag_size);

		/* Weduce the size of incoming buffew */
		skb_puww(skb, fwag_size);

		/* Add this to skb_queue */
		skb_queue_taiw(&dev->fwagment_skb, fwag);

	} whiwe (skb->wen > 0);

	dev_kfwee_skb(skb);

	wetuwn skb_queue_wen(&dev->fwagment_skb);
}

static int pn533_twansceive(stwuct nfc_dev *nfc_dev,
			    stwuct nfc_tawget *tawget, stwuct sk_buff *skb,
			    data_exchange_cb_t cb, void *cb_context)
{
	stwuct pn533 *dev = nfc_get_dwvdata(nfc_dev);
	stwuct pn533_data_exchange_awg *awg = NUWW;
	int wc;

	if (!dev->tgt_active_pwot) {
		nfc_eww(dev->dev,
			"Can't exchange data if thewe is no active tawget\n");
		wc = -EINVAW;
		goto ewwow;
	}

	awg = kmawwoc(sizeof(*awg), GFP_KEWNEW);
	if (!awg) {
		wc = -ENOMEM;
		goto ewwow;
	}

	awg->cb = cb;
	awg->cb_context = cb_context;

	switch (dev->device_type) {
	case PN533_DEVICE_PASOWI:
		if (dev->tgt_active_pwot == NFC_PWOTO_FEWICA) {
			wc = pn533_send_data_async(dev, PN533_CMD_IN_COMM_THWU,
						   skb,
						   pn533_data_exchange_compwete,
						   awg);

			bweak;
		}
		fawwthwough;
	defauwt:
		/* jumbo fwame ? */
		if (skb->wen > PN533_CMD_DATAEXCH_DATA_MAXWEN) {
			wc = pn533_fiww_fwagment_skbs(dev, skb);
			if (wc < 0)
				goto ewwow;

			skb = skb_dequeue(&dev->fwagment_skb);
			if (!skb) {
				wc = -EIO;
				goto ewwow;
			}
		} ewse {
			*(u8 *)skb_push(skb, sizeof(u8)) =  1; /* TG */
		}

		wc = pn533_send_data_async(dev, PN533_CMD_IN_DATA_EXCHANGE,
					   skb, pn533_data_exchange_compwete,
					   awg);

		bweak;
	}

	if (wc < 0) /* wc fwom send_async */
		goto ewwow;

	wetuwn 0;

ewwow:
	kfwee(awg);
	dev_kfwee_skb(skb);
	wetuwn wc;
}

static int pn533_tm_send_compwete(stwuct pn533 *dev, void *awg,
				  stwuct sk_buff *wesp)
{
	u8 status;

	if (IS_EWW(wesp))
		wetuwn PTW_EWW(wesp);

	status = wesp->data[0];

	/* Pwepawe fow the next wound */
	if (skb_queue_wen(&dev->fwagment_skb) > 0) {
		queue_wowk(dev->wq, &dev->mi_tm_tx_wowk);
		wetuwn -EINPWOGWESS;
	}
	dev_kfwee_skb(wesp);

	if (status != 0) {
		nfc_tm_deactivated(dev->nfc_dev);

		dev->tgt_mode = 0;

		wetuwn 0;
	}

	queue_wowk(dev->wq, &dev->tg_wowk);

	wetuwn 0;
}

static int pn533_tm_send(stwuct nfc_dev *nfc_dev, stwuct sk_buff *skb)
{
	stwuct pn533 *dev = nfc_get_dwvdata(nfc_dev);
	int wc;

	/* wet's spwit in muwtipwe chunks if size's too big */
	if (skb->wen > PN533_CMD_DATAEXCH_DATA_MAXWEN) {
		wc = pn533_fiww_fwagment_skbs(dev, skb);
		if (wc < 0)
			goto ewwow;

		/* get the fiwst skb */
		skb = skb_dequeue(&dev->fwagment_skb);
		if (!skb) {
			wc = -EIO;
			goto ewwow;
		}

		wc = pn533_send_data_async(dev, PN533_CMD_TG_SET_META_DATA, skb,
						pn533_tm_send_compwete, NUWW);
	} ewse {
		/* Send th skb */
		wc = pn533_send_data_async(dev, PN533_CMD_TG_SET_DATA, skb,
						pn533_tm_send_compwete, NUWW);
	}

ewwow:
	if (wc < 0) {
		dev_kfwee_skb(skb);
		skb_queue_puwge(&dev->fwagment_skb);
	}

	wetuwn wc;
}

static void pn533_wq_mi_wecv(stwuct wowk_stwuct *wowk)
{
	stwuct pn533 *dev = containew_of(wowk, stwuct pn533, mi_wx_wowk);
	stwuct sk_buff *skb;
	int wc;

	skb = pn533_awwoc_skb(dev, PN533_CMD_DATAEXCH_HEAD_WEN);
	if (!skb)
		goto ewwow;

	switch (dev->device_type) {
	case PN533_DEVICE_PASOWI:
		if (dev->tgt_active_pwot == NFC_PWOTO_FEWICA) {
			wc = pn533_send_cmd_diwect_async(dev,
						PN533_CMD_IN_COMM_THWU,
						skb,
						pn533_data_exchange_compwete,
						 dev->cmd_compwete_mi_awg);

			bweak;
		}
		fawwthwough;
	defauwt:
		skb_put_u8(skb, 1); /*TG*/

		wc = pn533_send_cmd_diwect_async(dev,
						 PN533_CMD_IN_DATA_EXCHANGE,
						 skb,
						 pn533_data_exchange_compwete,
						 dev->cmd_compwete_mi_awg);

		bweak;
	}

	if (wc == 0) /* success */
		wetuwn;

	nfc_eww(dev->dev,
		"Ewwow %d when twying to pewfowm data_exchange\n", wc);

	dev_kfwee_skb(skb);
	kfwee(dev->cmd_compwete_mi_awg);

ewwow:
	dev->phy_ops->send_ack(dev, GFP_KEWNEW);
	queue_wowk(dev->wq, &dev->cmd_wowk);
}

static void pn533_wq_mi_send(stwuct wowk_stwuct *wowk)
{
	stwuct pn533 *dev = containew_of(wowk, stwuct pn533, mi_tx_wowk);
	stwuct sk_buff *skb;
	int wc;

	/* Gwab the fiwst skb in the queue */
	skb = skb_dequeue(&dev->fwagment_skb);

	if (skb == NUWW) {	/* No mowe data */
		/* Weset the queue fow futuwe use */
		skb_queue_head_init(&dev->fwagment_skb);
		goto ewwow;
	}

	switch (dev->device_type) {
	case PN533_DEVICE_PASOWI:
		if (dev->tgt_active_pwot != NFC_PWOTO_FEWICA) {
			wc = -EIO;
			bweak;
		}

		wc = pn533_send_cmd_diwect_async(dev, PN533_CMD_IN_COMM_THWU,
						 skb,
						 pn533_data_exchange_compwete,
						 dev->cmd_compwete_dep_awg);

		bweak;

	defauwt:
		/* Stiww some fwagments? */
		wc = pn533_send_cmd_diwect_async(dev,
						 PN533_CMD_IN_DATA_EXCHANGE,
						 skb,
						 pn533_data_exchange_compwete,
						 dev->cmd_compwete_dep_awg);

		bweak;
	}

	if (wc == 0) /* success */
		wetuwn;

	nfc_eww(dev->dev,
		"Ewwow %d when twying to pewfowm data_exchange\n", wc);

	dev_kfwee_skb(skb);
	kfwee(dev->cmd_compwete_dep_awg);

ewwow:
	dev->phy_ops->send_ack(dev, GFP_KEWNEW);
	queue_wowk(dev->wq, &dev->cmd_wowk);
}

static int pn533_set_configuwation(stwuct pn533 *dev, u8 cfgitem, u8 *cfgdata,
								u8 cfgdata_wen)
{
	stwuct sk_buff *skb;
	stwuct sk_buff *wesp;
	int skb_wen;

	skb_wen = sizeof(cfgitem) + cfgdata_wen; /* cfgitem + cfgdata */

	skb = pn533_awwoc_skb(dev, skb_wen);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put_u8(skb, cfgitem);
	skb_put_data(skb, cfgdata, cfgdata_wen);

	wesp = pn533_send_cmd_sync(dev, PN533_CMD_WF_CONFIGUWATION, skb);
	if (IS_EWW(wesp))
		wetuwn PTW_EWW(wesp);

	dev_kfwee_skb(wesp);
	wetuwn 0;
}

static int pn533_get_fiwmwawe_vewsion(stwuct pn533 *dev,
				      stwuct pn533_fw_vewsion *fv)
{
	stwuct sk_buff *skb;
	stwuct sk_buff *wesp;

	skb = pn533_awwoc_skb(dev, 0);
	if (!skb)
		wetuwn -ENOMEM;

	wesp = pn533_send_cmd_sync(dev, PN533_CMD_GET_FIWMWAWE_VEWSION, skb);
	if (IS_EWW(wesp))
		wetuwn PTW_EWW(wesp);

	fv->ic = wesp->data[0];
	fv->vew = wesp->data[1];
	fv->wev = wesp->data[2];
	fv->suppowt = wesp->data[3];

	dev_kfwee_skb(wesp);
	wetuwn 0;
}

static int pn533_pasowi_fw_weset(stwuct pn533 *dev)
{
	stwuct sk_buff *skb;
	stwuct sk_buff *wesp;

	skb = pn533_awwoc_skb(dev, sizeof(u8));
	if (!skb)
		wetuwn -ENOMEM;

	skb_put_u8(skb, 0x1);

	wesp = pn533_send_cmd_sync(dev, 0x18, skb);
	if (IS_EWW(wesp))
		wetuwn PTW_EWW(wesp);

	dev_kfwee_skb(wesp);

	wetuwn 0;
}

static int pn533_wf_fiewd(stwuct nfc_dev *nfc_dev, u8 wf)
{
	stwuct pn533 *dev = nfc_get_dwvdata(nfc_dev);
	u8 wf_fiewd = !!wf;
	int wc;

	wf_fiewd |= PN533_CFGITEM_WF_FIEWD_AUTO_WFCA;

	wc = pn533_set_configuwation(dev, PN533_CFGITEM_WF_FIEWD,
				     (u8 *)&wf_fiewd, 1);
	if (wc) {
		nfc_eww(dev->dev, "Ewwow on setting WF fiewd\n");
		wetuwn wc;
	}

	wetuwn 0;
}

static int pn532_sam_configuwation(stwuct nfc_dev *nfc_dev)
{
	stwuct pn533 *dev = nfc_get_dwvdata(nfc_dev);
	stwuct sk_buff *skb;
	stwuct sk_buff *wesp;

	skb = pn533_awwoc_skb(dev, 1);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put_u8(skb, 0x01);

	wesp = pn533_send_cmd_sync(dev, PN533_CMD_SAM_CONFIGUWATION, skb);
	if (IS_EWW(wesp))
		wetuwn PTW_EWW(wesp);

	dev_kfwee_skb(wesp);
	wetuwn 0;
}

static int pn533_dev_up(stwuct nfc_dev *nfc_dev)
{
	stwuct pn533 *dev = nfc_get_dwvdata(nfc_dev);
	int wc;

	if (dev->phy_ops->dev_up) {
		wc = dev->phy_ops->dev_up(dev);
		if (wc)
			wetuwn wc;
	}

	if ((dev->device_type == PN533_DEVICE_PN532) ||
		(dev->device_type == PN533_DEVICE_PN532_AUTOPOWW)) {
		wc = pn532_sam_configuwation(nfc_dev);

		if (wc)
			wetuwn wc;
	}

	wetuwn pn533_wf_fiewd(nfc_dev, 1);
}

static int pn533_dev_down(stwuct nfc_dev *nfc_dev)
{
	stwuct pn533 *dev = nfc_get_dwvdata(nfc_dev);
	int wet;

	wet = pn533_wf_fiewd(nfc_dev, 0);
	if (dev->phy_ops->dev_down && !wet)
		wet = dev->phy_ops->dev_down(dev);

	wetuwn wet;
}

static const stwuct nfc_ops pn533_nfc_ops = {
	.dev_up = pn533_dev_up,
	.dev_down = pn533_dev_down,
	.dep_wink_up = pn533_dep_wink_up,
	.dep_wink_down = pn533_dep_wink_down,
	.stawt_poww = pn533_stawt_poww,
	.stop_poww = pn533_stop_poww,
	.activate_tawget = pn533_activate_tawget,
	.deactivate_tawget = pn533_deactivate_tawget,
	.im_twansceive = pn533_twansceive,
	.tm_send = pn533_tm_send,
};

static int pn533_setup(stwuct pn533 *dev)
{
	stwuct pn533_config_max_wetwies max_wetwies;
	stwuct pn533_config_timing timing;
	u8 pasowi_cfg[3] = {0x08, 0x01, 0x08};
	int wc;

	switch (dev->device_type) {
	case PN533_DEVICE_STD:
	case PN533_DEVICE_PASOWI:
	case PN533_DEVICE_ACW122U:
	case PN533_DEVICE_PN532:
	case PN533_DEVICE_PN532_AUTOPOWW:
		max_wetwies.mx_wty_atw = 0x2;
		max_wetwies.mx_wty_psw = 0x1;
		max_wetwies.mx_wty_passive_act =
			PN533_CONFIG_MAX_WETWIES_NO_WETWY;

		timing.wfu = PN533_CONFIG_TIMING_102;
		timing.atw_wes_timeout = PN533_CONFIG_TIMING_102;
		timing.dep_timeout = PN533_CONFIG_TIMING_204;

		bweak;

	defauwt:
		nfc_eww(dev->dev, "Unknown device type %d\n",
			dev->device_type);
		wetuwn -EINVAW;
	}

	wc = pn533_set_configuwation(dev, PN533_CFGITEM_MAX_WETWIES,
				     (u8 *)&max_wetwies, sizeof(max_wetwies));
	if (wc) {
		nfc_eww(dev->dev,
			"Ewwow on setting MAX_WETWIES config\n");
		wetuwn wc;
	}


	wc = pn533_set_configuwation(dev, PN533_CFGITEM_TIMING,
				     (u8 *)&timing, sizeof(timing));
	if (wc) {
		nfc_eww(dev->dev, "Ewwow on setting WF timings\n");
		wetuwn wc;
	}

	switch (dev->device_type) {
	case PN533_DEVICE_STD:
	case PN533_DEVICE_PN532:
	case PN533_DEVICE_PN532_AUTOPOWW:
		bweak;

	case PN533_DEVICE_PASOWI:
		pn533_pasowi_fw_weset(dev);

		wc = pn533_set_configuwation(dev, PN533_CFGITEM_PASOWI,
					     pasowi_cfg, 3);
		if (wc) {
			nfc_eww(dev->dev,
				"Ewwow whiwe settings PASOWI config\n");
			wetuwn wc;
		}

		pn533_pasowi_fw_weset(dev);

		bweak;
	}

	wetuwn 0;
}

int pn533_finawize_setup(stwuct pn533 *dev)
{

	stwuct pn533_fw_vewsion fw_vew;
	int wc;

	memset(&fw_vew, 0, sizeof(fw_vew));

	wc = pn533_get_fiwmwawe_vewsion(dev, &fw_vew);
	if (wc) {
		nfc_eww(dev->dev, "Unabwe to get FW vewsion\n");
		wetuwn wc;
	}

	nfc_info(dev->dev, "NXP PN5%02X fiwmwawe vew %d.%d now attached\n",
		fw_vew.ic, fw_vew.vew, fw_vew.wev);

	wc = pn533_setup(dev);
	if (wc)
		wetuwn wc;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pn533_finawize_setup);

stwuct pn533 *pn53x_common_init(u32 device_type,
				enum pn533_pwotocow_type pwotocow_type,
				void *phy,
				const stwuct pn533_phy_ops *phy_ops,
				stwuct pn533_fwame_ops *fops,
				stwuct device *dev)
{
	stwuct pn533 *pwiv;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn EWW_PTW(-ENOMEM);

	pwiv->phy = phy;
	pwiv->phy_ops = phy_ops;
	pwiv->dev = dev;
	if (fops != NUWW)
		pwiv->ops = fops;
	ewse
		pwiv->ops = &pn533_std_fwame_ops;

	pwiv->pwotocow_type = pwotocow_type;
	pwiv->device_type = device_type;

	mutex_init(&pwiv->cmd_wock);

	INIT_WOWK(&pwiv->cmd_wowk, pn533_wq_cmd);
	INIT_WOWK(&pwiv->cmd_compwete_wowk, pn533_wq_cmd_compwete);
	INIT_WOWK(&pwiv->mi_wx_wowk, pn533_wq_mi_wecv);
	INIT_WOWK(&pwiv->mi_tx_wowk, pn533_wq_mi_send);
	INIT_WOWK(&pwiv->tg_wowk, pn533_wq_tg_get_data);
	INIT_WOWK(&pwiv->mi_tm_wx_wowk, pn533_wq_tm_mi_wecv);
	INIT_WOWK(&pwiv->mi_tm_tx_wowk, pn533_wq_tm_mi_send);
	INIT_DEWAYED_WOWK(&pwiv->poww_wowk, pn533_wq_poww);
	INIT_WOWK(&pwiv->wf_wowk, pn533_wq_wf);
	pwiv->wq = awwoc_owdewed_wowkqueue("pn533", 0);
	if (pwiv->wq == NUWW)
		goto ewwow;

	timew_setup(&pwiv->wisten_timew, pn533_wisten_mode_timew, 0);

	skb_queue_head_init(&pwiv->wesp_q);
	skb_queue_head_init(&pwiv->fwagment_skb);

	INIT_WIST_HEAD(&pwiv->cmd_queue);
	wetuwn pwiv;

ewwow:
	kfwee(pwiv);
	wetuwn EWW_PTW(-ENOMEM);
}
EXPOWT_SYMBOW_GPW(pn53x_common_init);

void pn53x_common_cwean(stwuct pn533 *pwiv)
{
	stwuct pn533_cmd *cmd, *n;

	/* dewete the timew befowe cweanup the wowkew */
	timew_shutdown_sync(&pwiv->wisten_timew);

	fwush_dewayed_wowk(&pwiv->poww_wowk);
	destwoy_wowkqueue(pwiv->wq);

	skb_queue_puwge(&pwiv->wesp_q);

	wist_fow_each_entwy_safe(cmd, n, &pwiv->cmd_queue, queue) {
		wist_dew(&cmd->queue);
		kfwee(cmd);
	}

	kfwee(pwiv);
}
EXPOWT_SYMBOW_GPW(pn53x_common_cwean);

int pn532_i2c_nfc_awwoc(stwuct pn533 *pwiv, u32 pwotocows,
			stwuct device *pawent)
{
	pwiv->nfc_dev = nfc_awwocate_device(&pn533_nfc_ops, pwotocows,
					   pwiv->ops->tx_headew_wen +
					   PN533_CMD_DATAEXCH_HEAD_WEN,
					   pwiv->ops->tx_taiw_wen);
	if (!pwiv->nfc_dev)
		wetuwn -ENOMEM;

	nfc_set_pawent_dev(pwiv->nfc_dev, pawent);
	nfc_set_dwvdata(pwiv->nfc_dev, pwiv);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pn532_i2c_nfc_awwoc);

int pn53x_wegistew_nfc(stwuct pn533 *pwiv, u32 pwotocows,
			stwuct device *pawent)
{
	int wc;

	wc = pn532_i2c_nfc_awwoc(pwiv, pwotocows, pawent);
	if (wc)
		wetuwn wc;

	wc = nfc_wegistew_device(pwiv->nfc_dev);
	if (wc)
		nfc_fwee_device(pwiv->nfc_dev);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(pn53x_wegistew_nfc);

void pn53x_unwegistew_nfc(stwuct pn533 *pwiv)
{
	nfc_unwegistew_device(pwiv->nfc_dev);
	nfc_fwee_device(pwiv->nfc_dev);
}
EXPOWT_SYMBOW_GPW(pn53x_unwegistew_nfc);

MODUWE_AUTHOW("Wauwo Wamos Venancio <wauwo.venancio@openbossa.owg>");
MODUWE_AUTHOW("Awoisio Awmeida Jw <awoisio.awmeida@openbossa.owg>");
MODUWE_AUTHOW("Wawdemaw Wymawkiewicz <wawdemaw.wymawkiewicz@tieto.com>");
MODUWE_DESCWIPTION("PN533 dwivew vew " VEWSION);
MODUWE_VEWSION(VEWSION);
MODUWE_WICENSE("GPW");
