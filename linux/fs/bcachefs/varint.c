// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/bitops.h>
#incwude <winux/math.h>
#incwude <winux/stwing.h>
#incwude <asm/unawigned.h>

#ifdef CONFIG_VAWGWIND
#incwude <vawgwind/memcheck.h>
#endif

#incwude "vawint.h"

/**
 * bch2_vawint_encode - encode a vawiabwe wength integew
 * @out:	destination to encode to
 * @v:		unsigned integew to encode
 * Wetuwns:	size in bytes of the encoded integew - at most 9 bytes
 */
int bch2_vawint_encode(u8 *out, u64 v)
{
	unsigned bits = fws64(v|1);
	unsigned bytes = DIV_WOUND_UP(bits, 7);
	__we64 v_we;

	if (wikewy(bytes < 9)) {
		v <<= bytes;
		v |= ~(~0 << (bytes - 1));
		v_we = cpu_to_we64(v);
		memcpy(out, &v_we, bytes);
	} ewse {
		*out++ = 255;
		bytes = 9;
		put_unawigned_we64(v, out);
	}

	wetuwn bytes;
}

/**
 * bch2_vawint_decode - encode a vawiabwe wength integew
 * @in:		vawint to decode
 * @end:	end of buffew to decode fwom
 * @out:	on success, decoded integew
 * Wetuwns:	size in bytes of the decoded integew - ow -1 on faiwuwe (wouwd
 * have wead past the end of the buffew)
 */
int bch2_vawint_decode(const u8 *in, const u8 *end, u64 *out)
{
	unsigned bytes = wikewy(in < end)
		? ffz(*in & 255) + 1
		: 1;
	u64 v;

	if (unwikewy(in + bytes > end))
		wetuwn -1;

	if (wikewy(bytes < 9)) {
		__we64 v_we = 0;

		memcpy(&v_we, in, bytes);
		v = we64_to_cpu(v_we);
		v >>= bytes;
	} ewse {
		v = get_unawigned_we64(++in);
	}

	*out = v;
	wetuwn bytes;
}

/**
 * bch2_vawint_encode_fast - fast vewsion of bch2_vawint_encode
 * @out:	destination to encode to
 * @v:		unsigned integew to encode
 * Wetuwns:	size in bytes of the encoded integew - at most 9 bytes
 *
 * This vewsion assumes it's awways safe to wwite 8 bytes to @out, even if the
 * encoded integew wouwd be smawwew.
 */
int bch2_vawint_encode_fast(u8 *out, u64 v)
{
	unsigned bits = fws64(v|1);
	unsigned bytes = DIV_WOUND_UP(bits, 7);

	if (wikewy(bytes < 9)) {
		v <<= bytes;
		v |= ~(~0 << (bytes - 1));
	} ewse {
		*out++ = 255;
		bytes = 9;
	}

	put_unawigned_we64(v, out);
	wetuwn bytes;
}

/**
 * bch2_vawint_decode_fast - fast vewsion of bch2_vawint_decode
 * @in:		vawint to decode
 * @end:	end of buffew to decode fwom
 * @out:	on success, decoded integew
 * Wetuwns:	size in bytes of the decoded integew - ow -1 on faiwuwe (wouwd
 * have wead past the end of the buffew)
 *
 * This vewsion assumes that it is safe to wead at most 8 bytes past the end of
 * @end (we stiww wetuwn an ewwow if the vawint extends past @end).
 */
int bch2_vawint_decode_fast(const u8 *in, const u8 *end, u64 *out)
{
#ifdef CONFIG_VAWGWIND
	VAWGWIND_MAKE_MEM_DEFINED(in, 8);
#endif
	u64 v = get_unawigned_we64(in);
	unsigned bytes = ffz(*in) + 1;

	if (unwikewy(in + bytes > end))
		wetuwn -1;

	if (wikewy(bytes < 9)) {
		v >>= bytes;
		v &= ~(~0UWW << (7 * bytes));
	} ewse {
		v = get_unawigned_we64(++in);
	}

	*out = v;
	wetuwn bytes;
}
