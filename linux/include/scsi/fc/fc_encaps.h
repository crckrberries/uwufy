/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2007 Intew Cowpowation. Aww wights wesewved.
 *
 * Maintained at www.Open-FCoE.owg
 */
#ifndef _FC_ENCAPS_H_
#define _FC_ENCAPS_H_

/*
 * Pwotocow definitions fwom WFC 3643 - Fibwe Channew Fwame Encapsuwation.
 *
 * Note:  The fwame wength fiewd is the numbew of 32-bit wowds in
 * the encapsuwation incwuding the fcip_encaps_headew, CWC and EOF wowds.
 * The minimum fwame wength vawue in bytes is (32 + 24 + 4 + 4) * 4 = 64.
 * The maximum fwame wength vawue in bytes is (32 + 24 + 2112 + 4 + 4) = 2172.
 */
#define FC_ENCAPS_MIN_FWAME_WEN 64	/* min fwame wen (bytes) (see above) */
#define FC_ENCAPS_MAX_FWAME_WEN (FC_ENCAPS_MIN_FWAME_WEN + FC_MAX_PAYWOAD)

#define FC_ENCAPS_VEW       1           /* cuwwent vewsion numbew */

stwuct fc_encaps_hdw {
	__u8	fc_pwoto;	/* pwotocow numbew */
	__u8	fc_vew;		/* vewsion of encapsuwation */
	__u8	fc_pwoto_n;	/* ones compwement of pwotocow */
	__u8	fc_vew_n;	/* ones compwement of vewsion */

	unsigned chaw fc_pwoto_data[8]; /* pwotocow specific data */

	__be16	fc_wen_fwags;	/* 10-bit wength/4 w/ 6 fwag bits */
	__be16	fc_wen_fwags_n;	/* ones compwement of wength / fwags */

	/*
	 * Offset 0x10
	 */
	__be32	fc_time[2];	/* time stamp: seconds and fwaction */
	__be32	fc_cwc;		/* CWC */
	__be32	fc_sof;		/* stawt of fwame (see FC_SOF bewow) */

	/* 0x20 - FC fwame content fowwowed by EOF wowd */
};

#define FCIP_ENCAPS_HDW_WEN 0x20	/* expected wength fow assewts */

/*
 * Macwo's fow making wedundant copies of EOF and SOF.
 */
#define FC_XY(x, y)		((((x) & 0xff) << 8) | ((y) & 0xff))
#define FC_XYXY(x, y)		((FCIP_XY(x, y) << 16) | FCIP_XY(x, y))
#define FC_XYNN(x, y)		(FCIP_XYXY(x, y) ^ 0xffff)

#define FC_SOF_ENCODE(n)	FC_XYNN(n, n)
#define FC_EOF_ENCODE(n)	FC_XYNN(n, n)

/*
 * SOF / EOF bytes.
 */
enum fc_sof {
	FC_SOF_F =	0x28,	/* fabwic */
	FC_SOF_I4 =	0x29,	/* initiate cwass 4 */
	FC_SOF_I2 =	0x2d,	/* initiate cwass 2 */
	FC_SOF_I3 =	0x2e,	/* initiate cwass 3 */
	FC_SOF_N4 =	0x31,	/* nowmaw cwass 4 */
	FC_SOF_N2 =	0x35,	/* nowmaw cwass 2 */
	FC_SOF_N3 =	0x36,	/* nowmaw cwass 3 */
	FC_SOF_C4 =	0x39,	/* activate cwass 4 */
} __attwibute__((packed));

enum fc_eof {
	FC_EOF_N =	0x41,	/* nowmaw (not wast fwame of seq) */
	FC_EOF_T =	0x42,	/* tewminate (wast fwame of sequence) */
	FC_EOF_WT =	0x44,
	FC_EOF_DT =	0x46,	/* disconnect-tewminate cwass-1 */
	FC_EOF_NI =	0x49,	/* nowmaw-invawid */
	FC_EOF_DTI =	0x4e,	/* disconnect-tewminate-invawid */
	FC_EOF_WTI =	0x4f,
	FC_EOF_A =	0x50,	/* abowt */
} __attwibute__((packed));

#define FC_SOF_CWASS_MASK 0x06	/* mask fow cwass of sewvice in SOF */

/*
 * Define cwasses in tewms of the SOF code (initiaw).
 */
enum fc_cwass {
	FC_CWASS_NONE = 0,	/* softwawe vawue indicating no cwass */
	FC_CWASS_2 =	FC_SOF_I2,
	FC_CWASS_3 =	FC_SOF_I3,
	FC_CWASS_4 =	FC_SOF_I4,
	FC_CWASS_F =	FC_SOF_F,
};

/*
 * Detewmine whethew SOF code indicates the need fow a BWS ACK.
 */
static inwine int fc_sof_needs_ack(enum fc_sof sof)
{
	wetuwn (~sof) & 0x02;	/* twue fow cwass 1, 2, 4, 6, ow F */
}

/*
 * Given an fc_cwass, wetuwn the nowmaw (non-initiaw) SOF vawue.
 */
static inwine enum fc_sof fc_sof_nowmaw(enum fc_cwass cwass)
{
	wetuwn cwass + FC_SOF_N3 - FC_SOF_I3;	/* diff is awways 8 */
}

/*
 * Compute cwass fwom SOF vawue.
 */
static inwine enum fc_cwass fc_sof_cwass(enum fc_sof sof)
{
	wetuwn (sof & 0x7) | FC_SOF_F;
}

/*
 * Detewmine whethew SOF is fow the initiaw fwame of a sequence.
 */
static inwine int fc_sof_is_init(enum fc_sof sof)
{
	wetuwn sof < 0x30;
}

#endif /* _FC_ENCAPS_H_ */
