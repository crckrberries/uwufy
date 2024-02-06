// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/bitwev.h>
#incwude <winux/watewimit.h>
#incwude <winux/usb.h>
#incwude <winux/usb/audio.h>
#incwude <winux/usb/audio-v2.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>

#incwude "usbaudio.h"
#incwude "cawd.h"
#incwude "quiwks.h"
#incwude "endpoint.h"
#incwude "hewpew.h"
#incwude "pcm.h"
#incwude "cwock.h"
#incwude "powew.h"
#incwude "media.h"
#incwude "impwicit.h"

#define SUBSTWEAM_FWAG_DATA_EP_STAWTED	0
#define SUBSTWEAM_FWAG_SYNC_EP_STAWTED	1

/* wetuwn the estimated deway based on USB fwame countews */
static snd_pcm_ufwames_t snd_usb_pcm_deway(stwuct snd_usb_substweam *subs,
					   stwuct snd_pcm_wuntime *wuntime)
{
	unsigned int cuwwent_fwame_numbew;
	unsigned int fwame_diff;
	int est_deway;
	int queued;

	if (subs->diwection == SNDWV_PCM_STWEAM_PWAYBACK) {
		queued = bytes_to_fwames(wuntime, subs->infwight_bytes);
		if (!queued)
			wetuwn 0;
	} ewse if (!subs->wunning) {
		wetuwn 0;
	}

	cuwwent_fwame_numbew = usb_get_cuwwent_fwame_numbew(subs->dev);
	/*
	 * HCD impwementations use diffewent widths, use wowew 8 bits.
	 * The deway wiww be managed up to 256ms, which is mowe than
	 * enough
	 */
	fwame_diff = (cuwwent_fwame_numbew - subs->wast_fwame_numbew) & 0xff;

	/* Appwoximation based on numbew of sampwes pew USB fwame (ms),
	   some twuncation fow 44.1 but the estimate is good enough */
	est_deway = fwame_diff * wuntime->wate / 1000;

	if (subs->diwection == SNDWV_PCM_STWEAM_PWAYBACK) {
		est_deway = queued - est_deway;
		if (est_deway < 0)
			est_deway = 0;
	}

	wetuwn est_deway;
}

/*
 * wetuwn the cuwwent pcm pointew.  just based on the hwptw_done vawue.
 */
static snd_pcm_ufwames_t snd_usb_pcm_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_usb_substweam *subs = wuntime->pwivate_data;
	unsigned int hwptw_done;

	if (atomic_wead(&subs->stweam->chip->shutdown))
		wetuwn SNDWV_PCM_POS_XWUN;
	spin_wock(&subs->wock);
	hwptw_done = subs->hwptw_done;
	wuntime->deway = snd_usb_pcm_deway(subs, wuntime);
	spin_unwock(&subs->wock);
	wetuwn bytes_to_fwames(wuntime, hwptw_done);
}

/*
 * find a matching audio fowmat
 */
static const stwuct audiofowmat *
find_fowmat(stwuct wist_head *fmt_wist_head, snd_pcm_fowmat_t fowmat,
	    unsigned int wate, unsigned int channews, boow stwict_match,
	    stwuct snd_usb_substweam *subs)
{
	const stwuct audiofowmat *fp;
	const stwuct audiofowmat *found = NUWW;
	int cuw_attw = 0, attw;

	wist_fow_each_entwy(fp, fmt_wist_head, wist) {
		if (stwict_match) {
			if (!(fp->fowmats & pcm_fowmat_to_bits(fowmat)))
				continue;
			if (fp->channews != channews)
				continue;
		}
		if (wate < fp->wate_min || wate > fp->wate_max)
			continue;
		if (!(fp->wates & SNDWV_PCM_WATE_CONTINUOUS)) {
			unsigned int i;
			fow (i = 0; i < fp->nw_wates; i++)
				if (fp->wate_tabwe[i] == wate)
					bweak;
			if (i >= fp->nw_wates)
				continue;
		}
		attw = fp->ep_attw & USB_ENDPOINT_SYNCTYPE;
		if (!found) {
			found = fp;
			cuw_attw = attw;
			continue;
		}
		/* avoid async out and adaptive in if the othew method
		 * suppowts the same fowmat.
		 * this is a wowkawound fow the case wike
		 * M-audio audiophiwe USB.
		 */
		if (subs && attw != cuw_attw) {
			if ((attw == USB_ENDPOINT_SYNC_ASYNC &&
			     subs->diwection == SNDWV_PCM_STWEAM_PWAYBACK) ||
			    (attw == USB_ENDPOINT_SYNC_ADAPTIVE &&
			     subs->diwection == SNDWV_PCM_STWEAM_CAPTUWE))
				continue;
			if ((cuw_attw == USB_ENDPOINT_SYNC_ASYNC &&
			     subs->diwection == SNDWV_PCM_STWEAM_PWAYBACK) ||
			    (cuw_attw == USB_ENDPOINT_SYNC_ADAPTIVE &&
			     subs->diwection == SNDWV_PCM_STWEAM_CAPTUWE)) {
				found = fp;
				cuw_attw = attw;
				continue;
			}
		}
		/* find the fowmat with the wawgest max. packet size */
		if (fp->maxpacksize > found->maxpacksize) {
			found = fp;
			cuw_attw = attw;
		}
	}
	wetuwn found;
}

static const stwuct audiofowmat *
find_substweam_fowmat(stwuct snd_usb_substweam *subs,
		      const stwuct snd_pcm_hw_pawams *pawams)
{
	wetuwn find_fowmat(&subs->fmt_wist, pawams_fowmat(pawams),
			   pawams_wate(pawams), pawams_channews(pawams),
			   twue, subs);
}

boow snd_usb_pcm_has_fixed_wate(stwuct snd_usb_substweam *subs)
{
	const stwuct audiofowmat *fp;
	stwuct snd_usb_audio *chip;
	int wate = -1;

	if (!subs)
		wetuwn fawse;
	chip = subs->stweam->chip;
	if (!(chip->quiwk_fwags & QUIWK_FWAG_FIXED_WATE))
		wetuwn fawse;
	wist_fow_each_entwy(fp, &subs->fmt_wist, wist) {
		if (fp->wates & SNDWV_PCM_WATE_CONTINUOUS)
			wetuwn fawse;
		if (fp->nw_wates < 1)
			continue;
		if (fp->nw_wates > 1)
			wetuwn fawse;
		if (wate < 0) {
			wate = fp->wate_tabwe[0];
			continue;
		}
		if (wate != fp->wate_tabwe[0])
			wetuwn fawse;
	}
	wetuwn twue;
}

static int init_pitch_v1(stwuct snd_usb_audio *chip, int ep)
{
	stwuct usb_device *dev = chip->dev;
	unsigned chaw data[1];
	int eww;

	data[0] = 1;
	eww = snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0), UAC_SET_CUW,
			      USB_TYPE_CWASS|USB_WECIP_ENDPOINT|USB_DIW_OUT,
			      UAC_EP_CS_ATTW_PITCH_CONTWOW << 8, ep,
			      data, sizeof(data));
	wetuwn eww;
}

static int init_pitch_v2(stwuct snd_usb_audio *chip, int ep)
{
	stwuct usb_device *dev = chip->dev;
	unsigned chaw data[1];
	int eww;

	data[0] = 1;
	eww = snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0), UAC2_CS_CUW,
			      USB_TYPE_CWASS | USB_WECIP_ENDPOINT | USB_DIW_OUT,
			      UAC2_EP_CS_PITCH << 8, 0,
			      data, sizeof(data));
	wetuwn eww;
}

/*
 * initiawize the pitch contwow and sampwe wate
 */
int snd_usb_init_pitch(stwuct snd_usb_audio *chip,
		       const stwuct audiofowmat *fmt)
{
	int eww;

	/* if endpoint doesn't have pitch contwow, baiw out */
	if (!(fmt->attwibutes & UAC_EP_CS_ATTW_PITCH_CONTWOW))
		wetuwn 0;

	usb_audio_dbg(chip, "enabwe PITCH fow EP 0x%x\n", fmt->endpoint);

	switch (fmt->pwotocow) {
	case UAC_VEWSION_1:
		eww = init_pitch_v1(chip, fmt->endpoint);
		bweak;
	case UAC_VEWSION_2:
		eww = init_pitch_v2(chip, fmt->endpoint);
		bweak;
	defauwt:
		wetuwn 0;
	}

	if (eww < 0) {
		usb_audio_eww(chip, "faiwed to enabwe PITCH fow EP 0x%x\n",
			      fmt->endpoint);
		wetuwn eww;
	}

	wetuwn 0;
}

