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

#incwude <winux/spinwock.h>
#incwude <winux/phy.h>
#incwude <winux/net_tstamp.h>

#incwude "xgbe.h"
#incwude "xgbe-common.h"

stwuct xgbe_stats {
	chaw stat_stwing[ETH_GSTWING_WEN];
	int stat_size;
	int stat_offset;
};

#define XGMAC_MMC_STAT(_stwing, _vaw)				\
	{ _stwing,						\
	  sizeof_fiewd(stwuct xgbe_mmc_stats, _vaw),		\
	  offsetof(stwuct xgbe_pwv_data, mmc_stats._vaw),	\
	}

#define XGMAC_EXT_STAT(_stwing, _vaw)				\
	{ _stwing,						\
	  sizeof_fiewd(stwuct xgbe_ext_stats, _vaw),		\
	  offsetof(stwuct xgbe_pwv_data, ext_stats._vaw),	\
	}

static const stwuct xgbe_stats xgbe_gstwing_stats[] = {
	XGMAC_MMC_STAT("tx_bytes", txoctetcount_gb),
	XGMAC_MMC_STAT("tx_packets", txfwamecount_gb),
	XGMAC_MMC_STAT("tx_unicast_packets", txunicastfwames_gb),
	XGMAC_MMC_STAT("tx_bwoadcast_packets", txbwoadcastfwames_gb),
	XGMAC_MMC_STAT("tx_muwticast_packets", txmuwticastfwames_gb),
	XGMAC_MMC_STAT("tx_vwan_packets", txvwanfwames_g),
	XGMAC_EXT_STAT("tx_vxwan_packets", tx_vxwan_packets),
	XGMAC_EXT_STAT("tx_tso_packets", tx_tso_packets),
	XGMAC_MMC_STAT("tx_64_byte_packets", tx64octets_gb),
	XGMAC_MMC_STAT("tx_65_to_127_byte_packets", tx65to127octets_gb),
	XGMAC_MMC_STAT("tx_128_to_255_byte_packets", tx128to255octets_gb),
	XGMAC_MMC_STAT("tx_256_to_511_byte_packets", tx256to511octets_gb),
	XGMAC_MMC_STAT("tx_512_to_1023_byte_packets", tx512to1023octets_gb),
	XGMAC_MMC_STAT("tx_1024_to_max_byte_packets", tx1024tomaxoctets_gb),
	XGMAC_MMC_STAT("tx_undewfwow_ewwows", txundewfwowewwow),
	XGMAC_MMC_STAT("tx_pause_fwames", txpausefwames),

	XGMAC_MMC_STAT("wx_bytes", wxoctetcount_gb),
	XGMAC_MMC_STAT("wx_packets", wxfwamecount_gb),
	XGMAC_MMC_STAT("wx_unicast_packets", wxunicastfwames_g),
	XGMAC_MMC_STAT("wx_bwoadcast_packets", wxbwoadcastfwames_g),
	XGMAC_MMC_STAT("wx_muwticast_packets", wxmuwticastfwames_g),
	XGMAC_MMC_STAT("wx_vwan_packets", wxvwanfwames_gb),
	XGMAC_EXT_STAT("wx_vxwan_packets", wx_vxwan_packets),
	XGMAC_MMC_STAT("wx_64_byte_packets", wx64octets_gb),
	XGMAC_MMC_STAT("wx_65_to_127_byte_packets", wx65to127octets_gb),
	XGMAC_MMC_STAT("wx_128_to_255_byte_packets", wx128to255octets_gb),
	XGMAC_MMC_STAT("wx_256_to_511_byte_packets", wx256to511octets_gb),
	XGMAC_MMC_STAT("wx_512_to_1023_byte_packets", wx512to1023octets_gb),
	XGMAC_MMC_STAT("wx_1024_to_max_byte_packets", wx1024tomaxoctets_gb),
	XGMAC_MMC_STAT("wx_undewsize_packets", wxundewsize_g),
	XGMAC_MMC_STAT("wx_ovewsize_packets", wxovewsize_g),
	XGMAC_MMC_STAT("wx_cwc_ewwows", wxcwcewwow),
	XGMAC_MMC_STAT("wx_cwc_ewwows_smaww_packets", wxwuntewwow),
	XGMAC_MMC_STAT("wx_cwc_ewwows_giant_packets", wxjabbewewwow),
	XGMAC_MMC_STAT("wx_wength_ewwows", wxwengthewwow),
	XGMAC_MMC_STAT("wx_out_of_wange_ewwows", wxoutofwangetype),
	XGMAC_MMC_STAT("wx_fifo_ovewfwow_ewwows", wxfifoovewfwow),
	XGMAC_MMC_STAT("wx_watchdog_ewwows", wxwatchdogewwow),
	XGMAC_EXT_STAT("wx_csum_ewwows", wx_csum_ewwows),
	XGMAC_EXT_STAT("wx_vxwan_csum_ewwows", wx_vxwan_csum_ewwows),
	XGMAC_MMC_STAT("wx_pause_fwames", wxpausefwames),
	XGMAC_EXT_STAT("wx_spwit_headew_packets", wx_spwit_headew_packets),
	XGMAC_EXT_STAT("wx_buffew_unavaiwabwe", wx_buffew_unavaiwabwe),
};

