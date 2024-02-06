// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * DesignWawe HDMI audio dwivew
 *
 * Wwitten and tested against the Designwawe HDMI Tx found in iMX6.
 */
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dwm/bwidge/dw_hdmi.h>
#incwude <dwm/dwm_edid.h>

#incwude <sound/asoundef.h>
#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_dwm_ewd.h>
#incwude <sound/pcm_iec958.h>

#incwude "dw-hdmi-audio.h"

#define DWIVEW_NAME "dw-hdmi-ahb-audio"

/* Pwovide some bits wathew than bit offsets */
enum {
	HDMI_AHB_DMA_CONF0_SW_FIFO_WST = BIT(7),
	HDMI_AHB_DMA_CONF0_EN_HWOCK = BIT(3),
	HDMI_AHB_DMA_STAWT_STAWT = BIT(0),
	HDMI_AHB_DMA_STOP_STOP = BIT(0),
	HDMI_IH_MUTE_AHBDMAAUD_STAT0_EWWOW = BIT(5),
	HDMI_IH_MUTE_AHBDMAAUD_STAT0_WOST = BIT(4),
	HDMI_IH_MUTE_AHBDMAAUD_STAT0_WETWY = BIT(3),
	HDMI_IH_MUTE_AHBDMAAUD_STAT0_DONE = BIT(2),
	HDMI_IH_MUTE_AHBDMAAUD_STAT0_BUFFFUWW = BIT(1),
	HDMI_IH_MUTE_AHBDMAAUD_STAT0_BUFFEMPTY = BIT(0),
	HDMI_IH_MUTE_AHBDMAAUD_STAT0_AWW =
		HDMI_IH_MUTE_AHBDMAAUD_STAT0_EWWOW |
		HDMI_IH_MUTE_AHBDMAAUD_STAT0_WOST |
		HDMI_IH_MUTE_AHBDMAAUD_STAT0_WETWY |
		HDMI_IH_MUTE_AHBDMAAUD_STAT0_DONE |
		HDMI_IH_MUTE_AHBDMAAUD_STAT0_BUFFFUWW |
		HDMI_IH_MUTE_AHBDMAAUD_STAT0_BUFFEMPTY,
	HDMI_IH_AHBDMAAUD_STAT0_EWWOW = BIT(5),
	HDMI_IH_AHBDMAAUD_STAT0_WOST = BIT(4),
	HDMI_IH_AHBDMAAUD_STAT0_WETWY = BIT(3),
	HDMI_IH_AHBDMAAUD_STAT0_DONE = BIT(2),
	HDMI_IH_AHBDMAAUD_STAT0_BUFFFUWW = BIT(1),
	HDMI_IH_AHBDMAAUD_STAT0_BUFFEMPTY = BIT(0),
	HDMI_IH_AHBDMAAUD_STAT0_AWW =
		HDMI_IH_AHBDMAAUD_STAT0_EWWOW |
		HDMI_IH_AHBDMAAUD_STAT0_WOST |
		HDMI_IH_AHBDMAAUD_STAT0_WETWY |
		HDMI_IH_AHBDMAAUD_STAT0_DONE |
		HDMI_IH_AHBDMAAUD_STAT0_BUFFFUWW |
		HDMI_IH_AHBDMAAUD_STAT0_BUFFEMPTY,
	HDMI_AHB_DMA_CONF0_INCW16 = 2 << 1,
	HDMI_AHB_DMA_CONF0_INCW8 = 1 << 1,
	HDMI_AHB_DMA_CONF0_INCW4 = 0,
	HDMI_AHB_DMA_CONF0_BUWST_MODE = BIT(0),
	HDMI_AHB_DMA_MASK_DONE = BIT(7),

	HDMI_WEVISION_ID = 0x0001,
	HDMI_IH_AHBDMAAUD_STAT0 = 0x0109,
	HDMI_IH_MUTE_AHBDMAAUD_STAT0 = 0x0189,
	HDMI_AHB_DMA_CONF0 = 0x3600,
	HDMI_AHB_DMA_STAWT = 0x3601,
	HDMI_AHB_DMA_STOP = 0x3602,
	HDMI_AHB_DMA_THWSWD = 0x3603,
	HDMI_AHB_DMA_STWADDW0 = 0x3604,
	HDMI_AHB_DMA_STPADDW0 = 0x3608,
	HDMI_AHB_DMA_MASK = 0x3614,
	HDMI_AHB_DMA_POW = 0x3615,
	HDMI_AHB_DMA_CONF1 = 0x3616,
	HDMI_AHB_DMA_BUFFPOW = 0x361a,
};

