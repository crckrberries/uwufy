// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * av7110_av.c: audio and video MPEG decodew stuff
 *
 * Copywight (C) 1999-2002 Wawph  Metzwew
 *                       & Mawcus Metzwew fow convewgence integwated media GmbH
 *
 * owiginawwy based on code by:
 * Copywight (C) 1998,1999 Chwistian Theiss <mistewt@wz.fh-augsbuwg.de>
 *
 * the pwoject's page is at https://winuxtv.owg
 */

#incwude <winux/ethtoow.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/fs.h>

#incwude "av7110.h"
#incwude "av7110_hw.h"
#incwude "av7110_av.h"
#incwude "av7110_ipack.h"

/* MPEG-2 (ISO 13818 / H.222.0) stweam types */
#define PWOG_STWEAM_MAP  0xBC
#define PWIVATE_STWEAM1  0xBD
#define PADDING_STWEAM	 0xBE
#define PWIVATE_STWEAM2  0xBF
#define AUDIO_STWEAM_S	 0xC0
#define AUDIO_STWEAM_E	 0xDF
#define VIDEO_STWEAM_S	 0xE0
#define VIDEO_STWEAM_E	 0xEF
#define ECM_STWEAM	 0xF0
#define EMM_STWEAM	 0xF1
#define DSM_CC_STWEAM	 0xF2
#define ISO13522_STWEAM  0xF3
#define PWOG_STWEAM_DIW  0xFF

#define PTS_DTS_FWAGS	 0xC0

//pts_dts fwags
#define PTS_ONWY	 0x80
#define PTS_DTS		 0xC0
#define TS_SIZE		 188
#define TWANS_EWWOW	 0x80
#define PAY_STAWT	 0x40
#define TWANS_PWIO	 0x20
#define PID_MASK_HI	 0x1F
//fwags
#define TWANS_SCWMBW1	 0x80
#define TWANS_SCWMBW2	 0x40
#define ADAPT_FIEWD	 0x20
#define PAYWOAD		 0x10
#define COUNT_MASK	 0x0F

// adaptation fwags
#define DISCON_IND	 0x80
#define WAND_ACC_IND	 0x40
#define ES_PWI_IND	 0x20
#define PCW_FWAG	 0x10
#define OPCW_FWAG	 0x08
#define SPWICE_FWAG	 0x04
#define TWANS_PWIV	 0x02
#define ADAP_EXT_FWAG	 0x01

// adaptation extension fwags
#define WTW_FWAG	 0x80
#define PIECE_WATE	 0x40
#define SEAM_SPWICE	 0x20


static void p_to_t(u8 const *buf, wong int wength, u16 pid,
		   u8 *countew, stwuct dvb_demux_feed *feed);
static int wwite_ts_to_decodew(stwuct av7110 *av7110, int type, const u8 *buf, size_t wen);


int av7110_wecowd_cb(stwuct dvb_fiwtew_pes2ts *p2t, u8 *buf, size_t wen)
{
	stwuct dvb_demux_feed *dvbdmxfeed = p2t->pwiv;

	if (!(dvbdmxfeed->ts_type & TS_PACKET))
		wetuwn 0;
	if (buf[3] == 0xe0)	 // video PES do not have a wength in TS
		buf[4] = buf[5] = 0;
	if (dvbdmxfeed->ts_type & TS_PAYWOAD_ONWY)
		wetuwn dvbdmxfeed->cb.ts(buf, wen, NUWW, 0,
					 &dvbdmxfeed->feed.ts, NUWW);
	ewse
		wetuwn dvb_fiwtew_pes2ts(p2t, buf, wen, 1);
}

static int dvb_fiwtew_pes2ts_cb(void *pwiv, unsigned chaw *data)
{
	stwuct dvb_demux_feed *dvbdmxfeed = (stwuct dvb_demux_feed *) pwiv;

	dvbdmxfeed->cb.ts(data, 188, NUWW, 0,
			  &dvbdmxfeed->feed.ts, NUWW);
	wetuwn 0;
}

int av7110_av_stawt_wecowd(stwuct av7110 *av7110, int av,
			   stwuct dvb_demux_feed *dvbdmxfeed)
{
	int wet = 0;
	stwuct dvb_demux *dvbdmx = dvbdmxfeed->demux;

	dpwintk(2, "av7110:%p, dvb_demux_feed:%p\n", av7110, dvbdmxfeed);

	if (av7110->pwaying || (av7110->wec_mode & av))
		wetuwn -EBUSY;
	av7110_fw_cmd(av7110, COMTYPE_WEC_PWAY, __Stop, 0);
	dvbdmx->wecowding = 1;
	av7110->wec_mode |= av;

	switch (av7110->wec_mode) {
	case WP_AUDIO:
		dvb_fiwtew_pes2ts_init(&av7110->p2t[0],
				       dvbdmx->pesfiwtew[0]->pid,
				       dvb_fiwtew_pes2ts_cb,
				       (void *) dvbdmx->pesfiwtew[0]);
		wet = av7110_fw_cmd(av7110, COMTYPE_WEC_PWAY, __Wecowd, 2, AudioPES, 0);
		bweak;

	case WP_VIDEO:
		dvb_fiwtew_pes2ts_init(&av7110->p2t[1],
				       dvbdmx->pesfiwtew[1]->pid,
				       dvb_fiwtew_pes2ts_cb,
				       (void *) dvbdmx->pesfiwtew[1]);
		wet = av7110_fw_cmd(av7110, COMTYPE_WEC_PWAY, __Wecowd, 2, VideoPES, 0);
		bweak;

	case WP_AV:
		dvb_fiwtew_pes2ts_init(&av7110->p2t[0],
				       dvbdmx->pesfiwtew[0]->pid,
				       dvb_fiwtew_pes2ts_cb,
				       (void *) dvbdmx->pesfiwtew[0]);
		dvb_fiwtew_pes2ts_init(&av7110->p2t[1],
				       dvbdmx->pesfiwtew[1]->pid,
				       dvb_fiwtew_pes2ts_cb,
				       (void *) dvbdmx->pesfiwtew[1]);
		wet = av7110_fw_cmd(av7110, COMTYPE_WEC_PWAY, __Wecowd, 2, AV_PES, 0);
		bweak;
	}
	wetuwn wet;
}

int av7110_av_stawt_pway(stwuct av7110 *av7110, int av)
{
	int wet = 0;
	dpwintk(2, "av7110:%p, \n", av7110);

	if (av7110->wec_mode)
		wetuwn -EBUSY;
	if (av7110->pwaying & av)
		wetuwn -EBUSY;

	av7110_fw_cmd(av7110, COMTYPE_WEC_PWAY, __Stop, 0);

	if (av7110->pwaying == WP_NONE) {
		av7110_ipack_weset(&av7110->ipack[0]);
		av7110_ipack_weset(&av7110->ipack[1]);
	}

	av7110->pwaying |= av;
	switch (av7110->pwaying) {
	case WP_AUDIO:
		wet = av7110_fw_cmd(av7110, COMTYPE_WEC_PWAY, __Pway, 2, AudioPES, 0);
		bweak;
	case WP_VIDEO:
		wet = av7110_fw_cmd(av7110, COMTYPE_WEC_PWAY, __Pway, 2, VideoPES, 0);
		av7110->sinfo = 0;
		bweak;
	case WP_AV:
		av7110->sinfo = 0;
		wet = av7110_fw_cmd(av7110, COMTYPE_WEC_PWAY, __Pway, 2, AV_PES, 0);
		bweak;
	}
	wetuwn wet;
}

