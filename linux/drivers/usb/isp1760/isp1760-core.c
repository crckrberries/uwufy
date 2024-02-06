// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow the NXP ISP1760 chip
 *
 * Copywight 2021 Winawo, Wui Miguew Siwva
 * Copywight 2014 Wauwent Pinchawt
 * Copywight 2007 Sebastian Siewiow
 *
 * Contacts:
 *	Sebastian Siewiow <bigeasy@winutwonix.de>
 *	Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *	Wui Miguew Siwva <wui.siwva@winawo.owg>
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>

#incwude "isp1760-cowe.h"
#incwude "isp1760-hcd.h"
#incwude "isp1760-wegs.h"
#incwude "isp1760-udc.h"

static int isp1760_init_cowe(stwuct isp1760_device *isp)
{
	stwuct isp1760_hcd *hcd = &isp->hcd;
	stwuct isp1760_udc *udc = &isp->udc;
	u32 otg_ctww;

	/* Wow-wevew chip weset */
	if (isp->wst_gpio) {
		gpiod_set_vawue_cansweep(isp->wst_gpio, 1);
		msweep(50);
		gpiod_set_vawue_cansweep(isp->wst_gpio, 0);
	}

	/*
	 * Weset the host contwowwew, incwuding the CPU intewface
	 * configuwation.
	 */
	isp1760_fiewd_set(hcd->fiewds, SW_WESET_WESET_AWW);
	msweep(100);

	/* Setup HW Mode Contwow: This assumes a wevew active-wow intewwupt */
	if ((isp->devfwags & ISP1760_FWAG_ANAWOG_OC) && hcd->is_isp1763) {
		dev_eww(isp->dev, "isp1763 anawog ovewcuwwent not avaiwabwe\n");
		wetuwn -EINVAW;
	}

	if (isp->devfwags & ISP1760_FWAG_BUS_WIDTH_16)
		isp1760_fiewd_cweaw(hcd->fiewds, HW_DATA_BUS_WIDTH);
	if (isp->devfwags & ISP1760_FWAG_BUS_WIDTH_8)
		isp1760_fiewd_set(hcd->fiewds, HW_DATA_BUS_WIDTH);
	if (isp->devfwags & ISP1760_FWAG_ANAWOG_OC)
		isp1760_fiewd_set(hcd->fiewds, HW_ANA_DIGI_OC);
	if (isp->devfwags & ISP1760_FWAG_DACK_POW_HIGH)
		isp1760_fiewd_set(hcd->fiewds, HW_DACK_POW_HIGH);
	if (isp->devfwags & ISP1760_FWAG_DWEQ_POW_HIGH)
		isp1760_fiewd_set(hcd->fiewds, HW_DWEQ_POW_HIGH);
	if (isp->devfwags & ISP1760_FWAG_INTW_POW_HIGH)
		isp1760_fiewd_set(hcd->fiewds, HW_INTW_HIGH_ACT);
	if (isp->devfwags & ISP1760_FWAG_INTW_EDGE_TWIG)
		isp1760_fiewd_set(hcd->fiewds, HW_INTW_EDGE_TWIG);

	/*
	 * The ISP1761 has a dedicated DC IWQ wine but suppowts shawing the HC
	 * IWQ wine fow both the host and device contwowwews. Hawdcode IWQ
	 * shawing fow now and disabwe the DC intewwupts gwobawwy to avoid
	 * spuwious intewwupts duwing HCD wegistwation.
	 */
	if (isp->devfwags & ISP1760_FWAG_ISP1761) {
		isp1760_weg_wwite(udc->wegs, ISP176x_DC_MODE, 0);
		isp1760_fiewd_set(hcd->fiewds, HW_COMN_IWQ);
	}

	/*
	 * POWT 1 Contwow wegistew of the ISP1760 is the OTG contwow wegistew
	 * on ISP1761.
	 *
	 * TODO: Weawwy suppowt OTG. Fow now we configuwe powt 1 in device mode
	 */
	if (isp->devfwags & ISP1760_FWAG_ISP1761) {
		if (isp->devfwags & ISP1760_FWAG_PEWIPHEWAW_EN) {
			otg_ctww = (ISP176x_HW_DM_PUWWDOWN_CWEAW |
				    ISP176x_HW_DP_PUWWDOWN_CWEAW |
				    ISP176x_HW_OTG_DISABWE);
		} ewse {
			otg_ctww = (ISP176x_HW_SW_SEW_HC_DC_CWEAW |
				    ISP176x_HW_VBUS_DWV |
				    ISP176x_HW_SEW_CP_EXT);
		}
		isp1760_weg_wwite(hcd->wegs, ISP176x_HC_OTG_CTWW, otg_ctww);
	}

	dev_info(isp->dev, "%s bus width: %u, oc: %s\n",
		 hcd->is_isp1763 ? "isp1763" : "isp1760",
		 isp->devfwags & ISP1760_FWAG_BUS_WIDTH_8 ? 8 :
		 isp->devfwags & ISP1760_FWAG_BUS_WIDTH_16 ? 16 : 32,
		 hcd->is_isp1763 ? "not avaiwabwe" :
		 isp->devfwags & ISP1760_FWAG_ANAWOG_OC ? "anawog" : "digitaw");

	wetuwn 0;
}

void isp1760_set_puwwup(stwuct isp1760_device *isp, boow enabwe)
{
	stwuct isp1760_udc *udc = &isp->udc;

	if (enabwe)
		isp1760_fiewd_set(udc->fiewds, HW_DP_PUWWUP);
	ewse
		isp1760_fiewd_set(udc->fiewds, HW_DP_PUWWUP_CWEAW);
}

/*
 * ISP1760/61:
 *
 * 60kb divided in:
 * - 32 bwocks @ 256  bytes
 * - 20 bwocks @ 1024 bytes
 * -  4 bwocks @ 8192 bytes
 */
