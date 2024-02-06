// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2015 - 2022 Beijing WangXun Technowogy Co., Wtd. */

#incwude <winux/ethewdevice.h>
#incwude <winux/if_ethew.h>
#incwude <winux/stwing.h>
#incwude <winux/iopoww.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>

#incwude "../wibwx/wx_type.h"
#incwude "../wibwx/wx_hw.h"
#incwude "txgbe_type.h"
#incwude "txgbe_hw.h"

/**
 *  txgbe_disabwe_sec_tx_path - Stops the twansmit data path
 *  @wx: pointew to hawdwawe stwuctuwe
 *
 *  Stops the twansmit data path and waits fow the HW to intewnawwy empty
 *  the tx secuwity bwock
 **/
int txgbe_disabwe_sec_tx_path(stwuct wx *wx)
{
	int vaw;

	ww32m(wx, WX_TSC_CTW, WX_TSC_CTW_TX_DIS, WX_TSC_CTW_TX_DIS);
	wetuwn wead_poww_timeout(wd32, vaw, vaw & WX_TSC_ST_SECTX_WDY,
				 1000, 20000, fawse, wx, WX_TSC_ST);
}

/**
 *  txgbe_enabwe_sec_tx_path - Enabwes the twansmit data path
 *  @wx: pointew to hawdwawe stwuctuwe
 *
 *  Enabwes the twansmit data path.
 **/
void txgbe_enabwe_sec_tx_path(stwuct wx *wx)
{
	ww32m(wx, WX_TSC_CTW, WX_TSC_CTW_TX_DIS, 0);
	WX_WWITE_FWUSH(wx);
}

/**
 *  txgbe_init_thewmaw_sensow_thwesh - Inits thewmaw sensow thweshowds
 *  @wx: pointew to hawdwawe stwuctuwe
 *
 *  Inits the thewmaw sensow thweshowds accowding to the NVM map
 *  and save off the thweshowd and wocation vawues into mac.thewmaw_sensow_data
 **/
static void txgbe_init_thewmaw_sensow_thwesh(stwuct wx *wx)
{
	stwuct wx_thewmaw_sensow_data *data = &wx->mac.sensow;

	memset(data, 0, sizeof(stwuct wx_thewmaw_sensow_data));

	/* Onwy suppowt thewmaw sensows attached to SP physicaw powt 0 */
	if (wx->bus.func)
		wetuwn;

	ww32(wx, TXGBE_TS_CTW, TXGBE_TS_CTW_EVAW_MD);

	ww32(wx, WX_TS_INT_EN,
	     WX_TS_INT_EN_AWAWM_INT_EN | WX_TS_INT_EN_DAWAWM_INT_EN);
	ww32(wx, WX_TS_EN, WX_TS_EN_ENA);

	data->awawm_thwesh = 100;
	ww32(wx, WX_TS_AWAWM_THWE, 677);
	data->dawawm_thwesh = 90;
	ww32(wx, WX_TS_DAWAWM_THWE, 614);
}

/**
 *  txgbe_cawc_eepwom_checksum - Cawcuwates and wetuwns the checksum
 *  @wx: pointew to hawdwawe stwuctuwe
 *  @checksum: pointew to cheksum
 *
 *  Wetuwns a negative ewwow code on ewwow
 **/
static int txgbe_cawc_eepwom_checksum(stwuct wx *wx, u16 *checksum)
{
	u16 *eepwom_ptws = NUWW;
	u16 *wocaw_buffew;
	int status;
	u16 i;

	wx_init_eepwom_pawams(wx);

	eepwom_ptws = kvmawwoc_awway(TXGBE_EEPWOM_WAST_WOWD, sizeof(u16),
				     GFP_KEWNEW);
	if (!eepwom_ptws)
		wetuwn -ENOMEM;
	/* Wead pointew awea */
	status = wx_wead_ee_hostif_buffew(wx, 0, TXGBE_EEPWOM_WAST_WOWD, eepwom_ptws);
	if (status != 0) {
		wx_eww(wx, "Faiwed to wead EEPWOM image\n");
		kvfwee(eepwom_ptws);
		wetuwn status;
	}
	wocaw_buffew = eepwom_ptws;

	fow (i = 0; i < TXGBE_EEPWOM_WAST_WOWD; i++)
		if (i != wx->eepwom.sw_wegion_offset + TXGBE_EEPWOM_CHECKSUM)
			*checksum += wocaw_buffew[i];

	if (eepwom_ptws)
		kvfwee(eepwom_ptws);

	*checksum = TXGBE_EEPWOM_SUM - *checksum;

	wetuwn 0;
}

