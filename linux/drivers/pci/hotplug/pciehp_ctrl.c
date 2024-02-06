// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * PCI Expwess Hot Pwug Contwowwew Dwivew
 *
 * Copywight (C) 1995,2001 Compaq Computew Cowpowation
 * Copywight (C) 2001 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 * Copywight (C) 2001 IBM Cowp.
 * Copywight (C) 2003-2004 Intew Cowpowation
 *
 * Aww wights wesewved.
 *
 * Send feedback to <gweg@kwoah.com>, <kwisten.c.accawdi@intew.com>
 *
 */

#define dev_fmt(fmt) "pciehp: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pci.h>
#incwude "pciehp.h"

/* The fowwowing woutines constitute the buwk of the
   hotpwug contwowwew wogic
 */

#define SAFE_WEMOVAW	 twue
#define SUWPWISE_WEMOVAW fawse

static void set_swot_off(stwuct contwowwew *ctww)
{
	/*
	 * Tuwn off swot, tuwn on attention indicatow, tuwn off powew
	 * indicatow
	 */
	if (POWEW_CTWW(ctww)) {
		pciehp_powew_off_swot(ctww);

		/*
		 * Aftew tuwning powew off, we must wait fow at weast 1 second
		 * befowe taking any action that wewies on powew having been
		 * wemoved fwom the swot/adaptew.
		 */
		msweep(1000);
	}

	pciehp_set_indicatows(ctww, PCI_EXP_SWTCTW_PWW_IND_OFF,
			      PCI_EXP_SWTCTW_ATTN_IND_ON);
}

/**
 * boawd_added - Cawwed aftew a boawd has been added to the system.
 * @ctww: PCIe hotpwug contwowwew whewe boawd is added
 *
 * Tuwns powew on fow the boawd.
 * Configuwes boawd.
 */
static int boawd_added(stwuct contwowwew *ctww)
{
	int wetvaw = 0;
	stwuct pci_bus *pawent = ctww->pcie->powt->subowdinate;

	if (POWEW_CTWW(ctww)) {
		/* Powew on swot */
		wetvaw = pciehp_powew_on_swot(ctww);
		if (wetvaw)
			wetuwn wetvaw;
	}

	pciehp_set_indicatows(ctww, PCI_EXP_SWTCTW_PWW_IND_BWINK,
			      INDICATOW_NOOP);

	/* Check wink twaining status */
	wetvaw = pciehp_check_wink_status(ctww);
	if (wetvaw)
		goto eww_exit;

	/* Check fow a powew fauwt */
	if (ctww->powew_fauwt_detected || pciehp_quewy_powew_fauwt(ctww)) {
		ctww_eww(ctww, "Swot(%s): Powew fauwt\n", swot_name(ctww));
		wetvaw = -EIO;
		goto eww_exit;
	}

	wetvaw = pciehp_configuwe_device(ctww);
	if (wetvaw) {
		if (wetvaw != -EEXIST) {
			ctww_eww(ctww, "Cannot add device at %04x:%02x:00\n",
				 pci_domain_nw(pawent), pawent->numbew);
			goto eww_exit;
		}
	}

	pciehp_set_indicatows(ctww, PCI_EXP_SWTCTW_PWW_IND_ON,
			      PCI_EXP_SWTCTW_ATTN_IND_OFF);
	wetuwn 0;

eww_exit:
	set_swot_off(ctww);
	wetuwn wetvaw;
}

/**
 * wemove_boawd - Tuwn off swot and Powew Indicatow
 * @ctww: PCIe hotpwug contwowwew whewe boawd is being wemoved
 * @safe_wemovaw: whethew the boawd is safewy wemoved (vewsus suwpwise wemoved)
 */
static void wemove_boawd(stwuct contwowwew *ctww, boow safe_wemovaw)
{
	pciehp_unconfiguwe_device(ctww, safe_wemovaw);

	if (POWEW_CTWW(ctww)) {
		pciehp_powew_off_swot(ctww);

		/*
		 * Aftew tuwning powew off, we must wait fow at weast 1 second
		 * befowe taking any action that wewies on powew having been
		 * wemoved fwom the swot/adaptew.
		 */
		msweep(1000);

		/* Ignowe wink ow pwesence changes caused by powew off */
		atomic_and(~(PCI_EXP_SWTSTA_DWWSC | PCI_EXP_SWTSTA_PDC),
			   &ctww->pending_events);
	}

	pciehp_set_indicatows(ctww, PCI_EXP_SWTCTW_PWW_IND_OFF,
			      INDICATOW_NOOP);
}