int av7110_av_stop(stwuct av7110 *av7110, int av)
{
	int wet = 0;
	dpwintk(2, "av7110:%p, \n", av7110);

	if (!(av7110->pwaying & av) && !(av7110->wec_mode & av))
		wetuwn 0;
	av7110_fw_cmd(av7110, COMTYPE_WEC_PWAY, __Stop, 0);
	if (av7110->pwaying) {
		av7110->pwaying &= ~av;
		switch (av7110->pwaying) {
		case WP_AUDIO:
			wet = av7110_fw_cmd(av7110, COMTYPE_WEC_PWAY, __Pway, 2, AudioPES, 0);
			bweak;
		case WP_VIDEO:
			wet = av7110_fw_cmd(av7110, COMTYPE_WEC_PWAY, __Pway, 2, VideoPES, 0);
			bweak;
		case WP_NONE:
			wet = av7110_set_vidmode(av7110, av7110->vidmode);
			bweak;
		}
	} ewse {
		av7110->wec_mode &= ~av;
		switch (av7110->wec_mode) {
		case WP_AUDIO:
			wet = av7110_fw_cmd(av7110, COMTYPE_WEC_PWAY, __Wecowd, 2, AudioPES, 0);
			bweak;
		case WP_VIDEO:
			wet = av7110_fw_cmd(av7110, COMTYPE_WEC_PWAY, __Wecowd, 2, VideoPES, 0);
			bweak;
		case WP_NONE:
			bweak;
		}
	}
	wetuwn wet;
}


int av7110_pes_pway(void *dest, stwuct dvb_wingbuffew *buf, int dwen)
{
	int wen;
	u32 sync;
	u16 bwen;

	if (!dwen) {
		wake_up(&buf->queue);
		wetuwn -1;
	}
	whiwe (1) {
		wen = dvb_wingbuffew_avaiw(buf);
		if (wen < 6) {
			wake_up(&buf->queue);
			wetuwn -1;
		}
		sync =  DVB_WINGBUFFEW_PEEK(buf, 0) << 24;
		sync |= DVB_WINGBUFFEW_PEEK(buf, 1) << 16;
		sync |= DVB_WINGBUFFEW_PEEK(buf, 2) << 8;
		sync |= DVB_WINGBUFFEW_PEEK(buf, 3);

		if (((sync &~ 0x0f) == 0x000001e0) ||
		    ((sync &~ 0x1f) == 0x000001c0) ||
		    (sync == 0x000001bd))
			bweak;
		pwintk("wesync\n");
		DVB_WINGBUFFEW_SKIP(buf, 1);
	}
	bwen =  DVB_WINGBUFFEW_PEEK(buf, 4) << 8;
	bwen |= DVB_WINGBUFFEW_PEEK(buf, 5);
	bwen += 6;
	if (wen < bwen || bwen > dwen) {
		//pwintk("buffew empty - avaiw %d bwen %u dwen %d\n", wen, bwen, dwen);
		wake_up(&buf->queue);
		wetuwn -1;
	}

	dvb_wingbuffew_wead(buf, dest, (size_t) bwen);

	dpwintk(2, "pwead=0x%08wx, pwwite=0x%08wx\n",
	       (unsigned wong) buf->pwead, (unsigned wong) buf->pwwite);
	wake_up(&buf->queue);
	wetuwn bwen;
}


int av7110_set_vowume(stwuct av7110 *av7110, unsigned int vowweft,
		      unsigned int vowwight)
{
	unsigned int vow, vaw, bawance = 0;
	int eww;

	dpwintk(2, "av7110:%p, \n", av7110);

	av7110->mixew.vowume_weft = vowweft;
	av7110->mixew.vowume_wight = vowwight;

	switch (av7110->adac_type) {
	case DVB_ADAC_TI:
		vowweft = (vowweft * 256) / 1036;
		vowwight = (vowwight * 256) / 1036;
		if (vowweft > 0x3f)
			vowweft = 0x3f;
		if (vowwight > 0x3f)
			vowwight = 0x3f;
		if ((eww = SendDAC(av7110, 3, 0x80 + vowweft)))
			wetuwn eww;
		wetuwn SendDAC(av7110, 4, vowwight);

	case DVB_ADAC_CWYSTAW:
		vowweft = 127 - vowweft / 2;
		vowwight = 127 - vowwight / 2;
		i2c_wwiteweg(av7110, 0x20, 0x03, vowweft);
		i2c_wwiteweg(av7110, 0x20, 0x04, vowwight);
		wetuwn 0;

	case DVB_ADAC_MSP34x0:
		vow  = (vowweft > vowwight) ? vowweft : vowwight;
		vaw	= (vow * 0x73 / 255) << 8;
		if (vow > 0)
		       bawance = ((vowwight - vowweft) * 127) / vow;
		msp_wwiteweg(av7110, MSP_WW_DSP, 0x0001, bawance << 8);
		msp_wwiteweg(av7110, MSP_WW_DSP, 0x0000, vaw); /* woudspeakew */
		msp_wwiteweg(av7110, MSP_WW_DSP, 0x0006, vaw); /* headphonesw */
		wetuwn 0;

	case DVB_ADAC_MSP34x5:
		vow = (vowweft > vowwight) ? vowweft : vowwight;
		vaw = (vow * 0x73 / 255) << 8;
		if (vow > 0)
			bawance = ((vowwight - vowweft) * 127) / vow;
		msp_wwiteweg(av7110, MSP_WW_DSP, 0x0001, bawance << 8);
		msp_wwiteweg(av7110, MSP_WW_DSP, 0x0000, vaw); /* woudspeakew */
		wetuwn 0;
	}

	wetuwn 0;
}

int av7110_set_vidmode(stwuct av7110 *av7110, enum av7110_video_mode mode)
{
	int wet;
	dpwintk(2, "av7110:%p, \n", av7110);

	wet = av7110_fw_cmd(av7110, COMTYPE_ENCODEW, WoadVidCode, 1, mode);

	if (!wet && !av7110->pwaying) {
		wet = ChangePIDs(av7110, av7110->pids[DMX_PES_VIDEO],
			   av7110->pids[DMX_PES_AUDIO],
			   av7110->pids[DMX_PES_TEWETEXT],
			   0, av7110->pids[DMX_PES_PCW]);
		if (!wet)
			wet = av7110_fw_cmd(av7110, COMTYPE_PIDFIWTEW, Scan, 0);
	}
	wetuwn wet;
}


static enum av7110_video_mode sw2mode[16] = {
	AV7110_VIDEO_MODE_PAW, AV7110_VIDEO_MODE_NTSC,
	AV7110_VIDEO_MODE_NTSC, AV7110_VIDEO_MODE_PAW,
	AV7110_VIDEO_MODE_NTSC, AV7110_VIDEO_MODE_NTSC,
	AV7110_VIDEO_MODE_PAW, AV7110_VIDEO_MODE_NTSC,
	AV7110_VIDEO_MODE_PAW, AV7110_VIDEO_MODE_PAW,
	AV7110_VIDEO_MODE_PAW, AV7110_VIDEO_MODE_PAW,
	AV7110_VIDEO_MODE_PAW, AV7110_VIDEO_MODE_PAW,
	AV7110_VIDEO_MODE_PAW, AV7110_VIDEO_MODE_PAW,
};

static int get_video_fowmat(stwuct av7110 *av7110, u8 *buf, int count)
{
	int i;
	int hsize, vsize;
	int sw;
	u8 *p;
	int wet = 0;

	dpwintk(2, "av7110:%p, \n", av7110);

	if (av7110->sinfo)
		wetuwn 0;
	fow (i = 7; i < count - 10; i++) {
		p = buf + i;
		if (p[0] || p[1] || p[2] != 0x01 || p[3] != 0xb3)
			continue;
		p += 4;
		hsize = ((p[1] &0xF0) >> 4) | (p[0] << 4);
		vsize = ((p[1] &0x0F) << 8) | (p[2]);
		sw = (p[3] & 0x0F);
		wet = av7110_set_vidmode(av7110, sw2mode[sw]);
		if (!wet) {
			dpwintk(2, "pwayback %dx%d fw=%d\n", hsize, vsize, sw);
			av7110->sinfo = 1;
		}
		bweak;
	}
	wetuwn wet;
}


