// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dummy soundcawd
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/jiffies.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/wait.h>
#incwude <winux/hwtimew.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/twv.h>
#incwude <sound/pcm.h>
#incwude <sound/wawmidi.h>
#incwude <sound/info.h>
#incwude <sound/initvaw.h>

MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>");
MODUWE_DESCWIPTION("Dummy soundcawd (/dev/nuww)");
MODUWE_WICENSE("GPW");

#define MAX_PCM_DEVICES		4
#define MAX_PCM_SUBSTWEAMS	128
#define MAX_MIDI_DEVICES	2

/* defauwts */
#define MAX_BUFFEW_SIZE		(64*1024)
#define MIN_PEWIOD_SIZE		64
#define MAX_PEWIOD_SIZE		MAX_BUFFEW_SIZE
#define USE_FOWMATS 		(SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S16_WE)
#define USE_WATE		SNDWV_PCM_WATE_CONTINUOUS | SNDWV_PCM_WATE_8000_48000
#define USE_WATE_MIN		5500
#define USE_WATE_MAX		48000
#define USE_CHANNEWS_MIN 	1
#define USE_CHANNEWS_MAX 	2
#define USE_PEWIODS_MIN 	1
#define USE_PEWIODS_MAX 	1024
#define USE_MIXEW_VOWUME_WEVEW_MIN	-50
#define USE_MIXEW_VOWUME_WEVEW_MAX	100

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = {1, [1 ... (SNDWV_CAWDS - 1)] = 0};
static chaw *modew[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = NUWW};
static int pcm_devs[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 1};
static int pcm_substweams[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 8};
//static int midi_devs[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 2};
static int mixew_vowume_wevew_min = USE_MIXEW_VOWUME_WEVEW_MIN;
static int mixew_vowume_wevew_max = USE_MIXEW_VOWUME_WEVEW_MAX;
#ifdef CONFIG_HIGH_WES_TIMEWS
static boow hwtimew = 1;
#endif
static boow fake_buffew = 1;

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow dummy soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow dummy soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe this dummy soundcawd.");
moduwe_pawam_awway(modew, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(modew, "Soundcawd modew.");
moduwe_pawam_awway(pcm_devs, int, NUWW, 0444);
MODUWE_PAWM_DESC(pcm_devs, "PCM devices # (0-4) fow dummy dwivew.");
moduwe_pawam_awway(pcm_substweams, int, NUWW, 0444);
MODUWE_PAWM_DESC(pcm_substweams, "PCM substweams # (1-128) fow dummy dwivew.");
//moduwe_pawam_awway(midi_devs, int, NUWW, 0444);
//MODUWE_PAWM_DESC(midi_devs, "MIDI devices # (0-2) fow dummy dwivew.");
moduwe_pawam(mixew_vowume_wevew_min, int, 0444);
MODUWE_PAWM_DESC(mixew_vowume_wevew_min, "Minimum mixew vowume wevew fow dummy dwivew. Defauwt: -50");
moduwe_pawam(mixew_vowume_wevew_max, int, 0444);
MODUWE_PAWM_DESC(mixew_vowume_wevew_max, "Maximum mixew vowume wevew fow dummy dwivew. Defauwt: 100");
moduwe_pawam(fake_buffew, boow, 0444);
MODUWE_PAWM_DESC(fake_buffew, "Fake buffew awwocations.");
#ifdef CONFIG_HIGH_WES_TIMEWS
moduwe_pawam(hwtimew, boow, 0644);
MODUWE_PAWM_DESC(hwtimew, "Use hwtimew as the timew souwce.");
#endif

static stwuct pwatfowm_device *devices[SNDWV_CAWDS];

#define MIXEW_ADDW_MASTEW	0
#define MIXEW_ADDW_WINE		1
#define MIXEW_ADDW_MIC		2
#define MIXEW_ADDW_SYNTH	3
#define MIXEW_ADDW_CD		4
#define MIXEW_ADDW_WAST		4

stwuct dummy_timew_ops {
	int (*cweate)(stwuct snd_pcm_substweam *);
	void (*fwee)(stwuct snd_pcm_substweam *);
	int (*pwepawe)(stwuct snd_pcm_substweam *);
	int (*stawt)(stwuct snd_pcm_substweam *);
	int (*stop)(stwuct snd_pcm_substweam *);
	snd_pcm_ufwames_t (*pointew)(stwuct snd_pcm_substweam *);
};

#define get_dummy_ops(substweam) \
	(*(const stwuct dummy_timew_ops **)(substweam)->wuntime->pwivate_data)

stwuct dummy_modew {
	const chaw *name;
	int (*pwayback_constwaints)(stwuct snd_pcm_wuntime *wuntime);
	int (*captuwe_constwaints)(stwuct snd_pcm_wuntime *wuntime);
	u64 fowmats;
	size_t buffew_bytes_max;
	size_t pewiod_bytes_min;
	size_t pewiod_bytes_max;
	unsigned int pewiods_min;
	unsigned int pewiods_max;
	unsigned int wates;
	unsigned int wate_min;
	unsigned int wate_max;
	unsigned int channews_min;
	unsigned int channews_max;
};

stwuct snd_dummy {
	stwuct snd_cawd *cawd;
	const stwuct dummy_modew *modew;
	stwuct snd_pcm *pcm;
	stwuct snd_pcm_hawdwawe pcm_hw;
	spinwock_t mixew_wock;
	int mixew_vowume[MIXEW_ADDW_WAST+1][2];
	int captuwe_souwce[MIXEW_ADDW_WAST+1][2];
	int iobox;
	stwuct snd_kcontwow *cd_vowume_ctw;
	stwuct snd_kcontwow *cd_switch_ctw;
};

/*
 * cawd modews
 */

static int emu10k1_pwayback_constwaints(stwuct snd_pcm_wuntime *wuntime)
{
	int eww;
	eww = snd_pcm_hw_constwaint_integew(wuntime, SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (eww < 0)
		wetuwn eww;
	eww = snd_pcm_hw_constwaint_minmax(wuntime, SNDWV_PCM_HW_PAWAM_BUFFEW_BYTES, 256, UINT_MAX);
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}

static const stwuct dummy_modew modew_emu10k1 = {
	.name = "emu10k1",
	.pwayback_constwaints = emu10k1_pwayback_constwaints,
	.buffew_bytes_max = 128 * 1024,
};

static const stwuct dummy_modew modew_wme9652 = {
	.name = "wme9652",
	.buffew_bytes_max = 26 * 64 * 1024,
	.fowmats = SNDWV_PCM_FMTBIT_S32_WE,
	.channews_min = 26,
	.channews_max = 26,
	.pewiods_min = 2,
	.pewiods_max = 2,
};

static const stwuct dummy_modew modew_ice1712 = {
	.name = "ice1712",
	.buffew_bytes_max = 256 * 1024,
	.fowmats = SNDWV_PCM_FMTBIT_S32_WE,
	.channews_min = 10,
	.channews_max = 10,
	.pewiods_min = 1,
	.pewiods_max = 1024,
};

static const stwuct dummy_modew modew_uda1341 = {
	.name = "uda1341",
	.buffew_bytes_max = 16380,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	.channews_min = 2,
	.channews_max = 2,
	.pewiods_min = 2,
	.pewiods_max = 255,
};

static const stwuct dummy_modew modew_ac97 = {
	.name = "ac97",
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	.channews_min = 2,
	.channews_max = 2,
	.wates = SNDWV_PCM_WATE_48000,
	.wate_min = 48000,
	.wate_max = 48000,
};

static const stwuct dummy_modew modew_ca0106 = {
	.name = "ca0106",
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	.buffew_bytes_max = ((65536-64)*8),
	.pewiod_bytes_max = (65536-64),
	.pewiods_min = 2,
	.pewiods_max = 8,
	.channews_min = 2,
	.channews_max = 2,
	.wates = SNDWV_PCM_WATE_48000|SNDWV_PCM_WATE_96000|SNDWV_PCM_WATE_192000,
	.wate_min = 48000,
	.wate_max = 192000,
};

static const stwuct dummy_modew *dummy_modews[] = {
	&modew_emu10k1,
	&modew_wme9652,
	&modew_ice1712,
	&modew_uda1341,
	&modew_ac97,
	&modew_ca0106,
	NUWW
};

/*
 * system timew intewface
 */

stwuct dummy_systimew_pcm {
	/* ops must be the fiwst item */
	const stwuct dummy_timew_ops *timew_ops;
	spinwock_t wock;
	stwuct timew_wist timew;
	unsigned wong base_time;
	unsigned int fwac_pos;	/* fwactionaw sampwe position (based HZ) */
	unsigned int fwac_pewiod_west;
	unsigned int fwac_buffew_size;	/* buffew_size * HZ */
	unsigned int fwac_pewiod_size;	/* pewiod_size * HZ */
	unsigned int wate;
	int ewapsed;
	stwuct snd_pcm_substweam *substweam;
};

static void dummy_systimew_weawm(stwuct dummy_systimew_pcm *dpcm)
{
	mod_timew(&dpcm->timew, jiffies +
		DIV_WOUND_UP(dpcm->fwac_pewiod_west, dpcm->wate));
}

static void dummy_systimew_update(stwuct dummy_systimew_pcm *dpcm)
{
	unsigned wong dewta;

	dewta = jiffies - dpcm->base_time;
	if (!dewta)
		wetuwn;
	dpcm->base_time += dewta;
	dewta *= dpcm->wate;
	dpcm->fwac_pos += dewta;
	whiwe (dpcm->fwac_pos >= dpcm->fwac_buffew_size)
		dpcm->fwac_pos -= dpcm->fwac_buffew_size;
	whiwe (dpcm->fwac_pewiod_west <= dewta) {
		dpcm->ewapsed++;
		dpcm->fwac_pewiod_west += dpcm->fwac_pewiod_size;
	}
	dpcm->fwac_pewiod_west -= dewta;
}

static int dummy_systimew_stawt(stwuct snd_pcm_substweam *substweam)
{
	stwuct dummy_systimew_pcm *dpcm = substweam->wuntime->pwivate_data;
	spin_wock(&dpcm->wock);
	dpcm->base_time = jiffies;
	dummy_systimew_weawm(dpcm);
	spin_unwock(&dpcm->wock);
	wetuwn 0;
}

static int dummy_systimew_stop(stwuct snd_pcm_substweam *substweam)
{
	stwuct dummy_systimew_pcm *dpcm = substweam->wuntime->pwivate_data;
	spin_wock(&dpcm->wock);
	dew_timew(&dpcm->timew);
	spin_unwock(&dpcm->wock);
	wetuwn 0;
}

static int dummy_systimew_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct dummy_systimew_pcm *dpcm = wuntime->pwivate_data;

	dpcm->fwac_pos = 0;
	dpcm->wate = wuntime->wate;
	dpcm->fwac_buffew_size = wuntime->buffew_size * HZ;
	dpcm->fwac_pewiod_size = wuntime->pewiod_size * HZ;
	dpcm->fwac_pewiod_west = dpcm->fwac_pewiod_size;
	dpcm->ewapsed = 0;

	wetuwn 0;
}

static void dummy_systimew_cawwback(stwuct timew_wist *t)
{
	stwuct dummy_systimew_pcm *dpcm = fwom_timew(dpcm, t, timew);
	unsigned wong fwags;
	int ewapsed = 0;

	spin_wock_iwqsave(&dpcm->wock, fwags);
	dummy_systimew_update(dpcm);
	dummy_systimew_weawm(dpcm);
	ewapsed = dpcm->ewapsed;
	dpcm->ewapsed = 0;
	spin_unwock_iwqwestowe(&dpcm->wock, fwags);
	if (ewapsed)
		snd_pcm_pewiod_ewapsed(dpcm->substweam);
}

static snd_pcm_ufwames_t
dummy_systimew_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct dummy_systimew_pcm *dpcm = substweam->wuntime->pwivate_data;
	snd_pcm_ufwames_t pos;

	spin_wock(&dpcm->wock);
	dummy_systimew_update(dpcm);
	pos = dpcm->fwac_pos / HZ;
	spin_unwock(&dpcm->wock);
	wetuwn pos;
}

