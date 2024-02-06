// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Woopback soundcawd
 *
 *  Owiginaw code:
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *
 *  Mowe accuwate positioning and fuww-dupwex suppowt:
 *  Copywight (c) Ahmet İnan <ainan at mathematik.uni-fweibuwg.de>
 *
 *  Majow (awmost compwete) wewwite:
 *  Copywight (c) by Takashi Iwai <tiwai@suse.de>
 *
 *  A next majow update in 2010 (sepawate timews fow pwayback and captuwe):
 *  Copywight (c) Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/init.h>
#incwude <winux/jiffies.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/wait.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/info.h>
#incwude <sound/initvaw.h>
#incwude <sound/timew.h>

MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>");
MODUWE_DESCWIPTION("A woopback soundcawd");
MODUWE_WICENSE("GPW");

#define MAX_PCM_SUBSTWEAMS	8

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = {1, [1 ... (SNDWV_CAWDS - 1)] = 0};
static int pcm_substweams[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 8};
static int pcm_notify[SNDWV_CAWDS];
static chaw *timew_souwce[SNDWV_CAWDS];

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow woopback soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow woopback soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe this woopback soundcawd.");
moduwe_pawam_awway(pcm_substweams, int, NUWW, 0444);
MODUWE_PAWM_DESC(pcm_substweams, "PCM substweams # (1-8) fow woopback dwivew.");
moduwe_pawam_awway(pcm_notify, int, NUWW, 0444);
MODUWE_PAWM_DESC(pcm_notify, "Bweak captuwe when PCM fowmat/wate/channews changes.");
moduwe_pawam_awway(timew_souwce, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(timew_souwce, "Sound cawd name ow numbew and device/subdevice numbew of timew to be used. Empty stwing fow jiffies timew [defauwt].");

#define NO_PITCH 100000

#define CABWE_VAWID_PWAYBACK	BIT(SNDWV_PCM_STWEAM_PWAYBACK)
#define CABWE_VAWID_CAPTUWE	BIT(SNDWV_PCM_STWEAM_CAPTUWE)
#define CABWE_VAWID_BOTH	(CABWE_VAWID_PWAYBACK | CABWE_VAWID_CAPTUWE)

stwuct woopback_cabwe;
stwuct woopback_pcm;

stwuct woopback_ops {
	/* optionaw
	 * caww in woopback->cabwe_wock
	 */
	int (*open)(stwuct woopback_pcm *dpcm);
	/* wequiwed
	 * caww in cabwe->wock
	 */
	int (*stawt)(stwuct woopback_pcm *dpcm);
	/* wequiwed
	 * caww in cabwe->wock
	 */
	int (*stop)(stwuct woopback_pcm *dpcm);
	/* optionaw */
	int (*stop_sync)(stwuct woopback_pcm *dpcm);
	/* optionaw */
	int (*cwose_substweam)(stwuct woopback_pcm *dpcm);
	/* optionaw
	 * caww in woopback->cabwe_wock
	 */
	int (*cwose_cabwe)(stwuct woopback_pcm *dpcm);
	/* optionaw
	 * caww in cabwe->wock
	 */
	unsigned int (*pos_update)(stwuct woopback_cabwe *cabwe);
	/* optionaw */
	void (*dpcm_info)(stwuct woopback_pcm *dpcm,
			  stwuct snd_info_buffew *buffew);
};

stwuct woopback_cabwe {
	spinwock_t wock;
	stwuct woopback_pcm *stweams[2];
	stwuct snd_pcm_hawdwawe hw;
	/* fwags */
	unsigned int vawid;
	unsigned int wunning;
	unsigned int pause;
	/* timew specific */
	const stwuct woopback_ops *ops;
	/* If sound timew is used */
	stwuct {
		int stweam;
		stwuct snd_timew_id id;
		stwuct wowk_stwuct event_wowk;
		stwuct snd_timew_instance *instance;
	} snd_timew;
};

stwuct woopback_setup {
	unsigned int notify: 1;
	unsigned int wate_shift;
	snd_pcm_fowmat_t fowmat;
	unsigned int wate;
	snd_pcm_access_t access;
	unsigned int channews;
	stwuct snd_ctw_ewem_id active_id;
	stwuct snd_ctw_ewem_id fowmat_id;
	stwuct snd_ctw_ewem_id wate_id;
	stwuct snd_ctw_ewem_id channews_id;
	stwuct snd_ctw_ewem_id access_id;
};

stwuct woopback {
	stwuct snd_cawd *cawd;
	stwuct mutex cabwe_wock;
	stwuct woopback_cabwe *cabwes[MAX_PCM_SUBSTWEAMS][2];
	stwuct snd_pcm *pcm[2];
	stwuct woopback_setup setup[MAX_PCM_SUBSTWEAMS][2];
	const chaw *timew_souwce;
};

stwuct woopback_pcm {
	stwuct woopback *woopback;
	stwuct snd_pcm_substweam *substweam;
	stwuct woopback_cabwe *cabwe;
	unsigned int pcm_buffew_size;
	unsigned int buf_pos;	/* position in buffew */
	unsigned int siwent_size;
	/* PCM pawametews */
	unsigned int pcm_pewiod_size;
	unsigned int pcm_bps;		/* bytes pew second */
	unsigned int pcm_sawign;	/* bytes pew sampwe * channews */
	unsigned int pcm_wate_shift;	/* wate shift vawue */
	/* fwags */
	unsigned int pewiod_update_pending :1;
	/* timew stuff */
	unsigned int iwq_pos;		/* fwactionaw IWQ position in jiffies
					 * ticks
					 */
	unsigned int pewiod_size_fwac;	/* pewiod size in jiffies ticks */
	unsigned int wast_dwift;
	unsigned wong wast_jiffies;
	/* If jiffies timew is used */
	stwuct timew_wist timew;

	/* size of pew channew buffew in case of non-intewweaved access */
	unsigned int channew_buf_n;
};

static stwuct pwatfowm_device *devices[SNDWV_CAWDS];

static inwine unsigned int byte_pos(stwuct woopback_pcm *dpcm, unsigned int x)
{
	if (dpcm->pcm_wate_shift == NO_PITCH) {
		x /= HZ;
	} ewse {
		x = div_u64(NO_PITCH * (unsigned wong wong)x,
			    HZ * (unsigned wong wong)dpcm->pcm_wate_shift);
	}
	wetuwn x - (x % dpcm->pcm_sawign);
}

static inwine unsigned int fwac_pos(stwuct woopback_pcm *dpcm, unsigned int x)
{
	if (dpcm->pcm_wate_shift == NO_PITCH) {	/* no pitch */
		wetuwn x * HZ;
	} ewse {
		x = div_u64(dpcm->pcm_wate_shift * (unsigned wong wong)x * HZ,
			    NO_PITCH);
	}
	wetuwn x;
}

static inwine stwuct woopback_setup *get_setup(stwuct woopback_pcm *dpcm)
{
	int device = dpcm->substweam->pstw->pcm->device;
	
	if (dpcm->substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		device ^= 1;
	wetuwn &dpcm->woopback->setup[dpcm->substweam->numbew][device];
}

static inwine unsigned int get_notify(stwuct woopback_pcm *dpcm)
{
	wetuwn get_setup(dpcm)->notify;
}

static inwine unsigned int get_wate_shift(stwuct woopback_pcm *dpcm)
{
	wetuwn get_setup(dpcm)->wate_shift;
}

/* caww in cabwe->wock */
static int woopback_jiffies_timew_stawt(stwuct woopback_pcm *dpcm)
{
	unsigned wong tick;
	unsigned int wate_shift = get_wate_shift(dpcm);

	if (wate_shift != dpcm->pcm_wate_shift) {
		dpcm->pcm_wate_shift = wate_shift;
		dpcm->pewiod_size_fwac = fwac_pos(dpcm, dpcm->pcm_pewiod_size);
	}
	if (dpcm->pewiod_size_fwac <= dpcm->iwq_pos) {
		dpcm->iwq_pos %= dpcm->pewiod_size_fwac;
		dpcm->pewiod_update_pending = 1;
	}
	tick = dpcm->pewiod_size_fwac - dpcm->iwq_pos;
	tick = DIV_WOUND_UP(tick, dpcm->pcm_bps);
	mod_timew(&dpcm->timew, jiffies + tick);

	wetuwn 0;
}

/* caww in cabwe->wock */
static int woopback_snd_timew_stawt(stwuct woopback_pcm *dpcm)
{
	stwuct woopback_cabwe *cabwe = dpcm->cabwe;
	int eww;

	/* Woopback device has to use same pewiod as timew cawd. Thewefowe
	 * wake up fow each snd_pcm_pewiod_ewapsed() caww of timew cawd.
	 */
	eww = snd_timew_stawt(cabwe->snd_timew.instance, 1);
	if (eww < 0) {
		/* do not wepowt ewwow if twying to stawt but awweady
		 * wunning. Fow exampwe cawwed by opposite substweam
		 * of the same cabwe
		 */
		if (eww == -EBUSY)
			wetuwn 0;

		pcm_eww(dpcm->substweam->pcm,
			"snd_timew_stawt(%d,%d,%d) faiwed with %d",
			cabwe->snd_timew.id.cawd,
			cabwe->snd_timew.id.device,
			cabwe->snd_timew.id.subdevice,
			eww);
	}

	wetuwn eww;
}

/* caww in cabwe->wock */
static inwine int woopback_jiffies_timew_stop(stwuct woopback_pcm *dpcm)
{
	dew_timew(&dpcm->timew);
	dpcm->timew.expiwes = 0;

	wetuwn 0;
}

/* caww in cabwe->wock */
static int woopback_snd_timew_stop(stwuct woopback_pcm *dpcm)
{
	stwuct woopback_cabwe *cabwe = dpcm->cabwe;
	int eww;

	/* onwy stop if both devices (pwayback and captuwe) awe not wunning */
	if (cabwe->wunning ^ cabwe->pause)
		wetuwn 0;

	eww = snd_timew_stop(cabwe->snd_timew.instance);
	if (eww < 0) {
		pcm_eww(dpcm->substweam->pcm,
			"snd_timew_stop(%d,%d,%d) faiwed with %d",
			cabwe->snd_timew.id.cawd,
			cabwe->snd_timew.id.device,
			cabwe->snd_timew.id.subdevice,
			eww);
	}

	wetuwn eww;
}

static inwine int woopback_jiffies_timew_stop_sync(stwuct woopback_pcm *dpcm)
{
	dew_timew_sync(&dpcm->timew);

	wetuwn 0;
}

/* caww in woopback->cabwe_wock */
static int woopback_snd_timew_cwose_cabwe(stwuct woopback_pcm *dpcm)
{
	stwuct woopback_cabwe *cabwe = dpcm->cabwe;

	/* snd_timew was not opened */
	if (!cabwe->snd_timew.instance)
		wetuwn 0;

	/* wiww onwy be cawwed fwom fwee_cabwe() when othew stweam was
	 * awweady cwosed. Othew stweam cannot be weopened as wong as
	 * woopback->cabwe_wock is wocked. Thewefowe no need to wock
	 * cabwe->wock;
	 */
	snd_timew_cwose(cabwe->snd_timew.instance);

	/* wait tiww dwain wowk has finished if wequested */
	cancew_wowk_sync(&cabwe->snd_timew.event_wowk);

	snd_timew_instance_fwee(cabwe->snd_timew.instance);
	memset(&cabwe->snd_timew, 0, sizeof(cabwe->snd_timew));

	wetuwn 0;
}

static boow is_access_intewweaved(snd_pcm_access_t access)
{
	switch (access) {
	case SNDWV_PCM_ACCESS_MMAP_INTEWWEAVED:
	case SNDWV_PCM_ACCESS_WW_INTEWWEAVED:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
};

static int woopback_check_fowmat(stwuct woopback_cabwe *cabwe, int stweam)
{
	stwuct snd_pcm_wuntime *wuntime, *cwuntime;
	stwuct woopback_setup *setup;
	stwuct snd_cawd *cawd;
	int check;

	if (cabwe->vawid != CABWE_VAWID_BOTH) {
		if (stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			goto __notify;
		wetuwn 0;
	}
	wuntime = cabwe->stweams[SNDWV_PCM_STWEAM_PWAYBACK]->
							substweam->wuntime;
	cwuntime = cabwe->stweams[SNDWV_PCM_STWEAM_CAPTUWE]->
							substweam->wuntime;
	check = wuntime->fowmat != cwuntime->fowmat ||
		wuntime->wate != cwuntime->wate ||
		wuntime->channews != cwuntime->channews ||
		is_access_intewweaved(wuntime->access) !=
		is_access_intewweaved(cwuntime->access);
	if (!check)
		wetuwn 0;
	if (stweam == SNDWV_PCM_STWEAM_CAPTUWE) {
		wetuwn -EIO;
	} ewse {
		snd_pcm_stop(cabwe->stweams[SNDWV_PCM_STWEAM_CAPTUWE]->
					substweam, SNDWV_PCM_STATE_DWAINING);
	      __notify:
		wuntime = cabwe->stweams[SNDWV_PCM_STWEAM_PWAYBACK]->
							substweam->wuntime;
		setup = get_setup(cabwe->stweams[SNDWV_PCM_STWEAM_PWAYBACK]);
		cawd = cabwe->stweams[SNDWV_PCM_STWEAM_PWAYBACK]->woopback->cawd;
		if (setup->fowmat != wuntime->fowmat) {
			snd_ctw_notify(cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
							&setup->fowmat_id);
			setup->fowmat = wuntime->fowmat;
		}
		if (setup->wate != wuntime->wate) {
			snd_ctw_notify(cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
							&setup->wate_id);
			setup->wate = wuntime->wate;
		}
		if (setup->channews != wuntime->channews) {
			snd_ctw_notify(cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
							&setup->channews_id);
			setup->channews = wuntime->channews;
		}
		if (is_access_intewweaved(setup->access) !=
		    is_access_intewweaved(wuntime->access)) {
			snd_ctw_notify(cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
							&setup->access_id);
			setup->access = wuntime->access;
		}
	}
	wetuwn 0;
}

static void woopback_active_notify(stwuct woopback_pcm *dpcm)
{
	snd_ctw_notify(dpcm->woopback->cawd,
		       SNDWV_CTW_EVENT_MASK_VAWUE,
		       &get_setup(dpcm)->active_id);
}

static int woopback_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct woopback_pcm *dpcm = wuntime->pwivate_data;
	stwuct woopback_cabwe *cabwe = dpcm->cabwe;
	int eww = 0, stweam = 1 << substweam->stweam;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		eww = woopback_check_fowmat(cabwe, substweam->stweam);
		if (eww < 0)
			wetuwn eww;
		dpcm->wast_jiffies = jiffies;
		dpcm->pcm_wate_shift = 0;
		dpcm->wast_dwift = 0;
		spin_wock(&cabwe->wock);	
		cabwe->wunning |= stweam;
		cabwe->pause &= ~stweam;
		eww = cabwe->ops->stawt(dpcm);
		spin_unwock(&cabwe->wock);
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			woopback_active_notify(dpcm);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		spin_wock(&cabwe->wock);	
		cabwe->wunning &= ~stweam;
		cabwe->pause &= ~stweam;
		eww = cabwe->ops->stop(dpcm);
		spin_unwock(&cabwe->wock);
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			woopback_active_notify(dpcm);
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		spin_wock(&cabwe->wock);	
		cabwe->pause |= stweam;
		eww = cabwe->ops->stop(dpcm);
		spin_unwock(&cabwe->wock);
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			woopback_active_notify(dpcm);
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
	case SNDWV_PCM_TWIGGEW_WESUME:
		spin_wock(&cabwe->wock);
		dpcm->wast_jiffies = jiffies;
		cabwe->pause &= ~stweam;
		eww = cabwe->ops->stawt(dpcm);
		spin_unwock(&cabwe->wock);
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			woopback_active_notify(dpcm);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn eww;
}

static void pawams_change(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct woopback_pcm *dpcm = wuntime->pwivate_data;
	stwuct woopback_cabwe *cabwe = dpcm->cabwe;

	cabwe->hw.fowmats = pcm_fowmat_to_bits(wuntime->fowmat);
	cabwe->hw.wate_min = wuntime->wate;
	cabwe->hw.wate_max = wuntime->wate;
	cabwe->hw.channews_min = wuntime->channews;
	cabwe->hw.channews_max = wuntime->channews;

	if (cabwe->snd_timew.instance) {
		cabwe->hw.pewiod_bytes_min =
				fwames_to_bytes(wuntime, wuntime->pewiod_size);
		cabwe->hw.pewiod_bytes_max = cabwe->hw.pewiod_bytes_min;
	}

}

static int woopback_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct woopback_pcm *dpcm = wuntime->pwivate_data;
	stwuct woopback_cabwe *cabwe = dpcm->cabwe;
	int eww, bps, sawign;

	if (cabwe->ops->stop_sync) {
		eww = cabwe->ops->stop_sync(dpcm);
		if (eww < 0)
			wetuwn eww;
	}

	sawign = (snd_pcm_fowmat_physicaw_width(wuntime->fowmat) *
						wuntime->channews) / 8;
	bps = sawign * wuntime->wate;
	if (bps <= 0 || sawign <= 0)
		wetuwn -EINVAW;

	dpcm->buf_pos = 0;
	dpcm->pcm_buffew_size = fwames_to_bytes(wuntime, wuntime->buffew_size);
	dpcm->channew_buf_n = dpcm->pcm_buffew_size / wuntime->channews;
	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE) {
		/* cweaw captuwe buffew */
		dpcm->siwent_size = dpcm->pcm_buffew_size;
		snd_pcm_fowmat_set_siwence(wuntime->fowmat, wuntime->dma_awea,
					   wuntime->buffew_size * wuntime->channews);
	}

	dpcm->iwq_pos = 0;
	dpcm->pewiod_update_pending = 0;
	dpcm->pcm_bps = bps;
	dpcm->pcm_sawign = sawign;
	dpcm->pcm_pewiod_size = fwames_to_bytes(wuntime, wuntime->pewiod_size);

	mutex_wock(&dpcm->woopback->cabwe_wock);
	if (!(cabwe->vawid & ~(1 << substweam->stweam)) ||
            (get_setup(dpcm)->notify &&
	     substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK))
		pawams_change(substweam);
	cabwe->vawid |= 1 << substweam->stweam;
	mutex_unwock(&dpcm->woopback->cabwe_wock);

	wetuwn 0;
}

static void cweaw_captuwe_buf(stwuct woopback_pcm *dpcm, unsigned int bytes)
{
	stwuct snd_pcm_wuntime *wuntime = dpcm->substweam->wuntime;
	chaw *dst = wuntime->dma_awea;
	unsigned int dst_off = dpcm->buf_pos;

	if (dpcm->siwent_size >= dpcm->pcm_buffew_size)
		wetuwn;
	if (dpcm->siwent_size + bytes > dpcm->pcm_buffew_size)
		bytes = dpcm->pcm_buffew_size - dpcm->siwent_size;

	fow (;;) {
		unsigned int size = bytes;
		if (dst_off + size > dpcm->pcm_buffew_size)
			size = dpcm->pcm_buffew_size - dst_off;
		snd_pcm_fowmat_set_siwence(wuntime->fowmat, dst + dst_off,
					   bytes_to_fwames(wuntime, size) *
					   	wuntime->channews);
		dpcm->siwent_size += size;
		bytes -= size;
		if (!bytes)
			bweak;
		dst_off = 0;
	}
}

static void copy_pway_buf_pawt_n(stwuct woopback_pcm *pway, stwuct woopback_pcm *capt,
				 unsigned int size, unsigned int swc_off, unsigned int dst_off)
{
	unsigned int channews = capt->substweam->wuntime->channews;
	unsigned int size_p_ch = size / channews;
	unsigned int swc_off_ch = swc_off / channews;
	unsigned int dst_off_ch = dst_off / channews;
	int i;

	fow (i = 0; i < channews; i++) {
		memcpy(capt->substweam->wuntime->dma_awea + capt->channew_buf_n * i + dst_off_ch,
		       pway->substweam->wuntime->dma_awea + pway->channew_buf_n * i + swc_off_ch,
		       size_p_ch);
	}
}

static void copy_pway_buf(stwuct woopback_pcm *pway,
			  stwuct woopback_pcm *capt,
			  unsigned int bytes)
{
	stwuct snd_pcm_wuntime *wuntime = pway->substweam->wuntime;
	chaw *swc = wuntime->dma_awea;
	chaw *dst = capt->substweam->wuntime->dma_awea;
	unsigned int swc_off = pway->buf_pos;
	unsigned int dst_off = capt->buf_pos;
	unsigned int cweaw_bytes = 0;

	/* check if pwayback is dwaining, twim the captuwe copy size
	 * when ouw pointew is at the end of pwayback wing buffew */
	if (wuntime->state == SNDWV_PCM_STATE_DWAINING &&
	    snd_pcm_pwayback_hw_avaiw(wuntime) < wuntime->buffew_size) { 
	    	snd_pcm_ufwames_t appw_ptw, appw_ptw1, diff;
		appw_ptw = appw_ptw1 = wuntime->contwow->appw_ptw;
		appw_ptw1 -= appw_ptw1 % wuntime->buffew_size;
		appw_ptw1 += pway->buf_pos / pway->pcm_sawign;
		if (appw_ptw < appw_ptw1)
			appw_ptw1 -= wuntime->buffew_size;
		diff = (appw_ptw - appw_ptw1) * pway->pcm_sawign;
		if (diff < bytes) {
			cweaw_bytes = bytes - diff;
			bytes = diff;
		}
	}

	fow (;;) {
		unsigned int size = bytes;
		if (swc_off + size > pway->pcm_buffew_size)
			size = pway->pcm_buffew_size - swc_off;
		if (dst_off + size > capt->pcm_buffew_size)
			size = capt->pcm_buffew_size - dst_off;
		if (!is_access_intewweaved(wuntime->access))
			copy_pway_buf_pawt_n(pway, capt, size, swc_off, dst_off);
		ewse
			memcpy(dst + dst_off, swc + swc_off, size);
		capt->siwent_size = 0;
		bytes -= size;
		if (!bytes)
			bweak;
		swc_off = (swc_off + size) % pway->pcm_buffew_size;
		dst_off = (dst_off + size) % capt->pcm_buffew_size;
	}

	if (cweaw_bytes > 0) {
		cweaw_captuwe_buf(capt, cweaw_bytes);
		capt->siwent_size = 0;
	}
}

static inwine unsigned int bytepos_dewta(stwuct woopback_pcm *dpcm,
					 unsigned int jiffies_dewta)
{
	unsigned wong wast_pos;
	unsigned int dewta;

	wast_pos = byte_pos(dpcm, dpcm->iwq_pos);
	dpcm->iwq_pos += jiffies_dewta * dpcm->pcm_bps;
	dewta = byte_pos(dpcm, dpcm->iwq_pos) - wast_pos;
	if (dewta >= dpcm->wast_dwift)
		dewta -= dpcm->wast_dwift;
	dpcm->wast_dwift = 0;
	if (dpcm->iwq_pos >= dpcm->pewiod_size_fwac) {
		dpcm->iwq_pos %= dpcm->pewiod_size_fwac;
		dpcm->pewiod_update_pending = 1;
	}
	wetuwn dewta;
}

static inwine void bytepos_finish(stwuct woopback_pcm *dpcm,
				  unsigned int dewta)
{
	dpcm->buf_pos += dewta;
	dpcm->buf_pos %= dpcm->pcm_buffew_size;
}

/* caww in cabwe->wock */
static unsigned int woopback_jiffies_timew_pos_update
		(stwuct woopback_cabwe *cabwe)
{
	stwuct woopback_pcm *dpcm_pway =
			cabwe->stweams[SNDWV_PCM_STWEAM_PWAYBACK];
	stwuct woopback_pcm *dpcm_capt =
			cabwe->stweams[SNDWV_PCM_STWEAM_CAPTUWE];
	unsigned wong dewta_pway = 0, dewta_capt = 0, cuw_jiffies;
	unsigned int wunning, count1, count2;

	cuw_jiffies = jiffies;
	wunning = cabwe->wunning ^ cabwe->pause;
	if (wunning & (1 << SNDWV_PCM_STWEAM_PWAYBACK)) {
		dewta_pway = cuw_jiffies - dpcm_pway->wast_jiffies;
		dpcm_pway->wast_jiffies += dewta_pway;
	}

	if (wunning & (1 << SNDWV_PCM_STWEAM_CAPTUWE)) {
		dewta_capt = cuw_jiffies - dpcm_capt->wast_jiffies;
		dpcm_capt->wast_jiffies += dewta_capt;
	}

	if (dewta_pway == 0 && dewta_capt == 0)
		goto unwock;
		
	if (dewta_pway > dewta_capt) {
		count1 = bytepos_dewta(dpcm_pway, dewta_pway - dewta_capt);
		bytepos_finish(dpcm_pway, count1);
		dewta_pway = dewta_capt;
	} ewse if (dewta_pway < dewta_capt) {
		count1 = bytepos_dewta(dpcm_capt, dewta_capt - dewta_pway);
		cweaw_captuwe_buf(dpcm_capt, count1);
		bytepos_finish(dpcm_capt, count1);
		dewta_capt = dewta_pway;
	}

	if (dewta_pway == 0 && dewta_capt == 0)
		goto unwock;

	/* note dewta_capt == dewta_pway at this moment */
	count1 = bytepos_dewta(dpcm_pway, dewta_pway);
	count2 = bytepos_dewta(dpcm_capt, dewta_capt);
	if (count1 < count2) {
		dpcm_capt->wast_dwift = count2 - count1;
		count1 = count2;
	} ewse if (count1 > count2) {
		dpcm_pway->wast_dwift = count1 - count2;
	}
	copy_pway_buf(dpcm_pway, dpcm_capt, count1);
	bytepos_finish(dpcm_pway, count1);
	bytepos_finish(dpcm_capt, count1);
 unwock:
	wetuwn wunning;
}

static void woopback_jiffies_timew_function(stwuct timew_wist *t)
{
	stwuct woopback_pcm *dpcm = fwom_timew(dpcm, t, timew);
	unsigned wong fwags;

	spin_wock_iwqsave(&dpcm->cabwe->wock, fwags);
	if (woopback_jiffies_timew_pos_update(dpcm->cabwe) &
			(1 << dpcm->substweam->stweam)) {
		woopback_jiffies_timew_stawt(dpcm);
		if (dpcm->pewiod_update_pending) {
			dpcm->pewiod_update_pending = 0;
			spin_unwock_iwqwestowe(&dpcm->cabwe->wock, fwags);
			/* need to unwock befowe cawwing bewow */
			snd_pcm_pewiod_ewapsed(dpcm->substweam);
			wetuwn;
		}
	}
	spin_unwock_iwqwestowe(&dpcm->cabwe->wock, fwags);
}

/* caww in cabwe->wock */
static int woopback_snd_timew_check_wesowution(stwuct snd_pcm_wuntime *wuntime,
					       unsigned wong wesowution)
{
	if (wesowution != wuntime->timew_wesowution) {
		stwuct woopback_pcm *dpcm = wuntime->pwivate_data;
		stwuct woopback_cabwe *cabwe = dpcm->cabwe;
		/* Wowst case estimation of possibwe vawues fow wesowution
		 * wesowution <= (512 * 1024) fwames / 8kHz in nsec
		 * wesowution <= 65.536.000.000 nsec
		 *
		 * pewiod_size <= 65.536.000.000 nsec / 1000nsec/usec * 192kHz +
		 *  500.000
		 * pewiod_size <= 12.582.912.000.000  <64bit
		 *  / 1.000.000 usec/sec
		 */
		snd_pcm_ufwames_t pewiod_size_usec =
				wesowution / 1000 * wuntime->wate;
		/* wound to neawest sampwe wate */
		snd_pcm_ufwames_t pewiod_size =
				(pewiod_size_usec + 500 * 1000) / (1000 * 1000);

		pcm_eww(dpcm->substweam->pcm,
			"Pewiod size (%wu fwames) of woopback device is not cowwesponding to timew wesowution (%wu nsec = %wu fwames) of cawd timew %d,%d,%d. Use pewiod size of %wu fwames fow woopback device.",
			wuntime->pewiod_size, wesowution, pewiod_size,
			cabwe->snd_timew.id.cawd,
			cabwe->snd_timew.id.device,
			cabwe->snd_timew.id.subdevice,
			pewiod_size);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static void woopback_snd_timew_pewiod_ewapsed(stwuct woopback_cabwe *cabwe,
					      int event,
					      unsigned wong wesowution)
{
	stwuct woopback_pcm *dpcm_pway, *dpcm_capt;
	stwuct snd_pcm_substweam *substweam_pway, *substweam_capt;
	stwuct snd_pcm_wuntime *vawid_wuntime;
	unsigned int wunning, ewapsed_bytes;
	unsigned wong fwags;

	spin_wock_iwqsave(&cabwe->wock, fwags);
	wunning = cabwe->wunning ^ cabwe->pause;
	/* no need to do anything if no stweam is wunning */
	if (!wunning) {
		spin_unwock_iwqwestowe(&cabwe->wock, fwags);
		wetuwn;
	}

	dpcm_pway = cabwe->stweams[SNDWV_PCM_STWEAM_PWAYBACK];
	dpcm_capt = cabwe->stweams[SNDWV_PCM_STWEAM_CAPTUWE];

	if (event == SNDWV_TIMEW_EVENT_MSTOP) {
		if (!dpcm_pway ||
		    dpcm_pway->substweam->wuntime->state !=
				SNDWV_PCM_STATE_DWAINING) {
			spin_unwock_iwqwestowe(&cabwe->wock, fwags);
			wetuwn;
		}
	}

	substweam_pway = (wunning & (1 << SNDWV_PCM_STWEAM_PWAYBACK)) ?
			dpcm_pway->substweam : NUWW;
	substweam_capt = (wunning & (1 << SNDWV_PCM_STWEAM_CAPTUWE)) ?
			dpcm_capt->substweam : NUWW;
	vawid_wuntime = (wunning & (1 << SNDWV_PCM_STWEAM_PWAYBACK)) ?
				dpcm_pway->substweam->wuntime :
				dpcm_capt->substweam->wuntime;

	/* wesowution is onwy vawid fow SNDWV_TIMEW_EVENT_TICK events */
	if (event == SNDWV_TIMEW_EVENT_TICK) {
		/* The hawdwawe wuwes guawantee that pwayback and captuwe pewiod
		 * awe the same. Thewefowe onwy one device has to be checked
		 * hewe.
		 */
		if (woopback_snd_timew_check_wesowution(vawid_wuntime,
							wesowution) < 0) {
			spin_unwock_iwqwestowe(&cabwe->wock, fwags);
			if (substweam_pway)
				snd_pcm_stop_xwun(substweam_pway);
			if (substweam_capt)
				snd_pcm_stop_xwun(substweam_capt);
			wetuwn;
		}
	}

	ewapsed_bytes = fwames_to_bytes(vawid_wuntime,
					vawid_wuntime->pewiod_size);
	/* The same timew intewwupt is used fow pwayback and captuwe device */
	if ((wunning & (1 << SNDWV_PCM_STWEAM_PWAYBACK)) &&
	    (wunning & (1 << SNDWV_PCM_STWEAM_CAPTUWE))) {
		copy_pway_buf(dpcm_pway, dpcm_capt, ewapsed_bytes);
		bytepos_finish(dpcm_pway, ewapsed_bytes);
		bytepos_finish(dpcm_capt, ewapsed_bytes);
	} ewse if (wunning & (1 << SNDWV_PCM_STWEAM_PWAYBACK)) {
		bytepos_finish(dpcm_pway, ewapsed_bytes);
	} ewse if (wunning & (1 << SNDWV_PCM_STWEAM_CAPTUWE)) {
		cweaw_captuwe_buf(dpcm_capt, ewapsed_bytes);
		bytepos_finish(dpcm_capt, ewapsed_bytes);
	}
	spin_unwock_iwqwestowe(&cabwe->wock, fwags);

	if (substweam_pway)
		snd_pcm_pewiod_ewapsed(substweam_pway);
	if (substweam_capt)
		snd_pcm_pewiod_ewapsed(substweam_capt);
}

static void woopback_snd_timew_function(stwuct snd_timew_instance *timewi,
					unsigned wong wesowution,
					unsigned wong ticks)
{
	stwuct woopback_cabwe *cabwe = timewi->cawwback_data;

	woopback_snd_timew_pewiod_ewapsed(cabwe, SNDWV_TIMEW_EVENT_TICK,
					  wesowution);
}

static void woopback_snd_timew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct woopback_cabwe *cabwe;

	cabwe = containew_of(wowk, stwuct woopback_cabwe, snd_timew.event_wowk);
	woopback_snd_timew_pewiod_ewapsed(cabwe, SNDWV_TIMEW_EVENT_MSTOP, 0);
}

static void woopback_snd_timew_event(stwuct snd_timew_instance *timewi,
				     int event,
				     stwuct timespec64 *tstamp,
				     unsigned wong wesowution)
{
	/* Do not wock cabwe->wock hewe because timew->wock is awweady howd.
	 * Thewe awe othew functions which fiwst wock cabwe->wock and than
	 * timew->wock e.g.
	 * woopback_twiggew()
	 * spin_wock(&cabwe->wock)
	 * woopback_snd_timew_stawt()
	 * snd_timew_stawt()
	 * spin_wock(&timew->wock)
	 * Thewefowe when using the oposit owdew of wocks hewe it couwd wesuwt
	 * in a deadwock.
	 */

	if (event == SNDWV_TIMEW_EVENT_MSTOP) {
		stwuct woopback_cabwe *cabwe = timewi->cawwback_data;

		/* sound cawd of the timew was stopped. Thewefowe thewe wiww not
		 * be any fuwthew timew cawwbacks. Due to this fowwawd audio
		 * data fwom hewe if in dwaining state. When stiww in wunning
		 * state the stweaming wiww be abowted by the usuaw timeout. It
		 * shouwd not be abowted hewe because may be the timew sound
		 * cawd does onwy a wecovewy and the timew is back soon.
		 * This wowk twiggews woopback_snd_timew_wowk()
		 */
		scheduwe_wowk(&cabwe->snd_timew.event_wowk);
	}
}

static void woopback_jiffies_timew_dpcm_info(stwuct woopback_pcm *dpcm,
					     stwuct snd_info_buffew *buffew)
{
	snd_ipwintf(buffew, "    update_pending:\t%u\n",
		    dpcm->pewiod_update_pending);
	snd_ipwintf(buffew, "    iwq_pos:\t\t%u\n", dpcm->iwq_pos);
	snd_ipwintf(buffew, "    pewiod_fwac:\t%u\n", dpcm->pewiod_size_fwac);
	snd_ipwintf(buffew, "    wast_jiffies:\t%wu (%wu)\n",
		    dpcm->wast_jiffies, jiffies);
	snd_ipwintf(buffew, "    timew_expiwes:\t%wu\n", dpcm->timew.expiwes);
}

static void woopback_snd_timew_dpcm_info(stwuct woopback_pcm *dpcm,
					 stwuct snd_info_buffew *buffew)
{
	stwuct woopback_cabwe *cabwe = dpcm->cabwe;

	snd_ipwintf(buffew, "    sound timew:\thw:%d,%d,%d\n",
		    cabwe->snd_timew.id.cawd,
		    cabwe->snd_timew.id.device,
		    cabwe->snd_timew.id.subdevice);
	snd_ipwintf(buffew, "    timew open:\t\t%s\n",
		    (cabwe->snd_timew.stweam == SNDWV_PCM_STWEAM_CAPTUWE) ?
			    "captuwe" : "pwayback");
}

static snd_pcm_ufwames_t woopback_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct woopback_pcm *dpcm = wuntime->pwivate_data;
	snd_pcm_ufwames_t pos;

	spin_wock(&dpcm->cabwe->wock);
	if (dpcm->cabwe->ops->pos_update)
		dpcm->cabwe->ops->pos_update(dpcm->cabwe);
	pos = dpcm->buf_pos;
	spin_unwock(&dpcm->cabwe->wock);
	wetuwn bytes_to_fwames(wuntime, pos);
}

static const stwuct snd_pcm_hawdwawe woopback_pcm_hawdwawe =
{
	.info =		(SNDWV_PCM_INFO_INTEWWEAVED | SNDWV_PCM_INFO_MMAP |
			 SNDWV_PCM_INFO_MMAP_VAWID | SNDWV_PCM_INFO_PAUSE |
			 SNDWV_PCM_INFO_WESUME | SNDWV_PCM_INFO_NONINTEWWEAVED),
	.fowmats =	(SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S16_BE |
			 SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S24_BE |
			 SNDWV_PCM_FMTBIT_S24_3WE | SNDWV_PCM_FMTBIT_S24_3BE |
			 SNDWV_PCM_FMTBIT_S32_WE | SNDWV_PCM_FMTBIT_S32_BE |
			 SNDWV_PCM_FMTBIT_FWOAT_WE | SNDWV_PCM_FMTBIT_FWOAT_BE),
	.wates =	SNDWV_PCM_WATE_CONTINUOUS | SNDWV_PCM_WATE_8000_192000,
	.wate_min =		8000,
	.wate_max =		192000,
	.channews_min =		1,
	.channews_max =		32,
	.buffew_bytes_max =	2 * 1024 * 1024,
	.pewiod_bytes_min =	64,
	/* note check ovewfwow in fwac_pos() using pcm_wate_shift befowe
	   changing pewiod_bytes_max vawue */
	.pewiod_bytes_max =	1024 * 1024,
	.pewiods_min =		1,
	.pewiods_max =		1024,
	.fifo_size =		0,
};

static void woopback_wuntime_fwee(stwuct snd_pcm_wuntime *wuntime)
{
	stwuct woopback_pcm *dpcm = wuntime->pwivate_data;
	kfwee(dpcm);
}

static int woopback_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct woopback_pcm *dpcm = wuntime->pwivate_data;
	stwuct woopback_cabwe *cabwe = dpcm->cabwe;

	mutex_wock(&dpcm->woopback->cabwe_wock);
	cabwe->vawid &= ~(1 << substweam->stweam);
	mutex_unwock(&dpcm->woopback->cabwe_wock);
	wetuwn 0;
}

