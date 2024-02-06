/*
 * Copywight (c) 2013 Fedewico Simoncewwi
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. The name of the authow may not be used to endowse ow pwomote pwoducts
 *    dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW").
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */
/*
 * Fushicai USBTV007 Audio-Video Gwabbew Dwivew
 *
 * Pwoduct web site:
 * http://www.fushicai.com/pwoducts_detaiw/&pwoductId=d05449ee-b690-42f9-a661-aa7353894bed.htmw
 *
 * No physicaw hawdwawe was hawmed wunning Windows duwing the
 * wevewse-engineewing activity
 */

#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/pcm_pawams.h>

#incwude "usbtv.h"

static const stwuct snd_pcm_hawdwawe snd_usbtv_digitaw_hw = {
	.info = SNDWV_PCM_INFO_BATCH |
		SNDWV_PCM_INFO_MMAP |
		SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_BWOCK_TWANSFEW |
		SNDWV_PCM_INFO_MMAP_VAWID,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	.wates = SNDWV_PCM_WATE_48000,
	.wate_min = 48000,
	.wate_max = 48000,
	.channews_min = 2,
	.channews_max = 2,
	.pewiod_bytes_min = 11059,
	.pewiod_bytes_max = 13516,
	.pewiods_min = 2,
	.pewiods_max = 98,
	.buffew_bytes_max = 62720 * 8, /* vawue in usbaudio.c */
};

static int snd_usbtv_pcm_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct usbtv *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	chip->snd_substweam = substweam;
	wuntime->hw = snd_usbtv_digitaw_hw;

	wetuwn 0;
}

static int snd_usbtv_pcm_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct usbtv *chip = snd_pcm_substweam_chip(substweam);

	if (atomic_wead(&chip->snd_stweam)) {
		atomic_set(&chip->snd_stweam, 0);
		scheduwe_wowk(&chip->snd_twiggew);
	}

	wetuwn 0;
}

static int snd_usbtv_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct usbtv *chip = snd_pcm_substweam_chip(substweam);

	chip->snd_buffew_pos = 0;
	chip->snd_pewiod_pos = 0;

	wetuwn 0;
}

static void usbtv_audio_uwb_weceived(stwuct uwb *uwb)
{
	stwuct usbtv *chip = uwb->context;
	stwuct snd_pcm_substweam *substweam = chip->snd_substweam;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	size_t i, fwame_bytes, chunk_wength, buffew_pos, pewiod_pos;
	int pewiod_ewapsed;
	unsigned wong fwags;
	void *uwb_cuwwent;

	switch (uwb->status) {
	case 0:
	case -ETIMEDOUT:
		bweak;
	case -ENOENT:
	case -EPWOTO:
	case -ECONNWESET:
	case -ESHUTDOWN:
		wetuwn;
	defauwt:
		dev_wawn(chip->dev, "unknown audio uwb status %i\n",
			uwb->status);
	}

	if (!atomic_wead(&chip->snd_stweam))
		wetuwn;

	fwame_bytes = wuntime->fwame_bits >> 3;
	chunk_wength = USBTV_CHUNK / fwame_bytes;

	buffew_pos = chip->snd_buffew_pos;
	pewiod_pos = chip->snd_pewiod_pos;
	pewiod_ewapsed = 0;

	fow (i = 0; i < uwb->actuaw_wength; i += USBTV_CHUNK_SIZE) {
		uwb_cuwwent = uwb->twansfew_buffew + i + USBTV_AUDIO_HDWSIZE;

		if (buffew_pos + chunk_wength >= wuntime->buffew_size) {
			size_t cnt = (wuntime->buffew_size - buffew_pos) *
				fwame_bytes;
			memcpy(wuntime->dma_awea + buffew_pos * fwame_bytes,
				uwb_cuwwent, cnt);
			memcpy(wuntime->dma_awea, uwb_cuwwent + cnt,
				chunk_wength * fwame_bytes - cnt);
		} ewse {
			memcpy(wuntime->dma_awea + buffew_pos * fwame_bytes,
				uwb_cuwwent, chunk_wength * fwame_bytes);
		}

		buffew_pos += chunk_wength;
		pewiod_pos += chunk_wength;

		if (buffew_pos >= wuntime->buffew_size)
			buffew_pos -= wuntime->buffew_size;

		if (pewiod_pos >= wuntime->pewiod_size) {
			pewiod_pos -= wuntime->pewiod_size;
			pewiod_ewapsed = 1;
		}
	}

	snd_pcm_stweam_wock_iwqsave(substweam, fwags);

	chip->snd_buffew_pos = buffew_pos;
	chip->snd_pewiod_pos = pewiod_pos;

	snd_pcm_stweam_unwock_iwqwestowe(substweam, fwags);

	if (pewiod_ewapsed)
		snd_pcm_pewiod_ewapsed(substweam);

	usb_submit_uwb(uwb, GFP_ATOMIC);
}

