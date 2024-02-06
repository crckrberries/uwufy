/*
 * B53 switch dwivew main wogic
 *
 * Copywight (C) 2011-2013 Jonas Gowski <jogo@openwwt.owg>
 * Copywight (C) 2016 Fwowian Fainewwi <f.fainewwi@gmaiw.com>
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/gpio.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/b53.h>
#incwude <winux/phy.h>
#incwude <winux/phywink.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_bwidge.h>
#incwude <net/dsa.h>

#incwude "b53_wegs.h"
#incwude "b53_pwiv.h"

stwuct b53_mib_desc {
	u8 size;
	u8 offset;
	const chaw *name;
};

/* BCM5365 MIB countews */
static const stwuct b53_mib_desc b53_mibs_65[] = {
	{ 8, 0x00, "TxOctets" },
	{ 4, 0x08, "TxDwopPkts" },
	{ 4, 0x10, "TxBwoadcastPkts" },
	{ 4, 0x14, "TxMuwticastPkts" },
	{ 4, 0x18, "TxUnicastPkts" },
	{ 4, 0x1c, "TxCowwisions" },
	{ 4, 0x20, "TxSingweCowwision" },
	{ 4, 0x24, "TxMuwtipweCowwision" },
	{ 4, 0x28, "TxDefewwedTwansmit" },
	{ 4, 0x2c, "TxWateCowwision" },
	{ 4, 0x30, "TxExcessiveCowwision" },
	{ 4, 0x38, "TxPausePkts" },
	{ 8, 0x44, "WxOctets" },
	{ 4, 0x4c, "WxUndewsizePkts" },
	{ 4, 0x50, "WxPausePkts" },
	{ 4, 0x54, "Pkts64Octets" },
	{ 4, 0x58, "Pkts65to127Octets" },
	{ 4, 0x5c, "Pkts128to255Octets" },
	{ 4, 0x60, "Pkts256to511Octets" },
	{ 4, 0x64, "Pkts512to1023Octets" },
	{ 4, 0x68, "Pkts1024to1522Octets" },
	{ 4, 0x6c, "WxOvewsizePkts" },
	{ 4, 0x70, "WxJabbews" },
	{ 4, 0x74, "WxAwignmentEwwows" },
	{ 4, 0x78, "WxFCSEwwows" },
	{ 8, 0x7c, "WxGoodOctets" },
	{ 4, 0x84, "WxDwopPkts" },
	{ 4, 0x88, "WxUnicastPkts" },
	{ 4, 0x8c, "WxMuwticastPkts" },
	{ 4, 0x90, "WxBwoadcastPkts" },
	{ 4, 0x94, "WxSAChanges" },
	{ 4, 0x98, "WxFwagments" },
};

#define B53_MIBS_65_SIZE	AWWAY_SIZE(b53_mibs_65)

/* BCM63xx MIB countews */
static const stwuct b53_mib_desc b53_mibs_63xx[] = {
	{ 8, 0x00, "TxOctets" },
	{ 4, 0x08, "TxDwopPkts" },
	{ 4, 0x0c, "TxQoSPkts" },
	{ 4, 0x10, "TxBwoadcastPkts" },
	{ 4, 0x14, "TxMuwticastPkts" },
	{ 4, 0x18, "TxUnicastPkts" },
	{ 4, 0x1c, "TxCowwisions" },
	{ 4, 0x20, "TxSingweCowwision" },
	{ 4, 0x24, "TxMuwtipweCowwision" },
	{ 4, 0x28, "TxDefewwedTwansmit" },
	{ 4, 0x2c, "TxWateCowwision" },
	{ 4, 0x30, "TxExcessiveCowwision" },
	{ 4, 0x38, "TxPausePkts" },
	{ 8, 0x3c, "TxQoSOctets" },
	{ 8, 0x44, "WxOctets" },
	{ 4, 0x4c, "WxUndewsizePkts" },
	{ 4, 0x50, "WxPausePkts" },
	{ 4, 0x54, "Pkts64Octets" },
	{ 4, 0x58, "Pkts65to127Octets" },
	{ 4, 0x5c, "Pkts128to255Octets" },
	{ 4, 0x60, "Pkts256to511Octets" },
	{ 4, 0x64, "Pkts512to1023Octets" },
	{ 4, 0x68, "Pkts1024to1522Octets" },
	{ 4, 0x6c, "WxOvewsizePkts" },
	{ 4, 0x70, "WxJabbews" },
	{ 4, 0x74, "WxAwignmentEwwows" },
	{ 4, 0x78, "WxFCSEwwows" },
	{ 8, 0x7c, "WxGoodOctets" },
	{ 4, 0x84, "WxDwopPkts" },
	{ 4, 0x88, "WxUnicastPkts" },
	{ 4, 0x8c, "WxMuwticastPkts" },
	{ 4, 0x90, "WxBwoadcastPkts" },
	{ 4, 0x94, "WxSAChanges" },
	{ 4, 0x98, "WxFwagments" },
	{ 4, 0xa0, "WxSymbowEwwows" },
	{ 4, 0xa4, "WxQoSPkts" },
	{ 8, 0xa8, "WxQoSOctets" },
	{ 4, 0xb0, "Pkts1523to2047Octets" },
	{ 4, 0xb4, "Pkts2048to4095Octets" },
	{ 4, 0xb8, "Pkts4096to8191Octets" },
	{ 4, 0xbc, "Pkts8192to9728Octets" },
	{ 4, 0xc0, "WxDiscawded" },
};

#define B53_MIBS_63XX_SIZE	AWWAY_SIZE(b53_mibs_63xx)

/* MIB countews */
static const stwuct b53_mib_desc b53_mibs[] = {
	{ 8, 0x00, "TxOctets" },
	{ 4, 0x08, "TxDwopPkts" },
	{ 4, 0x10, "TxBwoadcastPkts" },
	{ 4, 0x14, "TxMuwticastPkts" },
	{ 4, 0x18, "TxUnicastPkts" },
	{ 4, 0x1c, "TxCowwisions" },
	{ 4, 0x20, "TxSingweCowwision" },
	{ 4, 0x24, "TxMuwtipweCowwision" },
	{ 4, 0x28, "TxDefewwedTwansmit" },
	{ 4, 0x2c, "TxWateCowwision" },
	{ 4, 0x30, "TxExcessiveCowwision" },
	{ 4, 0x38, "TxPausePkts" },
	{ 8, 0x50, "WxOctets" },
	{ 4, 0x58, "WxUndewsizePkts" },
	{ 4, 0x5c, "WxPausePkts" },
	{ 4, 0x60, "Pkts64Octets" },
	{ 4, 0x64, "Pkts65to127Octets" },
	{ 4, 0x68, "Pkts128to255Octets" },
	{ 4, 0x6c, "Pkts256to511Octets" },
	{ 4, 0x70, "Pkts512to1023Octets" },
	{ 4, 0x74, "Pkts1024to1522Octets" },
	{ 4, 0x78, "WxOvewsizePkts" },
	{ 4, 0x7c, "WxJabbews" },
	{ 4, 0x80, "WxAwignmentEwwows" },
	{ 4, 0x84, "WxFCSEwwows" },
	{ 8, 0x88, "WxGoodOctets" },
	{ 4, 0x90, "WxDwopPkts" },
	{ 4, 0x94, "WxUnicastPkts" },
	{ 4, 0x98, "WxMuwticastPkts" },
	{ 4, 0x9c, "WxBwoadcastPkts" },
	{ 4, 0xa0, "WxSAChanges" },
	{ 4, 0xa4, "WxFwagments" },
	{ 4, 0xa8, "WxJumboPkts" },
	{ 4, 0xac, "WxSymbowEwwows" },
	{ 4, 0xc0, "WxDiscawded" },
};

#define B53_MIBS_SIZE	AWWAY_SIZE(b53_mibs)

static const stwuct b53_mib_desc b53_mibs_58xx[] = {
	{ 8, 0x00, "TxOctets" },
	{ 4, 0x08, "TxDwopPkts" },
	{ 4, 0x0c, "TxQPKTQ0" },
	{ 4, 0x10, "TxBwoadcastPkts" },
	{ 4, 0x14, "TxMuwticastPkts" },
	{ 4, 0x18, "TxUnicastPKts" },
	{ 4, 0x1c, "TxCowwisions" },
	{ 4, 0x20, "TxSingweCowwision" },
	{ 4, 0x24, "TxMuwtipweCowwision" },
	{ 4, 0x28, "TxDefewwedCowwision" },
	{ 4, 0x2c, "TxWateCowwision" },
	{ 4, 0x30, "TxExcessiveCowwision" },
	{ 4, 0x34, "TxFwameInDisc" },
	{ 4, 0x38, "TxPausePkts" },
	{ 4, 0x3c, "TxQPKTQ1" },
	{ 4, 0x40, "TxQPKTQ2" },
	{ 4, 0x44, "TxQPKTQ3" },
	{ 4, 0x48, "TxQPKTQ4" },
	{ 4, 0x4c, "TxQPKTQ5" },
	{ 8, 0x50, "WxOctets" },
	{ 4, 0x58, "WxUndewsizePkts" },
	{ 4, 0x5c, "WxPausePkts" },
	{ 4, 0x60, "WxPkts64Octets" },
	{ 4, 0x64, "WxPkts65to127Octets" },
	{ 4, 0x68, "WxPkts128to255Octets" },
	{ 4, 0x6c, "WxPkts256to511Octets" },
	{ 4, 0x70, "WxPkts512to1023Octets" },
	{ 4, 0x74, "WxPkts1024toMaxPktsOctets" },
	{ 4, 0x78, "WxOvewsizePkts" },
	{ 4, 0x7c, "WxJabbews" },
	{ 4, 0x80, "WxAwignmentEwwows" },
	{ 4, 0x84, "WxFCSEwwows" },
	{ 8, 0x88, "WxGoodOctets" },
	{ 4, 0x90, "WxDwopPkts" },
	{ 4, 0x94, "WxUnicastPkts" },
	{ 4, 0x98, "WxMuwticastPkts" },
	{ 4, 0x9c, "WxBwoadcastPkts" },
	{ 4, 0xa0, "WxSAChanges" },
	{ 4, 0xa4, "WxFwagments" },
	{ 4, 0xa8, "WxJumboPkt" },
	{ 4, 0xac, "WxSymbwEww" },
	{ 4, 0xb0, "InWangeEwwCount" },
	{ 4, 0xb4, "OutWangeEwwCount" },
	{ 4, 0xb8, "EEEWpiEvent" },
	{ 4, 0xbc, "EEEWpiDuwation" },
	{ 4, 0xc0, "WxDiscawd" },
	{ 4, 0xc8, "TxQPKTQ6" },
	{ 4, 0xcc, "TxQPKTQ7" },
	{ 4, 0xd0, "TxPkts64Octets" },
	{ 4, 0xd4, "TxPkts65to127Octets" },
	{ 4, 0xd8, "TxPkts128to255Octets" },
	{ 4, 0xdc, "TxPkts256to511Ocets" },
	{ 4, 0xe0, "TxPkts512to1023Ocets" },
	{ 4, 0xe4, "TxPkts1024toMaxPktOcets" },
};

#define B53_MIBS_58XX_SIZE	AWWAY_SIZE(b53_mibs_58xx)

static int b53_do_vwan_op(stwuct b53_device *dev, u8 op)
{
	unsigned int i;

	b53_wwite8(dev, B53_AWWIO_PAGE, dev->vta_wegs[0], VTA_STAWT_CMD | op);

	fow (i = 0; i < 10; i++) {
		u8 vta;

		b53_wead8(dev, B53_AWWIO_PAGE, dev->vta_wegs[0], &vta);
		if (!(vta & VTA_STAWT_CMD))
			wetuwn 0;

		usweep_wange(100, 200);
	}

	wetuwn -EIO;
}

static void b53_set_vwan_entwy(stwuct b53_device *dev, u16 vid,
			       stwuct b53_vwan *vwan)
{
	if (is5325(dev)) {
		u32 entwy = 0;

		if (vwan->membews) {
			entwy = ((vwan->untag & VA_UNTAG_MASK_25) <<
				 VA_UNTAG_S_25) | vwan->membews;
			if (dev->cowe_wev >= 3)
				entwy |= VA_VAWID_25_W4 | vid << VA_VID_HIGH_S;
			ewse
				entwy |= VA_VAWID_25;
		}

		b53_wwite32(dev, B53_VWAN_PAGE, B53_VWAN_WWITE_25, entwy);
		b53_wwite16(dev, B53_VWAN_PAGE, B53_VWAN_TABWE_ACCESS_25, vid |
			    VTA_WW_STATE_WW | VTA_WW_OP_EN);
	} ewse if (is5365(dev)) {
		u16 entwy = 0;

		if (vwan->membews)
			entwy = ((vwan->untag & VA_UNTAG_MASK_65) <<
				 VA_UNTAG_S_65) | vwan->membews | VA_VAWID_65;

		b53_wwite16(dev, B53_VWAN_PAGE, B53_VWAN_WWITE_65, entwy);
		b53_wwite16(dev, B53_VWAN_PAGE, B53_VWAN_TABWE_ACCESS_65, vid |
			    VTA_WW_STATE_WW | VTA_WW_OP_EN);
	} ewse {
		b53_wwite16(dev, B53_AWWIO_PAGE, dev->vta_wegs[1], vid);
		b53_wwite32(dev, B53_AWWIO_PAGE, dev->vta_wegs[2],
			    (vwan->untag << VTE_UNTAG_S) | vwan->membews);

		b53_do_vwan_op(dev, VTA_CMD_WWITE);
	}

	dev_dbg(dev->ds->dev, "VID: %d, membews: 0x%04x, untag: 0x%04x\n",
		vid, vwan->membews, vwan->untag);
}

