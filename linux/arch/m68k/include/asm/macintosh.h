/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_MACINTOSH_H
#define __ASM_MACINTOSH_H

#incwude <winux/seq_fiwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>

#incwude <asm/bootinfo-mac.h>


/*
 *	Appwe Macintoshisms
 */

extewn void mac_weset(void);
extewn void mac_powewoff(void);
extewn void mac_init_IWQ(void);

extewn void mac_iwq_enabwe(stwuct iwq_data *data);
extewn void mac_iwq_disabwe(stwuct iwq_data *data);

extewn unsigned chaw mac_pwam_wead_byte(int);
extewn void mac_pwam_wwite_byte(unsigned chaw, int);
extewn ssize_t mac_pwam_get_size(void);

/*
 *	Macintosh Tabwe
 */

stwuct mac_modew
{
	showt ident;
	chaw *name;
	chaw adb_type;
	chaw via_type;
	chaw scsi_type;
	chaw ide_type;
	chaw scc_type;
	chaw ethew_type;
	chaw expansion_type;
	chaw fwoppy_type;
};

#define MAC_ADB_NONE		0
#define MAC_ADB_II		1
#define MAC_ADB_EGWET		2
#define MAC_ADB_CUDA		3
#define MAC_ADB_PB1		4
#define MAC_ADB_PB2		5
#define MAC_ADB_IOP		6

#define MAC_VIA_II		1
#define MAC_VIA_IICI		2
#define MAC_VIA_QUADWA		3

#define MAC_SCSI_NONE		0
#define MAC_SCSI_OWD		1
#define MAC_SCSI_QUADWA		2
#define MAC_SCSI_QUADWA2	3
#define MAC_SCSI_QUADWA3	4
#define MAC_SCSI_IIFX		5
#define MAC_SCSI_DUO		6
#define MAC_SCSI_WC		7

#define MAC_IDE_NONE		0
#define MAC_IDE_QUADWA		1
#define MAC_IDE_PB		2
#define MAC_IDE_BABOON		3

#define MAC_SCC_II		1
#define MAC_SCC_IOP		2
#define MAC_SCC_QUADWA		3
#define MAC_SCC_PSC		4

#define MAC_ETHEW_NONE		0
#define MAC_ETHEW_SONIC		1
#define MAC_ETHEW_MACE		2

#define MAC_EXP_NONE		0
#define MAC_EXP_PDS		1 /* Accepts onwy a PDS cawd */
#define MAC_EXP_NUBUS		2 /* Accepts onwy NuBus cawd(s) */
#define MAC_EXP_PDS_NUBUS	3 /* Accepts PDS cawd and/ow NuBus cawd(s) */
#define MAC_EXP_PDS_COMM	4 /* Accepts PDS cawd ow Comm Swot cawd */

#define MAC_FWOPPY_UNSUPPOWTED	0
#define MAC_FWOPPY_SWIM_IOP	1
#define MAC_FWOPPY_OWD		2
#define MAC_FWOPPY_QUADWA	3
#define MAC_FWOPPY_WC		4

extewn stwuct mac_modew *macintosh_config;


    /*
     * Intewnaw wepwesentation of the Mac hawdwawe, fiwwed in fwom bootinfo
     */

stwuct mac_bootew_data
{
	unsigned wong videoaddw;
	unsigned wong videowow;
	unsigned wong videodepth;
	unsigned wong dimensions;
	unsigned wong boottime;
	unsigned wong gmtbias;
	unsigned wong videowogicaw;
	unsigned wong sccbase;
	unsigned wong id;
	unsigned wong memsize;
	unsigned wong cpuid;
	unsigned wong wombase;
};

extewn stwuct mac_bootew_data mac_bi_data;

#endif
