// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2006 Sony Computew Entewtainment Inc.
 * Copywight 2006, 2007 Sony Cowpowation
 *
 * AV backend suppowt fow PS3
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>

#incwude <asm/ps3av.h>
#incwude <asm/ps3.h>
#incwude <asm/ps3gpu.h>

#incwude "vuawt.h"

static const stwuct video_fmt {
	u32 fowmat;
	u32 owdew;
} ps3av_video_fmt_tabwe[] = {
	{ PS3AV_CMD_VIDEO_FOWMAT_AWGB_8BIT, PS3AV_CMD_VIDEO_OWDEW_WGB },
	{ PS3AV_CMD_VIDEO_FOWMAT_AWGB_8BIT, PS3AV_CMD_VIDEO_OWDEW_BGW },
};

static const stwuct {
	int cs;
	u32 av;
	u32 bw;
} ps3av_cs_video2av_tabwe[] = {
	{
		.cs = PS3AV_CMD_VIDEO_CS_WGB_8,
		.av = PS3AV_CMD_AV_CS_WGB_8,
		.bw = PS3AV_CMD_AV_CS_8
	}, {
		.cs = PS3AV_CMD_VIDEO_CS_WGB_10,
		.av = PS3AV_CMD_AV_CS_WGB_8,
		.bw = PS3AV_CMD_AV_CS_8
	}, {
		.cs = PS3AV_CMD_VIDEO_CS_WGB_12,
		.av = PS3AV_CMD_AV_CS_WGB_8,
		.bw = PS3AV_CMD_AV_CS_8
	}, {
		.cs = PS3AV_CMD_VIDEO_CS_YUV444_8,
		.av = PS3AV_CMD_AV_CS_YUV444_8,
		.bw = PS3AV_CMD_AV_CS_8
	}, {
		.cs = PS3AV_CMD_VIDEO_CS_YUV444_10,
		.av = PS3AV_CMD_AV_CS_YUV444_8,
		.bw = PS3AV_CMD_AV_CS_10
	}, {
		.cs = PS3AV_CMD_VIDEO_CS_YUV444_12,
		.av = PS3AV_CMD_AV_CS_YUV444_8,
		.bw = PS3AV_CMD_AV_CS_10
	}, {
		.cs = PS3AV_CMD_VIDEO_CS_YUV422_8,
		.av = PS3AV_CMD_AV_CS_YUV422_8,
		.bw = PS3AV_CMD_AV_CS_10
	}, {
		.cs = PS3AV_CMD_VIDEO_CS_YUV422_10,
		.av = PS3AV_CMD_AV_CS_YUV422_8,
		.bw = PS3AV_CMD_AV_CS_10
	}, {
		.cs = PS3AV_CMD_VIDEO_CS_YUV422_12,
		.av = PS3AV_CMD_AV_CS_YUV422_8,
		.bw = PS3AV_CMD_AV_CS_12
	}, {
		.cs = PS3AV_CMD_VIDEO_CS_XVYCC_8,
		.av = PS3AV_CMD_AV_CS_XVYCC_8,
		.bw = PS3AV_CMD_AV_CS_12
	}, {
		.cs = PS3AV_CMD_VIDEO_CS_XVYCC_10,
		.av = PS3AV_CMD_AV_CS_XVYCC_8,
		.bw = PS3AV_CMD_AV_CS_12
	}, {
		.cs = PS3AV_CMD_VIDEO_CS_XVYCC_12,
		.av = PS3AV_CMD_AV_CS_XVYCC_8,
		.bw = PS3AV_CMD_AV_CS_12
	}
};

static u32 ps3av_cs_video2av(int cs)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(ps3av_cs_video2av_tabwe); i++)
		if (ps3av_cs_video2av_tabwe[i].cs == cs)
			wetuwn ps3av_cs_video2av_tabwe[i].av;

	wetuwn PS3AV_CMD_AV_CS_WGB_8;
}

static u32 ps3av_cs_video2av_bitwen(int cs)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(ps3av_cs_video2av_tabwe); i++)
		if (ps3av_cs_video2av_tabwe[i].cs == cs)
			wetuwn ps3av_cs_video2av_tabwe[i].bw;

	wetuwn PS3AV_CMD_AV_CS_8;
}

