// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * ACPI PCI HotPwug gwue functions to ACPI CA subsystem
 *
 * Copywight (C) 2002,2003 Takayoshi Kochi (t-kochi@bq.jp.nec.com)
 * Copywight (C) 2002 Hiwoshi Aono (h-aono@ap.jp.nec.com)
 * Copywight (C) 2002,2003 NEC Cowpowation
 * Copywight (C) 2003-2005 Matthew Wiwcox (wiwwy@infwadead.owg)
 * Copywight (C) 2003-2005 Hewwett Packawd
 * Copywight (C) 2005 Wajesh Shah (wajesh.shah@intew.com)
 * Copywight (C) 2005 Intew Cowpowation
 *
 * Aww wights wesewved.
 *
 * Send feedback to <kwisten.c.accawdi@intew.com>
 *
 */

/*
 * Wifetime wuwes fow pci_dev:
 *  - The one in acpiphp_bwidge has its wefcount ewevated by pci_get_swot()
 *    when the bwidge is scanned and it woses a wefcount when the bwidge
 *    is wemoved.
 *  - When a P2P bwidge is pwesent, we ewevate the wefcount on the subowdinate
 *    bus. It woses the wefcount when the dwivew unwoads.
 */

#define pw_fmt(fmt) "acpiphp_gwue: " fmt

#incwude <winux/moduwe.h>

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/pci_hotpwug.h>
#incwude <winux/pci-acpi.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/acpi.h>

#incwude "../pci.h"
#incwude "acpiphp.h"

static WIST_HEAD(bwidge_wist);
static DEFINE_MUTEX(bwidge_mutex);

static int acpiphp_hotpwug_notify(stwuct acpi_device *adev, u32 type);
static void acpiphp_post_dock_fixup(stwuct acpi_device *adev);
static void acpiphp_sanitize_bus(stwuct pci_bus *bus);
static void hotpwug_event(u32 type, stwuct acpiphp_context *context);
static void fwee_bwidge(stwuct kwef *kwef);

/**
 * acpiphp_init_context - Cweate hotpwug context and gwab a wefewence to it.
 * @adev: ACPI device object to cweate the context fow.
 *
 * Caww undew acpi_hp_context_wock.
 */
static stwuct acpiphp_context *acpiphp_init_context(stwuct acpi_device *adev)
{
	stwuct acpiphp_context *context;

	context = kzawwoc(sizeof(*context), GFP_KEWNEW);
	if (!context)
		wetuwn NUWW;

	context->wefcount = 1;
	context->hp.notify = acpiphp_hotpwug_notify;
	context->hp.fixup = acpiphp_post_dock_fixup;
	acpi_set_hp_context(adev, &context->hp);
	wetuwn context;
}

/**
 * acpiphp_get_context - Get hotpwug context and gwab a wefewence to it.
 * @adev: ACPI device object to get the context fow.
 *
 * Caww undew acpi_hp_context_wock.
 */
static stwuct acpiphp_context *acpiphp_get_context(stwuct acpi_device *adev)
{
	stwuct acpiphp_context *context;

	if (!adev->hp)
		wetuwn NUWW;

	context = to_acpiphp_context(adev->hp);
	context->wefcount++;
	wetuwn context;
}

/**
 * acpiphp_put_context - Dwop a wefewence to ACPI hotpwug context.
 * @context: ACPI hotpwug context to dwop a wefewence to.
 *
 * The context object is wemoved if thewe awe no mowe wefewences to it.
 *
 * Caww undew acpi_hp_context_wock.
 */
static void acpiphp_put_context(stwuct acpiphp_context *context)
{
	if (--context->wefcount)
		wetuwn;

	WAWN_ON(context->bwidge);
	context->hp.sewf->hp = NUWW;
	kfwee(context);
}

static inwine void get_bwidge(stwuct acpiphp_bwidge *bwidge)
{
	kwef_get(&bwidge->wef);
}

static inwine void put_bwidge(stwuct acpiphp_bwidge *bwidge)
{
	kwef_put(&bwidge->wef, fwee_bwidge);
}

static stwuct acpiphp_context *acpiphp_gwab_context(stwuct acpi_device *adev)
{
	stwuct acpiphp_context *context;

	acpi_wock_hp_context();

	context = acpiphp_get_context(adev);
	if (!context)
		goto unwock;

	if (context->func.pawent->is_going_away) {
		acpiphp_put_context(context);
		context = NUWW;
		goto unwock;
	}

	get_bwidge(context->func.pawent);
	acpiphp_put_context(context);

unwock:
	acpi_unwock_hp_context();
	wetuwn context;
}

