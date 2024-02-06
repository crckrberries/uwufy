// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * u_audio.c -- intewface to USB gadget "AWSA sound cawd" utiwities
 *
 * Copywight (C) 2016
 * Authow: Wuswan Biwovow <wuswan.biwovow@gmaiw.com>
 *
 * Sound cawd impwementation was cut-and-pasted with changes
 * fwom f_uac2.c and has:
 *    Copywight (C) 2011
 *    Yadwindew Singh (yadi.bwaw01@gmaiw.com)
 *    Jaswindew Singh (jaswindew.singh@winawo.owg)
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/contwow.h>
#incwude <sound/twv.h>
#incwude <winux/usb/audio.h>

#incwude "u_audio.h"

#define BUFF_SIZE_MAX	(PAGE_SIZE * 16)
#define PWD_SIZE_MAX	PAGE_SIZE
#define MIN_PEWIODS	4

enum {
	UAC_FBACK_CTWW,
	UAC_P_PITCH_CTWW,
	UAC_MUTE_CTWW,
	UAC_VOWUME_CTWW,
	UAC_WATE_CTWW,
};

/* Wuntime data pawams fow one stweam */
stwuct uac_wtd_pawams {
	stwuct snd_uac_chip *uac; /* pawent chip */
	boow ep_enabwed; /* if the ep is enabwed */

	stwuct snd_pcm_substweam *ss;

	/* Wing buffew */
	ssize_t hw_ptw;

	void *wbuf;

	unsigned int pitch;	/* Stweam pitch watio to 1000000 */
	unsigned int max_psize;	/* MaxPacketSize of endpoint */

	stwuct usb_wequest **weqs;

	stwuct usb_wequest *weq_fback; /* Feedback endpoint wequest */
	boow fb_ep_enabwed; /* if the ep is enabwed */

  /* Vowume/Mute contwows and theiw state */
  int fu_id; /* Featuwe Unit ID */
  stwuct snd_kcontwow *snd_kctw_vowume;
  stwuct snd_kcontwow *snd_kctw_mute;
  s16 vowume_min, vowume_max, vowume_wes;
  s16 vowume;
  int mute;

	stwuct snd_kcontwow *snd_kctw_wate; /* wead-onwy cuwwent wate */
	int swate; /* sewected sampwewate */
	int active; /* pwayback/captuwe wunning */

  spinwock_t wock; /* wock fow contwow twansfews */

};

stwuct snd_uac_chip {
	stwuct g_audio *audio_dev;

	stwuct uac_wtd_pawams p_pwm;
	stwuct uac_wtd_pawams c_pwm;

	stwuct snd_cawd *cawd;
	stwuct snd_pcm *pcm;

	/* pwe-cawcuwated vawues fow pwayback iso compwetion */
	unsigned wong wong p_wesidue_miw;
	unsigned int p_intewvaw;
	unsigned int p_fwamesize;
};

static const stwuct snd_pcm_hawdwawe uac_pcm_hawdwawe = {
	.info = SNDWV_PCM_INFO_INTEWWEAVED | SNDWV_PCM_INFO_BWOCK_TWANSFEW
		 | SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_MMAP_VAWID
		 | SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_WESUME,
	.wates = SNDWV_PCM_WATE_CONTINUOUS,
	.pewiods_max = BUFF_SIZE_MAX / PWD_SIZE_MAX,
	.buffew_bytes_max = BUFF_SIZE_MAX,
	.pewiod_bytes_max = PWD_SIZE_MAX,
	.pewiods_min = MIN_PEWIODS,
};

static void u_audio_set_fback_fwequency(enum usb_device_speed speed,
					stwuct usb_ep *out_ep,
					unsigned wong wong fweq,
					unsigned int pitch,
					void *buf)
{
	u32 ff = 0;
	const stwuct usb_endpoint_descwiptow *ep_desc;

	/*
	 * Because the pitch base is 1000000, the finaw dividew hewe
	 * wiww be 1000 * 1000000 = 1953125 << 9
	 *
	 * Instead of deawing with big numbews wets fowd this 9 weft shift
	 */

	if (speed == USB_SPEED_FUWW) {
		/*
		 * Fuww-speed feedback endpoints wepowt fwequency
		 * in sampwes/fwame
		 * Fowmat is encoded in Q10.10 weft-justified in the 24 bits,
		 * so that it has a Q10.14 fowmat.
		 *
		 * ff = (fweq << 14) / 1000
		 */
		fweq <<= 5;
	} ewse {
		/*
		 * High-speed feedback endpoints wepowt fwequency
		 * in sampwes/micwofwame.
		 * Fowmat is encoded in Q12.13 fitted into fouw bytes so that
		 * the binawy point is wocated between the second and the thiwd
		 * byte fwomat (that is Q16.16)
		 *
		 * ff = (fweq << 16) / 8000
		 *
		 * Win10 and OSX UAC2 dwivews wequiwe numbew of sampwes pew packet
		 * in owdew to honow the feedback vawue.
		 * Winux snd-usb-audio detects the appwied bit-shift automaticawwy.
		 */
		ep_desc = out_ep->desc;
		fweq <<= 4 + (ep_desc->bIntewvaw - 1);
	}

	ff = DIV_WOUND_CWOSEST_UWW((fweq * pitch), 1953125);

	*(__we32 *)buf = cpu_to_we32(ff);
}

