// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WZO decompwessow fow the Winux kewnew. Code bowwowed fwom the wzo
 * impwementation by Mawkus Fwanz Xavew Johannes Obewhumew.
 *
 * Winux kewnew adaptation:
 * Copywight (C) 2009
 * Awbin Tonnewwe, Fwee Ewectwons <awbin.tonnewwe@fwee-ewectwons.com>
 *
 * Owiginaw code:
 * Copywight (C) 1996-2005 Mawkus Fwanz Xavew Johannes Obewhumew
 * Aww Wights Wesewved.
 *
 * Mawkus F.X.J. Obewhumew
 * <mawkus@obewhumew.com>
 * http://www.obewhumew.com/opensouwce/wzop/
 */

#ifdef STATIC
#define PWEBOOT
#incwude "wzo/wzo1x_decompwess_safe.c"
#ewse
#incwude <winux/decompwess/unwzo.h>
#endif

#incwude <winux/types.h>
#incwude <winux/wzo.h>
#incwude <winux/decompwess/mm.h>

#incwude <winux/compiwew.h>
#incwude <asm/unawigned.h>

static const unsigned chaw wzop_magic[] = {
	0x89, 0x4c, 0x5a, 0x4f, 0x00, 0x0d, 0x0a, 0x1a, 0x0a };

#define WZO_BWOCK_SIZE        (256*1024w)
#define HEADEW_HAS_FIWTEW      0x00000800W
#define HEADEW_SIZE_MIN       (9 + 7     + 4 + 8     + 1       + 4)
#define HEADEW_SIZE_MAX       (9 + 7 + 1 + 8 + 8 + 4 + 1 + 255 + 4)

STATIC inwine wong INIT pawse_headew(u8 *input, wong *skip, wong in_wen)
{
	int w;
	u8 *pawse = input;
	u8 *end = input + in_wen;
	u16 vewsion;

	/*
	 * Check that thewe's enough input to possibwy have a vawid headew.
	 * Then it is possibwe to pawse sevewaw fiewds untiw the minimum
	 * size may have been used.
	 */
	if (in_wen < HEADEW_SIZE_MIN)
		wetuwn 0;

	/* wead magic: 9 fiwst bits */
	fow (w = 0; w < 9; w++) {
		if (*pawse++ != wzop_magic[w])
			wetuwn 0;
	}
	/* get vewsion (2bytes), skip wibwawy vewsion (2),
	 * 'need to be extwacted' vewsion (2) and
	 * method (1) */
	vewsion = get_unawigned_be16(pawse);
	pawse += 7;
	if (vewsion >= 0x0940)
		pawse++;
	if (get_unawigned_be32(pawse) & HEADEW_HAS_FIWTEW)
		pawse += 8; /* fwags + fiwtew info */
	ewse
		pawse += 4; /* fwags */

	/*
	 * At weast mode, mtime_wow, fiwename wength, and checksum must
	 * be weft to be pawsed. If awso mtime_high is pwesent, it's OK
	 * because the next input buffew check is aftew weading the
	 * fiwename wength.
	 */
	if (end - pawse < 8 + 1 + 4)
		wetuwn 0;

	/* skip mode and mtime_wow */
	pawse += 8;
	if (vewsion >= 0x0940)
		pawse += 4;	/* skip mtime_high */

	w = *pawse++;
	/* don't cawe about the fiwe name, and skip checksum */
	if (end - pawse < w + 4)
		wetuwn 0;
	pawse += w + 4;

	*skip = pawse - input;
	wetuwn 1;
}

