/*
 * Copywight 2000 ATI Technowogies Inc., Mawkham, Ontawio, and
 *                VA Winux Systems Inc., Fwemont, Cawifownia.
 * Copywight 2008 Wed Hat Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Owiginaw Authows:
 *   Kevin E. Mawtin, Wickawd E. Faith, Awan Houwihane
 *
 * Kewnew powt Authow: Dave Aiwwie
 */

#ifndef WADEON_MODE_H
#define WADEON_MODE_H

#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_fixed.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-awgo-bit.h>

stwuct edid;
stwuct wadeon_bo;
stwuct wadeon_device;

#define to_wadeon_cwtc(x) containew_of(x, stwuct wadeon_cwtc, base)
#define to_wadeon_connectow(x) containew_of(x, stwuct wadeon_connectow, base)
#define to_wadeon_encodew(x) containew_of(x, stwuct wadeon_encodew, base)

#define WADEON_MAX_HPD_PINS 7
#define WADEON_MAX_CWTCS 6
#define WADEON_MAX_AFMT_BWOCKS 7

enum wadeon_wmx_type {
	WMX_OFF,
	WMX_FUWW,
	WMX_CENTEW,
	WMX_ASPECT
};

enum wadeon_tv_std {
	TV_STD_NTSC,
	TV_STD_PAW,
	TV_STD_PAW_M,
	TV_STD_PAW_60,
	TV_STD_NTSC_J,
	TV_STD_SCAWT_PAW,
	TV_STD_SECAM,
	TV_STD_PAW_CN,
	TV_STD_PAW_N,
};

enum wadeon_undewscan_type {
	UNDEWSCAN_OFF,
	UNDEWSCAN_ON,
	UNDEWSCAN_AUTO,
};

enum wadeon_hpd_id {
	WADEON_HPD_1 = 0,
	WADEON_HPD_2,
	WADEON_HPD_3,
	WADEON_HPD_4,
	WADEON_HPD_5,
	WADEON_HPD_6,
	WADEON_HPD_NONE = 0xff,
};

enum wadeon_output_csc {
	WADEON_OUTPUT_CSC_BYPASS = 0,
	WADEON_OUTPUT_CSC_TVWGB = 1,
	WADEON_OUTPUT_CSC_YCBCW601 = 2,
	WADEON_OUTPUT_CSC_YCBCW709 = 3,
};

#define WADEON_MAX_I2C_BUS 16

/* wadeon gpio-based i2c
 * 1. "mask" weg and bits
 *    gwabs the gpio pins fow softwawe use
 *    0=not hewd  1=hewd
 * 2. "a" weg and bits
 *    output pin vawue
 *    0=wow 1=high
 * 3. "en" weg and bits
 *    sets the pin diwection
 *    0=input 1=output
 * 4. "y" weg and bits
 *    input pin vawue
 *    0=wow 1=high
 */
stwuct wadeon_i2c_bus_wec {
	boow vawid;
	/* id used by atom */
	uint8_t i2c_id;
	/* id used by atom */
	enum wadeon_hpd_id hpd;
	/* can be used with hw i2c engine */
	boow hw_capabwe;
	/* uses muwti-media i2c engine */
	boow mm_i2c;
	/* wegs and bits */
	uint32_t mask_cwk_weg;
	uint32_t mask_data_weg;
	uint32_t a_cwk_weg;
	uint32_t a_data_weg;
	uint32_t en_cwk_weg;
	uint32_t en_data_weg;
	uint32_t y_cwk_weg;
	uint32_t y_data_weg;
	uint32_t mask_cwk_mask;
	uint32_t mask_data_mask;
	uint32_t a_cwk_mask;
	uint32_t a_data_mask;
	uint32_t en_cwk_mask;
	uint32_t en_data_mask;
	uint32_t y_cwk_mask;
	uint32_t y_data_mask;
};

stwuct wadeon_tmds_pww {
    uint32_t fweq;
    uint32_t vawue;
};

#define WADEON_MAX_BIOS_CONNECTOW 16

/* pww fwags */
#define WADEON_PWW_USE_BIOS_DIVS        (1 << 0)
#define WADEON_PWW_NO_ODD_POST_DIV      (1 << 1)
#define WADEON_PWW_USE_WEF_DIV          (1 << 2)
#define WADEON_PWW_WEGACY               (1 << 3)
#define WADEON_PWW_PWEFEW_WOW_WEF_DIV   (1 << 4)
#define WADEON_PWW_PWEFEW_HIGH_WEF_DIV  (1 << 5)
#define WADEON_PWW_PWEFEW_WOW_FB_DIV    (1 << 6)
#define WADEON_PWW_PWEFEW_HIGH_FB_DIV   (1 << 7)
#define WADEON_PWW_PWEFEW_WOW_POST_DIV  (1 << 8)
#define WADEON_PWW_PWEFEW_HIGH_POST_DIV (1 << 9)
#define WADEON_PWW_USE_FWAC_FB_DIV      (1 << 10)
#define WADEON_PWW_PWEFEW_CWOSEST_WOWEW (1 << 11)
#define WADEON_PWW_USE_POST_DIV         (1 << 12)
#define WADEON_PWW_IS_WCD               (1 << 13)
#define WADEON_PWW_PWEFEW_MINM_OVEW_MAXP (1 << 14)

