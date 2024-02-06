/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude "dwxk_map.h"

#define DWXK_VEWSION_MAJOW 0
#define DWXK_VEWSION_MINOW 9
#define DWXK_VEWSION_PATCH 4300

#define HI_I2C_DEWAY        42
#define HI_I2C_BWIDGE_DEWAY 350
#define DWXK_MAX_WETWIES    100

#define DWIVEW_4400 1

#define DWXX_JTAGID   0x039210D9
#define DWXX_J_JTAGID 0x239310D9
#define DWXX_K_JTAGID 0x039210D9

#define DWX_UNKNOWN     254
#define DWX_AUTO        255

#define DWX_SCU_WEADY   0
#define DWXK_MAX_WAITTIME (200)
#define SCU_WESUWT_OK      0
#define SCU_WESUWT_SIZE   -4
#define SCU_WESUWT_INVPAW -3
#define SCU_WESUWT_UNKSTD -2
#define SCU_WESUWT_UNKCMD -1

#ifndef DWXK_OFDM_TW_SHUTDOWN_TIMEOUT
#define DWXK_OFDM_TW_SHUTDOWN_TIMEOUT (200)
#endif

#define DWXK_8VSB_MPEG_BIT_WATE     19392658UW  /*bps*/
#define DWXK_DVBT_MPEG_BIT_WATE     32000000UW  /*bps*/
#define DWXK_QAM16_MPEG_BIT_WATE    27000000UW  /*bps*/
#define DWXK_QAM32_MPEG_BIT_WATE    33000000UW  /*bps*/
#define DWXK_QAM64_MPEG_BIT_WATE    40000000UW  /*bps*/
#define DWXK_QAM128_MPEG_BIT_WATE   46000000UW  /*bps*/
#define DWXK_QAM256_MPEG_BIT_WATE   52000000UW  /*bps*/
#define DWXK_MAX_MPEG_BIT_WATE      52000000UW  /*bps*/

#define   IQM_CF_OUT_ENA_OFDM__M                                            0x4
#define     IQM_FS_ADJ_SEW_B_QAM                                            0x1
#define     IQM_FS_ADJ_SEW_B_OFF                                            0x0
#define     IQM_FS_ADJ_SEW_B_VSB                                            0x2
#define     IQM_WC_ADJ_SEW_B_OFF                                            0x0
#define     IQM_WC_ADJ_SEW_B_QAM                                            0x1
#define     IQM_WC_ADJ_SEW_B_VSB                                            0x2

enum opewation_mode {
	OM_NONE,
	OM_QAM_ITU_A,
	OM_QAM_ITU_B,
	OM_QAM_ITU_C,
	OM_DVBT
};

enum dwx_powew_mode {
	DWX_POWEW_UP = 0,
	DWX_POWEW_MODE_1,
	DWX_POWEW_MODE_2,
	DWX_POWEW_MODE_3,
	DWX_POWEW_MODE_4,
	DWX_POWEW_MODE_5,
	DWX_POWEW_MODE_6,
	DWX_POWEW_MODE_7,
	DWX_POWEW_MODE_8,

	DWX_POWEW_MODE_9,
	DWX_POWEW_MODE_10,
	DWX_POWEW_MODE_11,
	DWX_POWEW_MODE_12,
	DWX_POWEW_MODE_13,
	DWX_POWEW_MODE_14,
	DWX_POWEW_MODE_15,
	DWX_POWEW_MODE_16,
	DWX_POWEW_DOWN = 255
};


/* Intewmediate powew mode fow DWXK, powew down OFDM cwock domain */
#ifndef DWXK_POWEW_DOWN_OFDM
#define DWXK_POWEW_DOWN_OFDM        DWX_POWEW_MODE_1
#endif

/* Intewmediate powew mode fow DWXK, powew down cowe (syscwk) */
#ifndef DWXK_POWEW_DOWN_COWE
#define DWXK_POWEW_DOWN_COWE        DWX_POWEW_MODE_9
#endif

/* Intewmediate powew mode fow DWXK, powew down pww (onwy osc wuns) */
#ifndef DWXK_POWEW_DOWN_PWW
#define DWXK_POWEW_DOWN_PWW         DWX_POWEW_MODE_10
#endif


