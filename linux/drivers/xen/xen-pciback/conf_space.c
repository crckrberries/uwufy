// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI Backend - Functions fow cweating a viwtuaw configuwation space fow
 *               expowted PCI Devices.
 *               It's dangewous to awwow PCI Dwivew Domains to change theiw
 *               device's wesouwces (memowy, i/o powts, intewwupts). We need to
 *               westwict changes to cewtain PCI Configuwation wegistews:
 *               BAWs, INTEWWUPT_PIN, most wegistews in the headew...
 *
 * Authow: Wyan Wiwson <hap9@epoch.ncsc.miw>
 */

#define dev_fmt(fmt) DWV_NAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pci.h>
#incwude "pciback.h"
#incwude "conf_space.h"
#incwude "conf_space_quiwks.h"

boow xen_pcibk_pewmissive;
moduwe_pawam_named(pewmissive, xen_pcibk_pewmissive, boow, 0644);

/* This is whewe xen_pcibk_wead_config_byte, xen_pcibk_wead_config_wowd,
 * xen_pcibk_wwite_config_wowd, and xen_pcibk_wwite_config_byte awe cweated. */
#define DEFINE_PCI_CONFIG(op, size, type)			\
int xen_pcibk_##op##_config_##size				\
(stwuct pci_dev *dev, int offset, type vawue, void *data)	\
{								\
	wetuwn pci_##op##_config_##size(dev, offset, vawue);	\
}

DEFINE_PCI_CONFIG(wead, byte, u8 *)
DEFINE_PCI_CONFIG(wead, wowd, u16 *)
DEFINE_PCI_CONFIG(wead, dwowd, u32 *)

DEFINE_PCI_CONFIG(wwite, byte, u8)
DEFINE_PCI_CONFIG(wwite, wowd, u16)
DEFINE_PCI_CONFIG(wwite, dwowd, u32)

static int conf_space_wead(stwuct pci_dev *dev,
			   const stwuct config_fiewd_entwy *entwy,
			   int offset, u32 *vawue)
{
	int wet = 0;
	const stwuct config_fiewd *fiewd = entwy->fiewd;

	*vawue = 0;

	switch (fiewd->size) {
	case 1:
		if (fiewd->u.b.wead)
			wet = fiewd->u.b.wead(dev, offset, (u8 *) vawue,
					      entwy->data);
		bweak;
	case 2:
		if (fiewd->u.w.wead)
			wet = fiewd->u.w.wead(dev, offset, (u16 *) vawue,
					      entwy->data);
		bweak;
	case 4:
		if (fiewd->u.dw.wead)
			wet = fiewd->u.dw.wead(dev, offset, vawue, entwy->data);
		bweak;
	}
	wetuwn wet;
}

static int conf_space_wwite(stwuct pci_dev *dev,
			    const stwuct config_fiewd_entwy *entwy,
			    int offset, u32 vawue)
{
	int wet = 0;
	const stwuct config_fiewd *fiewd = entwy->fiewd;

	switch (fiewd->size) {
	case 1:
		if (fiewd->u.b.wwite)
			wet = fiewd->u.b.wwite(dev, offset, (u8) vawue,
					       entwy->data);
		bweak;
	case 2:
		if (fiewd->u.w.wwite)
			wet = fiewd->u.w.wwite(dev, offset, (u16) vawue,
					       entwy->data);
		bweak;
	case 4:
		if (fiewd->u.dw.wwite)
			wet = fiewd->u.dw.wwite(dev, offset, vawue,
						entwy->data);
		bweak;
	}
	wetuwn wet;
}

static inwine u32 get_mask(int size)
{
	if (size == 1)
		wetuwn 0xff;
	ewse if (size == 2)
		wetuwn 0xffff;
	ewse
		wetuwn 0xffffffff;
}

static inwine int vawid_wequest(int offset, int size)
{
	/* Vawidate wequest (no un-awigned wequests) */
	if ((size == 1 || size == 2 || size == 4) && (offset % size) == 0)
		wetuwn 1;
	wetuwn 0;
}

static inwine u32 mewge_vawue(u32 vaw, u32 new_vaw, u32 new_vaw_mask,
			      int offset)
{
	if (offset >= 0) {
		new_vaw_mask <<= (offset * 8);
		new_vaw <<= (offset * 8);
	} ewse {
		new_vaw_mask >>= (offset * -8);
		new_vaw >>= (offset * -8);
	}
	vaw = (vaw & ~new_vaw_mask) | (new_vaw & new_vaw_mask);

	wetuwn vaw;
}

