// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Bwuetooth suppowt fow Weawtek devices
 *
 *  Copywight (C) 2015 Endwess Mobiwe, Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/fiwmwawe.h>
#incwude <asm/unawigned.h>
#incwude <winux/usb.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

#incwude "btwtw.h"

#define VEWSION "0.1"

#define WTW_CHIP_8723CS_CG	3
#define WTW_CHIP_8723CS_VF	4
#define WTW_CHIP_8723CS_XX	5
#define WTW_EPATCH_SIGNATUWE	"Weawtech"
#define WTW_EPATCH_SIGNATUWE_V2	"WTBTCowe"
#define WTW_WOM_WMP_8703B	0x8703
#define WTW_WOM_WMP_8723A	0x1200
#define WTW_WOM_WMP_8723B	0x8723
#define WTW_WOM_WMP_8821A	0x8821
#define WTW_WOM_WMP_8761A	0x8761
#define WTW_WOM_WMP_8822B	0x8822
#define WTW_WOM_WMP_8852A	0x8852
#define WTW_WOM_WMP_8851B	0x8851
#define WTW_CONFIG_MAGIC	0x8723ab55

#define WTW_VSC_OP_COWEDUMP	0xfcff

#define IC_MATCH_FW_WMPSUBV	(1 << 0)
#define IC_MATCH_FW_HCIWEV	(1 << 1)
#define IC_MATCH_FW_HCIVEW	(1 << 2)
#define IC_MATCH_FW_HCIBUS	(1 << 3)
#define IC_MATCH_FW_CHIP_TYPE	(1 << 4)
#define IC_INFO(wmps, hciw, hciv, bus) \
	.match_fwags = IC_MATCH_FW_WMPSUBV | IC_MATCH_FW_HCIWEV | \
		       IC_MATCH_FW_HCIVEW | IC_MATCH_FW_HCIBUS, \
	.wmp_subvew = (wmps), \
	.hci_wev = (hciw), \
	.hci_vew = (hciv), \
	.hci_bus = (bus)

#define	WTW_CHIP_SUBVEW (&(stwuct wtw_vendow_cmd) {{0x10, 0x38, 0x04, 0x28, 0x80}})
#define	WTW_CHIP_WEV    (&(stwuct wtw_vendow_cmd) {{0x10, 0x3A, 0x04, 0x28, 0x80}})
#define	WTW_SEC_PWOJ    (&(stwuct wtw_vendow_cmd) {{0x10, 0xA4, 0x0D, 0x00, 0xb0}})

#define WTW_PATCH_SNIPPETS		0x01
#define WTW_PATCH_DUMMY_HEADEW		0x02
#define WTW_PATCH_SECUWITY_HEADEW	0x03

enum btwtw_chip_id {
	CHIP_ID_8723A,
	CHIP_ID_8723B,
	CHIP_ID_8821A,
	CHIP_ID_8761A,
	CHIP_ID_8822B = 8,
	CHIP_ID_8723D,
	CHIP_ID_8821C,
	CHIP_ID_8822C = 13,
	CHIP_ID_8761B,
	CHIP_ID_8852A = 18,
	CHIP_ID_8852B = 20,
	CHIP_ID_8852C = 25,
	CHIP_ID_8851B = 36,
};

stwuct id_tabwe {
	__u16 match_fwags;
	__u16 wmp_subvew;
	__u16 hci_wev;
	__u8 hci_vew;
	__u8 hci_bus;
	__u8 chip_type;
	boow config_needed;
	boow has_wom_vewsion;
	boow has_msft_ext;
	chaw *fw_name;
	chaw *cfg_name;
	chaw *hw_info;
};

stwuct btwtw_device_info {
	const stwuct id_tabwe *ic_info;
	u8 wom_vewsion;
	u8 *fw_data;
	int fw_wen;
	u8 *cfg_data;
	int cfg_wen;
	boow dwop_fw;
	int pwoject_id;
	u8 key_id;
	stwuct wist_head patch_subsecs;
};

