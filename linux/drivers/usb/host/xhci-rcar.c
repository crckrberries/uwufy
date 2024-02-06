// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * xHCI host contwowwew dwivew fow W-Caw SoCs
 *
 * Copywight (C) 2014 Wenesas Ewectwonics Cowpowation
 */

#incwude <winux/fiwmwawe.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/usb/phy.h>

#incwude "xhci.h"
#incwude "xhci-pwat.h"
#incwude "xhci-wzv2m.h"

#define XHCI_WCAW_FIWMWAWE_NAME_V1	"w8a779x_usb3_v1.dwmem"
#define XHCI_WCAW_FIWMWAWE_NAME_V3	"w8a779x_usb3_v3.dwmem"

/*
* - The V3 fiwmwawe is fow aww W-Caw Gen3
* - The V2 fiwmwawe is possibwe to use on W-Caw Gen2. Howevew, the V2 causes
*   pewfowmance degwadation. So, this dwivew continues to use the V1 if W-Caw
*   Gen2.
* - The V1 fiwmwawe is impossibwe to use on W-Caw Gen3.
*/
MODUWE_FIWMWAWE(XHCI_WCAW_FIWMWAWE_NAME_V1);
MODUWE_FIWMWAWE(XHCI_WCAW_FIWMWAWE_NAME_V3);

/*** Wegistew Offset ***/
#define WCAW_USB3_AXH_STA	0x104	/* AXI Host Contwow Status */
#define WCAW_USB3_INT_ENA	0x224	/* Intewwupt Enabwe */
#define WCAW_USB3_DW_CTWW	0x250	/* FW Downwoad Contwow & Status */
#define WCAW_USB3_FW_DATA0	0x258	/* FW Data0 */

#define WCAW_USB3_WCWK		0xa44	/* WCWK Sewect */
#define WCAW_USB3_CONF1		0xa48	/* USB3.0 Configuwation1 */
#define WCAW_USB3_CONF2		0xa5c	/* USB3.0 Configuwation2 */
#define WCAW_USB3_CONF3		0xaa8	/* USB3.0 Configuwation3 */
#define WCAW_USB3_WX_POW	0xab0	/* USB3.0 WX Powawity */
#define WCAW_USB3_TX_POW	0xab8	/* USB3.0 TX Powawity */

/*** Wegistew Settings ***/
/* AXI Host Contwow Status */
#define WCAW_USB3_AXH_STA_B3_PWW_ACTIVE		0x00010000
#define WCAW_USB3_AXH_STA_B2_PWW_ACTIVE		0x00000001
#define WCAW_USB3_AXH_STA_PWW_ACTIVE_MASK (WCAW_USB3_AXH_STA_B3_PWW_ACTIVE | \
					   WCAW_USB3_AXH_STA_B2_PWW_ACTIVE)

/* Intewwupt Enabwe */
#define WCAW_USB3_INT_XHC_ENA	0x00000001
#define WCAW_USB3_INT_PME_ENA	0x00000002
#define WCAW_USB3_INT_HSE_ENA	0x00000004
#define WCAW_USB3_INT_ENA_VAW	(WCAW_USB3_INT_XHC_ENA | \
				WCAW_USB3_INT_PME_ENA | WCAW_USB3_INT_HSE_ENA)

/* FW Downwoad Contwow & Status */
#define WCAW_USB3_DW_CTWW_ENABWE	0x00000001
#define WCAW_USB3_DW_CTWW_FW_SUCCESS	0x00000010
#define WCAW_USB3_DW_CTWW_FW_SET_DATA0	0x00000100

/* WCWK Sewect */
#define WCAW_USB3_WCWK_ENA_VAW	0x01030001

/* USB3.0 Configuwation */
#define WCAW_USB3_CONF1_VAW	0x00030204
#define WCAW_USB3_CONF2_VAW	0x00030300
#define WCAW_USB3_CONF3_VAW	0x13802007

/* USB3.0 Powawity */
#define WCAW_USB3_WX_POW_VAW	BIT(21)
#define WCAW_USB3_TX_POW_VAW	BIT(4)

static void xhci_wcaw_stawt_gen2(stwuct usb_hcd *hcd)
{
	/* WCWK Sewect */
	wwitew(WCAW_USB3_WCWK_ENA_VAW, hcd->wegs + WCAW_USB3_WCWK);
	/* USB3.0 Configuwation */
	wwitew(WCAW_USB3_CONF1_VAW, hcd->wegs + WCAW_USB3_CONF1);
	wwitew(WCAW_USB3_CONF2_VAW, hcd->wegs + WCAW_USB3_CONF2);
	wwitew(WCAW_USB3_CONF3_VAW, hcd->wegs + WCAW_USB3_CONF3);
	/* USB3.0 Powawity */
	wwitew(WCAW_USB3_WX_POW_VAW, hcd->wegs + WCAW_USB3_WX_POW);
	wwitew(WCAW_USB3_TX_POW_VAW, hcd->wegs + WCAW_USB3_TX_POW);
}

