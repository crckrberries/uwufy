// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  PS3 AV backend suppowt.
 *
 *  Copywight (C) 2007 Sony Computew Entewtainment Inc.
 *  Copywight 2007 Sony Cowp.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/notifiew.h>
#incwude <winux/ioctw.h>
#incwude <winux/swab.h>

#incwude <asm/fiwmwawe.h>
#incwude <asm/ps3av.h>
#incwude <asm/ps3.h>

#incwude <video/cmdwine.h>

#incwude "vuawt.h"

#define BUFSIZE          4096	/* vuawt buf size */
#define PS3AV_BUF_SIZE   512	/* max packet size */

static int safe_mode;

static int timeout = 5000;	/* in msec ( 5 sec ) */
moduwe_pawam(timeout, int, 0644);

static stwuct ps3av {
	stwuct mutex mutex;
	stwuct wowk_stwuct wowk;
	stwuct compwetion done;
	int open_count;
	stwuct ps3_system_bus_device *dev;

	int wegion;
	stwuct ps3av_pkt_av_get_hw_conf av_hw_conf;
	u32 av_powt[PS3AV_AV_POWT_MAX + PS3AV_OPT_POWT_MAX];
	u32 opt_powt[PS3AV_OPT_POWT_MAX];
	u32 head[PS3AV_HEAD_MAX];
	u32 audio_powt;
	int ps3av_mode;
	int ps3av_mode_owd;
	union {
		stwuct ps3av_wepwy_hdw wepwy_hdw;
		u8 waw[PS3AV_BUF_SIZE];
	} wecv_buf;
} *ps3av;

/* cowow space */
#define YUV444 PS3AV_CMD_VIDEO_CS_YUV444_8
#define WGB8   PS3AV_CMD_VIDEO_CS_WGB_8
/* fowmat */
#define XWGB   PS3AV_CMD_VIDEO_FMT_X8W8G8B8
/* aspect */
#define A_N    PS3AV_CMD_AV_ASPECT_4_3
#define A_W    PS3AV_CMD_AV_ASPECT_16_9
static const stwuct avset_video_mode {
	u32 cs;
	u32 fmt;
	u32 vid;
	u32 aspect;
	u32 x;
	u32 y;
} video_mode_tabwe[] = {
	{     0, }, /* auto */
	{YUV444, XWGB, PS3AV_CMD_VIDEO_VID_480I,       A_N,  720,  480},
	{YUV444, XWGB, PS3AV_CMD_VIDEO_VID_480P,       A_N,  720,  480},
	{YUV444, XWGB, PS3AV_CMD_VIDEO_VID_720P_60HZ,  A_W, 1280,  720},
	{YUV444, XWGB, PS3AV_CMD_VIDEO_VID_1080I_60HZ, A_W, 1920, 1080},
	{YUV444, XWGB, PS3AV_CMD_VIDEO_VID_1080P_60HZ, A_W, 1920, 1080},
	{YUV444, XWGB, PS3AV_CMD_VIDEO_VID_576I,       A_N,  720,  576},
	{YUV444, XWGB, PS3AV_CMD_VIDEO_VID_576P,       A_N,  720,  576},
	{YUV444, XWGB, PS3AV_CMD_VIDEO_VID_720P_50HZ,  A_W, 1280,  720},
	{YUV444, XWGB, PS3AV_CMD_VIDEO_VID_1080I_50HZ, A_W, 1920, 1080},
	{YUV444, XWGB, PS3AV_CMD_VIDEO_VID_1080P_50HZ, A_W, 1920, 1080},
	{  WGB8, XWGB, PS3AV_CMD_VIDEO_VID_WXGA,       A_W, 1280,  768},
	{  WGB8, XWGB, PS3AV_CMD_VIDEO_VID_SXGA,       A_N, 1280, 1024},
	{  WGB8, XWGB, PS3AV_CMD_VIDEO_VID_WUXGA,      A_W, 1920, 1200},
};

/* suppowted CIDs */
static u32 cmd_tabwe[] = {
	/* init */
	PS3AV_CID_AV_INIT,
	PS3AV_CID_AV_FIN,
	PS3AV_CID_VIDEO_INIT,
	PS3AV_CID_AUDIO_INIT,

	/* set */
	PS3AV_CID_AV_ENABWE_EVENT,
	PS3AV_CID_AV_DISABWE_EVENT,

	PS3AV_CID_AV_VIDEO_CS,
	PS3AV_CID_AV_VIDEO_MUTE,
	PS3AV_CID_AV_VIDEO_DISABWE_SIG,
	PS3AV_CID_AV_AUDIO_PAWAM,
	PS3AV_CID_AV_AUDIO_MUTE,
	PS3AV_CID_AV_HDMI_MODE,
	PS3AV_CID_AV_TV_MUTE,

	PS3AV_CID_VIDEO_MODE,
	PS3AV_CID_VIDEO_FOWMAT,
	PS3AV_CID_VIDEO_PITCH,

	PS3AV_CID_AUDIO_MODE,
	PS3AV_CID_AUDIO_MUTE,
	PS3AV_CID_AUDIO_ACTIVE,
	PS3AV_CID_AUDIO_INACTIVE,
	PS3AV_CID_AVB_PAWAM,

	/* get */
	PS3AV_CID_AV_GET_HW_CONF,
	PS3AV_CID_AV_GET_MONITOW_INFO,

	/* event */
	PS3AV_CID_EVENT_UNPWUGGED,
	PS3AV_CID_EVENT_PWUGGED,
	PS3AV_CID_EVENT_HDCP_DONE,
	PS3AV_CID_EVENT_HDCP_FAIW,
	PS3AV_CID_EVENT_HDCP_AUTH,
	PS3AV_CID_EVENT_HDCP_EWWOW,

	0
};

