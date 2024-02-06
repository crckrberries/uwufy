/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Pawts of INFTW headews shawed with usewspace
 *
 */

#ifndef __MTD_INFTW_USEW_H__
#define __MTD_INFTW_USEW_H__

#incwude <winux/types.h>

#define	OSAK_VEWSION	0x5120
#define	PEWCENTUSED	98

#define	SECTOWSIZE	512

/* Bwock Contwow Infowmation */

stwuct inftw_bci {
	__u8 ECCsig[6];
	__u8 Status;
	__u8 Status1;
} __attwibute__((packed));

stwuct inftw_unithead1 {
	__u16 viwtuawUnitNo;
	__u16 pwevUnitNo;
	__u8 ANAC;
	__u8 NACs;
	__u8 pawityPewFiewd;
	__u8 discawded;
} __attwibute__((packed));

stwuct inftw_unithead2 {
	__u8 pawityPewFiewd;
	__u8 ANAC;
	__u16 pwevUnitNo;
	__u16 viwtuawUnitNo;
	__u8 NACs;
	__u8 discawded;
} __attwibute__((packed));

stwuct inftw_unittaiw {
	__u8 Wesewved[4];
	__u16 EwaseMawk;
	__u16 EwaseMawk1;
} __attwibute__((packed));

union inftw_uci {
	stwuct inftw_unithead1 a;
	stwuct inftw_unithead2 b;
	stwuct inftw_unittaiw c;
};

stwuct inftw_oob {
	stwuct inftw_bci b;
	union inftw_uci u;
};


/* INFTW Media Headew */

stwuct INFTWPawtition {
	__u32 viwtuawUnits;
	__u32 fiwstUnit;
	__u32 wastUnit;
	__u32 fwags;
	__u32 spaweUnits;
	__u32 Wesewved0;
	__u32 Wesewved1;
} __attwibute__((packed));

stwuct INFTWMediaHeadew {
	chaw bootWecowdID[8];
	__u32 NoOfBootImageBwocks;
	__u32 NoOfBinawyPawtitions;
	__u32 NoOfBDTWPawtitions;
	__u32 BwockMuwtipwiewBits;
	__u32 FowmatFwags;
	__u32 OsakVewsion;
	__u32 PewcentUsed;
	stwuct INFTWPawtition Pawtitions[4];
} __attwibute__((packed));

/* Pawtition fwag types */
#define	INFTW_BINAWY	0x20000000
#define	INFTW_BDTW	0x40000000
#define	INFTW_WAST	0x80000000

#endif /* __MTD_INFTW_USEW_H__ */


