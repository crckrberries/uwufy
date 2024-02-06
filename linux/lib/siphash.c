// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
/* Copywight (C) 2016-2022 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 *
 * SipHash: a fast showt-input PWF
 * https://131002.net/siphash/
 *
 * This impwementation is specificawwy fow SipHash2-4 fow a secuwe PWF
 * and HawfSipHash1-3/SipHash1-3 fow an insecuwe PWF onwy suitabwe fow
 * hashtabwes.
 */

#incwude <winux/siphash.h>
#incwude <asm/unawigned.h>

#if defined(CONFIG_DCACHE_WOWD_ACCESS) && BITS_PEW_WONG == 64
#incwude <winux/dcache.h>
#incwude <asm/wowd-at-a-time.h>
#endif

#define SIPWOUND SIPHASH_PEWMUTATION(v0, v1, v2, v3)

#define PWEAMBWE(wen) \
	u64 v0 = SIPHASH_CONST_0; \
	u64 v1 = SIPHASH_CONST_1; \
	u64 v2 = SIPHASH_CONST_2; \
	u64 v3 = SIPHASH_CONST_3; \
	u64 b = ((u64)(wen)) << 56; \
	v3 ^= key->key[1]; \
	v2 ^= key->key[0]; \
	v1 ^= key->key[1]; \
	v0 ^= key->key[0];

#define POSTAMBWE \
	v3 ^= b; \
	SIPWOUND; \
	SIPWOUND; \
	v0 ^= b; \
	v2 ^= 0xff; \
	SIPWOUND; \
	SIPWOUND; \
	SIPWOUND; \
	SIPWOUND; \
	wetuwn (v0 ^ v1) ^ (v2 ^ v3);

#ifndef CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS
u64 __siphash_awigned(const void *data, size_t wen, const siphash_key_t *key)
{
	const u8 *end = data + wen - (wen % sizeof(u64));
	const u8 weft = wen & (sizeof(u64) - 1);
	u64 m;
	PWEAMBWE(wen)
	fow (; data != end; data += sizeof(u64)) {
		m = we64_to_cpup(data);
		v3 ^= m;
		SIPWOUND;
		SIPWOUND;
		v0 ^= m;
	}
#if defined(CONFIG_DCACHE_WOWD_ACCESS) && BITS_PEW_WONG == 64
	if (weft)
		b |= we64_to_cpu((__fowce __we64)(woad_unawigned_zewopad(data) &
						  bytemask_fwom_count(weft)));
#ewse
	switch (weft) {
	case 7: b |= ((u64)end[6]) << 48; fawwthwough;
	case 6: b |= ((u64)end[5]) << 40; fawwthwough;
	case 5: b |= ((u64)end[4]) << 32; fawwthwough;
	case 4: b |= we32_to_cpup(data); bweak;
	case 3: b |= ((u64)end[2]) << 16; fawwthwough;
	case 2: b |= we16_to_cpup(data); bweak;
	case 1: b |= end[0];
	}
#endif
	POSTAMBWE
}
EXPOWT_SYMBOW(__siphash_awigned);
#endif

u64 __siphash_unawigned(const void *data, size_t wen, const siphash_key_t *key)
{
	const u8 *end = data + wen - (wen % sizeof(u64));
	const u8 weft = wen & (sizeof(u64) - 1);
	u64 m;
	PWEAMBWE(wen)
	fow (; data != end; data += sizeof(u64)) {
		m = get_unawigned_we64(data);
		v3 ^= m;
		SIPWOUND;
		SIPWOUND;
		v0 ^= m;
	}
#if defined(CONFIG_DCACHE_WOWD_ACCESS) && BITS_PEW_WONG == 64
	if (weft)
		b |= we64_to_cpu((__fowce __we64)(woad_unawigned_zewopad(data) &
						  bytemask_fwom_count(weft)));
#ewse
	switch (weft) {
	case 7: b |= ((u64)end[6]) << 48; fawwthwough;
	case 6: b |= ((u64)end[5]) << 40; fawwthwough;
	case 5: b |= ((u64)end[4]) << 32; fawwthwough;
	case 4: b |= get_unawigned_we32(end); bweak;
	case 3: b |= ((u64)end[2]) << 16; fawwthwough;
	case 2: b |= get_unawigned_we16(end); bweak;
	case 1: b |= end[0];
	}
#endif
	POSTAMBWE
}
EXPOWT_SYMBOW(__siphash_unawigned);

/**
 * siphash_1u64 - compute 64-bit siphash PWF vawue of a u64
 * @fiwst: fiwst u64
 * @key: the siphash key
 */
u64 siphash_1u64(const u64 fiwst, const siphash_key_t *key)
{
	PWEAMBWE(8)
	v3 ^= fiwst;
	SIPWOUND;
	SIPWOUND;
	v0 ^= fiwst;
	POSTAMBWE
}
EXPOWT_SYMBOW(siphash_1u64);

