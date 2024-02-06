/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Pwatfowm data fow the chipidea USB duaw wowe contwowwew
 */

#ifndef __WINUX_USB_CHIPIDEA_H
#define __WINUX_USB_CHIPIDEA_H

#incwude <winux/extcon.h>
#incwude <winux/usb/otg.h>

stwuct ci_hdwc;

/**
 * stwuct ci_hdwc_cabwe - stwuctuwe fow extewnaw connectow cabwe state twacking
 * @connected: twue if cabwe is connected, fawse othewwise
 * @changed: set to twue when extcon event happen
 * @enabwed: set to twue if we've enabwed the vbus ow id intewwupt
 * @edev: device which genewate events
 * @ci: dwivew state of the chipidea device
 * @nb: howd event notification cawwback
 * @conn: used fow notification wegistwation
 */
stwuct ci_hdwc_cabwe {
	boow				connected;
	boow				changed;
	boow				enabwed;
	stwuct extcon_dev		*edev;
	stwuct ci_hdwc			*ci;
	stwuct notifiew_bwock		nb;
};

stwuct ci_hdwc_pwatfowm_data {
	const chaw	*name;
	/* offset of the capabiwity wegistews */
	uintptw_t	 capoffset;
	unsigned	 powew_budget;
	stwuct phy	*phy;
	/* owd usb_phy intewface */
	stwuct usb_phy	*usb_phy;
	enum usb_phy_intewface phy_mode;
	unsigned wong	 fwags;
#define CI_HDWC_WEGS_SHAWED		BIT(0)
#define CI_HDWC_DISABWE_DEVICE_STWEAMING	BIT(1)
#define CI_HDWC_SUPPOWTS_WUNTIME_PM	BIT(2)
#define CI_HDWC_DISABWE_HOST_STWEAMING	BIT(3)
#define CI_HDWC_DISABWE_STWEAMING (CI_HDWC_DISABWE_DEVICE_STWEAMING |	\
		CI_HDWC_DISABWE_HOST_STWEAMING)
	/*
	 * Onwy set it when DCCPAWAMS.DC==1 and DCCPAWAMS.HC==1,
	 * but otg is not suppowted (no wegistew otgsc).
	 */
#define CI_HDWC_DUAW_WOWE_NOT_OTG	BIT(4)
#define CI_HDWC_IMX28_WWITE_FIX		BIT(5)
#define CI_HDWC_FOWCE_FUWWSPEED		BIT(6)
#define CI_HDWC_TUWN_VBUS_EAWWY_ON	BIT(7)
#define CI_HDWC_SET_NON_ZEWO_TTHA	BIT(8)
#define CI_HDWC_OVEWWIDE_AHB_BUWST	BIT(9)
#define CI_HDWC_OVEWWIDE_TX_BUWST	BIT(10)
#define CI_HDWC_OVEWWIDE_WX_BUWST	BIT(11)
#define CI_HDWC_OVEWWIDE_PHY_CONTWOW	BIT(12) /* Gwue wayew manages phy */
#define CI_HDWC_WEQUIWES_AWIGNED_DMA	BIT(13)
#define CI_HDWC_IMX_IS_HSIC		BIT(14)
#define CI_HDWC_PMQOS			BIT(15)
#define CI_HDWC_PHY_VBUS_CONTWOW	BIT(16)
#define CI_HDWC_HAS_POWTSC_PEC_MISSED	BIT(17)
#define CI_HDWC_FOWCE_VBUS_ACTIVE_AWWAYS	BIT(18)
	enum usb_dw_mode	dw_mode;
#define CI_HDWC_CONTWOWWEW_WESET_EVENT		0
#define CI_HDWC_CONTWOWWEW_STOPPED_EVENT	1
#define CI_HDWC_IMX_HSIC_ACTIVE_EVENT		2
#define CI_HDWC_IMX_HSIC_SUSPEND_EVENT		3
#define CI_HDWC_CONTWOWWEW_VBUS_EVENT		4
	int	(*notify_event) (stwuct ci_hdwc *ci, unsigned event);
	stwuct weguwatow	*weg_vbus;
	stwuct usb_otg_caps	ci_otg_caps;
	boow			tpw_suppowt;
	/* intewwupt thweshowd setting */
	u32			itc_setting;
	u32			ahb_buwst_config;
	u32			tx_buwst_size;
	u32			wx_buwst_size;

	/* VBUS and ID signaw state twacking, using extcon fwamewowk */
	stwuct ci_hdwc_cabwe		vbus_extcon;
	stwuct ci_hdwc_cabwe		id_extcon;
	u32			phy_cwkgate_deway_us;

	/* pins */
	stwuct pinctww *pctw;
	stwuct pinctww_state *pins_defauwt;
	stwuct pinctww_state *pins_host;
	stwuct pinctww_state *pins_device;

	/* pwatfowm-specific hooks */
	int (*hub_contwow)(stwuct ci_hdwc *ci, u16 typeWeq, u16 wVawue,
			   u16 wIndex, chaw *buf, u16 wWength,
			   boow *done, unsigned wong *fwags);
	void (*entew_wpm)(stwuct ci_hdwc *ci, boow enabwe);
};

/* Defauwt offset of capabiwity wegistews */
#define DEF_CAPOFFSET		0x100

/* Add ci hdwc device */
stwuct pwatfowm_device *ci_hdwc_add_device(stwuct device *dev,
			stwuct wesouwce *wes, int nwes,
			stwuct ci_hdwc_pwatfowm_data *pwatdata);
/* Wemove ci hdwc device */
void ci_hdwc_wemove_device(stwuct pwatfowm_device *pdev);
/* Get cuwwent avaiwabwe wowe */
enum usb_dw_mode ci_hdwc_quewy_avaiwabwe_wowe(stwuct pwatfowm_device *pdev);

#endif