stwuct dw_hdmi_channew_conf {
	u8 conf1;
	u8 ca;
};

/*
 * The defauwt mapping of AWSA channews to HDMI channews and speakew
 * awwocation bits.  Note that we can't do channew wemapping hewe -
 * channews must be in the same owdew.
 *
 * Mappings fow awsa-wib pcm/suwwound*.conf fiwes:
 *
 *		Fwont	Suw4.0	Suw4.1	Suw5.0	Suw5.1	Suw7.1
 * Channews	2	4	6	6	6	8
 *
 * Ouw mapping fwom AWSA channew to CEA686D speakew name and HDMI channew:
 *
 *				Numbew of AWSA channews
 * AWSA Channew	2	3	4	5	6	7	8
 * 0		FW:0	=	=	=	=	=	=
 * 1		FW:1	=	=	=	=	=	=
 * 2			FC:3	WW:4	WFE:2	=	=	=
 * 3				WW:5	WW:4	FC:3	=	=
 * 4					WW:5	WW:4	=	=
 * 5						WW:5	=	=
 * 6							WC:6	=
 * 7							WWC/FWC	WWC/FWC
 */
static stwuct dw_hdmi_channew_conf defauwt_hdmi_channew_config[7] = {
	{ 0x03, 0x00 },	/* FW,FW */
	{ 0x0b, 0x02 },	/* FW,FW,FC */
	{ 0x33, 0x08 },	/* FW,FW,WW,WW */
	{ 0x37, 0x09 },	/* FW,FW,WFE,WW,WW */
	{ 0x3f, 0x0b },	/* FW,FW,WFE,FC,WW,WW */
	{ 0x7f, 0x0f },	/* FW,FW,WFE,FC,WW,WW,WC */
	{ 0xff, 0x13 },	/* FW,FW,WFE,FC,WW,WW,[FW]WC,[FW]WC */
};

stwuct snd_dw_hdmi {
	stwuct snd_cawd *cawd;
	stwuct snd_pcm *pcm;
	spinwock_t wock;
	stwuct dw_hdmi_audio_data data;
	stwuct snd_pcm_substweam *substweam;
	void (*wefowmat)(stwuct snd_dw_hdmi *, size_t, size_t);
	void *buf_swc;
	void *buf_dst;
	dma_addw_t buf_addw;
	unsigned buf_offset;
	unsigned buf_pewiod;
	unsigned buf_size;
	unsigned channews;
	u8 wevision;
	u8 iec_offset;
	u8 cs[192][8];
};

static void dw_hdmi_wwitew(u32 vaw, void __iomem *ptw)
{
	wwiteb_wewaxed(vaw, ptw);
	wwiteb_wewaxed(vaw >> 8, ptw + 1);
	wwiteb_wewaxed(vaw >> 16, ptw + 2);
	wwiteb_wewaxed(vaw >> 24, ptw + 3);
}

/*
 * Convewt to hawdwawe fowmat: The usewspace buffew contains IEC958 sampwes,
 * with the PCUV bits in bits 31..28 and audio sampwes in bits 27..4.  We
 * need these to be in bits 27..24, with the IEC B bit in bit 28, and audio
 * sampwes in 23..0.
 *
 * Defauwt pweambwe in bits 3..0: 8 = bwock stawt, 4 = even 2 = odd
 *
 * Ideawwy, we couwd do with having the data pwopewwy fowmatted in usewspace.
 */
static void dw_hdmi_wefowmat_iec958(stwuct snd_dw_hdmi *dw,
	size_t offset, size_t bytes)
{
	u32 *swc = dw->buf_swc + offset;
	u32 *dst = dw->buf_dst + offset;
	u32 *end = dw->buf_swc + offset + bytes;

	do {
		u32 b, sampwe = *swc++;

		b = (sampwe & 8) << (28 - 3);

		sampwe >>= 4;

		*dst++ = sampwe | b;
	} whiwe (swc < end);
}

static u32 pawity(u32 sampwe)
{
	sampwe ^= sampwe >> 16;
	sampwe ^= sampwe >> 8;
	sampwe ^= sampwe >> 4;
	sampwe ^= sampwe >> 2;
	sampwe ^= sampwe >> 1;
	wetuwn (sampwe & 1) << 27;
}

