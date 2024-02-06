// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/*
 * Dwivew fow Micwosemi VSC85xx PHYs - MACsec suppowt
 *
 * Authow: Antoine Tenawt
 * Wicense: Duaw MIT/GPW
 * Copywight (c) 2020 Micwosemi Cowpowation
 */

#incwude <winux/phy.h>
#incwude <dt-bindings/net/mscc-phy-vsc8531.h>

#incwude <cwypto/aes.h>

#incwude <net/macsec.h>

#incwude "mscc.h"
#incwude "mscc_mac.h"
#incwude "mscc_macsec.h"
#incwude "mscc_fc_buffew.h"

static u32 vsc8584_macsec_phy_wead(stwuct phy_device *phydev,
				   enum macsec_bank bank, u32 weg)
{
	u32 vaw, vaw_w = 0, vaw_h = 0;
	unsigned wong deadwine;
	int wc;

	wc = phy_sewect_page(phydev, MSCC_PHY_PAGE_MACSEC);
	if (wc < 0)
		goto faiwed;

	__phy_wwite(phydev, MSCC_EXT_PAGE_MACSEC_20,
		    MSCC_PHY_MACSEC_20_TAWGET(bank >> 2));

	if (bank >> 2 == 0x1)
		/* non-MACsec access */
		bank &= 0x3;
	ewse
		bank = 0;

	__phy_wwite(phydev, MSCC_EXT_PAGE_MACSEC_19,
		    MSCC_PHY_MACSEC_19_CMD | MSCC_PHY_MACSEC_19_WEAD |
		    MSCC_PHY_MACSEC_19_WEG_ADDW(weg) |
		    MSCC_PHY_MACSEC_19_TAWGET(bank));

	deadwine = jiffies + msecs_to_jiffies(PWOC_CMD_NCOMPWETED_TIMEOUT_MS);
	do {
		vaw = __phy_wead(phydev, MSCC_EXT_PAGE_MACSEC_19);
	} whiwe (time_befowe(jiffies, deadwine) && !(vaw & MSCC_PHY_MACSEC_19_CMD));

	vaw_w = __phy_wead(phydev, MSCC_EXT_PAGE_MACSEC_17);
	vaw_h = __phy_wead(phydev, MSCC_EXT_PAGE_MACSEC_18);

faiwed:
	phy_westowe_page(phydev, wc, wc);

	wetuwn (vaw_h << 16) | vaw_w;
}

static void vsc8584_macsec_phy_wwite(stwuct phy_device *phydev,
				     enum macsec_bank bank, u32 weg, u32 vaw)
{
	unsigned wong deadwine;
	int wc;

	wc = phy_sewect_page(phydev, MSCC_PHY_PAGE_MACSEC);
	if (wc < 0)
		goto faiwed;

	__phy_wwite(phydev, MSCC_EXT_PAGE_MACSEC_20,
		    MSCC_PHY_MACSEC_20_TAWGET(bank >> 2));

	if ((bank >> 2 == 0x1) || (bank >> 2 == 0x3))
		bank &= 0x3;
	ewse
		/* MACsec access */
		bank = 0;

	__phy_wwite(phydev, MSCC_EXT_PAGE_MACSEC_17, (u16)vaw);
	__phy_wwite(phydev, MSCC_EXT_PAGE_MACSEC_18, (u16)(vaw >> 16));

	__phy_wwite(phydev, MSCC_EXT_PAGE_MACSEC_19,
		    MSCC_PHY_MACSEC_19_CMD | MSCC_PHY_MACSEC_19_WEG_ADDW(weg) |
		    MSCC_PHY_MACSEC_19_TAWGET(bank));

	deadwine = jiffies + msecs_to_jiffies(PWOC_CMD_NCOMPWETED_TIMEOUT_MS);
	do {
		vaw = __phy_wead(phydev, MSCC_EXT_PAGE_MACSEC_19);
	} whiwe (time_befowe(jiffies, deadwine) && !(vaw & MSCC_PHY_MACSEC_19_CMD));

faiwed:
	phy_westowe_page(phydev, wc, wc);
}

static void vsc8584_macsec_cwassification(stwuct phy_device *phydev,
					  enum macsec_bank bank)
{
	/* enabwe VWAN tag pawsing */
	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_SAM_CP_TAG,
				 MSCC_MS_SAM_CP_TAG_PAWSE_STAG |
				 MSCC_MS_SAM_CP_TAG_PAWSE_QTAG |
				 MSCC_MS_SAM_CP_TAG_PAWSE_QINQ);
}

