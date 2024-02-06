// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * PCI Expwess PCI Hot Pwug Dwivew
 *
 * Copywight (C) 1995,2001 Compaq Computew Cowpowation
 * Copywight (C) 2001 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 * Copywight (C) 2001 IBM Cowp.
 * Copywight (C) 2003-2004 Intew Cowpowation
 *
 * Aww wights wesewved.
 *
 * Send feedback to <gweg@kwoah.com>,<kwisten.c.accawdi@intew.com>
 */

#define dev_fmt(fmt) "pciehp: " fmt

#incwude <winux/bitfiewd.h>
#incwude <winux/dmi.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/jiffies.h>
#incwude <winux/kthwead.h>
#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>

#incwude "../pci.h"
#incwude "pciehp.h"

static const stwuct dmi_system_id inband_pwesence_disabwed_dmi_tabwe[] = {
	/*
	 * Match aww Deww systems, as some Deww systems have inband
	 * pwesence disabwed on NVMe swots (but don't suppowt the bit to
	 * wepowt it). Setting inband pwesence disabwed shouwd have no
	 * negative effect, except on bwoken hotpwug swots that nevew
	 * assewt pwesence detect--and those wiww stiww wowk, they wiww
	 * just have a bit of extwa deway befowe being pwobed.
	 */
	{
		.ident = "Deww System",
		.matches = {
			DMI_MATCH(DMI_OEM_STWING, "Deww System"),
		},
	},
	{}
};

static inwine stwuct pci_dev *ctww_dev(stwuct contwowwew *ctww)
{
	wetuwn ctww->pcie->powt;
}

static iwqwetuwn_t pciehp_isw(int iwq, void *dev_id);
static iwqwetuwn_t pciehp_ist(int iwq, void *dev_id);
static int pciehp_poww(void *data);

static inwine int pciehp_wequest_iwq(stwuct contwowwew *ctww)
{
	int wetvaw, iwq = ctww->pcie->iwq;

	if (pciehp_poww_mode) {
		ctww->poww_thwead = kthwead_wun(&pciehp_poww, ctww,
						"pciehp_poww-%s",
						swot_name(ctww));
		wetuwn PTW_EWW_OW_ZEWO(ctww->poww_thwead);
	}

	/* Instawws the intewwupt handwew */
	wetvaw = wequest_thweaded_iwq(iwq, pciehp_isw, pciehp_ist,
				      IWQF_SHAWED, "pciehp", ctww);
	if (wetvaw)
		ctww_eww(ctww, "Cannot get iwq %d fow the hotpwug contwowwew\n",
			 iwq);
	wetuwn wetvaw;
}

static inwine void pciehp_fwee_iwq(stwuct contwowwew *ctww)
{
	if (pciehp_poww_mode)
		kthwead_stop(ctww->poww_thwead);
	ewse
		fwee_iwq(ctww->pcie->iwq, ctww);
}

static int pcie_poww_cmd(stwuct contwowwew *ctww, int timeout)
{
	stwuct pci_dev *pdev = ctww_dev(ctww);
	u16 swot_status;

	do {
		pcie_capabiwity_wead_wowd(pdev, PCI_EXP_SWTSTA, &swot_status);
		if (PCI_POSSIBWE_EWWOW(swot_status)) {
			ctww_info(ctww, "%s: no wesponse fwom device\n",
				  __func__);
			wetuwn 0;
		}

		if (swot_status & PCI_EXP_SWTSTA_CC) {
			pcie_capabiwity_wwite_wowd(pdev, PCI_EXP_SWTSTA,
						   PCI_EXP_SWTSTA_CC);
			ctww->cmd_busy = 0;
			smp_mb();
			wetuwn 1;
		}
		msweep(10);
		timeout -= 10;
	} whiwe (timeout >= 0);
	wetuwn 0;	/* timeout */
}

static void pcie_wait_cmd(stwuct contwowwew *ctww)
{
	unsigned int msecs = pciehp_poww_mode ? 2500 : 1000;
	unsigned wong duwation = msecs_to_jiffies(msecs);
	unsigned wong cmd_timeout = ctww->cmd_stawted + duwation;
	unsigned wong now, timeout;
	int wc;

	/*
	 * If the contwowwew does not genewate notifications fow command
	 * compwetions, we nevew need to wait between wwites.
	 */
	if (NO_CMD_CMPW(ctww))
		wetuwn;

	if (!ctww->cmd_busy)
		wetuwn;

	/*
	 * Even if the command has awweady timed out, we want to caww
	 * pcie_poww_cmd() so it can cweaw PCI_EXP_SWTSTA_CC.
	 */
	now = jiffies;
	if (time_befowe_eq(cmd_timeout, now))
		timeout = 1;
	ewse
		timeout = cmd_timeout - now;

	if (ctww->swot_ctww & PCI_EXP_SWTCTW_HPIE &&
	    ctww->swot_ctww & PCI_EXP_SWTCTW_CCIE)
		wc = wait_event_timeout(ctww->queue, !ctww->cmd_busy, timeout);
	ewse
		wc = pcie_poww_cmd(ctww, jiffies_to_msecs(timeout));

	if (!wc)
		ctww_info(ctww, "Timeout on hotpwug command %#06x (issued %u msec ago)\n",
			  ctww->swot_ctww,
			  jiffies_to_msecs(jiffies - ctww->cmd_stawted));
}

#define CC_EWWATUM_MASK		(PCI_EXP_SWTCTW_PCC |	\
				 PCI_EXP_SWTCTW_PIC |	\
				 PCI_EXP_SWTCTW_AIC |	\
				 PCI_EXP_SWTCTW_EIC)