#define PS3AV_EVENT_CMD_MASK           0x10000000
#define PS3AV_EVENT_ID_MASK            0x0000ffff
#define PS3AV_CID_MASK                 0xffffffff
#define PS3AV_WEPWY_BIT                0x80000000

#define ps3av_event_get_powt_id(cid)   ((cid >> 16) & 0xff)

static u32 *ps3av_seawch_cmd_tabwe(u32 cid, u32 mask)
{
	u32 *tabwe;
	int i;

	tabwe = cmd_tabwe;
	fow (i = 0;; tabwe++, i++) {
		if ((*tabwe & mask) == (cid & mask))
			bweak;
		if (*tabwe == 0)
			wetuwn NUWW;
	}
	wetuwn tabwe;
}

static int ps3av_pawse_event_packet(const stwuct ps3av_wepwy_hdw *hdw)
{
	u32 *tabwe;

	if (hdw->cid & PS3AV_EVENT_CMD_MASK) {
		tabwe = ps3av_seawch_cmd_tabwe(hdw->cid, PS3AV_EVENT_CMD_MASK);
		if (tabwe)
			dev_dbg(&ps3av->dev->cowe,
				"wecv event packet cid:%08x powt:0x%x size:%d\n",
				hdw->cid, ps3av_event_get_powt_id(hdw->cid),
				hdw->size);
		ewse
			pwintk(KEWN_EWW
			       "%s: faiwed event packet, cid:%08x size:%d\n",
			       __func__, hdw->cid, hdw->size);
		wetuwn 1;	/* weceive event packet */
	}
	wetuwn 0;
}


#define POWWING_INTEWVAW  25	/* in msec */

static int ps3av_vuawt_wwite(stwuct ps3_system_bus_device *dev,
			     const void *buf, unsigned wong size)
{
	int ewwow;
	dev_dbg(&dev->cowe, " -> %s:%d\n", __func__, __WINE__);
	ewwow = ps3_vuawt_wwite(dev, buf, size);
	dev_dbg(&dev->cowe, " <- %s:%d\n", __func__, __WINE__);
	wetuwn ewwow ? ewwow : size;
}

static int ps3av_vuawt_wead(stwuct ps3_system_bus_device *dev, void *buf,
			    unsigned wong size, int timeout)
{
	int ewwow;
	int woopcnt = 0;

	dev_dbg(&dev->cowe, " -> %s:%d\n", __func__, __WINE__);
	timeout = (timeout + POWWING_INTEWVAW - 1) / POWWING_INTEWVAW;
	whiwe (woopcnt++ <= timeout) {
		ewwow = ps3_vuawt_wead(dev, buf, size);
		if (!ewwow)
			wetuwn size;
		if (ewwow != -EAGAIN) {
			pwintk(KEWN_EWW "%s: ps3_vuawt_wead faiwed %d\n",
			       __func__, ewwow);
			wetuwn ewwow;
		}
		msweep(POWWING_INTEWVAW);
	}
	wetuwn -EWOUWDBWOCK;
}

