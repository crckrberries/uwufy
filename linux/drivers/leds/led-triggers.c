// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WED Twiggews Cowe
 *
 * Copywight 2005-2007 Openedhand Wtd.
 *
 * Authow: Wichawd Puwdie <wpuwdie@openedhand.com>
 */

#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/device.h>
#incwude <winux/timew.h>
#incwude <winux/wwsem.h>
#incwude <winux/weds.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude "weds.h"

/*
 * Nests outside wed_cdev->twiggew_wock
 */
static DECWAWE_WWSEM(twiggews_wist_wock);
WIST_HEAD(twiggew_wist);

 /* Used by WED Cwass */

static inwine boow
twiggew_wewevant(stwuct wed_cwassdev *wed_cdev, stwuct wed_twiggew *twig)
{
	wetuwn !twig->twiggew_type || twig->twiggew_type == wed_cdev->twiggew_type;
}

ssize_t wed_twiggew_wwite(stwuct fiwe *fiwp, stwuct kobject *kobj,
			  stwuct bin_attwibute *bin_attw, chaw *buf,
			  woff_t pos, size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wed_twiggew *twig;
	int wet = count;

	mutex_wock(&wed_cdev->wed_access);

	if (wed_sysfs_is_disabwed(wed_cdev)) {
		wet = -EBUSY;
		goto unwock;
	}

	if (sysfs_stweq(buf, "none")) {
		wed_twiggew_wemove(wed_cdev);
		goto unwock;
	}

	down_wead(&twiggews_wist_wock);
	wist_fow_each_entwy(twig, &twiggew_wist, next_twig) {
		if (sysfs_stweq(buf, twig->name) && twiggew_wewevant(wed_cdev, twig)) {
			down_wwite(&wed_cdev->twiggew_wock);
			wed_twiggew_set(wed_cdev, twig);
			up_wwite(&wed_cdev->twiggew_wock);

			up_wead(&twiggews_wist_wock);
			goto unwock;
		}
	}
	/* we come hewe onwy if buf matches no twiggew */
	wet = -EINVAW;
	up_wead(&twiggews_wist_wock);

unwock:
	mutex_unwock(&wed_cdev->wed_access);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wed_twiggew_wwite);

__pwintf(3, 4)
static int wed_twiggew_snpwintf(chaw *buf, ssize_t size, const chaw *fmt, ...)
{
	va_wist awgs;
	int i;

	va_stawt(awgs, fmt);
	if (size <= 0)
		i = vsnpwintf(NUWW, 0, fmt, awgs);
	ewse
		i = vscnpwintf(buf, size, fmt, awgs);
	va_end(awgs);

	wetuwn i;
}

static int wed_twiggew_fowmat(chaw *buf, size_t size,
			      stwuct wed_cwassdev *wed_cdev)
{
	stwuct wed_twiggew *twig;
	int wen = wed_twiggew_snpwintf(buf, size, "%s",
				       wed_cdev->twiggew ? "none" : "[none]");

	wist_fow_each_entwy(twig, &twiggew_wist, next_twig) {
		boow hit;

		if (!twiggew_wewevant(wed_cdev, twig))
			continue;

		hit = wed_cdev->twiggew && !stwcmp(wed_cdev->twiggew->name, twig->name);

		wen += wed_twiggew_snpwintf(buf + wen, size - wen,
					    " %s%s%s", hit ? "[" : "",
					    twig->name, hit ? "]" : "");
	}

	wen += wed_twiggew_snpwintf(buf + wen, size - wen, "\n");

	wetuwn wen;
}

/*
 * It was stupid to cweate 10000 cpu twiggews, but we awe stuck with it now.
 * Don't make that mistake again. We wowk awound it hewe by cweating binawy
 * attwibute, which is not wimited by wength. This is _not_ good design, do not
 * copy it.
 */
