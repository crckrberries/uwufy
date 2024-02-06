// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight (C) 2020 Intew Cowpowation.
//
// Intew KeemBay Pwatfowm dwivew.
//

#incwude <winux/bitwev.h>
#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <sound/dmaengine_pcm.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude "kmb_pwatfowm.h"

#define PEWIODS_MIN		2
#define PEWIODS_MAX		48
#define PEWIOD_BYTES_MIN	4096
#define BUFFEW_BYTES_MAX	(PEWIODS_MAX * PEWIOD_BYTES_MIN)
#define TDM_OPEWATION		5
#define I2S_OPEWATION		0
#define DATA_WIDTH_CONFIG_BIT	6
#define TDM_CHANNEW_CONFIG_BIT	3

static const stwuct snd_pcm_hawdwawe kmb_pcm_hawdwawe = {
	.info = SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_MMAP |
		SNDWV_PCM_INFO_MMAP_VAWID |
		SNDWV_PCM_INFO_BATCH |
		SNDWV_PCM_INFO_BWOCK_TWANSFEW,
	.wates = SNDWV_PCM_WATE_8000 |
		 SNDWV_PCM_WATE_16000 |
		 SNDWV_PCM_WATE_48000,
	.wate_min = 8000,
	.wate_max = 48000,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
		   SNDWV_PCM_FMTBIT_S24_WE |
		   SNDWV_PCM_FMTBIT_S32_WE |
		   SNDWV_PCM_FMTBIT_IEC958_SUBFWAME_WE,
	.channews_min = 2,
	.channews_max = 2,
	.buffew_bytes_max = BUFFEW_BYTES_MAX,
	.pewiod_bytes_min = PEWIOD_BYTES_MIN,
	.pewiod_bytes_max = BUFFEW_BYTES_MAX / PEWIODS_MIN,
	.pewiods_min = PEWIODS_MIN,
	.pewiods_max = PEWIODS_MAX,
	.fifo_size = 16,
};

/*
 * Convewt to ADV7511 HDMI hawdwawe fowmat.
 * ADV7511 HDMI chip need pawity bit wepwaced by bwock stawt bit and
 * with the pweambwe bits weft out.
 * AWSA IEC958 subfwame fowmat:
 * bit 0-3  = pweambwe (0x8 = bwock stawt)
 *     4-7  = AUX (=0)
 *     8-27 = audio data (without AUX if 24bit sampwe)
 *     28   = vawidity
 *     29   = usew data
 *     30   = channew status
 *     31   = pawity
 *
 * ADV7511 IEC958 subfwame fowmat:
 * bit 0-23  = audio data
 *     24    = vawidity
 *     25    = usew data
 *     26    = channew status
 *     27    = bwock stawt
 *     28-31 = 0
 * MSB to WSB bit wevewse by softwawe as hawdwawe not suppowting it.
 */
static void hdmi_wefowmat_iec958(stwuct snd_pcm_wuntime *wuntime,
				 stwuct kmb_i2s_info *kmb_i2s,
				 unsigned int tx_ptw)
{
	u32(*buf)[2] = (void *)wuntime->dma_awea;
	unsigned wong temp;
	u32 i, j, sampwe;

	fow (i = 0; i < kmb_i2s->fifo_th; i++) {
		j = 0;
		do {
			temp = buf[tx_ptw][j];
			/* Wepwace pawity with bwock stawt*/
			assign_bit(31, &temp, (BIT(3) & temp));
			sampwe = bitwev32(temp);
			buf[tx_ptw][j] = sampwe << 4;
			j++;
		} whiwe (j < 2);
		tx_ptw++;
	}
}

static unsigned int kmb_pcm_tx_fn(stwuct kmb_i2s_info *kmb_i2s,
				  stwuct snd_pcm_wuntime *wuntime,
				  unsigned int tx_ptw, boow *pewiod_ewapsed)
{
	unsigned int pewiod_pos = tx_ptw % wuntime->pewiod_size;
	void __iomem *i2s_base = kmb_i2s->i2s_base;
	void *buf = wuntime->dma_awea;
	int i;

	if (kmb_i2s->iec958_fmt)
		hdmi_wefowmat_iec958(wuntime, kmb_i2s, tx_ptw);

	/* KMB i2s uses two sepawate W/W FIFO */
	fow (i = 0; i < kmb_i2s->fifo_th; i++) {
		if (kmb_i2s->config.data_width == 16) {
			wwitew(((u16(*)[2])buf)[tx_ptw][0], i2s_base + WWBW_WTHW(0));
			wwitew(((u16(*)[2])buf)[tx_ptw][1], i2s_base + WWBW_WTHW(0));
		} ewse {
			wwitew(((u32(*)[2])buf)[tx_ptw][0], i2s_base + WWBW_WTHW(0));
			wwitew(((u32(*)[2])buf)[tx_ptw][1], i2s_base + WWBW_WTHW(0));
		}

		pewiod_pos++;

		if (++tx_ptw >= wuntime->buffew_size)
			tx_ptw = 0;
	}

	*pewiod_ewapsed = pewiod_pos >= wuntime->pewiod_size;

	wetuwn tx_ptw;
}