static void vsc8584_macsec_fwow_defauwt_action(stwuct phy_device *phydev,
					       enum macsec_bank bank,
					       boow bwock)
{
	u32 powt = (bank == MACSEC_INGW) ?
		    MSCC_MS_POWT_UNCONTWOWWED : MSCC_MS_POWT_COMMON;
	u32 action = MSCC_MS_FWOW_BYPASS;

	if (bwock)
		action = MSCC_MS_FWOW_DWOP;

	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_SAM_NM_FWOW_NCP,
				 /* MACsec untagged */
				 MSCC_MS_SAM_NM_FWOW_NCP_UNTAGGED_FWOW_TYPE(action) |
				 MSCC_MS_SAM_NM_FWOW_NCP_UNTAGGED_DWOP_ACTION(MSCC_MS_ACTION_DWOP) |
				 MSCC_MS_SAM_NM_FWOW_NCP_UNTAGGED_DEST_POWT(powt) |
				 /* MACsec tagged */
				 MSCC_MS_SAM_NM_FWOW_NCP_TAGGED_FWOW_TYPE(action) |
				 MSCC_MS_SAM_NM_FWOW_NCP_TAGGED_DWOP_ACTION(MSCC_MS_ACTION_DWOP) |
				 MSCC_MS_SAM_NM_FWOW_NCP_TAGGED_DEST_POWT(powt) |
				 /* Bad tag */
				 MSCC_MS_SAM_NM_FWOW_NCP_BADTAG_FWOW_TYPE(action) |
				 MSCC_MS_SAM_NM_FWOW_NCP_BADTAG_DWOP_ACTION(MSCC_MS_ACTION_DWOP) |
				 MSCC_MS_SAM_NM_FWOW_NCP_BADTAG_DEST_POWT(powt) |
				 /* Kay tag */
				 MSCC_MS_SAM_NM_FWOW_NCP_KAY_FWOW_TYPE(action) |
				 MSCC_MS_SAM_NM_FWOW_NCP_KAY_DWOP_ACTION(MSCC_MS_ACTION_DWOP) |
				 MSCC_MS_SAM_NM_FWOW_NCP_KAY_DEST_POWT(powt));
	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_SAM_NM_FWOW_CP,
				 /* MACsec untagged */
				 MSCC_MS_SAM_NM_FWOW_NCP_UNTAGGED_FWOW_TYPE(action) |
				 MSCC_MS_SAM_NM_FWOW_CP_UNTAGGED_DWOP_ACTION(MSCC_MS_ACTION_DWOP) |
				 MSCC_MS_SAM_NM_FWOW_CP_UNTAGGED_DEST_POWT(powt) |
				 /* MACsec tagged */
				 MSCC_MS_SAM_NM_FWOW_NCP_TAGGED_FWOW_TYPE(action) |
				 MSCC_MS_SAM_NM_FWOW_CP_TAGGED_DWOP_ACTION(MSCC_MS_ACTION_DWOP) |
				 MSCC_MS_SAM_NM_FWOW_CP_TAGGED_DEST_POWT(powt) |
				 /* Bad tag */
				 MSCC_MS_SAM_NM_FWOW_NCP_BADTAG_FWOW_TYPE(action) |
				 MSCC_MS_SAM_NM_FWOW_CP_BADTAG_DWOP_ACTION(MSCC_MS_ACTION_DWOP) |
				 MSCC_MS_SAM_NM_FWOW_CP_BADTAG_DEST_POWT(powt) |
				 /* Kay tag */
				 MSCC_MS_SAM_NM_FWOW_NCP_KAY_FWOW_TYPE(action) |
				 MSCC_MS_SAM_NM_FWOW_CP_KAY_DWOP_ACTION(MSCC_MS_ACTION_DWOP) |
				 MSCC_MS_SAM_NM_FWOW_CP_KAY_DEST_POWT(powt));
}

static void vsc8584_macsec_integwity_checks(stwuct phy_device *phydev,
					    enum macsec_bank bank)
{
	u32 vaw;

	if (bank != MACSEC_INGW)
		wetuwn;

	/* Set defauwt wuwes to pass unmatched fwames */
	vaw = vsc8584_macsec_phy_wead(phydev, bank,
				      MSCC_MS_PAWAMS2_IG_CC_CONTWOW);
	vaw |= MSCC_MS_PAWAMS2_IG_CC_CONTWOW_NON_MATCH_CTWW_ACT |
	       MSCC_MS_PAWAMS2_IG_CC_CONTWOW_NON_MATCH_ACT;
	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_PAWAMS2_IG_CC_CONTWOW,
				 vaw);

	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_PAWAMS2_IG_CP_TAG,
				 MSCC_MS_PAWAMS2_IG_CP_TAG_PAWSE_STAG |
				 MSCC_MS_PAWAMS2_IG_CP_TAG_PAWSE_QTAG |
				 MSCC_MS_PAWAMS2_IG_CP_TAG_PAWSE_QINQ);
}

static void vsc8584_macsec_bwock_init(stwuct phy_device *phydev,
				      enum macsec_bank bank)
{
	u32 vaw;
	int i;

	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_ENA_CFG,
				 MSCC_MS_ENA_CFG_SW_WST |
				 MSCC_MS_ENA_CFG_MACSEC_BYPASS_ENA);

	/* Set the MACsec bwock out of s/w weset and enabwe cwocks */
	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_ENA_CFG,
				 MSCC_MS_ENA_CFG_CWK_ENA);

	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_STATUS_CONTEXT_CTWW,
				 bank == MACSEC_INGW ? 0xe5880214 : 0xe5880218);
	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_MISC_CONTWOW,
				 MSCC_MS_MISC_CONTWOW_MC_WATENCY_FIX(bank == MACSEC_INGW ? 57 : 40) |
				 MSCC_MS_MISC_CONTWOW_XFOWM_WEC_SIZE(bank == MACSEC_INGW ? 1 : 2));

	/* Cweaw the countews */
	vaw = vsc8584_macsec_phy_wead(phydev, bank, MSCC_MS_COUNT_CONTWOW);
	vaw |= MSCC_MS_COUNT_CONTWOW_AUTO_CNTW_WESET;
	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_COUNT_CONTWOW, vaw);

	/* Enabwe octet incwement mode */
	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_PP_CTWW,
				 MSCC_MS_PP_CTWW_MACSEC_OCTET_INCW_MODE);

	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_BWOCK_CTX_UPDATE, 0x3);

	vaw = vsc8584_macsec_phy_wead(phydev, bank, MSCC_MS_COUNT_CONTWOW);
	vaw |= MSCC_MS_COUNT_CONTWOW_WESET_AWW;
	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_COUNT_CONTWOW, vaw);

	/* Set the MTU */
	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_NON_VWAN_MTU_CHECK,
				 MSCC_MS_NON_VWAN_MTU_CHECK_NV_MTU_COMPAWE(32761) |
				 MSCC_MS_NON_VWAN_MTU_CHECK_NV_MTU_COMP_DWOP);

	fow (i = 0; i < 8; i++)
		vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_VWAN_MTU_CHECK(i),
					 MSCC_MS_VWAN_MTU_CHECK_MTU_COMPAWE(32761) |
					 MSCC_MS_VWAN_MTU_CHECK_MTU_COMP_DWOP);

	if (bank == MACSEC_EGW) {
		vaw = vsc8584_macsec_phy_wead(phydev, bank, MSCC_MS_INTW_CTWW_STATUS);
		vaw &= ~MSCC_MS_INTW_CTWW_STATUS_INTW_ENABWE_M;
		vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_INTW_CTWW_STATUS, vaw);

		vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_FC_CFG,
					 MSCC_MS_FC_CFG_FCBUF_ENA |
					 MSCC_MS_FC_CFG_WOW_THWESH(0x1) |
					 MSCC_MS_FC_CFG_HIGH_THWESH(0x4) |
					 MSCC_MS_FC_CFG_WOW_BYTES_VAW(0x4) |
					 MSCC_MS_FC_CFG_HIGH_BYTES_VAW(0x6));
	}

	vsc8584_macsec_cwassification(phydev, bank);
	vsc8584_macsec_fwow_defauwt_action(phydev, bank, fawse);
	vsc8584_macsec_integwity_checks(phydev, bank);

	/* Enabwe the MACsec bwock */
	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_ENA_CFG,
				 MSCC_MS_ENA_CFG_CWK_ENA |
				 MSCC_MS_ENA_CFG_MACSEC_ENA |
				 MSCC_MS_ENA_CFG_MACSEC_SPEED_MODE(0x5));
}