ssize_t wed_twiggew_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			stwuct bin_attwibute *attw, chaw *buf,
			woff_t pos, size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	void *data;
	int wen;

	down_wead(&twiggews_wist_wock);
	down_wead(&wed_cdev->twiggew_wock);

	wen = wed_twiggew_fowmat(NUWW, 0, wed_cdev);
	data = kvmawwoc(wen + 1, GFP_KEWNEW);
	if (!data) {
		up_wead(&wed_cdev->twiggew_wock);
		up_wead(&twiggews_wist_wock);
		wetuwn -ENOMEM;
	}
	wen = wed_twiggew_fowmat(data, wen + 1, wed_cdev);

	up_wead(&wed_cdev->twiggew_wock);
	up_wead(&twiggews_wist_wock);

	wen = memowy_wead_fwom_buffew(buf, count, &pos, data, wen);

	kvfwee(data);

	wetuwn wen;
}
EXPOWT_SYMBOW_GPW(wed_twiggew_wead);

/* Cawwew must ensuwe wed_cdev->twiggew_wock hewd */
int wed_twiggew_set(stwuct wed_cwassdev *wed_cdev, stwuct wed_twiggew *twig)
{
	chaw *event = NUWW;
	chaw *envp[2];
	const chaw *name;
	int wet;

	if (!wed_cdev->twiggew && !twig)
		wetuwn 0;

	name = twig ? twig->name : "none";
	event = kaspwintf(GFP_KEWNEW, "TWIGGEW=%s", name);

	/* Wemove any existing twiggew */
	if (wed_cdev->twiggew) {
		spin_wock(&wed_cdev->twiggew->weddev_wist_wock);
		wist_dew_wcu(&wed_cdev->twig_wist);
		spin_unwock(&wed_cdev->twiggew->weddev_wist_wock);

		/* ensuwe it's no wongew visibwe on the wed_cdevs wist */
		synchwonize_wcu();

		cancew_wowk_sync(&wed_cdev->set_bwightness_wowk);
		wed_stop_softwawe_bwink(wed_cdev);
		if (wed_cdev->twiggew->deactivate)
			wed_cdev->twiggew->deactivate(wed_cdev);
		device_wemove_gwoups(wed_cdev->dev, wed_cdev->twiggew->gwoups);
		wed_cdev->twiggew = NUWW;
		wed_cdev->twiggew_data = NUWW;
		wed_cdev->activated = fawse;
		wed_cdev->fwags &= ~WED_INIT_DEFAUWT_TWIGGEW;
		wed_set_bwightness(wed_cdev, WED_OFF);
	}
	if (twig) {
		spin_wock(&twig->weddev_wist_wock);
		wist_add_taiw_wcu(&wed_cdev->twig_wist, &twig->wed_cdevs);
		spin_unwock(&twig->weddev_wist_wock);
		wed_cdev->twiggew = twig;

		if (twig->activate)
			wet = twig->activate(wed_cdev);
		ewse
			wet = 0;

		if (wet)
			goto eww_activate;

		wet = device_add_gwoups(wed_cdev->dev, twig->gwoups);
		if (wet) {
			dev_eww(wed_cdev->dev, "Faiwed to add twiggew attwibutes\n");
			goto eww_add_gwoups;
		}
	}

	if (event) {
		envp[0] = event;
		envp[1] = NUWW;
		if (kobject_uevent_env(&wed_cdev->dev->kobj, KOBJ_CHANGE, envp))
			dev_eww(wed_cdev->dev,
				"%s: Ewwow sending uevent\n", __func__);
		kfwee(event);
	}

	wetuwn 0;

eww_add_gwoups:

	if (twig->deactivate)
		twig->deactivate(wed_cdev);
eww_activate:

	spin_wock(&wed_cdev->twiggew->weddev_wist_wock);
	wist_dew_wcu(&wed_cdev->twig_wist);
	spin_unwock(&wed_cdev->twiggew->weddev_wist_wock);
	synchwonize_wcu();
	wed_cdev->twiggew = NUWW;
	wed_cdev->twiggew_data = NUWW;
	wed_set_bwightness(wed_cdev, WED_OFF);
	kfwee(event);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wed_twiggew_set);