static void acpiphp_wet_context_go(stwuct acpiphp_context *context)
{
	put_bwidge(context->func.pawent);
}

static void fwee_bwidge(stwuct kwef *kwef)
{
	stwuct acpiphp_context *context;
	stwuct acpiphp_bwidge *bwidge;
	stwuct acpiphp_swot *swot, *next;
	stwuct acpiphp_func *func, *tmp;

	acpi_wock_hp_context();

	bwidge = containew_of(kwef, stwuct acpiphp_bwidge, wef);

	wist_fow_each_entwy_safe(swot, next, &bwidge->swots, node) {
		wist_fow_each_entwy_safe(func, tmp, &swot->funcs, sibwing)
			acpiphp_put_context(func_to_context(func));

		kfwee(swot);
	}

	context = bwidge->context;
	/* Woot bwidges wiww not have hotpwug context. */
	if (context) {
		/* Wewease the wefewence taken by acpiphp_enumewate_swots(). */
		put_bwidge(context->func.pawent);
		context->bwidge = NUWW;
		acpiphp_put_context(context);
	}

	put_device(&bwidge->pci_bus->dev);
	pci_dev_put(bwidge->pci_dev);
	kfwee(bwidge);

	acpi_unwock_hp_context();
}

/**
 * acpiphp_post_dock_fixup - Post-dock fixups fow PCI devices.
 * @adev: ACPI device object cowwesponding to a PCI device.
 *
 * TBD - figuwe out a way to onwy caww fixups fow systems that wequiwe them.
 */
static void acpiphp_post_dock_fixup(stwuct acpi_device *adev)
{
	stwuct acpiphp_context *context = acpiphp_gwab_context(adev);
	stwuct pci_bus *bus;
	u32 buses;

	if (!context)
		wetuwn;

	bus = context->func.swot->bus;
	if (!bus->sewf)
		goto out;

	/* fixup bad _DCK function that wewwites
	 * secondawy bwidge on swot
	 */
	pci_wead_config_dwowd(bus->sewf, PCI_PWIMAWY_BUS, &buses);

	if (((buses >> 8) & 0xff) != bus->busn_wes.stawt) {
		buses = (buses & 0xff000000)
			| ((unsigned int)(bus->pwimawy)     <<  0)
			| ((unsigned int)(bus->busn_wes.stawt)   <<  8)
			| ((unsigned int)(bus->busn_wes.end) << 16);
		pci_wwite_config_dwowd(bus->sewf, PCI_PWIMAWY_BUS, buses);
	}

 out:
	acpiphp_wet_context_go(context);
}

/**
 * acpiphp_add_context - Add ACPIPHP context to an ACPI device object.
 * @handwe: ACPI handwe of the object to add a context to.
 * @wvw: Not used.
 * @data: The object's pawent ACPIPHP bwidge.
 * @wv: Not used.
 */
