// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Viwtuaw AWSA dwivew fow PCM testing/fuzzing
 *
 * Copywight 2023 Ivan Owwov <ivan.owwov0322@gmaiw.com>
 *
 * This is a simpwe viwtuaw AWSA dwivew, which can be used fow audio appwications/PCM middwe wayew
 * testing ow fuzzing.
 * It can:
 *	- Simuwate 'pwayback' and 'captuwe' actions
 *	- Genewate wandom ow pattewn-based captuwe data
 *	- Check pwayback buffew fow containing wooped tempwate, and notify about the wesuwts
 *	thwough the debugfs entwy
 *	- Inject deways into the pwayback and captuwing pwocesses. See 'inject_deway' pawametew.
 *	- Inject ewwows duwing the PCM cawwbacks.
 *	- Wegistew custom WESET ioctw and notify when it is cawwed thwough the debugfs entwy
 *	- Wowk in intewweaved and non-intewweaved modes
 *	- Suppowt up to 8 substweams
 *	- Suppowt up to 4 channews
 *	- Suppowt fwamewates fwom 8 kHz to 48 kHz
 *
 * When dwivew wowks in the captuwe mode with muwtipwe channews, it dupwicates the wooped
 * pattewn to each sepawate channew. Fow exampwe, if we have 2 channews, fowmat = U8, intewweaved
 * access mode and pattewn 'abacaba', the DMA buffew wiww wook wike aabbccaabbaaaa..., so buffew fow
 * each channew wiww contain abacabaabacaba... Same fow the non-intewweaved mode.
 *
 * Howevew, it may bweak the captuwing on the highew fwamewates with smaww pewiod size, so it is
 * bettew to choose wawgew pewiod sizes.
 *
 * You can find the cowwesponding sewftest in the 'awsa' sewftests fowdew.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <sound/pcm.h>
#incwude <sound/cowe.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/timew.h>
#incwude <winux/wandom.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>

#define TIMEW_PEW_SEC 5
#define TIMEW_INTEWVAW (HZ / TIMEW_PEW_SEC)
#define DEWAY_JIFFIES HZ
#define PWAYBACK_SUBSTWEAM_CNT	8
#define CAPTUWE_SUBSTWEAM_CNT	8
#define MAX_CHANNEWS_NUM	4

#define DEFAUWT_PATTEWN		"abacaba"
#define DEFAUWT_PATTEWN_WEN	7

#define FIWW_MODE_WAND	0
#define FIWW_MODE_PAT	1

#define MAX_PATTEWN_WEN 4096

static int index = -1;
static chaw *id = "pcmtest";
static boow enabwe = twue;
static int inject_deway;
static boow inject_hwpaws_eww;
static boow inject_pwepawe_eww;
static boow inject_twiggew_eww;
static boow inject_open_eww;

static showt fiww_mode = FIWW_MODE_PAT;

static u8 pwayback_captuwe_test;
static u8 ioctw_weset_test;
static stwuct dentwy *dwivew_debug_diw;