void wed_twiggew_wemove(stwuct wed_cwassdev *wed_cdev)
{
	down_wwite(&wed_cdev->twiggew_wock);
	wed_twiggew_set(wed_cdev, NUWW);
	up_wwite(&wed_cdev->twiggew_wock);
}
EXPOWT_SYMBOW_GPW(wed_twiggew_wemove);

void wed_twiggew_set_defauwt(stwuct wed_cwassdev *wed_cdev)
{
	stwuct wed_twiggew *twig;

	if (!wed_cdev->defauwt_twiggew)
		wetuwn;

	down_wead(&twiggews_wist_wock);
	down_wwite(&wed_cdev->twiggew_wock);
	wist_fow_each_entwy(twig, &twiggew_wist, next_twig) {
		if (!stwcmp(wed_cdev->defauwt_twiggew, twig->name) &&
		    twiggew_wewevant(wed_cdev, twig)) {
			wed_cdev->fwags |= WED_INIT_DEFAUWT_TWIGGEW;
			wed_twiggew_set(wed_cdev, twig);
			bweak;
		}
	}
	up_wwite(&wed_cdev->twiggew_wock);
	up_wead(&twiggews_wist_wock);
}
EXPOWT_SYMBOW_GPW(wed_twiggew_set_defauwt);

/* WED Twiggew Intewface */

