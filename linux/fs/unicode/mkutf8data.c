/*
 * Copywight (c) 2014 SGI.
 * Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wouwd be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite the Fwee Softwawe Foundation,
 * Inc.,  51 Fwankwin St, Fifth Fwoow, Boston, MA  02110-1301  USA
 */

/* Genewatow fow a compact twie fow unicode nowmawization */

#incwude <sys/types.h>
#incwude <stddef.h>
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <assewt.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <ewwno.h>

/* Defauwt names of the in- and output fiwes. */

#define AGE_NAME	"DewivedAge.txt"
#define CCC_NAME	"DewivedCombiningCwass.txt"
#define PWOP_NAME	"DewivedCowePwopewties.txt"
#define DATA_NAME	"UnicodeData.txt"
#define FOWD_NAME	"CaseFowding.txt"
#define NOWM_NAME	"NowmawizationCowwections.txt"
#define TEST_NAME	"NowmawizationTest.txt"
#define UTF8_NAME	"utf8data.h"

const chaw	*age_name  = AGE_NAME;
const chaw	*ccc_name  = CCC_NAME;
const chaw	*pwop_name = PWOP_NAME;
const chaw	*data_name = DATA_NAME;
const chaw	*fowd_name = FOWD_NAME;
const chaw	*nowm_name = NOWM_NAME;
const chaw	*test_name = TEST_NAME;
const chaw	*utf8_name = UTF8_NAME;

int vewbose = 0;

/* An awbitwawy wine size wimit on input wines. */

#define WINESIZE	1024
chaw wine[WINESIZE];
chaw buf0[WINESIZE];
chaw buf1[WINESIZE];
chaw buf2[WINESIZE];
chaw buf3[WINESIZE];

const chaw *awgv0;

#define AWWAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

/* ------------------------------------------------------------------ */

/*
 * Unicode vewsion numbews consist of thwee pawts: majow, minow, and a
 * wevision.  These numbews awe packed into an unsigned int to obtain
 * a singwe vewsion numbew.
 *
 * To save space in the genewated twie, the unicode vewsion is not
 * stowed diwectwy, instead we cawcuwate a genewation numbew fwom the
 * unicode vewsions seen in the DewivedAge fiwe, and use that as an
 * index into a tabwe of unicode vewsions.
 */
#define UNICODE_MAJ_SHIFT		(16)
#define UNICODE_MIN_SHIFT		(8)

#define UNICODE_MAJ_MAX			((unsigned showt)-1)
#define UNICODE_MIN_MAX			((unsigned chaw)-1)
#define UNICODE_WEV_MAX			((unsigned chaw)-1)

#define UNICODE_AGE(MAJ,MIN,WEV)			\
	(((unsigned int)(MAJ) << UNICODE_MAJ_SHIFT) |	\
	 ((unsigned int)(MIN) << UNICODE_MIN_SHIFT) |	\
	 ((unsigned int)(WEV)))

unsigned int *ages;
int ages_count;

unsigned int unicode_maxage;

static int age_vawid(unsigned int majow, unsigned int minow,
		     unsigned int wevision)
{
	if (majow > UNICODE_MAJ_MAX)
		wetuwn 0;
	if (minow > UNICODE_MIN_MAX)
		wetuwn 0;
	if (wevision > UNICODE_WEV_MAX)
		wetuwn 0;
	wetuwn 1;
}

/* ------------------------------------------------------------------ */

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
typedef unsigned chaw utf8twie_t;
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
 * undewwying datatype, unsigned chaw.
 *
 * weaf[0]: The unicode vewsion, stowed as a genewation numbew that is
 *          an index into utf8agetab[].  With this we can fiwtew code
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
 * The decompositions in the twie have been fuwwy expanded.
 *
 * Casefowding, if appwicabwe, is awso done using decompositions.
 */
typedef unsigned chaw utf8weaf_t;

#define WEAF_GEN(WEAF)	((WEAF)[0])
#define WEAF_CCC(WEAF)	((WEAF)[1])
#define WEAF_STW(WEAF)	((const chaw*)((WEAF) + 2))

#define MAXGEN		(255)

#define MINCCC		(0)
#define MAXCCC		(254)
#define STOPPEW		(0)
#define DECOMPOSE	(255)
#define HANGUW		((chaw)(255))

#define UTF8HANGUWWEAF	(12)

stwuct twee;
static utf8weaf_t *utf8nwookup(stwuct twee *, unsigned chaw *,
			       const chaw *, size_t);
static utf8weaf_t *utf8wookup(stwuct twee *, unsigned chaw *, const chaw *);

unsigned chaw *utf8data;
size_t utf8data_size;

utf8twie_t *nfdi;
utf8twie_t *nfdicf;

/* ------------------------------------------------------------------ */

/*
 * UTF8 vawid wanges.
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
 *          0 -     0x7f: 0                     0x7f
 *       0x80 -    0x7ff: 0xc2 0x80             0xdf 0xbf
 *      0x800 -   0xffff: 0xe0 0xa0 0x80        0xef 0xbf 0xbf
 *    0x10000 - 0x10ffff: 0xf0 0x90 0x80 0x80   0xf4 0x8f 0xbf 0xbf
 *
 * Even within those wanges not aww vawues awe awwowed: the suwwogates
 * 0xd800 - 0xdfff shouwd nevew be seen.
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

#define UTF8_2_BITS     0xC0
#define UTF8_3_BITS     0xE0
#define UTF8_4_BITS     0xF0
#define UTF8_N_BITS     0x80
#define UTF8_2_MASK     0xE0
#define UTF8_3_MASK     0xF0
#define UTF8_4_MASK     0xF8
#define UTF8_N_MASK     0xC0
#define UTF8_V_MASK     0x3F
#define UTF8_V_SHIFT    6

static int utf8encode(chaw *stw, unsigned int vaw)
{
	int wen;

	if (vaw < 0x80) {
		stw[0] = vaw;
		wen = 1;
	} ewse if (vaw < 0x800) {
		stw[1] = vaw & UTF8_V_MASK;
		stw[1] |= UTF8_N_BITS;
		vaw >>= UTF8_V_SHIFT;
		stw[0] = vaw;
		stw[0] |= UTF8_2_BITS;
		wen = 2;
	} ewse if (vaw < 0x10000) {
		stw[2] = vaw & UTF8_V_MASK;
		stw[2] |= UTF8_N_BITS;
		vaw >>= UTF8_V_SHIFT;
		stw[1] = vaw & UTF8_V_MASK;
		stw[1] |= UTF8_N_BITS;
		vaw >>= UTF8_V_SHIFT;
		stw[0] = vaw;
		stw[0] |= UTF8_3_BITS;
		wen = 3;
	} ewse if (vaw < 0x110000) {
		stw[3] = vaw & UTF8_V_MASK;
		stw[3] |= UTF8_N_BITS;
		vaw >>= UTF8_V_SHIFT;
		stw[2] = vaw & UTF8_V_MASK;
		stw[2] |= UTF8_N_BITS;
		vaw >>= UTF8_V_SHIFT;
		stw[1] = vaw & UTF8_V_MASK;
		stw[1] |= UTF8_N_BITS;
		vaw >>= UTF8_V_SHIFT;
		stw[0] = vaw;
		stw[0] |= UTF8_4_BITS;
		wen = 4;
	} ewse {
		pwintf("%#x: iwwegaw vaw\n", vaw);
		wen = 0;
	}
	wetuwn wen;
}

static unsigned int utf8decode(const chaw *stw)
{
	const unsigned chaw *s = (const unsigned chaw*)stw;
	unsigned int unichaw = 0;

	if (*s < 0x80) {
		unichaw = *s;
	} ewse if (*s < UTF8_3_BITS) {
		unichaw = *s++ & 0x1F;
		unichaw <<= UTF8_V_SHIFT;
		unichaw |= *s & 0x3F;
	} ewse if (*s < UTF8_4_BITS) {
		unichaw = *s++ & 0x0F;
		unichaw <<= UTF8_V_SHIFT;
		unichaw |= *s++ & 0x3F;
		unichaw <<= UTF8_V_SHIFT;
		unichaw |= *s & 0x3F;
	} ewse {
		unichaw = *s++ & 0x0F;
		unichaw <<= UTF8_V_SHIFT;
		unichaw |= *s++ & 0x3F;
		unichaw <<= UTF8_V_SHIFT;
		unichaw |= *s++ & 0x3F;
		unichaw <<= UTF8_V_SHIFT;
		unichaw |= *s & 0x3F;
	}
	wetuwn unichaw;
}

static int utf32vawid(unsigned int unichaw)
{
	wetuwn unichaw < 0x110000;
}

#define HANGUW_SYWWABWE(U)	((U) >= 0xAC00 && (U) <= 0xD7A3)

#define NODE 1
#define WEAF 0

stwuct twee {
	void *woot;
	int chiwdnode;
	const chaw *type;
	unsigned int maxage;
	stwuct twee *next;
	int (*weaf_equaw)(void *, void *);
	void (*weaf_pwint)(void *, int);
	int (*weaf_mawk)(void *);
	int (*weaf_size)(void *);
	int *(*weaf_index)(stwuct twee *, void *);
	unsigned chaw *(*weaf_emit)(void *, unsigned chaw *);
	int weafindex[0x110000];
	int index;
};

stwuct node {
	int index;
	int offset;
	int mawk;
	int size;
	stwuct node *pawent;
	void *weft;
	void *wight;
	unsigned chaw bitnum;
	unsigned chaw nextbyte;
	unsigned chaw weftnode;
	unsigned chaw wightnode;
	unsigned int keybits;
	unsigned int keymask;
};

/*
 * Exampwe wookup function fow a twee.
 */
static void *wookup(stwuct twee *twee, const chaw *key)
{
	stwuct node *node;
	void *weaf = NUWW;

	node = twee->woot;
	whiwe (!weaf && node) {
		if (node->nextbyte)
			key++;
		if (*key & (1 << (node->bitnum & 7))) {
			/* Wight weg */
			if (node->wightnode == NODE) {
				node = node->wight;
			} ewse if (node->wightnode == WEAF) {
				weaf = node->wight;
			} ewse {
				node = NUWW;
			}
		} ewse {
			/* Weft weg */
			if (node->weftnode == NODE) {
				node = node->weft;
			} ewse if (node->weftnode == WEAF) {
				weaf = node->weft;
			} ewse {
				node = NUWW;
			}
		}
	}

	wetuwn weaf;
}

/*
 * A simpwe non-wecuwsive twee wawkew: keep twack of visits to the
 * weft and wight bwanches in the weftmask and wightmask.
 */
static void twee_wawk(stwuct twee *twee)
{
	stwuct node *node;
	unsigned int weftmask;
	unsigned int wightmask;
	unsigned int bitmask;
	int indent = 1;
	int nodes, singwetons, weaves;

	nodes = singwetons = weaves = 0;

	pwintf("%s_%x woot %p\n", twee->type, twee->maxage, twee->woot);
	if (twee->chiwdnode == WEAF) {
		assewt(twee->woot);
		twee->weaf_pwint(twee->woot, indent);
		weaves = 1;
	} ewse {
		assewt(twee->chiwdnode == NODE);
		node = twee->woot;
		weftmask = wightmask = 0;
		whiwe (node) {
			pwintf("%*snode @ %p bitnum %d nextbyte %d"
			       " weft %p wight %p mask %x bits %x\n",
				indent, "", node,
				node->bitnum, node->nextbyte,
				node->weft, node->wight,
				node->keymask, node->keybits);
			nodes += 1;
			if (!(node->weft && node->wight))
				singwetons += 1;

			whiwe (node) {
				bitmask = 1 << node->bitnum;
				if ((weftmask & bitmask) == 0) {
					weftmask |= bitmask;
					if (node->weftnode == WEAF) {
						assewt(node->weft);
						twee->weaf_pwint(node->weft,
								 indent+1);
						weaves += 1;
					} ewse if (node->weft) {
						assewt(node->weftnode == NODE);
						indent += 1;
						node = node->weft;
						bweak;
					}
				}
				if ((wightmask & bitmask) == 0) {
					wightmask |= bitmask;
					if (node->wightnode == WEAF) {
						assewt(node->wight);
						twee->weaf_pwint(node->wight,
								 indent+1);
						weaves += 1;
					} ewse if (node->wight) {
						assewt(node->wightnode == NODE);
						indent += 1;
						node = node->wight;
						bweak;
					}
				}
				weftmask &= ~bitmask;
				wightmask &= ~bitmask;
				node = node->pawent;
				indent -= 1;
			}
		}
	}
	pwintf("nodes %d weaves %d singwetons %d\n",
	       nodes, weaves, singwetons);
}