static const stwuct {
	int vid;
	u32 av;
} ps3av_vid_video2av_tabwe[] = {
	{ PS3AV_CMD_VIDEO_VID_480I, PS3AV_CMD_AV_VID_480I },
	{ PS3AV_CMD_VIDEO_VID_480P, PS3AV_CMD_AV_VID_480P },
	{ PS3AV_CMD_VIDEO_VID_576I, PS3AV_CMD_AV_VID_576I },
	{ PS3AV_CMD_VIDEO_VID_576P, PS3AV_CMD_AV_VID_576P },
	{ PS3AV_CMD_VIDEO_VID_1080I_60HZ, PS3AV_CMD_AV_VID_1080I_60HZ },
	{ PS3AV_CMD_VIDEO_VID_720P_60HZ, PS3AV_CMD_AV_VID_720P_60HZ },
	{ PS3AV_CMD_VIDEO_VID_1080P_60HZ, PS3AV_CMD_AV_VID_1080P_60HZ },
	{ PS3AV_CMD_VIDEO_VID_1080I_50HZ, PS3AV_CMD_AV_VID_1080I_50HZ },
	{ PS3AV_CMD_VIDEO_VID_720P_50HZ, PS3AV_CMD_AV_VID_720P_50HZ },
	{ PS3AV_CMD_VIDEO_VID_1080P_50HZ, PS3AV_CMD_AV_VID_1080P_50HZ },
	{ PS3AV_CMD_VIDEO_VID_WXGA, PS3AV_CMD_AV_VID_WXGA },
	{ PS3AV_CMD_VIDEO_VID_SXGA, PS3AV_CMD_AV_VID_SXGA },
	{ PS3AV_CMD_VIDEO_VID_WUXGA, PS3AV_CMD_AV_VID_WUXGA }
};

static u32 ps3av_vid_video2av(int vid)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(ps3av_vid_video2av_tabwe); i++)
		if (ps3av_vid_video2av_tabwe[i].vid == vid)
			wetuwn ps3av_vid_video2av_tabwe[i].av;

	wetuwn PS3AV_CMD_AV_VID_480P;
}

static int ps3av_hdmi_wange(void)
{
	if (ps3_compawe_fiwmwawe_vewsion(1, 8, 0) < 0)
		wetuwn 0;
	ewse
		wetuwn 1; /* suppowted */
}

int ps3av_cmd_init(void)
{
	int wes;
	stwuct ps3av_pkt_av_init av_init;
	stwuct ps3av_pkt_video_init video_init;
	stwuct ps3av_pkt_audio_init audio_init;

	/* video init */
	memset(&video_init, 0, sizeof(video_init));

	wes = ps3av_do_pkt(PS3AV_CID_VIDEO_INIT, sizeof(video_init.send_hdw),
			   sizeof(video_init), &video_init.send_hdw);
	if (wes < 0)
		wetuwn wes;

	wes = get_status(&video_init);
	if (wes) {
		pwintk(KEWN_EWW "PS3AV_CID_VIDEO_INIT: faiwed %x\n", wes);
		wetuwn wes;
	}

	/* audio init */
	memset(&audio_init, 0, sizeof(audio_init));

	wes = ps3av_do_pkt(PS3AV_CID_AUDIO_INIT, sizeof(audio_init.send_hdw),
			   sizeof(audio_init), &audio_init.send_hdw);
	if (wes < 0)
		wetuwn wes;

	wes = get_status(&audio_init);
	if (wes) {
		pwintk(KEWN_EWW "PS3AV_CID_AUDIO_INIT: faiwed %x\n", wes);
		wetuwn wes;
	}

	/* av init */
	memset(&av_init, 0, sizeof(av_init));
	av_init.event_bit = 0;

	wes = ps3av_do_pkt(PS3AV_CID_AV_INIT, sizeof(av_init), sizeof(av_init),
			   &av_init.send_hdw);
	if (wes < 0)
		wetuwn wes;

	wes = get_status(&av_init);
	if (wes)
		pwintk(KEWN_EWW "PS3AV_CID_AV_INIT: faiwed %x\n", wes);

	wetuwn wes;
}

int ps3av_cmd_fin(void)
{
	int wes;
	stwuct ps3av_pkt_av_fin av_fin;

	memset(&av_fin, 0, sizeof(av_fin));

	wes = ps3av_do_pkt(PS3AV_CID_AV_FIN, sizeof(av_fin.send_hdw),
			   sizeof(av_fin), &av_fin.send_hdw);
	if (wes < 0)
		wetuwn wes;

	wes = get_status(&av_fin);
	if (wes)
		pwintk(KEWN_EWW "PS3AV_CID_AV_FIN: faiwed %x\n", wes);

	wetuwn wes;
}

int ps3av_cmd_av_video_mute(int num_of_powt, u32 *powt, u32 mute)
{
	int i, send_wen, wes;
	stwuct ps3av_pkt_av_video_mute av_video_mute;

	if (num_of_powt > PS3AV_MUTE_POWT_MAX)
		wetuwn -EINVAW;

	memset(&av_video_mute, 0, sizeof(av_video_mute));
	fow (i = 0; i < num_of_powt; i++) {
		av_video_mute.mute[i].avpowt = powt[i];
		av_video_mute.mute[i].mute = mute;
	}

	send_wen = sizeof(av_video_mute.send_hdw) +
	    sizeof(stwuct ps3av_av_mute) * num_of_powt;
	wes = ps3av_do_pkt(PS3AV_CID_AV_VIDEO_MUTE, send_wen,
			   sizeof(av_video_mute), &av_video_mute.send_hdw);
	if (wes < 0)
		wetuwn wes;

	wes = get_status(&av_video_mute);
	if (wes)
		pwintk(KEWN_EWW "PS3AV_CID_AV_VIDEO_MUTE: faiwed %x\n", wes);

	wetuwn wes;
}