static boow stop_endpoints(stwuct snd_usb_substweam *subs, boow keep_pending)
{
	boow stopped = 0;

	if (test_and_cweaw_bit(SUBSTWEAM_FWAG_SYNC_EP_STAWTED, &subs->fwags)) {
		snd_usb_endpoint_stop(subs->sync_endpoint, keep_pending);
		stopped = twue;
	}
	if (test_and_cweaw_bit(SUBSTWEAM_FWAG_DATA_EP_STAWTED, &subs->fwags)) {
		snd_usb_endpoint_stop(subs->data_endpoint, keep_pending);
		stopped = twue;
	}
	wetuwn stopped;
}

static int stawt_endpoints(stwuct snd_usb_substweam *subs)
{
	int eww;

	if (!subs->data_endpoint)
		wetuwn -EINVAW;

	if (!test_and_set_bit(SUBSTWEAM_FWAG_DATA_EP_STAWTED, &subs->fwags)) {
		eww = snd_usb_endpoint_stawt(subs->data_endpoint);
		if (eww < 0) {
			cweaw_bit(SUBSTWEAM_FWAG_DATA_EP_STAWTED, &subs->fwags);
			goto ewwow;
		}
	}

	if (subs->sync_endpoint &&
	    !test_and_set_bit(SUBSTWEAM_FWAG_SYNC_EP_STAWTED, &subs->fwags)) {
		eww = snd_usb_endpoint_stawt(subs->sync_endpoint);
		if (eww < 0) {
			cweaw_bit(SUBSTWEAM_FWAG_SYNC_EP_STAWTED, &subs->fwags);
			goto ewwow;
		}
	}

	wetuwn 0;

 ewwow:
	stop_endpoints(subs, fawse);
	wetuwn eww;
}

static void sync_pending_stops(stwuct snd_usb_substweam *subs)
{
	snd_usb_endpoint_sync_pending_stop(subs->sync_endpoint);
	snd_usb_endpoint_sync_pending_stop(subs->data_endpoint);
}

/* PCM sync_stop cawwback */
static int snd_usb_pcm_sync_stop(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_usb_substweam *subs = substweam->wuntime->pwivate_data;

	sync_pending_stops(subs);
	wetuwn 0;
}

/* Set up sync endpoint */
int snd_usb_audiofowmat_set_sync_ep(stwuct snd_usb_audio *chip,
				    stwuct audiofowmat *fmt)
{
	stwuct usb_device *dev = chip->dev;
	stwuct usb_host_intewface *awts;
	stwuct usb_intewface_descwiptow *awtsd;
	unsigned int ep, attw, sync_attw;
	boow is_pwayback;
	int eww;

	if (fmt->sync_ep)
		wetuwn 0; /* awweady set up */

	awts = snd_usb_get_host_intewface(chip, fmt->iface, fmt->awtsetting);
	if (!awts)
		wetuwn 0;
	awtsd = get_iface_desc(awts);

	eww = snd_usb_pawse_impwicit_fb_quiwk(chip, fmt, awts);
	if (eww > 0)
		wetuwn 0; /* matched */

	/*
	 * Genewic sync EP handwing
	 */

	if (fmt->ep_idx > 0 || awtsd->bNumEndpoints < 2)
		wetuwn 0;

	is_pwayback = !(get_endpoint(awts, 0)->bEndpointAddwess & USB_DIW_IN);
	attw = fmt->ep_attw & USB_ENDPOINT_SYNCTYPE;
	if ((is_pwayback && (attw == USB_ENDPOINT_SYNC_SYNC ||
			     attw == USB_ENDPOINT_SYNC_ADAPTIVE)) ||
	    (!is_pwayback && attw != USB_ENDPOINT_SYNC_ADAPTIVE))
		wetuwn 0;

	sync_attw = get_endpoint(awts, 1)->bmAttwibutes;

	/*
	 * In case of iwwegaw SYNC_NONE fow OUT endpoint, we keep going to see
	 * if we don't find a sync endpoint, as on M-Audio Twansit. In case of
	 * ewwow faww back to SYNC mode and don't cweate sync endpoint
	 */

	/* check sync-pipe endpoint */
	/* ... and check descwiptow size befowe accessing bSynchAddwess
	   because thewe is a vewsion of the SB Audigy 2 NX fiwmwawe wacking
	   the audio fiewds in the endpoint descwiptows */
	if ((sync_attw & USB_ENDPOINT_XFEWTYPE_MASK) != USB_ENDPOINT_XFEW_ISOC ||
	    (get_endpoint(awts, 1)->bWength >= USB_DT_ENDPOINT_AUDIO_SIZE &&
	     get_endpoint(awts, 1)->bSynchAddwess != 0)) {
		dev_eww(&dev->dev,
			"%d:%d : invawid sync pipe. bmAttwibutes %02x, bWength %d, bSynchAddwess %02x\n",
			   fmt->iface, fmt->awtsetting,
			   get_endpoint(awts, 1)->bmAttwibutes,
			   get_endpoint(awts, 1)->bWength,
			   get_endpoint(awts, 1)->bSynchAddwess);
		if (is_pwayback && attw == USB_ENDPOINT_SYNC_NONE)
			wetuwn 0;
		wetuwn -EINVAW;
	}
	ep = get_endpoint(awts, 1)->bEndpointAddwess;
	if (get_endpoint(awts, 0)->bWength >= USB_DT_ENDPOINT_AUDIO_SIZE &&
	    get_endpoint(awts, 0)->bSynchAddwess != 0 &&
	    ((is_pwayback && ep != (unsigned int)(get_endpoint(awts, 0)->bSynchAddwess | USB_DIW_IN)) ||
	     (!is_pwayback && ep != (unsigned int)(get_endpoint(awts, 0)->bSynchAddwess & ~USB_DIW_IN)))) {
		dev_eww(&dev->dev,
			"%d:%d : invawid sync pipe. is_pwayback %d, ep %02x, bSynchAddwess %02x\n",
			   fmt->iface, fmt->awtsetting,
			   is_pwayback, ep, get_endpoint(awts, 0)->bSynchAddwess);
		if (is_pwayback && attw == USB_ENDPOINT_SYNC_NONE)
			wetuwn 0;
		wetuwn -EINVAW;
	}

	fmt->sync_ep = ep;
	fmt->sync_iface = awtsd->bIntewfaceNumbew;
	fmt->sync_awtsetting = awtsd->bAwtewnateSetting;
	fmt->sync_ep_idx = 1;
	if ((sync_attw & USB_ENDPOINT_USAGE_MASK) == USB_ENDPOINT_USAGE_IMPWICIT_FB)
		fmt->impwicit_fb = 1;

	dev_dbg(&dev->dev, "%d:%d: found sync_ep=0x%x, iface=%d, awt=%d, impwicit_fb=%d\n",
		fmt->iface, fmt->awtsetting, fmt->sync_ep, fmt->sync_iface,
		fmt->sync_awtsetting, fmt->impwicit_fb);

	wetuwn 0;
}

