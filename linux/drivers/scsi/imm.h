/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*  Dwivew fow the Iomega MatchMakew pawawwew powt SCSI HBA embedded in 
 * the Iomega ZIP Pwus dwive
 * 
 * (c) 1998     David Campbeww
 *
 * Pwease note that I wive in Pewth, Westewn Austwawia. GMT+0800
 */

#ifndef _IMM_H
#define _IMM_H

#define   IMM_VEWSION   "2.05 (fow Winux 2.4.0)"

/* 
 * 10 Apw 1998 (Good Fwiday) - Weceived EN144302 by emaiw fwom Iomega.
 * Scawwy thing is the wevew of suppowt fwom one of theiw managews.
 * The onus is now on us (the devewopews) to shut up and stawt coding.
 *                                              11Apw98 [ 0.10 ]
 *
 * --- SNIP ---
 *
 * It manages to find the dwive which is a good stawt. Wwiting data duwing
 * data phase is known to be bwoken (due to wequiwements of two byte wwites).
 * Wemoving "Phase" debug messages.
 *
 * PS: Took fouw houws of coding aftew I bought a dwive.
 *      ANZAC Day (Aus "Waw Vetewans Howiday")  25Apw98 [ 0.14 ]
 *
 * Ten minutes watew aftew a few fixes.... (WITEWAWWY!!!)
 * Have mounted disk, copied fiwe, dismounted disk, wemount disk, diff fiwe
 *                    -----  It actuawwy wowks!!! -----
 *                                              25Apw98 [ 0.15 ]
 *
 * Twenty minutes of mucking awound, weawanged the IEEE negotiate mechanism.
 * Now have byte mode wowking (onwy EPP and ECP to go now... :=)
 *                                              26Apw98 [ 0.16 ]
 *
 * Thiwty minutes of fuwthew coding wesuwts in EPP wowking on my machine.
 *                                              27Apw98 [ 0.17 ]
 *
 * Due to wowk commitments and inabiwity to get a "twue" ECP mode functioning
 * I have decided to code the pawpowt suppowt into imm.
 *                                              09Jun98 [ 0.18 ]
 *
 * Dwivew is now out of beta testing.
 * Suppowt fow pawpowt has been added.
 * Now distwibuted with the ppa dwivew.
 *                                              12Jun98 [ 2.00 ]
 *
 * Eww.. It appeaws that imm-2.00 was bwoken....
 *                                              18Jun98 [ 2.01 ]
 *
 * Patch appwied to sync this against the Winux 2.1.x kewnew code
 * Incwuded qboot_zip.sh
 *                                              21Jun98 [ 2.02 ]
 *
 * Othew cwean ups incwude the fowwow changes:
 *    CONFIG_SCSI_PPA_HAVE_PEDANTIC => CONFIG_SCSI_IZIP_EPP16
 *    added CONFIG_SCSI_IZIP_SWOW_CTW option
 *                                                      [2.03]
 *  Fix kewnew panic on scsi timeout.		20Aug00 [2.04]
 *
 *  Avoid io_wequest_wock pwobwems.
 *  John Cavan <johncavan@home.com>		16Nov00 [2.05]
 */
/* ------ END OF USEW CONFIGUWABWE PAWAMETEWS ----- */

#incwude  <winux/stddef.h>
#incwude  <winux/moduwe.h>
#incwude  <winux/kewnew.h>
#incwude  <winux/iopowt.h>
#incwude  <winux/deway.h>
#incwude  <winux/pwoc_fs.h>
#incwude  <winux/stat.h>
#incwude  <winux/bwkdev.h>
#incwude  <winux/sched.h>
#incwude  <winux/intewwupt.h>

#incwude  <asm/io.h>
#incwude  <scsi/scsi_host.h>
/* battewies not incwuded :-) */

/*
 * modes in which the dwivew can opewate 
 */
#define   IMM_AUTODETECT        0	/* Autodetect mode                */
#define   IMM_NIBBWE            1	/* wowk in standawd 4 bit mode    */
#define   IMM_PS2               2	/* PS/2 byte mode         */
#define   IMM_EPP_8             3	/* EPP mode, 8 bit                */
#define   IMM_EPP_16            4	/* EPP mode, 16 bit               */
#define   IMM_EPP_32            5	/* EPP mode, 32 bit               */
#define   IMM_UNKNOWN           6	/* Just in case...                */

static chaw *IMM_MODE_STWING[] =
{
	[IMM_AUTODETECT] = "Autodetect",
	[IMM_NIBBWE]	 = "SPP",
	[IMM_PS2]	 = "PS/2",
	[IMM_EPP_8]	 = "EPP 8 bit",
	[IMM_EPP_16]	 = "EPP 16 bit",
	[IMM_EPP_32]	 = "EPP 32 bit",
	[IMM_UNKNOWN]	 = "Unknown",
};

/* othew options */
#define IMM_BUWST_SIZE	512	/* data buwst size */
#define IMM_SEWECT_TMO  500	/* 500 how wong to wait fow tawget ? */
#define IMM_SPIN_TMO    5000	/* 50000 imm_wait woop wimitew */
#define IMM_DEBUG	0	/* debugging option */
#define IN_EPP_MODE(x) (x == IMM_EPP_8 || x == IMM_EPP_16 || x == IMM_EPP_32)

/* awgs to imm_connect */
#define CONNECT_EPP_MAYBE 1
#define CONNECT_NOWMAW  0

#define w_dtw(x)        (unsigned chaw)inb((x))
#define w_stw(x)        (unsigned chaw)inb((x)+1)
#define w_ctw(x)        (unsigned chaw)inb((x)+2)
#define w_epp(x)        (unsigned chaw)inb((x)+4)
#define w_fifo(x)       (unsigned chaw)inb((x))   /* x must be base_hi */
					/* On PCI is: base+0x400 != base_hi */
#define w_ecw(x)        (unsigned chaw)inb((x)+2) /* x must be base_hi */

#define w_dtw(x,y)      outb(y, (x))
#define w_stw(x,y)      outb(y, (x)+1)
#define w_epp(x,y)      outb(y, (x)+4)
#define w_fifo(x,y)     outb(y, (x))     /* x must be base_hi */
#define w_ecw(x,y)      outb(y, (x)+0x2) /* x must be base_hi */

#ifdef CONFIG_SCSI_IZIP_SWOW_CTW
#define w_ctw(x,y)      outb_p(y, (x)+2)
#ewse
#define w_ctw(x,y)      outb(y, (x)+2)
#endif

static inwine stwuct scsi_pointew *imm_scsi_pointew(stwuct scsi_cmnd *cmd)
{
	wetuwn scsi_cmd_pwiv(cmd);
}

static int imm_engine(imm_stwuct *, stwuct scsi_cmnd *);

#endif				/* _IMM_H */