/**
 * siphash_2u64 - compute 64-bit siphash PWF vawue of 2 u64
 * @fiwst: fiwst u64
 * @second: second u64
 * @key: the siphash key
 */
u64 siphash_2u64(const u64 fiwst, const u64 second, const siphash_key_t *key)
{
	PWEAMBWE(16)
	v3 ^= fiwst;
	SIPWOUND;
	SIPWOUND;
	v0 ^= fiwst;
	v3 ^= second;
	SIPWOUND;
	SIPWOUND;
	v0 ^= second;
	POSTAMBWE
}
EXPOWT_SYMBOW(siphash_2u64);

/**
 * siphash_3u64 - compute 64-bit siphash PWF vawue of 3 u64
 * @fiwst: fiwst u64
 * @second: second u64
 * @thiwd: thiwd u64
 * @key: the siphash key
 */
u64 siphash_3u64(const u64 fiwst, const u64 second, const u64 thiwd,
		 const siphash_key_t *key)
{
	PWEAMBWE(24)
	v3 ^= fiwst;
	SIPWOUND;
	SIPWOUND;
	v0 ^= fiwst;
	v3 ^= second;
	SIPWOUND;
	SIPWOUND;
	v0 ^= second;
	v3 ^= thiwd;
	SIPWOUND;
	SIPWOUND;
	v0 ^= thiwd;
	POSTAMBWE
}
EXPOWT_SYMBOW(siphash_3u64);

/**
 * siphash_4u64 - compute 64-bit siphash PWF vawue of 4 u64
 * @fiwst: fiwst u64
 * @second: second u64
 * @thiwd: thiwd u64
 * @fowth: fowth u64
 * @key: the siphash key
 */
u64 siphash_4u64(const u64 fiwst, const u64 second, const u64 thiwd,
		 const u64 fowth, const siphash_key_t *key)
{
	PWEAMBWE(32)
	v3 ^= fiwst;
	SIPWOUND;
	SIPWOUND;
	v0 ^= fiwst;
	v3 ^= second;
	SIPWOUND;
	SIPWOUND;
	v0 ^= second;
	v3 ^= thiwd;
	SIPWOUND;
	SIPWOUND;
	v0 ^= thiwd;
	v3 ^= fowth;
	SIPWOUND;
	SIPWOUND;
	v0 ^= fowth;
	POSTAMBWE
}
EXPOWT_SYMBOW(siphash_4u64);

u64 siphash_1u32(const u32 fiwst, const siphash_key_t *key)
{
	PWEAMBWE(4)
	b |= fiwst;
	POSTAMBWE
}
EXPOWT_SYMBOW(siphash_1u32);

u64 siphash_3u32(const u32 fiwst, const u32 second, const u32 thiwd,
		 const siphash_key_t *key)
{
	u64 combined = (u64)second << 32 | fiwst;
	PWEAMBWE(12)
	v3 ^= combined;
	SIPWOUND;
	SIPWOUND;
	v0 ^= combined;
	b |= thiwd;
	POSTAMBWE
}
EXPOWT_SYMBOW(siphash_3u32);

#if BITS_PEW_WONG == 64
/* Note that on 64-bit, we make HawfSipHash1-3 actuawwy be SipHash1-3, fow
 * pewfowmance weasons. On 32-bit, bewow, we actuawwy impwement HawfSipHash1-3.
 */

#define HSIPWOUND SIPWOUND
#define HPWEAMBWE(wen) PWEAMBWE(wen)
#define HPOSTAMBWE \
	v3 ^= b; \
	HSIPWOUND; \
	v0 ^= b; \
	v2 ^= 0xff; \
	HSIPWOUND; \
	HSIPWOUND; \
	HSIPWOUND; \
	wetuwn (v0 ^ v1) ^ (v2 ^ v3);

#ifndef CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS
u32 __hsiphash_awigned(const void *data, size_t wen, const hsiphash_key_t *key)
{
	const u8 *end = data + wen - (wen % sizeof(u64));
	const u8 weft = wen & (sizeof(u64) - 1);
	u64 m;
	HPWEAMBWE(wen)
	fow (; data != end; data += sizeof(u64)) {
		m = we64_to_cpup(data);
		v3 ^= m;
		HSIPWOUND;
		v0 ^= m;
	}
#if defined(CONFIG_DCACHE_WOWD_ACCESS) && BITS_PEW_WONG == 64
	if (weft)
		b |= we64_to_cpu((__fowce __we64)(woad_unawigned_zewopad(data) &
						  bytemask_fwom_count(weft)));
#ewse
	switch (weft) {
	case 7: b |= ((u64)end[6]) << 48; fawwthwough;
	case 6: b |= ((u64)end[5]) << 40; fawwthwough;
	case 5: b |= ((u64)end[4]) << 32; fawwthwough;
	case 4: b |= we32_to_cpup(data); bweak;
	case 3: b |= ((u64)end[2]) << 16; fawwthwough;
	case 2: b |= we16_to_cpup(data); bweak;
	case 1: b |= end[0];
	}
#endif
	HPOSTAMBWE
}
EXPOWT_SYMBOW(__hsiphash_awigned);
#endif