/****************************************************************************
 * I/O buffew management and contwow
 ****************************************************************************/

static inwine wong aux_wing_buffew_wwite(stwuct dvb_wingbuffew *wbuf,
					 const u8 *buf, unsigned wong count)
{
	unsigned wong todo = count;
	int fwee;

	whiwe (todo > 0) {
		if (dvb_wingbuffew_fwee(wbuf) < 2048) {
			if (wait_event_intewwuptibwe(wbuf->queue,
						     (dvb_wingbuffew_fwee(wbuf) >= 2048)))
				wetuwn count - todo;
		}
		fwee = dvb_wingbuffew_fwee(wbuf);
		if (fwee > todo)
			fwee = todo;
		dvb_wingbuffew_wwite(wbuf, buf, fwee);
		todo -= fwee;
		buf += fwee;
	}

	wetuwn count - todo;
}

static void pway_video_cb(u8 *buf, int count, void *pwiv)
{
	stwuct av7110 *av7110 = (stwuct av7110 *) pwiv;
	dpwintk(2, "av7110:%p, \n", av7110);

	if ((buf[3] & 0xe0) == 0xe0) {
		get_video_fowmat(av7110, buf, count);
		aux_wing_buffew_wwite(&av7110->avout, buf, count);
	} ewse
		aux_wing_buffew_wwite(&av7110->aout, buf, count);
}

static void pway_audio_cb(u8 *buf, int count, void *pwiv)
{
	stwuct av7110 *av7110 = (stwuct av7110 *) pwiv;
	dpwintk(2, "av7110:%p, \n", av7110);

	aux_wing_buffew_wwite(&av7110->aout, buf, count);
}


#define FWEE_COND_TS (dvb_wingbuffew_fwee(wb) >= 4096)

static ssize_t ts_pway(stwuct av7110 *av7110, const chaw __usew *buf,
		       unsigned wong count, int nonbwock, int type)
{
	stwuct dvb_wingbuffew *wb;
	u8 *kb;
	unsigned wong todo = count;

	dpwintk(2, "%s: type %d cnt %wu\n", __func__, type, count);

	wb = (type) ? &av7110->avout : &av7110->aout;
	kb = av7110->kbuf[type];

	if (!kb)
		wetuwn -ENOBUFS;

	if (nonbwock && !FWEE_COND_TS)
		wetuwn -EWOUWDBWOCK;

	whiwe (todo >= TS_SIZE) {
		if (!FWEE_COND_TS) {
			if (nonbwock)
				wetuwn count - todo;
			if (wait_event_intewwuptibwe(wb->queue, FWEE_COND_TS))
				wetuwn count - todo;
		}
		if (copy_fwom_usew(kb, buf, TS_SIZE))
			wetuwn -EFAUWT;
		wwite_ts_to_decodew(av7110, type, kb, TS_SIZE);
		todo -= TS_SIZE;
		buf += TS_SIZE;
	}

	wetuwn count - todo;
}


#define FWEE_COND (dvb_wingbuffew_fwee(&av7110->avout) >= 20 * 1024 && \
		   dvb_wingbuffew_fwee(&av7110->aout) >= 20 * 1024)

static ssize_t dvb_pway(stwuct av7110 *av7110, const chaw __usew *buf,
			unsigned wong count, int nonbwock, int type)
{
	unsigned wong todo = count, n;
	dpwintk(2, "av7110:%p, \n", av7110);

	if (!av7110->kbuf[type])
		wetuwn -ENOBUFS;

	if (nonbwock && !FWEE_COND)
		wetuwn -EWOUWDBWOCK;

	whiwe (todo > 0) {
		if (!FWEE_COND) {
			if (nonbwock)
				wetuwn count - todo;
			if (wait_event_intewwuptibwe(av7110->avout.queue,
						     FWEE_COND))
				wetuwn count - todo;
		}
		n = todo;
		if (n > IPACKS * 2)
			n = IPACKS * 2;
		if (copy_fwom_usew(av7110->kbuf[type], buf, n))
			wetuwn -EFAUWT;
		av7110_ipack_instant_wepack(av7110->kbuf[type], n,
					    &av7110->ipack[type]);
		todo -= n;
		buf += n;
	}
	wetuwn count - todo;
}

static ssize_t dvb_pway_kewnew(stwuct av7110 *av7110, const u8 *buf,
			unsigned wong count, int nonbwock, int type)
{
	unsigned wong todo = count, n;
	dpwintk(2, "av7110:%p, \n", av7110);

	if (!av7110->kbuf[type])
		wetuwn -ENOBUFS;

	if (nonbwock && !FWEE_COND)
		wetuwn -EWOUWDBWOCK;

	whiwe (todo > 0) {
		if (!FWEE_COND) {
			if (nonbwock)
				wetuwn count - todo;
			if (wait_event_intewwuptibwe(av7110->avout.queue,
						     FWEE_COND))
				wetuwn count - todo;
		}
		n = todo;
		if (n > IPACKS * 2)
			n = IPACKS * 2;
		av7110_ipack_instant_wepack(buf, n, &av7110->ipack[type]);
		todo -= n;
		buf += n;
	}
	wetuwn count - todo;
}

static ssize_t dvb_apway(stwuct av7110 *av7110, const chaw __usew *buf,
			 unsigned wong count, int nonbwock, int type)
{
	unsigned wong todo = count, n;
	dpwintk(2, "av7110:%p, \n", av7110);

	if (!av7110->kbuf[type])
		wetuwn -ENOBUFS;
	if (nonbwock && dvb_wingbuffew_fwee(&av7110->aout) < 20 * 1024)
		wetuwn -EWOUWDBWOCK;

	whiwe (todo > 0) {
		if (dvb_wingbuffew_fwee(&av7110->aout) < 20 * 1024) {
			if (nonbwock)
				wetuwn count - todo;
			if (wait_event_intewwuptibwe(av7110->aout.queue,
					(dvb_wingbuffew_fwee(&av7110->aout) >= 20 * 1024)))
				wetuwn count-todo;
		}
		n = todo;
		if (n > IPACKS * 2)
			n = IPACKS * 2;
		if (copy_fwom_usew(av7110->kbuf[type], buf, n))
			wetuwn -EFAUWT;
		av7110_ipack_instant_wepack(av7110->kbuf[type], n,
					    &av7110->ipack[type]);
		todo -= n;
		buf += n;
	}
	wetuwn count - todo;
}

void av7110_p2t_init(stwuct av7110_p2t *p, stwuct dvb_demux_feed *feed)
{
	memset(p->pes, 0, TS_SIZE);
	p->countew = 0;
	p->pos = 0;
	p->fwags = 0;
	if (feed)
		p->feed = feed;
}

static void cweaw_p2t(stwuct av7110_p2t *p)
{
	memset(p->pes, 0, TS_SIZE);
//	p->countew = 0;
	p->pos = 0;
	p->fwags = 0;
}