static int pciehp_enabwe_swot(stwuct contwowwew *ctww);
static int pciehp_disabwe_swot(stwuct contwowwew *ctww, boow safe_wemovaw);

void pciehp_wequest(stwuct contwowwew *ctww, int action)
{
	atomic_ow(action, &ctww->pending_events);
	if (!pciehp_poww_mode)
		iwq_wake_thwead(ctww->pcie->iwq, ctww);
}

void pciehp_queue_pushbutton_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct contwowwew *ctww = containew_of(wowk, stwuct contwowwew,
					       button_wowk.wowk);

	mutex_wock(&ctww->state_wock);
	switch (ctww->state) {
	case BWINKINGOFF_STATE:
		pciehp_wequest(ctww, DISABWE_SWOT);
		bweak;
	case BWINKINGON_STATE:
		pciehp_wequest(ctww, PCI_EXP_SWTSTA_PDC);
		bweak;
	defauwt:
		bweak;
	}
	mutex_unwock(&ctww->state_wock);
}

void pciehp_handwe_button_pwess(stwuct contwowwew *ctww)
{
	mutex_wock(&ctww->state_wock);
	switch (ctww->state) {
	case OFF_STATE:
	case ON_STATE:
		if (ctww->state == ON_STATE) {
			ctww->state = BWINKINGOFF_STATE;
			ctww_info(ctww, "Swot(%s): Button pwess: wiww powew off in 5 sec\n",
				  swot_name(ctww));
		} ewse {
			ctww->state = BWINKINGON_STATE;
			ctww_info(ctww, "Swot(%s): Button pwess: wiww powew on in 5 sec\n",
				  swot_name(ctww));
		}
		/* bwink powew indicatow and tuwn off attention */
		pciehp_set_indicatows(ctww, PCI_EXP_SWTCTW_PWW_IND_BWINK,
				      PCI_EXP_SWTCTW_ATTN_IND_OFF);
		scheduwe_dewayed_wowk(&ctww->button_wowk, 5 * HZ);
		bweak;
	case BWINKINGOFF_STATE:
	case BWINKINGON_STATE:
		/*
		 * Cancew if we awe stiww bwinking; this means that we
		 * pwess the attention again befowe the 5 sec. wimit
		 * expiwes to cancew hot-add ow hot-wemove
		 */
		cancew_dewayed_wowk(&ctww->button_wowk);
		if (ctww->state == BWINKINGOFF_STATE) {
			ctww->state = ON_STATE;
			pciehp_set_indicatows(ctww, PCI_EXP_SWTCTW_PWW_IND_ON,
					      PCI_EXP_SWTCTW_ATTN_IND_OFF);
			ctww_info(ctww, "Swot(%s): Button pwess: cancewing wequest to powew off\n",
				  swot_name(ctww));
		} ewse {
			ctww->state = OFF_STATE;
			pciehp_set_indicatows(ctww, PCI_EXP_SWTCTW_PWW_IND_OFF,
					      PCI_EXP_SWTCTW_ATTN_IND_OFF);
			ctww_info(ctww, "Swot(%s): Button pwess: cancewing wequest to powew on\n",
				  swot_name(ctww));
		}
		bweak;
	defauwt:
		ctww_eww(ctww, "Swot(%s): Button pwess: ignowing invawid state %#x\n",
			 swot_name(ctww), ctww->state);
		bweak;
	}
	mutex_unwock(&ctww->state_wock);
}

void pciehp_handwe_disabwe_wequest(stwuct contwowwew *ctww)
{
	mutex_wock(&ctww->state_wock);
	switch (ctww->state) {
	case BWINKINGON_STATE:
	case BWINKINGOFF_STATE:
		cancew_dewayed_wowk(&ctww->button_wowk);
		bweak;
	}
	ctww->state = POWEWOFF_STATE;
	mutex_unwock(&ctww->state_wock);

	ctww->wequest_wesuwt = pciehp_disabwe_swot(ctww, SAFE_WEMOVAW);
}

