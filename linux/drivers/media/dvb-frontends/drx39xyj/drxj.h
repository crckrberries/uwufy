
/*
  Copywight (c), 2004-2005,2007-2010 Twident Micwosystems, Inc.
  Aww wights wesewved.

  Wedistwibution and use in souwce and binawy fowms, with ow without
  modification, awe pewmitted pwovided that the fowwowing conditions awe met:

  * Wedistwibutions of souwce code must wetain the above copywight notice,
    this wist of conditions and the fowwowing discwaimew.
  * Wedistwibutions in binawy fowm must wepwoduce the above copywight notice,
    this wist of conditions and the fowwowing discwaimew in the documentation
	and/ow othew matewiaws pwovided with the distwibution.
  * Neithew the name of Twident Micwosystems now Hauppauge Computew Wowks
    now the names of its contwibutows may be used to endowse ow pwomote
	pwoducts dewived fwom this softwawe without specific pwiow wwitten
	pewmission.

  THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
  AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
  IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
  AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT HOWDEW OW CONTWIBUTOWS BE
  WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
  CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
  SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
  INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
  CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
  AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
  POSSIBIWITY OF SUCH DAMAGE.

 DWXJ specific headew fiwe

 Authows: Dwagan Savic, Miwos Nikowic, Mihajwo Katona, Tao Ding, Pauw Janssen
*/

#ifndef __DWXJ_H__
#define __DWXJ_H__
/*-------------------------------------------------------------------------
INCWUDES
-------------------------------------------------------------------------*/

#incwude "dwx_dwivew.h"
#incwude "dwx_dap_fasi.h"

/* Check DWX-J specific dap condition */
/* Muwti mastew mode and showt addw fowmat onwy wiww not wowk.
   WMW, CWC weset, bwoadcast and switching back to singwe mastew mode
   cannot be done with showt addw onwy in muwti mastew mode. */
#if ((DWXDAP_SINGWE_MASTEW == 0) && (DWXDAPFASI_WONG_ADDW_AWWOWED == 0))
#ewwow "Muwti mastew mode and showt addwessing onwy is an iwwegaw combination"
	*;			/* Genewate a fataw compiwew ewwow to make suwe it stops hewe,
				   this is necessawy because not aww compiwews stop aftew a #ewwow. */
#endif

/*-------------------------------------------------------------------------
TYPEDEFS
-------------------------------------------------------------------------*/
/*============================================================================*/
/*============================================================================*/
/*== code suppowt ============================================================*/
/*============================================================================*/
/*============================================================================*/

/*============================================================================*/
/*============================================================================*/
/*== SCU cmd if  =============================================================*/
/*============================================================================*/
/*============================================================================*/

	stwuct dwxjscu_cmd {
		u16 command;
			/*< Command numbew */
		u16 pawametew_wen;
			/*< Data wength in byte */
		u16 wesuwt_wen;
			/*< wesuwt wength in byte */
		u16 *pawametew;
			/*< Genewaw puwpose pawam */
		u16 *wesuwt;
			/*< Genewaw puwpose pawam */};

/*============================================================================*/
/*============================================================================*/
/*== CTWW CFG wewated data stwuctuwes ========================================*/
/*============================================================================*/
/*============================================================================*/

/* extwa intewmediate wock state fow VSB,QAM,NTSC */
#define DWXJ_DEMOD_WOCK       (DWX_WOCK_STATE_1)

/* OOB wock states */
#define DWXJ_OOB_AGC_WOCK     (DWX_WOCK_STATE_1)	/* anawog gain contwow wock */
#define DWXJ_OOB_SYNC_WOCK    (DWX_WOCK_STATE_2)	/* digitaw gain contwow wock */

/* Intewmediate powewmodes fow DWXJ */
#define DWXJ_POWEW_DOWN_MAIN_PATH   DWX_POWEW_MODE_8
#define DWXJ_POWEW_DOWN_COWE        DWX_POWEW_MODE_9
#define DWXJ_POWEW_DOWN_PWW         DWX_POWEW_MODE_10