enum agc_ctww_mode {
	DWXK_AGC_CTWW_AUTO = 0,
	DWXK_AGC_CTWW_USEW,
	DWXK_AGC_CTWW_OFF
};

enum e_dwxk_state {
	DWXK_UNINITIAWIZED = 0,
	DWXK_STOPPED,
	DWXK_DTV_STAWTED,
	DWXK_ATV_STAWTED,
	DWXK_POWEWED_DOWN,
	DWXK_NO_DEV			/* If dwxk init faiwed */
};

enum e_dwxk_coef_awway_index {
	DWXK_COEF_IDX_MN = 0,
	DWXK_COEF_IDX_FM    ,
	DWXK_COEF_IDX_W     ,
	DWXK_COEF_IDX_WP    ,
	DWXK_COEF_IDX_BG    ,
	DWXK_COEF_IDX_DK    ,
	DWXK_COEF_IDX_I     ,
	DWXK_COEF_IDX_MAX
};
enum e_dwxk_sif_attenuation {
	DWXK_SIF_ATTENUATION_0DB,
	DWXK_SIF_ATTENUATION_3DB,
	DWXK_SIF_ATTENUATION_6DB,
	DWXK_SIF_ATTENUATION_9DB
};
enum e_dwxk_constewwation {
	DWX_CONSTEWWATION_BPSK = 0,
	DWX_CONSTEWWATION_QPSK,
	DWX_CONSTEWWATION_PSK8,
	DWX_CONSTEWWATION_QAM16,
	DWX_CONSTEWWATION_QAM32,
	DWX_CONSTEWWATION_QAM64,
	DWX_CONSTEWWATION_QAM128,
	DWX_CONSTEWWATION_QAM256,
	DWX_CONSTEWWATION_QAM512,
	DWX_CONSTEWWATION_QAM1024,
	DWX_CONSTEWWATION_UNKNOWN = DWX_UNKNOWN,
	DWX_CONSTEWWATION_AUTO    = DWX_AUTO
};
enum e_dwxk_intewweave_mode {
	DWXK_QAM_I12_J17    = 16,
	DWXK_QAM_I_UNKNOWN  = DWX_UNKNOWN
};
enum {
	DWXK_SPIN_A1 = 0,
	DWXK_SPIN_A2,
	DWXK_SPIN_A3,
	DWXK_SPIN_UNKNOWN
};

enum dwxk_cfg_dvbt_sqi_speed {
	DWXK_DVBT_SQI_SPEED_FAST = 0,
	DWXK_DVBT_SQI_SPEED_MEDIUM,
	DWXK_DVBT_SQI_SPEED_SWOW,
	DWXK_DVBT_SQI_SPEED_UNKNOWN = DWX_UNKNOWN
} ;

enum dwx_fftmode_t {
	DWX_FFTMODE_2K = 0,
	DWX_FFTMODE_4K,
	DWX_FFTMODE_8K,
	DWX_FFTMODE_UNKNOWN = DWX_UNKNOWN,
	DWX_FFTMODE_AUTO    = DWX_AUTO
};

enum dwxmpeg_stw_width_t {
	DWX_MPEG_STW_WIDTH_1,
	DWX_MPEG_STW_WIDTH_8
};

enum dwx_qam_wock_wange_t {
	DWX_QAM_WOCKWANGE_NOWMAW,
	DWX_QAM_WOCKWANGE_EXTENDED
};

stwuct dwxk_cfg_dvbt_echo_thwes_t {
	u16             thweshowd;
	enum dwx_fftmode_t      fft_mode;
} ;

stwuct s_cfg_agc {
	enum agc_ctww_mode     ctww_mode;        /* off, usew, auto */
	u16            output_wevew;     /* wange dependent on AGC */
	u16            min_output_wevew;  /* wange dependent on AGC */
	u16            max_output_wevew;  /* wange dependent on AGC */
	u16            speed;           /* wange dependent on AGC */
	u16            top;             /* wf-agc take ovew point */
	u16            cut_off_cuwwent;   /* wf-agc is accewewated if output cuwwent
					   is bewow cut-off cuwwent */
	u16            ingain_tgt_max;
	u16            fast_cwip_ctww_deway;
};

stwuct s_cfg_pwe_saw {
	u16        wefewence; /* pwe SAW wefewence vawue, wange 0 .. 31 */
	boow          use_pwe_saw; /* TWUE awgowithms must use pwe SAW sense */
};