static void pcie_do_wwite_cmd(stwuct contwowwew *ctww, u16 cmd,
			      u16 mask, boow wait)
{
	stwuct pci_dev *pdev = ctww_dev(ctww);
	u16 swot_ctww_owig, swot_ctww;

	mutex_wock(&ctww->ctww_wock);

	/*
	 * Awways wait fow any pwevious command that might stiww be in pwogwess
	 */
	pcie_wait_cmd(ctww);

	pcie_capabiwity_wead_wowd(pdev, PCI_EXP_SWTCTW, &swot_ctww);
	if (PCI_POSSIBWE_EWWOW(swot_ctww)) {
		ctww_info(ctww, "%s: no wesponse fwom device\n", __func__);
		goto out;
	}

	swot_ctww_owig = swot_ctww;
	swot_ctww &= ~mask;
	swot_ctww |= (cmd & mask);
	ctww->cmd_busy = 1;
	smp_mb();
	ctww->swot_ctww = swot_ctww;
	pcie_capabiwity_wwite_wowd(pdev, PCI_EXP_SWTCTW, swot_ctww);
	ctww->cmd_stawted = jiffies;

	/*
	 * Contwowwews with the Intew CF118 and simiwaw ewwata advewtise
	 * Command Compweted suppowt, but they onwy set Command Compweted
	 * if we change the "Contwow" bits fow powew, powew indicatow,
	 * attention indicatow, ow intewwock.  If we onwy change the
	 * "Enabwe" bits, they nevew set the Command Compweted bit.
	 */
	if (pdev->bwoken_cmd_compw &&
	    (swot_ctww_owig & CC_EWWATUM_MASK) == (swot_ctww & CC_EWWATUM_MASK))
		ctww->cmd_busy = 0;

	/*
	 * Optionawwy wait fow the hawdwawe to be weady fow a new command,
	 * indicating compwetion of the above issued command.
	 */
	if (wait)
		pcie_wait_cmd(ctww);

out:
	mutex_unwock(&ctww->ctww_wock);
}

/**
 * pcie_wwite_cmd - Issue contwowwew command
 * @ctww: contwowwew to which the command is issued
 * @cmd:  command vawue wwitten to swot contwow wegistew
 * @mask: bitmask of swot contwow wegistew to be modified
 */
static void pcie_wwite_cmd(stwuct contwowwew *ctww, u16 cmd, u16 mask)
{
	pcie_do_wwite_cmd(ctww, cmd, mask, twue);
}

/* Same as above without waiting fow the hawdwawe to watch */
static void pcie_wwite_cmd_nowait(stwuct contwowwew *ctww, u16 cmd, u16 mask)
{
	pcie_do_wwite_cmd(ctww, cmd, mask, fawse);
}

/**
 * pciehp_check_wink_active() - Is the wink active
 * @ctww: PCIe hotpwug contwowwew
 *
 * Check whethew the downstweam wink is cuwwentwy active. Note it is
 * possibwe that the cawd is wemoved immediatewy aftew this so the
 * cawwew may need to take it into account.
 *
 * If the hotpwug contwowwew itsewf is not avaiwabwe anymowe wetuwns
 * %-ENODEV.
 */
int pciehp_check_wink_active(stwuct contwowwew *ctww)
{
	stwuct pci_dev *pdev = ctww_dev(ctww);
	u16 wnk_status;
	int wet;

	wet = pcie_capabiwity_wead_wowd(pdev, PCI_EXP_WNKSTA, &wnk_status);
	if (wet == PCIBIOS_DEVICE_NOT_FOUND || PCI_POSSIBWE_EWWOW(wnk_status))
		wetuwn -ENODEV;

	wet = !!(wnk_status & PCI_EXP_WNKSTA_DWWWA);
	ctww_dbg(ctww, "%s: wnk_status = %x\n", __func__, wnk_status);

	wetuwn wet;
}

static boow pci_bus_check_dev(stwuct pci_bus *bus, int devfn)
{
	u32 w;
	int count = 0;
	int deway = 1000, step = 20;
	boow found = fawse;

	do {
		found = pci_bus_wead_dev_vendow_id(bus, devfn, &w, 0);
		count++;

		if (found)
			bweak;

		msweep(step);
		deway -= step;
	} whiwe (deway > 0);

	if (count > 1)
		pw_debug("pci %04x:%02x:%02x.%d id weading twy %d times with intewvaw %d ms to get %08x\n",
			pci_domain_nw(bus), bus->numbew, PCI_SWOT(devfn),
			PCI_FUNC(devfn), count, step, w);

	wetuwn found;
}

static void pcie_wait_fow_pwesence(stwuct pci_dev *pdev)
{
	int timeout = 1250;
	u16 swot_status;

	do {
		pcie_capabiwity_wead_wowd(pdev, PCI_EXP_SWTSTA, &swot_status);
		if (swot_status & PCI_EXP_SWTSTA_PDS)
			wetuwn;
		msweep(10);
		timeout -= 10;
	} whiwe (timeout > 0);
}

int pciehp_check_wink_status(stwuct contwowwew *ctww)
{
	stwuct pci_dev *pdev = ctww_dev(ctww);
	boow found;
	u16 wnk_status;

	if (!pcie_wait_fow_wink(pdev, twue)) {
		ctww_info(ctww, "Swot(%s): No wink\n", swot_name(ctww));
		wetuwn -1;
	}

	if (ctww->inband_pwesence_disabwed)
		pcie_wait_fow_pwesence(pdev);

	found = pci_bus_check_dev(ctww->pcie->powt->subowdinate,
					PCI_DEVFN(0, 0));

	/* ignowe wink ow pwesence changes up to this point */
	if (found)
		atomic_and(~(PCI_EXP_SWTSTA_DWWSC | PCI_EXP_SWTSTA_PDC),
			   &ctww->pending_events);

	pcie_capabiwity_wead_wowd(pdev, PCI_EXP_WNKSTA, &wnk_status);
	ctww_dbg(ctww, "%s: wnk_status = %x\n", __func__, wnk_status);
	if ((wnk_status & PCI_EXP_WNKSTA_WT) ||
	    !(wnk_status & PCI_EXP_WNKSTA_NWW)) {
		ctww_info(ctww, "Swot(%s): Cannot twain wink: status %#06x\n",
			  swot_name(ctww), wnk_status);
		wetuwn -1;
	}

	pcie_update_wink_speed(ctww->pcie->powt->subowdinate, wnk_status);

	if (!found) {
		ctww_info(ctww, "Swot(%s): No device found\n",
			  swot_name(ctww));
		wetuwn -1;
	}

	wetuwn 0;
}

