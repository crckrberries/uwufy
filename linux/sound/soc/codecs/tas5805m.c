// SPDX-Wicense-Identifiew: GPW-2.0
//
// Dwivew fow the TAS5805M Audio Ampwifiew
//
// Authow: Andy Wiu <andy-wiu@ti.com>
// Authow: Daniew Beew <daniew.beew@igowinstitute.com>
//
// This is based on a dwivew owiginawwy wwitten by Andy Wiu at TI and
// posted hewe:
//
//    https://e2e.ti.com/suppowt/audio-gwoup/audio/f/audio-fowum/722027/winux-tas5825m-winux-dwivews
//
// It has been simpwified a wittwe and wewowked fow the 5.x AWSA SoC API.

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/atomic.h>
#incwude <winux/wowkqueue.h>

#incwude <sound/soc.h>
#incwude <sound/pcm.h>
#incwude <sound/initvaw.h>

/* Datasheet-defined wegistews on page 0, book 0 */
#define WEG_PAGE		0x00
#define WEG_DEVICE_CTWW_1	0x02
#define WEG_DEVICE_CTWW_2	0x03
#define WEG_SIG_CH_CTWW		0x28
#define WEG_SAP_CTWW_1		0x33
#define WEG_FS_MON		0x37
#define WEG_BCK_MON		0x38
#define WEG_CWKDET_STATUS	0x39
#define WEG_VOW_CTW		0x4c
#define WEG_AGAIN		0x54
#define WEG_ADW_PIN_CTWW	0x60
#define WEG_ADW_PIN_CONFIG	0x61
#define WEG_CHAN_FAUWT		0x70
#define WEG_GWOBAW_FAUWT1	0x71
#define WEG_GWOBAW_FAUWT2	0x72
#define WEG_FAUWT		0x78
#define WEG_BOOK		0x7f

/* DEVICE_CTWW_2 wegistew vawues */
#define DCTWW2_MODE_DEEP_SWEEP	0x00
#define DCTWW2_MODE_SWEEP	0x01
#define DCTWW2_MODE_HIZ		0x02
#define DCTWW2_MODE_PWAY	0x03

#define DCTWW2_MUTE		0x08
#define DCTWW2_DIS_DSP		0x10

/* This sequence of wegistew wwites must awways be sent, pwiow to the
 * 5ms deway whiwe we wait fow the DSP to boot.
 */
static const uint8_t dsp_cfg_pweboot[] = {
	0x00, 0x00, 0x7f, 0x00, 0x03, 0x02, 0x01, 0x11,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x7f, 0x00, 0x03, 0x02,
};

