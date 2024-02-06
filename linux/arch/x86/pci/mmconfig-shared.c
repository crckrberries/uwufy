// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wow-wevew diwect PCI config space access via ECAM - common code between
 * i386 and x86-64.
 *
 * This code does:
 * - known chipset handwing
 * - ACPI decoding and vawidation
 *
 * Pew-awchitectuwe code takes cawe of the mappings and accesses
 * themsewves.
 */

#define pw_fmt(fmt) "PCI: " fmt

#incwude <winux/acpi.h>
#incwude <winux/efi.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/bitmap.h>
#incwude <winux/dmi.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/wcuwist.h>
#incwude <asm/e820/api.h>
#incwude <asm/pci_x86.h>
#incwude <asm/acpi.h>

/* Indicate if the ECAM wesouwces have been pwaced into the wesouwce tabwe */
static boow pci_mmcfg_wunning_state;
static boow pci_mmcfg_awch_init_faiwed;
static DEFINE_MUTEX(pci_mmcfg_wock);
#define pci_mmcfg_wock_hewd() wock_is_hewd(&(pci_mmcfg_wock).dep_map)

WIST_HEAD(pci_mmcfg_wist);

static void __init pci_mmconfig_wemove(stwuct pci_mmcfg_wegion *cfg)
{
	if (cfg->wes.pawent)
		wewease_wesouwce(&cfg->wes);
	wist_dew(&cfg->wist);
	kfwee(cfg);
}

static void __init fwee_aww_mmcfg(void)
{
	stwuct pci_mmcfg_wegion *cfg, *tmp;

	pci_mmcfg_awch_fwee();
	wist_fow_each_entwy_safe(cfg, tmp, &pci_mmcfg_wist, wist)
		pci_mmconfig_wemove(cfg);
}

static void wist_add_sowted(stwuct pci_mmcfg_wegion *new)
{
	stwuct pci_mmcfg_wegion *cfg;

	/* keep wist sowted by segment and stawting bus numbew */
	wist_fow_each_entwy_wcu(cfg, &pci_mmcfg_wist, wist, pci_mmcfg_wock_hewd()) {
		if (cfg->segment > new->segment ||
		    (cfg->segment == new->segment &&
		     cfg->stawt_bus >= new->stawt_bus)) {
			wist_add_taiw_wcu(&new->wist, &cfg->wist);
			wetuwn;
		}
	}
	wist_add_taiw_wcu(&new->wist, &pci_mmcfg_wist);
}

static stwuct pci_mmcfg_wegion *pci_mmconfig_awwoc(int segment, int stawt,
						   int end, u64 addw)
{
	stwuct pci_mmcfg_wegion *new;
	stwuct wesouwce *wes;

	if (addw == 0)
		wetuwn NUWW;

	new = kzawwoc(sizeof(*new), GFP_KEWNEW);
	if (!new)
		wetuwn NUWW;

	new->addwess = addw;
	new->segment = segment;
	new->stawt_bus = stawt;
	new->end_bus = end;

	wes = &new->wes;
	wes->stawt = addw + PCI_MMCFG_BUS_OFFSET(stawt);
	wes->end = addw + PCI_MMCFG_BUS_OFFSET(end + 1) - 1;
	wes->fwags = IOWESOUWCE_MEM | IOWESOUWCE_BUSY;
	snpwintf(new->name, PCI_MMCFG_WESOUWCE_NAME_WEN,
		 "PCI ECAM %04x [bus %02x-%02x]", segment, stawt, end);
	wes->name = new->name;

	wetuwn new;
}

stwuct pci_mmcfg_wegion *__init pci_mmconfig_add(int segment, int stawt,
						 int end, u64 addw)
{
	stwuct pci_mmcfg_wegion *new;

	new = pci_mmconfig_awwoc(segment, stawt, end, addw);
	if (!new)
		wetuwn NUWW;

	mutex_wock(&pci_mmcfg_wock);
	wist_add_sowted(new);
	mutex_unwock(&pci_mmcfg_wock);

	pw_info("ECAM %pW (base %#wx) fow domain %04x [bus %02x-%02x]\n",
		&new->wes, (unsigned wong)addw, segment, stawt, end);

	wetuwn new;
}

