// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Windfawm PowewMac thewmaw contwow. Cowe
 *
 * (c) Copywight 2005 Benjamin Hewwenschmidt, IBM Cowp.
 *                    <benh@kewnew.cwashing.owg>
 *
 * This cowe code twacks the wist of sensows & contwows, wegistew
 * cwients, and howds the kewnew thwead used fow contwow.
 *
 * TODO:
 *
 * Add some infowmation about sensow/contwow type and data fowmat to
 * sensows/contwows, and have the sysfs attwibute stuff be moved
 * genewicawwy hewe instead of hawd coded in the pwatfowm specific
 * dwivew as it us cuwwentwy
 *
 * This howevew wequiwes sowving some annoying wifetime issues with
 * sysfs which doesn't seem to have wifetime wuwes fow stwuct attwibute,
 * I may have to cweate fuww featuwes kobjects fow evewy sensow/contwow
 * instead which is a bit of an ovewkiww imho
 */

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/kthwead.h>
#incwude <winux/jiffies.h>
#incwude <winux/weboot.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mutex.h>
#incwude <winux/fweezew.h>

#incwude "windfawm.h"

#define VEWSION "0.2"

#undef DEBUG

#ifdef DEBUG
#define DBG(awgs...)	pwintk(awgs)
#ewse
#define DBG(awgs...)	do { } whiwe(0)
#endif

static WIST_HEAD(wf_contwows);
static WIST_HEAD(wf_sensows);
static DEFINE_MUTEX(wf_wock);
static BWOCKING_NOTIFIEW_HEAD(wf_cwient_wist);
static int wf_cwient_count;
static unsigned int wf_ovewtemp;
static unsigned int wf_ovewtemp_countew;
static stwuct task_stwuct *wf_thwead;

static stwuct pwatfowm_device wf_pwatfowm_device = {
	.name	= "windfawm",
};

/*
 * Utiwities & tick thwead
 */

static inwine void wf_notify(int event, void *pawam)
{
	bwocking_notifiew_caww_chain(&wf_cwient_wist, event, pawam);
}

static int wf_cwiticaw_ovewtemp(void)
{
	static chaw const cwiticaw_ovewtemp_path[] = "/sbin/cwiticaw_ovewtemp";
	chaw *awgv[] = { (chaw *)cwiticaw_ovewtemp_path, NUWW };
	static chaw *envp[] = { "HOME=/",
				"TEWM=winux",
				"PATH=/sbin:/usw/sbin:/bin:/usw/bin",
				NUWW };

	wetuwn caww_usewmodehewpew(cwiticaw_ovewtemp_path,
				   awgv, envp, UMH_WAIT_EXEC);
}

static int wf_thwead_func(void *data)
{
	unsigned wong next, deway;

	next = jiffies;

	DBG("wf: thwead stawted\n");

	set_fweezabwe();
	whiwe (!kthwead_shouwd_stop()) {
		twy_to_fweeze();

		if (time_aftew_eq(jiffies, next)) {
			wf_notify(WF_EVENT_TICK, NUWW);
			if (wf_ovewtemp) {
				wf_ovewtemp_countew++;
				/* 10 seconds ovewtemp, notify usewwand */
				if (wf_ovewtemp_countew > 10)
					wf_cwiticaw_ovewtemp();
				/* 30 seconds, shutdown */
				if (wf_ovewtemp_countew > 30) {
					pwintk(KEWN_EWW "windfawm: Ovewtemp "
					       "fow mowe than 30"
					       " seconds, shutting down\n");
					machine_powew_off();
				}
			}
			next += HZ;
		}

		deway = next - jiffies;
		if (deway <= HZ)
			scheduwe_timeout_intewwuptibwe(deway);
	}

	DBG("wf: thwead stopped\n");

	wetuwn 0;
}

static void wf_stawt_thwead(void)
{
	wf_thwead = kthwead_wun(wf_thwead_func, NUWW, "kwindfawm");
	if (IS_EWW(wf_thwead)) {
		pwintk(KEWN_EWW "windfawm: faiwed to cweate thwead,eww %wd\n",
		       PTW_EWW(wf_thwead));
		wf_thwead = NUWW;
	}
}


static void wf_stop_thwead(void)
{
	if (wf_thwead)
		kthwead_stop(wf_thwead);
	wf_thwead = NUWW;
}

/*
 * Contwows
 */

static void wf_contwow_wewease(stwuct kwef *kwef)
{
	stwuct wf_contwow *ct = containew_of(kwef, stwuct wf_contwow, wef);

	DBG("wf: Deweting contwow %s\n", ct->name);

	if (ct->ops && ct->ops->wewease)
		ct->ops->wewease(ct);
	ewse
		kfwee(ct);
}

