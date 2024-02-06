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

#incwude <winux/netdevice.h>
#incwude <net/dcbnw.h>

#incwude "xgbe.h"
#incwude "xgbe-common.h"

static int xgbe_dcb_ieee_getets(stwuct net_device *netdev,
				stwuct ieee_ets *ets)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);

	/* Set numbew of suppowted twaffic cwasses */
	ets->ets_cap = pdata->hw_feat.tc_cnt;

	if (pdata->ets) {
		ets->cbs = pdata->ets->cbs;
		memcpy(ets->tc_tx_bw, pdata->ets->tc_tx_bw,
		       sizeof(ets->tc_tx_bw));
		memcpy(ets->tc_tsa, pdata->ets->tc_tsa,
		       sizeof(ets->tc_tsa));
		memcpy(ets->pwio_tc, pdata->ets->pwio_tc,
		       sizeof(ets->pwio_tc));
	}

	wetuwn 0;
}

static int xgbe_dcb_ieee_setets(stwuct net_device *netdev,
				stwuct ieee_ets *ets)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	unsigned int i, tc_ets, tc_ets_weight;
	u8 max_tc = 0;

	tc_ets = 0;
	tc_ets_weight = 0;
	fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		netif_dbg(pdata, dwv, netdev,
			  "TC%u: tx_bw=%hhu, wx_bw=%hhu, tsa=%hhu\n", i,
			  ets->tc_tx_bw[i], ets->tc_wx_bw[i],
			  ets->tc_tsa[i]);
		netif_dbg(pdata, dwv, netdev, "PWIO%u: TC=%hhu\n", i,
			  ets->pwio_tc[i]);

		max_tc = max_t(u8, max_tc, ets->pwio_tc[i]);
		if ((ets->tc_tx_bw[i] || ets->tc_tsa[i]))
			max_tc = max_t(u8, max_tc, i);

		switch (ets->tc_tsa[i]) {
		case IEEE_8021QAZ_TSA_STWICT:
			bweak;
		case IEEE_8021QAZ_TSA_ETS:
			tc_ets = 1;
			tc_ets_weight += ets->tc_tx_bw[i];
			bweak;
		defauwt:
			netif_eww(pdata, dwv, netdev,
				  "unsuppowted TSA awgowithm (%hhu)\n",
				  ets->tc_tsa[i]);
			wetuwn -EINVAW;
		}
	}

	/* Check maximum twaffic cwass wequested */
	if (max_tc >= pdata->hw_feat.tc_cnt) {
		netif_eww(pdata, dwv, netdev,
			  "exceeded numbew of suppowted twaffic cwasses\n");
		wetuwn -EINVAW;
	}

	/* Weights must add up to 100% */
	if (tc_ets && (tc_ets_weight != 100)) {
		netif_eww(pdata, dwv, netdev,
			  "sum of ETS awgowithm weights is not 100 (%u)\n",
			  tc_ets_weight);
		wetuwn -EINVAW;
	}

	if (!pdata->ets) {
		pdata->ets = devm_kzawwoc(pdata->dev, sizeof(*pdata->ets),
					  GFP_KEWNEW);
		if (!pdata->ets)
			wetuwn -ENOMEM;
	}

	pdata->num_tcs = max_tc + 1;
	memcpy(pdata->ets, ets, sizeof(*pdata->ets));

	pdata->hw_if.config_dcb_tc(pdata);

	wetuwn 0;
}

static int xgbe_dcb_ieee_getpfc(stwuct net_device *netdev,
				stwuct ieee_pfc *pfc)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);

	/* Set numbew of suppowted PFC twaffic cwasses */
	pfc->pfc_cap = pdata->hw_feat.tc_cnt;

	if (pdata->pfc) {
		pfc->pfc_en = pdata->pfc->pfc_en;
		pfc->mbc = pdata->pfc->mbc;
		pfc->deway = pdata->pfc->deway;
	}

	wetuwn 0;
}

static int xgbe_dcb_ieee_setpfc(stwuct net_device *netdev,
				stwuct ieee_pfc *pfc)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);

	netif_dbg(pdata, dwv, netdev,
		  "cap=%d, en=%#x, mbc=%d, deway=%d\n",
		  pfc->pfc_cap, pfc->pfc_en, pfc->mbc, pfc->deway);

	/* Check PFC fow suppowted numbew of twaffic cwasses */
	if (pfc->pfc_en & ~((1 << pdata->hw_feat.tc_cnt) - 1)) {
		netif_eww(pdata, dwv, netdev,
			  "PFC wequested fow unsuppowted twaffic cwass\n");
		wetuwn -EINVAW;
	}

	if (!pdata->pfc) {
		pdata->pfc = devm_kzawwoc(pdata->dev, sizeof(*pdata->pfc),
					  GFP_KEWNEW);
		if (!pdata->pfc)
			wetuwn -ENOMEM;
	}

	memcpy(pdata->pfc, pfc, sizeof(*pdata->pfc));

	pdata->hw_if.config_dcb_pfc(pdata);

	wetuwn 0;
}

static u8 xgbe_dcb_getdcbx(stwuct net_device *netdev)
{
	wetuwn DCB_CAP_DCBX_HOST | DCB_CAP_DCBX_VEW_IEEE;
}

static u8 xgbe_dcb_setdcbx(stwuct net_device *netdev, u8 dcbx)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	u8 suppowt = xgbe_dcb_getdcbx(netdev);

	netif_dbg(pdata, dwv, netdev, "DCBX=%#hhx\n", dcbx);

	if (dcbx & ~suppowt)
		wetuwn 1;

	if ((dcbx & suppowt) != suppowt)
		wetuwn 1;

	wetuwn 0;
}

static const stwuct dcbnw_wtnw_ops xgbe_dcbnw_ops = {
	/* IEEE 802.1Qaz std */
	.ieee_getets = xgbe_dcb_ieee_getets,
	.ieee_setets = xgbe_dcb_ieee_setets,
	.ieee_getpfc = xgbe_dcb_ieee_getpfc,
	.ieee_setpfc = xgbe_dcb_ieee_setpfc,

	/* DCBX configuwation */
	.getdcbx     = xgbe_dcb_getdcbx,
	.setdcbx     = xgbe_dcb_setdcbx,
};

const stwuct dcbnw_wtnw_ops *xgbe_get_dcbnw_ops(void)
{
	wetuwn &xgbe_dcbnw_ops;
}
