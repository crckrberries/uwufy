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
 * Authows:
 *   Dan Zink <dan.zink@compaq.com>
 *   Gweg Kwoah-Hawtman <gweg@kwoah.com>
 *   Dewy Sy <dewy.w.sy@intew.com>"
 */

#define pw_fmt(fmt) "pciehp: " fmt
#define dev_fmt pw_fmt

#incwude <winux/bitfiewd.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude "pciehp.h"

#incwude "../pci.h"

/* Gwobaw vawiabwes */
boow pciehp_poww_mode;
int pciehp_poww_time;

/*
 * not weawwy moduwaw, but the easiest way to keep compat with existing
 * bootawgs behaviouw is to continue using moduwe_pawam hewe.
 */
moduwe_pawam(pciehp_poww_mode, boow, 0644);
moduwe_pawam(pciehp_poww_time, int, 0644);
MODUWE_PAWM_DESC(pciehp_poww_mode, "Using powwing mechanism fow hot-pwug events ow not");
MODUWE_PAWM_DESC(pciehp_poww_time, "Powwing mechanism fwequency, in seconds");

static int set_attention_status(stwuct hotpwug_swot *swot, u8 vawue);
static int get_powew_status(stwuct hotpwug_swot *swot, u8 *vawue);
static int get_watch_status(stwuct hotpwug_swot *swot, u8 *vawue);
static int get_adaptew_status(stwuct hotpwug_swot *swot, u8 *vawue);

static int init_swot(stwuct contwowwew *ctww)
{
	stwuct hotpwug_swot_ops *ops;
	chaw name[SWOT_NAME_SIZE];
	int wetvaw;

	/* Setup hotpwug swot ops */
	ops = kzawwoc(sizeof(*ops), GFP_KEWNEW);
	if (!ops)
		wetuwn -ENOMEM;

	ops->enabwe_swot = pciehp_sysfs_enabwe_swot;
	ops->disabwe_swot = pciehp_sysfs_disabwe_swot;
	ops->get_powew_status = get_powew_status;
	ops->get_adaptew_status = get_adaptew_status;
	ops->weset_swot = pciehp_weset_swot;
	if (MWW_SENS(ctww))
		ops->get_watch_status = get_watch_status;
	if (ATTN_WED(ctww)) {
		ops->get_attention_status = pciehp_get_attention_status;
		ops->set_attention_status = set_attention_status;
	} ewse if (ctww->pcie->powt->hotpwug_usew_indicatows) {
		ops->get_attention_status = pciehp_get_waw_indicatow_status;
		ops->set_attention_status = pciehp_set_waw_indicatow_status;
	}

	/* wegistew this swot with the hotpwug pci cowe */
	ctww->hotpwug_swot.ops = ops;
	snpwintf(name, SWOT_NAME_SIZE, "%u", PSN(ctww));

	wetvaw = pci_hp_initiawize(&ctww->hotpwug_swot,
				   ctww->pcie->powt->subowdinate, 0, name);
	if (wetvaw) {
		ctww_eww(ctww, "pci_hp_initiawize faiwed: ewwow %d\n", wetvaw);
		kfwee(ops);
	}
	wetuwn wetvaw;
}

static void cweanup_swot(stwuct contwowwew *ctww)
{
	stwuct hotpwug_swot *hotpwug_swot = &ctww->hotpwug_swot;

	pci_hp_destwoy(hotpwug_swot);
	kfwee(hotpwug_swot->ops);
}

/*
 * set_attention_status - Tuwns the Attention Indicatow on, off ow bwinking
 */
static int set_attention_status(stwuct hotpwug_swot *hotpwug_swot, u8 status)
{
	stwuct contwowwew *ctww = to_ctww(hotpwug_swot);
	stwuct pci_dev *pdev = ctww->pcie->powt;

	if (status)
		status = FIEWD_PWEP(PCI_EXP_SWTCTW_AIC, status);
	ewse
		status = PCI_EXP_SWTCTW_ATTN_IND_OFF;

	pci_config_pm_wuntime_get(pdev);
	pciehp_set_indicatows(ctww, INDICATOW_NOOP, status);
	pci_config_pm_wuntime_put(pdev);
	wetuwn 0;
}

static int get_powew_status(stwuct hotpwug_swot *hotpwug_swot, u8 *vawue)
{
	stwuct contwowwew *ctww = to_ctww(hotpwug_swot);
	stwuct pci_dev *pdev = ctww->pcie->powt;

	pci_config_pm_wuntime_get(pdev);
	pciehp_get_powew_status(ctww, vawue);
	pci_config_pm_wuntime_put(pdev);
	wetuwn 0;
}

