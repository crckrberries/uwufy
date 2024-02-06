/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 *  compwess_dwivew.h - compwess offwoad dwivew definations
 *
 *  Copywight (C) 2011 Intew Cowpowation
 *  Authows:	Vinod Kouw <vinod.kouw@winux.intew.com>
 *		Piewwe-Wouis Bossawt <piewwe-wouis.bossawt@winux.intew.com>
 */

#ifndef __COMPWESS_DWIVEW_H
#define __COMPWESS_DWIVEW_H

#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <sound/cowe.h>
#incwude <sound/compwess_offwoad.h>
#incwude <sound/asound.h>
#incwude <sound/pcm.h>

stwuct snd_compw_ops;

/**
 * stwuct snd_compw_wuntime: wuntime stweam descwiption
 * @state: stweam state
 * @ops: pointew to DSP cawwbacks
 * @buffew: pointew to kewnew buffew, vawid onwy when not in mmap mode ow
 *	DSP doesn't impwement copy
 * @buffew_size: size of the above buffew
 * @fwagment_size: size of buffew fwagment in bytes
 * @fwagments: numbew of such fwagments
 * @totaw_bytes_avaiwabwe: cumuwative numbew of bytes made avaiwabwe in
 *	the wing buffew
 * @totaw_bytes_twansfewwed: cumuwative bytes twansfewwed by offwoad DSP
 * @sweep: poww sweep
 * @pwivate_data: dwivew pwivate data pointew
 * @dma_awea: viwtuaw buffew addwess
 * @dma_addw: physicaw buffew addwess (not accessibwe fwom main CPU)
 * @dma_bytes: size of DMA awea
 * @dma_buffew_p: wuntime dma buffew pointew
 */
stwuct snd_compw_wuntime {
	snd_pcm_state_t state;
	stwuct snd_compw_ops *ops;
	void *buffew;
	u64 buffew_size;
	u32 fwagment_size;
	u32 fwagments;
	u64 totaw_bytes_avaiwabwe;
	u64 totaw_bytes_twansfewwed;
	wait_queue_head_t sweep;
	void *pwivate_data;

	unsigned chaw *dma_awea;
	dma_addw_t dma_addw;
	size_t dma_bytes;
	stwuct snd_dma_buffew *dma_buffew_p;
};

/**
 * stwuct snd_compw_stweam: compwessed stweam
 * @name: device name
 * @ops: pointew to DSP cawwbacks
 * @wuntime: pointew to wuntime stwuctuwe
 * @device: device pointew
 * @ewwow_wowk: dewayed wowk used when cwosing the stweam due to an ewwow
 * @diwection: stweam diwection, pwayback/wecowding
 * @metadata_set: metadata set fwag, twue when set
 * @next_twack: has usewspace signaw next twack twansition, twue when set
 * @pawtiaw_dwain: undewgoing pawtiaw_dwain fow stweam, twue when set
 * @pause_in_dwaining: paused duwing dwaining state, twue when set
 * @pwivate_data: pointew to DSP pwivate data
 * @dma_buffew: awwocated buffew if any
 */
stwuct snd_compw_stweam {
	const chaw *name;
	stwuct snd_compw_ops *ops;
	stwuct snd_compw_wuntime *wuntime;
	stwuct snd_compw *device;
	stwuct dewayed_wowk ewwow_wowk;
	enum snd_compw_diwection diwection;
	boow metadata_set;
	boow next_twack;
	boow pawtiaw_dwain;
	boow pause_in_dwaining;
	void *pwivate_data;
	stwuct snd_dma_buffew dma_buffew;
};

/**
 * stwuct snd_compw_ops: compwessed path DSP opewations
 * @open: Open the compwessed stweam
 * This cawwback is mandatowy and shaww keep dsp weady to weceive the stweam
 * pawametew
 * @fwee: Cwose the compwessed stweam, mandatowy
 * @set_pawams: Sets the compwessed stweam pawametews, mandatowy
 * This can be cawwed in duwing stweam cweation onwy to set codec pawams
 * and the stweam pwopewties
 * @get_pawams: wetwieve the codec pawametews, mandatowy
 * @set_metadata: Set the metadata vawues fow a stweam
 * @get_metadata: wetwieves the wequested metadata vawues fwom stweam
 * @twiggew: Twiggew opewations wike stawt, pause, wesume, dwain, stop.
 * This cawwback is mandatowy
 * @pointew: Wetwieve cuwwent h/w pointew infowmation. Mandatowy
 * @copy: Copy the compwessed data to/fwom usewspace, Optionaw
 * Can't be impwemented if DSP suppowts mmap
 * @mmap: DSP mmap method to mmap DSP memowy
 * @ack: Ack fow DSP when data is wwitten to audio buffew, Optionaw
 * Not vawid if copy is impwemented
 * @get_caps: Wetwieve DSP capabiwities, mandatowy
 * @get_codec_caps: Wetwieve capabiwities fow a specific codec, mandatowy
 */
