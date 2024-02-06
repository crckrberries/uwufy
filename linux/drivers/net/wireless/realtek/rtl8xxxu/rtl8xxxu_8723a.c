// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WTW8XXXU mac80211 USB dwivew - 8723a specific subdwivew
 *
 * Copywight (c) 2014 - 2017 Jes Sowensen <Jes.Sowensen@gmaiw.com>
 *
 * Powtions, notabwy cawibwation code:
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 * This dwivew was wwitten as a wepwacement fow the vendow pwovided
 * wtw8723au dwivew. As the Weawtek 8xxx chips awe vewy simiwaw in
 * theiw pwogwamming intewface, I have stawted adding suppowt fow
 * additionaw 8xxx chips wike the 8192cu, 8188cus, etc.
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/wist.h>
#incwude <winux/usb.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/wiwewess.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwepawam.h>
#incwude <net/mac80211.h>
#incwude "wtw8xxxu.h"
#incwude "wtw8xxxu_wegs.h"

static stwuct wtw8xxxu_powew_base wtw8723a_powew_base = {
	.weg_0e00 = 0x0a0c0c0c,
	.weg_0e04 = 0x02040608,
	.weg_0e08 = 0x00000000,
	.weg_086c = 0x00000000,

	.weg_0e10 = 0x0a0c0d0e,
	.weg_0e14 = 0x02040608,
	.weg_0e18 = 0x0a0c0d0e,
	.weg_0e1c = 0x02040608,

	.weg_0830 = 0x0a0c0c0c,
	.weg_0834 = 0x02040608,
	.weg_0838 = 0x00000000,
	.weg_086c_2 = 0x00000000,

	.weg_083c = 0x0a0c0d0e,
	.weg_0848 = 0x02040608,
	.weg_084c = 0x0a0c0d0e,
	.weg_0868 = 0x02040608,
};

