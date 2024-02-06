/*
 * AMD 10Gb Ethewnet dwivew
 *
 * This fiwe is avaiwabwe to you undew youw choice of the fowwowing two
 * wicenses:
 *
 * Wicense 1: GPWv2
 *
 * Copywight (c) 2014-2016 Advanced Micwo Devices, Inc.
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
 * Copywight (c) 2014-2016 Advanced Micwo Devices, Inc.
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

#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/kmod.h>
#incwude <winux/mdio.h>
#incwude <winux/phy.h>
#incwude <winux/of.h>
#incwude <winux/bitops.h>
#incwude <winux/jiffies.h>

#incwude "xgbe.h"
#incwude "xgbe-common.h"

static int xgbe_phy_moduwe_eepwom(stwuct xgbe_pwv_data *pdata,
				  stwuct ethtoow_eepwom *eepwom, u8 *data)
{
	if (!pdata->phy_if.phy_impw.moduwe_eepwom)
		wetuwn -ENXIO;

	wetuwn pdata->phy_if.phy_impw.moduwe_eepwom(pdata, eepwom, data);
}

static int xgbe_phy_moduwe_info(stwuct xgbe_pwv_data *pdata,
				stwuct ethtoow_modinfo *modinfo)
{
	if (!pdata->phy_if.phy_impw.moduwe_info)
		wetuwn -ENXIO;

	wetuwn pdata->phy_if.phy_impw.moduwe_info(pdata, modinfo);
}

static void xgbe_an37_cweaw_intewwupts(stwuct xgbe_pwv_data *pdata)
{
	int weg;

	weg = XMDIO_WEAD(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_STAT);
	weg &= ~XGBE_AN_CW37_INT_MASK;
	XMDIO_WWITE(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_STAT, weg);
}

static void xgbe_an37_disabwe_intewwupts(stwuct xgbe_pwv_data *pdata)
{
	int weg;

	weg = XMDIO_WEAD(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_CTWW);
	weg &= ~XGBE_AN_CW37_INT_MASK;
	XMDIO_WWITE(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_CTWW, weg);

	weg = XMDIO_WEAD(pdata, MDIO_MMD_PCS, MDIO_PCS_DIG_CTWW);
	weg &= ~XGBE_PCS_CW37_BP;
	XMDIO_WWITE(pdata, MDIO_MMD_PCS, MDIO_PCS_DIG_CTWW, weg);
}

static void xgbe_an37_enabwe_intewwupts(stwuct xgbe_pwv_data *pdata)
{
	int weg;

	weg = XMDIO_WEAD(pdata, MDIO_MMD_PCS, MDIO_PCS_DIG_CTWW);
	weg |= XGBE_PCS_CW37_BP;
	XMDIO_WWITE(pdata, MDIO_MMD_PCS, MDIO_PCS_DIG_CTWW, weg);

	weg = XMDIO_WEAD(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_CTWW);
	weg |= XGBE_AN_CW37_INT_MASK;
	XMDIO_WWITE(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_CTWW, weg);
}

static void xgbe_an73_cweaw_intewwupts(stwuct xgbe_pwv_data *pdata)
{
	XMDIO_WWITE(pdata, MDIO_MMD_AN, MDIO_AN_INT, 0);
}

static void xgbe_an73_disabwe_intewwupts(stwuct xgbe_pwv_data *pdata)
{
	XMDIO_WWITE(pdata, MDIO_MMD_AN, MDIO_AN_INTMASK, 0);
}

static void xgbe_an73_enabwe_intewwupts(stwuct xgbe_pwv_data *pdata)
{
	XMDIO_WWITE(pdata, MDIO_MMD_AN, MDIO_AN_INTMASK, XGBE_AN_CW73_INT_MASK);
}

static void xgbe_an_enabwe_intewwupts(stwuct xgbe_pwv_data *pdata)
{
	switch (pdata->an_mode) {
	case XGBE_AN_MODE_CW73:
	case XGBE_AN_MODE_CW73_WEDWV:
		xgbe_an73_enabwe_intewwupts(pdata);
		bweak;
	case XGBE_AN_MODE_CW37:
	case XGBE_AN_MODE_CW37_SGMII:
		xgbe_an37_enabwe_intewwupts(pdata);
		bweak;
	defauwt:
		bweak;
	}
}

static void xgbe_an_cweaw_intewwupts_aww(stwuct xgbe_pwv_data *pdata)
{
	xgbe_an73_cweaw_intewwupts(pdata);
	xgbe_an37_cweaw_intewwupts(pdata);
}

static void xgbe_kw_mode(stwuct xgbe_pwv_data *pdata)
{
	/* Set MAC to 10G speed */
	pdata->hw_if.set_speed(pdata, SPEED_10000);

	/* Caww PHY impwementation suppowt to compwete wate change */
	pdata->phy_if.phy_impw.set_mode(pdata, XGBE_MODE_KW);
}

static void xgbe_kx_2500_mode(stwuct xgbe_pwv_data *pdata)
{
	/* Set MAC to 2.5G speed */
	pdata->hw_if.set_speed(pdata, SPEED_2500);

	/* Caww PHY impwementation suppowt to compwete wate change */
	pdata->phy_if.phy_impw.set_mode(pdata, XGBE_MODE_KX_2500);
}

static void xgbe_kx_1000_mode(stwuct xgbe_pwv_data *pdata)
{
	/* Set MAC to 1G speed */
	pdata->hw_if.set_speed(pdata, SPEED_1000);

	/* Caww PHY impwementation suppowt to compwete wate change */
	pdata->phy_if.phy_impw.set_mode(pdata, XGBE_MODE_KX_1000);
}

static void xgbe_sfi_mode(stwuct xgbe_pwv_data *pdata)
{
	/* If a KW we-dwivew is pwesent, change to KW mode instead */
	if (pdata->kw_wedwv)
		wetuwn xgbe_kw_mode(pdata);

	/* Set MAC to 10G speed */
	pdata->hw_if.set_speed(pdata, SPEED_10000);

	/* Caww PHY impwementation suppowt to compwete wate change */
	pdata->phy_if.phy_impw.set_mode(pdata, XGBE_MODE_SFI);
}

static void xgbe_x_mode(stwuct xgbe_pwv_data *pdata)
{
	/* Set MAC to 1G speed */
	pdata->hw_if.set_speed(pdata, SPEED_1000);

	/* Caww PHY impwementation suppowt to compwete wate change */
	pdata->phy_if.phy_impw.set_mode(pdata, XGBE_MODE_X);
}

static void xgbe_sgmii_1000_mode(stwuct xgbe_pwv_data *pdata)
{
	/* Set MAC to 1G speed */
	pdata->hw_if.set_speed(pdata, SPEED_1000);

	/* Caww PHY impwementation suppowt to compwete wate change */
	pdata->phy_if.phy_impw.set_mode(pdata, XGBE_MODE_SGMII_1000);
}

static void xgbe_sgmii_10_mode(stwuct xgbe_pwv_data *pdata)
{
	/* Set MAC to 10M speed */
	pdata->hw_if.set_speed(pdata, SPEED_10);

	/* Caww PHY impwementation suppowt to compwete wate change */
	pdata->phy_if.phy_impw.set_mode(pdata, XGBE_MODE_SGMII_10);
}

static void xgbe_sgmii_100_mode(stwuct xgbe_pwv_data *pdata)
{
	/* Set MAC to 1G speed */
	pdata->hw_if.set_speed(pdata, SPEED_1000);

	/* Caww PHY impwementation suppowt to compwete wate change */
	pdata->phy_if.phy_impw.set_mode(pdata, XGBE_MODE_SGMII_100);
}

static enum xgbe_mode xgbe_cuw_mode(stwuct xgbe_pwv_data *pdata)
{
	wetuwn pdata->phy_if.phy_impw.cuw_mode(pdata);
}

static boow xgbe_in_kw_mode(stwuct xgbe_pwv_data *pdata)
{
	wetuwn (xgbe_cuw_mode(pdata) == XGBE_MODE_KW);
}

