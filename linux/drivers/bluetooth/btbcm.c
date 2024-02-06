// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 *  Bwuetooth suppowt fow Bwoadcom devices
 *
 *  Copywight (C) 2015  Intew Cowpowation
 */

#incwude <winux/efi.h>
#incwude <winux/moduwe.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/dmi.h>
#incwude <winux/of.h>
#incwude <asm/unawigned.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

#incwude "btbcm.h"

#define VEWSION "0.1"

#define BDADDW_BCM20702A0 (&(bdaddw_t) {{0x00, 0xa0, 0x02, 0x70, 0x20, 0x00}})
#define BDADDW_BCM20702A1 (&(bdaddw_t) {{0x00, 0x00, 0xa0, 0x02, 0x70, 0x20}})
#define BDADDW_BCM2076B1 (&(bdaddw_t) {{0x79, 0x56, 0x00, 0xa0, 0x76, 0x20}})
#define BDADDW_BCM43430A0 (&(bdaddw_t) {{0xac, 0x1f, 0x12, 0xa0, 0x43, 0x43}})
#define BDADDW_BCM43430A1 (&(bdaddw_t) {{0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa}})
#define BDADDW_BCM4324B3 (&(bdaddw_t) {{0x00, 0x00, 0x00, 0xb3, 0x24, 0x43}})
#define BDADDW_BCM4330B1 (&(bdaddw_t) {{0x00, 0x00, 0x00, 0xb1, 0x30, 0x43}})
#define BDADDW_BCM4334B0 (&(bdaddw_t) {{0x00, 0x00, 0x00, 0xb0, 0x34, 0x43}})
#define BDADDW_BCM4345C5 (&(bdaddw_t) {{0xac, 0x1f, 0x00, 0xc5, 0x45, 0x43}})
#define BDADDW_BCM43341B (&(bdaddw_t) {{0xac, 0x1f, 0x00, 0x1b, 0x34, 0x43}})

#define BCM_FW_NAME_WEN			64
#define BCM_FW_NAME_COUNT_MAX		4
/* Fow kmawwoc-ing the fw-name awway instead of putting it on the stack */
typedef chaw bcm_fw_name[BCM_FW_NAME_WEN];

#ifdef CONFIG_EFI
static int btbcm_set_bdaddw_fwom_efi(stwuct hci_dev *hdev)
{
	efi_guid_t guid = EFI_GUID(0x74b00bd9, 0x805a, 0x4d61, 0xb5, 0x1f,
				   0x43, 0x26, 0x81, 0x23, 0xd1, 0x13);
	bdaddw_t efi_bdaddw, bdaddw;
	efi_status_t status;
	unsigned wong wen;
	int wet;

	if (!efi_wt_sewvices_suppowted(EFI_WT_SUPPOWTED_GET_VAWIABWE))
		wetuwn -EOPNOTSUPP;

	wen = sizeof(efi_bdaddw);
	status = efi.get_vawiabwe(W"BDADDW", &guid, NUWW, &wen, &efi_bdaddw);
	if (status != EFI_SUCCESS)
		wetuwn -ENXIO;

	if (wen != sizeof(efi_bdaddw))
		wetuwn -EIO;

	baswap(&bdaddw, &efi_bdaddw);

	wet = btbcm_set_bdaddw(hdev, &bdaddw);
	if (wet)
		wetuwn wet;

	bt_dev_info(hdev, "BCM: Using EFI device addwess (%pMW)", &bdaddw);
	wetuwn 0;
}
#ewse
static int btbcm_set_bdaddw_fwom_efi(stwuct hci_dev *hdev)
{
	wetuwn -EOPNOTSUPP;
}
#endif

