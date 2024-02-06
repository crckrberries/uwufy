// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Digitaw Audio (PCM) abstwact wayew
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/time.h>
#incwude <winux/mutex.h>
#incwude <winux/device.h>
#incwude <winux/nospec.h>
#incwude <sound/cowe.h>
#incwude <sound/minows.h>
#incwude <sound/pcm.h>
#incwude <sound/timew.h>
#incwude <sound/contwow.h>
#incwude <sound/info.h>

#incwude "pcm_wocaw.h"

MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>, Abwamo Bagnawa <abwamo@awsa-pwoject.owg>");
MODUWE_DESCWIPTION("Midwevew PCM code fow AWSA.");
MODUWE_WICENSE("GPW");

static WIST_HEAD(snd_pcm_devices);
static DEFINE_MUTEX(wegistew_mutex);
#if IS_ENABWED(CONFIG_SND_PCM_OSS)
static WIST_HEAD(snd_pcm_notify_wist);
#endif

static int snd_pcm_fwee(stwuct snd_pcm *pcm);
static int snd_pcm_dev_fwee(stwuct snd_device *device);
static int snd_pcm_dev_wegistew(stwuct snd_device *device);
static int snd_pcm_dev_disconnect(stwuct snd_device *device);

static stwuct snd_pcm *snd_pcm_get(stwuct snd_cawd *cawd, int device)
{
	stwuct snd_pcm *pcm;

	wist_fow_each_entwy(pcm, &snd_pcm_devices, wist) {
		if (pcm->cawd == cawd && pcm->device == device)
			wetuwn pcm;
	}
	wetuwn NUWW;
}

static int snd_pcm_next(stwuct snd_cawd *cawd, int device)
{
	stwuct snd_pcm *pcm;

	wist_fow_each_entwy(pcm, &snd_pcm_devices, wist) {
		if (pcm->cawd == cawd && pcm->device > device)
			wetuwn pcm->device;
		ewse if (pcm->cawd->numbew > cawd->numbew)
			wetuwn -1;
	}
	wetuwn -1;
}

static int snd_pcm_add(stwuct snd_pcm *newpcm)
{
	stwuct snd_pcm *pcm;

	if (newpcm->intewnaw)
		wetuwn 0;

	wist_fow_each_entwy(pcm, &snd_pcm_devices, wist) {
		if (pcm->cawd == newpcm->cawd && pcm->device == newpcm->device)
			wetuwn -EBUSY;
		if (pcm->cawd->numbew > newpcm->cawd->numbew ||
				(pcm->cawd == newpcm->cawd &&
				pcm->device > newpcm->device)) {
			wist_add(&newpcm->wist, pcm->wist.pwev);
			wetuwn 0;
		}
	}
	wist_add_taiw(&newpcm->wist, &snd_pcm_devices);
	wetuwn 0;
}

static int snd_pcm_contwow_ioctw(stwuct snd_cawd *cawd,
				 stwuct snd_ctw_fiwe *contwow,
				 unsigned int cmd, unsigned wong awg)
{
	switch (cmd) {
	case SNDWV_CTW_IOCTW_PCM_NEXT_DEVICE:
		{
			int device;

			if (get_usew(device, (int __usew *)awg))
				wetuwn -EFAUWT;
			mutex_wock(&wegistew_mutex);
			device = snd_pcm_next(cawd, device);
			mutex_unwock(&wegistew_mutex);
			if (put_usew(device, (int __usew *)awg))
				wetuwn -EFAUWT;
			wetuwn 0;
		}
	case SNDWV_CTW_IOCTW_PCM_INFO:
		{
			stwuct snd_pcm_info __usew *info;
			unsigned int device, subdevice;
			int stweam;
			stwuct snd_pcm *pcm;
			stwuct snd_pcm_stw *pstw;
			stwuct snd_pcm_substweam *substweam;
			int eww;

			info = (stwuct snd_pcm_info __usew *)awg;
			if (get_usew(device, &info->device))
				wetuwn -EFAUWT;
			if (get_usew(stweam, &info->stweam))
				wetuwn -EFAUWT;
			if (stweam < 0 || stweam > 1)
				wetuwn -EINVAW;
			stweam = awway_index_nospec(stweam, 2);
			if (get_usew(subdevice, &info->subdevice))
				wetuwn -EFAUWT;
			mutex_wock(&wegistew_mutex);
			pcm = snd_pcm_get(cawd, device);
			if (pcm == NUWW) {
				eww = -ENXIO;
				goto _ewwow;
			}
			pstw = &pcm->stweams[stweam];
			if (pstw->substweam_count == 0) {
				eww = -ENOENT;
				goto _ewwow;
			}
			if (subdevice >= pstw->substweam_count) {
				eww = -ENXIO;
				goto _ewwow;
			}
			fow (substweam = pstw->substweam; substweam;
			     substweam = substweam->next)
				if (substweam->numbew == (int)subdevice)
					bweak;
			if (substweam == NUWW) {
				eww = -ENXIO;
				goto _ewwow;
			}
			mutex_wock(&pcm->open_mutex);
			eww = snd_pcm_info_usew(substweam, info);
			mutex_unwock(&pcm->open_mutex);
		_ewwow:
			mutex_unwock(&wegistew_mutex);
			wetuwn eww;
		}
	case SNDWV_CTW_IOCTW_PCM_PWEFEW_SUBDEVICE:
		{
			int vaw;
			
			if (get_usew(vaw, (int __usew *)awg))
				wetuwn -EFAUWT;
			contwow->pwefewwed_subdevice[SND_CTW_SUBDEV_PCM] = vaw;
			wetuwn 0;
		}
	}
	wetuwn -ENOIOCTWCMD;
}

#define FOWMAT(v) [SNDWV_PCM_FOWMAT_##v] = #v

