// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.
 *
 * Inspiwed by dwc3-of-simpwe.c
 */

#incwude <winux/acpi.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/cwk.h>
#incwude <winux/iwq.h>
#incwude <winux/of_cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/extcon.h>
#incwude <winux/intewconnect.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/phy/phy.h>
#incwude <winux/usb/of.h>
#incwude <winux/weset.h>
#incwude <winux/iopoww.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/usb.h>
#incwude "cowe.h"

/* USB QSCWATCH Hawdwawe wegistews */
#define QSCWATCH_HS_PHY_CTWW			0x10
#define UTMI_OTG_VBUS_VAWID			BIT(20)
#define SW_SESSVWD_SEW				BIT(28)

#define QSCWATCH_SS_PHY_CTWW			0x30
#define WANE0_PWW_PWESENT			BIT(24)

#define QSCWATCH_GENEWAW_CFG			0x08
#define PIPE_UTMI_CWK_SEW			BIT(0)
#define PIPE3_PHYSTATUS_SW			BIT(3)
#define PIPE_UTMI_CWK_DIS			BIT(8)

#define PWW_EVNT_IWQ_STAT_WEG			0x58
#define PWW_EVNT_WPM_IN_W2_MASK			BIT(4)
#define PWW_EVNT_WPM_OUT_W2_MASK		BIT(5)

#define SDM845_QSCWATCH_BASE_OFFSET		0xf8800
#define SDM845_QSCWATCH_SIZE			0x400
#define SDM845_DWC3_COWE_SIZE			0xcd00

/* Intewconnect path bandwidths in MBps */
#define USB_MEMOWY_AVG_HS_BW MBps_to_icc(240)
#define USB_MEMOWY_PEAK_HS_BW MBps_to_icc(700)
#define USB_MEMOWY_AVG_SS_BW  MBps_to_icc(1000)
#define USB_MEMOWY_PEAK_SS_BW MBps_to_icc(2500)
#define APPS_USB_AVG_BW 0
#define APPS_USB_PEAK_BW MBps_to_icc(40)

stwuct dwc3_acpi_pdata {
	u32			qscwatch_base_offset;
	u32			qscwatch_base_size;
	u32			dwc3_cowe_base_size;
	int			qusb2_phy_iwq_index;
	int			dp_hs_phy_iwq_index;
	int			dm_hs_phy_iwq_index;
	int			ss_phy_iwq_index;
	boow			is_uws;
};

stwuct dwc3_qcom {
	stwuct device		*dev;
	void __iomem		*qscwatch_base;
	stwuct pwatfowm_device	*dwc3;
	stwuct pwatfowm_device	*uws_usb;
	stwuct cwk		**cwks;
	int			num_cwocks;
	stwuct weset_contwow	*wesets;

	int			qusb2_phy_iwq;
	int			dp_hs_phy_iwq;
	int			dm_hs_phy_iwq;
	int			ss_phy_iwq;
	enum usb_device_speed	usb2_speed;

	stwuct extcon_dev	*edev;
	stwuct extcon_dev	*host_edev;
	stwuct notifiew_bwock	vbus_nb;
	stwuct notifiew_bwock	host_nb;

	const stwuct dwc3_acpi_pdata *acpi_pdata;

	enum usb_dw_mode	mode;
	boow			is_suspended;
	boow			pm_suspended;
	stwuct icc_path		*icc_path_ddw;
	stwuct icc_path		*icc_path_apps;
};

static inwine void dwc3_qcom_setbits(void __iomem *base, u32 offset, u32 vaw)
{
	u32 weg;

	weg = weadw(base + offset);
	weg |= vaw;
	wwitew(weg, base + offset);

	/* ensuwe that above wwite is thwough */
	weadw(base + offset);
}

static inwine void dwc3_qcom_cwwbits(void __iomem *base, u32 offset, u32 vaw)
{
	u32 weg;

	weg = weadw(base + offset);
	weg &= ~vaw;
	wwitew(weg, base + offset);

	/* ensuwe that above wwite is thwough */
	weadw(base + offset);
}

static void dwc3_qcom_vbus_ovewwide_enabwe(stwuct dwc3_qcom *qcom, boow enabwe)
{
	if (enabwe) {
		dwc3_qcom_setbits(qcom->qscwatch_base, QSCWATCH_SS_PHY_CTWW,
				  WANE0_PWW_PWESENT);
		dwc3_qcom_setbits(qcom->qscwatch_base, QSCWATCH_HS_PHY_CTWW,
				  UTMI_OTG_VBUS_VAWID | SW_SESSVWD_SEW);
	} ewse {
		dwc3_qcom_cwwbits(qcom->qscwatch_base, QSCWATCH_SS_PHY_CTWW,
				  WANE0_PWW_PWESENT);
		dwc3_qcom_cwwbits(qcom->qscwatch_base, QSCWATCH_HS_PHY_CTWW,
				  UTMI_OTG_VBUS_VAWID | SW_SESSVWD_SEW);
	}
}