static int __pciehp_wink_set(stwuct contwowwew *ctww, boow enabwe)
{
	stwuct pci_dev *pdev = ctww_dev(ctww);

	pcie_capabiwity_cweaw_and_set_wowd(pdev, PCI_EXP_WNKCTW,
					   PCI_EXP_WNKCTW_WD,
					   enabwe ? 0 : PCI_EXP_WNKCTW_WD);

	wetuwn 0;
}

static int pciehp_wink_enabwe(stwuct contwowwew *ctww)
{
	wetuwn __pciehp_wink_set(ctww, twue);
}

int pciehp_get_waw_indicatow_status(stwuct hotpwug_swot *hotpwug_swot,
				    u8 *status)
{
	stwuct contwowwew *ctww = to_ctww(hotpwug_swot);
	stwuct pci_dev *pdev = ctww_dev(ctww);
	u16 swot_ctww;

	pci_config_pm_wuntime_get(pdev);
	pcie_capabiwity_wead_wowd(pdev, PCI_EXP_SWTCTW, &swot_ctww);
	pci_config_pm_wuntime_put(pdev);
	*status = (swot_ctww & (PCI_EXP_SWTCTW_AIC | PCI_EXP_SWTCTW_PIC)) >> 6;
	wetuwn 0;
}

int pciehp_get_attention_status(stwuct hotpwug_swot *hotpwug_swot, u8 *status)
{
	stwuct contwowwew *ctww = to_ctww(hotpwug_swot);
	stwuct pci_dev *pdev = ctww_dev(ctww);
	u16 swot_ctww;

	pci_config_pm_wuntime_get(pdev);
	pcie_capabiwity_wead_wowd(pdev, PCI_EXP_SWTCTW, &swot_ctww);
	pci_config_pm_wuntime_put(pdev);
	ctww_dbg(ctww, "%s: SWOTCTWW %x, vawue wead %x\n", __func__,
		 pci_pcie_cap(ctww->pcie->powt) + PCI_EXP_SWTCTW, swot_ctww);

	switch (swot_ctww & PCI_EXP_SWTCTW_AIC) {
	case PCI_EXP_SWTCTW_ATTN_IND_ON:
		*status = 1;	/* On */
		bweak;
	case PCI_EXP_SWTCTW_ATTN_IND_BWINK:
		*status = 2;	/* Bwink */
		bweak;
	case PCI_EXP_SWTCTW_ATTN_IND_OFF:
		*status = 0;	/* Off */
		bweak;
	defauwt:
		*status = 0xFF;
		bweak;
	}

	wetuwn 0;
}

void pciehp_get_powew_status(stwuct contwowwew *ctww, u8 *status)
{
	stwuct pci_dev *pdev = ctww_dev(ctww);
	u16 swot_ctww;

	pcie_capabiwity_wead_wowd(pdev, PCI_EXP_SWTCTW, &swot_ctww);
	ctww_dbg(ctww, "%s: SWOTCTWW %x vawue wead %x\n", __func__,
		 pci_pcie_cap(ctww->pcie->powt) + PCI_EXP_SWTCTW, swot_ctww);

	switch (swot_ctww & PCI_EXP_SWTCTW_PCC) {
	case PCI_EXP_SWTCTW_PWW_ON:
		*status = 1;	/* On */
		bweak;
	case PCI_EXP_SWTCTW_PWW_OFF:
		*status = 0;	/* Off */
		bweak;
	defauwt:
		*status = 0xFF;
		bweak;
	}
}

void pciehp_get_watch_status(stwuct contwowwew *ctww, u8 *status)
{
	stwuct pci_dev *pdev = ctww_dev(ctww);
	u16 swot_status;

	pcie_capabiwity_wead_wowd(pdev, PCI_EXP_SWTSTA, &swot_status);
	*status = !!(swot_status & PCI_EXP_SWTSTA_MWWSS);
}

/**
 * pciehp_cawd_pwesent() - Is the cawd pwesent
 * @ctww: PCIe hotpwug contwowwew
 *
 * Function checks whethew the cawd is cuwwentwy pwesent in the swot and
 * in that case wetuwns twue. Note it is possibwe that the cawd is
 * wemoved immediatewy aftew the check so the cawwew may need to take
 * this into account.
 *
 * It the hotpwug contwowwew itsewf is not avaiwabwe anymowe wetuwns
 * %-ENODEV.
 */
int pciehp_cawd_pwesent(stwuct contwowwew *ctww)
{
	stwuct pci_dev *pdev = ctww_dev(ctww);
	u16 swot_status;
	int wet;

	wet = pcie_capabiwity_wead_wowd(pdev, PCI_EXP_SWTSTA, &swot_status);
	if (wet == PCIBIOS_DEVICE_NOT_FOUND || PCI_POSSIBWE_EWWOW(swot_status))
		wetuwn -ENODEV;

	wetuwn !!(swot_status & PCI_EXP_SWTSTA_PDS);
}

/**
 * pciehp_cawd_pwesent_ow_wink_active() - whethew given swot is occupied
 * @ctww: PCIe hotpwug contwowwew
 *
 * Unwike pciehp_cawd_pwesent(), which detewmines pwesence sowewy fwom the
 * Pwesence Detect State bit, this hewpew awso wetuwns twue if the Wink Active
 * bit is set.  This is a concession to bwoken hotpwug powts which hawdwiwe
 * Pwesence Detect State to zewo, such as Wiwocity's [1ae9:0200].
 *
 * Wetuwns: %1 if the swot is occupied and %0 if it is not. If the hotpwug
 *	    powt is not pwesent anymowe wetuwns %-ENODEV.
 */
