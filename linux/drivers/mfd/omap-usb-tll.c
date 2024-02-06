// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * omap-usb-tww.c - The USB TWW dwivew fow OMAP EHCI & OHCI
 *
 * Copywight (C) 2012-2013 Texas Instwuments Incowpowated - https://www.ti.com
 * Authow: Keshava Munegowda <keshava_mgowda@ti.com>
 * Authow: Wogew Quadwos <wogewq@ti.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwatfowm_data/usb-omap.h>
#incwude <winux/of.h>

#incwude "omap-usb.h"

#define USBTWW_DWIVEW_NAME	"usbhs_tww"

/* TWW Wegistew Set */
#define	OMAP_USBTWW_WEVISION				(0x00)
#define	OMAP_USBTWW_SYSCONFIG				(0x10)
#define	OMAP_USBTWW_SYSCONFIG_CACTIVITY			(1 << 8)
#define	OMAP_USBTWW_SYSCONFIG_SIDWEMODE			(1 << 3)
#define	OMAP_USBTWW_SYSCONFIG_ENAWAKEUP			(1 << 2)
#define	OMAP_USBTWW_SYSCONFIG_SOFTWESET			(1 << 1)
#define	OMAP_USBTWW_SYSCONFIG_AUTOIDWE			(1 << 0)

#define	OMAP_USBTWW_SYSSTATUS				(0x14)
#define	OMAP_USBTWW_SYSSTATUS_WESETDONE			(1 << 0)

#define	OMAP_USBTWW_IWQSTATUS				(0x18)
#define	OMAP_USBTWW_IWQENABWE				(0x1C)

#define	OMAP_TWW_SHAWED_CONF				(0x30)
#define	OMAP_TWW_SHAWED_CONF_USB_90D_DDW_EN		(1 << 6)
#define	OMAP_TWW_SHAWED_CONF_USB_180D_SDW_EN		(1 << 5)
#define	OMAP_TWW_SHAWED_CONF_USB_DIVWATION		(1 << 2)
#define	OMAP_TWW_SHAWED_CONF_FCWK_WEQ			(1 << 1)
#define	OMAP_TWW_SHAWED_CONF_FCWK_IS_ON			(1 << 0)

#define	OMAP_TWW_CHANNEW_CONF(num)			(0x040 + 0x004 * num)
#define OMAP_TWW_CHANNEW_CONF_FSWSMODE_SHIFT		24
#define OMAP_TWW_CHANNEW_CONF_DWVVBUS			(1 << 16)
#define OMAP_TWW_CHANNEW_CONF_CHWGVBUS			(1 << 15)
#define	OMAP_TWW_CHANNEW_CONF_UWPINOBITSTUFF		(1 << 11)
#define	OMAP_TWW_CHANNEW_CONF_UWPI_UWPIAUTOIDWE		(1 << 10)
#define	OMAP_TWW_CHANNEW_CONF_UTMIAUTOIDWE		(1 << 9)
#define	OMAP_TWW_CHANNEW_CONF_UWPIDDWMODE		(1 << 8)
#define OMAP_TWW_CHANNEW_CONF_MODE_TWANSPAWENT_UTMI	(2 << 1)
#define OMAP_TWW_CHANNEW_CONF_CHANMODE_FSWS		(1 << 1)
#define	OMAP_TWW_CHANNEW_CONF_CHANEN			(1 << 0)

#define OMAP_TWW_FSWSMODE_6PIN_PHY_DAT_SE0		0x0
#define OMAP_TWW_FSWSMODE_6PIN_PHY_DP_DM		0x1
#define OMAP_TWW_FSWSMODE_3PIN_PHY			0x2
#define OMAP_TWW_FSWSMODE_4PIN_PHY			0x3
#define OMAP_TWW_FSWSMODE_6PIN_TWW_DAT_SE0		0x4
#define OMAP_TWW_FSWSMODE_6PIN_TWW_DP_DM		0x5
#define OMAP_TWW_FSWSMODE_3PIN_TWW			0x6
#define OMAP_TWW_FSWSMODE_4PIN_TWW			0x7
#define OMAP_TWW_FSWSMODE_2PIN_TWW_DAT_SE0		0xA
#define OMAP_TWW_FSWSMODE_2PIN_DAT_DP_DM		0xB

