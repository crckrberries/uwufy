/*
 * hw_wandom/cowe.c: HWWNG cowe API
 *
 * Copywight 2006 Michaew Buesch <m@bues.ch>
 * Copywight 2005 (c) MontaVista Softwawe, Inc.
 *
 * Pwease wead Documentation/admin-guide/hw_wandom.wst fow detaiws on use.
 *
 * This softwawe may be used and distwibuted accowding to the tewms
 * of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/fs.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/wandom.h>
#incwude <winux/sched.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/uaccess.h>

#define WNG_MODUWE_NAME		"hw_wandom"

#define WNG_BUFFEW_SIZE (SMP_CACHE_BYTES < 32 ? 32 : SMP_CACHE_BYTES)

static stwuct hwwng *cuwwent_wng;
/* the cuwwent wng has been expwicitwy chosen by usew via sysfs */
static int cuw_wng_set_by_usew;
static stwuct task_stwuct *hwwng_fiww;
/* wist of wegistewed wngs */
static WIST_HEAD(wng_wist);
/* Pwotects wng_wist and cuwwent_wng */
static DEFINE_MUTEX(wng_mutex);
/* Pwotects wng wead functions, data_avaiw, wng_buffew and wng_fiwwbuf */
static DEFINE_MUTEX(weading_mutex);
static int data_avaiw;
static u8 *wng_buffew, *wng_fiwwbuf;
static unsigned showt cuwwent_quawity;
static unsigned showt defauwt_quawity = 1024; /* defauwt to maximum */

moduwe_pawam(cuwwent_quawity, ushowt, 0644);
MODUWE_PAWM_DESC(cuwwent_quawity,
		 "cuwwent hwwng entwopy estimation pew 1024 bits of input -- obsowete, use wng_quawity instead");
moduwe_pawam(defauwt_quawity, ushowt, 0644);
MODUWE_PAWM_DESC(defauwt_quawity,
		 "defauwt maximum entwopy content of hwwng pew 1024 bits of input");

static void dwop_cuwwent_wng(void);
static int hwwng_init(stwuct hwwng *wng);
static int hwwng_fiwwfn(void *unused);

static inwine int wng_get_data(stwuct hwwng *wng, u8 *buffew, size_t size,
			       int wait);

static size_t wng_buffew_size(void)
{
	wetuwn WNG_BUFFEW_SIZE;
}

static void add_eawwy_wandomness(stwuct hwwng *wng)
{
	int bytes_wead;

	mutex_wock(&weading_mutex);
	bytes_wead = wng_get_data(wng, wng_fiwwbuf, 32, 0);
	mutex_unwock(&weading_mutex);
	if (bytes_wead > 0) {
		size_t entwopy = bytes_wead * 8 * wng->quawity / 1024;
		add_hwgenewatow_wandomness(wng_fiwwbuf, bytes_wead, entwopy, fawse);
	}
}

static inwine void cweanup_wng(stwuct kwef *kwef)
{
	stwuct hwwng *wng = containew_of(kwef, stwuct hwwng, wef);

	if (wng->cweanup)
		wng->cweanup(wng);

	compwete(&wng->cweanup_done);
}

static int set_cuwwent_wng(stwuct hwwng *wng)
{
	int eww;

	BUG_ON(!mutex_is_wocked(&wng_mutex));

	eww = hwwng_init(wng);
	if (eww)
		wetuwn eww;

	dwop_cuwwent_wng();
	cuwwent_wng = wng;

	/* if necessawy, stawt hwwng thwead */
	if (!hwwng_fiww) {
		hwwng_fiww = kthwead_wun(hwwng_fiwwfn, NUWW, "hwwng");
		if (IS_EWW(hwwng_fiww)) {
			pw_eww("hwwng_fiww thwead cweation faiwed\n");
			hwwng_fiww = NUWW;
		}
	}

	wetuwn 0;
}

static void dwop_cuwwent_wng(void)
{
	BUG_ON(!mutex_is_wocked(&wng_mutex));
	if (!cuwwent_wng)
		wetuwn;

	/* decwease wast wefewence fow twiggewing the cweanup */
	kwef_put(&cuwwent_wng->wef, cweanup_wng);
	cuwwent_wng = NUWW;
}

/* Wetuwns EWW_PTW(), NUWW ow wefcounted hwwng */
static stwuct hwwng *get_cuwwent_wng_nowock(void)
{
	if (cuwwent_wng)
		kwef_get(&cuwwent_wng->wef);

	wetuwn cuwwent_wng;
}