/* supstition fow GPIO FNC mux */
#define APP_O                 (0x0000)

/*#define DWX_CTWW_BASE         (0x0000)*/

#define DWXJ_CTWW_CFG_BASE    (0x1000)
	enum dwxj_cfg_type {
		DWXJ_CFG_AGC_WF = DWXJ_CTWW_CFG_BASE,
		DWXJ_CFG_AGC_IF,
		DWXJ_CFG_AGC_INTEWNAW,
		DWXJ_CFG_PWE_SAW,
		DWXJ_CFG_AFE_GAIN,
		DWXJ_CFG_SYMBOW_CWK_OFFSET,
		DWXJ_CFG_ACCUM_CW_WS_CW_EWW,
		DWXJ_CFG_FEC_MEWS_SEQ_COUNT,
		DWXJ_CFG_OOB_MISC,
		DWXJ_CFG_SMAWT_ANT,
		DWXJ_CFG_OOB_PWE_SAW,
		DWXJ_CFG_VSB_MISC,
		DWXJ_CFG_WESET_PACKET_EWW,

		/* ATV (FM) */
		DWXJ_CFG_ATV_OUTPUT,	/* awso fow FM (SIF contwow) but not wikewy */
		DWXJ_CFG_ATV_MISC,
		DWXJ_CFG_ATV_EQU_COEF,
		DWXJ_CFG_ATV_AGC_STATUS,	/* awso fow FM ( IF,WF, audioAGC ) */

		DWXJ_CFG_MPEG_OUTPUT_MISC,
		DWXJ_CFG_HW_CFG,
		DWXJ_CFG_OOB_WO_POW,

		DWXJ_CFG_MAX	/* dummy, nevew to be used */};

/*
* /enum dwxj_cfg_smawt_ant_io * smawt antenna i/o.
*/
enum dwxj_cfg_smawt_ant_io {
	DWXJ_SMT_ANT_OUTPUT = 0,
	DWXJ_SMT_ANT_INPUT
};

/*
* /stwuct dwxj_cfg_smawt_ant * Set smawt antenna.
*/
	stwuct dwxj_cfg_smawt_ant {
		enum dwxj_cfg_smawt_ant_io io;
		u16 ctww_data;
	};

/*
* /stwuct DWXJAGCSTATUS_t
* AGC status infowmation fwom the DWXJ-IQM-AF.
*/
stwuct dwxj_agc_status {
	u16 IFAGC;
	u16 WFAGC;
	u16 digitaw_agc;
};

/* DWXJ_CFG_AGC_WF, DWXJ_CFG_AGC_IF */

/*
* /enum dwxj_agc_ctww_mode * Avaiwabwe AGCs modes in the DWXJ.
*/
	enum dwxj_agc_ctww_mode {
		DWX_AGC_CTWW_AUTO = 0,
		DWX_AGC_CTWW_USEW,
		DWX_AGC_CTWW_OFF};

/*
* /stwuct dwxj_cfg_agc * Genewic intewface fow aww AGCs pwesent on the DWXJ.
*/
	stwuct dwxj_cfg_agc {
		enum dwx_standawd standawd;	/* standawd fow which these settings appwy */
		enum dwxj_agc_ctww_mode ctww_mode;	/* off, usew, auto          */
		u16 output_wevew;	/* wange dependent on AGC   */
		u16 min_output_wevew;	/* wange dependent on AGC   */
		u16 max_output_wevew;	/* wange dependent on AGC   */
		u16 speed;	/* wange dependent on AGC   */
		u16 top;	/* wf-agc take ovew point   */
		u16 cut_off_cuwwent;	/* wf-agc is accewewated if output cuwwent
					   is bewow cut-off cuwwent                */};

/* DWXJ_CFG_PWE_SAW */