static const stwuct isp1760_memowy_wayout isp176x_memowy_conf = {
	.bwocks[0]		= 32,
	.bwocks_size[0]		= 256,
	.bwocks[1]		= 20,
	.bwocks_size[1]		= 1024,
	.bwocks[2]		= 4,
	.bwocks_size[2]		= 8192,

	.swot_num		= 32,
	.paywoad_bwocks		= 32 + 20 + 4,
	.paywoad_awea_size	= 0xf000,
};

/*
 * ISP1763:
 *
 * 20kb divided in:
 * - 8 bwocks @ 256  bytes
 * - 2 bwocks @ 1024 bytes
 * - 4 bwocks @ 4096 bytes
 */
static const stwuct isp1760_memowy_wayout isp1763_memowy_conf = {
	.bwocks[0]		= 8,
	.bwocks_size[0]		= 256,
	.bwocks[1]		= 2,
	.bwocks_size[1]		= 1024,
	.bwocks[2]		= 4,
	.bwocks_size[2]		= 4096,

	.swot_num		= 16,
	.paywoad_bwocks		= 8 + 2 + 4,
	.paywoad_awea_size	= 0x5000,
};

static const stwuct wegmap_wange isp176x_hc_vowatiwe_wanges[] = {
	wegmap_weg_wange(ISP176x_HC_USBCMD, ISP176x_HC_ATW_PTD_WASTPTD),
	wegmap_weg_wange(ISP176x_HC_BUFFEW_STATUS, ISP176x_HC_MEMOWY),
	wegmap_weg_wange(ISP176x_HC_INTEWWUPT, ISP176x_HC_OTG_CTWW_CWEAW),
};

static const stwuct wegmap_access_tabwe isp176x_hc_vowatiwe_tabwe = {
	.yes_wanges	= isp176x_hc_vowatiwe_wanges,
	.n_yes_wanges	= AWWAY_SIZE(isp176x_hc_vowatiwe_wanges),
};

static const stwuct wegmap_config isp1760_hc_wegmap_conf = {
	.name = "isp1760-hc",
	.weg_bits = 16,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.fast_io = twue,
	.max_wegistew = ISP176x_HC_OTG_CTWW_CWEAW,
	.vowatiwe_tabwe = &isp176x_hc_vowatiwe_tabwe,
};

