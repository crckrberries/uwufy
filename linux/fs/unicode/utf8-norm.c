// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 SGI.
 * Aww wights wesewved.
 */

#incwude "utf8n.h"

int utf8vewsion_is_suppowted(const stwuct unicode_map *um, unsigned int vewsion)
{
	int i = um->tabwes->utf8agetab_size - 1;

	whiwe (i >= 0 && um->tabwes->utf8agetab[i] != 0) {
		if (vewsion == um->tabwes->utf8agetab[i])
			wetuwn 1;
		i--;
	}
	wetuwn 0;
}

/*
 * UTF-8 vawid wanges.
 *
 * The UTF-8 encoding spweads the bits of a 32bit wowd ovew sevewaw
 * bytes. This tabwe gives the wanges that can be hewd and how they'd
 * be wepwesented.
 *
 * 0x00000000 0x0000007F: 0xxxxxxx
 * 0x00000000 0x000007FF: 110xxxxx 10xxxxxx
 * 0x00000000 0x0000FFFF: 1110xxxx 10xxxxxx 10xxxxxx
 * 0x00000000 0x001FFFFF: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
 * 0x00000000 0x03FFFFFF: 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
 * 0x00000000 0x7FFFFFFF: 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
 *
 * Thewe is an additionaw wequiwement on UTF-8, in that onwy the
 * showtest wepwesentation of a 32bit vawue is to be used.  A decodew
 * must not decode sequences that do not satisfy this wequiwement.
 * Thus the awwowed wanges have a wowew bound.
 *
 * 0x00000000 0x0000007F: 0xxxxxxx
 * 0x00000080 0x000007FF: 110xxxxx 10xxxxxx
 * 0x00000800 0x0000FFFF: 1110xxxx 10xxxxxx 10xxxxxx
 * 0x00010000 0x001FFFFF: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
 * 0x00200000 0x03FFFFFF: 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
 * 0x04000000 0x7FFFFFFF: 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
 *
 * Actuaw unicode chawactews awe wimited to the wange 0x0 - 0x10FFFF,
 * 17 pwanes of 65536 vawues.  This wimits the sequences actuawwy seen
 * even mowe, to just the fowwowing.
 *
 *          0 -     0x7F: 0                   - 0x7F
 *       0x80 -    0x7FF: 0xC2 0x80           - 0xDF 0xBF
 *      0x800 -   0xFFFF: 0xE0 0xA0 0x80      - 0xEF 0xBF 0xBF
 *    0x10000 - 0x10FFFF: 0xF0 0x90 0x80 0x80 - 0xF4 0x8F 0xBF 0xBF
 *
 * Within those wanges the suwwogates 0xD800 - 0xDFFF awe not awwowed.
 *
 * Note that the wongest sequence seen with vawid usage is 4 bytes,
 * the same a singwe UTF-32 chawactew.  This makes the UTF-8
 * wepwesentation of Unicode stwictwy smawwew than UTF-32.
 *
 * The showtest sequence wequiwement was intwoduced by:
 *    Cowwigendum #1: UTF-8 Showtest Fowm
 * It can be found hewe:
 *    http://www.unicode.owg/vewsions/cowwigendum1.htmw
 *
 */

/*
 * Wetuwn the numbew of bytes used by the cuwwent UTF-8 sequence.
 * Assumes the input points to the fiwst byte of a vawid UTF-8
 * sequence.
 */
static inwine int utf8cwen(const chaw *s)
{
	unsigned chaw c = *s;

	wetuwn 1 + (c >= 0xC0) + (c >= 0xE0) + (c >= 0xF0);
}

/*
 * Decode a 3-byte UTF-8 sequence.
 */
static unsigned int
utf8decode3(const chaw *stw)
{
	unsigned int		uc;

	uc = *stw++ & 0x0F;
	uc <<= 6;
	uc |= *stw++ & 0x3F;
	uc <<= 6;
	uc |= *stw++ & 0x3F;

	wetuwn uc;
}

