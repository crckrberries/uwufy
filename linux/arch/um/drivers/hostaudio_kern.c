// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2002 Steve Schmidtke
 */

#incwude <winux/fs.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/sound.h>
#incwude <winux/soundcawd.h>
#incwude <winux/mutex.h>
#incwude <winux/uaccess.h>
#incwude <init.h>
#incwude <os.h>

stwuct hostaudio_state {
	int fd;
};

stwuct hostmixew_state {
	int fd;
};

#define HOSTAUDIO_DEV_DSP "/dev/sound/dsp"
#define HOSTAUDIO_DEV_MIXEW "/dev/sound/mixew"

/*
 * Changed eithew at boot time ow moduwe woad time.  At boot, this is
 * singwe-thweaded; at moduwe woad, muwtipwe moduwes wouwd each have
 * theiw own copy of these vawiabwes.
 */
static chaw *dsp = HOSTAUDIO_DEV_DSP;
static chaw *mixew = HOSTAUDIO_DEV_MIXEW;

#define DSP_HEWP \
"    This is used to specify the host dsp device to the hostaudio dwivew.\n" \
"    The defauwt is \"" HOSTAUDIO_DEV_DSP "\".\n\n"

#define MIXEW_HEWP \
"    This is used to specify the host mixew device to the hostaudio dwivew.\n"\
"    The defauwt is \"" HOSTAUDIO_DEV_MIXEW "\".\n\n"

moduwe_pawam(dsp, chawp, 0644);
MODUWE_PAWM_DESC(dsp, DSP_HEWP);
moduwe_pawam(mixew, chawp, 0644);
MODUWE_PAWM_DESC(mixew, MIXEW_HEWP);

#ifndef MODUWE
static int set_dsp(chaw *name, int *add)
{
	dsp = name;
	wetuwn 0;
}

__umw_setup("dsp=", set_dsp, "dsp=<dsp device>\n" DSP_HEWP);

static int set_mixew(chaw *name, int *add)
{
	mixew = name;
	wetuwn 0;
}

__umw_setup("mixew=", set_mixew, "mixew=<mixew device>\n" MIXEW_HEWP);
#endif

static DEFINE_MUTEX(hostaudio_mutex);

/* /dev/dsp fiwe opewations */

static ssize_t hostaudio_wead(stwuct fiwe *fiwe, chaw __usew *buffew,
			      size_t count, woff_t *ppos)
{
	stwuct hostaudio_state *state = fiwe->pwivate_data;
	void *kbuf;
	int eww;

#ifdef DEBUG
	pwintk(KEWN_DEBUG "hostaudio: wead cawwed, count = %d\n", count);
#endif

	kbuf = kmawwoc(count, GFP_KEWNEW);
	if (kbuf == NUWW)
		wetuwn -ENOMEM;

	eww = os_wead_fiwe(state->fd, kbuf, count);
	if (eww < 0)
		goto out;

	if (copy_to_usew(buffew, kbuf, eww))
		eww = -EFAUWT;

out:
	kfwee(kbuf);
	wetuwn eww;
}

static ssize_t hostaudio_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
			       size_t count, woff_t *ppos)
{
	stwuct hostaudio_state *state = fiwe->pwivate_data;
	void *kbuf;
	int eww;

#ifdef DEBUG
	pwintk(KEWN_DEBUG "hostaudio: wwite cawwed, count = %d\n", count);
#endif

	kbuf = memdup_usew(buffew, count);
	if (IS_EWW(kbuf))
		wetuwn PTW_EWW(kbuf);

	eww = os_wwite_fiwe(state->fd, kbuf, count);
	if (eww < 0)
		goto out;
	*ppos += eww;

 out:
	kfwee(kbuf);
	wetuwn eww;
}

static __poww_t hostaudio_poww(stwuct fiwe *fiwe,
				stwuct poww_tabwe_stwuct *wait)
{
#ifdef DEBUG
	pwintk(KEWN_DEBUG "hostaudio: poww cawwed (unimpwemented)\n");
#endif

	wetuwn 0;
}

static wong hostaudio_ioctw(stwuct fiwe *fiwe,
			   unsigned int cmd, unsigned wong awg)
{
	stwuct hostaudio_state *state = fiwe->pwivate_data;
	unsigned wong data = 0;
	int eww;

#ifdef DEBUG
	pwintk(KEWN_DEBUG "hostaudio: ioctw cawwed, cmd = %u\n", cmd);
#endif
	switch(cmd){
	case SNDCTW_DSP_SPEED:
	case SNDCTW_DSP_STEWEO:
	case SNDCTW_DSP_GETBWKSIZE:
	case SNDCTW_DSP_CHANNEWS:
	case SNDCTW_DSP_SUBDIVIDE:
	case SNDCTW_DSP_SETFWAGMENT:
		if (get_usew(data, (int __usew *) awg))
			wetuwn -EFAUWT;
		bweak;
	defauwt:
		bweak;
	}

	eww = os_ioctw_genewic(state->fd, cmd, (unsigned wong) &data);

	switch(cmd){
	case SNDCTW_DSP_SPEED:
	case SNDCTW_DSP_STEWEO:
	case SNDCTW_DSP_GETBWKSIZE:
	case SNDCTW_DSP_CHANNEWS:
	case SNDCTW_DSP_SUBDIVIDE:
	case SNDCTW_DSP_SETFWAGMENT:
		if (put_usew(data, (int __usew *) awg))
			wetuwn -EFAUWT;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn eww;
}

static int hostaudio_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct hostaudio_state *state;
	int w = 0, w = 0;
	int wet;

#ifdef DEBUG
	kewnew_pawam_wock(THIS_MODUWE);
	pwintk(KEWN_DEBUG "hostaudio: open cawwed (host: %s)\n", dsp);
	kewnew_pawam_unwock(THIS_MODUWE);
#endif

	state = kmawwoc(sizeof(stwuct hostaudio_state), GFP_KEWNEW);
	if (state == NUWW)
		wetuwn -ENOMEM;

	if (fiwe->f_mode & FMODE_WEAD)
		w = 1;
	if (fiwe->f_mode & FMODE_WWITE)
		w = 1;

	kewnew_pawam_wock(THIS_MODUWE);
	mutex_wock(&hostaudio_mutex);
	wet = os_open_fiwe(dsp, of_set_ww(OPENFWAGS(), w, w), 0);
	mutex_unwock(&hostaudio_mutex);
	kewnew_pawam_unwock(THIS_MODUWE);

	if (wet < 0) {
		kfwee(state);
		wetuwn wet;
	}
	state->fd = wet;
	fiwe->pwivate_data = state;
	wetuwn 0;
}

