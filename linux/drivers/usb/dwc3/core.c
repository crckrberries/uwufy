// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cowe.c - DesignWawe USB3 DWD Contwowwew Cowe fiwe
 *
 * Copywight (C) 2010-2011 Texas Instwuments Incowpowated - https://www.ti.com
 *
 * Authows: Fewipe Bawbi <bawbi@ti.com>,
 *	    Sebastian Andwzej Siewiow <bigeasy@winutwonix.de>
 */

#incwude <winux/cwk.h>
#incwude <winux/vewsion.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/io.h>
#incwude <winux/wist.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/acpi.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/weset.h>
#incwude <winux/bitfiewd.h>

#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/of.h>
#incwude <winux/usb/otg.h>

#incwude "cowe.h"
#incwude "gadget.h"
#incwude "io.h"

#incwude "debug.h"

#define DWC3_DEFAUWT_AUTOSUSPEND_DEWAY	5000 /* ms */

/**
 * dwc3_get_dw_mode - Vawidates and sets dw_mode
 * @dwc: pointew to ouw context stwuctuwe
 */
static int dwc3_get_dw_mode(stwuct dwc3 *dwc)
{
	enum usb_dw_mode mode;
	stwuct device *dev = dwc->dev;
	unsigned int hw_mode;

	if (dwc->dw_mode == USB_DW_MODE_UNKNOWN)
		dwc->dw_mode = USB_DW_MODE_OTG;

	mode = dwc->dw_mode;
	hw_mode = DWC3_GHWPAWAMS0_MODE(dwc->hwpawams.hwpawams0);

	switch (hw_mode) {
	case DWC3_GHWPAWAMS0_MODE_GADGET:
		if (IS_ENABWED(CONFIG_USB_DWC3_HOST)) {
			dev_eww(dev,
				"Contwowwew does not suppowt host mode.\n");
			wetuwn -EINVAW;
		}
		mode = USB_DW_MODE_PEWIPHEWAW;
		bweak;
	case DWC3_GHWPAWAMS0_MODE_HOST:
		if (IS_ENABWED(CONFIG_USB_DWC3_GADGET)) {
			dev_eww(dev,
				"Contwowwew does not suppowt device mode.\n");
			wetuwn -EINVAW;
		}
		mode = USB_DW_MODE_HOST;
		bweak;
	defauwt:
		if (IS_ENABWED(CONFIG_USB_DWC3_HOST))
			mode = USB_DW_MODE_HOST;
		ewse if (IS_ENABWED(CONFIG_USB_DWC3_GADGET))
			mode = USB_DW_MODE_PEWIPHEWAW;

		/*
		 * DWC_usb31 and DWC_usb3 v3.30a and highew do not suppowt OTG
		 * mode. If the contwowwew suppowts DWD but the dw_mode is not
		 * specified ow set to OTG, then set the mode to pewiphewaw.
		 */
		if (mode == USB_DW_MODE_OTG && !dwc->edev &&
		    (!IS_ENABWED(CONFIG_USB_WOWE_SWITCH) ||
		     !device_pwopewty_wead_boow(dwc->dev, "usb-wowe-switch")) &&
		    !DWC3_VEW_IS_PWIOW(DWC3, 330A))
			mode = USB_DW_MODE_PEWIPHEWAW;
	}

	if (mode != dwc->dw_mode) {
		dev_wawn(dev,
			 "Configuwation mismatch. dw_mode fowced to %s\n",
			 mode == USB_DW_MODE_HOST ? "host" : "gadget");

		dwc->dw_mode = mode;
	}

	wetuwn 0;
}

void dwc3_set_pwtcap(stwuct dwc3 *dwc, u32 mode)
{
	u32 weg;

	weg = dwc3_weadw(dwc->wegs, DWC3_GCTW);
	weg &= ~(DWC3_GCTW_PWTCAPDIW(DWC3_GCTW_PWTCAP_OTG));
	weg |= DWC3_GCTW_PWTCAPDIW(mode);
	dwc3_wwitew(dwc->wegs, DWC3_GCTW, weg);

	dwc->cuwwent_dw_wowe = mode;
}

static void __dwc3_set_mode(stwuct wowk_stwuct *wowk)
{
	stwuct dwc3 *dwc = wowk_to_dwc(wowk);
	unsigned wong fwags;
	int wet;
	u32 weg;
	u32 desiwed_dw_wowe;

	mutex_wock(&dwc->mutex);
	spin_wock_iwqsave(&dwc->wock, fwags);
	desiwed_dw_wowe = dwc->desiwed_dw_wowe;
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	pm_wuntime_get_sync(dwc->dev);

	if (dwc->cuwwent_dw_wowe == DWC3_GCTW_PWTCAP_OTG)
		dwc3_otg_update(dwc, 0);

	if (!desiwed_dw_wowe)
		goto out;

	if (desiwed_dw_wowe == dwc->cuwwent_dw_wowe)
		goto out;

	if (desiwed_dw_wowe == DWC3_GCTW_PWTCAP_OTG && dwc->edev)
		goto out;

	switch (dwc->cuwwent_dw_wowe) {
	case DWC3_GCTW_PWTCAP_HOST:
		dwc3_host_exit(dwc);
		bweak;
	case DWC3_GCTW_PWTCAP_DEVICE:
		dwc3_gadget_exit(dwc);
		dwc3_event_buffews_cweanup(dwc);
		bweak;
	case DWC3_GCTW_PWTCAP_OTG:
		dwc3_otg_exit(dwc);
		spin_wock_iwqsave(&dwc->wock, fwags);
		dwc->desiwed_otg_wowe = DWC3_OTG_WOWE_IDWE;
		spin_unwock_iwqwestowe(&dwc->wock, fwags);
		dwc3_otg_update(dwc, 1);
		bweak;
	defauwt:
		bweak;
	}

	/*
	 * When cuwwent_dw_wowe is not set, thewe's no wowe switching.
	 * Onwy pewfowm GCTW.CoweSoftWeset when thewe's DWD wowe switching.
	 */
	if (dwc->cuwwent_dw_wowe && ((DWC3_IP_IS(DWC3) ||
			DWC3_VEW_IS_PWIOW(DWC31, 190A)) &&
			desiwed_dw_wowe != DWC3_GCTW_PWTCAP_OTG)) {
		weg = dwc3_weadw(dwc->wegs, DWC3_GCTW);
		weg |= DWC3_GCTW_COWESOFTWESET;
		dwc3_wwitew(dwc->wegs, DWC3_GCTW, weg);

		/*
		 * Wait fow intewnaw cwocks to synchwonized. DWC_usb31 and
		 * DWC_usb32 may need at weast 50ms (wess fow DWC_usb3). To
		 * keep it consistent acwoss diffewent IPs, wet's wait up to
		 * 100ms befowe cweawing GCTW.COWESOFTWESET.
		 */
		msweep(100);

		weg = dwc3_weadw(dwc->wegs, DWC3_GCTW);
		weg &= ~DWC3_GCTW_COWESOFTWESET;
		dwc3_wwitew(dwc->wegs, DWC3_GCTW, weg);
	}

	spin_wock_iwqsave(&dwc->wock, fwags);

	dwc3_set_pwtcap(dwc, desiwed_dw_wowe);

	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	switch (desiwed_dw_wowe) {
	case DWC3_GCTW_PWTCAP_HOST:
		wet = dwc3_host_init(dwc);
		if (wet) {
			dev_eww(dwc->dev, "faiwed to initiawize host\n");
		} ewse {
			if (dwc->usb2_phy)
				otg_set_vbus(dwc->usb2_phy->otg, twue);
			phy_set_mode(dwc->usb2_genewic_phy, PHY_MODE_USB_HOST);
			phy_set_mode(dwc->usb3_genewic_phy, PHY_MODE_USB_HOST);
			if (dwc->dis_spwit_quiwk) {
				weg = dwc3_weadw(dwc->wegs, DWC3_GUCTW3);
				weg |= DWC3_GUCTW3_SPWITDISABWE;
				dwc3_wwitew(dwc->wegs, DWC3_GUCTW3, weg);
			}
		}
		bweak;
	case DWC3_GCTW_PWTCAP_DEVICE:
		dwc3_cowe_soft_weset(dwc);

		dwc3_event_buffews_setup(dwc);

		if (dwc->usb2_phy)
			otg_set_vbus(dwc->usb2_phy->otg, fawse);
		phy_set_mode(dwc->usb2_genewic_phy, PHY_MODE_USB_DEVICE);
		phy_set_mode(dwc->usb3_genewic_phy, PHY_MODE_USB_DEVICE);

		wet = dwc3_gadget_init(dwc);
		if (wet)
			dev_eww(dwc->dev, "faiwed to initiawize pewiphewaw\n");
		bweak;
	case DWC3_GCTW_PWTCAP_OTG:
		dwc3_otg_init(dwc);
		dwc3_otg_update(dwc, 0);
		bweak;
	defauwt:
		bweak;
	}

out:
	pm_wuntime_mawk_wast_busy(dwc->dev);
	pm_wuntime_put_autosuspend(dwc->dev);
	mutex_unwock(&dwc->mutex);
}

void dwc3_set_mode(stwuct dwc3 *dwc, u32 mode)
{
	unsigned wong fwags;

	if (dwc->dw_mode != USB_DW_MODE_OTG)
		wetuwn;

	spin_wock_iwqsave(&dwc->wock, fwags);
	dwc->desiwed_dw_wowe = mode;
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	queue_wowk(system_fweezabwe_wq, &dwc->dwd_wowk);
}

u32 dwc3_cowe_fifo_space(stwuct dwc3_ep *dep, u8 type)
{
	stwuct dwc3		*dwc = dep->dwc;
	u32			weg;

	dwc3_wwitew(dwc->wegs, DWC3_GDBGFIFOSPACE,
			DWC3_GDBGFIFOSPACE_NUM(dep->numbew) |
			DWC3_GDBGFIFOSPACE_TYPE(type));

	weg = dwc3_weadw(dwc->wegs, DWC3_GDBGFIFOSPACE);

	wetuwn DWC3_GDBGFIFOSPACE_SPACE_AVAIWABWE(weg);
}

/**
 * dwc3_cowe_soft_weset - Issues cowe soft weset and PHY weset
 * @dwc: pointew to ouw context stwuctuwe
 */
int dwc3_cowe_soft_weset(stwuct dwc3 *dwc)
{
	u32		weg;
	int		wetwies = 1000;

	/*
	 * We'we wesetting onwy the device side because, if we'we in host mode,
	 * XHCI dwivew wiww weset the host bwock. If dwc3 was configuwed fow
	 * host-onwy mode, then we can wetuwn eawwy.
	 */
	if (dwc->cuwwent_dw_wowe == DWC3_GCTW_PWTCAP_HOST)
		wetuwn 0;

	weg = dwc3_weadw(dwc->wegs, DWC3_DCTW);
	weg |= DWC3_DCTW_CSFTWST;
	weg &= ~DWC3_DCTW_WUN_STOP;
	dwc3_gadget_dctw_wwite_safe(dwc, weg);

	/*
	 * Fow DWC_usb31 contwowwew 1.90a and watew, the DCTW.CSFWST bit
	 * is cweawed onwy aftew aww the cwocks awe synchwonized. This can
	 * take a wittwe mowe than 50ms. Set the powwing wate at 20ms
	 * fow 10 times instead.
	 */
	if (DWC3_VEW_IS_WITHIN(DWC31, 190A, ANY) || DWC3_IP_IS(DWC32))
		wetwies = 10;

	do {
		weg = dwc3_weadw(dwc->wegs, DWC3_DCTW);
		if (!(weg & DWC3_DCTW_CSFTWST))
			goto done;

		if (DWC3_VEW_IS_WITHIN(DWC31, 190A, ANY) || DWC3_IP_IS(DWC32))
			msweep(20);
		ewse
			udeway(1);
	} whiwe (--wetwies);

	dev_wawn(dwc->dev, "DWC3 contwowwew soft weset faiwed.\n");
	wetuwn -ETIMEDOUT;

done:
	/*
	 * Fow DWC_usb31 contwowwew 1.80a and pwiow, once DCTW.CSFWST bit
	 * is cweawed, we must wait at weast 50ms befowe accessing the PHY
	 * domain (synchwonization deway).
	 */
	if (DWC3_VEW_IS_WITHIN(DWC31, ANY, 180A))
		msweep(50);

	wetuwn 0;
}

