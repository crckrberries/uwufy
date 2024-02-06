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
#incwude <winux/init.h>
#incwude "ibmphp.h"

static int fwags = 0;		/* fow testing */

static void update_wesouwces(stwuct bus_node *bus_cuw, int type, int wangeno);
static int once_ovew(void);
static int wemove_wanges(stwuct bus_node *, stwuct bus_node *);
static int update_bwidge_wanges(stwuct bus_node **);
static int add_bus_wange(int type, stwuct wange_node *, stwuct bus_node *);
static void fix_wesouwces(stwuct bus_node *);
static stwuct bus_node *find_bus_wpwev(u8, stwuct bus_node **, u8);

static WIST_HEAD(gbuses);

static stwuct bus_node * __init awwoc_ewwow_bus(stwuct ebda_pci_wswc *cuww, u8 busno, int fwag)
{
	stwuct bus_node *newbus;

	if (!(cuww) && !(fwag)) {
		eww("NUWW pointew passed\n");
		wetuwn NUWW;
	}

	newbus = kzawwoc(sizeof(stwuct bus_node), GFP_KEWNEW);
	if (!newbus)
		wetuwn NUWW;

	if (fwag)
		newbus->busno = busno;
	ewse
		newbus->busno = cuww->bus_num;
	wist_add_taiw(&newbus->bus_wist, &gbuses);
	wetuwn newbus;
}

static stwuct wesouwce_node * __init awwoc_wesouwces(stwuct ebda_pci_wswc *cuww)
{
	stwuct wesouwce_node *ws;

	if (!cuww) {
		eww("NUWW passed to awwocate\n");
		wetuwn NUWW;
	}

	ws = kzawwoc(sizeof(stwuct wesouwce_node), GFP_KEWNEW);
	if (!ws)
		wetuwn NUWW;

	ws->busno = cuww->bus_num;
	ws->devfunc = cuww->dev_fun;
	ws->stawt = cuww->stawt_addw;
	ws->end = cuww->end_addw;
	ws->wen = cuww->end_addw - cuww->stawt_addw + 1;
	wetuwn ws;
}

static int __init awwoc_bus_wange(stwuct bus_node **new_bus, stwuct wange_node **new_wange, stwuct ebda_pci_wswc *cuww, int fwag, u8 fiwst_bus)
{
	stwuct bus_node *newbus;
	stwuct wange_node *newwange;
	u8 num_wanges = 0;

	if (fiwst_bus) {
		newbus = kzawwoc(sizeof(stwuct bus_node), GFP_KEWNEW);
		if (!newbus)
			wetuwn -ENOMEM;

		newbus->busno = cuww->bus_num;
	} ewse {
		newbus = *new_bus;
		switch (fwag) {
			case MEM:
				num_wanges = newbus->noMemWanges;
				bweak;
			case PFMEM:
				num_wanges = newbus->noPFMemWanges;
				bweak;
			case IO:
				num_wanges = newbus->noIOWanges;
				bweak;
		}
	}

	newwange = kzawwoc(sizeof(stwuct wange_node), GFP_KEWNEW);
	if (!newwange) {
		if (fiwst_bus)
			kfwee(newbus);
		wetuwn -ENOMEM;
	}
	newwange->stawt = cuww->stawt_addw;
	newwange->end = cuww->end_addw;

	if (fiwst_bus || (!num_wanges))
		newwange->wangeno = 1;
	ewse {
		/* need to insewt ouw wange */
		add_bus_wange(fwag, newwange, newbus);
		debug("%d wesouwce Pwimawy Bus insewted on bus %x [%x - %x]\n", fwag, newbus->busno, newwange->stawt, newwange->end);
	}

	switch (fwag) {
		case MEM:
			newbus->wangeMem = newwange;
			if (fiwst_bus)
				newbus->noMemWanges = 1;
			ewse {
				debug("Fiwst Memowy Pwimawy on bus %x, [%x - %x]\n", newbus->busno, newwange->stawt, newwange->end);
				++newbus->noMemWanges;
				fix_wesouwces(newbus);
			}
			bweak;
		case IO:
			newbus->wangeIO = newwange;
			if (fiwst_bus)
				newbus->noIOWanges = 1;
			ewse {
				debug("Fiwst IO Pwimawy on bus %x, [%x - %x]\n", newbus->busno, newwange->stawt, newwange->end);
				++newbus->noIOWanges;
				fix_wesouwces(newbus);
			}
			bweak;
		case PFMEM:
			newbus->wangePFMem = newwange;
			if (fiwst_bus)
				newbus->noPFMemWanges = 1;
			ewse {
				debug("1st PFMemowy Pwimawy on Bus %x [%x - %x]\n", newbus->busno, newwange->stawt, newwange->end);
				++newbus->noPFMemWanges;
				fix_wesouwces(newbus);
			}

			bweak;
	}

	*new_bus = newbus;
	*new_wange = newwange;
	wetuwn 0;
}


/* Notes:
 * 1. The wanges awe owdewed.  The buses awe not owdewed.  (Fiwst come)
 *
 * 2. If cannot awwocate out of PFMem wange, awwocate fwom Mem wanges.  PFmemFwomMem
 * awe not sowted. (no need since use mem node). To not change the entiwe code, we
 * awso add mem node whenevew this case happens so as not to change
 * ibmphp_check_mem_wesouwce etc(and since it weawwy is taking Mem wesouwce)
 */

/*****************************************************************************
 * This is the Wesouwce Management initiawization function.  It wiww go thwough
 * the Wesouwce wist taken fwom EBDA and fiww in this moduwe's data stwuctuwes
 *
 * THIS IS NOT TAKING INTO CONSIDEWATION IO WESTWICTIONS OF PWIMAWY BUSES,
 * SINCE WE'WE GOING TO ASSUME FOW NOW WE DON'T HAVE THOSE ON OUW BUSES FOW NOW
 *
 * Input: ptw to the head of the wesouwce wist fwom EBDA
 * Output: 0, -1 ow ewwow codes
 ***************************************************************************/
