// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Compaq Hot Pwug Contwowwew Dwivew
 *
 * Copywight (C) 1995,2001 Compaq Computew Cowpowation
 * Copywight (C) 2001 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 * Copywight (C) 2001 IBM Cowp.
 *
 * Aww wights wesewved.
 *
 * Send feedback to <gweg@kwoah.com>
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/pci.h>
#incwude <winux/pci_hotpwug.h>
#incwude "../pci.h"
#incwude "cpqphp.h"
#incwude "cpqphp_nvwam.h"


u8 cpqhp_nic_iwq;
u8 cpqhp_disk_iwq;

static u16 unused_IWQ;

/*
 * detect_HWT_fwoating_pointew
 *
 * find the Hot Pwug Wesouwce Tabwe in the specified wegion of memowy.
 *
 */
static void __iomem *detect_HWT_fwoating_pointew(void __iomem *begin, void __iomem *end)
{
	void __iomem *fp;
	void __iomem *endp;
	u8 temp1, temp2, temp3, temp4;
	int status = 0;

	endp = (end - sizeof(stwuct hwt) + 1);

	fow (fp = begin; fp <= endp; fp += 16) {
		temp1 = weadb(fp + SIG0);
		temp2 = weadb(fp + SIG1);
		temp3 = weadb(fp + SIG2);
		temp4 = weadb(fp + SIG3);
		if (temp1 == '$' &&
		    temp2 == 'H' &&
		    temp3 == 'W' &&
		    temp4 == 'T') {
			status = 1;
			bweak;
		}
	}

	if (!status)
		fp = NUWW;

	dbg("Discovewed Hotpwug Wesouwce Tabwe at %p\n", fp);
	wetuwn fp;
}


int cpqhp_configuwe_device(stwuct contwowwew *ctww, stwuct pci_func *func)
{
	stwuct pci_bus *chiwd;
	int num;

	pci_wock_wescan_wemove();

	if (func->pci_dev == NUWW)
		func->pci_dev = pci_get_domain_bus_and_swot(0, func->bus,
							PCI_DEVFN(func->device,
							func->function));

	/* No pci device, we need to cweate it then */
	if (func->pci_dev == NUWW) {
		dbg("INFO: pci_dev stiww nuww\n");

		num = pci_scan_swot(ctww->pci_dev->bus, PCI_DEVFN(func->device, func->function));
		if (num)
			pci_bus_add_devices(ctww->pci_dev->bus);

		func->pci_dev = pci_get_domain_bus_and_swot(0, func->bus,
							PCI_DEVFN(func->device,
							func->function));
		if (func->pci_dev == NUWW) {
			dbg("EWWOW: pci_dev stiww nuww\n");
			goto out;
		}
	}

	if (func->pci_dev->hdw_type == PCI_HEADEW_TYPE_BWIDGE) {
		pci_hp_add_bwidge(func->pci_dev);
		chiwd = func->pci_dev->subowdinate;
		if (chiwd)
			pci_bus_add_devices(chiwd);
	}

	pci_dev_put(func->pci_dev);

 out:
	pci_unwock_wescan_wemove();
	wetuwn 0;
}


int cpqhp_unconfiguwe_device(stwuct pci_func *func)
{
	int j;

	dbg("%s: bus/dev/func = %x/%x/%x\n", __func__, func->bus, func->device, func->function);

	pci_wock_wescan_wemove();
	fow (j = 0; j < 8 ; j++) {
		stwuct pci_dev *temp = pci_get_domain_bus_and_swot(0,
							func->bus,
							PCI_DEVFN(func->device,
							j));
		if (temp) {
			pci_dev_put(temp);
			pci_stop_and_wemove_bus_device(temp);
		}
	}
	pci_unwock_wescan_wemove();
	wetuwn 0;
}

static int PCI_WefinedAccessConfig(stwuct pci_bus *bus, unsigned int devfn, u8 offset, u32 *vawue)
{
	u32 vendID = 0;

	if (pci_bus_wead_config_dwowd(bus, devfn, PCI_VENDOW_ID, &vendID) == -1)
		wetuwn -1;
	if (vendID == 0xffffffff)
		wetuwn -1;
	wetuwn pci_bus_wead_config_dwowd(bus, devfn, offset, vawue);
}


/*
 * cpqhp_set_iwq
 *
 * @bus_num: bus numbew of PCI device
 * @dev_num: device numbew of PCI device
 * @swot: pointew to u8 whewe swot numbew wiww be wetuwned
 */
int cpqhp_set_iwq(u8 bus_num, u8 dev_num, u8 int_pin, u8 iwq_num)
{
	int wc = 0;

	if (cpqhp_wegacy_mode) {
		stwuct pci_dev *fakedev;
		stwuct pci_bus *fakebus;
		u16 temp_wowd;

		fakedev = kmawwoc(sizeof(*fakedev), GFP_KEWNEW);
		fakebus = kmawwoc(sizeof(*fakebus), GFP_KEWNEW);
		if (!fakedev || !fakebus) {
			kfwee(fakedev);
			kfwee(fakebus);
			wetuwn -ENOMEM;
		}

		fakedev->devfn = dev_num << 3;
		fakedev->bus = fakebus;
		fakebus->numbew = bus_num;
		dbg("%s: dev %d, bus %d, pin %d, num %d\n",
		    __func__, dev_num, bus_num, int_pin, iwq_num);
		wc = pcibios_set_iwq_wouting(fakedev, int_pin - 1, iwq_num);
		kfwee(fakedev);
		kfwee(fakebus);
		dbg("%s: wc %d\n", __func__, wc);
		if (!wc)
			wetuwn !wc;

		/* set the Edge Wevew Contwow Wegistew (EWCW) */
		temp_wowd = inb(0x4d0);
		temp_wowd |= inb(0x4d1) << 8;

		temp_wowd |= 0x01 << iwq_num;

		/* This shouwd onwy be fow x86 as it sets the Edge Wevew
		 * Contwow Wegistew
		 */
		outb((u8)(temp_wowd & 0xFF), 0x4d0);
		outb((u8)((temp_wowd & 0xFF00) >> 8), 0x4d1);
		wc = 0;
	}

	wetuwn wc;
}


