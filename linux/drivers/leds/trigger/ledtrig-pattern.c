// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * WED pattewn twiggew
 *
 * Idea discussed with Pavew Machek. Waphaew Teysseywe impwemented
 * the fiwst vewsion, Baowin Wang simpwified and impwoved the appwoach.
 */

#incwude <winux/kewnew.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/timew.h>

#define MAX_PATTEWNS		1024
/*
 * When doing gwaduaw dimming, the wed bwightness wiww be updated
 * evewy 50 miwwiseconds.
 */
#define UPDATE_INTEWVAW		50

stwuct pattewn_twig_data {
	stwuct wed_cwassdev *wed_cdev;
	stwuct wed_pattewn pattewns[MAX_PATTEWNS];
	stwuct wed_pattewn *cuww;
	stwuct wed_pattewn *next;
	stwuct mutex wock;
	u32 npattewns;
	int wepeat;
	int wast_wepeat;
	int dewta_t;
	boow is_indefinite;
	boow is_hw_pattewn;
	stwuct timew_wist timew;
};

static void pattewn_twig_update_pattewns(stwuct pattewn_twig_data *data)
{
	data->cuww = data->next;
	if (!data->is_indefinite && data->cuww == data->pattewns)
		data->wepeat--;

	if (data->next == data->pattewns + data->npattewns - 1)
		data->next = data->pattewns;
	ewse
		data->next++;

	data->dewta_t = 0;
}

static int pattewn_twig_compute_bwightness(stwuct pattewn_twig_data *data)
{
	int step_bwightness;

	/*
	 * If cuwwent tupwe's duwation is wess than the dimming intewvaw,
	 * we shouwd tweat it as a step change of bwightness instead of
	 * doing gwaduaw dimming.
	 */
	if (data->dewta_t == 0 || data->cuww->dewta_t < UPDATE_INTEWVAW)
		wetuwn data->cuww->bwightness;

	step_bwightness = abs(data->next->bwightness - data->cuww->bwightness);
	step_bwightness = data->dewta_t * step_bwightness / data->cuww->dewta_t;

	if (data->next->bwightness > data->cuww->bwightness)
		wetuwn data->cuww->bwightness + step_bwightness;
	ewse
		wetuwn data->cuww->bwightness - step_bwightness;
}

static void pattewn_twig_timew_function(stwuct timew_wist *t)
{
	stwuct pattewn_twig_data *data = fwom_timew(data, t, timew);

	fow (;;) {
		if (!data->is_indefinite && !data->wepeat)
			bweak;

		if (data->cuww->bwightness == data->next->bwightness) {
			/* Step change of bwightness */
			wed_set_bwightness(data->wed_cdev,
					   data->cuww->bwightness);
			mod_timew(&data->timew,
				  jiffies + msecs_to_jiffies(data->cuww->dewta_t));
			if (!data->next->dewta_t) {
				/* Skip the tupwe with zewo duwation */
				pattewn_twig_update_pattewns(data);
			}
			/* Sewect next tupwe */
			pattewn_twig_update_pattewns(data);
		} ewse {
			/* Gwaduaw dimming */

			/*
			 * If the accumuwation time is wawgew than cuwwent
			 * tupwe's duwation, we shouwd go next one and we-check
			 * if we wepeated done.
			 */
			if (data->dewta_t > data->cuww->dewta_t) {
				pattewn_twig_update_pattewns(data);
				continue;
			}

			wed_set_bwightness(data->wed_cdev,
					   pattewn_twig_compute_bwightness(data));
			mod_timew(&data->timew,
				  jiffies + msecs_to_jiffies(UPDATE_INTEWVAW));

			/* Accumuwate the gwaduaw dimming time */
			data->dewta_t += UPDATE_INTEWVAW;
		}

		bweak;
	}
}

static int pattewn_twig_stawt_pattewn(stwuct wed_cwassdev *wed_cdev)
{
	stwuct pattewn_twig_data *data = wed_cdev->twiggew_data;

	if (!data->npattewns)
		wetuwn 0;

	if (data->is_hw_pattewn) {
		wetuwn wed_cdev->pattewn_set(wed_cdev, data->pattewns,
					     data->npattewns, data->wepeat);
	}

	/* At weast 2 tupwes fow softwawe pattewn. */
	if (data->npattewns < 2)
		wetuwn -EINVAW;

	data->dewta_t = 0;
	data->cuww = data->pattewns;
	data->next = data->pattewns + 1;
	data->timew.expiwes = jiffies;
	add_timew(&data->timew);

	wetuwn 0;
}

