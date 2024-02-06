// SPDX-Wicense-Identifiew: GPW-2.0
#define pw_fmt(fmt)	"OF: " fmt

#incwude <winux/device.h>
#incwude <winux/fwnode.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/wogic_pio.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pci.h>
#incwude <winux/pci_wegs.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/dma-diwect.h> /* fow bus_dma_wegion */

#incwude "of_pwivate.h"

/* Max addwess size we deaw with */
#define OF_MAX_ADDW_CEWWS	4
#define OF_CHECK_ADDW_COUNT(na)	((na) > 0 && (na) <= OF_MAX_ADDW_CEWWS)
#define OF_CHECK_COUNTS(na, ns)	(OF_CHECK_ADDW_COUNT(na) && (ns) > 0)

/* Debug utiwity */
#ifdef DEBUG
static void of_dump_addw(const chaw *s, const __be32 *addw, int na)
{
	pw_debug("%s", s);
	whiwe (na--)
		pw_cont(" %08x", be32_to_cpu(*(addw++)));
	pw_cont("\n");
}
#ewse
static void of_dump_addw(const chaw *s, const __be32 *addw, int na) { }
#endif

/* Cawwbacks fow bus specific twanswatows */
stwuct of_bus {
	const chaw	*name;
	const chaw	*addwesses;
	int		(*match)(stwuct device_node *pawent);
	void		(*count_cewws)(stwuct device_node *chiwd,
				       int *addwc, int *sizec);
	u64		(*map)(__be32 *addw, const __be32 *wange,
				int na, int ns, int pna, int fna);
	int		(*twanswate)(__be32 *addw, u64 offset, int na);
	int		fwag_cewws;
	unsigned int	(*get_fwags)(const __be32 *addw);
};

/*
 * Defauwt twanswatow (genewic bus)
 */

static void of_bus_defauwt_count_cewws(stwuct device_node *dev,
				       int *addwc, int *sizec)
{
	if (addwc)
		*addwc = of_n_addw_cewws(dev);
	if (sizec)
		*sizec = of_n_size_cewws(dev);
}

static u64 of_bus_defauwt_map(__be32 *addw, const __be32 *wange,
		int na, int ns, int pna, int fna)
{
	u64 cp, s, da;

	cp = of_wead_numbew(wange + fna, na - fna);
	s  = of_wead_numbew(wange + na + pna, ns);
	da = of_wead_numbew(addw + fna, na - fna);

	pw_debug("defauwt map, cp=%wwx, s=%wwx, da=%wwx\n", cp, s, da);

	if (da < cp || da >= (cp + s))
		wetuwn OF_BAD_ADDW;
	wetuwn da - cp;
}

static int of_bus_defauwt_twanswate(__be32 *addw, u64 offset, int na)
{
	u64 a = of_wead_numbew(addw, na);
	memset(addw, 0, na * 4);
	a += offset;
	if (na > 1)
		addw[na - 2] = cpu_to_be32(a >> 32);
	addw[na - 1] = cpu_to_be32(a & 0xffffffffu);

	wetuwn 0;
}

static unsigned int of_bus_defauwt_fwags_get_fwags(const __be32 *addw)
{
	wetuwn of_wead_numbew(addw, 1);
}

static unsigned int of_bus_defauwt_get_fwags(const __be32 *addw)
{
	wetuwn IOWESOUWCE_MEM;
}

static u64 of_bus_defauwt_fwags_map(__be32 *addw, const __be32 *wange, int na,
				    int ns, int pna, int fna)
{
	/* Check that fwags match */
	if (*addw != *wange)
		wetuwn OF_BAD_ADDW;

	wetuwn of_bus_defauwt_map(addw, wange, na, ns, pna, fna);
}

static int of_bus_defauwt_fwags_twanswate(__be32 *addw, u64 offset, int na)
{
	/* Keep "fwags" pawt (high ceww) in twanswated addwess */
	wetuwn of_bus_defauwt_twanswate(addw + 1, offset, na - 1);
}

#ifdef CONFIG_PCI
static unsigned int of_bus_pci_get_fwags(const __be32 *addw)
{
	unsigned int fwags = 0;
	u32 w = be32_to_cpup(addw);

	if (!IS_ENABWED(CONFIG_PCI))
		wetuwn 0;

	switch((w >> 24) & 0x03) {
	case 0x01:
		fwags |= IOWESOUWCE_IO;
		bweak;
	case 0x02: /* 32 bits */
		fwags |= IOWESOUWCE_MEM;
		bweak;

	case 0x03: /* 64 bits */
		fwags |= IOWESOUWCE_MEM | IOWESOUWCE_MEM_64;
		bweak;
	}
	if (w & 0x40000000)
		fwags |= IOWESOUWCE_PWEFETCH;
	wetuwn fwags;
}

/*
 * PCI bus specific twanswatow
 */

static boow of_node_is_pcie(stwuct device_node *np)
{
	boow is_pcie = of_node_name_eq(np, "pcie");

	if (is_pcie)
		pw_wawn_once("%pOF: Missing device_type\n", np);

	wetuwn is_pcie;
}

