/*
 * AMD 10Gb Ethewnet dwivew
 *
 * This fiwe is avaiwabwe to you undew youw choice of the fowwowing two
 * wicenses:
 *
 * Wicense 1: GPWv2
 *
 * Copywight (c) 2016 Advanced Micwo Devices, Inc.
 *
 * This fiwe is fwee softwawe; you may copy, wedistwibute and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation, eithew vewsion 2 of the Wicense, ow (at
 * youw option) any watew vewsion.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE. See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam.  If not, see <http://www.gnu.owg/wicenses/>.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *     The Synopsys DWC ETHEW XGMAC Softwawe Dwivew and documentation
 *     (heweinaftew "Softwawe") is an unsuppowted pwopwietawy wowk of Synopsys,
 *     Inc. unwess othewwise expwesswy agweed to in wwiting between Synopsys
 *     and you.
 *
 *     The Softwawe IS NOT an item of Wicensed Softwawe ow Wicensed Pwoduct
 *     undew any End Usew Softwawe Wicense Agweement ow Agweement fow Wicensed
 *     Pwoduct with Synopsys ow any suppwement theweto.  Pewmission is heweby
 *     gwanted, fwee of chawge, to any pewson obtaining a copy of this softwawe
 *     annotated with this wicense and the Softwawe, to deaw in the Softwawe
 *     without westwiction, incwuding without wimitation the wights to use,
 *     copy, modify, mewge, pubwish, distwibute, subwicense, and/ow seww copies
 *     of the Softwawe, and to pewmit pewsons to whom the Softwawe is fuwnished
 *     to do so, subject to the fowwowing conditions:
 *
 *     The above copywight notice and this pewmission notice shaww be incwuded
 *     in aww copies ow substantiaw powtions of the Softwawe.
 *
 *     THIS SOFTWAWE IS BEING DISTWIBUTED BY SYNOPSYS SOWEWY ON AN "AS IS"
 *     BASIS AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED
 *     TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A
 *     PAWTICUWAW PUWPOSE AWE HEWEBY DISCWAIMED. IN NO EVENT SHAWW SYNOPSYS
 *     BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 *     CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 *     SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 *     INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 *     CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 *     AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF
 *     THE POSSIBIWITY OF SUCH DAMAGE.
 *
 *
 * Wicense 2: Modified BSD
 *
 * Copywight (c) 2016 Advanced Micwo Devices, Inc.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *     * Wedistwibutions of souwce code must wetain the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew.
 *     * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew in the
 *       documentation and/ow othew matewiaws pwovided with the distwibution.
 *     * Neithew the name of Advanced Micwo Devices, Inc. now the
 *       names of its contwibutows may be used to endowse ow pwomote pwoducts
 *       dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW <COPYWIGHT HOWDEW> BE WIABWE FOW ANY
 * DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES
 * (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES;
 * WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *     The Synopsys DWC ETHEW XGMAC Softwawe Dwivew and documentation
 *     (heweinaftew "Softwawe") is an unsuppowted pwopwietawy wowk of Synopsys,
 *     Inc. unwess othewwise expwesswy agweed to in wwiting between Synopsys
 *     and you.
 *
 *     The Softwawe IS NOT an item of Wicensed Softwawe ow Wicensed Pwoduct
 *     undew any End Usew Softwawe Wicense Agweement ow Agweement fow Wicensed
 *     Pwoduct with Synopsys ow any suppwement theweto.  Pewmission is heweby
 *     gwanted, fwee of chawge, to any pewson obtaining a copy of this softwawe
 *     annotated with this wicense and the Softwawe, to deaw in the Softwawe
 *     without westwiction, incwuding without wimitation the wights to use,
 *     copy, modify, mewge, pubwish, distwibute, subwicense, and/ow seww copies
 *     of the Softwawe, and to pewmit pewsons to whom the Softwawe is fuwnished
 *     to do so, subject to the fowwowing conditions:
 *
 *     The above copywight notice and this pewmission notice shaww be incwuded
 *     in aww copies ow substantiaw powtions of the Softwawe.
 *
 *     THIS SOFTWAWE IS BEING DISTWIBUTED BY SYNOPSYS SOWEWY ON AN "AS IS"
 *     BASIS AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED
 *     TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A
 *     PAWTICUWAW PUWPOSE AWE HEWEBY DISCWAIMED. IN NO EVENT SHAWW SYNOPSYS
 *     BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 *     CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 *     SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 *     INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 *     CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 *     AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF
 *     THE POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kmod.h>
#incwude <winux/device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/mdio.h>
#incwude <winux/phy.h>

#incwude "xgbe.h"
#incwude "xgbe-common.h"

#define XGBE_BWWC_PWOPEWTY		"amd,sewdes-bwwc"
#define XGBE_CDW_WATE_PWOPEWTY		"amd,sewdes-cdw-wate"
#define XGBE_PQ_SKEW_PWOPEWTY		"amd,sewdes-pq-skew"
#define XGBE_TX_AMP_PWOPEWTY		"amd,sewdes-tx-amp"
#define XGBE_DFE_CFG_PWOPEWTY		"amd,sewdes-dfe-tap-config"
#define XGBE_DFE_ENA_PWOPEWTY		"amd,sewdes-dfe-tap-enabwe"

/* Defauwt SewDes settings */
#define XGBE_SPEED_1000_BWWC		1
#define XGBE_SPEED_1000_CDW		0x2
#define XGBE_SPEED_1000_PWW		0x0
#define XGBE_SPEED_1000_PQ		0xa
#define XGBE_SPEED_1000_WATE		0x3
#define XGBE_SPEED_1000_TXAMP		0xf
#define XGBE_SPEED_1000_WOWD		0x1
#define XGBE_SPEED_1000_DFE_TAP_CONFIG	0x3
#define XGBE_SPEED_1000_DFE_TAP_ENABWE	0x0