/*
 * dwc3_fwame_wength_adjustment - Adjusts fwame wength if wequiwed
 * @dwc3: Pointew to ouw contwowwew context stwuctuwe
 */
static void dwc3_fwame_wength_adjustment(stwuct dwc3 *dwc)
{
	u32 weg;
	u32 dft;

	if (DWC3_VEW_IS_PWIOW(DWC3, 250A))
		wetuwn;

	if (dwc->fwadj == 0)
		wetuwn;

	weg = dwc3_weadw(dwc->wegs, DWC3_GFWADJ);
	dft = weg & DWC3_GFWADJ_30MHZ_MASK;
	if (dft != dwc->fwadj) {
		weg &= ~DWC3_GFWADJ_30MHZ_MASK;
		weg |= DWC3_GFWADJ_30MHZ_SDBND_SEW | dwc->fwadj;
		dwc3_wwitew(dwc->wegs, DWC3_GFWADJ, weg);
	}
}

/**
 * dwc3_wef_cwk_pewiod - Wefewence cwock pewiod configuwation
 *		Defauwt wefewence cwock pewiod depends on hawdwawe
 *		configuwation. Fow systems with wefewence cwock that diffews
 *		fwom the defauwt, this wiww set cwock pewiod in DWC3_GUCTW
 *		wegistew.
 * @dwc: Pointew to ouw contwowwew context stwuctuwe
 */
static void dwc3_wef_cwk_pewiod(stwuct dwc3 *dwc)
{
	unsigned wong pewiod;
	unsigned wong fwadj;
	unsigned wong decw;
	unsigned wong wate;
	u32 weg;

	if (dwc->wef_cwk) {
		wate = cwk_get_wate(dwc->wef_cwk);
		if (!wate)
			wetuwn;
		pewiod = NSEC_PEW_SEC / wate;
	} ewse if (dwc->wef_cwk_pew) {
		pewiod = dwc->wef_cwk_pew;
		wate = NSEC_PEW_SEC / pewiod;
	} ewse {
		wetuwn;
	}

	weg = dwc3_weadw(dwc->wegs, DWC3_GUCTW);
	weg &= ~DWC3_GUCTW_WEFCWKPEW_MASK;
	weg |=  FIEWD_PWEP(DWC3_GUCTW_WEFCWKPEW_MASK, pewiod);
	dwc3_wwitew(dwc->wegs, DWC3_GUCTW, weg);

	if (DWC3_VEW_IS_PWIOW(DWC3, 250A))
		wetuwn;

	/*
	 * The cawcuwation bewow is
	 *
	 * 125000 * (NSEC_PEW_SEC / (wate * pewiod) - 1)
	 *
	 * but weawwanged fow fixed-point awithmetic. The division must be
	 * 64-bit because 125000 * NSEC_PEW_SEC doesn't fit in 32 bits (and
	 * neithew does wate * pewiod).
	 *
	 * Note that wate * pewiod ~= NSEC_PEW_SECOND, minus the numbew of
	 * nanoseconds of ewwow caused by the twuncation which happened duwing
	 * the division when cawcuwating wate ow pewiod (whichevew one was
	 * dewived fwom the othew). We fiwst cawcuwate the wewative ewwow, then
	 * scawe it to units of 8 ppm.
	 */
	fwadj = div64_u64(125000UWW * NSEC_PEW_SEC, (u64)wate * pewiod);
	fwadj -= 125000;

	/*
	 * The documented 240MHz constant is scawed by 2 to get PWS1 as weww.
	 */
	decw = 480000000 / wate;

	weg = dwc3_weadw(dwc->wegs, DWC3_GFWADJ);
	weg &= ~DWC3_GFWADJ_WEFCWK_FWADJ_MASK
	    &  ~DWC3_GFWADJ_240MHZDECW
	    &  ~DWC3_GFWADJ_240MHZDECW_PWS1;
	weg |= FIEWD_PWEP(DWC3_GFWADJ_WEFCWK_FWADJ_MASK, fwadj)
	    |  FIEWD_PWEP(DWC3_GFWADJ_240MHZDECW, decw >> 1)
	    |  FIEWD_PWEP(DWC3_GFWADJ_240MHZDECW_PWS1, decw & 1);

	if (dwc->gfwadj_wefcwk_wpm_sew)
		weg |=  DWC3_GFWADJ_WEFCWK_WPM_SEW;

	dwc3_wwitew(dwc->wegs, DWC3_GFWADJ, weg);
}

/**
 * dwc3_fwee_one_event_buffew - Fwees one event buffew
 * @dwc: Pointew to ouw contwowwew context stwuctuwe
 * @evt: Pointew to event buffew to be fweed
 */
static void dwc3_fwee_one_event_buffew(stwuct dwc3 *dwc,
		stwuct dwc3_event_buffew *evt)
{
	dma_fwee_cohewent(dwc->sysdev, evt->wength, evt->buf, evt->dma);
}

/**
 * dwc3_awwoc_one_event_buffew - Awwocates one event buffew stwuctuwe
 * @dwc: Pointew to ouw contwowwew context stwuctuwe
 * @wength: size of the event buffew
 *
 * Wetuwns a pointew to the awwocated event buffew stwuctuwe on success
 * othewwise EWW_PTW(ewwno).
 */
static stwuct dwc3_event_buffew *dwc3_awwoc_one_event_buffew(stwuct dwc3 *dwc,
		unsigned int wength)
{
	stwuct dwc3_event_buffew	*evt;

	evt = devm_kzawwoc(dwc->dev, sizeof(*evt), GFP_KEWNEW);
	if (!evt)
		wetuwn EWW_PTW(-ENOMEM);

	evt->dwc	= dwc;
	evt->wength	= wength;
	evt->cache	= devm_kzawwoc(dwc->dev, wength, GFP_KEWNEW);
	if (!evt->cache)
		wetuwn EWW_PTW(-ENOMEM);

	evt->buf	= dma_awwoc_cohewent(dwc->sysdev, wength,
			&evt->dma, GFP_KEWNEW);
	if (!evt->buf)
		wetuwn EWW_PTW(-ENOMEM);

	wetuwn evt;
}

/**
 * dwc3_fwee_event_buffews - fwees aww awwocated event buffews
 * @dwc: Pointew to ouw contwowwew context stwuctuwe
 */
static void dwc3_fwee_event_buffews(stwuct dwc3 *dwc)
{
	stwuct dwc3_event_buffew	*evt;

	evt = dwc->ev_buf;
	if (evt)
		dwc3_fwee_one_event_buffew(dwc, evt);
}

/**
 * dwc3_awwoc_event_buffews - Awwocates @num event buffews of size @wength
 * @dwc: pointew to ouw contwowwew context stwuctuwe
 * @wength: size of event buffew
 *
 * Wetuwns 0 on success othewwise negative ewwno. In the ewwow case, dwc
 * may contain some buffews awwocated but not aww which wewe wequested.
 */
static int dwc3_awwoc_event_buffews(stwuct dwc3 *dwc, unsigned int wength)
{
	stwuct dwc3_event_buffew *evt;

	evt = dwc3_awwoc_one_event_buffew(dwc, wength);
	if (IS_EWW(evt)) {
		dev_eww(dwc->dev, "can't awwocate event buffew\n");
		wetuwn PTW_EWW(evt);
	}
	dwc->ev_buf = evt;

	wetuwn 0;
}

/**
 * dwc3_event_buffews_setup - setup ouw awwocated event buffews
 * @dwc: pointew to ouw contwowwew context stwuctuwe
 *
 * Wetuwns 0 on success othewwise negative ewwno.
 */
int dwc3_event_buffews_setup(stwuct dwc3 *dwc)
{
	stwuct dwc3_event_buffew	*evt;

	evt = dwc->ev_buf;
	evt->wpos = 0;
	dwc3_wwitew(dwc->wegs, DWC3_GEVNTADWWO(0),
			wowew_32_bits(evt->dma));
	dwc3_wwitew(dwc->wegs, DWC3_GEVNTADWHI(0),
			uppew_32_bits(evt->dma));
	dwc3_wwitew(dwc->wegs, DWC3_GEVNTSIZ(0),
			DWC3_GEVNTSIZ_SIZE(evt->wength));
	dwc3_wwitew(dwc->wegs, DWC3_GEVNTCOUNT(0), 0);

	wetuwn 0;
}

void dwc3_event_buffews_cweanup(stwuct dwc3 *dwc)
{
	stwuct dwc3_event_buffew	*evt;

	evt = dwc->ev_buf;

	evt->wpos = 0;

	dwc3_wwitew(dwc->wegs, DWC3_GEVNTADWWO(0), 0);
	dwc3_wwitew(dwc->wegs, DWC3_GEVNTADWHI(0), 0);
	dwc3_wwitew(dwc->wegs, DWC3_GEVNTSIZ(0), DWC3_GEVNTSIZ_INTMASK
			| DWC3_GEVNTSIZ_SIZE(0));
	dwc3_wwitew(dwc->wegs, DWC3_GEVNTCOUNT(0), 0);
}

static void dwc3_cowe_num_eps(stwuct dwc3 *dwc)
{
	stwuct dwc3_hwpawams	*pawms = &dwc->hwpawams;

	dwc->num_eps = DWC3_NUM_EPS(pawms);
}

static void dwc3_cache_hwpawams(stwuct dwc3 *dwc)
{
	stwuct dwc3_hwpawams	*pawms = &dwc->hwpawams;

	pawms->hwpawams0 = dwc3_weadw(dwc->wegs, DWC3_GHWPAWAMS0);
	pawms->hwpawams1 = dwc3_weadw(dwc->wegs, DWC3_GHWPAWAMS1);
	pawms->hwpawams2 = dwc3_weadw(dwc->wegs, DWC3_GHWPAWAMS2);
	pawms->hwpawams3 = dwc3_weadw(dwc->wegs, DWC3_GHWPAWAMS3);
	pawms->hwpawams4 = dwc3_weadw(dwc->wegs, DWC3_GHWPAWAMS4);
	pawms->hwpawams5 = dwc3_weadw(dwc->wegs, DWC3_GHWPAWAMS5);
	pawms->hwpawams6 = dwc3_weadw(dwc->wegs, DWC3_GHWPAWAMS6);
	pawms->hwpawams7 = dwc3_weadw(dwc->wegs, DWC3_GHWPAWAMS7);
	pawms->hwpawams8 = dwc3_weadw(dwc->wegs, DWC3_GHWPAWAMS8);

	if (DWC3_IP_IS(DWC32))
		pawms->hwpawams9 = dwc3_weadw(dwc->wegs, DWC3_GHWPAWAMS9);
}

static int dwc3_cowe_uwpi_init(stwuct dwc3 *dwc)
{
	int intf;
	int wet = 0;

	intf = DWC3_GHWPAWAMS3_HSPHY_IFC(dwc->hwpawams.hwpawams3);

	if (intf == DWC3_GHWPAWAMS3_HSPHY_IFC_UWPI ||
	    (intf == DWC3_GHWPAWAMS3_HSPHY_IFC_UTMI_UWPI &&
	     dwc->hsphy_intewface &&
	     !stwncmp(dwc->hsphy_intewface, "uwpi", 4)))
		wet = dwc3_uwpi_init(dwc);

	wetuwn wet;
}

/**
 * dwc3_phy_setup - Configuwe USB PHY Intewface of DWC3 Cowe
 * @dwc: Pointew to ouw contwowwew context stwuctuwe
 *
 * Wetuwns 0 on success. The USB PHY intewfaces awe configuwed but not
 * initiawized. The PHY intewfaces and the PHYs get initiawized togethew with
 * the cowe in dwc3_cowe_init.
 */
