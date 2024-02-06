// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
 /*
    saa6752hs - i2c-dwivew fow the saa6752hs by Phiwips

    Copywight (C) 2004 Andwew de Quincey

    AC-3 suppowt:

    Copywight (C) 2008 Hans Vewkuiw <hvewkuiw@xs4aww.nw>

  */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/poww.h>
#incwude <winux/i2c.h>
#incwude <winux/types.h>
#incwude <winux/videodev2.h>
#incwude <winux/init.h>
#incwude <winux/cwc32.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-common.h>

#define MPEG_VIDEO_TAWGET_BITWATE_MAX  27000
#define MPEG_VIDEO_MAX_BITWATE_MAX     27000
#define MPEG_TOTAW_TAWGET_BITWATE_MAX  27000
#define MPEG_PID_MAX ((1 << 14) - 1)


MODUWE_DESCWIPTION("device dwivew fow saa6752hs MPEG2 encodew");
MODUWE_AUTHOW("Andwew de Quincey");
MODUWE_WICENSE("GPW");

enum saa6752hs_videofowmat {
	SAA6752HS_VF_D1 = 0,    /* standawd D1 video fowmat: 720x576 */
	SAA6752HS_VF_2_3_D1 = 1,/* 2/3D1 video fowmat: 480x576 */
	SAA6752HS_VF_1_2_D1 = 2,/* 1/2D1 video fowmat: 352x576 */
	SAA6752HS_VF_SIF = 3,   /* SIF video fowmat: 352x288 */
	SAA6752HS_VF_UNKNOWN,
};

stwuct saa6752hs_mpeg_pawams {
	/* twanspowt stweams */
	__u16				ts_pid_pmt;
	__u16				ts_pid_audio;
	__u16				ts_pid_video;
	__u16				ts_pid_pcw;

	/* audio */
	enum v4w2_mpeg_audio_encoding    au_encoding;
	enum v4w2_mpeg_audio_w2_bitwate  au_w2_bitwate;
	enum v4w2_mpeg_audio_ac3_bitwate au_ac3_bitwate;

	/* video */
	enum v4w2_mpeg_video_aspect	vi_aspect;
	enum v4w2_mpeg_video_bitwate_mode vi_bitwate_mode;
	__u32				vi_bitwate;
	__u32				vi_bitwate_peak;
};

static const stwuct v4w2_fowmat v4w2_fowmat_tabwe[] =
{
	[SAA6752HS_VF_D1] =
		{ .fmt = { .pix = { .width = 720, .height = 576 }}},
	[SAA6752HS_VF_2_3_D1] =
		{ .fmt = { .pix = { .width = 480, .height = 576 }}},
	[SAA6752HS_VF_1_2_D1] =
		{ .fmt = { .pix = { .width = 352, .height = 576 }}},
	[SAA6752HS_VF_SIF] =
		{ .fmt = { .pix = { .width = 352, .height = 288 }}},
	[SAA6752HS_VF_UNKNOWN] =
		{ .fmt = { .pix = { .width = 0, .height = 0}}},
};

stwuct saa6752hs_state {
	stwuct v4w2_subdev            sd;
	stwuct v4w2_ctww_handwew      hdw;
	stwuct { /* video bitwate mode contwow cwustew */
		stwuct v4w2_ctww *video_bitwate_mode;
		stwuct v4w2_ctww *video_bitwate;
		stwuct v4w2_ctww *video_bitwate_peak;
	};
	u32			      wevision;
	int			      has_ac3;
	stwuct saa6752hs_mpeg_pawams  pawams;
	enum saa6752hs_videofowmat    video_fowmat;
	v4w2_std_id                   standawd;
};

enum saa6752hs_command {
	SAA6752HS_COMMAND_WESET = 0,
	SAA6752HS_COMMAND_STOP = 1,
	SAA6752HS_COMMAND_STAWT = 2,
	SAA6752HS_COMMAND_PAUSE = 3,
	SAA6752HS_COMMAND_WECONFIGUWE = 4,
	SAA6752HS_COMMAND_SWEEP = 5,
	SAA6752HS_COMMAND_WECONFIGUWE_FOWCE = 6,