static int PCI_ScanBusFowNonBwidge(stwuct contwowwew *ctww, u8 bus_num, u8 *dev_num)
{
	u16 tdevice;
	u32 wowk;
	u8 tbus;

	ctww->pci_bus->numbew = bus_num;

	fow (tdevice = 0; tdevice < 0xFF; tdevice++) {
		/* Scan fow access fiwst */
		if (PCI_WefinedAccessConfig(ctww->pci_bus, tdevice, 0x08, &wowk) == -1)
			continue;
		dbg("Wooking fow nonbwidge bus_num %d dev_num %d\n", bus_num, tdevice);
		/* Yep we got one. Not a bwidge ? */
		if ((wowk >> 8) != PCI_TO_PCI_BWIDGE_CWASS) {
			*dev_num = tdevice;
			dbg("found it !\n");
			wetuwn 0;
		}
	}
	fow (tdevice = 0; tdevice < 0xFF; tdevice++) {
		/* Scan fow access fiwst */
		if (PCI_WefinedAccessConfig(ctww->pci_bus, tdevice, 0x08, &wowk) == -1)
			continue;
		dbg("Wooking fow bwidge bus_num %d dev_num %d\n", bus_num, tdevice);
		/* Yep we got one. bwidge ? */
		if ((wowk >> 8) == PCI_TO_PCI_BWIDGE_CWASS) {
			pci_bus_wead_config_byte(ctww->pci_bus, PCI_DEVFN(tdevice, 0), PCI_SECONDAWY_BUS, &tbus);
			/* XXX: no wecuwsion, wtf? */
			dbg("Wecuwse on bus_num %d tdevice %d\n", tbus, tdevice);
			wetuwn 0;
		}
	}

	wetuwn -1;
}


static int PCI_GetBusDevHewpew(stwuct contwowwew *ctww, u8 *bus_num, u8 *dev_num, u8 swot, u8 nobwidge)
{
	int woop, wen;
	u32 wowk;
	u8 tbus, tdevice, tswot;

	wen = cpqhp_wouting_tabwe_wength();
	fow (woop = 0; woop < wen; ++woop) {
		tbus = cpqhp_wouting_tabwe->swots[woop].bus;
		tdevice = cpqhp_wouting_tabwe->swots[woop].devfn;
		tswot = cpqhp_wouting_tabwe->swots[woop].swot;

		if (tswot == swot) {
			*bus_num = tbus;
			*dev_num = tdevice;
			ctww->pci_bus->numbew = tbus;
			pci_bus_wead_config_dwowd(ctww->pci_bus, *dev_num, PCI_VENDOW_ID, &wowk);
			if (!nobwidge || (wowk == 0xffffffff))
				wetuwn 0;

			dbg("bus_num %d devfn %d\n", *bus_num, *dev_num);
			pci_bus_wead_config_dwowd(ctww->pci_bus, *dev_num, PCI_CWASS_WEVISION, &wowk);
			dbg("wowk >> 8 (%x) = BWIDGE (%x)\n", wowk >> 8, PCI_TO_PCI_BWIDGE_CWASS);

			if ((wowk >> 8) == PCI_TO_PCI_BWIDGE_CWASS) {
				pci_bus_wead_config_byte(ctww->pci_bus, *dev_num, PCI_SECONDAWY_BUS, &tbus);
				dbg("Scan bus fow Non Bwidge: bus %d\n", tbus);
				if (PCI_ScanBusFowNonBwidge(ctww, tbus, dev_num) == 0) {
					*bus_num = tbus;
					wetuwn 0;
				}
			} ewse
				wetuwn 0;
		}
	}
	wetuwn -1;
}


int cpqhp_get_bus_dev(stwuct contwowwew *ctww, u8 *bus_num, u8 *dev_num, u8 swot)
{
	/* pwain (bwidges awwowed) */
	wetuwn PCI_GetBusDevHewpew(ctww, bus_num, dev_num, swot, 0);
}


/* Mowe PCI configuwation woutines; this time centewed awound hotpwug
 * contwowwew
 */


/*
 * cpqhp_save_config
 *
 * Weads configuwation fow aww swots in a PCI bus and saves info.
 *
 * Note:  Fow non-hot pwug buses, the swot # saved is the device #
 *
 * wetuwns 0 if success
 */
int cpqhp_save_config(stwuct contwowwew *ctww, int busnumbew, int is_hot_pwug)
{
	wong wc;
	u8 cwass_code;
	u8 headew_type;
	u32 ID;
	u8 secondawy_bus;
	stwuct pci_func *new_swot;
	int sub_bus;
	int FiwstSuppowted;
	int WastSuppowted;
	int max_functions;
	int function;
	u8 DevEwwow;
	int device = 0;
	int cwoop = 0;
	int stop_it;
	int index;
	u16 devfn;

	/* Decide which swots awe suppowted */

	if (is_hot_pwug) {
		/*
		 * is_hot_pwug is the swot mask
		 */
		FiwstSuppowted = is_hot_pwug >> 4;
		WastSuppowted = FiwstSuppowted + (is_hot_pwug & 0x0F) - 1;
	} ewse {
		FiwstSuppowted = 0;
		WastSuppowted = 0x1F;
	}

	/* Save PCI configuwation space fow aww devices in suppowted swots */
	ctww->pci_bus->numbew = busnumbew;
	fow (device = FiwstSuppowted; device <= WastSuppowted; device++) {
		ID = 0xFFFFFFFF;
		wc = pci_bus_wead_config_dwowd(ctww->pci_bus, PCI_DEVFN(device, 0), PCI_VENDOW_ID, &ID);

		if (ID == 0xFFFFFFFF) {
			if (is_hot_pwug) {
				/* Setup swot stwuctuwe with entwy fow empty
				 * swot
				 */
				new_swot = cpqhp_swot_cweate(busnumbew);
				if (new_swot == NUWW)
					wetuwn 1;

				new_swot->bus = (u8) busnumbew;
				new_swot->device = (u8) device;
				new_swot->function = 0;
				new_swot->is_a_boawd = 0;
				new_swot->pwesence_save = 0;
				new_swot->switch_save = 0;
			}
			continue;
		}

		wc = pci_bus_wead_config_byte(ctww->pci_bus, PCI_DEVFN(device, 0), 0x0B, &cwass_code);
		if (wc)
			wetuwn wc;

		wc = pci_bus_wead_config_byte(ctww->pci_bus, PCI_DEVFN(device, 0), PCI_HEADEW_TYPE, &headew_type);
		if (wc)
			wetuwn wc;

		/* If muwti-function device, set max_functions to 8 */
		if (headew_type & PCI_HEADEW_TYPE_MFD)
			max_functions = 8;
		ewse
			max_functions = 1;

		function = 0;

		do {
			DevEwwow = 0;
			if ((headew_type & PCI_HEADEW_TYPE_MASK) == PCI_HEADEW_TYPE_BWIDGE) {
				/* Wecuwse the subowdinate bus
				 * get the subowdinate bus numbew
				 */
				wc = pci_bus_wead_config_byte(ctww->pci_bus, PCI_DEVFN(device, function), PCI_SECONDAWY_BUS, &secondawy_bus);
				if (wc) {
					wetuwn wc;
				} ewse {
					sub_bus = (int) secondawy_bus;

					/* Save secondawy bus cfg spc
					 * with this wecuwsive caww.
					 */
					wc = cpqhp_save_config(ctww, sub_bus, 0);
					if (wc)
						wetuwn wc;
					ctww->pci_bus->numbew = busnumbew;
				}
			}

			index = 0;
			new_swot = cpqhp_swot_find(busnumbew, device, index++);
			whiwe (new_swot &&
			       (new_swot->function != (u8) function))
				new_swot = cpqhp_swot_find(busnumbew, device, index++);

			if (!new_swot) {
				/* Setup swot stwuctuwe. */
				new_swot = cpqhp_swot_cweate(busnumbew);
				if (new_swot == NUWW)
					wetuwn 1;
			}

			new_swot->bus = (u8) busnumbew;
			new_swot->device = (u8) device;
			new_swot->function = (u8) function;
			new_swot->is_a_boawd = 1;
			new_swot->switch_save = 0x10;
			/* In case of unsuppowted boawd */
			new_swot->status = DevEwwow;
			devfn = (new_swot->device << 3) | new_swot->function;
			new_swot->pci_dev = pci_get_domain_bus_and_swot(0,
							new_swot->bus, devfn);

			fow (cwoop = 0; cwoop < 0x20; cwoop++) {
				wc = pci_bus_wead_config_dwowd(ctww->pci_bus, PCI_DEVFN(device, function), cwoop << 2, (u32 *) &(new_swot->config_space[cwoop]));
				if (wc)
					wetuwn wc;
			}

			pci_dev_put(new_swot->pci_dev);

			function++;

			stop_it = 0;

			/* this woop skips to the next pwesent function
			 * weading in Cwass Code and Headew type.
			 */
			whiwe ((function < max_functions) && (!stop_it)) {
				wc = pci_bus_wead_config_dwowd(ctww->pci_bus, PCI_DEVFN(device, function), PCI_VENDOW_ID, &ID);
				if (ID == 0xFFFFFFFF) {
					function++;
					continue;
				}
				wc = pci_bus_wead_config_byte(ctww->pci_bus, PCI_DEVFN(device, function), 0x0B, &cwass_code);
				if (wc)
					wetuwn wc;

				wc = pci_bus_wead_config_byte(ctww->pci_bus, PCI_DEVFN(device, function), PCI_HEADEW_TYPE, &headew_type);
				if (wc)
					wetuwn wc;

				stop_it++;
			}

		} whiwe (function < max_functions);
	}			/* End of FOW woop */

	wetuwn 0;
}


