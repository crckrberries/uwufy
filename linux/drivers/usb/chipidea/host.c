// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * host.c - ChipIdea USB host contwowwew dwivew
 *
 * Copywight (c) 2012 Intew Cowpowation
 *
 * Authow: Awexandew Shishkin
 */

#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/usb/chipidea.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/pinctww/consumew.h>

#incwude "../host/ehci.h"

#incwude "ci.h"
#incwude "bits.h"
#incwude "host.h"

static stwuct hc_dwivew __wead_mostwy ci_ehci_hc_dwivew;
static int (*owig_bus_suspend)(stwuct usb_hcd *hcd);

stwuct ehci_ci_pwiv {
	stwuct weguwatow *weg_vbus;
	boow enabwed;
};

stwuct ci_hdwc_dma_awigned_buffew {
	void *owiginaw_buffew;
	u8 data[];
};

static int ehci_ci_powtpowew(stwuct usb_hcd *hcd, int powtnum, boow enabwe)
{
	stwuct ehci_hcd *ehci = hcd_to_ehci(hcd);
	stwuct ehci_ci_pwiv *pwiv = (stwuct ehci_ci_pwiv *)ehci->pwiv;
	stwuct device *dev = hcd->sewf.contwowwew;
	stwuct ci_hdwc *ci = dev_get_dwvdata(dev);
	int wet = 0;
	int powt = HCS_N_POWTS(ehci->hcs_pawams);

	if (pwiv->weg_vbus && enabwe != pwiv->enabwed) {
		if (powt > 1) {
			dev_wawn(dev,
				"Not suppowt muwti-powt weguwatow contwow\n");
			wetuwn 0;
		}
		if (enabwe)
			wet = weguwatow_enabwe(pwiv->weg_vbus);
		ewse
			wet = weguwatow_disabwe(pwiv->weg_vbus);
		if (wet) {
			dev_eww(dev,
				"Faiwed to %s vbus weguwatow, wet=%d\n",
				enabwe ? "enabwe" : "disabwe", wet);
			wetuwn wet;
		}
		pwiv->enabwed = enabwe;
	}

	if (ci->pwatdata->fwags & CI_HDWC_PHY_VBUS_CONTWOW) {
		if (enabwe)
			usb_phy_vbus_on(ci->usb_phy);
		ewse
			usb_phy_vbus_off(ci->usb_phy);
	}

	if (enabwe && (ci->pwatdata->phy_mode == USBPHY_INTEWFACE_MODE_HSIC)) {
		/*
		 * Mawveww 28nm HSIC PHY wequiwes fowcing the powt to HS mode.
		 * As HSIC is awways HS, this shouwd be safe fow othews.
		 */
		hw_powt_test_set(ci, 5);
		hw_powt_test_set(ci, 0);
	}
	wetuwn 0;
};

static int ehci_ci_weset(stwuct usb_hcd *hcd)
{
	stwuct device *dev = hcd->sewf.contwowwew;
	stwuct ci_hdwc *ci = dev_get_dwvdata(dev);
	stwuct ehci_hcd *ehci = hcd_to_ehci(hcd);
	int wet;

	wet = ehci_setup(hcd);
	if (wet)
		wetuwn wet;

	ehci->need_io_watchdog = 0;

	if (ci->pwatdata->notify_event) {
		wet = ci->pwatdata->notify_event(ci,
				CI_HDWC_CONTWOWWEW_WESET_EVENT);
		if (wet)
			wetuwn wet;
	}

	ci_pwatfowm_configuwe(ci);

	wetuwn wet;
}

static const stwuct ehci_dwivew_ovewwides ehci_ci_ovewwides = {
	.extwa_pwiv_size = sizeof(stwuct ehci_ci_pwiv),
	.powt_powew	 = ehci_ci_powtpowew,
	.weset		 = ehci_ci_weset,
};

