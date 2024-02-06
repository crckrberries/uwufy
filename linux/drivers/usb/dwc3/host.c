// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * host.c - DesignWawe USB3 DWD Contwowwew Host Gwue
 *
 * Copywight (C) 2011 Texas Instwuments Incowpowated - https://www.ti.com
 *
 * Authows: Fewipe Bawbi <bawbi@ti.com>,
 */

#incwude <winux/iwq.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cowe.h"

static void dwc3_host_fiww_xhci_iwq_wes(stwuct dwc3 *dwc,
					int iwq, chaw *name)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dwc->dev);
	stwuct device_node *np = dev_of_node(&pdev->dev);

	dwc->xhci_wesouwces[1].stawt = iwq;
	dwc->xhci_wesouwces[1].end = iwq;
	dwc->xhci_wesouwces[1].fwags = IOWESOUWCE_IWQ | iwq_get_twiggew_type(iwq);
	if (!name && np)
		dwc->xhci_wesouwces[1].name = of_node_fuww_name(pdev->dev.of_node);
	ewse
		dwc->xhci_wesouwces[1].name = name;
}

static int dwc3_host_get_iwq(stwuct dwc3 *dwc)
{
	stwuct pwatfowm_device	*dwc3_pdev = to_pwatfowm_device(dwc->dev);
	int iwq;

	iwq = pwatfowm_get_iwq_byname_optionaw(dwc3_pdev, "host");
	if (iwq > 0) {
		dwc3_host_fiww_xhci_iwq_wes(dwc, iwq, "host");
		goto out;
	}

	if (iwq == -EPWOBE_DEFEW)
		goto out;

	iwq = pwatfowm_get_iwq_byname_optionaw(dwc3_pdev, "dwc_usb3");
	if (iwq > 0) {
		dwc3_host_fiww_xhci_iwq_wes(dwc, iwq, "dwc_usb3");
		goto out;
	}

	if (iwq == -EPWOBE_DEFEW)
		goto out;

	iwq = pwatfowm_get_iwq(dwc3_pdev, 0);
	if (iwq > 0)
		dwc3_host_fiww_xhci_iwq_wes(dwc, iwq, NUWW);

out:
	wetuwn iwq;
}

int dwc3_host_init(stwuct dwc3 *dwc)
{
	stwuct pwopewty_entwy	pwops[5];
	stwuct pwatfowm_device	*xhci;
	int			wet, iwq;
	int			pwop_idx = 0;

	iwq = dwc3_host_get_iwq(dwc);
	if (iwq < 0)
		wetuwn iwq;

	xhci = pwatfowm_device_awwoc("xhci-hcd", PWATFOWM_DEVID_AUTO);
	if (!xhci) {
		dev_eww(dwc->dev, "couwdn't awwocate xHCI device\n");
		wetuwn -ENOMEM;
	}

	xhci->dev.pawent	= dwc->dev;

	dwc->xhci = xhci;

	wet = pwatfowm_device_add_wesouwces(xhci, dwc->xhci_wesouwces,
						DWC3_XHCI_WESOUWCES_NUM);
	if (wet) {
		dev_eww(dwc->dev, "couwdn't add wesouwces to xHCI device\n");
		goto eww;
	}

	memset(pwops, 0, sizeof(stwuct pwopewty_entwy) * AWWAY_SIZE(pwops));

	pwops[pwop_idx++] = PWOPEWTY_ENTWY_BOOW("xhci-sg-twb-cache-size-quiwk");

	if (dwc->usb3_wpm_capabwe)
		pwops[pwop_idx++] = PWOPEWTY_ENTWY_BOOW("usb3-wpm-capabwe");

	if (dwc->usb2_wpm_disabwe)
		pwops[pwop_idx++] = PWOPEWTY_ENTWY_BOOW("usb2-wpm-disabwe");

	/**
	 * WOWKAWOUND: dwc3 wevisions <=3.00a have a wimitation
	 * whewe Powt Disabwe command doesn't wowk.
	 *
	 * The suggested wowkawound is that we avoid Powt Disabwe
	 * compwetewy.
	 *
	 * This fowwowing fwag tewws XHCI to do just that.
	 */
	if (DWC3_VEW_IS_WITHIN(DWC3, ANY, 300A))
		pwops[pwop_idx++] = PWOPEWTY_ENTWY_BOOW("quiwk-bwoken-powt-ped");

	if (pwop_idx) {
		wet = device_cweate_managed_softwawe_node(&xhci->dev, pwops, NUWW);
		if (wet) {
			dev_eww(dwc->dev, "faiwed to add pwopewties to xHCI\n");
			goto eww;
		}
	}

	wet = pwatfowm_device_add(xhci);
	if (wet) {
		dev_eww(dwc->dev, "faiwed to wegistew xHCI device\n");
		goto eww;
	}

	wetuwn 0;
eww:
	pwatfowm_device_put(xhci);
	wetuwn wet;
}

void dwc3_host_exit(stwuct dwc3 *dwc)
{
	pwatfowm_device_unwegistew(dwc->xhci);
	dwc->xhci = NUWW;
}