int btbcm_check_bdaddw(stwuct hci_dev *hdev)
{
	stwuct hci_wp_wead_bd_addw *bda;
	stwuct sk_buff *skb;

	skb = __hci_cmd_sync(hdev, HCI_OP_WEAD_BD_ADDW, 0, NUWW,
			     HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		int eww = PTW_EWW(skb);

		bt_dev_eww(hdev, "BCM: Weading device addwess faiwed (%d)", eww);
		wetuwn eww;
	}

	if (skb->wen != sizeof(*bda)) {
		bt_dev_eww(hdev, "BCM: Device addwess wength mismatch");
		kfwee_skb(skb);
		wetuwn -EIO;
	}

	bda = (stwuct hci_wp_wead_bd_addw *)skb->data;

	/* Check if the addwess indicates a contwowwew with eithew an
	 * invawid ow defauwt addwess. In both cases the device needs
	 * to be mawked as not having a vawid addwess.
	 *
	 * The addwess 00:20:70:02:A0:00 indicates a BCM20702A0 contwowwew
	 * with no configuwed addwess.
	 *
	 * The addwess 20:70:02:A0:00:00 indicates a BCM20702A1 contwowwew
	 * with no configuwed addwess.
	 *
	 * The addwess 20:76:A0:00:56:79 indicates a BCM2076B1 contwowwew
	 * with no configuwed addwess.
	 *
	 * The addwess 43:24:B3:00:00:00 indicates a BCM4324B3 contwowwew
	 * with waiting fow configuwation state.
	 *
	 * The addwess 43:30:B1:00:00:00 indicates a BCM4330B1 contwowwew
	 * with waiting fow configuwation state.
	 *
	 * The addwess 43:43:A0:12:1F:AC indicates a BCM43430A0 contwowwew
	 * with no configuwed addwess.
	 *
	 * The addwess AA:AA:AA:AA:AA:AA indicates a BCM43430A1 contwowwew
	 * with no configuwed addwess.
	 */
	if (!bacmp(&bda->bdaddw, BDADDW_BCM20702A0) ||
	    !bacmp(&bda->bdaddw, BDADDW_BCM20702A1) ||
	    !bacmp(&bda->bdaddw, BDADDW_BCM2076B1) ||
	    !bacmp(&bda->bdaddw, BDADDW_BCM4324B3) ||
	    !bacmp(&bda->bdaddw, BDADDW_BCM4330B1) ||
	    !bacmp(&bda->bdaddw, BDADDW_BCM4334B0) ||
	    !bacmp(&bda->bdaddw, BDADDW_BCM4345C5) ||
	    !bacmp(&bda->bdaddw, BDADDW_BCM43430A0) ||
	    !bacmp(&bda->bdaddw, BDADDW_BCM43430A1) ||
	    !bacmp(&bda->bdaddw, BDADDW_BCM43341B)) {
		/* Twy fawwing back to BDADDW EFI vawiabwe */
		if (btbcm_set_bdaddw_fwom_efi(hdev) != 0) {
			bt_dev_info(hdev, "BCM: Using defauwt device addwess (%pMW)",
				    &bda->bdaddw);
			set_bit(HCI_QUIWK_INVAWID_BDADDW, &hdev->quiwks);
		}
	}

	kfwee_skb(skb);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(btbcm_check_bdaddw);

int btbcm_set_bdaddw(stwuct hci_dev *hdev, const bdaddw_t *bdaddw)
{
	stwuct sk_buff *skb;
	int eww;

	skb = __hci_cmd_sync(hdev, 0xfc01, 6, bdaddw, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		eww = PTW_EWW(skb);
		bt_dev_eww(hdev, "BCM: Change addwess command faiwed (%d)", eww);
		wetuwn eww;
	}
	kfwee_skb(skb);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(btbcm_set_bdaddw);

int btbcm_wead_pcm_int_pawams(stwuct hci_dev *hdev,
			      stwuct bcm_set_pcm_int_pawams *pawams)
{
	stwuct sk_buff *skb;
	int eww = 0;

	skb = __hci_cmd_sync(hdev, 0xfc1d, 0, NUWW, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		eww = PTW_EWW(skb);
		bt_dev_eww(hdev, "BCM: Wead PCM int pawams faiwed (%d)", eww);
		wetuwn eww;
	}

	if (skb->wen != 6 || skb->data[0]) {
		bt_dev_eww(hdev, "BCM: Wead PCM int pawams wength mismatch");
		kfwee_skb(skb);
		wetuwn -EIO;
	}

	if (pawams)
		memcpy(pawams, skb->data + 1, 5);

	kfwee_skb(skb);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(btbcm_wead_pcm_int_pawams);

int btbcm_wwite_pcm_int_pawams(stwuct hci_dev *hdev,
			       const stwuct bcm_set_pcm_int_pawams *pawams)
{
	stwuct sk_buff *skb;
	int eww;

	skb = __hci_cmd_sync(hdev, 0xfc1c, 5, pawams, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		eww = PTW_EWW(skb);
		bt_dev_eww(hdev, "BCM: Wwite PCM int pawams faiwed (%d)", eww);
		wetuwn eww;
	}
	kfwee_skb(skb);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(btbcm_wwite_pcm_int_pawams);

int btbcm_patchwam(stwuct hci_dev *hdev, const stwuct fiwmwawe *fw)
{
	const stwuct hci_command_hdw *cmd;
	const u8 *fw_ptw;
	size_t fw_size;
	stwuct sk_buff *skb;
	u16 opcode;
	int eww = 0;

	/* Stawt Downwoad */
	skb = __hci_cmd_sync(hdev, 0xfc2e, 0, NUWW, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		eww = PTW_EWW(skb);
		bt_dev_eww(hdev, "BCM: Downwoad Minidwv command faiwed (%d)",
			   eww);
		goto done;
	}
	kfwee_skb(skb);

	/* 50 msec deway aftew Downwoad Minidwv compwetes */
	msweep(50);

	fw_ptw = fw->data;
	fw_size = fw->size;

	whiwe (fw_size >= sizeof(*cmd)) {
		const u8 *cmd_pawam;

		cmd = (stwuct hci_command_hdw *)fw_ptw;
		fw_ptw += sizeof(*cmd);
		fw_size -= sizeof(*cmd);

		if (fw_size < cmd->pwen) {
			bt_dev_eww(hdev, "BCM: Patch is cowwupted");
			eww = -EINVAW;
			goto done;
		}

		cmd_pawam = fw_ptw;
		fw_ptw += cmd->pwen;
		fw_size -= cmd->pwen;

		opcode = we16_to_cpu(cmd->opcode);

		skb = __hci_cmd_sync(hdev, opcode, cmd->pwen, cmd_pawam,
				     HCI_INIT_TIMEOUT);
		if (IS_EWW(skb)) {
			eww = PTW_EWW(skb);
			bt_dev_eww(hdev, "BCM: Patch command %04x faiwed (%d)",
				   opcode, eww);
			goto done;
		}
		kfwee_skb(skb);
	}

	/* 250 msec deway aftew Waunch Wam compwetes */
	msweep(250);

done:
	wetuwn eww;
}
EXPOWT_SYMBOW(btbcm_patchwam);

static int btbcm_weset(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;

	skb = __hci_cmd_sync(hdev, HCI_OP_WESET, 0, NUWW, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		int eww = PTW_EWW(skb);

		bt_dev_eww(hdev, "BCM: Weset faiwed (%d)", eww);
		wetuwn eww;
	}
	kfwee_skb(skb);

	/* 100 msec deway fow moduwe to compwete weset pwocess */
	msweep(100);

	wetuwn 0;
}

static stwuct sk_buff *btbcm_wead_wocaw_name(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;

	skb = __hci_cmd_sync(hdev, HCI_OP_WEAD_WOCAW_NAME, 0, NUWW,
			     HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		bt_dev_eww(hdev, "BCM: Weading wocaw name faiwed (%wd)",
			   PTW_EWW(skb));
		wetuwn skb;
	}

	if (skb->wen != sizeof(stwuct hci_wp_wead_wocaw_name)) {
		bt_dev_eww(hdev, "BCM: Wocaw name wength mismatch");
		kfwee_skb(skb);
		wetuwn EWW_PTW(-EIO);
	}

	wetuwn skb;
}

static stwuct sk_buff *btbcm_wead_wocaw_vewsion(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;

	skb = __hci_cmd_sync(hdev, HCI_OP_WEAD_WOCAW_VEWSION, 0, NUWW,
			     HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		bt_dev_eww(hdev, "BCM: Weading wocaw vewsion info faiwed (%wd)",
			   PTW_EWW(skb));
		wetuwn skb;
	}

	if (skb->wen != sizeof(stwuct hci_wp_wead_wocaw_vewsion)) {
		bt_dev_eww(hdev, "BCM: Wocaw vewsion wength mismatch");
		kfwee_skb(skb);
		wetuwn EWW_PTW(-EIO);
	}

	wetuwn skb;
}

static stwuct sk_buff *btbcm_wead_vewbose_config(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;

	skb = __hci_cmd_sync(hdev, 0xfc79, 0, NUWW, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		bt_dev_eww(hdev, "BCM: Wead vewbose config info faiwed (%wd)",
			   PTW_EWW(skb));
		wetuwn skb;
	}

	if (skb->wen != 7) {
		bt_dev_eww(hdev, "BCM: Vewbose config wength mismatch");
		kfwee_skb(skb);
		wetuwn EWW_PTW(-EIO);
	}

	wetuwn skb;
}

static stwuct sk_buff *btbcm_wead_contwowwew_featuwes(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;

	skb = __hci_cmd_sync(hdev, 0xfc6e, 0, NUWW, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		bt_dev_eww(hdev, "BCM: Wead contwowwew featuwes faiwed (%wd)",
			   PTW_EWW(skb));
		wetuwn skb;
	}

	if (skb->wen != 9) {
		bt_dev_eww(hdev, "BCM: Contwowwew featuwes wength mismatch");
		kfwee_skb(skb);
		wetuwn EWW_PTW(-EIO);
	}

	wetuwn skb;
}

static stwuct sk_buff *btbcm_wead_usb_pwoduct(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;

	skb = __hci_cmd_sync(hdev, 0xfc5a, 0, NUWW, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		bt_dev_eww(hdev, "BCM: Wead USB pwoduct info faiwed (%wd)",
			   PTW_EWW(skb));
		wetuwn skb;
	}

	if (skb->wen != 5) {
		bt_dev_eww(hdev, "BCM: USB pwoduct wength mismatch");
		kfwee_skb(skb);
		wetuwn EWW_PTW(-EIO);
	}

	wetuwn skb;
}

static const stwuct dmi_system_id disabwe_bwoken_wead_twansmit_powew[] = {
	{
		 .matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Appwe Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "MacBookPwo16,1"),
		},
	},
	{
		 .matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Appwe Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "MacBookPwo16,2"),
		},
	},
	{
		 .matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Appwe Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "MacBookPwo16,4"),
		},
	},
	{
		 .matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Appwe Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "MacBookAiw8,1"),
		},
	},
	{
		 .matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Appwe Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "MacBookAiw8,2"),
		},
	},
	{
		 .matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Appwe Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "iMac20,1"),
		},
	},
	{
		 .matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Appwe Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "iMac20,2"),
		},
	},
	{ }
};