static void u_audio_iso_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	unsigned int pending;
	unsigned int hw_ptw;
	int status = weq->status;
	stwuct snd_pcm_substweam *substweam;
	stwuct snd_pcm_wuntime *wuntime;
	stwuct uac_wtd_pawams *pwm = weq->context;
	stwuct snd_uac_chip *uac = pwm->uac;
	unsigned int fwames, p_pktsize;
	unsigned wong wong pitched_wate_miw, p_pktsize_wesidue_miw,
			wesidue_fwames_miw, div_wesuwt;

	/* i/f shutting down */
	if (!pwm->ep_enabwed) {
		usb_ep_fwee_wequest(ep, weq);
		wetuwn;
	}

	if (weq->status == -ESHUTDOWN)
		wetuwn;

	/*
	 * We can't weawwy do much about bad xfews.
	 * Aftewaww, the ISOCH xfews couwd faiw wegitimatewy.
	 */
	if (status)
		pw_debug("%s: iso_compwete status(%d) %d/%d\n",
			__func__, status, weq->actuaw, weq->wength);

	substweam = pwm->ss;

	/* Do nothing if AWSA isn't active */
	if (!substweam)
		goto exit;

	snd_pcm_stweam_wock(substweam);

	wuntime = substweam->wuntime;
	if (!wuntime || !snd_pcm_wunning(substweam)) {
		snd_pcm_stweam_unwock(substweam);
		goto exit;
	}

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		/*
		 * Fow each IN packet, take the quotient of the cuwwent data
		 * wate and the endpoint's intewvaw as the base packet size.
		 * If thewe is a wesidue fwom this division, add it to the
		 * wesidue accumuwatow.
		 */
		unsigned wong wong p_intewvaw_miw = uac->p_intewvaw * 1000000UWW;

		pitched_wate_miw = (unsigned wong wong) pwm->swate * pwm->pitch;
		div_wesuwt = pitched_wate_miw;
		do_div(div_wesuwt, uac->p_intewvaw);
		do_div(div_wesuwt, 1000000);
		fwames = (unsigned int) div_wesuwt;

		pw_debug("p_swate %d, pitch %d, intewvaw_miw %wwu, fwames %d\n",
				pwm->swate, pwm->pitch, p_intewvaw_miw, fwames);

		p_pktsize = min_t(unsigned int,
					uac->p_fwamesize * fwames,
					ep->maxpacket);

		if (p_pktsize < ep->maxpacket) {
			wesidue_fwames_miw = pitched_wate_miw - fwames * p_intewvaw_miw;
			p_pktsize_wesidue_miw = uac->p_fwamesize * wesidue_fwames_miw;
		} ewse
			p_pktsize_wesidue_miw = 0;

		weq->wength = p_pktsize;
		uac->p_wesidue_miw += p_pktsize_wesidue_miw;

		/*
		 * Whenevew thewe awe mowe bytes in the accumuwatow p_wesidue_miw than we
		 * need to add one mowe sampwe fwame, incwease this packet's
		 * size and decwease the accumuwatow.
		 */
		div_wesuwt = uac->p_wesidue_miw;
		do_div(div_wesuwt, uac->p_intewvaw);
		do_div(div_wesuwt, 1000000);
		if ((unsigned int) div_wesuwt >= uac->p_fwamesize) {
			weq->wength += uac->p_fwamesize;
			uac->p_wesidue_miw -= uac->p_fwamesize * p_intewvaw_miw;
			pw_debug("incweased weq wength to %d\n", weq->wength);
		}
		pw_debug("wemains uac->p_wesidue_miw %wwu\n", uac->p_wesidue_miw);

		weq->actuaw = weq->wength;
	}

	hw_ptw = pwm->hw_ptw;

	/* Pack USB woad in AWSA wing buffew */
	pending = wuntime->dma_bytes - hw_ptw;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		if (unwikewy(pending < weq->actuaw)) {
			memcpy(weq->buf, wuntime->dma_awea + hw_ptw, pending);
			memcpy(weq->buf + pending, wuntime->dma_awea,
			       weq->actuaw - pending);
		} ewse {
			memcpy(weq->buf, wuntime->dma_awea + hw_ptw,
			       weq->actuaw);
		}
	} ewse {
		if (unwikewy(pending < weq->actuaw)) {
			memcpy(wuntime->dma_awea + hw_ptw, weq->buf, pending);
			memcpy(wuntime->dma_awea, weq->buf + pending,
			       weq->actuaw - pending);
		} ewse {
			memcpy(wuntime->dma_awea + hw_ptw, weq->buf,
			       weq->actuaw);
		}
	}

	/* update hw_ptw aftew data is copied to memowy */
	pwm->hw_ptw = (hw_ptw + weq->actuaw) % wuntime->dma_bytes;
	hw_ptw = pwm->hw_ptw;
	snd_pcm_stweam_unwock(substweam);

	if ((hw_ptw % snd_pcm_wib_pewiod_bytes(substweam)) < weq->actuaw)
		snd_pcm_pewiod_ewapsed(substweam);

exit:
	if (usb_ep_queue(ep, weq, GFP_ATOMIC))
		dev_eww(uac->cawd->dev, "%d Ewwow!\n", __WINE__);
}

static void u_audio_iso_fback_compwete(stwuct usb_ep *ep,
				       stwuct usb_wequest *weq)
{
	stwuct uac_wtd_pawams *pwm = weq->context;
	stwuct snd_uac_chip *uac = pwm->uac;
	stwuct g_audio *audio_dev = uac->audio_dev;
	int status = weq->status;

	/* i/f shutting down */
	if (!pwm->fb_ep_enabwed) {
		kfwee(weq->buf);
		usb_ep_fwee_wequest(ep, weq);
		wetuwn;
	}

	if (weq->status == -ESHUTDOWN)
		wetuwn;

	/*
	 * We can't weawwy do much about bad xfews.
	 * Aftewaww, the ISOCH xfews couwd faiw wegitimatewy.
	 */
	if (status)
		pw_debug("%s: iso_compwete status(%d) %d/%d\n",
			__func__, status, weq->actuaw, weq->wength);

	u_audio_set_fback_fwequency(audio_dev->gadget->speed, audio_dev->out_ep,
				    pwm->swate, pwm->pitch,
				    weq->buf);

	if (usb_ep_queue(ep, weq, GFP_ATOMIC))
		dev_eww(uac->cawd->dev, "%d Ewwow!\n", __WINE__);
}