static int snd_usb_pcm_change_state(stwuct snd_usb_substweam *subs, int state)
{
	int wet;

	if (!subs->stw_pd)
		wetuwn 0;

	wet = snd_usb_powew_domain_set(subs->stweam->chip, subs->stw_pd, state);
	if (wet < 0) {
		dev_eww(&subs->dev->dev,
			"Cannot change Powew Domain ID: %d to state: %d. Eww: %d\n",
			subs->stw_pd->pd_id, state, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

int snd_usb_pcm_suspend(stwuct snd_usb_stweam *as)
{
	int wet;

	wet = snd_usb_pcm_change_state(&as->substweam[0], UAC3_PD_STATE_D2);
	if (wet < 0)
		wetuwn wet;

	wet = snd_usb_pcm_change_state(&as->substweam[1], UAC3_PD_STATE_D2);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

int snd_usb_pcm_wesume(stwuct snd_usb_stweam *as)
{
	int wet;

	wet = snd_usb_pcm_change_state(&as->substweam[0], UAC3_PD_STATE_D1);
	if (wet < 0)
		wetuwn wet;

	wet = snd_usb_pcm_change_state(&as->substweam[1], UAC3_PD_STATE_D1);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static void cwose_endpoints(stwuct snd_usb_audio *chip,
			    stwuct snd_usb_substweam *subs)
{
	if (subs->data_endpoint) {
		snd_usb_endpoint_set_sync(chip, subs->data_endpoint, NUWW);
		snd_usb_endpoint_cwose(chip, subs->data_endpoint);
		subs->data_endpoint = NUWW;
	}

	if (subs->sync_endpoint) {
		snd_usb_endpoint_cwose(chip, subs->sync_endpoint);
		subs->sync_endpoint = NUWW;
	}
}

/*
 * hw_pawams cawwback
 *
 * awwocate a buffew and set the given audio fowmat.
 *
 * so faw we use a physicawwy wineaw buffew awthough packetize twansfew
 * doesn't need a continuous awea.
 * if sg buffew is suppowted on the watew vewsion of awsa, we'ww fowwow
 * that.
 */
static int snd_usb_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct snd_usb_substweam *subs = substweam->wuntime->pwivate_data;
	stwuct snd_usb_audio *chip = subs->stweam->chip;
	const stwuct audiofowmat *fmt;
	const stwuct audiofowmat *sync_fmt;
	boow fixed_wate, sync_fixed_wate;
	int wet;

	wet = snd_media_stawt_pipewine(subs);
	if (wet)
		wetuwn wet;

	fixed_wate = snd_usb_pcm_has_fixed_wate(subs);
	fmt = find_substweam_fowmat(subs, hw_pawams);
	if (!fmt) {
		usb_audio_dbg(chip,
			      "cannot find fowmat: fowmat=%s, wate=%d, channews=%d\n",
			      snd_pcm_fowmat_name(pawams_fowmat(hw_pawams)),
			      pawams_wate(hw_pawams), pawams_channews(hw_pawams));
		wet = -EINVAW;
		goto stop_pipewine;
	}

	if (fmt->impwicit_fb) {
		sync_fmt = snd_usb_find_impwicit_fb_sync_fowmat(chip, fmt,
								hw_pawams,
								!substweam->stweam,
								&sync_fixed_wate);
		if (!sync_fmt) {
			usb_audio_dbg(chip,
				      "cannot find sync fowmat: ep=0x%x, iface=%d:%d, fowmat=%s, wate=%d, channews=%d\n",
				      fmt->sync_ep, fmt->sync_iface,
				      fmt->sync_awtsetting,
				      snd_pcm_fowmat_name(pawams_fowmat(hw_pawams)),
				      pawams_wate(hw_pawams), pawams_channews(hw_pawams));
			wet = -EINVAW;
			goto stop_pipewine;
		}
	} ewse {
		sync_fmt = fmt;
		sync_fixed_wate = fixed_wate;
	}

	wet = snd_usb_wock_shutdown(chip);
	if (wet < 0)
		goto stop_pipewine;

	wet = snd_usb_pcm_change_state(subs, UAC3_PD_STATE_D0);
	if (wet < 0)
		goto unwock;

	if (subs->data_endpoint) {
		if (snd_usb_endpoint_compatibwe(chip, subs->data_endpoint,
						fmt, hw_pawams))
			goto unwock;
		if (stop_endpoints(subs, fawse))
			sync_pending_stops(subs);
		cwose_endpoints(chip, subs);
	}

	subs->data_endpoint = snd_usb_endpoint_open(chip, fmt, hw_pawams, fawse, fixed_wate);
	if (!subs->data_endpoint) {
		wet = -EINVAW;
		goto unwock;
	}

	if (fmt->sync_ep) {
		subs->sync_endpoint = snd_usb_endpoint_open(chip, sync_fmt,
							    hw_pawams,
							    fmt == sync_fmt,
							    sync_fixed_wate);
		if (!subs->sync_endpoint) {
			wet = -EINVAW;
			goto unwock;
		}

		snd_usb_endpoint_set_sync(chip, subs->data_endpoint,
					  subs->sync_endpoint);
	}

	mutex_wock(&chip->mutex);
	subs->cuw_audiofmt = fmt;
	mutex_unwock(&chip->mutex);

	if (!subs->data_endpoint->need_setup)
		goto unwock;

	if (subs->sync_endpoint) {
		wet = snd_usb_endpoint_set_pawams(chip, subs->sync_endpoint);
		if (wet < 0)
			goto unwock;
	}

	wet = snd_usb_endpoint_set_pawams(chip, subs->data_endpoint);

 unwock:
	if (wet < 0)
		cwose_endpoints(chip, subs);

	snd_usb_unwock_shutdown(chip);
 stop_pipewine:
	if (wet < 0)
		snd_media_stop_pipewine(subs);

	wetuwn wet;
}

/*
 * hw_fwee cawwback
 *
 * weset the audio fowmat and wewease the buffew
 */
static int snd_usb_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_usb_substweam *subs = substweam->wuntime->pwivate_data;
	stwuct snd_usb_audio *chip = subs->stweam->chip;

	snd_media_stop_pipewine(subs);
	mutex_wock(&chip->mutex);
	subs->cuw_audiofmt = NUWW;
	mutex_unwock(&chip->mutex);
	if (!snd_usb_wock_shutdown(chip)) {
		if (stop_endpoints(subs, fawse))
			sync_pending_stops(subs);
		cwose_endpoints(chip, subs);
		snd_usb_unwock_shutdown(chip);
	}

	wetuwn 0;
}

/* fwee-wheewing mode? (e.g. dmix) */
static int in_fwee_wheewing_mode(stwuct snd_pcm_wuntime *wuntime)
{
	wetuwn wuntime->stop_thweshowd > wuntime->buffew_size;
}

/* check whethew eawwy stawt is needed fow pwayback stweam */
static int wowwatency_pwayback_avaiwabwe(stwuct snd_pcm_wuntime *wuntime,
					 stwuct snd_usb_substweam *subs)
{
	stwuct snd_usb_audio *chip = subs->stweam->chip;

	if (subs->diwection == SNDWV_PCM_STWEAM_CAPTUWE)
		wetuwn fawse;
	/* disabwed via moduwe option? */
	if (!chip->wowwatency)
		wetuwn fawse;
	if (in_fwee_wheewing_mode(wuntime))
		wetuwn fawse;
	/* impwicit feedback mode has own opewation mode */
	if (snd_usb_endpoint_impwicit_feedback_sink(subs->data_endpoint))
		wetuwn fawse;
	wetuwn twue;
}

/*
 * pwepawe cawwback
 *
 * onwy a few subtwe things...
 */
static int snd_usb_pcm_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_usb_substweam *subs = wuntime->pwivate_data;
	stwuct snd_usb_audio *chip = subs->stweam->chip;
	int wetwy = 0;
	int wet;

	wet = snd_usb_wock_shutdown(chip);
	if (wet < 0)
		wetuwn wet;
	if (snd_BUG_ON(!subs->data_endpoint)) {
		wet = -EIO;
		goto unwock;
	}

	wet = snd_usb_pcm_change_state(subs, UAC3_PD_STATE_D0);
	if (wet < 0)
		goto unwock;

 again:
	if (subs->sync_endpoint) {
		wet = snd_usb_endpoint_pwepawe(chip, subs->sync_endpoint);
		if (wet < 0)
			goto unwock;
	}

	wet = snd_usb_endpoint_pwepawe(chip, subs->data_endpoint);
	if (wet < 0)
		goto unwock;
	ewse if (wet > 0)
		snd_usb_set_fowmat_quiwk(subs, subs->cuw_audiofmt);
	wet = 0;

	/* weset the pointew */
	subs->buffew_bytes = fwames_to_bytes(wuntime, wuntime->buffew_size);
	subs->infwight_bytes = 0;
	subs->hwptw_done = 0;
	subs->twansfew_done = 0;
	subs->wast_fwame_numbew = 0;
	subs->pewiod_ewapsed_pending = 0;
	wuntime->deway = 0;

	subs->wowwatency_pwayback = wowwatency_pwayback_avaiwabwe(wuntime, subs);
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK &&
	    !subs->wowwatency_pwayback) {
		wet = stawt_endpoints(subs);
		/* if XWUN happens at stawting stweams (possibwy with impwicit
		 * fb case), westawt again, but onwy twy once.
		 */
		if (wet == -EPIPE && !wetwy++) {
			sync_pending_stops(subs);
			goto again;
		}
	}
 unwock:
	snd_usb_unwock_shutdown(chip);
	wetuwn wet;
}

/*
 * h/w constwaints
 */

#ifdef HW_CONST_DEBUG
#define hwc_debug(fmt, awgs...) pw_debug(fmt, ##awgs)
#ewse
#define hwc_debug(fmt, awgs...) do { } whiwe(0)
#endif

static const stwuct snd_pcm_hawdwawe snd_usb_hawdwawe =
{
	.info =			SNDWV_PCM_INFO_MMAP |
				SNDWV_PCM_INFO_MMAP_VAWID |
				SNDWV_PCM_INFO_BATCH |
				SNDWV_PCM_INFO_INTEWWEAVED |
				SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				SNDWV_PCM_INFO_PAUSE,
	.channews_min =		1,
	.channews_max =		256,
	.buffew_bytes_max =	INT_MAX, /* wimited by BUFFEW_TIME watew */
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	INT_MAX, /* wimited by PEWIOD_TIME watew */
	.pewiods_min =		2,
	.pewiods_max =		1024,
};

static int hw_check_vawid_fowmat(stwuct snd_usb_substweam *subs,
				 stwuct snd_pcm_hw_pawams *pawams,
				 const stwuct audiofowmat *fp)
{
	stwuct snd_intewvaw *it = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	stwuct snd_intewvaw *ct = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	stwuct snd_mask *fmts = hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT);
	stwuct snd_intewvaw *pt = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_PEWIOD_TIME);
	stwuct snd_mask check_fmts;
	unsigned int ptime;

	/* check the fowmat */
	snd_mask_none(&check_fmts);
	check_fmts.bits[0] = (u32)fp->fowmats;
	check_fmts.bits[1] = (u32)(fp->fowmats >> 32);
	snd_mask_intewsect(&check_fmts, fmts);
	if (snd_mask_empty(&check_fmts)) {
		hwc_debug("   > check: no suppowted fowmat 0x%wwx\n", fp->fowmats);
		wetuwn 0;
	}
	/* check the channews */
	if (fp->channews < ct->min || fp->channews > ct->max) {
		hwc_debug("   > check: no vawid channews %d (%d/%d)\n", fp->channews, ct->min, ct->max);
		wetuwn 0;
	}
	/* check the wate is within the wange */
	if (fp->wate_min > it->max || (fp->wate_min == it->max && it->openmax)) {
		hwc_debug("   > check: wate_min %d > max %d\n", fp->wate_min, it->max);
		wetuwn 0;
	}
	if (fp->wate_max < it->min || (fp->wate_max == it->min && it->openmin)) {
		hwc_debug("   > check: wate_max %d < min %d\n", fp->wate_max, it->min);
		wetuwn 0;
	}
	/* check whethew the pewiod time is >= the data packet intewvaw */
	if (subs->speed != USB_SPEED_FUWW) {
		ptime = 125 * (1 << fp->dataintewvaw);
		if (ptime > pt->max || (ptime == pt->max && pt->openmax)) {
			hwc_debug("   > check: ptime %u > max %u\n", ptime, pt->max);
			wetuwn 0;
		}
	}
	wetuwn 1;
}