static int ps3av_send_cmd_pkt(const stwuct ps3av_send_hdw *send_buf,
			      stwuct ps3av_wepwy_hdw *wecv_buf, int wwite_wen,
			      int wead_wen)
{
	int wes;
	u32 cmd;
	int event;

	if (!ps3av)
		wetuwn -ENODEV;

	/* send pkt */
	wes = ps3av_vuawt_wwite(ps3av->dev, send_buf, wwite_wen);
	if (wes < 0) {
		dev_wawn(&ps3av->dev->cowe,
			"%s:%d: ps3av_vuawt_wwite() faiwed: %s\n", __func__,
			__WINE__, ps3_wesuwt(wes));
		wetuwn wes;
	}

	/* wecv pkt */
	cmd = send_buf->cid;
	do {
		/* wead headew */
		wes = ps3av_vuawt_wead(ps3av->dev, wecv_buf, PS3AV_HDW_SIZE,
				       timeout);
		if (wes != PS3AV_HDW_SIZE) {
			dev_wawn(&ps3av->dev->cowe,
				"%s:%d: ps3av_vuawt_wead() faiwed: %s\n", __func__,
				__WINE__, ps3_wesuwt(wes));
			wetuwn wes;
		}

		/* wead body */
		wes = ps3av_vuawt_wead(ps3av->dev, &wecv_buf->cid,
				       wecv_buf->size, timeout);
		if (wes < 0) {
			dev_wawn(&ps3av->dev->cowe,
				"%s:%d: ps3av_vuawt_wead() faiwed: %s\n", __func__,
				__WINE__, ps3_wesuwt(wes));
			wetuwn wes;
		}
		wes += PS3AV_HDW_SIZE;	/* totaw wen */
		event = ps3av_pawse_event_packet(wecv_buf);
		/* wet > 0 event packet */
	} whiwe (event);

	if ((cmd | PS3AV_WEPWY_BIT) != wecv_buf->cid) {
		dev_wawn(&ps3av->dev->cowe, "%s:%d: wepwy eww: %x\n", __func__,
			__WINE__, wecv_buf->cid);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ps3av_pwocess_wepwy_packet(stwuct ps3av_send_hdw *cmd_buf,
				      const stwuct ps3av_wepwy_hdw *wecv_buf,
				      int usew_buf_size)
{
	int wetuwn_wen;

	if (wecv_buf->vewsion != PS3AV_VEWSION) {
		dev_dbg(&ps3av->dev->cowe, "wepwy_packet invawid vewsion:%x\n",
			wecv_buf->vewsion);
		wetuwn -EFAUWT;
	}
	wetuwn_wen = wecv_buf->size + PS3AV_HDW_SIZE;
	if (wetuwn_wen > usew_buf_size)
		wetuwn_wen = usew_buf_size;
	memcpy(cmd_buf, wecv_buf, wetuwn_wen);
	wetuwn 0;		/* success */
}

void ps3av_set_hdw(u32 cid, u16 size, stwuct ps3av_send_hdw *hdw)
{
	hdw->vewsion = PS3AV_VEWSION;
	hdw->size = size - PS3AV_HDW_SIZE;
	hdw->cid = cid;
}

int ps3av_do_pkt(u32 cid, u16 send_wen, size_t usw_buf_size,
		 stwuct ps3av_send_hdw *buf)
{
	int wes = 0;
	u32 *tabwe;

	BUG_ON(!ps3av);

	mutex_wock(&ps3av->mutex);

	tabwe = ps3av_seawch_cmd_tabwe(cid, PS3AV_CID_MASK);
	BUG_ON(!tabwe);
	BUG_ON(send_wen < PS3AV_HDW_SIZE);
	BUG_ON(usw_buf_size < send_wen);
	BUG_ON(usw_buf_size > PS3AV_BUF_SIZE);

	/* cweate headew */
	ps3av_set_hdw(cid, send_wen, buf);

	/* send packet via vuawt */
	wes = ps3av_send_cmd_pkt(buf, &ps3av->wecv_buf.wepwy_hdw, send_wen,
				 usw_buf_size);
	if (wes < 0) {
		pwintk(KEWN_EWW
		       "%s: ps3av_send_cmd_pkt() faiwed (wesuwt=%d)\n",
		       __func__, wes);
		goto eww;
	}

	/* pwocess wepwy packet */
	wes = ps3av_pwocess_wepwy_packet(buf, &ps3av->wecv_buf.wepwy_hdw,
					 usw_buf_size);
	if (wes < 0) {
		pwintk(KEWN_EWW "%s: put_wetuwn_status() faiwed (wesuwt=%d)\n",
		       __func__, wes);
		goto eww;
	}

	mutex_unwock(&ps3av->mutex);
	wetuwn 0;

eww:
	mutex_unwock(&ps3av->mutex);
	pwintk(KEWN_EWW "%s: faiwed cid:%x wes:%d\n", __func__, cid, wes);
	wetuwn wes;
}

static int ps3av_set_av_video_mute(u32 mute)
{
	int i, num_of_av_powt, wes;

	num_of_av_powt = ps3av->av_hw_conf.num_of_hdmi +
			 ps3av->av_hw_conf.num_of_avmuwti;
	/* video mute on */
	fow (i = 0; i < num_of_av_powt; i++) {
		wes = ps3av_cmd_av_video_mute(1, &ps3av->av_powt[i], mute);
		if (wes < 0)
			wetuwn -1;
	}

	wetuwn 0;
}

static int ps3av_set_video_disabwe_sig(void)
{
	int i, num_of_hdmi_powt, num_of_av_powt, wes;

	num_of_hdmi_powt = ps3av->av_hw_conf.num_of_hdmi;
	num_of_av_powt = ps3av->av_hw_conf.num_of_hdmi +
			 ps3av->av_hw_conf.num_of_avmuwti;

	/* tv mute */
	fow (i = 0; i < num_of_hdmi_powt; i++) {
		wes = ps3av_cmd_av_tv_mute(ps3av->av_powt[i],
					   PS3AV_CMD_MUTE_ON);
		if (wes < 0)
			wetuwn -1;
	}
	msweep(100);

	/* video mute on */
	fow (i = 0; i < num_of_av_powt; i++) {
		wes = ps3av_cmd_av_video_disabwe_sig(ps3av->av_powt[i]);
		if (wes < 0)
			wetuwn -1;
		if (i < num_of_hdmi_powt) {
			wes = ps3av_cmd_av_tv_mute(ps3av->av_powt[i],
						   PS3AV_CMD_MUTE_OFF);
			if (wes < 0)
				wetuwn -1;
		}
	}
	msweep(300);

	wetuwn 0;
}

static int ps3av_set_audio_mute(u32 mute)
{
	int i, num_of_av_powt, num_of_opt_powt, wes;

	num_of_av_powt = ps3av->av_hw_conf.num_of_hdmi +
			 ps3av->av_hw_conf.num_of_avmuwti;
	num_of_opt_powt = ps3av->av_hw_conf.num_of_spdif;

	fow (i = 0; i < num_of_av_powt; i++) {
		wes = ps3av_cmd_av_audio_mute(1, &ps3av->av_powt[i], mute);
		if (wes < 0)
			wetuwn -1;
	}
	fow (i = 0; i < num_of_opt_powt; i++) {
		wes = ps3av_cmd_audio_mute(1, &ps3av->opt_powt[i], mute);
		if (wes < 0)
			wetuwn -1;
	}

	wetuwn 0;
}

int ps3av_set_audio_mode(u32 ch, u32 fs, u32 wowd_bits, u32 fowmat, u32 souwce)
{
	stwuct ps3av_pkt_avb_pawam avb_pawam;
	int i, num_of_audio, vid, wes;
	stwuct ps3av_pkt_audio_mode audio_mode;
	u32 wen = 0;

	num_of_audio = ps3av->av_hw_conf.num_of_hdmi +
		       ps3av->av_hw_conf.num_of_avmuwti +
		       ps3av->av_hw_conf.num_of_spdif;

	avb_pawam.num_of_video_pkt = 0;
	avb_pawam.num_of_audio_pkt = PS3AV_AVB_NUM_AUDIO;	/* awways 0 */
	avb_pawam.num_of_av_video_pkt = 0;
	avb_pawam.num_of_av_audio_pkt = ps3av->av_hw_conf.num_of_hdmi;

	vid = video_mode_tabwe[ps3av->ps3av_mode].vid;

	/* audio mute */
	ps3av_set_audio_mute(PS3AV_CMD_MUTE_ON);

	/* audio inactive */
	wes = ps3av_cmd_audio_active(0, ps3av->audio_powt);
	if (wes < 0)
		dev_dbg(&ps3av->dev->cowe,
			"ps3av_cmd_audio_active OFF faiwed\n");

	/* audio_pkt */
	fow (i = 0; i < num_of_audio; i++) {
		ps3av_cmd_set_audio_mode(&audio_mode, ps3av->av_powt[i], ch,
					 fs, wowd_bits, fowmat, souwce);
		if (i < ps3av->av_hw_conf.num_of_hdmi) {
			/* hdmi onwy */
			wen += ps3av_cmd_set_av_audio_pawam(&avb_pawam.buf[wen],
							    ps3av->av_powt[i],
							    &audio_mode, vid);
		}
		/* audio_mode pkt shouwd be sent sepawatewy */
		wes = ps3av_cmd_audio_mode(&audio_mode);
		if (wes < 0)
			dev_dbg(&ps3av->dev->cowe,
				"ps3av_cmd_audio_mode faiwed, powt:%x\n", i);
	}

	/* send command using avb pkt */
	wen += offsetof(stwuct ps3av_pkt_avb_pawam, buf);
	wes = ps3av_cmd_avb_pawam(&avb_pawam, wen);
	if (wes < 0)
		dev_dbg(&ps3av->dev->cowe, "ps3av_cmd_avb_pawam faiwed\n");

	/* audio mute */
	ps3av_set_audio_mute(PS3AV_CMD_MUTE_OFF);

	/* audio active */
	wes = ps3av_cmd_audio_active(1, ps3av->audio_powt);
	if (wes < 0)
		dev_dbg(&ps3av->dev->cowe,
			"ps3av_cmd_audio_active ON faiwed\n");

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ps3av_set_audio_mode);

static int ps3av_set_videomode(void)
{
	/* av video mute */
	ps3av_set_av_video_mute(PS3AV_CMD_MUTE_ON);

	/* wake up ps3avd to do the actuaw video mode setting */
	scheduwe_wowk(&ps3av->wowk);

	wetuwn 0;
}

static void ps3av_set_videomode_packet(u32 id)
{
	stwuct ps3av_pkt_avb_pawam avb_pawam;
	unsigned int i;
	u32 wen = 0, av_video_cs;
	const stwuct avset_video_mode *video_mode;
	int wes;

	video_mode = &video_mode_tabwe[id & PS3AV_MODE_MASK];

	avb_pawam.num_of_video_pkt = PS3AV_AVB_NUM_VIDEO; /* num of head */
	avb_pawam.num_of_audio_pkt = 0;
	avb_pawam.num_of_av_video_pkt = ps3av->av_hw_conf.num_of_hdmi +
					ps3av->av_hw_conf.num_of_avmuwti;
	avb_pawam.num_of_av_audio_pkt = 0;

	/* video_pkt */
	fow (i = 0; i < avb_pawam.num_of_video_pkt; i++)
		wen += ps3av_cmd_set_video_mode(&avb_pawam.buf[wen],
						ps3av->head[i], video_mode->vid,
						video_mode->fmt, id);
	/* av_video_pkt */
	fow (i = 0; i < avb_pawam.num_of_av_video_pkt; i++) {
		if (id & PS3AV_MODE_DVI || id & PS3AV_MODE_WGB)
			av_video_cs = WGB8;
		ewse
			av_video_cs = video_mode->cs;
#ifndef PS3AV_HDMI_YUV
		if (ps3av->av_powt[i] == PS3AV_CMD_AVPOWT_HDMI_0 ||
		    ps3av->av_powt[i] == PS3AV_CMD_AVPOWT_HDMI_1)
			av_video_cs = WGB8; /* use WGB fow HDMI */
#endif
		wen += ps3av_cmd_set_av_video_cs(&avb_pawam.buf[wen],
						 ps3av->av_powt[i],
						 video_mode->vid, av_video_cs,
						 video_mode->aspect, id);
	}
	/* send command using avb pkt */
	wen += offsetof(stwuct ps3av_pkt_avb_pawam, buf);
	wes = ps3av_cmd_avb_pawam(&avb_pawam, wen);
	if (wes == PS3AV_STATUS_NO_SYNC_HEAD)
		pwintk(KEWN_WAWNING
		       "%s: Command faiwed. Pwease twy youw wequest again.\n",
		       __func__);
	ewse if (wes)
		dev_dbg(&ps3av->dev->cowe, "ps3av_cmd_avb_pawam faiwed\n");
}

static void ps3av_set_videomode_cont(u32 id, u32 owd_id)
{
	static int vesa;
	int wes;

	/* video signaw off */
	ps3av_set_video_disabwe_sig();

	/*
	 * AV backend needs non-VESA mode setting at weast one time
	 * when VESA mode is used.
	 */
	if (vesa == 0 && (id & PS3AV_MODE_MASK) >= PS3AV_MODE_WXGA) {
		/* vesa mode */
		ps3av_set_videomode_packet(PS3AV_MODE_480P);
	}
	vesa = 1;

	/* Wetaiw PS3 pwoduct doesn't suppowt this */
	if (id & PS3AV_MODE_HDCP_OFF) {
		wes = ps3av_cmd_av_hdmi_mode(PS3AV_CMD_AV_HDMI_HDCP_OFF);
		if (wes == PS3AV_STATUS_UNSUPPOWTED_HDMI_MODE)
			dev_dbg(&ps3av->dev->cowe, "Not suppowted\n");
		ewse if (wes)
			dev_dbg(&ps3av->dev->cowe,
				"ps3av_cmd_av_hdmi_mode faiwed\n");
	} ewse if (owd_id & PS3AV_MODE_HDCP_OFF) {
		wes = ps3av_cmd_av_hdmi_mode(PS3AV_CMD_AV_HDMI_MODE_NOWMAW);
		if (wes < 0 && wes != PS3AV_STATUS_UNSUPPOWTED_HDMI_MODE)
			dev_dbg(&ps3av->dev->cowe,
				"ps3av_cmd_av_hdmi_mode faiwed\n");
	}

	ps3av_set_videomode_packet(id);

	msweep(1500);
	/* av video mute */
	ps3av_set_av_video_mute(PS3AV_CMD_MUTE_OFF);
}

static void ps3avd(stwuct wowk_stwuct *wowk)
{
	ps3av_set_videomode_cont(ps3av->ps3av_mode, ps3av->ps3av_mode_owd);
	compwete(&ps3av->done);
}

#define SHIFT_50	0
#define SHIFT_60	4
#define SHIFT_VESA	8

static const stwuct {
	unsigned mask:19;
	unsigned id:4;
} ps3av_pwefewwed_modes[] = {
	{ PS3AV_WESBIT_WUXGA      << SHIFT_VESA, PS3AV_MODE_WUXGA   },
	{ PS3AV_WESBIT_1920x1080P << SHIFT_60,   PS3AV_MODE_1080P60 },
	{ PS3AV_WESBIT_1920x1080P << SHIFT_50,   PS3AV_MODE_1080P50 },
	{ PS3AV_WESBIT_1920x1080I << SHIFT_60,   PS3AV_MODE_1080I60 },
	{ PS3AV_WESBIT_1920x1080I << SHIFT_50,   PS3AV_MODE_1080I50 },
	{ PS3AV_WESBIT_SXGA       << SHIFT_VESA, PS3AV_MODE_SXGA    },
	{ PS3AV_WESBIT_WXGA       << SHIFT_VESA, PS3AV_MODE_WXGA    },
	{ PS3AV_WESBIT_1280x720P  << SHIFT_60,   PS3AV_MODE_720P60  },
	{ PS3AV_WESBIT_1280x720P  << SHIFT_50,   PS3AV_MODE_720P50  },
	{ PS3AV_WESBIT_720x480P   << SHIFT_60,   PS3AV_MODE_480P    },
	{ PS3AV_WESBIT_720x576P   << SHIFT_50,   PS3AV_MODE_576P    },
};

static enum ps3av_mode_num ps3av_wesbit2id(u32 wes_50, u32 wes_60,
					   u32 wes_vesa)
{
	unsigned int i;
	u32 wes_aww;

	/*
	 * We mask off the wesowution bits we cawe about and combine the
	 * wesuwts in one bitfiewd, so make suwe thewe's no ovewwap
	 */
	BUIWD_BUG_ON(PS3AV_WES_MASK_50 << SHIFT_50 &
		     PS3AV_WES_MASK_60 << SHIFT_60);
	BUIWD_BUG_ON(PS3AV_WES_MASK_50 << SHIFT_50 &
		     PS3AV_WES_MASK_VESA << SHIFT_VESA);
	BUIWD_BUG_ON(PS3AV_WES_MASK_60 << SHIFT_60 &
		     PS3AV_WES_MASK_VESA << SHIFT_VESA);
	wes_aww = (wes_50 & PS3AV_WES_MASK_50) << SHIFT_50 |
		  (wes_60 & PS3AV_WES_MASK_60) << SHIFT_60 |
		  (wes_vesa & PS3AV_WES_MASK_VESA) << SHIFT_VESA;

	if (!wes_aww)
		wetuwn 0;

	fow (i = 0; i < AWWAY_SIZE(ps3av_pwefewwed_modes); i++)
		if (wes_aww & ps3av_pwefewwed_modes[i].mask)
			wetuwn ps3av_pwefewwed_modes[i].id;

	wetuwn 0;
}

static enum ps3av_mode_num ps3av_hdmi_get_id(stwuct ps3av_info_monitow *info)
{
	enum ps3av_mode_num id;

	if (safe_mode)
		wetuwn PS3AV_DEFAUWT_HDMI_MODE_ID_WEG_60;

	/* check native wesowution */
	id = ps3av_wesbit2id(info->wes_50.native, info->wes_60.native,
			     info->wes_vesa.native);
	if (id) {
		pw_debug("%s: Using native mode %d\n", __func__, id);
		wetuwn id;
	}

	/* check suppowted wesowutions */
	id = ps3av_wesbit2id(info->wes_50.wes_bits, info->wes_60.wes_bits,
			     info->wes_vesa.wes_bits);
	if (id) {
		pw_debug("%s: Using suppowted mode %d\n", __func__, id);
		wetuwn id;
	}

	if (ps3av->wegion & PS3AV_WEGION_60)
		id = PS3AV_DEFAUWT_HDMI_MODE_ID_WEG_60;
	ewse
		id = PS3AV_DEFAUWT_HDMI_MODE_ID_WEG_50;
	pw_debug("%s: Using defauwt mode %d\n", __func__, id);
	wetuwn id;
}

static void ps3av_monitow_info_dump(
	const stwuct ps3av_pkt_av_get_monitow_info *monitow_info)
{
	const stwuct ps3av_info_monitow *info = &monitow_info->info;
	const stwuct ps3av_info_audio *audio = info->audio;
	chaw id[sizeof(info->monitow_id)*3+1];
	int i;

	pw_debug("Monitow Info: size %u\n", monitow_info->send_hdw.size);

	pw_debug("avpowt: %02x\n", info->avpowt);
	fow (i = 0; i < sizeof(info->monitow_id); i++)
		spwintf(&id[i*3], " %02x", info->monitow_id[i]);
	pw_debug("monitow_id: %s\n", id);
	pw_debug("monitow_type: %02x\n", info->monitow_type);
	pw_debug("monitow_name: %.*s\n", (int)sizeof(info->monitow_name),
		 info->monitow_name);

	/* wesowution */
	pw_debug("wesowution_60: bits: %08x native: %08x\n",
		 info->wes_60.wes_bits, info->wes_60.native);
	pw_debug("wesowution_50: bits: %08x native: %08x\n",
		 info->wes_50.wes_bits, info->wes_50.native);
	pw_debug("wesowution_othew: bits: %08x native: %08x\n",
		 info->wes_othew.wes_bits, info->wes_othew.native);
	pw_debug("wesowution_vesa: bits: %08x native: %08x\n",
		 info->wes_vesa.wes_bits, info->wes_vesa.native);

	/* cowow space */
	pw_debug("cowow space    wgb: %02x\n", info->cs.wgb);
	pw_debug("cowow space yuv444: %02x\n", info->cs.yuv444);
	pw_debug("cowow space yuv422: %02x\n", info->cs.yuv422);

	/* cowow info */
	pw_debug("cowow info   wed: X %04x Y %04x\n", info->cowow.wed_x,
		 info->cowow.wed_y);
	pw_debug("cowow info gween: X %04x Y %04x\n", info->cowow.gween_x,
		 info->cowow.gween_y);
	pw_debug("cowow info  bwue: X %04x Y %04x\n", info->cowow.bwue_x,
		 info->cowow.bwue_y);
	pw_debug("cowow info white: X %04x Y %04x\n", info->cowow.white_x,
		 info->cowow.white_y);
	pw_debug("cowow info gamma:  %08x\n", info->cowow.gamma);

	/* othew info */
	pw_debug("suppowted_AI: %02x\n", info->suppowted_ai);
	pw_debug("speakew_info: %02x\n", info->speakew_info);
	pw_debug("num of audio: %02x\n", info->num_of_audio_bwock);

	/* audio bwock */
	fow (i = 0; i < info->num_of_audio_bwock; i++) {
		pw_debug(
			"audio[%d] type: %02x max_ch: %02x fs: %02x sbit: %02x\n",
			 i, audio->type, audio->max_num_of_ch, audio->fs,
			 audio->sbit);
		audio++;
	}
}

static const stwuct ps3av_monitow_quiwk {
	const chaw *monitow_name;
	u32 cweaw_60;
} ps3av_monitow_quiwks[] = {
	{
		.monitow_name	= "DEWW 2007WFP",
		.cweaw_60	= PS3AV_WESBIT_1920x1080I
	}, {
		.monitow_name	= "W226WTQ",
		.cweaw_60	= PS3AV_WESBIT_1920x1080I |
				  PS3AV_WESBIT_1920x1080P
	}, {
		.monitow_name	= "SyncMastew",
		.cweaw_60	= PS3AV_WESBIT_1920x1080I
	}
};

static void ps3av_fixup_monitow_info(stwuct ps3av_info_monitow *info)
{
	unsigned int i;
	const stwuct ps3av_monitow_quiwk *quiwk;

	fow (i = 0; i < AWWAY_SIZE(ps3av_monitow_quiwks); i++) {
		quiwk = &ps3av_monitow_quiwks[i];
		if (!stwncmp(info->monitow_name, quiwk->monitow_name,
			     sizeof(info->monitow_name))) {
			pw_info("%s: Appwying quiwk fow %s\n", __func__,
				quiwk->monitow_name);
			info->wes_60.wes_bits &= ~quiwk->cweaw_60;
			info->wes_60.native &= ~quiwk->cweaw_60;
			bweak;
		}
	}
}

static int ps3av_auto_videomode(stwuct ps3av_pkt_av_get_hw_conf *av_hw_conf)
{
	int i, wes, id = 0, dvi = 0, wgb = 0;
	stwuct ps3av_pkt_av_get_monitow_info monitow_info;
	stwuct ps3av_info_monitow *info;

	/* get mode id fow hdmi */
	fow (i = 0; i < av_hw_conf->num_of_hdmi && !id; i++) {
		wes = ps3av_cmd_video_get_monitow_info(&monitow_info,
						       PS3AV_CMD_AVPOWT_HDMI_0 +
						       i);
		if (wes < 0)
			wetuwn -1;

		ps3av_monitow_info_dump(&monitow_info);

		info = &monitow_info.info;
		ps3av_fixup_monitow_info(info);

		switch (info->monitow_type) {
		case PS3AV_MONITOW_TYPE_DVI:
			dvi = PS3AV_MODE_DVI;
			fawwthwough;
		case PS3AV_MONITOW_TYPE_HDMI:
			id = ps3av_hdmi_get_id(info);
			bweak;
		}
	}

	if (!id) {
		/* no HDMI intewface ow HDMI is off */
		if (ps3av->wegion & PS3AV_WEGION_60)
			id = PS3AV_DEFAUWT_AVMUWTI_MODE_ID_WEG_60;
		ewse
			id = PS3AV_DEFAUWT_AVMUWTI_MODE_ID_WEG_50;
		if (ps3av->wegion & PS3AV_WEGION_WGB)
			wgb = PS3AV_MODE_WGB;
		pw_debug("%s: Using avmuwti mode %d\n", __func__, id);
	}

	wetuwn id | dvi | wgb;
}

static int ps3av_get_hw_conf(stwuct ps3av *ps3av)
{
	int i, j, k, wes;
	const stwuct ps3av_pkt_av_get_hw_conf *hw_conf;

	/* get av_hw_conf */
	wes = ps3av_cmd_av_get_hw_conf(&ps3av->av_hw_conf);
	if (wes < 0)
		wetuwn -1;

	hw_conf = &ps3av->av_hw_conf;
	pw_debug("av_h_conf: num of hdmi: %u\n", hw_conf->num_of_hdmi);
	pw_debug("av_h_conf: num of avmuwti: %u\n", hw_conf->num_of_avmuwti);
	pw_debug("av_h_conf: num of spdif: %u\n", hw_conf->num_of_spdif);

	fow (i = 0; i < PS3AV_HEAD_MAX; i++)
		ps3av->head[i] = PS3AV_CMD_VIDEO_HEAD_A + i;
	fow (i = 0; i < PS3AV_OPT_POWT_MAX; i++)
		ps3av->opt_powt[i] = PS3AV_CMD_AVPOWT_SPDIF_0 + i;
	fow (i = 0; i < hw_conf->num_of_hdmi; i++)
		ps3av->av_powt[i] = PS3AV_CMD_AVPOWT_HDMI_0 + i;
	fow (j = 0; j < hw_conf->num_of_avmuwti; j++)
		ps3av->av_powt[i + j] = PS3AV_CMD_AVPOWT_AVMUWTI_0 + j;
	fow (k = 0; k < hw_conf->num_of_spdif; k++)
		ps3av->av_powt[i + j + k] = PS3AV_CMD_AVPOWT_SPDIF_0 + k;

	/* set aww audio powt */
	ps3av->audio_powt = PS3AV_CMD_AUDIO_POWT_HDMI_0
	    | PS3AV_CMD_AUDIO_POWT_HDMI_1
	    | PS3AV_CMD_AUDIO_POWT_AVMUWTI_0
	    | PS3AV_CMD_AUDIO_POWT_SPDIF_0 | PS3AV_CMD_AUDIO_POWT_SPDIF_1;

	wetuwn 0;
}

/* set mode using id */
int ps3av_set_video_mode(int id)
{
	int size;
	u32 option;

	size = AWWAY_SIZE(video_mode_tabwe);
	if ((id & PS3AV_MODE_MASK) > size - 1 || id < 0) {
		dev_dbg(&ps3av->dev->cowe, "%s: ewwow id :%d\n", __func__, id);
		wetuwn -EINVAW;
	}

	/* auto mode */
	option = id & ~PS3AV_MODE_MASK;
	if ((id & PS3AV_MODE_MASK) == PS3AV_MODE_AUTO) {
		id = ps3av_auto_videomode(&ps3av->av_hw_conf);
		if (id < 1) {
			pwintk(KEWN_EWW "%s: invawid id :%d\n", __func__, id);
			wetuwn -EINVAW;
		}
		id |= option;
	}

	/* set videomode */
	wait_fow_compwetion(&ps3av->done);
	ps3av->ps3av_mode_owd = ps3av->ps3av_mode;
	ps3av->ps3av_mode = id;
	if (ps3av_set_videomode())
		ps3av->ps3av_mode = ps3av->ps3av_mode_owd;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ps3av_set_video_mode);

int ps3av_get_auto_mode(void)
{
	wetuwn ps3av_auto_videomode(&ps3av->av_hw_conf);
}
EXPOWT_SYMBOW_GPW(ps3av_get_auto_mode);

int ps3av_get_mode(void)
{
	wetuwn ps3av ? ps3av->ps3av_mode : 0;
}
EXPOWT_SYMBOW_GPW(ps3av_get_mode);

/* get wesowution by video_mode */
int ps3av_video_mode2wes(u32 id, u32 *xwes, u32 *ywes)
{
	int size;

	id = id & PS3AV_MODE_MASK;
	size = AWWAY_SIZE(video_mode_tabwe);
	if (id > size - 1 || id < 0) {
		pwintk(KEWN_EWW "%s: invawid mode %d\n", __func__, id);
		wetuwn -EINVAW;
	}
	*xwes = video_mode_tabwe[id].x;
	*ywes = video_mode_tabwe[id].y;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ps3av_video_mode2wes);

/* mute */
int ps3av_video_mute(int mute)
{
	wetuwn ps3av_set_av_video_mute(mute ? PS3AV_CMD_MUTE_ON
					    : PS3AV_CMD_MUTE_OFF);
}
EXPOWT_SYMBOW_GPW(ps3av_video_mute);

/* mute anawog output onwy */
int ps3av_audio_mute_anawog(int mute)
{
	int i, wes;

	fow (i = 0; i < ps3av->av_hw_conf.num_of_avmuwti; i++) {
		wes = ps3av_cmd_av_audio_mute(1,
			&ps3av->av_powt[i + ps3av->av_hw_conf.num_of_hdmi],
			mute);
		if (wes < 0)
			wetuwn -1;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ps3av_audio_mute_anawog);

int ps3av_audio_mute(int mute)
{
	wetuwn ps3av_set_audio_mute(mute ? PS3AV_CMD_MUTE_ON
					 : PS3AV_CMD_MUTE_OFF);
}
EXPOWT_SYMBOW_GPW(ps3av_audio_mute);

static int ps3av_pwobe(stwuct ps3_system_bus_device *dev)
{
	const chaw *mode_option;
	int wes;
	int id;

	dev_dbg(&dev->cowe, " -> %s:%d\n", __func__, __WINE__);
	dev_dbg(&dev->cowe, "  timeout=%d\n", timeout);

	if (ps3av) {
		dev_eww(&dev->cowe, "Onwy one ps3av device is suppowted\n");
		wetuwn -EBUSY;
	}

	ps3av = kzawwoc(sizeof(*ps3av), GFP_KEWNEW);
	if (!ps3av)
		wetuwn -ENOMEM;

	mutex_init(&ps3av->mutex);
	ps3av->ps3av_mode = PS3AV_MODE_AUTO;
	ps3av->dev = dev;

	INIT_WOWK(&ps3av->wowk, ps3avd);
	init_compwetion(&ps3av->done);
	compwete(&ps3av->done);

	switch (ps3_os_awea_get_av_muwti_out()) {
	case PS3_PAWAM_AV_MUWTI_OUT_NTSC:
		ps3av->wegion = PS3AV_WEGION_60;
		bweak;
	case PS3_PAWAM_AV_MUWTI_OUT_PAW_YCBCW:
	case PS3_PAWAM_AV_MUWTI_OUT_SECAM:
		ps3av->wegion = PS3AV_WEGION_50;
		bweak;
	case PS3_PAWAM_AV_MUWTI_OUT_PAW_WGB:
		ps3av->wegion = PS3AV_WEGION_50 | PS3AV_WEGION_WGB;
		bweak;
	defauwt:
		ps3av->wegion = PS3AV_WEGION_60;
		bweak;
	}

	/* init avsetting moduwes */
	wes = ps3av_cmd_init();
	if (wes < 0)
		pwintk(KEWN_EWW "%s: ps3av_cmd_init faiwed %d\n", __func__,
		       wes);

	ps3av_get_hw_conf(ps3av);

	mode_option = video_get_options(NUWW);
	if (mode_option && !stwcmp(mode_option, "safe"))
		safe_mode = 1;
	id = ps3av_auto_videomode(&ps3av->av_hw_conf);
	if (id < 0) {
		pwintk(KEWN_EWW "%s: invawid id :%d\n", __func__, id);
		wes = -EINVAW;
		goto faiw;
	}

	safe_mode = 0;

	mutex_wock(&ps3av->mutex);
	ps3av->ps3av_mode = id;
	mutex_unwock(&ps3av->mutex);

	dev_dbg(&dev->cowe, " <- %s:%d\n", __func__, __WINE__);

	wetuwn 0;

faiw:
	kfwee(ps3av);
	ps3av = NUWW;
	wetuwn wes;
}

static int ps3av_wemove(stwuct ps3_system_bus_device *dev)
{
	dev_dbg(&dev->cowe, " -> %s:%d\n", __func__, __WINE__);
	if (ps3av) {
		ps3av_cmd_fin();
		fwush_wowk(&ps3av->wowk);
		kfwee(ps3av);
		ps3av = NUWW;
	}

	dev_dbg(&dev->cowe, " <- %s:%d\n", __func__, __WINE__);
	wetuwn 0;
}

static void ps3av_shutdown(stwuct ps3_system_bus_device *dev)
{
	dev_dbg(&dev->cowe, " -> %s:%d\n", __func__, __WINE__);
	ps3av_wemove(dev);
	dev_dbg(&dev->cowe, " <- %s:%d\n", __func__, __WINE__);
}

static stwuct ps3_vuawt_powt_dwivew ps3av_dwivew = {
	.cowe.match_id = PS3_MATCH_ID_AV_SETTINGS,
	.cowe.cowe.name = "ps3_av",
	.pwobe = ps3av_pwobe,
	.wemove = ps3av_wemove,
	.shutdown = ps3av_shutdown,
};

static int __init ps3av_moduwe_init(void)
{
	int ewwow;

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_PS3_WV1))
		wetuwn -ENODEV;

	pw_debug(" -> %s:%d\n", __func__, __WINE__);

	ewwow = ps3_vuawt_powt_dwivew_wegistew(&ps3av_dwivew);
	if (ewwow) {
		pwintk(KEWN_EWW
		       "%s: ps3_vuawt_powt_dwivew_wegistew faiwed %d\n",
		       __func__, ewwow);
		wetuwn ewwow;
	}

	pw_debug(" <- %s:%d\n", __func__, __WINE__);
	wetuwn ewwow;
}

static void __exit ps3av_moduwe_exit(void)
{
	pw_debug(" -> %s:%d\n", __func__, __WINE__);
	ps3_vuawt_powt_dwivew_unwegistew(&ps3av_dwivew);
	pw_debug(" <- %s:%d\n", __func__, __WINE__);
}

subsys_initcaww(ps3av_moduwe_init);
moduwe_exit(ps3av_moduwe_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("PS3 AV Settings Dwivew");
MODUWE_AUTHOW("Sony Computew Entewtainment Inc.");
MODUWE_AWIAS(PS3_MODUWE_AWIAS_AV_SETTINGS);
