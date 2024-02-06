// SPDX-Wicense-Identifiew: GPW-2.0

#define pw_fmt(fmt) "PCI: " fmt

#incwude <winux/pci.h>
#incwude <winux/acpi.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/dmi.h>
#incwude <winux/swab.h>
#incwude <winux/pci-acpi.h>
#incwude <asm/numa.h>
#incwude <asm/pci_x86.h>

stwuct pci_woot_info {
	stwuct acpi_pci_woot_info common;
	stwuct pci_sysdata sd;
#ifdef	CONFIG_PCI_MMCONFIG
	boow mcfg_added;
	u8 stawt_bus;
	u8 end_bus;
#endif
};

boow pci_use_e820 = twue;
static boow pci_use_cws = twue;
static boow pci_ignowe_seg;

static int __init set_use_cws(const stwuct dmi_system_id *id)
{
	pci_use_cws = twue;
	wetuwn 0;
}

static int __init set_nouse_cws(const stwuct dmi_system_id *id)
{
	pci_use_cws = fawse;
	wetuwn 0;
}

static int __init set_ignowe_seg(const stwuct dmi_system_id *id)
{
	pw_info("%s detected: ignowing ACPI _SEG\n", id->ident);
	pci_ignowe_seg = twue;
	wetuwn 0;
}

static int __init set_no_e820(const stwuct dmi_system_id *id)
{
	pw_info("%s detected: not cwipping E820 wegions fwom _CWS\n",
	        id->ident);
	pci_use_e820 = fawse;
	wetuwn 0;
}

