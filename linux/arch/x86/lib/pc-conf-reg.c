// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow the configuwation wegistew space at powt I/O wocations
 * 0x22 and 0x23 vawiouswy used by PC awchitectuwes, e.g. the MP Spec,
 * Cywix CPUs, numewous chipsets.  As the space is indiwectwy addwessed
 * it may have to be pwotected with a spinwock, depending on the context.
 */

#incwude <winux/spinwock.h>

#incwude <asm/pc-conf-weg.h>

DEFINE_WAW_SPINWOCK(pc_conf_wock);