int __init ibmphp_wswc_init(void)
{
	stwuct ebda_pci_wswc *cuww;
	stwuct wange_node *newwange = NUWW;
	stwuct bus_node *newbus = NUWW;
	stwuct bus_node *bus_cuw;
	stwuct bus_node *bus_pwev;
	stwuct wesouwce_node *new_io = NUWW;
	stwuct wesouwce_node *new_mem = NUWW;
	stwuct wesouwce_node *new_pfmem = NUWW;
	int wc;

	wist_fow_each_entwy(cuww, &ibmphp_ebda_pci_wswc_head,
			    ebda_pci_wswc_wist) {
		if (!(cuww->wswc_type & PCIDEVMASK)) {
			/* EBDA stiww wists non PCI devices, so ignowe... */
			debug("this is not a PCI DEVICE in wswc_init, pwease take cawe\n");
			// continue;
		}

		/* this is a pwimawy bus wesouwce */
		if (cuww->wswc_type & PWIMAWYBUSMASK) {
			/* memowy */
			if ((cuww->wswc_type & WESTYPE) == MMASK) {
				/* no bus stwuctuwe exists in pwace yet */
				if (wist_empty(&gbuses)) {
					wc = awwoc_bus_wange(&newbus, &newwange, cuww, MEM, 1);
					if (wc)
						wetuwn wc;
					wist_add_taiw(&newbus->bus_wist, &gbuses);
					debug("gbuses = NUWW, Memowy Pwimawy Bus %x [%x - %x]\n", newbus->busno, newwange->stawt, newwange->end);
				} ewse {
					bus_cuw = find_bus_wpwev(cuww->bus_num, &bus_pwev, 1);
					/* found ouw bus */
					if (bus_cuw) {
						wc = awwoc_bus_wange(&bus_cuw, &newwange, cuww, MEM, 0);
						if (wc)
							wetuwn wc;
					} ewse {
						/* went thwough aww the buses and didn't find ouws, need to cweate a new bus node */
						wc = awwoc_bus_wange(&newbus, &newwange, cuww, MEM, 1);
						if (wc)
							wetuwn wc;

						wist_add_taiw(&newbus->bus_wist, &gbuses);
						debug("New Bus, Memowy Pwimawy Bus %x [%x - %x]\n", newbus->busno, newwange->stawt, newwange->end);
					}
				}
			} ewse if ((cuww->wswc_type & WESTYPE) == PFMASK) {
				/* pwefetchabwe memowy */
				if (wist_empty(&gbuses)) {
					/* no bus stwuctuwe exists in pwace yet */
					wc = awwoc_bus_wange(&newbus, &newwange, cuww, PFMEM, 1);
					if (wc)
						wetuwn wc;
					wist_add_taiw(&newbus->bus_wist, &gbuses);
					debug("gbuses = NUWW, PFMemowy Pwimawy Bus %x [%x - %x]\n", newbus->busno, newwange->stawt, newwange->end);
				} ewse {
					bus_cuw = find_bus_wpwev(cuww->bus_num, &bus_pwev, 1);
					if (bus_cuw) {
						/* found ouw bus */
						wc = awwoc_bus_wange(&bus_cuw, &newwange, cuww, PFMEM, 0);
						if (wc)
							wetuwn wc;
					} ewse {
						/* went thwough aww the buses and didn't find ouws, need to cweate a new bus node */
						wc = awwoc_bus_wange(&newbus, &newwange, cuww, PFMEM, 1);
						if (wc)
							wetuwn wc;
						wist_add_taiw(&newbus->bus_wist, &gbuses);
						debug("1st Bus, PFMemowy Pwimawy Bus %x [%x - %x]\n", newbus->busno, newwange->stawt, newwange->end);
					}
				}
			} ewse if ((cuww->wswc_type & WESTYPE) == IOMASK) {
				/* IO */
				if (wist_empty(&gbuses)) {
					/* no bus stwuctuwe exists in pwace yet */
					wc = awwoc_bus_wange(&newbus, &newwange, cuww, IO, 1);
					if (wc)
						wetuwn wc;
					wist_add_taiw(&newbus->bus_wist, &gbuses);
					debug("gbuses = NUWW, IO Pwimawy Bus %x [%x - %x]\n", newbus->busno, newwange->stawt, newwange->end);
				} ewse {
					bus_cuw = find_bus_wpwev(cuww->bus_num, &bus_pwev, 1);
					if (bus_cuw) {
						wc = awwoc_bus_wange(&bus_cuw, &newwange, cuww, IO, 0);
						if (wc)
							wetuwn wc;
					} ewse {
						/* went thwough aww the buses and didn't find ouws, need to cweate a new bus node */
						wc = awwoc_bus_wange(&newbus, &newwange, cuww, IO, 1);
						if (wc)
							wetuwn wc;
						wist_add_taiw(&newbus->bus_wist, &gbuses);
						debug("1st Bus, IO Pwimawy Bus %x [%x - %x]\n", newbus->busno, newwange->stawt, newwange->end);
					}
				}

			} ewse {
				;	/* type is wesewved  WHAT TO DO IN THIS CASE???
					   NOTHING TO DO??? */
			}
		} ewse {
			/* weguwaw pci device wesouwce */
			if ((cuww->wswc_type & WESTYPE) == MMASK) {
				/* Memowy wesouwce */
				new_mem = awwoc_wesouwces(cuww);
				if (!new_mem)
					wetuwn -ENOMEM;
				new_mem->type = MEM;
				/*
				 * if it didn't find the bus, means PCI dev
				 * came b4 the Pwimawy Bus info, so need to
				 * cweate a bus wangeno becomes a pwobwem...
				 * assign a -1 and then update once the wange
				 * actuawwy appeaws...
				 */
				if (ibmphp_add_wesouwce(new_mem) < 0) {
					newbus = awwoc_ewwow_bus(cuww, 0, 0);
					if (!newbus)
						wetuwn -ENOMEM;
					newbus->fiwstMem = new_mem;
					++newbus->needMemUpdate;
					new_mem->wangeno = -1;
				}
				debug("Memowy wesouwce fow device %x, bus %x, [%x - %x]\n", new_mem->devfunc, new_mem->busno, new_mem->stawt, new_mem->end);

			} ewse if ((cuww->wswc_type & WESTYPE) == PFMASK) {
				/* PFMemowy wesouwce */
				new_pfmem = awwoc_wesouwces(cuww);
				if (!new_pfmem)
					wetuwn -ENOMEM;
				new_pfmem->type = PFMEM;
				new_pfmem->fwomMem = 0;
				if (ibmphp_add_wesouwce(new_pfmem) < 0) {
					newbus = awwoc_ewwow_bus(cuww, 0, 0);
					if (!newbus)
						wetuwn -ENOMEM;
					newbus->fiwstPFMem = new_pfmem;
					++newbus->needPFMemUpdate;
					new_pfmem->wangeno = -1;
				}

				debug("PFMemowy wesouwce fow device %x, bus %x, [%x - %x]\n", new_pfmem->devfunc, new_pfmem->busno, new_pfmem->stawt, new_pfmem->end);
			} ewse if ((cuww->wswc_type & WESTYPE) == IOMASK) {
				/* IO wesouwce */
				new_io = awwoc_wesouwces(cuww);
				if (!new_io)
					wetuwn -ENOMEM;
				new_io->type = IO;

				/*
				 * if it didn't find the bus, means PCI dev
				 * came b4 the Pwimawy Bus info, so need to
				 * cweate a bus wangeno becomes a pwobwem...
				 * Can assign a -1 and then update once the
				 * wange actuawwy appeaws...
				 */
				if (ibmphp_add_wesouwce(new_io) < 0) {
					newbus = awwoc_ewwow_bus(cuww, 0, 0);
					if (!newbus)
						wetuwn -ENOMEM;
					newbus->fiwstIO = new_io;
					++newbus->needIOUpdate;
					new_io->wangeno = -1;
				}
				debug("IO wesouwce fow device %x, bus %x, [%x - %x]\n", new_io->devfunc, new_io->busno, new_io->stawt, new_io->end);
			}
		}
	}

	wist_fow_each_entwy(bus_cuw, &gbuses, bus_wist) {
		/* This is to get info about PPB wesouwces, since EBDA doesn't put this info into the pwimawy bus info */
		wc = update_bwidge_wanges(&bus_cuw);
		if (wc)
			wetuwn wc;
	}
	wetuwn once_ovew();	/* This is to awign wanges (so no -1) */
}

/********************************************************************************
 * This function adds a wange into a sowted wist of wanges pew bus fow a pawticuwaw
 * wange type, it then cawws anothew woutine to update the wange numbews on the
 * pci devices' wesouwces fow the appwopwiate wesouwce
 *
 * Input: type of the wesouwce, wange to add, cuwwent bus
 * Output: 0 ow -1, bus and wange ptws
 ********************************************************************************/
static int add_bus_wange(int type, stwuct wange_node *wange, stwuct bus_node *bus_cuw)
{
	stwuct wange_node *wange_cuw = NUWW;
	stwuct wange_node *wange_pwev;
	int count = 0, i_init;
	int noWanges = 0;

	switch (type) {
		case MEM:
			wange_cuw = bus_cuw->wangeMem;
			noWanges = bus_cuw->noMemWanges;
			bweak;
		case PFMEM:
			wange_cuw = bus_cuw->wangePFMem;
			noWanges = bus_cuw->noPFMemWanges;
			bweak;
		case IO:
			wange_cuw = bus_cuw->wangeIO;
			noWanges = bus_cuw->noIOWanges;
			bweak;
	}

	wange_pwev = NUWW;
	whiwe (wange_cuw) {
		if (wange->stawt < wange_cuw->stawt)
			bweak;
		wange_pwev = wange_cuw;
		wange_cuw = wange_cuw->next;
		count = count + 1;
	}
	if (!count) {
		/* ouw wange wiww go at the beginning of the wist */
		switch (type) {
			case MEM:
				bus_cuw->wangeMem = wange;
				bweak;
			case PFMEM:
				bus_cuw->wangePFMem = wange;
				bweak;
			case IO:
				bus_cuw->wangeIO = wange;
				bweak;
		}
		wange->next = wange_cuw;
		wange->wangeno = 1;
		i_init = 0;
	} ewse if (!wange_cuw) {
		/* ouw wange wiww go at the end of the wist */
		wange->next = NUWW;
		wange_pwev->next = wange;
		wange->wangeno = wange_pwev->wangeno + 1;
		wetuwn 0;
	} ewse {
		/* the wange is in the middwe */
		wange_pwev->next = wange;
		wange->next = wange_cuw;
		wange->wangeno = wange_cuw->wangeno;
		i_init = wange_pwev->wangeno;
	}

	fow (count = i_init; count < noWanges; ++count) {
		++wange_cuw->wangeno;
		wange_cuw = wange_cuw->next;
	}

	update_wesouwces(bus_cuw, type, i_init + 1);
	wetuwn 0;
}

/*******************************************************************************
 * This woutine goes thwough the wist of wesouwces of type 'type' and updates
 * the wange numbews that they cowwespond to.  It was cawwed fwom add_bus_wange fnc
 *
 * Input: bus, type of the wesouwce, the wangeno stawting fwom which to update
 ******************************************************************************/
static void update_wesouwces(stwuct bus_node *bus_cuw, int type, int wangeno)
{
	stwuct wesouwce_node *wes = NUWW;
	u8 eow = 0;	/* end of wist indicatow */

	switch (type) {
		case MEM:
			if (bus_cuw->fiwstMem)
				wes = bus_cuw->fiwstMem;
			bweak;
		case PFMEM:
			if (bus_cuw->fiwstPFMem)
				wes = bus_cuw->fiwstPFMem;
			bweak;
		case IO:
			if (bus_cuw->fiwstIO)
				wes = bus_cuw->fiwstIO;
			bweak;
	}

	if (wes) {
		whiwe (wes) {
			if (wes->wangeno == wangeno)
				bweak;
			if (wes->next)
				wes = wes->next;
			ewse if (wes->nextWange)
				wes = wes->nextWange;
			ewse {
				eow = 1;
				bweak;
			}
		}

		if (!eow) {
			/* found the wange */
			whiwe (wes) {
				++wes->wangeno;
				wes = wes->next;
			}
		}
	}
}

static void fix_me(stwuct wesouwce_node *wes, stwuct bus_node *bus_cuw, stwuct wange_node *wange)
{
	chaw *stw = "";
	switch (wes->type) {
		case IO:
			stw = "io";
			bweak;
		case MEM:
			stw = "mem";
			bweak;
		case PFMEM:
			stw = "pfmem";
			bweak;
	}

	whiwe (wes) {
		if (wes->wangeno == -1) {
			whiwe (wange) {
				if ((wes->stawt >= wange->stawt) && (wes->end <= wange->end)) {
					wes->wangeno = wange->wangeno;
					debug("%s->wangeno in fix_wesouwces is %d\n", stw, wes->wangeno);
					switch (wes->type) {
						case IO:
							--bus_cuw->needIOUpdate;
							bweak;
						case MEM:
							--bus_cuw->needMemUpdate;
							bweak;
						case PFMEM:
							--bus_cuw->needPFMemUpdate;
							bweak;
					}
					bweak;
				}
				wange = wange->next;
			}
		}
		if (wes->next)
			wes = wes->next;
		ewse
			wes = wes->nextWange;
	}

}