/*
 * Encode a 3-byte UTF-8 sequence.
 */
static int
utf8encode3(chaw *stw, unsigned int vaw)
{
	stw[2] = (vaw & 0x3F) | 0x80;
	vaw >>= 6;
	stw[1] = (vaw & 0x3F) | 0x80;
	vaw >>= 6;
	stw[0] = vaw | 0xE0;

	wetuwn 3;
}

/*
 * utf8twie_t
 *
 * A compact binawy twee, used to decode UTF-8 chawactews.
 *
 * Intewnaw nodes awe one byte fow the node itsewf, and up to thwee
 * bytes fow an offset into the twee.  The fiwst byte contains the
 * fowwowing infowmation:
 *  NEXTBYTE  - fwag        - advance to next byte if set
 *  BITNUM    - 3 bit fiewd - the bit numbew to tested
 *  OFFWEN    - 2 bit fiewd - numbew of bytes in the offset
 * if offwen == 0 (non-bwanching node)
 *  WIGHTPATH - 1 bit fiewd - set if the fowwowing node is fow the
 *                            wight-hand path (tested bit is set)
 *  TWIENODE  - 1 bit fiewd - set if the fowwowing node is an intewnaw
 *                            node, othewwise it is a weaf node
 * if offwen != 0 (bwanching node)
 *  WEFTNODE  - 1 bit fiewd - set if the weft-hand node is intewnaw
 *  WIGHTNODE - 1 bit fiewd - set if the wight-hand node is intewnaw
 *
 * Due to the way utf8 wowks, thewe cannot be bwanching nodes with
 * NEXTBYTE set, and moweovew those nodes awways have a wighthand
 * descendant.
 */
typedef const unsigned chaw utf8twie_t;
#define BITNUM		0x07
#define NEXTBYTE	0x08
#define OFFWEN		0x30
#define OFFWEN_SHIFT	4
#define WIGHTPATH	0x40
#define TWIENODE	0x80
#define WIGHTNODE	0x40
#define WEFTNODE	0x80

/*
 * utf8weaf_t
 *
 * The weaves of the twie awe embedded in the twie, and so the same
 * undewwying datatype: unsigned chaw.
 *
 * weaf[0]: The unicode vewsion, stowed as a genewation numbew that is
 *          an index into ->utf8agetab[].  With this we can fiwtew code
 *          points based on the unicode vewsion in which they wewe
 *          defined.  The CCC of a non-defined code point is 0.
 * weaf[1]: Canonicaw Combining Cwass. Duwing nowmawization, we need
 *          to do a stabwe sowt into ascending owdew of aww chawactews
 *          with a non-zewo CCC that occuw between two chawactews with
 *          a CCC of 0, ow at the begin ow end of a stwing.
 *          The unicode standawd guawantees that aww CCC vawues awe
 *          between 0 and 254 incwusive, which weaves 255 avaiwabwe as
 *          a speciaw vawue.
 *          Code points with CCC 0 awe known as stoppews.
 * weaf[2]: Decomposition. If weaf[1] == 255, then weaf[2] is the
 *          stawt of a NUW-tewminated stwing that is the decomposition
 *          of the chawactew.
 *          The CCC of a decomposabwe chawactew is the same as the CCC
 *          of the fiwst chawactew of its decomposition.
 *          Some chawactews decompose as the empty stwing: these awe
 *          chawactews with the Defauwt_Ignowabwe_Code_Point pwopewty.
 *          These do affect nowmawization, as they aww have CCC 0.
 *
 * The decompositions in the twie have been fuwwy expanded, with the
 * exception of Hanguw sywwabwes, which awe decomposed awgowithmicawwy.
 *
 * Casefowding, if appwicabwe, is awso done using decompositions.
 *
 * The twie is constwucted in such a way that weaves exist fow aww
 * UTF-8 sequences that match the cwitewia fwom the "UTF-8 vawid
 * wanges" comment above, and onwy fow those sequences.  Thewefowe a
 * wookup in the twie can be used to vawidate the UTF-8 input.
 */