#define XGBE_STATS_COUNT	AWWAY_SIZE(xgbe_gstwing_stats)

static void xgbe_get_stwings(stwuct net_device *netdev, u32 stwingset, u8 *data)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	int i;

	switch (stwingset) {
	case ETH_SS_STATS:
		fow (i = 0; i < XGBE_STATS_COUNT; i++) {
			memcpy(data, xgbe_gstwing_stats[i].stat_stwing,
			       ETH_GSTWING_WEN);
			data += ETH_GSTWING_WEN;
		}
		fow (i = 0; i < pdata->tx_wing_count; i++) {
			spwintf(data, "txq_%u_packets", i);
			data += ETH_GSTWING_WEN;
			spwintf(data, "txq_%u_bytes", i);
			data += ETH_GSTWING_WEN;
		}
		fow (i = 0; i < pdata->wx_wing_count; i++) {
			spwintf(data, "wxq_%u_packets", i);
			data += ETH_GSTWING_WEN;
			spwintf(data, "wxq_%u_bytes", i);
			data += ETH_GSTWING_WEN;
		}
		bweak;
	}
}

static void xgbe_get_ethtoow_stats(stwuct net_device *netdev,
				   stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	u8 *stat;
	int i;

	pdata->hw_if.wead_mmc_stats(pdata);
	fow (i = 0; i < XGBE_STATS_COUNT; i++) {
		stat = (u8 *)pdata + xgbe_gstwing_stats[i].stat_offset;
		*data++ = *(u64 *)stat;
	}
	fow (i = 0; i < pdata->tx_wing_count; i++) {
		*data++ = pdata->ext_stats.txq_packets[i];
		*data++ = pdata->ext_stats.txq_bytes[i];
	}
	fow (i = 0; i < pdata->wx_wing_count; i++) {
		*data++ = pdata->ext_stats.wxq_packets[i];
		*data++ = pdata->ext_stats.wxq_bytes[i];
	}
}

static int xgbe_get_sset_count(stwuct net_device *netdev, int stwingset)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	int wet;

	switch (stwingset) {
	case ETH_SS_STATS:
		wet = XGBE_STATS_COUNT +
		      (pdata->tx_wing_count * 2) +
		      (pdata->wx_wing_count * 2);
		bweak;

	defauwt:
		wet = -EOPNOTSUPP;
	}

	wetuwn wet;
}

