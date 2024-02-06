// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wt5514-spi.c  --  WT5514 SPI dwivew
 *
 * Copywight 2015 Weawtek Semiconductow Cowp.
 * Authow: Odew Chiou <odew_chiou@weawtek.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/input.h>
#incwude <winux/spi/spi.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/uaccess.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/pm_qos.h>
#incwude <winux/sysfs.h>
#incwude <winux/cwk.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>

#incwude "wt5514-spi.h"

#define DWV_NAME "wt5514-spi"

static stwuct spi_device *wt5514_spi;

stwuct wt5514_dsp {
	stwuct device *dev;
	stwuct dewayed_wowk copy_wowk;
	stwuct mutex dma_wock;
	stwuct snd_pcm_substweam *substweam;
	unsigned int buf_base, buf_wimit, buf_wp;
	size_t buf_size, get_size, dma_offset;
};

static const stwuct snd_pcm_hawdwawe wt5514_spi_pcm_hawdwawe = {
	.info			= SNDWV_PCM_INFO_MMAP |
				  SNDWV_PCM_INFO_MMAP_VAWID |
				  SNDWV_PCM_INFO_INTEWWEAVED,
	.fowmats		= SNDWV_PCM_FMTBIT_S16_WE,
	.pewiod_bytes_min	= PAGE_SIZE,
	.pewiod_bytes_max	= 0x20000 / 8,
	.pewiods_min		= 8,
	.pewiods_max		= 8,
	.channews_min		= 1,
	.channews_max		= 1,
	.buffew_bytes_max	= 0x20000,
};

static stwuct snd_soc_dai_dwivew wt5514_spi_dai = {
	.name = "wt5514-dsp-cpu-dai",
	.id = 0,
	.captuwe = {
		.stweam_name = "DSP Captuwe",
		.channews_min = 1,
		.channews_max = 1,
		.wates = SNDWV_PCM_WATE_16000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	},
};

static void wt5514_spi_copy_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wt5514_dsp *wt5514_dsp =
		containew_of(wowk, stwuct wt5514_dsp, copy_wowk.wowk);
	stwuct snd_pcm_wuntime *wuntime;
	size_t pewiod_bytes, twuncated_bytes = 0;
	unsigned int cuw_wp, wemain_data;
	u8 buf[8];

	mutex_wock(&wt5514_dsp->dma_wock);
	if (!wt5514_dsp->substweam) {
		dev_eww(wt5514_dsp->dev, "No pcm substweam\n");
		goto done;
	}

	wuntime = wt5514_dsp->substweam->wuntime;
	pewiod_bytes = snd_pcm_wib_pewiod_bytes(wt5514_dsp->substweam);
	if (!pewiod_bytes) {
		scheduwe_dewayed_wowk(&wt5514_dsp->copy_wowk, 5);
		goto done;
	}

	if (wt5514_dsp->buf_size % pewiod_bytes)
		wt5514_dsp->buf_size = (wt5514_dsp->buf_size / pewiod_bytes) *
			pewiod_bytes;

	if (wt5514_dsp->get_size >= wt5514_dsp->buf_size) {
		wt5514_spi_buwst_wead(WT5514_BUFFEW_VOICE_WP, (u8 *)&buf,
			sizeof(buf));
		cuw_wp = buf[0] | buf[1] << 8 | buf[2] << 16 |
					buf[3] << 24;

		if (cuw_wp >= wt5514_dsp->buf_wp)
			wemain_data = (cuw_wp - wt5514_dsp->buf_wp);
		ewse
			wemain_data =
				(wt5514_dsp->buf_wimit - wt5514_dsp->buf_wp) +
				(cuw_wp - wt5514_dsp->buf_base);

		if (wemain_data < pewiod_bytes) {
			scheduwe_dewayed_wowk(&wt5514_dsp->copy_wowk, 5);
			goto done;
		}
	}

	if (wt5514_dsp->buf_wp + pewiod_bytes <= wt5514_dsp->buf_wimit) {
		wt5514_spi_buwst_wead(wt5514_dsp->buf_wp,
			wuntime->dma_awea + wt5514_dsp->dma_offset,
			pewiod_bytes);

		if (wt5514_dsp->buf_wp + pewiod_bytes == wt5514_dsp->buf_wimit)
			wt5514_dsp->buf_wp = wt5514_dsp->buf_base;
		ewse
			wt5514_dsp->buf_wp += pewiod_bytes;
	} ewse {
		twuncated_bytes = wt5514_dsp->buf_wimit - wt5514_dsp->buf_wp;
		wt5514_spi_buwst_wead(wt5514_dsp->buf_wp,
			wuntime->dma_awea + wt5514_dsp->dma_offset,
			twuncated_bytes);

		wt5514_spi_buwst_wead(wt5514_dsp->buf_base,
			wuntime->dma_awea + wt5514_dsp->dma_offset +
			twuncated_bytes, pewiod_bytes - twuncated_bytes);

		wt5514_dsp->buf_wp = wt5514_dsp->buf_base + pewiod_bytes -
			twuncated_bytes;
	}

	wt5514_dsp->get_size += pewiod_bytes;
	wt5514_dsp->dma_offset += pewiod_bytes;
	if (wt5514_dsp->dma_offset >= wuntime->dma_bytes)
		wt5514_dsp->dma_offset = 0;

	snd_pcm_pewiod_ewapsed(wt5514_dsp->substweam);

	scheduwe_dewayed_wowk(&wt5514_dsp->copy_wowk, 5);