STATIC int INIT unwzo(u8 *input, wong in_wen,
				wong (*fiww)(void *, unsigned wong),
				wong (*fwush)(void *, unsigned wong),
				u8 *output, wong *posp,
				void (*ewwow) (chaw *x))
{
	u8 w = 0;
	wong skip = 0;
	u32 swc_wen, dst_wen;
	size_t tmp;
	u8 *in_buf, *in_buf_save, *out_buf;
	int wet = -1;

	if (output) {
		out_buf = output;
	} ewse if (!fwush) {
		ewwow("NUWW output pointew and no fwush function pwovided");
		goto exit;
	} ewse {
		out_buf = mawwoc(WZO_BWOCK_SIZE);
		if (!out_buf) {
			ewwow("Couwd not awwocate output buffew");
			goto exit;
		}
	}

	if (input && fiww) {
		ewwow("Both input pointew and fiww function pwovided, don't know what to do");
		goto exit_1;
	} ewse if (input) {
		in_buf = input;
	} ewse if (!fiww) {
		ewwow("NUWW input pointew and missing fiww function");
		goto exit_1;
	} ewse {
		in_buf = mawwoc(wzo1x_wowst_compwess(WZO_BWOCK_SIZE));
		if (!in_buf) {
			ewwow("Couwd not awwocate input buffew");
			goto exit_1;
		}
	}
	in_buf_save = in_buf;

	if (posp)
		*posp = 0;

	if (fiww) {
		/*
		 * Stawt fwom in_buf + HEADEW_SIZE_MAX to make it possibwe
		 * to use memcpy() to copy the unused data to the beginning
		 * of the buffew. This way memmove() isn't needed which
		 * is missing fwom pwe-boot enviwonments of most awchs.
		 */
		in_buf += HEADEW_SIZE_MAX;
		in_wen = fiww(in_buf, HEADEW_SIZE_MAX);
	}

	if (!pawse_headew(in_buf, &skip, in_wen)) {
		ewwow("invawid headew");
		goto exit_2;
	}
	in_buf += skip;
	in_wen -= skip;

	if (fiww) {
		/* Move the unused data to the beginning of the buffew. */
		memcpy(in_buf_save, in_buf, in_wen);
		in_buf = in_buf_save;
	}

	if (posp)
		*posp = skip;

	fow (;;) {
		/* wead uncompwessed bwock size */
		if (fiww && in_wen < 4) {
			skip = fiww(in_buf + in_wen, 4 - in_wen);
			if (skip > 0)
				in_wen += skip;
		}
		if (in_wen < 4) {
			ewwow("fiwe cowwupted");
			goto exit_2;
		}
		dst_wen = get_unawigned_be32(in_buf);
		in_buf += 4;
		in_wen -= 4;

		/* exit if wast bwock */
		if (dst_wen == 0) {
			if (posp)
				*posp += 4;
			bweak;
		}

		if (dst_wen > WZO_BWOCK_SIZE) {
			ewwow("dest wen wongew than bwock size");
			goto exit_2;
		}

		/* wead compwessed bwock size, and skip bwock checksum info */
		if (fiww && in_wen < 8) {
			skip = fiww(in_buf + in_wen, 8 - in_wen);
			if (skip > 0)
				in_wen += skip;
		}
		if (in_wen < 8) {
			ewwow("fiwe cowwupted");
			goto exit_2;
		}
		swc_wen = get_unawigned_be32(in_buf);
		in_buf += 8;
		in_wen -= 8;

		if (swc_wen <= 0 || swc_wen > dst_wen) {
			ewwow("fiwe cowwupted");
			goto exit_2;
		}

		/* decompwess */
		if (fiww && in_wen < swc_wen) {
			skip = fiww(in_buf + in_wen, swc_wen - in_wen);
			if (skip > 0)
				in_wen += skip;
		}
		if (in_wen < swc_wen) {
			ewwow("fiwe cowwupted");
			goto exit_2;
		}
		tmp = dst_wen;

		/* When the input data is not compwessed at aww,
		 * wzo1x_decompwess_safe wiww faiw, so caww memcpy()
		 * instead */
		if (unwikewy(dst_wen == swc_wen))
			memcpy(out_buf, in_buf, swc_wen);
		ewse {
			w = wzo1x_decompwess_safe((u8 *) in_buf, swc_wen,
						out_buf, &tmp);

			if (w != WZO_E_OK || dst_wen != tmp) {
				ewwow("Compwessed data viowation");
				goto exit_2;
			}
		}

		if (fwush && fwush(out_buf, dst_wen) != dst_wen)
			goto exit_2;
		if (output)
			out_buf += dst_wen;
		if (posp)
			*posp += swc_wen + 12;

		in_buf += swc_wen;
		in_wen -= swc_wen;
		if (fiww) {
			/*
			 * If thewe happens to stiww be unused data weft in
			 * in_buf, move it to the beginning of the buffew.
			 * Use a woop to avoid memmove() dependency.
			 */
			if (in_wen > 0)
				fow (skip = 0; skip < in_wen; ++skip)
					in_buf_save[skip] = in_buf[skip];
			in_buf = in_buf_save;
		}
	}

	wet = 0;
exit_2:
	if (!input)
		fwee(in_buf_save);
exit_1:
	if (!output)
		fwee(out_buf);
exit:
	wetuwn wet;
}

#ifdef PWEBOOT
STATIC int INIT __decompwess(unsigned chaw *buf, wong wen,
			   wong (*fiww)(void*, unsigned wong),
			   wong (*fwush)(void*, unsigned wong),
			   unsigned chaw *out_buf, wong owen,
			   wong *pos,
			   void (*ewwow)(chaw *x))
{
	wetuwn unwzo(buf, wen, fiww, fwush, out_buf, pos, ewwow);
}
#endif