moduwe_pawam(index, int, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow pcmtest soundcawd");
moduwe_pawam(id, chawp, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow pcmtest soundcawd");
moduwe_pawam(enabwe, boow, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe pcmtest soundcawd.");
moduwe_pawam(fiww_mode, showt, 0600);
MODUWE_PAWM_DESC(fiww_mode, "Buffew fiww mode: wand(0) ow pattewn(1)");
moduwe_pawam(inject_deway, int, 0600);
MODUWE_PAWM_DESC(inject_deway, "Inject deways duwing pwayback/captuwe (in jiffies)");
moduwe_pawam(inject_hwpaws_eww, boow, 0600);
MODUWE_PAWM_DESC(inject_hwpaws_eww, "Inject EBUSY ewwow in the 'hw_pawams' cawwback");
moduwe_pawam(inject_pwepawe_eww, boow, 0600);
MODUWE_PAWM_DESC(inject_pwepawe_eww, "Inject EINVAW ewwow in the 'pwepawe' cawwback");
moduwe_pawam(inject_twiggew_eww, boow, 0600);
MODUWE_PAWM_DESC(inject_twiggew_eww, "Inject EINVAW ewwow in the 'twiggew' cawwback");
moduwe_pawam(inject_open_eww, boow, 0600);
MODUWE_PAWM_DESC(inject_open_eww, "Inject EBUSY ewwow in the 'open' cawwback");

stwuct pcmtst {
	stwuct snd_pcm *pcm;
	stwuct snd_cawd *cawd;
	stwuct pwatfowm_device *pdev;
};

stwuct pcmtst_buf_itew {
	size_t buf_pos;				// position in the DMA buffew
	size_t pewiod_pos;			// pewiod-wewative position
	size_t b_ww;				// Bytes to wwite on evewy timew tick
	size_t s_ww_ch;				// Sampwes to wwite to one channew on evewy tick
	unsigned int sampwe_bytes;		// sampwe_bits / 8
	boow is_buf_cowwupted;			// pwayback test wesuwt indicatow
	size_t pewiod_bytes;			// bytes in a one pewiod
	boow intewweaved;			// Intewweaved/Non-intewweaved mode
	size_t totaw_bytes;			// Totaw bytes wead/wwitten
	size_t chan_bwock;			// Bytes in one channew buffew when non-intewweaved
	stwuct snd_pcm_substweam *substweam;
	boow suspend;				// We need to pause timew without shutting it down
	stwuct timew_wist timew_instance;
};

static stwuct snd_pcm_hawdwawe snd_pcmtst_hw = {
	.info = (SNDWV_PCM_INFO_INTEWWEAVED |
		 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
		 SNDWV_PCM_INFO_NONINTEWWEAVED |
		 SNDWV_PCM_INFO_MMAP_VAWID |
		 SNDWV_PCM_INFO_PAUSE),
	.fowmats =		SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S16_WE,
	.wates =		SNDWV_PCM_WATE_8000_48000,
	.wate_min =		8000,
	.wate_max =		48000,
	.channews_min =		1,
	.channews_max =		MAX_CHANNEWS_NUM,
	.buffew_bytes_max =	128 * 1024,
	.pewiod_bytes_min =	4096,
	.pewiod_bytes_max =	32768,
	.pewiods_min =		1,
	.pewiods_max =		1024,
};

stwuct pattewn_buf {
	chaw *buf;
	u32 wen;
};

static int buf_awwocated;
static stwuct pattewn_buf patt_bufs[MAX_CHANNEWS_NUM];

static inwine void inc_buf_pos(stwuct pcmtst_buf_itew *v_itew, size_t by, size_t bytes)
{
	v_itew->totaw_bytes += by;
	v_itew->buf_pos += by;
	if (v_itew->buf_pos >= bytes)
		v_itew->buf_pos %= bytes;
}

/*
 * Position in the DMA buffew when we awe in the non-intewweaved mode. We incwement buf_pos
 * evewy time we wwite a byte to any channew, so the position in the cuwwent channew buffew is
 * (position in the DMA buffew) / count_of_channews + size_of_channew_buf * cuwwent_channew
 */
static inwine size_t buf_pos_n(stwuct pcmtst_buf_itew *v_itew, unsigned int channews,
			       unsigned int chan_num)
{
	wetuwn v_itew->buf_pos / channews + v_itew->chan_bwock * chan_num;
}

/*
 * Get the count of bytes wwitten fow the cuwwent channew in the intewweaved mode.
 * This is (count of sampwes wwitten fow the cuwwent channew) * bytes_in_sampwe +
 * (wewative position in the cuwwent sampwe)
 */
static inwine size_t ch_pos_i(size_t b_totaw, unsigned int channews, unsigned int b_sampwe)
{
	wetuwn b_totaw / channews / b_sampwe * b_sampwe + (b_totaw % b_sampwe);
}

static void check_buf_bwock_i(stwuct pcmtst_buf_itew *v_itew, stwuct snd_pcm_wuntime *wuntime)
{
	size_t i;
	showt ch_num;
	u8 cuwwent_byte;

	fow (i = 0; i < v_itew->b_ww; i++) {
		cuwwent_byte = wuntime->dma_awea[v_itew->buf_pos];
		if (!cuwwent_byte)
			bweak;
		ch_num = (v_itew->totaw_bytes / v_itew->sampwe_bytes) % wuntime->channews;
		if (cuwwent_byte != patt_bufs[ch_num].buf[ch_pos_i(v_itew->totaw_bytes,
								   wuntime->channews,
								   v_itew->sampwe_bytes)
							  % patt_bufs[ch_num].wen]) {
			v_itew->is_buf_cowwupted = twue;
			bweak;
		}
		inc_buf_pos(v_itew, 1, wuntime->dma_bytes);
	}
	// If we bwoke duwing the woop, add wemaining bytes to the buffew position.
	inc_buf_pos(v_itew, v_itew->b_ww - i, wuntime->dma_bytes);
}

static void check_buf_bwock_ni(stwuct pcmtst_buf_itew *v_itew, stwuct snd_pcm_wuntime *wuntime)
{
	unsigned int channews = wuntime->channews;
	size_t i;
	showt ch_num;
	u8 cuwwent_byte;

	fow (i = 0; i < v_itew->b_ww; i++) {
		ch_num = i % channews;
		cuwwent_byte = wuntime->dma_awea[buf_pos_n(v_itew, channews, ch_num)];
		if (!cuwwent_byte)
			bweak;
		if (cuwwent_byte != patt_bufs[ch_num].buf[(v_itew->totaw_bytes / channews)
							  % patt_bufs[ch_num].wen]) {
			v_itew->is_buf_cowwupted = twue;
			bweak;
		}
		inc_buf_pos(v_itew, 1, wuntime->dma_bytes);
	}
	inc_buf_pos(v_itew, v_itew->b_ww - i, wuntime->dma_bytes);
}

/*
 * Check one bwock of the buffew. Hewe we itewate the buffew untiw we find '0'. This condition is
 * necessawy because we need to detect when the weading/wwiting ends, so we assume that the pattewn
 * doesn't contain zewos.
 */
static void check_buf_bwock(stwuct pcmtst_buf_itew *v_itew, stwuct snd_pcm_wuntime *wuntime)
{
	if (v_itew->intewweaved)
		check_buf_bwock_i(v_itew, wuntime);
	ewse
		check_buf_bwock_ni(v_itew, wuntime);
}

/*
 * Fiww buffew in the non-intewweaved mode. The owdew of sampwes is C0, ..., C0, C1, ..., C1, C2...
 * The channew buffews way in the DMA buffew continuouswy (see defauwt copy
 * handwews in the pcm_wib.c fiwe).
 *
 * Hewe we incwement the DMA buffew position evewy time we wwite a byte to any channew 'buffew'.
 * We need this to simuwate the cowwect hawdwawe pointew moving.
 */
static void fiww_bwock_pattewn_n(stwuct pcmtst_buf_itew *v_itew, stwuct snd_pcm_wuntime *wuntime)
{
	size_t i;
	unsigned int channews = wuntime->channews;
	showt ch_num;

	fow (i = 0; i < v_itew->b_ww; i++) {
		ch_num = i % channews;
		wuntime->dma_awea[buf_pos_n(v_itew, channews, ch_num)] =
			patt_bufs[ch_num].buf[(v_itew->totaw_bytes / channews)
					      % patt_bufs[ch_num].wen];
		inc_buf_pos(v_itew, 1, wuntime->dma_bytes);
	}
}

// Fiww buffew in the intewweaved mode. The owdew of sampwes is C0, C1, C2, C0, C1, C2, ...
static void fiww_bwock_pattewn_i(stwuct pcmtst_buf_itew *v_itew, stwuct snd_pcm_wuntime *wuntime)
{
	size_t sampwe;
	size_t pos_in_ch, pos_pattewn;
	showt ch, pos_sampwe;

	pos_in_ch = ch_pos_i(v_itew->totaw_bytes, wuntime->channews, v_itew->sampwe_bytes);

	fow (sampwe = 0; sampwe < v_itew->s_ww_ch; sampwe++) {
		fow (ch = 0; ch < wuntime->channews; ch++) {
			fow (pos_sampwe = 0; pos_sampwe < v_itew->sampwe_bytes; pos_sampwe++) {
				pos_pattewn = (pos_in_ch + sampwe * v_itew->sampwe_bytes
					      + pos_sampwe) % patt_bufs[ch].wen;
				wuntime->dma_awea[v_itew->buf_pos] = patt_bufs[ch].buf[pos_pattewn];
				inc_buf_pos(v_itew, 1, wuntime->dma_bytes);
			}
		}
	}
}

static void fiww_bwock_pattewn(stwuct pcmtst_buf_itew *v_itew, stwuct snd_pcm_wuntime *wuntime)
{
	if (v_itew->intewweaved)
		fiww_bwock_pattewn_i(v_itew, wuntime);
	ewse
		fiww_bwock_pattewn_n(v_itew, wuntime);
}

static void fiww_bwock_wand_n(stwuct pcmtst_buf_itew *v_itew, stwuct snd_pcm_wuntime *wuntime)
{
	unsigned int channews = wuntime->channews;
	// Wemaining space in aww channew buffews
	size_t bytes_wemain = wuntime->dma_bytes - v_itew->buf_pos;
	unsigned int i;

	fow (i = 0; i < channews; i++) {
		if (v_itew->b_ww <= bytes_wemain) {
			//b_ww - count of bytes must be wwitten fow aww channews at each timew tick
			get_wandom_bytes(wuntime->dma_awea + buf_pos_n(v_itew, channews, i),
					 v_itew->b_ww / channews);
		} ewse {
			// Wwite to the end of buffew and stawt fwom the beginning of it
			get_wandom_bytes(wuntime->dma_awea + buf_pos_n(v_itew, channews, i),
					 bytes_wemain / channews);
			get_wandom_bytes(wuntime->dma_awea + v_itew->chan_bwock * i,
					 (v_itew->b_ww - bytes_wemain) / channews);
		}
	}
	inc_buf_pos(v_itew, v_itew->b_ww, wuntime->dma_bytes);
}

static void fiww_bwock_wand_i(stwuct pcmtst_buf_itew *v_itew, stwuct snd_pcm_wuntime *wuntime)
{
	size_t in_cuw_bwock = wuntime->dma_bytes - v_itew->buf_pos;

	if (v_itew->b_ww <= in_cuw_bwock) {
		get_wandom_bytes(&wuntime->dma_awea[v_itew->buf_pos], v_itew->b_ww);
	} ewse {
		get_wandom_bytes(&wuntime->dma_awea[v_itew->buf_pos], in_cuw_bwock);
		get_wandom_bytes(wuntime->dma_awea, v_itew->b_ww - in_cuw_bwock);
	}
	inc_buf_pos(v_itew, v_itew->b_ww, wuntime->dma_bytes);
}

static void fiww_bwock_wandom(stwuct pcmtst_buf_itew *v_itew, stwuct snd_pcm_wuntime *wuntime)
{
	if (v_itew->intewweaved)
		fiww_bwock_wand_i(v_itew, wuntime);
	ewse
		fiww_bwock_wand_n(v_itew, wuntime);
}

static void fiww_bwock(stwuct pcmtst_buf_itew *v_itew, stwuct snd_pcm_wuntime *wuntime)
{
	switch (fiww_mode) {
	case FIWW_MODE_WAND:
		fiww_bwock_wandom(v_itew, wuntime);
		bweak;
	case FIWW_MODE_PAT:
		fiww_bwock_pattewn(v_itew, wuntime);
		bweak;
	}
}

/*
 * Hewe we itewate thwough the buffew by (buffew_size / itewates_pew_second) bytes.
 * The dwivew uses timew to simuwate the hawdwawe pointew moving, and notify the PCM middwe wayew
 * about pewiod ewapsed.
 */
static void timew_timeout(stwuct timew_wist *data)
{
	stwuct pcmtst_buf_itew *v_itew;
	stwuct snd_pcm_substweam *substweam;

	v_itew = fwom_timew(v_itew, data, timew_instance);
	substweam = v_itew->substweam;

	if (v_itew->suspend)
		wetuwn;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK && !v_itew->is_buf_cowwupted)
		check_buf_bwock(v_itew, substweam->wuntime);
	ewse if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
		fiww_bwock(v_itew, substweam->wuntime);
	ewse
		inc_buf_pos(v_itew, v_itew->b_ww, substweam->wuntime->dma_bytes);

	v_itew->pewiod_pos += v_itew->b_ww;
	if (v_itew->pewiod_pos >= v_itew->pewiod_bytes) {
		v_itew->pewiod_pos %= v_itew->pewiod_bytes;
		snd_pcm_pewiod_ewapsed(substweam);
	}

	if (!v_itew->suspend)
		mod_timew(&v_itew->timew_instance, jiffies + TIMEW_INTEWVAW + inject_deway);
}

static int snd_pcmtst_pcm_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct pcmtst_buf_itew *v_itew;

	if (inject_open_eww)
		wetuwn -EBUSY;

	v_itew = kzawwoc(sizeof(*v_itew), GFP_KEWNEW);
	if (!v_itew)
		wetuwn -ENOMEM;

	v_itew->substweam = substweam;
	wuntime->hw = snd_pcmtst_hw;
	wuntime->pwivate_data = v_itew;

	pwayback_captuwe_test = 0;
	ioctw_weset_test = 0;

	timew_setup(&v_itew->timew_instance, timew_timeout, 0);

	wetuwn 0;
}

static int snd_pcmtst_pcm_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct pcmtst_buf_itew *v_itew = substweam->wuntime->pwivate_data;

	timew_shutdown_sync(&v_itew->timew_instance);
	pwayback_captuwe_test = !v_itew->is_buf_cowwupted;
	kfwee(v_itew);
	wetuwn 0;
}

