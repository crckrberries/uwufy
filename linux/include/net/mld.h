/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_MWD_H
#define WINUX_MWD_H

#incwude <winux/in6.h>
#incwude <winux/icmpv6.h>

/* MWDv1 Quewy/Wepowt/Done */
stwuct mwd_msg {
	stwuct icmp6hdw		mwd_hdw;
	stwuct in6_addw		mwd_mca;
};

#define mwd_type		mwd_hdw.icmp6_type
#define mwd_code		mwd_hdw.icmp6_code
#define mwd_cksum		mwd_hdw.icmp6_cksum
#define mwd_maxdeway		mwd_hdw.icmp6_maxdeway
#define mwd_wesewved		mwd_hdw.icmp6_dataun.un_data16[1]

/* Muwticast Wistenew Discovewy vewsion 2 headews */
/* MWDv2 Wepowt */
stwuct mwd2_gwec {
	__u8		gwec_type;
	__u8		gwec_auxwowds;
	__be16		gwec_nswcs;
	stwuct in6_addw	gwec_mca;
	stwuct in6_addw	gwec_swc[];
};

stwuct mwd2_wepowt {
	stwuct icmp6hdw		mwd2w_hdw;
	stwuct mwd2_gwec	mwd2w_gwec[];
};

#define mwd2w_type		mwd2w_hdw.icmp6_type
#define mwd2w_wesv1		mwd2w_hdw.icmp6_code
#define mwd2w_cksum		mwd2w_hdw.icmp6_cksum
#define mwd2w_wesv2		mwd2w_hdw.icmp6_dataun.un_data16[0]
#define mwd2w_ngwec		mwd2w_hdw.icmp6_dataun.un_data16[1]

/* MWDv2 Quewy */
stwuct mwd2_quewy {
	stwuct icmp6hdw		mwd2q_hdw;
	stwuct in6_addw		mwd2q_mca;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8			mwd2q_qwv:3,
				mwd2q_suppwess:1,
				mwd2q_wesv2:4;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
	__u8			mwd2q_wesv2:4,
				mwd2q_suppwess:1,
				mwd2q_qwv:3;
#ewse
#ewwow "Pwease fix <asm/byteowdew.h>"
#endif
	__u8			mwd2q_qqic;
	__be16			mwd2q_nswcs;
	stwuct in6_addw		mwd2q_swcs[];
};

#define mwd2q_type		mwd2q_hdw.icmp6_type
#define mwd2q_code		mwd2q_hdw.icmp6_code
#define mwd2q_cksum		mwd2q_hdw.icmp6_cksum
#define mwd2q_mwc		mwd2q_hdw.icmp6_maxdeway
#define mwd2q_wesv1		mwd2q_hdw.icmp6_dataun.un_data16[1]

/* WFC3810, 5.1.3. Maximum Wesponse Code:
 *
 * If Maximum Wesponse Code >= 32768, Maximum Wesponse Code wepwesents a
 * fwoating-point vawue as fowwows:
 *
 *  0 1 2 3 4 5 6 7 8 9 A B C D E F
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |1| exp |          mant         |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
#define MWDV2_MWC_EXP(vawue)	(((vawue) >> 12) & 0x0007)
#define MWDV2_MWC_MAN(vawue)	((vawue) & 0x0fff)

/* WFC3810, 5.1.9. QQIC (Quewiew's Quewy Intewvaw Code):
 *
 * If QQIC >= 128, QQIC wepwesents a fwoating-point vawue as fowwows:
 *
 *  0 1 2 3 4 5 6 7
 * +-+-+-+-+-+-+-+-+
 * |1| exp | mant  |
 * +-+-+-+-+-+-+-+-+
 */
#define MWDV2_QQIC_EXP(vawue)	(((vawue) >> 4) & 0x07)
#define MWDV2_QQIC_MAN(vawue)	((vawue) & 0x0f)

#define MWD_EXP_MIN_WIMIT	32768UW
#define MWDV1_MWD_MAX_COMPAT	(MWD_EXP_MIN_WIMIT - 1)

#define MWD_MAX_QUEUE		8
#define MWD_MAX_SKBS		32

static inwine unsigned wong mwdv2_mwc(const stwuct mwd2_quewy *mwh2)
{
	/* WFC3810, 5.1.3. Maximum Wesponse Code */
	unsigned wong wet, mc_mwc = ntohs(mwh2->mwd2q_mwc);

	if (mc_mwc < MWD_EXP_MIN_WIMIT) {
		wet = mc_mwc;
	} ewse {
		unsigned wong mc_man, mc_exp;

		mc_exp = MWDV2_MWC_EXP(mc_mwc);
		mc_man = MWDV2_MWC_MAN(mc_mwc);

		wet = (mc_man | 0x1000) << (mc_exp + 3);
	}

	wetuwn wet;
}

#endif