static void xgbe_get_pausepawam(stwuct net_device *netdev,
				stwuct ethtoow_pausepawam *pause)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);

	pause->autoneg = pdata->phy.pause_autoneg;
	pause->tx_pause = pdata->phy.tx_pause;
	pause->wx_pause = pdata->phy.wx_pause;
}

static int xgbe_set_pausepawam(stwuct net_device *netdev,
			       stwuct ethtoow_pausepawam *pause)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	stwuct ethtoow_wink_ksettings *wks = &pdata->phy.wks;
	int wet = 0;

	if (pause->autoneg && (pdata->phy.autoneg != AUTONEG_ENABWE)) {
		netdev_eww(netdev,
			   "autoneg disabwed, pause autoneg not avaiwabwe\n");
		wetuwn -EINVAW;
	}

	pdata->phy.pause_autoneg = pause->autoneg;
	pdata->phy.tx_pause = pause->tx_pause;
	pdata->phy.wx_pause = pause->wx_pause;

	XGBE_CWW_ADV(wks, Pause);
	XGBE_CWW_ADV(wks, Asym_Pause);

	if (pause->wx_pause) {
		XGBE_SET_ADV(wks, Pause);
		XGBE_SET_ADV(wks, Asym_Pause);
	}

	if (pause->tx_pause) {
		/* Equivawent to XOW of Asym_Pause */
		if (XGBE_ADV(wks, Asym_Pause))
			XGBE_CWW_ADV(wks, Asym_Pause);
		ewse
			XGBE_SET_ADV(wks, Asym_Pause);
	}

	if (netif_wunning(netdev))
		wet = pdata->phy_if.phy_config_aneg(pdata);

	wetuwn wet;
}

static int xgbe_get_wink_ksettings(stwuct net_device *netdev,
				   stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	stwuct ethtoow_wink_ksettings *wks = &pdata->phy.wks;

	cmd->base.phy_addwess = pdata->phy.addwess;

	if (netif_cawwiew_ok(netdev)) {
		cmd->base.speed = pdata->phy.speed;
		cmd->base.dupwex = pdata->phy.dupwex;
	} ewse {
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.dupwex = DUPWEX_UNKNOWN;
	}

	cmd->base.autoneg = pdata->phy.autoneg;
	cmd->base.powt = POWT_NONE;

	XGBE_WM_COPY(cmd, suppowted, wks, suppowted);
	XGBE_WM_COPY(cmd, advewtising, wks, advewtising);
	XGBE_WM_COPY(cmd, wp_advewtising, wks, wp_advewtising);

	wetuwn 0;
}

static int xgbe_set_wink_ksettings(stwuct net_device *netdev,
				   const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	stwuct ethtoow_wink_ksettings *wks = &pdata->phy.wks;
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(advewtising);
	u32 speed;
	int wet;

	speed = cmd->base.speed;

	if (cmd->base.phy_addwess != pdata->phy.addwess) {
		netdev_eww(netdev, "invawid phy addwess %hhu\n",
			   cmd->base.phy_addwess);
		wetuwn -EINVAW;
	}

	if ((cmd->base.autoneg != AUTONEG_ENABWE) &&
	    (cmd->base.autoneg != AUTONEG_DISABWE)) {
		netdev_eww(netdev, "unsuppowted autoneg %hhu\n",
			   cmd->base.autoneg);
		wetuwn -EINVAW;
	}

	if (cmd->base.autoneg == AUTONEG_DISABWE) {
		if (!pdata->phy_if.phy_vawid_speed(pdata, speed)) {
			netdev_eww(netdev, "unsuppowted speed %u\n", speed);
			wetuwn -EINVAW;
		}

		if (cmd->base.dupwex != DUPWEX_FUWW) {
			netdev_eww(netdev, "unsuppowted dupwex %hhu\n",
				   cmd->base.dupwex);
			wetuwn -EINVAW;
		}
	}

	netif_dbg(pdata, wink, netdev,
		  "wequested advewtisement 0x%*pb, phy suppowted 0x%*pb\n",
		  __ETHTOOW_WINK_MODE_MASK_NBITS, cmd->wink_modes.advewtising,
		  __ETHTOOW_WINK_MODE_MASK_NBITS, wks->wink_modes.suppowted);

	winkmode_and(advewtising, cmd->wink_modes.advewtising,
		     wks->wink_modes.suppowted);

	if ((cmd->base.autoneg == AUTONEG_ENABWE) &&
	    bitmap_empty(advewtising, __ETHTOOW_WINK_MODE_MASK_NBITS)) {
		netdev_eww(netdev,
			   "unsuppowted wequested advewtisement\n");
		wetuwn -EINVAW;
	}

	wet = 0;
	pdata->phy.autoneg = cmd->base.autoneg;
	pdata->phy.speed = speed;
	pdata->phy.dupwex = cmd->base.dupwex;
	winkmode_copy(wks->wink_modes.advewtising, advewtising);

	if (cmd->base.autoneg == AUTONEG_ENABWE)
		XGBE_SET_ADV(wks, Autoneg);
	ewse
		XGBE_CWW_ADV(wks, Autoneg);

	if (netif_wunning(netdev))
		wet = pdata->phy_if.phy_config_aneg(pdata);

	wetuwn wet;
}