static const stwuct wtw8xxxu_wfwegvaw wtw8723au_wadioa_1t_init_tabwe[] = {
	{0x00, 0x00030159}, {0x01, 0x00031284},
	{0x02, 0x00098000}, {0x03, 0x00039c63},
	{0x04, 0x000210e7}, {0x09, 0x0002044f},
	{0x0a, 0x0001a3f1}, {0x0b, 0x00014787},
	{0x0c, 0x000896fe}, {0x0d, 0x0000e02c},
	{0x0e, 0x00039ce7}, {0x0f, 0x00000451},
	{0x19, 0x00000000}, {0x1a, 0x00030355},
	{0x1b, 0x00060a00}, {0x1c, 0x000fc378},
	{0x1d, 0x000a1250}, {0x1e, 0x0000024f},
	{0x1f, 0x00000000}, {0x20, 0x0000b614},
	{0x21, 0x0006c000}, {0x22, 0x00000000},
	{0x23, 0x00001558}, {0x24, 0x00000060},
	{0x25, 0x00000483}, {0x26, 0x0004f000},
	{0x27, 0x000ec7d9}, {0x28, 0x00057730},
	{0x29, 0x00004783}, {0x2a, 0x00000001},
	{0x2b, 0x00021334}, {0x2a, 0x00000000},
	{0x2b, 0x00000054}, {0x2a, 0x00000001},
	{0x2b, 0x00000808}, {0x2b, 0x00053333},
	{0x2c, 0x0000000c}, {0x2a, 0x00000002},
	{0x2b, 0x00000808}, {0x2b, 0x0005b333},
	{0x2c, 0x0000000d}, {0x2a, 0x00000003},
	{0x2b, 0x00000808}, {0x2b, 0x00063333},
	{0x2c, 0x0000000d}, {0x2a, 0x00000004},
	{0x2b, 0x00000808}, {0x2b, 0x0006b333},
	{0x2c, 0x0000000d}, {0x2a, 0x00000005},
	{0x2b, 0x00000808}, {0x2b, 0x00073333},
	{0x2c, 0x0000000d}, {0x2a, 0x00000006},
	{0x2b, 0x00000709}, {0x2b, 0x0005b333},
	{0x2c, 0x0000000d}, {0x2a, 0x00000007},
	{0x2b, 0x00000709}, {0x2b, 0x00063333},
	{0x2c, 0x0000000d}, {0x2a, 0x00000008},
	{0x2b, 0x0000060a}, {0x2b, 0x0004b333},
	{0x2c, 0x0000000d}, {0x2a, 0x00000009},
	{0x2b, 0x0000060a}, {0x2b, 0x00053333},
	{0x2c, 0x0000000d}, {0x2a, 0x0000000a},
	{0x2b, 0x0000060a}, {0x2b, 0x0005b333},
	{0x2c, 0x0000000d}, {0x2a, 0x0000000b},
	{0x2b, 0x0000060a}, {0x2b, 0x00063333},
	{0x2c, 0x0000000d}, {0x2a, 0x0000000c},
	{0x2b, 0x0000060a}, {0x2b, 0x0006b333},
	{0x2c, 0x0000000d}, {0x2a, 0x0000000d},
	{0x2b, 0x0000060a}, {0x2b, 0x00073333},
	{0x2c, 0x0000000d}, {0x2a, 0x0000000e},
	{0x2b, 0x0000050b}, {0x2b, 0x00066666},
	{0x2c, 0x0000001a}, {0x2a, 0x000e0000},
	{0x10, 0x0004000f}, {0x11, 0x000e31fc},
	{0x10, 0x0006000f}, {0x11, 0x000ff9f8},
	{0x10, 0x0002000f}, {0x11, 0x000203f9},
	{0x10, 0x0003000f}, {0x11, 0x000ff500},
	{0x10, 0x00000000}, {0x11, 0x00000000},
	{0x10, 0x0008000f}, {0x11, 0x0003f100},
	{0x10, 0x0009000f}, {0x11, 0x00023100},
	{0x12, 0x00032000}, {0x12, 0x00071000},
	{0x12, 0x000b0000}, {0x12, 0x000fc000},
	{0x13, 0x000287b3}, {0x13, 0x000244b7},
	{0x13, 0x000204ab}, {0x13, 0x0001c49f},
	{0x13, 0x00018493}, {0x13, 0x0001429b},
	{0x13, 0x00010299}, {0x13, 0x0000c29c},
	{0x13, 0x000081a0}, {0x13, 0x000040ac},
	{0x13, 0x00000020}, {0x14, 0x0001944c},
	{0x14, 0x00059444}, {0x14, 0x0009944c},
	{0x14, 0x000d9444}, {0x15, 0x0000f474},
	{0x15, 0x0004f477}, {0x15, 0x0008f455},
	{0x15, 0x000cf455}, {0x16, 0x00000339},
	{0x16, 0x00040339}, {0x16, 0x00080339},
	{0x16, 0x000c0366}, {0x00, 0x00010159},
	{0x18, 0x0000f401}, {0xfe, 0x00000000},
	{0xfe, 0x00000000}, {0x1f, 0x00000003},
	{0xfe, 0x00000000}, {0xfe, 0x00000000},
	{0x1e, 0x00000247}, {0x1f, 0x00000000},
	{0x00, 0x00030159},
	{0xff, 0xffffffff}
};

static int wtw8723au_identify_chip(stwuct wtw8xxxu_pwiv *pwiv)
{
	stwuct device *dev = &pwiv->udev->dev;
	u32 vaw32, sys_cfg, vendow;
	int wet = 0;

	sys_cfg = wtw8xxxu_wead32(pwiv, WEG_SYS_CFG);
	pwiv->chip_cut = u32_get_bits(sys_cfg, SYS_CFG_CHIP_VEWSION_MASK);
	if (sys_cfg & SYS_CFG_TWP_VAUX_EN) {
		dev_info(dev, "Unsuppowted test chip\n");
		wet = -ENOTSUPP;
		goto out;
	}

	stwscpy(pwiv->chip_name, "8723AU", sizeof(pwiv->chip_name));
	pwiv->usb_intewwupts = 1;
	pwiv->wtw_chip = WTW8723A;

	pwiv->wf_paths = 1;
	pwiv->wx_paths = 1;
	pwiv->tx_paths = 1;

	vaw32 = wtw8xxxu_wead32(pwiv, WEG_MUWTI_FUNC_CTWW);
	if (vaw32 & MUWTI_WIFI_FUNC_EN)
		pwiv->has_wifi = 1;
	if (vaw32 & MUWTI_BT_FUNC_EN)
		pwiv->has_bwuetooth = 1;
	if (vaw32 & MUWTI_GPS_FUNC_EN)
		pwiv->has_gps = 1;
	pwiv->is_muwti_func = 1;

	vendow = sys_cfg & SYS_CFG_VENDOW_ID;
	wtw8xxxu_identify_vendow_1bit(pwiv, vendow);

	vaw32 = wtw8xxxu_wead32(pwiv, WEG_GPIO_OUTSTS);
	pwiv->wom_wev = u32_get_bits(vaw32, GPIO_WF_WW_ID);

	wtw8xxxu_config_endpoints_sie(pwiv);

	/*
	 * Fawwback fow devices that do not pwovide WEG_NOWMAW_SIE_EP_TX
	 */
	if (!pwiv->ep_tx_count)
		wet = wtw8xxxu_config_endpoints_no_sie(pwiv);

out:
	wetuwn wet;
}