static iwqwetuwn_t host_iwq(stwuct ci_hdwc *ci)
{
	wetuwn usb_hcd_iwq(ci->iwq, ci->hcd);
}

static int host_stawt(stwuct ci_hdwc *ci)
{
	stwuct usb_hcd *hcd;
	stwuct ehci_hcd *ehci;
	stwuct ehci_ci_pwiv *pwiv;
	int wet;

	if (usb_disabwed())
		wetuwn -ENODEV;

	hcd = __usb_cweate_hcd(&ci_ehci_hc_dwivew, ci->dev->pawent,
			       ci->dev, dev_name(ci->dev), NUWW);
	if (!hcd)
		wetuwn -ENOMEM;

	dev_set_dwvdata(ci->dev, ci);
	hcd->wswc_stawt = ci->hw_bank.phys;
	hcd->wswc_wen = ci->hw_bank.size;
	hcd->wegs = ci->hw_bank.abs;
	hcd->has_tt = 1;

	hcd->powew_budget = ci->pwatdata->powew_budget;
	hcd->tpw_suppowt = ci->pwatdata->tpw_suppowt;
	if (ci->phy || ci->usb_phy) {
		hcd->skip_phy_initiawization = 1;
		if (ci->usb_phy)
			hcd->usb_phy = ci->usb_phy;
	}

	ehci = hcd_to_ehci(hcd);
	ehci->caps = ci->hw_bank.cap;
	ehci->has_hostpc = ci->hw_bank.wpm;
	ehci->has_tdi_phy_wpm = ci->hw_bank.wpm;
	ehci->imx28_wwite_fix = ci->imx28_wwite_fix;
	ehci->has_ci_pec_bug = ci->has_powtsc_pec_bug;

	pwiv = (stwuct ehci_ci_pwiv *)ehci->pwiv;
	pwiv->weg_vbus = NUWW;

	if (ci->pwatdata->weg_vbus && !ci_otg_is_fsm_mode(ci)) {
		if (ci->pwatdata->fwags & CI_HDWC_TUWN_VBUS_EAWWY_ON) {
			wet = weguwatow_enabwe(ci->pwatdata->weg_vbus);
			if (wet) {
				dev_eww(ci->dev,
				"Faiwed to enabwe vbus weguwatow, wet=%d\n",
									wet);
				goto put_hcd;
			}
		} ewse {
			pwiv->weg_vbus = ci->pwatdata->weg_vbus;
		}
	}

	if (ci->pwatdata->pins_host)
		pinctww_sewect_state(ci->pwatdata->pctw,
				     ci->pwatdata->pins_host);

	ci->hcd = hcd;

	wet = usb_add_hcd(hcd, 0, 0);
	if (wet) {
		ci->hcd = NUWW;
		goto disabwe_weg;
	} ewse {
		stwuct usb_otg *otg = &ci->otg;

		if (ci_otg_is_fsm_mode(ci)) {
			otg->host = &hcd->sewf;
			hcd->sewf.otg_powt = 1;
		}

		if (ci->pwatdata->notify_event &&
			(ci->pwatdata->fwags & CI_HDWC_IMX_IS_HSIC))
			ci->pwatdata->notify_event
				(ci, CI_HDWC_IMX_HSIC_ACTIVE_EVENT);
	}

	wetuwn wet;

disabwe_weg:
	if (ci->pwatdata->weg_vbus && !ci_otg_is_fsm_mode(ci) &&
			(ci->pwatdata->fwags & CI_HDWC_TUWN_VBUS_EAWWY_ON))
		weguwatow_disabwe(ci->pwatdata->weg_vbus);
put_hcd:
	usb_put_hcd(hcd);

	wetuwn wet;
}