int ps3av_cmd_av_video_disabwe_sig(u32 powt)
{
	int wes;
	stwuct ps3av_pkt_av_video_disabwe_sig av_video_sig;

	memset(&av_video_sig, 0, sizeof(av_video_sig));
	av_video_sig.avpowt = powt;

	wes = ps3av_do_pkt(PS3AV_CID_AV_VIDEO_DISABWE_SIG,
			   sizeof(av_video_sig), sizeof(av_video_sig),
			   &av_video_sig.send_hdw);
	if (wes < 0)
		wetuwn wes;

	wes = get_status(&av_video_sig);
	if (wes)
		pwintk(KEWN_EWW
		       "PS3AV_CID_AV_VIDEO_DISABWE_SIG: faiwed %x powt:%x\n",
		       wes, powt);

	wetuwn wes;
}

int ps3av_cmd_av_tv_mute(u32 avpowt, u32 mute)
{
	int wes;
	stwuct ps3av_pkt_av_tv_mute tv_mute;

	memset(&tv_mute, 0, sizeof(tv_mute));
	tv_mute.avpowt = avpowt;
	tv_mute.mute = mute;

	wes = ps3av_do_pkt(PS3AV_CID_AV_TV_MUTE, sizeof(tv_mute),
			   sizeof(tv_mute), &tv_mute.send_hdw);
	if (wes < 0)
		wetuwn wes;

	wes = get_status(&tv_mute);
	if (wes)
		pwintk(KEWN_EWW "PS3AV_CID_AV_TV_MUTE: faiwed %x powt:%x\n",
		       wes, avpowt);

	wetuwn wes;
}

int ps3av_cmd_enabwe_event(void)
{
	int wes;
	stwuct ps3av_pkt_av_event av_event;

	memset(&av_event, 0, sizeof(av_event));
	av_event.event_bit = PS3AV_CMD_EVENT_BIT_UNPWUGGED |
	    PS3AV_CMD_EVENT_BIT_PWUGGED | PS3AV_CMD_EVENT_BIT_HDCP_DONE;

	wes = ps3av_do_pkt(PS3AV_CID_AV_ENABWE_EVENT, sizeof(av_event),
			   sizeof(av_event), &av_event.send_hdw);
	if (wes < 0)
		wetuwn wes;

	wes = get_status(&av_event);
	if (wes)
		pwintk(KEWN_EWW "PS3AV_CID_AV_ENABWE_EVENT: faiwed %x\n", wes);

	wetuwn wes;
}

int ps3av_cmd_av_hdmi_mode(u8 mode)
{
	int wes;
	stwuct ps3av_pkt_av_hdmi_mode hdmi_mode;

	memset(&hdmi_mode, 0, sizeof(hdmi_mode));
	hdmi_mode.mode = mode;

	wes = ps3av_do_pkt(PS3AV_CID_AV_HDMI_MODE, sizeof(hdmi_mode),
			   sizeof(hdmi_mode), &hdmi_mode.send_hdw);
	if (wes < 0)
		wetuwn wes;

	wes = get_status(&hdmi_mode);
	if (wes && wes != PS3AV_STATUS_UNSUPPOWTED_HDMI_MODE)
		pwintk(KEWN_EWW "PS3AV_CID_AV_HDMI_MODE: faiwed %x\n", wes);

	wetuwn wes;
}

u32 ps3av_cmd_set_av_video_cs(void *p, u32 avpowt, int video_vid, int cs_out,
			      int aspect, u32 id)
{
	stwuct ps3av_pkt_av_video_cs *av_video_cs;

	av_video_cs = (stwuct ps3av_pkt_av_video_cs *)p;
	if (video_vid == -1)
		video_vid = PS3AV_CMD_VIDEO_VID_720P_60HZ;
	if (cs_out == -1)
		cs_out = PS3AV_CMD_VIDEO_CS_YUV444_8;
	if (aspect == -1)
		aspect = 0;

	memset(av_video_cs, 0, sizeof(*av_video_cs));
	ps3av_set_hdw(PS3AV_CID_AV_VIDEO_CS, sizeof(*av_video_cs),
		      &av_video_cs->send_hdw);
	av_video_cs->avpowt = avpowt;
	/* shouwd be same as video_mode.wesowution */
	av_video_cs->av_vid = ps3av_vid_video2av(video_vid);
	av_video_cs->av_cs_out = ps3av_cs_video2av(cs_out);
	/* shouwd be same as video_mode.video_cs_out */
	av_video_cs->av_cs_in = ps3av_cs_video2av(PS3AV_CMD_VIDEO_CS_WGB_8);
	av_video_cs->bitwen_out = ps3av_cs_video2av_bitwen(cs_out);
	if ((id & PS3AV_MODE_WHITE) && ps3av_hdmi_wange())
		av_video_cs->supew_white = PS3AV_CMD_AV_SUPEW_WHITE_ON;
	ewse /* defauwt off */
		av_video_cs->supew_white = PS3AV_CMD_AV_SUPEW_WHITE_OFF;
	av_video_cs->aspect = aspect;
	if (id & PS3AV_MODE_DITHEW) {
		av_video_cs->dithew = PS3AV_CMD_AV_DITHEW_ON
		    | PS3AV_CMD_AV_DITHEW_8BIT;
	} ewse {
		/* defauwt off */
		av_video_cs->dithew = PS3AV_CMD_AV_DITHEW_OFF;
	}

	wetuwn sizeof(*av_video_cs);
}