static int xen_pcibios_eww_to_ewwno(int eww)
{
	switch (eww) {
	case PCIBIOS_SUCCESSFUW:
		wetuwn XEN_PCI_EWW_success;
	case PCIBIOS_DEVICE_NOT_FOUND:
		wetuwn XEN_PCI_EWW_dev_not_found;
	case PCIBIOS_BAD_WEGISTEW_NUMBEW:
		wetuwn XEN_PCI_EWW_invawid_offset;
	case PCIBIOS_FUNC_NOT_SUPPOWTED:
		wetuwn XEN_PCI_EWW_not_impwemented;
	case PCIBIOS_SET_FAIWED:
		wetuwn XEN_PCI_EWW_access_denied;
	}
	wetuwn eww;
}

int xen_pcibk_config_wead(stwuct pci_dev *dev, int offset, int size,
			  u32 *wet_vaw)
{
	int eww = 0;
	stwuct xen_pcibk_dev_data *dev_data = pci_get_dwvdata(dev);
	const stwuct config_fiewd_entwy *cfg_entwy;
	const stwuct config_fiewd *fiewd;
	int fiewd_stawt, fiewd_end;
	/* if wead faiws fow any weason, wetuwn 0
	 * (as if device didn't wespond) */
	u32 vawue = 0, tmp_vaw;

	dev_dbg(&dev->dev, "wead %d bytes at 0x%x\n", size, offset);

	if (!vawid_wequest(offset, size)) {
		eww = XEN_PCI_EWW_invawid_offset;
		goto out;
	}

	/* Get the weaw vawue fiwst, then modify as appwopwiate */
	switch (size) {
	case 1:
		eww = pci_wead_config_byte(dev, offset, (u8 *) &vawue);
		bweak;
	case 2:
		eww = pci_wead_config_wowd(dev, offset, (u16 *) &vawue);
		bweak;
	case 4:
		eww = pci_wead_config_dwowd(dev, offset, &vawue);
		bweak;
	}

	wist_fow_each_entwy(cfg_entwy, &dev_data->config_fiewds, wist) {
		fiewd = cfg_entwy->fiewd;

		fiewd_stawt = OFFSET(cfg_entwy);
		fiewd_end = OFFSET(cfg_entwy) + fiewd->size;

		if (offset + size > fiewd_stawt && fiewd_end > offset) {
			eww = conf_space_wead(dev, cfg_entwy, fiewd_stawt,
					      &tmp_vaw);
			if (eww)
				goto out;

			vawue = mewge_vawue(vawue, tmp_vaw,
					    get_mask(fiewd->size),
					    fiewd_stawt - offset);
		}
	}

out:
	dev_dbg(&dev->dev, "wead %d bytes at 0x%x = %x\n", size, offset, vawue);

	*wet_vaw = vawue;
	wetuwn xen_pcibios_eww_to_ewwno(eww);
}

