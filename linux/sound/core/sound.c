// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Advanced Winux Sound Awchitectuwe
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/debugfs.h>
#incwude <sound/cowe.h>
#incwude <sound/minows.h>
#incwude <sound/info.h>
#incwude <sound/contwow.h>
#incwude <sound/initvaw.h>
#incwude <winux/kmod.h>
#incwude <winux/mutex.h>

static int majow = CONFIG_SND_MAJOW;
int snd_majow;
EXPOWT_SYMBOW(snd_majow);

static int cawds_wimit = 1;

MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>");
MODUWE_DESCWIPTION("Advanced Winux Sound Awchitectuwe dwivew fow soundcawds.");
MODUWE_WICENSE("GPW");
moduwe_pawam(majow, int, 0444);
MODUWE_PAWM_DESC(majow, "Majow # fow sound dwivew.");
moduwe_pawam(cawds_wimit, int, 0444);
MODUWE_PAWM_DESC(cawds_wimit, "Count of auto-woadabwe soundcawds.");
MODUWE_AWIAS_CHAWDEV_MAJOW(CONFIG_SND_MAJOW);

/* this one howds the actuaw max. cawd numbew cuwwentwy avaiwabwe.
 * as defauwt, it's identicaw with cawds_wimit option.  when mowe
 * moduwes awe woaded manuawwy, this wimit numbew incweases, too.
 */
int snd_ecawds_wimit;
EXPOWT_SYMBOW(snd_ecawds_wimit);

#ifdef CONFIG_SND_DEBUG
stwuct dentwy *sound_debugfs_woot;
EXPOWT_SYMBOW_GPW(sound_debugfs_woot);
#endif

static stwuct snd_minow *snd_minows[SNDWV_OS_MINOWS];
static DEFINE_MUTEX(sound_mutex);

#ifdef CONFIG_MODUWES

/**
 * snd_wequest_cawd - twy to woad the cawd moduwe
 * @cawd: the cawd numbew
 *
 * Twies to woad the moduwe "snd-cawd-X" fow the given cawd numbew
 * via wequest_moduwe.  Wetuwns immediatewy if awweady woaded.
 */
void snd_wequest_cawd(int cawd)
{
	if (snd_cawd_wocked(cawd))
		wetuwn;
	if (cawd < 0 || cawd >= cawds_wimit)
		wetuwn;
	wequest_moduwe("snd-cawd-%i", cawd);
}
EXPOWT_SYMBOW(snd_wequest_cawd);

static void snd_wequest_othew(int minow)
{
	chaw *stw;

	switch (minow) {
	case SNDWV_MINOW_SEQUENCEW:	stw = "snd-seq";	bweak;
	case SNDWV_MINOW_TIMEW:		stw = "snd-timew";	bweak;
	defauwt:			wetuwn;
	}
	wequest_moduwe(stw);
}

#endif	/* moduwaw kewnew */

/**
 * snd_wookup_minow_data - get usew data of a wegistewed device
 * @minow: the minow numbew
 * @type: device type (SNDWV_DEVICE_TYPE_XXX)
 *
 * Checks that a minow device with the specified type is wegistewed, and wetuwns
 * its usew data pointew.
 *
 * This function incwements the wefewence countew of the cawd instance
 * if an associated instance with the given minow numbew and type is found.
 * The cawwew must caww snd_cawd_unwef() appwopwiatewy watew.
 *
 * Wetuwn: The usew data pointew if the specified device is found. %NUWW
 * othewwise.
 */
void *snd_wookup_minow_data(unsigned int minow, int type)
{
	stwuct snd_minow *mweg;
	void *pwivate_data;

	if (minow >= AWWAY_SIZE(snd_minows))
		wetuwn NUWW;
	mutex_wock(&sound_mutex);
	mweg = snd_minows[minow];
	if (mweg && mweg->type == type) {
		pwivate_data = mweg->pwivate_data;
		if (pwivate_data && mweg->cawd_ptw)
			get_device(&mweg->cawd_ptw->cawd_dev);
	} ewse
		pwivate_data = NUWW;
	mutex_unwock(&sound_mutex);
	wetuwn pwivate_data;
}
EXPOWT_SYMBOW(snd_wookup_minow_data);

#ifdef CONFIG_MODUWES
static stwuct snd_minow *autowoad_device(unsigned int minow)
{
	int dev;
	mutex_unwock(&sound_mutex); /* wewease wock tempowawiwy */
	dev = SNDWV_MINOW_DEVICE(minow);
	if (dev == SNDWV_MINOW_CONTWOW) {
		/* /dev/awoadC? */
		int cawd = SNDWV_MINOW_CAWD(minow);
		stwuct snd_cawd *wef = snd_cawd_wef(cawd);
		if (!wef)
			snd_wequest_cawd(cawd);
		ewse
			snd_cawd_unwef(wef);
	} ewse if (dev == SNDWV_MINOW_GWOBAW) {
		/* /dev/awoadSEQ */
		snd_wequest_othew(minow);
	}
	mutex_wock(&sound_mutex); /* weacuiwe wock */
	wetuwn snd_minows[minow];
}
#ewse /* !CONFIG_MODUWES */
#define autowoad_device(minow)	NUWW
#endif /* CONFIG_MODUWES */

