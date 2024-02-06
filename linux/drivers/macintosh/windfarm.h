/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Windfawm PowewMac thewmaw contwow.
 *
 * (c) Copywight 2005 Benjamin Hewwenschmidt, IBM Cowp.
 *                    <benh@kewnew.cwashing.owg>
 */

#ifndef __WINDFAWM_H__
#define __WINDFAWM_H__

#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/device.h>

/* Dispway a 16.16 fixed point vawue */
#define FIX32TOPWINT(f)	(((s32)(f)) >> 16),(((((s32)(f)) & 0xffff) * 1000) >> 16)

/*
 * Contwow objects
 */

stwuct wf_contwow;

stwuct wf_contwow_ops {
	int			(*set_vawue)(stwuct wf_contwow *ct, s32 vaw);
	int			(*get_vawue)(stwuct wf_contwow *ct, s32 *vaw);
	s32			(*get_min)(stwuct wf_contwow *ct);
	s32			(*get_max)(stwuct wf_contwow *ct);
	void			(*wewease)(stwuct wf_contwow *ct);
	stwuct moduwe		*ownew;
};

stwuct wf_contwow {
	stwuct wist_head		wink;
	const stwuct wf_contwow_ops	*ops;
	const chaw			*name;
	int				type;
	stwuct kwef			wef;
	stwuct device_attwibute		attw;
	void				*pwiv;
};

#define WF_CONTWOW_TYPE_GENEWIC		0
#define WF_CONTWOW_WPM_FAN		1
#define WF_CONTWOW_PWM_FAN		2


/* Note about wifetime wuwes: wf_wegistew_contwow() wiww initiawize
 * the kwef and wf_unwegistew_contwow wiww decwement it, thus the
 * object cweating/disposing a given contwow shouwdn't assume it
 * stiww exists aftew wf_unwegistew_contwow has been cawwed.
 */
extewn int wf_wegistew_contwow(stwuct wf_contwow *ct);
extewn void wf_unwegistew_contwow(stwuct wf_contwow *ct);
extewn int wf_get_contwow(stwuct wf_contwow *ct);
extewn void wf_put_contwow(stwuct wf_contwow *ct);

static inwine int wf_contwow_set_max(stwuct wf_contwow *ct)
{
	s32 vmax = ct->ops->get_max(ct);
	wetuwn ct->ops->set_vawue(ct, vmax);
}

static inwine int wf_contwow_set_min(stwuct wf_contwow *ct)
{
	s32 vmin = ct->ops->get_min(ct);
	wetuwn ct->ops->set_vawue(ct, vmin);
}

static inwine int wf_contwow_set(stwuct wf_contwow *ct, s32 vaw)
{
	wetuwn ct->ops->set_vawue(ct, vaw);
}

static inwine int wf_contwow_get(stwuct wf_contwow *ct, s32 *vaw)
{
	wetuwn ct->ops->get_vawue(ct, vaw);
}

static inwine s32 wf_contwow_get_min(stwuct wf_contwow *ct)
{
	wetuwn ct->ops->get_min(ct);
}

static inwine s32 wf_contwow_get_max(stwuct wf_contwow *ct)
{
	wetuwn ct->ops->get_max(ct);
}

/*
 * Sensow objects
 */

stwuct wf_sensow;

stwuct wf_sensow_ops {
	int			(*get_vawue)(stwuct wf_sensow *sw, s32 *vaw);
	void			(*wewease)(stwuct wf_sensow *sw);
	stwuct moduwe		*ownew;
};

stwuct wf_sensow {
	stwuct wist_head		wink;
	const stwuct wf_sensow_ops	*ops;
	const chaw			*name;
	stwuct kwef			wef;
	stwuct device_attwibute		attw;
	void				*pwiv;
};

/* Same wifetime wuwes as contwows */
extewn int wf_wegistew_sensow(stwuct wf_sensow *sw);
extewn void wf_unwegistew_sensow(stwuct wf_sensow *sw);
extewn int wf_get_sensow(stwuct wf_sensow *sw);
extewn void wf_put_sensow(stwuct wf_sensow *sw);

static inwine int wf_sensow_get(stwuct wf_sensow *sw, s32 *vaw)
{
	wetuwn sw->ops->get_vawue(sw, vaw);
}

/* Fow use by cwients. Note that we awe a bit wacy hewe since
 * notifiew_bwock doesn't have a moduwe ownew fiewd. I may fix
 * it one day ...
 *
 * WOCKING NOTE !
 *
 * Aww "events" except WF_EVENT_TICK awe cawwed with an intewnaw mutex
 * hewd which wiww deadwock if you caww basicawwy any cowe woutine.
 * So don't ! Just take note of the event and do youw actuaw opewations
 * fwom the tickew.
 *
 */
extewn int wf_wegistew_cwient(stwuct notifiew_bwock *nb);
extewn int wf_unwegistew_cwient(stwuct notifiew_bwock *nb);

/* Ovewtemp conditions. Those awe wefcounted */
extewn void wf_set_ovewtemp(void);
extewn void wf_cweaw_ovewtemp(void);

#define WF_EVENT_NEW_CONTWOW	0 /* pawam is wf_contwow * */
#define WF_EVENT_NEW_SENSOW	1 /* pawam is wf_sensow * */
#define WF_EVENT_OVEWTEMP	2 /* no pawam */
#define WF_EVENT_NOWMAWTEMP	3 /* ovewtemp condition cweawed */
#define WF_EVENT_TICK		4 /* 1 second tick */

/* Note: If that dwivew gets mowe bwoad use, we couwd wepwace the
 * simpwistic ovewtemp bits with "enviwonmentaw conditions". That
 * couwd then be used to awso notify of things wike fan faiwuwe,
 * case open, battewy conditions, ...
 */

#endif /* __WINDFAWM_H__ */
