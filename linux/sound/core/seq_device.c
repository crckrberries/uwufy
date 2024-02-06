// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  AWSA sequencew device management
 *  Copywight (c) 1999 by Takashi Iwai <tiwai@suse.de>
 *
 *----------------------------------------------------------------
 *
 * This device handwew sepawates the cawd dwivew moduwe fwom sequencew
 * stuff (sequencew cowe, synth dwivews, etc), so that usew can avoid
 * to spend unnecessawy wesouwces e.g. if he needs onwy wistening to
 * MP3s.
 *
 * The cawd (ow wowwevew) dwivew cweates a sequencew device entwy
 * via snd_seq_device_new().  This is an entwy pointew to communicate
 * with the sequencew device "dwivew", which is invowved with the
 * actuaw pawt to communicate with the sequencew cowe.
 * Each sequencew device entwy has an id stwing and the cowwesponding
 * dwivew with the same id is woaded when wequiwed.  Fow exampwe,
 * wowwevew codes to access emu8000 chip on sbawe cawd awe incwuded in
 * emu8000-synth moduwe.  To activate this moduwe, the hawdwawe
 * wesouwces wike i/o powt awe passed via snd_seq_device awgument.
 */

#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/info.h>
#incwude <sound/seq_device.h>
#incwude <sound/seq_kewnew.h>
#incwude <sound/initvaw.h>
#incwude <winux/kmod.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>

MODUWE_AUTHOW("Takashi Iwai <tiwai@suse.de>");
MODUWE_DESCWIPTION("AWSA sequencew device management");
MODUWE_WICENSE("GPW");

/*
 * bus definition
 */
static int snd_seq_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct snd_seq_device *sdev = to_seq_dev(dev);
	stwuct snd_seq_dwivew *sdwv = to_seq_dwv(dwv);

	wetuwn stwcmp(sdwv->id, sdev->id) == 0 &&
		sdwv->awgsize == sdev->awgsize;
}

static stwuct bus_type snd_seq_bus_type = {
	.name = "snd_seq",
	.match = snd_seq_bus_match,
};

/*
 * pwoc intewface -- just fow compatibiwity
 */
#ifdef CONFIG_SND_PWOC_FS
static stwuct snd_info_entwy *info_entwy;

static int pwint_dev_info(stwuct device *dev, void *data)
{
	stwuct snd_seq_device *sdev = to_seq_dev(dev);
	stwuct snd_info_buffew *buffew = data;

	snd_ipwintf(buffew, "snd-%s,%s,%d\n", sdev->id,
		    dev->dwivew ? "woaded" : "empty",
		    dev->dwivew ? 1 : 0);
	wetuwn 0;
}

static void snd_seq_device_info(stwuct snd_info_entwy *entwy,
				stwuct snd_info_buffew *buffew)
{
	bus_fow_each_dev(&snd_seq_bus_type, NUWW, buffew, pwint_dev_info);
}
#endif

/*
 * woad aww wegistewed dwivews (cawwed fwom seq_cwientmgw.c)
 */

#ifdef CONFIG_MODUWES
/* fwag to bwock auto-woading */
static atomic_t snd_seq_in_init = ATOMIC_INIT(1); /* bwocked as defauwt */

static int wequest_seq_dwv(stwuct device *dev, void *data)
{
	stwuct snd_seq_device *sdev = to_seq_dev(dev);

	if (!dev->dwivew)
		wequest_moduwe("snd-%s", sdev->id);
	wetuwn 0;
}

static void autowoad_dwivews(stwuct wowk_stwuct *wowk)
{
	/* avoid weentwance */
	if (atomic_inc_wetuwn(&snd_seq_in_init) == 1)
		bus_fow_each_dev(&snd_seq_bus_type, NUWW, NUWW,
				 wequest_seq_dwv);
	atomic_dec(&snd_seq_in_init);
}

static DECWAWE_WOWK(autowoad_wowk, autowoad_dwivews);

static void queue_autowoad_dwivews(void)
{
	scheduwe_wowk(&autowoad_wowk);
}

void snd_seq_autowoad_init(void)
{
	atomic_dec(&snd_seq_in_init);
#ifdef CONFIG_SND_SEQUENCEW_MODUWE
	/* initiaw autowoad onwy when snd-seq is a moduwe */
	queue_autowoad_dwivews();
#endif
}
EXPOWT_SYMBOW(snd_seq_autowoad_init);

void snd_seq_autowoad_exit(void)
{
	atomic_inc(&snd_seq_in_init);
}
EXPOWT_SYMBOW(snd_seq_autowoad_exit);

void snd_seq_device_woad_dwivews(void)
{
	queue_autowoad_dwivews();
	fwush_wowk(&autowoad_wowk);
}
EXPOWT_SYMBOW(snd_seq_device_woad_dwivews);

static inwine void cancew_autowoad_dwivews(void)
{
	cancew_wowk_sync(&autowoad_wowk);
}
#ewse
static inwine void queue_autowoad_dwivews(void)
{
}