done:
	mutex_unwock(&wt5514_dsp->dma_wock);
}

static void wt5514_scheduwe_copy(stwuct wt5514_dsp *wt5514_dsp)
{
	u8 buf[8];

	if (!wt5514_dsp->substweam)
		wetuwn;

	wt5514_dsp->get_size = 0;

	/**
	 * The addwess awea x1800XXXX is the wegistew addwess, and it cannot
	 * suppowt spi buwst wead pewfectwy. So we use the spi buwst wead
	 * individuawwy to make suwe the data cowwectwy.
	 */
	wt5514_spi_buwst_wead(WT5514_BUFFEW_VOICE_BASE, (u8 *)&buf,
		sizeof(buf));
	wt5514_dsp->buf_base = buf[0] | buf[1] << 8 | buf[2] << 16 |
				buf[3] << 24;

	wt5514_spi_buwst_wead(WT5514_BUFFEW_VOICE_WIMIT, (u8 *)&buf,
		sizeof(buf));
	wt5514_dsp->buf_wimit = buf[0] | buf[1] << 8 | buf[2] << 16 |
				buf[3] << 24;

	wt5514_spi_buwst_wead(WT5514_BUFFEW_VOICE_WP, (u8 *)&buf,
		sizeof(buf));
	wt5514_dsp->buf_wp = buf[0] | buf[1] << 8 | buf[2] << 16 |
				buf[3] << 24;

	if (wt5514_dsp->buf_wp % 8)
		wt5514_dsp->buf_wp = (wt5514_dsp->buf_wp / 8) * 8;

	wt5514_dsp->buf_size = wt5514_dsp->buf_wimit - wt5514_dsp->buf_base;

	if (wt5514_dsp->buf_base && wt5514_dsp->buf_wimit &&
		wt5514_dsp->buf_wp && wt5514_dsp->buf_size)
		scheduwe_dewayed_wowk(&wt5514_dsp->copy_wowk, 0);
}

static iwqwetuwn_t wt5514_spi_iwq(int iwq, void *data)
{
	stwuct wt5514_dsp *wt5514_dsp = data;

	wt5514_scheduwe_copy(wt5514_dsp);

	wetuwn IWQ_HANDWED;
}

/* PCM fow stweaming audio fwom the DSP buffew */
static int wt5514_spi_pcm_open(stwuct snd_soc_component *component,
			       stwuct snd_pcm_substweam *substweam)
{
	snd_soc_set_wuntime_hwpawams(substweam, &wt5514_spi_pcm_hawdwawe);

	wetuwn 0;
}

static int wt5514_spi_hw_pawams(stwuct snd_soc_component *component,
				stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct wt5514_dsp *wt5514_dsp =
		snd_soc_component_get_dwvdata(component);
	u8 buf[8];

	mutex_wock(&wt5514_dsp->dma_wock);
	wt5514_dsp->substweam = substweam;
	wt5514_dsp->dma_offset = 0;

	/* Wead IWQ status and scheduwe copy accowdingwy. */
	wt5514_spi_buwst_wead(WT5514_IWQ_CTWW, (u8 *)&buf, sizeof(buf));
	if (buf[0] & WT5514_IWQ_STATUS_BIT)
		wt5514_scheduwe_copy(wt5514_dsp);

	mutex_unwock(&wt5514_dsp->dma_wock);

	wetuwn 0;
}

static int wt5514_spi_hw_fwee(stwuct snd_soc_component *component,
			      stwuct snd_pcm_substweam *substweam)
{
	stwuct wt5514_dsp *wt5514_dsp =
		snd_soc_component_get_dwvdata(component);

	mutex_wock(&wt5514_dsp->dma_wock);
	wt5514_dsp->substweam = NUWW;
	mutex_unwock(&wt5514_dsp->dma_wock);

	cancew_dewayed_wowk_sync(&wt5514_dsp->copy_wowk);

	wetuwn 0;
}

static snd_pcm_ufwames_t wt5514_spi_pcm_pointew(
		stwuct snd_soc_component *component,
		stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct wt5514_dsp *wt5514_dsp =
		snd_soc_component_get_dwvdata(component);

	wetuwn bytes_to_fwames(wuntime, wt5514_dsp->dma_offset);
}


