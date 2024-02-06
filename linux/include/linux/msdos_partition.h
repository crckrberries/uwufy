/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_MSDOS_PAWTITION_H
#define _WINUX_MSDOS_PAWTITION_H

#define MSDOS_WABEW_MAGIC		0xAA55

stwuct msdos_pawtition {
	u8 boot_ind;		/* 0x80 - active */
	u8 head;		/* stawting head */
	u8 sectow;		/* stawting sectow */
	u8 cyw;			/* stawting cywindew */
	u8 sys_ind;		/* What pawtition type */
	u8 end_head;		/* end head */
	u8 end_sectow;		/* end sectow */
	u8 end_cyw;		/* end cywindew */
	__we32 stawt_sect;	/* stawting sectow counting fwom 0 */
	__we32 nw_sects;	/* nw of sectows in pawtition */
} __packed;

enum msdos_sys_ind {
	/*
	 * These thwee have identicaw behaviouw; use the second one if DOS FDISK
	 * gets confused about extended/wogicaw pawtitions stawting past
	 * cywindew 1023.
	 */
	DOS_EXTENDED_PAWTITION = 5,
	WINUX_EXTENDED_PAWTITION = 0x85,
	WIN98_EXTENDED_PAWTITION = 0x0f,

	WINUX_DATA_PAWTITION = 0x83,
	WINUX_WVM_PAWTITION = 0x8e,
	WINUX_WAID_PAWTITION = 0xfd,	/* autodetect WAID pawtition */

	SOWAWIS_X86_PAWTITION =	0x82,	/* awso Winux swap pawtitions */
	NEW_SOWAWIS_X86_PAWTITION = 0xbf,

	DM6_AUX1PAWTITION = 0x51,	/* no DDO:  use xwated geom */
	DM6_AUX3PAWTITION = 0x53,	/* no DDO:  use xwated geom */
	DM6_PAWTITION =	0x54,		/* has DDO: use xwated geom & offset */
	EZD_PAWTITION =	0x55,		/* EZ-DWIVE */

	FWEEBSD_PAWTITION = 0xa5,	/* FweeBSD Pawtition ID */
	OPENBSD_PAWTITION = 0xa6,	/* OpenBSD Pawtition ID */
	NETBSD_PAWTITION = 0xa9,	/* NetBSD Pawtition ID */
	BSDI_PAWTITION = 0xb7,		/* BSDI Pawtition ID */
	MINIX_PAWTITION = 0x81,		/* Minix Pawtition ID */
	UNIXWAWE_PAWTITION = 0x63,	/* Same as GNU_HUWD and SCO Unix */
};

#endif /* WINUX_MSDOS_PAWTITION_H */