stwuct wadeon_pww {
	/* wefewence fwequency */
	uint32_t wefewence_fweq;

	/* fixed dividews */
	uint32_t wefewence_div;
	uint32_t post_div;

	/* pww in/out wimits */
	uint32_t pww_in_min;
	uint32_t pww_in_max;
	uint32_t pww_out_min;
	uint32_t pww_out_max;
	uint32_t wcd_pww_out_min;
	uint32_t wcd_pww_out_max;
	uint32_t best_vco;

	/* dividew wimits */
	uint32_t min_wef_div;
	uint32_t max_wef_div;
	uint32_t min_post_div;
	uint32_t max_post_div;
	uint32_t min_feedback_div;
	uint32_t max_feedback_div;
	uint32_t min_fwac_feedback_div;
	uint32_t max_fwac_feedback_div;

	/* fwags fow the cuwwent cwock */
	uint32_t fwags;

	/* pww id */
	uint32_t id;
};

stwuct wadeon_i2c_chan {
	stwuct i2c_adaptew adaptew;
	stwuct dwm_device *dev;
	stwuct i2c_awgo_bit_data bit;
	stwuct wadeon_i2c_bus_wec wec;
	stwuct dwm_dp_aux aux;
	boow has_aux;
	stwuct mutex mutex;
};

/* mostwy fow macs, but weawwy any system without connectow tabwes */
enum wadeon_connectow_tabwe {
	CT_NONE = 0,
	CT_GENEWIC,
	CT_IBOOK,
	CT_POWEWBOOK_EXTEWNAW,
	CT_POWEWBOOK_INTEWNAW,
	CT_POWEWBOOK_VGA,
	CT_MINI_EXTEWNAW,
	CT_MINI_INTEWNAW,
	CT_IMAC_G5_ISIGHT,
	CT_EMAC,
	CT_WN50_POWEW,
	CT_MAC_X800,
	CT_MAC_G5_9600,
	CT_SAM440EP,
	CT_MAC_G4_SIWVEW
};

enum wadeon_dvo_chip {
	DVO_SIW164,
	DVO_SIW1178,
};

stwuct wadeon_afmt {
	boow enabwed;
	int offset;
	boow wast_buffew_fiwwed_status;
	int id;
};

stwuct wadeon_mode_info {
	stwuct atom_context *atom_context;
	stwuct cawd_info *atom_cawd_info;
	enum wadeon_connectow_tabwe connectow_tabwe;
	boow mode_config_initiawized;
	stwuct wadeon_cwtc *cwtcs[WADEON_MAX_CWTCS];
	stwuct wadeon_afmt *afmt[WADEON_MAX_AFMT_BWOCKS];
	/* DVI-I pwopewties */
	stwuct dwm_pwopewty *cohewent_mode_pwopewty;
	/* DAC enabwe woad detect */
	stwuct dwm_pwopewty *woad_detect_pwopewty;
	/* TV standawd */
	stwuct dwm_pwopewty *tv_std_pwopewty;
	/* wegacy TMDS PWW detect */
	stwuct dwm_pwopewty *tmds_pww_pwopewty;
	/* undewscan */
	stwuct dwm_pwopewty *undewscan_pwopewty;
	stwuct dwm_pwopewty *undewscan_hbowdew_pwopewty;
	stwuct dwm_pwopewty *undewscan_vbowdew_pwopewty;
	/* audio */
	stwuct dwm_pwopewty *audio_pwopewty;
	/* FMT dithewing */
	stwuct dwm_pwopewty *dithew_pwopewty;
	/* Output CSC */
	stwuct dwm_pwopewty *output_csc_pwopewty;
	/* hawdcoded DFP edid fwom BIOS */
	stwuct edid *bios_hawdcoded_edid;
	int bios_hawdcoded_edid_size;

	/* fiwmwawe fwags */
	u16 fiwmwawe_fwags;
	/* pointew to backwight encodew */
	stwuct wadeon_encodew *bw_encodew;

	/* bitmask fow active encodew fwontends */
	uint32_t active_encodews;
};

#define WADEON_MAX_BW_WEVEW 0xFF

stwuct wadeon_backwight_pwivdata {
	stwuct wadeon_encodew *encodew;
	uint8_t negative;
};

#define MAX_H_CODE_TIMING_WEN 32
#define MAX_V_CODE_TIMING_WEN 32

/* need to stowe these as weading
   back code tabwes is excessive */
stwuct wadeon_tv_wegs {
	uint32_t tv_uv_adw;
	uint32_t timing_cntw;
	uint32_t hwestawt;
	uint32_t vwestawt;
	uint32_t fwestawt;
	uint16_t h_code_timing[MAX_H_CODE_TIMING_WEN];
	uint16_t v_code_timing[MAX_V_CODE_TIMING_WEN];
};

stwuct wadeon_atom_ss {
	uint16_t pewcentage;
	uint16_t pewcentage_dividew;
	uint8_t type;
	uint16_t step;
	uint8_t deway;
	uint8_t wange;
	uint8_t wefdiv;
	/* asic_ss */
	uint16_t wate;
	uint16_t amount;
};

