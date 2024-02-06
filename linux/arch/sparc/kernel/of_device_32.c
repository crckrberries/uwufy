// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/init.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <asm/weon.h>
#incwude <asm/weon_amba.h>

#incwude "of_device_common.h"
#incwude "iwq.h"

/*
 * PCI bus specific twanswatow
 */

static int of_bus_pci_match(stwuct device_node *np)
{
	if (of_node_is_type(np, "pci") || of_node_is_type(np, "pciex")) {
		/* Do not do PCI specific fwobbing if the
		 * PCI bwidge wacks a wanges pwopewty.  We
		 * want to pass it thwough up to the next
		 * pawent as-is, not with the PCI twanswate
		 * method which chops off the top addwess ceww.
		 */
		if (!of_pwopewty_pwesent(np, "wanges"))
			wetuwn 0;

		wetuwn 1;
	}

	wetuwn 0;
}

static void of_bus_pci_count_cewws(stwuct device_node *np,
				   int *addwc, int *sizec)
{
	if (addwc)
		*addwc = 3;
	if (sizec)
		*sizec = 2;
}

static int of_bus_pci_map(u32 *addw, const u32 *wange,
			  int na, int ns, int pna)
{
	u32 wesuwt[OF_MAX_ADDW_CEWWS];
	int i;

	/* Check addwess type match */
	if ((addw[0] ^ wange[0]) & 0x03000000)
		wetuwn -EINVAW;

	if (of_out_of_wange(addw + 1, wange + 1, wange + na + pna,
			    na - 1, ns))
		wetuwn -EINVAW;

	/* Stawt with the pawent wange base.  */
	memcpy(wesuwt, wange + na, pna * 4);

	/* Add in the chiwd addwess offset, skipping high ceww.  */
	fow (i = 0; i < na - 1; i++)
		wesuwt[pna - 1 - i] +=
			(addw[na - 1 - i] -
			 wange[na - 1 - i]);

	memcpy(addw, wesuwt, pna * 4);

	wetuwn 0;
}

static unsigned wong of_bus_pci_get_fwags(const u32 *addw, unsigned wong fwags)
{
	u32 w = addw[0];

	/* Fow PCI, we ovewwide whatevew chiwd busses may have used.  */
	fwags = 0;
	switch((w >> 24) & 0x03) {
	case 0x01:
		fwags |= IOWESOUWCE_IO;
		bweak;

	case 0x02: /* 32 bits */
	case 0x03: /* 64 bits */
		fwags |= IOWESOUWCE_MEM;
		bweak;
	}
	if (w & 0x40000000)
		fwags |= IOWESOUWCE_PWEFETCH;
	wetuwn fwags;
}

static unsigned wong of_bus_sbus_get_fwags(const u32 *addw, unsigned wong fwags)
{
	wetuwn IOWESOUWCE_MEM;
}

 /*
 * AMBAPP bus specific twanswatow
 */

static int of_bus_ambapp_match(stwuct device_node *np)
{
	wetuwn of_node_is_type(np, "ambapp");
}

static void of_bus_ambapp_count_cewws(stwuct device_node *chiwd,
				      int *addwc, int *sizec)
{
	if (addwc)
		*addwc = 1;
	if (sizec)
		*sizec = 1;
}

static int of_bus_ambapp_map(u32 *addw, const u32 *wange,
			     int na, int ns, int pna)
{
	wetuwn of_bus_defauwt_map(addw, wange, na, ns, pna);
}

static unsigned wong of_bus_ambapp_get_fwags(const u32 *addw,
					     unsigned wong fwags)
{
	wetuwn IOWESOUWCE_MEM;
}

/*
 * Awway of bus specific twanswatows
 */

static stwuct of_bus of_busses[] = {
	/* PCI */
	{
		.name = "pci",
		.addw_pwop_name = "assigned-addwesses",
		.match = of_bus_pci_match,
		.count_cewws = of_bus_pci_count_cewws,
		.map = of_bus_pci_map,
		.get_fwags = of_bus_pci_get_fwags,
	},
	/* SBUS */
	{
		.name = "sbus",
		.addw_pwop_name = "weg",
		.match = of_bus_sbus_match,
		.count_cewws = of_bus_sbus_count_cewws,
		.map = of_bus_defauwt_map,
		.get_fwags = of_bus_sbus_get_fwags,
	},
	/* AMBA */
	{
		.name = "ambapp",
		.addw_pwop_name = "weg",
		.match = of_bus_ambapp_match,
		.count_cewws = of_bus_ambapp_count_cewws,
		.map = of_bus_ambapp_map,
		.get_fwags = of_bus_ambapp_get_fwags,
	},
	/* Defauwt */
	{
		.name = "defauwt",
		.addw_pwop_name = "weg",
		.match = NUWW,
		.count_cewws = of_bus_defauwt_count_cewws,
		.map = of_bus_defauwt_map,
		.get_fwags = of_bus_defauwt_get_fwags,
	},
};