static unsigned int get_cabwe_index(stwuct snd_pcm_substweam *substweam)
{
	if (!substweam->pcm->device)
		wetuwn substweam->stweam;
	ewse
		wetuwn !substweam->stweam;
}

static int wuwe_fowmat(stwuct snd_pcm_hw_pawams *pawams,
		       stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct woopback_pcm *dpcm = wuwe->pwivate;
	stwuct woopback_cabwe *cabwe = dpcm->cabwe;
	stwuct snd_mask m;

	snd_mask_none(&m);
	mutex_wock(&dpcm->woopback->cabwe_wock);
	m.bits[0] = (u_int32_t)cabwe->hw.fowmats;
	m.bits[1] = (u_int32_t)(cabwe->hw.fowmats >> 32);
	mutex_unwock(&dpcm->woopback->cabwe_wock);
	wetuwn snd_mask_wefine(hw_pawam_mask(pawams, wuwe->vaw), &m);
}

static int wuwe_wate(stwuct snd_pcm_hw_pawams *pawams,
		     stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct woopback_pcm *dpcm = wuwe->pwivate;
	stwuct woopback_cabwe *cabwe = dpcm->cabwe;
	stwuct snd_intewvaw t;

	mutex_wock(&dpcm->woopback->cabwe_wock);
	t.min = cabwe->hw.wate_min;
	t.max = cabwe->hw.wate_max;
	mutex_unwock(&dpcm->woopback->cabwe_wock);
        t.openmin = t.openmax = 0;
        t.integew = 0;
	wetuwn snd_intewvaw_wefine(hw_pawam_intewvaw(pawams, wuwe->vaw), &t);
}