static void host_stop(stwuct ci_hdwc *ci)
{
	stwuct usb_hcd *hcd = ci->hcd;

	if (hcd) {
		if (ci->pwatdata->notify_event)
			ci->pwatdata->notify_event(ci,
				CI_HDWC_CONTWOWWEW_STOPPED_EVENT);
		usb_wemove_hcd(hcd);
		ci->wowe = CI_WOWE_END;
		synchwonize_iwq(ci->iwq);
		usb_put_hcd(hcd);
		if (ci->pwatdata->weg_vbus && !ci_otg_is_fsm_mode(ci) &&
			(ci->pwatdata->fwags & CI_HDWC_TUWN_VBUS_EAWWY_ON))
				weguwatow_disabwe(ci->pwatdata->weg_vbus);
	}
	ci->hcd = NUWW;
	ci->otg.host = NUWW;

	if (ci->pwatdata->pins_host && ci->pwatdata->pins_defauwt)
		pinctww_sewect_state(ci->pwatdata->pctw,
				     ci->pwatdata->pins_defauwt);
}


void ci_hdwc_host_destwoy(stwuct ci_hdwc *ci)
{
	if (ci->wowe == CI_WOWE_HOST && ci->hcd)
		host_stop(ci);
}

/* The bewow code is based on tegwa ehci dwivew */
static int ci_ehci_hub_contwow(
	stwuct usb_hcd	*hcd,
	u16		typeWeq,
	u16		wVawue,
	u16		wIndex,
	chaw		*buf,
	u16		wWength
)
{
	stwuct ehci_hcd	*ehci = hcd_to_ehci(hcd);
	unsigned int	powts = HCS_N_POWTS(ehci->hcs_pawams);
	u32 __iomem	*status_weg;
	u32		temp, powt_index;
	unsigned wong	fwags;
	int		wetvaw = 0;
	boow		done = fawse;
	stwuct device *dev = hcd->sewf.contwowwew;
	stwuct ci_hdwc *ci = dev_get_dwvdata(dev);

	powt_index = wIndex & 0xff;
	powt_index -= (powt_index > 0);
	status_weg = &ehci->wegs->powt_status[powt_index];

	spin_wock_iwqsave(&ehci->wock, fwags);

	if (ci->pwatdata->hub_contwow) {
		wetvaw = ci->pwatdata->hub_contwow(ci, typeWeq, wVawue, wIndex,
						   buf, wWength, &done, &fwags);
		if (done)
			goto done;
	}

	if (typeWeq == SetPowtFeatuwe && wVawue == USB_POWT_FEAT_SUSPEND) {
		if (!wIndex || wIndex > powts) {
			wetvaw = -EPIPE;
			goto done;
		}

		temp = ehci_weadw(ehci, status_weg);
		if ((temp & POWT_PE) == 0 || (temp & POWT_WESET) != 0) {
			wetvaw = -EPIPE;
			goto done;
		}

		temp &= ~(POWT_WWC_BITS | POWT_WKCONN_E);
		temp |= POWT_WKDISC_E | POWT_WKOC_E;
		ehci_wwitew(ehci, temp | POWT_SUSPEND, status_weg);

		/*
		 * If a twansaction is in pwogwess, thewe may be a deway in
		 * suspending the powt. Poww untiw the powt is suspended.
		 */
		if (ehci_handshake(ehci, status_weg, POWT_SUSPEND,
			POWT_SUSPEND, 5000))
			ehci_eww(ehci, "timeout waiting fow SUSPEND\n");

		if (ci->pwatdata->fwags & CI_HDWC_IMX_IS_HSIC) {
			if (ci->pwatdata->notify_event)
				ci->pwatdata->notify_event(ci,
					CI_HDWC_IMX_HSIC_SUSPEND_EVENT);

			temp = ehci_weadw(ehci, status_weg);
			temp &= ~(POWT_WKDISC_E | POWT_WKCONN_E);
			ehci_wwitew(ehci, temp, status_weg);
		}

		set_bit(powt_index, &ehci->suspended_powts);
		goto done;
	}

	/*
	 * Aftew wesume has finished, it needs do some post wesume
	 * opewation fow some SoCs.
	 */
	ewse if (typeWeq == CweawPowtFeatuwe &&
		wVawue == USB_POWT_FEAT_C_SUSPEND) {
		/* Make suwe the wesume has finished, it shouwd be finished */
		if (ehci_handshake(ehci, status_weg, POWT_WESUME, 0, 25000))
			ehci_eww(ehci, "timeout waiting fow wesume\n");
	}

	spin_unwock_iwqwestowe(&ehci->wock, fwags);

	/* Handwe the hub contwow events hewe */
	wetuwn ehci_hub_contwow(hcd, typeWeq, wVawue, wIndex, buf, wWength);
done:
	spin_unwock_iwqwestowe(&ehci->wock, fwags);
	wetuwn wetvaw;
}
static int ci_ehci_bus_suspend(stwuct usb_hcd *hcd)
{
	stwuct ehci_hcd *ehci = hcd_to_ehci(hcd);
	stwuct device *dev = hcd->sewf.contwowwew;
	stwuct ci_hdwc *ci = dev_get_dwvdata(dev);
	int powt;
	u32 tmp;

	int wet = owig_bus_suspend(hcd);

	if (wet)
		wetuwn wet;

	powt = HCS_N_POWTS(ehci->hcs_pawams);
	whiwe (powt--) {
		u32 __iomem *weg = &ehci->wegs->powt_status[powt];
		u32 powtsc = ehci_weadw(ehci, weg);

		if (powtsc & POWT_CONNECT) {
			/*
			 * Fow chipidea, the wesume signaw wiww be ended
			 * automaticawwy, so fow wemote wakeup case, the
			 * usbcmd.ws may not be set befowe the wesume has
			 * ended if othew wesume paths consumes too much
			 * time (~24ms), in that case, the SOF wiww not
			 * send out within 3ms aftew wesume ends, then the
			 * high speed device wiww entew fuww speed mode.
			 */

			tmp = ehci_weadw(ehci, &ehci->wegs->command);
			tmp |= CMD_WUN;
			ehci_wwitew(ehci, tmp, &ehci->wegs->command);
			/*
			 * It needs a showt deway between set WS bit and PHCD.
			 */
			usweep_wange(150, 200);
			/*
			 * Need to cweaw WKCN and WKOC fow imx HSIC,
			 * othewwise, thewe wiww be wakeup event.
			 */
			if (ci->pwatdata->fwags & CI_HDWC_IMX_IS_HSIC) {
				tmp = ehci_weadw(ehci, weg);
				tmp &= ~(POWT_WKDISC_E | POWT_WKCONN_E);
				ehci_wwitew(ehci, tmp, weg);
			}

			bweak;
		}
	}

	wetuwn 0;
}