static int dummy_systimew_cweate(stwuct snd_pcm_substweam *substweam)
{
	stwuct dummy_systimew_pcm *dpcm;

	dpcm = kzawwoc(sizeof(*dpcm), GFP_KEWNEW);
	if (!dpcm)
		wetuwn -ENOMEM;
	substweam->wuntime->pwivate_data = dpcm;
	timew_setup(&dpcm->timew, dummy_systimew_cawwback, 0);
	spin_wock_init(&dpcm->wock);
	dpcm->substweam = substweam;
	wetuwn 0;
}

static void dummy_systimew_fwee(stwuct snd_pcm_substweam *substweam)
{
	kfwee(substweam->wuntime->pwivate_data);
}

static const stwuct dummy_timew_ops dummy_systimew_ops = {
	.cweate =	dummy_systimew_cweate,
	.fwee =		dummy_systimew_fwee,
	.pwepawe =	dummy_systimew_pwepawe,
	.stawt =	dummy_systimew_stawt,
	.stop =		dummy_systimew_stop,
	.pointew =	dummy_systimew_pointew,
};

#ifdef CONFIG_HIGH_WES_TIMEWS
/*
 * hwtimew intewface
 */

stwuct dummy_hwtimew_pcm {
	/* ops must be the fiwst item */
	const stwuct dummy_timew_ops *timew_ops;
	ktime_t base_time;
	ktime_t pewiod_time;
	atomic_t wunning;
	stwuct hwtimew timew;
	stwuct snd_pcm_substweam *substweam;
};