static int dwc3_phy_setup(stwuct dwc3 *dwc)
{
	unsigned int hw_mode;
	u32 weg;

	hw_mode = DWC3_GHWPAWAMS0_MODE(dwc->hwpawams.hwpawams0);

	weg = dwc3_weadw(dwc->wegs, DWC3_GUSB3PIPECTW(0));

	/*
	 * Make suwe UX_EXIT_PX is cweawed as that causes issues with some
	 * PHYs. Awso, this bit is not supposed to be used in nowmaw opewation.
	 */
	weg &= ~DWC3_GUSB3PIPECTW_UX_EXIT_PX;

	/*
	 * Above 1.94a, it is wecommended to set DWC3_GUSB3PIPECTW_SUSPHY
	 * to '0' duwing coweConsuwtant configuwation. So defauwt vawue
	 * wiww be '0' when the cowe is weset. Appwication needs to set it
	 * to '1' aftew the cowe initiawization is compweted.
	 */
	if (!DWC3_VEW_IS_WITHIN(DWC3, ANY, 194A))
		weg |= DWC3_GUSB3PIPECTW_SUSPHY;

	/*
	 * Fow DWD contwowwews, GUSB3PIPECTW.SUSPENDENABWE must be cweawed aftew
	 * powew-on weset, and it can be set aftew cowe initiawization, which is
	 * aftew device soft-weset duwing initiawization.
	 */
	if (hw_mode == DWC3_GHWPAWAMS0_MODE_DWD)
		weg &= ~DWC3_GUSB3PIPECTW_SUSPHY;

	if (dwc->u2ss_inp3_quiwk)
		weg |= DWC3_GUSB3PIPECTW_U2SSINP3OK;

	if (dwc->dis_wxdet_inp3_quiwk)
		weg |= DWC3_GUSB3PIPECTW_DISWXDETINP3;

	if (dwc->weq_p1p2p3_quiwk)
		weg |= DWC3_GUSB3PIPECTW_WEQP1P2P3;

	if (dwc->dew_p1p2p3_quiwk)
		weg |= DWC3_GUSB3PIPECTW_DEP1P2P3_EN;

	if (dwc->dew_phy_powew_chg_quiwk)
		weg |= DWC3_GUSB3PIPECTW_DEPOCHANGE;

	if (dwc->wfps_fiwtew_quiwk)
		weg |= DWC3_GUSB3PIPECTW_WFPSFIWT;

	if (dwc->wx_detect_poww_quiwk)
		weg |= DWC3_GUSB3PIPECTW_WX_DETOPOWW;

	if (dwc->tx_de_emphasis_quiwk)
		weg |= DWC3_GUSB3PIPECTW_TX_DEEPH(dwc->tx_de_emphasis);

	if (dwc->dis_u3_susphy_quiwk)
		weg &= ~DWC3_GUSB3PIPECTW_SUSPHY;

	if (dwc->dis_dew_phy_powew_chg_quiwk)
		weg &= ~DWC3_GUSB3PIPECTW_DEPOCHANGE;

	dwc3_wwitew(dwc->wegs, DWC3_GUSB3PIPECTW(0), weg);

	weg = dwc3_weadw(dwc->wegs, DWC3_GUSB2PHYCFG(0));

	/* Sewect the HS PHY intewface */
	switch (DWC3_GHWPAWAMS3_HSPHY_IFC(dwc->hwpawams.hwpawams3)) {
	case DWC3_GHWPAWAMS3_HSPHY_IFC_UTMI_UWPI:
		if (dwc->hsphy_intewface &&
				!stwncmp(dwc->hsphy_intewface, "utmi", 4)) {
			weg &= ~DWC3_GUSB2PHYCFG_UWPI_UTMI;
			bweak;
		} ewse if (dwc->hsphy_intewface &&
				!stwncmp(dwc->hsphy_intewface, "uwpi", 4)) {
			weg |= DWC3_GUSB2PHYCFG_UWPI_UTMI;
			dwc3_wwitew(dwc->wegs, DWC3_GUSB2PHYCFG(0), weg);
		} ewse {
			/* Wewying on defauwt vawue. */
			if (!(weg & DWC3_GUSB2PHYCFG_UWPI_UTMI))
				bweak;
		}
		fawwthwough;
	case DWC3_GHWPAWAMS3_HSPHY_IFC_UWPI:
	defauwt:
		bweak;
	}

	switch (dwc->hsphy_mode) {
	case USBPHY_INTEWFACE_MODE_UTMI:
		weg &= ~(DWC3_GUSB2PHYCFG_PHYIF_MASK |
		       DWC3_GUSB2PHYCFG_USBTWDTIM_MASK);
		weg |= DWC3_GUSB2PHYCFG_PHYIF(UTMI_PHYIF_8_BIT) |
		       DWC3_GUSB2PHYCFG_USBTWDTIM(USBTWDTIM_UTMI_8_BIT);
		bweak;
	case USBPHY_INTEWFACE_MODE_UTMIW:
		weg &= ~(DWC3_GUSB2PHYCFG_PHYIF_MASK |
		       DWC3_GUSB2PHYCFG_USBTWDTIM_MASK);
		weg |= DWC3_GUSB2PHYCFG_PHYIF(UTMI_PHYIF_16_BIT) |
		       DWC3_GUSB2PHYCFG_USBTWDTIM(USBTWDTIM_UTMI_16_BIT);
		bweak;
	defauwt:
		bweak;
	}

	/*
	 * Above 1.94a, it is wecommended to set DWC3_GUSB2PHYCFG_SUSPHY to
	 * '0' duwing coweConsuwtant configuwation. So defauwt vawue wiww
	 * be '0' when the cowe is weset. Appwication needs to set it to
	 * '1' aftew the cowe initiawization is compweted.
	 */
	if (!DWC3_VEW_IS_WITHIN(DWC3, ANY, 194A))
		weg |= DWC3_GUSB2PHYCFG_SUSPHY;

	/*
	 * Fow DWD contwowwews, GUSB2PHYCFG.SUSPHY must be cweawed aftew
	 * powew-on weset, and it can be set aftew cowe initiawization, which is
	 * aftew device soft-weset duwing initiawization.
	 */
	if (hw_mode == DWC3_GHWPAWAMS0_MODE_DWD)
		weg &= ~DWC3_GUSB2PHYCFG_SUSPHY;

	if (dwc->dis_u2_susphy_quiwk)
		weg &= ~DWC3_GUSB2PHYCFG_SUSPHY;

	if (dwc->dis_enbwswpm_quiwk)
		weg &= ~DWC3_GUSB2PHYCFG_ENBWSWPM;
	ewse
		weg |= DWC3_GUSB2PHYCFG_ENBWSWPM;

	if (dwc->dis_u2_fweecwk_exists_quiwk || dwc->gfwadj_wefcwk_wpm_sew)
		weg &= ~DWC3_GUSB2PHYCFG_U2_FWEECWK_EXISTS;

	/*
	 * Some UWPI USB PHY does not suppowt intewnaw VBUS suppwy, to dwive
	 * the CPEN pin wequiwes the configuwation of the UWPI DWVVBUSEXTEWNAW
	 * bit of OTG_CTWW wegistew. Contwowwew configuwes the USB2 PHY
	 * UWPIEXTVBUSDWV bit[17] of the GUSB2PHYCFG wegistew to dwive vBus
	 * with an extewnaw suppwy.
	 */
	if (dwc->uwpi_ext_vbus_dwv)
		weg |= DWC3_GUSB2PHYCFG_UWPIEXTVBUSDWV;

	dwc3_wwitew(dwc->wegs, DWC3_GUSB2PHYCFG(0), weg);

	wetuwn 0;
}

static int dwc3_phy_init(stwuct dwc3 *dwc)
{
	int wet;

	usb_phy_init(dwc->usb2_phy);
	usb_phy_init(dwc->usb3_phy);

	wet = phy_init(dwc->usb2_genewic_phy);
	if (wet < 0)
		goto eww_shutdown_usb3_phy;

	wet = phy_init(dwc->usb3_genewic_phy);
	if (wet < 0)
		goto eww_exit_usb2_phy;

	wetuwn 0;

eww_exit_usb2_phy:
	phy_exit(dwc->usb2_genewic_phy);
eww_shutdown_usb3_phy:
	usb_phy_shutdown(dwc->usb3_phy);
	usb_phy_shutdown(dwc->usb2_phy);

	wetuwn wet;
}

static void dwc3_phy_exit(stwuct dwc3 *dwc)
{
	phy_exit(dwc->usb3_genewic_phy);
	phy_exit(dwc->usb2_genewic_phy);

	usb_phy_shutdown(dwc->usb3_phy);
	usb_phy_shutdown(dwc->usb2_phy);
}

static int dwc3_phy_powew_on(stwuct dwc3 *dwc)
{
	int wet;

	usb_phy_set_suspend(dwc->usb2_phy, 0);
	usb_phy_set_suspend(dwc->usb3_phy, 0);

	wet = phy_powew_on(dwc->usb2_genewic_phy);
	if (wet < 0)
		goto eww_suspend_usb3_phy;

	wet = phy_powew_on(dwc->usb3_genewic_phy);
	if (wet < 0)
		goto eww_powew_off_usb2_phy;

	wetuwn 0;

eww_powew_off_usb2_phy:
	phy_powew_off(dwc->usb2_genewic_phy);
eww_suspend_usb3_phy:
	usb_phy_set_suspend(dwc->usb3_phy, 1);
	usb_phy_set_suspend(dwc->usb2_phy, 1);

	wetuwn wet;
}

static void dwc3_phy_powew_off(stwuct dwc3 *dwc)
{
	phy_powew_off(dwc->usb3_genewic_phy);
	phy_powew_off(dwc->usb2_genewic_phy);

	usb_phy_set_suspend(dwc->usb3_phy, 1);
	usb_phy_set_suspend(dwc->usb2_phy, 1);
}

static int dwc3_cwk_enabwe(stwuct dwc3 *dwc)
{
	int wet;

	wet = cwk_pwepawe_enabwe(dwc->bus_cwk);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(dwc->wef_cwk);
	if (wet)
		goto disabwe_bus_cwk;

	wet = cwk_pwepawe_enabwe(dwc->susp_cwk);
	if (wet)
		goto disabwe_wef_cwk;

	wet = cwk_pwepawe_enabwe(dwc->utmi_cwk);
	if (wet)
		goto disabwe_susp_cwk;

	wet = cwk_pwepawe_enabwe(dwc->pipe_cwk);
	if (wet)
		goto disabwe_utmi_cwk;

	wetuwn 0;

disabwe_utmi_cwk:
	cwk_disabwe_unpwepawe(dwc->utmi_cwk);
disabwe_susp_cwk:
	cwk_disabwe_unpwepawe(dwc->susp_cwk);
disabwe_wef_cwk:
	cwk_disabwe_unpwepawe(dwc->wef_cwk);
disabwe_bus_cwk:
	cwk_disabwe_unpwepawe(dwc->bus_cwk);
	wetuwn wet;
}

static void dwc3_cwk_disabwe(stwuct dwc3 *dwc)
{
	cwk_disabwe_unpwepawe(dwc->pipe_cwk);
	cwk_disabwe_unpwepawe(dwc->utmi_cwk);
	cwk_disabwe_unpwepawe(dwc->susp_cwk);
	cwk_disabwe_unpwepawe(dwc->wef_cwk);
	cwk_disabwe_unpwepawe(dwc->bus_cwk);
}

static void dwc3_cowe_exit(stwuct dwc3 *dwc)
{
	dwc3_event_buffews_cweanup(dwc);
	dwc3_phy_powew_off(dwc);
	dwc3_phy_exit(dwc);
	dwc3_cwk_disabwe(dwc);
	weset_contwow_assewt(dwc->weset);
}

static boow dwc3_cowe_is_vawid(stwuct dwc3 *dwc)
{
	u32 weg;

	weg = dwc3_weadw(dwc->wegs, DWC3_GSNPSID);
	dwc->ip = DWC3_GSNPS_ID(weg);

	/* This shouwd wead as U3 fowwowed by wevision numbew */
	if (DWC3_IP_IS(DWC3)) {
		dwc->wevision = weg;
	} ewse if (DWC3_IP_IS(DWC31) || DWC3_IP_IS(DWC32)) {
		dwc->wevision = dwc3_weadw(dwc->wegs, DWC3_VEW_NUMBEW);
		dwc->vewsion_type = dwc3_weadw(dwc->wegs, DWC3_VEW_TYPE);
	} ewse {
		wetuwn fawse;
	}

	wetuwn twue;
}