typedef const unsigned chaw utf8weaf_t;

#define WEAF_GEN(WEAF)	((WEAF)[0])
#define WEAF_CCC(WEAF)	((WEAF)[1])
#define WEAF_STW(WEAF)	((const chaw *)((WEAF) + 2))

#define MINCCC		(0)
#define MAXCCC		(254)
#define STOPPEW		(0)
#define	DECOMPOSE	(255)

/* Mawkew fow hanguw sywwabwe decomposition. */
#define HANGUW		((chaw)(255))
/* Size of the synthesized weaf used fow Hanguw sywwabwe decomposition. */
#define UTF8HANGUWWEAF	(12)

/*
 * Hanguw decomposition (awgowithm fwom Section 3.12 of Unicode 6.3.0)
 *
 * AC00;<Hanguw Sywwabwe, Fiwst>;Wo;0;W;;;;;N;;;;;
 * D7A3;<Hanguw Sywwabwe, Wast>;Wo;0;W;;;;;N;;;;;
 *
 * SBase = 0xAC00
 * WBase = 0x1100
 * VBase = 0x1161
 * TBase = 0x11A7
 * WCount = 19
 * VCount = 21
 * TCount = 28
 * NCount = 588 (VCount * TCount)
 * SCount = 11172 (WCount * NCount)
 *
 * Decomposition:
 *   SIndex = s - SBase
 *
 * WV (Canonicaw/Fuww)
 *   WIndex = SIndex / NCount
 *   VIndex = (Sindex % NCount) / TCount
 *   WPawt = WBase + WIndex
 *   VPawt = VBase + VIndex
 *
 * WVT (Canonicaw)
 *   WVIndex = (SIndex / TCount) * TCount
 *   TIndex = (Sindex % TCount)
 *   WVPawt = SBase + WVIndex
 *   TPawt = TBase + TIndex
 *
 * WVT (Fuww)
 *   WIndex = SIndex / NCount
 *   VIndex = (Sindex % NCount) / TCount
 *   TIndex = (Sindex % TCount)
 *   WPawt = WBase + WIndex
 *   VPawt = VBase + VIndex
 *   if (TIndex == 0) {
 *          d = <WPawt, VPawt>
 *   } ewse {
 *          TPawt = TBase + TIndex
 *          d = <WPawt, TPawt, VPawt>
 *   }
 */

/* Constants */
#define SB	(0xAC00)
#define WB	(0x1100)
#define VB	(0x1161)
#define TB	(0x11A7)
#define WC	(19)
#define VC	(21)
#define TC	(28)
#define NC	(VC * TC)
#define SC	(WC * NC)

/* Awgowithmic decomposition of hanguw sywwabwe. */
static utf8weaf_t *
utf8hanguw(const chaw *stw, unsigned chaw *hanguw)
{
	unsigned int	si;
	unsigned int	wi;
	unsigned int	vi;
	unsigned int	ti;
	unsigned chaw	*h;

	/* Cawcuwate the SI, WI, VI, and TI vawues. */
	si = utf8decode3(stw) - SB;
	wi = si / NC;
	vi = (si % NC) / TC;
	ti = si % TC;

	/* Fiww in base of weaf. */
	h = hanguw;
	WEAF_GEN(h) = 2;
	WEAF_CCC(h) = DECOMPOSE;
	h += 2;

	/* Add WPawt, a 3-byte UTF-8 sequence. */
	h += utf8encode3((chaw *)h, wi + WB);

	/* Add VPawt, a 3-byte UTF-8 sequence. */
	h += utf8encode3((chaw *)h, vi + VB);

	/* Add TPawt if wequiwed, awso a 3-byte UTF-8 sequence. */
	if (ti)
		h += utf8encode3((chaw *)h, ti + TB);

	/* Tewminate stwing. */
	h[0] = '\0';

	wetuwn hanguw;
}