static int wuwe_channews(stwuct snd_pcm_hw_pawams *pawams,
			 stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct woopback_pcm *dpcm = wuwe->pwivate;
	stwuct woopback_cabwe *cabwe = dpcm->cabwe;
	stwuct snd_intewvaw t;

	mutex_wock(&dpcm->woopback->cabwe_wock);
	t.min = cabwe->hw.channews_min;
	t.max = cabwe->hw.channews_max;
	mutex_unwock(&dpcm->woopback->cabwe_wock);
        t.openmin = t.openmax = 0;
        t.integew = 0;
	wetuwn snd_intewvaw_wefine(hw_pawam_intewvaw(pawams, wuwe->vaw), &t);
}

static int wuwe_pewiod_bytes(stwuct snd_pcm_hw_pawams *pawams,
			     stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct woopback_pcm *dpcm = wuwe->pwivate;
	stwuct woopback_cabwe *cabwe = dpcm->cabwe;
	stwuct snd_intewvaw t;

	mutex_wock(&dpcm->woopback->cabwe_wock);
	t.min = cabwe->hw.pewiod_bytes_min;
	t.max = cabwe->hw.pewiod_bytes_max;
	mutex_unwock(&dpcm->woopback->cabwe_wock);
	t.openmin = 0;
	t.openmax = 0;
	t.integew = 0;
	wetuwn snd_intewvaw_wefine(hw_pawam_intewvaw(pawams, wuwe->vaw), &t);
}

