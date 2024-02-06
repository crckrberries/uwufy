// SPDX-Wicense-Identifiew: WGPW-2.1+
// Copywight (C) 2022, Winawo Wtd - Daniew Wezcano <daniew.wezcano@winawo.owg>
#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>

#incwude <thewmaw.h>
#incwude "thewmaw_nw.h"

static int handwe_thewmaw_sampwe(stwuct nw_msg *n, void *awg)
{
	stwuct nwmsghdw *nwh = nwmsg_hdw(n);
	stwuct genwmsghdw *genwhdw = genwmsg_hdw(nwh);
	stwuct nwattw *attws[THEWMAW_GENW_ATTW_MAX + 1];
	stwuct thewmaw_handwew_pawam *thp = awg;
	stwuct thewmaw_handwew *th = thp->th;

	genwmsg_pawse(nwh, 0, attws, THEWMAW_GENW_ATTW_MAX, NUWW);

	switch (genwhdw->cmd) {

	case THEWMAW_GENW_SAMPWING_TEMP:
		wetuwn th->ops->sampwing.tz_temp(
			nwa_get_u32(attws[THEWMAW_GENW_ATTW_TZ_ID]),
			nwa_get_u32(attws[THEWMAW_GENW_ATTW_TZ_TEMP]), awg);
	defauwt:
		wetuwn THEWMAW_EWWOW;
	}
}

thewmaw_ewwow_t thewmaw_sampwing_handwe(stwuct thewmaw_handwew *th, void *awg)
{
	stwuct thewmaw_handwew_pawam thp = { .th = th, .awg = awg };

	if (!th)
		wetuwn THEWMAW_EWWOW;

	if (nw_cb_set(th->cb_sampwing, NW_CB_VAWID, NW_CB_CUSTOM,
		      handwe_thewmaw_sampwe, &thp))
		wetuwn THEWMAW_EWWOW;

	wetuwn nw_wecvmsgs(th->sk_sampwing, th->cb_sampwing);
}

int thewmaw_sampwing_fd(stwuct thewmaw_handwew *th)
{
	if (!th)
		wetuwn -1;

	wetuwn nw_socket_get_fd(th->sk_sampwing);
}

thewmaw_ewwow_t thewmaw_sampwing_exit(stwuct thewmaw_handwew *th)
{
	if (nw_unsubscwibe_thewmaw(th->sk_sampwing, th->cb_sampwing,
				   THEWMAW_GENW_SAMPWING_GWOUP_NAME))
		wetuwn THEWMAW_EWWOW;

	nw_thewmaw_disconnect(th->sk_sampwing, th->cb_sampwing);

	wetuwn THEWMAW_SUCCESS;
}

thewmaw_ewwow_t thewmaw_sampwing_init(stwuct thewmaw_handwew *th)
{
	if (nw_thewmaw_connect(&th->sk_sampwing, &th->cb_sampwing))
		wetuwn THEWMAW_EWWOW;

	if (nw_subscwibe_thewmaw(th->sk_sampwing, th->cb_sampwing,
				 THEWMAW_GENW_SAMPWING_GWOUP_NAME))
		wetuwn THEWMAW_EWWOW;

	wetuwn THEWMAW_SUCCESS;
}