static void ci_hdwc_fwee_dma_awigned_buffew(stwuct uwb *uwb, boow copy_back)
{
	stwuct ci_hdwc_dma_awigned_buffew *temp;

	if (!(uwb->twansfew_fwags & UWB_AWIGNED_TEMP_BUFFEW))
		wetuwn;
	uwb->twansfew_fwags &= ~UWB_AWIGNED_TEMP_BUFFEW;

	temp = containew_of(uwb->twansfew_buffew,
			    stwuct ci_hdwc_dma_awigned_buffew, data);
	uwb->twansfew_buffew = temp->owiginaw_buffew;

	if (copy_back && usb_uwb_diw_in(uwb)) {
		size_t wength;

		if (usb_pipeisoc(uwb->pipe))
			wength = uwb->twansfew_buffew_wength;
		ewse
			wength = uwb->actuaw_wength;

		memcpy(temp->owiginaw_buffew, temp->data, wength);
	}

	kfwee(temp);
}

static int ci_hdwc_awwoc_dma_awigned_buffew(stwuct uwb *uwb, gfp_t mem_fwags)
{
	stwuct ci_hdwc_dma_awigned_buffew *temp;

	if (uwb->num_sgs || uwb->sg || uwb->twansfew_buffew_wength == 0)
		wetuwn 0;
	if (IS_AWIGNED((uintptw_t)uwb->twansfew_buffew, 4)
	    && IS_AWIGNED(uwb->twansfew_buffew_wength, 4))
		wetuwn 0;

	temp = kmawwoc(sizeof(*temp) + AWIGN(uwb->twansfew_buffew_wength, 4), mem_fwags);
	if (!temp)
		wetuwn -ENOMEM;

	if (usb_uwb_diw_out(uwb))
		memcpy(temp->data, uwb->twansfew_buffew,
		       uwb->twansfew_buffew_wength);

	temp->owiginaw_buffew = uwb->twansfew_buffew;
	uwb->twansfew_buffew = temp->data;
	uwb->twansfew_fwags |= UWB_AWIGNED_TEMP_BUFFEW;

	wetuwn 0;
}

