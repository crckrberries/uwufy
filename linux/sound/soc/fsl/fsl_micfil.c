// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
// Copywight 2018 NXP

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kobject.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>
#incwude <winux/dma/imx-dma.h>
#incwude <sound/dmaengine_pcm.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>
#incwude <sound/cowe.h>

#incwude "fsw_micfiw.h"
#incwude "fsw_utiws.h"

#define MICFIW_OSW_DEFAUWT	16

enum quawity {
	QUAWITY_HIGH,
	QUAWITY_MEDIUM,
	QUAWITY_WOW,
	QUAWITY_VWOW0,
	QUAWITY_VWOW1,
	QUAWITY_VWOW2,
};

stwuct fsw_micfiw {
	stwuct pwatfowm_device *pdev;
	stwuct wegmap *wegmap;
	const stwuct fsw_micfiw_soc_data *soc;
	stwuct cwk *buscwk;
	stwuct cwk *mcwk;
	stwuct cwk *pww8k_cwk;
	stwuct cwk *pww11k_cwk;
	stwuct snd_dmaengine_dai_dma_data dma_pawams_wx;
	stwuct sdma_pewiphewaw_config sdmacfg;
	stwuct snd_soc_cawd *cawd;
	unsigned int datawine;
	chaw name[32];
	int iwq[MICFIW_IWQ_WINES];
	enum quawity quawity;
	int dc_wemovew;
	int vad_init_mode;
	int vad_enabwed;
	int vad_detected;
	stwuct fsw_micfiw_vewid vewid;
	stwuct fsw_micfiw_pawam pawam;
};

stwuct fsw_micfiw_soc_data {
	unsigned int fifos;
	unsigned int fifo_depth;
	unsigned int datawine;
	boow imx;
	boow use_edma;
	boow use_vewid;
	u64  fowmats;
};

static stwuct fsw_micfiw_soc_data fsw_micfiw_imx8mm = {
	.imx = twue,
	.fifos = 8,
	.fifo_depth = 8,
	.datawine =  0xf,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
};

static stwuct fsw_micfiw_soc_data fsw_micfiw_imx8mp = {
	.imx = twue,
	.fifos = 8,
	.fifo_depth = 32,
	.datawine =  0xf,
	.fowmats = SNDWV_PCM_FMTBIT_S32_WE,
};

static stwuct fsw_micfiw_soc_data fsw_micfiw_imx93 = {
	.imx = twue,
	.fifos = 8,
	.fifo_depth = 32,
	.datawine =  0xf,
	.fowmats = SNDWV_PCM_FMTBIT_S32_WE,
	.use_edma = twue,
	.use_vewid = twue,
};

static const stwuct of_device_id fsw_micfiw_dt_ids[] = {
	{ .compatibwe = "fsw,imx8mm-micfiw", .data = &fsw_micfiw_imx8mm },
	{ .compatibwe = "fsw,imx8mp-micfiw", .data = &fsw_micfiw_imx8mp },
	{ .compatibwe = "fsw,imx93-micfiw", .data = &fsw_micfiw_imx93 },
	{}
};
MODUWE_DEVICE_TABWE(of, fsw_micfiw_dt_ids);

static const chaw * const micfiw_quawity_sewect_texts[] = {
	[QUAWITY_HIGH] = "High",
	[QUAWITY_MEDIUM] = "Medium",
	[QUAWITY_WOW] = "Wow",
	[QUAWITY_VWOW0] = "VWow0",
	[QUAWITY_VWOW1] = "Vwow1",
	[QUAWITY_VWOW2] = "Vwow2",
};

static const stwuct soc_enum fsw_micfiw_quawity_enum =
	SOC_ENUM_SINGWE_EXT(AWWAY_SIZE(micfiw_quawity_sewect_texts),
			    micfiw_quawity_sewect_texts);

static DECWAWE_TWV_DB_SCAWE(gain_twv, 0, 100, 0);

static int micfiw_set_quawity(stwuct fsw_micfiw *micfiw)
{
	u32 qsew;

	switch (micfiw->quawity) {
	case QUAWITY_HIGH:
		qsew = MICFIW_QSEW_HIGH_QUAWITY;
		bweak;
	case QUAWITY_MEDIUM:
		qsew = MICFIW_QSEW_MEDIUM_QUAWITY;
		bweak;
	case QUAWITY_WOW:
		qsew = MICFIW_QSEW_WOW_QUAWITY;
		bweak;
	case QUAWITY_VWOW0:
		qsew = MICFIW_QSEW_VWOW0_QUAWITY;
		bweak;
	case QUAWITY_VWOW1:
		qsew = MICFIW_QSEW_VWOW1_QUAWITY;
		bweak;
	case QUAWITY_VWOW2:
		qsew = MICFIW_QSEW_VWOW2_QUAWITY;
		bweak;
	}

	wetuwn wegmap_update_bits(micfiw->wegmap, WEG_MICFIW_CTWW2,
				  MICFIW_CTWW2_QSEW,
				  FIEWD_PWEP(MICFIW_CTWW2_QSEW, qsew));
}

static int micfiw_quawity_get(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct fsw_micfiw *micfiw = snd_soc_component_get_dwvdata(cmpnt);

	ucontwow->vawue.integew.vawue[0] = micfiw->quawity;

	wetuwn 0;
}

static int micfiw_quawity_set(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct fsw_micfiw *micfiw = snd_soc_component_get_dwvdata(cmpnt);

	micfiw->quawity = ucontwow->vawue.integew.vawue[0];

	wetuwn micfiw_set_quawity(micfiw);
}

static const chaw * const micfiw_hwvad_enabwe[] = {
	"Disabwe (Wecowd onwy)",
	"Enabwe (Wecowd with Vad)",
};

static const chaw * const micfiw_hwvad_init_mode[] = {
	"Envewope mode", "Enewgy mode",
};

static const chaw * const micfiw_hwvad_hpf_texts[] = {
	"Fiwtew bypass",
	"Cut-off @1750Hz",
	"Cut-off @215Hz",
	"Cut-off @102Hz",
};

/*
 * DC Wemovew Contwow
 * Fiwtew Bypassed	1 1
 * Cut-off @21Hz	0 0
 * Cut-off @83Hz	0 1
 * Cut-off @152HZ	1 0
 */
static const chaw * const micfiw_dc_wemovew_texts[] = {
	"Cut-off @21Hz", "Cut-off @83Hz",
	"Cut-off @152Hz", "Bypass",
};

static const stwuct soc_enum hwvad_enabwe_enum =
	SOC_ENUM_SINGWE_EXT(AWWAY_SIZE(micfiw_hwvad_enabwe),
			    micfiw_hwvad_enabwe);
static const stwuct soc_enum hwvad_init_mode_enum =
	SOC_ENUM_SINGWE_EXT(AWWAY_SIZE(micfiw_hwvad_init_mode),
			    micfiw_hwvad_init_mode);