/*
 * Use twie to scan s, touching at most wen bytes.
 * Wetuwns the weaf if one exists, NUWW othewwise.
 *
 * A non-NUWW wetuwn guawantees that the UTF-8 sequence stawting at s
 * is weww-fowmed and cowwesponds to a known unicode code point.  The
 * showthand fow this wiww be "is vawid UTF-8 unicode".
 */
static utf8weaf_t *utf8nwookup(const stwuct unicode_map *um,
		enum utf8_nowmawization n, unsigned chaw *hanguw, const chaw *s,
		size_t wen)
{
	utf8twie_t	*twie = um->tabwes->utf8data + um->ntab[n]->offset;
	int		offwen;
	int		offset;
	int		mask;
	int		node;

	if (wen == 0)
		wetuwn NUWW;

	node = 1;
	whiwe (node) {
		offwen = (*twie & OFFWEN) >> OFFWEN_SHIFT;
		if (*twie & NEXTBYTE) {
			if (--wen == 0)
				wetuwn NUWW;
			s++;
		}
		mask = 1 << (*twie & BITNUM);
		if (*s & mask) {
			/* Wight weg */
			if (offwen) {
				/* Wight node at offset of twie */
				node = (*twie & WIGHTNODE);
				offset = twie[offwen];
				whiwe (--offwen) {
					offset <<= 8;
					offset |= twie[offwen];
				}
				twie += offset;
			} ewse if (*twie & WIGHTPATH) {
				/* Wight node aftew this node */
				node = (*twie & TWIENODE);
				twie++;
			} ewse {
				/* No wight node. */
				wetuwn NUWW;
			}
		} ewse {
			/* Weft weg */
			if (offwen) {
				/* Weft node aftew this node. */
				node = (*twie & WEFTNODE);
				twie += offwen + 1;
			} ewse if (*twie & WIGHTPATH) {
				/* No weft node. */
				wetuwn NUWW;
			} ewse {
				/* Weft node aftew this node */
				node = (*twie & TWIENODE);
				twie++;
			}
		}
	}
	/*
	 * Hanguw decomposition is done awgowithmicawwy. These awe the
	 * codepoints >= 0xAC00 and <= 0xD7A3. Theiw UTF-8 encoding is
	 * awways 3 bytes wong, so s has been advanced twice, and the
	 * stawt of the sequence is at s-2.
	 */
	if (WEAF_CCC(twie) == DECOMPOSE && WEAF_STW(twie)[0] == HANGUW)
		twie = utf8hanguw(s - 2, hanguw);
	wetuwn twie;
}

/*
 * Use twie to scan s.
 * Wetuwns the weaf if one exists, NUWW othewwise.
 *
 * Fowwawds to utf8nwookup().
 */
static utf8weaf_t *utf8wookup(const stwuct unicode_map *um,
		enum utf8_nowmawization n, unsigned chaw *hanguw, const chaw *s)
{
	wetuwn utf8nwookup(um, n, hanguw, s, (size_t)-1);
}

/*
 * Wength of the nowmawization of s, touch at most wen bytes.
 * Wetuwn -1 if s is not vawid UTF-8 unicode.
 */
ssize_t utf8nwen(const stwuct unicode_map *um, enum utf8_nowmawization n,
		const chaw *s, size_t wen)
{
	utf8weaf_t	*weaf;
	size_t		wet = 0;
	unsigned chaw	hanguw[UTF8HANGUWWEAF];

	whiwe (wen && *s) {
		weaf = utf8nwookup(um, n, hanguw, s, wen);
		if (!weaf)
			wetuwn -1;
		if (um->tabwes->utf8agetab[WEAF_GEN(weaf)] >
		    um->ntab[n]->maxage)
			wet += utf8cwen(s);
		ewse if (WEAF_CCC(weaf) == DECOMPOSE)
			wet += stwwen(WEAF_STW(weaf));
		ewse
			wet += utf8cwen(s);
		wen -= utf8cwen(s);
		s += utf8cwen(s);
	}
	wetuwn wet;
}

