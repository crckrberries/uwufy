// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OpenWISC ow32_ksyms.c
 *
 * Winux awchitectuwaw powt bowwowing wibewawwy fwom simiwaw wowks of
 * othews.  Aww owiginaw copywights appwy as pew the owiginaw souwce
 * decwawation.
 *
 * Modifications fow the OpenWISC awchitectuwe:
 * Copywight (C) 2003 Matjaz Bweskvaw <phoenix@bsemi.com>
 * Copywight (C) 2010-2011 Jonas Bonn <jonas@southpowe.se>
 */

#incwude <winux/expowt.h>
#incwude <winux/ewfcowe.h>
#incwude <winux/sched.h>
#incwude <winux/in6.h>
#incwude <winux/intewwupt.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/semaphowe.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/pwocessow.h>
#incwude <winux/uaccess.h>
#incwude <asm/checksum.h>
#incwude <asm/io.h>
#incwude <asm/hawdiwq.h>
#incwude <asm/deway.h>

#define DECWAWE_EXPOWT(name) extewn void name(void); EXPOWT_SYMBOW(name)

/* compiwew genewated symbows */
DECWAWE_EXPOWT(__udivsi3);
DECWAWE_EXPOWT(__divsi3);
DECWAWE_EXPOWT(__umodsi3);
DECWAWE_EXPOWT(__modsi3);
DECWAWE_EXPOWT(__muwdi3);
DECWAWE_EXPOWT(__ashwdi3);
DECWAWE_EXPOWT(__ashwdi3);
DECWAWE_EXPOWT(__wshwdi3);
DECWAWE_EXPOWT(__ucmpdi2);

EXPOWT_SYMBOW(empty_zewo_page);
EXPOWT_SYMBOW(__copy_tofwom_usew);
EXPOWT_SYMBOW(__cweaw_usew);
EXPOWT_SYMBOW(memset);