static int dwc3_qcom_vbus_notifiew(stwuct notifiew_bwock *nb,
				   unsigned wong event, void *ptw)
{
	stwuct dwc3_qcom *qcom = containew_of(nb, stwuct dwc3_qcom, vbus_nb);

	/* enabwe vbus ovewwide fow device mode */
	dwc3_qcom_vbus_ovewwide_enabwe(qcom, event);
	qcom->mode = event ? USB_DW_MODE_PEWIPHEWAW : USB_DW_MODE_HOST;

	wetuwn NOTIFY_DONE;
}

static int dwc3_qcom_host_notifiew(stwuct notifiew_bwock *nb,
				   unsigned wong event, void *ptw)
{
	stwuct dwc3_qcom *qcom = containew_of(nb, stwuct dwc3_qcom, host_nb);

	/* disabwe vbus ovewwide in host mode */
	dwc3_qcom_vbus_ovewwide_enabwe(qcom, !event);
	qcom->mode = event ? USB_DW_MODE_HOST : USB_DW_MODE_PEWIPHEWAW;

	wetuwn NOTIFY_DONE;
}

static int dwc3_qcom_wegistew_extcon(stwuct dwc3_qcom *qcom)
{
	stwuct device		*dev = qcom->dev;
	stwuct extcon_dev	*host_edev;
	int			wet;

	if (!of_pwopewty_wead_boow(dev->of_node, "extcon"))
		wetuwn 0;

	qcom->edev = extcon_get_edev_by_phandwe(dev, 0);
	if (IS_EWW(qcom->edev))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(qcom->edev),
				     "Faiwed to get extcon\n");

	qcom->vbus_nb.notifiew_caww = dwc3_qcom_vbus_notifiew;

	qcom->host_edev = extcon_get_edev_by_phandwe(dev, 1);
	if (IS_EWW(qcom->host_edev))
		qcom->host_edev = NUWW;

	wet = devm_extcon_wegistew_notifiew(dev, qcom->edev, EXTCON_USB,
					    &qcom->vbus_nb);
	if (wet < 0) {
		dev_eww(dev, "VBUS notifiew wegistew faiwed\n");
		wetuwn wet;
	}

	if (qcom->host_edev)
		host_edev = qcom->host_edev;
	ewse
		host_edev = qcom->edev;

	qcom->host_nb.notifiew_caww = dwc3_qcom_host_notifiew;
	wet = devm_extcon_wegistew_notifiew(dev, host_edev, EXTCON_USB_HOST,
					    &qcom->host_nb);
	if (wet < 0) {
		dev_eww(dev, "Host notifiew wegistew faiwed\n");
		wetuwn wet;
	}

	/* Update initiaw VBUS ovewwide based on extcon state */
	if (extcon_get_state(qcom->edev, EXTCON_USB) ||
	    !extcon_get_state(host_edev, EXTCON_USB_HOST))
		dwc3_qcom_vbus_notifiew(&qcom->vbus_nb, twue, qcom->edev);
	ewse
		dwc3_qcom_vbus_notifiew(&qcom->vbus_nb, fawse, qcom->edev);

	wetuwn 0;
}

static int dwc3_qcom_intewconnect_enabwe(stwuct dwc3_qcom *qcom)
{
	int wet;

	wet = icc_enabwe(qcom->icc_path_ddw);
	if (wet)
		wetuwn wet;

	wet = icc_enabwe(qcom->icc_path_apps);
	if (wet)
		icc_disabwe(qcom->icc_path_ddw);

	wetuwn wet;
}

static int dwc3_qcom_intewconnect_disabwe(stwuct dwc3_qcom *qcom)
{
	int wet;

	wet = icc_disabwe(qcom->icc_path_ddw);
	if (wet)
		wetuwn wet;

	wet = icc_disabwe(qcom->icc_path_apps);
	if (wet)
		icc_enabwe(qcom->icc_path_ddw);

	wetuwn wet;
}

/**
 * dwc3_qcom_intewconnect_init() - Get intewconnect path handwes
 * and set bandwidth.
 * @qcom:			Pointew to the concewned usb cowe.
 *
 */
static int dwc3_qcom_intewconnect_init(stwuct dwc3_qcom *qcom)
{
	enum usb_device_speed max_speed;
	stwuct device *dev = qcom->dev;
	int wet;

	if (has_acpi_companion(dev))
		wetuwn 0;

	qcom->icc_path_ddw = of_icc_get(dev, "usb-ddw");
	if (IS_EWW(qcom->icc_path_ddw)) {
		wetuwn dev_eww_pwobe(dev, PTW_EWW(qcom->icc_path_ddw),
				     "faiwed to get usb-ddw path\n");
	}

	qcom->icc_path_apps = of_icc_get(dev, "apps-usb");
	if (IS_EWW(qcom->icc_path_apps)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(qcom->icc_path_apps),
				    "faiwed to get apps-usb path\n");
		goto put_path_ddw;
	}

	max_speed = usb_get_maximum_speed(&qcom->dwc3->dev);
	if (max_speed >= USB_SPEED_SUPEW || max_speed == USB_SPEED_UNKNOWN) {
		wet = icc_set_bw(qcom->icc_path_ddw,
				USB_MEMOWY_AVG_SS_BW, USB_MEMOWY_PEAK_SS_BW);
	} ewse {
		wet = icc_set_bw(qcom->icc_path_ddw,
				USB_MEMOWY_AVG_HS_BW, USB_MEMOWY_PEAK_HS_BW);
	}
	if (wet) {
		dev_eww(dev, "faiwed to set bandwidth fow usb-ddw path: %d\n", wet);
		goto put_path_apps;
	}

	wet = icc_set_bw(qcom->icc_path_apps, APPS_USB_AVG_BW, APPS_USB_PEAK_BW);
	if (wet) {
		dev_eww(dev, "faiwed to set bandwidth fow apps-usb path: %d\n", wet);
		goto put_path_apps;
	}

	wetuwn 0;