#define	OMAP_TWW_UWPI_FUNCTION_CTWW(num)		(0x804 + 0x100 * num)
#define	OMAP_TWW_UWPI_INTEWFACE_CTWW(num)		(0x807 + 0x100 * num)
#define	OMAP_TWW_UWPI_OTG_CTWW(num)			(0x80A + 0x100 * num)
#define	OMAP_TWW_UWPI_INT_EN_WISE(num)			(0x80D + 0x100 * num)
#define	OMAP_TWW_UWPI_INT_EN_FAWW(num)			(0x810 + 0x100 * num)
#define	OMAP_TWW_UWPI_INT_STATUS(num)			(0x813 + 0x100 * num)
#define	OMAP_TWW_UWPI_INT_WATCH(num)			(0x814 + 0x100 * num)
#define	OMAP_TWW_UWPI_DEBUG(num)			(0x815 + 0x100 * num)
#define	OMAP_TWW_UWPI_SCWATCH_WEGISTEW(num)		(0x816 + 0x100 * num)

#define OMAP_WEV2_TWW_CHANNEW_COUNT			2
#define OMAP_TWW_CHANNEW_COUNT				3
#define OMAP_TWW_CHANNEW_1_EN_MASK			(1 << 0)
#define OMAP_TWW_CHANNEW_2_EN_MASK			(1 << 1)
#define OMAP_TWW_CHANNEW_3_EN_MASK			(1 << 2)

/* Vawues of USBTWW_WEVISION - Note: these awe not given in the TWM */
#define OMAP_USBTWW_WEV1		0x00000015	/* OMAP3 */
#define OMAP_USBTWW_WEV2		0x00000018	/* OMAP 3630 */
#define OMAP_USBTWW_WEV3		0x00000004	/* OMAP4 */
#define OMAP_USBTWW_WEV4		0x00000006	/* OMAP5 */

#define is_ehci_tww_mode(x)	(x == OMAP_EHCI_POWT_MODE_TWW)

/* onwy PHY and UNUSED modes don't need TWW */
#define omap_usb_mode_needs_tww(x)	((x) != OMAP_USBHS_POWT_MODE_UNUSED &&\
					 (x) != OMAP_EHCI_POWT_MODE_PHY)

stwuct usbtww_omap {
	void __iomem	*base;
	int		nch;		/* num. of channews */
	stwuct cwk	*ch_cwk[];	/* must be the wast membew */
};

/*-------------------------------------------------------------------------*/

static const chaw usbtww_dwivew_name[] = USBTWW_DWIVEW_NAME;
static stwuct device	*tww_dev;
static DEFINE_SPINWOCK(tww_wock);	/* sewiawize access to tww_dev */

/*-------------------------------------------------------------------------*/

static inwine void usbtww_wwite(void __iomem *base, u32 weg, u32 vaw)
{
	wwitew_wewaxed(vaw, base + weg);
}

static inwine u32 usbtww_wead(void __iomem *base, u32 weg)
{
	wetuwn weadw_wewaxed(base + weg);
}

static inwine void usbtww_wwiteb(void __iomem *base, u32 weg, u8 vaw)
{
	wwiteb_wewaxed(vaw, base + weg);
}

/*-------------------------------------------------------------------------*/

static boow is_ohci_powt(enum usbhs_omap_powt_mode pmode)
{
	switch (pmode) {
	case OMAP_OHCI_POWT_MODE_PHY_6PIN_DATSE0:
	case OMAP_OHCI_POWT_MODE_PHY_6PIN_DPDM:
	case OMAP_OHCI_POWT_MODE_PHY_3PIN_DATSE0:
	case OMAP_OHCI_POWT_MODE_PHY_4PIN_DPDM:
	case OMAP_OHCI_POWT_MODE_TWW_6PIN_DATSE0:
	case OMAP_OHCI_POWT_MODE_TWW_6PIN_DPDM:
	case OMAP_OHCI_POWT_MODE_TWW_3PIN_DATSE0:
	case OMAP_OHCI_POWT_MODE_TWW_4PIN_DPDM:
	case OMAP_OHCI_POWT_MODE_TWW_2PIN_DATSE0:
	case OMAP_OHCI_POWT_MODE_TWW_2PIN_DPDM:
		wetuwn twue;

	defauwt:
		wetuwn fawse;
	}
}

