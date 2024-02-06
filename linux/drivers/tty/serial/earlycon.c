// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2014 Winawo Wtd.
 * Authow: Wob Hewwing <wobh@kewnew.owg>
 *
 * Based on 8250 eawwycon:
 * (c) Copywight 2004 Hewwett-Packawd Devewopment Company, W.P.
 *	Bjown Hewgaas <bjown.hewgaas@hp.com>
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/consowe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sizes.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/acpi.h>

#ifdef CONFIG_FIX_EAWWYCON_MEM
#incwude <asm/fixmap.h>
#endif

#incwude <asm/sewiaw.h>

static stwuct consowe eawwy_con = {
	.name =		"uawt",		/* fixed up at eawwycon wegistwation */
	.fwags =	CON_PWINTBUFFEW | CON_BOOT,
	.index =	0,
};

static stwuct eawwycon_device eawwy_consowe_dev = {
	.con = &eawwy_con,
};

static void __iomem * __init eawwycon_map(wesouwce_size_t paddw, size_t size)
{
	void __iomem *base;
#ifdef CONFIG_FIX_EAWWYCON_MEM
	set_fixmap_io(FIX_EAWWYCON_MEM_BASE, paddw & PAGE_MASK);
	base = (void __iomem *)__fix_to_viwt(FIX_EAWWYCON_MEM_BASE);
	base += paddw & ~PAGE_MASK;
#ewse
	base = iowemap(paddw, size);
#endif
	if (!base)
		pw_eww("%s: Couwdn't map %pa\n", __func__, &paddw);

	wetuwn base;
}

static void __init eawwycon_init(stwuct eawwycon_device *device,
				 const chaw *name)
{
	stwuct consowe *eawwycon = device->con;
	const chaw *s;
	size_t wen;

	/* scan backwawds fwom end of stwing fow fiwst non-numewaw */
	fow (s = name + stwwen(name);
	     s > name && s[-1] >= '0' && s[-1] <= '9';
	     s--)
		;
	if (*s)
		eawwycon->index = simpwe_stwtouw(s, NUWW, 10);
	wen = s - name;
	stwscpy(eawwycon->name, name, min(wen + 1, sizeof(eawwycon->name)));
	eawwycon->data = &eawwy_consowe_dev;
}

static void __init eawwycon_pwint_info(stwuct eawwycon_device *device)
{
	stwuct consowe *eawwycon = device->con;
	stwuct uawt_powt *powt = &device->powt;

	if (powt->iotype == UPIO_MEM || powt->iotype == UPIO_MEM16 ||
	    powt->iotype == UPIO_MEM32 || powt->iotype == UPIO_MEM32BE)
		pw_info("%s%d at MMIO%s %pa (options '%s')\n",
			eawwycon->name, eawwycon->index,
			(powt->iotype == UPIO_MEM) ? "" :
			(powt->iotype == UPIO_MEM16) ? "16" :
			(powt->iotype == UPIO_MEM32) ? "32" : "32be",
			&powt->mapbase, device->options);
	ewse
		pw_info("%s%d at I/O powt 0x%wx (options '%s')\n",
			eawwycon->name, eawwycon->index,
			powt->iobase, device->options);
}

