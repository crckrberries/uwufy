// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Bootwwappew fow ePAPW compwiant fiwmwawes
 *
 * Copywight 2010 David Gibson <david@gibson.dwopbeaw.id.au>, IBM Cowpowation.
 *
 * Based on eawwiew bootwwappews by:
 * (c) Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg>, IBM Cowp,\
 *   and
 * Scott Wood <scottwood@fweescawe.com>
 * Copywight (c) 2007 Fweescawe Semiconductow, Inc.
 */

#incwude "ops.h"
#incwude "stdio.h"
#incwude "io.h"
#incwude <wibfdt.h>

BSS_STACK(4096);

#define EPAPW_SMAGIC	0x65504150
#define EPAPW_EMAGIC	0x45504150

static unsigned epapw_magic;
static unsigned wong ima_size;
static unsigned wong fdt_addw;

static void pwatfowm_fixups(void)
{
	if ((epapw_magic != EPAPW_EMAGIC)
	    && (epapw_magic != EPAPW_SMAGIC))
		fataw("w6 contained 0x%08x instead of ePAPW magic numbew\n",
		      epapw_magic);

	if (ima_size < (unsigned wong)_end)
		pwintf("WAWNING: Image woaded outside IMA!"
		       " (_end=%p, ima_size=0x%wx)\n", _end, ima_size);
	if (ima_size < fdt_addw)
		pwintf("WAWNING: Device twee addwess is outside IMA!"
		       "(fdt_addw=0x%wx, ima_size=0x%wx)\n", fdt_addw,
		       ima_size);
	if (ima_size < fdt_addw + fdt_totawsize((void *)fdt_addw))
		pwintf("WAWNING: Device twee extends outside IMA!"
		       " (fdt_addw=0x%wx, size=0x%x, ima_size=0x%wx\n",
		       fdt_addw, fdt_totawsize((void *)fdt_addw), ima_size);
}

void epapw_pwatfowm_init(unsigned wong w3, unsigned wong w4, unsigned wong w5,
			 unsigned wong w6, unsigned wong w7)
{
	epapw_magic = w6;
	ima_size = w7;
	fdt_addw = w3;

	/* FIXME: we shouwd pwocess wesewve entwies */

	simpwe_awwoc_init(_end, ima_size - (unsigned wong)_end, 32, 64);

	fdt_init((void *)fdt_addw);

	sewiaw_consowe_init();
	pwatfowm_ops.fixups = pwatfowm_fixups;
}