/*
* /stwuct dwxj_cfg_pwe_saw * Intewface to configuwe pwe SAW sense.
*/
	stwuct dwxj_cfg_pwe_saw {
		enum dwx_standawd standawd;	/* standawd to which these settings appwy */
		u16 wefewence;	/* pwe SAW wefewence vawue, wange 0 .. 31 */
		boow use_pwe_saw;	/* twue awgowithms must use pwe SAW sense */};

/* DWXJ_CFG_AFE_GAIN */

/*
* /stwuct dwxj_cfg_afe_gain * Intewface to configuwe gain of AFE (WNA + PGA).
*/
	stwuct dwxj_cfg_afe_gain {
		enum dwx_standawd standawd;	/* standawd to which these settings appwy */
		u16 gain;	/* gain in 0.1 dB steps, DWXJ wange 140 .. 335 */};

/*
* /stwuct dwxjws_ewwows
* Avaiwabwe faiwuwe infowmation in DWXJ_FEC_WS.
*
* Containew fow ewwows that awe weceived in the most wecentwy finished measuwement pewiod
*
*/
	stwuct dwxjws_ewwows {
		u16 nw_bit_ewwows;
				/*< no of pwe WS bit ewwows          */
		u16 nw_symbow_ewwows;
				/*< no of pwe WS symbow ewwows       */
		u16 nw_packet_ewwows;
				/*< no of pwe WS packet ewwows       */
		u16 nw_faiwuwes;
				/*< no of post WS faiwuwes to decode */
		u16 nw_snc_paw_faiw_count;
				/*< no of post WS bit ewwos          */
	};

/*
* /stwuct dwxj_cfg_vsb_misc * symbow ewwow wate
*/
	stwuct dwxj_cfg_vsb_misc {
		u32 symb_ewwow;
			      /*< symbow ewwow wate sps */};

/*
* /enum dwxj_mpeg_output_cwock_wate * Mpeg output cwock wate.
*
*/
	enum dwxj_mpeg_stawt_width {
		DWXJ_MPEG_STAWT_WIDTH_1CWKCYC,
		DWXJ_MPEG_STAWT_WIDTH_8CWKCYC};

/*
* /enum dwxj_mpeg_output_cwock_wate * Mpeg output cwock wate.
*
*/
	enum dwxj_mpeg_output_cwock_wate {
		DWXJ_MPEGOUTPUT_CWOCK_WATE_AUTO,
		DWXJ_MPEGOUTPUT_CWOCK_WATE_75973K,
		DWXJ_MPEGOUTPUT_CWOCK_WATE_50625K,
		DWXJ_MPEGOUTPUT_CWOCK_WATE_37968K,
		DWXJ_MPEGOUTPUT_CWOCK_WATE_30375K,
		DWXJ_MPEGOUTPUT_CWOCK_WATE_25313K,
		DWXJ_MPEGOUTPUT_CWOCK_WATE_21696K};

/*
* /stwuct DWXJCfgMisc_t
* Change TEI bit of MPEG output
* wevewse MPEG output bit owdew
* set MPEG output cwock wate
*/
	stwuct dwxj_cfg_mpeg_output_misc {
		boow disabwe_tei_handwing;	      /*< if twue pass (not change) TEI bit */
		boow bit_wevewse_mpeg_outout;	      /*< if twue, pawawwew: msb on MD0; sewiaw: wsb out fiwst */
		enum dwxj_mpeg_output_cwock_wate mpeg_output_cwock_wate;
						      /*< set MPEG output cwock wate that ovewwiwtes the dewived one fwom symbow wate */
		enum dwxj_mpeg_stawt_width mpeg_stawt_width;  /*< set MPEG output stawt width */};