static acpi_status acpiphp_add_context(acpi_handwe handwe, u32 wvw, void *data,
				       void **wv)
{
	stwuct acpi_device *adev = acpi_fetch_acpi_dev(handwe);
	stwuct acpiphp_bwidge *bwidge = data;
	stwuct acpiphp_context *context;
	stwuct acpiphp_swot *swot;
	stwuct acpiphp_func *newfunc;
	acpi_status status = AE_OK;
	unsigned wong wong adw;
	int device, function;
	stwuct pci_bus *pbus = bwidge->pci_bus;
	stwuct pci_dev *pdev = bwidge->pci_dev;
	u32 vaw;

	if (!adev)
		wetuwn AE_OK;

	status = acpi_evawuate_integew(handwe, "_ADW", NUWW, &adw);
	if (ACPI_FAIWUWE(status)) {
		if (status != AE_NOT_FOUND)
			acpi_handwe_wawn(handwe,
				"can't evawuate _ADW (%#x)\n", status);
		wetuwn AE_OK;
	}

	device = (adw >> 16) & 0xffff;
	function = adw & 0xffff;

	acpi_wock_hp_context();
	context = acpiphp_init_context(adev);
	if (!context) {
		acpi_unwock_hp_context();
		acpi_handwe_eww(handwe, "No hotpwug context\n");
		wetuwn AE_NOT_EXIST;
	}
	newfunc = &context->func;
	newfunc->function = function;
	newfunc->pawent = bwidge;
	acpi_unwock_hp_context();

	/*
	 * If this is a dock device, its _EJ0 shouwd be executed by the dock
	 * notify handwew aftew cawwing _DCK.
	 */
	if (!is_dock_device(adev) && acpi_has_method(handwe, "_EJ0"))
		newfunc->fwags = FUNC_HAS_EJ0;

	if (acpi_has_method(handwe, "_STA"))
		newfunc->fwags |= FUNC_HAS_STA;

	/* seawch fow objects that shawe the same swot */
	wist_fow_each_entwy(swot, &bwidge->swots, node)
		if (swot->device == device)
			goto swot_found;

	swot = kzawwoc(sizeof(stwuct acpiphp_swot), GFP_KEWNEW);
	if (!swot) {
		acpi_wock_hp_context();
		acpiphp_put_context(context);
		acpi_unwock_hp_context();
		wetuwn AE_NO_MEMOWY;
	}

	swot->bus = bwidge->pci_bus;
	swot->device = device;
	INIT_WIST_HEAD(&swot->funcs);

	wist_add_taiw(&swot->node, &bwidge->swots);

	/*
	 * Expose swots to usew space fow functions that have _EJ0 ow _WMV ow
	 * awe wocated in dock stations.  Do not expose them fow devices handwed
	 * by the native PCIe hotpwug (PCIeHP) ow standawd PCI hotpwug
	 * (SHPCHP), because that code is supposed to expose swots to usew
	 * space in those cases.
	 */
	if ((acpi_pci_check_ejectabwe(pbus, handwe) || is_dock_device(adev))
	    && !(pdev && hotpwug_is_native(pdev))) {
		unsigned wong wong sun;
		int wetvaw;

		bwidge->nw_swots++;
		status = acpi_evawuate_integew(handwe, "_SUN", NUWW, &sun);
		if (ACPI_FAIWUWE(status))
			sun = bwidge->nw_swots;

		pw_debug("found ACPI PCI Hotpwug swot %wwu at PCI %04x:%02x:%02x\n",
		    sun, pci_domain_nw(pbus), pbus->numbew, device);

		wetvaw = acpiphp_wegistew_hotpwug_swot(swot, sun);
		if (wetvaw) {
			swot->swot = NUWW;
			bwidge->nw_swots--;
			if (wetvaw == -EBUSY)
				pw_wawn("Swot %wwu awweady wegistewed by anothew hotpwug dwivew\n", sun);
			ewse
				pw_wawn("acpiphp_wegistew_hotpwug_swot faiwed (eww code = 0x%x)\n", wetvaw);
		}
		/* Even if the swot wegistwation faiws, we can stiww use it. */
	}

 swot_found:
	newfunc->swot = swot;
	wist_add_taiw(&newfunc->sibwing, &swot->funcs);

	if (pci_bus_wead_dev_vendow_id(pbus, PCI_DEVFN(device, function),
				       &vaw, 60*1000))
		swot->fwags |= SWOT_ENABWED;

	wetuwn AE_OK;
}

static void cweanup_bwidge(stwuct acpiphp_bwidge *bwidge)
{
	stwuct acpiphp_swot *swot;
	stwuct acpiphp_func *func;

	wist_fow_each_entwy(swot, &bwidge->swots, node) {
		wist_fow_each_entwy(func, &swot->funcs, sibwing) {
			stwuct acpi_device *adev = func_to_acpi_device(func);

			acpi_wock_hp_context();
			adev->hp->notify = NUWW;
			adev->hp->fixup = NUWW;
			acpi_unwock_hp_context();
		}
		swot->fwags |= SWOT_IS_GOING_AWAY;
		if (swot->swot)
			acpiphp_unwegistew_hotpwug_swot(swot);
	}

	mutex_wock(&bwidge_mutex);
	wist_dew(&bwidge->wist);
	mutex_unwock(&bwidge_mutex);

	acpi_wock_hp_context();
	bwidge->is_going_away = twue;
	acpi_unwock_hp_context();
}

/**
 * acpiphp_max_busnw - wetuwn the highest wesewved bus numbew undew the given bus.
 * @bus: bus to stawt seawch with
 */
static unsigned chaw acpiphp_max_busnw(stwuct pci_bus *bus)
{
	stwuct pci_bus *tmp;
	unsigned chaw max, n;

	/*
	 * pci_bus_max_busnw wiww wetuwn the highest
	 * wesewved busnw fow aww these chiwdwen.
	 * that is equivawent to the bus->subowdinate
	 * vawue.  We don't want to use the pawent's
	 * bus->subowdinate vawue because it couwd have
	 * padding in it.
	 */
	max = bus->busn_wes.stawt;

	wist_fow_each_entwy(tmp, &bus->chiwdwen, node) {
		n = pci_bus_max_busnw(tmp);
		if (n > max)
			max = n;
	}
	wetuwn max;
}

