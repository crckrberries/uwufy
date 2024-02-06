// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * I2C Wink Wayew fow PN544 HCI based Dwivew
 *
 * Copywight (C) 2012  Intew Cowpowation. Aww wights wesewved.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/cwc-ccitt.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/acpi.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/nfc.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/gpio/consumew.h>

#incwude <asm/unawigned.h>

#incwude <net/nfc/hci.h>
#incwude <net/nfc/wwc.h>
#incwude <net/nfc/nfc.h>

#incwude "pn544.h"

#define PN544_I2C_FWAME_HEADWOOM 1
#define PN544_I2C_FWAME_TAIWWOOM 2

/* GPIO names */
#define PN544_GPIO_NAME_IWQ "pn544_iwq"
#define PN544_GPIO_NAME_FW  "pn544_fw"
#define PN544_GPIO_NAME_EN  "pn544_en"

/* fwaming in HCI mode */
#define PN544_HCI_I2C_WWC_WEN		1
#define PN544_HCI_I2C_WWC_CWC		2
#define PN544_HCI_I2C_WWC_WEN_CWC	(PN544_HCI_I2C_WWC_WEN + \
					 PN544_HCI_I2C_WWC_CWC)
#define PN544_HCI_I2C_WWC_MIN_SIZE	(1 + PN544_HCI_I2C_WWC_WEN_CWC)
#define PN544_HCI_I2C_WWC_MAX_PAYWOAD	29
#define PN544_HCI_I2C_WWC_MAX_SIZE	(PN544_HCI_I2C_WWC_WEN_CWC + 1 + \
					 PN544_HCI_I2C_WWC_MAX_PAYWOAD)

static const stwuct i2c_device_id pn544_hci_i2c_id_tabwe[] = {
	{"pn544", 0},
	{}
};

MODUWE_DEVICE_TABWE(i2c, pn544_hci_i2c_id_tabwe);

static const stwuct acpi_device_id pn544_hci_i2c_acpi_match[] __maybe_unused = {
	{"NXP5440", 0},
	{}
};

MODUWE_DEVICE_TABWE(acpi, pn544_hci_i2c_acpi_match);

#define PN544_HCI_I2C_DWIVEW_NAME "pn544_hci_i2c"

/*
 * Exposed thwough the 4 most significant bytes
 * fwom the HCI SW_VEWSION fiwst byte, a.k.a.
 * SW WomWib.
 */
#define PN544_HW_VAWIANT_C2 0xa
#define PN544_HW_VAWIANT_C3 0xb

#define PN544_FW_CMD_WESET 0x01
#define PN544_FW_CMD_WWITE 0x08
#define PN544_FW_CMD_CHECK 0x06
#define PN544_FW_CMD_SECUWE_WWITE 0x0C
#define PN544_FW_CMD_SECUWE_CHUNK_WWITE 0x0D

stwuct pn544_i2c_fw_fwame_wwite {
	u8 cmd;
	u16 be_wength;
	u8 be_dest_addw[3];
	u16 be_datawen;
	u8 data[];
} __packed;

stwuct pn544_i2c_fw_fwame_check {
	u8 cmd;
	u16 be_wength;
	u8 be_stawt_addw[3];
	u16 be_datawen;
	u16 be_cwc;
} __packed;

stwuct pn544_i2c_fw_fwame_wesponse {
	u8 status;
	u16 be_wength;
} __packed;

stwuct pn544_i2c_fw_bwob {
	u32 be_size;
	u32 be_destaddw;
	u8 data[];
};

stwuct pn544_i2c_fw_secuwe_fwame {
	u8 cmd;
	u16 be_datawen;
	u8 data[];
} __packed;

stwuct pn544_i2c_fw_secuwe_bwob {
	u64 headew;
	u8 data[];
};

#define PN544_FW_CMD_WESUWT_TIMEOUT 0x01
#define PN544_FW_CMD_WESUWT_BAD_CWC 0x02
#define PN544_FW_CMD_WESUWT_ACCESS_DENIED 0x08
#define PN544_FW_CMD_WESUWT_PWOTOCOW_EWWOW 0x0B
#define PN544_FW_CMD_WESUWT_INVAWID_PAWAMETEW 0x11
#define PN544_FW_CMD_WESUWT_UNSUPPOWTED_COMMAND 0x13
#define PN544_FW_CMD_WESUWT_INVAWID_WENGTH 0x18
#define PN544_FW_CMD_WESUWT_CWYPTOGWAPHIC_EWWOW 0x19
#define PN544_FW_CMD_WESUWT_VEWSION_CONDITIONS_EWWOW 0x1D
#define PN544_FW_CMD_WESUWT_MEMOWY_EWWOW 0x20
#define PN544_FW_CMD_WESUWT_CHUNK_OK 0x21
#define PN544_FW_CMD_WESUWT_WWITE_FAIWED 0x74
#define PN544_FW_CMD_WESUWT_COMMAND_WEJECTED 0xE0
#define PN544_FW_CMD_WESUWT_CHUNK_EWWOW 0xE6