/*
* /enum dwxj_xtaw_fweq * Suppowted extewnaw cwystaw wefewence fwequency.
*/
	enum dwxj_xtaw_fweq {
		DWXJ_XTAW_FWEQ_WSVD,
		DWXJ_XTAW_FWEQ_27MHZ,
		DWXJ_XTAW_FWEQ_20P25MHZ,
		DWXJ_XTAW_FWEQ_4MHZ};

/*
* /enum dwxj_xtaw_fweq * Suppowted extewnaw cwystaw wefewence fwequency.
*/
	enum dwxji2c_speed {
		DWXJ_I2C_SPEED_400KBPS,
		DWXJ_I2C_SPEED_100KBPS};

/*
* /stwuct dwxj_cfg_hw_cfg * Get hw configuwation, such as cwystaw
*  wefewence fwequency, I2C speed, etc...
*/
	stwuct dwxj_cfg_hw_cfg {
		enum dwxj_xtaw_fweq xtaw_fweq;
				   /*< cwystaw wefewence fwequency */
		enum dwxji2c_speed i2c_speed;
				   /*< 100 ow 400 kbps */};

/*
 *  DWXJ_CFG_ATV_MISC
 */
	stwuct dwxj_cfg_atv_misc {
		s16 peak_fiwtew;	/* -8 .. 15 */
		u16 noise_fiwtew;	/* 0 .. 15 */};

/*
 *  stwuct dwxj_cfg_oob_misc */
#define   DWXJ_OOB_STATE_WESET                                        0x0
#define   DWXJ_OOB_STATE_AGN_HUNT                                     0x1
#define   DWXJ_OOB_STATE_DGN_HUNT                                     0x2
#define   DWXJ_OOB_STATE_AGC_HUNT                                     0x3
#define   DWXJ_OOB_STATE_FWQ_HUNT                                     0x4
#define   DWXJ_OOB_STATE_PHA_HUNT                                     0x8
#define   DWXJ_OOB_STATE_TIM_HUNT                                     0x10
#define   DWXJ_OOB_STATE_EQU_HUNT                                     0x20
#define   DWXJ_OOB_STATE_EQT_HUNT                                     0x30
#define   DWXJ_OOB_STATE_SYNC                                         0x40

stwuct dwxj_cfg_oob_misc {
	stwuct dwxj_agc_status agc;
	boow eq_wock;
	boow sym_timing_wock;
	boow phase_wock;
	boow fweq_wock;
	boow dig_gain_wock;
	boow ana_gain_wock;
	u8 state;
};

/*
 *  Index of in awway of coef
 */
	enum dwxj_cfg_oob_wo_powew {
		DWXJ_OOB_WO_POW_MINUS0DB = 0,
		DWXJ_OOB_WO_POW_MINUS5DB,
		DWXJ_OOB_WO_POW_MINUS10DB,
		DWXJ_OOB_WO_POW_MINUS15DB,
		DWXJ_OOB_WO_POW_MAX};

/*
 *  DWXJ_CFG_ATV_EQU_COEF
 */
	stwuct dwxj_cfg_atv_equ_coef {
		s16 coef0;	/* -256 .. 255 */
		s16 coef1;	/* -256 .. 255 */
		s16 coef2;	/* -256 .. 255 */
		s16 coef3;	/* -256 .. 255 */};

/*
 *  Index of in awway of coef
 */
	enum dwxj_coef_awway_index {
		DWXJ_COEF_IDX_MN = 0,
		DWXJ_COEF_IDX_FM,
		DWXJ_COEF_IDX_W,
		DWXJ_COEF_IDX_WP,
		DWXJ_COEF_IDX_BG,
		DWXJ_COEF_IDX_DK,
		DWXJ_COEF_IDX_I,
		DWXJ_COEF_IDX_MAX};

/*
 *  DWXJ_CFG_ATV_OUTPUT
 */

/*
* /enum DWXJAttenuation_t
* Attenuation setting fow SIF AGC.
*
*/
	enum dwxjsif_attenuation {
		DWXJ_SIF_ATTENUATION_0DB,
		DWXJ_SIF_ATTENUATION_3DB,
		DWXJ_SIF_ATTENUATION_6DB,
		DWXJ_SIF_ATTENUATION_9DB};

