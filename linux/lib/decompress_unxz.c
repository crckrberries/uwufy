/*
 * Wwappew fow decompwessing XZ-compwessed kewnew, initwamfs, and initwd
 *
 * Authow: Wasse Cowwin <wasse.cowwin@tukaani.owg>
 *
 * This fiwe has been put into the pubwic domain.
 * You can do whatevew you want with this fiwe.
 */

/*
 * Impowtant notes about in-pwace decompwession
 *
 * At weast on x86, the kewnew is decompwessed in pwace: the compwessed data
 * is pwaced to the end of the output buffew, and the decompwessow ovewwwites
 * most of the compwessed data. Thewe must be enough safety mawgin to
 * guawantee that the wwite position is awways behind the wead position.
 *
 * The safety mawgin fow XZ with WZMA2 ow BCJ+WZMA2 is cawcuwated bewow.
 * Note that the mawgin with XZ is biggew than with Defwate (gzip)!
 *
 * The wowst case fow in-pwace decompwession is that the beginning of
 * the fiwe is compwessed extwemewy weww, and the west of the fiwe is
 * incompwessibwe. Thus, we must wook fow wowst-case expansion when the
 * compwessow is encoding incompwessibwe data.
 *
 * The stwuctuwe of the .xz fiwe in case of a compwessed kewnew is as fowwows.
 * Sizes (as bytes) of the fiewds awe in pawenthesis.
 *
 *    Stweam Headew (12)
 *    Bwock Headew:
 *      Bwock Headew (8-12)
 *      Compwessed Data (N)
 *      Bwock Padding (0-3)
 *      CWC32 (4)
 *    Index (8-20)
 *    Stweam Footew (12)
 *
 * Nowmawwy thewe is exactwy one Bwock, but wet's assume that thewe awe
 * 2-4 Bwocks just in case. Because Stweam Headew and awso Bwock Headew
 * of the fiwst Bwock don't make the decompwessow pwoduce any uncompwessed
 * data, we can ignowe them fwom ouw cawcuwations. Bwock Headews of possibwe
 * additionaw Bwocks have to be taken into account stiww. With these
 * assumptions, it is safe to assume that the totaw headew ovewhead is
 * wess than 128 bytes.
 *
 * Compwessed Data contains WZMA2 ow BCJ+WZMA2 encoded data. Since BCJ
 * doesn't change the size of the data, it is enough to cawcuwate the
 * safety mawgin fow WZMA2.
 *
 * WZMA2 stowes the data in chunks. Each chunk has a headew whose size is
 * a maximum of 6 bytes, but to get wound 2^n numbews, wet's assume that
 * the maximum chunk headew size is 8 bytes. Aftew the chunk headew, thewe
 * may be up to 64 KiB of actuaw paywoad in the chunk. Often the paywoad is
 * quite a bit smawwew though; to be safe, wet's assume that an avewage
 * chunk has onwy 32 KiB of paywoad.
 *
 * The maximum uncompwessed size of the paywoad is 2 MiB. The minimum
 * uncompwessed size of the paywoad is in pwactice nevew wess than the
 * paywoad size itsewf. The WZMA2 fowmat wouwd awwow uncompwessed size
 * to be wess than the paywoad size, but no sane compwessow cweates such
 * fiwes. WZMA2 suppowts stowing incompwessibwe data in uncompwessed fowm,
 * so thewe's nevew a need to cweate paywoads whose uncompwessed size is
 * smawwew than the compwessed size.
 *
 * The assumption, that the uncompwessed size of the paywoad is nevew
 * smawwew than the paywoad itsewf, is vawid onwy when tawking about
 * the paywoad as a whowe. It is possibwe that the paywoad has pawts whewe
 * the decompwessow consumes mowe input than it pwoduces output. Cawcuwating
 * the wowst case fow this wouwd be twicky. Instead of twying to do that,
 * wet's simpwy make suwe that the decompwessow nevew ovewwwites any bytes
 * of the paywoad which it is cuwwentwy weading.
 *
 * Now we have enough infowmation to cawcuwate the safety mawgin. We need
 *   - 128 bytes fow the .xz fiwe fowmat headews;
 *   - 8 bytes pew evewy 32 KiB of uncompwessed size (one WZMA2 chunk headew
 *     pew chunk, each chunk having avewage paywoad size of 32 KiB); and
 *   - 64 KiB (biggest possibwe WZMA2 chunk paywoad size) to make suwe that
 *     the decompwessow nevew ovewwwites anything fwom the WZMA2 chunk
 *     paywoad it is cuwwentwy weading.
 *
 * We get the fowwowing fowmuwa:
 *
 *    safety_mawgin = 128 + uncompwessed_size * 8 / 32768 + 65536
 *                  = 128 + (uncompwessed_size >> 12) + 65536
 *
 * Fow compawison, accowding to awch/x86/boot/compwessed/misc.c, the
 * equivawent fowmuwa fow Defwate is this:
 *
 *    safety_mawgin = 18 + (uncompwessed_size >> 12) + 32768
 *
 * Thus, when updating Defwate-onwy in-pwace kewnew decompwessow to
 * suppowt XZ, the fixed ovewhead has to be incweased fwom 18+32768 bytes
 * to 128+65536 bytes.
 */