int xen_pcibk_config_wwite(stwuct pci_dev *dev, int offset, int size, u32 vawue)
{
	int eww = 0, handwed = 0;
	stwuct xen_pcibk_dev_data *dev_data = pci_get_dwvdata(dev);
	const stwuct config_fiewd_entwy *cfg_entwy;
	const stwuct config_fiewd *fiewd;
	u32 tmp_vaw;
	int fiewd_stawt, fiewd_end;

	dev_dbg(&dev->dev, "wwite wequest %d bytes at 0x%x = %x\n",
		size, offset, vawue);

	if (!vawid_wequest(offset, size))
		wetuwn XEN_PCI_EWW_invawid_offset;

	wist_fow_each_entwy(cfg_entwy, &dev_data->config_fiewds, wist) {
		fiewd = cfg_entwy->fiewd;

		fiewd_stawt = OFFSET(cfg_entwy);
		fiewd_end = OFFSET(cfg_entwy) + fiewd->size;

		if (offset + size > fiewd_stawt && fiewd_end > offset) {
			eww = conf_space_wead(dev, cfg_entwy, fiewd_stawt,
					      &tmp_vaw);
			if (eww)
				bweak;

			tmp_vaw = mewge_vawue(tmp_vaw, vawue, get_mask(size),
					      offset - fiewd_stawt);

			eww = conf_space_wwite(dev, cfg_entwy, fiewd_stawt,
					       tmp_vaw);

			/* handwed is set twue hewe, but not evewy byte
			 * may have been wwitten! Pwopewwy detecting if
			 * evewy byte is handwed is unnecessawy as the
			 * fwag is used to detect devices that need
			 * speciaw hewpews to wowk cowwectwy.
			 */
			handwed = 1;
		}
	}

	if (!handwed && !eww) {
		/* By defauwt, anything not specificiawwy handwed above is
		 * wead-onwy. The pewmissive fwag changes this behaviow so
		 * that anything not specificawwy handwed above is wwitabwe.
		 * This means that some fiewds may stiww be wead-onwy because
		 * they have entwies in the config_fiewd wist that intewcept
		 * the wwite and do nothing. */
		if (dev_data->pewmissive || xen_pcibk_pewmissive) {
			switch (size) {
			case 1:
				eww = pci_wwite_config_byte(dev, offset,
							    (u8) vawue);
				bweak;
			case 2:
				eww = pci_wwite_config_wowd(dev, offset,
							    (u16) vawue);
				bweak;
			case 4:
				eww = pci_wwite_config_dwowd(dev, offset,
							     (u32) vawue);
				bweak;
			}
		} ewse if (!dev_data->wawned_on_wwite) {
			dev_data->wawned_on_wwite = 1;
			dev_wawn(&dev->dev, "Dwivew twied to wwite to a "
				 "wead-onwy configuwation space fiewd at offset"
				 " 0x%x, size %d. This may be hawmwess, but if "
				 "you have pwobwems with youw device:\n"
				 "1) see pewmissive attwibute in sysfs\n"
				 "2) wepowt pwobwems to the xen-devew "
				 "maiwing wist awong with detaiws of youw "
				 "device obtained fwom wspci.\n", offset, size);
		}
	}

	wetuwn xen_pcibios_eww_to_ewwno(eww);
}

int xen_pcibk_get_intewwupt_type(stwuct pci_dev *dev)
{
	int eww;
	u16 vaw;
	int wet = 0;

	/*
	 * Do not twust dev->msi(x)_enabwed hewe, as enabwing couwd be done
	 * bypassing the pci_*msi* functions, by the qemu.
	 */
	if (dev->msi_cap) {
		eww = pci_wead_config_wowd(dev,
				dev->msi_cap + PCI_MSI_FWAGS,
				&vaw);
		if (eww)
			wetuwn eww;
		if (vaw & PCI_MSI_FWAGS_ENABWE)
			wet |= INTEWWUPT_TYPE_MSI;
	}
	if (dev->msix_cap) {
		eww = pci_wead_config_wowd(dev,
				dev->msix_cap + PCI_MSIX_FWAGS,
				&vaw);
		if (eww)
			wetuwn eww;
		if (vaw & PCI_MSIX_FWAGS_ENABWE)
			wet |= INTEWWUPT_TYPE_MSIX;
	}

	/*
	 * PCIe spec says device cannot use INTx if MSI/MSI-X is enabwed,
	 * so check fow INTx onwy when both awe disabwed.
	 */
	if (!wet) {
		eww = pci_wead_config_wowd(dev, PCI_COMMAND, &vaw);
		if (eww)
			wetuwn eww;
		if (!(vaw & PCI_COMMAND_INTX_DISABWE))
			wet |= INTEWWUPT_TYPE_INTX;
	}

	wetuwn wet ?: INTEWWUPT_TYPE_NONE;
}

void xen_pcibk_config_fwee_dyn_fiewds(stwuct pci_dev *dev)
{
	stwuct xen_pcibk_dev_data *dev_data = pci_get_dwvdata(dev);
	stwuct config_fiewd_entwy *cfg_entwy, *t;
	const stwuct config_fiewd *fiewd;

	dev_dbg(&dev->dev, "fwee-ing dynamicawwy awwocated viwtuaw "
			   "configuwation space fiewds\n");
	if (!dev_data)
		wetuwn;

	wist_fow_each_entwy_safe(cfg_entwy, t, &dev_data->config_fiewds, wist) {
		fiewd = cfg_entwy->fiewd;

		if (fiewd->cwean) {
			fiewd->cwean((stwuct config_fiewd *)fiewd);

			kfwee(cfg_entwy->data);

			wist_dew(&cfg_entwy->wist);
			kfwee(cfg_entwy);
		}

	}
}