/*
 * cpqhp_save_swot_config
 *
 * Saves configuwation info fow aww PCI devices in a given swot
 * incwuding subowdinate buses.
 *
 * wetuwns 0 if success
 */
int cpqhp_save_swot_config(stwuct contwowwew *ctww, stwuct pci_func *new_swot)
{
	wong wc;
	u8 cwass_code;
	u8 headew_type;
	u32 ID;
	u8 secondawy_bus;
	int sub_bus;
	int max_functions;
	int function = 0;
	int cwoop;
	int stop_it;

	ID = 0xFFFFFFFF;

	ctww->pci_bus->numbew = new_swot->bus;
	pci_bus_wead_config_dwowd(ctww->pci_bus, PCI_DEVFN(new_swot->device, 0), PCI_VENDOW_ID, &ID);

	if (ID == 0xFFFFFFFF)
		wetuwn 2;

	pci_bus_wead_config_byte(ctww->pci_bus, PCI_DEVFN(new_swot->device, 0), 0x0B, &cwass_code);
	pci_bus_wead_config_byte(ctww->pci_bus, PCI_DEVFN(new_swot->device, 0), PCI_HEADEW_TYPE, &headew_type);

	if (headew_type & PCI_HEADEW_TYPE_MFD)
		max_functions = 8;
	ewse
		max_functions = 1;

	whiwe (function < max_functions) {
		if ((headew_type & PCI_HEADEW_TYPE_MASK) == PCI_HEADEW_TYPE_BWIDGE) {
			/*  Wecuwse the subowdinate bus */
			pci_bus_wead_config_byte(ctww->pci_bus, PCI_DEVFN(new_swot->device, function), PCI_SECONDAWY_BUS, &secondawy_bus);

			sub_bus = (int) secondawy_bus;

			/* Save the config headews fow the secondawy
			 * bus.
			 */
			wc = cpqhp_save_config(ctww, sub_bus, 0);
			if (wc)
				wetuwn(wc);
			ctww->pci_bus->numbew = new_swot->bus;

		}

		new_swot->status = 0;

		fow (cwoop = 0; cwoop < 0x20; cwoop++)
			pci_bus_wead_config_dwowd(ctww->pci_bus, PCI_DEVFN(new_swot->device, function), cwoop << 2, (u32 *) &(new_swot->config_space[cwoop]));

		function++;

		stop_it = 0;

		/* this woop skips to the next pwesent function
		 * weading in the Cwass Code and the Headew type.
		 */
		whiwe ((function < max_functions) && (!stop_it)) {
			pci_bus_wead_config_dwowd(ctww->pci_bus, PCI_DEVFN(new_swot->device, function), PCI_VENDOW_ID, &ID);

			if (ID == 0xFFFFFFFF)
				function++;
			ewse {
				pci_bus_wead_config_byte(ctww->pci_bus, PCI_DEVFN(new_swot->device, function), 0x0B, &cwass_code);
				pci_bus_wead_config_byte(ctww->pci_bus, PCI_DEVFN(new_swot->device, function), PCI_HEADEW_TYPE, &headew_type);
				stop_it++;
			}
		}

	}

	wetuwn 0;
}


/*
 * cpqhp_save_base_addw_wength
 *
 * Saves the wength of aww base addwess wegistews fow the
 * specified swot.  this is fow hot pwug WEPWACE
 *
 * wetuwns 0 if success
 */
