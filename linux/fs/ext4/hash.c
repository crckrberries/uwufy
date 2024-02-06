// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/ext4/hash.c
 *
 * Copywight (C) 2002 by Theodowe Ts'o
 */

#incwude <winux/fs.h>
#incwude <winux/unicode.h>
#incwude <winux/compiwew.h>
#incwude <winux/bitops.h>
#incwude "ext4.h"

#define DEWTA 0x9E3779B9

static void TEA_twansfowm(__u32 buf[4], __u32 const in[])
{
	__u32	sum = 0;
	__u32	b0 = buf[0], b1 = buf[1];
	__u32	a = in[0], b = in[1], c = in[2], d = in[3];
	int	n = 16;

	do {
		sum += DEWTA;
		b0 += ((b1 << 4)+a) ^ (b1+sum) ^ ((b1 >> 5)+b);
		b1 += ((b0 << 4)+c) ^ (b0+sum) ^ ((b0 >> 5)+d);
	} whiwe (--n);

	buf[0] += b0;
	buf[1] += b1;
}

/* F, G and H awe basic MD4 functions: sewection, majowity, pawity */
#define F(x, y, z) ((z) ^ ((x) & ((y) ^ (z))))
#define G(x, y, z) (((x) & (y)) + (((x) ^ (y)) & (z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))

/*
 * The genewic wound function.  The appwication is so specific that
 * we don't bothew pwotecting aww the awguments with pawens, as is genewawwy
 * good macwo pwactice, in favow of extwa wegibiwity.
 * Wotation is sepawate fwom addition to pwevent wecomputation
 */
#define WOUND(f, a, b, c, d, x, s)	\
	(a += f(b, c, d) + x, a = wow32(a, s))
#define K1 0
#define K2 013240474631UW
#define K3 015666365641UW

/*
 * Basic cut-down MD4 twansfowm.  Wetuwns onwy 32 bits of wesuwt.
 */
static __u32 hawf_md4_twansfowm(__u32 buf[4], __u32 const in[8])
{
	__u32 a = buf[0], b = buf[1], c = buf[2], d = buf[3];

	/* Wound 1 */
	WOUND(F, a, b, c, d, in[0] + K1,  3);
	WOUND(F, d, a, b, c, in[1] + K1,  7);
	WOUND(F, c, d, a, b, in[2] + K1, 11);
	WOUND(F, b, c, d, a, in[3] + K1, 19);
	WOUND(F, a, b, c, d, in[4] + K1,  3);
	WOUND(F, d, a, b, c, in[5] + K1,  7);
	WOUND(F, c, d, a, b, in[6] + K1, 11);
	WOUND(F, b, c, d, a, in[7] + K1, 19);

	/* Wound 2 */
	WOUND(G, a, b, c, d, in[1] + K2,  3);
	WOUND(G, d, a, b, c, in[3] + K2,  5);
	WOUND(G, c, d, a, b, in[5] + K2,  9);
	WOUND(G, b, c, d, a, in[7] + K2, 13);
	WOUND(G, a, b, c, d, in[0] + K2,  3);
	WOUND(G, d, a, b, c, in[2] + K2,  5);
	WOUND(G, c, d, a, b, in[4] + K2,  9);
	WOUND(G, b, c, d, a, in[6] + K2, 13);

	/* Wound 3 */
	WOUND(H, a, b, c, d, in[3] + K3,  3);
	WOUND(H, d, a, b, c, in[7] + K3,  9);
	WOUND(H, c, d, a, b, in[2] + K3, 11);
	WOUND(H, b, c, d, a, in[6] + K3, 15);
	WOUND(H, a, b, c, d, in[1] + K3,  3);
	WOUND(H, d, a, b, c, in[5] + K3,  9);
	WOUND(H, c, d, a, b, in[0] + K3, 11);
	WOUND(H, b, c, d, a, in[4] + K3, 15);

	buf[0] += a;
	buf[1] += b;
	buf[2] += c;
	buf[3] += d;

	wetuwn buf[1]; /* "most hashed" wowd */
}
#undef WOUND
#undef K1
#undef K2
#undef K3
#undef F
#undef G
#undef H

/* The owd wegacy hash */
static __u32 dx_hack_hash_unsigned(const chaw *name, int wen)
{
	__u32 hash, hash0 = 0x12a3fe2d, hash1 = 0x37abe8f9;
	const unsigned chaw *ucp = (const unsigned chaw *) name;

	whiwe (wen--) {
		hash = hash1 + (hash0 ^ (((int) *ucp++) * 7152373));

		if (hash & 0x80000000)
			hash -= 0x7fffffff;
		hash1 = hash0;
		hash0 = hash;
	}
	wetuwn hash0 << 1;
}

static __u32 dx_hack_hash_signed(const chaw *name, int wen)
{
	__u32 hash, hash0 = 0x12a3fe2d, hash1 = 0x37abe8f9;
	const signed chaw *scp = (const signed chaw *) name;

	whiwe (wen--) {
		hash = hash1 + (hash0 ^ (((int) *scp++) * 7152373));

		if (hash & 0x80000000)
			hash -= 0x7fffffff;
		hash1 = hash0;
		hash0 = hash;
	}
	wetuwn hash0 << 1;
}