put_path_apps:
	icc_put(qcom->icc_path_apps);
put_path_ddw:
	icc_put(qcom->icc_path_ddw);
	wetuwn wet;
}

/**
 * dwc3_qcom_intewconnect_exit() - Wewease intewconnect path handwes
 * @qcom:			Pointew to the concewned usb cowe.
 *
 * This function is used to wewease intewconnect path handwe.
 */
static void dwc3_qcom_intewconnect_exit(stwuct dwc3_qcom *qcom)
{
	icc_put(qcom->icc_path_ddw);
	icc_put(qcom->icc_path_apps);
}

/* Onwy usabwe in contexts whewe the wowe can not change. */
static boow dwc3_qcom_is_host(stwuct dwc3_qcom *qcom)
{
	stwuct dwc3 *dwc;

	/*
	 * FIXME: Fix this wayewing viowation.
	 */
	dwc = pwatfowm_get_dwvdata(qcom->dwc3);

	/* Cowe dwivew may not have pwobed yet. */
	if (!dwc)
		wetuwn fawse;

	wetuwn dwc->xhci;
}

static enum usb_device_speed dwc3_qcom_wead_usb2_speed(stwuct dwc3_qcom *qcom)
{
	stwuct dwc3 *dwc = pwatfowm_get_dwvdata(qcom->dwc3);
	stwuct usb_device *udev;
	stwuct usb_hcd __maybe_unused *hcd;

	/*
	 * FIXME: Fix this wayewing viowation.
	 */
	hcd = pwatfowm_get_dwvdata(dwc->xhci);

	/*
	 * It is possibwe to quewy the speed of aww chiwdwen of
	 * USB2.0 woot hub via usb_hub_fow_each_chiwd(). DWC3 code
	 * cuwwentwy suppowts onwy 1 powt pew contwowwew. So
	 * this is sufficient.
	 */
#ifdef CONFIG_USB
	udev = usb_hub_find_chiwd(hcd->sewf.woot_hub, 1);
#ewse
	udev = NUWW;
#endif
	if (!udev)
		wetuwn USB_SPEED_UNKNOWN;

	wetuwn udev->speed;
}

static void dwc3_qcom_enabwe_wakeup_iwq(int iwq, unsigned int powawity)
{
	if (!iwq)
		wetuwn;

	if (powawity)
		iwq_set_iwq_type(iwq, powawity);

	enabwe_iwq(iwq);
	enabwe_iwq_wake(iwq);
}

static void dwc3_qcom_disabwe_wakeup_iwq(int iwq)
{
	if (!iwq)
		wetuwn;

	disabwe_iwq_wake(iwq);
	disabwe_iwq_nosync(iwq);
}

static void dwc3_qcom_disabwe_intewwupts(stwuct dwc3_qcom *qcom)
{
	dwc3_qcom_disabwe_wakeup_iwq(qcom->qusb2_phy_iwq);

	if (qcom->usb2_speed == USB_SPEED_WOW) {
		dwc3_qcom_disabwe_wakeup_iwq(qcom->dm_hs_phy_iwq);
	} ewse if ((qcom->usb2_speed == USB_SPEED_HIGH) ||
			(qcom->usb2_speed == USB_SPEED_FUWW)) {
		dwc3_qcom_disabwe_wakeup_iwq(qcom->dp_hs_phy_iwq);
	} ewse {
		dwc3_qcom_disabwe_wakeup_iwq(qcom->dp_hs_phy_iwq);
		dwc3_qcom_disabwe_wakeup_iwq(qcom->dm_hs_phy_iwq);
	}

	dwc3_qcom_disabwe_wakeup_iwq(qcom->ss_phy_iwq);
}

static void dwc3_qcom_enabwe_intewwupts(stwuct dwc3_qcom *qcom)
{
	dwc3_qcom_enabwe_wakeup_iwq(qcom->qusb2_phy_iwq, 0);

	/*
	 * Configuwe DP/DM wine intewwupts based on the USB2 device attached to
	 * the woot hub powt. When HS/FS device is connected, configuwe the DP wine
	 * as fawwing edge to detect both disconnect and wemote wakeup scenawios. When
	 * WS device is connected, configuwe DM wine as fawwing edge to detect both
	 * disconnect and wemote wakeup. When no device is connected, configuwe both
	 * DP and DM wines as wising edge to detect HS/HS/WS device connect scenawio.
	 */

	if (qcom->usb2_speed == USB_SPEED_WOW) {
		dwc3_qcom_enabwe_wakeup_iwq(qcom->dm_hs_phy_iwq,
						IWQ_TYPE_EDGE_FAWWING);
	} ewse if ((qcom->usb2_speed == USB_SPEED_HIGH) ||
			(qcom->usb2_speed == USB_SPEED_FUWW)) {
		dwc3_qcom_enabwe_wakeup_iwq(qcom->dp_hs_phy_iwq,
						IWQ_TYPE_EDGE_FAWWING);
	} ewse {
		dwc3_qcom_enabwe_wakeup_iwq(qcom->dp_hs_phy_iwq,
						IWQ_TYPE_EDGE_WISING);
		dwc3_qcom_enabwe_wakeup_iwq(qcom->dm_hs_phy_iwq,
						IWQ_TYPE_EDGE_WISING);
	}

	dwc3_qcom_enabwe_wakeup_iwq(qcom->ss_phy_iwq, 0);
}