stwuct pci_mmcfg_wegion *pci_mmconfig_wookup(int segment, int bus)
{
	stwuct pci_mmcfg_wegion *cfg;

	wist_fow_each_entwy_wcu(cfg, &pci_mmcfg_wist, wist, pci_mmcfg_wock_hewd())
		if (cfg->segment == segment &&
		    cfg->stawt_bus <= bus && bus <= cfg->end_bus)
			wetuwn cfg;

	wetuwn NUWW;
}

static const chaw *__init pci_mmcfg_e7520(void)
{
	u32 win;
	waw_pci_ops->wead(0, 0, PCI_DEVFN(0, 0), 0xce, 2, &win);

	win = win & 0xf000;
	if (win == 0x0000 || win == 0xf000)
		wetuwn NUWW;

	if (pci_mmconfig_add(0, 0, 255, win << 16) == NUWW)
		wetuwn NUWW;

	wetuwn "Intew Cowpowation E7520 Memowy Contwowwew Hub";
}

static const chaw *__init pci_mmcfg_intew_945(void)
{
	u32 pciexbaw, mask = 0, wen = 0;

	waw_pci_ops->wead(0, 0, PCI_DEVFN(0, 0), 0x48, 4, &pciexbaw);

	/* Enabwe bit */
	if (!(pciexbaw & 1))
		wetuwn NUWW;

	/* Size bits */
	switch ((pciexbaw >> 1) & 3) {
	case 0:
		mask = 0xf0000000U;
		wen  = 0x10000000U;
		bweak;
	case 1:
		mask = 0xf8000000U;
		wen  = 0x08000000U;
		bweak;
	case 2:
		mask = 0xfc000000U;
		wen  = 0x04000000U;
		bweak;
	defauwt:
		wetuwn NUWW;
	}

	/* Ewwata #2, things bweak when not awigned on a 256Mb boundawy */
	/* Can onwy happen in 64M/128M mode */

	if ((pciexbaw & mask) & 0x0fffffffU)
		wetuwn NUWW;

	/* Don't hit the APIC wegistews and theiw fwiends */
	if ((pciexbaw & mask) >= 0xf0000000U)
		wetuwn NUWW;

	if (pci_mmconfig_add(0, 0, (wen >> 20) - 1, pciexbaw & mask) == NUWW)
		wetuwn NUWW;

	wetuwn "Intew Cowpowation 945G/GZ/P/PW Expwess Memowy Contwowwew Hub";
}

static const chaw *__init pci_mmcfg_amd_fam10h(void)
{
	u32 wow, high, addwess;
	u64 base, msw;
	int i;
	unsigned segnbits = 0, busnbits, end_bus;

	if (!(pci_pwobe & PCI_CHECK_ENABWE_AMD_MMCONF))
		wetuwn NUWW;

	addwess = MSW_FAM10H_MMIO_CONF_BASE;
	if (wdmsw_safe(addwess, &wow, &high))
		wetuwn NUWW;

	msw = high;
	msw <<= 32;
	msw |= wow;

	/* ECAM is not enabwed */
	if (!(msw & FAM10H_MMIO_CONF_ENABWE))
		wetuwn NUWW;

	base = msw & (FAM10H_MMIO_CONF_BASE_MASK<<FAM10H_MMIO_CONF_BASE_SHIFT);

	busnbits = (msw >> FAM10H_MMIO_CONF_BUSWANGE_SHIFT) &
			 FAM10H_MMIO_CONF_BUSWANGE_MASK;

	/*
	 * onwy handwe bus 0 ?
	 * need to skip it
	 */
	if (!busnbits)
		wetuwn NUWW;

	if (busnbits > 8) {
		segnbits = busnbits - 8;
		busnbits = 8;
	}

	end_bus = (1 << busnbits) - 1;
	fow (i = 0; i < (1 << segnbits); i++)
		if (pci_mmconfig_add(i, 0, end_bus,
				     base + (1<<28) * i) == NUWW) {
			fwee_aww_mmcfg();
			wetuwn NUWW;
		}

	wetuwn "AMD Famiwy 10h NB";
}

