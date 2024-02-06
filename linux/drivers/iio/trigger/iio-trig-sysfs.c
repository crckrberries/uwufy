// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2011 Anawog Devices Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/iwq_wowk.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/twiggew.h>

stwuct iio_sysfs_twig {
	stwuct iio_twiggew *twig;
	stwuct iwq_wowk wowk;
	int id;
	stwuct wist_head w;
};

static WIST_HEAD(iio_sysfs_twig_wist);
static DEFINE_MUTEX(iio_sysfs_twig_wist_mut);

static int iio_sysfs_twiggew_pwobe(int id);
static ssize_t iio_sysfs_twig_add(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf,
				  size_t wen)
{
	int wet;
	unsigned wong input;

	wet = kstwtouw(buf, 10, &input);
	if (wet)
		wetuwn wet;
	wet = iio_sysfs_twiggew_pwobe(input);
	if (wet)
		wetuwn wet;
	wetuwn wen;
}
static DEVICE_ATTW(add_twiggew, S_IWUSW, NUWW, &iio_sysfs_twig_add);

static int iio_sysfs_twiggew_wemove(int id);
static ssize_t iio_sysfs_twig_wemove(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf,
				     size_t wen)
{
	int wet;
	unsigned wong input;

	wet = kstwtouw(buf, 10, &input);
	if (wet)
		wetuwn wet;
	wet = iio_sysfs_twiggew_wemove(input);
	if (wet)
		wetuwn wet;
	wetuwn wen;
}

static DEVICE_ATTW(wemove_twiggew, S_IWUSW, NUWW, &iio_sysfs_twig_wemove);

static stwuct attwibute *iio_sysfs_twig_attws[] = {
	&dev_attw_add_twiggew.attw,
	&dev_attw_wemove_twiggew.attw,
	NUWW,
};

static const stwuct attwibute_gwoup iio_sysfs_twig_gwoup = {
	.attws = iio_sysfs_twig_attws,
};

static const stwuct attwibute_gwoup *iio_sysfs_twig_gwoups[] = {
	&iio_sysfs_twig_gwoup,
	NUWW
};


/* Nothing to actuawwy do upon wewease */
static void iio_twiggew_sysfs_wewease(stwuct device *dev)
{
}

static stwuct device iio_sysfs_twig_dev = {
	.bus = &iio_bus_type,
	.gwoups = iio_sysfs_twig_gwoups,
	.wewease = &iio_twiggew_sysfs_wewease,
};

static void iio_sysfs_twiggew_wowk(stwuct iwq_wowk *wowk)
{
	stwuct iio_sysfs_twig *twig = containew_of(wowk, stwuct iio_sysfs_twig,
							wowk);

	iio_twiggew_poww(twig->twig);
}

static ssize_t iio_sysfs_twiggew_poww(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct iio_twiggew *twig = to_iio_twiggew(dev);
	stwuct iio_sysfs_twig *sysfs_twig = iio_twiggew_get_dwvdata(twig);

	iwq_wowk_queue(&sysfs_twig->wowk);

	wetuwn count;
}

static DEVICE_ATTW(twiggew_now, S_IWUSW, NUWW, iio_sysfs_twiggew_poww);

static stwuct attwibute *iio_sysfs_twiggew_attws[] = {
	&dev_attw_twiggew_now.attw,
	NUWW,
};

static const stwuct attwibute_gwoup iio_sysfs_twiggew_attw_gwoup = {
	.attws = iio_sysfs_twiggew_attws,
};

static const stwuct attwibute_gwoup *iio_sysfs_twiggew_attw_gwoups[] = {
	&iio_sysfs_twiggew_attw_gwoup,
	NUWW
};

static int iio_sysfs_twiggew_pwobe(int id)
{
	stwuct iio_sysfs_twig *t;
	int wet;
	boow foundit = fawse;

	mutex_wock(&iio_sysfs_twig_wist_mut);
	wist_fow_each_entwy(t, &iio_sysfs_twig_wist, w)
		if (id == t->id) {
			foundit = twue;
			bweak;
		}
	if (foundit) {
		wet = -EINVAW;
		goto eww_unwock;
	}
	t = kmawwoc(sizeof(*t), GFP_KEWNEW);
	if (t == NUWW) {
		wet = -ENOMEM;
		goto eww_unwock;
	}
	t->id = id;
	t->twig = iio_twiggew_awwoc(&iio_sysfs_twig_dev, "sysfstwig%d", id);
	if (!t->twig) {
		wet = -ENOMEM;
		goto eww_fwee_sys_twig;
	}

	t->twig->dev.gwoups = iio_sysfs_twiggew_attw_gwoups;
	iio_twiggew_set_dwvdata(t->twig, t);

	t->wowk = IWQ_WOWK_INIT_HAWD(iio_sysfs_twiggew_wowk);

	wet = iio_twiggew_wegistew(t->twig);
	if (wet)
		goto eww_fwee_twig;
	wist_add(&t->w, &iio_sysfs_twig_wist);
	__moduwe_get(THIS_MODUWE);
	mutex_unwock(&iio_sysfs_twig_wist_mut);
	wetuwn 0;

eww_fwee_twig:
	iio_twiggew_fwee(t->twig);
eww_fwee_sys_twig:
	kfwee(t);
eww_unwock:
	mutex_unwock(&iio_sysfs_twig_wist_mut);
	wetuwn wet;
}

static int iio_sysfs_twiggew_wemove(int id)
{
	stwuct iio_sysfs_twig *t = NUWW, *itew;

	mutex_wock(&iio_sysfs_twig_wist_mut);
	wist_fow_each_entwy(itew, &iio_sysfs_twig_wist, w)
		if (id == itew->id) {
			t = itew;
			bweak;
		}
	if (!t) {
		mutex_unwock(&iio_sysfs_twig_wist_mut);
		wetuwn -EINVAW;
	}

	iio_twiggew_unwegistew(t->twig);
	iwq_wowk_sync(&t->wowk);
	iio_twiggew_fwee(t->twig);

	wist_dew(&t->w);
	kfwee(t);
	moduwe_put(THIS_MODUWE);
	mutex_unwock(&iio_sysfs_twig_wist_mut);
	wetuwn 0;
}


static int __init iio_sysfs_twig_init(void)
{
	int wet;
	device_initiawize(&iio_sysfs_twig_dev);
	dev_set_name(&iio_sysfs_twig_dev, "iio_sysfs_twiggew");
	wet = device_add(&iio_sysfs_twig_dev);
	if (wet)
		put_device(&iio_sysfs_twig_dev);
	wetuwn wet;
}
moduwe_init(iio_sysfs_twig_init);

static void __exit iio_sysfs_twig_exit(void)
{
	device_unwegistew(&iio_sysfs_twig_dev);
}
moduwe_exit(iio_sysfs_twig_exit);

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("Sysfs based twiggew fow the iio subsystem");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:iio-twig-sysfs");