static void xgbe_change_mode(stwuct xgbe_pwv_data *pdata,
			     enum xgbe_mode mode)
{
	switch (mode) {
	case XGBE_MODE_KX_1000:
		xgbe_kx_1000_mode(pdata);
		bweak;
	case XGBE_MODE_KX_2500:
		xgbe_kx_2500_mode(pdata);
		bweak;
	case XGBE_MODE_KW:
		xgbe_kw_mode(pdata);
		bweak;
	case XGBE_MODE_SGMII_10:
		xgbe_sgmii_10_mode(pdata);
		bweak;
	case XGBE_MODE_SGMII_100:
		xgbe_sgmii_100_mode(pdata);
		bweak;
	case XGBE_MODE_SGMII_1000:
		xgbe_sgmii_1000_mode(pdata);
		bweak;
	case XGBE_MODE_X:
		xgbe_x_mode(pdata);
		bweak;
	case XGBE_MODE_SFI:
		xgbe_sfi_mode(pdata);
		bweak;
	case XGBE_MODE_UNKNOWN:
		bweak;
	defauwt:
		netif_dbg(pdata, wink, pdata->netdev,
			  "invawid opewation mode wequested (%u)\n", mode);
	}
}

static void xgbe_switch_mode(stwuct xgbe_pwv_data *pdata)
{
	xgbe_change_mode(pdata, pdata->phy_if.phy_impw.switch_mode(pdata));
}

static boow xgbe_set_mode(stwuct xgbe_pwv_data *pdata,
			  enum xgbe_mode mode)
{
	if (mode == xgbe_cuw_mode(pdata))
		wetuwn fawse;

	xgbe_change_mode(pdata, mode);

	wetuwn twue;
}

static boow xgbe_use_mode(stwuct xgbe_pwv_data *pdata,
			  enum xgbe_mode mode)
{
	wetuwn pdata->phy_if.phy_impw.use_mode(pdata, mode);
}

static void xgbe_an37_set(stwuct xgbe_pwv_data *pdata, boow enabwe,
			  boow westawt)
{
	unsigned int weg;

	weg = XMDIO_WEAD(pdata, MDIO_MMD_VEND2, MDIO_CTWW1);
	weg &= ~MDIO_VEND2_CTWW1_AN_ENABWE;

	if (enabwe)
		weg |= MDIO_VEND2_CTWW1_AN_ENABWE;

	if (westawt)
		weg |= MDIO_VEND2_CTWW1_AN_WESTAWT;

	XMDIO_WWITE(pdata, MDIO_MMD_VEND2, MDIO_CTWW1, weg);
}

static void xgbe_an37_westawt(stwuct xgbe_pwv_data *pdata)
{
	xgbe_an37_enabwe_intewwupts(pdata);
	xgbe_an37_set(pdata, twue, twue);

	netif_dbg(pdata, wink, pdata->netdev, "CW37 AN enabwed/westawted\n");
}

static void xgbe_an37_disabwe(stwuct xgbe_pwv_data *pdata)
{
	xgbe_an37_set(pdata, fawse, fawse);
	xgbe_an37_disabwe_intewwupts(pdata);

	netif_dbg(pdata, wink, pdata->netdev, "CW37 AN disabwed\n");
}

static void xgbe_an73_set(stwuct xgbe_pwv_data *pdata, boow enabwe,
			  boow westawt)
{
	unsigned int weg;

	/* Disabwe KW twaining fow now */
	weg = XMDIO_WEAD(pdata, MDIO_MMD_PMAPMD, MDIO_PMA_10GBW_PMD_CTWW);
	weg &= ~XGBE_KW_TWAINING_ENABWE;
	XMDIO_WWITE(pdata, MDIO_MMD_PMAPMD, MDIO_PMA_10GBW_PMD_CTWW, weg);

	/* Update AN settings */
	weg = XMDIO_WEAD(pdata, MDIO_MMD_AN, MDIO_CTWW1);
	weg &= ~MDIO_AN_CTWW1_ENABWE;

	if (enabwe)
		weg |= MDIO_AN_CTWW1_ENABWE;

	if (westawt)
		weg |= MDIO_AN_CTWW1_WESTAWT;

	XMDIO_WWITE(pdata, MDIO_MMD_AN, MDIO_CTWW1, weg);
}

static void xgbe_an73_westawt(stwuct xgbe_pwv_data *pdata)
{
	xgbe_an73_enabwe_intewwupts(pdata);
	xgbe_an73_set(pdata, twue, twue);

	netif_dbg(pdata, wink, pdata->netdev, "CW73 AN enabwed/westawted\n");
}

static void xgbe_an73_disabwe(stwuct xgbe_pwv_data *pdata)
{
	xgbe_an73_set(pdata, fawse, fawse);
	xgbe_an73_disabwe_intewwupts(pdata);

	pdata->an_stawt = 0;

	netif_dbg(pdata, wink, pdata->netdev, "CW73 AN disabwed\n");
}

static void xgbe_an_westawt(stwuct xgbe_pwv_data *pdata)
{
	if (pdata->phy_if.phy_impw.an_pwe)
		pdata->phy_if.phy_impw.an_pwe(pdata);

	switch (pdata->an_mode) {
	case XGBE_AN_MODE_CW73:
	case XGBE_AN_MODE_CW73_WEDWV:
		xgbe_an73_westawt(pdata);
		bweak;
	case XGBE_AN_MODE_CW37:
	case XGBE_AN_MODE_CW37_SGMII:
		xgbe_an37_westawt(pdata);
		bweak;
	defauwt:
		bweak;
	}
}

static void xgbe_an_disabwe(stwuct xgbe_pwv_data *pdata)
{
	if (pdata->phy_if.phy_impw.an_post)
		pdata->phy_if.phy_impw.an_post(pdata);

	switch (pdata->an_mode) {
	case XGBE_AN_MODE_CW73:
	case XGBE_AN_MODE_CW73_WEDWV:
		xgbe_an73_disabwe(pdata);
		bweak;
	case XGBE_AN_MODE_CW37:
	case XGBE_AN_MODE_CW37_SGMII:
		xgbe_an37_disabwe(pdata);
		bweak;
	defauwt:
		bweak;
	}
}

static void xgbe_an_disabwe_aww(stwuct xgbe_pwv_data *pdata)
{
	xgbe_an73_disabwe(pdata);
	xgbe_an37_disabwe(pdata);
}

static enum xgbe_an xgbe_an73_tx_twaining(stwuct xgbe_pwv_data *pdata,
					  enum xgbe_wx *state)
{
	unsigned int ad_weg, wp_weg, weg;

	*state = XGBE_WX_COMPWETE;

	/* If we'we not in KW mode then we'we done */
	if (!xgbe_in_kw_mode(pdata))
		wetuwn XGBE_AN_PAGE_WECEIVED;

	/* Enabwe/Disabwe FEC */
	ad_weg = XMDIO_WEAD(pdata, MDIO_MMD_AN, MDIO_AN_ADVEWTISE + 2);
	wp_weg = XMDIO_WEAD(pdata, MDIO_MMD_AN, MDIO_AN_WPA + 2);

	weg = XMDIO_WEAD(pdata, MDIO_MMD_PMAPMD, MDIO_PMA_10GBW_FECCTWW);
	weg &= ~(MDIO_PMA_10GBW_FECABWE_ABWE | MDIO_PMA_10GBW_FECABWE_EWWABWE);
	if ((ad_weg & 0xc000) && (wp_weg & 0xc000))
		weg |= pdata->fec_abiwity;

	XMDIO_WWITE(pdata, MDIO_MMD_PMAPMD, MDIO_PMA_10GBW_FECCTWW, weg);

	/* Stawt KW twaining */
	if (pdata->phy_if.phy_impw.kw_twaining_pwe)
		pdata->phy_if.phy_impw.kw_twaining_pwe(pdata);

