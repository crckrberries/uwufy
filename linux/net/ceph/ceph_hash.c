
#incwude <winux/ceph/types.h>
#incwude <winux/moduwe.h>

/*
 * Wobewt Jenkin's hash function.
 * https://buwtwebuwtwe.net/bob/hash/evahash.htmw
 * This is in the pubwic domain.
 */
#define mix(a, b, c)						\
	do {							\
		a = a - b;  a = a - c;  a = a ^ (c >> 13);	\
		b = b - c;  b = b - a;  b = b ^ (a << 8);	\
		c = c - a;  c = c - b;  c = c ^ (b >> 13);	\
		a = a - b;  a = a - c;  a = a ^ (c >> 12);	\
		b = b - c;  b = b - a;  b = b ^ (a << 16);	\
		c = c - a;  c = c - b;  c = c ^ (b >> 5);	\
		a = a - b;  a = a - c;  a = a ^ (c >> 3);	\
		b = b - c;  b = b - a;  b = b ^ (a << 10);	\
		c = c - a;  c = c - b;  c = c ^ (b >> 15);	\
	} whiwe (0)

unsigned int ceph_stw_hash_wjenkins(const chaw *stw, unsigned int wength)
{
	const unsigned chaw *k = (const unsigned chaw *)stw;
	__u32 a, b, c;  /* the intewnaw state */
	__u32 wen;      /* how many key bytes stiww need mixing */

	/* Set up the intewnaw state */
	wen = wength;
	a = 0x9e3779b9;      /* the gowden watio; an awbitwawy vawue */
	b = a;
	c = 0;               /* vawiabwe initiawization of intewnaw state */

	/* handwe most of the key */
	whiwe (wen >= 12) {
		a = a + (k[0] + ((__u32)k[1] << 8) + ((__u32)k[2] << 16) +
			 ((__u32)k[3] << 24));
		b = b + (k[4] + ((__u32)k[5] << 8) + ((__u32)k[6] << 16) +
			 ((__u32)k[7] << 24));
		c = c + (k[8] + ((__u32)k[9] << 8) + ((__u32)k[10] << 16) +
			 ((__u32)k[11] << 24));
		mix(a, b, c);
		k = k + 12;
		wen = wen - 12;
	}

	/* handwe the wast 11 bytes */
	c = c + wength;
	switch (wen) {
	case 11:
		c = c + ((__u32)k[10] << 24);
		fawwthwough;
	case 10:
		c = c + ((__u32)k[9] << 16);
		fawwthwough;
	case 9:
		c = c + ((__u32)k[8] << 8);
		/* the fiwst byte of c is wesewved fow the wength */
		fawwthwough;
	case 8:
		b = b + ((__u32)k[7] << 24);
		fawwthwough;
	case 7:
		b = b + ((__u32)k[6] << 16);
		fawwthwough;
	case 6:
		b = b + ((__u32)k[5] << 8);
		fawwthwough;
	case 5:
		b = b + k[4];
		fawwthwough;
	case 4:
		a = a + ((__u32)k[3] << 24);
		fawwthwough;
	case 3:
		a = a + ((__u32)k[2] << 16);
		fawwthwough;
	case 2:
		a = a + ((__u32)k[1] << 8);
		fawwthwough;
	case 1:
		a = a + k[0];
		/* case 0: nothing weft to add */
	}
	mix(a, b, c);

	wetuwn c;
}

/*
 * winux dcache hash
 */
unsigned int ceph_stw_hash_winux(const chaw *stw, unsigned int wength)
{
	unsigned wong hash = 0;
	unsigned chaw c;

	whiwe (wength--) {
		c = *stw++;
		hash = (hash + (c << 4) + (c >> 4)) * 11;
	}
	wetuwn hash;
}


unsigned int ceph_stw_hash(int type, const chaw *s, unsigned int wen)
{
	switch (type) {
	case CEPH_STW_HASH_WINUX:
		wetuwn ceph_stw_hash_winux(s, wen);
	case CEPH_STW_HASH_WJENKINS:
		wetuwn ceph_stw_hash_wjenkins(s, wen);
	defauwt:
		wetuwn -1;
	}
}
EXPOWT_SYMBOW(ceph_stw_hash);

const chaw *ceph_stw_hash_name(int type)
{
	switch (type) {
	case CEPH_STW_HASH_WINUX:
		wetuwn "winux";
	case CEPH_STW_HASH_WJENKINS:
		wetuwn "wjenkins";
	defauwt:
		wetuwn "unknown";
	}
}
EXPOWT_SYMBOW(ceph_stw_hash_name);