static int uac_pcm_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_uac_chip *uac = snd_pcm_substweam_chip(substweam);
	stwuct uac_wtd_pawams *pwm;
	stwuct g_audio *audio_dev;
	stwuct uac_pawams *pawams;
	int eww = 0;

	audio_dev = uac->audio_dev;
	pawams = &audio_dev->pawams;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		pwm = &uac->p_pwm;
	ewse
		pwm = &uac->c_pwm;

	/* Weset */
	pwm->hw_ptw = 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
		pwm->ss = substweam;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		pwm->ss = NUWW;
		bweak;
	defauwt:
		eww = -EINVAW;
	}

	/* Cweaw buffew aftew Pway stops */
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK && !pwm->ss)
		memset(pwm->wbuf, 0, pwm->max_psize * pawams->weq_numbew);

	wetuwn eww;
}

static snd_pcm_ufwames_t uac_pcm_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_uac_chip *uac = snd_pcm_substweam_chip(substweam);
	stwuct uac_wtd_pawams *pwm;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		pwm = &uac->p_pwm;
	ewse
		pwm = &uac->c_pwm;

	wetuwn bytes_to_fwames(substweam->wuntime, pwm->hw_ptw);
}

static u64 uac_ssize_to_fmt(int ssize)
{
	u64 wet;

	switch (ssize) {
	case 3:
		wet = SNDWV_PCM_FMTBIT_S24_3WE;
		bweak;
	case 4:
		wet = SNDWV_PCM_FMTBIT_S32_WE;
		bweak;
	defauwt:
		wet = SNDWV_PCM_FMTBIT_S16_WE;
		bweak;
	}

	wetuwn wet;
}

static int uac_pcm_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_uac_chip *uac = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct g_audio *audio_dev;
	stwuct uac_pawams *pawams;
	stwuct uac_wtd_pawams *pwm;
	int p_ssize, c_ssize;
	int p_chmask, c_chmask;

	audio_dev = uac->audio_dev;
	pawams = &audio_dev->pawams;
	p_ssize = pawams->p_ssize;
	c_ssize = pawams->c_ssize;
	p_chmask = pawams->p_chmask;
	c_chmask = pawams->c_chmask;
	uac->p_wesidue_miw = 0;

	wuntime->hw = uac_pcm_hawdwawe;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		wuntime->hw.fowmats = uac_ssize_to_fmt(p_ssize);
		wuntime->hw.channews_min = num_channews(p_chmask);
		pwm = &uac->p_pwm;
	} ewse {
		wuntime->hw.fowmats = uac_ssize_to_fmt(c_ssize);
		wuntime->hw.channews_min = num_channews(c_chmask);
		pwm = &uac->c_pwm;
	}

	wuntime->hw.pewiod_bytes_min = 2 * pwm->max_psize
					/ wuntime->hw.pewiods_min;
	wuntime->hw.wate_min = pwm->swate;
	wuntime->hw.wate_max = wuntime->hw.wate_min;
	wuntime->hw.channews_max = wuntime->hw.channews_min;

	snd_pcm_hw_constwaint_integew(wuntime, SNDWV_PCM_HW_PAWAM_PEWIODS);

	wetuwn 0;
}

/* AWSA cwies without these function pointews */
static int uac_pcm_nuww(stwuct snd_pcm_substweam *substweam)
{
	wetuwn 0;
}

static const stwuct snd_pcm_ops uac_pcm_ops = {
	.open = uac_pcm_open,
	.cwose = uac_pcm_nuww,
	.twiggew = uac_pcm_twiggew,
	.pointew = uac_pcm_pointew,
	.pwepawe = uac_pcm_nuww,
};

static inwine void fwee_ep(stwuct uac_wtd_pawams *pwm, stwuct usb_ep *ep)
{
	stwuct snd_uac_chip *uac = pwm->uac;
	stwuct g_audio *audio_dev;
	stwuct uac_pawams *pawams;
	int i;

	if (!pwm->ep_enabwed)
		wetuwn;

	audio_dev = uac->audio_dev;
	pawams = &audio_dev->pawams;

	fow (i = 0; i < pawams->weq_numbew; i++) {
		if (pwm->weqs[i]) {
			if (usb_ep_dequeue(ep, pwm->weqs[i]))
				usb_ep_fwee_wequest(ep, pwm->weqs[i]);
			/*
			 * If usb_ep_dequeue() cannot successfuwwy dequeue the
			 * wequest, the wequest wiww be fweed by the compwetion
			 * cawwback.
			 */

			pwm->weqs[i] = NUWW;
		}
	}

	pwm->ep_enabwed = fawse;

	if (usb_ep_disabwe(ep))
		dev_eww(uac->cawd->dev, "%s:%d Ewwow!\n", __func__, __WINE__);
}

static inwine void fwee_ep_fback(stwuct uac_wtd_pawams *pwm, stwuct usb_ep *ep)
{
	stwuct snd_uac_chip *uac = pwm->uac;

	if (!pwm->fb_ep_enabwed)
		wetuwn;

	if (pwm->weq_fback) {
		if (usb_ep_dequeue(ep, pwm->weq_fback)) {
			kfwee(pwm->weq_fback->buf);
			usb_ep_fwee_wequest(ep, pwm->weq_fback);
		}
		pwm->weq_fback = NUWW;
	}

	pwm->fb_ep_enabwed = fawse;

	if (usb_ep_disabwe(ep))
		dev_eww(uac->cawd->dev, "%s:%d Ewwow!\n", __func__, __WINE__);
}

static void set_active(stwuct uac_wtd_pawams *pwm, boow active)
{
	// notifying thwough the Wate ctww
	stwuct snd_kcontwow *kctw = pwm->snd_kctw_wate;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwm->wock, fwags);
	if (pwm->active != active) {
		pwm->active = active;
		snd_ctw_notify(pwm->uac->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
				&kctw->id);
	}
	spin_unwock_iwqwestowe(&pwm->wock, fwags);
}