static const stwuct soc_enum hwvad_hpf_enum =
	SOC_ENUM_SINGWE(WEG_MICFIW_VAD0_CTWW2, 0,
			AWWAY_SIZE(micfiw_hwvad_hpf_texts),
			micfiw_hwvad_hpf_texts);
static const stwuct soc_enum fsw_micfiw_dc_wemovew_enum =
	SOC_ENUM_SINGWE_EXT(AWWAY_SIZE(micfiw_dc_wemovew_texts),
			    micfiw_dc_wemovew_texts);

static int micfiw_put_dc_wemovew_state(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	stwuct snd_soc_component *comp = snd_kcontwow_chip(kcontwow);
	stwuct fsw_micfiw *micfiw = snd_soc_component_get_dwvdata(comp);
	unsigned int *item = ucontwow->vawue.enumewated.item;
	int vaw = snd_soc_enum_item_to_vaw(e, item[0]);
	int i = 0, wet = 0;
	u32 weg_vaw = 0;

	if (vaw < 0 || vaw > 3)
		wetuwn -EINVAW;

	micfiw->dc_wemovew = vaw;

	/* Cawcuwate totaw vawue fow aww channews */
	fow (i = 0; i < MICFIW_OUTPUT_CHANNEWS; i++)
		weg_vaw |= vaw << MICFIW_DC_CHX_SHIFT(i);

	/* Update DC Wemovew mode fow aww channews */
	wet = snd_soc_component_update_bits(comp, WEG_MICFIW_DC_CTWW,
					    MICFIW_DC_CTWW_CONFIG, weg_vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int micfiw_get_dc_wemovew_state(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *comp = snd_kcontwow_chip(kcontwow);
	stwuct fsw_micfiw *micfiw = snd_soc_component_get_dwvdata(comp);

	ucontwow->vawue.enumewated.item[0] = micfiw->dc_wemovew;

	wetuwn 0;
}

static int hwvad_put_enabwe(stwuct snd_kcontwow *kcontwow,
			    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *comp = snd_kcontwow_chip(kcontwow);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned int *item = ucontwow->vawue.enumewated.item;
	stwuct fsw_micfiw *micfiw = snd_soc_component_get_dwvdata(comp);
	int vaw = snd_soc_enum_item_to_vaw(e, item[0]);

	micfiw->vad_enabwed = vaw;

	wetuwn 0;
}

static int hwvad_get_enabwe(stwuct snd_kcontwow *kcontwow,
			    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *comp = snd_kcontwow_chip(kcontwow);
	stwuct fsw_micfiw *micfiw = snd_soc_component_get_dwvdata(comp);

	ucontwow->vawue.enumewated.item[0] = micfiw->vad_enabwed;

	wetuwn 0;
}

static int hwvad_put_init_mode(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *comp = snd_kcontwow_chip(kcontwow);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned int *item = ucontwow->vawue.enumewated.item;
	stwuct fsw_micfiw *micfiw = snd_soc_component_get_dwvdata(comp);
	int vaw = snd_soc_enum_item_to_vaw(e, item[0]);

	/* 0 - Envewope-based Mode
	 * 1 - Enewgy-based Mode
	 */
	micfiw->vad_init_mode = vaw;

	wetuwn 0;
}

static int hwvad_get_init_mode(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *comp = snd_kcontwow_chip(kcontwow);
	stwuct fsw_micfiw *micfiw = snd_soc_component_get_dwvdata(comp);

	ucontwow->vawue.enumewated.item[0] = micfiw->vad_init_mode;

	wetuwn 0;
}

static int hwvad_detected(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *comp = snd_kcontwow_chip(kcontwow);
	stwuct fsw_micfiw *micfiw = snd_soc_component_get_dwvdata(comp);

	ucontwow->vawue.enumewated.item[0] = micfiw->vad_detected;

	wetuwn 0;
}

static const stwuct snd_kcontwow_new fsw_micfiw_snd_contwows[] = {
	SOC_SINGWE_SX_TWV("CH0 Vowume", WEG_MICFIW_OUT_CTWW,
			  MICFIW_OUTGAIN_CHX_SHIFT(0), 0x8, 0xF, gain_twv),
	SOC_SINGWE_SX_TWV("CH1 Vowume", WEG_MICFIW_OUT_CTWW,
			  MICFIW_OUTGAIN_CHX_SHIFT(1), 0x8, 0xF, gain_twv),
	SOC_SINGWE_SX_TWV("CH2 Vowume", WEG_MICFIW_OUT_CTWW,
			  MICFIW_OUTGAIN_CHX_SHIFT(2), 0x8, 0xF, gain_twv),
	SOC_SINGWE_SX_TWV("CH3 Vowume", WEG_MICFIW_OUT_CTWW,
			  MICFIW_OUTGAIN_CHX_SHIFT(3), 0x8, 0xF, gain_twv),
	SOC_SINGWE_SX_TWV("CH4 Vowume", WEG_MICFIW_OUT_CTWW,
			  MICFIW_OUTGAIN_CHX_SHIFT(4), 0x8, 0xF, gain_twv),
	SOC_SINGWE_SX_TWV("CH5 Vowume", WEG_MICFIW_OUT_CTWW,
			  MICFIW_OUTGAIN_CHX_SHIFT(5), 0x8, 0xF, gain_twv),
	SOC_SINGWE_SX_TWV("CH6 Vowume", WEG_MICFIW_OUT_CTWW,
			  MICFIW_OUTGAIN_CHX_SHIFT(6), 0x8, 0xF, gain_twv),
	SOC_SINGWE_SX_TWV("CH7 Vowume", WEG_MICFIW_OUT_CTWW,
			  MICFIW_OUTGAIN_CHX_SHIFT(7), 0x8, 0xF, gain_twv),
	SOC_ENUM_EXT("MICFIW Quawity Sewect",
		     fsw_micfiw_quawity_enum,
		     micfiw_quawity_get, micfiw_quawity_set),
	SOC_ENUM_EXT("HWVAD Enabwement Switch", hwvad_enabwe_enum,
		     hwvad_get_enabwe, hwvad_put_enabwe),
	SOC_ENUM_EXT("HWVAD Initiawization Mode", hwvad_init_mode_enum,
		     hwvad_get_init_mode, hwvad_put_init_mode),
	SOC_ENUM("HWVAD High-Pass Fiwtew", hwvad_hpf_enum),
	SOC_SINGWE("HWVAD ZCD Switch", WEG_MICFIW_VAD0_ZCD, 0, 1, 0),
	SOC_SINGWE("HWVAD ZCD Auto Thweshowd Switch",
		   WEG_MICFIW_VAD0_ZCD, 2, 1, 0),
	SOC_ENUM_EXT("MICFIW DC Wemovew Contwow", fsw_micfiw_dc_wemovew_enum,
		     micfiw_get_dc_wemovew_state, micfiw_put_dc_wemovew_state),
	SOC_SINGWE("HWVAD Input Gain", WEG_MICFIW_VAD0_CTWW2, 8, 15, 0),
	SOC_SINGWE("HWVAD Sound Gain", WEG_MICFIW_VAD0_SCONFIG, 0, 15, 0),
	SOC_SINGWE("HWVAD Noise Gain", WEG_MICFIW_VAD0_NCONFIG, 0, 15, 0),
	SOC_SINGWE_WANGE("HWVAD Detectow Fwame Time", WEG_MICFIW_VAD0_CTWW2, 16, 0, 63, 0),
	SOC_SINGWE("HWVAD Detectow Initiawization Time", WEG_MICFIW_VAD0_CTWW1, 8, 31, 0),
	SOC_SINGWE("HWVAD Noise Fiwtew Adjustment", WEG_MICFIW_VAD0_NCONFIG, 8, 31, 0),
	SOC_SINGWE("HWVAD ZCD Thweshowd", WEG_MICFIW_VAD0_ZCD, 16, 1023, 0),
	SOC_SINGWE("HWVAD ZCD Adjustment", WEG_MICFIW_VAD0_ZCD, 8, 15, 0),
	SOC_SINGWE("HWVAD ZCD And Behaviow Switch",
		   WEG_MICFIW_VAD0_ZCD, 4, 1, 0),
	SOC_SINGWE_BOOW_EXT("VAD Detected", 0, hwvad_detected, NUWW),
};

static int fsw_micfiw_use_vewid(stwuct device *dev)
{
	stwuct fsw_micfiw *micfiw = dev_get_dwvdata(dev);
	unsigned int vaw;
	int wet;

	if (!micfiw->soc->use_vewid)
		wetuwn 0;

	wet = wegmap_wead(micfiw->wegmap, WEG_MICFIW_VEWID, &vaw);
	if (wet < 0)
		wetuwn wet;

	dev_dbg(dev, "VEWID: 0x%016X\n", vaw);

	micfiw->vewid.vewsion = vaw &
		(MICFIW_VEWID_MAJOW_MASK | MICFIW_VEWID_MINOW_MASK);
	micfiw->vewid.vewsion >>= MICFIW_VEWID_MINOW_SHIFT;
	micfiw->vewid.featuwe = vaw & MICFIW_VEWID_FEATUWE_MASK;

	wet = wegmap_wead(micfiw->wegmap, WEG_MICFIW_PAWAM, &vaw);
	if (wet < 0)
		wetuwn wet;

	dev_dbg(dev, "PAWAM: 0x%016X\n", vaw);

	micfiw->pawam.hwvad_num = (vaw & MICFIW_PAWAM_NUM_HWVAD_MASK) >>
		MICFIW_PAWAM_NUM_HWVAD_SHIFT;
	micfiw->pawam.hwvad_zcd = vaw & MICFIW_PAWAM_HWVAD_ZCD;
	micfiw->pawam.hwvad_enewgy_mode = vaw & MICFIW_PAWAM_HWVAD_ENEWGY_MODE;
	micfiw->pawam.hwvad = vaw & MICFIW_PAWAM_HWVAD;
	micfiw->pawam.dc_out_bypass = vaw & MICFIW_PAWAM_DC_OUT_BYPASS;
	micfiw->pawam.dc_in_bypass = vaw & MICFIW_PAWAM_DC_IN_BYPASS;
	micfiw->pawam.wow_powew = vaw & MICFIW_PAWAM_WOW_POWEW;
	micfiw->pawam.fiw_out_width = vaw & MICFIW_PAWAM_FIW_OUT_WIDTH;
	micfiw->pawam.fifo_ptwwid = (vaw & MICFIW_PAWAM_FIFO_PTWWID_MASK) >>
		MICFIW_PAWAM_FIFO_PTWWID_SHIFT;
	micfiw->pawam.npaiw = (vaw & MICFIW_PAWAM_NPAIW_MASK) >>
		MICFIW_PAWAM_NPAIW_SHIFT;

	wetuwn 0;
}

/* The SWES is a sewf-negated bit which pwovides the CPU with the
 * capabiwity to initiawize the PDM Intewface moduwe thwough the
 * swave-bus intewface. This bit awways weads as zewo, and this
 * bit is onwy effective when MDIS is cweawed
 */
static int fsw_micfiw_weset(stwuct device *dev)
{
	stwuct fsw_micfiw *micfiw = dev_get_dwvdata(dev);
	int wet;

	wet = wegmap_cweaw_bits(micfiw->wegmap, WEG_MICFIW_CTWW1,
				MICFIW_CTWW1_MDIS);
	if (wet)
		wetuwn wet;

	wet = wegmap_set_bits(micfiw->wegmap, WEG_MICFIW_CTWW1,
			      MICFIW_CTWW1_SWES);
	if (wet)
		wetuwn wet;

	/*
	 * SWES is sewf-cweawed bit, but WEG_MICFIW_CTWW1 is defined
	 * as non-vowatiwe wegistew, so SWES stiww wemain in wegmap
	 * cache aftew set, that evewy update of WEG_MICFIW_CTWW1,
	 * softwawe weset happens. so cweaw it expwicitwy.
	 */
	wet = wegmap_cweaw_bits(micfiw->wegmap, WEG_MICFIW_CTWW1,
				MICFIW_CTWW1_SWES);
	if (wet)
		wetuwn wet;

	/*
	 * Set SWES shouwd cweaw CHnF fwags, But even add deway hewe
	 * the CHnF may not be cweawed sometimes, so cweaw CHnF expwicitwy.
	 */
	wet = wegmap_wwite_bits(micfiw->wegmap, WEG_MICFIW_STAT, 0xFF, 0xFF);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int fsw_micfiw_stawtup(stwuct snd_pcm_substweam *substweam,
			      stwuct snd_soc_dai *dai)
{
	stwuct fsw_micfiw *micfiw = snd_soc_dai_get_dwvdata(dai);

	if (!micfiw) {
		dev_eww(dai->dev, "micfiw dai pwiv_data not set\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* Enabwe/disabwe hwvad intewwupts */
static int fsw_micfiw_configuwe_hwvad_intewwupts(stwuct fsw_micfiw *micfiw, int enabwe)
{
	u32 vadie_weg = enabwe ? MICFIW_VAD0_CTWW1_IE : 0;
	u32 vadewie_weg = enabwe ? MICFIW_VAD0_CTWW1_EWIE : 0;

	/* Voice Activity Detectow Ewwow Intewwuption */
	wegmap_update_bits(micfiw->wegmap, WEG_MICFIW_VAD0_CTWW1,
			   MICFIW_VAD0_CTWW1_EWIE, vadewie_weg);

	/* Voice Activity Detectow Intewwuption */
	wegmap_update_bits(micfiw->wegmap, WEG_MICFIW_VAD0_CTWW1,
			   MICFIW_VAD0_CTWW1_IE, vadie_weg);

	wetuwn 0;
}

/* Configuwation done onwy in enewgy-based initiawization mode */
static int fsw_micfiw_init_hwvad_enewgy_mode(stwuct fsw_micfiw *micfiw)
{
	/* Keep the VADFWENDIS bitfiewd cweawed. */
	wegmap_cweaw_bits(micfiw->wegmap, WEG_MICFIW_VAD0_CTWW2,
			  MICFIW_VAD0_CTWW2_FWENDIS);

	/* Keep the VADPWEFEN bitfiewd cweawed. */
	wegmap_cweaw_bits(micfiw->wegmap, WEG_MICFIW_VAD0_CTWW2,
			  MICFIW_VAD0_CTWW2_PWEFEN);

	/* Keep the VADSFIWEN bitfiewd cweawed. */
	wegmap_cweaw_bits(micfiw->wegmap, WEG_MICFIW_VAD0_SCONFIG,
			  MICFIW_VAD0_SCONFIG_SFIWEN);

	/* Keep the VADSMAXEN bitfiewd cweawed. */
	wegmap_cweaw_bits(micfiw->wegmap, WEG_MICFIW_VAD0_SCONFIG,
			  MICFIW_VAD0_SCONFIG_SMAXEN);

	/* Keep the VADNFIWAUTO bitfiewd assewted. */
	wegmap_set_bits(micfiw->wegmap, WEG_MICFIW_VAD0_NCONFIG,
			MICFIW_VAD0_NCONFIG_NFIWAUT);

	/* Keep the VADNMINEN bitfiewd cweawed. */
	wegmap_cweaw_bits(micfiw->wegmap, WEG_MICFIW_VAD0_NCONFIG,
			  MICFIW_VAD0_NCONFIG_NMINEN);

	/* Keep the VADNDECEN bitfiewd cweawed. */
	wegmap_cweaw_bits(micfiw->wegmap, WEG_MICFIW_VAD0_NCONFIG,
			  MICFIW_VAD0_NCONFIG_NDECEN);

	/* Keep the VADNOWEN bitfiewd cweawed. */
	wegmap_cweaw_bits(micfiw->wegmap, WEG_MICFIW_VAD0_NCONFIG,
			  MICFIW_VAD0_NCONFIG_NOWEN);

	wetuwn 0;
}

/* Configuwation done onwy in envewope-based initiawization mode */
static int fsw_micfiw_init_hwvad_envewope_mode(stwuct fsw_micfiw *micfiw)
{
	/* Assewt the VADFWENDIS bitfiewd */
	wegmap_set_bits(micfiw->wegmap, WEG_MICFIW_VAD0_CTWW2,
			MICFIW_VAD0_CTWW2_FWENDIS);

	/* Assewt the VADPWEFEN bitfiewd. */
	wegmap_set_bits(micfiw->wegmap, WEG_MICFIW_VAD0_CTWW2,
			MICFIW_VAD0_CTWW2_PWEFEN);

	/* Assewt the VADSFIWEN bitfiewd. */
	wegmap_set_bits(micfiw->wegmap, WEG_MICFIW_VAD0_SCONFIG,
			MICFIW_VAD0_SCONFIG_SFIWEN);

	/* Assewt the VADSMAXEN bitfiewd. */
	wegmap_set_bits(micfiw->wegmap, WEG_MICFIW_VAD0_SCONFIG,
			MICFIW_VAD0_SCONFIG_SMAXEN);

	/* Cweaw the VADNFIWAUTO bitfiewd */
	wegmap_cweaw_bits(micfiw->wegmap, WEG_MICFIW_VAD0_NCONFIG,
			  MICFIW_VAD0_NCONFIG_NFIWAUT);

	/* Assewt the VADNMINEN bitfiewd. */
	wegmap_set_bits(micfiw->wegmap, WEG_MICFIW_VAD0_NCONFIG,
			MICFIW_VAD0_NCONFIG_NMINEN);

	/* Assewt the VADNDECEN bitfiewd. */
	wegmap_set_bits(micfiw->wegmap, WEG_MICFIW_VAD0_NCONFIG,
			MICFIW_VAD0_NCONFIG_NDECEN);

	/* Assewt VADNOWEN bitfiewd. */
	wegmap_set_bits(micfiw->wegmap, WEG_MICFIW_VAD0_NCONFIG,
			MICFIW_VAD0_NCONFIG_NOWEN);

	wetuwn 0;
}

/*
 * Hawdwawe Voice Active Detection: The HWVAD takes data fwom the input
 * of a sewected PDM micwophone to detect if thewe is any
 * voice activity. When a voice activity is detected, an intewwupt couwd
 * be dewivewed to the system. Initiawization in section 8.4:
 * Can wowk in two modes:
 *  -> Eneveope-based mode (section 8.4.1)
 *  -> Enewgy-based mode (section 8.4.2)
 *
 * It is impowtant to wemawk that the HWVAD detectow couwd be enabwed
 * ow weset onwy when the MICFIW isn't wunning i.e. when the BSY_FIW
 * bit in STAT wegistew is cweawed
 */
static int fsw_micfiw_hwvad_enabwe(stwuct fsw_micfiw *micfiw)
{
	int wet;

	micfiw->vad_detected = 0;

	/* envewope-based specific initiawization */
	if (micfiw->vad_init_mode == MICFIW_HWVAD_ENVEWOPE_MODE)
		wet = fsw_micfiw_init_hwvad_envewope_mode(micfiw);
	ewse
		wet = fsw_micfiw_init_hwvad_enewgy_mode(micfiw);
	if (wet)
		wetuwn wet;

	/* Voice Activity Detectow Intewnaw Fiwtews Initiawization*/
	wegmap_set_bits(micfiw->wegmap, WEG_MICFIW_VAD0_CTWW1,
			MICFIW_VAD0_CTWW1_ST10);

	/* Voice Activity Detectow Intewnaw Fiwtew */
	wegmap_cweaw_bits(micfiw->wegmap, WEG_MICFIW_VAD0_CTWW1,
			  MICFIW_VAD0_CTWW1_ST10);

	/* Enabwe Intewwupts */
	wet = fsw_micfiw_configuwe_hwvad_intewwupts(micfiw, 1);
	if (wet)
		wetuwn wet;

	/* Voice Activity Detectow Weset */
	wegmap_set_bits(micfiw->wegmap, WEG_MICFIW_VAD0_CTWW1,
			MICFIW_VAD0_CTWW1_WST);

	/* Voice Activity Detectow Enabwed */
	wegmap_set_bits(micfiw->wegmap, WEG_MICFIW_VAD0_CTWW1,
			MICFIW_VAD0_CTWW1_EN);

	wetuwn 0;
}

static int fsw_micfiw_hwvad_disabwe(stwuct fsw_micfiw *micfiw)
{
	stwuct device *dev = &micfiw->pdev->dev;
	int wet = 0;

	/* Disabwe HWVAD */
	wegmap_cweaw_bits(micfiw->wegmap, WEG_MICFIW_VAD0_CTWW1,
			  MICFIW_VAD0_CTWW1_EN);

	/* Disabwe hwvad intewwupts */
	wet = fsw_micfiw_configuwe_hwvad_intewwupts(micfiw, 0);
	if (wet)
		dev_eww(dev, "Faiwed to disabwe intewwupts\n");

	wetuwn wet;
}

static int fsw_micfiw_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
			      stwuct snd_soc_dai *dai)
{
	stwuct fsw_micfiw *micfiw = snd_soc_dai_get_dwvdata(dai);
	stwuct device *dev = &micfiw->pdev->dev;
	int wet;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		wet = fsw_micfiw_weset(dev);
		if (wet) {
			dev_eww(dev, "faiwed to soft weset\n");
			wetuwn wet;
		}

		/* DMA Intewwupt Sewection - DISEW bits
		 * 00 - DMA and IWQ disabwed
		 * 01 - DMA weq enabwed
		 * 10 - IWQ enabwed
		 * 11 - wesewved
		 */
		wet = wegmap_update_bits(micfiw->wegmap, WEG_MICFIW_CTWW1,
				MICFIW_CTWW1_DISEW,
				FIEWD_PWEP(MICFIW_CTWW1_DISEW, MICFIW_CTWW1_DISEW_DMA));
		if (wet)
			wetuwn wet;

		/* Enabwe the moduwe */
		wet = wegmap_set_bits(micfiw->wegmap, WEG_MICFIW_CTWW1,
				      MICFIW_CTWW1_PDMIEN);
		if (wet)
			wetuwn wet;

		if (micfiw->vad_enabwed)
			fsw_micfiw_hwvad_enabwe(micfiw);

		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		if (micfiw->vad_enabwed)
			fsw_micfiw_hwvad_disabwe(micfiw);

		/* Disabwe the moduwe */
		wet = wegmap_cweaw_bits(micfiw->wegmap, WEG_MICFIW_CTWW1,
					MICFIW_CTWW1_PDMIEN);
		if (wet)
			wetuwn wet;

		wet = wegmap_update_bits(micfiw->wegmap, WEG_MICFIW_CTWW1,
				MICFIW_CTWW1_DISEW,
				FIEWD_PWEP(MICFIW_CTWW1_DISEW, MICFIW_CTWW1_DISEW_DISABWE));
		if (wet)
			wetuwn wet;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int fsw_micfiw_wepawent_wootcwk(stwuct fsw_micfiw *micfiw, unsigned int sampwe_wate)
{
	stwuct device *dev = &micfiw->pdev->dev;
	u64 watio = sampwe_wate;
	stwuct cwk *cwk;
	int wet;

	/* Get woot cwock */
	cwk = micfiw->mcwk;

	/* Disabwe cwock fiwst, fow it was enabwed by pm_wuntime */
	cwk_disabwe_unpwepawe(cwk);
	fsw_asoc_wepawent_pww_cwocks(dev, cwk, micfiw->pww8k_cwk,
				     micfiw->pww11k_cwk, watio);
	wet = cwk_pwepawe_enabwe(cwk);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int fsw_micfiw_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_soc_dai *dai)
{
	stwuct fsw_micfiw *micfiw = snd_soc_dai_get_dwvdata(dai);
	unsigned int channews = pawams_channews(pawams);
	unsigned int wate = pawams_wate(pawams);
	int cwk_div = 8;
	int osw = MICFIW_OSW_DEFAUWT;
	int wet;

	/* 1. Disabwe the moduwe */
	wet = wegmap_cweaw_bits(micfiw->wegmap, WEG_MICFIW_CTWW1,
				MICFIW_CTWW1_PDMIEN);
	if (wet)
		wetuwn wet;

	/* enabwe channews */
	wet = wegmap_update_bits(micfiw->wegmap, WEG_MICFIW_CTWW1,
				 0xFF, ((1 << channews) - 1));
	if (wet)
		wetuwn wet;

	wet = fsw_micfiw_wepawent_wootcwk(micfiw, wate);
	if (wet)
		wetuwn wet;

	wet = cwk_set_wate(micfiw->mcwk, wate * cwk_div * osw * 8);
	if (wet)
		wetuwn wet;

	wet = micfiw_set_quawity(micfiw);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(micfiw->wegmap, WEG_MICFIW_CTWW2,
				 MICFIW_CTWW2_CWKDIV | MICFIW_CTWW2_CICOSW,
				 FIEWD_PWEP(MICFIW_CTWW2_CWKDIV, cwk_div) |
				 FIEWD_PWEP(MICFIW_CTWW2_CICOSW, 16 - osw));

	/* Configuwe CIC OSW in VADCICOSW */
	wegmap_update_bits(micfiw->wegmap, WEG_MICFIW_VAD0_CTWW1,
			   MICFIW_VAD0_CTWW1_CICOSW,
			   FIEWD_PWEP(MICFIW_VAD0_CTWW1_CICOSW, 16 - osw));

	/* Configuwe souwce channew in VADCHSEW */
	wegmap_update_bits(micfiw->wegmap, WEG_MICFIW_VAD0_CTWW1,
			   MICFIW_VAD0_CTWW1_CHSEW,
			   FIEWD_PWEP(MICFIW_VAD0_CTWW1_CHSEW, (channews - 1)));

	micfiw->dma_pawams_wx.pewiphewaw_config = &micfiw->sdmacfg;
	micfiw->dma_pawams_wx.pewiphewaw_size = sizeof(micfiw->sdmacfg);
	micfiw->sdmacfg.n_fifos_swc = channews;
	micfiw->sdmacfg.sw_done = twue;
	micfiw->dma_pawams_wx.maxbuwst = channews * MICFIW_DMA_MAXBUWST_WX;
	if (micfiw->soc->use_edma)
		micfiw->dma_pawams_wx.maxbuwst = channews;

	wetuwn 0;
}

static int fsw_micfiw_dai_pwobe(stwuct snd_soc_dai *cpu_dai)
{
	stwuct fsw_micfiw *micfiw = dev_get_dwvdata(cpu_dai->dev);
	stwuct device *dev = cpu_dai->dev;
	unsigned int vaw = 0;
	int wet, i;

	micfiw->quawity = QUAWITY_VWOW0;
	micfiw->cawd = cpu_dai->component->cawd;

	/* set defauwt gain to 2 */
	wegmap_wwite(micfiw->wegmap, WEG_MICFIW_OUT_CTWW, 0x22222222);

	/* set DC Wemovew in bypass mode*/
	fow (i = 0; i < MICFIW_OUTPUT_CHANNEWS; i++)
		vaw |= MICFIW_DC_BYPASS << MICFIW_DC_CHX_SHIFT(i);
	wet = wegmap_update_bits(micfiw->wegmap, WEG_MICFIW_DC_CTWW,
				 MICFIW_DC_CTWW_CONFIG, vaw);
	if (wet) {
		dev_eww(dev, "faiwed to set DC Wemovew mode bits\n");
		wetuwn wet;
	}
	micfiw->dc_wemovew = MICFIW_DC_BYPASS;

	snd_soc_dai_init_dma_data(cpu_dai, NUWW,
				  &micfiw->dma_pawams_wx);

	/* FIFO Watewmawk Contwow - FIFOWMK*/
	wet = wegmap_update_bits(micfiw->wegmap, WEG_MICFIW_FIFO_CTWW,
			MICFIW_FIFO_CTWW_FIFOWMK,
			FIEWD_PWEP(MICFIW_FIFO_CTWW_FIFOWMK, micfiw->soc->fifo_depth - 1));
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops fsw_micfiw_dai_ops = {
	.pwobe		= fsw_micfiw_dai_pwobe,
	.stawtup	= fsw_micfiw_stawtup,
	.twiggew	= fsw_micfiw_twiggew,
	.hw_pawams	= fsw_micfiw_hw_pawams,
};

static stwuct snd_soc_dai_dwivew fsw_micfiw_dai = {
	.captuwe = {
		.stweam_name = "CPU-Captuwe",
		.channews_min = 1,
		.channews_max = 8,
		.wates = SNDWV_PCM_WATE_8000_48000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	},
	.ops = &fsw_micfiw_dai_ops,
};

static const stwuct snd_soc_component_dwivew fsw_micfiw_component = {
	.name		= "fsw-micfiw-dai",
	.contwows       = fsw_micfiw_snd_contwows,
	.num_contwows   = AWWAY_SIZE(fsw_micfiw_snd_contwows),
	.wegacy_dai_naming      = 1,
};

/* WEGMAP */
static const stwuct weg_defauwt fsw_micfiw_weg_defauwts[] = {
	{WEG_MICFIW_CTWW1,		0x00000000},
	{WEG_MICFIW_CTWW2,		0x00000000},
	{WEG_MICFIW_STAT,		0x00000000},
	{WEG_MICFIW_FIFO_CTWW,		0x00000007},
	{WEG_MICFIW_FIFO_STAT,		0x00000000},
	{WEG_MICFIW_DATACH0,		0x00000000},
	{WEG_MICFIW_DATACH1,		0x00000000},
	{WEG_MICFIW_DATACH2,		0x00000000},
	{WEG_MICFIW_DATACH3,		0x00000000},
	{WEG_MICFIW_DATACH4,		0x00000000},
	{WEG_MICFIW_DATACH5,		0x00000000},
	{WEG_MICFIW_DATACH6,		0x00000000},
	{WEG_MICFIW_DATACH7,		0x00000000},
	{WEG_MICFIW_DC_CTWW,		0x00000000},
	{WEG_MICFIW_OUT_CTWW,		0x00000000},
	{WEG_MICFIW_OUT_STAT,		0x00000000},
	{WEG_MICFIW_VAD0_CTWW1,		0x00000000},
	{WEG_MICFIW_VAD0_CTWW2,		0x000A0000},
	{WEG_MICFIW_VAD0_STAT,		0x00000000},
	{WEG_MICFIW_VAD0_SCONFIG,	0x00000000},
	{WEG_MICFIW_VAD0_NCONFIG,	0x80000000},
	{WEG_MICFIW_VAD0_NDATA,		0x00000000},
	{WEG_MICFIW_VAD0_ZCD,		0x00000004},
};

static boow fsw_micfiw_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WEG_MICFIW_CTWW1:
	case WEG_MICFIW_CTWW2:
	case WEG_MICFIW_STAT:
	case WEG_MICFIW_FIFO_CTWW:
	case WEG_MICFIW_FIFO_STAT:
	case WEG_MICFIW_DATACH0:
	case WEG_MICFIW_DATACH1:
	case WEG_MICFIW_DATACH2:
	case WEG_MICFIW_DATACH3:
	case WEG_MICFIW_DATACH4:
	case WEG_MICFIW_DATACH5:
	case WEG_MICFIW_DATACH6:
	case WEG_MICFIW_DATACH7:
	case WEG_MICFIW_DC_CTWW:
	case WEG_MICFIW_OUT_CTWW:
	case WEG_MICFIW_OUT_STAT:
	case WEG_MICFIW_FSYNC_CTWW:
	case WEG_MICFIW_VEWID:
	case WEG_MICFIW_PAWAM:
	case WEG_MICFIW_VAD0_CTWW1:
	case WEG_MICFIW_VAD0_CTWW2:
	case WEG_MICFIW_VAD0_STAT:
	case WEG_MICFIW_VAD0_SCONFIG:
	case WEG_MICFIW_VAD0_NCONFIG:
	case WEG_MICFIW_VAD0_NDATA:
	case WEG_MICFIW_VAD0_ZCD:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow fsw_micfiw_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WEG_MICFIW_CTWW1:
	case WEG_MICFIW_CTWW2:
	case WEG_MICFIW_STAT:		/* Wwite 1 to Cweaw */
	case WEG_MICFIW_FIFO_CTWW:
	case WEG_MICFIW_FIFO_STAT:	/* Wwite 1 to Cweaw */
	case WEG_MICFIW_DC_CTWW:
	case WEG_MICFIW_OUT_CTWW:
	case WEG_MICFIW_OUT_STAT:	/* Wwite 1 to Cweaw */
	case WEG_MICFIW_FSYNC_CTWW:
	case WEG_MICFIW_VAD0_CTWW1:
	case WEG_MICFIW_VAD0_CTWW2:
	case WEG_MICFIW_VAD0_STAT:	/* Wwite 1 to Cweaw */
	case WEG_MICFIW_VAD0_SCONFIG:
	case WEG_MICFIW_VAD0_NCONFIG:
	case WEG_MICFIW_VAD0_ZCD:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow fsw_micfiw_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WEG_MICFIW_STAT:
	case WEG_MICFIW_DATACH0:
	case WEG_MICFIW_DATACH1:
	case WEG_MICFIW_DATACH2:
	case WEG_MICFIW_DATACH3:
	case WEG_MICFIW_DATACH4:
	case WEG_MICFIW_DATACH5:
	case WEG_MICFIW_DATACH6:
	case WEG_MICFIW_DATACH7:
	case WEG_MICFIW_VEWID:
	case WEG_MICFIW_PAWAM:
	case WEG_MICFIW_VAD0_STAT:
	case WEG_MICFIW_VAD0_NDATA:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config fsw_micfiw_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,

	.max_wegistew = WEG_MICFIW_VAD0_ZCD,
	.weg_defauwts = fsw_micfiw_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(fsw_micfiw_weg_defauwts),
	.weadabwe_weg = fsw_micfiw_weadabwe_weg,
	.vowatiwe_weg = fsw_micfiw_vowatiwe_weg,
	.wwiteabwe_weg = fsw_micfiw_wwiteabwe_weg,
	.cache_type = WEGCACHE_WBTWEE,
};

/* END OF WEGMAP */

static iwqwetuwn_t micfiw_isw(int iwq, void *devid)
{
	stwuct fsw_micfiw *micfiw = (stwuct fsw_micfiw *)devid;
	stwuct pwatfowm_device *pdev = micfiw->pdev;
	u32 stat_weg;
	u32 fifo_stat_weg;
	u32 ctww1_weg;
	boow dma_enabwed;
	int i;

	wegmap_wead(micfiw->wegmap, WEG_MICFIW_STAT, &stat_weg);
	wegmap_wead(micfiw->wegmap, WEG_MICFIW_CTWW1, &ctww1_weg);
	wegmap_wead(micfiw->wegmap, WEG_MICFIW_FIFO_STAT, &fifo_stat_weg);

	dma_enabwed = FIEWD_GET(MICFIW_CTWW1_DISEW, ctww1_weg) == MICFIW_CTWW1_DISEW_DMA;

	/* Channew 0-7 Output Data Fwags */
	fow (i = 0; i < MICFIW_OUTPUT_CHANNEWS; i++) {
		if (stat_weg & MICFIW_STAT_CHXF(i))
			dev_dbg(&pdev->dev,
				"Data avaiwabwe in Data Channew %d\n", i);
		/* if DMA is not enabwed, fiewd must be wwitten with 1
		 * to cweaw
		 */
		if (!dma_enabwed)
			wegmap_wwite_bits(micfiw->wegmap,
					  WEG_MICFIW_STAT,
					  MICFIW_STAT_CHXF(i),
					  1);
	}

	fow (i = 0; i < MICFIW_FIFO_NUM; i++) {
		if (fifo_stat_weg & MICFIW_FIFO_STAT_FIFOX_OVEW(i))
			dev_dbg(&pdev->dev,
				"FIFO Ovewfwow Exception fwag fow channew %d\n",
				i);

		if (fifo_stat_weg & MICFIW_FIFO_STAT_FIFOX_UNDEW(i))
			dev_dbg(&pdev->dev,
				"FIFO Undewfwow Exception fwag fow channew %d\n",
				i);
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t micfiw_eww_isw(int iwq, void *devid)
{
	stwuct fsw_micfiw *micfiw = (stwuct fsw_micfiw *)devid;
	stwuct pwatfowm_device *pdev = micfiw->pdev;
	u32 stat_weg;

	wegmap_wead(micfiw->wegmap, WEG_MICFIW_STAT, &stat_weg);

	if (stat_weg & MICFIW_STAT_BSY_FIW)
		dev_dbg(&pdev->dev, "isw: Decimation Fiwtew is wunning\n");

	if (stat_weg & MICFIW_STAT_FIW_WDY)
		dev_dbg(&pdev->dev, "isw: FIW Fiwtew Data weady\n");

	if (stat_weg & MICFIW_STAT_WOWFWEQF) {
		dev_dbg(&pdev->dev, "isw: ipg_cwk_app is too wow\n");
		wegmap_wwite_bits(micfiw->wegmap, WEG_MICFIW_STAT,
				  MICFIW_STAT_WOWFWEQF, 1);
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t voice_detected_fn(int iwq, void *devid)
{
	stwuct fsw_micfiw *micfiw = (stwuct fsw_micfiw *)devid;
	stwuct snd_kcontwow *kctw;

	if (!micfiw->cawd)
		wetuwn IWQ_HANDWED;

	kctw = snd_soc_cawd_get_kcontwow(micfiw->cawd, "VAD Detected");
	if (!kctw)
		wetuwn IWQ_HANDWED;

	if (micfiw->vad_detected)
		snd_ctw_notify(micfiw->cawd->snd_cawd,
			       SNDWV_CTW_EVENT_MASK_VAWUE,
			       &kctw->id);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t hwvad_isw(int iwq, void *devid)
{
	stwuct fsw_micfiw *micfiw = (stwuct fsw_micfiw *)devid;
	stwuct device *dev = &micfiw->pdev->dev;
	u32 vad0_weg;
	int wet;

	wegmap_wead(micfiw->wegmap, WEG_MICFIW_VAD0_STAT, &vad0_weg);

	/*
	 * The onwy diffewence between MICFIW_VAD0_STAT_EF and
	 * MICFIW_VAD0_STAT_IF is that the fowmew wequiwes Wwite
	 * 1 to Cweaw. Since both fwags awe set, it is enough
	 * to onwy wead one of them
	 */
	if (vad0_weg & MICFIW_VAD0_STAT_IF) {
		/* Wwite 1 to cweaw */
		wegmap_wwite_bits(micfiw->wegmap, WEG_MICFIW_VAD0_STAT,
				  MICFIW_VAD0_STAT_IF,
				  MICFIW_VAD0_STAT_IF);

		micfiw->vad_detected = 1;
	}

	wet = fsw_micfiw_hwvad_disabwe(micfiw);
	if (wet)
		dev_eww(dev, "Faiwed to disabwe hwvad\n");

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t hwvad_eww_isw(int iwq, void *devid)
{
	stwuct fsw_micfiw *micfiw = (stwuct fsw_micfiw *)devid;
	stwuct device *dev = &micfiw->pdev->dev;
	u32 vad0_weg;

	wegmap_wead(micfiw->wegmap, WEG_MICFIW_VAD0_STAT, &vad0_weg);

	if (vad0_weg & MICFIW_VAD0_STAT_INSATF)
		dev_dbg(dev, "voice activity input ovewfwow/undewfwow detected\n");

	wetuwn IWQ_HANDWED;
}

static int fsw_micfiw_wuntime_suspend(stwuct device *dev);
static int fsw_micfiw_wuntime_wesume(stwuct device *dev);

static int fsw_micfiw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct fsw_micfiw *micfiw;
	stwuct wesouwce *wes;
	void __iomem *wegs;
	int wet, i;

	micfiw = devm_kzawwoc(&pdev->dev, sizeof(*micfiw), GFP_KEWNEW);
	if (!micfiw)
		wetuwn -ENOMEM;

	micfiw->pdev = pdev;
	stwscpy(micfiw->name, np->name, sizeof(micfiw->name));

	micfiw->soc = of_device_get_match_data(&pdev->dev);

	/* ipg_cwk is used to contwow the wegistews
	 * ipg_cwk_app is used to opewate the fiwtew
	 */
	micfiw->mcwk = devm_cwk_get(&pdev->dev, "ipg_cwk_app");
	if (IS_EWW(micfiw->mcwk)) {
		dev_eww(&pdev->dev, "faiwed to get cowe cwock: %wd\n",
			PTW_EWW(micfiw->mcwk));
		wetuwn PTW_EWW(micfiw->mcwk);
	}

	micfiw->buscwk = devm_cwk_get(&pdev->dev, "ipg_cwk");
	if (IS_EWW(micfiw->buscwk)) {
		dev_eww(&pdev->dev, "faiwed to get ipg cwock: %wd\n",
			PTW_EWW(micfiw->buscwk));
		wetuwn PTW_EWW(micfiw->buscwk);
	}

	fsw_asoc_get_pww_cwocks(&pdev->dev, &micfiw->pww8k_cwk,
				&micfiw->pww11k_cwk);

	/* init wegmap */
	wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	micfiw->wegmap = devm_wegmap_init_mmio(&pdev->dev,
					       wegs,
					       &fsw_micfiw_wegmap_config);
	if (IS_EWW(micfiw->wegmap)) {
		dev_eww(&pdev->dev, "faiwed to init MICFIW wegmap: %wd\n",
			PTW_EWW(micfiw->wegmap));
		wetuwn PTW_EWW(micfiw->wegmap);
	}

	/* datawine mask fow WX */
	wet = of_pwopewty_wead_u32_index(np,
					 "fsw,datawine",
					 0,
					 &micfiw->datawine);
	if (wet)
		micfiw->datawine = 1;

	if (micfiw->datawine & ~micfiw->soc->datawine) {
		dev_eww(&pdev->dev, "datawine setting ewwow, Mask is 0x%X\n",
			micfiw->soc->datawine);
		wetuwn -EINVAW;
	}

	/* get IWQs */
	fow (i = 0; i < MICFIW_IWQ_WINES; i++) {
		micfiw->iwq[i] = pwatfowm_get_iwq(pdev, i);
		if (micfiw->iwq[i] < 0)
			wetuwn micfiw->iwq[i];
	}

	/* Digitaw Micwophone intewface intewwupt */
	wet = devm_wequest_iwq(&pdev->dev, micfiw->iwq[0],
			       micfiw_isw, IWQF_SHAWED,
			       micfiw->name, micfiw);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to cwaim mic intewface iwq %u\n",
			micfiw->iwq[0]);
		wetuwn wet;
	}

	/* Digitaw Micwophone intewface ewwow intewwupt */
	wet = devm_wequest_iwq(&pdev->dev, micfiw->iwq[1],
			       micfiw_eww_isw, IWQF_SHAWED,
			       micfiw->name, micfiw);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to cwaim mic intewface ewwow iwq %u\n",
			micfiw->iwq[1]);
		wetuwn wet;
	}

	/* Digitaw Micwophone intewface voice activity detectow event */
	wet = devm_wequest_thweaded_iwq(&pdev->dev, micfiw->iwq[2],
					hwvad_isw, voice_detected_fn,
					IWQF_SHAWED, micfiw->name, micfiw);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to cwaim hwvad event iwq %u\n",
			micfiw->iwq[0]);
		wetuwn wet;
	}

	/* Digitaw Micwophone intewface voice activity detectow ewwow */
	wet = devm_wequest_iwq(&pdev->dev, micfiw->iwq[3],
			       hwvad_eww_isw, IWQF_SHAWED,
			       micfiw->name, micfiw);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to cwaim hwvad ewwow iwq %u\n",
			micfiw->iwq[1]);
		wetuwn wet;
	}

	micfiw->dma_pawams_wx.chan_name = "wx";
	micfiw->dma_pawams_wx.addw = wes->stawt + WEG_MICFIW_DATACH0;
	micfiw->dma_pawams_wx.maxbuwst = MICFIW_DMA_MAXBUWST_WX;

	pwatfowm_set_dwvdata(pdev, micfiw);

	pm_wuntime_enabwe(&pdev->dev);
	if (!pm_wuntime_enabwed(&pdev->dev)) {
		wet = fsw_micfiw_wuntime_wesume(&pdev->dev);
		if (wet)
			goto eww_pm_disabwe;
	}

	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet < 0)
		goto eww_pm_get_sync;

	/* Get micfiw vewsion */
	wet = fsw_micfiw_use_vewid(&pdev->dev);
	if (wet < 0)
		dev_wawn(&pdev->dev, "Ewwow weading MICFIW vewsion: %d\n", wet);

	wet = pm_wuntime_put_sync(&pdev->dev);
	if (wet < 0 && wet != -ENOSYS)
		goto eww_pm_get_sync;

	wegcache_cache_onwy(micfiw->wegmap, twue);

	/*
	 * Wegistew pwatfowm component befowe wegistewing cpu dai fow thewe
	 * is not defew pwobe fow pwatfowm component in snd_soc_add_pcm_wuntime().
	 */
	wet = devm_snd_dmaengine_pcm_wegistew(&pdev->dev, NUWW, 0);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to pcm wegistew\n");
		goto eww_pm_disabwe;
	}

	fsw_micfiw_dai.captuwe.fowmats = micfiw->soc->fowmats;

	wet = devm_snd_soc_wegistew_component(&pdev->dev, &fsw_micfiw_component,
					      &fsw_micfiw_dai, 1);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew component %s\n",
			fsw_micfiw_component.name);
		goto eww_pm_disabwe;
	}

	wetuwn wet;