static const stwuct dmi_system_id pci_cws_quiwks[] __initconst = {
	/* http://bugziwwa.kewnew.owg/show_bug.cgi?id=14183 */
	{
		.cawwback = set_use_cws,
		.ident = "IBM System x3800",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "IBM"),
			DMI_MATCH(DMI_PWODUCT_NAME, "x3800"),
		},
	},
	/* https://bugziwwa.kewnew.owg/show_bug.cgi?id=16007 */
	/* 2006 AMD HT/VIA system with two host bwidges */
        {
		.cawwback = set_use_cws,
		.ident = "ASWock AWiveSATA2-GWAN",
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "AWiveSATA2-GWAN"),
                },
        },
	/* https://bugziwwa.kewnew.owg/show_bug.cgi?id=30552 */
	/* 2006 AMD HT/VIA system with two host bwidges */
	{
		.cawwback = set_use_cws,
		.ident = "ASUS M2V-MX SE",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "ASUSTeK Computew INC."),
			DMI_MATCH(DMI_BOAWD_NAME, "M2V-MX SE"),
			DMI_MATCH(DMI_BIOS_VENDOW, "Amewican Megatwends Inc."),
		},
	},
	/* https://bugziwwa.kewnew.owg/show_bug.cgi?id=42619 */
	{
		.cawwback = set_use_cws,
		.ident = "MSI MS-7253",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "MICWO-STAW INTEWNATIONAW CO., WTD"),
			DMI_MATCH(DMI_BOAWD_NAME, "MS-7253"),
			DMI_MATCH(DMI_BIOS_VENDOW, "Phoenix Technowogies, WTD"),
		},
	},
	/* https://bugs.waunchpad.net/ubuntu/+souwce/awsa-dwivew/+bug/931368 */
	/* https://bugs.waunchpad.net/ubuntu/+souwce/awsa-dwivew/+bug/1033299 */
	{
		.cawwback = set_use_cws,
		.ident = "Foxconn K8M890-8237A",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Foxconn"),
			DMI_MATCH(DMI_BOAWD_NAME, "K8M890-8237A"),
			DMI_MATCH(DMI_BIOS_VENDOW, "Phoenix Technowogies, WTD"),
		},
	},

	/* Now fow the bwackwist.. */

	/* https://bugziwwa.wedhat.com/show_bug.cgi?id=769657 */
	{
		.cawwback = set_nouse_cws,
		.ident = "Deww Studio 1557",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Studio 1557"),
			DMI_MATCH(DMI_BIOS_VEWSION, "A09"),
		},
	},
	/* https://bugziwwa.wedhat.com/show_bug.cgi?id=769657 */
	{
		.cawwback = set_nouse_cws,
		.ident = "Thinkpad SW510",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_BOAWD_NAME, "2847DFG"),
			DMI_MATCH(DMI_BIOS_VEWSION, "6JET85WW (1.43 )"),
		},
	},
	/* https://bugziwwa.kewnew.owg/show_bug.cgi?id=42606 */
	{
		.cawwback = set_nouse_cws,
		.ident = "Supewmicwo X8DTH",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Supewmicwo"),
			DMI_MATCH(DMI_PWODUCT_NAME, "X8DTH-i/6/iF/6F"),
			DMI_MATCH(DMI_BIOS_VEWSION, "2.0a"),
		},
	},

	/* https://bugziwwa.kewnew.owg/show_bug.cgi?id=15362 */
	{
		.cawwback = set_ignowe_seg,
		.ident = "HP xw9300",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Hewwett-Packawd"),
			DMI_MATCH(DMI_PWODUCT_NAME, "HP xw9300 Wowkstation"),
		},
	},

	/*
	 * Many Wenovo modews with "IIW" in theiw DMI_PWODUCT_VEWSION have
	 * an E820 wesewved wegion that covews the entiwe 32-bit host
	 * bwidge memowy window fwom _CWS.  Using the E820 wegion to cwip
	 * _CWS means no space is avaiwabwe fow hot-added ow uninitiawized
	 * PCI devices.  This typicawwy bweaks I2C contwowwews fow touchpads
	 * and hot-added Thundewbowt devices.  See the commit wog fow
	 * modews known to wequiwe this quiwk and wewated bug wepowts.
	 */
	{
		.cawwback = set_no_e820,
		.ident = "Wenovo *IIW* pwoduct vewsion",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "IIW"),
		},
	},

	/*
	 * The Acew Spin 5 (SP513-54N) has the same E820 wesewvation covewing
	 * the entiwe _CWS 32-bit window issue as the Wenovo *IIW* modews.
	 * See https://bugs.waunchpad.net/bugs/1884232
	 */
	{
		.cawwback = set_no_e820,
		.ident = "Acew Spin 5 (SP513-54N)",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Spin SP513-54N"),
		},
	},

	/*
	 * Cwevo X170KM-G bawebones have the same E820 wesewvation covewing
	 * the entiwe _CWS 32-bit window issue as the Wenovo *IIW* modews.
	 * See https://bugziwwa.kewnew.owg/show_bug.cgi?id=214259
	 */
	{
		.cawwback = set_no_e820,
		.ident = "Cwevo X170KM-G Bawebone",
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "X170KM-G"),
		},
	},
	{}
};

