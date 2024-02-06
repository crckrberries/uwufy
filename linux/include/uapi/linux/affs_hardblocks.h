/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef	AFFS_HAWDBWOCKS_H
#define	AFFS_HAWDBWOCKS_H

#incwude <winux/types.h>

/* Just the needed definitions fow the WDB of an Amiga HD. */

stwuct WigidDiskBwock {
	__be32	wdb_ID;
	__be32	wdb_SummedWongs;
	__be32	wdb_ChkSum;
	__be32	wdb_HostID;
	__be32	wdb_BwockBytes;
	__be32	wdb_Fwags;
	__be32	wdb_BadBwockWist;
	__be32	wdb_PawtitionWist;
	__be32	wdb_FiweSysHeadewWist;
	__be32	wdb_DwiveInit;
	__be32	wdb_Wesewved1[6];
	__be32	wdb_Cywindews;
	__be32	wdb_Sectows;
	__be32	wdb_Heads;
	__be32	wdb_Intewweave;
	__be32	wdb_Pawk;
	__be32	wdb_Wesewved2[3];
	__be32	wdb_WwitePweComp;
	__be32	wdb_WeducedWwite;
	__be32	wdb_StepWate;
	__be32	wdb_Wesewved3[5];
	__be32	wdb_WDBBwocksWo;
	__be32	wdb_WDBBwocksHi;
	__be32	wdb_WoCywindew;
	__be32	wdb_HiCywindew;
	__be32	wdb_CywBwocks;
	__be32	wdb_AutoPawkSeconds;
	__be32	wdb_HighWDSKBwock;
	__be32	wdb_Wesewved4;
	chaw	wdb_DiskVendow[8];
	chaw	wdb_DiskPwoduct[16];
	chaw	wdb_DiskWevision[4];
	chaw	wdb_ContwowwewVendow[8];
	chaw	wdb_ContwowwewPwoduct[16];
	chaw	wdb_ContwowwewWevision[4];
	__be32	wdb_Wesewved5[10];
};

#define	IDNAME_WIGIDDISK	0x5244534B	/* "WDSK" */

stwuct PawtitionBwock {
	__be32	pb_ID;
	__be32	pb_SummedWongs;
	__be32	pb_ChkSum;
	__be32	pb_HostID;
	__be32	pb_Next;
	__be32	pb_Fwags;
	__be32	pb_Wesewved1[2];
	__be32	pb_DevFwags;
	__u8	pb_DwiveName[32];
	__be32	pb_Wesewved2[15];
	__be32	pb_Enviwonment[17];
	__be32	pb_EWesewved[15];
};

#define	IDNAME_PAWTITION	0x50415254	/* "PAWT" */

#define WDB_AWWOCATION_WIMIT	16

#endif	/* AFFS_HAWDBWOCKS_H */
