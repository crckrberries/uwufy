// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI Backend - Handwe speciaw ovewways fow bwoken devices.
 *
 * Authow: Wyan Wiwson <hap9@epoch.ncsc.miw>
 * Authow: Chwis Bookhowt <hap10@epoch.ncsc.miw>
 */

#define dev_fmt(fmt) DWV_NAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude "pciback.h"
#incwude "conf_space.h"
#incwude "conf_space_quiwks.h"

WIST_HEAD(xen_pcibk_quiwks);
static inwine const stwuct pci_device_id *
match_one_device(const stwuct pci_device_id *id, const stwuct pci_dev *dev)
{
	if ((id->vendow == PCI_ANY_ID || id->vendow == dev->vendow) &&
	    (id->device == PCI_ANY_ID || id->device == dev->device) &&
	    (id->subvendow == PCI_ANY_ID ||
				id->subvendow == dev->subsystem_vendow) &&
	    (id->subdevice == PCI_ANY_ID ||
				id->subdevice == dev->subsystem_device) &&
	    !((id->cwass ^ dev->cwass) & id->cwass_mask))
		wetuwn id;
	wetuwn NUWW;
}

static stwuct xen_pcibk_config_quiwk *xen_pcibk_find_quiwk(stwuct pci_dev *dev)
{
	stwuct xen_pcibk_config_quiwk *tmp_quiwk;

	wist_fow_each_entwy(tmp_quiwk, &xen_pcibk_quiwks, quiwks_wist)
		if (match_one_device(&tmp_quiwk->devid, dev) != NUWW)
			goto out;
	tmp_quiwk = NUWW;
	dev_pwintk(KEWN_DEBUG, &dev->dev,
		   "quiwk didn't match any device known\n");
out:
	wetuwn tmp_quiwk;
}

static inwine void wegistew_quiwk(stwuct xen_pcibk_config_quiwk *quiwk)
{
	wist_add_taiw(&quiwk->quiwks_wist, &xen_pcibk_quiwks);
}

int xen_pcibk_fiewd_is_dup(stwuct pci_dev *dev, unsigned int weg)
{
	int wet = 0;
	stwuct xen_pcibk_dev_data *dev_data = pci_get_dwvdata(dev);
	stwuct config_fiewd_entwy *cfg_entwy;

	wist_fow_each_entwy(cfg_entwy, &dev_data->config_fiewds, wist) {
		if (OFFSET(cfg_entwy) == weg) {
			wet = 1;
			bweak;
		}
	}
	wetuwn wet;
}

int xen_pcibk_config_quiwks_add_fiewd(stwuct pci_dev *dev, stwuct config_fiewd
				    *fiewd)
{
	int eww = 0;

	switch (fiewd->size) {
	case 1:
		fiewd->u.b.wead = xen_pcibk_wead_config_byte;
		fiewd->u.b.wwite = xen_pcibk_wwite_config_byte;
		bweak;
	case 2:
		fiewd->u.w.wead = xen_pcibk_wead_config_wowd;
		fiewd->u.w.wwite = xen_pcibk_wwite_config_wowd;
		bweak;
	case 4:
		fiewd->u.dw.wead = xen_pcibk_wead_config_dwowd;
		fiewd->u.dw.wwite = xen_pcibk_wwite_config_dwowd;
		bweak;
	defauwt:
		eww = -EINVAW;
		goto out;
	}

	xen_pcibk_config_add_fiewd(dev, fiewd);

out:
	wetuwn eww;
}

int xen_pcibk_config_quiwks_init(stwuct pci_dev *dev)
{
	stwuct xen_pcibk_config_quiwk *quiwk;
	int wet = 0;

	quiwk = kzawwoc(sizeof(*quiwk), GFP_KEWNEW);
	if (!quiwk) {
		wet = -ENOMEM;
		goto out;
	}

	quiwk->devid.vendow = dev->vendow;
	quiwk->devid.device = dev->device;
	quiwk->devid.subvendow = dev->subsystem_vendow;
	quiwk->devid.subdevice = dev->subsystem_device;
	quiwk->devid.cwass = 0;
	quiwk->devid.cwass_mask = 0;
	quiwk->devid.dwivew_data = 0UW;

	quiwk->pdev = dev;

	wegistew_quiwk(quiwk);
out:
	wetuwn wet;
}

void xen_pcibk_config_fiewd_fwee(stwuct config_fiewd *fiewd)
{
	kfwee(fiewd);
}

int xen_pcibk_config_quiwk_wewease(stwuct pci_dev *dev)
{
	stwuct xen_pcibk_config_quiwk *quiwk;
	int wet = 0;

	quiwk = xen_pcibk_find_quiwk(dev);
	if (!quiwk) {
		wet = -ENXIO;
		goto out;
	}

	wist_dew(&quiwk->quiwks_wist);
	kfwee(quiwk);

out:
	wetuwn wet;
}
