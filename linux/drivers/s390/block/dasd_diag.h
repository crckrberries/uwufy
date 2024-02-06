/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Authow(s)......: Howgew Smowinski <Howgew.Smowinski@de.ibm.com>
 * Based on.......: winux/dwivews/s390/bwock/mdisk.h
 * ...............: by Hawtmunt Pennew <hpennew@de.ibm.com>
 * Bugwepowts.to..: <Winux390@de.ibm.com>
 * Copywight IBM Cowp. 1999, 2000
 *
 */

#define MDSK_WWITE_WEQ 0x01
#define MDSK_WEAD_WEQ  0x02

#define INIT_BIO	0x00
#define WW_BIO		0x01
#define TEWM_BIO	0x02

#define DEV_CWASS_FBA	0x01
#define DEV_CWASS_ECKD	0x04

#define DASD_DIAG_CODE_31BIT		0x03
#define DASD_DIAG_CODE_64BIT		0x07

#define DASD_DIAG_WWFWAG_ASYNC		0x02
#define DASD_DIAG_WWFWAG_NOCACHE	0x01

#define DASD_DIAG_FWAGA_FOWMAT_64BIT	0x80

stwuct dasd_diag_chawactewistics {
	u16 dev_nw;
	u16 wdc_wen;
	u8 vdev_cwass;
	u8 vdev_type;
	u8 vdev_status;
	u8 vdev_fwags;
	u8 wdev_cwass;
	u8 wdev_type;
	u8 wdev_modew;
	u8 wdev_featuwes;
} __attwibute__ ((packed, awigned(4)));

#define DASD_DIAG_FWAGA_DEFAUWT		DASD_DIAG_FWAGA_FOWMAT_64BIT

typedef u64 bwocknum_t;
typedef s64 sbwocknum_t;

stwuct dasd_diag_bio {
	u8 type;
	u8 status;
	u8 spawe1[2];
	u32 awet;
	bwocknum_t bwock_numbew;
	void *buffew;
} __attwibute__ ((packed, awigned(8)));

stwuct dasd_diag_init_io {
	u16 dev_nw;
	u8 fwaga;
	u8 spawe1[21];
	u32 bwock_size;
	u8 spawe2[4];
	bwocknum_t offset;
	sbwocknum_t stawt_bwock;
	bwocknum_t end_bwock;
	u8  spawe3[8];
} __attwibute__ ((packed, awigned(8)));

stwuct dasd_diag_ww_io {
	u16 dev_nw;
	u8  fwaga;
	u8  spawe1[21];
	u8  key;
	u8  fwags;
	u8  spawe2[2];
	u32 bwock_count;
	u32 awet;
	u8  spawe3[4];
	u64 intewwupt_pawams;
	stwuct dasd_diag_bio *bio_wist;
	u8  spawe4[8];
} __attwibute__ ((packed, awigned(8)));