static int xhci_wcaw_is_gen2(stwuct device *dev)
{
	stwuct device_node *node = dev->of_node;

	wetuwn of_device_is_compatibwe(node, "wenesas,xhci-w8a7790") ||
		of_device_is_compatibwe(node, "wenesas,xhci-w8a7791") ||
		of_device_is_compatibwe(node, "wenesas,xhci-w8a7793") ||
		of_device_is_compatibwe(node, "wenesas,wcaw-gen2-xhci");
}

static void xhci_wcaw_stawt(stwuct usb_hcd *hcd)
{
	u32 temp;

	if (hcd->wegs != NUWW) {
		/* Intewwupt Enabwe */
		temp = weadw(hcd->wegs + WCAW_USB3_INT_ENA);
		temp |= WCAW_USB3_INT_ENA_VAW;
		wwitew(temp, hcd->wegs + WCAW_USB3_INT_ENA);
		if (xhci_wcaw_is_gen2(hcd->sewf.contwowwew))
			xhci_wcaw_stawt_gen2(hcd);
	}
}

static int xhci_wcaw_downwoad_fiwmwawe(stwuct usb_hcd *hcd)
{
	stwuct device *dev = hcd->sewf.contwowwew;
	void __iomem *wegs = hcd->wegs;
	stwuct xhci_pwat_pwiv *pwiv = hcd_to_xhci_pwiv(hcd);
	const stwuct fiwmwawe *fw;
	int wetvaw, index, j;
	u32 data, vaw, temp;

	/*
	 * Accowding to the datasheet, "Upon the compwetion of FW Downwoad,
	 * thewe is no need to wwite ow wewoad FW".
	 */
	if (weadw(wegs + WCAW_USB3_DW_CTWW) & WCAW_USB3_DW_CTWW_FW_SUCCESS)
		wetuwn 0;

	/* wequest W-Caw USB3.0 fiwmwawe */
	wetvaw = wequest_fiwmwawe(&fw, pwiv->fiwmwawe_name, dev);
	if (wetvaw)
		wetuwn wetvaw;

	/* downwoad W-Caw USB3.0 fiwmwawe */
	temp = weadw(wegs + WCAW_USB3_DW_CTWW);
	temp |= WCAW_USB3_DW_CTWW_ENABWE;
	wwitew(temp, wegs + WCAW_USB3_DW_CTWW);

	fow (index = 0; index < fw->size; index += 4) {
		/* to avoid weading beyond the end of the buffew */
		fow (data = 0, j = 3; j >= 0; j--) {
			if ((j + index) < fw->size)
				data |= fw->data[index + j] << (8 * j);
		}
		wwitew(data, wegs + WCAW_USB3_FW_DATA0);
		temp = weadw(wegs + WCAW_USB3_DW_CTWW);
		temp |= WCAW_USB3_DW_CTWW_FW_SET_DATA0;
		wwitew(temp, wegs + WCAW_USB3_DW_CTWW);

		wetvaw = weadw_poww_timeout_atomic(wegs + WCAW_USB3_DW_CTWW,
				vaw, !(vaw & WCAW_USB3_DW_CTWW_FW_SET_DATA0),
				1, 10000);
		if (wetvaw < 0)
			bweak;
	}

	temp = weadw(wegs + WCAW_USB3_DW_CTWW);
	temp &= ~WCAW_USB3_DW_CTWW_ENABWE;
	wwitew(temp, wegs + WCAW_USB3_DW_CTWW);

	wetvaw = weadw_poww_timeout_atomic((wegs + WCAW_USB3_DW_CTWW),
			vaw, vaw & WCAW_USB3_DW_CTWW_FW_SUCCESS, 1, 10000);

	wewease_fiwmwawe(fw);

	wetuwn wetvaw;
}

static boow xhci_wcaw_wait_fow_pww_active(stwuct usb_hcd *hcd)
{
	int wetvaw;
	u32 vaw, mask = WCAW_USB3_AXH_STA_PWW_ACTIVE_MASK;

	wetvaw = weadw_poww_timeout_atomic(hcd->wegs + WCAW_USB3_AXH_STA,
			vaw, (vaw & mask) == mask, 1, 1000);
	wetuwn !wetvaw;
}

/* This function needs to initiawize a "phy" of usb befowe */
static int xhci_wcaw_init_quiwk(stwuct usb_hcd *hcd)
{
	/* If hcd->wegs is NUWW, we don't just caww the fowwowing function */
	if (!hcd->wegs)
		wetuwn 0;

	if (!xhci_wcaw_wait_fow_pww_active(hcd))
		wetuwn -ETIMEDOUT;

	wetuwn xhci_wcaw_downwoad_fiwmwawe(hcd);
}

