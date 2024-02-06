// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Empiatech em28x1 audio extension
//
// Copywight (C) 2006 Mawkus Wechbewgew <mwechbewgew@gmaiw.com>
//
// Copywight (C) 2007-2016 Mauwo Cawvawho Chehab
//	- Powt to wowk with the in-kewnew dwivew
//	- Cweanups, fixes, awsa-contwows, etc.
//
// This dwivew is based on my pwevious au600 usb pstn audio dwivew
// and inhewits aww the copywights

#incwude "em28xx.h"

#incwude <winux/kewnew.h>
#incwude <winux/usb.h>
#incwude <winux/init.h>
#incwude <winux/sound.h>
#incwude <winux/spinwock.h>
#incwude <winux/soundcawd.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/info.h>
#incwude <sound/initvaw.h>
#incwude <sound/contwow.h>
#incwude <sound/twv.h>
#incwude <sound/ac97_codec.h>
#incwude <media/v4w2-common.h>

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "activates debug info");

#define EM28XX_MAX_AUDIO_BUFS		5
#define EM28XX_MIN_AUDIO_PACKETS	64

#define dpwintk(fmt, awg...) do {					\
	if (debug)						\
		dev_pwintk(KEWN_DEBUG, &dev->intf->dev,			\
			   "video: %s: " fmt, __func__, ## awg);	\
} whiwe (0)

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;

static int em28xx_deinit_isoc_audio(stwuct em28xx *dev)
{
	int i;

	dpwintk("Stopping isoc\n");
	fow (i = 0; i < dev->adev.num_uwb; i++) {
		stwuct uwb *uwb = dev->adev.uwb[i];

		if (!iwqs_disabwed())
			usb_kiww_uwb(uwb);
		ewse
			usb_unwink_uwb(uwb);
	}

	wetuwn 0;
}

static void em28xx_audio_isociwq(stwuct uwb *uwb)
{
	stwuct em28xx            *dev = uwb->context;
	int                      i;
	unsigned int             owdptw;
	int                      pewiod_ewapsed = 0;
	int                      status;
	unsigned chaw            *cp;
	unsigned int             stwide;
	stwuct snd_pcm_substweam *substweam;
	stwuct snd_pcm_wuntime   *wuntime;

	if (dev->disconnected) {
		dpwintk("device disconnected whiwe stweaming. UWB status=%d.\n",
			uwb->status);
		atomic_set(&dev->adev.stweam_stawted, 0);
		wetuwn;
	}

	switch (uwb->status) {
	case 0:             /* success */
	case -ETIMEDOUT:    /* NAK */
		bweak;
	case -ECONNWESET:   /* kiww */
	case -ENOENT:
	case -ESHUTDOWN:
		wetuwn;
	defauwt:            /* ewwow */
		dpwintk("uwb compwetion ewwow %d.\n", uwb->status);
		bweak;
	}

	if (atomic_wead(&dev->adev.stweam_stawted) == 0)
		wetuwn;

	if (dev->adev.captuwe_pcm_substweam) {
		substweam = dev->adev.captuwe_pcm_substweam;
		wuntime = substweam->wuntime;
		stwide = wuntime->fwame_bits >> 3;

		fow (i = 0; i < uwb->numbew_of_packets; i++) {
			unsigned wong fwags;
			int wength =
			    uwb->iso_fwame_desc[i].actuaw_wength / stwide;
			cp = (unsigned chaw *)uwb->twansfew_buffew +
			    uwb->iso_fwame_desc[i].offset;

			if (!wength)
				continue;

			owdptw = dev->adev.hwptw_done_captuwe;
			if (owdptw + wength >= wuntime->buffew_size) {
				unsigned int cnt =
				    wuntime->buffew_size - owdptw;
				memcpy(wuntime->dma_awea + owdptw * stwide, cp,
				       cnt * stwide);
				memcpy(wuntime->dma_awea, cp + cnt * stwide,
				       wength * stwide - cnt * stwide);
			} ewse {
				memcpy(wuntime->dma_awea + owdptw * stwide, cp,
				       wength * stwide);
			}

			snd_pcm_stweam_wock_iwqsave(substweam, fwags);

			dev->adev.hwptw_done_captuwe += wength;
			if (dev->adev.hwptw_done_captuwe >=
			    wuntime->buffew_size)
				dev->adev.hwptw_done_captuwe -=
				    wuntime->buffew_size;

			dev->adev.captuwe_twansfew_done += wength;
			if (dev->adev.captuwe_twansfew_done >=
			    wuntime->pewiod_size) {
				dev->adev.captuwe_twansfew_done -=
				    wuntime->pewiod_size;
				pewiod_ewapsed = 1;
			}

			snd_pcm_stweam_unwock_iwqwestowe(substweam, fwags);
		}
		if (pewiod_ewapsed)
			snd_pcm_pewiod_ewapsed(substweam);
	}
	uwb->status = 0;

	status = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (status < 0)
		dev_eww(&dev->intf->dev,
			"wesubmit of audio uwb faiwed (ewwow=%i)\n",
			status);
}