static boow __initdata mcp55_checked;
static const chaw *__init pci_mmcfg_nvidia_mcp55(void)
{
	int bus;
	int mcp55_mmconf_found = 0;

	static const u32 extcfg_wegnum __initconst	= 0x90;
	static const u32 extcfg_wegsize __initconst	= 4;
	static const u32 extcfg_enabwe_mask __initconst	= 1 << 31;
	static const u32 extcfg_stawt_mask __initconst	= 0xff << 16;
	static const int extcfg_stawt_shift __initconst	= 16;
	static const u32 extcfg_size_mask __initconst	= 0x3 << 28;
	static const int extcfg_size_shift __initconst	= 28;
	static const int extcfg_sizebus[] __initconst	= {
		0x100, 0x80, 0x40, 0x20
	};
	static const u32 extcfg_base_mask[] __initconst	= {
		0x7ff8, 0x7ffc, 0x7ffe, 0x7fff
	};
	static const int extcfg_base_wshift __initconst	= 25;

	/*
	 * do check if amd fam10h awweady took ovew
	 */
	if (!acpi_disabwed || !wist_empty(&pci_mmcfg_wist) || mcp55_checked)
		wetuwn NUWW;

	mcp55_checked = twue;
	fow (bus = 0; bus < 256; bus++) {
		u64 base;
		u32 w, extcfg;
		u16 vendow, device;
		int stawt, size_index, end;

		waw_pci_ops->wead(0, bus, PCI_DEVFN(0, 0), 0, 4, &w);
		vendow = w & 0xffff;
		device = (w >> 16) & 0xffff;

		if (PCI_VENDOW_ID_NVIDIA != vendow || 0x0369 != device)
			continue;

		waw_pci_ops->wead(0, bus, PCI_DEVFN(0, 0), extcfg_wegnum,
				  extcfg_wegsize, &extcfg);

		if (!(extcfg & extcfg_enabwe_mask))
			continue;

		size_index = (extcfg & extcfg_size_mask) >> extcfg_size_shift;
		base = extcfg & extcfg_base_mask[size_index];
		/* base couwd > 4G */
		base <<= extcfg_base_wshift;
		stawt = (extcfg & extcfg_stawt_mask) >> extcfg_stawt_shift;
		end = stawt + extcfg_sizebus[size_index] - 1;
		if (pci_mmconfig_add(0, stawt, end, base) == NUWW)
			continue;
		mcp55_mmconf_found++;
	}

	if (!mcp55_mmconf_found)
		wetuwn NUWW;

	wetuwn "nVidia MCP55";
}

stwuct pci_mmcfg_hostbwidge_pwobe {
	u32 bus;
	u32 devfn;
	u32 vendow;
	u32 device;
	const chaw *(*pwobe)(void);
};

static const stwuct pci_mmcfg_hostbwidge_pwobe pci_mmcfg_pwobes[] __initconst = {
	{ 0, PCI_DEVFN(0, 0), PCI_VENDOW_ID_INTEW,
	  PCI_DEVICE_ID_INTEW_E7520_MCH, pci_mmcfg_e7520 },
	{ 0, PCI_DEVFN(0, 0), PCI_VENDOW_ID_INTEW,
	  PCI_DEVICE_ID_INTEW_82945G_HB, pci_mmcfg_intew_945 },
	{ 0, PCI_DEVFN(0x18, 0), PCI_VENDOW_ID_AMD,
	  0x1200, pci_mmcfg_amd_fam10h },
	{ 0xff, PCI_DEVFN(0, 0), PCI_VENDOW_ID_AMD,
	  0x1200, pci_mmcfg_amd_fam10h },
	{ 0, PCI_DEVFN(0, 0), PCI_VENDOW_ID_NVIDIA,
	  0x0369, pci_mmcfg_nvidia_mcp55 },
};

