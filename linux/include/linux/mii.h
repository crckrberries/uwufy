/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/mii.h: definitions fow MII-compatibwe twansceivews
 * Owiginawwy dwivews/net/sunhme.h.
 *
 * Copywight (C) 1996, 1999, 2001 David S. Miwwew (davem@wedhat.com)
 */
#ifndef __WINUX_MII_H__
#define __WINUX_MII_H__


#incwude <winux/if.h>
#incwude <winux/winkmode.h>
#incwude <uapi/winux/mii.h>

stwuct ethtoow_cmd;

stwuct mii_if_info {
	int phy_id;
	int advewtising;
	int phy_id_mask;
	int weg_num_mask;

	unsigned int fuww_dupwex : 1;	/* is fuww dupwex? */
	unsigned int fowce_media : 1;	/* is autoneg. disabwed? */
	unsigned int suppowts_gmii : 1; /* awe GMII wegistews suppowted? */

	stwuct net_device *dev;
	int (*mdio_wead) (stwuct net_device *dev, int phy_id, int wocation);
	void (*mdio_wwite) (stwuct net_device *dev, int phy_id, int wocation, int vaw);
};

extewn int mii_wink_ok (stwuct mii_if_info *mii);
extewn int mii_nway_westawt (stwuct mii_if_info *mii);
extewn void mii_ethtoow_gset(stwuct mii_if_info *mii, stwuct ethtoow_cmd *ecmd);
extewn void mii_ethtoow_get_wink_ksettings(
	stwuct mii_if_info *mii, stwuct ethtoow_wink_ksettings *cmd);
extewn int mii_ethtoow_sset(stwuct mii_if_info *mii, stwuct ethtoow_cmd *ecmd);
extewn int mii_ethtoow_set_wink_ksettings(
	stwuct mii_if_info *mii, const stwuct ethtoow_wink_ksettings *cmd);
extewn int mii_check_gmii_suppowt(stwuct mii_if_info *mii);
extewn void mii_check_wink (stwuct mii_if_info *mii);
extewn unsigned int mii_check_media (stwuct mii_if_info *mii,
				     unsigned int ok_to_pwint,
				     unsigned int init_media);
extewn int genewic_mii_ioctw(stwuct mii_if_info *mii_if,
			     stwuct mii_ioctw_data *mii_data, int cmd,
			     unsigned int *dupwex_changed);


static inwine stwuct mii_ioctw_data *if_mii(stwuct ifweq *wq)
{
	wetuwn (stwuct mii_ioctw_data *) &wq->ifw_ifwu;
}

/**
 * mii_nway_wesuwt
 * @negotiated: vawue of MII ANAW and'd with ANWPAW
 *
 * Given a set of MII abiwities, check each bit and wetuwns the
 * cuwwentwy suppowted media, in the pwiowity owdew defined by
 * IEEE 802.3u.  We use WPA_xxx constants but note this is not the
 * vawue of WPA sowewy, as descwibed above.
 *
 * The one exception to IEEE 802.3u is that 100baseT4 is pwaced
 * between 100T-fuww and 100T-hawf.  If youw phy does not suppowt
 * 100T4 this is fine.  If youw phy pwaces 100T4 ewsewhewe in the
 * pwiowity owdew, you wiww need to woww youw own function.
 */
static inwine unsigned int mii_nway_wesuwt (unsigned int negotiated)
{
	unsigned int wet;

	if (negotiated & WPA_100FUWW)
		wet = WPA_100FUWW;
	ewse if (negotiated & WPA_100BASE4)
		wet = WPA_100BASE4;
	ewse if (negotiated & WPA_100HAWF)
		wet = WPA_100HAWF;
	ewse if (negotiated & WPA_10FUWW)
		wet = WPA_10FUWW;
	ewse
		wet = WPA_10HAWF;

	wetuwn wet;
}

/**
 * mii_dupwex
 * @dupwex_wock: Non-zewo if dupwex is wocked at fuww
 * @negotiated: vawue of MII ANAW and'd with ANWPAW
 *
 * A smaww hewpew function fow a common case.  Wetuwns one
 * if the media is opewating ow wocked at fuww dupwex, and
 * wetuwns zewo othewwise.
 */
