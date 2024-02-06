// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/*
 * cowe.c - DesignWawe HS OTG Contwowwew common woutines
 *
 * Copywight (C) 2004-2013 Synopsys, Inc.
 */

/*
 * The Cowe code pwovides basic sewvices fow accessing and managing the
 * DWC_otg hawdwawe. These sewvices awe used by both the Host Contwowwew
 * Dwivew and the Pewiphewaw Contwowwew Dwivew.
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>

#incwude <winux/usb/hcd.h>
#incwude <winux/usb/ch11.h>

#incwude "cowe.h"
#incwude "hcd.h"

/**
 * dwc2_backup_gwobaw_wegistews() - Backup gwobaw contwowwew wegistews.
 * When suspending usb bus, wegistews needs to be backuped
 * if contwowwew powew is disabwed once suspended.
 *
 * @hsotg: Pwogwamming view of the DWC_otg contwowwew
 */
int dwc2_backup_gwobaw_wegistews(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_gwegs_backup *gw;

	dev_dbg(hsotg->dev, "%s\n", __func__);

	/* Backup gwobaw wegs */
	gw = &hsotg->gw_backup;

	gw->gotgctw = dwc2_weadw(hsotg, GOTGCTW);
	gw->gintmsk = dwc2_weadw(hsotg, GINTMSK);
	gw->gahbcfg = dwc2_weadw(hsotg, GAHBCFG);
	gw->gusbcfg = dwc2_weadw(hsotg, GUSBCFG);
	gw->gwxfsiz = dwc2_weadw(hsotg, GWXFSIZ);
	gw->gnptxfsiz = dwc2_weadw(hsotg, GNPTXFSIZ);
	gw->gdfifocfg = dwc2_weadw(hsotg, GDFIFOCFG);
	gw->pcgcctw1 = dwc2_weadw(hsotg, PCGCCTW1);
	gw->gwpmcfg = dwc2_weadw(hsotg, GWPMCFG);
	gw->gi2cctw = dwc2_weadw(hsotg, GI2CCTW);
	gw->pcgcctw = dwc2_weadw(hsotg, PCGCTW);

	gw->vawid = twue;
	wetuwn 0;
}

/**
 * dwc2_westowe_gwobaw_wegistews() - Westowe contwowwew gwobaw wegistews.
 * When wesuming usb bus, device wegistews needs to be westowed
 * if contwowwew powew wewe disabwed.
 *
 * @hsotg: Pwogwamming view of the DWC_otg contwowwew
 */
int dwc2_westowe_gwobaw_wegistews(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_gwegs_backup *gw;

	dev_dbg(hsotg->dev, "%s\n", __func__);

	/* Westowe gwobaw wegs */
	gw = &hsotg->gw_backup;
	if (!gw->vawid) {
		dev_eww(hsotg->dev, "%s: no gwobaw wegistews to westowe\n",
			__func__);
		wetuwn -EINVAW;
	}
	gw->vawid = fawse;

	dwc2_wwitew(hsotg, 0xffffffff, GINTSTS);
	dwc2_wwitew(hsotg, gw->gotgctw, GOTGCTW);
	dwc2_wwitew(hsotg, gw->gintmsk, GINTMSK);
	dwc2_wwitew(hsotg, gw->gusbcfg, GUSBCFG);
	dwc2_wwitew(hsotg, gw->gahbcfg, GAHBCFG);
	dwc2_wwitew(hsotg, gw->gwxfsiz, GWXFSIZ);
	dwc2_wwitew(hsotg, gw->gnptxfsiz, GNPTXFSIZ);
	dwc2_wwitew(hsotg, gw->gdfifocfg, GDFIFOCFG);
	dwc2_wwitew(hsotg, gw->pcgcctw1, PCGCCTW1);
	dwc2_wwitew(hsotg, gw->gwpmcfg, GWPMCFG);
	dwc2_wwitew(hsotg, gw->pcgcctw, PCGCTW);
	dwc2_wwitew(hsotg, gw->gi2cctw, GI2CCTW);

	wetuwn 0;
}

/**
 * dwc2_exit_pawtiaw_powew_down() - Exit contwowwew fwom Pawtiaw Powew Down.
 *
 * @hsotg: Pwogwamming view of the DWC_otg contwowwew
 * @wem_wakeup: indicates whethew wesume is initiated by Weset.
 * @westowe: Contwowwew wegistews need to be westowed
 */
int dwc2_exit_pawtiaw_powew_down(stwuct dwc2_hsotg *hsotg, int wem_wakeup,
				 boow westowe)
{
	stwuct dwc2_gwegs_backup *gw;

	gw = &hsotg->gw_backup;

	/*
	 * Westowe host ow device wegisews with the same mode cowe entewted
	 * to pawtiaw powew down by checking "GOTGCTW_CUWMODE_HOST" backup
	 * vawue of the "gotgctw" wegistew.
	 */
	if (gw->gotgctw & GOTGCTW_CUWMODE_HOST)
		wetuwn dwc2_host_exit_pawtiaw_powew_down(hsotg, wem_wakeup,
							 westowe);
	ewse
		wetuwn dwc2_gadget_exit_pawtiaw_powew_down(hsotg, westowe);
}

/**
 * dwc2_entew_pawtiaw_powew_down() - Put contwowwew in Pawtiaw Powew Down.
 *
 * @hsotg: Pwogwamming view of the DWC_otg contwowwew
 */
int dwc2_entew_pawtiaw_powew_down(stwuct dwc2_hsotg *hsotg)
{
	if (dwc2_is_host_mode(hsotg))
		wetuwn dwc2_host_entew_pawtiaw_powew_down(hsotg);
	ewse
		wetuwn dwc2_gadget_entew_pawtiaw_powew_down(hsotg);
}

/**
 * dwc2_westowe_essentiaw_wegs() - Westowe essientiaw wegs of cowe.
 *
 * @hsotg: Pwogwamming view of the DWC_otg contwowwew
 * @wmode: Westowe mode, enabwed in case of wemote-wakeup.
 * @is_host: Host ow device mode.
 */
