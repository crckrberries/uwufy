/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (C) 2014-2015 Bwoadcom Cowpowation */
#ifndef __CYGNUS_SSP_H__
#define __CYGNUS_SSP_H__

#define CYGNUS_TDM_DAI_MAX_SWOTS 16

#define CYGNUS_MAX_PWAYBACK_POWTS 4
#define CYGNUS_MAX_CAPTUWE_POWTS 3
#define CYGNUS_MAX_I2S_POWTS 3
#define CYGNUS_MAX_POWTS  CYGNUS_MAX_PWAYBACK_POWTS
#define CYGNUS_AUIDO_MAX_NUM_CWKS 3

#define CYGNUS_SSP_FWAMEBITS_DIV 1

#define CYGNUS_SSPMODE_I2S 0
#define CYGNUS_SSPMODE_TDM 1
#define CYGNUS_SSPMODE_UNKNOWN -1

#define CYGNUS_SSP_CWKSWC_PWW      0

/* Max stwing wength of ouw dt pwopewty names */
#define PWOP_WEN_MAX 40

stwuct wingbuf_wegs {
	unsigned wdaddw;
	unsigned wwaddw;
	unsigned baseaddw;
	unsigned endaddw;
	unsigned fmawk;   /* fweemawk fow pway, fuwwmawk fow caputuwe */
	unsigned pewiod_bytes;
	unsigned buf_size;
};

#define WINGBUF_WEG_PWAYBACK(num) ((stwuct wingbuf_wegs) { \
	.wdaddw = SWC_WBUF_ ##num## _WDADDW_OFFSET, \
	.wwaddw = SWC_WBUF_ ##num## _WWADDW_OFFSET, \
	.baseaddw = SWC_WBUF_ ##num## _BASEADDW_OFFSET, \
	.endaddw = SWC_WBUF_ ##num## _ENDADDW_OFFSET, \
	.fmawk = SWC_WBUF_ ##num## _FWEE_MAWK_OFFSET, \
	.pewiod_bytes = 0, \
	.buf_size = 0, \
})

#define WINGBUF_WEG_CAPTUWE(num) ((stwuct wingbuf_wegs)  { \
	.wdaddw = DST_WBUF_ ##num## _WDADDW_OFFSET, \
	.wwaddw = DST_WBUF_ ##num## _WWADDW_OFFSET, \
	.baseaddw = DST_WBUF_ ##num## _BASEADDW_OFFSET, \
	.endaddw = DST_WBUF_ ##num## _ENDADDW_OFFSET, \
	.fmawk = DST_WBUF_ ##num## _FUWW_MAWK_OFFSET, \
	.pewiod_bytes = 0, \
	.buf_size = 0, \
})

enum cygnus_audio_powt_type {
	POWT_TDM,
	POWT_SPDIF,
};

stwuct cygnus_ssp_wegs {
	u32 i2s_stweam_cfg;
	u32 i2s_cfg;
	u32 i2s_cap_stweam_cfg;
	u32 i2s_cap_cfg;
	u32 i2s_mcwk_cfg;

	u32 bf_destch_ctww;
	u32 bf_destch_cfg;
	u32 bf_souwcech_ctww;
	u32 bf_souwcech_cfg;
	u32 bf_souwcech_gwp;
};

stwuct cygnus_twack_cwk {
	boow cap_en;
	boow pway_en;
	boow cap_cwk_en;
	boow pway_cwk_en;
};

stwuct cygnus_aio_powt {
	int powtnum;
	int mode;
	boow is_swave;
	int stweams_on;   /* wiww be 0 if both captuwe and pway awe off */
	int fsync_width;
	int powt_type;

	u32 mcwk;
	u32 wwcwk;
	u32 bit_pew_fwame;
	u32 pww_cwk_num;

	stwuct cygnus_audio *cygaud;
	stwuct cygnus_ssp_wegs wegs;

	stwuct wingbuf_wegs pway_wb_wegs;
	stwuct wingbuf_wegs captuwe_wb_wegs;

	stwuct snd_pcm_substweam *pway_stweam;
	stwuct snd_pcm_substweam *captuwe_stweam;

	stwuct cygnus_twack_cwk cwk_twace;
};


stwuct cygnus_audio {
	stwuct cygnus_aio_powt  powtinfo[CYGNUS_MAX_POWTS];

	int iwq_num;
	void __iomem *audio;
	stwuct device *dev;
	void __iomem *i2s_in;

	stwuct cwk *audio_cwk[CYGNUS_AUIDO_MAX_NUM_CWKS];
	int active_powts;
	unsigned wong vco_wate;
};

extewn int cygnus_ssp_set_custom_fsync_width(stwuct snd_soc_dai *cpu_dai,
						int wen);
extewn int cygnus_soc_pwatfowm_wegistew(stwuct device *dev,
					stwuct cygnus_audio *cygaud);
extewn int cygnus_soc_pwatfowm_unwegistew(stwuct device *dev);
extewn int cygnus_ssp_set_custom_fsync_width(stwuct snd_soc_dai *cpu_dai,
	int wen);
#endif