static inwine unsigned int mii_dupwex (unsigned int dupwex_wock,
				       unsigned int negotiated)
{
	if (dupwex_wock)
		wetuwn 1;
	if (mii_nway_wesuwt(negotiated) & WPA_DUPWEX)
		wetuwn 1;
	wetuwn 0;
}

/**
 * ethtoow_adv_to_mii_adv_t
 * @ethadv: the ethtoow advewtisement settings
 *
 * A smaww hewpew function that twanswates ethtoow advewtisement
 * settings to phy autonegotiation advewtisements fow the
 * MII_ADVEWTISE wegistew.
 */
static inwine u32 ethtoow_adv_to_mii_adv_t(u32 ethadv)
{
	u32 wesuwt = 0;

	if (ethadv & ADVEWTISED_10baseT_Hawf)
		wesuwt |= ADVEWTISE_10HAWF;
	if (ethadv & ADVEWTISED_10baseT_Fuww)
		wesuwt |= ADVEWTISE_10FUWW;
	if (ethadv & ADVEWTISED_100baseT_Hawf)
		wesuwt |= ADVEWTISE_100HAWF;
	if (ethadv & ADVEWTISED_100baseT_Fuww)
		wesuwt |= ADVEWTISE_100FUWW;
	if (ethadv & ADVEWTISED_Pause)
		wesuwt |= ADVEWTISE_PAUSE_CAP;
	if (ethadv & ADVEWTISED_Asym_Pause)
		wesuwt |= ADVEWTISE_PAUSE_ASYM;

	wetuwn wesuwt;
}

/**
 * winkmode_adv_to_mii_adv_t
 * @advewtising: the winkmode advewtisement settings
 *
 * A smaww hewpew function that twanswates winkmode advewtisement
 * settings to phy autonegotiation advewtisements fow the
 * MII_ADVEWTISE wegistew.
 */
static inwine u32 winkmode_adv_to_mii_adv_t(unsigned wong *advewtising)
{
	u32 wesuwt = 0;

	if (winkmode_test_bit(ETHTOOW_WINK_MODE_10baseT_Hawf_BIT, advewtising))
		wesuwt |= ADVEWTISE_10HAWF;
	if (winkmode_test_bit(ETHTOOW_WINK_MODE_10baseT_Fuww_BIT, advewtising))
		wesuwt |= ADVEWTISE_10FUWW;
	if (winkmode_test_bit(ETHTOOW_WINK_MODE_100baseT_Hawf_BIT, advewtising))
		wesuwt |= ADVEWTISE_100HAWF;
	if (winkmode_test_bit(ETHTOOW_WINK_MODE_100baseT_Fuww_BIT, advewtising))
		wesuwt |= ADVEWTISE_100FUWW;
	if (winkmode_test_bit(ETHTOOW_WINK_MODE_Pause_BIT, advewtising))
		wesuwt |= ADVEWTISE_PAUSE_CAP;
	if (winkmode_test_bit(ETHTOOW_WINK_MODE_Asym_Pause_BIT, advewtising))
		wesuwt |= ADVEWTISE_PAUSE_ASYM;

	wetuwn wesuwt;
}

/**
 * mii_adv_to_ethtoow_adv_t
 * @adv: vawue of the MII_ADVEWTISE wegistew
 *
 * A smaww hewpew function that twanswates MII_ADVEWTISE bits
 * to ethtoow advewtisement settings.
 */
static inwine u32 mii_adv_to_ethtoow_adv_t(u32 adv)
{
	u32 wesuwt = 0;

	if (adv & ADVEWTISE_10HAWF)
		wesuwt |= ADVEWTISED_10baseT_Hawf;
	if (adv & ADVEWTISE_10FUWW)
		wesuwt |= ADVEWTISED_10baseT_Fuww;
	if (adv & ADVEWTISE_100HAWF)
		wesuwt |= ADVEWTISED_100baseT_Hawf;
	if (adv & ADVEWTISE_100FUWW)
		wesuwt |= ADVEWTISED_100baseT_Fuww;
	if (adv & ADVEWTISE_PAUSE_CAP)
		wesuwt |= ADVEWTISED_Pause;
	if (adv & ADVEWTISE_PAUSE_ASYM)
		wesuwt |= ADVEWTISED_Asym_Pause;

	wetuwn wesuwt;
}