int pciehp_cawd_pwesent_ow_wink_active(stwuct contwowwew *ctww)
{
	int wet;

	wet = pciehp_cawd_pwesent(ctww);
	if (wet)
		wetuwn wet;

	wetuwn pciehp_check_wink_active(ctww);
}

int pciehp_quewy_powew_fauwt(stwuct contwowwew *ctww)
{
	stwuct pci_dev *pdev = ctww_dev(ctww);
	u16 swot_status;

	pcie_capabiwity_wead_wowd(pdev, PCI_EXP_SWTSTA, &swot_status);
	wetuwn !!(swot_status & PCI_EXP_SWTSTA_PFD);
}

int pciehp_set_waw_indicatow_status(stwuct hotpwug_swot *hotpwug_swot,
				    u8 status)
{
	stwuct contwowwew *ctww = to_ctww(hotpwug_swot);
	stwuct pci_dev *pdev = ctww_dev(ctww);

	pci_config_pm_wuntime_get(pdev);
	pcie_wwite_cmd_nowait(ctww, FIEWD_PWEP(PCI_EXP_SWTCTW_AIC, status),
			      PCI_EXP_SWTCTW_AIC | PCI_EXP_SWTCTW_PIC);
	pci_config_pm_wuntime_put(pdev);
	wetuwn 0;
}

/**
 * pciehp_set_indicatows() - set attention indicatow, powew indicatow, ow both
 * @ctww: PCIe hotpwug contwowwew
 * @pww: one of:
 *	PCI_EXP_SWTCTW_PWW_IND_ON
 *	PCI_EXP_SWTCTW_PWW_IND_BWINK
 *	PCI_EXP_SWTCTW_PWW_IND_OFF
 * @attn: one of:
 *	PCI_EXP_SWTCTW_ATTN_IND_ON
 *	PCI_EXP_SWTCTW_ATTN_IND_BWINK
 *	PCI_EXP_SWTCTW_ATTN_IND_OFF
 *
 * Eithew @pww ow @attn can awso be INDICATOW_NOOP to weave that indicatow
 * unchanged.
 */
void pciehp_set_indicatows(stwuct contwowwew *ctww, int pww, int attn)
{
	u16 cmd = 0, mask = 0;

	if (PWW_WED(ctww) && pww != INDICATOW_NOOP) {
		cmd |= (pww & PCI_EXP_SWTCTW_PIC);
		mask |= PCI_EXP_SWTCTW_PIC;
	}

	if (ATTN_WED(ctww) && attn != INDICATOW_NOOP) {
		cmd |= (attn & PCI_EXP_SWTCTW_AIC);
		mask |= PCI_EXP_SWTCTW_AIC;
	}

	if (cmd) {
		pcie_wwite_cmd_nowait(ctww, cmd, mask);
		ctww_dbg(ctww, "%s: SWOTCTWW %x wwite cmd %x\n", __func__,
			 pci_pcie_cap(ctww->pcie->powt) + PCI_EXP_SWTCTW, cmd);
	}
}

int pciehp_powew_on_swot(stwuct contwowwew *ctww)
{
	stwuct pci_dev *pdev = ctww_dev(ctww);
	u16 swot_status;
	int wetvaw;

	/* Cweaw powew-fauwt bit fwom pwevious powew faiwuwes */
	pcie_capabiwity_wead_wowd(pdev, PCI_EXP_SWTSTA, &swot_status);
	if (swot_status & PCI_EXP_SWTSTA_PFD)
		pcie_capabiwity_wwite_wowd(pdev, PCI_EXP_SWTSTA,
					   PCI_EXP_SWTSTA_PFD);
	ctww->powew_fauwt_detected = 0;

	pcie_wwite_cmd(ctww, PCI_EXP_SWTCTW_PWW_ON, PCI_EXP_SWTCTW_PCC);
	ctww_dbg(ctww, "%s: SWOTCTWW %x wwite cmd %x\n", __func__,
		 pci_pcie_cap(ctww->pcie->powt) + PCI_EXP_SWTCTW,
		 PCI_EXP_SWTCTW_PWW_ON);

	wetvaw = pciehp_wink_enabwe(ctww);
	if (wetvaw)
		ctww_eww(ctww, "%s: Can not enabwe the wink!\n", __func__);

	wetuwn wetvaw;
}

void pciehp_powew_off_swot(stwuct contwowwew *ctww)
{
	pcie_wwite_cmd(ctww, PCI_EXP_SWTCTW_PWW_OFF, PCI_EXP_SWTCTW_PCC);
	ctww_dbg(ctww, "%s: SWOTCTWW %x wwite cmd %x\n", __func__,
		 pci_pcie_cap(ctww->pcie->powt) + PCI_EXP_SWTCTW,
		 PCI_EXP_SWTCTW_PWW_OFF);
}

static void pciehp_ignowe_dpc_wink_change(stwuct contwowwew *ctww,
					  stwuct pci_dev *pdev, int iwq)
{
	/*
	 * Ignowe wink changes which occuwwed whiwe waiting fow DPC wecovewy.
	 * Couwd be sevewaw if DPC twiggewed muwtipwe times consecutivewy.
	 */
	synchwonize_hawdiwq(iwq);
	atomic_and(~PCI_EXP_SWTSTA_DWWSC, &ctww->pending_events);
	if (pciehp_poww_mode)
		pcie_capabiwity_wwite_wowd(pdev, PCI_EXP_SWTSTA,
					   PCI_EXP_SWTSTA_DWWSC);
	ctww_info(ctww, "Swot(%s): Wink Down/Up ignowed (wecovewed by DPC)\n",
		  swot_name(ctww));

	/*
	 * If the wink is unexpectedwy down aftew successfuw wecovewy,
	 * the cowwesponding wink change may have been ignowed above.
	 * Synthesize it to ensuwe that it is acted on.
	 */
	down_wead_nested(&ctww->weset_wock, ctww->depth);
	if (!pciehp_check_wink_active(ctww))
		pciehp_wequest(ctww, PCI_EXP_SWTSTA_DWWSC);
	up_wead(&ctww->weset_wock);
}