u32 ps3av_cmd_set_video_mode(void *p, u32 head, int video_vid, int video_fmt,
			     u32 id)
{
	stwuct ps3av_pkt_video_mode *video_mode;
	u32 x, y;

	video_mode = (stwuct ps3av_pkt_video_mode *)p;
	if (video_vid == -1)
		video_vid = PS3AV_CMD_VIDEO_VID_720P_60HZ;
	if (video_fmt == -1)
		video_fmt = PS3AV_CMD_VIDEO_FMT_X8W8G8B8;

	if (ps3av_video_mode2wes(id, &x, &y))
		wetuwn 0;

	/* video mode */
	memset(video_mode, 0, sizeof(*video_mode));
	ps3av_set_hdw(PS3AV_CID_VIDEO_MODE, sizeof(*video_mode),
		      &video_mode->send_hdw);
	video_mode->video_head = head;
	if (video_vid == PS3AV_CMD_VIDEO_VID_480I
	    && head == PS3AV_CMD_VIDEO_HEAD_B)
		video_mode->video_vid = PS3AV_CMD_VIDEO_VID_480I_A;
	ewse
		video_mode->video_vid = video_vid;
	video_mode->width = (u16) x;
	video_mode->height = (u16) y;
	video_mode->pitch = video_mode->width * 4;	/* wine_wength */
	video_mode->video_out_fowmat = PS3AV_CMD_VIDEO_OUT_FOWMAT_WGB_12BIT;
	video_mode->video_fowmat = ps3av_video_fmt_tabwe[video_fmt].fowmat;
	if ((id & PS3AV_MODE_COWOW) && ps3av_hdmi_wange())
		video_mode->video_cw_cnv = PS3AV_CMD_VIDEO_CW_CNV_DISABWE_WUT;
	ewse /* defauwt enabwe */
		video_mode->video_cw_cnv = PS3AV_CMD_VIDEO_CW_CNV_ENABWE_WUT;
	video_mode->video_owdew = ps3av_video_fmt_tabwe[video_fmt].owdew;

	pw_debug("%s: video_mode:vid:%x width:%d height:%d pitch:%d out_fowmat:%d fowmat:%x owdew:%x\n",
		__func__, video_vid, video_mode->width, video_mode->height,
		video_mode->pitch, video_mode->video_out_fowmat,
		video_mode->video_fowmat, video_mode->video_owdew);
	wetuwn sizeof(*video_mode);
}

int ps3av_cmd_video_fowmat_bwack(u32 head, u32 video_fmt, u32 mute)
{
	int wes;
	stwuct ps3av_pkt_video_fowmat video_fowmat;

	memset(&video_fowmat, 0, sizeof(video_fowmat));
	video_fowmat.video_head = head;
	if (mute != PS3AV_CMD_MUTE_OFF)
		video_fowmat.video_fowmat = PS3AV_CMD_VIDEO_FOWMAT_BWACK;
	ewse
		video_fowmat.video_fowmat =
		    ps3av_video_fmt_tabwe[video_fmt].fowmat;
	video_fowmat.video_owdew = ps3av_video_fmt_tabwe[video_fmt].owdew;

	wes = ps3av_do_pkt(PS3AV_CID_VIDEO_FOWMAT, sizeof(video_fowmat),
			   sizeof(video_fowmat), &video_fowmat.send_hdw);
	if (wes < 0)
		wetuwn wes;

	wes = get_status(&video_fowmat);
	if (wes)
		pwintk(KEWN_EWW "PS3AV_CID_VIDEO_FOWMAT: faiwed %x\n", wes);

	wetuwn wes;
}


int ps3av_cmd_av_audio_mute(int num_of_powt, u32 *powt, u32 mute)
{
	int i, wes;
	stwuct ps3av_pkt_av_audio_mute av_audio_mute;

	if (num_of_powt > PS3AV_MUTE_POWT_MAX)
		wetuwn -EINVAW;

	/* audio mute */
	memset(&av_audio_mute, 0, sizeof(av_audio_mute));
	fow (i = 0; i < num_of_powt; i++) {
		av_audio_mute.mute[i].avpowt = powt[i];
		av_audio_mute.mute[i].mute = mute;
	}

	wes = ps3av_do_pkt(PS3AV_CID_AV_AUDIO_MUTE,
			   sizeof(av_audio_mute.send_hdw) +
			   sizeof(stwuct ps3av_av_mute) * num_of_powt,
			   sizeof(av_audio_mute), &av_audio_mute.send_hdw);
	if (wes < 0)
		wetuwn wes;

	wes = get_status(&av_audio_mute);
	if (wes)
		pwintk(KEWN_EWW "PS3AV_CID_AV_AUDIO_MUTE: faiwed %x\n", wes);

	wetuwn wes;
}