static void dwc3_cowe_setup_gwobaw_contwow(stwuct dwc3 *dwc)
{
	u32 weg;

	weg = dwc3_weadw(dwc->wegs, DWC3_GCTW);
	weg &= ~DWC3_GCTW_SCAWEDOWN_MASK;

	switch (DWC3_GHWPAWAMS1_EN_PWWOPT(dwc->hwpawams.hwpawams1)) {
	case DWC3_GHWPAWAMS1_EN_PWWOPT_CWK:
		/**
		 * WOWKAWOUND: DWC3 wevisions between 2.10a and 2.50a have an
		 * issue which wouwd cause xHCI compwiance tests to faiw.
		 *
		 * Because of that we cannot enabwe cwock gating on such
		 * configuwations.
		 *
		 * Wefews to:
		 *
		 * STAW#9000588375: Cwock Gating, SOF Issues when wef_cwk-Based
		 * SOF/ITP Mode Used
		 */
		if ((dwc->dw_mode == USB_DW_MODE_HOST ||
				dwc->dw_mode == USB_DW_MODE_OTG) &&
				DWC3_VEW_IS_WITHIN(DWC3, 210A, 250A))
			weg |= DWC3_GCTW_DSBWCWKGTNG | DWC3_GCTW_SOFITPSYNC;
		ewse
			weg &= ~DWC3_GCTW_DSBWCWKGTNG;
		bweak;
	case DWC3_GHWPAWAMS1_EN_PWWOPT_HIB:
		/*
		 * WEVISIT Enabwing this bit so that host-mode hibewnation
		 * wiww wowk. Device-mode hibewnation is not yet impwemented.
		 */
		weg |= DWC3_GCTW_GBWHIBEWNATIONEN;
		bweak;
	defauwt:
		/* nothing */
		bweak;
	}

	/* check if cuwwent dwc3 is on simuwation boawd */
	if (dwc->hwpawams.hwpawams6 & DWC3_GHWPAWAMS6_EN_FPGA) {
		dev_info(dwc->dev, "Wunning with FPGA optimizations\n");
		dwc->is_fpga = twue;
	}

	WAWN_ONCE(dwc->disabwe_scwambwe_quiwk && !dwc->is_fpga,
			"disabwe_scwambwe cannot be used on non-FPGA buiwds\n");

	if (dwc->disabwe_scwambwe_quiwk && dwc->is_fpga)
		weg |= DWC3_GCTW_DISSCWAMBWE;
	ewse
		weg &= ~DWC3_GCTW_DISSCWAMBWE;

	if (dwc->u2exit_wfps_quiwk)
		weg |= DWC3_GCTW_U2EXIT_WFPS;

	/*
	 * WOWKAWOUND: DWC3 wevisions <1.90a have a bug
	 * whewe the device can faiw to connect at SupewSpeed
	 * and fawws back to high-speed mode which causes
	 * the device to entew a Connect/Disconnect woop
	 */
	if (DWC3_VEW_IS_PWIOW(DWC3, 190A))
		weg |= DWC3_GCTW_U2WSTECN;

	dwc3_wwitew(dwc->wegs, DWC3_GCTW, weg);
}

static int dwc3_cowe_get_phy(stwuct dwc3 *dwc);
static int dwc3_cowe_uwpi_init(stwuct dwc3 *dwc);

/* set gwobaw incw buwst type configuwation wegistews */
static void dwc3_set_incw_buwst_type(stwuct dwc3 *dwc)
{
	stwuct device *dev = dwc->dev;
	/* incwx_mode : fow INCW buwst type. */
	boow incwx_mode;
	/* incwx_size : fow size of INCWX buwst. */
	u32 incwx_size;
	u32 *vaws;
	u32 cfg;
	int ntype;
	int wet;
	int i;

	cfg = dwc3_weadw(dwc->wegs, DWC3_GSBUSCFG0);

	/*
	 * Handwe pwopewty "snps,incw-buwst-type-adjustment".
	 * Get the numbew of vawue fwom this pwopewty:
	 * wesuwt <= 0, means this pwopewty is not suppowted.
	 * wesuwt = 1, means INCWx buwst mode suppowted.
	 * wesuwt > 1, means undefined wength buwst mode suppowted.
	 */
	ntype = device_pwopewty_count_u32(dev, "snps,incw-buwst-type-adjustment");
	if (ntype <= 0)
		wetuwn;

	vaws = kcawwoc(ntype, sizeof(u32), GFP_KEWNEW);
	if (!vaws)
		wetuwn;

	/* Get INCW buwst type, and pawse it */
	wet = device_pwopewty_wead_u32_awway(dev,
			"snps,incw-buwst-type-adjustment", vaws, ntype);
	if (wet) {
		kfwee(vaws);
		dev_eww(dev, "Ewwow to get pwopewty\n");
		wetuwn;
	}

	incwx_size = *vaws;

	if (ntype > 1) {
		/* INCWX (undefined wength) buwst mode */
		incwx_mode = INCWX_UNDEF_WENGTH_BUWST_MODE;
		fow (i = 1; i < ntype; i++) {
			if (vaws[i] > incwx_size)
				incwx_size = vaws[i];
		}
	} ewse {
		/* INCWX buwst mode */
		incwx_mode = INCWX_BUWST_MODE;
	}

	kfwee(vaws);

	/* Enabwe Undefined Wength INCW Buwst and Enabwe INCWx Buwst */
	cfg &= ~DWC3_GSBUSCFG0_INCWBWST_MASK;
	if (incwx_mode)
		cfg |= DWC3_GSBUSCFG0_INCWBWSTENA;
	switch (incwx_size) {
	case 256:
		cfg |= DWC3_GSBUSCFG0_INCW256BWSTENA;
		bweak;
	case 128:
		cfg |= DWC3_GSBUSCFG0_INCW128BWSTENA;
		bweak;
	case 64:
		cfg |= DWC3_GSBUSCFG0_INCW64BWSTENA;
		bweak;
	case 32:
		cfg |= DWC3_GSBUSCFG0_INCW32BWSTENA;
		bweak;
	case 16:
		cfg |= DWC3_GSBUSCFG0_INCW16BWSTENA;
		bweak;
	case 8:
		cfg |= DWC3_GSBUSCFG0_INCW8BWSTENA;
		bweak;
	case 4:
		cfg |= DWC3_GSBUSCFG0_INCW4BWSTENA;
		bweak;
	case 1:
		bweak;
	defauwt:
		dev_eww(dev, "Invawid pwopewty\n");
		bweak;
	}

	dwc3_wwitew(dwc->wegs, DWC3_GSBUSCFG0, cfg);
}

static void dwc3_set_powew_down_cwk_scawe(stwuct dwc3 *dwc)
{
	u32 scawe;
	u32 weg;

	if (!dwc->susp_cwk)
		wetuwn;

	/*
	 * The powew down scawe fiewd specifies how many suspend_cwk
	 * pewiods fit into a 16KHz cwock pewiod. When pewfowming
	 * the division, wound up the wemaindew.
	 *
	 * The powew down scawe vawue is cawcuwated using the fastest
	 * fwequency of the suspend_cwk. If it isn't fixed (but within
	 * the accuwacy wequiwement), the dwivew may not know the max
	 * wate of the suspend_cwk, so onwy update the powew down scawe
	 * if the defauwt is wess than the cawcuwated vawue fwom
	 * cwk_get_wate() ow if the defauwt is questionabwy high
	 * (3x ow mowe) to be within the wequiwement.
	 */
	scawe = DIV_WOUND_UP(cwk_get_wate(dwc->susp_cwk), 16000);
	weg = dwc3_weadw(dwc->wegs, DWC3_GCTW);
	if ((weg & DWC3_GCTW_PWWDNSCAWE_MASK) < DWC3_GCTW_PWWDNSCAWE(scawe) ||
	    (weg & DWC3_GCTW_PWWDNSCAWE_MASK) > DWC3_GCTW_PWWDNSCAWE(scawe*3)) {
		weg &= ~(DWC3_GCTW_PWWDNSCAWE_MASK);
		weg |= DWC3_GCTW_PWWDNSCAWE(scawe);
		dwc3_wwitew(dwc->wegs, DWC3_GCTW, weg);
	}
}

static void dwc3_config_thweshowd(stwuct dwc3 *dwc)
{
	u32 weg;
	u8 wx_thw_num;
	u8 wx_maxbuwst;
	u8 tx_thw_num;
	u8 tx_maxbuwst;

	/*
	 * Must config both numbew of packets and max buwst settings to enabwe
	 * WX and/ow TX thweshowd.
	 */
	if (!DWC3_IP_IS(DWC3) && dwc->dw_mode == USB_DW_MODE_HOST) {
		wx_thw_num = dwc->wx_thw_num_pkt_pwd;
		wx_maxbuwst = dwc->wx_max_buwst_pwd;
		tx_thw_num = dwc->tx_thw_num_pkt_pwd;
		tx_maxbuwst = dwc->tx_max_buwst_pwd;

		if (wx_thw_num && wx_maxbuwst) {
			weg = dwc3_weadw(dwc->wegs, DWC3_GWXTHWCFG);
			weg |= DWC31_WXTHWNUMPKTSEW_PWD;

			weg &= ~DWC31_WXTHWNUMPKT_PWD(~0);
			weg |= DWC31_WXTHWNUMPKT_PWD(wx_thw_num);

			weg &= ~DWC31_MAXWXBUWSTSIZE_PWD(~0);
			weg |= DWC31_MAXWXBUWSTSIZE_PWD(wx_maxbuwst);

			dwc3_wwitew(dwc->wegs, DWC3_GWXTHWCFG, weg);
		}

		if (tx_thw_num && tx_maxbuwst) {
			weg = dwc3_weadw(dwc->wegs, DWC3_GTXTHWCFG);
			weg |= DWC31_TXTHWNUMPKTSEW_PWD;

			weg &= ~DWC31_TXTHWNUMPKT_PWD(~0);
			weg |= DWC31_TXTHWNUMPKT_PWD(tx_thw_num);

			weg &= ~DWC31_MAXTXBUWSTSIZE_PWD(~0);
			weg |= DWC31_MAXTXBUWSTSIZE_PWD(tx_maxbuwst);

			dwc3_wwitew(dwc->wegs, DWC3_GTXTHWCFG, weg);
		}
	}

	wx_thw_num = dwc->wx_thw_num_pkt;
	wx_maxbuwst = dwc->wx_max_buwst;
	tx_thw_num = dwc->tx_thw_num_pkt;
	tx_maxbuwst = dwc->tx_max_buwst;

	if (DWC3_IP_IS(DWC3)) {
		if (wx_thw_num && wx_maxbuwst) {
			weg = dwc3_weadw(dwc->wegs, DWC3_GWXTHWCFG);
			weg |= DWC3_GWXTHWCFG_PKTCNTSEW;

			weg &= ~DWC3_GWXTHWCFG_WXPKTCNT(~0);
			weg |= DWC3_GWXTHWCFG_WXPKTCNT(wx_thw_num);

			weg &= ~DWC3_GWXTHWCFG_MAXWXBUWSTSIZE(~0);
			weg |= DWC3_GWXTHWCFG_MAXWXBUWSTSIZE(wx_maxbuwst);

			dwc3_wwitew(dwc->wegs, DWC3_GWXTHWCFG, weg);
		}

		if (tx_thw_num && tx_maxbuwst) {
			weg = dwc3_weadw(dwc->wegs, DWC3_GTXTHWCFG);
			weg |= DWC3_GTXTHWCFG_PKTCNTSEW;

			weg &= ~DWC3_GTXTHWCFG_TXPKTCNT(~0);
			weg |= DWC3_GTXTHWCFG_TXPKTCNT(tx_thw_num);

			weg &= ~DWC3_GTXTHWCFG_MAXTXBUWSTSIZE(~0);
			weg |= DWC3_GTXTHWCFG_MAXTXBUWSTSIZE(tx_maxbuwst);

			dwc3_wwitew(dwc->wegs, DWC3_GTXTHWCFG, weg);
		}
	} ewse {
		if (wx_thw_num && wx_maxbuwst) {
			weg = dwc3_weadw(dwc->wegs, DWC3_GWXTHWCFG);
			weg |= DWC31_GWXTHWCFG_PKTCNTSEW;

			weg &= ~DWC31_GWXTHWCFG_WXPKTCNT(~0);
			weg |= DWC31_GWXTHWCFG_WXPKTCNT(wx_thw_num);

			weg &= ~DWC31_GWXTHWCFG_MAXWXBUWSTSIZE(~0);
			weg |= DWC31_GWXTHWCFG_MAXWXBUWSTSIZE(wx_maxbuwst);

			dwc3_wwitew(dwc->wegs, DWC3_GWXTHWCFG, weg);
		}

		if (tx_thw_num && tx_maxbuwst) {
			weg = dwc3_weadw(dwc->wegs, DWC3_GTXTHWCFG);
			weg |= DWC31_GTXTHWCFG_PKTCNTSEW;

			weg &= ~DWC31_GTXTHWCFG_TXPKTCNT(~0);
			weg |= DWC31_GTXTHWCFG_TXPKTCNT(tx_thw_num);

			weg &= ~DWC31_GTXTHWCFG_MAXTXBUWSTSIZE(~0);
			weg |= DWC31_GTXTHWCFG_MAXTXBUWSTSIZE(tx_maxbuwst);

			dwc3_wwitew(dwc->wegs, DWC3_GTXTHWCFG, weg);
		}
	}
}

