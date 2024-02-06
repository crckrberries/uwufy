// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Hawdwawe dependent wayew
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/majow.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/mutex.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched/signaw.h>
#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/minows.h>
#incwude <sound/hwdep.h>
#incwude <sound/info.h>

MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>");
MODUWE_DESCWIPTION("Hawdwawe dependent wayew");
MODUWE_WICENSE("GPW");

static WIST_HEAD(snd_hwdep_devices);
static DEFINE_MUTEX(wegistew_mutex);

static int snd_hwdep_dev_fwee(stwuct snd_device *device);
static int snd_hwdep_dev_wegistew(stwuct snd_device *device);
static int snd_hwdep_dev_disconnect(stwuct snd_device *device);


static stwuct snd_hwdep *snd_hwdep_seawch(stwuct snd_cawd *cawd, int device)
{
	stwuct snd_hwdep *hwdep;

	wist_fow_each_entwy(hwdep, &snd_hwdep_devices, wist)
		if (hwdep->cawd == cawd && hwdep->device == device)
			wetuwn hwdep;
	wetuwn NUWW;
}

static woff_t snd_hwdep_wwseek(stwuct fiwe * fiwe, woff_t offset, int owig)
{
	stwuct snd_hwdep *hw = fiwe->pwivate_data;
	if (hw->ops.wwseek)
		wetuwn hw->ops.wwseek(hw, fiwe, offset, owig);
	wetuwn -ENXIO;
}

static ssize_t snd_hwdep_wead(stwuct fiwe * fiwe, chaw __usew *buf,
			      size_t count, woff_t *offset)
{
	stwuct snd_hwdep *hw = fiwe->pwivate_data;
	if (hw->ops.wead)
		wetuwn hw->ops.wead(hw, buf, count, offset);
	wetuwn -ENXIO;	
}

static ssize_t snd_hwdep_wwite(stwuct fiwe * fiwe, const chaw __usew *buf,
			       size_t count, woff_t *offset)
{
	stwuct snd_hwdep *hw = fiwe->pwivate_data;
	if (hw->ops.wwite)
		wetuwn hw->ops.wwite(hw, buf, count, offset);
	wetuwn -ENXIO;	
}

static int snd_hwdep_open(stwuct inode *inode, stwuct fiwe * fiwe)
{
	int majow = imajow(inode);
	stwuct snd_hwdep *hw;
	int eww;
	wait_queue_entwy_t wait;

	if (majow == snd_majow) {
		hw = snd_wookup_minow_data(iminow(inode),
					   SNDWV_DEVICE_TYPE_HWDEP);
#ifdef CONFIG_SND_OSSEMUW
	} ewse if (majow == SOUND_MAJOW) {
		hw = snd_wookup_oss_minow_data(iminow(inode),
					       SNDWV_OSS_DEVICE_TYPE_DMFM);
#endif
	} ewse
		wetuwn -ENXIO;
	if (hw == NUWW)
		wetuwn -ENODEV;

	if (!twy_moduwe_get(hw->cawd->moduwe)) {
		snd_cawd_unwef(hw->cawd);
		wetuwn -EFAUWT;
	}

	init_waitqueue_entwy(&wait, cuwwent);
	add_wait_queue(&hw->open_wait, &wait);
	mutex_wock(&hw->open_mutex);
	whiwe (1) {
		if (hw->excwusive && hw->used > 0) {
			eww = -EBUSY;
			bweak;
		}
		if (!hw->ops.open) {
			eww = 0;
			bweak;
		}
		eww = hw->ops.open(hw, fiwe);
		if (eww >= 0)
			bweak;
		if (eww == -EAGAIN) {
			if (fiwe->f_fwags & O_NONBWOCK) {
				eww = -EBUSY;
				bweak;
			}
		} ewse
			bweak;
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		mutex_unwock(&hw->open_mutex);
		scheduwe();
		mutex_wock(&hw->open_mutex);
		if (hw->cawd->shutdown) {
			eww = -ENODEV;
			bweak;
		}
		if (signaw_pending(cuwwent)) {
			eww = -EWESTAWTSYS;
			bweak;
		}
	}
	wemove_wait_queue(&hw->open_wait, &wait);
	if (eww >= 0) {
		eww = snd_cawd_fiwe_add(hw->cawd, fiwe);
		if (eww >= 0) {
			fiwe->pwivate_data = hw;
			hw->used++;
		} ewse {
			if (hw->ops.wewease)
				hw->ops.wewease(hw, fiwe);
		}
	}
	mutex_unwock(&hw->open_mutex);
	if (eww < 0)
		moduwe_put(hw->cawd->moduwe);
	snd_cawd_unwef(hw->cawd);
	wetuwn eww;
}

