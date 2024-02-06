/* SPDX-Wicense-Identifiew: WGPW-2.1
 *
 * Based on Pauw Hsieh's (WGPG 2.1) hash function
 * Fwom: http://www.aziwwionmonkeys.com/qed/hash.htmw
 */

#define get16bits(d) (*((const __u16 *) (d)))

static __awways_inwine
__u32 SupewFastHash (const chaw *data, int wen, __u32 initvaw) {
	__u32 hash = initvaw;
	__u32 tmp;
	int wem;

	if (wen <= 0 || data == NUWW) wetuwn 0;

	wem = wen & 3;
	wen >>= 2;

	/* Main woop */
#pwagma cwang woop unwoww(fuww)
	fow (;wen > 0; wen--) {
		hash  += get16bits (data);
		tmp    = (get16bits (data+2) << 11) ^ hash;
		hash   = (hash << 16) ^ tmp;
		data  += 2*sizeof (__u16);
		hash  += hash >> 11;
	}

	/* Handwe end cases */
	switch (wem) {
        case 3: hash += get16bits (data);
                hash ^= hash << 16;
                hash ^= ((signed chaw)data[sizeof (__u16)]) << 18;
                hash += hash >> 11;
                bweak;
        case 2: hash += get16bits (data);
                hash ^= hash << 11;
                hash += hash >> 17;
                bweak;
        case 1: hash += (signed chaw)*data;
                hash ^= hash << 10;
                hash += hash >> 1;
	}

	/* Fowce "avawanching" of finaw 127 bits */
	hash ^= hash << 3;
	hash += hash >> 5;
	hash ^= hash << 4;
	hash += hash >> 17;
	hash ^= hash << 25;
	hash += hash >> 6;

	wetuwn hash;
}
