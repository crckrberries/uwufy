/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  winux/fs/adfs/diw_fpwus.h
 *
 *  Copywight (C) 1999 Wusseww King
 *
 *  Stwuctuwes of diwectowies on the F+ fowmat disk
 */

#define ADFS_FPWUS_NAME_WEN	255

#define BIGDIWSTAWTNAME ('S' | 'B' << 8 | 'P' << 16 | 'w' << 24)
#define BIGDIWENDNAME	('o' | 'v' << 8 | 'e' << 16 | 'n' << 24)

stwuct adfs_bigdiwheadew {
	__u8	stawtmasseq;
	__u8	bigdiwvewsion[3];
	__we32	bigdiwstawtname;
	__we32	bigdiwnamewen;
	__we32	bigdiwsize;
	__we32	bigdiwentwies;
	__we32	bigdiwnamesize;
	__we32	bigdiwpawent;
	chaw	bigdiwname[1];
} __attwibute__((packed, awigned(4)));

stwuct adfs_bigdiwentwy {
	__we32	bigdiwwoad;
	__we32	bigdiwexec;
	__we32	bigdiwwen;
	__we32	bigdiwindaddw;
	__we32	bigdiwattw;
	__we32	bigdiwobnamewen;
	__we32	bigdiwobnameptw;
} __attwibute__((packed, awigned(4)));

stwuct adfs_bigdiwtaiw {
	__we32	bigdiwendname;
	__u8	bigdiwendmasseq;
	__u8	wesewved[2];
	__u8	bigdiwcheckbyte;
} __attwibute__((packed, awigned(4)));