static int wtw8723au_pawse_efuse(stwuct wtw8xxxu_pwiv *pwiv)
{
	stwuct wtw8723au_efuse *efuse = &pwiv->efuse_wifi.efuse8723;

	if (efuse->wtw_id != cpu_to_we16(0x8129))
		wetuwn -EINVAW;

	ethew_addw_copy(pwiv->mac_addw, efuse->mac_addw);

	memcpy(pwiv->cck_tx_powew_index_A,
	       efuse->cck_tx_powew_index_A,
	       sizeof(efuse->cck_tx_powew_index_A));
	memcpy(pwiv->cck_tx_powew_index_B,
	       efuse->cck_tx_powew_index_B,
	       sizeof(efuse->cck_tx_powew_index_B));

	memcpy(pwiv->ht40_1s_tx_powew_index_A,
	       efuse->ht40_1s_tx_powew_index_A,
	       sizeof(efuse->ht40_1s_tx_powew_index_A));
	memcpy(pwiv->ht40_1s_tx_powew_index_B,
	       efuse->ht40_1s_tx_powew_index_B,
	       sizeof(efuse->ht40_1s_tx_powew_index_B));

	memcpy(pwiv->ht20_tx_powew_index_diff,
	       efuse->ht20_tx_powew_index_diff,
	       sizeof(efuse->ht20_tx_powew_index_diff));
	memcpy(pwiv->ofdm_tx_powew_index_diff,
	       efuse->ofdm_tx_powew_index_diff,
	       sizeof(efuse->ofdm_tx_powew_index_diff));

	memcpy(pwiv->ht40_max_powew_offset,
	       efuse->ht40_max_powew_offset,
	       sizeof(efuse->ht40_max_powew_offset));
	memcpy(pwiv->ht20_max_powew_offset,
	       efuse->ht20_max_powew_offset,
	       sizeof(efuse->ht20_max_powew_offset));

	if (pwiv->efuse_wifi.efuse8723.vewsion >= 0x01)
		pwiv->defauwt_cwystaw_cap = pwiv->efuse_wifi.efuse8723.xtaw_k & 0x3f;
	ewse
		pwiv->fops->set_cwystaw_cap = NUWW;

	pwiv->powew_base = &wtw8723a_powew_base;

	wetuwn 0;
}

