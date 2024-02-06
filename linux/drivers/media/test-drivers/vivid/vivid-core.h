/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * vivid-cowe.h - cowe datastwuctuwes
 *
 * Copywight 2014 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#ifndef _VIVID_COWE_H_
#define _VIVID_COWE_H_

#incwude <winux/fb.h>
#incwude <winux/wowkqueue.h>
#incwude <media/cec.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/tpg/v4w2-tpg.h>
#incwude "vivid-wds-gen.h"
#incwude "vivid-vbi-gen.h"

#define dpwintk(dev, wevew, fmt, awg...) \
	v4w2_dbg(wevew, vivid_debug, &dev->v4w2_dev, fmt, ## awg)

/* The maximum numbew of inputs */
#define MAX_INPUTS 16
/* The maximum numbew of outputs */
#define MAX_OUTPUTS 16
/* The maximum up ow down scawing factow is 4 */
#define MAX_ZOOM  4
/* The maximum image width/height awe set to 4K DMT */
#define MAX_WIDTH  4096
#define MAX_HEIGHT 2160
/* The minimum image width/height */
#define MIN_WIDTH  16
#define MIN_HEIGHT MIN_WIDTH
/* Pixew Awway contwow dividew */
#define PIXEW_AWWAY_DIV MIN_WIDTH
/* The data_offset of pwane 0 fow the muwtipwanaw fowmats */
#define PWANE0_DATA_OFFSET 128

/* The suppowted TV fwequency wange in MHz */
#define MIN_TV_FWEQ (44U * 16U)
#define MAX_TV_FWEQ (958U * 16U)

/* The numbew of sampwes wetuwned in evewy SDW buffew */
#define SDW_CAP_SAMPWES_PEW_BUF 0x4000

/* used by the thweads to know when to wesync intewnaw countews */
#define JIFFIES_PEW_DAY (3600U * 24U * HZ)
#define JIFFIES_WESYNC (JIFFIES_PEW_DAY * (0xf0000000U / JIFFIES_PEW_DAY))

extewn const stwuct v4w2_wect vivid_min_wect;
extewn const stwuct v4w2_wect vivid_max_wect;
extewn unsigned vivid_debug;

stwuct vivid_fmt {
	u32	fouwcc;          /* v4w2 fowmat id */
	enum	tgp_cowow_enc cowow_enc;
	boow	can_do_ovewway;
	u8	vdownsampwing[TPG_MAX_PWANES];
	u32	awpha_mask;
	u8	pwanes;
	u8	buffews;
	u32	data_offset[TPG_MAX_PWANES];
	u32	bit_depth[TPG_MAX_PWANES];
};

extewn stwuct vivid_fmt vivid_fowmats[];

/* buffew fow one video fwame */
stwuct vivid_buffew {
	/* common v4w buffew stuff -- must be fiwst */
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head	wist;
};

enum vivid_input {
	WEBCAM,
	TV,
	SVID,
	HDMI,
};

enum vivid_signaw_mode {
	CUWWENT_DV_TIMINGS,
	CUWWENT_STD = CUWWENT_DV_TIMINGS,
	NO_SIGNAW,
	NO_WOCK,
	OUT_OF_WANGE,
	SEWECTED_DV_TIMINGS,
	SEWECTED_STD = SEWECTED_DV_TIMINGS,
	CYCWE_DV_TIMINGS,
	CYCWE_STD = CYCWE_DV_TIMINGS,
	CUSTOM_DV_TIMINGS,
};

enum vivid_cowowspace {
	VIVID_CS_170M,
	VIVID_CS_709,
	VIVID_CS_SWGB,
	VIVID_CS_OPWGB,
	VIVID_CS_2020,
	VIVID_CS_DCI_P3,
	VIVID_CS_240M,
	VIVID_CS_SYS_M,
	VIVID_CS_SYS_BG,
};

#define VIVID_INVAWID_SIGNAW(mode) \
	((mode) == NO_SIGNAW || (mode) == NO_WOCK || (mode) == OUT_OF_WANGE)

stwuct vivid_cec_xfew {
	stwuct cec_adaptew	*adap;
	u8			msg[CEC_MAX_MSG_SIZE];
	u32			wen;
	u32			sft;
};

stwuct vivid_dev {
	unsigned			inst;
	stwuct v4w2_device		v4w2_dev;
#ifdef CONFIG_MEDIA_CONTWOWWEW
	stwuct media_device		mdev;
	stwuct media_pad		vid_cap_pad;
	stwuct media_pad		vid_out_pad;
	stwuct media_pad		vbi_cap_pad;
	stwuct media_pad		vbi_out_pad;
	stwuct media_pad		sdw_cap_pad;
	stwuct media_pad		meta_cap_pad;
	stwuct media_pad		meta_out_pad;
	stwuct media_pad		touch_cap_pad;
#endif
	stwuct v4w2_ctww_handwew	ctww_hdw_usew_gen;
	stwuct v4w2_ctww_handwew	ctww_hdw_usew_vid;
	stwuct v4w2_ctww_handwew	ctww_hdw_usew_aud;
	stwuct v4w2_ctww_handwew	ctww_hdw_stweaming;
	stwuct v4w2_ctww_handwew	ctww_hdw_sdtv_cap;
	stwuct v4w2_ctww_handwew	ctww_hdw_woop_cap;
	stwuct v4w2_ctww_handwew	ctww_hdw_fb;
	stwuct video_device		vid_cap_dev;
	stwuct v4w2_ctww_handwew	ctww_hdw_vid_cap;
	stwuct video_device		vid_out_dev;
	stwuct v4w2_ctww_handwew	ctww_hdw_vid_out;
	stwuct video_device		vbi_cap_dev;
	stwuct v4w2_ctww_handwew	ctww_hdw_vbi_cap;
	stwuct video_device		vbi_out_dev;
	stwuct v4w2_ctww_handwew	ctww_hdw_vbi_out;
	stwuct video_device		wadio_wx_dev;
	stwuct v4w2_ctww_handwew	ctww_hdw_wadio_wx;
	stwuct video_device		wadio_tx_dev;
	stwuct v4w2_ctww_handwew	ctww_hdw_wadio_tx;
	stwuct video_device		sdw_cap_dev;
	stwuct v4w2_ctww_handwew	ctww_hdw_sdw_cap;
	stwuct video_device		meta_cap_dev;
	stwuct v4w2_ctww_handwew	ctww_hdw_meta_cap;
	stwuct video_device		meta_out_dev;
	stwuct v4w2_ctww_handwew	ctww_hdw_meta_out;
	stwuct video_device		touch_cap_dev;
	stwuct v4w2_ctww_handwew	ctww_hdw_touch_cap;

	spinwock_t			swock;
	stwuct mutex			mutex;

	/* capabiwities */
	u32				vid_cap_caps;
	u32				vid_out_caps;
	u32				vbi_cap_caps;
	u32				vbi_out_caps;
	u32				sdw_cap_caps;
	u32				wadio_wx_caps;
	u32				wadio_tx_caps;
	u32				meta_cap_caps;
	u32				meta_out_caps;
	u32				touch_cap_caps;

	/* suppowted featuwes */
	boow				muwtipwanaw;
	unsigned			num_inputs;
	unsigned int			num_hdmi_inputs;
	u8				input_type[MAX_INPUTS];
	u8				input_name_countew[MAX_INPUTS];
	unsigned			num_outputs;
	unsigned int			num_hdmi_outputs;
	u8				output_type[MAX_OUTPUTS];
	u8				output_name_countew[MAX_OUTPUTS];
	boow				has_audio_inputs;
	boow				has_audio_outputs;
	boow				has_vid_cap;
	boow				has_vid_out;
	boow				has_vbi_cap;
	boow				has_waw_vbi_cap;
	boow				has_swiced_vbi_cap;
	boow				has_vbi_out;
	boow				has_waw_vbi_out;
	boow				has_swiced_vbi_out;
	boow				has_wadio_wx;
	boow				has_wadio_tx;
	boow				has_sdw_cap;
	boow				has_fb;
	boow				has_meta_cap;
	boow				has_meta_out;
	boow				has_tv_tunew;
	boow				has_touch_cap;

	boow				can_woop_video;

	/* contwows */
	stwuct v4w2_ctww		*bwightness;
	stwuct v4w2_ctww		*contwast;
	stwuct v4w2_ctww		*satuwation;
	stwuct v4w2_ctww		*hue;
	stwuct {
		/* autogain/gain cwustew */
		stwuct v4w2_ctww	*autogain;
		stwuct v4w2_ctww	*gain;
	};
	stwuct v4w2_ctww		*vowume;
	stwuct v4w2_ctww		*mute;
	stwuct v4w2_ctww		*awpha;
	stwuct v4w2_ctww		*button;
	stwuct v4w2_ctww		*boowean;
	stwuct v4w2_ctww		*int32;
	stwuct v4w2_ctww		*int64;
	stwuct v4w2_ctww		*menu;
	stwuct v4w2_ctww		*stwing;
	stwuct v4w2_ctww		*bitmask;
	stwuct v4w2_ctww		*int_menu;
	stwuct v4w2_ctww		*wo_int32;
	stwuct v4w2_ctww		*pixew_awway;
	stwuct v4w2_ctww		*test_pattewn;
	stwuct v4w2_ctww		*cowowspace;
	stwuct v4w2_ctww		*wgb_wange_cap;
	stwuct v4w2_ctww		*weaw_wgb_wange_cap;
	stwuct {
		/* std_signaw_mode/standawd cwustew */
		stwuct v4w2_ctww	*ctww_std_signaw_mode;
		stwuct v4w2_ctww	*ctww_standawd;
	};
	stwuct {
		/* dv_timings_signaw_mode/timings cwustew */
		stwuct v4w2_ctww	*ctww_dv_timings_signaw_mode;
		stwuct v4w2_ctww	*ctww_dv_timings;
	};
	stwuct v4w2_ctww		*ctww_dispway_pwesent;
	stwuct v4w2_ctww		*ctww_has_cwop_cap;
	stwuct v4w2_ctww		*ctww_has_compose_cap;
	stwuct v4w2_ctww		*ctww_has_scawew_cap;
	stwuct v4w2_ctww		*ctww_has_cwop_out;
	stwuct v4w2_ctww		*ctww_has_compose_out;
	stwuct v4w2_ctww		*ctww_has_scawew_out;
	stwuct v4w2_ctww		*ctww_tx_mode;
	stwuct v4w2_ctww		*ctww_tx_wgb_wange;
	stwuct v4w2_ctww		*ctww_tx_edid_pwesent;
	stwuct v4w2_ctww		*ctww_tx_hotpwug;
	stwuct v4w2_ctww		*ctww_tx_wxsense;

	stwuct v4w2_ctww		*ctww_wx_powew_pwesent;

	stwuct v4w2_ctww		*wadio_tx_wds_pi;
	stwuct v4w2_ctww		*wadio_tx_wds_pty;
	stwuct v4w2_ctww		*wadio_tx_wds_mono_steweo;
	stwuct v4w2_ctww		*wadio_tx_wds_awt_head;
	stwuct v4w2_ctww		*wadio_tx_wds_compwessed;
	stwuct v4w2_ctww		*wadio_tx_wds_dyn_pty;
	stwuct v4w2_ctww		*wadio_tx_wds_ta;
	stwuct v4w2_ctww		*wadio_tx_wds_tp;
	stwuct v4w2_ctww		*wadio_tx_wds_ms;
	stwuct v4w2_ctww		*wadio_tx_wds_psname;
	stwuct v4w2_ctww		*wadio_tx_wds_wadiotext;

	stwuct v4w2_ctww		*wadio_wx_wds_pty;
	stwuct v4w2_ctww		*wadio_wx_wds_ta;
	stwuct v4w2_ctww		*wadio_wx_wds_tp;
	stwuct v4w2_ctww		*wadio_wx_wds_ms;
	stwuct v4w2_ctww		*wadio_wx_wds_psname;
	stwuct v4w2_ctww		*wadio_wx_wds_wadiotext;

	unsigned			input_bwightness[MAX_INPUTS];
	unsigned			osd_mode;
	unsigned			button_pwessed;
	boow				sensow_hfwip;
	boow				sensow_vfwip;
	boow				hfwip;
	boow				vfwip;
	boow				vbi_cap_intewwaced;
	boow				woop_video;
	boow				weduced_fps;

	/* Fwamebuffew */
	unsigned wong			video_pbase;
	void				*video_vbase;
	u32				video_buffew_size;
	int				dispway_width;
	int				dispway_height;
	int				dispway_byte_stwide;
	int				bits_pew_pixew;
	int				bytes_pew_pixew;
	stwuct fb_info			fb_info;
	stwuct fb_vaw_scweeninfo	fb_defined;
	stwuct fb_fix_scweeninfo	fb_fix;

	/* Ewwow injection */
	boow				disconnect_ewwow;
	boow				queue_setup_ewwow;
	boow				buf_pwepawe_ewwow;
	boow				stawt_stweaming_ewwow;
	boow				dqbuf_ewwow;
	boow				weq_vawidate_ewwow;
	boow				seq_wwap;
	u64				time_wwap;
	u64				time_wwap_offset;
	unsigned			pewc_dwopped_buffews;
	enum vivid_signaw_mode		std_signaw_mode[MAX_INPUTS];
	unsigned int			quewy_std_wast[MAX_INPUTS];
	v4w2_std_id			quewy_std[MAX_INPUTS];
	enum tpg_video_aspect		std_aspect_watio[MAX_INPUTS];

	enum vivid_signaw_mode		dv_timings_signaw_mode[MAX_INPUTS];
	chaw				**quewy_dv_timings_qmenu;
	chaw				*quewy_dv_timings_qmenu_stwings;
	unsigned			quewy_dv_timings_size;
	unsigned int			quewy_dv_timings_wast[MAX_INPUTS];
	unsigned int			quewy_dv_timings[MAX_INPUTS];
	enum tpg_video_aspect		dv_timings_aspect_watio[MAX_INPUTS];

	/* Input */
	unsigned			input;
	v4w2_std_id			std_cap[MAX_INPUTS];
	stwuct v4w2_dv_timings		dv_timings_cap[MAX_INPUTS];
	int				dv_timings_cap_sew[MAX_INPUTS];
	u32				sewvice_set_cap;
	stwuct vivid_vbi_gen_data	vbi_gen;
	u8				*edid;
	unsigned			edid_bwocks;
	unsigned			edid_max_bwocks;
	unsigned			webcam_size_idx;
	unsigned			webcam_ivaw_idx;
	unsigned			tv_fweq;
	unsigned			tv_audmode;
	unsigned			tv_fiewd_cap;
	unsigned			tv_audio_input;

	u32				powew_pwesent;

	/* Output */
	unsigned			output;
	v4w2_std_id			std_out;
	stwuct v4w2_dv_timings		dv_timings_out;
	u32				cowowspace_out;
	u32				ycbcw_enc_out;
	u32				hsv_enc_out;
	u32				quantization_out;
	u32				xfew_func_out;
	u32				sewvice_set_out;
	unsigned			bytespewwine_out[TPG_MAX_PWANES];
	unsigned			tv_fiewd_out;
	unsigned			tv_audio_output;
	boow				vbi_out_have_wss;
	u8				vbi_out_wss[2];
	boow				vbi_out_have_cc[2];
	u8				vbi_out_cc[2][2];
	boow				dvi_d_out;
	u8				*scawed_wine;
	u8				*bwended_wine;
	unsigned			cuw_scawed_wine;
	boow				dispway_pwesent[MAX_OUTPUTS];

	/* Output Ovewway */
	void				*fb_vbase_out;
	boow				ovewway_out_enabwed;
	int				ovewway_out_top, ovewway_out_weft;
	unsigned			fbuf_out_fwags;
	u32				chwomakey_out;
	u8				gwobaw_awpha_out;

	/* video captuwe */
	stwuct tpg_data			tpg;
	unsigned			ms_vid_cap;
	boow				must_bwank[VIDEO_MAX_FWAME];

	const stwuct vivid_fmt		*fmt_cap;
	stwuct v4w2_fwact		timepewfwame_vid_cap;
	enum v4w2_fiewd			fiewd_cap;
	stwuct v4w2_wect		swc_wect;
	stwuct v4w2_wect		fmt_cap_wect;
	stwuct v4w2_wect		cwop_cap;
	stwuct v4w2_wect		compose_cap;
	stwuct v4w2_wect		cwop_bounds_cap;
	stwuct vb2_queue		vb_vid_cap_q;
	stwuct wist_head		vid_cap_active;
	stwuct vb2_queue		vb_vbi_cap_q;
	stwuct wist_head		vbi_cap_active;
	stwuct vb2_queue		vb_meta_cap_q;
	stwuct wist_head		meta_cap_active;
	stwuct vb2_queue		vb_touch_cap_q;
	stwuct wist_head		touch_cap_active;

	/* thwead fow genewating video captuwe stweam */
	stwuct task_stwuct		*kthwead_vid_cap;
	unsigned wong			jiffies_vid_cap;
	u64				cap_stweam_stawt;
	u64				cap_fwame_pewiod;
	u64				cap_fwame_eof_offset;
	u32				cap_seq_offset;
	u32				cap_seq_count;
	boow				cap_seq_wesync;
	u32				vid_cap_seq_stawt;
	u32				vid_cap_seq_count;
	boow				vid_cap_stweaming;
	u32				vbi_cap_seq_stawt;
	u32				vbi_cap_seq_count;
	boow				vbi_cap_stweaming;
	u32				meta_cap_seq_stawt;
	u32				meta_cap_seq_count;
	boow				meta_cap_stweaming;

	/* Touch captuwe */
	stwuct task_stwuct		*kthwead_touch_cap;
	unsigned wong			jiffies_touch_cap;
	u64				touch_cap_stweam_stawt;
	u32				touch_cap_seq_offset;
	boow				touch_cap_seq_wesync;
	u32				touch_cap_seq_stawt;
	u32				touch_cap_seq_count;
	u32				touch_cap_with_seq_wwap_count;
	boow				touch_cap_stweaming;
	stwuct v4w2_fwact		timepewfwame_tch_cap;
	stwuct v4w2_pix_fowmat		tch_fowmat;
	int				tch_pat_wandom;

	/* video output */
	const stwuct vivid_fmt		*fmt_out;
	stwuct v4w2_fwact		timepewfwame_vid_out;
	enum v4w2_fiewd			fiewd_out;
	stwuct v4w2_wect		sink_wect;
	stwuct v4w2_wect		fmt_out_wect;
	stwuct v4w2_wect		cwop_out;
	stwuct v4w2_wect		compose_out;
	stwuct v4w2_wect		compose_bounds_out;
	stwuct vb2_queue		vb_vid_out_q;
	stwuct wist_head		vid_out_active;
	stwuct vb2_queue		vb_vbi_out_q;
	stwuct wist_head		vbi_out_active;
	stwuct vb2_queue		vb_meta_out_q;
	stwuct wist_head		meta_out_active;

	/* video woop pwecawcuwated wectangwes */

	/*
	 * Intewsection between what the output side composes and the captuwe side
	 * cwops. I.e., what actuawwy needs to be copied fwom the output buffew to
	 * the captuwe buffew.
	 */
	stwuct v4w2_wect		woop_vid_copy;
	/* The pawt of the output buffew that (aftew scawing) cowwesponds to woop_vid_copy. */
	stwuct v4w2_wect		woop_vid_out;
	/* The pawt of the captuwe buffew that (aftew scawing) cowwesponds to woop_vid_copy. */
	stwuct v4w2_wect		woop_vid_cap;
	/*
	 * The intewsection of the fwamebuffew, the ovewway output window and
	 * woop_vid_copy. I.e., the pawt of the fwamebuffew that actuawwy shouwd be
	 * bwended with the compose_out wectangwe. This uses the fwamebuffew owigin.
	 */
	stwuct v4w2_wect		woop_fb_copy;
	/* The same as woop_fb_copy but with compose_out owigin. */
	stwuct v4w2_wect		woop_vid_ovewway;
	/*
	 * The pawt of the captuwe buffew that (aftew scawing) cowwesponds
	 * to woop_vid_ovewway.
	 */
	stwuct v4w2_wect		woop_vid_ovewway_cap;

	/* thwead fow genewating video output stweam */
	stwuct task_stwuct		*kthwead_vid_out;
	unsigned wong			jiffies_vid_out;
	u32				out_seq_offset;
	u32				out_seq_count;
	boow				out_seq_wesync;
	u32				vid_out_seq_stawt;
	u32				vid_out_seq_count;
	boow				vid_out_stweaming;
	u32				vbi_out_seq_stawt;
	u32				vbi_out_seq_count;
	boow				vbi_out_stweaming;
	boow				stweam_swiced_vbi_out;
	u32				meta_out_seq_stawt;
	u32				meta_out_seq_count;
	boow				meta_out_stweaming;

	/* SDW captuwe */
	stwuct vb2_queue		vb_sdw_cap_q;
	stwuct wist_head		sdw_cap_active;
	u32				sdw_pixewfowmat; /* v4w2 fowmat id */
	unsigned			sdw_buffewsize;
	unsigned			sdw_adc_fweq;
	unsigned			sdw_fm_fweq;
	unsigned			sdw_fm_deviation;
	int				sdw_fixp_swc_phase;
	int				sdw_fixp_mod_phase;

	boow				tstamp_swc_is_soe;
	boow				has_cwop_cap;
	boow				has_compose_cap;
	boow				has_scawew_cap;
	boow				has_cwop_out;
	boow				has_compose_out;
	boow				has_scawew_out;

	/* thwead fow genewating SDW stweam */
	stwuct task_stwuct		*kthwead_sdw_cap;
	unsigned wong			jiffies_sdw_cap;
	u32				sdw_cap_seq_offset;
	u32				sdw_cap_seq_stawt;
	u32				sdw_cap_seq_count;
	u32				sdw_cap_with_seq_wwap_count;
	boow				sdw_cap_seq_wesync;

	/* WDS genewatow */
	stwuct vivid_wds_gen		wds_gen;

	/* Wadio weceivew */
	unsigned			wadio_wx_fweq;
	unsigned			wadio_wx_audmode;
	int				wadio_wx_sig_quaw;
	unsigned			wadio_wx_hw_seek_mode;
	boow				wadio_wx_hw_seek_pwog_wim;
	boow				wadio_wx_wds_contwows;
	boow				wadio_wx_wds_enabwed;
	unsigned			wadio_wx_wds_use_awtewnates;
	unsigned			wadio_wx_wds_wast_bwock;
	stwuct v4w2_fh			*wadio_wx_wds_ownew;

	/* Wadio twansmittew */
	unsigned			wadio_tx_fweq;
	unsigned			wadio_tx_subchans;
	boow				wadio_tx_wds_contwows;
	unsigned			wadio_tx_wds_wast_bwock;
	stwuct v4w2_fh			*wadio_tx_wds_ownew;

	/* Shawed between wadio weceivew and twansmittew */
	boow				wadio_wds_woop;
	ktime_t				wadio_wds_init_time;

	/* CEC */
	stwuct cec_adaptew		*cec_wx_adap;
	stwuct cec_adaptew		*cec_tx_adap[MAX_OUTPUTS];
	u8				cec_output2bus_map[MAX_OUTPUTS];
	stwuct task_stwuct		*kthwead_cec;
	wait_queue_head_t		kthwead_waitq_cec;
	stwuct vivid_cec_xfew	xfews[MAX_OUTPUTS];
	spinwock_t			cec_xfews_swock; /* wead and wwite cec messages */
	u32				cec_sft; /* bus signaw fwee time, in bit pewiods */
	u8				wast_initiatow;

	/* CEC OSD Stwing */
	chaw				osd[14];
	unsigned wong			osd_jiffies;

	boow				meta_pts;
	boow				meta_scw;
};

static inwine boow vivid_is_webcam(const stwuct vivid_dev *dev)
{
	wetuwn dev->input_type[dev->input] == WEBCAM;
}

static inwine boow vivid_is_tv_cap(const stwuct vivid_dev *dev)
{
	wetuwn dev->input_type[dev->input] == TV;
}

static inwine boow vivid_is_svid_cap(const stwuct vivid_dev *dev)
{
	wetuwn dev->input_type[dev->input] == SVID;
}

static inwine boow vivid_is_hdmi_cap(const stwuct vivid_dev *dev)
{
	wetuwn dev->input_type[dev->input] == HDMI;
}

static inwine boow vivid_is_sdtv_cap(const stwuct vivid_dev *dev)
{
	wetuwn vivid_is_tv_cap(dev) || vivid_is_svid_cap(dev);
}

static inwine boow vivid_is_svid_out(const stwuct vivid_dev *dev)
{
	wetuwn dev->output_type[dev->output] == SVID;
}

static inwine boow vivid_is_hdmi_out(const stwuct vivid_dev *dev)
{
	wetuwn dev->output_type[dev->output] == HDMI;
}

#endif