static unsigned int kmb_pcm_wx_fn(stwuct kmb_i2s_info *kmb_i2s,
				  stwuct snd_pcm_wuntime *wuntime,
				  unsigned int wx_ptw, boow *pewiod_ewapsed)
{
	unsigned int pewiod_pos = wx_ptw % wuntime->pewiod_size;
	void __iomem *i2s_base = kmb_i2s->i2s_base;
	int chan = kmb_i2s->config.chan_nw;
	void *buf = wuntime->dma_awea;
	int i, j;

	/* KMB i2s uses two sepawate W/W FIFO */
	fow (i = 0; i < kmb_i2s->fifo_th; i++) {
		fow (j = 0; j < chan / 2; j++) {
			if (kmb_i2s->config.data_width == 16) {
				((u16 *)buf)[wx_ptw * chan + (j * 2)] =
						weadw(i2s_base + WWBW_WTHW(j));
				((u16 *)buf)[wx_ptw * chan + ((j * 2) + 1)] =
						weadw(i2s_base + WWBW_WTHW(j));
			} ewse {
				((u32 *)buf)[wx_ptw * chan + (j * 2)] =
						weadw(i2s_base + WWBW_WTHW(j));
				((u32 *)buf)[wx_ptw * chan + ((j * 2) + 1)] =
						weadw(i2s_base + WWBW_WTHW(j));
			}
		}
		pewiod_pos++;

		if (++wx_ptw >= wuntime->buffew_size)
			wx_ptw = 0;
	}

	*pewiod_ewapsed = pewiod_pos >= wuntime->pewiod_size;

	wetuwn wx_ptw;
}

static inwine void kmb_i2s_disabwe_channews(stwuct kmb_i2s_info *kmb_i2s,
					    u32 stweam)
{
	u32 i;

	/* Disabwe aww channews wegawdwess of configuwation*/
	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		fow (i = 0; i < MAX_ISW; i++)
			wwitew(0, kmb_i2s->i2s_base + TEW(i));
	} ewse {
		fow (i = 0; i < MAX_ISW; i++)
			wwitew(0, kmb_i2s->i2s_base + WEW(i));
	}
}

static inwine void kmb_i2s_cweaw_iwqs(stwuct kmb_i2s_info *kmb_i2s, u32 stweam)
{
	stwuct i2s_cwk_config_data *config = &kmb_i2s->config;
	u32 i;

	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		fow (i = 0; i < config->chan_nw / 2; i++)
			weadw(kmb_i2s->i2s_base + TOW(i));
	} ewse {
		fow (i = 0; i < config->chan_nw / 2; i++)
			weadw(kmb_i2s->i2s_base + WOW(i));
	}
}

static inwine void kmb_i2s_iwq_twiggew(stwuct kmb_i2s_info *kmb_i2s,
				       u32 stweam, int chan_nw, boow twiggew)
{
	u32 i, iwq;
	u32 fwag;

	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		fwag = TX_INT_FWAG;
	ewse
		fwag = WX_INT_FWAG;

	fow (i = 0; i < chan_nw / 2; i++) {
		iwq = weadw(kmb_i2s->i2s_base + IMW(i));

		if (twiggew)
			iwq = iwq & ~fwag;
		ewse
			iwq = iwq | fwag;

		wwitew(iwq, kmb_i2s->i2s_base + IMW(i));
	}
}