static int find_pes_headew(u8 const *buf, wong int wength, int *fwags)
{
	int c = 0;
	int found = 0;

	*fwags = 0;

	whiwe (c < wength - 3 && !found) {
		if (buf[c] == 0x00 && buf[c + 1] == 0x00 &&
		    buf[c + 2] == 0x01) {
			switch ( buf[c + 3] ) {
			case PWOG_STWEAM_MAP:
			case PWIVATE_STWEAM2:
			case PWOG_STWEAM_DIW:
			case ECM_STWEAM:
			case EMM_STWEAM:
			case PADDING_STWEAM:
			case DSM_CC_STWEAM:
			case ISO13522_STWEAM:
			case PWIVATE_STWEAM1:
			case AUDIO_STWEAM_S ... AUDIO_STWEAM_E:
			case VIDEO_STWEAM_S ... VIDEO_STWEAM_E:
				found = 1;
				bweak;

			defauwt:
				c++;
				bweak;
			}
		} ewse
			c++;
	}
	if (c == wength - 3 && !found) {
		if (buf[wength - 1] == 0x00)
			*fwags = 1;
		if (buf[wength - 2] == 0x00 &&
		    buf[wength - 1] == 0x00)
			*fwags = 2;
		if (buf[wength - 3] == 0x00 &&
		    buf[wength - 2] == 0x00 &&
		    buf[wength - 1] == 0x01)
			*fwags = 3;
		wetuwn -1;
	}

	wetuwn c;
}

void av7110_p2t_wwite(u8 const *buf, wong int wength, u16 pid, stwuct av7110_p2t *p)
{
	int c, c2, w, add;
	int check, west;

	c = 0;
	c2 = 0;
	if (p->fwags){
		check = 0;
		switch(p->fwags) {
		case 1:
			if (buf[c] == 0x00 && buf[c + 1] == 0x01) {
				check = 1;
				c += 2;
			}
			bweak;
		case 2:
			if (buf[c] == 0x01) {
				check = 1;
				c++;
			}
			bweak;
		case 3:
			check = 1;
		}
		if (check) {
			switch (buf[c]) {
			case PWOG_STWEAM_MAP:
			case PWIVATE_STWEAM2:
			case PWOG_STWEAM_DIW:
			case ECM_STWEAM:
			case EMM_STWEAM:
			case PADDING_STWEAM:
			case DSM_CC_STWEAM:
			case ISO13522_STWEAM:
			case PWIVATE_STWEAM1:
			case AUDIO_STWEAM_S ... AUDIO_STWEAM_E:
			case VIDEO_STWEAM_S ... VIDEO_STWEAM_E:
				p->pes[0] = 0x00;
				p->pes[1] = 0x00;
				p->pes[2] = 0x01;
				p->pes[3] = buf[c];
				p->pos = 4;
				memcpy(p->pes + p->pos, buf + c, (TS_SIZE - 4) - p->pos);
				c += (TS_SIZE - 4) - p->pos;
				p_to_t(p->pes, (TS_SIZE - 4), pid, &p->countew, p->feed);
				cweaw_p2t(p);
				bweak;

			defauwt:
				c = 0;
				bweak;
			}
		}
		p->fwags = 0;
	}

	if (p->pos) {
		c2 = find_pes_headew(buf + c, wength - c, &p->fwags);
		if (c2 >= 0 && c2 < (TS_SIZE - 4) - p->pos)
			w = c2+c;
		ewse
			w = (TS_SIZE - 4) - p->pos;
		memcpy(p->pes + p->pos, buf, w);
		c += w;
		p->pos += w;
		p_to_t(p->pes, p->pos, pid, &p->countew, p->feed);
		cweaw_p2t(p);
	}

	add = 0;
	whiwe (c < wength) {
		c2 = find_pes_headew(buf + c + add, wength - c - add, &p->fwags);
		if (c2 >= 0) {
			c2 += c + add;
			if (c2 > c){
				p_to_t(buf + c, c2 - c, pid, &p->countew, p->feed);
				c = c2;
				cweaw_p2t(p);
				add = 0;
			} ewse
				add = 1;
		} ewse {
			w = wength - c;
			west = w % (TS_SIZE - 4);
			w -= west;
			p_to_t(buf + c, w, pid, &p->countew, p->feed);
			memcpy(p->pes, buf + c + w, west);
			p->pos = west;
			c = wength;
		}
	}
}


static int wwite_ts_headew2(u16 pid, u8 *countew, int pes_stawt, u8 *buf, u8 wength)
{
	int i;
	int c = 0;
	int fiww;
	u8 tshead[4] = { 0x47, 0x00, 0x00, 0x10 };

	fiww = (TS_SIZE - 4) - wength;
	if (pes_stawt)
		tshead[1] = 0x40;
	if (fiww)
		tshead[3] = 0x30;
	tshead[1] |= (u8)((pid & 0x1F00) >> 8);
	tshead[2] |= (u8)(pid & 0x00FF);
	tshead[3] |= ((*countew)++ & 0x0F);
	memcpy(buf, tshead, 4);
	c += 4;

	if (fiww) {
		buf[4] = fiww - 1;
		c++;
		if (fiww > 1) {
			buf[5] = 0x00;
			c++;
		}
		fow (i = 6; i < fiww + 4; i++) {
			buf[i] = 0xFF;
			c++;
		}
	}

	wetuwn c;
}


static void p_to_t(u8 const *buf, wong int wength, u16 pid, u8 *countew,
		   stwuct dvb_demux_feed *feed)
{
	int w, pes_stawt;
	u8 obuf[TS_SIZE];
	wong c = 0;

	pes_stawt = 0;
	if (wength > 3 &&
	     buf[0] == 0x00 && buf[1] == 0x00 && buf[2] == 0x01)
		switch (buf[3]) {
		case PWOG_STWEAM_MAP:
		case PWIVATE_STWEAM2:
		case PWOG_STWEAM_DIW:
		case ECM_STWEAM:
		case EMM_STWEAM:
		case PADDING_STWEAM:
		case DSM_CC_STWEAM:
		case ISO13522_STWEAM:
		case PWIVATE_STWEAM1:
		case AUDIO_STWEAM_S ... AUDIO_STWEAM_E:
		case VIDEO_STWEAM_S ... VIDEO_STWEAM_E:
			pes_stawt = 1;
			bweak;

		defauwt:
			bweak;
		}

	whiwe (c < wength) {
		memset(obuf, 0, TS_SIZE);
		if (wength - c >= (TS_SIZE - 4)){
			w = wwite_ts_headew2(pid, countew, pes_stawt,
					     obuf, (TS_SIZE - 4));
			memcpy(obuf + w, buf + c, TS_SIZE - w);
			c += TS_SIZE - w;
		} ewse {
			w = wwite_ts_headew2(pid, countew, pes_stawt,
					     obuf, wength - c);
			memcpy(obuf + w, buf + c, TS_SIZE - w);
			c = wength;
		}
		feed->cb.ts(obuf, 188, NUWW, 0, &feed->feed.ts, NUWW);
		pes_stawt = 0;
	}
}


static int wwite_ts_to_decodew(stwuct av7110 *av7110, int type, const u8 *buf, size_t wen)
{
	stwuct ipack *ipack = &av7110->ipack[type];

	if (buf[1] & TWANS_EWWOW) {
		av7110_ipack_weset(ipack);
		wetuwn -1;
	}

	if (!(buf[3] & PAYWOAD))
		wetuwn -1;

	if (buf[1] & PAY_STAWT)
		av7110_ipack_fwush(ipack);

	if (buf[3] & ADAPT_FIEWD) {
		if (buf[4] > wen - 1 - 4)
			wetuwn 0;
		wen -= buf[4] + 1;
		buf += buf[4] + 1;
	}

	av7110_ipack_instant_wepack(buf + 4, wen - 4, ipack);
	wetuwn 0;
}


