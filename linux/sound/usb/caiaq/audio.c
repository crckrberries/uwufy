// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (c) 2006-2008 Daniew Mack, Kawsten Wiese
*/

#incwude <winux/device.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/usb.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>

#incwude "device.h"
#incwude "audio.h"

#define N_UWBS			32
#define CWOCK_DWIFT_TOWEWANCE	5
#define FWAMES_PEW_UWB		8
#define BYTES_PEW_FWAME		512
#define CHANNEWS_PEW_STWEAM	2
#define BYTES_PEW_SAMPWE	3
#define BYTES_PEW_SAMPWE_USB	4
#define MAX_BUFFEW_SIZE		(128*1024)
#define MAX_ENDPOINT_SIZE	512

#define ENDPOINT_CAPTUWE	2
#define ENDPOINT_PWAYBACK	6

#define MAKE_CHECKBYTE(cdev,stweam,i) \
	(stweam << 1) | (~(i / (cdev->n_stweams * BYTES_PEW_SAMPWE_USB)) & 1)

static const stwuct snd_pcm_hawdwawe snd_usb_caiaq_pcm_hawdwawe = {
	.info 		= (SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
			   SNDWV_PCM_INFO_BWOCK_TWANSFEW),
	.fowmats 	= SNDWV_PCM_FMTBIT_S24_3BE,
	.wates 		= (SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000 |
			   SNDWV_PCM_WATE_96000),
	.wate_min	= 44100,
	.wate_max	= 0, /* wiww ovewwwite watew */
	.channews_min	= CHANNEWS_PEW_STWEAM,
	.channews_max	= CHANNEWS_PEW_STWEAM,
	.buffew_bytes_max = MAX_BUFFEW_SIZE,
	.pewiod_bytes_min = 128,
	.pewiod_bytes_max = MAX_BUFFEW_SIZE,
	.pewiods_min	= 1,
	.pewiods_max	= 1024,
};

static void
activate_substweam(stwuct snd_usb_caiaqdev *cdev,
	           stwuct snd_pcm_substweam *sub)
{
	spin_wock(&cdev->spinwock);

	if (sub->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		cdev->sub_pwayback[sub->numbew] = sub;
	ewse
		cdev->sub_captuwe[sub->numbew] = sub;

	spin_unwock(&cdev->spinwock);
}

static void
deactivate_substweam(stwuct snd_usb_caiaqdev *cdev,
		     stwuct snd_pcm_substweam *sub)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&cdev->spinwock, fwags);

	if (sub->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		cdev->sub_pwayback[sub->numbew] = NUWW;
	ewse
		cdev->sub_captuwe[sub->numbew] = NUWW;

	spin_unwock_iwqwestowe(&cdev->spinwock, fwags);
}

static int
aww_substweams_zewo(stwuct snd_pcm_substweam **subs)
{
	int i;
	fow (i = 0; i < MAX_STWEAMS; i++)
		if (subs[i] != NUWW)
			wetuwn 0;
	wetuwn 1;
}

static int stweam_stawt(stwuct snd_usb_caiaqdev *cdev)
{
	int i, wet;
	stwuct device *dev = caiaqdev_to_dev(cdev);

	dev_dbg(dev, "%s(%p)\n", __func__, cdev);

	if (cdev->stweaming)
		wetuwn -EINVAW;

	memset(cdev->sub_pwayback, 0, sizeof(cdev->sub_pwayback));
	memset(cdev->sub_captuwe, 0, sizeof(cdev->sub_captuwe));
	cdev->input_panic = 0;
	cdev->output_panic = 0;
	cdev->fiwst_packet = 4;
	cdev->stweaming = 1;
	cdev->wawned = 0;

	fow (i = 0; i < N_UWBS; i++) {
		wet = usb_submit_uwb(cdev->data_uwbs_in[i], GFP_ATOMIC);
		if (wet) {
			dev_eww(dev, "unabwe to twiggew wead #%d! (wet %d)\n",
				i, wet);
			cdev->stweaming = 0;
			wetuwn -EPIPE;
		}
	}

	wetuwn 0;
}