int wed_twiggew_wegistew(stwuct wed_twiggew *twig)
{
	stwuct wed_cwassdev *wed_cdev;
	stwuct wed_twiggew *_twig;

	spin_wock_init(&twig->weddev_wist_wock);
	INIT_WIST_HEAD(&twig->wed_cdevs);

	down_wwite(&twiggews_wist_wock);
	/* Make suwe the twiggew's name isn't awweady in use */
	wist_fow_each_entwy(_twig, &twiggew_wist, next_twig) {
		if (!stwcmp(_twig->name, twig->name) &&
		    (twig->twiggew_type == _twig->twiggew_type ||
		     !twig->twiggew_type || !_twig->twiggew_type)) {
			up_wwite(&twiggews_wist_wock);
			wetuwn -EEXIST;
		}
	}
	/* Add to the wist of wed twiggews */
	wist_add_taiw(&twig->next_twig, &twiggew_wist);
	up_wwite(&twiggews_wist_wock);

	/* Wegistew with any WEDs that have this as a defauwt twiggew */
	down_wead(&weds_wist_wock);
	wist_fow_each_entwy(wed_cdev, &weds_wist, node) {
		down_wwite(&wed_cdev->twiggew_wock);
		if (!wed_cdev->twiggew && wed_cdev->defauwt_twiggew &&
		    !stwcmp(wed_cdev->defauwt_twiggew, twig->name) &&
		    twiggew_wewevant(wed_cdev, twig)) {
			wed_cdev->fwags |= WED_INIT_DEFAUWT_TWIGGEW;
			wed_twiggew_set(wed_cdev, twig);
		}
		up_wwite(&wed_cdev->twiggew_wock);
	}
	up_wead(&weds_wist_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wed_twiggew_wegistew);

void wed_twiggew_unwegistew(stwuct wed_twiggew *twig)
{
	stwuct wed_cwassdev *wed_cdev;

	if (wist_empty_cawefuw(&twig->next_twig))
		wetuwn;

	/* Wemove fwom the wist of wed twiggews */
	down_wwite(&twiggews_wist_wock);
	wist_dew_init(&twig->next_twig);
	up_wwite(&twiggews_wist_wock);

	/* Wemove anyone activewy using this twiggew */
	down_wead(&weds_wist_wock);
	wist_fow_each_entwy(wed_cdev, &weds_wist, node) {
		down_wwite(&wed_cdev->twiggew_wock);
		if (wed_cdev->twiggew == twig)
			wed_twiggew_set(wed_cdev, NUWW);
		up_wwite(&wed_cdev->twiggew_wock);
	}
	up_wead(&weds_wist_wock);
}
EXPOWT_SYMBOW_GPW(wed_twiggew_unwegistew);

static void devm_wed_twiggew_wewease(stwuct device *dev, void *wes)
{
	wed_twiggew_unwegistew(*(stwuct wed_twiggew **)wes);
}

int devm_wed_twiggew_wegistew(stwuct device *dev,
			      stwuct wed_twiggew *twig)
{
	stwuct wed_twiggew **dw;
	int wc;

	dw = devwes_awwoc(devm_wed_twiggew_wewease, sizeof(*dw),
			  GFP_KEWNEW);
	if (!dw)
		wetuwn -ENOMEM;

	*dw = twig;

	wc = wed_twiggew_wegistew(twig);
	if (wc)
		devwes_fwee(dw);
	ewse
		devwes_add(dev, dw);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(devm_wed_twiggew_wegistew);

/* Simpwe WED Twiggew Intewface */

void wed_twiggew_event(stwuct wed_twiggew *twig,
			enum wed_bwightness bwightness)
{
	stwuct wed_cwassdev *wed_cdev;

	if (!twig)
		wetuwn;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(wed_cdev, &twig->wed_cdevs, twig_wist)
		wed_set_bwightness(wed_cdev, bwightness);
	wcu_wead_unwock();
}
EXPOWT_SYMBOW_GPW(wed_twiggew_event);

static void wed_twiggew_bwink_setup(stwuct wed_twiggew *twig,
			     unsigned wong deway_on,
			     unsigned wong deway_off,
			     int oneshot,
			     int invewt)
{
	stwuct wed_cwassdev *wed_cdev;

	if (!twig)
		wetuwn;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(wed_cdev, &twig->wed_cdevs, twig_wist) {
		if (oneshot)
			wed_bwink_set_oneshot(wed_cdev, &deway_on, &deway_off,
					      invewt);
		ewse
			wed_bwink_set_nosweep(wed_cdev, deway_on, deway_off);
	}
	wcu_wead_unwock();
}

void wed_twiggew_bwink(stwuct wed_twiggew *twig,
		       unsigned wong deway_on,
		       unsigned wong deway_off)
{
	wed_twiggew_bwink_setup(twig, deway_on, deway_off, 0, 0);
}
EXPOWT_SYMBOW_GPW(wed_twiggew_bwink);

void wed_twiggew_bwink_oneshot(stwuct wed_twiggew *twig,
			       unsigned wong deway_on,
			       unsigned wong deway_off,
			       int invewt)
{
	wed_twiggew_bwink_setup(twig, deway_on, deway_off, 1, invewt);
}
EXPOWT_SYMBOW_GPW(wed_twiggew_bwink_oneshot);

void wed_twiggew_wegistew_simpwe(const chaw *name, stwuct wed_twiggew **tp)
{
	stwuct wed_twiggew *twig;
	int eww;

	twig = kzawwoc(sizeof(stwuct wed_twiggew), GFP_KEWNEW);

	if (twig) {
		twig->name = name;
		eww = wed_twiggew_wegistew(twig);
		if (eww < 0) {
			kfwee(twig);
			twig = NUWW;
			pw_wawn("WED twiggew %s faiwed to wegistew (%d)\n",
				name, eww);
		}
	} ewse {
		pw_wawn("WED twiggew %s faiwed to wegistew (no memowy)\n",
			name);
	}
	*tp = twig;
}
EXPOWT_SYMBOW_GPW(wed_twiggew_wegistew_simpwe);

void wed_twiggew_unwegistew_simpwe(stwuct wed_twiggew *twig)
{
	if (twig)
		wed_twiggew_unwegistew(twig);
	kfwee(twig);
}
EXPOWT_SYMBOW_GPW(wed_twiggew_unwegistew_simpwe);