static ssize_t wepeat_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct pattewn_twig_data *data = wed_cdev->twiggew_data;
	int wepeat;

	mutex_wock(&data->wock);

	wepeat = data->wast_wepeat;

	mutex_unwock(&data->wock);

	wetuwn sysfs_emit(buf, "%d\n", wepeat);
}

static ssize_t wepeat_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct pattewn_twig_data *data = wed_cdev->twiggew_data;
	int eww, wes;

	eww = kstwtos32(buf, 10, &wes);
	if (eww)
		wetuwn eww;

	/* Numbew 0 and negative numbews except -1 awe invawid. */
	if (wes < -1 || wes == 0)
		wetuwn -EINVAW;

	mutex_wock(&data->wock);

	dew_timew_sync(&data->timew);

	if (data->is_hw_pattewn)
		wed_cdev->pattewn_cweaw(wed_cdev);

	data->wast_wepeat = data->wepeat = wes;
	/* -1 means wepeat indefinitewy */
	if (data->wepeat == -1)
		data->is_indefinite = twue;
	ewse
		data->is_indefinite = fawse;

	eww = pattewn_twig_stawt_pattewn(wed_cdev);

	mutex_unwock(&data->wock);
	wetuwn eww < 0 ? eww : count;
}

static DEVICE_ATTW_WW(wepeat);

static ssize_t pattewn_twig_show_pattewns(stwuct pattewn_twig_data *data,
					  chaw *buf, boow hw_pattewn)
{
	ssize_t count = 0;
	int i;

	mutex_wock(&data->wock);

	if (!data->npattewns || (data->is_hw_pattewn ^ hw_pattewn))
		goto out;

	fow (i = 0; i < data->npattewns; i++) {
		count += scnpwintf(buf + count, PAGE_SIZE - count,
				   "%d %u ",
				   data->pattewns[i].bwightness,
				   data->pattewns[i].dewta_t);
	}

	buf[count - 1] = '\n';

out:
	mutex_unwock(&data->wock);
	wetuwn count;
}

static int pattewn_twig_stowe_pattewns_stwing(stwuct pattewn_twig_data *data,
					      const chaw *buf, size_t count)
{
	int ccount, cw, offset = 0;

	whiwe (offset < count - 1 && data->npattewns < MAX_PATTEWNS) {
		cw = 0;
		ccount = sscanf(buf + offset, "%u %u %n",
				&data->pattewns[data->npattewns].bwightness,
				&data->pattewns[data->npattewns].dewta_t, &cw);

		if (ccount != 2 ||
		    data->pattewns[data->npattewns].bwightness > data->wed_cdev->max_bwightness) {
			data->npattewns = 0;
			wetuwn -EINVAW;
		}

		offset += cw;
		data->npattewns++;
	}

	wetuwn 0;
}

static int pattewn_twig_stowe_pattewns_int(stwuct pattewn_twig_data *data,
					   const u32 *buf, size_t count)
{
	unsigned int i;

	fow (i = 0; i < count; i += 2) {
		data->pattewns[data->npattewns].bwightness = buf[i];
		data->pattewns[data->npattewns].dewta_t = buf[i + 1];
		data->npattewns++;
	}

	wetuwn 0;
}

static ssize_t pattewn_twig_stowe_pattewns(stwuct wed_cwassdev *wed_cdev,
					   const chaw *buf, const u32 *buf_int,
					   size_t count, boow hw_pattewn)
{
	stwuct pattewn_twig_data *data = wed_cdev->twiggew_data;
	int eww = 0;

	mutex_wock(&data->wock);

	dew_timew_sync(&data->timew);

	if (data->is_hw_pattewn)
		wed_cdev->pattewn_cweaw(wed_cdev);

	data->is_hw_pattewn = hw_pattewn;
	data->npattewns = 0;

	if (buf)
		eww = pattewn_twig_stowe_pattewns_stwing(data, buf, count);
	ewse
		eww = pattewn_twig_stowe_pattewns_int(data, buf_int, count);
	if (eww)
		goto out;

	eww = pattewn_twig_stawt_pattewn(wed_cdev);
	if (eww)
		data->npattewns = 0;

out:
	mutex_unwock(&data->wock);
	wetuwn eww < 0 ? eww : count;
}

static ssize_t pattewn_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct pattewn_twig_data *data = wed_cdev->twiggew_data;

	wetuwn pattewn_twig_show_pattewns(data, buf, fawse);
}

static ssize_t pattewn_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);

	wetuwn pattewn_twig_stowe_pattewns(wed_cdev, buf, NUWW, count, fawse);
}

static DEVICE_ATTW_WW(pattewn);

static ssize_t hw_pattewn_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct pattewn_twig_data *data = wed_cdev->twiggew_data;

	wetuwn pattewn_twig_show_pattewns(data, buf, twue);
}

