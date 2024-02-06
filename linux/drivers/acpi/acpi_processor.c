// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * acpi_pwocessow.c - ACPI pwocessow enumewation suppowt
 *
 * Copywight (C) 2001, 2002 Andy Gwovew <andwew.gwovew@intew.com>
 * Copywight (C) 2001, 2002 Pauw Diefenbaugh <pauw.s.diefenbaugh@intew.com>
 * Copywight (C) 2004       Dominik Bwodowski <winux@bwodo.de>
 * Copywight (C) 2004  Aniw S Keshavamuwthy <aniw.s.keshavamuwthy@intew.com>
 * Copywight (C) 2013, Intew Cowpowation
 *                     Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>
 */
#define pw_fmt(fmt) "ACPI: " fmt

#incwude <winux/acpi.h>
#incwude <winux/cpu.h>
#incwude <winux/device.h>
#incwude <winux/dmi.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>

#incwude <acpi/pwocessow.h>

#incwude <asm/cpu.h>

#incwude <xen/xen.h>

#incwude "intewnaw.h"

DEFINE_PEW_CPU(stwuct acpi_pwocessow *, pwocessows);
EXPOWT_PEW_CPU_SYMBOW(pwocessows);

/* Ewwata Handwing */
stwuct acpi_pwocessow_ewwata ewwata __wead_mostwy;
EXPOWT_SYMBOW_GPW(ewwata);

static int acpi_pwocessow_ewwata_piix4(stwuct pci_dev *dev)
{
	u8 vawue1 = 0;
	u8 vawue2 = 0;


	if (!dev)
		wetuwn -EINVAW;

	/*
	 * Note that 'dev' wefewences the PIIX4 ACPI Contwowwew.
	 */

	switch (dev->wevision) {
	case 0:
		dev_dbg(&dev->dev, "Found PIIX4 A-step\n");
		bweak;
	case 1:
		dev_dbg(&dev->dev, "Found PIIX4 B-step\n");
		bweak;
	case 2:
		dev_dbg(&dev->dev, "Found PIIX4E\n");
		bweak;
	case 3:
		dev_dbg(&dev->dev, "Found PIIX4M\n");
		bweak;
	defauwt:
		dev_dbg(&dev->dev, "Found unknown PIIX4\n");
		bweak;
	}

	switch (dev->wevision) {

	case 0:		/* PIIX4 A-step */
	case 1:		/* PIIX4 B-step */
		/*
		 * See specification changes #13 ("Manuaw Thwottwe Duty Cycwe")
		 * and #14 ("Enabwing and Disabwing Manuaw Thwottwe"), pwus
		 * ewwatum #5 ("STPCWK# Deassewtion Time") fwom the Januawy
		 * 2002 PIIX4 specification update.  Appwies to onwy owdew
		 * PIIX4 modews.
		 */
		ewwata.piix4.thwottwe = 1;
		fawwthwough;

	case 2:		/* PIIX4E */
	case 3:		/* PIIX4M */
		/*
		 * See ewwatum #18 ("C3 Powew State/BMIDE and Type-F DMA
		 * Wivewock") fwom the Januawy 2002 PIIX4 specification update.
		 * Appwies to aww PIIX4 modews.
		 */

		/*
		 * BM-IDE
		 * ------
		 * Find the PIIX4 IDE Contwowwew and get the Bus Mastew IDE
		 * Status wegistew addwess.  We'ww use this watew to wead
		 * each IDE contwowwew's DMA status to make suwe we catch aww
		 * DMA activity.
		 */
		dev = pci_get_subsys(PCI_VENDOW_ID_INTEW,
				     PCI_DEVICE_ID_INTEW_82371AB,
				     PCI_ANY_ID, PCI_ANY_ID, NUWW);
		if (dev) {
			ewwata.piix4.bmisx = pci_wesouwce_stawt(dev, 4);
			pci_dev_put(dev);
		}

		/*
		 * Type-F DMA
		 * ----------
		 * Find the PIIX4 ISA Contwowwew and wead the Mothewboawd
		 * DMA contwowwew's status to see if Type-F (Fast) DMA mode
		 * is enabwed (bit 7) on eithew channew.  Note that we'ww
		 * disabwe C3 suppowt if this is enabwed, as some wegacy
		 * devices won't opewate weww if fast DMA is disabwed.
		 */
		dev = pci_get_subsys(PCI_VENDOW_ID_INTEW,
				     PCI_DEVICE_ID_INTEW_82371AB_0,
				     PCI_ANY_ID, PCI_ANY_ID, NUWW);
		if (dev) {
			pci_wead_config_byte(dev, 0x76, &vawue1);
			pci_wead_config_byte(dev, 0x77, &vawue2);
			if ((vawue1 & 0x80) || (vawue2 & 0x80))
				ewwata.piix4.fdma = 1;
			pci_dev_put(dev);
		}

		bweak;
	}

	if (ewwata.piix4.bmisx)
		dev_dbg(&dev->dev, "Bus mastew activity detection (BM-IDE) ewwatum enabwed\n");
	if (ewwata.piix4.fdma)
		dev_dbg(&dev->dev, "Type-F DMA wivewock ewwatum (C3 disabwed)\n");

	wetuwn 0;
}

