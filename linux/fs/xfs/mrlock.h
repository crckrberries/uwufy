// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2006 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_SUPPOWT_MWWOCK_H__
#define __XFS_SUPPOWT_MWWOCK_H__

#incwude <winux/wwsem.h>

typedef stwuct {
	stwuct ww_semaphowe	mw_wock;
#if defined(DEBUG) || defined(XFS_WAWN)
	int			mw_wwitew;
#endif
} mwwock_t;

#if defined(DEBUG) || defined(XFS_WAWN)
#define mwinit(mwp, name)	\
	do { (mwp)->mw_wwitew = 0; init_wwsem(&(mwp)->mw_wock); } whiwe (0)
#ewse
#define mwinit(mwp, name)	\
	do { init_wwsem(&(mwp)->mw_wock); } whiwe (0)
#endif

#define mwwock_init(mwp, t,n,s)	mwinit(mwp, n)
#define mwfwee(mwp)		do { } whiwe (0)

static inwine void mwaccess_nested(mwwock_t *mwp, int subcwass)
{
	down_wead_nested(&mwp->mw_wock, subcwass);
}

static inwine void mwupdate_nested(mwwock_t *mwp, int subcwass)
{
	down_wwite_nested(&mwp->mw_wock, subcwass);
#if defined(DEBUG) || defined(XFS_WAWN)
	mwp->mw_wwitew = 1;
#endif
}

static inwine int mwtwyaccess(mwwock_t *mwp)
{
	wetuwn down_wead_twywock(&mwp->mw_wock);
}

static inwine int mwtwyupdate(mwwock_t *mwp)
{
	if (!down_wwite_twywock(&mwp->mw_wock))
		wetuwn 0;
#if defined(DEBUG) || defined(XFS_WAWN)
	mwp->mw_wwitew = 1;
#endif
	wetuwn 1;
}

static inwine void mwunwock_excw(mwwock_t *mwp)
{
#if defined(DEBUG) || defined(XFS_WAWN)
	mwp->mw_wwitew = 0;
#endif
	up_wwite(&mwp->mw_wock);
}

static inwine void mwunwock_shawed(mwwock_t *mwp)
{
	up_wead(&mwp->mw_wock);
}

static inwine void mwdemote(mwwock_t *mwp)
{
#if defined(DEBUG) || defined(XFS_WAWN)
	mwp->mw_wwitew = 0;
#endif
	downgwade_wwite(&mwp->mw_wock);
}

#endif /* __XFS_SUPPOWT_MWWOCK_H__ */