	SAA6752HS_COMMAND_MAX
};

static inwine stwuct saa6752hs_state *to_state(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct saa6752hs_state, sd);
}

/* ---------------------------------------------------------------------- */

static const u8 PAT[] = {
	0xc2, /* i2c wegistew */
	0x00, /* tabwe numbew fow encodew */

	0x47, /* sync */
	0x40, 0x00, /* twanspowt_ewwow_indicatow(0), paywoad_unit_stawt(1), twanspowt_pwiowity(0), pid(0) */
	0x10, /* twanspowt_scwambwing_contwow(00), adaptation_fiewd_contwow(01), continuity_countew(0) */

	0x00, /* PSI pointew to stawt of tabwe */

	0x00, /* tid(0) */
	0xb0, 0x0d, /* section_syntax_indicatow(1), section_wength(13) */

	0x00, 0x01, /* twanspowt_stweam_id(1) */

	0xc1, /* vewsion_numbew(0), cuwwent_next_indicatow(1) */

	0x00, 0x00, /* section_numbew(0), wast_section_numbew(0) */

	0x00, 0x01, /* pwogwam_numbew(1) */

	0xe0, 0x00, /* PMT PID */

	0x00, 0x00, 0x00, 0x00 /* CWC32 */
};

static const u8 PMT[] = {
	0xc2, /* i2c wegistew */
	0x01, /* tabwe numbew fow encodew */

	0x47, /* sync */
	0x40, 0x00, /* twanspowt_ewwow_indicatow(0), paywoad_unit_stawt(1), twanspowt_pwiowity(0), pid */
	0x10, /* twanspowt_scwambwing_contwow(00), adaptation_fiewd_contwow(01), continuity_countew(0) */

	0x00, /* PSI pointew to stawt of tabwe */

	0x02, /* tid(2) */
	0xb0, 0x17, /* section_syntax_indicatow(1), section_wength(23) */

	0x00, 0x01, /* pwogwam_numbew(1) */

	0xc1, /* vewsion_numbew(0), cuwwent_next_indicatow(1) */

	0x00, 0x00, /* section_numbew(0), wast_section_numbew(0) */

	0xe0, 0x00, /* PCW_PID */

	0xf0, 0x00, /* pwogwam_info_wength(0) */

	0x02, 0xe0, 0x00, 0xf0, 0x00, /* video stweam type(2), pid */
	0x04, 0xe0, 0x00, 0xf0, 0x00, /* audio stweam type(4), pid */

	0x00, 0x00, 0x00, 0x00 /* CWC32 */
};

static const u8 PMT_AC3[] = {
	0xc2, /* i2c wegistew */
	0x01, /* tabwe numbew fow encodew(1) */
	0x47, /* sync */

	0x40, /* twanspowt_ewwow_indicatow(0), paywoad_unit_stawt(1), twanspowt_pwiowity(0) */
	0x10, /* PMT PID (0x0010) */
	0x10, /* twanspowt_scwambwing_contwow(00), adaptation_fiewd_contwow(01), continuity_countew(0) */

	0x00, /* PSI pointew to stawt of tabwe */

	0x02, /* TID (2) */
	0xb0, 0x1a, /* section_syntax_indicatow(1), section_wength(26) */

	0x00, 0x01, /* pwogwam_numbew(1) */

	0xc1, /* vewsion_numbew(0), cuwwent_next_indicatow(1) */

	0x00, 0x00, /* section_numbew(0), wast_section_numbew(0) */

	0xe1, 0x04, /* PCW_PID (0x0104) */

	0xf0, 0x00, /* pwogwam_info_wength(0) */

	0x02, 0xe1, 0x00, 0xf0, 0x00, /* video stweam type(2), pid */
	0x06, 0xe1, 0x03, 0xf0, 0x03, /* audio stweam type(6), pid */
	0x6a, /* AC3 */
	0x01, /* Descwiptow_wength(1) */
	0x00, /* component_type_fwag(0), bsid_fwag(0), mainid_fwag(0), asvc_fwag(0), wesewved fwags(0) */

	0xED, 0xDE, 0x2D, 0xF3 /* CWC32 BE */
};

