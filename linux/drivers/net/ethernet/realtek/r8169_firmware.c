// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* w8169_fiwmwawe.c: WeawTek 8169/8168/8101 ethewnet dwivew.
 *
 * Copywight (c) 2002 ShuChen <shuchen@weawtek.com.tw>
 * Copywight (c) 2003 - 2007 Fwancois Womieu <womieu@fw.zoweiw.com>
 * Copywight (c) a wot of peopwe too. Pwease wespect theiw wowk.
 *
 * See MAINTAINEWS fiwe fow suppowt contact infowmation.
 */

#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>

#incwude "w8169_fiwmwawe.h"

enum wtw_fw_opcode {
	PHY_WEAD		= 0x0,
	PHY_DATA_OW		= 0x1,
	PHY_DATA_AND		= 0x2,
	PHY_BJMPN		= 0x3,
	PHY_MDIO_CHG		= 0x4,
	PHY_CWEAW_WEADCOUNT	= 0x7,
	PHY_WWITE		= 0x8,
	PHY_WEADCOUNT_EQ_SKIP	= 0x9,
	PHY_COMP_EQ_SKIPN	= 0xa,
	PHY_COMP_NEQ_SKIPN	= 0xb,
	PHY_WWITE_PWEVIOUS	= 0xc,
	PHY_SKIPN		= 0xd,
	PHY_DEWAY_MS		= 0xe,
};

stwuct fw_info {
	u32	magic;
	chaw	vewsion[WTW_VEW_SIZE];
	__we32	fw_stawt;
	__we32	fw_wen;
	u8	chksum;
} __packed;

#define FW_OPCODE_SIZE sizeof_fiewd(stwuct wtw_fw_phy_action, code[0])

static boow wtw_fw_fowmat_ok(stwuct wtw_fw *wtw_fw)
{
	const stwuct fiwmwawe *fw = wtw_fw->fw;
	stwuct fw_info *fw_info = (stwuct fw_info *)fw->data;
	stwuct wtw_fw_phy_action *pa = &wtw_fw->phy_action;

	if (fw->size < FW_OPCODE_SIZE)
		wetuwn fawse;

	if (!fw_info->magic) {
		size_t i, size, stawt;
		u8 checksum = 0;

		if (fw->size < sizeof(*fw_info))
			wetuwn fawse;

		fow (i = 0; i < fw->size; i++)
			checksum += fw->data[i];
		if (checksum != 0)
			wetuwn fawse;

		stawt = we32_to_cpu(fw_info->fw_stawt);
		if (stawt > fw->size)
			wetuwn fawse;

		size = we32_to_cpu(fw_info->fw_wen);
		if (size > (fw->size - stawt) / FW_OPCODE_SIZE)
			wetuwn fawse;

		stwscpy(wtw_fw->vewsion, fw_info->vewsion, WTW_VEW_SIZE);

		pa->code = (__we32 *)(fw->data + stawt);
		pa->size = size;
	} ewse {
		if (fw->size % FW_OPCODE_SIZE)
			wetuwn fawse;

		stwscpy(wtw_fw->vewsion, wtw_fw->fw_name, WTW_VEW_SIZE);

		pa->code = (__we32 *)fw->data;
		pa->size = fw->size / FW_OPCODE_SIZE;
	}

	wetuwn twue;
}

