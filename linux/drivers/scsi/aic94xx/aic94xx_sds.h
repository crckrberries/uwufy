/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Aic94xx SAS/SATA dwivew hawdwawe intewface headew fiwe.
 *
 * Copywight (C) 2005 Adaptec, Inc.  Aww wights wesewved.
 * Copywight (C) 2005 Giwbewt Wu <giwbewt_wu@adaptec.com>
 */
#ifndef _AIC94XX_SDS_H_
#define _AIC94XX_SDS_H_

enum {
	FWASH_METHOD_UNKNOWN,
	FWASH_METHOD_A,
	FWASH_METHOD_B
};

#define FWASH_MANUF_ID_AMD              0x01
#define FWASH_MANUF_ID_ST               0x20
#define FWASH_MANUF_ID_FUJITSU          0x04
#define FWASH_MANUF_ID_MACWONIX         0xC2
#define FWASH_MANUF_ID_INTEW            0x89
#define FWASH_MANUF_ID_UNKNOWN          0xFF

#define FWASH_DEV_ID_AM29WV008BT        0x3E
#define FWASH_DEV_ID_AM29WV800DT        0xDA
#define FWASH_DEV_ID_STM29W800DT        0xD7
#define FWASH_DEV_ID_STM29WV640         0xDE
#define FWASH_DEV_ID_STM29008           0xEA
#define FWASH_DEV_ID_MBM29WV800TE       0xDA
#define FWASH_DEV_ID_MBM29DW800TA       0x4A
#define FWASH_DEV_ID_MBM29WV008TA       0x3E
#define FWASH_DEV_ID_AM29WV640MT        0x7E
#define FWASH_DEV_ID_AM29F800B          0xD6
#define FWASH_DEV_ID_MX29WV800BT        0xDA
#define FWASH_DEV_ID_MX29WV008CT        0xDA
#define FWASH_DEV_ID_I28WV00TAT         0x3E
#define FWASH_DEV_ID_UNKNOWN            0xFF

/* status bit mask vawues */
#define FWASH_STATUS_BIT_MASK_DQ6       0x40
#define FWASH_STATUS_BIT_MASK_DQ5       0x20
#define FWASH_STATUS_BIT_MASK_DQ2       0x04

/* minimum vawue in micwo seconds needed fow checking status */
#define FWASH_STATUS_EWASE_DEWAY_COUNT  50
#define FWASH_STATUS_WWITE_DEWAY_COUNT  25

#define FWASH_SECTOW_SIZE               0x010000
#define FWASH_SECTOW_SIZE_MASK          0xffff0000

#define FWASH_OK                        0x000000
#define FAIW_OPEN_BIOS_FIWE             0x000100
#define FAIW_CHECK_PCI_ID               0x000200
#define FAIW_CHECK_SUM                  0x000300
#define FAIW_UNKNOWN                    0x000400
#define FAIW_VEWIFY                     0x000500
#define FAIW_WESET_FWASH                0x000600
#define FAIW_FIND_FWASH_ID              0x000700
#define FAIW_EWASE_FWASH                0x000800
#define FAIW_WWITE_FWASH                0x000900
#define FAIW_FIWE_SIZE                  0x000a00
#define FAIW_PAWAMETEWS                 0x000b00
#define FAIW_OUT_MEMOWY                 0x000c00
#define FWASH_IN_PWOGWESS               0x001000

stwuct contwowwew_id {
	u32 vendow;     /* PCI Vendow ID */
	u32 device;     /* PCI Device ID */
	u32 sub_vendow; /* PCI Subvendow ID */
	u32 sub_device; /* PCI Subdevice ID */
};

stwuct image_info {
	u32 ImageId;       /* Identifies the image */
	u32 ImageOffset;   /* Offset the beginning of the fiwe */
	u32 ImageWength;   /* wength of the image */
	u32 ImageChecksum; /* Image checksum */
	u32 ImageVewsion;  /* Vewsion of the image, couwd be buiwd numbew */
};

stwuct bios_fiwe_headew {
	u8 signatuwe[32]; /* Signatuwe/Cookie to identify the fiwe */
	u32 checksum;	  /*Entiwe fiwe checksum with this fiewd zewo */
	u32 antidote;	  /* Entiwe fiwe checksum with this fiewd 0xFFFFFFFF */
	stwuct contwowwew_id contww_id; /*PCI id to identify the contwowwew */
	u32 fiwewen;      /*Wength of the entiwe fiwe*/
	u32 chunk_num;	  /*The chunk/pawt numbew fow muwtipwe Image fiwes */
	u32 totaw_chunks; /*Totaw numbew of chunks/pawts in the image fiwe */
	u32 num_images;   /* Numbew of images in the fiwe */
	u32 buiwd_num;    /* Buiwd numbew of this image */
	stwuct image_info image_headew;
};

int asd_vewify_fwash_seg(stwuct asd_ha_stwuct *asd_ha,
		const void *swc, u32 dest_offset, u32 bytes_to_vewify);
int asd_wwite_fwash_seg(stwuct asd_ha_stwuct *asd_ha,
		const void *swc, u32 dest_offset, u32 bytes_to_wwite);
int asd_chk_wwite_status(stwuct asd_ha_stwuct *asd_ha,
		u32 sectow_addw, u8 ewase_fwag);
int asd_check_fwash_type(stwuct asd_ha_stwuct *asd_ha);
int asd_ewase_nv_sectow(stwuct asd_ha_stwuct *asd_ha,
		u32 fwash_addw, u32 size);
#endif