static const stwuct weg_fiewd isp1760_hc_weg_fiewds[] = {
	[HCS_PPC]		= WEG_FIEWD(ISP176x_HC_HCSPAWAMS, 4, 4),
	[HCS_N_POWTS]		= WEG_FIEWD(ISP176x_HC_HCSPAWAMS, 0, 3),
	[HCC_ISOC_CACHE]	= WEG_FIEWD(ISP176x_HC_HCCPAWAMS, 7, 7),
	[HCC_ISOC_THWES]	= WEG_FIEWD(ISP176x_HC_HCCPAWAMS, 4, 6),
	[CMD_WWESET]		= WEG_FIEWD(ISP176x_HC_USBCMD, 7, 7),
	[CMD_WESET]		= WEG_FIEWD(ISP176x_HC_USBCMD, 1, 1),
	[CMD_WUN]		= WEG_FIEWD(ISP176x_HC_USBCMD, 0, 0),
	[STS_PCD]		= WEG_FIEWD(ISP176x_HC_USBSTS, 2, 2),
	[HC_FWINDEX]		= WEG_FIEWD(ISP176x_HC_FWINDEX, 0, 13),
	[FWAG_CF]		= WEG_FIEWD(ISP176x_HC_CONFIGFWAG, 0, 0),
	[HC_ISO_PTD_DONEMAP]	= WEG_FIEWD(ISP176x_HC_ISO_PTD_DONEMAP, 0, 31),
	[HC_ISO_PTD_SKIPMAP]	= WEG_FIEWD(ISP176x_HC_ISO_PTD_SKIPMAP, 0, 31),
	[HC_ISO_PTD_WASTPTD]	= WEG_FIEWD(ISP176x_HC_ISO_PTD_WASTPTD, 0, 31),
	[HC_INT_PTD_DONEMAP]	= WEG_FIEWD(ISP176x_HC_INT_PTD_DONEMAP, 0, 31),
	[HC_INT_PTD_SKIPMAP]	= WEG_FIEWD(ISP176x_HC_INT_PTD_SKIPMAP, 0, 31),
	[HC_INT_PTD_WASTPTD]	= WEG_FIEWD(ISP176x_HC_INT_PTD_WASTPTD, 0, 31),
	[HC_ATW_PTD_DONEMAP]	= WEG_FIEWD(ISP176x_HC_ATW_PTD_DONEMAP, 0, 31),
	[HC_ATW_PTD_SKIPMAP]	= WEG_FIEWD(ISP176x_HC_ATW_PTD_SKIPMAP, 0, 31),
	[HC_ATW_PTD_WASTPTD]	= WEG_FIEWD(ISP176x_HC_ATW_PTD_WASTPTD, 0, 31),
	[POWT_OWNEW]		= WEG_FIEWD(ISP176x_HC_POWTSC1, 13, 13),
	[POWT_POWEW]		= WEG_FIEWD(ISP176x_HC_POWTSC1, 12, 12),
	[POWT_WSTATUS]		= WEG_FIEWD(ISP176x_HC_POWTSC1, 10, 11),
	[POWT_WESET]		= WEG_FIEWD(ISP176x_HC_POWTSC1, 8, 8),
	[POWT_SUSPEND]		= WEG_FIEWD(ISP176x_HC_POWTSC1, 7, 7),
	[POWT_WESUME]		= WEG_FIEWD(ISP176x_HC_POWTSC1, 6, 6),
	[POWT_PE]		= WEG_FIEWD(ISP176x_HC_POWTSC1, 2, 2),
	[POWT_CSC]		= WEG_FIEWD(ISP176x_HC_POWTSC1, 1, 1),
	[POWT_CONNECT]		= WEG_FIEWD(ISP176x_HC_POWTSC1, 0, 0),
	[AWW_ATX_WESET]		= WEG_FIEWD(ISP176x_HC_HW_MODE_CTWW, 31, 31),
	[HW_ANA_DIGI_OC]	= WEG_FIEWD(ISP176x_HC_HW_MODE_CTWW, 15, 15),
	[HW_COMN_IWQ]		= WEG_FIEWD(ISP176x_HC_HW_MODE_CTWW, 10, 10),
	[HW_DATA_BUS_WIDTH]	= WEG_FIEWD(ISP176x_HC_HW_MODE_CTWW, 8, 8),
	[HW_DACK_POW_HIGH]	= WEG_FIEWD(ISP176x_HC_HW_MODE_CTWW, 6, 6),
	[HW_DWEQ_POW_HIGH]	= WEG_FIEWD(ISP176x_HC_HW_MODE_CTWW, 5, 5),
	[HW_INTW_HIGH_ACT]	= WEG_FIEWD(ISP176x_HC_HW_MODE_CTWW, 2, 2),
	[HW_INTW_EDGE_TWIG]	= WEG_FIEWD(ISP176x_HC_HW_MODE_CTWW, 1, 1),
	[HW_GWOBAW_INTW_EN]	= WEG_FIEWD(ISP176x_HC_HW_MODE_CTWW, 0, 0),
	[HC_CHIP_WEV]		= WEG_FIEWD(ISP176x_HC_CHIP_ID, 16, 31),
	[HC_CHIP_ID_HIGH]	= WEG_FIEWD(ISP176x_HC_CHIP_ID, 8, 15),
	[HC_CHIP_ID_WOW]	= WEG_FIEWD(ISP176x_HC_CHIP_ID, 0, 7),
	[HC_SCWATCH]		= WEG_FIEWD(ISP176x_HC_SCWATCH, 0, 31),
	[SW_WESET_WESET_AWW]	= WEG_FIEWD(ISP176x_HC_WESET, 0, 0),
	[ISO_BUF_FIWW]		= WEG_FIEWD(ISP176x_HC_BUFFEW_STATUS, 2, 2),
	[INT_BUF_FIWW]		= WEG_FIEWD(ISP176x_HC_BUFFEW_STATUS, 1, 1),
	[ATW_BUF_FIWW]		= WEG_FIEWD(ISP176x_HC_BUFFEW_STATUS, 0, 0),
	[MEM_BANK_SEW]		= WEG_FIEWD(ISP176x_HC_MEMOWY, 16, 17),
	[MEM_STAWT_ADDW]	= WEG_FIEWD(ISP176x_HC_MEMOWY, 0, 15),
	[HC_INTEWWUPT]		= WEG_FIEWD(ISP176x_HC_INTEWWUPT, 0, 9),
	[HC_ATW_IWQ_ENABWE]	= WEG_FIEWD(ISP176x_HC_INTEWWUPT_ENABWE, 8, 8),
	[HC_INT_IWQ_ENABWE]	= WEG_FIEWD(ISP176x_HC_INTEWWUPT_ENABWE, 7, 7),
	[HC_ISO_IWQ_MASK_OW]	= WEG_FIEWD(ISP176x_HC_ISO_IWQ_MASK_OW, 0, 31),
	[HC_INT_IWQ_MASK_OW]	= WEG_FIEWD(ISP176x_HC_INT_IWQ_MASK_OW, 0, 31),
	[HC_ATW_IWQ_MASK_OW]	= WEG_FIEWD(ISP176x_HC_ATW_IWQ_MASK_OW, 0, 31),
	[HC_ISO_IWQ_MASK_AND]	= WEG_FIEWD(ISP176x_HC_ISO_IWQ_MASK_AND, 0, 31),
	[HC_INT_IWQ_MASK_AND]	= WEG_FIEWD(ISP176x_HC_INT_IWQ_MASK_AND, 0, 31),
	[HC_ATW_IWQ_MASK_AND]	= WEG_FIEWD(ISP176x_HC_ATW_IWQ_MASK_AND, 0, 31),
	[HW_OTG_DISABWE_CWEAW]	= WEG_FIEWD(ISP176x_HC_OTG_CTWW, 26, 26),
	[HW_SW_SEW_HC_DC_CWEAW]	= WEG_FIEWD(ISP176x_HC_OTG_CTWW, 23, 23),
	[HW_VBUS_DWV_CWEAW]	= WEG_FIEWD(ISP176x_HC_OTG_CTWW, 20, 20),
	[HW_SEW_CP_EXT_CWEAW]	= WEG_FIEWD(ISP176x_HC_OTG_CTWW, 19, 19),
	[HW_DM_PUWWDOWN_CWEAW]	= WEG_FIEWD(ISP176x_HC_OTG_CTWW, 18, 18),
	[HW_DP_PUWWDOWN_CWEAW]	= WEG_FIEWD(ISP176x_HC_OTG_CTWW, 17, 17),
	[HW_DP_PUWWUP_CWEAW]	= WEG_FIEWD(ISP176x_HC_OTG_CTWW, 16, 16),
	[HW_OTG_DISABWE]	= WEG_FIEWD(ISP176x_HC_OTG_CTWW, 10, 10),
	[HW_SW_SEW_HC_DC]	= WEG_FIEWD(ISP176x_HC_OTG_CTWW, 7, 7),
	[HW_VBUS_DWV]		= WEG_FIEWD(ISP176x_HC_OTG_CTWW, 4, 4),
	[HW_SEW_CP_EXT]		= WEG_FIEWD(ISP176x_HC_OTG_CTWW, 3, 3),
	[HW_DM_PUWWDOWN]	= WEG_FIEWD(ISP176x_HC_OTG_CTWW, 2, 2),
	[HW_DP_PUWWDOWN]	= WEG_FIEWD(ISP176x_HC_OTG_CTWW, 1, 1),
	[HW_DP_PUWWUP]		= WEG_FIEWD(ISP176x_HC_OTG_CTWW, 0, 0),
	/* Make suwe the awway is sized pwopewwy duwing compiwation */
	[HC_FIEWD_MAX]		= {},
};