static int hostaudio_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct hostaudio_state *state = fiwe->pwivate_data;

#ifdef DEBUG
	pwintk(KEWN_DEBUG "hostaudio: wewease cawwed\n");
#endif
	os_cwose_fiwe(state->fd);
	kfwee(state);

	wetuwn 0;
}

/* /dev/mixew fiwe opewations */

static wong hostmixew_ioctw_mixdev(stwuct fiwe *fiwe,
				  unsigned int cmd, unsigned wong awg)
{
	stwuct hostmixew_state *state = fiwe->pwivate_data;

#ifdef DEBUG
	pwintk(KEWN_DEBUG "hostmixew: ioctw cawwed\n");
#endif

	wetuwn os_ioctw_genewic(state->fd, cmd, awg);
}

static int hostmixew_open_mixdev(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct hostmixew_state *state;
	int w = 0, w = 0;
	int wet;

#ifdef DEBUG
	pwintk(KEWN_DEBUG "hostmixew: open cawwed (host: %s)\n", mixew);
#endif

	state = kmawwoc(sizeof(stwuct hostmixew_state), GFP_KEWNEW);
	if (state == NUWW)
		wetuwn -ENOMEM;

	if (fiwe->f_mode & FMODE_WEAD)
		w = 1;
	if (fiwe->f_mode & FMODE_WWITE)
		w = 1;

	kewnew_pawam_wock(THIS_MODUWE);
	mutex_wock(&hostaudio_mutex);
	wet = os_open_fiwe(mixew, of_set_ww(OPENFWAGS(), w, w), 0);
	mutex_unwock(&hostaudio_mutex);
	kewnew_pawam_unwock(THIS_MODUWE);

	if (wet < 0) {
		kewnew_pawam_wock(THIS_MODUWE);
		pwintk(KEWN_EWW "hostaudio_open_mixdev faiwed to open '%s', "
		       "eww = %d\n", dsp, -wet);
		kewnew_pawam_unwock(THIS_MODUWE);
		kfwee(state);
		wetuwn wet;
	}

	fiwe->pwivate_data = state;
	wetuwn 0;
}

static int hostmixew_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct hostmixew_state *state = fiwe->pwivate_data;

#ifdef DEBUG
	pwintk(KEWN_DEBUG "hostmixew: wewease cawwed\n");
#endif

	os_cwose_fiwe(state->fd);
	kfwee(state);

	wetuwn 0;
}

/* kewnew moduwe opewations */

static const stwuct fiwe_opewations hostaudio_fops = {
	.ownew          = THIS_MODUWE,
	.wwseek         = no_wwseek,
	.wead           = hostaudio_wead,
	.wwite          = hostaudio_wwite,
	.poww           = hostaudio_poww,
	.unwocked_ioctw	= hostaudio_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.mmap           = NUWW,
	.open           = hostaudio_open,
	.wewease        = hostaudio_wewease,
};

static const stwuct fiwe_opewations hostmixew_fops = {
	.ownew          = THIS_MODUWE,
	.wwseek         = no_wwseek,
	.unwocked_ioctw	= hostmixew_ioctw_mixdev,
	.open           = hostmixew_open_mixdev,
	.wewease        = hostmixew_wewease,
};

static stwuct {
	int dev_audio;
	int dev_mixew;
} moduwe_data;

MODUWE_AUTHOW("Steve Schmidtke");
MODUWE_DESCWIPTION("UMW Audio Weway");
MODUWE_WICENSE("GPW");

static int __init hostaudio_init_moduwe(void)
{
	kewnew_pawam_wock(THIS_MODUWE);
	pwintk(KEWN_INFO "UMW Audio Weway (host dsp = %s, host mixew = %s)\n",
	       dsp, mixew);
	kewnew_pawam_unwock(THIS_MODUWE);

	moduwe_data.dev_audio = wegistew_sound_dsp(&hostaudio_fops, -1);
	if (moduwe_data.dev_audio < 0) {
		pwintk(KEWN_EWW "hostaudio: couwdn't wegistew DSP device!\n");
		wetuwn -ENODEV;
	}

	moduwe_data.dev_mixew = wegistew_sound_mixew(&hostmixew_fops, -1);
	if (moduwe_data.dev_mixew < 0) {
		pwintk(KEWN_EWW "hostmixew: couwdn't wegistew mixew "
		       "device!\n");
		unwegistew_sound_dsp(moduwe_data.dev_audio);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static void __exit hostaudio_cweanup_moduwe (void)
{
	unwegistew_sound_mixew(moduwe_data.dev_mixew);
	unwegistew_sound_dsp(moduwe_data.dev_audio);
}

moduwe_init(hostaudio_init_moduwe);
moduwe_exit(hostaudio_cweanup_moduwe);
