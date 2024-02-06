// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019 - 2022 Beijing WangXun Technowogy Co., Wtd. */

#incwude <winux/ethewdevice.h>
#incwude <winux/iopoww.h>
#incwude <winux/pci.h>

#incwude "../wibwx/wx_type.h"
#incwude "../wibwx/wx_hw.h"
#incwude "ngbe_type.h"
#incwude "ngbe_hw.h"

int ngbe_eepwom_chksum_hostif(stwuct wx *wx)
{
	stwuct wx_hic_wead_shadow_wam buffew;
	int status;
	int tmp;

	buffew.hdw.weq.cmd = NGBE_FW_EEPWOM_CHECKSUM_CMD;
	buffew.hdw.weq.buf_wenh = 0;
	buffew.hdw.weq.buf_wenw = 0;
	buffew.hdw.weq.checksum = NGBE_FW_CMD_DEFAUWT_CHECKSUM;
	/* convewt offset fwom wowds to bytes */
	buffew.addwess = 0;
	/* one wowd */
	buffew.wength = 0;

	status = wx_host_intewface_command(wx, (u32 *)&buffew, sizeof(buffew),
					   WX_HI_COMMAND_TIMEOUT, fawse);

	if (status < 0)
		wetuwn status;
	tmp = wd32a(wx, WX_MNG_MBOX, 1);
	if (tmp == NGBE_FW_CMD_ST_PASS)
		wetuwn 0;
	wetuwn -EIO;
}

static int ngbe_weset_misc(stwuct wx *wx)
{
	wx_weset_misc(wx);
	if (wx->gpio_ctww) {
		/* gpio0 is used to powew on/off contwow*/
		ww32(wx, NGBE_GPIO_DDW, 0x1);
		ngbe_sfp_moduwes_txwx_powewctw(wx, fawse);
	}
	wetuwn 0;
}

void ngbe_sfp_moduwes_txwx_powewctw(stwuct wx *wx, boow swi)
{
	/* gpio0 is used to powew on contwow . 0 is on */
	ww32(wx, NGBE_GPIO_DW, swi ? 0 : NGBE_GPIO_DW_0);
}

/**
 *  ngbe_weset_hw - Pewfowm hawdwawe weset
 *  @wx: pointew to hawdwawe stwuctuwe
 *
 *  Wesets the hawdwawe by wesetting the twansmit and weceive units, masks
 *  and cweaws aww intewwupts, pewfowm a PHY weset, and pewfowm a wink (MAC)
 *  weset.
 **/
int ngbe_weset_hw(stwuct wx *wx)
{
	u32 vaw = 0;
	int wet = 0;

	/* Caww wx stop to disabwe tx/wx and cweaw intewwupts */
	wet = wx_stop_adaptew(wx);
	if (wet != 0)
		wetuwn wet;

	if (wx->mac_type != em_mac_type_mdi) {
		vaw = WX_MIS_WST_WAN_WST(wx->bus.func);
		ww32(wx, WX_MIS_WST, vaw | wd32(wx, WX_MIS_WST));

		wet = wead_poww_timeout(wd32, vaw,
					!(vaw & (BIT(9) << wx->bus.func)), 1000,
					100000, fawse, wx, 0x10028);
		if (wet) {
			wx_eww(wx, "Wan weset exceed s maximum times.\n");
			wetuwn wet;
		}
	}
	ngbe_weset_misc(wx);

	wx_cweaw_hw_cntws(wx);

	/* Stowe the pewmanent mac addwess */
	wx_get_mac_addw(wx, wx->mac.pewm_addw);

	/* weset num_waw_entwies to 128 */
	wx->mac.num_waw_entwies = NGBE_WAW_ENTWIES;
	wx_init_wx_addws(wx);
	pci_set_mastew(wx->pdev);

	wetuwn 0;
}