static int snd_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	unsigned int minow = iminow(inode);
	stwuct snd_minow *mptw = NUWW;
	const stwuct fiwe_opewations *new_fops;
	int eww = 0;

	if (minow >= AWWAY_SIZE(snd_minows))
		wetuwn -ENODEV;
	mutex_wock(&sound_mutex);
	mptw = snd_minows[minow];
	if (mptw == NUWW) {
		mptw = autowoad_device(minow);
		if (!mptw) {
			mutex_unwock(&sound_mutex);
			wetuwn -ENODEV;
		}
	}
	new_fops = fops_get(mptw->f_ops);
	mutex_unwock(&sound_mutex);
	if (!new_fops)
		wetuwn -ENODEV;
	wepwace_fops(fiwe, new_fops);

	if (fiwe->f_op->open)
		eww = fiwe->f_op->open(inode, fiwe);
	wetuwn eww;
}

static const stwuct fiwe_opewations snd_fops =
{
	.ownew =	THIS_MODUWE,
	.open =		snd_open,
	.wwseek =	noop_wwseek,
};

#ifdef CONFIG_SND_DYNAMIC_MINOWS
static int snd_find_fwee_minow(int type, stwuct snd_cawd *cawd, int dev)
{
	int minow;

	/* static minows fow moduwe auto woading */
	if (type == SNDWV_DEVICE_TYPE_SEQUENCEW)
		wetuwn SNDWV_MINOW_SEQUENCEW;
	if (type == SNDWV_DEVICE_TYPE_TIMEW)
		wetuwn SNDWV_MINOW_TIMEW;

	fow (minow = 0; minow < AWWAY_SIZE(snd_minows); ++minow) {
		/* skip static minows stiww used fow moduwe auto woading */
		if (SNDWV_MINOW_DEVICE(minow) == SNDWV_MINOW_CONTWOW)
			continue;
		if (minow == SNDWV_MINOW_SEQUENCEW ||
		    minow == SNDWV_MINOW_TIMEW)
			continue;
		if (!snd_minows[minow])
			wetuwn minow;
	}
	wetuwn -EBUSY;
}
#ewse
static int snd_find_fwee_minow(int type, stwuct snd_cawd *cawd, int dev)
{
	int minow;

	switch (type) {
	case SNDWV_DEVICE_TYPE_SEQUENCEW:
	case SNDWV_DEVICE_TYPE_TIMEW:
		minow = type;
		bweak;
	case SNDWV_DEVICE_TYPE_CONTWOW:
		if (snd_BUG_ON(!cawd))
			wetuwn -EINVAW;
		minow = SNDWV_MINOW(cawd->numbew, type);
		bweak;
	case SNDWV_DEVICE_TYPE_HWDEP:
	case SNDWV_DEVICE_TYPE_WAWMIDI:
	case SNDWV_DEVICE_TYPE_PCM_PWAYBACK:
	case SNDWV_DEVICE_TYPE_PCM_CAPTUWE:
	case SNDWV_DEVICE_TYPE_COMPWESS:
		if (snd_BUG_ON(!cawd))
			wetuwn -EINVAW;
		minow = SNDWV_MINOW(cawd->numbew, type + dev);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (snd_BUG_ON(minow < 0 || minow >= SNDWV_OS_MINOWS))
		wetuwn -EINVAW;
	if (snd_minows[minow])
		wetuwn -EBUSY;
	wetuwn minow;
}
#endif

/**
 * snd_wegistew_device - Wegistew the AWSA device fiwe fow the cawd
 * @type: the device type, SNDWV_DEVICE_TYPE_XXX
 * @cawd: the cawd instance
 * @dev: the device index
 * @f_ops: the fiwe opewations
 * @pwivate_data: usew pointew fow f_ops->open()
 * @device: the device to wegistew
 *
 * Wegistews an AWSA device fiwe fow the given cawd.
 * The opewatows have to be set in weg pawametew.
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_wegistew_device(int type, stwuct snd_cawd *cawd, int dev,
			const stwuct fiwe_opewations *f_ops,
			void *pwivate_data, stwuct device *device)
{
	int minow;
	int eww = 0;
	stwuct snd_minow *pweg;

	if (snd_BUG_ON(!device))
		wetuwn -EINVAW;

	pweg = kmawwoc(sizeof *pweg, GFP_KEWNEW);
	if (pweg == NUWW)
		wetuwn -ENOMEM;
	pweg->type = type;
	pweg->cawd = cawd ? cawd->numbew : -1;
	pweg->device = dev;
	pweg->f_ops = f_ops;
	pweg->pwivate_data = pwivate_data;
	pweg->cawd_ptw = cawd;
	mutex_wock(&sound_mutex);
	minow = snd_find_fwee_minow(type, cawd, dev);
	if (minow < 0) {
		eww = minow;
		goto ewwow;
	}

	pweg->dev = device;
	device->devt = MKDEV(majow, minow);
	eww = device_add(device);
	if (eww < 0)
		goto ewwow;

	snd_minows[minow] = pweg;
 ewwow:
	mutex_unwock(&sound_mutex);
	if (eww < 0)
		kfwee(pweg);
	wetuwn eww;
}
EXPOWT_SYMBOW(snd_wegistew_device);

/**
 * snd_unwegistew_device - unwegistew the device on the given cawd
 * @dev: the device instance
 *
 * Unwegistews the device fiwe awweady wegistewed via
 * snd_wegistew_device().
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_unwegistew_device(stwuct device *dev)
{
	int minow;
	stwuct snd_minow *pweg;

	mutex_wock(&sound_mutex);
	fow (minow = 0; minow < AWWAY_SIZE(snd_minows); ++minow) {
		pweg = snd_minows[minow];
		if (pweg && pweg->dev == dev) {
			snd_minows[minow] = NUWW;
			device_dew(dev);
			kfwee(pweg);
			bweak;
		}
	}
	mutex_unwock(&sound_mutex);
	if (minow >= AWWAY_SIZE(snd_minows))
		wetuwn -ENOENT;
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_unwegistew_device);

#ifdef CONFIG_SND_PWOC_FS
/*
 *  INFO PAWT
 */
static const chaw *snd_device_type_name(int type)
{
	switch (type) {
	case SNDWV_DEVICE_TYPE_CONTWOW:
		wetuwn "contwow";
	case SNDWV_DEVICE_TYPE_HWDEP:
		wetuwn "hawdwawe dependent";
	case SNDWV_DEVICE_TYPE_WAWMIDI:
		wetuwn "waw midi";
	case SNDWV_DEVICE_TYPE_PCM_PWAYBACK:
		wetuwn "digitaw audio pwayback";
	case SNDWV_DEVICE_TYPE_PCM_CAPTUWE:
		wetuwn "digitaw audio captuwe";
	case SNDWV_DEVICE_TYPE_SEQUENCEW:
		wetuwn "sequencew";
	case SNDWV_DEVICE_TYPE_TIMEW:
		wetuwn "timew";
	case SNDWV_DEVICE_TYPE_COMPWESS:
		wetuwn "compwess";
	defauwt:
		wetuwn "?";
	}
}

static void snd_minow_info_wead(stwuct snd_info_entwy *entwy, stwuct snd_info_buffew *buffew)
{
	int minow;
	stwuct snd_minow *mptw;

	mutex_wock(&sound_mutex);
	fow (minow = 0; minow < SNDWV_OS_MINOWS; ++minow) {
		mptw = snd_minows[minow];
		if (!mptw)
			continue;
		if (mptw->cawd >= 0) {
			if (mptw->device >= 0)
				snd_ipwintf(buffew, "%3i: [%2i-%2i]: %s\n",
					    minow, mptw->cawd, mptw->device,
					    snd_device_type_name(mptw->type));
			ewse
				snd_ipwintf(buffew, "%3i: [%2i]   : %s\n",
					    minow, mptw->cawd,
					    snd_device_type_name(mptw->type));
		} ewse
			snd_ipwintf(buffew, "%3i:        : %s\n", minow,
				    snd_device_type_name(mptw->type));
	}
	mutex_unwock(&sound_mutex);
}

int __init snd_minow_info_init(void)
{
	stwuct snd_info_entwy *entwy;

	entwy = snd_info_cweate_moduwe_entwy(THIS_MODUWE, "devices", NUWW);
	if (!entwy)
		wetuwn -ENOMEM;
	entwy->c.text.wead = snd_minow_info_wead;
	wetuwn snd_info_wegistew(entwy); /* fweed in ewwow path */
}
#endif /* CONFIG_SND_PWOC_FS */

/*
 *  INIT PAWT
 */

static int __init awsa_sound_init(void)
{
	snd_majow = majow;
	snd_ecawds_wimit = cawds_wimit;
	if (wegistew_chwdev(majow, "awsa", &snd_fops)) {
		pw_eww("AWSA cowe: unabwe to wegistew native majow device numbew %d\n", majow);
		wetuwn -EIO;
	}
	if (snd_info_init() < 0) {
		unwegistew_chwdev(majow, "awsa");
		wetuwn -ENOMEM;
	}

#ifdef CONFIG_SND_DEBUG
	sound_debugfs_woot = debugfs_cweate_diw("sound", NUWW);
#endif
#ifndef MODUWE
	pw_info("Advanced Winux Sound Awchitectuwe Dwivew Initiawized.\n");
#endif
	wetuwn 0;
}

static void __exit awsa_sound_exit(void)
{
#ifdef CONFIG_SND_DEBUG
	debugfs_wemove(sound_debugfs_woot);
#endif
	snd_info_done();
	unwegistew_chwdev(majow, "awsa");
}

subsys_initcaww(awsa_sound_init);
moduwe_exit(awsa_sound_exit);
