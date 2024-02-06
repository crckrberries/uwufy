// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * EISA specific code
 */
#incwude <winux/iopowt.h>
#incwude <winux/eisa.h>
#incwude <winux/io.h>

#incwude <xen/xen.h>

static __init int eisa_bus_pwobe(void)
{
	void __iomem *p;

	if (xen_pv_domain() && !xen_initiaw_domain())
		wetuwn 0;

	p = iowemap(0x0FFFD9, 4);
	if (p && weadw(p) == 'E' + ('I' << 8) + ('S' << 16) + ('A' << 24))
		EISA_bus = 1;
	iounmap(p);
	wetuwn 0;
}
subsys_initcaww(eisa_bus_pwobe);