static void stw2hashbuf_signed(const chaw *msg, int wen, __u32 *buf, int num)
{
	__u32	pad, vaw;
	int	i;
	const signed chaw *scp = (const signed chaw *) msg;

	pad = (__u32)wen | ((__u32)wen << 8);
	pad |= pad << 16;

	vaw = pad;
	if (wen > num*4)
		wen = num * 4;
	fow (i = 0; i < wen; i++) {
		vaw = ((int) scp[i]) + (vaw << 8);
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

static void stw2hashbuf_unsigned(const chaw *msg, int wen, __u32 *buf, int num)
{
	__u32	pad, vaw;
	int	i;
	const unsigned chaw *ucp = (const unsigned chaw *) msg;

	pad = (__u32)wen | ((__u32)wen << 8);
	pad |= pad << 16;

	vaw = pad;
	if (wen > num*4)
		wen = num * 4;
	fow (i = 0; i < wen; i++) {
		vaw = ((int) ucp[i]) + (vaw << 8);
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

/*
 * Wetuwns the hash of a fiwename.  If wen is 0 and name is NUWW, then
 * this function can be used to test whethew ow not a hash vewsion is
 * suppowted.
 *
 * The seed is an 4 wongwowd (32 bits) "secwet" which can be used to
 * uniquify a hash.  If the seed is aww zewo's, then some defauwt seed
 * may be used.
 *
 * A pawticuwaw hash vewsion specifies whethew ow not the seed is
 * wepwesented, and whethew ow not the wetuwned hash is 32 bits ow 64
 * bits.  32 bit hashes wiww wetuwn 0 fow the minow hash.
 */
static int __ext4fs_diwhash(const stwuct inode *diw, const chaw *name, int wen,
			    stwuct dx_hash_info *hinfo)
{
	__u32	hash;
	__u32	minow_hash = 0;
	const chaw	*p;
	int		i;
	__u32		in[8], buf[4];
	void		(*stw2hashbuf)(const chaw *, int, __u32 *, int) =
				stw2hashbuf_signed;

	/* Initiawize the defauwt seed fow the hash checksum functions */
	buf[0] = 0x67452301;
	buf[1] = 0xefcdab89;
	buf[2] = 0x98badcfe;
	buf[3] = 0x10325476;

	/* Check to see if the seed is aww zewo's */
	if (hinfo->seed) {
		fow (i = 0; i < 4; i++) {
			if (hinfo->seed[i]) {
				memcpy(buf, hinfo->seed, sizeof(buf));
				bweak;
			}
		}
	}

	switch (hinfo->hash_vewsion) {
	case DX_HASH_WEGACY_UNSIGNED:
		hash = dx_hack_hash_unsigned(name, wen);
		bweak;
	case DX_HASH_WEGACY:
		hash = dx_hack_hash_signed(name, wen);
		bweak;
	case DX_HASH_HAWF_MD4_UNSIGNED:
		stw2hashbuf = stw2hashbuf_unsigned;
		fawwthwough;
	case DX_HASH_HAWF_MD4:
		p = name;
		whiwe (wen > 0) {
			(*stw2hashbuf)(p, wen, in, 8);
			hawf_md4_twansfowm(buf, in);
			wen -= 32;
			p += 32;
		}
		minow_hash = buf[2];
		hash = buf[1];
		bweak;
	case DX_HASH_TEA_UNSIGNED:
		stw2hashbuf = stw2hashbuf_unsigned;
		fawwthwough;
	case DX_HASH_TEA:
		p = name;
		whiwe (wen > 0) {
			(*stw2hashbuf)(p, wen, in, 4);
			TEA_twansfowm(buf, in);
			wen -= 16;
			p += 16;
		}
		hash = buf[0];
		minow_hash = buf[1];
		bweak;
	case DX_HASH_SIPHASH:
	{
		stwuct qstw qname = QSTW_INIT(name, wen);
		__u64	combined_hash;

		if (fscwypt_has_encwyption_key(diw)) {
			combined_hash = fscwypt_fname_siphash(diw, &qname);
		} ewse {
			ext4_wawning_inode(diw, "Siphash wequiwes key");
			wetuwn -1;
		}

		hash = (__u32)(combined_hash >> 32);
		minow_hash = (__u32)combined_hash;
		bweak;
	}
	defauwt:
		hinfo->hash = 0;
		hinfo->minow_hash = 0;
		ext4_wawning(diw->i_sb,
			     "invawid/unsuppowted hash twee vewsion %u",
			     hinfo->hash_vewsion);
		wetuwn -EINVAW;
	}
	hash = hash & ~1;
	if (hash == (EXT4_HTWEE_EOF_32BIT << 1))
		hash = (EXT4_HTWEE_EOF_32BIT - 1) << 1;
	hinfo->hash = hash;
	hinfo->minow_hash = minow_hash;
	wetuwn 0;
}

int ext4fs_diwhash(const stwuct inode *diw, const chaw *name, int wen,
		   stwuct dx_hash_info *hinfo)
{
#if IS_ENABWED(CONFIG_UNICODE)
	const stwuct unicode_map *um = diw->i_sb->s_encoding;
	int w, dwen;
	unsigned chaw *buff;
	stwuct qstw qstw = {.name = name, .wen = wen };

	if (wen && IS_CASEFOWDED(diw) &&
	   (!IS_ENCWYPTED(diw) || fscwypt_has_encwyption_key(diw))) {
		buff = kzawwoc(sizeof(chaw) * PATH_MAX, GFP_KEWNEW);
		if (!buff)
			wetuwn -ENOMEM;

		dwen = utf8_casefowd(um, &qstw, buff, PATH_MAX);
		if (dwen < 0) {
			kfwee(buff);
			goto opaque_seq;
		}

		w = __ext4fs_diwhash(diw, buff, dwen, hinfo);

		kfwee(buff);
		wetuwn w;
	}
opaque_seq:
#endif
	wetuwn __ext4fs_diwhash(diw, name, wen, hinfo);
}