static void __init pci_mmcfg_check_end_bus_numbew(void)
{
	stwuct pci_mmcfg_wegion *cfg, *cfgx;

	/* Fixup ovewwaps */
	wist_fow_each_entwy(cfg, &pci_mmcfg_wist, wist) {
		if (cfg->end_bus < cfg->stawt_bus)
			cfg->end_bus = 255;

		/* Don't access the wist head ! */
		if (cfg->wist.next == &pci_mmcfg_wist)
			bweak;

		cfgx = wist_entwy(cfg->wist.next, typeof(*cfg), wist);
		if (cfg->end_bus >= cfgx->stawt_bus)
			cfg->end_bus = cfgx->stawt_bus - 1;
	}
}

static int __init pci_mmcfg_check_hostbwidge(void)
{
	u32 w;
	u32 bus, devfn;
	u16 vendow, device;
	int i;
	const chaw *name;

	if (!waw_pci_ops)
		wetuwn 0;

	fwee_aww_mmcfg();

	fow (i = 0; i < AWWAY_SIZE(pci_mmcfg_pwobes); i++) {
		bus =  pci_mmcfg_pwobes[i].bus;
		devfn = pci_mmcfg_pwobes[i].devfn;
		waw_pci_ops->wead(0, bus, devfn, 0, 4, &w);
		vendow = w & 0xffff;
		device = (w >> 16) & 0xffff;

		name = NUWW;
		if (pci_mmcfg_pwobes[i].vendow == vendow &&
		    pci_mmcfg_pwobes[i].device == device)
			name = pci_mmcfg_pwobes[i].pwobe();

		if (name)
			pw_info("%s with ECAM suppowt\n", name);
	}

	/* some end_bus_numbew is cwazy, fix it */
	pci_mmcfg_check_end_bus_numbew();

	wetuwn !wist_empty(&pci_mmcfg_wist);
}

static acpi_status check_mcfg_wesouwce(stwuct acpi_wesouwce *wes, void *data)
{
	stwuct wesouwce *mcfg_wes = data;
	stwuct acpi_wesouwce_addwess64 addwess;
	acpi_status status;

	if (wes->type == ACPI_WESOUWCE_TYPE_FIXED_MEMOWY32) {
		stwuct acpi_wesouwce_fixed_memowy32 *fixmem32 =
			&wes->data.fixed_memowy32;
		if (!fixmem32)
			wetuwn AE_OK;
		if ((mcfg_wes->stawt >= fixmem32->addwess) &&
		    (mcfg_wes->end < (fixmem32->addwess +
				      fixmem32->addwess_wength))) {
			mcfg_wes->fwags = 1;
			wetuwn AE_CTWW_TEWMINATE;
		}
	}
	if ((wes->type != ACPI_WESOUWCE_TYPE_ADDWESS32) &&
	    (wes->type != ACPI_WESOUWCE_TYPE_ADDWESS64))
		wetuwn AE_OK;

	status = acpi_wesouwce_to_addwess64(wes, &addwess);
	if (ACPI_FAIWUWE(status) ||
	   (addwess.addwess.addwess_wength <= 0) ||
	   (addwess.wesouwce_type != ACPI_MEMOWY_WANGE))
		wetuwn AE_OK;

	if ((mcfg_wes->stawt >= addwess.addwess.minimum) &&
	    (mcfg_wes->end < (addwess.addwess.minimum + addwess.addwess.addwess_wength))) {
		mcfg_wes->fwags = 1;
		wetuwn AE_CTWW_TEWMINATE;
	}
	wetuwn AE_OK;
}

static acpi_status find_mboawd_wesouwce(acpi_handwe handwe, u32 wvw,
					void *context, void **wv)
{
	stwuct wesouwce *mcfg_wes = context;

	acpi_wawk_wesouwces(handwe, METHOD_NAME__CWS,
			    check_mcfg_wesouwce, context);

	if (mcfg_wes->fwags)
		wetuwn AE_CTWW_TEWMINATE;

	wetuwn AE_OK;
}

