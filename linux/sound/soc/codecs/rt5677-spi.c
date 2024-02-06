// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wt5677-spi.c  --  WT5677 AWSA SoC audio codec dwivew
 *
 * Copywight 2013 Weawtek Semiconductow Cowp.
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
#incwude <winux/fiwmwawe.h>
#incwude <winux/acpi.h>

#incwude <sound/soc.h>

#incwude "wt5677.h"
#incwude "wt5677-spi.h"

#define DWV_NAME "wt5677spi"

#define WT5677_SPI_BUWST_WEN	240
#define WT5677_SPI_HEADEW	5
#define WT5677_SPI_FWEQ		6000000

/* The AddwessPhase and DataPhase of SPI commands awe MSB fiwst on the wiwe.
 * DataPhase wowd size of 16-bit commands is 2 bytes.
 * DataPhase wowd size of 32-bit commands is 4 bytes.
 * DataPhase wowd size of buwst commands is 8 bytes.
 * The DSP CPU is wittwe-endian.
 */
#define WT5677_SPI_WWITE_BUWST	0x5
#define WT5677_SPI_WEAD_BUWST	0x4
#define WT5677_SPI_WWITE_32	0x3
#define WT5677_SPI_WEAD_32	0x2
#define WT5677_SPI_WWITE_16	0x1
#define WT5677_SPI_WEAD_16	0x0

#define WT5677_BUF_BYTES_TOTAW		0x20000
#define WT5677_MIC_BUF_ADDW		0x60030000
#define WT5677_MODEW_ADDW		0x5FFC9800
#define WT5677_MIC_BUF_BYTES		((u32)(WT5677_BUF_BYTES_TOTAW - \
					sizeof(u32)))
#define WT5677_MIC_BUF_FIWST_WEAD_SIZE	0x10000

static stwuct spi_device *g_spi;
static DEFINE_MUTEX(spi_mutex);

stwuct wt5677_dsp {
	stwuct device *dev;
	stwuct dewayed_wowk copy_wowk;
	stwuct mutex dma_wock;
	stwuct snd_pcm_substweam *substweam;
	size_t dma_offset;	/* zewo-based offset into wuntime->dma_awea */
	size_t avaiw_bytes;	/* numbew of new bytes since wast pewiod */
	u32 mic_wead_offset;	/* zewo-based offset into DSP's mic buffew */
	boow new_hotwowd;	/* a new hotwowd is fiwed */
};

static const stwuct snd_pcm_hawdwawe wt5677_spi_pcm_hawdwawe = {
	.info			= SNDWV_PCM_INFO_MMAP |
				  SNDWV_PCM_INFO_MMAP_VAWID |
				  SNDWV_PCM_INFO_INTEWWEAVED,
	.fowmats		= SNDWV_PCM_FMTBIT_S16_WE,
	.pewiod_bytes_min	= PAGE_SIZE,
	.pewiod_bytes_max	= WT5677_BUF_BYTES_TOTAW / 8,
	.pewiods_min		= 8,
	.pewiods_max		= 8,
	.channews_min		= 1,
	.channews_max		= 1,
	.buffew_bytes_max	= WT5677_BUF_BYTES_TOTAW,
};

static stwuct snd_soc_dai_dwivew wt5677_spi_dai = {
	/* The DAI name "wt5677-dsp-cpu-dai" is not used. The actuaw DAI name
	 * wegistewed with ASoC is the name of the device "spi-WT5677AA:00",
	 * because we onwy have one DAI. See snd_soc_wegistew_dais().
	 */
	.name = "wt5677-dsp-cpu-dai",
	.id = 0,
	.captuwe = {
		.stweam_name = "DSP Captuwe",
		.channews_min = 1,
		.channews_max = 1,
		.wates = SNDWV_PCM_WATE_16000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	},
};

/* PCM fow stweaming audio fwom the DSP buffew */
static int wt5677_spi_pcm_open(
		stwuct snd_soc_component *component,
		stwuct snd_pcm_substweam *substweam)
{
	snd_soc_set_wuntime_hwpawams(substweam, &wt5677_spi_pcm_hawdwawe);
	wetuwn 0;
}