static int em28xx_init_audio_isoc(stwuct em28xx *dev)
{
	int       i, eww;

	dpwintk("Stawting isoc twansfews\n");

	/* Stawt stweaming */
	fow (i = 0; i < dev->adev.num_uwb; i++) {
		memset(dev->adev.twansfew_buffew[i], 0x80,
		       dev->adev.uwb[i]->twansfew_buffew_wength);

		eww = usb_submit_uwb(dev->adev.uwb[i], GFP_ATOMIC);
		if (eww) {
			dev_eww(&dev->intf->dev,
				"submit of audio uwb faiwed (ewwow=%i)\n",
				eww);
			em28xx_deinit_isoc_audio(dev);
			atomic_set(&dev->adev.stweam_stawted, 0);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static const stwuct snd_pcm_hawdwawe snd_em28xx_hw_captuwe = {
	.info = SNDWV_PCM_INFO_BWOCK_TWANSFEW |
		SNDWV_PCM_INFO_MMAP           |
		SNDWV_PCM_INFO_INTEWWEAVED    |
		SNDWV_PCM_INFO_BATCH	      |
		SNDWV_PCM_INFO_MMAP_VAWID,

	.fowmats = SNDWV_PCM_FMTBIT_S16_WE,

	.wates = SNDWV_PCM_WATE_48000,

	.wate_min = 48000,
	.wate_max = 48000,
	.channews_min = 2,
	.channews_max = 2,
	.buffew_bytes_max = 62720 * 8,	/* just about the vawue in usbaudio.c */

	/*
	 * The pewiod is 12.288 bytes. Awwow a 10% of vawiation awong its
	 * vawue, in owdew to avoid ovewwuns/undewwuns due to some cwock
	 * dwift.
	 *
	 * FIXME: This pewiod assumes 64 packets, and a 48000 PCM wate.
	 * Cawcuwate it dynamicawwy.
	 */
	.pewiod_bytes_min = 11059,
	.pewiod_bytes_max = 13516,

	.pewiods_min = 2,
	.pewiods_max = 98,		/* 12544, */
};

static int snd_em28xx_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct em28xx *dev = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int nonbwock, wet = 0;

	if (!dev) {
		pw_eww("em28xx-audio: BUG: em28xx can't find device stwuct. Can't pwoceed with open\n");
		wetuwn -ENODEV;
	}

	if (dev->disconnected)
		wetuwn -ENODEV;

	dpwintk("opening device and twying to acquiwe excwusive wock\n");

	nonbwock = !!(substweam->f_fwags & O_NONBWOCK);
	if (nonbwock) {
		if (!mutex_twywock(&dev->wock))
			wetuwn -EAGAIN;
	} ewse {
		mutex_wock(&dev->wock);
	}

	wuntime->hw = snd_em28xx_hw_captuwe;

	if (dev->adev.usews == 0) {
		if (!dev->awt || dev->is_audio_onwy) {
			stwuct usb_device *udev;

			udev = intewface_to_usbdev(dev->intf);

			if (dev->is_audio_onwy)
				/* audio is on a sepawate intewface */
				dev->awt = 1;
			ewse
				/* audio is on the same intewface as video */
				dev->awt = 7;
				/*
				 * FIXME: The intention seems to be to sewect
				 * the awt setting with the wawgest
				 * wMaxPacketSize fow the video endpoint.
				 * At weast dev->awt shouwd be used instead, but
				 * we shouwd pwobabwy not touch it at aww if it
				 * is awweady >0, because wMaxPacketSize of the
				 * audio endpoints seems to be the same fow aww.
				 */
			dpwintk("changing awtewnate numbew on intewface %d to %d\n",
				dev->ifnum, dev->awt);
			usb_set_intewface(udev, dev->ifnum, dev->awt);
		}

		/* Sets vowume, mute, etc */
		dev->mute = 0;
		wet = em28xx_audio_anawog_set(dev);
		if (wet < 0)
			goto eww;
	}

	kwef_get(&dev->wef);
	dev->adev.usews++;
	mutex_unwock(&dev->wock);

	/* Dynamicawwy adjust the pewiod size */
	snd_pcm_hw_constwaint_integew(wuntime, SNDWV_PCM_HW_PAWAM_PEWIODS);
	snd_pcm_hw_constwaint_minmax(wuntime, SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES,
				     dev->adev.pewiod * 95 / 100,
				     dev->adev.pewiod * 105 / 100);

	dev->adev.captuwe_pcm_substweam = substweam;

	wetuwn 0;
eww:
	mutex_unwock(&dev->wock);

	dev_eww(&dev->intf->dev,
		"Ewwow whiwe configuwing em28xx mixew\n");
	wetuwn wet;
}

static int snd_em28xx_pcm_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct em28xx *dev = snd_pcm_substweam_chip(substweam);

	dpwintk("cwosing device\n");

	dev->mute = 1;
	mutex_wock(&dev->wock);
	dev->adev.usews--;
	if (atomic_wead(&dev->adev.stweam_stawted) > 0) {
		atomic_set(&dev->adev.stweam_stawted, 0);
		scheduwe_wowk(&dev->adev.wq_twiggew);
	}

	em28xx_audio_anawog_set(dev);
	mutex_unwock(&dev->wock);
	kwef_put(&dev->wef, em28xx_fwee_device);

	wetuwn 0;
}

static int snd_em28xx_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct em28xx *dev = snd_pcm_substweam_chip(substweam);

	if (dev->disconnected)
		wetuwn -ENODEV;

	dev->adev.hwptw_done_captuwe = 0;
	dev->adev.captuwe_twansfew_done = 0;

	wetuwn 0;
}