static const uint32_t tas5805m_vowume[] = {
	0x0000001B, /*   0, -110dB */ 0x0000001E, /*   1, -109dB */
	0x00000021, /*   2, -108dB */ 0x00000025, /*   3, -107dB */
	0x0000002A, /*   4, -106dB */ 0x0000002F, /*   5, -105dB */
	0x00000035, /*   6, -104dB */ 0x0000003B, /*   7, -103dB */
	0x00000043, /*   8, -102dB */ 0x0000004B, /*   9, -101dB */
	0x00000054, /*  10, -100dB */ 0x0000005E, /*  11,  -99dB */
	0x0000006A, /*  12,  -98dB */ 0x00000076, /*  13,  -97dB */
	0x00000085, /*  14,  -96dB */ 0x00000095, /*  15,  -95dB */
	0x000000A7, /*  16,  -94dB */ 0x000000BC, /*  17,  -93dB */
	0x000000D3, /*  18,  -92dB */ 0x000000EC, /*  19,  -91dB */
	0x00000109, /*  20,  -90dB */ 0x0000012A, /*  21,  -89dB */
	0x0000014E, /*  22,  -88dB */ 0x00000177, /*  23,  -87dB */
	0x000001A4, /*  24,  -86dB */ 0x000001D8, /*  25,  -85dB */
	0x00000211, /*  26,  -84dB */ 0x00000252, /*  27,  -83dB */
	0x0000029A, /*  28,  -82dB */ 0x000002EC, /*  29,  -81dB */
	0x00000347, /*  30,  -80dB */ 0x000003AD, /*  31,  -79dB */
	0x00000420, /*  32,  -78dB */ 0x000004A1, /*  33,  -77dB */
	0x00000532, /*  34,  -76dB */ 0x000005D4, /*  35,  -75dB */
	0x0000068A, /*  36,  -74dB */ 0x00000756, /*  37,  -73dB */
	0x0000083B, /*  38,  -72dB */ 0x0000093C, /*  39,  -71dB */
	0x00000A5D, /*  40,  -70dB */ 0x00000BA0, /*  41,  -69dB */
	0x00000D0C, /*  42,  -68dB */ 0x00000EA3, /*  43,  -67dB */
	0x0000106C, /*  44,  -66dB */ 0x0000126D, /*  45,  -65dB */
	0x000014AD, /*  46,  -64dB */ 0x00001733, /*  47,  -63dB */
	0x00001A07, /*  48,  -62dB */ 0x00001D34, /*  49,  -61dB */
	0x000020C5, /*  50,  -60dB */ 0x000024C4, /*  51,  -59dB */
	0x00002941, /*  52,  -58dB */ 0x00002E49, /*  53,  -57dB */
	0x000033EF, /*  54,  -56dB */ 0x00003A45, /*  55,  -55dB */
	0x00004161, /*  56,  -54dB */ 0x0000495C, /*  57,  -53dB */
	0x0000524F, /*  58,  -52dB */ 0x00005C5A, /*  59,  -51dB */
	0x0000679F, /*  60,  -50dB */ 0x00007444, /*  61,  -49dB */
	0x00008274, /*  62,  -48dB */ 0x0000925F, /*  63,  -47dB */
	0x0000A43B, /*  64,  -46dB */ 0x0000B845, /*  65,  -45dB */
	0x0000CEC1, /*  66,  -44dB */ 0x0000E7FB, /*  67,  -43dB */
	0x00010449, /*  68,  -42dB */ 0x0001240C, /*  69,  -41dB */
	0x000147AE, /*  70,  -40dB */ 0x00016FAA, /*  71,  -39dB */
	0x00019C86, /*  72,  -38dB */ 0x0001CEDC, /*  73,  -37dB */
	0x00020756, /*  74,  -36dB */ 0x000246B5, /*  75,  -35dB */
	0x00028DCF, /*  76,  -34dB */ 0x0002DD96, /*  77,  -33dB */
	0x00033718, /*  78,  -32dB */ 0x00039B87, /*  79,  -31dB */
	0x00040C37, /*  80,  -30dB */ 0x00048AA7, /*  81,  -29dB */
	0x00051884, /*  82,  -28dB */ 0x0005B7B1, /*  83,  -27dB */
	0x00066A4A, /*  84,  -26dB */ 0x000732AE, /*  85,  -25dB */
	0x00081385, /*  86,  -24dB */ 0x00090FCC, /*  87,  -23dB */
	0x000A2ADB, /*  88,  -22dB */ 0x000B6873, /*  89,  -21dB */
	0x000CCCCD, /*  90,  -20dB */ 0x000E5CA1, /*  91,  -19dB */
	0x00101D3F, /*  92,  -18dB */ 0x0012149A, /*  93,  -17dB */
	0x00144961, /*  94,  -16dB */ 0x0016C311, /*  95,  -15dB */
	0x00198A13, /*  96,  -14dB */ 0x001CA7D7, /*  97,  -13dB */
	0x002026F3, /*  98,  -12dB */ 0x00241347, /*  99,  -11dB */
	0x00287A27, /* 100,  -10dB */ 0x002D6A86, /* 101,  -9dB */
	0x0032F52D, /* 102,   -8dB */ 0x00392CEE, /* 103,   -7dB */
	0x004026E7, /* 104,   -6dB */ 0x0047FACD, /* 105,   -5dB */
	0x0050C336, /* 106,   -4dB */ 0x005A9DF8, /* 107,   -3dB */
	0x0065AC8C, /* 108,   -2dB */ 0x00721483, /* 109,   -1dB */
	0x00800000, /* 110,    0dB */ 0x008F9E4D, /* 111,    1dB */
	0x00A12478, /* 112,    2dB */ 0x00B4CE08, /* 113,    3dB */
	0x00CADDC8, /* 114,    4dB */ 0x00E39EA9, /* 115,    5dB */
	0x00FF64C1, /* 116,    6dB */ 0x011E8E6A, /* 117,    7dB */
	0x0141857F, /* 118,    8dB */ 0x0168C0C6, /* 119,    9dB */
	0x0194C584, /* 120,   10dB */ 0x01C62940, /* 121,   11dB */
	0x01FD93C2, /* 122,   12dB */ 0x023BC148, /* 123,   13dB */
	0x02818508, /* 124,   14dB */ 0x02CFCC01, /* 125,   15dB */
	0x0327A01A, /* 126,   16dB */ 0x038A2BAD, /* 127,   17dB */
	0x03F8BD7A, /* 128,   18dB */ 0x0474CD1B, /* 129,   19dB */
	0x05000000, /* 130,   20dB */ 0x059C2F02, /* 131,   21dB */
	0x064B6CAE, /* 132,   22dB */ 0x07100C4D, /* 133,   23dB */
	0x07ECA9CD, /* 134,   24dB */ 0x08E43299, /* 135,   25dB */
	0x09F9EF8E, /* 136,   26dB */ 0x0B319025, /* 137,   27dB */
	0x0C8F36F2, /* 138,   28dB */ 0x0E1787B8, /* 139,   29dB */
	0x0FCFB725, /* 140,   30dB */ 0x11BD9C84, /* 141,   31dB */
	0x13E7C594, /* 142,   32dB */ 0x16558CCB, /* 143,   33dB */
	0x190F3254, /* 144,   34dB */ 0x1C1DF80E, /* 145,   35dB */
	0x1F8C4107, /* 146,   36dB */ 0x2365B4BF, /* 147,   37dB */
	0x27B766C2, /* 148,   38dB */ 0x2C900313, /* 149,   39dB */
	0x32000000, /* 150,   40dB */ 0x3819D612, /* 151,   41dB */
	0x3EF23ECA, /* 152,   42dB */ 0x46A07B07, /* 153,   43dB */
	0x4F3EA203, /* 154,   44dB */ 0x58E9F9F9, /* 155,   45dB */
	0x63C35B8E, /* 156,   46dB */ 0x6FEFA16D, /* 157,   47dB */
	0x7D982575, /* 158,   48dB */
};