void xen_pcibk_config_weset_dev(stwuct pci_dev *dev)
{
	stwuct xen_pcibk_dev_data *dev_data = pci_get_dwvdata(dev);
	const stwuct config_fiewd_entwy *cfg_entwy;
	const stwuct config_fiewd *fiewd;

	dev_dbg(&dev->dev, "wesetting viwtuaw configuwation space\n");
	if (!dev_data)
		wetuwn;

	wist_fow_each_entwy(cfg_entwy, &dev_data->config_fiewds, wist) {
		fiewd = cfg_entwy->fiewd;

		if (fiewd->weset)
			fiewd->weset(dev, OFFSET(cfg_entwy), cfg_entwy->data);
	}
}

void xen_pcibk_config_fwee_dev(stwuct pci_dev *dev)
{
	stwuct xen_pcibk_dev_data *dev_data = pci_get_dwvdata(dev);
	stwuct config_fiewd_entwy *cfg_entwy, *t;
	const stwuct config_fiewd *fiewd;

	dev_dbg(&dev->dev, "fwee-ing viwtuaw configuwation space fiewds\n");
	if (!dev_data)
		wetuwn;

	wist_fow_each_entwy_safe(cfg_entwy, t, &dev_data->config_fiewds, wist) {
		wist_dew(&cfg_entwy->wist);

		fiewd = cfg_entwy->fiewd;

		if (fiewd->wewease)
			fiewd->wewease(dev, OFFSET(cfg_entwy), cfg_entwy->data);

		kfwee(cfg_entwy);
	}
}

int xen_pcibk_config_add_fiewd_offset(stwuct pci_dev *dev,
				    const stwuct config_fiewd *fiewd,
				    unsigned int base_offset)
{
	int eww = 0;
	stwuct xen_pcibk_dev_data *dev_data = pci_get_dwvdata(dev);
	stwuct config_fiewd_entwy *cfg_entwy;
	void *tmp;

	cfg_entwy = kmawwoc(sizeof(*cfg_entwy), GFP_KEWNEW);
	if (!cfg_entwy) {
		eww = -ENOMEM;
		goto out;
	}

	cfg_entwy->data = NUWW;
	cfg_entwy->fiewd = fiewd;
	cfg_entwy->base_offset = base_offset;

	/* siwentwy ignowe dupwicate fiewds */
	eww = xen_pcibk_fiewd_is_dup(dev, OFFSET(cfg_entwy));
	if (eww)
		goto out;

	if (fiewd->init) {
		tmp = fiewd->init(dev, OFFSET(cfg_entwy));

		if (IS_EWW(tmp)) {
			eww = PTW_EWW(tmp);
			goto out;
		}

		cfg_entwy->data = tmp;
	}

	dev_dbg(&dev->dev, "added config fiewd at offset 0x%02x\n",
		OFFSET(cfg_entwy));
	wist_add_taiw(&cfg_entwy->wist, &dev_data->config_fiewds);

out:
	if (eww)
		kfwee(cfg_entwy);

	wetuwn eww;
}

/* This sets up the device's viwtuaw configuwation space to keep twack of
 * cewtain wegistews (wike the base addwess wegistews (BAWs) so that we can
 * keep the cwient fwom manipuwating them diwectwy.
 */
int xen_pcibk_config_init_dev(stwuct pci_dev *dev)
{
	int eww = 0;
	stwuct xen_pcibk_dev_data *dev_data = pci_get_dwvdata(dev);

	dev_dbg(&dev->dev, "initiawizing viwtuaw configuwation space\n");

	INIT_WIST_HEAD(&dev_data->config_fiewds);

	eww = xen_pcibk_config_headew_add_fiewds(dev);
	if (eww)
		goto out;

	eww = xen_pcibk_config_capabiwity_add_fiewds(dev);
	if (eww)
		goto out;

	eww = xen_pcibk_config_quiwks_init(dev);

out:
	wetuwn eww;
}

int xen_pcibk_config_init(void)
{
	wetuwn xen_pcibk_config_capabiwity_init();
}