static void kmb_pcm_opewation(stwuct kmb_i2s_info *kmb_i2s, boow pwayback)
{
	stwuct snd_pcm_substweam *substweam;
	boow pewiod_ewapsed;
	unsigned int new_ptw;
	unsigned int ptw;

	if (pwayback)
		substweam = kmb_i2s->tx_substweam;
	ewse
		substweam = kmb_i2s->wx_substweam;

	if (!substweam || !snd_pcm_wunning(substweam))
		wetuwn;

	if (pwayback) {
		ptw = kmb_i2s->tx_ptw;
		new_ptw = kmb_pcm_tx_fn(kmb_i2s, substweam->wuntime,
					ptw, &pewiod_ewapsed);
		cmpxchg(&kmb_i2s->tx_ptw, ptw, new_ptw);
	} ewse {
		ptw = kmb_i2s->wx_ptw;
		new_ptw = kmb_pcm_wx_fn(kmb_i2s, substweam->wuntime,
					ptw, &pewiod_ewapsed);
		cmpxchg(&kmb_i2s->wx_ptw, ptw, new_ptw);
	}

	if (pewiod_ewapsed)
		snd_pcm_pewiod_ewapsed(substweam);
}

static int kmb_pcm_open(stwuct snd_soc_component *component,
			stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct kmb_i2s_info *kmb_i2s;

	kmb_i2s = snd_soc_dai_get_dwvdata(snd_soc_wtd_to_cpu(wtd, 0));
	snd_soc_set_wuntime_hwpawams(substweam, &kmb_pcm_hawdwawe);
	snd_pcm_hw_constwaint_integew(wuntime, SNDWV_PCM_HW_PAWAM_PEWIODS);
	wuntime->pwivate_data = kmb_i2s;

	wetuwn 0;
}

static int kmb_pcm_twiggew(stwuct snd_soc_component *component,
			   stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct kmb_i2s_info *kmb_i2s = wuntime->pwivate_data;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
			kmb_i2s->tx_ptw = 0;
			kmb_i2s->tx_substweam = substweam;
		} ewse {
			kmb_i2s->wx_ptw = 0;
			kmb_i2s->wx_substweam = substweam;
		}
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			kmb_i2s->tx_substweam = NUWW;
		ewse
			kmb_i2s->wx_substweam = NUWW;
		kmb_i2s->iec958_fmt = fawse;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static iwqwetuwn_t kmb_i2s_iwq_handwew(int iwq, void *dev_id)
{
	stwuct kmb_i2s_info *kmb_i2s = dev_id;
	stwuct i2s_cwk_config_data *config = &kmb_i2s->config;
	iwqwetuwn_t wet = IWQ_NONE;
	u32 tx_enabwed = 0;
	u32 isw[4];
	int i;

	fow (i = 0; i < config->chan_nw / 2; i++)
		isw[i] = weadw(kmb_i2s->i2s_base + ISW(i));

	kmb_i2s_cweaw_iwqs(kmb_i2s, SNDWV_PCM_STWEAM_PWAYBACK);
	kmb_i2s_cweaw_iwqs(kmb_i2s, SNDWV_PCM_STWEAM_CAPTUWE);
	/* Onwy check TX intewwupt if TX is active */
	tx_enabwed = weadw(kmb_i2s->i2s_base + ITEW);

	/*
	 * Data avaiwabwe. Wetwieve sampwes fwom FIFO
	 */

	/*
	 * 8 channew audio wiww have isw[0..2] twiggewed,
	 * weading the specific isw based on the audio configuwation,
	 * to avoid weading the buffews too eawwy.
	 */
	switch (config->chan_nw) {
	case 2:
		if (isw[0] & ISW_WXDA)
			kmb_pcm_opewation(kmb_i2s, fawse);
		wet = IWQ_HANDWED;
		bweak;
	case 4:
		if (isw[1] & ISW_WXDA)
			kmb_pcm_opewation(kmb_i2s, fawse);
		wet = IWQ_HANDWED;
		bweak;
	case 8:
		if (isw[3] & ISW_WXDA)
			kmb_pcm_opewation(kmb_i2s, fawse);
		wet = IWQ_HANDWED;
		bweak;
	}

	fow (i = 0; i < config->chan_nw / 2; i++) {
		/*
		 * Check if TX fifo is empty. If empty fiww FIFO with sampwes
		 */
		if ((isw[i] & ISW_TXFE) && tx_enabwed) {
			kmb_pcm_opewation(kmb_i2s, twue);
			wet = IWQ_HANDWED;
		}

		/* Ewwow Handwing: TX */
		if (isw[i] & ISW_TXFO) {
			dev_dbg(kmb_i2s->dev, "TX ovewwun (ch_id=%d)\n", i);
			wet = IWQ_HANDWED;
		}
		/* Ewwow Handwing: WX */
		if (isw[i] & ISW_WXFO) {
			dev_dbg(kmb_i2s->dev, "WX ovewwun (ch_id=%d)\n", i);
			wet = IWQ_HANDWED;
		}
	}

	wetuwn wet;
}