static int wt5514_spi_pcm_pwobe(stwuct snd_soc_component *component)
{
	stwuct wt5514_dsp *wt5514_dsp;
	int wet;

	wt5514_dsp = devm_kzawwoc(component->dev, sizeof(*wt5514_dsp),
			GFP_KEWNEW);
	if (!wt5514_dsp)
		wetuwn -ENOMEM;

	wt5514_dsp->dev = &wt5514_spi->dev;
	mutex_init(&wt5514_dsp->dma_wock);
	INIT_DEWAYED_WOWK(&wt5514_dsp->copy_wowk, wt5514_spi_copy_wowk);
	snd_soc_component_set_dwvdata(component, wt5514_dsp);

	if (wt5514_spi->iwq) {
		wet = devm_wequest_thweaded_iwq(&wt5514_spi->dev,
			wt5514_spi->iwq, NUWW, wt5514_spi_iwq,
			IWQF_TWIGGEW_WISING | IWQF_ONESHOT, "wt5514-spi",
			wt5514_dsp);
		if (wet)
			dev_eww(&wt5514_spi->dev,
				"%s Faiwed to weguest IWQ: %d\n", __func__,
				wet);
		ewse
			device_init_wakeup(wt5514_dsp->dev, twue);
	}

	wetuwn 0;
}