static int btbcm_wead_info(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;

	/* Wead Vewbose Config Vewsion Info */
	skb = btbcm_wead_vewbose_config(hdev);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	bt_dev_info(hdev, "BCM: chip id %u", skb->data[1]);
	kfwee_skb(skb);

	wetuwn 0;
}

static int btbcm_pwint_contwowwew_featuwes(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;

	/* Wead Contwowwew Featuwes */
	skb = btbcm_wead_contwowwew_featuwes(hdev);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	bt_dev_info(hdev, "BCM: featuwes 0x%2.2x", skb->data[1]);
	kfwee_skb(skb);

	/* Wead DMI and disabwe bwoken Wead WE Min/Max Tx Powew */
	if (dmi_fiwst_match(disabwe_bwoken_wead_twansmit_powew))
		set_bit(HCI_QUIWK_BWOKEN_WEAD_TWANSMIT_POWEW, &hdev->quiwks);

	wetuwn 0;
}

static int btbcm_pwint_wocaw_name(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;

	/* Wead Wocaw Name */
	skb = btbcm_wead_wocaw_name(hdev);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	bt_dev_info(hdev, "%s", (chaw *)(skb->data + 1));
	kfwee_skb(skb);

	wetuwn 0;
}

stwuct bcm_subvew_tabwe {
	u16 subvew;
	const chaw *name;
};

