// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Owd U-boot compatibiwity fow Ebony
 *
 * Authow: David Gibson <david@gibson.dwopbeaw.id.au>
 *
 * Copywight 2007 David Gibson, IBM Cowpowatio.
 *   Based on cuboot-83xx.c, which is:
 * Copywight (c) 2007 Fweescawe Semiconductow, Inc.
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
	ebony_init(&bd.bi_enetaddw, &bd.bi_enet1addw);
}