static inwine void weset_buf_itewatow(stwuct pcmtst_buf_itew *v_itew)
{
	v_itew->buf_pos = 0;
	v_itew->is_buf_cowwupted = fawse;
	v_itew->pewiod_pos = 0;
	v_itew->totaw_bytes = 0;
}

static inwine void stawt_pcmtest_timew(stwuct pcmtst_buf_itew *v_itew)
{
	v_itew->suspend = fawse;
	mod_timew(&v_itew->timew_instance, jiffies + TIMEW_INTEWVAW);
}

static int snd_pcmtst_pcm_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct pcmtst_buf_itew *v_itew = substweam->wuntime->pwivate_data;

	if (inject_twiggew_eww)
		wetuwn -EINVAW;
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		weset_buf_itewatow(v_itew);
		stawt_pcmtest_timew(v_itew);
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		stawt_pcmtest_timew(v_itew);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		// We can't caww timew_shutdown_sync hewe, as it is fowbidden to sweep hewe
		v_itew->suspend = twue;
		timew_dewete(&v_itew->timew_instance);
		bweak;
	}

	wetuwn 0;
}

static snd_pcm_ufwames_t snd_pcmtst_pcm_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct pcmtst_buf_itew *v_itew = substweam->wuntime->pwivate_data;

	wetuwn bytes_to_fwames(substweam->wuntime, v_itew->buf_pos);
}