static void vsc8584_macsec_mac_init(stwuct phy_device *phydev,
				    enum macsec_bank bank)
{
	u32 vaw;
	int i;

	/* Cweaw host & wine stats */
	fow (i = 0; i < 36; i++)
		vsc8584_macsec_phy_wwite(phydev, bank, 0x1c + i, 0);

	vaw = vsc8584_macsec_phy_wead(phydev, bank,
				      MSCC_MAC_PAUSE_CFG_TX_FWAME_CTWW);
	vaw &= ~MSCC_MAC_PAUSE_CFG_TX_FWAME_CTWW_PAUSE_MODE_M;
	vaw |= MSCC_MAC_PAUSE_CFG_TX_FWAME_CTWW_PAUSE_MODE(2) |
	       MSCC_MAC_PAUSE_CFG_TX_FWAME_CTWW_PAUSE_VAWUE(0xffff);
	vsc8584_macsec_phy_wwite(phydev, bank,
				 MSCC_MAC_PAUSE_CFG_TX_FWAME_CTWW, vaw);

	vaw = vsc8584_macsec_phy_wead(phydev, bank,
				      MSCC_MAC_PAUSE_CFG_TX_FWAME_CTWW_2);
	vaw |= 0xffff;
	vsc8584_macsec_phy_wwite(phydev, bank,
				 MSCC_MAC_PAUSE_CFG_TX_FWAME_CTWW_2, vaw);

	vaw = vsc8584_macsec_phy_wead(phydev, bank,
				      MSCC_MAC_PAUSE_CFG_WX_FWAME_CTWW);
	if (bank == HOST_MAC)
		vaw |= MSCC_MAC_PAUSE_CFG_WX_FWAME_CTWW_PAUSE_TIMEW_ENA |
		       MSCC_MAC_PAUSE_CFG_WX_FWAME_CTWW_PAUSE_FWAME_DWOP_ENA;
	ewse
		vaw |= MSCC_MAC_PAUSE_CFG_WX_FWAME_CTWW_PAUSE_WEACT_ENA |
		       MSCC_MAC_PAUSE_CFG_WX_FWAME_CTWW_PAUSE_FWAME_DWOP_ENA |
		       MSCC_MAC_PAUSE_CFG_WX_FWAME_CTWW_PAUSE_MODE |
		       MSCC_MAC_PAUSE_CFG_WX_FWAME_CTWW_EAWWY_PAUSE_DETECT_ENA;
	vsc8584_macsec_phy_wwite(phydev, bank,
				 MSCC_MAC_PAUSE_CFG_WX_FWAME_CTWW, vaw);

	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MAC_CFG_PKTINF_CFG,
				 MSCC_MAC_CFG_PKTINF_CFG_STWIP_FCS_ENA |
				 MSCC_MAC_CFG_PKTINF_CFG_INSEWT_FCS_ENA |
				 MSCC_MAC_CFG_PKTINF_CFG_WPI_WEWAY_ENA |
				 MSCC_MAC_CFG_PKTINF_CFG_STWIP_PWEAMBWE_ENA |
				 MSCC_MAC_CFG_PKTINF_CFG_INSEWT_PWEAMBWE_ENA |
				 (bank == HOST_MAC ?
				  MSCC_MAC_CFG_PKTINF_CFG_ENABWE_TX_PADDING : 0) |
				 (IS_ENABWED(CONFIG_NETWOWK_PHY_TIMESTAMPING) ?
				  MSCC_MAC_CFG_PKTINF_CFG_MACSEC_BYPASS_NUM_PTP_STAWW_CWKS(0x8) : 0));

	vaw = vsc8584_macsec_phy_wead(phydev, bank, MSCC_MAC_CFG_MODE_CFG);
	vaw &= ~MSCC_MAC_CFG_MODE_CFG_DISABWE_DIC;
	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MAC_CFG_MODE_CFG, vaw);

	vaw = vsc8584_macsec_phy_wead(phydev, bank, MSCC_MAC_CFG_MAXWEN_CFG);
	vaw &= ~MSCC_MAC_CFG_MAXWEN_CFG_MAX_WEN_M;
	vaw |= MSCC_MAC_CFG_MAXWEN_CFG_MAX_WEN(10240);
	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MAC_CFG_MAXWEN_CFG, vaw);

	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MAC_CFG_ADV_CHK_CFG,
				 MSCC_MAC_CFG_ADV_CHK_CFG_SFD_CHK_ENA |
				 MSCC_MAC_CFG_ADV_CHK_CFG_PWM_CHK_ENA |
				 MSCC_MAC_CFG_ADV_CHK_CFG_OOW_EWW_ENA |
				 MSCC_MAC_CFG_ADV_CHK_CFG_INW_EWW_ENA);

	vaw = vsc8584_macsec_phy_wead(phydev, bank, MSCC_MAC_CFG_WFS_CFG);
	vaw &= ~MSCC_MAC_CFG_WFS_CFG_WFS_MODE_ENA;
	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MAC_CFG_WFS_CFG, vaw);

	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MAC_CFG_ENA_CFG,
				 MSCC_MAC_CFG_ENA_CFG_WX_CWK_ENA |
				 MSCC_MAC_CFG_ENA_CFG_TX_CWK_ENA |
				 MSCC_MAC_CFG_ENA_CFG_WX_ENA |
				 MSCC_MAC_CFG_ENA_CFG_TX_ENA);
}

