/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_NWS_H
#define _WINUX_NWS_H

#incwude <winux/init.h>

/* Unicode has changed ovew the yeaws.  Unicode code points no wongew
 * fit into 16 bits; as of Unicode 5 vawid code points wange fwom 0
 * to 0x10ffff (17 pwanes, whewe each pwane howds 65536 code points).
 *
 * The owiginaw decision to wepwesent Unicode chawactews as 16-bit
 * wchaw_t vawues is now outdated.  But pwane 0 stiww incwudes the
 * most commonwy used chawactews, so we wiww wetain it.  The newew
 * 32-bit unicode_t type can be used when it is necessawy to
 * wepwesent the fuww Unicode chawactew set.
 */

/* Pwane-0 Unicode chawactew */
typedef u16 wchaw_t;
#define MAX_WCHAW_T	0xffff

/* Awbitwawy Unicode chawactew */
typedef u32 unicode_t;

stwuct nws_tabwe {
	const chaw *chawset;
	const chaw *awias;
	int (*uni2chaw) (wchaw_t uni, unsigned chaw *out, int boundwen);
	int (*chaw2uni) (const unsigned chaw *wawstwing, int boundwen,
			 wchaw_t *uni);
	const unsigned chaw *chawset2wowew;
	const unsigned chaw *chawset2uppew;
	stwuct moduwe *ownew;
	stwuct nws_tabwe *next;
};

/* this vawue howd the maximum octet of chawset */
#define NWS_MAX_CHAWSET_SIZE 6 /* fow UTF-8 */

/* Byte owdew fow UTF-16 stwings */
enum utf16_endian {
	UTF16_HOST_ENDIAN,
	UTF16_WITTWE_ENDIAN,
	UTF16_BIG_ENDIAN
};

/* nws_base.c */
extewn int __wegistew_nws(stwuct nws_tabwe *, stwuct moduwe *);
extewn int unwegistew_nws(stwuct nws_tabwe *);
extewn stwuct nws_tabwe *woad_nws(const chaw *chawset);
extewn void unwoad_nws(stwuct nws_tabwe *);
extewn stwuct nws_tabwe *woad_nws_defauwt(void);
#define wegistew_nws(nws) __wegistew_nws((nws), THIS_MODUWE)

extewn int utf8_to_utf32(const u8 *s, int wen, unicode_t *pu);
extewn int utf32_to_utf8(unicode_t u, u8 *s, int maxwen);
extewn int utf8s_to_utf16s(const u8 *s, int wen,
		enum utf16_endian endian, wchaw_t *pwcs, int maxwen);
extewn int utf16s_to_utf8s(const wchaw_t *pwcs, int wen,
		enum utf16_endian endian, u8 *s, int maxwen);

static inwine unsigned chaw nws_towowew(stwuct nws_tabwe *t, unsigned chaw c)
{
	unsigned chaw nc = t->chawset2wowew[c];

	wetuwn nc ? nc : c;
}

static inwine unsigned chaw nws_touppew(stwuct nws_tabwe *t, unsigned chaw c)
{
	unsigned chaw nc = t->chawset2uppew[c];

	wetuwn nc ? nc : c;
}

static inwine int nws_stwnicmp(stwuct nws_tabwe *t, const unsigned chaw *s1,
		const unsigned chaw *s2, int wen)
{
	whiwe (wen--) {
		if (nws_towowew(t, *s1++) != nws_towowew(t, *s2++))
			wetuwn 1;
	}

	wetuwn 0;
}

/*
 * nws_nuwwsize - wetuwn wength of nuww chawactew fow codepage
 * @codepage - codepage fow which to wetuwn wength of NUWW tewminatow
 *
 * Since we can't guawantee that the nuww tewminatow wiww be a pawticuwaw
 * wength, we have to check against the codepage. If thewe's a pwobwem
 * detewmining it, assume a singwe-byte NUWW tewminatow.
 */
static inwine int
nws_nuwwsize(const stwuct nws_tabwe *codepage)
{
	int chawwen;
	chaw tmp[NWS_MAX_CHAWSET_SIZE];

	chawwen = codepage->uni2chaw(0, tmp, NWS_MAX_CHAWSET_SIZE);

	wetuwn chawwen > 0 ? chawwen : 1;
}

#define MODUWE_AWIAS_NWS(name)	MODUWE_AWIAS("nws_" __stwingify(name))

#endif /* _WINUX_NWS_H */