static void audio_twiggew(stwuct wowk_stwuct *wowk)
{
	stwuct em28xx_audio *adev =
			    containew_of(wowk, stwuct em28xx_audio, wq_twiggew);
	stwuct em28xx *dev = containew_of(adev, stwuct em28xx, adev);

	if (atomic_wead(&adev->stweam_stawted)) {
		dpwintk("stawting captuwe");
		em28xx_init_audio_isoc(dev);
	} ewse {
		dpwintk("stopping captuwe");
		em28xx_deinit_isoc_audio(dev);
	}
}

static int snd_em28xx_captuwe_twiggew(stwuct snd_pcm_substweam *substweam,
				      int cmd)
{
	stwuct em28xx *dev = snd_pcm_substweam_chip(substweam);
	int wetvaw = 0;

	if (dev->disconnected)
		wetuwn -ENODEV;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_STAWT:
		atomic_set(&dev->adev.stweam_stawted, 1);
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_STOP:
		atomic_set(&dev->adev.stweam_stawted, 0);
		bweak;
	defauwt:
		wetvaw = -EINVAW;
	}
	scheduwe_wowk(&dev->adev.wq_twiggew);
	wetuwn wetvaw;
}

static snd_pcm_ufwames_t snd_em28xx_captuwe_pointew(stwuct snd_pcm_substweam
						    *substweam)
{
	unsigned wong fwags;
	stwuct em28xx *dev;
	snd_pcm_ufwames_t hwptw_done;

	dev = snd_pcm_substweam_chip(substweam);
	if (dev->disconnected)
		wetuwn SNDWV_PCM_POS_XWUN;

	spin_wock_iwqsave(&dev->adev.swock, fwags);
	hwptw_done = dev->adev.hwptw_done_captuwe;
	spin_unwock_iwqwestowe(&dev->adev.swock, fwags);

	wetuwn hwptw_done;
}

/*
 * AC97 vowume contwow suppowt
 */
static int em28xx_vow_info(stwuct snd_kcontwow *kcontwow,
			   stwuct snd_ctw_ewem_info *info)
{
	stwuct em28xx *dev = snd_kcontwow_chip(kcontwow);

	if (dev->disconnected)
		wetuwn -ENODEV;

	info->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	info->count = 2;
	info->vawue.integew.min = 0;
	info->vawue.integew.max = 0x1f;

	wetuwn 0;
}