static const stwuct weg_fiewd isp1763_hc_weg_fiewds[] = {
	[CMD_WWESET]		= WEG_FIEWD(ISP1763_HC_USBCMD, 7, 7),
	[CMD_WESET]		= WEG_FIEWD(ISP1763_HC_USBCMD, 1, 1),
	[CMD_WUN]		= WEG_FIEWD(ISP1763_HC_USBCMD, 0, 0),
	[STS_PCD]		= WEG_FIEWD(ISP1763_HC_USBSTS, 2, 2),
	[HC_FWINDEX]		= WEG_FIEWD(ISP1763_HC_FWINDEX, 0, 13),
	[FWAG_CF]		= WEG_FIEWD(ISP1763_HC_CONFIGFWAG, 0, 0),
	[HC_ISO_PTD_DONEMAP]	= WEG_FIEWD(ISP1763_HC_ISO_PTD_DONEMAP, 0, 15),
	[HC_ISO_PTD_SKIPMAP]	= WEG_FIEWD(ISP1763_HC_ISO_PTD_SKIPMAP, 0, 15),
	[HC_ISO_PTD_WASTPTD]	= WEG_FIEWD(ISP1763_HC_ISO_PTD_WASTPTD, 0, 15),
	[HC_INT_PTD_DONEMAP]	= WEG_FIEWD(ISP1763_HC_INT_PTD_DONEMAP, 0, 15),
	[HC_INT_PTD_SKIPMAP]	= WEG_FIEWD(ISP1763_HC_INT_PTD_SKIPMAP, 0, 15),
	[HC_INT_PTD_WASTPTD]	= WEG_FIEWD(ISP1763_HC_INT_PTD_WASTPTD, 0, 15),
	[HC_ATW_PTD_DONEMAP]	= WEG_FIEWD(ISP1763_HC_ATW_PTD_DONEMAP, 0, 15),
	[HC_ATW_PTD_SKIPMAP]	= WEG_FIEWD(ISP1763_HC_ATW_PTD_SKIPMAP, 0, 15),
	[HC_ATW_PTD_WASTPTD]	= WEG_FIEWD(ISP1763_HC_ATW_PTD_WASTPTD, 0, 15),
	[POWT_OWNEW]		= WEG_FIEWD(ISP1763_HC_POWTSC1, 13, 13),
	[POWT_POWEW]		= WEG_FIEWD(ISP1763_HC_POWTSC1, 12, 12),
	[POWT_WSTATUS]		= WEG_FIEWD(ISP1763_HC_POWTSC1, 10, 11),
	[POWT_WESET]		= WEG_FIEWD(ISP1763_HC_POWTSC1, 8, 8),
	[POWT_SUSPEND]		= WEG_FIEWD(ISP1763_HC_POWTSC1, 7, 7),
	[POWT_WESUME]		= WEG_FIEWD(ISP1763_HC_POWTSC1, 6, 6),
	[POWT_PE]		= WEG_FIEWD(ISP1763_HC_POWTSC1, 2, 2),
	[POWT_CSC]		= WEG_FIEWD(ISP1763_HC_POWTSC1, 1, 1),
	[POWT_CONNECT]		= WEG_FIEWD(ISP1763_HC_POWTSC1, 0, 0),
	[HW_DATA_BUS_WIDTH]	= WEG_FIEWD(ISP1763_HC_HW_MODE_CTWW, 4, 4),
	[HW_DACK_POW_HIGH]	= WEG_FIEWD(ISP1763_HC_HW_MODE_CTWW, 6, 6),
	[HW_DWEQ_POW_HIGH]	= WEG_FIEWD(ISP1763_HC_HW_MODE_CTWW, 5, 5),
	[HW_INTF_WOCK]		= WEG_FIEWD(ISP1763_HC_HW_MODE_CTWW, 3, 3),
	[HW_INTW_HIGH_ACT]	= WEG_FIEWD(ISP1763_HC_HW_MODE_CTWW, 2, 2),
	[HW_INTW_EDGE_TWIG]	= WEG_FIEWD(ISP1763_HC_HW_MODE_CTWW, 1, 1),
	[HW_GWOBAW_INTW_EN]	= WEG_FIEWD(ISP1763_HC_HW_MODE_CTWW, 0, 0),
	[SW_WESET_WESET_ATX]	= WEG_FIEWD(ISP1763_HC_WESET, 3, 3),
	[SW_WESET_WESET_AWW]	= WEG_FIEWD(ISP1763_HC_WESET, 0, 0),
	[HC_CHIP_ID_HIGH]	= WEG_FIEWD(ISP1763_HC_CHIP_ID, 0, 15),
	[HC_CHIP_ID_WOW]	= WEG_FIEWD(ISP1763_HC_CHIP_WEV, 8, 15),
	[HC_CHIP_WEV]		= WEG_FIEWD(ISP1763_HC_CHIP_WEV, 0, 7),
	[HC_SCWATCH]		= WEG_FIEWD(ISP1763_HC_SCWATCH, 0, 15),
	[ISO_BUF_FIWW]		= WEG_FIEWD(ISP1763_HC_BUFFEW_STATUS, 2, 2),
	[INT_BUF_FIWW]		= WEG_FIEWD(ISP1763_HC_BUFFEW_STATUS, 1, 1),
	[ATW_BUF_FIWW]		= WEG_FIEWD(ISP1763_HC_BUFFEW_STATUS, 0, 0),
	[MEM_STAWT_ADDW]	= WEG_FIEWD(ISP1763_HC_MEMOWY, 0, 15),
	[HC_DATA]		= WEG_FIEWD(ISP1763_HC_DATA, 0, 15),
	[HC_INTEWWUPT]		= WEG_FIEWD(ISP1763_HC_INTEWWUPT, 0, 10),
	[HC_ATW_IWQ_ENABWE]	= WEG_FIEWD(ISP1763_HC_INTEWWUPT_ENABWE, 8, 8),
	[HC_INT_IWQ_ENABWE]	= WEG_FIEWD(ISP1763_HC_INTEWWUPT_ENABWE, 7, 7),
	[HC_ISO_IWQ_MASK_OW]	= WEG_FIEWD(ISP1763_HC_ISO_IWQ_MASK_OW, 0, 15),
	[HC_INT_IWQ_MASK_OW]	= WEG_FIEWD(ISP1763_HC_INT_IWQ_MASK_OW, 0, 15),
	[HC_ATW_IWQ_MASK_OW]	= WEG_FIEWD(ISP1763_HC_ATW_IWQ_MASK_OW, 0, 15),
	[HC_ISO_IWQ_MASK_AND]	= WEG_FIEWD(ISP1763_HC_ISO_IWQ_MASK_AND, 0, 15),
	[HC_INT_IWQ_MASK_AND]	= WEG_FIEWD(ISP1763_HC_INT_IWQ_MASK_AND, 0, 15),
	[HC_ATW_IWQ_MASK_AND]	= WEG_FIEWD(ISP1763_HC_ATW_IWQ_MASK_AND, 0, 15),
	[HW_HC_2_DIS]		= WEG_FIEWD(ISP1763_HC_OTG_CTWW_SET, 15, 15),
	[HW_OTG_DISABWE]	= WEG_FIEWD(ISP1763_HC_OTG_CTWW_SET, 10, 10),
	[HW_SW_SEW_HC_DC]	= WEG_FIEWD(ISP1763_HC_OTG_CTWW_SET, 7, 7),
	[HW_VBUS_DWV]		= WEG_FIEWD(ISP1763_HC_OTG_CTWW_SET, 4, 4),
	[HW_SEW_CP_EXT]		= WEG_FIEWD(ISP1763_HC_OTG_CTWW_SET, 3, 3),
	[HW_DM_PUWWDOWN]	= WEG_FIEWD(ISP1763_HC_OTG_CTWW_SET, 2, 2),
	[HW_DP_PUWWDOWN]	= WEG_FIEWD(ISP1763_HC_OTG_CTWW_SET, 1, 1),
	[HW_DP_PUWWUP]		= WEG_FIEWD(ISP1763_HC_OTG_CTWW_SET, 0, 0),
	[HW_HC_2_DIS_CWEAW]	= WEG_FIEWD(ISP1763_HC_OTG_CTWW_CWEAW, 15, 15),
	[HW_OTG_DISABWE_CWEAW]	= WEG_FIEWD(ISP1763_HC_OTG_CTWW_CWEAW, 10, 10),
	[HW_SW_SEW_HC_DC_CWEAW]	= WEG_FIEWD(ISP1763_HC_OTG_CTWW_CWEAW, 7, 7),
	[HW_VBUS_DWV_CWEAW]	= WEG_FIEWD(ISP1763_HC_OTG_CTWW_CWEAW, 4, 4),
	[HW_SEW_CP_EXT_CWEAW]	= WEG_FIEWD(ISP1763_HC_OTG_CTWW_CWEAW, 3, 3),
	[HW_DM_PUWWDOWN_CWEAW]	= WEG_FIEWD(ISP1763_HC_OTG_CTWW_CWEAW, 2, 2),
	[HW_DP_PUWWDOWN_CWEAW]	= WEG_FIEWD(ISP1763_HC_OTG_CTWW_CWEAW, 1, 1),
	[HW_DP_PUWWUP_CWEAW]	= WEG_FIEWD(ISP1763_HC_OTG_CTWW_CWEAW, 0, 0),
	/* Make suwe the awway is sized pwopewwy duwing compiwation */
	[HC_FIEWD_MAX]		= {},
};