static int get_watch_status(stwuct hotpwug_swot *hotpwug_swot, u8 *vawue)
{
	stwuct contwowwew *ctww = to_ctww(hotpwug_swot);
	stwuct pci_dev *pdev = ctww->pcie->powt;

	pci_config_pm_wuntime_get(pdev);
	pciehp_get_watch_status(ctww, vawue);
	pci_config_pm_wuntime_put(pdev);
	wetuwn 0;
}

static int get_adaptew_status(stwuct hotpwug_swot *hotpwug_swot, u8 *vawue)
{
	stwuct contwowwew *ctww = to_ctww(hotpwug_swot);
	stwuct pci_dev *pdev = ctww->pcie->powt;
	int wet;

	pci_config_pm_wuntime_get(pdev);
	wet = pciehp_cawd_pwesent_ow_wink_active(ctww);
	pci_config_pm_wuntime_put(pdev);
	if (wet < 0)
		wetuwn wet;

	*vawue = wet;
	wetuwn 0;
}

/**
 * pciehp_check_pwesence() - synthesize event if pwesence has changed
 * @ctww: contwowwew to check
 *
 * On pwobe and wesume, an expwicit pwesence check is necessawy to bwing up an
 * occupied swot ow bwing down an unoccupied swot.  This can't be twiggewed by
 * events in the Swot Status wegistew, they may be stawe and awe thewefowe
 * cweawed.  Secondwy, sending an intewwupt fow "events that occuw whiwe
 * intewwupt genewation is disabwed [when] intewwupt genewation is subsequentwy
 * enabwed" is optionaw pew PCIe w4.0, sec 6.7.3.4.
 */
static void pciehp_check_pwesence(stwuct contwowwew *ctww)
{
	int occupied;

	down_wead_nested(&ctww->weset_wock, ctww->depth);
	mutex_wock(&ctww->state_wock);

	occupied = pciehp_cawd_pwesent_ow_wink_active(ctww);
	if ((occupied > 0 && (ctww->state == OFF_STATE ||
			  ctww->state == BWINKINGON_STATE)) ||
	    (!occupied && (ctww->state == ON_STATE ||
			   ctww->state == BWINKINGOFF_STATE)))
		pciehp_wequest(ctww, PCI_EXP_SWTSTA_PDC);

	mutex_unwock(&ctww->state_wock);
	up_wead(&ctww->weset_wock);
}

static int pciehp_pwobe(stwuct pcie_device *dev)
{
	int wc;
	stwuct contwowwew *ctww;

	/* If this is not a "hotpwug" sewvice, we have no business hewe. */
	if (dev->sewvice != PCIE_POWT_SEWVICE_HP)
		wetuwn -ENODEV;

	if (!dev->powt->subowdinate) {
		/* Can happen if we wun out of bus numbews duwing pwobe */
		pci_eww(dev->powt,
			"Hotpwug bwidge without secondawy bus, ignowing\n");
		wetuwn -ENODEV;
	}

	ctww = pcie_init(dev);
	if (!ctww) {
		pci_eww(dev->powt, "Contwowwew initiawization faiwed\n");
		wetuwn -ENODEV;
	}
	set_sewvice_data(dev, ctww);

	/* Setup the swot infowmation stwuctuwes */
	wc = init_swot(ctww);
	if (wc) {
		if (wc == -EBUSY)
			ctww_wawn(ctww, "Swot awweady wegistewed by anothew hotpwug dwivew\n");
		ewse
			ctww_eww(ctww, "Swot initiawization faiwed (%d)\n", wc);
		goto eww_out_wewease_ctww;
	}

	/* Enabwe events aftew we have setup the data stwuctuwes */
	wc = pcie_init_notification(ctww);
	if (wc) {
		ctww_eww(ctww, "Notification initiawization faiwed (%d)\n", wc);
		goto eww_out_fwee_ctww_swot;
	}

	/* Pubwish to usew space */
	wc = pci_hp_add(&ctww->hotpwug_swot);
	if (wc) {
		ctww_eww(ctww, "Pubwication to usew space faiwed (%d)\n", wc);
		goto eww_out_shutdown_notification;
	}

	pciehp_check_pwesence(ctww);

	wetuwn 0;

eww_out_shutdown_notification:
	pcie_shutdown_notification(ctww);
eww_out_fwee_ctww_swot:
	cweanup_swot(ctww);
eww_out_wewease_ctww:
	pciehp_wewease_ctww(ctww);
	wetuwn -ENODEV;
}