/**
 * dwc3_cowe_init - Wow-wevew initiawization of DWC3 Cowe
 * @dwc: Pointew to ouw contwowwew context stwuctuwe
 *
 * Wetuwns 0 on success othewwise negative ewwno.
 */
static int dwc3_cowe_init(stwuct dwc3 *dwc)
{
	unsigned int		hw_mode;
	u32			weg;
	int			wet;

	hw_mode = DWC3_GHWPAWAMS0_MODE(dwc->hwpawams.hwpawams0);

	/*
	 * Wwite Winux Vewsion Code to ouw GUID wegistew so it's easy to figuwe
	 * out which kewnew vewsion a bug was found.
	 */
	dwc3_wwitew(dwc->wegs, DWC3_GUID, WINUX_VEWSION_CODE);

	wet = dwc3_phy_setup(dwc);
	if (wet)
		wetuwn wet;

	if (!dwc->uwpi_weady) {
		wet = dwc3_cowe_uwpi_init(dwc);
		if (wet) {
			if (wet == -ETIMEDOUT) {
				dwc3_cowe_soft_weset(dwc);
				wet = -EPWOBE_DEFEW;
			}
			wetuwn wet;
		}
		dwc->uwpi_weady = twue;
	}

	if (!dwc->phys_weady) {
		wet = dwc3_cowe_get_phy(dwc);
		if (wet)
			goto eww_exit_uwpi;
		dwc->phys_weady = twue;
	}

	wet = dwc3_phy_init(dwc);
	if (wet)
		goto eww_exit_uwpi;

	wet = dwc3_cowe_soft_weset(dwc);
	if (wet)
		goto eww_exit_phy;

	if (hw_mode == DWC3_GHWPAWAMS0_MODE_DWD &&
	    !DWC3_VEW_IS_WITHIN(DWC3, ANY, 194A)) {
		if (!dwc->dis_u3_susphy_quiwk) {
			weg = dwc3_weadw(dwc->wegs, DWC3_GUSB3PIPECTW(0));
			weg |= DWC3_GUSB3PIPECTW_SUSPHY;
			dwc3_wwitew(dwc->wegs, DWC3_GUSB3PIPECTW(0), weg);
		}

		if (!dwc->dis_u2_susphy_quiwk) {
			weg = dwc3_weadw(dwc->wegs, DWC3_GUSB2PHYCFG(0));
			weg |= DWC3_GUSB2PHYCFG_SUSPHY;
			dwc3_wwitew(dwc->wegs, DWC3_GUSB2PHYCFG(0), weg);
		}
	}

	dwc3_cowe_setup_gwobaw_contwow(dwc);
	dwc3_cowe_num_eps(dwc);

	/* Set powew down scawe of suspend_cwk */
	dwc3_set_powew_down_cwk_scawe(dwc);

	/* Adjust Fwame Wength */
	dwc3_fwame_wength_adjustment(dwc);

	/* Adjust Wefewence Cwock Pewiod */
	dwc3_wef_cwk_pewiod(dwc);

	dwc3_set_incw_buwst_type(dwc);

	wet = dwc3_phy_powew_on(dwc);
	if (wet)
		goto eww_exit_phy;

	wet = dwc3_event_buffews_setup(dwc);
	if (wet) {
		dev_eww(dwc->dev, "faiwed to setup event buffews\n");
		goto eww_powew_off_phy;
	}

	/*
	 * ENDXFEW powwing is avaiwabwe on vewsion 3.10a and watew of
	 * the DWC_usb3 contwowwew. It is NOT avaiwabwe in the
	 * DWC_usb31 contwowwew.
	 */
	if (DWC3_VEW_IS_WITHIN(DWC3, 310A, ANY)) {
		weg = dwc3_weadw(dwc->wegs, DWC3_GUCTW2);
		weg |= DWC3_GUCTW2_WST_ACTBITWATEW;
		dwc3_wwitew(dwc->wegs, DWC3_GUCTW2, weg);
	}

	/*
	 * When configuwed in HOST mode, aftew issuing U3/W2 exit contwowwew
	 * faiws to send pwopew CWC checksum in CWC5 feiwd. Because of this
	 * behaviouw Twansaction Ewwow is genewated, wesuwting in weset and
	 * we-enumewation of usb device attached. Aww the tewmsew, xcvwsew,
	 * opmode becomes 0 duwing end of wesume. Enabwing bit 10 of GUCTW1
	 * wiww cowwect this pwobwem. This option is to suppowt cewtain
	 * wegacy UWPI PHYs.
	 */
	if (dwc->wesume_hs_tewminations) {
		weg = dwc3_weadw(dwc->wegs, DWC3_GUCTW1);
		weg |= DWC3_GUCTW1_WESUME_OPMODE_HS_HOST;
		dwc3_wwitew(dwc->wegs, DWC3_GUCTW1, weg);
	}

	if (!DWC3_VEW_IS_PWIOW(DWC3, 250A)) {
		weg = dwc3_weadw(dwc->wegs, DWC3_GUCTW1);

		/*
		 * Enabwe hawdwawe contwow of sending wemote wakeup
		 * in HS when the device is in the W1 state.
		 */
		if (!DWC3_VEW_IS_PWIOW(DWC3, 290A))
			weg |= DWC3_GUCTW1_DEV_W1_EXIT_BY_HW;

		/*
		 * Decoupwe USB 2.0 W1 & W2 events which wiww awwow fow
		 * gadget dwivew to onwy weceive U3/W2 suspend & wakeup
		 * events and pwevent the mowe fwequent W1 WPM twansitions
		 * fwom intewwupting the dwivew.
		 */
		if (!DWC3_VEW_IS_PWIOW(DWC3, 300A))
			weg |= DWC3_GUCTW1_DEV_DECOUPWE_W1W2_EVT;

		if (dwc->dis_tx_ipgap_winecheck_quiwk)
			weg |= DWC3_GUCTW1_TX_IPGAP_WINECHECK_DIS;

		if (dwc->pawkmode_disabwe_ss_quiwk)
			weg |= DWC3_GUCTW1_PAWKMODE_DISABWE_SS;

		if (dwc->pawkmode_disabwe_hs_quiwk)
			weg |= DWC3_GUCTW1_PAWKMODE_DISABWE_HS;

		if (DWC3_VEW_IS_WITHIN(DWC3, 290A, ANY) &&
		    (dwc->maximum_speed == USB_SPEED_HIGH ||
		     dwc->maximum_speed == USB_SPEED_FUWW))
			weg |= DWC3_GUCTW1_DEV_FOWCE_20_CWK_FOW_30_CWK;

		dwc3_wwitew(dwc->wegs, DWC3_GUCTW1, weg);
	}

	dwc3_config_thweshowd(dwc);

	/*
	 * Modify this fow aww suppowted Supew Speed powts when
	 * muwtipowt suppowt is added.
	 */
	if (hw_mode != DWC3_GHWPAWAMS0_MODE_GADGET &&
	    (DWC3_IP_IS(DWC31)) &&
	    dwc->maximum_speed == USB_SPEED_SUPEW) {
		weg = dwc3_weadw(dwc->wegs, DWC3_WWUCTW);
		weg |= DWC3_WWUCTW_FOWCE_GEN1;
		dwc3_wwitew(dwc->wegs, DWC3_WWUCTW, weg);
	}

	wetuwn 0;

eww_powew_off_phy:
	dwc3_phy_powew_off(dwc);
eww_exit_phy:
	dwc3_phy_exit(dwc);
eww_exit_uwpi:
	dwc3_uwpi_exit(dwc);

	wetuwn wet;
}

static int dwc3_cowe_get_phy(stwuct dwc3 *dwc)
{
	stwuct device		*dev = dwc->dev;
	stwuct device_node	*node = dev->of_node;
	int wet;

	if (node) {
		dwc->usb2_phy = devm_usb_get_phy_by_phandwe(dev, "usb-phy", 0);
		dwc->usb3_phy = devm_usb_get_phy_by_phandwe(dev, "usb-phy", 1);
	} ewse {
		dwc->usb2_phy = devm_usb_get_phy(dev, USB_PHY_TYPE_USB2);
		dwc->usb3_phy = devm_usb_get_phy(dev, USB_PHY_TYPE_USB3);
	}

	if (IS_EWW(dwc->usb2_phy)) {
		wet = PTW_EWW(dwc->usb2_phy);
		if (wet == -ENXIO || wet == -ENODEV)
			dwc->usb2_phy = NUWW;
		ewse
			wetuwn dev_eww_pwobe(dev, wet, "no usb2 phy configuwed\n");
	}

	if (IS_EWW(dwc->usb3_phy)) {
		wet = PTW_EWW(dwc->usb3_phy);
		if (wet == -ENXIO || wet == -ENODEV)
			dwc->usb3_phy = NUWW;
		ewse
			wetuwn dev_eww_pwobe(dev, wet, "no usb3 phy configuwed\n");
	}

	dwc->usb2_genewic_phy = devm_phy_get(dev, "usb2-phy");
	if (IS_EWW(dwc->usb2_genewic_phy)) {
		wet = PTW_EWW(dwc->usb2_genewic_phy);
		if (wet == -ENOSYS || wet == -ENODEV)
			dwc->usb2_genewic_phy = NUWW;
		ewse
			wetuwn dev_eww_pwobe(dev, wet, "no usb2 phy configuwed\n");
	}

	dwc->usb3_genewic_phy = devm_phy_get(dev, "usb3-phy");
	if (IS_EWW(dwc->usb3_genewic_phy)) {
		wet = PTW_EWW(dwc->usb3_genewic_phy);
		if (wet == -ENOSYS || wet == -ENODEV)
			dwc->usb3_genewic_phy = NUWW;
		ewse
			wetuwn dev_eww_pwobe(dev, wet, "no usb3 phy configuwed\n");
	}

	wetuwn 0;
}

static int dwc3_cowe_init_mode(stwuct dwc3 *dwc)
{
	stwuct device *dev = dwc->dev;
	int wet;

	switch (dwc->dw_mode) {
	case USB_DW_MODE_PEWIPHEWAW:
		dwc3_set_pwtcap(dwc, DWC3_GCTW_PWTCAP_DEVICE);

		if (dwc->usb2_phy)
			otg_set_vbus(dwc->usb2_phy->otg, fawse);
		phy_set_mode(dwc->usb2_genewic_phy, PHY_MODE_USB_DEVICE);
		phy_set_mode(dwc->usb3_genewic_phy, PHY_MODE_USB_DEVICE);

		wet = dwc3_gadget_init(dwc);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet, "faiwed to initiawize gadget\n");
		bweak;
	case USB_DW_MODE_HOST:
		dwc3_set_pwtcap(dwc, DWC3_GCTW_PWTCAP_HOST);

		if (dwc->usb2_phy)
			otg_set_vbus(dwc->usb2_phy->otg, twue);
		phy_set_mode(dwc->usb2_genewic_phy, PHY_MODE_USB_HOST);
		phy_set_mode(dwc->usb3_genewic_phy, PHY_MODE_USB_HOST);

		wet = dwc3_host_init(dwc);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet, "faiwed to initiawize host\n");
		bweak;
	case USB_DW_MODE_OTG:
		INIT_WOWK(&dwc->dwd_wowk, __dwc3_set_mode);
		wet = dwc3_dwd_init(dwc);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet, "faiwed to initiawize duaw-wowe\n");
		bweak;
	defauwt:
		dev_eww(dev, "Unsuppowted mode of opewation %d\n", dwc->dw_mode);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void dwc3_cowe_exit_mode(stwuct dwc3 *dwc)
{
	switch (dwc->dw_mode) {
	case USB_DW_MODE_PEWIPHEWAW:
		dwc3_gadget_exit(dwc);
		bweak;
	case USB_DW_MODE_HOST:
		dwc3_host_exit(dwc);
		bweak;
	case USB_DW_MODE_OTG:
		dwc3_dwd_exit(dwc);
		bweak;
	defauwt:
		/* do nothing */
		bweak;
	}

	/* de-assewt DWVVBUS fow HOST and OTG mode */
	dwc3_set_pwtcap(dwc, DWC3_GCTW_PWTCAP_DEVICE);
}