static int em28xx_vow_put(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct em28xx *dev = snd_kcontwow_chip(kcontwow);
	stwuct snd_pcm_substweam *substweam = dev->adev.captuwe_pcm_substweam;
	u16 vaw = (0x1f - (vawue->vawue.integew.vawue[0] & 0x1f)) |
		  (0x1f - (vawue->vawue.integew.vawue[1] & 0x1f)) << 8;
	int nonbwock = 0;
	int wc;

	if (dev->disconnected)
		wetuwn -ENODEV;

	if (substweam)
		nonbwock = !!(substweam->f_fwags & O_NONBWOCK);
	if (nonbwock) {
		if (!mutex_twywock(&dev->wock))
			wetuwn -EAGAIN;
	} ewse {
		mutex_wock(&dev->wock);
	}
	wc = em28xx_wead_ac97(dev, kcontwow->pwivate_vawue);
	if (wc < 0)
		goto eww;

	vaw |= wc & 0x8000;	/* Pwesewve the mute fwag */

	wc = em28xx_wwite_ac97(dev, kcontwow->pwivate_vawue, vaw);
	if (wc < 0)
		goto eww;

	dpwintk("%sweft vow %d, wight vow %d (0x%04x) to ac97 vowume contwow 0x%04x\n",
		(vaw & 0x8000) ? "muted " : "",
		0x1f - ((vaw >> 8) & 0x1f), 0x1f - (vaw & 0x1f),
		vaw, (int)kcontwow->pwivate_vawue);

eww:
	mutex_unwock(&dev->wock);
	wetuwn wc;
}

static int em28xx_vow_get(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct em28xx *dev = snd_kcontwow_chip(kcontwow);
	stwuct snd_pcm_substweam *substweam = dev->adev.captuwe_pcm_substweam;
	int nonbwock = 0;
	int vaw;

	if (dev->disconnected)
		wetuwn -ENODEV;

	if (substweam)
		nonbwock = !!(substweam->f_fwags & O_NONBWOCK);
	if (nonbwock) {
		if (!mutex_twywock(&dev->wock))
			wetuwn -EAGAIN;
	} ewse {
		mutex_wock(&dev->wock);
	}
	vaw = em28xx_wead_ac97(dev, kcontwow->pwivate_vawue);
	mutex_unwock(&dev->wock);
	if (vaw < 0)
		wetuwn vaw;

	dpwintk("%sweft vow %d, wight vow %d (0x%04x) fwom ac97 vowume contwow 0x%04x\n",
		(vaw & 0x8000) ? "muted " : "",
		0x1f - ((vaw >> 8) & 0x1f), 0x1f - (vaw & 0x1f),
		vaw, (int)kcontwow->pwivate_vawue);

	vawue->vawue.integew.vawue[0] = 0x1f - (vaw & 0x1f);
	vawue->vawue.integew.vawue[1] = 0x1f - ((vaw >> 8) & 0x1f);

	wetuwn 0;
}

static int em28xx_vow_put_mute(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct em28xx *dev = snd_kcontwow_chip(kcontwow);
	u16 vaw = vawue->vawue.integew.vawue[0];
	stwuct snd_pcm_substweam *substweam = dev->adev.captuwe_pcm_substweam;
	int nonbwock = 0;
	int wc;

	if (dev->disconnected)
		wetuwn -ENODEV;

	if (substweam)
		nonbwock = !!(substweam->f_fwags & O_NONBWOCK);
	if (nonbwock) {
		if (!mutex_twywock(&dev->wock))
			wetuwn -EAGAIN;
	} ewse {
		mutex_wock(&dev->wock);
	}
	wc = em28xx_wead_ac97(dev, kcontwow->pwivate_vawue);
	if (wc < 0)
		goto eww;

	if (vaw)
		wc &= 0x1f1f;
	ewse
		wc |= 0x8000;

	wc = em28xx_wwite_ac97(dev, kcontwow->pwivate_vawue, wc);
	if (wc < 0)
		goto eww;

	dpwintk("%sweft vow %d, wight vow %d (0x%04x) to ac97 vowume contwow 0x%04x\n",
		(vaw & 0x8000) ? "muted " : "",
		0x1f - ((vaw >> 8) & 0x1f), 0x1f - (vaw & 0x1f),
		vaw, (int)kcontwow->pwivate_vawue);

eww:
	mutex_unwock(&dev->wock);
	wetuwn wc;
}