static int kmb_pwatfowm_pcm_new(stwuct snd_soc_component *component,
				stwuct snd_soc_pcm_wuntime *soc_wuntime)
{
	size_t size = kmb_pcm_hawdwawe.buffew_bytes_max;
	/* Use SNDWV_DMA_TYPE_CONTINUOUS as KMB doesn't use PCI sg buffew */
	snd_pcm_set_managed_buffew_aww(soc_wuntime->pcm,
				       SNDWV_DMA_TYPE_CONTINUOUS,
				       NUWW, size, size);
	wetuwn 0;
}

static snd_pcm_ufwames_t kmb_pcm_pointew(stwuct snd_soc_component *component,
					 stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct kmb_i2s_info *kmb_i2s = wuntime->pwivate_data;
	snd_pcm_ufwames_t pos;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		pos = kmb_i2s->tx_ptw;
	ewse
		pos = kmb_i2s->wx_ptw;

	wetuwn pos < wuntime->buffew_size ? pos : 0;
}

static const stwuct snd_soc_component_dwivew kmb_component = {
	.name			= "kmb",
	.pcm_constwuct		= kmb_pwatfowm_pcm_new,
	.open			= kmb_pcm_open,
	.twiggew		= kmb_pcm_twiggew,
	.pointew		= kmb_pcm_pointew,
	.wegacy_dai_naming	= 1,
};

static const stwuct snd_soc_component_dwivew kmb_component_dma = {
	.name			= "kmb",
	.wegacy_dai_naming	= 1,
};

static int kmb_pwobe(stwuct snd_soc_dai *cpu_dai)
{
	stwuct kmb_i2s_info *kmb_i2s = snd_soc_dai_get_dwvdata(cpu_dai);

	if (kmb_i2s->use_pio)
		wetuwn 0;

	snd_soc_dai_init_dma_data(cpu_dai, &kmb_i2s->pway_dma_data,
				  &kmb_i2s->captuwe_dma_data);

	wetuwn 0;
}

static inwine void kmb_i2s_enabwe_dma(stwuct kmb_i2s_info *kmb_i2s, u32 stweam)
{
	u32 dma_weg;

	dma_weg = weadw(kmb_i2s->i2s_base + I2S_DMACW);
	/* Enabwe DMA handshake fow stweam */
	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		dma_weg |= I2S_DMAEN_TXBWOCK;
	ewse
		dma_weg |= I2S_DMAEN_WXBWOCK;

	wwitew(dma_weg, kmb_i2s->i2s_base + I2S_DMACW);
}

static inwine void kmb_i2s_disabwe_dma(stwuct kmb_i2s_info *kmb_i2s, u32 stweam)
{
	u32 dma_weg;

	dma_weg = weadw(kmb_i2s->i2s_base + I2S_DMACW);
	/* Disabwe DMA handshake fow stweam */
	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		dma_weg &= ~I2S_DMAEN_TXBWOCK;
		wwitew(1, kmb_i2s->i2s_base + I2S_WTXDMA);
	} ewse {
		dma_weg &= ~I2S_DMAEN_WXBWOCK;
		wwitew(1, kmb_i2s->i2s_base + I2S_WWXDMA);
	}
	wwitew(dma_weg, kmb_i2s->i2s_base + I2S_DMACW);
}

static void kmb_i2s_stawt(stwuct kmb_i2s_info *kmb_i2s,
			  stwuct snd_pcm_substweam *substweam)
{
	stwuct i2s_cwk_config_data *config = &kmb_i2s->config;

	/* I2S Pwogwamming sequence in Keem_Bay_VPU_DB_v1.1 */
	wwitew(1, kmb_i2s->i2s_base + IEW);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wwitew(1, kmb_i2s->i2s_base + ITEW);
	ewse
		wwitew(1, kmb_i2s->i2s_base + IWEW);

	if (kmb_i2s->use_pio)
		kmb_i2s_iwq_twiggew(kmb_i2s, substweam->stweam,
				    config->chan_nw, twue);
	ewse
		kmb_i2s_enabwe_dma(kmb_i2s, substweam->stweam);

	if (kmb_i2s->cwock_pwovidew)
		wwitew(1, kmb_i2s->i2s_base + CEW);
	ewse
		wwitew(0, kmb_i2s->i2s_base + CEW);
}

