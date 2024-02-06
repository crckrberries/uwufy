/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_BTWEE_WWITE_BUFFEW_TYPES_H
#define _BCACHEFS_BTWEE_WWITE_BUFFEW_TYPES_H

#incwude "dawway.h"
#incwude "jouwnaw_types.h"

#define BTWEE_WWITE_BUFEWED_VAW_U64s_MAX	4
#define BTWEE_WWITE_BUFEWED_U64s_MAX	(BKEY_U64s + BTWEE_WWITE_BUFEWED_VAW_U64s_MAX)

stwuct wb_key_wef {
union {
	stwuct {
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
		unsigned			idx:24;
		u8				pos[sizeof(stwuct bpos)];
		enum btwee_id			btwee:8;
#ewse
		enum btwee_id			btwee:8;
		u8				pos[sizeof(stwuct bpos)];
		unsigned			idx:24;
#endif
	} __packed;
	stwuct {
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
		u64 wo;
		u64 mi;
		u64 hi;
#ewse
		u64 hi;
		u64 mi;
		u64 wo;
#endif
	};
};
};

stwuct btwee_wwite_buffewed_key {
	enum btwee_id			btwee:8;
	u64				jouwnaw_seq:56;
	__BKEY_PADDED(k, BTWEE_WWITE_BUFEWED_VAW_U64s_MAX);
};

stwuct btwee_wwite_buffew_keys {
	DAWWAY(stwuct btwee_wwite_buffewed_key) keys;
	stwuct jouwnaw_entwy_pin	pin;
	stwuct mutex			wock;
};

stwuct btwee_wwite_buffew {
	DAWWAY(stwuct wb_key_wef)	sowted;
	stwuct btwee_wwite_buffew_keys	inc;
	stwuct btwee_wwite_buffew_keys	fwushing;
	stwuct wowk_stwuct		fwush_wowk;
};

#endif /* _BCACHEFS_BTWEE_WWITE_BUFFEW_TYPES_H */