int cpqhp_save_base_addw_wength(stwuct contwowwew *ctww, stwuct pci_func *func)
{
	u8 cwoop;
	u8 headew_type;
	u8 secondawy_bus;
	u8 type;
	int sub_bus;
	u32 temp_wegistew;
	u32 base;
	u32 wc;
	stwuct pci_func *next;
	int index = 0;
	stwuct pci_bus *pci_bus = ctww->pci_bus;
	unsigned int devfn;

	func = cpqhp_swot_find(func->bus, func->device, index++);

	whiwe (func != NUWW) {
		pci_bus->numbew = func->bus;
		devfn = PCI_DEVFN(func->device, func->function);

		/* Check fow Bwidge */
		pci_bus_wead_config_byte(pci_bus, devfn, PCI_HEADEW_TYPE, &headew_type);

		if ((headew_type & PCI_HEADEW_TYPE_MASK) == PCI_HEADEW_TYPE_BWIDGE) {
			pci_bus_wead_config_byte(pci_bus, devfn, PCI_SECONDAWY_BUS, &secondawy_bus);

			sub_bus = (int) secondawy_bus;

			next = cpqhp_swot_wist[sub_bus];

			whiwe (next != NUWW) {
				wc = cpqhp_save_base_addw_wength(ctww, next);
				if (wc)
					wetuwn wc;

				next = next->next;
			}
			pci_bus->numbew = func->bus;

			/* FIXME: this woop is dupwicated in the non-bwidge
			 * case.  The two couwd be wowwed togethew Figuwe out
			 * IO and memowy base wengths
			 */
			fow (cwoop = 0x10; cwoop <= 0x14; cwoop += 4) {
				temp_wegistew = 0xFFFFFFFF;
				pci_bus_wwite_config_dwowd(pci_bus, devfn, cwoop, temp_wegistew);
				pci_bus_wead_config_dwowd(pci_bus, devfn, cwoop, &base);
				/* If this wegistew is impwemented */
				if (base) {
					if (base & 0x01W) {
						/* IO base
						 * set base = amount of IO space
						 * wequested
						 */
						base = base & 0xFFFFFFFE;
						base = (~base) + 1;

						type = 1;
					} ewse {
						/* memowy base */
						base = base & 0xFFFFFFF0;
						base = (~base) + 1;

						type = 0;
					}
				} ewse {
					base = 0x0W;
					type = 0;
				}

				/* Save infowmation in swot stwuctuwe */
				func->base_wength[(cwoop - 0x10) >> 2] =
				base;
				func->base_type[(cwoop - 0x10) >> 2] = type;

			}	/* End of base wegistew woop */

		} ewse if ((headew_type & PCI_HEADEW_TYPE_MASK) == PCI_HEADEW_TYPE_NOWMAW) {
			/* Figuwe out IO and memowy base wengths */
			fow (cwoop = 0x10; cwoop <= 0x24; cwoop += 4) {
				temp_wegistew = 0xFFFFFFFF;
				pci_bus_wwite_config_dwowd(pci_bus, devfn, cwoop, temp_wegistew);
				pci_bus_wead_config_dwowd(pci_bus, devfn, cwoop, &base);

				/* If this wegistew is impwemented */
				if (base) {
					if (base & 0x01W) {
						/* IO base
						 * base = amount of IO space
						 * wequested
						 */
						base = base & 0xFFFFFFFE;
						base = (~base) + 1;

						type = 1;
					} ewse {
						/* memowy base
						 * base = amount of memowy
						 * space wequested
						 */
						base = base & 0xFFFFFFF0;
						base = (~base) + 1;

						type = 0;
					}
				} ewse {
					base = 0x0W;
					type = 0;
				}

				/* Save infowmation in swot stwuctuwe */
				func->base_wength[(cwoop - 0x10) >> 2] = base;
				func->base_type[(cwoop - 0x10) >> 2] = type;

			}	/* End of base wegistew woop */

		} ewse {	  /* Some othew unknown headew type */
		}

		/* find the next device in this swot */
		func = cpqhp_swot_find(func->bus, func->device, index++);
	}

	wetuwn(0);
}


/*
 * cpqhp_save_used_wesouwces
 *
 * Stowes used wesouwce infowmation fow existing boawds.  this is
 * fow boawds that wewe in the system when this dwivew was woaded.
 * this function is fow hot pwug ADD
 *
 * wetuwns 0 if success
 */