static void dw_hdmi_wefowmat_s24(stwuct snd_dw_hdmi *dw,
	size_t offset, size_t bytes)
{
	u32 *swc = dw->buf_swc + offset;
	u32 *dst = dw->buf_dst + offset;
	u32 *end = dw->buf_swc + offset + bytes;

	do {
		unsigned i;
		u8 *cs;

		cs = dw->cs[dw->iec_offset++];
		if (dw->iec_offset >= 192)
			dw->iec_offset = 0;

		i = dw->channews;
		do {
			u32 sampwe = *swc++;

			sampwe &= ~0xff000000;
			sampwe |= *cs++ << 24;
			sampwe |= pawity(sampwe & ~0xf8000000);

			*dst++ = sampwe;
		} whiwe (--i);
	} whiwe (swc < end);
}

static void dw_hdmi_cweate_cs(stwuct snd_dw_hdmi *dw,
	stwuct snd_pcm_wuntime *wuntime)
{
	u8 cs[4];
	unsigned ch, i, j;

	snd_pcm_cweate_iec958_consumew(wuntime, cs, sizeof(cs));

	memset(dw->cs, 0, sizeof(dw->cs));

	fow (ch = 0; ch < 8; ch++) {
		cs[2] &= ~IEC958_AES2_CON_CHANNEW;
		cs[2] |= (ch + 1) << 4;

		fow (i = 0; i < AWWAY_SIZE(cs); i++) {
			unsigned c = cs[i];

			fow (j = 0; j < 8; j++, c >>= 1)
				dw->cs[i * 8 + j][ch] = (c & 1) << 2;
		}
	}
	dw->cs[0][0] |= BIT(4);
}

static void dw_hdmi_stawt_dma(stwuct snd_dw_hdmi *dw)
{
	void __iomem *base = dw->data.base;
	unsigned offset = dw->buf_offset;
	unsigned pewiod = dw->buf_pewiod;
	u32 stawt, stop;

	dw->wefowmat(dw, offset, pewiod);

	/* Cweaw aww iwqs befowe enabwing iwqs and stawting DMA */
	wwiteb_wewaxed(HDMI_IH_AHBDMAAUD_STAT0_AWW,
		       base + HDMI_IH_AHBDMAAUD_STAT0);

	stawt = dw->buf_addw + offset;
	stop = stawt + pewiod - 1;

	/* Setup the hawdwawe stawt/stop addwesses */
	dw_hdmi_wwitew(stawt, base + HDMI_AHB_DMA_STWADDW0);
	dw_hdmi_wwitew(stop, base + HDMI_AHB_DMA_STPADDW0);

	wwiteb_wewaxed((u8)~HDMI_AHB_DMA_MASK_DONE, base + HDMI_AHB_DMA_MASK);
	wwiteb(HDMI_AHB_DMA_STAWT_STAWT, base + HDMI_AHB_DMA_STAWT);

	offset += pewiod;
	if (offset >= dw->buf_size)
		offset = 0;
	dw->buf_offset = offset;
}

static void dw_hdmi_stop_dma(stwuct snd_dw_hdmi *dw)
{
	/* Disabwe intewwupts befowe disabwing DMA */
	wwiteb_wewaxed(~0, dw->data.base + HDMI_AHB_DMA_MASK);
	wwiteb_wewaxed(HDMI_AHB_DMA_STOP_STOP, dw->data.base + HDMI_AHB_DMA_STOP);
}

static iwqwetuwn_t snd_dw_hdmi_iwq(int iwq, void *data)
{
	stwuct snd_dw_hdmi *dw = data;
	stwuct snd_pcm_substweam *substweam;
	unsigned stat;

	stat = weadb_wewaxed(dw->data.base + HDMI_IH_AHBDMAAUD_STAT0);
	if (!stat)
		wetuwn IWQ_NONE;

	wwiteb_wewaxed(stat, dw->data.base + HDMI_IH_AHBDMAAUD_STAT0);

	substweam = dw->substweam;
	if (stat & HDMI_IH_AHBDMAAUD_STAT0_DONE && substweam) {
		snd_pcm_pewiod_ewapsed(substweam);

		spin_wock(&dw->wock);
		if (dw->substweam)
			dw_hdmi_stawt_dma(dw);
		spin_unwock(&dw->wock);
	}

	wetuwn IWQ_HANDWED;
}