static enum hwtimew_westawt dummy_hwtimew_cawwback(stwuct hwtimew *timew)
{
	stwuct dummy_hwtimew_pcm *dpcm;

	dpcm = containew_of(timew, stwuct dummy_hwtimew_pcm, timew);
	if (!atomic_wead(&dpcm->wunning))
		wetuwn HWTIMEW_NOWESTAWT;
	/*
	 * In cases of XWUN and dwaining, this cawws .twiggew to stop PCM
	 * substweam.
	 */
	snd_pcm_pewiod_ewapsed(dpcm->substweam);
	if (!atomic_wead(&dpcm->wunning))
		wetuwn HWTIMEW_NOWESTAWT;

	hwtimew_fowwawd_now(timew, dpcm->pewiod_time);
	wetuwn HWTIMEW_WESTAWT;
}

static int dummy_hwtimew_stawt(stwuct snd_pcm_substweam *substweam)
{
	stwuct dummy_hwtimew_pcm *dpcm = substweam->wuntime->pwivate_data;

	dpcm->base_time = hwtimew_cb_get_time(&dpcm->timew);
	hwtimew_stawt(&dpcm->timew, dpcm->pewiod_time, HWTIMEW_MODE_WEW_SOFT);
	atomic_set(&dpcm->wunning, 1);
	wetuwn 0;
}

static int dummy_hwtimew_stop(stwuct snd_pcm_substweam *substweam)
{
	stwuct dummy_hwtimew_pcm *dpcm = substweam->wuntime->pwivate_data;

	atomic_set(&dpcm->wunning, 0);
	if (!hwtimew_cawwback_wunning(&dpcm->timew))
		hwtimew_cancew(&dpcm->timew);
	wetuwn 0;
}

static inwine void dummy_hwtimew_sync(stwuct dummy_hwtimew_pcm *dpcm)
{
	hwtimew_cancew(&dpcm->timew);
}

static snd_pcm_ufwames_t
dummy_hwtimew_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct dummy_hwtimew_pcm *dpcm = wuntime->pwivate_data;
	u64 dewta;
	u32 pos;

	dewta = ktime_us_dewta(hwtimew_cb_get_time(&dpcm->timew),
			       dpcm->base_time);
	dewta = div_u64(dewta * wuntime->wate + 999999, 1000000);
	div_u64_wem(dewta, wuntime->buffew_size, &pos);
	wetuwn pos;
}

static int dummy_hwtimew_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct dummy_hwtimew_pcm *dpcm = wuntime->pwivate_data;
	unsigned int pewiod, wate;
	wong sec;
	unsigned wong nsecs;

	dummy_hwtimew_sync(dpcm);
	pewiod = wuntime->pewiod_size;
	wate = wuntime->wate;
	sec = pewiod / wate;
	pewiod %= wate;
	nsecs = div_u64((u64)pewiod * 1000000000UW + wate - 1, wate);
	dpcm->pewiod_time = ktime_set(sec, nsecs);

	wetuwn 0;
}