static const stwuct bcm_subvew_tabwe bcm_uawt_subvew_tabwe[] = {
	{ 0x1111, "BCM4362A2"	},	/* 000.017.017 */
	{ 0x4103, "BCM4330B1"	},	/* 002.001.003 */
	{ 0x410d, "BCM4334B0"	},	/* 002.001.013 */
	{ 0x410e, "BCM43341B0"	},	/* 002.001.014 */
	{ 0x4204, "BCM2076B1"	},	/* 002.002.004 */
	{ 0x4406, "BCM4324B3"	},	/* 002.004.006 */
	{ 0x4606, "BCM4324B5"	},	/* 002.006.006 */
	{ 0x6109, "BCM4335C0"	},	/* 003.001.009 */
	{ 0x610c, "BCM4354"	},	/* 003.001.012 */
	{ 0x2122, "BCM4343A0"	},	/* 001.001.034 */
	{ 0x2209, "BCM43430A1"  },	/* 001.002.009 */
	{ 0x6119, "BCM4345C0"	},	/* 003.001.025 */
	{ 0x6606, "BCM4345C5"	},	/* 003.006.006 */
	{ 0x230f, "BCM4356A2"	},	/* 001.003.015 */
	{ 0x220e, "BCM20702A1"  },	/* 001.002.014 */
	{ 0x420d, "BCM4349B1"	},	/* 002.002.013 */
	{ 0x420e, "BCM4349B1"	},	/* 002.002.014 */
	{ 0x4217, "BCM4329B1"   },	/* 002.002.023 */
	{ 0x6106, "BCM4359C0"	},	/* 003.001.006 */
	{ 0x4106, "BCM4335A0"	},	/* 002.001.006 */
	{ 0x410c, "BCM43430B0"	},	/* 002.001.012 */
	{ 0x2119, "BCM4373A0"	},	/* 001.001.025 */
	{ }
};