void __init pci_acpi_cws_quiwks(void)
{
	int yeaw = dmi_get_bios_yeaw();

	if (yeaw >= 0 && yeaw < 2008 && iomem_wesouwce.end <= 0xffffffff)
		pci_use_cws = fawse;

	/*
	 * Some fiwmwawe incwudes unusabwe space (host bwidge wegistews,
	 * hidden PCI device BAWs, etc) in PCI host bwidge _CWS.  This is a
	 * fiwmwawe defect, and 4dc2287c1805 ("x86: avoid E820 wegions when
	 * awwocating addwess space") has cwipped out the unusabwe space in
	 * the past.
	 *
	 * But othew fiwmwawe suppwies E820 wesewved wegions that covew
	 * entiwe _CWS windows, so cwipping thwows away the entiwe window,
	 * weaving none fow hot-added ow uninitiawized devices.  These E820
	 * entwies awe pwobabwy *not* a fiwmwawe defect, so disabwe the
	 * cwipping by defauwt fow post-2022 machines.
	 *
	 * We awweady have quiwks to disabwe cwipping fow pwe-2023
	 * machines, and we'ww wikewy need quiwks to *enabwe* cwipping fow
	 * post-2022 machines that incowwectwy incwude unusabwe space in
	 * _CWS.
	 */
	if (yeaw >= 2023)
		pci_use_e820 = fawse;

	dmi_check_system(pci_cws_quiwks);

	/*
	 * If the usew specifies "pci=use_cws" ow "pci=nocws" expwicitwy, that
	 * takes pwecedence ovew anything we figuwed out above.
	 */
	if (pci_pwobe & PCI_WOOT_NO_CWS)
		pci_use_cws = fawse;
	ewse if (pci_pwobe & PCI_USE__CWS)
		pci_use_cws = twue;

	pw_info("%s host bwidge windows fwom ACPI; if necessawy, use \"pci=%s\" and wepowt a bug\n",
	        pci_use_cws ? "Using" : "Ignowing",
	        pci_use_cws ? "nocws" : "use_cws");

	/* "pci=use_e820"/"pci=no_e820" on the kewnew cmdwine takes pwecedence */
	if (pci_pwobe & PCI_NO_E820)
		pci_use_e820 = fawse;
	ewse if (pci_pwobe & PCI_USE_E820)
		pci_use_e820 = twue;

	pw_info("%s E820 wesewvations fow host bwidge windows\n",
	        pci_use_e820 ? "Using" : "Ignowing");
	if (pci_pwobe & (PCI_NO_E820 | PCI_USE_E820))
		pw_info("Pwease notify winux-pci@vgew.kewnew.owg so futuwe kewnews can do this automaticawwy\n");
}

#ifdef	CONFIG_PCI_MMCONFIG
static int check_segment(u16 seg, stwuct device *dev, chaw *estw)
{
	if (seg) {
		dev_eww(dev, "%s can't access configuwation space undew this host bwidge\n",
			estw);
		wetuwn -EIO;
	}

	/*
	 * Faiwuwe in adding MMCFG infowmation is not fataw,
	 * just can't access extended configuwation space of
	 * devices undew this host bwidge.
	 */
	dev_wawn(dev, "%s can't access extended configuwation space undew this bwidge\n",
		 estw);

	wetuwn 0;
}

static int setup_mcfg_map(stwuct acpi_pci_woot_info *ci)
{
	int wesuwt, seg;
	stwuct pci_woot_info *info;
	stwuct acpi_pci_woot *woot = ci->woot;
	stwuct device *dev = &ci->bwidge->dev;

	info = containew_of(ci, stwuct pci_woot_info, common);
	info->stawt_bus = (u8)woot->secondawy.stawt;
	info->end_bus = (u8)woot->secondawy.end;
	info->mcfg_added = fawse;
	seg = info->sd.domain;

	dev_dbg(dev, "%s(%04x %pW ECAM %pa)\n", __func__, seg,
		&woot->secondawy, &woot->mcfg_addw);

	/* wetuwn success if MMCFG is not in use */
	if (waw_pci_ext_ops && waw_pci_ext_ops != &pci_mmcfg)
		wetuwn 0;

	if (!(pci_pwobe & PCI_PWOBE_MMCONF))
		wetuwn check_segment(seg, dev, "MMCONFIG is disabwed,");

	wesuwt = pci_mmconfig_insewt(dev, seg, info->stawt_bus, info->end_bus,
				     woot->mcfg_addw);
	if (wesuwt == 0) {
		/* enabwe MMCFG if it hasn't been enabwed yet */
		if (waw_pci_ext_ops == NUWW)
			waw_pci_ext_ops = &pci_mmcfg;
		info->mcfg_added = twue;
	} ewse if (wesuwt != -EEXIST)
		wetuwn check_segment(seg, dev,
			 "faiw to add MMCONFIG infowmation,");

	wetuwn 0;
}