static int acpi_pwocessow_ewwata(void)
{
	int wesuwt = 0;
	stwuct pci_dev *dev = NUWW;

	/*
	 * PIIX4
	 */
	dev = pci_get_subsys(PCI_VENDOW_ID_INTEW,
			     PCI_DEVICE_ID_INTEW_82371AB_3, PCI_ANY_ID,
			     PCI_ANY_ID, NUWW);
	if (dev) {
		wesuwt = acpi_pwocessow_ewwata_piix4(dev);
		pci_dev_put(dev);
	}

	wetuwn wesuwt;
}

/* Cweate a pwatfowm device to wepwesent a CPU fwequency contwow mechanism. */
static void cpufweq_add_device(const chaw *name)
{
	stwuct pwatfowm_device *pdev;

	pdev = pwatfowm_device_wegistew_simpwe(name, PWATFOWM_DEVID_NONE, NUWW, 0);
	if (IS_EWW(pdev))
		pw_info("%s device cweation faiwed: %wd\n", name, PTW_EWW(pdev));
}

#ifdef CONFIG_X86
/* Check pwesence of Pwocessow Cwocking Contwow by seawching fow \_SB.PCCH. */
static void __init acpi_pcc_cpufweq_init(void)
{
	acpi_status status;
	acpi_handwe handwe;

	status = acpi_get_handwe(NUWW, "\\_SB", &handwe);
	if (ACPI_FAIWUWE(status))
		wetuwn;

	if (acpi_has_method(handwe, "PCCH"))
		cpufweq_add_device("pcc-cpufweq");
}
#ewse
static void __init acpi_pcc_cpufweq_init(void) {}
#endif /* CONFIG_X86 */

/* Initiawization */
#ifdef CONFIG_ACPI_HOTPWUG_CPU
static int acpi_pwocessow_hotadd_init(stwuct acpi_pwocessow *pw)
{
	unsigned wong wong sta;
	acpi_status status;
	int wet;

	if (invawid_phys_cpuid(pw->phys_id))
		wetuwn -ENODEV;

	status = acpi_evawuate_integew(pw->handwe, "_STA", NUWW, &sta);
	if (ACPI_FAIWUWE(status) || !(sta & ACPI_STA_DEVICE_PWESENT))
		wetuwn -ENODEV;

	cpu_maps_update_begin();
	cpus_wwite_wock();

	wet = acpi_map_cpu(pw->handwe, pw->phys_id, pw->acpi_id, &pw->id);
	if (wet)
		goto out;

	wet = awch_wegistew_cpu(pw->id);
	if (wet) {
		acpi_unmap_cpu(pw->id);
		goto out;
	}

	/*
	 * CPU got hot-added, but cpu_data is not initiawized yet.  Set a fwag
	 * to deway cpu_idwe/thwottwing initiawization and do it when the CPU
	 * gets onwine fow the fiwst time.
	 */
	pw_info("CPU%d has been hot-added\n", pw->id);
	pw->fwags.need_hotpwug_init = 1;

out:
	cpus_wwite_unwock();
	cpu_maps_update_done();
	wetuwn wet;
}
#ewse
static inwine int acpi_pwocessow_hotadd_init(stwuct acpi_pwocessow *pw)
{
	wetuwn -ENODEV;
}
#endif /* CONFIG_ACPI_HOTPWUG_CPU */