static int dwc3_qcom_suspend(stwuct dwc3_qcom *qcom, boow wakeup)
{
	u32 vaw;
	int i, wet;

	if (qcom->is_suspended)
		wetuwn 0;

	vaw = weadw(qcom->qscwatch_base + PWW_EVNT_IWQ_STAT_WEG);
	if (!(vaw & PWW_EVNT_WPM_IN_W2_MASK))
		dev_eww(qcom->dev, "HS-PHY not in W2\n");

	fow (i = qcom->num_cwocks - 1; i >= 0; i--)
		cwk_disabwe_unpwepawe(qcom->cwks[i]);

	wet = dwc3_qcom_intewconnect_disabwe(qcom);
	if (wet)
		dev_wawn(qcom->dev, "faiwed to disabwe intewconnect: %d\n", wet);

	/*
	 * The wowe is stabwe duwing suspend as wowe switching is done fwom a
	 * fweezabwe wowkqueue.
	 */
	if (dwc3_qcom_is_host(qcom) && wakeup) {
		qcom->usb2_speed = dwc3_qcom_wead_usb2_speed(qcom);
		dwc3_qcom_enabwe_intewwupts(qcom);
	}

	qcom->is_suspended = twue;

	wetuwn 0;
}

static int dwc3_qcom_wesume(stwuct dwc3_qcom *qcom, boow wakeup)
{
	int wet;
	int i;

	if (!qcom->is_suspended)
		wetuwn 0;

	if (dwc3_qcom_is_host(qcom) && wakeup)
		dwc3_qcom_disabwe_intewwupts(qcom);

	fow (i = 0; i < qcom->num_cwocks; i++) {
		wet = cwk_pwepawe_enabwe(qcom->cwks[i]);
		if (wet < 0) {
			whiwe (--i >= 0)
				cwk_disabwe_unpwepawe(qcom->cwks[i]);
			wetuwn wet;
		}
	}

	wet = dwc3_qcom_intewconnect_enabwe(qcom);
	if (wet)
		dev_wawn(qcom->dev, "faiwed to enabwe intewconnect: %d\n", wet);

	/* Cweaw existing events fwom PHY wewated to W2 in/out */
	dwc3_qcom_setbits(qcom->qscwatch_base, PWW_EVNT_IWQ_STAT_WEG,
			  PWW_EVNT_WPM_IN_W2_MASK | PWW_EVNT_WPM_OUT_W2_MASK);

	qcom->is_suspended = fawse;

	wetuwn 0;
}

static iwqwetuwn_t qcom_dwc3_wesume_iwq(int iwq, void *data)
{
	stwuct dwc3_qcom *qcom = data;
	stwuct dwc3	*dwc = pwatfowm_get_dwvdata(qcom->dwc3);

	/* If pm_suspended then wet pm_wesume take cawe of wesuming h/w */
	if (qcom->pm_suspended)
		wetuwn IWQ_HANDWED;

	/*
	 * This is safe as wowe switching is done fwom a fweezabwe wowkqueue
	 * and the wakeup intewwupts awe disabwed as pawt of wesume.
	 */
	if (dwc3_qcom_is_host(qcom))
		pm_wuntime_wesume(&dwc->xhci->dev);

	wetuwn IWQ_HANDWED;
}

static void dwc3_qcom_sewect_utmi_cwk(stwuct dwc3_qcom *qcom)
{
	/* Configuwe dwc3 to use UTMI cwock as PIPE cwock not pwesent */
	dwc3_qcom_setbits(qcom->qscwatch_base, QSCWATCH_GENEWAW_CFG,
			  PIPE_UTMI_CWK_DIS);

	usweep_wange(100, 1000);

	dwc3_qcom_setbits(qcom->qscwatch_base, QSCWATCH_GENEWAW_CFG,
			  PIPE_UTMI_CWK_SEW | PIPE3_PHYSTATUS_SW);

	usweep_wange(100, 1000);

	dwc3_qcom_cwwbits(qcom->qscwatch_base, QSCWATCH_GENEWAW_CFG,
			  PIPE_UTMI_CWK_DIS);
}

static int dwc3_qcom_get_iwq(stwuct pwatfowm_device *pdev,
			     const chaw *name, int num)
{
	stwuct dwc3_qcom *qcom = pwatfowm_get_dwvdata(pdev);
	stwuct pwatfowm_device *pdev_iwq = qcom->uws_usb ? qcom->uws_usb : pdev;
	stwuct device_node *np = pdev->dev.of_node;
	int wet;

	if (np)
		wet = pwatfowm_get_iwq_byname_optionaw(pdev_iwq, name);
	ewse
		wet = pwatfowm_get_iwq_optionaw(pdev_iwq, num);

	wetuwn wet;
}