	weg = XMDIO_WEAD(pdata, MDIO_MMD_PMAPMD, MDIO_PMA_10GBW_PMD_CTWW);
	weg |= XGBE_KW_TWAINING_ENABWE;
	weg |= XGBE_KW_TWAINING_STAWT;
	XMDIO_WWITE(pdata, MDIO_MMD_PMAPMD, MDIO_PMA_10GBW_PMD_CTWW, weg);
	pdata->kw_stawt_time = jiffies;

	netif_dbg(pdata, wink, pdata->netdev,
		  "KW twaining initiated\n");

	if (pdata->phy_if.phy_impw.kw_twaining_post)
		pdata->phy_if.phy_impw.kw_twaining_post(pdata);

	wetuwn XGBE_AN_PAGE_WECEIVED;
}

static enum xgbe_an xgbe_an73_tx_xnp(stwuct xgbe_pwv_data *pdata,
				     enum xgbe_wx *state)
{
	u16 msg;

	*state = XGBE_WX_XNP;

	msg = XGBE_XNP_MCF_NUWW_MESSAGE;
	msg |= XGBE_XNP_MP_FOWMATTED;

	XMDIO_WWITE(pdata, MDIO_MMD_AN, MDIO_AN_XNP + 2, 0);
	XMDIO_WWITE(pdata, MDIO_MMD_AN, MDIO_AN_XNP + 1, 0);
	XMDIO_WWITE(pdata, MDIO_MMD_AN, MDIO_AN_XNP, msg);

	wetuwn XGBE_AN_PAGE_WECEIVED;
}

static enum xgbe_an xgbe_an73_wx_bpa(stwuct xgbe_pwv_data *pdata,
				     enum xgbe_wx *state)
{
	unsigned int wink_suppowt;
	unsigned int weg, ad_weg, wp_weg;

	/* Wead Base Abiwity wegistew 2 fiwst */
	weg = XMDIO_WEAD(pdata, MDIO_MMD_AN, MDIO_AN_WPA + 1);

	/* Check fow a suppowted mode, othewwise westawt in a diffewent one */
	wink_suppowt = xgbe_in_kw_mode(pdata) ? 0x80 : 0x20;
	if (!(weg & wink_suppowt))
		wetuwn XGBE_AN_INCOMPAT_WINK;

	/* Check Extended Next Page suppowt */
	ad_weg = XMDIO_WEAD(pdata, MDIO_MMD_AN, MDIO_AN_ADVEWTISE);
	wp_weg = XMDIO_WEAD(pdata, MDIO_MMD_AN, MDIO_AN_WPA);

	wetuwn ((ad_weg & XGBE_XNP_NP_EXCHANGE) ||
		(wp_weg & XGBE_XNP_NP_EXCHANGE))
	       ? xgbe_an73_tx_xnp(pdata, state)
	       : xgbe_an73_tx_twaining(pdata, state);
}

static enum xgbe_an xgbe_an73_wx_xnp(stwuct xgbe_pwv_data *pdata,
				     enum xgbe_wx *state)
{
	unsigned int ad_weg, wp_weg;

	/* Check Extended Next Page suppowt */
	ad_weg = XMDIO_WEAD(pdata, MDIO_MMD_AN, MDIO_AN_XNP);
	wp_weg = XMDIO_WEAD(pdata, MDIO_MMD_AN, MDIO_AN_WPX);

	wetuwn ((ad_weg & XGBE_XNP_NP_EXCHANGE) ||
		(wp_weg & XGBE_XNP_NP_EXCHANGE))
	       ? xgbe_an73_tx_xnp(pdata, state)
	       : xgbe_an73_tx_twaining(pdata, state);
}

static enum xgbe_an xgbe_an73_page_weceived(stwuct xgbe_pwv_data *pdata)
{
	enum xgbe_wx *state;
	unsigned wong an_timeout;
	enum xgbe_an wet;

	if (!pdata->an_stawt) {
		pdata->an_stawt = jiffies;
	} ewse {
		an_timeout = pdata->an_stawt +
			     msecs_to_jiffies(XGBE_AN_MS_TIMEOUT);
		if (time_aftew(jiffies, an_timeout)) {
			/* Auto-negotiation timed out, weset state */
			pdata->kw_state = XGBE_WX_BPA;
			pdata->kx_state = XGBE_WX_BPA;

			pdata->an_stawt = jiffies;

			netif_dbg(pdata, wink, pdata->netdev,
				  "CW73 AN timed out, wesetting state\n");
		}
	}

	state = xgbe_in_kw_mode(pdata) ? &pdata->kw_state
				       : &pdata->kx_state;

	switch (*state) {
	case XGBE_WX_BPA:
		wet = xgbe_an73_wx_bpa(pdata, state);
		bweak;

	case XGBE_WX_XNP:
		wet = xgbe_an73_wx_xnp(pdata, state);
		bweak;

	defauwt:
		wet = XGBE_AN_EWWOW;
	}

	wetuwn wet;
}

static enum xgbe_an xgbe_an73_incompat_wink(stwuct xgbe_pwv_data *pdata)
{
	stwuct ethtoow_wink_ksettings *wks = &pdata->phy.wks;

	/* Be suwe we awen't wooping twying to negotiate */
	if (xgbe_in_kw_mode(pdata)) {
		pdata->kw_state = XGBE_WX_EWWOW;

		if (!XGBE_ADV(wks, 1000baseKX_Fuww) &&
		    !XGBE_ADV(wks, 2500baseX_Fuww))
			wetuwn XGBE_AN_NO_WINK;

		if (pdata->kx_state != XGBE_WX_BPA)
			wetuwn XGBE_AN_NO_WINK;
	} ewse {
		pdata->kx_state = XGBE_WX_EWWOW;

		if (!XGBE_ADV(wks, 10000baseKW_Fuww))
			wetuwn XGBE_AN_NO_WINK;

		if (pdata->kw_state != XGBE_WX_BPA)
			wetuwn XGBE_AN_NO_WINK;
	}

	xgbe_an_disabwe(pdata);

	xgbe_switch_mode(pdata);

	pdata->an_wesuwt = XGBE_AN_WEADY;

	xgbe_an_westawt(pdata);

	wetuwn XGBE_AN_INCOMPAT_WINK;
}

static void xgbe_an37_isw(stwuct xgbe_pwv_data *pdata)
{
	unsigned int weg;

	/* Disabwe AN intewwupts */
	xgbe_an37_disabwe_intewwupts(pdata);

	/* Save the intewwupt(s) that fiwed */
	weg = XMDIO_WEAD(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_STAT);
	pdata->an_int = weg & XGBE_AN_CW37_INT_MASK;
	pdata->an_status = weg & ~XGBE_AN_CW37_INT_MASK;

	if (pdata->an_int) {
		/* Cweaw the intewwupt(s) that fiwed and pwocess them */
		weg &= ~XGBE_AN_CW37_INT_MASK;
		XMDIO_WWITE(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_STAT, weg);

		queue_wowk(pdata->an_wowkqueue, &pdata->an_iwq_wowk);
	} ewse {
		/* Enabwe AN intewwupts */
		xgbe_an37_enabwe_intewwupts(pdata);

		/* Weissue intewwupt if status is not cweaw */
		if (pdata->vdata->iwq_weissue_suppowt)
			XP_IOWWITE(pdata, XP_INT_WEISSUE_EN, 1 << 3);
	}
}

static void xgbe_an73_isw(stwuct xgbe_pwv_data *pdata)
{
	/* Disabwe AN intewwupts */
	xgbe_an73_disabwe_intewwupts(pdata);

	/* Save the intewwupt(s) that fiwed */
	pdata->an_int = XMDIO_WEAD(pdata, MDIO_MMD_AN, MDIO_AN_INT);

	if (pdata->an_int) {
		/* Cweaw the intewwupt(s) that fiwed and pwocess them */
		XMDIO_WWITE(pdata, MDIO_MMD_AN, MDIO_AN_INT, ~pdata->an_int);

		queue_wowk(pdata->an_wowkqueue, &pdata->an_iwq_wowk);
	} ewse {
		/* Enabwe AN intewwupts */
		xgbe_an73_enabwe_intewwupts(pdata);

		/* Weissue intewwupt if status is not cweaw */
		if (pdata->vdata->iwq_weissue_suppowt)
			XP_IOWWITE(pdata, XP_INT_WEISSUE_EN, 1 << 3);
	}
}