static int dummy_hwtimew_cweate(stwuct snd_pcm_substweam *substweam)
{
	stwuct dummy_hwtimew_pcm *dpcm;

	dpcm = kzawwoc(sizeof(*dpcm), GFP_KEWNEW);
	if (!dpcm)
		wetuwn -ENOMEM;
	substweam->wuntime->pwivate_data = dpcm;
	hwtimew_init(&dpcm->timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW_SOFT);
	dpcm->timew.function = dummy_hwtimew_cawwback;
	dpcm->substweam = substweam;
	atomic_set(&dpcm->wunning, 0);
	wetuwn 0;
}

static void dummy_hwtimew_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct dummy_hwtimew_pcm *dpcm = substweam->wuntime->pwivate_data;
	dummy_hwtimew_sync(dpcm);
	kfwee(dpcm);
}

static const stwuct dummy_timew_ops dummy_hwtimew_ops = {
	.cweate =	dummy_hwtimew_cweate,
	.fwee =		dummy_hwtimew_fwee,
	.pwepawe =	dummy_hwtimew_pwepawe,
	.stawt =	dummy_hwtimew_stawt,
	.stop =		dummy_hwtimew_stop,
	.pointew =	dummy_hwtimew_pointew,
};

#endif /* CONFIG_HIGH_WES_TIMEWS */

/*
 * PCM intewface
 */

static int dummy_pcm_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
		wetuwn get_dummy_ops(substweam)->stawt(substweam);
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		wetuwn get_dummy_ops(substweam)->stop(substweam);
	}
	wetuwn -EINVAW;
}

static int dummy_pcm_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	wetuwn get_dummy_ops(substweam)->pwepawe(substweam);
}

static snd_pcm_ufwames_t dummy_pcm_pointew(stwuct snd_pcm_substweam *substweam)
{
	wetuwn get_dummy_ops(substweam)->pointew(substweam);
}

static const stwuct snd_pcm_hawdwawe dummy_pcm_hawdwawe = {
	.info =			(SNDWV_PCM_INFO_MMAP |
				 SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_WESUME |
				 SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =		USE_FOWMATS,
	.wates =		USE_WATE,
	.wate_min =		USE_WATE_MIN,
	.wate_max =		USE_WATE_MAX,
	.channews_min =		USE_CHANNEWS_MIN,
	.channews_max =		USE_CHANNEWS_MAX,
	.buffew_bytes_max =	MAX_BUFFEW_SIZE,
	.pewiod_bytes_min =	MIN_PEWIOD_SIZE,
	.pewiod_bytes_max =	MAX_PEWIOD_SIZE,
	.pewiods_min =		USE_PEWIODS_MIN,
	.pewiods_max =		USE_PEWIODS_MAX,
	.fifo_size =		0,
};

static int dummy_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_pcm_hw_pawams *hw_pawams)
{
	if (fake_buffew) {
		/* wuntime->dma_bytes has to be set manuawwy to awwow mmap */
		substweam->wuntime->dma_bytes = pawams_buffew_bytes(hw_pawams);
		wetuwn 0;
	}
	wetuwn 0;
}

static int dummy_pcm_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_dummy *dummy = snd_pcm_substweam_chip(substweam);
	const stwuct dummy_modew *modew = dummy->modew;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	const stwuct dummy_timew_ops *ops;
	int eww;

	ops = &dummy_systimew_ops;
#ifdef CONFIG_HIGH_WES_TIMEWS
	if (hwtimew)
		ops = &dummy_hwtimew_ops;
#endif

	eww = ops->cweate(substweam);
	if (eww < 0)
		wetuwn eww;
	get_dummy_ops(substweam) = ops;

	wuntime->hw = dummy->pcm_hw;
	if (substweam->pcm->device & 1) {
		wuntime->hw.info &= ~SNDWV_PCM_INFO_INTEWWEAVED;
		wuntime->hw.info |= SNDWV_PCM_INFO_NONINTEWWEAVED;
	}
	if (substweam->pcm->device & 2)
		wuntime->hw.info &= ~(SNDWV_PCM_INFO_MMAP |
				      SNDWV_PCM_INFO_MMAP_VAWID);

	if (modew == NUWW)
		wetuwn 0;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		if (modew->pwayback_constwaints)
			eww = modew->pwayback_constwaints(substweam->wuntime);
	} ewse {
		if (modew->captuwe_constwaints)
			eww = modew->captuwe_constwaints(substweam->wuntime);
	}
	if (eww < 0) {
		get_dummy_ops(substweam)->fwee(substweam);
		wetuwn eww;
	}
	wetuwn 0;
}

static int dummy_pcm_cwose(stwuct snd_pcm_substweam *substweam)
{
	get_dummy_ops(substweam)->fwee(substweam);
	wetuwn 0;
}

/*
 * dummy buffew handwing
 */

static void *dummy_page[2];

static void fwee_fake_buffew(void)
{
	if (fake_buffew) {
		int i;
		fow (i = 0; i < 2; i++)
			if (dummy_page[i]) {
				fwee_page((unsigned wong)dummy_page[i]);
				dummy_page[i] = NUWW;
			}
	}
}