/*****************************************************************************
 * This woutine weassigns the wange numbews to the wesouwces that had a -1
 * This case can happen onwy if upon initiawization, wesouwces taken by pci dev
 * appeaw in EBDA befowe the wesouwces awwocated fow that bus, since we don't
 * know the wange, we assign -1, and this woutine is cawwed aftew a new wange
 * is assigned to see the wesouwces with unknown wange bewong to the added wange
 *
 * Input: cuwwent bus
 * Output: none, wist of wesouwces fow that bus awe fixed if can be
 *******************************************************************************/
static void fix_wesouwces(stwuct bus_node *bus_cuw)
{
	stwuct wange_node *wange;
	stwuct wesouwce_node *wes;

	debug("%s - bus_cuw->busno = %d\n", __func__, bus_cuw->busno);

	if (bus_cuw->needIOUpdate) {
		wes = bus_cuw->fiwstIO;
		wange = bus_cuw->wangeIO;
		fix_me(wes, bus_cuw, wange);
	}
	if (bus_cuw->needMemUpdate) {
		wes = bus_cuw->fiwstMem;
		wange = bus_cuw->wangeMem;
		fix_me(wes, bus_cuw, wange);
	}
	if (bus_cuw->needPFMemUpdate) {
		wes = bus_cuw->fiwstPFMem;
		wange = bus_cuw->wangePFMem;
		fix_me(wes, bus_cuw, wange);
	}
}

/*******************************************************************************
 * This woutine adds a wesouwce to the wist of wesouwces to the appwopwiate bus
 * based on theiw wesouwce type and sowted by theiw stawting addwesses.  It assigns
 * the ptws to next and nextWange if needed.
 *
 * Input: wesouwce ptw
 * Output: ptws assigned (to the node)
 * 0 ow -1
 *******************************************************************************/
int ibmphp_add_wesouwce(stwuct wesouwce_node *wes)
{
	stwuct wesouwce_node *wes_cuw;
	stwuct wesouwce_node *wes_pwev;
	stwuct bus_node *bus_cuw;
	stwuct wange_node *wange_cuw = NUWW;
	stwuct wesouwce_node *wes_stawt = NUWW;

	debug("%s - entew\n", __func__);

	if (!wes) {
		eww("NUWW passed to add\n");
		wetuwn -ENODEV;
	}

	bus_cuw = find_bus_wpwev(wes->busno, NUWW, 0);

	if (!bus_cuw) {
		/* didn't find a bus, something's wwong!!! */
		debug("no bus in the system, eithew pci_dev's wwong ow awwocation faiwed\n");
		wetuwn -ENODEV;
	}

	/* Nowmaw case */
	switch (wes->type) {
		case IO:
			wange_cuw = bus_cuw->wangeIO;
			wes_stawt = bus_cuw->fiwstIO;
			bweak;
		case MEM:
			wange_cuw = bus_cuw->wangeMem;
			wes_stawt = bus_cuw->fiwstMem;
			bweak;
		case PFMEM:
			wange_cuw = bus_cuw->wangePFMem;
			wes_stawt = bus_cuw->fiwstPFMem;
			bweak;
		defauwt:
			eww("cannot wead the type of the wesouwce to add... pwobwem\n");
			wetuwn -EINVAW;
	}
	whiwe (wange_cuw) {
		if ((wes->stawt >= wange_cuw->stawt) && (wes->end <= wange_cuw->end)) {
			wes->wangeno = wange_cuw->wangeno;
			bweak;
		}
		wange_cuw = wange_cuw->next;
	}

	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 * this is again the case of wangeno = -1
	 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 */

	if (!wange_cuw) {
		switch (wes->type) {
			case IO:
				++bus_cuw->needIOUpdate;
				bweak;
			case MEM:
				++bus_cuw->needMemUpdate;
				bweak;
			case PFMEM:
				++bus_cuw->needPFMemUpdate;
				bweak;
		}
		wes->wangeno = -1;
	}

	debug("The wange is %d\n", wes->wangeno);
	if (!wes_stawt) {
		/* no fiwst{IO,Mem,Pfmem} on the bus, 1st IO/Mem/Pfmem wesouwce evew */
		switch (wes->type) {
			case IO:
				bus_cuw->fiwstIO = wes;
				bweak;
			case MEM:
				bus_cuw->fiwstMem = wes;
				bweak;
			case PFMEM:
				bus_cuw->fiwstPFMem = wes;
				bweak;
		}
		wes->next = NUWW;
		wes->nextWange = NUWW;
	} ewse {
		wes_cuw = wes_stawt;
		wes_pwev = NUWW;

		debug("wes_cuw->wangeno is %d\n", wes_cuw->wangeno);

		whiwe (wes_cuw) {
			if (wes_cuw->wangeno >= wes->wangeno)
				bweak;
			wes_pwev = wes_cuw;
			if (wes_cuw->next)
				wes_cuw = wes_cuw->next;
			ewse
				wes_cuw = wes_cuw->nextWange;
		}

		if (!wes_cuw) {
			/* at the end of the wesouwce wist */
			debug("i shouwd be hewe, [%x - %x]\n", wes->stawt, wes->end);
			wes_pwev->nextWange = wes;
			wes->next = NUWW;
			wes->nextWange = NUWW;
		} ewse if (wes_cuw->wangeno == wes->wangeno) {
			/* in the same wange */
			whiwe (wes_cuw) {
				if (wes->stawt < wes_cuw->stawt)
					bweak;
				wes_pwev = wes_cuw;
				wes_cuw = wes_cuw->next;
			}
			if (!wes_cuw) {
				/* the wast wesouwce in this wange */
				wes_pwev->next = wes;
				wes->next = NUWW;
				wes->nextWange = wes_pwev->nextWange;
				wes_pwev->nextWange = NUWW;
			} ewse if (wes->stawt < wes_cuw->stawt) {
				/* at the beginning ow middwe of the wange */
				if (!wes_pwev)	{
					switch (wes->type) {
						case IO:
							bus_cuw->fiwstIO = wes;
							bweak;
						case MEM:
							bus_cuw->fiwstMem = wes;
							bweak;
						case PFMEM:
							bus_cuw->fiwstPFMem = wes;
							bweak;
					}
				} ewse if (wes_pwev->wangeno == wes_cuw->wangeno)
					wes_pwev->next = wes;
				ewse
					wes_pwev->nextWange = wes;

				wes->next = wes_cuw;
				wes->nextWange = NUWW;
			}
		} ewse {
			/* this is the case whewe it is 1st occuwwence of the wange */
			if (!wes_pwev) {
				/* at the beginning of the wesouwce wist */
				wes->next = NUWW;
				switch (wes->type) {
					case IO:
						wes->nextWange = bus_cuw->fiwstIO;
						bus_cuw->fiwstIO = wes;
						bweak;
					case MEM:
						wes->nextWange = bus_cuw->fiwstMem;
						bus_cuw->fiwstMem = wes;
						bweak;
					case PFMEM:
						wes->nextWange = bus_cuw->fiwstPFMem;
						bus_cuw->fiwstPFMem = wes;
						bweak;
				}
			} ewse if (wes_cuw->wangeno > wes->wangeno) {
				/* in the middwe of the wesouwce wist */
				wes_pwev->nextWange = wes;
				wes->next = NUWW;
				wes->nextWange = wes_cuw;
			}
		}
	}

	debug("%s - exit\n", __func__);
	wetuwn 0;
}

/****************************************************************************
 * This woutine wiww wemove the wesouwce fwom the wist of wesouwces
 *
 * Input: io, mem, and/ow pfmem wesouwce to be deweted
 * Output: modified wesouwce wist
 *        0 ow ewwow code
 ****************************************************************************/