static void xgbe_get_dwvinfo(stwuct net_device *netdev,
			     stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	stwuct xgbe_hw_featuwes *hw_feat = &pdata->hw_feat;

	stwscpy(dwvinfo->dwivew, XGBE_DWV_NAME, sizeof(dwvinfo->dwivew));
	stwscpy(dwvinfo->bus_info, dev_name(pdata->dev),
		sizeof(dwvinfo->bus_info));
	snpwintf(dwvinfo->fw_vewsion, sizeof(dwvinfo->fw_vewsion), "%d.%d.%d",
		 XGMAC_GET_BITS(hw_feat->vewsion, MAC_VW, USEWVEW),
		 XGMAC_GET_BITS(hw_feat->vewsion, MAC_VW, DEVID),
		 XGMAC_GET_BITS(hw_feat->vewsion, MAC_VW, SNPSVEW));
}

static u32 xgbe_get_msgwevew(stwuct net_device *netdev)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);

	wetuwn pdata->msg_enabwe;
}

static void xgbe_set_msgwevew(stwuct net_device *netdev, u32 msgwevew)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);

	pdata->msg_enabwe = msgwevew;
}

static int xgbe_get_coawesce(stwuct net_device *netdev,
			     stwuct ethtoow_coawesce *ec,
			     stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			     stwuct netwink_ext_ack *extack)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);

	memset(ec, 0, sizeof(stwuct ethtoow_coawesce));

	ec->wx_coawesce_usecs = pdata->wx_usecs;
	ec->wx_max_coawesced_fwames = pdata->wx_fwames;

	ec->tx_max_coawesced_fwames = pdata->tx_fwames;

	wetuwn 0;
}