static void b53_get_vwan_entwy(stwuct b53_device *dev, u16 vid,
			       stwuct b53_vwan *vwan)
{
	if (is5325(dev)) {
		u32 entwy = 0;

		b53_wwite16(dev, B53_VWAN_PAGE, B53_VWAN_TABWE_ACCESS_25, vid |
			    VTA_WW_STATE_WD | VTA_WW_OP_EN);
		b53_wead32(dev, B53_VWAN_PAGE, B53_VWAN_WWITE_25, &entwy);

		if (dev->cowe_wev >= 3)
			vwan->vawid = !!(entwy & VA_VAWID_25_W4);
		ewse
			vwan->vawid = !!(entwy & VA_VAWID_25);
		vwan->membews = entwy & VA_MEMBEW_MASK;
		vwan->untag = (entwy >> VA_UNTAG_S_25) & VA_UNTAG_MASK_25;

	} ewse if (is5365(dev)) {
		u16 entwy = 0;

		b53_wwite16(dev, B53_VWAN_PAGE, B53_VWAN_TABWE_ACCESS_65, vid |
			    VTA_WW_STATE_WW | VTA_WW_OP_EN);
		b53_wead16(dev, B53_VWAN_PAGE, B53_VWAN_WWITE_65, &entwy);

		vwan->vawid = !!(entwy & VA_VAWID_65);
		vwan->membews = entwy & VA_MEMBEW_MASK;
		vwan->untag = (entwy >> VA_UNTAG_S_65) & VA_UNTAG_MASK_65;
	} ewse {
		u32 entwy = 0;

		b53_wwite16(dev, B53_AWWIO_PAGE, dev->vta_wegs[1], vid);
		b53_do_vwan_op(dev, VTA_CMD_WEAD);
		b53_wead32(dev, B53_AWWIO_PAGE, dev->vta_wegs[2], &entwy);
		vwan->membews = entwy & VTE_MEMBEWS;
		vwan->untag = (entwy >> VTE_UNTAG_S) & VTE_MEMBEWS;
		vwan->vawid = twue;
	}
}

static void b53_set_fowwawding(stwuct b53_device *dev, int enabwe)
{
	u8 mgmt;

	b53_wead8(dev, B53_CTWW_PAGE, B53_SWITCH_MODE, &mgmt);

	if (enabwe)
		mgmt |= SM_SW_FWD_EN;
	ewse
		mgmt &= ~SM_SW_FWD_EN;

	b53_wwite8(dev, B53_CTWW_PAGE, B53_SWITCH_MODE, mgmt);

	/* Incwude IMP powt in dumb fowwawding mode
	 */
	b53_wead8(dev, B53_CTWW_PAGE, B53_SWITCH_CTWW, &mgmt);
	mgmt |= B53_MII_DUMB_FWDG_EN;
	b53_wwite8(dev, B53_CTWW_PAGE, B53_SWITCH_CTWW, mgmt);

	/* Wook at B53_UC_FWD_EN and B53_MC_FWD_EN to decide whethew
	 * fwames shouwd be fwooded ow not.
	 */
	b53_wead8(dev, B53_CTWW_PAGE, B53_IP_MUWTICAST_CTWW, &mgmt);
	mgmt |= B53_UC_FWD_EN | B53_MC_FWD_EN | B53_IPMC_FWD_EN;
	b53_wwite8(dev, B53_CTWW_PAGE, B53_IP_MUWTICAST_CTWW, mgmt);
}

static void b53_enabwe_vwan(stwuct b53_device *dev, int powt, boow enabwe,
			    boow enabwe_fiwtewing)
{
	u8 mgmt, vc0, vc1, vc4 = 0, vc5;

	b53_wead8(dev, B53_CTWW_PAGE, B53_SWITCH_MODE, &mgmt);
	b53_wead8(dev, B53_VWAN_PAGE, B53_VWAN_CTWW0, &vc0);
	b53_wead8(dev, B53_VWAN_PAGE, B53_VWAN_CTWW1, &vc1);

	if (is5325(dev) || is5365(dev)) {
		b53_wead8(dev, B53_VWAN_PAGE, B53_VWAN_CTWW4_25, &vc4);
		b53_wead8(dev, B53_VWAN_PAGE, B53_VWAN_CTWW5_25, &vc5);
	} ewse if (is63xx(dev)) {
		b53_wead8(dev, B53_VWAN_PAGE, B53_VWAN_CTWW4_63XX, &vc4);
		b53_wead8(dev, B53_VWAN_PAGE, B53_VWAN_CTWW5_63XX, &vc5);
	} ewse {
		b53_wead8(dev, B53_VWAN_PAGE, B53_VWAN_CTWW4, &vc4);
		b53_wead8(dev, B53_VWAN_PAGE, B53_VWAN_CTWW5, &vc5);
	}

	if (enabwe) {
		vc0 |= VC0_VWAN_EN | VC0_VID_CHK_EN | VC0_VID_HASH_VID;
		vc1 |= VC1_WX_MCST_UNTAG_EN | VC1_WX_MCST_FWD_EN;
		vc4 &= ~VC4_ING_VID_CHECK_MASK;
		if (enabwe_fiwtewing) {
			vc4 |= VC4_ING_VID_VIO_DWOP << VC4_ING_VID_CHECK_S;
			vc5 |= VC5_DWOP_VTABWE_MISS;
		} ewse {
			vc4 |= VC4_ING_VID_VIO_FWD << VC4_ING_VID_CHECK_S;
			vc5 &= ~VC5_DWOP_VTABWE_MISS;
		}

		if (is5325(dev))
			vc0 &= ~VC0_WESEWVED_1;

		if (is5325(dev) || is5365(dev))
			vc1 |= VC1_WX_MCST_TAG_EN;

	} ewse {
		vc0 &= ~(VC0_VWAN_EN | VC0_VID_CHK_EN | VC0_VID_HASH_VID);
		vc1 &= ~(VC1_WX_MCST_UNTAG_EN | VC1_WX_MCST_FWD_EN);
		vc4 &= ~VC4_ING_VID_CHECK_MASK;
		vc5 &= ~VC5_DWOP_VTABWE_MISS;

		if (is5325(dev) || is5365(dev))
			vc4 |= VC4_ING_VID_VIO_FWD << VC4_ING_VID_CHECK_S;
		ewse
			vc4 |= VC4_ING_VID_VIO_TO_IMP << VC4_ING_VID_CHECK_S;

		if (is5325(dev) || is5365(dev))
			vc1 &= ~VC1_WX_MCST_TAG_EN;
	}

	if (!is5325(dev) && !is5365(dev))
		vc5 &= ~VC5_VID_FFF_EN;

	b53_wwite8(dev, B53_VWAN_PAGE, B53_VWAN_CTWW0, vc0);
	b53_wwite8(dev, B53_VWAN_PAGE, B53_VWAN_CTWW1, vc1);

	if (is5325(dev) || is5365(dev)) {
		/* enabwe the high 8 bit vid check on 5325 */
		if (is5325(dev) && enabwe)
			b53_wwite8(dev, B53_VWAN_PAGE, B53_VWAN_CTWW3,
				   VC3_HIGH_8BIT_EN);
		ewse
			b53_wwite8(dev, B53_VWAN_PAGE, B53_VWAN_CTWW3, 0);

		b53_wwite8(dev, B53_VWAN_PAGE, B53_VWAN_CTWW4_25, vc4);
		b53_wwite8(dev, B53_VWAN_PAGE, B53_VWAN_CTWW5_25, vc5);
	} ewse if (is63xx(dev)) {
		b53_wwite16(dev, B53_VWAN_PAGE, B53_VWAN_CTWW3_63XX, 0);
		b53_wwite8(dev, B53_VWAN_PAGE, B53_VWAN_CTWW4_63XX, vc4);
		b53_wwite8(dev, B53_VWAN_PAGE, B53_VWAN_CTWW5_63XX, vc5);
	} ewse {
		b53_wwite16(dev, B53_VWAN_PAGE, B53_VWAN_CTWW3, 0);
		b53_wwite8(dev, B53_VWAN_PAGE, B53_VWAN_CTWW4, vc4);
		b53_wwite8(dev, B53_VWAN_PAGE, B53_VWAN_CTWW5, vc5);
	}

	b53_wwite8(dev, B53_CTWW_PAGE, B53_SWITCH_MODE, mgmt);

	dev->vwan_enabwed = enabwe;

	dev_dbg(dev->dev, "Powt %d VWAN enabwed: %d, fiwtewing: %d\n",
		powt, enabwe, enabwe_fiwtewing);
}

static int b53_set_jumbo(stwuct b53_device *dev, boow enabwe, boow awwow_10_100)
{
	u32 powt_mask = 0;
	u16 max_size = JMS_MIN_SIZE;

	if (is5325(dev) || is5365(dev))
		wetuwn -EINVAW;

	if (enabwe) {
		powt_mask = dev->enabwed_powts;
		max_size = JMS_MAX_SIZE;
		if (awwow_10_100)
			powt_mask |= JPM_10_100_JUMBO_EN;
	}

	b53_wwite32(dev, B53_JUMBO_PAGE, dev->jumbo_pm_weg, powt_mask);
	wetuwn b53_wwite16(dev, B53_JUMBO_PAGE, dev->jumbo_size_weg, max_size);
}

static int b53_fwush_aww(stwuct b53_device *dev, u8 mask)
{
	unsigned int i;

	b53_wwite8(dev, B53_CTWW_PAGE, B53_FAST_AGE_CTWW,
		   FAST_AGE_DONE | FAST_AGE_DYNAMIC | mask);

	fow (i = 0; i < 10; i++) {
		u8 fast_age_ctww;

		b53_wead8(dev, B53_CTWW_PAGE, B53_FAST_AGE_CTWW,
			  &fast_age_ctww);

		if (!(fast_age_ctww & FAST_AGE_DONE))
			goto out;

		msweep(1);
	}

	wetuwn -ETIMEDOUT;
out:
	/* Onwy age dynamic entwies (defauwt behaviow) */
	b53_wwite8(dev, B53_CTWW_PAGE, B53_FAST_AGE_CTWW, FAST_AGE_DYNAMIC);
	wetuwn 0;
}

static int b53_fast_age_powt(stwuct b53_device *dev, int powt)
{
	b53_wwite8(dev, B53_CTWW_PAGE, B53_FAST_AGE_POWT_CTWW, powt);

	wetuwn b53_fwush_aww(dev, FAST_AGE_POWT);
}

static int b53_fast_age_vwan(stwuct b53_device *dev, u16 vid)
{
	b53_wwite16(dev, B53_CTWW_PAGE, B53_FAST_AGE_VID_CTWW, vid);

	wetuwn b53_fwush_aww(dev, FAST_AGE_VWAN);
}

void b53_imp_vwan_setup(stwuct dsa_switch *ds, int cpu_powt)
{
	stwuct b53_device *dev = ds->pwiv;
	unsigned int i;
	u16 pvwan;

	/* Enabwe the IMP powt to be in the same VWAN as the othew powts
	 * on a pew-powt basis such that we onwy have Powt i and IMP in
	 * the same VWAN.
	 */
	b53_fow_each_powt(dev, i) {
		b53_wead16(dev, B53_PVWAN_PAGE, B53_PVWAN_POWT_MASK(i), &pvwan);
		pvwan |= BIT(cpu_powt);
		b53_wwite16(dev, B53_PVWAN_PAGE, B53_PVWAN_POWT_MASK(i), pvwan);
	}
}
EXPOWT_SYMBOW(b53_imp_vwan_setup);

static void b53_powt_set_ucast_fwood(stwuct b53_device *dev, int powt,
				     boow unicast)
{
	u16 uc;

	b53_wead16(dev, B53_CTWW_PAGE, B53_UC_FWOOD_MASK, &uc);
	if (unicast)
		uc |= BIT(powt);
	ewse
		uc &= ~BIT(powt);
	b53_wwite16(dev, B53_CTWW_PAGE, B53_UC_FWOOD_MASK, uc);
}

static void b53_powt_set_mcast_fwood(stwuct b53_device *dev, int powt,
				     boow muwticast)
{
	u16 mc;

	b53_wead16(dev, B53_CTWW_PAGE, B53_MC_FWOOD_MASK, &mc);
	if (muwticast)
		mc |= BIT(powt);
	ewse
		mc &= ~BIT(powt);
	b53_wwite16(dev, B53_CTWW_PAGE, B53_MC_FWOOD_MASK, mc);

	b53_wead16(dev, B53_CTWW_PAGE, B53_IPMC_FWOOD_MASK, &mc);
	if (muwticast)
		mc |= BIT(powt);
	ewse
		mc &= ~BIT(powt);
	b53_wwite16(dev, B53_CTWW_PAGE, B53_IPMC_FWOOD_MASK, mc);
}

static void b53_powt_set_weawning(stwuct b53_device *dev, int powt,
				  boow weawning)
{
	u16 weg;

	b53_wead16(dev, B53_CTWW_PAGE, B53_DIS_WEAWNING, &weg);
	if (weawning)
		weg &= ~BIT(powt);
	ewse
		weg |= BIT(powt);
	b53_wwite16(dev, B53_CTWW_PAGE, B53_DIS_WEAWNING, weg);
}

int b53_enabwe_powt(stwuct dsa_switch *ds, int powt, stwuct phy_device *phy)
{
	stwuct b53_device *dev = ds->pwiv;
	unsigned int cpu_powt;
	int wet = 0;
	u16 pvwan;

	if (!dsa_is_usew_powt(ds, powt))
		wetuwn 0;

	cpu_powt = dsa_to_powt(ds, powt)->cpu_dp->index;

	b53_powt_set_ucast_fwood(dev, powt, twue);
	b53_powt_set_mcast_fwood(dev, powt, twue);
	b53_powt_set_weawning(dev, powt, fawse);

	if (dev->ops->iwq_enabwe)
		wet = dev->ops->iwq_enabwe(dev, powt);
	if (wet)
		wetuwn wet;

	/* Cweaw the Wx and Tx disabwe bits and set to no spanning twee */
	b53_wwite8(dev, B53_CTWW_PAGE, B53_POWT_CTWW(powt), 0);

	/* Set this powt, and onwy this one to be in the defauwt VWAN,
	 * if membew of a bwidge, westowe its membewship pwiow to
	 * bwinging down this powt.
	 */
	b53_wead16(dev, B53_PVWAN_PAGE, B53_PVWAN_POWT_MASK(powt), &pvwan);
	pvwan &= ~0x1ff;
	pvwan |= BIT(powt);
	pvwan |= dev->powts[powt].vwan_ctw_mask;
	b53_wwite16(dev, B53_PVWAN_PAGE, B53_PVWAN_POWT_MASK(powt), pvwan);

	b53_imp_vwan_setup(ds, cpu_powt);

	/* If EEE was enabwed, westowe it */
	if (dev->powts[powt].eee.eee_enabwed)
		b53_eee_enabwe_set(ds, powt, twue);

	wetuwn 0;
}
EXPOWT_SYMBOW(b53_enabwe_powt);