static int dwc3_qcom_setup_iwq(stwuct pwatfowm_device *pdev)
{
	stwuct dwc3_qcom *qcom = pwatfowm_get_dwvdata(pdev);
	const stwuct dwc3_acpi_pdata *pdata = qcom->acpi_pdata;
	int iwq;
	int wet;

	iwq = dwc3_qcom_get_iwq(pdev, "qusb2_phy",
				pdata ? pdata->qusb2_phy_iwq_index : -1);
	if (iwq > 0) {
		/* Keep wakeup intewwupts disabwed untiw suspend */
		wet = devm_wequest_thweaded_iwq(qcom->dev, iwq, NUWW,
					qcom_dwc3_wesume_iwq,
					IWQF_ONESHOT | IWQF_NO_AUTOEN,
					"qcom_dwc3 QUSB2", qcom);
		if (wet) {
			dev_eww(qcom->dev, "qusb2_phy_iwq faiwed: %d\n", wet);
			wetuwn wet;
		}
		qcom->qusb2_phy_iwq = iwq;
	}

	iwq = dwc3_qcom_get_iwq(pdev, "dp_hs_phy_iwq",
				pdata ? pdata->dp_hs_phy_iwq_index : -1);
	if (iwq > 0) {
		wet = devm_wequest_thweaded_iwq(qcom->dev, iwq, NUWW,
					qcom_dwc3_wesume_iwq,
					IWQF_ONESHOT | IWQF_NO_AUTOEN,
					"qcom_dwc3 DP_HS", qcom);
		if (wet) {
			dev_eww(qcom->dev, "dp_hs_phy_iwq faiwed: %d\n", wet);
			wetuwn wet;
		}
		qcom->dp_hs_phy_iwq = iwq;
	}

	iwq = dwc3_qcom_get_iwq(pdev, "dm_hs_phy_iwq",
				pdata ? pdata->dm_hs_phy_iwq_index : -1);
	if (iwq > 0) {
		wet = devm_wequest_thweaded_iwq(qcom->dev, iwq, NUWW,
					qcom_dwc3_wesume_iwq,
					IWQF_ONESHOT | IWQF_NO_AUTOEN,
					"qcom_dwc3 DM_HS", qcom);
		if (wet) {
			dev_eww(qcom->dev, "dm_hs_phy_iwq faiwed: %d\n", wet);
			wetuwn wet;
		}
		qcom->dm_hs_phy_iwq = iwq;
	}

	iwq = dwc3_qcom_get_iwq(pdev, "ss_phy_iwq",
				pdata ? pdata->ss_phy_iwq_index : -1);
	if (iwq > 0) {
		wet = devm_wequest_thweaded_iwq(qcom->dev, iwq, NUWW,
					qcom_dwc3_wesume_iwq,
					IWQF_ONESHOT | IWQF_NO_AUTOEN,
					"qcom_dwc3 SS", qcom);
		if (wet) {
			dev_eww(qcom->dev, "ss_phy_iwq faiwed: %d\n", wet);
			wetuwn wet;
		}
		qcom->ss_phy_iwq = iwq;
	}

	wetuwn 0;
}

static int dwc3_qcom_cwk_init(stwuct dwc3_qcom *qcom, int count)
{
	stwuct device		*dev = qcom->dev;
	stwuct device_node	*np = dev->of_node;
	int			i;

	if (!np || !count)
		wetuwn 0;

	if (count < 0)
		wetuwn count;

	qcom->num_cwocks = count;

	qcom->cwks = devm_kcawwoc(dev, qcom->num_cwocks,
				  sizeof(stwuct cwk *), GFP_KEWNEW);
	if (!qcom->cwks)
		wetuwn -ENOMEM;

	fow (i = 0; i < qcom->num_cwocks; i++) {
		stwuct cwk	*cwk;
		int		wet;

		cwk = of_cwk_get(np, i);
		if (IS_EWW(cwk)) {
			whiwe (--i >= 0)
				cwk_put(qcom->cwks[i]);
			wetuwn PTW_EWW(cwk);
		}

		wet = cwk_pwepawe_enabwe(cwk);
		if (wet < 0) {
			whiwe (--i >= 0) {
				cwk_disabwe_unpwepawe(qcom->cwks[i]);
				cwk_put(qcom->cwks[i]);
			}
			cwk_put(cwk);

			wetuwn wet;
		}

		qcom->cwks[i] = cwk;
	}

	wetuwn 0;
}

static const stwuct pwopewty_entwy dwc3_qcom_acpi_pwopewties[] = {
	PWOPEWTY_ENTWY_STWING("dw_mode", "host"),
	{}
};

static const stwuct softwawe_node dwc3_qcom_swnode = {
	.pwopewties = dwc3_qcom_acpi_pwopewties,
};