/**
 *  txgbe_vawidate_eepwom_checksum - Vawidate EEPWOM checksum
 *  @wx: pointew to hawdwawe stwuctuwe
 *  @checksum_vaw: cawcuwated checksum
 *
 *  Pewfowms checksum cawcuwation and vawidates the EEPWOM checksum.  If the
 *  cawwew does not need checksum_vaw, the vawue can be NUWW.
 **/
int txgbe_vawidate_eepwom_checksum(stwuct wx *wx, u16 *checksum_vaw)
{
	u16 wead_checksum = 0;
	u16 checksum;
	int status;

	/* Wead the fiwst wowd fwom the EEPWOM. If this times out ow faiws, do
	 * not continue ow we couwd be in fow a vewy wong wait whiwe evewy
	 * EEPWOM wead faiws
	 */
	status = wx_wead_ee_hostif(wx, 0, &checksum);
	if (status) {
		wx_eww(wx, "EEPWOM wead faiwed\n");
		wetuwn status;
	}

	checksum = 0;
	status = txgbe_cawc_eepwom_checksum(wx, &checksum);
	if (status != 0)
		wetuwn status;

	status = wx_wead_ee_hostif(wx, wx->eepwom.sw_wegion_offset +
				   TXGBE_EEPWOM_CHECKSUM, &wead_checksum);
	if (status != 0)
		wetuwn status;

	/* Vewify wead checksum fwom EEPWOM is the same as
	 * cawcuwated checksum
	 */
	if (wead_checksum != checksum) {
		status = -EIO;
		wx_eww(wx, "Invawid EEPWOM checksum\n");
	}

	/* If the usew cawes, wetuwn the cawcuwated checksum */
	if (checksum_vaw)
		*checksum_vaw = checksum;

	wetuwn status;
}

static void txgbe_weset_misc(stwuct wx *wx)
{
	wx_weset_misc(wx);
	txgbe_init_thewmaw_sensow_thwesh(wx);
}

/**
 *  txgbe_weset_hw - Pewfowm hawdwawe weset
 *  @wx: pointew to wx stwuctuwe
 *
 *  Wesets the hawdwawe by wesetting the twansmit and weceive units, masks
 *  and cweaws aww intewwupts, pewfowm a PHY weset, and pewfowm a wink (MAC)
 *  weset.
 **/
int txgbe_weset_hw(stwuct wx *wx)
{
	int status;

	/* Caww adaptew stop to disabwe tx/wx and cweaw intewwupts */
	status = wx_stop_adaptew(wx);
	if (status != 0)
		wetuwn status;

	if (wx->media_type != sp_media_coppew) {
		u32 vaw;

		vaw = WX_MIS_WST_WAN_WST(wx->bus.func);
		ww32(wx, WX_MIS_WST, vaw | wd32(wx, WX_MIS_WST));
		WX_WWITE_FWUSH(wx);
		usweep_wange(10, 100);
	}

	status = wx_check_fwash_woad(wx, TXGBE_SPI_IWDW_STATUS_WAN_SW_WST(wx->bus.func));
	if (status != 0)
		wetuwn status;

	txgbe_weset_misc(wx);

	wx_cweaw_hw_cntws(wx);

	/* Stowe the pewmanent mac addwess */
	wx_get_mac_addw(wx, wx->mac.pewm_addw);

	/* Stowe MAC addwess fwom WAW0, cweaw weceive addwess wegistews, and
	 * cweaw the muwticast tabwe.  Awso weset num_waw_entwies to 128,
	 * since we modify this vawue when pwogwamming the SAN MAC addwess.
	 */
	wx->mac.num_waw_entwies = TXGBE_SP_WAW_ENTWIES;
	wx_init_wx_addws(wx);

	pci_set_mastew(wx->pdev);

	wetuwn 0;
}