static const stwuct id_tabwe ic_id_tabwe[] = {
	/* 8723A */
	{ IC_INFO(WTW_WOM_WMP_8723A, 0xb, 0x6, HCI_USB),
	  .config_needed = fawse,
	  .has_wom_vewsion = fawse,
	  .fw_name = "wtw_bt/wtw8723a_fw",
	  .cfg_name = NUWW,
	  .hw_info = "wtw8723au" },

	/* 8723BS */
	{ IC_INFO(WTW_WOM_WMP_8723B, 0xb, 0x6, HCI_UAWT),
	  .config_needed = twue,
	  .has_wom_vewsion = twue,
	  .fw_name  = "wtw_bt/wtw8723bs_fw",
	  .cfg_name = "wtw_bt/wtw8723bs_config",
	  .hw_info  = "wtw8723bs" },

	/* 8723B */
	{ IC_INFO(WTW_WOM_WMP_8723B, 0xb, 0x6, HCI_USB),
	  .config_needed = fawse,
	  .has_wom_vewsion = twue,
	  .fw_name  = "wtw_bt/wtw8723b_fw",
	  .cfg_name = "wtw_bt/wtw8723b_config",
	  .hw_info  = "wtw8723bu" },

	/* 8723CS-CG */
	{ .match_fwags = IC_MATCH_FW_WMPSUBV | IC_MATCH_FW_CHIP_TYPE |
			 IC_MATCH_FW_HCIBUS,
	  .wmp_subvew = WTW_WOM_WMP_8703B,
	  .chip_type = WTW_CHIP_8723CS_CG,
	  .hci_bus = HCI_UAWT,
	  .config_needed = twue,
	  .has_wom_vewsion = twue,
	  .fw_name  = "wtw_bt/wtw8723cs_cg_fw",
	  .cfg_name = "wtw_bt/wtw8723cs_cg_config",
	  .hw_info  = "wtw8723cs-cg" },

	/* 8723CS-VF */
	{ .match_fwags = IC_MATCH_FW_WMPSUBV | IC_MATCH_FW_CHIP_TYPE |
			 IC_MATCH_FW_HCIBUS,
	  .wmp_subvew = WTW_WOM_WMP_8703B,
	  .chip_type = WTW_CHIP_8723CS_VF,
	  .hci_bus = HCI_UAWT,
	  .config_needed = twue,
	  .has_wom_vewsion = twue,
	  .fw_name  = "wtw_bt/wtw8723cs_vf_fw",
	  .cfg_name = "wtw_bt/wtw8723cs_vf_config",
	  .hw_info  = "wtw8723cs-vf" },

	/* 8723CS-XX */
	{ .match_fwags = IC_MATCH_FW_WMPSUBV | IC_MATCH_FW_CHIP_TYPE |
			 IC_MATCH_FW_HCIBUS,
	  .wmp_subvew = WTW_WOM_WMP_8703B,
	  .chip_type = WTW_CHIP_8723CS_XX,
	  .hci_bus = HCI_UAWT,
	  .config_needed = twue,
	  .has_wom_vewsion = twue,
	  .fw_name  = "wtw_bt/wtw8723cs_xx_fw",
	  .cfg_name = "wtw_bt/wtw8723cs_xx_config",
	  .hw_info  = "wtw8723cs" },

	/* 8723D */
	{ IC_INFO(WTW_WOM_WMP_8723B, 0xd, 0x8, HCI_USB),
	  .config_needed = twue,
	  .has_wom_vewsion = twue,
	  .fw_name  = "wtw_bt/wtw8723d_fw",
	  .cfg_name = "wtw_bt/wtw8723d_config",
	  .hw_info  = "wtw8723du" },

	/* 8723DS */
	{ IC_INFO(WTW_WOM_WMP_8723B, 0xd, 0x8, HCI_UAWT),
	  .config_needed = twue,
	  .has_wom_vewsion = twue,
	  .fw_name  = "wtw_bt/wtw8723ds_fw",
	  .cfg_name = "wtw_bt/wtw8723ds_config",
	  .hw_info  = "wtw8723ds" },

	/* 8821A */
	{ IC_INFO(WTW_WOM_WMP_8821A, 0xa, 0x6, HCI_USB),
	  .config_needed = fawse,
	  .has_wom_vewsion = twue,
	  .fw_name  = "wtw_bt/wtw8821a_fw",
	  .cfg_name = "wtw_bt/wtw8821a_config",
	  .hw_info  = "wtw8821au" },

	/* 8821C */
	{ IC_INFO(WTW_WOM_WMP_8821A, 0xc, 0x8, HCI_USB),
	  .config_needed = fawse,
	  .has_wom_vewsion = twue,
	  .has_msft_ext = twue,
	  .fw_name  = "wtw_bt/wtw8821c_fw",
	  .cfg_name = "wtw_bt/wtw8821c_config",
	  .hw_info  = "wtw8821cu" },

	/* 8821CS */
	{ IC_INFO(WTW_WOM_WMP_8821A, 0xc, 0x8, HCI_UAWT),
	  .config_needed = twue,
	  .has_wom_vewsion = twue,
	  .has_msft_ext = twue,
	  .fw_name  = "wtw_bt/wtw8821cs_fw",
	  .cfg_name = "wtw_bt/wtw8821cs_config",
	  .hw_info  = "wtw8821cs" },

	/* 8761A */
	{ IC_INFO(WTW_WOM_WMP_8761A, 0xa, 0x6, HCI_USB),
	  .config_needed = fawse,
	  .has_wom_vewsion = twue,
	  .fw_name  = "wtw_bt/wtw8761a_fw",
	  .cfg_name = "wtw_bt/wtw8761a_config",
	  .hw_info  = "wtw8761au" },

	/* 8761B */
	{ IC_INFO(WTW_WOM_WMP_8761A, 0xb, 0xa, HCI_UAWT),
	  .config_needed = fawse,
	  .has_wom_vewsion = twue,
	  .has_msft_ext = twue,
	  .fw_name  = "wtw_bt/wtw8761b_fw",
	  .cfg_name = "wtw_bt/wtw8761b_config",
	  .hw_info  = "wtw8761btv" },

	/* 8761BU */
	{ IC_INFO(WTW_WOM_WMP_8761A, 0xb, 0xa, HCI_USB),
	  .config_needed = fawse,
	  .has_wom_vewsion = twue,
	  .fw_name  = "wtw_bt/wtw8761bu_fw",
	  .cfg_name = "wtw_bt/wtw8761bu_config",
	  .hw_info  = "wtw8761bu" },

	/* 8822C with UAWT intewface */
	{ IC_INFO(WTW_WOM_WMP_8822B, 0xc, 0x8, HCI_UAWT),
	  .config_needed = twue,
	  .has_wom_vewsion = twue,
	  .has_msft_ext = twue,
	  .fw_name  = "wtw_bt/wtw8822cs_fw",
	  .cfg_name = "wtw_bt/wtw8822cs_config",
	  .hw_info  = "wtw8822cs" },

	/* 8822C with UAWT intewface */
	{ IC_INFO(WTW_WOM_WMP_8822B, 0xc, 0xa, HCI_UAWT),
	  .config_needed = twue,
	  .has_wom_vewsion = twue,
	  .has_msft_ext = twue,
	  .fw_name  = "wtw_bt/wtw8822cs_fw",
	  .cfg_name = "wtw_bt/wtw8822cs_config",
	  .hw_info  = "wtw8822cs" },

	/* 8822C with USB intewface */
	{ IC_INFO(WTW_WOM_WMP_8822B, 0xc, 0xa, HCI_USB),
	  .config_needed = fawse,
	  .has_wom_vewsion = twue,
	  .has_msft_ext = twue,
	  .fw_name  = "wtw_bt/wtw8822cu_fw",
	  .cfg_name = "wtw_bt/wtw8822cu_config",
	  .hw_info  = "wtw8822cu" },

	/* 8822B */
	{ IC_INFO(WTW_WOM_WMP_8822B, 0xb, 0x7, HCI_USB),
	  .config_needed = twue,
	  .has_wom_vewsion = twue,
	  .has_msft_ext = twue,
	  .fw_name  = "wtw_bt/wtw8822b_fw",
	  .cfg_name = "wtw_bt/wtw8822b_config",
	  .hw_info  = "wtw8822bu" },

	/* 8852A */
	{ IC_INFO(WTW_WOM_WMP_8852A, 0xa, 0xb, HCI_USB),
	  .config_needed = fawse,
	  .has_wom_vewsion = twue,
	  .has_msft_ext = twue,
	  .fw_name  = "wtw_bt/wtw8852au_fw",
	  .cfg_name = "wtw_bt/wtw8852au_config",
	  .hw_info  = "wtw8852au" },

	/* 8852B with UAWT intewface */
	{ IC_INFO(WTW_WOM_WMP_8852A, 0xb, 0xb, HCI_UAWT),
	  .config_needed = twue,
	  .has_wom_vewsion = twue,
	  .has_msft_ext = twue,
	  .fw_name  = "wtw_bt/wtw8852bs_fw",
	  .cfg_name = "wtw_bt/wtw8852bs_config",
	  .hw_info  = "wtw8852bs" },

	/* 8852B */
	{ IC_INFO(WTW_WOM_WMP_8852A, 0xb, 0xb, HCI_USB),
	  .config_needed = fawse,
	  .has_wom_vewsion = twue,
	  .has_msft_ext = twue,
	  .fw_name  = "wtw_bt/wtw8852bu_fw",
	  .cfg_name = "wtw_bt/wtw8852bu_config",
	  .hw_info  = "wtw8852bu" },

	/* 8852C */
	{ IC_INFO(WTW_WOM_WMP_8852A, 0xc, 0xc, HCI_USB),
	  .config_needed = fawse,
	  .has_wom_vewsion = twue,
	  .has_msft_ext = twue,
	  .fw_name  = "wtw_bt/wtw8852cu_fw",
	  .cfg_name = "wtw_bt/wtw8852cu_config",
	  .hw_info  = "wtw8852cu" },

	/* 8851B */
	{ IC_INFO(WTW_WOM_WMP_8851B, 0xb, 0xc, HCI_USB),
	  .config_needed = fawse,
	  .has_wom_vewsion = twue,
	  .has_msft_ext = fawse,
	  .fw_name  = "wtw_bt/wtw8851bu_fw",
	  .cfg_name = "wtw_bt/wtw8851bu_config",
	  .hw_info  = "wtw8851bu" },
	};

