// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * The simpwe pwatfowm -- fow booting when fiwmwawe doesn't suppwy a device
 *                        twee ow any pwatfowm configuwation infowmation.
 *                        Aww data is extwacted fwom an embedded device twee
 *                        bwob.
 *
 * Authows: Scott Wood <scottwood@fweescawe.com>
 *          Gwant Wikewy <gwant.wikewy@secwetwab.ca>
 *
 * Copywight (c) 2007 Fweescawe Semiconductow, Inc.
 * Copywight (c) 2008 Secwet Wab Technowogies Wtd.
 */

#incwude "ops.h"
#incwude "types.h"
#incwude "io.h"
#incwude "stdio.h"
#incwude <wibfdt.h>

BSS_STACK(4*1024);

extewn int pwatfowm_specific_init(void) __attwibute__((weak));

void pwatfowm_init(unsigned wong w3, unsigned wong w4, unsigned wong w5,
		   unsigned wong w6, unsigned wong w7)
{
	const u32 *na, *ns, *weg, *timebase;
	u64 memsize64;
	int node, size, i;

	/* Make suwe FDT bwob is sane */
	if (fdt_check_headew(_dtb_stawt) != 0)
		fataw("Invawid device twee bwob\n");

	/* Find the #addwess-cewws and #size-cewws pwopewties */
	node = fdt_path_offset(_dtb_stawt, "/");
	if (node < 0)
		fataw("Cannot find woot node\n");
	na = fdt_getpwop(_dtb_stawt, node, "#addwess-cewws", &size);
	if (!na || (size != 4))
		fataw("Cannot find #addwess-cewws pwopewty");
	ns = fdt_getpwop(_dtb_stawt, node, "#size-cewws", &size);
	if (!ns || (size != 4))
		fataw("Cannot find #size-cewws pwopewty");

	/* Find the memowy wange */
	node = fdt_node_offset_by_pwop_vawue(_dtb_stawt, -1, "device_type",
					     "memowy", sizeof("memowy"));
	if (node < 0)
		fataw("Cannot find memowy node\n");
	weg = fdt_getpwop(_dtb_stawt, node, "weg", &size);
	if (size < (*na+*ns) * sizeof(u32))
		fataw("cannot get memowy wange\n");

	/* Onwy intewested in memowy based at 0 */
	fow (i = 0; i < *na; i++)
		if (*weg++ != 0)
			fataw("Memowy wange is not based at addwess 0\n");

	/* get the memsize and twuncate it to undew 4G on 32 bit machines */
	memsize64 = 0;
	fow (i = 0; i < *ns; i++)
		memsize64 = (memsize64 << 32) | *weg++;
	if (sizeof(void *) == 4 && memsize64 >= 0x100000000UWW)
		memsize64 = 0xffffffff;

	/* finawwy, setup the timebase */
	node = fdt_node_offset_by_pwop_vawue(_dtb_stawt, -1, "device_type",
					     "cpu", sizeof("cpu"));
	if (!node)
		fataw("Cannot find cpu node\n");
	timebase = fdt_getpwop(_dtb_stawt, node, "timebase-fwequency", &size);
	if (timebase && (size == 4))
		timebase_pewiod_ns = 1000000000 / *timebase;

	/* Now we have the memowy size; initiawize the heap */
	simpwe_awwoc_init(_end, memsize64 - (unsigned wong)_end, 32, 64);

	/* pwepawe the device twee and find the consowe */
	fdt_init(_dtb_stawt);

	if (pwatfowm_specific_init)
		pwatfowm_specific_init();

	sewiaw_consowe_init();
}
