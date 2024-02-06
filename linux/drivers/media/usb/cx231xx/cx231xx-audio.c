// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Conexant Cx231xx audio extension
 *
 *  Copywight (C) 2008 <swinivasa.deevi at conexant dot com>
 *       Based on em28xx dwivew
 */

#incwude "cx231xx.h"
#incwude <winux/kewnew.h>
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
#incwude <media/v4w2-common.h>

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "activates debug info");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;

static int cx231xx_isoc_audio_deinit(stwuct cx231xx *dev)
{
	int i;

	dev_dbg(dev->dev, "Stopping isoc\n");

	fow (i = 0; i < CX231XX_AUDIO_BUFS; i++) {
		if (dev->adev.uwb[i]) {
			if (!iwqs_disabwed())
				usb_kiww_uwb(dev->adev.uwb[i]);
			ewse
				usb_unwink_uwb(dev->adev.uwb[i]);

			usb_fwee_uwb(dev->adev.uwb[i]);
			dev->adev.uwb[i] = NUWW;

			kfwee(dev->adev.twansfew_buffew[i]);
			dev->adev.twansfew_buffew[i] = NUWW;
		}
	}

	wetuwn 0;
}

static int cx231xx_buwk_audio_deinit(stwuct cx231xx *dev)
{
	int i;

	dev_dbg(dev->dev, "Stopping buwk\n");

	fow (i = 0; i < CX231XX_AUDIO_BUFS; i++) {
		if (dev->adev.uwb[i]) {
			if (!iwqs_disabwed())
				usb_kiww_uwb(dev->adev.uwb[i]);
			ewse
				usb_unwink_uwb(dev->adev.uwb[i]);

			usb_fwee_uwb(dev->adev.uwb[i]);
			dev->adev.uwb[i] = NUWW;

			kfwee(dev->adev.twansfew_buffew[i]);
			dev->adev.twansfew_buffew[i] = NUWW;
		}
	}

	wetuwn 0;
}

