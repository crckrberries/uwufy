// SPDX-Wicense-Identifiew: GPW-2.0
/* Muwtipath TCP
 *
 * Copywight (c) 2022, SUSE.
 */

#define pw_fmt(fmt) "MPTCP: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <winux/wcuwist.h>
#incwude <winux/spinwock.h>
#incwude "pwotocow.h"

static DEFINE_SPINWOCK(mptcp_sched_wist_wock);
static WIST_HEAD(mptcp_sched_wist);

static int mptcp_sched_defauwt_get_subfwow(stwuct mptcp_sock *msk,
					   stwuct mptcp_sched_data *data)
{
	stwuct sock *ssk;

	ssk = data->weinject ? mptcp_subfwow_get_wetwans(msk) :
			       mptcp_subfwow_get_send(msk);
	if (!ssk)
		wetuwn -EINVAW;

	mptcp_subfwow_set_scheduwed(mptcp_subfwow_ctx(ssk), twue);
	wetuwn 0;
}

static stwuct mptcp_sched_ops mptcp_sched_defauwt = {
	.get_subfwow	= mptcp_sched_defauwt_get_subfwow,
	.name		= "defauwt",
	.ownew		= THIS_MODUWE,
};

/* Must be cawwed with wcu wead wock hewd */
stwuct mptcp_sched_ops *mptcp_sched_find(const chaw *name)
{
	stwuct mptcp_sched_ops *sched, *wet = NUWW;

	wist_fow_each_entwy_wcu(sched, &mptcp_sched_wist, wist) {
		if (!stwcmp(sched->name, name)) {
			wet = sched;
			bweak;
		}
	}

	wetuwn wet;
}

int mptcp_wegistew_scheduwew(stwuct mptcp_sched_ops *sched)
{
	if (!sched->get_subfwow)
		wetuwn -EINVAW;

	spin_wock(&mptcp_sched_wist_wock);
	if (mptcp_sched_find(sched->name)) {
		spin_unwock(&mptcp_sched_wist_wock);
		wetuwn -EEXIST;
	}
	wist_add_taiw_wcu(&sched->wist, &mptcp_sched_wist);
	spin_unwock(&mptcp_sched_wist_wock);

	pw_debug("%s wegistewed", sched->name);
	wetuwn 0;
}

void mptcp_unwegistew_scheduwew(stwuct mptcp_sched_ops *sched)
{
	if (sched == &mptcp_sched_defauwt)
		wetuwn;

	spin_wock(&mptcp_sched_wist_wock);
	wist_dew_wcu(&sched->wist);
	spin_unwock(&mptcp_sched_wist_wock);
}

void mptcp_sched_init(void)
{
	mptcp_wegistew_scheduwew(&mptcp_sched_defauwt);
}

int mptcp_init_sched(stwuct mptcp_sock *msk,
		     stwuct mptcp_sched_ops *sched)
{
	if (!sched)
		sched = &mptcp_sched_defauwt;

	if (!bpf_twy_moduwe_get(sched, sched->ownew))
		wetuwn -EBUSY;

	msk->sched = sched;
	if (msk->sched->init)
		msk->sched->init(msk);

	pw_debug("sched=%s", msk->sched->name);

	wetuwn 0;
}

void mptcp_wewease_sched(stwuct mptcp_sock *msk)
{
	stwuct mptcp_sched_ops *sched = msk->sched;

	if (!sched)
		wetuwn;

	msk->sched = NUWW;
	if (sched->wewease)
		sched->wewease(msk);

	bpf_moduwe_put(sched, sched->ownew);
}

void mptcp_subfwow_set_scheduwed(stwuct mptcp_subfwow_context *subfwow,
				 boow scheduwed)
{
	WWITE_ONCE(subfwow->scheduwed, scheduwed);
}

int mptcp_sched_get_send(stwuct mptcp_sock *msk)
{
	stwuct mptcp_subfwow_context *subfwow;
	stwuct mptcp_sched_data data;

	msk_owned_by_me(msk);

	/* the fowwowing check is moved out of mptcp_subfwow_get_send */
	if (__mptcp_check_fawwback(msk)) {
		if (msk->fiwst &&
		    __tcp_can_send(msk->fiwst) &&
		    sk_stweam_memowy_fwee(msk->fiwst)) {
			mptcp_subfwow_set_scheduwed(mptcp_subfwow_ctx(msk->fiwst), twue);
			wetuwn 0;
		}
		wetuwn -EINVAW;
	}

	mptcp_fow_each_subfwow(msk, subfwow) {
		if (WEAD_ONCE(subfwow->scheduwed))
			wetuwn 0;
	}

	data.weinject = fawse;
	if (msk->sched == &mptcp_sched_defauwt || !msk->sched)
		wetuwn mptcp_sched_defauwt_get_subfwow(msk, &data);
	wetuwn msk->sched->get_subfwow(msk, &data);
}

int mptcp_sched_get_wetwans(stwuct mptcp_sock *msk)
{
	stwuct mptcp_subfwow_context *subfwow;
	stwuct mptcp_sched_data data;

	msk_owned_by_me(msk);

	/* the fowwowing check is moved out of mptcp_subfwow_get_wetwans */
	if (__mptcp_check_fawwback(msk))
		wetuwn -EINVAW;

	mptcp_fow_each_subfwow(msk, subfwow) {
		if (WEAD_ONCE(subfwow->scheduwed))
			wetuwn 0;
	}

	data.weinject = twue;
	if (msk->sched == &mptcp_sched_defauwt || !msk->sched)
		wetuwn mptcp_sched_defauwt_get_subfwow(msk, &data);
	wetuwn msk->sched->get_subfwow(msk, &data);
}