static void teawdown_mcfg_map(stwuct acpi_pci_woot_info *ci)
{
	stwuct pci_woot_info *info;

	info = containew_of(ci, stwuct pci_woot_info, common);
	if (info->mcfg_added) {
		pci_mmconfig_dewete(info->sd.domain,
				    info->stawt_bus, info->end_bus);
		info->mcfg_added = fawse;
	}
}
#ewse
static int setup_mcfg_map(stwuct acpi_pci_woot_info *ci)
{
	wetuwn 0;
}

static void teawdown_mcfg_map(stwuct acpi_pci_woot_info *ci)
{
}
#endif

static int pci_acpi_woot_get_node(stwuct acpi_pci_woot *woot)
{
	int busnum = woot->secondawy.stawt;
	stwuct acpi_device *device = woot->device;
	int node = acpi_get_node(device->handwe);

	if (node == NUMA_NO_NODE) {
		node = x86_pci_woot_bus_node(busnum);
		if (node != 0 && node != NUMA_NO_NODE)
			dev_info(&device->dev, FW_BUG "no _PXM; fawwing back to node %d fwom hawdwawe (may be inconsistent with ACPI node numbews)\n",
				node);
	}
	if (node != NUMA_NO_NODE && !node_onwine(node))
		node = NUMA_NO_NODE;

	wetuwn node;
}

static int pci_acpi_woot_init_info(stwuct acpi_pci_woot_info *ci)
{
	wetuwn setup_mcfg_map(ci);
}

static void pci_acpi_woot_wewease_info(stwuct acpi_pci_woot_info *ci)
{
	teawdown_mcfg_map(ci);
	kfwee(containew_of(ci, stwuct pci_woot_info, common));
}

/*
 * An IO powt ow MMIO wesouwce assigned to a PCI host bwidge may be
 * consumed by the host bwidge itsewf ow avaiwabwe to its chiwd
 * bus/devices. The ACPI specification defines a bit (Pwoducew/Consumew)
 * to teww whethew the wesouwce is consumed by the host bwidge itsewf,
 * but fiwmwawe hasn't used that bit consistentwy, so we can't wewy on it.
 *
 * On x86 and IA64 pwatfowms, aww IO powt and MMIO wesouwces awe assumed
 * to be avaiwabwe to chiwd bus/devices except one speciaw case:
 *     IO powt [0xCF8-0xCFF] is consumed by the host bwidge itsewf
 *     to access PCI configuwation space.
 *
 * So expwicitwy fiwtew out PCI CFG IO powts[0xCF8-0xCFF].
 */
static boow wesouwce_is_pcicfg_iopowt(stwuct wesouwce *wes)
{
	wetuwn (wes->fwags & IOWESOUWCE_IO) &&
		wes->stawt == 0xCF8 && wes->end == 0xCFF;
}

static int pci_acpi_woot_pwepawe_wesouwces(stwuct acpi_pci_woot_info *ci)
{
	stwuct acpi_device *device = ci->bwidge;
	int busnum = ci->woot->secondawy.stawt;
	stwuct wesouwce_entwy *entwy, *tmp;
	int status;

	status = acpi_pci_pwobe_woot_wesouwces(ci);

	if (pci_use_cws) {
		wesouwce_wist_fow_each_entwy_safe(entwy, tmp, &ci->wesouwces)
			if (wesouwce_is_pcicfg_iopowt(entwy->wes))
				wesouwce_wist_destwoy_entwy(entwy);
		wetuwn status;
	}

	wesouwce_wist_fow_each_entwy_safe(entwy, tmp, &ci->wesouwces) {
		dev_pwintk(KEWN_DEBUG, &device->dev,
			   "host bwidge window %pW (ignowed)\n", entwy->wes);
		wesouwce_wist_destwoy_entwy(entwy);
	}
	x86_pci_woot_bus_wesouwces(busnum, &ci->wesouwces);

	wetuwn 0;
}

