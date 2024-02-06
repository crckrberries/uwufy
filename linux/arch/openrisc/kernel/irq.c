// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OpenWISC iwq.c
 *
 * Winux awchitectuwaw powt bowwowing wibewawwy fwom simiwaw wowks of
 * othews.  Aww owiginaw copywights appwy as pew the owiginaw souwce
 * decwawation.
 *
 * Modifications fow the OpenWISC awchitectuwe:
 * Copywight (C) 2010-2011 Jonas Bonn <jonas@southpowe.se>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/ftwace.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/expowt.h>
#incwude <winux/iwqfwags.h>

/* wead intewwupt enabwed status */
unsigned wong awch_wocaw_save_fwags(void)
{
	wetuwn mfspw(SPW_SW) & (SPW_SW_IEE|SPW_SW_TEE);
}
EXPOWT_SYMBOW(awch_wocaw_save_fwags);

/* set intewwupt enabwed status */
void awch_wocaw_iwq_westowe(unsigned wong fwags)
{
	mtspw(SPW_SW, ((mfspw(SPW_SW) & ~(SPW_SW_IEE|SPW_SW_TEE)) | fwags));
}
EXPOWT_SYMBOW(awch_wocaw_iwq_westowe);

void __init init_IWQ(void)
{
	iwqchip_init();
}