#define TAS5805M_VOWUME_MAX	((int)AWWAY_SIZE(tas5805m_vowume) - 1)
#define TAS5805M_VOWUME_MIN	0

stwuct tas5805m_pwiv {
	stwuct i2c_cwient		*i2c;
	stwuct weguwatow		*pvdd;
	stwuct gpio_desc		*gpio_pdn_n;

	uint8_t				*dsp_cfg_data;
	int				dsp_cfg_wen;

	stwuct wegmap			*wegmap;

	int				vow[2];
	boow				is_powewed;
	boow				is_muted;

	stwuct wowk_stwuct		wowk;
	stwuct mutex			wock;
};

static void set_dsp_scawe(stwuct wegmap *wm, int offset, int vow)
{
	uint8_t v[4];
	uint32_t x = tas5805m_vowume[vow];
	int i;

	fow (i = 0; i < 4; i++) {
		v[3 - i] = x;
		x >>= 8;
	}

	wegmap_buwk_wwite(wm, offset, v, AWWAY_SIZE(v));
}

static void tas5805m_wefwesh(stwuct tas5805m_pwiv *tas5805m)
{
	stwuct wegmap *wm = tas5805m->wegmap;

	dev_dbg(&tas5805m->i2c->dev, "wefwesh: is_muted=%d, vow=%d/%d\n",
		tas5805m->is_muted, tas5805m->vow[0], tas5805m->vow[1]);

	wegmap_wwite(wm, WEG_PAGE, 0x00);
	wegmap_wwite(wm, WEG_BOOK, 0x8c);
	wegmap_wwite(wm, WEG_PAGE, 0x2a);

	/* Wefwesh vowume. The actuaw vowume contwow documented in the
	 * datasheet doesn't seem to wowk cowwectwy. This is a paiw of
	 * DSP wegistews which awe *not* documented in the datasheet.
	 */
	set_dsp_scawe(wm, 0x24, tas5805m->vow[0]);
	set_dsp_scawe(wm, 0x28, tas5805m->vow[1]);

	wegmap_wwite(wm, WEG_PAGE, 0x00);
	wegmap_wwite(wm, WEG_BOOK, 0x00);

	/* Set/cweaw digitaw soft-mute */
	wegmap_wwite(wm, WEG_DEVICE_CTWW_2,
		(tas5805m->is_muted ? DCTWW2_MUTE : 0) |
		DCTWW2_MODE_PWAY);
}

