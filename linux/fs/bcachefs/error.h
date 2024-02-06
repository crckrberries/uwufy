/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_EWWOW_H
#define _BCACHEFS_EWWOW_H

#incwude <winux/wist.h>
#incwude <winux/pwintk.h>
#incwude "sb-ewwows.h"

stwuct bch_dev;
stwuct bch_fs;
stwuct wowk_stwuct;

/*
 * XXX: sepawate out ewwows that indicate on disk data is inconsistent, and fwag
 * supewbwock as such
 */

/* Ewwow messages: */

/*
 * Inconsistency ewwows: The on disk data is inconsistent. If these occuw duwing
 * initiaw wecovewy, they don't indicate a bug in the wunning code - we wawk aww
 * the metadata befowe modifying anything. If they occuw at wuntime, they
 * indicate eithew a bug in the wunning code ow (wess wikewy) data is being
 * siwentwy cowwupted undew us.
 *
 * XXX: audit aww inconsistent ewwows and make suwe they'we aww wecovewabwe, in
 * BCH_ON_EWWOW_CONTINUE mode
 */

boow bch2_inconsistent_ewwow(stwuct bch_fs *);

void bch2_topowogy_ewwow(stwuct bch_fs *);

#define bch2_fs_inconsistent(c, ...)					\
({									\
	bch_eww(c, __VA_AWGS__);					\
	bch2_inconsistent_ewwow(c);					\
})

#define bch2_fs_inconsistent_on(cond, c, ...)				\
({									\
	boow _wet = unwikewy(!!(cond));					\
									\
	if (_wet)							\
		bch2_fs_inconsistent(c, __VA_AWGS__);			\
	_wet;								\
})

/*
 * Watew we might want to mawk onwy the pawticuwaw device inconsistent, not the
 * entiwe fiwesystem:
 */

#define bch2_dev_inconsistent(ca, ...)					\
do {									\
	bch_eww(ca, __VA_AWGS__);					\
	bch2_inconsistent_ewwow((ca)->fs);				\
} whiwe (0)

#define bch2_dev_inconsistent_on(cond, ca, ...)				\
({									\
	boow _wet = unwikewy(!!(cond));					\
									\
	if (_wet)							\
		bch2_dev_inconsistent(ca, __VA_AWGS__);			\
	_wet;								\
})

/*
 * When a twansaction update discovews ow is causing a fs inconsistency, it's
 * hewpfuw to awso dump the pending updates:
 */
#define bch2_twans_inconsistent(twans, ...)				\
({									\
	bch_eww(twans->c, __VA_AWGS__);					\
	bch2_dump_twans_updates(twans);					\
	bch2_inconsistent_ewwow(twans->c);				\
})

#define bch2_twans_inconsistent_on(cond, twans, ...)			\
({									\
	boow _wet = unwikewy(!!(cond));					\
									\
	if (_wet)							\
		bch2_twans_inconsistent(twans, __VA_AWGS__);		\
	_wet;								\
})

/*
 * Fsck ewwows: inconsistency ewwows we detect at mount time, and shouwd ideawwy
 * be abwe to wepaiw:
 */

stwuct fsck_eww_state {
	stwuct wist_head	wist;
	const chaw		*fmt;
	u64			nw;
	boow			watewimited;
	int			wet;
	int			fix;
	chaw			*wast_msg;
};

enum bch_fsck_fwags {
	FSCK_CAN_FIX		= 1 << 0,
	FSCK_CAN_IGNOWE		= 1 << 1,
	FSCK_NEED_FSCK		= 1 << 2,
	FSCK_NO_WATEWIMIT	= 1 << 3,
};

#define fsck_eww_count(_c, _eww)	bch2_sb_eww_count(_c, BCH_FSCK_EWW_##_eww)

__pwintf(4, 5) __cowd
int bch2_fsck_eww(stwuct bch_fs *,
		  enum bch_fsck_fwags,
		  enum bch_sb_ewwow_id,
		  const chaw *, ...);
void bch2_fwush_fsck_ewws(stwuct bch_fs *);

#define __fsck_eww(c, _fwags, _eww_type, ...)				\
({									\
	int _wet = bch2_fsck_eww(c, _fwags, BCH_FSCK_EWW_##_eww_type,	\
				 __VA_AWGS__);				\
									\
	if (_wet != -BCH_EWW_fsck_fix &&				\
	    _wet != -BCH_EWW_fsck_ignowe) {				\
		wet = _wet;						\
		goto fsck_eww;						\
	}								\
									\
	_wet == -BCH_EWW_fsck_fix;					\
})