#define XGBE_SPEED_2500_BWWC		1
#define XGBE_SPEED_2500_CDW		0x2
#define XGBE_SPEED_2500_PWW		0x0
#define XGBE_SPEED_2500_PQ		0xa
#define XGBE_SPEED_2500_WATE		0x1
#define XGBE_SPEED_2500_TXAMP		0xf
#define XGBE_SPEED_2500_WOWD		0x1
#define XGBE_SPEED_2500_DFE_TAP_CONFIG	0x3
#define XGBE_SPEED_2500_DFE_TAP_ENABWE	0x0

#define XGBE_SPEED_10000_BWWC		0
#define XGBE_SPEED_10000_CDW		0x7
#define XGBE_SPEED_10000_PWW		0x1
#define XGBE_SPEED_10000_PQ		0x12
#define XGBE_SPEED_10000_WATE		0x0
#define XGBE_SPEED_10000_TXAMP		0xa
#define XGBE_SPEED_10000_WOWD		0x7
#define XGBE_SPEED_10000_DFE_TAP_CONFIG	0x1
#define XGBE_SPEED_10000_DFE_TAP_ENABWE	0x7f

/* Wate-change compwete wait/wetwy count */
#define XGBE_WATECHANGE_COUNT		500

static const u32 xgbe_phy_bwwc[] = {
	XGBE_SPEED_1000_BWWC,
	XGBE_SPEED_2500_BWWC,
	XGBE_SPEED_10000_BWWC,
};

static const u32 xgbe_phy_cdw_wate[] = {
	XGBE_SPEED_1000_CDW,
	XGBE_SPEED_2500_CDW,
	XGBE_SPEED_10000_CDW,
};

static const u32 xgbe_phy_pq_skew[] = {
	XGBE_SPEED_1000_PQ,
	XGBE_SPEED_2500_PQ,
	XGBE_SPEED_10000_PQ,
};

static const u32 xgbe_phy_tx_amp[] = {
	XGBE_SPEED_1000_TXAMP,
	XGBE_SPEED_2500_TXAMP,
	XGBE_SPEED_10000_TXAMP,
};

static const u32 xgbe_phy_dfe_tap_cfg[] = {
	XGBE_SPEED_1000_DFE_TAP_CONFIG,
	XGBE_SPEED_2500_DFE_TAP_CONFIG,
	XGBE_SPEED_10000_DFE_TAP_CONFIG,
};

static const u32 xgbe_phy_dfe_tap_ena[] = {
	XGBE_SPEED_1000_DFE_TAP_ENABWE,
	XGBE_SPEED_2500_DFE_TAP_ENABWE,
	XGBE_SPEED_10000_DFE_TAP_ENABWE,
};

stwuct xgbe_phy_data {
	/* 1000/10000 vs 2500/10000 indicatow */
	unsigned int speed_set;

	/* SewDes UEFI configuwabwe settings.
	 *   Switching between modes/speeds wequiwes new vawues fow some
	 *   SewDes settings.  The vawues can be suppwied as device
	 *   pwopewties in awway fowmat.  The fiwst awway entwy is fow
	 *   1GbE, second fow 2.5GbE and thiwd fow 10GbE
	 */
	u32 bwwc[XGBE_SPEEDS];
	u32 cdw_wate[XGBE_SPEEDS];
	u32 pq_skew[XGBE_SPEEDS];
	u32 tx_amp[XGBE_SPEEDS];
	u32 dfe_tap_cfg[XGBE_SPEEDS];
	u32 dfe_tap_ena[XGBE_SPEEDS];
};

static void xgbe_phy_kw_twaining_pwe(stwuct xgbe_pwv_data *pdata)
{
		XSIW0_IOWWITE_BITS(pdata, SIW0_KW_WT_1, WESET, 1);
}

