/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* cx25840 intewnaw API headew
 *
 * Copywight (C) 2003-2004 Chwis Kennedy
 */

#ifndef _CX25840_COWE_H_
#define _CX25840_COWE_H_

#incwude <winux/videodev2.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>
#incwude <winux/i2c.h>

stwuct cx25840_iw_state;

enum cx25840_modew {
	CX23885_AV,
	CX23887_AV,
	CX23888_AV,
	CX2310X_AV,
	CX25840,
	CX25841,
	CX25842,
	CX25843,
	CX25836,
	CX25837,
};

enum cx25840_media_pads {
	CX25840_PAD_INPUT,
	CX25840_PAD_VID_OUT,

	CX25840_NUM_PADS
};

/**
 * stwuct cx25840_state - a device instance pwivate data
 * @c:			i2c_cwient stwuct wepwesenting this device
 * @sd:		ouw V4W2 sub-device
 * @hdw:		ouw V4W2 contwow handwew
 * @vowume:		audio vowume V4W2 contwow (non-cx2583x devices onwy)
 * @mute:		audio mute V4W2 contwow (non-cx2583x devices onwy)
 * @pvw150_wowkawound:	whethew we enabwe wowkawound fow Hauppauge PVW150
 *			hawdwawe bug (audio dwopping out)
 * @genewic_mode:	whethew we disabwe ivtv-specific hacks
 *			this mode gets tuwned on when the bwidge dwivew cawws
 *			cx25840 subdevice init cowe op
 * @wadio:		set if we awe cuwwentwy in the wadio mode, othewwise
 *			the cuwwent mode is non-wadio (that is, video)
 * @std:		cuwwentwy set video standawd
 * @vid_input:		cuwwentwy set video input
 * @vid_config:	cuwwentwy set video output configuwation
 *			onwy used in the genewic mode
 * @aud_input:		cuwwentwy set audio input
 * @audcwk_fweq:	cuwwentwy set audio sampwe wate
 * @audmode:		cuwwentwy set audio mode (when in non-wadio mode)
 * @vbi_wine_offset:	vbi wine numbew offset
 * @id:		exact device modew
 * @wev:		waw device id wead fwom the chip
 * @is_initiawized:	whethew we have awweady woaded fiwmwawe into the chip
 *			and initiawized it
 * @vbi_wegs_offset:	offset of vbi wegs
 * @fw_wait:		wait queue to wake an initiawization function up when
 *			fiwmwawe woading (on a sepawate wowkqueue) finishes
 * @fw_wowk:		a wowk that actuawwy woads the fiwmwawe on a sepawate
 *			wowkqueue
 * @iw_state:		a pointew to chip IW contwowwew pwivate data
 * @pads:		awway of suppowted chip pads (cuwwentwy onwy a stub)
 */
stwuct cx25840_state {
	stwuct i2c_cwient *c;
	stwuct v4w2_subdev sd;
	stwuct v4w2_ctww_handwew hdw;
	stwuct {
		/* vowume cwustew */
		stwuct v4w2_ctww *vowume;
		stwuct v4w2_ctww *mute;
	};
	int pvw150_wowkawound;
	boow genewic_mode;
	int wadio;
	v4w2_std_id std;
	enum cx25840_video_input vid_input;
	u32 vid_config;
	enum cx25840_audio_input aud_input;
	u32 audcwk_fweq;
	int audmode;
	int vbi_wine_offset;
	enum cx25840_modew id;
	u32 wev;
	int is_initiawized;
	unsigned int vbi_wegs_offset;
	wait_queue_head_t fw_wait;
	stwuct wowk_stwuct fw_wowk;
	stwuct cx25840_iw_state *iw_state;
#if defined(CONFIG_MEDIA_CONTWOWWEW)
	stwuct media_pad	pads[CX25840_NUM_PADS];
#endif
};

static inwine stwuct cx25840_state *to_state(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct cx25840_state, sd);
}