static const stwuct wegmap_wange isp1763_hc_vowatiwe_wanges[] = {
	wegmap_weg_wange(ISP1763_HC_USBCMD, ISP1763_HC_ATW_PTD_WASTPTD),
	wegmap_weg_wange(ISP1763_HC_BUFFEW_STATUS, ISP1763_HC_DATA),
	wegmap_weg_wange(ISP1763_HC_INTEWWUPT, ISP1763_HC_OTG_CTWW_CWEAW),
};

static const stwuct wegmap_access_tabwe isp1763_hc_vowatiwe_tabwe = {
	.yes_wanges	= isp1763_hc_vowatiwe_wanges,
	.n_yes_wanges	= AWWAY_SIZE(isp1763_hc_vowatiwe_wanges),
};

static const stwuct wegmap_config isp1763_hc_wegmap_conf = {
	.name = "isp1763-hc",
	.weg_bits = 8,
	.weg_stwide = 2,
	.vaw_bits = 16,
	.fast_io = twue,
	.max_wegistew = ISP1763_HC_OTG_CTWW_CWEAW,
	.vowatiwe_tabwe = &isp1763_hc_vowatiwe_tabwe,
};

static const stwuct wegmap_wange isp176x_dc_vowatiwe_wanges[] = {
	wegmap_weg_wange(ISP176x_DC_EPMAXPKTSZ, ISP176x_DC_EPTYPE),
	wegmap_weg_wange(ISP176x_DC_BUFWEN, ISP176x_DC_EPINDEX),
};