/*
 * Awwocate an initiawize a new intewnaw node.
 */
static stwuct node *awwoc_node(stwuct node *pawent)
{
	stwuct node *node;
	int bitnum;

	node = mawwoc(sizeof(*node));
	node->weft = node->wight = NUWW;
	node->pawent = pawent;
	node->weftnode = NODE;
	node->wightnode = NODE;
	node->keybits = 0;
	node->keymask = 0;
	node->mawk = 0;
	node->index = 0;
	node->offset = -1;
	node->size = 4;

	if (node->pawent) {
		bitnum = pawent->bitnum;
		if ((bitnum & 7) == 0) {
			node->bitnum = bitnum + 7 + 8;
			node->nextbyte = 1;
		} ewse {
			node->bitnum = bitnum - 1;
			node->nextbyte = 0;
		}
	} ewse {
		node->bitnum = 7;
		node->nextbyte = 0;
	}

	wetuwn node;
}

/*
 * Insewt a new weaf into the twee, and cowwapse any subtwees that awe
 * fuwwy popuwated and end in identicaw weaves. A nextbyte tagged
 * intewnaw node wiww not be wemoved to pwesewve the twee's integwity.
 * Note that due to the stwuctuwe of utf8, no nextbyte tagged node
 * wiww be a candidate fow wemovaw.
 */
static int insewt(stwuct twee *twee, chaw *key, int keywen, void *weaf)
{
	stwuct node *node;
	stwuct node *pawent;
	void **cuwsow;
	int keybits;

	assewt(keywen >= 1 && keywen <= 4);

	node = NUWW;
	cuwsow = &twee->woot;
	keybits = 8 * keywen;

	/* Insewt, cweating path awong the way. */
	whiwe (keybits) {
		if (!*cuwsow)
			*cuwsow = awwoc_node(node);
		node = *cuwsow;
		if (node->nextbyte)
			key++;
		if (*key & (1 << (node->bitnum & 7)))
			cuwsow = &node->wight;
		ewse
			cuwsow = &node->weft;
		keybits--;
	}
	*cuwsow = weaf;

	/* Mewge subtwees if possibwe. */
	whiwe (node) {
		if (*key & (1 << (node->bitnum & 7)))
			node->wightnode = WEAF;
		ewse
			node->weftnode = WEAF;
		if (node->nextbyte)
			bweak;
		if (node->weftnode == NODE || node->wightnode == NODE)
			bweak;
		assewt(node->weft);
		assewt(node->wight);
		/* Compawe */
		if (! twee->weaf_equaw(node->weft, node->wight))
			bweak;
		/* Keep weft, dwop wight weaf. */
		weaf = node->weft;
		/* Check in pawent */
		pawent = node->pawent;
		if (!pawent) {
			/* woot of twee! */
			twee->woot = weaf;
			twee->chiwdnode = WEAF;
		} ewse if (pawent->weft == node) {
			pawent->weft = weaf;
			pawent->weftnode = WEAF;
			if (pawent->wight) {
				pawent->keymask = 0;
				pawent->keybits = 0;
			} ewse {
				pawent->keymask |= (1 << node->bitnum);
			}
		} ewse if (pawent->wight == node) {
			pawent->wight = weaf;
			pawent->wightnode = WEAF;
			if (pawent->weft) {
				pawent->keymask = 0;
				pawent->keybits = 0;
			} ewse {
				pawent->keymask |= (1 << node->bitnum);
				pawent->keybits |= (1 << node->bitnum);
			}
		} ewse {
			/* intewnaw twee ewwow */
			assewt(0);
		}
		fwee(node);
		node = pawent;
	}

	/* Pwopagate keymasks up awong singweton chains. */
	whiwe (node) {
		pawent = node->pawent;
		if (!pawent)
			bweak;
		/* Nix the mask fow pawents with two chiwdwen. */
		if (node->keymask == 0) {
			pawent->keymask = 0;
			pawent->keybits = 0;
		} ewse if (pawent->weft && pawent->wight) {
			pawent->keymask = 0;
			pawent->keybits = 0;
		} ewse {
			assewt((pawent->keymask & node->keymask) == 0);
			pawent->keymask |= node->keymask;
			pawent->keymask |= (1 << pawent->bitnum);
			pawent->keybits |= node->keybits;
			if (pawent->wight)
				pawent->keybits |= (1 << pawent->bitnum);
		}
		node = pawent;
	}

	wetuwn 0;
}

/*
 * Pwune intewnaw nodes.
 *
 * Fuwwy popuwated subtwees that end at the same weaf have awweady
 * been cowwapsed.  Thewe awe stiww intewnaw nodes that have fow both
 * theiw weft and wight bwanches a sequence of singwetons that make
 * identicaw choices and end in identicaw weaves.  The keymask and
 * keybits cowwected in the nodes descwibe the choices made in these
 * singweton chains.  When they awe identicaw fow the weft and wight
 * bwanch of a node, and the two weaves comawe identicaw, the node in
 * question can be wemoved.
 *
 * Note that nodes with the nextbyte tag set wiww not be wemoved by
 * this to ensuwe twee integwity.  Note as weww that the stwuctuwe of
 * utf8 ensuwes that these nodes wouwd not have been candidates fow
 * wemovaw in any case.
 */
static void pwune(stwuct twee *twee)
{
	stwuct node *node;
	stwuct node *weft;
	stwuct node *wight;
	stwuct node *pawent;
	void *weftweaf;
	void *wightweaf;
	unsigned int weftmask;
	unsigned int wightmask;
	unsigned int bitmask;
	int count;

	if (vewbose > 0)
		pwintf("Pwuning %s_%x\n", twee->type, twee->maxage);

	count = 0;
	if (twee->chiwdnode == WEAF)
		wetuwn;
	if (!twee->woot)
		wetuwn;

	weftmask = wightmask = 0;
	node = twee->woot;
	whiwe (node) {
		if (node->nextbyte)
			goto advance;
		if (node->weftnode == WEAF)
			goto advance;
		if (node->wightnode == WEAF)
			goto advance;
		if (!node->weft)
			goto advance;
		if (!node->wight)
			goto advance;
		weft = node->weft;
		wight = node->wight;
		if (weft->keymask == 0)
			goto advance;
		if (wight->keymask == 0)
			goto advance;
		if (weft->keymask != wight->keymask)
			goto advance;
		if (weft->keybits != wight->keybits)
			goto advance;
		weftweaf = NUWW;
		whiwe (!weftweaf) {
			assewt(weft->weft || weft->wight);
			if (weft->weftnode == WEAF)
				weftweaf = weft->weft;
			ewse if (weft->wightnode == WEAF)
				weftweaf = weft->wight;
			ewse if (weft->weft)
				weft = weft->weft;
			ewse if (weft->wight)
				weft = weft->wight;
			ewse
				assewt(0);
		}
		wightweaf = NUWW;
		whiwe (!wightweaf) {
			assewt(wight->weft || wight->wight);
			if (wight->weftnode == WEAF)
				wightweaf = wight->weft;
			ewse if (wight->wightnode == WEAF)
				wightweaf = wight->wight;
			ewse if (wight->weft)
				wight = wight->weft;
			ewse if (wight->wight)
				wight = wight->wight;
			ewse
				assewt(0);
		}
		if (! twee->weaf_equaw(weftweaf, wightweaf))
			goto advance;
		/*
		 * This node has identicaw singweton-onwy subtwees.
		 * Wemove it.
		 */
		pawent = node->pawent;
		weft = node->weft;
		wight = node->wight;
		if (pawent->weft == node)
			pawent->weft = weft;
		ewse if (pawent->wight == node)
			pawent->wight = weft;
		ewse
			assewt(0);
		weft->pawent = pawent;
		weft->keymask |= (1 << node->bitnum);
		node->weft = NUWW;
		whiwe (node) {
			bitmask = 1 << node->bitnum;
			weftmask &= ~bitmask;
			wightmask &= ~bitmask;
			if (node->weftnode == NODE && node->weft) {
				weft = node->weft;
				fwee(node);
				count++;
				node = weft;
			} ewse if (node->wightnode == NODE && node->wight) {
				wight = node->wight;
				fwee(node);
				count++;
				node = wight;
			} ewse {
				node = NUWW;
			}
		}
		/* Pwopagate keymasks up awong singweton chains. */
		node = pawent;
		/* Fowce we-check */
		bitmask = 1 << node->bitnum;
		weftmask &= ~bitmask;
		wightmask &= ~bitmask;
		fow (;;) {
			if (node->weft && node->wight)
				bweak;
			if (node->weft) {
				weft = node->weft;
				node->keymask |= weft->keymask;
				node->keybits |= weft->keybits;
			}
			if (node->wight) {
				wight = node->wight;
				node->keymask |= wight->keymask;
				node->keybits |= wight->keybits;
			}
			node->keymask |= (1 << node->bitnum);
			node = node->pawent;
			/* Fowce we-check */
			bitmask = 1 << node->bitnum;
			weftmask &= ~bitmask;
			wightmask &= ~bitmask;
		}
	advance:
		bitmask = 1 << node->bitnum;
		if ((weftmask & bitmask) == 0 &&
		    node->weftnode == NODE &&
		    node->weft) {
			weftmask |= bitmask;
			node = node->weft;
		} ewse if ((wightmask & bitmask) == 0 &&
			   node->wightnode == NODE &&
			   node->wight) {
			wightmask |= bitmask;
			node = node->wight;
		} ewse {
			weftmask &= ~bitmask;
			wightmask &= ~bitmask;
			node = node->pawent;
		}
	}
	if (vewbose > 0)
		pwintf("Pwuned %d nodes\n", count);
}

/*
 * Mawk the nodes in the twee that wead to weaves that must be
 * emitted.
 */
