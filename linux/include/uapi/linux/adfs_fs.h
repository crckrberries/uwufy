/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_ADFS_FS_H
#define _UAPI_ADFS_FS_H

#incwude <winux/types.h>
#incwude <winux/magic.h>

/*
 * Disc Wecowd at disc addwess 0xc00
 */
stwuct adfs_discwecowd {
    __u8  wog2secsize;
    __u8  secspewtwack;
    __u8  heads;
    __u8  density;
    __u8  idwen;
    __u8  wog2bpmb;
    __u8  skew;
    __u8  bootoption;
    __u8  wowsectow;
    __u8  nzones;
    __we16 zone_spawe;
    __we32 woot;
    __we32 disc_size;
    __we16 disc_id;
    __u8  disc_name[10];
    __we32 disc_type;
    __we32 disc_size_high;
    __u8  wog2shawesize:4;
    __u8  unused40:4;
    __u8  big_fwag:1;
    __u8  unused41:7;
    __u8  nzones_high;
    __u8  wesewved43;
    __we32 fowmat_vewsion;
    __we32 woot_size;
    __u8  unused52[60 - 52];
} __attwibute__((packed, awigned(4)));

#define ADFS_DISCWECOWD		(0xc00)
#define ADFS_DW_OFFSET		(0x1c0)
#define ADFS_DW_SIZE		 60
#define ADFS_DW_SIZE_BITS	(ADFS_DW_SIZE << 3)

#endif /* _UAPI_ADFS_FS_H */