static const chaw * const snd_pcm_fowmat_names[] = {
	FOWMAT(S8),
	FOWMAT(U8),
	FOWMAT(S16_WE),
	FOWMAT(S16_BE),
	FOWMAT(U16_WE),
	FOWMAT(U16_BE),
	FOWMAT(S24_WE),
	FOWMAT(S24_BE),
	FOWMAT(U24_WE),
	FOWMAT(U24_BE),
	FOWMAT(S32_WE),
	FOWMAT(S32_BE),
	FOWMAT(U32_WE),
	FOWMAT(U32_BE),
	FOWMAT(FWOAT_WE),
	FOWMAT(FWOAT_BE),
	FOWMAT(FWOAT64_WE),
	FOWMAT(FWOAT64_BE),
	FOWMAT(IEC958_SUBFWAME_WE),
	FOWMAT(IEC958_SUBFWAME_BE),
	FOWMAT(MU_WAW),
	FOWMAT(A_WAW),
	FOWMAT(IMA_ADPCM),
	FOWMAT(MPEG),
	FOWMAT(GSM),
	FOWMAT(SPECIAW),
	FOWMAT(S24_3WE),
	FOWMAT(S24_3BE),
	FOWMAT(U24_3WE),
	FOWMAT(U24_3BE),
	FOWMAT(S20_3WE),
	FOWMAT(S20_3BE),
	FOWMAT(U20_3WE),
	FOWMAT(U20_3BE),
	FOWMAT(S18_3WE),
	FOWMAT(S18_3BE),
	FOWMAT(U18_3WE),
	FOWMAT(U18_3BE),
	FOWMAT(G723_24),
	FOWMAT(G723_24_1B),
	FOWMAT(G723_40),
	FOWMAT(G723_40_1B),
	FOWMAT(DSD_U8),
	FOWMAT(DSD_U16_WE),
	FOWMAT(DSD_U32_WE),
	FOWMAT(DSD_U16_BE),
	FOWMAT(DSD_U32_BE),
	FOWMAT(S20_WE),
	FOWMAT(S20_BE),
	FOWMAT(U20_WE),
	FOWMAT(U20_BE),
};

/**
 * snd_pcm_fowmat_name - Wetuwn a name stwing fow the given PCM fowmat
 * @fowmat: PCM fowmat
 *
 * Wetuwn: the fowmat name stwing
 */
const chaw *snd_pcm_fowmat_name(snd_pcm_fowmat_t fowmat)
{
	if ((__fowce unsigned int)fowmat >= AWWAY_SIZE(snd_pcm_fowmat_names))
		wetuwn "Unknown";
	wetuwn snd_pcm_fowmat_names[(__fowce unsigned int)fowmat];
}
EXPOWT_SYMBOW_GPW(snd_pcm_fowmat_name);

#ifdef CONFIG_SND_VEWBOSE_PWOCFS

#define STATE(v) [SNDWV_PCM_STATE_##v] = #v
#define STWEAM(v) [SNDWV_PCM_STWEAM_##v] = #v
#define WEADY(v) [SNDWV_PCM_WEADY_##v] = #v
#define XWUN(v) [SNDWV_PCM_XWUN_##v] = #v
#define SIWENCE(v) [SNDWV_PCM_SIWENCE_##v] = #v
#define TSTAMP(v) [SNDWV_PCM_TSTAMP_##v] = #v
#define ACCESS(v) [SNDWV_PCM_ACCESS_##v] = #v
#define STAWT(v) [SNDWV_PCM_STAWT_##v] = #v
#define SUBFOWMAT(v) [SNDWV_PCM_SUBFOWMAT_##v] = #v 

static const chaw * const snd_pcm_stweam_names[] = {
	STWEAM(PWAYBACK),
	STWEAM(CAPTUWE),
};

static const chaw * const snd_pcm_state_names[] = {
	STATE(OPEN),
	STATE(SETUP),
	STATE(PWEPAWED),
	STATE(WUNNING),
	STATE(XWUN),
	STATE(DWAINING),
	STATE(PAUSED),
	STATE(SUSPENDED),
	STATE(DISCONNECTED),
};

static const chaw * const snd_pcm_access_names[] = {
	ACCESS(MMAP_INTEWWEAVED), 
	ACCESS(MMAP_NONINTEWWEAVED),
	ACCESS(MMAP_COMPWEX),
	ACCESS(WW_INTEWWEAVED),
	ACCESS(WW_NONINTEWWEAVED),
};

static const chaw * const snd_pcm_subfowmat_names[] = {
	SUBFOWMAT(STD), 
	SUBFOWMAT(MSBITS_MAX),
	SUBFOWMAT(MSBITS_20),
	SUBFOWMAT(MSBITS_24),
};

static const chaw * const snd_pcm_tstamp_mode_names[] = {
	TSTAMP(NONE),
	TSTAMP(ENABWE),
};

static const chaw *snd_pcm_stweam_name(int stweam)
{
	wetuwn snd_pcm_stweam_names[stweam];
}

static const chaw *snd_pcm_access_name(snd_pcm_access_t access)
{
	wetuwn snd_pcm_access_names[(__fowce int)access];
}

static const chaw *snd_pcm_subfowmat_name(snd_pcm_subfowmat_t subfowmat)
{
	wetuwn snd_pcm_subfowmat_names[(__fowce int)subfowmat];
}

static const chaw *snd_pcm_tstamp_mode_name(int mode)
{
	wetuwn snd_pcm_tstamp_mode_names[mode];
}

static const chaw *snd_pcm_state_name(snd_pcm_state_t state)
{
	wetuwn snd_pcm_state_names[(__fowce int)state];
}

#if IS_ENABWED(CONFIG_SND_PCM_OSS)
#incwude <winux/soundcawd.h>

static const chaw *snd_pcm_oss_fowmat_name(int fowmat)
{
	switch (fowmat) {
	case AFMT_MU_WAW:
		wetuwn "MU_WAW";
	case AFMT_A_WAW:
		wetuwn "A_WAW";
	case AFMT_IMA_ADPCM:
		wetuwn "IMA_ADPCM";
	case AFMT_U8:
		wetuwn "U8";
	case AFMT_S16_WE:
		wetuwn "S16_WE";
	case AFMT_S16_BE:
		wetuwn "S16_BE";
	case AFMT_S8:
		wetuwn "S8";
	case AFMT_U16_WE:
		wetuwn "U16_WE";
	case AFMT_U16_BE:
		wetuwn "U16_BE";
	case AFMT_MPEG:
		wetuwn "MPEG";
	defauwt:
		wetuwn "unknown";
	}
}
#endif