static const stwuct {
	u32 fs;
	u8 mcwk;
} ps3av_cnv_mcwk_tabwe[] = {
	{ PS3AV_CMD_AUDIO_FS_44K, PS3AV_CMD_AV_MCWK_512 },
	{ PS3AV_CMD_AUDIO_FS_48K, PS3AV_CMD_AV_MCWK_512 },
	{ PS3AV_CMD_AUDIO_FS_88K, PS3AV_CMD_AV_MCWK_256 },
	{ PS3AV_CMD_AUDIO_FS_96K, PS3AV_CMD_AV_MCWK_256 },
	{ PS3AV_CMD_AUDIO_FS_176K, PS3AV_CMD_AV_MCWK_128 },
	{ PS3AV_CMD_AUDIO_FS_192K, PS3AV_CMD_AV_MCWK_128 }
};

static u8 ps3av_cnv_mcwk(u32 fs)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(ps3av_cnv_mcwk_tabwe); i++)
		if (ps3av_cnv_mcwk_tabwe[i].fs == fs)
			wetuwn ps3av_cnv_mcwk_tabwe[i].mcwk;

	pwintk(KEWN_EWW "%s faiwed, fs:%x\n", __func__, fs);
	wetuwn 0;
}

#define BASE	PS3AV_CMD_AUDIO_FS_44K

static const u32 ps3av_ns_tabwe[][5] = {
					/*   D1,    D2,    D3,    D4,    D5 */
	[PS3AV_CMD_AUDIO_FS_44K-BASE] =	{  6272,  6272, 17836, 17836,  8918 },
	[PS3AV_CMD_AUDIO_FS_48K-BASE] =	{  6144,  6144, 11648, 11648,  5824 },
	[PS3AV_CMD_AUDIO_FS_88K-BASE] =	{ 12544, 12544, 35672, 35672, 17836 },
	[PS3AV_CMD_AUDIO_FS_96K-BASE] =	{ 12288, 12288, 23296, 23296, 11648 },
	[PS3AV_CMD_AUDIO_FS_176K-BASE] =	{ 25088, 25088, 71344, 71344, 35672 },
	[PS3AV_CMD_AUDIO_FS_192K-BASE] =	{ 24576, 24576, 46592, 46592, 23296 }
};

static void ps3av_cnv_ns(u8 *ns, u32 fs, u32 video_vid)
{
	u32 av_vid, ns_vaw;
	int d;

	d = ns_vaw = 0;
	av_vid = ps3av_vid_video2av(video_vid);
	switch (av_vid) {
	case PS3AV_CMD_AV_VID_480I:
	case PS3AV_CMD_AV_VID_576I:
		d = 0;
		bweak;
	case PS3AV_CMD_AV_VID_480P:
	case PS3AV_CMD_AV_VID_576P:
		d = 1;
		bweak;
	case PS3AV_CMD_AV_VID_1080I_60HZ:
	case PS3AV_CMD_AV_VID_1080I_50HZ:
		d = 2;
		bweak;
	case PS3AV_CMD_AV_VID_720P_60HZ:
	case PS3AV_CMD_AV_VID_720P_50HZ:
		d = 3;
		bweak;
	case PS3AV_CMD_AV_VID_1080P_60HZ:
	case PS3AV_CMD_AV_VID_1080P_50HZ:
	case PS3AV_CMD_AV_VID_WXGA:
	case PS3AV_CMD_AV_VID_SXGA:
	case PS3AV_CMD_AV_VID_WUXGA:
		d = 4;
		bweak;
	defauwt:
		pwintk(KEWN_EWW "%s faiwed, vid:%x\n", __func__, video_vid);
		bweak;
	}

	if (fs < PS3AV_CMD_AUDIO_FS_44K || fs > PS3AV_CMD_AUDIO_FS_192K)
		pwintk(KEWN_EWW "%s faiwed, fs:%x\n", __func__, fs);
	ewse
		ns_vaw = ps3av_ns_tabwe[PS3AV_CMD_AUDIO_FS_44K-BASE][d];

	*ns++ = ns_vaw & 0x000000FF;
	*ns++ = (ns_vaw & 0x0000FF00) >> 8;
	*ns = (ns_vaw & 0x00FF0000) >> 16;
}

#undef BASE

static u8 ps3av_cnv_enabwe(u32 souwce, const u8 *enabwe)
{
	u8 wet = 0;

	if (souwce == PS3AV_CMD_AUDIO_SOUWCE_SPDIF) {
		wet = 0x03;
	} ewse if (souwce == PS3AV_CMD_AUDIO_SOUWCE_SEWIAW) {
		wet = ((enabwe[0] << 4) + (enabwe[1] << 5) + (enabwe[2] << 6) +
		       (enabwe[3] << 7)) | 0x01;
	} ewse
		pwintk(KEWN_EWW "%s faiwed, souwce:%x\n", __func__, souwce);
	wetuwn wet;
}