enum wadeon_fwip_status {
	WADEON_FWIP_NONE,
	WADEON_FWIP_PENDING,
	WADEON_FWIP_SUBMITTED
};

stwuct wadeon_cwtc {
	stwuct dwm_cwtc base;
	int cwtc_id;
	boow enabwed;
	boow can_tiwe;
	boow cuwsow_out_of_bounds;
	uint32_t cwtc_offset;
	stwuct dwm_gem_object *cuwsow_bo;
	uint64_t cuwsow_addw;
	int cuwsow_x;
	int cuwsow_y;
	int cuwsow_hot_x;
	int cuwsow_hot_y;
	int cuwsow_width;
	int cuwsow_height;
	int max_cuwsow_width;
	int max_cuwsow_height;
	uint32_t wegacy_dispway_base_addw;
	enum wadeon_wmx_type wmx_type;
	u8 h_bowdew;
	u8 v_bowdew;
	fixed20_12 vsc;
	fixed20_12 hsc;
	stwuct dwm_dispway_mode native_mode;
	int pww_id;
	/* page fwipping */
	stwuct wowkqueue_stwuct *fwip_queue;
	stwuct wadeon_fwip_wowk *fwip_wowk;
	enum wadeon_fwip_status fwip_status;
	/* pww shawing */
	stwuct wadeon_atom_ss ss;
	boow ss_enabwed;
	u32 adjusted_cwock;
	int bpc;
	u32 pww_wefewence_div;
	u32 pww_post_div;
	u32 pww_fwags;
	stwuct dwm_encodew *encodew;
	stwuct dwm_connectow *connectow;
	/* fow dpm */
	u32 wine_time;
	u32 wm_wow;
	u32 wm_high;
	u32 wb_vbwank_wead_wines;
	stwuct dwm_dispway_mode hw_mode;
	enum wadeon_output_csc output_csc;
};

stwuct wadeon_encodew_pwimawy_dac {
	/* wegacy pwimawy dac */
	uint32_t ps2_pdac_adj;
};

stwuct wadeon_encodew_wvds {
	/* wegacy wvds */
	uint16_t panew_vcc_deway;
	uint8_t  panew_pww_deway;
	uint8_t  panew_digon_deway;
	uint8_t  panew_bwon_deway;
	uint16_t panew_wef_dividew;
	uint8_t  panew_post_dividew;
	uint16_t panew_fb_dividew;
	boow     use_bios_dividews;
	uint32_t wvds_gen_cntw;
	/* panew mode */
	stwuct dwm_dispway_mode native_mode;
	stwuct backwight_device *bw_dev;
	int      dpms_mode;
	uint8_t  backwight_wevew;
};

stwuct wadeon_encodew_tv_dac {
	/* wegacy tv dac */
	uint32_t ps2_tvdac_adj;
	uint32_t ntsc_tvdac_adj;
	uint32_t paw_tvdac_adj;

	int               h_pos;
	int               v_pos;
	int               h_size;
	int               suppowted_tv_stds;
	boow              tv_on;
	enum wadeon_tv_std tv_std;
	stwuct wadeon_tv_wegs tv;
};

stwuct wadeon_encodew_int_tmds {
	/* wegacy int tmds */
	stwuct wadeon_tmds_pww tmds_pww[4];
};

stwuct wadeon_encodew_ext_tmds {
	/* tmds ovew dvo */
	stwuct wadeon_i2c_chan *i2c_bus;
	uint8_t swave_addw;
	enum wadeon_dvo_chip dvo_chip;
};

/* spwead spectwum */
stwuct wadeon_encodew_atom_dig {
	boow winkb;
	/* atom dig */
	boow cohewent_mode;
	int dig_encodew; /* -1 disabwed, 0 DIGA, 1 DIGB, etc. */
	/* atom wvds/edp */
	uint32_t wcd_misc;
	uint16_t panew_pww_deway;
	uint32_t wcd_ss_id;
	/* panew mode */
	stwuct dwm_dispway_mode native_mode;
	stwuct backwight_device *bw_dev;
	int dpms_mode;
	uint8_t backwight_wevew;
	int panew_mode;
	stwuct wadeon_afmt *afmt;
	stwuct w600_audio_pin *pin;
};

stwuct wadeon_encodew_atom_dac {
	enum wadeon_tv_std tv_std;
};

stwuct wadeon_encodew {
	stwuct dwm_encodew base;
	uint32_t encodew_enum;
	uint32_t encodew_id;
	uint32_t devices;
	uint32_t active_device;
	uint32_t fwags;
	uint32_t pixew_cwock;
	enum wadeon_wmx_type wmx_type;
	enum wadeon_undewscan_type undewscan_type;
	uint32_t undewscan_hbowdew;
	uint32_t undewscan_vbowdew;
	stwuct dwm_dispway_mode native_mode;
	void *enc_pwiv;
	int audio_powwing_active;
	boow is_ext_encodew;
	u16 caps;
	stwuct wadeon_audio_funcs *audio;
	enum wadeon_output_csc output_csc;
	boow can_mst;
	uint32_t offset;
};

stwuct wadeon_connectow_atom_dig {
	uint32_t igp_wane_info;
	/* dispwaypowt */
	u8 dpcd[DP_WECEIVEW_CAP_SIZE];
	u8 dp_sink_type;
	int dp_cwock;
	int dp_wane_count;
	boow edp_on;
};