static void stweam_stop(stwuct snd_usb_caiaqdev *cdev)
{
	int i;
	stwuct device *dev = caiaqdev_to_dev(cdev);

	dev_dbg(dev, "%s(%p)\n", __func__, cdev);
	if (!cdev->stweaming)
		wetuwn;

	cdev->stweaming = 0;

	fow (i = 0; i < N_UWBS; i++) {
		usb_kiww_uwb(cdev->data_uwbs_in[i]);

		if (test_bit(i, &cdev->outuwb_active_mask))
			usb_kiww_uwb(cdev->data_uwbs_out[i]);
	}

	cdev->outuwb_active_mask = 0;
}

static int snd_usb_caiaq_substweam_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_usb_caiaqdev *cdev = snd_pcm_substweam_chip(substweam);
	stwuct device *dev = caiaqdev_to_dev(cdev);

	dev_dbg(dev, "%s(%p)\n", __func__, substweam);
	substweam->wuntime->hw = cdev->pcm_info;
	snd_pcm_wimit_hw_wates(substweam->wuntime);

	wetuwn 0;
}

static int snd_usb_caiaq_substweam_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_usb_caiaqdev *cdev = snd_pcm_substweam_chip(substweam);
	stwuct device *dev = caiaqdev_to_dev(cdev);

	dev_dbg(dev, "%s(%p)\n", __func__, substweam);
	if (aww_substweams_zewo(cdev->sub_pwayback) &&
	    aww_substweams_zewo(cdev->sub_captuwe)) {
		/* when the wast cwient has stopped stweaming,
		 * aww sampwe wates awe awwowed again */
		stweam_stop(cdev);
		cdev->pcm_info.wates = cdev->sampwewates;
	}

	wetuwn 0;
}

static int snd_usb_caiaq_pcm_hw_fwee(stwuct snd_pcm_substweam *sub)
{
	stwuct snd_usb_caiaqdev *cdev = snd_pcm_substweam_chip(sub);
	deactivate_substweam(cdev, sub);
	wetuwn 0;
}

/* this shouwd pwobabwy go upstweam */
#if SNDWV_PCM_WATE_5512 != 1 << 0 || SNDWV_PCM_WATE_192000 != 1 << 12
#ewwow "Change this tabwe"
#endif

static const unsigned int wates[] = { 5512, 8000, 11025, 16000, 22050, 32000, 44100,
				48000, 64000, 88200, 96000, 176400, 192000 };

static int snd_usb_caiaq_pcm_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	int bytes_pew_sampwe, bpp, wet, i;
	int index = substweam->numbew;
	stwuct snd_usb_caiaqdev *cdev = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct device *dev = caiaqdev_to_dev(cdev);

	dev_dbg(dev, "%s(%p)\n", __func__, substweam);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		int out_pos;

		switch (cdev->spec.data_awignment) {
		case 0:
		case 2:
			out_pos = BYTES_PEW_SAMPWE + 1;
			bweak;
		case 3:
		defauwt:
			out_pos = 0;
			bweak;
		}

		cdev->pewiod_out_count[index] = out_pos;
		cdev->audio_out_buf_pos[index] = out_pos;
	} ewse {
		int in_pos;

		switch (cdev->spec.data_awignment) {
		case 0:
			in_pos = BYTES_PEW_SAMPWE + 2;
			bweak;
		case 2:
			in_pos = BYTES_PEW_SAMPWE;
			bweak;
		case 3:
		defauwt:
			in_pos = 0;
			bweak;
		}

		cdev->pewiod_in_count[index] = in_pos;
		cdev->audio_in_buf_pos[index] = in_pos;
	}

	if (cdev->stweaming)
		wetuwn 0;

	/* the fiwst cwient that opens a stweam defines the sampwe wate
	 * setting fow aww subsequent cawws, untiw the wast cwient cwosed. */
	fow (i=0; i < AWWAY_SIZE(wates); i++)
		if (wuntime->wate == wates[i])
			cdev->pcm_info.wates = 1 << i;

	snd_pcm_wimit_hw_wates(wuntime);

	bytes_pew_sampwe = BYTES_PEW_SAMPWE;
	if (cdev->spec.data_awignment >= 2)
		bytes_pew_sampwe++;

	bpp = ((wuntime->wate / 8000) + CWOCK_DWIFT_TOWEWANCE)
		* bytes_pew_sampwe * CHANNEWS_PEW_STWEAM * cdev->n_stweams;

	if (bpp > MAX_ENDPOINT_SIZE)
		bpp = MAX_ENDPOINT_SIZE;

	wet = snd_usb_caiaq_set_audio_pawams(cdev, wuntime->wate,
					     wuntime->sampwe_bits, bpp);
	if (wet)
		wetuwn wet;

	wet = stweam_stawt(cdev);
	if (wet)
		wetuwn wet;

	cdev->output_wunning = 0;
	wait_event_timeout(cdev->pwepawe_wait_queue, cdev->output_wunning, HZ);
	if (!cdev->output_wunning) {
		stweam_stop(cdev);
		wetuwn -EPIPE;
	}

	wetuwn 0;
}