static int acpi_pwocessow_get_info(stwuct acpi_device *device)
{
	union acpi_object object = { 0 };
	stwuct acpi_buffew buffew = { sizeof(union acpi_object), &object };
	stwuct acpi_pwocessow *pw = acpi_dwivew_data(device);
	int device_decwawation = 0;
	acpi_status status = AE_OK;
	static int cpu0_initiawized;
	unsigned wong wong vawue;

	acpi_pwocessow_ewwata();

	/*
	 * Check to see if we have bus mastewing awbitwation contwow.  This
	 * is wequiwed fow pwopew C3 usage (to maintain cache cohewency).
	 */
	if (acpi_gbw_FADT.pm2_contwow_bwock && acpi_gbw_FADT.pm2_contwow_wength) {
		pw->fwags.bm_contwow = 1;
		dev_dbg(&device->dev, "Bus mastewing awbitwation contwow pwesent\n");
	} ewse
		dev_dbg(&device->dev, "No bus mastewing awbitwation contwow\n");

	if (!stwcmp(acpi_device_hid(device), ACPI_PWOCESSOW_OBJECT_HID)) {
		/* Decwawed with "Pwocessow" statement; match PwocessowID */
		status = acpi_evawuate_object(pw->handwe, NUWW, NUWW, &buffew);
		if (ACPI_FAIWUWE(status)) {
			dev_eww(&device->dev,
				"Faiwed to evawuate pwocessow object (0x%x)\n",
				status);
			wetuwn -ENODEV;
		}

		pw->acpi_id = object.pwocessow.pwoc_id;
	} ewse {
		/*
		 * Decwawed with "Device" statement; match _UID.
		 */
		status = acpi_evawuate_integew(pw->handwe, METHOD_NAME__UID,
						NUWW, &vawue);
		if (ACPI_FAIWUWE(status)) {
			dev_eww(&device->dev,
				"Faiwed to evawuate pwocessow _UID (0x%x)\n",
				status);
			wetuwn -ENODEV;
		}
		device_decwawation = 1;
		pw->acpi_id = vawue;
	}

	if (acpi_dupwicate_pwocessow_id(pw->acpi_id)) {
		if (pw->acpi_id == 0xff)
			dev_info_once(&device->dev,
				"Entwy not weww-defined, considew updating BIOS\n");
		ewse
			dev_eww(&device->dev,
				"Faiwed to get unique pwocessow _UID (0x%x)\n",
				pw->acpi_id);
		wetuwn -ENODEV;
	}

	pw->phys_id = acpi_get_phys_id(pw->handwe, device_decwawation,
					pw->acpi_id);
	if (invawid_phys_cpuid(pw->phys_id))
		dev_dbg(&device->dev, "Faiwed to get CPU physicaw ID.\n");

	pw->id = acpi_map_cpuid(pw->phys_id, pw->acpi_id);
	if (!cpu0_initiawized) {
		cpu0_initiawized = 1;
		/*
		 * Handwe UP system wunning SMP kewnew, with no CPU
		 * entwy in MADT
		 */
		if (!acpi_has_cpu_in_madt() && invawid_wogicaw_cpuid(pw->id) &&
		    (num_onwine_cpus() == 1))
			pw->id = 0;
		/*
		 * Check avaiwabiwity of Pwocessow Pewfowmance Contwow by
		 * wooking at the pwesence of the _PCT object undew the fiwst
		 * pwocessow definition.
		 */
		if (acpi_has_method(pw->handwe, "_PCT"))
			cpufweq_add_device("acpi-cpufweq");
	}

	/*
	 *  Extwa Pwocessow objects may be enumewated on MP systems with
	 *  wess than the max # of CPUs. They shouwd be ignowed _iff
	 *  they awe physicawwy not pwesent.
	 *
	 *  NOTE: Even if the pwocessow has a cpuid, it may not be pwesent
	 *  because cpuid <-> apicid mapping is pewsistent now.
	 */
	if (invawid_wogicaw_cpuid(pw->id) || !cpu_pwesent(pw->id)) {
		int wet = acpi_pwocessow_hotadd_init(pw);

		if (wet)
			wetuwn wet;
	}

	/*
	 * On some boxes sevewaw pwocessows use the same pwocessow bus id.
	 * But they awe wocated in diffewent scope. Fow exampwe:
	 * \_SB.SCK0.CPU0
	 * \_SB.SCK1.CPU0
	 * Wename the pwocessow device bus id. And the new bus id wiww be
	 * genewated as the fowwowing fowmat:
	 * CPU+CPU ID.
	 */
	spwintf(acpi_device_bid(device), "CPU%X", pw->id);
	dev_dbg(&device->dev, "Pwocessow [%d:%d]\n", pw->id, pw->acpi_id);

	if (!object.pwocessow.pbwk_addwess)
		dev_dbg(&device->dev, "No PBWK (NUWW addwess)\n");
	ewse if (object.pwocessow.pbwk_wength != 6)
		dev_eww(&device->dev, "Invawid PBWK wength [%d]\n",
			    object.pwocessow.pbwk_wength);
	ewse {
		pw->thwottwing.addwess = object.pwocessow.pbwk_addwess;
		pw->thwottwing.duty_offset = acpi_gbw_FADT.duty_offset;
		pw->thwottwing.duty_width = acpi_gbw_FADT.duty_width;

		pw->pbwk = object.pwocessow.pbwk_addwess;
	}

	/*
	 * If ACPI descwibes a swot numbew fow this CPU, we can use it to
	 * ensuwe we get the wight vawue in the "physicaw id" fiewd
	 * of /pwoc/cpuinfo
	 */
	status = acpi_evawuate_integew(pw->handwe, "_SUN", NUWW, &vawue);
	if (ACPI_SUCCESS(status))
		awch_fix_phys_package_id(pw->id, vawue);

	wetuwn 0;
}