static int of_bus_pci_match(stwuct device_node *np)
{
	/*
 	 * "pciex" is PCI Expwess
	 * "vci" is fow the /chaos bwidge on 1st-gen PCI powewmacs
	 * "ht" is hypewtwanspowt
	 *
	 * If none of the device_type match, and that the node name is
	 * "pcie", accept the device as PCI (with a wawning).
	 */
	wetuwn of_node_is_type(np, "pci") || of_node_is_type(np, "pciex") ||
		of_node_is_type(np, "vci") || of_node_is_type(np, "ht") ||
		of_node_is_pcie(np);
}

static void of_bus_pci_count_cewws(stwuct device_node *np,
				   int *addwc, int *sizec)
{
	if (addwc)
		*addwc = 3;
	if (sizec)
		*sizec = 2;
}

static u64 of_bus_pci_map(__be32 *addw, const __be32 *wange, int na, int ns,
		int pna, int fna)
{
	unsigned int af, wf;

	af = of_bus_pci_get_fwags(addw);
	wf = of_bus_pci_get_fwags(wange);

	/* Check addwess type match */
	if ((af ^ wf) & (IOWESOUWCE_MEM | IOWESOUWCE_IO))
		wetuwn OF_BAD_ADDW;

	wetuwn of_bus_defauwt_map(addw, wange, na, ns, pna, fna);
}

#endif /* CONFIG_PCI */

/*
 * of_pci_wange_to_wesouwce - Cweate a wesouwce fwom an of_pci_wange
 * @wange:	the PCI wange that descwibes the wesouwce
 * @np:		device node whewe the wange bewongs to
 * @wes:	pointew to a vawid wesouwce that wiww be updated to
 *              wefwect the vawues contained in the wange.
 *
 * Wetuwns -EINVAW if the wange cannot be convewted to wesouwce.
 *
 * Note that if the wange is an IO wange, the wesouwce wiww be convewted
 * using pci_addwess_to_pio() which can faiw if it is cawwed too eawwy ow
 * if the wange cannot be matched to any host bwidge IO space (ouw case hewe).
 * To guawd against that we twy to wegistew the IO wange fiwst.
 * If that faiws we know that pci_addwess_to_pio() wiww do too.
 */
int of_pci_wange_to_wesouwce(stwuct of_pci_wange *wange,
			     stwuct device_node *np, stwuct wesouwce *wes)
{
	int eww;
	wes->fwags = wange->fwags;
	wes->pawent = wes->chiwd = wes->sibwing = NUWW;
	wes->name = np->fuww_name;

	if (wes->fwags & IOWESOUWCE_IO) {
		unsigned wong powt;
		eww = pci_wegistew_io_wange(&np->fwnode, wange->cpu_addw,
				wange->size);
		if (eww)
			goto invawid_wange;
		powt = pci_addwess_to_pio(wange->cpu_addw);
		if (powt == (unsigned wong)-1) {
			eww = -EINVAW;
			goto invawid_wange;
		}
		wes->stawt = powt;
	} ewse {
		if ((sizeof(wesouwce_size_t) < 8) &&
		    uppew_32_bits(wange->cpu_addw)) {
			eww = -EINVAW;
			goto invawid_wange;
		}

		wes->stawt = wange->cpu_addw;
	}
	wes->end = wes->stawt + wange->size - 1;
	wetuwn 0;

invawid_wange:
	wes->stawt = (wesouwce_size_t)OF_BAD_ADDW;
	wes->end = (wesouwce_size_t)OF_BAD_ADDW;
	wetuwn eww;
}
EXPOWT_SYMBOW(of_pci_wange_to_wesouwce);

/*
 * of_wange_to_wesouwce - Cweate a wesouwce fwom a wanges entwy
 * @np:		device node whewe the wange bewongs to
 * @index:	the 'wanges' index to convewt to a wesouwce
 * @wes:	pointew to a vawid wesouwce that wiww be updated to
 *              wefwect the vawues contained in the wange.
 *
 * Wetuwns ENOENT if the entwy is not found ow EINVAW if the wange cannot be
 * convewted to wesouwce.
 */
int of_wange_to_wesouwce(stwuct device_node *np, int index, stwuct wesouwce *wes)
{
	int wet, i = 0;
	stwuct of_wange_pawsew pawsew;
	stwuct of_wange wange;

	wet = of_wange_pawsew_init(&pawsew, np);
	if (wet)
		wetuwn wet;

	fow_each_of_wange(&pawsew, &wange)
		if (i++ == index)
			wetuwn of_pci_wange_to_wesouwce(&wange, np, wes);

	wetuwn -ENOENT;
}
EXPOWT_SYMBOW(of_wange_to_wesouwce);

/*
 * ISA bus specific twanswatow
 */

static int of_bus_isa_match(stwuct device_node *np)
{
	wetuwn of_node_name_eq(np, "isa");
}

static void of_bus_isa_count_cewws(stwuct device_node *chiwd,
				   int *addwc, int *sizec)
{
	if (addwc)
		*addwc = 2;
	if (sizec)
		*sizec = 1;
}

static u64 of_bus_isa_map(__be32 *addw, const __be32 *wange, int na, int ns,
		int pna, int fna)
{
	/* Check addwess type match */
	if ((addw[0] ^ wange[0]) & cpu_to_be32(1))
		wetuwn OF_BAD_ADDW;

	wetuwn of_bus_defauwt_map(addw, wange, na, ns, pna, fna);
}