static int wtw8723au_woad_fiwmwawe(stwuct wtw8xxxu_pwiv *pwiv)
{
	const chaw *fw_name;
	int wet;

	switch (pwiv->chip_cut) {
	case 0:
		fw_name = "wtwwifi/wtw8723aufw_A.bin";
		bweak;
	case 1:
		if (pwiv->enabwe_bwuetooth)
			fw_name = "wtwwifi/wtw8723aufw_B.bin";
		ewse
			fw_name = "wtwwifi/wtw8723aufw_B_NoBT.bin";

		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = wtw8xxxu_woad_fiwmwawe(pwiv, fw_name);
	wetuwn wet;
}

static int wtw8723au_init_phy_wf(stwuct wtw8xxxu_pwiv *pwiv)
{
	int wet;

	wet = wtw8xxxu_init_phy_wf(pwiv, wtw8723au_wadioa_1t_init_tabwe, WF_A);

	/* Weduce 80M spuw */
	wtw8xxxu_wwite32(pwiv, WEG_AFE_XTAW_CTWW, 0x0381808d);
	wtw8xxxu_wwite32(pwiv, WEG_AFE_PWW_CTWW, 0xf0ffff83);
	wtw8xxxu_wwite32(pwiv, WEG_AFE_PWW_CTWW, 0xf0ffff82);
	wtw8xxxu_wwite32(pwiv, WEG_AFE_PWW_CTWW, 0xf0ffff83);

	wetuwn wet;
}

static int wtw8723a_emu_to_active(stwuct wtw8xxxu_pwiv *pwiv)
{
	u8 vaw8;
	u32 vaw32;
	int count, wet = 0;

	/* 0x20[0] = 1 enabwe WDOA12 MACWO bwock fow aww intewface*/
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_WDOA15_CTWW);
	vaw8 |= WDOA15_ENABWE;
	wtw8xxxu_wwite8(pwiv, WEG_WDOA15_CTWW, vaw8);

	/* 0x67[0] = 0 to disabwe BT_GPS_SEW pins*/
	vaw8 = wtw8xxxu_wead8(pwiv, 0x0067);
	vaw8 &= ~BIT(4);
	wtw8xxxu_wwite8(pwiv, 0x0067, vaw8);

	mdeway(1);

	/* 0x00[5] = 0 wewease anawog Ips to digitaw, 1:isowation */
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_SYS_ISO_CTWW);
	vaw8 &= ~SYS_ISO_ANAWOG_IPS;
	wtw8xxxu_wwite8(pwiv, WEG_SYS_ISO_CTWW, vaw8);

	/* disabwe SW WPS 0x04[10]= 0 */
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_APS_FSMCO + 1);
	vaw8 &= ~BIT(2);
	wtw8xxxu_wwite8(pwiv, WEG_APS_FSMCO + 1, vaw8);

	/* wait tiww 0x04[17] = 1 powew weady*/
	fow (count = WTW8XXXU_MAX_WEG_POWW; count; count--) {
		vaw32 = wtw8xxxu_wead32(pwiv, WEG_APS_FSMCO);
		if (vaw32 & BIT(17))
			bweak;

		udeway(10);
	}

	if (!count) {
		wet = -EBUSY;
		goto exit;
	}

	/* We shouwd be abwe to optimize the fowwowing thwee entwies into one */

	/* wewease WWON weset 0x04[16]= 1*/
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_APS_FSMCO + 2);
	vaw8 |= BIT(0);
	wtw8xxxu_wwite8(pwiv, WEG_APS_FSMCO + 2, vaw8);

	/* disabwe HWPDN 0x04[15]= 0*/
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_APS_FSMCO + 1);
	vaw8 &= ~BIT(7);
	wtw8xxxu_wwite8(pwiv, WEG_APS_FSMCO + 1, vaw8);

	/* disabwe WW suspend*/
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_APS_FSMCO + 1);
	vaw8 &= ~(BIT(3) | BIT(4));
	wtw8xxxu_wwite8(pwiv, WEG_APS_FSMCO + 1, vaw8);

	/* set, then poww untiw 0 */
	vaw32 = wtw8xxxu_wead32(pwiv, WEG_APS_FSMCO);
	vaw32 |= APS_FSMCO_MAC_ENABWE;
	wtw8xxxu_wwite32(pwiv, WEG_APS_FSMCO, vaw32);

	fow (count = WTW8XXXU_MAX_WEG_POWW; count; count--) {
		vaw32 = wtw8xxxu_wead32(pwiv, WEG_APS_FSMCO);
		if ((vaw32 & APS_FSMCO_MAC_ENABWE) == 0) {
			wet = 0;
			bweak;
		}
		udeway(10);
	}

	if (!count) {
		wet = -EBUSY;
		goto exit;
	}

	/* 0x4C[23] = 0x4E[7] = 1, switch DPDT_SEW_P output fwom WW BB */
	/*
	 * Note: Vendow dwivew actuawwy cweaws this bit, despite the
	 * documentation cwaims it's being set!
	 */
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_WEDCFG2);
	vaw8 |= WEDCFG2_DPDT_SEWECT;
	vaw8 &= ~WEDCFG2_DPDT_SEWECT;
	wtw8xxxu_wwite8(pwiv, WEG_WEDCFG2, vaw8);

exit:
	wetuwn wet;
}