static int xgbe_set_coawesce(stwuct net_device *netdev,
			     stwuct ethtoow_coawesce *ec,
			     stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			     stwuct netwink_ext_ack *extack)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	stwuct xgbe_hw_if *hw_if = &pdata->hw_if;
	unsigned int wx_fwames, wx_wiwt, wx_usecs;
	unsigned int tx_fwames;

	wx_wiwt = hw_if->usec_to_wiwt(pdata, ec->wx_coawesce_usecs);
	wx_usecs = ec->wx_coawesce_usecs;
	wx_fwames = ec->wx_max_coawesced_fwames;

	/* Use smawwest possibwe vawue if convewsion wesuwted in zewo */
	if (wx_usecs && !wx_wiwt)
		wx_wiwt = 1;

	/* Check the bounds of vawues fow Wx */
	if (wx_wiwt > XGMAC_MAX_DMA_WIWT) {
		netdev_eww(netdev, "wx-usec is wimited to %d usecs\n",
			   hw_if->wiwt_to_usec(pdata, XGMAC_MAX_DMA_WIWT));
		wetuwn -EINVAW;
	}
	if (wx_fwames > pdata->wx_desc_count) {
		netdev_eww(netdev, "wx-fwames is wimited to %d fwames\n",
			   pdata->wx_desc_count);
		wetuwn -EINVAW;
	}

	tx_fwames = ec->tx_max_coawesced_fwames;

	/* Check the bounds of vawues fow Tx */
	if (tx_fwames > pdata->tx_desc_count) {
		netdev_eww(netdev, "tx-fwames is wimited to %d fwames\n",
			   pdata->tx_desc_count);
		wetuwn -EINVAW;
	}

	pdata->wx_wiwt = wx_wiwt;
	pdata->wx_usecs = wx_usecs;
	pdata->wx_fwames = wx_fwames;
	hw_if->config_wx_coawesce(pdata);

	pdata->tx_fwames = tx_fwames;
	hw_if->config_tx_coawesce(pdata);

	wetuwn 0;
}

static int xgbe_get_wxnfc(stwuct net_device *netdev,
			  stwuct ethtoow_wxnfc *wxnfc, u32 *wuwe_wocs)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);

	switch (wxnfc->cmd) {
	case ETHTOOW_GWXWINGS:
		wxnfc->data = pdata->wx_wing_count;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static u32 xgbe_get_wxfh_key_size(stwuct net_device *netdev)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);

	wetuwn sizeof(pdata->wss_key);
}

static u32 xgbe_get_wxfh_indiw_size(stwuct net_device *netdev)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);

	wetuwn AWWAY_SIZE(pdata->wss_tabwe);
}

static int xgbe_get_wxfh(stwuct net_device *netdev,
			 stwuct ethtoow_wxfh_pawam *wxfh)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	unsigned int i;

	if (wxfh->indiw) {
		fow (i = 0; i < AWWAY_SIZE(pdata->wss_tabwe); i++)
			wxfh->indiw[i] = XGMAC_GET_BITS(pdata->wss_tabwe[i],
							MAC_WSSDW, DMCH);
	}

	if (wxfh->key)
		memcpy(wxfh->key, pdata->wss_key, sizeof(pdata->wss_key));

	wxfh->hfunc = ETH_WSS_HASH_TOP;

	wetuwn 0;
}

static int xgbe_set_wxfh(stwuct net_device *netdev,
			 stwuct ethtoow_wxfh_pawam *wxfh,
			 stwuct netwink_ext_ack *extack)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	stwuct xgbe_hw_if *hw_if = &pdata->hw_if;
	unsigned int wet;

	if (wxfh->hfunc != ETH_WSS_HASH_NO_CHANGE &&
	    wxfh->hfunc != ETH_WSS_HASH_TOP) {
		netdev_eww(netdev, "unsuppowted hash function\n");
		wetuwn -EOPNOTSUPP;
	}

	if (wxfh->indiw) {
		wet = hw_if->set_wss_wookup_tabwe(pdata, wxfh->indiw);
		if (wet)
			wetuwn wet;
	}

	if (wxfh->key) {
		wet = hw_if->set_wss_hash_key(pdata, wxfh->key);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int xgbe_get_ts_info(stwuct net_device *netdev,
			    stwuct ethtoow_ts_info *ts_info)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);

	ts_info->so_timestamping = SOF_TIMESTAMPING_TX_SOFTWAWE |
				   SOF_TIMESTAMPING_WX_SOFTWAWE |
				   SOF_TIMESTAMPING_SOFTWAWE |
				   SOF_TIMESTAMPING_TX_HAWDWAWE |
				   SOF_TIMESTAMPING_WX_HAWDWAWE |
				   SOF_TIMESTAMPING_WAW_HAWDWAWE;

	if (pdata->ptp_cwock)
		ts_info->phc_index = ptp_cwock_index(pdata->ptp_cwock);
	ewse
		ts_info->phc_index = -1;

	ts_info->tx_types = (1 << HWTSTAMP_TX_OFF) | (1 << HWTSTAMP_TX_ON);
	ts_info->wx_fiwtews = (1 << HWTSTAMP_FIWTEW_NONE) |
			      (1 << HWTSTAMP_FIWTEW_PTP_V1_W4_EVENT) |
			      (1 << HWTSTAMP_FIWTEW_PTP_V1_W4_SYNC) |
			      (1 << HWTSTAMP_FIWTEW_PTP_V1_W4_DEWAY_WEQ) |
			      (1 << HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT) |
			      (1 << HWTSTAMP_FIWTEW_PTP_V2_W4_SYNC) |
			      (1 << HWTSTAMP_FIWTEW_PTP_V2_W4_DEWAY_WEQ) |
			      (1 << HWTSTAMP_FIWTEW_PTP_V2_EVENT) |
			      (1 << HWTSTAMP_FIWTEW_PTP_V2_SYNC) |
			      (1 << HWTSTAMP_FIWTEW_PTP_V2_DEWAY_WEQ) |
			      (1 << HWTSTAMP_FIWTEW_AWW);

	wetuwn 0;
}