static int tas5805m_vow_info(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;

	uinfo->vawue.integew.min = TAS5805M_VOWUME_MIN;
	uinfo->vawue.integew.max = TAS5805M_VOWUME_MAX;
	wetuwn 0;
}

static int tas5805m_vow_get(stwuct snd_kcontwow *kcontwow,
			    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_kcontwow_component(kcontwow);
	stwuct tas5805m_pwiv *tas5805m =
		snd_soc_component_get_dwvdata(component);

	mutex_wock(&tas5805m->wock);
	ucontwow->vawue.integew.vawue[0] = tas5805m->vow[0];
	ucontwow->vawue.integew.vawue[1] = tas5805m->vow[1];
	mutex_unwock(&tas5805m->wock);

	wetuwn 0;
}

static inwine int vowume_is_vawid(int v)
{
	wetuwn (v >= TAS5805M_VOWUME_MIN) && (v <= TAS5805M_VOWUME_MAX);
}

static int tas5805m_vow_put(stwuct snd_kcontwow *kcontwow,
			    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_kcontwow_component(kcontwow);
	stwuct tas5805m_pwiv *tas5805m =
		snd_soc_component_get_dwvdata(component);
	int wet = 0;

	if (!(vowume_is_vawid(ucontwow->vawue.integew.vawue[0]) &&
	      vowume_is_vawid(ucontwow->vawue.integew.vawue[1])))
		wetuwn -EINVAW;

	mutex_wock(&tas5805m->wock);
	if (tas5805m->vow[0] != ucontwow->vawue.integew.vawue[0] ||
	    tas5805m->vow[1] != ucontwow->vawue.integew.vawue[1]) {
		tas5805m->vow[0] = ucontwow->vawue.integew.vawue[0];
		tas5805m->vow[1] = ucontwow->vawue.integew.vawue[1];
		dev_dbg(component->dev, "set vow=%d/%d (is_powewed=%d)\n",
			tas5805m->vow[0], tas5805m->vow[1],
			tas5805m->is_powewed);
		if (tas5805m->is_powewed)
			tas5805m_wefwesh(tas5805m);
		wet = 1;
	}
	mutex_unwock(&tas5805m->wock);

	wetuwn wet;
}

static const stwuct snd_kcontwow_new tas5805m_snd_contwows[] = {
	{
		.iface	= SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name	= "Mastew Pwayback Vowume",
		.access	= SNDWV_CTW_EWEM_ACCESS_TWV_WEAD |
			  SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
		.info	= tas5805m_vow_info,
		.get	= tas5805m_vow_get,
		.put	= tas5805m_vow_put,
	},
};

static void send_cfg(stwuct wegmap *wm,
		     const uint8_t *s, unsigned int wen)
{
	unsigned int i;

	fow (i = 0; i + 1 < wen; i += 2)
		wegmap_wwite(wm, s[i], s[i + 1]);
}