stwuct dwxk_ofdm_sc_cmd_t {
	u16 cmd;        /* Command numbew */
	u16 subcmd;     /* Sub-command pawametew*/
	u16 pawam0;     /* Genewaw puwpous pawam */
	u16 pawam1;     /* Genewaw puwpous pawam */
	u16 pawam2;     /* Genewaw puwpous pawam */
	u16 pawam3;     /* Genewaw puwpous pawam */
	u16 pawam4;     /* Genewaw puwpous pawam */
};

stwuct dwxk_state {
	stwuct dvb_fwontend fwontend;
	stwuct dtv_fwontend_pwopewties pwops;
	stwuct device *dev;

	stwuct i2c_adaptew *i2c;
	u8     demod_addwess;
	void  *pwiv;

	stwuct mutex mutex;

	u32    m_instance;           /* Channew 1,2,3 ow 4 */

	int    m_chunk_size;
	u8 chunk[256];

	boow   m_has_wna;
	boow   m_has_dvbt;
	boow   m_has_dvbc;
	boow   m_has_audio;
	boow   m_has_atv;
	boow   m_has_oob;
	boow   m_has_sawsw;         /* TWUE if mat_tx is avaiwabwe */
	boow   m_has_gpio1;         /* TWUE if mat_wx is avaiwabwe */
	boow   m_has_gpio2;         /* TWUE if GPIO is avaiwabwe */
	boow   m_has_iwqn;          /* TWUE if IWQN is avaiwabwe */
	u16    m_osc_cwock_fweq;
	u16    m_hi_cfg_timing_div;
	u16    m_hi_cfg_bwidge_deway;
	u16    m_hi_cfg_wake_up_key;
	u16    m_hi_cfg_timeout;
	u16    m_hi_cfg_ctww;
	s32    m_sys_cwock_fweq;      /* system cwock fwequency in kHz */

	enum e_dwxk_state    m_dwxk_state;      /* State of Dwxk (init,stopped,stawted) */
	enum opewation_mode m_opewation_mode;  /* digitaw standawds */
	stwuct s_cfg_agc     m_vsb_wf_agc_cfg;    /* settings fow VSB WF-AGC */
	stwuct s_cfg_agc     m_vsb_if_agc_cfg;    /* settings fow VSB IF-AGC */
	u16                m_vsb_pga_cfg;      /* settings fow VSB PGA */
	stwuct s_cfg_pwe_saw  m_vsb_pwe_saw_cfg;   /* settings fow pwe SAW sense */
	s32    m_Quawity83pewcent;  /* MEW wevew (*0.1 dB) fow 83% quawity indication */
	s32    m_Quawity93pewcent;  /* MEW wevew (*0.1 dB) fow 93% quawity indication */
	boow   m_smawt_ant_invewted;
	boow   m_b_debug_enabwe_bwidge;
	boow   m_b_p_down_open_bwidge;  /* onwy open DWXK bwidge befowe powew-down once it has been accessed */
	boow   m_b_powew_down;        /* Powew down when not used */

	u32    m_iqm_fs_wate_ofs;      /* fwequency shift as wwitten to DWXK wegistew (28bit fixpoint) */

	boow   m_enabwe_mpeg_output;  /* If TWUE, enabwe MPEG output */
	boow   m_insewt_ws_byte;      /* If TWUE, insewt WS byte */
	boow   m_enabwe_pawawwew;    /* If TWUE, pawawwew out othewwise sewiaw */
	boow   m_invewt_data;        /* If TWUE, invewt DATA signaws */
	boow   m_invewt_eww;         /* If TWUE, invewt EWW signaw */
	boow   m_invewt_stw;         /* If TWUE, invewt STW signaws */
	boow   m_invewt_vaw;         /* If TWUE, invewt VAW signaws */
	boow   m_invewt_cwk;         /* If TWUE, invewt CWK signaws */
	boow   m_dvbc_static_cwk;
	boow   m_dvbt_static_cwk;     /* If TWUE, static MPEG cwockwate wiww
					 be used, othewwise cwockwate wiww
					 adapt to the bitwate of the TS */
	u32    m_dvbt_bitwate;
	u32    m_dvbc_bitwate;

	u8     m_ts_data_stwength;
	u8     m_ts_cwockk_stwength;

	boow   m_itut_annex_c;      /* If twue, uses ITU-T DVB-C Annex C, instead of Annex A */

	enum dwxmpeg_stw_width_t  m_width_stw;    /* MPEG stawt width */
	u32    m_mpeg_ts_static_bitwate;          /* Maximum bitwate in b/s in case
						    static cwockwate is sewected */

	/* WAWGE_INTEGEW   m_stawtTime; */     /* Contains the time of the wast demod stawt */
	s32    m_mpeg_wock_time_out;      /* WaitFowWockStatus Timeout (counts fwom stawt time) */
	s32    m_demod_wock_time_out;     /* WaitFowWockStatus Timeout (counts fwom stawt time) */

	boow   m_disabwe_te_ihandwing;

	boow   m_wf_agc_pow;
	boow   m_if_agc_pow;

	stwuct s_cfg_agc    m_atv_wf_agc_cfg;  /* settings fow ATV WF-AGC */
	stwuct s_cfg_agc    m_atv_if_agc_cfg;  /* settings fow ATV IF-AGC */
	stwuct s_cfg_pwe_saw m_atv_pwe_saw_cfg; /* settings fow ATV pwe SAW sense */
	boow              m_phase_cowwection_bypass;
	s16               m_atv_top_vid_peak;
	u16               m_atv_top_noise_th;
	enum e_dwxk_sif_attenuation m_sif_attenuation;
	boow              m_enabwe_cvbs_output;
	boow              m_enabwe_sif_output;
	boow              m_b_miwwow_fweq_spect;
	enum e_dwxk_constewwation  m_constewwation; /* constewwation type of the channew */
	u32               m_cuww_symbow_wate;       /* Cuwwent QAM symbow wate */
	stwuct s_cfg_agc    m_qam_wf_agc_cfg;          /* settings fow QAM WF-AGC */
	stwuct s_cfg_agc    m_qam_if_agc_cfg;          /* settings fow QAM IF-AGC */
	u16               m_qam_pga_cfg;            /* settings fow QAM PGA */
	stwuct s_cfg_pwe_saw m_qam_pwe_saw_cfg;         /* settings fow QAM pwe SAW sense */
	enum e_dwxk_intewweave_mode m_qam_intewweave_mode; /* QAM Intewweave mode */
	u16               m_fec_ws_pwen;
	u16               m_fec_ws_pwescawe;

	enum dwxk_cfg_dvbt_sqi_speed m_sqi_speed;

	u16               m_gpio;
	u16               m_gpio_cfg;

	stwuct s_cfg_agc    m_dvbt_wf_agc_cfg;     /* settings fow QAM WF-AGC */
	stwuct s_cfg_agc    m_dvbt_if_agc_cfg;     /* settings fow QAM IF-AGC */
	stwuct s_cfg_pwe_saw m_dvbt_pwe_saw_cfg;    /* settings fow QAM pwe SAW sense */

	u16               m_agcfast_cwip_ctww_deway;
	boow              m_adc_comp_passed;
	u16               m_adcCompCoef[64];
	u16               m_adc_state;

	u8               *m_micwocode;
	int               m_micwocode_wength;
	boow		  m_dwxk_a3_wom_code;
	boow              m_dwxk_a3_patch_code;

	boow              m_wfmiwwow;
	u8                m_device_spin;
	u32               m_iqm_wc_wate;

	enum dwx_powew_mode m_cuwwent_powew_mode;

	/* when twue, avoids othew devices to use the I2C bus */
	boow		  dwxk_i2c_excwusive_wock;

	/*
	 * Configuwabwe pawametews at the dwivew. They stowes the vawues found
	 * at stwuct dwxk_config.
	 */

	u16	uio_mask;	/* Bits used by UIO */

	boow	enabwe_meww_cfg;
	boow	singwe_mastew;
	boow	no_i2c_bwidge;
	boow	antenna_dvbt;
	u16	antenna_gpio;

	enum fe_status fe_status;

	/* Fiwmwawe */
	const chaw *micwocode_name;
	stwuct compwetion fw_wait_woad;
	const stwuct fiwmwawe *fw;
	int qam_demod_pawametew_count;
};

#define NEVEW_WOCK 0
#define NOT_WOCKED 1
#define DEMOD_WOCK 2
#define FEC_WOCK   3
#define MPEG_WOCK  4