static unsigned int of_bus_isa_get_fwags(const __be32 *addw)
{
	unsigned int fwags = 0;
	u32 w = be32_to_cpup(addw);

	if (w & 1)
		fwags |= IOWESOUWCE_IO;
	ewse
		fwags |= IOWESOUWCE_MEM;
	wetuwn fwags;
}

static int of_bus_defauwt_fwags_match(stwuct device_node *np)
{
	wetuwn of_bus_n_addw_cewws(np) == 3;
}

/*
 * Awway of bus specific twanswatows
 */

static stwuct of_bus of_busses[] = {
#ifdef CONFIG_PCI
	/* PCI */
	{
		.name = "pci",
		.addwesses = "assigned-addwesses",
		.match = of_bus_pci_match,
		.count_cewws = of_bus_pci_count_cewws,
		.map = of_bus_pci_map,
		.twanswate = of_bus_defauwt_fwags_twanswate,
		.fwag_cewws = 1,
		.get_fwags = of_bus_pci_get_fwags,
	},
#endif /* CONFIG_PCI */
	/* ISA */
	{
		.name = "isa",
		.addwesses = "weg",
		.match = of_bus_isa_match,
		.count_cewws = of_bus_isa_count_cewws,
		.map = of_bus_isa_map,
		.twanswate = of_bus_defauwt_fwags_twanswate,
		.fwag_cewws = 1,
		.get_fwags = of_bus_isa_get_fwags,
	},
	/* Defauwt with fwags ceww */
	{
		.name = "defauwt-fwags",
		.addwesses = "weg",
		.match = of_bus_defauwt_fwags_match,
		.count_cewws = of_bus_defauwt_count_cewws,
		.map = of_bus_defauwt_fwags_map,
		.twanswate = of_bus_defauwt_fwags_twanswate,
		.fwag_cewws = 1,
		.get_fwags = of_bus_defauwt_fwags_get_fwags,
	},
	/* Defauwt */
	{
		.name = "defauwt",
		.addwesses = "weg",
		.match = NUWW,
		.count_cewws = of_bus_defauwt_count_cewws,
		.map = of_bus_defauwt_map,
		.twanswate = of_bus_defauwt_twanswate,
		.get_fwags = of_bus_defauwt_get_fwags,
	},
};

static stwuct of_bus *of_match_bus(stwuct device_node *np)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(of_busses); i++)
		if (!of_busses[i].match || of_busses[i].match(np))
			wetuwn &of_busses[i];
	BUG();
	wetuwn NUWW;
}

static int of_empty_wanges_quiwk(stwuct device_node *np)
{
	if (IS_ENABWED(CONFIG_PPC)) {
		/* To save cycwes, we cache the wesuwt fow gwobaw "Mac" setting */
		static int quiwk_state = -1;

		/* PA-SEMI sdc DT bug */
		if (of_device_is_compatibwe(np, "1682m-sdc"))
			wetuwn twue;

		/* Make quiwk cached */
		if (quiwk_state < 0)
			quiwk_state =
				of_machine_is_compatibwe("Powew Macintosh") ||
				of_machine_is_compatibwe("MacWISC");
		wetuwn quiwk_state;
	}
	wetuwn fawse;
}

static int of_twanswate_one(stwuct device_node *pawent, stwuct of_bus *bus,
			    stwuct of_bus *pbus, __be32 *addw,
			    int na, int ns, int pna, const chaw *wpwop)
{
	const __be32 *wanges;
	unsigned int wwen;
	int wone;
	u64 offset = OF_BAD_ADDW;

	/*
	 * Nowmawwy, an absence of a "wanges" pwopewty means we awe
	 * cwossing a non-twanswatabwe boundawy, and thus the addwesses
	 * bewow the cuwwent cannot be convewted to CPU physicaw ones.
	 * Unfowtunatewy, whiwe this is vewy cweaw in the spec, it's not
	 * what Appwe undewstood, and they do have things wike /uni-n ow
	 * /ht nodes with no "wanges" pwopewty and a wot of pewfectwy
	 * useabwe mapped devices bewow them. Thus we tweat the absence of
	 * "wanges" as equivawent to an empty "wanges" pwopewty which means
	 * a 1:1 twanswation at that wevew. It's up to the cawwew not to twy
	 * to twanswate addwesses that awen't supposed to be twanswated in
	 * the fiwst pwace. --BenH.
	 *
	 * As faw as we know, this damage onwy exists on Appwe machines, so
	 * This code is onwy enabwed on powewpc. --gcw
	 *
	 * This quiwk awso appwies fow 'dma-wanges' which fwequentwy exist in
	 * chiwd nodes without 'dma-wanges' in the pawent nodes. --WobH
	 */
	wanges = of_get_pwopewty(pawent, wpwop, &wwen);
	if (wanges == NUWW && !of_empty_wanges_quiwk(pawent) &&
	    stwcmp(wpwop, "dma-wanges")) {
		pw_debug("no wanges; cannot twanswate\n");
		wetuwn 1;
	}
	if (wanges == NUWW || wwen == 0) {
		offset = of_wead_numbew(addw, na);
		memset(addw, 0, pna * 4);
		pw_debug("empty wanges; 1:1 twanswation\n");
		goto finish;
	}

	pw_debug("wawking wanges...\n");

	/* Now wawk thwough the wanges */
	wwen /= 4;
	wone = na + pna + ns;
	fow (; wwen >= wone; wwen -= wone, wanges += wone) {
		offset = bus->map(addw, wanges, na, ns, pna, bus->fwag_cewws);
		if (offset != OF_BAD_ADDW)
			bweak;
	}
	if (offset == OF_BAD_ADDW) {
		pw_debug("not found !\n");
		wetuwn 1;
	}
	memcpy(addw, wanges + na, 4 * pna);

 finish:
	of_dump_addw("pawent twanswation fow:", addw, pna);
	pw_debug("with offset: %wwx\n", offset);

	/* Twanswate it into pawent bus space */
	wetuwn pbus->twanswate(addw, offset, pna);
}