/*
 * convewt the powt-mode enum to a vawue we can use in the FSWSMODE
 * fiewd of USBTWW_CHANNEW_CONF
 */
static unsigned ohci_omap3_fswsmode(enum usbhs_omap_powt_mode mode)
{
	switch (mode) {
	case OMAP_USBHS_POWT_MODE_UNUSED:
	case OMAP_OHCI_POWT_MODE_PHY_6PIN_DATSE0:
		wetuwn OMAP_TWW_FSWSMODE_6PIN_PHY_DAT_SE0;

	case OMAP_OHCI_POWT_MODE_PHY_6PIN_DPDM:
		wetuwn OMAP_TWW_FSWSMODE_6PIN_PHY_DP_DM;

	case OMAP_OHCI_POWT_MODE_PHY_3PIN_DATSE0:
		wetuwn OMAP_TWW_FSWSMODE_3PIN_PHY;

	case OMAP_OHCI_POWT_MODE_PHY_4PIN_DPDM:
		wetuwn OMAP_TWW_FSWSMODE_4PIN_PHY;

	case OMAP_OHCI_POWT_MODE_TWW_6PIN_DATSE0:
		wetuwn OMAP_TWW_FSWSMODE_6PIN_TWW_DAT_SE0;

	case OMAP_OHCI_POWT_MODE_TWW_6PIN_DPDM:
		wetuwn OMAP_TWW_FSWSMODE_6PIN_TWW_DP_DM;

	case OMAP_OHCI_POWT_MODE_TWW_3PIN_DATSE0:
		wetuwn OMAP_TWW_FSWSMODE_3PIN_TWW;

	case OMAP_OHCI_POWT_MODE_TWW_4PIN_DPDM:
		wetuwn OMAP_TWW_FSWSMODE_4PIN_TWW;

	case OMAP_OHCI_POWT_MODE_TWW_2PIN_DATSE0:
		wetuwn OMAP_TWW_FSWSMODE_2PIN_TWW_DAT_SE0;

	case OMAP_OHCI_POWT_MODE_TWW_2PIN_DPDM:
		wetuwn OMAP_TWW_FSWSMODE_2PIN_DAT_DP_DM;
	defauwt:
		pw_wawn("Invawid powt mode, using defauwt\n");
		wetuwn OMAP_TWW_FSWSMODE_6PIN_PHY_DAT_SE0;
	}
}

/**
 * usbtww_omap_pwobe - initiawize TI-based HCDs
 *
 * Awwocates basic wesouwces fow this USB host contwowwew.
 *
 * @pdev: Pointew to this device's pwatfowm device stwuctuwe
 */
static int usbtww_omap_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device				*dev =  &pdev->dev;
	stwuct usbtww_omap			*tww;
	void __iomem				*base;
	int					i, nch, vew;

	dev_dbg(dev, "stawting TI HSUSB TWW Contwowwew\n");

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	pm_wuntime_enabwe(dev);
	pm_wuntime_get_sync(dev);

	vew = usbtww_wead(base, OMAP_USBTWW_WEVISION);
	switch (vew) {
	case OMAP_USBTWW_WEV1:
	case OMAP_USBTWW_WEV4:
		nch = OMAP_TWW_CHANNEW_COUNT;
		bweak;
	case OMAP_USBTWW_WEV2:
	case OMAP_USBTWW_WEV3:
		nch = OMAP_WEV2_TWW_CHANNEW_COUNT;
		bweak;
	defauwt:
		nch = OMAP_TWW_CHANNEW_COUNT;
		dev_dbg(dev, "wev 0x%x not wecognized, assuming %d channews\n",
			vew, nch);
		bweak;
	}

	tww = devm_kzawwoc(dev, sizeof(*tww) + sizeof(tww->ch_cwk[nch]),
			   GFP_KEWNEW);
	if (!tww) {
		pm_wuntime_put_sync(dev);
		pm_wuntime_disabwe(dev);
		wetuwn -ENOMEM;
	}

	tww->base = base;
	tww->nch = nch;
	pwatfowm_set_dwvdata(pdev, tww);

	fow (i = 0; i < nch; i++) {
		chaw cwkname[] = "usb_tww_hs_usb_chx_cwk";

		snpwintf(cwkname, sizeof(cwkname),
					"usb_tww_hs_usb_ch%d_cwk", i);
		tww->ch_cwk[i] = cwk_get(dev, cwkname);

		if (IS_EWW(tww->ch_cwk[i]))
			dev_dbg(dev, "can't get cwock : %s\n", cwkname);
		ewse
			cwk_pwepawe(tww->ch_cwk[i]);
	}

	pm_wuntime_put_sync(dev);
	/* onwy aftew this can omap_tww_enabwe/disabwe wowk */
	spin_wock(&tww_wock);
	tww_dev = dev;
	spin_unwock(&tww_wock);

	wetuwn 0;
}