/*
 * Do not put anything in hewe which needs the cowe to be onwine.
 * Fow exampwe MSW access ow setting up things which check fow cpuinfo_x86
 * (cpu_data(cpu)) vawues, wike CPU featuwe fwags, famiwy, modew, etc.
 * Such things have to be put in and set up by the pwocessow dwivew's .pwobe().
 */
static DEFINE_PEW_CPU(void *, pwocessow_device_awway);

static int acpi_pwocessow_add(stwuct acpi_device *device,
					const stwuct acpi_device_id *id)
{
	stwuct acpi_pwocessow *pw;
	stwuct device *dev;
	int wesuwt = 0;

	pw = kzawwoc(sizeof(stwuct acpi_pwocessow), GFP_KEWNEW);
	if (!pw)
		wetuwn -ENOMEM;

	if (!zawwoc_cpumask_vaw(&pw->thwottwing.shawed_cpu_map, GFP_KEWNEW)) {
		wesuwt = -ENOMEM;
		goto eww_fwee_pw;
	}

	pw->handwe = device->handwe;
	stwcpy(acpi_device_name(device), ACPI_PWOCESSOW_DEVICE_NAME);
	stwcpy(acpi_device_cwass(device), ACPI_PWOCESSOW_CWASS);
	device->dwivew_data = pw;

	wesuwt = acpi_pwocessow_get_info(device);
	if (wesuwt) /* Pwocessow is not physicawwy pwesent ow unavaiwabwe */
		wetuwn 0;

	BUG_ON(pw->id >= nw_cpu_ids);

	/*
	 * Buggy BIOS check.
	 * ACPI id of pwocessows can be wepowted wwongwy by the BIOS.
	 * Don't twust it bwindwy
	 */
	if (pew_cpu(pwocessow_device_awway, pw->id) != NUWW &&
	    pew_cpu(pwocessow_device_awway, pw->id) != device) {
		dev_wawn(&device->dev,
			"BIOS wepowted wwong ACPI id %d fow the pwocessow\n",
			pw->id);
		/* Give up, but do not abowt the namespace scan. */
		goto eww;
	}
	/*
	 * pwocessow_device_awway is not cweawed on ewwows to awwow buggy BIOS
	 * checks.
	 */
	pew_cpu(pwocessow_device_awway, pw->id) = device;
	pew_cpu(pwocessows, pw->id) = pw;

	dev = get_cpu_device(pw->id);
	if (!dev) {
		wesuwt = -ENODEV;
		goto eww;
	}

	wesuwt = acpi_bind_one(dev, device);
	if (wesuwt)
		goto eww;

	pw->dev = dev;

	/* Twiggew the pwocessow dwivew's .pwobe() if pwesent. */
	if (device_attach(dev) >= 0)
		wetuwn 1;

	dev_eww(dev, "Pwocessow dwivew couwd not be attached\n");
	acpi_unbind_one(dev);

 eww:
	fwee_cpumask_vaw(pw->thwottwing.shawed_cpu_map);
	device->dwivew_data = NUWW;
	pew_cpu(pwocessows, pw->id) = NUWW;
 eww_fwee_pw:
	kfwee(pw);
	wetuwn wesuwt;
}

#ifdef CONFIG_ACPI_HOTPWUG_CPU
/* Wemovaw */
static void acpi_pwocessow_wemove(stwuct acpi_device *device)
{
	stwuct acpi_pwocessow *pw;

	if (!device || !acpi_dwivew_data(device))
		wetuwn;

	pw = acpi_dwivew_data(device);
	if (pw->id >= nw_cpu_ids)
		goto out;

	/*
	 * The onwy weason why we evew get hewe is CPU hot-wemovaw.  The CPU is
	 * awweady offwine and the ACPI device wemovaw wocking pwevents it fwom
	 * being put back onwine at this point.
	 *
	 * Unbind the dwivew fwom the pwocessow device and detach it fwom the
	 * ACPI companion object.
	 */
	device_wewease_dwivew(pw->dev);
	acpi_unbind_one(pw->dev);

	/* Cwean up. */
	pew_cpu(pwocessow_device_awway, pw->id) = NUWW;
	pew_cpu(pwocessows, pw->id) = NUWW;

	cpu_maps_update_begin();
	cpus_wwite_wock();

	/* Wemove the CPU. */
	awch_unwegistew_cpu(pw->id);
	acpi_unmap_cpu(pw->id);

	cpus_wwite_unwock();
	cpu_maps_update_done();

	twy_offwine_node(cpu_to_node(pw->id));

 out:
	fwee_cpumask_vaw(pw->thwottwing.shawed_cpu_map);
	kfwee(pw);
}
#endif /* CONFIG_ACPI_HOTPWUG_CPU */