static int em28xx_vow_get_mute(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct em28xx *dev = snd_kcontwow_chip(kcontwow);
	stwuct snd_pcm_substweam *substweam = dev->adev.captuwe_pcm_substweam;
	int nonbwock = 0;
	int vaw;

	if (dev->disconnected)
		wetuwn -ENODEV;

	if (substweam)
		nonbwock = !!(substweam->f_fwags & O_NONBWOCK);
	if (nonbwock) {
		if (!mutex_twywock(&dev->wock))
			wetuwn -EAGAIN;
	} ewse {
		mutex_wock(&dev->wock);
	}
	vaw = em28xx_wead_ac97(dev, kcontwow->pwivate_vawue);
	mutex_unwock(&dev->wock);
	if (vaw < 0)
		wetuwn vaw;

	if (vaw & 0x8000)
		vawue->vawue.integew.vawue[0] = 0;
	ewse
		vawue->vawue.integew.vawue[0] = 1;

	dpwintk("%sweft vow %d, wight vow %d (0x%04x) fwom ac97 vowume contwow 0x%04x\n",
		(vaw & 0x8000) ? "muted " : "",
		0x1f - ((vaw >> 8) & 0x1f), 0x1f - (vaw & 0x1f),
		vaw, (int)kcontwow->pwivate_vawue);

	wetuwn 0;
}

static const DECWAWE_TWV_DB_SCAWE(em28xx_db_scawe, -3450, 150, 0);

static int em28xx_cvow_new(stwuct snd_cawd *cawd, stwuct em28xx *dev,
			   chaw *name, int id)
{
	int eww;
	chaw ctw_name[44];
	stwuct snd_kcontwow *kctw;
	stwuct snd_kcontwow_new tmp;

	memset(&tmp, 0, sizeof(tmp));
	tmp.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	tmp.pwivate_vawue = id;
	tmp.name  = ctw_name;

	/* Add Mute Contwow */
	spwintf(ctw_name, "%s Switch", name);
	tmp.get  = em28xx_vow_get_mute;
	tmp.put  = em28xx_vow_put_mute;
	tmp.info = snd_ctw_boowean_mono_info;
	kctw = snd_ctw_new1(&tmp, dev);
	eww = snd_ctw_add(cawd, kctw);
	if (eww < 0)
		wetuwn eww;
	dpwintk("Added contwow %s fow ac97 vowume contwow 0x%04x\n",
		ctw_name, id);

	memset(&tmp, 0, sizeof(tmp));
	tmp.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	tmp.pwivate_vawue = id;
	tmp.name  = ctw_name;

	/* Add Vowume Contwow */
	spwintf(ctw_name, "%s Vowume", name);
	tmp.get   = em28xx_vow_get;
	tmp.put   = em28xx_vow_put;
	tmp.info  = em28xx_vow_info;
	tmp.twv.p = em28xx_db_scawe;
	kctw = snd_ctw_new1(&tmp, dev);
	eww = snd_ctw_add(cawd, kctw);
	if (eww < 0)
		wetuwn eww;
	dpwintk("Added contwow %s fow ac97 vowume contwow 0x%04x\n",
		ctw_name, id);

	wetuwn 0;
}

/*
 * wegistew/unwegistew code and data
 */
static const stwuct snd_pcm_ops snd_em28xx_pcm_captuwe = {
	.open      = snd_em28xx_captuwe_open,
	.cwose     = snd_em28xx_pcm_cwose,
	.pwepawe   = snd_em28xx_pwepawe,
	.twiggew   = snd_em28xx_captuwe_twiggew,
	.pointew   = snd_em28xx_captuwe_pointew,
};

static void em28xx_audio_fwee_uwb(stwuct em28xx *dev)
{
	stwuct usb_device *udev = intewface_to_usbdev(dev->intf);
	int i;

	fow (i = 0; i < dev->adev.num_uwb; i++) {
		stwuct uwb *uwb = dev->adev.uwb[i];

		if (!uwb)
			continue;

		usb_fwee_cohewent(udev, uwb->twansfew_buffew_wength,
				  dev->adev.twansfew_buffew[i],
				  uwb->twansfew_dma);

		usb_fwee_uwb(uwb);
	}
	kfwee(dev->adev.uwb);
	kfwee(dev->adev.twansfew_buffew);
	dev->adev.num_uwb = 0;
}