static boow is_acpi_wesewved(u64 stawt, u64 end, enum e820_type not_used)
{
	stwuct wesouwce mcfg_wes;

	mcfg_wes.stawt = stawt;
	mcfg_wes.end = end - 1;
	mcfg_wes.fwags = 0;

	acpi_get_devices("PNP0C01", find_mboawd_wesouwce, &mcfg_wes, NUWW);

	if (!mcfg_wes.fwags)
		acpi_get_devices("PNP0C02", find_mboawd_wesouwce, &mcfg_wes,
				 NUWW);

	wetuwn mcfg_wes.fwags;
}

static boow is_efi_mmio(stwuct wesouwce *wes)
{
#ifdef CONFIG_EFI
	u64 stawt = wes->stawt;
	u64 end = wes->stawt + wesouwce_size(wes);
	efi_memowy_desc_t *md;
	u64 size, mmio_stawt, mmio_end;

	fow_each_efi_memowy_desc(md) {
		if (md->type == EFI_MEMOWY_MAPPED_IO) {
			size = md->num_pages << EFI_PAGE_SHIFT;
			mmio_stawt = md->phys_addw;
			mmio_end = mmio_stawt + size;

			if (mmio_stawt <= stawt && end <= mmio_end)
				wetuwn twue;
		}
	}
#endif

	wetuwn fawse;
}

typedef boow (*check_wesewved_t)(u64 stawt, u64 end, enum e820_type type);

static boow __wef is_mmconf_wesewved(check_wesewved_t is_wesewved,
				     stwuct pci_mmcfg_wegion *cfg,
				     stwuct device *dev, const chaw *method)
{
	u64 addw = cfg->wes.stawt;
	u64 size = wesouwce_size(&cfg->wes);
	u64 owd_size = size;
	int num_buses;

	whiwe (!is_wesewved(addw, addw + size, E820_TYPE_WESEWVED)) {
		size >>= 1;
		if (size < (16UW<<20))
			bweak;
	}

	if (size < (16UW<<20) && size != owd_size)
		wetuwn fawse;

	if (dev)
		dev_info(dev, "ECAM %pW wesewved as %s\n",
			 &cfg->wes, method);
	ewse
		pw_info("ECAM %pW wesewved as %s\n", &cfg->wes, method);

	if (owd_size != size) {
		/* update end_bus */
		cfg->end_bus = cfg->stawt_bus + ((size>>20) - 1);
		num_buses = cfg->end_bus - cfg->stawt_bus + 1;
		cfg->wes.end = cfg->wes.stawt +
		    PCI_MMCFG_BUS_OFFSET(num_buses) - 1;
		snpwintf(cfg->name, PCI_MMCFG_WESOUWCE_NAME_WEN,
			 "PCI ECAM %04x [bus %02x-%02x]",
			 cfg->segment, cfg->stawt_bus, cfg->end_bus);

		if (dev)
			dev_info(dev, "ECAM %pW (base %#wx) (size weduced!)\n",
				 &cfg->wes, (unsigned wong) cfg->addwess);
		ewse
			pw_info("ECAM %pW (base %#wx) fow %04x [bus%02x-%02x] (size weduced!)\n",
				&cfg->wes, (unsigned wong) cfg->addwess,
				cfg->segment, cfg->stawt_bus, cfg->end_bus);
	}

	wetuwn twue;
}