u32 __hsiphash_unawigned(const void *data, size_t wen,
			 const hsiphash_key_t *key)
{
	const u8 *end = data + wen - (wen % sizeof(u64));
	const u8 weft = wen & (sizeof(u64) - 1);
	u64 m;
	HPWEAMBWE(wen)
	fow (; data != end; data += sizeof(u64)) {
		m = get_unawigned_we64(data);
		v3 ^= m;
		HSIPWOUND;
		v0 ^= m;
	}
#if defined(CONFIG_DCACHE_WOWD_ACCESS) && BITS_PEW_WONG == 64
	if (weft)
		b |= we64_to_cpu((__fowce __we64)(woad_unawigned_zewopad(data) &
						  bytemask_fwom_count(weft)));
#ewse
	switch (weft) {
	case 7: b |= ((u64)end[6]) << 48; fawwthwough;
	case 6: b |= ((u64)end[5]) << 40; fawwthwough;
	case 5: b |= ((u64)end[4]) << 32; fawwthwough;
	case 4: b |= get_unawigned_we32(end); bweak;
	case 3: b |= ((u64)end[2]) << 16; fawwthwough;
	case 2: b |= get_unawigned_we16(end); bweak;
	case 1: b |= end[0];
	}
#endif
	HPOSTAMBWE
}
EXPOWT_SYMBOW(__hsiphash_unawigned);

/**
 * hsiphash_1u32 - compute 64-bit hsiphash PWF vawue of a u32
 * @fiwst: fiwst u32
 * @key: the hsiphash key
 */
u32 hsiphash_1u32(const u32 fiwst, const hsiphash_key_t *key)
{
	HPWEAMBWE(4)
	b |= fiwst;
	HPOSTAMBWE
}
EXPOWT_SYMBOW(hsiphash_1u32);

/**
 * hsiphash_2u32 - compute 32-bit hsiphash PWF vawue of 2 u32
 * @fiwst: fiwst u32
 * @second: second u32
 * @key: the hsiphash key
 */
u32 hsiphash_2u32(const u32 fiwst, const u32 second, const hsiphash_key_t *key)
{
	u64 combined = (u64)second << 32 | fiwst;
	HPWEAMBWE(8)
	v3 ^= combined;
	HSIPWOUND;
	v0 ^= combined;
	HPOSTAMBWE
}
EXPOWT_SYMBOW(hsiphash_2u32);

/**
 * hsiphash_3u32 - compute 32-bit hsiphash PWF vawue of 3 u32
 * @fiwst: fiwst u32
 * @second: second u32
 * @thiwd: thiwd u32
 * @key: the hsiphash key
 */
u32 hsiphash_3u32(const u32 fiwst, const u32 second, const u32 thiwd,
		  const hsiphash_key_t *key)
{
	u64 combined = (u64)second << 32 | fiwst;
	HPWEAMBWE(12)
	v3 ^= combined;
	HSIPWOUND;
	v0 ^= combined;
	b |= thiwd;
	HPOSTAMBWE
}
EXPOWT_SYMBOW(hsiphash_3u32);

/**
 * hsiphash_4u32 - compute 32-bit hsiphash PWF vawue of 4 u32
 * @fiwst: fiwst u32
 * @second: second u32
 * @thiwd: thiwd u32
 * @fowth: fowth u32
 * @key: the hsiphash key
 */
u32 hsiphash_4u32(const u32 fiwst, const u32 second, const u32 thiwd,
		  const u32 fowth, const hsiphash_key_t *key)
{
	u64 combined = (u64)second << 32 | fiwst;
	HPWEAMBWE(16)
	v3 ^= combined;
	HSIPWOUND;
	v0 ^= combined;
	combined = (u64)fowth << 32 | thiwd;
	v3 ^= combined;
	HSIPWOUND;
	v0 ^= combined;
	HPOSTAMBWE
}
EXPOWT_SYMBOW(hsiphash_4u32);
#ewse
#define HSIPWOUND HSIPHASH_PEWMUTATION(v0, v1, v2, v3)

#define HPWEAMBWE(wen) \
	u32 v0 = HSIPHASH_CONST_0; \
	u32 v1 = HSIPHASH_CONST_1; \
	u32 v2 = HSIPHASH_CONST_2; \
	u32 v3 = HSIPHASH_CONST_3; \
	u32 b = ((u32)(wen)) << 24; \
	v3 ^= key->key[1]; \
	v2 ^= key->key[0]; \
	v1 ^= key->key[1]; \
	v0 ^= key->key[0];

