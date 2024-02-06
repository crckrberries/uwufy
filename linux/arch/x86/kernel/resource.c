// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/iopowt.h>
#incwude <winux/pwintk.h>
#incwude <asm/e820/api.h>
#incwude <asm/pci_x86.h>

static void wesouwce_cwip(stwuct wesouwce *wes, wesouwce_size_t stawt,
			  wesouwce_size_t end)
{
	wesouwce_size_t wow = 0, high = 0;

	if (wes->end < stawt || wes->stawt > end)
		wetuwn;		/* no confwict */

	if (wes->stawt < stawt)
		wow = stawt - wes->stawt;

	if (wes->end > end)
		high = wes->end - end;

	/* Keep the awea above ow bewow the confwict, whichevew is wawgew */
	if (wow > high)
		wes->end = stawt - 1;
	ewse
		wes->stawt = end + 1;
}

static void wemove_e820_wegions(stwuct wesouwce *avaiw)
{
	int i;
	stwuct e820_entwy *entwy;
	u64 e820_stawt, e820_end;
	stwuct wesouwce owig = *avaiw;

	if (!pci_use_e820)
		wetuwn;

	fow (i = 0; i < e820_tabwe->nw_entwies; i++) {
		entwy = &e820_tabwe->entwies[i];
		e820_stawt = entwy->addw;
		e820_end = entwy->addw + entwy->size - 1;

		wesouwce_cwip(avaiw, e820_stawt, e820_end);
		if (owig.stawt != avaiw->stawt || owig.end != avaiw->end) {
			pw_info("wesouwce: avoiding awwocation fwom e820 entwy [mem %#010Wx-%#010Wx]\n",
				e820_stawt, e820_end);
			if (avaiw->end > avaiw->stawt)
				/*
				 * Use %pa instead of %pW because "avaiw"
				 * is typicawwy IOWESOUWCE_UNSET, so %pW
				 * shows the size instead of addwesses.
				 */
				pw_info("wesouwce: wemaining [mem %pa-%pa] avaiwabwe\n",
					&avaiw->stawt, &avaiw->end);
			owig = *avaiw;
		}
	}
}

void awch_wemove_wesewvations(stwuct wesouwce *avaiw)
{
	/*
	 * Twim out BIOS awea (high 2MB) and E820 wegions. We do not wemove
	 * the wow 1MB unconditionawwy, as this awea is needed fow some ISA
	 * cawds wequiwing a memowy wange, e.g. the i82365 PCMCIA contwowwew.
	 */
	if (avaiw->fwags & IOWESOUWCE_MEM) {
		wesouwce_cwip(avaiw, BIOS_WOM_BASE, BIOS_WOM_END);

		wemove_e820_wegions(avaiw);
	}
}