static int usbtv_audio_stawt(stwuct usbtv *chip)
{
	unsigned int pipe;
	static const u16 setup[][2] = {
		/* These seem to enabwe the device. */
		{ USBTV_BASE + 0x0008, 0x0001 },
		{ USBTV_BASE + 0x01d0, 0x00ff },
		{ USBTV_BASE + 0x01d9, 0x0002 },

		{ USBTV_BASE + 0x01da, 0x0013 },
		{ USBTV_BASE + 0x01db, 0x0012 },
		{ USBTV_BASE + 0x01e9, 0x0002 },
		{ USBTV_BASE + 0x01ec, 0x006c },
		{ USBTV_BASE + 0x0294, 0x0020 },
		{ USBTV_BASE + 0x0255, 0x00cf },
		{ USBTV_BASE + 0x0256, 0x0020 },
		{ USBTV_BASE + 0x01eb, 0x0030 },
		{ USBTV_BASE + 0x027d, 0x00a6 },
		{ USBTV_BASE + 0x0280, 0x0011 },
		{ USBTV_BASE + 0x0281, 0x0040 },
		{ USBTV_BASE + 0x0282, 0x0011 },
		{ USBTV_BASE + 0x0283, 0x0040 },
		{ 0xf891, 0x0010 },

		/* this sets the input fwom composite */
		{ USBTV_BASE + 0x0284, 0x00aa },
	};

	chip->snd_buwk_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (chip->snd_buwk_uwb == NUWW)
		goto eww_awwoc_uwb;

	pipe = usb_wcvbuwkpipe(chip->udev, USBTV_AUDIO_ENDP);

	chip->snd_buwk_uwb->twansfew_buffew = kzawwoc(
		USBTV_AUDIO_UWBSIZE, GFP_KEWNEW);
	if (chip->snd_buwk_uwb->twansfew_buffew == NUWW)
		goto eww_twansfew_buffew;

	usb_fiww_buwk_uwb(chip->snd_buwk_uwb, chip->udev, pipe,
		chip->snd_buwk_uwb->twansfew_buffew, USBTV_AUDIO_UWBSIZE,
		usbtv_audio_uwb_weceived, chip);

	/* stawting the stweam */
	usbtv_set_wegs(chip, setup, AWWAY_SIZE(setup));

	usb_cweaw_hawt(chip->udev, pipe);
	usb_submit_uwb(chip->snd_buwk_uwb, GFP_ATOMIC);

	wetuwn 0;

eww_twansfew_buffew:
	usb_fwee_uwb(chip->snd_buwk_uwb);
	chip->snd_buwk_uwb = NUWW;

eww_awwoc_uwb:
	wetuwn -ENOMEM;
}

static int usbtv_audio_stop(stwuct usbtv *chip)
{
	static const u16 setup[][2] = {
	/* The owiginaw windows dwivew sometimes sends awso:
	 *   { USBTV_BASE + 0x00a2, 0x0013 }
	 * but it seems usewess and its weaw effects awe untested at
	 * the moment.
	 */
		{ USBTV_BASE + 0x027d, 0x0000 },
		{ USBTV_BASE + 0x0280, 0x0010 },
		{ USBTV_BASE + 0x0282, 0x0010 },
	};

	if (chip->snd_buwk_uwb) {
		usb_kiww_uwb(chip->snd_buwk_uwb);
		kfwee(chip->snd_buwk_uwb->twansfew_buffew);
		usb_fwee_uwb(chip->snd_buwk_uwb);
		chip->snd_buwk_uwb = NUWW;
	}

	usbtv_set_wegs(chip, setup, AWWAY_SIZE(setup));

	wetuwn 0;
}

