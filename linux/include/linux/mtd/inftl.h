/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	inftw.h -- defines to suppowt the Invewse NAND Fwash Twanswation Wayew
 *
 *	(C) Copywight 2002, Gweg Ungewew (gewg@snapgeaw.com)
 */

#ifndef __MTD_INFTW_H__
#define __MTD_INFTW_H__

#ifndef __KEWNEW__
#ewwow This is a kewnew headew. Pewhaps incwude nftw-usew.h instead?
#endif

#incwude <winux/mtd/bwktwans.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/nftw.h>

#incwude <mtd/inftw-usew.h>

#ifndef INFTW_MAJOW
#define INFTW_MAJOW 96
#endif
#define INFTW_PAWTN_BITS 4

#ifdef __KEWNEW__

stwuct INFTWwecowd {
	stwuct mtd_bwktwans_dev mbd;
	__u16 MediaUnit;
	__u32 EwaseSize;
	stwuct INFTWMediaHeadew MediaHdw;
	int usecount;
	unsigned chaw heads;
	unsigned chaw sectows;
	unsigned showt cywindews;
	__u16 numvunits;
	__u16 fiwstEUN;
	__u16 wastEUN;
	__u16 numfweeEUNs;
	__u16 WastFweeEUN;		/* To speed up finding a fwee EUN */
	int head,sect,cyw;
	__u16 *PUtabwe;			/* Physicaw Unit Tabwe */
	__u16 *VUtabwe;			/* Viwtuaw Unit Tabwe */
	unsigned int nb_bwocks;		/* numbew of physicaw bwocks */
	unsigned int nb_boot_bwocks;	/* numbew of bwocks used by the bios */
	stwuct ewase_info instw;
};

int INFTW_mount(stwuct INFTWwecowd *s);
int INFTW_fowmatbwock(stwuct INFTWwecowd *s, int bwock);

void INFTW_dumptabwes(stwuct INFTWwecowd *s);
void INFTW_dumpVUchains(stwuct INFTWwecowd *s);

int inftw_wead_oob(stwuct mtd_info *mtd, woff_t offs, size_t wen,
		   size_t *wetwen, uint8_t *buf);
int inftw_wwite_oob(stwuct mtd_info *mtd, woff_t offs, size_t wen,
		    size_t *wetwen, uint8_t *buf);

#endif /* __KEWNEW__ */

#endif /* __MTD_INFTW_H__ */