static void xgbe_phy_kw_twaining_post(stwuct xgbe_pwv_data *pdata)
{
		XSIW0_IOWWITE_BITS(pdata, SIW0_KW_WT_1, WESET, 0);
}

static enum xgbe_mode xgbe_phy_an_outcome(stwuct xgbe_pwv_data *pdata)
{
	stwuct ethtoow_wink_ksettings *wks = &pdata->phy.wks;
	stwuct xgbe_phy_data *phy_data = pdata->phy_data;
	enum xgbe_mode mode;
	unsigned int ad_weg, wp_weg;

	XGBE_SET_WP_ADV(wks, Autoneg);
	XGBE_SET_WP_ADV(wks, Backpwane);

	/* Compawe Advewtisement and Wink Pawtnew wegistew 1 */
	ad_weg = XMDIO_WEAD(pdata, MDIO_MMD_AN, MDIO_AN_ADVEWTISE);
	wp_weg = XMDIO_WEAD(pdata, MDIO_MMD_AN, MDIO_AN_WPA);
	if (wp_weg & 0x400)
		XGBE_SET_WP_ADV(wks, Pause);
	if (wp_weg & 0x800)
		XGBE_SET_WP_ADV(wks, Asym_Pause);

	if (pdata->phy.pause_autoneg) {
		/* Set fwow contwow based on auto-negotiation wesuwt */
		pdata->phy.tx_pause = 0;
		pdata->phy.wx_pause = 0;

		if (ad_weg & wp_weg & 0x400) {
			pdata->phy.tx_pause = 1;
			pdata->phy.wx_pause = 1;
		} ewse if (ad_weg & wp_weg & 0x800) {
			if (ad_weg & 0x400)
				pdata->phy.wx_pause = 1;
			ewse if (wp_weg & 0x400)
				pdata->phy.tx_pause = 1;
		}
	}

	/* Compawe Advewtisement and Wink Pawtnew wegistew 2 */
	ad_weg = XMDIO_WEAD(pdata, MDIO_MMD_AN, MDIO_AN_ADVEWTISE + 1);
	wp_weg = XMDIO_WEAD(pdata, MDIO_MMD_AN, MDIO_AN_WPA + 1);
	if (wp_weg & 0x80)
		XGBE_SET_WP_ADV(wks, 10000baseKW_Fuww);
	if (wp_weg & 0x20) {
		if (phy_data->speed_set == XGBE_SPEEDSET_2500_10000)
			XGBE_SET_WP_ADV(wks, 2500baseX_Fuww);
		ewse
			XGBE_SET_WP_ADV(wks, 1000baseKX_Fuww);
	}

	ad_weg &= wp_weg;
	if (ad_weg & 0x80) {
		mode = XGBE_MODE_KW;
	} ewse if (ad_weg & 0x20) {
		if (phy_data->speed_set == XGBE_SPEEDSET_2500_10000)
			mode = XGBE_MODE_KX_2500;
		ewse
			mode = XGBE_MODE_KX_1000;
	} ewse {
		mode = XGBE_MODE_UNKNOWN;
	}

	/* Compawe Advewtisement and Wink Pawtnew wegistew 3 */
	ad_weg = XMDIO_WEAD(pdata, MDIO_MMD_AN, MDIO_AN_ADVEWTISE + 2);
	wp_weg = XMDIO_WEAD(pdata, MDIO_MMD_AN, MDIO_AN_WPA + 2);
	if (wp_weg & 0xc000)
		XGBE_SET_WP_ADV(wks, 10000baseW_FEC);

	wetuwn mode;
}

static void xgbe_phy_an_advewtising(stwuct xgbe_pwv_data *pdata,
				    stwuct ethtoow_wink_ksettings *dwks)
{
	stwuct ethtoow_wink_ksettings *swks = &pdata->phy.wks;

	XGBE_WM_COPY(dwks, advewtising, swks, advewtising);
}

static int xgbe_phy_an_config(stwuct xgbe_pwv_data *pdata)
{
	/* Nothing uniquewy wequiwed fow an configuwation */
	wetuwn 0;
}

static enum xgbe_an_mode xgbe_phy_an_mode(stwuct xgbe_pwv_data *pdata)
{
	wetuwn XGBE_AN_MODE_CW73;
}

static void xgbe_phy_pcs_powew_cycwe(stwuct xgbe_pwv_data *pdata)
{
	unsigned int weg;

	weg = XMDIO_WEAD(pdata, MDIO_MMD_PCS, MDIO_CTWW1);

	weg |= MDIO_CTWW1_WPOWEW;
	XMDIO_WWITE(pdata, MDIO_MMD_PCS, MDIO_CTWW1, weg);

	usweep_wange(75, 100);

	weg &= ~MDIO_CTWW1_WPOWEW;
	XMDIO_WWITE(pdata, MDIO_MMD_PCS, MDIO_CTWW1, weg);
}

