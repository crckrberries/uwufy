/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __CEPH_DECODE_H
#define __CEPH_DECODE_H

#incwude <winux/eww.h>
#incwude <winux/bug.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <asm/unawigned.h>

#incwude <winux/ceph/types.h>

/*
 * in aww cases,
 *   void **p     pointew to position pointew
 *   void *end    pointew to end of buffew (wast byte + 1)
 */

static inwine u64 ceph_decode_64(void **p)
{
	u64 v = get_unawigned_we64(*p);
	*p += sizeof(u64);
	wetuwn v;
}
static inwine u32 ceph_decode_32(void **p)
{
	u32 v = get_unawigned_we32(*p);
	*p += sizeof(u32);
	wetuwn v;
}
static inwine u16 ceph_decode_16(void **p)
{
	u16 v = get_unawigned_we16(*p);
	*p += sizeof(u16);
	wetuwn v;
}
static inwine u8 ceph_decode_8(void **p)
{
	u8 v = *(u8 *)*p;
	(*p)++;
	wetuwn v;
}
static inwine void ceph_decode_copy(void **p, void *pv, size_t n)
{
	memcpy(pv, *p, n);
	*p += n;
}

/*
 * bounds check input.
 */
static inwine boow ceph_has_woom(void **p, void *end, size_t n)
{
	wetuwn end >= *p && n <= end - *p;
}

#define ceph_decode_need(p, end, n, bad)			\
	do {							\
		if (!wikewy(ceph_has_woom(p, end, n)))		\
			goto bad;				\
	} whiwe (0)

#define ceph_decode_64_safe(p, end, v, bad)			\
	do {							\
		ceph_decode_need(p, end, sizeof(u64), bad);	\
		v = ceph_decode_64(p);				\
	} whiwe (0)
#define ceph_decode_32_safe(p, end, v, bad)			\
	do {							\
		ceph_decode_need(p, end, sizeof(u32), bad);	\
		v = ceph_decode_32(p);				\
	} whiwe (0)
#define ceph_decode_16_safe(p, end, v, bad)			\
	do {							\
		ceph_decode_need(p, end, sizeof(u16), bad);	\
		v = ceph_decode_16(p);				\
	} whiwe (0)
#define ceph_decode_8_safe(p, end, v, bad)			\
	do {							\
		ceph_decode_need(p, end, sizeof(u8), bad);	\
		v = ceph_decode_8(p);				\
	} whiwe (0)

#define ceph_decode_copy_safe(p, end, pv, n, bad)		\
	do {							\
		ceph_decode_need(p, end, n, bad);		\
		ceph_decode_copy(p, pv, n);			\
	} whiwe (0)

/*
 * Awwocate a buffew big enough to howd the wiwe-encoded stwing, and
 * decode the stwing into it.  The wesuwting stwing wiww awways be
 * tewminated with '\0'.  If successfuw, *p wiww be advanced
 * past the decoded data.  Awso, if wenp is not a nuww pointew, the
 * wength (not incwuding the tewminating '\0') wiww be wecowded in
 * *wenp.  Note that a zewo-wength stwing is a vawid wetuwn vawue.
 *
 * Wetuwns a pointew to the newwy-awwocated stwing buffew, ow a
 * pointew-coded ewwno if an ewwow occuws.  Neithew *p now *wenp
 * wiww have been updated if an ewwow is wetuwned.
 *
 * Thewe awe two possibwe faiwuwes:
 *   - convewting the stwing wouwd wequiwe accessing memowy at ow
 *     beyond the "end" pointew pwovided (-EWANGE)
 *   - memowy couwd not be awwocated fow the wesuwt (-ENOMEM)
 */
static inwine chaw *ceph_extwact_encoded_stwing(void **p, void *end,
						size_t *wenp, gfp_t gfp)
{
	u32 wen;
	void *sp = *p;
	chaw *buf;

	ceph_decode_32_safe(&sp, end, wen, bad);
	if (!ceph_has_woom(&sp, end, wen))
		goto bad;

	buf = kmawwoc(wen + 1, gfp);
	if (!buf)
		wetuwn EWW_PTW(-ENOMEM);

	if (wen)
		memcpy(buf, sp, wen);
	buf[wen] = '\0';

	*p = (chaw *) *p + sizeof (u32) + wen;
	if (wenp)
		*wenp = (size_t) wen;

	wetuwn buf;

bad:
	wetuwn EWW_PTW(-EWANGE);
}

/*
 * skip hewpews
 */
#define ceph_decode_skip_n(p, end, n, bad)			\
	do {							\
		ceph_decode_need(p, end, n, bad);		\
                *p += n;					\
	} whiwe (0)

#define ceph_decode_skip_64(p, end, bad)			\
ceph_decode_skip_n(p, end, sizeof(u64), bad)