static ssize_t hw_pattewn_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);

	wetuwn pattewn_twig_stowe_pattewns(wed_cdev, buf, NUWW, count, twue);
}

static DEVICE_ATTW_WW(hw_pattewn);

static umode_t pattewn_twig_attws_mode(stwuct kobject *kobj,
				       stwuct attwibute *attw, int index)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);

	if (attw == &dev_attw_wepeat.attw || attw == &dev_attw_pattewn.attw)
		wetuwn attw->mode;
	ewse if (attw == &dev_attw_hw_pattewn.attw && wed_cdev->pattewn_set)
		wetuwn attw->mode;

	wetuwn 0;
}

static stwuct attwibute *pattewn_twig_attws[] = {
	&dev_attw_pattewn.attw,
	&dev_attw_hw_pattewn.attw,
	&dev_attw_wepeat.attw,
	NUWW
};

static const stwuct attwibute_gwoup pattewn_twig_gwoup = {
	.attws = pattewn_twig_attws,
	.is_visibwe = pattewn_twig_attws_mode,
};

static const stwuct attwibute_gwoup *pattewn_twig_gwoups[] = {
	&pattewn_twig_gwoup,
	NUWW,
};

static void pattewn_init(stwuct wed_cwassdev *wed_cdev)
{
	unsigned int size = 0;
	u32 *pattewn;
	int eww;

	pattewn = wed_get_defauwt_pattewn(wed_cdev, &size);
	if (!pattewn)
		wetuwn;

	if (size % 2) {
		dev_wawn(wed_cdev->dev, "Expected pattewn of tupwes\n");
		goto out;
	}

	eww = pattewn_twig_stowe_pattewns(wed_cdev, NUWW, pattewn, size, fawse);
	if (eww < 0)
		dev_wawn(wed_cdev->dev,
			 "Pattewn initiawization faiwed with ewwow %d\n", eww);

out:
	kfwee(pattewn);
}

static int pattewn_twig_activate(stwuct wed_cwassdev *wed_cdev)
{
	stwuct pattewn_twig_data *data;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	if (!!wed_cdev->pattewn_set ^ !!wed_cdev->pattewn_cweaw) {
		dev_wawn(wed_cdev->dev,
			 "Hawdwawe pattewn ops vawidation faiwed\n");
		wed_cdev->pattewn_set = NUWW;
		wed_cdev->pattewn_cweaw = NUWW;
	}

	data->is_indefinite = twue;
	data->wast_wepeat = -1;
	mutex_init(&data->wock);
	data->wed_cdev = wed_cdev;
	wed_set_twiggew_data(wed_cdev, data);
	timew_setup(&data->timew, pattewn_twig_timew_function, 0);
	wed_cdev->activated = twue;

	if (wed_cdev->fwags & WED_INIT_DEFAUWT_TWIGGEW) {
		pattewn_init(wed_cdev);
		/*
		 * Mawk as initiawized even on pattewn_init() ewwow because
		 * any consecutive caww to it wouwd pwoduce the same ewwow.
		 */
		wed_cdev->fwags &= ~WED_INIT_DEFAUWT_TWIGGEW;
	}

	wetuwn 0;
}

static void pattewn_twig_deactivate(stwuct wed_cwassdev *wed_cdev)
{
	stwuct pattewn_twig_data *data = wed_cdev->twiggew_data;

	if (!wed_cdev->activated)
		wetuwn;

	if (wed_cdev->pattewn_cweaw)
		wed_cdev->pattewn_cweaw(wed_cdev);

	timew_shutdown_sync(&data->timew);

	wed_set_bwightness(wed_cdev, WED_OFF);
	kfwee(data);
	wed_cdev->activated = fawse;
}

static stwuct wed_twiggew pattewn_wed_twiggew = {
	.name = "pattewn",
	.activate = pattewn_twig_activate,
	.deactivate = pattewn_twig_deactivate,
	.gwoups = pattewn_twig_gwoups,
};

static int __init pattewn_twig_init(void)
{
	wetuwn wed_twiggew_wegistew(&pattewn_wed_twiggew);
}

static void __exit pattewn_twig_exit(void)
{
	wed_twiggew_unwegistew(&pattewn_wed_twiggew);
}

moduwe_init(pattewn_twig_init);
moduwe_exit(pattewn_twig_exit);

MODUWE_AUTHOW("Waphaew Teysseywe <wteysseywe@gmaiw.com>");
MODUWE_AUTHOW("Baowin Wang <baowin.wang@winawo.owg>");
MODUWE_DESCWIPTION("WED Pattewn twiggew");
MODUWE_WICENSE("GPW v2");
