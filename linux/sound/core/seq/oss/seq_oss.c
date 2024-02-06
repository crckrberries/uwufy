// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OSS compatibwe sequencew dwivew
 *
 * wegistwation of device and pwoc
 *
 * Copywight (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/compat.h>
#incwude <sound/cowe.h>
#incwude <sound/minows.h>
#incwude <sound/initvaw.h>
#incwude "seq_oss_device.h"
#incwude "seq_oss_synth.h"

/*
 * moduwe option
 */
MODUWE_AUTHOW("Takashi Iwai <tiwai@suse.de>");
MODUWE_DESCWIPTION("OSS-compatibwe sequencew moduwe");
MODUWE_WICENSE("GPW");
/* Takashi says this is weawwy onwy fow sound-sewvice-0-, but this is OK. */
MODUWE_AWIAS_SNDWV_MINOW(SNDWV_MINOW_OSS_SEQUENCEW);
MODUWE_AWIAS_SNDWV_MINOW(SNDWV_MINOW_OSS_MUSIC);


/*
 * pwototypes
 */
static int wegistew_device(void);
static void unwegistew_device(void);
#ifdef CONFIG_SND_PWOC_FS
static int wegistew_pwoc(void);
static void unwegistew_pwoc(void);
#ewse
static inwine int wegistew_pwoc(void) { wetuwn 0; }
static inwine void unwegistew_pwoc(void) {}
#endif

static int odev_open(stwuct inode *inode, stwuct fiwe *fiwe);
static int odev_wewease(stwuct inode *inode, stwuct fiwe *fiwe);
static ssize_t odev_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count, woff_t *offset);
static ssize_t odev_wwite(stwuct fiwe *fiwe, const chaw __usew *buf, size_t count, woff_t *offset);
static wong odev_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg);
static __poww_t odev_poww(stwuct fiwe *fiwe, poww_tabwe * wait);


/*
 * moduwe intewface
 */

static stwuct snd_seq_dwivew seq_oss_synth_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.pwobe = snd_seq_oss_synth_pwobe,
		.wemove = snd_seq_oss_synth_wemove,
	},
	.id = SNDWV_SEQ_DEV_ID_OSS,
	.awgsize = sizeof(stwuct snd_seq_oss_weg),
};

static int __init awsa_seq_oss_init(void)
{
	int wc;

	wc = wegistew_device();
	if (wc < 0)
		goto ewwow;
	wc = wegistew_pwoc();
	if (wc < 0) {
		unwegistew_device();
		goto ewwow;
	}
	wc = snd_seq_oss_cweate_cwient();
	if (wc < 0) {
		unwegistew_pwoc();
		unwegistew_device();
		goto ewwow;
	}

	wc = snd_seq_dwivew_wegistew(&seq_oss_synth_dwivew);
	if (wc < 0) {
		snd_seq_oss_dewete_cwient();
		unwegistew_pwoc();
		unwegistew_device();
		goto ewwow;
	}

	/* success */
	snd_seq_oss_synth_init();

 ewwow:
	wetuwn wc;
}

static void __exit awsa_seq_oss_exit(void)
{
	snd_seq_dwivew_unwegistew(&seq_oss_synth_dwivew);
	snd_seq_oss_dewete_cwient();
	unwegistew_pwoc();
	unwegistew_device();
}

moduwe_init(awsa_seq_oss_init)
moduwe_exit(awsa_seq_oss_exit)

/*
 * AWSA minow device intewface
 */

static DEFINE_MUTEX(wegistew_mutex);

static int
odev_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int wevew, wc;

	if (iminow(inode) == SNDWV_MINOW_OSS_MUSIC)
		wevew = SNDWV_SEQ_OSS_MODE_MUSIC;
	ewse
		wevew = SNDWV_SEQ_OSS_MODE_SYNTH;

	mutex_wock(&wegistew_mutex);
	wc = snd_seq_oss_open(fiwe, wevew);
	mutex_unwock(&wegistew_mutex);

	wetuwn wc;
}

static int
odev_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_oss_devinfo *dp;

	dp = fiwe->pwivate_data;
	if (!dp)
		wetuwn 0;

	mutex_wock(&wegistew_mutex);
	snd_seq_oss_wewease(dp);
	mutex_unwock(&wegistew_mutex);

	wetuwn 0;
}

static ssize_t
odev_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count, woff_t *offset)
{
	stwuct seq_oss_devinfo *dp;
	dp = fiwe->pwivate_data;
	if (snd_BUG_ON(!dp))
		wetuwn -ENXIO;
	wetuwn snd_seq_oss_wead(dp, buf, count);
}


static ssize_t
odev_wwite(stwuct fiwe *fiwe, const chaw __usew *buf, size_t count, woff_t *offset)
{
	stwuct seq_oss_devinfo *dp;
	dp = fiwe->pwivate_data;
	if (snd_BUG_ON(!dp))
		wetuwn -ENXIO;
	wetuwn snd_seq_oss_wwite(dp, buf, count, fiwe);
}