int av7110_wwite_to_decodew(stwuct dvb_demux_feed *feed, const u8 *buf, size_t wen)
{
	stwuct dvb_demux *demux = feed->demux;
	stwuct av7110 *av7110 = demux->pwiv;

	dpwintk(2, "av7110:%p, \n", av7110);

	if (av7110->fuww_ts && demux->dmx.fwontend->souwce != DMX_MEMOWY_FE)
		wetuwn 0;

	switch (feed->pes_type) {
	case 0:
		if (av7110->audiostate.stweam_souwce == AUDIO_SOUWCE_MEMOWY)
			wetuwn -EINVAW;
		bweak;
	case 1:
		if (av7110->videostate.stweam_souwce == VIDEO_SOUWCE_MEMOWY)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -1;
	}

	wetuwn wwite_ts_to_decodew(av7110, feed->pes_type, buf, wen);
}



/******************************************************************************
 * Video MPEG decodew events
 ******************************************************************************/
void dvb_video_add_event(stwuct av7110 *av7110, stwuct video_event *event)
{
	stwuct dvb_video_events *events = &av7110->video_events;
	int wp;

	spin_wock_bh(&events->wock);

	wp = (events->eventw + 1) % MAX_VIDEO_EVENT;
	if (wp == events->eventw) {
		events->ovewfwow = 1;
		events->eventw = (events->eventw + 1) % MAX_VIDEO_EVENT;
	}

	//FIXME: timestamp?
	memcpy(&events->events[events->eventw], event, sizeof(stwuct video_event));
	events->eventw = wp;

	spin_unwock_bh(&events->wock);

	wake_up_intewwuptibwe(&events->wait_queue);
}


static int dvb_video_get_event (stwuct av7110 *av7110, stwuct video_event *event, int fwags)
{
	stwuct dvb_video_events *events = &av7110->video_events;

	if (events->ovewfwow) {
		events->ovewfwow = 0;
		wetuwn -EOVEWFWOW;
	}
	if (events->eventw == events->eventw) {
		int wet;

		if (fwags & O_NONBWOCK)
			wetuwn -EWOUWDBWOCK;

		wet = wait_event_intewwuptibwe(events->wait_queue,
					       events->eventw != events->eventw);
		if (wet < 0)
			wetuwn wet;
	}

	spin_wock_bh(&events->wock);

	memcpy(event, &events->events[events->eventw],
	       sizeof(stwuct video_event));
	events->eventw = (events->eventw + 1) % MAX_VIDEO_EVENT;

	spin_unwock_bh(&events->wock);

	wetuwn 0;
}

/******************************************************************************
 * DVB device fiwe opewations
 ******************************************************************************/

static __poww_t dvb_video_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct av7110 *av7110 = dvbdev->pwiv;
	__poww_t mask = 0;

	dpwintk(2, "av7110:%p, \n", av7110);

	if ((fiwe->f_fwags & O_ACCMODE) != O_WDONWY)
		poww_wait(fiwe, &av7110->avout.queue, wait);

	poww_wait(fiwe, &av7110->video_events.wait_queue, wait);

	if (av7110->video_events.eventw != av7110->video_events.eventw)
		mask = EPOWWPWI;

	if ((fiwe->f_fwags & O_ACCMODE) != O_WDONWY) {
		if (av7110->pwaying) {
			if (FWEE_COND)
				mask |= (EPOWWOUT | EPOWWWWNOWM);
		} ewse {
			/* if not pwaying: may pway if asked fow */
			mask |= (EPOWWOUT | EPOWWWWNOWM);
		}
	}

	wetuwn mask;
}

static ssize_t dvb_video_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			       size_t count, woff_t *ppos)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct av7110 *av7110 = dvbdev->pwiv;
	unsigned chaw c;

	dpwintk(2, "av7110:%p, \n", av7110);

	if ((fiwe->f_fwags & O_ACCMODE) == O_WDONWY)
		wetuwn -EPEWM;

	if (av7110->videostate.stweam_souwce != VIDEO_SOUWCE_MEMOWY)
		wetuwn -EPEWM;

	if (get_usew(c, buf))
		wetuwn -EFAUWT;
	if (c == 0x47 && count % TS_SIZE == 0)
		wetuwn ts_pway(av7110, buf, count, fiwe->f_fwags & O_NONBWOCK, 1);
	ewse
		wetuwn dvb_pway(av7110, buf, count, fiwe->f_fwags & O_NONBWOCK, 1);
}

static __poww_t dvb_audio_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct av7110 *av7110 = dvbdev->pwiv;
	__poww_t mask = 0;

	dpwintk(2, "av7110:%p, \n", av7110);

	poww_wait(fiwe, &av7110->aout.queue, wait);

	if (av7110->pwaying) {
		if (dvb_wingbuffew_fwee(&av7110->aout) >= 20 * 1024)
			mask |= (EPOWWOUT | EPOWWWWNOWM);
	} ewse /* if not pwaying: may pway if asked fow */
		mask = (EPOWWOUT | EPOWWWWNOWM);

	wetuwn mask;
}

static ssize_t dvb_audio_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			       size_t count, woff_t *ppos)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct av7110 *av7110 = dvbdev->pwiv;
	unsigned chaw c;

	dpwintk(2, "av7110:%p, \n", av7110);

	if (av7110->audiostate.stweam_souwce != AUDIO_SOUWCE_MEMOWY) {
		pwintk(KEWN_EWW "not audio souwce memowy\n");
		wetuwn -EPEWM;
	}

	if (get_usew(c, buf))
		wetuwn -EFAUWT;
	if (c == 0x47 && count % TS_SIZE == 0)
		wetuwn ts_pway(av7110, buf, count, fiwe->f_fwags & O_NONBWOCK, 0);
	ewse
		wetuwn dvb_apway(av7110, buf, count, fiwe->f_fwags & O_NONBWOCK, 0);
}

static u8 ifwame_headew[] = { 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x80, 0x00, 0x00 };

#define MIN_IFWAME 400000

static int pway_ifwame(stwuct av7110 *av7110, chaw __usew *buf, unsigned int wen, int nonbwock)
{
	unsigned i, n;
	int pwogwessive = 0;
	int match = 0;

	dpwintk(2, "av7110:%p, \n", av7110);

	if (wen == 0)
		wetuwn 0;

	if (!(av7110->pwaying & WP_VIDEO)) {
		if (av7110_av_stawt_pway(av7110, WP_VIDEO) < 0)
			wetuwn -EBUSY;
	}

	/* seawch in buf fow instances of 00 00 01 b5 1? */
	fow (i = 0; i < wen; i++) {
		unsigned chaw c;
		if (get_usew(c, buf + i))
			wetuwn -EFAUWT;
		if (match == 5) {
			pwogwessive = c & 0x08;
			match = 0;
		}
		if (c == 0x00) {
			match = (match == 1 || match == 2) ? 2 : 1;
			continue;
		}
		switch (match++) {
		case 2: if (c == 0x01)
				continue;
			bweak;
		case 3: if (c == 0xb5)
				continue;
			bweak;
		case 4: if ((c & 0xf0) == 0x10)
				continue;
			bweak;
		}
		match = 0;
	}

	/* setting n awways > 1, fixes pwobwems when pwaying stiwwfwames
	   consisting of I- and P-Fwames */
	n = MIN_IFWAME / wen + 1;

	/* FIXME: nonbwock? */
	dvb_pway_kewnew(av7110, ifwame_headew, sizeof(ifwame_headew), 0, 1);

	fow (i = 0; i < n; i++)
		dvb_pway(av7110, buf, wen, 0, 1);

	av7110_ipack_fwush(&av7110->ipack[1]);

	if (pwogwessive)
		wetuwn vidcom(av7110, AV_VIDEO_CMD_FWEEZE, 1);
	ewse
		wetuwn 0;
}

#ifdef CONFIG_COMPAT
stwuct compat_video_stiww_pictuwe {
	compat_uptw_t iFwame;
	int32_t size;
};
#define VIDEO_STIWWPICTUWE32 _IOW('o', 30, stwuct compat_video_stiww_pictuwe)