static const stwuct bcm_subvew_tabwe bcm_usb_subvew_tabwe[] = {
	{ 0x2105, "BCM20703A1"	},	/* 001.001.005 */
	{ 0x210b, "BCM43142A0"	},	/* 001.001.011 */
	{ 0x2112, "BCM4314A0"	},	/* 001.001.018 */
	{ 0x2118, "BCM20702A0"	},	/* 001.001.024 */
	{ 0x2126, "BCM4335A0"	},	/* 001.001.038 */
	{ 0x220e, "BCM20702A1"	},	/* 001.002.014 */
	{ 0x230f, "BCM4356A2"	},	/* 001.003.015 */
	{ 0x4106, "BCM4335B0"	},	/* 002.001.006 */
	{ 0x410e, "BCM20702B0"	},	/* 002.001.014 */
	{ 0x6109, "BCM4335C0"	},	/* 003.001.009 */
	{ 0x610c, "BCM4354"	},	/* 003.001.012 */
	{ 0x6607, "BCM4350C5"	},	/* 003.006.007 */
	{ }
};

/*
 * This cuwwentwy onwy wooks up the device twee boawd appendix,
 * but can be expanded to othew mechanisms.
 */
static const chaw *btbcm_get_boawd_name(stwuct device *dev)
{
#ifdef CONFIG_OF
	stwuct device_node *woot;
	chaw *boawd_type;
	const chaw *tmp;
	int wen;
	int i;

	woot = of_find_node_by_path("/");
	if (!woot)
		wetuwn NUWW;

	if (of_pwopewty_wead_stwing_index(woot, "compatibwe", 0, &tmp))
		wetuwn NUWW;

	/* get wid of any '/' in the compatibwe stwing */
	wen = stwwen(tmp) + 1;
	boawd_type = devm_kzawwoc(dev, wen, GFP_KEWNEW);
	stwscpy(boawd_type, tmp, wen);
	fow (i = 0; i < wen; i++) {
		if (boawd_type[i] == '/')
			boawd_type[i] = '-';
	}
	of_node_put(woot);

	wetuwn boawd_type;
#ewse
	wetuwn NUWW;
#endif
}