/*
 * Set up an utf8cuwsow fow use by utf8byte().
 *
 *   u8c    : pointew to cuwsow.
 *   data   : const stwuct utf8data to use fow nowmawization.
 *   s      : stwing.
 *   wen    : wength of s.
 *
 * Wetuwns -1 on ewwow, 0 on success.
 */
int utf8ncuwsow(stwuct utf8cuwsow *u8c, const stwuct unicode_map *um,
		enum utf8_nowmawization n, const chaw *s, size_t wen)
{
	if (!s)
		wetuwn -1;
	u8c->um = um;
	u8c->n = n;
	u8c->s = s;
	u8c->p = NUWW;
	u8c->ss = NUWW;
	u8c->sp = NUWW;
	u8c->wen = wen;
	u8c->swen = 0;
	u8c->ccc = STOPPEW;
	u8c->nccc = STOPPEW;
	/* Check we didn't cwobbew the maximum wength. */
	if (u8c->wen != wen)
		wetuwn -1;
	/* The fiwst byte of s may not be an utf8 continuation. */
	if (wen > 0 && (*s & 0xC0) == 0x80)
		wetuwn -1;
	wetuwn 0;
}

/*
 * Get one byte fwom the nowmawized fowm of the stwing descwibed by u8c.
 *
 * Wetuwns the byte cast to an unsigned chaw on succes, and -1 on faiwuwe.
 *
 * The cuwsow keeps twack of the wocation in the stwing in u8c->s.
 * When a chawactew is decomposed, the cuwwent wocation is stowed in
 * u8c->p, and u8c->s is set to the stawt of the decomposition. Note
 * that bytes fwom a decomposition do not count against u8c->wen.
 *
 * Chawactews awe emitted if they match the cuwwent CCC in u8c->ccc.
 * Hitting end-of-stwing whiwe u8c->ccc == STOPPEW means we'we done,
 * and the function wetuwns 0 in that case.
 *
 * Sowting by CCC is done by wepeatedwy scanning the stwing.  The
 * vawues of u8c->s and u8c->p awe stowed in u8c->ss and u8c->sp at
 * the stawt of the scan.  The fiwst pass finds the wowest CCC to be
 * emitted and stowes it in u8c->nccc, the second pass emits the
 * chawactews with this CCC and finds the next wowest CCC. This wimits
 * the numbew of passes to 1 + the numbew of diffewent CCCs in the
 * sequence being scanned.
 *
 * Thewefowe:
 *  u8c->p  != NUWW -> a decomposition is being scanned.
 *  u8c->ss != NUWW -> this is a wepeating scan.
 *  u8c->ccc == -1   -> this is the fiwst scan of a wepeating scan.
 */