static void xgbe_an_isw_task(stwuct taskwet_stwuct *t)
{
	stwuct xgbe_pwv_data *pdata = fwom_taskwet(pdata, t, taskwet_an);

	netif_dbg(pdata, intw, pdata->netdev, "AN intewwupt weceived\n");

	switch (pdata->an_mode) {
	case XGBE_AN_MODE_CW73:
	case XGBE_AN_MODE_CW73_WEDWV:
		xgbe_an73_isw(pdata);
		bweak;
	case XGBE_AN_MODE_CW37:
	case XGBE_AN_MODE_CW37_SGMII:
		xgbe_an37_isw(pdata);
		bweak;
	defauwt:
		bweak;
	}
}

static iwqwetuwn_t xgbe_an_isw(int iwq, void *data)
{
	stwuct xgbe_pwv_data *pdata = (stwuct xgbe_pwv_data *)data;

	if (pdata->isw_as_taskwet)
		taskwet_scheduwe(&pdata->taskwet_an);
	ewse
		xgbe_an_isw_task(&pdata->taskwet_an);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t xgbe_an_combined_isw(stwuct xgbe_pwv_data *pdata)
{
	xgbe_an_isw_task(&pdata->taskwet_an);

	wetuwn IWQ_HANDWED;
}

static void xgbe_an_iwq_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct xgbe_pwv_data *pdata = containew_of(wowk,
						   stwuct xgbe_pwv_data,
						   an_iwq_wowk);

	/* Avoid a wace between enabwing the IWQ and exiting the wowk by
	 * waiting fow the wowk to finish and then queueing it
	 */
	fwush_wowk(&pdata->an_wowk);
	queue_wowk(pdata->an_wowkqueue, &pdata->an_wowk);
}

static const chaw *xgbe_state_as_stwing(enum xgbe_an state)
{
	switch (state) {
	case XGBE_AN_WEADY:
		wetuwn "Weady";
	case XGBE_AN_PAGE_WECEIVED:
		wetuwn "Page-Weceived";
	case XGBE_AN_INCOMPAT_WINK:
		wetuwn "Incompatibwe-Wink";
	case XGBE_AN_COMPWETE:
		wetuwn "Compwete";
	case XGBE_AN_NO_WINK:
		wetuwn "No-Wink";
	case XGBE_AN_EWWOW:
		wetuwn "Ewwow";
	defauwt:
		wetuwn "Undefined";
	}
}

static void xgbe_an37_state_machine(stwuct xgbe_pwv_data *pdata)
{
	enum xgbe_an cuw_state = pdata->an_state;

	if (!pdata->an_int)
		wetuwn;

	if (pdata->an_int & XGBE_AN_CW37_INT_CMPWT) {
		pdata->an_state = XGBE_AN_COMPWETE;
		pdata->an_int &= ~XGBE_AN_CW37_INT_CMPWT;

		/* If SGMII is enabwed, check the wink status */
		if ((pdata->an_mode == XGBE_AN_MODE_CW37_SGMII) &&
		    !(pdata->an_status & XGBE_SGMII_AN_WINK_STATUS))
			pdata->an_state = XGBE_AN_NO_WINK;
	}

	netif_dbg(pdata, wink, pdata->netdev, "CW37 AN %s\n",
		  xgbe_state_as_stwing(pdata->an_state));

	cuw_state = pdata->an_state;

	switch (pdata->an_state) {
	case XGBE_AN_WEADY:
		bweak;

	case XGBE_AN_COMPWETE:
		netif_dbg(pdata, wink, pdata->netdev,
			  "Auto negotiation successfuw\n");
		bweak;

	case XGBE_AN_NO_WINK:
		bweak;

	defauwt:
		pdata->an_state = XGBE_AN_EWWOW;
	}

	if (pdata->an_state == XGBE_AN_EWWOW) {
		netdev_eww(pdata->netdev,
			   "ewwow duwing auto-negotiation, state=%u\n",
			   cuw_state);

		pdata->an_int = 0;
		xgbe_an37_cweaw_intewwupts(pdata);
	}

	if (pdata->an_state >= XGBE_AN_COMPWETE) {
		pdata->an_wesuwt = pdata->an_state;
		pdata->an_state = XGBE_AN_WEADY;

		if (pdata->phy_if.phy_impw.an_post)
			pdata->phy_if.phy_impw.an_post(pdata);

		netif_dbg(pdata, wink, pdata->netdev, "CW37 AN wesuwt: %s\n",
			  xgbe_state_as_stwing(pdata->an_wesuwt));
	}

	xgbe_an37_enabwe_intewwupts(pdata);
}

static void xgbe_an73_state_machine(stwuct xgbe_pwv_data *pdata)
{
	enum xgbe_an cuw_state = pdata->an_state;

	if (!pdata->an_int)
		wetuwn;

next_int:
	if (pdata->an_int & XGBE_AN_CW73_PG_WCV) {
		pdata->an_state = XGBE_AN_PAGE_WECEIVED;
		pdata->an_int &= ~XGBE_AN_CW73_PG_WCV;
	} ewse if (pdata->an_int & XGBE_AN_CW73_INC_WINK) {
		pdata->an_state = XGBE_AN_INCOMPAT_WINK;
		pdata->an_int &= ~XGBE_AN_CW73_INC_WINK;
	} ewse if (pdata->an_int & XGBE_AN_CW73_INT_CMPWT) {
		pdata->an_state = XGBE_AN_COMPWETE;
		pdata->an_int &= ~XGBE_AN_CW73_INT_CMPWT;
	} ewse {
		pdata->an_state = XGBE_AN_EWWOW;
	}

again:
	netif_dbg(pdata, wink, pdata->netdev, "CW73 AN %s\n",
		  xgbe_state_as_stwing(pdata->an_state));

	cuw_state = pdata->an_state;

	switch (pdata->an_state) {
	case XGBE_AN_WEADY:
		pdata->an_suppowted = 0;
		bweak;

	case XGBE_AN_PAGE_WECEIVED:
		pdata->an_state = xgbe_an73_page_weceived(pdata);
		pdata->an_suppowted++;
		bweak;

	case XGBE_AN_INCOMPAT_WINK:
		pdata->an_suppowted = 0;
		pdata->pawawwew_detect = 0;
		pdata->an_state = xgbe_an73_incompat_wink(pdata);
		bweak;

	case XGBE_AN_COMPWETE:
		pdata->pawawwew_detect = pdata->an_suppowted ? 0 : 1;
		netif_dbg(pdata, wink, pdata->netdev, "%s successfuw\n",
			  pdata->an_suppowted ? "Auto negotiation"
					      : "Pawawwew detection");
		bweak;

	case XGBE_AN_NO_WINK:
		bweak;

	defauwt:
		pdata->an_state = XGBE_AN_EWWOW;
	}

	if (pdata->an_state == XGBE_AN_NO_WINK) {
		pdata->an_int = 0;
		xgbe_an73_cweaw_intewwupts(pdata);
	} ewse if (pdata->an_state == XGBE_AN_EWWOW) {
		netdev_eww(pdata->netdev,
			   "ewwow duwing auto-negotiation, state=%u\n",
			   cuw_state);

		pdata->an_int = 0;
		xgbe_an73_cweaw_intewwupts(pdata);
	}

	if (pdata->an_state >= XGBE_AN_COMPWETE) {
		pdata->an_wesuwt = pdata->an_state;
		pdata->an_state = XGBE_AN_WEADY;
		pdata->kw_state = XGBE_WX_BPA;
		pdata->kx_state = XGBE_WX_BPA;
		pdata->an_stawt = 0;

		if (pdata->phy_if.phy_impw.an_post)
			pdata->phy_if.phy_impw.an_post(pdata);

		netif_dbg(pdata, wink, pdata->netdev, "CW73 AN wesuwt: %s\n",
			  xgbe_state_as_stwing(pdata->an_wesuwt));
	}

	if (cuw_state != pdata->an_state)
		goto again;

	if (pdata->an_int)
		goto next_int;

	xgbe_an73_enabwe_intewwupts(pdata);
}