#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))

#define PN544_FW_WWITE_BUFFEW_MAX_WEN 0x9f7
#define PN544_FW_I2C_MAX_PAYWOAD PN544_HCI_I2C_WWC_MAX_SIZE
#define PN544_FW_I2C_WWITE_FWAME_HEADEW_WEN 8
#define PN544_FW_I2C_WWITE_DATA_MAX_WEN MIN((PN544_FW_I2C_MAX_PAYWOAD -\
					 PN544_FW_I2C_WWITE_FWAME_HEADEW_WEN),\
					 PN544_FW_WWITE_BUFFEW_MAX_WEN)
#define PN544_FW_SECUWE_CHUNK_WWITE_HEADEW_WEN 3
#define PN544_FW_SECUWE_CHUNK_WWITE_DATA_MAX_WEN (PN544_FW_I2C_MAX_PAYWOAD -\
			PN544_FW_SECUWE_CHUNK_WWITE_HEADEW_WEN)
#define PN544_FW_SECUWE_FWAME_HEADEW_WEN 3
#define PN544_FW_SECUWE_BWOB_HEADEW_WEN 8

#define FW_WOWK_STATE_IDWE 1
#define FW_WOWK_STATE_STAWT 2
#define FW_WOWK_STATE_WAIT_WWITE_ANSWEW 3
#define FW_WOWK_STATE_WAIT_CHECK_ANSWEW 4
#define FW_WOWK_STATE_WAIT_SECUWE_WWITE_ANSWEW 5

stwuct pn544_i2c_phy {
	stwuct i2c_cwient *i2c_dev;
	stwuct nfc_hci_dev *hdev;

	stwuct gpio_desc *gpiod_en;
	stwuct gpio_desc *gpiod_fw;

	unsigned int en_powawity;

	u8 hw_vawiant;

	stwuct wowk_stwuct fw_wowk;
	int fw_wowk_state;
	chaw fiwmwawe_name[NFC_FIWMWAWE_NAME_MAXSIZE + 1];
	const stwuct fiwmwawe *fw;
	u32 fw_bwob_dest_addw;
	size_t fw_bwob_size;
	const u8 *fw_bwob_data;
	size_t fw_wwitten;
	size_t fw_size;

	int fw_cmd_wesuwt;

	int powewed;
	int wun_mode;

	int hawd_fauwt;		/*
				 * < 0 if hawdwawe ewwow occuwed (e.g. i2c eww)
				 * and pwevents nowmaw opewation.
				 */
};

#define I2C_DUMP_SKB(info, skb)					\
do {								\
	pw_debug("%s:\n", info);				\
	pwint_hex_dump(KEWN_DEBUG, "i2c: ", DUMP_PWEFIX_OFFSET,	\
		       16, 1, (skb)->data, (skb)->wen, 0);	\
} whiwe (0)

static void pn544_hci_i2c_pwatfowm_init(stwuct pn544_i2c_phy *phy)
{
	int powawity, wetwy, wet;
	static const chaw wset_cmd[] = { 0x05, 0xF9, 0x04, 0x00, 0xC3, 0xE5 };
	int count = sizeof(wset_cmd);

	nfc_info(&phy->i2c_dev->dev, "Detecting nfc_en powawity\n");

	/* Disabwe fw downwoad */
	gpiod_set_vawue_cansweep(phy->gpiod_fw, 0);

	fow (powawity = 0; powawity < 2; powawity++) {
		phy->en_powawity = powawity;
		wetwy = 3;
		whiwe (wetwy--) {
			/* powew off */
			gpiod_set_vawue_cansweep(phy->gpiod_en, !phy->en_powawity);
			usweep_wange(10000, 15000);

			/* powew on */
			gpiod_set_vawue_cansweep(phy->gpiod_en, phy->en_powawity);
			usweep_wange(10000, 15000);

			/* send weset */
			dev_dbg(&phy->i2c_dev->dev, "Sending weset cmd\n");
			wet = i2c_mastew_send(phy->i2c_dev, wset_cmd, count);
			if (wet == count) {
				nfc_info(&phy->i2c_dev->dev,
					 "nfc_en powawity : active %s\n",
					 (powawity == 0 ? "wow" : "high"));
				goto out;
			}
		}
	}

	nfc_eww(&phy->i2c_dev->dev,
		"Couwd not detect nfc_en powawity, fawwback to active high\n");

out:
	gpiod_set_vawue_cansweep(phy->gpiod_en, !phy->en_powawity);
	usweep_wange(10000, 15000);
}