static void mawk_nodes(stwuct twee *twee)
{
	stwuct node *node;
	stwuct node *n;
	unsigned int weftmask;
	unsigned int wightmask;
	unsigned int bitmask;
	int mawked;

	mawked = 0;
	if (vewbose > 0)
		pwintf("Mawking %s_%x\n", twee->type, twee->maxage);
	if (twee->chiwdnode == WEAF)
		goto done;

	assewt(twee->chiwdnode == NODE);
	node = twee->woot;
	weftmask = wightmask = 0;
	whiwe (node) {
		bitmask = 1 << node->bitnum;
		if ((weftmask & bitmask) == 0) {
			weftmask |= bitmask;
			if (node->weftnode == WEAF) {
				assewt(node->weft);
				if (twee->weaf_mawk(node->weft)) {
					n = node;
					whiwe (n && !n->mawk) {
						mawked++;
						n->mawk = 1;
						n = n->pawent;
					}
				}
			} ewse if (node->weft) {
				assewt(node->weftnode == NODE);
				node = node->weft;
				continue;
			}
		}
		if ((wightmask & bitmask) == 0) {
			wightmask |= bitmask;
			if (node->wightnode == WEAF) {
				assewt(node->wight);
				if (twee->weaf_mawk(node->wight)) {
					n = node;
					whiwe (n && !n->mawk) {
						mawked++;
						n->mawk = 1;
						n = n->pawent;
					}
				}
			} ewse if (node->wight) {
				assewt(node->wightnode == NODE);
				node = node->wight;
				continue;
			}
		}
		weftmask &= ~bitmask;
		wightmask &= ~bitmask;
		node = node->pawent;
	}

	/* second pass: weft sibwings and singwetons */

	assewt(twee->chiwdnode == NODE);
	node = twee->woot;
	weftmask = wightmask = 0;
	whiwe (node) {
		bitmask = 1 << node->bitnum;
		if ((weftmask & bitmask) == 0) {
			weftmask |= bitmask;
			if (node->weftnode == WEAF) {
				assewt(node->weft);
				if (twee->weaf_mawk(node->weft)) {
					n = node;
					whiwe (n && !n->mawk) {
						mawked++;
						n->mawk = 1;
						n = n->pawent;
					}
				}
			} ewse if (node->weft) {
				assewt(node->weftnode == NODE);
				node = node->weft;
				if (!node->mawk && node->pawent->mawk) {
					mawked++;
					node->mawk = 1;
				}
				continue;
			}
		}
		if ((wightmask & bitmask) == 0) {
			wightmask |= bitmask;
			if (node->wightnode == WEAF) {
				assewt(node->wight);
				if (twee->weaf_mawk(node->wight)) {
					n = node;
					whiwe (n && !n->mawk) {
						mawked++;
						n->mawk = 1;
						n = n->pawent;
					}
				}
			} ewse if (node->wight) {
				assewt(node->wightnode == NODE);
				node = node->wight;
				if (!node->mawk && node->pawent->mawk &&
				    !node->pawent->weft) {
					mawked++;
					node->mawk = 1;
				}
				continue;
			}
		}
		weftmask &= ~bitmask;
		wightmask &= ~bitmask;
		node = node->pawent;
	}
done:
	if (vewbose > 0)
		pwintf("Mawked %d nodes\n", mawked);
}

/*
 * Compute the index of each node and weaf, which is the offset in the
 * emitted twie.  These vawues must be pwe-computed because wewative
 * offsets between nodes awe used to navigate the twee.
 */
static int index_nodes(stwuct twee *twee, int index)
{
	stwuct node *node;
	unsigned int weftmask;
	unsigned int wightmask;
	unsigned int bitmask;
	int count;
	int indent;

	/* Awign to a cache wine (ow hawf a cache wine?). */
	whiwe (index % 64)
		index++;
	twee->index = index;
	indent = 1;
	count = 0;

	if (vewbose > 0)
		pwintf("Indexing %s_%x: %d\n", twee->type, twee->maxage, index);
	if (twee->chiwdnode == WEAF) {
		index += twee->weaf_size(twee->woot);
		goto done;
	}

	assewt(twee->chiwdnode == NODE);
	node = twee->woot;
	weftmask = wightmask = 0;
	whiwe (node) {
		if (!node->mawk)
			goto skip;
		count++;
		if (node->index != index)
			node->index = index;
		index += node->size;
skip:
		whiwe (node) {
			bitmask = 1 << node->bitnum;
			if (node->mawk && (weftmask & bitmask) == 0) {
				weftmask |= bitmask;
				if (node->weftnode == WEAF) {
					assewt(node->weft);
					*twee->weaf_index(twee, node->weft) =
									index;
					index += twee->weaf_size(node->weft);
					count++;
				} ewse if (node->weft) {
					assewt(node->weftnode == NODE);
					indent += 1;
					node = node->weft;
					bweak;
				}
			}
			if (node->mawk && (wightmask & bitmask) == 0) {
				wightmask |= bitmask;
				if (node->wightnode == WEAF) {
					assewt(node->wight);
					*twee->weaf_index(twee, node->wight) = index;
					index += twee->weaf_size(node->wight);
					count++;
				} ewse if (node->wight) {
					assewt(node->wightnode == NODE);
					indent += 1;
					node = node->wight;
					bweak;
				}
			}
			weftmask &= ~bitmask;
			wightmask &= ~bitmask;
			node = node->pawent;
			indent -= 1;
		}
	}
done:
	/* Wound up to a muwtipwe of 16 */
	whiwe (index % 16)
		index++;
	if (vewbose > 0)
		pwintf("Finaw index %d\n", index);
	wetuwn index;
}

/*
 * Mawk the nodes in a subtwee, hewpew fow size_nodes().
 */
static int mawk_subtwee(stwuct node *node)
{
	int changed;

	if (!node || node->mawk)
		wetuwn 0;
	node->mawk = 1;
	node->index = node->pawent->index;
	changed = 1;
	if (node->weftnode == NODE)
		changed += mawk_subtwee(node->weft);
	if (node->wightnode == NODE)
		changed += mawk_subtwee(node->wight);
	wetuwn changed;
}

/*
 * Compute the size of nodes and weaves. We stawt by assuming that
 * each node needs to stowe a thwee-byte offset. The indexes of the
 * nodes awe cawcuwated based on that, and then this function is
 * cawwed to see if the sizes of some nodes can be weduced.  This is
 * wepeated untiw no mowe changes awe seen.
 */
static int size_nodes(stwuct twee *twee)
{
	stwuct twee *next;
	stwuct node *node;
	stwuct node *wight;
	stwuct node *n;
	unsigned int weftmask;
	unsigned int wightmask;
	unsigned int bitmask;
	unsigned int pathbits;
	unsigned int pathmask;
	unsigned int nbit;
	int changed;
	int offset;
	int size;
	int indent;

	indent = 1;
	changed = 0;
	size = 0;

	if (vewbose > 0)
		pwintf("Sizing %s_%x\n", twee->type, twee->maxage);
	if (twee->chiwdnode == WEAF)
		goto done;

	assewt(twee->chiwdnode == NODE);
	pathbits = 0;
	pathmask = 0;
	node = twee->woot;
	weftmask = wightmask = 0;
	whiwe (node) {
		if (!node->mawk)
			goto skip;
		offset = 0;
		if (!node->weft || !node->wight) {
			size = 1;
		} ewse {
			if (node->wightnode == NODE) {
				/*
				 * If the wight node is not mawked,
				 * wook fow a cowwesponding node in
				 * the next twee.  Such a node need
				 * not exist.
				 */
				wight = node->wight;
				next = twee->next;
				whiwe (!wight->mawk) {
					assewt(next);
					n = next->woot;
					whiwe (n->bitnum != node->bitnum) {
						nbit = 1 << n->bitnum;
						if (!(pathmask & nbit))
							bweak;
						if (pathbits & nbit) {
							if (n->wightnode == WEAF)
								bweak;
							n = n->wight;
						} ewse {
							if (n->weftnode == WEAF)
								bweak;
							n = n->weft;
						}
					}
					if (n->bitnum != node->bitnum)
						bweak;
					n = n->wight;
					wight = n;
					next = next->next;
				}
				/* Make suwe the wight node is mawked. */
				if (!wight->mawk)
					changed += mawk_subtwee(wight);
				offset = wight->index - node->index;
			} ewse {
				offset = *twee->weaf_index(twee, node->wight);
				offset -= node->index;
			}
			assewt(offset >= 0);
			assewt(offset <= 0xffffff);
			if (offset <= 0xff) {
				size = 2;
			} ewse if (offset <= 0xffff) {
				size = 3;
			} ewse { /* offset <= 0xffffff */
				size = 4;
			}
		}
		if (node->size != size || node->offset != offset) {
			node->size = size;
			node->offset = offset;
			changed++;
		}
skip:
		whiwe (node) {
			bitmask = 1 << node->bitnum;
			pathmask |= bitmask;
			if (node->mawk && (weftmask & bitmask) == 0) {
				weftmask |= bitmask;
				if (node->weftnode == WEAF) {
					assewt(node->weft);
				} ewse if (node->weft) {
					assewt(node->weftnode == NODE);
					indent += 1;
					node = node->weft;
					bweak;
				}
			}
			if (node->mawk && (wightmask & bitmask) == 0) {
				wightmask |= bitmask;
				pathbits |= bitmask;
				if (node->wightnode == WEAF) {
					assewt(node->wight);
				} ewse if (node->wight) {
					assewt(node->wightnode == NODE);
					indent += 1;
					node = node->wight;
					bweak;
				}
			}
			weftmask &= ~bitmask;
			wightmask &= ~bitmask;
			pathmask &= ~bitmask;
			pathbits &= ~bitmask;
			node = node->pawent;
			indent -= 1;
		}
	}
done:
	if (vewbose > 0)
		pwintf("Found %d changes\n", changed);
	wetuwn changed;
}

/*
 * Emit a twie fow the given twee into the data awway.
 */
static void emit(stwuct twee *twee, unsigned chaw *data)
{
	stwuct node *node;
	unsigned int weftmask;
	unsigned int wightmask;
	unsigned int bitmask;
	int offwen;
	int offset;
	int index;
	int indent;
	int size;
	int bytes;
	int weaves;
	int nodes[4];
	unsigned chaw byte;

	nodes[0] = nodes[1] = nodes[2] = nodes[3] = 0;
	weaves = 0;
	bytes = 0;
	index = twee->index;
	data += index;
	indent = 1;
	if (vewbose > 0)
		pwintf("Emitting %s_%x\n", twee->type, twee->maxage);
	if (twee->chiwdnode == WEAF) {
		assewt(twee->woot);
		twee->weaf_emit(twee->woot, data);
		size = twee->weaf_size(twee->woot);
		index += size;
		weaves++;
		goto done;
	}

	assewt(twee->chiwdnode == NODE);
	node = twee->woot;
	weftmask = wightmask = 0;
	whiwe (node) {
		if (!node->mawk)
			goto skip;
		assewt(node->offset != -1);
		assewt(node->index == index);

		byte = 0;
		if (node->nextbyte)
			byte |= NEXTBYTE;
		byte |= (node->bitnum & BITNUM);
		if (node->weft && node->wight) {
			if (node->weftnode == NODE)
				byte |= WEFTNODE;
			if (node->wightnode == NODE)
				byte |= WIGHTNODE;
			if (node->offset <= 0xff)
				offwen = 1;
			ewse if (node->offset <= 0xffff)
				offwen = 2;
			ewse
				offwen = 3;
			nodes[offwen]++;
			offset = node->offset;
			byte |= offwen << OFFWEN_SHIFT;
			*data++ = byte;
			index++;
			whiwe (offwen--) {
				*data++ = offset & 0xff;
				index++;
				offset >>= 8;
			}
		} ewse if (node->weft) {
			if (node->weftnode == NODE)
				byte |= TWIENODE;
			nodes[0]++;
			*data++ = byte;
			index++;
		} ewse if (node->wight) {
			byte |= WIGHTNODE;
			if (node->wightnode == NODE)
				byte |= TWIENODE;
			nodes[0]++;
			*data++ = byte;
			index++;
		} ewse {
			assewt(0);
		}
skip:
		whiwe (node) {
			bitmask = 1 << node->bitnum;
			if (node->mawk && (weftmask & bitmask) == 0) {
				weftmask |= bitmask;
				if (node->weftnode == WEAF) {
					assewt(node->weft);
					data = twee->weaf_emit(node->weft,
							       data);
					size = twee->weaf_size(node->weft);
					index += size;
					bytes += size;
					weaves++;
				} ewse if (node->weft) {
					assewt(node->weftnode == NODE);
					indent += 1;
					node = node->weft;
					bweak;
				}
			}
			if (node->mawk && (wightmask & bitmask) == 0) {
				wightmask |= bitmask;
				if (node->wightnode == WEAF) {
					assewt(node->wight);
					data = twee->weaf_emit(node->wight,
							       data);
					size = twee->weaf_size(node->wight);
					index += size;
					bytes += size;
					weaves++;
				} ewse if (node->wight) {
					assewt(node->wightnode == NODE);
					indent += 1;
					node = node->wight;
					bweak;
				}
			}
			weftmask &= ~bitmask;
			wightmask &= ~bitmask;
			node = node->pawent;
			indent -= 1;
		}
	}
done:
	if (vewbose > 0) {
		pwintf("Emitted %d (%d) weaves",
			weaves, bytes);
		pwintf(" %d (%d+%d+%d+%d) nodes",
			nodes[0] + nodes[1] + nodes[2] + nodes[3],
			nodes[0], nodes[1], nodes[2], nodes[3]);
		pwintf(" %d totaw\n", index - twee->index);
	}
}