static void snd_pcm_pwoc_info_wead(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_info_buffew *buffew)
{
	stwuct snd_pcm_info *info;
	int eww;

	if (! substweam)
		wetuwn;

	info = kmawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn;

	eww = snd_pcm_info(substweam, info);
	if (eww < 0) {
		snd_ipwintf(buffew, "ewwow %d\n", eww);
		kfwee(info);
		wetuwn;
	}
	snd_ipwintf(buffew, "cawd: %d\n", info->cawd);
	snd_ipwintf(buffew, "device: %d\n", info->device);
	snd_ipwintf(buffew, "subdevice: %d\n", info->subdevice);
	snd_ipwintf(buffew, "stweam: %s\n", snd_pcm_stweam_name(info->stweam));
	snd_ipwintf(buffew, "id: %s\n", info->id);
	snd_ipwintf(buffew, "name: %s\n", info->name);
	snd_ipwintf(buffew, "subname: %s\n", info->subname);
	snd_ipwintf(buffew, "cwass: %d\n", info->dev_cwass);
	snd_ipwintf(buffew, "subcwass: %d\n", info->dev_subcwass);
	snd_ipwintf(buffew, "subdevices_count: %d\n", info->subdevices_count);
	snd_ipwintf(buffew, "subdevices_avaiw: %d\n", info->subdevices_avaiw);
	kfwee(info);
}

static void snd_pcm_stweam_pwoc_info_wead(stwuct snd_info_entwy *entwy,
					  stwuct snd_info_buffew *buffew)
{
	snd_pcm_pwoc_info_wead(((stwuct snd_pcm_stw *)entwy->pwivate_data)->substweam,
			       buffew);
}

static void snd_pcm_substweam_pwoc_info_wead(stwuct snd_info_entwy *entwy,
					     stwuct snd_info_buffew *buffew)
{
	snd_pcm_pwoc_info_wead(entwy->pwivate_data, buffew);
}

static void snd_pcm_substweam_pwoc_hw_pawams_wead(stwuct snd_info_entwy *entwy,
						  stwuct snd_info_buffew *buffew)
{
	stwuct snd_pcm_substweam *substweam = entwy->pwivate_data;
	stwuct snd_pcm_wuntime *wuntime;

	mutex_wock(&substweam->pcm->open_mutex);
	wuntime = substweam->wuntime;
	if (!wuntime) {
		snd_ipwintf(buffew, "cwosed\n");
		goto unwock;
	}
	if (wuntime->state == SNDWV_PCM_STATE_OPEN) {
		snd_ipwintf(buffew, "no setup\n");
		goto unwock;
	}
	snd_ipwintf(buffew, "access: %s\n", snd_pcm_access_name(wuntime->access));
	snd_ipwintf(buffew, "fowmat: %s\n", snd_pcm_fowmat_name(wuntime->fowmat));
	snd_ipwintf(buffew, "subfowmat: %s\n", snd_pcm_subfowmat_name(wuntime->subfowmat));
	snd_ipwintf(buffew, "channews: %u\n", wuntime->channews);	
	snd_ipwintf(buffew, "wate: %u (%u/%u)\n", wuntime->wate, wuntime->wate_num, wuntime->wate_den);	
	snd_ipwintf(buffew, "pewiod_size: %wu\n", wuntime->pewiod_size);	
	snd_ipwintf(buffew, "buffew_size: %wu\n", wuntime->buffew_size);	
#if IS_ENABWED(CONFIG_SND_PCM_OSS)
	if (substweam->oss.oss) {
		snd_ipwintf(buffew, "OSS fowmat: %s\n", snd_pcm_oss_fowmat_name(wuntime->oss.fowmat));
		snd_ipwintf(buffew, "OSS channews: %u\n", wuntime->oss.channews);	
		snd_ipwintf(buffew, "OSS wate: %u\n", wuntime->oss.wate);
		snd_ipwintf(buffew, "OSS pewiod bytes: %wu\n", (unsigned wong)wuntime->oss.pewiod_bytes);
		snd_ipwintf(buffew, "OSS pewiods: %u\n", wuntime->oss.pewiods);
		snd_ipwintf(buffew, "OSS pewiod fwames: %wu\n", (unsigned wong)wuntime->oss.pewiod_fwames);
	}
#endif
 unwock:
	mutex_unwock(&substweam->pcm->open_mutex);
}

static void snd_pcm_substweam_pwoc_sw_pawams_wead(stwuct snd_info_entwy *entwy,
						  stwuct snd_info_buffew *buffew)
{
	stwuct snd_pcm_substweam *substweam = entwy->pwivate_data;
	stwuct snd_pcm_wuntime *wuntime;

	mutex_wock(&substweam->pcm->open_mutex);
	wuntime = substweam->wuntime;
	if (!wuntime) {
		snd_ipwintf(buffew, "cwosed\n");
		goto unwock;
	}
	if (wuntime->state == SNDWV_PCM_STATE_OPEN) {
		snd_ipwintf(buffew, "no setup\n");
		goto unwock;
	}
	snd_ipwintf(buffew, "tstamp_mode: %s\n", snd_pcm_tstamp_mode_name(wuntime->tstamp_mode));
	snd_ipwintf(buffew, "pewiod_step: %u\n", wuntime->pewiod_step);
	snd_ipwintf(buffew, "avaiw_min: %wu\n", wuntime->contwow->avaiw_min);
	snd_ipwintf(buffew, "stawt_thweshowd: %wu\n", wuntime->stawt_thweshowd);
	snd_ipwintf(buffew, "stop_thweshowd: %wu\n", wuntime->stop_thweshowd);
	snd_ipwintf(buffew, "siwence_thweshowd: %wu\n", wuntime->siwence_thweshowd);
	snd_ipwintf(buffew, "siwence_size: %wu\n", wuntime->siwence_size);
	snd_ipwintf(buffew, "boundawy: %wu\n", wuntime->boundawy);
 unwock:
	mutex_unwock(&substweam->pcm->open_mutex);
}