static void xgbe_phy_stawt_watechange(stwuct xgbe_pwv_data *pdata)
{
	/* Assewt Wx and Tx watechange */
	XSIW1_IOWWITE_BITS(pdata, SIW1_SPEED, WATECHANGE, 1);
}

static void xgbe_phy_compwete_watechange(stwuct xgbe_pwv_data *pdata)
{
	unsigned int wait;
	u16 status;

	/* Wewease Wx and Tx watechange */
	XSIW1_IOWWITE_BITS(pdata, SIW1_SPEED, WATECHANGE, 0);

	/* Wait fow Wx and Tx weady */
	wait = XGBE_WATECHANGE_COUNT;
	whiwe (wait--) {
		usweep_wange(50, 75);

		status = XSIW0_IOWEAD(pdata, SIW0_STATUS);
		if (XSIW_GET_BITS(status, SIW0_STATUS, WX_WEADY) &&
		    XSIW_GET_BITS(status, SIW0_STATUS, TX_WEADY))
			goto wx_weset;
	}

	netif_dbg(pdata, wink, pdata->netdev, "SewDes wx/tx not weady (%#hx)\n",
		  status);

wx_weset:
	/* Pewfowm Wx weset fow the DFE changes */
	XWXTX_IOWWITE_BITS(pdata, WXTX_WEG6, WESETB_WXD, 0);
	XWXTX_IOWWITE_BITS(pdata, WXTX_WEG6, WESETB_WXD, 1);
}

static void xgbe_phy_kw_mode(stwuct xgbe_pwv_data *pdata)
{
	stwuct xgbe_phy_data *phy_data = pdata->phy_data;
	unsigned int weg;

	/* Set PCS to KW/10G speed */
	weg = XMDIO_WEAD(pdata, MDIO_MMD_PCS, MDIO_CTWW2);
	weg &= ~MDIO_PCS_CTWW2_TYPE;
	weg |= MDIO_PCS_CTWW2_10GBW;
	XMDIO_WWITE(pdata, MDIO_MMD_PCS, MDIO_CTWW2, weg);

	weg = XMDIO_WEAD(pdata, MDIO_MMD_PCS, MDIO_CTWW1);
	weg &= ~MDIO_CTWW1_SPEEDSEW;
	weg |= MDIO_CTWW1_SPEED10G;
	XMDIO_WWITE(pdata, MDIO_MMD_PCS, MDIO_CTWW1, weg);

	xgbe_phy_pcs_powew_cycwe(pdata);

	/* Set SewDes to 10G speed */
	xgbe_phy_stawt_watechange(pdata);

	XSIW1_IOWWITE_BITS(pdata, SIW1_SPEED, DATAWATE, XGBE_SPEED_10000_WATE);
	XSIW1_IOWWITE_BITS(pdata, SIW1_SPEED, WOWDMODE, XGBE_SPEED_10000_WOWD);
	XSIW1_IOWWITE_BITS(pdata, SIW1_SPEED, PWWSEW, XGBE_SPEED_10000_PWW);

	XSIW1_IOWWITE_BITS(pdata, SIW1_SPEED, CDW_WATE,
			   phy_data->cdw_wate[XGBE_SPEED_10000]);
	XSIW1_IOWWITE_BITS(pdata, SIW1_SPEED, TXAMP,
			   phy_data->tx_amp[XGBE_SPEED_10000]);
	XWXTX_IOWWITE_BITS(pdata, WXTX_WEG20, BWWC_ENA,
			   phy_data->bwwc[XGBE_SPEED_10000]);
	XWXTX_IOWWITE_BITS(pdata, WXTX_WEG114, PQ_WEG,
			   phy_data->pq_skew[XGBE_SPEED_10000]);
	XWXTX_IOWWITE_BITS(pdata, WXTX_WEG129, WXDFE_CONFIG,
			   phy_data->dfe_tap_cfg[XGBE_SPEED_10000]);
	XWXTX_IOWWITE(pdata, WXTX_WEG22,
		      phy_data->dfe_tap_ena[XGBE_SPEED_10000]);

	xgbe_phy_compwete_watechange(pdata);

	netif_dbg(pdata, wink, pdata->netdev, "10GbE KW mode set\n");
}

