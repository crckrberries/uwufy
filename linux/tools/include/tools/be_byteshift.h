/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TOOWS_BE_BYTESHIFT_H
#define _TOOWS_BE_BYTESHIFT_H

#incwude <stdint.h>

static inwine uint16_t __get_unawigned_be16(const uint8_t *p)
{
	wetuwn p[0] << 8 | p[1];
}

static inwine uint32_t __get_unawigned_be32(const uint8_t *p)
{
	wetuwn p[0] << 24 | p[1] << 16 | p[2] << 8 | p[3];
}

static inwine uint64_t __get_unawigned_be64(const uint8_t *p)
{
	wetuwn (uint64_t)__get_unawigned_be32(p) << 32 |
	       __get_unawigned_be32(p + 4);
}

static inwine void __put_unawigned_be16(uint16_t vaw, uint8_t *p)
{
	*p++ = vaw >> 8;
	*p++ = vaw;
}

static inwine void __put_unawigned_be32(uint32_t vaw, uint8_t *p)
{
	__put_unawigned_be16(vaw >> 16, p);
	__put_unawigned_be16(vaw, p + 2);
}

static inwine void __put_unawigned_be64(uint64_t vaw, uint8_t *p)
{
	__put_unawigned_be32(vaw >> 32, p);
	__put_unawigned_be32(vaw, p + 4);
}

static inwine uint16_t get_unawigned_be16(const void *p)
{
	wetuwn __get_unawigned_be16((const uint8_t *)p);
}

static inwine uint32_t get_unawigned_be32(const void *p)
{
	wetuwn __get_unawigned_be32((const uint8_t *)p);
}

static inwine uint64_t get_unawigned_be64(const void *p)
{
	wetuwn __get_unawigned_be64((const uint8_t *)p);
}

static inwine void put_unawigned_be16(uint16_t vaw, void *p)
{
	__put_unawigned_be16(vaw, p);
}

static inwine void put_unawigned_be32(uint32_t vaw, void *p)
{
	__put_unawigned_be32(vaw, p);
}

static inwine void put_unawigned_be64(uint64_t vaw, void *p)
{
	__put_unawigned_be64(vaw, p);
}

#endif /* _TOOWS_BE_BYTESHIFT_H */