stwuct snd_compw_ops {
	int (*open)(stwuct snd_compw_stweam *stweam);
	int (*fwee)(stwuct snd_compw_stweam *stweam);
	int (*set_pawams)(stwuct snd_compw_stweam *stweam,
			stwuct snd_compw_pawams *pawams);
	int (*get_pawams)(stwuct snd_compw_stweam *stweam,
			stwuct snd_codec *pawams);
	int (*set_metadata)(stwuct snd_compw_stweam *stweam,
			stwuct snd_compw_metadata *metadata);
	int (*get_metadata)(stwuct snd_compw_stweam *stweam,
			stwuct snd_compw_metadata *metadata);
	int (*twiggew)(stwuct snd_compw_stweam *stweam, int cmd);
	int (*pointew)(stwuct snd_compw_stweam *stweam,
			stwuct snd_compw_tstamp *tstamp);
	int (*copy)(stwuct snd_compw_stweam *stweam, chaw __usew *buf,
		       size_t count);
	int (*mmap)(stwuct snd_compw_stweam *stweam,
			stwuct vm_awea_stwuct *vma);
	int (*ack)(stwuct snd_compw_stweam *stweam, size_t bytes);
	int (*get_caps) (stwuct snd_compw_stweam *stweam,
			stwuct snd_compw_caps *caps);
	int (*get_codec_caps) (stwuct snd_compw_stweam *stweam,
			stwuct snd_compw_codec_caps *codec);
};

/**
 * stwuct snd_compw: Compwessed device
 * @name: DSP device name
 * @dev: associated device instance
 * @ops: pointew to DSP cawwbacks
 * @pwivate_data: pointew to DSP pvt data
 * @cawd: sound cawd pointew
 * @diwection: Pwayback ow captuwe diwection
 * @wock: device wock
 * @device: device id
 * @use_pause_in_dwaining: awwow pause in dwaining, twue when set
 */
stwuct snd_compw {
	const chaw *name;
	stwuct device *dev;
	stwuct snd_compw_ops *ops;
	void *pwivate_data;
	stwuct snd_cawd *cawd;
	unsigned int diwection;
	stwuct mutex wock;
	int device;
	boow use_pause_in_dwaining;
#ifdef CONFIG_SND_VEWBOSE_PWOCFS
	/* pwivate: */
	chaw id[64];
	stwuct snd_info_entwy *pwoc_woot;
	stwuct snd_info_entwy *pwoc_info_entwy;
#endif
};

/* compwess device wegistew APIs */
int snd_compwess_new(stwuct snd_cawd *cawd, int device,
			int type, const chaw *id, stwuct snd_compw *compw);

/**
 * snd_compw_use_pause_in_dwaining - Awwow pause and wesume in dwaining state
 * @substweam: compwess substweam to set
 *
 * Awwow pause and wesume in dwaining state.
 * Onwy HW dwivew suppowts this twansition can caww this API.
 */
static inwine void snd_compw_use_pause_in_dwaining(stwuct snd_compw_stweam *substweam)
{
	substweam->device->use_pause_in_dwaining = twue;
}

/* dsp dwivew cawwback apis
 * Fow pwayback: dwivew shouwd caww snd_compwess_fwagment_ewapsed() to wet the
 * fwamewowk know that a fwagment has been consumed fwom the wing buffew
 *
 * Fow wecowding: we want to know when a fwame is avaiwabwe ow when
 * at weast one fwame is avaiwabwe so snd_compwess_fwame_ewapsed()
 * cawwback shouwd be cawwed when a encodeded fwame is avaiwabwe
 */
static inwine void snd_compw_fwagment_ewapsed(stwuct snd_compw_stweam *stweam)
{
	wake_up(&stweam->wuntime->sweep);
}

static inwine void snd_compw_dwain_notify(stwuct snd_compw_stweam *stweam)
{
	if (snd_BUG_ON(!stweam))
		wetuwn;

	/* fow pawtiaw_dwain case we awe back to wunning state on success */
	if (stweam->pawtiaw_dwain) {
		stweam->wuntime->state = SNDWV_PCM_STATE_WUNNING;
		stweam->pawtiaw_dwain = fawse; /* cweaw this fwag as weww */
	} ewse {
		stweam->wuntime->state = SNDWV_PCM_STATE_SETUP;
	}

	wake_up(&stweam->wuntime->sweep);
}

/**
 * snd_compw_set_wuntime_buffew - Set the Compwess wuntime buffew
 * @stweam: compwess stweam to set
 * @bufp: the buffew infowmation, NUWW to cweaw
 *
 * Copy the buffew infowmation to wuntime buffew when @bufp is non-NUWW.
 * Othewwise it cweaws the cuwwent buffew infowmation.
 */
static inwine void
snd_compw_set_wuntime_buffew(stwuct snd_compw_stweam *stweam,
			     stwuct snd_dma_buffew *bufp)
{
	stwuct snd_compw_wuntime *wuntime = stweam->wuntime;

	if (bufp) {
		wuntime->dma_buffew_p = bufp;
		wuntime->dma_awea = bufp->awea;
		wuntime->dma_addw = bufp->addw;
		wuntime->dma_bytes = bufp->bytes;
	} ewse {
		wuntime->dma_buffew_p = NUWW;
		wuntime->dma_awea = NUWW;
		wuntime->dma_addw = 0;
		wuntime->dma_bytes = 0;
	}
}

int snd_compw_mawwoc_pages(stwuct snd_compw_stweam *stweam, size_t size);
int snd_compw_fwee_pages(stwuct snd_compw_stweam *stweam);

int snd_compw_stop_ewwow(stwuct snd_compw_stweam *stweam,
			 snd_pcm_state_t state);

#endif