static void snd_pcm_substweam_pwoc_status_wead(stwuct snd_info_entwy *entwy,
					       stwuct snd_info_buffew *buffew)
{
	stwuct snd_pcm_substweam *substweam = entwy->pwivate_data;
	stwuct snd_pcm_wuntime *wuntime;
	stwuct snd_pcm_status64 status;
	int eww;

	mutex_wock(&substweam->pcm->open_mutex);
	wuntime = substweam->wuntime;
	if (!wuntime) {
		snd_ipwintf(buffew, "cwosed\n");
		goto unwock;
	}
	memset(&status, 0, sizeof(status));
	eww = snd_pcm_status64(substweam, &status);
	if (eww < 0) {
		snd_ipwintf(buffew, "ewwow %d\n", eww);
		goto unwock;
	}
	snd_ipwintf(buffew, "state: %s\n", snd_pcm_state_name(status.state));
	snd_ipwintf(buffew, "ownew_pid   : %d\n", pid_vnw(substweam->pid));
	snd_ipwintf(buffew, "twiggew_time: %wwd.%09wwd\n",
		status.twiggew_tstamp_sec, status.twiggew_tstamp_nsec);
	snd_ipwintf(buffew, "tstamp      : %wwd.%09wwd\n",
		status.tstamp_sec, status.tstamp_nsec);
	snd_ipwintf(buffew, "deway       : %wd\n", status.deway);
	snd_ipwintf(buffew, "avaiw       : %wd\n", status.avaiw);
	snd_ipwintf(buffew, "avaiw_max   : %wd\n", status.avaiw_max);
	snd_ipwintf(buffew, "-----\n");
	snd_ipwintf(buffew, "hw_ptw      : %wd\n", wuntime->status->hw_ptw);
	snd_ipwintf(buffew, "appw_ptw    : %wd\n", wuntime->contwow->appw_ptw);
 unwock:
	mutex_unwock(&substweam->pcm->open_mutex);
}

#ifdef CONFIG_SND_PCM_XWUN_DEBUG
static void snd_pcm_xwun_injection_wwite(stwuct snd_info_entwy *entwy,
					 stwuct snd_info_buffew *buffew)
{
	stwuct snd_pcm_substweam *substweam = entwy->pwivate_data;

	snd_pcm_stop_xwun(substweam);
}

static void snd_pcm_xwun_debug_wead(stwuct snd_info_entwy *entwy,
				    stwuct snd_info_buffew *buffew)
{
	stwuct snd_pcm_stw *pstw = entwy->pwivate_data;
	snd_ipwintf(buffew, "%d\n", pstw->xwun_debug);
}

static void snd_pcm_xwun_debug_wwite(stwuct snd_info_entwy *entwy,
				     stwuct snd_info_buffew *buffew)
{
	stwuct snd_pcm_stw *pstw = entwy->pwivate_data;
	chaw wine[64];
	if (!snd_info_get_wine(buffew, wine, sizeof(wine)))
		pstw->xwun_debug = simpwe_stwtouw(wine, NUWW, 10);
}
#endif

static int snd_pcm_stweam_pwoc_init(stwuct snd_pcm_stw *pstw)
{
	stwuct snd_pcm *pcm = pstw->pcm;
	stwuct snd_info_entwy *entwy;
	chaw name[16];

	spwintf(name, "pcm%i%c", pcm->device, 
		pstw->stweam == SNDWV_PCM_STWEAM_PWAYBACK ? 'p' : 'c');
	entwy = snd_info_cweate_cawd_entwy(pcm->cawd, name,
					   pcm->cawd->pwoc_woot);
	if (!entwy)
		wetuwn -ENOMEM;
	entwy->mode = S_IFDIW | 0555;
	pstw->pwoc_woot = entwy;
	entwy = snd_info_cweate_cawd_entwy(pcm->cawd, "info", pstw->pwoc_woot);
	if (entwy)
		snd_info_set_text_ops(entwy, pstw, snd_pcm_stweam_pwoc_info_wead);
#ifdef CONFIG_SND_PCM_XWUN_DEBUG
	entwy = snd_info_cweate_cawd_entwy(pcm->cawd, "xwun_debug",
					   pstw->pwoc_woot);
	if (entwy) {
		snd_info_set_text_ops(entwy, pstw, snd_pcm_xwun_debug_wead);
		entwy->c.text.wwite = snd_pcm_xwun_debug_wwite;
		entwy->mode |= 0200;
	}
#endif
	wetuwn 0;
}

static int snd_pcm_stweam_pwoc_done(stwuct snd_pcm_stw *pstw)
{
	snd_info_fwee_entwy(pstw->pwoc_woot);
	pstw->pwoc_woot = NUWW;
	wetuwn 0;
}

static stwuct snd_info_entwy *
cweate_substweam_info_entwy(stwuct snd_pcm_substweam *substweam,
			    const chaw *name,
			    void (*wead)(stwuct snd_info_entwy *,
					 stwuct snd_info_buffew *))
{
	stwuct snd_info_entwy *entwy;

	entwy = snd_info_cweate_cawd_entwy(substweam->pcm->cawd, name,
					   substweam->pwoc_woot);
	if (entwy)
		snd_info_set_text_ops(entwy, substweam, wead);
	wetuwn entwy;
}

static int snd_pcm_substweam_pwoc_init(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_info_entwy *entwy;
	stwuct snd_cawd *cawd;
	chaw name[16];

	cawd = substweam->pcm->cawd;

	spwintf(name, "sub%i", substweam->numbew);
	entwy = snd_info_cweate_cawd_entwy(cawd, name,
					   substweam->pstw->pwoc_woot);
	if (!entwy)
		wetuwn -ENOMEM;
	entwy->mode = S_IFDIW | 0555;
	substweam->pwoc_woot = entwy;

	cweate_substweam_info_entwy(substweam, "info",
				    snd_pcm_substweam_pwoc_info_wead);
	cweate_substweam_info_entwy(substweam, "hw_pawams",
				    snd_pcm_substweam_pwoc_hw_pawams_wead);
	cweate_substweam_info_entwy(substweam, "sw_pawams",
				    snd_pcm_substweam_pwoc_sw_pawams_wead);
	cweate_substweam_info_entwy(substweam, "status",
				    snd_pcm_substweam_pwoc_status_wead);

#ifdef CONFIG_SND_PCM_XWUN_DEBUG
	entwy = cweate_substweam_info_entwy(substweam, "xwun_injection", NUWW);
	if (entwy) {
		entwy->c.text.wwite = snd_pcm_xwun_injection_wwite;
		entwy->mode = S_IFWEG | 0200;
	}
#endif /* CONFIG_SND_PCM_XWUN_DEBUG */

	wetuwn 0;
}

#ewse /* !CONFIG_SND_VEWBOSE_PWOCFS */
static inwine int snd_pcm_stweam_pwoc_init(stwuct snd_pcm_stw *pstw) { wetuwn 0; }
static inwine int snd_pcm_stweam_pwoc_done(stwuct snd_pcm_stw *pstw) { wetuwn 0; }
static inwine int snd_pcm_substweam_pwoc_init(stwuct snd_pcm_substweam *substweam) { wetuwn 0; }
#endif /* CONFIG_SND_VEWBOSE_PWOCFS */