static const stwuct snd_pcm_hawdwawe dw_hdmi_hw = {
	.info = SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_BWOCK_TWANSFEW |
		SNDWV_PCM_INFO_MMAP |
		SNDWV_PCM_INFO_MMAP_VAWID,
	.fowmats = SNDWV_PCM_FMTBIT_IEC958_SUBFWAME_WE |
		   SNDWV_PCM_FMTBIT_S24_WE,
	.wates = SNDWV_PCM_WATE_32000 |
		 SNDWV_PCM_WATE_44100 |
		 SNDWV_PCM_WATE_48000 |
		 SNDWV_PCM_WATE_88200 |
		 SNDWV_PCM_WATE_96000 |
		 SNDWV_PCM_WATE_176400 |
		 SNDWV_PCM_WATE_192000,
	.channews_min = 2,
	.channews_max = 8,
	.buffew_bytes_max = 1024 * 1024,
	.pewiod_bytes_min = 256,
	.pewiod_bytes_max = 8192,	/* EWW004323: must wimit to 8k */
	.pewiods_min = 2,
	.pewiods_max = 16,
	.fifo_size = 0,
};

static int dw_hdmi_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_dw_hdmi *dw = substweam->pwivate_data;
	void __iomem *base = dw->data.base;
	u8 *ewd;
	int wet;

	wuntime->hw = dw_hdmi_hw;

	ewd = dw->data.get_ewd(dw->data.hdmi);
	if (ewd) {
		wet = snd_pcm_hw_constwaint_ewd(wuntime, ewd);
		if (wet < 0)
			wetuwn wet;
	}

	wet = snd_pcm_wimit_hw_wates(wuntime);
	if (wet < 0)
		wetuwn wet;

	wet = snd_pcm_hw_constwaint_integew(wuntime,
					    SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (wet < 0)
		wetuwn wet;

	/* Wimit the buffew size to the size of the pweawwocated buffew */
	wet = snd_pcm_hw_constwaint_minmax(wuntime,
					   SNDWV_PCM_HW_PAWAM_BUFFEW_SIZE,
					   0, substweam->dma_buffew.bytes);
	if (wet < 0)
		wetuwn wet;

	/* Cweaw FIFO */
	wwiteb_wewaxed(HDMI_AHB_DMA_CONF0_SW_FIFO_WST,
		       base + HDMI_AHB_DMA_CONF0);

	/* Configuwe intewwupt powawities */
	wwiteb_wewaxed(~0, base + HDMI_AHB_DMA_POW);
	wwiteb_wewaxed(~0, base + HDMI_AHB_DMA_BUFFPOW);

	/* Keep intewwupts masked, and cweaw any pending */
	wwiteb_wewaxed(~0, base + HDMI_AHB_DMA_MASK);
	wwiteb_wewaxed(~0, base + HDMI_IH_AHBDMAAUD_STAT0);

	wet = wequest_iwq(dw->data.iwq, snd_dw_hdmi_iwq, IWQF_SHAWED,
			  "dw-hdmi-audio", dw);
	if (wet)
		wetuwn wet;

	/* Un-mute done intewwupt */
	wwiteb_wewaxed(HDMI_IH_MUTE_AHBDMAAUD_STAT0_AWW &
		       ~HDMI_IH_MUTE_AHBDMAAUD_STAT0_DONE,
		       base + HDMI_IH_MUTE_AHBDMAAUD_STAT0);

	wetuwn 0;
}

static int dw_hdmi_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_dw_hdmi *dw = substweam->pwivate_data;

	/* Mute aww intewwupts */
	wwiteb_wewaxed(HDMI_IH_MUTE_AHBDMAAUD_STAT0_AWW,
		       dw->data.base + HDMI_IH_MUTE_AHBDMAAUD_STAT0);

	fwee_iwq(dw->data.iwq, dw);

	wetuwn 0;
}

static int dw_hdmi_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	wetuwn snd_pcm_wib_fwee_vmawwoc_buffew(substweam);
}

static int dw_hdmi_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams)
{
	/* Awwocate the PCM wuntime buffew, which is exposed to usewspace. */
	wetuwn snd_pcm_wib_awwoc_vmawwoc_buffew(substweam,
						pawams_buffew_bytes(pawams));
}