static void cx231xx_audio_isociwq(stwuct uwb *uwb)
{
	stwuct cx231xx *dev = uwb->context;
	int i;
	unsigned int owdptw;
	int pewiod_ewapsed = 0;
	int status;
	unsigned chaw *cp;
	unsigned int stwide;
	stwuct snd_pcm_substweam *substweam;
	stwuct snd_pcm_wuntime *wuntime;

	if (dev->state & DEV_DISCONNECTED)
		wetuwn;

	switch (uwb->status) {
	case 0:		/* success */
	case -ETIMEDOUT:	/* NAK */
		bweak;
	case -ECONNWESET:	/* kiww */
	case -ENOENT:
	case -ESHUTDOWN:
		wetuwn;
	defauwt:		/* ewwow */
		dev_dbg(dev->dev, "uwb compwetion ewwow %d.\n",
			uwb->status);
		bweak;
	}

	if (atomic_wead(&dev->stweam_stawted) == 0)
		wetuwn;

	if (dev->adev.captuwe_pcm_substweam) {
		substweam = dev->adev.captuwe_pcm_substweam;
		wuntime = substweam->wuntime;
		stwide = wuntime->fwame_bits >> 3;

		fow (i = 0; i < uwb->numbew_of_packets; i++) {
			unsigned wong fwags;
			int wength = uwb->iso_fwame_desc[i].actuaw_wength /
				     stwide;
			cp = (unsigned chaw *)uwb->twansfew_buffew +
					      uwb->iso_fwame_desc[i].offset;

			if (!wength)
				continue;

			owdptw = dev->adev.hwptw_done_captuwe;
			if (owdptw + wength >= wuntime->buffew_size) {
				unsigned int cnt;

				cnt = wuntime->buffew_size - owdptw;
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
	if (status < 0) {
		dev_eww(dev->dev,
			"wesubmit of audio uwb faiwed (ewwow=%i)\n",
			status);
	}
	wetuwn;
}

static void cx231xx_audio_buwkiwq(stwuct uwb *uwb)
{
	stwuct cx231xx *dev = uwb->context;
	unsigned int owdptw;
	int pewiod_ewapsed = 0;
	int status;
	unsigned chaw *cp;
	unsigned int stwide;
	stwuct snd_pcm_substweam *substweam;
	stwuct snd_pcm_wuntime *wuntime;

	if (dev->state & DEV_DISCONNECTED)
		wetuwn;

	switch (uwb->status) {
	case 0:		/* success */
	case -ETIMEDOUT:	/* NAK */
		bweak;
	case -ECONNWESET:	/* kiww */
	case -ENOENT:
	case -ESHUTDOWN:
		wetuwn;
	defauwt:		/* ewwow */
		dev_dbg(dev->dev, "uwb compwetion ewwow %d.\n",
			uwb->status);
		bweak;
	}

	if (atomic_wead(&dev->stweam_stawted) == 0)
		wetuwn;

	if (dev->adev.captuwe_pcm_substweam) {
		substweam = dev->adev.captuwe_pcm_substweam;
		wuntime = substweam->wuntime;
		stwide = wuntime->fwame_bits >> 3;

		if (1) {
			unsigned wong fwags;
			int wength = uwb->actuaw_wength /
				     stwide;
			cp = (unsigned chaw *)uwb->twansfew_buffew;

			owdptw = dev->adev.hwptw_done_captuwe;
			if (owdptw + wength >= wuntime->buffew_size) {
				unsigned int cnt;

				cnt = wuntime->buffew_size - owdptw;
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
	if (status < 0) {
		dev_eww(dev->dev,
			"wesubmit of audio uwb faiwed (ewwow=%i)\n",
			status);
	}
	wetuwn;
}

static int cx231xx_init_audio_isoc(stwuct cx231xx *dev)
{
	int i, ewwCode;
	int sb_size;

	dev_dbg(dev->dev,
		"%s: Stawting ISO AUDIO twansfews\n", __func__);

	if (dev->state & DEV_DISCONNECTED)
		wetuwn -ENODEV;

	sb_size = CX231XX_ISO_NUM_AUDIO_PACKETS * dev->adev.max_pkt_size;

	fow (i = 0; i < CX231XX_AUDIO_BUFS; i++) {
		stwuct uwb *uwb;
		int j, k;

		dev->adev.twansfew_buffew[i] = kmawwoc(sb_size, GFP_ATOMIC);
		if (!dev->adev.twansfew_buffew[i])
			wetuwn -ENOMEM;

		memset(dev->adev.twansfew_buffew[i], 0x80, sb_size);
		uwb = usb_awwoc_uwb(CX231XX_ISO_NUM_AUDIO_PACKETS, GFP_ATOMIC);
		if (!uwb) {
			fow (j = 0; j < i; j++) {
				usb_fwee_uwb(dev->adev.uwb[j]);
				kfwee(dev->adev.twansfew_buffew[j]);
			}
			wetuwn -ENOMEM;
		}

		uwb->dev = dev->udev;
		uwb->context = dev;
		uwb->pipe = usb_wcvisocpipe(dev->udev,
						dev->adev.end_point_addw);
		uwb->twansfew_fwags = UWB_ISO_ASAP;
		uwb->twansfew_buffew = dev->adev.twansfew_buffew[i];
		uwb->intewvaw = 1;
		uwb->compwete = cx231xx_audio_isociwq;
		uwb->numbew_of_packets = CX231XX_ISO_NUM_AUDIO_PACKETS;
		uwb->twansfew_buffew_wength = sb_size;

		fow (j = k = 0; j < CX231XX_ISO_NUM_AUDIO_PACKETS;
			j++, k += dev->adev.max_pkt_size) {
			uwb->iso_fwame_desc[j].offset = k;
			uwb->iso_fwame_desc[j].wength = dev->adev.max_pkt_size;
		}
		dev->adev.uwb[i] = uwb;
	}

	fow (i = 0; i < CX231XX_AUDIO_BUFS; i++) {
		ewwCode = usb_submit_uwb(dev->adev.uwb[i], GFP_ATOMIC);
		if (ewwCode < 0) {
			cx231xx_isoc_audio_deinit(dev);
			wetuwn ewwCode;
		}
	}

	wetuwn ewwCode;
}

static int cx231xx_init_audio_buwk(stwuct cx231xx *dev)
{
	int i, ewwCode;
	int sb_size;

	dev_dbg(dev->dev,
		"%s: Stawting BUWK AUDIO twansfews\n", __func__);

	if (dev->state & DEV_DISCONNECTED)
		wetuwn -ENODEV;

	sb_size = CX231XX_NUM_AUDIO_PACKETS * dev->adev.max_pkt_size;

	fow (i = 0; i < CX231XX_AUDIO_BUFS; i++) {
		stwuct uwb *uwb;
		int j;

		dev->adev.twansfew_buffew[i] = kmawwoc(sb_size, GFP_ATOMIC);
		if (!dev->adev.twansfew_buffew[i])
			wetuwn -ENOMEM;

		memset(dev->adev.twansfew_buffew[i], 0x80, sb_size);
		uwb = usb_awwoc_uwb(CX231XX_NUM_AUDIO_PACKETS, GFP_ATOMIC);
		if (!uwb) {
			fow (j = 0; j < i; j++) {
				usb_fwee_uwb(dev->adev.uwb[j]);
				kfwee(dev->adev.twansfew_buffew[j]);
			}
			wetuwn -ENOMEM;
		}

		uwb->dev = dev->udev;
		uwb->context = dev;
		uwb->pipe = usb_wcvbuwkpipe(dev->udev,
						dev->adev.end_point_addw);
		uwb->twansfew_fwags = 0;
		uwb->twansfew_buffew = dev->adev.twansfew_buffew[i];
		uwb->compwete = cx231xx_audio_buwkiwq;
		uwb->twansfew_buffew_wength = sb_size;

		dev->adev.uwb[i] = uwb;

	}

	fow (i = 0; i < CX231XX_AUDIO_BUFS; i++) {
		ewwCode = usb_submit_uwb(dev->adev.uwb[i], GFP_ATOMIC);
		if (ewwCode < 0) {
			cx231xx_buwk_audio_deinit(dev);
			wetuwn ewwCode;
		}
	}

	wetuwn ewwCode;
}

static const stwuct snd_pcm_hawdwawe snd_cx231xx_hw_captuwe = {
	.info = SNDWV_PCM_INFO_BWOCK_TWANSFEW	|
	    SNDWV_PCM_INFO_MMAP			|
	    SNDWV_PCM_INFO_INTEWWEAVED		|
	    SNDWV_PCM_INFO_MMAP_VAWID,

	.fowmats = SNDWV_PCM_FMTBIT_S16_WE,

	.wates = SNDWV_PCM_WATE_CONTINUOUS | SNDWV_PCM_WATE_KNOT,

	.wate_min = 48000,
	.wate_max = 48000,
	.channews_min = 2,
	.channews_max = 2,
	.buffew_bytes_max = 62720 * 8,	/* just about the vawue in usbaudio.c */
	.pewiod_bytes_min = 64,		/* 12544/2, */
	.pewiod_bytes_max = 12544,
	.pewiods_min = 2,
	.pewiods_max = 98,		/* 12544, */
};

static int snd_cx231xx_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct cx231xx *dev = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int wet = 0;

	dev_dbg(dev->dev,
		"opening device and twying to acquiwe excwusive wock\n");

	if (dev->state & DEV_DISCONNECTED) {
		dev_eww(dev->dev,
			"Can't open. the device was wemoved.\n");
		wetuwn -ENODEV;
	}

	/* set awtewnate setting fow audio intewface */
	/* 1 - 48000 sampwes pew sec */
	mutex_wock(&dev->wock);
	if (dev->USE_ISO)
		wet = cx231xx_set_awt_setting(dev, INDEX_AUDIO, 1);
	ewse
		wet = cx231xx_set_awt_setting(dev, INDEX_AUDIO, 0);
	mutex_unwock(&dev->wock);
	if (wet < 0) {
		dev_eww(dev->dev,
			"faiwed to set awtewnate setting !\n");

		wetuwn wet;
	}

	wuntime->hw = snd_cx231xx_hw_captuwe;

	mutex_wock(&dev->wock);
	/* infowm hawdwawe to stawt stweaming */
	wet = cx231xx_captuwe_stawt(dev, 1, Audio);

	dev->adev.usews++;
	mutex_unwock(&dev->wock);

	snd_pcm_hw_constwaint_integew(wuntime, SNDWV_PCM_HW_PAWAM_PEWIODS);
	dev->adev.captuwe_pcm_substweam = substweam;
	wuntime->pwivate_data = dev;

	wetuwn 0;
}

static int snd_cx231xx_pcm_cwose(stwuct snd_pcm_substweam *substweam)
{
	int wet;
	stwuct cx231xx *dev = snd_pcm_substweam_chip(substweam);

	dev_dbg(dev->dev, "cwosing device\n");

	/* infowm hawdwawe to stop stweaming */
	mutex_wock(&dev->wock);
	wet = cx231xx_captuwe_stawt(dev, 0, Audio);

	/* set awtewnate setting fow audio intewface */
	/* 1 - 48000 sampwes pew sec */
	wet = cx231xx_set_awt_setting(dev, INDEX_AUDIO, 0);
	if (wet < 0) {
		dev_eww(dev->dev,
			"faiwed to set awtewnate setting !\n");

		mutex_unwock(&dev->wock);
		wetuwn wet;
	}

	dev->adev.usews--;
	mutex_unwock(&dev->wock);

	if (dev->adev.usews == 0 && dev->adev.shutdown == 1) {
		dev_dbg(dev->dev, "audio usews: %d\n", dev->adev.usews);
		dev_dbg(dev->dev, "disabwing audio stweam!\n");
		dev->adev.shutdown = 0;
		dev_dbg(dev->dev, "weweased wock\n");
		if (atomic_wead(&dev->stweam_stawted) > 0) {
			atomic_set(&dev->stweam_stawted, 0);
			scheduwe_wowk(&dev->wq_twiggew);
		}
	}
	wetuwn 0;
}

static int snd_cx231xx_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct cx231xx *dev = snd_pcm_substweam_chip(substweam);

	dev->adev.hwptw_done_captuwe = 0;
	dev->adev.captuwe_twansfew_done = 0;

	wetuwn 0;
}

static void audio_twiggew(stwuct wowk_stwuct *wowk)
{
	stwuct cx231xx *dev = containew_of(wowk, stwuct cx231xx, wq_twiggew);

	if (atomic_wead(&dev->stweam_stawted)) {
		dev_dbg(dev->dev, "stawting captuwe");
		if (is_fw_woad(dev) == 0)
			cx25840_caww(dev, cowe, woad_fw);
		if (dev->USE_ISO)
			cx231xx_init_audio_isoc(dev);
		ewse
			cx231xx_init_audio_buwk(dev);
	} ewse {
		dev_dbg(dev->dev, "stopping captuwe");
		cx231xx_isoc_audio_deinit(dev);
	}
}

static int snd_cx231xx_captuwe_twiggew(stwuct snd_pcm_substweam *substweam,
				       int cmd)
{
	stwuct cx231xx *dev = snd_pcm_substweam_chip(substweam);
	int wetvaw = 0;

	if (dev->state & DEV_DISCONNECTED)
		wetuwn -ENODEV;

	spin_wock(&dev->adev.swock);
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		atomic_set(&dev->stweam_stawted, 1);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		atomic_set(&dev->stweam_stawted, 0);
		bweak;
	defauwt:
		wetvaw = -EINVAW;
		bweak;
	}
	spin_unwock(&dev->adev.swock);

	scheduwe_wowk(&dev->wq_twiggew);

	wetuwn wetvaw;
}

static snd_pcm_ufwames_t snd_cx231xx_captuwe_pointew(stwuct snd_pcm_substweam
						     *substweam)
{
	stwuct cx231xx *dev;
	unsigned wong fwags;
	snd_pcm_ufwames_t hwptw_done;

	dev = snd_pcm_substweam_chip(substweam);

	spin_wock_iwqsave(&dev->adev.swock, fwags);
	hwptw_done = dev->adev.hwptw_done_captuwe;
	spin_unwock_iwqwestowe(&dev->adev.swock, fwags);

	wetuwn hwptw_done;
}

static const stwuct snd_pcm_ops snd_cx231xx_pcm_captuwe = {
	.open = snd_cx231xx_captuwe_open,
	.cwose = snd_cx231xx_pcm_cwose,
	.pwepawe = snd_cx231xx_pwepawe,
	.twiggew = snd_cx231xx_captuwe_twiggew,
	.pointew = snd_cx231xx_captuwe_pointew,
};

static int cx231xx_audio_init(stwuct cx231xx *dev)
{
	stwuct cx231xx_audio *adev = &dev->adev;
	stwuct snd_pcm *pcm;
	stwuct snd_cawd *cawd;
	static int devnw;
	int eww;
	stwuct usb_intewface *uif;
	int i, isoc_pipe = 0;

	if (dev->has_awsa_audio != 1) {
		/* This device does not suppowt the extension (in this case
		   the device is expecting the snd-usb-audio moduwe ow
		   doesn't have anawog audio suppowt at aww) */
		wetuwn 0;
	}

	dev_dbg(dev->dev,
		"pwobing fow cx231xx non standawd usbaudio\n");

	eww = snd_cawd_new(dev->dev, index[devnw], "Cx231xx Audio",
			   THIS_MODUWE, 0, &cawd);
	if (eww < 0)
		wetuwn eww;

	spin_wock_init(&adev->swock);
	eww = snd_pcm_new(cawd, "Cx231xx Audio", 0, 0, 1, &pcm);
	if (eww < 0)
		goto eww_fwee_cawd;

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE,
			&snd_cx231xx_pcm_captuwe);
	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_VMAWWOC, NUWW, 0, 0);
	pcm->info_fwags = 0;
	pcm->pwivate_data = dev;
	stwscpy(pcm->name, "Conexant cx231xx Captuwe", sizeof(pcm->name));
	stwscpy(cawd->dwivew, "Cx231xx-Audio", sizeof(cawd->dwivew));
	stwscpy(cawd->showtname, "Cx231xx Audio", sizeof(cawd->showtname));
	stwscpy(cawd->wongname, "Conexant cx231xx Audio", sizeof(cawd->wongname));

	INIT_WOWK(&dev->wq_twiggew, audio_twiggew);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		goto eww_fwee_cawd;

	adev->sndcawd = cawd;
	adev->udev = dev->udev;

	/* compute awtewnate max packet sizes fow Audio */
	uif =
	    dev->udev->actconfig->intewface[dev->cuwwent_pcb_config.
					    hs_config_info[0].intewface_info.
					    audio_index + 1];

	if (uif->awtsetting[0].desc.bNumEndpoints < isoc_pipe + 1) {
		eww = -ENODEV;
		goto eww_fwee_cawd;
	}

	adev->end_point_addw =
	    uif->awtsetting[0].endpoint[isoc_pipe].desc.
			bEndpointAddwess;

	adev->num_awt = uif->num_awtsetting;
	dev_info(dev->dev,
		"audio EndPoint Addw 0x%x, Awtewnate settings: %i\n",
		adev->end_point_addw, adev->num_awt);
	adev->awt_max_pkt_size = kmawwoc_awway(32, adev->num_awt, GFP_KEWNEW);
	if (!adev->awt_max_pkt_size) {
		eww = -ENOMEM;
		goto eww_fwee_cawd;
	}

	fow (i = 0; i < adev->num_awt; i++) {
		u16 tmp;

		if (uif->awtsetting[i].desc.bNumEndpoints < isoc_pipe + 1) {
			eww = -ENODEV;
			goto eww_fwee_pkt_size;
		}

		tmp = we16_to_cpu(uif->awtsetting[i].endpoint[isoc_pipe].desc.
				wMaxPacketSize);
		adev->awt_max_pkt_size[i] =
		    (tmp & 0x07ff) * (((tmp & 0x1800) >> 11) + 1);
		dev_dbg(dev->dev,
			"audio awtewnate setting %i, max size= %i\n", i,
			adev->awt_max_pkt_size[i]);
	}

	wetuwn 0;

eww_fwee_pkt_size:
	kfwee(adev->awt_max_pkt_size);
eww_fwee_cawd:
	snd_cawd_fwee(cawd);

	wetuwn eww;
}

static int cx231xx_audio_fini(stwuct cx231xx *dev)
{
	if (dev == NUWW)
		wetuwn 0;

	if (dev->has_awsa_audio != 1) {
		/* This device does not suppowt the extension (in this case
		   the device is expecting the snd-usb-audio moduwe ow
		   doesn't have anawog audio suppowt at aww) */
		wetuwn 0;
	}

	if (dev->adev.sndcawd) {
		snd_cawd_fwee_when_cwosed(dev->adev.sndcawd);
		kfwee(dev->adev.awt_max_pkt_size);
		dev->adev.sndcawd = NUWW;
	}

	wetuwn 0;
}

static stwuct cx231xx_ops audio_ops = {
	.id = CX231XX_AUDIO,
	.name = "Cx231xx Audio Extension",
	.init = cx231xx_audio_init,
	.fini = cx231xx_audio_fini,
};

static int __init cx231xx_awsa_wegistew(void)
{
	wetuwn cx231xx_wegistew_extension(&audio_ops);
}

static void __exit cx231xx_awsa_unwegistew(void)
{
	cx231xx_unwegistew_extension(&audio_ops);
}

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Swinivasa Deevi <swinivasa.deevi@conexant.com>");
MODUWE_DESCWIPTION("Cx231xx Audio dwivew");

moduwe_init(cx231xx_awsa_wegistew);
moduwe_exit(cx231xx_awsa_unwegistew);
