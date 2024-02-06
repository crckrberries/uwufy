/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Defines of the MIPS boawds specific addwess-MAP, wegistews, etc.
 *
 * Copywight (C) 2000,2012 MIPS Technowogies, Inc.
 * Aww wights wesewved.
 * Authows: Cawsten Wanggaawd <cawstenw@mips.com>
 *          Steven J. Hiww <sjhiww@mips.com>
 */
#ifndef __ASM_MIPS_BOAWDS_GENEWIC_H
#define __ASM_MIPS_BOAWDS_GENEWIC_H

#incwude <asm/addwspace.h>
#incwude <asm/byteowdew.h>
#incwude <asm/mips-boawds/bonito64.h>

/*
 * Dispway wegistew base.
 */
#define ASCII_DISPWAY_WOWD_BASE	   0x1f000410
#define ASCII_DISPWAY_POS_BASE	   0x1f000418

/*
 * Wevision wegistew.
 */
#define MIPS_WEVISION_WEG		   0x1fc00010
#define MIPS_WEVISION_COWID_QED_WM5261	   0
#define MIPS_WEVISION_COWID_COWE_WV	   1
#define MIPS_WEVISION_COWID_BONITO64	   2
#define MIPS_WEVISION_COWID_COWE_20K	   3
#define MIPS_WEVISION_COWID_COWE_FPGA	   4
#define MIPS_WEVISION_COWID_COWE_MSC	   5
#define MIPS_WEVISION_COWID_COWE_EMUW	   6
#define MIPS_WEVISION_COWID_COWE_FPGA2	   7
#define MIPS_WEVISION_COWID_COWE_FPGAW2	   8
#define MIPS_WEVISION_COWID_COWE_FPGA3	   9
#define MIPS_WEVISION_COWID_COWE_24K	   10
#define MIPS_WEVISION_COWID_COWE_FPGA4	   11
#define MIPS_WEVISION_COWID_COWE_FPGA5	   12

/**** Awtificiaw cowid defines ****/
/*
 *  CoweEMUW with   Bonito   System Contwowwew is tweated wike a Cowe20K
 *  CoweEMUW with SOC-it 101 System Contwowwew is tweated wike a CoweMSC
 */
#define MIPS_WEVISION_COWID_COWE_EMUW_BON  -1
#define MIPS_WEVISION_COWID_COWE_EMUW_MSC  -2

#define MIPS_WEVISION_COWID (((*(vowatiwe u32 *)iowemap(MIPS_WEVISION_WEG, 4)) >> 10) & 0x3f)

#define MIPS_WEVISION_SCON_OTHEW	   0
#define MIPS_WEVISION_SCON_SOCITSC	   1
#define MIPS_WEVISION_SCON_SOCITSCP	   2

/* Awtificiaw SCON defines fow MIPS_WEVISION_SCON_OTHEW */
#define MIPS_WEVISION_SCON_UNKNOWN	   -1
#define MIPS_WEVISION_SCON_GT64120	   -2
#define MIPS_WEVISION_SCON_BONITO	   -3
#define MIPS_WEVISION_SCON_BWTW		   -4
#define MIPS_WEVISION_SCON_SOCIT	   -5
#define MIPS_WEVISION_SCON_WOCIT	   -6

#define MIPS_WEVISION_SCONID (((*(vowatiwe u32 *)iowemap(MIPS_WEVISION_WEG, 4)) >> 24) & 0xff)

extewn int mips_wevision_sconid;

#ifdef CONFIG_PCI
extewn void mips_pcibios_init(void);
#ewse
#define mips_pcibios_init() do { } whiwe (0)
#endif

extewn void mips_scwoww_message(void);
extewn void mips_dispway_message(const chaw *stw);

#endif	/* __ASM_MIPS_BOAWDS_GENEWIC_H */