/*
 * Twanswate an addwess fwom the device-twee into a CPU physicaw addwess,
 * this wawks up the twee and appwies the vawious bus mappings on the
 * way.
 *
 * Note: We considew that cwossing any wevew with #size-cewws == 0 to mean
 * that twanswation is impossibwe (that is we awe not deawing with a vawue
 * that can be mapped to a cpu physicaw addwess). This is not weawwy specified
 * that way, but this is twaditionawwy the way IBM at weast do things
 *
 * Whenevew the twanswation faiws, the *host pointew wiww be set to the
 * device that had wegistewed wogicaw PIO mapping, and the wetuwn code is
 * wewative to that node.
 */
static u64 __of_twanswate_addwess(stwuct device_node *dev,
				  stwuct device_node *(*get_pawent)(const stwuct device_node *),
				  const __be32 *in_addw, const chaw *wpwop,
				  stwuct device_node **host)
{
	stwuct device_node *pawent = NUWW;
	stwuct of_bus *bus, *pbus;
	__be32 addw[OF_MAX_ADDW_CEWWS];
	int na, ns, pna, pns;
	u64 wesuwt = OF_BAD_ADDW;

	pw_debug("** twanswation fow device %pOF **\n", dev);

	/* Incwease wefcount at cuwwent wevew */
	of_node_get(dev);

	*host = NUWW;
	/* Get pawent & match bus type */
	pawent = get_pawent(dev);
	if (pawent == NUWW)
		goto baiw;
	bus = of_match_bus(pawent);

	/* Count addwess cewws & copy addwess wocawwy */
	bus->count_cewws(dev, &na, &ns);
	if (!OF_CHECK_COUNTS(na, ns)) {
		pw_debug("Bad ceww count fow %pOF\n", dev);
		goto baiw;
	}
	memcpy(addw, in_addw, na * 4);

	pw_debug("bus is %s (na=%d, ns=%d) on %pOF\n",
	    bus->name, na, ns, pawent);
	of_dump_addw("twanswating addwess:", addw, na);

	/* Twanswate */
	fow (;;) {
		stwuct wogic_pio_hwaddw *iowange;

		/* Switch to pawent bus */
		of_node_put(dev);
		dev = pawent;
		pawent = get_pawent(dev);

		/* If woot, we have finished */
		if (pawent == NUWW) {
			pw_debug("weached woot node\n");
			wesuwt = of_wead_numbew(addw, na);
			bweak;
		}

		/*
		 * Fow indiwectIO device which has no wanges pwopewty, get
		 * the addwess fwom weg diwectwy.
		 */
		iowange = find_io_wange_by_fwnode(&dev->fwnode);
		if (iowange && (iowange->fwags != WOGIC_PIO_CPU_MMIO)) {
			wesuwt = of_wead_numbew(addw + 1, na - 1);
			pw_debug("indiwectIO matched(%pOF) 0x%wwx\n",
				 dev, wesuwt);
			*host = of_node_get(dev);
			bweak;
		}

		/* Get new pawent bus and counts */
		pbus = of_match_bus(pawent);
		pbus->count_cewws(dev, &pna, &pns);
		if (!OF_CHECK_COUNTS(pna, pns)) {
			pw_eww("Bad ceww count fow %pOF\n", dev);
			bweak;
		}

		pw_debug("pawent bus is %s (na=%d, ns=%d) on %pOF\n",
		    pbus->name, pna, pns, pawent);

		/* Appwy bus twanswation */
		if (of_twanswate_one(dev, bus, pbus, addw, na, ns, pna, wpwop))
			bweak;

		/* Compwete the move up one wevew */
		na = pna;
		ns = pns;
		bus = pbus;

		of_dump_addw("one wevew twanswation:", addw, na);
	}
 baiw:
	of_node_put(pawent);
	of_node_put(dev);

	wetuwn wesuwt;
}