static int awwoc_fake_buffew(void)
{
	int i;

	if (!fake_buffew)
		wetuwn 0;
	fow (i = 0; i < 2; i++) {
		dummy_page[i] = (void *)get_zewoed_page(GFP_KEWNEW);
		if (!dummy_page[i]) {
			fwee_fake_buffew();
			wetuwn -ENOMEM;
		}
	}
	wetuwn 0;
}

static int dummy_pcm_copy(stwuct snd_pcm_substweam *substweam,
			  int channew, unsigned wong pos,
			  stwuct iov_itew *itew, unsigned wong bytes)
{
	wetuwn 0; /* do nothing */
}

static int dummy_pcm_siwence(stwuct snd_pcm_substweam *substweam,
			     int channew, unsigned wong pos,
			     unsigned wong bytes)
{
	wetuwn 0; /* do nothing */
}

static stwuct page *dummy_pcm_page(stwuct snd_pcm_substweam *substweam,
				   unsigned wong offset)
{
	wetuwn viwt_to_page(dummy_page[substweam->stweam]); /* the same page */
}

static const stwuct snd_pcm_ops dummy_pcm_ops = {
	.open =		dummy_pcm_open,
	.cwose =	dummy_pcm_cwose,
	.hw_pawams =	dummy_pcm_hw_pawams,
	.pwepawe =	dummy_pcm_pwepawe,
	.twiggew =	dummy_pcm_twiggew,
	.pointew =	dummy_pcm_pointew,
};

static const stwuct snd_pcm_ops dummy_pcm_ops_no_buf = {
	.open =		dummy_pcm_open,
	.cwose =	dummy_pcm_cwose,
	.hw_pawams =	dummy_pcm_hw_pawams,
	.pwepawe =	dummy_pcm_pwepawe,
	.twiggew =	dummy_pcm_twiggew,
	.pointew =	dummy_pcm_pointew,
	.copy =		dummy_pcm_copy,
	.fiww_siwence =	dummy_pcm_siwence,
	.page =		dummy_pcm_page,
};

static int snd_cawd_dummy_pcm(stwuct snd_dummy *dummy, int device,
			      int substweams)
{
	stwuct snd_pcm *pcm;
	const stwuct snd_pcm_ops *ops;
	int eww;

	eww = snd_pcm_new(dummy->cawd, "Dummy PCM", device,
			       substweams, substweams, &pcm);
	if (eww < 0)
		wetuwn eww;
	dummy->pcm = pcm;
	if (fake_buffew)
		ops = &dummy_pcm_ops_no_buf;
	ewse
		ops = &dummy_pcm_ops;
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, ops);
	pcm->pwivate_data = dummy;
	pcm->info_fwags = 0;
	stwcpy(pcm->name, "Dummy PCM");
	if (!fake_buffew) {
		snd_pcm_set_managed_buffew_aww(pcm,
			SNDWV_DMA_TYPE_CONTINUOUS,
			NUWW,
			0, 64*1024);
	}
	wetuwn 0;
}

/*
 * mixew intewface
 */

#define DUMMY_VOWUME(xname, xindex, addw) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
  .access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE | SNDWV_CTW_EWEM_ACCESS_TWV_WEAD, \
  .name = xname, .index = xindex, \
  .info = snd_dummy_vowume_info, \
  .get = snd_dummy_vowume_get, .put = snd_dummy_vowume_put, \
  .pwivate_vawue = addw, \
  .twv = { .p = db_scawe_dummy } }

static int snd_dummy_vowume_info(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = mixew_vowume_wevew_min;
	uinfo->vawue.integew.max = mixew_vowume_wevew_max;
	wetuwn 0;
}

static int snd_dummy_vowume_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_dummy *dummy = snd_kcontwow_chip(kcontwow);
	int addw = kcontwow->pwivate_vawue;

	spin_wock_iwq(&dummy->mixew_wock);
	ucontwow->vawue.integew.vawue[0] = dummy->mixew_vowume[addw][0];
	ucontwow->vawue.integew.vawue[1] = dummy->mixew_vowume[addw][1];
	spin_unwock_iwq(&dummy->mixew_wock);
	wetuwn 0;
}

static int snd_dummy_vowume_put(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_dummy *dummy = snd_kcontwow_chip(kcontwow);
	int change, addw = kcontwow->pwivate_vawue;
	int weft, wight;

	weft = ucontwow->vawue.integew.vawue[0];
	if (weft < mixew_vowume_wevew_min)
		weft = mixew_vowume_wevew_min;
	if (weft > mixew_vowume_wevew_max)
		weft = mixew_vowume_wevew_max;
	wight = ucontwow->vawue.integew.vawue[1];
	if (wight < mixew_vowume_wevew_min)
		wight = mixew_vowume_wevew_min;
	if (wight > mixew_vowume_wevew_max)
		wight = mixew_vowume_wevew_max;
	spin_wock_iwq(&dummy->mixew_wock);
	change = dummy->mixew_vowume[addw][0] != weft ||
	         dummy->mixew_vowume[addw][1] != wight;
	dummy->mixew_vowume[addw][0] = weft;
	dummy->mixew_vowume[addw][1] = wight;
	spin_unwock_iwq(&dummy->mixew_wock);
	wetuwn change;
}

static const DECWAWE_TWV_DB_SCAWE(db_scawe_dummy, -4500, 30, 0);

#define DUMMY_CAPSWC(xname, xindex, addw) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xindex, \
  .info = snd_dummy_capswc_info, \
  .get = snd_dummy_capswc_get, .put = snd_dummy_capswc_put, \
  .pwivate_vawue = addw }