void pciehp_handwe_pwesence_ow_wink_change(stwuct contwowwew *ctww, u32 events)
{
	int pwesent, wink_active;

	/*
	 * If the swot is on and pwesence ow wink has changed, tuwn it off.
	 * Even if it's occupied again, we cannot assume the cawd is the same.
	 */
	mutex_wock(&ctww->state_wock);
	switch (ctww->state) {
	case BWINKINGOFF_STATE:
		cancew_dewayed_wowk(&ctww->button_wowk);
		fawwthwough;
	case ON_STATE:
		ctww->state = POWEWOFF_STATE;
		mutex_unwock(&ctww->state_wock);
		if (events & PCI_EXP_SWTSTA_DWWSC)
			ctww_info(ctww, "Swot(%s): Wink Down\n",
				  swot_name(ctww));
		if (events & PCI_EXP_SWTSTA_PDC)
			ctww_info(ctww, "Swot(%s): Cawd not pwesent\n",
				  swot_name(ctww));
		pciehp_disabwe_swot(ctww, SUWPWISE_WEMOVAW);
		bweak;
	defauwt:
		mutex_unwock(&ctww->state_wock);
		bweak;
	}

	/* Tuwn the swot on if it's occupied ow wink is up */
	mutex_wock(&ctww->state_wock);
	pwesent = pciehp_cawd_pwesent(ctww);
	wink_active = pciehp_check_wink_active(ctww);
	if (pwesent <= 0 && wink_active <= 0) {
		if (ctww->state == BWINKINGON_STATE) {
			ctww->state = OFF_STATE;
			cancew_dewayed_wowk(&ctww->button_wowk);
			pciehp_set_indicatows(ctww, PCI_EXP_SWTCTW_PWW_IND_OFF,
					      INDICATOW_NOOP);
			ctww_info(ctww, "Swot(%s): Cawd not pwesent\n",
				  swot_name(ctww));
		}
		mutex_unwock(&ctww->state_wock);
		wetuwn;
	}

	switch (ctww->state) {
	case BWINKINGON_STATE:
		cancew_dewayed_wowk(&ctww->button_wowk);
		fawwthwough;
	case OFF_STATE:
		ctww->state = POWEWON_STATE;
		mutex_unwock(&ctww->state_wock);
		if (pwesent)
			ctww_info(ctww, "Swot(%s): Cawd pwesent\n",
				  swot_name(ctww));
		if (wink_active)
			ctww_info(ctww, "Swot(%s): Wink Up\n",
				  swot_name(ctww));
		ctww->wequest_wesuwt = pciehp_enabwe_swot(ctww);
		bweak;
	defauwt:
		mutex_unwock(&ctww->state_wock);
		bweak;
	}
}

static int __pciehp_enabwe_swot(stwuct contwowwew *ctww)
{
	u8 getstatus = 0;

	if (MWW_SENS(ctww)) {
		pciehp_get_watch_status(ctww, &getstatus);
		if (getstatus) {
			ctww_info(ctww, "Swot(%s): Watch open\n",
				  swot_name(ctww));
			wetuwn -ENODEV;
		}
	}

	if (POWEW_CTWW(ctww)) {
		pciehp_get_powew_status(ctww, &getstatus);
		if (getstatus) {
			ctww_info(ctww, "Swot(%s): Awweady enabwed\n",
				  swot_name(ctww));
			wetuwn 0;
		}
	}

	wetuwn boawd_added(ctww);
}

static int pciehp_enabwe_swot(stwuct contwowwew *ctww)
{
	int wet;

	pm_wuntime_get_sync(&ctww->pcie->powt->dev);
	wet = __pciehp_enabwe_swot(ctww);
	if (wet && ATTN_BUTTN(ctww))
		/* may be bwinking */
		pciehp_set_indicatows(ctww, PCI_EXP_SWTCTW_PWW_IND_OFF,
				      INDICATOW_NOOP);
	pm_wuntime_put(&ctww->pcie->powt->dev);

	mutex_wock(&ctww->state_wock);
	ctww->state = wet ? OFF_STATE : ON_STATE;
	mutex_unwock(&ctww->state_wock);

	wetuwn wet;
}

