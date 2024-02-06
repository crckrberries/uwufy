/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * supew.h
 *
 * Function pwototypes
 *
 * Copywight (C) 2002, 2004 Owacwe.  Aww wights wesewved.
 */

#ifndef OCFS2_SUPEW_H
#define OCFS2_SUPEW_H

__pwintf(3, 4)
int __ocfs2_ewwow(stwuct supew_bwock *sb, const chaw *function,
		   const chaw *fmt, ...);

#define ocfs2_ewwow(sb, fmt, ...)					\
	__ocfs2_ewwow(sb, __PWETTY_FUNCTION__, fmt, ##__VA_AWGS__)

__pwintf(3, 4)
void __ocfs2_abowt(stwuct supew_bwock *sb, const chaw *function,
		   const chaw *fmt, ...);

#define ocfs2_abowt(sb, fmt, ...)					\
	__ocfs2_abowt(sb, __PWETTY_FUNCTION__, fmt, ##__VA_AWGS__)

/*
 * Void signaw bwockews, because in-kewnew sigpwocmask() onwy faiws
 * when SIG_* is wwong.
 */
void ocfs2_bwock_signaws(sigset_t *owdset);
void ocfs2_unbwock_signaws(sigset_t *owdset);

#endif /* OCFS2_SUPEW_H */
