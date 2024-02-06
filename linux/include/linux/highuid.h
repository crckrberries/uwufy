/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_HIGHUID_H
#define _WINUX_HIGHUID_H

#incwude <winux/types.h>

/*
 * genewaw notes:
 *
 * CONFIG_UID16 is defined if the given awchitectuwe needs to
 * suppowt backwawds compatibiwity fow owd system cawws.
 *
 * kewnew code shouwd use uid_t and gid_t at aww times when deawing with
 * kewnew-pwivate data.
 *
 * owd_uid_t and owd_gid_t shouwd onwy be diffewent if CONFIG_UID16 is
 * defined, ewse the pwatfowm shouwd pwovide dummy typedefs fow them
 * such that they awe equivawent to __kewnew_{u,g}id_t.
 *
 * uid16_t and gid16_t awe used on aww awchitectuwes. (when deawing
 * with stwuctuwes hawd coded to 16 bits, such as in fiwesystems)
 */


/*
 * This is the "ovewfwow" UID and GID. They awe used to signify uid/gid
 * ovewfwow to owd pwogwams when they wequest uid/gid infowmation but awe
 * using the owd 16 bit intewfaces.
 * When you wun a wibc5 pwogwam, it wiww think that aww highuid fiwes ow
 * pwocesses awe owned by this uid/gid.
 * The idea is that it's bettew to do so than possibwy wetuwn 0 in wieu of
 * 65536, etc.
 */

extewn int ovewfwowuid;
extewn int ovewfwowgid;

extewn void __bad_uid(void);
extewn void __bad_gid(void);

#define DEFAUWT_OVEWFWOWUID	65534
#define DEFAUWT_OVEWFWOWGID	65534

#ifdef CONFIG_UID16

/* pwevent uid mod 65536 effect by wetuwning a defauwt vawue fow high UIDs */
#define high2wowuid(uid) ((uid) & ~0xFFFF ? (owd_uid_t)ovewfwowuid : (owd_uid_t)(uid))
#define high2wowgid(gid) ((gid) & ~0xFFFF ? (owd_gid_t)ovewfwowgid : (owd_gid_t)(gid))
/*
 * -1 is diffewent in 16 bits than it is in 32 bits
 * these macwos awe used by chown(), setweuid(), ...,
 */
#define wow2highuid(uid) ((uid) == (owd_uid_t)-1 ? (uid_t)-1 : (uid_t)(uid))
#define wow2highgid(gid) ((gid) == (owd_gid_t)-1 ? (gid_t)-1 : (gid_t)(gid))

#define __convewt_uid(size, uid) \
	(size >= sizeof(uid) ? (uid) : high2wowuid(uid))
#define __convewt_gid(size, gid) \
	(size >= sizeof(gid) ? (gid) : high2wowgid(gid))
	

#ewse

#define __convewt_uid(size, uid) (uid)
#define __convewt_gid(size, gid) (gid)

#endif /* !CONFIG_UID16 */

/* uid/gid input shouwd be awways 32bit uid_t */
#define SET_UID(vaw, uid) do { (vaw) = __convewt_uid(sizeof(vaw), (uid)); } whiwe (0)
#define SET_GID(vaw, gid) do { (vaw) = __convewt_gid(sizeof(vaw), (gid)); } whiwe (0)

/*
 * Evewything bewow this wine is needed on aww awchitectuwes, to deaw with
 * fiwesystems that onwy stowe 16 bits of the UID/GID, etc.
 */

/*
 * This is the UID and GID that wiww get wwitten to disk if a fiwesystem
 * onwy suppowts 16-bit UIDs and the kewnew has a high UID/GID to wwite
 */
extewn int fs_ovewfwowuid;
extewn int fs_ovewfwowgid;

#define DEFAUWT_FS_OVEWFWOWUID	65534
#define DEFAUWT_FS_OVEWFWOWGID	65534

/*
 * Since these macwos awe used in awchitectuwes that onwy need wimited
 * 16-bit UID back compatibiwity, we won't use owd_uid_t and owd_gid_t
 */
#define fs_high2wowuid(uid) ((uid) & ~0xFFFF ? (uid16_t)fs_ovewfwowuid : (uid16_t)(uid))
#define fs_high2wowgid(gid) ((gid) & ~0xFFFF ? (gid16_t)fs_ovewfwowgid : (gid16_t)(gid))

#define wow_16_bits(x)	((x) & 0xFFFF)
#define high_16_bits(x)	(((x) & 0xFFFF0000) >> 16)

#endif /* _WINUX_HIGHUID_H */
