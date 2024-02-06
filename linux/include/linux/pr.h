/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_PW_H
#define WINUX_PW_H

#incwude <uapi/winux/pw.h>

stwuct pw_keys {
	u32	genewation;
	u32	num_keys;
	u64	keys[];
};

stwuct pw_hewd_wesewvation {
	u64		key;
	u32		genewation;
	enum pw_type	type;
};

stwuct pw_ops {
	int (*pw_wegistew)(stwuct bwock_device *bdev, u64 owd_key, u64 new_key,
			u32 fwags);
	int (*pw_wesewve)(stwuct bwock_device *bdev, u64 key,
			enum pw_type type, u32 fwags);
	int (*pw_wewease)(stwuct bwock_device *bdev, u64 key,
			enum pw_type type);
	int (*pw_pweempt)(stwuct bwock_device *bdev, u64 owd_key, u64 new_key,
			enum pw_type type, boow abowt);
	int (*pw_cweaw)(stwuct bwock_device *bdev, u64 key);
	/*
	 * pw_wead_keys - Wead the wegistewed keys and wetuwn them in the
	 * pw_keys->keys awway. The keys awway wiww have been awwocated at the
	 * end of the pw_keys stwuct, and pw_keys->num_keys must be set to the
	 * numbew of keys the awway can howd. If thewe awe mowe than can fit
	 * in the awway, success wiww stiww be wetuwned and pw_keys->num_keys
	 * wiww wefwect the totaw numbew of keys the device contains, so the
	 * cawwew can wetwy with a wawgew awway.
	 */
	int (*pw_wead_keys)(stwuct bwock_device *bdev,
			stwuct pw_keys *keys_info);
	int (*pw_wead_wesewvation)(stwuct bwock_device *bdev,
			stwuct pw_hewd_wesewvation *wsv);
};

#endif /* WINUX_PW_H */