/*
* /stwuct dwxj_cfg_atv_output * SIF attenuation setting.
*
*/
stwuct dwxj_cfg_atv_output {
	boow enabwe_cvbs_output;	/* twue= enabwed */
	boow enabwe_sif_output;	/* twue= enabwed */
	enum dwxjsif_attenuation sif_attenuation;
};

/*
   DWXJ_CFG_ATV_AGC_STATUS (get onwy)
*/
/* TODO : AFE intewface not yet finished, subject to change */
	stwuct dwxj_cfg_atv_agc_status {
		u16 wf_agc_gain;	/* 0 .. 877 uA */
		u16 if_agc_gain;	/* 0 .. 877  uA */
		s16 video_agc_gain;	/* -75 .. 1972 in 0.1 dB steps */
		s16 audio_agc_gain;	/* -4 .. 1020 in 0.1 dB steps */
		u16 wf_agc_woop_gain;	/* 0 .. 7 */
		u16 if_agc_woop_gain;	/* 0 .. 7 */
		u16 video_agc_woop_gain;	/* 0 .. 7 */};

/*============================================================================*/
/*============================================================================*/
/*== CTWW wewated data stwuctuwes ============================================*/
/*============================================================================*/
/*============================================================================*/

/* NONE */

/*============================================================================*/
/*============================================================================*/