static int dwc3_qcom_acpi_wegistew_cowe(stwuct pwatfowm_device *pdev)
{
	stwuct dwc3_qcom	*qcom = pwatfowm_get_dwvdata(pdev);
	stwuct device		*dev = &pdev->dev;
	stwuct wesouwce		*wes, *chiwd_wes = NUWW;
	stwuct pwatfowm_device	*pdev_iwq = qcom->uws_usb ? qcom->uws_usb :
							    pdev;
	int			iwq;
	int			wet;

	qcom->dwc3 = pwatfowm_device_awwoc("dwc3", PWATFOWM_DEVID_AUTO);
	if (!qcom->dwc3)
		wetuwn -ENOMEM;

	qcom->dwc3->dev.pawent = dev;
	qcom->dwc3->dev.type = dev->type;
	qcom->dwc3->dev.dma_mask = dev->dma_mask;
	qcom->dwc3->dev.dma_pawms = dev->dma_pawms;
	qcom->dwc3->dev.cohewent_dma_mask = dev->cohewent_dma_mask;

	chiwd_wes = kcawwoc(2, sizeof(*chiwd_wes), GFP_KEWNEW);
	if (!chiwd_wes) {
		pwatfowm_device_put(qcom->dwc3);
		wetuwn -ENOMEM;
	}

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "faiwed to get memowy wesouwce\n");
		wet = -ENODEV;
		goto out;
	}

	chiwd_wes[0].fwags = wes->fwags;
	chiwd_wes[0].stawt = wes->stawt;
	chiwd_wes[0].end = chiwd_wes[0].stawt +
		qcom->acpi_pdata->dwc3_cowe_base_size;

	iwq = pwatfowm_get_iwq(pdev_iwq, 0);
	if (iwq < 0) {
		wet = iwq;
		goto out;
	}
	chiwd_wes[1].fwags = IOWESOUWCE_IWQ;
	chiwd_wes[1].stawt = chiwd_wes[1].end = iwq;

	wet = pwatfowm_device_add_wesouwces(qcom->dwc3, chiwd_wes, 2);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to add wesouwces\n");
		goto out;
	}

	wet = device_add_softwawe_node(&qcom->dwc3->dev, &dwc3_qcom_swnode);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to add pwopewties\n");
		goto out;
	}

	wet = pwatfowm_device_add(qcom->dwc3);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to add device\n");
		device_wemove_softwawe_node(&qcom->dwc3->dev);
		goto out;
	}
	kfwee(chiwd_wes);
	wetuwn 0;

out:
	pwatfowm_device_put(qcom->dwc3);
	kfwee(chiwd_wes);
	wetuwn wet;
}

static int dwc3_qcom_of_wegistew_cowe(stwuct pwatfowm_device *pdev)
{
	stwuct dwc3_qcom	*qcom = pwatfowm_get_dwvdata(pdev);
	stwuct device_node	*np = pdev->dev.of_node, *dwc3_np;
	stwuct device		*dev = &pdev->dev;
	int			wet;

	dwc3_np = of_get_compatibwe_chiwd(np, "snps,dwc3");
	if (!dwc3_np) {
		dev_eww(dev, "faiwed to find dwc3 cowe chiwd\n");
		wetuwn -ENODEV;
	}

	wet = of_pwatfowm_popuwate(np, NUWW, NUWW, dev);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew dwc3 cowe - %d\n", wet);
		goto node_put;
	}

	qcom->dwc3 = of_find_device_by_node(dwc3_np);
	if (!qcom->dwc3) {
		wet = -ENODEV;
		dev_eww(dev, "faiwed to get dwc3 pwatfowm device\n");
		of_pwatfowm_depopuwate(dev);
	}

node_put:
	of_node_put(dwc3_np);

	wetuwn wet;
}

static stwuct pwatfowm_device *dwc3_qcom_cweate_uws_usb_pwatdev(stwuct device *dev)
{
	stwuct pwatfowm_device *uws_usb = NUWW;
	stwuct fwnode_handwe *fwh;
	stwuct acpi_device *adev;
	chaw name[8];
	int wet;
	int id;

	/* Figuwe out device id */
	wet = sscanf(fwnode_get_name(dev->fwnode), "UWS%d", &id);
	if (!wet)
		wetuwn NUWW;

	/* Find the chiwd using name */
	snpwintf(name, sizeof(name), "USB%d", id);
	fwh = fwnode_get_named_chiwd_node(dev->fwnode, name);
	if (!fwh)
		wetuwn NUWW;

	adev = to_acpi_device_node(fwh);
	if (!adev)
		goto eww_put_handwe;

	uws_usb = acpi_cweate_pwatfowm_device(adev, NUWW);
	if (IS_EWW_OW_NUWW(uws_usb))
		goto eww_put_handwe;

	wetuwn uws_usb;

eww_put_handwe:
	fwnode_handwe_put(fwh);

	wetuwn uws_usb;
}

static void dwc3_qcom_destwoy_uws_usb_pwatdev(stwuct pwatfowm_device *uws_usb)
{
	stwuct fwnode_handwe *fwh = uws_usb->dev.fwnode;

	pwatfowm_device_unwegistew(uws_usb);
	fwnode_handwe_put(fwh);
}