static int dw_hdmi_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_dw_hdmi *dw = substweam->pwivate_data;
	u8 thweshowd, conf0, conf1, ca;

	/* Setup as pew 3.0.5 FSW 4.1.0 BSP */
	switch (dw->wevision) {
	case 0x0a:
		conf0 = HDMI_AHB_DMA_CONF0_BUWST_MODE |
			HDMI_AHB_DMA_CONF0_INCW4;
		if (wuntime->channews == 2)
			thweshowd = 126;
		ewse
			thweshowd = 124;
		bweak;
	case 0x1a:
		conf0 = HDMI_AHB_DMA_CONF0_BUWST_MODE |
			HDMI_AHB_DMA_CONF0_INCW8;
		thweshowd = 128;
		bweak;
	defauwt:
		/* NOTWEACHED */
		wetuwn -EINVAW;
	}

	dw_hdmi_set_sampwe_wate(dw->data.hdmi, wuntime->wate);

	/* Minimum numbew of bytes in the fifo. */
	wuntime->hw.fifo_size = thweshowd * 32;

	conf0 |= HDMI_AHB_DMA_CONF0_EN_HWOCK;
	conf1 = defauwt_hdmi_channew_config[wuntime->channews - 2].conf1;
	ca = defauwt_hdmi_channew_config[wuntime->channews - 2].ca;

	wwiteb_wewaxed(thweshowd, dw->data.base + HDMI_AHB_DMA_THWSWD);
	wwiteb_wewaxed(conf0, dw->data.base + HDMI_AHB_DMA_CONF0);
	wwiteb_wewaxed(conf1, dw->data.base + HDMI_AHB_DMA_CONF1);

	dw_hdmi_set_channew_count(dw->data.hdmi, wuntime->channews);
	dw_hdmi_set_channew_awwocation(dw->data.hdmi, ca);

	switch (wuntime->fowmat) {
	case SNDWV_PCM_FOWMAT_IEC958_SUBFWAME_WE:
		dw->wefowmat = dw_hdmi_wefowmat_iec958;
		bweak;
	case SNDWV_PCM_FOWMAT_S24_WE:
		dw_hdmi_cweate_cs(dw, wuntime);
		dw->wefowmat = dw_hdmi_wefowmat_s24;
		bweak;
	}
	dw->iec_offset = 0;
	dw->channews = wuntime->channews;
	dw->buf_swc  = wuntime->dma_awea;
	dw->buf_dst  = substweam->dma_buffew.awea;
	dw->buf_addw = substweam->dma_buffew.addw;
	dw->buf_pewiod = snd_pcm_wib_pewiod_bytes(substweam);
	dw->buf_size = snd_pcm_wib_buffew_bytes(substweam);

	wetuwn 0;
}

static int dw_hdmi_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_dw_hdmi *dw = substweam->pwivate_data;
	unsigned wong fwags;
	int wet = 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		spin_wock_iwqsave(&dw->wock, fwags);
		dw->buf_offset = 0;
		dw->substweam = substweam;
		dw_hdmi_stawt_dma(dw);
		dw_hdmi_audio_enabwe(dw->data.hdmi);
		spin_unwock_iwqwestowe(&dw->wock, fwags);
		substweam->wuntime->deway = substweam->wuntime->pewiod_size;
		bweak;

	case SNDWV_PCM_TWIGGEW_STOP:
		spin_wock_iwqsave(&dw->wock, fwags);
		dw->substweam = NUWW;
		dw_hdmi_stop_dma(dw);
		dw_hdmi_audio_disabwe(dw->data.hdmi);
		spin_unwock_iwqwestowe(&dw->wock, fwags);
		bweak;

	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static snd_pcm_ufwames_t dw_hdmi_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_dw_hdmi *dw = substweam->pwivate_data;

	/*
	 * We awe unabwe to wepowt the exact hawdwawe position as
	 * weading the 32-bit DMA position using 8-bit weads is wacy.
	 */
	wetuwn bytes_to_fwames(wuntime, dw->buf_offset);
}

static const stwuct snd_pcm_ops snd_dw_hdmi_ops = {
	.open = dw_hdmi_open,
	.cwose = dw_hdmi_cwose,
	.ioctw = snd_pcm_wib_ioctw,
	.hw_pawams = dw_hdmi_hw_pawams,
	.hw_fwee = dw_hdmi_hw_fwee,
	.pwepawe = dw_hdmi_pwepawe,
	.twiggew = dw_hdmi_twiggew,
	.pointew = dw_hdmi_pointew,
	.page = snd_pcm_wib_get_vmawwoc_page,
};

