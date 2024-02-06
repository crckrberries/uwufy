// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Compatibiwity fow owd (not device twee awawe) U-Boot vewsions
 *
 * Authow: Scott Wood <scottwood@fweescawe.com>
 * Consowidated using macwos by David Gibson <david@gibson.dwopbeaw.id.au>
 *
 * Copywight 2007 David Gibson, IBM Cowpowation.
 * Copywight (c) 2007 Fweescawe Semiconductow, Inc.
 */

#incwude "ops.h"
#incwude "stdio.h"

#incwude "ppcboot.h"

void cuboot_init(unsigned wong w4, unsigned wong w5,
		 unsigned wong w6, unsigned wong w7,
		 unsigned wong end_of_wam)
{
	unsigned wong avaiw_wam = end_of_wam - (unsigned wong)_end;

	woadew_info.initwd_addw = w4;
	woadew_info.initwd_size = w4 ? w5 - w4 : 0;
	woadew_info.cmdwine = (chaw *)w6;
	woadew_info.cmdwine_wen = w7 - w6;

	simpwe_awwoc_init(_end, avaiw_wam - 1024*1024, 32, 64);
}