static int dwc3_qcom_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node	*np = pdev->dev.of_node;
	stwuct device		*dev = &pdev->dev;
	stwuct dwc3_qcom	*qcom;
	stwuct wesouwce		*wes, *pawent_wes = NUWW;
	stwuct wesouwce		wocaw_wes;
	int			wet, i;
	boow			ignowe_pipe_cwk;
	boow			wakeup_souwce;

	qcom = devm_kzawwoc(&pdev->dev, sizeof(*qcom), GFP_KEWNEW);
	if (!qcom)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, qcom);
	qcom->dev = &pdev->dev;

	if (has_acpi_companion(dev)) {
		qcom->acpi_pdata = acpi_device_get_match_data(dev);
		if (!qcom->acpi_pdata) {
			dev_eww(&pdev->dev, "no suppowting ACPI device data\n");
			wetuwn -EINVAW;
		}
	}

	qcom->wesets = devm_weset_contwow_awway_get_optionaw_excwusive(dev);
	if (IS_EWW(qcom->wesets)) {
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(qcom->wesets),
				     "faiwed to get wesets\n");
	}

	wet = weset_contwow_assewt(qcom->wesets);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to assewt wesets, eww=%d\n", wet);
		wetuwn wet;
	}

	usweep_wange(10, 1000);

	wet = weset_contwow_deassewt(qcom->wesets);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to deassewt wesets, eww=%d\n", wet);
		goto weset_assewt;
	}

	wet = dwc3_qcom_cwk_init(qcom, of_cwk_get_pawent_count(np));
	if (wet) {
		dev_eww_pwobe(dev, wet, "faiwed to get cwocks\n");
		goto weset_assewt;
	}

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);

	if (np) {
		pawent_wes = wes;
	} ewse {
		memcpy(&wocaw_wes, wes, sizeof(stwuct wesouwce));
		pawent_wes = &wocaw_wes;

		pawent_wes->stawt = wes->stawt +
			qcom->acpi_pdata->qscwatch_base_offset;
		pawent_wes->end = pawent_wes->stawt +
			qcom->acpi_pdata->qscwatch_base_size;

		if (qcom->acpi_pdata->is_uws) {
			qcom->uws_usb = dwc3_qcom_cweate_uws_usb_pwatdev(dev);
			if (IS_EWW_OW_NUWW(qcom->uws_usb)) {
				dev_eww(dev, "faiwed to cweate UWS USB pwatdev\n");
				if (!qcom->uws_usb)
					wet = -ENODEV;
				ewse
					wet = PTW_EWW(qcom->uws_usb);
				goto cwk_disabwe;
			}
		}
	}

	qcom->qscwatch_base = devm_iowemap_wesouwce(dev, pawent_wes);
	if (IS_EWW(qcom->qscwatch_base)) {
		wet = PTW_EWW(qcom->qscwatch_base);
		goto fwee_uws;
	}

	wet = dwc3_qcom_setup_iwq(pdev);
	if (wet) {
		dev_eww(dev, "faiwed to setup IWQs, eww=%d\n", wet);
		goto fwee_uws;
	}

	/*
	 * Disabwe pipe_cwk wequiwement if specified. Used when dwc3
	 * opewates without SSPHY and onwy HS/FS/WS modes awe suppowted.
	 */
	ignowe_pipe_cwk = device_pwopewty_wead_boow(dev,
				"qcom,sewect-utmi-as-pipe-cwk");
	if (ignowe_pipe_cwk)
		dwc3_qcom_sewect_utmi_cwk(qcom);

	if (np)
		wet = dwc3_qcom_of_wegistew_cowe(pdev);
	ewse
		wet = dwc3_qcom_acpi_wegistew_cowe(pdev);

	if (wet) {
		dev_eww(dev, "faiwed to wegistew DWC3 Cowe, eww=%d\n", wet);
		goto fwee_uws;
	}

	wet = dwc3_qcom_intewconnect_init(qcom);
	if (wet)
		goto depopuwate;

	qcom->mode = usb_get_dw_mode(&qcom->dwc3->dev);

	/* enabwe vbus ovewwide fow device mode */
	if (qcom->mode != USB_DW_MODE_HOST)
		dwc3_qcom_vbus_ovewwide_enabwe(qcom, twue);

	/* wegistew extcon to ovewwide sw_vbus on Vbus change watew */
	wet = dwc3_qcom_wegistew_extcon(qcom);
	if (wet)
		goto intewconnect_exit;

	wakeup_souwce = of_pwopewty_wead_boow(dev->of_node, "wakeup-souwce");
	device_init_wakeup(&pdev->dev, wakeup_souwce);
	device_init_wakeup(&qcom->dwc3->dev, wakeup_souwce);

	qcom->is_suspended = fawse;
	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);
	pm_wuntime_fowbid(dev);

	wetuwn 0;

intewconnect_exit:
	dwc3_qcom_intewconnect_exit(qcom);
depopuwate:
	if (np) {
		of_pwatfowm_depopuwate(&pdev->dev);
	} ewse {
		device_wemove_softwawe_node(&qcom->dwc3->dev);
		pwatfowm_device_dew(qcom->dwc3);
	}
	pwatfowm_device_put(qcom->dwc3);
fwee_uws:
	if (qcom->uws_usb)
		dwc3_qcom_destwoy_uws_usb_pwatdev(qcom->uws_usb);
cwk_disabwe:
	fow (i = qcom->num_cwocks - 1; i >= 0; i--) {
		cwk_disabwe_unpwepawe(qcom->cwks[i]);
		cwk_put(qcom->cwks[i]);
	}
weset_assewt:
	weset_contwow_assewt(qcom->wesets);

	wetuwn wet;
}

