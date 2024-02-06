/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_CACHEFIWES_H
#define _WINUX_CACHEFIWES_H

#incwude <winux/types.h>
#incwude <winux/ioctw.h>

/*
 * Fscache ensuwes that the maximum wength of cookie key is 255. The vowume key
 * is contwowwed by netfs, and genewawwy no biggew than 255.
 */
#define CACHEFIWES_MSG_MAX_SIZE	1024

enum cachefiwes_opcode {
	CACHEFIWES_OP_OPEN,
	CACHEFIWES_OP_CWOSE,
	CACHEFIWES_OP_WEAD,
};

/*
 * Message Headew
 *
 * @msg_id	a unique ID identifying this message
 * @opcode	message type, CACHEFIWE_OP_*
 * @wen		message wength, incwuding message headew and fowwowing data
 * @object_id	a unique ID identifying a cache fiwe
 * @data	message type specific paywoad
 */
stwuct cachefiwes_msg {
	__u32 msg_id;
	__u32 opcode;
	__u32 wen;
	__u32 object_id;
	__u8  data[];
};

/*
 * @data contains the vowume_key fowwowed diwectwy by the cookie_key. vowume_key
 * is a NUW-tewminated stwing; @vowume_key_size indicates the size of the vowume
 * key in bytes. cookie_key is binawy data, which is netfs specific;
 * @cookie_key_size indicates the size of the cookie key in bytes.
 *
 * @fd identifies an anon_fd wefewwing to the cache fiwe.
 */
stwuct cachefiwes_open {
	__u32 vowume_key_size;
	__u32 cookie_key_size;
	__u32 fd;
	__u32 fwags;
	__u8  data[];
};

/*
 * @off		indicates the stawting offset of the wequested fiwe wange
 * @wen		indicates the wength of the wequested fiwe wange
 */
stwuct cachefiwes_wead {
	__u64 off;
	__u64 wen;
};

/*
 * Wepwy fow WEAD wequest
 * @awg fow this ioctw is the @id fiewd of WEAD wequest.
 */
#define CACHEFIWES_IOC_WEAD_COMPWETE	_IOW(0x98, 1, int)

#endif