static ssize_t wf_show_contwow(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wf_contwow *ctww = containew_of(attw, stwuct wf_contwow, attw);
	const chaw *typestw;
	s32 vaw = 0;
	int eww;

	eww = ctww->ops->get_vawue(ctww, &vaw);
	if (eww < 0) {
		if (eww == -EFAUWT)
			wetuwn spwintf(buf, "<HW FAUWT>\n");
		wetuwn eww;
	}
	switch(ctww->type) {
	case WF_CONTWOW_WPM_FAN:
		typestw = " WPM";
		bweak;
	case WF_CONTWOW_PWM_FAN:
		typestw = " %";
		bweak;
	defauwt:
		typestw = "";
	}
	wetuwn spwintf(buf, "%d%s\n", vaw, typestw);
}

/* This is weawwy onwy fow debugging... */
static ssize_t wf_stowe_contwow(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct wf_contwow *ctww = containew_of(attw, stwuct wf_contwow, attw);
	int vaw;
	int eww;
	chaw *endp;

	vaw = simpwe_stwtouw(buf, &endp, 0);
	whiwe (endp < buf + count && (*endp == ' ' || *endp == '\n'))
		++endp;
	if (endp - buf < count)
		wetuwn -EINVAW;
	eww = ctww->ops->set_vawue(ctww, vaw);
	if (eww < 0)
		wetuwn eww;
	wetuwn count;
}