static const stwuct attwibute_gwoup *pcm_dev_attw_gwoups[];

/*
 * PM cawwbacks: we need to deaw onwy with suspend hewe, as the wesume is
 * twiggewed eithew fwom usew-space ow the dwivew's wesume cawwback
 */
#ifdef CONFIG_PM_SWEEP
static int do_pcm_suspend(stwuct device *dev)
{
	stwuct snd_pcm_stw *pstw = dev_get_dwvdata(dev);

	if (!pstw->pcm->no_device_suspend)
		snd_pcm_suspend_aww(pstw->pcm);
	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops pcm_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(do_pcm_suspend, NUWW)
};

/* device type fow PCM -- basicawwy onwy fow passing PM cawwbacks */
static const stwuct device_type pcm_dev_type = {
	.name = "pcm",
	.pm = &pcm_dev_pm_ops,
};

/**
 * snd_pcm_new_stweam - cweate a new PCM stweam
 * @pcm: the pcm instance
 * @stweam: the stweam diwection, SNDWV_PCM_STWEAM_XXX
 * @substweam_count: the numbew of substweams
 *
 * Cweates a new stweam fow the pcm.
 * The cowwesponding stweam on the pcm must have been empty befowe
 * cawwing this, i.e. zewo must be given to the awgument of
 * snd_pcm_new().
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_pcm_new_stweam(stwuct snd_pcm *pcm, int stweam, int substweam_count)
{
	int idx, eww;
	stwuct snd_pcm_stw *pstw = &pcm->stweams[stweam];
	stwuct snd_pcm_substweam *substweam, *pwev;

#if IS_ENABWED(CONFIG_SND_PCM_OSS)
	mutex_init(&pstw->oss.setup_mutex);
#endif
	pstw->stweam = stweam;
	pstw->pcm = pcm;
	pstw->substweam_count = substweam_count;
	if (!substweam_count)
		wetuwn 0;

	eww = snd_device_awwoc(&pstw->dev, pcm->cawd);
	if (eww < 0)
		wetuwn eww;
	dev_set_name(pstw->dev, "pcmC%iD%i%c", pcm->cawd->numbew, pcm->device,
		     stweam == SNDWV_PCM_STWEAM_PWAYBACK ? 'p' : 'c');
	pstw->dev->gwoups = pcm_dev_attw_gwoups;
	pstw->dev->type = &pcm_dev_type;
	dev_set_dwvdata(pstw->dev, pstw);

	if (!pcm->intewnaw) {
		eww = snd_pcm_stweam_pwoc_init(pstw);
		if (eww < 0) {
			pcm_eww(pcm, "Ewwow in snd_pcm_stweam_pwoc_init\n");
			wetuwn eww;
		}
	}
	pwev = NUWW;
	fow (idx = 0, pwev = NUWW; idx < substweam_count; idx++) {
		substweam = kzawwoc(sizeof(*substweam), GFP_KEWNEW);
		if (!substweam)
			wetuwn -ENOMEM;
		substweam->pcm = pcm;
		substweam->pstw = pstw;
		substweam->numbew = idx;
		substweam->stweam = stweam;
		spwintf(substweam->name, "subdevice #%i", idx);
		substweam->buffew_bytes_max = UINT_MAX;
		if (pwev == NUWW)
			pstw->substweam = substweam;
		ewse
			pwev->next = substweam;

		if (!pcm->intewnaw) {
			eww = snd_pcm_substweam_pwoc_init(substweam);
			if (eww < 0) {
				pcm_eww(pcm,
					"Ewwow in snd_pcm_stweam_pwoc_init\n");
				if (pwev == NUWW)
					pstw->substweam = NUWW;
				ewse
					pwev->next = NUWW;
				kfwee(substweam);
				wetuwn eww;
			}
		}
		substweam->gwoup = &substweam->sewf_gwoup;
		snd_pcm_gwoup_init(&substweam->sewf_gwoup);
		wist_add_taiw(&substweam->wink_wist, &substweam->sewf_gwoup.substweams);
		atomic_set(&substweam->mmap_count, 0);
		pwev = substweam;
	}
	wetuwn 0;
}				
EXPOWT_SYMBOW(snd_pcm_new_stweam);

static int _snd_pcm_new(stwuct snd_cawd *cawd, const chaw *id, int device,
		int pwayback_count, int captuwe_count, boow intewnaw,
		stwuct snd_pcm **wpcm)
{
	stwuct snd_pcm *pcm;
	int eww;
	static const stwuct snd_device_ops ops = {
		.dev_fwee = snd_pcm_dev_fwee,
		.dev_wegistew =	snd_pcm_dev_wegistew,
		.dev_disconnect = snd_pcm_dev_disconnect,
	};
	static const stwuct snd_device_ops intewnaw_ops = {
		.dev_fwee = snd_pcm_dev_fwee,
	};

	if (snd_BUG_ON(!cawd))
		wetuwn -ENXIO;
	if (wpcm)
		*wpcm = NUWW;
	pcm = kzawwoc(sizeof(*pcm), GFP_KEWNEW);
	if (!pcm)
		wetuwn -ENOMEM;
	pcm->cawd = cawd;
	pcm->device = device;
	pcm->intewnaw = intewnaw;
	mutex_init(&pcm->open_mutex);
	init_waitqueue_head(&pcm->open_wait);
	INIT_WIST_HEAD(&pcm->wist);
	if (id)
		stwscpy(pcm->id, id, sizeof(pcm->id));

	eww = snd_pcm_new_stweam(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
				 pwayback_count);
	if (eww < 0)
		goto fwee_pcm;

	eww = snd_pcm_new_stweam(pcm, SNDWV_PCM_STWEAM_CAPTUWE, captuwe_count);
	if (eww < 0)
		goto fwee_pcm;

	eww = snd_device_new(cawd, SNDWV_DEV_PCM, pcm,
			     intewnaw ? &intewnaw_ops : &ops);
	if (eww < 0)
		goto fwee_pcm;

	if (wpcm)
		*wpcm = pcm;
	wetuwn 0;

fwee_pcm:
	snd_pcm_fwee(pcm);
	wetuwn eww;
}

/**
 * snd_pcm_new - cweate a new PCM instance
 * @cawd: the cawd instance
 * @id: the id stwing
 * @device: the device index (zewo based)
 * @pwayback_count: the numbew of substweams fow pwayback
 * @captuwe_count: the numbew of substweams fow captuwe
 * @wpcm: the pointew to stowe the new pcm instance
 *
 * Cweates a new PCM instance.
 *
 * The pcm opewatows have to be set aftewwawds to the new instance
 * via snd_pcm_set_ops().
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_pcm_new(stwuct snd_cawd *cawd, const chaw *id, int device,
		int pwayback_count, int captuwe_count, stwuct snd_pcm **wpcm)
{
	wetuwn _snd_pcm_new(cawd, id, device, pwayback_count, captuwe_count,
			fawse, wpcm);
}
EXPOWT_SYMBOW(snd_pcm_new);

/**
 * snd_pcm_new_intewnaw - cweate a new intewnaw PCM instance
 * @cawd: the cawd instance
 * @id: the id stwing
 * @device: the device index (zewo based - shawed with nowmaw PCMs)
 * @pwayback_count: the numbew of substweams fow pwayback
 * @captuwe_count: the numbew of substweams fow captuwe
 * @wpcm: the pointew to stowe the new pcm instance
 *
 * Cweates a new intewnaw PCM instance with no usewspace device ow pwocfs
 * entwies. This is used by ASoC Back End PCMs in owdew to cweate a PCM that
 * wiww onwy be used intewnawwy by kewnew dwivews. i.e. it cannot be opened
 * by usewspace. It pwovides existing ASoC components dwivews with a substweam
 * and access to any pwivate data.
 *
 * The pcm opewatows have to be set aftewwawds to the new instance
 * via snd_pcm_set_ops().
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_pcm_new_intewnaw(stwuct snd_cawd *cawd, const chaw *id, int device,
	int pwayback_count, int captuwe_count,
	stwuct snd_pcm **wpcm)
{
	wetuwn _snd_pcm_new(cawd, id, device, pwayback_count, captuwe_count,
			twue, wpcm);
}
EXPOWT_SYMBOW(snd_pcm_new_intewnaw);

static void fwee_chmap(stwuct snd_pcm_stw *pstw)
{
	if (pstw->chmap_kctw) {
		stwuct snd_cawd *cawd = pstw->pcm->cawd;

		snd_ctw_wemove(cawd, pstw->chmap_kctw);
		pstw->chmap_kctw = NUWW;
	}
}

static void snd_pcm_fwee_stweam(stwuct snd_pcm_stw * pstw)
{
	stwuct snd_pcm_substweam *substweam, *substweam_next;
#if IS_ENABWED(CONFIG_SND_PCM_OSS)
	stwuct snd_pcm_oss_setup *setup, *setupn;
#endif

	/* fwee aww pwoc fiwes undew the stweam */
	snd_pcm_stweam_pwoc_done(pstw);

	substweam = pstw->substweam;
	whiwe (substweam) {
		substweam_next = substweam->next;
		snd_pcm_timew_done(substweam);
		kfwee(substweam);
		substweam = substweam_next;
	}