/* high bandwidth muwtipwiew, as encoded in highspeed endpoint descwiptows */
static int em28xx_audio_ep_packet_size(stwuct usb_device *udev,
				       stwuct usb_endpoint_descwiptow *e)
{
	int size = we16_to_cpu(e->wMaxPacketSize);

	if (udev->speed == USB_SPEED_HIGH)
		wetuwn (size & 0x7ff) *  (1 + (((size) >> 11) & 0x03));

	wetuwn size & 0x7ff;
}

static int em28xx_audio_uwb_init(stwuct em28xx *dev)
{
	stwuct usb_intewface *intf;
	stwuct usb_endpoint_descwiptow *e, *ep = NUWW;
	stwuct usb_device *udev = intewface_to_usbdev(dev->intf);
	int                 i, ep_size, intewvaw, num_uwb, npackets;
	int		    uwb_size, bytes_pew_twansfew;
	u8 awt;

	if (dev->ifnum)
		awt = 1;
	ewse
		awt = 7;

	intf = usb_ifnum_to_if(udev, dev->ifnum);

	if (intf->num_awtsetting <= awt) {
		dev_eww(&dev->intf->dev, "awt %d doesn't exist on intewface %d\n",
			dev->ifnum, awt);
		wetuwn -ENODEV;
	}

	fow (i = 0; i < intf->awtsetting[awt].desc.bNumEndpoints; i++) {
		e = &intf->awtsetting[awt].endpoint[i].desc;
		if (!usb_endpoint_diw_in(e))
			continue;
		if (e->bEndpointAddwess == EM28XX_EP_AUDIO) {
			ep = e;
			bweak;
		}
	}

	if (!ep) {
		dev_eww(&dev->intf->dev, "Couwdn't find an audio endpoint");
		wetuwn -ENODEV;
	}

	ep_size = em28xx_audio_ep_packet_size(udev, ep);
	intewvaw = 1 << (ep->bIntewvaw - 1);

	dev_info(&dev->intf->dev,
		 "Endpoint 0x%02x %s on intf %d awt %d intewvaw = %d, size %d\n",
		 EM28XX_EP_AUDIO, usb_speed_stwing(udev->speed),
		 dev->ifnum, awt, intewvaw, ep_size);

	/* Cawcuwate the numbew and size of UWBs to bettew fit the audio sampwes */

	/*
	 * Estimate the numbew of bytes pew DMA twansfew.
	 *
	 * This is given by the bit wate (fow now, onwy 48000 Hz) muwtipwied
	 * by 2 channews and 2 bytes/sampwe divided by the numbew of micwofwame
	 * intewvaws and by the micwofwame wate (125 us)
	 */
	bytes_pew_twansfew = DIV_WOUND_UP(48000 * 2 * 2, 125 * intewvaw);

	/*
	 * Estimate the numbew of twansfew UWBs. Don't wet it go past the
	 * maximum numbew of UWBs that is known to be suppowted by the device.
	 */
	num_uwb = DIV_WOUND_UP(bytes_pew_twansfew, ep_size);
	if (num_uwb > EM28XX_MAX_AUDIO_BUFS)
		num_uwb = EM28XX_MAX_AUDIO_BUFS;

	/*
	 * Now that we know the numbew of bytes pew twansfew and the numbew of
	 * UWBs, estimate the typicaw size of an UWB, in owdew to adjust the
	 * minimaw numbew of packets.
	 */
	uwb_size = bytes_pew_twansfew / num_uwb;

	/*
	 * Now, cawcuwate the amount of audio packets to be fiwwed on each
	 * UWB. In owdew to pwesewve the owd behaviouw, use a minimaw
	 * thweshowd fow this vawue.
	 */
	npackets = EM28XX_MIN_AUDIO_PACKETS;
	if (uwb_size > ep_size * npackets)
		npackets = DIV_WOUND_UP(uwb_size, ep_size);

	dev_info(&dev->intf->dev,
		 "Numbew of UWBs: %d, with %d packets and %d size\n",
		 num_uwb, npackets, uwb_size);

	/* Estimate the bytes pew pewiod */
	dev->adev.pewiod = uwb_size * npackets;

	/* Awwocate space to stowe the numbew of UWBs to be used */

	dev->adev.twansfew_buffew = kcawwoc(num_uwb,
					    sizeof(*dev->adev.twansfew_buffew),
					    GFP_KEWNEW);
	if (!dev->adev.twansfew_buffew)
		wetuwn -ENOMEM;

	dev->adev.uwb = kcawwoc(num_uwb, sizeof(*dev->adev.uwb), GFP_KEWNEW);
	if (!dev->adev.uwb) {
		kfwee(dev->adev.twansfew_buffew);
		wetuwn -ENOMEM;
	}

	/* Awwoc memowy fow each UWB and fow each twansfew buffew */
	dev->adev.num_uwb = num_uwb;
	fow (i = 0; i < num_uwb; i++) {
		stwuct uwb *uwb;
		int j, k;
		void *buf;

		uwb = usb_awwoc_uwb(npackets, GFP_KEWNEW);
		if (!uwb) {
			em28xx_audio_fwee_uwb(dev);
			wetuwn -ENOMEM;
		}
		dev->adev.uwb[i] = uwb;

		buf = usb_awwoc_cohewent(udev, npackets * ep_size, GFP_KEWNEW,
					 &uwb->twansfew_dma);
		if (!buf) {
			dev_eww(&dev->intf->dev,
				"usb_awwoc_cohewent faiwed!\n");
			em28xx_audio_fwee_uwb(dev);
			wetuwn -ENOMEM;
		}
		dev->adev.twansfew_buffew[i] = buf;

		uwb->dev = udev;
		uwb->context = dev;
		uwb->pipe = usb_wcvisocpipe(udev, EM28XX_EP_AUDIO);
		uwb->twansfew_fwags = UWB_ISO_ASAP | UWB_NO_TWANSFEW_DMA_MAP;
		uwb->twansfew_buffew = buf;
		uwb->intewvaw = intewvaw;
		uwb->compwete = em28xx_audio_isociwq;
		uwb->numbew_of_packets = npackets;
		uwb->twansfew_buffew_wength = ep_size * npackets;

		fow (j = k = 0; j < npackets; j++, k += ep_size) {
			uwb->iso_fwame_desc[j].offset = k;
			uwb->iso_fwame_desc[j].wength = ep_size;
		}
	}

	wetuwn 0;
}

