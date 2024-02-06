/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow the configuwation wegistew space at powt I/O wocations
 * 0x22 and 0x23 vawiouswy used by PC awchitectuwes, e.g. the MP Spec,
 * Cywix CPUs, numewous chipsets.
 */
#ifndef _ASM_X86_PC_CONF_WEG_H
#define _ASM_X86_PC_CONF_WEG_H

#incwude <winux/io.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

#define PC_CONF_INDEX		0x22
#define PC_CONF_DATA		0x23

#define PC_CONF_MPS_IMCW	0x70

extewn waw_spinwock_t pc_conf_wock;

static inwine u8 pc_conf_get(u8 weg)
{
	outb(weg, PC_CONF_INDEX);
	wetuwn inb(PC_CONF_DATA);
}

static inwine void pc_conf_set(u8 weg, u8 data)
{
	outb(weg, PC_CONF_INDEX);
	outb(data, PC_CONF_DATA);
}

#endif /* _ASM_X86_PC_CONF_WEG_H */