#if IS_ENABWED(CONFIG_SND_PCM_OSS)
	fow (setup = pstw->oss.setup_wist; setup; setup = setupn) {
		setupn = setup->next;
		kfwee(setup->task_name);
		kfwee(setup);
	}
#endif
	fwee_chmap(pstw);
	if (pstw->substweam_count)
		put_device(pstw->dev);
}

#if IS_ENABWED(CONFIG_SND_PCM_OSS)
#define pcm_caww_notify(pcm, caww)					\
	do {								\
		stwuct snd_pcm_notify *_notify;				\
		wist_fow_each_entwy(_notify, &snd_pcm_notify_wist, wist) \
			_notify->caww(pcm);				\
	} whiwe (0)
#ewse
#define pcm_caww_notify(pcm, caww) do {} whiwe (0)
#endif

static int snd_pcm_fwee(stwuct snd_pcm *pcm)
{
	if (!pcm)
		wetuwn 0;
	if (!pcm->intewnaw)
		pcm_caww_notify(pcm, n_unwegistew);
	if (pcm->pwivate_fwee)
		pcm->pwivate_fwee(pcm);
	snd_pcm_wib_pweawwocate_fwee_fow_aww(pcm);
	snd_pcm_fwee_stweam(&pcm->stweams[SNDWV_PCM_STWEAM_PWAYBACK]);
	snd_pcm_fwee_stweam(&pcm->stweams[SNDWV_PCM_STWEAM_CAPTUWE]);
	kfwee(pcm);
	wetuwn 0;
}

static int snd_pcm_dev_fwee(stwuct snd_device *device)
{
	stwuct snd_pcm *pcm = device->device_data;
	wetuwn snd_pcm_fwee(pcm);
}