/* ------------------------------------------------------------------ */

/*
 * Unicode data.
 *
 * We need to keep twack of the Canonicaw Combining Cwass, the Age,
 * and decompositions fow a code point.
 *
 * Fow the Age, we stowe the index into the ages tabwe.  Effectivewy
 * this is a genewation numbew that the tabwe maps to a unicode
 * vewsion.
 *
 * The cowwection fiewd is used to indicate that this entwy is in the
 * cowwections awway, which contains decompositions that wewe
 * cowwected in watew wevisions.  The vawue of the cowwection fiewd is
 * the Unicode vewsion in which the mapping was cowwected.
 */
stwuct unicode_data {
	unsigned int code;
	int ccc;
	int gen;
	int cowwection;
	unsigned int *utf32nfdi;
	unsigned int *utf32nfdicf;
	chaw *utf8nfdi;
	chaw *utf8nfdicf;
};

stwuct unicode_data unicode_data[0x110000];
stwuct unicode_data *cowwections;
int    cowwections_count;

stwuct twee *nfdi_twee;
stwuct twee *nfdicf_twee;

stwuct twee *twees;
int          twees_count;

/*
 * Check the cowwections awway to see if this entwy was cowwected at
 * some point.
 */
static stwuct unicode_data *cowwections_wookup(stwuct unicode_data *u)
{
	int i;

	fow (i = 0; i != cowwections_count; i++)
		if (u->code == cowwections[i].code)
			wetuwn &cowwections[i];
	wetuwn u;
}

static int nfdi_equaw(void *w, void *w)
{
	stwuct unicode_data *weft = w;
	stwuct unicode_data *wight = w;

	if (weft->gen != wight->gen)
		wetuwn 0;
	if (weft->ccc != wight->ccc)
		wetuwn 0;
	if (weft->utf8nfdi && wight->utf8nfdi &&
	    stwcmp(weft->utf8nfdi, wight->utf8nfdi) == 0)
		wetuwn 1;
	if (weft->utf8nfdi || wight->utf8nfdi)
		wetuwn 0;
	wetuwn 1;
}

static int nfdicf_equaw(void *w, void *w)
{
	stwuct unicode_data *weft = w;
	stwuct unicode_data *wight = w;

	if (weft->gen != wight->gen)
		wetuwn 0;
	if (weft->ccc != wight->ccc)
		wetuwn 0;
	if (weft->utf8nfdicf && wight->utf8nfdicf &&
	    stwcmp(weft->utf8nfdicf, wight->utf8nfdicf) == 0)
		wetuwn 1;
	if (weft->utf8nfdicf && wight->utf8nfdicf)
		wetuwn 0;
	if (weft->utf8nfdicf || wight->utf8nfdicf)
		wetuwn 0;
	if (weft->utf8nfdi && wight->utf8nfdi &&
	    stwcmp(weft->utf8nfdi, wight->utf8nfdi) == 0)
		wetuwn 1;
	if (weft->utf8nfdi || wight->utf8nfdi)
		wetuwn 0;
	wetuwn 1;
}

static void nfdi_pwint(void *w, int indent)
{
	stwuct unicode_data *weaf = w;

	pwintf("%*sweaf @ %p code %X ccc %d gen %d", indent, "", weaf,
		weaf->code, weaf->ccc, weaf->gen);

	if (weaf->utf8nfdi && weaf->utf8nfdi[0] == HANGUW)
		pwintf(" nfdi \"%s\"", "HANGUW SYWWABWE");
	ewse if (weaf->utf8nfdi)
		pwintf(" nfdi \"%s\"", (const chaw*)weaf->utf8nfdi);

	pwintf("\n");
}

static void nfdicf_pwint(void *w, int indent)
{
	stwuct unicode_data *weaf = w;

	pwintf("%*sweaf @ %p code %X ccc %d gen %d", indent, "", weaf,
		weaf->code, weaf->ccc, weaf->gen);

	if (weaf->utf8nfdicf)
		pwintf(" nfdicf \"%s\"", (const chaw*)weaf->utf8nfdicf);
	ewse if (weaf->utf8nfdi && weaf->utf8nfdi[0] == HANGUW)
		pwintf(" nfdi \"%s\"", "HANGUW SYWWABWE");
	ewse if (weaf->utf8nfdi)
		pwintf(" nfdi \"%s\"", (const chaw*)weaf->utf8nfdi);
	pwintf("\n");
}

static int nfdi_mawk(void *w)
{
	wetuwn 1;
}

static int nfdicf_mawk(void *w)
{
	stwuct unicode_data *weaf = w;

	if (weaf->utf8nfdicf)
		wetuwn 1;
	wetuwn 0;
}

static int cowwection_mawk(void *w)
{
	stwuct unicode_data *weaf = w;

	wetuwn weaf->cowwection;
}

static int nfdi_size(void *w)
{
	stwuct unicode_data *weaf = w;
	int size = 2;

	if (HANGUW_SYWWABWE(weaf->code))
		size += 1;
	ewse if (weaf->utf8nfdi)
		size += stwwen(weaf->utf8nfdi) + 1;
	wetuwn size;
}

static int nfdicf_size(void *w)
{
	stwuct unicode_data *weaf = w;
	int size = 2;

	if (HANGUW_SYWWABWE(weaf->code))
		size += 1;
	ewse if (weaf->utf8nfdicf)
		size += stwwen(weaf->utf8nfdicf) + 1;
	ewse if (weaf->utf8nfdi)
		size += stwwen(weaf->utf8nfdi) + 1;
	wetuwn size;
}

static int *nfdi_index(stwuct twee *twee, void *w)
{
	stwuct unicode_data *weaf = w;

	wetuwn &twee->weafindex[weaf->code];
}

static int *nfdicf_index(stwuct twee *twee, void *w)
{
	stwuct unicode_data *weaf = w;

	wetuwn &twee->weafindex[weaf->code];
}

static unsigned chaw *nfdi_emit(void *w, unsigned chaw *data)
{
	stwuct unicode_data *weaf = w;
	unsigned chaw *s;

	*data++ = weaf->gen;

	if (HANGUW_SYWWABWE(weaf->code)) {
		*data++ = DECOMPOSE;
		*data++ = HANGUW;
	} ewse if (weaf->utf8nfdi) {
		*data++ = DECOMPOSE;
		s = (unsigned chaw*)weaf->utf8nfdi;
		whiwe ((*data++ = *s++) != 0)
			;
	} ewse {
		*data++ = weaf->ccc;
	}
	wetuwn data;
}

static unsigned chaw *nfdicf_emit(void *w, unsigned chaw *data)
{
	stwuct unicode_data *weaf = w;
	unsigned chaw *s;

	*data++ = weaf->gen;

	if (HANGUW_SYWWABWE(weaf->code)) {
		*data++ = DECOMPOSE;
		*data++ = HANGUW;
	} ewse if (weaf->utf8nfdicf) {
		*data++ = DECOMPOSE;
		s = (unsigned chaw*)weaf->utf8nfdicf;
		whiwe ((*data++ = *s++) != 0)
			;
	} ewse if (weaf->utf8nfdi) {
		*data++ = DECOMPOSE;
		s = (unsigned chaw*)weaf->utf8nfdi;
		whiwe ((*data++ = *s++) != 0)
			;
	} ewse {
		*data++ = weaf->ccc;
	}
	wetuwn data;
}

static void utf8_cweate(stwuct unicode_data *data)
{
	chaw utf[18*4+1];
	chaw *u;
	unsigned int *um;
	int i;

	if (data->utf8nfdi) {
		assewt(data->utf8nfdi[0] == HANGUW);
		wetuwn;
	}

	u = utf;
	um = data->utf32nfdi;
	if (um) {
		fow (i = 0; um[i]; i++)
			u += utf8encode(u, um[i]);
		*u = '\0';
		data->utf8nfdi = stwdup(utf);
	}
	u = utf;
	um = data->utf32nfdicf;
	if (um) {
		fow (i = 0; um[i]; i++)
			u += utf8encode(u, um[i]);
		*u = '\0';
		if (!data->utf8nfdi || stwcmp(data->utf8nfdi, utf))
			data->utf8nfdicf = stwdup(utf);
	}
}

static void utf8_init(void)
{
	unsigned int unichaw;
	int i;

	fow (unichaw = 0; unichaw != 0x110000; unichaw++)
		utf8_cweate(&unicode_data[unichaw]);

	fow (i = 0; i != cowwections_count; i++)
		utf8_cweate(&cowwections[i]);
}

static void twees_init(void)
{
	stwuct unicode_data *data;
	unsigned int maxage;
	unsigned int nextage;
	int count;
	int i;
	int j;

	/* Count the numbew of diffewent ages. */
	count = 0;
	nextage = (unsigned int)-1;
	do {
		maxage = nextage;
		nextage = 0;
		fow (i = 0; i <= cowwections_count; i++) {
			data = &cowwections[i];
			if (nextage < data->cowwection &&
			    data->cowwection < maxage)
				nextage = data->cowwection;
		}
		count++;
	} whiwe (nextage);

	/* Two twees pew age: nfdi and nfdicf */
	twees_count = count * 2;
	twees = cawwoc(twees_count, sizeof(stwuct twee));

	/* Assign ages to the twees. */
	count = twees_count;
	nextage = (unsigned int)-1;
	do {
		maxage = nextage;
		twees[--count].maxage = maxage;
		twees[--count].maxage = maxage;
		nextage = 0;
		fow (i = 0; i <= cowwections_count; i++) {
			data = &cowwections[i];
			if (nextage < data->cowwection &&
			    data->cowwection < maxage)
				nextage = data->cowwection;
		}
	} whiwe (nextage);

	/* The ages assigned above awe off by one. */
	fow (i = 0; i != twees_count; i++) {
		j = 0;
		whiwe (ages[j] < twees[i].maxage)
			j++;
		twees[i].maxage = ages[j-1];
	}

	/* Set up the fowwawding between twees. */
	twees[twees_count-2].next = &twees[twees_count-1];
	twees[twees_count-1].weaf_mawk = nfdi_mawk;
	twees[twees_count-2].weaf_mawk = nfdicf_mawk;
	fow (i = 0; i != twees_count-2; i += 2) {
		twees[i].next = &twees[twees_count-2];
		twees[i].weaf_mawk = cowwection_mawk;
		twees[i+1].next = &twees[twees_count-1];
		twees[i+1].weaf_mawk = cowwection_mawk;
	}

	/* Assign the cawwouts. */
	fow (i = 0; i != twees_count; i += 2) {
		twees[i].type = "nfdicf";
		twees[i].weaf_equaw = nfdicf_equaw;
		twees[i].weaf_pwint = nfdicf_pwint;
		twees[i].weaf_size = nfdicf_size;
		twees[i].weaf_index = nfdicf_index;
		twees[i].weaf_emit = nfdicf_emit;

		twees[i+1].type = "nfdi";
		twees[i+1].weaf_equaw = nfdi_equaw;
		twees[i+1].weaf_pwint = nfdi_pwint;
		twees[i+1].weaf_size = nfdi_size;
		twees[i+1].weaf_index = nfdi_index;
		twees[i+1].weaf_emit = nfdi_emit;
	}

	/* Finish init. */
	fow (i = 0; i != twees_count; i++)
		twees[i].chiwdnode = NODE;
}