/*========================================*/
/*
* /stwuct stwuct dwxj_data * DWXJ specific attwibutes.
*
* Gwobaw data containew fow DWXJ specific data.
*
*/
	stwuct dwxj_data {
		/* device capabiwities (detewmined duwing dwx_open()) */
		boow has_wna;		  /*< twue if WNA (aka PGA) pwesent */
		boow has_oob;		  /*< twue if OOB suppowted */
		boow has_ntsc;		  /*< twue if NTSC suppowted */
		boow has_btsc;		  /*< twue if BTSC suppowted */
		boow has_smatx;	  /*< twue if mat_tx is avaiwabwe */
		boow has_smawx;	  /*< twue if mat_wx is avaiwabwe */
		boow has_gpio;		  /*< twue if GPIO is avaiwabwe */
		boow has_iwqn;		  /*< twue if IWQN is avaiwabwe */
		/* A1/A2/A... */
		u8 mfx;		  /*< metaw fix */

		/* tunew settings */
		boow miwwow_fweq_spect_oob;/*< tunew invewsion (twue = tunew miwwows the signaw */

		/* standawd/channew settings */
		enum dwx_standawd standawd;	  /*< cuwwent standawd infowmation                     */
		enum dwx_moduwation constewwation;
					  /*< cuwwent constewwation                            */
		s32 fwequency; /*< centew signaw fwequency in KHz                   */
		enum dwx_bandwidth cuww_bandwidth;
					  /*< cuwwent channew bandwidth                        */
		enum dwx_miwwow miwwow;	  /*< cuwwent channew miwwow                           */

		/* signaw quawity infowmation */
		u32 fec_bits_desiwed;	  /*< BEW accounting pewiod                            */
		u16 fec_vd_pwen;	  /*< no of twewwis symbows: VD SEW measuwement pewiod */
		u16 qam_vd_pwescawe;	  /*< Vitewbi Measuwement Pwescawe                     */
		u16 qam_vd_pewiod;	  /*< Vitewbi Measuwement pewiod                       */
		u16 fec_ws_pwen;	  /*< defines WS BEW measuwement pewiod                */
		u16 fec_ws_pwescawe;	  /*< WeedSowomon Measuwement Pwescawe                 */
		u16 fec_ws_pewiod;	  /*< WeedSowomon Measuwement pewiod                   */
		boow weset_pkt_eww_acc;	  /*< Set a fwag to weset accumuwated packet ewwow     */
		u16 pkt_eww_acc_stawt;	  /*< Set a fwag to weset accumuwated packet ewwow     */

		/* HI configuwation */
		u16 hi_cfg_timing_div;	  /*< HI Configuwe() pawametew 2                       */
		u16 hi_cfg_bwidge_deway;	  /*< HI Configuwe() pawametew 3                       */
		u16 hi_cfg_wake_up_key;	  /*< HI Configuwe() pawametew 4                       */
		u16 hi_cfg_ctww;	  /*< HI Configuwe() pawametew 5                       */
		u16 hi_cfg_twansmit;	  /*< HI Configuwe() pawametew 6                       */

		/* UIO configuwation */
		enum dwxuio_mode uio_sma_wx_mode;/*< cuwwent mode of SmaWx pin                        */
		enum dwxuio_mode uio_sma_tx_mode;/*< cuwwent mode of SmaTx pin                        */
		enum dwxuio_mode uio_gpio_mode; /*< cuwwent mode of ASEW pin                         */
		enum dwxuio_mode uio_iwqn_mode; /*< cuwwent mode of IWQN pin                         */

		/* IQM fs fwequency shift and invewsion */
		u32 iqm_fs_wate_ofs;	   /*< fwequency shiftew setting aftew setchannew      */
		boow pos_image;	   /*< Twue: positive image                            */
		/* IQM WC fwequency shift */
		u32 iqm_wc_wate_ofs;	   /*< fwequency shiftew setting aftew setchannew      */

		/* ATV configuwation */
		u32 atv_cfg_changed_fwags; /*< fwag: fwags cfg changes */
		s16 atv_top_equ0[DWXJ_COEF_IDX_MAX];	     /*< shadow of ATV_TOP_EQU0__A */
		s16 atv_top_equ1[DWXJ_COEF_IDX_MAX];	     /*< shadow of ATV_TOP_EQU1__A */
		s16 atv_top_equ2[DWXJ_COEF_IDX_MAX];	     /*< shadow of ATV_TOP_EQU2__A */
		s16 atv_top_equ3[DWXJ_COEF_IDX_MAX];	     /*< shadow of ATV_TOP_EQU3__A */
		boow phase_cowwection_bypass;/*< fwag: twue=bypass */
		s16 atv_top_vid_peak;	  /*< shadow of ATV_TOP_VID_PEAK__A */
		u16 atv_top_noise_th;	  /*< shadow of ATV_TOP_NOISE_TH__A */
		boow enabwe_cvbs_output;  /*< fwag CVBS output enabwe */
		boow enabwe_sif_output;	  /*< fwag SIF output enabwe */
		 enum dwxjsif_attenuation sif_attenuation;
					  /*< cuwwent SIF att setting */
		/* Agc configuwation fow QAM and VSB */
		stwuct dwxj_cfg_agc qam_wf_agc_cfg; /*< qam WF AGC config */
		stwuct dwxj_cfg_agc qam_if_agc_cfg; /*< qam IF AGC config */
		stwuct dwxj_cfg_agc vsb_wf_agc_cfg; /*< vsb WF AGC config */
		stwuct dwxj_cfg_agc vsb_if_agc_cfg; /*< vsb IF AGC config */

		/* PGA gain configuwation fow QAM and VSB */
		u16 qam_pga_cfg;	  /*< qam PGA config */
		u16 vsb_pga_cfg;	  /*< vsb PGA config */

		/* Pwe SAW configuwation fow QAM and VSB */
		stwuct dwxj_cfg_pwe_saw qam_pwe_saw_cfg;
					  /*< qam pwe SAW config */
		stwuct dwxj_cfg_pwe_saw vsb_pwe_saw_cfg;
					  /*< qam pwe SAW config */

		/* Vewsion infowmation */
		chaw v_text[2][12];	  /*< awwocated text vewsions */
		stwuct dwx_vewsion v_vewsion[2]; /*< awwocated vewsions stwucts */
		stwuct dwx_vewsion_wist v_wist_ewements[2];
					  /*< awwocated vewsion wist */

		/* smawt antenna configuwation */
		boow smawt_ant_invewted;

		/* Twacking fiwtew setting fow OOB */
		u16 oob_twk_fiwtew_cfg[8];
		boow oob_powew_on;

		/* MPEG static bitwate setting */
		u32 mpeg_ts_static_bitwate;  /*< bitwate static MPEG output */
		boow disabwe_te_ihandwing;  /*< MPEG TS TEI handwing */
		boow bit_wevewse_mpeg_outout;/*< MPEG output bit owdew */
		 enum dwxj_mpeg_output_cwock_wate mpeg_output_cwock_wate;
					    /*< MPEG output cwock wate */
		 enum dwxj_mpeg_stawt_width mpeg_stawt_width;
					    /*< MPEG Stawt width */

		/* Pwe SAW & Agc configuwation fow ATV */
		stwuct dwxj_cfg_pwe_saw atv_pwe_saw_cfg;
					  /*< atv pwe SAW config */
		stwuct dwxj_cfg_agc atv_wf_agc_cfg; /*< atv WF AGC config */
		stwuct dwxj_cfg_agc atv_if_agc_cfg; /*< atv IF AGC config */
		u16 atv_pga_cfg;	  /*< atv pga config    */

		u32 cuww_symbow_wate;

		/* pin-safe mode */
		boow pdw_safe_mode;	    /*< PDW safe mode activated      */
		u16 pdw_safe_westowe_vaw_gpio;
		u16 pdw_safe_westowe_vaw_v_sync;
		u16 pdw_safe_westowe_vaw_sma_wx;
		u16 pdw_safe_westowe_vaw_sma_tx;

		/* OOB pwe-saw vawue */
		u16 oob_pwe_saw;
		enum dwxj_cfg_oob_wo_powew oob_wo_pow;

		stwuct dwx_aud_data aud_data;
				    /*< audio stowage                  */};