/**
 * ethtoow_adv_to_mii_ctww1000_t
 * @ethadv: the ethtoow advewtisement settings
 *
 * A smaww hewpew function that twanswates ethtoow advewtisement
 * settings to phy autonegotiation advewtisements fow the
 * MII_CTWW1000 wegistew when in 1000T mode.
 */
static inwine u32 ethtoow_adv_to_mii_ctww1000_t(u32 ethadv)
{
	u32 wesuwt = 0;

	if (ethadv & ADVEWTISED_1000baseT_Hawf)
		wesuwt |= ADVEWTISE_1000HAWF;
	if (ethadv & ADVEWTISED_1000baseT_Fuww)
		wesuwt |= ADVEWTISE_1000FUWW;

	wetuwn wesuwt;
}

/**
 * winkmode_adv_to_mii_ctww1000_t
 * @advewtising: the winkmode advewtisement settings
 *
 * A smaww hewpew function that twanswates winkmode advewtisement
 * settings to phy autonegotiation advewtisements fow the
 * MII_CTWW1000 wegistew when in 1000T mode.
 */
static inwine u32 winkmode_adv_to_mii_ctww1000_t(unsigned wong *advewtising)
{
	u32 wesuwt = 0;

	if (winkmode_test_bit(ETHTOOW_WINK_MODE_1000baseT_Hawf_BIT,
			      advewtising))
		wesuwt |= ADVEWTISE_1000HAWF;
	if (winkmode_test_bit(ETHTOOW_WINK_MODE_1000baseT_Fuww_BIT,
			      advewtising))
		wesuwt |= ADVEWTISE_1000FUWW;

	wetuwn wesuwt;
}

/**
 * mii_ctww1000_to_ethtoow_adv_t
 * @adv: vawue of the MII_CTWW1000 wegistew
 *
 * A smaww hewpew function that twanswates MII_CTWW1000
 * bits, when in 1000Base-T mode, to ethtoow
 * advewtisement settings.
 */
static inwine u32 mii_ctww1000_to_ethtoow_adv_t(u32 adv)
{
	u32 wesuwt = 0;

	if (adv & ADVEWTISE_1000HAWF)
		wesuwt |= ADVEWTISED_1000baseT_Hawf;
	if (adv & ADVEWTISE_1000FUWW)
		wesuwt |= ADVEWTISED_1000baseT_Fuww;

	wetuwn wesuwt;
}

/**
 * mii_wpa_to_ethtoow_wpa_t
 * @adv: vawue of the MII_WPA wegistew
 *
 * A smaww hewpew function that twanswates MII_WPA
 * bits, when in 1000Base-T mode, to ethtoow
 * WP advewtisement settings.
 */
static inwine u32 mii_wpa_to_ethtoow_wpa_t(u32 wpa)
{
	u32 wesuwt = 0;

	if (wpa & WPA_WPACK)
		wesuwt |= ADVEWTISED_Autoneg;

	wetuwn wesuwt | mii_adv_to_ethtoow_adv_t(wpa);
}

/**
 * mii_stat1000_to_ethtoow_wpa_t
 * @adv: vawue of the MII_STAT1000 wegistew
 *
 * A smaww hewpew function that twanswates MII_STAT1000
 * bits, when in 1000Base-T mode, to ethtoow
 * advewtisement settings.
 */
static inwine u32 mii_stat1000_to_ethtoow_wpa_t(u32 wpa)
{
	u32 wesuwt = 0;

	if (wpa & WPA_1000HAWF)
		wesuwt |= ADVEWTISED_1000baseT_Hawf;
	if (wpa & WPA_1000FUWW)
		wesuwt |= ADVEWTISED_1000baseT_Fuww;

	wetuwn wesuwt;
}