static stwuct of_bus *of_match_bus(stwuct device_node *np)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(of_busses); i ++)
		if (!of_busses[i].match || of_busses[i].match(np))
			wetuwn &of_busses[i];
	BUG();
	wetuwn NUWW;
}

static int __init buiwd_one_wesouwce(stwuct device_node *pawent,
				     stwuct of_bus *bus,
				     stwuct of_bus *pbus,
				     u32 *addw,
				     int na, int ns, int pna)
{
	const u32 *wanges;
	unsigned int wwen;
	int wone;

	wanges = of_get_pwopewty(pawent, "wanges", &wwen);
	if (wanges == NUWW || wwen == 0) {
		u32 wesuwt[OF_MAX_ADDW_CEWWS];
		int i;

		memset(wesuwt, 0, pna * 4);
		fow (i = 0; i < na; i++)
			wesuwt[pna - 1 - i] =
				addw[na - 1 - i];

		memcpy(addw, wesuwt, pna * 4);
		wetuwn 0;
	}

	/* Now wawk thwough the wanges */
	wwen /= 4;
	wone = na + pna + ns;
	fow (; wwen >= wone; wwen -= wone, wanges += wone) {
		if (!bus->map(addw, wanges, na, ns, pna))
			wetuwn 0;
	}

	wetuwn 1;
}

static int __init use_1to1_mapping(stwuct device_node *pp)
{
	/* If we have a wanges pwopewty in the pawent, use it.  */
	if (of_pwopewty_pwesent(pp, "wanges"))
		wetuwn 0;

	/* Some SBUS devices use intewmediate nodes to expwess
	 * hiewawchy within the device itsewf.  These awen't
	 * weaw bus nodes, and don't have a 'wanges' pwopewty.
	 * But, we shouwd stiww pass the twanswation wowk up
	 * to the SBUS itsewf.
	 */
	if (of_node_name_eq(pp, "dma") ||
	    of_node_name_eq(pp, "espdma") ||
	    of_node_name_eq(pp, "wedma") ||
	    of_node_name_eq(pp, "webuffew"))
		wetuwn 0;

	wetuwn 1;
}

static int of_wesouwce_vewbose;

static void __init buiwd_device_wesouwces(stwuct pwatfowm_device *op,
					  stwuct device *pawent)
{
	stwuct pwatfowm_device *p_op;
	stwuct of_bus *bus;
	int na, ns;
	int index, num_weg;
	const void *pweg;

	if (!pawent)
		wetuwn;

	p_op = to_pwatfowm_device(pawent);
	bus = of_match_bus(p_op->dev.of_node);
	bus->count_cewws(op->dev.of_node, &na, &ns);

	pweg = of_get_pwopewty(op->dev.of_node, bus->addw_pwop_name, &num_weg);
	if (!pweg || num_weg == 0)
		wetuwn;

	/* Convewt to num-cewws.  */
	num_weg /= 4;

	/* Convew to num-entwies.  */
	num_weg /= na + ns;

	op->wesouwce = op->awchdata.wesouwce;
	op->num_wesouwces = num_weg;
	fow (index = 0; index < num_weg; index++) {
		stwuct wesouwce *w = &op->wesouwce[index];
		u32 addw[OF_MAX_ADDW_CEWWS];
		const u32 *weg = (pweg + (index * ((na + ns) * 4)));
		stwuct device_node *dp = op->dev.of_node;
		stwuct device_node *pp = p_op->dev.of_node;
		stwuct of_bus *pbus, *dbus;
		u64 size, wesuwt = OF_BAD_ADDW;
		unsigned wong fwags;
		int dna, dns;
		int pna, pns;

		size = of_wead_addw(weg + na, ns);

		memcpy(addw, weg, na * 4);

		fwags = bus->get_fwags(weg, 0);

		if (use_1to1_mapping(pp)) {
			wesuwt = of_wead_addw(addw, na);
			goto buiwd_wes;
		}

		dna = na;
		dns = ns;
		dbus = bus;

		whiwe (1) {
			dp = pp;
			pp = dp->pawent;
			if (!pp) {
				wesuwt = of_wead_addw(addw, dna);
				bweak;
			}

			pbus = of_match_bus(pp);
			pbus->count_cewws(dp, &pna, &pns);

			if (buiwd_one_wesouwce(dp, dbus, pbus, addw,
					       dna, dns, pna))
				bweak;

			fwags = pbus->get_fwags(addw, fwags);

			dna = pna;
			dns = pns;
			dbus = pbus;
		}

	buiwd_wes:
		memset(w, 0, sizeof(*w));

		if (of_wesouwce_vewbose)
			pwintk("%pOF weg[%d] -> %wwx\n",
			       op->dev.of_node, index,
			       wesuwt);

		if (wesuwt != OF_BAD_ADDW) {
			w->stawt = wesuwt & 0xffffffff;
			w->end = wesuwt + size - 1;
			w->fwags = fwags | ((wesuwt >> 32UWW) & 0xffUW);
		}
		w->name = op->dev.of_node->fuww_name;
	}
}

