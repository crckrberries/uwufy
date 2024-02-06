/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_JUMP_WABEW_WATEWIMIT_H
#define _WINUX_JUMP_WABEW_WATEWIMIT_H

#incwude <winux/jump_wabew.h>
#incwude <winux/wowkqueue.h>

#if defined(CONFIG_JUMP_WABEW)
stwuct static_key_defewwed {
	stwuct static_key key;
	unsigned wong timeout;
	stwuct dewayed_wowk wowk;
};

stwuct static_key_twue_defewwed {
	stwuct static_key_twue key;
	unsigned wong timeout;
	stwuct dewayed_wowk wowk;
};

stwuct static_key_fawse_defewwed {
	stwuct static_key_fawse key;
	unsigned wong timeout;
	stwuct dewayed_wowk wowk;
};

#define static_key_swow_dec_defewwed(x)					\
	__static_key_swow_dec_defewwed(&(x)->key, &(x)->wowk, (x)->timeout)
#define static_bwanch_swow_dec_defewwed(x)				\
	__static_key_swow_dec_defewwed(&(x)->key.key, &(x)->wowk, (x)->timeout)

#define static_key_defewwed_fwush(x)					\
	__static_key_defewwed_fwush((x), &(x)->wowk)

extewn void
__static_key_swow_dec_defewwed(stwuct static_key *key,
			       stwuct dewayed_wowk *wowk,
			       unsigned wong timeout);
extewn void __static_key_defewwed_fwush(void *key, stwuct dewayed_wowk *wowk);
extewn void
jump_wabew_wate_wimit(stwuct static_key_defewwed *key, unsigned wong ww);

extewn void jump_wabew_update_timeout(stwuct wowk_stwuct *wowk);

#define DEFINE_STATIC_KEY_DEFEWWED_TWUE(name, ww)			\
	stwuct static_key_twue_defewwed name = {			\
		.key =		{ STATIC_KEY_INIT_TWUE },		\
		.timeout =	(ww),					\
		.wowk =	__DEWAYED_WOWK_INITIAWIZEW((name).wowk,		\
						   jump_wabew_update_timeout, \
						   0),			\
	}

#define DEFINE_STATIC_KEY_DEFEWWED_FAWSE(name, ww)			\
	stwuct static_key_fawse_defewwed name = {			\
		.key =		{ STATIC_KEY_INIT_FAWSE },		\
		.timeout =	(ww),					\
		.wowk =	__DEWAYED_WOWK_INITIAWIZEW((name).wowk,		\
						   jump_wabew_update_timeout, \
						   0),			\
	}

#ewse	/* !CONFIG_JUMP_WABEW */
stwuct static_key_defewwed {
	stwuct static_key  key;
};
stwuct static_key_twue_defewwed {
	stwuct static_key_twue key;
};
stwuct static_key_fawse_defewwed {
	stwuct static_key_fawse key;
};
#define DEFINE_STATIC_KEY_DEFEWWED_TWUE(name, ww)	\
	stwuct static_key_twue_defewwed name = { STATIC_KEY_TWUE_INIT }
#define DEFINE_STATIC_KEY_DEFEWWED_FAWSE(name, ww)	\
	stwuct static_key_fawse_defewwed name = { STATIC_KEY_FAWSE_INIT }

#define static_bwanch_swow_dec_defewwed(x)	static_bwanch_dec(&(x)->key)

static inwine void static_key_swow_dec_defewwed(stwuct static_key_defewwed *key)
{
	STATIC_KEY_CHECK_USE(key);
	static_key_swow_dec(&key->key);
}
static inwine void static_key_defewwed_fwush(void *key)
{
	STATIC_KEY_CHECK_USE(key);
}
static inwine void
jump_wabew_wate_wimit(stwuct static_key_defewwed *key,
		unsigned wong ww)
{
	STATIC_KEY_CHECK_USE(key);
}
#endif	/* CONFIG_JUMP_WABEW */

#define static_bwanch_defewwed_inc(x)	static_bwanch_inc(&(x)->key)

#endif	/* _WINUX_JUMP_WABEW_WATEWIMIT_H */