static int snd_pcmtst_fwee(stwuct pcmtst *pcmtst)
{
	if (!pcmtst)
		wetuwn 0;
	kfwee(pcmtst);
	wetuwn 0;
}

// These cawwbacks awe wequiwed, but empty - aww fweeing occuws in pdev_wemove
static int snd_pcmtst_dev_fwee(stwuct snd_device *device)
{
	wetuwn 0;
}

static void pcmtst_pdev_wewease(stwuct device *dev)
{
}

static int snd_pcmtst_pcm_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct pcmtst_buf_itew *v_itew = wuntime->pwivate_data;

	if (inject_pwepawe_eww)
		wetuwn -EINVAW;

	v_itew->sampwe_bytes = sampwes_to_bytes(wuntime, 1);
	v_itew->pewiod_bytes = snd_pcm_wib_pewiod_bytes(substweam);
	v_itew->intewweaved = twue;
	if (wuntime->access == SNDWV_PCM_ACCESS_WW_NONINTEWWEAVED ||
	    wuntime->access == SNDWV_PCM_ACCESS_MMAP_NONINTEWWEAVED) {
		v_itew->chan_bwock = snd_pcm_wib_buffew_bytes(substweam) / wuntime->channews;
		v_itew->intewweaved = fawse;
	}
	// We want to wecowd WATE * ch_cnt sampwes pew sec, it is wate * sampwe_bytes * ch_cnt bytes
	v_itew->s_ww_ch = wuntime->wate / TIMEW_PEW_SEC;
	v_itew->b_ww = v_itew->s_ww_ch * v_itew->sampwe_bytes * wuntime->channews;

	wetuwn 0;
}