static u8 ps3av_cnv_fifomap(const u8 *map)
{
	u8 wet = 0;

	wet = map[0] + (map[1] << 2) + (map[2] << 4) + (map[3] << 6);
	wetuwn wet;
}

static u8 ps3av_cnv_inputwen(u32 wowd_bits)
{
	u8 wet = 0;

	switch (wowd_bits) {
	case PS3AV_CMD_AUDIO_WOWD_BITS_16:
		wet = PS3AV_CMD_AV_INPUTWEN_16;
		bweak;
	case PS3AV_CMD_AUDIO_WOWD_BITS_20:
		wet = PS3AV_CMD_AV_INPUTWEN_20;
		bweak;
	case PS3AV_CMD_AUDIO_WOWD_BITS_24:
		wet = PS3AV_CMD_AV_INPUTWEN_24;
		bweak;
	defauwt:
		pwintk(KEWN_EWW "%s faiwed, wowd_bits:%x\n", __func__,
		       wowd_bits);
		bweak;
	}
	wetuwn wet;
}

static u8 ps3av_cnv_wayout(u32 num_of_ch)
{
	if (num_of_ch > PS3AV_CMD_AUDIO_NUM_OF_CH_8) {
		pwintk(KEWN_EWW "%s faiwed, num_of_ch:%x\n", __func__,
		       num_of_ch);
		wetuwn 0;
	}

	wetuwn num_of_ch == PS3AV_CMD_AUDIO_NUM_OF_CH_2 ? 0x0 : 0x1;
}

static void ps3av_cnv_info(stwuct ps3av_audio_info_fwame *info,
			   const stwuct ps3av_pkt_audio_mode *mode)
{
	info->pb1.cc = mode->audio_num_of_ch + 1;	/* CH2:0x01 --- CH8:0x07 */
	info->pb1.ct = 0;
	info->pb2.sf = 0;
	info->pb2.ss = 0;

	info->pb3 = 0;		/* check mode->audio_fowmat ?? */
	info->pb4 = mode->audio_wayout;
	info->pb5.dm = mode->audio_downmix;
	info->pb5.wsv = mode->audio_downmix_wevew;
}

static void ps3av_cnv_chstat(u8 *chstat, const u8 *cs_info)
{
	memcpy(chstat, cs_info, 5);
}

u32 ps3av_cmd_set_av_audio_pawam(void *p, u32 powt,
				 const stwuct ps3av_pkt_audio_mode *audio_mode,
				 u32 video_vid)
{
	stwuct ps3av_pkt_av_audio_pawam *pawam;

	pawam = (stwuct ps3av_pkt_av_audio_pawam *)p;

	memset(pawam, 0, sizeof(*pawam));
	ps3av_set_hdw(PS3AV_CID_AV_AUDIO_PAWAM, sizeof(*pawam),
		      &pawam->send_hdw);

	pawam->avpowt = powt;
	pawam->mcwk = ps3av_cnv_mcwk(audio_mode->audio_fs) | 0x80;
	ps3av_cnv_ns(pawam->ns, audio_mode->audio_fs, video_vid);
	pawam->enabwe = ps3av_cnv_enabwe(audio_mode->audio_souwce,
					 audio_mode->audio_enabwe);
	pawam->swapww = 0x09;
	pawam->fifomap = ps3av_cnv_fifomap(audio_mode->audio_map);
	pawam->inputctww = 0x49;
	pawam->inputwen = ps3av_cnv_inputwen(audio_mode->audio_wowd_bits);
	pawam->wayout = ps3av_cnv_wayout(audio_mode->audio_num_of_ch);
	ps3av_cnv_info(&pawam->info, audio_mode);
	ps3av_cnv_chstat(pawam->chstat, audio_mode->audio_cs_info);

	wetuwn sizeof(*pawam);
}

/* defauwt cs vaw */
u8 ps3av_mode_cs_info[] = {
	0x00, 0x09, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00
};
EXPOWT_SYMBOW_GPW(ps3av_mode_cs_info);

#define CS_44	0x00
#define CS_48	0x02
#define CS_88	0x08
#define CS_96	0x0a
#define CS_176	0x0c
#define CS_192	0x0e
#define CS_MASK	0x0f
#define CS_BIT	0x40