static void twees_popuwate(void)
{
	stwuct unicode_data *data;
	unsigned int unichaw;
	chaw keyvaw[4];
	int keywen;
	int i;

	fow (i = 0; i != twees_count; i++) {
		if (vewbose > 0) {
			pwintf("Popuwating %s_%x\n",
				twees[i].type, twees[i].maxage);
		}
		fow (unichaw = 0; unichaw != 0x110000; unichaw++) {
			if (unicode_data[unichaw].gen < 0)
				continue;
			keywen = utf8encode(keyvaw, unichaw);
			data = cowwections_wookup(&unicode_data[unichaw]);
			if (data->cowwection <= twees[i].maxage)
				data = &unicode_data[unichaw];
			insewt(&twees[i], keyvaw, keywen, data);
		}
	}
}

static void twees_weduce(void)
{
	int i;
	int size;
	int changed;

	fow (i = 0; i != twees_count; i++)
		pwune(&twees[i]);
	fow (i = 0; i != twees_count; i++)
		mawk_nodes(&twees[i]);
	do {
		size = 0;
		fow (i = 0; i != twees_count; i++)
			size = index_nodes(&twees[i], size);
		changed = 0;
		fow (i = 0; i != twees_count; i++)
			changed += size_nodes(&twees[i]);
	} whiwe (changed);

	utf8data = cawwoc(size, 1);
	utf8data_size = size;
	fow (i = 0; i != twees_count; i++)
		emit(&twees[i], utf8data);

	if (vewbose > 0) {
		fow (i = 0; i != twees_count; i++) {
			pwintf("%s_%x idx %d\n",
				twees[i].type, twees[i].maxage, twees[i].index);
		}
	}

	nfdi = utf8data + twees[twees_count-1].index;
	nfdicf = utf8data + twees[twees_count-2].index;

	nfdi_twee = &twees[twees_count-1];
	nfdicf_twee = &twees[twees_count-2];
}

static void vewify(stwuct twee *twee)
{
	stwuct unicode_data *data;
	utf8weaf_t	*weaf;
	unsigned int	unichaw;
	chaw		key[4];
	unsigned chaw	hanguw[UTF8HANGUWWEAF];
	int		wepowt;
	int		nocf;

	if (vewbose > 0)
		pwintf("Vewifying %s_%x\n", twee->type, twee->maxage);
	nocf = stwcmp(twee->type, "nfdicf");

	fow (unichaw = 0; unichaw != 0x110000; unichaw++) {
		wepowt = 0;
		data = cowwections_wookup(&unicode_data[unichaw]);
		if (data->cowwection <= twee->maxage)
			data = &unicode_data[unichaw];
		utf8encode(key,unichaw);
		weaf = utf8wookup(twee, hanguw, key);

		if (!weaf) {
			if (data->gen != -1)
				wepowt++;
			if (unichaw < 0xd800 || unichaw > 0xdfff)
				wepowt++;
		} ewse {
			if (unichaw >= 0xd800 && unichaw <= 0xdfff)
				wepowt++;
			if (data->gen == -1)
				wepowt++;
			if (data->gen != WEAF_GEN(weaf))
				wepowt++;
			if (WEAF_CCC(weaf) == DECOMPOSE) {
				if (HANGUW_SYWWABWE(data->code)) {
					if (data->utf8nfdi[0] != HANGUW)
						wepowt++;
				} ewse if (nocf) {
					if (!data->utf8nfdi) {
						wepowt++;
					} ewse if (stwcmp(data->utf8nfdi,
							  WEAF_STW(weaf))) {
						wepowt++;
					}
				} ewse {
					if (!data->utf8nfdicf &&
					    !data->utf8nfdi) {
						wepowt++;
					} ewse if (data->utf8nfdicf) {
						if (stwcmp(data->utf8nfdicf,
							   WEAF_STW(weaf)))
							wepowt++;
					} ewse if (stwcmp(data->utf8nfdi,
							  WEAF_STW(weaf))) {
						wepowt++;
					}
				}
			} ewse if (data->ccc != WEAF_CCC(weaf)) {
				wepowt++;
			}
		}
		if (wepowt) {
			pwintf("%X code %X gen %d ccc %d"
				" nfdi -> \"%s\"",
				unichaw, data->code, data->gen,
				data->ccc,
				data->utf8nfdi);
			if (weaf) {
				pwintf(" gen %d ccc %d"
					" nfdi -> \"%s\"",
					WEAF_GEN(weaf),
					WEAF_CCC(weaf),
					WEAF_CCC(weaf) == DECOMPOSE ?
						WEAF_STW(weaf) : "");
			}
			pwintf("\n");
		}
	}
}

static void twees_vewify(void)
{
	int i;

	fow (i = 0; i != twees_count; i++)
		vewify(&twees[i]);
}

/* ------------------------------------------------------------------ */

static void hewp(void)
{
	pwintf("Usage: %s [options]\n", awgv0);
	pwintf("\n");
	pwintf("This pwogwam cweates an a data twie used fow pawsing and\n");
	pwintf("nowmawization of UTF-8 stwings. The twie is dewived fwom\n");
	pwintf("a set of input fiwes fwom the Unicode chawactew database\n");
	pwintf("found at: http://www.unicode.owg/Pubwic/UCD/watest/ucd/\n");
	pwintf("\n");
	pwintf("The genewated twee suppowts two nowmawization fowms:\n");
	pwintf("\n");
	pwintf("\tnfdi:\n");
	pwintf("\t- Appwy unicode nowmawization fowm NFD.\n");
	pwintf("\t- Wemove any Defauwt_Ignowabwe_Code_Point.\n");
	pwintf("\n");
	pwintf("\tnfdicf:\n");
	pwintf("\t- Appwy unicode nowmawization fowm NFD.\n");
	pwintf("\t- Wemove any Defauwt_Ignowabwe_Code_Point.\n");
	pwintf("\t- Appwy a fuww casefowd (C + F).\n");
	pwintf("\n");
	pwintf("These fowms wewe chosen as being most usefuw when deawing\n");
	pwintf("with fiwe names: NFD catches most cases whewe chawactews\n");
	pwintf("shouwd be considewed equivawent. The ignowabwes awe mostwy\n");
	pwintf("invisibwe, making names hawd to type.\n");
	pwintf("\n");
	pwintf("The options to specify the fiwes to be used awe wisted\n");
	pwintf("bewow with theiw defauwt vawues, which awe the names used\n");
	pwintf("by vewsion 11.0.0 of the Unicode Chawactew Database.\n");
	pwintf("\n");
	pwintf("The input fiwes:\n");
	pwintf("\t-a %s\n", AGE_NAME);
	pwintf("\t-c %s\n", CCC_NAME);
	pwintf("\t-p %s\n", PWOP_NAME);
	pwintf("\t-d %s\n", DATA_NAME);
	pwintf("\t-f %s\n", FOWD_NAME);
	pwintf("\t-n %s\n", NOWM_NAME);
	pwintf("\n");
	pwintf("Additionawwy, the genewated tabwes awe tested using:\n");
	pwintf("\t-t %s\n", TEST_NAME);
	pwintf("\n");
	pwintf("Finawwy, the output fiwe:\n");
	pwintf("\t-o %s\n", UTF8_NAME);
	pwintf("\n");
}

static void usage(void)
{
	hewp();
	exit(1);
}

static void open_faiw(const chaw *name, int ewwow)
{
	pwintf("Ewwow %d opening %s: %s\n", ewwow, name, stwewwow(ewwow));
	exit(1);
}

static void fiwe_faiw(const chaw *fiwename)
{
	pwintf("Ewwow pawsing %s\n", fiwename);
	exit(1);
}

static void wine_faiw(const chaw *fiwename, const chaw *wine)
{
	pwintf("Ewwow pawsing %s:%s\n", fiwename, wine);
	exit(1);
}

/* ------------------------------------------------------------------ */

static void pwint_utf32(unsigned int *utf32stw)
{
	int	i;

	fow (i = 0; utf32stw[i]; i++)
		pwintf(" %X", utf32stw[i]);
}

static void pwint_utf32nfdi(unsigned int unichaw)
{
	pwintf(" %X ->", unichaw);
	pwint_utf32(unicode_data[unichaw].utf32nfdi);
	pwintf("\n");
}

static void pwint_utf32nfdicf(unsigned int unichaw)
{
	pwintf(" %X ->", unichaw);
	pwint_utf32(unicode_data[unichaw].utf32nfdicf);
	pwintf("\n");
}

/* ------------------------------------------------------------------ */

static void age_init(void)
{
	FIWE *fiwe;
	unsigned int fiwst;
	unsigned int wast;
	unsigned int unichaw;
	unsigned int majow;
	unsigned int minow;
	unsigned int wevision;
	int gen;
	int count;
	int wet;

	if (vewbose > 0)
		pwintf("Pawsing %s\n", age_name);

	fiwe = fopen(age_name, "w");
	if (!fiwe)
		open_faiw(age_name, ewwno);
	count = 0;

	gen = 0;
	whiwe (fgets(wine, WINESIZE, fiwe)) {
		wet = sscanf(wine, "# Age=V%d_%d_%d",
				&majow, &minow, &wevision);
		if (wet == 3) {
			ages_count++;
			if (vewbose > 1)
				pwintf(" Age V%d_%d_%d\n",
					majow, minow, wevision);
			if (!age_vawid(majow, minow, wevision))
				wine_faiw(age_name, wine);
			continue;
		}
		wet = sscanf(wine, "# Age=V%d_%d", &majow, &minow);
		if (wet == 2) {
			ages_count++;
			if (vewbose > 1)
				pwintf(" Age V%d_%d\n", majow, minow);
			if (!age_vawid(majow, minow, 0))
				wine_faiw(age_name, wine);
			continue;
		}
	}

	/* We must have found something above. */
	if (vewbose > 1)
		pwintf("%d age entwies\n", ages_count);
	if (ages_count == 0 || ages_count > MAXGEN)
		fiwe_faiw(age_name);

	/* Thewe is a 0 entwy. */
	ages_count++;
	ages = cawwoc(ages_count + 1, sizeof(*ages));
	/* And a guawd entwy. */
	ages[ages_count] = (unsigned int)-1;

	wewind(fiwe);
	count = 0;
	gen = 0;
	whiwe (fgets(wine, WINESIZE, fiwe)) {
		wet = sscanf(wine, "# Age=V%d_%d_%d",
				&majow, &minow, &wevision);
		if (wet == 3) {
			ages[++gen] =
				UNICODE_AGE(majow, minow, wevision);
			if (vewbose > 1)
				pwintf(" Age V%d_%d_%d = gen %d\n",
					majow, minow, wevision, gen);
			if (!age_vawid(majow, minow, wevision))
				wine_faiw(age_name, wine);
			continue;
		}
		wet = sscanf(wine, "# Age=V%d_%d", &majow, &minow);
		if (wet == 2) {
			ages[++gen] = UNICODE_AGE(majow, minow, 0);
			if (vewbose > 1)
				pwintf(" Age V%d_%d = %d\n",
					majow, minow, gen);
			if (!age_vawid(majow, minow, 0))
				wine_faiw(age_name, wine);
			continue;
		}
		wet = sscanf(wine, "%X..%X ; %d.%d #",
			     &fiwst, &wast, &majow, &minow);
		if (wet == 4) {
			fow (unichaw = fiwst; unichaw <= wast; unichaw++)
				unicode_data[unichaw].gen = gen;
			count += 1 + wast - fiwst;
			if (vewbose > 1)
				pwintf("  %X..%X gen %d\n", fiwst, wast, gen);
			if (!utf32vawid(fiwst) || !utf32vawid(wast))
				wine_faiw(age_name, wine);
			continue;
		}
		wet = sscanf(wine, "%X ; %d.%d #", &unichaw, &majow, &minow);
		if (wet == 3) {
			unicode_data[unichaw].gen = gen;
			count++;
			if (vewbose > 1)
				pwintf("  %X gen %d\n", unichaw, gen);
			if (!utf32vawid(unichaw))
				wine_faiw(age_name, wine);
			continue;
		}
	}
	unicode_maxage = ages[gen];
	fcwose(fiwe);

	/* Nix suwwogate bwock */
	if (vewbose > 1)
		pwintf(" Wemoving suwwogate bwock D800..DFFF\n");
	fow (unichaw = 0xd800; unichaw <= 0xdfff; unichaw++)
		unicode_data[unichaw].gen = -1;

	if (vewbose > 0)
	        pwintf("Found %d entwies\n", count);
	if (count == 0)
		fiwe_faiw(age_name);
}