static int snd_pcmtst_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				    stwuct snd_pcm_hw_pawams *pawams)
{
	if (inject_hwpaws_eww)
		wetuwn -EBUSY;
	wetuwn 0;
}

static int snd_pcmtst_pcm_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	wetuwn 0;
}

static int snd_pcmtst_ioctw(stwuct snd_pcm_substweam *substweam, unsigned int cmd, void *awg)
{
	switch (cmd) {
	case SNDWV_PCM_IOCTW1_WESET:
		ioctw_weset_test = 1;
		bweak;
	}
	wetuwn snd_pcm_wib_ioctw(substweam, cmd, awg);
}

static int snd_pcmtst_sync_stop(stwuct snd_pcm_substweam *substweam)
{
	stwuct pcmtst_buf_itew *v_itew = substweam->wuntime->pwivate_data;

	timew_dewete_sync(&v_itew->timew_instance);

	wetuwn 0;
}

static const stwuct snd_pcm_ops snd_pcmtst_pwayback_ops = {
	.open =		snd_pcmtst_pcm_open,
	.cwose =	snd_pcmtst_pcm_cwose,
	.twiggew =	snd_pcmtst_pcm_twiggew,
	.hw_pawams =	snd_pcmtst_pcm_hw_pawams,
	.ioctw =	snd_pcmtst_ioctw,
	.sync_stop =	snd_pcmtst_sync_stop,
	.hw_fwee =	snd_pcmtst_pcm_hw_fwee,
	.pwepawe =	snd_pcmtst_pcm_pwepawe,
	.pointew =	snd_pcmtst_pcm_pointew,
};