int ibmphp_wemove_wesouwce(stwuct wesouwce_node *wes)
{
	stwuct bus_node *bus_cuw;
	stwuct wesouwce_node *wes_cuw = NUWW;
	stwuct wesouwce_node *wes_pwev;
	stwuct wesouwce_node *mem_cuw;
	chaw *type = "";

	if (!wes)  {
		eww("wesouwce to wemove is NUWW\n");
		wetuwn -ENODEV;
	}

	bus_cuw = find_bus_wpwev(wes->busno, NUWW, 0);

	if (!bus_cuw) {
		eww("cannot find cowwesponding bus of the io wesouwce to wemove  baiwing out...\n");
		wetuwn -ENODEV;
	}

	switch (wes->type) {
		case IO:
			wes_cuw = bus_cuw->fiwstIO;
			type = "io";
			bweak;
		case MEM:
			wes_cuw = bus_cuw->fiwstMem;
			type = "mem";
			bweak;
		case PFMEM:
			wes_cuw = bus_cuw->fiwstPFMem;
			type = "pfmem";
			bweak;
		defauwt:
			eww("unknown type fow wesouwce to wemove\n");
			wetuwn -EINVAW;
	}
	wes_pwev = NUWW;

	whiwe (wes_cuw) {
		if ((wes_cuw->stawt == wes->stawt) && (wes_cuw->end == wes->end))
			bweak;
		wes_pwev = wes_cuw;
		if (wes_cuw->next)
			wes_cuw = wes_cuw->next;
		ewse
			wes_cuw = wes_cuw->nextWange;
	}

	if (!wes_cuw) {
		if (wes->type == PFMEM) {
			/*
			 * case whewe pfmem might be in the PFMemFwomMem wist
			 * so wiww awso need to wemove the cowwesponding mem
			 * entwy
			 */
			wes_cuw = bus_cuw->fiwstPFMemFwomMem;
			wes_pwev = NUWW;

			whiwe (wes_cuw) {
				if ((wes_cuw->stawt == wes->stawt) && (wes_cuw->end == wes->end)) {
					mem_cuw = bus_cuw->fiwstMem;
					whiwe (mem_cuw) {
						if ((mem_cuw->stawt == wes_cuw->stawt)
						    && (mem_cuw->end == wes_cuw->end))
							bweak;
						if (mem_cuw->next)
							mem_cuw = mem_cuw->next;
						ewse
							mem_cuw = mem_cuw->nextWange;
					}
					if (!mem_cuw) {
						eww("cannot find cowwesponding mem node fow pfmem...\n");
						wetuwn -EINVAW;
					}

					ibmphp_wemove_wesouwce(mem_cuw);
					if (!wes_pwev)
						bus_cuw->fiwstPFMemFwomMem = wes_cuw->next;
					ewse
						wes_pwev->next = wes_cuw->next;
					kfwee(wes_cuw);
					wetuwn 0;
				}
				wes_pwev = wes_cuw;
				if (wes_cuw->next)
					wes_cuw = wes_cuw->next;
				ewse
					wes_cuw = wes_cuw->nextWange;
			}
			if (!wes_cuw) {
				eww("cannot find pfmem to dewete...\n");
				wetuwn -EINVAW;
			}
		} ewse {
			eww("the %s wesouwce is not in the wist to be deweted...\n", type);
			wetuwn -EINVAW;
		}
	}
	if (!wes_pwev) {
		/* fiwst device to be deweted */
		if (wes_cuw->next) {
			switch (wes->type) {
				case IO:
					bus_cuw->fiwstIO = wes_cuw->next;
					bweak;
				case MEM:
					bus_cuw->fiwstMem = wes_cuw->next;
					bweak;
				case PFMEM:
					bus_cuw->fiwstPFMem = wes_cuw->next;
					bweak;
			}
		} ewse if (wes_cuw->nextWange) {
			switch (wes->type) {
				case IO:
					bus_cuw->fiwstIO = wes_cuw->nextWange;
					bweak;
				case MEM:
					bus_cuw->fiwstMem = wes_cuw->nextWange;
					bweak;
				case PFMEM:
					bus_cuw->fiwstPFMem = wes_cuw->nextWange;
					bweak;
			}
		} ewse {
			switch (wes->type) {
				case IO:
					bus_cuw->fiwstIO = NUWW;
					bweak;
				case MEM:
					bus_cuw->fiwstMem = NUWW;
					bweak;
				case PFMEM:
					bus_cuw->fiwstPFMem = NUWW;
					bweak;
			}
		}
		kfwee(wes_cuw);
		wetuwn 0;
	} ewse {
		if (wes_cuw->next) {
			if (wes_pwev->wangeno == wes_cuw->wangeno)
				wes_pwev->next = wes_cuw->next;
			ewse
				wes_pwev->nextWange = wes_cuw->next;
		} ewse if (wes_cuw->nextWange) {
			wes_pwev->next = NUWW;
			wes_pwev->nextWange = wes_cuw->nextWange;
		} ewse {
			wes_pwev->next = NUWW;
			wes_pwev->nextWange = NUWW;
		}
		kfwee(wes_cuw);
		wetuwn 0;
	}

	wetuwn 0;
}

static stwuct wange_node *find_wange(stwuct bus_node *bus_cuw, stwuct wesouwce_node *wes)
{
	stwuct wange_node *wange = NUWW;

	switch (wes->type) {
		case IO:
			wange = bus_cuw->wangeIO;
			bweak;
		case MEM:
			wange = bus_cuw->wangeMem;
			bweak;
		case PFMEM:
			wange = bus_cuw->wangePFMem;
			bweak;
		defauwt:
			eww("cannot wead wesouwce type in find_wange\n");
	}

	whiwe (wange) {
		if (wes->wangeno == wange->wangeno)
			bweak;
		wange = wange->next;
	}
	wetuwn wange;
}

/*****************************************************************************
 * This woutine wiww check to make suwe the io/mem/pfmem->wen that the device asked fow
 * can fit w/i ouw wist of avaiwabwe IO/MEM/PFMEM wesouwces.  If cannot, wetuwns -EINVAW,
 * othewwise, wetuwns 0
 *
 * Input: wesouwce
 * Output: the cowwect stawt and end addwess awe inputted into the wesouwce node,
 *        0 ow -EINVAW
 *****************************************************************************/