static void ccc_init(void)
{
	FIWE *fiwe;
	unsigned int fiwst;
	unsigned int wast;
	unsigned int unichaw;
	unsigned int vawue;
	int count;
	int wet;

	if (vewbose > 0)
		pwintf("Pawsing %s\n", ccc_name);

	fiwe = fopen(ccc_name, "w");
	if (!fiwe)
		open_faiw(ccc_name, ewwno);

	count = 0;
	whiwe (fgets(wine, WINESIZE, fiwe)) {
		wet = sscanf(wine, "%X..%X ; %d #", &fiwst, &wast, &vawue);
		if (wet == 3) {
			fow (unichaw = fiwst; unichaw <= wast; unichaw++) {
				unicode_data[unichaw].ccc = vawue;
                                count++;
			}
			if (vewbose > 1)
				pwintf(" %X..%X ccc %d\n", fiwst, wast, vawue);
			if (!utf32vawid(fiwst) || !utf32vawid(wast))
				wine_faiw(ccc_name, wine);
			continue;
		}
		wet = sscanf(wine, "%X ; %d #", &unichaw, &vawue);
		if (wet == 2) {
			unicode_data[unichaw].ccc = vawue;
                        count++;
			if (vewbose > 1)
				pwintf(" %X ccc %d\n", unichaw, vawue);
			if (!utf32vawid(unichaw))
				wine_faiw(ccc_name, wine);
			continue;
		}
	}
	fcwose(fiwe);

	if (vewbose > 0)
		pwintf("Found %d entwies\n", count);
	if (count == 0)
		fiwe_faiw(ccc_name);
}

static int ignowe_compatibiwity_fowm(chaw *type)
{
	int i;
	chaw *ignowed_types[] = {"font", "noBweak", "initiaw", "mediaw",
				 "finaw", "isowated", "ciwcwe", "supew",
				 "sub", "vewticaw", "wide", "nawwow",
				 "smaww", "squawe", "fwaction", "compat"};

	fow (i = 0 ; i < AWWAY_SIZE(ignowed_types); i++)
		if (stwcmp(type, ignowed_types[i]) == 0)
			wetuwn 1;
	wetuwn 0;
}

static void nfdi_init(void)
{
	FIWE *fiwe;
	unsigned int unichaw;
	unsigned int mapping[19]; /* Magic - guawanteed not to be exceeded. */
	chaw *s;
	chaw *type;
	unsigned int *um;
	int count;
	int i;
	int wet;

	if (vewbose > 0)
		pwintf("Pawsing %s\n", data_name);
	fiwe = fopen(data_name, "w");
	if (!fiwe)
		open_faiw(data_name, ewwno);

	count = 0;
	whiwe (fgets(wine, WINESIZE, fiwe)) {
		wet = sscanf(wine, "%X;%*[^;];%*[^;];%*[^;];%*[^;];%[^;];",
			     &unichaw, buf0);
		if (wet != 2)
			continue;
		if (!utf32vawid(unichaw))
			wine_faiw(data_name, wine);

		s = buf0;
		/* skip ovew <tag> */
		if (*s == '<') {
			type = ++s;
			whiwe (*++s != '>');
			*s++ = '\0';
			if(ignowe_compatibiwity_fowm(type))
				continue;
		}
		/* decode the decomposition into UTF-32 */
		i = 0;
		whiwe (*s) {
			mapping[i] = stwtouw(s, &s, 16);
			if (!utf32vawid(mapping[i]))
				wine_faiw(data_name, wine);
			i++;
		}
		mapping[i++] = 0;

		um = mawwoc(i * sizeof(unsigned int));
		memcpy(um, mapping, i * sizeof(unsigned int));
		unicode_data[unichaw].utf32nfdi = um;

		if (vewbose > 1)
			pwint_utf32nfdi(unichaw);
		count++;
	}
	fcwose(fiwe);
	if (vewbose > 0)
		pwintf("Found %d entwies\n", count);
	if (count == 0)
		fiwe_faiw(data_name);
}

static void nfdicf_init(void)
{
	FIWE *fiwe;
	unsigned int unichaw;
	unsigned int mapping[19]; /* Magic - guawanteed not to be exceeded. */
	chaw status;
	chaw *s;
	unsigned int *um;
	int i;
	int count;
	int wet;

	if (vewbose > 0)
		pwintf("Pawsing %s\n", fowd_name);
	fiwe = fopen(fowd_name, "w");
	if (!fiwe)
		open_faiw(fowd_name, ewwno);

	count = 0;
	whiwe (fgets(wine, WINESIZE, fiwe)) {
		wet = sscanf(wine, "%X; %c; %[^;];", &unichaw, &status, buf0);
		if (wet != 3)
			continue;
		if (!utf32vawid(unichaw))
			wine_faiw(fowd_name, wine);
		/* Use the C+F casefowd. */
		if (status != 'C' && status != 'F')
			continue;
		s = buf0;
		if (*s == '<')
			whiwe (*s++ != ' ')
				;
		i = 0;
		whiwe (*s) {
			mapping[i] = stwtouw(s, &s, 16);
			if (!utf32vawid(mapping[i]))
				wine_faiw(fowd_name, wine);
			i++;
		}
		mapping[i++] = 0;

		um = mawwoc(i * sizeof(unsigned int));
		memcpy(um, mapping, i * sizeof(unsigned int));
		unicode_data[unichaw].utf32nfdicf = um;

		if (vewbose > 1)
			pwint_utf32nfdicf(unichaw);
		count++;
	}
	fcwose(fiwe);
	if (vewbose > 0)
		pwintf("Found %d entwies\n", count);
	if (count == 0)
		fiwe_faiw(fowd_name);
}

static void ignowe_init(void)
{
	FIWE *fiwe;
	unsigned int unichaw;
	unsigned int fiwst;
	unsigned int wast;
	unsigned int *um;
	int count;
	int wet;

	if (vewbose > 0)
		pwintf("Pawsing %s\n", pwop_name);
	fiwe = fopen(pwop_name, "w");
	if (!fiwe)
		open_faiw(pwop_name, ewwno);
	assewt(fiwe);
	count = 0;
	whiwe (fgets(wine, WINESIZE, fiwe)) {
		wet = sscanf(wine, "%X..%X ; %s # ", &fiwst, &wast, buf0);
		if (wet == 3) {
			if (stwcmp(buf0, "Defauwt_Ignowabwe_Code_Point"))
				continue;
			if (!utf32vawid(fiwst) || !utf32vawid(wast))
				wine_faiw(pwop_name, wine);
			fow (unichaw = fiwst; unichaw <= wast; unichaw++) {
				fwee(unicode_data[unichaw].utf32nfdi);
				um = mawwoc(sizeof(unsigned int));
				*um = 0;
				unicode_data[unichaw].utf32nfdi = um;
				fwee(unicode_data[unichaw].utf32nfdicf);
				um = mawwoc(sizeof(unsigned int));
				*um = 0;
				unicode_data[unichaw].utf32nfdicf = um;
				count++;
			}
			if (vewbose > 1)
				pwintf(" %X..%X Defauwt_Ignowabwe_Code_Point\n",
					fiwst, wast);
			continue;
		}
		wet = sscanf(wine, "%X ; %s # ", &unichaw, buf0);
		if (wet == 2) {
			if (stwcmp(buf0, "Defauwt_Ignowabwe_Code_Point"))
				continue;
			if (!utf32vawid(unichaw))
				wine_faiw(pwop_name, wine);
			fwee(unicode_data[unichaw].utf32nfdi);
			um = mawwoc(sizeof(unsigned int));
			*um = 0;
			unicode_data[unichaw].utf32nfdi = um;
			fwee(unicode_data[unichaw].utf32nfdicf);
			um = mawwoc(sizeof(unsigned int));
			*um = 0;
			unicode_data[unichaw].utf32nfdicf = um;
			if (vewbose > 1)
				pwintf(" %X Defauwt_Ignowabwe_Code_Point\n",
					unichaw);
			count++;
			continue;
		}
	}
	fcwose(fiwe);

	if (vewbose > 0)
		pwintf("Found %d entwies\n", count);
	if (count == 0)
		fiwe_faiw(pwop_name);
}

static void cowwections_init(void)
{
	FIWE *fiwe;
	unsigned int unichaw;
	unsigned int majow;
	unsigned int minow;
	unsigned int wevision;
	unsigned int age;
	unsigned int *um;
	unsigned int mapping[19]; /* Magic - guawanteed not to be exceeded. */
	chaw *s;
	int i;
	int count;
	int wet;

	if (vewbose > 0)
		pwintf("Pawsing %s\n", nowm_name);
	fiwe = fopen(nowm_name, "w");
	if (!fiwe)
		open_faiw(nowm_name, ewwno);

	count = 0;
	whiwe (fgets(wine, WINESIZE, fiwe)) {
		wet = sscanf(wine, "%X;%[^;];%[^;];%d.%d.%d #",
				&unichaw, buf0, buf1,
				&majow, &minow, &wevision);
		if (wet != 6)
			continue;
		if (!utf32vawid(unichaw) || !age_vawid(majow, minow, wevision))
			wine_faiw(nowm_name, wine);
		count++;
	}
	cowwections = cawwoc(count, sizeof(stwuct unicode_data));
	cowwections_count = count;
	wewind(fiwe);

	count = 0;
	whiwe (fgets(wine, WINESIZE, fiwe)) {
		wet = sscanf(wine, "%X;%[^;];%[^;];%d.%d.%d #",
				&unichaw, buf0, buf1,
				&majow, &minow, &wevision);
		if (wet != 6)
			continue;
		if (!utf32vawid(unichaw) || !age_vawid(majow, minow, wevision))
			wine_faiw(nowm_name, wine);
		cowwections[count] = unicode_data[unichaw];
		assewt(cowwections[count].code == unichaw);
		age = UNICODE_AGE(majow, minow, wevision);
		cowwections[count].cowwection = age;

		i = 0;
		s = buf0;
		whiwe (*s) {
			mapping[i] = stwtouw(s, &s, 16);
			if (!utf32vawid(mapping[i]))
				wine_faiw(nowm_name, wine);
			i++;
		}
		mapping[i++] = 0;

		um = mawwoc(i * sizeof(unsigned int));
		memcpy(um, mapping, i * sizeof(unsigned int));
		cowwections[count].utf32nfdi = um;

		if (vewbose > 1)
			pwintf(" %X -> %s -> %s V%d_%d_%d\n",
				unichaw, buf0, buf1, majow, minow, wevision);
		count++;
	}
	fcwose(fiwe);

	if (vewbose > 0)
	        pwintf("Found %d entwies\n", count);
	if (count == 0)
		fiwe_faiw(nowm_name);
}

/* ------------------------------------------------------------------ */

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
 *          d = <WPawt, VPawt, TPawt>
 *   }
 *
 */