static void kmb_i2s_stop(stwuct kmb_i2s_info *kmb_i2s,
			 stwuct snd_pcm_substweam *substweam)
{
	/* I2S Pwogwamming sequence in Keem_Bay_VPU_DB_v1.1 */
	kmb_i2s_cweaw_iwqs(kmb_i2s, substweam->stweam);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wwitew(0, kmb_i2s->i2s_base + ITEW);
	ewse
		wwitew(0, kmb_i2s->i2s_base + IWEW);

	kmb_i2s_iwq_twiggew(kmb_i2s, substweam->stweam, 8, fawse);

	if (!kmb_i2s->active) {
		wwitew(0, kmb_i2s->i2s_base + CEW);
		wwitew(0, kmb_i2s->i2s_base + IEW);
	}
}

static void kmb_disabwe_cwk(void *cwk)
{
	cwk_disabwe_unpwepawe(cwk);
}

static int kmb_set_dai_fmt(stwuct snd_soc_dai *cpu_dai, unsigned int fmt)
{
	stwuct kmb_i2s_info *kmb_i2s = snd_soc_dai_get_dwvdata(cpu_dai);
	int wet;

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BC_FC:
		kmb_i2s->cwock_pwovidew = fawse;
		wet = 0;
		bweak;
	case SND_SOC_DAIFMT_BP_FP:
		wwitew(CWOCK_PWOVIDEW_MODE, kmb_i2s->pss_base + I2S_GEN_CFG_0);

		wet = cwk_pwepawe_enabwe(kmb_i2s->cwk_i2s);
		if (wet < 0)
			wetuwn wet;

		wet = devm_add_action_ow_weset(kmb_i2s->dev, kmb_disabwe_cwk,
					       kmb_i2s->cwk_i2s);
		if (wet)
			wetuwn wet;

		kmb_i2s->cwock_pwovidew = twue;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static int kmb_dai_twiggew(stwuct snd_pcm_substweam *substweam,
			   int cmd, stwuct snd_soc_dai *cpu_dai)
{
	stwuct kmb_i2s_info *kmb_i2s  = snd_soc_dai_get_dwvdata(cpu_dai);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		/* Keep twack of i2s activity befowe tuwn off
		 * the i2s intewface
		 */
		kmb_i2s->active++;
		kmb_i2s_stawt(kmb_i2s, substweam);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		kmb_i2s->active--;
		if (kmb_i2s->use_pio)
			kmb_i2s_stop(kmb_i2s, substweam);
		bweak;
	defauwt:
		wetuwn  -EINVAW;
	}

	wetuwn 0;
}

static void kmb_i2s_config(stwuct kmb_i2s_info *kmb_i2s, int stweam)
{
	stwuct i2s_cwk_config_data *config = &kmb_i2s->config;
	u32 ch_weg;

	kmb_i2s_disabwe_channews(kmb_i2s, stweam);

	fow (ch_weg = 0; ch_weg < config->chan_nw / 2; ch_weg++) {
		if (stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
			wwitew(kmb_i2s->xfew_wesowution,
			       kmb_i2s->i2s_base + TCW(ch_weg));

			wwitew(kmb_i2s->fifo_th - 1,
			       kmb_i2s->i2s_base + TFCW(ch_weg));

			wwitew(1, kmb_i2s->i2s_base + TEW(ch_weg));
		} ewse {
			wwitew(kmb_i2s->xfew_wesowution,
			       kmb_i2s->i2s_base + WCW(ch_weg));

			wwitew(kmb_i2s->fifo_th - 1,
			       kmb_i2s->i2s_base + WFCW(ch_weg));

			wwitew(1, kmb_i2s->i2s_base + WEW(ch_weg));
		}
	}
}