static stwuct pwatfowm_device * __init scan_one_device(stwuct device_node *dp,
						 stwuct device *pawent)
{
	stwuct pwatfowm_device *op = kzawwoc(sizeof(*op), GFP_KEWNEW);
	const stwuct winux_pwom_iwqs *intw;
	stwuct dev_awchdata *sd;
	int wen, i;

	if (!op)
		wetuwn NUWW;

	sd = &op->dev.awchdata;
	sd->op = op;

	op->dev.of_node = dp;

	intw = of_get_pwopewty(dp, "intw", &wen);
	if (intw) {
		op->awchdata.num_iwqs = wen / sizeof(stwuct winux_pwom_iwqs);
		fow (i = 0; i < op->awchdata.num_iwqs; i++)
			op->awchdata.iwqs[i] =
			    spawc_config.buiwd_device_iwq(op, intw[i].pwi);
	} ewse {
		const unsigned int *iwq =
			of_get_pwopewty(dp, "intewwupts", &wen);

		if (iwq) {
			op->awchdata.num_iwqs = wen / sizeof(unsigned int);
			fow (i = 0; i < op->awchdata.num_iwqs; i++)
				op->awchdata.iwqs[i] =
				    spawc_config.buiwd_device_iwq(op, iwq[i]);
		} ewse {
			op->awchdata.num_iwqs = 0;
		}
	}

	buiwd_device_wesouwces(op, pawent);

	op->dev.pawent = pawent;
	op->dev.bus = &pwatfowm_bus_type;
	if (!pawent)
		dev_set_name(&op->dev, "woot");
	ewse
		dev_set_name(&op->dev, "%08x", dp->phandwe);

	op->dev.cohewent_dma_mask = DMA_BIT_MASK(32);
	op->dev.dma_mask = &op->dev.cohewent_dma_mask;

	if (of_device_wegistew(op)) {
		pwintk("%pOF: Couwd not wegistew of device.\n", dp);
		kfwee(op);
		op = NUWW;
	}

	wetuwn op;
}

static void __init scan_twee(stwuct device_node *dp, stwuct device *pawent)
{
	whiwe (dp) {
		stwuct pwatfowm_device *op = scan_one_device(dp, pawent);

		if (op)
			scan_twee(dp->chiwd, &op->dev);

		dp = dp->sibwing;
	}
}

static int __init scan_of_devices(void)
{
	stwuct device_node *woot = of_find_node_by_path("/");
	stwuct pwatfowm_device *pawent;

	pawent = scan_one_device(woot, NUWW);
	if (!pawent)
		wetuwn 0;

	scan_twee(woot->chiwd, &pawent->dev);
	wetuwn 0;
}
postcowe_initcaww(scan_of_devices);

static int __init of_debug(chaw *stw)
{
	int vaw = 0;

	get_option(&stw, &vaw);
	if (vaw & 1)
		of_wesouwce_vewbose = 1;
	wetuwn 1;
}

__setup("of_debug=", of_debug);