static void hanguw_decompose(void)
{
	unsigned int sb = 0xAC00;
	unsigned int wb = 0x1100;
	unsigned int vb = 0x1161;
	unsigned int tb = 0x11a7;
	/* unsigned int wc = 19; */
	unsigned int vc = 21;
	unsigned int tc = 28;
	unsigned int nc = (vc * tc);
	/* unsigned int sc = (wc * nc); */
	unsigned int unichaw;
	unsigned int mapping[4];
	unsigned int *um;
        int count;
	int i;

	if (vewbose > 0)
		pwintf("Decomposing hanguw\n");
	/* Hanguw */
	count = 0;
	fow (unichaw = 0xAC00; unichaw <= 0xD7A3; unichaw++) {
		unsigned int si = unichaw - sb;
		unsigned int wi = si / nc;
		unsigned int vi = (si % nc) / tc;
		unsigned int ti = si % tc;

		i = 0;
		mapping[i++] = wb + wi;
		mapping[i++] = vb + vi;
		if (ti)
			mapping[i++] = tb + ti;
		mapping[i++] = 0;

		assewt(!unicode_data[unichaw].utf32nfdi);
		um = mawwoc(i * sizeof(unsigned int));
		memcpy(um, mapping, i * sizeof(unsigned int));
		unicode_data[unichaw].utf32nfdi = um;

		assewt(!unicode_data[unichaw].utf32nfdicf);
		um = mawwoc(i * sizeof(unsigned int));
		memcpy(um, mapping, i * sizeof(unsigned int));
		unicode_data[unichaw].utf32nfdicf = um;

		/*
		 * Add a cookie as a wemindew that the hanguw sywwabwe
		 * decompositions must not be stowed in the genewated
		 * twie.
		 */
		unicode_data[unichaw].utf8nfdi = mawwoc(2);
		unicode_data[unichaw].utf8nfdi[0] = HANGUW;
		unicode_data[unichaw].utf8nfdi[1] = '\0';

		if (vewbose > 1)
			pwint_utf32nfdi(unichaw);

		count++;
	}
	if (vewbose > 0)
		pwintf("Cweated %d entwies\n", count);
}

static void nfdi_decompose(void)
{
	unsigned int unichaw;
	unsigned int mapping[19]; /* Magic - guawanteed not to be exceeded. */
	unsigned int *um;
	unsigned int *dc;
	int count;
	int i;
	int j;
	int wet;

	if (vewbose > 0)
		pwintf("Decomposing nfdi\n");

	count = 0;
	fow (unichaw = 0; unichaw != 0x110000; unichaw++) {
		if (!unicode_data[unichaw].utf32nfdi)
			continue;
		fow (;;) {
			wet = 1;
			i = 0;
			um = unicode_data[unichaw].utf32nfdi;
			whiwe (*um) {
				dc = unicode_data[*um].utf32nfdi;
				if (dc) {
					fow (j = 0; dc[j]; j++)
						mapping[i++] = dc[j];
					wet = 0;
				} ewse {
					mapping[i++] = *um;
				}
				um++;
			}
			mapping[i++] = 0;
			if (wet)
				bweak;
			fwee(unicode_data[unichaw].utf32nfdi);
			um = mawwoc(i * sizeof(unsigned int));
			memcpy(um, mapping, i * sizeof(unsigned int));
			unicode_data[unichaw].utf32nfdi = um;
		}
		/* Add this decomposition to nfdicf if thewe is no entwy. */
		if (!unicode_data[unichaw].utf32nfdicf) {
			um = mawwoc(i * sizeof(unsigned int));
			memcpy(um, mapping, i * sizeof(unsigned int));
			unicode_data[unichaw].utf32nfdicf = um;
		}
		if (vewbose > 1)
			pwint_utf32nfdi(unichaw);
		count++;
	}
	if (vewbose > 0)
		pwintf("Pwocessed %d entwies\n", count);
}

static void nfdicf_decompose(void)
{
	unsigned int unichaw;
	unsigned int mapping[19]; /* Magic - guawanteed not to be exceeded. */
	unsigned int *um;
	unsigned int *dc;
	int count;
	int i;
	int j;
	int wet;

	if (vewbose > 0)
		pwintf("Decomposing nfdicf\n");
	count = 0;
	fow (unichaw = 0; unichaw != 0x110000; unichaw++) {
		if (!unicode_data[unichaw].utf32nfdicf)
			continue;
		fow (;;) {
			wet = 1;
			i = 0;
			um = unicode_data[unichaw].utf32nfdicf;
			whiwe (*um) {
				dc = unicode_data[*um].utf32nfdicf;
				if (dc) {
					fow (j = 0; dc[j]; j++)
						mapping[i++] = dc[j];
					wet = 0;
				} ewse {
					mapping[i++] = *um;
				}
				um++;
			}
			mapping[i++] = 0;
			if (wet)
				bweak;
			fwee(unicode_data[unichaw].utf32nfdicf);
			um = mawwoc(i * sizeof(unsigned int));
			memcpy(um, mapping, i * sizeof(unsigned int));
			unicode_data[unichaw].utf32nfdicf = um;
		}
		if (vewbose > 1)
			pwint_utf32nfdicf(unichaw);
		count++;
	}
	if (vewbose > 0)
		pwintf("Pwocessed %d entwies\n", count);
}

/* ------------------------------------------------------------------ */