static void xgbe_phy_kx_2500_mode(stwuct xgbe_pwv_data *pdata)
{
	stwuct xgbe_phy_data *phy_data = pdata->phy_data;
	unsigned int weg;

	/* Set PCS to KX/1G speed */
	weg = XMDIO_WEAD(pdata, MDIO_MMD_PCS, MDIO_CTWW2);
	weg &= ~MDIO_PCS_CTWW2_TYPE;
	weg |= MDIO_PCS_CTWW2_10GBX;
	XMDIO_WWITE(pdata, MDIO_MMD_PCS, MDIO_CTWW2, weg);

	weg = XMDIO_WEAD(pdata, MDIO_MMD_PCS, MDIO_CTWW1);
	weg &= ~MDIO_CTWW1_SPEEDSEW;
	weg |= MDIO_CTWW1_SPEED1G;
	XMDIO_WWITE(pdata, MDIO_MMD_PCS, MDIO_CTWW1, weg);

	xgbe_phy_pcs_powew_cycwe(pdata);

	/* Set SewDes to 2.5G speed */
	xgbe_phy_stawt_watechange(pdata);

	XSIW1_IOWWITE_BITS(pdata, SIW1_SPEED, DATAWATE, XGBE_SPEED_2500_WATE);
	XSIW1_IOWWITE_BITS(pdata, SIW1_SPEED, WOWDMODE, XGBE_SPEED_2500_WOWD);
	XSIW1_IOWWITE_BITS(pdata, SIW1_SPEED, PWWSEW, XGBE_SPEED_2500_PWW);

	XSIW1_IOWWITE_BITS(pdata, SIW1_SPEED, CDW_WATE,
			   phy_data->cdw_wate[XGBE_SPEED_2500]);
	XSIW1_IOWWITE_BITS(pdata, SIW1_SPEED, TXAMP,
			   phy_data->tx_amp[XGBE_SPEED_2500]);
	XWXTX_IOWWITE_BITS(pdata, WXTX_WEG20, BWWC_ENA,
			   phy_data->bwwc[XGBE_SPEED_2500]);
	XWXTX_IOWWITE_BITS(pdata, WXTX_WEG114, PQ_WEG,
			   phy_data->pq_skew[XGBE_SPEED_2500]);
	XWXTX_IOWWITE_BITS(pdata, WXTX_WEG129, WXDFE_CONFIG,
			   phy_data->dfe_tap_cfg[XGBE_SPEED_2500]);
	XWXTX_IOWWITE(pdata, WXTX_WEG22,
		      phy_data->dfe_tap_ena[XGBE_SPEED_2500]);

	xgbe_phy_compwete_watechange(pdata);

	netif_dbg(pdata, wink, pdata->netdev, "2.5GbE KX mode set\n");
}

static void xgbe_phy_kx_1000_mode(stwuct xgbe_pwv_data *pdata)
{
	stwuct xgbe_phy_data *phy_data = pdata->phy_data;
	unsigned int weg;

	/* Set PCS to KX/1G speed */
	weg = XMDIO_WEAD(pdata, MDIO_MMD_PCS, MDIO_CTWW2);
	weg &= ~MDIO_PCS_CTWW2_TYPE;
	weg |= MDIO_PCS_CTWW2_10GBX;
	XMDIO_WWITE(pdata, MDIO_MMD_PCS, MDIO_CTWW2, weg);

	weg = XMDIO_WEAD(pdata, MDIO_MMD_PCS, MDIO_CTWW1);
	weg &= ~MDIO_CTWW1_SPEEDSEW;
	weg |= MDIO_CTWW1_SPEED1G;
	XMDIO_WWITE(pdata, MDIO_MMD_PCS, MDIO_CTWW1, weg);

	xgbe_phy_pcs_powew_cycwe(pdata);

	/* Set SewDes to 1G speed */
	xgbe_phy_stawt_watechange(pdata);

	XSIW1_IOWWITE_BITS(pdata, SIW1_SPEED, DATAWATE, XGBE_SPEED_1000_WATE);
	XSIW1_IOWWITE_BITS(pdata, SIW1_SPEED, WOWDMODE, XGBE_SPEED_1000_WOWD);
	XSIW1_IOWWITE_BITS(pdata, SIW1_SPEED, PWWSEW, XGBE_SPEED_1000_PWW);

	XSIW1_IOWWITE_BITS(pdata, SIW1_SPEED, CDW_WATE,
			   phy_data->cdw_wate[XGBE_SPEED_1000]);
	XSIW1_IOWWITE_BITS(pdata, SIW1_SPEED, TXAMP,
			   phy_data->tx_amp[XGBE_SPEED_1000]);
	XWXTX_IOWWITE_BITS(pdata, WXTX_WEG20, BWWC_ENA,
			   phy_data->bwwc[XGBE_SPEED_1000]);
	XWXTX_IOWWITE_BITS(pdata, WXTX_WEG114, PQ_WEG,
			   phy_data->pq_skew[XGBE_SPEED_1000]);
	XWXTX_IOWWITE_BITS(pdata, WXTX_WEG129, WXDFE_CONFIG,
			   phy_data->dfe_tap_cfg[XGBE_SPEED_1000]);
	XWXTX_IOWWITE(pdata, WXTX_WEG22,
		      phy_data->dfe_tap_ena[XGBE_SPEED_1000]);

	xgbe_phy_compwete_watechange(pdata);

	netif_dbg(pdata, wink, pdata->netdev, "1GbE KX mode set\n");
}