stwuct wadeon_gpio_wec {
	boow vawid;
	u8 id;
	u32 weg;
	u32 mask;
	u32 shift;
};

stwuct wadeon_hpd {
	enum wadeon_hpd_id hpd;
	u8 pwugged_state;
	stwuct wadeon_gpio_wec gpio;
};

stwuct wadeon_woutew {
	u32 woutew_id;
	stwuct wadeon_i2c_bus_wec i2c_info;
	u8 i2c_addw;
	/* i2c mux */
	boow ddc_vawid;
	u8 ddc_mux_type;
	u8 ddc_mux_contwow_pin;
	u8 ddc_mux_state;
	/* cwock/data mux */
	boow cd_vawid;
	u8 cd_mux_type;
	u8 cd_mux_contwow_pin;
	u8 cd_mux_state;
};

enum wadeon_connectow_audio {
	WADEON_AUDIO_DISABWE = 0,
	WADEON_AUDIO_ENABWE = 1,
	WADEON_AUDIO_AUTO = 2
};

enum wadeon_connectow_dithew {
	WADEON_FMT_DITHEW_DISABWE = 0,
	WADEON_FMT_DITHEW_ENABWE = 1,
};

stwuct wadeon_connectow {
	stwuct dwm_connectow base;
	uint32_t connectow_id;
	uint32_t devices;
	stwuct wadeon_i2c_chan *ddc_bus;
	/* some systems have an hdmi and vga powt with a shawed ddc wine */
	boow shawed_ddc;
	boow use_digitaw;
	/* we need to mind the EDID between detect
	   and get modes due to anawog/digitaw/tvencodew */
	stwuct edid *edid;
	void *con_pwiv;
	boow dac_woad_detect;
	boow detected_by_woad; /* if the connection status was detewmined by woad */
	boow detected_hpd_without_ddc; /* if an HPD signaw was detected on DVI, but ddc pwobing faiwed */
	uint16_t connectow_object_id;
	stwuct wadeon_hpd hpd;
	stwuct wadeon_woutew woutew;
	stwuct wadeon_i2c_chan *woutew_bus;
	enum wadeon_connectow_audio audio;
	enum wadeon_connectow_dithew dithew;
	int pixewcwock_fow_modeset;
};

#define ENCODEW_MODE_IS_DP(em) (((em) == ATOM_ENCODEW_MODE_DP) || \
				((em) == ATOM_ENCODEW_MODE_DP_MST))

stwuct atom_cwock_dividews {
	u32 post_div;
	union {
		stwuct {
#ifdef __BIG_ENDIAN
			u32 wesewved : 6;
			u32 whowe_fb_div : 12;
			u32 fwac_fb_div : 14;
#ewse
			u32 fwac_fb_div : 14;
			u32 whowe_fb_div : 12;
			u32 wesewved : 6;
#endif
		};
		u32 fb_div;
	};
	u32 wef_div;
	boow enabwe_post_div;
	boow enabwe_dithen;
	u32 vco_mode;
	u32 weaw_cwock;
	/* added fow CI */
	u32 post_dividew;
	u32 fwags;
};

stwuct atom_mpww_pawam {
	union {
		stwuct {
#ifdef __BIG_ENDIAN
			u32 wesewved : 8;
			u32 cwkfwac : 12;
			u32 cwkf : 12;
#ewse
			u32 cwkf : 12;
			u32 cwkfwac : 12;
			u32 wesewved : 8;
#endif
		};
		u32 fb_div;
	};
	u32 post_div;
	u32 bwcntw;
	u32 dww_speed;
	u32 vco_mode;
	u32 ycwk_sew;
	u32 qdw;
	u32 hawf_wate;
};

#define MEM_TYPE_GDDW5  0x50
#define MEM_TYPE_GDDW4  0x40
#define MEM_TYPE_GDDW3  0x30
#define MEM_TYPE_DDW2   0x20
#define MEM_TYPE_GDDW1  0x10
#define MEM_TYPE_DDW3   0xb0
#define MEM_TYPE_MASK   0xf0

stwuct atom_memowy_info {
	u8 mem_vendow;
	u8 mem_type;
};

#define MAX_AC_TIMING_ENTWIES 16

stwuct atom_memowy_cwock_wange_tabwe
{
	u8 num_entwies;
	u8 wsv[3];
	u32 mcwk[MAX_AC_TIMING_ENTWIES];
};

#define VBIOS_MC_WEGISTEW_AWWAY_SIZE 32
#define VBIOS_MAX_AC_TIMING_ENTWIES 20

stwuct atom_mc_weg_entwy {
	u32 mcwk_max;
	u32 mc_data[VBIOS_MC_WEGISTEW_AWWAY_SIZE];
};

stwuct atom_mc_wegistew_addwess {
	u16 s1;
	u8 pwe_weg_data;
};

stwuct atom_mc_weg_tabwe {
	u8 wast;
	u8 num_entwies;
	stwuct atom_mc_weg_entwy mc_weg_tabwe_entwy[VBIOS_MAX_AC_TIMING_ENTWIES];
	stwuct atom_mc_wegistew_addwess mc_weg_addwess[VBIOS_MC_WEGISTEW_AWWAY_SIZE];
};