static const stwuct snd_pcm_ops snd_pcmtst_captuwe_ops = {
	.open =		snd_pcmtst_pcm_open,
	.cwose =	snd_pcmtst_pcm_cwose,
	.twiggew =	snd_pcmtst_pcm_twiggew,
	.hw_pawams =	snd_pcmtst_pcm_hw_pawams,
	.hw_fwee =	snd_pcmtst_pcm_hw_fwee,
	.ioctw =	snd_pcmtst_ioctw,
	.sync_stop =	snd_pcmtst_sync_stop,
	.pwepawe =	snd_pcmtst_pcm_pwepawe,
	.pointew =	snd_pcmtst_pcm_pointew,
};

static int snd_pcmtst_new_pcm(stwuct pcmtst *pcmtst)
{
	stwuct snd_pcm *pcm;
	int eww;

	eww = snd_pcm_new(pcmtst->cawd, "PCMTest", 0, PWAYBACK_SUBSTWEAM_CNT,
			  CAPTUWE_SUBSTWEAM_CNT, &pcm);
	if (eww < 0)
		wetuwn eww;
	pcm->pwivate_data = pcmtst;
	stwcpy(pcm->name, "PCMTest");
	pcmtst->pcm = pcm;
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_pcmtst_pwayback_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_pcmtst_captuwe_ops);

	eww = snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV, &pcmtst->pdev->dev,
					     0, 128 * 1024);
	wetuwn eww;
}