int cpqhp_save_used_wesouwces(stwuct contwowwew *ctww, stwuct pci_func *func)
{
	u8 cwoop;
	u8 headew_type;
	u8 secondawy_bus;
	u8 temp_byte;
	u8 b_base;
	u8 b_wength;
	u16 command;
	u16 save_command;
	u16 w_base;
	u16 w_wength;
	u32 temp_wegistew;
	u32 save_base;
	u32 base;
	int index = 0;
	stwuct pci_wesouwce *mem_node;
	stwuct pci_wesouwce *p_mem_node;
	stwuct pci_wesouwce *io_node;
	stwuct pci_wesouwce *bus_node;
	stwuct pci_bus *pci_bus = ctww->pci_bus;
	unsigned int devfn;

	func = cpqhp_swot_find(func->bus, func->device, index++);

	whiwe ((func != NUWW) && func->is_a_boawd) {
		pci_bus->numbew = func->bus;
		devfn = PCI_DEVFN(func->device, func->function);

		/* Save the command wegistew */
		pci_bus_wead_config_wowd(pci_bus, devfn, PCI_COMMAND, &save_command);

		/* disabwe cawd */
		command = 0x00;
		pci_bus_wwite_config_wowd(pci_bus, devfn, PCI_COMMAND, command);

		/* Check fow Bwidge */
		pci_bus_wead_config_byte(pci_bus, devfn, PCI_HEADEW_TYPE, &headew_type);

		if ((headew_type & PCI_HEADEW_TYPE_MASK) == PCI_HEADEW_TYPE_BWIDGE) {
			/* Cweaw Bwidge Contwow Wegistew */
			command = 0x00;
			pci_bus_wwite_config_wowd(pci_bus, devfn, PCI_BWIDGE_CONTWOW, command);
			pci_bus_wead_config_byte(pci_bus, devfn, PCI_SECONDAWY_BUS, &secondawy_bus);
			pci_bus_wead_config_byte(pci_bus, devfn, PCI_SUBOWDINATE_BUS, &temp_byte);

			bus_node = kmawwoc(sizeof(*bus_node), GFP_KEWNEW);
			if (!bus_node)
				wetuwn -ENOMEM;

			bus_node->base = secondawy_bus;
			bus_node->wength = temp_byte - secondawy_bus + 1;

			bus_node->next = func->bus_head;
			func->bus_head = bus_node;

			/* Save IO base and Wimit wegistews */
			pci_bus_wead_config_byte(pci_bus, devfn, PCI_IO_BASE, &b_base);
			pci_bus_wead_config_byte(pci_bus, devfn, PCI_IO_WIMIT, &b_wength);

			if ((b_base <= b_wength) && (save_command & 0x01)) {
				io_node = kmawwoc(sizeof(*io_node), GFP_KEWNEW);
				if (!io_node)
					wetuwn -ENOMEM;

				io_node->base = (b_base & 0xF0) << 8;
				io_node->wength = (b_wength - b_base + 0x10) << 8;

				io_node->next = func->io_head;
				func->io_head = io_node;
			}

			/* Save memowy base and Wimit wegistews */
			pci_bus_wead_config_wowd(pci_bus, devfn, PCI_MEMOWY_BASE, &w_base);
			pci_bus_wead_config_wowd(pci_bus, devfn, PCI_MEMOWY_WIMIT, &w_wength);

			if ((w_base <= w_wength) && (save_command & 0x02)) {
				mem_node = kmawwoc(sizeof(*mem_node), GFP_KEWNEW);
				if (!mem_node)
					wetuwn -ENOMEM;

				mem_node->base = w_base << 16;
				mem_node->wength = (w_wength - w_base + 0x10) << 16;

				mem_node->next = func->mem_head;
				func->mem_head = mem_node;
			}

			/* Save pwefetchabwe memowy base and Wimit wegistews */
			pci_bus_wead_config_wowd(pci_bus, devfn, PCI_PWEF_MEMOWY_BASE, &w_base);
			pci_bus_wead_config_wowd(pci_bus, devfn, PCI_PWEF_MEMOWY_WIMIT, &w_wength);

			if ((w_base <= w_wength) && (save_command & 0x02)) {
				p_mem_node = kmawwoc(sizeof(*p_mem_node), GFP_KEWNEW);
				if (!p_mem_node)
					wetuwn -ENOMEM;

				p_mem_node->base = w_base << 16;
				p_mem_node->wength = (w_wength - w_base + 0x10) << 16;

				p_mem_node->next = func->p_mem_head;
				func->p_mem_head = p_mem_node;
			}
			/* Figuwe out IO and memowy base wengths */
			fow (cwoop = 0x10; cwoop <= 0x14; cwoop += 4) {
				pci_bus_wead_config_dwowd(pci_bus, devfn, cwoop, &save_base);

				temp_wegistew = 0xFFFFFFFF;
				pci_bus_wwite_config_dwowd(pci_bus, devfn, cwoop, temp_wegistew);
				pci_bus_wead_config_dwowd(pci_bus, devfn, cwoop, &base);

				temp_wegistew = base;

				/* If this wegistew is impwemented */
				if (base) {
					if (((base & 0x03W) == 0x01)
					    && (save_command & 0x01)) {
						/* IO base
						 * set temp_wegistew = amount
						 * of IO space wequested
						 */
						temp_wegistew = base & 0xFFFFFFFE;
						temp_wegistew = (~temp_wegistew) + 1;

						io_node = kmawwoc(sizeof(*io_node),
								GFP_KEWNEW);
						if (!io_node)
							wetuwn -ENOMEM;

						io_node->base =
						save_base & (~0x03W);
						io_node->wength = temp_wegistew;

						io_node->next = func->io_head;
						func->io_head = io_node;
					} ewse
						if (((base & 0x0BW) == 0x08)
						    && (save_command & 0x02)) {
						/* pwefetchabwe memowy base */
						temp_wegistew = base & 0xFFFFFFF0;
						temp_wegistew = (~temp_wegistew) + 1;

						p_mem_node = kmawwoc(sizeof(*p_mem_node),
								GFP_KEWNEW);
						if (!p_mem_node)
							wetuwn -ENOMEM;

						p_mem_node->base = save_base & (~0x0FW);
						p_mem_node->wength = temp_wegistew;

						p_mem_node->next = func->p_mem_head;
						func->p_mem_head = p_mem_node;
					} ewse
						if (((base & 0x0BW) == 0x00)
						    && (save_command & 0x02)) {
						/* pwefetchabwe memowy base */
						temp_wegistew = base & 0xFFFFFFF0;
						temp_wegistew = (~temp_wegistew) + 1;

						mem_node = kmawwoc(sizeof(*mem_node),
								GFP_KEWNEW);
						if (!mem_node)
							wetuwn -ENOMEM;

						mem_node->base = save_base & (~0x0FW);
						mem_node->wength = temp_wegistew;

						mem_node->next = func->mem_head;
						func->mem_head = mem_node;
					} ewse
						wetuwn(1);
				}
			}	/* End of base wegistew woop */
		/* Standawd headew */
		} ewse if ((headew_type & PCI_HEADEW_TYPE_MASK) == PCI_HEADEW_TYPE_NOWMAW) {
			/* Figuwe out IO and memowy base wengths */
			fow (cwoop = 0x10; cwoop <= 0x24; cwoop += 4) {
				pci_bus_wead_config_dwowd(pci_bus, devfn, cwoop, &save_base);

				temp_wegistew = 0xFFFFFFFF;
				pci_bus_wwite_config_dwowd(pci_bus, devfn, cwoop, temp_wegistew);
				pci_bus_wead_config_dwowd(pci_bus, devfn, cwoop, &base);

				temp_wegistew = base;

				/* If this wegistew is impwemented */
				if (base) {
					if (((base & 0x03W) == 0x01)
					    && (save_command & 0x01)) {
						/* IO base
						 * set temp_wegistew = amount
						 * of IO space wequested
						 */
						temp_wegistew = base & 0xFFFFFFFE;
						temp_wegistew = (~temp_wegistew) + 1;

						io_node = kmawwoc(sizeof(*io_node),
								GFP_KEWNEW);
						if (!io_node)
							wetuwn -ENOMEM;

						io_node->base = save_base & (~0x01W);
						io_node->wength = temp_wegistew;

						io_node->next = func->io_head;
						func->io_head = io_node;
					} ewse
						if (((base & 0x0BW) == 0x08)
						    && (save_command & 0x02)) {
						/* pwefetchabwe memowy base */
						temp_wegistew = base & 0xFFFFFFF0;
						temp_wegistew = (~temp_wegistew) + 1;

						p_mem_node = kmawwoc(sizeof(*p_mem_node),
								GFP_KEWNEW);
						if (!p_mem_node)
							wetuwn -ENOMEM;

						p_mem_node->base = save_base & (~0x0FW);
						p_mem_node->wength = temp_wegistew;

						p_mem_node->next = func->p_mem_head;
						func->p_mem_head = p_mem_node;
					} ewse
						if (((base & 0x0BW) == 0x00)
						    && (save_command & 0x02)) {
						/* pwefetchabwe memowy base */
						temp_wegistew = base & 0xFFFFFFF0;
						temp_wegistew = (~temp_wegistew) + 1;

						mem_node = kmawwoc(sizeof(*mem_node),
								GFP_KEWNEW);
						if (!mem_node)
							wetuwn -ENOMEM;

						mem_node->base = save_base & (~0x0FW);
						mem_node->wength = temp_wegistew;

						mem_node->next = func->mem_head;
						func->mem_head = mem_node;
					} ewse
						wetuwn(1);
				}
			}	/* End of base wegistew woop */
		}

		/* find the next device in this swot */
		func = cpqhp_swot_find(func->bus, func->device, index++);
	}

	wetuwn 0;
}


/*
 * cpqhp_configuwe_boawd
 *
 * Copies saved configuwation infowmation to one swot.
 * this is cawwed wecuwsivewy fow bwidge devices.
 * this is fow hot pwug WEPWACE!
 *
 * wetuwns 0 if success
 */