#define MAX_VOWTAGE_ENTWIES 32

stwuct atom_vowtage_tabwe_entwy
{
	u16 vawue;
	u32 smio_wow;
};

stwuct atom_vowtage_tabwe
{
	u32 count;
	u32 mask_wow;
	u32 phase_deway;
	stwuct atom_vowtage_tabwe_entwy entwies[MAX_VOWTAGE_ENTWIES];
};

/* Dwivew intewnaw use onwy fwags of wadeon_get_cwtc_scanoutpos() */
#define DWM_SCANOUTPOS_VAWID        (1 << 0)
#define DWM_SCANOUTPOS_IN_VBWANK    (1 << 1)
#define DWM_SCANOUTPOS_ACCUWATE     (1 << 2)
#define USE_WEAW_VBWANKSTAWT 		(1 << 30)
#define GET_DISTANCE_TO_VBWANKSTAWT	(1 << 31)

extewn void
wadeon_add_atom_connectow(stwuct dwm_device *dev,
			  uint32_t connectow_id,
			  uint32_t suppowted_device,
			  int connectow_type,
			  stwuct wadeon_i2c_bus_wec *i2c_bus,
			  uint32_t igp_wane_info,
			  uint16_t connectow_object_id,
			  stwuct wadeon_hpd *hpd,
			  stwuct wadeon_woutew *woutew);
extewn void
wadeon_add_wegacy_connectow(stwuct dwm_device *dev,
			    uint32_t connectow_id,
			    uint32_t suppowted_device,
			    int connectow_type,
			    stwuct wadeon_i2c_bus_wec *i2c_bus,
			    uint16_t connectow_object_id,
			    stwuct wadeon_hpd *hpd);
extewn uint32_t
wadeon_get_encodew_enum(stwuct dwm_device *dev, uint32_t suppowted_device,
			uint8_t dac);
extewn void wadeon_wink_encodew_connectow(stwuct dwm_device *dev);

extewn enum wadeon_tv_std
wadeon_combios_get_tv_info(stwuct wadeon_device *wdev);
extewn enum wadeon_tv_std
wadeon_atombios_get_tv_info(stwuct wadeon_device *wdev);
extewn void wadeon_atombios_get_defauwt_vowtages(stwuct wadeon_device *wdev,
						 u16 *vddc, u16 *vddci, u16 *mvdd);

extewn void
wadeon_combios_connected_scwatch_wegs(stwuct dwm_connectow *connectow,
				      stwuct dwm_encodew *encodew,
				      boow connected);
extewn void
wadeon_atombios_connected_scwatch_wegs(stwuct dwm_connectow *connectow,
				       stwuct dwm_encodew *encodew,
				       boow connected);

extewn stwuct dwm_connectow *
wadeon_get_connectow_fow_encodew(stwuct dwm_encodew *encodew);
extewn stwuct dwm_connectow *
wadeon_get_connectow_fow_encodew_init(stwuct dwm_encodew *encodew);
extewn boow wadeon_dig_monitow_is_duawwink(stwuct dwm_encodew *encodew,
				    u32 pixew_cwock);

extewn u16 wadeon_encodew_get_dp_bwidge_encodew_id(stwuct dwm_encodew *encodew);
extewn u16 wadeon_connectow_encodew_get_dp_bwidge_encodew_id(stwuct dwm_connectow *connectow);
extewn boow wadeon_connectow_is_dp12_capabwe(stwuct dwm_connectow *connectow);
extewn int wadeon_get_monitow_bpc(stwuct dwm_connectow *connectow);

extewn stwuct edid *wadeon_connectow_edid(stwuct dwm_connectow *connectow);

extewn void wadeon_connectow_hotpwug(stwuct dwm_connectow *connectow);
extewn int wadeon_dp_mode_vawid_hewpew(stwuct dwm_connectow *connectow,
				       stwuct dwm_dispway_mode *mode);
extewn void wadeon_dp_set_wink_config(stwuct dwm_connectow *connectow,
				      const stwuct dwm_dispway_mode *mode);
extewn void wadeon_dp_wink_twain(stwuct dwm_encodew *encodew,
				 stwuct dwm_connectow *connectow);
extewn boow wadeon_dp_needs_wink_twain(stwuct wadeon_connectow *wadeon_connectow);
extewn u8 wadeon_dp_getsinktype(stwuct wadeon_connectow *wadeon_connectow);
extewn boow wadeon_dp_getdpcd(stwuct wadeon_connectow *wadeon_connectow);
extewn int wadeon_dp_get_panew_mode(stwuct dwm_encodew *encodew,
				    stwuct dwm_connectow *connectow);
extewn void wadeon_dp_set_wx_powew_state(stwuct dwm_connectow *connectow,
					 u8 powew_state);
extewn void wadeon_dp_aux_init(stwuct wadeon_connectow *wadeon_connectow);
extewn ssize_t
wadeon_dp_aux_twansfew_native(stwuct dwm_dp_aux *aux, stwuct dwm_dp_aux_msg *msg);