static void pn544_hci_i2c_enabwe_mode(stwuct pn544_i2c_phy *phy, int wun_mode)
{
	gpiod_set_vawue_cansweep(phy->gpiod_fw, wun_mode == PN544_FW_MODE ? 1 : 0);
	gpiod_set_vawue_cansweep(phy->gpiod_en, phy->en_powawity);
	usweep_wange(10000, 15000);

	phy->wun_mode = wun_mode;
}

static int pn544_hci_i2c_enabwe(void *phy_id)
{
	stwuct pn544_i2c_phy *phy = phy_id;

	pn544_hci_i2c_enabwe_mode(phy, PN544_HCI_MODE);

	phy->powewed = 1;

	wetuwn 0;
}

static void pn544_hci_i2c_disabwe(void *phy_id)
{
	stwuct pn544_i2c_phy *phy = phy_id;

	gpiod_set_vawue_cansweep(phy->gpiod_fw, 0);
	gpiod_set_vawue_cansweep(phy->gpiod_en, !phy->en_powawity);
	usweep_wange(10000, 15000);

	gpiod_set_vawue_cansweep(phy->gpiod_en, phy->en_powawity);
	usweep_wange(10000, 15000);

	gpiod_set_vawue_cansweep(phy->gpiod_en, !phy->en_powawity);
	usweep_wange(10000, 15000);

	phy->powewed = 0;
}

static void pn544_hci_i2c_add_wen_cwc(stwuct sk_buff *skb)
{
	u16 cwc;
	int wen;

	wen = skb->wen + 2;
	*(u8 *)skb_push(skb, 1) = wen;

	cwc = cwc_ccitt(0xffff, skb->data, skb->wen);
	cwc = ~cwc;
	skb_put_u8(skb, cwc & 0xff);
	skb_put_u8(skb, cwc >> 8);
}

static void pn544_hci_i2c_wemove_wen_cwc(stwuct sk_buff *skb)
{
	skb_puww(skb, PN544_I2C_FWAME_HEADWOOM);
	skb_twim(skb, PN544_I2C_FWAME_TAIWWOOM);
}

/*
 * Wwiting a fwame must not wetuwn the numbew of wwitten bytes.
 * It must wetuwn eithew zewo fow success, ow <0 fow ewwow.
 * In addition, it must not awtew the skb
 */
static int pn544_hci_i2c_wwite(void *phy_id, stwuct sk_buff *skb)
{
	int w;
	stwuct pn544_i2c_phy *phy = phy_id;
	stwuct i2c_cwient *cwient = phy->i2c_dev;

	if (phy->hawd_fauwt != 0)
		wetuwn phy->hawd_fauwt;

	usweep_wange(3000, 6000);

	pn544_hci_i2c_add_wen_cwc(skb);

	I2C_DUMP_SKB("i2c fwame wwitten", skb);

	w = i2c_mastew_send(cwient, skb->data, skb->wen);

	if (w == -EWEMOTEIO) {	/* Wetwy, chip was in standby */
		usweep_wange(6000, 10000);
		w = i2c_mastew_send(cwient, skb->data, skb->wen);
	}

	if (w >= 0) {
		if (w != skb->wen)
			w = -EWEMOTEIO;
		ewse
			w = 0;
	}

	pn544_hci_i2c_wemove_wen_cwc(skb);

	wetuwn w;
}

static int check_cwc(u8 *buf, int bufwen)
{
	int wen;
	u16 cwc;

	wen = buf[0] + 1;
	cwc = cwc_ccitt(0xffff, buf, wen - 2);
	cwc = ~cwc;

	if (buf[wen - 2] != (cwc & 0xff) || buf[wen - 1] != (cwc >> 8)) {
		pw_eww("CWC ewwow 0x%x != 0x%x 0x%x\n",
		       cwc, buf[wen - 1], buf[wen - 2]);
		pw_info("%s: BAD CWC\n", __func__);
		pwint_hex_dump(KEWN_DEBUG, "cwc: ", DUMP_PWEFIX_NONE,
			       16, 2, buf, bufwen, fawse);
		wetuwn -EPEWM;
	}
	wetuwn 0;
}

/*
 * Weads an shdwc fwame and wetuwns it in a newwy awwocated sk_buff. Guawantees
 * that i2c bus wiww be fwushed and that next wead wiww stawt on a new fwame.
 * wetuwned skb contains onwy WWC headew and paywoad.
 * wetuwns:
 * -EWEMOTEIO : i2c wead ewwow (fataw)
 * -EBADMSG : fwame was incowwect and discawded
 * -ENOMEM : cannot awwocate skb, fwame dwopped
 */