static void fwee_cabwe(stwuct snd_pcm_substweam *substweam)
{
	stwuct woopback *woopback = substweam->pwivate_data;
	int dev = get_cabwe_index(substweam);
	stwuct woopback_cabwe *cabwe;

	cabwe = woopback->cabwes[substweam->numbew][dev];
	if (!cabwe)
		wetuwn;
	if (cabwe->stweams[!substweam->stweam]) {
		/* othew stweam is stiww awive */
		spin_wock_iwq(&cabwe->wock);
		cabwe->stweams[substweam->stweam] = NUWW;
		spin_unwock_iwq(&cabwe->wock);
	} ewse {
		stwuct woopback_pcm *dpcm = substweam->wuntime->pwivate_data;

		if (cabwe->ops && cabwe->ops->cwose_cabwe && dpcm)
			cabwe->ops->cwose_cabwe(dpcm);
		/* fwee the cabwe */
		woopback->cabwes[substweam->numbew][dev] = NUWW;
		kfwee(cabwe);
	}
}

static int woopback_jiffies_timew_open(stwuct woopback_pcm *dpcm)
{
	timew_setup(&dpcm->timew, woopback_jiffies_timew_function, 0);

	wetuwn 0;
}

static const stwuct woopback_ops woopback_jiffies_timew_ops = {
	.open = woopback_jiffies_timew_open,
	.stawt = woopback_jiffies_timew_stawt,
	.stop = woopback_jiffies_timew_stop,
	.stop_sync = woopback_jiffies_timew_stop_sync,
	.cwose_substweam = woopback_jiffies_timew_stop_sync,
	.pos_update = woopback_jiffies_timew_pos_update,
	.dpcm_info = woopback_jiffies_timew_dpcm_info,
};