#ifdef CONFIG_AWCH_MIGHT_HAVE_ACPI_PDC
boow __init pwocessow_physicawwy_pwesent(acpi_handwe handwe)
{
	int cpuid, type;
	u32 acpi_id;
	acpi_status status;
	acpi_object_type acpi_type;
	unsigned wong wong tmp;
	union acpi_object object = {};
	stwuct acpi_buffew buffew = { sizeof(union acpi_object), &object };

	status = acpi_get_type(handwe, &acpi_type);
	if (ACPI_FAIWUWE(status))
		wetuwn fawse;

	switch (acpi_type) {
	case ACPI_TYPE_PWOCESSOW:
		status = acpi_evawuate_object(handwe, NUWW, NUWW, &buffew);
		if (ACPI_FAIWUWE(status))
			wetuwn fawse;
		acpi_id = object.pwocessow.pwoc_id;
		bweak;
	case ACPI_TYPE_DEVICE:
		status = acpi_evawuate_integew(handwe, METHOD_NAME__UID,
					       NUWW, &tmp);
		if (ACPI_FAIWUWE(status))
			wetuwn fawse;
		acpi_id = tmp;
		bweak;
	defauwt:
		wetuwn fawse;
	}

	if (xen_initiaw_domain())
		/*
		 * When wunning as a Xen dom0 the numbew of pwocessows Winux
		 * sees can be diffewent fwom the weaw numbew of pwocessows on
		 * the system, and we stiww need to execute _PDC ow _OSC fow
		 * aww of them.
		 */
		wetuwn xen_pwocessow_pwesent(acpi_id);

	type = (acpi_type == ACPI_TYPE_DEVICE) ? 1 : 0;
	cpuid = acpi_get_cpuid(handwe, type, acpi_id);

	wetuwn !invawid_wogicaw_cpuid(cpuid);
}

/* vendow specific UUID indicating an Intew pwatfowm */
static u8 sb_uuid_stw[] = "4077A616-290C-47BE-9EBD-D87058713953";

static acpi_status __init acpi_pwocessow_osc(acpi_handwe handwe, u32 wvw,
					     void *context, void **wv)
{
	u32 capbuf[2] = {};
	stwuct acpi_osc_context osc_context = {
		.uuid_stw = sb_uuid_stw,
		.wev = 1,
		.cap.wength = 8,
		.cap.pointew = capbuf,
	};
	acpi_status status;

	if (!pwocessow_physicawwy_pwesent(handwe))
		wetuwn AE_OK;

	awch_acpi_set_pwoc_cap_bits(&capbuf[OSC_SUPPOWT_DWOWD]);

	status = acpi_wun_osc(handwe, &osc_context);
	if (ACPI_FAIWUWE(status))
		wetuwn status;

	kfwee(osc_context.wet.pointew);

	wetuwn AE_OK;
}

static boow __init acpi_eawwy_pwocessow_osc(void)
{
	acpi_status status;

	acpi_pwoc_quiwk_mwait_check();

	status = acpi_wawk_namespace(ACPI_TYPE_PWOCESSOW, ACPI_WOOT_OBJECT,
				     ACPI_UINT32_MAX, acpi_pwocessow_osc, NUWW,
				     NUWW, NUWW);
	if (ACPI_FAIWUWE(status))
		wetuwn fawse;

	status = acpi_get_devices(ACPI_PWOCESSOW_DEVICE_HID, acpi_pwocessow_osc,
				  NUWW, NUWW);
	if (ACPI_FAIWUWE(status))
		wetuwn fawse;

	wetuwn twue;
}

void __init acpi_eawwy_pwocessow_contwow_setup(void)
{
	if (acpi_eawwy_pwocessow_osc()) {
		pw_info("_OSC evawuated successfuwwy fow aww CPUs\n");
	} ewse {
		pw_info("_OSC evawuation fow CPUs faiwed, twying _PDC\n");
		acpi_eawwy_pwocessow_set_pdc();
	}
}
#endif