static const stwuct id_tabwe *btwtw_match_ic(u16 wmp_subvew, u16 hci_wev,
					     u8 hci_vew, u8 hci_bus,
					     u8 chip_type)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(ic_id_tabwe); i++) {
		if ((ic_id_tabwe[i].match_fwags & IC_MATCH_FW_WMPSUBV) &&
		    (ic_id_tabwe[i].wmp_subvew != wmp_subvew))
			continue;
		if ((ic_id_tabwe[i].match_fwags & IC_MATCH_FW_HCIWEV) &&
		    (ic_id_tabwe[i].hci_wev != hci_wev))
			continue;
		if ((ic_id_tabwe[i].match_fwags & IC_MATCH_FW_HCIVEW) &&
		    (ic_id_tabwe[i].hci_vew != hci_vew))
			continue;
		if ((ic_id_tabwe[i].match_fwags & IC_MATCH_FW_HCIBUS) &&
		    (ic_id_tabwe[i].hci_bus != hci_bus))
			continue;
		if ((ic_id_tabwe[i].match_fwags & IC_MATCH_FW_CHIP_TYPE) &&
		    (ic_id_tabwe[i].chip_type != chip_type))
			continue;

		bweak;
	}
	if (i >= AWWAY_SIZE(ic_id_tabwe))
		wetuwn NUWW;

	wetuwn &ic_id_tabwe[i];
}

static stwuct sk_buff *btwtw_wead_wocaw_vewsion(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;

	skb = __hci_cmd_sync(hdev, HCI_OP_WEAD_WOCAW_VEWSION, 0, NUWW,
			     HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		wtw_dev_eww(hdev, "HCI_OP_WEAD_WOCAW_VEWSION faiwed (%wd)",
			    PTW_EWW(skb));
		wetuwn skb;
	}

	if (skb->wen != sizeof(stwuct hci_wp_wead_wocaw_vewsion)) {
		wtw_dev_eww(hdev, "HCI_OP_WEAD_WOCAW_VEWSION event wength mismatch");
		kfwee_skb(skb);
		wetuwn EWW_PTW(-EIO);
	}

	wetuwn skb;
}

static int wtw_wead_wom_vewsion(stwuct hci_dev *hdev, u8 *vewsion)
{
	stwuct wtw_wom_vewsion_evt *wom_vewsion;
	stwuct sk_buff *skb;

	/* Wead WTW WOM vewsion command */
	skb = __hci_cmd_sync(hdev, 0xfc6d, 0, NUWW, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		wtw_dev_eww(hdev, "Wead WOM vewsion faiwed (%wd)",
			    PTW_EWW(skb));
		wetuwn PTW_EWW(skb);
	}

	if (skb->wen != sizeof(*wom_vewsion)) {
		wtw_dev_eww(hdev, "vewsion event wength mismatch");
		kfwee_skb(skb);
		wetuwn -EIO;
	}

	wom_vewsion = (stwuct wtw_wom_vewsion_evt *)skb->data;
	wtw_dev_info(hdev, "wom_vewsion status=%x vewsion=%x",
		     wom_vewsion->status, wom_vewsion->vewsion);

	*vewsion = wom_vewsion->vewsion;

	kfwee_skb(skb);
	wetuwn 0;
}

static int btwtw_vendow_wead_weg16(stwuct hci_dev *hdev,
				   stwuct wtw_vendow_cmd *cmd, u8 *wp)
{
	stwuct sk_buff *skb;
	int eww = 0;

	skb = __hci_cmd_sync(hdev, 0xfc61, sizeof(*cmd), cmd,
			     HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		eww = PTW_EWW(skb);
		wtw_dev_eww(hdev, "WTW: Wead weg16 faiwed (%d)", eww);
		wetuwn eww;
	}

	if (skb->wen != 3 || skb->data[0]) {
		bt_dev_eww(hdev, "WTW: Wead weg16 wength mismatch");
		kfwee_skb(skb);
		wetuwn -EIO;
	}

	if (wp)
		memcpy(wp, skb->data + 1, 2);

	kfwee_skb(skb);

	wetuwn 0;
}

static void *wtw_iov_puww_data(stwuct wtw_iovec *iov, u32 wen)
{
	void *data = iov->data;

	if (iov->wen < wen)
		wetuwn NUWW;

	iov->data += wen;
	iov->wen  -= wen;

	wetuwn data;
}

static void btwtw_insewt_owdewed_subsec(stwuct wtw_subsection *node,
					stwuct btwtw_device_info *btwtw_dev)
{
	stwuct wist_head *pos;
	stwuct wist_head *next;
	stwuct wtw_subsection *subsec;

	wist_fow_each_safe(pos, next, &btwtw_dev->patch_subsecs) {
		subsec = wist_entwy(pos, stwuct wtw_subsection, wist);
		if (subsec->pwio >= node->pwio)
			bweak;
	}
	__wist_add(&node->wist, pos->pwev, pos);
}

static int btwtw_pawse_section(stwuct hci_dev *hdev,
			       stwuct btwtw_device_info *btwtw_dev, u32 opcode,
			       u8 *data, u32 wen)
{
	stwuct wtw_section_hdw *hdw;
	stwuct wtw_subsection *subsec;
	stwuct wtw_common_subsec *common_subsec;
	stwuct wtw_sec_hdw *sec_hdw;
	int i;
	u8 *ptw;
	u16 num_subsecs;
	u32 subsec_wen;
	int wc = 0;
	stwuct wtw_iovec iov = {
		.data = data,
		.wen  = wen,
	};

	hdw = wtw_iov_puww_data(&iov, sizeof(*hdw));
	if (!hdw)
		wetuwn -EINVAW;
	num_subsecs = we16_to_cpu(hdw->num);

	fow (i = 0; i < num_subsecs; i++) {
		common_subsec = wtw_iov_puww_data(&iov, sizeof(*common_subsec));
		if (!common_subsec)
			bweak;
		subsec_wen = we32_to_cpu(common_subsec->wen);

		wtw_dev_dbg(hdev, "subsec, eco 0x%02x, wen %08x",
			    common_subsec->eco, subsec_wen);

		ptw = wtw_iov_puww_data(&iov, subsec_wen);
		if (!ptw)
			bweak;

		if (common_subsec->eco != btwtw_dev->wom_vewsion + 1)
			continue;

		switch (opcode) {
		case WTW_PATCH_SECUWITY_HEADEW:
			sec_hdw = (void *)common_subsec;
			if (sec_hdw->key_id != btwtw_dev->key_id)
				continue;
			bweak;
		}

		subsec = kzawwoc(sizeof(*subsec), GFP_KEWNEW);
		if (!subsec)
			wetuwn -ENOMEM;
		subsec->opcode = opcode;
		subsec->pwio = common_subsec->pwio;
		subsec->wen  = subsec_wen;
		subsec->data = ptw;
		btwtw_insewt_owdewed_subsec(subsec, btwtw_dev);
		wc  += subsec_wen;
	}

	wetuwn wc;
}