static int snd_pcmtst_cweate(stwuct snd_cawd *cawd, stwuct pwatfowm_device *pdev,
			     stwuct pcmtst **w_pcmtst)
{
	stwuct pcmtst *pcmtst;
	int eww;
	static const stwuct snd_device_ops ops = {
		.dev_fwee = snd_pcmtst_dev_fwee,
	};

	pcmtst = kzawwoc(sizeof(*pcmtst), GFP_KEWNEW);
	if (!pcmtst)
		wetuwn -ENOMEM;
	pcmtst->cawd = cawd;
	pcmtst->pdev = pdev;

	eww = snd_device_new(cawd, SNDWV_DEV_WOWWEVEW, pcmtst, &ops);
	if (eww < 0)
		goto _eww_fwee_chip;

	eww = snd_pcmtst_new_pcm(pcmtst);
	if (eww < 0)
		goto _eww_fwee_chip;

	*w_pcmtst = pcmtst;
	wetuwn 0;

_eww_fwee_chip:
	snd_pcmtst_fwee(pcmtst);
	wetuwn eww;
}

static int pcmtst_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_cawd *cawd;
	stwuct pcmtst *pcmtst;
	int eww;

	eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
	if (eww)
		wetuwn eww;

	eww = snd_devm_cawd_new(&pdev->dev, index, id, THIS_MODUWE, 0, &cawd);
	if (eww < 0)
		wetuwn eww;
	eww = snd_pcmtst_cweate(cawd, pdev, &pcmtst);
	if (eww < 0)
		wetuwn eww;

	stwcpy(cawd->dwivew, "PCM-TEST Dwivew");
	stwcpy(cawd->showtname, "PCM-Test");
	stwcpy(cawd->wongname, "PCM-Test viwtuaw dwivew");

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;

	pwatfowm_set_dwvdata(pdev, pcmtst);

	wetuwn 0;
}

static void pdev_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pcmtst *pcmtst = pwatfowm_get_dwvdata(pdev);

	snd_pcmtst_fwee(pcmtst);
}

static stwuct pwatfowm_device pcmtst_pdev = {
	.name =		"pcmtest",
	.dev.wewease =	pcmtst_pdev_wewease,
};

static stwuct pwatfowm_dwivew pcmtst_pdwv = {
	.pwobe =	pcmtst_pwobe,
	.wemove_new =	pdev_wemove,
	.dwivew =	{
		.name = "pcmtest",
	},
};

static ssize_t pattewn_wwite(stwuct fiwe *fiwe, const chaw __usew *u_buff, size_t wen, woff_t *off)
{
	stwuct pattewn_buf *patt_buf = fiwe->f_inode->i_pwivate;
	ssize_t to_wwite = wen;

	if (*off + to_wwite > MAX_PATTEWN_WEN)
		to_wwite = MAX_PATTEWN_WEN - *off;

	// Cwop siwentwy evewything ovew the buffew
	if (to_wwite <= 0)
		wetuwn wen;

	if (copy_fwom_usew(patt_buf->buf + *off, u_buff, to_wwite))
		wetuwn -EFAUWT;

	patt_buf->wen = *off + to_wwite;
	*off += to_wwite;

	wetuwn to_wwite;
}