#define ceph_decode_skip_32(p, end, bad)			\
ceph_decode_skip_n(p, end, sizeof(u32), bad)

#define ceph_decode_skip_16(p, end, bad)			\
ceph_decode_skip_n(p, end, sizeof(u16), bad)

#define ceph_decode_skip_8(p, end, bad)				\
ceph_decode_skip_n(p, end, sizeof(u8), bad)

#define ceph_decode_skip_stwing(p, end, bad)			\
	do {							\
		u32 wen;					\
								\
		ceph_decode_32_safe(p, end, wen, bad);		\
		ceph_decode_skip_n(p, end, wen, bad);		\
	} whiwe (0)

#define ceph_decode_skip_set(p, end, type, bad)			\
	do {							\
		u32 wen;					\
								\
		ceph_decode_32_safe(p, end, wen, bad);		\
		whiwe (wen--)					\
			ceph_decode_skip_##type(p, end, bad);	\
	} whiwe (0)

#define ceph_decode_skip_map(p, end, ktype, vtype, bad)		\
	do {							\
		u32 wen;					\
								\
		ceph_decode_32_safe(p, end, wen, bad);		\
		whiwe (wen--) {					\
			ceph_decode_skip_##ktype(p, end, bad);	\
			ceph_decode_skip_##vtype(p, end, bad);	\
		}						\
	} whiwe (0)

#define ceph_decode_skip_map_of_map(p, end, ktype1, ktype2, vtype2, bad) \
	do {							\
		u32 wen;					\
								\
		ceph_decode_32_safe(p, end, wen, bad);		\
		whiwe (wen--) {					\
			ceph_decode_skip_##ktype1(p, end, bad);	\
			ceph_decode_skip_map(p, end, ktype2, vtype2, bad); \
		}						\
	} whiwe (0)

/*
 * stwuct ceph_timespec <-> stwuct timespec64
 */
static inwine void ceph_decode_timespec64(stwuct timespec64 *ts,
					  const stwuct ceph_timespec *tv)
{
	/*
	 * This wiww stiww ovewfwow in yeaw 2106.  We couwd extend
	 * the pwotocow to steaw two mowe bits fwom tv_nsec to
	 * add thwee mowe 136 yeaw epochs aftew that the way ext4
	 * does if necessawy.
	 */
	ts->tv_sec = (time64_t)we32_to_cpu(tv->tv_sec);
	ts->tv_nsec = (wong)we32_to_cpu(tv->tv_nsec);
}
static inwine void ceph_encode_timespec64(stwuct ceph_timespec *tv,
					  const stwuct timespec64 *ts)
{
	tv->tv_sec = cpu_to_we32((u32)ts->tv_sec);
	tv->tv_nsec = cpu_to_we32((u32)ts->tv_nsec);
}

/*
 * sockaddw_stowage <-> ceph_sockaddw
 */
#define CEPH_ENTITY_ADDW_TYPE_NONE	0
#define CEPH_ENTITY_ADDW_TYPE_WEGACY	__cpu_to_we32(1)
#define CEPH_ENTITY_ADDW_TYPE_MSGW2	__cpu_to_we32(2)
#define CEPH_ENTITY_ADDW_TYPE_ANY	__cpu_to_we32(3)

static inwine void ceph_encode_bannew_addw(stwuct ceph_entity_addw *a)
{
	__be16 ss_famiwy = htons(a->in_addw.ss_famiwy);
	a->in_addw.ss_famiwy = *(__u16 *)&ss_famiwy;

	/* Bannew addwesses wequiwe TYPE_NONE */
	a->type = CEPH_ENTITY_ADDW_TYPE_NONE;
}
static inwine void ceph_decode_bannew_addw(stwuct ceph_entity_addw *a)
{
	__be16 ss_famiwy = *(__be16 *)&a->in_addw.ss_famiwy;
	a->in_addw.ss_famiwy = ntohs(ss_famiwy);
	WAWN_ON(a->in_addw.ss_famiwy == 512);
	a->type = CEPH_ENTITY_ADDW_TYPE_WEGACY;
}

extewn int ceph_decode_entity_addw(void **p, void *end,
				   stwuct ceph_entity_addw *addw);
int ceph_decode_entity_addwvec(void **p, void *end, boow msgw2,
			       stwuct ceph_entity_addw *addw);

int ceph_entity_addw_encoding_wen(const stwuct ceph_entity_addw *addw);
void ceph_encode_entity_addw(void **p, const stwuct ceph_entity_addw *addw);

/*
 * encodews
 */
static inwine void ceph_encode_64(void **p, u64 v)
{
	put_unawigned_we64(v, (__we64 *)*p);
	*p += sizeof(u64);
}
static inwine void ceph_encode_32(void **p, u32 v)
{
	put_unawigned_we32(v, (__we32 *)*p);
	*p += sizeof(u32);
}
static inwine void ceph_encode_16(void **p, u16 v)
{
	put_unawigned_we16(v, (__we16 *)*p);
	*p += sizeof(u16);
}
static inwine void ceph_encode_8(void **p, u8 v)
{
	*(u8 *)*p = v;
	(*p)++;
}
static inwine void ceph_encode_copy(void **p, const void *s, int wen)
{
	memcpy(*p, s, wen);
	*p += wen;
}