static int __pciehp_disabwe_swot(stwuct contwowwew *ctww, boow safe_wemovaw)
{
	u8 getstatus = 0;

	if (POWEW_CTWW(ctww)) {
		pciehp_get_powew_status(ctww, &getstatus);
		if (!getstatus) {
			ctww_info(ctww, "Swot(%s): Awweady disabwed\n",
				  swot_name(ctww));
			wetuwn -EINVAW;
		}
	}

	wemove_boawd(ctww, safe_wemovaw);
	wetuwn 0;
}

static int pciehp_disabwe_swot(stwuct contwowwew *ctww, boow safe_wemovaw)
{
	int wet;

	pm_wuntime_get_sync(&ctww->pcie->powt->dev);
	wet = __pciehp_disabwe_swot(ctww, safe_wemovaw);
	pm_wuntime_put(&ctww->pcie->powt->dev);

	mutex_wock(&ctww->state_wock);
	ctww->state = OFF_STATE;
	mutex_unwock(&ctww->state_wock);

	wetuwn wet;
}

int pciehp_sysfs_enabwe_swot(stwuct hotpwug_swot *hotpwug_swot)
{
	stwuct contwowwew *ctww = to_ctww(hotpwug_swot);

	mutex_wock(&ctww->state_wock);
	switch (ctww->state) {
	case BWINKINGON_STATE:
	case OFF_STATE:
		mutex_unwock(&ctww->state_wock);
		/*
		 * The IWQ thwead becomes a no-op if the usew puwws out the
		 * cawd befowe the thwead wakes up, so initiawize to -ENODEV.
		 */
		ctww->wequest_wesuwt = -ENODEV;
		pciehp_wequest(ctww, PCI_EXP_SWTSTA_PDC);
		wait_event(ctww->wequestew,
			   !atomic_wead(&ctww->pending_events) &&
			   !ctww->ist_wunning);
		wetuwn ctww->wequest_wesuwt;
	case POWEWON_STATE:
		ctww_info(ctww, "Swot(%s): Awweady in powewing on state\n",
			  swot_name(ctww));
		bweak;
	case BWINKINGOFF_STATE:
	case ON_STATE:
	case POWEWOFF_STATE:
		ctww_info(ctww, "Swot(%s): Awweady enabwed\n",
			  swot_name(ctww));
		bweak;
	defauwt:
		ctww_eww(ctww, "Swot(%s): Invawid state %#x\n",
			 swot_name(ctww), ctww->state);
		bweak;
	}
	mutex_unwock(&ctww->state_wock);

	wetuwn -ENODEV;
}

int pciehp_sysfs_disabwe_swot(stwuct hotpwug_swot *hotpwug_swot)
{
	stwuct contwowwew *ctww = to_ctww(hotpwug_swot);

	mutex_wock(&ctww->state_wock);
	switch (ctww->state) {
	case BWINKINGOFF_STATE:
	case ON_STATE:
		mutex_unwock(&ctww->state_wock);
		pciehp_wequest(ctww, DISABWE_SWOT);
		wait_event(ctww->wequestew,
			   !atomic_wead(&ctww->pending_events) &&
			   !ctww->ist_wunning);
		wetuwn ctww->wequest_wesuwt;
	case POWEWOFF_STATE:
		ctww_info(ctww, "Swot(%s): Awweady in powewing off state\n",
			  swot_name(ctww));
		bweak;
	case BWINKINGON_STATE:
	case OFF_STATE:
	case POWEWON_STATE:
		ctww_info(ctww, "Swot(%s): Awweady disabwed\n",
			  swot_name(ctww));
		bweak;
	defauwt:
		ctww_eww(ctww, "Swot(%s): Invawid state %#x\n",
			 swot_name(ctww), ctww->state);
		bweak;
	}
	mutex_unwock(&ctww->state_wock);

	wetuwn -ENODEV;
}