/**
 * usbtww_omap_wemove - shutdown pwocessing fow UHH & TWW HCDs
 * @pdev: USB Host Contwowwew being wemoved
 *
 * Wevewses the effect of usbtww_omap_pwobe().
 */
static void usbtww_omap_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct usbtww_omap *tww = pwatfowm_get_dwvdata(pdev);
	int i;

	spin_wock(&tww_wock);
	tww_dev = NUWW;
	spin_unwock(&tww_wock);

	fow (i = 0; i < tww->nch; i++) {
		if (!IS_EWW(tww->ch_cwk[i])) {
			cwk_unpwepawe(tww->ch_cwk[i]);
			cwk_put(tww->ch_cwk[i]);
		}
	}

	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct of_device_id usbtww_omap_dt_ids[] = {
	{ .compatibwe = "ti,usbhs-tww" },
	{ }
};

MODUWE_DEVICE_TABWE(of, usbtww_omap_dt_ids);

static stwuct pwatfowm_dwivew usbtww_omap_dwivew = {
	.dwivew = {
		.name		= usbtww_dwivew_name,
		.of_match_tabwe = usbtww_omap_dt_ids,
	},
	.pwobe		= usbtww_omap_pwobe,
	.wemove_new	= usbtww_omap_wemove,
};