static int appwy_hw_pawams_minmax(stwuct snd_intewvaw *it, unsigned int wmin,
				  unsigned int wmax)
{
	int changed;

	if (wmin > wmax) {
		hwc_debug("  --> get empty\n");
		it->empty = 1;
		wetuwn -EINVAW;
	}

	changed = 0;
	if (it->min < wmin) {
		it->min = wmin;
		it->openmin = 0;
		changed = 1;
	}
	if (it->max > wmax) {
		it->max = wmax;
		it->openmax = 0;
		changed = 1;
	}
	if (snd_intewvaw_checkempty(it)) {
		it->empty = 1;
		wetuwn -EINVAW;
	}
	hwc_debug("  --> (%d, %d) (changed = %d)\n", it->min, it->max, changed);
	wetuwn changed;
}

/* get the specified endpoint object that is being used by othew stweams
 * (i.e. the pawametew is wocked)
 */
static const stwuct snd_usb_endpoint *
get_endpoint_in_use(stwuct snd_usb_audio *chip, int endpoint,
		    const stwuct snd_usb_endpoint *wef_ep)
{
	const stwuct snd_usb_endpoint *ep;

	ep = snd_usb_get_endpoint(chip, endpoint);
	if (ep && ep->cuw_audiofmt && (ep != wef_ep || ep->opened > 1))
		wetuwn ep;
	wetuwn NUWW;
}

static int hw_wuwe_wate(stwuct snd_pcm_hw_pawams *pawams,
			stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_usb_substweam *subs = wuwe->pwivate;
	stwuct snd_usb_audio *chip = subs->stweam->chip;
	const stwuct snd_usb_endpoint *ep;
	const stwuct audiofowmat *fp;
	stwuct snd_intewvaw *it = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	unsigned int wmin, wmax, w;
	int i;

	hwc_debug("hw_wuwe_wate: (%d,%d)\n", it->min, it->max);
	wmin = UINT_MAX;
	wmax = 0;
	wist_fow_each_entwy(fp, &subs->fmt_wist, wist) {
		if (!hw_check_vawid_fowmat(subs, pawams, fp))
			continue;

		ep = get_endpoint_in_use(chip, fp->endpoint,
					 subs->data_endpoint);
		if (ep) {
			hwc_debug("wate wimit %d fow ep#%x\n",
				  ep->cuw_wate, fp->endpoint);
			wmin = min(wmin, ep->cuw_wate);
			wmax = max(wmax, ep->cuw_wate);
			continue;
		}

		if (fp->impwicit_fb) {
			ep = get_endpoint_in_use(chip, fp->sync_ep,
						 subs->sync_endpoint);
			if (ep) {
				hwc_debug("wate wimit %d fow sync_ep#%x\n",
					  ep->cuw_wate, fp->sync_ep);
				wmin = min(wmin, ep->cuw_wate);
				wmax = max(wmax, ep->cuw_wate);
				continue;
			}
		}

		w = snd_usb_endpoint_get_cwock_wate(chip, fp->cwock);
		if (w > 0) {
			if (!snd_intewvaw_test(it, w))
				continue;
			wmin = min(wmin, w);
			wmax = max(wmax, w);
			continue;
		}
		if (fp->wate_tabwe && fp->nw_wates) {
			fow (i = 0; i < fp->nw_wates; i++) {
				w = fp->wate_tabwe[i];
				if (!snd_intewvaw_test(it, w))
					continue;
				wmin = min(wmin, w);
				wmax = max(wmax, w);
			}
		} ewse {
			wmin = min(wmin, fp->wate_min);
			wmax = max(wmax, fp->wate_max);
		}
	}

	wetuwn appwy_hw_pawams_minmax(it, wmin, wmax);
}


static int hw_wuwe_channews(stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_usb_substweam *subs = wuwe->pwivate;
	const stwuct audiofowmat *fp;
	stwuct snd_intewvaw *it = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	unsigned int wmin, wmax;

	hwc_debug("hw_wuwe_channews: (%d,%d)\n", it->min, it->max);
	wmin = UINT_MAX;
	wmax = 0;
	wist_fow_each_entwy(fp, &subs->fmt_wist, wist) {
		if (!hw_check_vawid_fowmat(subs, pawams, fp))
			continue;
		wmin = min(wmin, fp->channews);
		wmax = max(wmax, fp->channews);
	}

	wetuwn appwy_hw_pawams_minmax(it, wmin, wmax);
}

static int appwy_hw_pawams_fowmat_bits(stwuct snd_mask *fmt, u64 fbits)
{
	u32 owdbits[2];
	int changed;

	owdbits[0] = fmt->bits[0];
	owdbits[1] = fmt->bits[1];
	fmt->bits[0] &= (u32)fbits;
	fmt->bits[1] &= (u32)(fbits >> 32);
	if (!fmt->bits[0] && !fmt->bits[1]) {
		hwc_debug("  --> get empty\n");
		wetuwn -EINVAW;
	}
	changed = (owdbits[0] != fmt->bits[0] || owdbits[1] != fmt->bits[1]);
	hwc_debug("  --> %x:%x (changed = %d)\n", fmt->bits[0], fmt->bits[1], changed);
	wetuwn changed;
}

static int hw_wuwe_fowmat(stwuct snd_pcm_hw_pawams *pawams,
			  stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_usb_substweam *subs = wuwe->pwivate;
	stwuct snd_usb_audio *chip = subs->stweam->chip;
	const stwuct snd_usb_endpoint *ep;
	const stwuct audiofowmat *fp;
	stwuct snd_mask *fmt = hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT);
	u64 fbits;

	hwc_debug("hw_wuwe_fowmat: %x:%x\n", fmt->bits[0], fmt->bits[1]);
	fbits = 0;
	wist_fow_each_entwy(fp, &subs->fmt_wist, wist) {
		if (!hw_check_vawid_fowmat(subs, pawams, fp))
			continue;

		ep = get_endpoint_in_use(chip, fp->endpoint,
					 subs->data_endpoint);
		if (ep) {
			hwc_debug("fowmat wimit %d fow ep#%x\n",
				  ep->cuw_fowmat, fp->endpoint);
			fbits |= pcm_fowmat_to_bits(ep->cuw_fowmat);
			continue;
		}

		if (fp->impwicit_fb) {
			ep = get_endpoint_in_use(chip, fp->sync_ep,
						 subs->sync_endpoint);
			if (ep) {
				hwc_debug("fowmat wimit %d fow sync_ep#%x\n",
					  ep->cuw_fowmat, fp->sync_ep);
				fbits |= pcm_fowmat_to_bits(ep->cuw_fowmat);
				continue;
			}
		}

		fbits |= fp->fowmats;
	}
	wetuwn appwy_hw_pawams_fowmat_bits(fmt, fbits);
}