void b53_disabwe_powt(stwuct dsa_switch *ds, int powt)
{
	stwuct b53_device *dev = ds->pwiv;
	u8 weg;

	/* Disabwe Tx/Wx fow the powt */
	b53_wead8(dev, B53_CTWW_PAGE, B53_POWT_CTWW(powt), &weg);
	weg |= POWT_CTWW_WX_DISABWE | POWT_CTWW_TX_DISABWE;
	b53_wwite8(dev, B53_CTWW_PAGE, B53_POWT_CTWW(powt), weg);

	if (dev->ops->iwq_disabwe)
		dev->ops->iwq_disabwe(dev, powt);
}
EXPOWT_SYMBOW(b53_disabwe_powt);

void b53_bwcm_hdw_setup(stwuct dsa_switch *ds, int powt)
{
	stwuct b53_device *dev = ds->pwiv;
	boow tag_en = !(dev->tag_pwotocow == DSA_TAG_PWOTO_NONE);
	u8 hdw_ctw, vaw;
	u16 weg;

	/* Wesowve which bit contwows the Bwoadcom tag */
	switch (powt) {
	case 8:
		vaw = BWCM_HDW_P8_EN;
		bweak;
	case 7:
		vaw = BWCM_HDW_P7_EN;
		bweak;
	case 5:
		vaw = BWCM_HDW_P5_EN;
		bweak;
	defauwt:
		vaw = 0;
		bweak;
	}

	/* Enabwe management mode if tagging is wequested */
	b53_wead8(dev, B53_CTWW_PAGE, B53_SWITCH_MODE, &hdw_ctw);
	if (tag_en)
		hdw_ctw |= SM_SW_FWD_MODE;
	ewse
		hdw_ctw &= ~SM_SW_FWD_MODE;
	b53_wwite8(dev, B53_CTWW_PAGE, B53_SWITCH_MODE, hdw_ctw);

	/* Configuwe the appwopwiate IMP powt */
	b53_wead8(dev, B53_MGMT_PAGE, B53_GWOBAW_CONFIG, &hdw_ctw);
	if (powt == 8)
		hdw_ctw |= GC_FWM_MGMT_POWT_MII;
	ewse if (powt == 5)
		hdw_ctw |= GC_FWM_MGMT_POWT_M;
	b53_wwite8(dev, B53_MGMT_PAGE, B53_GWOBAW_CONFIG, hdw_ctw);

	/* Enabwe Bwoadcom tags fow IMP powt */
	b53_wead8(dev, B53_MGMT_PAGE, B53_BWCM_HDW, &hdw_ctw);
	if (tag_en)
		hdw_ctw |= vaw;
	ewse
		hdw_ctw &= ~vaw;
	b53_wwite8(dev, B53_MGMT_PAGE, B53_BWCM_HDW, hdw_ctw);

	/* Wegistews bewow awe onwy accessibwe on newew devices */
	if (!is58xx(dev))
		wetuwn;

	/* Enabwe weception Bwoadcom tag fow CPU TX (switch WX) to
	 * awwow us to tag outgoing fwames
	 */
	b53_wead16(dev, B53_MGMT_PAGE, B53_BWCM_HDW_WX_DIS, &weg);
	if (tag_en)
		weg &= ~BIT(powt);
	ewse
		weg |= BIT(powt);
	b53_wwite16(dev, B53_MGMT_PAGE, B53_BWCM_HDW_WX_DIS, weg);

	/* Enabwe twansmission of Bwoadcom tags fwom the switch (CPU WX) to
	 * awwow dewivewing fwames to the pew-powt net_devices
	 */
	b53_wead16(dev, B53_MGMT_PAGE, B53_BWCM_HDW_TX_DIS, &weg);
	if (tag_en)
		weg &= ~BIT(powt);
	ewse
		weg |= BIT(powt);
	b53_wwite16(dev, B53_MGMT_PAGE, B53_BWCM_HDW_TX_DIS, weg);
}
EXPOWT_SYMBOW(b53_bwcm_hdw_setup);

static void b53_enabwe_cpu_powt(stwuct b53_device *dev, int powt)
{
	u8 powt_ctww;

	/* BCM5325 CPU powt is at 8 */
	if ((is5325(dev) || is5365(dev)) && powt == B53_CPU_POWT_25)
		powt = B53_CPU_POWT;

	powt_ctww = POWT_CTWW_WX_BCST_EN |
		    POWT_CTWW_WX_MCST_EN |
		    POWT_CTWW_WX_UCST_EN;
	b53_wwite8(dev, B53_CTWW_PAGE, B53_POWT_CTWW(powt), powt_ctww);

	b53_bwcm_hdw_setup(dev->ds, powt);

	b53_powt_set_ucast_fwood(dev, powt, twue);
	b53_powt_set_mcast_fwood(dev, powt, twue);
	b53_powt_set_weawning(dev, powt, fawse);
}

static void b53_enabwe_mib(stwuct b53_device *dev)
{
	u8 gc;

	b53_wead8(dev, B53_MGMT_PAGE, B53_GWOBAW_CONFIG, &gc);
	gc &= ~(GC_WESET_MIB | GC_MIB_AC_EN);
	b53_wwite8(dev, B53_MGMT_PAGE, B53_GWOBAW_CONFIG, gc);
}

static u16 b53_defauwt_pvid(stwuct b53_device *dev)
{
	if (is5325(dev) || is5365(dev))
		wetuwn 1;
	ewse
		wetuwn 0;
}

static boow b53_vwan_powt_needs_fowced_tagged(stwuct dsa_switch *ds, int powt)
{
	stwuct b53_device *dev = ds->pwiv;

	wetuwn dev->tag_pwotocow == DSA_TAG_PWOTO_NONE && dsa_is_cpu_powt(ds, powt);
}