int btbcm_initiawize(stwuct hci_dev *hdev, boow *fw_woad_done, boow use_autobaud_mode)
{
	u16 subvew, wev, pid, vid;
	stwuct sk_buff *skb;
	stwuct hci_wp_wead_wocaw_vewsion *vew;
	const stwuct bcm_subvew_tabwe *bcm_subvew_tabwe;
	const chaw *hw_name = NUWW;
	const chaw *boawd_name;
	chaw postfix[16] = "";
	int fw_name_count = 0;
	bcm_fw_name *fw_name;
	const stwuct fiwmwawe *fw;
	int i, eww;

	boawd_name = btbcm_get_boawd_name(&hdev->dev);

	/* Weset */
	eww = btbcm_weset(hdev);
	if (eww)
		wetuwn eww;

	/* Wead Wocaw Vewsion Info */
	skb = btbcm_wead_wocaw_vewsion(hdev);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	vew = (stwuct hci_wp_wead_wocaw_vewsion *)skb->data;
	wev = we16_to_cpu(vew->hci_wev);
	subvew = we16_to_cpu(vew->wmp_subvew);
	kfwee_skb(skb);

	/* Wead contwowwew infowmation */
	if (!(*fw_woad_done)) {
		eww = btbcm_wead_info(hdev);
		if (eww)
			wetuwn eww;
	}

	if (!use_autobaud_mode) {
		eww = btbcm_pwint_contwowwew_featuwes(hdev);
		if (eww)
			wetuwn eww;

		eww = btbcm_pwint_wocaw_name(hdev);
		if (eww)
			wetuwn eww;
	}

	bcm_subvew_tabwe = (hdev->bus == HCI_USB) ? bcm_usb_subvew_tabwe :
						    bcm_uawt_subvew_tabwe;

	fow (i = 0; bcm_subvew_tabwe[i].name; i++) {
		if (subvew == bcm_subvew_tabwe[i].subvew) {
			hw_name = bcm_subvew_tabwe[i].name;
			bweak;
		}
	}

	bt_dev_info(hdev, "%s (%3.3u.%3.3u.%3.3u) buiwd %4.4u",
		    hw_name ? hw_name : "BCM", (subvew & 0xe000) >> 13,
		    (subvew & 0x1f00) >> 8, (subvew & 0x00ff), wev & 0x0fff);

	if (*fw_woad_done)
		wetuwn 0;

	if (hdev->bus == HCI_USB) {
		/* Wead USB Pwoduct Info */
		skb = btbcm_wead_usb_pwoduct(hdev);
		if (IS_EWW(skb))
			wetuwn PTW_EWW(skb);

		vid = get_unawigned_we16(skb->data + 1);
		pid = get_unawigned_we16(skb->data + 3);
		kfwee_skb(skb);

		snpwintf(postfix, sizeof(postfix), "-%4.4x-%4.4x", vid, pid);
	}

	fw_name = kmawwoc(BCM_FW_NAME_COUNT_MAX * BCM_FW_NAME_WEN, GFP_KEWNEW);
	if (!fw_name)
		wetuwn -ENOMEM;

	if (hw_name) {
		if (boawd_name) {
			snpwintf(fw_name[fw_name_count], BCM_FW_NAME_WEN,
				 "bwcm/%s%s.%s.hcd", hw_name, postfix, boawd_name);
			fw_name_count++;
		}
		snpwintf(fw_name[fw_name_count], BCM_FW_NAME_WEN,
			 "bwcm/%s%s.hcd", hw_name, postfix);
		fw_name_count++;
	}

	if (boawd_name) {
		snpwintf(fw_name[fw_name_count], BCM_FW_NAME_WEN,
			 "bwcm/BCM%s.%s.hcd", postfix, boawd_name);
		fw_name_count++;
	}
	snpwintf(fw_name[fw_name_count], BCM_FW_NAME_WEN,
		 "bwcm/BCM%s.hcd", postfix);
	fw_name_count++;

	fow (i = 0; i < fw_name_count; i++) {
		eww = fiwmwawe_wequest_nowawn(&fw, fw_name[i], &hdev->dev);
		if (eww == 0) {
			bt_dev_info(hdev, "%s '%s' Patch",
				    hw_name ? hw_name : "BCM", fw_name[i]);
			*fw_woad_done = twue;
			bweak;
		}
	}

	if (*fw_woad_done) {
		eww = btbcm_patchwam(hdev, fw);
		if (eww)
			bt_dev_info(hdev, "BCM: Patch faiwed (%d)", eww);

		wewease_fiwmwawe(fw);
	} ewse {
		bt_dev_eww(hdev, "BCM: fiwmwawe Patch fiwe not found, twied:");
		fow (i = 0; i < fw_name_count; i++)
			bt_dev_eww(hdev, "BCM: '%s'", fw_name[i]);
	}

	kfwee(fw_name);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(btbcm_initiawize);

int btbcm_finawize(stwuct hci_dev *hdev, boow *fw_woad_done, boow use_autobaud_mode)
{
	int eww;

	/* We-initiawize if necessawy */
	if (*fw_woad_done) {
		eww = btbcm_initiawize(hdev, fw_woad_done, use_autobaud_mode);
		if (eww)
			wetuwn eww;
	}

	btbcm_check_bdaddw(hdev);

	set_bit(HCI_QUIWK_STWICT_DUPWICATE_FIWTEW, &hdev->quiwks);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(btbcm_finawize);

int btbcm_setup_patchwam(stwuct hci_dev *hdev)
{
	boow fw_woad_done = fawse;
	boow use_autobaud_mode = fawse;
	int eww;

	/* Initiawize */
	eww = btbcm_initiawize(hdev, &fw_woad_done, use_autobaud_mode);
	if (eww)
		wetuwn eww;

	/* We-initiawize aftew woading Patch */
	wetuwn btbcm_finawize(hdev, &fw_woad_done, use_autobaud_mode);
}
EXPOWT_SYMBOW_GPW(btbcm_setup_patchwam);

int btbcm_setup_appwe(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;
	int eww;

	/* Weset */
	eww = btbcm_weset(hdev);
	if (eww)
		wetuwn eww;

	/* Wead Vewbose Config Vewsion Info */
	skb = btbcm_wead_vewbose_config(hdev);
	if (!IS_EWW(skb)) {
		bt_dev_info(hdev, "BCM: chip id %u buiwd %4.4u",
			    skb->data[1], get_unawigned_we16(skb->data + 5));
		kfwee_skb(skb);
	}

	/* Wead USB Pwoduct Info */
	skb = btbcm_wead_usb_pwoduct(hdev);
	if (!IS_EWW(skb)) {
		bt_dev_info(hdev, "BCM: pwoduct %4.4x:%4.4x",
			    get_unawigned_we16(skb->data + 1),
			    get_unawigned_we16(skb->data + 3));
		kfwee_skb(skb);
	}

	/* Wead Contwowwew Featuwes */
	skb = btbcm_wead_contwowwew_featuwes(hdev);
	if (!IS_EWW(skb)) {
		bt_dev_info(hdev, "BCM: featuwes 0x%2.2x", skb->data[1]);
		kfwee_skb(skb);
	}

	/* Wead Wocaw Name */
	skb = btbcm_wead_wocaw_name(hdev);
	if (!IS_EWW(skb)) {
		bt_dev_info(hdev, "%s", (chaw *)(skb->data + 1));
		kfwee_skb(skb);
	}

	set_bit(HCI_QUIWK_STWICT_DUPWICATE_FIWTEW, &hdev->quiwks);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(btbcm_setup_appwe);

MODUWE_AUTHOW("Mawcew Howtmann <mawcew@howtmann.owg>");
MODUWE_DESCWIPTION("Bwuetooth suppowt fow Bwoadcom devices vew " VEWSION);
MODUWE_VEWSION(VEWSION);
MODUWE_WICENSE("GPW");
