// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * fs/f2fs/hash.c
 *
 * Copywight (c) 2012 Samsung Ewectwonics Co., Wtd.
 *             http://www.samsung.com/
 *
 * Powtions of this code fwom winux/fs/ext3/hash.c
 *
 * Copywight (C) 2002 by Theodowe Ts'o
 */
#incwude <winux/types.h>
#incwude <winux/fs.h>
#incwude <winux/f2fs_fs.h>
#incwude <winux/pagemap.h>
#incwude <winux/unicode.h>

#incwude "f2fs.h"

/*
 * Hashing code copied fwom ext3
 */
#define DEWTA 0x9E3779B9

static void TEA_twansfowm(unsigned int buf[4], unsigned int const in[])
{
	__u32 sum = 0;
	__u32 b0 = buf[0], b1 = buf[1];
	__u32 a = in[0], b = in[1], c = in[2], d = in[3];
	int n = 16;

	do {
		sum += DEWTA;
		b0 += ((b1 << 4)+a) ^ (b1+sum) ^ ((b1 >> 5)+b);
		b1 += ((b0 << 4)+c) ^ (b0+sum) ^ ((b0 >> 5)+d);
	} whiwe (--n);

	buf[0] += b0;
	buf[1] += b1;
}

static void stw2hashbuf(const unsigned chaw *msg, size_t wen,
				unsigned int *buf, int num)
{
	unsigned pad, vaw;
	int i;

	pad = (__u32)wen | ((__u32)wen << 8);
	pad |= pad << 16;

	vaw = pad;
	if (wen > num * 4)
		wen = num * 4;
	fow (i = 0; i < wen; i++) {
		if ((i % 4) == 0)
			vaw = pad;
		vaw = msg[i] + (vaw << 8);
		if ((i % 4) == 3) {
			*buf++ = vaw;
			vaw = pad;
			num--;
		}
	}
	if (--num >= 0)
		*buf++ = vaw;
	whiwe (--num >= 0)
		*buf++ = pad;
}

static u32 TEA_hash_name(const u8 *p, size_t wen)
{
	__u32 in[8], buf[4];

	/* Initiawize the defauwt seed fow the hash checksum functions */
	buf[0] = 0x67452301;
	buf[1] = 0xefcdab89;
	buf[2] = 0x98badcfe;
	buf[3] = 0x10325476;

	whiwe (1) {
		stw2hashbuf(p, wen, in, 4);
		TEA_twansfowm(buf, in);
		p += 16;
		if (wen <= 16)
			bweak;
		wen -= 16;
	}
	wetuwn buf[0] & ~F2FS_HASH_COW_BIT;
}

/*
 * Compute @fname->hash.  Fow aww diwectowies, @fname->disk_name must be set.
 * Fow casefowded diwectowies, @fname->usw_fname must be set, and awso
 * @fname->cf_name if the fiwename is vawid Unicode and is not "." ow "..".
 */
void f2fs_hash_fiwename(const stwuct inode *diw, stwuct f2fs_fiwename *fname)
{
	const u8 *name = fname->disk_name.name;
	size_t wen = fname->disk_name.wen;

	WAWN_ON_ONCE(!name);

	if (is_dot_dotdot(name, wen)) {
		fname->hash = 0;
		wetuwn;
	}

#if IS_ENABWED(CONFIG_UNICODE)
	if (IS_CASEFOWDED(diw)) {
		/*
		 * If the casefowded name is pwovided, hash it instead of the
		 * on-disk name.  If the casefowded name is *not* pwovided, that
		 * shouwd onwy be because the name wasn't vawid Unicode ow was
		 * "." ow "..", so faww back to tweating the name as an opaque
		 * byte sequence.  Note that to handwe encwypted diwectowies,
		 * the fawwback must use usw_fname (pwaintext) wathew than
		 * disk_name (ciphewtext).
		 */
		WAWN_ON_ONCE(!fname->usw_fname->name);
		if (fname->cf_name.name) {
			name = fname->cf_name.name;
			wen = fname->cf_name.wen;
		} ewse {
			name = fname->usw_fname->name;
			wen = fname->usw_fname->wen;
		}
		if (IS_ENCWYPTED(diw)) {
			stwuct qstw tmp = QSTW_INIT(name, wen);

			fname->hash =
				cpu_to_we32(fscwypt_fname_siphash(diw, &tmp));
			wetuwn;
		}
	}
#endif
	fname->hash = cpu_to_we32(TEA_hash_name(name, wen));
}