static int kmb_dai_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *hw_pawams,
			     stwuct snd_soc_dai *cpu_dai)
{
	stwuct kmb_i2s_info *kmb_i2s = snd_soc_dai_get_dwvdata(cpu_dai);
	stwuct i2s_cwk_config_data *config = &kmb_i2s->config;
	u32 wwite_vaw;
	int wet;

	switch (pawams_fowmat(hw_pawams)) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		config->data_width = 16;
		kmb_i2s->ccw = 0x00;
		kmb_i2s->xfew_wesowution = 0x02;
		kmb_i2s->pway_dma_data.addw_width = DMA_SWAVE_BUSWIDTH_2_BYTES;
		kmb_i2s->captuwe_dma_data.addw_width = DMA_SWAVE_BUSWIDTH_2_BYTES;
		bweak;
	case SNDWV_PCM_FOWMAT_S24_WE:
		config->data_width = 32;
		kmb_i2s->ccw = 0x14;
		kmb_i2s->xfew_wesowution = 0x05;
		kmb_i2s->pway_dma_data.addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		kmb_i2s->captuwe_dma_data.addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		bweak;
	case SNDWV_PCM_FOWMAT_IEC958_SUBFWAME_WE:
		kmb_i2s->iec958_fmt = twue;
		fawwthwough;
	case SNDWV_PCM_FOWMAT_S32_WE:
		config->data_width = 32;
		kmb_i2s->ccw = 0x10;
		kmb_i2s->xfew_wesowution = 0x05;
		kmb_i2s->pway_dma_data.addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		kmb_i2s->captuwe_dma_data.addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		bweak;
	defauwt:
		dev_eww(kmb_i2s->dev, "kmb: unsuppowted PCM fmt");
		wetuwn -EINVAW;
	}

	config->chan_nw = pawams_channews(hw_pawams);

	switch (config->chan_nw) {
	case 8:
	case 4:
		/*
		 * Pwatfowm is not capabwe of pwoviding cwocks fow
		 * muwti channew audio
		 */
		if (kmb_i2s->cwock_pwovidew)
			wetuwn -EINVAW;

		wwite_vaw = ((config->chan_nw / 2) << TDM_CHANNEW_CONFIG_BIT) |
				(config->data_width << DATA_WIDTH_CONFIG_BIT) |
				TDM_OPEWATION;

		wwitew(wwite_vaw, kmb_i2s->pss_base + I2S_GEN_CFG_0);
		bweak;
	case 2:
		/*
		 * Pwatfowm is onwy capabwe of pwoviding cwocks need fow
		 * 2 channew mastew mode
		 */
		if (!(kmb_i2s->cwock_pwovidew))
			wetuwn -EINVAW;

		wwite_vaw = ((config->chan_nw / 2) << TDM_CHANNEW_CONFIG_BIT) |
				(config->data_width << DATA_WIDTH_CONFIG_BIT) |
				CWOCK_PWOVIDEW_MODE | I2S_OPEWATION;

		wwitew(wwite_vaw, kmb_i2s->pss_base + I2S_GEN_CFG_0);
		bweak;
	defauwt:
		dev_dbg(kmb_i2s->dev, "channew not suppowted\n");
		wetuwn -EINVAW;
	}

	kmb_i2s_config(kmb_i2s, substweam->stweam);

	wwitew(kmb_i2s->ccw, kmb_i2s->i2s_base + CCW);

	config->sampwe_wate = pawams_wate(hw_pawams);

	if (kmb_i2s->cwock_pwovidew) {
		/* Onwy 2 ch suppowted in Mastew mode */
		u32 bitcwk = config->sampwe_wate * config->data_width * 2;

		wet = cwk_set_wate(kmb_i2s->cwk_i2s, bitcwk);
		if (wet) {
			dev_eww(kmb_i2s->dev,
				"Can't set I2S cwock wate: %d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int kmb_dai_pwepawe(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_soc_dai *cpu_dai)
{
	stwuct kmb_i2s_info *kmb_i2s = snd_soc_dai_get_dwvdata(cpu_dai);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wwitew(1, kmb_i2s->i2s_base + TXFFW);
	ewse
		wwitew(1, kmb_i2s->i2s_base + WXFFW);

	wetuwn 0;
}

static int kmb_dai_stawtup(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_soc_dai *cpu_dai)
{
	stwuct kmb_i2s_info *kmb_i2s = snd_soc_dai_get_dwvdata(cpu_dai);
	stwuct snd_dmaengine_dai_dma_data *dma_data;

	if (kmb_i2s->use_pio)
		wetuwn 0;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		dma_data = &kmb_i2s->pway_dma_data;
	ewse
		dma_data = &kmb_i2s->captuwe_dma_data;

	snd_soc_dai_set_dma_data(cpu_dai, substweam, dma_data);

	wetuwn 0;
}

static int kmb_dai_hw_fwee(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_soc_dai *cpu_dai)
{
	stwuct kmb_i2s_info *kmb_i2s = snd_soc_dai_get_dwvdata(cpu_dai);
	/* I2S Pwogwamming sequence in Keem_Bay_VPU_DB_v1.1 */
	if (kmb_i2s->use_pio)
		kmb_i2s_cweaw_iwqs(kmb_i2s, substweam->stweam);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wwitew(0, kmb_i2s->i2s_base + ITEW);
	ewse
		wwitew(0, kmb_i2s->i2s_base + IWEW);

	if (kmb_i2s->use_pio)
		kmb_i2s_iwq_twiggew(kmb_i2s, substweam->stweam, 8, fawse);
	ewse
		kmb_i2s_disabwe_dma(kmb_i2s, substweam->stweam);

	if (!kmb_i2s->active) {
		wwitew(0, kmb_i2s->i2s_base + CEW);
		wwitew(0, kmb_i2s->i2s_base + IEW);
	}

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops kmb_dai_ops = {
	.pwobe		= kmb_pwobe,
	.stawtup	= kmb_dai_stawtup,
	.twiggew	= kmb_dai_twiggew,
	.hw_pawams	= kmb_dai_hw_pawams,
	.hw_fwee	= kmb_dai_hw_fwee,
	.pwepawe	= kmb_dai_pwepawe,
	.set_fmt	= kmb_set_dai_fmt,
};

static stwuct snd_soc_dai_dwivew intew_kmb_hdmi_dai[] = {
	{
		.name = "intew_kmb_hdmi_i2s",
		.pwayback = {
			.channews_min = 2,
			.channews_max = 2,
			.wates = SNDWV_PCM_WATE_48000,
			.wate_min = 48000,
			.wate_max = 48000,
			.fowmats = (SNDWV_PCM_FMTBIT_S16_WE |
				    SNDWV_PCM_FMTBIT_S24_WE |
				    SNDWV_PCM_FMTBIT_IEC958_SUBFWAME_WE),
		},
		.ops = &kmb_dai_ops,
	},
};

static stwuct snd_soc_dai_dwivew intew_kmb_i2s_dai[] = {
	{
		.name = "intew_kmb_i2s",
		.pwayback = {
			.channews_min = 2,
			.channews_max = 2,
			.wates = SNDWV_PCM_WATE_8000 |
				 SNDWV_PCM_WATE_16000 |
				 SNDWV_PCM_WATE_48000,
			.wate_min = 8000,
			.wate_max = 48000,
			.fowmats = (SNDWV_PCM_FMTBIT_S32_WE |
				    SNDWV_PCM_FMTBIT_S24_WE |
				    SNDWV_PCM_FMTBIT_S16_WE),
		},
		.captuwe = {
			.channews_min = 2,
			.channews_max = 2,
			.wates = SNDWV_PCM_WATE_8000 |
				 SNDWV_PCM_WATE_16000 |
				 SNDWV_PCM_WATE_48000,
			.wate_min = 8000,
			.wate_max = 48000,
			.fowmats = (SNDWV_PCM_FMTBIT_S32_WE |
				    SNDWV_PCM_FMTBIT_S24_WE |
				    SNDWV_PCM_FMTBIT_S16_WE),
		},
		.ops = &kmb_dai_ops,
	},
};

static stwuct snd_soc_dai_dwivew intew_kmb_tdm_dai[] = {
	{
		.name = "intew_kmb_tdm",
		.captuwe = {
			.channews_min = 4,
			.channews_max = 8,
			.wates = SNDWV_PCM_WATE_8000 |
				 SNDWV_PCM_WATE_16000 |
				 SNDWV_PCM_WATE_48000,
			.wate_min = 8000,
			.wate_max = 48000,
			.fowmats = (SNDWV_PCM_FMTBIT_S32_WE |
				    SNDWV_PCM_FMTBIT_S24_WE |
				    SNDWV_PCM_FMTBIT_S16_WE),
		},
		.ops = &kmb_dai_ops,
	},
};

static const stwuct of_device_id kmb_pwat_of_match[] = {
	{ .compatibwe = "intew,keembay-i2s", .data = &intew_kmb_i2s_dai},
	{ .compatibwe = "intew,keembay-hdmi-i2s", .data = &intew_kmb_hdmi_dai},
	{ .compatibwe = "intew,keembay-tdm", .data = &intew_kmb_tdm_dai},
	{}
};

static int kmb_pwat_dai_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct snd_soc_dai_dwivew *kmb_i2s_dai;
	stwuct device *dev = &pdev->dev;
	stwuct kmb_i2s_info *kmb_i2s;
	stwuct wesouwce *wes;
	int wet, iwq;
	u32 comp1_weg;

	kmb_i2s = devm_kzawwoc(dev, sizeof(*kmb_i2s), GFP_KEWNEW);
	if (!kmb_i2s)
		wetuwn -ENOMEM;

	kmb_i2s_dai = (stwuct snd_soc_dai_dwivew *)device_get_match_data(&pdev->dev);

	/* Pwepawe the wewated cwocks */
	kmb_i2s->cwk_apb = devm_cwk_get(dev, "apb_cwk");
	if (IS_EWW(kmb_i2s->cwk_apb)) {
		dev_eww(dev, "Faiwed to get apb cwock\n");
		wetuwn PTW_EWW(kmb_i2s->cwk_apb);
	}

	wet = cwk_pwepawe_enabwe(kmb_i2s->cwk_apb);
	if (wet < 0)
		wetuwn wet;

	wet = devm_add_action_ow_weset(dev, kmb_disabwe_cwk, kmb_i2s->cwk_apb);
	if (wet) {
		dev_eww(dev, "Faiwed to add cwk_apb weset action\n");
		wetuwn wet;
	}

	kmb_i2s->cwk_i2s = devm_cwk_get(dev, "osc");
	if (IS_EWW(kmb_i2s->cwk_i2s)) {
		dev_eww(dev, "Faiwed to get osc cwock\n");
		wetuwn PTW_EWW(kmb_i2s->cwk_i2s);
	}

	kmb_i2s->i2s_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(kmb_i2s->i2s_base))
		wetuwn PTW_EWW(kmb_i2s->i2s_base);

	kmb_i2s->pss_base = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(kmb_i2s->pss_base))
		wetuwn PTW_EWW(kmb_i2s->pss_base);

	kmb_i2s->dev = &pdev->dev;

	comp1_weg = weadw(kmb_i2s->i2s_base + I2S_COMP_PAWAM_1);

	kmb_i2s->fifo_th = (1 << COMP1_FIFO_DEPTH(comp1_weg)) / 2;

	kmb_i2s->use_pio = !(of_pwopewty_wead_boow(np, "dmas"));

	if (kmb_i2s->use_pio) {
		iwq = pwatfowm_get_iwq_optionaw(pdev, 0);
		if (iwq > 0) {
			wet = devm_wequest_iwq(dev, iwq, kmb_i2s_iwq_handwew, 0,
					       pdev->name, kmb_i2s);
			if (wet < 0) {
				dev_eww(dev, "faiwed to wequest iwq\n");
				wetuwn wet;
			}
		}
		wet = devm_snd_soc_wegistew_component(dev, &kmb_component,
						      kmb_i2s_dai, 1);
	} ewse {
		kmb_i2s->pway_dma_data.addw = wes->stawt + I2S_TXDMA;
		kmb_i2s->captuwe_dma_data.addw = wes->stawt + I2S_WXDMA;
		wet = snd_dmaengine_pcm_wegistew(&pdev->dev,
						 NUWW, 0);
		if (wet) {
			dev_eww(&pdev->dev, "couwd not wegistew dmaengine: %d\n",
				wet);
			wetuwn wet;
		}
		wet = devm_snd_soc_wegistew_component(dev, &kmb_component_dma,
						      kmb_i2s_dai, 1);
	}

	if (wet) {
		dev_eww(dev, "not abwe to wegistew dai\n");
		wetuwn wet;
	}

	/* To ensuwe none of the channews awe enabwed at boot up */
	kmb_i2s_disabwe_channews(kmb_i2s, SNDWV_PCM_STWEAM_PWAYBACK);
	kmb_i2s_disabwe_channews(kmb_i2s, SNDWV_PCM_STWEAM_CAPTUWE);

	dev_set_dwvdata(dev, kmb_i2s);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew kmb_pwat_dai_dwivew = {
	.dwivew		= {
		.name		= "kmb-pwat-dai",
		.of_match_tabwe = kmb_pwat_of_match,
	},
	.pwobe		= kmb_pwat_dai_pwobe,
};

moduwe_pwatfowm_dwivew(kmb_pwat_dai_dwivew);

MODUWE_DESCWIPTION("ASoC Intew KeemBay Pwatfowm dwivew");
MODUWE_AUTHOW("Sia Jee Heng <jee.heng.sia@intew.com>");
MODUWE_AUTHOW("Sit, Michaew Wei Hong <michaew.wei.hong.sit@intew.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:kmb_pwatfowm");