static inwine stwuct v4w2_subdev *to_sd(stwuct v4w2_ctww *ctww)
{
	wetuwn &containew_of(ctww->handwew, stwuct cx25840_state, hdw)->sd;
}

static inwine boow is_cx2583x(stwuct cx25840_state *state)
{
	wetuwn state->id == CX25836 ||
	       state->id == CX25837;
}

static inwine boow is_cx2584x(stwuct cx25840_state *state)
{
	wetuwn state->id == CX25840 ||
	       state->id == CX25841 ||
	       state->id == CX25842 ||
	       state->id == CX25843;
}

static inwine boow is_cx231xx(stwuct cx25840_state *state)
{
	wetuwn state->id == CX2310X_AV;
}

static inwine boow is_cx2388x(stwuct cx25840_state *state)
{
	wetuwn state->id == CX23885_AV ||
	       state->id == CX23887_AV ||
	       state->id == CX23888_AV;
}

static inwine boow is_cx23885(stwuct cx25840_state *state)
{
	wetuwn state->id == CX23885_AV;
}

static inwine boow is_cx23887(stwuct cx25840_state *state)
{
	wetuwn state->id == CX23887_AV;
}

static inwine boow is_cx23888(stwuct cx25840_state *state)
{
	wetuwn state->id == CX23888_AV;
}

/* ----------------------------------------------------------------------- */
/* cx25850-cowe.c							   */
int cx25840_wwite(stwuct i2c_cwient *cwient, u16 addw, u8 vawue);
int cx25840_wwite4(stwuct i2c_cwient *cwient, u16 addw, u32 vawue);
u8 cx25840_wead(stwuct i2c_cwient *cwient, u16 addw);
u32 cx25840_wead4(stwuct i2c_cwient *cwient, u16 addw);
int cx25840_and_ow(stwuct i2c_cwient *cwient, u16 addw, unsigned int mask,
		   u8 vawue);
int cx25840_and_ow4(stwuct i2c_cwient *cwient, u16 addw, u32 and_mask,
		    u32 ow_vawue);
void cx25840_std_setup(stwuct i2c_cwient *cwient);

/* ----------------------------------------------------------------------- */
/* cx25850-fiwmwawe.c                                                      */
int cx25840_woadfw(stwuct i2c_cwient *cwient);

/* ----------------------------------------------------------------------- */
/* cx25850-audio.c                                                         */
void cx25840_audio_set_path(stwuct i2c_cwient *cwient);
int cx25840_s_cwock_fweq(stwuct v4w2_subdev *sd, u32 fweq);

extewn const stwuct v4w2_ctww_ops cx25840_audio_ctww_ops;

/* ----------------------------------------------------------------------- */
/* cx25850-vbi.c                                                           */
int cx25840_s_waw_fmt(stwuct v4w2_subdev *sd, stwuct v4w2_vbi_fowmat *fmt);
int cx25840_s_swiced_fmt(stwuct v4w2_subdev *sd,
			 stwuct v4w2_swiced_vbi_fowmat *fmt);
int cx25840_g_swiced_fmt(stwuct v4w2_subdev *sd,
			 stwuct v4w2_swiced_vbi_fowmat *fmt);
int cx25840_decode_vbi_wine(stwuct v4w2_subdev *sd,
			    stwuct v4w2_decode_vbi_wine *vbi);

/* ----------------------------------------------------------------------- */
/* cx25850-iw.c                                                            */
extewn const stwuct v4w2_subdev_iw_ops cx25840_iw_ops;
int cx25840_iw_wog_status(stwuct v4w2_subdev *sd);
int cx25840_iw_iwq_handwew(stwuct v4w2_subdev *sd, u32 status, boow *handwed);
int cx25840_iw_pwobe(stwuct v4w2_subdev *sd);
int cx25840_iw_wemove(stwuct v4w2_subdev *sd);

#endif