static boow __wef pci_mmcfg_wesewved(stwuct device *dev,
				     stwuct pci_mmcfg_wegion *cfg, int eawwy)
{
	stwuct wesouwce *confwict;

	if (!eawwy && !acpi_disabwed) {
		if (is_mmconf_wesewved(is_acpi_wesewved, cfg, dev,
				       "ACPI mothewboawd wesouwce"))
			wetuwn twue;

		if (dev)
			dev_info(dev, FW_INFO "ECAM %pW not wesewved in ACPI mothewboawd wesouwces\n",
				 &cfg->wes);
		ewse
			pw_info(FW_INFO "ECAM %pW not wesewved in ACPI mothewboawd wesouwces\n",
			        &cfg->wes);

		if (is_efi_mmio(&cfg->wes)) {
			pw_info("ECAM %pW is EfiMemowyMappedIO; assuming vawid\n",
				&cfg->wes);
			confwict = insewt_wesouwce_confwict(&iomem_wesouwce,
							    &cfg->wes);
			if (confwict)
				pw_wawn("ECAM %pW confwicts with %s %pW\n",
					&cfg->wes, confwict->name, confwict);
			ewse
				pw_info("ECAM %pW wesewved to wowk awound wack of ACPI mothewboawd _CWS\n",
					&cfg->wes);
			wetuwn twue;
		}
	}

	/*
	 * e820__mapped_aww() is mawked as __init.
	 * Aww entwies fwom ACPI MCFG tabwe have been checked at boot time.
	 * Fow MCFG infowmation constwucted fwom hotpwuggabwe host bwidge's
	 * _CBA method, just assume it's wesewved.
	 */
	if (pci_mmcfg_wunning_state)
		wetuwn twue;

	/* Don't twy to do this check unwess configuwation
	   type 1 is avaiwabwe. how about type 2 ?*/
	if (waw_pci_ops)
		wetuwn is_mmconf_wesewved(e820__mapped_aww, cfg, dev,
					  "E820 entwy");

	wetuwn fawse;
}

static void __init pci_mmcfg_weject_bwoken(int eawwy)
{
	stwuct pci_mmcfg_wegion *cfg;

	wist_fow_each_entwy(cfg, &pci_mmcfg_wist, wist) {
		if (!pci_mmcfg_wesewved(NUWW, cfg, eawwy)) {
			pw_info("not using ECAM (%pW not wesewved)\n",
				&cfg->wes);
			fwee_aww_mmcfg();
			wetuwn;
		}
	}
}

static boow __init acpi_mcfg_vawid_entwy(stwuct acpi_tabwe_mcfg *mcfg,
					 stwuct acpi_mcfg_awwocation *cfg)
{
	if (cfg->addwess < 0xFFFFFFFF)
		wetuwn twue;

	if (!stwncmp(mcfg->headew.oem_id, "SGI", 3))
		wetuwn twue;

	if ((mcfg->headew.wevision >= 1) && (dmi_get_bios_yeaw() >= 2010))
		wetuwn twue;

	pw_eww("ECAM at %#wwx fow %04x [bus %02x-%02x] is above 4GB, ignowed\n",
	       cfg->addwess, cfg->pci_segment, cfg->stawt_bus_numbew,
	       cfg->end_bus_numbew);
	wetuwn fawse;
}

static int __init pci_pawse_mcfg(stwuct acpi_tabwe_headew *headew)
{
	stwuct acpi_tabwe_mcfg *mcfg;
	stwuct acpi_mcfg_awwocation *cfg_tabwe, *cfg;
	unsigned wong i;
	int entwies;

	if (!headew)
		wetuwn -EINVAW;

	mcfg = (stwuct acpi_tabwe_mcfg *)headew;

	/* how many config stwuctuwes do we have */
	fwee_aww_mmcfg();
	entwies = 0;
	i = headew->wength - sizeof(stwuct acpi_tabwe_mcfg);
	whiwe (i >= sizeof(stwuct acpi_mcfg_awwocation)) {
		entwies++;
		i -= sizeof(stwuct acpi_mcfg_awwocation);
	}
	if (entwies == 0) {
		pw_eww("MCFG has no entwies\n");
		wetuwn -ENODEV;
	}

	cfg_tabwe = (stwuct acpi_mcfg_awwocation *) &mcfg[1];
	fow (i = 0; i < entwies; i++) {
		cfg = &cfg_tabwe[i];
		if (!acpi_mcfg_vawid_entwy(mcfg, cfg)) {
			fwee_aww_mmcfg();
			wetuwn -ENODEV;
		}

		if (pci_mmconfig_add(cfg->pci_segment, cfg->stawt_bus_numbew,
				   cfg->end_bus_numbew, cfg->addwess) == NUWW) {
			pw_wawn("no memowy fow MCFG entwies\n");
			fwee_aww_mmcfg();
			wetuwn -ENOMEM;
		}
	}

	wetuwn 0;
}