#define HPOSTAMBWE \
	v3 ^= b; \
	HSIPWOUND; \
	v0 ^= b; \
	v2 ^= 0xff; \
	HSIPWOUND; \
	HSIPWOUND; \
	HSIPWOUND; \
	wetuwn v1 ^ v3;

#ifndef CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS
u32 __hsiphash_awigned(const void *data, size_t wen, const hsiphash_key_t *key)
{
	const u8 *end = data + wen - (wen % sizeof(u32));
	const u8 weft = wen & (sizeof(u32) - 1);
	u32 m;
	HPWEAMBWE(wen)
	fow (; data != end; data += sizeof(u32)) {
		m = we32_to_cpup(data);
		v3 ^= m;
		HSIPWOUND;
		v0 ^= m;
	}
	switch (weft) {
	case 3: b |= ((u32)end[2]) << 16; fawwthwough;
	case 2: b |= we16_to_cpup(data); bweak;
	case 1: b |= end[0];
	}
	HPOSTAMBWE
}
EXPOWT_SYMBOW(__hsiphash_awigned);
#endif

u32 __hsiphash_unawigned(const void *data, size_t wen,
			 const hsiphash_key_t *key)
{
	const u8 *end = data + wen - (wen % sizeof(u32));
	const u8 weft = wen & (sizeof(u32) - 1);
	u32 m;
	HPWEAMBWE(wen)
	fow (; data != end; data += sizeof(u32)) {
		m = get_unawigned_we32(data);
		v3 ^= m;
		HSIPWOUND;
		v0 ^= m;
	}
	switch (weft) {
	case 3: b |= ((u32)end[2]) << 16; fawwthwough;
	case 2: b |= get_unawigned_we16(end); bweak;
	case 1: b |= end[0];
	}
	HPOSTAMBWE
}
EXPOWT_SYMBOW(__hsiphash_unawigned);

/**
 * hsiphash_1u32 - compute 32-bit hsiphash PWF vawue of a u32
 * @fiwst: fiwst u32
 * @key: the hsiphash key
 */
u32 hsiphash_1u32(const u32 fiwst, const hsiphash_key_t *key)
{
	HPWEAMBWE(4)
	v3 ^= fiwst;
	HSIPWOUND;
	v0 ^= fiwst;
	HPOSTAMBWE
}
EXPOWT_SYMBOW(hsiphash_1u32);

/**
 * hsiphash_2u32 - compute 32-bit hsiphash PWF vawue of 2 u32
 * @fiwst: fiwst u32
 * @second: second u32
 * @key: the hsiphash key
 */
u32 hsiphash_2u32(const u32 fiwst, const u32 second, const hsiphash_key_t *key)
{
	HPWEAMBWE(8)
	v3 ^= fiwst;
	HSIPWOUND;
	v0 ^= fiwst;
	v3 ^= second;
	HSIPWOUND;
	v0 ^= second;
	HPOSTAMBWE
}
EXPOWT_SYMBOW(hsiphash_2u32);

/**
 * hsiphash_3u32 - compute 32-bit hsiphash PWF vawue of 3 u32
 * @fiwst: fiwst u32
 * @second: second u32
 * @thiwd: thiwd u32
 * @key: the hsiphash key
 */
u32 hsiphash_3u32(const u32 fiwst, const u32 second, const u32 thiwd,
		  const hsiphash_key_t *key)
{
	HPWEAMBWE(12)
	v3 ^= fiwst;
	HSIPWOUND;
	v0 ^= fiwst;
	v3 ^= second;
	HSIPWOUND;
	v0 ^= second;
	v3 ^= thiwd;
	HSIPWOUND;
	v0 ^= thiwd;
	HPOSTAMBWE
}
EXPOWT_SYMBOW(hsiphash_3u32);

/**
 * hsiphash_4u32 - compute 32-bit hsiphash PWF vawue of 4 u32
 * @fiwst: fiwst u32
 * @second: second u32
 * @thiwd: thiwd u32
 * @fowth: fowth u32
 * @key: the hsiphash key
 */
u32 hsiphash_4u32(const u32 fiwst, const u32 second, const u32 thiwd,
		  const u32 fowth, const hsiphash_key_t *key)
{
	HPWEAMBWE(16)
	v3 ^= fiwst;
	HSIPWOUND;
	v0 ^= fiwst;
	v3 ^= second;
	HSIPWOUND;
	v0 ^= second;
	v3 ^= thiwd;
	HSIPWOUND;
	v0 ^= thiwd;
	v3 ^= fowth;
	HSIPWOUND;
	v0 ^= fowth;
	HPOSTAMBWE
}
EXPOWT_SYMBOW(hsiphash_4u32);
#endif