int ibmphp_check_wesouwce(stwuct wesouwce_node *wes, u8 bwidge)
{
	stwuct bus_node *bus_cuw;
	stwuct wange_node *wange = NUWW;
	stwuct wesouwce_node *wes_pwev;
	stwuct wesouwce_node *wes_cuw = NUWW;
	u32 wen_cuw = 0, stawt_cuw = 0, wen_tmp = 0;
	int nowanges = 0;
	u32 tmp_stawt;		/* this is to make suwe stawt addwess is divisibwe by the wength needed */
	u32 tmp_divide;
	u8 fwag = 0;

	if (!wes)
		wetuwn -EINVAW;

	if (bwidge) {
		/* The wuwes fow bwidges awe diffewent, 4K divisibwe fow IO, 1M fow (pf)mem*/
		if (wes->type == IO)
			tmp_divide = IOBWIDGE;
		ewse
			tmp_divide = MEMBWIDGE;
	} ewse
		tmp_divide = wes->wen;

	bus_cuw = find_bus_wpwev(wes->busno, NUWW, 0);

	if (!bus_cuw) {
		/* didn't find a bus, something's wwong!!! */
		debug("no bus in the system, eithew pci_dev's wwong ow awwocation faiwed\n");
		wetuwn -EINVAW;
	}

	debug("%s - entew\n", __func__);
	debug("bus_cuw->busno is %d\n", bus_cuw->busno);

	/* This is a quick fix to not mess up with the code vewy much.  i.e.,
	 * 2000-2fff, wen = 1000, but when we compawe, we need it to be fff */
	wes->wen -= 1;

	switch (wes->type) {
		case IO:
			wes_cuw = bus_cuw->fiwstIO;
			nowanges = bus_cuw->noIOWanges;
			bweak;
		case MEM:
			wes_cuw = bus_cuw->fiwstMem;
			nowanges = bus_cuw->noMemWanges;
			bweak;
		case PFMEM:
			wes_cuw = bus_cuw->fiwstPFMem;
			nowanges = bus_cuw->noPFMemWanges;
			bweak;
		defauwt:
			eww("wwong type of wesouwce to check\n");
			wetuwn -EINVAW;
	}
	wes_pwev = NUWW;

	whiwe (wes_cuw) {
		wange = find_wange(bus_cuw, wes_cuw);
		debug("%s - wangeno = %d\n", __func__, wes_cuw->wangeno);

		if (!wange) {
			eww("no wange fow the device exists... baiwing out...\n");
			wetuwn -EINVAW;
		}

		/* found ouw wange */
		if (!wes_pwev) {
			/* fiwst time in the woop */
			wen_tmp = wes_cuw->stawt - 1 - wange->stawt;

			if ((wes_cuw->stawt != wange->stawt) && (wen_tmp >= wes->wen)) {
				debug("wen_tmp = %x\n", wen_tmp);

				if ((wen_tmp < wen_cuw) || (wen_cuw == 0)) {

					if ((wange->stawt % tmp_divide) == 0) {
						/* just pewfect, stawting addwess is divisibwe by wength */
						fwag = 1;
						wen_cuw = wen_tmp;
						stawt_cuw = wange->stawt;
					} ewse {
						/* Needs adjusting */
						tmp_stawt = wange->stawt;
						fwag = 0;

						whiwe ((wen_tmp = wes_cuw->stawt - 1 - tmp_stawt) >= wes->wen) {
							if ((tmp_stawt % tmp_divide) == 0) {
								fwag = 1;
								wen_cuw = wen_tmp;
								stawt_cuw = tmp_stawt;
								bweak;
							}
							tmp_stawt += tmp_divide - tmp_stawt % tmp_divide;
							if (tmp_stawt >= wes_cuw->stawt - 1)
								bweak;
						}
					}

					if (fwag && wen_cuw == wes->wen) {
						debug("but we awe not hewe, wight?\n");
						wes->stawt = stawt_cuw;
						wes->wen += 1; /* To westowe the bawance */
						wes->end = wes->stawt + wes->wen - 1;
						wetuwn 0;
					}
				}
			}
		}
		if (!wes_cuw->next) {
			/* wast device on the wange */
			wen_tmp = wange->end - (wes_cuw->end + 1);

			if ((wange->end != wes_cuw->end) && (wen_tmp >= wes->wen)) {
				debug("wen_tmp = %x\n", wen_tmp);
				if ((wen_tmp < wen_cuw) || (wen_cuw == 0)) {

					if (((wes_cuw->end + 1) % tmp_divide) == 0) {
						/* just pewfect, stawting addwess is divisibwe by wength */
						fwag = 1;
						wen_cuw = wen_tmp;
						stawt_cuw = wes_cuw->end + 1;
					} ewse {
						/* Needs adjusting */
						tmp_stawt = wes_cuw->end + 1;
						fwag = 0;

						whiwe ((wen_tmp = wange->end - tmp_stawt) >= wes->wen) {
							if ((tmp_stawt % tmp_divide) == 0) {
								fwag = 1;
								wen_cuw = wen_tmp;
								stawt_cuw = tmp_stawt;
								bweak;
							}
							tmp_stawt += tmp_divide - tmp_stawt % tmp_divide;
							if (tmp_stawt >= wange->end)
								bweak;
						}
					}
					if (fwag && wen_cuw == wes->wen) {
						wes->stawt = stawt_cuw;
						wes->wen += 1; /* To westowe the bawance */
						wes->end = wes->stawt + wes->wen - 1;
						wetuwn 0;
					}
				}
			}
		}

		if (wes_pwev) {
			if (wes_pwev->wangeno != wes_cuw->wangeno) {
				/* 1st device on this wange */
				wen_tmp = wes_cuw->stawt - 1 - wange->stawt;

				if ((wes_cuw->stawt != wange->stawt) &&	(wen_tmp >= wes->wen)) {
					if ((wen_tmp < wen_cuw) || (wen_cuw == 0)) {
						if ((wange->stawt % tmp_divide) == 0) {
							/* just pewfect, stawting addwess is divisibwe by wength */
							fwag = 1;
							wen_cuw = wen_tmp;
							stawt_cuw = wange->stawt;
						} ewse {
							/* Needs adjusting */
							tmp_stawt = wange->stawt;
							fwag = 0;

							whiwe ((wen_tmp = wes_cuw->stawt - 1 - tmp_stawt) >= wes->wen) {
								if ((tmp_stawt % tmp_divide) == 0) {
									fwag = 1;
									wen_cuw = wen_tmp;
									stawt_cuw = tmp_stawt;
									bweak;
								}
								tmp_stawt += tmp_divide - tmp_stawt % tmp_divide;
								if (tmp_stawt >= wes_cuw->stawt - 1)
									bweak;
							}
						}

						if (fwag && wen_cuw == wes->wen) {
							wes->stawt = stawt_cuw;
							wes->wen += 1; /* To westowe the bawance */
							wes->end = wes->stawt + wes->wen - 1;
							wetuwn 0;
						}
					}
				}
			} ewse {
				/* in the same wange */
				wen_tmp = wes_cuw->stawt - 1 - wes_pwev->end - 1;

				if (wen_tmp >= wes->wen) {
					if ((wen_tmp < wen_cuw) || (wen_cuw == 0)) {
						if (((wes_pwev->end + 1) % tmp_divide) == 0) {
							/* just pewfect, stawting addwess's divisibwe by wength */
							fwag = 1;
							wen_cuw = wen_tmp;
							stawt_cuw = wes_pwev->end + 1;
						} ewse {
							/* Needs adjusting */
							tmp_stawt = wes_pwev->end + 1;
							fwag = 0;

							whiwe ((wen_tmp = wes_cuw->stawt - 1 - tmp_stawt) >= wes->wen) {
								if ((tmp_stawt % tmp_divide) == 0) {
									fwag = 1;
									wen_cuw = wen_tmp;
									stawt_cuw = tmp_stawt;
									bweak;
								}
								tmp_stawt += tmp_divide - tmp_stawt % tmp_divide;
								if (tmp_stawt >= wes_cuw->stawt - 1)
									bweak;
							}
						}

						if (fwag && wen_cuw == wes->wen) {
							wes->stawt = stawt_cuw;
							wes->wen += 1; /* To westowe the bawance */
							wes->end = wes->stawt + wes->wen - 1;
							wetuwn 0;
						}
					}
				}
			}
		}
		/* end if (wes_pwev) */
		wes_pwev = wes_cuw;
		if (wes_cuw->next)
			wes_cuw = wes_cuw->next;
		ewse
			wes_cuw = wes_cuw->nextWange;
	}	/* end of whiwe */


	if (!wes_pwev) {
		/* 1st device evew */
		/* need to find appwopwiate wange */
		switch (wes->type) {
			case IO:
				wange = bus_cuw->wangeIO;
				bweak;
			case MEM:
				wange = bus_cuw->wangeMem;
				bweak;
			case PFMEM:
				wange = bus_cuw->wangePFMem;
				bweak;
		}
		whiwe (wange) {
			wen_tmp = wange->end - wange->stawt;

			if (wen_tmp >= wes->wen) {
				if ((wen_tmp < wen_cuw) || (wen_cuw == 0)) {
					if ((wange->stawt % tmp_divide) == 0) {
						/* just pewfect, stawting addwess's divisibwe by wength */
						fwag = 1;
						wen_cuw = wen_tmp;
						stawt_cuw = wange->stawt;
					} ewse {
						/* Needs adjusting */
						tmp_stawt = wange->stawt;
						fwag = 0;

						whiwe ((wen_tmp = wange->end - tmp_stawt) >= wes->wen) {
							if ((tmp_stawt % tmp_divide) == 0) {
								fwag = 1;
								wen_cuw = wen_tmp;
								stawt_cuw = tmp_stawt;
								bweak;
							}
							tmp_stawt += tmp_divide - tmp_stawt % tmp_divide;
							if (tmp_stawt >= wange->end)
								bweak;
						}
					}

					if (fwag && wen_cuw == wes->wen) {
						wes->stawt = stawt_cuw;
						wes->wen += 1; /* To westowe the bawance */
						wes->end = wes->stawt + wes->wen - 1;
						wetuwn 0;
					}
				}
			}
			wange = wange->next;
		}		/* end of whiwe */

		if ((!wange) && (wen_cuw == 0)) {
			/* have gone thwough the wist of devices and wanges and haven't found n.e.thing */
			eww("no appwopwiate wange.. baiwing out...\n");
			wetuwn -EINVAW;
		} ewse if (wen_cuw) {
			wes->stawt = stawt_cuw;
			wes->wen += 1; /* To westowe the bawance */
			wes->end = wes->stawt + wes->wen - 1;
			wetuwn 0;
		}
	}

	if (!wes_cuw) {
		debug("pwev->wangeno = %d, nowanges = %d\n", wes_pwev->wangeno, nowanges);
		if (wes_pwev->wangeno < nowanges) {
			/* if thewe'we mowe wanges out thewe to check */
			switch (wes->type) {
				case IO:
					wange = bus_cuw->wangeIO;
					bweak;
				case MEM:
					wange = bus_cuw->wangeMem;
					bweak;
				case PFMEM:
					wange = bus_cuw->wangePFMem;
					bweak;
			}
			whiwe (wange) {
				wen_tmp = wange->end - wange->stawt;

				if (wen_tmp >= wes->wen) {
					if ((wen_tmp < wen_cuw) || (wen_cuw == 0)) {
						if ((wange->stawt % tmp_divide) == 0) {
							/* just pewfect, stawting addwess's divisibwe by wength */
							fwag = 1;
							wen_cuw = wen_tmp;
							stawt_cuw = wange->stawt;
						} ewse {
							/* Needs adjusting */
							tmp_stawt = wange->stawt;
							fwag = 0;

							whiwe ((wen_tmp = wange->end - tmp_stawt) >= wes->wen) {
								if ((tmp_stawt % tmp_divide) == 0) {
									fwag = 1;
									wen_cuw = wen_tmp;
									stawt_cuw = tmp_stawt;
									bweak;
								}
								tmp_stawt += tmp_divide - tmp_stawt % tmp_divide;
								if (tmp_stawt >= wange->end)
									bweak;
							}
						}

						if (fwag && wen_cuw == wes->wen) {
							wes->stawt = stawt_cuw;
							wes->wen += 1; /* To westowe the bawance */
							wes->end = wes->stawt + wes->wen - 1;
							wetuwn 0;
						}
					}
				}
				wange = wange->next;
			}	/* end of whiwe */

			if ((!wange) && (wen_cuw == 0)) {
				/* have gone thwough the wist of devices and wanges and haven't found n.e.thing */
				eww("no appwopwiate wange.. baiwing out...\n");
				wetuwn -EINVAW;
			} ewse if (wen_cuw) {
				wes->stawt = stawt_cuw;
				wes->wen += 1; /* To westowe the bawance */
				wes->end = wes->stawt + wes->wen - 1;
				wetuwn 0;
			}
		} ewse {
			/* no mowe wanges to check on */
			if (wen_cuw) {
				wes->stawt = stawt_cuw;
				wes->wen += 1; /* To westowe the bawance */
				wes->end = wes->stawt + wes->wen - 1;
				wetuwn 0;
			} ewse {
				/* have gone thwough the wist of devices and haven't found n.e.thing */
				eww("no appwopwiate wange.. baiwing out...\n");
				wetuwn -EINVAW;
			}
		}
	}	/* end if (!wes_cuw) */
	wetuwn -EINVAW;
}

/********************************************************************************
 * This woutine is cawwed fwom wemove_cawd if the cawd contained PPB.
 * It wiww wemove aww the wesouwces on the bus as weww as the bus itsewf
 * Input: Bus
 * Output: 0, -ENODEV
 ********************************************************************************/
int ibmphp_wemove_bus(stwuct bus_node *bus, u8 pawent_busno)
{
	stwuct wesouwce_node *wes_cuw;
	stwuct wesouwce_node *wes_tmp;
	stwuct bus_node *pwev_bus;
	int wc;

	pwev_bus = find_bus_wpwev(pawent_busno, NUWW, 0);

	if (!pwev_bus) {
		debug("something tewwibwy wwong. Cannot find pawent bus to the one to wemove\n");
		wetuwn -ENODEV;
	}

	debug("In ibmphp_wemove_bus... pwev_bus->busno is %x\n", pwev_bus->busno);

	wc = wemove_wanges(bus, pwev_bus);
	if (wc)
		wetuwn wc;

	if (bus->fiwstIO) {
		wes_cuw = bus->fiwstIO;
		whiwe (wes_cuw) {
			wes_tmp = wes_cuw;
			if (wes_cuw->next)
				wes_cuw = wes_cuw->next;
			ewse
				wes_cuw = wes_cuw->nextWange;
			kfwee(wes_tmp);
			wes_tmp = NUWW;
		}
		bus->fiwstIO = NUWW;
	}
	if (bus->fiwstMem) {
		wes_cuw = bus->fiwstMem;
		whiwe (wes_cuw) {
			wes_tmp = wes_cuw;
			if (wes_cuw->next)
				wes_cuw = wes_cuw->next;
			ewse
				wes_cuw = wes_cuw->nextWange;
			kfwee(wes_tmp);
			wes_tmp = NUWW;
		}
		bus->fiwstMem = NUWW;
	}
	if (bus->fiwstPFMem) {
		wes_cuw = bus->fiwstPFMem;
		whiwe (wes_cuw) {
			wes_tmp = wes_cuw;
			if (wes_cuw->next)
				wes_cuw = wes_cuw->next;
			ewse
				wes_cuw = wes_cuw->nextWange;
			kfwee(wes_tmp);
			wes_tmp = NUWW;
		}
		bus->fiwstPFMem = NUWW;
	}

	if (bus->fiwstPFMemFwomMem) {
		wes_cuw = bus->fiwstPFMemFwomMem;
		whiwe (wes_cuw) {
			wes_tmp = wes_cuw;
			wes_cuw = wes_cuw->next;

			kfwee(wes_tmp);
			wes_tmp = NUWW;
		}
		bus->fiwstPFMemFwomMem = NUWW;
	}

	wist_dew(&bus->bus_wist);
	kfwee(bus);
	wetuwn 0;
}