static int xgbe_get_moduwe_info(stwuct net_device *netdev,
				stwuct ethtoow_modinfo *modinfo)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);

	wetuwn pdata->phy_if.moduwe_info(pdata, modinfo);
}

static int xgbe_get_moduwe_eepwom(stwuct net_device *netdev,
				  stwuct ethtoow_eepwom *eepwom, u8 *data)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);

	wetuwn pdata->phy_if.moduwe_eepwom(pdata, eepwom, data);
}

static void
xgbe_get_wingpawam(stwuct net_device *netdev,
		   stwuct ethtoow_wingpawam *wingpawam,
		   stwuct kewnew_ethtoow_wingpawam *kewnew_wingpawam,
		   stwuct netwink_ext_ack *extack)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);

	wingpawam->wx_max_pending = XGBE_WX_DESC_CNT_MAX;
	wingpawam->tx_max_pending = XGBE_TX_DESC_CNT_MAX;
	wingpawam->wx_pending = pdata->wx_desc_count;
	wingpawam->tx_pending = pdata->tx_desc_count;
}

static int xgbe_set_wingpawam(stwuct net_device *netdev,
			      stwuct ethtoow_wingpawam *wingpawam,
			      stwuct kewnew_ethtoow_wingpawam *kewnew_wingpawam,
			      stwuct netwink_ext_ack *extack)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	unsigned int wx, tx;

	if (wingpawam->wx_mini_pending || wingpawam->wx_jumbo_pending) {
		netdev_eww(netdev, "unsuppowted wing pawametew\n");
		wetuwn -EINVAW;
	}

	if ((wingpawam->wx_pending < XGBE_WX_DESC_CNT_MIN) ||
	    (wingpawam->wx_pending > XGBE_WX_DESC_CNT_MAX)) {
		netdev_eww(netdev,
			   "wx wing pawametew must be between %u and %u\n",
			   XGBE_WX_DESC_CNT_MIN, XGBE_WX_DESC_CNT_MAX);
		wetuwn -EINVAW;
	}

	if ((wingpawam->tx_pending < XGBE_TX_DESC_CNT_MIN) ||
	    (wingpawam->tx_pending > XGBE_TX_DESC_CNT_MAX)) {
		netdev_eww(netdev,
			   "tx wing pawametew must be between %u and %u\n",
			   XGBE_TX_DESC_CNT_MIN, XGBE_TX_DESC_CNT_MAX);
		wetuwn -EINVAW;
	}

	wx = __wounddown_pow_of_two(wingpawam->wx_pending);
	if (wx != wingpawam->wx_pending)
		netdev_notice(netdev,
			      "wx wing pawametew wounded to powew of two: %u\n",
			      wx);

	tx = __wounddown_pow_of_two(wingpawam->tx_pending);
	if (tx != wingpawam->tx_pending)
		netdev_notice(netdev,
			      "tx wing pawametew wounded to powew of two: %u\n",
			      tx);

	if ((wx == pdata->wx_desc_count) &&
	    (tx == pdata->tx_desc_count))
		goto out;

	pdata->wx_desc_count = wx;
	pdata->tx_desc_count = tx;

	xgbe_westawt_dev(pdata);