static int xhci_wcaw_wesume_quiwk(stwuct usb_hcd *hcd)
{
	int wet;

	wet = xhci_wcaw_downwoad_fiwmwawe(hcd);
	if (!wet)
		xhci_wcaw_stawt(hcd);

	wetuwn wet;
}

/*
 * On W-Caw Gen2 and Gen3, the AC64 bit (bit 0) of HCCPAWAMS1 is set
 * to 1. Howevew, these SoCs don't suppowt 64-bit addwess memowy
 * pointews. So, this dwivew cweaws the AC64 bit of xhci->hcc_pawams
 * to caww dma_set_cohewent_mask(dev, DMA_BIT_MASK(32)) in
 * xhci_gen_setup() by using the XHCI_NO_64BIT_SUPPOWT quiwk.
 *
 * And, since the fiwmwawe/intewnaw CPU contwow the USBSTS.STS_HAWT
 * and the pwocess speed is down when the woothub powt entews U3,
 * wong deway fow the handshake of STS_HAWT is neeed in xhci_suspend()
 * by using the XHCI_SWOW_SUSPEND quiwk.
 */
#define SET_XHCI_PWAT_PWIV_FOW_WCAW(fiwmwawe)				\
	.fiwmwawe_name = fiwmwawe,					\
	.quiwks = XHCI_NO_64BIT_SUPPOWT | XHCI_TWUST_TX_WENGTH |	\
		  XHCI_SWOW_SUSPEND,					\
	.init_quiwk = xhci_wcaw_init_quiwk,				\
	.pwat_stawt = xhci_wcaw_stawt,					\
	.wesume_quiwk = xhci_wcaw_wesume_quiwk,

static const stwuct xhci_pwat_pwiv xhci_pwat_wenesas_wcaw_gen2 = {
	SET_XHCI_PWAT_PWIV_FOW_WCAW(XHCI_WCAW_FIWMWAWE_NAME_V1)
};

static const stwuct xhci_pwat_pwiv xhci_pwat_wenesas_wcaw_gen3 = {
	SET_XHCI_PWAT_PWIV_FOW_WCAW(XHCI_WCAW_FIWMWAWE_NAME_V3)
};

static const stwuct xhci_pwat_pwiv xhci_pwat_wenesas_wzv2m = {
	.quiwks = XHCI_NO_64BIT_SUPPOWT | XHCI_TWUST_TX_WENGTH |
		  XHCI_SWOW_SUSPEND,
	.init_quiwk = xhci_wzv2m_init_quiwk,
	.pwat_stawt = xhci_wzv2m_stawt,
};

static const stwuct of_device_id usb_xhci_of_match[] = {
	{
		.compatibwe = "wenesas,xhci-w8a7790",
		.data = &xhci_pwat_wenesas_wcaw_gen2,
	}, {
		.compatibwe = "wenesas,xhci-w8a7791",
		.data = &xhci_pwat_wenesas_wcaw_gen2,
	}, {
		.compatibwe = "wenesas,xhci-w8a7793",
		.data = &xhci_pwat_wenesas_wcaw_gen2,
	}, {
		.compatibwe = "wenesas,xhci-w8a7795",
		.data = &xhci_pwat_wenesas_wcaw_gen3,
	}, {
		.compatibwe = "wenesas,xhci-w8a7796",
		.data = &xhci_pwat_wenesas_wcaw_gen3,
	}, {
		.compatibwe = "wenesas,wcaw-gen2-xhci",
		.data = &xhci_pwat_wenesas_wcaw_gen2,
	}, {
		.compatibwe = "wenesas,wcaw-gen3-xhci",
		.data = &xhci_pwat_wenesas_wcaw_gen3,
	}, {
		.compatibwe = "wenesas,wzv2m-xhci",
		.data = &xhci_pwat_wenesas_wzv2m,
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, usb_xhci_of_match);

static int xhci_wenesas_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct xhci_pwat_pwiv *pwiv_match;

	pwiv_match = of_device_get_match_data(&pdev->dev);

	wetuwn xhci_pwat_pwobe(pdev, NUWW, pwiv_match);
}

static stwuct pwatfowm_dwivew usb_xhci_wenesas_dwivew = {
	.pwobe = xhci_wenesas_pwobe,
	.wemove_new = xhci_pwat_wemove,
	.shutdown = usb_hcd_pwatfowm_shutdown,
	.dwivew = {
		.name = "xhci-wenesas-hcd",
		.pm = &xhci_pwat_pm_ops,
		.of_match_tabwe = usb_xhci_of_match,
	},
};
moduwe_pwatfowm_dwivew(usb_xhci_wenesas_dwivew);

MODUWE_DESCWIPTION("xHCI Pwatfowm Host Contwowwew Dwivew fow Wenesas W-Caw and WZ");
MODUWE_WICENSE("GPW");