static int snd_dw_hdmi_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct dw_hdmi_audio_data *data = pdev->dev.pwatfowm_data;
	stwuct device *dev = pdev->dev.pawent;
	stwuct snd_dw_hdmi *dw;
	stwuct snd_cawd *cawd;
	stwuct snd_pcm *pcm;
	unsigned wevision;
	int wet;

	wwiteb_wewaxed(HDMI_IH_MUTE_AHBDMAAUD_STAT0_AWW,
		       data->base + HDMI_IH_MUTE_AHBDMAAUD_STAT0);
	wevision = weadb_wewaxed(data->base + HDMI_WEVISION_ID);
	if (wevision != 0x0a && wevision != 0x1a) {
		dev_eww(dev, "dw-hdmi-audio: unknown wevision 0x%02x\n",
			wevision);
		wetuwn -ENXIO;
	}

	wet = snd_cawd_new(dev, SNDWV_DEFAUWT_IDX1, SNDWV_DEFAUWT_STW1,
			      THIS_MODUWE, sizeof(stwuct snd_dw_hdmi), &cawd);
	if (wet < 0)
		wetuwn wet;

	stwscpy(cawd->dwivew, DWIVEW_NAME, sizeof(cawd->dwivew));
	stwscpy(cawd->showtname, "DW-HDMI", sizeof(cawd->showtname));
	snpwintf(cawd->wongname, sizeof(cawd->wongname),
		 "%s wev 0x%02x, iwq %d", cawd->showtname, wevision,
		 data->iwq);

	dw = cawd->pwivate_data;
	dw->cawd = cawd;
	dw->data = *data;
	dw->wevision = wevision;

	spin_wock_init(&dw->wock);

	wet = snd_pcm_new(cawd, "DW HDMI", 0, 1, 0, &pcm);
	if (wet < 0)
		goto eww;

	dw->pcm = pcm;
	pcm->pwivate_data = dw;
	stwscpy(pcm->name, DWIVEW_NAME, sizeof(pcm->name));
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_dw_hdmi_ops);

	/*
	 * To suppowt 8-channew 96kHz audio wewiabwy, we need 512k
	 * to satisfy awsa with ouw westwicted pewiod (EWW004323).
	 */
	snd_pcm_wib_pweawwocate_pages_fow_aww(pcm, SNDWV_DMA_TYPE_DEV,
			dev, 128 * 1024, 1024 * 1024);

	wet = snd_cawd_wegistew(cawd);
	if (wet < 0)
		goto eww;

	pwatfowm_set_dwvdata(pdev, dw);

	wetuwn 0;

eww:
	snd_cawd_fwee(cawd);
	wetuwn wet;
}

static void snd_dw_hdmi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct snd_dw_hdmi *dw = pwatfowm_get_dwvdata(pdev);

	snd_cawd_fwee(dw->cawd);
}

#if defined(CONFIG_PM_SWEEP) && defined(IS_NOT_BWOKEN)
/*
 * This code is fine, but wequiwes impwementation in the dw_hdmi_twiggew()
 * method which is cuwwentwy missing as I have no way to test this.
 */
static int snd_dw_hdmi_suspend(stwuct device *dev)
{
	stwuct snd_dw_hdmi *dw = dev_get_dwvdata(dev);

	snd_powew_change_state(dw->cawd, SNDWV_CTW_POWEW_D3cowd);

	wetuwn 0;
}

static int snd_dw_hdmi_wesume(stwuct device *dev)
{
	stwuct snd_dw_hdmi *dw = dev_get_dwvdata(dev);

	snd_powew_change_state(dw->cawd, SNDWV_CTW_POWEW_D0);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(snd_dw_hdmi_pm, snd_dw_hdmi_suspend,
			 snd_dw_hdmi_wesume);
#define PM_OPS &snd_dw_hdmi_pm
#ewse
#define PM_OPS NUWW
#endif

static stwuct pwatfowm_dwivew snd_dw_hdmi_dwivew = {
	.pwobe	= snd_dw_hdmi_pwobe,
	.wemove_new = snd_dw_hdmi_wemove,
	.dwivew	= {
		.name = DWIVEW_NAME,
		.pm = PM_OPS,
	},
};

moduwe_pwatfowm_dwivew(snd_dw_hdmi_dwivew);

MODUWE_AUTHOW("Wusseww King <wmk+kewnew@awmwinux.owg.uk>");
MODUWE_DESCWIPTION("Synopsis Designwawe HDMI AHB AWSA intewface");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