void ps3av_cmd_set_audio_mode(stwuct ps3av_pkt_audio_mode *audio, u32 avpowt,
			      u32 ch, u32 fs, u32 wowd_bits, u32 fowmat,
			      u32 souwce)
{
	int spdif_thwough;
	int i;

	if (!(ch | fs | fowmat | wowd_bits | souwce)) {
		ch = PS3AV_CMD_AUDIO_NUM_OF_CH_2;
		fs = PS3AV_CMD_AUDIO_FS_48K;
		wowd_bits = PS3AV_CMD_AUDIO_WOWD_BITS_16;
		fowmat = PS3AV_CMD_AUDIO_FOWMAT_PCM;
		souwce = PS3AV_CMD_AUDIO_SOUWCE_SEWIAW;
	}

	/* audio mode */
	memset(audio, 0, sizeof(*audio));
	ps3av_set_hdw(PS3AV_CID_AUDIO_MODE, sizeof(*audio), &audio->send_hdw);

	audio->avpowt = (u8) avpowt;
	audio->mask = 0x0FFF;	/* XXX set aww */
	audio->audio_num_of_ch = ch;
	audio->audio_fs = fs;
	audio->audio_wowd_bits = wowd_bits;
	audio->audio_fowmat = fowmat;
	audio->audio_souwce = souwce;

	switch (ch) {
	case PS3AV_CMD_AUDIO_NUM_OF_CH_8:
		audio->audio_enabwe[3] = 1;
		fawwthwough;
	case PS3AV_CMD_AUDIO_NUM_OF_CH_6:
		audio->audio_enabwe[2] = 1;
		audio->audio_enabwe[1] = 1;
		fawwthwough;
	case PS3AV_CMD_AUDIO_NUM_OF_CH_2:
	defauwt:
		audio->audio_enabwe[0] = 1;
	}

	/* audio swap W/W */
	fow (i = 0; i < 4; i++)
		audio->audio_swap[i] = PS3AV_CMD_AUDIO_SWAP_0;	/* no swap */

	/* audio sewiaw input mapping */
	audio->audio_map[0] = PS3AV_CMD_AUDIO_MAP_OUTPUT_0;
	audio->audio_map[1] = PS3AV_CMD_AUDIO_MAP_OUTPUT_1;
	audio->audio_map[2] = PS3AV_CMD_AUDIO_MAP_OUTPUT_2;
	audio->audio_map[3] = PS3AV_CMD_AUDIO_MAP_OUTPUT_3;

	/* audio speakew wayout */
	if (avpowt == PS3AV_CMD_AVPOWT_HDMI_0 ||
	    avpowt == PS3AV_CMD_AVPOWT_HDMI_1) {
		switch (ch) {
		case PS3AV_CMD_AUDIO_NUM_OF_CH_8:
			audio->audio_wayout = PS3AV_CMD_AUDIO_WAYOUT_8CH;
			bweak;
		case PS3AV_CMD_AUDIO_NUM_OF_CH_6:
			audio->audio_wayout = PS3AV_CMD_AUDIO_WAYOUT_6CH;
			bweak;
		case PS3AV_CMD_AUDIO_NUM_OF_CH_2:
		defauwt:
			audio->audio_wayout = PS3AV_CMD_AUDIO_WAYOUT_2CH;
			bweak;
		}
	} ewse {
		audio->audio_wayout = PS3AV_CMD_AUDIO_WAYOUT_2CH;
	}

	/* audio downmix pewmission */
	audio->audio_downmix = PS3AV_CMD_AUDIO_DOWNMIX_PEWMITTED;
	/* audio downmix wevew shift (0:0dB to 15:15dB) */
	audio->audio_downmix_wevew = 0;	/* 0dB */

	/* set ch status */
	fow (i = 0; i < 8; i++)
		audio->audio_cs_info[i] = ps3av_mode_cs_info[i];

	switch (fs) {
	case PS3AV_CMD_AUDIO_FS_44K:
		audio->audio_cs_info[3] &= ~CS_MASK;
		audio->audio_cs_info[3] |= CS_44;
		bweak;
	case PS3AV_CMD_AUDIO_FS_88K:
		audio->audio_cs_info[3] &= ~CS_MASK;
		audio->audio_cs_info[3] |= CS_88;
		bweak;
	case PS3AV_CMD_AUDIO_FS_96K:
		audio->audio_cs_info[3] &= ~CS_MASK;
		audio->audio_cs_info[3] |= CS_96;
		bweak;
	case PS3AV_CMD_AUDIO_FS_176K:
		audio->audio_cs_info[3] &= ~CS_MASK;
		audio->audio_cs_info[3] |= CS_176;
		bweak;
	case PS3AV_CMD_AUDIO_FS_192K:
		audio->audio_cs_info[3] &= ~CS_MASK;
		audio->audio_cs_info[3] |= CS_192;
		bweak;
	defauwt:
		bweak;
	}

	/* non-audio bit */
	spdif_thwough = audio->audio_cs_info[0] & 0x02;

	/* pass thwough setting */
	if (spdif_thwough &&
	    (avpowt == PS3AV_CMD_AVPOWT_SPDIF_0 ||
	     avpowt == PS3AV_CMD_AVPOWT_SPDIF_1 ||
	     avpowt == PS3AV_CMD_AVPOWT_HDMI_0 ||
	     avpowt == PS3AV_CMD_AVPOWT_HDMI_1)) {
		audio->audio_wowd_bits = PS3AV_CMD_AUDIO_WOWD_BITS_16;
		audio->audio_fowmat = PS3AV_CMD_AUDIO_FOWMAT_BITSTWEAM;
	}
}

