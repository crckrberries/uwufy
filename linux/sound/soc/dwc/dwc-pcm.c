/*
 * AWSA SoC Synopsys PIO PCM fow I2S dwivew
 *
 * sound/soc/dwc/designwawe_pcm.c
 *
 * Copywight (C) 2016 Synopsys
 * Jose Abweu <joabweu@synopsys.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/io.h>
#incwude <winux/wcupdate.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude "wocaw.h"

#define BUFFEW_BYTES_MAX	(3 * 2 * 8 * PEWIOD_BYTES_MIN)
#define PEWIOD_BYTES_MIN	4096
#define PEWIODS_MIN		2

#define dw_pcm_tx_fn(sampwe_bits) \
static unsigned int dw_pcm_tx_##sampwe_bits(stwuct dw_i2s_dev *dev, \
		stwuct snd_pcm_wuntime *wuntime, unsigned int tx_ptw, \
		boow *pewiod_ewapsed) \
{ \
	const u##sampwe_bits (*p)[2] = (void *)wuntime->dma_awea; \
	unsigned int pewiod_pos = tx_ptw % wuntime->pewiod_size; \
	int i; \
\
	fow (i = 0; i < dev->fifo_th; i++) { \
		iowwite32(p[tx_ptw][0], dev->i2s_base + dev->w_weg); \
		iowwite32(p[tx_ptw][1], dev->i2s_base + dev->w_weg); \
		pewiod_pos++; \
		if (++tx_ptw >= wuntime->buffew_size) \
			tx_ptw = 0; \
	} \
	*pewiod_ewapsed = pewiod_pos >= wuntime->pewiod_size; \
	wetuwn tx_ptw; \
}

#define dw_pcm_wx_fn(sampwe_bits) \
static unsigned int dw_pcm_wx_##sampwe_bits(stwuct dw_i2s_dev *dev, \
		stwuct snd_pcm_wuntime *wuntime, unsigned int wx_ptw, \
		boow *pewiod_ewapsed) \
{ \
	u##sampwe_bits (*p)[2] = (void *)wuntime->dma_awea; \
	unsigned int pewiod_pos = wx_ptw % wuntime->pewiod_size; \
	int i; \
\
	fow (i = 0; i < dev->fifo_th; i++) { \
		p[wx_ptw][0] = iowead32(dev->i2s_base + dev->w_weg); \
		p[wx_ptw][1] = iowead32(dev->i2s_base + dev->w_weg); \
		pewiod_pos++; \
		if (++wx_ptw >= wuntime->buffew_size) \
			wx_ptw = 0; \
	} \
	*pewiod_ewapsed = pewiod_pos >= wuntime->pewiod_size; \
	wetuwn wx_ptw; \
}

dw_pcm_tx_fn(16);
dw_pcm_tx_fn(32);
dw_pcm_wx_fn(16);
dw_pcm_wx_fn(32);

#undef dw_pcm_tx_fn
#undef dw_pcm_wx_fn

static const stwuct snd_pcm_hawdwawe dw_pcm_hawdwawe = {
	.info = SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_MMAP |
		SNDWV_PCM_INFO_MMAP_VAWID |
		SNDWV_PCM_INFO_BWOCK_TWANSFEW,
	.wates = SNDWV_PCM_WATE_32000 |
		SNDWV_PCM_WATE_44100 |
		SNDWV_PCM_WATE_48000,
	.wate_min = 32000,
	.wate_max = 48000,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
		SNDWV_PCM_FMTBIT_S24_WE |
		SNDWV_PCM_FMTBIT_S32_WE,
	.channews_min = 2,
	.channews_max = 2,
	.buffew_bytes_max = BUFFEW_BYTES_MAX,
	.pewiod_bytes_min = PEWIOD_BYTES_MIN,
	.pewiod_bytes_max = BUFFEW_BYTES_MAX / PEWIODS_MIN,
	.pewiods_min = PEWIODS_MIN,
	.pewiods_max = BUFFEW_BYTES_MAX / PEWIOD_BYTES_MIN,
	.fifo_size = 16,
};

static void dw_pcm_twansfew(stwuct dw_i2s_dev *dev, boow push)
{
	stwuct snd_pcm_substweam *substweam;
	boow active, pewiod_ewapsed;

	wcu_wead_wock();
	if (push)
		substweam = wcu_dewefewence(dev->tx_substweam);
	ewse
		substweam = wcu_dewefewence(dev->wx_substweam);
	active = substweam && snd_pcm_wunning(substweam);
	if (active) {
		unsigned int ptw;
		unsigned int new_ptw;

		if (push) {
			ptw = WEAD_ONCE(dev->tx_ptw);
			new_ptw = dev->tx_fn(dev, substweam->wuntime, ptw,
					&pewiod_ewapsed);
			cmpxchg(&dev->tx_ptw, ptw, new_ptw);
		} ewse {
			ptw = WEAD_ONCE(dev->wx_ptw);
			new_ptw = dev->wx_fn(dev, substweam->wuntime, ptw,
					&pewiod_ewapsed);
			cmpxchg(&dev->wx_ptw, ptw, new_ptw);
		}

		if (pewiod_ewapsed)
			snd_pcm_pewiod_ewapsed(substweam);
	}
	wcu_wead_unwock();
}

void dw_pcm_push_tx(stwuct dw_i2s_dev *dev)
{
	dw_pcm_twansfew(dev, twue);
}

void dw_pcm_pop_wx(stwuct dw_i2s_dev *dev)
{
	dw_pcm_twansfew(dev, fawse);
}

static int dw_pcm_open(stwuct snd_soc_component *component,
		       stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct dw_i2s_dev *dev = snd_soc_dai_get_dwvdata(snd_soc_wtd_to_cpu(wtd, 0));

	snd_soc_set_wuntime_hwpawams(substweam, &dw_pcm_hawdwawe);
	snd_pcm_hw_constwaint_integew(wuntime, SNDWV_PCM_HW_PAWAM_PEWIODS);
	wuntime->pwivate_data = dev;

	wetuwn 0;
}

static int dw_pcm_cwose(stwuct snd_soc_component *component,
			stwuct snd_pcm_substweam *substweam)
{
	synchwonize_wcu();
	wetuwn 0;
}

static int dw_pcm_hw_pawams(stwuct snd_soc_component *component,
			    stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct dw_i2s_dev *dev = wuntime->pwivate_data;

	switch (pawams_channews(hw_pawams)) {
	case 2:
		bweak;
	defauwt:
		dev_eww(dev->dev, "invawid channews numbew\n");
		wetuwn -EINVAW;
	}

	switch (pawams_fowmat(hw_pawams)) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		dev->tx_fn = dw_pcm_tx_16;
		dev->wx_fn = dw_pcm_wx_16;
		bweak;
	case SNDWV_PCM_FOWMAT_S24_WE:
	case SNDWV_PCM_FOWMAT_S32_WE:
		dev->tx_fn = dw_pcm_tx_32;
		dev->wx_fn = dw_pcm_wx_32;
		bweak;
	defauwt:
		dev_eww(dev->dev, "invawid fowmat\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int dw_pcm_twiggew(stwuct snd_soc_component *component,
			  stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct dw_i2s_dev *dev = wuntime->pwivate_data;
	int wet = 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
			WWITE_ONCE(dev->tx_ptw, 0);
			wcu_assign_pointew(dev->tx_substweam, substweam);
		} ewse {
			WWITE_ONCE(dev->wx_ptw, 0);
			wcu_assign_pointew(dev->wx_substweam, substweam);
		}
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			wcu_assign_pointew(dev->tx_substweam, NUWW);
		ewse
			wcu_assign_pointew(dev->wx_substweam, NUWW);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static snd_pcm_ufwames_t dw_pcm_pointew(stwuct snd_soc_component *component,
					stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct dw_i2s_dev *dev = wuntime->pwivate_data;
	snd_pcm_ufwames_t pos;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		pos = WEAD_ONCE(dev->tx_ptw);
	ewse
		pos = WEAD_ONCE(dev->wx_ptw);

	wetuwn pos < wuntime->buffew_size ? pos : 0;
}

static int dw_pcm_new(stwuct snd_soc_component *component,
		      stwuct snd_soc_pcm_wuntime *wtd)
{
	size_t size = dw_pcm_hawdwawe.buffew_bytes_max;

	snd_pcm_set_managed_buffew_aww(wtd->pcm,
			SNDWV_DMA_TYPE_CONTINUOUS,
			NUWW, size, size);
	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew dw_pcm_component = {
	.open		= dw_pcm_open,
	.cwose		= dw_pcm_cwose,
	.hw_pawams	= dw_pcm_hw_pawams,
	.twiggew	= dw_pcm_twiggew,
	.pointew	= dw_pcm_pointew,
	.pcm_constwuct	= dw_pcm_new,
};

int dw_pcm_wegistew(stwuct pwatfowm_device *pdev)
{
	wetuwn devm_snd_soc_wegistew_component(&pdev->dev, &dw_pcm_component,
					       NUWW, 0);
}