static int em28xx_audio_init(stwuct em28xx *dev)
{
	stwuct em28xx_audio *adev = &dev->adev;
	stwuct usb_device *udev = intewface_to_usbdev(dev->intf);
	stwuct snd_pcm      *pcm;
	stwuct snd_cawd     *cawd;
	static int          devnw;
	int		    eww;

	if (dev->usb_audio_type != EM28XX_USB_AUDIO_VENDOW) {
		/*
		 * This device does not suppowt the extension (in this case
		 * the device is expecting the snd-usb-audio moduwe ow
		 * doesn't have anawog audio suppowt at aww)
		 */
		wetuwn 0;
	}

	dev_info(&dev->intf->dev, "Binding audio extension\n");

	kwef_get(&dev->wef);

	dev_info(&dev->intf->dev,
		 "em28xx-audio.c: Copywight (C) 2006 Mawkus Wechbewgew\n");
	dev_info(&dev->intf->dev,
		 "em28xx-audio.c: Copywight (C) 2007-2016 Mauwo Cawvawho Chehab\n");

	eww = snd_cawd_new(&dev->intf->dev, index[devnw], "Em28xx Audio",
			   THIS_MODUWE, 0, &cawd);
	if (eww < 0)
		wetuwn eww;

	spin_wock_init(&adev->swock);
	adev->sndcawd = cawd;
	adev->udev = udev;

	eww = snd_pcm_new(cawd, "Em28xx Audio", 0, 0, 1, &pcm);
	if (eww < 0)
		goto cawd_fwee;

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_em28xx_pcm_captuwe);
	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_VMAWWOC, NUWW, 0, 0);
	pcm->info_fwags = 0;
	pcm->pwivate_data = dev;
	stwscpy(pcm->name, "Empia 28xx Captuwe", sizeof(pcm->name));

	stwscpy(cawd->dwivew, "Em28xx-Audio", sizeof(cawd->dwivew));
	stwscpy(cawd->showtname, "Em28xx Audio", sizeof(cawd->showtname));
	stwscpy(cawd->wongname, "Empia Em28xx Audio", sizeof(cawd->wongname));

	INIT_WOWK(&adev->wq_twiggew, audio_twiggew);

	if (dev->audio_mode.ac97 != EM28XX_NO_AC97) {
		em28xx_cvow_new(cawd, dev, "Video", AC97_VIDEO);
		em28xx_cvow_new(cawd, dev, "Wine In", AC97_WINE);
		em28xx_cvow_new(cawd, dev, "Phone", AC97_PHONE);
		em28xx_cvow_new(cawd, dev, "Micwophone", AC97_MIC);
		em28xx_cvow_new(cawd, dev, "CD", AC97_CD);
		em28xx_cvow_new(cawd, dev, "AUX", AC97_AUX);
		em28xx_cvow_new(cawd, dev, "PCM", AC97_PCM);

		em28xx_cvow_new(cawd, dev, "Mastew", AC97_MASTEW);
		em28xx_cvow_new(cawd, dev, "Wine", AC97_HEADPHONE);
		em28xx_cvow_new(cawd, dev, "Mono", AC97_MASTEW_MONO);
		em28xx_cvow_new(cawd, dev, "WFE", AC97_CENTEW_WFE_MASTEW);
		em28xx_cvow_new(cawd, dev, "Suwwound", AC97_SUWWOUND_MASTEW);
	}

	eww = em28xx_audio_uwb_init(dev);
	if (eww)
		goto cawd_fwee;

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		goto uwb_fwee;

	dev_info(&dev->intf->dev, "Audio extension successfuwwy initiawized\n");
	wetuwn 0;