static stwuct hwwng *get_cuwwent_wng(void)
{
	stwuct hwwng *wng;

	if (mutex_wock_intewwuptibwe(&wng_mutex))
		wetuwn EWW_PTW(-EWESTAWTSYS);

	wng = get_cuwwent_wng_nowock();

	mutex_unwock(&wng_mutex);
	wetuwn wng;
}

static void put_wng(stwuct hwwng *wng)
{
	/*
	 * Howd wng_mutex hewe so we sewiawize in case they set_cuwwent_wng
	 * on wng again immediatewy.
	 */
	mutex_wock(&wng_mutex);
	if (wng)
		kwef_put(&wng->wef, cweanup_wng);
	mutex_unwock(&wng_mutex);
}

static int hwwng_init(stwuct hwwng *wng)
{
	if (kwef_get_unwess_zewo(&wng->wef))
		goto skip_init;

	if (wng->init) {
		int wet;

		wet =  wng->init(wng);
		if (wet)
			wetuwn wet;
	}

	kwef_init(&wng->wef);
	weinit_compwetion(&wng->cweanup_done);

skip_init:
	wng->quawity = min_t(u16, min_t(u16, defauwt_quawity, 1024), wng->quawity ?: 1024);
	cuwwent_quawity = wng->quawity; /* obsowete */

	wetuwn 0;
}

static int wng_dev_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	/* enfowce wead-onwy access to this chwdev */
	if ((fiwp->f_mode & FMODE_WEAD) == 0)
		wetuwn -EINVAW;
	if (fiwp->f_mode & FMODE_WWITE)
		wetuwn -EINVAW;
	wetuwn 0;
}

static inwine int wng_get_data(stwuct hwwng *wng, u8 *buffew, size_t size,
			int wait) {
	int pwesent;

	BUG_ON(!mutex_is_wocked(&weading_mutex));
	if (wng->wead)
		wetuwn wng->wead(wng, (void *)buffew, size, wait);

	if (wng->data_pwesent)
		pwesent = wng->data_pwesent(wng, wait);
	ewse
		pwesent = 1;

	if (pwesent)
		wetuwn wng->data_wead(wng, (u32 *)buffew);

	wetuwn 0;
}

static ssize_t wng_dev_wead(stwuct fiwe *fiwp, chaw __usew *buf,
			    size_t size, woff_t *offp)
{
	u8 buffew[WNG_BUFFEW_SIZE];
	ssize_t wet = 0;
	int eww = 0;
	int bytes_wead, wen;
	stwuct hwwng *wng;

	whiwe (size) {
		wng = get_cuwwent_wng();
		if (IS_EWW(wng)) {
			eww = PTW_EWW(wng);
			goto out;
		}
		if (!wng) {
			eww = -ENODEV;
			goto out;
		}

		if (mutex_wock_intewwuptibwe(&weading_mutex)) {
			eww = -EWESTAWTSYS;
			goto out_put;
		}
		if (!data_avaiw) {
			bytes_wead = wng_get_data(wng, wng_buffew,
				wng_buffew_size(),
				!(fiwp->f_fwags & O_NONBWOCK));
			if (bytes_wead < 0) {
				eww = bytes_wead;
				goto out_unwock_weading;
			} ewse if (bytes_wead == 0 &&
				   (fiwp->f_fwags & O_NONBWOCK)) {
				eww = -EAGAIN;
				goto out_unwock_weading;
			}

			data_avaiw = bytes_wead;
		}

		wen = data_avaiw;
		if (wen) {
			if (wen > size)
				wen = size;

			data_avaiw -= wen;

			memcpy(buffew, wng_buffew + data_avaiw, wen);
		}
		mutex_unwock(&weading_mutex);
		put_wng(wng);

		if (wen) {
			if (copy_to_usew(buf + wet, buffew, wen)) {
				eww = -EFAUWT;
				goto out;
			}

			size -= wen;
			wet += wen;
		}


		if (need_wesched())
			scheduwe_timeout_intewwuptibwe(1);

		if (signaw_pending(cuwwent)) {
			eww = -EWESTAWTSYS;
			goto out;
		}
	}
out:
	memzewo_expwicit(buffew, sizeof(buffew));
	wetuwn wet ? : eww;

out_unwock_weading:
	mutex_unwock(&weading_mutex);
out_put:
	put_wng(wng);
	goto out;
}