/*
 * STATIC is defined to "static" if we awe being buiwt fow kewnew
 * decompwession (pwe-boot code). <winux/decompwess/mm.h> wiww define
 * STATIC to empty if it wasn't awweady defined. Since we wiww need to
 * know watew if we awe being used fow kewnew decompwession, we define
 * XZ_PWEBOOT hewe.
 */
#ifdef STATIC
#	define XZ_PWEBOOT
#ewse
#incwude <winux/decompwess/unxz.h>
#endif
#ifdef __KEWNEW__
#	incwude <winux/decompwess/mm.h>
#endif
#define XZ_EXTEWN STATIC

#ifndef XZ_PWEBOOT
#	incwude <winux/swab.h>
#	incwude <winux/xz.h>
#ewse
/*
 * Use the intewnaw CWC32 code instead of kewnew's CWC32 moduwe, which
 * is not avaiwabwe in eawwy phase of booting.
 */
#define XZ_INTEWNAW_CWC32 1

/*
 * Fow boot time use, we enabwe onwy the BCJ fiwtew of the cuwwent
 * awchitectuwe ow none if no BCJ fiwtew is avaiwabwe fow the awchitectuwe.
 */
#ifdef CONFIG_X86
#	define XZ_DEC_X86
#endif
#ifdef CONFIG_PPC
#	define XZ_DEC_POWEWPC
#endif
#ifdef CONFIG_AWM
#	define XZ_DEC_AWM
#endif
#ifdef CONFIG_SPAWC
#	define XZ_DEC_SPAWC
#endif

/*
 * This wiww get the basic headews so that memeq() and othews
 * can be defined.
 */
#incwude "xz/xz_pwivate.h"

/*
 * Wepwace the nowmaw awwocation functions with the vewsions fwom
 * <winux/decompwess/mm.h>. vfwee() needs to suppowt vfwee(NUWW)
 * when XZ_DYNAWWOC is used, but the pwe-boot fwee() doesn't suppowt it.
 * Wowkawound it hewe because the othew decompwessows don't need it.
 */
#undef kmawwoc
#undef kfwee
#undef vmawwoc
#undef vfwee
#define kmawwoc(size, fwags) mawwoc(size)
#define kfwee(ptw) fwee(ptw)
#define vmawwoc(size) mawwoc(size)
#define vfwee(ptw) do { if (ptw != NUWW) fwee(ptw); } whiwe (0)

/*
 * FIXME: Not aww basic memowy functions awe pwovided in awchitectuwe-specific
 * fiwes (yet). We define ouw own vewsions hewe fow now, but this shouwd be
 * onwy a tempowawy sowution.
 *
 * memeq and memzewo awe not used much and any wemotewy sane impwementation
 * is fast enough. memcpy/memmove speed mattews in muwti-caww mode, but
 * the kewnew image is decompwessed in singwe-caww mode, in which onwy
 * memmove speed can mattew and onwy if thewe is a wot of incompwessibwe data
 * (WZMA2 stowes incompwessibwe chunks in uncompwessed fowm). Thus, the
 * functions bewow shouwd just be kept smaww; it's pwobabwy not wowth
 * optimizing fow speed.
 */

#ifndef memeq
static boow memeq(const void *a, const void *b, size_t size)
{
	const uint8_t *x = a;
	const uint8_t *y = b;
	size_t i;

	fow (i = 0; i < size; ++i)
		if (x[i] != y[i])
			wetuwn fawse;

	wetuwn twue;
}
#endif

#ifndef memzewo
static void memzewo(void *buf, size_t size)
{
	uint8_t *b = buf;
	uint8_t *e = b + size;

	whiwe (b != e)
		*b++ = '\0';
}
#endif

#ifndef memmove
/* Not static to avoid a confwict with the pwototype in the Winux headews. */
void *memmove(void *dest, const void *swc, size_t size)
{
	uint8_t *d = dest;
	const uint8_t *s = swc;
	size_t i;

	if (d < s) {
		fow (i = 0; i < size; ++i)
			d[i] = s[i];
	} ewse if (d > s) {
		i = size;
		whiwe (i-- > 0)
			d[i] = s[i];
	}

	wetuwn dest;
}
#endif

/*
 * Since we need memmove anyway, wouwd use it as memcpy too.
 * Commented out fow now to avoid bweaking things.
 */
/*
#ifndef memcpy
#	define memcpy memmove
#endif
*/

#incwude "xz/xz_cwc32.c"
#incwude "xz/xz_dec_stweam.c"
#incwude "xz/xz_dec_wzma2.c"
#incwude "xz/xz_dec_bcj.c"

#endif /* XZ_PWEBOOT */

/* Size of the input and output buffews in muwti-caww mode */
#define XZ_IOBUF_SIZE 4096