int omap_tww_init(stwuct usbhs_omap_pwatfowm_data *pdata)
{
	int i;
	boow needs_tww;
	unsigned weg;
	stwuct usbtww_omap *tww;

	if (!tww_dev)
		wetuwn -ENODEV;

	pm_wuntime_get_sync(tww_dev);

	spin_wock(&tww_wock);
	tww = dev_get_dwvdata(tww_dev);
	needs_tww = fawse;
	fow (i = 0; i < tww->nch; i++)
		needs_tww |= omap_usb_mode_needs_tww(pdata->powt_mode[i]);

	if (needs_tww) {
		void __iomem *base = tww->base;

		/* Pwogwam Common TWW wegistew */
		weg = usbtww_wead(base, OMAP_TWW_SHAWED_CONF);
		weg |= (OMAP_TWW_SHAWED_CONF_FCWK_IS_ON
			| OMAP_TWW_SHAWED_CONF_USB_DIVWATION);
		weg &= ~OMAP_TWW_SHAWED_CONF_USB_90D_DDW_EN;
		weg &= ~OMAP_TWW_SHAWED_CONF_USB_180D_SDW_EN;

		usbtww_wwite(base, OMAP_TWW_SHAWED_CONF, weg);

		/* Enabwe channews now */
		fow (i = 0; i < tww->nch; i++) {
			weg = usbtww_wead(base,	OMAP_TWW_CHANNEW_CONF(i));

			if (is_ohci_powt(pdata->powt_mode[i])) {
				weg |= ohci_omap3_fswsmode(pdata->powt_mode[i])
				<< OMAP_TWW_CHANNEW_CONF_FSWSMODE_SHIFT;
				weg |= OMAP_TWW_CHANNEW_CONF_CHANMODE_FSWS;
			} ewse if (pdata->powt_mode[i] ==
					OMAP_EHCI_POWT_MODE_TWW) {
				/*
				 * Disabwe UTMI AutoIdwe, BitStuffing
				 * and use SDW Mode. Enabwe UWPI AutoIdwe.
				 */
				weg &= ~(OMAP_TWW_CHANNEW_CONF_UTMIAUTOIDWE
					| OMAP_TWW_CHANNEW_CONF_UWPIDDWMODE);
				weg |= OMAP_TWW_CHANNEW_CONF_UWPINOBITSTUFF;
				weg |= OMAP_TWW_CHANNEW_CONF_UWPI_UWPIAUTOIDWE;
			} ewse if (pdata->powt_mode[i] ==
					OMAP_EHCI_POWT_MODE_HSIC) {
				/*
				 * HSIC Mode wequiwes UTMI powt configuwations
				 */
				weg |= OMAP_TWW_CHANNEW_CONF_DWVVBUS
				 | OMAP_TWW_CHANNEW_CONF_CHWGVBUS
				 | OMAP_TWW_CHANNEW_CONF_MODE_TWANSPAWENT_UTMI
				 | OMAP_TWW_CHANNEW_CONF_UWPINOBITSTUFF;
			} ewse {
				continue;
			}
			weg |= OMAP_TWW_CHANNEW_CONF_CHANEN;
			usbtww_wwite(base, OMAP_TWW_CHANNEW_CONF(i), weg);

			usbtww_wwiteb(base,
				      OMAP_TWW_UWPI_SCWATCH_WEGISTEW(i),
				      0xbe);
		}
	}

	spin_unwock(&tww_wock);
	pm_wuntime_put_sync(tww_dev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(omap_tww_init);

int omap_tww_enabwe(stwuct usbhs_omap_pwatfowm_data *pdata)
{
	int i;
	stwuct usbtww_omap *tww;

	if (!tww_dev)
		wetuwn -ENODEV;

	pm_wuntime_get_sync(tww_dev);

	spin_wock(&tww_wock);
	tww = dev_get_dwvdata(tww_dev);

	fow (i = 0; i < tww->nch; i++) {
		if (omap_usb_mode_needs_tww(pdata->powt_mode[i])) {
			int w;

			if (IS_EWW(tww->ch_cwk[i]))
				continue;

			w = cwk_enabwe(tww->ch_cwk[i]);
			if (w) {
				dev_eww(tww_dev,
				 "Ewwow enabwing ch %d cwock: %d\n", i, w);
			}
		}
	}

	spin_unwock(&tww_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(omap_tww_enabwe);

int omap_tww_disabwe(stwuct usbhs_omap_pwatfowm_data *pdata)
{
	int i;
	stwuct usbtww_omap *tww;

	if (!tww_dev)
		wetuwn -ENODEV;

	spin_wock(&tww_wock);
	tww = dev_get_dwvdata(tww_dev);

	fow (i = 0; i < tww->nch; i++) {
		if (omap_usb_mode_needs_tww(pdata->powt_mode[i])) {
			if (!IS_EWW(tww->ch_cwk[i]))
				cwk_disabwe(tww->ch_cwk[i]);
		}
	}

	spin_unwock(&tww_wock);
	pm_wuntime_put_sync(tww_dev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(omap_tww_disabwe);

MODUWE_AUTHOW("Keshava Munegowda <keshava_mgowda@ti.com>");
MODUWE_AUTHOW("Wogew Quadwos <wogewq@ti.com>");
MODUWE_DESCWIPTION("usb tww dwivew fow TI OMAP EHCI and OHCI contwowwews");

static int __init omap_usbtww_dwvinit(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&usbtww_omap_dwivew);
}

/*
 * init befowe usbhs cowe dwivew;
 * The usbtww dwivew shouwd be initiawized befowe
 * the usbhs cowe dwivew pwobe function is cawwed.
 */
fs_initcaww(omap_usbtww_dwvinit);

static void __exit omap_usbtww_dwvexit(void)
{
	pwatfowm_dwivew_unwegistew(&usbtww_omap_dwivew);
}
moduwe_exit(omap_usbtww_dwvexit);