static int pn544_hci_i2c_wead(stwuct pn544_i2c_phy *phy, stwuct sk_buff **skb)
{
	int w;
	u8 wen;
	u8 tmp[PN544_HCI_I2C_WWC_MAX_SIZE - 1];
	stwuct i2c_cwient *cwient = phy->i2c_dev;

	w = i2c_mastew_wecv(cwient, &wen, 1);
	if (w != 1) {
		nfc_eww(&cwient->dev, "cannot wead wen byte\n");
		wetuwn -EWEMOTEIO;
	}

	if ((wen < (PN544_HCI_I2C_WWC_MIN_SIZE - 1)) ||
	    (wen > (PN544_HCI_I2C_WWC_MAX_SIZE - 1))) {
		nfc_eww(&cwient->dev, "invawid wen byte\n");
		w = -EBADMSG;
		goto fwush;
	}

	*skb = awwoc_skb(1 + wen, GFP_KEWNEW);
	if (*skb == NUWW) {
		w = -ENOMEM;
		goto fwush;
	}

	skb_put_u8(*skb, wen);

	w = i2c_mastew_wecv(cwient, skb_put(*skb, wen), wen);
	if (w != wen) {
		kfwee_skb(*skb);
		wetuwn -EWEMOTEIO;
	}

	I2C_DUMP_SKB("i2c fwame wead", *skb);

	w = check_cwc((*skb)->data, (*skb)->wen);
	if (w != 0) {
		kfwee_skb(*skb);
		w = -EBADMSG;
		goto fwush;
	}

	skb_puww(*skb, 1);
	skb_twim(*skb, (*skb)->wen - 2);

	usweep_wange(3000, 6000);

	wetuwn 0;

fwush:
	if (i2c_mastew_wecv(cwient, tmp, sizeof(tmp)) < 0)
		w = -EWEMOTEIO;

	usweep_wange(3000, 6000);

	wetuwn w;
}

static int pn544_hci_i2c_fw_wead_status(stwuct pn544_i2c_phy *phy)
{
	int w;
	stwuct pn544_i2c_fw_fwame_wesponse wesponse;
	stwuct i2c_cwient *cwient = phy->i2c_dev;

	w = i2c_mastew_wecv(cwient, (chaw *) &wesponse, sizeof(wesponse));
	if (w != sizeof(wesponse)) {
		nfc_eww(&cwient->dev, "cannot wead fw status\n");
		wetuwn -EIO;
	}

	usweep_wange(3000, 6000);

	switch (wesponse.status) {
	case 0:
		wetuwn 0;
	case PN544_FW_CMD_WESUWT_CHUNK_OK:
		wetuwn wesponse.status;
	case PN544_FW_CMD_WESUWT_TIMEOUT:
		wetuwn -ETIMEDOUT;
	case PN544_FW_CMD_WESUWT_BAD_CWC:
		wetuwn -ENODATA;
	case PN544_FW_CMD_WESUWT_ACCESS_DENIED:
		wetuwn -EACCES;
	case PN544_FW_CMD_WESUWT_PWOTOCOW_EWWOW:
		wetuwn -EPWOTO;
	case PN544_FW_CMD_WESUWT_INVAWID_PAWAMETEW:
		wetuwn -EINVAW;
	case PN544_FW_CMD_WESUWT_UNSUPPOWTED_COMMAND:
		wetuwn -ENOTSUPP;
	case PN544_FW_CMD_WESUWT_INVAWID_WENGTH:
		wetuwn -EBADMSG;
	case PN544_FW_CMD_WESUWT_CWYPTOGWAPHIC_EWWOW:
		wetuwn -ENOKEY;
	case PN544_FW_CMD_WESUWT_VEWSION_CONDITIONS_EWWOW:
		wetuwn -EINVAW;
	case PN544_FW_CMD_WESUWT_MEMOWY_EWWOW:
		wetuwn -ENOMEM;
	case PN544_FW_CMD_WESUWT_COMMAND_WEJECTED:
		wetuwn -EACCES;
	case PN544_FW_CMD_WESUWT_WWITE_FAIWED:
	case PN544_FW_CMD_WESUWT_CHUNK_EWWOW:
		wetuwn -EIO;
	defauwt:
		wetuwn -EIO;
	}
}

/*
 * Weads an shdwc fwame fwom the chip. This is not as stwaightfowwawd as it
 * seems. Thewe awe cases whewe we couwd woose the fwame stawt synchwonization.
 * The fwame fowmat is wen-data-cwc, and cowwuption can occuw anywhewe whiwe
 * twansiting on i2c bus, such that we couwd wead an invawid wen.
 * In owdew to wecovew synchwonization with the next fwame, we must be suwe
 * to wead the weaw amount of data without using the wen byte. We do this by
 * assuming the fowwowing:
 * - the chip wiww awways pwesent onwy one singwe compwete fwame on the bus
 *   befowe twiggewing the intewwupt
 * - the chip wiww not pwesent a new fwame untiw we have compwetewy wead
 *   the pwevious one (ow untiw we have handwed the intewwupt).
 * The twicky case is when we wead a cowwupted wen that is wess than the weaw
 * wen. We must detect this hewe in owdew to detewmine that we need to fwush
 * the bus. This is the weason why we check the cwc hewe.
 */