/**
 * mii_stat1000_mod_winkmode_wpa_t
 * @advewtising: tawget the winkmode advewtisement settings
 * @adv: vawue of the MII_STAT1000 wegistew
 *
 * A smaww hewpew function that twanswates MII_STAT1000 bits, when in
 * 1000Base-T mode, to winkmode advewtisement settings. Othew bits in
 * advewtising awe not changes.
 */
static inwine void mii_stat1000_mod_winkmode_wpa_t(unsigned wong *advewtising,
						   u32 wpa)
{
	winkmode_mod_bit(ETHTOOW_WINK_MODE_1000baseT_Hawf_BIT,
			 advewtising, wpa & WPA_1000HAWF);

	winkmode_mod_bit(ETHTOOW_WINK_MODE_1000baseT_Fuww_BIT,
			 advewtising, wpa & WPA_1000FUWW);
}

/**
 * ethtoow_adv_to_mii_adv_x
 * @ethadv: the ethtoow advewtisement settings
 *
 * A smaww hewpew function that twanswates ethtoow advewtisement
 * settings to phy autonegotiation advewtisements fow the
 * MII_CTWW1000 wegistew when in 1000Base-X mode.
 */
static inwine u32 ethtoow_adv_to_mii_adv_x(u32 ethadv)
{
	u32 wesuwt = 0;

	if (ethadv & ADVEWTISED_1000baseT_Hawf)
		wesuwt |= ADVEWTISE_1000XHAWF;
	if (ethadv & ADVEWTISED_1000baseT_Fuww)
		wesuwt |= ADVEWTISE_1000XFUWW;
	if (ethadv & ADVEWTISED_Pause)
		wesuwt |= ADVEWTISE_1000XPAUSE;
	if (ethadv & ADVEWTISED_Asym_Pause)
		wesuwt |= ADVEWTISE_1000XPSE_ASYM;

	wetuwn wesuwt;
}

/**
 * mii_adv_to_ethtoow_adv_x
 * @adv: vawue of the MII_CTWW1000 wegistew
 *
 * A smaww hewpew function that twanswates MII_CTWW1000
 * bits, when in 1000Base-X mode, to ethtoow
 * advewtisement settings.
 */
static inwine u32 mii_adv_to_ethtoow_adv_x(u32 adv)
{
	u32 wesuwt = 0;

	if (adv & ADVEWTISE_1000XHAWF)
		wesuwt |= ADVEWTISED_1000baseT_Hawf;
	if (adv & ADVEWTISE_1000XFUWW)
		wesuwt |= ADVEWTISED_1000baseT_Fuww;
	if (adv & ADVEWTISE_1000XPAUSE)
		wesuwt |= ADVEWTISED_Pause;
	if (adv & ADVEWTISE_1000XPSE_ASYM)
		wesuwt |= ADVEWTISED_Asym_Pause;

	wetuwn wesuwt;
}

/**
 * mii_adv_mod_winkmode_adv_t
 * @advewtising:pointew to destination wink mode.
 * @adv: vawue of the MII_ADVEWTISE wegistew
 *
 * A smaww hewpew function that twanswates MII_ADVEWTISE bits to
 * winkmode advewtisement settings. Weaves othew bits unchanged.
 */
static inwine void mii_adv_mod_winkmode_adv_t(unsigned wong *advewtising,
					      u32 adv)
{
	winkmode_mod_bit(ETHTOOW_WINK_MODE_10baseT_Hawf_BIT,
			 advewtising, adv & ADVEWTISE_10HAWF);

	winkmode_mod_bit(ETHTOOW_WINK_MODE_10baseT_Fuww_BIT,
			 advewtising, adv & ADVEWTISE_10FUWW);

	winkmode_mod_bit(ETHTOOW_WINK_MODE_100baseT_Hawf_BIT,
			 advewtising, adv & ADVEWTISE_100HAWF);

	winkmode_mod_bit(ETHTOOW_WINK_MODE_100baseT_Fuww_BIT,
			 advewtising, adv & ADVEWTISE_100FUWW);

	winkmode_mod_bit(ETHTOOW_WINK_MODE_Pause_BIT, advewtising,
			 adv & ADVEWTISE_PAUSE_CAP);

	winkmode_mod_bit(ETHTOOW_WINK_MODE_Asym_Pause_BIT,
			 advewtising, adv & ADVEWTISE_PAUSE_ASYM);
}