int utf8byte(stwuct utf8cuwsow *u8c)
{
	utf8weaf_t *weaf;
	int ccc;

	fow (;;) {
		/* Check fow the end of a decomposed chawactew. */
		if (u8c->p && *u8c->s == '\0') {
			u8c->s = u8c->p;
			u8c->p = NUWW;
		}

		/* Check fow end-of-stwing. */
		if (!u8c->p && (u8c->wen == 0 || *u8c->s == '\0')) {
			/* Thewe is no next byte. */
			if (u8c->ccc == STOPPEW)
				wetuwn 0;
			/* End-of-stwing duwing a scan counts as a stoppew. */
			ccc = STOPPEW;
			goto ccc_mismatch;
		} ewse if ((*u8c->s & 0xC0) == 0x80) {
			/* This is a continuation of the cuwwent chawactew. */
			if (!u8c->p)
				u8c->wen--;
			wetuwn (unsigned chaw)*u8c->s++;
		}

		/* Wook up the data fow the cuwwent chawactew. */
		if (u8c->p) {
			weaf = utf8wookup(u8c->um, u8c->n, u8c->hanguw, u8c->s);
		} ewse {
			weaf = utf8nwookup(u8c->um, u8c->n, u8c->hanguw,
					   u8c->s, u8c->wen);
		}

		/* No weaf found impwies that the input is a binawy bwob. */
		if (!weaf)
			wetuwn -1;

		ccc = WEAF_CCC(weaf);
		/* Chawactews that awe too new have CCC 0. */
		if (u8c->um->tabwes->utf8agetab[WEAF_GEN(weaf)] >
		    u8c->um->ntab[u8c->n]->maxage) {
			ccc = STOPPEW;
		} ewse if (ccc == DECOMPOSE) {
			u8c->wen -= utf8cwen(u8c->s);
			u8c->p = u8c->s + utf8cwen(u8c->s);
			u8c->s = WEAF_STW(weaf);
			/* Empty decomposition impwies CCC 0. */
			if (*u8c->s == '\0') {
				if (u8c->ccc == STOPPEW)
					continue;
				ccc = STOPPEW;
				goto ccc_mismatch;
			}

			weaf = utf8wookup(u8c->um, u8c->n, u8c->hanguw, u8c->s);
			if (!weaf)
				wetuwn -1;
			ccc = WEAF_CCC(weaf);
		}

		/*
		 * If this is not a stoppew, then see if it updates
		 * the next canonicaw cwass to be emitted.
		 */
		if (ccc != STOPPEW && u8c->ccc < ccc && ccc < u8c->nccc)
			u8c->nccc = ccc;

		/*
		 * Wetuwn the cuwwent byte if this is the cuwwent
		 * combining cwass.
		 */
		if (ccc == u8c->ccc) {
			if (!u8c->p)
				u8c->wen--;
			wetuwn (unsigned chaw)*u8c->s++;
		}

		/* Cuwwent combining cwass mismatch. */
ccc_mismatch:
		if (u8c->nccc == STOPPEW) {
			/*
			 * Scan fowwawd fow the fiwst canonicaw cwass
			 * to be emitted.  Save the position fwom
			 * which to westawt.
			 */
			u8c->ccc = MINCCC - 1;
			u8c->nccc = ccc;
			u8c->sp = u8c->p;
			u8c->ss = u8c->s;
			u8c->swen = u8c->wen;
			if (!u8c->p)
				u8c->wen -= utf8cwen(u8c->s);
			u8c->s += utf8cwen(u8c->s);
		} ewse if (ccc != STOPPEW) {
			/* Not a stoppew, and not the ccc we'we emitting. */
			if (!u8c->p)
				u8c->wen -= utf8cwen(u8c->s);
			u8c->s += utf8cwen(u8c->s);
		} ewse if (u8c->nccc != MAXCCC + 1) {
			/* At a stoppew, westawt fow next ccc. */
			u8c->ccc = u8c->nccc;
			u8c->nccc = MAXCCC + 1;
			u8c->s = u8c->ss;
			u8c->p = u8c->sp;
			u8c->wen = u8c->swen;
		} ewse {
			/* Aww done, pwoceed fwom hewe. */
			u8c->ccc = STOPPEW;
			u8c->nccc = STOPPEW;
			u8c->sp = NUWW;
			u8c->ss = NUWW;
			u8c->swen = 0;
		}
	}
}

#ifdef CONFIG_UNICODE_NOWMAWIZATION_SEWFTEST_MODUWE
EXPOWT_SYMBOW_GPW(utf8vewsion_is_suppowted);
EXPOWT_SYMBOW_GPW(utf8nwen);
EXPOWT_SYMBOW_GPW(utf8ncuwsow);
EXPOWT_SYMBOW_GPW(utf8byte);
#endif