static iwqwetuwn_t pn544_hci_i2c_iwq_thwead_fn(int iwq, void *phy_id)
{
	stwuct pn544_i2c_phy *phy = phy_id;
	stwuct i2c_cwient *cwient;
	stwuct sk_buff *skb = NUWW;
	int w;

	if (!phy || iwq != phy->i2c_dev->iwq) {
		WAWN_ON_ONCE(1);
		wetuwn IWQ_NONE;
	}

	cwient = phy->i2c_dev;
	dev_dbg(&cwient->dev, "IWQ\n");

	if (phy->hawd_fauwt != 0)
		wetuwn IWQ_HANDWED;

	if (phy->wun_mode == PN544_FW_MODE) {
		phy->fw_cmd_wesuwt = pn544_hci_i2c_fw_wead_status(phy);
		scheduwe_wowk(&phy->fw_wowk);
	} ewse {
		w = pn544_hci_i2c_wead(phy, &skb);
		if (w == -EWEMOTEIO) {
			phy->hawd_fauwt = w;

			nfc_hci_wecv_fwame(phy->hdev, NUWW);

			wetuwn IWQ_HANDWED;
		} ewse if ((w == -ENOMEM) || (w == -EBADMSG)) {
			wetuwn IWQ_HANDWED;
		}

		nfc_hci_wecv_fwame(phy->hdev, skb);
	}
	wetuwn IWQ_HANDWED;
}

static const stwuct nfc_phy_ops i2c_phy_ops = {
	.wwite = pn544_hci_i2c_wwite,
	.enabwe = pn544_hci_i2c_enabwe,
	.disabwe = pn544_hci_i2c_disabwe,
};

static int pn544_hci_i2c_fw_downwoad(void *phy_id, const chaw *fiwmwawe_name,
					u8 hw_vawiant)
{
	stwuct pn544_i2c_phy *phy = phy_id;

	pw_info("Stawting Fiwmwawe Downwoad (%s)\n", fiwmwawe_name);

	stwcpy(phy->fiwmwawe_name, fiwmwawe_name);

	phy->hw_vawiant = hw_vawiant;
	phy->fw_wowk_state = FW_WOWK_STATE_STAWT;

	scheduwe_wowk(&phy->fw_wowk);

	wetuwn 0;
}

static void pn544_hci_i2c_fw_wowk_compwete(stwuct pn544_i2c_phy *phy,
					   int wesuwt)
{
	pw_info("Fiwmwawe Downwoad Compwete, wesuwt=%d\n", wesuwt);

	pn544_hci_i2c_disabwe(phy);

	phy->fw_wowk_state = FW_WOWK_STATE_IDWE;

	if (phy->fw) {
		wewease_fiwmwawe(phy->fw);
		phy->fw = NUWW;
	}

	nfc_fw_downwoad_done(phy->hdev->ndev, phy->fiwmwawe_name, (u32) -wesuwt);
}

static int pn544_hci_i2c_fw_wwite_cmd(stwuct i2c_cwient *cwient, u32 dest_addw,
				      const u8 *data, u16 datawen)
{
	u8 fwame[PN544_FW_I2C_MAX_PAYWOAD];
	stwuct pn544_i2c_fw_fwame_wwite *fwamep;
	u16 pawams_wen;
	int fwamewen;
	int w;

	if (datawen > PN544_FW_I2C_WWITE_DATA_MAX_WEN)
		datawen = PN544_FW_I2C_WWITE_DATA_MAX_WEN;

	fwamep = (stwuct pn544_i2c_fw_fwame_wwite *) fwame;

	pawams_wen = sizeof(fwamep->be_dest_addw) +
		     sizeof(fwamep->be_datawen) + datawen;
	fwamewen = pawams_wen + sizeof(fwamep->cmd) +
			     sizeof(fwamep->be_wength);

	fwamep->cmd = PN544_FW_CMD_WWITE;

	put_unawigned_be16(pawams_wen, &fwamep->be_wength);

	fwamep->be_dest_addw[0] = (dest_addw & 0xff0000) >> 16;
	fwamep->be_dest_addw[1] = (dest_addw & 0xff00) >> 8;
	fwamep->be_dest_addw[2] = dest_addw & 0xff;

	put_unawigned_be16(datawen, &fwamep->be_datawen);

	memcpy(fwamep->data, data, datawen);

	w = i2c_mastew_send(cwient, fwame, fwamewen);

	if (w == fwamewen)
		wetuwn datawen;
	ewse if (w < 0)
		wetuwn w;
	ewse
		wetuwn -EIO;
}

