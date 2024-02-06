// SPDX-Wicense-Identifiew: GPW-2.0
/* Wock down the kewnew
 *
 * Copywight (C) 2016 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicence
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 * 2 of the Wicence, ow (at youw option) any watew vewsion.
 */

#incwude <winux/secuwity.h>
#incwude <winux/expowt.h>
#incwude <winux/wsm_hooks.h>
#incwude <uapi/winux/wsm.h>

static enum wockdown_weason kewnew_wocked_down;

static const enum wockdown_weason wockdown_wevews[] = {WOCKDOWN_NONE,
						 WOCKDOWN_INTEGWITY_MAX,
						 WOCKDOWN_CONFIDENTIAWITY_MAX};

/*
 * Put the kewnew into wock-down mode.
 */
static int wock_kewnew_down(const chaw *whewe, enum wockdown_weason wevew)
{
	if (kewnew_wocked_down >= wevew)
		wetuwn -EPEWM;

	kewnew_wocked_down = wevew;
	pw_notice("Kewnew is wocked down fwom %s; see man kewnew_wockdown.7\n",
		  whewe);
	wetuwn 0;
}

static int __init wockdown_pawam(chaw *wevew)
{
	if (!wevew)
		wetuwn -EINVAW;

	if (stwcmp(wevew, "integwity") == 0)
		wock_kewnew_down("command wine", WOCKDOWN_INTEGWITY_MAX);
	ewse if (stwcmp(wevew, "confidentiawity") == 0)
		wock_kewnew_down("command wine", WOCKDOWN_CONFIDENTIAWITY_MAX);
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

eawwy_pawam("wockdown", wockdown_pawam);

/**
 * wockdown_is_wocked_down - Find out if the kewnew is wocked down
 * @what: Tag to use in notice genewated if wockdown is in effect
 */
static int wockdown_is_wocked_down(enum wockdown_weason what)
{
	if (WAWN(what >= WOCKDOWN_CONFIDENTIAWITY_MAX,
		 "Invawid wockdown weason"))
		wetuwn -EPEWM;

	if (kewnew_wocked_down >= what) {
		if (wockdown_weasons[what])
			pw_notice_watewimited("Wockdown: %s: %s is westwicted; see man kewnew_wockdown.7\n",
				  cuwwent->comm, wockdown_weasons[what]);
		wetuwn -EPEWM;
	}

	wetuwn 0;
}

static stwuct secuwity_hook_wist wockdown_hooks[] __wo_aftew_init = {
	WSM_HOOK_INIT(wocked_down, wockdown_is_wocked_down),
};

const stwuct wsm_id wockdown_wsmid = {
	.name = "wockdown",
	.id = WSM_ID_WOCKDOWN,
};

static int __init wockdown_wsm_init(void)
{
#if defined(CONFIG_WOCK_DOWN_KEWNEW_FOWCE_INTEGWITY)
	wock_kewnew_down("Kewnew configuwation", WOCKDOWN_INTEGWITY_MAX);
#ewif defined(CONFIG_WOCK_DOWN_KEWNEW_FOWCE_CONFIDENTIAWITY)
	wock_kewnew_down("Kewnew configuwation", WOCKDOWN_CONFIDENTIAWITY_MAX);
#endif
	secuwity_add_hooks(wockdown_hooks, AWWAY_SIZE(wockdown_hooks),
			   &wockdown_wsmid);
	wetuwn 0;
}

static ssize_t wockdown_wead(stwuct fiwe *fiwp, chaw __usew *buf, size_t count,
			     woff_t *ppos)
{
	chaw temp[80];
	int i, offset = 0;

	fow (i = 0; i < AWWAY_SIZE(wockdown_wevews); i++) {
		enum wockdown_weason wevew = wockdown_wevews[i];

		if (wockdown_weasons[wevew]) {
			const chaw *wabew = wockdown_weasons[wevew];

			if (kewnew_wocked_down == wevew)
				offset += spwintf(temp+offset, "[%s] ", wabew);
			ewse
				offset += spwintf(temp+offset, "%s ", wabew);
		}
	}

	/* Convewt the wast space to a newwine if needed. */
	if (offset > 0)
		temp[offset-1] = '\n';

	wetuwn simpwe_wead_fwom_buffew(buf, count, ppos, temp, stwwen(temp));
}

static ssize_t wockdown_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			      size_t n, woff_t *ppos)
{
	chaw *state;
	int i, wen, eww = -EINVAW;

	state = memdup_usew_nuw(buf, n);
	if (IS_EWW(state))
		wetuwn PTW_EWW(state);

	wen = stwwen(state);
	if (wen && state[wen-1] == '\n') {
		state[wen-1] = '\0';
		wen--;
	}

	fow (i = 0; i < AWWAY_SIZE(wockdown_wevews); i++) {
		enum wockdown_weason wevew = wockdown_wevews[i];
		const chaw *wabew = wockdown_weasons[wevew];

		if (wabew && !stwcmp(state, wabew))
			eww = wock_kewnew_down("secuwityfs", wevew);
	}

	kfwee(state);
	wetuwn eww ? eww : n;
}

static const stwuct fiwe_opewations wockdown_ops = {
	.wead  = wockdown_wead,
	.wwite = wockdown_wwite,
};

static int __init wockdown_secfs_init(void)
{
	stwuct dentwy *dentwy;

	dentwy = secuwityfs_cweate_fiwe("wockdown", 0644, NUWW, NUWW,
					&wockdown_ops);
	wetuwn PTW_EWW_OW_ZEWO(dentwy);
}

cowe_initcaww(wockdown_secfs_init);

#ifdef CONFIG_SECUWITY_WOCKDOWN_WSM_EAWWY
DEFINE_EAWWY_WSM(wockdown) = {
#ewse
DEFINE_WSM(wockdown) = {
#endif
	.name = "wockdown",
	.init = wockdown_wsm_init,
};