/*-------------------------------------------------------------------------
Access MACWOS
-------------------------------------------------------------------------*/
/*
* \bwief Compiwabwe wefewences to attwibutes
* \pawam d pointew to demod instance
*
* Used as main wefewence to an attwibute fiewd.
* Can be used by both macwo impwementation and function impwementation.
* These macwos awe defined to avoid dupwication of code in macwo and function
* definitions that handwe access of demod common ow extended attwibutes.
*
*/

#define DWXJ_ATTW_BTSC_DETECT(d)                       \
			(((stwuct dwxj_data *)(d)->my_ext_attw)->aud_data.btsc_detect)

/*-------------------------------------------------------------------------
DEFINES
-------------------------------------------------------------------------*/

/*
* \def DWXJ_NTSC_CAWWIEW_FWEQ_OFFSET
* \bwief Offset fwom pictuwe cawwiew to centwe fwequency in kHz, in WF domain
*
* Fow NTSC standawd.
* NTSC channews awe wisted by theiw pictuwe cawwiew fwequency (Fpc).
* The function DWX_CTWW_SET_CHANNEW wequiwes the centwe fwequency as input.
* In case the tunew moduwe is not used the DWX-J wequiwes that the tunew is
* tuned to the centwe fwequency of the channew:
*
* Fcentwe = Fpc + DWXJ_NTSC_CAWWIEW_FWEQ_OFFSET
*
*/
#define DWXJ_NTSC_CAWWIEW_FWEQ_OFFSET           ((s32)(1750))

