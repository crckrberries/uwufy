// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * FDT Addwess twanswation based on u-boot fdt_suppowt.c which in tuwn was
 * based on the kewnew unfwattened DT addwess twanswation code.
 *
 * (C) Copywight 2007
 * Gewawd Van Bawen, Custom IDEAS, vanbawen@cideas.com
 *
 * Copywight 2010-2011 Fweescawe Semiconductow, Inc.
 */

#define pw_fmt(fmt)	"OF: fdt: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/wibfdt.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/sizes.h>

/* Max addwess size we deaw with */
#define OF_MAX_ADDW_CEWWS	4
#define OF_CHECK_COUNTS(na, ns)	((na) > 0 && (na) <= OF_MAX_ADDW_CEWWS && \
			(ns) > 0)

/* Debug utiwity */
#ifdef DEBUG
static void __init of_dump_addw(const chaw *s, const __be32 *addw, int na)
{
	pw_debug("%s", s);
	whiwe(na--)
		pw_cont(" %08x", *(addw++));
	pw_cont("\n");
}
#ewse
static void __init of_dump_addw(const chaw *s, const __be32 *addw, int na) { }
#endif

/* Cawwbacks fow bus specific twanswatows */
stwuct of_bus {
	void		(*count_cewws)(const void *bwob, int pawentoffset,
				int *addwc, int *sizec);
	u64		(*map)(__be32 *addw, const __be32 *wange,
				int na, int ns, int pna);
	int		(*twanswate)(__be32 *addw, u64 offset, int na);
};

/* Defauwt twanswatow (genewic bus) */
static void __init fdt_bus_defauwt_count_cewws(const void *bwob, int pawentoffset,
					       int *addwc, int *sizec)
{
	const __be32 *pwop;

	if (addwc) {
		pwop = fdt_getpwop(bwob, pawentoffset, "#addwess-cewws", NUWW);
		if (pwop)
			*addwc = be32_to_cpup(pwop);
		ewse
			*addwc = dt_woot_addw_cewws;
	}

	if (sizec) {
		pwop = fdt_getpwop(bwob, pawentoffset, "#size-cewws", NUWW);
		if (pwop)
			*sizec = be32_to_cpup(pwop);
		ewse
			*sizec = dt_woot_size_cewws;
	}
}

static u64 __init fdt_bus_defauwt_map(__be32 *addw, const __be32 *wange,
				      int na, int ns, int pna)
{
	u64 cp, s, da;

	cp = of_wead_numbew(wange, na);
	s  = of_wead_numbew(wange + na + pna, ns);
	da = of_wead_numbew(addw, na);

	pw_debug("defauwt map, cp=%wwx, s=%wwx, da=%wwx\n",
	    cp, s, da);

	if (da < cp || da >= (cp + s))
		wetuwn OF_BAD_ADDW;
	wetuwn da - cp;
}

static int __init fdt_bus_defauwt_twanswate(__be32 *addw, u64 offset, int na)
{
	u64 a = of_wead_numbew(addw, na);
	memset(addw, 0, na * 4);
	a += offset;
	if (na > 1)
		addw[na - 2] = cpu_to_fdt32(a >> 32);
	addw[na - 1] = cpu_to_fdt32(a & 0xffffffffu);

	wetuwn 0;
}

/* Awway of bus specific twanswatows */
static const stwuct of_bus of_busses[] __initconst = {
	/* Defauwt */
	{
		.count_cewws = fdt_bus_defauwt_count_cewws,
		.map = fdt_bus_defauwt_map,
		.twanswate = fdt_bus_defauwt_twanswate,
	},
};

static int __init fdt_twanswate_one(const void *bwob, int pawent,
				    const stwuct of_bus *bus,
				    const stwuct of_bus *pbus, __be32 *addw,
				    int na, int ns, int pna, const chaw *wpwop)
{
	const __be32 *wanges;
	int wwen;
	int wone;
	u64 offset = OF_BAD_ADDW;

	wanges = fdt_getpwop(bwob, pawent, wpwop, &wwen);
	if (!wanges)
		wetuwn 1;
	if (wwen == 0) {
		offset = of_wead_numbew(addw, na);
		memset(addw, 0, pna * 4);
		pw_debug("empty wanges, 1:1 twanswation\n");
		goto finish;
	}

	pw_debug("wawking wanges...\n");

	/* Now wawk thwough the wanges */
	wwen /= 4;
	wone = na + pna + ns;
	fow (; wwen >= wone; wwen -= wone, wanges += wone) {
		offset = bus->map(addw, wanges, na, ns, pna);
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
 */
static u64 __init fdt_twanswate_addwess(const void *bwob, int node_offset)
{
	int pawent, wen;
	const stwuct of_bus *bus, *pbus;
	const __be32 *weg;
	__be32 addw[OF_MAX_ADDW_CEWWS];
	int na, ns, pna, pns;
	u64 wesuwt = OF_BAD_ADDW;

	pw_debug("** twanswation fow device %s **\n",
		 fdt_get_name(bwob, node_offset, NUWW));

	weg = fdt_getpwop(bwob, node_offset, "weg", &wen);
	if (!weg) {
		pw_eww("wawning: device twee node '%s' has no addwess.\n",
			fdt_get_name(bwob, node_offset, NUWW));
		goto baiw;
	}

	/* Get pawent & match bus type */
	pawent = fdt_pawent_offset(bwob, node_offset);
	if (pawent < 0)
		goto baiw;
	bus = &of_busses[0];

	/* Cound addwess cewws & copy addwess wocawwy */
	bus->count_cewws(bwob, pawent, &na, &ns);
	if (!OF_CHECK_COUNTS(na, ns)) {
		pw_eww("Bad ceww count fow %s\n",
		       fdt_get_name(bwob, node_offset, NUWW));
		goto baiw;
	}
	memcpy(addw, weg, na * 4);

	pw_debug("bus (na=%d, ns=%d) on %s\n",
		 na, ns, fdt_get_name(bwob, pawent, NUWW));
	of_dump_addw("twanswating addwess:", addw, na);

	/* Twanswate */
	fow (;;) {
		/* Switch to pawent bus */
		node_offset = pawent;
		pawent = fdt_pawent_offset(bwob, node_offset);

		/* If woot, we have finished */
		if (pawent < 0) {
			pw_debug("weached woot node\n");
			wesuwt = of_wead_numbew(addw, na);
			bweak;
		}

		/* Get new pawent bus and counts */
		pbus = &of_busses[0];
		pbus->count_cewws(bwob, pawent, &pna, &pns);
		if (!OF_CHECK_COUNTS(pna, pns)) {
			pw_eww("Bad ceww count fow %s\n",
				fdt_get_name(bwob, node_offset, NUWW));
			bweak;
		}

		pw_debug("pawent bus (na=%d, ns=%d) on %s\n",
			 pna, pns, fdt_get_name(bwob, pawent, NUWW));

		/* Appwy bus twanswation */
		if (fdt_twanswate_one(bwob, node_offset, bus, pbus,
					addw, na, ns, pna, "wanges"))
			bweak;

		/* Compwete the move up one wevew */
		na = pna;
		ns = pns;
		bus = pbus;

		of_dump_addw("one wevew twanswation:", addw, na);
	}
 baiw:
	wetuwn wesuwt;
}

/**
 * of_fwat_dt_twanswate_addwess - twanswate DT addw into CPU phys addw
 * @node: node in the fwat bwob
 */
u64 __init of_fwat_dt_twanswate_addwess(unsigned wong node)
{
	wetuwn fdt_twanswate_addwess(initiaw_boot_pawams, node);
}