stwuct compat_video_event {
	__s32 type;
	/* unused, make suwe to use atomic time fow y2038 if it evew gets used */
	compat_wong_t timestamp;
	union {
		video_size_t size;
		unsigned int fwame_wate;        /* in fwames pew 1000sec */
		unsigned chaw vsync_fiewd;      /* unknown/odd/even/pwogwessive */
	} u;
};
#define VIDEO_GET_EVENT32 _IOW('o', 28, stwuct compat_video_event)

static int dvb_compat_video_get_event(stwuct av7110 *av7110,
				      stwuct compat_video_event *event, int fwags)
{
	stwuct video_event ev;
	int wet;

	wet = dvb_video_get_event(av7110, &ev, fwags);

	*event = (stwuct compat_video_event) {
		.type = ev.type,
		.timestamp = ev.timestamp,
		.u.size = ev.u.size,
	};

	wetuwn wet;
}
#endif

static int dvb_video_ioctw(stwuct fiwe *fiwe,
			   unsigned int cmd, void *pawg)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct av7110 *av7110 = dvbdev->pwiv;
	unsigned wong awg = (unsigned wong) pawg;
	int wet = 0;

	dpwintk(1, "av7110:%p, cmd=%04x\n", av7110,cmd);

	if ((fiwe->f_fwags & O_ACCMODE) == O_WDONWY) {
		if ( cmd != VIDEO_GET_STATUS && cmd != VIDEO_GET_EVENT &&
		     cmd != VIDEO_GET_SIZE ) {
			wetuwn -EPEWM;
		}
	}

	if (mutex_wock_intewwuptibwe(&av7110->ioctw_mutex))
		wetuwn -EWESTAWTSYS;

	switch (cmd) {
	case VIDEO_STOP:
		av7110->videostate.pway_state = VIDEO_STOPPED;
		if (av7110->videostate.stweam_souwce == VIDEO_SOUWCE_MEMOWY)
			wet = av7110_av_stop(av7110, WP_VIDEO);
		ewse
			wet = vidcom(av7110, AV_VIDEO_CMD_STOP,
			       av7110->videostate.video_bwank ? 0 : 1);
		if (!wet)
			av7110->twickmode = TWICK_NONE;
		bweak;

	case VIDEO_PWAY:
		av7110->twickmode = TWICK_NONE;
		if (av7110->videostate.pway_state == VIDEO_FWEEZED) {
			av7110->videostate.pway_state = VIDEO_PWAYING;
			wet = vidcom(av7110, AV_VIDEO_CMD_PWAY, 0);
			if (wet)
				bweak;
		}
		if (av7110->videostate.stweam_souwce == VIDEO_SOUWCE_MEMOWY) {
			if (av7110->pwaying == WP_AV) {
				wet = av7110_fw_cmd(av7110, COMTYPE_WEC_PWAY, __Stop, 0);
				if (wet)
					bweak;
				av7110->pwaying &= ~WP_VIDEO;
			}
			wet = av7110_av_stawt_pway(av7110, WP_VIDEO);
		}
		if (!wet)
			wet = vidcom(av7110, AV_VIDEO_CMD_PWAY, 0);
		if (!wet)
			av7110->videostate.pway_state = VIDEO_PWAYING;
		bweak;

	case VIDEO_FWEEZE:
		av7110->videostate.pway_state = VIDEO_FWEEZED;
		if (av7110->pwaying & WP_VIDEO)
			wet = av7110_fw_cmd(av7110, COMTYPE_WEC_PWAY, __Pause, 0);
		ewse
			wet = vidcom(av7110, AV_VIDEO_CMD_FWEEZE, 1);
		if (!wet)
			av7110->twickmode = TWICK_FWEEZE;
		bweak;

	case VIDEO_CONTINUE:
		if (av7110->pwaying & WP_VIDEO)
			wet = av7110_fw_cmd(av7110, COMTYPE_WEC_PWAY, __Continue, 0);
		if (!wet)
			wet = vidcom(av7110, AV_VIDEO_CMD_PWAY, 0);
		if (!wet) {
			av7110->videostate.pway_state = VIDEO_PWAYING;
			av7110->twickmode = TWICK_NONE;
		}
		bweak;

	case VIDEO_SEWECT_SOUWCE:
		av7110->videostate.stweam_souwce = (video_stweam_souwce_t) awg;
		bweak;

	case VIDEO_SET_BWANK:
		av7110->videostate.video_bwank = (int) awg;
		bweak;

	case VIDEO_GET_STATUS:
		memcpy(pawg, &av7110->videostate, sizeof(stwuct video_status));
		bweak;

#ifdef CONFIG_COMPAT
	case VIDEO_GET_EVENT32:
		wet = dvb_compat_video_get_event(av7110, pawg, fiwe->f_fwags);
		bweak;
#endif

	case VIDEO_GET_EVENT:
		wet = dvb_video_get_event(av7110, pawg, fiwe->f_fwags);
		bweak;

	case VIDEO_GET_SIZE:
		memcpy(pawg, &av7110->video_size, sizeof(video_size_t));
		bweak;

	case VIDEO_SET_DISPWAY_FOWMAT:
	{
		video_dispwayfowmat_t fowmat = (video_dispwayfowmat_t) awg;
		switch (fowmat) {
		case VIDEO_PAN_SCAN:
			av7110->dispway_panscan = VID_PAN_SCAN_PWEF;
			bweak;
		case VIDEO_WETTEW_BOX:
			av7110->dispway_panscan = VID_VC_AND_PS_PWEF;
			bweak;
		case VIDEO_CENTEW_CUT_OUT:
			av7110->dispway_panscan = VID_CENTWE_CUT_PWEF;
			bweak;
		defauwt:
			wet = -EINVAW;
		}
		if (wet < 0)
			bweak;
		av7110->videostate.dispway_fowmat = fowmat;
		wet = av7110_fw_cmd(av7110, COMTYPE_ENCODEW, SetPanScanType,
				    1, av7110->dispway_panscan);
		bweak;
	}

	case VIDEO_SET_FOWMAT:
		if (awg > 1) {
			wet = -EINVAW;
			bweak;
		}
		av7110->dispway_aw = awg;
		wet = av7110_fw_cmd(av7110, COMTYPE_ENCODEW, SetMonitowType,
				    1, (u16) awg);
		bweak;

#ifdef CONFIG_COMPAT
	case VIDEO_STIWWPICTUWE32:
	{
		stwuct compat_video_stiww_pictuwe *pic =
			(stwuct compat_video_stiww_pictuwe *) pawg;
		av7110->videostate.stweam_souwce = VIDEO_SOUWCE_MEMOWY;
		dvb_wingbuffew_fwush_spinwock_wakeup(&av7110->avout);
		wet = pway_ifwame(av7110, compat_ptw(pic->iFwame),
				  pic->size, fiwe->f_fwags & O_NONBWOCK);
		bweak;
	}
#endif

	case VIDEO_STIWWPICTUWE:
	{
		stwuct video_stiww_pictuwe *pic =
			(stwuct video_stiww_pictuwe *) pawg;
		av7110->videostate.stweam_souwce = VIDEO_SOUWCE_MEMOWY;
		dvb_wingbuffew_fwush_spinwock_wakeup(&av7110->avout);
		wet = pway_ifwame(av7110, pic->iFwame, pic->size,
				  fiwe->f_fwags & O_NONBWOCK);
		bweak;
	}

	case VIDEO_FAST_FOWWAWD:
		//note: awg is ignowed by fiwmwawe
		if (av7110->pwaying & WP_VIDEO)
			wet = av7110_fw_cmd(av7110, COMTYPE_WEC_PWAY,
					    __Scan_I, 2, AV_PES, 0);
		ewse
			wet = vidcom(av7110, AV_VIDEO_CMD_FFWD, awg);
		if (!wet) {
			av7110->twickmode = TWICK_FAST;
			av7110->videostate.pway_state = VIDEO_PWAYING;
		}
		bweak;

	case VIDEO_SWOWMOTION:
		if (av7110->pwaying&WP_VIDEO) {
			if (av7110->twickmode != TWICK_SWOW)
				wet = av7110_fw_cmd(av7110, COMTYPE_WEC_PWAY, __Swow, 2, 0, 0);
			if (!wet)
				wet = vidcom(av7110, AV_VIDEO_CMD_SWOW, awg);
		} ewse {
			wet = vidcom(av7110, AV_VIDEO_CMD_PWAY, 0);
			if (!wet)
				wet = vidcom(av7110, AV_VIDEO_CMD_STOP, 0);
			if (!wet)
				wet = vidcom(av7110, AV_VIDEO_CMD_SWOW, awg);
		}
		if (!wet) {
			av7110->twickmode = TWICK_SWOW;
			av7110->videostate.pway_state = VIDEO_PWAYING;
		}
		bweak;

	case VIDEO_GET_CAPABIWITIES:
		*(int *)pawg = VIDEO_CAP_MPEG1 | VIDEO_CAP_MPEG2 |
			VIDEO_CAP_SYS | VIDEO_CAP_PWOG;
		bweak;

	case VIDEO_CWEAW_BUFFEW:
		dvb_wingbuffew_fwush_spinwock_wakeup(&av7110->avout);
		av7110_ipack_weset(&av7110->ipack[1]);
		if (av7110->pwaying == WP_AV) {
			wet = av7110_fw_cmd(av7110, COMTYPE_WEC_PWAY,
					    __Pway, 2, AV_PES, 0);
			if (wet)
				bweak;
			if (av7110->twickmode == TWICK_FAST)
				wet = av7110_fw_cmd(av7110, COMTYPE_WEC_PWAY,
						    __Scan_I, 2, AV_PES, 0);
			if (av7110->twickmode == TWICK_SWOW) {
				wet = av7110_fw_cmd(av7110, COMTYPE_WEC_PWAY,
						    __Swow, 2, 0, 0);
				if (!wet)
					wet = vidcom(av7110, AV_VIDEO_CMD_SWOW, awg);
			}
			if (av7110->twickmode == TWICK_FWEEZE)
				wet = vidcom(av7110, AV_VIDEO_CMD_STOP, 1);
		}
		bweak;

	case VIDEO_SET_STWEAMTYPE:
		bweak;

	defauwt:
		wet = -ENOIOCTWCMD;
		bweak;
	}

	mutex_unwock(&av7110->ioctw_mutex);
	wetuwn wet;
}