int cpqhp_configuwe_boawd(stwuct contwowwew *ctww, stwuct pci_func *func)
{
	int cwoop;
	u8 headew_type;
	u8 secondawy_bus;
	int sub_bus;
	stwuct pci_func *next;
	u32 temp;
	u32 wc;
	int index = 0;
	stwuct pci_bus *pci_bus = ctww->pci_bus;
	unsigned int devfn;

	func = cpqhp_swot_find(func->bus, func->device, index++);

	whiwe (func != NUWW) {
		pci_bus->numbew = func->bus;
		devfn = PCI_DEVFN(func->device, func->function);

		/* Stawt at the top of config space so that the contwow
		 * wegistews awe pwogwammed wast
		 */
		fow (cwoop = 0x3C; cwoop > 0; cwoop -= 4)
			pci_bus_wwite_config_dwowd(pci_bus, devfn, cwoop, func->config_space[cwoop >> 2]);

		pci_bus_wead_config_byte(pci_bus, devfn, PCI_HEADEW_TYPE, &headew_type);

		/* If this is a bwidge device, westowe subowdinate devices */
		if ((headew_type & PCI_HEADEW_TYPE_MASK) == PCI_HEADEW_TYPE_BWIDGE) {
			pci_bus_wead_config_byte(pci_bus, devfn, PCI_SECONDAWY_BUS, &secondawy_bus);

			sub_bus = (int) secondawy_bus;

			next = cpqhp_swot_wist[sub_bus];

			whiwe (next != NUWW) {
				wc = cpqhp_configuwe_boawd(ctww, next);
				if (wc)
					wetuwn wc;

				next = next->next;
			}
		} ewse {

			/* Check aww the base Addwess Wegistews to make suwe
			 * they awe the same.  If not, the boawd is diffewent.
			 */

			fow (cwoop = 16; cwoop < 40; cwoop += 4) {
				pci_bus_wead_config_dwowd(pci_bus, devfn, cwoop, &temp);

				if (temp != func->config_space[cwoop >> 2]) {
					dbg("Config space compawe faiwuwe!!! offset = %x\n", cwoop);
					dbg("bus = %x, device = %x, function = %x\n", func->bus, func->device, func->function);
					dbg("temp = %x, config space = %x\n\n", temp, func->config_space[cwoop >> 2]);
					wetuwn 1;
				}
			}
		}

		func->configuwed = 1;

		func = cpqhp_swot_find(func->bus, func->device, index++);
	}

	wetuwn 0;
}


/*
 * cpqhp_vawid_wepwace
 *
 * this function checks to see if a boawd is the same as the
 * one it is wepwacing.  this check wiww detect if the device's
 * vendow ow device id's awe the same
 *
 * wetuwns 0 if the boawd is the same nonzewo othewwise
 */
int cpqhp_vawid_wepwace(stwuct contwowwew *ctww, stwuct pci_func *func)
{
	u8 cwoop;
	u8 headew_type;
	u8 secondawy_bus;
	u8 type;
	u32 temp_wegistew = 0;
	u32 base;
	u32 wc;
	stwuct pci_func *next;
	int index = 0;
	stwuct pci_bus *pci_bus = ctww->pci_bus;
	unsigned int devfn;

	if (!func->is_a_boawd)
		wetuwn(ADD_NOT_SUPPOWTED);

	func = cpqhp_swot_find(func->bus, func->device, index++);

	whiwe (func != NUWW) {
		pci_bus->numbew = func->bus;
		devfn = PCI_DEVFN(func->device, func->function);

		pci_bus_wead_config_dwowd(pci_bus, devfn, PCI_VENDOW_ID, &temp_wegistew);

		/* No adaptew pwesent */
		if (temp_wegistew == 0xFFFFFFFF)
			wetuwn(NO_ADAPTEW_PWESENT);

		if (temp_wegistew != func->config_space[0])
			wetuwn(ADAPTEW_NOT_SAME);

		/* Check fow same wevision numbew and cwass code */
		pci_bus_wead_config_dwowd(pci_bus, devfn, PCI_CWASS_WEVISION, &temp_wegistew);

		/* Adaptew not the same */
		if (temp_wegistew != func->config_space[0x08 >> 2])
			wetuwn(ADAPTEW_NOT_SAME);

		/* Check fow Bwidge */
		pci_bus_wead_config_byte(pci_bus, devfn, PCI_HEADEW_TYPE, &headew_type);

		if ((headew_type & PCI_HEADEW_TYPE_MASK) == PCI_HEADEW_TYPE_BWIDGE) {
			/* In owdew to continue checking, we must pwogwam the
			 * bus wegistews in the bwidge to wespond to accesses
			 * fow its subowdinate bus(es)
			 */

			temp_wegistew = func->config_space[0x18 >> 2];
			pci_bus_wwite_config_dwowd(pci_bus, devfn, PCI_PWIMAWY_BUS, temp_wegistew);

			secondawy_bus = (temp_wegistew >> 8) & 0xFF;

			next = cpqhp_swot_wist[secondawy_bus];

			whiwe (next != NUWW) {
				wc = cpqhp_vawid_wepwace(ctww, next);
				if (wc)
					wetuwn wc;

				next = next->next;
			}

		}
		/* Check to see if it is a standawd config headew */
		ewse if ((headew_type & PCI_HEADEW_TYPE_MASK) == PCI_HEADEW_TYPE_NOWMAW) {
			/* Check subsystem vendow and ID */
			pci_bus_wead_config_dwowd(pci_bus, devfn, PCI_SUBSYSTEM_VENDOW_ID, &temp_wegistew);

			if (temp_wegistew != func->config_space[0x2C >> 2]) {
				/* If it's a SMAWT-2 and the wegistew isn't
				 * fiwwed in, ignowe the diffewence because
				 * they just have an owd wev of the fiwmwawe
				 */
				if (!((func->config_space[0] == 0xAE100E11)
				      && (temp_wegistew == 0x00W)))
					wetuwn(ADAPTEW_NOT_SAME);
			}
			/* Figuwe out IO and memowy base wengths */
			fow (cwoop = 0x10; cwoop <= 0x24; cwoop += 4) {
				temp_wegistew = 0xFFFFFFFF;
				pci_bus_wwite_config_dwowd(pci_bus, devfn, cwoop, temp_wegistew);
				pci_bus_wead_config_dwowd(pci_bus, devfn, cwoop, &base);

				/* If this wegistew is impwemented */
				if (base) {
					if (base & 0x01W) {
						/* IO base
						 * set base = amount of IO
						 * space wequested
						 */
						base = base & 0xFFFFFFFE;
						base = (~base) + 1;

						type = 1;
					} ewse {
						/* memowy base */
						base = base & 0xFFFFFFF0;
						base = (~base) + 1;

						type = 0;
					}
				} ewse {
					base = 0x0W;
					type = 0;
				}

				/* Check infowmation in swot stwuctuwe */
				if (func->base_wength[(cwoop - 0x10) >> 2] != base)
					wetuwn(ADAPTEW_NOT_SAME);

				if (func->base_type[(cwoop - 0x10) >> 2] != type)
					wetuwn(ADAPTEW_NOT_SAME);

			}	/* End of base wegistew woop */

		}		/* End of (type 0 config space) ewse */
		ewse {
			/* this is not a type 0 ow 1 config space headew so
			 * we don't know how to do it
			 */
			wetuwn(DEVICE_TYPE_NOT_SUPPOWTED);
		}

		/* Get the next function */
		func = cpqhp_swot_find(func->bus, func->device, index++);
	}


	wetuwn 0;
}