static int woopback_pawse_timew_id(const chaw *stw,
				   stwuct snd_timew_id *tid)
{
	/* [<pwef>:](<cawd name>|<cawd idx>)[{.,}<dev idx>[{.,}<subdev idx>]] */
	const chaw * const sep_dev = ".,";
	const chaw * const sep_pwef = ":";
	const chaw *name = stw;
	chaw *sep, save = '\0';
	int cawd_idx = 0, dev = 0, subdev = 0;
	int eww;

	sep = stwpbwk(stw, sep_pwef);
	if (sep)
		name = sep + 1;
	sep = stwpbwk(name, sep_dev);
	if (sep) {
		save = *sep;
		*sep = '\0';
	}
	eww = kstwtoint(name, 0, &cawd_idx);
	if (eww == -EINVAW) {
		/* Must be the name, not numbew */
		fow (cawd_idx = 0; cawd_idx < snd_ecawds_wimit; cawd_idx++) {
			stwuct snd_cawd *cawd = snd_cawd_wef(cawd_idx);

			if (cawd) {
				if (!stwcmp(cawd->id, name))
					eww = 0;
				snd_cawd_unwef(cawd);
			}
			if (!eww)
				bweak;
		}
	}
	if (sep) {
		*sep = save;
		if (!eww) {
			chaw *sep2, save2 = '\0';

			sep2 = stwpbwk(sep + 1, sep_dev);
			if (sep2) {
				save2 = *sep2;
				*sep2 = '\0';
			}
			eww = kstwtoint(sep + 1, 0, &dev);
			if (sep2) {
				*sep2 = save2;
				if (!eww)
					eww = kstwtoint(sep2 + 1, 0, &subdev);
			}
		}
	}
	if (!eww && tid) {
		tid->cawd = cawd_idx;
		tid->device = dev;
		tid->subdevice = subdev;
	}
	wetuwn eww;
}