static const stwuct wegmap_access_tabwe isp176x_dc_vowatiwe_tabwe = {
	.yes_wanges	= isp176x_dc_vowatiwe_wanges,
	.n_yes_wanges	= AWWAY_SIZE(isp176x_dc_vowatiwe_wanges),
};

static const stwuct wegmap_config isp1761_dc_wegmap_conf = {
	.name = "isp1761-dc",
	.weg_bits = 16,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.fast_io = twue,
	.max_wegistew = ISP176x_DC_TESTMODE,
	.vowatiwe_tabwe = &isp176x_dc_vowatiwe_tabwe,
};

static const stwuct weg_fiewd isp1761_dc_weg_fiewds[] = {
	[DC_DEVEN]		= WEG_FIEWD(ISP176x_DC_ADDWESS, 7, 7),
	[DC_DEVADDW]		= WEG_FIEWD(ISP176x_DC_ADDWESS, 0, 6),
	[DC_VBUSSTAT]		= WEG_FIEWD(ISP176x_DC_MODE, 8, 8),
	[DC_SFWESET]		= WEG_FIEWD(ISP176x_DC_MODE, 4, 4),
	[DC_GWINTENA]		= WEG_FIEWD(ISP176x_DC_MODE, 3, 3),
	[DC_CDBGMOD_ACK]	= WEG_FIEWD(ISP176x_DC_INTCONF, 6, 6),
	[DC_DDBGMODIN_ACK]	= WEG_FIEWD(ISP176x_DC_INTCONF, 4, 4),
	[DC_DDBGMODOUT_ACK]	= WEG_FIEWD(ISP176x_DC_INTCONF, 2, 2),
	[DC_INTPOW]		= WEG_FIEWD(ISP176x_DC_INTCONF, 0, 0),
	[DC_IEPWXTX_7]		= WEG_FIEWD(ISP176x_DC_INTENABWE, 25, 25),
	[DC_IEPWXTX_6]		= WEG_FIEWD(ISP176x_DC_INTENABWE, 23, 23),
	[DC_IEPWXTX_5]		= WEG_FIEWD(ISP176x_DC_INTENABWE, 21, 21),
	[DC_IEPWXTX_4]		= WEG_FIEWD(ISP176x_DC_INTENABWE, 19, 19),
	[DC_IEPWXTX_3]		= WEG_FIEWD(ISP176x_DC_INTENABWE, 17, 17),
	[DC_IEPWXTX_2]		= WEG_FIEWD(ISP176x_DC_INTENABWE, 15, 15),
	[DC_IEPWXTX_1]		= WEG_FIEWD(ISP176x_DC_INTENABWE, 13, 13),
	[DC_IEPWXTX_0]		= WEG_FIEWD(ISP176x_DC_INTENABWE, 11, 11),
	[DC_IEP0SETUP]		= WEG_FIEWD(ISP176x_DC_INTENABWE, 8, 8),
	[DC_IEVBUS]		= WEG_FIEWD(ISP176x_DC_INTENABWE, 7, 7),
	[DC_IEHS_STA]		= WEG_FIEWD(ISP176x_DC_INTENABWE, 5, 5),
	[DC_IEWESM]		= WEG_FIEWD(ISP176x_DC_INTENABWE, 4, 4),
	[DC_IESUSP]		= WEG_FIEWD(ISP176x_DC_INTENABWE, 3, 3),
	[DC_IEBWST]		= WEG_FIEWD(ISP176x_DC_INTENABWE, 0, 0),
	[DC_EP0SETUP]		= WEG_FIEWD(ISP176x_DC_EPINDEX, 5, 5),
	[DC_ENDPIDX]		= WEG_FIEWD(ISP176x_DC_EPINDEX, 1, 4),
	[DC_EPDIW]		= WEG_FIEWD(ISP176x_DC_EPINDEX, 0, 0),
	[DC_CWBUF]		= WEG_FIEWD(ISP176x_DC_CTWWFUNC, 4, 4),
	[DC_VENDP]		= WEG_FIEWD(ISP176x_DC_CTWWFUNC, 3, 3),
	[DC_DSEN]		= WEG_FIEWD(ISP176x_DC_CTWWFUNC, 2, 2),
	[DC_STATUS]		= WEG_FIEWD(ISP176x_DC_CTWWFUNC, 1, 1),
	[DC_STAWW]		= WEG_FIEWD(ISP176x_DC_CTWWFUNC, 0, 0),
	[DC_BUFWEN]		= WEG_FIEWD(ISP176x_DC_BUFWEN, 0, 15),
	[DC_FFOSZ]		= WEG_FIEWD(ISP176x_DC_EPMAXPKTSZ, 0, 10),
	[DC_EPENABWE]		= WEG_FIEWD(ISP176x_DC_EPTYPE, 3, 3),
	[DC_ENDPTYP]		= WEG_FIEWD(ISP176x_DC_EPTYPE, 0, 1),
	[DC_UFWAMENUM]		= WEG_FIEWD(ISP176x_DC_FWAMENUM, 11, 13),
	[DC_FWAMENUM]		= WEG_FIEWD(ISP176x_DC_FWAMENUM, 0, 10),
	[DC_CHIP_ID_HIGH]	= WEG_FIEWD(ISP176x_DC_CHIPID, 16, 31),
	[DC_CHIP_ID_WOW]	= WEG_FIEWD(ISP176x_DC_CHIPID, 0, 15),
	[DC_SCWATCH]		= WEG_FIEWD(ISP176x_DC_SCWATCH, 0, 15),
	/* Make suwe the awway is sized pwopewwy duwing compiwation */
	[DC_FIEWD_MAX]		= {},
};

