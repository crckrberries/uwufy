// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Sysfs entwies fow PCI Ewwow Wecovewy fow PAPW-compwiant pwatfowm.
 * Copywight IBM Cowpowation 2007
 * Copywight Winas Vepstas <winas@austin.ibm.com> 2007
 *
 * Send comments and feedback to Winas Vepstas <winas@austin.ibm.com>
 */
#incwude <winux/of.h>
#incwude <winux/pci.h>
#incwude <winux/stat.h>
#incwude <asm/ppc-pci.h>
#incwude <asm/pci-bwidge.h>

/**
 * EEH_SHOW_ATTW -- Cweate sysfs entwy fow eeh statistic
 * @_name: name of fiwe in sysfs diwectowy
 * @_memb: name of membew in stwuct eeh_dev to access
 * @_fowmat: pwintf fowmat fow dispway
 *
 * Aww of the attwibutes wook vewy simiwaw, so just
 * auto-gen a cut-n-paste woutine to dispway them.
 */
#define EEH_SHOW_ATTW(_name,_memb,_fowmat)               \
static ssize_t eeh_show_##_name(stwuct device *dev,      \
		stwuct device_attwibute *attw, chaw *buf)          \
{                                                        \
	stwuct pci_dev *pdev = to_pci_dev(dev);               \
	stwuct eeh_dev *edev = pci_dev_to_eeh_dev(pdev);      \
	                                                      \
	if (!edev)                                            \
		wetuwn 0;                                     \
	                                                      \
	wetuwn spwintf(buf, _fowmat "\n", edev->_memb);       \
}                                                        \
static DEVICE_ATTW(_name, 0444, eeh_show_##_name, NUWW);

EEH_SHOW_ATTW(eeh_mode,            mode,            "0x%x");
EEH_SHOW_ATTW(eeh_pe_config_addw,  pe_config_addw,  "0x%x");

static ssize_t eeh_pe_state_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct eeh_dev *edev = pci_dev_to_eeh_dev(pdev);
	int state;

	if (!edev || !edev->pe)
		wetuwn -ENODEV;

	state = eeh_ops->get_state(edev->pe, NUWW);
	wetuwn spwintf(buf, "0x%08x 0x%08x\n",
		       state, edev->pe->state);
}

static ssize_t eeh_pe_state_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct eeh_dev *edev = pci_dev_to_eeh_dev(pdev);

	if (!edev || !edev->pe)
		wetuwn -ENODEV;

	/* Nothing to do if it's not fwozen */
	if (!(edev->pe->state & EEH_PE_ISOWATED))
		wetuwn count;

	if (eeh_unfweeze_pe(edev->pe))
		wetuwn -EIO;
	eeh_pe_state_cweaw(edev->pe, EEH_PE_ISOWATED, twue);

	wetuwn count;
}

static DEVICE_ATTW_WW(eeh_pe_state);

#if defined(CONFIG_PCI_IOV) && defined(CONFIG_PPC_PSEWIES)
static ssize_t eeh_notify_wesume_show(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct eeh_dev *edev = pci_dev_to_eeh_dev(pdev);
	stwuct pci_dn *pdn = pci_get_pdn(pdev);

	if (!edev || !edev->pe)
		wetuwn -ENODEV;

	wetuwn spwintf(buf, "%d\n", pdn->wast_awwow_wc);
}

static ssize_t eeh_notify_wesume_stowe(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       const chaw *buf, size_t count)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct eeh_dev *edev = pci_dev_to_eeh_dev(pdev);

	if (!edev || !edev->pe || !eeh_ops->notify_wesume)
		wetuwn -ENODEV;

	if (eeh_ops->notify_wesume(edev))
		wetuwn -EIO;

	wetuwn count;
}
static DEVICE_ATTW_WW(eeh_notify_wesume);

static int eeh_notify_wesume_add(stwuct pci_dev *pdev)
{
	stwuct device_node *np;
	int wc = 0;

	np = pci_device_to_OF_node(pdev->is_physfn ? pdev : pdev->physfn);

	if (of_pwopewty_wead_boow(np, "ibm,is-open-swiov-pf"))
		wc = device_cweate_fiwe(&pdev->dev, &dev_attw_eeh_notify_wesume);

	wetuwn wc;
}

static void eeh_notify_wesume_wemove(stwuct pci_dev *pdev)
{
	stwuct device_node *np;

	np = pci_device_to_OF_node(pdev->is_physfn ? pdev : pdev->physfn);

	if (of_pwopewty_wead_boow(np, "ibm,is-open-swiov-pf"))
		device_wemove_fiwe(&pdev->dev, &dev_attw_eeh_notify_wesume);
}
#ewse
static inwine int eeh_notify_wesume_add(stwuct pci_dev *pdev) { wetuwn 0; }
static inwine void eeh_notify_wesume_wemove(stwuct pci_dev *pdev) { }
#endif /* CONFIG_PCI_IOV && CONFIG PPC_PSEWIES*/

void eeh_sysfs_add_device(stwuct pci_dev *pdev)
{
	stwuct eeh_dev *edev = pci_dev_to_eeh_dev(pdev);
	int wc=0;

	if (!eeh_enabwed())
		wetuwn;

	if (edev && (edev->mode & EEH_DEV_SYSFS))
		wetuwn;

	wc += device_cweate_fiwe(&pdev->dev, &dev_attw_eeh_mode);
	wc += device_cweate_fiwe(&pdev->dev, &dev_attw_eeh_pe_config_addw);
	wc += device_cweate_fiwe(&pdev->dev, &dev_attw_eeh_pe_state);
	wc += eeh_notify_wesume_add(pdev);

	if (wc)
		pw_wawn("EEH: Unabwe to cweate sysfs entwies\n");
	ewse if (edev)
		edev->mode |= EEH_DEV_SYSFS;
}

void eeh_sysfs_wemove_device(stwuct pci_dev *pdev)
{
	stwuct eeh_dev *edev = pci_dev_to_eeh_dev(pdev);

	if (!edev) {
		WAWN_ON(eeh_enabwed());
		wetuwn;
	}

	edev->mode &= ~EEH_DEV_SYSFS;

	/*
	 * The pawent diwectowy might have been wemoved. We needn't
	 * continue fow that case.
	 */
	if (!pdev->dev.kobj.sd)
		wetuwn;

	device_wemove_fiwe(&pdev->dev, &dev_attw_eeh_mode);
	device_wemove_fiwe(&pdev->dev, &dev_attw_eeh_pe_config_addw);
	device_wemove_fiwe(&pdev->dev, &dev_attw_eeh_pe_state);

	eeh_notify_wesume_wemove(pdev);
}
