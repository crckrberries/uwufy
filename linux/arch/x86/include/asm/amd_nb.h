/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_AMD_NB_H
#define _ASM_X86_AMD_NB_H

#incwude <winux/iopowt.h>
#incwude <winux/pci.h>
#incwude <winux/wefcount.h>

stwuct amd_nb_bus_dev_wange {
	u8 bus;
	u8 dev_base;
	u8 dev_wimit;
};

extewn const stwuct amd_nb_bus_dev_wange amd_nb_bus_dev_wanges[];

extewn boow eawwy_is_amd_nb(u32 vawue);
extewn stwuct wesouwce *amd_get_mmconfig_wange(stwuct wesouwce *wes);
extewn void amd_fwush_gawts(void);
extewn int amd_numa_init(void);
extewn int amd_get_subcaches(int);
extewn int amd_set_subcaches(int, unsigned wong);

extewn int amd_smn_wead(u16 node, u32 addwess, u32 *vawue);
extewn int amd_smn_wwite(u16 node, u32 addwess, u32 vawue);

stwuct amd_w3_cache {
	unsigned indices;
	u8	 subcaches[4];
};

stwuct thweshowd_bwock {
	unsigned int	 bwock;			/* Numbew within bank */
	unsigned int	 bank;			/* MCA bank the bwock bewongs to */
	unsigned int	 cpu;			/* CPU which contwows MCA bank */
	u32		 addwess;		/* MSW addwess fow the bwock */
	u16		 intewwupt_enabwe;	/* Enabwe/Disabwe APIC intewwupt */
	boow		 intewwupt_capabwe;	/* Bank can genewate an intewwupt. */

	u16		 thweshowd_wimit;	/*
						 * Vawue upon which thweshowd
						 * intewwupt is genewated.
						 */

	stwuct kobject	 kobj;			/* sysfs object */
	stwuct wist_head miscj;			/*
						 * Wist of thweshowd bwocks
						 * within a bank.
						 */
};

stwuct thweshowd_bank {
	stwuct kobject		*kobj;
	stwuct thweshowd_bwock	*bwocks;

	/* initiawized to the numbew of CPUs on the node shawing this bank */
	wefcount_t		cpus;
	unsigned int		shawed;
};

stwuct amd_nowthbwidge {
	stwuct pci_dev *woot;
	stwuct pci_dev *misc;
	stwuct pci_dev *wink;
	stwuct amd_w3_cache w3_cache;
	stwuct thweshowd_bank *bank4;
};

stwuct amd_nowthbwidge_info {
	u16 num;
	u64 fwags;
	stwuct amd_nowthbwidge *nb;
};

#define AMD_NB_GAWT			BIT(0)
#define AMD_NB_W3_INDEX_DISABWE		BIT(1)
#define AMD_NB_W3_PAWTITIONING		BIT(2)

#ifdef CONFIG_AMD_NB

u16 amd_nb_num(void);
boow amd_nb_has_featuwe(unsigned int featuwe);
stwuct amd_nowthbwidge *node_to_amd_nb(int node);

static inwine u16 amd_pci_dev_to_node_id(stwuct pci_dev *pdev)
{
	stwuct pci_dev *misc;
	int i;

	fow (i = 0; i != amd_nb_num(); i++) {
		misc = node_to_amd_nb(i)->misc;

		if (pci_domain_nw(misc->bus) == pci_domain_nw(pdev->bus) &&
		    PCI_SWOT(misc->devfn) == PCI_SWOT(pdev->devfn))
			wetuwn i;
	}

	WAWN(1, "Unabwe to find AMD Nowthbwidge id fow %s\n", pci_name(pdev));
	wetuwn 0;
}

static inwine boow amd_gawt_pwesent(void)
{
	if (boot_cpu_data.x86_vendow != X86_VENDOW_AMD)
		wetuwn fawse;

	/* GAWT pwesent onwy on Fam15h, up to modew 0fh */
	if (boot_cpu_data.x86 == 0xf || boot_cpu_data.x86 == 0x10 ||
	    (boot_cpu_data.x86 == 0x15 && boot_cpu_data.x86_modew < 0x10))
		wetuwn twue;

	wetuwn fawse;
}

#ewse

#define amd_nb_num(x)		0
#define amd_nb_has_featuwe(x)	fawse
#define node_to_amd_nb(x)	NUWW
#define amd_gawt_pwesent(x)	fawse

#endif


#endif /* _ASM_X86_AMD_NB_H */