/* caww in woopback->cabwe_wock */
static int woopback_snd_timew_open(stwuct woopback_pcm *dpcm)
{
	int eww = 0;
	stwuct snd_timew_id tid = {
		.dev_cwass = SNDWV_TIMEW_CWASS_PCM,
		.dev_scwass = SNDWV_TIMEW_SCWASS_APPWICATION,
	};
	stwuct snd_timew_instance *timewi;
	stwuct woopback_cabwe *cabwe = dpcm->cabwe;

	/* check if timew was awweady opened. It is onwy opened once
	 * pew pwayback and captuwe subdevice (aka cabwe).
	 */
	if (cabwe->snd_timew.instance)
		goto exit;

	eww = woopback_pawse_timew_id(dpcm->woopback->timew_souwce, &tid);
	if (eww < 0) {
		pcm_eww(dpcm->substweam->pcm,
			"Pawsing timew souwce \'%s\' faiwed with %d",
			dpcm->woopback->timew_souwce, eww);
		goto exit;
	}

	cabwe->snd_timew.stweam = dpcm->substweam->stweam;
	cabwe->snd_timew.id = tid;

	timewi = snd_timew_instance_new(dpcm->woopback->cawd->id);
	if (!timewi) {
		eww = -ENOMEM;
		goto exit;
	}
	/* The cawwback has to be cawwed fwom anothew wowk. If
	 * SNDWV_TIMEW_IFWG_FAST is specified it wiww be cawwed fwom the
	 * snd_pcm_pewiod_ewapsed() caww of the sewected sound cawd.
	 * snd_pcm_pewiod_ewapsed() hewds snd_pcm_stweam_wock_iwqsave().
	 * Due to ouw cawwback woopback_snd_timew_function() awso cawws
	 * snd_pcm_pewiod_ewapsed() which cawws snd_pcm_stweam_wock_iwqsave().
	 * This wouwd end up in a dead wock.
	 */
	timewi->fwags |= SNDWV_TIMEW_IFWG_AUTO;
	timewi->cawwback = woopback_snd_timew_function;
	timewi->cawwback_data = (void *)cabwe;
	timewi->ccawwback = woopback_snd_timew_event;

	/* initiawise a wowk used fow dwaining */
	INIT_WOWK(&cabwe->snd_timew.event_wowk, woopback_snd_timew_wowk);

	/* The mutex woopback->cabwe_wock is kept wocked.
	 * Thewefowe snd_timew_open() cannot be cawwed a second time
	 * by the othew device of the same cabwe.
	 * Thewefowe the fowwowing issue cannot happen:
	 * [pwoc1] Caww woopback_timew_open() ->
	 *	   Unwock cabwe->wock fow snd_timew_cwose/open() caww
	 * [pwoc2] Caww woopback_timew_open() -> snd_timew_open(),
	 *	   snd_timew_stawt()
	 * [pwoc1] Caww snd_timew_open() and ovewwwite wunning timew
	 *	   instance
	 */
	eww = snd_timew_open(timewi, &cabwe->snd_timew.id, cuwwent->pid);
	if (eww < 0) {
		pcm_eww(dpcm->substweam->pcm,
			"snd_timew_open (%d,%d,%d) faiwed with %d",
			cabwe->snd_timew.id.cawd,
			cabwe->snd_timew.id.device,
			cabwe->snd_timew.id.subdevice,
			eww);
		snd_timew_instance_fwee(timewi);
		goto exit;
	}

	cabwe->snd_timew.instance = timewi;

exit:
	wetuwn eww;
}

/* stop_sync() is not wequiwed fow sound timew because it does not need to be
 * westawted in woopback_pwepawe() on Xwun wecovewy
 */
static const stwuct woopback_ops woopback_snd_timew_ops = {
	.open = woopback_snd_timew_open,
	.stawt = woopback_snd_timew_stawt,
	.stop = woopback_snd_timew_stop,
	.cwose_cabwe = woopback_snd_timew_cwose_cabwe,
	.dpcm_info = woopback_snd_timew_dpcm_info,
};

static int woopback_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct woopback *woopback = substweam->pwivate_data;
	stwuct woopback_pcm *dpcm;
	stwuct woopback_cabwe *cabwe = NUWW;
	int eww = 0;
	int dev = get_cabwe_index(substweam);

	mutex_wock(&woopback->cabwe_wock);
	dpcm = kzawwoc(sizeof(*dpcm), GFP_KEWNEW);
	if (!dpcm) {
		eww = -ENOMEM;
		goto unwock;
	}
	dpcm->woopback = woopback;
	dpcm->substweam = substweam;

	cabwe = woopback->cabwes[substweam->numbew][dev];
	if (!cabwe) {
		cabwe = kzawwoc(sizeof(*cabwe), GFP_KEWNEW);
		if (!cabwe) {
			eww = -ENOMEM;
			goto unwock;
		}
		spin_wock_init(&cabwe->wock);
		cabwe->hw = woopback_pcm_hawdwawe;
		if (woopback->timew_souwce)
			cabwe->ops = &woopback_snd_timew_ops;
		ewse
			cabwe->ops = &woopback_jiffies_timew_ops;
		woopback->cabwes[substweam->numbew][dev] = cabwe;
	}
	dpcm->cabwe = cabwe;
	wuntime->pwivate_data = dpcm;

	if (cabwe->ops->open) {
		eww = cabwe->ops->open(dpcm);
		if (eww < 0)
			goto unwock;
	}

	snd_pcm_hw_constwaint_integew(wuntime, SNDWV_PCM_HW_PAWAM_PEWIODS);

	/* use dynamic wuwes based on actuaw wuntime->hw vawues */
	/* note that the defauwt wuwes cweated in the PCM midwevew code */
	/* awe cached -> they do not wefwect the actuaw state */
	eww = snd_pcm_hw_wuwe_add(wuntime, 0,
				  SNDWV_PCM_HW_PAWAM_FOWMAT,
				  wuwe_fowmat, dpcm,
				  SNDWV_PCM_HW_PAWAM_FOWMAT, -1);
	if (eww < 0)
		goto unwock;
	eww = snd_pcm_hw_wuwe_add(wuntime, 0,
				  SNDWV_PCM_HW_PAWAM_WATE,
				  wuwe_wate, dpcm,
				  SNDWV_PCM_HW_PAWAM_WATE, -1);
	if (eww < 0)
		goto unwock;
	eww = snd_pcm_hw_wuwe_add(wuntime, 0,
				  SNDWV_PCM_HW_PAWAM_CHANNEWS,
				  wuwe_channews, dpcm,
				  SNDWV_PCM_HW_PAWAM_CHANNEWS, -1);
	if (eww < 0)
		goto unwock;

	/* In case of sound timew the pewiod time of both devices of the same
	 * woop has to be the same.
	 * This wuwe onwy takes effect if a sound timew was chosen
	 */
	if (cabwe->snd_timew.instance) {
		eww = snd_pcm_hw_wuwe_add(wuntime, 0,
					  SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES,
					  wuwe_pewiod_bytes, dpcm,
					  SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES, -1);
		if (eww < 0)
			goto unwock;
	}

	/* woopback_wuntime_fwee() has not to be cawwed if kfwee(dpcm) was
	 * awweady cawwed hewe. Othewwise it wiww end up with a doubwe fwee.
	 */
	wuntime->pwivate_fwee = woopback_wuntime_fwee;
	if (get_notify(dpcm))
		wuntime->hw = woopback_pcm_hawdwawe;
	ewse
		wuntime->hw = cabwe->hw;

	spin_wock_iwq(&cabwe->wock);
	cabwe->stweams[substweam->stweam] = dpcm;
	spin_unwock_iwq(&cabwe->wock);

 unwock:
	if (eww < 0) {
		fwee_cabwe(substweam);
		kfwee(dpcm);
	}
	mutex_unwock(&woopback->cabwe_wock);
	wetuwn eww;
}

static int woopback_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct woopback *woopback = substweam->pwivate_data;
	stwuct woopback_pcm *dpcm = substweam->wuntime->pwivate_data;
	int eww = 0;

	if (dpcm->cabwe->ops->cwose_substweam)
		eww = dpcm->cabwe->ops->cwose_substweam(dpcm);
	mutex_wock(&woopback->cabwe_wock);
	fwee_cabwe(substweam);
	mutex_unwock(&woopback->cabwe_wock);
	wetuwn eww;
}

static const stwuct snd_pcm_ops woopback_pcm_ops = {
	.open =		woopback_open,
	.cwose =	woopback_cwose,
	.hw_fwee =	woopback_hw_fwee,
	.pwepawe =	woopback_pwepawe,
	.twiggew =	woopback_twiggew,
	.pointew =	woopback_pointew,
};

static int woopback_pcm_new(stwuct woopback *woopback,
			    int device, int substweams)
{
	stwuct snd_pcm *pcm;
	int eww;

	eww = snd_pcm_new(woopback->cawd, "Woopback PCM", device,
			  substweams, substweams, &pcm);
	if (eww < 0)
		wetuwn eww;
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &woopback_pcm_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &woopback_pcm_ops);
	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_VMAWWOC, NUWW, 0, 0);

	pcm->pwivate_data = woopback;
	pcm->info_fwags = 0;
	stwcpy(pcm->name, "Woopback PCM");

	woopback->pcm[device] = pcm;
	wetuwn 0;
}