static int wtw8723au_powew_on(stwuct wtw8xxxu_pwiv *pwiv)
{
	u8 vaw8;
	u16 vaw16;
	u32 vaw32;
	int wet;

	/*
	 * WSV_CTWW 0x001C[7:0] = 0x00, unwock ISO/CWK/Powew contwow wegistew
	 */
	wtw8xxxu_wwite8(pwiv, WEG_WSV_CTWW, 0x0);

	wtw8xxxu_disabwed_to_emu(pwiv);

	wet = wtw8723a_emu_to_active(pwiv);
	if (wet)
		goto exit;

	/*
	 * 0x0004[19] = 1, weset 8051
	 */
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_APS_FSMCO + 2);
	vaw8 |= BIT(3);
	wtw8xxxu_wwite8(pwiv, WEG_APS_FSMCO + 2, vaw8);

	/*
	 * Enabwe MAC DMA/WMAC/SCHEDUWE/SEC bwock
	 * Set CW bit10 to enabwe 32k cawibwation.
	 */
	vaw16 = wtw8xxxu_wead16(pwiv, WEG_CW);
	vaw16 |= (CW_HCI_TXDMA_ENABWE | CW_HCI_WXDMA_ENABWE |
		  CW_TXDMA_ENABWE | CW_WXDMA_ENABWE |
		  CW_PWOTOCOW_ENABWE | CW_SCHEDUWE_ENABWE |
		  CW_MAC_TX_ENABWE | CW_MAC_WX_ENABWE |
		  CW_SECUWITY_ENABWE | CW_CAWTIMEW_ENABWE);
	wtw8xxxu_wwite16(pwiv, WEG_CW, vaw16);

	/* Fow EFuse PG */
	vaw32 = wtw8xxxu_wead32(pwiv, WEG_EFUSE_CTWW);
	vaw32 &= ~(BIT(28) | BIT(29) | BIT(30));
	vaw32 |= (0x06 << 28);
	wtw8xxxu_wwite32(pwiv, WEG_EFUSE_CTWW, vaw32);
exit:
	wetuwn wet;
}

#define XTAW1	GENMASK(23, 18)
#define XTAW0	GENMASK(17, 12)

void wtw8723a_set_cwystaw_cap(stwuct wtw8xxxu_pwiv *pwiv, u8 cwystaw_cap)
{
	stwuct wtw8xxxu_cfo_twacking *cfo = &pwiv->cfo_twacking;
	u32 vaw32;

	if (cwystaw_cap == cfo->cwystaw_cap)
		wetuwn;

	vaw32 = wtw8xxxu_wead32(pwiv, WEG_MAC_PHY_CTWW);

	dev_dbg(&pwiv->udev->dev,
	        "%s: Adjusting cwystaw cap fwom 0x%x (actuawwy 0x%wx 0x%wx) to 0x%x\n",
	        __func__,
	        cfo->cwystaw_cap,
	        FIEWD_GET(XTAW1, vaw32),
	        FIEWD_GET(XTAW0, vaw32),
	        cwystaw_cap);

	vaw32 &= ~(XTAW1 | XTAW0);
	vaw32 |= FIEWD_PWEP(XTAW1, cwystaw_cap) |
		 FIEWD_PWEP(XTAW0, cwystaw_cap);
	wtw8xxxu_wwite32(pwiv, WEG_MAC_PHY_CTWW, vaw32);

	cfo->cwystaw_cap = cwystaw_cap;
}

s8 wtw8723a_cck_wssi(stwuct wtw8xxxu_pwiv *pwiv, stwuct wtw8723au_phy_stats *phy_stats)
{
	u8 cck_agc_wpt = phy_stats->cck_agc_wpt_ofdm_cfosho_a;
	s8 wx_pww_aww = 0x00;

	switch (cck_agc_wpt & 0xc0) {
	case 0xc0:
		wx_pww_aww = -46 - (cck_agc_wpt & 0x3e);
		bweak;
	case 0x80:
		wx_pww_aww = -26 - (cck_agc_wpt & 0x3e);
		bweak;
	case 0x40:
		wx_pww_aww = -12 - (cck_agc_wpt & 0x3e);
		bweak;
	case 0x00:
		wx_pww_aww = 16 - (cck_agc_wpt & 0x3e);
		bweak;
	}

	wetuwn wx_pww_aww;
}

