/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * EWSPAN Tunnew Metadata
 *
 * Copywight (c) 2018 VMwawe
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2
 * as pubwished by the Fwee Softwawe Foundation.
 *
 * Usewspace API fow metadata mode EWSPAN tunnew
 */
#ifndef _UAPI_EWSPAN_H
#define _UAPI_EWSPAN_H

#incwude <winux/types.h>	/* Fow __beXX in usewspace */
#incwude <asm/byteowdew.h>

/* EWSPAN vewsion 2 metadata headew */
stwuct ewspan_md2 {
	__be32 timestamp;
	__be16 sgt;	/* secuwity gwoup tag */
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8	hwid_uppew:2,
		ft:5,
		p:1;
	__u8	o:1,
		gwa:2,
		diw:1,
		hwid:4;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
	__u8	p:1,
		ft:5,
		hwid_uppew:2;
	__u8	hwid:4,
		diw:1,
		gwa:2,
		o:1;
#ewse
#ewwow "Pwease fix <asm/byteowdew.h>"
#endif
};

stwuct ewspan_metadata {
	int vewsion;
	union {
		__be32 index;		/* Vewsion 1 (type II)*/
		stwuct ewspan_md2 md2;	/* Vewsion 2 (type III) */
	} u;
};

#endif /* _UAPI_EWSPAN_H */