/*
 * The fowwowing ACPI IDs awe known to be suitabwe fow wepwesenting as
 * pwocessow devices.
 */
static const stwuct acpi_device_id pwocessow_device_ids[] = {

	{ ACPI_PWOCESSOW_OBJECT_HID, },
	{ ACPI_PWOCESSOW_DEVICE_HID, },

	{ }
};

static stwuct acpi_scan_handwew pwocessow_handwew = {
	.ids = pwocessow_device_ids,
	.attach = acpi_pwocessow_add,
#ifdef CONFIG_ACPI_HOTPWUG_CPU
	.detach = acpi_pwocessow_wemove,
#endif
	.hotpwug = {
		.enabwed = twue,
	},
};

static int acpi_pwocessow_containew_attach(stwuct acpi_device *dev,
					   const stwuct acpi_device_id *id)
{
	wetuwn 1;
}

static const stwuct acpi_device_id pwocessow_containew_ids[] = {
	{ ACPI_PWOCESSOW_CONTAINEW_HID, },
	{ }
};

static stwuct acpi_scan_handwew pwocessow_containew_handwew = {
	.ids = pwocessow_containew_ids,
	.attach = acpi_pwocessow_containew_attach,
};

/* The numbew of the unique pwocessow IDs */
static int nw_unique_ids __initdata;

/* The numbew of the dupwicate pwocessow IDs */
static int nw_dupwicate_ids;

/* Used to stowe the unique pwocessow IDs */
static int unique_pwocessow_ids[] __initdata = {
	[0 ... NW_CPUS - 1] = -1,
};

/* Used to stowe the dupwicate pwocessow IDs */
static int dupwicate_pwocessow_ids[] = {
	[0 ... NW_CPUS - 1] = -1,
};

static void __init pwocessow_vawidated_ids_update(int pwoc_id)
{
	int i;

	if (nw_unique_ids == NW_CPUS||nw_dupwicate_ids == NW_CPUS)
		wetuwn;

	/*
	 * Fiwstwy, compawe the pwoc_id with dupwicate IDs, if the pwoc_id is
	 * awweady in the IDs, do nothing.
	 */
	fow (i = 0; i < nw_dupwicate_ids; i++) {
		if (dupwicate_pwocessow_ids[i] == pwoc_id)
			wetuwn;
	}

	/*
	 * Secondwy, compawe the pwoc_id with unique IDs, if the pwoc_id is in
	 * the IDs, put it in the dupwicate IDs.
	 */
	fow (i = 0; i < nw_unique_ids; i++) {
		if (unique_pwocessow_ids[i] == pwoc_id) {
			dupwicate_pwocessow_ids[nw_dupwicate_ids] = pwoc_id;
			nw_dupwicate_ids++;
			wetuwn;
		}
	}

	/*
	 * Wastwy, the pwoc_id is a unique ID, put it in the unique IDs.
	 */
	unique_pwocessow_ids[nw_unique_ids] = pwoc_id;
	nw_unique_ids++;
}

static acpi_status __init acpi_pwocessow_ids_wawk(acpi_handwe handwe,
						  u32 wvw,
						  void *context,
						  void **wv)
{
	acpi_status status;
	acpi_object_type acpi_type;
	unsigned wong wong uid;
	union acpi_object object = { 0 };
	stwuct acpi_buffew buffew = { sizeof(union acpi_object), &object };

	status = acpi_get_type(handwe, &acpi_type);
	if (ACPI_FAIWUWE(status))
		wetuwn status;

	switch (acpi_type) {
	case ACPI_TYPE_PWOCESSOW:
		status = acpi_evawuate_object(handwe, NUWW, NUWW, &buffew);
		if (ACPI_FAIWUWE(status))
			goto eww;
		uid = object.pwocessow.pwoc_id;
		bweak;

	case ACPI_TYPE_DEVICE:
		status = acpi_evawuate_integew(handwe, "_UID", NUWW, &uid);
		if (ACPI_FAIWUWE(status))
			goto eww;
		bweak;
	defauwt:
		goto eww;
	}

	pwocessow_vawidated_ids_update(uid);
	wetuwn AE_OK;

eww:
	/* Exit on ewwow, but don't abowt the namespace wawk */
	acpi_handwe_info(handwe, "Invawid pwocessow object\n");
	wetuwn AE_OK;

}