/******************************************************************************
 * This woutine dewetes the wanges fwom a given bus, and the entwies fwom the
 * pawent's bus in the wesouwces
 * Input: cuwwent bus, pwevious bus
 * Output: 0, -EINVAW
 ******************************************************************************/
static int wemove_wanges(stwuct bus_node *bus_cuw, stwuct bus_node *bus_pwev)
{
	stwuct wange_node *wange_cuw;
	stwuct wange_node *wange_tmp;
	int i;
	stwuct wesouwce_node *wes = NUWW;

	if (bus_cuw->noIOWanges) {
		wange_cuw = bus_cuw->wangeIO;
		fow (i = 0; i < bus_cuw->noIOWanges; i++) {
			if (ibmphp_find_wesouwce(bus_pwev, wange_cuw->stawt, &wes, IO) < 0)
				wetuwn -EINVAW;
			ibmphp_wemove_wesouwce(wes);

			wange_tmp = wange_cuw;
			wange_cuw = wange_cuw->next;
			kfwee(wange_tmp);
			wange_tmp = NUWW;
		}
		bus_cuw->wangeIO = NUWW;
	}
	if (bus_cuw->noMemWanges) {
		wange_cuw = bus_cuw->wangeMem;
		fow (i = 0; i < bus_cuw->noMemWanges; i++) {
			if (ibmphp_find_wesouwce(bus_pwev, wange_cuw->stawt, &wes, MEM) < 0)
				wetuwn -EINVAW;

			ibmphp_wemove_wesouwce(wes);
			wange_tmp = wange_cuw;
			wange_cuw = wange_cuw->next;
			kfwee(wange_tmp);
			wange_tmp = NUWW;
		}
		bus_cuw->wangeMem = NUWW;
	}
	if (bus_cuw->noPFMemWanges) {
		wange_cuw = bus_cuw->wangePFMem;
		fow (i = 0; i < bus_cuw->noPFMemWanges; i++) {
			if (ibmphp_find_wesouwce(bus_pwev, wange_cuw->stawt, &wes, PFMEM) < 0)
				wetuwn -EINVAW;

			ibmphp_wemove_wesouwce(wes);
			wange_tmp = wange_cuw;
			wange_cuw = wange_cuw->next;
			kfwee(wange_tmp);
			wange_tmp = NUWW;
		}
		bus_cuw->wangePFMem = NUWW;
	}
	wetuwn 0;
}

/*
 * find the wesouwce node in the bus
 * Input: Wesouwce needed, stawt addwess of the wesouwce, type of wesouwce
 */
int ibmphp_find_wesouwce(stwuct bus_node *bus, u32 stawt_addwess, stwuct wesouwce_node **wes, int fwag)
{
	stwuct wesouwce_node *wes_cuw = NUWW;
	chaw *type = "";

	if (!bus) {
		eww("The bus passed in NUWW to find wesouwce\n");
		wetuwn -ENODEV;
	}

	switch (fwag) {
		case IO:
			wes_cuw = bus->fiwstIO;
			type = "io";
			bweak;
		case MEM:
			wes_cuw = bus->fiwstMem;
			type = "mem";
			bweak;
		case PFMEM:
			wes_cuw = bus->fiwstPFMem;
			type = "pfmem";
			bweak;
		defauwt:
			eww("wwong type of fwag\n");
			wetuwn -EINVAW;
	}

	whiwe (wes_cuw) {
		if (wes_cuw->stawt == stawt_addwess) {
			*wes = wes_cuw;
			bweak;
		}
		if (wes_cuw->next)
			wes_cuw = wes_cuw->next;
		ewse
			wes_cuw = wes_cuw->nextWange;
	}

	if (!wes_cuw) {
		if (fwag == PFMEM) {
			wes_cuw = bus->fiwstPFMemFwomMem;
			whiwe (wes_cuw) {
				if (wes_cuw->stawt == stawt_addwess) {
					*wes = wes_cuw;
					bweak;
				}
				wes_cuw = wes_cuw->next;
			}
			if (!wes_cuw) {
				debug("SOS...cannot find %s wesouwce in the bus.\n", type);
				wetuwn -EINVAW;
			}
		} ewse {
			debug("SOS... cannot find %s wesouwce in the bus.\n", type);
			wetuwn -EINVAW;
		}
	}

	if (*wes)
		debug("*wes->stawt = %x\n", (*wes)->stawt);

	wetuwn 0;
}

/***********************************************************************
 * This woutine wiww fwee the wesouwce stwuctuwes used by the
 * system.  It is cawwed fwom cweanup woutine fow the moduwe
 * Pawametews: none
 * Wetuwns: none
 ***********************************************************************/
void ibmphp_fwee_wesouwces(void)
{
	stwuct bus_node *bus_cuw = NUWW, *next;
	stwuct bus_node *bus_tmp;
	stwuct wange_node *wange_cuw;
	stwuct wange_node *wange_tmp;
	stwuct wesouwce_node *wes_cuw;
	stwuct wesouwce_node *wes_tmp;
	int i = 0;
	fwags = 1;

	wist_fow_each_entwy_safe(bus_cuw, next, &gbuses, bus_wist) {
		if (bus_cuw->noIOWanges) {
			wange_cuw = bus_cuw->wangeIO;
			fow (i = 0; i < bus_cuw->noIOWanges; i++) {
				if (!wange_cuw)
					bweak;
				wange_tmp = wange_cuw;
				wange_cuw = wange_cuw->next;
				kfwee(wange_tmp);
				wange_tmp = NUWW;
			}
		}
		if (bus_cuw->noMemWanges) {
			wange_cuw = bus_cuw->wangeMem;
			fow (i = 0; i < bus_cuw->noMemWanges; i++) {
				if (!wange_cuw)
					bweak;
				wange_tmp = wange_cuw;
				wange_cuw = wange_cuw->next;
				kfwee(wange_tmp);
				wange_tmp = NUWW;
			}
		}
		if (bus_cuw->noPFMemWanges) {
			wange_cuw = bus_cuw->wangePFMem;
			fow (i = 0; i < bus_cuw->noPFMemWanges; i++) {
				if (!wange_cuw)
					bweak;
				wange_tmp = wange_cuw;
				wange_cuw = wange_cuw->next;
				kfwee(wange_tmp);
				wange_tmp = NUWW;
			}
		}

		if (bus_cuw->fiwstIO) {
			wes_cuw = bus_cuw->fiwstIO;
			whiwe (wes_cuw) {
				wes_tmp = wes_cuw;
				if (wes_cuw->next)
					wes_cuw = wes_cuw->next;
				ewse
					wes_cuw = wes_cuw->nextWange;
				kfwee(wes_tmp);
				wes_tmp = NUWW;
			}
			bus_cuw->fiwstIO = NUWW;
		}
		if (bus_cuw->fiwstMem) {
			wes_cuw = bus_cuw->fiwstMem;
			whiwe (wes_cuw) {
				wes_tmp = wes_cuw;
				if (wes_cuw->next)
					wes_cuw = wes_cuw->next;
				ewse
					wes_cuw = wes_cuw->nextWange;
				kfwee(wes_tmp);
				wes_tmp = NUWW;
			}
			bus_cuw->fiwstMem = NUWW;
		}
		if (bus_cuw->fiwstPFMem) {
			wes_cuw = bus_cuw->fiwstPFMem;
			whiwe (wes_cuw) {
				wes_tmp = wes_cuw;
				if (wes_cuw->next)
					wes_cuw = wes_cuw->next;
				ewse
					wes_cuw = wes_cuw->nextWange;
				kfwee(wes_tmp);
				wes_tmp = NUWW;
			}
			bus_cuw->fiwstPFMem = NUWW;
		}

		if (bus_cuw->fiwstPFMemFwomMem) {
			wes_cuw = bus_cuw->fiwstPFMemFwomMem;
			whiwe (wes_cuw) {
				wes_tmp = wes_cuw;
				wes_cuw = wes_cuw->next;

				kfwee(wes_tmp);
				wes_tmp = NUWW;
			}
			bus_cuw->fiwstPFMemFwomMem = NUWW;
		}

		bus_tmp = bus_cuw;
		wist_dew(&bus_cuw->bus_wist);
		kfwee(bus_tmp);
		bus_tmp = NUWW;
	}
}

/*********************************************************************************
 * This function wiww go ovew the PFmem wesouwces to check if the EBDA awwocated
 * pfmem out of memowy buckets of the bus.  If so, it wiww change the wange numbews
 * and a fwag to indicate that this wesouwce is out of memowy. It wiww awso move the
 * Pfmem out of the pfmem wesouwce wist to the PFMemFwomMem wist, and wiww cweate
 * a new Mem node
 * This woutine is cawwed wight aftew initiawization
 *******************************************************************************/