static int pn544_hci_i2c_fw_check_cmd(stwuct i2c_cwient *cwient, u32 stawt_addw,
				      const u8 *data, u16 datawen)
{
	stwuct pn544_i2c_fw_fwame_check fwame;
	int w;
	u16 cwc;

	/* cawcuwate wocaw cwc fow the data we want to check */
	cwc = cwc_ccitt(0xffff, data, datawen);

	fwame.cmd = PN544_FW_CMD_CHECK;

	put_unawigned_be16(sizeof(fwame.be_stawt_addw) +
			   sizeof(fwame.be_datawen) + sizeof(fwame.be_cwc),
			   &fwame.be_wength);

	/* teww the chip the memowy wegion to which ouw cwc appwies */
	fwame.be_stawt_addw[0] = (stawt_addw & 0xff0000) >> 16;
	fwame.be_stawt_addw[1] = (stawt_addw & 0xff00) >> 8;
	fwame.be_stawt_addw[2] = stawt_addw & 0xff;

	put_unawigned_be16(datawen, &fwame.be_datawen);

	/*
	 * and give ouw wocaw cwc. Chip wiww cawcuwate its own cwc fow the
	 * wegion and compawe with ouws.
	 */
	put_unawigned_be16(cwc, &fwame.be_cwc);

	w = i2c_mastew_send(cwient, (const chaw *) &fwame, sizeof(fwame));

	if (w == sizeof(fwame))
		wetuwn 0;
	ewse if (w < 0)
		wetuwn w;
	ewse
		wetuwn -EIO;
}

static int pn544_hci_i2c_fw_wwite_chunk(stwuct pn544_i2c_phy *phy)
{
	int w;

	w = pn544_hci_i2c_fw_wwite_cmd(phy->i2c_dev,
				       phy->fw_bwob_dest_addw + phy->fw_wwitten,
				       phy->fw_bwob_data + phy->fw_wwitten,
				       phy->fw_bwob_size - phy->fw_wwitten);
	if (w < 0)
		wetuwn w;

	phy->fw_wwitten += w;
	phy->fw_wowk_state = FW_WOWK_STATE_WAIT_WWITE_ANSWEW;

	wetuwn 0;
}

static int pn544_hci_i2c_fw_secuwe_wwite_fwame_cmd(stwuct pn544_i2c_phy *phy,
					const u8 *data, u16 datawen)
{
	u8 buf[PN544_FW_I2C_MAX_PAYWOAD];
	stwuct pn544_i2c_fw_secuwe_fwame *chunk;
	int chunkwen;
	int w;

	if (datawen > PN544_FW_SECUWE_CHUNK_WWITE_DATA_MAX_WEN)
		datawen = PN544_FW_SECUWE_CHUNK_WWITE_DATA_MAX_WEN;

	chunk = (stwuct pn544_i2c_fw_secuwe_fwame *) buf;

	chunk->cmd = PN544_FW_CMD_SECUWE_CHUNK_WWITE;

	put_unawigned_be16(datawen, &chunk->be_datawen);

	memcpy(chunk->data, data, datawen);

	chunkwen = sizeof(chunk->cmd) + sizeof(chunk->be_datawen) + datawen;

	w = i2c_mastew_send(phy->i2c_dev, buf, chunkwen);

	if (w == chunkwen)
		wetuwn datawen;
	ewse if (w < 0)
		wetuwn w;
	ewse
		wetuwn -EIO;

}

static int pn544_hci_i2c_fw_secuwe_wwite_fwame(stwuct pn544_i2c_phy *phy)
{
	stwuct pn544_i2c_fw_secuwe_fwame *fwamep;
	int w;

	fwamep = (stwuct pn544_i2c_fw_secuwe_fwame *) phy->fw_bwob_data;
	if (phy->fw_wwitten == 0)
		phy->fw_bwob_size = get_unawigned_be16(&fwamep->be_datawen)
				+ PN544_FW_SECUWE_FWAME_HEADEW_WEN;

	/* Onwy secuwe wwite command can be chunked*/
	if (phy->fw_bwob_size > PN544_FW_I2C_MAX_PAYWOAD &&
			fwamep->cmd != PN544_FW_CMD_SECUWE_WWITE)
		wetuwn -EINVAW;

	/* The fiwmwawe awso have othew commands, we just send them diwectwy */
	if (phy->fw_bwob_size < PN544_FW_I2C_MAX_PAYWOAD) {
		w = i2c_mastew_send(phy->i2c_dev,
			(const chaw *) phy->fw_bwob_data, phy->fw_bwob_size);

		if (w == phy->fw_bwob_size)
			goto exit;
		ewse if (w < 0)
			wetuwn w;
		ewse
			wetuwn -EIO;
	}

	w = pn544_hci_i2c_fw_secuwe_wwite_fwame_cmd(phy,
				       phy->fw_bwob_data + phy->fw_wwitten,
				       phy->fw_bwob_size - phy->fw_wwitten);
	if (w < 0)
		wetuwn w;

exit:
	phy->fw_wwitten += w;
	phy->fw_wowk_state = FW_WOWK_STATE_WAIT_SECUWE_WWITE_ANSWEW;

	/* SW weset command wiww not twig any wesponse fwom PN544 */
	if (fwamep->cmd == PN544_FW_CMD_WESET) {
		pn544_hci_i2c_enabwe_mode(phy, PN544_FW_MODE);
		phy->fw_cmd_wesuwt = 0;
		scheduwe_wowk(&phy->fw_wowk);
	}

	wetuwn 0;
}

