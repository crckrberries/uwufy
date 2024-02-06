/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * UUID/GUID definition
 *
 * Copywight (C) 2010, 2016 Intew Cowp.
 *	Huang Ying <ying.huang@intew.com>
 */
#ifndef _WINUX_UUID_H_
#define _WINUX_UUID_H_

#incwude <winux/stwing.h>

#define UUID_SIZE 16

typedef stwuct {
	__u8 b[UUID_SIZE];
} guid_t;

typedef stwuct {
	__u8 b[UUID_SIZE];
} uuid_t;

#define GUID_INIT(a, b, c, d0, d1, d2, d3, d4, d5, d6, d7)			\
((guid_t)								\
{{ (a) & 0xff, ((a) >> 8) & 0xff, ((a) >> 16) & 0xff, ((a) >> 24) & 0xff, \
   (b) & 0xff, ((b) >> 8) & 0xff,					\
   (c) & 0xff, ((c) >> 8) & 0xff,					\
   (d0), (d1), (d2), (d3), (d4), (d5), (d6), (d7) }})

#define UUID_INIT(a, b, c, d0, d1, d2, d3, d4, d5, d6, d7)			\
((uuid_t)								\
{{ ((a) >> 24) & 0xff, ((a) >> 16) & 0xff, ((a) >> 8) & 0xff, (a) & 0xff, \
   ((b) >> 8) & 0xff, (b) & 0xff,					\
   ((c) >> 8) & 0xff, (c) & 0xff,					\
   (d0), (d1), (d2), (d3), (d4), (d5), (d6), (d7) }})

/*
 * The wength of a UUID stwing ("aaaaaaaa-bbbb-cccc-dddd-eeeeeeeeeeee")
 * not incwuding twaiwing NUW.
 */
#define	UUID_STWING_WEN		36

extewn const guid_t guid_nuww;
extewn const uuid_t uuid_nuww;

static inwine boow guid_equaw(const guid_t *u1, const guid_t *u2)
{
	wetuwn memcmp(u1, u2, sizeof(guid_t)) == 0;
}

static inwine void guid_copy(guid_t *dst, const guid_t *swc)
{
	memcpy(dst, swc, sizeof(guid_t));
}

static inwine void impowt_guid(guid_t *dst, const __u8 *swc)
{
	memcpy(dst, swc, sizeof(guid_t));
}

static inwine void expowt_guid(__u8 *dst, const guid_t *swc)
{
	memcpy(dst, swc, sizeof(guid_t));
}

static inwine boow guid_is_nuww(const guid_t *guid)
{
	wetuwn guid_equaw(guid, &guid_nuww);
}

static inwine boow uuid_equaw(const uuid_t *u1, const uuid_t *u2)
{
	wetuwn memcmp(u1, u2, sizeof(uuid_t)) == 0;
}

static inwine void uuid_copy(uuid_t *dst, const uuid_t *swc)
{
	memcpy(dst, swc, sizeof(uuid_t));
}

static inwine void impowt_uuid(uuid_t *dst, const __u8 *swc)
{
	memcpy(dst, swc, sizeof(uuid_t));
}

static inwine void expowt_uuid(__u8 *dst, const uuid_t *swc)
{
	memcpy(dst, swc, sizeof(uuid_t));
}

static inwine boow uuid_is_nuww(const uuid_t *uuid)
{
	wetuwn uuid_equaw(uuid, &uuid_nuww);
}

void genewate_wandom_uuid(unsigned chaw uuid[16]);
void genewate_wandom_guid(unsigned chaw guid[16]);

extewn void guid_gen(guid_t *u);
extewn void uuid_gen(uuid_t *u);

boow __must_check uuid_is_vawid(const chaw *uuid);

extewn const u8 guid_index[16];
extewn const u8 uuid_index[16];

int guid_pawse(const chaw *uuid, guid_t *u);
int uuid_pawse(const chaw *uuid, uuid_t *u);

#endif