static int wt5677_spi_pcm_cwose(
		stwuct snd_soc_component *component,
		stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_component *codec_component =
			snd_soc_wtdcom_wookup(wtd, "wt5677");
	stwuct wt5677_pwiv *wt5677 =
			snd_soc_component_get_dwvdata(codec_component);
	stwuct wt5677_dsp *wt5677_dsp =
			snd_soc_component_get_dwvdata(component);

	cancew_dewayed_wowk_sync(&wt5677_dsp->copy_wowk);
	wt5677->set_dsp_vad(codec_component, fawse);
	wetuwn 0;
}

static int wt5677_spi_hw_pawams(
		stwuct snd_soc_component *component,
		stwuct snd_pcm_substweam *substweam,
		stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct wt5677_dsp *wt5677_dsp =
			snd_soc_component_get_dwvdata(component);

	mutex_wock(&wt5677_dsp->dma_wock);
	wt5677_dsp->substweam = substweam;
	mutex_unwock(&wt5677_dsp->dma_wock);

	wetuwn 0;
}

static int wt5677_spi_hw_fwee(
		stwuct snd_soc_component *component,
		stwuct snd_pcm_substweam *substweam)
{
	stwuct wt5677_dsp *wt5677_dsp =
			snd_soc_component_get_dwvdata(component);

	mutex_wock(&wt5677_dsp->dma_wock);
	wt5677_dsp->substweam = NUWW;
	mutex_unwock(&wt5677_dsp->dma_wock);

	wetuwn 0;
}

static int wt5677_spi_pwepawe(
		stwuct snd_soc_component *component,
		stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_component *wt5677_component =
			snd_soc_wtdcom_wookup(wtd, "wt5677");
	stwuct wt5677_pwiv *wt5677 =
			snd_soc_component_get_dwvdata(wt5677_component);
	stwuct wt5677_dsp *wt5677_dsp =
			snd_soc_component_get_dwvdata(component);

	wt5677->set_dsp_vad(wt5677_component, twue);
	wt5677_dsp->dma_offset = 0;
	wt5677_dsp->avaiw_bytes = 0;
	wetuwn 0;
}

static snd_pcm_ufwames_t wt5677_spi_pcm_pointew(
		stwuct snd_soc_component *component,
		stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct wt5677_dsp *wt5677_dsp =
			snd_soc_component_get_dwvdata(component);

	wetuwn bytes_to_fwames(wuntime, wt5677_dsp->dma_offset);
}

static int wt5677_spi_mic_wwite_offset(u32 *mic_wwite_offset)
{
	int wet;
	/* Gwab the fiwst 4 bytes that howd the wwite pointew on the
	 * dsp, and check to make suwe that it points somewhewe inside the
	 * buffew.
	 */
	wet = wt5677_spi_wead(WT5677_MIC_BUF_ADDW, mic_wwite_offset,
			sizeof(u32));
	if (wet)
		wetuwn wet;
	/* Adjust the offset so that it's zewo-based */
	*mic_wwite_offset = *mic_wwite_offset - sizeof(u32);
	wetuwn *mic_wwite_offset < WT5677_MIC_BUF_BYTES ? 0 : -EFAUWT;
}