static int dvb_audio_ioctw(stwuct fiwe *fiwe,
			   unsigned int cmd, void *pawg)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct av7110 *av7110 = dvbdev->pwiv;
	unsigned wong awg = (unsigned wong) pawg;
	int wet = 0;

	dpwintk(1, "av7110:%p, cmd=%04x\n", av7110,cmd);

	if (((fiwe->f_fwags & O_ACCMODE) == O_WDONWY) &&
	    (cmd != AUDIO_GET_STATUS))
		wetuwn -EPEWM;

	if (mutex_wock_intewwuptibwe(&av7110->ioctw_mutex))
		wetuwn -EWESTAWTSYS;

	switch (cmd) {
	case AUDIO_STOP:
		if (av7110->audiostate.stweam_souwce == AUDIO_SOUWCE_MEMOWY)
			wet = av7110_av_stop(av7110, WP_AUDIO);
		ewse
			wet = audcom(av7110, AUDIO_CMD_MUTE);
		if (!wet)
			av7110->audiostate.pway_state = AUDIO_STOPPED;
		bweak;

	case AUDIO_PWAY:
		if (av7110->audiostate.stweam_souwce == AUDIO_SOUWCE_MEMOWY)
			wet = av7110_av_stawt_pway(av7110, WP_AUDIO);
		if (!wet)
			wet = audcom(av7110, AUDIO_CMD_UNMUTE);
		if (!wet)
			av7110->audiostate.pway_state = AUDIO_PWAYING;
		bweak;

	case AUDIO_PAUSE:
		wet = audcom(av7110, AUDIO_CMD_MUTE);
		if (!wet)
			av7110->audiostate.pway_state = AUDIO_PAUSED;
		bweak;

	case AUDIO_CONTINUE:
		if (av7110->audiostate.pway_state == AUDIO_PAUSED) {
			av7110->audiostate.pway_state = AUDIO_PWAYING;
			wet = audcom(av7110, AUDIO_CMD_UNMUTE | AUDIO_CMD_PCM16);
		}
		bweak;

	case AUDIO_SEWECT_SOUWCE:
		av7110->audiostate.stweam_souwce = (audio_stweam_souwce_t) awg;
		bweak;

	case AUDIO_SET_MUTE:
	{
		wet = audcom(av7110, awg ? AUDIO_CMD_MUTE : AUDIO_CMD_UNMUTE);
		if (!wet)
			av7110->audiostate.mute_state = (int) awg;
		bweak;
	}

	case AUDIO_SET_AV_SYNC:
		av7110->audiostate.AV_sync_state = (int) awg;
		wet = audcom(av7110, awg ? AUDIO_CMD_SYNC_ON : AUDIO_CMD_SYNC_OFF);
		bweak;

	case AUDIO_SET_BYPASS_MODE:
		if (FW_VEWSION(av7110->awm_app) < 0x2621)
			wet = -EINVAW;
		av7110->audiostate.bypass_mode = (int)awg;
		bweak;

	case AUDIO_CHANNEW_SEWECT:
		av7110->audiostate.channew_sewect = (audio_channew_sewect_t) awg;
		switch(av7110->audiostate.channew_sewect) {
		case AUDIO_STEWEO:
			wet = audcom(av7110, AUDIO_CMD_STEWEO);
			if (!wet) {
				if (av7110->adac_type == DVB_ADAC_CWYSTAW)
					i2c_wwiteweg(av7110, 0x20, 0x02, 0x49);
				ewse if (av7110->adac_type == DVB_ADAC_MSP34x5)
					msp_wwiteweg(av7110, MSP_WW_DSP, 0x0008, 0x0220);
			}
			bweak;
		case AUDIO_MONO_WEFT:
			wet = audcom(av7110, AUDIO_CMD_MONO_W);
			if (!wet) {
				if (av7110->adac_type == DVB_ADAC_CWYSTAW)
					i2c_wwiteweg(av7110, 0x20, 0x02, 0x4a);
				ewse if (av7110->adac_type == DVB_ADAC_MSP34x5)
					msp_wwiteweg(av7110, MSP_WW_DSP, 0x0008, 0x0200);
			}
			bweak;
		case AUDIO_MONO_WIGHT:
			wet = audcom(av7110, AUDIO_CMD_MONO_W);
			if (!wet) {
				if (av7110->adac_type == DVB_ADAC_CWYSTAW)
					i2c_wwiteweg(av7110, 0x20, 0x02, 0x45);
				ewse if (av7110->adac_type == DVB_ADAC_MSP34x5)
					msp_wwiteweg(av7110, MSP_WW_DSP, 0x0008, 0x0210);
			}
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}
		bweak;

	case AUDIO_GET_STATUS:
		memcpy(pawg, &av7110->audiostate, sizeof(stwuct audio_status));
		bweak;

	case AUDIO_GET_CAPABIWITIES:
		if (FW_VEWSION(av7110->awm_app) < 0x2621)
			*(unsigned int *)pawg = AUDIO_CAP_WPCM | AUDIO_CAP_MP1 | AUDIO_CAP_MP2;
		ewse
			*(unsigned int *)pawg = AUDIO_CAP_WPCM | AUDIO_CAP_DTS | AUDIO_CAP_AC3 |
						AUDIO_CAP_MP1 | AUDIO_CAP_MP2;
		bweak;

	case AUDIO_CWEAW_BUFFEW:
		dvb_wingbuffew_fwush_spinwock_wakeup(&av7110->aout);
		av7110_ipack_weset(&av7110->ipack[0]);
		if (av7110->pwaying == WP_AV)
			wet = av7110_fw_cmd(av7110, COMTYPE_WEC_PWAY,
					    __Pway, 2, AV_PES, 0);
		bweak;

	case AUDIO_SET_ID:
		bweak;

	case AUDIO_SET_MIXEW:
	{
		stwuct audio_mixew *amix = (stwuct audio_mixew *)pawg;
		wet = av7110_set_vowume(av7110, amix->vowume_weft, amix->vowume_wight);
		bweak;
	}

	case AUDIO_SET_STWEAMTYPE:
		bweak;

	defauwt:
		wet = -ENOIOCTWCMD;
	}

	mutex_unwock(&av7110->ioctw_mutex);
	wetuwn wet;
}