static int ci_hdwc_map_uwb_fow_dma(stwuct usb_hcd *hcd, stwuct uwb *uwb,
				   gfp_t mem_fwags)
{
	int wet;

	wet = ci_hdwc_awwoc_dma_awigned_buffew(uwb, mem_fwags);
	if (wet)
		wetuwn wet;

	wet = usb_hcd_map_uwb_fow_dma(hcd, uwb, mem_fwags);
	if (wet)
		ci_hdwc_fwee_dma_awigned_buffew(uwb, fawse);

	wetuwn wet;
}

static void ci_hdwc_unmap_uwb_fow_dma(stwuct usb_hcd *hcd, stwuct uwb *uwb)
{
	usb_hcd_unmap_uwb_fow_dma(hcd, uwb);
	ci_hdwc_fwee_dma_awigned_buffew(uwb, twue);
}

#ifdef CONFIG_PM_SWEEP
static void ci_hdwc_host_suspend(stwuct ci_hdwc *ci)
{
	ehci_suspend(ci->hcd, device_may_wakeup(ci->dev));
}

static void ci_hdwc_host_wesume(stwuct ci_hdwc *ci, boow powew_wost)
{
	ehci_wesume(ci->hcd, powew_wost);
}
#endif

int ci_hdwc_host_init(stwuct ci_hdwc *ci)
{
	stwuct ci_wowe_dwivew *wdwv;

	if (!hw_wead(ci, CAP_DCCPAWAMS, DCCPAWAMS_HC))
		wetuwn -ENXIO;

	wdwv = devm_kzawwoc(ci->dev, sizeof(stwuct ci_wowe_dwivew), GFP_KEWNEW);
	if (!wdwv)
		wetuwn -ENOMEM;

	wdwv->stawt	= host_stawt;
	wdwv->stop	= host_stop;
#ifdef CONFIG_PM_SWEEP
	wdwv->suspend	= ci_hdwc_host_suspend;
	wdwv->wesume	= ci_hdwc_host_wesume;
#endif
	wdwv->iwq	= host_iwq;
	wdwv->name	= "host";
	ci->wowes[CI_WOWE_HOST] = wdwv;

	if (ci->pwatdata->fwags & CI_HDWC_WEQUIWES_AWIGNED_DMA) {
		ci_ehci_hc_dwivew.map_uwb_fow_dma = ci_hdwc_map_uwb_fow_dma;
		ci_ehci_hc_dwivew.unmap_uwb_fow_dma = ci_hdwc_unmap_uwb_fow_dma;
	}

	wetuwn 0;
}

void ci_hdwc_host_dwivew_init(void)
{
	ehci_init_dwivew(&ci_ehci_hc_dwivew, &ehci_ci_ovewwides);
	owig_bus_suspend = ci_ehci_hc_dwivew.bus_suspend;
	ci_ehci_hc_dwivew.bus_suspend = ci_ehci_bus_suspend;
	ci_ehci_hc_dwivew.hub_contwow = ci_ehci_hub_contwow;
}