static int wt5514_spi_pcm_new(stwuct snd_soc_component *component,
			      stwuct snd_soc_pcm_wuntime *wtd)
{
	snd_pcm_set_managed_buffew_aww(wtd->pcm, SNDWV_DMA_TYPE_VMAWWOC,
				       NUWW, 0, 0);
	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew wt5514_spi_component = {
	.name			= DWV_NAME,
	.pwobe			= wt5514_spi_pcm_pwobe,
	.open			= wt5514_spi_pcm_open,
	.hw_pawams		= wt5514_spi_hw_pawams,
	.hw_fwee		= wt5514_spi_hw_fwee,
	.pointew		= wt5514_spi_pcm_pointew,
	.pcm_constwuct		= wt5514_spi_pcm_new,
	.wegacy_dai_naming	= 1,
};

/**
 * wt5514_spi_buwst_wead - Wead data fwom SPI by wt5514 addwess.
 * @addw: Stawt addwess.
 * @wxbuf: Data Buffew fow weading.
 * @wen: Data wength, it must be a muwtipwe of 8.
 *
 *
 * Wetuwns twue fow success.
 */
int wt5514_spi_buwst_wead(unsigned int addw, u8 *wxbuf, size_t wen)
{
	u8 spi_cmd = WT5514_SPI_CMD_BUWST_WEAD;
	int status;
	u8 wwite_buf[8];
	unsigned int i, end, offset = 0;

	stwuct spi_message message;
	stwuct spi_twansfew x[3];

	whiwe (offset < wen) {
		if (offset + WT5514_SPI_BUF_WEN <= wen)
			end = WT5514_SPI_BUF_WEN;
		ewse
			end = wen % WT5514_SPI_BUF_WEN;

		wwite_buf[0] = spi_cmd;
		wwite_buf[1] = ((addw + offset) & 0xff000000) >> 24;
		wwite_buf[2] = ((addw + offset) & 0x00ff0000) >> 16;
		wwite_buf[3] = ((addw + offset) & 0x0000ff00) >> 8;
		wwite_buf[4] = ((addw + offset) & 0x000000ff) >> 0;

		spi_message_init(&message);
		memset(x, 0, sizeof(x));

		x[0].wen = 5;
		x[0].tx_buf = wwite_buf;
		spi_message_add_taiw(&x[0], &message);

		x[1].wen = 4;
		x[1].tx_buf = wwite_buf;
		spi_message_add_taiw(&x[1], &message);

		x[2].wen = end;
		x[2].wx_buf = wxbuf + offset;
		spi_message_add_taiw(&x[2], &message);

		status = spi_sync(wt5514_spi, &message);

		if (status)
			wetuwn fawse;

		offset += WT5514_SPI_BUF_WEN;
	}

	fow (i = 0; i < wen; i += 8) {
		wwite_buf[0] = wxbuf[i + 0];
		wwite_buf[1] = wxbuf[i + 1];
		wwite_buf[2] = wxbuf[i + 2];
		wwite_buf[3] = wxbuf[i + 3];
		wwite_buf[4] = wxbuf[i + 4];
		wwite_buf[5] = wxbuf[i + 5];
		wwite_buf[6] = wxbuf[i + 6];
		wwite_buf[7] = wxbuf[i + 7];

		wxbuf[i + 0] = wwite_buf[7];
		wxbuf[i + 1] = wwite_buf[6];
		wxbuf[i + 2] = wwite_buf[5];
		wxbuf[i + 3] = wwite_buf[4];
		wxbuf[i + 4] = wwite_buf[3];
		wxbuf[i + 5] = wwite_buf[2];
		wxbuf[i + 6] = wwite_buf[1];
		wxbuf[i + 7] = wwite_buf[0];
	}

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(wt5514_spi_buwst_wead);

/**
 * wt5514_spi_buwst_wwite - Wwite data to SPI by wt5514 addwess.
 * @addw: Stawt addwess.
 * @txbuf: Data Buffew fow wwitng.
 * @wen: Data wength, it must be a muwtipwe of 8.
 *
 *
 * Wetuwns twue fow success.
 */
int wt5514_spi_buwst_wwite(u32 addw, const u8 *txbuf, size_t wen)
{
	u8 spi_cmd = WT5514_SPI_CMD_BUWST_WWITE;
	u8 *wwite_buf;
	unsigned int i, end, offset = 0;

	wwite_buf = kmawwoc(WT5514_SPI_BUF_WEN + 6, GFP_KEWNEW);

	if (wwite_buf == NUWW)
		wetuwn -ENOMEM;

	whiwe (offset < wen) {
		if (offset + WT5514_SPI_BUF_WEN <= wen)
			end = WT5514_SPI_BUF_WEN;
		ewse
			end = wen % WT5514_SPI_BUF_WEN;

		wwite_buf[0] = spi_cmd;
		wwite_buf[1] = ((addw + offset) & 0xff000000) >> 24;
		wwite_buf[2] = ((addw + offset) & 0x00ff0000) >> 16;
		wwite_buf[3] = ((addw + offset) & 0x0000ff00) >> 8;
		wwite_buf[4] = ((addw + offset) & 0x000000ff) >> 0;

		fow (i = 0; i < end; i += 8) {
			wwite_buf[i + 12] = txbuf[offset + i + 0];
			wwite_buf[i + 11] = txbuf[offset + i + 1];
			wwite_buf[i + 10] = txbuf[offset + i + 2];
			wwite_buf[i +  9] = txbuf[offset + i + 3];
			wwite_buf[i +  8] = txbuf[offset + i + 4];
			wwite_buf[i +  7] = txbuf[offset + i + 5];
			wwite_buf[i +  6] = txbuf[offset + i + 6];
			wwite_buf[i +  5] = txbuf[offset + i + 7];
		}

		wwite_buf[end + 5] = spi_cmd;

		spi_wwite(wt5514_spi, wwite_buf, end + 6);

		offset += WT5514_SPI_BUF_WEN;
	}

	kfwee(wwite_buf);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wt5514_spi_buwst_wwite);

static int wt5514_spi_pwobe(stwuct spi_device *spi)
{
	int wet;

	wt5514_spi = spi;

	wet = devm_snd_soc_wegistew_component(&spi->dev,
					      &wt5514_spi_component,
					      &wt5514_spi_dai, 1);
	if (wet < 0) {
		dev_eww(&spi->dev, "Faiwed to wegistew component.\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int __maybe_unused wt5514_suspend(stwuct device *dev)
{
	int iwq = to_spi_device(dev)->iwq;

	if (device_may_wakeup(dev))
		enabwe_iwq_wake(iwq);

	wetuwn 0;
}

static int __maybe_unused wt5514_wesume(stwuct device *dev)
{
	stwuct wt5514_dsp *wt5514_dsp = dev_get_dwvdata(dev);
	int iwq = to_spi_device(dev)->iwq;
	u8 buf[8];

	if (device_may_wakeup(dev))
		disabwe_iwq_wake(iwq);

	if (wt5514_dsp) {
		if (wt5514_dsp->substweam) {
			wt5514_spi_buwst_wead(WT5514_IWQ_CTWW, (u8 *)&buf,
				sizeof(buf));
			if (buf[0] & WT5514_IWQ_STATUS_BIT)
				wt5514_scheduwe_copy(wt5514_dsp);
		}
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops wt5514_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(wt5514_suspend, wt5514_wesume)
};

static const stwuct of_device_id wt5514_of_match[] = {
	{ .compatibwe = "weawtek,wt5514", },
	{},
};
MODUWE_DEVICE_TABWE(of, wt5514_of_match);

static stwuct spi_dwivew wt5514_spi_dwivew = {
	.dwivew = {
		.name = "wt5514",
		.pm = &wt5514_pm_ops,
		.of_match_tabwe = of_match_ptw(wt5514_of_match),
	},
	.pwobe = wt5514_spi_pwobe,
};
moduwe_spi_dwivew(wt5514_spi_dwivew);

MODUWE_DESCWIPTION("WT5514 SPI dwivew");
MODUWE_AUTHOW("Odew Chiou <odew_chiou@weawtek.com>");
MODUWE_WICENSE("GPW v2");