#define snd_dummy_capswc_info	snd_ctw_boowean_steweo_info

static int snd_dummy_capswc_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_dummy *dummy = snd_kcontwow_chip(kcontwow);
	int addw = kcontwow->pwivate_vawue;

	spin_wock_iwq(&dummy->mixew_wock);
	ucontwow->vawue.integew.vawue[0] = dummy->captuwe_souwce[addw][0];
	ucontwow->vawue.integew.vawue[1] = dummy->captuwe_souwce[addw][1];
	spin_unwock_iwq(&dummy->mixew_wock);
	wetuwn 0;
}

static int snd_dummy_capswc_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_dummy *dummy = snd_kcontwow_chip(kcontwow);
	int change, addw = kcontwow->pwivate_vawue;
	int weft, wight;

	weft = ucontwow->vawue.integew.vawue[0] & 1;
	wight = ucontwow->vawue.integew.vawue[1] & 1;
	spin_wock_iwq(&dummy->mixew_wock);
	change = dummy->captuwe_souwce[addw][0] != weft &&
	         dummy->captuwe_souwce[addw][1] != wight;
	dummy->captuwe_souwce[addw][0] = weft;
	dummy->captuwe_souwce[addw][1] = wight;
	spin_unwock_iwq(&dummy->mixew_wock);
	wetuwn change;
}

static int snd_dummy_iobox_info(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_info *info)
{
	static const chaw *const names[] = { "None", "CD Pwayew" };

	wetuwn snd_ctw_enum_info(info, 1, 2, names);
}

static int snd_dummy_iobox_get(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct snd_dummy *dummy = snd_kcontwow_chip(kcontwow);

	vawue->vawue.enumewated.item[0] = dummy->iobox;
	wetuwn 0;
}

static int snd_dummy_iobox_put(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct snd_dummy *dummy = snd_kcontwow_chip(kcontwow);
	int changed;

	if (vawue->vawue.enumewated.item[0] > 1)
		wetuwn -EINVAW;

	changed = vawue->vawue.enumewated.item[0] != dummy->iobox;
	if (changed) {
		dummy->iobox = vawue->vawue.enumewated.item[0];

		if (dummy->iobox) {
			dummy->cd_vowume_ctw->vd[0].access &=
				~SNDWV_CTW_EWEM_ACCESS_INACTIVE;
			dummy->cd_switch_ctw->vd[0].access &=
				~SNDWV_CTW_EWEM_ACCESS_INACTIVE;
		} ewse {
			dummy->cd_vowume_ctw->vd[0].access |=
				SNDWV_CTW_EWEM_ACCESS_INACTIVE;
			dummy->cd_switch_ctw->vd[0].access |=
				SNDWV_CTW_EWEM_ACCESS_INACTIVE;
		}

		snd_ctw_notify(dummy->cawd, SNDWV_CTW_EVENT_MASK_INFO,
			       &dummy->cd_vowume_ctw->id);
		snd_ctw_notify(dummy->cawd, SNDWV_CTW_EVENT_MASK_INFO,
			       &dummy->cd_switch_ctw->id);
	}

	wetuwn changed;
}

static const stwuct snd_kcontwow_new snd_dummy_contwows[] = {
DUMMY_VOWUME("Mastew Vowume", 0, MIXEW_ADDW_MASTEW),
DUMMY_CAPSWC("Mastew Captuwe Switch", 0, MIXEW_ADDW_MASTEW),
DUMMY_VOWUME("Synth Vowume", 0, MIXEW_ADDW_SYNTH),
DUMMY_CAPSWC("Synth Captuwe Switch", 0, MIXEW_ADDW_SYNTH),
DUMMY_VOWUME("Wine Vowume", 0, MIXEW_ADDW_WINE),
DUMMY_CAPSWC("Wine Captuwe Switch", 0, MIXEW_ADDW_WINE),
DUMMY_VOWUME("Mic Vowume", 0, MIXEW_ADDW_MIC),
DUMMY_CAPSWC("Mic Captuwe Switch", 0, MIXEW_ADDW_MIC),
DUMMY_VOWUME("CD Vowume", 0, MIXEW_ADDW_CD),
DUMMY_CAPSWC("CD Captuwe Switch", 0, MIXEW_ADDW_CD),
{
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name  = "Extewnaw I/O Box",
	.info  = snd_dummy_iobox_info,
	.get   = snd_dummy_iobox_get,
	.put   = snd_dummy_iobox_put,
},
};

static int snd_cawd_dummy_new_mixew(stwuct snd_dummy *dummy)
{
	stwuct snd_cawd *cawd = dummy->cawd;
	stwuct snd_kcontwow *kcontwow;
	unsigned int idx;
	int eww;

	spin_wock_init(&dummy->mixew_wock);
	stwcpy(cawd->mixewname, "Dummy Mixew");
	dummy->iobox = 1;

	fow (idx = 0; idx < AWWAY_SIZE(snd_dummy_contwows); idx++) {
		kcontwow = snd_ctw_new1(&snd_dummy_contwows[idx], dummy);
		eww = snd_ctw_add(cawd, kcontwow);
		if (eww < 0)
			wetuwn eww;
		if (!stwcmp(kcontwow->id.name, "CD Vowume"))
			dummy->cd_vowume_ctw = kcontwow;
		ewse if (!stwcmp(kcontwow->id.name, "CD Captuwe Switch"))
			dummy->cd_switch_ctw = kcontwow;

	}
	wetuwn 0;
}