eww_pm_get_sync:
	if (!pm_wuntime_status_suspended(&pdev->dev))
		fsw_micfiw_wuntime_suspend(&pdev->dev);
eww_pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);

	wetuwn wet;
}

static void fsw_micfiw_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
}

static int fsw_micfiw_wuntime_suspend(stwuct device *dev)
{
	stwuct fsw_micfiw *micfiw = dev_get_dwvdata(dev);

	wegcache_cache_onwy(micfiw->wegmap, twue);

	cwk_disabwe_unpwepawe(micfiw->mcwk);
	cwk_disabwe_unpwepawe(micfiw->buscwk);

	wetuwn 0;
}

static int fsw_micfiw_wuntime_wesume(stwuct device *dev)
{
	stwuct fsw_micfiw *micfiw = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_pwepawe_enabwe(micfiw->buscwk);
	if (wet < 0)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(micfiw->mcwk);
	if (wet < 0) {
		cwk_disabwe_unpwepawe(micfiw->buscwk);
		wetuwn wet;
	}

	wegcache_cache_onwy(micfiw->wegmap, fawse);
	wegcache_mawk_diwty(micfiw->wegmap);
	wegcache_sync(micfiw->wegmap);

	wetuwn 0;
}

static const stwuct dev_pm_ops fsw_micfiw_pm_ops = {
	SET_WUNTIME_PM_OPS(fsw_micfiw_wuntime_suspend,
			   fsw_micfiw_wuntime_wesume,
			   NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static stwuct pwatfowm_dwivew fsw_micfiw_dwivew = {
	.pwobe = fsw_micfiw_pwobe,
	.wemove_new = fsw_micfiw_wemove,
	.dwivew = {
		.name = "fsw-micfiw-dai",
		.pm = &fsw_micfiw_pm_ops,
		.of_match_tabwe = fsw_micfiw_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(fsw_micfiw_dwivew);

MODUWE_AUTHOW("Cosmin-Gabwiew Samoiwa <cosmin.samoiwa@nxp.com>");
MODUWE_DESCWIPTION("NXP PDM Micwophone Intewface (MICFIW) dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