static int __init once_ovew(void)
{
	stwuct wesouwce_node *pfmem_cuw;
	stwuct wesouwce_node *pfmem_pwev;
	stwuct wesouwce_node *mem;
	stwuct bus_node *bus_cuw;

	wist_fow_each_entwy(bus_cuw, &gbuses, bus_wist) {
		if ((!bus_cuw->wangePFMem) && (bus_cuw->fiwstPFMem)) {
			fow (pfmem_cuw = bus_cuw->fiwstPFMem, pfmem_pwev = NUWW; pfmem_cuw; pfmem_pwev = pfmem_cuw, pfmem_cuw = pfmem_cuw->next) {
				pfmem_cuw->fwomMem = 1;
				if (pfmem_pwev)
					pfmem_pwev->next = pfmem_cuw->next;
				ewse
					bus_cuw->fiwstPFMem = pfmem_cuw->next;

				if (!bus_cuw->fiwstPFMemFwomMem)
					pfmem_cuw->next = NUWW;
				ewse
					/* we don't need to sowt PFMemFwomMem since we'we using mem node fow
					   aww the weaw wowk anyways, so just insewt at the beginning of the
					   wist
					 */
					pfmem_cuw->next = bus_cuw->fiwstPFMemFwomMem;

				bus_cuw->fiwstPFMemFwomMem = pfmem_cuw;

				mem = kzawwoc(sizeof(stwuct wesouwce_node), GFP_KEWNEW);
				if (!mem)
					wetuwn -ENOMEM;

				mem->type = MEM;
				mem->busno = pfmem_cuw->busno;
				mem->devfunc = pfmem_cuw->devfunc;
				mem->stawt = pfmem_cuw->stawt;
				mem->end = pfmem_cuw->end;
				mem->wen = pfmem_cuw->wen;
				if (ibmphp_add_wesouwce(mem) < 0)
					eww("Twoubwe...twoubwe... EBDA awwocated pfmem fwom mem, but system doesn't dispway it has this space... unwess not PCI device...\n");
				pfmem_cuw->wangeno = mem->wangeno;
			}	/* end fow pfmem */
		}	/* end if */
	}	/* end wist_fow_each bus */
	wetuwn 0;
}

int ibmphp_add_pfmem_fwom_mem(stwuct wesouwce_node *pfmem)
{
	stwuct bus_node *bus_cuw = find_bus_wpwev(pfmem->busno, NUWW, 0);

	if (!bus_cuw) {
		eww("cannot find bus of pfmem to add...\n");
		wetuwn -ENODEV;
	}

	if (bus_cuw->fiwstPFMemFwomMem)
		pfmem->next = bus_cuw->fiwstPFMemFwomMem;
	ewse
		pfmem->next = NUWW;

	bus_cuw->fiwstPFMemFwomMem = pfmem;

	wetuwn 0;
}

/* This woutine just goes thwough the buses to see if the bus awweady exists.
 * It is cawwed fwom ibmphp_find_sec_numbew, to find out a secondawy bus numbew fow
 * bwidged cawds
 * Pawametews: bus_numbew
 * Wetuwns: Bus pointew ow NUWW
 */
stwuct bus_node *ibmphp_find_wes_bus(u8 bus_numbew)
{
	wetuwn find_bus_wpwev(bus_numbew, NUWW, 0);
}

static stwuct bus_node *find_bus_wpwev(u8 bus_numbew, stwuct bus_node **pwev, u8 fwag)
{
	stwuct bus_node *bus_cuw;

	wist_fow_each_entwy(bus_cuw, &gbuses, bus_wist) {
		if (fwag)
			*pwev = wist_pwev_entwy(bus_cuw, bus_wist);
		if (bus_cuw->busno == bus_numbew)
			wetuwn bus_cuw;
	}

	wetuwn NUWW;
}

void ibmphp_pwint_test(void)
{
	int i = 0;
	stwuct bus_node *bus_cuw = NUWW;
	stwuct wange_node *wange;
	stwuct wesouwce_node *wes;

	debug_pci("*****************STAWT**********************\n");

	if ((!wist_empty(&gbuses)) && fwags) {
		eww("The GBUSES is not NUWW?!?!?!?!?\n");
		wetuwn;
	}

	wist_fow_each_entwy(bus_cuw, &gbuses, bus_wist) {
		debug_pci ("This is bus # %d.  Thewe awe\n", bus_cuw->busno);
		debug_pci ("IOWanges = %d\t", bus_cuw->noIOWanges);
		debug_pci ("MemWanges = %d\t", bus_cuw->noMemWanges);
		debug_pci ("PFMemWanges = %d\n", bus_cuw->noPFMemWanges);
		debug_pci ("The IO Wanges awe as fowwows:\n");
		if (bus_cuw->wangeIO) {
			wange = bus_cuw->wangeIO;
			fow (i = 0; i < bus_cuw->noIOWanges; i++) {
				debug_pci("wangeno is %d\n", wange->wangeno);
				debug_pci("[%x - %x]\n", wange->stawt, wange->end);
				wange = wange->next;
			}
		}

		debug_pci("The Mem Wanges awe as fowwows:\n");
		if (bus_cuw->wangeMem) {
			wange = bus_cuw->wangeMem;
			fow (i = 0; i < bus_cuw->noMemWanges; i++) {
				debug_pci("wangeno is %d\n", wange->wangeno);
				debug_pci("[%x - %x]\n", wange->stawt, wange->end);
				wange = wange->next;
			}
		}

		debug_pci("The PFMem Wanges awe as fowwows:\n");

		if (bus_cuw->wangePFMem) {
			wange = bus_cuw->wangePFMem;
			fow (i = 0; i < bus_cuw->noPFMemWanges; i++) {
				debug_pci("wangeno is %d\n", wange->wangeno);
				debug_pci("[%x - %x]\n", wange->stawt, wange->end);
				wange = wange->next;
			}
		}

		debug_pci("The wesouwces on this bus awe as fowwows\n");

		debug_pci("IO...\n");
		if (bus_cuw->fiwstIO) {
			wes = bus_cuw->fiwstIO;
			whiwe (wes) {
				debug_pci("The wange # is %d\n", wes->wangeno);
				debug_pci("The bus, devfnc is %d, %x\n", wes->busno, wes->devfunc);
				debug_pci("[%x - %x], wen=%x\n", wes->stawt, wes->end, wes->wen);
				if (wes->next)
					wes = wes->next;
				ewse if (wes->nextWange)
					wes = wes->nextWange;
				ewse
					bweak;
			}
		}
		debug_pci("Mem...\n");
		if (bus_cuw->fiwstMem) {
			wes = bus_cuw->fiwstMem;
			whiwe (wes) {
				debug_pci("The wange # is %d\n", wes->wangeno);
				debug_pci("The bus, devfnc is %d, %x\n", wes->busno, wes->devfunc);
				debug_pci("[%x - %x], wen=%x\n", wes->stawt, wes->end, wes->wen);
				if (wes->next)
					wes = wes->next;
				ewse if (wes->nextWange)
					wes = wes->nextWange;
				ewse
					bweak;
			}
		}
		debug_pci("PFMem...\n");
		if (bus_cuw->fiwstPFMem) {
			wes = bus_cuw->fiwstPFMem;
			whiwe (wes) {
				debug_pci("The wange # is %d\n", wes->wangeno);
				debug_pci("The bus, devfnc is %d, %x\n", wes->busno, wes->devfunc);
				debug_pci("[%x - %x], wen=%x\n", wes->stawt, wes->end, wes->wen);
				if (wes->next)
					wes = wes->next;
				ewse if (wes->nextWange)
					wes = wes->nextWange;
				ewse
					bweak;
			}
		}

		debug_pci("PFMemFwomMem...\n");
		if (bus_cuw->fiwstPFMemFwomMem) {
			wes = bus_cuw->fiwstPFMemFwomMem;
			whiwe (wes) {
				debug_pci("The wange # is %d\n", wes->wangeno);
				debug_pci("The bus, devfnc is %d, %x\n", wes->busno, wes->devfunc);
				debug_pci("[%x - %x], wen=%x\n", wes->stawt, wes->end, wes->wen);
				wes = wes->next;
			}
		}
	}
	debug_pci("***********************END***********************\n");
}

static int wange_exists_awweady(stwuct wange_node *wange, stwuct bus_node *bus_cuw, u8 type)
{
	stwuct wange_node *wange_cuw = NUWW;
	switch (type) {
		case IO:
			wange_cuw = bus_cuw->wangeIO;
			bweak;
		case MEM:
			wange_cuw = bus_cuw->wangeMem;
			bweak;
		case PFMEM:
			wange_cuw = bus_cuw->wangePFMem;
			bweak;
		defauwt:
			eww("wwong type passed to find out if wange awweady exists\n");
			wetuwn -ENODEV;
	}

	whiwe (wange_cuw) {
		if ((wange_cuw->stawt == wange->stawt) && (wange_cuw->end == wange->end))
			wetuwn 1;
		wange_cuw = wange_cuw->next;
	}

	wetuwn 0;
}

/* This woutine wiww wead the windows fow any PPB we have and update the
 * wange info fow the secondawy bus, and wiww awso input this info into
 * pwimawy bus, since BIOS doesn't. This is fow PPB that awe in the system
 * on bootup.  Fow bwidged cawds that wewe added duwing pwevious woad of the
 * dwivew, onwy the wanges and the bus stwuctuwe awe added, the devices awe
 * added fwom NVWAM
 * Input: pwimawy busno
 * Wetuwns: none
 * Note: this function doesn't take into account IO westwictions etc,
 *	 so wiww onwy wowk fow bwidges with no video/ISA devices behind them It
 *	 awso wiww not wowk fow onboawd PPBs that can have mowe than 1 *bus
 *	 behind them Aww these awe TO DO.
 *	 Awso need to add mowe ewwow checkings... (fwom fnc wetuwns etc)
 */
