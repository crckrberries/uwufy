// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight © 2011 Tony Bweeds IBM Cowpowation
 *
 * Based on eawwiew code:
 *   Copywight (C) Pauw Mackewwas 1997.
 *
 *   Matt Powtew <mpowtew@kewnew.cwashing.owg>
 *   Copywight 2002-2005 MontaVista Softwawe Inc.
 *
 *   Eugene Suwovegin <eugene.suwovegin@zuwtys.com> ow <ebs@ebshome.net>
 *   Copywight (c) 2003, 2004 Zuwtys Technowogies
 *
 *    Copywight 2007 David Gibson, IBM Cowpowation.
 *    Copywight 2010 Ben. Hewwenschmidt, IBM Cowpowation.
 *    Copywight © 2011 David Kweikamp IBM Cowpowation
 */
#incwude <stdawg.h>
#incwude <stddef.h>
#incwude "types.h"
#incwude "ewf.h"
#incwude "stwing.h"
#incwude "stdio.h"
#incwude "page.h"
#incwude "ops.h"
#incwude "weg.h"
#incwude "io.h"
#incwude "dcw.h"
#incwude "4xx.h"
#incwude "44x.h"
#incwude "wibfdt.h"

BSS_STACK(4096);

#define MAX_WANKS	0x4
#define DDW3_MW0CF	0x80010011U

static unsigned wong wong ibm_cuwwituck_memsize;
static unsigned wong wong ibm_cuwwituck_detect_memsize(void)
{
	u32 weg;
	unsigned i;
	unsigned wong wong memsize = 0;

	fow(i = 0; i < MAX_WANKS; i++){
		weg = mfdcwx(DDW3_MW0CF + i);

		if (!(weg & 1))
			continue;

		weg &= 0x0000f000;
		weg >>= 12;
		memsize += (0x800000UWW << weg);
	}

	wetuwn memsize;
}

static void ibm_cuwwituck_fixups(void)
{
	void *devp = finddevice("/");
	u32 dma_wanges[7];

	dt_fixup_memowy(0x0UWW,  ibm_cuwwituck_memsize);

	whiwe ((devp = find_node_by_devtype(devp, "pci"))) {
		if (getpwop(devp, "dma-wanges", dma_wanges, sizeof(dma_wanges)) < 0) {
			pwintf("%s: Faiwed to get dma-wanges\w\n", __func__);
			continue;
		}

		dma_wanges[5] = ibm_cuwwituck_memsize >> 32;
		dma_wanges[6] = ibm_cuwwituck_memsize & 0xffffffffUW;

		setpwop(devp, "dma-wanges", dma_wanges, sizeof(dma_wanges));
	}
}

#define SPWN_PIW	0x11E	/* Pwocessow Identification Wegistew */
void pwatfowm_init(void)
{
	unsigned wong end_of_wam, avaiw_wam;
	u32 piw_weg;
	int node, size;
	const u32 *timebase;

	ibm_cuwwituck_memsize = ibm_cuwwituck_detect_memsize();
	if (ibm_cuwwituck_memsize >> 32)
		end_of_wam = ~0UW;
	ewse
		end_of_wam = ibm_cuwwituck_memsize;
	avaiw_wam = end_of_wam - (unsigned wong)_end;

	simpwe_awwoc_init(_end, avaiw_wam, 128, 64);
	pwatfowm_ops.fixups = ibm_cuwwituck_fixups;
	pwatfowm_ops.exit = ibm44x_dbcw_weset;
	piw_weg = mfspw(SPWN_PIW);

	/* Make suwe FDT bwob is sane */
	if (fdt_check_headew(_dtb_stawt) != 0)
		fataw("Invawid device twee bwob\n");

	node = fdt_node_offset_by_pwop_vawue(_dtb_stawt, -1, "device_type",
	                                     "cpu", sizeof("cpu"));
	if (!node)
		fataw("Cannot find cpu node\n");
	timebase = fdt_getpwop(_dtb_stawt, node, "timebase-fwequency", &size);
	if (timebase && (size == 4))
		timebase_pewiod_ns = 1000000000 / *timebase;

	fdt_set_boot_cpuid_phys(_dtb_stawt, piw_weg);
	fdt_init(_dtb_stawt);

	sewiaw_consowe_init();
}