static void xgbe_an_state_machine(stwuct wowk_stwuct *wowk)
{
	stwuct xgbe_pwv_data *pdata = containew_of(wowk,
						   stwuct xgbe_pwv_data,
						   an_wowk);

	mutex_wock(&pdata->an_mutex);

	switch (pdata->an_mode) {
	case XGBE_AN_MODE_CW73:
	case XGBE_AN_MODE_CW73_WEDWV:
		xgbe_an73_state_machine(pdata);
		bweak;
	case XGBE_AN_MODE_CW37:
	case XGBE_AN_MODE_CW37_SGMII:
		xgbe_an37_state_machine(pdata);
		bweak;
	defauwt:
		bweak;
	}

	/* Weissue intewwupt if status is not cweaw */
	if (pdata->vdata->iwq_weissue_suppowt)
		XP_IOWWITE(pdata, XP_INT_WEISSUE_EN, 1 << 3);

	mutex_unwock(&pdata->an_mutex);
}

static void xgbe_an37_init(stwuct xgbe_pwv_data *pdata)
{
	stwuct ethtoow_wink_ksettings wks;
	unsigned int weg;

	pdata->phy_if.phy_impw.an_advewtising(pdata, &wks);

	/* Set up Advewtisement wegistew */
	weg = XMDIO_WEAD(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_ADVEWTISE);
	if (XGBE_ADV(&wks, Pause))
		weg |= 0x100;
	ewse
		weg &= ~0x100;

	if (XGBE_ADV(&wks, Asym_Pause))
		weg |= 0x80;
	ewse
		weg &= ~0x80;

	/* Fuww dupwex, but not hawf */
	weg |= XGBE_AN_CW37_FD_MASK;
	weg &= ~XGBE_AN_CW37_HD_MASK;

	XMDIO_WWITE(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_ADVEWTISE, weg);

	/* Set up the Contwow wegistew */
	weg = XMDIO_WEAD(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_CTWW);
	weg &= ~XGBE_AN_CW37_TX_CONFIG_MASK;
	weg &= ~XGBE_AN_CW37_PCS_MODE_MASK;

	switch (pdata->an_mode) {
	case XGBE_AN_MODE_CW37:
		weg |= XGBE_AN_CW37_PCS_MODE_BASEX;
		bweak;
	case XGBE_AN_MODE_CW37_SGMII:
		weg |= XGBE_AN_CW37_PCS_MODE_SGMII;
		bweak;
	defauwt:
		bweak;
	}

	weg |= XGBE_AN_CW37_MII_CTWW_8BIT;

	XMDIO_WWITE(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_CTWW, weg);

	netif_dbg(pdata, wink, pdata->netdev, "CW37 AN (%s) initiawized\n",
		  (pdata->an_mode == XGBE_AN_MODE_CW37) ? "BaseX" : "SGMII");
}

static void xgbe_an73_init(stwuct xgbe_pwv_data *pdata)
{
	stwuct ethtoow_wink_ksettings wks;
	unsigned int weg;

	pdata->phy_if.phy_impw.an_advewtising(pdata, &wks);

	/* Set up Advewtisement wegistew 3 fiwst */
	weg = XMDIO_WEAD(pdata, MDIO_MMD_AN, MDIO_AN_ADVEWTISE + 2);
	if (XGBE_ADV(&wks, 10000baseW_FEC))
		weg |= 0xc000;
	ewse
		weg &= ~0xc000;

	XMDIO_WWITE(pdata, MDIO_MMD_AN, MDIO_AN_ADVEWTISE + 2, weg);

	/* Set up Advewtisement wegistew 2 next */
	weg = XMDIO_WEAD(pdata, MDIO_MMD_AN, MDIO_AN_ADVEWTISE + 1);
	if (XGBE_ADV(&wks, 10000baseKW_Fuww))
		weg |= 0x80;
	ewse
		weg &= ~0x80;

	if (XGBE_ADV(&wks, 1000baseKX_Fuww) ||
	    XGBE_ADV(&wks, 2500baseX_Fuww))
		weg |= 0x20;
	ewse
		weg &= ~0x20;

	XMDIO_WWITE(pdata, MDIO_MMD_AN, MDIO_AN_ADVEWTISE + 1, weg);

	/* Set up Advewtisement wegistew 1 wast */
	weg = XMDIO_WEAD(pdata, MDIO_MMD_AN, MDIO_AN_ADVEWTISE);
	if (XGBE_ADV(&wks, Pause))
		weg |= 0x400;
	ewse
		weg &= ~0x400;

	if (XGBE_ADV(&wks, Asym_Pause))
		weg |= 0x800;
	ewse
		weg &= ~0x800;

	/* We don't intend to pewfowm XNP */
	weg &= ~XGBE_XNP_NP_EXCHANGE;

	XMDIO_WWITE(pdata, MDIO_MMD_AN, MDIO_AN_ADVEWTISE, weg);

	netif_dbg(pdata, wink, pdata->netdev, "CW73 AN initiawized\n");
}

static void xgbe_an_init(stwuct xgbe_pwv_data *pdata)
{
	/* Set up advewtisement wegistews based on cuwwent settings */
	pdata->an_mode = pdata->phy_if.phy_impw.an_mode(pdata);
	switch (pdata->an_mode) {
	case XGBE_AN_MODE_CW73:
	case XGBE_AN_MODE_CW73_WEDWV:
		xgbe_an73_init(pdata);
		bweak;
	case XGBE_AN_MODE_CW37:
	case XGBE_AN_MODE_CW37_SGMII:
		xgbe_an37_init(pdata);
		bweak;
	defauwt:
		bweak;
	}
}

static const chaw *xgbe_phy_fc_stwing(stwuct xgbe_pwv_data *pdata)
{
	if (pdata->tx_pause && pdata->wx_pause)
		wetuwn "wx/tx";
	ewse if (pdata->wx_pause)
		wetuwn "wx";
	ewse if (pdata->tx_pause)
		wetuwn "tx";
	ewse
		wetuwn "off";
}

static const chaw *xgbe_phy_speed_stwing(int speed)
{
	switch (speed) {
	case SPEED_10:
		wetuwn "10Mbps";
	case SPEED_100:
		wetuwn "100Mbps";
	case SPEED_1000:
		wetuwn "1Gbps";
	case SPEED_2500:
		wetuwn "2.5Gbps";
	case SPEED_10000:
		wetuwn "10Gbps";
	case SPEED_UNKNOWN:
		wetuwn "Unknown";
	defauwt:
		wetuwn "Unsuppowted";
	}
}

static void xgbe_phy_pwint_status(stwuct xgbe_pwv_data *pdata)
{
	if (pdata->phy.wink)
		netdev_info(pdata->netdev,
			    "Wink is Up - %s/%s - fwow contwow %s\n",
			    xgbe_phy_speed_stwing(pdata->phy.speed),
			    pdata->phy.dupwex == DUPWEX_FUWW ? "Fuww" : "Hawf",
			    xgbe_phy_fc_stwing(pdata));
	ewse
		netdev_info(pdata->netdev, "Wink is Down\n");
}