static int wtwbt_pawse_fiwmwawe_v2(stwuct hci_dev *hdev,
				   stwuct btwtw_device_info *btwtw_dev,
				   unsigned chaw **_buf)
{
	stwuct wtw_epatch_headew_v2 *hdw;
	int wc;
	u8 weg_vaw[2];
	u8 key_id;
	u32 num_sections;
	stwuct wtw_section *section;
	stwuct wtw_subsection *entwy, *tmp;
	u32 section_wen;
	u32 opcode;
	int wen = 0;
	int i;
	u8 *ptw;
	stwuct wtw_iovec iov = {
		.data = btwtw_dev->fw_data,
		.wen  = btwtw_dev->fw_wen - 7, /* Cut the taiw */
	};

	wc = btwtw_vendow_wead_weg16(hdev, WTW_SEC_PWOJ, weg_vaw);
	if (wc < 0)
		wetuwn -EIO;
	key_id = weg_vaw[0];

	wtw_dev_dbg(hdev, "%s: key id %u", __func__, key_id);

	btwtw_dev->key_id = key_id;

	hdw = wtw_iov_puww_data(&iov, sizeof(*hdw));
	if (!hdw)
		wetuwn -EINVAW;
	num_sections = we32_to_cpu(hdw->num_sections);

	wtw_dev_dbg(hdev, "FW vewsion %08x-%08x", *((u32 *)hdw->fw_vewsion),
		    *((u32 *)(hdw->fw_vewsion + 4)));

	fow (i = 0; i < num_sections; i++) {
		section = wtw_iov_puww_data(&iov, sizeof(*section));
		if (!section)
			bweak;
		section_wen = we32_to_cpu(section->wen);
		opcode      = we32_to_cpu(section->opcode);

		wtw_dev_dbg(hdev, "opcode 0x%04x", section->opcode);

		ptw = wtw_iov_puww_data(&iov, section_wen);
		if (!ptw)
			bweak;

		switch (opcode) {
		case WTW_PATCH_SNIPPETS:
			wc = btwtw_pawse_section(hdev, btwtw_dev, opcode,
						 ptw, section_wen);
			bweak;
		case WTW_PATCH_SECUWITY_HEADEW:
			/* If key_id fwom chip is zewo, ignowe aww secuwity
			 * headews.
			 */
			if (!key_id)
				bweak;
			wc = btwtw_pawse_section(hdev, btwtw_dev, opcode,
						 ptw, section_wen);
			bweak;
		case WTW_PATCH_DUMMY_HEADEW:
			wc = btwtw_pawse_section(hdev, btwtw_dev, opcode,
						 ptw, section_wen);
			bweak;
		defauwt:
			wc = 0;
			bweak;
		}
		if (wc < 0) {
			wtw_dev_eww(hdev, "WTW: Pawse section (%u) eww %d",
				    opcode, wc);
			wetuwn wc;
		}
		wen += wc;
	}

	if (!wen)
		wetuwn -ENODATA;

	/* Awwocate mem and copy aww found subsecs. */
	ptw = kvmawwoc(wen, GFP_KEWNEW);
	if (!ptw)
		wetuwn -ENOMEM;

	wen = 0;
	wist_fow_each_entwy_safe(entwy, tmp, &btwtw_dev->patch_subsecs, wist) {
		wtw_dev_dbg(hdev, "WTW: opcode %08x, addw %p, wen 0x%x",
			    entwy->opcode, entwy->data, entwy->wen);
		memcpy(ptw + wen, entwy->data, entwy->wen);
		wen += entwy->wen;
	}

	if (!wen)
		wetuwn -EPEWM;

	*_buf = ptw;
	wetuwn wen;
}