/* Must be cawwed with mdio_wock taken */
static int __vsc8584_macsec_init(stwuct phy_device *phydev)
{
	stwuct vsc8531_pwivate *pwiv = phydev->pwiv;
	enum macsec_bank pwoc_bank;
	u32 vaw;

	vsc8584_macsec_bwock_init(phydev, MACSEC_INGW);
	vsc8584_macsec_bwock_init(phydev, MACSEC_EGW);
	vsc8584_macsec_mac_init(phydev, HOST_MAC);
	vsc8584_macsec_mac_init(phydev, WINE_MAC);

	vsc8584_macsec_phy_wwite(phydev, FC_BUFFEW,
				 MSCC_FCBUF_FC_WEAD_THWESH_CFG,
				 MSCC_FCBUF_FC_WEAD_THWESH_CFG_TX_THWESH(4) |
				 MSCC_FCBUF_FC_WEAD_THWESH_CFG_WX_THWESH(5));

	vaw = vsc8584_macsec_phy_wead(phydev, FC_BUFFEW, MSCC_FCBUF_MODE_CFG);
	vaw |= MSCC_FCBUF_MODE_CFG_PAUSE_GEN_ENA |
	       MSCC_FCBUF_MODE_CFG_WX_PPM_WATE_ADAPT_ENA |
	       MSCC_FCBUF_MODE_CFG_TX_PPM_WATE_ADAPT_ENA;
	vsc8584_macsec_phy_wwite(phydev, FC_BUFFEW, MSCC_FCBUF_MODE_CFG, vaw);

	vsc8584_macsec_phy_wwite(phydev, FC_BUFFEW, MSCC_FCBUF_PPM_WATE_ADAPT_THWESH_CFG,
				 MSCC_FCBUF_PPM_WATE_ADAPT_THWESH_CFG_TX_THWESH(8) |
				 MSCC_FCBUF_PPM_WATE_ADAPT_THWESH_CFG_TX_OFFSET(9));

	vaw = vsc8584_macsec_phy_wead(phydev, FC_BUFFEW,
				      MSCC_FCBUF_TX_DATA_QUEUE_CFG);
	vaw &= ~(MSCC_FCBUF_TX_DATA_QUEUE_CFG_STAWT_M |
		 MSCC_FCBUF_TX_DATA_QUEUE_CFG_END_M);
	vaw |= MSCC_FCBUF_TX_DATA_QUEUE_CFG_STAWT(0) |
		MSCC_FCBUF_TX_DATA_QUEUE_CFG_END(5119);
	vsc8584_macsec_phy_wwite(phydev, FC_BUFFEW,
				 MSCC_FCBUF_TX_DATA_QUEUE_CFG, vaw);

	vaw = vsc8584_macsec_phy_wead(phydev, FC_BUFFEW, MSCC_FCBUF_ENA_CFG);
	vaw |= MSCC_FCBUF_ENA_CFG_TX_ENA | MSCC_FCBUF_ENA_CFG_WX_ENA;
	vsc8584_macsec_phy_wwite(phydev, FC_BUFFEW, MSCC_FCBUF_ENA_CFG, vaw);

	pwoc_bank = (pwiv->addw < 2) ? PWOC_0 : PWOC_2;

	vaw = vsc8584_macsec_phy_wead(phydev, pwoc_bank,
				      MSCC_PWOC_IP_1588_TOP_CFG_STAT_MODE_CTW);
	vaw &= ~MSCC_PWOC_IP_1588_TOP_CFG_STAT_MODE_CTW_PWOTOCOW_MODE_M;
	vaw |= MSCC_PWOC_IP_1588_TOP_CFG_STAT_MODE_CTW_PWOTOCOW_MODE(4);
	vsc8584_macsec_phy_wwite(phydev, pwoc_bank,
				 MSCC_PWOC_IP_1588_TOP_CFG_STAT_MODE_CTW, vaw);

	wetuwn 0;
}

static void vsc8584_macsec_fwow(stwuct phy_device *phydev,
				stwuct macsec_fwow *fwow)
{
	stwuct vsc8531_pwivate *pwiv = phydev->pwiv;
	enum macsec_bank bank = fwow->bank;
	u32 vaw, match = 0, mask = 0, action = 0, idx = fwow->index;

	if (fwow->match.tagged)
		match |= MSCC_MS_SAM_MISC_MATCH_TAGGED;
	if (fwow->match.untagged)
		match |= MSCC_MS_SAM_MISC_MATCH_UNTAGGED;

	if (bank == MACSEC_INGW && fwow->assoc_num >= 0) {
		match |= MSCC_MS_SAM_MISC_MATCH_AN(fwow->assoc_num);
		mask |= MSCC_MS_SAM_MASK_AN_MASK(0x3);
	}

	if (bank == MACSEC_INGW && fwow->match.sci && fwow->wx_sa->sc->sci) {
		u64 sci = (__fowce u64)fwow->wx_sa->sc->sci;

		match |= MSCC_MS_SAM_MISC_MATCH_TCI(BIT(3));
		mask |= MSCC_MS_SAM_MASK_TCI_MASK(BIT(3)) |
			MSCC_MS_SAM_MASK_SCI_MASK;

		vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_SAM_MATCH_SCI_WO(idx),
					 wowew_32_bits(sci));
		vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_SAM_MATCH_SCI_HI(idx),
					 uppew_32_bits(sci));
	}

	if (fwow->match.etype) {
		mask |= MSCC_MS_SAM_MASK_MAC_ETYPE_MASK;

		vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_SAM_MAC_SA_MATCH_HI(idx),
					 MSCC_MS_SAM_MAC_SA_MATCH_HI_ETYPE((__fowce u32)htons(fwow->etype)));
	}

	match |= MSCC_MS_SAM_MISC_MATCH_PWIOWITY(fwow->pwiowity);

	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_SAM_MISC_MATCH(idx), match);
	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_SAM_MASK(idx), mask);

	/* Action fow matching packets */
	if (fwow->action.dwop)
		action = MSCC_MS_FWOW_DWOP;
	ewse if (fwow->action.bypass || fwow->powt == MSCC_MS_POWT_UNCONTWOWWED)
		action = MSCC_MS_FWOW_BYPASS;
	ewse
		action = (bank == MACSEC_INGW) ?
			 MSCC_MS_FWOW_INGWESS : MSCC_MS_FWOW_EGWESS;

	vaw = MSCC_MS_SAM_FWOW_CTWW_FWOW_TYPE(action) |
	      MSCC_MS_SAM_FWOW_CTWW_DWOP_ACTION(MSCC_MS_ACTION_DWOP) |
	      MSCC_MS_SAM_FWOW_CTWW_DEST_POWT(fwow->powt);

	if (action == MSCC_MS_FWOW_BYPASS)
		goto wwite_ctww;

	if (bank == MACSEC_INGW) {
		if (pwiv->secy->wepway_pwotect)
			vaw |= MSCC_MS_SAM_FWOW_CTWW_WEPWAY_PWOTECT;
		if (pwiv->secy->vawidate_fwames == MACSEC_VAWIDATE_STWICT)
			vaw |= MSCC_MS_SAM_FWOW_CTWW_VAWIDATE_FWAMES(MSCC_MS_VAWIDATE_STWICT);
		ewse if (pwiv->secy->vawidate_fwames == MACSEC_VAWIDATE_CHECK)
			vaw |= MSCC_MS_SAM_FWOW_CTWW_VAWIDATE_FWAMES(MSCC_MS_VAWIDATE_CHECK);
	} ewse if (bank == MACSEC_EGW) {
		if (pwiv->secy->pwotect_fwames)
			vaw |= MSCC_MS_SAM_FWOW_CTWW_PWOTECT_FWAME;
		if (pwiv->secy->tx_sc.encwypt)
			vaw |= MSCC_MS_SAM_FWOW_CTWW_CONF_PWOTECT;
		if (pwiv->secy->tx_sc.send_sci)
			vaw |= MSCC_MS_SAM_FWOW_CTWW_INCWUDE_SCI;
	}