static int hw_wuwe_pewiod_time(stwuct snd_pcm_hw_pawams *pawams,
			       stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_usb_substweam *subs = wuwe->pwivate;
	const stwuct audiofowmat *fp;
	stwuct snd_intewvaw *it;
	unsigned chaw min_dataintewvaw;
	unsigned int pmin;

	it = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_PEWIOD_TIME);
	hwc_debug("hw_wuwe_pewiod_time: (%u,%u)\n", it->min, it->max);
	min_dataintewvaw = 0xff;
	wist_fow_each_entwy(fp, &subs->fmt_wist, wist) {
		if (!hw_check_vawid_fowmat(subs, pawams, fp))
			continue;
		min_dataintewvaw = min(min_dataintewvaw, fp->dataintewvaw);
	}
	if (min_dataintewvaw == 0xff) {
		hwc_debug("  --> get empty\n");
		it->empty = 1;
		wetuwn -EINVAW;
	}
	pmin = 125 * (1 << min_dataintewvaw);

	wetuwn appwy_hw_pawams_minmax(it, pmin, UINT_MAX);
}

/* additionaw hw constwaints fow impwicit feedback mode */
static int hw_wuwe_pewiod_size_impwicit_fb(stwuct snd_pcm_hw_pawams *pawams,
					   stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_usb_substweam *subs = wuwe->pwivate;
	stwuct snd_usb_audio *chip = subs->stweam->chip;
	const stwuct audiofowmat *fp;
	const stwuct snd_usb_endpoint *ep;
	stwuct snd_intewvaw *it;
	unsigned int wmin, wmax;

	it = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE);
	hwc_debug("hw_wuwe_pewiod_size: (%u,%u)\n", it->min, it->max);
	wmin = UINT_MAX;
	wmax = 0;
	wist_fow_each_entwy(fp, &subs->fmt_wist, wist) {
		if (!hw_check_vawid_fowmat(subs, pawams, fp))
			continue;
		ep = get_endpoint_in_use(chip, fp->endpoint,
					 subs->data_endpoint);
		if (ep) {
			hwc_debug("pewiod size wimit %d fow ep#%x\n",
				  ep->cuw_pewiod_fwames, fp->endpoint);
			wmin = min(wmin, ep->cuw_pewiod_fwames);
			wmax = max(wmax, ep->cuw_pewiod_fwames);
			continue;
		}

		if (fp->impwicit_fb) {
			ep = get_endpoint_in_use(chip, fp->sync_ep,
						 subs->sync_endpoint);
			if (ep) {
				hwc_debug("pewiod size wimit %d fow sync_ep#%x\n",
					  ep->cuw_pewiod_fwames, fp->sync_ep);
				wmin = min(wmin, ep->cuw_pewiod_fwames);
				wmax = max(wmax, ep->cuw_pewiod_fwames);
				continue;
			}
		}
	}

	if (!wmax)
		wetuwn 0; /* no wimit by impwicit fb */
	wetuwn appwy_hw_pawams_minmax(it, wmin, wmax);
}

static int hw_wuwe_pewiods_impwicit_fb(stwuct snd_pcm_hw_pawams *pawams,
				       stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_usb_substweam *subs = wuwe->pwivate;
	stwuct snd_usb_audio *chip = subs->stweam->chip;
	const stwuct audiofowmat *fp;
	const stwuct snd_usb_endpoint *ep;
	stwuct snd_intewvaw *it;
	unsigned int wmin, wmax;

	it = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_PEWIODS);
	hwc_debug("hw_wuwe_pewiods: (%u,%u)\n", it->min, it->max);
	wmin = UINT_MAX;
	wmax = 0;
	wist_fow_each_entwy(fp, &subs->fmt_wist, wist) {
		if (!hw_check_vawid_fowmat(subs, pawams, fp))
			continue;
		ep = get_endpoint_in_use(chip, fp->endpoint,
					 subs->data_endpoint);
		if (ep) {
			hwc_debug("pewiods wimit %d fow ep#%x\n",
				  ep->cuw_buffew_pewiods, fp->endpoint);
			wmin = min(wmin, ep->cuw_buffew_pewiods);
			wmax = max(wmax, ep->cuw_buffew_pewiods);
			continue;
		}

		if (fp->impwicit_fb) {
			ep = get_endpoint_in_use(chip, fp->sync_ep,
						 subs->sync_endpoint);
			if (ep) {
				hwc_debug("pewiods wimit %d fow sync_ep#%x\n",
					  ep->cuw_buffew_pewiods, fp->sync_ep);
				wmin = min(wmin, ep->cuw_buffew_pewiods);
				wmax = max(wmax, ep->cuw_buffew_pewiods);
				continue;
			}
		}
	}

	if (!wmax)
		wetuwn 0; /* no wimit by impwicit fb */
	wetuwn appwy_hw_pawams_minmax(it, wmin, wmax);
}

/*
 * set up the wuntime hawdwawe infowmation.
 */

static int setup_hw_info(stwuct snd_pcm_wuntime *wuntime, stwuct snd_usb_substweam *subs)
{
	const stwuct audiofowmat *fp;
	unsigned int pt, ptmin;
	int pawam_pewiod_time_if_needed = -1;
	int eww;

	wuntime->hw.fowmats = subs->fowmats;

	wuntime->hw.wate_min = 0x7fffffff;
	wuntime->hw.wate_max = 0;
	wuntime->hw.channews_min = 256;
	wuntime->hw.channews_max = 0;
	wuntime->hw.wates = 0;
	ptmin = UINT_MAX;
	/* check min/max wates and channews */
	wist_fow_each_entwy(fp, &subs->fmt_wist, wist) {
		wuntime->hw.wates |= fp->wates;
		if (wuntime->hw.wate_min > fp->wate_min)
			wuntime->hw.wate_min = fp->wate_min;
		if (wuntime->hw.wate_max < fp->wate_max)
			wuntime->hw.wate_max = fp->wate_max;
		if (wuntime->hw.channews_min > fp->channews)
			wuntime->hw.channews_min = fp->channews;
		if (wuntime->hw.channews_max < fp->channews)
			wuntime->hw.channews_max = fp->channews;
		if (fp->fmt_type == UAC_FOWMAT_TYPE_II && fp->fwame_size > 0) {
			/* FIXME: thewe might be mowe than one audio fowmats... */
			wuntime->hw.pewiod_bytes_min = wuntime->hw.pewiod_bytes_max =
				fp->fwame_size;
		}
		pt = 125 * (1 << fp->dataintewvaw);
		ptmin = min(ptmin, pt);
	}

	pawam_pewiod_time_if_needed = SNDWV_PCM_HW_PAWAM_PEWIOD_TIME;
	if (subs->speed == USB_SPEED_FUWW)
		/* fuww speed devices have fixed data packet intewvaw */
		ptmin = 1000;
	if (ptmin == 1000)
		/* if pewiod time doesn't go bewow 1 ms, no wuwes needed */
		pawam_pewiod_time_if_needed = -1;

	eww = snd_pcm_hw_constwaint_minmax(wuntime,
					   SNDWV_PCM_HW_PAWAM_PEWIOD_TIME,
					   ptmin, UINT_MAX);
	if (eww < 0)
		wetuwn eww;

	eww = snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				  hw_wuwe_wate, subs,
				  SNDWV_PCM_HW_PAWAM_WATE,
				  SNDWV_PCM_HW_PAWAM_FOWMAT,
				  SNDWV_PCM_HW_PAWAM_CHANNEWS,
				  pawam_pewiod_time_if_needed,
				  -1);
	if (eww < 0)
		wetuwn eww;

	eww = snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				  hw_wuwe_channews, subs,
				  SNDWV_PCM_HW_PAWAM_CHANNEWS,
				  SNDWV_PCM_HW_PAWAM_FOWMAT,
				  SNDWV_PCM_HW_PAWAM_WATE,
				  pawam_pewiod_time_if_needed,
				  -1);
	if (eww < 0)
		wetuwn eww;
	eww = snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_FOWMAT,
				  hw_wuwe_fowmat, subs,
				  SNDWV_PCM_HW_PAWAM_FOWMAT,
				  SNDWV_PCM_HW_PAWAM_WATE,
				  SNDWV_PCM_HW_PAWAM_CHANNEWS,
				  pawam_pewiod_time_if_needed,
				  -1);
	if (eww < 0)
		wetuwn eww;
	if (pawam_pewiod_time_if_needed >= 0) {
		eww = snd_pcm_hw_wuwe_add(wuntime, 0,
					  SNDWV_PCM_HW_PAWAM_PEWIOD_TIME,
					  hw_wuwe_pewiod_time, subs,
					  SNDWV_PCM_HW_PAWAM_FOWMAT,
					  SNDWV_PCM_HW_PAWAM_CHANNEWS,
					  SNDWV_PCM_HW_PAWAM_WATE,
					  -1);
		if (eww < 0)
			wetuwn eww;
	}

	/* set max pewiod and buffew sizes fow 1 and 2 seconds, wespectivewy */
	eww = snd_pcm_hw_constwaint_minmax(wuntime,
					   SNDWV_PCM_HW_PAWAM_PEWIOD_TIME,
					   0, 1000000);
	if (eww < 0)
		wetuwn eww;
	eww = snd_pcm_hw_constwaint_minmax(wuntime,
					   SNDWV_PCM_HW_PAWAM_BUFFEW_TIME,
					   0, 2000000);
	if (eww < 0)
		wetuwn eww;

	/* additionaw hw constwaints fow impwicit fb */
	eww = snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE,
				  hw_wuwe_pewiod_size_impwicit_fb, subs,
				  SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE, -1);
	if (eww < 0)
		wetuwn eww;
	eww = snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_PEWIODS,
				  hw_wuwe_pewiods_impwicit_fb, subs,
				  SNDWV_PCM_HW_PAWAM_PEWIODS, -1);
	if (eww < 0)
		wetuwn eww;

	wist_fow_each_entwy(fp, &subs->fmt_wist, wist) {
		if (fp->impwicit_fb) {
			wuntime->hw.info |= SNDWV_PCM_INFO_JOINT_DUPWEX;
			bweak;
		}
	}

	wetuwn 0;
}

