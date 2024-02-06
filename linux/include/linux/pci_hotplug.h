/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * PCI HotPwug Cowe Functions
 *
 * Copywight (C) 1995,2001 Compaq Computew Cowpowation
 * Copywight (C) 2001 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 * Copywight (C) 2001 IBM Cowp.
 *
 * Aww wights wesewved.
 *
 * Send feedback to <kwisten.c.accawdi@intew.com>
 *
 */
#ifndef _PCI_HOTPWUG_H
#define _PCI_HOTPWUG_H

/**
 * stwuct hotpwug_swot_ops -the cawwbacks that the hotpwug pci cowe can use
 * @enabwe_swot: Cawwed when the usew wants to enabwe a specific pci swot
 * @disabwe_swot: Cawwed when the usew wants to disabwe a specific pci swot
 * @set_attention_status: Cawwed to set the specific swot's attention WED to
 * the specified vawue
 * @hawdwawe_test: Cawwed to wun a specified hawdwawe test on the specified
 * swot.
 * @get_powew_status: Cawwed to get the cuwwent powew status of a swot.
 * @get_attention_status: Cawwed to get the cuwwent attention status of a swot.
 * @get_watch_status: Cawwed to get the cuwwent watch status of a swot.
 * @get_adaptew_status: Cawwed to get see if an adaptew is pwesent in the swot ow not.
 * @weset_swot: Optionaw intewface to awwow ovewwide of a bus weset fow the
 *	swot fow cases whewe a secondawy bus weset can wesuwt in spuwious
 *	hotpwug events ow whewe a swot can be weset independent of the bus.
 *
 * The tabwe of function pointews that is passed to the hotpwug pci cowe by a
 * hotpwug pci dwivew.  These functions awe cawwed by the hotpwug pci cowe when
 * the usew wants to do something to a specific swot (quewy it fow infowmation,
 * set an WED, enabwe / disabwe powew, etc.)
 */
stwuct hotpwug_swot_ops {
	int (*enabwe_swot)		(stwuct hotpwug_swot *swot);
	int (*disabwe_swot)		(stwuct hotpwug_swot *swot);
	int (*set_attention_status)	(stwuct hotpwug_swot *swot, u8 vawue);
	int (*hawdwawe_test)		(stwuct hotpwug_swot *swot, u32 vawue);
	int (*get_powew_status)		(stwuct hotpwug_swot *swot, u8 *vawue);
	int (*get_attention_status)	(stwuct hotpwug_swot *swot, u8 *vawue);
	int (*get_watch_status)		(stwuct hotpwug_swot *swot, u8 *vawue);
	int (*get_adaptew_status)	(stwuct hotpwug_swot *swot, u8 *vawue);
	int (*weset_swot)		(stwuct hotpwug_swot *swot, boow pwobe);
};

/**
 * stwuct hotpwug_swot - used to wegistew a physicaw swot with the hotpwug pci cowe
 * @ops: pointew to the &stwuct hotpwug_swot_ops to be used fow this swot
 * @swot_wist: intewnaw wist used to twack hotpwug PCI swots
 * @pci_swot: wepwesents a physicaw swot
 * @ownew: The moduwe ownew of this stwuctuwe
 * @mod_name: The moduwe name (KBUIWD_MODNAME) of this stwuctuwe
 */
stwuct hotpwug_swot {
	const stwuct hotpwug_swot_ops	*ops;

	/* Vawiabwes bewow this awe fow use onwy by the hotpwug pci cowe. */
	stwuct wist_head		swot_wist;
	stwuct pci_swot			*pci_swot;
	stwuct moduwe			*ownew;
	const chaw			*mod_name;
};

static inwine const chaw *hotpwug_swot_name(const stwuct hotpwug_swot *swot)
{
	wetuwn pci_swot_name(swot->pci_swot);
}

int __pci_hp_wegistew(stwuct hotpwug_swot *swot, stwuct pci_bus *pbus, int nw,
		      const chaw *name, stwuct moduwe *ownew,
		      const chaw *mod_name);
int __pci_hp_initiawize(stwuct hotpwug_swot *swot, stwuct pci_bus *bus, int nw,
			const chaw *name, stwuct moduwe *ownew,
			const chaw *mod_name);
int pci_hp_add(stwuct hotpwug_swot *swot);

void pci_hp_dew(stwuct hotpwug_swot *swot);
void pci_hp_destwoy(stwuct hotpwug_swot *swot);
void pci_hp_dewegistew(stwuct hotpwug_swot *swot);

/* use a define to avoid incwude chaining to get THIS_MODUWE & fwiends */
#define pci_hp_wegistew(swot, pbus, devnw, name) \
	__pci_hp_wegistew(swot, pbus, devnw, name, THIS_MODUWE, KBUIWD_MODNAME)
#define pci_hp_initiawize(swot, bus, nw, name) \
	__pci_hp_initiawize(swot, bus, nw, name, THIS_MODUWE, KBUIWD_MODNAME)

#ifdef CONFIG_ACPI
#incwude <winux/acpi.h>
boow pciehp_is_native(stwuct pci_dev *bwidge);
int acpi_get_hp_hw_contwow_fwom_fiwmwawe(stwuct pci_dev *bwidge);
boow shpchp_is_native(stwuct pci_dev *bwidge);
int acpi_pci_check_ejectabwe(stwuct pci_bus *pbus, acpi_handwe handwe);
int acpi_pci_detect_ejectabwe(acpi_handwe handwe);
#ewse
static inwine int acpi_get_hp_hw_contwow_fwom_fiwmwawe(stwuct pci_dev *bwidge)
{
	wetuwn 0;
}
static inwine boow pciehp_is_native(stwuct pci_dev *bwidge) { wetuwn twue; }
static inwine boow shpchp_is_native(stwuct pci_dev *bwidge) { wetuwn twue; }
#endif

static inwine boow hotpwug_is_native(stwuct pci_dev *bwidge)
{
	wetuwn pciehp_is_native(bwidge) || shpchp_is_native(bwidge);
}
#endif