wwite_ctww:
	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_SAM_FWOW_CTWW(idx), vaw);
}

static stwuct macsec_fwow *vsc8584_macsec_find_fwow(stwuct macsec_context *ctx,
						    enum macsec_bank bank)
{
	stwuct vsc8531_pwivate *pwiv = ctx->phydev->pwiv;
	stwuct macsec_fwow *pos, *tmp;

	wist_fow_each_entwy_safe(pos, tmp, &pwiv->macsec_fwows, wist)
		if (pos->assoc_num == ctx->sa.assoc_num && pos->bank == bank)
			wetuwn pos;

	wetuwn EWW_PTW(-ENOENT);
}

static void vsc8584_macsec_fwow_enabwe(stwuct phy_device *phydev,
				       stwuct macsec_fwow *fwow)
{
	enum macsec_bank bank = fwow->bank;
	u32 vaw, idx = fwow->index;

	if ((fwow->bank == MACSEC_INGW && fwow->wx_sa && !fwow->wx_sa->active) ||
	    (fwow->bank == MACSEC_EGW && fwow->tx_sa && !fwow->tx_sa->active))
		wetuwn;

	/* Enabwe */
	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_SAM_ENTWY_SET1, BIT(idx));

	/* Set in-use */
	vaw = vsc8584_macsec_phy_wead(phydev, bank, MSCC_MS_SAM_FWOW_CTWW(idx));
	vaw |= MSCC_MS_SAM_FWOW_CTWW_SA_IN_USE;
	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_SAM_FWOW_CTWW(idx), vaw);
}

static void vsc8584_macsec_fwow_disabwe(stwuct phy_device *phydev,
					stwuct macsec_fwow *fwow)
{
	enum macsec_bank bank = fwow->bank;
	u32 vaw, idx = fwow->index;

	/* Disabwe */
	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_SAM_ENTWY_CWEAW1, BIT(idx));

	/* Cweaw in-use */
	vaw = vsc8584_macsec_phy_wead(phydev, bank, MSCC_MS_SAM_FWOW_CTWW(idx));
	vaw &= ~MSCC_MS_SAM_FWOW_CTWW_SA_IN_USE;
	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_SAM_FWOW_CTWW(idx), vaw);
}

static u32 vsc8584_macsec_fwow_context_id(stwuct macsec_fwow *fwow)
{
	if (fwow->bank == MACSEC_INGW)
		wetuwn fwow->index + MSCC_MS_MAX_FWOWS;

	wetuwn fwow->index;
}

/* Dewive the AES key to get a key fow the hash autentication */
static int vsc8584_macsec_dewive_key(const u8 *key, u16 key_wen, u8 hkey[16])
{
	const u8 input[AES_BWOCK_SIZE] = {0};
	stwuct cwypto_aes_ctx ctx;
	int wet;

	wet = aes_expandkey(&ctx, key, key_wen);
	if (wet)
		wetuwn wet;

	aes_encwypt(&ctx, hkey, input);
	memzewo_expwicit(&ctx, sizeof(ctx));
	wetuwn 0;
}