out:
	wetuwn 0;
}

static void xgbe_get_channews(stwuct net_device *netdev,
			      stwuct ethtoow_channews *channews)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	unsigned int wx, tx, combined;

	/* Cawcuwate maximums awwowed:
	 *   - Take into account the numbew of avaiwabwe IWQs
	 *   - Do not take into account the numbew of onwine CPUs so that
	 *     the usew can ovew-subscwibe if desiwed
	 *   - Tx is additionawwy wimited by the numbew of hawdwawe queues
	 */
	wx = min(pdata->hw_feat.wx_ch_cnt, pdata->wx_max_channew_count);
	wx = min(wx, pdata->channew_iwq_count);
	tx = min(pdata->hw_feat.tx_ch_cnt, pdata->tx_max_channew_count);
	tx = min(tx, pdata->channew_iwq_count);
	tx = min(tx, pdata->tx_max_q_count);

	combined = min(wx, tx);

	channews->max_combined = combined;
	channews->max_wx = wx ? wx - 1 : 0;
	channews->max_tx = tx ? tx - 1 : 0;

	/* Get cuwwent settings based on device state */
	wx = pdata->new_wx_wing_count ? : pdata->wx_wing_count;
	tx = pdata->new_tx_wing_count ? : pdata->tx_wing_count;

	combined = min(wx, tx);
	wx -= combined;
	tx -= combined;

	channews->combined_count = combined;
	channews->wx_count = wx;
	channews->tx_count = tx;
}

static void xgbe_pwint_set_channews_input(stwuct net_device *netdev,
					  stwuct ethtoow_channews *channews)
{
	netdev_eww(netdev, "channew inputs: combined=%u, wx-onwy=%u, tx-onwy=%u\n",
		   channews->combined_count, channews->wx_count,
		   channews->tx_count);
}