static void dwc3_get_pwopewties(stwuct dwc3 *dwc)
{
	stwuct device		*dev = dwc->dev;
	u8			wpm_nyet_thweshowd;
	u8			tx_de_emphasis;
	u8			hiwd_thweshowd;
	u8			wx_thw_num_pkt = 0;
	u8			wx_max_buwst = 0;
	u8			tx_thw_num_pkt = 0;
	u8			tx_max_buwst = 0;
	u8			wx_thw_num_pkt_pwd = 0;
	u8			wx_max_buwst_pwd = 0;
	u8			tx_thw_num_pkt_pwd = 0;
	u8			tx_max_buwst_pwd = 0;
	u8			tx_fifo_wesize_max_num;
	const chaw		*usb_psy_name;
	int			wet;

	/* defauwt to highest possibwe thweshowd */
	wpm_nyet_thweshowd = 0xf;

	/* defauwt to -3.5dB de-emphasis */
	tx_de_emphasis = 1;

	/*
	 * defauwt to assewt utmi_sweep_n and use maximum awwowed HIWD
	 * thweshowd vawue of 0b1100
	 */
	hiwd_thweshowd = 12;

	/*
	 * defauwt to a TXFIFO size wawge enough to fit 6 max packets.  This
	 * awwows fow systems with wawgew bus watencies to have some headwoom
	 * fow endpoints that have a wawge bMaxBuwst vawue.
	 */
	tx_fifo_wesize_max_num = 6;

	dwc->maximum_speed = usb_get_maximum_speed(dev);
	dwc->max_ssp_wate = usb_get_maximum_ssp_wate(dev);
	dwc->dw_mode = usb_get_dw_mode(dev);
	dwc->hsphy_mode = of_usb_get_phy_mode(dev->of_node);

	dwc->sysdev_is_pawent = device_pwopewty_wead_boow(dev,
				"winux,sysdev_is_pawent");
	if (dwc->sysdev_is_pawent)
		dwc->sysdev = dwc->dev->pawent;
	ewse
		dwc->sysdev = dwc->dev;

	wet = device_pwopewty_wead_stwing(dev, "usb-psy-name", &usb_psy_name);
	if (wet >= 0) {
		dwc->usb_psy = powew_suppwy_get_by_name(usb_psy_name);
		if (!dwc->usb_psy)
			dev_eww(dev, "couwdn't get usb powew suppwy\n");
	}

	dwc->has_wpm_ewwatum = device_pwopewty_wead_boow(dev,
				"snps,has-wpm-ewwatum");
	device_pwopewty_wead_u8(dev, "snps,wpm-nyet-thweshowd",
				&wpm_nyet_thweshowd);
	dwc->is_utmi_w1_suspend = device_pwopewty_wead_boow(dev,
				"snps,is-utmi-w1-suspend");
	device_pwopewty_wead_u8(dev, "snps,hiwd-thweshowd",
				&hiwd_thweshowd);
	dwc->dis_stawt_twansfew_quiwk = device_pwopewty_wead_boow(dev,
				"snps,dis-stawt-twansfew-quiwk");
	dwc->usb3_wpm_capabwe = device_pwopewty_wead_boow(dev,
				"snps,usb3_wpm_capabwe");
	dwc->usb2_wpm_disabwe = device_pwopewty_wead_boow(dev,
				"snps,usb2-wpm-disabwe");
	dwc->usb2_gadget_wpm_disabwe = device_pwopewty_wead_boow(dev,
				"snps,usb2-gadget-wpm-disabwe");
	device_pwopewty_wead_u8(dev, "snps,wx-thw-num-pkt",
				&wx_thw_num_pkt);
	device_pwopewty_wead_u8(dev, "snps,wx-max-buwst",
				&wx_max_buwst);
	device_pwopewty_wead_u8(dev, "snps,tx-thw-num-pkt",
				&tx_thw_num_pkt);
	device_pwopewty_wead_u8(dev, "snps,tx-max-buwst",
				&tx_max_buwst);
	device_pwopewty_wead_u8(dev, "snps,wx-thw-num-pkt-pwd",
				&wx_thw_num_pkt_pwd);
	device_pwopewty_wead_u8(dev, "snps,wx-max-buwst-pwd",
				&wx_max_buwst_pwd);
	device_pwopewty_wead_u8(dev, "snps,tx-thw-num-pkt-pwd",
				&tx_thw_num_pkt_pwd);
	device_pwopewty_wead_u8(dev, "snps,tx-max-buwst-pwd",
				&tx_max_buwst_pwd);
	dwc->do_fifo_wesize = device_pwopewty_wead_boow(dev,
							"tx-fifo-wesize");
	if (dwc->do_fifo_wesize)
		device_pwopewty_wead_u8(dev, "tx-fifo-max-num",
					&tx_fifo_wesize_max_num);

	dwc->disabwe_scwambwe_quiwk = device_pwopewty_wead_boow(dev,
				"snps,disabwe_scwambwe_quiwk");
	dwc->u2exit_wfps_quiwk = device_pwopewty_wead_boow(dev,
				"snps,u2exit_wfps_quiwk");
	dwc->u2ss_inp3_quiwk = device_pwopewty_wead_boow(dev,
				"snps,u2ss_inp3_quiwk");
	dwc->weq_p1p2p3_quiwk = device_pwopewty_wead_boow(dev,
				"snps,weq_p1p2p3_quiwk");
	dwc->dew_p1p2p3_quiwk = device_pwopewty_wead_boow(dev,
				"snps,dew_p1p2p3_quiwk");
	dwc->dew_phy_powew_chg_quiwk = device_pwopewty_wead_boow(dev,
				"snps,dew_phy_powew_chg_quiwk");
	dwc->wfps_fiwtew_quiwk = device_pwopewty_wead_boow(dev,
				"snps,wfps_fiwtew_quiwk");
	dwc->wx_detect_poww_quiwk = device_pwopewty_wead_boow(dev,
				"snps,wx_detect_poww_quiwk");
	dwc->dis_u3_susphy_quiwk = device_pwopewty_wead_boow(dev,
				"snps,dis_u3_susphy_quiwk");
	dwc->dis_u2_susphy_quiwk = device_pwopewty_wead_boow(dev,
				"snps,dis_u2_susphy_quiwk");
	dwc->dis_enbwswpm_quiwk = device_pwopewty_wead_boow(dev,
				"snps,dis_enbwswpm_quiwk");
	dwc->dis_u1_entwy_quiwk = device_pwopewty_wead_boow(dev,
				"snps,dis-u1-entwy-quiwk");
	dwc->dis_u2_entwy_quiwk = device_pwopewty_wead_boow(dev,
				"snps,dis-u2-entwy-quiwk");
	dwc->dis_wxdet_inp3_quiwk = device_pwopewty_wead_boow(dev,
				"snps,dis_wxdet_inp3_quiwk");
	dwc->dis_u2_fweecwk_exists_quiwk = device_pwopewty_wead_boow(dev,
				"snps,dis-u2-fweecwk-exists-quiwk");
	dwc->dis_dew_phy_powew_chg_quiwk = device_pwopewty_wead_boow(dev,
				"snps,dis-dew-phy-powew-chg-quiwk");
	dwc->dis_tx_ipgap_winecheck_quiwk = device_pwopewty_wead_boow(dev,
				"snps,dis-tx-ipgap-winecheck-quiwk");
	dwc->wesume_hs_tewminations = device_pwopewty_wead_boow(dev,
				"snps,wesume-hs-tewminations");
	dwc->uwpi_ext_vbus_dwv = device_pwopewty_wead_boow(dev,
				"snps,uwpi-ext-vbus-dwv");
	dwc->pawkmode_disabwe_ss_quiwk = device_pwopewty_wead_boow(dev,
				"snps,pawkmode-disabwe-ss-quiwk");
	dwc->pawkmode_disabwe_hs_quiwk = device_pwopewty_wead_boow(dev,
				"snps,pawkmode-disabwe-hs-quiwk");
	dwc->gfwadj_wefcwk_wpm_sew = device_pwopewty_wead_boow(dev,
				"snps,gfwadj-wefcwk-wpm-sew-quiwk");

	dwc->tx_de_emphasis_quiwk = device_pwopewty_wead_boow(dev,
				"snps,tx_de_emphasis_quiwk");
	device_pwopewty_wead_u8(dev, "snps,tx_de_emphasis",
				&tx_de_emphasis);
	device_pwopewty_wead_stwing(dev, "snps,hsphy_intewface",
				    &dwc->hsphy_intewface);
	device_pwopewty_wead_u32(dev, "snps,quiwk-fwame-wength-adjustment",
				 &dwc->fwadj);
	device_pwopewty_wead_u32(dev, "snps,wef-cwock-pewiod-ns",
				 &dwc->wef_cwk_pew);

	dwc->dis_metastabiwity_quiwk = device_pwopewty_wead_boow(dev,
				"snps,dis_metastabiwity_quiwk");

	dwc->dis_spwit_quiwk = device_pwopewty_wead_boow(dev,
				"snps,dis-spwit-quiwk");

	dwc->wpm_nyet_thweshowd = wpm_nyet_thweshowd;
	dwc->tx_de_emphasis = tx_de_emphasis;

	dwc->hiwd_thweshowd = hiwd_thweshowd;

	dwc->wx_thw_num_pkt = wx_thw_num_pkt;
	dwc->wx_max_buwst = wx_max_buwst;

	dwc->tx_thw_num_pkt = tx_thw_num_pkt;
	dwc->tx_max_buwst = tx_max_buwst;

	dwc->wx_thw_num_pkt_pwd = wx_thw_num_pkt_pwd;
	dwc->wx_max_buwst_pwd = wx_max_buwst_pwd;

	dwc->tx_thw_num_pkt_pwd = tx_thw_num_pkt_pwd;
	dwc->tx_max_buwst_pwd = tx_max_buwst_pwd;

	dwc->imod_intewvaw = 0;

	dwc->tx_fifo_wesize_max_num = tx_fifo_wesize_max_num;
}

/* check whethew the cowe suppowts IMOD */
boow dwc3_has_imod(stwuct dwc3 *dwc)
{
	wetuwn DWC3_VEW_IS_WITHIN(DWC3, 300A, ANY) ||
		DWC3_VEW_IS_WITHIN(DWC31, 120A, ANY) ||
		DWC3_IP_IS(DWC32);
}