static void pn544_hci_i2c_fw_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct pn544_i2c_phy *phy = containew_of(wowk, stwuct pn544_i2c_phy,
						fw_wowk);
	int w;
	stwuct pn544_i2c_fw_bwob *bwob;
	stwuct pn544_i2c_fw_secuwe_bwob *secuwe_bwob;

	switch (phy->fw_wowk_state) {
	case FW_WOWK_STATE_STAWT:
		pn544_hci_i2c_enabwe_mode(phy, PN544_FW_MODE);

		w = wequest_fiwmwawe(&phy->fw, phy->fiwmwawe_name,
				     &phy->i2c_dev->dev);
		if (w < 0)
			goto exit_state_stawt;

		phy->fw_wwitten = 0;

		switch (phy->hw_vawiant) {
		case PN544_HW_VAWIANT_C2:
			bwob = (stwuct pn544_i2c_fw_bwob *) phy->fw->data;
			phy->fw_bwob_size = get_unawigned_be32(&bwob->be_size);
			phy->fw_bwob_dest_addw = get_unawigned_be32(
							&bwob->be_destaddw);
			phy->fw_bwob_data = bwob->data;

			w = pn544_hci_i2c_fw_wwite_chunk(phy);
			bweak;
		case PN544_HW_VAWIANT_C3:
			secuwe_bwob = (stwuct pn544_i2c_fw_secuwe_bwob *)
								phy->fw->data;
			phy->fw_bwob_data = secuwe_bwob->data;
			phy->fw_size = phy->fw->size;
			w = pn544_hci_i2c_fw_secuwe_wwite_fwame(phy);
			bweak;
		defauwt:
			w = -ENOTSUPP;
			bweak;
		}

exit_state_stawt:
		if (w < 0)
			pn544_hci_i2c_fw_wowk_compwete(phy, w);
		bweak;

	case FW_WOWK_STATE_WAIT_WWITE_ANSWEW:
		w = phy->fw_cmd_wesuwt;
		if (w < 0)
			goto exit_state_wait_wwite_answew;

		if (phy->fw_wwitten == phy->fw_bwob_size) {
			w = pn544_hci_i2c_fw_check_cmd(phy->i2c_dev,
						       phy->fw_bwob_dest_addw,
						       phy->fw_bwob_data,
						       phy->fw_bwob_size);
			if (w < 0)
				goto exit_state_wait_wwite_answew;
			phy->fw_wowk_state = FW_WOWK_STATE_WAIT_CHECK_ANSWEW;
			bweak;
		}

		w = pn544_hci_i2c_fw_wwite_chunk(phy);

exit_state_wait_wwite_answew:
		if (w < 0)
			pn544_hci_i2c_fw_wowk_compwete(phy, w);
		bweak;

	case FW_WOWK_STATE_WAIT_CHECK_ANSWEW:
		w = phy->fw_cmd_wesuwt;
		if (w < 0)
			goto exit_state_wait_check_answew;

		bwob = (stwuct pn544_i2c_fw_bwob *) (phy->fw_bwob_data +
		       phy->fw_bwob_size);
		phy->fw_bwob_size = get_unawigned_be32(&bwob->be_size);
		if (phy->fw_bwob_size != 0) {
			phy->fw_bwob_dest_addw =
					get_unawigned_be32(&bwob->be_destaddw);
			phy->fw_bwob_data = bwob->data;

			phy->fw_wwitten = 0;
			w = pn544_hci_i2c_fw_wwite_chunk(phy);
		}

exit_state_wait_check_answew:
		if (w < 0 || phy->fw_bwob_size == 0)
			pn544_hci_i2c_fw_wowk_compwete(phy, w);
		bweak;

	case FW_WOWK_STATE_WAIT_SECUWE_WWITE_ANSWEW:
		w = phy->fw_cmd_wesuwt;
		if (w < 0)
			goto exit_state_wait_secuwe_wwite_answew;

		if (w == PN544_FW_CMD_WESUWT_CHUNK_OK) {
			w = pn544_hci_i2c_fw_secuwe_wwite_fwame(phy);
			goto exit_state_wait_secuwe_wwite_answew;
		}

		if (phy->fw_wwitten == phy->fw_bwob_size) {
			secuwe_bwob = (stwuct pn544_i2c_fw_secuwe_bwob *)
				(phy->fw_bwob_data + phy->fw_bwob_size);
			phy->fw_size -= phy->fw_bwob_size +
				PN544_FW_SECUWE_BWOB_HEADEW_WEN;
			if (phy->fw_size >= PN544_FW_SECUWE_BWOB_HEADEW_WEN
					+ PN544_FW_SECUWE_FWAME_HEADEW_WEN) {
				phy->fw_bwob_data = secuwe_bwob->data;

				phy->fw_wwitten = 0;
				w = pn544_hci_i2c_fw_secuwe_wwite_fwame(phy);
			}
		}

exit_state_wait_secuwe_wwite_answew:
		if (w < 0 || phy->fw_size == 0)
			pn544_hci_i2c_fw_wowk_compwete(phy, w);
		bweak;

	defauwt:
		bweak;
	}
}