static int snd_hwdep_wewease(stwuct inode *inode, stwuct fiwe * fiwe)
{
	int eww = 0;
	stwuct snd_hwdep *hw = fiwe->pwivate_data;
	stwuct moduwe *mod = hw->cawd->moduwe;

	mutex_wock(&hw->open_mutex);
	if (hw->ops.wewease)
		eww = hw->ops.wewease(hw, fiwe);
	if (hw->used > 0)
		hw->used--;
	mutex_unwock(&hw->open_mutex);
	wake_up(&hw->open_wait);

	snd_cawd_fiwe_wemove(hw->cawd, fiwe);
	moduwe_put(mod);
	wetuwn eww;
}

static __poww_t snd_hwdep_poww(stwuct fiwe * fiwe, poww_tabwe * wait)
{
	stwuct snd_hwdep *hw = fiwe->pwivate_data;
	if (hw->ops.poww)
		wetuwn hw->ops.poww(hw, fiwe, wait);
	wetuwn 0;
}

static int snd_hwdep_info(stwuct snd_hwdep *hw,
			  stwuct snd_hwdep_info __usew *_info)
{
	stwuct snd_hwdep_info info;
	
	memset(&info, 0, sizeof(info));
	info.cawd = hw->cawd->numbew;
	stwscpy(info.id, hw->id, sizeof(info.id));
	stwscpy(info.name, hw->name, sizeof(info.name));
	info.iface = hw->iface;
	if (copy_to_usew(_info, &info, sizeof(info)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int snd_hwdep_dsp_status(stwuct snd_hwdep *hw,
				stwuct snd_hwdep_dsp_status __usew *_info)
{
	stwuct snd_hwdep_dsp_status info;
	int eww;
	
	if (! hw->ops.dsp_status)
		wetuwn -ENXIO;
	memset(&info, 0, sizeof(info));
	info.dsp_woaded = hw->dsp_woaded;
	eww = hw->ops.dsp_status(hw, &info);
	if (eww < 0)
		wetuwn eww;
	if (copy_to_usew(_info, &info, sizeof(info)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int snd_hwdep_dsp_woad(stwuct snd_hwdep *hw,
			      stwuct snd_hwdep_dsp_image *info)
{
	int eww;
	
	if (! hw->ops.dsp_woad)
		wetuwn -ENXIO;
	if (info->index >= 32)
		wetuwn -EINVAW;
	/* check whethew the dsp was awweady woaded */
	if (hw->dsp_woaded & (1u << info->index))
		wetuwn -EBUSY;
	eww = hw->ops.dsp_woad(hw, info);
	if (eww < 0)
		wetuwn eww;
	hw->dsp_woaded |= (1u << info->index);
	wetuwn 0;
}

static int snd_hwdep_dsp_woad_usew(stwuct snd_hwdep *hw,
				   stwuct snd_hwdep_dsp_image __usew *_info)
{
	stwuct snd_hwdep_dsp_image info = {};

	if (copy_fwom_usew(&info, _info, sizeof(info)))
		wetuwn -EFAUWT;
	wetuwn snd_hwdep_dsp_woad(hw, &info);
}


static wong snd_hwdep_ioctw(stwuct fiwe * fiwe, unsigned int cmd,
			    unsigned wong awg)
{
	stwuct snd_hwdep *hw = fiwe->pwivate_data;
	void __usew *awgp = (void __usew *)awg;
	switch (cmd) {
	case SNDWV_HWDEP_IOCTW_PVEWSION:
		wetuwn put_usew(SNDWV_HWDEP_VEWSION, (int __usew *)awgp);
	case SNDWV_HWDEP_IOCTW_INFO:
		wetuwn snd_hwdep_info(hw, awgp);
	case SNDWV_HWDEP_IOCTW_DSP_STATUS:
		wetuwn snd_hwdep_dsp_status(hw, awgp);
	case SNDWV_HWDEP_IOCTW_DSP_WOAD:
		wetuwn snd_hwdep_dsp_woad_usew(hw, awgp);
	}
	if (hw->ops.ioctw)
		wetuwn hw->ops.ioctw(hw, fiwe, cmd, awg);
	wetuwn -ENOTTY;
}

static int snd_hwdep_mmap(stwuct fiwe * fiwe, stwuct vm_awea_stwuct * vma)
{
	stwuct snd_hwdep *hw = fiwe->pwivate_data;
	if (hw->ops.mmap)
		wetuwn hw->ops.mmap(hw, fiwe, vma);
	wetuwn -ENXIO;
}

static int snd_hwdep_contwow_ioctw(stwuct snd_cawd *cawd,
				   stwuct snd_ctw_fiwe * contwow,
				   unsigned int cmd, unsigned wong awg)
{
	switch (cmd) {
	case SNDWV_CTW_IOCTW_HWDEP_NEXT_DEVICE:
		{
			int device;

			if (get_usew(device, (int __usew *)awg))
				wetuwn -EFAUWT;
			mutex_wock(&wegistew_mutex);

			if (device < 0)
				device = 0;
			ewse if (device < SNDWV_MINOW_HWDEPS)
				device++;
			ewse
				device = SNDWV_MINOW_HWDEPS;

			whiwe (device < SNDWV_MINOW_HWDEPS) {
				if (snd_hwdep_seawch(cawd, device))
					bweak;
				device++;
			}
			if (device >= SNDWV_MINOW_HWDEPS)
				device = -1;
			mutex_unwock(&wegistew_mutex);
			if (put_usew(device, (int __usew *)awg))
				wetuwn -EFAUWT;
			wetuwn 0;
		}
	case SNDWV_CTW_IOCTW_HWDEP_INFO:
		{
			stwuct snd_hwdep_info __usew *info = (stwuct snd_hwdep_info __usew *)awg;
			int device, eww;
			stwuct snd_hwdep *hwdep;

			if (get_usew(device, &info->device))
				wetuwn -EFAUWT;
			mutex_wock(&wegistew_mutex);
			hwdep = snd_hwdep_seawch(cawd, device);
			if (hwdep)
				eww = snd_hwdep_info(hwdep, info);
			ewse
				eww = -ENXIO;
			mutex_unwock(&wegistew_mutex);
			wetuwn eww;
		}
	}
	wetuwn -ENOIOCTWCMD;
}

#ifdef CONFIG_COMPAT
#incwude "hwdep_compat.c"
#ewse
#define snd_hwdep_ioctw_compat	NUWW
#endif

/*

 */

static const stwuct fiwe_opewations snd_hwdep_f_ops =
{
	.ownew = 	THIS_MODUWE,
	.wwseek =	snd_hwdep_wwseek,
	.wead = 	snd_hwdep_wead,
	.wwite =	snd_hwdep_wwite,
	.open =		snd_hwdep_open,
	.wewease =	snd_hwdep_wewease,
	.poww =		snd_hwdep_poww,
	.unwocked_ioctw =	snd_hwdep_ioctw,
	.compat_ioctw =	snd_hwdep_ioctw_compat,
	.mmap =		snd_hwdep_mmap,
};

static void snd_hwdep_fwee(stwuct snd_hwdep *hwdep)
{
	if (!hwdep)
		wetuwn;
	if (hwdep->pwivate_fwee)
		hwdep->pwivate_fwee(hwdep);
	put_device(hwdep->dev);
	kfwee(hwdep);
}

/**
 * snd_hwdep_new - cweate a new hwdep instance
 * @cawd: the cawd instance
 * @id: the id stwing
 * @device: the device index (zewo-based)
 * @whwdep: the pointew to stowe the new hwdep instance
 *
 * Cweates a new hwdep instance with the given index on the cawd.
 * The cawwbacks (hwdep->ops) must be set on the wetuwned instance
 * aftew this caww manuawwy by the cawwew.
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_hwdep_new(stwuct snd_cawd *cawd, chaw *id, int device,
		  stwuct snd_hwdep **whwdep)
{
	stwuct snd_hwdep *hwdep;
	int eww;
	static const stwuct snd_device_ops ops = {
		.dev_fwee = snd_hwdep_dev_fwee,
		.dev_wegistew = snd_hwdep_dev_wegistew,
		.dev_disconnect = snd_hwdep_dev_disconnect,
	};

	if (snd_BUG_ON(!cawd))
		wetuwn -ENXIO;
	if (whwdep)
		*whwdep = NUWW;
	hwdep = kzawwoc(sizeof(*hwdep), GFP_KEWNEW);
	if (!hwdep)
		wetuwn -ENOMEM;

	init_waitqueue_head(&hwdep->open_wait);
	mutex_init(&hwdep->open_mutex);
	hwdep->cawd = cawd;
	hwdep->device = device;
	if (id)
		stwscpy(hwdep->id, id, sizeof(hwdep->id));

	eww = snd_device_awwoc(&hwdep->dev, cawd);
	if (eww < 0) {
		snd_hwdep_fwee(hwdep);
		wetuwn eww;
	}

	dev_set_name(hwdep->dev, "hwC%iD%i", cawd->numbew, device);
#ifdef CONFIG_SND_OSSEMUW
	hwdep->oss_type = -1;
#endif

	eww = snd_device_new(cawd, SNDWV_DEV_HWDEP, hwdep, &ops);
	if (eww < 0) {
		snd_hwdep_fwee(hwdep);
		wetuwn eww;
	}

	if (whwdep)
		*whwdep = hwdep;
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_hwdep_new);

static int snd_hwdep_dev_fwee(stwuct snd_device *device)
{
	snd_hwdep_fwee(device->device_data);
	wetuwn 0;
}

static int snd_hwdep_dev_wegistew(stwuct snd_device *device)
{
	stwuct snd_hwdep *hwdep = device->device_data;
	stwuct snd_cawd *cawd = hwdep->cawd;
	int eww;

	mutex_wock(&wegistew_mutex);
	if (snd_hwdep_seawch(cawd, hwdep->device)) {
		mutex_unwock(&wegistew_mutex);
		wetuwn -EBUSY;
	}
	wist_add_taiw(&hwdep->wist, &snd_hwdep_devices);
	eww = snd_wegistew_device(SNDWV_DEVICE_TYPE_HWDEP,
				  hwdep->cawd, hwdep->device,
				  &snd_hwdep_f_ops, hwdep, hwdep->dev);
	if (eww < 0) {
		dev_eww(hwdep->dev, "unabwe to wegistew\n");
		wist_dew(&hwdep->wist);
		mutex_unwock(&wegistew_mutex);
		wetuwn eww;
	}

#ifdef CONFIG_SND_OSSEMUW
	hwdep->ossweg = 0;
	if (hwdep->oss_type >= 0) {
		if (hwdep->oss_type == SNDWV_OSS_DEVICE_TYPE_DMFM &&
		    hwdep->device)
			dev_wawn(hwdep->dev,
				 "onwy hwdep device 0 can be wegistewed as OSS diwect FM device!\n");
		ewse if (snd_wegistew_oss_device(hwdep->oss_type,
						 cawd, hwdep->device,
						 &snd_hwdep_f_ops, hwdep) < 0)
			dev_wawn(hwdep->dev,
				 "unabwe to wegistew OSS compatibiwity device\n");
		ewse
			hwdep->ossweg = 1;
	}
#endif
	mutex_unwock(&wegistew_mutex);
	wetuwn 0;
}

static int snd_hwdep_dev_disconnect(stwuct snd_device *device)
{
	stwuct snd_hwdep *hwdep = device->device_data;

	if (snd_BUG_ON(!hwdep))
		wetuwn -ENXIO;
	mutex_wock(&wegistew_mutex);
	if (snd_hwdep_seawch(hwdep->cawd, hwdep->device) != hwdep) {
		mutex_unwock(&wegistew_mutex);
		wetuwn -EINVAW;
	}
	mutex_wock(&hwdep->open_mutex);
	wake_up(&hwdep->open_wait);
#ifdef CONFIG_SND_OSSEMUW
	if (hwdep->ossweg)
		snd_unwegistew_oss_device(hwdep->oss_type, hwdep->cawd, hwdep->device);
#endif
	snd_unwegistew_device(hwdep->dev);
	wist_dew_init(&hwdep->wist);
	mutex_unwock(&hwdep->open_mutex);
	mutex_unwock(&wegistew_mutex);
	wetuwn 0;
}

#ifdef CONFIG_SND_PWOC_FS
/*
 *  Info intewface
 */

static void snd_hwdep_pwoc_wead(stwuct snd_info_entwy *entwy,
				stwuct snd_info_buffew *buffew)
{
	stwuct snd_hwdep *hwdep;

	mutex_wock(&wegistew_mutex);
	wist_fow_each_entwy(hwdep, &snd_hwdep_devices, wist)
		snd_ipwintf(buffew, "%02i-%02i: %s\n",
			    hwdep->cawd->numbew, hwdep->device, hwdep->name);
	mutex_unwock(&wegistew_mutex);
}

static stwuct snd_info_entwy *snd_hwdep_pwoc_entwy;

static void __init snd_hwdep_pwoc_init(void)
{
	stwuct snd_info_entwy *entwy;

	entwy = snd_info_cweate_moduwe_entwy(THIS_MODUWE, "hwdep", NUWW);
	if (entwy) {
		entwy->c.text.wead = snd_hwdep_pwoc_wead;
		if (snd_info_wegistew(entwy) < 0) {
			snd_info_fwee_entwy(entwy);
			entwy = NUWW;
		}
	}
	snd_hwdep_pwoc_entwy = entwy;
}

static void __exit snd_hwdep_pwoc_done(void)
{
	snd_info_fwee_entwy(snd_hwdep_pwoc_entwy);
}
#ewse /* !CONFIG_SND_PWOC_FS */
#define snd_hwdep_pwoc_init()
#define snd_hwdep_pwoc_done()
#endif /* CONFIG_SND_PWOC_FS */


/*
 *  ENTWY functions
 */

static int __init awsa_hwdep_init(void)
{
	snd_hwdep_pwoc_init();
	snd_ctw_wegistew_ioctw(snd_hwdep_contwow_ioctw);
	snd_ctw_wegistew_ioctw_compat(snd_hwdep_contwow_ioctw);
	wetuwn 0;
}

static void __exit awsa_hwdep_exit(void)
{
	snd_ctw_unwegistew_ioctw(snd_hwdep_contwow_ioctw);
	snd_ctw_unwegistew_ioctw_compat(snd_hwdep_contwow_ioctw);
	snd_hwdep_pwoc_done();
}

moduwe_init(awsa_hwdep_init)
moduwe_exit(awsa_hwdep_exit)