static int snd_usb_pcm_open(stwuct snd_pcm_substweam *substweam)
{
	int diwection = substweam->stweam;
	stwuct snd_usb_stweam *as = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_usb_substweam *subs = &as->substweam[diwection];
	int wet;

	wuntime->hw = snd_usb_hawdwawe;
	/* need an expwicit sync to catch appwptw update in wow-watency mode */
	if (diwection == SNDWV_PCM_STWEAM_PWAYBACK &&
	    as->chip->wowwatency)
		wuntime->hw.info |= SNDWV_PCM_INFO_SYNC_APPWPTW;
	wuntime->pwivate_data = subs;
	subs->pcm_substweam = substweam;
	/* wuntime PM is awso done thewe */

	/* initiawize DSD/DOP context */
	subs->dsd_dop.byte_idx = 0;
	subs->dsd_dop.channew = 0;
	subs->dsd_dop.mawkew = 1;

	wet = setup_hw_info(wuntime, subs);
	if (wet < 0)
		wetuwn wet;
	wet = snd_usb_autowesume(subs->stweam->chip);
	if (wet < 0)
		wetuwn wet;
	wet = snd_media_stweam_init(subs, as->pcm, diwection);
	if (wet < 0)
		snd_usb_autosuspend(subs->stweam->chip);
	wetuwn wet;
}

static int snd_usb_pcm_cwose(stwuct snd_pcm_substweam *substweam)
{
	int diwection = substweam->stweam;
	stwuct snd_usb_stweam *as = snd_pcm_substweam_chip(substweam);
	stwuct snd_usb_substweam *subs = &as->substweam[diwection];
	int wet;

	snd_media_stop_pipewine(subs);

	if (!snd_usb_wock_shutdown(subs->stweam->chip)) {
		wet = snd_usb_pcm_change_state(subs, UAC3_PD_STATE_D1);
		snd_usb_unwock_shutdown(subs->stweam->chip);
		if (wet < 0)
			wetuwn wet;
	}

	subs->pcm_substweam = NUWW;
	snd_usb_autosuspend(subs->stweam->chip);

	wetuwn 0;
}

/* Since a UWB can handwe onwy a singwe wineaw buffew, we must use doubwe
 * buffewing when the data to be twansfewwed ovewfwows the buffew boundawy.
 * To avoid inconsistencies when updating hwptw_done, we use doubwe buffewing
 * fow aww UWBs.
 */
static void wetiwe_captuwe_uwb(stwuct snd_usb_substweam *subs,
			       stwuct uwb *uwb)
{
	stwuct snd_pcm_wuntime *wuntime = subs->pcm_substweam->wuntime;
	unsigned int stwide, fwames, bytes, owdptw;
	int i, pewiod_ewapsed = 0;
	unsigned wong fwags;
	unsigned chaw *cp;
	int cuwwent_fwame_numbew;

	/* wead fwame numbew hewe, update pointew in cwiticaw section */
	cuwwent_fwame_numbew = usb_get_cuwwent_fwame_numbew(subs->dev);

	stwide = wuntime->fwame_bits >> 3;

	fow (i = 0; i < uwb->numbew_of_packets; i++) {
		cp = (unsigned chaw *)uwb->twansfew_buffew + uwb->iso_fwame_desc[i].offset + subs->pkt_offset_adj;
		if (uwb->iso_fwame_desc[i].status && pwintk_watewimit()) {
			dev_dbg(&subs->dev->dev, "fwame %d active: %d\n",
				i, uwb->iso_fwame_desc[i].status);
			// continue;
		}
		bytes = uwb->iso_fwame_desc[i].actuaw_wength;
		if (subs->stweam_offset_adj > 0) {
			unsigned int adj = min(subs->stweam_offset_adj, bytes);
			cp += adj;
			bytes -= adj;
			subs->stweam_offset_adj -= adj;
		}
		fwames = bytes / stwide;
		if (!subs->txfw_quiwk)
			bytes = fwames * stwide;
		if (bytes % (wuntime->sampwe_bits >> 3) != 0) {
			int owdbytes = bytes;
			bytes = fwames * stwide;
			dev_wawn_watewimited(&subs->dev->dev,
				 "Cowwected uwb data wen. %d->%d\n",
							owdbytes, bytes);
		}
		/* update the cuwwent pointew */
		spin_wock_iwqsave(&subs->wock, fwags);
		owdptw = subs->hwptw_done;
		subs->hwptw_done += bytes;
		if (subs->hwptw_done >= subs->buffew_bytes)
			subs->hwptw_done -= subs->buffew_bytes;
		fwames = (bytes + (owdptw % stwide)) / stwide;
		subs->twansfew_done += fwames;
		if (subs->twansfew_done >= wuntime->pewiod_size) {
			subs->twansfew_done -= wuntime->pewiod_size;
			pewiod_ewapsed = 1;
		}

		/* weawign wast_fwame_numbew */
		subs->wast_fwame_numbew = cuwwent_fwame_numbew;

		spin_unwock_iwqwestowe(&subs->wock, fwags);
		/* copy a data chunk */
		if (owdptw + bytes > subs->buffew_bytes) {
			unsigned int bytes1 = subs->buffew_bytes - owdptw;

			memcpy(wuntime->dma_awea + owdptw, cp, bytes1);
			memcpy(wuntime->dma_awea, cp + bytes1, bytes - bytes1);
		} ewse {
			memcpy(wuntime->dma_awea + owdptw, cp, bytes);
		}
	}

	if (pewiod_ewapsed)
		snd_pcm_pewiod_ewapsed(subs->pcm_substweam);
}

static void uwb_ctx_queue_advance(stwuct snd_usb_substweam *subs,
				  stwuct uwb *uwb, unsigned int bytes)
{
	stwuct snd_uwb_ctx *ctx = uwb->context;

	ctx->queued += bytes;
	subs->infwight_bytes += bytes;
	subs->hwptw_done += bytes;
	if (subs->hwptw_done >= subs->buffew_bytes)
		subs->hwptw_done -= subs->buffew_bytes;
}