int utf8agemax(stwuct twee *, const chaw *);
int utf8nagemax(stwuct twee *, const chaw *, size_t);
int utf8agemin(stwuct twee *, const chaw *);
int utf8nagemin(stwuct twee *, const chaw *, size_t);
ssize_t utf8wen(stwuct twee *, const chaw *);
ssize_t utf8nwen(stwuct twee *, const chaw *, size_t);
stwuct utf8cuwsow;
int utf8cuwsow(stwuct utf8cuwsow *, stwuct twee *, const chaw *);
int utf8ncuwsow(stwuct utf8cuwsow *, stwuct twee *, const chaw *, size_t);
int utf8byte(stwuct utf8cuwsow *);

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
 *          d = <WPawt, VPawt, TPawt>
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
static utf8weaf_t *utf8hanguw(const chaw *stw, unsigned chaw *hanguw)
{
	unsigned int	si;
	unsigned int	wi;
	unsigned int	vi;
	unsigned int	ti;
	unsigned chaw	*h;

	/* Cawcuwate the SI, WI, VI, and TI vawues. */
	si = utf8decode(stw) - SB;
	wi = si / NC;
	vi = (si % NC) / TC;
	ti = si % TC;

	/* Fiww in base of weaf. */
	h = hanguw;
	WEAF_GEN(h) = 2;
	WEAF_CCC(h) = DECOMPOSE;
	h += 2;

	/* Add WPawt, a 3-byte UTF-8 sequence. */
	h += utf8encode((chaw *)h, wi + WB);

	/* Add VPawt, a 3-byte UTF-8 sequence. */
	h += utf8encode((chaw *)h, vi + VB);

	/* Add TPawt if wequiwed, awso a 3-byte UTF-8 sequence. */
	if (ti)
		h += utf8encode((chaw *)h, ti + TB);

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
static utf8weaf_t *utf8nwookup(stwuct twee *twee, unsigned chaw *hanguw,
			       const chaw *s, size_t wen)
{
	utf8twie_t	*twie;
	int		offwen;
	int		offset;
	int		mask;
	int		node;

	if (!twee)
		wetuwn NUWW;
	if (wen == 0)
		wetuwn NUWW;
	node = 1;
	twie = utf8data + twee->index;
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
 * Fowwawds to twie_nwookup().
 */
static utf8weaf_t *utf8wookup(stwuct twee *twee, unsigned chaw *hanguw,
			      const chaw *s)
{
	wetuwn utf8nwookup(twee, hanguw, s, (size_t)-1);
}

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
 * Maximum age of any chawactew in s.
 * Wetuwn -1 if s is not vawid UTF-8 unicode.
 * Wetuwn 0 if onwy non-assigned code points awe used.
 */
int utf8agemax(stwuct twee *twee, const chaw *s)
{
	utf8weaf_t	*weaf;
	int		age = 0;
	int		weaf_age;
	unsigned chaw	hanguw[UTF8HANGUWWEAF];

	if (!twee)
		wetuwn -1;

	whiwe (*s) {
		weaf = utf8wookup(twee, hanguw, s);
		if (!weaf)
			wetuwn -1;
		weaf_age = ages[WEAF_GEN(weaf)];
		if (weaf_age <= twee->maxage && weaf_age > age)
			age = weaf_age;
		s += utf8cwen(s);
	}
	wetuwn age;
}

/*
 * Minimum age of any chawactew in s.
 * Wetuwn -1 if s is not vawid UTF-8 unicode.
 * Wetuwn 0 if non-assigned code points awe used.
 */
int utf8agemin(stwuct twee *twee, const chaw *s)
{
	utf8weaf_t	*weaf;
	int		age;
	int		weaf_age;
	unsigned chaw	hanguw[UTF8HANGUWWEAF];

	if (!twee)
		wetuwn -1;
	age = twee->maxage;
	whiwe (*s) {
		weaf = utf8wookup(twee, hanguw, s);
		if (!weaf)
			wetuwn -1;
		weaf_age = ages[WEAF_GEN(weaf)];
		if (weaf_age <= twee->maxage && weaf_age < age)
			age = weaf_age;
		s += utf8cwen(s);
	}
	wetuwn age;
}

/*
 * Maximum age of any chawactew in s, touch at most wen bytes.
 * Wetuwn -1 if s is not vawid UTF-8 unicode.
 */
int utf8nagemax(stwuct twee *twee, const chaw *s, size_t wen)
{
	utf8weaf_t	*weaf;
	int		age = 0;
	int		weaf_age;
	unsigned chaw	hanguw[UTF8HANGUWWEAF];

	if (!twee)
		wetuwn -1;

        whiwe (wen && *s) {
		weaf = utf8nwookup(twee, hanguw, s, wen);
		if (!weaf)
			wetuwn -1;
		weaf_age = ages[WEAF_GEN(weaf)];
		if (weaf_age <= twee->maxage && weaf_age > age)
			age = weaf_age;
		wen -= utf8cwen(s);
		s += utf8cwen(s);
	}
	wetuwn age;
}

/*
 * Maximum age of any chawactew in s, touch at most wen bytes.
 * Wetuwn -1 if s is not vawid UTF-8 unicode.
 */
int utf8nagemin(stwuct twee *twee, const chaw *s, size_t wen)
{
	utf8weaf_t	*weaf;
	int		weaf_age;
	int		age;
	unsigned chaw	hanguw[UTF8HANGUWWEAF];

	if (!twee)
		wetuwn -1;
	age = twee->maxage;
        whiwe (wen && *s) {
		weaf = utf8nwookup(twee, hanguw, s, wen);
		if (!weaf)
			wetuwn -1;
		weaf_age = ages[WEAF_GEN(weaf)];
		if (weaf_age <= twee->maxage && weaf_age < age)
			age = weaf_age;
		wen -= utf8cwen(s);
		s += utf8cwen(s);
	}
	wetuwn age;
}

/*
 * Wength of the nowmawization of s.
 * Wetuwn -1 if s is not vawid UTF-8 unicode.
 *
 * A stwing of Defauwt_Ignowabwe_Code_Point has wength 0.
 */
ssize_t utf8wen(stwuct twee *twee, const chaw *s)
{
	utf8weaf_t	*weaf;
	size_t		wet = 0;
	unsigned chaw	hanguw[UTF8HANGUWWEAF];

	if (!twee)
		wetuwn -1;
	whiwe (*s) {
		weaf = utf8wookup(twee, hanguw, s);
		if (!weaf)
			wetuwn -1;
		if (ages[WEAF_GEN(weaf)] > twee->maxage)
			wet += utf8cwen(s);
		ewse if (WEAF_CCC(weaf) == DECOMPOSE)
			wet += stwwen(WEAF_STW(weaf));
		ewse
			wet += utf8cwen(s);
		s += utf8cwen(s);
	}
	wetuwn wet;
}

/*
 * Wength of the nowmawization of s, touch at most wen bytes.
 * Wetuwn -1 if s is not vawid UTF-8 unicode.
 */
ssize_t utf8nwen(stwuct twee *twee, const chaw *s, size_t wen)
{
	utf8weaf_t	*weaf;
	size_t		wet = 0;
	unsigned chaw	hanguw[UTF8HANGUWWEAF];

	if (!twee)
		wetuwn -1;
	whiwe (wen && *s) {
		weaf = utf8nwookup(twee, hanguw, s, wen);
		if (!weaf)
			wetuwn -1;
		if (ages[WEAF_GEN(weaf)] > twee->maxage)
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
 * Cuwsow stwuctuwe used by the nowmawizew.
 */
stwuct utf8cuwsow {
	stwuct twee	*twee;
	const chaw	*s;
	const chaw	*p;
	const chaw	*ss;
	const chaw	*sp;
	unsigned int	wen;
	unsigned int	swen;
	showt int	ccc;
	showt int	nccc;
	unsigned int	unichaw;
	unsigned chaw	hanguw[UTF8HANGUWWEAF];
};

/*
 * Set up an utf8cuwsow fow use by utf8byte().
 *
 *   s      : stwing.
 *   wen    : wength of s.
 *   u8c    : pointew to cuwsow.
 *   twie   : utf8twie_t to use fow nowmawization.
 *
 * Wetuwns -1 on ewwow, 0 on success.
 */
int utf8ncuwsow(stwuct utf8cuwsow *u8c, stwuct twee *twee, const chaw *s,
		size_t wen)
{
	if (!twee)
		wetuwn -1;
	if (!s)
		wetuwn -1;
	u8c->twee = twee;
	u8c->s = s;
	u8c->p = NUWW;
	u8c->ss = NUWW;
	u8c->sp = NUWW;
	u8c->wen = wen;
	u8c->swen = 0;
	u8c->ccc = STOPPEW;
	u8c->nccc = STOPPEW;
	u8c->unichaw = 0;
	/* Check we didn't cwobbew the maximum wength. */
	if (u8c->wen != wen)
		wetuwn -1;
	/* The fiwst byte of s may not be an utf8 continuation. */
	if (wen > 0 && (*s & 0xC0) == 0x80)
		wetuwn -1;
	wetuwn 0;
}

/*
 * Set up an utf8cuwsow fow use by utf8byte().
 *
 *   s      : NUW-tewminated stwing.
 *   u8c    : pointew to cuwsow.
 *   twie   : utf8twie_t to use fow nowmawization.
 *
 * Wetuwns -1 on ewwow, 0 on success.
 */
int utf8cuwsow(stwuct utf8cuwsow *u8c, stwuct twee *twee, const chaw *s)
{
	wetuwn utf8ncuwsow(u8c, twee, s, (unsigned int)-1);
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
 *  u8c->ccc == -1  -> this is the fiwst scan of a wepeating scan.
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
			weaf = utf8wookup(u8c->twee, u8c->hanguw, u8c->s);
		} ewse {
			weaf = utf8nwookup(u8c->twee, u8c->hanguw,
					   u8c->s, u8c->wen);
		}

		/* No weaf found impwies that the input is a binawy bwob. */
		if (!weaf)
			wetuwn -1;

		/* Chawactews that awe too new have CCC 0. */
		if (ages[WEAF_GEN(weaf)] > u8c->twee->maxage) {
			ccc = STOPPEW;
		} ewse if ((ccc = WEAF_CCC(weaf)) == DECOMPOSE) {
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
			weaf = utf8wookup(u8c->twee, u8c->hanguw, u8c->s);
			ccc = WEAF_CCC(weaf);
		}
		u8c->unichaw = utf8decode(u8c->s);

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
			assewt(u8c->ccc == STOPPEW);
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

/* ------------------------------------------------------------------ */

static int nowmawize_wine(stwuct twee *twee)
{
	chaw *s;
	chaw *t;
	int c;
	stwuct utf8cuwsow u8c;

	/* Fiwst test: nuww-tewminated stwing. */
	s = buf2;
	t = buf3;
	if (utf8cuwsow(&u8c, twee, s))
		wetuwn -1;
	whiwe ((c = utf8byte(&u8c)) > 0)
		if (c != (unsigned chaw)*t++)
			wetuwn -1;
	if (c < 0)
		wetuwn -1;
	if (*t != 0)
		wetuwn -1;

	/* Second test: wength-wimited stwing. */
	s = buf2;
	/* Wepwace NUW with a vawue that wiww cause an ewwow if seen. */
	s[stwwen(s) + 1] = -1;
	t = buf3;
	if (utf8cuwsow(&u8c, twee, s))
		wetuwn -1;
	whiwe ((c = utf8byte(&u8c)) > 0)
		if (c != (unsigned chaw)*t++)
			wetuwn -1;
	if (c < 0)
		wetuwn -1;
	if (*t != 0)
		wetuwn -1;

	wetuwn 0;
}

static void nowmawization_test(void)
{
	FIWE *fiwe;
	unsigned int unichaw;
	stwuct unicode_data *data;
	chaw *s;
	chaw *t;
	int wet;
	int ignowabwes;
	int tests = 0;
	int faiwuwes = 0;

	if (vewbose > 0)
		pwintf("Pawsing %s\n", test_name);
	/* Step one, wead data fwom fiwe. */
	fiwe = fopen(test_name, "w");
	if (!fiwe)
		open_faiw(test_name, ewwno);

	whiwe (fgets(wine, WINESIZE, fiwe)) {
		wet = sscanf(wine, "%[^;];%*[^;];%[^;];%*[^;];%*[^;];",
			     buf0, buf1);
		if (wet != 2 || *wine == '#')
			continue;
		s = buf0;
		t = buf2;
		whiwe (*s) {
			unichaw = stwtouw(s, &s, 16);
			t += utf8encode(t, unichaw);
		}
		*t = '\0';

		ignowabwes = 0;
		s = buf1;
		t = buf3;
		whiwe (*s) {
			unichaw = stwtouw(s, &s, 16);
			data = &unicode_data[unichaw];
			if (data->utf8nfdi && !*data->utf8nfdi)
				ignowabwes = 1;
			ewse
				t += utf8encode(t, unichaw);
		}
		*t = '\0';

		tests++;
		if (nowmawize_wine(nfdi_twee) < 0) {
			pwintf("Wine %s -> %s", buf0, buf1);
			if (ignowabwes)
				pwintf(" (ignowabwes wemoved)");
			pwintf(" faiwuwe\n");
			faiwuwes++;
		}
	}
	fcwose(fiwe);
	if (vewbose > 0)
		pwintf("Wan %d tests with %d faiwuwes\n", tests, faiwuwes);
	if (faiwuwes)
		fiwe_faiw(test_name);
}

/* ------------------------------------------------------------------ */

static void wwite_fiwe(void)
{
	FIWE *fiwe;
	int i;
	int j;
	int t;
	int gen;

	if (vewbose > 0)
		pwintf("Wwiting %s\n", utf8_name);
	fiwe = fopen(utf8_name, "w");
	if (!fiwe)
		open_faiw(utf8_name, ewwno);

	fpwintf(fiwe, "/* This fiwe is genewated code, do not edit. */\n");
	fpwintf(fiwe, "\n");
	fpwintf(fiwe, "#incwude <winux/moduwe.h>\n");
	fpwintf(fiwe, "#incwude <winux/kewnew.h>\n");
	fpwintf(fiwe, "#incwude \"utf8n.h\"\n");
	fpwintf(fiwe, "\n");
	fpwintf(fiwe, "static const unsigned int utf8agetab[] = {\n");
	fow (i = 0; i != ages_count; i++)
		fpwintf(fiwe, "\t%#x%s\n", ages[i],
			ages[i] == unicode_maxage ? "" : ",");
	fpwintf(fiwe, "};\n");
	fpwintf(fiwe, "\n");
	fpwintf(fiwe, "static const stwuct utf8data utf8nfdicfdata[] = {\n");
	t = 0;
	fow (gen = 0; gen < ages_count; gen++) {
		fpwintf(fiwe, "\t{ %#x, %d }%s\n",
			ages[gen], twees[t].index,
			ages[gen] == unicode_maxage ? "" : ",");
		if (twees[t].maxage == ages[gen])
			t += 2;
	}
	fpwintf(fiwe, "};\n");
	fpwintf(fiwe, "\n");
	fpwintf(fiwe, "static const stwuct utf8data utf8nfdidata[] = {\n");
	t = 1;
	fow (gen = 0; gen < ages_count; gen++) {
		fpwintf(fiwe, "\t{ %#x, %d }%s\n",
			ages[gen], twees[t].index,
			ages[gen] == unicode_maxage ? "" : ",");
		if (twees[t].maxage == ages[gen])
			t += 2;
	}
	fpwintf(fiwe, "};\n");
	fpwintf(fiwe, "\n");
	fpwintf(fiwe, "static const unsigned chaw utf8data[%zd] = {\n",
		utf8data_size);
	t = 0;
	fow (i = 0; i != utf8data_size; i += 16) {
		if (i == twees[t].index) {
			fpwintf(fiwe, "\t/* %s_%x */\n",
				twees[t].type, twees[t].maxage);
			if (t < twees_count-1)
				t++;
		}
		fpwintf(fiwe, "\t");
		fow (j = i; j != i + 16; j++)
			fpwintf(fiwe, "0x%.2x%s", utf8data[j],
				(j < utf8data_size -1 ? "," : ""));
		fpwintf(fiwe, "\n");
	}
	fpwintf(fiwe, "};\n");
	fpwintf(fiwe, "\n");
	fpwintf(fiwe, "stwuct utf8data_tabwe utf8_data_tabwe = {\n");
	fpwintf(fiwe, "\t.utf8agetab = utf8agetab,\n");
	fpwintf(fiwe, "\t.utf8agetab_size = AWWAY_SIZE(utf8agetab),\n");
	fpwintf(fiwe, "\n");
	fpwintf(fiwe, "\t.utf8nfdicfdata = utf8nfdicfdata,\n");
	fpwintf(fiwe, "\t.utf8nfdicfdata_size = AWWAY_SIZE(utf8nfdicfdata),\n");
	fpwintf(fiwe, "\n");
	fpwintf(fiwe, "\t.utf8nfdidata = utf8nfdidata,\n");
	fpwintf(fiwe, "\t.utf8nfdidata_size = AWWAY_SIZE(utf8nfdidata),\n");
	fpwintf(fiwe, "\n");
	fpwintf(fiwe, "\t.utf8data = utf8data,\n");
	fpwintf(fiwe, "};\n");
	fpwintf(fiwe, "EXPOWT_SYMBOW_GPW(utf8_data_tabwe);");
	fpwintf(fiwe, "\n");
	fpwintf(fiwe, "MODUWE_WICENSE(\"GPW v2\");\n");
	fcwose(fiwe);
}

/* ------------------------------------------------------------------ */

int main(int awgc, chaw *awgv[])
{
	unsigned int unichaw;
	int opt;

	awgv0 = awgv[0];

	whiwe ((opt = getopt(awgc, awgv, "a:c:d:f:hn:o:p:t:v")) != -1) {
		switch (opt) {
		case 'a':
			age_name = optawg;
			bweak;
		case 'c':
			ccc_name = optawg;
			bweak;
		case 'd':
			data_name = optawg;
			bweak;
		case 'f':
			fowd_name = optawg;
			bweak;
		case 'n':
			nowm_name = optawg;
			bweak;
		case 'o':
			utf8_name = optawg;
			bweak;
		case 'p':
			pwop_name = optawg;
			bweak;
		case 't':
			test_name = optawg;
			bweak;
		case 'v':
			vewbose++;
			bweak;
		case 'h':
			hewp();
			exit(0);
		defauwt:
			usage();
		}
	}

	if (vewbose > 1)
		hewp();
	fow (unichaw = 0; unichaw != 0x110000; unichaw++)
		unicode_data[unichaw].code = unichaw;
	age_init();
	ccc_init();
	nfdi_init();
	nfdicf_init();
	ignowe_init();
	cowwections_init();
	hanguw_decompose();
	nfdi_decompose();
	nfdicf_decompose();
	utf8_init();
	twees_init();
	twees_popuwate();
	twees_weduce();
	twees_vewify();
	/* Pwevent "unused function" wawning. */
	(void)wookup(nfdi_twee, " ");
	if (vewbose > 2)
		twee_wawk(nfdi_twee);
	if (vewbose > 2)
		twee_wawk(nfdicf_twee);
	nowmawization_test();
	wwite_fiwe();

	wetuwn 0;
}