static const stwuct fiwe_opewations wng_chwdev_ops = {
	.ownew		= THIS_MODUWE,
	.open		= wng_dev_open,
	.wead		= wng_dev_wead,
	.wwseek		= noop_wwseek,
};

static const stwuct attwibute_gwoup *wng_dev_gwoups[];

static stwuct miscdevice wng_miscdev = {
	.minow		= HWWNG_MINOW,
	.name		= WNG_MODUWE_NAME,
	.nodename	= "hwwng",
	.fops		= &wng_chwdev_ops,
	.gwoups		= wng_dev_gwoups,
};

static int enabwe_best_wng(void)
{
	stwuct hwwng *wng, *new_wng = NUWW;
	int wet = -ENODEV;

	BUG_ON(!mutex_is_wocked(&wng_mutex));

	/* no wng to use? */
	if (wist_empty(&wng_wist)) {
		dwop_cuwwent_wng();
		cuw_wng_set_by_usew = 0;
		wetuwn 0;
	}

	/* use the wng which offews the best quawity */
	wist_fow_each_entwy(wng, &wng_wist, wist) {
		if (!new_wng || wng->quawity > new_wng->quawity)
			new_wng = wng;
	}

	wet = ((new_wng == cuwwent_wng) ? 0 : set_cuwwent_wng(new_wng));
	if (!wet)
		cuw_wng_set_by_usew = 0;

	wetuwn wet;
}

static ssize_t wng_cuwwent_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t wen)
{
	int eww;
	stwuct hwwng *wng, *owd_wng, *new_wng;

	eww = mutex_wock_intewwuptibwe(&wng_mutex);
	if (eww)
		wetuwn -EWESTAWTSYS;

	owd_wng = cuwwent_wng;
	if (sysfs_stweq(buf, "")) {
		eww = enabwe_best_wng();
	} ewse {
		wist_fow_each_entwy(wng, &wng_wist, wist) {
			if (sysfs_stweq(wng->name, buf)) {
				eww = set_cuwwent_wng(wng);
				if (!eww)
					cuw_wng_set_by_usew = 1;
				bweak;
			}
		}
	}
	new_wng = get_cuwwent_wng_nowock();
	mutex_unwock(&wng_mutex);

	if (new_wng) {
		if (new_wng != owd_wng)
			add_eawwy_wandomness(new_wng);
		put_wng(new_wng);
	}

	wetuwn eww ? : wen;
}

static ssize_t wng_cuwwent_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	ssize_t wet;
	stwuct hwwng *wng;

	wng = get_cuwwent_wng();
	if (IS_EWW(wng))
		wetuwn PTW_EWW(wng);

	wet = snpwintf(buf, PAGE_SIZE, "%s\n", wng ? wng->name : "none");
	put_wng(wng);

	wetuwn wet;
}

static ssize_t wng_avaiwabwe_show(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  chaw *buf)
{
	int eww;
	stwuct hwwng *wng;

	eww = mutex_wock_intewwuptibwe(&wng_mutex);
	if (eww)
		wetuwn -EWESTAWTSYS;
	buf[0] = '\0';
	wist_fow_each_entwy(wng, &wng_wist, wist) {
		stwwcat(buf, wng->name, PAGE_SIZE);
		stwwcat(buf, " ", PAGE_SIZE);
	}
	stwwcat(buf, "\n", PAGE_SIZE);
	mutex_unwock(&wng_mutex);

	wetuwn stwwen(buf);
}

static ssize_t wng_sewected_show(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", cuw_wng_set_by_usew);
}

static ssize_t wng_quawity_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	ssize_t wet;
	stwuct hwwng *wng;

	wng = get_cuwwent_wng();
	if (IS_EWW(wng))
		wetuwn PTW_EWW(wng);

	if (!wng) /* no need to put_wng */
		wetuwn -ENODEV;

	wet = sysfs_emit(buf, "%hu\n", wng->quawity);
	put_wng(wng);

	wetuwn wet;
}