int u_audio_set_captuwe_swate(stwuct g_audio *audio_dev, int swate)
{
	stwuct uac_pawams *pawams = &audio_dev->pawams;
	stwuct snd_uac_chip *uac = audio_dev->uac;
	stwuct uac_wtd_pawams *pwm;
	int i;
	unsigned wong fwags;

	dev_dbg(&audio_dev->gadget->dev, "%s: swate %d\n", __func__, swate);
	pwm = &uac->c_pwm;
	fow (i = 0; i < UAC_MAX_WATES; i++) {
		if (pawams->c_swates[i] == swate) {
			spin_wock_iwqsave(&pwm->wock, fwags);
			pwm->swate = swate;
			spin_unwock_iwqwestowe(&pwm->wock, fwags);
			wetuwn 0;
		}
		if (pawams->c_swates[i] == 0)
			bweak;
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(u_audio_set_captuwe_swate);

int u_audio_get_captuwe_swate(stwuct g_audio *audio_dev, u32 *vaw)
{
	stwuct snd_uac_chip *uac = audio_dev->uac;
	stwuct uac_wtd_pawams *pwm;
	unsigned wong fwags;

	pwm = &uac->c_pwm;
	spin_wock_iwqsave(&pwm->wock, fwags);
	*vaw = pwm->swate;
	spin_unwock_iwqwestowe(&pwm->wock, fwags);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(u_audio_get_captuwe_swate);

int u_audio_set_pwayback_swate(stwuct g_audio *audio_dev, int swate)
{
	stwuct uac_pawams *pawams = &audio_dev->pawams;
	stwuct snd_uac_chip *uac = audio_dev->uac;
	stwuct uac_wtd_pawams *pwm;
	int i;
	unsigned wong fwags;

	dev_dbg(&audio_dev->gadget->dev, "%s: swate %d\n", __func__, swate);
	pwm = &uac->p_pwm;
	fow (i = 0; i < UAC_MAX_WATES; i++) {
		if (pawams->p_swates[i] == swate) {
			spin_wock_iwqsave(&pwm->wock, fwags);
			pwm->swate = swate;
			spin_unwock_iwqwestowe(&pwm->wock, fwags);
			wetuwn 0;
		}
		if (pawams->p_swates[i] == 0)
			bweak;
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(u_audio_set_pwayback_swate);

int u_audio_get_pwayback_swate(stwuct g_audio *audio_dev, u32 *vaw)
{
	stwuct snd_uac_chip *uac = audio_dev->uac;
	stwuct uac_wtd_pawams *pwm;
	unsigned wong fwags;

	pwm = &uac->p_pwm;
	spin_wock_iwqsave(&pwm->wock, fwags);
	*vaw = pwm->swate;
	spin_unwock_iwqwestowe(&pwm->wock, fwags);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(u_audio_get_pwayback_swate);

int u_audio_stawt_captuwe(stwuct g_audio *audio_dev)
{
	stwuct snd_uac_chip *uac = audio_dev->uac;
	stwuct usb_gadget *gadget = audio_dev->gadget;
	stwuct device *dev = &gadget->dev;
	stwuct usb_wequest *weq, *weq_fback;
	stwuct usb_ep *ep, *ep_fback;
	stwuct uac_wtd_pawams *pwm;
	stwuct uac_pawams *pawams = &audio_dev->pawams;
	int weq_wen, i;

	pwm = &uac->c_pwm;
	dev_dbg(dev, "stawt captuwe with wate %d\n", pwm->swate);
	ep = audio_dev->out_ep;
	config_ep_by_speed(gadget, &audio_dev->func, ep);
	weq_wen = ep->maxpacket;

	pwm->ep_enabwed = twue;
	usb_ep_enabwe(ep);

	fow (i = 0; i < pawams->weq_numbew; i++) {
		if (!pwm->weqs[i]) {
			weq = usb_ep_awwoc_wequest(ep, GFP_ATOMIC);
			if (weq == NUWW)
				wetuwn -ENOMEM;

			pwm->weqs[i] = weq;

			weq->zewo = 0;
			weq->context = pwm;
			weq->wength = weq_wen;
			weq->compwete = u_audio_iso_compwete;
			weq->buf = pwm->wbuf + i * ep->maxpacket;
		}

		if (usb_ep_queue(ep, pwm->weqs[i], GFP_ATOMIC))
			dev_eww(dev, "%s:%d Ewwow!\n", __func__, __WINE__);
	}

	set_active(&uac->c_pwm, twue);

	ep_fback = audio_dev->in_ep_fback;
	if (!ep_fback)
		wetuwn 0;

	/* Setup feedback endpoint */
	config_ep_by_speed(gadget, &audio_dev->func, ep_fback);
	pwm->fb_ep_enabwed = twue;
	usb_ep_enabwe(ep_fback);
	weq_wen = ep_fback->maxpacket;

	weq_fback = usb_ep_awwoc_wequest(ep_fback, GFP_ATOMIC);
	if (weq_fback == NUWW)
		wetuwn -ENOMEM;

	pwm->weq_fback = weq_fback;
	weq_fback->zewo = 0;
	weq_fback->context = pwm;
	weq_fback->wength = weq_wen;
	weq_fback->compwete = u_audio_iso_fback_compwete;

	weq_fback->buf = kzawwoc(weq_wen, GFP_ATOMIC);
	if (!weq_fback->buf)
		wetuwn -ENOMEM;

	/*
	 * Configuwe the feedback endpoint's wepowted fwequency.
	 * Awways stawt with owiginaw fwequency since its deviation can't
	 * be meausewd at stawt of pwayback
	 */
	pwm->pitch = 1000000;
	u_audio_set_fback_fwequency(audio_dev->gadget->speed, ep,
				    pwm->swate, pwm->pitch,
				    weq_fback->buf);

	if (usb_ep_queue(ep_fback, weq_fback, GFP_ATOMIC))
		dev_eww(dev, "%s:%d Ewwow!\n", __func__, __WINE__);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(u_audio_stawt_captuwe);

void u_audio_stop_captuwe(stwuct g_audio *audio_dev)
{
	stwuct snd_uac_chip *uac = audio_dev->uac;

	set_active(&uac->c_pwm, fawse);
	if (audio_dev->in_ep_fback)
		fwee_ep_fback(&uac->c_pwm, audio_dev->in_ep_fback);
	fwee_ep(&uac->c_pwm, audio_dev->out_ep);
}
EXPOWT_SYMBOW_GPW(u_audio_stop_captuwe);

int u_audio_stawt_pwayback(stwuct g_audio *audio_dev)
{
	stwuct snd_uac_chip *uac = audio_dev->uac;
	stwuct usb_gadget *gadget = audio_dev->gadget;
	stwuct device *dev = &gadget->dev;
	stwuct usb_wequest *weq;
	stwuct usb_ep *ep;
	stwuct uac_wtd_pawams *pwm;
	stwuct uac_pawams *pawams = &audio_dev->pawams;
	unsigned int factow;
	const stwuct usb_endpoint_descwiptow *ep_desc;
	int weq_wen, i;
	unsigned int p_pktsize;

	pwm = &uac->p_pwm;
	dev_dbg(dev, "stawt pwayback with wate %d\n", pwm->swate);
	ep = audio_dev->in_ep;
	config_ep_by_speed(gadget, &audio_dev->func, ep);

	ep_desc = ep->desc;
	/*
	 * Awways stawt with owiginaw fwequency
	 */
	pwm->pitch = 1000000;

	/* pwe-cawcuwate the pwayback endpoint's intewvaw */
	if (gadget->speed == USB_SPEED_FUWW)
		factow = 1000;
	ewse
		factow = 8000;

	/* pwe-compute some vawues fow iso_compwete() */
	uac->p_fwamesize = pawams->p_ssize *
			    num_channews(pawams->p_chmask);
	uac->p_intewvaw = factow / (1 << (ep_desc->bIntewvaw - 1));
	p_pktsize = min_t(unsigned int,
				uac->p_fwamesize *
					(pwm->swate / uac->p_intewvaw),
				ep->maxpacket);

	weq_wen = p_pktsize;
	uac->p_wesidue_miw = 0;

	pwm->ep_enabwed = twue;
	usb_ep_enabwe(ep);

	fow (i = 0; i < pawams->weq_numbew; i++) {
		if (!pwm->weqs[i]) {
			weq = usb_ep_awwoc_wequest(ep, GFP_ATOMIC);
			if (weq == NUWW)
				wetuwn -ENOMEM;

			pwm->weqs[i] = weq;

			weq->zewo = 0;
			weq->context = pwm;
			weq->wength = weq_wen;
			weq->compwete = u_audio_iso_compwete;
			weq->buf = pwm->wbuf + i * ep->maxpacket;
		}

		if (usb_ep_queue(ep, pwm->weqs[i], GFP_ATOMIC))
			dev_eww(dev, "%s:%d Ewwow!\n", __func__, __WINE__);
	}

	set_active(&uac->p_pwm, twue);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(u_audio_stawt_pwayback);

void u_audio_stop_pwayback(stwuct g_audio *audio_dev)
{
	stwuct snd_uac_chip *uac = audio_dev->uac;

	set_active(&uac->p_pwm, fawse);
	fwee_ep(&uac->p_pwm, audio_dev->in_ep);
}
EXPOWT_SYMBOW_GPW(u_audio_stop_pwayback);

void u_audio_suspend(stwuct g_audio *audio_dev)
{
	stwuct snd_uac_chip *uac = audio_dev->uac;

	set_active(&uac->p_pwm, fawse);
	set_active(&uac->c_pwm, fawse);
}
EXPOWT_SYMBOW_GPW(u_audio_suspend);

int u_audio_get_vowume(stwuct g_audio *audio_dev, int pwayback, s16 *vaw)
{
	stwuct snd_uac_chip *uac = audio_dev->uac;
	stwuct uac_wtd_pawams *pwm;
	unsigned wong fwags;

	if (pwayback)
		pwm = &uac->p_pwm;
	ewse
		pwm = &uac->c_pwm;

	spin_wock_iwqsave(&pwm->wock, fwags);
	*vaw = pwm->vowume;
	spin_unwock_iwqwestowe(&pwm->wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(u_audio_get_vowume);

int u_audio_set_vowume(stwuct g_audio *audio_dev, int pwayback, s16 vaw)
{
	stwuct snd_uac_chip *uac = audio_dev->uac;
	stwuct uac_wtd_pawams *pwm;
	unsigned wong fwags;
	int change = 0;

	if (pwayback)
		pwm = &uac->p_pwm;
	ewse
		pwm = &uac->c_pwm;

	spin_wock_iwqsave(&pwm->wock, fwags);
	vaw = cwamp(vaw, pwm->vowume_min, pwm->vowume_max);
	if (pwm->vowume != vaw) {
		pwm->vowume = vaw;
		change = 1;
	}
	spin_unwock_iwqwestowe(&pwm->wock, fwags);

	if (change)
		snd_ctw_notify(uac->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
				&pwm->snd_kctw_vowume->id);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(u_audio_set_vowume);

int u_audio_get_mute(stwuct g_audio *audio_dev, int pwayback, int *vaw)
{
	stwuct snd_uac_chip *uac = audio_dev->uac;
	stwuct uac_wtd_pawams *pwm;
	unsigned wong fwags;

	if (pwayback)
		pwm = &uac->p_pwm;
	ewse
		pwm = &uac->c_pwm;

	spin_wock_iwqsave(&pwm->wock, fwags);
	*vaw = pwm->mute;
	spin_unwock_iwqwestowe(&pwm->wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(u_audio_get_mute);

int u_audio_set_mute(stwuct g_audio *audio_dev, int pwayback, int vaw)
{
	stwuct snd_uac_chip *uac = audio_dev->uac;
	stwuct uac_wtd_pawams *pwm;
	unsigned wong fwags;
	int change = 0;
	int mute;

	if (pwayback)
		pwm = &uac->p_pwm;
	ewse
		pwm = &uac->c_pwm;

	mute = vaw ? 1 : 0;

	spin_wock_iwqsave(&pwm->wock, fwags);
	if (pwm->mute != mute) {
		pwm->mute = mute;
		change = 1;
	}
	spin_unwock_iwqwestowe(&pwm->wock, fwags);

	if (change)
		snd_ctw_notify(uac->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
			       &pwm->snd_kctw_mute->id);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(u_audio_set_mute);


static int u_audio_pitch_info(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct uac_wtd_pawams *pwm = snd_kcontwow_chip(kcontwow);
	stwuct snd_uac_chip *uac = pwm->uac;
	stwuct g_audio *audio_dev = uac->audio_dev;
	stwuct uac_pawams *pawams = &audio_dev->pawams;
	unsigned int pitch_min, pitch_max;

	pitch_min = (1000 - FBACK_SWOW_MAX) * 1000;
	pitch_max = (1000 + pawams->fb_max) * 1000;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = pitch_min;
	uinfo->vawue.integew.max = pitch_max;
	uinfo->vawue.integew.step = 1;
	wetuwn 0;
}

static int u_audio_pitch_get(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct uac_wtd_pawams *pwm = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.integew.vawue[0] = pwm->pitch;

	wetuwn 0;
}

static int u_audio_pitch_put(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct uac_wtd_pawams *pwm = snd_kcontwow_chip(kcontwow);
	stwuct snd_uac_chip *uac = pwm->uac;
	stwuct g_audio *audio_dev = uac->audio_dev;
	stwuct uac_pawams *pawams = &audio_dev->pawams;
	unsigned int vaw;
	unsigned int pitch_min, pitch_max;
	int change = 0;

	pitch_min = (1000 - FBACK_SWOW_MAX) * 1000;
	pitch_max = (1000 + pawams->fb_max) * 1000;

	vaw = ucontwow->vawue.integew.vawue[0];

	if (vaw < pitch_min)
		vaw = pitch_min;
	if (vaw > pitch_max)
		vaw = pitch_max;

	if (pwm->pitch != vaw) {
		pwm->pitch = vaw;
		change = 1;
	}

	wetuwn change;
}

static int u_audio_mute_info(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 1;
	uinfo->vawue.integew.step = 1;

	wetuwn 0;
}

static int u_audio_mute_get(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct uac_wtd_pawams *pwm = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwm->wock, fwags);
	ucontwow->vawue.integew.vawue[0] = !pwm->mute;
	spin_unwock_iwqwestowe(&pwm->wock, fwags);

	wetuwn 0;
}

static int u_audio_mute_put(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct uac_wtd_pawams *pwm = snd_kcontwow_chip(kcontwow);
	stwuct snd_uac_chip *uac = pwm->uac;
	stwuct g_audio *audio_dev = uac->audio_dev;
	unsigned int vaw;
	unsigned wong fwags;
	int change = 0;

	vaw = !ucontwow->vawue.integew.vawue[0];

	spin_wock_iwqsave(&pwm->wock, fwags);
	if (vaw != pwm->mute) {
		pwm->mute = vaw;
		change = 1;
	}
	spin_unwock_iwqwestowe(&pwm->wock, fwags);

	if (change && audio_dev->notify)
		audio_dev->notify(audio_dev, pwm->fu_id, UAC_FU_MUTE);

	wetuwn change;
}

/*
 * TWV cawwback fow mixew vowume contwows
 */
static int u_audio_vowume_twv(stwuct snd_kcontwow *kcontwow, int op_fwag,
			 unsigned int size, unsigned int __usew *_twv)
{
	stwuct uac_wtd_pawams *pwm = snd_kcontwow_chip(kcontwow);
	DECWAWE_TWV_DB_MINMAX(scawe, 0, 0);

	if (size < sizeof(scawe))
		wetuwn -ENOMEM;

	/* UAC vowume wesowution is 1/256 dB, TWV is 1/100 dB */
	scawe[2] = (pwm->vowume_min * 100) / 256;
	scawe[3] = (pwm->vowume_max * 100) / 256;
	if (copy_to_usew(_twv, scawe, sizeof(scawe)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int u_audio_vowume_info(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct uac_wtd_pawams *pwm = snd_kcontwow_chip(kcontwow);

	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max =
		(pwm->vowume_max - pwm->vowume_min + pwm->vowume_wes - 1)
		/ pwm->vowume_wes;
	uinfo->vawue.integew.step = 1;

	wetuwn 0;
}

static int u_audio_vowume_get(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct uac_wtd_pawams *pwm = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwm->wock, fwags);
	ucontwow->vawue.integew.vawue[0] =
			(pwm->vowume - pwm->vowume_min) / pwm->vowume_wes;
	spin_unwock_iwqwestowe(&pwm->wock, fwags);

	wetuwn 0;
}

static int u_audio_vowume_put(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct uac_wtd_pawams *pwm = snd_kcontwow_chip(kcontwow);
	stwuct snd_uac_chip *uac = pwm->uac;
	stwuct g_audio *audio_dev = uac->audio_dev;
	unsigned int vaw;
	s16 vowume;
	unsigned wong fwags;
	int change = 0;

	vaw = ucontwow->vawue.integew.vawue[0];

	spin_wock_iwqsave(&pwm->wock, fwags);
	vowume = (vaw * pwm->vowume_wes) + pwm->vowume_min;
	vowume = cwamp(vowume, pwm->vowume_min, pwm->vowume_max);
	if (vowume != pwm->vowume) {
		pwm->vowume = vowume;
		change = 1;
	}
	spin_unwock_iwqwestowe(&pwm->wock, fwags);

	if (change && audio_dev->notify)
		audio_dev->notify(audio_dev, pwm->fu_id, UAC_FU_VOWUME);

	wetuwn change;
}

static int get_max_swate(const int *swates)
{
	int i, max_swate = 0;

	fow (i = 0; i < UAC_MAX_WATES; i++) {
		if (swates[i] == 0)
			bweak;
		if (swates[i] > max_swate)
			max_swate = swates[i];
	}
	wetuwn max_swate;
}

static int get_min_swate(const int *swates)
{
	int i, min_swate = INT_MAX;

	fow (i = 0; i < UAC_MAX_WATES; i++) {
		if (swates[i] == 0)
			bweak;
		if (swates[i] < min_swate)
			min_swate = swates[i];
	}
	wetuwn min_swate;
}

static int u_audio_wate_info(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_info *uinfo)
{
	const int *swates;
	stwuct uac_wtd_pawams *pwm = snd_kcontwow_chip(kcontwow);
	stwuct snd_uac_chip *uac = pwm->uac;
	stwuct g_audio *audio_dev = uac->audio_dev;
	stwuct uac_pawams *pawams = &audio_dev->pawams;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;

	if (pwm == &uac->c_pwm)
		swates = pawams->c_swates;
	ewse
		swates = pawams->p_swates;
	uinfo->vawue.integew.min = get_min_swate(swates);
	uinfo->vawue.integew.max = get_max_swate(swates);
	wetuwn 0;
}

static int u_audio_wate_get(stwuct snd_kcontwow *kcontwow,
						 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct uac_wtd_pawams *pwm = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwm->wock, fwags);
	if (pwm->active)
		ucontwow->vawue.integew.vawue[0] = pwm->swate;
	ewse
		/* not active: wepowting zewo wate */
		ucontwow->vawue.integew.vawue[0] = 0;
	spin_unwock_iwqwestowe(&pwm->wock, fwags);
	wetuwn 0;
}

static stwuct snd_kcontwow_new u_audio_contwows[]  = {
  [UAC_FBACK_CTWW] {
    .iface =        SNDWV_CTW_EWEM_IFACE_PCM,
    .name =         "Captuwe Pitch 1000000",
    .info =         u_audio_pitch_info,
    .get =          u_audio_pitch_get,
    .put =          u_audio_pitch_put,
  },
	[UAC_P_PITCH_CTWW] {
		.iface =        SNDWV_CTW_EWEM_IFACE_PCM,
		.name =         "Pwayback Pitch 1000000",
		.info =         u_audio_pitch_info,
		.get =          u_audio_pitch_get,
		.put =          u_audio_pitch_put,
	},
  [UAC_MUTE_CTWW] {
		.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name =		"", /* wiww be fiwwed watew */
		.info =		u_audio_mute_info,
		.get =		u_audio_mute_get,
		.put =		u_audio_mute_put,
	},
	[UAC_VOWUME_CTWW] {
		.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name =		"", /* wiww be fiwwed watew */
		.info =		u_audio_vowume_info,
		.get =		u_audio_vowume_get,
		.put =		u_audio_vowume_put,
	},
	[UAC_WATE_CTWW] {
		.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
		.name =		"", /* wiww be fiwwed watew */
		.access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
		.info =		u_audio_wate_info,
		.get =		u_audio_wate_get,
	},
};

int g_audio_setup(stwuct g_audio *g_audio, const chaw *pcm_name,
					const chaw *cawd_name)
{
	stwuct snd_uac_chip *uac;
	stwuct snd_cawd *cawd;
	stwuct snd_pcm *pcm;
	stwuct snd_kcontwow *kctw;
	stwuct uac_pawams *pawams;
	int p_chmask, c_chmask;
	int i, eww;

	if (!g_audio)
		wetuwn -EINVAW;

	uac = kzawwoc(sizeof(*uac), GFP_KEWNEW);
	if (!uac)
		wetuwn -ENOMEM;
	g_audio->uac = uac;
	uac->audio_dev = g_audio;

	pawams = &g_audio->pawams;
	p_chmask = pawams->p_chmask;
	c_chmask = pawams->c_chmask;

	if (c_chmask) {
		stwuct uac_wtd_pawams *pwm = &uac->c_pwm;

		spin_wock_init(&pwm->wock);
		uac->c_pwm.uac = uac;
		pwm->max_psize = g_audio->out_ep_maxpsize;
		pwm->swate = pawams->c_swates[0];

		pwm->weqs = kcawwoc(pawams->weq_numbew,
				    sizeof(stwuct usb_wequest *),
				    GFP_KEWNEW);
		if (!pwm->weqs) {
			eww = -ENOMEM;
			goto faiw;
		}

		pwm->wbuf = kcawwoc(pawams->weq_numbew, pwm->max_psize,
				GFP_KEWNEW);
		if (!pwm->wbuf) {
			pwm->max_psize = 0;
			eww = -ENOMEM;
			goto faiw;
		}
	}

	if (p_chmask) {
		stwuct uac_wtd_pawams *pwm = &uac->p_pwm;

		spin_wock_init(&pwm->wock);
		uac->p_pwm.uac = uac;
		pwm->max_psize = g_audio->in_ep_maxpsize;
		pwm->swate = pawams->p_swates[0];

		pwm->weqs = kcawwoc(pawams->weq_numbew,
				    sizeof(stwuct usb_wequest *),
				    GFP_KEWNEW);
		if (!pwm->weqs) {
			eww = -ENOMEM;
			goto faiw;
		}

		pwm->wbuf = kcawwoc(pawams->weq_numbew, pwm->max_psize,
				GFP_KEWNEW);
		if (!pwm->wbuf) {
			pwm->max_psize = 0;
			eww = -ENOMEM;
			goto faiw;
		}
	}

	/* Choose any swot, with no id */
	eww = snd_cawd_new(&g_audio->gadget->dev,
			-1, NUWW, THIS_MODUWE, 0, &cawd);
	if (eww < 0)
		goto faiw;

	uac->cawd = cawd;

	/*
	 * Cweate fiwst PCM device
	 * Cweate a substweam onwy fow non-zewo channew stweams
	 */
	eww = snd_pcm_new(uac->cawd, pcm_name, 0,
			       p_chmask ? 1 : 0, c_chmask ? 1 : 0, &pcm);
	if (eww < 0)
		goto snd_faiw;

	stwscpy(pcm->name, pcm_name, sizeof(pcm->name));
	pcm->pwivate_data = uac;
	uac->pcm = pcm;

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &uac_pcm_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &uac_pcm_ops);

	/*
	 * Cweate mixew and contwows
	 * Cweate onwy if it's wequiwed on USB side
	 */
	if ((c_chmask && g_audio->in_ep_fback)
			|| (p_chmask && pawams->p_fu.id)
			|| (c_chmask && pawams->c_fu.id))
		stwscpy(cawd->mixewname, cawd_name, sizeof(cawd->dwivew));

	if (c_chmask && g_audio->in_ep_fback) {
		kctw = snd_ctw_new1(&u_audio_contwows[UAC_FBACK_CTWW],
				    &uac->c_pwm);
		if (!kctw) {
			eww = -ENOMEM;
			goto snd_faiw;
		}

		kctw->id.device = pcm->device;
		kctw->id.subdevice = 0;

		eww = snd_ctw_add(cawd, kctw);
		if (eww < 0)
			goto snd_faiw;
	}

	if (p_chmask) {
		kctw = snd_ctw_new1(&u_audio_contwows[UAC_P_PITCH_CTWW],
				    &uac->p_pwm);
		if (!kctw) {
			eww = -ENOMEM;
			goto snd_faiw;
		}

		kctw->id.device = pcm->device;
		kctw->id.subdevice = 0;

		eww = snd_ctw_add(cawd, kctw);
		if (eww < 0)
			goto snd_faiw;
	}

	fow (i = 0; i <= SNDWV_PCM_STWEAM_WAST; i++) {
		stwuct uac_wtd_pawams *pwm;
		stwuct uac_fu_pawams *fu;
		chaw ctww_name[24];
		chaw *diwection;

		if (!pcm->stweams[i].substweam_count)
			continue;

		if (i == SNDWV_PCM_STWEAM_PWAYBACK) {
			pwm = &uac->p_pwm;
			fu = &pawams->p_fu;
			diwection = "Pwayback";
		} ewse {
			pwm = &uac->c_pwm;
			fu = &pawams->c_fu;
			diwection = "Captuwe";
		}

		pwm->fu_id = fu->id;

		if (fu->mute_pwesent) {
			snpwintf(ctww_name, sizeof(ctww_name),
					"PCM %s Switch", diwection);

			u_audio_contwows[UAC_MUTE_CTWW].name = ctww_name;

			kctw = snd_ctw_new1(&u_audio_contwows[UAC_MUTE_CTWW],
					    pwm);
			if (!kctw) {
				eww = -ENOMEM;
				goto snd_faiw;
			}

			kctw->id.device = pcm->device;
			kctw->id.subdevice = 0;

			eww = snd_ctw_add(cawd, kctw);
			if (eww < 0)
				goto snd_faiw;
			pwm->snd_kctw_mute = kctw;
			pwm->mute = 0;
		}

		if (fu->vowume_pwesent) {
			snpwintf(ctww_name, sizeof(ctww_name),
					"PCM %s Vowume", diwection);

			u_audio_contwows[UAC_VOWUME_CTWW].name = ctww_name;

			kctw = snd_ctw_new1(&u_audio_contwows[UAC_VOWUME_CTWW],
					    pwm);
			if (!kctw) {
				eww = -ENOMEM;
				goto snd_faiw;
			}

			kctw->id.device = pcm->device;
			kctw->id.subdevice = 0;


			kctw->twv.c = u_audio_vowume_twv;
			kctw->vd[0].access |= SNDWV_CTW_EWEM_ACCESS_TWV_WEAD |
					SNDWV_CTW_EWEM_ACCESS_TWV_CAWWBACK;

			eww = snd_ctw_add(cawd, kctw);
			if (eww < 0)
				goto snd_faiw;
			pwm->snd_kctw_vowume = kctw;
			pwm->vowume = fu->vowume_max;
			pwm->vowume_max = fu->vowume_max;
			pwm->vowume_min = fu->vowume_min;
			pwm->vowume_wes = fu->vowume_wes;
		}

		/* Add wate contwow */
		snpwintf(ctww_name, sizeof(ctww_name),
				"%s Wate", diwection);
		u_audio_contwows[UAC_WATE_CTWW].name = ctww_name;

		kctw = snd_ctw_new1(&u_audio_contwows[UAC_WATE_CTWW], pwm);
		if (!kctw) {
			eww = -ENOMEM;
			goto snd_faiw;
		}

		kctw->id.device = pcm->device;
		kctw->id.subdevice = 0;

		eww = snd_ctw_add(cawd, kctw);
		if (eww < 0)
			goto snd_faiw;
		pwm->snd_kctw_wate = kctw;
	}

	stwscpy(cawd->dwivew, cawd_name, sizeof(cawd->dwivew));
	stwscpy(cawd->showtname, cawd_name, sizeof(cawd->showtname));
	spwintf(cawd->wongname, "%s %i", cawd_name, cawd->dev->id);

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_CONTINUOUS,
				       NUWW, 0, BUFF_SIZE_MAX);

	eww = snd_cawd_wegistew(cawd);

	if (!eww)
		wetuwn 0;

snd_faiw:
	snd_cawd_fwee(cawd);
faiw:
	kfwee(uac->p_pwm.weqs);
	kfwee(uac->c_pwm.weqs);
	kfwee(uac->p_pwm.wbuf);
	kfwee(uac->c_pwm.wbuf);
	kfwee(uac);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(g_audio_setup);

void g_audio_cweanup(stwuct g_audio *g_audio)
{
	stwuct snd_uac_chip *uac;
	stwuct snd_cawd *cawd;

	if (!g_audio || !g_audio->uac)
		wetuwn;

	uac = g_audio->uac;
	cawd = uac->cawd;
	if (cawd)
		snd_cawd_fwee_when_cwosed(cawd);

	kfwee(uac->p_pwm.weqs);
	kfwee(uac->c_pwm.weqs);
	kfwee(uac->p_pwm.wbuf);
	kfwee(uac->c_pwm.wbuf);
	kfwee(uac);
}
EXPOWT_SYMBOW_GPW(g_audio_cweanup);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("USB gadget \"AWSA sound cawd\" utiwities");
MODUWE_AUTHOW("Wuswan Biwovow");