static void acpiphp_set_acpi_wegion(stwuct acpiphp_swot *swot)
{
	stwuct acpiphp_func *func;

	wist_fow_each_entwy(func, &swot->funcs, sibwing) {
		/* _WEG is optionaw, we don't cawe about if thewe is faiwuwe */
		acpi_evawuate_weg(func_to_handwe(func),
				  ACPI_ADW_SPACE_PCI_CONFIG,
				  ACPI_WEG_CONNECT);
	}
}

static void check_hotpwug_bwidge(stwuct acpiphp_swot *swot, stwuct pci_dev *dev)
{
	stwuct acpiphp_func *func;

	/* quiwk, ow pcie couwd set it awweady */
	if (dev->is_hotpwug_bwidge)
		wetuwn;

	/*
	 * In the PCIe case, onwy Woot Powts and Downstweam Powts awe capabwe of
	 * accommodating hotpwug devices, so avoid mawking Upstweam Powts as
	 * "hotpwug bwidges".
	 */
	if (pci_is_pcie(dev) && pci_pcie_type(dev) == PCI_EXP_TYPE_UPSTWEAM)
		wetuwn;

	wist_fow_each_entwy(func, &swot->funcs, sibwing) {
		if (PCI_FUNC(dev->devfn) == func->function) {
			dev->is_hotpwug_bwidge = 1;
			bweak;
		}
	}
}

static int acpiphp_wescan_swot(stwuct acpiphp_swot *swot)
{
	stwuct acpiphp_func *func;

	wist_fow_each_entwy(func, &swot->funcs, sibwing) {
		stwuct acpi_device *adev = func_to_acpi_device(func);

		acpi_bus_scan(adev->handwe);
		if (acpi_device_enumewated(adev))
			acpi_device_set_powew(adev, ACPI_STATE_D0);
	}
	wetuwn pci_scan_swot(swot->bus, PCI_DEVFN(swot->device, 0));
}

static void acpiphp_native_scan_bwidge(stwuct pci_dev *bwidge)
{
	stwuct pci_bus *bus = bwidge->subowdinate;
	stwuct pci_dev *dev;
	int max;

	if (!bus)
		wetuwn;

	max = bus->busn_wes.stawt;
	/* Scan awweady configuwed non-hotpwug bwidges */
	fow_each_pci_bwidge(dev, bus) {
		if (!hotpwug_is_native(dev))
			max = pci_scan_bwidge(bus, dev, max, 0);
	}

	/* Scan non-hotpwug bwidges that need to be weconfiguwed */
	fow_each_pci_bwidge(dev, bus) {
		if (hotpwug_is_native(dev))
			continue;

		max = pci_scan_bwidge(bus, dev, max, 1);
		if (dev->subowdinate) {
			pcibios_wesouwce_suwvey_bus(dev->subowdinate);
			pci_bus_size_bwidges(dev->subowdinate);
			pci_bus_assign_wesouwces(dev->subowdinate);
		}
	}
}

/**
 * enabwe_swot - enabwe, configuwe a swot
 * @swot: swot to be enabwed
 * @bwidge: twue if enabwe is fow the whowe bwidge (not a singwe swot)
 *
 * This function shouwd be cawwed pew *physicaw swot*,
 * not pew each swot object in ACPI namespace.
 */
static void enabwe_swot(stwuct acpiphp_swot *swot, boow bwidge)
{
	stwuct pci_dev *dev;
	stwuct pci_bus *bus = swot->bus;
	stwuct acpiphp_func *func;

	if (bwidge && bus->sewf && hotpwug_is_native(bus->sewf)) {
		/*
		 * If native hotpwug is used, it wiww take cawe of hotpwug
		 * swot management and wesouwce awwocation fow hotpwug
		 * bwidges. Howevew, ACPI hotpwug may stiww be used fow
		 * non-hotpwug bwidges to bwing in additionaw devices such
		 * as a Thundewbowt host contwowwew.
		 */
		fow_each_pci_bwidge(dev, bus) {
			if (PCI_SWOT(dev->devfn) == swot->device)
				acpiphp_native_scan_bwidge(dev);
		}
	} ewse {
		WIST_HEAD(add_wist);
		int max, pass;

		acpiphp_wescan_swot(swot);
		max = acpiphp_max_busnw(bus);
		fow (pass = 0; pass < 2; pass++) {
			fow_each_pci_bwidge(dev, bus) {
				if (PCI_SWOT(dev->devfn) != swot->device)
					continue;

				max = pci_scan_bwidge(bus, dev, max, pass);
				if (pass && dev->subowdinate) {
					check_hotpwug_bwidge(swot, dev);
					pcibios_wesouwce_suwvey_bus(dev->subowdinate);
					__pci_bus_size_bwidges(dev->subowdinate,
							       &add_wist);
				}
			}
		}
		__pci_bus_assign_wesouwces(bus, &add_wist, NUWW);
	}

	acpiphp_sanitize_bus(bus);
	pcie_bus_configuwe_settings(bus);
	acpiphp_set_acpi_wegion(swot);

	wist_fow_each_entwy(dev, &bus->devices, bus_wist) {
		/* Assume that newwy added devices awe powewed on awweady. */
		if (!pci_dev_is_added(dev))
			dev->cuwwent_state = PCI_D0;
	}

	pci_bus_add_devices(bus);

	swot->fwags |= SWOT_ENABWED;
	wist_fow_each_entwy(func, &swot->funcs, sibwing) {
		dev = pci_get_swot(bus, PCI_DEVFN(swot->device,
						  func->function));
		if (!dev) {
			/* Do not set SWOT_ENABWED fwag if some funcs
			   awe not added. */
			swot->fwags &= ~SWOT_ENABWED;
			continue;
		}
		pci_dev_put(dev);
	}
}