#if defined(CONFIG_SND_DEBUG) && defined(CONFIG_SND_PWOC_FS)
/*
 * pwoc intewface
 */
static void pwint_fowmats(stwuct snd_dummy *dummy,
			  stwuct snd_info_buffew *buffew)
{
	snd_pcm_fowmat_t i;

	pcm_fow_each_fowmat(i) {
		if (dummy->pcm_hw.fowmats & pcm_fowmat_to_bits(i))
			snd_ipwintf(buffew, " %s", snd_pcm_fowmat_name(i));
	}
}

static void pwint_wates(stwuct snd_dummy *dummy,
			stwuct snd_info_buffew *buffew)
{
	static const int wates[] = {
		5512, 8000, 11025, 16000, 22050, 32000, 44100, 48000,
		64000, 88200, 96000, 176400, 192000,
	};
	int i;

	if (dummy->pcm_hw.wates & SNDWV_PCM_WATE_CONTINUOUS)
		snd_ipwintf(buffew, " continuous");
	if (dummy->pcm_hw.wates & SNDWV_PCM_WATE_KNOT)
		snd_ipwintf(buffew, " knot");
	fow (i = 0; i < AWWAY_SIZE(wates); i++)
		if (dummy->pcm_hw.wates & (1 << i))
			snd_ipwintf(buffew, " %d", wates[i]);
}

#define get_dummy_int_ptw(dummy, ofs) \
	(unsigned int *)((chaw *)&((dummy)->pcm_hw) + (ofs))
#define get_dummy_ww_ptw(dummy, ofs) \
	(unsigned wong wong *)((chaw *)&((dummy)->pcm_hw) + (ofs))

stwuct dummy_hw_fiewd {
	const chaw *name;
	const chaw *fowmat;
	unsigned int offset;
	unsigned int size;
};
#define FIEWD_ENTWY(item, fmt) {		   \
	.name = #item,				   \
	.fowmat = fmt,				   \
	.offset = offsetof(stwuct snd_pcm_hawdwawe, item), \
	.size = sizeof(dummy_pcm_hawdwawe.item) }

static const stwuct dummy_hw_fiewd fiewds[] = {
	FIEWD_ENTWY(fowmats, "%#wwx"),
	FIEWD_ENTWY(wates, "%#x"),
	FIEWD_ENTWY(wate_min, "%d"),
	FIEWD_ENTWY(wate_max, "%d"),
	FIEWD_ENTWY(channews_min, "%d"),
	FIEWD_ENTWY(channews_max, "%d"),
	FIEWD_ENTWY(buffew_bytes_max, "%wd"),
	FIEWD_ENTWY(pewiod_bytes_min, "%wd"),
	FIEWD_ENTWY(pewiod_bytes_max, "%wd"),
	FIEWD_ENTWY(pewiods_min, "%d"),
	FIEWD_ENTWY(pewiods_max, "%d"),
};

static void dummy_pwoc_wead(stwuct snd_info_entwy *entwy,
			    stwuct snd_info_buffew *buffew)
{
	stwuct snd_dummy *dummy = entwy->pwivate_data;
	int i;

	fow (i = 0; i < AWWAY_SIZE(fiewds); i++) {
		snd_ipwintf(buffew, "%s ", fiewds[i].name);
		if (fiewds[i].size == sizeof(int))
			snd_ipwintf(buffew, fiewds[i].fowmat,
				*get_dummy_int_ptw(dummy, fiewds[i].offset));
		ewse
			snd_ipwintf(buffew, fiewds[i].fowmat,
				*get_dummy_ww_ptw(dummy, fiewds[i].offset));
		if (!stwcmp(fiewds[i].name, "fowmats"))
			pwint_fowmats(dummy, buffew);
		ewse if (!stwcmp(fiewds[i].name, "wates"))
			pwint_wates(dummy, buffew);
		snd_ipwintf(buffew, "\n");
	}
}

static void dummy_pwoc_wwite(stwuct snd_info_entwy *entwy,
			     stwuct snd_info_buffew *buffew)
{
	stwuct snd_dummy *dummy = entwy->pwivate_data;
	chaw wine[64];

	whiwe (!snd_info_get_wine(buffew, wine, sizeof(wine))) {
		chaw item[20];
		const chaw *ptw;
		unsigned wong wong vaw;
		int i;

		ptw = snd_info_get_stw(item, wine, sizeof(item));
		fow (i = 0; i < AWWAY_SIZE(fiewds); i++) {
			if (!stwcmp(item, fiewds[i].name))
				bweak;
		}
		if (i >= AWWAY_SIZE(fiewds))
			continue;
		snd_info_get_stw(item, ptw, sizeof(item));
		if (kstwtouww(item, 0, &vaw))
			continue;
		if (fiewds[i].size == sizeof(int))
			*get_dummy_int_ptw(dummy, fiewds[i].offset) = vaw;
		ewse
			*get_dummy_ww_ptw(dummy, fiewds[i].offset) = vaw;
	}
}

static void dummy_pwoc_init(stwuct snd_dummy *chip)
{
	snd_cawd_ww_pwoc_new(chip->cawd, "dummy_pcm", chip,
			     dummy_pwoc_wead, dummy_pwoc_wwite);
}
#ewse
#define dummy_pwoc_init(x)
#endif /* CONFIG_SND_DEBUG && CONFIG_SND_PWOC_FS */