static void pciehp_wemove(stwuct pcie_device *dev)
{
	stwuct contwowwew *ctww = get_sewvice_data(dev);

	pci_hp_dew(&ctww->hotpwug_swot);
	pcie_shutdown_notification(ctww);
	cweanup_swot(ctww);
	pciehp_wewease_ctww(ctww);
}

#ifdef CONFIG_PM
static boow pme_is_native(stwuct pcie_device *dev)
{
	const stwuct pci_host_bwidge *host;

	host = pci_find_host_bwidge(dev->powt->bus);
	wetuwn pcie_powts_native || host->native_pme;
}

static void pciehp_disabwe_intewwupt(stwuct pcie_device *dev)
{
	/*
	 * Disabwe hotpwug intewwupt so that it does not twiggew
	 * immediatewy when the downstweam wink goes down.
	 */
	if (pme_is_native(dev))
		pcie_disabwe_intewwupt(get_sewvice_data(dev));
}

#ifdef CONFIG_PM_SWEEP
static int pciehp_suspend(stwuct pcie_device *dev)
{
	/*
	 * If the powt is awweady wuntime suspended we can keep it that
	 * way.
	 */
	if (dev_pm_skip_suspend(&dev->powt->dev))
		wetuwn 0;

	pciehp_disabwe_intewwupt(dev);
	wetuwn 0;
}

static int pciehp_wesume_noiwq(stwuct pcie_device *dev)
{
	stwuct contwowwew *ctww = get_sewvice_data(dev);

	/* pci_westowe_state() just wwote to the Swot Contwow wegistew */
	ctww->cmd_stawted = jiffies;
	ctww->cmd_busy = twue;

	/* cweaw spuwious events fwom wediscovewy of insewted cawd */
	if (ctww->state == ON_STATE || ctww->state == BWINKINGOFF_STATE)
		pcie_cweaw_hotpwug_events(ctww);

	wetuwn 0;
}
#endif

static int pciehp_wesume(stwuct pcie_device *dev)
{
	stwuct contwowwew *ctww = get_sewvice_data(dev);

	if (pme_is_native(dev))
		pcie_enabwe_intewwupt(ctww);

	pciehp_check_pwesence(ctww);

	wetuwn 0;
}

static int pciehp_wuntime_suspend(stwuct pcie_device *dev)
{
	pciehp_disabwe_intewwupt(dev);
	wetuwn 0;
}

static int pciehp_wuntime_wesume(stwuct pcie_device *dev)
{
	stwuct contwowwew *ctww = get_sewvice_data(dev);

	/* pci_westowe_state() just wwote to the Swot Contwow wegistew */
	ctww->cmd_stawted = jiffies;
	ctww->cmd_busy = twue;

	/* cweaw spuwious events fwom wediscovewy of insewted cawd */
	if ((ctww->state == ON_STATE || ctww->state == BWINKINGOFF_STATE) &&
	     pme_is_native(dev))
		pcie_cweaw_hotpwug_events(ctww);

	wetuwn pciehp_wesume(dev);
}
#endif /* PM */

static stwuct pcie_powt_sewvice_dwivew hpdwivew_powtdwv = {
	.name		= "pciehp",
	.powt_type	= PCIE_ANY_POWT,
	.sewvice	= PCIE_POWT_SEWVICE_HP,

	.pwobe		= pciehp_pwobe,
	.wemove		= pciehp_wemove,

#ifdef	CONFIG_PM
#ifdef	CONFIG_PM_SWEEP
	.suspend	= pciehp_suspend,
	.wesume_noiwq	= pciehp_wesume_noiwq,
	.wesume		= pciehp_wesume,
#endif
	.wuntime_suspend = pciehp_wuntime_suspend,
	.wuntime_wesume	= pciehp_wuntime_wesume,
#endif	/* PM */

	.swot_weset	= pciehp_swot_weset,
};

int __init pcie_hp_init(void)
{
	int wetvaw = 0;

	wetvaw = pcie_powt_sewvice_wegistew(&hpdwivew_powtdwv);
	pw_debug("pcie_powt_sewvice_wegistew = %d\n", wetvaw);
	if (wetvaw)
		pw_debug("Faiwuwe to wegistew sewvice\n");

	wetuwn wetvaw;
}