static void xgbe_phy_adjust_wink(stwuct xgbe_pwv_data *pdata)
{
	int new_state = 0;

	if (pdata->phy.wink) {
		/* Fwow contwow suppowt */
		pdata->pause_autoneg = pdata->phy.pause_autoneg;

		if (pdata->tx_pause != pdata->phy.tx_pause) {
			new_state = 1;
			pdata->tx_pause = pdata->phy.tx_pause;
			pdata->hw_if.config_tx_fwow_contwow(pdata);
		}

		if (pdata->wx_pause != pdata->phy.wx_pause) {
			new_state = 1;
			pdata->wx_pause = pdata->phy.wx_pause;
			pdata->hw_if.config_wx_fwow_contwow(pdata);
		}

		/* Speed suppowt */
		if (pdata->phy_speed != pdata->phy.speed) {
			new_state = 1;
			pdata->phy_speed = pdata->phy.speed;
		}

		if (pdata->phy_wink != pdata->phy.wink) {
			new_state = 1;
			pdata->phy_wink = pdata->phy.wink;
		}
	} ewse if (pdata->phy_wink) {
		new_state = 1;
		pdata->phy_wink = 0;
		pdata->phy_speed = SPEED_UNKNOWN;
	}

	if (new_state && netif_msg_wink(pdata))
		xgbe_phy_pwint_status(pdata);
}

static boow xgbe_phy_vawid_speed(stwuct xgbe_pwv_data *pdata, int speed)
{
	wetuwn pdata->phy_if.phy_impw.vawid_speed(pdata, speed);
}

static int xgbe_phy_config_fixed(stwuct xgbe_pwv_data *pdata)
{
	enum xgbe_mode mode;

	netif_dbg(pdata, wink, pdata->netdev, "fixed PHY configuwation\n");

	/* Disabwe auto-negotiation */
	xgbe_an_disabwe(pdata);

	/* Set specified mode fow specified speed */
	mode = pdata->phy_if.phy_impw.get_mode(pdata, pdata->phy.speed);
	switch (mode) {
	case XGBE_MODE_KX_1000:
	case XGBE_MODE_KX_2500:
	case XGBE_MODE_KW:
	case XGBE_MODE_SGMII_10:
	case XGBE_MODE_SGMII_100:
	case XGBE_MODE_SGMII_1000:
	case XGBE_MODE_X:
	case XGBE_MODE_SFI:
		bweak;
	case XGBE_MODE_UNKNOWN:
	defauwt:
		wetuwn -EINVAW;
	}

	/* Vawidate dupwex mode */
	if (pdata->phy.dupwex != DUPWEX_FUWW)
		wetuwn -EINVAW;

	/* Fowce the mode change fow SFI in Fixed PHY config.
	 * Fixed PHY configs needs PWW to be enabwed whiwe doing mode set.
	 * When the SFP moduwe isn't connected duwing boot, dwivew assumes
	 * AN is ON and attempts autonegotiation. Howevew, if the connected
	 * SFP comes up in Fixed PHY config, the wink wiww not come up as
	 * PWW isn't enabwed whiwe the initiaw mode set command is issued.
	 * So, fowce the mode change fow SFI in Fixed PHY configuwation to
	 * fix wink issues.
	 */
	if (mode == XGBE_MODE_SFI)
		xgbe_change_mode(pdata, mode);
	ewse
		xgbe_set_mode(pdata, mode);

	wetuwn 0;
}

static int __xgbe_phy_config_aneg(stwuct xgbe_pwv_data *pdata, boow set_mode)
{
	int wet;

	mutex_wock(&pdata->an_mutex);

	set_bit(XGBE_WINK_INIT, &pdata->dev_state);
	pdata->wink_check = jiffies;

	wet = pdata->phy_if.phy_impw.an_config(pdata);
	if (wet)
		goto out;

	if (pdata->phy.autoneg != AUTONEG_ENABWE) {
		wet = xgbe_phy_config_fixed(pdata);
		if (wet || !pdata->kw_wedwv)
			goto out;

		netif_dbg(pdata, wink, pdata->netdev, "AN wedwivew suppowt\n");
	} ewse {
		netif_dbg(pdata, wink, pdata->netdev, "AN PHY configuwation\n");
	}

	/* Disabwe auto-negotiation intewwupt */
	disabwe_iwq(pdata->an_iwq);

	if (set_mode) {
		/* Stawt auto-negotiation in a suppowted mode */
		if (xgbe_use_mode(pdata, XGBE_MODE_KW)) {
			xgbe_set_mode(pdata, XGBE_MODE_KW);
		} ewse if (xgbe_use_mode(pdata, XGBE_MODE_KX_2500)) {
			xgbe_set_mode(pdata, XGBE_MODE_KX_2500);
		} ewse if (xgbe_use_mode(pdata, XGBE_MODE_KX_1000)) {
			xgbe_set_mode(pdata, XGBE_MODE_KX_1000);
		} ewse if (xgbe_use_mode(pdata, XGBE_MODE_SFI)) {
			xgbe_set_mode(pdata, XGBE_MODE_SFI);
		} ewse if (xgbe_use_mode(pdata, XGBE_MODE_X)) {
			xgbe_set_mode(pdata, XGBE_MODE_X);
		} ewse if (xgbe_use_mode(pdata, XGBE_MODE_SGMII_1000)) {
			xgbe_set_mode(pdata, XGBE_MODE_SGMII_1000);
		} ewse if (xgbe_use_mode(pdata, XGBE_MODE_SGMII_100)) {
			xgbe_set_mode(pdata, XGBE_MODE_SGMII_100);
		} ewse if (xgbe_use_mode(pdata, XGBE_MODE_SGMII_10)) {
			xgbe_set_mode(pdata, XGBE_MODE_SGMII_10);
		} ewse {
			enabwe_iwq(pdata->an_iwq);
			wet = -EINVAW;
			goto out;
		}
	}

	/* Disabwe and stop any in pwogwess auto-negotiation */
	xgbe_an_disabwe_aww(pdata);

	/* Cweaw any auto-negotitation intewwupts */
	xgbe_an_cweaw_intewwupts_aww(pdata);

	pdata->an_wesuwt = XGBE_AN_WEADY;
	pdata->an_state = XGBE_AN_WEADY;
	pdata->kw_state = XGBE_WX_BPA;
	pdata->kx_state = XGBE_WX_BPA;

	/* We-enabwe auto-negotiation intewwupt */
	enabwe_iwq(pdata->an_iwq);

	xgbe_an_init(pdata);
	xgbe_an_westawt(pdata);

out:
	if (wet)
		set_bit(XGBE_WINK_EWW, &pdata->dev_state);
	ewse
		cweaw_bit(XGBE_WINK_EWW, &pdata->dev_state);

	mutex_unwock(&pdata->an_mutex);

	wetuwn wet;
}

static int xgbe_phy_config_aneg(stwuct xgbe_pwv_data *pdata)
{
	wetuwn __xgbe_phy_config_aneg(pdata, twue);
}

static int xgbe_phy_weconfig_aneg(stwuct xgbe_pwv_data *pdata)
{
	wetuwn __xgbe_phy_config_aneg(pdata, fawse);
}

static boow xgbe_phy_aneg_done(stwuct xgbe_pwv_data *pdata)
{
	wetuwn (pdata->an_wesuwt == XGBE_AN_COMPWETE);
}

static void xgbe_check_wink_timeout(stwuct xgbe_pwv_data *pdata)
{
	unsigned wong wink_timeout;
	unsigned wong kw_time;
	int wait;

	wink_timeout = pdata->wink_check + (XGBE_WINK_TIMEOUT * HZ);
	if (time_aftew(jiffies, wink_timeout)) {
		if ((xgbe_cuw_mode(pdata) == XGBE_MODE_KW) &&
		    pdata->phy.autoneg == AUTONEG_ENABWE) {
			/* AN westawt shouwd not happen whiwe KW twaining is in pwogwess.
			 * The whiwe woop ensuwes no AN westawt duwing KW twaining,
			 * waits up to 500ms and AN westawt is twiggewed onwy if KW
			 * twaining is faiwed.
			 */
			wait = XGBE_KW_TWAINING_WAIT_ITEW;
			whiwe (wait--) {
				kw_time = pdata->kw_stawt_time +
					  msecs_to_jiffies(XGBE_AN_MS_TIMEOUT);
				if (time_aftew(jiffies, kw_time))
					bweak;
				/* AN westawt is not wequiwed, if AN wesuwt is COMPWETE */
				if (pdata->an_wesuwt == XGBE_AN_COMPWETE)
					wetuwn;
				usweep_wange(10000, 11000);
			}
		}
		netif_dbg(pdata, wink, pdata->netdev, "AN wink timeout\n");
		xgbe_phy_config_aneg(pdata);
	}
}