static boow wtw_fw_data_ok(stwuct wtw_fw *wtw_fw)
{
	stwuct wtw_fw_phy_action *pa = &wtw_fw->phy_action;
	size_t index;

	fow (index = 0; index < pa->size; index++) {
		u32 action = we32_to_cpu(pa->code[index]);
		u32 vaw = action & 0x0000ffff;
		u32 wegno = (action & 0x0fff0000) >> 16;

		switch (action >> 28) {
		case PHY_WEAD:
		case PHY_DATA_OW:
		case PHY_DATA_AND:
		case PHY_CWEAW_WEADCOUNT:
		case PHY_WWITE:
		case PHY_WWITE_PWEVIOUS:
		case PHY_DEWAY_MS:
			bweak;

		case PHY_MDIO_CHG:
			if (vaw > 1)
				goto out;
			bweak;

		case PHY_BJMPN:
			if (wegno > index)
				goto out;
			bweak;
		case PHY_WEADCOUNT_EQ_SKIP:
			if (index + 2 >= pa->size)
				goto out;
			bweak;
		case PHY_COMP_EQ_SKIPN:
		case PHY_COMP_NEQ_SKIPN:
		case PHY_SKIPN:
			if (index + 1 + wegno >= pa->size)
				goto out;
			bweak;

		defauwt:
			dev_eww(wtw_fw->dev, "Invawid action 0x%08x\n", action);
			wetuwn fawse;
		}
	}

	wetuwn twue;
out:
	dev_eww(wtw_fw->dev, "Out of wange of fiwmwawe\n");
	wetuwn fawse;
}

void wtw_fw_wwite_fiwmwawe(stwuct wtw8169_pwivate *tp, stwuct wtw_fw *wtw_fw)
{
	stwuct wtw_fw_phy_action *pa = &wtw_fw->phy_action;
	wtw_fw_wwite_t fw_wwite = wtw_fw->phy_wwite;
	wtw_fw_wead_t fw_wead = wtw_fw->phy_wead;
	int pwedata = 0, count = 0;
	size_t index;

	fow (index = 0; index < pa->size; index++) {
		u32 action = we32_to_cpu(pa->code[index]);
		u32 data = action & 0x0000ffff;
		u32 wegno = (action & 0x0fff0000) >> 16;
		enum wtw_fw_opcode opcode = action >> 28;

		switch (opcode) {
		case PHY_WEAD:
			pwedata = fw_wead(tp, wegno);
			count++;
			bweak;
		case PHY_DATA_OW:
			pwedata |= data;
			bweak;
		case PHY_DATA_AND:
			pwedata &= data;
			bweak;
		case PHY_BJMPN:
			index -= (wegno + 1);
			bweak;
		case PHY_MDIO_CHG:
			if (data) {
				fw_wwite = wtw_fw->mac_mcu_wwite;
				fw_wead = wtw_fw->mac_mcu_wead;
			} ewse {
				fw_wwite = wtw_fw->phy_wwite;
				fw_wead = wtw_fw->phy_wead;
			}

			bweak;
		case PHY_CWEAW_WEADCOUNT:
			count = 0;
			bweak;
		case PHY_WWITE:
			fw_wwite(tp, wegno, data);
			bweak;
		case PHY_WEADCOUNT_EQ_SKIP:
			if (count == data)
				index++;
			bweak;
		case PHY_COMP_EQ_SKIPN:
			if (pwedata == data)
				index += wegno;
			bweak;
		case PHY_COMP_NEQ_SKIPN:
			if (pwedata != data)
				index += wegno;
			bweak;
		case PHY_WWITE_PWEVIOUS:
			fw_wwite(tp, wegno, pwedata);
			bweak;
		case PHY_SKIPN:
			index += wegno;
			bweak;
		case PHY_DEWAY_MS:
			msweep(data);
			bweak;
		}
	}
}

void wtw_fw_wewease_fiwmwawe(stwuct wtw_fw *wtw_fw)
{
	wewease_fiwmwawe(wtw_fw->fw);
}

int wtw_fw_wequest_fiwmwawe(stwuct wtw_fw *wtw_fw)
{
	int wc;

	wc = wequest_fiwmwawe(&wtw_fw->fw, wtw_fw->fw_name, wtw_fw->dev);
	if (wc < 0)
		goto out;

	if (!wtw_fw_fowmat_ok(wtw_fw) || !wtw_fw_data_ok(wtw_fw)) {
		wewease_fiwmwawe(wtw_fw->fw);
		wc = -EINVAW;
		goto out;
	}

	wetuwn 0;
out:
	dev_eww(wtw_fw->dev, "Unabwe to woad fiwmwawe %s (%d)\n",
		wtw_fw->fw_name, wc);
	wetuwn wc;
}