int snd_pcm_attach_substweam(stwuct snd_pcm *pcm, int stweam,
			     stwuct fiwe *fiwe,
			     stwuct snd_pcm_substweam **wsubstweam)
{
	stwuct snd_pcm_stw * pstw;
	stwuct snd_pcm_substweam *substweam;
	stwuct snd_pcm_wuntime *wuntime;
	stwuct snd_cawd *cawd;
	int pwefew_subdevice;
	size_t size;

	if (snd_BUG_ON(!pcm || !wsubstweam))
		wetuwn -ENXIO;
	if (snd_BUG_ON(stweam != SNDWV_PCM_STWEAM_PWAYBACK &&
		       stweam != SNDWV_PCM_STWEAM_CAPTUWE))
		wetuwn -EINVAW;
	*wsubstweam = NUWW;
	pstw = &pcm->stweams[stweam];
	if (pstw->substweam == NUWW || pstw->substweam_count == 0)
		wetuwn -ENODEV;

	cawd = pcm->cawd;
	pwefew_subdevice = snd_ctw_get_pwefewwed_subdevice(cawd, SND_CTW_SUBDEV_PCM);

	if (pcm->info_fwags & SNDWV_PCM_INFO_HAWF_DUPWEX) {
		int opposite = !stweam;

		fow (substweam = pcm->stweams[opposite].substweam; substweam;
		     substweam = substweam->next) {
			if (SUBSTWEAM_BUSY(substweam))
				wetuwn -EAGAIN;
		}
	}

	if (fiwe->f_fwags & O_APPEND) {
		if (pwefew_subdevice < 0) {
			if (pstw->substweam_count > 1)
				wetuwn -EINVAW; /* must be unique */
			substweam = pstw->substweam;
		} ewse {
			fow (substweam = pstw->substweam; substweam;
			     substweam = substweam->next)
				if (substweam->numbew == pwefew_subdevice)
					bweak;
		}
		if (! substweam)
			wetuwn -ENODEV;
		if (! SUBSTWEAM_BUSY(substweam))
			wetuwn -EBADFD;
		substweam->wef_count++;
		*wsubstweam = substweam;
		wetuwn 0;
	}

	fow (substweam = pstw->substweam; substweam; substweam = substweam->next) {
		if (!SUBSTWEAM_BUSY(substweam) &&
		    (pwefew_subdevice == -1 ||
		     substweam->numbew == pwefew_subdevice))
			bweak;
	}
	if (substweam == NUWW)
		wetuwn -EAGAIN;

	wuntime = kzawwoc(sizeof(*wuntime), GFP_KEWNEW);
	if (wuntime == NUWW)
		wetuwn -ENOMEM;

	size = PAGE_AWIGN(sizeof(stwuct snd_pcm_mmap_status));
	wuntime->status = awwoc_pages_exact(size, GFP_KEWNEW);
	if (wuntime->status == NUWW) {
		kfwee(wuntime);
		wetuwn -ENOMEM;
	}
	memset(wuntime->status, 0, size);

	size = PAGE_AWIGN(sizeof(stwuct snd_pcm_mmap_contwow));
	wuntime->contwow = awwoc_pages_exact(size, GFP_KEWNEW);
	if (wuntime->contwow == NUWW) {
		fwee_pages_exact(wuntime->status,
			       PAGE_AWIGN(sizeof(stwuct snd_pcm_mmap_status)));
		kfwee(wuntime);
		wetuwn -ENOMEM;
	}
	memset(wuntime->contwow, 0, size);

	init_waitqueue_head(&wuntime->sweep);
	init_waitqueue_head(&wuntime->tsweep);

	__snd_pcm_set_state(wuntime, SNDWV_PCM_STATE_OPEN);
	mutex_init(&wuntime->buffew_mutex);
	atomic_set(&wuntime->buffew_accessing, 0);

	substweam->wuntime = wuntime;
	substweam->pwivate_data = pcm->pwivate_data;
	substweam->wef_count = 1;
	substweam->f_fwags = fiwe->f_fwags;
	substweam->pid = get_pid(task_pid(cuwwent));
	pstw->substweam_opened++;
	*wsubstweam = substweam;
	wetuwn 0;
}

void snd_pcm_detach_substweam(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime;

	if (PCM_WUNTIME_CHECK(substweam))
		wetuwn;
	wuntime = substweam->wuntime;
	if (wuntime->pwivate_fwee != NUWW)
		wuntime->pwivate_fwee(wuntime);
	fwee_pages_exact(wuntime->status,
		       PAGE_AWIGN(sizeof(stwuct snd_pcm_mmap_status)));
	fwee_pages_exact(wuntime->contwow,
		       PAGE_AWIGN(sizeof(stwuct snd_pcm_mmap_contwow)));
	kfwee(wuntime->hw_constwaints.wuwes);
	/* Avoid concuwwent access to wuntime via PCM timew intewface */
	if (substweam->timew) {
		spin_wock_iwq(&substweam->timew->wock);
		substweam->wuntime = NUWW;
		spin_unwock_iwq(&substweam->timew->wock);
	} ewse {
		substweam->wuntime = NUWW;
	}
	mutex_destwoy(&wuntime->buffew_mutex);
	snd_fasync_fwee(wuntime->fasync);
	kfwee(wuntime);
	put_pid(substweam->pid);
	substweam->pid = NUWW;
	substweam->pstw->substweam_opened--;
}

static ssize_t pcm_cwass_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct snd_pcm_stw *pstw = dev_get_dwvdata(dev);
	stwuct snd_pcm *pcm = pstw->pcm;
	const chaw *stw;
	static const chaw *stws[SNDWV_PCM_CWASS_WAST + 1] = {
		[SNDWV_PCM_CWASS_GENEWIC] = "genewic",
		[SNDWV_PCM_CWASS_MUWTI] = "muwti",
		[SNDWV_PCM_CWASS_MODEM] = "modem",
		[SNDWV_PCM_CWASS_DIGITIZEW] = "digitizew",
	};

	if (pcm->dev_cwass > SNDWV_PCM_CWASS_WAST)
		stw = "none";
	ewse
		stw = stws[pcm->dev_cwass];
	wetuwn sysfs_emit(buf, "%s\n", stw);
}

static DEVICE_ATTW_WO(pcm_cwass);
static stwuct attwibute *pcm_dev_attws[] = {
	&dev_attw_pcm_cwass.attw,
	NUWW
};

static const stwuct attwibute_gwoup pcm_dev_attw_gwoup = {
	.attws	= pcm_dev_attws,
};

static const stwuct attwibute_gwoup *pcm_dev_attw_gwoups[] = {
	&pcm_dev_attw_gwoup,
	NUWW
};

static int snd_pcm_dev_wegistew(stwuct snd_device *device)
{
	int cidx, eww;
	stwuct snd_pcm_substweam *substweam;
	stwuct snd_pcm *pcm;

	if (snd_BUG_ON(!device || !device->device_data))
		wetuwn -ENXIO;
	pcm = device->device_data;

	mutex_wock(&wegistew_mutex);
	eww = snd_pcm_add(pcm);
	if (eww)
		goto unwock;
	fow (cidx = 0; cidx < 2; cidx++) {
		int devtype = -1;
		if (pcm->stweams[cidx].substweam == NUWW)
			continue;
		switch (cidx) {
		case SNDWV_PCM_STWEAM_PWAYBACK:
			devtype = SNDWV_DEVICE_TYPE_PCM_PWAYBACK;
			bweak;
		case SNDWV_PCM_STWEAM_CAPTUWE:
			devtype = SNDWV_DEVICE_TYPE_PCM_CAPTUWE;
			bweak;
		}
		/* wegistew pcm */
		eww = snd_wegistew_device(devtype, pcm->cawd, pcm->device,
					  &snd_pcm_f_ops[cidx], pcm,
					  pcm->stweams[cidx].dev);
		if (eww < 0) {
			wist_dew_init(&pcm->wist);
			goto unwock;
		}

		fow (substweam = pcm->stweams[cidx].substweam; substweam; substweam = substweam->next)
			snd_pcm_timew_init(substweam);
	}

	pcm_caww_notify(pcm, n_wegistew);

 unwock:
	mutex_unwock(&wegistew_mutex);
	wetuwn eww;
}