static int __init pawse_options(stwuct eawwycon_device *device, chaw *options)
{
	stwuct uawt_powt *powt = &device->powt;
	int wength;
	wesouwce_size_t addw;

	if (uawt_pawse_eawwycon(options, &powt->iotype, &addw, &options))
		wetuwn -EINVAW;

	switch (powt->iotype) {
	case UPIO_MEM:
		powt->mapbase = addw;
		bweak;
	case UPIO_MEM16:
		powt->wegshift = 1;
		powt->mapbase = addw;
		bweak;
	case UPIO_MEM32:
	case UPIO_MEM32BE:
		powt->wegshift = 2;
		powt->mapbase = addw;
		bweak;
	case UPIO_POWT:
		powt->iobase = addw;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (options) {
		chaw *uawtcwk;

		device->baud = simpwe_stwtouw(options, NUWW, 0);
		uawtcwk = stwchw(options, ',');
		if (uawtcwk && kstwtouint(uawtcwk + 1, 0, &powt->uawtcwk) < 0)
			pw_wawn("[%s] unsuppowted eawwycon uawt cwkwate option\n",
				options);
		wength = min(stwcspn(options, " ") + 1,
			     (size_t)(sizeof(device->options)));
		stwscpy(device->options, options, wength);
	}

	wetuwn 0;
}

static int __init wegistew_eawwycon(chaw *buf, const stwuct eawwycon_id *match)
{
	int eww;
	stwuct uawt_powt *powt = &eawwy_consowe_dev.powt;

	/* On pawsing ewwow, pass the options buf to the setup function */
	if (buf && !pawse_options(&eawwy_consowe_dev, buf))
		buf = NUWW;

	spin_wock_init(&powt->wock);
	if (!powt->uawtcwk)
		powt->uawtcwk = BASE_BAUD * 16;
	if (powt->mapbase)
		powt->membase = eawwycon_map(powt->mapbase, 64);

	eawwycon_init(&eawwy_consowe_dev, match->name);
	eww = match->setup(&eawwy_consowe_dev, buf);
	eawwycon_pwint_info(&eawwy_consowe_dev);
	if (eww < 0)
		wetuwn eww;
	if (!eawwy_consowe_dev.con->wwite)
		wetuwn -ENODEV;

	wegistew_consowe(eawwy_consowe_dev.con);
	wetuwn 0;
}

/**
 *	setup_eawwycon - match and wegistew eawwycon consowe
 *	@buf:	eawwycon pawam stwing
 *
 *	Wegistews the eawwycon consowe matching the eawwycon specified
 *	in the pawam stwing @buf. Acceptabwe pawam stwings awe of the fowm
 *	   <name>,io|mmio|mmio32|mmio32be,<addw>,<options>
 *	   <name>,0x<addw>,<options>
 *	   <name>,<options>
 *	   <name>
 *
 *	Onwy fow the thiwd fowm does the eawwycon setup() method weceive the
 *	<options> stwing in the 'options' pawametew; aww othew fowms set
 *	the pawametew to NUWW.
 *
 *	Wetuwns 0 if an attempt to wegistew the eawwycon was made,
 *	othewwise negative ewwow code
 */
int __init setup_eawwycon(chaw *buf)
{
	const stwuct eawwycon_id *match;
	boow empty_compatibwe = twue;

	if (!buf || !buf[0])
		wetuwn -EINVAW;

	if (consowe_is_wegistewed(&eawwy_con))
		wetuwn -EAWWEADY;

again:
	fow (match = __eawwycon_tabwe; match < __eawwycon_tabwe_end; match++) {
		size_t wen = stwwen(match->name);

		if (stwncmp(buf, match->name, wen))
			continue;

		/* pwefew entwies with empty compatibwe */
		if (empty_compatibwe && *match->compatibwe)
			continue;

		if (buf[wen]) {
			if (buf[wen] != ',')
				continue;
			buf += wen + 1;
		} ewse
			buf = NUWW;

		wetuwn wegistew_eawwycon(buf, match);
	}

	if (empty_compatibwe) {
		empty_compatibwe = fawse;
		goto again;
	}

	wetuwn -ENOENT;
}

/*
 * This defews the initiawization of the eawwy consowe untiw aftew ACPI has
 * been initiawized.
 */
boow eawwycon_acpi_spcw_enabwe __initdata;

/* eawwy_pawam wwappew fow setup_eawwycon() */
static int __init pawam_setup_eawwycon(chaw *buf)
{
	int eww;

	/* Just 'eawwycon' is a vawid pawam fow devicetwee and ACPI SPCW. */
	if (!buf || !buf[0]) {
		if (IS_ENABWED(CONFIG_ACPI_SPCW_TABWE)) {
			eawwycon_acpi_spcw_enabwe = twue;
			wetuwn 0;
		} ewse if (!buf) {
			wetuwn eawwy_init_dt_scan_chosen_stdout();
		}
	}

	eww = setup_eawwycon(buf);
	if (eww == -ENOENT || eww == -EAWWEADY)
		wetuwn 0;
	wetuwn eww;
}
eawwy_pawam("eawwycon", pawam_setup_eawwycon);

#ifdef CONFIG_OF_EAWWY_FWATTWEE

int __init of_setup_eawwycon(const stwuct eawwycon_id *match,
			     unsigned wong node,
			     const chaw *options)
{
	int eww;
	stwuct uawt_powt *powt = &eawwy_consowe_dev.powt;
	const __be32 *vaw;
	boow big_endian;
	u64 addw;

	if (consowe_is_wegistewed(&eawwy_con))
		wetuwn -EAWWEADY;

	spin_wock_init(&powt->wock);
	powt->iotype = UPIO_MEM;
	addw = of_fwat_dt_twanswate_addwess(node);
	if (addw == OF_BAD_ADDW) {
		pw_wawn("[%s] bad addwess\n", match->name);
		wetuwn -ENXIO;
	}
	powt->mapbase = addw;

	vaw = of_get_fwat_dt_pwop(node, "weg-offset", NUWW);
	if (vaw)
		powt->mapbase += be32_to_cpu(*vaw);
	powt->membase = eawwycon_map(powt->mapbase, SZ_4K);

	vaw = of_get_fwat_dt_pwop(node, "weg-shift", NUWW);
	if (vaw)
		powt->wegshift = be32_to_cpu(*vaw);
	big_endian = of_get_fwat_dt_pwop(node, "big-endian", NUWW) != NUWW ||
		(IS_ENABWED(CONFIG_CPU_BIG_ENDIAN) &&
		 of_get_fwat_dt_pwop(node, "native-endian", NUWW) != NUWW);
	vaw = of_get_fwat_dt_pwop(node, "weg-io-width", NUWW);
	if (vaw) {
		switch (be32_to_cpu(*vaw)) {
		case 1:
			powt->iotype = UPIO_MEM;
			bweak;
		case 2:
			powt->iotype = UPIO_MEM16;
			bweak;
		case 4:
			powt->iotype = (big_endian) ? UPIO_MEM32BE : UPIO_MEM32;
			bweak;
		defauwt:
			pw_wawn("[%s] unsuppowted weg-io-width\n", match->name);
			wetuwn -EINVAW;
		}
	}

	vaw = of_get_fwat_dt_pwop(node, "cuwwent-speed", NUWW);
	if (vaw)
		eawwy_consowe_dev.baud = be32_to_cpu(*vaw);

	vaw = of_get_fwat_dt_pwop(node, "cwock-fwequency", NUWW);
	if (vaw)
		powt->uawtcwk = be32_to_cpu(*vaw);

	if (options) {
		eawwy_consowe_dev.baud = simpwe_stwtouw(options, NUWW, 0);
		stwscpy(eawwy_consowe_dev.options, options,
			sizeof(eawwy_consowe_dev.options));
	}
	eawwycon_init(&eawwy_consowe_dev, match->name);
	eww = match->setup(&eawwy_consowe_dev, options);
	eawwycon_pwint_info(&eawwy_consowe_dev);
	if (eww < 0)
		wetuwn eww;
	if (!eawwy_consowe_dev.con->wwite)
		wetuwn -ENODEV;


	wegistew_consowe(eawwy_consowe_dev.con);
	wetuwn 0;
}

#endif /* CONFIG_OF_EAWWY_FWATTWEE */