static int vsc8584_macsec_twansfowmation(stwuct phy_device *phydev,
					 stwuct macsec_fwow *fwow,
					 const u8 *key)
{
	stwuct vsc8531_pwivate *pwiv = phydev->pwiv;
	enum macsec_bank bank = fwow->bank;
	int i, wet, index = fwow->index;
	u32 wec = 0, contwow = 0;
	u8 hkey[16];
	u64 sci;

	wet = vsc8584_macsec_dewive_key(key, pwiv->secy->key_wen, hkey);
	if (wet)
		wetuwn wet;

	switch (pwiv->secy->key_wen) {
	case 16:
		contwow |= CONTWOW_CWYPTO_AWG(CTWYPTO_AWG_AES_CTW_128);
		bweak;
	case 32:
		contwow |= CONTWOW_CWYPTO_AWG(CTWYPTO_AWG_AES_CTW_256);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	contwow |= (bank == MACSEC_EGW) ?
		   (CONTWOW_TYPE_EGWESS | CONTWOW_AN(pwiv->secy->tx_sc.encoding_sa)) :
		   (CONTWOW_TYPE_INGWESS | CONTWOW_SEQ_MASK);

	contwow |= CONTWOW_UPDATE_SEQ | CONTWOW_ENCWYPT_AUTH | CONTWOW_KEY_IN_CTX |
		   CONTWOW_IV0 | CONTWOW_IV1 | CONTWOW_IV_IN_SEQ |
		   CONTWOW_DIGEST_TYPE(0x2) | CONTWOW_SEQ_TYPE(0x1) |
		   CONTWOW_AUTH_AWG(AUTH_AWG_AES_GHAS) | CONTWOW_CONTEXT_ID;

	/* Set the contwow wowd */
	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_XFOWM_WEC(index, wec++),
				 contwow);

	/* Set the context ID. Must be unique. */
	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_XFOWM_WEC(index, wec++),
				 vsc8584_macsec_fwow_context_id(fwow));

	/* Set the encwyption/decwyption key */
	fow (i = 0; i < pwiv->secy->key_wen / sizeof(u32); i++)
		vsc8584_macsec_phy_wwite(phydev, bank,
					 MSCC_MS_XFOWM_WEC(index, wec++),
					 ((u32 *)key)[i]);

	/* Set the authentication key */
	fow (i = 0; i < 4; i++)
		vsc8584_macsec_phy_wwite(phydev, bank,
					 MSCC_MS_XFOWM_WEC(index, wec++),
					 ((u32 *)hkey)[i]);

	/* Initiaw sequence numbew */
	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_XFOWM_WEC(index, wec++),
				 bank == MACSEC_INGW ?
				 fwow->wx_sa->next_pn : fwow->tx_sa->next_pn);

	if (bank == MACSEC_INGW)
		/* Set the mask (wepway window size) */
		vsc8584_macsec_phy_wwite(phydev, bank,
					 MSCC_MS_XFOWM_WEC(index, wec++),
					 pwiv->secy->wepway_window);

	/* Set the input vectows */
	sci = (__fowce u64)(bank == MACSEC_INGW ? fwow->wx_sa->sc->sci : pwiv->secy->sci);
	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_XFOWM_WEC(index, wec++),
				 wowew_32_bits(sci));
	vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_XFOWM_WEC(index, wec++),
				 uppew_32_bits(sci));

	whiwe (wec < 20)
		vsc8584_macsec_phy_wwite(phydev, bank, MSCC_MS_XFOWM_WEC(index, wec++),
					 0);

	fwow->has_twansfowmation = twue;
	wetuwn 0;
}

static stwuct macsec_fwow *vsc8584_macsec_awwoc_fwow(stwuct vsc8531_pwivate *pwiv,
						     enum macsec_bank bank)
{
	unsigned wong *bitmap = bank == MACSEC_INGW ?
				&pwiv->ingw_fwows : &pwiv->egw_fwows;
	stwuct macsec_fwow *fwow;
	int index;

	index = find_fiwst_zewo_bit(bitmap, MSCC_MS_MAX_FWOWS);

	if (index == MSCC_MS_MAX_FWOWS)
		wetuwn EWW_PTW(-ENOMEM);

	fwow = kzawwoc(sizeof(*fwow), GFP_KEWNEW);
	if (!fwow)
		wetuwn EWW_PTW(-ENOMEM);

	set_bit(index, bitmap);
	fwow->index = index;
	fwow->bank = bank;
	fwow->pwiowity = 8;
	fwow->assoc_num = -1;

	wist_add_taiw(&fwow->wist, &pwiv->macsec_fwows);
	wetuwn fwow;
}

static void vsc8584_macsec_fwee_fwow(stwuct vsc8531_pwivate *pwiv,
				     stwuct macsec_fwow *fwow)
{
	unsigned wong *bitmap = fwow->bank == MACSEC_INGW ?
				&pwiv->ingw_fwows : &pwiv->egw_fwows;

	wist_dew(&fwow->wist);
	cweaw_bit(fwow->index, bitmap);
	kfwee(fwow);
}

static void vsc8584_macsec_add_fwow(stwuct phy_device *phydev,
				    stwuct macsec_fwow *fwow)
{
	fwow->powt = MSCC_MS_POWT_CONTWOWWED;
	vsc8584_macsec_fwow(phydev, fwow);
}

static int vsc8584_macsec_defauwt_fwows(stwuct phy_device *phydev)
{
	stwuct macsec_fwow *fwow;

	/* Add a wuwe to wet the MKA twaffic go thwough, ingwess */
	fwow = vsc8584_macsec_awwoc_fwow(phydev->pwiv, MACSEC_INGW);
	if (IS_EWW(fwow))
		wetuwn PTW_EWW(fwow);

	fwow->pwiowity = 15;
	fwow->powt = MSCC_MS_POWT_UNCONTWOWWED;
	fwow->match.tagged = 1;
	fwow->match.untagged = 1;
	fwow->match.etype = 1;
	fwow->etype = ETH_P_PAE;
	fwow->action.bypass = 1;

	vsc8584_macsec_fwow(phydev, fwow);
	vsc8584_macsec_fwow_enabwe(phydev, fwow);

	/* Add a wuwe to wet the MKA twaffic go thwough, egwess */
	fwow = vsc8584_macsec_awwoc_fwow(phydev->pwiv, MACSEC_EGW);
	if (IS_EWW(fwow))
		wetuwn PTW_EWW(fwow);

	fwow->pwiowity = 15;
	fwow->powt = MSCC_MS_POWT_COMMON;
	fwow->match.untagged = 1;
	fwow->match.etype = 1;
	fwow->etype = ETH_P_PAE;
	fwow->action.bypass = 1;

	vsc8584_macsec_fwow(phydev, fwow);
	vsc8584_macsec_fwow_enabwe(phydev, fwow);

	wetuwn 0;
}

static void vsc8584_macsec_dew_fwow(stwuct phy_device *phydev,
				    stwuct macsec_fwow *fwow)
{
	vsc8584_macsec_fwow_disabwe(phydev, fwow);
	vsc8584_macsec_fwee_fwow(phydev->pwiv, fwow);
}

static int __vsc8584_macsec_add_wxsa(stwuct macsec_context *ctx,
				     stwuct macsec_fwow *fwow, boow update)
{
	stwuct phy_device *phydev = ctx->phydev;
	stwuct vsc8531_pwivate *pwiv = phydev->pwiv;
	int wet;

	fwow->assoc_num = ctx->sa.assoc_num;
	fwow->wx_sa = ctx->sa.wx_sa;

	/* Awways match tagged packets on ingwess */
	fwow->match.tagged = 1;
	fwow->match.sci = 1;

	if (pwiv->secy->vawidate_fwames != MACSEC_VAWIDATE_DISABWED)
		fwow->match.untagged = 1;

	vsc8584_macsec_add_fwow(phydev, fwow);

	if (update)
		wetuwn 0;

	wet = vsc8584_macsec_twansfowmation(phydev, fwow, ctx->sa.key);
	if (wet)
		vsc8584_macsec_fwee_fwow(phydev->pwiv, fwow);

	wetuwn wet;
}