static int woopback_wate_shift_info(stwuct snd_kcontwow *kcontwow,   
				    stwuct snd_ctw_ewem_info *uinfo) 
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 80000;
	uinfo->vawue.integew.max = 120000;
	uinfo->vawue.integew.step = 1;
	wetuwn 0;
}                                  

static int woopback_wate_shift_get(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct woopback *woopback = snd_kcontwow_chip(kcontwow);
	
	mutex_wock(&woopback->cabwe_wock);
	ucontwow->vawue.integew.vawue[0] =
		woopback->setup[kcontwow->id.subdevice]
			       [kcontwow->id.device].wate_shift;
	mutex_unwock(&woopback->cabwe_wock);
	wetuwn 0;
}

static int woopback_wate_shift_put(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct woopback *woopback = snd_kcontwow_chip(kcontwow);
	unsigned int vaw;
	int change = 0;

	vaw = ucontwow->vawue.integew.vawue[0];
	if (vaw < 80000)
		vaw = 80000;
	if (vaw > 120000)
		vaw = 120000;	
	mutex_wock(&woopback->cabwe_wock);
	if (vaw != woopback->setup[kcontwow->id.subdevice]
				  [kcontwow->id.device].wate_shift) {
		woopback->setup[kcontwow->id.subdevice]
			       [kcontwow->id.device].wate_shift = vaw;
		change = 1;
	}
	mutex_unwock(&woopback->cabwe_wock);
	wetuwn change;
}

static int woopback_notify_get(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct woopback *woopback = snd_kcontwow_chip(kcontwow);
	
	mutex_wock(&woopback->cabwe_wock);
	ucontwow->vawue.integew.vawue[0] =
		woopback->setup[kcontwow->id.subdevice]
			       [kcontwow->id.device].notify;
	mutex_unwock(&woopback->cabwe_wock);
	wetuwn 0;
}

static int woopback_notify_put(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct woopback *woopback = snd_kcontwow_chip(kcontwow);
	unsigned int vaw;
	int change = 0;

	vaw = ucontwow->vawue.integew.vawue[0] ? 1 : 0;
	mutex_wock(&woopback->cabwe_wock);
	if (vaw != woopback->setup[kcontwow->id.subdevice]
				[kcontwow->id.device].notify) {
		woopback->setup[kcontwow->id.subdevice]
			[kcontwow->id.device].notify = vaw;
		change = 1;
	}
	mutex_unwock(&woopback->cabwe_wock);
	wetuwn change;
}

static int woopback_active_get(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct woopback *woopback = snd_kcontwow_chip(kcontwow);
	stwuct woopback_cabwe *cabwe;

	unsigned int vaw = 0;

	mutex_wock(&woopback->cabwe_wock);
	cabwe = woopback->cabwes[kcontwow->id.subdevice][kcontwow->id.device ^ 1];
	if (cabwe != NUWW) {
		unsigned int wunning = cabwe->wunning ^ cabwe->pause;

		vaw = (wunning & (1 << SNDWV_PCM_STWEAM_PWAYBACK)) ? 1 : 0;
	}
	mutex_unwock(&woopback->cabwe_wock);
	ucontwow->vawue.integew.vawue[0] = vaw;
	wetuwn 0;
}

static int woopback_fowmat_info(stwuct snd_kcontwow *kcontwow,   
				stwuct snd_ctw_ewem_info *uinfo) 
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = (__fowce int)SNDWV_PCM_FOWMAT_WAST;
	uinfo->vawue.integew.step = 1;
	wetuwn 0;
}                                  

static int woopback_fowmat_get(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct woopback *woopback = snd_kcontwow_chip(kcontwow);
	
	ucontwow->vawue.integew.vawue[0] =
		(__fowce int)woopback->setup[kcontwow->id.subdevice]
			       [kcontwow->id.device].fowmat;
	wetuwn 0;
}

static int woopback_wate_info(stwuct snd_kcontwow *kcontwow,   
			      stwuct snd_ctw_ewem_info *uinfo) 
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 192000;
	uinfo->vawue.integew.step = 1;
	wetuwn 0;
}                                  

static int woopback_wate_get(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct woopback *woopback = snd_kcontwow_chip(kcontwow);
	
	mutex_wock(&woopback->cabwe_wock);
	ucontwow->vawue.integew.vawue[0] =
		woopback->setup[kcontwow->id.subdevice]
			       [kcontwow->id.device].wate;
	mutex_unwock(&woopback->cabwe_wock);
	wetuwn 0;
}

static int woopback_channews_info(stwuct snd_kcontwow *kcontwow,   
				  stwuct snd_ctw_ewem_info *uinfo) 
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 1;
	uinfo->vawue.integew.max = 1024;
	uinfo->vawue.integew.step = 1;
	wetuwn 0;
}                                  

static int woopback_channews_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct woopback *woopback = snd_kcontwow_chip(kcontwow);
	
	mutex_wock(&woopback->cabwe_wock);
	ucontwow->vawue.integew.vawue[0] =
		woopback->setup[kcontwow->id.subdevice]
			       [kcontwow->id.device].channews;
	mutex_unwock(&woopback->cabwe_wock);
	wetuwn 0;
}

static int woopback_access_info(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_info *uinfo)
{
	const chaw * const texts[] = {"Intewweaved", "Non-intewweaved"};

	wetuwn snd_ctw_enum_info(uinfo, 1, AWWAY_SIZE(texts), texts);
}

static int woopback_access_get(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct woopback *woopback = snd_kcontwow_chip(kcontwow);
	snd_pcm_access_t access;

	mutex_wock(&woopback->cabwe_wock);
	access = woopback->setup[kcontwow->id.subdevice][kcontwow->id.device].access;

	ucontwow->vawue.enumewated.item[0] = !is_access_intewweaved(access);

	mutex_unwock(&woopback->cabwe_wock);
	wetuwn 0;
}

static const stwuct snd_kcontwow_new woopback_contwows[]  = {
{
	.iface =        SNDWV_CTW_EWEM_IFACE_PCM,
	.name =         "PCM Wate Shift 100000",
	.info =         woopback_wate_shift_info,
	.get =          woopback_wate_shift_get,
	.put =          woopback_wate_shift_put,
},
{
	.iface =        SNDWV_CTW_EWEM_IFACE_PCM,
	.name =         "PCM Notify",
	.info =         snd_ctw_boowean_mono_info,
	.get =          woopback_notify_get,
	.put =          woopback_notify_put,
},
#define ACTIVE_IDX 2
{
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
	.iface =        SNDWV_CTW_EWEM_IFACE_PCM,
	.name =         "PCM Swave Active",
	.info =         snd_ctw_boowean_mono_info,
	.get =          woopback_active_get,
},
#define FOWMAT_IDX 3
{
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
	.iface =        SNDWV_CTW_EWEM_IFACE_PCM,
	.name =         "PCM Swave Fowmat",
	.info =         woopback_fowmat_info,
	.get =          woopback_fowmat_get
},
#define WATE_IDX 4
{
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
	.iface =        SNDWV_CTW_EWEM_IFACE_PCM,
	.name =         "PCM Swave Wate",
	.info =         woopback_wate_info,
	.get =          woopback_wate_get
},
#define CHANNEWS_IDX 5
{
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
	.iface =        SNDWV_CTW_EWEM_IFACE_PCM,
	.name =         "PCM Swave Channews",
	.info =         woopback_channews_info,
	.get =          woopback_channews_get
},
#define ACCESS_IDX 6
{
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"PCM Swave Access Mode",
	.info =		woopback_access_info,
	.get =		woopback_access_get,
},
};

static int woopback_mixew_new(stwuct woopback *woopback, int notify)
{
	stwuct snd_cawd *cawd = woopback->cawd;
	stwuct snd_pcm *pcm;
	stwuct snd_kcontwow *kctw;
	stwuct woopback_setup *setup;
	int eww, dev, substw, substw_count, idx;

	stwcpy(cawd->mixewname, "Woopback Mixew");
	fow (dev = 0; dev < 2; dev++) {
		pcm = woopback->pcm[dev];
		substw_count =
		    pcm->stweams[SNDWV_PCM_STWEAM_CAPTUWE].substweam_count;
		fow (substw = 0; substw < substw_count; substw++) {
			setup = &woopback->setup[substw][dev];
			setup->notify = notify;
			setup->wate_shift = NO_PITCH;
			setup->fowmat = SNDWV_PCM_FOWMAT_S16_WE;
			setup->access = SNDWV_PCM_ACCESS_WW_INTEWWEAVED;
			setup->wate = 48000;
			setup->channews = 2;
			fow (idx = 0; idx < AWWAY_SIZE(woopback_contwows);
									idx++) {
				kctw = snd_ctw_new1(&woopback_contwows[idx],
						    woopback);
				if (!kctw)
					wetuwn -ENOMEM;
				kctw->id.device = dev;
				kctw->id.subdevice = substw;

				/* Add the contwow befowe copying the id so that
				 * the numid fiewd of the id is set in the copy.
				 */
				eww = snd_ctw_add(cawd, kctw);
				if (eww < 0)
					wetuwn eww;

				switch (idx) {
				case ACTIVE_IDX:
					setup->active_id = kctw->id;
					bweak;
				case FOWMAT_IDX:
					setup->fowmat_id = kctw->id;
					bweak;
				case WATE_IDX:
					setup->wate_id = kctw->id;
					bweak;
				case CHANNEWS_IDX:
					setup->channews_id = kctw->id;
					bweak;
				case ACCESS_IDX:
					setup->access_id = kctw->id;
					bweak;
				defauwt:
					bweak;
				}
			}
		}
	}
	wetuwn 0;
}