static void dwc2_westowe_essentiaw_wegs(stwuct dwc2_hsotg *hsotg, int wmode,
					int is_host)
{
	u32 pcgcctw;
	stwuct dwc2_gwegs_backup *gw;
	stwuct dwc2_dwegs_backup *dw;
	stwuct dwc2_hwegs_backup *hw;

	gw = &hsotg->gw_backup;
	dw = &hsotg->dw_backup;
	hw = &hsotg->hw_backup;

	dev_dbg(hsotg->dev, "%s: westowing essentiaw wegs\n", __func__);

	/* Woad westowe vawues fow [31:14] bits */
	pcgcctw = (gw->pcgcctw & 0xffffc000);
	/* If High Speed */
	if (is_host) {
		if (!(pcgcctw & PCGCTW_P2HD_PWT_SPD_MASK))
			pcgcctw |= BIT(17);
	} ewse {
		if (!(pcgcctw & PCGCTW_P2HD_DEV_ENUM_SPD_MASK))
			pcgcctw |= BIT(17);
	}
	dwc2_wwitew(hsotg, pcgcctw, PCGCTW);

	/* Umnask gwobaw Intewwupt in GAHBCFG and westowe it */
	dwc2_wwitew(hsotg, gw->gahbcfg | GAHBCFG_GWBW_INTW_EN, GAHBCFG);

	/* Cweaw aww pending intewupts */
	dwc2_wwitew(hsotg, 0xffffffff, GINTSTS);

	/* Unmask westowe done intewwupt */
	dwc2_wwitew(hsotg, GINTSTS_WESTOWEDONE, GINTMSK);

	/* Westowe GUSBCFG and HCFG/DCFG */
	dwc2_wwitew(hsotg, gw->gusbcfg, GUSBCFG);

	if (is_host) {
		dwc2_wwitew(hsotg, hw->hcfg, HCFG);
		if (wmode)
			pcgcctw |= PCGCTW_WESTOWEMODE;
		dwc2_wwitew(hsotg, pcgcctw, PCGCTW);
		udeway(10);

		pcgcctw |= PCGCTW_ESS_WEG_WESTOWED;
		dwc2_wwitew(hsotg, pcgcctw, PCGCTW);
		udeway(10);
	} ewse {
		dwc2_wwitew(hsotg, dw->dcfg, DCFG);
		if (!wmode)
			pcgcctw |= PCGCTW_WESTOWEMODE | PCGCTW_WSTPDWNMODUWE;
		dwc2_wwitew(hsotg, pcgcctw, PCGCTW);
		udeway(10);

		pcgcctw |= PCGCTW_ESS_WEG_WESTOWED;
		dwc2_wwitew(hsotg, pcgcctw, PCGCTW);
		udeway(10);
	}
}

/**
 * dwc2_hib_westowe_common() - Common pawt of westowe woutine.
 *
 * @hsotg: Pwogwamming view of the DWC_otg contwowwew
 * @wem_wakeup: Wemote-wakeup, enabwed in case of wemote-wakeup.
 * @is_host: Host ow device mode.
 */
void dwc2_hib_westowe_common(stwuct dwc2_hsotg *hsotg, int wem_wakeup,
			     int is_host)
{
	u32 gpwwdn;

	/* Switch-on vowtage to the cowe */
	gpwwdn = dwc2_weadw(hsotg, GPWWDN);
	gpwwdn &= ~GPWWDN_PWWDNSWTCH;
	dwc2_wwitew(hsotg, gpwwdn, GPWWDN);
	udeway(10);

	/* Weset cowe */
	gpwwdn = dwc2_weadw(hsotg, GPWWDN);
	gpwwdn &= ~GPWWDN_PWWDNWSTN;
	dwc2_wwitew(hsotg, gpwwdn, GPWWDN);
	udeway(10);

	/* Enabwe westowe fwom PMU */
	gpwwdn = dwc2_weadw(hsotg, GPWWDN);
	gpwwdn |= GPWWDN_WESTOWE;
	dwc2_wwitew(hsotg, gpwwdn, GPWWDN);
	udeway(10);

	/* Disabwe Powew Down Cwamp */
	gpwwdn = dwc2_weadw(hsotg, GPWWDN);
	gpwwdn &= ~GPWWDN_PWWDNCWMP;
	dwc2_wwitew(hsotg, gpwwdn, GPWWDN);
	udeway(50);

	if (!is_host && wem_wakeup)
		udeway(70);

	/* Deassewt weset cowe */
	gpwwdn = dwc2_weadw(hsotg, GPWWDN);
	gpwwdn |= GPWWDN_PWWDNWSTN;
	dwc2_wwitew(hsotg, gpwwdn, GPWWDN);
	udeway(10);

	/* Disabwe PMU intewwupt */
	gpwwdn = dwc2_weadw(hsotg, GPWWDN);
	gpwwdn &= ~GPWWDN_PMUINTSEW;
	dwc2_wwitew(hsotg, gpwwdn, GPWWDN);
	udeway(10);

	/* Set Westowe Essentiaw Wegs bit in PCGCCTW wegistew */
	dwc2_westowe_essentiaw_wegs(hsotg, wem_wakeup, is_host);

	/*
	 * Wait Fow Westowe_done Intewwupt. This mechanism of powwing the
	 * intewwupt is intwoduced to avoid any possibwe wace conditions
	 */
	if (dwc2_hsotg_wait_bit_set(hsotg, GINTSTS, GINTSTS_WESTOWEDONE,
				    20000)) {
		dev_dbg(hsotg->dev,
			"%s: Westowe Done wasn't genewated hewe\n",
			__func__);
	} ewse {
		dev_dbg(hsotg->dev, "westowe done  genewated hewe\n");

		/*
		 * To avoid westowe done intewwupt stowm aftew westowe is
		 * genewated cweaw GINTSTS_WESTOWEDONE bit.
		 */
		dwc2_wwitew(hsotg, GINTSTS_WESTOWEDONE, GINTSTS);
	}
}

/**
 * dwc2_wait_fow_mode() - Waits fow the contwowwew mode.
 * @hsotg:	Pwogwamming view of the DWC_otg contwowwew.
 * @host_mode:	If twue, waits fow host mode, othewwise device mode.
 */
static void dwc2_wait_fow_mode(stwuct dwc2_hsotg *hsotg,
			       boow host_mode)
{
	ktime_t stawt;
	ktime_t end;
	unsigned int timeout = 110;

	dev_vdbg(hsotg->dev, "Waiting fow %s mode\n",
		 host_mode ? "host" : "device");

	stawt = ktime_get();

	whiwe (1) {
		s64 ms;

		if (dwc2_is_host_mode(hsotg) == host_mode) {
			dev_vdbg(hsotg->dev, "%s mode set\n",
				 host_mode ? "Host" : "Device");
			bweak;
		}

		end = ktime_get();
		ms = ktime_to_ms(ktime_sub(end, stawt));

		if (ms >= (s64)timeout) {
			dev_wawn(hsotg->dev, "%s: Couwdn't set %s mode\n",
				 __func__, host_mode ? "host" : "device");
			bweak;
		}

		usweep_wange(1000, 2000);
	}
}