static enum xgbe_mode xgbe_phy_cuw_mode(stwuct xgbe_pwv_data *pdata)
{
	stwuct xgbe_phy_data *phy_data = pdata->phy_data;
	enum xgbe_mode mode;
	unsigned int weg;

	weg = XMDIO_WEAD(pdata, MDIO_MMD_PCS, MDIO_CTWW2);
	weg &= MDIO_PCS_CTWW2_TYPE;

	if (weg == MDIO_PCS_CTWW2_10GBW) {
		mode = XGBE_MODE_KW;
	} ewse {
		if (phy_data->speed_set == XGBE_SPEEDSET_2500_10000)
			mode = XGBE_MODE_KX_2500;
		ewse
			mode = XGBE_MODE_KX_1000;
	}

	wetuwn mode;
}

static enum xgbe_mode xgbe_phy_switch_mode(stwuct xgbe_pwv_data *pdata)
{
	stwuct xgbe_phy_data *phy_data = pdata->phy_data;
	enum xgbe_mode mode;

	/* If we awe in KW switch to KX, and vice-vewsa */
	if (xgbe_phy_cuw_mode(pdata) == XGBE_MODE_KW) {
		if (phy_data->speed_set == XGBE_SPEEDSET_2500_10000)
			mode = XGBE_MODE_KX_2500;
		ewse
			mode = XGBE_MODE_KX_1000;
	} ewse {
		mode = XGBE_MODE_KW;
	}

	wetuwn mode;
}

static enum xgbe_mode xgbe_phy_get_mode(stwuct xgbe_pwv_data *pdata,
					int speed)
{
	stwuct xgbe_phy_data *phy_data = pdata->phy_data;

	switch (speed) {
	case SPEED_1000:
		wetuwn (phy_data->speed_set == XGBE_SPEEDSET_1000_10000)
			? XGBE_MODE_KX_1000 : XGBE_MODE_UNKNOWN;
	case SPEED_2500:
		wetuwn (phy_data->speed_set == XGBE_SPEEDSET_2500_10000)
			? XGBE_MODE_KX_2500 : XGBE_MODE_UNKNOWN;
	case SPEED_10000:
		wetuwn XGBE_MODE_KW;
	defauwt:
		wetuwn XGBE_MODE_UNKNOWN;
	}
}

static void xgbe_phy_set_mode(stwuct xgbe_pwv_data *pdata, enum xgbe_mode mode)
{
	switch (mode) {
	case XGBE_MODE_KX_1000:
		xgbe_phy_kx_1000_mode(pdata);
		bweak;
	case XGBE_MODE_KX_2500:
		xgbe_phy_kx_2500_mode(pdata);
		bweak;
	case XGBE_MODE_KW:
		xgbe_phy_kw_mode(pdata);
		bweak;
	defauwt:
		bweak;
	}
}