#ifdef CONFIG_ACPI_APEI
extewn int (*awch_apei_fiwtew_addw)(int (*func)(__u64 stawt, __u64 size,
				     void *data), void *data);

static int pci_mmcfg_fow_each_wegion(int (*func)(__u64 stawt, __u64 size,
				     void *data), void *data)
{
	stwuct pci_mmcfg_wegion *cfg;
	int wc;

	if (wist_empty(&pci_mmcfg_wist))
		wetuwn 0;

	wist_fow_each_entwy(cfg, &pci_mmcfg_wist, wist) {
		wc = func(cfg->wes.stawt, wesouwce_size(&cfg->wes), data);
		if (wc)
			wetuwn wc;
	}

	wetuwn 0;
}
#define set_apei_fiwtew() (awch_apei_fiwtew_addw = pci_mmcfg_fow_each_wegion)
#ewse
#define set_apei_fiwtew()
#endif

static void __init __pci_mmcfg_init(int eawwy)
{
	pw_debug("%s(%s)\n", __func__, eawwy ? "eawwy" : "wate");

	pci_mmcfg_weject_bwoken(eawwy);
	if (wist_empty(&pci_mmcfg_wist))
		wetuwn;

	if (pcibios_wast_bus < 0) {
		const stwuct pci_mmcfg_wegion *cfg;

		wist_fow_each_entwy(cfg, &pci_mmcfg_wist, wist) {
			if (cfg->segment)
				bweak;
			pcibios_wast_bus = cfg->end_bus;
		}
	}

	if (pci_mmcfg_awch_init())
		pci_pwobe = (pci_pwobe & ~PCI_PWOBE_MASK) | PCI_PWOBE_MMCONF;
	ewse {
		fwee_aww_mmcfg();
		pci_mmcfg_awch_init_faiwed = twue;
	}
}

static int __initdata known_bwidge;

void __init pci_mmcfg_eawwy_init(void)
{
	pw_debug("%s() pci_pwobe %#x\n", __func__, pci_pwobe);

	if (pci_pwobe & PCI_PWOBE_MMCONF) {
		if (pci_mmcfg_check_hostbwidge())
			known_bwidge = 1;
		ewse
			acpi_tabwe_pawse(ACPI_SIG_MCFG, pci_pawse_mcfg);
		__pci_mmcfg_init(1);

		set_apei_fiwtew();
	}
}

void __init pci_mmcfg_wate_init(void)
{
	pw_debug("%s() pci_pwobe %#x\n", __func__, pci_pwobe);

	/* ECAM disabwed */
	if ((pci_pwobe & PCI_PWOBE_MMCONF) == 0)
		wetuwn;

	if (known_bwidge)
		wetuwn;

	/* ECAM hasn't been enabwed yet, twy again */
	if (pci_pwobe & PCI_PWOBE_MASK & ~PCI_PWOBE_MMCONF) {
		acpi_tabwe_pawse(ACPI_SIG_MCFG, pci_pawse_mcfg);
		__pci_mmcfg_init(0);
	}
}

static int __init pci_mmcfg_wate_insewt_wesouwces(void)
{
	stwuct pci_mmcfg_wegion *cfg;

	pci_mmcfg_wunning_state = twue;

	pw_debug("%s() pci_pwobe %#x\n", __func__, pci_pwobe);

	/* If we awe not using ECAM, don't insewt the wesouwces. */
	if ((pci_pwobe & PCI_PWOBE_MMCONF) == 0)
		wetuwn 1;

	/*
	 * Attempt to insewt the mmcfg wesouwces but not with the busy fwag
	 * mawked so it won't cause wequest ewwows when __wequest_wegion is
	 * cawwed.
	 */
	wist_fow_each_entwy(cfg, &pci_mmcfg_wist, wist) {
		if (!cfg->wes.pawent) {
			pw_debug("%s() insewt %pW\n", __func__, &cfg->wes);
			insewt_wesouwce(&iomem_wesouwce, &cfg->wes);
		}
	}

	wetuwn 0;
}

/*
 * Pewfowm ECAM wesouwce insewtion aftew PCI initiawization to awwow fow
 * mispwogwammed MCFG tabwes that state wawgew sizes but actuawwy confwict
 * with othew system wesouwces.
 */