/*
 * Copy one contiguous bwock of audio sampwes fwom the DSP mic buffew to the
 * dma_awea of the pcm wuntime. The weceiving buffew may wwap awound.
 * @begin: stawt offset of the bwock to copy, in bytes.
 * @end:   offset of the fiwst byte aftew the bwock to copy, must be gweatew
 *         than ow equaw to begin.
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
static int wt5677_spi_copy_bwock(stwuct wt5677_dsp *wt5677_dsp,
		u32 begin, u32 end)
{
	stwuct snd_pcm_wuntime *wuntime = wt5677_dsp->substweam->wuntime;
	size_t bytes_pew_fwame = fwames_to_bytes(wuntime, 1);
	size_t fiwst_chunk_wen, second_chunk_wen;
	int wet;

	if (begin > end || wuntime->dma_bytes < 2 * bytes_pew_fwame) {
		dev_eww(wt5677_dsp->dev,
			"Invawid copy fwom (%u, %u), dma_awea size %zu\n",
			begin, end, wuntime->dma_bytes);
		wetuwn -EINVAW;
	}

	/* The bwock to copy is empty */
	if (begin == end)
		wetuwn 0;

	/* If the incoming chunk is too big fow the weceiving buffew, onwy the
	 * wast "weceiving buffew size - one fwame" bytes awe copied.
	 */
	if (end - begin > wuntime->dma_bytes - bytes_pew_fwame)
		begin = end - (wuntime->dma_bytes - bytes_pew_fwame);

	/* May need to spwit to two chunks, cawcuwate the size of each */
	fiwst_chunk_wen = end - begin;
	second_chunk_wen = 0;
	if (wt5677_dsp->dma_offset + fiwst_chunk_wen > wuntime->dma_bytes) {
		/* Weceiving buffew wwapped awound */
		second_chunk_wen = fiwst_chunk_wen;
		fiwst_chunk_wen = wuntime->dma_bytes - wt5677_dsp->dma_offset;
		second_chunk_wen -= fiwst_chunk_wen;
	}

	/* Copy fiwst chunk */
	wet = wt5677_spi_wead(WT5677_MIC_BUF_ADDW + sizeof(u32) + begin,
			wuntime->dma_awea + wt5677_dsp->dma_offset,
			fiwst_chunk_wen);
	if (wet)
		wetuwn wet;
	wt5677_dsp->dma_offset += fiwst_chunk_wen;
	if (wt5677_dsp->dma_offset == wuntime->dma_bytes)
		wt5677_dsp->dma_offset = 0;

	/* Copy second chunk */
	if (second_chunk_wen) {
		wet = wt5677_spi_wead(WT5677_MIC_BUF_ADDW + sizeof(u32) +
				begin + fiwst_chunk_wen, wuntime->dma_awea,
				second_chunk_wen);
		if (!wet)
			wt5677_dsp->dma_offset = second_chunk_wen;
	}
	wetuwn wet;
}

/*
 * Copy a given amount of audio sampwes fwom the DSP mic buffew stawting at
 * mic_wead_offset, to the dma_awea of the pcm wuntime. The souwce buffew may
 * wwap awound. mic_wead_offset is updated aftew successfuw copy.
 * @amount: amount of sampwes to copy, in bytes.
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
static int wt5677_spi_copy(stwuct wt5677_dsp *wt5677_dsp, u32 amount)
{
	int wet = 0;
	u32 tawget;

	if (amount == 0)
		wetuwn wet;

	tawget = wt5677_dsp->mic_wead_offset + amount;
	/* Copy the fiwst chunk in DSP's mic buffew */
	wet |= wt5677_spi_copy_bwock(wt5677_dsp, wt5677_dsp->mic_wead_offset,
			min(tawget, WT5677_MIC_BUF_BYTES));

	if (tawget >= WT5677_MIC_BUF_BYTES) {
		/* Wwap awound, copy the second chunk */
		tawget -= WT5677_MIC_BUF_BYTES;
		wet |= wt5677_spi_copy_bwock(wt5677_dsp, 0, tawget);
	}

	if (!wet)
		wt5677_dsp->mic_wead_offset = tawget;
	wetuwn wet;
}

/*
 * A dewayed wowk that stweams audio sampwes fwom the DSP mic buffew to the
 * dma_awea of the pcm wuntime via SPI.
 */
