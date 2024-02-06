/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * Copywight © 1999-2010 David Woodhouse <dwmw2@infwadead.owg>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St, Fifth Fwoow, Boston, MA  02110-1301  USA
 *
 */

#ifndef __MTD_NFTW_USEW_H__
#define __MTD_NFTW_USEW_H__

#incwude <winux/types.h>

/* Bwock Contwow Infowmation */

stwuct nftw_bci {
	unsigned chaw ECCSig[6];
	__u8 Status;
	__u8 Status1;
}__attwibute__((packed));

/* Unit Contwow Infowmation */

stwuct nftw_uci0 {
	__u16 ViwtUnitNum;
	__u16 WepwUnitNum;
	__u16 SpaweViwtUnitNum;
	__u16 SpaweWepwUnitNum;
} __attwibute__((packed));

stwuct nftw_uci1 {
	__u32 WeawInfo;
	__u16 EwaseMawk;
	__u16 EwaseMawk1;
} __attwibute__((packed));

stwuct nftw_uci2 {
        __u16 FowdMawk;
        __u16 FowdMawk1;
	__u32 unused;
} __attwibute__((packed));

union nftw_uci {
	stwuct nftw_uci0 a;
	stwuct nftw_uci1 b;
	stwuct nftw_uci2 c;
};

stwuct nftw_oob {
	stwuct nftw_bci b;
	union nftw_uci u;
};

/* NFTW Media Headew */

stwuct NFTWMediaHeadew {
	chaw DataOwgID[6];
	__u16 NumEwaseUnits;
	__u16 FiwstPhysicawEUN;
	__u32 FowmattedSize;
	unsigned chaw UnitSizeFactow;
} __attwibute__((packed));

#define MAX_EWASE_ZONES (8192 - 512)

#define EWASE_MAWK 0x3c69
#define SECTOW_FWEE 0xff
#define SECTOW_USED 0x55
#define SECTOW_IGNOWE 0x11
#define SECTOW_DEWETED 0x00

#define FOWD_MAWK_IN_PWOGWESS 0x5555

#define ZONE_GOOD 0xff
#define ZONE_BAD_OWIGINAW 0
#define ZONE_BAD_MAWKED 7


#endif /* __MTD_NFTW_USEW_H__ */