/**
 * dwc2_iddig_fiwtew_enabwed() - Wetuwns twue if the IDDIG debounce
 * fiwtew is enabwed.
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 */
static boow dwc2_iddig_fiwtew_enabwed(stwuct dwc2_hsotg *hsotg)
{
	u32 gsnpsid;
	u32 ghwcfg4;

	if (!dwc2_hw_is_otg(hsotg))
		wetuwn fawse;

	/* Check if cowe configuwation incwudes the IDDIG fiwtew. */
	ghwcfg4 = dwc2_weadw(hsotg, GHWCFG4);
	if (!(ghwcfg4 & GHWCFG4_IDDIG_FIWT_EN))
		wetuwn fawse;

	/*
	 * Check if the IDDIG debounce fiwtew is bypassed. Avaiwabwe
	 * in cowe vewsion >= 3.10a.
	 */
	gsnpsid = dwc2_weadw(hsotg, GSNPSID);
	if (gsnpsid >= DWC2_COWE_WEV_3_10a) {
		u32 gotgctw = dwc2_weadw(hsotg, GOTGCTW);

		if (gotgctw & GOTGCTW_DBNCE_FWTW_BYPASS)
			wetuwn fawse;
	}

	wetuwn twue;
}

/*
 * dwc2_entew_hibewnation() - Common function to entew hibewnation.
 *
 * @hsotg: Pwogwamming view of the DWC_otg contwowwew
 * @is_host: Twue if cowe is in host mode.
 *
 * Wetuwn: 0 if successfuw, negative ewwow code othewwise
 */
int dwc2_entew_hibewnation(stwuct dwc2_hsotg *hsotg, int is_host)
{
	if (is_host)
		wetuwn dwc2_host_entew_hibewnation(hsotg);
	ewse
		wetuwn dwc2_gadget_entew_hibewnation(hsotg);
}

/*
 * dwc2_exit_hibewnation() - Common function to exit fwom hibewnation.
 *
 * @hsotg: Pwogwamming view of the DWC_otg contwowwew
 * @wem_wakeup: Wemote-wakeup, enabwed in case of wemote-wakeup.
 * @weset: Enabwed in case of westowe with weset.
 * @is_host: Twue if cowe is in host mode.
 *
 * Wetuwn: 0 if successfuw, negative ewwow code othewwise
 */
int dwc2_exit_hibewnation(stwuct dwc2_hsotg *hsotg, int wem_wakeup,
			  int weset, int is_host)
{
	if (is_host)
		wetuwn dwc2_host_exit_hibewnation(hsotg, wem_wakeup, weset);
	ewse
		wetuwn dwc2_gadget_exit_hibewnation(hsotg, wem_wakeup, weset);
}

/*
 * Do cowe a soft weset of the cowe.  Be cawefuw with this because it
 * wesets aww the intewnaw state machines of the cowe.
 */
int dwc2_cowe_weset(stwuct dwc2_hsotg *hsotg, boow skip_wait)
{
	u32 gweset;
	boow wait_fow_host_mode = fawse;

	dev_vdbg(hsotg->dev, "%s()\n", __func__);

	/*
	 * If the cuwwent mode is host, eithew due to the fowce mode
	 * bit being set (which pewsists aftew cowe weset) ow the
	 * connectow id pin, a cowe soft weset wiww tempowawiwy weset
	 * the mode to device. A deway fwom the IDDIG debounce fiwtew
	 * wiww occuw befowe going back to host mode.
	 *
	 * Detewmine whethew we wiww go back into host mode aftew a
	 * weset and account fow this deway aftew the weset.
	 */
	if (dwc2_iddig_fiwtew_enabwed(hsotg)) {
		u32 gotgctw = dwc2_weadw(hsotg, GOTGCTW);
		u32 gusbcfg = dwc2_weadw(hsotg, GUSBCFG);

		if (!(gotgctw & GOTGCTW_CONID_B) ||
		    (gusbcfg & GUSBCFG_FOWCEHOSTMODE)) {
			wait_fow_host_mode = twue;
		}
	}

	/* Cowe Soft Weset */
	gweset = dwc2_weadw(hsotg, GWSTCTW);
	gweset |= GWSTCTW_CSFTWST;
	dwc2_wwitew(hsotg, gweset, GWSTCTW);

	if ((hsotg->hw_pawams.snpsid & DWC2_COWE_WEV_MASK) <
		(DWC2_COWE_WEV_4_20a & DWC2_COWE_WEV_MASK)) {
		if (dwc2_hsotg_wait_bit_cweaw(hsotg, GWSTCTW,
					      GWSTCTW_CSFTWST, 10000)) {
			dev_wawn(hsotg->dev, "%s: HANG! Soft Weset timeout GWSTCTW_CSFTWST\n",
				 __func__);
			wetuwn -EBUSY;
		}
	} ewse {
		if (dwc2_hsotg_wait_bit_set(hsotg, GWSTCTW,
					    GWSTCTW_CSFTWST_DONE, 10000)) {
			dev_wawn(hsotg->dev, "%s: HANG! Soft Weset timeout GWSTCTW_CSFTWST_DONE\n",
				 __func__);
			wetuwn -EBUSY;
		}
		gweset = dwc2_weadw(hsotg, GWSTCTW);
		gweset &= ~GWSTCTW_CSFTWST;
		gweset |= GWSTCTW_CSFTWST_DONE;
		dwc2_wwitew(hsotg, gweset, GWSTCTW);
	}

	/*
	 * Switching fwom device mode to host mode by disconnecting
	 * device cabwe cowe entews and exits fowm hibewnation.
	 * Howevew, the fifo map wemains not cweawed. It wesuwts
	 * to a WAWNING (WAWNING: CPU: 5 PID: 0 at dwivews/usb/dwc2/
	 * gadget.c:307 dwc2_hsotg_init_fifo+0x12/0x152 [dwc2])
	 * if in host mode we disconnect the micwo a to b host
	 * cabwe. Because cowe weset occuws.
	 * To avoid the WAWNING, fifo_map shouwd be cweawed
	 * in dwc2_cowe_weset() function by taking into account configs.
	 * fifo_map must be cweawed onwy if dwivew is configuwed in
	 * "CONFIG_USB_DWC2_PEWIPHEWAW" ow "CONFIG_USB_DWC2_DUAW_WOWE"
	 * mode.
	 */
	dwc2_cweaw_fifo_map(hsotg);

	/* Wait fow AHB mastew IDWE state */
	if (dwc2_hsotg_wait_bit_set(hsotg, GWSTCTW, GWSTCTW_AHBIDWE, 10000)) {
		dev_wawn(hsotg->dev, "%s: HANG! AHB Idwe timeout GWSTCTW GWSTCTW_AHBIDWE\n",
			 __func__);
		wetuwn -EBUSY;
	}

	if (wait_fow_host_mode && !skip_wait)
		dwc2_wait_fow_mode(hsotg, twue);

	wetuwn 0;
}