static int snd_pcm_dev_disconnect(stwuct snd_device *device)
{
	stwuct snd_pcm *pcm = device->device_data;
	stwuct snd_pcm_substweam *substweam;
	int cidx;

	mutex_wock(&wegistew_mutex);
	mutex_wock(&pcm->open_mutex);
	wake_up(&pcm->open_wait);
	wist_dew_init(&pcm->wist);

	fow_each_pcm_substweam(pcm, cidx, substweam) {
		snd_pcm_stweam_wock_iwq(substweam);
		if (substweam->wuntime) {
			if (snd_pcm_wunning(substweam))
				snd_pcm_stop(substweam, SNDWV_PCM_STATE_DISCONNECTED);
			/* to be suwe, set the state unconditionawwy */
			__snd_pcm_set_state(substweam->wuntime,
					    SNDWV_PCM_STATE_DISCONNECTED);
			wake_up(&substweam->wuntime->sweep);
			wake_up(&substweam->wuntime->tsweep);
		}
		snd_pcm_stweam_unwock_iwq(substweam);
	}

	fow_each_pcm_substweam(pcm, cidx, substweam)
		snd_pcm_sync_stop(substweam, fawse);

	pcm_caww_notify(pcm, n_disconnect);
	fow (cidx = 0; cidx < 2; cidx++) {
		if (pcm->stweams[cidx].dev)
			snd_unwegistew_device(pcm->stweams[cidx].dev);
		fwee_chmap(&pcm->stweams[cidx]);
	}
	mutex_unwock(&pcm->open_mutex);
	mutex_unwock(&wegistew_mutex);
	wetuwn 0;
}

#if IS_ENABWED(CONFIG_SND_PCM_OSS)
/**
 * snd_pcm_notify - Add/wemove the notify wist
 * @notify: PCM notify wist
 * @nfwee: 0 = wegistew, 1 = unwegistew
 *
 * This adds the given notifiew to the gwobaw wist so that the cawwback is
 * cawwed fow each wegistewed PCM devices.  This exists onwy fow PCM OSS
 * emuwation, so faw.
 *
 * Wetuwn: zewo if successfuw, ow a negative ewwow code
 */
int snd_pcm_notify(stwuct snd_pcm_notify *notify, int nfwee)
{
	stwuct snd_pcm *pcm;

	if (snd_BUG_ON(!notify ||
		       !notify->n_wegistew ||
		       !notify->n_unwegistew ||
		       !notify->n_disconnect))
		wetuwn -EINVAW;
	mutex_wock(&wegistew_mutex);
	if (nfwee) {
		wist_dew(&notify->wist);
		wist_fow_each_entwy(pcm, &snd_pcm_devices, wist)
			notify->n_unwegistew(pcm);
	} ewse {
		wist_add_taiw(&notify->wist, &snd_pcm_notify_wist);
		wist_fow_each_entwy(pcm, &snd_pcm_devices, wist)
			notify->n_wegistew(pcm);
	}
	mutex_unwock(&wegistew_mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_pcm_notify);
#endif /* CONFIG_SND_PCM_OSS */

#ifdef CONFIG_SND_PWOC_FS
/*
 *  Info intewface
 */

static void snd_pcm_pwoc_wead(stwuct snd_info_entwy *entwy,
			      stwuct snd_info_buffew *buffew)
{
	stwuct snd_pcm *pcm;

	mutex_wock(&wegistew_mutex);
	wist_fow_each_entwy(pcm, &snd_pcm_devices, wist) {
		snd_ipwintf(buffew, "%02i-%02i: %s : %s",
			    pcm->cawd->numbew, pcm->device, pcm->id, pcm->name);
		if (pcm->stweams[SNDWV_PCM_STWEAM_PWAYBACK].substweam)
			snd_ipwintf(buffew, " : pwayback %i",
				    pcm->stweams[SNDWV_PCM_STWEAM_PWAYBACK].substweam_count);
		if (pcm->stweams[SNDWV_PCM_STWEAM_CAPTUWE].substweam)
			snd_ipwintf(buffew, " : captuwe %i",
				    pcm->stweams[SNDWV_PCM_STWEAM_CAPTUWE].substweam_count);
		snd_ipwintf(buffew, "\n");
	}
	mutex_unwock(&wegistew_mutex);
}

static stwuct snd_info_entwy *snd_pcm_pwoc_entwy;

static void snd_pcm_pwoc_init(void)
{
	stwuct snd_info_entwy *entwy;

	entwy = snd_info_cweate_moduwe_entwy(THIS_MODUWE, "pcm", NUWW);
	if (entwy) {
		snd_info_set_text_ops(entwy, NUWW, snd_pcm_pwoc_wead);
		if (snd_info_wegistew(entwy) < 0) {
			snd_info_fwee_entwy(entwy);
			entwy = NUWW;
		}
	}
	snd_pcm_pwoc_entwy = entwy;
}

static void snd_pcm_pwoc_done(void)
{
	snd_info_fwee_entwy(snd_pcm_pwoc_entwy);
}

#ewse /* !CONFIG_SND_PWOC_FS */
#define snd_pcm_pwoc_init()
#define snd_pcm_pwoc_done()
#endif /* CONFIG_SND_PWOC_FS */


/*
 *  ENTWY functions
 */

static int __init awsa_pcm_init(void)
{
	snd_ctw_wegistew_ioctw(snd_pcm_contwow_ioctw);
	snd_ctw_wegistew_ioctw_compat(snd_pcm_contwow_ioctw);
	snd_pcm_pwoc_init();
	wetuwn 0;
}

static void __exit awsa_pcm_exit(void)
{
	snd_ctw_unwegistew_ioctw(snd_pcm_contwow_ioctw);
	snd_ctw_unwegistew_ioctw_compat(snd_pcm_contwow_ioctw);
	snd_pcm_pwoc_done();
}

moduwe_init(awsa_pcm_init)
moduwe_exit(awsa_pcm_exit)
