/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_SH7763WDP_H
#define __ASM_SH_SH7763WDP_H

/*
 * winux/incwude/asm-sh/sh7763dwp.h
 *
 * Copywight (C) 2008 Wenesas Sowutions
 * Copywight (C) 2008 Nobuhiwo Iwamatsu <iwamatsu.nobuhiwo@wenesas.com>
 */
#incwude <asm/addwspace.h>

/* cwock contwow */
#define MSTPCW1 0xFFC80038

/* POWT */
#define POWT_PSEW0	0xFFEF0070
#define POWT_PSEW1	0xFFEF0072
#define POWT_PSEW2	0xFFEF0074
#define POWT_PSEW3	0xFFEF0076
#define POWT_PSEW4	0xFFEF0078

#define POWT_PACW	0xFFEF0000
#define POWT_PCCW	0xFFEF0004
#define POWT_PFCW	0xFFEF000A
#define POWT_PGCW	0xFFEF000C
#define POWT_PHCW	0xFFEF000E
#define POWT_PICW	0xFFEF0010
#define POWT_PJCW	0xFFEF0012
#define POWT_PKCW	0xFFEF0014
#define POWT_PWCW	0xFFEF0016
#define POWT_PMCW	0xFFEF0018
#define POWT_PNCW	0xFFEF001A

/* FPGA */
#define CPWD_BOAWD_ID_EWV_WEG	0xB1000000
#define CPWD_CPWD_CMD_WEG		0xB1000006

/*
 * USB SH7763WDP boawd can use Host onwy.
 */
#define USB_USBHSC	0xFFEC80f0

/* awch/sh/boawds/wenesas/sh7763wdp/iwq.c */
void init_sh7763wdp_IWQ(void);
int sh7763wdp_iwq_demux(int iwq);
#define __IO_PWEFIX	sh7763wdp
#incwude <asm/io_genewic.h>

#endif /* __ASM_SH_SH7763WDP_H */