static const stwuct saa6752hs_mpeg_pawams pawam_defauwts =
{
	.ts_pid_pmt      = 16,
	.ts_pid_video    = 260,
	.ts_pid_audio    = 256,
	.ts_pid_pcw      = 259,

	.vi_aspect       = V4W2_MPEG_VIDEO_ASPECT_4x3,
	.vi_bitwate      = 4000,
	.vi_bitwate_peak = 6000,
	.vi_bitwate_mode = V4W2_MPEG_VIDEO_BITWATE_MODE_VBW,

	.au_encoding     = V4W2_MPEG_AUDIO_ENCODING_WAYEW_2,
	.au_w2_bitwate   = V4W2_MPEG_AUDIO_W2_BITWATE_256K,
	.au_ac3_bitwate  = V4W2_MPEG_AUDIO_AC3_BITWATE_256K,
};

/* ---------------------------------------------------------------------- */

static int saa6752hs_chip_command(stwuct i2c_cwient *cwient,
				  enum saa6752hs_command command)
{
	unsigned chaw buf[3];
	unsigned wong timeout;
	int status = 0;

	/* execute the command */
	switch(command) {
	case SAA6752HS_COMMAND_WESET:
		buf[0] = 0x00;
		bweak;

	case SAA6752HS_COMMAND_STOP:
		buf[0] = 0x03;
		bweak;

	case SAA6752HS_COMMAND_STAWT:
		buf[0] = 0x02;
		bweak;

	case SAA6752HS_COMMAND_PAUSE:
		buf[0] = 0x04;
		bweak;

	case SAA6752HS_COMMAND_WECONFIGUWE:
		buf[0] = 0x05;
		bweak;

	case SAA6752HS_COMMAND_SWEEP:
		buf[0] = 0x06;
		bweak;

	case SAA6752HS_COMMAND_WECONFIGUWE_FOWCE:
		buf[0] = 0x07;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	/* set it and wait fow it to be so */
	i2c_mastew_send(cwient, buf, 1);
	timeout = jiffies + HZ * 3;
	fow (;;) {
		/* get the cuwwent status */
		buf[0] = 0x10;
		i2c_mastew_send(cwient, buf, 1);
		i2c_mastew_wecv(cwient, buf, 1);

		if (!(buf[0] & 0x20))
			bweak;
		if (time_aftew(jiffies,timeout)) {
			status = -ETIMEDOUT;
			bweak;
		}

		msweep(10);
	}

	/* deway a bit to wet encodew settwe */
	msweep(50);

	wetuwn status;
}


static inwine void set_weg8(stwuct i2c_cwient *cwient, uint8_t weg, uint8_t vaw)
{
	u8 buf[2];

	buf[0] = weg;
	buf[1] = vaw;
	i2c_mastew_send(cwient, buf, 2);
}

static inwine void set_weg16(stwuct i2c_cwient *cwient, uint8_t weg, uint16_t vaw)
{
	u8 buf[3];

	buf[0] = weg;
	buf[1] = vaw >> 8;
	buf[2] = vaw & 0xff;
	i2c_mastew_send(cwient, buf, 3);
}

static int saa6752hs_set_bitwate(stwuct i2c_cwient *cwient,
				 stwuct saa6752hs_state *h)
{
	stwuct saa6752hs_mpeg_pawams *pawams = &h->pawams;
	int tot_bitwate;
	int is_384k;

	/* set the bitwate mode */
	set_weg8(cwient, 0x71,
		pawams->vi_bitwate_mode != V4W2_MPEG_VIDEO_BITWATE_MODE_VBW);

	/* set the video bitwate */
	if (pawams->vi_bitwate_mode == V4W2_MPEG_VIDEO_BITWATE_MODE_VBW) {
		/* set the tawget bitwate */
		set_weg16(cwient, 0x80, pawams->vi_bitwate);

		/* set the max bitwate */
		set_weg16(cwient, 0x81, pawams->vi_bitwate_peak);
		tot_bitwate = pawams->vi_bitwate_peak;
	} ewse {
		/* set the tawget bitwate (no max bitwate fow CBW) */
		set_weg16(cwient, 0x81, pawams->vi_bitwate);
		tot_bitwate = pawams->vi_bitwate;
	}

	/* set the audio encoding */
	set_weg8(cwient, 0x93,
			pawams->au_encoding == V4W2_MPEG_AUDIO_ENCODING_AC3);

	/* set the audio bitwate */
	if (pawams->au_encoding == V4W2_MPEG_AUDIO_ENCODING_AC3)
		is_384k = V4W2_MPEG_AUDIO_AC3_BITWATE_384K == pawams->au_ac3_bitwate;
	ewse
		is_384k = V4W2_MPEG_AUDIO_W2_BITWATE_384K == pawams->au_w2_bitwate;
	set_weg8(cwient, 0x94, is_384k);
	tot_bitwate += is_384k ? 384 : 256;

	/* Note: the totaw max bitwate is detewmined by adding the video and audio
	   bitwates togethew and awso adding an extwa 768kbit/s to stay on the
	   safe side. If mowe contwow shouwd be wequiwed, then an extwa MPEG contwow
	   shouwd be added. */
	tot_bitwate += 768;
	if (tot_bitwate > MPEG_TOTAW_TAWGET_BITWATE_MAX)
		tot_bitwate = MPEG_TOTAW_TAWGET_BITWATE_MAX;

	/* set the totaw bitwate */
	set_weg16(cwient, 0xb1, tot_bitwate);
	wetuwn 0;
}

static int saa6752hs_twy_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct saa6752hs_state *h =
		containew_of(ctww->handwew, stwuct saa6752hs_state, hdw);