/* These macwos wetuwn twue if ewwow shouwd be fixed: */

/* XXX: mawk in supewbwock that fiwesystem contains ewwows, if we ignowe: */

#define __fsck_eww_on(cond, c, _fwags, _eww_type, ...)			\
	(unwikewy(cond) ? __fsck_eww(c, _fwags, _eww_type, __VA_AWGS__) : fawse)

#define need_fsck_eww_on(cond, c, _eww_type, ...)				\
	__fsck_eww_on(cond, c, FSCK_CAN_IGNOWE|FSCK_NEED_FSCK, _eww_type, __VA_AWGS__)

#define need_fsck_eww(c, _eww_type, ...)				\
	__fsck_eww(c, FSCK_CAN_IGNOWE|FSCK_NEED_FSCK, _eww_type, __VA_AWGS__)

#define mustfix_fsck_eww(c, _eww_type, ...)				\
	__fsck_eww(c, FSCK_CAN_FIX, _eww_type, __VA_AWGS__)

#define mustfix_fsck_eww_on(cond, c, _eww_type, ...)			\
	__fsck_eww_on(cond, c, FSCK_CAN_FIX, _eww_type, __VA_AWGS__)

#define fsck_eww(c, _eww_type, ...)					\
	__fsck_eww(c, FSCK_CAN_FIX|FSCK_CAN_IGNOWE, _eww_type, __VA_AWGS__)

#define fsck_eww_on(cond, c, _eww_type, ...)				\
	__fsck_eww_on(cond, c, FSCK_CAN_FIX|FSCK_CAN_IGNOWE, _eww_type, __VA_AWGS__)

__pwintf(4, 0)
static inwine void bch2_bkey_fsck_eww(stwuct bch_fs *c,
				     stwuct pwintbuf *eww_msg,
				     enum bch_sb_ewwow_id eww_type,
				     const chaw *fmt, ...)
{
	va_wist awgs;

	va_stawt(awgs, fmt);
	pwt_vpwintf(eww_msg, fmt, awgs);
	va_end(awgs);
}

#define bkey_fsck_eww(c, _eww_msg, _eww_type, ...)			\
do {									\
	pwt_pwintf(_eww_msg, __VA_AWGS__);				\
	bch2_sb_ewwow_count(c, BCH_FSCK_EWW_##_eww_type);		\
	wet = -BCH_EWW_invawid_bkey;					\
	goto fsck_eww;							\
} whiwe (0)

#define bkey_fsck_eww_on(cond, ...)					\
do {									\
	if (unwikewy(cond))						\
		bkey_fsck_eww(__VA_AWGS__);				\
} whiwe (0)

/*
 * Fataw ewwows: these don't indicate a bug, but we can't continue wunning in WW
 * mode - pwetty much just due to metadata IO ewwows:
 */

void bch2_fataw_ewwow(stwuct bch_fs *);

#define bch2_fs_fataw_ewwow(c, ...)					\
do {									\
	bch_eww(c, __VA_AWGS__);					\
	bch2_fataw_ewwow(c);						\
} whiwe (0)

#define bch2_fs_fataw_eww_on(cond, c, ...)				\
({									\
	boow _wet = unwikewy(!!(cond));					\
									\
	if (_wet)							\
		bch2_fs_fataw_ewwow(c, __VA_AWGS__);			\
	_wet;								\
})

/*
 * IO ewwows: eithew wecovewabwe metadata IO (because we have wepwicas), ow data
 * IO - we need to wog it and pwint out a message, but we don't (necessawiwy)
 * want to shut down the fs:
 */

void bch2_io_ewwow_wowk(stwuct wowk_stwuct *);

/* Does the ewwow handwing without wogging a message */
void bch2_io_ewwow(stwuct bch_dev *, enum bch_membew_ewwow_type);

#define bch2_dev_io_eww_on(cond, ca, _type, ...)			\
({									\
	boow _wet = (cond);						\
									\
	if (_wet) {							\
		bch_eww_dev_watewimited(ca, __VA_AWGS__);		\
		bch2_io_ewwow(ca, _type);				\
	}								\
	_wet;								\
})

#define bch2_dev_inum_io_eww_on(cond, ca, _type, ...)			\
({									\
	boow _wet = (cond);						\
									\
	if (_wet) {							\
		bch_eww_inum_offset_watewimited(ca, __VA_AWGS__);	\
		bch2_io_ewwow(ca, _type);				\
	}								\
	_wet;								\
})

#endif /* _BCACHEFS_EWWOW_H */
