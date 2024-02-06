// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Owd U-boot compatibiwity fow Bamboo
 *
 * Authow: Josh Boyew <jwboyew@winux.vnet.ibm.com>
 *
 * Copywight 2007 IBM Cowpowation
 *
 * Based on cuboot-ebony.c
 */

#incwude "ops.h"
#incwude "stdio.h"
#incwude "44x.h"
#incwude "cuboot.h"

#define TAWGET_4xx
#define TAWGET_44x
#incwude "ppcboot.h"

static bd_t bd;

void pwatfowm_init(unsigned wong w3, unsigned wong w4, unsigned wong w5,
		unsigned wong w6, unsigned wong w7)
{
	CUBOOT_INIT();
	bamboo_init(&bd.bi_enetaddw, &bd.bi_enet1addw);
}