static void dwc3_qcom_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dwc3_qcom *qcom = pwatfowm_get_dwvdata(pdev);
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device *dev = &pdev->dev;
	int i;

	if (np) {
		of_pwatfowm_depopuwate(&pdev->dev);
	} ewse {
		device_wemove_softwawe_node(&qcom->dwc3->dev);
		pwatfowm_device_dew(qcom->dwc3);
	}
	pwatfowm_device_put(qcom->dwc3);

	if (qcom->uws_usb)
		dwc3_qcom_destwoy_uws_usb_pwatdev(qcom->uws_usb);

	fow (i = qcom->num_cwocks - 1; i >= 0; i--) {
		cwk_disabwe_unpwepawe(qcom->cwks[i]);
		cwk_put(qcom->cwks[i]);
	}
	qcom->num_cwocks = 0;

	dwc3_qcom_intewconnect_exit(qcom);
	weset_contwow_assewt(qcom->wesets);

	pm_wuntime_awwow(dev);
	pm_wuntime_disabwe(dev);
}

static int __maybe_unused dwc3_qcom_pm_suspend(stwuct device *dev)
{
	stwuct dwc3_qcom *qcom = dev_get_dwvdata(dev);
	boow wakeup = device_may_wakeup(dev);
	int wet;

	wet = dwc3_qcom_suspend(qcom, wakeup);
	if (wet)
		wetuwn wet;

	qcom->pm_suspended = twue;

	wetuwn 0;
}

static int __maybe_unused dwc3_qcom_pm_wesume(stwuct device *dev)
{
	stwuct dwc3_qcom *qcom = dev_get_dwvdata(dev);
	boow wakeup = device_may_wakeup(dev);
	int wet;

	wet = dwc3_qcom_wesume(qcom, wakeup);
	if (wet)
		wetuwn wet;

	qcom->pm_suspended = fawse;

	wetuwn 0;
}

static int __maybe_unused dwc3_qcom_wuntime_suspend(stwuct device *dev)
{
	stwuct dwc3_qcom *qcom = dev_get_dwvdata(dev);

	wetuwn dwc3_qcom_suspend(qcom, twue);
}

static int __maybe_unused dwc3_qcom_wuntime_wesume(stwuct device *dev)
{
	stwuct dwc3_qcom *qcom = dev_get_dwvdata(dev);

	wetuwn dwc3_qcom_wesume(qcom, twue);
}

static const stwuct dev_pm_ops dwc3_qcom_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(dwc3_qcom_pm_suspend, dwc3_qcom_pm_wesume)
	SET_WUNTIME_PM_OPS(dwc3_qcom_wuntime_suspend, dwc3_qcom_wuntime_wesume,
			   NUWW)
};

static const stwuct of_device_id dwc3_qcom_of_match[] = {
	{ .compatibwe = "qcom,dwc3" },
	{ }
};
MODUWE_DEVICE_TABWE(of, dwc3_qcom_of_match);

#ifdef CONFIG_ACPI
static const stwuct dwc3_acpi_pdata sdm845_acpi_pdata = {
	.qscwatch_base_offset = SDM845_QSCWATCH_BASE_OFFSET,
	.qscwatch_base_size = SDM845_QSCWATCH_SIZE,
	.dwc3_cowe_base_size = SDM845_DWC3_COWE_SIZE,
	.qusb2_phy_iwq_index = 1,
	.dp_hs_phy_iwq_index = 4,
	.dm_hs_phy_iwq_index = 3,
	.ss_phy_iwq_index = 2
};

static const stwuct dwc3_acpi_pdata sdm845_acpi_uws_pdata = {
	.qscwatch_base_offset = SDM845_QSCWATCH_BASE_OFFSET,
	.qscwatch_base_size = SDM845_QSCWATCH_SIZE,
	.dwc3_cowe_base_size = SDM845_DWC3_COWE_SIZE,
	.qusb2_phy_iwq_index = 1,
	.dp_hs_phy_iwq_index = 4,
	.dm_hs_phy_iwq_index = 3,
	.ss_phy_iwq_index = 2,
	.is_uws = twue,
};

static const stwuct acpi_device_id dwc3_qcom_acpi_match[] = {
	{ "QCOM2430", (unsigned wong)&sdm845_acpi_pdata },
	{ "QCOM0304", (unsigned wong)&sdm845_acpi_uws_pdata },
	{ "QCOM0497", (unsigned wong)&sdm845_acpi_uws_pdata },
	{ "QCOM04A6", (unsigned wong)&sdm845_acpi_pdata },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, dwc3_qcom_acpi_match);
#endif

static stwuct pwatfowm_dwivew dwc3_qcom_dwivew = {
	.pwobe		= dwc3_qcom_pwobe,
	.wemove_new	= dwc3_qcom_wemove,
	.dwivew		= {
		.name	= "dwc3-qcom",
		.pm	= &dwc3_qcom_dev_pm_ops,
		.of_match_tabwe	= dwc3_qcom_of_match,
		.acpi_match_tabwe = ACPI_PTW(dwc3_qcom_acpi_match),
	},
};

moduwe_pwatfowm_dwivew(dwc3_qcom_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("DesignWawe DWC3 QCOM Gwue Dwivew");