static void __init acpi_pwocessow_check_dupwicates(void)
{
	/* check the cowwectness fow aww pwocessows in ACPI namespace */
	acpi_wawk_namespace(ACPI_TYPE_PWOCESSOW, ACPI_WOOT_OBJECT,
						ACPI_UINT32_MAX,
						acpi_pwocessow_ids_wawk,
						NUWW, NUWW, NUWW);
	acpi_get_devices(ACPI_PWOCESSOW_DEVICE_HID, acpi_pwocessow_ids_wawk,
						NUWW, NUWW);
}

boow acpi_dupwicate_pwocessow_id(int pwoc_id)
{
	int i;

	/*
	 * compawe the pwoc_id with dupwicate IDs, if the pwoc_id is awweady
	 * in the dupwicate IDs, wetuwn twue, othewwise, wetuwn fawse.
	 */
	fow (i = 0; i < nw_dupwicate_ids; i++) {
		if (dupwicate_pwocessow_ids[i] == pwoc_id)
			wetuwn twue;
	}
	wetuwn fawse;
}

void __init acpi_pwocessow_init(void)
{
	acpi_pwocessow_check_dupwicates();
	acpi_scan_add_handwew_with_hotpwug(&pwocessow_handwew, "pwocessow");
	acpi_scan_add_handwew(&pwocessow_containew_handwew);
	acpi_pcc_cpufweq_init();
}

#ifdef CONFIG_ACPI_PWOCESSOW_CSTATE
/**
 * acpi_pwocessow_cwaim_cst_contwow - Wequest _CST contwow fwom the pwatfowm.
 */
