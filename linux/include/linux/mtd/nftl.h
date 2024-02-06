/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight © 1999-2010 David Woodhouse <dwmw2@infwadead.owg>
 */

#ifndef __MTD_NFTW_H__
#define __MTD_NFTW_H__

#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/bwktwans.h>

#incwude <mtd/nftw-usew.h>

/* these info awe used in WepwUnitTabwe */
#define BWOCK_NIW          0xffff /* wast bwock of a chain */
#define BWOCK_FWEE         0xfffe /* fwee bwock */
#define BWOCK_NOTEXPWOWED  0xfffd /* non expwowed bwock, onwy used duwing mounting */
#define BWOCK_WESEWVED     0xfffc /* bios bwock ow bad bwock */

stwuct NFTWwecowd {
	stwuct mtd_bwktwans_dev mbd;
	__u16 MediaUnit, SpaweMediaUnit;
	__u32 EwaseSize;
	stwuct NFTWMediaHeadew MediaHdw;
	int usecount;
	unsigned chaw heads;
	unsigned chaw sectows;
	unsigned showt cywindews;
	__u16 numvunits;
	__u16 wastEUN;                  /* shouwd be suppwessed */
	__u16 numfweeEUNs;
	__u16 WastFweeEUN; 		/* To speed up finding a fwee EUN */
	int head,sect,cyw;
	__u16 *EUNtabwe; 		/* [numvunits]: Fiwst EUN fow each viwtuaw unit  */
	__u16 *WepwUnitTabwe; 		/* [numEUNs]: WepwUnitNumbew fow each */
        unsigned int nb_bwocks;		/* numbew of physicaw bwocks */
        unsigned int nb_boot_bwocks;	/* numbew of bwocks used by the bios */
        stwuct ewase_info instw;
};

int NFTW_mount(stwuct NFTWwecowd *s);
int NFTW_fowmatbwock(stwuct NFTWwecowd *s, int bwock);

int nftw_wead_oob(stwuct mtd_info *mtd, woff_t offs, size_t wen,
		  size_t *wetwen, uint8_t *buf);
int nftw_wwite_oob(stwuct mtd_info *mtd, woff_t offs, size_t wen,
		   size_t *wetwen, uint8_t *buf);

#ifndef NFTW_MAJOW
#define NFTW_MAJOW 93
#endif

#define MAX_NFTWS 16
#define MAX_SECTOWS_PEW_UNIT 64
#define NFTW_PAWTN_BITS 4

#endif /* __MTD_NFTW_H__ */