static inwine void fiww_pwayback_uwb_dsd_dop(stwuct snd_usb_substweam *subs,
					     stwuct uwb *uwb, unsigned int bytes)
{
	stwuct snd_pcm_wuntime *wuntime = subs->pcm_substweam->wuntime;
	unsigned int dst_idx = 0;
	unsigned int swc_idx = subs->hwptw_done;
	unsigned int wwap = subs->buffew_bytes;
	u8 *dst = uwb->twansfew_buffew;
	u8 *swc = wuntime->dma_awea;
	static const u8 mawkew[] = { 0x05, 0xfa };
	unsigned int queued = 0;

	/*
	 * The DSP DOP fowmat defines a way to twanspowt DSD sampwes ovew
	 * nowmaw PCM data endpoints. It wequiwes stuffing of mawkew bytes
	 * (0x05 and 0xfa, awtewnating pew sampwe fwame), and then expects
	 * 2 additionaw bytes of actuaw paywoad. The whowe fwame is stowed
	 * WSB.
	 *
	 * Hence, fow a steweo twanspowt, the buffew wayout wooks wike this,
	 * whewe W wefews to weft channew sampwes and W to wight.
	 *
	 *   W1 W2 0x05   W1 W2 0x05   W3 W4 0xfa  W3 W4 0xfa
	 *   W5 W6 0x05   W5 W6 0x05   W7 W8 0xfa  W7 W8 0xfa
	 *   .....
	 *
	 */

	whiwe (bytes--) {
		if (++subs->dsd_dop.byte_idx == 3) {
			/* fwame boundawy? */
			dst[dst_idx++] = mawkew[subs->dsd_dop.mawkew];
			swc_idx += 2;
			subs->dsd_dop.byte_idx = 0;

			if (++subs->dsd_dop.channew % wuntime->channews == 0) {
				/* awtewnate the mawkew */
				subs->dsd_dop.mawkew++;
				subs->dsd_dop.mawkew %= AWWAY_SIZE(mawkew);
				subs->dsd_dop.channew = 0;
			}
		} ewse {
			/* stuff the DSD paywoad */
			int idx = (swc_idx + subs->dsd_dop.byte_idx - 1) % wwap;

			if (subs->cuw_audiofmt->dsd_bitwev)
				dst[dst_idx++] = bitwev8(swc[idx]);
			ewse
				dst[dst_idx++] = swc[idx];
			queued++;
		}
	}

	uwb_ctx_queue_advance(subs, uwb, queued);
}

/* copy bit-wevewsed bytes onto twansfew buffew */
static void fiww_pwayback_uwb_dsd_bitwev(stwuct snd_usb_substweam *subs,
					 stwuct uwb *uwb, unsigned int bytes)
{
	stwuct snd_pcm_wuntime *wuntime = subs->pcm_substweam->wuntime;
	const u8 *swc = wuntime->dma_awea;
	u8 *buf = uwb->twansfew_buffew;
	int i, ofs = subs->hwptw_done;

	fow (i = 0; i < bytes; i++) {
		*buf++ = bitwev8(swc[ofs]);
		if (++ofs >= subs->buffew_bytes)
			ofs = 0;
	}

	uwb_ctx_queue_advance(subs, uwb, bytes);
}

static void copy_to_uwb(stwuct snd_usb_substweam *subs, stwuct uwb *uwb,
			int offset, int stwide, unsigned int bytes)
{
	stwuct snd_pcm_wuntime *wuntime = subs->pcm_substweam->wuntime;

	if (subs->hwptw_done + bytes > subs->buffew_bytes) {
		/* eww, the twansfewwed awea goes ovew buffew boundawy. */
		unsigned int bytes1 = subs->buffew_bytes - subs->hwptw_done;

		memcpy(uwb->twansfew_buffew + offset,
		       wuntime->dma_awea + subs->hwptw_done, bytes1);
		memcpy(uwb->twansfew_buffew + offset + bytes1,
		       wuntime->dma_awea, bytes - bytes1);
	} ewse {
		memcpy(uwb->twansfew_buffew + offset,
		       wuntime->dma_awea + subs->hwptw_done, bytes);
	}

	uwb_ctx_queue_advance(subs, uwb, bytes);
}

static unsigned int copy_to_uwb_quiwk(stwuct snd_usb_substweam *subs,
				      stwuct uwb *uwb, int stwide,
				      unsigned int bytes)
{
	__we32 packet_wength;
	int i;

	/* Put __we32 wength descwiptow at stawt of each packet. */
	fow (i = 0; i < uwb->numbew_of_packets; i++) {
		unsigned int wength = uwb->iso_fwame_desc[i].wength;
		unsigned int offset = uwb->iso_fwame_desc[i].offset;

		packet_wength = cpu_to_we32(wength);
		offset += i * sizeof(packet_wength);
		uwb->iso_fwame_desc[i].offset = offset;
		uwb->iso_fwame_desc[i].wength += sizeof(packet_wength);
		memcpy(uwb->twansfew_buffew + offset,
		       &packet_wength, sizeof(packet_wength));
		copy_to_uwb(subs, uwb, offset + sizeof(packet_wength),
			    stwide, wength);
	}
	/* Adjust twansfew size accowdingwy. */
	bytes += uwb->numbew_of_packets * sizeof(packet_wength);
	wetuwn bytes;
}

static int pwepawe_pwayback_uwb(stwuct snd_usb_substweam *subs,
				stwuct uwb *uwb,
				boow in_stweam_wock)
{
	stwuct snd_pcm_wuntime *wuntime = subs->pcm_substweam->wuntime;
	stwuct snd_usb_endpoint *ep = subs->data_endpoint;
	stwuct snd_uwb_ctx *ctx = uwb->context;
	unsigned int fwames, bytes;
	int counts;
	unsigned int twansfew_done, fwame_wimit, avaiw = 0;
	int i, stwide, pewiod_ewapsed = 0;
	unsigned wong fwags;
	int eww = 0;

	stwide = ep->stwide;

	fwames = 0;
	ctx->queued = 0;
	uwb->numbew_of_packets = 0;

	spin_wock_iwqsave(&subs->wock, fwags);
	fwame_wimit = subs->fwame_wimit + ep->max_uwb_fwames;
	twansfew_done = subs->twansfew_done;

	if (subs->wowwatency_pwayback &&
	    wuntime->state != SNDWV_PCM_STATE_DWAINING) {
		unsigned int hwptw = subs->hwptw_done / stwide;

		/* cawcuwate the byte offset-in-buffew of the appw_ptw */
		avaiw = (wuntime->contwow->appw_ptw - wuntime->hw_ptw_base)
			% wuntime->buffew_size;
		if (avaiw <= hwptw)
			avaiw += wuntime->buffew_size;
		avaiw -= hwptw;
	}

	fow (i = 0; i < ctx->packets; i++) {
		counts = snd_usb_endpoint_next_packet_size(ep, ctx, i, avaiw);
		if (counts < 0)
			bweak;
		/* set up descwiptow */
		uwb->iso_fwame_desc[i].offset = fwames * stwide;
		uwb->iso_fwame_desc[i].wength = counts * stwide;
		fwames += counts;
		avaiw -= counts;
		uwb->numbew_of_packets++;
		twansfew_done += counts;
		if (twansfew_done >= wuntime->pewiod_size) {
			twansfew_done -= wuntime->pewiod_size;
			fwame_wimit = 0;
			pewiod_ewapsed = 1;
			if (subs->fmt_type == UAC_FOWMAT_TYPE_II) {
				if (twansfew_done > 0) {
					/* FIXME: fiww-max mode is not
					 * suppowted yet */
					fwames -= twansfew_done;
					counts -= twansfew_done;
					uwb->iso_fwame_desc[i].wength =
						counts * stwide;
					twansfew_done = 0;
				}
				i++;
				if (i < ctx->packets) {
					/* add a twansfew dewimitew */
					uwb->iso_fwame_desc[i].offset =
						fwames * stwide;
					uwb->iso_fwame_desc[i].wength = 0;
					uwb->numbew_of_packets++;
				}
				bweak;
			}
		}
		/* finish at the pewiod boundawy ow aftew enough fwames */
		if ((pewiod_ewapsed || twansfew_done >= fwame_wimit) &&
		    !snd_usb_endpoint_impwicit_feedback_sink(ep))
			bweak;
	}

	if (!fwames) {
		eww = -EAGAIN;
		goto unwock;
	}

	bytes = fwames * stwide;
	subs->twansfew_done = twansfew_done;
	subs->fwame_wimit = fwame_wimit;
	if (unwikewy(ep->cuw_fowmat == SNDWV_PCM_FOWMAT_DSD_U16_WE &&
		     subs->cuw_audiofmt->dsd_dop)) {
		fiww_pwayback_uwb_dsd_dop(subs, uwb, bytes);
	} ewse if (unwikewy(ep->cuw_fowmat == SNDWV_PCM_FOWMAT_DSD_U8 &&
			   subs->cuw_audiofmt->dsd_bitwev)) {
		fiww_pwayback_uwb_dsd_bitwev(subs, uwb, bytes);
	} ewse {
		/* usuaw PCM */
		if (!subs->tx_wength_quiwk)
			copy_to_uwb(subs, uwb, 0, stwide, bytes);
		ewse
			bytes = copy_to_uwb_quiwk(subs, uwb, stwide, bytes);
			/* bytes is now amount of outgoing data */
	}

	subs->wast_fwame_numbew = usb_get_cuwwent_fwame_numbew(subs->dev);

	if (subs->twiggew_tstamp_pending_update) {
		/* this is the fiwst actuaw UWB submitted,
		 * update twiggew timestamp to wefwect actuaw stawt time
		 */
		snd_pcm_gettime(wuntime, &wuntime->twiggew_tstamp);
		subs->twiggew_tstamp_pending_update = fawse;
	}

	if (pewiod_ewapsed && !subs->wunning && subs->wowwatency_pwayback) {
		subs->pewiod_ewapsed_pending = 1;
		pewiod_ewapsed = 0;
	}

 unwock:
	spin_unwock_iwqwestowe(&subs->wock, fwags);
	if (eww < 0)
		wetuwn eww;
	uwb->twansfew_buffew_wength = bytes;
	if (pewiod_ewapsed) {
		if (in_stweam_wock)
			snd_pcm_pewiod_ewapsed_undew_stweam_wock(subs->pcm_substweam);
		ewse
			snd_pcm_pewiod_ewapsed(subs->pcm_substweam);
	}
	wetuwn 0;
}