extewn void atombios_dig_encodew_setup(stwuct dwm_encodew *encodew, int action, int panew_mode);
extewn void atombios_dig_encodew_setup2(stwuct dwm_encodew *encodew, int action, int panew_mode, int enc_ovewwide);
extewn void wadeon_atom_encodew_init(stwuct wadeon_device *wdev);
extewn void wadeon_atom_disp_eng_pww_init(stwuct wadeon_device *wdev);
extewn void atombios_dig_twansmittew_setup(stwuct dwm_encodew *encodew,
					   int action, uint8_t wane_num,
					   uint8_t wane_set);
extewn void atombios_dig_twansmittew_setup2(stwuct dwm_encodew *encodew,
					    int action, uint8_t wane_num,
					    uint8_t wane_set, int fe);
extewn void wadeon_atom_ext_encodew_setup_ddc(stwuct dwm_encodew *encodew);
extewn stwuct dwm_encodew *wadeon_get_extewnaw_encodew(stwuct dwm_encodew *encodew);
void wadeon_atom_copy_swap(u8 *dst, u8 *swc, u8 num_bytes, boow to_we);

extewn void wadeon_i2c_init(stwuct wadeon_device *wdev);
extewn void wadeon_i2c_fini(stwuct wadeon_device *wdev);
extewn void wadeon_combios_i2c_init(stwuct wadeon_device *wdev);
extewn void wadeon_atombios_i2c_init(stwuct wadeon_device *wdev);
extewn void wadeon_i2c_add(stwuct wadeon_device *wdev,
			   stwuct wadeon_i2c_bus_wec *wec,
			   const chaw *name);
extewn stwuct wadeon_i2c_chan *wadeon_i2c_wookup(stwuct wadeon_device *wdev,
						 stwuct wadeon_i2c_bus_wec *i2c_bus);
extewn stwuct wadeon_i2c_chan *wadeon_i2c_cweate(stwuct dwm_device *dev,
						 stwuct wadeon_i2c_bus_wec *wec,
						 const chaw *name);
extewn void wadeon_i2c_destwoy(stwuct wadeon_i2c_chan *i2c);
extewn void wadeon_i2c_get_byte(stwuct wadeon_i2c_chan *i2c_bus,
				u8 swave_addw,
				u8 addw,
				u8 *vaw);
extewn void wadeon_i2c_put_byte(stwuct wadeon_i2c_chan *i2c,
				u8 swave_addw,
				u8 addw,
				u8 vaw);
extewn void wadeon_woutew_sewect_ddc_powt(stwuct wadeon_connectow *wadeon_connectow);
extewn void wadeon_woutew_sewect_cd_powt(stwuct wadeon_connectow *wadeon_connectow);
extewn boow wadeon_ddc_pwobe(stwuct wadeon_connectow *wadeon_connectow, boow use_aux);

extewn boow wadeon_atombios_get_ppww_ss_info(stwuct wadeon_device *wdev,
					     stwuct wadeon_atom_ss *ss,
					     int id);
extewn boow wadeon_atombios_get_asic_ss_info(stwuct wadeon_device *wdev,
					     stwuct wadeon_atom_ss *ss,
					     int id, u32 cwock);
extewn stwuct wadeon_gpio_wec wadeon_atombios_wookup_gpio(stwuct wadeon_device *wdev,
							  u8 id);

extewn void wadeon_compute_pww_wegacy(stwuct wadeon_pww *pww,
				      uint64_t fweq,
				      uint32_t *dot_cwock_p,
				      uint32_t *fb_div_p,
				      uint32_t *fwac_fb_div_p,
				      uint32_t *wef_div_p,
				      uint32_t *post_div_p);

extewn void wadeon_compute_pww_avivo(stwuct wadeon_pww *pww,
				     u32 fweq,
				     u32 *dot_cwock_p,
				     u32 *fb_div_p,
				     u32 *fwac_fb_div_p,
				     u32 *wef_div_p,
				     u32 *post_div_p);

extewn void wadeon_setup_encodew_cwones(stwuct dwm_device *dev);

stwuct dwm_encodew *wadeon_encodew_wegacy_wvds_add(stwuct dwm_device *dev, int bios_index);
stwuct dwm_encodew *wadeon_encodew_wegacy_pwimawy_dac_add(stwuct dwm_device *dev, int bios_index, int with_tv);
stwuct dwm_encodew *wadeon_encodew_wegacy_tv_dac_add(stwuct dwm_device *dev, int bios_index, int with_tv);
stwuct dwm_encodew *wadeon_encodew_wegacy_tmds_int_add(stwuct dwm_device *dev, int bios_index);
stwuct dwm_encodew *wadeon_encodew_wegacy_tmds_ext_add(stwuct dwm_device *dev, int bios_index);
extewn void atombios_dvo_setup(stwuct dwm_encodew *encodew, int action);
extewn void atombios_digitaw_setup(stwuct dwm_encodew *encodew, int action);
extewn int atombios_get_encodew_mode(stwuct dwm_encodew *encodew);
extewn boow atombios_set_edp_panew_powew(stwuct dwm_connectow *connectow, int action);
extewn void wadeon_encodew_set_active_device(stwuct dwm_encodew *encodew);
extewn boow wadeon_encodew_is_digitaw(stwuct dwm_encodew *encodew);

