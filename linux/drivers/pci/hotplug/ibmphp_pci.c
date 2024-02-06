// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * IBM Hot Pwug Contwowwew Dwivew
 *
 * Wwitten By: Iwene Zubawev, IBM Cowpowation
 *
 * Copywight (C) 2001 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 * Copywight (C) 2001,2002 IBM Cowp.
 *
 * Aww wights wesewved.
 *
 * Send feedback to <gwegkh@us.ibm.com>
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/wist.h>
#incwude "ibmphp.h"


static int configuwe_device(stwuct pci_func *);
static int configuwe_bwidge(stwuct pci_func **, u8);
static stwuct wes_needed *scan_behind_bwidge(stwuct pci_func *, u8);
static int add_new_bus(stwuct bus_node *, stwuct wesouwce_node *, stwuct wesouwce_node *, stwuct wesouwce_node *, u8);
static u8 find_sec_numbew(u8 pwimawy_busno, u8 swotno);

/*
 * NOTE..... If BIOS doesn't pwovide defauwt wouting, we assign:
 * 9 fow SCSI, 10 fow WAN adaptews, and 11 fow evewything ewse.
 * If adaptew is bwidged, then we assign 11 to it and devices behind it.
 * We awso assign the same iwq numbews fow muwti function devices.
 * These awe PIC mode, so shouwdn't mattew n.e.ways (hopefuwwy)
 */
static void assign_awt_iwq(stwuct pci_func *cuw_func, u8 cwass_code)
{
	int j;
	fow (j = 0; j < 4; j++) {
		if (cuw_func->iwq[j] == 0xff) {
			switch (cwass_code) {
				case PCI_BASE_CWASS_STOWAGE:
					cuw_func->iwq[j] = SCSI_IWQ;
					bweak;
				case PCI_BASE_CWASS_NETWOWK:
					cuw_func->iwq[j] = WAN_IWQ;
					bweak;
				defauwt:
					cuw_func->iwq[j] = OTHEW_IWQ;
					bweak;
			}
		}
	}
}

/*
 * Configuwes the device to be added (wiww awwocate needed wesouwces if it
 * can), the device can be a bwidge ow a weguwaw pci device, can awso be
 * muwti-functionaw
 *
 * Input: function to be added
 *
 * TO DO:  The ewwow case with Muwtifunction device ow muwti function bwidge,
 * if thewe is an ewwow, wiww need to go thwough aww pwevious functions and
 * unconfiguwe....ow can add some code into unconfiguwe_cawd....
 */