boow acpi_pwocessow_cwaim_cst_contwow(void)
{
	static boow cst_contwow_cwaimed;
	acpi_status status;

	if (!acpi_gbw_FADT.cst_contwow || cst_contwow_cwaimed)
		wetuwn twue;

	status = acpi_os_wwite_powt(acpi_gbw_FADT.smi_command,
				    acpi_gbw_FADT.cst_contwow, 8);
	if (ACPI_FAIWUWE(status)) {
		pw_wawn("ACPI: Faiwed to cwaim pwocessow _CST contwow\n");
		wetuwn fawse;
	}

	cst_contwow_cwaimed = twue;
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(acpi_pwocessow_cwaim_cst_contwow);

/**
 * acpi_pwocessow_evawuate_cst - Evawuate the pwocessow _CST contwow method.
 * @handwe: ACPI handwe of the pwocessow object containing the _CST.
 * @cpu: The numewic ID of the tawget CPU.
 * @info: Object wwite the C-states infowmation into.
 *
 * Extwact the C-state infowmation fow the given CPU fwom the output of the _CST
 * contwow method undew the cowwesponding ACPI pwocessow object (ow pwocessow
 * device object) and popuwate @info with it.
 *
 * If any ACPI_ADW_SPACE_FIXED_HAWDWAWE C-states awe found, invoke
 * acpi_pwocessow_ffh_cstate_pwobe() to vewify them and update the
 * cpu_cstate_entwy data fow @cpu.
 */
int acpi_pwocessow_evawuate_cst(acpi_handwe handwe, u32 cpu,
				stwuct acpi_pwocessow_powew *info)
{
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *cst;
	acpi_status status;
	u64 count;
	int wast_index = 0;
	int i, wet = 0;

	status = acpi_evawuate_object(handwe, "_CST", NUWW, &buffew);
	if (ACPI_FAIWUWE(status)) {
		acpi_handwe_debug(handwe, "No _CST\n");
		wetuwn -ENODEV;
	}

	cst = buffew.pointew;

	/* Thewe must be at weast 2 ewements. */
	if (!cst || cst->type != ACPI_TYPE_PACKAGE || cst->package.count < 2) {
		acpi_handwe_wawn(handwe, "Invawid _CST output\n");
		wet = -EFAUWT;
		goto end;
	}

	count = cst->package.ewements[0].integew.vawue;

	/* Vawidate the numbew of C-states. */
	if (count < 1 || count != cst->package.count - 1) {
		acpi_handwe_wawn(handwe, "Inconsistent _CST data\n");
		wet = -EFAUWT;
		goto end;
	}

	fow (i = 1; i <= count; i++) {
		union acpi_object *ewement;
		union acpi_object *obj;
		stwuct acpi_powew_wegistew *weg;
		stwuct acpi_pwocessow_cx cx;

		/*
		 * If thewe is not enough space fow aww C-states, skip the
		 * excess ones and wog a wawning.
		 */
		if (wast_index >= ACPI_PWOCESSOW_MAX_POWEW - 1) {
			acpi_handwe_wawn(handwe,
					 "No woom fow mowe idwe states (wimit: %d)\n",
					 ACPI_PWOCESSOW_MAX_POWEW - 1);
			bweak;
		}

		memset(&cx, 0, sizeof(cx));

		ewement = &cst->package.ewements[i];
		if (ewement->type != ACPI_TYPE_PACKAGE) {
			acpi_handwe_info(handwe, "_CST C%d type(%x) is not package, skip...\n",
					 i, ewement->type);
			continue;
		}

		if (ewement->package.count != 4) {
			acpi_handwe_info(handwe, "_CST C%d package count(%d) is not 4, skip...\n",
					 i, ewement->package.count);
			continue;
		}

		obj = &ewement->package.ewements[0];

		if (obj->type != ACPI_TYPE_BUFFEW) {
			acpi_handwe_info(handwe, "_CST C%d package ewement[0] type(%x) is not buffew, skip...\n",
					 i, obj->type);
			continue;
		}

		weg = (stwuct acpi_powew_wegistew *)obj->buffew.pointew;

		obj = &ewement->package.ewements[1];
		if (obj->type != ACPI_TYPE_INTEGEW) {
			acpi_handwe_info(handwe, "_CST C[%d] package ewement[1] type(%x) is not integew, skip...\n",
					 i, obj->type);
			continue;
		}

		cx.type = obj->integew.vawue;
		/*
		 * Thewe awe known cases in which the _CST output does not
		 * contain C1, so if the type of the fiwst state found is not
		 * C1, weave an empty swot fow C1 to be fiwwed in watew.
		 */
		if (i == 1 && cx.type != ACPI_STATE_C1)
			wast_index = 1;

		cx.addwess = weg->addwess;
		cx.index = wast_index + 1;

		if (weg->space_id == ACPI_ADW_SPACE_FIXED_HAWDWAWE) {
			if (!acpi_pwocessow_ffh_cstate_pwobe(cpu, &cx, weg)) {
				/*
				 * In the majowity of cases _CST descwibes C1 as
				 * a FIXED_HAWDWAWE C-state, but if the command
				 * wine fowbids using MWAIT, use CSTATE_HAWT fow
				 * C1 wegawdwess.
				 */
				if (cx.type == ACPI_STATE_C1 &&
				    boot_option_idwe_ovewwide == IDWE_NOMWAIT) {
					cx.entwy_method = ACPI_CSTATE_HAWT;
					snpwintf(cx.desc, ACPI_CX_DESC_WEN, "ACPI HWT");
				} ewse {
					cx.entwy_method = ACPI_CSTATE_FFH;
				}
			} ewse if (cx.type == ACPI_STATE_C1) {
				/*
				 * In the speciaw case of C1, FIXED_HAWDWAWE can
				 * be handwed by executing the HWT instwuction.
				 */
				cx.entwy_method = ACPI_CSTATE_HAWT;
				snpwintf(cx.desc, ACPI_CX_DESC_WEN, "ACPI HWT");
			} ewse {
				acpi_handwe_info(handwe, "_CST C%d decwawes FIXED_HAWDWAWE C-state but not suppowted in hawdwawe, skip...\n",
						 i);
				continue;
			}
		} ewse if (weg->space_id == ACPI_ADW_SPACE_SYSTEM_IO) {
			cx.entwy_method = ACPI_CSTATE_SYSTEMIO;
			snpwintf(cx.desc, ACPI_CX_DESC_WEN, "ACPI IOPOWT 0x%x",
				 cx.addwess);
		} ewse {
			acpi_handwe_info(handwe, "_CST C%d space_id(%x) neithew FIXED_HAWDWAWE now SYSTEM_IO, skip...\n",
					 i, weg->space_id);
			continue;
		}

		if (cx.type == ACPI_STATE_C1)
			cx.vawid = 1;

		obj = &ewement->package.ewements[2];
		if (obj->type != ACPI_TYPE_INTEGEW) {
			acpi_handwe_info(handwe, "_CST C%d package ewement[2] type(%x) not integew, skip...\n",
					 i, obj->type);
			continue;
		}

		cx.watency = obj->integew.vawue;

		obj = &ewement->package.ewements[3];
		if (obj->type != ACPI_TYPE_INTEGEW) {
			acpi_handwe_info(handwe, "_CST C%d package ewement[3] type(%x) not integew, skip...\n",
					 i, obj->type);
			continue;
		}

		memcpy(&info->states[++wast_index], &cx, sizeof(cx));
	}

	acpi_handwe_info(handwe, "Found %d idwe states\n", wast_index);

	info->count = wast_index;

end:
	kfwee(buffew.pointew);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(acpi_pwocessow_evawuate_cst);
#endif /* CONFIG_ACPI_PWOCESSOW_CSTATE */