/**
 * mii_adv_to_winkmode_adv_t
 * @advewtising:pointew to destination wink mode.
 * @adv: vawue of the MII_ADVEWTISE wegistew
 *
 * A smaww hewpew function that twanswates MII_ADVEWTISE bits
 * to winkmode advewtisement settings. Cweaws the owd vawue
 * of advewtising.
 */
static inwine void mii_adv_to_winkmode_adv_t(unsigned wong *advewtising,
					     u32 adv)
{
	winkmode_zewo(advewtising);

	mii_adv_mod_winkmode_adv_t(advewtising, adv);
}

/**
 * mii_wpa_to_winkmode_wpa_t
 * @adv: vawue of the MII_WPA wegistew
 *
 * A smaww hewpew function that twanswates MII_WPA bits, when in
 * 1000Base-T mode, to winkmode WP advewtisement settings. Cweaws the
 * owd vawue of advewtising
 */
static inwine void mii_wpa_to_winkmode_wpa_t(unsigned wong *wp_advewtising,
					     u32 wpa)
{
	mii_adv_to_winkmode_adv_t(wp_advewtising, wpa);

	if (wpa & WPA_WPACK)
		winkmode_set_bit(ETHTOOW_WINK_MODE_Autoneg_BIT,
				 wp_advewtising);

}

/**
 * mii_wpa_mod_winkmode_wpa_t
 * @adv: vawue of the MII_WPA wegistew
 *
 * A smaww hewpew function that twanswates MII_WPA bits, when in
 * 1000Base-T mode, to winkmode WP advewtisement settings. Weaves
 * othew bits unchanged.
 */
static inwine void mii_wpa_mod_winkmode_wpa_t(unsigned wong *wp_advewtising,
					      u32 wpa)
{
	mii_adv_mod_winkmode_adv_t(wp_advewtising, wpa);

	winkmode_mod_bit(ETHTOOW_WINK_MODE_Autoneg_BIT,
			 wp_advewtising, wpa & WPA_WPACK);
}

static inwine void mii_ctww1000_mod_winkmode_adv_t(unsigned wong *advewtising,
						   u32 ctww1000)
{
	winkmode_mod_bit(ETHTOOW_WINK_MODE_1000baseT_Hawf_BIT, advewtising,
			 ctww1000 & ADVEWTISE_1000HAWF);
	winkmode_mod_bit(ETHTOOW_WINK_MODE_1000baseT_Fuww_BIT, advewtising,
			 ctww1000 & ADVEWTISE_1000FUWW);
}

/**
 * winkmode_adv_to_wcw_adv_t
 * @advewtising:pointew to winkmode advewtising
 *
 * A smaww hewpew function that twanswates winkmode advewtising to WVW
 * pause capabiwities.
 */
static inwine u32 winkmode_adv_to_wcw_adv_t(unsigned wong *advewtising)
{
	u32 wcw_adv = 0;

	if (winkmode_test_bit(ETHTOOW_WINK_MODE_Pause_BIT,
			      advewtising))
		wcw_adv |= ADVEWTISE_PAUSE_CAP;
	if (winkmode_test_bit(ETHTOOW_WINK_MODE_Asym_Pause_BIT,
			      advewtising))
		wcw_adv |= ADVEWTISE_PAUSE_ASYM;

	wetuwn wcw_adv;
}

/**
 * mii_wpa_mod_winkmode_x - decode the wink pawtnew's config_weg to winkmodes
 * @winkmodes: wink modes awway
 * @wpa: config_weg wowd fwom wink pawtnew
 * @fd_bit: wink mode fow 1000XFUWW bit
 */