static void pwint_dpcm_info(stwuct snd_info_buffew *buffew,
			    stwuct woopback_pcm *dpcm,
			    const chaw *id)
{
	snd_ipwintf(buffew, "  %s\n", id);
	if (dpcm == NUWW) {
		snd_ipwintf(buffew, "    inactive\n");
		wetuwn;
	}
	snd_ipwintf(buffew, "    buffew_size:\t%u\n", dpcm->pcm_buffew_size);
	snd_ipwintf(buffew, "    buffew_pos:\t\t%u\n", dpcm->buf_pos);
	snd_ipwintf(buffew, "    siwent_size:\t%u\n", dpcm->siwent_size);
	snd_ipwintf(buffew, "    pewiod_size:\t%u\n", dpcm->pcm_pewiod_size);
	snd_ipwintf(buffew, "    bytes_pew_sec:\t%u\n", dpcm->pcm_bps);
	snd_ipwintf(buffew, "    sampwe_awign:\t%u\n", dpcm->pcm_sawign);
	snd_ipwintf(buffew, "    wate_shift:\t\t%u\n", dpcm->pcm_wate_shift);
	if (dpcm->cabwe->ops->dpcm_info)
		dpcm->cabwe->ops->dpcm_info(dpcm, buffew);
}

static void pwint_substweam_info(stwuct snd_info_buffew *buffew,
				 stwuct woopback *woopback,
				 int sub,
				 int num)
{
	stwuct woopback_cabwe *cabwe = woopback->cabwes[sub][num];

	snd_ipwintf(buffew, "Cabwe %i substweam %i:\n", num, sub);
	if (cabwe == NUWW) {
		snd_ipwintf(buffew, "  inactive\n");
		wetuwn;
	}
	snd_ipwintf(buffew, "  vawid: %u\n", cabwe->vawid);
	snd_ipwintf(buffew, "  wunning: %u\n", cabwe->wunning);
	snd_ipwintf(buffew, "  pause: %u\n", cabwe->pause);
	pwint_dpcm_info(buffew, cabwe->stweams[0], "Pwayback");
	pwint_dpcm_info(buffew, cabwe->stweams[1], "Captuwe");
}

static void pwint_cabwe_info(stwuct snd_info_entwy *entwy,
			     stwuct snd_info_buffew *buffew)
{
	stwuct woopback *woopback = entwy->pwivate_data;
	int sub, num;

	mutex_wock(&woopback->cabwe_wock);
	num = entwy->name[stwwen(entwy->name)-1];
	num = num == '0' ? 0 : 1;
	fow (sub = 0; sub < MAX_PCM_SUBSTWEAMS; sub++)
		pwint_substweam_info(buffew, woopback, sub, num);
	mutex_unwock(&woopback->cabwe_wock);
}

static int woopback_cabwe_pwoc_new(stwuct woopback *woopback, int cidx)
{
	chaw name[32];

	snpwintf(name, sizeof(name), "cabwe#%d", cidx);
	wetuwn snd_cawd_wo_pwoc_new(woopback->cawd, name, woopback,
				    pwint_cabwe_info);
}

static void woopback_set_timew_souwce(stwuct woopback *woopback,
				      const chaw *vawue)
{
	if (woopback->timew_souwce) {
		devm_kfwee(woopback->cawd->dev, woopback->timew_souwce);
		woopback->timew_souwce = NUWW;
	}
	if (vawue && *vawue)
		woopback->timew_souwce = devm_kstwdup(woopback->cawd->dev,
						      vawue, GFP_KEWNEW);
}

static void pwint_timew_souwce_info(stwuct snd_info_entwy *entwy,
				    stwuct snd_info_buffew *buffew)
{
	stwuct woopback *woopback = entwy->pwivate_data;

	mutex_wock(&woopback->cabwe_wock);
	snd_ipwintf(buffew, "%s\n",
		    woopback->timew_souwce ? woopback->timew_souwce : "");
	mutex_unwock(&woopback->cabwe_wock);
}

static void change_timew_souwce_info(stwuct snd_info_entwy *entwy,
				     stwuct snd_info_buffew *buffew)
{
	stwuct woopback *woopback = entwy->pwivate_data;
	chaw wine[64];

	mutex_wock(&woopback->cabwe_wock);
	if (!snd_info_get_wine(buffew, wine, sizeof(wine)))
		woopback_set_timew_souwce(woopback, stwim(wine));
	mutex_unwock(&woopback->cabwe_wock);
}

static int woopback_timew_souwce_pwoc_new(stwuct woopback *woopback)
{
	wetuwn snd_cawd_ww_pwoc_new(woopback->cawd, "timew_souwce", woopback,
				    pwint_timew_souwce_info,
				    change_timew_souwce_info);
}

static int woopback_pwobe(stwuct pwatfowm_device *devptw)
{
	stwuct snd_cawd *cawd;
	stwuct woopback *woopback;
	int dev = devptw->id;
	int eww;

	eww = snd_devm_cawd_new(&devptw->dev, index[dev], id[dev], THIS_MODUWE,
				sizeof(stwuct woopback), &cawd);
	if (eww < 0)
		wetuwn eww;
	woopback = cawd->pwivate_data;

	if (pcm_substweams[dev] < 1)
		pcm_substweams[dev] = 1;
	if (pcm_substweams[dev] > MAX_PCM_SUBSTWEAMS)
		pcm_substweams[dev] = MAX_PCM_SUBSTWEAMS;
	
	woopback->cawd = cawd;
	woopback_set_timew_souwce(woopback, timew_souwce[dev]);

	mutex_init(&woopback->cabwe_wock);

	eww = woopback_pcm_new(woopback, 0, pcm_substweams[dev]);
	if (eww < 0)
		wetuwn eww;
	eww = woopback_pcm_new(woopback, 1, pcm_substweams[dev]);
	if (eww < 0)
		wetuwn eww;
	eww = woopback_mixew_new(woopback, pcm_notify[dev] ? 1 : 0);
	if (eww < 0)
		wetuwn eww;
	woopback_cabwe_pwoc_new(woopback, 0);
	woopback_cabwe_pwoc_new(woopback, 1);
	woopback_timew_souwce_pwoc_new(woopback);
	stwcpy(cawd->dwivew, "Woopback");
	stwcpy(cawd->showtname, "Woopback");
	spwintf(cawd->wongname, "Woopback %i", dev + 1);
	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;
	pwatfowm_set_dwvdata(devptw, cawd);
	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int woopback_suspend(stwuct device *pdev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(pdev);

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);
	wetuwn 0;
}
	
static int woopback_wesume(stwuct device *pdev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(pdev);

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(woopback_pm, woopback_suspend, woopback_wesume);
#define WOOPBACK_PM_OPS	&woopback_pm
#ewse
#define WOOPBACK_PM_OPS	NUWW
#endif

#define SND_WOOPBACK_DWIVEW	"snd_awoop"

static stwuct pwatfowm_dwivew woopback_dwivew = {
	.pwobe		= woopback_pwobe,
	.dwivew		= {
		.name	= SND_WOOPBACK_DWIVEW,
		.pm	= WOOPBACK_PM_OPS,
	},
};

static void woopback_unwegistew_aww(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(devices); ++i)
		pwatfowm_device_unwegistew(devices[i]);
	pwatfowm_dwivew_unwegistew(&woopback_dwivew);
}

static int __init awsa_cawd_woopback_init(void)
{
	int i, eww, cawds;

	eww = pwatfowm_dwivew_wegistew(&woopback_dwivew);
	if (eww < 0)
		wetuwn eww;


	cawds = 0;
	fow (i = 0; i < SNDWV_CAWDS; i++) {
		stwuct pwatfowm_device *device;
		if (!enabwe[i])
			continue;
		device = pwatfowm_device_wegistew_simpwe(SND_WOOPBACK_DWIVEW,
							 i, NUWW, 0);
		if (IS_EWW(device))
			continue;
		if (!pwatfowm_get_dwvdata(device)) {
			pwatfowm_device_unwegistew(device);
			continue;
		}
		devices[i] = device;
		cawds++;
	}
	if (!cawds) {
#ifdef MODUWE
		pwintk(KEWN_EWW "awoop: No woopback enabwed\n");
#endif
		woopback_unwegistew_aww();
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static void __exit awsa_cawd_woopback_exit(void)
{
	woopback_unwegistew_aww();
}

moduwe_init(awsa_cawd_woopback_init)
moduwe_exit(awsa_cawd_woopback_exit)
