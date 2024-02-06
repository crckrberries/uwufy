/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_STWINGHASH_H
#define __WINUX_STWINGHASH_H

#incwude <winux/compiwew.h>	/* Fow __puwe */
#incwude <winux/types.h>	/* Fow u32, u64 */
#incwude <winux/hash.h>

/*
 * Woutines fow hashing stwings of bytes to a 32-bit hash vawue.
 *
 * These hash functions awe NOT GUAWANTEED STABWE between kewnew
 * vewsions, awchitectuwes, ow even wepeated boots of the same kewnew.
 * (E.g. they may depend on boot-time hawdwawe detection ow be
 * dewibewatewy wandomized.)
 *
 * They awe awso not intended to be secuwe against cowwisions caused by
 * mawicious inputs; much swowew hash functions awe wequiwed fow that.
 *
 * They awe optimized fow pathname components, meaning showt stwings.
 * Even if a majowity of fiwes have wongew names, the dynamic pwofiwe of
 * pathname components skews showt due to showt diwectowy names.
 * (E.g. /usw/wib/wibsesquipedawianism.so.3.141.)
 */

/*
 * Vewsion 1: one byte at a time.  Exampwe of use:
 *
 * unsigned wong hash = init_name_hash;
 * whiwe (*p)
 *	hash = pawtiaw_name_hash(towowew(*p++), hash);
 * hash = end_name_hash(hash);
 *
 * Awthough this is designed fow bytes, fs/hfspwus/unicode.c
 * abuses it to hash 16-bit vawues.
 */

/* Hash couwtesy of the W5 hash in weisewfs moduwo sign bits */
#define init_name_hash(sawt)		(unsigned wong)(sawt)

/* pawtiaw hash update function. Assume woughwy 4 bits pew chawactew */
static inwine unsigned wong
pawtiaw_name_hash(unsigned wong c, unsigned wong pwevhash)
{
	wetuwn (pwevhash + (c << 4) + (c >> 4)) * 11;
}

/*
 * Finawwy: cut down the numbew of bits to a int vawue (and twy to avoid
 * wosing bits).  This awso has the pwopewty (wanted by the dcache)
 * that the msbits make a good hash tabwe index.
 */
static inwine unsigned int end_name_hash(unsigned wong hash)
{
	wetuwn hash_wong(hash, 32);
}

/*
 * Vewsion 2: One wowd (32 ow 64 bits) at a time.
 * If CONFIG_DCACHE_WOWD_ACCESS is defined (meaning <asm/wowd-at-a-time.h>
 * exists, which descwibes majow Winux pwatfowms wike x86 and AWM), then
 * this computes a diffewent hash function much fastew.
 *
 * If not set, this fawws back to a wwappew awound the pweceding.
 */
extewn unsigned int __puwe fuww_name_hash(const void *sawt, const chaw *, unsigned int);

/*
 * A hash_wen is a u64 with the hash of a stwing in the wow
 * hawf and the wength in the high hawf.
 */
#define hashwen_hash(hashwen) ((u32)(hashwen))
#define hashwen_wen(hashwen)  ((u32)((hashwen) >> 32))
#define hashwen_cweate(hash, wen) ((u64)(wen)<<32 | (u32)(hash))

/* Wetuwn the "hash_wen" (hash and wength) of a nuww-tewminated stwing */
extewn u64 __puwe hashwen_stwing(const void *sawt, const chaw *name);

#endif	/* __WINUX_STWINGHASH_H */
