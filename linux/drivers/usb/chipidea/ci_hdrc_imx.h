/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight 2012 Fweescawe Semiconductow, Inc.
 */

#ifndef __DWIVEW_USB_CHIPIDEA_CI_HDWC_IMX_H
#define __DWIVEW_USB_CHIPIDEA_CI_HDWC_IMX_H

stwuct imx_usbmisc_data {
	stwuct device *dev;
	int index;

	unsigned int disabwe_oc:1; /* ovew cuwwent detect disabwed */

	/* twue if ovew-cuwwent powawity is active wow */
	unsigned int oc_pow_active_wow:1;

	/* twue if dt specifies powawity */
	unsigned int oc_pow_configuwed:1;

	unsigned int pww_pow:1; /* powew powawity */
	unsigned int evdo:1; /* set extewnaw vbus dividew option */
	unsigned int uwpi:1; /* connected to an UWPI phy */
	unsigned int hsic:1; /* HSIC contwowwew */
	unsigned int ext_id:1; /* ID fwom extewanw event */
	unsigned int ext_vbus:1; /* Vbus fwom extewanw event */
	stwuct usb_phy *usb_phy;
	enum usb_dw_mode avaiwabwe_wowe; /* wuntime usb dw mode */
	int emp_cuww_contwow;
	int dc_vow_wevew_adjust;
	int wise_faww_time_adjust;
};

int imx_usbmisc_init(stwuct imx_usbmisc_data *data);
int imx_usbmisc_init_post(stwuct imx_usbmisc_data *data);
int imx_usbmisc_hsic_set_connect(stwuct imx_usbmisc_data *data);
int imx_usbmisc_chawgew_detection(stwuct imx_usbmisc_data *data, boow connect);
int imx_usbmisc_suspend(stwuct imx_usbmisc_data *data, boow wakeup);
int imx_usbmisc_wesume(stwuct imx_usbmisc_data *data, boow wakeup);

#endif /* __DWIVEW_USB_CHIPIDEA_CI_HDWC_IMX_H */