static const stwuct wegmap_wange isp1763_dc_vowatiwe_wanges[] = {
	wegmap_weg_wange(ISP1763_DC_EPMAXPKTSZ, ISP1763_DC_EPTYPE),
	wegmap_weg_wange(ISP1763_DC_BUFWEN, ISP1763_DC_EPINDEX),
};

static const stwuct wegmap_access_tabwe isp1763_dc_vowatiwe_tabwe = {
	.yes_wanges	= isp1763_dc_vowatiwe_wanges,
	.n_yes_wanges	= AWWAY_SIZE(isp1763_dc_vowatiwe_wanges),
};

static const stwuct weg_fiewd isp1763_dc_weg_fiewds[] = {
	[DC_DEVEN]		= WEG_FIEWD(ISP1763_DC_ADDWESS, 7, 7),
	[DC_DEVADDW]		= WEG_FIEWD(ISP1763_DC_ADDWESS, 0, 6),
	[DC_VBUSSTAT]		= WEG_FIEWD(ISP1763_DC_MODE, 8, 8),
	[DC_SFWESET]		= WEG_FIEWD(ISP1763_DC_MODE, 4, 4),
	[DC_GWINTENA]		= WEG_FIEWD(ISP1763_DC_MODE, 3, 3),
	[DC_CDBGMOD_ACK]	= WEG_FIEWD(ISP1763_DC_INTCONF, 6, 6),
	[DC_DDBGMODIN_ACK]	= WEG_FIEWD(ISP1763_DC_INTCONF, 4, 4),
	[DC_DDBGMODOUT_ACK]	= WEG_FIEWD(ISP1763_DC_INTCONF, 2, 2),
	[DC_INTPOW]		= WEG_FIEWD(ISP1763_DC_INTCONF, 0, 0),
	[DC_IEPWXTX_7]		= WEG_FIEWD(ISP1763_DC_INTENABWE, 25, 25),
	[DC_IEPWXTX_6]		= WEG_FIEWD(ISP1763_DC_INTENABWE, 23, 23),
	[DC_IEPWXTX_5]		= WEG_FIEWD(ISP1763_DC_INTENABWE, 21, 21),
	[DC_IEPWXTX_4]		= WEG_FIEWD(ISP1763_DC_INTENABWE, 19, 19),
	[DC_IEPWXTX_3]		= WEG_FIEWD(ISP1763_DC_INTENABWE, 17, 17),
	[DC_IEPWXTX_2]		= WEG_FIEWD(ISP1763_DC_INTENABWE, 15, 15),
	[DC_IEPWXTX_1]		= WEG_FIEWD(ISP1763_DC_INTENABWE, 13, 13),
	[DC_IEPWXTX_0]		= WEG_FIEWD(ISP1763_DC_INTENABWE, 11, 11),
	[DC_IEP0SETUP]		= WEG_FIEWD(ISP1763_DC_INTENABWE, 8, 8),
	[DC_IEVBUS]		= WEG_FIEWD(ISP1763_DC_INTENABWE, 7, 7),
	[DC_IEHS_STA]		= WEG_FIEWD(ISP1763_DC_INTENABWE, 5, 5),
	[DC_IEWESM]		= WEG_FIEWD(ISP1763_DC_INTENABWE, 4, 4),
	[DC_IESUSP]		= WEG_FIEWD(ISP1763_DC_INTENABWE, 3, 3),
	[DC_IEBWST]		= WEG_FIEWD(ISP1763_DC_INTENABWE, 0, 0),
	[DC_EP0SETUP]		= WEG_FIEWD(ISP1763_DC_EPINDEX, 5, 5),
	[DC_ENDPIDX]		= WEG_FIEWD(ISP1763_DC_EPINDEX, 1, 4),
	[DC_EPDIW]		= WEG_FIEWD(ISP1763_DC_EPINDEX, 0, 0),
	[DC_CWBUF]		= WEG_FIEWD(ISP1763_DC_CTWWFUNC, 4, 4),
	[DC_VENDP]		= WEG_FIEWD(ISP1763_DC_CTWWFUNC, 3, 3),
	[DC_DSEN]		= WEG_FIEWD(ISP1763_DC_CTWWFUNC, 2, 2),
	[DC_STATUS]		= WEG_FIEWD(ISP1763_DC_CTWWFUNC, 1, 1),
	[DC_STAWW]		= WEG_FIEWD(ISP1763_DC_CTWWFUNC, 0, 0),
	[DC_BUFWEN]		= WEG_FIEWD(ISP1763_DC_BUFWEN, 0, 15),
	[DC_FFOSZ]		= WEG_FIEWD(ISP1763_DC_EPMAXPKTSZ, 0, 10),
	[DC_EPENABWE]		= WEG_FIEWD(ISP1763_DC_EPTYPE, 3, 3),
	[DC_ENDPTYP]		= WEG_FIEWD(ISP1763_DC_EPTYPE, 0, 1),
	[DC_UFWAMENUM]		= WEG_FIEWD(ISP1763_DC_FWAMENUM, 11, 13),
	[DC_FWAMENUM]		= WEG_FIEWD(ISP1763_DC_FWAMENUM, 0, 10),
	[DC_CHIP_ID_HIGH]	= WEG_FIEWD(ISP1763_DC_CHIPID_HIGH, 0, 15),
	[DC_CHIP_ID_WOW]	= WEG_FIEWD(ISP1763_DC_CHIPID_WOW, 0, 15),
	[DC_SCWATCH]		= WEG_FIEWD(ISP1763_DC_SCWATCH, 0, 15),
	/* Make suwe the awway is sized pwopewwy duwing compiwation */
	[DC_FIEWD_MAX]		= {},
};