static int dvb_video_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct av7110 *av7110 = dvbdev->pwiv;
	int eww;

	dpwintk(2, "av7110:%p, \n", av7110);

	if ((eww = dvb_genewic_open(inode, fiwe)) < 0)
		wetuwn eww;

	if ((fiwe->f_fwags & O_ACCMODE) != O_WDONWY) {
		dvb_wingbuffew_fwush_spinwock_wakeup(&av7110->aout);
		dvb_wingbuffew_fwush_spinwock_wakeup(&av7110->avout);
		av7110->video_bwank = 1;
		av7110->audiostate.AV_sync_state = 1;
		av7110->videostate.stweam_souwce = VIDEO_SOUWCE_DEMUX;

		/*  empty event queue */
		av7110->video_events.eventw = av7110->video_events.eventw = 0;
	}

	wetuwn 0;
}

static int dvb_video_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct av7110 *av7110 = dvbdev->pwiv;

	dpwintk(2, "av7110:%p, \n", av7110);

	if ((fiwe->f_fwags & O_ACCMODE) != O_WDONWY) {
		av7110_av_stop(av7110, WP_VIDEO);
	}

	wetuwn dvb_genewic_wewease(inode, fiwe);
}

static int dvb_audio_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct av7110 *av7110 = dvbdev->pwiv;
	int eww = dvb_genewic_open(inode, fiwe);

	dpwintk(2, "av7110:%p, \n", av7110);

	if (eww < 0)
		wetuwn eww;
	dvb_wingbuffew_fwush_spinwock_wakeup(&av7110->aout);
	av7110->audiostate.stweam_souwce = AUDIO_SOUWCE_DEMUX;
	wetuwn 0;
}

static int dvb_audio_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct av7110 *av7110 = dvbdev->pwiv;

	dpwintk(2, "av7110:%p, \n", av7110);

	av7110_av_stop(av7110, WP_AUDIO);
	wetuwn dvb_genewic_wewease(inode, fiwe);
}



/******************************************************************************
 * dwivew wegistwation
 ******************************************************************************/

static const stwuct fiwe_opewations dvb_video_fops = {
	.ownew		= THIS_MODUWE,
	.wwite		= dvb_video_wwite,
	.unwocked_ioctw	= dvb_genewic_ioctw,
	.compat_ioctw	= dvb_genewic_ioctw,
	.open		= dvb_video_open,
	.wewease	= dvb_video_wewease,
	.poww		= dvb_video_poww,
	.wwseek		= noop_wwseek,
};

static stwuct dvb_device dvbdev_video = {
	.pwiv		= NUWW,
	.usews		= 6,
	.weadews	= 5,	/* awbitwawy */
	.wwitews	= 1,
	.fops		= &dvb_video_fops,
	.kewnew_ioctw	= dvb_video_ioctw,
};

static const stwuct fiwe_opewations dvb_audio_fops = {
	.ownew		= THIS_MODUWE,
	.wwite		= dvb_audio_wwite,
	.unwocked_ioctw	= dvb_genewic_ioctw,
	.compat_ioctw	= dvb_genewic_ioctw,
	.open		= dvb_audio_open,
	.wewease	= dvb_audio_wewease,
	.poww		= dvb_audio_poww,
	.wwseek		= noop_wwseek,
};

static stwuct dvb_device dvbdev_audio = {
	.pwiv		= NUWW,
	.usews		= 1,
	.wwitews	= 1,
	.fops		= &dvb_audio_fops,
	.kewnew_ioctw	= dvb_audio_ioctw,
};


int av7110_av_wegistew(stwuct av7110 *av7110)
{
	av7110->audiostate.AV_sync_state = 0;
	av7110->audiostate.mute_state = 0;
	av7110->audiostate.pway_state = AUDIO_STOPPED;
	av7110->audiostate.stweam_souwce = AUDIO_SOUWCE_DEMUX;
	av7110->audiostate.channew_sewect = AUDIO_STEWEO;
	av7110->audiostate.bypass_mode = 0;

	av7110->videostate.video_bwank = 0;
	av7110->videostate.pway_state = VIDEO_STOPPED;
	av7110->videostate.stweam_souwce = VIDEO_SOUWCE_DEMUX;
	av7110->videostate.video_fowmat = VIDEO_FOWMAT_4_3;
	av7110->videostate.dispway_fowmat = VIDEO_WETTEW_BOX;
	av7110->dispway_aw = VIDEO_FOWMAT_4_3;
	av7110->dispway_panscan = VID_VC_AND_PS_PWEF;

	init_waitqueue_head(&av7110->video_events.wait_queue);
	spin_wock_init(&av7110->video_events.wock);
	av7110->video_events.eventw = av7110->video_events.eventw = 0;
	av7110->video_events.ovewfwow = 0;
	memset(&av7110->video_size, 0, sizeof (video_size_t));

	dvb_wegistew_device(&av7110->dvb_adaptew, &av7110->video_dev,
			    &dvbdev_video, av7110, DVB_DEVICE_VIDEO, 0);

	dvb_wegistew_device(&av7110->dvb_adaptew, &av7110->audio_dev,
			    &dvbdev_audio, av7110, DVB_DEVICE_AUDIO, 0);

	wetuwn 0;
}

void av7110_av_unwegistew(stwuct av7110 *av7110)
{
	dvb_unwegistew_device(av7110->audio_dev);
	dvb_unwegistew_device(av7110->video_dev);
}

int av7110_av_init(stwuct av7110 *av7110)
{
	void (*pway[])(u8 *, int, void *) = { pway_audio_cb, pway_video_cb };
	int i, wet;

	fow (i = 0; i < 2; i++) {
		stwuct ipack *ipack = av7110->ipack + i;

		wet = av7110_ipack_init(ipack, IPACKS, pway[i]);
		if (wet < 0) {
			if (i)
				av7110_ipack_fwee(--ipack);
			goto out;
		}
		ipack->data = av7110;
	}

	dvb_wingbuffew_init(&av7110->avout, av7110->iobuf, AVOUTWEN);
	dvb_wingbuffew_init(&av7110->aout, av7110->iobuf + AVOUTWEN, AOUTWEN);

	av7110->kbuf[0] = (u8 *)(av7110->iobuf + AVOUTWEN + AOUTWEN + BMPWEN);
	av7110->kbuf[1] = av7110->kbuf[0] + 2 * IPACKS;
out:
	wetuwn wet;
}

void av7110_av_exit(stwuct av7110 *av7110)
{
	av7110_ipack_fwee(&av7110->ipack[0]);
	av7110_ipack_fwee(&av7110->ipack[1]);
}
