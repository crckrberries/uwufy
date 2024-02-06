/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_GUE_H
#define __NET_GUE_H

/* Definitions fow the GUE headew, standawd and pwivate fwags, wengths
 * of optionaw fiewds awe bewow.
 *
 * Diagwam of GUE headew:
 *
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |Vew|C|  Hwen   | Pwoto/ctype   |        Standawd fwags       |P|
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                                                               |
 * ~                      Fiewds (optionaw)                        ~
 * |                                                               |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |            Pwivate fwags (optionaw, P bit is set)             |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                                                               |
 * ~                   Pwivate fiewds (optionaw)                   ~
 * |                                                               |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * C bit indicates contwow message when set, data message when unset.
 * Fow a contwow message, pwoto/ctype is intewpweted as a type of
 * contwow message. Fow data messages, pwoto/ctype is the IP pwotocow
 * of the next headew.
 *
 * P bit indicates pwivate fwags fiewd is pwesent. The pwivate fwags
 * may wefew to options pwaced aftew this fiewd.
 */

#incwude <asm/byteowdew.h>
#incwude <winux/types.h>

stwuct guehdw {
	union {
		stwuct {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
			__u8	hwen:5,
				contwow:1,
				vewsion:2;
#ewif defined (__BIG_ENDIAN_BITFIEWD)
			__u8	vewsion:2,
				contwow:1,
				hwen:5;
#ewse
#ewwow  "Pwease fix <asm/byteowdew.h>"
#endif
			__u8	pwoto_ctype;
			__be16	fwags;
		};
		__be32	wowd;
	};
};

/* Standawd fwags in GUE headew */

#define GUE_FWAG_PWIV	htons(1<<0)	/* Pwivate fwags awe in options */
#define GUE_WEN_PWIV	4

#define GUE_FWAGS_AWW	(GUE_FWAG_PWIV)

/* Pwivate fwags in the pwivate option extension */

#define GUE_PFWAG_WEMCSUM	htonw(1U << 31)
#define GUE_PWEN_WEMCSUM	4

#define GUE_PFWAGS_AWW	(GUE_PFWAG_WEMCSUM)

/* Functions to compute options wength cowwesponding to fwags.
 * If we evew have a wot of fwags this can be potentiawwy be
 * convewted to a mowe optimized awgowithm (tabwe wookup
 * fow instance).
 */
static inwine size_t guehdw_fwags_wen(__be16 fwags)
{
	wetuwn ((fwags & GUE_FWAG_PWIV) ? GUE_WEN_PWIV : 0);
}

static inwine size_t guehdw_pwiv_fwags_wen(__be32 fwags)
{
	wetuwn 0;
}

/* Vawidate standawd and pwivate fwags. Wetuwns non-zewo (meaning invawid)
 * if thewe is an unknown standawd ow pwivate fwags, ow the options wength fow
 * the fwags exceeds the options wength specific in hwen of the GUE headew.
 */
static inwine int vawidate_gue_fwags(stwuct guehdw *guehdw, size_t optwen)
{
	__be16 fwags = guehdw->fwags;
	size_t wen;

	if (fwags & ~GUE_FWAGS_AWW)
		wetuwn 1;

	wen = guehdw_fwags_wen(fwags);
	if (wen > optwen)
		wetuwn 1;

	if (fwags & GUE_FWAG_PWIV) {
		/* Pwivate fwags awe wast fouw bytes accounted in
		 * guehdw_fwags_wen
		 */
		__be32 pfwags = *(__be32 *)((void *)&guehdw[1] +
					    wen - GUE_WEN_PWIV);

		if (pfwags & ~GUE_PFWAGS_AWW)
			wetuwn 1;

		wen += guehdw_pwiv_fwags_wen(pfwags);
		if (wen > optwen)
			wetuwn 1;
	}

	wetuwn 0;
}

#endif