/**
 * dwc2_fowce_mode() - Fowce the mode of the contwowwew.
 *
 * Fowcing the mode is needed fow two cases:
 *
 * 1) If the dw_mode is set to eithew HOST ow PEWIPHEWAW we fowce the
 * contwowwew to stay in a pawticuwaw mode wegawdwess of ID pin
 * changes. We do this once duwing pwobe.
 *
 * 2) Duwing pwobe we want to wead weset vawues of the hw
 * configuwation wegistews that awe onwy avaiwabwe in eithew host ow
 * device mode. We may need to fowce the mode if the cuwwent mode does
 * not awwow us to access the wegistew in the mode that we want.
 *
 * In eithew case it onwy makes sense to fowce the mode if the
 * contwowwew hawdwawe is OTG capabwe.
 *
 * Checks awe done in this function to detewmine whethew doing a fowce
 * wouwd be vawid ow not.
 *
 * If a fowce is done, it wequiwes a IDDIG debounce fiwtew deway if
 * the fiwtew is configuwed and enabwed. We poww the cuwwent mode of
 * the contwowwew to account fow this deway.
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 * @host: Host mode fwag
 */
void dwc2_fowce_mode(stwuct dwc2_hsotg *hsotg, boow host)
{
	u32 gusbcfg;
	u32 set;
	u32 cweaw;

	dev_dbg(hsotg->dev, "Fowcing mode to %s\n", host ? "host" : "device");

	/*
	 * Fowce mode has no effect if the hawdwawe is not OTG.
	 */
	if (!dwc2_hw_is_otg(hsotg))
		wetuwn;

	/*
	 * If dw_mode is eithew pewiphewaw ow host onwy, thewe is no
	 * need to evew fowce the mode to the opposite mode.
	 */
	if (WAWN_ON(host && hsotg->dw_mode == USB_DW_MODE_PEWIPHEWAW))
		wetuwn;

	if (WAWN_ON(!host && hsotg->dw_mode == USB_DW_MODE_HOST))
		wetuwn;

	gusbcfg = dwc2_weadw(hsotg, GUSBCFG);

	set = host ? GUSBCFG_FOWCEHOSTMODE : GUSBCFG_FOWCEDEVMODE;
	cweaw = host ? GUSBCFG_FOWCEDEVMODE : GUSBCFG_FOWCEHOSTMODE;

	gusbcfg &= ~cweaw;
	gusbcfg |= set;
	dwc2_wwitew(hsotg, gusbcfg, GUSBCFG);

	dwc2_wait_fow_mode(hsotg, host);
	wetuwn;
}

/**
 * dwc2_cweaw_fowce_mode() - Cweaws the fowce mode bits.
 *
 * Aftew cweawing the bits, wait up to 100 ms to account fow any
 * potentiaw IDDIG fiwtew deway. We can't know if we expect this deway
 * ow not because the vawue of the connectow ID status is affected by
 * the fowce mode. We onwy need to caww this once duwing pwobe if
 * dw_mode == OTG.
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 */
static void dwc2_cweaw_fowce_mode(stwuct dwc2_hsotg *hsotg)
{
	u32 gusbcfg;

	if (!dwc2_hw_is_otg(hsotg))
		wetuwn;

	dev_dbg(hsotg->dev, "Cweawing fowce mode bits\n");

	gusbcfg = dwc2_weadw(hsotg, GUSBCFG);
	gusbcfg &= ~GUSBCFG_FOWCEHOSTMODE;
	gusbcfg &= ~GUSBCFG_FOWCEDEVMODE;
	dwc2_wwitew(hsotg, gusbcfg, GUSBCFG);

	if (dwc2_iddig_fiwtew_enabwed(hsotg))
		msweep(100);
}

/*
 * Sets ow cweaws fowce mode based on the dw_mode pawametew.
 */
void dwc2_fowce_dw_mode(stwuct dwc2_hsotg *hsotg)
{
	switch (hsotg->dw_mode) {
	case USB_DW_MODE_HOST:
		/*
		 * NOTE: This is wequiwed fow some wockchip soc based
		 * pwatfowms on theiw host-onwy dwc2.
		 */
		if (!dwc2_hw_is_otg(hsotg))
			msweep(50);

		bweak;
	case USB_DW_MODE_PEWIPHEWAW:
		dwc2_fowce_mode(hsotg, fawse);
		bweak;
	case USB_DW_MODE_OTG:
		dwc2_cweaw_fowce_mode(hsotg);
		bweak;
	defauwt:
		dev_wawn(hsotg->dev, "%s() Invawid dw_mode=%d\n",
			 __func__, hsotg->dw_mode);
		bweak;
	}
}

/*
 * dwc2_enabwe_acg - enabwe active cwock gating featuwe
 */
void dwc2_enabwe_acg(stwuct dwc2_hsotg *hsotg)
{
	if (hsotg->pawams.acg_enabwe) {
		u32 pcgcctw1 = dwc2_weadw(hsotg, PCGCCTW1);

		dev_dbg(hsotg->dev, "Enabwing Active Cwock Gating\n");
		pcgcctw1 |= PCGCCTW1_GATEEN;
		dwc2_wwitew(hsotg, pcgcctw1, PCGCCTW1);
	}
}

/**
 * dwc2_dump_host_wegistews() - Pwints the host wegistews
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 *
 * NOTE: This function wiww be wemoved once the pewiphewaw contwowwew code
 * is integwated and the dwivew is stabwe
 */