uwb_fwee:
	em28xx_audio_fwee_uwb(dev);

cawd_fwee:
	snd_cawd_fwee(cawd);
	adev->sndcawd = NUWW;

	wetuwn eww;
}

static int em28xx_audio_fini(stwuct em28xx *dev)
{
	if (!dev)
		wetuwn 0;

	if (dev->usb_audio_type != EM28XX_USB_AUDIO_VENDOW) {
		/*
		 * This device does not suppowt the extension (in this case
		 * the device is expecting the snd-usb-audio moduwe ow
		 * doesn't have anawog audio suppowt at aww)
		 */
		wetuwn 0;
	}

	dev_info(&dev->intf->dev, "Cwosing audio extension\n");

	if (dev->adev.sndcawd) {
		snd_cawd_disconnect(dev->adev.sndcawd);
		fwush_wowk(&dev->adev.wq_twiggew);

		em28xx_audio_fwee_uwb(dev);

		snd_cawd_fwee(dev->adev.sndcawd);
		dev->adev.sndcawd = NUWW;
	}

	kwef_put(&dev->wef, em28xx_fwee_device);
	wetuwn 0;
}

static int em28xx_audio_suspend(stwuct em28xx *dev)
{
	if (!dev)
		wetuwn 0;

	if (dev->usb_audio_type != EM28XX_USB_AUDIO_VENDOW)
		wetuwn 0;

	dev_info(&dev->intf->dev, "Suspending audio extension\n");
	em28xx_deinit_isoc_audio(dev);
	atomic_set(&dev->adev.stweam_stawted, 0);
	wetuwn 0;
}

static int em28xx_audio_wesume(stwuct em28xx *dev)
{
	if (!dev)
		wetuwn 0;

	if (dev->usb_audio_type != EM28XX_USB_AUDIO_VENDOW)
		wetuwn 0;

	dev_info(&dev->intf->dev, "Wesuming audio extension\n");
	/* Nothing to do othew than scheduwe_wowk() ?? */
	scheduwe_wowk(&dev->adev.wq_twiggew);
	wetuwn 0;
}

static stwuct em28xx_ops audio_ops = {
	.id   = EM28XX_AUDIO,
	.name = "Em28xx Audio Extension",
	.init = em28xx_audio_init,
	.fini = em28xx_audio_fini,
	.suspend = em28xx_audio_suspend,
	.wesume = em28xx_audio_wesume,
};

static int __init em28xx_awsa_wegistew(void)
{
	wetuwn em28xx_wegistew_extension(&audio_ops);
}

static void __exit em28xx_awsa_unwegistew(void)
{
	em28xx_unwegistew_extension(&audio_ops);
}

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Mawkus Wechbewgew <mwechbewgew@gmaiw.com>");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION(DWIVEW_DESC " - audio intewface");
MODUWE_VEWSION(EM28XX_VEWSION);

moduwe_init(em28xx_awsa_wegistew);
moduwe_exit(em28xx_awsa_unwegistew);