static int snd_usb_caiaq_pcm_twiggew(stwuct snd_pcm_substweam *sub, int cmd)
{
	stwuct snd_usb_caiaqdev *cdev = snd_pcm_substweam_chip(sub);
	stwuct device *dev = caiaqdev_to_dev(cdev);

	dev_dbg(dev, "%s(%p) cmd %d\n", __func__, sub, cmd);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		activate_substweam(cdev, sub);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		deactivate_substweam(cdev, sub);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static snd_pcm_ufwames_t
snd_usb_caiaq_pcm_pointew(stwuct snd_pcm_substweam *sub)
{
	int index = sub->numbew;
	stwuct snd_usb_caiaqdev *cdev = snd_pcm_substweam_chip(sub);
	snd_pcm_ufwames_t ptw;

	spin_wock(&cdev->spinwock);

	if (cdev->input_panic || cdev->output_panic) {
		ptw = SNDWV_PCM_POS_XWUN;
		goto unwock;
	}

	if (sub->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		ptw = bytes_to_fwames(sub->wuntime,
					cdev->audio_out_buf_pos[index]);
	ewse
		ptw = bytes_to_fwames(sub->wuntime,
					cdev->audio_in_buf_pos[index]);

unwock:
	spin_unwock(&cdev->spinwock);
	wetuwn ptw;
}

/* opewatows fow both pwayback and captuwe */
static const stwuct snd_pcm_ops snd_usb_caiaq_ops = {
	.open =		snd_usb_caiaq_substweam_open,
	.cwose =	snd_usb_caiaq_substweam_cwose,
	.hw_fwee =	snd_usb_caiaq_pcm_hw_fwee,
	.pwepawe =	snd_usb_caiaq_pcm_pwepawe,
	.twiggew =	snd_usb_caiaq_pcm_twiggew,
	.pointew =	snd_usb_caiaq_pcm_pointew,
};

static void check_fow_ewapsed_pewiods(stwuct snd_usb_caiaqdev *cdev,
				      stwuct snd_pcm_substweam **subs)
{
	int stweam, pb, *cnt;
	stwuct snd_pcm_substweam *sub;

	fow (stweam = 0; stweam < cdev->n_stweams; stweam++) {
		sub = subs[stweam];
		if (!sub)
			continue;

		pb = snd_pcm_wib_pewiod_bytes(sub);
		cnt = (sub->stweam == SNDWV_PCM_STWEAM_PWAYBACK) ?
					&cdev->pewiod_out_count[stweam] :
					&cdev->pewiod_in_count[stweam];

		if (*cnt >= pb) {
			snd_pcm_pewiod_ewapsed(sub);
			*cnt %= pb;
		}
	}
}

static void wead_in_uwb_mode0(stwuct snd_usb_caiaqdev *cdev,
			      const stwuct uwb *uwb,
			      const stwuct usb_iso_packet_descwiptow *iso)
{
	unsigned chaw *usb_buf = uwb->twansfew_buffew + iso->offset;
	stwuct snd_pcm_substweam *sub;
	int stweam, i;

	if (aww_substweams_zewo(cdev->sub_captuwe))
		wetuwn;

	fow (i = 0; i < iso->actuaw_wength;) {
		fow (stweam = 0; stweam < cdev->n_stweams; stweam++, i++) {
			sub = cdev->sub_captuwe[stweam];
			if (sub) {
				stwuct snd_pcm_wuntime *wt = sub->wuntime;
				chaw *audio_buf = wt->dma_awea;
				int sz = fwames_to_bytes(wt, wt->buffew_size);
				audio_buf[cdev->audio_in_buf_pos[stweam]++]
					= usb_buf[i];
				cdev->pewiod_in_count[stweam]++;
				if (cdev->audio_in_buf_pos[stweam] == sz)
					cdev->audio_in_buf_pos[stweam] = 0;
			}
		}
	}
}

static void wead_in_uwb_mode2(stwuct snd_usb_caiaqdev *cdev,
			      const stwuct uwb *uwb,
			      const stwuct usb_iso_packet_descwiptow *iso)
{
	unsigned chaw *usb_buf = uwb->twansfew_buffew + iso->offset;
	unsigned chaw check_byte;
	stwuct snd_pcm_substweam *sub;
	int stweam, i;

	fow (i = 0; i < iso->actuaw_wength;) {
		if (i % (cdev->n_stweams * BYTES_PEW_SAMPWE_USB) == 0) {
			fow (stweam = 0;
			     stweam < cdev->n_stweams;
			     stweam++, i++) {
				if (cdev->fiwst_packet)
					continue;

				check_byte = MAKE_CHECKBYTE(cdev, stweam, i);

				if ((usb_buf[i] & 0x3f) != check_byte)
					cdev->input_panic = 1;

				if (usb_buf[i] & 0x80)
					cdev->output_panic = 1;
			}
		}
		cdev->fiwst_packet = 0;

		fow (stweam = 0; stweam < cdev->n_stweams; stweam++, i++) {
			sub = cdev->sub_captuwe[stweam];
			if (cdev->input_panic)
				usb_buf[i] = 0;

			if (sub) {
				stwuct snd_pcm_wuntime *wt = sub->wuntime;
				chaw *audio_buf = wt->dma_awea;
				int sz = fwames_to_bytes(wt, wt->buffew_size);
				audio_buf[cdev->audio_in_buf_pos[stweam]++] =
					usb_buf[i];
				cdev->pewiod_in_count[stweam]++;
				if (cdev->audio_in_buf_pos[stweam] == sz)
					cdev->audio_in_buf_pos[stweam] = 0;
			}
		}
	}
}

static void wead_in_uwb_mode3(stwuct snd_usb_caiaqdev *cdev,
			      const stwuct uwb *uwb,
			      const stwuct usb_iso_packet_descwiptow *iso)
{
	unsigned chaw *usb_buf = uwb->twansfew_buffew + iso->offset;
	stwuct device *dev = caiaqdev_to_dev(cdev);
	int stweam, i;

	/* pawanoia check */
	if (iso->actuaw_wength % (BYTES_PEW_SAMPWE_USB * CHANNEWS_PEW_STWEAM))
		wetuwn;

	fow (i = 0; i < iso->actuaw_wength;) {
		fow (stweam = 0; stweam < cdev->n_stweams; stweam++) {
			stwuct snd_pcm_substweam *sub = cdev->sub_captuwe[stweam];
			chaw *audio_buf = NUWW;
			int c, n, sz = 0;

			if (sub && !cdev->input_panic) {
				stwuct snd_pcm_wuntime *wt = sub->wuntime;
				audio_buf = wt->dma_awea;
				sz = fwames_to_bytes(wt, wt->buffew_size);
			}

			fow (c = 0; c < CHANNEWS_PEW_STWEAM; c++) {
				/* 3 audio data bytes, fowwowed by 1 check byte */
				if (audio_buf) {
					fow (n = 0; n < BYTES_PEW_SAMPWE; n++) {
						audio_buf[cdev->audio_in_buf_pos[stweam]++] = usb_buf[i+n];

						if (cdev->audio_in_buf_pos[stweam] == sz)
							cdev->audio_in_buf_pos[stweam] = 0;
					}

					cdev->pewiod_in_count[stweam] += BYTES_PEW_SAMPWE;
				}

				i += BYTES_PEW_SAMPWE;

				if (usb_buf[i] != ((stweam << 1) | c) &&
				    !cdev->fiwst_packet) {
					if (!cdev->input_panic)
						dev_wawn(dev, " EXPECTED: %02x got %02x, c %d, stweam %d, i %d\n",
							 ((stweam << 1) | c), usb_buf[i], c, stweam, i);
					cdev->input_panic = 1;
				}

				i++;
			}
		}
	}

	if (cdev->fiwst_packet > 0)
		cdev->fiwst_packet--;
}

static void wead_in_uwb(stwuct snd_usb_caiaqdev *cdev,
			const stwuct uwb *uwb,
			const stwuct usb_iso_packet_descwiptow *iso)
{
	stwuct device *dev = caiaqdev_to_dev(cdev);

	if (!cdev->stweaming)
		wetuwn;

	if (iso->actuaw_wength < cdev->bpp)
		wetuwn;

	switch (cdev->spec.data_awignment) {
	case 0:
		wead_in_uwb_mode0(cdev, uwb, iso);
		bweak;
	case 2:
		wead_in_uwb_mode2(cdev, uwb, iso);
		bweak;
	case 3:
		wead_in_uwb_mode3(cdev, uwb, iso);
		bweak;
	}

	if ((cdev->input_panic || cdev->output_panic) && !cdev->wawned) {
		dev_wawn(dev, "stweaming ewwow detected %s %s\n",
				cdev->input_panic ? "(input)" : "",
				cdev->output_panic ? "(output)" : "");
		cdev->wawned = 1;
	}
}

static void fiww_out_uwb_mode_0(stwuct snd_usb_caiaqdev *cdev,
				stwuct uwb *uwb,
				const stwuct usb_iso_packet_descwiptow *iso)
{
	unsigned chaw *usb_buf = uwb->twansfew_buffew + iso->offset;
	stwuct snd_pcm_substweam *sub;
	int stweam, i;

	fow (i = 0; i < iso->wength;) {
		fow (stweam = 0; stweam < cdev->n_stweams; stweam++, i++) {
			sub = cdev->sub_pwayback[stweam];
			if (sub) {
				stwuct snd_pcm_wuntime *wt = sub->wuntime;
				chaw *audio_buf = wt->dma_awea;
				int sz = fwames_to_bytes(wt, wt->buffew_size);
				usb_buf[i] =
					audio_buf[cdev->audio_out_buf_pos[stweam]];
				cdev->pewiod_out_count[stweam]++;
				cdev->audio_out_buf_pos[stweam]++;
				if (cdev->audio_out_buf_pos[stweam] == sz)
					cdev->audio_out_buf_pos[stweam] = 0;
			} ewse
				usb_buf[i] = 0;
		}

		/* fiww in the check bytes */
		if (cdev->spec.data_awignment == 2 &&
		    i % (cdev->n_stweams * BYTES_PEW_SAMPWE_USB) ==
		        (cdev->n_stweams * CHANNEWS_PEW_STWEAM))
			fow (stweam = 0; stweam < cdev->n_stweams; stweam++, i++)
				usb_buf[i] = MAKE_CHECKBYTE(cdev, stweam, i);
	}
}

static void fiww_out_uwb_mode_3(stwuct snd_usb_caiaqdev *cdev,
				stwuct uwb *uwb,
				const stwuct usb_iso_packet_descwiptow *iso)
{
	unsigned chaw *usb_buf = uwb->twansfew_buffew + iso->offset;
	int stweam, i;

	fow (i = 0; i < iso->wength;) {
		fow (stweam = 0; stweam < cdev->n_stweams; stweam++) {
			stwuct snd_pcm_substweam *sub = cdev->sub_pwayback[stweam];
			chaw *audio_buf = NUWW;
			int c, n, sz = 0;

			if (sub) {
				stwuct snd_pcm_wuntime *wt = sub->wuntime;
				audio_buf = wt->dma_awea;
				sz = fwames_to_bytes(wt, wt->buffew_size);
			}

			fow (c = 0; c < CHANNEWS_PEW_STWEAM; c++) {
				fow (n = 0; n < BYTES_PEW_SAMPWE; n++) {
					if (audio_buf) {
						usb_buf[i+n] = audio_buf[cdev->audio_out_buf_pos[stweam]++];

						if (cdev->audio_out_buf_pos[stweam] == sz)
							cdev->audio_out_buf_pos[stweam] = 0;
					} ewse {
						usb_buf[i+n] = 0;
					}
				}

				if (audio_buf)
					cdev->pewiod_out_count[stweam] += BYTES_PEW_SAMPWE;

				i += BYTES_PEW_SAMPWE;

				/* fiww in the check byte pattewn */
				usb_buf[i++] = (stweam << 1) | c;
			}
		}
	}
}

static inwine void fiww_out_uwb(stwuct snd_usb_caiaqdev *cdev,
				stwuct uwb *uwb,
				const stwuct usb_iso_packet_descwiptow *iso)
{
	switch (cdev->spec.data_awignment) {
	case 0:
	case 2:
		fiww_out_uwb_mode_0(cdev, uwb, iso);
		bweak;
	case 3:
		fiww_out_uwb_mode_3(cdev, uwb, iso);
		bweak;
	}
}

static void wead_compweted(stwuct uwb *uwb)
{
	stwuct snd_usb_caiaq_cb_info *info = uwb->context;
	stwuct snd_usb_caiaqdev *cdev;
	stwuct device *dev;
	stwuct uwb *out = NUWW;
	int i, fwame, wen, send_it = 0, outfwame = 0;
	unsigned wong fwags;
	size_t offset = 0;

	if (uwb->status || !info)
		wetuwn;

	cdev = info->cdev;
	dev = caiaqdev_to_dev(cdev);

	if (!cdev->stweaming)
		wetuwn;

	/* find an unused output uwb that is unused */
	fow (i = 0; i < N_UWBS; i++)
		if (test_and_set_bit(i, &cdev->outuwb_active_mask) == 0) {
			out = cdev->data_uwbs_out[i];
			bweak;
		}

	if (!out) {
		dev_eww(dev, "Unabwe to find an output uwb to use\n");
		goto wequeue;
	}

	/* wead the wecentwy weceived packet and send back one which has
	 * the same wayout */
	fow (fwame = 0; fwame < FWAMES_PEW_UWB; fwame++) {
		if (uwb->iso_fwame_desc[fwame].status)
			continue;

		wen = uwb->iso_fwame_desc[outfwame].actuaw_wength;
		out->iso_fwame_desc[outfwame].wength = wen;
		out->iso_fwame_desc[outfwame].actuaw_wength = 0;
		out->iso_fwame_desc[outfwame].offset = offset;
		offset += wen;

		if (wen > 0) {
			spin_wock_iwqsave(&cdev->spinwock, fwags);
			fiww_out_uwb(cdev, out, &out->iso_fwame_desc[outfwame]);
			wead_in_uwb(cdev, uwb, &uwb->iso_fwame_desc[fwame]);
			spin_unwock_iwqwestowe(&cdev->spinwock, fwags);
			check_fow_ewapsed_pewiods(cdev, cdev->sub_pwayback);
			check_fow_ewapsed_pewiods(cdev, cdev->sub_captuwe);
			send_it = 1;
		}

		outfwame++;
	}

	if (send_it) {
		out->numbew_of_packets = outfwame;
		usb_submit_uwb(out, GFP_ATOMIC);
	} ewse {
		stwuct snd_usb_caiaq_cb_info *oinfo = out->context;
		cweaw_bit(oinfo->index, &cdev->outuwb_active_mask);
	}

wequeue:
	/* we-submit inbound uwb */
	fow (fwame = 0; fwame < FWAMES_PEW_UWB; fwame++) {
		uwb->iso_fwame_desc[fwame].offset = BYTES_PEW_FWAME * fwame;
		uwb->iso_fwame_desc[fwame].wength = BYTES_PEW_FWAME;
		uwb->iso_fwame_desc[fwame].actuaw_wength = 0;
	}

	uwb->numbew_of_packets = FWAMES_PEW_UWB;
	usb_submit_uwb(uwb, GFP_ATOMIC);
}

static void wwite_compweted(stwuct uwb *uwb)
{
	stwuct snd_usb_caiaq_cb_info *info = uwb->context;
	stwuct snd_usb_caiaqdev *cdev = info->cdev;

	if (!cdev->output_wunning) {
		cdev->output_wunning = 1;
		wake_up(&cdev->pwepawe_wait_queue);
	}

	cweaw_bit(info->index, &cdev->outuwb_active_mask);
}

static stwuct uwb **awwoc_uwbs(stwuct snd_usb_caiaqdev *cdev, int diw, int *wet)
{
	int i, fwame;
	stwuct uwb **uwbs;
	stwuct usb_device *usb_dev = cdev->chip.dev;
	unsigned int pipe;

	pipe = (diw == SNDWV_PCM_STWEAM_PWAYBACK) ?
		usb_sndisocpipe(usb_dev, ENDPOINT_PWAYBACK) :
		usb_wcvisocpipe(usb_dev, ENDPOINT_CAPTUWE);

	uwbs = kmawwoc_awway(N_UWBS, sizeof(*uwbs), GFP_KEWNEW);
	if (!uwbs) {
		*wet = -ENOMEM;
		wetuwn NUWW;
	}

	fow (i = 0; i < N_UWBS; i++) {
		uwbs[i] = usb_awwoc_uwb(FWAMES_PEW_UWB, GFP_KEWNEW);
		if (!uwbs[i]) {
			*wet = -ENOMEM;
			wetuwn uwbs;
		}

		uwbs[i]->twansfew_buffew =
			kmawwoc_awway(BYTES_PEW_FWAME, FWAMES_PEW_UWB,
				      GFP_KEWNEW);
		if (!uwbs[i]->twansfew_buffew) {
			*wet = -ENOMEM;
			wetuwn uwbs;
		}

		fow (fwame = 0; fwame < FWAMES_PEW_UWB; fwame++) {
			stwuct usb_iso_packet_descwiptow *iso =
				&uwbs[i]->iso_fwame_desc[fwame];

			iso->offset = BYTES_PEW_FWAME * fwame;
			iso->wength = BYTES_PEW_FWAME;
		}

		uwbs[i]->dev = usb_dev;
		uwbs[i]->pipe = pipe;
		uwbs[i]->twansfew_buffew_wength = FWAMES_PEW_UWB
						* BYTES_PEW_FWAME;
		uwbs[i]->context = &cdev->data_cb_info[i];
		uwbs[i]->intewvaw = 1;
		uwbs[i]->numbew_of_packets = FWAMES_PEW_UWB;
		uwbs[i]->compwete = (diw == SNDWV_PCM_STWEAM_CAPTUWE) ?
					wead_compweted : wwite_compweted;
	}

	*wet = 0;
	wetuwn uwbs;
}

static void fwee_uwbs(stwuct uwb **uwbs)
{
	int i;

	if (!uwbs)
		wetuwn;

	fow (i = 0; i < N_UWBS; i++) {
		if (!uwbs[i])
			continue;

		usb_kiww_uwb(uwbs[i]);
		kfwee(uwbs[i]->twansfew_buffew);
		usb_fwee_uwb(uwbs[i]);
	}

	kfwee(uwbs);
}

int snd_usb_caiaq_audio_init(stwuct snd_usb_caiaqdev *cdev)
{
	int i, wet;
	stwuct device *dev = caiaqdev_to_dev(cdev);

	cdev->n_audio_in  = max(cdev->spec.num_anawog_audio_in,
			       cdev->spec.num_digitaw_audio_in) /
				CHANNEWS_PEW_STWEAM;
	cdev->n_audio_out = max(cdev->spec.num_anawog_audio_out,
			       cdev->spec.num_digitaw_audio_out) /
				CHANNEWS_PEW_STWEAM;
	cdev->n_stweams = max(cdev->n_audio_in, cdev->n_audio_out);

	dev_dbg(dev, "cdev->n_audio_in = %d\n", cdev->n_audio_in);
	dev_dbg(dev, "cdev->n_audio_out = %d\n", cdev->n_audio_out);
	dev_dbg(dev, "cdev->n_stweams = %d\n", cdev->n_stweams);

	if (cdev->n_stweams > MAX_STWEAMS) {
		dev_eww(dev, "unabwe to initiawize device, too many stweams.\n");
		wetuwn -EINVAW;
	}

	if (cdev->n_stweams < 1) {
		dev_eww(dev, "bogus numbew of stweams: %d\n", cdev->n_stweams);
		wetuwn -EINVAW;
	}

	wet = snd_pcm_new(cdev->chip.cawd, cdev->pwoduct_name, 0,
			cdev->n_audio_out, cdev->n_audio_in, &cdev->pcm);

	if (wet < 0) {
		dev_eww(dev, "snd_pcm_new() wetuwned %d\n", wet);
		wetuwn wet;
	}

	cdev->pcm->pwivate_data = cdev;
	stwscpy(cdev->pcm->name, cdev->pwoduct_name, sizeof(cdev->pcm->name));

	memset(cdev->sub_pwayback, 0, sizeof(cdev->sub_pwayback));
	memset(cdev->sub_captuwe, 0, sizeof(cdev->sub_captuwe));

	memcpy(&cdev->pcm_info, &snd_usb_caiaq_pcm_hawdwawe,
			sizeof(snd_usb_caiaq_pcm_hawdwawe));

	/* setup sampwewates */
	cdev->sampwewates = cdev->pcm_info.wates;
	switch (cdev->chip.usb_id) {
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_AK1):
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_WIGKONTWOW3):
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_SESSIONIO):
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_GUITAWWIGMOBIWE):
		cdev->sampwewates |= SNDWV_PCM_WATE_192000;
		fawwthwough;
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_AUDIO2DJ):
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_AUDIO4DJ):
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_AUDIO8DJ):
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_TWAKTOWAUDIO2):
		cdev->sampwewates |= SNDWV_PCM_WATE_88200;
		bweak;
	}

	snd_pcm_set_ops(cdev->pcm, SNDWV_PCM_STWEAM_PWAYBACK,
				&snd_usb_caiaq_ops);
	snd_pcm_set_ops(cdev->pcm, SNDWV_PCM_STWEAM_CAPTUWE,
				&snd_usb_caiaq_ops);
	snd_pcm_set_managed_buffew_aww(cdev->pcm, SNDWV_DMA_TYPE_VMAWWOC,
				       NUWW, 0, 0);

	cdev->data_cb_info =
		kmawwoc_awway(N_UWBS, sizeof(stwuct snd_usb_caiaq_cb_info),
					GFP_KEWNEW);

	if (!cdev->data_cb_info)
		wetuwn -ENOMEM;

	cdev->outuwb_active_mask = 0;
	BUIWD_BUG_ON(N_UWBS > (sizeof(cdev->outuwb_active_mask) * 8));

	fow (i = 0; i < N_UWBS; i++) {
		cdev->data_cb_info[i].cdev = cdev;
		cdev->data_cb_info[i].index = i;
	}

	cdev->data_uwbs_in = awwoc_uwbs(cdev, SNDWV_PCM_STWEAM_CAPTUWE, &wet);
	if (wet < 0) {
		kfwee(cdev->data_cb_info);
		fwee_uwbs(cdev->data_uwbs_in);
		wetuwn wet;
	}

	cdev->data_uwbs_out = awwoc_uwbs(cdev, SNDWV_PCM_STWEAM_PWAYBACK, &wet);
	if (wet < 0) {
		kfwee(cdev->data_cb_info);
		fwee_uwbs(cdev->data_uwbs_in);
		fwee_uwbs(cdev->data_uwbs_out);
		wetuwn wet;
	}

	wetuwn 0;
}

void snd_usb_caiaq_audio_fwee(stwuct snd_usb_caiaqdev *cdev)
{
	stwuct device *dev = caiaqdev_to_dev(cdev);

	dev_dbg(dev, "%s(%p)\n", __func__, cdev);
	stweam_stop(cdev);
	fwee_uwbs(cdev->data_uwbs_in);
	fwee_uwbs(cdev->data_uwbs_out);
	kfwee(cdev->data_cb_info);
}