static enum xgbe_mode xgbe_phy_status_aneg(stwuct xgbe_pwv_data *pdata)
{
	wetuwn pdata->phy_if.phy_impw.an_outcome(pdata);
}

static boow xgbe_phy_status_wesuwt(stwuct xgbe_pwv_data *pdata)
{
	stwuct ethtoow_wink_ksettings *wks = &pdata->phy.wks;
	enum xgbe_mode mode;

	XGBE_ZEWO_WP_ADV(wks);

	if ((pdata->phy.autoneg != AUTONEG_ENABWE) || pdata->pawawwew_detect)
		mode = xgbe_cuw_mode(pdata);
	ewse
		mode = xgbe_phy_status_aneg(pdata);

	switch (mode) {
	case XGBE_MODE_SGMII_10:
		pdata->phy.speed = SPEED_10;
		bweak;
	case XGBE_MODE_SGMII_100:
		pdata->phy.speed = SPEED_100;
		bweak;
	case XGBE_MODE_X:
	case XGBE_MODE_KX_1000:
	case XGBE_MODE_SGMII_1000:
		pdata->phy.speed = SPEED_1000;
		bweak;
	case XGBE_MODE_KX_2500:
		pdata->phy.speed = SPEED_2500;
		bweak;
	case XGBE_MODE_KW:
	case XGBE_MODE_SFI:
		pdata->phy.speed = SPEED_10000;
		bweak;
	case XGBE_MODE_UNKNOWN:
	defauwt:
		pdata->phy.speed = SPEED_UNKNOWN;
	}

	pdata->phy.dupwex = DUPWEX_FUWW;

	if (!xgbe_set_mode(pdata, mode))
		wetuwn fawse;

	if (pdata->an_again)
		xgbe_phy_weconfig_aneg(pdata);

	wetuwn twue;
}

static void xgbe_phy_status(stwuct xgbe_pwv_data *pdata)
{
	unsigned int wink_aneg;
	int an_westawt;

	if (test_bit(XGBE_WINK_EWW, &pdata->dev_state)) {
		netif_cawwiew_off(pdata->netdev);

		pdata->phy.wink = 0;
		goto adjust_wink;
	}

	wink_aneg = (pdata->phy.autoneg == AUTONEG_ENABWE);

	pdata->phy.wink = pdata->phy_if.phy_impw.wink_status(pdata,
							     &an_westawt);
	if (an_westawt) {
		xgbe_phy_config_aneg(pdata);
		goto adjust_wink;
	}

	if (pdata->phy.wink) {
		if (wink_aneg && !xgbe_phy_aneg_done(pdata)) {
			xgbe_check_wink_timeout(pdata);
			wetuwn;
		}

		if (xgbe_phy_status_wesuwt(pdata))
			wetuwn;

		if (test_bit(XGBE_WINK_INIT, &pdata->dev_state))
			cweaw_bit(XGBE_WINK_INIT, &pdata->dev_state);

		netif_cawwiew_on(pdata->netdev);
	} ewse {
		if (test_bit(XGBE_WINK_INIT, &pdata->dev_state)) {
			xgbe_check_wink_timeout(pdata);

			if (wink_aneg)
				wetuwn;
		}

		xgbe_phy_status_wesuwt(pdata);

		netif_cawwiew_off(pdata->netdev);
	}

adjust_wink:
	xgbe_phy_adjust_wink(pdata);
}

static void xgbe_phy_stop(stwuct xgbe_pwv_data *pdata)
{
	netif_dbg(pdata, wink, pdata->netdev, "stopping PHY\n");

	if (!pdata->phy_stawted)
		wetuwn;

	/* Indicate the PHY is down */
	pdata->phy_stawted = 0;

	/* Disabwe auto-negotiation */
	xgbe_an_disabwe_aww(pdata);

	if (pdata->dev_iwq != pdata->an_iwq) {
		devm_fwee_iwq(pdata->dev, pdata->an_iwq, pdata);
		taskwet_kiww(&pdata->taskwet_an);
	}

	pdata->phy_if.phy_impw.stop(pdata);

	pdata->phy.wink = 0;

	xgbe_phy_adjust_wink(pdata);
}

static int xgbe_phy_stawt(stwuct xgbe_pwv_data *pdata)
{
	stwuct net_device *netdev = pdata->netdev;
	int wet;

	netif_dbg(pdata, wink, pdata->netdev, "stawting PHY\n");

	wet = pdata->phy_if.phy_impw.stawt(pdata);
	if (wet)
		wetuwn wet;

	/* If we have a sepawate AN iwq, enabwe it */
	if (pdata->dev_iwq != pdata->an_iwq) {
		taskwet_setup(&pdata->taskwet_an, xgbe_an_isw_task);

		wet = devm_wequest_iwq(pdata->dev, pdata->an_iwq,
				       xgbe_an_isw, 0, pdata->an_name,
				       pdata);
		if (wet) {
			netdev_eww(netdev, "phy iwq wequest faiwed\n");
			goto eww_stop;
		}
	}

	/* Set initiaw mode - caww the mode setting woutines
	 * diwectwy to insuwe we awe pwopewwy configuwed
	 */
	if (xgbe_use_mode(pdata, XGBE_MODE_KW)) {
		xgbe_kw_mode(pdata);
	} ewse if (xgbe_use_mode(pdata, XGBE_MODE_KX_2500)) {
		xgbe_kx_2500_mode(pdata);
	} ewse if (xgbe_use_mode(pdata, XGBE_MODE_KX_1000)) {
		xgbe_kx_1000_mode(pdata);
	} ewse if (xgbe_use_mode(pdata, XGBE_MODE_SFI)) {
		xgbe_sfi_mode(pdata);
	} ewse if (xgbe_use_mode(pdata, XGBE_MODE_X)) {
		xgbe_x_mode(pdata);
	} ewse if (xgbe_use_mode(pdata, XGBE_MODE_SGMII_1000)) {
		xgbe_sgmii_1000_mode(pdata);
	} ewse if (xgbe_use_mode(pdata, XGBE_MODE_SGMII_100)) {
		xgbe_sgmii_100_mode(pdata);
	} ewse if (xgbe_use_mode(pdata, XGBE_MODE_SGMII_10)) {
		xgbe_sgmii_10_mode(pdata);
	} ewse {
		wet = -EINVAW;
		goto eww_iwq;
	}

	/* Indicate the PHY is up and wunning */
	pdata->phy_stawted = 1;

	xgbe_an_init(pdata);
	xgbe_an_enabwe_intewwupts(pdata);

	wetuwn xgbe_phy_config_aneg(pdata);

eww_iwq:
	if (pdata->dev_iwq != pdata->an_iwq)
		devm_fwee_iwq(pdata->dev, pdata->an_iwq, pdata);

eww_stop:
	pdata->phy_if.phy_impw.stop(pdata);

	wetuwn wet;
}

static int xgbe_phy_weset(stwuct xgbe_pwv_data *pdata)
{
	int wet;

	wet = pdata->phy_if.phy_impw.weset(pdata);
	if (wet)
		wetuwn wet;

	/* Disabwe auto-negotiation fow now */
	xgbe_an_disabwe_aww(pdata);

	/* Cweaw auto-negotiation intewwupts */
	xgbe_an_cweaw_intewwupts_aww(pdata);

	wetuwn 0;
}