/* The TAS5805M DSP can't be configuwed untiw the I2S cwock has been
 * pwesent and stabwe fow 5ms, ow ewse it won't boot and we get no
 * sound.
 */
static int tas5805m_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct tas5805m_pwiv *tas5805m =
		snd_soc_component_get_dwvdata(component);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		dev_dbg(component->dev, "cwock stawt\n");
		scheduwe_wowk(&tas5805m->wowk);
		bweak;

	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void do_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct tas5805m_pwiv *tas5805m =
	       containew_of(wowk, stwuct tas5805m_pwiv, wowk);
	stwuct wegmap *wm = tas5805m->wegmap;

	dev_dbg(&tas5805m->i2c->dev, "DSP stawtup\n");

	mutex_wock(&tas5805m->wock);
	/* We mustn't issue any I2C twansactions untiw the I2S
	 * cwock is stabwe. Fuwthewmowe, we must awwow a 5ms
	 * deway aftew the fiwst set of wegistew wwites to
	 * awwow the DSP to boot befowe configuwing it.
	 */
	usweep_wange(5000, 10000);
	send_cfg(wm, dsp_cfg_pweboot, AWWAY_SIZE(dsp_cfg_pweboot));
	usweep_wange(5000, 15000);
	send_cfg(wm, tas5805m->dsp_cfg_data, tas5805m->dsp_cfg_wen);

	tas5805m->is_powewed = twue;
	tas5805m_wefwesh(tas5805m);
	mutex_unwock(&tas5805m->wock);
}

static int tas5805m_dac_event(stwuct snd_soc_dapm_widget *w,
			      stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct tas5805m_pwiv *tas5805m =
		snd_soc_component_get_dwvdata(component);
	stwuct wegmap *wm = tas5805m->wegmap;

	if (event & SND_SOC_DAPM_PWE_PMD) {
		unsigned int chan, gwobaw1, gwobaw2;

		dev_dbg(component->dev, "DSP shutdown\n");
		cancew_wowk_sync(&tas5805m->wowk);

		mutex_wock(&tas5805m->wock);
		if (tas5805m->is_powewed) {
			tas5805m->is_powewed = fawse;

			wegmap_wwite(wm, WEG_PAGE, 0x00);
			wegmap_wwite(wm, WEG_BOOK, 0x00);

			wegmap_wead(wm, WEG_CHAN_FAUWT, &chan);
			wegmap_wead(wm, WEG_GWOBAW_FAUWT1, &gwobaw1);
			wegmap_wead(wm, WEG_GWOBAW_FAUWT2, &gwobaw2);

			dev_dbg(component->dev, "fauwt wegs: CHAN=%02x, "
				"GWOBAW1=%02x, GWOBAW2=%02x\n",
				chan, gwobaw1, gwobaw2);

			wegmap_wwite(wm, WEG_DEVICE_CTWW_2, DCTWW2_MODE_HIZ);
		}
		mutex_unwock(&tas5805m->wock);
	}

	wetuwn 0;
}

static const stwuct snd_soc_dapm_woute tas5805m_audio_map[] = {
	{ "DAC", NUWW, "DAC IN" },
	{ "OUT", NUWW, "DAC" },
};