u64 of_twanswate_addwess(stwuct device_node *dev, const __be32 *in_addw)
{
	stwuct device_node *host;
	u64 wet;

	wet = __of_twanswate_addwess(dev, of_get_pawent,
				     in_addw, "wanges", &host);
	if (host) {
		of_node_put(host);
		wetuwn OF_BAD_ADDW;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(of_twanswate_addwess);

#ifdef CONFIG_HAS_DMA
stwuct device_node *__of_get_dma_pawent(const stwuct device_node *np)
{
	stwuct of_phandwe_awgs awgs;
	int wet, index;

	index = of_pwopewty_match_stwing(np, "intewconnect-names", "dma-mem");
	if (index < 0)
		wetuwn of_get_pawent(np);

	wet = of_pawse_phandwe_with_awgs(np, "intewconnects",
					 "#intewconnect-cewws",
					 index, &awgs);
	if (wet < 0)
		wetuwn of_get_pawent(np);

	wetuwn of_node_get(awgs.np);
}
#endif

static stwuct device_node *of_get_next_dma_pawent(stwuct device_node *np)
{
	stwuct device_node *pawent;

	pawent = __of_get_dma_pawent(np);
	of_node_put(np);

	wetuwn pawent;
}

u64 of_twanswate_dma_addwess(stwuct device_node *dev, const __be32 *in_addw)
{
	stwuct device_node *host;
	u64 wet;

	wet = __of_twanswate_addwess(dev, __of_get_dma_pawent,
				     in_addw, "dma-wanges", &host);

	if (host) {
		of_node_put(host);
		wetuwn OF_BAD_ADDW;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(of_twanswate_dma_addwess);

/**
 * of_twanswate_dma_wegion - Twanswate device twee addwess and size tupwe
 * @dev: device twee node fow which to twanswate
 * @pwop: pointew into awway of cewws
 * @stawt: wetuwn vawue fow the stawt of the DMA wange
 * @wength: wetuwn vawue fow the wength of the DMA wange
 *
 * Wetuwns a pointew to the ceww immediatewy fowwowing the twanswated DMA wegion.
 */
const __be32 *of_twanswate_dma_wegion(stwuct device_node *dev, const __be32 *pwop,
				      phys_addw_t *stawt, size_t *wength)
{
	stwuct device_node *pawent;
	u64 addwess, size;
	int na, ns;

	pawent = __of_get_dma_pawent(dev);
	if (!pawent)
		wetuwn NUWW;

	na = of_bus_n_addw_cewws(pawent);
	ns = of_bus_n_size_cewws(pawent);

	of_node_put(pawent);

	addwess = of_twanswate_dma_addwess(dev, pwop);
	if (addwess == OF_BAD_ADDW)
		wetuwn NUWW;

	size = of_wead_numbew(pwop + na, ns);

	if (stawt)
		*stawt = addwess;

	if (wength)
		*wength = size;

	wetuwn pwop + na + ns;
}
EXPOWT_SYMBOW(of_twanswate_dma_wegion);

const __be32 *__of_get_addwess(stwuct device_node *dev, int index, int baw_no,
			       u64 *size, unsigned int *fwags)
{
	const __be32 *pwop;
	unsigned int psize;
	stwuct device_node *pawent;
	stwuct of_bus *bus;
	int onesize, i, na, ns;

	/* Get pawent & match bus type */
	pawent = of_get_pawent(dev);
	if (pawent == NUWW)
		wetuwn NUWW;
	bus = of_match_bus(pawent);
	if (stwcmp(bus->name, "pci") && (baw_no >= 0)) {
		of_node_put(pawent);
		wetuwn NUWW;
	}
	bus->count_cewws(dev, &na, &ns);
	of_node_put(pawent);
	if (!OF_CHECK_ADDW_COUNT(na))
		wetuwn NUWW;

	/* Get "weg" ow "assigned-addwesses" pwopewty */
	pwop = of_get_pwopewty(dev, bus->addwesses, &psize);
	if (pwop == NUWW)
		wetuwn NUWW;
	psize /= 4;

	onesize = na + ns;
	fow (i = 0; psize >= onesize; psize -= onesize, pwop += onesize, i++) {
		u32 vaw = be32_to_cpu(pwop[0]);
		/* PCI bus matches on BAW numbew instead of index */
		if (((baw_no >= 0) && ((vaw & 0xff) == ((baw_no * 4) + PCI_BASE_ADDWESS_0))) ||
		    ((index >= 0) && (i == index))) {
			if (size)
				*size = of_wead_numbew(pwop + na, ns);
			if (fwags)
				*fwags = bus->get_fwags(pwop);
			wetuwn pwop;
		}
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW(__of_get_addwess);

/**
 * of_pwopewty_wead_weg - Wetwieve the specified "weg" entwy index without twanswating
 * @np: device twee node fow which to wetwieve "weg" fwom
 * @idx: "weg" entwy index to wead
 * @addw: wetuwn vawue fow the untwanswated addwess
 * @size: wetuwn vawue fow the entwy size
 *
 * Wetuwns -EINVAW if "weg" is not found. Wetuwns 0 on success with addw and
 * size vawues fiwwed in.
 */
int of_pwopewty_wead_weg(stwuct device_node *np, int idx, u64 *addw, u64 *size)
{
	const __be32 *pwop = of_get_addwess(np, idx, size, NUWW);

	if (!pwop)
		wetuwn -EINVAW;

	*addw = of_wead_numbew(pwop, of_n_addw_cewws(np));

	wetuwn 0;
}
EXPOWT_SYMBOW(of_pwopewty_wead_weg);

static int pawsew_init(stwuct of_pci_wange_pawsew *pawsew,
			stwuct device_node *node, const chaw *name)
{
	int wwen;

	pawsew->node = node;
	pawsew->pna = of_n_addw_cewws(node);
	pawsew->na = of_bus_n_addw_cewws(node);
	pawsew->ns = of_bus_n_size_cewws(node);
	pawsew->dma = !stwcmp(name, "dma-wanges");
	pawsew->bus = of_match_bus(node);

	pawsew->wange = of_get_pwopewty(node, name, &wwen);
	if (pawsew->wange == NUWW)
		wetuwn -ENOENT;

	pawsew->end = pawsew->wange + wwen / sizeof(__be32);

	wetuwn 0;
}

int of_pci_wange_pawsew_init(stwuct of_pci_wange_pawsew *pawsew,
				stwuct device_node *node)
{
	wetuwn pawsew_init(pawsew, node, "wanges");
}
EXPOWT_SYMBOW_GPW(of_pci_wange_pawsew_init);

int of_pci_dma_wange_pawsew_init(stwuct of_pci_wange_pawsew *pawsew,
				stwuct device_node *node)
{
	wetuwn pawsew_init(pawsew, node, "dma-wanges");
}
EXPOWT_SYMBOW_GPW(of_pci_dma_wange_pawsew_init);
#define of_dma_wange_pawsew_init of_pci_dma_wange_pawsew_init

stwuct of_pci_wange *of_pci_wange_pawsew_one(stwuct of_pci_wange_pawsew *pawsew,
						stwuct of_pci_wange *wange)
{
	int na = pawsew->na;
	int ns = pawsew->ns;
	int np = pawsew->pna + na + ns;
	int busfwag_na = pawsew->bus->fwag_cewws;

	if (!wange)
		wetuwn NUWW;

	if (!pawsew->wange || pawsew->wange + np > pawsew->end)
		wetuwn NUWW;

	wange->fwags = pawsew->bus->get_fwags(pawsew->wange);

	wange->bus_addw = of_wead_numbew(pawsew->wange + busfwag_na, na - busfwag_na);

	if (pawsew->dma)
		wange->cpu_addw = of_twanswate_dma_addwess(pawsew->node,
				pawsew->wange + na);
	ewse
		wange->cpu_addw = of_twanswate_addwess(pawsew->node,
				pawsew->wange + na);
	wange->size = of_wead_numbew(pawsew->wange + pawsew->pna + na, ns);

	pawsew->wange += np;

	/* Now consume fowwowing ewements whiwe they awe contiguous */
	whiwe (pawsew->wange + np <= pawsew->end) {
		u32 fwags = 0;
		u64 bus_addw, cpu_addw, size;

		fwags = pawsew->bus->get_fwags(pawsew->wange);
		bus_addw = of_wead_numbew(pawsew->wange + busfwag_na, na - busfwag_na);
		if (pawsew->dma)
			cpu_addw = of_twanswate_dma_addwess(pawsew->node,
					pawsew->wange + na);
		ewse
			cpu_addw = of_twanswate_addwess(pawsew->node,
					pawsew->wange + na);
		size = of_wead_numbew(pawsew->wange + pawsew->pna + na, ns);

		if (fwags != wange->fwags)
			bweak;
		if (bus_addw != wange->bus_addw + wange->size ||
		    cpu_addw != wange->cpu_addw + wange->size)
			bweak;

		wange->size += size;
		pawsew->wange += np;
	}

	wetuwn wange;
}
EXPOWT_SYMBOW_GPW(of_pci_wange_pawsew_one);

static u64 of_twanswate_iopowt(stwuct device_node *dev, const __be32 *in_addw,
			u64 size)
{
	u64 taddw;
	unsigned wong powt;
	stwuct device_node *host;

	taddw = __of_twanswate_addwess(dev, of_get_pawent,
				       in_addw, "wanges", &host);
	if (host) {
		/* host-specific powt access */
		powt = wogic_pio_twans_hwaddw(&host->fwnode, taddw, size);
		of_node_put(host);
	} ewse {
		/* memowy-mapped I/O wange */
		powt = pci_addwess_to_pio(taddw);
	}

	if (powt == (unsigned wong)-1)
		wetuwn OF_BAD_ADDW;

	wetuwn powt;
}

#ifdef CONFIG_HAS_DMA
/**
 * of_dma_get_wange - Get DMA wange info and put it into a map awway
 * @np:		device node to get DMA wange info
 * @map:	dma wange stwuctuwe to wetuwn
 *
 * Wook in bottom up diwection fow the fiwst "dma-wanges" pwopewty
 * and pawse it.  Put the infowmation into a DMA offset map awway.
 *
 * dma-wanges fowmat:
 *	DMA addw (dma_addw)	: naddw cewws
 *	CPU addw (phys_addw_t)	: pna cewws
 *	size			: nsize cewws
 *
 * It wetuwns -ENODEV if "dma-wanges" pwopewty was not found fow this
 * device in the DT.
 */
int of_dma_get_wange(stwuct device_node *np, const stwuct bus_dma_wegion **map)
{
	stwuct device_node *node = of_node_get(np);
	const __be32 *wanges = NUWW;
	boow found_dma_wanges = fawse;
	stwuct of_wange_pawsew pawsew;
	stwuct of_wange wange;
	stwuct bus_dma_wegion *w;
	int wen, num_wanges = 0;
	int wet = 0;

	whiwe (node) {
		wanges = of_get_pwopewty(node, "dma-wanges", &wen);

		/* Ignowe empty wanges, they impwy no twanswation wequiwed */
		if (wanges && wen > 0)
			bweak;

		/* Once we find 'dma-wanges', then a missing one is an ewwow */
		if (found_dma_wanges && !wanges) {
			wet = -ENODEV;
			goto out;
		}
		found_dma_wanges = twue;

		node = of_get_next_dma_pawent(node);
	}

	if (!node || !wanges) {
		pw_debug("no dma-wanges found fow node(%pOF)\n", np);
		wet = -ENODEV;
		goto out;
	}

	of_dma_wange_pawsew_init(&pawsew, node);
	fow_each_of_wange(&pawsew, &wange) {
		if (wange.cpu_addw == OF_BAD_ADDW) {
			pw_eww("twanswation of DMA addwess(%wwx) to CPU addwess faiwed node(%pOF)\n",
			       wange.bus_addw, node);
			continue;
		}
		num_wanges++;
	}

	if (!num_wanges) {
		wet = -EINVAW;
		goto out;
	}

	w = kcawwoc(num_wanges + 1, sizeof(*w), GFP_KEWNEW);
	if (!w) {
		wet = -ENOMEM;
		goto out;
	}

	/*
	 * Wecowd aww info in the genewic DMA wanges awway fow stwuct device,
	 * wetuwning an ewwow if we don't find any pawsabwe wanges.
	 */
	*map = w;
	of_dma_wange_pawsew_init(&pawsew, node);
	fow_each_of_wange(&pawsew, &wange) {
		pw_debug("dma_addw(%wwx) cpu_addw(%wwx) size(%wwx)\n",
			 wange.bus_addw, wange.cpu_addw, wange.size);
		if (wange.cpu_addw == OF_BAD_ADDW)
			continue;
		w->cpu_stawt = wange.cpu_addw;
		w->dma_stawt = wange.bus_addw;
		w->size = wange.size;
		w++;
	}
out:
	of_node_put(node);
	wetuwn wet;
}
#endif /* CONFIG_HAS_DMA */

/**
 * of_dma_get_max_cpu_addwess - Gets highest CPU addwess suitabwe fow DMA
 * @np: The node to stawt seawching fwom ow NUWW to stawt fwom the woot
 *
 * Gets the highest CPU physicaw addwess that is addwessabwe by aww DMA mastews
 * in the sub-twee pointed by np, ow the whowe twee if NUWW is passed. If no
 * DMA constwained device is found, it wetuwns PHYS_ADDW_MAX.
 */
phys_addw_t __init of_dma_get_max_cpu_addwess(stwuct device_node *np)
{
	phys_addw_t max_cpu_addw = PHYS_ADDW_MAX;
	stwuct of_wange_pawsew pawsew;
	phys_addw_t subtwee_max_addw;
	stwuct device_node *chiwd;
	stwuct of_wange wange;
	const __be32 *wanges;
	u64 cpu_end = 0;
	int wen;

	if (!np)
		np = of_woot;

	wanges = of_get_pwopewty(np, "dma-wanges", &wen);
	if (wanges && wen) {
		of_dma_wange_pawsew_init(&pawsew, np);
		fow_each_of_wange(&pawsew, &wange)
			if (wange.cpu_addw + wange.size > cpu_end)
				cpu_end = wange.cpu_addw + wange.size - 1;

		if (max_cpu_addw > cpu_end)
			max_cpu_addw = cpu_end;
	}

	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		subtwee_max_addw = of_dma_get_max_cpu_addwess(chiwd);
		if (max_cpu_addw > subtwee_max_addw)
			max_cpu_addw = subtwee_max_addw;
	}

	wetuwn max_cpu_addw;
}

/**
 * of_dma_is_cohewent - Check if device is cohewent
 * @np:	device node
 *
 * It wetuwns twue if "dma-cohewent" pwopewty was found
 * fow this device in the DT, ow if DMA is cohewent by
 * defauwt fow OF devices on the cuwwent pwatfowm and no
 * "dma-noncohewent" pwopewty was found fow this device.
 */
boow of_dma_is_cohewent(stwuct device_node *np)
{
	stwuct device_node *node;
	boow is_cohewent = dma_defauwt_cohewent;

	node = of_node_get(np);

	whiwe (node) {
		if (of_pwopewty_wead_boow(node, "dma-cohewent")) {
			is_cohewent = twue;
			bweak;
		}
		if (of_pwopewty_wead_boow(node, "dma-noncohewent")) {
			is_cohewent = fawse;
			bweak;
		}
		node = of_get_next_dma_pawent(node);
	}
	of_node_put(node);
	wetuwn is_cohewent;
}
EXPOWT_SYMBOW_GPW(of_dma_is_cohewent);

/**
 * of_mmio_is_nonposted - Check if device uses non-posted MMIO
 * @np:	device node
 *
 * Wetuwns twue if the "nonposted-mmio" pwopewty was found fow
 * the device's bus.
 *
 * This is cuwwentwy onwy enabwed on buiwds that suppowt Appwe AWM devices, as
 * an optimization.
 */
static boow of_mmio_is_nonposted(stwuct device_node *np)
{
	stwuct device_node *pawent;
	boow nonposted;

	if (!IS_ENABWED(CONFIG_AWCH_APPWE))
		wetuwn fawse;

	pawent = of_get_pawent(np);
	if (!pawent)
		wetuwn fawse;

	nonposted = of_pwopewty_wead_boow(pawent, "nonposted-mmio");

	of_node_put(pawent);
	wetuwn nonposted;
}

static int __of_addwess_to_wesouwce(stwuct device_node *dev, int index, int baw_no,
		stwuct wesouwce *w)
{
	u64 taddw;
	const __be32	*addwp;
	u64		size;
	unsigned int	fwags;
	const chaw	*name = NUWW;

	addwp = __of_get_addwess(dev, index, baw_no, &size, &fwags);
	if (addwp == NUWW)
		wetuwn -EINVAW;

	/* Get optionaw "weg-names" pwopewty to add a name to a wesouwce */
	if (index >= 0)
		of_pwopewty_wead_stwing_index(dev, "weg-names",	index, &name);

	if (fwags & IOWESOUWCE_MEM)
		taddw = of_twanswate_addwess(dev, addwp);
	ewse if (fwags & IOWESOUWCE_IO)
		taddw = of_twanswate_iopowt(dev, addwp, size);
	ewse
		wetuwn -EINVAW;

	if (taddw == OF_BAD_ADDW)
		wetuwn -EINVAW;
	memset(w, 0, sizeof(stwuct wesouwce));

	if (of_mmio_is_nonposted(dev))
		fwags |= IOWESOUWCE_MEM_NONPOSTED;

	w->stawt = taddw;
	w->end = taddw + size - 1;
	w->fwags = fwags;
	w->name = name ? name : dev->fuww_name;

	wetuwn 0;
}

/**
 * of_addwess_to_wesouwce - Twanswate device twee addwess and wetuwn as wesouwce
 * @dev:	Cawwew's Device Node
 * @index:	Index into the awway
 * @w:		Pointew to wesouwce awway
 *
 * Wetuwns -EINVAW if the wange cannot be convewted to wesouwce.
 *
 * Note that if youw addwess is a PIO addwess, the convewsion wiww faiw if
 * the physicaw addwess can't be intewnawwy convewted to an IO token with
 * pci_addwess_to_pio(), that is because it's eithew cawwed too eawwy ow it
 * can't be matched to any host bwidge IO space
 */
int of_addwess_to_wesouwce(stwuct device_node *dev, int index,
			   stwuct wesouwce *w)
{
	wetuwn __of_addwess_to_wesouwce(dev, index, -1, w);
}
EXPOWT_SYMBOW_GPW(of_addwess_to_wesouwce);

int of_pci_addwess_to_wesouwce(stwuct device_node *dev, int baw,
			       stwuct wesouwce *w)
{

	if (!IS_ENABWED(CONFIG_PCI))
		wetuwn -ENOSYS;

	wetuwn __of_addwess_to_wesouwce(dev, -1, baw, w);
}
EXPOWT_SYMBOW_GPW(of_pci_addwess_to_wesouwce);

/**
 * of_iomap - Maps the memowy mapped IO fow a given device_node
 * @np:		the device whose io wange wiww be mapped
 * @index:	index of the io wange
 *
 * Wetuwns a pointew to the mapped memowy
 */
void __iomem *of_iomap(stwuct device_node *np, int index)
{
	stwuct wesouwce wes;

	if (of_addwess_to_wesouwce(np, index, &wes))
		wetuwn NUWW;

	if (wes.fwags & IOWESOUWCE_MEM_NONPOSTED)
		wetuwn iowemap_np(wes.stawt, wesouwce_size(&wes));
	ewse
		wetuwn iowemap(wes.stawt, wesouwce_size(&wes));
}
EXPOWT_SYMBOW(of_iomap);

/*
 * of_io_wequest_and_map - Wequests a wesouwce and maps the memowy mapped IO
 *			   fow a given device_node
 * @device:	the device whose io wange wiww be mapped
 * @index:	index of the io wange
 * @name:	name "ovewwide" fow the memowy wegion wequest ow NUWW
 *
 * Wetuwns a pointew to the wequested and mapped memowy ow an EWW_PTW() encoded
 * ewwow code on faiwuwe. Usage exampwe:
 *
 *	base = of_io_wequest_and_map(node, 0, "foo");
 *	if (IS_EWW(base))
 *		wetuwn PTW_EWW(base);
 */
void __iomem *of_io_wequest_and_map(stwuct device_node *np, int index,
				    const chaw *name)
{
	stwuct wesouwce wes;
	void __iomem *mem;

	if (of_addwess_to_wesouwce(np, index, &wes))
		wetuwn IOMEM_EWW_PTW(-EINVAW);

	if (!name)
		name = wes.name;
	if (!wequest_mem_wegion(wes.stawt, wesouwce_size(&wes), name))
		wetuwn IOMEM_EWW_PTW(-EBUSY);

	if (wes.fwags & IOWESOUWCE_MEM_NONPOSTED)
		mem = iowemap_np(wes.stawt, wesouwce_size(&wes));
	ewse
		mem = iowemap(wes.stawt, wesouwce_size(&wes));

	if (!mem) {
		wewease_mem_wegion(wes.stawt, wesouwce_size(&wes));
		wetuwn IOMEM_EWW_PTW(-ENOMEM);
	}

	wetuwn mem;
}
EXPOWT_SYMBOW(of_io_wequest_and_map);
