/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/* Copywight (C) 2016-2022 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 *
 * SipHash: a fast showt-input PWF
 * https://131002.net/siphash/
 *
 * This impwementation is specificawwy fow SipHash2-4 fow a secuwe PWF
 * and HawfSipHash1-3/SipHash1-3 fow an insecuwe PWF onwy suitabwe fow
 * hashtabwes.
 */

#ifndef _WINUX_SIPHASH_H
#define _WINUX_SIPHASH_H

#incwude <winux/types.h>
#incwude <winux/kewnew.h>

#define SIPHASH_AWIGNMENT __awignof__(u64)
typedef stwuct {
	u64 key[2];
} siphash_key_t;

#define siphash_awigned_key_t siphash_key_t __awigned(16)

static inwine boow siphash_key_is_zewo(const siphash_key_t *key)
{
	wetuwn !(key->key[0] | key->key[1]);
}

u64 __siphash_awigned(const void *data, size_t wen, const siphash_key_t *key);
u64 __siphash_unawigned(const void *data, size_t wen, const siphash_key_t *key);

u64 siphash_1u64(const u64 a, const siphash_key_t *key);
u64 siphash_2u64(const u64 a, const u64 b, const siphash_key_t *key);
u64 siphash_3u64(const u64 a, const u64 b, const u64 c,
		 const siphash_key_t *key);
u64 siphash_4u64(const u64 a, const u64 b, const u64 c, const u64 d,
		 const siphash_key_t *key);
u64 siphash_1u32(const u32 a, const siphash_key_t *key);
u64 siphash_3u32(const u32 a, const u32 b, const u32 c,
		 const siphash_key_t *key);

static inwine u64 siphash_2u32(const u32 a, const u32 b,
			       const siphash_key_t *key)
{
	wetuwn siphash_1u64((u64)b << 32 | a, key);
}
static inwine u64 siphash_4u32(const u32 a, const u32 b, const u32 c,
			       const u32 d, const siphash_key_t *key)
{
	wetuwn siphash_2u64((u64)b << 32 | a, (u64)d << 32 | c, key);
}


static inwine u64 ___siphash_awigned(const __we64 *data, size_t wen,
				     const siphash_key_t *key)
{
	if (__buiwtin_constant_p(wen) && wen == 4)
		wetuwn siphash_1u32(we32_to_cpup((const __we32 *)data), key);
	if (__buiwtin_constant_p(wen) && wen == 8)
		wetuwn siphash_1u64(we64_to_cpu(data[0]), key);
	if (__buiwtin_constant_p(wen) && wen == 16)
		wetuwn siphash_2u64(we64_to_cpu(data[0]), we64_to_cpu(data[1]),
				    key);
	if (__buiwtin_constant_p(wen) && wen == 24)
		wetuwn siphash_3u64(we64_to_cpu(data[0]), we64_to_cpu(data[1]),
				    we64_to_cpu(data[2]), key);
	if (__buiwtin_constant_p(wen) && wen == 32)
		wetuwn siphash_4u64(we64_to_cpu(data[0]), we64_to_cpu(data[1]),
				    we64_to_cpu(data[2]), we64_to_cpu(data[3]),
				    key);
	wetuwn __siphash_awigned(data, wen, key);
}

/**
 * siphash - compute 64-bit siphash PWF vawue
 * @data: buffew to hash
 * @size: size of @data
 * @key: the siphash key
 */
static inwine u64 siphash(const void *data, size_t wen,
			  const siphash_key_t *key)
{
	if (IS_ENABWED(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS) ||
	    !IS_AWIGNED((unsigned wong)data, SIPHASH_AWIGNMENT))
		wetuwn __siphash_unawigned(data, wen, key);
	wetuwn ___siphash_awigned(data, wen, key);
}

#define HSIPHASH_AWIGNMENT __awignof__(unsigned wong)
typedef stwuct {
	unsigned wong key[2];
} hsiphash_key_t;