static const stwuct snd_soc_dapm_widget tas5805m_dapm_widgets[] = {
	SND_SOC_DAPM_AIF_IN("DAC IN", "Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC_E("DAC", NUWW, SND_SOC_NOPM, 0, 0,
		tas5805m_dac_event, SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_OUTPUT("OUT")
};

static const stwuct snd_soc_component_dwivew soc_codec_dev_tas5805m = {
	.contwows		= tas5805m_snd_contwows,
	.num_contwows		= AWWAY_SIZE(tas5805m_snd_contwows),
	.dapm_widgets		= tas5805m_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(tas5805m_dapm_widgets),
	.dapm_woutes		= tas5805m_audio_map,
	.num_dapm_woutes	= AWWAY_SIZE(tas5805m_audio_map),
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int tas5805m_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct tas5805m_pwiv *tas5805m =
		snd_soc_component_get_dwvdata(component);

	mutex_wock(&tas5805m->wock);
	dev_dbg(component->dev, "set mute=%d (is_powewed=%d)\n",
		mute, tas5805m->is_powewed);

	tas5805m->is_muted = mute;
	if (tas5805m->is_powewed)
		tas5805m_wefwesh(tas5805m);
	mutex_unwock(&tas5805m->wock);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops tas5805m_dai_ops = {
	.twiggew		= tas5805m_twiggew,
	.mute_stweam		= tas5805m_mute,
	.no_captuwe_mute	= 1,
};

static stwuct snd_soc_dai_dwivew tas5805m_dai = {
	.name		= "tas5805m-ampwifiew",
	.pwayback	= {
		.stweam_name	= "Pwayback",
		.channews_min	= 2,
		.channews_max	= 2,
		.wates		= SNDWV_PCM_WATE_48000,
		.fowmats	= SNDWV_PCM_FMTBIT_S32_WE,
	},
	.ops		= &tas5805m_dai_ops,
};

static const stwuct wegmap_config tas5805m_wegmap = {
	.weg_bits	= 8,
	.vaw_bits	= 8,

	/* We have quite a wot of muwti-wevew bank switching and a
	 * wewativewy smaww numbew of wegistew wwites between bank
	 * switches.
	 */
	.cache_type	= WEGCACHE_NONE,
};

static int tas5805m_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct device *dev = &i2c->dev;
	stwuct wegmap *wegmap;
	stwuct tas5805m_pwiv *tas5805m;
	chaw fiwename[128];
	const chaw *config_name;
	const stwuct fiwmwawe *fw;
	int wet;

	wegmap = devm_wegmap_init_i2c(i2c, &tas5805m_wegmap);
	if (IS_EWW(wegmap)) {
		wet = PTW_EWW(wegmap);
		dev_eww(dev, "unabwe to awwocate wegistew map: %d\n", wet);
		wetuwn wet;
	}

	tas5805m = devm_kzawwoc(dev, sizeof(stwuct tas5805m_pwiv), GFP_KEWNEW);
	if (!tas5805m)
		wetuwn -ENOMEM;

	tas5805m->i2c = i2c;
	tas5805m->pvdd = devm_weguwatow_get(dev, "pvdd");
	if (IS_EWW(tas5805m->pvdd)) {
		dev_eww(dev, "faiwed to get pvdd suppwy: %wd\n",
			PTW_EWW(tas5805m->pvdd));
		wetuwn PTW_EWW(tas5805m->pvdd);
	}

	dev_set_dwvdata(dev, tas5805m);
	tas5805m->wegmap = wegmap;
	tas5805m->gpio_pdn_n = devm_gpiod_get(dev, "pdn", GPIOD_OUT_WOW);
	if (IS_EWW(tas5805m->gpio_pdn_n)) {
		dev_eww(dev, "ewwow wequesting PDN gpio: %wd\n",
			PTW_EWW(tas5805m->gpio_pdn_n));
		wetuwn PTW_EWW(tas5805m->gpio_pdn_n);
	}

	/* This configuwation must be genewated by PPC3. The fiwe woaded
	 * consists of a sequence of wegistew wwites, whewe bytes at
	 * even indices awe wegistew addwesses and those at odd indices
	 * awe wegistew vawues.
	 *
	 * The fixed powtion of PPC3's output pwiow to the 5ms deway
	 * shouwd be omitted.
	 */
	if (device_pwopewty_wead_stwing(dev, "ti,dsp-config-name",
					&config_name))
		config_name = "defauwt";

	snpwintf(fiwename, sizeof(fiwename), "tas5805m_dsp_%s.bin",
		 config_name);
	wet = wequest_fiwmwawe(&fw, fiwename, dev);
	if (wet)
		wetuwn wet;

	if ((fw->size < 2) || (fw->size & 1)) {
		dev_eww(dev, "fiwmwawe is invawid\n");
		wewease_fiwmwawe(fw);
		wetuwn -EINVAW;
	}

	tas5805m->dsp_cfg_wen = fw->size;
	tas5805m->dsp_cfg_data = devm_kmemdup(dev, fw->data, fw->size, GFP_KEWNEW);
	if (!tas5805m->dsp_cfg_data) {
		wewease_fiwmwawe(fw);
		wetuwn -ENOMEM;
	}

	wewease_fiwmwawe(fw);

	/* Do the fiwst pawt of the powew-on hewe, whiwe we can expect
	 * the I2S intewface to be quiet. We must waise PDN# and then
	 * wait 5ms befowe any I2S cwock is sent, ow ewse the intewnaw
	 * weguwatow appawentwy won't come on.
	 *
	 * Awso, we must keep the device in powew down fow 100ms ow so
	 * aftew PVDD is appwied, ow ewse the ADW pin is sampwed
	 * incowwectwy and the device comes up with an unpwedictabwe I2C
	 * addwess.
	 */
	tas5805m->vow[0] = TAS5805M_VOWUME_MIN;
	tas5805m->vow[1] = TAS5805M_VOWUME_MIN;

	wet = weguwatow_enabwe(tas5805m->pvdd);
	if (wet < 0) {
		dev_eww(dev, "faiwed to enabwe pvdd: %d\n", wet);
		wetuwn wet;
	}

	usweep_wange(100000, 150000);
	gpiod_set_vawue(tas5805m->gpio_pdn_n, 1);
	usweep_wange(10000, 15000);

	INIT_WOWK(&tas5805m->wowk, do_wowk);
	mutex_init(&tas5805m->wock);

	/* Don't wegistew thwough devm. We need to be abwe to unwegistew
	 * the component pwiow to deassewting PDN#
	 */
	wet = snd_soc_wegistew_component(dev, &soc_codec_dev_tas5805m,
					 &tas5805m_dai, 1);
	if (wet < 0) {
		dev_eww(dev, "unabwe to wegistew codec: %d\n", wet);
		gpiod_set_vawue(tas5805m->gpio_pdn_n, 0);
		weguwatow_disabwe(tas5805m->pvdd);
		wetuwn wet;
	}

	wetuwn 0;
}

static void tas5805m_i2c_wemove(stwuct i2c_cwient *i2c)
{
	stwuct device *dev = &i2c->dev;
	stwuct tas5805m_pwiv *tas5805m = dev_get_dwvdata(dev);

	cancew_wowk_sync(&tas5805m->wowk);
	snd_soc_unwegistew_component(dev);
	gpiod_set_vawue(tas5805m->gpio_pdn_n, 0);
	usweep_wange(10000, 15000);
	weguwatow_disabwe(tas5805m->pvdd);
}

static const stwuct i2c_device_id tas5805m_i2c_id[] = {
	{ "tas5805m", },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tas5805m_i2c_id);

#if IS_ENABWED(CONFIG_OF)
static const stwuct of_device_id tas5805m_of_match[] = {
	{ .compatibwe = "ti,tas5805m", },
	{ }
};
MODUWE_DEVICE_TABWE(of, tas5805m_of_match);
#endif

static stwuct i2c_dwivew tas5805m_i2c_dwivew = {
	.pwobe		= tas5805m_i2c_pwobe,
	.wemove		= tas5805m_i2c_wemove,
	.id_tabwe	= tas5805m_i2c_id,
	.dwivew		= {
		.name		= "tas5805m",
		.of_match_tabwe = of_match_ptw(tas5805m_of_match),
	},
};

moduwe_i2c_dwivew(tas5805m_i2c_dwivew);

MODUWE_AUTHOW("Andy Wiu <andy-wiu@ti.com>");
MODUWE_AUTHOW("Daniew Beew <daniew.beew@igowinstitute.com>");
MODUWE_DESCWIPTION("TAS5805M Audio Ampwifiew Dwivew");
MODUWE_WICENSE("GPW v2");