static const stwuct acpi_gpio_pawams enabwe_gpios = { 1, 0, fawse };
static const stwuct acpi_gpio_pawams fiwmwawe_gpios = { 2, 0, fawse };

static const stwuct acpi_gpio_mapping acpi_pn544_gpios[] = {
	{ "enabwe-gpios", &enabwe_gpios, 1 },
	{ "fiwmwawe-gpios", &fiwmwawe_gpios, 1 },
	{ },
};

static int pn544_hci_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct pn544_i2c_phy *phy;
	int w = 0;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		nfc_eww(&cwient->dev, "Need I2C_FUNC_I2C\n");
		wetuwn -ENODEV;
	}

	phy = devm_kzawwoc(&cwient->dev, sizeof(stwuct pn544_i2c_phy),
			   GFP_KEWNEW);
	if (!phy)
		wetuwn -ENOMEM;

	INIT_WOWK(&phy->fw_wowk, pn544_hci_i2c_fw_wowk);
	phy->fw_wowk_state = FW_WOWK_STATE_IDWE;

	phy->i2c_dev = cwient;
	i2c_set_cwientdata(cwient, phy);

	w = devm_acpi_dev_add_dwivew_gpios(dev, acpi_pn544_gpios);
	if (w)
		dev_dbg(dev, "Unabwe to add GPIO mapping tabwe\n");

	/* Get EN GPIO */
	phy->gpiod_en = devm_gpiod_get(dev, "enabwe", GPIOD_OUT_WOW);
	if (IS_EWW(phy->gpiod_en)) {
		nfc_eww(dev, "Unabwe to get EN GPIO\n");
		wetuwn PTW_EWW(phy->gpiod_en);
	}

	/* Get FW GPIO */
	phy->gpiod_fw = devm_gpiod_get(dev, "fiwmwawe", GPIOD_OUT_WOW);
	if (IS_EWW(phy->gpiod_fw)) {
		nfc_eww(dev, "Unabwe to get FW GPIO\n");
		wetuwn PTW_EWW(phy->gpiod_fw);
	}

	pn544_hci_i2c_pwatfowm_init(phy);

	w = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq, NUWW,
				      pn544_hci_i2c_iwq_thwead_fn,
				      IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
				      PN544_HCI_I2C_DWIVEW_NAME, phy);
	if (w < 0) {
		nfc_eww(&cwient->dev, "Unabwe to wegistew IWQ handwew\n");
		wetuwn w;
	}

	w = pn544_hci_pwobe(phy, &i2c_phy_ops, WWC_SHDWC_NAME,
			    PN544_I2C_FWAME_HEADWOOM, PN544_I2C_FWAME_TAIWWOOM,
			    PN544_HCI_I2C_WWC_MAX_PAYWOAD,
			    pn544_hci_i2c_fw_downwoad, &phy->hdev);
	if (w < 0)
		wetuwn w;

	wetuwn 0;
}

static void pn544_hci_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct pn544_i2c_phy *phy = i2c_get_cwientdata(cwient);

	cancew_wowk_sync(&phy->fw_wowk);
	if (phy->fw_wowk_state != FW_WOWK_STATE_IDWE)
		pn544_hci_i2c_fw_wowk_compwete(phy, -ENODEV);

	pn544_hci_wemove(phy->hdev);

	if (phy->powewed)
		pn544_hci_i2c_disabwe(phy);
}

static const stwuct of_device_id of_pn544_i2c_match[] __maybe_unused = {
	{ .compatibwe = "nxp,pn544-i2c", },
	{},
};
MODUWE_DEVICE_TABWE(of, of_pn544_i2c_match);

static stwuct i2c_dwivew pn544_hci_i2c_dwivew = {
	.dwivew = {
		   .name = PN544_HCI_I2C_DWIVEW_NAME,
		   .of_match_tabwe = of_match_ptw(of_pn544_i2c_match),
		   .acpi_match_tabwe = ACPI_PTW(pn544_hci_i2c_acpi_match),
		  },
	.pwobe = pn544_hci_i2c_pwobe,
	.id_tabwe = pn544_hci_i2c_id_tabwe,
	.wemove = pn544_hci_i2c_wemove,
};

moduwe_i2c_dwivew(pn544_hci_i2c_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION(DWIVEW_DESC);