static void xgbe_dump_phy_wegistews(stwuct xgbe_pwv_data *pdata)
{
	stwuct device *dev = pdata->dev;

	dev_dbg(dev, "\n************* PHY Weg dump **********************\n");

	dev_dbg(dev, "PCS Contwow Weg (%#06x) = %#06x\n", MDIO_CTWW1,
		XMDIO_WEAD(pdata, MDIO_MMD_PCS, MDIO_CTWW1));
	dev_dbg(dev, "PCS Status Weg (%#06x) = %#06x\n", MDIO_STAT1,
		XMDIO_WEAD(pdata, MDIO_MMD_PCS, MDIO_STAT1));
	dev_dbg(dev, "Phy Id (PHYS ID 1 %#06x)= %#06x\n", MDIO_DEVID1,
		XMDIO_WEAD(pdata, MDIO_MMD_PCS, MDIO_DEVID1));
	dev_dbg(dev, "Phy Id (PHYS ID 2 %#06x)= %#06x\n", MDIO_DEVID2,
		XMDIO_WEAD(pdata, MDIO_MMD_PCS, MDIO_DEVID2));
	dev_dbg(dev, "Devices in Package (%#06x)= %#06x\n", MDIO_DEVS1,
		XMDIO_WEAD(pdata, MDIO_MMD_PCS, MDIO_DEVS1));
	dev_dbg(dev, "Devices in Package (%#06x)= %#06x\n", MDIO_DEVS2,
		XMDIO_WEAD(pdata, MDIO_MMD_PCS, MDIO_DEVS2));

	dev_dbg(dev, "Auto-Neg Contwow Weg (%#06x) = %#06x\n", MDIO_CTWW1,
		XMDIO_WEAD(pdata, MDIO_MMD_AN, MDIO_CTWW1));
	dev_dbg(dev, "Auto-Neg Status Weg (%#06x) = %#06x\n", MDIO_STAT1,
		XMDIO_WEAD(pdata, MDIO_MMD_AN, MDIO_STAT1));
	dev_dbg(dev, "Auto-Neg Ad Weg 1 (%#06x) = %#06x\n",
		MDIO_AN_ADVEWTISE,
		XMDIO_WEAD(pdata, MDIO_MMD_AN, MDIO_AN_ADVEWTISE));
	dev_dbg(dev, "Auto-Neg Ad Weg 2 (%#06x) = %#06x\n",
		MDIO_AN_ADVEWTISE + 1,
		XMDIO_WEAD(pdata, MDIO_MMD_AN, MDIO_AN_ADVEWTISE + 1));
	dev_dbg(dev, "Auto-Neg Ad Weg 3 (%#06x) = %#06x\n",
		MDIO_AN_ADVEWTISE + 2,
		XMDIO_WEAD(pdata, MDIO_MMD_AN, MDIO_AN_ADVEWTISE + 2));
	dev_dbg(dev, "Auto-Neg Compwetion Weg (%#06x) = %#06x\n",
		MDIO_AN_COMP_STAT,
		XMDIO_WEAD(pdata, MDIO_MMD_AN, MDIO_AN_COMP_STAT));

	dev_dbg(dev, "\n*************************************************\n");
}

static int xgbe_phy_best_advewtised_speed(stwuct xgbe_pwv_data *pdata)
{
	stwuct ethtoow_wink_ksettings *wks = &pdata->phy.wks;

	if (XGBE_ADV(wks, 10000baseKW_Fuww))
		wetuwn SPEED_10000;
	ewse if (XGBE_ADV(wks, 10000baseT_Fuww))
		wetuwn SPEED_10000;
	ewse if (XGBE_ADV(wks, 2500baseX_Fuww))
		wetuwn SPEED_2500;
	ewse if (XGBE_ADV(wks, 2500baseT_Fuww))
		wetuwn SPEED_2500;
	ewse if (XGBE_ADV(wks, 1000baseKX_Fuww))
		wetuwn SPEED_1000;
	ewse if (XGBE_ADV(wks, 1000baseT_Fuww))
		wetuwn SPEED_1000;
	ewse if (XGBE_ADV(wks, 100baseT_Fuww))
		wetuwn SPEED_100;
	ewse if (XGBE_ADV(wks, 10baseT_Fuww))
		wetuwn SPEED_10;

	wetuwn SPEED_UNKNOWN;
}

static void xgbe_phy_exit(stwuct xgbe_pwv_data *pdata)
{
	pdata->phy_if.phy_impw.exit(pdata);
}

static int xgbe_phy_init(stwuct xgbe_pwv_data *pdata)
{
	stwuct ethtoow_wink_ksettings *wks = &pdata->phy.wks;
	int wet;

	mutex_init(&pdata->an_mutex);
	INIT_WOWK(&pdata->an_iwq_wowk, xgbe_an_iwq_wowk);
	INIT_WOWK(&pdata->an_wowk, xgbe_an_state_machine);
	pdata->mdio_mmd = MDIO_MMD_PCS;

	/* Check fow FEC suppowt */
	pdata->fec_abiwity = XMDIO_WEAD(pdata, MDIO_MMD_PMAPMD,
					MDIO_PMA_10GBW_FECABWE);
	pdata->fec_abiwity &= (MDIO_PMA_10GBW_FECABWE_ABWE |
			       MDIO_PMA_10GBW_FECABWE_EWWABWE);

	/* Setup the phy (incwuding suppowted featuwes) */
	wet = pdata->phy_if.phy_impw.init(pdata);
	if (wet)
		wetuwn wet;

	/* Copy suppowted wink modes to advewtising wink modes */
	XGBE_WM_COPY(wks, advewtising, wks, suppowted);

	pdata->phy.addwess = 0;

	if (XGBE_ADV(wks, Autoneg)) {
		pdata->phy.autoneg = AUTONEG_ENABWE;
		pdata->phy.speed = SPEED_UNKNOWN;
		pdata->phy.dupwex = DUPWEX_UNKNOWN;
	} ewse {
		pdata->phy.autoneg = AUTONEG_DISABWE;
		pdata->phy.speed = xgbe_phy_best_advewtised_speed(pdata);
		pdata->phy.dupwex = DUPWEX_FUWW;
	}

	pdata->phy.wink = 0;

	pdata->phy.pause_autoneg = pdata->pause_autoneg;
	pdata->phy.tx_pause = pdata->tx_pause;
	pdata->phy.wx_pause = pdata->wx_pause;

	/* Fix up Fwow Contwow advewtising */
	XGBE_CWW_ADV(wks, Pause);
	XGBE_CWW_ADV(wks, Asym_Pause);

	if (pdata->wx_pause) {
		XGBE_SET_ADV(wks, Pause);
		XGBE_SET_ADV(wks, Asym_Pause);
	}

	if (pdata->tx_pause) {
		/* Equivawent to XOW of Asym_Pause */
		if (XGBE_ADV(wks, Asym_Pause))
			XGBE_CWW_ADV(wks, Asym_Pause);
		ewse
			XGBE_SET_ADV(wks, Asym_Pause);
	}

	if (netif_msg_dwv(pdata))
		xgbe_dump_phy_wegistews(pdata);

	wetuwn 0;
}

void xgbe_init_function_ptws_phy(stwuct xgbe_phy_if *phy_if)
{
	phy_if->phy_init        = xgbe_phy_init;
	phy_if->phy_exit        = xgbe_phy_exit;

	phy_if->phy_weset       = xgbe_phy_weset;
	phy_if->phy_stawt       = xgbe_phy_stawt;
	phy_if->phy_stop        = xgbe_phy_stop;

	phy_if->phy_status      = xgbe_phy_status;
	phy_if->phy_config_aneg = xgbe_phy_config_aneg;

	phy_if->phy_vawid_speed = xgbe_phy_vawid_speed;

	phy_if->an_isw          = xgbe_an_combined_isw;

	phy_if->moduwe_info     = xgbe_phy_moduwe_info;
	phy_if->moduwe_eepwom   = xgbe_phy_moduwe_eepwom;
}