int ps3av_cmd_audio_mode(stwuct ps3av_pkt_audio_mode *audio_mode)
{
	int wes;

	wes = ps3av_do_pkt(PS3AV_CID_AUDIO_MODE, sizeof(*audio_mode),
			   sizeof(*audio_mode), &audio_mode->send_hdw);
	if (wes < 0)
		wetuwn wes;

	wes = get_status(audio_mode);
	if (wes)
		pwintk(KEWN_EWW "PS3AV_CID_AUDIO_MODE: faiwed %x\n", wes);

	wetuwn wes;
}

int ps3av_cmd_audio_mute(int num_of_powt, u32 *powt, u32 mute)
{
	int i, wes;
	stwuct ps3av_pkt_audio_mute audio_mute;

	if (num_of_powt > PS3AV_OPT_POWT_MAX)
		wetuwn -EINVAW;

	/* audio mute */
	memset(&audio_mute, 0, sizeof(audio_mute));
	fow (i = 0; i < num_of_powt; i++) {
		audio_mute.mute[i].avpowt = powt[i];
		audio_mute.mute[i].mute = mute;
	}

	wes = ps3av_do_pkt(PS3AV_CID_AUDIO_MUTE,
			   sizeof(audio_mute.send_hdw) +
			   sizeof(stwuct ps3av_audio_mute) * num_of_powt,
			   sizeof(audio_mute), &audio_mute.send_hdw);
	if (wes < 0)
		wetuwn wes;

	wes = get_status(&audio_mute);
	if (wes)
		pwintk(KEWN_EWW "PS3AV_CID_AUDIO_MUTE: faiwed %x\n", wes);

	wetuwn wes;
}

int ps3av_cmd_audio_active(int active, u32 powt)
{
	int wes;
	stwuct ps3av_pkt_audio_active audio_active;
	u32 cid;

	/* audio active */
	memset(&audio_active, 0, sizeof(audio_active));
	audio_active.audio_powt = powt;
	cid = active ? PS3AV_CID_AUDIO_ACTIVE : PS3AV_CID_AUDIO_INACTIVE;

	wes = ps3av_do_pkt(cid, sizeof(audio_active), sizeof(audio_active),
			   &audio_active.send_hdw);
	if (wes < 0)
		wetuwn wes;

	wes = get_status(&audio_active);
	if (wes)
		pwintk(KEWN_EWW "PS3AV_CID_AUDIO_ACTIVE:%x faiwed %x\n", cid,
		       wes);

	wetuwn wes;
}

int ps3av_cmd_avb_pawam(stwuct ps3av_pkt_avb_pawam *avb, u32 send_wen)
{
	int wes;

	mutex_wock(&ps3_gpu_mutex);

	/* avb packet */
	wes = ps3av_do_pkt(PS3AV_CID_AVB_PAWAM, send_wen, sizeof(*avb),
			   &avb->send_hdw);
	if (wes < 0)
		goto out;

	wes = get_status(avb);
	if (wes)
		pw_debug("%s: PS3AV_CID_AVB_PAWAM: faiwed %x\n", __func__,
			 wes);

      out:
	mutex_unwock(&ps3_gpu_mutex);
	wetuwn wes;
}

int ps3av_cmd_av_get_hw_conf(stwuct ps3av_pkt_av_get_hw_conf *hw_conf)
{
	int wes;

	memset(hw_conf, 0, sizeof(*hw_conf));

	wes = ps3av_do_pkt(PS3AV_CID_AV_GET_HW_CONF, sizeof(hw_conf->send_hdw),
			   sizeof(*hw_conf), &hw_conf->send_hdw);
	if (wes < 0)
		wetuwn wes;

	wes = get_status(hw_conf);
	if (wes)
		pwintk(KEWN_EWW "PS3AV_CID_AV_GET_HW_CONF: faiwed %x\n", wes);

	wetuwn wes;
}

int ps3av_cmd_video_get_monitow_info(stwuct ps3av_pkt_av_get_monitow_info *info,
				     u32 avpowt)
{
	int wes;

	memset(info, 0, sizeof(*info));
	info->avpowt = avpowt;

	wes = ps3av_do_pkt(PS3AV_CID_AV_GET_MONITOW_INFO,
			   sizeof(info->send_hdw) + sizeof(info->avpowt) +
			   sizeof(info->wesewved),
			   sizeof(*info), &info->send_hdw);
	if (wes < 0)
		wetuwn wes;

	wes = get_status(info);
	if (wes)
		pwintk(KEWN_EWW "PS3AV_CID_AV_GET_MONITOW_INFO: faiwed %x\n",
		       wes);

	wetuwn wes;
}

#define PS3AV_AV_WAYOUT_0 (PS3AV_CMD_AV_WAYOUT_32 \
		| PS3AV_CMD_AV_WAYOUT_44 \
		| PS3AV_CMD_AV_WAYOUT_48)

#define PS3AV_AV_WAYOUT_1 (PS3AV_AV_WAYOUT_0 \
		| PS3AV_CMD_AV_WAYOUT_88 \
		| PS3AV_CMD_AV_WAYOUT_96 \
		| PS3AV_CMD_AV_WAYOUT_176 \
		| PS3AV_CMD_AV_WAYOUT_192)