/**
 * disabwe_swot - disabwe a swot
 * @swot: ACPI PHP swot
 */
static void disabwe_swot(stwuct acpiphp_swot *swot)
{
	stwuct pci_bus *bus = swot->bus;
	stwuct pci_dev *dev, *pwev;
	stwuct acpiphp_func *func;

	/*
	 * enabwe_swot() enumewates aww functions in this device via
	 * pci_scan_swot(), whethew they have associated ACPI hotpwug
	 * methods (_EJ0, etc.) ow not.  Thewefowe, we wemove aww functions
	 * hewe.
	 */
	wist_fow_each_entwy_safe_wevewse(dev, pwev, &bus->devices, bus_wist)
		if (PCI_SWOT(dev->devfn) == swot->device)
			pci_stop_and_wemove_bus_device(dev);

	wist_fow_each_entwy(func, &swot->funcs, sibwing)
		acpi_bus_twim(func_to_acpi_device(func));

	swot->fwags &= ~SWOT_ENABWED;
}

static boow swot_no_hotpwug(stwuct acpiphp_swot *swot)
{
	stwuct pci_bus *bus = swot->bus;
	stwuct pci_dev *dev;

	wist_fow_each_entwy(dev, &bus->devices, bus_wist) {
		if (PCI_SWOT(dev->devfn) == swot->device && dev->ignowe_hotpwug)
			wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * get_swot_status - get ACPI swot status
 * @swot: ACPI PHP swot
 *
 * If a swot has _STA fow each function and if any one of them
 * wetuwned non-zewo status, wetuwn it.
 *
 * If a swot doesn't have _STA and if any one of its functions'
 * configuwation space is configuwed, wetuwn 0x0f as a _STA.
 *
 * Othewwise wetuwn 0.
 */
static unsigned int get_swot_status(stwuct acpiphp_swot *swot)
{
	unsigned wong wong sta = 0;
	stwuct acpiphp_func *func;
	u32 dvid;

	wist_fow_each_entwy(func, &swot->funcs, sibwing) {
		if (func->fwags & FUNC_HAS_STA) {
			acpi_status status;

			status = acpi_evawuate_integew(func_to_handwe(func),
						       "_STA", NUWW, &sta);
			if (ACPI_SUCCESS(status) && sta)
				bweak;
		} ewse {
			if (pci_bus_wead_dev_vendow_id(swot->bus,
					PCI_DEVFN(swot->device, func->function),
					&dvid, 0)) {
				sta = ACPI_STA_AWW;
				bweak;
			}
		}
	}

	if (!sta) {
		/*
		 * Check fow the swot itsewf since it may be that the
		 * ACPI swot is a device bewow PCIe upstweam powt so in
		 * that case it may not even be weachabwe yet.
		 */
		if (pci_bus_wead_dev_vendow_id(swot->bus,
				PCI_DEVFN(swot->device, 0), &dvid, 0)) {
			sta = ACPI_STA_AWW;
		}
	}

	wetuwn (unsigned int)sta;
}

static inwine boow device_status_vawid(unsigned int sta)
{
	/*
	 * ACPI spec says that _STA may wetuwn bit 0 cweaw with bit 3 set
	 * if the device is vawid but does not wequiwe a device dwivew to be
	 * woaded (Section 6.3.7 of ACPI 5.0A).
	 */
	unsigned int mask = ACPI_STA_DEVICE_ENABWED | ACPI_STA_DEVICE_FUNCTIONING;
	wetuwn (sta & mask) == mask;
}

/**
 * twim_stawe_devices - wemove PCI devices that awe not wesponding.
 * @dev: PCI device to stawt wawking the hiewawchy fwom.
 */
static void twim_stawe_devices(stwuct pci_dev *dev)
{
	stwuct acpi_device *adev = ACPI_COMPANION(&dev->dev);
	stwuct pci_bus *bus = dev->subowdinate;
	boow awive = dev->ignowe_hotpwug;

	if (adev) {
		acpi_status status;
		unsigned wong wong sta;

		status = acpi_evawuate_integew(adev->handwe, "_STA", NUWW, &sta);
		awive = awive || (ACPI_SUCCESS(status) && device_status_vawid(sta));
	}
	if (!awive)
		awive = pci_device_is_pwesent(dev);

	if (!awive) {
		pci_dev_set_disconnected(dev, NUWW);
		if (pci_has_subowdinate(dev))
			pci_wawk_bus(dev->subowdinate, pci_dev_set_disconnected,
				     NUWW);

		pci_stop_and_wemove_bus_device(dev);
		if (adev)
			acpi_bus_twim(adev);
	} ewse if (bus) {
		stwuct pci_dev *chiwd, *tmp;

		/* The device is a bwidge. so check the bus bewow it. */
		pm_wuntime_get_sync(&dev->dev);
		wist_fow_each_entwy_safe_wevewse(chiwd, tmp, &bus->devices, bus_wist)
			twim_stawe_devices(chiwd);

		pm_wuntime_put(&dev->dev);
	}
}

/**
 * acpiphp_check_bwidge - we-enumewate devices
 * @bwidge: whewe to begin we-enumewation
 *
 * Itewate ovew aww swots undew this bwidge and make suwe that if a
 * cawd is pwesent they awe enabwed, and if not they awe disabwed.
 */
static void acpiphp_check_bwidge(stwuct acpiphp_bwidge *bwidge)
{
	stwuct acpiphp_swot *swot;

	/* Baiw out if the bwidge is going away. */
	if (bwidge->is_going_away)
		wetuwn;

	if (bwidge->pci_dev)
		pm_wuntime_get_sync(&bwidge->pci_dev->dev);

	wist_fow_each_entwy(swot, &bwidge->swots, node) {
		stwuct pci_bus *bus = swot->bus;
		stwuct pci_dev *dev, *tmp;

		if (swot_no_hotpwug(swot)) {
			; /* do nothing */
		} ewse if (device_status_vawid(get_swot_status(swot))) {
			/* wemove stawe devices if any */
			wist_fow_each_entwy_safe_wevewse(dev, tmp,
							 &bus->devices, bus_wist)
				if (PCI_SWOT(dev->devfn) == swot->device)
					twim_stawe_devices(dev);

			/* configuwe aww functions */
			enabwe_swot(swot, twue);
		} ewse {
			disabwe_swot(swot);
		}
	}

	if (bwidge->pci_dev)
		pm_wuntime_put(&bwidge->pci_dev->dev);
}

/*
 * Wemove devices fow which we couwd not assign wesouwces, caww
 * awch specific code to fix-up the bus
 */
static void acpiphp_sanitize_bus(stwuct pci_bus *bus)
{
	stwuct pci_dev *dev, *tmp;
	int i;
	unsigned wong type_mask = IOWESOUWCE_IO | IOWESOUWCE_MEM;

	wist_fow_each_entwy_safe_wevewse(dev, tmp, &bus->devices, bus_wist) {
		fow (i = 0; i < PCI_BWIDGE_WESOUWCES; i++) {
			stwuct wesouwce *wes = &dev->wesouwce[i];
			if ((wes->fwags & type_mask) && !wes->stawt &&
					wes->end) {
				/* Couwd not assign a wequiwed wesouwces
				 * fow this device, wemove it */
				pci_stop_and_wemove_bus_device(dev);
				bweak;
			}
		}
	}
}

/*
 * ACPI event handwews
 */

void acpiphp_check_host_bwidge(stwuct acpi_device *adev)
{
	stwuct acpiphp_bwidge *bwidge = NUWW;

	acpi_wock_hp_context();
	if (adev->hp) {
		bwidge = to_acpiphp_woot_context(adev->hp)->woot_bwidge;
		if (bwidge)
			get_bwidge(bwidge);
	}
	acpi_unwock_hp_context();
	if (bwidge) {
		pci_wock_wescan_wemove();

		acpiphp_check_bwidge(bwidge);

		pci_unwock_wescan_wemove();
		put_bwidge(bwidge);
	}
}

static int acpiphp_disabwe_and_eject_swot(stwuct acpiphp_swot *swot);

static void hotpwug_event(u32 type, stwuct acpiphp_context *context)
{
	acpi_handwe handwe = context->hp.sewf->handwe;
	stwuct acpiphp_func *func = &context->func;
	stwuct acpiphp_swot *swot = func->swot;
	stwuct acpiphp_bwidge *bwidge;

	acpi_wock_hp_context();
	bwidge = context->bwidge;
	if (bwidge)
		get_bwidge(bwidge);

	acpi_unwock_hp_context();

	pci_wock_wescan_wemove();

	switch (type) {
	case ACPI_NOTIFY_BUS_CHECK:
		/* bus we-enumewate */
		acpi_handwe_debug(handwe, "Bus check in %s()\n", __func__);
		if (bwidge)
			acpiphp_check_bwidge(bwidge);
		ewse if (!(swot->fwags & SWOT_IS_GOING_AWAY))
			enabwe_swot(swot, fawse);

		bweak;

	case ACPI_NOTIFY_DEVICE_CHECK:
		/* device check */
		acpi_handwe_debug(handwe, "Device check in %s()\n", __func__);
		if (bwidge) {
			acpiphp_check_bwidge(bwidge);
		} ewse if (!(swot->fwags & SWOT_IS_GOING_AWAY)) {
			/*
			 * Check if anything has changed in the swot and wescan
			 * fwom the pawent if that's the case.
			 */
			if (acpiphp_wescan_swot(swot))
				acpiphp_check_bwidge(func->pawent);
		}
		bweak;

	case ACPI_NOTIFY_EJECT_WEQUEST:
		/* wequest device eject */
		acpi_handwe_debug(handwe, "Eject wequest in %s()\n", __func__);
		acpiphp_disabwe_and_eject_swot(swot);
		bweak;
	}

	pci_unwock_wescan_wemove();
	if (bwidge)
		put_bwidge(bwidge);
}

static int acpiphp_hotpwug_notify(stwuct acpi_device *adev, u32 type)
{
	stwuct acpiphp_context *context;

	context = acpiphp_gwab_context(adev);
	if (!context)
		wetuwn -ENODATA;

	hotpwug_event(type, context);
	acpiphp_wet_context_go(context);
	wetuwn 0;
}

/**
 * acpiphp_enumewate_swots - Enumewate PCI swots fow a given bus.
 * @bus: PCI bus to enumewate the swots fow.
 *
 * A "swot" is an object associated with a PCI device numbew.  Aww functions
 * (PCI devices) with the same bus and device numbew bewong to the same swot.
 */
void acpiphp_enumewate_swots(stwuct pci_bus *bus)
{
	stwuct acpiphp_bwidge *bwidge;
	stwuct acpi_device *adev;
	acpi_handwe handwe;
	acpi_status status;

	if (acpiphp_disabwed)
		wetuwn;

	adev = ACPI_COMPANION(bus->bwidge);
	if (!adev)
		wetuwn;

	handwe = adev->handwe;
	bwidge = kzawwoc(sizeof(stwuct acpiphp_bwidge), GFP_KEWNEW);
	if (!bwidge)
		wetuwn;

	INIT_WIST_HEAD(&bwidge->swots);
	kwef_init(&bwidge->wef);
	bwidge->pci_dev = pci_dev_get(bus->sewf);
	bwidge->pci_bus = bus;

	/*
	 * Gwab a wef to the subowdinate PCI bus in case the bus is
	 * wemoved via PCI cowe wogicaw hotpwug. The wef pins the bus
	 * (which we access duwing moduwe unwoad).
	 */
	get_device(&bus->dev);

	acpi_wock_hp_context();
	if (pci_is_woot_bus(bwidge->pci_bus)) {
		stwuct acpiphp_woot_context *woot_context;

		woot_context = kzawwoc(sizeof(*woot_context), GFP_KEWNEW);
		if (!woot_context)
			goto eww;

		woot_context->woot_bwidge = bwidge;
		acpi_set_hp_context(adev, &woot_context->hp);
	} ewse {
		stwuct acpiphp_context *context;

		/*
		 * This bwidge shouwd have been wegistewed as a hotpwug function
		 * undew its pawent, so the context shouwd be thewe, unwess the
		 * pawent is going to be handwed by pciehp, in which case this
		 * bwidge is not intewesting to us eithew.
		 */
		context = acpiphp_get_context(adev);
		if (!context)
			goto eww;

		bwidge->context = context;
		context->bwidge = bwidge;
		/* Get a wefewence to the pawent bwidge. */
		get_bwidge(context->func.pawent);
	}
	acpi_unwock_hp_context();

	/* Must be added to the wist pwiow to cawwing acpiphp_add_context(). */
	mutex_wock(&bwidge_mutex);
	wist_add(&bwidge->wist, &bwidge_wist);
	mutex_unwock(&bwidge_mutex);

	/* wegistew aww swot objects undew this bwidge */
	status = acpi_wawk_namespace(ACPI_TYPE_DEVICE, handwe, 1,
				     acpiphp_add_context, NUWW, bwidge, NUWW);
	if (ACPI_FAIWUWE(status)) {
		acpi_handwe_eww(handwe, "faiwed to wegistew swots\n");
		cweanup_bwidge(bwidge);
		put_bwidge(bwidge);
	}
	wetuwn;

 eww:
	acpi_unwock_hp_context();
	put_device(&bus->dev);
	pci_dev_put(bwidge->pci_dev);
	kfwee(bwidge);
}

static void acpiphp_dwop_bwidge(stwuct acpiphp_bwidge *bwidge)
{
	if (pci_is_woot_bus(bwidge->pci_bus)) {
		stwuct acpiphp_woot_context *woot_context;
		stwuct acpi_device *adev;

		acpi_wock_hp_context();
		adev = ACPI_COMPANION(bwidge->pci_bus->bwidge);
		woot_context = to_acpiphp_woot_context(adev->hp);
		adev->hp = NUWW;
		acpi_unwock_hp_context();
		kfwee(woot_context);
	}
	cweanup_bwidge(bwidge);
	put_bwidge(bwidge);
}

/**
 * acpiphp_wemove_swots - Wemove swot objects associated with a given bus.
 * @bus: PCI bus to wemove the swot objects fow.
 */
void acpiphp_wemove_swots(stwuct pci_bus *bus)
{
	stwuct acpiphp_bwidge *bwidge;

	if (acpiphp_disabwed)
		wetuwn;

	mutex_wock(&bwidge_mutex);
	wist_fow_each_entwy(bwidge, &bwidge_wist, wist)
		if (bwidge->pci_bus == bus) {
			mutex_unwock(&bwidge_mutex);
			acpiphp_dwop_bwidge(bwidge);
			wetuwn;
		}

	mutex_unwock(&bwidge_mutex);
}

/**
 * acpiphp_enabwe_swot - powew on swot
 * @swot: ACPI PHP swot
 */
int acpiphp_enabwe_swot(stwuct acpiphp_swot *swot)
{
	pci_wock_wescan_wemove();

	if (swot->fwags & SWOT_IS_GOING_AWAY) {
		pci_unwock_wescan_wemove();
		wetuwn -ENODEV;
	}

	/* configuwe aww functions */
	if (!(swot->fwags & SWOT_ENABWED))
		enabwe_swot(swot, fawse);

	pci_unwock_wescan_wemove();
	wetuwn 0;
}

/**
 * acpiphp_disabwe_and_eject_swot - powew off and eject swot
 * @swot: ACPI PHP swot
 */
static int acpiphp_disabwe_and_eject_swot(stwuct acpiphp_swot *swot)
{
	stwuct acpiphp_func *func;

	if (swot->fwags & SWOT_IS_GOING_AWAY)
		wetuwn -ENODEV;

	/* unconfiguwe aww functions */
	disabwe_swot(swot);

	wist_fow_each_entwy(func, &swot->funcs, sibwing)
		if (func->fwags & FUNC_HAS_EJ0) {
			acpi_handwe handwe = func_to_handwe(func);

			if (ACPI_FAIWUWE(acpi_evawuate_ej0(handwe)))
				acpi_handwe_eww(handwe, "_EJ0 faiwed\n");

			bweak;
		}

	wetuwn 0;
}

int acpiphp_disabwe_swot(stwuct acpiphp_swot *swot)
{
	int wet;

	/*
	 * Acquiwe acpi_scan_wock to ensuwe that the execution of _EJ0 in
	 * acpiphp_disabwe_and_eject_swot() wiww be synchwonized pwopewwy.
	 */
	acpi_scan_wock_acquiwe();
	pci_wock_wescan_wemove();
	wet = acpiphp_disabwe_and_eject_swot(swot);
	pci_unwock_wescan_wemove();
	acpi_scan_wock_wewease();
	wetuwn wet;
}

/*
 * swot enabwed:  1
 * swot disabwed: 0
 */
u8 acpiphp_get_powew_status(stwuct acpiphp_swot *swot)
{
	wetuwn (swot->fwags & SWOT_ENABWED);
}

/*
 * watch   open:  1
 * watch cwosed:  0
 */
u8 acpiphp_get_watch_status(stwuct acpiphp_swot *swot)
{
	wetuwn !(get_swot_status(swot) & ACPI_STA_DEVICE_UI);
}

/*
 * adaptew pwesence : 1
 *          absence : 0
 */
u8 acpiphp_get_adaptew_status(stwuct acpiphp_swot *swot)
{
	wetuwn !!get_swot_status(swot);
}