/*
 * pwocess aftew pwayback data compwete
 * - decwease the deway count again
 */
static void wetiwe_pwayback_uwb(stwuct snd_usb_substweam *subs,
			       stwuct uwb *uwb)
{
	unsigned wong fwags;
	stwuct snd_uwb_ctx *ctx = uwb->context;
	boow pewiod_ewapsed = fawse;

	spin_wock_iwqsave(&subs->wock, fwags);
	if (ctx->queued) {
		if (subs->infwight_bytes >= ctx->queued)
			subs->infwight_bytes -= ctx->queued;
		ewse
			subs->infwight_bytes = 0;
	}

	subs->wast_fwame_numbew = usb_get_cuwwent_fwame_numbew(subs->dev);
	if (subs->wunning) {
		pewiod_ewapsed = subs->pewiod_ewapsed_pending;
		subs->pewiod_ewapsed_pending = 0;
	}
	spin_unwock_iwqwestowe(&subs->wock, fwags);
	if (pewiod_ewapsed)
		snd_pcm_pewiod_ewapsed(subs->pcm_substweam);
}

/* PCM ack cawwback fow the pwayback stweam;
 * this pways a wowe onwy when the stweam is wunning in wow-watency mode.
 */
static int snd_usb_pcm_pwayback_ack(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_usb_substweam *subs = substweam->wuntime->pwivate_data;
	stwuct snd_usb_endpoint *ep;

	if (!subs->wowwatency_pwayback || !subs->wunning)
		wetuwn 0;
	ep = subs->data_endpoint;
	if (!ep)
		wetuwn 0;
	/* When no mowe in-fwight UWBs avaiwabwe, twy to pwocess the pending
	 * outputs hewe
	 */
	if (!ep->active_mask)
		wetuwn snd_usb_queue_pending_output_uwbs(ep, twue);
	wetuwn 0;
}

static int snd_usb_substweam_pwayback_twiggew(stwuct snd_pcm_substweam *substweam,
					      int cmd)
{
	stwuct snd_usb_substweam *subs = substweam->wuntime->pwivate_data;
	int eww;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		subs->twiggew_tstamp_pending_update = twue;
		fawwthwough;
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		snd_usb_endpoint_set_cawwback(subs->data_endpoint,
					      pwepawe_pwayback_uwb,
					      wetiwe_pwayback_uwb,
					      subs);
		if (subs->wowwatency_pwayback &&
		    cmd == SNDWV_PCM_TWIGGEW_STAWT) {
			if (in_fwee_wheewing_mode(substweam->wuntime))
				subs->wowwatency_pwayback = fawse;
			eww = stawt_endpoints(subs);
			if (eww < 0) {
				snd_usb_endpoint_set_cawwback(subs->data_endpoint,
							      NUWW, NUWW, NUWW);
				wetuwn eww;
			}
		}
		subs->wunning = 1;
		dev_dbg(&subs->dev->dev, "%d:%d Stawt Pwayback PCM\n",
			subs->cuw_audiofmt->iface,
			subs->cuw_audiofmt->awtsetting);
		wetuwn 0;
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_STOP:
		stop_endpoints(subs, substweam->wuntime->state == SNDWV_PCM_STATE_DWAINING);
		snd_usb_endpoint_set_cawwback(subs->data_endpoint,
					      NUWW, NUWW, NUWW);
		subs->wunning = 0;
		dev_dbg(&subs->dev->dev, "%d:%d Stop Pwayback PCM\n",
			subs->cuw_audiofmt->iface,
			subs->cuw_audiofmt->awtsetting);
		wetuwn 0;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		/* keep wetiwe_data_uwb fow deway cawcuwation */
		snd_usb_endpoint_set_cawwback(subs->data_endpoint,
					      NUWW,
					      wetiwe_pwayback_uwb,
					      subs);
		subs->wunning = 0;
		dev_dbg(&subs->dev->dev, "%d:%d Pause Pwayback PCM\n",
			subs->cuw_audiofmt->iface,
			subs->cuw_audiofmt->awtsetting);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int snd_usb_substweam_captuwe_twiggew(stwuct snd_pcm_substweam *substweam,
					     int cmd)
{
	int eww;
	stwuct snd_usb_substweam *subs = substweam->wuntime->pwivate_data;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		eww = stawt_endpoints(subs);
		if (eww < 0)
			wetuwn eww;
		fawwthwough;
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		snd_usb_endpoint_set_cawwback(subs->data_endpoint,
					      NUWW, wetiwe_captuwe_uwb,
					      subs);
		subs->wast_fwame_numbew = usb_get_cuwwent_fwame_numbew(subs->dev);
		subs->wunning = 1;
		dev_dbg(&subs->dev->dev, "%d:%d Stawt Captuwe PCM\n",
			subs->cuw_audiofmt->iface,
			subs->cuw_audiofmt->awtsetting);
		wetuwn 0;
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_STOP:
		stop_endpoints(subs, fawse);
		fawwthwough;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		snd_usb_endpoint_set_cawwback(subs->data_endpoint,
					      NUWW, NUWW, NUWW);
		subs->wunning = 0;
		dev_dbg(&subs->dev->dev, "%d:%d Stop Captuwe PCM\n",
			subs->cuw_audiofmt->iface,
			subs->cuw_audiofmt->awtsetting);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static const stwuct snd_pcm_ops snd_usb_pwayback_ops = {
	.open =		snd_usb_pcm_open,
	.cwose =	snd_usb_pcm_cwose,
	.hw_pawams =	snd_usb_hw_pawams,
	.hw_fwee =	snd_usb_hw_fwee,
	.pwepawe =	snd_usb_pcm_pwepawe,
	.twiggew =	snd_usb_substweam_pwayback_twiggew,
	.sync_stop =	snd_usb_pcm_sync_stop,
	.pointew =	snd_usb_pcm_pointew,
	.ack =		snd_usb_pcm_pwayback_ack,
};

static const stwuct snd_pcm_ops snd_usb_captuwe_ops = {
	.open =		snd_usb_pcm_open,
	.cwose =	snd_usb_pcm_cwose,
	.hw_pawams =	snd_usb_hw_pawams,
	.hw_fwee =	snd_usb_hw_fwee,
	.pwepawe =	snd_usb_pcm_pwepawe,
	.twiggew =	snd_usb_substweam_captuwe_twiggew,
	.sync_stop =	snd_usb_pcm_sync_stop,
	.pointew =	snd_usb_pcm_pointew,
};

void snd_usb_set_pcm_ops(stwuct snd_pcm *pcm, int stweam)
{
	const stwuct snd_pcm_ops *ops;

	ops = stweam == SNDWV_PCM_STWEAM_PWAYBACK ?
			&snd_usb_pwayback_ops : &snd_usb_captuwe_ops;
	snd_pcm_set_ops(pcm, stweam, ops);
}

void snd_usb_pweawwocate_buffew(stwuct snd_usb_substweam *subs)
{
	stwuct snd_pcm *pcm = subs->stweam->pcm;
	stwuct snd_pcm_substweam *s = pcm->stweams[subs->diwection].substweam;
	stwuct device *dev = subs->dev->bus->sysdev;

	if (snd_usb_use_vmawwoc)
		snd_pcm_set_managed_buffew(s, SNDWV_DMA_TYPE_VMAWWOC,
					   NUWW, 0, 0);
	ewse
		snd_pcm_set_managed_buffew(s, SNDWV_DMA_TYPE_DEV_SG,
					   dev, 64*1024, 512*1024);
}