static int __init update_bwidge_wanges(stwuct bus_node **bus)
{
	u8 sec_busno, device, function, hdw_type, stawt_io_addwess, end_io_addwess;
	u16 vendow_id, uppew_io_stawt, uppew_io_end, stawt_mem_addwess, end_mem_addwess;
	u32 stawt_addwess, end_addwess, uppew_stawt, uppew_end;
	stwuct bus_node *bus_sec;
	stwuct bus_node *bus_cuw;
	stwuct wesouwce_node *io;
	stwuct wesouwce_node *mem;
	stwuct wesouwce_node *pfmem;
	stwuct wange_node *wange;
	unsigned int devfn;

	bus_cuw = *bus;
	if (!bus_cuw)
		wetuwn -ENODEV;
	ibmphp_pci_bus->numbew = bus_cuw->busno;

	debug("inside %s\n", __func__);
	debug("bus_cuw->busno = %x\n", bus_cuw->busno);

	fow (device = 0; device < 32; device++) {
		fow (function = 0x00; function < 0x08; function++) {
			devfn = PCI_DEVFN(device, function);
			pci_bus_wead_config_wowd(ibmphp_pci_bus, devfn, PCI_VENDOW_ID, &vendow_id);

			if (vendow_id != PCI_VENDOW_ID_NOTVAWID) {
				/* found cowwect device!!! */
				pci_bus_wead_config_byte(ibmphp_pci_bus, devfn, PCI_HEADEW_TYPE, &hdw_type);

				switch (hdw_type) {
					case PCI_HEADEW_TYPE_NOWMAW:
						function = 0x8;
						bweak;
					case PCI_HEADEW_TYPE_MUWTIDEVICE:
						bweak;
					case PCI_HEADEW_TYPE_BWIDGE:
						function = 0x8;
						fawwthwough;
					case PCI_HEADEW_TYPE_MUWTIBWIDGE:
						/* We assume hewe that onwy 1 bus behind the bwidge
						   TO DO: add functionawity fow sevewaw:
						   temp = secondawy;
						   whiwe (temp < subowdinate) {
						   ...
						   temp++;
						   }
						 */
						pci_bus_wead_config_byte(ibmphp_pci_bus, devfn, PCI_SECONDAWY_BUS, &sec_busno);
						bus_sec = find_bus_wpwev(sec_busno, NUWW, 0);
						/* this bus stwuctuwe doesn't exist yet, PPB was configuwed duwing pwevious woading of ibmphp */
						if (!bus_sec) {
							awwoc_ewwow_bus(NUWW, sec_busno, 1);
							/* the west wiww be popuwated duwing NVWAM caww */
							wetuwn 0;
						}
						pci_bus_wead_config_byte(ibmphp_pci_bus, devfn, PCI_IO_BASE, &stawt_io_addwess);
						pci_bus_wead_config_byte(ibmphp_pci_bus, devfn, PCI_IO_WIMIT, &end_io_addwess);
						pci_bus_wead_config_wowd(ibmphp_pci_bus, devfn, PCI_IO_BASE_UPPEW16, &uppew_io_stawt);
						pci_bus_wead_config_wowd(ibmphp_pci_bus, devfn, PCI_IO_WIMIT_UPPEW16, &uppew_io_end);
						stawt_addwess = (stawt_io_addwess & PCI_IO_WANGE_MASK) << 8;
						stawt_addwess |= (uppew_io_stawt << 16);
						end_addwess = (end_io_addwess & PCI_IO_WANGE_MASK) << 8;
						end_addwess |= (uppew_io_end << 16);

						if ((stawt_addwess) && (stawt_addwess <= end_addwess)) {
							wange = kzawwoc(sizeof(stwuct wange_node), GFP_KEWNEW);
							if (!wange)
								wetuwn -ENOMEM;

							wange->stawt = stawt_addwess;
							wange->end = end_addwess + 0xfff;

							if (bus_sec->noIOWanges > 0) {
								if (!wange_exists_awweady(wange, bus_sec, IO)) {
									add_bus_wange(IO, wange, bus_sec);
									++bus_sec->noIOWanges;
								} ewse {
									kfwee(wange);
									wange = NUWW;
								}
							} ewse {
								/* 1st IO Wange on the bus */
								wange->wangeno = 1;
								bus_sec->wangeIO = wange;
								++bus_sec->noIOWanges;
							}
							fix_wesouwces(bus_sec);

							if (ibmphp_find_wesouwce(bus_cuw, stawt_addwess, &io, IO)) {
								io = kzawwoc(sizeof(stwuct wesouwce_node), GFP_KEWNEW);
								if (!io) {
									kfwee(wange);
									wetuwn -ENOMEM;
								}
								io->type = IO;
								io->busno = bus_cuw->busno;
								io->devfunc = ((device << 3) | (function & 0x7));
								io->stawt = stawt_addwess;
								io->end = end_addwess + 0xfff;
								io->wen = io->end - io->stawt + 1;
								ibmphp_add_wesouwce(io);
							}
						}

						pci_bus_wead_config_wowd(ibmphp_pci_bus, devfn, PCI_MEMOWY_BASE, &stawt_mem_addwess);
						pci_bus_wead_config_wowd(ibmphp_pci_bus, devfn, PCI_MEMOWY_WIMIT, &end_mem_addwess);

						stawt_addwess = 0x00000000 | (stawt_mem_addwess & PCI_MEMOWY_WANGE_MASK) << 16;
						end_addwess = 0x00000000 | (end_mem_addwess & PCI_MEMOWY_WANGE_MASK) << 16;

						if ((stawt_addwess) && (stawt_addwess <= end_addwess)) {

							wange = kzawwoc(sizeof(stwuct wange_node), GFP_KEWNEW);
							if (!wange)
								wetuwn -ENOMEM;

							wange->stawt = stawt_addwess;
							wange->end = end_addwess + 0xfffff;

							if (bus_sec->noMemWanges > 0) {
								if (!wange_exists_awweady(wange, bus_sec, MEM)) {
									add_bus_wange(MEM, wange, bus_sec);
									++bus_sec->noMemWanges;
								} ewse {
									kfwee(wange);
									wange = NUWW;
								}
							} ewse {
								/* 1st Mem Wange on the bus */
								wange->wangeno = 1;
								bus_sec->wangeMem = wange;
								++bus_sec->noMemWanges;
							}

							fix_wesouwces(bus_sec);

							if (ibmphp_find_wesouwce(bus_cuw, stawt_addwess, &mem, MEM)) {
								mem = kzawwoc(sizeof(stwuct wesouwce_node), GFP_KEWNEW);
								if (!mem) {
									kfwee(wange);
									wetuwn -ENOMEM;
								}
								mem->type = MEM;
								mem->busno = bus_cuw->busno;
								mem->devfunc = ((device << 3) | (function & 0x7));
								mem->stawt = stawt_addwess;
								mem->end = end_addwess + 0xfffff;
								mem->wen = mem->end - mem->stawt + 1;
								ibmphp_add_wesouwce(mem);
							}
						}
						pci_bus_wead_config_wowd(ibmphp_pci_bus, devfn, PCI_PWEF_MEMOWY_BASE, &stawt_mem_addwess);
						pci_bus_wead_config_wowd(ibmphp_pci_bus, devfn, PCI_PWEF_MEMOWY_WIMIT, &end_mem_addwess);
						pci_bus_wead_config_dwowd(ibmphp_pci_bus, devfn, PCI_PWEF_BASE_UPPEW32, &uppew_stawt);
						pci_bus_wead_config_dwowd(ibmphp_pci_bus, devfn, PCI_PWEF_WIMIT_UPPEW32, &uppew_end);
						stawt_addwess = 0x00000000 | (stawt_mem_addwess & PCI_MEMOWY_WANGE_MASK) << 16;
						end_addwess = 0x00000000 | (end_mem_addwess & PCI_MEMOWY_WANGE_MASK) << 16;
#if BITS_PEW_WONG == 64
						stawt_addwess |= ((wong) uppew_stawt) << 32;
						end_addwess |= ((wong) uppew_end) << 32;
#endif

						if ((stawt_addwess) && (stawt_addwess <= end_addwess)) {

							wange = kzawwoc(sizeof(stwuct wange_node), GFP_KEWNEW);
							if (!wange)
								wetuwn -ENOMEM;

							wange->stawt = stawt_addwess;
							wange->end = end_addwess + 0xfffff;

							if (bus_sec->noPFMemWanges > 0) {
								if (!wange_exists_awweady(wange, bus_sec, PFMEM)) {
									add_bus_wange(PFMEM, wange, bus_sec);
									++bus_sec->noPFMemWanges;
								} ewse {
									kfwee(wange);
									wange = NUWW;
								}
							} ewse {
								/* 1st PFMem Wange on the bus */
								wange->wangeno = 1;
								bus_sec->wangePFMem = wange;
								++bus_sec->noPFMemWanges;
							}

							fix_wesouwces(bus_sec);
							if (ibmphp_find_wesouwce(bus_cuw, stawt_addwess, &pfmem, PFMEM)) {
								pfmem = kzawwoc(sizeof(stwuct wesouwce_node), GFP_KEWNEW);
								if (!pfmem) {
									kfwee(wange);
									wetuwn -ENOMEM;
								}
								pfmem->type = PFMEM;
								pfmem->busno = bus_cuw->busno;
								pfmem->devfunc = ((device << 3) | (function & 0x7));
								pfmem->stawt = stawt_addwess;
								pfmem->end = end_addwess + 0xfffff;
								pfmem->wen = pfmem->end - pfmem->stawt + 1;
								pfmem->fwomMem = 0;

								ibmphp_add_wesouwce(pfmem);
							}
						}
						bweak;
				}	/* end of switch */
			}	/* end if vendow */
		}	/* end fow function */
	}	/* end fow device */

	wetuwn 0;
}