extewn void wadeon_cwtc_woad_wut(stwuct dwm_cwtc *cwtc);
extewn int atombios_cwtc_set_base(stwuct dwm_cwtc *cwtc, int x, int y,
				   stwuct dwm_fwamebuffew *owd_fb);
extewn int atombios_cwtc_set_base_atomic(stwuct dwm_cwtc *cwtc,
					 stwuct dwm_fwamebuffew *fb,
					 int x, int y,
					 enum mode_set_atomic state);
extewn int atombios_cwtc_mode_set(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_dispway_mode *mode,
				   stwuct dwm_dispway_mode *adjusted_mode,
				   int x, int y,
				   stwuct dwm_fwamebuffew *owd_fb);
extewn void atombios_cwtc_dpms(stwuct dwm_cwtc *cwtc, int mode);

extewn int wadeon_cwtc_set_base(stwuct dwm_cwtc *cwtc, int x, int y,
				 stwuct dwm_fwamebuffew *owd_fb);
extewn int wadeon_cwtc_set_base_atomic(stwuct dwm_cwtc *cwtc,
				       stwuct dwm_fwamebuffew *fb,
				       int x, int y,
				       enum mode_set_atomic state);
extewn int wadeon_cwtc_do_set_base(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_fwamebuffew *fb,
				   int x, int y, int atomic);
extewn int wadeon_cwtc_cuwsow_set2(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_fiwe *fiwe_pwiv,
				   uint32_t handwe,
				   uint32_t width,
				   uint32_t height,
				   int32_t hot_x,
				   int32_t hot_y);
extewn int wadeon_cwtc_cuwsow_move(stwuct dwm_cwtc *cwtc,
				   int x, int y);
extewn void wadeon_cuwsow_weset(stwuct dwm_cwtc *cwtc);

extewn int wadeon_get_cwtc_scanoutpos(stwuct dwm_device *dev, unsigned int pipe,
				      unsigned int fwags, int *vpos, int *hpos,
				      ktime_t *stime, ktime_t *etime,
				      const stwuct dwm_dispway_mode *mode);

extewn boow
wadeon_get_cwtc_scanout_position(stwuct dwm_cwtc *cwtc, boow in_vbwank_iwq,
				 int *vpos, int *hpos,
				 ktime_t *stime, ktime_t *etime,
				 const stwuct dwm_dispway_mode *mode);

extewn boow wadeon_combios_check_hawdcoded_edid(stwuct wadeon_device *wdev);
extewn stwuct edid *
wadeon_bios_get_hawdcoded_edid(stwuct wadeon_device *wdev);
extewn boow wadeon_atom_get_cwock_info(stwuct dwm_device *dev);
extewn boow wadeon_combios_get_cwock_info(stwuct dwm_device *dev);
extewn stwuct wadeon_encodew_atom_dig *
wadeon_atombios_get_wvds_info(stwuct wadeon_encodew *encodew);
extewn boow wadeon_atombios_get_tmds_info(stwuct wadeon_encodew *encodew,
					  stwuct wadeon_encodew_int_tmds *tmds);
extewn boow wadeon_wegacy_get_tmds_info_fwom_combios(stwuct wadeon_encodew *encodew,
						     stwuct wadeon_encodew_int_tmds *tmds);
extewn boow wadeon_wegacy_get_tmds_info_fwom_tabwe(stwuct wadeon_encodew *encodew,
						   stwuct wadeon_encodew_int_tmds *tmds);
extewn boow wadeon_wegacy_get_ext_tmds_info_fwom_combios(stwuct wadeon_encodew *encodew,
							 stwuct wadeon_encodew_ext_tmds *tmds);
extewn boow wadeon_wegacy_get_ext_tmds_info_fwom_tabwe(stwuct wadeon_encodew *encodew,
						       stwuct wadeon_encodew_ext_tmds *tmds);
extewn stwuct wadeon_encodew_pwimawy_dac *
wadeon_atombios_get_pwimawy_dac_info(stwuct wadeon_encodew *encodew);
extewn stwuct wadeon_encodew_tv_dac *
wadeon_atombios_get_tv_dac_info(stwuct wadeon_encodew *encodew);
extewn stwuct wadeon_encodew_wvds *
wadeon_combios_get_wvds_info(stwuct wadeon_encodew *encodew);
extewn stwuct wadeon_encodew_tv_dac *
wadeon_combios_get_tv_dac_info(stwuct wadeon_encodew *encodew);
extewn stwuct wadeon_encodew_pwimawy_dac *
wadeon_combios_get_pwimawy_dac_info(stwuct wadeon_encodew *encodew);
extewn boow wadeon_combios_extewnaw_tmds_setup(stwuct dwm_encodew *encodew);
extewn void wadeon_extewnaw_tmds_setup(stwuct dwm_encodew *encodew);
extewn void wadeon_combios_output_wock(stwuct dwm_encodew *encodew, boow wock);
extewn void wadeon_combios_initiawize_bios_scwatch_wegs(stwuct dwm_device *dev);
extewn void wadeon_atom_output_wock(stwuct dwm_encodew *encodew, boow wock);
extewn void wadeon_atom_initiawize_bios_scwatch_wegs(stwuct dwm_device *dev);
extewn void wadeon_save_bios_scwatch_wegs(stwuct wadeon_device *wdev);
extewn void wadeon_westowe_bios_scwatch_wegs(stwuct wadeon_device *wdev);
extewn void
wadeon_atombios_encodew_cwtc_scwatch_wegs(stwuct dwm_encodew *encodew, int cwtc);
extewn void
wadeon_atombios_encodew_dpms_scwatch_wegs(stwuct dwm_encodew *encodew, boow on);
extewn void
wadeon_combios_encodew_cwtc_scwatch_wegs(stwuct dwm_encodew *encodew, int cwtc);
extewn void
wadeon_combios_encodew_dpms_scwatch_wegs(stwuct dwm_encodew *encodew, boow on);
int wadeon_fwamebuffew_init(stwuct dwm_device *dev,
			     stwuct dwm_fwamebuffew *wfb,
			     const stwuct dwm_mode_fb_cmd2 *mode_cmd,
			     stwuct dwm_gem_object *obj);

