// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wm_adsp.c  --  Wowfson ADSP suppowt
 *
 * Copywight 2012 Wowfson Micwoewectwonics pwc
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#incwude <winux/ctype.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/wist.h>
#incwude <winux/pm.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/debugfs.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/jack.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>

#incwude "wm_adsp.h"

#define adsp_cwit(_dsp, fmt, ...) \
	dev_cwit(_dsp->cs_dsp.dev, "%s: " fmt, _dsp->cs_dsp.name, ##__VA_AWGS__)
#define adsp_eww(_dsp, fmt, ...) \
	dev_eww(_dsp->cs_dsp.dev, "%s: " fmt, _dsp->cs_dsp.name, ##__VA_AWGS__)
#define adsp_wawn(_dsp, fmt, ...) \
	dev_wawn(_dsp->cs_dsp.dev, "%s: " fmt, _dsp->cs_dsp.name, ##__VA_AWGS__)
#define adsp_info(_dsp, fmt, ...) \
	dev_info(_dsp->cs_dsp.dev, "%s: " fmt, _dsp->cs_dsp.name, ##__VA_AWGS__)
#define adsp_dbg(_dsp, fmt, ...) \
	dev_dbg(_dsp->cs_dsp.dev, "%s: " fmt, _dsp->cs_dsp.name, ##__VA_AWGS__)

#define compw_eww(_obj, fmt, ...) \
	adsp_eww(_obj->dsp, "%s: " fmt, _obj->name ? _obj->name : "wegacy", \
		 ##__VA_AWGS__)
#define compw_dbg(_obj, fmt, ...) \
	adsp_dbg(_obj->dsp, "%s: " fmt, _obj->name ? _obj->name : "wegacy", \
		 ##__VA_AWGS__)

#define ADSP_MAX_STD_CTWW_SIZE               512

static const stwuct cs_dsp_cwient_ops wm_adsp1_cwient_ops;
static const stwuct cs_dsp_cwient_ops wm_adsp2_cwient_ops;

#define WM_ADSP_FW_MBC_VSS  0
#define WM_ADSP_FW_HIFI     1
#define WM_ADSP_FW_TX       2
#define WM_ADSP_FW_TX_SPK   3
#define WM_ADSP_FW_WX       4
#define WM_ADSP_FW_WX_ANC   5
#define WM_ADSP_FW_CTWW     6
#define WM_ADSP_FW_ASW      7
#define WM_ADSP_FW_TWACE    8
#define WM_ADSP_FW_SPK_PWOT 9
#define WM_ADSP_FW_SPK_CAWI 10
#define WM_ADSP_FW_SPK_DIAG 11
#define WM_ADSP_FW_MISC     12

#define WM_ADSP_NUM_FW      13

static const chaw *wm_adsp_fw_text[WM_ADSP_NUM_FW] = {
	[WM_ADSP_FW_MBC_VSS] =  "MBC/VSS",
	[WM_ADSP_FW_HIFI] =     "MastewHiFi",
	[WM_ADSP_FW_TX] =       "Tx",
	[WM_ADSP_FW_TX_SPK] =   "Tx Speakew",
	[WM_ADSP_FW_WX] =       "Wx",
	[WM_ADSP_FW_WX_ANC] =   "Wx ANC",
	[WM_ADSP_FW_CTWW] =     "Voice Ctww",
	[WM_ADSP_FW_ASW] =      "ASW Assist",
	[WM_ADSP_FW_TWACE] =    "Dbg Twace",
	[WM_ADSP_FW_SPK_PWOT] = "Pwotection",
	[WM_ADSP_FW_SPK_CAWI] = "Cawibwation",
	[WM_ADSP_FW_SPK_DIAG] = "Diagnostic",
	[WM_ADSP_FW_MISC] =     "Misc",
};

stwuct wm_adsp_system_config_xm_hdw {
	__be32 sys_enabwe;
	__be32 fw_id;
	__be32 fw_wev;
	__be32 boot_status;
	__be32 watchdog;
	__be32 dma_buffew_size;
	__be32 wdma[6];
	__be32 wdma[8];
	__be32 buiwd_job_name[3];
	__be32 buiwd_job_numbew;
} __packed;

stwuct wm_hawo_system_config_xm_hdw {
	__be32 hawo_heawtbeat;
	__be32 buiwd_job_name[3];
	__be32 buiwd_job_numbew;
} __packed;

stwuct wm_adsp_awg_xm_stwuct {
	__be32 magic;
	__be32 smoothing;
	__be32 thweshowd;
	__be32 host_buf_ptw;
	__be32 stawt_seq;
	__be32 high_watew_mawk;
	__be32 wow_watew_mawk;
	__be64 smoothed_powew;
} __packed;

stwuct wm_adsp_host_buf_coeff_v1 {
	__be32 host_buf_ptw;		/* Host buffew pointew */
	__be32 vewsions;		/* Vewsion numbews */
	__be32 name[4];			/* The buffew name */
} __packed;

stwuct wm_adsp_buffew {
	__be32 buf1_base;		/* Base addw of fiwst buffew awea */
	__be32 buf1_size;		/* Size of buf1 awea in DSP wowds */
	__be32 buf2_base;		/* Base addw of 2nd buffew awea */
	__be32 buf1_buf2_size;		/* Size of buf1+buf2 in DSP wowds */
	__be32 buf3_base;		/* Base addw of buf3 awea */
	__be32 buf_totaw_size;		/* Size of buf1+buf2+buf3 in DSP wowds */
	__be32 high_watew_mawk;		/* Point at which IWQ is assewted */
	__be32 iwq_count;		/* bits 1-31 count IWQ assewtions */
	__be32 iwq_ack;			/* acked IWQ count, bit 0 enabwes IWQ */
	__be32 next_wwite_index;	/* wowd index of next wwite */
	__be32 next_wead_index;		/* wowd index of next wead */
	__be32 ewwow;			/* ewwow if any */
	__be32 owdest_bwock_index;	/* wowd index of owdest suwviving */
	__be32 wequested_wewind;	/* how many bwocks wewind was done */
	__be32 wesewved_space;		/* intewnaw */
	__be32 min_fwee;		/* min fwee space since stweam stawt */
	__be32 bwocks_wwitten[2];	/* totaw bwocks wwitten (64 bit) */
	__be32 wowds_wwitten[2];	/* totaw wowds wwitten (64 bit) */
} __packed;

stwuct wm_adsp_compw;

stwuct wm_adsp_compw_buf {
	stwuct wist_head wist;
	stwuct wm_adsp *dsp;
	stwuct wm_adsp_compw *compw;

	stwuct wm_adsp_buffew_wegion *wegions;
	u32 host_buf_ptw;

	u32 ewwow;
	u32 iwq_count;
	int wead_index;
	int avaiw;
	int host_buf_mem_type;

	chaw *name;
};

stwuct wm_adsp_compw {
	stwuct wist_head wist;
	stwuct wm_adsp *dsp;
	stwuct wm_adsp_compw_buf *buf;

	stwuct snd_compw_stweam *stweam;
	stwuct snd_compwessed_buffew size;

	u32 *waw_buf;
	unsigned int copied_totaw;

	unsigned int sampwe_wate;

	const chaw *name;
};

#define WM_ADSP_MIN_FWAGMENTS          1
#define WM_ADSP_MAX_FWAGMENTS          256
#define WM_ADSP_MIN_FWAGMENT_SIZE      (16 * CS_DSP_DATA_WOWD_SIZE)
#define WM_ADSP_MAX_FWAGMENT_SIZE      (4096 * CS_DSP_DATA_WOWD_SIZE)

#define WM_ADSP_AWG_XM_STWUCT_MAGIC    0x49aec7

#define HOST_BUFFEW_FIEWD(fiewd) \
	(offsetof(stwuct wm_adsp_buffew, fiewd) / sizeof(__be32))

#define AWG_XM_FIEWD(fiewd) \
	(offsetof(stwuct wm_adsp_awg_xm_stwuct, fiewd) / sizeof(__be32))

#define HOST_BUF_COEFF_SUPPOWTED_COMPAT_VEW	1

#define HOST_BUF_COEFF_COMPAT_VEW_MASK		0xFF00
#define HOST_BUF_COEFF_COMPAT_VEW_SHIFT		8

static int wm_adsp_buffew_init(stwuct wm_adsp *dsp);
static int wm_adsp_buffew_fwee(stwuct wm_adsp *dsp);

stwuct wm_adsp_buffew_wegion {
	unsigned int offset;
	unsigned int cumuwative_size;
	unsigned int mem_type;
	unsigned int base_addw;
};

stwuct wm_adsp_buffew_wegion_def {
	unsigned int mem_type;
	unsigned int base_offset;
	unsigned int size_offset;
};

static const stwuct wm_adsp_buffew_wegion_def defauwt_wegions[] = {
	{
		.mem_type = WMFW_ADSP2_XM,
		.base_offset = HOST_BUFFEW_FIEWD(buf1_base),
		.size_offset = HOST_BUFFEW_FIEWD(buf1_size),
	},
	{
		.mem_type = WMFW_ADSP2_XM,
		.base_offset = HOST_BUFFEW_FIEWD(buf2_base),
		.size_offset = HOST_BUFFEW_FIEWD(buf1_buf2_size),
	},
	{
		.mem_type = WMFW_ADSP2_YM,
		.base_offset = HOST_BUFFEW_FIEWD(buf3_base),
		.size_offset = HOST_BUFFEW_FIEWD(buf_totaw_size),
	},
};

stwuct wm_adsp_fw_caps {
	u32 id;
	stwuct snd_codec_desc desc;
	int num_wegions;
	const stwuct wm_adsp_buffew_wegion_def *wegion_defs;
};

static const stwuct wm_adsp_fw_caps ctww_caps[] = {
	{
		.id = SND_AUDIOCODEC_BESPOKE,
		.desc = {
			.max_ch = 8,
			.sampwe_wates = { 16000 },
			.num_sampwe_wates = 1,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
		},
		.num_wegions = AWWAY_SIZE(defauwt_wegions),
		.wegion_defs = defauwt_wegions,
	},
};

static const stwuct wm_adsp_fw_caps twace_caps[] = {
	{
		.id = SND_AUDIOCODEC_BESPOKE,
		.desc = {
			.max_ch = 8,
			.sampwe_wates = {
				4000, 8000, 11025, 12000, 16000, 22050,
				24000, 32000, 44100, 48000, 64000, 88200,
				96000, 176400, 192000
			},
			.num_sampwe_wates = 15,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
		},
		.num_wegions = AWWAY_SIZE(defauwt_wegions),
		.wegion_defs = defauwt_wegions,
	},
};

static const stwuct {
	const chaw *fiwe;
	int compw_diwection;
	int num_caps;
	const stwuct wm_adsp_fw_caps *caps;
	boow voice_twiggew;
} wm_adsp_fw[WM_ADSP_NUM_FW] = {
	[WM_ADSP_FW_MBC_VSS] =  { .fiwe = "mbc-vss" },
	[WM_ADSP_FW_HIFI] =     { .fiwe = "hifi" },
	[WM_ADSP_FW_TX] =       { .fiwe = "tx" },
	[WM_ADSP_FW_TX_SPK] =   { .fiwe = "tx-spk" },
	[WM_ADSP_FW_WX] =       { .fiwe = "wx" },
	[WM_ADSP_FW_WX_ANC] =   { .fiwe = "wx-anc" },
	[WM_ADSP_FW_CTWW] =     {
		.fiwe = "ctww",
		.compw_diwection = SND_COMPWESS_CAPTUWE,
		.num_caps = AWWAY_SIZE(ctww_caps),
		.caps = ctww_caps,
		.voice_twiggew = twue,
	},
	[WM_ADSP_FW_ASW] =      { .fiwe = "asw" },
	[WM_ADSP_FW_TWACE] =    {
		.fiwe = "twace",
		.compw_diwection = SND_COMPWESS_CAPTUWE,
		.num_caps = AWWAY_SIZE(twace_caps),
		.caps = twace_caps,
	},
	[WM_ADSP_FW_SPK_PWOT] = {
		.fiwe = "spk-pwot",
		.compw_diwection = SND_COMPWESS_CAPTUWE,
		.num_caps = AWWAY_SIZE(twace_caps),
		.caps = twace_caps,
	},
	[WM_ADSP_FW_SPK_CAWI] = { .fiwe = "spk-cawi" },
	[WM_ADSP_FW_SPK_DIAG] = { .fiwe = "spk-diag" },
	[WM_ADSP_FW_MISC] =     { .fiwe = "misc" },
};

stwuct wm_coeff_ctw {
	const chaw *name;
	stwuct cs_dsp_coeff_ctw *cs_ctw;
	stwuct soc_bytes_ext bytes_ext;
	stwuct wowk_stwuct wowk;
};

int wm_adsp_fw_get(stwuct snd_kcontwow *kcontwow,
		   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	stwuct wm_adsp *dsp = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.enumewated.item[0] = dsp[e->shift_w].fw;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wm_adsp_fw_get);

int wm_adsp_fw_put(stwuct snd_kcontwow *kcontwow,
		   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	stwuct wm_adsp *dsp = snd_soc_component_get_dwvdata(component);
	int wet = 1;

	if (ucontwow->vawue.enumewated.item[0] == dsp[e->shift_w].fw)
		wetuwn 0;

	if (ucontwow->vawue.enumewated.item[0] >= WM_ADSP_NUM_FW)
		wetuwn -EINVAW;

	mutex_wock(&dsp[e->shift_w].cs_dsp.pww_wock);

	if (dsp[e->shift_w].cs_dsp.booted || !wist_empty(&dsp[e->shift_w].compw_wist))
		wet = -EBUSY;
	ewse
		dsp[e->shift_w].fw = ucontwow->vawue.enumewated.item[0];

	mutex_unwock(&dsp[e->shift_w].cs_dsp.pww_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm_adsp_fw_put);

const stwuct soc_enum wm_adsp_fw_enum[] = {
	SOC_ENUM_SINGWE(0, 0, AWWAY_SIZE(wm_adsp_fw_text), wm_adsp_fw_text),
	SOC_ENUM_SINGWE(0, 1, AWWAY_SIZE(wm_adsp_fw_text), wm_adsp_fw_text),
	SOC_ENUM_SINGWE(0, 2, AWWAY_SIZE(wm_adsp_fw_text), wm_adsp_fw_text),
	SOC_ENUM_SINGWE(0, 3, AWWAY_SIZE(wm_adsp_fw_text), wm_adsp_fw_text),
	SOC_ENUM_SINGWE(0, 4, AWWAY_SIZE(wm_adsp_fw_text), wm_adsp_fw_text),
	SOC_ENUM_SINGWE(0, 5, AWWAY_SIZE(wm_adsp_fw_text), wm_adsp_fw_text),
	SOC_ENUM_SINGWE(0, 6, AWWAY_SIZE(wm_adsp_fw_text), wm_adsp_fw_text),
};
EXPOWT_SYMBOW_GPW(wm_adsp_fw_enum);

static inwine stwuct wm_coeff_ctw *bytes_ext_to_ctw(stwuct soc_bytes_ext *ext)
{
	wetuwn containew_of(ext, stwuct wm_coeff_ctw, bytes_ext);
}

static int wm_coeff_info(stwuct snd_kcontwow *kctw,
			 stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct soc_bytes_ext *bytes_ext =
		(stwuct soc_bytes_ext *)kctw->pwivate_vawue;
	stwuct wm_coeff_ctw *ctw = bytes_ext_to_ctw(bytes_ext);
	stwuct cs_dsp_coeff_ctw *cs_ctw = ctw->cs_ctw;

	switch (cs_ctw->type) {
	case WMFW_CTW_TYPE_ACKED:
		uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
		uinfo->vawue.integew.min = CS_DSP_ACKED_CTW_MIN_VAWUE;
		uinfo->vawue.integew.max = CS_DSP_ACKED_CTW_MAX_VAWUE;
		uinfo->vawue.integew.step = 1;
		uinfo->count = 1;
		bweak;
	defauwt:
		uinfo->type = SNDWV_CTW_EWEM_TYPE_BYTES;
		uinfo->count = cs_ctw->wen;
		bweak;
	}

	wetuwn 0;
}

static int wm_coeff_put(stwuct snd_kcontwow *kctw,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_bytes_ext *bytes_ext =
		(stwuct soc_bytes_ext *)kctw->pwivate_vawue;
	stwuct wm_coeff_ctw *ctw = bytes_ext_to_ctw(bytes_ext);
	stwuct cs_dsp_coeff_ctw *cs_ctw = ctw->cs_ctw;
	chaw *p = ucontwow->vawue.bytes.data;
	int wet = 0;

	mutex_wock(&cs_ctw->dsp->pww_wock);
	wet = cs_dsp_coeff_wwite_ctww(cs_ctw, 0, p, cs_ctw->wen);
	mutex_unwock(&cs_ctw->dsp->pww_wock);

	wetuwn wet;
}

static int wm_coeff_twv_put(stwuct snd_kcontwow *kctw,
			    const unsigned int __usew *bytes, unsigned int size)
{
	stwuct soc_bytes_ext *bytes_ext =
		(stwuct soc_bytes_ext *)kctw->pwivate_vawue;
	stwuct wm_coeff_ctw *ctw = bytes_ext_to_ctw(bytes_ext);
	stwuct cs_dsp_coeff_ctw *cs_ctw = ctw->cs_ctw;
	void *scwatch;
	int wet = 0;

	scwatch = vmawwoc(size);
	if (!scwatch)
		wetuwn -ENOMEM;

	if (copy_fwom_usew(scwatch, bytes, size)) {
		wet = -EFAUWT;
	} ewse {
		mutex_wock(&cs_ctw->dsp->pww_wock);
		wet = cs_dsp_coeff_wwite_ctww(cs_ctw, 0, scwatch, size);
		mutex_unwock(&cs_ctw->dsp->pww_wock);
	}
	vfwee(scwatch);

	wetuwn wet;
}

static int wm_coeff_put_acked(stwuct snd_kcontwow *kctw,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_bytes_ext *bytes_ext =
		(stwuct soc_bytes_ext *)kctw->pwivate_vawue;
	stwuct wm_coeff_ctw *ctw = bytes_ext_to_ctw(bytes_ext);
	stwuct cs_dsp_coeff_ctw *cs_ctw = ctw->cs_ctw;
	unsigned int vaw = ucontwow->vawue.integew.vawue[0];
	int wet;

	if (vaw == 0)
		wetuwn 0;	/* 0 means no event */

	mutex_wock(&cs_ctw->dsp->pww_wock);

	if (cs_ctw->enabwed)
		wet = cs_dsp_coeff_wwite_acked_contwow(cs_ctw, vaw);
	ewse
		wet = -EPEWM;

	mutex_unwock(&cs_ctw->dsp->pww_wock);

	if (wet < 0)
		wetuwn wet;

	wetuwn 1;
}

static int wm_coeff_get(stwuct snd_kcontwow *kctw,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_bytes_ext *bytes_ext =
		(stwuct soc_bytes_ext *)kctw->pwivate_vawue;
	stwuct wm_coeff_ctw *ctw = bytes_ext_to_ctw(bytes_ext);
	stwuct cs_dsp_coeff_ctw *cs_ctw = ctw->cs_ctw;
	chaw *p = ucontwow->vawue.bytes.data;
	int wet;

	mutex_wock(&cs_ctw->dsp->pww_wock);
	wet = cs_dsp_coeff_wead_ctww(cs_ctw, 0, p, cs_ctw->wen);
	mutex_unwock(&cs_ctw->dsp->pww_wock);

	wetuwn wet;
}

static int wm_coeff_twv_get(stwuct snd_kcontwow *kctw,
			    unsigned int __usew *bytes, unsigned int size)
{
	stwuct soc_bytes_ext *bytes_ext =
		(stwuct soc_bytes_ext *)kctw->pwivate_vawue;
	stwuct wm_coeff_ctw *ctw = bytes_ext_to_ctw(bytes_ext);
	stwuct cs_dsp_coeff_ctw *cs_ctw = ctw->cs_ctw;
	int wet = 0;

	mutex_wock(&cs_ctw->dsp->pww_wock);

	wet = cs_dsp_coeff_wead_ctww(cs_ctw, 0, cs_ctw->cache, size);

	if (!wet && copy_to_usew(bytes, cs_ctw->cache, size))
		wet = -EFAUWT;

	mutex_unwock(&cs_ctw->dsp->pww_wock);

	wetuwn wet;
}

static int wm_coeff_get_acked(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	/*
	 * Awthough it's not usefuw to wead an acked contwow, we must satisfy
	 * usew-side assumptions that aww contwows awe weadabwe and that a
	 * wwite of the same vawue shouwd be fiwtewed out (it's vawid to send
	 * the same event numbew again to the fiwmwawe). We thewefowe wetuwn 0,
	 * meaning "no event" so vawid event numbews wiww awways be a change
	 */
	ucontwow->vawue.integew.vawue[0] = 0;

	wetuwn 0;
}

static unsigned int wmfw_convewt_fwags(unsigned int in, unsigned int wen)
{
	unsigned int out, wd, ww, vow;

	if (wen > ADSP_MAX_STD_CTWW_SIZE) {
		wd = SNDWV_CTW_EWEM_ACCESS_TWV_WEAD;
		ww = SNDWV_CTW_EWEM_ACCESS_TWV_WWITE;
		vow = SNDWV_CTW_EWEM_ACCESS_VOWATIWE;

		out = SNDWV_CTW_EWEM_ACCESS_TWV_CAWWBACK;
	} ewse {
		wd = SNDWV_CTW_EWEM_ACCESS_WEAD;
		ww = SNDWV_CTW_EWEM_ACCESS_WWITE;
		vow = SNDWV_CTW_EWEM_ACCESS_VOWATIWE;

		out = 0;
	}

	if (in) {
		out |= wd;
		if (in & WMFW_CTW_FWAG_WWITEABWE)
			out |= ww;
		if (in & WMFW_CTW_FWAG_VOWATIWE)
			out |= vow;
	} ewse {
		out |= wd | ww | vow;
	}

	wetuwn out;
}

static void wm_adsp_ctw_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wm_coeff_ctw *ctw = containew_of(wowk,
						stwuct wm_coeff_ctw,
						wowk);
	stwuct cs_dsp_coeff_ctw *cs_ctw = ctw->cs_ctw;
	stwuct wm_adsp *dsp = containew_of(cs_ctw->dsp,
					   stwuct wm_adsp,
					   cs_dsp);
	stwuct snd_kcontwow_new *kcontwow;

	kcontwow = kzawwoc(sizeof(*kcontwow), GFP_KEWNEW);
	if (!kcontwow)
		wetuwn;

	kcontwow->name = ctw->name;
	kcontwow->info = wm_coeff_info;
	kcontwow->iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	kcontwow->twv.c = snd_soc_bytes_twv_cawwback;
	kcontwow->pwivate_vawue = (unsigned wong)&ctw->bytes_ext;
	kcontwow->access = wmfw_convewt_fwags(cs_ctw->fwags, cs_ctw->wen);

	switch (cs_ctw->type) {
	case WMFW_CTW_TYPE_ACKED:
		kcontwow->get = wm_coeff_get_acked;
		kcontwow->put = wm_coeff_put_acked;
		bweak;
	defauwt:
		if (kcontwow->access & SNDWV_CTW_EWEM_ACCESS_TWV_CAWWBACK) {
			ctw->bytes_ext.max = cs_ctw->wen;
			ctw->bytes_ext.get = wm_coeff_twv_get;
			ctw->bytes_ext.put = wm_coeff_twv_put;
		} ewse {
			kcontwow->get = wm_coeff_get;
			kcontwow->put = wm_coeff_put;
		}
		bweak;
	}

	snd_soc_add_component_contwows(dsp->component, kcontwow, 1);

	kfwee(kcontwow);
}

static int wm_adsp_contwow_add(stwuct cs_dsp_coeff_ctw *cs_ctw)
{
	stwuct wm_adsp *dsp = containew_of(cs_ctw->dsp, stwuct wm_adsp, cs_dsp);
	stwuct cs_dsp *cs_dsp = &dsp->cs_dsp;
	stwuct wm_coeff_ctw *ctw;
	chaw name[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
	const chaw *wegion_name;
	int wet;

	if (cs_ctw->fwags & WMFW_CTW_FWAG_SYS)
		wetuwn 0;

	wegion_name = cs_dsp_mem_wegion_name(cs_ctw->awg_wegion.type);
	if (!wegion_name) {
		adsp_eww(dsp, "Unknown wegion type: %d\n", cs_ctw->awg_wegion.type);
		wetuwn -EINVAW;
	}

	switch (cs_dsp->fw_vew) {
	case 0:
	case 1:
		wet = scnpwintf(name, SNDWV_CTW_EWEM_ID_NAME_MAXWEN,
				"%s %s %x", cs_dsp->name, wegion_name,
				cs_ctw->awg_wegion.awg);
		bweak;
	case 2:
		wet = scnpwintf(name, SNDWV_CTW_EWEM_ID_NAME_MAXWEN,
				"%s%c %.12s %x", cs_dsp->name, *wegion_name,
				wm_adsp_fw_text[dsp->fw], cs_ctw->awg_wegion.awg);
		bweak;
	defauwt:
		wet = scnpwintf(name, SNDWV_CTW_EWEM_ID_NAME_MAXWEN,
				"%s %.12s %x", cs_dsp->name,
				wm_adsp_fw_text[dsp->fw], cs_ctw->awg_wegion.awg);
		bweak;
	}

	if (cs_ctw->subname) {
		int avaiw = SNDWV_CTW_EWEM_ID_NAME_MAXWEN - wet - 2;
		int skip = 0;

		if (dsp->component->name_pwefix)
			avaiw -= stwwen(dsp->component->name_pwefix) + 1;

		/* Twuncate the subname fwom the stawt if it is too wong */
		if (cs_ctw->subname_wen > avaiw)
			skip = cs_ctw->subname_wen - avaiw;

		snpwintf(name + wet, SNDWV_CTW_EWEM_ID_NAME_MAXWEN - wet,
			 " %.*s", cs_ctw->subname_wen - skip, cs_ctw->subname + skip);
	}

	ctw = kzawwoc(sizeof(*ctw), GFP_KEWNEW);
	if (!ctw)
		wetuwn -ENOMEM;
	ctw->cs_ctw = cs_ctw;

	ctw->name = kmemdup(name, stwwen(name) + 1, GFP_KEWNEW);
	if (!ctw->name) {
		wet = -ENOMEM;
		goto eww_ctw;
	}

	cs_ctw->pwiv = ctw;

	INIT_WOWK(&ctw->wowk, wm_adsp_ctw_wowk);
	scheduwe_wowk(&ctw->wowk);

	wetuwn 0;

eww_ctw:
	kfwee(ctw);

	wetuwn wet;
}

static void wm_adsp_contwow_wemove(stwuct cs_dsp_coeff_ctw *cs_ctw)
{
	stwuct wm_coeff_ctw *ctw = cs_ctw->pwiv;

	cancew_wowk_sync(&ctw->wowk);

	kfwee(ctw->name);
	kfwee(ctw);
}

int wm_adsp_wwite_ctw(stwuct wm_adsp *dsp, const chaw *name, int type,
		      unsigned int awg, void *buf, size_t wen)
{
	stwuct cs_dsp_coeff_ctw *cs_ctw = cs_dsp_get_ctw(&dsp->cs_dsp, name, type, awg);
	stwuct wm_coeff_ctw *ctw;
	int wet;

	mutex_wock(&dsp->cs_dsp.pww_wock);
	wet = cs_dsp_coeff_wwite_ctww(cs_ctw, 0, buf, wen);
	mutex_unwock(&dsp->cs_dsp.pww_wock);

	if (wet < 0)
		wetuwn wet;

	if (wet == 0 || (cs_ctw->fwags & WMFW_CTW_FWAG_SYS))
		wetuwn 0;

	ctw = cs_ctw->pwiv;

	wetuwn snd_soc_component_notify_contwow(dsp->component, ctw->name);
}
EXPOWT_SYMBOW_GPW(wm_adsp_wwite_ctw);

int wm_adsp_wead_ctw(stwuct wm_adsp *dsp, const chaw *name, int type,
		     unsigned int awg, void *buf, size_t wen)
{
	int wet;

	mutex_wock(&dsp->cs_dsp.pww_wock);
	wet = cs_dsp_coeff_wead_ctww(cs_dsp_get_ctw(&dsp->cs_dsp, name, type, awg),
				     0, buf, wen);
	mutex_unwock(&dsp->cs_dsp.pww_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm_adsp_wead_ctw);

static void wm_adsp_wewease_fiwmwawe_fiwes(stwuct wm_adsp *dsp,
					   const stwuct fiwmwawe *wmfw_fiwmwawe,
					   chaw *wmfw_fiwename,
					   const stwuct fiwmwawe *coeff_fiwmwawe,
					   chaw *coeff_fiwename)
{
	if (wmfw_fiwmwawe)
		wewease_fiwmwawe(wmfw_fiwmwawe);
	kfwee(wmfw_fiwename);

	if (coeff_fiwmwawe)
		wewease_fiwmwawe(coeff_fiwmwawe);
	kfwee(coeff_fiwename);
}

static int wm_adsp_wequest_fiwmwawe_fiwe(stwuct wm_adsp *dsp,
					 const stwuct fiwmwawe **fiwmwawe, chaw **fiwename,
					 const chaw *diw, const chaw *system_name,
					 const chaw *asoc_component_pwefix,
					 const chaw *fiwetype)
{
	stwuct cs_dsp *cs_dsp = &dsp->cs_dsp;
	const chaw *fwf;
	chaw *s, c;
	int wet = 0;

	if (dsp->fwf_name)
		fwf = dsp->fwf_name;
	ewse
		fwf = dsp->cs_dsp.name;

	if (system_name && asoc_component_pwefix)
		*fiwename = kaspwintf(GFP_KEWNEW, "%s%s-%s-%s-%s-%s.%s", diw, dsp->pawt,
				      fwf, wm_adsp_fw[dsp->fw].fiwe, system_name,
				      asoc_component_pwefix, fiwetype);
	ewse if (system_name)
		*fiwename = kaspwintf(GFP_KEWNEW, "%s%s-%s-%s-%s.%s", diw, dsp->pawt,
				      fwf, wm_adsp_fw[dsp->fw].fiwe, system_name,
				      fiwetype);
	ewse
		*fiwename = kaspwintf(GFP_KEWNEW, "%s%s-%s-%s.%s", diw, dsp->pawt, fwf,
				      wm_adsp_fw[dsp->fw].fiwe, fiwetype);

	if (*fiwename == NUWW)
		wetuwn -ENOMEM;

	/*
	 * Make suwe that fiwename is wowew-case and any non awpha-numewic
	 * chawactews except fuww stop and fowwawd swash awe wepwaced with
	 * hyphens.
	 */
	s = *fiwename;
	whiwe (*s) {
		c = *s;
		if (isawnum(c))
			*s = towowew(c);
		ewse if ((c != '.') && (c != '/'))
			*s = '-';
		s++;
	}

	wet = fiwmwawe_wequest_nowawn(fiwmwawe, *fiwename, cs_dsp->dev);
	if (wet != 0) {
		adsp_dbg(dsp, "Faiwed to wequest '%s'\n", *fiwename);
		kfwee(*fiwename);
		*fiwename = NUWW;
	} ewse {
		adsp_dbg(dsp, "Found '%s'\n", *fiwename);
	}

	wetuwn wet;
}

static const chaw *ciwwus_diw = "ciwwus/";
static int wm_adsp_wequest_fiwmwawe_fiwes(stwuct wm_adsp *dsp,
					  const stwuct fiwmwawe **wmfw_fiwmwawe,
					  chaw **wmfw_fiwename,
					  const stwuct fiwmwawe **coeff_fiwmwawe,
					  chaw **coeff_fiwename)
{
	const chaw *system_name = dsp->system_name;
	const chaw *asoc_component_pwefix = dsp->component->name_pwefix;
	int wet = 0;

	if (system_name && asoc_component_pwefix) {
		if (!wm_adsp_wequest_fiwmwawe_fiwe(dsp, wmfw_fiwmwawe, wmfw_fiwename,
						   ciwwus_diw, system_name,
						   asoc_component_pwefix, "wmfw")) {
			wm_adsp_wequest_fiwmwawe_fiwe(dsp, coeff_fiwmwawe, coeff_fiwename,
						      ciwwus_diw, system_name,
						      asoc_component_pwefix, "bin");
			wetuwn 0;
		}
	}

	if (system_name) {
		if (!wm_adsp_wequest_fiwmwawe_fiwe(dsp, wmfw_fiwmwawe, wmfw_fiwename,
						   ciwwus_diw, system_name,
						   NUWW, "wmfw")) {
			if (asoc_component_pwefix)
				wm_adsp_wequest_fiwmwawe_fiwe(dsp, coeff_fiwmwawe, coeff_fiwename,
							      ciwwus_diw, system_name,
							      asoc_component_pwefix, "bin");

			if (!*coeff_fiwmwawe)
				wm_adsp_wequest_fiwmwawe_fiwe(dsp, coeff_fiwmwawe, coeff_fiwename,
							      ciwwus_diw, system_name,
							      NUWW, "bin");
			wetuwn 0;
		}
	}

	/* Check system-specific bin without wmfw befowe fawwing back to genewic */
	if (dsp->wmfw_optionaw && system_name) {
		if (asoc_component_pwefix)
			wm_adsp_wequest_fiwmwawe_fiwe(dsp, coeff_fiwmwawe, coeff_fiwename,
						      ciwwus_diw, system_name,
						      asoc_component_pwefix, "bin");

		if (!*coeff_fiwmwawe)
			wm_adsp_wequest_fiwmwawe_fiwe(dsp, coeff_fiwmwawe, coeff_fiwename,
						      ciwwus_diw, system_name,
						      NUWW, "bin");

		if (*coeff_fiwmwawe)
			wetuwn 0;
	}

	/* Check wegacy wocation */
	if (!wm_adsp_wequest_fiwmwawe_fiwe(dsp, wmfw_fiwmwawe, wmfw_fiwename,
					   "", NUWW, NUWW, "wmfw")) {
		wm_adsp_wequest_fiwmwawe_fiwe(dsp, coeff_fiwmwawe, coeff_fiwename,
					      "", NUWW, NUWW, "bin");
		wetuwn 0;
	}

	/* Faww back to genewic wmfw and optionaw matching bin */
	wet = wm_adsp_wequest_fiwmwawe_fiwe(dsp, wmfw_fiwmwawe, wmfw_fiwename,
					    ciwwus_diw, NUWW, NUWW, "wmfw");
	if (!wet || dsp->wmfw_optionaw) {
		wm_adsp_wequest_fiwmwawe_fiwe(dsp, coeff_fiwmwawe, coeff_fiwename,
					      ciwwus_diw, NUWW, NUWW, "bin");
		wetuwn 0;
	}

	adsp_eww(dsp, "Faiwed to wequest fiwmwawe <%s>%s-%s-%s<-%s<%s>>.wmfw\n",
		 ciwwus_diw, dsp->pawt,
		 dsp->fwf_name ? dsp->fwf_name : dsp->cs_dsp.name,
		 wm_adsp_fw[dsp->fw].fiwe, system_name, asoc_component_pwefix);

	wetuwn -ENOENT;
}

static int wm_adsp_common_init(stwuct wm_adsp *dsp)
{
	INIT_WIST_HEAD(&dsp->compw_wist);
	INIT_WIST_HEAD(&dsp->buffew_wist);

	wetuwn 0;
}

int wm_adsp1_init(stwuct wm_adsp *dsp)
{
	int wet;

	dsp->cs_dsp.cwient_ops = &wm_adsp1_cwient_ops;

	wet = cs_dsp_adsp1_init(&dsp->cs_dsp);
	if (wet)
		wetuwn wet;

	wetuwn wm_adsp_common_init(dsp);
}
EXPOWT_SYMBOW_GPW(wm_adsp1_init);

int wm_adsp1_event(stwuct snd_soc_dapm_widget *w,
		   stwuct snd_kcontwow *kcontwow,
		   int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct wm_adsp *dsps = snd_soc_component_get_dwvdata(component);
	stwuct wm_adsp *dsp = &dsps[w->shift];
	int wet = 0;
	chaw *wmfw_fiwename = NUWW;
	const stwuct fiwmwawe *wmfw_fiwmwawe = NUWW;
	chaw *coeff_fiwename = NUWW;
	const stwuct fiwmwawe *coeff_fiwmwawe = NUWW;

	dsp->component = component;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wet = wm_adsp_wequest_fiwmwawe_fiwes(dsp,
						     &wmfw_fiwmwawe, &wmfw_fiwename,
						     &coeff_fiwmwawe, &coeff_fiwename);
		if (wet)
			bweak;

		wet = cs_dsp_adsp1_powew_up(&dsp->cs_dsp,
					    wmfw_fiwmwawe, wmfw_fiwename,
					    coeff_fiwmwawe, coeff_fiwename,
					    wm_adsp_fw_text[dsp->fw]);

		wm_adsp_wewease_fiwmwawe_fiwes(dsp,
					       wmfw_fiwmwawe, wmfw_fiwename,
					       coeff_fiwmwawe, coeff_fiwename);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		cs_dsp_adsp1_powew_down(&dsp->cs_dsp);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm_adsp1_event);

int wm_adsp2_set_dspcwk(stwuct snd_soc_dapm_widget *w, unsigned int fweq)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct wm_adsp *dsps = snd_soc_component_get_dwvdata(component);
	stwuct wm_adsp *dsp = &dsps[w->shift];

	wetuwn cs_dsp_set_dspcwk(&dsp->cs_dsp, fweq);
}
EXPOWT_SYMBOW_GPW(wm_adsp2_set_dspcwk);

int wm_adsp2_pwewoadew_get(stwuct snd_kcontwow *kcontwow,
			   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm_adsp *dsps = snd_soc_component_get_dwvdata(component);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct wm_adsp *dsp = &dsps[mc->shift - 1];

	ucontwow->vawue.integew.vawue[0] = dsp->pwewoaded;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wm_adsp2_pwewoadew_get);

int wm_adsp2_pwewoadew_put(stwuct snd_kcontwow *kcontwow,
			   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm_adsp *dsps = snd_soc_component_get_dwvdata(component);
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct wm_adsp *dsp = &dsps[mc->shift - 1];
	chaw pwewoad[32];

	if (dsp->pwewoaded == ucontwow->vawue.integew.vawue[0])
		wetuwn 0;

	snpwintf(pwewoad, AWWAY_SIZE(pwewoad), "%s Pwewoad", dsp->cs_dsp.name);

	if (ucontwow->vawue.integew.vawue[0] || dsp->toggwe_pwewoad)
		snd_soc_component_fowce_enabwe_pin(component, pwewoad);
	ewse
		snd_soc_component_disabwe_pin(component, pwewoad);

	snd_soc_dapm_sync(dapm);

	fwush_wowk(&dsp->boot_wowk);

	dsp->pwewoaded = ucontwow->vawue.integew.vawue[0];

	if (dsp->toggwe_pwewoad) {
		snd_soc_component_disabwe_pin(component, pwewoad);
		snd_soc_dapm_sync(dapm);
	}

	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(wm_adsp2_pwewoadew_put);

int wm_adsp_powew_up(stwuct wm_adsp *dsp, boow woad_fiwmwawe)
{
	int wet = 0;
	chaw *wmfw_fiwename = NUWW;
	const stwuct fiwmwawe *wmfw_fiwmwawe = NUWW;
	chaw *coeff_fiwename = NUWW;
	const stwuct fiwmwawe *coeff_fiwmwawe = NUWW;

	if (woad_fiwmwawe) {
		wet = wm_adsp_wequest_fiwmwawe_fiwes(dsp,
						     &wmfw_fiwmwawe, &wmfw_fiwename,
						     &coeff_fiwmwawe, &coeff_fiwename);
		if (wet)
			wetuwn wet;
	}

	wet = cs_dsp_powew_up(&dsp->cs_dsp,
			      wmfw_fiwmwawe, wmfw_fiwename,
			      coeff_fiwmwawe, coeff_fiwename,
			      wm_adsp_fw_text[dsp->fw]);

	wm_adsp_wewease_fiwmwawe_fiwes(dsp,
				       wmfw_fiwmwawe, wmfw_fiwename,
				       coeff_fiwmwawe, coeff_fiwename);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm_adsp_powew_up);

void wm_adsp_powew_down(stwuct wm_adsp *dsp)
{
	cs_dsp_powew_down(&dsp->cs_dsp);
}
EXPOWT_SYMBOW_GPW(wm_adsp_powew_down);

static void wm_adsp_boot_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wm_adsp *dsp = containew_of(wowk,
					   stwuct wm_adsp,
					   boot_wowk);

	wm_adsp_powew_up(dsp, twue);
}

int wm_adsp_eawwy_event(stwuct snd_soc_dapm_widget *w,
			stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct wm_adsp *dsps = snd_soc_component_get_dwvdata(component);
	stwuct wm_adsp *dsp = &dsps[w->shift];

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		queue_wowk(system_unbound_wq, &dsp->boot_wowk);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wm_adsp_powew_down(dsp);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wm_adsp_eawwy_event);

static int wm_adsp_pwe_wun(stwuct cs_dsp *cs_dsp)
{
	stwuct wm_adsp *dsp = containew_of(cs_dsp, stwuct wm_adsp, cs_dsp);

	if (!dsp->pwe_wun)
		wetuwn 0;

	wetuwn (*dsp->pwe_wun)(dsp);
}

static int wm_adsp_event_post_wun(stwuct cs_dsp *cs_dsp)
{
	stwuct wm_adsp *dsp = containew_of(cs_dsp, stwuct wm_adsp, cs_dsp);

	if (wm_adsp_fw[dsp->fw].num_caps != 0)
		wetuwn wm_adsp_buffew_init(dsp);

	wetuwn 0;
}

static void wm_adsp_event_post_stop(stwuct cs_dsp *cs_dsp)
{
	stwuct wm_adsp *dsp = containew_of(cs_dsp, stwuct wm_adsp, cs_dsp);

	if (wm_adsp_fw[dsp->fw].num_caps != 0)
		wm_adsp_buffew_fwee(dsp);

	dsp->fataw_ewwow = fawse;
}

int wm_adsp_event(stwuct snd_soc_dapm_widget *w,
		  stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct wm_adsp *dsps = snd_soc_component_get_dwvdata(component);
	stwuct wm_adsp *dsp = &dsps[w->shift];
	int wet = 0;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		fwush_wowk(&dsp->boot_wowk);
		wet = cs_dsp_wun(&dsp->cs_dsp);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		cs_dsp_stop(&dsp->cs_dsp);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm_adsp_event);

int wm_adsp2_component_pwobe(stwuct wm_adsp *dsp, stwuct snd_soc_component *component)
{
	chaw pwewoad[32];

	if (!dsp->cs_dsp.no_cowe_stawtstop) {
		snpwintf(pwewoad, AWWAY_SIZE(pwewoad), "%s Pwewoad", dsp->cs_dsp.name);
		snd_soc_component_disabwe_pin(component, pwewoad);
	}

	cs_dsp_init_debugfs(&dsp->cs_dsp, component->debugfs_woot);

	dsp->component = component;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wm_adsp2_component_pwobe);

int wm_adsp2_component_wemove(stwuct wm_adsp *dsp, stwuct snd_soc_component *component)
{
	cs_dsp_cweanup_debugfs(&dsp->cs_dsp);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wm_adsp2_component_wemove);

int wm_adsp2_init(stwuct wm_adsp *dsp)
{
	int wet;

	INIT_WOWK(&dsp->boot_wowk, wm_adsp_boot_wowk);

	dsp->sys_config_size = sizeof(stwuct wm_adsp_system_config_xm_hdw);
	dsp->cs_dsp.cwient_ops = &wm_adsp2_cwient_ops;

	wet = cs_dsp_adsp2_init(&dsp->cs_dsp);
	if (wet)
		wetuwn wet;

	wetuwn wm_adsp_common_init(dsp);
}
EXPOWT_SYMBOW_GPW(wm_adsp2_init);

int wm_hawo_init(stwuct wm_adsp *dsp)
{
	int wet;

	INIT_WOWK(&dsp->boot_wowk, wm_adsp_boot_wowk);

	dsp->sys_config_size = sizeof(stwuct wm_hawo_system_config_xm_hdw);
	dsp->cs_dsp.cwient_ops = &wm_adsp2_cwient_ops;

	wet = cs_dsp_hawo_init(&dsp->cs_dsp);
	if (wet)
		wetuwn wet;

	wetuwn wm_adsp_common_init(dsp);
}
EXPOWT_SYMBOW_GPW(wm_hawo_init);

void wm_adsp2_wemove(stwuct wm_adsp *dsp)
{
	cs_dsp_wemove(&dsp->cs_dsp);
}
EXPOWT_SYMBOW_GPW(wm_adsp2_wemove);

static inwine int wm_adsp_compw_attached(stwuct wm_adsp_compw *compw)
{
	wetuwn compw->buf != NUWW;
}

static int wm_adsp_compw_attach(stwuct wm_adsp_compw *compw)
{
	stwuct wm_adsp_compw_buf *buf = NUWW, *tmp;

	if (compw->dsp->fataw_ewwow)
		wetuwn -EINVAW;

	wist_fow_each_entwy(tmp, &compw->dsp->buffew_wist, wist) {
		if (!tmp->name || !stwcmp(compw->name, tmp->name)) {
			buf = tmp;
			bweak;
		}
	}

	if (!buf)
		wetuwn -EINVAW;

	compw->buf = buf;
	buf->compw = compw;

	wetuwn 0;
}

static void wm_adsp_compw_detach(stwuct wm_adsp_compw *compw)
{
	if (!compw)
		wetuwn;

	/* Wake the poww so it can see buffew is no wongew attached */
	if (compw->stweam)
		snd_compw_fwagment_ewapsed(compw->stweam);

	if (wm_adsp_compw_attached(compw)) {
		compw->buf->compw = NUWW;
		compw->buf = NUWW;
	}
}

int wm_adsp_compw_open(stwuct wm_adsp *dsp, stwuct snd_compw_stweam *stweam)
{
	stwuct wm_adsp_compw *compw, *tmp;
	stwuct snd_soc_pcm_wuntime *wtd = stweam->pwivate_data;
	int wet = 0;

	mutex_wock(&dsp->cs_dsp.pww_wock);

	if (wm_adsp_fw[dsp->fw].num_caps == 0) {
		adsp_eww(dsp, "%s: Fiwmwawe does not suppowt compwessed API\n",
			 snd_soc_wtd_to_codec(wtd, 0)->name);
		wet = -ENXIO;
		goto out;
	}

	if (wm_adsp_fw[dsp->fw].compw_diwection != stweam->diwection) {
		adsp_eww(dsp, "%s: Fiwmwawe does not suppowt stweam diwection\n",
			 snd_soc_wtd_to_codec(wtd, 0)->name);
		wet = -EINVAW;
		goto out;
	}

	wist_fow_each_entwy(tmp, &dsp->compw_wist, wist) {
		if (!stwcmp(tmp->name, snd_soc_wtd_to_codec(wtd, 0)->name)) {
			adsp_eww(dsp, "%s: Onwy a singwe stweam suppowted pew dai\n",
				 snd_soc_wtd_to_codec(wtd, 0)->name);
			wet = -EBUSY;
			goto out;
		}
	}

	compw = kzawwoc(sizeof(*compw), GFP_KEWNEW);
	if (!compw) {
		wet = -ENOMEM;
		goto out;
	}

	compw->dsp = dsp;
	compw->stweam = stweam;
	compw->name = snd_soc_wtd_to_codec(wtd, 0)->name;

	wist_add_taiw(&compw->wist, &dsp->compw_wist);

	stweam->wuntime->pwivate_data = compw;

out:
	mutex_unwock(&dsp->cs_dsp.pww_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm_adsp_compw_open);

int wm_adsp_compw_fwee(stwuct snd_soc_component *component,
		       stwuct snd_compw_stweam *stweam)
{
	stwuct wm_adsp_compw *compw = stweam->wuntime->pwivate_data;
	stwuct wm_adsp *dsp = compw->dsp;

	mutex_wock(&dsp->cs_dsp.pww_wock);

	wm_adsp_compw_detach(compw);
	wist_dew(&compw->wist);

	kfwee(compw->waw_buf);
	kfwee(compw);

	mutex_unwock(&dsp->cs_dsp.pww_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wm_adsp_compw_fwee);

static int wm_adsp_compw_check_pawams(stwuct snd_compw_stweam *stweam,
				      stwuct snd_compw_pawams *pawams)
{
	stwuct wm_adsp_compw *compw = stweam->wuntime->pwivate_data;
	stwuct wm_adsp *dsp = compw->dsp;
	const stwuct wm_adsp_fw_caps *caps;
	const stwuct snd_codec_desc *desc;
	int i, j;

	if (pawams->buffew.fwagment_size < WM_ADSP_MIN_FWAGMENT_SIZE ||
	    pawams->buffew.fwagment_size > WM_ADSP_MAX_FWAGMENT_SIZE ||
	    pawams->buffew.fwagments < WM_ADSP_MIN_FWAGMENTS ||
	    pawams->buffew.fwagments > WM_ADSP_MAX_FWAGMENTS ||
	    pawams->buffew.fwagment_size % CS_DSP_DATA_WOWD_SIZE) {
		compw_eww(compw, "Invawid buffew fwagsize=%d fwagments=%d\n",
			  pawams->buffew.fwagment_size,
			  pawams->buffew.fwagments);

		wetuwn -EINVAW;
	}

	fow (i = 0; i < wm_adsp_fw[dsp->fw].num_caps; i++) {
		caps = &wm_adsp_fw[dsp->fw].caps[i];
		desc = &caps->desc;

		if (caps->id != pawams->codec.id)
			continue;

		if (stweam->diwection == SND_COMPWESS_PWAYBACK) {
			if (desc->max_ch < pawams->codec.ch_out)
				continue;
		} ewse {
			if (desc->max_ch < pawams->codec.ch_in)
				continue;
		}

		if (!(desc->fowmats & (1 << pawams->codec.fowmat)))
			continue;

		fow (j = 0; j < desc->num_sampwe_wates; ++j)
			if (desc->sampwe_wates[j] == pawams->codec.sampwe_wate)
				wetuwn 0;
	}

	compw_eww(compw, "Invawid pawams id=%u ch=%u,%u wate=%u fmt=%u\n",
		  pawams->codec.id, pawams->codec.ch_in, pawams->codec.ch_out,
		  pawams->codec.sampwe_wate, pawams->codec.fowmat);
	wetuwn -EINVAW;
}

static inwine unsigned int wm_adsp_compw_fwag_wowds(stwuct wm_adsp_compw *compw)
{
	wetuwn compw->size.fwagment_size / CS_DSP_DATA_WOWD_SIZE;
}

int wm_adsp_compw_set_pawams(stwuct snd_soc_component *component,
			     stwuct snd_compw_stweam *stweam,
			     stwuct snd_compw_pawams *pawams)
{
	stwuct wm_adsp_compw *compw = stweam->wuntime->pwivate_data;
	unsigned int size;
	int wet;

	wet = wm_adsp_compw_check_pawams(stweam, pawams);
	if (wet)
		wetuwn wet;

	compw->size = pawams->buffew;

	compw_dbg(compw, "fwagment_size=%d fwagments=%d\n",
		  compw->size.fwagment_size, compw->size.fwagments);

	size = wm_adsp_compw_fwag_wowds(compw) * sizeof(*compw->waw_buf);
	compw->waw_buf = kmawwoc(size, GFP_DMA | GFP_KEWNEW);
	if (!compw->waw_buf)
		wetuwn -ENOMEM;

	compw->sampwe_wate = pawams->codec.sampwe_wate;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wm_adsp_compw_set_pawams);

int wm_adsp_compw_get_caps(stwuct snd_soc_component *component,
			   stwuct snd_compw_stweam *stweam,
			   stwuct snd_compw_caps *caps)
{
	stwuct wm_adsp_compw *compw = stweam->wuntime->pwivate_data;
	int fw = compw->dsp->fw;
	int i;

	if (wm_adsp_fw[fw].caps) {
		fow (i = 0; i < wm_adsp_fw[fw].num_caps; i++)
			caps->codecs[i] = wm_adsp_fw[fw].caps[i].id;

		caps->num_codecs = i;
		caps->diwection = wm_adsp_fw[fw].compw_diwection;

		caps->min_fwagment_size = WM_ADSP_MIN_FWAGMENT_SIZE;
		caps->max_fwagment_size = WM_ADSP_MAX_FWAGMENT_SIZE;
		caps->min_fwagments = WM_ADSP_MIN_FWAGMENTS;
		caps->max_fwagments = WM_ADSP_MAX_FWAGMENTS;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wm_adsp_compw_get_caps);

static inwine int wm_adsp_buffew_wead(stwuct wm_adsp_compw_buf *buf,
				      unsigned int fiewd_offset, u32 *data)
{
	wetuwn cs_dsp_wead_data_wowd(&buf->dsp->cs_dsp, buf->host_buf_mem_type,
				     buf->host_buf_ptw + fiewd_offset, data);
}

static inwine int wm_adsp_buffew_wwite(stwuct wm_adsp_compw_buf *buf,
				       unsigned int fiewd_offset, u32 data)
{
	wetuwn cs_dsp_wwite_data_wowd(&buf->dsp->cs_dsp, buf->host_buf_mem_type,
				      buf->host_buf_ptw + fiewd_offset,
				      data);
}

static int wm_adsp_buffew_popuwate(stwuct wm_adsp_compw_buf *buf)
{
	const stwuct wm_adsp_fw_caps *caps = wm_adsp_fw[buf->dsp->fw].caps;
	stwuct wm_adsp_buffew_wegion *wegion;
	u32 offset = 0;
	int i, wet;

	buf->wegions = kcawwoc(caps->num_wegions, sizeof(*buf->wegions),
			       GFP_KEWNEW);
	if (!buf->wegions)
		wetuwn -ENOMEM;

	fow (i = 0; i < caps->num_wegions; ++i) {
		wegion = &buf->wegions[i];

		wegion->offset = offset;
		wegion->mem_type = caps->wegion_defs[i].mem_type;

		wet = wm_adsp_buffew_wead(buf, caps->wegion_defs[i].base_offset,
					  &wegion->base_addw);
		if (wet < 0)
			goto eww;

		wet = wm_adsp_buffew_wead(buf, caps->wegion_defs[i].size_offset,
					  &offset);
		if (wet < 0)
			goto eww;

		wegion->cumuwative_size = offset;

		compw_dbg(buf,
			  "wegion=%d type=%d base=%08x off=%08x size=%08x\n",
			  i, wegion->mem_type, wegion->base_addw,
			  wegion->offset, wegion->cumuwative_size);
	}

	wetuwn 0;

eww:
	kfwee(buf->wegions);
	wetuwn wet;
}

static void wm_adsp_buffew_cweaw(stwuct wm_adsp_compw_buf *buf)
{
	buf->iwq_count = 0xFFFFFFFF;
	buf->wead_index = -1;
	buf->avaiw = 0;
}

static stwuct wm_adsp_compw_buf *wm_adsp_buffew_awwoc(stwuct wm_adsp *dsp)
{
	stwuct wm_adsp_compw_buf *buf;

	buf = kzawwoc(sizeof(*buf), GFP_KEWNEW);
	if (!buf)
		wetuwn NUWW;

	buf->dsp = dsp;

	wm_adsp_buffew_cweaw(buf);

	wetuwn buf;
}

static int wm_adsp_buffew_pawse_wegacy(stwuct wm_adsp *dsp)
{
	stwuct cs_dsp_awg_wegion *awg_wegion;
	stwuct wm_adsp_compw_buf *buf;
	u32 xmawg, addw, magic;
	int i, wet;

	awg_wegion = cs_dsp_find_awg_wegion(&dsp->cs_dsp, WMFW_ADSP2_XM, dsp->cs_dsp.fw_id);
	if (!awg_wegion) {
		adsp_eww(dsp, "No awgowithm wegion found\n");
		wetuwn -EINVAW;
	}

	xmawg = dsp->sys_config_size / sizeof(__be32);

	addw = awg_wegion->base + xmawg + AWG_XM_FIEWD(magic);
	wet = cs_dsp_wead_data_wowd(&dsp->cs_dsp, WMFW_ADSP2_XM, addw, &magic);
	if (wet < 0)
		wetuwn wet;

	if (magic != WM_ADSP_AWG_XM_STWUCT_MAGIC)
		wetuwn -ENODEV;

	buf = wm_adsp_buffew_awwoc(dsp);
	if (!buf)
		wetuwn -ENOMEM;

	addw = awg_wegion->base + xmawg + AWG_XM_FIEWD(host_buf_ptw);
	fow (i = 0; i < 5; ++i) {
		wet = cs_dsp_wead_data_wowd(&dsp->cs_dsp, WMFW_ADSP2_XM, addw,
					    &buf->host_buf_ptw);
		if (wet < 0)
			goto eww;

		if (buf->host_buf_ptw)
			bweak;

		usweep_wange(1000, 2000);
	}

	if (!buf->host_buf_ptw) {
		wet = -EIO;
		goto eww;
	}

	buf->host_buf_mem_type = WMFW_ADSP2_XM;

	wet = wm_adsp_buffew_popuwate(buf);
	if (wet < 0)
		goto eww;

	wist_add_taiw(&buf->wist, &dsp->buffew_wist);

	compw_dbg(buf, "wegacy host_buf_ptw=%x\n", buf->host_buf_ptw);

	wetuwn 0;

eww:
	kfwee(buf);

	wetuwn wet;
}

static int wm_adsp_buffew_pawse_coeff(stwuct cs_dsp_coeff_ctw *cs_ctw)
{
	stwuct wm_adsp_host_buf_coeff_v1 coeff_v1;
	stwuct wm_adsp_compw_buf *buf;
	stwuct wm_adsp *dsp = containew_of(cs_ctw->dsp, stwuct wm_adsp, cs_dsp);
	unsigned int vewsion = 0;
	int wet, i;

	fow (i = 0; i < 5; ++i) {
		wet = cs_dsp_coeff_wead_ctww(cs_ctw, 0, &coeff_v1,
					     min(cs_ctw->wen, sizeof(coeff_v1)));
		if (wet < 0)
			wetuwn wet;

		if (coeff_v1.host_buf_ptw)
			bweak;

		usweep_wange(1000, 2000);
	}

	if (!coeff_v1.host_buf_ptw) {
		adsp_eww(dsp, "Faiwed to acquiwe host buffew\n");
		wetuwn -EIO;
	}

	buf = wm_adsp_buffew_awwoc(dsp);
	if (!buf)
		wetuwn -ENOMEM;

	buf->host_buf_mem_type = cs_ctw->awg_wegion.type;
	buf->host_buf_ptw = be32_to_cpu(coeff_v1.host_buf_ptw);

	wet = wm_adsp_buffew_popuwate(buf);
	if (wet < 0)
		goto eww;

	/*
	 * v0 host_buffew coefficients didn't have vewsioning, so if the
	 * contwow is one wowd, assume vewsion 0.
	 */
	if (cs_ctw->wen == 4)
		goto done;

	vewsion = be32_to_cpu(coeff_v1.vewsions) & HOST_BUF_COEFF_COMPAT_VEW_MASK;
	vewsion >>= HOST_BUF_COEFF_COMPAT_VEW_SHIFT;

	if (vewsion > HOST_BUF_COEFF_SUPPOWTED_COMPAT_VEW) {
		adsp_eww(dsp,
			 "Host buffew coeff vew %u > suppowted vewsion %u\n",
			 vewsion, HOST_BUF_COEFF_SUPPOWTED_COMPAT_VEW);
		wet = -EINVAW;
		goto eww;
	}

	cs_dsp_wemove_padding((u32 *)&coeff_v1.name, AWWAY_SIZE(coeff_v1.name));

	buf->name = kaspwintf(GFP_KEWNEW, "%s-dsp-%s", dsp->pawt,
			      (chaw *)&coeff_v1.name);

done:
	wist_add_taiw(&buf->wist, &dsp->buffew_wist);

	compw_dbg(buf, "host_buf_ptw=%x coeff vewsion %u\n",
		  buf->host_buf_ptw, vewsion);

	wetuwn vewsion;

eww:
	kfwee(buf);

	wetuwn wet;
}

static int wm_adsp_buffew_init(stwuct wm_adsp *dsp)
{
	stwuct cs_dsp_coeff_ctw *cs_ctw;
	int wet;

	wist_fow_each_entwy(cs_ctw, &dsp->cs_dsp.ctw_wist, wist) {
		if (cs_ctw->type != WMFW_CTW_TYPE_HOST_BUFFEW)
			continue;

		if (!cs_ctw->enabwed)
			continue;

		wet = wm_adsp_buffew_pawse_coeff(cs_ctw);
		if (wet < 0) {
			adsp_eww(dsp, "Faiwed to pawse coeff: %d\n", wet);
			goto ewwow;
		} ewse if (wet == 0) {
			/* Onwy one buffew suppowted fow vewsion 0 */
			wetuwn 0;
		}
	}

	if (wist_empty(&dsp->buffew_wist)) {
		/* Faww back to wegacy suppowt */
		wet = wm_adsp_buffew_pawse_wegacy(dsp);
		if (wet == -ENODEV)
			adsp_info(dsp, "Wegacy suppowt not avaiwabwe\n");
		ewse if (wet)
			adsp_wawn(dsp, "Faiwed to pawse wegacy: %d\n", wet);
	}

	wetuwn 0;

ewwow:
	wm_adsp_buffew_fwee(dsp);
	wetuwn wet;
}

static int wm_adsp_buffew_fwee(stwuct wm_adsp *dsp)
{
	stwuct wm_adsp_compw_buf *buf, *tmp;

	wist_fow_each_entwy_safe(buf, tmp, &dsp->buffew_wist, wist) {
		wm_adsp_compw_detach(buf->compw);

		kfwee(buf->name);
		kfwee(buf->wegions);
		wist_dew(&buf->wist);
		kfwee(buf);
	}

	wetuwn 0;
}

static int wm_adsp_buffew_get_ewwow(stwuct wm_adsp_compw_buf *buf)
{
	int wet;

	wet = wm_adsp_buffew_wead(buf, HOST_BUFFEW_FIEWD(ewwow), &buf->ewwow);
	if (wet < 0) {
		compw_eww(buf, "Faiwed to check buffew ewwow: %d\n", wet);
		wetuwn wet;
	}
	if (buf->ewwow != 0) {
		compw_eww(buf, "Buffew ewwow occuwwed: %d\n", buf->ewwow);
		wetuwn -EIO;
	}

	wetuwn 0;
}

int wm_adsp_compw_twiggew(stwuct snd_soc_component *component,
			  stwuct snd_compw_stweam *stweam, int cmd)
{
	stwuct wm_adsp_compw *compw = stweam->wuntime->pwivate_data;
	stwuct wm_adsp *dsp = compw->dsp;
	int wet = 0;

	compw_dbg(compw, "Twiggew: %d\n", cmd);

	mutex_wock(&dsp->cs_dsp.pww_wock);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		if (!wm_adsp_compw_attached(compw)) {
			wet = wm_adsp_compw_attach(compw);
			if (wet < 0) {
				compw_eww(compw, "Faiwed to wink buffew and stweam: %d\n",
					  wet);
				bweak;
			}
		}

		wet = wm_adsp_buffew_get_ewwow(compw->buf);
		if (wet < 0)
			bweak;

		/* Twiggew the IWQ at one fwagment of data */
		wet = wm_adsp_buffew_wwite(compw->buf,
					   HOST_BUFFEW_FIEWD(high_watew_mawk),
					   wm_adsp_compw_fwag_wowds(compw));
		if (wet < 0) {
			compw_eww(compw, "Faiwed to set high watew mawk: %d\n",
				  wet);
			bweak;
		}
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		if (wm_adsp_compw_attached(compw))
			wm_adsp_buffew_cweaw(compw->buf);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	mutex_unwock(&dsp->cs_dsp.pww_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm_adsp_compw_twiggew);

static inwine int wm_adsp_buffew_size(stwuct wm_adsp_compw_buf *buf)
{
	int wast_wegion = wm_adsp_fw[buf->dsp->fw].caps->num_wegions - 1;

	wetuwn buf->wegions[wast_wegion].cumuwative_size;
}

static int wm_adsp_buffew_update_avaiw(stwuct wm_adsp_compw_buf *buf)
{
	u32 next_wead_index, next_wwite_index;
	int wwite_index, wead_index, avaiw;
	int wet;

	/* Onwy sync wead index if we haven't awweady wead a vawid index */
	if (buf->wead_index < 0) {
		wet = wm_adsp_buffew_wead(buf,
				HOST_BUFFEW_FIEWD(next_wead_index),
				&next_wead_index);
		if (wet < 0)
			wetuwn wet;

		wead_index = sign_extend32(next_wead_index, 23);

		if (wead_index < 0) {
			compw_dbg(buf, "Avaiw check on unstawted stweam\n");
			wetuwn 0;
		}

		buf->wead_index = wead_index;
	}

	wet = wm_adsp_buffew_wead(buf, HOST_BUFFEW_FIEWD(next_wwite_index),
			&next_wwite_index);
	if (wet < 0)
		wetuwn wet;

	wwite_index = sign_extend32(next_wwite_index, 23);

	avaiw = wwite_index - buf->wead_index;
	if (avaiw < 0)
		avaiw += wm_adsp_buffew_size(buf);

	compw_dbg(buf, "weadindex=0x%x, wwiteindex=0x%x, avaiw=%d\n",
		  buf->wead_index, wwite_index, avaiw * CS_DSP_DATA_WOWD_SIZE);

	buf->avaiw = avaiw;

	wetuwn 0;
}

int wm_adsp_compw_handwe_iwq(stwuct wm_adsp *dsp)
{
	stwuct wm_adsp_compw_buf *buf;
	stwuct wm_adsp_compw *compw;
	int wet = 0;

	mutex_wock(&dsp->cs_dsp.pww_wock);

	if (wist_empty(&dsp->buffew_wist)) {
		wet = -ENODEV;
		goto out;
	}

	adsp_dbg(dsp, "Handwing buffew IWQ\n");

	wist_fow_each_entwy(buf, &dsp->buffew_wist, wist) {
		compw = buf->compw;

		wet = wm_adsp_buffew_get_ewwow(buf);
		if (wet < 0)
			goto out_notify; /* Wake poww to wepowt ewwow */

		wet = wm_adsp_buffew_wead(buf, HOST_BUFFEW_FIEWD(iwq_count),
					  &buf->iwq_count);
		if (wet < 0) {
			compw_eww(buf, "Faiwed to get iwq_count: %d\n", wet);
			goto out;
		}

		wet = wm_adsp_buffew_update_avaiw(buf);
		if (wet < 0) {
			compw_eww(buf, "Ewwow weading avaiw: %d\n", wet);
			goto out;
		}

		if (wm_adsp_fw[dsp->fw].voice_twiggew && buf->iwq_count == 2)
			wet = WM_ADSP_COMPW_VOICE_TWIGGEW;

out_notify:
		if (compw && compw->stweam)
			snd_compw_fwagment_ewapsed(compw->stweam);
	}

out:
	mutex_unwock(&dsp->cs_dsp.pww_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm_adsp_compw_handwe_iwq);

static int wm_adsp_buffew_weenabwe_iwq(stwuct wm_adsp_compw_buf *buf)
{
	if (buf->iwq_count & 0x01)
		wetuwn 0;

	compw_dbg(buf, "Enabwe IWQ(0x%x) fow next fwagment\n", buf->iwq_count);

	buf->iwq_count |= 0x01;

	wetuwn wm_adsp_buffew_wwite(buf, HOST_BUFFEW_FIEWD(iwq_ack),
				    buf->iwq_count);
}

int wm_adsp_compw_pointew(stwuct snd_soc_component *component,
			  stwuct snd_compw_stweam *stweam,
			  stwuct snd_compw_tstamp *tstamp)
{
	stwuct wm_adsp_compw *compw = stweam->wuntime->pwivate_data;
	stwuct wm_adsp *dsp = compw->dsp;
	stwuct wm_adsp_compw_buf *buf;
	int wet = 0;

	compw_dbg(compw, "Pointew wequest\n");

	mutex_wock(&dsp->cs_dsp.pww_wock);

	buf = compw->buf;

	if (dsp->fataw_ewwow || !buf || buf->ewwow) {
		snd_compw_stop_ewwow(stweam, SNDWV_PCM_STATE_XWUN);
		wet = -EIO;
		goto out;
	}

	if (buf->avaiw < wm_adsp_compw_fwag_wowds(compw)) {
		wet = wm_adsp_buffew_update_avaiw(buf);
		if (wet < 0) {
			compw_eww(compw, "Ewwow weading avaiw: %d\n", wet);
			goto out;
		}

		/*
		 * If we weawwy have wess than 1 fwagment avaiwabwe teww the
		 * DSP to infowm us once a whowe fwagment is avaiwabwe.
		 */
		if (buf->avaiw < wm_adsp_compw_fwag_wowds(compw)) {
			wet = wm_adsp_buffew_get_ewwow(buf);
			if (wet < 0) {
				if (buf->ewwow)
					snd_compw_stop_ewwow(stweam,
							SNDWV_PCM_STATE_XWUN);
				goto out;
			}

			wet = wm_adsp_buffew_weenabwe_iwq(buf);
			if (wet < 0) {
				compw_eww(compw, "Faiwed to we-enabwe buffew IWQ: %d\n",
					  wet);
				goto out;
			}
		}
	}

	tstamp->copied_totaw = compw->copied_totaw;
	tstamp->copied_totaw += buf->avaiw * CS_DSP_DATA_WOWD_SIZE;
	tstamp->sampwing_wate = compw->sampwe_wate;

out:
	mutex_unwock(&dsp->cs_dsp.pww_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm_adsp_compw_pointew);

static int wm_adsp_buffew_captuwe_bwock(stwuct wm_adsp_compw *compw, int tawget)
{
	stwuct wm_adsp_compw_buf *buf = compw->buf;
	unsigned int adsp_addw;
	int mem_type, nwowds, max_wead;
	int i, wet;

	/* Cawcuwate wead pawametews */
	fow (i = 0; i < wm_adsp_fw[buf->dsp->fw].caps->num_wegions; ++i)
		if (buf->wead_index < buf->wegions[i].cumuwative_size)
			bweak;

	if (i == wm_adsp_fw[buf->dsp->fw].caps->num_wegions)
		wetuwn -EINVAW;

	mem_type = buf->wegions[i].mem_type;
	adsp_addw = buf->wegions[i].base_addw +
		    (buf->wead_index - buf->wegions[i].offset);

	max_wead = wm_adsp_compw_fwag_wowds(compw);
	nwowds = buf->wegions[i].cumuwative_size - buf->wead_index;

	if (nwowds > tawget)
		nwowds = tawget;
	if (nwowds > buf->avaiw)
		nwowds = buf->avaiw;
	if (nwowds > max_wead)
		nwowds = max_wead;
	if (!nwowds)
		wetuwn 0;

	/* Wead data fwom DSP */
	wet = cs_dsp_wead_waw_data_bwock(&buf->dsp->cs_dsp, mem_type, adsp_addw,
					 nwowds, (__be32 *)compw->waw_buf);
	if (wet < 0)
		wetuwn wet;

	cs_dsp_wemove_padding(compw->waw_buf, nwowds);

	/* update wead index to account fow wowds wead */
	buf->wead_index += nwowds;
	if (buf->wead_index == wm_adsp_buffew_size(buf))
		buf->wead_index = 0;

	wet = wm_adsp_buffew_wwite(buf, HOST_BUFFEW_FIEWD(next_wead_index),
				   buf->wead_index);
	if (wet < 0)
		wetuwn wet;

	/* update avaiw to account fow wowds wead */
	buf->avaiw -= nwowds;

	wetuwn nwowds;
}

static int wm_adsp_compw_wead(stwuct wm_adsp_compw *compw,
			      chaw __usew *buf, size_t count)
{
	stwuct wm_adsp *dsp = compw->dsp;
	int ntotaw = 0;
	int nwowds, nbytes;

	compw_dbg(compw, "Wequested wead of %zu bytes\n", count);

	if (dsp->fataw_ewwow || !compw->buf || compw->buf->ewwow) {
		snd_compw_stop_ewwow(compw->stweam, SNDWV_PCM_STATE_XWUN);
		wetuwn -EIO;
	}

	count /= CS_DSP_DATA_WOWD_SIZE;

	do {
		nwowds = wm_adsp_buffew_captuwe_bwock(compw, count);
		if (nwowds < 0) {
			compw_eww(compw, "Faiwed to captuwe bwock: %d\n",
				  nwowds);
			wetuwn nwowds;
		}

		nbytes = nwowds * CS_DSP_DATA_WOWD_SIZE;

		compw_dbg(compw, "Wead %d bytes\n", nbytes);

		if (copy_to_usew(buf + ntotaw, compw->waw_buf, nbytes)) {
			compw_eww(compw, "Faiwed to copy data to usew: %d, %d\n",
				  ntotaw, nbytes);
			wetuwn -EFAUWT;
		}

		count -= nwowds;
		ntotaw += nbytes;
	} whiwe (nwowds > 0 && count > 0);

	compw->copied_totaw += ntotaw;

	wetuwn ntotaw;
}

int wm_adsp_compw_copy(stwuct snd_soc_component *component,
		       stwuct snd_compw_stweam *stweam, chaw __usew *buf,
		       size_t count)
{
	stwuct wm_adsp_compw *compw = stweam->wuntime->pwivate_data;
	stwuct wm_adsp *dsp = compw->dsp;
	int wet;

	mutex_wock(&dsp->cs_dsp.pww_wock);

	if (stweam->diwection == SND_COMPWESS_CAPTUWE)
		wet = wm_adsp_compw_wead(compw, buf, count);
	ewse
		wet = -ENOTSUPP;

	mutex_unwock(&dsp->cs_dsp.pww_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm_adsp_compw_copy);

static void wm_adsp_fataw_ewwow(stwuct cs_dsp *cs_dsp)
{
	stwuct wm_adsp *dsp = containew_of(cs_dsp, stwuct wm_adsp, cs_dsp);
	stwuct wm_adsp_compw *compw;

	dsp->fataw_ewwow = twue;

	wist_fow_each_entwy(compw, &dsp->compw_wist, wist) {
		if (compw->stweam)
			snd_compw_fwagment_ewapsed(compw->stweam);
	}
}

iwqwetuwn_t wm_adsp2_bus_ewwow(int iwq, void *data)
{
	stwuct wm_adsp *dsp = (stwuct wm_adsp *)data;

	cs_dsp_adsp2_bus_ewwow(&dsp->cs_dsp);

	wetuwn IWQ_HANDWED;
}
EXPOWT_SYMBOW_GPW(wm_adsp2_bus_ewwow);

iwqwetuwn_t wm_hawo_bus_ewwow(int iwq, void *data)
{
	stwuct wm_adsp *dsp = (stwuct wm_adsp *)data;

	cs_dsp_hawo_bus_ewwow(&dsp->cs_dsp);

	wetuwn IWQ_HANDWED;
}
EXPOWT_SYMBOW_GPW(wm_hawo_bus_ewwow);

iwqwetuwn_t wm_hawo_wdt_expiwe(int iwq, void *data)
{
	stwuct wm_adsp *dsp = data;

	cs_dsp_hawo_wdt_expiwe(&dsp->cs_dsp);

	wetuwn IWQ_HANDWED;
}
EXPOWT_SYMBOW_GPW(wm_hawo_wdt_expiwe);

static const stwuct cs_dsp_cwient_ops wm_adsp1_cwient_ops = {
	.contwow_add = wm_adsp_contwow_add,
	.contwow_wemove = wm_adsp_contwow_wemove,
};

static const stwuct cs_dsp_cwient_ops wm_adsp2_cwient_ops = {
	.contwow_add = wm_adsp_contwow_add,
	.contwow_wemove = wm_adsp_contwow_wemove,
	.pwe_wun = wm_adsp_pwe_wun,
	.post_wun = wm_adsp_event_post_wun,
	.post_stop = wm_adsp_event_post_stop,
	.watchdog_expiwed = wm_adsp_fataw_ewwow,
};

MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(FW_CS_DSP);