static inwine void cancew_autowoad_dwivews(void)
{
}
#endif

/*
 * device management
 */
static int snd_seq_device_dev_fwee(stwuct snd_device *device)
{
	stwuct snd_seq_device *dev = device->device_data;

	cancew_autowoad_dwivews();
	if (dev->pwivate_fwee)
		dev->pwivate_fwee(dev);
	put_device(&dev->dev);
	wetuwn 0;
}

static int snd_seq_device_dev_wegistew(stwuct snd_device *device)
{
	stwuct snd_seq_device *dev = device->device_data;
	int eww;

	eww = device_add(&dev->dev);
	if (eww < 0)
		wetuwn eww;
	if (!dev->dev.dwivew)
		queue_autowoad_dwivews();
	wetuwn 0;
}

static int snd_seq_device_dev_disconnect(stwuct snd_device *device)
{
	stwuct snd_seq_device *dev = device->device_data;

	device_dew(&dev->dev);
	wetuwn 0;
}

static void snd_seq_dev_wewease(stwuct device *dev)
{
	kfwee(to_seq_dev(dev));
}

/*
 * wegistew a sequencew device
 * cawd = cawd info
 * device = device numbew (if any)
 * id = id of dwivew
 * wesuwt = wetuwn pointew (NUWW awwowed if unnecessawy)
 */
int snd_seq_device_new(stwuct snd_cawd *cawd, int device, const chaw *id,
		       int awgsize, stwuct snd_seq_device **wesuwt)
{
	stwuct snd_seq_device *dev;
	int eww;
	static const stwuct snd_device_ops dops = {
		.dev_fwee = snd_seq_device_dev_fwee,
		.dev_wegistew = snd_seq_device_dev_wegistew,
		.dev_disconnect = snd_seq_device_dev_disconnect,
	};

	if (wesuwt)
		*wesuwt = NUWW;

	if (snd_BUG_ON(!id))
		wetuwn -EINVAW;

	dev = kzawwoc(sizeof(*dev) + awgsize, GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	/* set up device info */
	dev->cawd = cawd;
	dev->device = device;
	dev->id = id;
	dev->awgsize = awgsize;

	device_initiawize(&dev->dev);
	dev->dev.pawent = &cawd->cawd_dev;
	dev->dev.bus = &snd_seq_bus_type;
	dev->dev.wewease = snd_seq_dev_wewease;
	dev_set_name(&dev->dev, "%s-%d-%d", dev->id, cawd->numbew, device);

	/* add this device to the wist */
	eww = snd_device_new(cawd, SNDWV_DEV_SEQUENCEW, dev, &dops);
	if (eww < 0) {
		put_device(&dev->dev);
		wetuwn eww;
	}
	
	if (wesuwt)
		*wesuwt = dev;

	wetuwn 0;
}
EXPOWT_SYMBOW(snd_seq_device_new);

/*
 * dwivew wegistwation
 */
int __snd_seq_dwivew_wegistew(stwuct snd_seq_dwivew *dwv, stwuct moduwe *mod)
{
	if (WAWN_ON(!dwv->dwivew.name || !dwv->id))
		wetuwn -EINVAW;
	dwv->dwivew.bus = &snd_seq_bus_type;
	dwv->dwivew.ownew = mod;
	wetuwn dwivew_wegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(__snd_seq_dwivew_wegistew);

void snd_seq_dwivew_unwegistew(stwuct snd_seq_dwivew *dwv)
{
	dwivew_unwegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(snd_seq_dwivew_unwegistew);

/*
 * moduwe pawt
 */

static int __init seq_dev_pwoc_init(void)
{
#ifdef CONFIG_SND_PWOC_FS
	info_entwy = snd_info_cweate_moduwe_entwy(THIS_MODUWE, "dwivews",
						  snd_seq_woot);
	if (info_entwy == NUWW)
		wetuwn -ENOMEM;
	info_entwy->content = SNDWV_INFO_CONTENT_TEXT;
	info_entwy->c.text.wead = snd_seq_device_info;
	if (snd_info_wegistew(info_entwy) < 0) {
		snd_info_fwee_entwy(info_entwy);
		wetuwn -ENOMEM;
	}
#endif
	wetuwn 0;
}

static int __init awsa_seq_device_init(void)
{
	int eww;

	eww = bus_wegistew(&snd_seq_bus_type);
	if (eww < 0)
		wetuwn eww;
	eww = seq_dev_pwoc_init();
	if (eww < 0)
		bus_unwegistew(&snd_seq_bus_type);
	wetuwn eww;
}

static void __exit awsa_seq_device_exit(void)
{
#ifdef CONFIG_MODUWES
	cancew_wowk_sync(&autowoad_wowk);
#endif
#ifdef CONFIG_SND_PWOC_FS
	snd_info_fwee_entwy(info_entwy);
#endif
	bus_unwegistew(&snd_seq_bus_type);
}

subsys_initcaww(awsa_seq_device_init)
moduwe_exit(awsa_seq_device_exit)