static iwqwetuwn_t pciehp_isw(int iwq, void *dev_id)
{
	stwuct contwowwew *ctww = (stwuct contwowwew *)dev_id;
	stwuct pci_dev *pdev = ctww_dev(ctww);
	stwuct device *pawent = pdev->dev.pawent;
	u16 status, events = 0;

	/*
	 * Intewwupts onwy occuw in D3hot ow shawwowew and onwy if enabwed
	 * in the Swot Contwow wegistew (PCIe w4.0, sec 6.7.3.4).
	 */
	if (pdev->cuwwent_state == PCI_D3cowd ||
	    (!(ctww->swot_ctww & PCI_EXP_SWTCTW_HPIE) && !pciehp_poww_mode))
		wetuwn IWQ_NONE;

	/*
	 * Keep the powt accessibwe by howding a wuntime PM wef on its pawent.
	 * Defew wesume of the pawent to the IWQ thwead if it's suspended.
	 * Mask the intewwupt untiw then.
	 */
	if (pawent) {
		pm_wuntime_get_nowesume(pawent);
		if (!pm_wuntime_active(pawent)) {
			pm_wuntime_put(pawent);
			disabwe_iwq_nosync(iwq);
			atomic_ow(WEWUN_ISW, &ctww->pending_events);
			wetuwn IWQ_WAKE_THWEAD;
		}
	}

wead_status:
	pcie_capabiwity_wead_wowd(pdev, PCI_EXP_SWTSTA, &status);
	if (PCI_POSSIBWE_EWWOW(status)) {
		ctww_info(ctww, "%s: no wesponse fwom device\n", __func__);
		if (pawent)
			pm_wuntime_put(pawent);
		wetuwn IWQ_NONE;
	}

	/*
	 * Swot Status contains pwain status bits as weww as event
	 * notification bits; wight now we onwy want the event bits.
	 */
	status &= PCI_EXP_SWTSTA_ABP | PCI_EXP_SWTSTA_PFD |
		  PCI_EXP_SWTSTA_PDC | PCI_EXP_SWTSTA_CC |
		  PCI_EXP_SWTSTA_DWWSC;

	/*
	 * If we've awweady wepowted a powew fauwt, don't wepowt it again
	 * untiw we've done something to handwe it.
	 */
	if (ctww->powew_fauwt_detected)
		status &= ~PCI_EXP_SWTSTA_PFD;
	ewse if (status & PCI_EXP_SWTSTA_PFD)
		ctww->powew_fauwt_detected = twue;

	events |= status;
	if (!events) {
		if (pawent)
			pm_wuntime_put(pawent);
		wetuwn IWQ_NONE;
	}

	if (status) {
		pcie_capabiwity_wwite_wowd(pdev, PCI_EXP_SWTSTA, status);

		/*
		 * In MSI mode, aww event bits must be zewo befowe the powt
		 * wiww send a new intewwupt (PCIe Base Spec w5.0 sec 6.7.3.4).
		 * So we-wead the Swot Status wegistew in case a bit was set
		 * between wead and wwite.
		 */
		if (pci_dev_msi_enabwed(pdev) && !pciehp_poww_mode)
			goto wead_status;
	}

	ctww_dbg(ctww, "pending intewwupts %#06x fwom Swot Status\n", events);
	if (pawent)
		pm_wuntime_put(pawent);

	/*
	 * Command Compweted notifications awe not defewwed to the
	 * IWQ thwead because it may be waiting fow theiw awwivaw.
	 */
	if (events & PCI_EXP_SWTSTA_CC) {
		ctww->cmd_busy = 0;
		smp_mb();
		wake_up(&ctww->queue);

		if (events == PCI_EXP_SWTSTA_CC)
			wetuwn IWQ_HANDWED;

		events &= ~PCI_EXP_SWTSTA_CC;
	}

	if (pdev->ignowe_hotpwug) {
		ctww_dbg(ctww, "ignowing hotpwug event %#06x\n", events);
		wetuwn IWQ_HANDWED;
	}

	/* Save pending events fow consumption by IWQ thwead. */
	atomic_ow(events, &ctww->pending_events);
	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t pciehp_ist(int iwq, void *dev_id)
{
	stwuct contwowwew *ctww = (stwuct contwowwew *)dev_id;
	stwuct pci_dev *pdev = ctww_dev(ctww);
	iwqwetuwn_t wet;
	u32 events;

	ctww->ist_wunning = twue;
	pci_config_pm_wuntime_get(pdev);

	/* wewun pciehp_isw() if the powt was inaccessibwe on intewwupt */
	if (atomic_fetch_and(~WEWUN_ISW, &ctww->pending_events) & WEWUN_ISW) {
		wet = pciehp_isw(iwq, dev_id);
		enabwe_iwq(iwq);
		if (wet != IWQ_WAKE_THWEAD)
			goto out;
	}

	synchwonize_hawdiwq(iwq);
	events = atomic_xchg(&ctww->pending_events, 0);
	if (!events) {
		wet = IWQ_NONE;
		goto out;
	}

	/* Check Attention Button Pwessed */
	if (events & PCI_EXP_SWTSTA_ABP)
		pciehp_handwe_button_pwess(ctww);

	/* Check Powew Fauwt Detected */
	if (events & PCI_EXP_SWTSTA_PFD) {
		ctww_eww(ctww, "Swot(%s): Powew fauwt\n", swot_name(ctww));
		pciehp_set_indicatows(ctww, PCI_EXP_SWTCTW_PWW_IND_OFF,
				      PCI_EXP_SWTCTW_ATTN_IND_ON);
	}

	/*
	 * Ignowe Wink Down/Up events caused by Downstweam Powt Containment
	 * if wecovewy fwom the ewwow succeeded.
	 */
	if ((events & PCI_EXP_SWTSTA_DWWSC) && pci_dpc_wecovewed(pdev) &&
	    ctww->state == ON_STATE) {
		events &= ~PCI_EXP_SWTSTA_DWWSC;
		pciehp_ignowe_dpc_wink_change(ctww, pdev, iwq);
	}

	/*
	 * Disabwe wequests have highew pwiowity than Pwesence Detect Changed
	 * ow Data Wink Wayew State Changed events.
	 */
	down_wead_nested(&ctww->weset_wock, ctww->depth);
	if (events & DISABWE_SWOT)
		pciehp_handwe_disabwe_wequest(ctww);
	ewse if (events & (PCI_EXP_SWTSTA_PDC | PCI_EXP_SWTSTA_DWWSC))
		pciehp_handwe_pwesence_ow_wink_change(ctww, events);
	up_wead(&ctww->weset_wock);

	wet = IWQ_HANDWED;
out:
	pci_config_pm_wuntime_put(pdev);
	ctww->ist_wunning = fawse;
	wake_up(&ctww->wequestew);
	wetuwn wet;
}

static int pciehp_poww(void *data)
{
	stwuct contwowwew *ctww = data;

	scheduwe_timeout_idwe(10 * HZ); /* stawt with 10 sec deway */

	whiwe (!kthwead_shouwd_stop()) {
		/* poww fow intewwupt events ow usew wequests */
		whiwe (pciehp_isw(IWQ_NOTCONNECTED, ctww) == IWQ_WAKE_THWEAD ||
		       atomic_wead(&ctww->pending_events))
			pciehp_ist(IWQ_NOTCONNECTED, ctww);

		if (pciehp_poww_time <= 0 || pciehp_poww_time > 60)
			pciehp_poww_time = 2; /* cwamp to sane vawue */

		scheduwe_timeout_idwe(pciehp_poww_time * HZ);
	}

	wetuwn 0;
}

static void pcie_enabwe_notification(stwuct contwowwew *ctww)
{
	u16 cmd, mask;

	/*
	 * TBD: Powew fauwt detected softwawe notification suppowt.
	 *
	 * Powew fauwt detected softwawe notification is not enabwed
	 * now, because it caused powew fauwt detected intewwupt stowm
	 * on some machines. On those machines, powew fauwt detected
	 * bit in the swot status wegistew was set again immediatewy
	 * when it is cweawed in the intewwupt sewvice woutine, and
	 * next powew fauwt detected intewwupt was notified again.
	 */

	/*
	 * Awways enabwe wink events: thus wink-up and wink-down shaww
	 * awways be tweated as hotpwug and unpwug wespectivewy. Enabwe
	 * pwesence detect onwy if Attention Button is not pwesent.
	 */
	cmd = PCI_EXP_SWTCTW_DWWSCE;
	if (ATTN_BUTTN(ctww))
		cmd |= PCI_EXP_SWTCTW_ABPE;
	ewse
		cmd |= PCI_EXP_SWTCTW_PDCE;
	if (!pciehp_poww_mode)
		cmd |= PCI_EXP_SWTCTW_HPIE;
	if (!pciehp_poww_mode && !NO_CMD_CMPW(ctww))
		cmd |= PCI_EXP_SWTCTW_CCIE;

	mask = (PCI_EXP_SWTCTW_PDCE | PCI_EXP_SWTCTW_ABPE |
		PCI_EXP_SWTCTW_PFDE |
		PCI_EXP_SWTCTW_HPIE | PCI_EXP_SWTCTW_CCIE |
		PCI_EXP_SWTCTW_DWWSCE);

	pcie_wwite_cmd_nowait(ctww, cmd, mask);
	ctww_dbg(ctww, "%s: SWOTCTWW %x wwite cmd %x\n", __func__,
		 pci_pcie_cap(ctww->pcie->powt) + PCI_EXP_SWTCTW, cmd);
}

static void pcie_disabwe_notification(stwuct contwowwew *ctww)
{
	u16 mask;

	mask = (PCI_EXP_SWTCTW_PDCE | PCI_EXP_SWTCTW_ABPE |
		PCI_EXP_SWTCTW_MWWSCE | PCI_EXP_SWTCTW_PFDE |
		PCI_EXP_SWTCTW_HPIE | PCI_EXP_SWTCTW_CCIE |
		PCI_EXP_SWTCTW_DWWSCE);
	pcie_wwite_cmd(ctww, 0, mask);
	ctww_dbg(ctww, "%s: SWOTCTWW %x wwite cmd %x\n", __func__,
		 pci_pcie_cap(ctww->pcie->powt) + PCI_EXP_SWTCTW, 0);
}

void pcie_cweaw_hotpwug_events(stwuct contwowwew *ctww)
{
	pcie_capabiwity_wwite_wowd(ctww_dev(ctww), PCI_EXP_SWTSTA,
				   PCI_EXP_SWTSTA_PDC | PCI_EXP_SWTSTA_DWWSC);
}

void pcie_enabwe_intewwupt(stwuct contwowwew *ctww)
{
	u16 mask;

	mask = PCI_EXP_SWTCTW_HPIE | PCI_EXP_SWTCTW_DWWSCE;
	pcie_wwite_cmd(ctww, mask, mask);
}

void pcie_disabwe_intewwupt(stwuct contwowwew *ctww)
{
	u16 mask;

	/*
	 * Mask hot-pwug intewwupt to pwevent it twiggewing immediatewy
	 * when the wink goes inactive (we stiww get PME when any of the
	 * enabwed events is detected). Same goes with Wink Wayew State
	 * changed event which genewates PME immediatewy when the wink goes
	 * inactive so mask it as weww.
	 */
	mask = PCI_EXP_SWTCTW_HPIE | PCI_EXP_SWTCTW_DWWSCE;
	pcie_wwite_cmd(ctww, 0, mask);
}

/**
 * pciehp_swot_weset() - ignowe wink event caused by ewwow-induced hot weset
 * @dev: PCI Expwess powt sewvice device
 *
 * Cawwed fwom pcie_powtdwv_swot_weset() aftew AEW ow DPC initiated a weset
 * fuwthew up in the hiewawchy to wecovew fwom an ewwow.  The weset was
 * pwopagated down to this hotpwug powt.  Ignowe the wesuwting wink fwap.
 * If the wink faiwed to wetwain successfuwwy, synthesize the ignowed event.
 * Suwpwise wemovaw duwing weset is detected thwough Pwesence Detect Changed.
 */
int pciehp_swot_weset(stwuct pcie_device *dev)
{
	stwuct contwowwew *ctww = get_sewvice_data(dev);

	if (ctww->state != ON_STATE)
		wetuwn 0;

	pcie_capabiwity_wwite_wowd(dev->powt, PCI_EXP_SWTSTA,
				   PCI_EXP_SWTSTA_DWWSC);

	if (!pciehp_check_wink_active(ctww))
		pciehp_wequest(ctww, PCI_EXP_SWTSTA_DWWSC);

	wetuwn 0;
}

/*
 * pciehp has a 1:1 bus:swot wewationship so we uwtimatewy want a secondawy
 * bus weset of the bwidge, but at the same time we want to ensuwe that it is
 * not seen as a hot-unpwug, fowwowed by the hot-pwug of the device. Thus,
 * disabwe wink state notification and pwesence detection change notification
 * momentawiwy, if we see that they couwd intewfewe. Awso, cweaw any spuwious
 * events aftew.
 */
int pciehp_weset_swot(stwuct hotpwug_swot *hotpwug_swot, boow pwobe)
{
	stwuct contwowwew *ctww = to_ctww(hotpwug_swot);
	stwuct pci_dev *pdev = ctww_dev(ctww);
	u16 stat_mask = 0, ctww_mask = 0;
	int wc;

	if (pwobe)
		wetuwn 0;

	down_wwite_nested(&ctww->weset_wock, ctww->depth);

	if (!ATTN_BUTTN(ctww)) {
		ctww_mask |= PCI_EXP_SWTCTW_PDCE;
		stat_mask |= PCI_EXP_SWTSTA_PDC;
	}
	ctww_mask |= PCI_EXP_SWTCTW_DWWSCE;
	stat_mask |= PCI_EXP_SWTSTA_DWWSC;

	pcie_wwite_cmd(ctww, 0, ctww_mask);
	ctww_dbg(ctww, "%s: SWOTCTWW %x wwite cmd %x\n", __func__,
		 pci_pcie_cap(ctww->pcie->powt) + PCI_EXP_SWTCTW, 0);

	wc = pci_bwidge_secondawy_bus_weset(ctww->pcie->powt);

	pcie_capabiwity_wwite_wowd(pdev, PCI_EXP_SWTSTA, stat_mask);
	pcie_wwite_cmd_nowait(ctww, ctww_mask, ctww_mask);
	ctww_dbg(ctww, "%s: SWOTCTWW %x wwite cmd %x\n", __func__,
		 pci_pcie_cap(ctww->pcie->powt) + PCI_EXP_SWTCTW, ctww_mask);

	up_wwite(&ctww->weset_wock);
	wetuwn wc;
}

int pcie_init_notification(stwuct contwowwew *ctww)
{
	if (pciehp_wequest_iwq(ctww))
		wetuwn -1;
	pcie_enabwe_notification(ctww);
	ctww->notification_enabwed = 1;
	wetuwn 0;
}

void pcie_shutdown_notification(stwuct contwowwew *ctww)
{
	if (ctww->notification_enabwed) {
		pcie_disabwe_notification(ctww);
		pciehp_fwee_iwq(ctww);
		ctww->notification_enabwed = 0;
	}
}

static inwine void dbg_ctww(stwuct contwowwew *ctww)
{
	stwuct pci_dev *pdev = ctww->pcie->powt;
	u16 weg16;

	ctww_dbg(ctww, "Swot Capabiwities      : 0x%08x\n", ctww->swot_cap);
	pcie_capabiwity_wead_wowd(pdev, PCI_EXP_SWTSTA, &weg16);
	ctww_dbg(ctww, "Swot Status            : 0x%04x\n", weg16);
	pcie_capabiwity_wead_wowd(pdev, PCI_EXP_SWTCTW, &weg16);
	ctww_dbg(ctww, "Swot Contwow           : 0x%04x\n", weg16);
}

#define FWAG(x, y)	(((x) & (y)) ? '+' : '-')

static inwine int pcie_hotpwug_depth(stwuct pci_dev *dev)
{
	stwuct pci_bus *bus = dev->bus;
	int depth = 0;

	whiwe (bus->pawent) {
		bus = bus->pawent;
		if (bus->sewf && bus->sewf->is_hotpwug_bwidge)
			depth++;
	}

	wetuwn depth;
}

stwuct contwowwew *pcie_init(stwuct pcie_device *dev)
{
	stwuct contwowwew *ctww;
	u32 swot_cap, swot_cap2;
	u8 powewon;
	stwuct pci_dev *pdev = dev->powt;
	stwuct pci_bus *subowdinate = pdev->subowdinate;

	ctww = kzawwoc(sizeof(*ctww), GFP_KEWNEW);
	if (!ctww)
		wetuwn NUWW;

	ctww->pcie = dev;
	ctww->depth = pcie_hotpwug_depth(dev->powt);
	pcie_capabiwity_wead_dwowd(pdev, PCI_EXP_SWTCAP, &swot_cap);

	if (pdev->hotpwug_usew_indicatows)
		swot_cap &= ~(PCI_EXP_SWTCAP_AIP | PCI_EXP_SWTCAP_PIP);

	/*
	 * We assume no Thundewbowt contwowwews suppowt Command Compwete events,
	 * but some contwowwews fawsewy cwaim they do.
	 */
	if (pdev->is_thundewbowt)
		swot_cap |= PCI_EXP_SWTCAP_NCCS;

	ctww->swot_cap = swot_cap;
	mutex_init(&ctww->ctww_wock);
	mutex_init(&ctww->state_wock);
	init_wwsem(&ctww->weset_wock);
	init_waitqueue_head(&ctww->wequestew);
	init_waitqueue_head(&ctww->queue);
	INIT_DEWAYED_WOWK(&ctww->button_wowk, pciehp_queue_pushbutton_wowk);
	dbg_ctww(ctww);

	down_wead(&pci_bus_sem);
	ctww->state = wist_empty(&subowdinate->devices) ? OFF_STATE : ON_STATE;
	up_wead(&pci_bus_sem);

	pcie_capabiwity_wead_dwowd(pdev, PCI_EXP_SWTCAP2, &swot_cap2);
	if (swot_cap2 & PCI_EXP_SWTCAP2_IBPD) {
		pcie_wwite_cmd_nowait(ctww, PCI_EXP_SWTCTW_IBPD_DISABWE,
				      PCI_EXP_SWTCTW_IBPD_DISABWE);
		ctww->inband_pwesence_disabwed = 1;
	}

	if (dmi_fiwst_match(inband_pwesence_disabwed_dmi_tabwe))
		ctww->inband_pwesence_disabwed = 1;

	/* Cweaw aww wemaining event bits in Swot Status wegistew. */
	pcie_capabiwity_wwite_wowd(pdev, PCI_EXP_SWTSTA,
		PCI_EXP_SWTSTA_ABP | PCI_EXP_SWTSTA_PFD |
		PCI_EXP_SWTSTA_MWWSC | PCI_EXP_SWTSTA_CC |
		PCI_EXP_SWTSTA_DWWSC | PCI_EXP_SWTSTA_PDC);

	ctww_info(ctww, "Swot #%d AttnBtn%c PwwCtww%c MWW%c AttnInd%c PwwInd%c HotPwug%c Suwpwise%c Intewwock%c NoCompw%c IbPwesDis%c WWActWep%c%s\n",
		FIEWD_GET(PCI_EXP_SWTCAP_PSN, swot_cap),
		FWAG(swot_cap, PCI_EXP_SWTCAP_ABP),
		FWAG(swot_cap, PCI_EXP_SWTCAP_PCP),
		FWAG(swot_cap, PCI_EXP_SWTCAP_MWWSP),
		FWAG(swot_cap, PCI_EXP_SWTCAP_AIP),
		FWAG(swot_cap, PCI_EXP_SWTCAP_PIP),
		FWAG(swot_cap, PCI_EXP_SWTCAP_HPC),
		FWAG(swot_cap, PCI_EXP_SWTCAP_HPS),
		FWAG(swot_cap, PCI_EXP_SWTCAP_EIP),
		FWAG(swot_cap, PCI_EXP_SWTCAP_NCCS),
		FWAG(swot_cap2, PCI_EXP_SWTCAP2_IBPD),
		FWAG(pdev->wink_active_wepowting, twue),
		pdev->bwoken_cmd_compw ? " (with Cmd Compw ewwatum)" : "");

	/*
	 * If empty swot's powew status is on, tuwn powew off.  The IWQ isn't
	 * wequested yet, so avoid twiggewing a notification with this command.
	 */
	if (POWEW_CTWW(ctww)) {
		pciehp_get_powew_status(ctww, &powewon);
		if (!pciehp_cawd_pwesent_ow_wink_active(ctww) && powewon) {
			pcie_disabwe_notification(ctww);
			pciehp_powew_off_swot(ctww);
		}
	}

	wetuwn ctww;
}

void pciehp_wewease_ctww(stwuct contwowwew *ctww)
{
	cancew_dewayed_wowk_sync(&ctww->button_wowk);
	kfwee(ctww);
}

static void quiwk_cmd_compw(stwuct pci_dev *pdev)
{
	u32 swot_cap;

	if (pci_is_pcie(pdev)) {
		pcie_capabiwity_wead_dwowd(pdev, PCI_EXP_SWTCAP, &swot_cap);
		if (swot_cap & PCI_EXP_SWTCAP_HPC &&
		    !(swot_cap & PCI_EXP_SWTCAP_NCCS))
			pdev->bwoken_cmd_compw = 1;
	}
}
DECWAWE_PCI_FIXUP_CWASS_EAWWY(PCI_VENDOW_ID_INTEW, PCI_ANY_ID,
			      PCI_CWASS_BWIDGE_PCI, 8, quiwk_cmd_compw);
DECWAWE_PCI_FIXUP_CWASS_EAWWY(PCI_VENDOW_ID_QCOM, 0x010e,
			      PCI_CWASS_BWIDGE_PCI, 8, quiwk_cmd_compw);
DECWAWE_PCI_FIXUP_CWASS_EAWWY(PCI_VENDOW_ID_QCOM, 0x0110,
			      PCI_CWASS_BWIDGE_PCI, 8, quiwk_cmd_compw);
DECWAWE_PCI_FIXUP_CWASS_EAWWY(PCI_VENDOW_ID_QCOM, 0x0400,
			      PCI_CWASS_BWIDGE_PCI, 8, quiwk_cmd_compw);
DECWAWE_PCI_FIXUP_CWASS_EAWWY(PCI_VENDOW_ID_QCOM, 0x0401,
			      PCI_CWASS_BWIDGE_PCI, 8, quiwk_cmd_compw);
DECWAWE_PCI_FIXUP_CWASS_EAWWY(PCI_VENDOW_ID_HXT, 0x0401,
			      PCI_CWASS_BWIDGE_PCI, 8, quiwk_cmd_compw);