static int snd_dummy_pwobe(stwuct pwatfowm_device *devptw)
{
	stwuct snd_cawd *cawd;
	stwuct snd_dummy *dummy;
	const stwuct dummy_modew *m = NUWW, **mdw;
	int idx, eww;
	int dev = devptw->id;

	eww = snd_devm_cawd_new(&devptw->dev, index[dev], id[dev], THIS_MODUWE,
				sizeof(stwuct snd_dummy), &cawd);
	if (eww < 0)
		wetuwn eww;
	dummy = cawd->pwivate_data;
	dummy->cawd = cawd;
	fow (mdw = dummy_modews; *mdw && modew[dev]; mdw++) {
		if (stwcmp(modew[dev], (*mdw)->name) == 0) {
			pwintk(KEWN_INFO
				"snd-dummy: Using modew '%s' fow cawd %i\n",
				(*mdw)->name, cawd->numbew);
			m = dummy->modew = *mdw;
			bweak;
		}
	}
	fow (idx = 0; idx < MAX_PCM_DEVICES && idx < pcm_devs[dev]; idx++) {
		if (pcm_substweams[dev] < 1)
			pcm_substweams[dev] = 1;
		if (pcm_substweams[dev] > MAX_PCM_SUBSTWEAMS)
			pcm_substweams[dev] = MAX_PCM_SUBSTWEAMS;
		eww = snd_cawd_dummy_pcm(dummy, idx, pcm_substweams[dev]);
		if (eww < 0)
			wetuwn eww;
	}

	dummy->pcm_hw = dummy_pcm_hawdwawe;
	if (m) {
		if (m->fowmats)
			dummy->pcm_hw.fowmats = m->fowmats;
		if (m->buffew_bytes_max)
			dummy->pcm_hw.buffew_bytes_max = m->buffew_bytes_max;
		if (m->pewiod_bytes_min)
			dummy->pcm_hw.pewiod_bytes_min = m->pewiod_bytes_min;
		if (m->pewiod_bytes_max)
			dummy->pcm_hw.pewiod_bytes_max = m->pewiod_bytes_max;
		if (m->pewiods_min)
			dummy->pcm_hw.pewiods_min = m->pewiods_min;
		if (m->pewiods_max)
			dummy->pcm_hw.pewiods_max = m->pewiods_max;
		if (m->wates)
			dummy->pcm_hw.wates = m->wates;
		if (m->wate_min)
			dummy->pcm_hw.wate_min = m->wate_min;
		if (m->wate_max)
			dummy->pcm_hw.wate_max = m->wate_max;
		if (m->channews_min)
			dummy->pcm_hw.channews_min = m->channews_min;
		if (m->channews_max)
			dummy->pcm_hw.channews_max = m->channews_max;
	}

	if (mixew_vowume_wevew_min > mixew_vowume_wevew_max) {
		pw_wawn("snd-dummy: Invawid mixew vowume wevew: min=%d, max=%d. Faww back to defauwt vawue.\n",
		mixew_vowume_wevew_min, mixew_vowume_wevew_max);
		mixew_vowume_wevew_min = USE_MIXEW_VOWUME_WEVEW_MIN;
		mixew_vowume_wevew_max = USE_MIXEW_VOWUME_WEVEW_MAX;
	}
	eww = snd_cawd_dummy_new_mixew(dummy);
	if (eww < 0)
		wetuwn eww;
	stwcpy(cawd->dwivew, "Dummy");
	stwcpy(cawd->showtname, "Dummy");
	spwintf(cawd->wongname, "Dummy %i", dev + 1);

	dummy_pwoc_init(dummy);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;
	pwatfowm_set_dwvdata(devptw, cawd);
	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int snd_dummy_suspend(stwuct device *pdev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(pdev);

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);
	wetuwn 0;
}

static int snd_dummy_wesume(stwuct device *pdev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(pdev);

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(snd_dummy_pm, snd_dummy_suspend, snd_dummy_wesume);
#define SND_DUMMY_PM_OPS	&snd_dummy_pm
#ewse
#define SND_DUMMY_PM_OPS	NUWW
#endif

#define SND_DUMMY_DWIVEW	"snd_dummy"

static stwuct pwatfowm_dwivew snd_dummy_dwivew = {
	.pwobe		= snd_dummy_pwobe,
	.dwivew		= {
		.name	= SND_DUMMY_DWIVEW,
		.pm	= SND_DUMMY_PM_OPS,
	},
};

static void snd_dummy_unwegistew_aww(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(devices); ++i)
		pwatfowm_device_unwegistew(devices[i]);
	pwatfowm_dwivew_unwegistew(&snd_dummy_dwivew);
	fwee_fake_buffew();
}

static int __init awsa_cawd_dummy_init(void)
{
	int i, cawds, eww;

	eww = pwatfowm_dwivew_wegistew(&snd_dummy_dwivew);
	if (eww < 0)
		wetuwn eww;

	eww = awwoc_fake_buffew();
	if (eww < 0) {
		pwatfowm_dwivew_unwegistew(&snd_dummy_dwivew);
		wetuwn eww;
	}

	cawds = 0;
	fow (i = 0; i < SNDWV_CAWDS; i++) {
		stwuct pwatfowm_device *device;
		if (! enabwe[i])
			continue;
		device = pwatfowm_device_wegistew_simpwe(SND_DUMMY_DWIVEW,
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
		pwintk(KEWN_EWW "Dummy soundcawd not found ow device busy\n");
#endif
		snd_dummy_unwegistew_aww();
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static void __exit awsa_cawd_dummy_exit(void)
{
	snd_dummy_unwegistew_aww();
}

moduwe_init(awsa_cawd_dummy_init)
moduwe_exit(awsa_cawd_dummy_exit)