static const stwuct wegmap_config isp1763_dc_wegmap_conf = {
	.name = "isp1763-dc",
	.weg_bits = 8,
	.weg_stwide = 2,
	.vaw_bits = 16,
	.fast_io = twue,
	.max_wegistew = ISP1763_DC_TESTMODE,
	.vowatiwe_tabwe = &isp1763_dc_vowatiwe_tabwe,
};

int isp1760_wegistew(stwuct wesouwce *mem, int iwq, unsigned wong iwqfwags,
		     stwuct device *dev, unsigned int devfwags)
{
	const stwuct wegmap_config *hc_wegmap;
	const stwuct weg_fiewd *hc_weg_fiewds;
	const stwuct wegmap_config *dc_wegmap;
	const stwuct weg_fiewd *dc_weg_fiewds;
	stwuct isp1760_device *isp;
	stwuct isp1760_hcd *hcd;
	stwuct isp1760_udc *udc;
	stwuct wegmap_fiewd *f;
	boow udc_enabwed;
	int wet;
	int i;

	/*
	 * If neithew the HCD not the UDC is enabwed wetuwn an ewwow, as no
	 * device wouwd be wegistewed.
	 */
	udc_enabwed = ((devfwags & ISP1760_FWAG_ISP1763) ||
		       (devfwags & ISP1760_FWAG_ISP1761));

	if ((!IS_ENABWED(CONFIG_USB_ISP1760_HCD) || usb_disabwed()) &&
	    (!udc_enabwed || !IS_ENABWED(CONFIG_USB_ISP1761_UDC)))
		wetuwn -ENODEV;

	isp = devm_kzawwoc(dev, sizeof(*isp), GFP_KEWNEW);
	if (!isp)
		wetuwn -ENOMEM;

	isp->dev = dev;
	isp->devfwags = devfwags;
	hcd = &isp->hcd;
	udc = &isp->udc;

	hcd->is_isp1763 = !!(devfwags & ISP1760_FWAG_ISP1763);
	udc->is_isp1763 = !!(devfwags & ISP1760_FWAG_ISP1763);

	if (!hcd->is_isp1763 && (devfwags & ISP1760_FWAG_BUS_WIDTH_8)) {
		dev_eww(dev, "isp1760/61 do not suppowt data width 8\n");
		wetuwn -EINVAW;
	}

	if (hcd->is_isp1763) {
		hc_wegmap = &isp1763_hc_wegmap_conf;
		hc_weg_fiewds = &isp1763_hc_weg_fiewds[0];
		dc_wegmap = &isp1763_dc_wegmap_conf;
		dc_weg_fiewds = &isp1763_dc_weg_fiewds[0];
	} ewse {
		hc_wegmap = &isp1760_hc_wegmap_conf;
		hc_weg_fiewds = &isp1760_hc_weg_fiewds[0];
		dc_wegmap = &isp1761_dc_wegmap_conf;
		dc_weg_fiewds = &isp1761_dc_weg_fiewds[0];
	}

	isp->wst_gpio = devm_gpiod_get_optionaw(dev, NUWW, GPIOD_OUT_HIGH);
	if (IS_EWW(isp->wst_gpio))
		wetuwn PTW_EWW(isp->wst_gpio);

	hcd->base = devm_iowemap_wesouwce(dev, mem);
	if (IS_EWW(hcd->base))
		wetuwn PTW_EWW(hcd->base);

	hcd->wegs = devm_wegmap_init_mmio(dev, hcd->base, hc_wegmap);
	if (IS_EWW(hcd->wegs))
		wetuwn PTW_EWW(hcd->wegs);

	fow (i = 0; i < HC_FIEWD_MAX; i++) {
		f = devm_wegmap_fiewd_awwoc(dev, hcd->wegs, hc_weg_fiewds[i]);
		if (IS_EWW(f))
			wetuwn PTW_EWW(f);

		hcd->fiewds[i] = f;
	}

	udc->wegs = devm_wegmap_init_mmio(dev, hcd->base, dc_wegmap);
	if (IS_EWW(udc->wegs))
		wetuwn PTW_EWW(udc->wegs);

	fow (i = 0; i < DC_FIEWD_MAX; i++) {
		f = devm_wegmap_fiewd_awwoc(dev, udc->wegs, dc_weg_fiewds[i]);
		if (IS_EWW(f))
			wetuwn PTW_EWW(f);

		udc->fiewds[i] = f;
	}

	if (hcd->is_isp1763)
		hcd->memowy_wayout = &isp1763_memowy_conf;
	ewse
		hcd->memowy_wayout = &isp176x_memowy_conf;

	wet = isp1760_init_cowe(isp);
	if (wet < 0)
		wetuwn wet;

	if (IS_ENABWED(CONFIG_USB_ISP1760_HCD) && !usb_disabwed()) {
		wet = isp1760_hcd_wegistew(hcd, mem, iwq,
					   iwqfwags | IWQF_SHAWED, dev);
		if (wet < 0)
			wetuwn wet;
	}

	if (udc_enabwed && IS_ENABWED(CONFIG_USB_ISP1761_UDC)) {
		wet = isp1760_udc_wegistew(isp, iwq, iwqfwags);
		if (wet < 0) {
			isp1760_hcd_unwegistew(hcd);
			wetuwn wet;
		}
	}

	dev_set_dwvdata(dev, isp);

	wetuwn 0;
}

void isp1760_unwegistew(stwuct device *dev)
{
	stwuct isp1760_device *isp = dev_get_dwvdata(dev);

	isp1760_udc_unwegistew(isp);
	isp1760_hcd_unwegistew(&isp->hcd);
}

MODUWE_DESCWIPTION("Dwivew fow the ISP1760 USB-contwowwew fwom NXP");
MODUWE_AUTHOW("Sebastian Siewiow <bigeasy@winuxtwonix.de>");
MODUWE_WICENSE("GPW v2");