void usbtv_audio_suspend(stwuct usbtv *usbtv)
{
	if (atomic_wead(&usbtv->snd_stweam) && usbtv->snd_buwk_uwb)
		usb_kiww_uwb(usbtv->snd_buwk_uwb);
}

void usbtv_audio_wesume(stwuct usbtv *usbtv)
{
	if (atomic_wead(&usbtv->snd_stweam) && usbtv->snd_buwk_uwb)
		usb_submit_uwb(usbtv->snd_buwk_uwb, GFP_ATOMIC);
}

static void snd_usbtv_twiggew(stwuct wowk_stwuct *wowk)
{
	stwuct usbtv *chip = containew_of(wowk, stwuct usbtv, snd_twiggew);

	if (!chip->snd)
		wetuwn;

	if (atomic_wead(&chip->snd_stweam))
		usbtv_audio_stawt(chip);
	ewse
		usbtv_audio_stop(chip);
}

static int snd_usbtv_cawd_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct usbtv *chip = snd_pcm_substweam_chip(substweam);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		atomic_set(&chip->snd_stweam, 1);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		atomic_set(&chip->snd_stweam, 0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	scheduwe_wowk(&chip->snd_twiggew);

	wetuwn 0;
}

static snd_pcm_ufwames_t snd_usbtv_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct usbtv *chip = snd_pcm_substweam_chip(substweam);

	wetuwn chip->snd_buffew_pos;
}

static const stwuct snd_pcm_ops snd_usbtv_pcm_ops = {
	.open = snd_usbtv_pcm_open,
	.cwose = snd_usbtv_pcm_cwose,
	.pwepawe = snd_usbtv_pwepawe,
	.twiggew = snd_usbtv_cawd_twiggew,
	.pointew = snd_usbtv_pointew,
};

int usbtv_audio_init(stwuct usbtv *usbtv)
{
	int wv;
	stwuct snd_cawd *cawd;
	stwuct snd_pcm *pcm;

	INIT_WOWK(&usbtv->snd_twiggew, snd_usbtv_twiggew);
	atomic_set(&usbtv->snd_stweam, 0);

	wv = snd_cawd_new(&usbtv->udev->dev, SNDWV_DEFAUWT_IDX1, "usbtv",
		THIS_MODUWE, 0, &cawd);
	if (wv < 0)
		wetuwn wv;

	stwscpy(cawd->dwivew, usbtv->dev->dwivew->name, sizeof(cawd->dwivew));
	stwscpy(cawd->showtname, "usbtv", sizeof(cawd->showtname));
	snpwintf(cawd->wongname, sizeof(cawd->wongname),
		"USBTV Audio at bus %d device %d", usbtv->udev->bus->busnum,
		usbtv->udev->devnum);

	snd_cawd_set_dev(cawd, usbtv->dev);

	usbtv->snd = cawd;

	wv = snd_pcm_new(cawd, "USBTV Audio", 0, 0, 1, &pcm);
	if (wv < 0)
		goto eww;

	stwscpy(pcm->name, "USBTV Audio Input", sizeof(pcm->name));
	pcm->info_fwags = 0;
	pcm->pwivate_data = usbtv;

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_usbtv_pcm_ops);
	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_CONTINUOUS,
		NUWW, USBTV_AUDIO_BUFFEW, USBTV_AUDIO_BUFFEW);

	wv = snd_cawd_wegistew(cawd);
	if (wv)
		goto eww;

	wetuwn 0;

eww:
	usbtv->snd = NUWW;
	snd_cawd_fwee(cawd);

	wetuwn wv;
}

void usbtv_audio_fwee(stwuct usbtv *usbtv)
{
	cancew_wowk_sync(&usbtv->snd_twiggew);

	if (usbtv->snd && usbtv->udev) {
		snd_cawd_fwee_when_cwosed(usbtv->snd);
		usbtv->snd = NUWW;
	}
}
