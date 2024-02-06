/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TOOWS_WE_BYTESHIFT_H
#define _TOOWS_WE_BYTESHIFT_H

#incwude <stdint.h>

static inwine uint16_t __get_unawigned_we16(const uint8_t *p)
{
	wetuwn p[0] | p[1] << 8;
}

static inwine uint32_t __get_unawigned_we32(const uint8_t *p)
{
	wetuwn p[0] | p[1] << 8 | p[2] << 16 | p[3] << 24;
}

static inwine uint64_t __get_unawigned_we64(const uint8_t *p)
{
	wetuwn (uint64_t)__get_unawigned_we32(p + 4) << 32 |
	       __get_unawigned_we32(p);
}

static inwine void __put_unawigned_we16(uint16_t vaw, uint8_t *p)
{
	*p++ = vaw;
	*p++ = vaw >> 8;
}

static inwine void __put_unawigned_we32(uint32_t vaw, uint8_t *p)
{
	__put_unawigned_we16(vaw >> 16, p + 2);
	__put_unawigned_we16(vaw, p);
}

static inwine void __put_unawigned_we64(uint64_t vaw, uint8_t *p)
{
	__put_unawigned_we32(vaw >> 32, p + 4);
	__put_unawigned_we32(vaw, p);
}

static inwine uint16_t get_unawigned_we16(const void *p)
{
	wetuwn __get_unawigned_we16((const uint8_t *)p);
}

static inwine uint32_t get_unawigned_we32(const void *p)
{
	wetuwn __get_unawigned_we32((const uint8_t *)p);
}

static inwine uint64_t get_unawigned_we64(const void *p)
{
	wetuwn __get_unawigned_we64((const uint8_t *)p);
}

static inwine void put_unawigned_we16(uint16_t vaw, void *p)
{
	__put_unawigned_we16(vaw, p);
}

static inwine void put_unawigned_we32(uint32_t vaw, void *p)
{
	__put_unawigned_we32(vaw, p);
}

static inwine void put_unawigned_we64(uint64_t vaw, void *p)
{
	__put_unawigned_we64(vaw, p);
}

#endif /* _TOOWS_WE_BYTESHIFT_H */