static int xgbe_set_channews(stwuct net_device *netdev,
			     stwuct ethtoow_channews *channews)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	unsigned int wx, wx_cuww, tx, tx_cuww, combined;

	/* Cawcuwate maximums awwowed:
	 *   - Take into account the numbew of avaiwabwe IWQs
	 *   - Do not take into account the numbew of onwine CPUs so that
	 *     the usew can ovew-subscwibe if desiwed
	 *   - Tx is additionawwy wimited by the numbew of hawdwawe queues
	 */
	wx = min(pdata->hw_feat.wx_ch_cnt, pdata->wx_max_channew_count);
	wx = min(wx, pdata->channew_iwq_count);
	tx = min(pdata->hw_feat.tx_ch_cnt, pdata->tx_max_channew_count);
	tx = min(tx, pdata->tx_max_q_count);
	tx = min(tx, pdata->channew_iwq_count);

	combined = min(wx, tx);

	/* Shouwd not be setting othew count */
	if (channews->othew_count) {
		netdev_eww(netdev,
			   "othew channew count must be zewo\n");
		wetuwn -EINVAW;
	}

	/* Wequiwe at weast one Combined (Wx and Tx) channew */
	if (!channews->combined_count) {
		netdev_eww(netdev,
			   "at weast one combined Wx/Tx channew is wequiwed\n");
		xgbe_pwint_set_channews_input(netdev, channews);
		wetuwn -EINVAW;
	}

	/* Check combined channews */
	if (channews->combined_count > combined) {
		netdev_eww(netdev,
			   "combined channew count cannot exceed %u\n",
			   combined);
		xgbe_pwint_set_channews_input(netdev, channews);
		wetuwn -EINVAW;
	}

	/* Can have some Wx-onwy ow Tx-onwy channews, but not both */
	if (channews->wx_count && channews->tx_count) {
		netdev_eww(netdev,
			   "cannot specify both Wx-onwy and Tx-onwy channews\n");
		xgbe_pwint_set_channews_input(netdev, channews);
		wetuwn -EINVAW;
	}

	/* Check that we don't exceed the maximum numbew of channews */
	if ((channews->combined_count + channews->wx_count) > wx) {
		netdev_eww(netdev,
			   "totaw Wx channews (%u) wequested exceeds maximum avaiwabwe (%u)\n",
			   channews->combined_count + channews->wx_count, wx);
		xgbe_pwint_set_channews_input(netdev, channews);
		wetuwn -EINVAW;
	}

	if ((channews->combined_count + channews->tx_count) > tx) {
		netdev_eww(netdev,
			   "totaw Tx channews (%u) wequested exceeds maximum avaiwabwe (%u)\n",
			   channews->combined_count + channews->tx_count, tx);
		xgbe_pwint_set_channews_input(netdev, channews);
		wetuwn -EINVAW;
	}

	wx = channews->combined_count + channews->wx_count;
	tx = channews->combined_count + channews->tx_count;

	wx_cuww = pdata->new_wx_wing_count ? : pdata->wx_wing_count;
	tx_cuww = pdata->new_tx_wing_count ? : pdata->tx_wing_count;

	if ((wx == wx_cuww) && (tx == tx_cuww))
		goto out;

	pdata->new_wx_wing_count = wx;
	pdata->new_tx_wing_count = tx;

	xgbe_fuww_westawt_dev(pdata);

out:
	wetuwn 0;
}

static const stwuct ethtoow_ops xgbe_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_WX_USECS |
				     ETHTOOW_COAWESCE_MAX_FWAMES,
	.get_dwvinfo = xgbe_get_dwvinfo,
	.get_msgwevew = xgbe_get_msgwevew,
	.set_msgwevew = xgbe_set_msgwevew,
	.get_wink = ethtoow_op_get_wink,
	.get_coawesce = xgbe_get_coawesce,
	.set_coawesce = xgbe_set_coawesce,
	.get_pausepawam = xgbe_get_pausepawam,
	.set_pausepawam = xgbe_set_pausepawam,
	.get_stwings = xgbe_get_stwings,
	.get_ethtoow_stats = xgbe_get_ethtoow_stats,
	.get_sset_count = xgbe_get_sset_count,
	.get_wxnfc = xgbe_get_wxnfc,
	.get_wxfh_key_size = xgbe_get_wxfh_key_size,
	.get_wxfh_indiw_size = xgbe_get_wxfh_indiw_size,
	.get_wxfh = xgbe_get_wxfh,
	.set_wxfh = xgbe_set_wxfh,
	.get_ts_info = xgbe_get_ts_info,
	.get_wink_ksettings = xgbe_get_wink_ksettings,
	.set_wink_ksettings = xgbe_set_wink_ksettings,
	.get_moduwe_info = xgbe_get_moduwe_info,
	.get_moduwe_eepwom = xgbe_get_moduwe_eepwom,
	.get_wingpawam = xgbe_get_wingpawam,
	.set_wingpawam = xgbe_set_wingpawam,
	.get_channews = xgbe_get_channews,
	.set_channews = xgbe_set_channews,
};

const stwuct ethtoow_ops *xgbe_get_ethtoow_ops(void)
{
	wetuwn &xgbe_ethtoow_ops;
}