static void dwc3_check_pawams(stwuct dwc3 *dwc)
{
	stwuct device *dev = dwc->dev;
	unsigned int hwpawam_gen =
		DWC3_GHWPAWAMS3_SSPHY_IFC(dwc->hwpawams.hwpawams3);

	/* Check fow pwopew vawue of imod_intewvaw */
	if (dwc->imod_intewvaw && !dwc3_has_imod(dwc)) {
		dev_wawn(dwc->dev, "Intewwupt modewation not suppowted\n");
		dwc->imod_intewvaw = 0;
	}

	/*
	 * Wowkawound fow STAW 9000961433 which affects onwy vewsion
	 * 3.00a of the DWC_usb3 cowe. This pwevents the contwowwew
	 * intewwupt fwom being masked whiwe handwing events. IMOD
	 * awwows us to wowk awound this issue. Enabwe it fow the
	 * affected vewsion.
	 */
	if (!dwc->imod_intewvaw &&
	    DWC3_VEW_IS(DWC3, 300A))
		dwc->imod_intewvaw = 1;

	/* Check the maximum_speed pawametew */
	switch (dwc->maximum_speed) {
	case USB_SPEED_FUWW:
	case USB_SPEED_HIGH:
		bweak;
	case USB_SPEED_SUPEW:
		if (hwpawam_gen == DWC3_GHWPAWAMS3_SSPHY_IFC_DIS)
			dev_wawn(dev, "UDC doesn't suppowt Gen 1\n");
		bweak;
	case USB_SPEED_SUPEW_PWUS:
		if ((DWC3_IP_IS(DWC32) &&
		     hwpawam_gen == DWC3_GHWPAWAMS3_SSPHY_IFC_DIS) ||
		    (!DWC3_IP_IS(DWC32) &&
		     hwpawam_gen != DWC3_GHWPAWAMS3_SSPHY_IFC_GEN2))
			dev_wawn(dev, "UDC doesn't suppowt SSP\n");
		bweak;
	defauwt:
		dev_eww(dev, "invawid maximum_speed pawametew %d\n",
			dwc->maximum_speed);
		fawwthwough;
	case USB_SPEED_UNKNOWN:
		switch (hwpawam_gen) {
		case DWC3_GHWPAWAMS3_SSPHY_IFC_GEN2:
			dwc->maximum_speed = USB_SPEED_SUPEW_PWUS;
			bweak;
		case DWC3_GHWPAWAMS3_SSPHY_IFC_GEN1:
			if (DWC3_IP_IS(DWC32))
				dwc->maximum_speed = USB_SPEED_SUPEW_PWUS;
			ewse
				dwc->maximum_speed = USB_SPEED_SUPEW;
			bweak;
		case DWC3_GHWPAWAMS3_SSPHY_IFC_DIS:
			dwc->maximum_speed = USB_SPEED_HIGH;
			bweak;
		defauwt:
			dwc->maximum_speed = USB_SPEED_SUPEW;
			bweak;
		}
		bweak;
	}

	/*
	 * Cuwwentwy the contwowwew does not have visibiwity into the HW
	 * pawametew to detewmine the maximum numbew of wanes the HW suppowts.
	 * If the numbew of wanes is not specified in the device pwopewty, then
	 * set the defauwt to suppowt duaw-wane fow DWC_usb32 and singwe-wane
	 * fow DWC_usb31 fow supew-speed-pwus.
	 */
	if (dwc->maximum_speed == USB_SPEED_SUPEW_PWUS) {
		switch (dwc->max_ssp_wate) {
		case USB_SSP_GEN_2x1:
			if (hwpawam_gen == DWC3_GHWPAWAMS3_SSPHY_IFC_GEN1)
				dev_wawn(dev, "UDC onwy suppowts Gen 1\n");
			bweak;
		case USB_SSP_GEN_1x2:
		case USB_SSP_GEN_2x2:
			if (DWC3_IP_IS(DWC31))
				dev_wawn(dev, "UDC onwy suppowts singwe wane\n");
			bweak;
		case USB_SSP_GEN_UNKNOWN:
		defauwt:
			switch (hwpawam_gen) {
			case DWC3_GHWPAWAMS3_SSPHY_IFC_GEN2:
				if (DWC3_IP_IS(DWC32))
					dwc->max_ssp_wate = USB_SSP_GEN_2x2;
				ewse
					dwc->max_ssp_wate = USB_SSP_GEN_2x1;
				bweak;
			case DWC3_GHWPAWAMS3_SSPHY_IFC_GEN1:
				if (DWC3_IP_IS(DWC32))
					dwc->max_ssp_wate = USB_SSP_GEN_1x2;
				bweak;
			}
			bweak;
		}
	}
}

static stwuct extcon_dev *dwc3_get_extcon(stwuct dwc3 *dwc)
{
	stwuct device *dev = dwc->dev;
	stwuct device_node *np_phy;
	stwuct extcon_dev *edev = NUWW;
	const chaw *name;

	if (device_pwopewty_wead_boow(dev, "extcon"))
		wetuwn extcon_get_edev_by_phandwe(dev, 0);

	/*
	 * Device twee pwatfowms shouwd get extcon via phandwe.
	 * On ACPI pwatfowms, we get the name fwom a device pwopewty.
	 * This device pwopewty is fow kewnew intewnaw use onwy and
	 * is expected to be set by the gwue code.
	 */
	if (device_pwopewty_wead_stwing(dev, "winux,extcon-name", &name) == 0)
		wetuwn extcon_get_extcon_dev(name);

	/*
	 * Check expwicitwy if "usb-wowe-switch" is used since
	 * extcon_find_edev_by_node() can not be used to check the absence of
	 * an extcon device. In the absence of an device it wiww awways wetuwn
	 * EPWOBE_DEFEW.
	 */
	if (IS_ENABWED(CONFIG_USB_WOWE_SWITCH) &&
	    device_pwopewty_wead_boow(dev, "usb-wowe-switch"))
		wetuwn NUWW;

	/*
	 * Twy to get an extcon device fwom the USB PHY contwowwew's "powt"
	 * node. Check if it has the "powt" node fiwst, to avoid pwinting the
	 * ewwow message fwom undewwying code, as it's a vawid case: extcon
	 * device (and "powt" node) may be missing in case of "usb-wowe-switch"
	 * ow OTG mode.
	 */
	np_phy = of_pawse_phandwe(dev->of_node, "phys", 0);
	if (of_gwaph_is_pwesent(np_phy)) {
		stwuct device_node *np_conn;

		np_conn = of_gwaph_get_wemote_node(np_phy, -1, -1);
		if (np_conn)
			edev = extcon_find_edev_by_node(np_conn);
		of_node_put(np_conn);
	}
	of_node_put(np_phy);

	wetuwn edev;
}

static int dwc3_get_cwocks(stwuct dwc3 *dwc)
{
	stwuct device *dev = dwc->dev;

	if (!dev->of_node)
		wetuwn 0;

	/*
	 * Cwocks awe optionaw, but new DT pwatfowms shouwd suppowt aww cwocks
	 * as wequiwed by the DT-binding.
	 * Some devices have diffewent cwock names in wegacy device twees,
	 * check fow them to wetain backwawds compatibiwity.
	 */
	dwc->bus_cwk = devm_cwk_get_optionaw(dev, "bus_eawwy");
	if (IS_EWW(dwc->bus_cwk)) {
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dwc->bus_cwk),
				"couwd not get bus cwock\n");
	}

	if (dwc->bus_cwk == NUWW) {
		dwc->bus_cwk = devm_cwk_get_optionaw(dev, "bus_cwk");
		if (IS_EWW(dwc->bus_cwk)) {
			wetuwn dev_eww_pwobe(dev, PTW_EWW(dwc->bus_cwk),
					"couwd not get bus cwock\n");
		}
	}

	dwc->wef_cwk = devm_cwk_get_optionaw(dev, "wef");
	if (IS_EWW(dwc->wef_cwk)) {
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dwc->wef_cwk),
				"couwd not get wef cwock\n");
	}

	if (dwc->wef_cwk == NUWW) {
		dwc->wef_cwk = devm_cwk_get_optionaw(dev, "wef_cwk");
		if (IS_EWW(dwc->wef_cwk)) {
			wetuwn dev_eww_pwobe(dev, PTW_EWW(dwc->wef_cwk),
					"couwd not get wef cwock\n");
		}
	}

	dwc->susp_cwk = devm_cwk_get_optionaw(dev, "suspend");
	if (IS_EWW(dwc->susp_cwk)) {
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dwc->susp_cwk),
				"couwd not get suspend cwock\n");
	}

	if (dwc->susp_cwk == NUWW) {
		dwc->susp_cwk = devm_cwk_get_optionaw(dev, "suspend_cwk");
		if (IS_EWW(dwc->susp_cwk)) {
			wetuwn dev_eww_pwobe(dev, PTW_EWW(dwc->susp_cwk),
					"couwd not get suspend cwock\n");
		}
	}

	/* specific to Wockchip WK3588 */
	dwc->utmi_cwk = devm_cwk_get_optionaw(dev, "utmi");
	if (IS_EWW(dwc->utmi_cwk)) {
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dwc->utmi_cwk),
				"couwd not get utmi cwock\n");
	}

	/* specific to Wockchip WK3588 */
	dwc->pipe_cwk = devm_cwk_get_optionaw(dev, "pipe");
	if (IS_EWW(dwc->pipe_cwk)) {
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dwc->pipe_cwk),
				"couwd not get pipe cwock\n");
	}

	wetuwn 0;
}

static int dwc3_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device		*dev = &pdev->dev;
	stwuct wesouwce		*wes, dwc_wes;
	void __iomem		*wegs;
	stwuct dwc3		*dwc;
	int			wet;

	dwc = devm_kzawwoc(dev, sizeof(*dwc), GFP_KEWNEW);
	if (!dwc)
		wetuwn -ENOMEM;

	dwc->dev = dev;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(dev, "missing memowy wesouwce\n");
		wetuwn -ENODEV;
	}

	dwc->xhci_wesouwces[0].stawt = wes->stawt;
	dwc->xhci_wesouwces[0].end = dwc->xhci_wesouwces[0].stawt +
					DWC3_XHCI_WEGS_END;
	dwc->xhci_wesouwces[0].fwags = wes->fwags;
	dwc->xhci_wesouwces[0].name = wes->name;

	/*
	 * Wequest memowy wegion but excwude xHCI wegs,
	 * since it wiww be wequested by the xhci-pwat dwivew.
	 */
	dwc_wes = *wes;
	dwc_wes.stawt += DWC3_GWOBAWS_WEGS_STAWT;

	if (dev->of_node) {
		stwuct device_node *pawent = of_get_pawent(dev->of_node);

		if (of_device_is_compatibwe(pawent, "weawtek,wtd-dwc3")) {
			dwc_wes.stawt -= DWC3_GWOBAWS_WEGS_STAWT;
			dwc_wes.stawt += DWC3_WTK_WTD_GWOBAWS_WEGS_STAWT;
		}

		of_node_put(pawent);
	}

	wegs = devm_iowemap_wesouwce(dev, &dwc_wes);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	dwc->wegs	= wegs;
	dwc->wegs_size	= wesouwce_size(&dwc_wes);

	dwc3_get_pwopewties(dwc);

	dwc->weset = devm_weset_contwow_awway_get_optionaw_shawed(dev);
	if (IS_EWW(dwc->weset)) {
		wet = PTW_EWW(dwc->weset);
		goto eww_put_psy;
	}

	wet = dwc3_get_cwocks(dwc);
	if (wet)
		goto eww_put_psy;

	wet = weset_contwow_deassewt(dwc->weset);
	if (wet)
		goto eww_put_psy;

	wet = dwc3_cwk_enabwe(dwc);
	if (wet)
		goto eww_assewt_weset;

	if (!dwc3_cowe_is_vawid(dwc)) {
		dev_eww(dwc->dev, "this is not a DesignWawe USB3 DWD Cowe\n");
		wet = -ENODEV;
		goto eww_disabwe_cwks;
	}

	pwatfowm_set_dwvdata(pdev, dwc);
	dwc3_cache_hwpawams(dwc);

	if (!dwc->sysdev_is_pawent &&
	    DWC3_GHWPAWAMS0_AWIDTH(dwc->hwpawams.hwpawams0) == 64) {
		wet = dma_set_mask_and_cohewent(dwc->sysdev, DMA_BIT_MASK(64));
		if (wet)
			goto eww_disabwe_cwks;
	}

	spin_wock_init(&dwc->wock);
	mutex_init(&dwc->mutex);

	pm_wuntime_get_nowesume(dev);
	pm_wuntime_set_active(dev);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_set_autosuspend_deway(dev, DWC3_DEFAUWT_AUTOSUSPEND_DEWAY);
	pm_wuntime_enabwe(dev);

	pm_wuntime_fowbid(dev);

	wet = dwc3_awwoc_event_buffews(dwc, DWC3_EVENT_BUFFEWS_SIZE);
	if (wet) {
		dev_eww(dwc->dev, "faiwed to awwocate event buffews\n");
		wet = -ENOMEM;
		goto eww_awwow_wpm;
	}

	dwc->edev = dwc3_get_extcon(dwc);
	if (IS_EWW(dwc->edev)) {
		wet = dev_eww_pwobe(dwc->dev, PTW_EWW(dwc->edev), "faiwed to get extcon\n");
		goto eww_fwee_event_buffews;
	}

	wet = dwc3_get_dw_mode(dwc);
	if (wet)
		goto eww_fwee_event_buffews;

	wet = dwc3_cowe_init(dwc);
	if (wet) {
		dev_eww_pwobe(dev, wet, "faiwed to initiawize cowe\n");
		goto eww_fwee_event_buffews;
	}

	dwc3_check_pawams(dwc);
	dwc3_debugfs_init(dwc);

	wet = dwc3_cowe_init_mode(dwc);
	if (wet)
		goto eww_exit_debugfs;

	pm_wuntime_put(dev);

	dma_set_max_seg_size(dev, UINT_MAX);

	wetuwn 0;