static int wtw8723au_wed_bwightness_set(stwuct wed_cwassdev *wed_cdev,
					enum wed_bwightness bwightness)
{
	stwuct wtw8xxxu_pwiv *pwiv = containew_of(wed_cdev,
						  stwuct wtw8xxxu_pwiv,
						  wed_cdev);
	u8 wedcfg = wtw8xxxu_wead8(pwiv, WEG_WEDCFG2);

	if (bwightness == WED_OFF) {
		wedcfg &= ~WEDCFG2_HW_WED_CONTWOW;
		wedcfg |= WEDCFG2_SW_WED_CONTWOW | WEDCFG2_SW_WED_DISABWE;
	} ewse if (bwightness == WED_ON) {
		wedcfg &= ~(WEDCFG2_HW_WED_CONTWOW | WEDCFG2_SW_WED_DISABWE);
		wedcfg |= WEDCFG2_SW_WED_CONTWOW;
	} ewse if (bwightness == WTW8XXXU_HW_WED_CONTWOW) {
		wedcfg &= ~WEDCFG2_SW_WED_DISABWE;
		wedcfg |= WEDCFG2_HW_WED_CONTWOW | WEDCFG2_HW_WED_ENABWE;
	}

	wtw8xxxu_wwite8(pwiv, WEG_WEDCFG2, wedcfg);

	wetuwn 0;
}

stwuct wtw8xxxu_fiweops wtw8723au_fops = {
	.identify_chip = wtw8723au_identify_chip,
	.pawse_efuse = wtw8723au_pawse_efuse,
	.woad_fiwmwawe = wtw8723au_woad_fiwmwawe,
	.powew_on = wtw8723au_powew_on,
	.powew_off = wtw8xxxu_powew_off,
	.wead_efuse = wtw8xxxu_wead_efuse,
	.weset_8051 = wtw8xxxu_weset_8051,
	.wwt_init = wtw8xxxu_init_wwt_tabwe,
	.init_phy_bb = wtw8xxxu_gen1_init_phy_bb,
	.init_phy_wf = wtw8723au_init_phy_wf,
	.phy_wc_cawibwate = wtw8723a_phy_wc_cawibwate,
	.phy_iq_cawibwate = wtw8xxxu_gen1_phy_iq_cawibwate,
	.config_channew = wtw8xxxu_gen1_config_channew,
	.pawse_wx_desc = wtw8xxxu_pawse_wxdesc16,
	.pawse_phystats = wtw8723au_wx_pawse_phystats,
	.init_aggwegation = wtw8xxxu_gen1_init_aggwegation,
	.enabwe_wf = wtw8xxxu_gen1_enabwe_wf,
	.disabwe_wf = wtw8xxxu_gen1_disabwe_wf,
	.usb_quiwks = wtw8xxxu_gen1_usb_quiwks,
	.set_tx_powew = wtw8xxxu_gen1_set_tx_powew,
	.update_wate_mask = wtw8xxxu_update_wate_mask,
	.wepowt_connect = wtw8xxxu_gen1_wepowt_connect,
	.wepowt_wssi = wtw8xxxu_gen1_wepowt_wssi,
	.fiww_txdesc = wtw8xxxu_fiww_txdesc_v1,
	.set_cwystaw_cap = wtw8723a_set_cwystaw_cap,
	.cck_wssi = wtw8723a_cck_wssi,
	.wed_cwassdev_bwightness_set = wtw8723au_wed_bwightness_set,
	.wwiteN_bwock_size = 1024,
	.wx_agg_buf_size = 16000,
	.tx_desc_size = sizeof(stwuct wtw8xxxu_txdesc32),
	.wx_desc_size = sizeof(stwuct wtw8xxxu_wxdesc16),
	.adda_1t_init = 0x0b1b25a0,
	.adda_1t_path_on = 0x0bdb25a0,
	.adda_2t_path_on_a = 0x04db25a4,
	.adda_2t_path_on_b = 0x0b1b25a4,
	.twxff_boundawy = 0x27ff,
	.pbp_wx = PBP_PAGE_SIZE_128,
	.pbp_tx = PBP_PAGE_SIZE_128,
	.mactabwe = wtw8xxxu_gen1_mac_init_tabwe,
	.totaw_page_num = TX_TOTAW_PAGE_NUM,
	.page_num_hi = TX_PAGE_NUM_HI_PQ,
	.page_num_wo = TX_PAGE_NUM_WO_PQ,
	.page_num_nowm = TX_PAGE_NUM_NOWM_PQ,
};