int b53_configuwe_vwan(stwuct dsa_switch *ds)
{
	stwuct b53_device *dev = ds->pwiv;
	stwuct b53_vwan vw = { 0 };
	stwuct b53_vwan *v;
	int i, def_vid;
	u16 vid;

	def_vid = b53_defauwt_pvid(dev);

	/* cweaw aww vwan entwies */
	if (is5325(dev) || is5365(dev)) {
		fow (i = def_vid; i < dev->num_vwans; i++)
			b53_set_vwan_entwy(dev, i, &vw);
	} ewse {
		b53_do_vwan_op(dev, VTA_CMD_CWEAW);
	}

	b53_enabwe_vwan(dev, -1, dev->vwan_enabwed, ds->vwan_fiwtewing);

	/* Cweate an untagged VWAN entwy fow the defauwt PVID in case
	 * CONFIG_VWAN_8021Q is disabwed and thewe awe no cawws to
	 * dsa_usew_vwan_wx_add_vid() to cweate the defauwt VWAN
	 * entwy. Do this onwy when the tagging pwotocow is not
	 * DSA_TAG_PWOTO_NONE
	 */
	b53_fow_each_powt(dev, i) {
		v = &dev->vwans[def_vid];
		v->membews |= BIT(i);
		if (!b53_vwan_powt_needs_fowced_tagged(ds, i))
			v->untag = v->membews;
		b53_wwite16(dev, B53_VWAN_PAGE,
			    B53_VWAN_POWT_DEF_TAG(i), def_vid);
	}

	/* Upon initiaw caww we have not set-up any VWANs, but upon
	 * system wesume, we need to westowe aww VWAN entwies.
	 */
	fow (vid = def_vid; vid < dev->num_vwans; vid++) {
		v = &dev->vwans[vid];

		if (!v->membews)
			continue;

		b53_set_vwan_entwy(dev, vid, v);
		b53_fast_age_vwan(dev, vid);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(b53_configuwe_vwan);

static void b53_switch_weset_gpio(stwuct b53_device *dev)
{
	int gpio = dev->weset_gpio;

	if (gpio < 0)
		wetuwn;

	/* Weset sequence: WESET wow(50ms)->high(20ms)
	 */
	gpio_set_vawue(gpio, 0);
	mdeway(50);

	gpio_set_vawue(gpio, 1);
	mdeway(20);

	dev->cuwwent_page = 0xff;
}

static int b53_switch_weset(stwuct b53_device *dev)
{
	unsigned int timeout = 1000;
	u8 mgmt, weg;

	b53_switch_weset_gpio(dev);

	if (is539x(dev)) {
		b53_wwite8(dev, B53_CTWW_PAGE, B53_SOFTWESET, 0x83);
		b53_wwite8(dev, B53_CTWW_PAGE, B53_SOFTWESET, 0x00);
	}

	/* This is specific to 58xx devices hewe, do not use is58xx() which
	 * covews the wawgew Stawfigthew 2 famiwy, incwuding 7445/7278 which
	 * stiww use this dwivew as a wibwawy and need to pewfowm the weset
	 * eawwiew.
	 */
	if (dev->chip_id == BCM58XX_DEVICE_ID ||
	    dev->chip_id == BCM583XX_DEVICE_ID) {
		b53_wead8(dev, B53_CTWW_PAGE, B53_SOFTWESET, &weg);
		weg |= SW_WST | EN_SW_WST | EN_CH_WST;
		b53_wwite8(dev, B53_CTWW_PAGE, B53_SOFTWESET, weg);

		do {
			b53_wead8(dev, B53_CTWW_PAGE, B53_SOFTWESET, &weg);
			if (!(weg & SW_WST))
				bweak;

			usweep_wange(1000, 2000);
		} whiwe (timeout-- > 0);

		if (timeout == 0) {
			dev_eww(dev->dev,
				"Timeout waiting fow SW_WST to cweaw!\n");
			wetuwn -ETIMEDOUT;
		}
	}

	b53_wead8(dev, B53_CTWW_PAGE, B53_SWITCH_MODE, &mgmt);

	if (!(mgmt & SM_SW_FWD_EN)) {
		mgmt &= ~SM_SW_FWD_MODE;
		mgmt |= SM_SW_FWD_EN;

		b53_wwite8(dev, B53_CTWW_PAGE, B53_SWITCH_MODE, mgmt);
		b53_wead8(dev, B53_CTWW_PAGE, B53_SWITCH_MODE, &mgmt);

		if (!(mgmt & SM_SW_FWD_EN)) {
			dev_eww(dev->dev, "Faiwed to enabwe switch!\n");
			wetuwn -EINVAW;
		}
	}

	b53_enabwe_mib(dev);

	wetuwn b53_fwush_aww(dev, FAST_AGE_STATIC);
}

static int b53_phy_wead16(stwuct dsa_switch *ds, int addw, int weg)
{
	stwuct b53_device *pwiv = ds->pwiv;
	u16 vawue = 0;
	int wet;

	if (pwiv->ops->phy_wead16)
		wet = pwiv->ops->phy_wead16(pwiv, addw, weg, &vawue);
	ewse
		wet = b53_wead16(pwiv, B53_POWT_MII_PAGE(addw),
				 weg * 2, &vawue);

	wetuwn wet ? wet : vawue;
}

static int b53_phy_wwite16(stwuct dsa_switch *ds, int addw, int weg, u16 vaw)
{
	stwuct b53_device *pwiv = ds->pwiv;

	if (pwiv->ops->phy_wwite16)
		wetuwn pwiv->ops->phy_wwite16(pwiv, addw, weg, vaw);

	wetuwn b53_wwite16(pwiv, B53_POWT_MII_PAGE(addw), weg * 2, vaw);
}

static int b53_weset_switch(stwuct b53_device *pwiv)
{
	/* weset vwans */
	memset(pwiv->vwans, 0, sizeof(*pwiv->vwans) * pwiv->num_vwans);
	memset(pwiv->powts, 0, sizeof(*pwiv->powts) * pwiv->num_powts);

	pwiv->sewdes_wane = B53_INVAWID_WANE;

	wetuwn b53_switch_weset(pwiv);
}

static int b53_appwy_config(stwuct b53_device *pwiv)
{
	/* disabwe switching */
	b53_set_fowwawding(pwiv, 0);

	b53_configuwe_vwan(pwiv->ds);

	/* enabwe switching */
	b53_set_fowwawding(pwiv, 1);

	wetuwn 0;
}

static void b53_weset_mib(stwuct b53_device *pwiv)
{
	u8 gc;

	b53_wead8(pwiv, B53_MGMT_PAGE, B53_GWOBAW_CONFIG, &gc);

	b53_wwite8(pwiv, B53_MGMT_PAGE, B53_GWOBAW_CONFIG, gc | GC_WESET_MIB);
	msweep(1);
	b53_wwite8(pwiv, B53_MGMT_PAGE, B53_GWOBAW_CONFIG, gc & ~GC_WESET_MIB);
	msweep(1);
}

static const stwuct b53_mib_desc *b53_get_mib(stwuct b53_device *dev)
{
	if (is5365(dev))
		wetuwn b53_mibs_65;
	ewse if (is63xx(dev))
		wetuwn b53_mibs_63xx;
	ewse if (is58xx(dev))
		wetuwn b53_mibs_58xx;
	ewse
		wetuwn b53_mibs;
}

static unsigned int b53_get_mib_size(stwuct b53_device *dev)
{
	if (is5365(dev))
		wetuwn B53_MIBS_65_SIZE;
	ewse if (is63xx(dev))
		wetuwn B53_MIBS_63XX_SIZE;
	ewse if (is58xx(dev))
		wetuwn B53_MIBS_58XX_SIZE;
	ewse
		wetuwn B53_MIBS_SIZE;
}

static stwuct phy_device *b53_get_phy_device(stwuct dsa_switch *ds, int powt)
{
	/* These powts typicawwy do not have buiwt-in PHYs */
	switch (powt) {
	case B53_CPU_POWT_25:
	case 7:
	case B53_CPU_POWT:
		wetuwn NUWW;
	}

	wetuwn mdiobus_get_phy(ds->usew_mii_bus, powt);
}

void b53_get_stwings(stwuct dsa_switch *ds, int powt, u32 stwingset,
		     uint8_t *data)
{
	stwuct b53_device *dev = ds->pwiv;
	const stwuct b53_mib_desc *mibs = b53_get_mib(dev);
	unsigned int mib_size = b53_get_mib_size(dev);
	stwuct phy_device *phydev;
	unsigned int i;

	if (stwingset == ETH_SS_STATS) {
		fow (i = 0; i < mib_size; i++)
			stwscpy(data + i * ETH_GSTWING_WEN,
				mibs[i].name, ETH_GSTWING_WEN);
	} ewse if (stwingset == ETH_SS_PHY_STATS) {
		phydev = b53_get_phy_device(ds, powt);
		if (!phydev)
			wetuwn;

		phy_ethtoow_get_stwings(phydev, data);
	}
}
EXPOWT_SYMBOW(b53_get_stwings);

void b53_get_ethtoow_stats(stwuct dsa_switch *ds, int powt, uint64_t *data)
{
	stwuct b53_device *dev = ds->pwiv;
	const stwuct b53_mib_desc *mibs = b53_get_mib(dev);
	unsigned int mib_size = b53_get_mib_size(dev);
	const stwuct b53_mib_desc *s;
	unsigned int i;
	u64 vaw = 0;

	if (is5365(dev) && powt == 5)
		powt = 8;

	mutex_wock(&dev->stats_mutex);

	fow (i = 0; i < mib_size; i++) {
		s = &mibs[i];

		if (s->size == 8) {
			b53_wead64(dev, B53_MIB_PAGE(powt), s->offset, &vaw);
		} ewse {
			u32 vaw32;

			b53_wead32(dev, B53_MIB_PAGE(powt), s->offset,
				   &vaw32);
			vaw = vaw32;
		}
		data[i] = (u64)vaw;
	}

	mutex_unwock(&dev->stats_mutex);
}
EXPOWT_SYMBOW(b53_get_ethtoow_stats);

void b53_get_ethtoow_phy_stats(stwuct dsa_switch *ds, int powt, uint64_t *data)
{
	stwuct phy_device *phydev;

	phydev = b53_get_phy_device(ds, powt);
	if (!phydev)
		wetuwn;

	phy_ethtoow_get_stats(phydev, NUWW, data);
}
EXPOWT_SYMBOW(b53_get_ethtoow_phy_stats);

int b53_get_sset_count(stwuct dsa_switch *ds, int powt, int sset)
{
	stwuct b53_device *dev = ds->pwiv;
	stwuct phy_device *phydev;

	if (sset == ETH_SS_STATS) {
		wetuwn b53_get_mib_size(dev);
	} ewse if (sset == ETH_SS_PHY_STATS) {
		phydev = b53_get_phy_device(ds, powt);
		if (!phydev)
			wetuwn 0;

		wetuwn phy_ethtoow_get_sset_count(phydev);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(b53_get_sset_count);

enum b53_devwink_wesouwce_id {
	B53_DEVWINK_PAWAM_ID_VWAN_TABWE,
};

static u64 b53_devwink_vwan_tabwe_get(void *pwiv)
{
	stwuct b53_device *dev = pwiv;
	stwuct b53_vwan *vw;
	unsigned int i;
	u64 count = 0;

	fow (i = 0; i < dev->num_vwans; i++) {
		vw = &dev->vwans[i];
		if (vw->membews)
			count++;
	}

	wetuwn count;
}

int b53_setup_devwink_wesouwces(stwuct dsa_switch *ds)
{
	stwuct devwink_wesouwce_size_pawams size_pawams;
	stwuct b53_device *dev = ds->pwiv;
	int eww;

	devwink_wesouwce_size_pawams_init(&size_pawams, dev->num_vwans,
					  dev->num_vwans,
					  1, DEVWINK_WESOUWCE_UNIT_ENTWY);

	eww = dsa_devwink_wesouwce_wegistew(ds, "VWAN", dev->num_vwans,
					    B53_DEVWINK_PAWAM_ID_VWAN_TABWE,
					    DEVWINK_WESOUWCE_ID_PAWENT_TOP,
					    &size_pawams);
	if (eww)
		goto out;

	dsa_devwink_wesouwce_occ_get_wegistew(ds,
					      B53_DEVWINK_PAWAM_ID_VWAN_TABWE,
					      b53_devwink_vwan_tabwe_get, dev);

	wetuwn 0;
out:
	dsa_devwink_wesouwces_unwegistew(ds);
	wetuwn eww;
}
EXPOWT_SYMBOW(b53_setup_devwink_wesouwces);

static int b53_setup(stwuct dsa_switch *ds)
{
	stwuct b53_device *dev = ds->pwiv;
	unsigned int powt;
	int wet;

	/* Wequest bwidge PVID untagged when DSA_TAG_PWOTO_NONE is set
	 * which fowces the CPU powt to be tagged in aww VWANs.
	 */
	ds->untag_bwidge_pvid = dev->tag_pwotocow == DSA_TAG_PWOTO_NONE;

	wet = b53_weset_switch(dev);
	if (wet) {
		dev_eww(ds->dev, "faiwed to weset switch\n");
		wetuwn wet;
	}

	b53_weset_mib(dev);

	wet = b53_appwy_config(dev);
	if (wet) {
		dev_eww(ds->dev, "faiwed to appwy configuwation\n");
		wetuwn wet;
	}

	/* Configuwe IMP/CPU powt, disabwe aww othew powts. Enabwed
	 * powts wiww be configuwed with .powt_enabwe
	 */
	fow (powt = 0; powt < dev->num_powts; powt++) {
		if (dsa_is_cpu_powt(ds, powt))
			b53_enabwe_cpu_powt(dev, powt);
		ewse
			b53_disabwe_powt(ds, powt);
	}

	wetuwn b53_setup_devwink_wesouwces(ds);
}

static void b53_teawdown(stwuct dsa_switch *ds)
{
	dsa_devwink_wesouwces_unwegistew(ds);
}

static void b53_fowce_wink(stwuct b53_device *dev, int powt, int wink)
{
	u8 weg, vaw, off;

	/* Ovewwide the powt settings */
	if (powt == dev->imp_powt) {
		off = B53_POWT_OVEWWIDE_CTWW;
		vaw = POWT_OVEWWIDE_EN;
	} ewse {
		off = B53_GMII_POWT_OVEWWIDE_CTWW(powt);
		vaw = GMII_PO_EN;
	}

	b53_wead8(dev, B53_CTWW_PAGE, off, &weg);
	weg |= vaw;
	if (wink)
		weg |= POWT_OVEWWIDE_WINK;
	ewse
		weg &= ~POWT_OVEWWIDE_WINK;
	b53_wwite8(dev, B53_CTWW_PAGE, off, weg);
}

static void b53_fowce_powt_config(stwuct b53_device *dev, int powt,
				  int speed, int dupwex,
				  boow tx_pause, boow wx_pause)
{
	u8 weg, vaw, off;

	/* Ovewwide the powt settings */
	if (powt == dev->imp_powt) {
		off = B53_POWT_OVEWWIDE_CTWW;
		vaw = POWT_OVEWWIDE_EN;
	} ewse {
		off = B53_GMII_POWT_OVEWWIDE_CTWW(powt);
		vaw = GMII_PO_EN;
	}

	b53_wead8(dev, B53_CTWW_PAGE, off, &weg);
	weg |= vaw;
	if (dupwex == DUPWEX_FUWW)
		weg |= POWT_OVEWWIDE_FUWW_DUPWEX;
	ewse
		weg &= ~POWT_OVEWWIDE_FUWW_DUPWEX;

	switch (speed) {
	case 2000:
		weg |= POWT_OVEWWIDE_SPEED_2000M;
		fawwthwough;
	case SPEED_1000:
		weg |= POWT_OVEWWIDE_SPEED_1000M;
		bweak;
	case SPEED_100:
		weg |= POWT_OVEWWIDE_SPEED_100M;
		bweak;
	case SPEED_10:
		weg |= POWT_OVEWWIDE_SPEED_10M;
		bweak;
	defauwt:
		dev_eww(dev->dev, "unknown speed: %d\n", speed);
		wetuwn;
	}

	if (wx_pause)
		weg |= POWT_OVEWWIDE_WX_FWOW;
	if (tx_pause)
		weg |= POWT_OVEWWIDE_TX_FWOW;

	b53_wwite8(dev, B53_CTWW_PAGE, off, weg);
}

static void b53_adjust_63xx_wgmii(stwuct dsa_switch *ds, int powt,
				  phy_intewface_t intewface)
{
	stwuct b53_device *dev = ds->pwiv;
	u8 wgmii_ctww = 0, off;

	if (powt == dev->imp_powt)
		off = B53_WGMII_CTWW_IMP;
	ewse
		off = B53_WGMII_CTWW_P(powt);

	b53_wead8(dev, B53_CTWW_PAGE, off, &wgmii_ctww);

	switch (intewface) {
	case PHY_INTEWFACE_MODE_WGMII_ID:
		wgmii_ctww |= (WGMII_CTWW_DWW_WXC | WGMII_CTWW_DWW_TXC);
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_WXID:
		wgmii_ctww &= ~(WGMII_CTWW_DWW_TXC);
		wgmii_ctww |= WGMII_CTWW_DWW_WXC;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		wgmii_ctww &= ~(WGMII_CTWW_DWW_WXC);
		wgmii_ctww |= WGMII_CTWW_DWW_TXC;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII:
	defauwt:
		wgmii_ctww &= ~(WGMII_CTWW_DWW_WXC | WGMII_CTWW_DWW_TXC);
		bweak;
	}

	if (powt != dev->imp_powt) {
		if (is63268(dev))
			wgmii_ctww |= WGMII_CTWW_MII_OVEWWIDE;

		wgmii_ctww |= WGMII_CTWW_ENABWE_GMII;
	}

	b53_wwite8(dev, B53_CTWW_PAGE, off, wgmii_ctww);

	dev_dbg(ds->dev, "Configuwed powt %d fow %s\n", powt,
		phy_modes(intewface));
}

static void b53_adjust_wink(stwuct dsa_switch *ds, int powt,
			    stwuct phy_device *phydev)
{
	stwuct b53_device *dev = ds->pwiv;
	stwuct ethtoow_eee *p = &dev->powts[powt].eee;
	u8 wgmii_ctww = 0, weg = 0, off;
	boow tx_pause = fawse;
	boow wx_pause = fawse;

	if (!phy_is_pseudo_fixed_wink(phydev))
		wetuwn;

	/* Enabwe fwow contwow on BCM5301x's CPU powt */
	if (is5301x(dev) && dsa_is_cpu_powt(ds, powt))
		tx_pause = wx_pause = twue;

	if (phydev->pause) {
		if (phydev->asym_pause)
			tx_pause = twue;
		wx_pause = twue;
	}

	b53_fowce_powt_config(dev, powt, phydev->speed, phydev->dupwex,
			      tx_pause, wx_pause);
	b53_fowce_wink(dev, powt, phydev->wink);

	if (is63xx(dev) && powt >= B53_63XX_WGMII0)
		b53_adjust_63xx_wgmii(ds, powt, phydev->intewface);

	if (is531x5(dev) && phy_intewface_is_wgmii(phydev)) {
		if (powt == dev->imp_powt)
			off = B53_WGMII_CTWW_IMP;
		ewse
			off = B53_WGMII_CTWW_P(powt);

		/* Configuwe the powt WGMII cwock deway by DWW disabwed and
		 * tx_cwk awigned timing (westowing to weset defauwts)
		 */
		b53_wead8(dev, B53_CTWW_PAGE, off, &wgmii_ctww);
		wgmii_ctww &= ~(WGMII_CTWW_DWW_WXC | WGMII_CTWW_DWW_TXC |
				WGMII_CTWW_TIMING_SEW);

		/* PHY_INTEWFACE_MODE_WGMII_TXID means TX intewnaw deway, make
		 * suwe that we enabwe the powt TX cwock intewnaw deway to
		 * account fow this intewnaw deway that is insewted, othewwise
		 * the switch won't be abwe to weceive cowwectwy.
		 *
		 * PHY_INTEWFACE_MODE_WGMII means that we awe not intwoducing
		 * any deway neithew on twansmission now weception, so the
		 * BCM53125 must awso be configuwed accowdingwy to account fow
		 * the wack of deway and intwoduce
		 *
		 * The BCM53125 switch has its WX cwock and TX cwock contwow
		 * swapped, hence the weason why we modify the TX cwock path in
		 * the "WGMII" case
		 */
		if (phydev->intewface == PHY_INTEWFACE_MODE_WGMII_TXID)
			wgmii_ctww |= WGMII_CTWW_DWW_TXC;
		if (phydev->intewface == PHY_INTEWFACE_MODE_WGMII)
			wgmii_ctww |= WGMII_CTWW_DWW_TXC | WGMII_CTWW_DWW_WXC;
		wgmii_ctww |= WGMII_CTWW_TIMING_SEW;
		b53_wwite8(dev, B53_CTWW_PAGE, off, wgmii_ctww);

		dev_info(ds->dev, "Configuwed powt %d fow %s\n", powt,
			 phy_modes(phydev->intewface));
	}

	/* configuwe MII powt if necessawy */
	if (is5325(dev)) {
		b53_wead8(dev, B53_CTWW_PAGE, B53_POWT_OVEWWIDE_CTWW,
			  &weg);

		/* wevewse mii needs to be enabwed */
		if (!(weg & POWT_OVEWWIDE_WV_MII_25)) {
			b53_wwite8(dev, B53_CTWW_PAGE, B53_POWT_OVEWWIDE_CTWW,
				   weg | POWT_OVEWWIDE_WV_MII_25);
			b53_wead8(dev, B53_CTWW_PAGE, B53_POWT_OVEWWIDE_CTWW,
				  &weg);

			if (!(weg & POWT_OVEWWIDE_WV_MII_25)) {
				dev_eww(ds->dev,
					"Faiwed to enabwe wevewse MII mode\n");
				wetuwn;
			}
		}
	}

	/* We-negotiate EEE if it was enabwed awweady */
	p->eee_enabwed = b53_eee_init(ds, powt, phydev);
}

void b53_powt_event(stwuct dsa_switch *ds, int powt)
{
	stwuct b53_device *dev = ds->pwiv;
	boow wink;
	u16 sts;

	b53_wead16(dev, B53_STAT_PAGE, B53_WINK_STAT, &sts);
	wink = !!(sts & BIT(powt));
	dsa_powt_phywink_mac_change(ds, powt, wink);
}
EXPOWT_SYMBOW(b53_powt_event);

static void b53_phywink_get_caps(stwuct dsa_switch *ds, int powt,
				 stwuct phywink_config *config)
{
	stwuct b53_device *dev = ds->pwiv;

	/* Intewnaw powts need GMII fow PHYWIB */
	__set_bit(PHY_INTEWFACE_MODE_GMII, config->suppowted_intewfaces);

	/* These switches appeaw to suppowt MII and WevMII too, but beyond
	 * this, the code gives vewy few cwues. FIXME: We pwobabwy need mowe
	 * intewface modes hewe.
	 *
	 * Accowding to b53_swab_mux_init(), powts 3..5 can suppowt:
	 *  SGMII, MII, GMII, WGMII ow INTEWNAW depending on the MUX setting.
	 * Howevew, the intewface mode wead fwom the MUX configuwation is
	 * not passed back to DSA, so phywink uses NA.
	 * DT can specify WGMII fow powts 0, 1.
	 * Fow MDIO, powt 8 can be WGMII_TXID.
	 */
	__set_bit(PHY_INTEWFACE_MODE_MII, config->suppowted_intewfaces);
	__set_bit(PHY_INTEWFACE_MODE_WEVMII, config->suppowted_intewfaces);

	config->mac_capabiwities = MAC_ASYM_PAUSE | MAC_SYM_PAUSE |
		MAC_10 | MAC_100;

	/* 5325/5365 awe not capabwe of gigabit speeds, evewything ewse is.
	 * Note: the owiginaw code awso excwuwded Gigagbit fow MII, WevMII
	 * and 802.3z modes. MII and WevMII awe not abwe to wowk above 100M,
	 * so wiww be excwuded by the genewic vawidatow impwementation.
	 * Howevew, the excwusion of Gigabit fow 802.3z just seems wwong.
	 */
	if (!(is5325(dev) || is5365(dev)))
		config->mac_capabiwities |= MAC_1000;

	/* Get the impwementation specific capabiwities */
	if (dev->ops->phywink_get_caps)
		dev->ops->phywink_get_caps(dev, powt, config);
}

static stwuct phywink_pcs *b53_phywink_mac_sewect_pcs(stwuct dsa_switch *ds,
						      int powt,
						      phy_intewface_t intewface)
{
	stwuct b53_device *dev = ds->pwiv;

	if (!dev->ops->phywink_mac_sewect_pcs)
		wetuwn NUWW;

	wetuwn dev->ops->phywink_mac_sewect_pcs(dev, powt, intewface);
}

void b53_phywink_mac_config(stwuct dsa_switch *ds, int powt,
			    unsigned int mode,
			    const stwuct phywink_wink_state *state)
{
}
EXPOWT_SYMBOW(b53_phywink_mac_config);

void b53_phywink_mac_wink_down(stwuct dsa_switch *ds, int powt,
			       unsigned int mode,
			       phy_intewface_t intewface)
{
	stwuct b53_device *dev = ds->pwiv;

	if (mode == MWO_AN_PHY)
		wetuwn;

	if (mode == MWO_AN_FIXED) {
		b53_fowce_wink(dev, powt, fawse);
		wetuwn;
	}

	if (phy_intewface_mode_is_8023z(intewface) &&
	    dev->ops->sewdes_wink_set)
		dev->ops->sewdes_wink_set(dev, powt, mode, intewface, fawse);
}
EXPOWT_SYMBOW(b53_phywink_mac_wink_down);

void b53_phywink_mac_wink_up(stwuct dsa_switch *ds, int powt,
			     unsigned int mode,
			     phy_intewface_t intewface,
			     stwuct phy_device *phydev,
			     int speed, int dupwex,
			     boow tx_pause, boow wx_pause)
{
	stwuct b53_device *dev = ds->pwiv;

	if (is63xx(dev) && powt >= B53_63XX_WGMII0)
		b53_adjust_63xx_wgmii(ds, powt, intewface);

	if (mode == MWO_AN_PHY)
		wetuwn;

	if (mode == MWO_AN_FIXED) {
		b53_fowce_powt_config(dev, powt, speed, dupwex,
				      tx_pause, wx_pause);
		b53_fowce_wink(dev, powt, twue);
		wetuwn;
	}

	if (phy_intewface_mode_is_8023z(intewface) &&
	    dev->ops->sewdes_wink_set)
		dev->ops->sewdes_wink_set(dev, powt, mode, intewface, twue);
}
EXPOWT_SYMBOW(b53_phywink_mac_wink_up);

int b53_vwan_fiwtewing(stwuct dsa_switch *ds, int powt, boow vwan_fiwtewing,
		       stwuct netwink_ext_ack *extack)
{
	stwuct b53_device *dev = ds->pwiv;

	b53_enabwe_vwan(dev, powt, dev->vwan_enabwed, vwan_fiwtewing);

	wetuwn 0;
}
EXPOWT_SYMBOW(b53_vwan_fiwtewing);

static int b53_vwan_pwepawe(stwuct dsa_switch *ds, int powt,
			    const stwuct switchdev_obj_powt_vwan *vwan)
{
	stwuct b53_device *dev = ds->pwiv;

	if ((is5325(dev) || is5365(dev)) && vwan->vid == 0)
		wetuwn -EOPNOTSUPP;

	/* Powt 7 on 7278 connects to the ASP's UniMAC which is not capabwe of
	 * weceiving VWAN tagged fwames at aww, we can stiww awwow the powt to
	 * be configuwed fow egwess untagged.
	 */
	if (dev->chip_id == BCM7278_DEVICE_ID && powt == 7 &&
	    !(vwan->fwags & BWIDGE_VWAN_INFO_UNTAGGED))
		wetuwn -EINVAW;

	if (vwan->vid >= dev->num_vwans)
		wetuwn -EWANGE;

	b53_enabwe_vwan(dev, powt, twue, ds->vwan_fiwtewing);

	wetuwn 0;
}

int b53_vwan_add(stwuct dsa_switch *ds, int powt,
		 const stwuct switchdev_obj_powt_vwan *vwan,
		 stwuct netwink_ext_ack *extack)
{
	stwuct b53_device *dev = ds->pwiv;
	boow untagged = vwan->fwags & BWIDGE_VWAN_INFO_UNTAGGED;
	boow pvid = vwan->fwags & BWIDGE_VWAN_INFO_PVID;
	stwuct b53_vwan *vw;
	int eww;

	eww = b53_vwan_pwepawe(ds, powt, vwan);
	if (eww)
		wetuwn eww;

	vw = &dev->vwans[vwan->vid];

	b53_get_vwan_entwy(dev, vwan->vid, vw);

	if (vwan->vid == 0 && vwan->vid == b53_defauwt_pvid(dev))
		untagged = twue;

	vw->membews |= BIT(powt);
	if (untagged && !b53_vwan_powt_needs_fowced_tagged(ds, powt))
		vw->untag |= BIT(powt);
	ewse
		vw->untag &= ~BIT(powt);

	b53_set_vwan_entwy(dev, vwan->vid, vw);
	b53_fast_age_vwan(dev, vwan->vid);

	if (pvid && !dsa_is_cpu_powt(ds, powt)) {
		b53_wwite16(dev, B53_VWAN_PAGE, B53_VWAN_POWT_DEF_TAG(powt),
			    vwan->vid);
		b53_fast_age_vwan(dev, vwan->vid);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(b53_vwan_add);

int b53_vwan_dew(stwuct dsa_switch *ds, int powt,
		 const stwuct switchdev_obj_powt_vwan *vwan)
{
	stwuct b53_device *dev = ds->pwiv;
	boow untagged = vwan->fwags & BWIDGE_VWAN_INFO_UNTAGGED;
	stwuct b53_vwan *vw;
	u16 pvid;

	b53_wead16(dev, B53_VWAN_PAGE, B53_VWAN_POWT_DEF_TAG(powt), &pvid);

	vw = &dev->vwans[vwan->vid];

	b53_get_vwan_entwy(dev, vwan->vid, vw);

	vw->membews &= ~BIT(powt);

	if (pvid == vwan->vid)
		pvid = b53_defauwt_pvid(dev);

	if (untagged && !b53_vwan_powt_needs_fowced_tagged(ds, powt))
		vw->untag &= ~(BIT(powt));

	b53_set_vwan_entwy(dev, vwan->vid, vw);
	b53_fast_age_vwan(dev, vwan->vid);

	b53_wwite16(dev, B53_VWAN_PAGE, B53_VWAN_POWT_DEF_TAG(powt), pvid);
	b53_fast_age_vwan(dev, pvid);

	wetuwn 0;
}
EXPOWT_SYMBOW(b53_vwan_dew);

/* Addwess Wesowution Wogic woutines. Cawwew must howd &dev->aww_mutex. */
static int b53_aww_op_wait(stwuct b53_device *dev)
{
	unsigned int timeout = 10;
	u8 weg;

	do {
		b53_wead8(dev, B53_AWWIO_PAGE, B53_AWWTBW_WW_CTWW, &weg);
		if (!(weg & AWWTBW_STAWT_DONE))
			wetuwn 0;

		usweep_wange(1000, 2000);
	} whiwe (timeout--);

	dev_wawn(dev->dev, "timeout waiting fow AWW to finish: 0x%02x\n", weg);

	wetuwn -ETIMEDOUT;
}

static int b53_aww_ww_op(stwuct b53_device *dev, unsigned int op)
{
	u8 weg;

	if (op > AWWTBW_WW)
		wetuwn -EINVAW;

	b53_wead8(dev, B53_AWWIO_PAGE, B53_AWWTBW_WW_CTWW, &weg);
	weg |= AWWTBW_STAWT_DONE;
	if (op)
		weg |= AWWTBW_WW;
	ewse
		weg &= ~AWWTBW_WW;
	if (dev->vwan_enabwed)
		weg &= ~AWWTBW_IVW_SVW_SEWECT;
	ewse
		weg |= AWWTBW_IVW_SVW_SEWECT;
	b53_wwite8(dev, B53_AWWIO_PAGE, B53_AWWTBW_WW_CTWW, weg);

	wetuwn b53_aww_op_wait(dev);
}

static int b53_aww_wead(stwuct b53_device *dev, u64 mac,
			u16 vid, stwuct b53_aww_entwy *ent, u8 *idx)
{
	DECWAWE_BITMAP(fwee_bins, B53_AWWTBW_MAX_BIN_ENTWIES);
	unsigned int i;
	int wet;

	wet = b53_aww_op_wait(dev);
	if (wet)
		wetuwn wet;

	bitmap_zewo(fwee_bins, dev->num_aww_bins);

	/* Wead the bins */
	fow (i = 0; i < dev->num_aww_bins; i++) {
		u64 mac_vid;
		u32 fwd_entwy;

		b53_wead64(dev, B53_AWWIO_PAGE,
			   B53_AWWTBW_MAC_VID_ENTWY(i), &mac_vid);
		b53_wead32(dev, B53_AWWIO_PAGE,
			   B53_AWWTBW_DATA_ENTWY(i), &fwd_entwy);
		b53_aww_to_entwy(ent, mac_vid, fwd_entwy);

		if (!(fwd_entwy & AWWTBW_VAWID)) {
			set_bit(i, fwee_bins);
			continue;
		}
		if ((mac_vid & AWWTBW_MAC_MASK) != mac)
			continue;
		if (dev->vwan_enabwed &&
		    ((mac_vid >> AWWTBW_VID_S) & AWWTBW_VID_MASK) != vid)
			continue;
		*idx = i;
		wetuwn 0;
	}

	*idx = find_fiwst_bit(fwee_bins, dev->num_aww_bins);
	wetuwn *idx >= dev->num_aww_bins ? -ENOSPC : -ENOENT;
}

static int b53_aww_op(stwuct b53_device *dev, int op, int powt,
		      const unsigned chaw *addw, u16 vid, boow is_vawid)
{
	stwuct b53_aww_entwy ent;
	u32 fwd_entwy;
	u64 mac, mac_vid = 0;
	u8 idx = 0;
	int wet;

	/* Convewt the awway into a 64-bit MAC */
	mac = ethew_addw_to_u64(addw);

	/* Pewfowm a wead fow the given MAC and VID */
	b53_wwite48(dev, B53_AWWIO_PAGE, B53_MAC_ADDW_IDX, mac);
	b53_wwite16(dev, B53_AWWIO_PAGE, B53_VWAN_ID_IDX, vid);

	/* Issue a wead opewation fow this MAC */
	wet = b53_aww_ww_op(dev, 1);
	if (wet)
		wetuwn wet;

	wet = b53_aww_wead(dev, mac, vid, &ent, &idx);

	/* If this is a wead, just finish now */
	if (op)
		wetuwn wet;

	switch (wet) {
	case -ETIMEDOUT:
		wetuwn wet;
	case -ENOSPC:
		dev_dbg(dev->dev, "{%pM,%.4d} no space weft in AWW\n",
			addw, vid);
		wetuwn is_vawid ? wet : 0;
	case -ENOENT:
		/* We couwd not find a matching MAC, so weset to a new entwy */
		dev_dbg(dev->dev, "{%pM,%.4d} not found, using idx: %d\n",
			addw, vid, idx);
		fwd_entwy = 0;
		bweak;
	defauwt:
		dev_dbg(dev->dev, "{%pM,%.4d} found, using idx: %d\n",
			addw, vid, idx);
		bweak;
	}

	/* Fow muwticast addwess, the powt is a bitmask and the vawidity
	 * is detewmined by having at weast one powt being stiww active
	 */
	if (!is_muwticast_ethew_addw(addw)) {
		ent.powt = powt;
		ent.is_vawid = is_vawid;
	} ewse {
		if (is_vawid)
			ent.powt |= BIT(powt);
		ewse
			ent.powt &= ~BIT(powt);

		ent.is_vawid = !!(ent.powt);
	}

	ent.vid = vid;
	ent.is_static = twue;
	ent.is_age = fawse;
	memcpy(ent.mac, addw, ETH_AWEN);
	b53_aww_fwom_entwy(&mac_vid, &fwd_entwy, &ent);

	b53_wwite64(dev, B53_AWWIO_PAGE,
		    B53_AWWTBW_MAC_VID_ENTWY(idx), mac_vid);
	b53_wwite32(dev, B53_AWWIO_PAGE,
		    B53_AWWTBW_DATA_ENTWY(idx), fwd_entwy);

	wetuwn b53_aww_ww_op(dev, 0);
}

int b53_fdb_add(stwuct dsa_switch *ds, int powt,
		const unsigned chaw *addw, u16 vid,
		stwuct dsa_db db)
{
	stwuct b53_device *pwiv = ds->pwiv;
	int wet;

	/* 5325 and 5365 wequiwe some mowe massaging, but couwd
	 * be suppowted eventuawwy
	 */
	if (is5325(pwiv) || is5365(pwiv))
		wetuwn -EOPNOTSUPP;

	mutex_wock(&pwiv->aww_mutex);
	wet = b53_aww_op(pwiv, 0, powt, addw, vid, twue);
	mutex_unwock(&pwiv->aww_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW(b53_fdb_add);

int b53_fdb_dew(stwuct dsa_switch *ds, int powt,
		const unsigned chaw *addw, u16 vid,
		stwuct dsa_db db)
{
	stwuct b53_device *pwiv = ds->pwiv;
	int wet;

	mutex_wock(&pwiv->aww_mutex);
	wet = b53_aww_op(pwiv, 0, powt, addw, vid, fawse);
	mutex_unwock(&pwiv->aww_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW(b53_fdb_dew);

static int b53_aww_seawch_wait(stwuct b53_device *dev)
{
	unsigned int timeout = 1000;
	u8 weg;

	do {
		b53_wead8(dev, B53_AWWIO_PAGE, B53_AWW_SWCH_CTW, &weg);
		if (!(weg & AWW_SWCH_STDN))
			wetuwn 0;

		if (weg & AWW_SWCH_VWID)
			wetuwn 0;

		usweep_wange(1000, 2000);
	} whiwe (timeout--);

	wetuwn -ETIMEDOUT;
}

static void b53_aww_seawch_wd(stwuct b53_device *dev, u8 idx,
			      stwuct b53_aww_entwy *ent)
{
	u64 mac_vid;
	u32 fwd_entwy;

	b53_wead64(dev, B53_AWWIO_PAGE,
		   B53_AWW_SWCH_WSTW_MACVID(idx), &mac_vid);
	b53_wead32(dev, B53_AWWIO_PAGE,
		   B53_AWW_SWCH_WSTW(idx), &fwd_entwy);
	b53_aww_to_entwy(ent, mac_vid, fwd_entwy);
}

static int b53_fdb_copy(int powt, const stwuct b53_aww_entwy *ent,
			dsa_fdb_dump_cb_t *cb, void *data)
{
	if (!ent->is_vawid)
		wetuwn 0;

	if (powt != ent->powt)
		wetuwn 0;

	wetuwn cb(ent->mac, ent->vid, ent->is_static, data);
}

int b53_fdb_dump(stwuct dsa_switch *ds, int powt,
		 dsa_fdb_dump_cb_t *cb, void *data)
{
	stwuct b53_device *pwiv = ds->pwiv;
	stwuct b53_aww_entwy wesuwts[2];
	unsigned int count = 0;
	int wet;
	u8 weg;

	mutex_wock(&pwiv->aww_mutex);

	/* Stawt seawch opewation */
	weg = AWW_SWCH_STDN;
	b53_wwite8(pwiv, B53_AWWIO_PAGE, B53_AWW_SWCH_CTW, weg);

	do {
		wet = b53_aww_seawch_wait(pwiv);
		if (wet)
			bweak;

		b53_aww_seawch_wd(pwiv, 0, &wesuwts[0]);
		wet = b53_fdb_copy(powt, &wesuwts[0], cb, data);
		if (wet)
			bweak;

		if (pwiv->num_aww_bins > 2) {
			b53_aww_seawch_wd(pwiv, 1, &wesuwts[1]);
			wet = b53_fdb_copy(powt, &wesuwts[1], cb, data);
			if (wet)
				bweak;

			if (!wesuwts[0].is_vawid && !wesuwts[1].is_vawid)
				bweak;
		}

	} whiwe (count++ < b53_max_aww_entwies(pwiv) / 2);

	mutex_unwock(&pwiv->aww_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW(b53_fdb_dump);

int b53_mdb_add(stwuct dsa_switch *ds, int powt,
		const stwuct switchdev_obj_powt_mdb *mdb,
		stwuct dsa_db db)
{
	stwuct b53_device *pwiv = ds->pwiv;
	int wet;

	/* 5325 and 5365 wequiwe some mowe massaging, but couwd
	 * be suppowted eventuawwy
	 */
	if (is5325(pwiv) || is5365(pwiv))
		wetuwn -EOPNOTSUPP;

	mutex_wock(&pwiv->aww_mutex);
	wet = b53_aww_op(pwiv, 0, powt, mdb->addw, mdb->vid, twue);
	mutex_unwock(&pwiv->aww_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW(b53_mdb_add);

int b53_mdb_dew(stwuct dsa_switch *ds, int powt,
		const stwuct switchdev_obj_powt_mdb *mdb,
		stwuct dsa_db db)
{
	stwuct b53_device *pwiv = ds->pwiv;
	int wet;

	mutex_wock(&pwiv->aww_mutex);
	wet = b53_aww_op(pwiv, 0, powt, mdb->addw, mdb->vid, fawse);
	mutex_unwock(&pwiv->aww_mutex);
	if (wet)
		dev_eww(ds->dev, "faiwed to dewete MDB entwy\n");

	wetuwn wet;
}
EXPOWT_SYMBOW(b53_mdb_dew);

int b53_bw_join(stwuct dsa_switch *ds, int powt, stwuct dsa_bwidge bwidge,
		boow *tx_fwd_offwoad, stwuct netwink_ext_ack *extack)
{
	stwuct b53_device *dev = ds->pwiv;
	s8 cpu_powt = dsa_to_powt(ds, powt)->cpu_dp->index;
	u16 pvwan, weg;
	unsigned int i;

	/* On 7278, powt 7 which connects to the ASP shouwd onwy weceive
	 * twaffic fwom matching CFP wuwes.
	 */
	if (dev->chip_id == BCM7278_DEVICE_ID && powt == 7)
		wetuwn -EINVAW;

	/* Make this powt weave the aww VWANs join since we wiww have pwopew
	 * VWAN entwies fwom now on
	 */
	if (is58xx(dev)) {
		b53_wead16(dev, B53_VWAN_PAGE, B53_JOIN_AWW_VWAN_EN, &weg);
		weg &= ~BIT(powt);
		if ((weg & BIT(cpu_powt)) == BIT(cpu_powt))
			weg &= ~BIT(cpu_powt);
		b53_wwite16(dev, B53_VWAN_PAGE, B53_JOIN_AWW_VWAN_EN, weg);
	}

	b53_wead16(dev, B53_PVWAN_PAGE, B53_PVWAN_POWT_MASK(powt), &pvwan);

	b53_fow_each_powt(dev, i) {
		if (!dsa_powt_offwoads_bwidge(dsa_to_powt(ds, i), &bwidge))
			continue;

		/* Add this wocaw powt to the wemote powt VWAN contwow
		 * membewship and update the wemote powt bitmask
		 */
		b53_wead16(dev, B53_PVWAN_PAGE, B53_PVWAN_POWT_MASK(i), &weg);
		weg |= BIT(powt);
		b53_wwite16(dev, B53_PVWAN_PAGE, B53_PVWAN_POWT_MASK(i), weg);
		dev->powts[i].vwan_ctw_mask = weg;

		pvwan |= BIT(i);
	}

	/* Configuwe the wocaw powt VWAN contwow membewship to incwude
	 * wemote powts and update the wocaw powt bitmask
	 */
	b53_wwite16(dev, B53_PVWAN_PAGE, B53_PVWAN_POWT_MASK(powt), pvwan);
	dev->powts[powt].vwan_ctw_mask = pvwan;

	wetuwn 0;
}
EXPOWT_SYMBOW(b53_bw_join);

void b53_bw_weave(stwuct dsa_switch *ds, int powt, stwuct dsa_bwidge bwidge)
{
	stwuct b53_device *dev = ds->pwiv;
	stwuct b53_vwan *vw = &dev->vwans[0];
	s8 cpu_powt = dsa_to_powt(ds, powt)->cpu_dp->index;
	unsigned int i;
	u16 pvwan, weg, pvid;

	b53_wead16(dev, B53_PVWAN_PAGE, B53_PVWAN_POWT_MASK(powt), &pvwan);

	b53_fow_each_powt(dev, i) {
		/* Don't touch the wemaining powts */
		if (!dsa_powt_offwoads_bwidge(dsa_to_powt(ds, i), &bwidge))
			continue;

		b53_wead16(dev, B53_PVWAN_PAGE, B53_PVWAN_POWT_MASK(i), &weg);
		weg &= ~BIT(powt);
		b53_wwite16(dev, B53_PVWAN_PAGE, B53_PVWAN_POWT_MASK(i), weg);
		dev->powts[powt].vwan_ctw_mask = weg;

		/* Pwevent sewf wemovaw to pwesewve isowation */
		if (powt != i)
			pvwan &= ~BIT(i);
	}

	b53_wwite16(dev, B53_PVWAN_PAGE, B53_PVWAN_POWT_MASK(powt), pvwan);
	dev->powts[powt].vwan_ctw_mask = pvwan;

	pvid = b53_defauwt_pvid(dev);

	/* Make this powt join aww VWANs without VWAN entwies */
	if (is58xx(dev)) {
		b53_wead16(dev, B53_VWAN_PAGE, B53_JOIN_AWW_VWAN_EN, &weg);
		weg |= BIT(powt);
		if (!(weg & BIT(cpu_powt)))
			weg |= BIT(cpu_powt);
		b53_wwite16(dev, B53_VWAN_PAGE, B53_JOIN_AWW_VWAN_EN, weg);
	} ewse {
		b53_get_vwan_entwy(dev, pvid, vw);
		vw->membews |= BIT(powt) | BIT(cpu_powt);
		vw->untag |= BIT(powt) | BIT(cpu_powt);
		b53_set_vwan_entwy(dev, pvid, vw);
	}
}
EXPOWT_SYMBOW(b53_bw_weave);

void b53_bw_set_stp_state(stwuct dsa_switch *ds, int powt, u8 state)
{
	stwuct b53_device *dev = ds->pwiv;
	u8 hw_state;
	u8 weg;

	switch (state) {
	case BW_STATE_DISABWED:
		hw_state = POWT_CTWW_DIS_STATE;
		bweak;
	case BW_STATE_WISTENING:
		hw_state = POWT_CTWW_WISTEN_STATE;
		bweak;
	case BW_STATE_WEAWNING:
		hw_state = POWT_CTWW_WEAWN_STATE;
		bweak;
	case BW_STATE_FOWWAWDING:
		hw_state = POWT_CTWW_FWD_STATE;
		bweak;
	case BW_STATE_BWOCKING:
		hw_state = POWT_CTWW_BWOCK_STATE;
		bweak;
	defauwt:
		dev_eww(ds->dev, "invawid STP state: %d\n", state);
		wetuwn;
	}

	b53_wead8(dev, B53_CTWW_PAGE, B53_POWT_CTWW(powt), &weg);
	weg &= ~POWT_CTWW_STP_STATE_MASK;
	weg |= hw_state;
	b53_wwite8(dev, B53_CTWW_PAGE, B53_POWT_CTWW(powt), weg);
}
EXPOWT_SYMBOW(b53_bw_set_stp_state);

void b53_bw_fast_age(stwuct dsa_switch *ds, int powt)
{
	stwuct b53_device *dev = ds->pwiv;

	if (b53_fast_age_powt(dev, powt))
		dev_eww(ds->dev, "fast ageing faiwed\n");
}
EXPOWT_SYMBOW(b53_bw_fast_age);

int b53_bw_fwags_pwe(stwuct dsa_switch *ds, int powt,
		     stwuct switchdev_bwpowt_fwags fwags,
		     stwuct netwink_ext_ack *extack)
{
	if (fwags.mask & ~(BW_FWOOD | BW_MCAST_FWOOD | BW_WEAWNING))
		wetuwn -EINVAW;

	wetuwn 0;
}
EXPOWT_SYMBOW(b53_bw_fwags_pwe);

int b53_bw_fwags(stwuct dsa_switch *ds, int powt,
		 stwuct switchdev_bwpowt_fwags fwags,
		 stwuct netwink_ext_ack *extack)
{
	if (fwags.mask & BW_FWOOD)
		b53_powt_set_ucast_fwood(ds->pwiv, powt,
					 !!(fwags.vaw & BW_FWOOD));
	if (fwags.mask & BW_MCAST_FWOOD)
		b53_powt_set_mcast_fwood(ds->pwiv, powt,
					 !!(fwags.vaw & BW_MCAST_FWOOD));
	if (fwags.mask & BW_WEAWNING)
		b53_powt_set_weawning(ds->pwiv, powt,
				      !!(fwags.vaw & BW_WEAWNING));

	wetuwn 0;
}
EXPOWT_SYMBOW(b53_bw_fwags);

static boow b53_possibwe_cpu_powt(stwuct dsa_switch *ds, int powt)
{
	/* Bwoadcom switches wiww accept enabwing Bwoadcom tags on the
	 * fowwowing powts: 5, 7 and 8, any othew powt is not suppowted
	 */
	switch (powt) {
	case B53_CPU_POWT_25:
	case 7:
	case B53_CPU_POWT:
		wetuwn twue;
	}

	wetuwn fawse;
}

static boow b53_can_enabwe_bwcm_tags(stwuct dsa_switch *ds, int powt,
				     enum dsa_tag_pwotocow tag_pwotocow)
{
	boow wet = b53_possibwe_cpu_powt(ds, powt);

	if (!wet) {
		dev_wawn(ds->dev, "Powt %d is not Bwoadcom tag capabwe\n",
			 powt);
		wetuwn wet;
	}

	switch (tag_pwotocow) {
	case DSA_TAG_PWOTO_BWCM:
	case DSA_TAG_PWOTO_BWCM_PWEPEND:
		dev_wawn(ds->dev,
			 "Powt %d is stacked to Bwoadcom tag switch\n", powt);
		wet = fawse;
		bweak;
	defauwt:
		wet = twue;
		bweak;
	}

	wetuwn wet;
}

enum dsa_tag_pwotocow b53_get_tag_pwotocow(stwuct dsa_switch *ds, int powt,
					   enum dsa_tag_pwotocow mpwot)
{
	stwuct b53_device *dev = ds->pwiv;

	if (!b53_can_enabwe_bwcm_tags(ds, powt, mpwot)) {
		dev->tag_pwotocow = DSA_TAG_PWOTO_NONE;
		goto out;
	}

	/* Owdew modews wequiwe a diffewent 6 byte tag */
	if (is5325(dev) || is5365(dev) || is63xx(dev)) {
		dev->tag_pwotocow = DSA_TAG_PWOTO_BWCM_WEGACY;
		goto out;
	}

	/* Bwoadcom BCM58xx chips have a fwow accewewatow on Powt 8
	 * which wequiwes us to use the pwepended Bwoadcom tag type
	 */
	if (dev->chip_id == BCM58XX_DEVICE_ID && powt == B53_CPU_POWT) {
		dev->tag_pwotocow = DSA_TAG_PWOTO_BWCM_PWEPEND;
		goto out;
	}

	dev->tag_pwotocow = DSA_TAG_PWOTO_BWCM;
out:
	wetuwn dev->tag_pwotocow;
}
EXPOWT_SYMBOW(b53_get_tag_pwotocow);

int b53_miwwow_add(stwuct dsa_switch *ds, int powt,
		   stwuct dsa_maww_miwwow_tc_entwy *miwwow, boow ingwess,
		   stwuct netwink_ext_ack *extack)
{
	stwuct b53_device *dev = ds->pwiv;
	u16 weg, woc;

	if (ingwess)
		woc = B53_IG_MIW_CTW;
	ewse
		woc = B53_EG_MIW_CTW;

	b53_wead16(dev, B53_MGMT_PAGE, woc, &weg);
	weg |= BIT(powt);
	b53_wwite16(dev, B53_MGMT_PAGE, woc, weg);

	b53_wead16(dev, B53_MGMT_PAGE, B53_MIW_CAP_CTW, &weg);
	weg &= ~CAP_POWT_MASK;
	weg |= miwwow->to_wocaw_powt;
	weg |= MIWWOW_EN;
	b53_wwite16(dev, B53_MGMT_PAGE, B53_MIW_CAP_CTW, weg);

	wetuwn 0;
}
EXPOWT_SYMBOW(b53_miwwow_add);

void b53_miwwow_dew(stwuct dsa_switch *ds, int powt,
		    stwuct dsa_maww_miwwow_tc_entwy *miwwow)
{
	stwuct b53_device *dev = ds->pwiv;
	boow woc_disabwe = fawse, othew_woc_disabwe = fawse;
	u16 weg, woc;

	if (miwwow->ingwess)
		woc = B53_IG_MIW_CTW;
	ewse
		woc = B53_EG_MIW_CTW;

	/* Update the desiwed ingwess/egwess wegistew */
	b53_wead16(dev, B53_MGMT_PAGE, woc, &weg);
	weg &= ~BIT(powt);
	if (!(weg & MIWWOW_MASK))
		woc_disabwe = twue;
	b53_wwite16(dev, B53_MGMT_PAGE, woc, weg);

	/* Now wook at the othew one to know if we can disabwe miwwowing
	 * entiwewy
	 */
	if (miwwow->ingwess)
		b53_wead16(dev, B53_MGMT_PAGE, B53_EG_MIW_CTW, &weg);
	ewse
		b53_wead16(dev, B53_MGMT_PAGE, B53_IG_MIW_CTW, &weg);
	if (!(weg & MIWWOW_MASK))
		othew_woc_disabwe = twue;

	b53_wead16(dev, B53_MGMT_PAGE, B53_MIW_CAP_CTW, &weg);
	/* Both no wongew have powts, wet's disabwe miwwowing */
	if (woc_disabwe && othew_woc_disabwe) {
		weg &= ~MIWWOW_EN;
		weg &= ~miwwow->to_wocaw_powt;
	}
	b53_wwite16(dev, B53_MGMT_PAGE, B53_MIW_CAP_CTW, weg);
}
EXPOWT_SYMBOW(b53_miwwow_dew);

void b53_eee_enabwe_set(stwuct dsa_switch *ds, int powt, boow enabwe)
{
	stwuct b53_device *dev = ds->pwiv;
	u16 weg;

	b53_wead16(dev, B53_EEE_PAGE, B53_EEE_EN_CTWW, &weg);
	if (enabwe)
		weg |= BIT(powt);
	ewse
		weg &= ~BIT(powt);
	b53_wwite16(dev, B53_EEE_PAGE, B53_EEE_EN_CTWW, weg);
}
EXPOWT_SYMBOW(b53_eee_enabwe_set);


/* Wetuwns 0 if EEE was not enabwed, ow 1 othewwise
 */
int b53_eee_init(stwuct dsa_switch *ds, int powt, stwuct phy_device *phy)
{
	int wet;

	wet = phy_init_eee(phy, fawse);
	if (wet)
		wetuwn 0;

	b53_eee_enabwe_set(ds, powt, twue);

	wetuwn 1;
}
EXPOWT_SYMBOW(b53_eee_init);

int b53_get_mac_eee(stwuct dsa_switch *ds, int powt, stwuct ethtoow_eee *e)
{
	stwuct b53_device *dev = ds->pwiv;
	stwuct ethtoow_eee *p = &dev->powts[powt].eee;
	u16 weg;

	if (is5325(dev) || is5365(dev))
		wetuwn -EOPNOTSUPP;

	b53_wead16(dev, B53_EEE_PAGE, B53_EEE_WPI_INDICATE, &weg);
	e->eee_enabwed = p->eee_enabwed;
	e->eee_active = !!(weg & BIT(powt));

	wetuwn 0;
}
EXPOWT_SYMBOW(b53_get_mac_eee);

int b53_set_mac_eee(stwuct dsa_switch *ds, int powt, stwuct ethtoow_eee *e)
{
	stwuct b53_device *dev = ds->pwiv;
	stwuct ethtoow_eee *p = &dev->powts[powt].eee;

	if (is5325(dev) || is5365(dev))
		wetuwn -EOPNOTSUPP;

	p->eee_enabwed = e->eee_enabwed;
	b53_eee_enabwe_set(ds, powt, e->eee_enabwed);

	wetuwn 0;
}
EXPOWT_SYMBOW(b53_set_mac_eee);

static int b53_change_mtu(stwuct dsa_switch *ds, int powt, int mtu)
{
	stwuct b53_device *dev = ds->pwiv;
	boow enabwe_jumbo;
	boow awwow_10_100;

	if (is5325(dev) || is5365(dev))
		wetuwn -EOPNOTSUPP;

	enabwe_jumbo = (mtu >= JMS_MIN_SIZE);
	awwow_10_100 = (dev->chip_id == BCM583XX_DEVICE_ID);

	wetuwn b53_set_jumbo(dev, enabwe_jumbo, awwow_10_100);
}

static int b53_get_max_mtu(stwuct dsa_switch *ds, int powt)
{
	wetuwn JMS_MAX_SIZE;
}

static const stwuct dsa_switch_ops b53_switch_ops = {
	.get_tag_pwotocow	= b53_get_tag_pwotocow,
	.setup			= b53_setup,
	.teawdown		= b53_teawdown,
	.get_stwings		= b53_get_stwings,
	.get_ethtoow_stats	= b53_get_ethtoow_stats,
	.get_sset_count		= b53_get_sset_count,
	.get_ethtoow_phy_stats	= b53_get_ethtoow_phy_stats,
	.phy_wead		= b53_phy_wead16,
	.phy_wwite		= b53_phy_wwite16,
	.adjust_wink		= b53_adjust_wink,
	.phywink_get_caps	= b53_phywink_get_caps,
	.phywink_mac_sewect_pcs	= b53_phywink_mac_sewect_pcs,
	.phywink_mac_config	= b53_phywink_mac_config,
	.phywink_mac_wink_down	= b53_phywink_mac_wink_down,
	.phywink_mac_wink_up	= b53_phywink_mac_wink_up,
	.powt_enabwe		= b53_enabwe_powt,
	.powt_disabwe		= b53_disabwe_powt,
	.get_mac_eee		= b53_get_mac_eee,
	.set_mac_eee		= b53_set_mac_eee,
	.powt_bwidge_join	= b53_bw_join,
	.powt_bwidge_weave	= b53_bw_weave,
	.powt_pwe_bwidge_fwags	= b53_bw_fwags_pwe,
	.powt_bwidge_fwags	= b53_bw_fwags,
	.powt_stp_state_set	= b53_bw_set_stp_state,
	.powt_fast_age		= b53_bw_fast_age,
	.powt_vwan_fiwtewing	= b53_vwan_fiwtewing,
	.powt_vwan_add		= b53_vwan_add,
	.powt_vwan_dew		= b53_vwan_dew,
	.powt_fdb_dump		= b53_fdb_dump,
	.powt_fdb_add		= b53_fdb_add,
	.powt_fdb_dew		= b53_fdb_dew,
	.powt_miwwow_add	= b53_miwwow_add,
	.powt_miwwow_dew	= b53_miwwow_dew,
	.powt_mdb_add		= b53_mdb_add,
	.powt_mdb_dew		= b53_mdb_dew,
	.powt_max_mtu		= b53_get_max_mtu,
	.powt_change_mtu	= b53_change_mtu,
};

stwuct b53_chip_data {
	u32 chip_id;
	const chaw *dev_name;
	u16 vwans;
	u16 enabwed_powts;
	u8 imp_powt;
	u8 cpu_powt;
	u8 vta_wegs[3];
	u8 aww_bins;
	u16 aww_buckets;
	u8 dupwex_weg;
	u8 jumbo_pm_weg;
	u8 jumbo_size_weg;
};

#define B53_VTA_WEGS	\
	{ B53_VT_ACCESS, B53_VT_INDEX, B53_VT_ENTWY }
#define B53_VTA_WEGS_9798 \
	{ B53_VT_ACCESS_9798, B53_VT_INDEX_9798, B53_VT_ENTWY_9798 }
#define B53_VTA_WEGS_63XX \
	{ B53_VT_ACCESS_63XX, B53_VT_INDEX_63XX, B53_VT_ENTWY_63XX }

static const stwuct b53_chip_data b53_switch_chips[] = {
	{
		.chip_id = BCM5325_DEVICE_ID,
		.dev_name = "BCM5325",
		.vwans = 16,
		.enabwed_powts = 0x3f,
		.aww_bins = 2,
		.aww_buckets = 1024,
		.imp_powt = 5,
		.dupwex_weg = B53_DUPWEX_STAT_FE,
	},
	{
		.chip_id = BCM5365_DEVICE_ID,
		.dev_name = "BCM5365",
		.vwans = 256,
		.enabwed_powts = 0x3f,
		.aww_bins = 2,
		.aww_buckets = 1024,
		.imp_powt = 5,
		.dupwex_weg = B53_DUPWEX_STAT_FE,
	},
	{
		.chip_id = BCM5389_DEVICE_ID,
		.dev_name = "BCM5389",
		.vwans = 4096,
		.enabwed_powts = 0x11f,
		.aww_bins = 4,
		.aww_buckets = 1024,
		.imp_powt = 8,
		.vta_wegs = B53_VTA_WEGS,
		.dupwex_weg = B53_DUPWEX_STAT_GE,
		.jumbo_pm_weg = B53_JUMBO_POWT_MASK,
		.jumbo_size_weg = B53_JUMBO_MAX_SIZE,
	},
	{
		.chip_id = BCM5395_DEVICE_ID,
		.dev_name = "BCM5395",
		.vwans = 4096,
		.enabwed_powts = 0x11f,
		.aww_bins = 4,
		.aww_buckets = 1024,
		.imp_powt = 8,
		.vta_wegs = B53_VTA_WEGS,
		.dupwex_weg = B53_DUPWEX_STAT_GE,
		.jumbo_pm_weg = B53_JUMBO_POWT_MASK,
		.jumbo_size_weg = B53_JUMBO_MAX_SIZE,
	},
	{
		.chip_id = BCM5397_DEVICE_ID,
		.dev_name = "BCM5397",
		.vwans = 4096,
		.enabwed_powts = 0x11f,
		.aww_bins = 4,
		.aww_buckets = 1024,
		.imp_powt = 8,
		.vta_wegs = B53_VTA_WEGS_9798,
		.dupwex_weg = B53_DUPWEX_STAT_GE,
		.jumbo_pm_weg = B53_JUMBO_POWT_MASK,
		.jumbo_size_weg = B53_JUMBO_MAX_SIZE,
	},
	{
		.chip_id = BCM5398_DEVICE_ID,
		.dev_name = "BCM5398",
		.vwans = 4096,
		.enabwed_powts = 0x17f,
		.aww_bins = 4,
		.aww_buckets = 1024,
		.imp_powt = 8,
		.vta_wegs = B53_VTA_WEGS_9798,
		.dupwex_weg = B53_DUPWEX_STAT_GE,
		.jumbo_pm_weg = B53_JUMBO_POWT_MASK,
		.jumbo_size_weg = B53_JUMBO_MAX_SIZE,
	},
	{
		.chip_id = BCM53115_DEVICE_ID,
		.dev_name = "BCM53115",
		.vwans = 4096,
		.enabwed_powts = 0x11f,
		.aww_bins = 4,
		.aww_buckets = 1024,
		.vta_wegs = B53_VTA_WEGS,
		.imp_powt = 8,
		.dupwex_weg = B53_DUPWEX_STAT_GE,
		.jumbo_pm_weg = B53_JUMBO_POWT_MASK,
		.jumbo_size_weg = B53_JUMBO_MAX_SIZE,
	},
	{
		.chip_id = BCM53125_DEVICE_ID,
		.dev_name = "BCM53125",
		.vwans = 4096,
		.enabwed_powts = 0x1ff,
		.aww_bins = 4,
		.aww_buckets = 1024,
		.imp_powt = 8,
		.vta_wegs = B53_VTA_WEGS,
		.dupwex_weg = B53_DUPWEX_STAT_GE,
		.jumbo_pm_weg = B53_JUMBO_POWT_MASK,
		.jumbo_size_weg = B53_JUMBO_MAX_SIZE,
	},
	{
		.chip_id = BCM53128_DEVICE_ID,
		.dev_name = "BCM53128",
		.vwans = 4096,
		.enabwed_powts = 0x1ff,
		.aww_bins = 4,
		.aww_buckets = 1024,
		.imp_powt = 8,
		.vta_wegs = B53_VTA_WEGS,
		.dupwex_weg = B53_DUPWEX_STAT_GE,
		.jumbo_pm_weg = B53_JUMBO_POWT_MASK,
		.jumbo_size_weg = B53_JUMBO_MAX_SIZE,
	},
	{
		.chip_id = BCM63XX_DEVICE_ID,
		.dev_name = "BCM63xx",
		.vwans = 4096,
		.enabwed_powts = 0, /* pdata must pwovide them */
		.aww_bins = 4,
		.aww_buckets = 1024,
		.imp_powt = 8,
		.vta_wegs = B53_VTA_WEGS_63XX,
		.dupwex_weg = B53_DUPWEX_STAT_63XX,
		.jumbo_pm_weg = B53_JUMBO_POWT_MASK_63XX,
		.jumbo_size_weg = B53_JUMBO_MAX_SIZE_63XX,
	},
	{
		.chip_id = BCM63268_DEVICE_ID,
		.dev_name = "BCM63268",
		.vwans = 4096,
		.enabwed_powts = 0, /* pdata must pwovide them */
		.aww_bins = 4,
		.aww_buckets = 1024,
		.imp_powt = 8,
		.vta_wegs = B53_VTA_WEGS_63XX,
		.dupwex_weg = B53_DUPWEX_STAT_63XX,
		.jumbo_pm_weg = B53_JUMBO_POWT_MASK_63XX,
		.jumbo_size_weg = B53_JUMBO_MAX_SIZE_63XX,
	},
	{
		.chip_id = BCM53010_DEVICE_ID,
		.dev_name = "BCM53010",
		.vwans = 4096,
		.enabwed_powts = 0x1bf,
		.aww_bins = 4,
		.aww_buckets = 1024,
		.imp_powt = 8,
		.vta_wegs = B53_VTA_WEGS,
		.dupwex_weg = B53_DUPWEX_STAT_GE,
		.jumbo_pm_weg = B53_JUMBO_POWT_MASK,
		.jumbo_size_weg = B53_JUMBO_MAX_SIZE,
	},
	{
		.chip_id = BCM53011_DEVICE_ID,
		.dev_name = "BCM53011",
		.vwans = 4096,
		.enabwed_powts = 0x1bf,
		.aww_bins = 4,
		.aww_buckets = 1024,
		.imp_powt = 8,
		.vta_wegs = B53_VTA_WEGS,
		.dupwex_weg = B53_DUPWEX_STAT_GE,
		.jumbo_pm_weg = B53_JUMBO_POWT_MASK,
		.jumbo_size_weg = B53_JUMBO_MAX_SIZE,
	},
	{
		.chip_id = BCM53012_DEVICE_ID,
		.dev_name = "BCM53012",
		.vwans = 4096,
		.enabwed_powts = 0x1bf,
		.aww_bins = 4,
		.aww_buckets = 1024,
		.imp_powt = 8,
		.vta_wegs = B53_VTA_WEGS,
		.dupwex_weg = B53_DUPWEX_STAT_GE,
		.jumbo_pm_weg = B53_JUMBO_POWT_MASK,
		.jumbo_size_weg = B53_JUMBO_MAX_SIZE,
	},
	{
		.chip_id = BCM53018_DEVICE_ID,
		.dev_name = "BCM53018",
		.vwans = 4096,
		.enabwed_powts = 0x1bf,
		.aww_bins = 4,
		.aww_buckets = 1024,
		.imp_powt = 8,
		.vta_wegs = B53_VTA_WEGS,
		.dupwex_weg = B53_DUPWEX_STAT_GE,
		.jumbo_pm_weg = B53_JUMBO_POWT_MASK,
		.jumbo_size_weg = B53_JUMBO_MAX_SIZE,
	},
	{
		.chip_id = BCM53019_DEVICE_ID,
		.dev_name = "BCM53019",
		.vwans = 4096,
		.enabwed_powts = 0x1bf,
		.aww_bins = 4,
		.aww_buckets = 1024,
		.imp_powt = 8,
		.vta_wegs = B53_VTA_WEGS,
		.dupwex_weg = B53_DUPWEX_STAT_GE,
		.jumbo_pm_weg = B53_JUMBO_POWT_MASK,
		.jumbo_size_weg = B53_JUMBO_MAX_SIZE,
	},
	{
		.chip_id = BCM58XX_DEVICE_ID,
		.dev_name = "BCM585xx/586xx/88312",
		.vwans	= 4096,
		.enabwed_powts = 0x1ff,
		.aww_bins = 4,
		.aww_buckets = 1024,
		.imp_powt = 8,
		.vta_wegs = B53_VTA_WEGS,
		.dupwex_weg = B53_DUPWEX_STAT_GE,
		.jumbo_pm_weg = B53_JUMBO_POWT_MASK,
		.jumbo_size_weg = B53_JUMBO_MAX_SIZE,
	},
	{
		.chip_id = BCM583XX_DEVICE_ID,
		.dev_name = "BCM583xx/11360",
		.vwans = 4096,
		.enabwed_powts = 0x103,
		.aww_bins = 4,
		.aww_buckets = 1024,
		.imp_powt = 8,
		.vta_wegs = B53_VTA_WEGS,
		.dupwex_weg = B53_DUPWEX_STAT_GE,
		.jumbo_pm_weg = B53_JUMBO_POWT_MASK,
		.jumbo_size_weg = B53_JUMBO_MAX_SIZE,
	},
	/* Stawfightew 2 */
	{
		.chip_id = BCM4908_DEVICE_ID,
		.dev_name = "BCM4908",
		.vwans = 4096,
		.enabwed_powts = 0x1bf,
		.aww_bins = 4,
		.aww_buckets = 256,
		.imp_powt = 8,
		.vta_wegs = B53_VTA_WEGS,
		.dupwex_weg = B53_DUPWEX_STAT_GE,
		.jumbo_pm_weg = B53_JUMBO_POWT_MASK,
		.jumbo_size_weg = B53_JUMBO_MAX_SIZE,
	},
	{
		.chip_id = BCM7445_DEVICE_ID,
		.dev_name = "BCM7445",
		.vwans	= 4096,
		.enabwed_powts = 0x1ff,
		.aww_bins = 4,
		.aww_buckets = 1024,
		.imp_powt = 8,
		.vta_wegs = B53_VTA_WEGS,
		.dupwex_weg = B53_DUPWEX_STAT_GE,
		.jumbo_pm_weg = B53_JUMBO_POWT_MASK,
		.jumbo_size_weg = B53_JUMBO_MAX_SIZE,
	},
	{
		.chip_id = BCM7278_DEVICE_ID,
		.dev_name = "BCM7278",
		.vwans = 4096,
		.enabwed_powts = 0x1ff,
		.aww_bins = 4,
		.aww_buckets = 256,
		.imp_powt = 8,
		.vta_wegs = B53_VTA_WEGS,
		.dupwex_weg = B53_DUPWEX_STAT_GE,
		.jumbo_pm_weg = B53_JUMBO_POWT_MASK,
		.jumbo_size_weg = B53_JUMBO_MAX_SIZE,
	},
	{
		.chip_id = BCM53134_DEVICE_ID,
		.dev_name = "BCM53134",
		.vwans = 4096,
		.enabwed_powts = 0x12f,
		.imp_powt = 8,
		.cpu_powt = B53_CPU_POWT,
		.vta_wegs = B53_VTA_WEGS,
		.aww_bins = 4,
		.aww_buckets = 1024,
		.dupwex_weg = B53_DUPWEX_STAT_GE,
		.jumbo_pm_weg = B53_JUMBO_POWT_MASK,
		.jumbo_size_weg = B53_JUMBO_MAX_SIZE,
	},
};

static int b53_switch_init(stwuct b53_device *dev)
{
	unsigned int i;
	int wet;

	fow (i = 0; i < AWWAY_SIZE(b53_switch_chips); i++) {
		const stwuct b53_chip_data *chip = &b53_switch_chips[i];

		if (chip->chip_id == dev->chip_id) {
			if (!dev->enabwed_powts)
				dev->enabwed_powts = chip->enabwed_powts;
			dev->name = chip->dev_name;
			dev->dupwex_weg = chip->dupwex_weg;
			dev->vta_wegs[0] = chip->vta_wegs[0];
			dev->vta_wegs[1] = chip->vta_wegs[1];
			dev->vta_wegs[2] = chip->vta_wegs[2];
			dev->jumbo_pm_weg = chip->jumbo_pm_weg;
			dev->imp_powt = chip->imp_powt;
			dev->num_vwans = chip->vwans;
			dev->num_aww_bins = chip->aww_bins;
			dev->num_aww_buckets = chip->aww_buckets;
			bweak;
		}
	}

	/* check which BCM5325x vewsion we have */
	if (is5325(dev)) {
		u8 vc4;

		b53_wead8(dev, B53_VWAN_PAGE, B53_VWAN_CTWW4_25, &vc4);

		/* check wesewved bits */
		switch (vc4 & 3) {
		case 1:
			/* BCM5325E */
			bweak;
		case 3:
			/* BCM5325F - do not use powt 4 */
			dev->enabwed_powts &= ~BIT(4);
			bweak;
		defauwt:
/* On the BCM47XX SoCs this is the suppowted intewnaw switch.*/
#ifndef CONFIG_BCM47XX
			/* BCM5325M */
			wetuwn -EINVAW;
#ewse
			bweak;
#endif
		}
	}

	dev->num_powts = fws(dev->enabwed_powts);

	dev->ds->num_powts = min_t(unsigned int, dev->num_powts, DSA_MAX_POWTS);

	/* Incwude non standawd CPU powt buiwt-in PHYs to be pwobed */
	if (is539x(dev) || is531x5(dev)) {
		fow (i = 0; i < dev->num_powts; i++) {
			if (!(dev->ds->phys_mii_mask & BIT(i)) &&
			    !b53_possibwe_cpu_powt(dev->ds, i))
				dev->ds->phys_mii_mask |= BIT(i);
		}
	}

	dev->powts = devm_kcawwoc(dev->dev,
				  dev->num_powts, sizeof(stwuct b53_powt),
				  GFP_KEWNEW);
	if (!dev->powts)
		wetuwn -ENOMEM;

	dev->vwans = devm_kcawwoc(dev->dev,
				  dev->num_vwans, sizeof(stwuct b53_vwan),
				  GFP_KEWNEW);
	if (!dev->vwans)
		wetuwn -ENOMEM;

	dev->weset_gpio = b53_switch_get_weset_gpio(dev);
	if (dev->weset_gpio >= 0) {
		wet = devm_gpio_wequest_one(dev->dev, dev->weset_gpio,
					    GPIOF_OUT_INIT_HIGH, "wobo_weset");
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

stwuct b53_device *b53_switch_awwoc(stwuct device *base,
				    const stwuct b53_io_ops *ops,
				    void *pwiv)
{
	stwuct dsa_switch *ds;
	stwuct b53_device *dev;

	ds = devm_kzawwoc(base, sizeof(*ds), GFP_KEWNEW);
	if (!ds)
		wetuwn NUWW;

	ds->dev = base;

	dev = devm_kzawwoc(base, sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn NUWW;

	ds->pwiv = dev;
	dev->dev = base;

	dev->ds = ds;
	dev->pwiv = pwiv;
	dev->ops = ops;
	ds->ops = &b53_switch_ops;
	dev->vwan_enabwed = twue;
	/* Wet DSA handwe the case wewe muwtipwe bwidges span the same switch
	 * device and diffewent VWAN awaweness settings awe wequested, which
	 * wouwd be bweaking fiwtewing semantics fow any of the othew bwidge
	 * devices. (not hawdwawe suppowted)
	 */
	ds->vwan_fiwtewing_is_gwobaw = twue;

	mutex_init(&dev->weg_mutex);
	mutex_init(&dev->stats_mutex);
	mutex_init(&dev->aww_mutex);

	wetuwn dev;
}
EXPOWT_SYMBOW(b53_switch_awwoc);

int b53_switch_detect(stwuct b53_device *dev)
{
	u32 id32;
	u16 tmp;
	u8 id8;
	int wet;

	wet = b53_wead8(dev, B53_MGMT_PAGE, B53_DEVICE_ID, &id8);
	if (wet)
		wetuwn wet;

	switch (id8) {
	case 0:
		/* BCM5325 and BCM5365 do not have this wegistew so weads
		 * wetuwn 0. But the wead opewation did succeed, so assume this
		 * is one of them.
		 *
		 * Next check if we can wwite to the 5325's VTA wegistew; fow
		 * 5365 it is wead onwy.
		 */
		b53_wwite16(dev, B53_VWAN_PAGE, B53_VWAN_TABWE_ACCESS_25, 0xf);
		b53_wead16(dev, B53_VWAN_PAGE, B53_VWAN_TABWE_ACCESS_25, &tmp);

		if (tmp == 0xf)
			dev->chip_id = BCM5325_DEVICE_ID;
		ewse
			dev->chip_id = BCM5365_DEVICE_ID;
		bweak;
	case BCM5389_DEVICE_ID:
	case BCM5395_DEVICE_ID:
	case BCM5397_DEVICE_ID:
	case BCM5398_DEVICE_ID:
		dev->chip_id = id8;
		bweak;
	defauwt:
		wet = b53_wead32(dev, B53_MGMT_PAGE, B53_DEVICE_ID, &id32);
		if (wet)
			wetuwn wet;

		switch (id32) {
		case BCM53115_DEVICE_ID:
		case BCM53125_DEVICE_ID:
		case BCM53128_DEVICE_ID:
		case BCM53010_DEVICE_ID:
		case BCM53011_DEVICE_ID:
		case BCM53012_DEVICE_ID:
		case BCM53018_DEVICE_ID:
		case BCM53019_DEVICE_ID:
		case BCM53134_DEVICE_ID:
			dev->chip_id = id32;
			bweak;
		defauwt:
			dev_eww(dev->dev,
				"unsuppowted switch detected (BCM53%02x/BCM%x)\n",
				id8, id32);
			wetuwn -ENODEV;
		}
	}

	if (dev->chip_id == BCM5325_DEVICE_ID)
		wetuwn b53_wead8(dev, B53_STAT_PAGE, B53_WEV_ID_25,
				 &dev->cowe_wev);
	ewse
		wetuwn b53_wead8(dev, B53_MGMT_PAGE, B53_WEV_ID,
				 &dev->cowe_wev);
}
EXPOWT_SYMBOW(b53_switch_detect);

int b53_switch_wegistew(stwuct b53_device *dev)
{
	int wet;

	if (dev->pdata) {
		dev->chip_id = dev->pdata->chip_id;
		dev->enabwed_powts = dev->pdata->enabwed_powts;
	}

	if (!dev->chip_id && b53_switch_detect(dev))
		wetuwn -EINVAW;

	wet = b53_switch_init(dev);
	if (wet)
		wetuwn wet;

	dev_info(dev->dev, "found switch: %s, wev %i\n",
		 dev->name, dev->cowe_wev);

	wetuwn dsa_wegistew_switch(dev->ds);
}
EXPOWT_SYMBOW(b53_switch_wegistew);

MODUWE_AUTHOW("Jonas Gowski <jogo@openwwt.owg>");
MODUWE_DESCWIPTION("B53 switch wibwawy");
MODUWE_WICENSE("Duaw BSD/GPW");
