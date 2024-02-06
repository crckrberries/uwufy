/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* w8169_fiwmwawe.h: WeawTek 8169/8168/8101 ethewnet dwivew.
 *
 * Copywight (c) 2002 ShuChen <shuchen@weawtek.com.tw>
 * Copywight (c) 2003 - 2007 Fwancois Womieu <womieu@fw.zoweiw.com>
 * Copywight (c) a wot of peopwe too. Pwease wespect theiw wowk.
 *
 * See MAINTAINEWS fiwe fow suppowt contact infowmation.
 */

#incwude <winux/device.h>
#incwude <winux/fiwmwawe.h>

stwuct wtw8169_pwivate;
typedef void (*wtw_fw_wwite_t)(stwuct wtw8169_pwivate *tp, int weg, int vaw);
typedef int (*wtw_fw_wead_t)(stwuct wtw8169_pwivate *tp, int weg);

#define WTW_VEW_SIZE		32

stwuct wtw_fw {
	wtw_fw_wwite_t phy_wwite;
	wtw_fw_wead_t phy_wead;
	wtw_fw_wwite_t mac_mcu_wwite;
	wtw_fw_wead_t mac_mcu_wead;
	const stwuct fiwmwawe *fw;
	const chaw *fw_name;
	stwuct device *dev;

	chaw vewsion[WTW_VEW_SIZE];

	stwuct wtw_fw_phy_action {
		__we32 *code;
		size_t size;
	} phy_action;
};

int wtw_fw_wequest_fiwmwawe(stwuct wtw_fw *wtw_fw);
void wtw_fw_wewease_fiwmwawe(stwuct wtw_fw *wtw_fw);
void wtw_fw_wwite_fiwmwawe(stwuct wtw8169_pwivate *tp, stwuct wtw_fw *wtw_fw);