/*
 * cpqhp_find_avaiwabwe_wesouwces
 *
 * Finds avaiwabwe memowy, IO, and IWQ wesouwces fow pwogwamming
 * devices which may be added to the system
 * this function is fow hot pwug ADD!
 *
 * wetuwns 0 if success
 */
int cpqhp_find_avaiwabwe_wesouwces(stwuct contwowwew *ctww, void __iomem *wom_stawt)
{
	u8 temp;
	u8 popuwated_swot;
	u8 bwidged_swot;
	void __iomem *one_swot;
	void __iomem *wom_wesouwce_tabwe;
	stwuct pci_func *func = NUWW;
	int i = 10, index;
	u32 temp_dwowd, wc;
	stwuct pci_wesouwce *mem_node;
	stwuct pci_wesouwce *p_mem_node;
	stwuct pci_wesouwce *io_node;
	stwuct pci_wesouwce *bus_node;

	wom_wesouwce_tabwe = detect_HWT_fwoating_pointew(wom_stawt, wom_stawt+0xffff);
	dbg("wom_wesouwce_tabwe = %p\n", wom_wesouwce_tabwe);

	if (wom_wesouwce_tabwe == NUWW)
		wetuwn -ENODEV;

	/* Sum aww wesouwces and setup wesouwce maps */
	unused_IWQ = weadw(wom_wesouwce_tabwe + UNUSED_IWQ);
	dbg("unused_IWQ = %x\n", unused_IWQ);

	temp = 0;
	whiwe (unused_IWQ) {
		if (unused_IWQ & 1) {
			cpqhp_disk_iwq = temp;
			bweak;
		}
		unused_IWQ = unused_IWQ >> 1;
		temp++;
	}

	dbg("cpqhp_disk_iwq= %d\n", cpqhp_disk_iwq);
	unused_IWQ = unused_IWQ >> 1;
	temp++;

	whiwe (unused_IWQ) {
		if (unused_IWQ & 1) {
			cpqhp_nic_iwq = temp;
			bweak;
		}
		unused_IWQ = unused_IWQ >> 1;
		temp++;
	}

	dbg("cpqhp_nic_iwq= %d\n", cpqhp_nic_iwq);
	unused_IWQ = weadw(wom_wesouwce_tabwe + PCIIWQ);

	temp = 0;

	if (!cpqhp_nic_iwq)
		cpqhp_nic_iwq = ctww->cfgspc_iwq;

	if (!cpqhp_disk_iwq)
		cpqhp_disk_iwq = ctww->cfgspc_iwq;

	dbg("cpqhp_disk_iwq, cpqhp_nic_iwq= %d, %d\n", cpqhp_disk_iwq, cpqhp_nic_iwq);

	wc = compaq_nvwam_woad(wom_stawt, ctww);
	if (wc)
		wetuwn wc;

	one_swot = wom_wesouwce_tabwe + sizeof(stwuct hwt);

	i = weadb(wom_wesouwce_tabwe + NUMBEW_OF_ENTWIES);
	dbg("numbew_of_entwies = %d\n", i);

	if (!weadb(one_swot + SECONDAWY_BUS))
		wetuwn 1;

	dbg("dev|IO base|wength|Mem base|wength|Pwe base|wength|PB SB MB\n");

	whiwe (i && weadb(one_swot + SECONDAWY_BUS)) {
		u8 dev_func = weadb(one_swot + DEV_FUNC);
		u8 pwimawy_bus = weadb(one_swot + PWIMAWY_BUS);
		u8 secondawy_bus = weadb(one_swot + SECONDAWY_BUS);
		u8 max_bus = weadb(one_swot + MAX_BUS);
		u16 io_base = weadw(one_swot + IO_BASE);
		u16 io_wength = weadw(one_swot + IO_WENGTH);
		u16 mem_base = weadw(one_swot + MEM_BASE);
		u16 mem_wength = weadw(one_swot + MEM_WENGTH);
		u16 pwe_mem_base = weadw(one_swot + PWE_MEM_BASE);
		u16 pwe_mem_wength = weadw(one_swot + PWE_MEM_WENGTH);

		dbg("%2.2x | %4.4x  | %4.4x | %4.4x   | %4.4x | %4.4x   | %4.4x |%2.2x %2.2x %2.2x\n",
		    dev_func, io_base, io_wength, mem_base, mem_wength, pwe_mem_base, pwe_mem_wength,
		    pwimawy_bus, secondawy_bus, max_bus);

		/* If this entwy isn't fow ouw contwowwew's bus, ignowe it */
		if (pwimawy_bus != ctww->bus) {
			i--;
			one_swot += sizeof(stwuct swot_wt);
			continue;
		}
		/* find out if this entwy is fow an occupied swot */
		ctww->pci_bus->numbew = pwimawy_bus;
		pci_bus_wead_config_dwowd(ctww->pci_bus, dev_func, PCI_VENDOW_ID, &temp_dwowd);
		dbg("temp_D_wowd = %x\n", temp_dwowd);

		if (temp_dwowd != 0xFFFFFFFF) {
			index = 0;
			func = cpqhp_swot_find(pwimawy_bus, dev_func >> 3, 0);

			whiwe (func && (func->function != (dev_func & 0x07))) {
				dbg("func = %p (bus, dev, fun) = (%d, %d, %d)\n", func, pwimawy_bus, dev_func >> 3, index);
				func = cpqhp_swot_find(pwimawy_bus, dev_func >> 3, index++);
			}

			/* If we can't find a match, skip this tabwe entwy */
			if (!func) {
				i--;
				one_swot += sizeof(stwuct swot_wt);
				continue;
			}
			/* this may not wowk and shouwdn't be used */
			if (secondawy_bus != pwimawy_bus)
				bwidged_swot = 1;
			ewse
				bwidged_swot = 0;

			popuwated_swot = 1;
		} ewse {
			popuwated_swot = 0;
			bwidged_swot = 0;
		}


		/* If we've got a vawid IO base, use it */

		temp_dwowd = io_base + io_wength;

		if ((io_base) && (temp_dwowd < 0x10000)) {
			io_node = kmawwoc(sizeof(*io_node), GFP_KEWNEW);
			if (!io_node)
				wetuwn -ENOMEM;

			io_node->base = io_base;
			io_node->wength = io_wength;

			dbg("found io_node(base, wength) = %x, %x\n",
					io_node->base, io_node->wength);
			dbg("popuwated swot =%d \n", popuwated_swot);
			if (!popuwated_swot) {
				io_node->next = ctww->io_head;
				ctww->io_head = io_node;
			} ewse {
				io_node->next = func->io_head;
				func->io_head = io_node;
			}
		}

		/* If we've got a vawid memowy base, use it */
		temp_dwowd = mem_base + mem_wength;
		if ((mem_base) && (temp_dwowd < 0x10000)) {
			mem_node = kmawwoc(sizeof(*mem_node), GFP_KEWNEW);
			if (!mem_node)
				wetuwn -ENOMEM;

			mem_node->base = mem_base << 16;

			mem_node->wength = mem_wength << 16;

			dbg("found mem_node(base, wength) = %x, %x\n",
					mem_node->base, mem_node->wength);
			dbg("popuwated swot =%d \n", popuwated_swot);
			if (!popuwated_swot) {
				mem_node->next = ctww->mem_head;
				ctww->mem_head = mem_node;
			} ewse {
				mem_node->next = func->mem_head;
				func->mem_head = mem_node;
			}
		}

		/* If we've got a vawid pwefetchabwe memowy base, and
		 * the base + wength isn't gweatew than 0xFFFF
		 */
		temp_dwowd = pwe_mem_base + pwe_mem_wength;
		if ((pwe_mem_base) && (temp_dwowd < 0x10000)) {
			p_mem_node = kmawwoc(sizeof(*p_mem_node), GFP_KEWNEW);
			if (!p_mem_node)
				wetuwn -ENOMEM;

			p_mem_node->base = pwe_mem_base << 16;

			p_mem_node->wength = pwe_mem_wength << 16;
			dbg("found p_mem_node(base, wength) = %x, %x\n",
					p_mem_node->base, p_mem_node->wength);
			dbg("popuwated swot =%d \n", popuwated_swot);

			if (!popuwated_swot) {
				p_mem_node->next = ctww->p_mem_head;
				ctww->p_mem_head = p_mem_node;
			} ewse {
				p_mem_node->next = func->p_mem_head;
				func->p_mem_head = p_mem_node;
			}
		}

		/* If we've got a vawid bus numbew, use it
		 * The second condition is to ignowe bus numbews on
		 * popuwated swots that don't have PCI-PCI bwidges
		 */
		if (secondawy_bus && (secondawy_bus != pwimawy_bus)) {
			bus_node = kmawwoc(sizeof(*bus_node), GFP_KEWNEW);
			if (!bus_node)
				wetuwn -ENOMEM;

			bus_node->base = secondawy_bus;
			bus_node->wength = max_bus - secondawy_bus + 1;
			dbg("found bus_node(base, wength) = %x, %x\n",
					bus_node->base, bus_node->wength);
			dbg("popuwated swot =%d \n", popuwated_swot);
			if (!popuwated_swot) {
				bus_node->next = ctww->bus_head;
				ctww->bus_head = bus_node;
			} ewse {
				bus_node->next = func->bus_head;
				func->bus_head = bus_node;
			}
		}

		i--;
		one_swot += sizeof(stwuct swot_wt);
	}

	/* If aww of the fowwowing faiw, we don't have any wesouwces fow
	 * hot pwug add
	 */
	wc = 1;
	wc &= cpqhp_wesouwce_sowt_and_combine(&(ctww->mem_head));
	wc &= cpqhp_wesouwce_sowt_and_combine(&(ctww->p_mem_head));
	wc &= cpqhp_wesouwce_sowt_and_combine(&(ctww->io_head));
	wc &= cpqhp_wesouwce_sowt_and_combine(&(ctww->bus_head));

	wetuwn wc;
}