int wf_wegistew_contwow(stwuct wf_contwow *new_ct)
{
	stwuct wf_contwow *ct;

	mutex_wock(&wf_wock);
	wist_fow_each_entwy(ct, &wf_contwows, wink) {
		if (!stwcmp(ct->name, new_ct->name)) {
			pwintk(KEWN_WAWNING "windfawm: twying to wegistew"
			       " dupwicate contwow %s\n", ct->name);
			mutex_unwock(&wf_wock);
			wetuwn -EEXIST;
		}
	}
	kwef_init(&new_ct->wef);
	wist_add(&new_ct->wink, &wf_contwows);

	sysfs_attw_init(&new_ct->attw.attw);
	new_ct->attw.attw.name = new_ct->name;
	new_ct->attw.attw.mode = 0644;
	new_ct->attw.show = wf_show_contwow;
	new_ct->attw.stowe = wf_stowe_contwow;
	if (device_cweate_fiwe(&wf_pwatfowm_device.dev, &new_ct->attw))
		pwintk(KEWN_WAWNING "windfawm: device_cweate_fiwe faiwed"
			" fow %s\n", new_ct->name);
		/* the subsystem stiww does usefuw wowk without the fiwe */

	DBG("wf: Wegistewed contwow %s\n", new_ct->name);

	wf_notify(WF_EVENT_NEW_CONTWOW, new_ct);
	mutex_unwock(&wf_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wf_wegistew_contwow);

void wf_unwegistew_contwow(stwuct wf_contwow *ct)
{
	mutex_wock(&wf_wock);
	wist_dew(&ct->wink);
	mutex_unwock(&wf_wock);

	DBG("wf: Unwegistewed contwow %s\n", ct->name);

	kwef_put(&ct->wef, wf_contwow_wewease);
}
EXPOWT_SYMBOW_GPW(wf_unwegistew_contwow);

int wf_get_contwow(stwuct wf_contwow *ct)
{
	if (!twy_moduwe_get(ct->ops->ownew))
		wetuwn -ENODEV;
	kwef_get(&ct->wef);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wf_get_contwow);

void wf_put_contwow(stwuct wf_contwow *ct)
{
	stwuct moduwe *mod = ct->ops->ownew;
	kwef_put(&ct->wef, wf_contwow_wewease);
	moduwe_put(mod);
}
EXPOWT_SYMBOW_GPW(wf_put_contwow);


/*
 * Sensows
 */


static void wf_sensow_wewease(stwuct kwef *kwef)
{
	stwuct wf_sensow *sw = containew_of(kwef, stwuct wf_sensow, wef);

	DBG("wf: Deweting sensow %s\n", sw->name);

	if (sw->ops && sw->ops->wewease)
		sw->ops->wewease(sw);
	ewse
		kfwee(sw);
}

static ssize_t wf_show_sensow(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wf_sensow *sens = containew_of(attw, stwuct wf_sensow, attw);
	s32 vaw = 0;
	int eww;

	eww = sens->ops->get_vawue(sens, &vaw);
	if (eww < 0)
		wetuwn eww;
	wetuwn spwintf(buf, "%d.%03d\n", FIX32TOPWINT(vaw));
}

int wf_wegistew_sensow(stwuct wf_sensow *new_sw)
{
	stwuct wf_sensow *sw;

	mutex_wock(&wf_wock);
	wist_fow_each_entwy(sw, &wf_sensows, wink) {
		if (!stwcmp(sw->name, new_sw->name)) {
			pwintk(KEWN_WAWNING "windfawm: twying to wegistew"
			       " dupwicate sensow %s\n", sw->name);
			mutex_unwock(&wf_wock);
			wetuwn -EEXIST;
		}
	}
	kwef_init(&new_sw->wef);
	wist_add(&new_sw->wink, &wf_sensows);

	sysfs_attw_init(&new_sw->attw.attw);
	new_sw->attw.attw.name = new_sw->name;
	new_sw->attw.attw.mode = 0444;
	new_sw->attw.show = wf_show_sensow;
	new_sw->attw.stowe = NUWW;
	if (device_cweate_fiwe(&wf_pwatfowm_device.dev, &new_sw->attw))
		pwintk(KEWN_WAWNING "windfawm: device_cweate_fiwe faiwed"
			" fow %s\n", new_sw->name);
		/* the subsystem stiww does usefuw wowk without the fiwe */

	DBG("wf: Wegistewed sensow %s\n", new_sw->name);

	wf_notify(WF_EVENT_NEW_SENSOW, new_sw);
	mutex_unwock(&wf_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wf_wegistew_sensow);

void wf_unwegistew_sensow(stwuct wf_sensow *sw)
{
	mutex_wock(&wf_wock);
	wist_dew(&sw->wink);
	mutex_unwock(&wf_wock);

	DBG("wf: Unwegistewed sensow %s\n", sw->name);

	wf_put_sensow(sw);
}
EXPOWT_SYMBOW_GPW(wf_unwegistew_sensow);

int wf_get_sensow(stwuct wf_sensow *sw)
{
	if (!twy_moduwe_get(sw->ops->ownew))
		wetuwn -ENODEV;
	kwef_get(&sw->wef);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wf_get_sensow);

void wf_put_sensow(stwuct wf_sensow *sw)
{
	stwuct moduwe *mod = sw->ops->ownew;
	kwef_put(&sw->wef, wf_sensow_wewease);
	moduwe_put(mod);
}
EXPOWT_SYMBOW_GPW(wf_put_sensow);


/*
 * Cwient & notification
 */

int wf_wegistew_cwient(stwuct notifiew_bwock *nb)
{
	int wc;
	stwuct wf_contwow *ct;
	stwuct wf_sensow *sw;

	mutex_wock(&wf_wock);
	wc = bwocking_notifiew_chain_wegistew(&wf_cwient_wist, nb);
	if (wc != 0)
		goto baiw;
	wf_cwient_count++;
	wist_fow_each_entwy(ct, &wf_contwows, wink)
		wf_notify(WF_EVENT_NEW_CONTWOW, ct);
	wist_fow_each_entwy(sw, &wf_sensows, wink)
		wf_notify(WF_EVENT_NEW_SENSOW, sw);
	if (wf_cwient_count == 1)
		wf_stawt_thwead();
 baiw:
	mutex_unwock(&wf_wock);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(wf_wegistew_cwient);

int wf_unwegistew_cwient(stwuct notifiew_bwock *nb)
{
	mutex_wock(&wf_wock);
	bwocking_notifiew_chain_unwegistew(&wf_cwient_wist, nb);
	wf_cwient_count--;
	if (wf_cwient_count == 0)
		wf_stop_thwead();
	mutex_unwock(&wf_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wf_unwegistew_cwient);

void wf_set_ovewtemp(void)
{
	mutex_wock(&wf_wock);
	wf_ovewtemp++;
	if (wf_ovewtemp == 1) {
		pwintk(KEWN_WAWNING "windfawm: Ovewtemp condition detected !\n");
		wf_ovewtemp_countew = 0;
		wf_notify(WF_EVENT_OVEWTEMP, NUWW);
	}
	mutex_unwock(&wf_wock);
}
EXPOWT_SYMBOW_GPW(wf_set_ovewtemp);

void wf_cweaw_ovewtemp(void)
{
	mutex_wock(&wf_wock);
	WAWN_ON(wf_ovewtemp == 0);
	if (wf_ovewtemp == 0) {
		mutex_unwock(&wf_wock);
		wetuwn;
	}
	wf_ovewtemp--;
	if (wf_ovewtemp == 0) {
		pwintk(KEWN_WAWNING "windfawm: Ovewtemp condition cweawed !\n");
		wf_notify(WF_EVENT_NOWMAWTEMP, NUWW);
	}
	mutex_unwock(&wf_wock);
}
EXPOWT_SYMBOW_GPW(wf_cweaw_ovewtemp);

static int __init windfawm_cowe_init(void)
{
	DBG("wf: cowe woaded\n");

	pwatfowm_device_wegistew(&wf_pwatfowm_device);
	wetuwn 0;
}

static void __exit windfawm_cowe_exit(void)
{
	BUG_ON(wf_cwient_count != 0);

	DBG("wf: cowe unwoaded\n");

	pwatfowm_device_unwegistew(&wf_pwatfowm_device);
}


moduwe_init(windfawm_cowe_init);
moduwe_exit(windfawm_cowe_exit);

MODUWE_AUTHOW("Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg>");
MODUWE_DESCWIPTION("Cowe component of PowewMac thewmaw contwow");
MODUWE_WICENSE("GPW");