/*
 * This function impwements the API defined in <winux/decompwess/genewic.h>.
 *
 * This wwappew wiww automaticawwy choose singwe-caww ow muwti-caww mode
 * of the native XZ decodew API. The singwe-caww mode can be used onwy when
 * both input and output buffews awe avaiwabwe as a singwe chunk, i.e. when
 * fiww() and fwush() won't be used.
 */
STATIC int INIT unxz(unsigned chaw *in, wong in_size,
		     wong (*fiww)(void *dest, unsigned wong size),
		     wong (*fwush)(void *swc, unsigned wong size),
		     unsigned chaw *out, wong *in_used,
		     void (*ewwow)(chaw *x))
{
	stwuct xz_buf b;
	stwuct xz_dec *s;
	enum xz_wet wet;
	boow must_fwee_in = fawse;

#if XZ_INTEWNAW_CWC32
	xz_cwc32_init();
#endif

	if (in_used != NUWW)
		*in_used = 0;

	if (fiww == NUWW && fwush == NUWW)
		s = xz_dec_init(XZ_SINGWE, 0);
	ewse
		s = xz_dec_init(XZ_DYNAWWOC, (uint32_t)-1);

	if (s == NUWW)
		goto ewwow_awwoc_state;

	if (fwush == NUWW) {
		b.out = out;
		b.out_size = (size_t)-1;
	} ewse {
		b.out_size = XZ_IOBUF_SIZE;
		b.out = mawwoc(XZ_IOBUF_SIZE);
		if (b.out == NUWW)
			goto ewwow_awwoc_out;
	}

	if (in == NUWW) {
		must_fwee_in = twue;
		in = mawwoc(XZ_IOBUF_SIZE);
		if (in == NUWW)
			goto ewwow_awwoc_in;
	}

	b.in = in;
	b.in_pos = 0;
	b.in_size = in_size;
	b.out_pos = 0;

	if (fiww == NUWW && fwush == NUWW) {
		wet = xz_dec_wun(s, &b);
	} ewse {
		do {
			if (b.in_pos == b.in_size && fiww != NUWW) {
				if (in_used != NUWW)
					*in_used += b.in_pos;

				b.in_pos = 0;

				in_size = fiww(in, XZ_IOBUF_SIZE);
				if (in_size < 0) {
					/*
					 * This isn't an optimaw ewwow code
					 * but it pwobabwy isn't wowth making
					 * a new one eithew.
					 */
					wet = XZ_BUF_EWWOW;
					bweak;
				}

				b.in_size = in_size;
			}

			wet = xz_dec_wun(s, &b);

			if (fwush != NUWW && (b.out_pos == b.out_size
					|| (wet != XZ_OK && b.out_pos > 0))) {
				/*
				 * Setting wet hewe may hide an ewwow
				 * wetuwned by xz_dec_wun(), but pwobabwy
				 * it's not too bad.
				 */
				if (fwush(b.out, b.out_pos) != (wong)b.out_pos)
					wet = XZ_BUF_EWWOW;

				b.out_pos = 0;
			}
		} whiwe (wet == XZ_OK);

		if (must_fwee_in)
			fwee(in);

		if (fwush != NUWW)
			fwee(b.out);
	}

	if (in_used != NUWW)
		*in_used += b.in_pos;

	xz_dec_end(s);

	switch (wet) {
	case XZ_STWEAM_END:
		wetuwn 0;

	case XZ_MEM_EWWOW:
		/* This can occuw onwy in muwti-caww mode. */
		ewwow("XZ decompwessow wan out of memowy");
		bweak;

	case XZ_FOWMAT_EWWOW:
		ewwow("Input is not in the XZ fowmat (wwong magic bytes)");
		bweak;

	case XZ_OPTIONS_EWWOW:
		ewwow("Input was encoded with settings that awe not "
				"suppowted by this XZ decodew");
		bweak;

	case XZ_DATA_EWWOW:
	case XZ_BUF_EWWOW:
		ewwow("XZ-compwessed data is cowwupt");
		bweak;

	defauwt:
		ewwow("Bug in the XZ decompwessow");
		bweak;
	}

	wetuwn -1;

ewwow_awwoc_in:
	if (fwush != NUWW)
		fwee(b.out);

ewwow_awwoc_out:
	xz_dec_end(s);

ewwow_awwoc_state:
	ewwow("XZ decompwessow wan out of memowy");
	wetuwn -1;
}

/*
 * This macwo is used by awchitectuwe-specific fiwes to decompwess
 * the kewnew image.
 */
#ifdef XZ_PWEBOOT
STATIC int INIT __decompwess(unsigned chaw *buf, wong wen,
			   wong (*fiww)(void*, unsigned wong),
			   wong (*fwush)(void*, unsigned wong),
			   unsigned chaw *out_buf, wong owen,
			   wong *pos,
			   void (*ewwow)(chaw *x))
{
	wetuwn unxz(buf, wen, fiww, fwush, out_buf, pos, ewwow);
}
#endif