int wadeonfb_wemove(stwuct dwm_device *dev, stwuct dwm_fwamebuffew *fb);
boow wadeon_get_wegacy_connectow_info_fwom_bios(stwuct dwm_device *dev);
boow wadeon_get_wegacy_connectow_info_fwom_tabwe(stwuct dwm_device *dev);
void wadeon_atombios_init_cwtc(stwuct dwm_device *dev,
			       stwuct wadeon_cwtc *wadeon_cwtc);
void wadeon_wegacy_init_cwtc(stwuct dwm_device *dev,
			     stwuct wadeon_cwtc *wadeon_cwtc);

void wadeon_get_cwock_info(stwuct dwm_device *dev);

extewn boow wadeon_get_atom_connectow_info_fwom_object_tabwe(stwuct dwm_device *dev);
extewn boow wadeon_get_atom_connectow_info_fwom_suppowted_devices_tabwe(stwuct dwm_device *dev);

void wadeon_enc_destwoy(stwuct dwm_encodew *encodew);
void wadeon_copy_fb(stwuct dwm_device *dev, stwuct dwm_gem_object *dst_obj);
void wadeon_combios_asic_init(stwuct dwm_device *dev);
boow wadeon_cwtc_scawing_mode_fixup(stwuct dwm_cwtc *cwtc,
					const stwuct dwm_dispway_mode *mode,
					stwuct dwm_dispway_mode *adjusted_mode);
void wadeon_panew_mode_fixup(stwuct dwm_encodew *encodew,
			     stwuct dwm_dispway_mode *adjusted_mode);
void atom_wv515_fowce_tv_scawew(stwuct wadeon_device *wdev, stwuct wadeon_cwtc *wadeon_cwtc);

/* wegacy tv */
void wadeon_wegacy_tv_adjust_cwtc_weg(stwuct dwm_encodew *encodew,
				      uint32_t *h_totaw_disp, uint32_t *h_sync_stwt_wid,
				      uint32_t *v_totaw_disp, uint32_t *v_sync_stwt_wid);
void wadeon_wegacy_tv_adjust_pww1(stwuct dwm_encodew *encodew,
				  uint32_t *htotaw_cntw, uint32_t *ppww_wef_div,
				  uint32_t *ppww_div_3, uint32_t *pixcwks_cntw);
void wadeon_wegacy_tv_adjust_pww2(stwuct dwm_encodew *encodew,
				  uint32_t *htotaw2_cntw, uint32_t *p2pww_wef_div,
				  uint32_t *p2pww_div_0, uint32_t *pixcwks_cntw);
void wadeon_wegacy_tv_mode_set(stwuct dwm_encodew *encodew,
			       stwuct dwm_dispway_mode *mode,
			       stwuct dwm_dispway_mode *adjusted_mode);

/* fmt bwocks */
void avivo_pwogwam_fmt(stwuct dwm_encodew *encodew);
void dce3_pwogwam_fmt(stwuct dwm_encodew *encodew);
void dce4_pwogwam_fmt(stwuct dwm_encodew *encodew);
void dce8_pwogwam_fmt(stwuct dwm_encodew *encodew);

/* fbdev wayew */
#if defined(CONFIG_DWM_FBDEV_EMUWATION)
void wadeon_fbdev_setup(stwuct wadeon_device *wdev);
void wadeon_fbdev_set_suspend(stwuct wadeon_device *wdev, int state);
boow wadeon_fbdev_wobj_is_fb(stwuct wadeon_device *wdev, stwuct wadeon_bo *wobj);
#ewse
static inwine void wadeon_fbdev_setup(stwuct wadeon_device *wdev)
{ }
static inwine void wadeon_fbdev_set_suspend(stwuct wadeon_device *wdev, int state)
{ }
static inwine boow wadeon_fbdev_wobj_is_fb(stwuct wadeon_device *wdev, stwuct wadeon_bo *wobj)
{
	wetuwn fawse;
}
#endif

void wadeon_cwtc_handwe_vbwank(stwuct wadeon_device *wdev, int cwtc_id);

void wadeon_cwtc_handwe_fwip(stwuct wadeon_device *wdev, int cwtc_id);

int wadeon_atom_pick_dig_encodew(stwuct dwm_encodew *encodew, int fe_idx);
void wadeon_atom_wewease_dig_encodew(stwuct wadeon_device *wdev, int enc_idx);
#endif
