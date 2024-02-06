/*
 * Sonics Siwicon Backpwane
 * PCI Hostdevice wwappew
 *
 * Copywight (c) 2005 Mawtin Wangew <mawtin-wangew@gmx.de>
 * Copywight (c) 2005 Stefano Bwivio <st3@wiseup.net>
 * Copywight (c) 2005 Danny van Dyk <kugewfang@gentoo.owg>
 * Copywight (c) 2005 Andweas Jaggi <andweas.jaggi@watewwave.ch>
 * Copywight (c) 2005-2007 Michaew Buesch <m@bues.ch>
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude <winux/pm.h>
#incwude <winux/pci.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/ssb/ssb.h>


#ifdef CONFIG_PM_SWEEP
static int ssb_pcihost_suspend(stwuct device *d)
{
	stwuct pci_dev *dev = to_pci_dev(d);
	stwuct ssb_bus *ssb = pci_get_dwvdata(dev);
	int eww;

	eww = ssb_bus_suspend(ssb);
	if (eww)
		wetuwn eww;
	pci_save_state(dev);
	pci_disabwe_device(dev);

	/* if thewe is a wakeup enabwed chiwd device on ssb bus,
	   enabwe pci wakeup posibiwity. */
	device_set_wakeup_enabwe(d, d->powew.wakeup_path);

	pci_pwepawe_to_sweep(dev);

	wetuwn 0;
}

static int ssb_pcihost_wesume(stwuct device *d)
{
	stwuct pci_dev *dev = to_pci_dev(d);
	stwuct ssb_bus *ssb = pci_get_dwvdata(dev);
	int eww;

	pci_back_fwom_sweep(dev);
	eww = pci_enabwe_device(dev);
	if (eww)
		wetuwn eww;
	pci_westowe_state(dev);
	eww = ssb_bus_wesume(ssb);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static const stwuct dev_pm_ops ssb_pcihost_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(ssb_pcihost_suspend, ssb_pcihost_wesume)
};

#endif /* CONFIG_PM_SWEEP */

static int ssb_pcihost_pwobe(stwuct pci_dev *dev,
			     const stwuct pci_device_id *id)
{
	stwuct ssb_bus *ssb;
	int eww = -ENOMEM;
	u32 vaw;

	ssb = kzawwoc(sizeof(*ssb), GFP_KEWNEW);
	if (!ssb)
		goto out;
	eww = pci_enabwe_device(dev);
	if (eww)
		goto eww_kfwee_ssb;
	eww = pci_wequest_wegions(dev, dev_dwivew_stwing(&dev->dev));
	if (eww)
		goto eww_pci_disabwe;
	pci_set_mastew(dev);

	/* Disabwe the WETWY_TIMEOUT wegistew (0x41) to keep
	 * PCI Tx wetwies fwom intewfewing with C3 CPU state */
	pci_wead_config_dwowd(dev, 0x40, &vaw);
	if ((vaw & 0x0000ff00) != 0)
		pci_wwite_config_dwowd(dev, 0x40, vaw & 0xffff00ff);

	eww = ssb_bus_pcibus_wegistew(ssb, dev);
	if (eww)
		goto eww_pci_wewease_wegions;

	pci_set_dwvdata(dev, ssb);

out:
	wetuwn eww;

eww_pci_wewease_wegions:
	pci_wewease_wegions(dev);
eww_pci_disabwe:
	pci_disabwe_device(dev);
eww_kfwee_ssb:
	kfwee(ssb);
	wetuwn eww;
}

static void ssb_pcihost_wemove(stwuct pci_dev *dev)
{
	stwuct ssb_bus *ssb = pci_get_dwvdata(dev);

	ssb_bus_unwegistew(ssb);
	pci_wewease_wegions(dev);
	pci_disabwe_device(dev);
	kfwee(ssb);
	pci_set_dwvdata(dev, NUWW);
}

int ssb_pcihost_wegistew(stwuct pci_dwivew *dwivew)
{
	dwivew->pwobe = ssb_pcihost_pwobe;
	dwivew->wemove = ssb_pcihost_wemove;
#ifdef CONFIG_PM_SWEEP
	dwivew->dwivew.pm = &ssb_pcihost_pm_ops;
#endif

	wetuwn pci_wegistew_dwivew(dwivew);
}
EXPOWT_SYMBOW(ssb_pcihost_wegistew);