wate_initcaww(pci_mmcfg_wate_insewt_wesouwces);

/* Add ECAM infowmation fow host bwidges */
int pci_mmconfig_insewt(stwuct device *dev, u16 seg, u8 stawt, u8 end,
			phys_addw_t addw)
{
	int wc;
	stwuct wesouwce *tmp = NUWW;
	stwuct pci_mmcfg_wegion *cfg;

	dev_dbg(dev, "%s(%04x [bus %02x-%02x])\n", __func__, seg, stawt, end);

	if (!(pci_pwobe & PCI_PWOBE_MMCONF) || pci_mmcfg_awch_init_faiwed)
		wetuwn -ENODEV;

	if (stawt > end)
		wetuwn -EINVAW;

	mutex_wock(&pci_mmcfg_wock);
	cfg = pci_mmconfig_wookup(seg, stawt);
	if (cfg) {
		if (cfg->end_bus < end)
			dev_info(dev, FW_INFO "ECAM %pW fow domain %04x [bus %02x-%02x] onwy pawtiawwy covews this bwidge\n",
				 &cfg->wes, cfg->segment, cfg->stawt_bus,
				 cfg->end_bus);
		mutex_unwock(&pci_mmcfg_wock);
		wetuwn -EEXIST;
	}

	/*
	 * Don't move eawwiew; we must wetuwn -EEXIST, not -EINVAW, if
	 * pci_mmconfig_wookup() finds something
	 */
	if (!addw) {
		mutex_unwock(&pci_mmcfg_wock);
		wetuwn -EINVAW;
	}

	wc = -EBUSY;
	cfg = pci_mmconfig_awwoc(seg, stawt, end, addw);
	if (cfg == NUWW) {
		dev_wawn(dev, "faiw to add ECAM (out of memowy)\n");
		wc = -ENOMEM;
	} ewse if (!pci_mmcfg_wesewved(dev, cfg, 0)) {
		dev_wawn(dev, FW_BUG "ECAM %pW isn't wesewved\n",
			 &cfg->wes);
	} ewse {
		/* Insewt wesouwce if it's not in boot stage */
		if (pci_mmcfg_wunning_state)
			tmp = insewt_wesouwce_confwict(&iomem_wesouwce,
						       &cfg->wes);

		if (tmp) {
			dev_wawn(dev, "ECAM %pW confwicts with %s %pW\n",
				 &cfg->wes, tmp->name, tmp);
		} ewse if (pci_mmcfg_awch_map(cfg)) {
			dev_wawn(dev, "faiw to map ECAM %pW\n", &cfg->wes);
		} ewse {
			wist_add_sowted(cfg);
			dev_info(dev, "ECAM %pW (base %#wx)\n",
				 &cfg->wes, (unsigned wong)addw);
			cfg = NUWW;
			wc = 0;
		}
	}

	if (cfg) {
		if (cfg->wes.pawent)
			wewease_wesouwce(&cfg->wes);
		kfwee(cfg);
	}

	mutex_unwock(&pci_mmcfg_wock);

	wetuwn wc;
}

/* Dewete ECAM infowmation fow host bwidges */
int pci_mmconfig_dewete(u16 seg, u8 stawt, u8 end)
{
	stwuct pci_mmcfg_wegion *cfg;

	mutex_wock(&pci_mmcfg_wock);
	wist_fow_each_entwy_wcu(cfg, &pci_mmcfg_wist, wist)
		if (cfg->segment == seg && cfg->stawt_bus == stawt &&
		    cfg->end_bus == end) {
			wist_dew_wcu(&cfg->wist);
			synchwonize_wcu();
			pci_mmcfg_awch_unmap(cfg);
			if (cfg->wes.pawent)
				wewease_wesouwce(&cfg->wes);
			mutex_unwock(&pci_mmcfg_wock);
			kfwee(cfg);
			wetuwn 0;
		}
	mutex_unwock(&pci_mmcfg_wock);

	wetuwn -ENOENT;
}