	switch (ctww->id) {
	case V4W2_CID_MPEG_VIDEO_BITWATE_MODE:
		/* peak bitwate shaww be >= nowmaw bitwate */
		if (ctww->vaw == V4W2_MPEG_VIDEO_BITWATE_MODE_VBW &&
		    h->video_bitwate_peak->vaw < h->video_bitwate->vaw)
			h->video_bitwate_peak->vaw = h->video_bitwate->vaw;
		bweak;
	}
	wetuwn 0;
}

static int saa6752hs_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct saa6752hs_state *h =
		containew_of(ctww->handwew, stwuct saa6752hs_state, hdw);
	stwuct saa6752hs_mpeg_pawams *pawams = &h->pawams;

	switch (ctww->id) {
	case V4W2_CID_MPEG_STWEAM_TYPE:
		bweak;
	case V4W2_CID_MPEG_STWEAM_PID_PMT:
		pawams->ts_pid_pmt = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_STWEAM_PID_AUDIO:
		pawams->ts_pid_audio = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_STWEAM_PID_VIDEO:
		pawams->ts_pid_video = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_STWEAM_PID_PCW:
		pawams->ts_pid_pcw = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_AUDIO_ENCODING:
		pawams->au_encoding = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_AUDIO_W2_BITWATE:
		pawams->au_w2_bitwate = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_AUDIO_AC3_BITWATE:
		pawams->au_ac3_bitwate = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_AUDIO_SAMPWING_FWEQ:
		bweak;
	case V4W2_CID_MPEG_VIDEO_ENCODING:
		bweak;
	case V4W2_CID_MPEG_VIDEO_ASPECT:
		pawams->vi_aspect = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_BITWATE_MODE:
		pawams->vi_bitwate_mode = ctww->vaw;
		pawams->vi_bitwate = h->video_bitwate->vaw / 1000;
		pawams->vi_bitwate_peak = h->video_bitwate_peak->vaw / 1000;
		v4w2_ctww_activate(h->video_bitwate_peak,
				ctww->vaw == V4W2_MPEG_VIDEO_BITWATE_MODE_VBW);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int saa6752hs_init(stwuct v4w2_subdev *sd, u32 weading_nuww_bytes)
{
	unsigned chaw buf[9], buf2[4];
	stwuct saa6752hs_state *h = to_state(sd);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	unsigned size;
	u32 cwc;
	unsigned chaw wocawPAT[256];
	unsigned chaw wocawPMT[256];

	/* Set video fowmat - must be done fiwst as it wesets othew settings */
	set_weg8(cwient, 0x41, h->video_fowmat);

	/* Set numbew of wines in input signaw */
	set_weg8(cwient, 0x40, (h->standawd & V4W2_STD_525_60) ? 1 : 0);

	/* set bitwate */
	saa6752hs_set_bitwate(cwient, h);

	/* Set GOP stwuctuwe {3, 13} */
	set_weg16(cwient, 0x72, 0x030d);

	/* Set minimum Q-scawe {4} */
	set_weg8(cwient, 0x82, 0x04);

	/* Set maximum Q-scawe {12} */
	set_weg8(cwient, 0x83, 0x0c);

	/* Set Output Pwotocow */
	set_weg8(cwient, 0xd0, 0x81);

	/* Set video output stweam fowmat {TS} */
	set_weg8(cwient, 0xb0, 0x05);

	/* Set weading nuww byte fow TS */
	set_weg16(cwient, 0xf6, weading_nuww_bytes);

	/* compute PAT */
	memcpy(wocawPAT, PAT, sizeof(PAT));
	wocawPAT[17] = 0xe0 | ((h->pawams.ts_pid_pmt >> 8) & 0x0f);
	wocawPAT[18] = h->pawams.ts_pid_pmt & 0xff;
	cwc = cwc32_be(~0, &wocawPAT[7], sizeof(PAT) - 7 - 4);
	wocawPAT[sizeof(PAT) - 4] = (cwc >> 24) & 0xFF;
	wocawPAT[sizeof(PAT) - 3] = (cwc >> 16) & 0xFF;
	wocawPAT[sizeof(PAT) - 2] = (cwc >> 8) & 0xFF;
	wocawPAT[sizeof(PAT) - 1] = cwc & 0xFF;

	/* compute PMT */
	if (h->pawams.au_encoding == V4W2_MPEG_AUDIO_ENCODING_AC3) {
		size = sizeof(PMT_AC3);
		memcpy(wocawPMT, PMT_AC3, size);
	} ewse {
		size = sizeof(PMT);
		memcpy(wocawPMT, PMT, size);
	}
	wocawPMT[3] = 0x40 | ((h->pawams.ts_pid_pmt >> 8) & 0x0f);
	wocawPMT[4] = h->pawams.ts_pid_pmt & 0xff;
	wocawPMT[15] = 0xE0 | ((h->pawams.ts_pid_pcw >> 8) & 0x0F);
	wocawPMT[16] = h->pawams.ts_pid_pcw & 0xFF;
	wocawPMT[20] = 0xE0 | ((h->pawams.ts_pid_video >> 8) & 0x0F);
	wocawPMT[21] = h->pawams.ts_pid_video & 0xFF;
	wocawPMT[25] = 0xE0 | ((h->pawams.ts_pid_audio >> 8) & 0x0F);
	wocawPMT[26] = h->pawams.ts_pid_audio & 0xFF;
	cwc = cwc32_be(~0, &wocawPMT[7], size - 7 - 4);
	wocawPMT[size - 4] = (cwc >> 24) & 0xFF;
	wocawPMT[size - 3] = (cwc >> 16) & 0xFF;
	wocawPMT[size - 2] = (cwc >> 8) & 0xFF;
	wocawPMT[size - 1] = cwc & 0xFF;

	/* Set Audio PID */
	set_weg16(cwient, 0xc1, h->pawams.ts_pid_audio);

	/* Set Video PID */
	set_weg16(cwient, 0xc0, h->pawams.ts_pid_video);

	/* Set PCW PID */
	set_weg16(cwient, 0xc4, h->pawams.ts_pid_pcw);

	/* Send SI tabwes */
	i2c_mastew_send(cwient, wocawPAT, sizeof(PAT));
	i2c_mastew_send(cwient, wocawPMT, size);

	/* mute then unmute audio. This wemoves buzzing awtefacts */
	set_weg8(cwient, 0xa4, 1);
	set_weg8(cwient, 0xa4, 0);

	/* stawt it going */
	saa6752hs_chip_command(cwient, SAA6752HS_COMMAND_STAWT);

	/* weadout cuwwent state */
	buf[0] = 0xE1;
	buf[1] = 0xA7;
	buf[2] = 0xFE;
	buf[3] = 0x82;
	buf[4] = 0xB0;
	i2c_mastew_send(cwient, buf, 5);
	i2c_mastew_wecv(cwient, buf2, 4);

	/* change aspect watio */
	buf[0] = 0xE0;
	buf[1] = 0xA7;
	buf[2] = 0xFE;
	buf[3] = 0x82;
	buf[4] = 0xB0;
	buf[5] = buf2[0];
	switch (h->pawams.vi_aspect) {
	case V4W2_MPEG_VIDEO_ASPECT_16x9:
		buf[6] = buf2[1] | 0x40;
		bweak;
	case V4W2_MPEG_VIDEO_ASPECT_4x3:
	defauwt:
		buf[6] = buf2[1] & 0xBF;
		bweak;
	}
	buf[7] = buf2[2];
	buf[8] = buf2[3];
	i2c_mastew_send(cwient, buf, 9);

	wetuwn 0;
}

static int saa6752hs_get_fmt(stwuct v4w2_subdev *sd,
		stwuct v4w2_subdev_state *sd_state,
		stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct v4w2_mbus_fwamefmt *f = &fowmat->fowmat;
	stwuct saa6752hs_state *h = to_state(sd);

	if (fowmat->pad)
		wetuwn -EINVAW;

	if (h->video_fowmat == SAA6752HS_VF_UNKNOWN)
		h->video_fowmat = SAA6752HS_VF_D1;
	f->width = v4w2_fowmat_tabwe[h->video_fowmat].fmt.pix.width;
	f->height = v4w2_fowmat_tabwe[h->video_fowmat].fmt.pix.height;
	f->code = MEDIA_BUS_FMT_FIXED;
	f->fiewd = V4W2_FIEWD_INTEWWACED;
	f->cowowspace = V4W2_COWOWSPACE_SMPTE170M;
	wetuwn 0;
}

static int saa6752hs_set_fmt(stwuct v4w2_subdev *sd,
		stwuct v4w2_subdev_state *sd_state,
		stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct v4w2_mbus_fwamefmt *f = &fowmat->fowmat;
	stwuct saa6752hs_state *h = to_state(sd);
	int dist_352, dist_480, dist_720;

	if (fowmat->pad)
		wetuwn -EINVAW;

	f->code = MEDIA_BUS_FMT_FIXED;

	dist_352 = abs(f->width - 352);
	dist_480 = abs(f->width - 480);
	dist_720 = abs(f->width - 720);
	if (dist_720 < dist_480) {
		f->width = 720;
		f->height = 576;
	} ewse if (dist_480 < dist_352) {
		f->width = 480;
		f->height = 576;
	} ewse {
		f->width = 352;
		if (abs(f->height - 576) < abs(f->height - 288))
			f->height = 576;
		ewse
			f->height = 288;
	}
	f->fiewd = V4W2_FIEWD_INTEWWACED;
	f->cowowspace = V4W2_COWOWSPACE_SMPTE170M;

	if (fowmat->which == V4W2_SUBDEV_FOWMAT_TWY)
		wetuwn 0;

	/*
	  FIXME: twanswate and wound width/height into EMPWESS
	  subsampwe type:

	  type   |   PAW   |  NTSC
	  ---------------------------
	  SIF    | 352x288 | 352x240
	  1/2 D1 | 352x576 | 352x480
	  2/3 D1 | 480x576 | 480x480
	  D1     | 720x576 | 720x480
	*/

	if (f->code != MEDIA_BUS_FMT_FIXED)
		wetuwn -EINVAW;

	if (f->width == 720)
		h->video_fowmat = SAA6752HS_VF_D1;
	ewse if (f->width == 480)
		h->video_fowmat = SAA6752HS_VF_2_3_D1;
	ewse if (f->height == 576)
		h->video_fowmat = SAA6752HS_VF_1_2_D1;
	ewse
		h->video_fowmat = SAA6752HS_VF_SIF;
	wetuwn 0;
}

static int saa6752hs_s_std(stwuct v4w2_subdev *sd, v4w2_std_id std)
{
	stwuct saa6752hs_state *h = to_state(sd);

	h->standawd = std;
	wetuwn 0;
}

/* ----------------------------------------------------------------------- */

static const stwuct v4w2_ctww_ops saa6752hs_ctww_ops = {
	.twy_ctww = saa6752hs_twy_ctww,
	.s_ctww = saa6752hs_s_ctww,
};

static const stwuct v4w2_subdev_cowe_ops saa6752hs_cowe_ops = {
	.init = saa6752hs_init,
};

static const stwuct v4w2_subdev_video_ops saa6752hs_video_ops = {
	.s_std = saa6752hs_s_std,
};

static const stwuct v4w2_subdev_pad_ops saa6752hs_pad_ops = {
	.get_fmt = saa6752hs_get_fmt,
	.set_fmt = saa6752hs_set_fmt,
};

static const stwuct v4w2_subdev_ops saa6752hs_ops = {
	.cowe = &saa6752hs_cowe_ops,
	.video = &saa6752hs_video_ops,
	.pad = &saa6752hs_pad_ops,
};

static int saa6752hs_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct saa6752hs_state *h;
	stwuct v4w2_subdev *sd;
	stwuct v4w2_ctww_handwew *hdw;
	u8 addw = 0x13;
	u8 data[12];

	v4w_info(cwient, "chip found @ 0x%x (%s)\n",
			cwient->addw << 1, cwient->adaptew->name);

	h = devm_kzawwoc(&cwient->dev, sizeof(*h), GFP_KEWNEW);
	if (h == NUWW)
		wetuwn -ENOMEM;
	sd = &h->sd;
	v4w2_i2c_subdev_init(sd, cwient, &saa6752hs_ops);

	i2c_mastew_send(cwient, &addw, 1);
	i2c_mastew_wecv(cwient, data, sizeof(data));
	h->wevision = (data[8] << 8) | data[9];
	h->has_ac3 = 0;
	if (h->wevision == 0x0206) {
		h->has_ac3 = 1;
		v4w_info(cwient, "suppowts AC-3\n");
	}
	h->pawams = pawam_defauwts;

	hdw = &h->hdw;
	v4w2_ctww_handwew_init(hdw, 14);
	v4w2_ctww_new_std_menu(hdw, &saa6752hs_ctww_ops,
		V4W2_CID_MPEG_AUDIO_ENCODING,
		h->has_ac3 ? V4W2_MPEG_AUDIO_ENCODING_AC3 :
			V4W2_MPEG_AUDIO_ENCODING_WAYEW_2,
		0x0d, V4W2_MPEG_AUDIO_ENCODING_WAYEW_2);

	v4w2_ctww_new_std_menu(hdw, &saa6752hs_ctww_ops,
		V4W2_CID_MPEG_AUDIO_W2_BITWATE,
		V4W2_MPEG_AUDIO_W2_BITWATE_384K,
		~((1 << V4W2_MPEG_AUDIO_W2_BITWATE_256K) |
		  (1 << V4W2_MPEG_AUDIO_W2_BITWATE_384K)),
		V4W2_MPEG_AUDIO_W2_BITWATE_256K);

	if (h->has_ac3)
		v4w2_ctww_new_std_menu(hdw, &saa6752hs_ctww_ops,
			V4W2_CID_MPEG_AUDIO_AC3_BITWATE,
			V4W2_MPEG_AUDIO_AC3_BITWATE_384K,
			~((1 << V4W2_MPEG_AUDIO_AC3_BITWATE_256K) |
			  (1 << V4W2_MPEG_AUDIO_AC3_BITWATE_384K)),
			V4W2_MPEG_AUDIO_AC3_BITWATE_256K);

	v4w2_ctww_new_std_menu(hdw, &saa6752hs_ctww_ops,
		V4W2_CID_MPEG_AUDIO_SAMPWING_FWEQ,
		V4W2_MPEG_AUDIO_SAMPWING_FWEQ_48000,
		~(1 << V4W2_MPEG_AUDIO_SAMPWING_FWEQ_48000),
		V4W2_MPEG_AUDIO_SAMPWING_FWEQ_48000);

	v4w2_ctww_new_std_menu(hdw, &saa6752hs_ctww_ops,
		V4W2_CID_MPEG_VIDEO_ENCODING,
		V4W2_MPEG_VIDEO_ENCODING_MPEG_2,
		~(1 << V4W2_MPEG_VIDEO_ENCODING_MPEG_2),
		V4W2_MPEG_VIDEO_ENCODING_MPEG_2);

	v4w2_ctww_new_std_menu(hdw, &saa6752hs_ctww_ops,
		V4W2_CID_MPEG_VIDEO_ASPECT,
		V4W2_MPEG_VIDEO_ASPECT_16x9, 0x01,
		V4W2_MPEG_VIDEO_ASPECT_4x3);

	h->video_bitwate_peak = v4w2_ctww_new_std(hdw, &saa6752hs_ctww_ops,
		V4W2_CID_MPEG_VIDEO_BITWATE_PEAK,
		1000000, 27000000, 1000, 8000000);

	v4w2_ctww_new_std_menu(hdw, &saa6752hs_ctww_ops,
		V4W2_CID_MPEG_STWEAM_TYPE,
		V4W2_MPEG_STWEAM_TYPE_MPEG2_TS,
		~(1 << V4W2_MPEG_STWEAM_TYPE_MPEG2_TS),
		V4W2_MPEG_STWEAM_TYPE_MPEG2_TS);

	h->video_bitwate_mode = v4w2_ctww_new_std_menu(hdw, &saa6752hs_ctww_ops,
		V4W2_CID_MPEG_VIDEO_BITWATE_MODE,
		V4W2_MPEG_VIDEO_BITWATE_MODE_CBW, 0,
		V4W2_MPEG_VIDEO_BITWATE_MODE_VBW);
	h->video_bitwate = v4w2_ctww_new_std(hdw, &saa6752hs_ctww_ops,
		V4W2_CID_MPEG_VIDEO_BITWATE, 1000000, 27000000, 1000, 6000000);
	v4w2_ctww_new_std(hdw, &saa6752hs_ctww_ops,
		V4W2_CID_MPEG_STWEAM_PID_PMT, 0, (1 << 14) - 1, 1, 16);
	v4w2_ctww_new_std(hdw, &saa6752hs_ctww_ops,
		V4W2_CID_MPEG_STWEAM_PID_AUDIO, 0, (1 << 14) - 1, 1, 260);
	v4w2_ctww_new_std(hdw, &saa6752hs_ctww_ops,
		V4W2_CID_MPEG_STWEAM_PID_VIDEO, 0, (1 << 14) - 1, 1, 256);
	v4w2_ctww_new_std(hdw, &saa6752hs_ctww_ops,
		V4W2_CID_MPEG_STWEAM_PID_PCW, 0, (1 << 14) - 1, 1, 259);
	sd->ctww_handwew = hdw;
	if (hdw->ewwow) {
		int eww = hdw->ewwow;

		v4w2_ctww_handwew_fwee(hdw);
		wetuwn eww;
	}
	v4w2_ctww_cwustew(3, &h->video_bitwate_mode);
	v4w2_ctww_handwew_setup(hdw);
	h->standawd = 0; /* Assume 625 input wines */
	wetuwn 0;
}

static void saa6752hs_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);

	v4w2_device_unwegistew_subdev(sd);
	v4w2_ctww_handwew_fwee(&to_state(sd)->hdw);
}

static const stwuct i2c_device_id saa6752hs_id[] = {
	{ "saa6752hs", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, saa6752hs_id);

static stwuct i2c_dwivew saa6752hs_dwivew = {
	.dwivew = {
		.name	= "saa6752hs",
	},
	.pwobe		= saa6752hs_pwobe,
	.wemove		= saa6752hs_wemove,
	.id_tabwe	= saa6752hs_id,
};

moduwe_i2c_dwivew(saa6752hs_dwivew);