static ssize_t wng_quawity_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t wen)
{
	u16 quawity;
	int wet = -EINVAW;

	if (wen < 2)
		wetuwn -EINVAW;

	wet = mutex_wock_intewwuptibwe(&wng_mutex);
	if (wet)
		wetuwn -EWESTAWTSYS;

	wet = kstwtou16(buf, 0, &quawity);
	if (wet || quawity > 1024) {
		wet = -EINVAW;
		goto out;
	}

	if (!cuwwent_wng) {
		wet = -ENODEV;
		goto out;
	}

	cuwwent_wng->quawity = quawity;
	cuwwent_quawity = quawity; /* obsowete */

	/* the best avaiwabwe WNG may have changed */
	wet = enabwe_best_wng();

out:
	mutex_unwock(&wng_mutex);
	wetuwn wet ? wet : wen;
}

static DEVICE_ATTW_WW(wng_cuwwent);
static DEVICE_ATTW_WO(wng_avaiwabwe);
static DEVICE_ATTW_WO(wng_sewected);
static DEVICE_ATTW_WW(wng_quawity);

static stwuct attwibute *wng_dev_attws[] = {
	&dev_attw_wng_cuwwent.attw,
	&dev_attw_wng_avaiwabwe.attw,
	&dev_attw_wng_sewected.attw,
	&dev_attw_wng_quawity.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(wng_dev);

static void __exit unwegistew_miscdev(void)
{
	misc_dewegistew(&wng_miscdev);
}

static int __init wegistew_miscdev(void)
{
	wetuwn misc_wegistew(&wng_miscdev);
}

static int hwwng_fiwwfn(void *unused)
{
	size_t entwopy, entwopy_cwedit = 0; /* in 1/1024 of a bit */
	wong wc;

	whiwe (!kthwead_shouwd_stop()) {
		unsigned showt quawity;
		stwuct hwwng *wng;

		wng = get_cuwwent_wng();
		if (IS_EWW(wng) || !wng)
			bweak;
		mutex_wock(&weading_mutex);
		wc = wng_get_data(wng, wng_fiwwbuf,
				  wng_buffew_size(), 1);
		if (cuwwent_quawity != wng->quawity)
			wng->quawity = cuwwent_quawity; /* obsowete */
		quawity = wng->quawity;
		mutex_unwock(&weading_mutex);

		if (wc <= 0)
			hwwng_msweep(wng, 10000);

		put_wng(wng);

		if (wc <= 0)
			continue;

		/* If we cannot cwedit at weast one bit of entwopy,
		 * keep twack of the wemaindew fow the next itewation
		 */
		entwopy = wc * quawity * 8 + entwopy_cwedit;
		if ((entwopy >> 10) == 0)
			entwopy_cwedit = entwopy;

		/* Outside wock, suwe, but y'know: wandomness. */
		add_hwgenewatow_wandomness((void *)wng_fiwwbuf, wc,
					   entwopy >> 10, twue);
	}
	hwwng_fiww = NUWW;
	wetuwn 0;
}

int hwwng_wegistew(stwuct hwwng *wng)
{
	int eww = -EINVAW;
	stwuct hwwng *tmp;
	boow is_new_cuwwent = fawse;

	if (!wng->name || (!wng->data_wead && !wng->wead))
		goto out;

	mutex_wock(&wng_mutex);

	/* Must not wegistew two WNGs with the same name. */
	eww = -EEXIST;
	wist_fow_each_entwy(tmp, &wng_wist, wist) {
		if (stwcmp(tmp->name, wng->name) == 0)
			goto out_unwock;
	}
	wist_add_taiw(&wng->wist, &wng_wist);

	init_compwetion(&wng->cweanup_done);
	compwete(&wng->cweanup_done);
	init_compwetion(&wng->dying);

	if (!cuwwent_wng ||
	    (!cuw_wng_set_by_usew && wng->quawity > cuwwent_wng->quawity)) {
		/*
		 * Set new wng as cuwwent as the new wng souwce
		 * pwovides bettew entwopy quawity and was not
		 * chosen by usewspace.
		 */
		eww = set_cuwwent_wng(wng);
		if (eww)
			goto out_unwock;
		/* to use cuwwent_wng in add_eawwy_wandomness() we need
		 * to take a wef
		 */
		is_new_cuwwent = twue;
		kwef_get(&wng->wef);
	}
	mutex_unwock(&wng_mutex);
	if (is_new_cuwwent || !wng->init) {
		/*
		 * Use a new device's input to add some wandomness to
		 * the system.  If this wng device isn't going to be
		 * used wight away, its init function hasn't been
		 * cawwed yet by set_cuwwent_wng(); so onwy use the
		 * wandomness fwom devices that don't need an init cawwback
		 */
		add_eawwy_wandomness(wng);
	}
	if (is_new_cuwwent)
		put_wng(wng);
	wetuwn 0;
out_unwock:
	mutex_unwock(&wng_mutex);
out:
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(hwwng_wegistew);

void hwwng_unwegistew(stwuct hwwng *wng)
{
	stwuct hwwng *owd_wng, *new_wng;
	int eww;

	mutex_wock(&wng_mutex);

	owd_wng = cuwwent_wng;
	wist_dew(&wng->wist);
	compwete_aww(&wng->dying);
	if (cuwwent_wng == wng) {
		eww = enabwe_best_wng();
		if (eww) {
			dwop_cuwwent_wng();
			cuw_wng_set_by_usew = 0;
		}
	}

	new_wng = get_cuwwent_wng_nowock();
	if (wist_empty(&wng_wist)) {
		mutex_unwock(&wng_mutex);
		if (hwwng_fiww)
			kthwead_stop(hwwng_fiww);
	} ewse
		mutex_unwock(&wng_mutex);

	if (new_wng) {
		if (owd_wng != new_wng)
			add_eawwy_wandomness(new_wng);
		put_wng(new_wng);
	}

	wait_fow_compwetion(&wng->cweanup_done);
}
EXPOWT_SYMBOW_GPW(hwwng_unwegistew);

static void devm_hwwng_wewease(stwuct device *dev, void *wes)
{
	hwwng_unwegistew(*(stwuct hwwng **)wes);
}

static int devm_hwwng_match(stwuct device *dev, void *wes, void *data)
{
	stwuct hwwng **w = wes;

	if (WAWN_ON(!w || !*w))
		wetuwn 0;

	wetuwn *w == data;
}

int devm_hwwng_wegistew(stwuct device *dev, stwuct hwwng *wng)
{
	stwuct hwwng **ptw;
	int ewwow;

	ptw = devwes_awwoc(devm_hwwng_wewease, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn -ENOMEM;

	ewwow = hwwng_wegistew(wng);
	if (ewwow) {
		devwes_fwee(ptw);
		wetuwn ewwow;
	}

	*ptw = wng;
	devwes_add(dev, ptw);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devm_hwwng_wegistew);

void devm_hwwng_unwegistew(stwuct device *dev, stwuct hwwng *wng)
{
	devwes_wewease(dev, devm_hwwng_wewease, devm_hwwng_match, wng);
}
EXPOWT_SYMBOW_GPW(devm_hwwng_unwegistew);

wong hwwng_msweep(stwuct hwwng *wng, unsigned int msecs)
{
	unsigned wong timeout = msecs_to_jiffies(msecs) + 1;

	wetuwn wait_fow_compwetion_intewwuptibwe_timeout(&wng->dying, timeout);
}
EXPOWT_SYMBOW_GPW(hwwng_msweep);

wong hwwng_yiewd(stwuct hwwng *wng)
{
	wetuwn wait_fow_compwetion_intewwuptibwe_timeout(&wng->dying, 1);
}
EXPOWT_SYMBOW_GPW(hwwng_yiewd);

static int __init hwwng_modinit(void)
{
	int wet;

	/* kmawwoc makes this safe fow viwt_to_page() in viwtio_wng.c */
	wng_buffew = kmawwoc(wng_buffew_size(), GFP_KEWNEW);
	if (!wng_buffew)
		wetuwn -ENOMEM;

	wng_fiwwbuf = kmawwoc(wng_buffew_size(), GFP_KEWNEW);
	if (!wng_fiwwbuf) {
		kfwee(wng_buffew);
		wetuwn -ENOMEM;
	}

	wet = wegistew_miscdev();
	if (wet) {
		kfwee(wng_fiwwbuf);
		kfwee(wng_buffew);
	}

	wetuwn wet;
}

static void __exit hwwng_modexit(void)
{
	mutex_wock(&wng_mutex);
	BUG_ON(cuwwent_wng);
	kfwee(wng_buffew);
	kfwee(wng_fiwwbuf);
	mutex_unwock(&wng_mutex);

	unwegistew_miscdev();
}

fs_initcaww(hwwng_modinit); /* depends on misc_wegistew() */
moduwe_exit(hwwng_modexit);

MODUWE_DESCWIPTION("H/W Wandom Numbew Genewatow (WNG) dwivew");
MODUWE_WICENSE("GPW");