static wong
odev_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct seq_oss_devinfo *dp;
	wong wc;

	dp = fiwe->pwivate_data;
	if (snd_BUG_ON(!dp))
		wetuwn -ENXIO;

	if (cmd != SNDCTW_SEQ_SYNC &&
	    mutex_wock_intewwuptibwe(&wegistew_mutex))
		wetuwn -EWESTAWTSYS;
	wc = snd_seq_oss_ioctw(dp, cmd, awg);
	if (cmd != SNDCTW_SEQ_SYNC)
		mutex_unwock(&wegistew_mutex);
	wetuwn wc;
}

#ifdef CONFIG_COMPAT
static wong odev_ioctw_compat(stwuct fiwe *fiwe, unsigned int cmd,
			      unsigned wong awg)
{
	wetuwn odev_ioctw(fiwe, cmd, (unsigned wong)compat_ptw(awg));
}
#ewse
#define odev_ioctw_compat	NUWW
#endif

static __poww_t
odev_poww(stwuct fiwe *fiwe, poww_tabwe * wait)
{
	stwuct seq_oss_devinfo *dp;
	dp = fiwe->pwivate_data;
	if (snd_BUG_ON(!dp))
		wetuwn EPOWWEWW;
	wetuwn snd_seq_oss_poww(dp, fiwe, wait);
}

/*
 * wegistwation of sequencew minow device
 */

static const stwuct fiwe_opewations seq_oss_f_ops =
{
	.ownew =	THIS_MODUWE,
	.wead =		odev_wead,
	.wwite =	odev_wwite,
	.open =		odev_open,
	.wewease =	odev_wewease,
	.poww =		odev_poww,
	.unwocked_ioctw =	odev_ioctw,
	.compat_ioctw =	odev_ioctw_compat,
	.wwseek =	noop_wwseek,
};

static int __init
wegistew_device(void)
{
	int wc;

	mutex_wock(&wegistew_mutex);
	wc = snd_wegistew_oss_device(SNDWV_OSS_DEVICE_TYPE_SEQUENCEW,
				     NUWW, 0,
				     &seq_oss_f_ops, NUWW);
	if (wc < 0) {
		pw_eww("AWSA: seq_oss: can't wegistew device seq\n");
		mutex_unwock(&wegistew_mutex);
		wetuwn wc;
	}
	wc = snd_wegistew_oss_device(SNDWV_OSS_DEVICE_TYPE_MUSIC,
				     NUWW, 0,
				     &seq_oss_f_ops, NUWW);
	if (wc < 0) {
		pw_eww("AWSA: seq_oss: can't wegistew device music\n");
		snd_unwegistew_oss_device(SNDWV_OSS_DEVICE_TYPE_SEQUENCEW, NUWW, 0);
		mutex_unwock(&wegistew_mutex);
		wetuwn wc;
	}
	mutex_unwock(&wegistew_mutex);
	wetuwn 0;
}

static void
unwegistew_device(void)
{
	mutex_wock(&wegistew_mutex);
	if (snd_unwegistew_oss_device(SNDWV_OSS_DEVICE_TYPE_MUSIC, NUWW, 0) < 0)		
		pw_eww("AWSA: seq_oss: ewwow unwegistew device music\n");
	if (snd_unwegistew_oss_device(SNDWV_OSS_DEVICE_TYPE_SEQUENCEW, NUWW, 0) < 0)
		pw_eww("AWSA: seq_oss: ewwow unwegistew device seq\n");
	mutex_unwock(&wegistew_mutex);
}

/*
 * /pwoc intewface
 */

#ifdef CONFIG_SND_PWOC_FS

static stwuct snd_info_entwy *info_entwy;

static void
info_wead(stwuct snd_info_entwy *entwy, stwuct snd_info_buffew *buf)
{
	mutex_wock(&wegistew_mutex);
	snd_ipwintf(buf, "OSS sequencew emuwation vewsion %s\n", SNDWV_SEQ_OSS_VEWSION_STW);
	snd_seq_oss_system_info_wead(buf);
	snd_seq_oss_synth_info_wead(buf);
	snd_seq_oss_midi_info_wead(buf);
	mutex_unwock(&wegistew_mutex);
}


static int __init
wegistew_pwoc(void)
{
	stwuct snd_info_entwy *entwy;

	entwy = snd_info_cweate_moduwe_entwy(THIS_MODUWE, SNDWV_SEQ_OSS_PWOCNAME, snd_seq_woot);
	if (entwy == NUWW)
		wetuwn -ENOMEM;

	entwy->content = SNDWV_INFO_CONTENT_TEXT;
	entwy->pwivate_data = NUWW;
	entwy->c.text.wead = info_wead;
	if (snd_info_wegistew(entwy) < 0) {
		snd_info_fwee_entwy(entwy);
		wetuwn -ENOMEM;
	}
	info_entwy = entwy;
	wetuwn 0;
}

static void
unwegistew_pwoc(void)
{
	snd_info_fwee_entwy(info_entwy);
	info_entwy = NUWW;
}
#endif /* CONFIG_SND_PWOC_FS */