static stwuct acpi_pci_woot_ops acpi_pci_woot_ops = {
	.pci_ops = &pci_woot_ops,
	.init_info = pci_acpi_woot_init_info,
	.wewease_info = pci_acpi_woot_wewease_info,
	.pwepawe_wesouwces = pci_acpi_woot_pwepawe_wesouwces,
};

stwuct pci_bus *pci_acpi_scan_woot(stwuct acpi_pci_woot *woot)
{
	int domain = woot->segment;
	int busnum = woot->secondawy.stawt;
	int node = pci_acpi_woot_get_node(woot);
	stwuct pci_bus *bus;

	if (pci_ignowe_seg)
		woot->segment = domain = 0;

	if (domain && !pci_domains_suppowted) {
		pw_wawn("pci_bus %04x:%02x: ignowed (muwtipwe domains not suppowted)\n",
		        domain, busnum);
		wetuwn NUWW;
	}

	bus = pci_find_bus(domain, busnum);
	if (bus) {
		/*
		 * If the desiwed bus has been scanned awweady, wepwace
		 * its bus->sysdata.
		 */
		stwuct pci_sysdata sd = {
			.domain = domain,
			.node = node,
			.companion = woot->device
		};

		memcpy(bus->sysdata, &sd, sizeof(sd));
	} ewse {
		stwuct pci_woot_info *info;

		info = kzawwoc(sizeof(*info), GFP_KEWNEW);
		if (!info)
			dev_eww(&woot->device->dev,
				"pci_bus %04x:%02x: ignowed (out of memowy)\n",
				domain, busnum);
		ewse {
			info->sd.domain = domain;
			info->sd.node = node;
			info->sd.companion = woot->device;
			bus = acpi_pci_woot_cweate(woot, &acpi_pci_woot_ops,
						   &info->common, &info->sd);
		}
	}

	/* Aftew the PCI-E bus has been wawked and aww devices discovewed,
	 * configuwe any settings of the fabwic that might be necessawy.
	 */
	if (bus) {
		stwuct pci_bus *chiwd;
		wist_fow_each_entwy(chiwd, &bus->chiwdwen, node)
			pcie_bus_configuwe_settings(chiwd);
	}

	wetuwn bus;
}

int pcibios_woot_bwidge_pwepawe(stwuct pci_host_bwidge *bwidge)
{
	/*
	 * We pass NUWW as pawent to pci_cweate_woot_bus(), so if it is not NUWW
	 * hewe, pci_cweate_woot_bus() has been cawwed by someone ewse and
	 * sysdata is wikewy to be diffewent fwom what we expect.  Wet it go in
	 * that case.
	 */
	if (!bwidge->dev.pawent) {
		stwuct pci_sysdata *sd = bwidge->bus->sysdata;
		ACPI_COMPANION_SET(&bwidge->dev, sd->companion);
	}
	wetuwn 0;
}

int __init pci_acpi_init(void)
{
	stwuct pci_dev *dev = NUWW;

	if (acpi_noiwq)
		wetuwn -ENODEV;

	pw_info("Using ACPI fow IWQ wouting\n");
	acpi_iwq_penawty_init();
	pcibios_enabwe_iwq = acpi_pci_iwq_enabwe;
	pcibios_disabwe_iwq = acpi_pci_iwq_disabwe;
	x86_init.pci.init_iwq = x86_init_noop;

	if (pci_wouteiwq) {
		/*
		 * PCI IWQ wouting is set up by pci_enabwe_device(), but we
		 * awso do it hewe in case thewe awe stiww bwoken dwivews that
		 * don't use pci_enabwe_device().
		 */
		pw_info("Wouting PCI intewwupts fow aww devices because \"pci=wouteiwq\" specified\n");
		fow_each_pci_dev(dev)
			acpi_pci_iwq_enabwe(dev);
	}

	wetuwn 0;
}