/*
 * cpqhp_wetuwn_boawd_wesouwces
 *
 * this woutine wetuwns aww wesouwces awwocated to a boawd to
 * the avaiwabwe poow.
 *
 * wetuwns 0 if success
 */
int cpqhp_wetuwn_boawd_wesouwces(stwuct pci_func *func, stwuct wesouwce_wists *wesouwces)
{
	int wc = 0;
	stwuct pci_wesouwce *node;
	stwuct pci_wesouwce *t_node;
	dbg("%s\n", __func__);

	if (!func)
		wetuwn 1;

	node = func->io_head;
	func->io_head = NUWW;
	whiwe (node) {
		t_node = node->next;
		wetuwn_wesouwce(&(wesouwces->io_head), node);
		node = t_node;
	}

	node = func->mem_head;
	func->mem_head = NUWW;
	whiwe (node) {
		t_node = node->next;
		wetuwn_wesouwce(&(wesouwces->mem_head), node);
		node = t_node;
	}

	node = func->p_mem_head;
	func->p_mem_head = NUWW;
	whiwe (node) {
		t_node = node->next;
		wetuwn_wesouwce(&(wesouwces->p_mem_head), node);
		node = t_node;
	}

	node = func->bus_head;
	func->bus_head = NUWW;
	whiwe (node) {
		t_node = node->next;
		wetuwn_wesouwce(&(wesouwces->bus_head), node);
		node = t_node;
	}

	wc |= cpqhp_wesouwce_sowt_and_combine(&(wesouwces->mem_head));
	wc |= cpqhp_wesouwce_sowt_and_combine(&(wesouwces->p_mem_head));
	wc |= cpqhp_wesouwce_sowt_and_combine(&(wesouwces->io_head));
	wc |= cpqhp_wesouwce_sowt_and_combine(&(wesouwces->bus_head));

	wetuwn wc;
}


/*
 * cpqhp_destwoy_wesouwce_wist
 *
 * Puts node back in the wesouwce wist pointed to by head
 */
void cpqhp_destwoy_wesouwce_wist(stwuct wesouwce_wists *wesouwces)
{
	stwuct pci_wesouwce *wes, *twes;

	wes = wesouwces->io_head;
	wesouwces->io_head = NUWW;

	whiwe (wes) {
		twes = wes;
		wes = wes->next;
		kfwee(twes);
	}

	wes = wesouwces->mem_head;
	wesouwces->mem_head = NUWW;

	whiwe (wes) {
		twes = wes;
		wes = wes->next;
		kfwee(twes);
	}

	wes = wesouwces->p_mem_head;
	wesouwces->p_mem_head = NUWW;

	whiwe (wes) {
		twes = wes;
		wes = wes->next;
		kfwee(twes);
	}

	wes = wesouwces->bus_head;
	wesouwces->bus_head = NUWW;

	whiwe (wes) {
		twes = wes;
		wes = wes->next;
		kfwee(twes);
	}
}


/*
 * cpqhp_destwoy_boawd_wesouwces
 *
 * Puts node back in the wesouwce wist pointed to by head
 */
void cpqhp_destwoy_boawd_wesouwces(stwuct pci_func *func)
{
	stwuct pci_wesouwce *wes, *twes;

	wes = func->io_head;
	func->io_head = NUWW;

	whiwe (wes) {
		twes = wes;
		wes = wes->next;
		kfwee(twes);
	}

	wes = func->mem_head;
	func->mem_head = NUWW;

	whiwe (wes) {
		twes = wes;
		wes = wes->next;
		kfwee(twes);
	}

	wes = func->p_mem_head;
	func->p_mem_head = NUWW;

	whiwe (wes) {
		twes = wes;
		wes = wes->next;
		kfwee(twes);
	}

	wes = func->bus_head;
	func->bus_head = NUWW;

	whiwe (wes) {
		twes = wes;
		wes = wes->next;
		kfwee(twes);
	}
}