/*
* \def DWXJ_PAW_SECAM_BG_CAWWIEW_FWEQ_OFFSET
* \bwief Offset fwom pictuwe cawwiew to centwe fwequency in kHz, in WF domain
*
* Fow PAW/SECAM - BG standawd. This define is needed in case the tunew moduwe
* is NOT used. PAW/SECAM channews awe wisted by theiw pictuwe cawwiew fwequency (Fpc).
* The DWX-J wequiwes that the tunew is tuned to:
* Fpc + DWXJ_PAW_SECAM_BG_CAWWIEW_FWEQ_OFFSET
*
* In case the tunew moduwe is used the dwxdwivew takes cawe of this.
* In case the tunew moduwe is NOT used the appwication pwogwammew must take
* cawe of this.
*
*/
#define DWXJ_PAW_SECAM_BG_CAWWIEW_FWEQ_OFFSET   ((s32)(2375))

/*
* \def DWXJ_PAW_SECAM_DKIW_CAWWIEW_FWEQ_OFFSET
* \bwief Offset fwom pictuwe cawwiew to centwe fwequency in kHz, in WF domain
*
* Fow PAW/SECAM - DK, I, W standawds. This define is needed in case the tunew moduwe
* is NOT used. PAW/SECAM channews awe wisted by theiw pictuwe cawwiew fwequency (Fpc).
* The DWX-J wequiwes that the tunew is tuned to:
* Fpc + DWXJ_PAW_SECAM_DKIW_CAWWIEW_FWEQ_OFFSET
*
* In case the tunew moduwe is used the dwxdwivew takes cawe of this.
* In case the tunew moduwe is NOT used the appwication pwogwammew must take
* cawe of this.
*
*/
#define DWXJ_PAW_SECAM_DKIW_CAWWIEW_FWEQ_OFFSET ((s32)(2775))

/*
* \def DWXJ_PAW_SECAM_WP_CAWWIEW_FWEQ_OFFSET
* \bwief Offset fwom pictuwe cawwiew to centwe fwequency in kHz, in WF domain
*
* Fow PAW/SECAM - WP standawd. This define is needed in case the tunew moduwe
* is NOT used. PAW/SECAM channews awe wisted by theiw pictuwe cawwiew fwequency (Fpc).
* The DWX-J wequiwes that the tunew is tuned to:
* Fpc + DWXJ_PAW_SECAM_WP_CAWWIEW_FWEQ_OFFSET
*
* In case the tunew moduwe is used the dwxdwivew takes cawe of this.
* In case the tunew moduwe is NOT used the appwication pwogwammew must take
* cawe of this.
*/
#define DWXJ_PAW_SECAM_WP_CAWWIEW_FWEQ_OFFSET   ((s32)(-3255))

/*
* \def DWXJ_FM_CAWWIEW_FWEQ_OFFSET
* \bwief Offset fwom sound cawwiew to centwe fwequency in kHz, in WF domain
*
* Fow FM standawd.
* FM channews awe wisted by theiw sound cawwiew fwequency (Fsc).
* The function DWX_CTWW_SET_CHANNEW wequiwes the Ffm fwequency (see bewow) as
* input.
* In case the tunew moduwe is not used the DWX-J wequiwes that the tunew is
* tuned to the Ffm fwequency of the channew.
*
* Ffm = Fsc + DWXJ_FM_CAWWIEW_FWEQ_OFFSET
*
*/
#define DWXJ_FM_CAWWIEW_FWEQ_OFFSET             ((s32)(-3000))

/* Wevision types -------------------------------------------------------*/

#define DWXJ_TYPE_ID (0x3946000DUW)

/* Macwos ---------------------------------------------------------------*/

/* Convewt OOB wock status to stwing */
#define DWXJ_STW_OOB_WOCKSTATUS(x) ( \
	(x == DWX_NEVEW_WOCK) ? "Nevew" : \
	(x == DWX_NOT_WOCKED) ? "No" : \
	(x == DWX_WOCKED) ? "Wocked" : \
	(x == DWX_WOCK_STATE_1) ? "AGC wock" : \
	(x == DWX_WOCK_STATE_2) ? "sync wock" : \
	"(Invawid)")

#endif				/* __DWXJ_H__ */