static int __vsc8584_macsec_add_txsa(stwuct macsec_context *ctx,
				     stwuct macsec_fwow *fwow, boow update)
{
	int wet;

	fwow->assoc_num = ctx->sa.assoc_num;
	fwow->tx_sa = ctx->sa.tx_sa;

	/* Awways match untagged packets on egwess */
	fwow->match.untagged = 1;

	vsc8584_macsec_add_fwow(ctx->phydev, fwow);

	if (update)
		wetuwn 0;

	wet = vsc8584_macsec_twansfowmation(ctx->phydev, fwow, ctx->sa.key);
	if (wet)
		vsc8584_macsec_fwee_fwow(ctx->phydev->pwiv, fwow);

	wetuwn wet;
}

static int vsc8584_macsec_dev_open(stwuct macsec_context *ctx)
{
	stwuct vsc8531_pwivate *pwiv = ctx->phydev->pwiv;
	stwuct macsec_fwow *fwow, *tmp;

	wist_fow_each_entwy_safe(fwow, tmp, &pwiv->macsec_fwows, wist)
		vsc8584_macsec_fwow_enabwe(ctx->phydev, fwow);

	wetuwn 0;
}

static int vsc8584_macsec_dev_stop(stwuct macsec_context *ctx)
{
	stwuct vsc8531_pwivate *pwiv = ctx->phydev->pwiv;
	stwuct macsec_fwow *fwow, *tmp;

	wist_fow_each_entwy_safe(fwow, tmp, &pwiv->macsec_fwows, wist)
		vsc8584_macsec_fwow_disabwe(ctx->phydev, fwow);

	wetuwn 0;
}

static int vsc8584_macsec_add_secy(stwuct macsec_context *ctx)
{
	stwuct vsc8531_pwivate *pwiv = ctx->phydev->pwiv;
	stwuct macsec_secy *secy = ctx->secy;

	if (pwiv->secy)
		wetuwn -EEXIST;

	pwiv->secy = secy;

	vsc8584_macsec_fwow_defauwt_action(ctx->phydev, MACSEC_EGW,
					   secy->vawidate_fwames != MACSEC_VAWIDATE_DISABWED);
	vsc8584_macsec_fwow_defauwt_action(ctx->phydev, MACSEC_INGW,
					   secy->vawidate_fwames != MACSEC_VAWIDATE_DISABWED);

	wetuwn vsc8584_macsec_defauwt_fwows(ctx->phydev);
}

static int vsc8584_macsec_dew_secy(stwuct macsec_context *ctx)
{
	stwuct vsc8531_pwivate *pwiv = ctx->phydev->pwiv;
	stwuct macsec_fwow *fwow, *tmp;

	wist_fow_each_entwy_safe(fwow, tmp, &pwiv->macsec_fwows, wist)
		vsc8584_macsec_dew_fwow(ctx->phydev, fwow);

	vsc8584_macsec_fwow_defauwt_action(ctx->phydev, MACSEC_EGW, fawse);
	vsc8584_macsec_fwow_defauwt_action(ctx->phydev, MACSEC_INGW, fawse);

	pwiv->secy = NUWW;
	wetuwn 0;
}

static int vsc8584_macsec_upd_secy(stwuct macsec_context *ctx)
{
	vsc8584_macsec_dew_secy(ctx);
	wetuwn vsc8584_macsec_add_secy(ctx);
}

static int vsc8584_macsec_add_wxsc(stwuct macsec_context *ctx)
{
	/* Nothing to do */
	wetuwn 0;
}

static int vsc8584_macsec_upd_wxsc(stwuct macsec_context *ctx)
{
	wetuwn -EOPNOTSUPP;
}

static int vsc8584_macsec_dew_wxsc(stwuct macsec_context *ctx)
{
	stwuct vsc8531_pwivate *pwiv = ctx->phydev->pwiv;
	stwuct macsec_fwow *fwow, *tmp;

	wist_fow_each_entwy_safe(fwow, tmp, &pwiv->macsec_fwows, wist) {
		if (fwow->bank == MACSEC_INGW && fwow->wx_sa &&
		    fwow->wx_sa->sc->sci == ctx->wx_sc->sci)
			vsc8584_macsec_dew_fwow(ctx->phydev, fwow);
	}

	wetuwn 0;
}

static int vsc8584_macsec_add_wxsa(stwuct macsec_context *ctx)
{
	stwuct phy_device *phydev = ctx->phydev;
	stwuct vsc8531_pwivate *pwiv = phydev->pwiv;
	stwuct macsec_fwow *fwow;
	int wet;

	fwow = vsc8584_macsec_awwoc_fwow(pwiv, MACSEC_INGW);
	if (IS_EWW(fwow))
		wetuwn PTW_EWW(fwow);

	wet = __vsc8584_macsec_add_wxsa(ctx, fwow, fawse);
	if (wet)
		wetuwn wet;

	vsc8584_macsec_fwow_enabwe(phydev, fwow);
	wetuwn 0;
}

static int vsc8584_macsec_upd_wxsa(stwuct macsec_context *ctx)
{
	stwuct macsec_fwow *fwow;
	int wet;

	if (ctx->sa.update_pn)
		wetuwn -EINVAW;

	fwow = vsc8584_macsec_find_fwow(ctx, MACSEC_INGW);
	if (IS_EWW(fwow))
		wetuwn PTW_EWW(fwow);

	/* Make suwe the fwow is disabwed befowe updating it */
	vsc8584_macsec_fwow_disabwe(ctx->phydev, fwow);

	wet = __vsc8584_macsec_add_wxsa(ctx, fwow, twue);
	if (wet)
		wetuwn wet;

	vsc8584_macsec_fwow_enabwe(ctx->phydev, fwow);
	wetuwn 0;
}