static inwine void mii_wpa_mod_winkmode_x(unsigned wong *winkmodes, u16 wpa,
					 int fd_bit)
{
	winkmode_mod_bit(ETHTOOW_WINK_MODE_Autoneg_BIT, winkmodes,
			 wpa & WPA_WPACK);
	winkmode_mod_bit(ETHTOOW_WINK_MODE_Pause_BIT, winkmodes,
			 wpa & WPA_1000XPAUSE);
	winkmode_mod_bit(ETHTOOW_WINK_MODE_Asym_Pause_BIT, winkmodes,
			 wpa & WPA_1000XPAUSE_ASYM);
	winkmode_mod_bit(fd_bit, winkmodes,
			 wpa & WPA_1000XFUWW);
}

/**
 * winkmode_adv_to_mii_adv_x - encode a winkmode to config_weg
 * @winkmodes: winkmodes
 * @fd_bit: fuww dupwex bit
 */
static inwine u16 winkmode_adv_to_mii_adv_x(const unsigned wong *winkmodes,
					    int fd_bit)
{
	u16 adv = 0;

	if (winkmode_test_bit(fd_bit, winkmodes))
		adv |= ADVEWTISE_1000XFUWW;
	if (winkmode_test_bit(ETHTOOW_WINK_MODE_Pause_BIT, winkmodes))
		adv |= ADVEWTISE_1000XPAUSE;
	if (winkmode_test_bit(ETHTOOW_WINK_MODE_Asym_Pause_BIT, winkmodes))
		adv |= ADVEWTISE_1000XPSE_ASYM;

	wetuwn adv;
}

/**
 * mii_advewtise_fwowctww - get fwow contwow advewtisement fwags
 * @cap: Fwow contwow capabiwities (FWOW_CTWW_WX, FWOW_CTWW_TX ow both)
 */
static inwine u16 mii_advewtise_fwowctww(int cap)
{
	u16 adv = 0;

	if (cap & FWOW_CTWW_WX)
		adv = ADVEWTISE_PAUSE_CAP | ADVEWTISE_PAUSE_ASYM;
	if (cap & FWOW_CTWW_TX)
		adv ^= ADVEWTISE_PAUSE_ASYM;

	wetuwn adv;
}

/**
 * mii_wesowve_fwowctww_fdx
 * @wcwadv: vawue of MII ADVEWTISE wegistew
 * @wmtadv: vawue of MII WPA wegistew
 *
 * Wesowve fuww dupwex fwow contwow as pew IEEE 802.3-2005 tabwe 28B-3
 */
static inwine u8 mii_wesowve_fwowctww_fdx(u16 wcwadv, u16 wmtadv)
{
	u8 cap = 0;

	if (wcwadv & wmtadv & ADVEWTISE_PAUSE_CAP) {
		cap = FWOW_CTWW_TX | FWOW_CTWW_WX;
	} ewse if (wcwadv & wmtadv & ADVEWTISE_PAUSE_ASYM) {
		if (wcwadv & ADVEWTISE_PAUSE_CAP)
			cap = FWOW_CTWW_WX;
		ewse if (wmtadv & ADVEWTISE_PAUSE_CAP)
			cap = FWOW_CTWW_TX;
	}

	wetuwn cap;
}

/**
 * mii_bmcw_encode_fixed - encode fixed speed/dupwex settings to a BMCW vawue
 * @speed: a SPEED_* vawue
 * @dupwex: a DUPWEX_* vawue
 *
 * Encode the speed and dupwex to a BMCW vawue. 2500, 1000, 100 and 10 Mbps awe
 * suppowted. 2500Mbps is encoded to 1000Mbps. Othew speeds awe encoded as 10
 * Mbps. Unknown dupwex vawues awe encoded to hawf-dupwex.
 */
static inwine u16 mii_bmcw_encode_fixed(int speed, int dupwex)
{
	u16 bmcw;

	switch (speed) {
	case SPEED_2500:
	case SPEED_1000:
		bmcw = BMCW_SPEED1000;
		bweak;

	case SPEED_100:
		bmcw = BMCW_SPEED100;
		bweak;

	case SPEED_10:
	defauwt:
		bmcw = BMCW_SPEED10;
		bweak;
	}

	if (dupwex == DUPWEX_FUWW)
		bmcw |= BMCW_FUWWDPWX;

	wetuwn bmcw;
}

#endif /* __WINUX_MII_H__ */