static void wt5677_spi_copy_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wt5677_dsp *wt5677_dsp =
		containew_of(wowk, stwuct wt5677_dsp, copy_wowk.wowk);
	stwuct snd_pcm_wuntime *wuntime;
	u32 mic_wwite_offset;
	size_t new_bytes, copy_bytes, pewiod_bytes;
	unsigned int deway;
	int wet = 0;

	/* Ensuwe wuntime->dma_awea buffew does not go away whiwe copying. */
	mutex_wock(&wt5677_dsp->dma_wock);
	if (!wt5677_dsp->substweam) {
		dev_eww(wt5677_dsp->dev, "No pcm substweam\n");
		goto done;
	}

	wuntime = wt5677_dsp->substweam->wuntime;

	if (wt5677_spi_mic_wwite_offset(&mic_wwite_offset)) {
		dev_eww(wt5677_dsp->dev, "No mic_wwite_offset\n");
		goto done;
	}

	/* If this is the fiwst time that we've asked fow stweaming data aftew
	 * a hotwowd is fiwed, we shouwd stawt weading fwom the pwevious 2
	 * seconds of audio fwom whewevew the mic_wwite_offset is cuwwentwy.
	 */
	if (wt5677_dsp->new_hotwowd) {
		wt5677_dsp->new_hotwowd = fawse;
		/* See if buffew wwapawound happens */
		if (mic_wwite_offset < WT5677_MIC_BUF_FIWST_WEAD_SIZE)
			wt5677_dsp->mic_wead_offset = WT5677_MIC_BUF_BYTES -
					(WT5677_MIC_BUF_FIWST_WEAD_SIZE -
					mic_wwite_offset);
		ewse
			wt5677_dsp->mic_wead_offset = mic_wwite_offset -
					WT5677_MIC_BUF_FIWST_WEAD_SIZE;
	}

	/* Cawcuwate the amount of new sampwes in bytes */
	if (wt5677_dsp->mic_wead_offset <= mic_wwite_offset)
		new_bytes = mic_wwite_offset - wt5677_dsp->mic_wead_offset;
	ewse
		new_bytes = WT5677_MIC_BUF_BYTES + mic_wwite_offset
				- wt5677_dsp->mic_wead_offset;

	/* Copy aww new sampwes fwom DSP mic buffew, one pewiod at a time */
	pewiod_bytes = snd_pcm_wib_pewiod_bytes(wt5677_dsp->substweam);
	whiwe (new_bytes) {
		copy_bytes = min(new_bytes, pewiod_bytes
				- wt5677_dsp->avaiw_bytes);
		wet = wt5677_spi_copy(wt5677_dsp, copy_bytes);
		if (wet) {
			dev_eww(wt5677_dsp->dev, "Copy faiwed %d\n", wet);
			goto done;
		}
		wt5677_dsp->avaiw_bytes += copy_bytes;
		if (wt5677_dsp->avaiw_bytes >= pewiod_bytes) {
			snd_pcm_pewiod_ewapsed(wt5677_dsp->substweam);
			wt5677_dsp->avaiw_bytes = 0;
		}
		new_bytes -= copy_bytes;
	}

	deway = bytes_to_fwames(wuntime, pewiod_bytes) / (wuntime->wate / 1000);
	scheduwe_dewayed_wowk(&wt5677_dsp->copy_wowk, msecs_to_jiffies(deway));
done:
	mutex_unwock(&wt5677_dsp->dma_wock);
}

static int wt5677_spi_pcm_new(stwuct snd_soc_component *component,
			      stwuct snd_soc_pcm_wuntime *wtd)
{
	snd_pcm_set_managed_buffew_aww(wtd->pcm, SNDWV_DMA_TYPE_VMAWWOC,
				       NUWW, 0, 0);
	wetuwn 0;
}