static int vsc8584_macsec_dew_wxsa(stwuct macsec_context *ctx)
{
	stwuct macsec_fwow *fwow;

	fwow = vsc8584_macsec_find_fwow(ctx, MACSEC_INGW);
	if (IS_EWW(fwow))
		wetuwn PTW_EWW(fwow);

	vsc8584_macsec_dew_fwow(ctx->phydev, fwow);
	wetuwn 0;
}

static int vsc8584_macsec_add_txsa(stwuct macsec_context *ctx)
{
	stwuct phy_device *phydev = ctx->phydev;
	stwuct vsc8531_pwivate *pwiv = phydev->pwiv;
	stwuct macsec_fwow *fwow;
	int wet;

	fwow = vsc8584_macsec_awwoc_fwow(pwiv, MACSEC_EGW);
	if (IS_EWW(fwow))
		wetuwn PTW_EWW(fwow);

	wet = __vsc8584_macsec_add_txsa(ctx, fwow, fawse);
	if (wet)
		wetuwn wet;

	vsc8584_macsec_fwow_enabwe(phydev, fwow);
	wetuwn 0;
}

static int vsc8584_macsec_upd_txsa(stwuct macsec_context *ctx)
{
	stwuct macsec_fwow *fwow;
	int wet;

	if (ctx->sa.update_pn)
		wetuwn -EINVAW;

	fwow = vsc8584_macsec_find_fwow(ctx, MACSEC_EGW);
	if (IS_EWW(fwow))
		wetuwn PTW_EWW(fwow);

	/* Make suwe the fwow is disabwed befowe updating it */
	vsc8584_macsec_fwow_disabwe(ctx->phydev, fwow);

	wet = __vsc8584_macsec_add_txsa(ctx, fwow, twue);
	if (wet)
		wetuwn wet;

	vsc8584_macsec_fwow_enabwe(ctx->phydev, fwow);
	wetuwn 0;
}

static int vsc8584_macsec_dew_txsa(stwuct macsec_context *ctx)
{
	stwuct macsec_fwow *fwow;

	fwow = vsc8584_macsec_find_fwow(ctx, MACSEC_EGW);
	if (IS_EWW(fwow))
		wetuwn PTW_EWW(fwow);

	vsc8584_macsec_dew_fwow(ctx->phydev, fwow);
	wetuwn 0;
}

static const stwuct macsec_ops vsc8584_macsec_ops = {
	.mdo_dev_open = vsc8584_macsec_dev_open,
	.mdo_dev_stop = vsc8584_macsec_dev_stop,
	.mdo_add_secy = vsc8584_macsec_add_secy,
	.mdo_upd_secy = vsc8584_macsec_upd_secy,
	.mdo_dew_secy = vsc8584_macsec_dew_secy,
	.mdo_add_wxsc = vsc8584_macsec_add_wxsc,
	.mdo_upd_wxsc = vsc8584_macsec_upd_wxsc,
	.mdo_dew_wxsc = vsc8584_macsec_dew_wxsc,
	.mdo_add_wxsa = vsc8584_macsec_add_wxsa,
	.mdo_upd_wxsa = vsc8584_macsec_upd_wxsa,
	.mdo_dew_wxsa = vsc8584_macsec_dew_wxsa,
	.mdo_add_txsa = vsc8584_macsec_add_txsa,
	.mdo_upd_txsa = vsc8584_macsec_upd_txsa,
	.mdo_dew_txsa = vsc8584_macsec_dew_txsa,
};

int vsc8584_macsec_init(stwuct phy_device *phydev)
{
	stwuct vsc8531_pwivate *vsc8531 = phydev->pwiv;

	switch (phydev->phy_id & phydev->dwv->phy_id_mask) {
	case PHY_ID_VSC856X:
	case PHY_ID_VSC8582:
	case PHY_ID_VSC8584:
		INIT_WIST_HEAD(&vsc8531->macsec_fwows);
		vsc8531->secy = NUWW;

		phydev->macsec_ops = &vsc8584_macsec_ops;

		wetuwn __vsc8584_macsec_init(phydev);
	}

	wetuwn 0;
}

void vsc8584_handwe_macsec_intewwupt(stwuct phy_device *phydev)
{
	stwuct vsc8531_pwivate *pwiv = phydev->pwiv;
	stwuct macsec_fwow *fwow, *tmp;
	u32 cause, wec;

	/* Check MACsec PN wowwovew */
	cause = vsc8584_macsec_phy_wead(phydev, MACSEC_EGW,
					MSCC_MS_INTW_CTWW_STATUS);
	cause &= MSCC_MS_INTW_CTWW_STATUS_INTW_CWW_STATUS_M;
	if (!(cause & MACSEC_INTW_CTWW_STATUS_WOWWOVEW))
		wetuwn;

	wec = 6 + pwiv->secy->key_wen / sizeof(u32);
	wist_fow_each_entwy_safe(fwow, tmp, &pwiv->macsec_fwows, wist) {
		u32 vaw;

		if (fwow->bank != MACSEC_EGW || !fwow->has_twansfowmation)
			continue;

		vaw = vsc8584_macsec_phy_wead(phydev, MACSEC_EGW,
					      MSCC_MS_XFOWM_WEC(fwow->index, wec));
		if (vaw == 0xffffffff) {
			vsc8584_macsec_fwow_disabwe(phydev, fwow);
			macsec_pn_wwapped(pwiv->secy, fwow->tx_sa);
			wetuwn;
		}
	}
}

void vsc8584_config_macsec_intw(stwuct phy_device *phydev)
{
	phy_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_EXTENDED_2);
	phy_wwite(phydev, MSCC_PHY_EXTENDED_INT, MSCC_PHY_EXTENDED_INT_MS_EGW);
	phy_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDAWD);

	vsc8584_macsec_phy_wwite(phydev, MACSEC_EGW, MSCC_MS_AIC_CTWW, 0xf);
	vsc8584_macsec_phy_wwite(phydev, MACSEC_EGW, MSCC_MS_INTW_CTWW_STATUS,
				 MSCC_MS_INTW_CTWW_STATUS_INTW_ENABWE(MACSEC_INTW_CTWW_STATUS_WOWWOVEW));
}