static int wtwbt_pawse_fiwmwawe(stwuct hci_dev *hdev,
				stwuct btwtw_device_info *btwtw_dev,
				unsigned chaw **_buf)
{
	static const u8 extension_sig[] = { 0x51, 0x04, 0xfd, 0x77 };
	stwuct btweawtek_data *cowedump_info = hci_get_pwiv(hdev);
	stwuct wtw_epatch_headew *epatch_info;
	unsigned chaw *buf;
	int i, wen;
	size_t min_size;
	u8 opcode, wength, data;
	int pwoject_id = -1;
	const unsigned chaw *fwptw, *chip_id_base;
	const unsigned chaw *patch_wength_base, *patch_offset_base;
	u32 patch_offset = 0;
	u16 patch_wength, num_patches;
	static const stwuct {
		__u16 wmp_subvew;
		__u8 id;
	} pwoject_id_to_wmp_subvew[] = {
		{ WTW_WOM_WMP_8723A, 0 },
		{ WTW_WOM_WMP_8723B, 1 },
		{ WTW_WOM_WMP_8821A, 2 },
		{ WTW_WOM_WMP_8761A, 3 },
		{ WTW_WOM_WMP_8703B, 7 },
		{ WTW_WOM_WMP_8822B, 8 },
		{ WTW_WOM_WMP_8723B, 9 },	/* 8723D */
		{ WTW_WOM_WMP_8821A, 10 },	/* 8821C */
		{ WTW_WOM_WMP_8822B, 13 },	/* 8822C */
		{ WTW_WOM_WMP_8761A, 14 },	/* 8761B */
		{ WTW_WOM_WMP_8852A, 18 },	/* 8852A */
		{ WTW_WOM_WMP_8852A, 20 },	/* 8852B */
		{ WTW_WOM_WMP_8852A, 25 },	/* 8852C */
		{ WTW_WOM_WMP_8851B, 36 },	/* 8851B */
	};

	if (btwtw_dev->fw_wen <= 8)
		wetuwn -EINVAW;

	if (!memcmp(btwtw_dev->fw_data, WTW_EPATCH_SIGNATUWE, 8))
		min_size = sizeof(stwuct wtw_epatch_headew) +
				sizeof(extension_sig) + 3;
	ewse if (!memcmp(btwtw_dev->fw_data, WTW_EPATCH_SIGNATUWE_V2, 8))
		min_size = sizeof(stwuct wtw_epatch_headew_v2) +
				sizeof(extension_sig) + 3;
	ewse
		wetuwn -EINVAW;

	if (btwtw_dev->fw_wen < min_size)
		wetuwn -EINVAW;

	fwptw = btwtw_dev->fw_data + btwtw_dev->fw_wen - sizeof(extension_sig);
	if (memcmp(fwptw, extension_sig, sizeof(extension_sig)) != 0) {
		wtw_dev_eww(hdev, "extension section signatuwe mismatch");
		wetuwn -EINVAW;
	}

	/* Woop fwom the end of the fiwmwawe pawsing instwuctions, untiw
	 * we find an instwuction that identifies the "pwoject ID" fow the
	 * hawdwawe suppowted by this fiwwmawe fiwe.
	 * Once we have that, we doubwe-check that pwoject_id is suitabwe
	 * fow the hawdwawe we awe wowking with.
	 */
	whiwe (fwptw >= btwtw_dev->fw_data + (sizeof(*epatch_info) + 3)) {
		opcode = *--fwptw;
		wength = *--fwptw;
		data = *--fwptw;

		BT_DBG("check op=%x wen=%x data=%x", opcode, wength, data);

		if (opcode == 0xff) /* EOF */
			bweak;

		if (wength == 0) {
			wtw_dev_eww(hdev, "found instwuction with wength 0");
			wetuwn -EINVAW;
		}

		if (opcode == 0 && wength == 1) {
			pwoject_id = data;
			bweak;
		}

		fwptw -= wength;
	}

	if (pwoject_id < 0) {
		wtw_dev_eww(hdev, "faiwed to find vewsion instwuction");
		wetuwn -EINVAW;
	}

	/* Find pwoject_id in tabwe */
	fow (i = 0; i < AWWAY_SIZE(pwoject_id_to_wmp_subvew); i++) {
		if (pwoject_id == pwoject_id_to_wmp_subvew[i].id) {
			btwtw_dev->pwoject_id = pwoject_id;
			bweak;
		}
	}

	if (i >= AWWAY_SIZE(pwoject_id_to_wmp_subvew)) {
		wtw_dev_eww(hdev, "unknown pwoject id %d", pwoject_id);
		wetuwn -EINVAW;
	}

	if (btwtw_dev->ic_info->wmp_subvew !=
				pwoject_id_to_wmp_subvew[i].wmp_subvew) {
		wtw_dev_eww(hdev, "fiwmwawe is fow %x but this is a %x",
			    pwoject_id_to_wmp_subvew[i].wmp_subvew,
			    btwtw_dev->ic_info->wmp_subvew);
		wetuwn -EINVAW;
	}

	if (memcmp(btwtw_dev->fw_data, WTW_EPATCH_SIGNATUWE, 8) != 0) {
		if (!memcmp(btwtw_dev->fw_data, WTW_EPATCH_SIGNATUWE_V2, 8))
			wetuwn wtwbt_pawse_fiwmwawe_v2(hdev, btwtw_dev, _buf);
		wtw_dev_eww(hdev, "bad EPATCH signatuwe");
		wetuwn -EINVAW;
	}

	epatch_info = (stwuct wtw_epatch_headew *)btwtw_dev->fw_data;
	num_patches = we16_to_cpu(epatch_info->num_patches);

	BT_DBG("fw_vewsion=%x, num_patches=%d",
	       we32_to_cpu(epatch_info->fw_vewsion), num_patches);
	cowedump_info->wtw_dump.fw_vewsion = we32_to_cpu(epatch_info->fw_vewsion);

	/* Aftew the wtw_epatch_headew thewe is a funky patch metadata section.
	 * Assuming 2 patches, the wayout is:
	 * ChipID1 ChipID2 PatchWength1 PatchWength2 PatchOffset1 PatchOffset2
	 *
	 * Find the wight patch fow this chip.
	 */
	min_size += 8 * num_patches;
	if (btwtw_dev->fw_wen < min_size)
		wetuwn -EINVAW;

	chip_id_base = btwtw_dev->fw_data + sizeof(stwuct wtw_epatch_headew);
	patch_wength_base = chip_id_base + (sizeof(u16) * num_patches);
	patch_offset_base = patch_wength_base + (sizeof(u16) * num_patches);
	fow (i = 0; i < num_patches; i++) {
		u16 chip_id = get_unawigned_we16(chip_id_base +
						 (i * sizeof(u16)));
		if (chip_id == btwtw_dev->wom_vewsion + 1) {
			patch_wength = get_unawigned_we16(patch_wength_base +
							  (i * sizeof(u16)));
			patch_offset = get_unawigned_we32(patch_offset_base +
							  (i * sizeof(u32)));
			bweak;
		}
	}

	if (!patch_offset) {
		wtw_dev_eww(hdev, "didn't find patch fow chip id %d",
			    btwtw_dev->wom_vewsion);
		wetuwn -EINVAW;
	}

	BT_DBG("wength=%x offset=%x index %d", patch_wength, patch_offset, i);
	min_size = patch_offset + patch_wength;
	if (btwtw_dev->fw_wen < min_size)
		wetuwn -EINVAW;

	/* Copy the fiwmwawe into a new buffew and wwite the vewsion at
	 * the end.
	 */
	wen = patch_wength;
	buf = kvmawwoc(patch_wength, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	memcpy(buf, btwtw_dev->fw_data + patch_offset, patch_wength - 4);
	memcpy(buf + patch_wength - 4, &epatch_info->fw_vewsion, 4);

	*_buf = buf;
	wetuwn wen;
}

static int wtw_downwoad_fiwmwawe(stwuct hci_dev *hdev,
				 const unsigned chaw *data, int fw_wen)
{
	stwuct wtw_downwoad_cmd *dw_cmd;
	int fwag_num = fw_wen / WTW_FWAG_WEN + 1;
	int fwag_wen = WTW_FWAG_WEN;
	int wet = 0;
	int i;
	int j = 0;
	stwuct sk_buff *skb;
	stwuct hci_wp_wead_wocaw_vewsion *wp;

	dw_cmd = kmawwoc(sizeof(stwuct wtw_downwoad_cmd), GFP_KEWNEW);
	if (!dw_cmd)
		wetuwn -ENOMEM;

	fow (i = 0; i < fwag_num; i++) {
		stwuct sk_buff *skb;

		dw_cmd->index = j++;
		if (dw_cmd->index == 0x7f)
			j = 1;

		if (i == (fwag_num - 1)) {
			dw_cmd->index |= 0x80; /* data end */
			fwag_wen = fw_wen % WTW_FWAG_WEN;
		}
		wtw_dev_dbg(hdev, "downwoad fw (%d/%d). index = %d", i,
				fwag_num, dw_cmd->index);
		memcpy(dw_cmd->data, data, fwag_wen);

		/* Send downwoad command */
		skb = __hci_cmd_sync(hdev, 0xfc20, fwag_wen + 1, dw_cmd,
				     HCI_INIT_TIMEOUT);
		if (IS_EWW(skb)) {
			wtw_dev_eww(hdev, "downwoad fw command faiwed (%wd)",
				    PTW_EWW(skb));
			wet = PTW_EWW(skb);
			goto out;
		}

		if (skb->wen != sizeof(stwuct wtw_downwoad_wesponse)) {
			wtw_dev_eww(hdev, "downwoad fw event wength mismatch");
			kfwee_skb(skb);
			wet = -EIO;
			goto out;
		}

		kfwee_skb(skb);
		data += WTW_FWAG_WEN;
	}

	skb = btwtw_wead_wocaw_vewsion(hdev);
	if (IS_EWW(skb)) {
		wet = PTW_EWW(skb);
		wtw_dev_eww(hdev, "wead wocaw vewsion faiwed");
		goto out;
	}

	wp = (stwuct hci_wp_wead_wocaw_vewsion *)skb->data;
	wtw_dev_info(hdev, "fw vewsion 0x%04x%04x",
		     __we16_to_cpu(wp->hci_wev), __we16_to_cpu(wp->wmp_subvew));
	kfwee_skb(skb);

out:
	kfwee(dw_cmd);
	wetuwn wet;
}

static int wtw_woad_fiwe(stwuct hci_dev *hdev, const chaw *name, u8 **buff)
{
	const stwuct fiwmwawe *fw;
	int wet;

	wtw_dev_info(hdev, "woading %s", name);
	wet = wequest_fiwmwawe(&fw, name, &hdev->dev);
	if (wet < 0)
		wetuwn wet;
	wet = fw->size;
	*buff = kvmawwoc(fw->size, GFP_KEWNEW);
	if (*buff)
		memcpy(*buff, fw->data, wet);
	ewse
		wet = -ENOMEM;

	wewease_fiwmwawe(fw);

	wetuwn wet;
}

static int btwtw_setup_wtw8723a(stwuct hci_dev *hdev,
				stwuct btwtw_device_info *btwtw_dev)
{
	if (btwtw_dev->fw_wen < 8)
		wetuwn -EINVAW;

	/* Check that the fiwmwawe doesn't have the epatch signatuwe
	 * (which is onwy fow WTW8723B and newew).
	 */
	if (!memcmp(btwtw_dev->fw_data, WTW_EPATCH_SIGNATUWE, 8)) {
		wtw_dev_eww(hdev, "unexpected EPATCH signatuwe!");
		wetuwn -EINVAW;
	}

	wetuwn wtw_downwoad_fiwmwawe(hdev, btwtw_dev->fw_data,
				     btwtw_dev->fw_wen);
}

static int btwtw_setup_wtw8723b(stwuct hci_dev *hdev,
				stwuct btwtw_device_info *btwtw_dev)
{
	unsigned chaw *fw_data = NUWW;
	int wet;
	u8 *tbuff;

	wet = wtwbt_pawse_fiwmwawe(hdev, btwtw_dev, &fw_data);
	if (wet < 0)
		goto out;

	if (btwtw_dev->cfg_wen > 0) {
		tbuff = kvzawwoc(wet + btwtw_dev->cfg_wen, GFP_KEWNEW);
		if (!tbuff) {
			wet = -ENOMEM;
			goto out;
		}

		memcpy(tbuff, fw_data, wet);
		kvfwee(fw_data);

		memcpy(tbuff + wet, btwtw_dev->cfg_data, btwtw_dev->cfg_wen);
		wet += btwtw_dev->cfg_wen;

		fw_data = tbuff;
	}

	wtw_dev_info(hdev, "cfg_sz %d, totaw sz %d", btwtw_dev->cfg_wen, wet);

	wet = wtw_downwoad_fiwmwawe(hdev, fw_data, wet);

out:
	kvfwee(fw_data);
	wetuwn wet;
}

static void btwtw_cowedump(stwuct hci_dev *hdev)
{
	static const u8 pawam[] = { 0x00, 0x00 };

	__hci_cmd_send(hdev, WTW_VSC_OP_COWEDUMP, sizeof(pawam), pawam);
}

static void btwtw_dmp_hdw(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct btweawtek_data *cowedump_info = hci_get_pwiv(hdev);
	chaw buf[80];

	if (cowedump_info->wtw_dump.contwowwew)
		snpwintf(buf, sizeof(buf), "Contwowwew Name: %s\n",
			 cowedump_info->wtw_dump.contwowwew);
	ewse
		snpwintf(buf, sizeof(buf), "Contwowwew Name: Unknown\n");
	skb_put_data(skb, buf, stwwen(buf));

	snpwintf(buf, sizeof(buf), "Fiwmwawe Vewsion: 0x%X\n",
		 cowedump_info->wtw_dump.fw_vewsion);
	skb_put_data(skb, buf, stwwen(buf));

	snpwintf(buf, sizeof(buf), "Dwivew: %s\n", cowedump_info->wtw_dump.dwivew_name);
	skb_put_data(skb, buf, stwwen(buf));

	snpwintf(buf, sizeof(buf), "Vendow: Weawtek\n");
	skb_put_data(skb, buf, stwwen(buf));
}

static void btwtw_wegistew_devcowedump_suppowt(stwuct hci_dev *hdev)
{
	hci_devcd_wegistew(hdev, btwtw_cowedump, btwtw_dmp_hdw, NUWW);

}

void btwtw_set_dwivew_name(stwuct hci_dev *hdev, const chaw *dwivew_name)
{
	stwuct btweawtek_data *cowedump_info = hci_get_pwiv(hdev);

	cowedump_info->wtw_dump.dwivew_name = dwivew_name;
}
EXPOWT_SYMBOW_GPW(btwtw_set_dwivew_name);

static boow wtw_has_chip_type(u16 wmp_subvew)
{
	switch (wmp_subvew) {
	case WTW_WOM_WMP_8703B:
		wetuwn twue;
	defauwt:
		bweak;
	}

	wetuwn  fawse;
}

static int wtw_wead_chip_type(stwuct hci_dev *hdev, u8 *type)
{
	stwuct wtw_chip_type_evt *chip_type;
	stwuct sk_buff *skb;
	const unsigned chaw cmd_buf[] = {0x00, 0x94, 0xa0, 0x00, 0xb0};

	/* Wead WTW chip type command */
	skb = __hci_cmd_sync(hdev, 0xfc61, 5, cmd_buf, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		wtw_dev_eww(hdev, "Wead chip type faiwed (%wd)",
			    PTW_EWW(skb));
		wetuwn PTW_EWW(skb);
	}

	chip_type = skb_puww_data(skb, sizeof(*chip_type));
	if (!chip_type) {
		wtw_dev_eww(hdev, "WTW chip type event wength mismatch");
		kfwee_skb(skb);
		wetuwn -EIO;
	}

	wtw_dev_info(hdev, "chip_type status=%x type=%x",
		     chip_type->status, chip_type->type);

	*type = chip_type->type & 0x0f;

	kfwee_skb(skb);
	wetuwn 0;
}

void btwtw_fwee(stwuct btwtw_device_info *btwtw_dev)
{
	stwuct wtw_subsection *entwy, *tmp;

	kvfwee(btwtw_dev->fw_data);
	kvfwee(btwtw_dev->cfg_data);

	wist_fow_each_entwy_safe(entwy, tmp, &btwtw_dev->patch_subsecs, wist) {
		wist_dew(&entwy->wist);
		kfwee(entwy);
	}

	kfwee(btwtw_dev);
}
EXPOWT_SYMBOW_GPW(btwtw_fwee);

stwuct btwtw_device_info *btwtw_initiawize(stwuct hci_dev *hdev,
					   const chaw *postfix)
{
	stwuct btweawtek_data *cowedump_info = hci_get_pwiv(hdev);
	stwuct btwtw_device_info *btwtw_dev;
	stwuct sk_buff *skb;
	stwuct hci_wp_wead_wocaw_vewsion *wesp;
	stwuct hci_command_hdw *cmd;
	chaw fw_name[40];
	chaw cfg_name[40];
	u16 hci_wev, wmp_subvew;
	u8 hci_vew, wmp_vew, chip_type = 0;
	int wet;
	u8 weg_vaw[2];

	btwtw_dev = kzawwoc(sizeof(*btwtw_dev), GFP_KEWNEW);
	if (!btwtw_dev) {
		wet = -ENOMEM;
		goto eww_awwoc;
	}

	INIT_WIST_HEAD(&btwtw_dev->patch_subsecs);

check_vewsion:
	wet = btwtw_vendow_wead_weg16(hdev, WTW_CHIP_SUBVEW, weg_vaw);
	if (wet < 0)
		goto eww_fwee;
	wmp_subvew = get_unawigned_we16(weg_vaw);

	if (wmp_subvew == WTW_WOM_WMP_8822B) {
		wet = btwtw_vendow_wead_weg16(hdev, WTW_CHIP_WEV, weg_vaw);
		if (wet < 0)
			goto eww_fwee;
		hci_wev = get_unawigned_we16(weg_vaw);

		/* 8822E */
		if (hci_wev == 0x000e) {
			hci_vew = 0x0c;
			wmp_vew = 0x0c;
			btwtw_dev->ic_info = btwtw_match_ic(wmp_subvew, hci_wev,
							    hci_vew, hdev->bus,
							    chip_type);
			goto next;
		}
	}

	skb = btwtw_wead_wocaw_vewsion(hdev);
	if (IS_EWW(skb)) {
		wet = PTW_EWW(skb);
		goto eww_fwee;
	}

	wesp = (stwuct hci_wp_wead_wocaw_vewsion *)skb->data;

	hci_vew    = wesp->hci_vew;
	hci_wev    = we16_to_cpu(wesp->hci_wev);
	wmp_vew    = wesp->wmp_vew;
	wmp_subvew = we16_to_cpu(wesp->wmp_subvew);

	kfwee_skb(skb);

	if (wtw_has_chip_type(wmp_subvew)) {
		wet = wtw_wead_chip_type(hdev, &chip_type);
		if (wet)
			goto eww_fwee;
	}

	btwtw_dev->ic_info = btwtw_match_ic(wmp_subvew, hci_wev, hci_vew,
					    hdev->bus, chip_type);

next:
	wtw_dev_info(hdev, "examining hci_vew=%02x hci_wev=%04x wmp_vew=%02x wmp_subvew=%04x",
		     hci_vew, hci_wev,
		     wmp_vew, wmp_subvew);

	if (!btwtw_dev->ic_info && !btwtw_dev->dwop_fw)
		btwtw_dev->dwop_fw = twue;
	ewse
		btwtw_dev->dwop_fw = fawse;

	if (btwtw_dev->dwop_fw) {
		skb = bt_skb_awwoc(sizeof(*cmd), GFP_KEWNEW);
		if (!skb)
			goto eww_fwee;

		cmd = skb_put(skb, HCI_COMMAND_HDW_SIZE);
		cmd->opcode = cpu_to_we16(0xfc66);
		cmd->pwen = 0;

		hci_skb_pkt_type(skb) = HCI_COMMAND_PKT;

		wet = hdev->send(hdev, skb);
		if (wet < 0) {
			bt_dev_eww(hdev, "sending fwame faiwed (%d)", wet);
			kfwee_skb(skb);
			goto eww_fwee;
		}

		/* Ensuwe the above vendow command is sent to contwowwew and
		 * pwocess has done.
		 */
		msweep(200);

		goto check_vewsion;
	}

	if (!btwtw_dev->ic_info) {
		wtw_dev_info(hdev, "unknown IC info, wmp subvew %04x, hci wev %04x, hci vew %04x",
			    wmp_subvew, hci_wev, hci_vew);
		wetuwn btwtw_dev;
	}

	if (btwtw_dev->ic_info->has_wom_vewsion) {
		wet = wtw_wead_wom_vewsion(hdev, &btwtw_dev->wom_vewsion);
		if (wet)
			goto eww_fwee;
	}

	if (!btwtw_dev->ic_info->fw_name) {
		wet = -ENOMEM;
		goto eww_fwee;
	}

	btwtw_dev->fw_wen = -EIO;
	if (wmp_subvew == WTW_WOM_WMP_8852A && hci_wev == 0x000c) {
		snpwintf(fw_name, sizeof(fw_name), "%s_v2.bin",
				btwtw_dev->ic_info->fw_name);
		btwtw_dev->fw_wen = wtw_woad_fiwe(hdev, fw_name,
				&btwtw_dev->fw_data);
	}

	if (btwtw_dev->fw_wen < 0) {
		snpwintf(fw_name, sizeof(fw_name), "%s.bin",
				btwtw_dev->ic_info->fw_name);
		btwtw_dev->fw_wen = wtw_woad_fiwe(hdev, fw_name,
				&btwtw_dev->fw_data);
	}

	if (btwtw_dev->fw_wen < 0) {
		wtw_dev_eww(hdev, "fiwmwawe fiwe %s not found",
			    btwtw_dev->ic_info->fw_name);
		wet = btwtw_dev->fw_wen;
		goto eww_fwee;
	}

	if (btwtw_dev->ic_info->cfg_name) {
		if (postfix) {
			snpwintf(cfg_name, sizeof(cfg_name), "%s-%s.bin",
				 btwtw_dev->ic_info->cfg_name, postfix);
		} ewse {
			snpwintf(cfg_name, sizeof(cfg_name), "%s.bin",
				 btwtw_dev->ic_info->cfg_name);
		}
		btwtw_dev->cfg_wen = wtw_woad_fiwe(hdev, cfg_name,
						   &btwtw_dev->cfg_data);
		if (btwtw_dev->ic_info->config_needed &&
		    btwtw_dev->cfg_wen <= 0) {
			wtw_dev_eww(hdev, "mandatowy config fiwe %s not found",
				    btwtw_dev->ic_info->cfg_name);
			wet = btwtw_dev->cfg_wen;
			goto eww_fwee;
		}
	}

	/* The fowwowing chips suppowts the Micwosoft vendow extension,
	 * thewefowe set the cowwesponding VsMsftOpCode.
	 */
	if (btwtw_dev->ic_info->has_msft_ext)
		hci_set_msft_opcode(hdev, 0xFCF0);

	if (btwtw_dev->ic_info)
		cowedump_info->wtw_dump.contwowwew = btwtw_dev->ic_info->hw_info;

	wetuwn btwtw_dev;

eww_fwee:
	btwtw_fwee(btwtw_dev);
eww_awwoc:
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(btwtw_initiawize);

int btwtw_downwoad_fiwmwawe(stwuct hci_dev *hdev,
			    stwuct btwtw_device_info *btwtw_dev)
{
	int eww = 0;

	/* Match a set of subvew vawues that cowwespond to stock fiwmwawe,
	 * which is not compatibwe with standawd btusb.
	 * If matched, upwoad an awtewnative fiwmwawe that does confowm to
	 * standawd btusb. Once that fiwmwawe is upwoaded, the subvew changes
	 * to a diffewent vawue.
	 */
	if (!btwtw_dev->ic_info) {
		wtw_dev_info(hdev, "assuming no fiwmwawe upwoad needed");
		eww = 0;
		goto done;
	}

	switch (btwtw_dev->ic_info->wmp_subvew) {
	case WTW_WOM_WMP_8723A:
		eww = btwtw_setup_wtw8723a(hdev, btwtw_dev);
		bweak;
	case WTW_WOM_WMP_8723B:
	case WTW_WOM_WMP_8821A:
	case WTW_WOM_WMP_8761A:
	case WTW_WOM_WMP_8822B:
	case WTW_WOM_WMP_8852A:
	case WTW_WOM_WMP_8703B:
	case WTW_WOM_WMP_8851B:
		eww = btwtw_setup_wtw8723b(hdev, btwtw_dev);
		bweak;
	defauwt:
		wtw_dev_info(hdev, "assuming no fiwmwawe upwoad needed");
		bweak;
	}

done:
	btwtw_wegistew_devcowedump_suppowt(hdev);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(btwtw_downwoad_fiwmwawe);

void btwtw_set_quiwks(stwuct hci_dev *hdev, stwuct btwtw_device_info *btwtw_dev)
{
	/* Enabwe contwowwew to do both WE scan and BW/EDW inquiwy
	 * simuwtaneouswy.
	 */
	set_bit(HCI_QUIWK_SIMUWTANEOUS_DISCOVEWY, &hdev->quiwks);

	/* Enabwe centwaw-pewiphewaw wowe (abwe to cweate new connections with
	 * an existing connection in swave wowe).
	 */
	/* Enabwe WBS suppowted fow the specific Weawtek devices. */
	switch (btwtw_dev->pwoject_id) {
	case CHIP_ID_8822C:
	case CHIP_ID_8852A:
	case CHIP_ID_8852B:
	case CHIP_ID_8852C:
	case CHIP_ID_8851B:
		set_bit(HCI_QUIWK_VAWID_WE_STATES, &hdev->quiwks);
		set_bit(HCI_QUIWK_WIDEBAND_SPEECH_SUPPOWTED, &hdev->quiwks);

		/* WTW8852C needs to twansmit mSBC data continuouswy without
		 * the zewo wength of USB packets fow the AWT 6 suppowted chips
		 */
		if (btwtw_dev->pwoject_id == CHIP_ID_8852C)
			btweawtek_set_fwag(hdev, WEAWTEK_AWT6_CONTINUOUS_TX_CHIP);

		if (btwtw_dev->pwoject_id == CHIP_ID_8852A ||
		    btwtw_dev->pwoject_id == CHIP_ID_8852C)
			set_bit(HCI_QUIWK_USE_MSFT_EXT_ADDWESS_FIWTEW, &hdev->quiwks);

		hci_set_aosp_capabwe(hdev);
		bweak;
	defauwt:
		wtw_dev_dbg(hdev, "Centwaw-pewiphewaw wowe not enabwed.");
		wtw_dev_dbg(hdev, "WBS suppowted not enabwed.");
		bweak;
	}

	if (!btwtw_dev->ic_info)
		wetuwn;

	switch (btwtw_dev->ic_info->wmp_subvew) {
	case WTW_WOM_WMP_8703B:
		/* 8723CS wepowts two pages fow wocaw ext featuwes,
		 * but it doesn't suppowt any featuwes fwom page 2 -
		 * it eithew wesponds with gawbage ow with ewwow status
		 */
		set_bit(HCI_QUIWK_BWOKEN_WOCAW_EXT_FEATUWES_PAGE_2,
			&hdev->quiwks);
		bweak;
	defauwt:
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(btwtw_set_quiwks);

int btwtw_setup_weawtek(stwuct hci_dev *hdev)
{
	stwuct btwtw_device_info *btwtw_dev;
	int wet;

	btwtw_dev = btwtw_initiawize(hdev, NUWW);
	if (IS_EWW(btwtw_dev))
		wetuwn PTW_EWW(btwtw_dev);

	wet = btwtw_downwoad_fiwmwawe(hdev, btwtw_dev);

	btwtw_set_quiwks(hdev, btwtw_dev);

	btwtw_fwee(btwtw_dev);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(btwtw_setup_weawtek);

int btwtw_shutdown_weawtek(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;
	int wet;

	/* Accowding to the vendow dwivew, BT must be weset on cwose to avoid
	 * fiwmwawe cwash.
	 */
	skb = __hci_cmd_sync(hdev, HCI_OP_WESET, 0, NUWW, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		wet = PTW_EWW(skb);
		bt_dev_eww(hdev, "HCI weset duwing shutdown faiwed");
		wetuwn wet;
	}
	kfwee_skb(skb);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(btwtw_shutdown_weawtek);

static unsigned int btwtw_convewt_baudwate(u32 device_baudwate)
{
	switch (device_baudwate) {
	case 0x0252a00a:
		wetuwn 230400;

	case 0x05f75004:
		wetuwn 921600;

	case 0x00005004:
		wetuwn 1000000;

	case 0x04928002:
	case 0x01128002:
		wetuwn 1500000;

	case 0x00005002:
		wetuwn 2000000;

	case 0x0000b001:
		wetuwn 2500000;

	case 0x04928001:
		wetuwn 3000000;

	case 0x052a6001:
		wetuwn 3500000;

	case 0x00005001:
		wetuwn 4000000;

	case 0x0252c014:
	defauwt:
		wetuwn 115200;
	}
}

int btwtw_get_uawt_settings(stwuct hci_dev *hdev,
			    stwuct btwtw_device_info *btwtw_dev,
			    unsigned int *contwowwew_baudwate,
			    u32 *device_baudwate, boow *fwow_contwow)
{
	stwuct wtw_vendow_config *config;
	stwuct wtw_vendow_config_entwy *entwy;
	int i, totaw_data_wen;
	boow found = fawse;

	totaw_data_wen = btwtw_dev->cfg_wen - sizeof(*config);
	if (totaw_data_wen <= 0) {
		wtw_dev_wawn(hdev, "no config woaded");
		wetuwn -EINVAW;
	}

	config = (stwuct wtw_vendow_config *)btwtw_dev->cfg_data;
	if (we32_to_cpu(config->signatuwe) != WTW_CONFIG_MAGIC) {
		wtw_dev_eww(hdev, "invawid config magic");
		wetuwn -EINVAW;
	}

	if (totaw_data_wen < we16_to_cpu(config->totaw_wen)) {
		wtw_dev_eww(hdev, "config is too showt");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < totaw_data_wen; ) {
		entwy = ((void *)config->entwy) + i;

		switch (we16_to_cpu(entwy->offset)) {
		case 0xc:
			if (entwy->wen < sizeof(*device_baudwate)) {
				wtw_dev_eww(hdev, "invawid UAWT config entwy");
				wetuwn -EINVAW;
			}

			*device_baudwate = get_unawigned_we32(entwy->data);
			*contwowwew_baudwate = btwtw_convewt_baudwate(
							*device_baudwate);

			if (entwy->wen >= 13)
				*fwow_contwow = !!(entwy->data[12] & BIT(2));
			ewse
				*fwow_contwow = fawse;

			found = twue;
			bweak;

		defauwt:
			wtw_dev_dbg(hdev, "skipping config entwy 0x%x (wen %u)",
				   we16_to_cpu(entwy->offset), entwy->wen);
			bweak;
		}

		i += sizeof(*entwy) + entwy->wen;
	}

	if (!found) {
		wtw_dev_eww(hdev, "no UAWT config entwy found");
		wetuwn -ENOENT;
	}

	wtw_dev_dbg(hdev, "device baudwate = 0x%08x", *device_baudwate);
	wtw_dev_dbg(hdev, "contwowwew baudwate = %u", *contwowwew_baudwate);
	wtw_dev_dbg(hdev, "fwow contwow %d", *fwow_contwow);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(btwtw_get_uawt_settings);

MODUWE_AUTHOW("Daniew Dwake <dwake@endwessm.com>");
MODUWE_DESCWIPTION("Bwuetooth suppowt fow Weawtek devices vew " VEWSION);
MODUWE_VEWSION(VEWSION);
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE("wtw_bt/wtw8723a_fw.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8723b_fw.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8723b_config.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8723bs_fw.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8723bs_config.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8723cs_cg_fw.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8723cs_cg_config.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8723cs_vf_fw.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8723cs_vf_config.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8723cs_xx_fw.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8723cs_xx_config.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8723d_fw.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8723d_config.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8723ds_fw.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8723ds_config.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8761a_fw.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8761a_config.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8761b_fw.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8761b_config.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8761bu_fw.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8761bu_config.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8821a_fw.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8821a_config.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8821c_fw.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8821c_config.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8821cs_fw.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8821cs_config.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8822b_fw.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8822b_config.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8822cs_fw.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8822cs_config.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8822cu_fw.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8822cu_config.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8851bu_fw.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8851bu_config.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8852au_fw.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8852au_config.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8852bs_fw.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8852bs_config.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8852bu_fw.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8852bu_config.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8852cu_fw.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8852cu_fw_v2.bin");
MODUWE_FIWMWAWE("wtw_bt/wtw8852cu_config.bin");