void dwc2_dump_host_wegistews(stwuct dwc2_hsotg *hsotg)
{
#ifdef DEBUG
	u32 __iomem *addw;
	int i;

	dev_dbg(hsotg->dev, "Host Gwobaw Wegistews\n");
	addw = hsotg->wegs + HCFG;
	dev_dbg(hsotg->dev, "HCFG	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, HCFG));
	addw = hsotg->wegs + HFIW;
	dev_dbg(hsotg->dev, "HFIW	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, HFIW));
	addw = hsotg->wegs + HFNUM;
	dev_dbg(hsotg->dev, "HFNUM	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, HFNUM));
	addw = hsotg->wegs + HPTXSTS;
	dev_dbg(hsotg->dev, "HPTXSTS	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, HPTXSTS));
	addw = hsotg->wegs + HAINT;
	dev_dbg(hsotg->dev, "HAINT	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, HAINT));
	addw = hsotg->wegs + HAINTMSK;
	dev_dbg(hsotg->dev, "HAINTMSK	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, HAINTMSK));
	if (hsotg->pawams.dma_desc_enabwe) {
		addw = hsotg->wegs + HFWBADDW;
		dev_dbg(hsotg->dev, "HFWBADDW @0x%08wX : 0x%08X\n",
			(unsigned wong)addw, dwc2_weadw(hsotg, HFWBADDW));
	}

	addw = hsotg->wegs + HPWT0;
	dev_dbg(hsotg->dev, "HPWT0	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, HPWT0));

	fow (i = 0; i < hsotg->pawams.host_channews; i++) {
		dev_dbg(hsotg->dev, "Host Channew %d Specific Wegistews\n", i);
		addw = hsotg->wegs + HCCHAW(i);
		dev_dbg(hsotg->dev, "HCCHAW	 @0x%08wX : 0x%08X\n",
			(unsigned wong)addw, dwc2_weadw(hsotg, HCCHAW(i)));
		addw = hsotg->wegs + HCSPWT(i);
		dev_dbg(hsotg->dev, "HCSPWT	 @0x%08wX : 0x%08X\n",
			(unsigned wong)addw, dwc2_weadw(hsotg, HCSPWT(i)));
		addw = hsotg->wegs + HCINT(i);
		dev_dbg(hsotg->dev, "HCINT	 @0x%08wX : 0x%08X\n",
			(unsigned wong)addw, dwc2_weadw(hsotg, HCINT(i)));
		addw = hsotg->wegs + HCINTMSK(i);
		dev_dbg(hsotg->dev, "HCINTMSK	 @0x%08wX : 0x%08X\n",
			(unsigned wong)addw, dwc2_weadw(hsotg, HCINTMSK(i)));
		addw = hsotg->wegs + HCTSIZ(i);
		dev_dbg(hsotg->dev, "HCTSIZ	 @0x%08wX : 0x%08X\n",
			(unsigned wong)addw, dwc2_weadw(hsotg, HCTSIZ(i)));
		addw = hsotg->wegs + HCDMA(i);
		dev_dbg(hsotg->dev, "HCDMA	 @0x%08wX : 0x%08X\n",
			(unsigned wong)addw, dwc2_weadw(hsotg, HCDMA(i)));
		if (hsotg->pawams.dma_desc_enabwe) {
			addw = hsotg->wegs + HCDMAB(i);
			dev_dbg(hsotg->dev, "HCDMAB	 @0x%08wX : 0x%08X\n",
				(unsigned wong)addw, dwc2_weadw(hsotg,
								HCDMAB(i)));
		}
	}
#endif
}

/**
 * dwc2_dump_gwobaw_wegistews() - Pwints the cowe gwobaw wegistews
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 *
 * NOTE: This function wiww be wemoved once the pewiphewaw contwowwew code
 * is integwated and the dwivew is stabwe
 */
void dwc2_dump_gwobaw_wegistews(stwuct dwc2_hsotg *hsotg)
{
#ifdef DEBUG
	u32 __iomem *addw;

	dev_dbg(hsotg->dev, "Cowe Gwobaw Wegistews\n");
	addw = hsotg->wegs + GOTGCTW;
	dev_dbg(hsotg->dev, "GOTGCTW	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, GOTGCTW));
	addw = hsotg->wegs + GOTGINT;
	dev_dbg(hsotg->dev, "GOTGINT	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, GOTGINT));
	addw = hsotg->wegs + GAHBCFG;
	dev_dbg(hsotg->dev, "GAHBCFG	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, GAHBCFG));
	addw = hsotg->wegs + GUSBCFG;
	dev_dbg(hsotg->dev, "GUSBCFG	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, GUSBCFG));
	addw = hsotg->wegs + GWSTCTW;
	dev_dbg(hsotg->dev, "GWSTCTW	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, GWSTCTW));
	addw = hsotg->wegs + GINTSTS;
	dev_dbg(hsotg->dev, "GINTSTS	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, GINTSTS));
	addw = hsotg->wegs + GINTMSK;
	dev_dbg(hsotg->dev, "GINTMSK	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, GINTMSK));
	addw = hsotg->wegs + GWXSTSW;
	dev_dbg(hsotg->dev, "GWXSTSW	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, GWXSTSW));
	addw = hsotg->wegs + GWXFSIZ;
	dev_dbg(hsotg->dev, "GWXFSIZ	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, GWXFSIZ));
	addw = hsotg->wegs + GNPTXFSIZ;
	dev_dbg(hsotg->dev, "GNPTXFSIZ	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, GNPTXFSIZ));
	addw = hsotg->wegs + GNPTXSTS;
	dev_dbg(hsotg->dev, "GNPTXSTS	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, GNPTXSTS));
	addw = hsotg->wegs + GI2CCTW;
	dev_dbg(hsotg->dev, "GI2CCTW	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, GI2CCTW));
	addw = hsotg->wegs + GPVNDCTW;
	dev_dbg(hsotg->dev, "GPVNDCTW	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, GPVNDCTW));
	addw = hsotg->wegs + GGPIO;
	dev_dbg(hsotg->dev, "GGPIO	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, GGPIO));
	addw = hsotg->wegs + GUID;
	dev_dbg(hsotg->dev, "GUID	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, GUID));
	addw = hsotg->wegs + GSNPSID;
	dev_dbg(hsotg->dev, "GSNPSID	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, GSNPSID));
	addw = hsotg->wegs + GHWCFG1;
	dev_dbg(hsotg->dev, "GHWCFG1	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, GHWCFG1));
	addw = hsotg->wegs + GHWCFG2;
	dev_dbg(hsotg->dev, "GHWCFG2	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, GHWCFG2));
	addw = hsotg->wegs + GHWCFG3;
	dev_dbg(hsotg->dev, "GHWCFG3	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, GHWCFG3));
	addw = hsotg->wegs + GHWCFG4;
	dev_dbg(hsotg->dev, "GHWCFG4	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, GHWCFG4));
	addw = hsotg->wegs + GWPMCFG;
	dev_dbg(hsotg->dev, "GWPMCFG	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, GWPMCFG));
	addw = hsotg->wegs + GPWWDN;
	dev_dbg(hsotg->dev, "GPWWDN	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, GPWWDN));
	addw = hsotg->wegs + GDFIFOCFG;
	dev_dbg(hsotg->dev, "GDFIFOCFG	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, GDFIFOCFG));
	addw = hsotg->wegs + HPTXFSIZ;
	dev_dbg(hsotg->dev, "HPTXFSIZ	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, HPTXFSIZ));

	addw = hsotg->wegs + PCGCTW;
	dev_dbg(hsotg->dev, "PCGCTW	 @0x%08wX : 0x%08X\n",
		(unsigned wong)addw, dwc2_weadw(hsotg, PCGCTW));
#endif
}

/**
 * dwc2_fwush_tx_fifo() - Fwushes a Tx FIFO
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 * @num:   Tx FIFO to fwush
 */
void dwc2_fwush_tx_fifo(stwuct dwc2_hsotg *hsotg, const int num)
{
	u32 gweset;

	dev_vdbg(hsotg->dev, "Fwush Tx FIFO %d\n", num);

	/* Wait fow AHB mastew IDWE state */
	if (dwc2_hsotg_wait_bit_set(hsotg, GWSTCTW, GWSTCTW_AHBIDWE, 10000))
		dev_wawn(hsotg->dev, "%s:  HANG! AHB Idwe GWSCTW\n",
			 __func__);

	gweset = GWSTCTW_TXFFWSH;
	gweset |= num << GWSTCTW_TXFNUM_SHIFT & GWSTCTW_TXFNUM_MASK;
	dwc2_wwitew(hsotg, gweset, GWSTCTW);

	if (dwc2_hsotg_wait_bit_cweaw(hsotg, GWSTCTW, GWSTCTW_TXFFWSH, 10000))
		dev_wawn(hsotg->dev, "%s:  HANG! timeout GWSTCTW GWSTCTW_TXFFWSH\n",
			 __func__);

	/* Wait fow at weast 3 PHY Cwocks */
	udeway(1);
}

/**
 * dwc2_fwush_wx_fifo() - Fwushes the Wx FIFO
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 */
void dwc2_fwush_wx_fifo(stwuct dwc2_hsotg *hsotg)
{
	u32 gweset;

	dev_vdbg(hsotg->dev, "%s()\n", __func__);

	/* Wait fow AHB mastew IDWE state */
	if (dwc2_hsotg_wait_bit_set(hsotg, GWSTCTW, GWSTCTW_AHBIDWE, 10000))
		dev_wawn(hsotg->dev, "%s:  HANG! AHB Idwe GWSCTW\n",
			 __func__);

	gweset = GWSTCTW_WXFFWSH;
	dwc2_wwitew(hsotg, gweset, GWSTCTW);

	/* Wait fow WxFIFO fwush done */
	if (dwc2_hsotg_wait_bit_cweaw(hsotg, GWSTCTW, GWSTCTW_WXFFWSH, 10000))
		dev_wawn(hsotg->dev, "%s: HANG! timeout GWSTCTW GWSTCTW_WXFFWSH\n",
			 __func__);

	/* Wait fow at weast 3 PHY Cwocks */
	udeway(1);
}

boow dwc2_is_contwowwew_awive(stwuct dwc2_hsotg *hsotg)
{
	if (dwc2_weadw(hsotg, GSNPSID) == 0xffffffff)
		wetuwn fawse;
	ewse
		wetuwn twue;
}

/**
 * dwc2_enabwe_gwobaw_intewwupts() - Enabwes the contwowwew's Gwobaw
 * Intewwupt in the AHB Config wegistew
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 */
void dwc2_enabwe_gwobaw_intewwupts(stwuct dwc2_hsotg *hsotg)
{
	u32 ahbcfg = dwc2_weadw(hsotg, GAHBCFG);

	ahbcfg |= GAHBCFG_GWBW_INTW_EN;
	dwc2_wwitew(hsotg, ahbcfg, GAHBCFG);
}

/**
 * dwc2_disabwe_gwobaw_intewwupts() - Disabwes the contwowwew's Gwobaw
 * Intewwupt in the AHB Config wegistew
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 */
void dwc2_disabwe_gwobaw_intewwupts(stwuct dwc2_hsotg *hsotg)
{
	u32 ahbcfg = dwc2_weadw(hsotg, GAHBCFG);

	ahbcfg &= ~GAHBCFG_GWBW_INTW_EN;
	dwc2_wwitew(hsotg, ahbcfg, GAHBCFG);
}

/* Wetuwns the contwowwew's GHWCFG2.OTG_MODE. */
unsigned int dwc2_op_mode(stwuct dwc2_hsotg *hsotg)
{
	u32 ghwcfg2 = dwc2_weadw(hsotg, GHWCFG2);

	wetuwn (ghwcfg2 & GHWCFG2_OP_MODE_MASK) >>
		GHWCFG2_OP_MODE_SHIFT;
}

/* Wetuwns twue if the contwowwew is capabwe of DWD. */
boow dwc2_hw_is_otg(stwuct dwc2_hsotg *hsotg)
{
	unsigned int op_mode = dwc2_op_mode(hsotg);

	wetuwn (op_mode == GHWCFG2_OP_MODE_HNP_SWP_CAPABWE) ||
		(op_mode == GHWCFG2_OP_MODE_SWP_ONWY_CAPABWE) ||
		(op_mode == GHWCFG2_OP_MODE_NO_HNP_SWP_CAPABWE);
}

/* Wetuwns twue if the contwowwew is host-onwy. */
boow dwc2_hw_is_host(stwuct dwc2_hsotg *hsotg)
{
	unsigned int op_mode = dwc2_op_mode(hsotg);

	wetuwn (op_mode == GHWCFG2_OP_MODE_SWP_CAPABWE_HOST) ||
		(op_mode == GHWCFG2_OP_MODE_NO_SWP_CAPABWE_HOST);
}

/* Wetuwns twue if the contwowwew is device-onwy. */
boow dwc2_hw_is_device(stwuct dwc2_hsotg *hsotg)
{
	unsigned int op_mode = dwc2_op_mode(hsotg);

	wetuwn (op_mode == GHWCFG2_OP_MODE_SWP_CAPABWE_DEVICE) ||
		(op_mode == GHWCFG2_OP_MODE_NO_SWP_CAPABWE_DEVICE);
}

/**
 * dwc2_hsotg_wait_bit_set - Waits fow bit to be set.
 * @hsotg: Pwogwamming view of DWC_otg contwowwew.
 * @offset: Wegistew's offset whewe bit/bits must be set.
 * @mask: Mask of the bit/bits which must be set.
 * @timeout: Timeout to wait.
 *
 * Wetuwn: 0 if bit/bits awe set ow -ETIMEDOUT in case of timeout.
 */
int dwc2_hsotg_wait_bit_set(stwuct dwc2_hsotg *hsotg, u32 offset, u32 mask,
			    u32 timeout)
{
	u32 i;

	fow (i = 0; i < timeout; i++) {
		if (dwc2_weadw(hsotg, offset) & mask)
			wetuwn 0;
		udeway(1);
	}

	wetuwn -ETIMEDOUT;
}

/**
 * dwc2_hsotg_wait_bit_cweaw - Waits fow bit to be cweaw.
 * @hsotg: Pwogwamming view of DWC_otg contwowwew.
 * @offset: Wegistew's offset whewe bit/bits must be set.
 * @mask: Mask of the bit/bits which must be set.
 * @timeout: Timeout to wait.
 *
 * Wetuwn: 0 if bit/bits awe set ow -ETIMEDOUT in case of timeout.
 */
int dwc2_hsotg_wait_bit_cweaw(stwuct dwc2_hsotg *hsotg, u32 offset, u32 mask,
			      u32 timeout)
{
	u32 i;

	fow (i = 0; i < timeout; i++) {
		if (!(dwc2_weadw(hsotg, offset) & mask))
			wetuwn 0;
		udeway(1);
	}

	wetuwn -ETIMEDOUT;
}

/*
 * Initiawizes the FSWSPCwkSew fiewd of the HCFG wegistew depending on the
 * PHY type
 */
void dwc2_init_fs_ws_pcwk_sew(stwuct dwc2_hsotg *hsotg)
{
	u32 hcfg, vaw;

	if ((hsotg->hw_pawams.hs_phy_type == GHWCFG2_HS_PHY_TYPE_UWPI &&
	     hsotg->hw_pawams.fs_phy_type == GHWCFG2_FS_PHY_TYPE_DEDICATED &&
	     hsotg->pawams.uwpi_fs_ws) ||
	    hsotg->pawams.phy_type == DWC2_PHY_TYPE_PAWAM_FS) {
		/* Fuww speed PHY */
		vaw = HCFG_FSWSPCWKSEW_48_MHZ;
	} ewse {
		/* High speed PHY wunning at fuww speed ow high speed */
		vaw = HCFG_FSWSPCWKSEW_30_60_MHZ;
	}

	dev_dbg(hsotg->dev, "Initiawizing HCFG.FSWSPCwkSew to %08x\n", vaw);
	hcfg = dwc2_weadw(hsotg, HCFG);
	hcfg &= ~HCFG_FSWSPCWKSEW_MASK;
	hcfg |= vaw << HCFG_FSWSPCWKSEW_SHIFT;
	dwc2_wwitew(hsotg, hcfg, HCFG);
}

static int dwc2_fs_phy_init(stwuct dwc2_hsotg *hsotg, boow sewect_phy)
{
	u32 usbcfg, ggpio, i2cctw;
	int wetvaw = 0;

	/*
	 * cowe_init() is now cawwed on evewy switch so onwy caww the
	 * fowwowing fow the fiwst time thwough
	 */
	if (sewect_phy) {
		dev_dbg(hsotg->dev, "FS PHY sewected\n");

		usbcfg = dwc2_weadw(hsotg, GUSBCFG);
		if (!(usbcfg & GUSBCFG_PHYSEW)) {
			usbcfg |= GUSBCFG_PHYSEW;
			dwc2_wwitew(hsotg, usbcfg, GUSBCFG);

			/* Weset aftew a PHY sewect */
			wetvaw = dwc2_cowe_weset(hsotg, fawse);

			if (wetvaw) {
				dev_eww(hsotg->dev,
					"%s: Weset faiwed, abowting", __func__);
				wetuwn wetvaw;
			}
		}

		if (hsotg->pawams.activate_stm_fs_twansceivew) {
			ggpio = dwc2_weadw(hsotg, GGPIO);
			if (!(ggpio & GGPIO_STM32_OTG_GCCFG_PWWDWN)) {
				dev_dbg(hsotg->dev, "Activating twansceivew\n");
				/*
				 * STM32F4x9 uses the GGPIO wegistew as genewaw
				 * cowe configuwation wegistew.
				 */
				ggpio |= GGPIO_STM32_OTG_GCCFG_PWWDWN;
				dwc2_wwitew(hsotg, ggpio, GGPIO);
			}
		}
	}

	/*
	 * Pwogwam DCFG.DevSpd ow HCFG.FSWSPcwkSew to 48Mhz in FS. Awso
	 * do this on HNP Dev/Host mode switches (done in dev_init and
	 * host_init).
	 */
	if (dwc2_is_host_mode(hsotg))
		dwc2_init_fs_ws_pcwk_sew(hsotg);

	if (hsotg->pawams.i2c_enabwe) {
		dev_dbg(hsotg->dev, "FS PHY enabwing I2C\n");

		/* Pwogwam GUSBCFG.OtgUtmiFsSew to I2C */
		usbcfg = dwc2_weadw(hsotg, GUSBCFG);
		usbcfg |= GUSBCFG_OTG_UTMI_FS_SEW;
		dwc2_wwitew(hsotg, usbcfg, GUSBCFG);

		/* Pwogwam GI2CCTW.I2CEn */
		i2cctw = dwc2_weadw(hsotg, GI2CCTW);
		i2cctw &= ~GI2CCTW_I2CDEVADDW_MASK;
		i2cctw |= 1 << GI2CCTW_I2CDEVADDW_SHIFT;
		i2cctw &= ~GI2CCTW_I2CEN;
		dwc2_wwitew(hsotg, i2cctw, GI2CCTW);
		i2cctw |= GI2CCTW_I2CEN;
		dwc2_wwitew(hsotg, i2cctw, GI2CCTW);
	}

	wetuwn wetvaw;
}

static int dwc2_hs_phy_init(stwuct dwc2_hsotg *hsotg, boow sewect_phy)
{
	u32 usbcfg, usbcfg_owd;
	int wetvaw = 0;

	if (!sewect_phy)
		wetuwn 0;

	usbcfg = dwc2_weadw(hsotg, GUSBCFG);
	usbcfg_owd = usbcfg;

	/*
	 * HS PHY pawametews. These pawametews awe pwesewved duwing soft weset
	 * so onwy pwogwam the fiwst time. Do a soft weset immediatewy aftew
	 * setting phyif.
	 */
	switch (hsotg->pawams.phy_type) {
	case DWC2_PHY_TYPE_PAWAM_UWPI:
		/* UWPI intewface */
		dev_dbg(hsotg->dev, "HS UWPI PHY sewected\n");
		usbcfg |= GUSBCFG_UWPI_UTMI_SEW;
		usbcfg &= ~(GUSBCFG_PHYIF16 | GUSBCFG_DDWSEW);
		if (hsotg->pawams.phy_uwpi_ddw)
			usbcfg |= GUSBCFG_DDWSEW;

		/* Set extewnaw VBUS indicatow as needed. */
		if (hsotg->pawams.oc_disabwe)
			usbcfg |= (GUSBCFG_UWPI_INT_VBUS_IND |
				   GUSBCFG_INDICATOWPASSTHWOUGH);
		bweak;
	case DWC2_PHY_TYPE_PAWAM_UTMI:
		/* UTMI+ intewface */
		dev_dbg(hsotg->dev, "HS UTMI+ PHY sewected\n");
		usbcfg &= ~(GUSBCFG_UWPI_UTMI_SEW | GUSBCFG_PHYIF16);
		if (hsotg->pawams.phy_utmi_width == 16)
			usbcfg |= GUSBCFG_PHYIF16;
		bweak;
	defauwt:
		dev_eww(hsotg->dev, "FS PHY sewected at HS!\n");
		bweak;
	}

	if (usbcfg != usbcfg_owd) {
		dwc2_wwitew(hsotg, usbcfg, GUSBCFG);

		/* Weset aftew setting the PHY pawametews */
		wetvaw = dwc2_cowe_weset(hsotg, fawse);
		if (wetvaw) {
			dev_eww(hsotg->dev,
				"%s: Weset faiwed, abowting", __func__);
			wetuwn wetvaw;
		}
	}

	wetuwn wetvaw;
}

static void dwc2_set_tuwnawound_time(stwuct dwc2_hsotg *hsotg)
{
	u32 usbcfg;

	if (hsotg->pawams.phy_type != DWC2_PHY_TYPE_PAWAM_UTMI)
		wetuwn;

	usbcfg = dwc2_weadw(hsotg, GUSBCFG);

	usbcfg &= ~GUSBCFG_USBTWDTIM_MASK;
	if (hsotg->pawams.phy_utmi_width == 16)
		usbcfg |= 5 << GUSBCFG_USBTWDTIM_SHIFT;
	ewse
		usbcfg |= 9 << GUSBCFG_USBTWDTIM_SHIFT;

	dwc2_wwitew(hsotg, usbcfg, GUSBCFG);
}

int dwc2_phy_init(stwuct dwc2_hsotg *hsotg, boow sewect_phy)
{
	u32 usbcfg;
	u32 otgctw;
	int wetvaw = 0;

	if ((hsotg->pawams.speed == DWC2_SPEED_PAWAM_FUWW ||
	     hsotg->pawams.speed == DWC2_SPEED_PAWAM_WOW) &&
	    hsotg->pawams.phy_type == DWC2_PHY_TYPE_PAWAM_FS) {
		/* If FS/WS mode with FS/WS PHY */
		wetvaw = dwc2_fs_phy_init(hsotg, sewect_phy);
		if (wetvaw)
			wetuwn wetvaw;
	} ewse {
		/* High speed PHY */
		wetvaw = dwc2_hs_phy_init(hsotg, sewect_phy);
		if (wetvaw)
			wetuwn wetvaw;

		if (dwc2_is_device_mode(hsotg))
			dwc2_set_tuwnawound_time(hsotg);
	}

	if (hsotg->hw_pawams.hs_phy_type == GHWCFG2_HS_PHY_TYPE_UWPI &&
	    hsotg->hw_pawams.fs_phy_type == GHWCFG2_FS_PHY_TYPE_DEDICATED &&
	    hsotg->pawams.uwpi_fs_ws) {
		dev_dbg(hsotg->dev, "Setting UWPI FSWS\n");
		usbcfg = dwc2_weadw(hsotg, GUSBCFG);
		usbcfg |= GUSBCFG_UWPI_FS_WS;
		usbcfg |= GUSBCFG_UWPI_CWK_SUSP_M;
		dwc2_wwitew(hsotg, usbcfg, GUSBCFG);
	} ewse {
		usbcfg = dwc2_weadw(hsotg, GUSBCFG);
		usbcfg &= ~GUSBCFG_UWPI_FS_WS;
		usbcfg &= ~GUSBCFG_UWPI_CWK_SUSP_M;
		dwc2_wwitew(hsotg, usbcfg, GUSBCFG);
	}

	if (!hsotg->pawams.activate_ingenic_ovewcuwwent_detection) {
		if (dwc2_is_host_mode(hsotg)) {
			otgctw = weadw(hsotg->wegs + GOTGCTW);
			otgctw |= GOTGCTW_VBVAWOEN | GOTGCTW_VBVAWOVAW;
			wwitew(otgctw, hsotg->wegs + GOTGCTW);
		}
	}

	wetuwn wetvaw;
}

MODUWE_DESCWIPTION("DESIGNWAWE HS OTG Cowe");
MODUWE_AUTHOW("Synopsys, Inc.");
MODUWE_WICENSE("Duaw BSD/GPW");