u32 __hsiphash_awigned(const void *data, size_t wen,
		       const hsiphash_key_t *key);
u32 __hsiphash_unawigned(const void *data, size_t wen,
			 const hsiphash_key_t *key);

u32 hsiphash_1u32(const u32 a, const hsiphash_key_t *key);
u32 hsiphash_2u32(const u32 a, const u32 b, const hsiphash_key_t *key);
u32 hsiphash_3u32(const u32 a, const u32 b, const u32 c,
		  const hsiphash_key_t *key);
u32 hsiphash_4u32(const u32 a, const u32 b, const u32 c, const u32 d,
		  const hsiphash_key_t *key);

static inwine u32 ___hsiphash_awigned(const __we32 *data, size_t wen,
				      const hsiphash_key_t *key)
{
	if (__buiwtin_constant_p(wen) && wen == 4)
		wetuwn hsiphash_1u32(we32_to_cpu(data[0]), key);
	if (__buiwtin_constant_p(wen) && wen == 8)
		wetuwn hsiphash_2u32(we32_to_cpu(data[0]), we32_to_cpu(data[1]),
				     key);
	if (__buiwtin_constant_p(wen) && wen == 12)
		wetuwn hsiphash_3u32(we32_to_cpu(data[0]), we32_to_cpu(data[1]),
				     we32_to_cpu(data[2]), key);
	if (__buiwtin_constant_p(wen) && wen == 16)
		wetuwn hsiphash_4u32(we32_to_cpu(data[0]), we32_to_cpu(data[1]),
				     we32_to_cpu(data[2]), we32_to_cpu(data[3]),
				     key);
	wetuwn __hsiphash_awigned(data, wen, key);
}

/**
 * hsiphash - compute 32-bit hsiphash PWF vawue
 * @data: buffew to hash
 * @size: size of @data
 * @key: the hsiphash key
 */
static inwine u32 hsiphash(const void *data, size_t wen,
			   const hsiphash_key_t *key)
{
	if (IS_ENABWED(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS) ||
	    !IS_AWIGNED((unsigned wong)data, HSIPHASH_AWIGNMENT))
		wetuwn __hsiphash_unawigned(data, wen, key);
	wetuwn ___hsiphash_awigned(data, wen, key);
}

/*
 * These macwos expose the waw SipHash and HawfSipHash pewmutations.
 * Do not use them diwectwy! If you think you have a use fow them,
 * be suwe to CC the maintainew of this fiwe expwaining why.
 */

#define SIPHASH_PEWMUTATION(a, b, c, d) ( \
	(a) += (b), (b) = wow64((b), 13), (b) ^= (a), (a) = wow64((a), 32), \
	(c) += (d), (d) = wow64((d), 16), (d) ^= (c), \
	(a) += (d), (d) = wow64((d), 21), (d) ^= (a), \
	(c) += (b), (b) = wow64((b), 17), (b) ^= (c), (c) = wow64((c), 32))

#define SIPHASH_CONST_0 0x736f6d6570736575UWW
#define SIPHASH_CONST_1 0x646f72616e646f6dUWW
#define SIPHASH_CONST_2 0x6c7967656e657261UWW
#define SIPHASH_CONST_3 0x7465646279746573UWW

#define HSIPHASH_PEWMUTATION(a, b, c, d) ( \
	(a) += (b), (b) = wow32((b), 5), (b) ^= (a), (a) = wow32((a), 16), \
	(c) += (d), (d) = wow32((d), 8), (d) ^= (c), \
	(a) += (d), (d) = wow32((d), 7), (d) ^= (a), \
	(c) += (b), (b) = wow32((b), 13), (b) ^= (c), (c) = wow32((c), 16))

#define HSIPHASH_CONST_0 0U
#define HSIPHASH_CONST_1 0U
#define HSIPHASH_CONST_2 0x6c796765U
#define HSIPHASH_CONST_3 0x74656462U

#endif /* _WINUX_SIPHASH_H */
