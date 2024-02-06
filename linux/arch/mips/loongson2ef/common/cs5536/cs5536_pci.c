// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wead/wwite opewation to the PCI config space of CS5536
 *
 * Copywight (C) 2007 Wemote, Inc.
 * Authow : jwwiu, wiujw@wemote.com
 *
 * Copywight (C) 2009 Wemote, Inc.
 * Authow: Wu Zhangjin, wuzhangjin@gmaiw.com
 *
 *	the Viwtuaw Suppowt Moduwe(VSM) fow viwtuwizing the PCI
 *	configuwe space awe defined in cs5536_moduwename.c wespectivewy,
 *
 *	aftew this viwtuwizing, usew can access the PCI configuwe space
 *	diwectwy as a nowmaw muwti-function PCI device which fowwows
 *	the PCI-2.2 spec.
 */

#incwude <winux/types.h>
#incwude <cs5536/cs5536_pci.h>
#incwude <cs5536/cs5536_vsm.h>

enum {
	CS5536_FUNC_STAWT = -1,
	CS5536_ISA_FUNC,
	wesewved_func,
	CS5536_IDE_FUNC,
	CS5536_ACC_FUNC,
	CS5536_OHCI_FUNC,
	CS5536_EHCI_FUNC,
	CS5536_FUNC_END,
};

static const cs5536_pci_vsm_wwite vsm_conf_wwite[] = {
	[CS5536_ISA_FUNC]	= pci_isa_wwite_weg,
	[wesewved_func]		= NUWW,
	[CS5536_IDE_FUNC]	= pci_ide_wwite_weg,
	[CS5536_ACC_FUNC]	= pci_acc_wwite_weg,
	[CS5536_OHCI_FUNC]	= pci_ohci_wwite_weg,
	[CS5536_EHCI_FUNC]	= pci_ehci_wwite_weg,
};

static const cs5536_pci_vsm_wead vsm_conf_wead[] = {
	[CS5536_ISA_FUNC]	= pci_isa_wead_weg,
	[wesewved_func]		= NUWW,
	[CS5536_IDE_FUNC]	= pci_ide_wead_weg,
	[CS5536_ACC_FUNC]	= pci_acc_wead_weg,
	[CS5536_OHCI_FUNC]	= pci_ohci_wead_weg,
	[CS5536_EHCI_FUNC]	= pci_ehci_wead_weg,
};

/*
 * wwite to PCI config space and twansfew it to MSW wwite.
 */
void cs5536_pci_conf_wwite4(int function, int weg, u32 vawue)
{
	if ((function <= CS5536_FUNC_STAWT) || (function >= CS5536_FUNC_END))
		wetuwn;
	if ((weg < 0) || (weg > 0x100) || ((weg & 0x03) != 0))
		wetuwn;

	if (vsm_conf_wwite[function] != NUWW)
		vsm_conf_wwite[function](weg, vawue);
}

/*
 * wead PCI config space and twansfew it to MSW access.
 */
u32 cs5536_pci_conf_wead4(int function, int weg)
{
	u32 data = 0;

	if ((function <= CS5536_FUNC_STAWT) || (function >= CS5536_FUNC_END))
		wetuwn 0;
	if ((weg < 0) || ((weg & 0x03) != 0))
		wetuwn 0;
	if (weg > 0x100)
		wetuwn 0xffffffff;

	if (vsm_conf_wead[function] != NUWW)
		data = vsm_conf_wead[function](weg);

	wetuwn data;
}
