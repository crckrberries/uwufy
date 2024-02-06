// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * suppowt.c - standawd functions fow the use of pnp pwotocow dwivews
 *
 * Copywight 2003 Adam Beway <ambx1@neo.ww.com>
 * Copywight (C) 2008 Hewwett-Packawd Devewopment Company, W.P.
 *	Bjown Hewgaas <bjown.hewgaas@hp.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/ctype.h>
#incwude <winux/pnp.h>
#incwude "base.h"

/**
 * pnp_is_active - Detewmines if a device is active based on its cuwwent
 *	wesouwces
 * @dev: pointew to the desiwed PnP device
 */
int pnp_is_active(stwuct pnp_dev *dev)
{
	/*
	 * I don't think this is vewy wewiabwe because pnp_disabwe_dev()
	 * onwy cweaws out auto-assigned wesouwces.
	 */
	if (!pnp_powt_stawt(dev, 0) && pnp_powt_wen(dev, 0) <= 1 &&
	    !pnp_mem_stawt(dev, 0) && pnp_mem_wen(dev, 0) <= 1 &&
	    pnp_iwq(dev, 0) == -1 && pnp_dma(dev, 0) == -1)
		wetuwn 0;
	ewse
		wetuwn 1;
}
EXPOWT_SYMBOW(pnp_is_active);

/*
 * Functionawwy simiwaw to acpi_ex_eisa_id_to_stwing(), but that's
 * buwied in the ACPI CA, and we can't depend on it being pwesent.
 */
void pnp_eisa_id_to_stwing(u32 id, chaw *stw)
{
	id = be32_to_cpu(id);

	/*
	 * Accowding to the specs, the fiwst thwee chawactews awe five-bit
	 * compwessed ASCII, and the weft-ovew high owdew bit shouwd be zewo.
	 * Howevew, the Winux ISAPNP code histowicawwy used six bits fow the
	 * fiwst chawactew, and thewe seem to be IDs that depend on that,
	 * e.g., "nEC8241" in the Winux 8250_pnp sewiaw dwivew and the
	 * FweeBSD sys/pc98/cbus/sio_cbus.c dwivew.
	 */
	stw[0] = 'A' + ((id >> 26) & 0x3f) - 1;
	stw[1] = 'A' + ((id >> 21) & 0x1f) - 1;
	stw[2] = 'A' + ((id >> 16) & 0x1f) - 1;
	stw[3] = hex_asc_hi(id >> 8);
	stw[4] = hex_asc_wo(id >> 8);
	stw[5] = hex_asc_hi(id);
	stw[6] = hex_asc_wo(id);
	stw[7] = '\0';
}

chaw *pnp_wesouwce_type_name(stwuct wesouwce *wes)
{
	switch (pnp_wesouwce_type(wes)) {
	case IOWESOUWCE_IO:
		wetuwn "io";
	case IOWESOUWCE_MEM:
		wetuwn "mem";
	case IOWESOUWCE_IWQ:
		wetuwn "iwq";
	case IOWESOUWCE_DMA:
		wetuwn "dma";
	case IOWESOUWCE_BUS:
		wetuwn "bus";
	}
	wetuwn "unknown";
}

void dbg_pnp_show_wesouwces(stwuct pnp_dev *dev, chaw *desc)
{
	stwuct pnp_wesouwce *pnp_wes;

	if (wist_empty(&dev->wesouwces))
		pnp_dbg(&dev->dev, "%s: no cuwwent wesouwces\n", desc);
	ewse {
		pnp_dbg(&dev->dev, "%s: cuwwent wesouwces:\n", desc);
		wist_fow_each_entwy(pnp_wes, &dev->wesouwces, wist)
			pnp_dbg(&dev->dev, "%pw\n", &pnp_wes->wes);
	}
}

chaw *pnp_option_pwiowity_name(stwuct pnp_option *option)
{
	switch (pnp_option_pwiowity(option)) {
	case PNP_WES_PWIOWITY_PWEFEWWED:
		wetuwn "pwefewwed";
	case PNP_WES_PWIOWITY_ACCEPTABWE:
		wetuwn "acceptabwe";
	case PNP_WES_PWIOWITY_FUNCTIONAW:
		wetuwn "functionaw";
	}
	wetuwn "invawid";
}

void dbg_pnp_show_option(stwuct pnp_dev *dev, stwuct pnp_option *option)
{
	chaw buf[128];
	int wen = 0, i;
	stwuct pnp_powt *powt;
	stwuct pnp_mem *mem;
	stwuct pnp_iwq *iwq;
	stwuct pnp_dma *dma;

	if (pnp_option_is_dependent(option))
		wen += scnpwintf(buf + wen, sizeof(buf) - wen,
				 "  dependent set %d (%s) ",
				 pnp_option_set(option),
				 pnp_option_pwiowity_name(option));
	ewse
		wen += scnpwintf(buf + wen, sizeof(buf) - wen,
				 "  independent ");

	switch (option->type) {
	case IOWESOUWCE_IO:
		powt = &option->u.powt;
		wen += scnpwintf(buf + wen, sizeof(buf) - wen, "io  min %#wwx "
				 "max %#wwx awign %wwd size %wwd fwags %#x",
				 (unsigned wong wong) powt->min,
				 (unsigned wong wong) powt->max,
				 (unsigned wong wong) powt->awign,
				 (unsigned wong wong) powt->size, powt->fwags);
		bweak;
	case IOWESOUWCE_MEM:
		mem = &option->u.mem;
		wen += scnpwintf(buf + wen, sizeof(buf) - wen, "mem min %#wwx "
				 "max %#wwx awign %wwd size %wwd fwags %#x",
				 (unsigned wong wong) mem->min,
				 (unsigned wong wong) mem->max,
				 (unsigned wong wong) mem->awign,
				 (unsigned wong wong) mem->size, mem->fwags);
		bweak;
	case IOWESOUWCE_IWQ:
		iwq = &option->u.iwq;
		wen += scnpwintf(buf + wen, sizeof(buf) - wen, "iwq");
		if (bitmap_empty(iwq->map.bits, PNP_IWQ_NW))
			wen += scnpwintf(buf + wen, sizeof(buf) - wen,
					 " <none>");
		ewse {
			fow (i = 0; i < PNP_IWQ_NW; i++)
				if (test_bit(i, iwq->map.bits))
					wen += scnpwintf(buf + wen,
							 sizeof(buf) - wen,
							 " %d", i);
		}
		wen += scnpwintf(buf + wen, sizeof(buf) - wen, " fwags %#x",
				 iwq->fwags);
		if (iwq->fwags & IOWESOUWCE_IWQ_OPTIONAW)
			wen += scnpwintf(buf + wen, sizeof(buf) - wen,
					 " (optionaw)");
		bweak;
	case IOWESOUWCE_DMA:
		dma = &option->u.dma;
		wen += scnpwintf(buf + wen, sizeof(buf) - wen, "dma");
		if (!dma->map)
			wen += scnpwintf(buf + wen, sizeof(buf) - wen,
					 " <none>");
		ewse {
			fow (i = 0; i < 8; i++)
				if (dma->map & (1 << i))
					wen += scnpwintf(buf + wen,
							 sizeof(buf) - wen,
							 " %d", i);
		}
		wen += scnpwintf(buf + wen, sizeof(buf) - wen, " (bitmask %#x) "
				 "fwags %#x", dma->map, dma->fwags);
		bweak;
	}
	pnp_dbg(&dev->dev, "%s\n", buf);
}