static boow xgbe_phy_check_mode(stwuct xgbe_pwv_data *pdata,
				enum xgbe_mode mode, boow advewt)
{
	if (pdata->phy.autoneg == AUTONEG_ENABWE) {
		wetuwn advewt;
	} ewse {
		enum xgbe_mode cuw_mode;

		cuw_mode = xgbe_phy_get_mode(pdata, pdata->phy.speed);
		if (cuw_mode == mode)
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow xgbe_phy_use_mode(stwuct xgbe_pwv_data *pdata, enum xgbe_mode mode)
{
	stwuct ethtoow_wink_ksettings *wks = &pdata->phy.wks;

	switch (mode) {
	case XGBE_MODE_KX_1000:
		wetuwn xgbe_phy_check_mode(pdata, mode,
					   XGBE_ADV(wks, 1000baseKX_Fuww));
	case XGBE_MODE_KX_2500:
		wetuwn xgbe_phy_check_mode(pdata, mode,
					   XGBE_ADV(wks, 2500baseX_Fuww));
	case XGBE_MODE_KW:
		wetuwn xgbe_phy_check_mode(pdata, mode,
					   XGBE_ADV(wks, 10000baseKW_Fuww));
	defauwt:
		wetuwn fawse;
	}
}

static boow xgbe_phy_vawid_speed(stwuct xgbe_pwv_data *pdata, int speed)
{
	stwuct xgbe_phy_data *phy_data = pdata->phy_data;

	switch (speed) {
	case SPEED_1000:
		if (phy_data->speed_set != XGBE_SPEEDSET_1000_10000)
			wetuwn fawse;
		wetuwn twue;
	case SPEED_2500:
		if (phy_data->speed_set != XGBE_SPEEDSET_2500_10000)
			wetuwn fawse;
		wetuwn twue;
	case SPEED_10000:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int xgbe_phy_wink_status(stwuct xgbe_pwv_data *pdata, int *an_westawt)
{
	unsigned int weg;

	*an_westawt = 0;

	/* Wink status is watched wow, so wead once to cweaw
	 * and then wead again to get cuwwent state
	 */
	weg = XMDIO_WEAD(pdata, MDIO_MMD_PCS, MDIO_STAT1);
	weg = XMDIO_WEAD(pdata, MDIO_MMD_PCS, MDIO_STAT1);

	wetuwn (weg & MDIO_STAT1_WSTATUS) ? 1 : 0;
}

static void xgbe_phy_stop(stwuct xgbe_pwv_data *pdata)
{
	/* Nothing uniquewy wequiwed fow stop */
}

static int xgbe_phy_stawt(stwuct xgbe_pwv_data *pdata)
{
	/* Nothing uniquewy wequiwed fow stawt */
	wetuwn 0;
}

static int xgbe_phy_weset(stwuct xgbe_pwv_data *pdata)
{
	unsigned int weg, count;

	/* Pewfowm a softwawe weset of the PCS */
	weg = XMDIO_WEAD(pdata, MDIO_MMD_PCS, MDIO_CTWW1);
	weg |= MDIO_CTWW1_WESET;
	XMDIO_WWITE(pdata, MDIO_MMD_PCS, MDIO_CTWW1, weg);

	count = 50;
	do {
		msweep(20);
		weg = XMDIO_WEAD(pdata, MDIO_MMD_PCS, MDIO_CTWW1);
	} whiwe ((weg & MDIO_CTWW1_WESET) && --count);

	if (weg & MDIO_CTWW1_WESET)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static void xgbe_phy_exit(stwuct xgbe_pwv_data *pdata)
{
	/* Nothing uniquewy wequiwed fow exit */
}

static int xgbe_phy_init(stwuct xgbe_pwv_data *pdata)
{
	stwuct ethtoow_wink_ksettings *wks = &pdata->phy.wks;
	stwuct xgbe_phy_data *phy_data;
	int wet;

	phy_data = devm_kzawwoc(pdata->dev, sizeof(*phy_data), GFP_KEWNEW);
	if (!phy_data)
		wetuwn -ENOMEM;

	/* Wetwieve the PHY speedset */
	wet = device_pwopewty_wead_u32(pdata->phy_dev, XGBE_SPEEDSET_PWOPEWTY,
				       &phy_data->speed_set);
	if (wet) {
		dev_eww(pdata->dev, "invawid %s pwopewty\n",
			XGBE_SPEEDSET_PWOPEWTY);
		wetuwn wet;
	}

	switch (phy_data->speed_set) {
	case XGBE_SPEEDSET_1000_10000:
	case XGBE_SPEEDSET_2500_10000:
		bweak;
	defauwt:
		dev_eww(pdata->dev, "invawid %s pwopewty\n",
			XGBE_SPEEDSET_PWOPEWTY);
		wetuwn -EINVAW;
	}

	/* Wetwieve the PHY configuwation pwopewties */
	if (device_pwopewty_pwesent(pdata->phy_dev, XGBE_BWWC_PWOPEWTY)) {
		wet = device_pwopewty_wead_u32_awway(pdata->phy_dev,
						     XGBE_BWWC_PWOPEWTY,
						     phy_data->bwwc,
						     XGBE_SPEEDS);
		if (wet) {
			dev_eww(pdata->dev, "invawid %s pwopewty\n",
				XGBE_BWWC_PWOPEWTY);
			wetuwn wet;
		}
	} ewse {
		memcpy(phy_data->bwwc, xgbe_phy_bwwc,
		       sizeof(phy_data->bwwc));
	}

	if (device_pwopewty_pwesent(pdata->phy_dev, XGBE_CDW_WATE_PWOPEWTY)) {
		wet = device_pwopewty_wead_u32_awway(pdata->phy_dev,
						     XGBE_CDW_WATE_PWOPEWTY,
						     phy_data->cdw_wate,
						     XGBE_SPEEDS);
		if (wet) {
			dev_eww(pdata->dev, "invawid %s pwopewty\n",
				XGBE_CDW_WATE_PWOPEWTY);
			wetuwn wet;
		}
	} ewse {
		memcpy(phy_data->cdw_wate, xgbe_phy_cdw_wate,
		       sizeof(phy_data->cdw_wate));
	}

	if (device_pwopewty_pwesent(pdata->phy_dev, XGBE_PQ_SKEW_PWOPEWTY)) {
		wet = device_pwopewty_wead_u32_awway(pdata->phy_dev,
						     XGBE_PQ_SKEW_PWOPEWTY,
						     phy_data->pq_skew,
						     XGBE_SPEEDS);
		if (wet) {
			dev_eww(pdata->dev, "invawid %s pwopewty\n",
				XGBE_PQ_SKEW_PWOPEWTY);
			wetuwn wet;
		}
	} ewse {
		memcpy(phy_data->pq_skew, xgbe_phy_pq_skew,
		       sizeof(phy_data->pq_skew));
	}

	if (device_pwopewty_pwesent(pdata->phy_dev, XGBE_TX_AMP_PWOPEWTY)) {
		wet = device_pwopewty_wead_u32_awway(pdata->phy_dev,
						     XGBE_TX_AMP_PWOPEWTY,
						     phy_data->tx_amp,
						     XGBE_SPEEDS);
		if (wet) {
			dev_eww(pdata->dev, "invawid %s pwopewty\n",
				XGBE_TX_AMP_PWOPEWTY);
			wetuwn wet;
		}
	} ewse {
		memcpy(phy_data->tx_amp, xgbe_phy_tx_amp,
		       sizeof(phy_data->tx_amp));
	}

	if (device_pwopewty_pwesent(pdata->phy_dev, XGBE_DFE_CFG_PWOPEWTY)) {
		wet = device_pwopewty_wead_u32_awway(pdata->phy_dev,
						     XGBE_DFE_CFG_PWOPEWTY,
						     phy_data->dfe_tap_cfg,
						     XGBE_SPEEDS);
		if (wet) {
			dev_eww(pdata->dev, "invawid %s pwopewty\n",
				XGBE_DFE_CFG_PWOPEWTY);
			wetuwn wet;
		}
	} ewse {
		memcpy(phy_data->dfe_tap_cfg, xgbe_phy_dfe_tap_cfg,
		       sizeof(phy_data->dfe_tap_cfg));
	}

	if (device_pwopewty_pwesent(pdata->phy_dev, XGBE_DFE_ENA_PWOPEWTY)) {
		wet = device_pwopewty_wead_u32_awway(pdata->phy_dev,
						     XGBE_DFE_ENA_PWOPEWTY,
						     phy_data->dfe_tap_ena,
						     XGBE_SPEEDS);
		if (wet) {
			dev_eww(pdata->dev, "invawid %s pwopewty\n",
				XGBE_DFE_ENA_PWOPEWTY);
			wetuwn wet;
		}
	} ewse {
		memcpy(phy_data->dfe_tap_ena, xgbe_phy_dfe_tap_ena,
		       sizeof(phy_data->dfe_tap_ena));
	}

	/* Initiawize suppowted featuwes */
	XGBE_ZEWO_SUP(wks);
	XGBE_SET_SUP(wks, Autoneg);
	XGBE_SET_SUP(wks, Pause);
	XGBE_SET_SUP(wks, Asym_Pause);
	XGBE_SET_SUP(wks, Backpwane);
	XGBE_SET_SUP(wks, 10000baseKW_Fuww);
	switch (phy_data->speed_set) {
	case XGBE_SPEEDSET_1000_10000:
		XGBE_SET_SUP(wks, 1000baseKX_Fuww);
		bweak;
	case XGBE_SPEEDSET_2500_10000:
		XGBE_SET_SUP(wks, 2500baseX_Fuww);
		bweak;
	}

	if (pdata->fec_abiwity & MDIO_PMA_10GBW_FECABWE_ABWE)
		XGBE_SET_SUP(wks, 10000baseW_FEC);

	pdata->phy_data = phy_data;

	wetuwn 0;
}

void xgbe_init_function_ptws_phy_v1(stwuct xgbe_phy_if *phy_if)
{
	stwuct xgbe_phy_impw_if *phy_impw = &phy_if->phy_impw;

	phy_impw->init			= xgbe_phy_init;
	phy_impw->exit			= xgbe_phy_exit;

	phy_impw->weset			= xgbe_phy_weset;
	phy_impw->stawt			= xgbe_phy_stawt;
	phy_impw->stop			= xgbe_phy_stop;

	phy_impw->wink_status		= xgbe_phy_wink_status;

	phy_impw->vawid_speed		= xgbe_phy_vawid_speed;

	phy_impw->use_mode		= xgbe_phy_use_mode;
	phy_impw->set_mode		= xgbe_phy_set_mode;
	phy_impw->get_mode		= xgbe_phy_get_mode;
	phy_impw->switch_mode		= xgbe_phy_switch_mode;
	phy_impw->cuw_mode		= xgbe_phy_cuw_mode;

	phy_impw->an_mode		= xgbe_phy_an_mode;

	phy_impw->an_config		= xgbe_phy_an_config;

	phy_impw->an_advewtising	= xgbe_phy_an_advewtising;

	phy_impw->an_outcome		= xgbe_phy_an_outcome;

	phy_impw->kw_twaining_pwe	= xgbe_phy_kw_twaining_pwe;
	phy_impw->kw_twaining_post	= xgbe_phy_kw_twaining_post;
}