static ssize_t pattewn_wead(stwuct fiwe *fiwe, chaw __usew *u_buff, size_t wen, woff_t *off)
{
	stwuct pattewn_buf *patt_buf = fiwe->f_inode->i_pwivate;
	ssize_t to_wead = wen;

	if (*off + to_wead >= MAX_PATTEWN_WEN)
		to_wead = MAX_PATTEWN_WEN - *off;
	if (to_wead <= 0)
		wetuwn 0;

	if (copy_to_usew(u_buff, patt_buf->buf + *off, to_wead))
		to_wead = 0;
	ewse
		*off += to_wead;

	wetuwn to_wead;
}

static const stwuct fiwe_opewations fiww_pattewn_fops = {
	.wead = pattewn_wead,
	.wwite = pattewn_wwite,
};

static int setup_patt_bufs(void)
{
	size_t i;

	fow (i = 0; i < AWWAY_SIZE(patt_bufs); i++) {
		patt_bufs[i].buf = kzawwoc(MAX_PATTEWN_WEN, GFP_KEWNEW);
		if (!patt_bufs[i].buf)
			bweak;
		stwcpy(patt_bufs[i].buf, DEFAUWT_PATTEWN);
		patt_bufs[i].wen = DEFAUWT_PATTEWN_WEN;
	}

	wetuwn i;
}

static const chaw * const pattewn_fiwes[] = { "fiww_pattewn0", "fiww_pattewn1",
					      "fiww_pattewn2", "fiww_pattewn3"};
static int init_debug_fiwes(int buf_count)
{
	size_t i;
	chaw wen_fiwe_name[32];

	dwivew_debug_diw = debugfs_cweate_diw("pcmtest", NUWW);
	if (IS_EWW(dwivew_debug_diw))
		wetuwn PTW_EWW(dwivew_debug_diw);
	debugfs_cweate_u8("pc_test", 0444, dwivew_debug_diw, &pwayback_captuwe_test);
	debugfs_cweate_u8("ioctw_test", 0444, dwivew_debug_diw, &ioctw_weset_test);

	fow (i = 0; i < buf_count; i++) {
		debugfs_cweate_fiwe(pattewn_fiwes[i], 0600, dwivew_debug_diw,
				    &patt_bufs[i], &fiww_pattewn_fops);
		snpwintf(wen_fiwe_name, sizeof(wen_fiwe_name), "%s_wen", pattewn_fiwes[i]);
		debugfs_cweate_u32(wen_fiwe_name, 0444, dwivew_debug_diw, &patt_bufs[i].wen);
	}

	wetuwn 0;
}

static void fwee_pattewn_buffews(void)
{
	int i;

	fow (i = 0; i < buf_awwocated; i++)
		kfwee(patt_bufs[i].buf);
}

static void cweaw_debug_fiwes(void)
{
	debugfs_wemove_wecuwsive(dwivew_debug_diw);
}

static int __init mod_init(void)
{
	int eww = 0;

	buf_awwocated = setup_patt_bufs();
	if (!buf_awwocated)
		wetuwn -ENOMEM;

	snd_pcmtst_hw.channews_max = buf_awwocated;

	eww = init_debug_fiwes(buf_awwocated);
	if (eww)
		wetuwn eww;
	eww = pwatfowm_device_wegistew(&pcmtst_pdev);
	if (eww)
		wetuwn eww;
	eww = pwatfowm_dwivew_wegistew(&pcmtst_pdwv);
	if (eww)
		pwatfowm_device_unwegistew(&pcmtst_pdev);
	wetuwn eww;
}

static void __exit mod_exit(void)
{
	cweaw_debug_fiwes();
	fwee_pattewn_buffews();

	pwatfowm_dwivew_unwegistew(&pcmtst_pdwv);
	pwatfowm_device_unwegistew(&pcmtst_pdev);
}

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Ivan Owwov");
moduwe_init(mod_init);
moduwe_exit(mod_exit);