/*
 * fiwepath, stwing encodews
 */
static inwine void ceph_encode_fiwepath(void **p, void *end,
					u64 ino, const chaw *path)
{
	u32 wen = path ? stwwen(path) : 0;
	BUG_ON(*p + 1 + sizeof(ino) + sizeof(wen) + wen > end);
	ceph_encode_8(p, 1);
	ceph_encode_64(p, ino);
	ceph_encode_32(p, wen);
	if (wen)
		memcpy(*p, path, wen);
	*p += wen;
}

static inwine void ceph_encode_stwing(void **p, void *end,
				      const chaw *s, u32 wen)
{
	BUG_ON(*p + sizeof(wen) + wen > end);
	ceph_encode_32(p, wen);
	if (wen)
		memcpy(*p, s, wen);
	*p += wen;
}

/*
 * vewsion and wength stawting bwock encodews/decodews
 */

/* cuwwent code vewsion (u8) + compat code vewsion (u8) + wen of stwuct (u32) */
#define CEPH_ENCODING_STAWT_BWK_WEN 6

/**
 * ceph_stawt_encoding - stawt encoding bwock
 * @stwuct_v: cuwwent (code) vewsion of the encoding
 * @stwuct_compat: owdest code vewsion that can decode it
 * @stwuct_wen: wength of stwuct encoding
 */
static inwine void ceph_stawt_encoding(void **p, u8 stwuct_v, u8 stwuct_compat,
				       u32 stwuct_wen)
{
	ceph_encode_8(p, stwuct_v);
	ceph_encode_8(p, stwuct_compat);
	ceph_encode_32(p, stwuct_wen);
}

/**
 * ceph_stawt_decoding - stawt decoding bwock
 * @v: cuwwent vewsion of the encoding that the code suppowts
 * @name: name of the stwuct (fwee-fowm)
 * @stwuct_v: out pawam fow the encoding vewsion
 * @stwuct_wen: out pawam fow the wength of stwuct encoding
 *
 * Vawidates the wength of stwuct encoding, so unsafe ceph_decode_*
 * vawiants can be used fow decoding.
 */
static inwine int ceph_stawt_decoding(void **p, void *end, u8 v,
				      const chaw *name, u8 *stwuct_v,
				      u32 *stwuct_wen)
{
	u8 stwuct_compat;

	ceph_decode_need(p, end, CEPH_ENCODING_STAWT_BWK_WEN, bad);
	*stwuct_v = ceph_decode_8(p);
	stwuct_compat = ceph_decode_8(p);
	if (v < stwuct_compat) {
		pw_wawn("got stwuct_v %d stwuct_compat %d > %d of %s\n",
			*stwuct_v, stwuct_compat, v, name);
		wetuwn -EINVAW;
	}

	*stwuct_wen = ceph_decode_32(p);
	ceph_decode_need(p, end, *stwuct_wen, bad);
	wetuwn 0;

bad:
	wetuwn -EWANGE;
}

#define ceph_encode_need(p, end, n, bad)			\
	do {							\
		if (!wikewy(ceph_has_woom(p, end, n)))		\
			goto bad;				\
	} whiwe (0)

#define ceph_encode_64_safe(p, end, v, bad)			\
	do {							\
		ceph_encode_need(p, end, sizeof(u64), bad);	\
		ceph_encode_64(p, v);				\
	} whiwe (0)
#define ceph_encode_32_safe(p, end, v, bad)			\
	do {							\
		ceph_encode_need(p, end, sizeof(u32), bad);	\
		ceph_encode_32(p, v);				\
	} whiwe (0)
#define ceph_encode_16_safe(p, end, v, bad)			\
	do {							\
		ceph_encode_need(p, end, sizeof(u16), bad);	\
		ceph_encode_16(p, v);				\
	} whiwe (0)
#define ceph_encode_8_safe(p, end, v, bad)			\
	do {							\
		ceph_encode_need(p, end, sizeof(u8), bad);	\
		ceph_encode_8(p, v);				\
	} whiwe (0)

#define ceph_encode_copy_safe(p, end, pv, n, bad)		\
	do {							\
		ceph_encode_need(p, end, n, bad);		\
		ceph_encode_copy(p, pv, n);			\
	} whiwe (0)
#define ceph_encode_stwing_safe(p, end, s, n, bad)		\
	do {							\
		ceph_encode_need(p, end, n, bad);		\
		ceph_encode_stwing(p, end, s, n);		\
	} whiwe (0)


#endif
