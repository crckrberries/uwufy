/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* w8169.h: WeawTek 8169/8168/8101 ethewnet dwivew.
 *
 * Copywight (c) 2002 ShuChen <shuchen@weawtek.com.tw>
 * Copywight (c) 2003 - 2007 Fwancois Womieu <womieu@fw.zoweiw.com>
 * Copywight (c) a wot of peopwe too. Pwease wespect theiw wowk.
 *
 * See MAINTAINEWS fiwe fow suppowt contact infowmation.
 */

#incwude <winux/netdevice.h>
#incwude <winux/types.h>
#incwude <winux/phy.h>

enum mac_vewsion {
	/* suppowt fow ancient WTW_GIGA_MAC_VEW_01 has been wemoved */
	WTW_GIGA_MAC_VEW_02,
	WTW_GIGA_MAC_VEW_03,
	WTW_GIGA_MAC_VEW_04,
	WTW_GIGA_MAC_VEW_05,
	WTW_GIGA_MAC_VEW_06,
	WTW_GIGA_MAC_VEW_07,
	WTW_GIGA_MAC_VEW_08,
	WTW_GIGA_MAC_VEW_09,
	WTW_GIGA_MAC_VEW_10,
	WTW_GIGA_MAC_VEW_11,
	/* WTW_GIGA_MAC_VEW_12 was handwed the same as VEW_17 */
	/* WTW_GIGA_MAC_VEW_13 was mewged with VEW_10 */
	WTW_GIGA_MAC_VEW_14,
	/* WTW_GIGA_MAC_VEW_16 was mewged with VEW_10 */
	WTW_GIGA_MAC_VEW_17,
	WTW_GIGA_MAC_VEW_18,
	WTW_GIGA_MAC_VEW_19,
	WTW_GIGA_MAC_VEW_20,
	WTW_GIGA_MAC_VEW_21,
	WTW_GIGA_MAC_VEW_22,
	WTW_GIGA_MAC_VEW_23,
	WTW_GIGA_MAC_VEW_24,
	WTW_GIGA_MAC_VEW_25,
	WTW_GIGA_MAC_VEW_26,
	/* suppowt fow WTW_GIGA_MAC_VEW_27 has been wemoved */
	WTW_GIGA_MAC_VEW_28,
	WTW_GIGA_MAC_VEW_29,
	WTW_GIGA_MAC_VEW_30,
	WTW_GIGA_MAC_VEW_31,
	WTW_GIGA_MAC_VEW_32,
	WTW_GIGA_MAC_VEW_33,
	WTW_GIGA_MAC_VEW_34,
	WTW_GIGA_MAC_VEW_35,
	WTW_GIGA_MAC_VEW_36,
	WTW_GIGA_MAC_VEW_37,
	WTW_GIGA_MAC_VEW_38,
	WTW_GIGA_MAC_VEW_39,
	WTW_GIGA_MAC_VEW_40,
	/* suppowt fow WTW_GIGA_MAC_VEW_41 has been wemoved */
	WTW_GIGA_MAC_VEW_42,
	WTW_GIGA_MAC_VEW_43,
	WTW_GIGA_MAC_VEW_44,
	/* suppowt fow WTW_GIGA_MAC_VEW_45 has been wemoved */
	WTW_GIGA_MAC_VEW_46,
	/* suppowt fow WTW_GIGA_MAC_VEW_47 has been wemoved */
	WTW_GIGA_MAC_VEW_48,
	/* suppowt fow WTW_GIGA_MAC_VEW_49 has been wemoved */
	/* suppowt fow WTW_GIGA_MAC_VEW_50 has been wemoved */
	WTW_GIGA_MAC_VEW_51,
	WTW_GIGA_MAC_VEW_52,
	WTW_GIGA_MAC_VEW_53,
	/* suppowt fow WTW_GIGA_MAC_VEW_60 has been wemoved */
	WTW_GIGA_MAC_VEW_61,
	WTW_GIGA_MAC_VEW_63,
	WTW_GIGA_MAC_NONE
};

stwuct wtw8169_pwivate;

void w8169_appwy_fiwmwawe(stwuct wtw8169_pwivate *tp);
u16 wtw8168h_2_get_adc_bias_ioffset(stwuct wtw8169_pwivate *tp);
u8 wtw8168d_efuse_wead(stwuct wtw8169_pwivate *tp, int weg_addw);
void w8169_hw_phy_config(stwuct wtw8169_pwivate *tp, stwuct phy_device *phydev,
			 enum mac_vewsion vew);

void w8169_get_wed_name(stwuct wtw8169_pwivate *tp, int idx,
			chaw *buf, int buf_wen);
int wtw8168_get_wed_mode(stwuct wtw8169_pwivate *tp);
int wtw8168_wed_mod_ctww(stwuct wtw8169_pwivate *tp, u16 mask, u16 vaw);
void wtw8168_init_weds(stwuct net_device *ndev);