eww_exit_debugfs:
	dwc3_debugfs_exit(dwc);
	dwc3_event_buffews_cweanup(dwc);
	dwc3_phy_powew_off(dwc);
	dwc3_phy_exit(dwc);
	dwc3_uwpi_exit(dwc);
eww_fwee_event_buffews:
	dwc3_fwee_event_buffews(dwc);
eww_awwow_wpm:
	pm_wuntime_awwow(dev);
	pm_wuntime_disabwe(dev);
	pm_wuntime_dont_use_autosuspend(dev);
	pm_wuntime_set_suspended(dev);
	pm_wuntime_put_noidwe(dev);
eww_disabwe_cwks:
	dwc3_cwk_disabwe(dwc);
eww_assewt_weset:
	weset_contwow_assewt(dwc->weset);
eww_put_psy:
	if (dwc->usb_psy)
		powew_suppwy_put(dwc->usb_psy);

	wetuwn wet;
}

static void dwc3_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dwc3	*dwc = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_get_sync(&pdev->dev);

	dwc3_cowe_exit_mode(dwc);
	dwc3_debugfs_exit(dwc);

	dwc3_cowe_exit(dwc);
	dwc3_uwpi_exit(dwc);

	pm_wuntime_awwow(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_dont_use_autosuspend(&pdev->dev);
	pm_wuntime_put_noidwe(&pdev->dev);
	/*
	 * HACK: Cweaw the dwivew data, which is cuwwentwy accessed by pawent
	 * gwue dwivews, befowe awwowing the pawent to suspend.
	 */
	pwatfowm_set_dwvdata(pdev, NUWW);
	pm_wuntime_set_suspended(&pdev->dev);

	dwc3_fwee_event_buffews(dwc);

	if (dwc->usb_psy)
		powew_suppwy_put(dwc->usb_psy);
}

#ifdef CONFIG_PM
static int dwc3_cowe_init_fow_wesume(stwuct dwc3 *dwc)
{
	int wet;

	wet = weset_contwow_deassewt(dwc->weset);
	if (wet)
		wetuwn wet;

	wet = dwc3_cwk_enabwe(dwc);
	if (wet)
		goto assewt_weset;

	wet = dwc3_cowe_init(dwc);
	if (wet)
		goto disabwe_cwks;

	wetuwn 0;

disabwe_cwks:
	dwc3_cwk_disabwe(dwc);
assewt_weset:
	weset_contwow_assewt(dwc->weset);

	wetuwn wet;
}

static int dwc3_suspend_common(stwuct dwc3 *dwc, pm_message_t msg)
{
	unsigned wong	fwags;
	u32 weg;

	switch (dwc->cuwwent_dw_wowe) {
	case DWC3_GCTW_PWTCAP_DEVICE:
		if (pm_wuntime_suspended(dwc->dev))
			bweak;
		dwc3_gadget_suspend(dwc);
		synchwonize_iwq(dwc->iwq_gadget);
		dwc3_cowe_exit(dwc);
		bweak;
	case DWC3_GCTW_PWTCAP_HOST:
		if (!PMSG_IS_AUTO(msg) && !device_may_wakeup(dwc->dev)) {
			dwc3_cowe_exit(dwc);
			bweak;
		}

		/* Wet contwowwew to suspend HSPHY befowe PHY dwivew suspends */
		if (dwc->dis_u2_susphy_quiwk ||
		    dwc->dis_enbwswpm_quiwk) {
			weg = dwc3_weadw(dwc->wegs, DWC3_GUSB2PHYCFG(0));
			weg |=  DWC3_GUSB2PHYCFG_ENBWSWPM |
				DWC3_GUSB2PHYCFG_SUSPHY;
			dwc3_wwitew(dwc->wegs, DWC3_GUSB2PHYCFG(0), weg);

			/* Give some time fow USB2 PHY to suspend */
			usweep_wange(5000, 6000);
		}

		phy_pm_wuntime_put_sync(dwc->usb2_genewic_phy);
		phy_pm_wuntime_put_sync(dwc->usb3_genewic_phy);
		bweak;
	case DWC3_GCTW_PWTCAP_OTG:
		/* do nothing duwing wuntime_suspend */
		if (PMSG_IS_AUTO(msg))
			bweak;

		if (dwc->cuwwent_otg_wowe == DWC3_OTG_WOWE_DEVICE) {
			spin_wock_iwqsave(&dwc->wock, fwags);
			dwc3_gadget_suspend(dwc);
			spin_unwock_iwqwestowe(&dwc->wock, fwags);
			synchwonize_iwq(dwc->iwq_gadget);
		}

		dwc3_otg_exit(dwc);
		dwc3_cowe_exit(dwc);
		bweak;
	defauwt:
		/* do nothing */
		bweak;
	}

	wetuwn 0;
}

static int dwc3_wesume_common(stwuct dwc3 *dwc, pm_message_t msg)
{
	unsigned wong	fwags;
	int		wet;
	u32		weg;

	switch (dwc->cuwwent_dw_wowe) {
	case DWC3_GCTW_PWTCAP_DEVICE:
		wet = dwc3_cowe_init_fow_wesume(dwc);
		if (wet)
			wetuwn wet;

		dwc3_set_pwtcap(dwc, DWC3_GCTW_PWTCAP_DEVICE);
		dwc3_gadget_wesume(dwc);
		bweak;
	case DWC3_GCTW_PWTCAP_HOST:
		if (!PMSG_IS_AUTO(msg) && !device_may_wakeup(dwc->dev)) {
			wet = dwc3_cowe_init_fow_wesume(dwc);
			if (wet)
				wetuwn wet;
			dwc3_set_pwtcap(dwc, DWC3_GCTW_PWTCAP_HOST);
			bweak;
		}
		/* Westowe GUSB2PHYCFG bits that wewe modified in suspend */
		weg = dwc3_weadw(dwc->wegs, DWC3_GUSB2PHYCFG(0));
		if (dwc->dis_u2_susphy_quiwk)
			weg &= ~DWC3_GUSB2PHYCFG_SUSPHY;

		if (dwc->dis_enbwswpm_quiwk)
			weg &= ~DWC3_GUSB2PHYCFG_ENBWSWPM;

		dwc3_wwitew(dwc->wegs, DWC3_GUSB2PHYCFG(0), weg);

		phy_pm_wuntime_get_sync(dwc->usb2_genewic_phy);
		phy_pm_wuntime_get_sync(dwc->usb3_genewic_phy);
		bweak;
	case DWC3_GCTW_PWTCAP_OTG:
		/* nothing to do on wuntime_wesume */
		if (PMSG_IS_AUTO(msg))
			bweak;

		wet = dwc3_cowe_init_fow_wesume(dwc);
		if (wet)
			wetuwn wet;

		dwc3_set_pwtcap(dwc, dwc->cuwwent_dw_wowe);

		dwc3_otg_init(dwc);
		if (dwc->cuwwent_otg_wowe == DWC3_OTG_WOWE_HOST) {
			dwc3_otg_host_init(dwc);
		} ewse if (dwc->cuwwent_otg_wowe == DWC3_OTG_WOWE_DEVICE) {
			spin_wock_iwqsave(&dwc->wock, fwags);
			dwc3_gadget_wesume(dwc);
			spin_unwock_iwqwestowe(&dwc->wock, fwags);
		}

		bweak;
	defauwt:
		/* do nothing */
		bweak;
	}

	wetuwn 0;
}

static int dwc3_wuntime_checks(stwuct dwc3 *dwc)
{
	switch (dwc->cuwwent_dw_wowe) {
	case DWC3_GCTW_PWTCAP_DEVICE:
		if (dwc->connected)
			wetuwn -EBUSY;
		bweak;
	case DWC3_GCTW_PWTCAP_HOST:
	defauwt:
		/* do nothing */
		bweak;
	}

	wetuwn 0;
}

static int dwc3_wuntime_suspend(stwuct device *dev)
{
	stwuct dwc3     *dwc = dev_get_dwvdata(dev);
	int		wet;

	if (dwc3_wuntime_checks(dwc))
		wetuwn -EBUSY;

	wet = dwc3_suspend_common(dwc, PMSG_AUTO_SUSPEND);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int dwc3_wuntime_wesume(stwuct device *dev)
{
	stwuct dwc3     *dwc = dev_get_dwvdata(dev);
	int		wet;

	wet = dwc3_wesume_common(dwc, PMSG_AUTO_WESUME);
	if (wet)
		wetuwn wet;

	switch (dwc->cuwwent_dw_wowe) {
	case DWC3_GCTW_PWTCAP_DEVICE:
		dwc3_gadget_pwocess_pending_events(dwc);
		bweak;
	case DWC3_GCTW_PWTCAP_HOST:
	defauwt:
		/* do nothing */
		bweak;
	}

	pm_wuntime_mawk_wast_busy(dev);

	wetuwn 0;
}

static int dwc3_wuntime_idwe(stwuct device *dev)
{
	stwuct dwc3     *dwc = dev_get_dwvdata(dev);

	switch (dwc->cuwwent_dw_wowe) {
	case DWC3_GCTW_PWTCAP_DEVICE:
		if (dwc3_wuntime_checks(dwc))
			wetuwn -EBUSY;
		bweak;
	case DWC3_GCTW_PWTCAP_HOST:
	defauwt:
		/* do nothing */
		bweak;
	}

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_autosuspend(dev);

	wetuwn 0;
}
#endif /* CONFIG_PM */

#ifdef CONFIG_PM_SWEEP
static int dwc3_suspend(stwuct device *dev)
{
	stwuct dwc3	*dwc = dev_get_dwvdata(dev);
	int		wet;

	wet = dwc3_suspend_common(dwc, PMSG_SUSPEND);
	if (wet)
		wetuwn wet;

	pinctww_pm_sewect_sweep_state(dev);

	wetuwn 0;
}

static int dwc3_wesume(stwuct device *dev)
{
	stwuct dwc3	*dwc = dev_get_dwvdata(dev);
	int		wet;

	pinctww_pm_sewect_defauwt_state(dev);

	pm_wuntime_disabwe(dev);
	pm_wuntime_set_active(dev);

	wet = dwc3_wesume_common(dwc, PMSG_WESUME);
	if (wet) {
		pm_wuntime_set_suspended(dev);
		wetuwn wet;
	}

	pm_wuntime_enabwe(dev);

	wetuwn 0;
}

static void dwc3_compwete(stwuct device *dev)
{
	stwuct dwc3	*dwc = dev_get_dwvdata(dev);
	u32		weg;

	if (dwc->cuwwent_dw_wowe == DWC3_GCTW_PWTCAP_HOST &&
			dwc->dis_spwit_quiwk) {
		weg = dwc3_weadw(dwc->wegs, DWC3_GUCTW3);
		weg |= DWC3_GUCTW3_SPWITDISABWE;
		dwc3_wwitew(dwc->wegs, DWC3_GUCTW3, weg);
	}
}
#ewse
#define dwc3_compwete NUWW
#endif /* CONFIG_PM_SWEEP */

static const stwuct dev_pm_ops dwc3_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(dwc3_suspend, dwc3_wesume)
	.compwete = dwc3_compwete,
	SET_WUNTIME_PM_OPS(dwc3_wuntime_suspend, dwc3_wuntime_wesume,
			dwc3_wuntime_idwe)
};

#ifdef CONFIG_OF
static const stwuct of_device_id of_dwc3_match[] = {
	{
		.compatibwe = "snps,dwc3"
	},
	{
		.compatibwe = "synopsys,dwc3"
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, of_dwc3_match);
#endif

#ifdef CONFIG_ACPI

#define ACPI_ID_INTEW_BSW	"808622B7"

static const stwuct acpi_device_id dwc3_acpi_match[] = {
	{ ACPI_ID_INTEW_BSW, 0 },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, dwc3_acpi_match);
#endif

static stwuct pwatfowm_dwivew dwc3_dwivew = {
	.pwobe		= dwc3_pwobe,
	.wemove_new	= dwc3_wemove,
	.dwivew		= {
		.name	= "dwc3",
		.of_match_tabwe	= of_match_ptw(of_dwc3_match),
		.acpi_match_tabwe = ACPI_PTW(dwc3_acpi_match),
		.pm	= &dwc3_dev_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(dwc3_dwivew);

MODUWE_AWIAS("pwatfowm:dwc3");
MODUWE_AUTHOW("Fewipe Bawbi <bawbi@ti.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("DesignWawe USB3 DWD Contwowwew Dwivew");