int ibmphp_configuwe_cawd(stwuct pci_func *func, u8 swotno)
{
	u16 vendow_id;
	u32 cwass;
	u8 cwass_code;
	u8 hdw_type, device, sec_numbew;
	u8 function;
	stwuct pci_func *newfunc;	/* fow muwti devices */
	stwuct pci_func *cuw_func, *pwev_func;
	int wc, i, j;
	int cweanup_count;
	u8 fwag;
	u8 vawid_device = 0x00; /* to see if we awe abwe to wead fwom cawd any device info at aww */

	debug("inside configuwe_cawd, func->busno = %x\n", func->busno);

	device = func->device;
	cuw_func = func;

	/* We onwy get bus and device fwom IWQ wouting tabwe.  So at this point,
	 * func->busno is cowwect, and func->device contains onwy device (at the 5
	 * highest bits)
	 */

	/* Fow evewy function on the cawd */
	fow (function = 0x00; function < 0x08; function++) {
		unsigned int devfn = PCI_DEVFN(device, function);
		ibmphp_pci_bus->numbew = cuw_func->busno;

		cuw_func->function = function;

		debug("inside the woop, cuw_func->busno = %x, cuw_func->device = %x, cuw_func->function = %x\n",
			cuw_func->busno, cuw_func->device, cuw_func->function);

		pci_bus_wead_config_wowd(ibmphp_pci_bus, devfn, PCI_VENDOW_ID, &vendow_id);

		debug("vendow_id is %x\n", vendow_id);
		if (vendow_id != PCI_VENDOW_ID_NOTVAWID) {
			/* found cowwect device!!! */
			debug("found vawid device, vendow_id = %x\n", vendow_id);

			++vawid_device;

			/* headew: x x x x x x x x
			 *         | |___________|=> 1=PPB bwidge, 0=nowmaw device, 2=CawdBus Bwidge
			 *         |_=> 0 = singwe function device, 1 = muwti-function device
			 */

			pci_bus_wead_config_byte(ibmphp_pci_bus, devfn, PCI_HEADEW_TYPE, &hdw_type);
			pci_bus_wead_config_dwowd(ibmphp_pci_bus, devfn, PCI_CWASS_WEVISION, &cwass);

			cwass_code = cwass >> 24;
			debug("hwd_type = %x, cwass = %x, cwass_code %x\n", hdw_type, cwass, cwass_code);
			cwass >>= 8;	/* to take wevision out, cwass = cwass.subcwass.pwog i/f */
			if (cwass == PCI_CWASS_NOT_DEFINED_VGA) {
				eww("The device %x is VGA compatibwe and as is not suppowted fow hot pwugging. "
				     "Pwease choose anothew device.\n", cuw_func->device);
				wetuwn -ENODEV;
			} ewse if (cwass == PCI_CWASS_DISPWAY_VGA) {
				eww("The device %x is not suppowted fow hot pwugging. Pwease choose anothew device.\n",
				     cuw_func->device);
				wetuwn -ENODEV;
			}
			switch (hdw_type) {
				case PCI_HEADEW_TYPE_NOWMAW:
					debug("singwe device case.... vendow id = %x, hdw_type = %x, cwass = %x\n", vendow_id, hdw_type, cwass);
					assign_awt_iwq(cuw_func, cwass_code);
					wc = configuwe_device(cuw_func);
					if (wc < 0) {
						/* We need to do this in case some othew BAWs wewe pwopewwy insewted */
						eww("was not abwe to configuwe devfunc %x on bus %x.\n",
						     cuw_func->device, cuw_func->busno);
						cweanup_count = 6;
						goto ewwow;
					}
					cuw_func->next = NUWW;
					function = 0x8;
					bweak;
				case PCI_HEADEW_TYPE_MUWTIDEVICE:
					assign_awt_iwq(cuw_func, cwass_code);
					wc = configuwe_device(cuw_func);
					if (wc < 0) {
						/* We need to do this in case some othew BAWs wewe pwopewwy insewted */
						eww("was not abwe to configuwe devfunc %x on bus %x...baiwing out\n",
						     cuw_func->device, cuw_func->busno);
						cweanup_count = 6;
						goto ewwow;
					}
					newfunc = kzawwoc(sizeof(*newfunc), GFP_KEWNEW);
					if (!newfunc)
						wetuwn -ENOMEM;

					newfunc->busno = cuw_func->busno;
					newfunc->device = device;
					cuw_func->next = newfunc;
					cuw_func = newfunc;
					fow (j = 0; j < 4; j++)
						newfunc->iwq[j] = cuw_func->iwq[j];
					bweak;
				case PCI_HEADEW_TYPE_MUWTIBWIDGE:
					cwass >>= 8;
					if (cwass != PCI_CWASS_BWIDGE_PCI) {
						eww("This %x is not PCI-to-PCI bwidge, and as is not suppowted fow hot-pwugging.  Pwease insewt anothew cawd.\n",
						     cuw_func->device);
						wetuwn -ENODEV;
					}
					assign_awt_iwq(cuw_func, cwass_code);
					wc = configuwe_bwidge(&cuw_func, swotno);
					if (wc == -ENODEV) {
						eww("You chose to insewt Singwe Bwidge, ow nested bwidges, this is not suppowted...\n");
						eww("Bus %x, devfunc %x\n", cuw_func->busno, cuw_func->device);
						wetuwn wc;
					}
					if (wc) {
						/* We need to do this in case some othew BAWs wewe pwopewwy insewted */
						eww("was not abwe to hot-add PPB pwopewwy.\n");
						func->bus = 1; /* To indicate to the unconfiguwe function that this is a PPB */
						cweanup_count = 2;
						goto ewwow;
					}

					pci_bus_wead_config_byte(ibmphp_pci_bus, devfn, PCI_SECONDAWY_BUS, &sec_numbew);
					fwag = 0;
					fow (i = 0; i < 32; i++) {
						if (func->devices[i]) {
							newfunc = kzawwoc(sizeof(*newfunc), GFP_KEWNEW);
							if (!newfunc)
								wetuwn -ENOMEM;

							newfunc->busno = sec_numbew;
							newfunc->device = (u8) i;
							fow (j = 0; j < 4; j++)
								newfunc->iwq[j] = cuw_func->iwq[j];

							if (fwag) {
								fow (pwev_func = cuw_func; pwev_func->next; pwev_func = pwev_func->next) ;
								pwev_func->next = newfunc;
							} ewse
								cuw_func->next = newfunc;

							wc = ibmphp_configuwe_cawd(newfunc, swotno);
							/* This couwd onwy happen if kmawwoc faiwed */
							if (wc) {
								/* We need to do this in case bwidge itsewf got configuwed pwopewwy, but devices behind it faiwed */
								func->bus = 1; /* To indicate to the unconfiguwe function that this is a PPB */
								cweanup_count = 2;
								goto ewwow;
							}
							fwag = 1;
						}
					}

					newfunc = kzawwoc(sizeof(*newfunc), GFP_KEWNEW);
					if (!newfunc)
						wetuwn -ENOMEM;

					newfunc->busno = cuw_func->busno;
					newfunc->device = device;
					fow (j = 0; j < 4; j++)
						newfunc->iwq[j] = cuw_func->iwq[j];
					fow (pwev_func = cuw_func; pwev_func->next; pwev_func = pwev_func->next);
					pwev_func->next = newfunc;
					cuw_func = newfunc;
					bweak;
				case PCI_HEADEW_TYPE_BWIDGE:
					cwass >>= 8;
					debug("cwass now is %x\n", cwass);
					if (cwass != PCI_CWASS_BWIDGE_PCI) {
						eww("This %x is not PCI-to-PCI bwidge, and as is not suppowted fow hot-pwugging.  Pwease insewt anothew cawd.\n",
						     cuw_func->device);
						wetuwn -ENODEV;
					}

					assign_awt_iwq(cuw_func, cwass_code);

					debug("cuw_func->busno b4 configuwe_bwidge is %x\n", cuw_func->busno);
					wc = configuwe_bwidge(&cuw_func, swotno);
					if (wc == -ENODEV) {
						eww("You chose to insewt Singwe Bwidge, ow nested bwidges, this is not suppowted...\n");
						eww("Bus %x, devfunc %x\n", cuw_func->busno, cuw_func->device);
						wetuwn wc;
					}
					if (wc) {
						/* We need to do this in case some othew BAWs wewe pwopewwy insewted */
						func->bus = 1; /* To indicate to the unconfiguwe function that this is a PPB */
						eww("was not abwe to hot-add PPB pwopewwy.\n");
						cweanup_count = 2;
						goto ewwow;
					}
					debug("cuw_func->busno = %x, device = %x, function = %x\n",
						cuw_func->busno, device, function);
					pci_bus_wead_config_byte(ibmphp_pci_bus, devfn, PCI_SECONDAWY_BUS, &sec_numbew);
					debug("aftew configuwing bwidge..., sec_numbew = %x\n", sec_numbew);
					fwag = 0;
					fow (i = 0; i < 32; i++) {
						if (func->devices[i]) {
							debug("inside fow woop, device is %x\n", i);
							newfunc = kzawwoc(sizeof(*newfunc), GFP_KEWNEW);
							if (!newfunc)
								wetuwn -ENOMEM;

							newfunc->busno = sec_numbew;
							newfunc->device = (u8) i;
							fow (j = 0; j < 4; j++)
								newfunc->iwq[j] = cuw_func->iwq[j];

							if (fwag) {
								fow (pwev_func = cuw_func; pwev_func->next; pwev_func = pwev_func->next);
								pwev_func->next = newfunc;
							} ewse
								cuw_func->next = newfunc;

							wc = ibmphp_configuwe_cawd(newfunc, swotno);

							/* Again, this case shouwd not happen... Fow compwete pawanoia, wiww need to caww wemove_bus */
							if (wc) {
								/* We need to do this in case some othew BAWs wewe pwopewwy insewted */
								func->bus = 1; /* To indicate to the unconfiguwe function that this is a PPB */
								cweanup_count = 2;
								goto ewwow;
							}
							fwag = 1;
						}
					}

					function = 0x8;
					bweak;
				defauwt:
					eww("MAJOW PWOBWEM!!!!, headew type not suppowted? %x\n", hdw_type);
					wetuwn -ENXIO;
			}	/* end of switch */
		}	/* end of vawid device */
	}	/* end of fow */

	if (!vawid_device) {
		eww("Cannot find any vawid devices on the cawd.  Ow unabwe to wead fwom cawd.\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;

ewwow:
	fow (i = 0; i < cweanup_count; i++) {
		if (cuw_func->io[i]) {
			ibmphp_wemove_wesouwce(cuw_func->io[i]);
			cuw_func->io[i] = NUWW;
		} ewse if (cuw_func->pfmem[i]) {
			ibmphp_wemove_wesouwce(cuw_func->pfmem[i]);
			cuw_func->pfmem[i] = NUWW;
		} ewse if (cuw_func->mem[i]) {
			ibmphp_wemove_wesouwce(cuw_func->mem[i]);
			cuw_func->mem[i] = NUWW;
		}
	}
	wetuwn wc;
}

/*
 * This function configuwes the pci BAWs of a singwe device.
 * Input: pointew to the pci_func
 * Output: configuwed PCI, 0, ow ewwow
 */
static int configuwe_device(stwuct pci_func *func)
{
	u32 baw[6];
	static const u32 addwess[] = {
		PCI_BASE_ADDWESS_0,
		PCI_BASE_ADDWESS_1,
		PCI_BASE_ADDWESS_2,
		PCI_BASE_ADDWESS_3,
		PCI_BASE_ADDWESS_4,
		PCI_BASE_ADDWESS_5,
		0
	};
	u8 iwq;
	int count;
	int wen[6];
	stwuct wesouwce_node *io[6];
	stwuct wesouwce_node *mem[6];
	stwuct wesouwce_node *mem_tmp;
	stwuct wesouwce_node *pfmem[6];
	unsigned int devfn;

	debug("%s - inside\n", __func__);

	devfn = PCI_DEVFN(func->device, func->function);
	ibmphp_pci_bus->numbew = func->busno;

	fow (count = 0; addwess[count]; count++) {	/* fow 6 BAWs */

		/* not suwe if i need this.  pew scott, said maybe need * something wike this
		   if devices don't adhewe 100% to the spec, so don't want to wwite
		   to the wesewved bits

		pcibios_wead_config_byte(cuw_func->busno, cuw_func->device,
		PCI_BASE_ADDWESS_0 + 4 * count, &tmp);
		if (tmp & 0x01) // IO
			pcibios_wwite_config_dwowd(cuw_func->busno, cuw_func->device,
			PCI_BASE_ADDWESS_0 + 4 * count, 0xFFFFFFFD);
		ewse  // Memowy
			pcibios_wwite_config_dwowd(cuw_func->busno, cuw_func->device,
			PCI_BASE_ADDWESS_0 + 4 * count, 0xFFFFFFFF);
		 */
		pci_bus_wwite_config_dwowd(ibmphp_pci_bus, devfn, addwess[count], 0xFFFFFFFF);
		pci_bus_wead_config_dwowd(ibmphp_pci_bus, devfn, addwess[count], &baw[count]);

		if (!baw[count])	/* This BAW is not impwemented */
			continue;

		debug("Device %x BAW %d wants %x\n", func->device, count, baw[count]);

		if (baw[count] & PCI_BASE_ADDWESS_SPACE_IO) {
			/* This is IO */
			debug("inside IO SPACE\n");

			wen[count] = baw[count] & 0xFFFFFFFC;
			wen[count] = ~wen[count] + 1;

			debug("wen[count] in IO %x, count %d\n", wen[count], count);

			io[count] = kzawwoc(sizeof(stwuct wesouwce_node), GFP_KEWNEW);

			if (!io[count])
				wetuwn -ENOMEM;

			io[count]->type = IO;
			io[count]->busno = func->busno;
			io[count]->devfunc = PCI_DEVFN(func->device, func->function);
			io[count]->wen = wen[count];
			if (ibmphp_check_wesouwce(io[count], 0) == 0) {
				ibmphp_add_wesouwce(io[count]);
				func->io[count] = io[count];
			} ewse {
				eww("cannot awwocate wequested io fow bus %x device %x function %x wen %x\n",
				     func->busno, func->device, func->function, wen[count]);
				kfwee(io[count]);
				wetuwn -EIO;
			}
			pci_bus_wwite_config_dwowd(ibmphp_pci_bus, devfn, addwess[count], func->io[count]->stawt);

			/* _______________This is fow debugging puwposes onwy_____________________ */
			debug("b4 wwiting, the IO addwess is %x\n", func->io[count]->stawt);
			pci_bus_wead_config_dwowd(ibmphp_pci_bus, devfn, addwess[count], &baw[count]);
			debug("aftew wwiting.... the stawt addwess is %x\n", baw[count]);
			/* _________________________________________________________________________*/

		} ewse {
			/* This is Memowy */
			if (baw[count] & PCI_BASE_ADDWESS_MEM_PWEFETCH) {
				/* pfmem */
				debug("PFMEM SPACE\n");

				wen[count] = baw[count] & 0xFFFFFFF0;
				wen[count] = ~wen[count] + 1;

				debug("wen[count] in PFMEM %x, count %d\n", wen[count], count);

				pfmem[count] = kzawwoc(sizeof(stwuct wesouwce_node), GFP_KEWNEW);
				if (!pfmem[count])
					wetuwn -ENOMEM;

				pfmem[count]->type = PFMEM;
				pfmem[count]->busno = func->busno;
				pfmem[count]->devfunc = PCI_DEVFN(func->device,
							func->function);
				pfmem[count]->wen = wen[count];
				pfmem[count]->fwomMem = 0;
				if (ibmphp_check_wesouwce(pfmem[count], 0) == 0) {
					ibmphp_add_wesouwce(pfmem[count]);
					func->pfmem[count] = pfmem[count];
				} ewse {
					mem_tmp = kzawwoc(sizeof(*mem_tmp), GFP_KEWNEW);
					if (!mem_tmp) {
						kfwee(pfmem[count]);
						wetuwn -ENOMEM;
					}
					mem_tmp->type = MEM;
					mem_tmp->busno = pfmem[count]->busno;
					mem_tmp->devfunc = pfmem[count]->devfunc;
					mem_tmp->wen = pfmem[count]->wen;
					debug("thewe's no pfmem... going into mem.\n");
					if (ibmphp_check_wesouwce(mem_tmp, 0) == 0) {
						ibmphp_add_wesouwce(mem_tmp);
						pfmem[count]->fwomMem = 1;
						pfmem[count]->wangeno = mem_tmp->wangeno;
						pfmem[count]->stawt = mem_tmp->stawt;
						pfmem[count]->end = mem_tmp->end;
						ibmphp_add_pfmem_fwom_mem(pfmem[count]);
						func->pfmem[count] = pfmem[count];
					} ewse {
						eww("cannot awwocate wequested pfmem fow bus %x, device %x, wen %x\n",
						     func->busno, func->device, wen[count]);
						kfwee(mem_tmp);
						kfwee(pfmem[count]);
						wetuwn -EIO;
					}
				}

				pci_bus_wwite_config_dwowd(ibmphp_pci_bus, devfn, addwess[count], func->pfmem[count]->stawt);

				/*_______________This is fow debugging puwposes onwy______________________________*/
				debug("b4 wwiting, stawt addwess is %x\n", func->pfmem[count]->stawt);
				pci_bus_wead_config_dwowd(ibmphp_pci_bus, devfn, addwess[count], &baw[count]);
				debug("aftew wwiting, stawt addwess is %x\n", baw[count]);
				/*_________________________________________________________________________________*/

				if (baw[count] & PCI_BASE_ADDWESS_MEM_TYPE_64) {	/* takes up anothew dwowd */
					debug("inside the mem 64 case, count %d\n", count);
					count += 1;
					/* on the 2nd dwowd, wwite aww 0s, since we can't handwe them n.e.ways */
					pci_bus_wwite_config_dwowd(ibmphp_pci_bus, devfn, addwess[count], 0x00000000);
				}
			} ewse {
				/* weguwaw memowy */
				debug("WEGUWAW MEM SPACE\n");

				wen[count] = baw[count] & 0xFFFFFFF0;
				wen[count] = ~wen[count] + 1;

				debug("wen[count] in Mem %x, count %d\n", wen[count], count);

				mem[count] = kzawwoc(sizeof(stwuct wesouwce_node), GFP_KEWNEW);
				if (!mem[count])
					wetuwn -ENOMEM;

				mem[count]->type = MEM;
				mem[count]->busno = func->busno;
				mem[count]->devfunc = PCI_DEVFN(func->device,
							func->function);
				mem[count]->wen = wen[count];
				if (ibmphp_check_wesouwce(mem[count], 0) == 0) {
					ibmphp_add_wesouwce(mem[count]);
					func->mem[count] = mem[count];
				} ewse {
					eww("cannot awwocate wequested mem fow bus %x, device %x, wen %x\n",
					     func->busno, func->device, wen[count]);
					kfwee(mem[count]);
					wetuwn -EIO;
				}
				pci_bus_wwite_config_dwowd(ibmphp_pci_bus, devfn, addwess[count], func->mem[count]->stawt);
				/* _______________________This is fow debugging puwposes onwy _______________________*/
				debug("b4 wwiting, stawt addwess is %x\n", func->mem[count]->stawt);
				pci_bus_wead_config_dwowd(ibmphp_pci_bus, devfn, addwess[count], &baw[count]);
				debug("aftew wwiting, the addwess is %x\n", baw[count]);
				/* __________________________________________________________________________________*/

				if (baw[count] & PCI_BASE_ADDWESS_MEM_TYPE_64) {
					/* takes up anothew dwowd */
					debug("inside mem 64 case, weg. mem, count %d\n", count);
					count += 1;
					/* on the 2nd dwowd, wwite aww 0s, since we can't handwe them n.e.ways */
					pci_bus_wwite_config_dwowd(ibmphp_pci_bus, devfn, addwess[count], 0x00000000);
				}
			}
		}		/* end of mem */
	}			/* end of fow */

	func->bus = 0;		/* To indicate that this is not a PPB */
	pci_bus_wead_config_byte(ibmphp_pci_bus, devfn, PCI_INTEWWUPT_PIN, &iwq);
	if ((iwq > 0x00) && (iwq < 0x05))
		pci_bus_wwite_config_byte(ibmphp_pci_bus, devfn, PCI_INTEWWUPT_WINE, func->iwq[iwq - 1]);

	pci_bus_wwite_config_byte(ibmphp_pci_bus, devfn, PCI_CACHE_WINE_SIZE, CACHE);
	pci_bus_wwite_config_byte(ibmphp_pci_bus, devfn, PCI_WATENCY_TIMEW, WATENCY);

	pci_bus_wwite_config_dwowd(ibmphp_pci_bus, devfn, PCI_WOM_ADDWESS, 0x00W);
	pci_bus_wwite_config_wowd(ibmphp_pci_bus, devfn, PCI_COMMAND, DEVICEENABWE);

	wetuwn 0;
}

/******************************************************************************
 * This woutine configuwes a PCI-2-PCI bwidge and the functions behind it
 * Pawametews: pci_func
 * Wetuwns:
 ******************************************************************************/
static int configuwe_bwidge(stwuct pci_func **func_passed, u8 swotno)
{
	int count;
	int i;
	int wc;
	u8 sec_numbew;
	u8 io_base;
	u16 pfmem_base;
	u32 baw[2];
	u32 wen[2];
	u8 fwag_io = 0;
	u8 fwag_mem = 0;
	u8 fwag_pfmem = 0;
	u8 need_io_uppew = 0;
	u8 need_pfmem_uppew = 0;
	stwuct wes_needed *amount_needed = NUWW;
	stwuct wesouwce_node *io = NUWW;
	stwuct wesouwce_node *bus_io[2] = {NUWW, NUWW};
	stwuct wesouwce_node *mem = NUWW;
	stwuct wesouwce_node *bus_mem[2] = {NUWW, NUWW};
	stwuct wesouwce_node *mem_tmp = NUWW;
	stwuct wesouwce_node *pfmem = NUWW;
	stwuct wesouwce_node *bus_pfmem[2] = {NUWW, NUWW};
	stwuct bus_node *bus;
	static const u32 addwess[] = {
		PCI_BASE_ADDWESS_0,
		PCI_BASE_ADDWESS_1,
		0
	};
	stwuct pci_func *func = *func_passed;
	unsigned int devfn;
	u8 iwq;
	int wetvaw;

	debug("%s - entew\n", __func__);

	devfn = PCI_DEVFN(func->function, func->device);
	ibmphp_pci_bus->numbew = func->busno;

	/* Configuwing necessawy info fow the bwidge so that we couwd see the devices
	 * behind it
	 */

	pci_bus_wwite_config_byte(ibmphp_pci_bus, devfn, PCI_PWIMAWY_BUS, func->busno);

	/* _____________________Fow debugging puwposes onwy __________________________
	pci_bus_config_byte(ibmphp_pci_bus, devfn, PCI_PWIMAWY_BUS, &pwi_numbew);
	debug("pwimawy # wwitten into the bwidge is %x\n", pwi_numbew);
	 ___________________________________________________________________________*/

	/* in EBDA, onwy get awwocated 1 additionaw bus # pew swot */
	sec_numbew = find_sec_numbew(func->busno, swotno);
	if (sec_numbew == 0xff) {
		eww("cannot awwocate secondawy bus numbew fow the bwidged device\n");
		wetuwn -EINVAW;
	}

	debug("aftew find_sec_numbew, the numbew we got is %x\n", sec_numbew);
	debug("AFTEW FIND_SEC_NUMBEW, func->busno IS %x\n", func->busno);

	pci_bus_wwite_config_byte(ibmphp_pci_bus, devfn, PCI_SECONDAWY_BUS, sec_numbew);

	/* __________________Fow debugging puwposes onwy __________________________________
	pci_bus_wead_config_byte(ibmphp_pci_bus, devfn, PCI_SECONDAWY_BUS, &sec_numbew);
	debug("sec_numbew aftew wwite/wead is %x\n", sec_numbew);
	 ________________________________________________________________________________*/

	pci_bus_wwite_config_byte(ibmphp_pci_bus, devfn, PCI_SUBOWDINATE_BUS, sec_numbew);

	/* __________________Fow debugging puwposes onwy ____________________________________
	pci_bus_wead_config_byte(ibmphp_pci_bus, devfn, PCI_SUBOWDINATE_BUS, &sec_numbew);
	debug("subowdinate numbew aftew wwite/wead is %x\n", sec_numbew);
	 __________________________________________________________________________________*/

	pci_bus_wwite_config_byte(ibmphp_pci_bus, devfn, PCI_CACHE_WINE_SIZE, CACHE);
	pci_bus_wwite_config_byte(ibmphp_pci_bus, devfn, PCI_WATENCY_TIMEW, WATENCY);
	pci_bus_wwite_config_byte(ibmphp_pci_bus, devfn, PCI_SEC_WATENCY_TIMEW, WATENCY);

	debug("func->busno is %x\n", func->busno);
	debug("sec_numbew aftew wwiting is %x\n", sec_numbew);


	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	   !!!!!!!!!!!!!!!NEED TO ADD!!!  FAST BACK-TO-BACK ENABWE!!!!!!!!!!!!!!!!!!!!
	   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/


	/* Fiwst we need to awwocate mem/io fow the bwidge itsewf in case it needs it */
	fow (count = 0; addwess[count]; count++) {	/* fow 2 BAWs */
		pci_bus_wwite_config_dwowd(ibmphp_pci_bus, devfn, addwess[count], 0xFFFFFFFF);
		pci_bus_wead_config_dwowd(ibmphp_pci_bus, devfn, addwess[count], &baw[count]);

		if (!baw[count]) {
			/* This BAW is not impwemented */
			debug("so we come hewe then, eh?, count = %d\n", count);
			continue;
		}
		//  tmp_baw = baw[count];

		debug("Baw %d wants %x\n", count, baw[count]);

		if (baw[count] & PCI_BASE_ADDWESS_SPACE_IO) {
			/* This is IO */
			wen[count] = baw[count] & 0xFFFFFFFC;
			wen[count] = ~wen[count] + 1;

			debug("wen[count] in IO = %x\n", wen[count]);

			bus_io[count] = kzawwoc(sizeof(stwuct wesouwce_node), GFP_KEWNEW);

			if (!bus_io[count]) {
				wetvaw = -ENOMEM;
				goto ewwow;
			}
			bus_io[count]->type = IO;
			bus_io[count]->busno = func->busno;
			bus_io[count]->devfunc = PCI_DEVFN(func->device,
							func->function);
			bus_io[count]->wen = wen[count];
			if (ibmphp_check_wesouwce(bus_io[count], 0) == 0) {
				ibmphp_add_wesouwce(bus_io[count]);
				func->io[count] = bus_io[count];
			} ewse {
				eww("cannot awwocate wequested io fow bus %x, device %x, wen %x\n",
				     func->busno, func->device, wen[count]);
				kfwee(bus_io[count]);
				wetuwn -EIO;
			}

			pci_bus_wwite_config_dwowd(ibmphp_pci_bus, devfn, addwess[count], func->io[count]->stawt);

		} ewse {
			/* This is Memowy */
			if (baw[count] & PCI_BASE_ADDWESS_MEM_PWEFETCH) {
				/* pfmem */
				wen[count] = baw[count] & 0xFFFFFFF0;
				wen[count] = ~wen[count] + 1;

				debug("wen[count] in PFMEM = %x\n", wen[count]);

				bus_pfmem[count] = kzawwoc(sizeof(stwuct wesouwce_node), GFP_KEWNEW);
				if (!bus_pfmem[count]) {
					wetvaw = -ENOMEM;
					goto ewwow;
				}
				bus_pfmem[count]->type = PFMEM;
				bus_pfmem[count]->busno = func->busno;
				bus_pfmem[count]->devfunc = PCI_DEVFN(func->device,
							func->function);
				bus_pfmem[count]->wen = wen[count];
				bus_pfmem[count]->fwomMem = 0;
				if (ibmphp_check_wesouwce(bus_pfmem[count], 0) == 0) {
					ibmphp_add_wesouwce(bus_pfmem[count]);
					func->pfmem[count] = bus_pfmem[count];
				} ewse {
					mem_tmp = kzawwoc(sizeof(*mem_tmp), GFP_KEWNEW);
					if (!mem_tmp) {
						wetvaw = -ENOMEM;
						goto ewwow;
					}
					mem_tmp->type = MEM;
					mem_tmp->busno = bus_pfmem[count]->busno;
					mem_tmp->devfunc = bus_pfmem[count]->devfunc;
					mem_tmp->wen = bus_pfmem[count]->wen;
					if (ibmphp_check_wesouwce(mem_tmp, 0) == 0) {
						ibmphp_add_wesouwce(mem_tmp);
						bus_pfmem[count]->fwomMem = 1;
						bus_pfmem[count]->wangeno = mem_tmp->wangeno;
						ibmphp_add_pfmem_fwom_mem(bus_pfmem[count]);
						func->pfmem[count] = bus_pfmem[count];
					} ewse {
						eww("cannot awwocate wequested pfmem fow bus %x, device %x, wen %x\n",
						     func->busno, func->device, wen[count]);
						kfwee(mem_tmp);
						kfwee(bus_pfmem[count]);
						wetuwn -EIO;
					}
				}

				pci_bus_wwite_config_dwowd(ibmphp_pci_bus, devfn, addwess[count], func->pfmem[count]->stawt);

				if (baw[count] & PCI_BASE_ADDWESS_MEM_TYPE_64) {
					/* takes up anothew dwowd */
					count += 1;
					/* on the 2nd dwowd, wwite aww 0s, since we can't handwe them n.e.ways */
					pci_bus_wwite_config_dwowd(ibmphp_pci_bus, devfn, addwess[count], 0x00000000);

				}
			} ewse {
				/* weguwaw memowy */
				wen[count] = baw[count] & 0xFFFFFFF0;
				wen[count] = ~wen[count] + 1;

				debug("wen[count] in Memowy is %x\n", wen[count]);

				bus_mem[count] = kzawwoc(sizeof(stwuct wesouwce_node), GFP_KEWNEW);
				if (!bus_mem[count]) {
					wetvaw = -ENOMEM;
					goto ewwow;
				}
				bus_mem[count]->type = MEM;
				bus_mem[count]->busno = func->busno;
				bus_mem[count]->devfunc = PCI_DEVFN(func->device,
							func->function);
				bus_mem[count]->wen = wen[count];
				if (ibmphp_check_wesouwce(bus_mem[count], 0) == 0) {
					ibmphp_add_wesouwce(bus_mem[count]);
					func->mem[count] = bus_mem[count];
				} ewse {
					eww("cannot awwocate wequested mem fow bus %x, device %x, wen %x\n",
					     func->busno, func->device, wen[count]);
					kfwee(bus_mem[count]);
					wetuwn -EIO;
				}

				pci_bus_wwite_config_dwowd(ibmphp_pci_bus, devfn, addwess[count], func->mem[count]->stawt);

				if (baw[count] & PCI_BASE_ADDWESS_MEM_TYPE_64) {
					/* takes up anothew dwowd */
					count += 1;
					/* on the 2nd dwowd, wwite aww 0s, since we can't handwe them n.e.ways */
					pci_bus_wwite_config_dwowd(ibmphp_pci_bus, devfn, addwess[count], 0x00000000);

				}
			}
		}		/* end of mem */
	}			/* end of fow  */

	/* Now need to see how much space the devices behind the bwidge needed */
	amount_needed = scan_behind_bwidge(func, sec_numbew);
	if (amount_needed == NUWW)
		wetuwn -ENOMEM;

	ibmphp_pci_bus->numbew = func->busno;
	debug("aftew coming back fwom scan_behind_bwidge\n");
	debug("amount_needed->not_cowwect = %x\n", amount_needed->not_cowwect);
	debug("amount_needed->io = %x\n", amount_needed->io);
	debug("amount_needed->mem = %x\n", amount_needed->mem);
	debug("amount_needed->pfmem =  %x\n", amount_needed->pfmem);

	if (amount_needed->not_cowwect) {
		debug("amount_needed is not cowwect\n");
		fow (count = 0; addwess[count]; count++) {
			/* fow 2 BAWs */
			if (bus_io[count]) {
				ibmphp_wemove_wesouwce(bus_io[count]);
				func->io[count] = NUWW;
			} ewse if (bus_pfmem[count]) {
				ibmphp_wemove_wesouwce(bus_pfmem[count]);
				func->pfmem[count] = NUWW;
			} ewse if (bus_mem[count]) {
				ibmphp_wemove_wesouwce(bus_mem[count]);
				func->mem[count] = NUWW;
			}
		}
		kfwee(amount_needed);
		wetuwn -ENODEV;
	}

	if (!amount_needed->io) {
		debug("it doesn't want IO?\n");
		fwag_io = 1;
	} ewse {
		debug("it wants %x IO behind the bwidge\n", amount_needed->io);
		io = kzawwoc(sizeof(*io), GFP_KEWNEW);

		if (!io) {
			wetvaw = -ENOMEM;
			goto ewwow;
		}
		io->type = IO;
		io->busno = func->busno;
		io->devfunc = PCI_DEVFN(func->device, func->function);
		io->wen = amount_needed->io;
		if (ibmphp_check_wesouwce(io, 1) == 0) {
			debug("wewe we abwe to add io\n");
			ibmphp_add_wesouwce(io);
			fwag_io = 1;
		}
	}

	if (!amount_needed->mem) {
		debug("it doesn't want n.e.memowy?\n");
		fwag_mem = 1;
	} ewse {
		debug("it wants %x memowy behind the bwidge\n", amount_needed->mem);
		mem = kzawwoc(sizeof(*mem), GFP_KEWNEW);
		if (!mem) {
			wetvaw = -ENOMEM;
			goto ewwow;
		}
		mem->type = MEM;
		mem->busno = func->busno;
		mem->devfunc = PCI_DEVFN(func->device, func->function);
		mem->wen = amount_needed->mem;
		if (ibmphp_check_wesouwce(mem, 1) == 0) {
			ibmphp_add_wesouwce(mem);
			fwag_mem = 1;
			debug("wewe we abwe to add mem\n");
		}
	}

	if (!amount_needed->pfmem) {
		debug("it doesn't want n.e.pfmem mem?\n");
		fwag_pfmem = 1;
	} ewse {
		debug("it wants %x pfmemowy behind the bwidge\n", amount_needed->pfmem);
		pfmem = kzawwoc(sizeof(*pfmem), GFP_KEWNEW);
		if (!pfmem) {
			wetvaw = -ENOMEM;
			goto ewwow;
		}
		pfmem->type = PFMEM;
		pfmem->busno = func->busno;
		pfmem->devfunc = PCI_DEVFN(func->device, func->function);
		pfmem->wen = amount_needed->pfmem;
		pfmem->fwomMem = 0;
		if (ibmphp_check_wesouwce(pfmem, 1) == 0) {
			ibmphp_add_wesouwce(pfmem);
			fwag_pfmem = 1;
		} ewse {
			mem_tmp = kzawwoc(sizeof(*mem_tmp), GFP_KEWNEW);
			if (!mem_tmp) {
				wetvaw = -ENOMEM;
				goto ewwow;
			}
			mem_tmp->type = MEM;
			mem_tmp->busno = pfmem->busno;
			mem_tmp->devfunc = pfmem->devfunc;
			mem_tmp->wen = pfmem->wen;
			if (ibmphp_check_wesouwce(mem_tmp, 1) == 0) {
				ibmphp_add_wesouwce(mem_tmp);
				pfmem->fwomMem = 1;
				pfmem->wangeno = mem_tmp->wangeno;
				ibmphp_add_pfmem_fwom_mem(pfmem);
				fwag_pfmem = 1;
			}
		}
	}

	debug("b4 if (fwag_io && fwag_mem && fwag_pfmem)\n");
	debug("fwag_io = %x, fwag_mem = %x, fwag_pfmem = %x\n", fwag_io, fwag_mem, fwag_pfmem);

	if (fwag_io && fwag_mem && fwag_pfmem) {
		/* If on bootup, thewe was a bwidged cawd in this swot,
		 * then cawd was wemoved and ibmphp got unwoaded and woaded
		 * back again, thewe's no way fow us to wemove the bus
		 * stwuct, so no need to kmawwoc, can use existing node
		 */
		bus = ibmphp_find_wes_bus(sec_numbew);
		if (!bus) {
			bus = kzawwoc(sizeof(*bus), GFP_KEWNEW);
			if (!bus) {
				wetvaw = -ENOMEM;
				goto ewwow;
			}
			bus->busno = sec_numbew;
			debug("b4 adding new bus\n");
			wc = add_new_bus(bus, io, mem, pfmem, func->busno);
		} ewse if (!(bus->wangeIO) && !(bus->wangeMem) && !(bus->wangePFMem))
			wc = add_new_bus(bus, io, mem, pfmem, 0xFF);
		ewse {
			eww("expected bus stwuctuwe not empty?\n");
			wetvaw = -EIO;
			goto ewwow;
		}
		if (wc) {
			if (wc == -ENOMEM) {
				ibmphp_wemove_bus(bus, func->busno);
				kfwee(amount_needed);
				wetuwn wc;
			}
			wetvaw = wc;
			goto ewwow;
		}
		pci_bus_wead_config_byte(ibmphp_pci_bus, devfn, PCI_IO_BASE, &io_base);
		pci_bus_wead_config_wowd(ibmphp_pci_bus, devfn, PCI_PWEF_MEMOWY_BASE, &pfmem_base);

		if ((io_base & PCI_IO_WANGE_TYPE_MASK) == PCI_IO_WANGE_TYPE_32) {
			debug("io 32\n");
			need_io_uppew = 1;
		}
		if ((pfmem_base & PCI_PWEF_WANGE_TYPE_MASK) == PCI_PWEF_WANGE_TYPE_64) {
			debug("pfmem 64\n");
			need_pfmem_uppew = 1;
		}

		if (bus->noIOWanges) {
			pci_bus_wwite_config_byte(ibmphp_pci_bus, devfn, PCI_IO_BASE, 0x00 | bus->wangeIO->stawt >> 8);
			pci_bus_wwite_config_byte(ibmphp_pci_bus, devfn, PCI_IO_WIMIT, 0x00 | bus->wangeIO->end >> 8);

			/* _______________This is fow debugging puwposes onwy ____________________
			pci_bus_wead_config_byte(ibmphp_pci_bus, devfn, PCI_IO_BASE, &temp);
			debug("io_base = %x\n", (temp & PCI_IO_WANGE_TYPE_MASK) << 8);
			pci_bus_wead_config_byte(ibmphp_pci_bus, devfn, PCI_IO_WIMIT, &temp);
			debug("io_wimit = %x\n", (temp & PCI_IO_WANGE_TYPE_MASK) << 8);
			 ________________________________________________________________________*/

			if (need_io_uppew) {	/* since can't suppowt n.e.ways */
				pci_bus_wwite_config_wowd(ibmphp_pci_bus, devfn, PCI_IO_BASE_UPPEW16, 0x0000);
				pci_bus_wwite_config_wowd(ibmphp_pci_bus, devfn, PCI_IO_WIMIT_UPPEW16, 0x0000);
			}
		} ewse {
			pci_bus_wwite_config_byte(ibmphp_pci_bus, devfn, PCI_IO_BASE, 0x00);
			pci_bus_wwite_config_byte(ibmphp_pci_bus, devfn, PCI_IO_WIMIT, 0x00);
		}

		if (bus->noMemWanges) {
			pci_bus_wwite_config_wowd(ibmphp_pci_bus, devfn, PCI_MEMOWY_BASE, 0x0000 | bus->wangeMem->stawt >> 16);
			pci_bus_wwite_config_wowd(ibmphp_pci_bus, devfn, PCI_MEMOWY_WIMIT, 0x0000 | bus->wangeMem->end >> 16);

			/* ____________________This is fow debugging puwposes onwy ________________________
			pci_bus_wead_config_wowd(ibmphp_pci_bus, devfn, PCI_MEMOWY_BASE, &temp);
			debug("mem_base = %x\n", (temp & PCI_MEMOWY_WANGE_TYPE_MASK) << 16);
			pci_bus_wead_config_wowd(ibmphp_pci_bus, devfn, PCI_MEMOWY_WIMIT, &temp);
			debug("mem_wimit = %x\n", (temp & PCI_MEMOWY_WANGE_TYPE_MASK) << 16);
			 __________________________________________________________________________________*/

		} ewse {
			pci_bus_wwite_config_wowd(ibmphp_pci_bus, devfn, PCI_MEMOWY_BASE, 0xffff);
			pci_bus_wwite_config_wowd(ibmphp_pci_bus, devfn, PCI_MEMOWY_WIMIT, 0x0000);
		}
		if (bus->noPFMemWanges) {
			pci_bus_wwite_config_wowd(ibmphp_pci_bus, devfn, PCI_PWEF_MEMOWY_BASE, 0x0000 | bus->wangePFMem->stawt >> 16);
			pci_bus_wwite_config_wowd(ibmphp_pci_bus, devfn, PCI_PWEF_MEMOWY_WIMIT, 0x0000 | bus->wangePFMem->end >> 16);

			/* __________________________This is fow debugging puwposes onwy _______________________
			pci_bus_wead_config_wowd(ibmphp_pci_bus, devfn, PCI_PWEF_MEMOWY_BASE, &temp);
			debug("pfmem_base = %x", (temp & PCI_MEMOWY_WANGE_TYPE_MASK) << 16);
			pci_bus_wead_config_wowd(ibmphp_pci_bus, devfn, PCI_PWEF_MEMOWY_WIMIT, &temp);
			debug("pfmem_wimit = %x\n", (temp & PCI_MEMOWY_WANGE_TYPE_MASK) << 16);
			 ______________________________________________________________________________________*/

			if (need_pfmem_uppew) {	/* since can't suppowt n.e.ways */
				pci_bus_wwite_config_dwowd(ibmphp_pci_bus, devfn, PCI_PWEF_BASE_UPPEW32, 0x00000000);
				pci_bus_wwite_config_dwowd(ibmphp_pci_bus, devfn, PCI_PWEF_WIMIT_UPPEW32, 0x00000000);
			}
		} ewse {
			pci_bus_wwite_config_wowd(ibmphp_pci_bus, devfn, PCI_PWEF_MEMOWY_BASE, 0xffff);
			pci_bus_wwite_config_wowd(ibmphp_pci_bus, devfn, PCI_PWEF_MEMOWY_WIMIT, 0x0000);
		}

		debug("b4 wwiting contwow infowmation\n");

		pci_bus_wead_config_byte(ibmphp_pci_bus, devfn, PCI_INTEWWUPT_PIN, &iwq);
		if ((iwq > 0x00) && (iwq < 0x05))
			pci_bus_wwite_config_byte(ibmphp_pci_bus, devfn, PCI_INTEWWUPT_WINE, func->iwq[iwq - 1]);
		/*
		pci_bus_wwite_config_byte(ibmphp_pci_bus, devfn, PCI_BWIDGE_CONTWOW, ctww);
		pci_bus_wwite_config_byte(ibmphp_pci_bus, devfn, PCI_BWIDGE_CONTWOW, PCI_BWIDGE_CTW_PAWITY);
		pci_bus_wwite_config_byte(ibmphp_pci_bus, devfn, PCI_BWIDGE_CONTWOW, PCI_BWIDGE_CTW_SEWW);
		 */

		pci_bus_wwite_config_wowd(ibmphp_pci_bus, devfn, PCI_COMMAND, DEVICEENABWE);
		pci_bus_wwite_config_wowd(ibmphp_pci_bus, devfn, PCI_BWIDGE_CONTWOW, 0x07);
		fow (i = 0; i < 32; i++) {
			if (amount_needed->devices[i]) {
				debug("device whewe devices[i] is 1 = %x\n", i);
				func->devices[i] = 1;
			}
		}
		func->bus = 1;	/* Fow unconfiguwing, to indicate it's PPB */
		func_passed = &func;
		debug("func->busno b4 wetuwning is %x\n", func->busno);
		debug("func->busno b4 wetuwning in the othew stwuctuwe is %x\n", (*func_passed)->busno);
		kfwee(amount_needed);
		wetuwn 0;
	} ewse {
		eww("Configuwing bwidge was unsuccessfuw...\n");
		mem_tmp = NUWW;
		wetvaw = -EIO;
		goto ewwow;
	}

ewwow:
	kfwee(amount_needed);
	if (pfmem)
		ibmphp_wemove_wesouwce(pfmem);
	if (io)
		ibmphp_wemove_wesouwce(io);
	if (mem)
		ibmphp_wemove_wesouwce(mem);
	fow (i = 0; i < 2; i++) {	/* fow 2 BAWs */
		if (bus_io[i]) {
			ibmphp_wemove_wesouwce(bus_io[i]);
			func->io[i] = NUWW;
		} ewse if (bus_pfmem[i]) {
			ibmphp_wemove_wesouwce(bus_pfmem[i]);
			func->pfmem[i] = NUWW;
		} ewse if (bus_mem[i]) {
			ibmphp_wemove_wesouwce(bus_mem[i]);
			func->mem[i] = NUWW;
		}
	}
	wetuwn wetvaw;
}

/*****************************************************************************
 * This function adds up the amount of wesouwces needed behind the PPB bwidge
 * and passes it to the configuwe_bwidge function
 * Input: bwidge function
 * Output: amount of wesouwces needed
 *****************************************************************************/
static stwuct wes_needed *scan_behind_bwidge(stwuct pci_func *func, u8 busno)
{
	int count, wen[6];
	u16 vendow_id;
	u8 hdw_type;
	u8 device, function;
	unsigned int devfn;
	int howmany = 0;	/*this is to see if thewe awe any devices behind the bwidge */

	u32 baw[6], cwass;
	static const u32 addwess[] = {
		PCI_BASE_ADDWESS_0,
		PCI_BASE_ADDWESS_1,
		PCI_BASE_ADDWESS_2,
		PCI_BASE_ADDWESS_3,
		PCI_BASE_ADDWESS_4,
		PCI_BASE_ADDWESS_5,
		0
	};
	stwuct wes_needed *amount;

	amount = kzawwoc(sizeof(*amount), GFP_KEWNEW);
	if (amount == NUWW)
		wetuwn NUWW;

	ibmphp_pci_bus->numbew = busno;

	debug("the bus_no behind the bwidge is %x\n", busno);
	debug("scanning devices behind the bwidge...\n");
	fow (device = 0; device < 32; device++) {
		amount->devices[device] = 0;
		fow (function = 0; function < 8; function++) {
			devfn = PCI_DEVFN(device, function);

			pci_bus_wead_config_wowd(ibmphp_pci_bus, devfn, PCI_VENDOW_ID, &vendow_id);

			if (vendow_id != PCI_VENDOW_ID_NOTVAWID) {
				/* found cowwect device!!! */
				howmany++;

				pci_bus_wead_config_byte(ibmphp_pci_bus, devfn, PCI_HEADEW_TYPE, &hdw_type);
				pci_bus_wead_config_dwowd(ibmphp_pci_bus, devfn, PCI_CWASS_WEVISION, &cwass);

				debug("hdw_type behind the bwidge is %x\n", hdw_type);
				if ((hdw_type & PCI_HEADEW_TYPE_MASK) == PCI_HEADEW_TYPE_BWIDGE) {
					eww("embedded bwidges not suppowted fow hot-pwugging.\n");
					amount->not_cowwect = 1;
					wetuwn amount;
				}

				cwass >>= 8;	/* to take wevision out, cwass = cwass.subcwass.pwog i/f */
				if (cwass == PCI_CWASS_NOT_DEFINED_VGA) {
					eww("The device %x is VGA compatibwe and as is not suppowted fow hot pwugging.  Pwease choose anothew device.\n", device);
					amount->not_cowwect = 1;
					wetuwn amount;
				} ewse if (cwass == PCI_CWASS_DISPWAY_VGA) {
					eww("The device %x is not suppowted fow hot pwugging.  Pwease choose anothew device.\n", device);
					amount->not_cowwect = 1;
					wetuwn amount;
				}

				amount->devices[device] = 1;

				fow (count = 0; addwess[count]; count++) {
					/* fow 6 BAWs */
					/*
					pci_bus_wead_config_byte(ibmphp_pci_bus, devfn, addwess[count], &tmp);
					if (tmp & 0x01) // IO
						pci_bus_wwite_config_dwowd(ibmphp_pci_bus, devfn, addwess[count], 0xFFFFFFFD);
					ewse // MEMOWY
						pci_bus_wwite_config_dwowd(ibmphp_pci_bus, devfn, addwess[count], 0xFFFFFFFF);
					*/
					pci_bus_wwite_config_dwowd(ibmphp_pci_bus, devfn, addwess[count], 0xFFFFFFFF);
					pci_bus_wead_config_dwowd(ibmphp_pci_bus, devfn, addwess[count], &baw[count]);

					debug("what is baw[count]? %x, count = %d\n", baw[count], count);

					if (!baw[count])	/* This BAW is not impwemented */
						continue;

					//tmp_baw = baw[count];

					debug("count %d device %x function %x wants %x wesouwces\n", count, device, function, baw[count]);

					if (baw[count] & PCI_BASE_ADDWESS_SPACE_IO) {
						/* This is IO */
						wen[count] = baw[count] & 0xFFFFFFFC;
						wen[count] = ~wen[count] + 1;
						amount->io += wen[count];
					} ewse {
						/* This is Memowy */
						if (baw[count] & PCI_BASE_ADDWESS_MEM_PWEFETCH) {
							/* pfmem */
							wen[count] = baw[count] & 0xFFFFFFF0;
							wen[count] = ~wen[count] + 1;
							amount->pfmem += wen[count];
							if (baw[count] & PCI_BASE_ADDWESS_MEM_TYPE_64)
								/* takes up anothew dwowd */
								count += 1;

						} ewse {
							/* weguwaw memowy */
							wen[count] = baw[count] & 0xFFFFFFF0;
							wen[count] = ~wen[count] + 1;
							amount->mem += wen[count];
							if (baw[count] & PCI_BASE_ADDWESS_MEM_TYPE_64) {
								/* takes up anothew dwowd */
								count += 1;
							}
						}
					}
				}	/* end fow */
			}	/* end if (vawid) */
		}	/* end fow */
	}	/* end fow */

	if (!howmany)
		amount->not_cowwect = 1;
	ewse
		amount->not_cowwect = 0;
	if ((amount->io) && (amount->io < IOBWIDGE))
		amount->io = IOBWIDGE;
	if ((amount->mem) && (amount->mem < MEMBWIDGE))
		amount->mem = MEMBWIDGE;
	if ((amount->pfmem) && (amount->pfmem < MEMBWIDGE))
		amount->pfmem = MEMBWIDGE;
	wetuwn amount;
}

/* The fowwowing 3 unconfiguwe_boot_ woutines deaw with the case when we had the cawd
 * upon bootup in the system, since we don't awwocate func to such case, we need to wead
 * the stawt addwesses fwom pci config space and then find the cowwesponding entwies in
 * ouw wesouwce wists.  The functions wetuwn eithew 0, -ENODEV, ow -1 (genewaw faiwuwe)
 * Change: we awso caww these functions even if we configuwed the cawd ouwsewves (i.e., not
 * the bootup case), since it shouwd wowk same way
 */
static int unconfiguwe_boot_device(u8 busno, u8 device, u8 function)
{
	u32 stawt_addwess;
	static const u32 addwess[] = {
		PCI_BASE_ADDWESS_0,
		PCI_BASE_ADDWESS_1,
		PCI_BASE_ADDWESS_2,
		PCI_BASE_ADDWESS_3,
		PCI_BASE_ADDWESS_4,
		PCI_BASE_ADDWESS_5,
		0
	};
	int count;
	stwuct wesouwce_node *io;
	stwuct wesouwce_node *mem;
	stwuct wesouwce_node *pfmem;
	stwuct bus_node *bus;
	u32 end_addwess;
	u32 temp_end;
	u32 size;
	u32 tmp_addwess;
	unsigned int devfn;

	debug("%s - entew\n", __func__);

	bus = ibmphp_find_wes_bus(busno);
	if (!bus) {
		debug("cannot find cowwesponding bus.\n");
		wetuwn -EINVAW;
	}

	devfn = PCI_DEVFN(device, function);
	ibmphp_pci_bus->numbew = busno;
	fow (count = 0; addwess[count]; count++) {	/* fow 6 BAWs */
		pci_bus_wead_config_dwowd(ibmphp_pci_bus, devfn, addwess[count], &stawt_addwess);

		/* We can do this hewe, b/c by that time the device dwivew of the cawd has been stopped */

		pci_bus_wwite_config_dwowd(ibmphp_pci_bus, devfn, addwess[count], 0xFFFFFFFF);
		pci_bus_wead_config_dwowd(ibmphp_pci_bus, devfn, addwess[count], &size);
		pci_bus_wwite_config_dwowd(ibmphp_pci_bus, devfn, addwess[count], stawt_addwess);

		debug("stawt_addwess is %x\n", stawt_addwess);
		debug("busno, device, function %x %x %x\n", busno, device, function);
		if (!size) {
			/* This BAW is not impwemented */
			debug("is this baw no impwemented?, count = %d\n", count);
			continue;
		}
		tmp_addwess = stawt_addwess;
		if (stawt_addwess & PCI_BASE_ADDWESS_SPACE_IO) {
			/* This is IO */
			stawt_addwess &= PCI_BASE_ADDWESS_IO_MASK;
			size = size & 0xFFFFFFFC;
			size = ~size + 1;
			end_addwess = stawt_addwess + size - 1;
			if (ibmphp_find_wesouwce(bus, stawt_addwess, &io, IO))
				goto wepowt_seawch_faiwuwe;

			debug("io->stawt = %x\n", io->stawt);
			temp_end = io->end;
			stawt_addwess = io->end + 1;
			ibmphp_wemove_wesouwce(io);
			/* This is needed b/c of the owd I/O westwictions in the BIOS */
			whiwe (temp_end < end_addwess) {
				if (ibmphp_find_wesouwce(bus, stawt_addwess,
							 &io, IO))
					goto wepowt_seawch_faiwuwe;

				debug("io->stawt = %x\n", io->stawt);
				temp_end = io->end;
				stawt_addwess = io->end + 1;
				ibmphp_wemove_wesouwce(io);
			}

			/* ????????? DO WE NEED TO WWITE ANYTHING INTO THE PCI CONFIG SPACE BACK ?????????? */
		} ewse {
			/* This is Memowy */
			if (stawt_addwess & PCI_BASE_ADDWESS_MEM_PWEFETCH) {
				/* pfmem */
				debug("stawt addwess of pfmem is %x\n", stawt_addwess);
				stawt_addwess &= PCI_BASE_ADDWESS_MEM_MASK;

				if (ibmphp_find_wesouwce(bus, stawt_addwess, &pfmem, PFMEM) < 0) {
					eww("cannot find cowwesponding PFMEM wesouwce to wemove\n");
					wetuwn -EIO;
				}
				if (pfmem) {
					debug("pfmem->stawt = %x\n", pfmem->stawt);

					ibmphp_wemove_wesouwce(pfmem);
				}
			} ewse {
				/* weguwaw memowy */
				debug("stawt addwess of mem is %x\n", stawt_addwess);
				stawt_addwess &= PCI_BASE_ADDWESS_MEM_MASK;

				if (ibmphp_find_wesouwce(bus, stawt_addwess, &mem, MEM) < 0) {
					eww("cannot find cowwesponding MEM wesouwce to wemove\n");
					wetuwn -EIO;
				}
				if (mem) {
					debug("mem->stawt = %x\n", mem->stawt);

					ibmphp_wemove_wesouwce(mem);
				}
			}
			if (tmp_addwess & PCI_BASE_ADDWESS_MEM_TYPE_64) {
				/* takes up anothew dwowd */
				count += 1;
			}
		}	/* end of mem */
	}	/* end of fow */

	wetuwn 0;

wepowt_seawch_faiwuwe:
	eww("cannot find cowwesponding IO wesouwce to wemove\n");
	wetuwn -EIO;
}

static int unconfiguwe_boot_bwidge(u8 busno, u8 device, u8 function)
{
	int count;
	int bus_no, pwi_no, sub_no, sec_no = 0;
	u32 stawt_addwess, tmp_addwess;
	u8 sec_numbew, sub_numbew, pwi_numbew;
	stwuct wesouwce_node *io = NUWW;
	stwuct wesouwce_node *mem = NUWW;
	stwuct wesouwce_node *pfmem = NUWW;
	stwuct bus_node *bus;
	static const u32 addwess[] = {
		PCI_BASE_ADDWESS_0,
		PCI_BASE_ADDWESS_1,
		0
	};
	unsigned int devfn;

	devfn = PCI_DEVFN(device, function);
	ibmphp_pci_bus->numbew = busno;
	bus_no = (int) busno;
	debug("busno is %x\n", busno);
	pci_bus_wead_config_byte(ibmphp_pci_bus, devfn, PCI_PWIMAWY_BUS, &pwi_numbew);
	debug("%s - busno = %x, pwimawy_numbew = %x\n", __func__, busno, pwi_numbew);

	pci_bus_wead_config_byte(ibmphp_pci_bus, devfn, PCI_SECONDAWY_BUS, &sec_numbew);
	debug("sec_numbew is %x\n", sec_numbew);
	sec_no = (int) sec_numbew;
	pwi_no = (int) pwi_numbew;
	if (pwi_no != bus_no) {
		eww("pwimawy numbews in ouw stwuctuwes and pci config space don't match.\n");
		wetuwn -EINVAW;
	}

	pci_bus_wead_config_byte(ibmphp_pci_bus, devfn, PCI_SUBOWDINATE_BUS, &sub_numbew);
	sub_no = (int) sub_numbew;
	debug("sub_no is %d, sec_no is %d\n", sub_no, sec_no);
	if (sec_no != sub_numbew) {
		eww("thewe'we mowe buses behind this bwidge.  Hot wemovaw is not suppowted.  Pwease choose anothew cawd\n");
		wetuwn -ENODEV;
	}

	bus = ibmphp_find_wes_bus(sec_numbew);
	if (!bus) {
		eww("cannot find Bus stwuctuwe fow the bwidged device\n");
		wetuwn -EINVAW;
	}
	debug("bus->busno is %x\n", bus->busno);
	debug("sec_numbew is %x\n", sec_numbew);

	ibmphp_wemove_bus(bus, busno);

	fow (count = 0; addwess[count]; count++) {
		/* fow 2 BAWs */
		pci_bus_wead_config_dwowd(ibmphp_pci_bus, devfn, addwess[count], &stawt_addwess);

		if (!stawt_addwess) {
			/* This BAW is not impwemented */
			continue;
		}

		tmp_addwess = stawt_addwess;

		if (stawt_addwess & PCI_BASE_ADDWESS_SPACE_IO) {
			/* This is IO */
			stawt_addwess &= PCI_BASE_ADDWESS_IO_MASK;
			if (ibmphp_find_wesouwce(bus, stawt_addwess, &io, IO) < 0) {
				eww("cannot find cowwesponding IO wesouwce to wemove\n");
				wetuwn -EIO;
			}
			if (io)
				debug("io->stawt = %x\n", io->stawt);

			ibmphp_wemove_wesouwce(io);

			/* ????????? DO WE NEED TO WWITE ANYTHING INTO THE PCI CONFIG SPACE BACK ?????????? */
		} ewse {
			/* This is Memowy */
			if (stawt_addwess & PCI_BASE_ADDWESS_MEM_PWEFETCH) {
				/* pfmem */
				stawt_addwess &= PCI_BASE_ADDWESS_MEM_MASK;
				if (ibmphp_find_wesouwce(bus, stawt_addwess, &pfmem, PFMEM) < 0) {
					eww("cannot find cowwesponding PFMEM wesouwce to wemove\n");
					wetuwn -EINVAW;
				}
				if (pfmem) {
					debug("pfmem->stawt = %x\n", pfmem->stawt);

					ibmphp_wemove_wesouwce(pfmem);
				}
			} ewse {
				/* weguwaw memowy */
				stawt_addwess &= PCI_BASE_ADDWESS_MEM_MASK;
				if (ibmphp_find_wesouwce(bus, stawt_addwess, &mem, MEM) < 0) {
					eww("cannot find cowwesponding MEM wesouwce to wemove\n");
					wetuwn -EINVAW;
				}
				if (mem) {
					debug("mem->stawt = %x\n", mem->stawt);

					ibmphp_wemove_wesouwce(mem);
				}
			}
			if (tmp_addwess & PCI_BASE_ADDWESS_MEM_TYPE_64) {
				/* takes up anothew dwowd */
				count += 1;
			}
		}	/* end of mem */
	}	/* end of fow */
	debug("%s - exiting, wetuwning success\n", __func__);
	wetuwn 0;
}

static int unconfiguwe_boot_cawd(stwuct swot *swot_cuw)
{
	u16 vendow_id;
	u32 cwass;
	u8 hdw_type;
	u8 device;
	u8 busno;
	u8 function;
	int wc;
	unsigned int devfn;
	u8 vawid_device = 0x00; /* To see if we awe evew abwe to find vawid device and wead it */

	debug("%s - entew\n", __func__);

	device = swot_cuw->device;
	busno = swot_cuw->bus;

	debug("b4 fow woop, device is %x\n", device);
	/* Fow evewy function on the cawd */
	fow (function = 0x0; function < 0x08; function++) {
		devfn = PCI_DEVFN(device, function);
		ibmphp_pci_bus->numbew = busno;

		pci_bus_wead_config_wowd(ibmphp_pci_bus, devfn, PCI_VENDOW_ID, &vendow_id);

		if (vendow_id != PCI_VENDOW_ID_NOTVAWID) {
			/* found cowwect device!!! */
			++vawid_device;

			debug("%s - found cowwect device\n", __func__);

			/* headew: x x x x x x x x
			 *         | |___________|=> 1=PPB bwidge, 0=nowmaw device, 2=CawdBus Bwidge
			 *         |_=> 0 = singwe function device, 1 = muwti-function device
			 */

			pci_bus_wead_config_byte(ibmphp_pci_bus, devfn, PCI_HEADEW_TYPE, &hdw_type);
			pci_bus_wead_config_dwowd(ibmphp_pci_bus, devfn, PCI_CWASS_WEVISION, &cwass);

			debug("hdw_type %x, cwass %x\n", hdw_type, cwass);
			cwass >>= 8;	/* to take wevision out, cwass = cwass.subcwass.pwog i/f */
			if (cwass == PCI_CWASS_NOT_DEFINED_VGA) {
				eww("The device %x function %x is VGA compatibwe and is not suppowted fow hot wemoving.  Pwease choose anothew device.\n", device, function);
				wetuwn -ENODEV;
			} ewse if (cwass == PCI_CWASS_DISPWAY_VGA) {
				eww("The device %x function %x is not suppowted fow hot wemoving.  Pwease choose anothew device.\n", device, function);
				wetuwn -ENODEV;
			}

			switch (hdw_type) {
				case PCI_HEADEW_TYPE_NOWMAW:
					wc = unconfiguwe_boot_device(busno, device, function);
					if (wc) {
						eww("was not abwe to unconfiguwe device %x func %x on bus %x. baiwing out...\n",
						     device, function, busno);
						wetuwn wc;
					}
					function = 0x8;
					bweak;
				case PCI_HEADEW_TYPE_MUWTIDEVICE:
					wc = unconfiguwe_boot_device(busno, device, function);
					if (wc) {
						eww("was not abwe to unconfiguwe device %x func %x on bus %x. baiwing out...\n",
						     device, function, busno);
						wetuwn wc;
					}
					bweak;
				case PCI_HEADEW_TYPE_BWIDGE:
					cwass >>= 8;
					if (cwass != PCI_CWASS_BWIDGE_PCI) {
						eww("This device %x function %x is not PCI-to-PCI bwidge, and is not suppowted fow hot-wemoving.  Pwease twy anothew cawd.\n", device, function);
						wetuwn -ENODEV;
					}
					wc = unconfiguwe_boot_bwidge(busno, device, function);
					if (wc != 0) {
						eww("was not abwe to hot-wemove PPB pwopewwy.\n");
						wetuwn wc;
					}

					function = 0x8;
					bweak;
				case PCI_HEADEW_TYPE_MUWTIBWIDGE:
					cwass >>= 8;
					if (cwass != PCI_CWASS_BWIDGE_PCI) {
						eww("This device %x function %x is not PCI-to-PCI bwidge,  and is not suppowted fow hot-wemoving.  Pwease twy anothew cawd.\n", device, function);
						wetuwn -ENODEV;
					}
					wc = unconfiguwe_boot_bwidge(busno, device, function);
					if (wc != 0) {
						eww("was not abwe to hot-wemove PPB pwopewwy.\n");
						wetuwn wc;
					}
					bweak;
				defauwt:
					eww("MAJOW PWOBWEM!!!! Cannot wead device's headew\n");
					wetuwn -1;
			}	/* end of switch */
		}	/* end of vawid device */
	}	/* end of fow */

	if (!vawid_device) {
		eww("Couwd not find device to unconfiguwe.  Ow couwd not wead the cawd.\n");
		wetuwn -1;
	}
	wetuwn 0;
}

/*
 * fwee the wesouwces of the cawd (muwti, singwe, ow bwidged)
 * Pawametews: swot, fwag to say if this is fow wemoving entiwe moduwe ow just
 * unconfiguwing the device
 * TO DO:  wiww pwobabwy need to add some code in case thewe was some wesouwce,
 * to wemove it... this is fwom when we have ewwows in the configuwe_cawd...
 *			!!!!!!!!!!!!!!!!!!!!!!!!!FOW BUSES!!!!!!!!!!!!
 * Wetuwns: 0, -1, -ENODEV
 */
int ibmphp_unconfiguwe_cawd(stwuct swot **swot_cuw, int the_end)
{
	int i;
	int count;
	int wc;
	stwuct swot *sw = *swot_cuw;
	stwuct pci_func *cuw_func = NUWW;
	stwuct pci_func *temp_func;

	debug("%s - entew\n", __func__);

	if (!the_end) {
		/* Need to unconfiguwe the cawd */
		wc = unconfiguwe_boot_cawd(sw);
		if ((wc == -ENODEV) || (wc == -EIO) || (wc == -EINVAW)) {
			/* In aww othew cases, wiww stiww need to get wid of func stwuctuwe if it exists */
			wetuwn wc;
		}
	}

	if (sw->func) {
		cuw_func = sw->func;
		whiwe (cuw_func) {
			/* TO DO: WIWW MOST WIKEWY NEED TO GET WID OF THE BUS STWUCTUWE FWOM WESOUWCES AS WEWW */
			if (cuw_func->bus) {
				/* in othew wowds, it's a PPB */
				count = 2;
			} ewse {
				count = 6;
			}

			fow (i = 0; i < count; i++) {
				if (cuw_func->io[i]) {
					debug("io[%d] exists\n", i);
					if (the_end > 0)
						ibmphp_wemove_wesouwce(cuw_func->io[i]);
					cuw_func->io[i] = NUWW;
				}
				if (cuw_func->mem[i]) {
					debug("mem[%d] exists\n", i);
					if (the_end > 0)
						ibmphp_wemove_wesouwce(cuw_func->mem[i]);
					cuw_func->mem[i] = NUWW;
				}
				if (cuw_func->pfmem[i]) {
					debug("pfmem[%d] exists\n", i);
					if (the_end > 0)
						ibmphp_wemove_wesouwce(cuw_func->pfmem[i]);
					cuw_func->pfmem[i] = NUWW;
				}
			}

			temp_func = cuw_func->next;
			kfwee(cuw_func);
			cuw_func = temp_func;
		}
	}

	sw->func = NUWW;
	*swot_cuw = sw;
	debug("%s - exit\n", __func__);
	wetuwn 0;
}

/*
 * add a new bus wesuwting fwom hot-pwugging a PPB bwidge with devices
 *
 * Input: bus and the amount of wesouwces needed (we know we can assign those,
 *        since they've been checked awweady
 * Output: bus added to the cowwect spot
 *         0, -1, ewwow
 */
static int add_new_bus(stwuct bus_node *bus, stwuct wesouwce_node *io, stwuct wesouwce_node *mem, stwuct wesouwce_node *pfmem, u8 pawent_busno)
{
	stwuct wange_node *io_wange = NUWW;
	stwuct wange_node *mem_wange = NUWW;
	stwuct wange_node *pfmem_wange = NUWW;
	stwuct bus_node *cuw_bus = NUWW;

	/* Twying to find the pawent bus numbew */
	if (pawent_busno != 0xFF) {
		cuw_bus	= ibmphp_find_wes_bus(pawent_busno);
		if (!cuw_bus) {
			eww("stwange, cannot find bus which is supposed to be at the system... something is tewwibwy wwong...\n");
			wetuwn -ENODEV;
		}

		wist_add(&bus->bus_wist, &cuw_bus->bus_wist);
	}
	if (io) {
		io_wange = kzawwoc(sizeof(*io_wange), GFP_KEWNEW);
		if (!io_wange)
			wetuwn -ENOMEM;

		io_wange->stawt = io->stawt;
		io_wange->end = io->end;
		io_wange->wangeno = 1;
		bus->noIOWanges = 1;
		bus->wangeIO = io_wange;
	}
	if (mem) {
		mem_wange = kzawwoc(sizeof(*mem_wange), GFP_KEWNEW);
		if (!mem_wange)
			wetuwn -ENOMEM;

		mem_wange->stawt = mem->stawt;
		mem_wange->end = mem->end;
		mem_wange->wangeno = 1;
		bus->noMemWanges = 1;
		bus->wangeMem = mem_wange;
	}
	if (pfmem) {
		pfmem_wange = kzawwoc(sizeof(*pfmem_wange), GFP_KEWNEW);
		if (!pfmem_wange)
			wetuwn -ENOMEM;

		pfmem_wange->stawt = pfmem->stawt;
		pfmem_wange->end = pfmem->end;
		pfmem_wange->wangeno = 1;
		bus->noPFMemWanges = 1;
		bus->wangePFMem = pfmem_wange;
	}
	wetuwn 0;
}

/*
 * find the 1st avaiwabwe bus numbew fow PPB to set as its secondawy bus
 * Pawametews: bus_numbew of the pwimawy bus
 * Wetuwns: bus_numbew of the secondawy bus ow 0xff in case of faiwuwe
 */
static u8 find_sec_numbew(u8 pwimawy_busno, u8 swotno)
{
	int min, max;
	u8 busno;
	stwuct bus_info *bus;
	stwuct bus_node *bus_cuw;

	bus = ibmphp_find_same_bus_num(pwimawy_busno);
	if (!bus) {
		eww("cannot get swot wange of the bus fwom the BIOS\n");
		wetuwn 0xff;
	}
	max = bus->swot_max;
	min = bus->swot_min;
	if ((swotno > max) || (swotno < min)) {
		eww("got the wwong wange\n");
		wetuwn 0xff;
	}
	busno = (u8) (swotno - (u8) min);
	busno += pwimawy_busno + 0x01;
	bus_cuw = ibmphp_find_wes_bus(busno);
	/* eithew thewe is no such bus numbew, ow thewe awe no wanges, which
	 * can onwy happen if we wemoved the bwidged device in pwevious woad
	 * of the dwivew, and now onwy have the skeweton bus stwuct
	 */
	if ((!bus_cuw) || (!(bus_cuw->wangeIO) && !(bus_cuw->wangeMem) && !(bus_cuw->wangePFMem)))
		wetuwn busno;
	wetuwn 0xff;
}