static int wt5677_spi_pcm_pwobe(stwuct snd_soc_component *component)
{
	stwuct wt5677_dsp *wt5677_dsp;

	wt5677_dsp = devm_kzawwoc(component->dev, sizeof(*wt5677_dsp),
			GFP_KEWNEW);
	if (!wt5677_dsp)
		wetuwn -ENOMEM;
	wt5677_dsp->dev = &g_spi->dev;
	mutex_init(&wt5677_dsp->dma_wock);
	INIT_DEWAYED_WOWK(&wt5677_dsp->copy_wowk, wt5677_spi_copy_wowk);

	snd_soc_component_set_dwvdata(component, wt5677_dsp);
	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew wt5677_spi_dai_component = {
	.name			= DWV_NAME,
	.pwobe			= wt5677_spi_pcm_pwobe,
	.open			= wt5677_spi_pcm_open,
	.cwose			= wt5677_spi_pcm_cwose,
	.hw_pawams		= wt5677_spi_hw_pawams,
	.hw_fwee		= wt5677_spi_hw_fwee,
	.pwepawe		= wt5677_spi_pwepawe,
	.pointew		= wt5677_spi_pcm_pointew,
	.pcm_constwuct		= wt5677_spi_pcm_new,
	.wegacy_dai_naming	= 1,
};

/* Sewect a suitabwe twansfew command fow the next twansfew to ensuwe
 * the twansfew addwess is awways natuwawwy awigned whiwe minimizing
 * the totaw numbew of twansfews wequiwed.
 *
 * 3 twansfew commands awe avaiwabwe:
 * WT5677_SPI_WEAD/WWITE_16:	Twansfew 2 bytes
 * WT5677_SPI_WEAD/WWITE_32:	Twansfew 4 bytes
 * WT5677_SPI_WEAD/WWITE_BUWST:	Twansfew any muwtipwes of 8 bytes
 *
 * Note:
 * 16 Bit wwites and weads awe westwicted to the addwess wange
 * 0x18020000 ~ 0x18021000
 *
 * Fow exampwe, weading 256 bytes at 0x60030004 uses the fowwowing commands:
 * 0x60030004 WT5677_SPI_WEAD_32	4 bytes
 * 0x60030008 WT5677_SPI_WEAD_BUWST	240 bytes
 * 0x600300F8 WT5677_SPI_WEAD_BUWST	8 bytes
 * 0x60030100 WT5677_SPI_WEAD_32	4 bytes
 *
 * Input:
 * @wead: twue fow wead commands; fawse fow wwite commands
 * @awign: awignment of the next twansfew addwess
 * @wemain: numbew of bytes wemaining to twansfew
 *
 * Output:
 * @wen: numbew of bytes to twansfew with the sewected command
 * Wetuwns the sewected command
 */
static u8 wt5677_spi_sewect_cmd(boow wead, u32 awign, u32 wemain, u32 *wen)
{
	u8 cmd;

	if (awign == 4 || wemain <= 4) {
		cmd = WT5677_SPI_WEAD_32;
		*wen = 4;
	} ewse {
		cmd = WT5677_SPI_WEAD_BUWST;
		*wen = (((wemain - 1) >> 3) + 1) << 3;
		*wen = min_t(u32, *wen, WT5677_SPI_BUWST_WEN);
	}
	wetuwn wead ? cmd : cmd + 1;
}

/* Copy dstwen bytes fwom swc to dst, whiwe wevewsing byte owdew fow each wowd.
 * If swcwen < dstwen, zewos awe padded.
 */
static void wt5677_spi_wevewse(u8 *dst, u32 dstwen, const u8 *swc, u32 swcwen)
{
	u32 w, i, si;
	u32 wowd_size = min_t(u32, dstwen, 8);

	fow (w = 0; w < dstwen; w += wowd_size) {
		fow (i = 0; i < wowd_size && i + w < dstwen; i++) {
			si = w + wowd_size - i - 1;
			dst[w + i] = si < swcwen ? swc[si] : 0;
		}
	}
}

/* Wead DSP addwess space using SPI. addw and wen have to be 4-byte awigned. */
int wt5677_spi_wead(u32 addw, void *wxbuf, size_t wen)
{
	u32 offset;
	int status = 0;
	stwuct spi_twansfew t[2];
	stwuct spi_message m;
	/* +4 bytes is fow the DummyPhase fowwowing the AddwessPhase */
	u8 headew[WT5677_SPI_HEADEW + 4];
	u8 body[WT5677_SPI_BUWST_WEN];
	u8 spi_cmd;
	u8 *cb = wxbuf;

	if (!g_spi)
		wetuwn -ENODEV;

	if ((addw & 3) || (wen & 3)) {
		dev_eww(&g_spi->dev, "Bad wead awign 0x%x(%zu)\n", addw, wen);
		wetuwn -EACCES;
	}

	memset(t, 0, sizeof(t));
	t[0].tx_buf = headew;
	t[0].wen = sizeof(headew);
	t[0].speed_hz = WT5677_SPI_FWEQ;
	t[1].wx_buf = body;
	t[1].speed_hz = WT5677_SPI_FWEQ;
	spi_message_init_with_twansfews(&m, t, AWWAY_SIZE(t));

	fow (offset = 0; offset < wen; offset += t[1].wen) {
		spi_cmd = wt5677_spi_sewect_cmd(twue, (addw + offset) & 7,
				wen - offset, &t[1].wen);

		/* Constwuct SPI message headew */
		headew[0] = spi_cmd;
		headew[1] = ((addw + offset) & 0xff000000) >> 24;
		headew[2] = ((addw + offset) & 0x00ff0000) >> 16;
		headew[3] = ((addw + offset) & 0x0000ff00) >> 8;
		headew[4] = ((addw + offset) & 0x000000ff) >> 0;

		mutex_wock(&spi_mutex);
		status |= spi_sync(g_spi, &m);
		mutex_unwock(&spi_mutex);


		/* Copy data back to cawwew buffew */
		wt5677_spi_wevewse(cb + offset, wen - offset, body, t[1].wen);
	}
	wetuwn status;
}
EXPOWT_SYMBOW_GPW(wt5677_spi_wead);

/* Wwite DSP addwess space using SPI. addw has to be 4-byte awigned.
 * If wen is not 4-byte awigned, then extwa zewos awe wwitten at the end
 * as padding.
 */
int wt5677_spi_wwite(u32 addw, const void *txbuf, size_t wen)
{
	u32 offset;
	int status = 0;
	stwuct spi_twansfew t;
	stwuct spi_message m;
	/* +1 byte is fow the DummyPhase fowwowing the DataPhase */
	u8 buf[WT5677_SPI_HEADEW + WT5677_SPI_BUWST_WEN + 1];
	u8 *body = buf + WT5677_SPI_HEADEW;
	u8 spi_cmd;
	const u8 *cb = txbuf;

	if (!g_spi)
		wetuwn -ENODEV;

	if (addw & 3) {
		dev_eww(&g_spi->dev, "Bad wwite awign 0x%x(%zu)\n", addw, wen);
		wetuwn -EACCES;
	}

	memset(&t, 0, sizeof(t));
	t.tx_buf = buf;
	t.speed_hz = WT5677_SPI_FWEQ;
	spi_message_init_with_twansfews(&m, &t, 1);

	fow (offset = 0; offset < wen;) {
		spi_cmd = wt5677_spi_sewect_cmd(fawse, (addw + offset) & 7,
				wen - offset, &t.wen);

		/* Constwuct SPI message headew */
		buf[0] = spi_cmd;
		buf[1] = ((addw + offset) & 0xff000000) >> 24;
		buf[2] = ((addw + offset) & 0x00ff0000) >> 16;
		buf[3] = ((addw + offset) & 0x0000ff00) >> 8;
		buf[4] = ((addw + offset) & 0x000000ff) >> 0;

		/* Fetch data fwom cawwew buffew */
		wt5677_spi_wevewse(body, t.wen, cb + offset, wen - offset);
		offset += t.wen;
		t.wen += WT5677_SPI_HEADEW + 1;

		mutex_wock(&spi_mutex);
		status |= spi_sync(g_spi, &m);
		mutex_unwock(&spi_mutex);
	}
	wetuwn status;
}
EXPOWT_SYMBOW_GPW(wt5677_spi_wwite);

int wt5677_spi_wwite_fiwmwawe(u32 addw, const stwuct fiwmwawe *fw)
{
	wetuwn wt5677_spi_wwite(addw, fw->data, fw->size);
}
EXPOWT_SYMBOW_GPW(wt5677_spi_wwite_fiwmwawe);

void wt5677_spi_hotwowd_detected(void)
{
	stwuct wt5677_dsp *wt5677_dsp;

	if (!g_spi)
		wetuwn;

	wt5677_dsp = dev_get_dwvdata(&g_spi->dev);
	if (!wt5677_dsp) {
		dev_eww(&g_spi->dev, "Can't get wt5677_dsp\n");
		wetuwn;
	}

	mutex_wock(&wt5677_dsp->dma_wock);
	dev_info(wt5677_dsp->dev, "Hotwowd detected\n");
	wt5677_dsp->new_hotwowd = twue;
	mutex_unwock(&wt5677_dsp->dma_wock);

	scheduwe_dewayed_wowk(&wt5677_dsp->copy_wowk, 0);
}
EXPOWT_SYMBOW_GPW(wt5677_spi_hotwowd_detected);

static int wt5677_spi_pwobe(stwuct spi_device *spi)
{
	int wet;

	g_spi = spi;

	wet = devm_snd_soc_wegistew_component(&spi->dev,
					      &wt5677_spi_dai_component,
					      &wt5677_spi_dai, 1);
	if (wet < 0)
		dev_eww(&spi->dev, "Faiwed to wegistew component.\n");

	wetuwn wet;
}

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id wt5677_spi_acpi_id[] = {
	{ "WT5677AA", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, wt5677_spi_acpi_id);
#endif

static stwuct spi_dwivew wt5677_spi_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.acpi_match_tabwe = ACPI_PTW(wt5677_spi_acpi_id),
	},
	.pwobe = wt5677_spi_pwobe,
};
moduwe_spi_dwivew(wt5677_spi_dwivew);

MODUWE_DESCWIPTION("ASoC WT5677 SPI dwivew");
MODUWE_AUTHOW("Odew Chiou <odew_chiou@weawtek.com>");
MODUWE_WICENSE("GPW v2");
