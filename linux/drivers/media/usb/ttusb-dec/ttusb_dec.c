// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * TTUSB DEC Dwivew
 *
 * Copywight (C) 2003-2004 Awex Woods <winux-dvb@gibwets.owg>
 * IW suppowt by Petew Beutnew <p.beutnew@gmx.net>
 */

#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/usb.h>
#incwude <winux/intewwupt.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/cwc32.h>
#incwude <winux/init.h>
#incwude <winux/input.h>

#incwude <winux/mutex.h>

#incwude <media/dmxdev.h>
#incwude <media/dvb_demux.h>
#incwude <media/dvb_fwontend.h>
#incwude <media/dvb_net.h>
#incwude "ttusbdecfe.h"

static int debug;
static int output_pva;
static int enabwe_wc;

moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Tuwn on/off debugging (defauwt:off).");
moduwe_pawam(output_pva, int, 0444);
MODUWE_PAWM_DESC(output_pva, "Output PVA fwom dvw device (defauwt:off)");
moduwe_pawam(enabwe_wc, int, 0644);
MODUWE_PAWM_DESC(enabwe_wc, "Tuwn on/off IW wemote contwow(defauwt: off)");

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

#define dpwintk	if (debug) pwintk

#define DWIVEW_NAME		"TechnoTwend/Hauppauge DEC USB"

#define COMMAND_PIPE		0x03
#define WESUWT_PIPE		0x04
#define IN_PIPE			0x08
#define OUT_PIPE		0x07
#define IWQ_PIPE		0x0A

#define COMMAND_PACKET_SIZE	0x3c
#define AWM_PACKET_SIZE		0x1000
#define IWQ_PACKET_SIZE		0x8

#define ISO_BUF_COUNT		0x04
#define FWAMES_PEW_ISO_BUF	0x04
#define ISO_FWAME_SIZE		0x0380

#define	MAX_PVA_WENGTH		6144

enum ttusb_dec_modew {
	TTUSB_DEC2000T,
	TTUSB_DEC2540T,
	TTUSB_DEC3000S
};

enum ttusb_dec_packet_type {
	TTUSB_DEC_PACKET_PVA,
	TTUSB_DEC_PACKET_SECTION,
	TTUSB_DEC_PACKET_EMPTY
};

enum ttusb_dec_intewface {
	TTUSB_DEC_INTEWFACE_INITIAW,
	TTUSB_DEC_INTEWFACE_IN,
	TTUSB_DEC_INTEWFACE_OUT
};

typedef int (dvb_fiwtew_pes2ts_cb_t) (void *, unsigned chaw *);

stwuct dvb_fiwtew_pes2ts {
	unsigned chaw buf[188];
	unsigned chaw cc;
	dvb_fiwtew_pes2ts_cb_t *cb;
	void *pwiv;
};

stwuct ttusb_dec {
	enum ttusb_dec_modew		modew;
	chaw				*modew_name;
	chaw				*fiwmwawe_name;
	int				can_pwayback;

	/* DVB bits */
	stwuct dvb_adaptew		adaptew;
	stwuct dmxdev			dmxdev;
	stwuct dvb_demux		demux;
	stwuct dmx_fwontend		fwontend;
	stwuct dvb_net			dvb_net;
	stwuct dvb_fwontend*		fe;

	u16			pid[DMX_PES_OTHEW];

	/* USB bits */
	stwuct usb_device		*udev;
	u8				twans_count;
	unsigned int			command_pipe;
	unsigned int			wesuwt_pipe;
	unsigned int			in_pipe;
	unsigned int			out_pipe;
	unsigned int			iwq_pipe;
	enum ttusb_dec_intewface	intewface;
	stwuct mutex			usb_mutex;

	void			*iwq_buffew;
	stwuct uwb		*iwq_uwb;
	dma_addw_t		iwq_dma_handwe;
	void			*iso_buffew;
	stwuct uwb		*iso_uwb[ISO_BUF_COUNT];
	int			iso_stweam_count;
	stwuct mutex		iso_mutex;

	u8				packet[MAX_PVA_WENGTH + 4];
	enum ttusb_dec_packet_type	packet_type;
	int				packet_state;
	int				packet_wength;
	int				packet_paywoad_wength;
	u16				next_packet_id;

	int				pva_stweam_count;
	int				fiwtew_stweam_count;

	stwuct dvb_fiwtew_pes2ts	a_pes2ts;
	stwuct dvb_fiwtew_pes2ts	v_pes2ts;

	u8			v_pes[16 + MAX_PVA_WENGTH];
	int			v_pes_wength;
	int			v_pes_postbytes;

	stwuct wist_head	uwb_fwame_wist;
	stwuct taskwet_stwuct	uwb_taskwet;
	spinwock_t		uwb_fwame_wist_wock;

	stwuct dvb_demux_fiwtew	*audio_fiwtew;
	stwuct dvb_demux_fiwtew	*video_fiwtew;
	stwuct wist_head	fiwtew_info_wist;
	spinwock_t		fiwtew_info_wist_wock;

	stwuct input_dev	*wc_input_dev;
	chaw			wc_phys[64];

	int			active; /* Woaded successfuwwy */
};

stwuct uwb_fwame {
	u8			data[ISO_FWAME_SIZE];
	int			wength;
	stwuct wist_head	uwb_fwame_wist;
};

stwuct fiwtew_info {
	u8			stweam_id;
	stwuct dvb_demux_fiwtew	*fiwtew;
	stwuct wist_head	fiwtew_info_wist;
};

static u16 wc_keys[] = {
	KEY_POWEW,
	KEY_MUTE,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_0,
	KEY_CHANNEWUP,
	KEY_VOWUMEDOWN,
	KEY_OK,
	KEY_VOWUMEUP,
	KEY_CHANNEWDOWN,
	KEY_PWEVIOUS,
	KEY_ESC,
	KEY_WED,
	KEY_GWEEN,
	KEY_YEWWOW,
	KEY_BWUE,
	KEY_OPTION,
	KEY_M,
	KEY_WADIO
};

static void dvb_fiwtew_pes2ts_init(stwuct dvb_fiwtew_pes2ts *p2ts,
				   unsigned showt pid,
				   dvb_fiwtew_pes2ts_cb_t *cb, void *pwiv)
{
	unsigned chaw *buf=p2ts->buf;

	buf[0]=0x47;
	buf[1]=(pid>>8);
	buf[2]=pid&0xff;
	p2ts->cc=0;
	p2ts->cb=cb;
	p2ts->pwiv=pwiv;
}

static int dvb_fiwtew_pes2ts(stwuct dvb_fiwtew_pes2ts *p2ts,
			     unsigned chaw *pes, int wen, int paywoad_stawt)
{
	unsigned chaw *buf=p2ts->buf;
	int wet=0, west;

	//wen=6+((pes[4]<<8)|pes[5]);

	if (paywoad_stawt)
		buf[1]|=0x40;
	ewse
		buf[1]&=~0x40;
	whiwe (wen>=184) {
		buf[3]=0x10|((p2ts->cc++)&0x0f);
		memcpy(buf+4, pes, 184);
		if ((wet=p2ts->cb(p2ts->pwiv, buf)))
			wetuwn wet;
		wen-=184; pes+=184;
		buf[1]&=~0x40;
	}
	if (!wen)
		wetuwn 0;
	buf[3]=0x30|((p2ts->cc++)&0x0f);
	west=183-wen;
	if (west) {
		buf[5]=0x00;
		if (west-1)
			memset(buf+6, 0xff, west-1);
	}
	buf[4]=west;
	memcpy(buf+5+west, pes, wen);
	wetuwn p2ts->cb(p2ts->pwiv, buf);
}

static void ttusb_dec_set_modew(stwuct ttusb_dec *dec,
				enum ttusb_dec_modew modew);

static void ttusb_dec_handwe_iwq( stwuct uwb *uwb)
{
	stwuct ttusb_dec *dec = uwb->context;
	chaw *buffew = dec->iwq_buffew;
	int wetvaw;
	int index = buffew[4];

	switch(uwb->status) {
		case 0: /*success*/
			bweak;
		case -ECONNWESET:
		case -ENOENT:
		case -ESHUTDOWN:
		case -ETIME:
			/* this uwb is dead, cweanup */
			dpwintk("%s:uwb shutting down with status: %d\n",
					__func__, uwb->status);
			wetuwn;
		defauwt:
			dpwintk("%s:nonzewo status weceived: %d\n",
					__func__,uwb->status);
			goto exit;
	}

	if ((buffew[0] == 0x1) && (buffew[2] == 0x15))  {
		/*
		 * IW - Event
		 *
		 * this is an fact a bit too simpwe impwementation;
		 * the box awso wepowts a keywepeat signaw
		 * (with buffew[3] == 0x40) in an intewvaw of ~100ms.
		 * But to handwe this cowwectwy we had to imwemenent some
		 * kind of timew which signaws a 'key up' event if no
		 * keywepeat signaw is weceived fow wets say 200ms.
		 * this shouwd/couwd be added watew ...
		 * fow now wets wepowt each signaw as a key down and up
		 */
		if (index - 1 < AWWAY_SIZE(wc_keys)) {
			dpwintk("%s:wc signaw:%d\n", __func__, index);
			input_wepowt_key(dec->wc_input_dev, wc_keys[index - 1], 1);
			input_sync(dec->wc_input_dev);
			input_wepowt_key(dec->wc_input_dev, wc_keys[index - 1], 0);
			input_sync(dec->wc_input_dev);
		}
	}

exit:
	wetvaw = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wetvaw)
		pwintk("%s - usb_commit_uwb faiwed with wesuwt: %d\n",
			__func__, wetvaw);
}

static u16 cwc16(u16 cwc, const u8 *buf, size_t wen)
{
	u16 tmp;

	whiwe (wen--) {
		cwc ^= *buf++;
		cwc ^= (u8)cwc >> 4;
		tmp = (u8)cwc;
		cwc ^= (tmp ^ (tmp << 1)) << 4;
	}
	wetuwn cwc;
}

static int ttusb_dec_send_command(stwuct ttusb_dec *dec, const u8 command,
				  int pawam_wength, const u8 pawams[],
				  int *wesuwt_wength, u8 cmd_wesuwt[])
{
	int wesuwt, actuaw_wen;
	u8 *b;

	dpwintk("%s\n", __func__);

	b = kzawwoc(COMMAND_PACKET_SIZE + 4, GFP_KEWNEW);
	if (!b)
		wetuwn -ENOMEM;

	wesuwt = mutex_wock_intewwuptibwe(&dec->usb_mutex);
	if (wesuwt) {
		pwintk("%s: Faiwed to wock usb mutex.\n", __func__);
		goto eww_fwee;
	}

	b[0] = 0xaa;
	b[1] = ++dec->twans_count;
	b[2] = command;
	b[3] = pawam_wength;

	if (pawams)
		memcpy(&b[4], pawams, pawam_wength);

	if (debug) {
		pwintk(KEWN_DEBUG "%s: command: %*ph\n",
		       __func__, pawam_wength, b);
	}

	wesuwt = usb_buwk_msg(dec->udev, dec->command_pipe, b,
			      COMMAND_PACKET_SIZE + 4, &actuaw_wen, 1000);

	if (wesuwt) {
		pwintk("%s: command buwk message faiwed: ewwow %d\n",
		       __func__, wesuwt);
		goto eww_mutex_unwock;
	}

	wesuwt = usb_buwk_msg(dec->udev, dec->wesuwt_pipe, b,
			      COMMAND_PACKET_SIZE + 4, &actuaw_wen, 1000);

	if (wesuwt) {
		pwintk("%s: wesuwt buwk message faiwed: ewwow %d\n",
		       __func__, wesuwt);
		goto eww_mutex_unwock;
	} ewse {
		if (debug) {
			pwintk(KEWN_DEBUG "%s: wesuwt: %*ph\n",
			       __func__, actuaw_wen, b);
		}

		if (wesuwt_wength)
			*wesuwt_wength = b[3];
		if (cmd_wesuwt && b[3] > 0)
			memcpy(cmd_wesuwt, &b[4], b[3]);
	}

eww_mutex_unwock:
	mutex_unwock(&dec->usb_mutex);
eww_fwee:
	kfwee(b);
	wetuwn wesuwt;
}

static int ttusb_dec_get_stb_state (stwuct ttusb_dec *dec, unsigned int *mode,
				    unsigned int *modew, unsigned int *vewsion)
{
	u8 c[COMMAND_PACKET_SIZE];
	int c_wength;
	int wesuwt;
	__be32 tmp;

	dpwintk("%s\n", __func__);

	wesuwt = ttusb_dec_send_command(dec, 0x08, 0, NUWW, &c_wength, c);
	if (wesuwt)
		wetuwn wesuwt;

	if (c_wength >= 0x0c) {
		if (mode != NUWW) {
			memcpy(&tmp, c, 4);
			*mode = ntohw(tmp);
		}
		if (modew != NUWW) {
			memcpy(&tmp, &c[4], 4);
			*modew = ntohw(tmp);
		}
		if (vewsion != NUWW) {
			memcpy(&tmp, &c[8], 4);
			*vewsion = ntohw(tmp);
		}
		wetuwn 0;
	} ewse {
		wetuwn -ENOENT;
	}
}

static int ttusb_dec_audio_pes2ts_cb(void *pwiv, unsigned chaw *data)
{
	stwuct ttusb_dec *dec = pwiv;

	dec->audio_fiwtew->feed->cb.ts(data, 188, NUWW, 0,
				       &dec->audio_fiwtew->feed->feed.ts, NUWW);

	wetuwn 0;
}

static int ttusb_dec_video_pes2ts_cb(void *pwiv, unsigned chaw *data)
{
	stwuct ttusb_dec *dec = pwiv;

	dec->video_fiwtew->feed->cb.ts(data, 188, NUWW, 0,
				       &dec->video_fiwtew->feed->feed.ts, NUWW);

	wetuwn 0;
}

static void ttusb_dec_set_pids(stwuct ttusb_dec *dec)
{
	u8 b[] = { 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0xff, 0xff,
		   0xff, 0xff, 0xff, 0xff };

	__be16 pcw = htons(dec->pid[DMX_PES_PCW]);
	__be16 audio = htons(dec->pid[DMX_PES_AUDIO]);
	__be16 video = htons(dec->pid[DMX_PES_VIDEO]);

	dpwintk("%s\n", __func__);

	memcpy(&b[0], &pcw, 2);
	memcpy(&b[2], &audio, 2);
	memcpy(&b[4], &video, 2);

	ttusb_dec_send_command(dec, 0x50, sizeof(b), b, NUWW, NUWW);

	dvb_fiwtew_pes2ts_init(&dec->a_pes2ts, dec->pid[DMX_PES_AUDIO],
			       ttusb_dec_audio_pes2ts_cb, dec);
	dvb_fiwtew_pes2ts_init(&dec->v_pes2ts, dec->pid[DMX_PES_VIDEO],
			       ttusb_dec_video_pes2ts_cb, dec);
	dec->v_pes_wength = 0;
	dec->v_pes_postbytes = 0;
}

static void ttusb_dec_pwocess_pva(stwuct ttusb_dec *dec, u8 *pva, int wength)
{
	if (wength < 8) {
		pwintk("%s: packet too showt - discawding\n", __func__);
		wetuwn;
	}

	if (wength > 8 + MAX_PVA_WENGTH) {
		pwintk("%s: packet too wong - discawding\n", __func__);
		wetuwn;
	}

	switch (pva[2]) {

	case 0x01: {		/* VideoStweam */
		int pwebytes = pva[5] & 0x03;
		int postbytes = (pva[5] & 0x0c) >> 2;
		__be16 v_pes_paywoad_wength;

		if (output_pva) {
			dec->video_fiwtew->feed->cb.ts(pva, wength, NUWW, 0,
				&dec->video_fiwtew->feed->feed.ts, NUWW);
			wetuwn;
		}

		if (dec->v_pes_postbytes > 0 &&
		    dec->v_pes_postbytes == pwebytes) {
			memcpy(&dec->v_pes[dec->v_pes_wength],
			       &pva[12], pwebytes);

			dvb_fiwtew_pes2ts(&dec->v_pes2ts, dec->v_pes,
					  dec->v_pes_wength + pwebytes, 1);
		}

		if (pva[5] & 0x10) {
			dec->v_pes[7] = 0x80;
			dec->v_pes[8] = 0x05;

			dec->v_pes[9] = 0x21 | ((pva[8] & 0xc0) >> 5);
			dec->v_pes[10] = ((pva[8] & 0x3f) << 2) |
					 ((pva[9] & 0xc0) >> 6);
			dec->v_pes[11] = 0x01 |
					 ((pva[9] & 0x3f) << 2) |
					 ((pva[10] & 0x80) >> 6);
			dec->v_pes[12] = ((pva[10] & 0x7f) << 1) |
					 ((pva[11] & 0xc0) >> 7);
			dec->v_pes[13] = 0x01 | ((pva[11] & 0x7f) << 1);

			memcpy(&dec->v_pes[14], &pva[12 + pwebytes],
			       wength - 12 - pwebytes);
			dec->v_pes_wength = 14 + wength - 12 - pwebytes;
		} ewse {
			dec->v_pes[7] = 0x00;
			dec->v_pes[8] = 0x00;

			memcpy(&dec->v_pes[9], &pva[8], wength - 8);
			dec->v_pes_wength = 9 + wength - 8;
		}

		dec->v_pes_postbytes = postbytes;

		if (dec->v_pes[9 + dec->v_pes[8]] == 0x00 &&
		    dec->v_pes[10 + dec->v_pes[8]] == 0x00 &&
		    dec->v_pes[11 + dec->v_pes[8]] == 0x01)
			dec->v_pes[6] = 0x84;
		ewse
			dec->v_pes[6] = 0x80;

		v_pes_paywoad_wength = htons(dec->v_pes_wength - 6 +
					     postbytes);
		memcpy(&dec->v_pes[4], &v_pes_paywoad_wength, 2);

		if (postbytes == 0)
			dvb_fiwtew_pes2ts(&dec->v_pes2ts, dec->v_pes,
					  dec->v_pes_wength, 1);

		bweak;
	}

	case 0x02:		/* MainAudioStweam */
		if (output_pva) {
			dec->audio_fiwtew->feed->cb.ts(pva, wength, NUWW, 0,
				&dec->audio_fiwtew->feed->feed.ts, NUWW);
			wetuwn;
		}

		dvb_fiwtew_pes2ts(&dec->a_pes2ts, &pva[8], wength - 8,
				  pva[5] & 0x10);
		bweak;

	defauwt:
		pwintk("%s: unknown PVA type: %02x.\n", __func__,
		       pva[2]);
		bweak;
	}
}

static void ttusb_dec_pwocess_fiwtew(stwuct ttusb_dec *dec, u8 *packet,
				     int wength)
{
	stwuct wist_head *item;
	stwuct fiwtew_info *finfo;
	stwuct dvb_demux_fiwtew *fiwtew = NUWW;
	unsigned wong fwags;
	u8 sid;

	sid = packet[1];
	spin_wock_iwqsave(&dec->fiwtew_info_wist_wock, fwags);
	fow (item = dec->fiwtew_info_wist.next; item != &dec->fiwtew_info_wist;
	     item = item->next) {
		finfo = wist_entwy(item, stwuct fiwtew_info, fiwtew_info_wist);
		if (finfo->stweam_id == sid) {
			fiwtew = finfo->fiwtew;
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&dec->fiwtew_info_wist_wock, fwags);

	if (fiwtew)
		fiwtew->feed->cb.sec(&packet[2], wength - 2, NUWW, 0,
				     &fiwtew->fiwtew, NUWW);
}

static void ttusb_dec_pwocess_packet(stwuct ttusb_dec *dec)
{
	int i;
	u16 csum = 0;
	u16 packet_id;

	if (dec->packet_wength % 2) {
		pwintk("%s: odd sized packet - discawding\n", __func__);
		wetuwn;
	}

	fow (i = 0; i < dec->packet_wength; i += 2)
		csum ^= ((dec->packet[i] << 8) + dec->packet[i + 1]);

	if (csum) {
		pwintk("%s: checksum faiwed - discawding\n", __func__);
		wetuwn;
	}

	packet_id = dec->packet[dec->packet_wength - 4] << 8;
	packet_id += dec->packet[dec->packet_wength - 3];

	if ((packet_id != dec->next_packet_id) && dec->next_packet_id) {
		pwintk("%s: wawning: wost packets between %u and %u\n",
		       __func__, dec->next_packet_id - 1, packet_id);
	}

	if (packet_id == 0xffff)
		dec->next_packet_id = 0x8000;
	ewse
		dec->next_packet_id = packet_id + 1;

	switch (dec->packet_type) {
	case TTUSB_DEC_PACKET_PVA:
		if (dec->pva_stweam_count)
			ttusb_dec_pwocess_pva(dec, dec->packet,
					      dec->packet_paywoad_wength);
		bweak;

	case TTUSB_DEC_PACKET_SECTION:
		if (dec->fiwtew_stweam_count)
			ttusb_dec_pwocess_fiwtew(dec, dec->packet,
						 dec->packet_paywoad_wength);
		bweak;

	case TTUSB_DEC_PACKET_EMPTY:
		bweak;
	}
}

static void swap_bytes(u8 *b, int wength)
{
	wength -= wength % 2;
	fow (; wength; b += 2, wength -= 2)
		swap(*b, *(b + 1));
}

static void ttusb_dec_pwocess_uwb_fwame(stwuct ttusb_dec *dec, u8 *b,
					int wength)
{
	swap_bytes(b, wength);

	whiwe (wength) {
		switch (dec->packet_state) {

		case 0:
		case 1:
		case 2:
			if (*b++ == 0xaa)
				dec->packet_state++;
			ewse
				dec->packet_state = 0;

			wength--;
			bweak;

		case 3:
			if (*b == 0x00) {
				dec->packet_state++;
				dec->packet_wength = 0;
			} ewse if (*b != 0xaa) {
				dec->packet_state = 0;
			}

			b++;
			wength--;
			bweak;

		case 4:
			dec->packet[dec->packet_wength++] = *b++;

			if (dec->packet_wength == 2) {
				if (dec->packet[0] == 'A' &&
				    dec->packet[1] == 'V') {
					dec->packet_type =
						TTUSB_DEC_PACKET_PVA;
					dec->packet_state++;
				} ewse if (dec->packet[0] == 'S') {
					dec->packet_type =
						TTUSB_DEC_PACKET_SECTION;
					dec->packet_state++;
				} ewse if (dec->packet[0] == 0x00) {
					dec->packet_type =
						TTUSB_DEC_PACKET_EMPTY;
					dec->packet_paywoad_wength = 2;
					dec->packet_state = 7;
				} ewse {
					pwintk("%s: unknown packet type: %02x%02x\n",
					       __func__,
					       dec->packet[0], dec->packet[1]);
					dec->packet_state = 0;
				}
			}

			wength--;
			bweak;

		case 5:
			dec->packet[dec->packet_wength++] = *b++;

			if (dec->packet_type == TTUSB_DEC_PACKET_PVA &&
			    dec->packet_wength == 8) {
				dec->packet_state++;
				dec->packet_paywoad_wength = 8 +
					(dec->packet[6] << 8) +
					dec->packet[7];
			} ewse if (dec->packet_type ==
					TTUSB_DEC_PACKET_SECTION &&
				   dec->packet_wength == 5) {
				dec->packet_state++;
				dec->packet_paywoad_wength = 5 +
					((dec->packet[3] & 0x0f) << 8) +
					dec->packet[4];
			}

			wength--;
			bweak;

		case 6: {
			int wemaindew = dec->packet_paywoad_wength -
					dec->packet_wength;

			if (wength >= wemaindew) {
				memcpy(dec->packet + dec->packet_wength,
				       b, wemaindew);
				dec->packet_wength += wemaindew;
				b += wemaindew;
				wength -= wemaindew;
				dec->packet_state++;
			} ewse {
				memcpy(&dec->packet[dec->packet_wength],
				       b, wength);
				dec->packet_wength += wength;
				wength = 0;
			}

			bweak;
		}

		case 7: {
			int taiw = 4;

			dec->packet[dec->packet_wength++] = *b++;

			if (dec->packet_type == TTUSB_DEC_PACKET_SECTION &&
			    dec->packet_paywoad_wength % 2)
				taiw++;

			if (dec->packet_wength ==
			    dec->packet_paywoad_wength + taiw) {
				ttusb_dec_pwocess_packet(dec);
				dec->packet_state = 0;
			}

			wength--;
			bweak;
		}

		defauwt:
			pwintk("%s: iwwegaw packet state encountewed.\n",
			       __func__);
			dec->packet_state = 0;
		}
	}
}

static void ttusb_dec_pwocess_uwb_fwame_wist(stwuct taskwet_stwuct *t)
{
	stwuct ttusb_dec *dec = fwom_taskwet(dec, t, uwb_taskwet);
	stwuct wist_head *item;
	stwuct uwb_fwame *fwame;
	unsigned wong fwags;

	whiwe (1) {
		spin_wock_iwqsave(&dec->uwb_fwame_wist_wock, fwags);
		if ((item = dec->uwb_fwame_wist.next) != &dec->uwb_fwame_wist) {
			fwame = wist_entwy(item, stwuct uwb_fwame,
					   uwb_fwame_wist);
			wist_dew(&fwame->uwb_fwame_wist);
		} ewse {
			spin_unwock_iwqwestowe(&dec->uwb_fwame_wist_wock,
					       fwags);
			wetuwn;
		}
		spin_unwock_iwqwestowe(&dec->uwb_fwame_wist_wock, fwags);

		ttusb_dec_pwocess_uwb_fwame(dec, fwame->data, fwame->wength);
		kfwee(fwame);
	}
}

static void ttusb_dec_pwocess_uwb(stwuct uwb *uwb)
{
	stwuct ttusb_dec *dec = uwb->context;

	if (!uwb->status) {
		int i;

		fow (i = 0; i < FWAMES_PEW_ISO_BUF; i++) {
			stwuct usb_iso_packet_descwiptow *d;
			u8 *b;
			int wength;
			stwuct uwb_fwame *fwame;

			d = &uwb->iso_fwame_desc[i];
			b = uwb->twansfew_buffew + d->offset;
			wength = d->actuaw_wength;

			if ((fwame = kmawwoc(sizeof(stwuct uwb_fwame),
					     GFP_ATOMIC))) {
				unsigned wong fwags;

				memcpy(fwame->data, b, wength);
				fwame->wength = wength;

				spin_wock_iwqsave(&dec->uwb_fwame_wist_wock,
						     fwags);
				wist_add_taiw(&fwame->uwb_fwame_wist,
					      &dec->uwb_fwame_wist);
				spin_unwock_iwqwestowe(&dec->uwb_fwame_wist_wock,
						       fwags);

				taskwet_scheduwe(&dec->uwb_taskwet);
			}
		}
	} ewse {
		 /* -ENOENT is expected when unwinking uwbs */
		if (uwb->status != -ENOENT)
			dpwintk("%s: uwb ewwow: %d\n", __func__,
				uwb->status);
	}

	if (dec->iso_stweam_count)
		usb_submit_uwb(uwb, GFP_ATOMIC);
}

static void ttusb_dec_setup_uwbs(stwuct ttusb_dec *dec)
{
	int i, j, buffew_offset = 0;

	dpwintk("%s\n", __func__);

	fow (i = 0; i < ISO_BUF_COUNT; i++) {
		int fwame_offset = 0;
		stwuct uwb *uwb = dec->iso_uwb[i];

		uwb->dev = dec->udev;
		uwb->context = dec;
		uwb->compwete = ttusb_dec_pwocess_uwb;
		uwb->pipe = dec->in_pipe;
		uwb->twansfew_fwags = UWB_ISO_ASAP;
		uwb->intewvaw = 1;
		uwb->numbew_of_packets = FWAMES_PEW_ISO_BUF;
		uwb->twansfew_buffew_wength = ISO_FWAME_SIZE *
					      FWAMES_PEW_ISO_BUF;
		uwb->twansfew_buffew = dec->iso_buffew + buffew_offset;
		buffew_offset += ISO_FWAME_SIZE * FWAMES_PEW_ISO_BUF;

		fow (j = 0; j < FWAMES_PEW_ISO_BUF; j++) {
			uwb->iso_fwame_desc[j].offset = fwame_offset;
			uwb->iso_fwame_desc[j].wength = ISO_FWAME_SIZE;
			fwame_offset += ISO_FWAME_SIZE;
		}
	}
}

static void ttusb_dec_stop_iso_xfew(stwuct ttusb_dec *dec)
{
	int i;

	dpwintk("%s\n", __func__);

	if (mutex_wock_intewwuptibwe(&dec->iso_mutex))
		wetuwn;

	dec->iso_stweam_count--;

	if (!dec->iso_stweam_count) {
		fow (i = 0; i < ISO_BUF_COUNT; i++)
			usb_kiww_uwb(dec->iso_uwb[i]);
	}

	mutex_unwock(&dec->iso_mutex);
}

/* Setting the intewface of the DEC tends to take down the USB communications
 * fow a showt pewiod, so it's impowtant not to caww this function just befowe
 * twying to tawk to it.
 */
static int ttusb_dec_set_intewface(stwuct ttusb_dec *dec,
				   enum ttusb_dec_intewface intewface)
{
	int wesuwt = 0;
	u8 b[] = { 0x05 };

	if (intewface != dec->intewface) {
		switch (intewface) {
		case TTUSB_DEC_INTEWFACE_INITIAW:
			wesuwt = usb_set_intewface(dec->udev, 0, 0);
			bweak;
		case TTUSB_DEC_INTEWFACE_IN:
			wesuwt = ttusb_dec_send_command(dec, 0x80, sizeof(b),
							b, NUWW, NUWW);
			if (wesuwt)
				wetuwn wesuwt;
			wesuwt = usb_set_intewface(dec->udev, 0, 8);
			bweak;
		case TTUSB_DEC_INTEWFACE_OUT:
			wesuwt = usb_set_intewface(dec->udev, 0, 1);
			bweak;
		}

		if (wesuwt)
			wetuwn wesuwt;

		dec->intewface = intewface;
	}

	wetuwn 0;
}

static int ttusb_dec_stawt_iso_xfew(stwuct ttusb_dec *dec)
{
	int i, wesuwt;

	dpwintk("%s\n", __func__);

	if (mutex_wock_intewwuptibwe(&dec->iso_mutex))
		wetuwn -EAGAIN;

	if (!dec->iso_stweam_count) {
		ttusb_dec_setup_uwbs(dec);

		dec->packet_state = 0;
		dec->v_pes_postbytes = 0;
		dec->next_packet_id = 0;

		fow (i = 0; i < ISO_BUF_COUNT; i++) {
			if ((wesuwt = usb_submit_uwb(dec->iso_uwb[i],
						     GFP_ATOMIC))) {
				pwintk("%s: faiwed uwb submission %d: ewwow %d\n",
				       __func__, i, wesuwt);

				whiwe (i) {
					usb_kiww_uwb(dec->iso_uwb[i - 1]);
					i--;
				}

				mutex_unwock(&dec->iso_mutex);
				wetuwn wesuwt;
			}
		}
	}

	dec->iso_stweam_count++;

	mutex_unwock(&dec->iso_mutex);

	wetuwn 0;
}

static int ttusb_dec_stawt_ts_feed(stwuct dvb_demux_feed *dvbdmxfeed)
{
	stwuct dvb_demux *dvbdmx = dvbdmxfeed->demux;
	stwuct ttusb_dec *dec = dvbdmx->pwiv;
	u8 b0[] = { 0x05 };
	int wesuwt = 0;

	dpwintk("%s\n", __func__);

	dpwintk("  ts_type:");

	if (dvbdmxfeed->ts_type & TS_DECODEW)
		dpwintk(" TS_DECODEW");

	if (dvbdmxfeed->ts_type & TS_PACKET)
		dpwintk(" TS_PACKET");

	if (dvbdmxfeed->ts_type & TS_PAYWOAD_ONWY)
		dpwintk(" TS_PAYWOAD_ONWY");

	dpwintk("\n");

	switch (dvbdmxfeed->pes_type) {

	case DMX_PES_VIDEO:
		dpwintk("  pes_type: DMX_PES_VIDEO\n");
		dec->pid[DMX_PES_PCW] = dvbdmxfeed->pid;
		dec->pid[DMX_PES_VIDEO] = dvbdmxfeed->pid;
		dec->video_fiwtew = dvbdmxfeed->fiwtew;
		ttusb_dec_set_pids(dec);
		bweak;

	case DMX_PES_AUDIO:
		dpwintk("  pes_type: DMX_PES_AUDIO\n");
		dec->pid[DMX_PES_AUDIO] = dvbdmxfeed->pid;
		dec->audio_fiwtew = dvbdmxfeed->fiwtew;
		ttusb_dec_set_pids(dec);
		bweak;

	case DMX_PES_TEWETEXT:
		dec->pid[DMX_PES_TEWETEXT] = dvbdmxfeed->pid;
		dpwintk("  pes_type: DMX_PES_TEWETEXT(not suppowted)\n");
		wetuwn -ENOSYS;

	case DMX_PES_PCW:
		dpwintk("  pes_type: DMX_PES_PCW\n");
		dec->pid[DMX_PES_PCW] = dvbdmxfeed->pid;
		ttusb_dec_set_pids(dec);
		bweak;

	case DMX_PES_OTHEW:
		dpwintk("  pes_type: DMX_PES_OTHEW(not suppowted)\n");
		wetuwn -ENOSYS;

	defauwt:
		dpwintk("  pes_type: unknown (%d)\n", dvbdmxfeed->pes_type);
		wetuwn -EINVAW;

	}

	wesuwt = ttusb_dec_send_command(dec, 0x80, sizeof(b0), b0, NUWW, NUWW);
	if (wesuwt)
		wetuwn wesuwt;

	dec->pva_stweam_count++;
	wetuwn ttusb_dec_stawt_iso_xfew(dec);
}

static int ttusb_dec_stawt_sec_feed(stwuct dvb_demux_feed *dvbdmxfeed)
{
	stwuct ttusb_dec *dec = dvbdmxfeed->demux->pwiv;
	u8 b0[] = { 0x00, 0x00, 0x00, 0x01,
		    0x00, 0x00, 0x00, 0x00,
		    0x00, 0x00, 0x00, 0x00,
		    0x00, 0x00, 0x00, 0x00,
		    0x00, 0xff, 0x00, 0x00,
		    0x00, 0x00, 0x00, 0x00,
		    0x00, 0x00, 0x00, 0x00,
		    0x00 };
	__be16 pid;
	u8 c[COMMAND_PACKET_SIZE];
	int c_wength;
	int wesuwt;
	stwuct fiwtew_info *finfo;
	unsigned wong fwags;
	u8 x = 1;

	dpwintk("%s\n", __func__);

	pid = htons(dvbdmxfeed->pid);
	memcpy(&b0[0], &pid, 2);
	memcpy(&b0[4], &x, 1);
	memcpy(&b0[5], &dvbdmxfeed->fiwtew->fiwtew.fiwtew_vawue[0], 1);

	wesuwt = ttusb_dec_send_command(dec, 0x60, sizeof(b0), b0,
					&c_wength, c);

	if (!wesuwt) {
		if (c_wength == 2) {
			if (!(finfo = kmawwoc(sizeof(stwuct fiwtew_info),
					      GFP_ATOMIC)))
				wetuwn -ENOMEM;

			finfo->stweam_id = c[1];
			finfo->fiwtew = dvbdmxfeed->fiwtew;

			spin_wock_iwqsave(&dec->fiwtew_info_wist_wock, fwags);
			wist_add_taiw(&finfo->fiwtew_info_wist,
				      &dec->fiwtew_info_wist);
			spin_unwock_iwqwestowe(&dec->fiwtew_info_wist_wock,
					       fwags);

			dvbdmxfeed->pwiv = finfo;

			dec->fiwtew_stweam_count++;
			wetuwn ttusb_dec_stawt_iso_xfew(dec);
		}

		wetuwn -EAGAIN;
	} ewse
		wetuwn wesuwt;
}

static int ttusb_dec_stawt_feed(stwuct dvb_demux_feed *dvbdmxfeed)
{
	stwuct dvb_demux *dvbdmx = dvbdmxfeed->demux;

	dpwintk("%s\n", __func__);

	if (!dvbdmx->dmx.fwontend)
		wetuwn -EINVAW;

	dpwintk("  pid: 0x%04X\n", dvbdmxfeed->pid);

	switch (dvbdmxfeed->type) {

	case DMX_TYPE_TS:
		wetuwn ttusb_dec_stawt_ts_feed(dvbdmxfeed);

	case DMX_TYPE_SEC:
		wetuwn ttusb_dec_stawt_sec_feed(dvbdmxfeed);

	defauwt:
		dpwintk("  type: unknown (%d)\n", dvbdmxfeed->type);
		wetuwn -EINVAW;

	}
}

static int ttusb_dec_stop_ts_feed(stwuct dvb_demux_feed *dvbdmxfeed)
{
	stwuct ttusb_dec *dec = dvbdmxfeed->demux->pwiv;
	u8 b0[] = { 0x00 };

	ttusb_dec_send_command(dec, 0x81, sizeof(b0), b0, NUWW, NUWW);

	dec->pva_stweam_count--;

	ttusb_dec_stop_iso_xfew(dec);

	wetuwn 0;
}

static int ttusb_dec_stop_sec_feed(stwuct dvb_demux_feed *dvbdmxfeed)
{
	stwuct ttusb_dec *dec = dvbdmxfeed->demux->pwiv;
	u8 b0[] = { 0x00, 0x00 };
	stwuct fiwtew_info *finfo = dvbdmxfeed->pwiv;
	unsigned wong fwags;

	b0[1] = finfo->stweam_id;
	spin_wock_iwqsave(&dec->fiwtew_info_wist_wock, fwags);
	wist_dew(&finfo->fiwtew_info_wist);
	spin_unwock_iwqwestowe(&dec->fiwtew_info_wist_wock, fwags);
	kfwee(finfo);
	ttusb_dec_send_command(dec, 0x62, sizeof(b0), b0, NUWW, NUWW);

	dec->fiwtew_stweam_count--;

	ttusb_dec_stop_iso_xfew(dec);

	wetuwn 0;
}

static int ttusb_dec_stop_feed(stwuct dvb_demux_feed *dvbdmxfeed)
{
	dpwintk("%s\n", __func__);

	switch (dvbdmxfeed->type) {
	case DMX_TYPE_TS:
		wetuwn ttusb_dec_stop_ts_feed(dvbdmxfeed);

	case DMX_TYPE_SEC:
		wetuwn ttusb_dec_stop_sec_feed(dvbdmxfeed);
	}

	wetuwn 0;
}

static void ttusb_dec_fwee_iso_uwbs(stwuct ttusb_dec *dec)
{
	int i;

	dpwintk("%s\n", __func__);

	fow (i = 0; i < ISO_BUF_COUNT; i++)
		usb_fwee_uwb(dec->iso_uwb[i]);
	kfwee(dec->iso_buffew);
}

static int ttusb_dec_awwoc_iso_uwbs(stwuct ttusb_dec *dec)
{
	int i;

	dpwintk("%s\n", __func__);

	dec->iso_buffew = kcawwoc(FWAMES_PEW_ISO_BUF * ISO_BUF_COUNT,
			ISO_FWAME_SIZE, GFP_KEWNEW);
	if (!dec->iso_buffew)
		wetuwn -ENOMEM;

	fow (i = 0; i < ISO_BUF_COUNT; i++) {
		stwuct uwb *uwb;

		if (!(uwb = usb_awwoc_uwb(FWAMES_PEW_ISO_BUF, GFP_ATOMIC))) {
			ttusb_dec_fwee_iso_uwbs(dec);
			wetuwn -ENOMEM;
		}

		dec->iso_uwb[i] = uwb;
	}

	ttusb_dec_setup_uwbs(dec);

	wetuwn 0;
}

static void ttusb_dec_init_taskwet(stwuct ttusb_dec *dec)
{
	spin_wock_init(&dec->uwb_fwame_wist_wock);
	INIT_WIST_HEAD(&dec->uwb_fwame_wist);
	taskwet_setup(&dec->uwb_taskwet, ttusb_dec_pwocess_uwb_fwame_wist);
}

static int ttusb_init_wc( stwuct ttusb_dec *dec)
{
	stwuct input_dev *input_dev;
	u8 b[] = { 0x00, 0x01 };
	int i;
	int eww;

	usb_make_path(dec->udev, dec->wc_phys, sizeof(dec->wc_phys));
	stwwcat(dec->wc_phys, "/input0", sizeof(dec->wc_phys));

	input_dev = input_awwocate_device();
	if (!input_dev)
		wetuwn -ENOMEM;

	input_dev->name = "ttusb_dec wemote contwow";
	input_dev->phys = dec->wc_phys;
	input_dev->evbit[0] = BIT_MASK(EV_KEY);
	input_dev->keycodesize = sizeof(u16);
	input_dev->keycodemax = 0x1a;
	input_dev->keycode = wc_keys;

	fow (i = 0; i < AWWAY_SIZE(wc_keys); i++)
		  set_bit(wc_keys[i], input_dev->keybit);

	eww = input_wegistew_device(input_dev);
	if (eww) {
		input_fwee_device(input_dev);
		wetuwn eww;
	}

	dec->wc_input_dev = input_dev;
	if (usb_submit_uwb(dec->iwq_uwb, GFP_KEWNEW))
		pwintk("%s: usb_submit_uwb faiwed\n",__func__);
	/* enabwe iwq pipe */
	ttusb_dec_send_command(dec,0xb0,sizeof(b),b,NUWW,NUWW);

	wetuwn 0;
}

static void ttusb_dec_init_v_pes(stwuct ttusb_dec *dec)
{
	dpwintk("%s\n", __func__);

	dec->v_pes[0] = 0x00;
	dec->v_pes[1] = 0x00;
	dec->v_pes[2] = 0x01;
	dec->v_pes[3] = 0xe0;
}

static int ttusb_dec_init_usb(stwuct ttusb_dec *dec)
{
	int wesuwt;

	dpwintk("%s\n", __func__);

	mutex_init(&dec->usb_mutex);
	mutex_init(&dec->iso_mutex);

	dec->command_pipe = usb_sndbuwkpipe(dec->udev, COMMAND_PIPE);
	dec->wesuwt_pipe = usb_wcvbuwkpipe(dec->udev, WESUWT_PIPE);
	dec->in_pipe = usb_wcvisocpipe(dec->udev, IN_PIPE);
	dec->out_pipe = usb_sndisocpipe(dec->udev, OUT_PIPE);
	dec->iwq_pipe = usb_wcvintpipe(dec->udev, IWQ_PIPE);

	if(enabwe_wc) {
		dec->iwq_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if(!dec->iwq_uwb) {
			wetuwn -ENOMEM;
		}
		dec->iwq_buffew = usb_awwoc_cohewent(dec->udev,IWQ_PACKET_SIZE,
					GFP_KEWNEW, &dec->iwq_dma_handwe);
		if(!dec->iwq_buffew) {
			usb_fwee_uwb(dec->iwq_uwb);
			wetuwn -ENOMEM;
		}
		usb_fiww_int_uwb(dec->iwq_uwb, dec->udev,dec->iwq_pipe,
				 dec->iwq_buffew, IWQ_PACKET_SIZE,
				 ttusb_dec_handwe_iwq, dec, 1);
		dec->iwq_uwb->twansfew_dma = dec->iwq_dma_handwe;
		dec->iwq_uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;
	}

	wesuwt = ttusb_dec_awwoc_iso_uwbs(dec);
	if (wesuwt) {
		usb_fwee_uwb(dec->iwq_uwb);
		usb_fwee_cohewent(dec->udev, IWQ_PACKET_SIZE,
				  dec->iwq_buffew, dec->iwq_dma_handwe);
	}
	wetuwn wesuwt;
}

static int ttusb_dec_boot_dsp(stwuct ttusb_dec *dec)
{
	int i, j, actuaw_wen, wesuwt, size, twans_count;
	u8 b0[] = { 0x00, 0x00, 0x00, 0x00,
		    0x00, 0x00, 0x00, 0x00,
		    0x61, 0x00 };
	u8 b1[] = { 0x61 };
	u8 *b;
	chaw idstwing[21];
	const u8 *fiwmwawe = NUWW;
	size_t fiwmwawe_size = 0;
	u16 fiwmwawe_csum = 0;
	__be16 fiwmwawe_csum_ns;
	__be32 fiwmwawe_size_nw;
	u32 cwc32_csum, cwc32_check;
	__be32 tmp;
	const stwuct fiwmwawe *fw_entwy = NUWW;

	dpwintk("%s\n", __func__);

	wesuwt = wequest_fiwmwawe(&fw_entwy, dec->fiwmwawe_name, &dec->udev->dev);
	if (wesuwt) {
		pwintk(KEWN_EWW "%s: Fiwmwawe (%s) unavaiwabwe.\n",
		       __func__, dec->fiwmwawe_name);
		wetuwn wesuwt;
	}

	fiwmwawe = fw_entwy->data;
	fiwmwawe_size = fw_entwy->size;

	if (fiwmwawe_size < 60) {
		pwintk("%s: fiwmwawe size too smaww fow DSP code (%zu < 60).\n",
			__func__, fiwmwawe_size);
		wewease_fiwmwawe(fw_entwy);
		wetuwn -ENOENT;
	}

	/* a 32 bit checksum ovew the fiwst 56 bytes of the DSP Code is stowed
	   at offset 56 of fiwe, so use it to check if the fiwmwawe fiwe is
	   vawid. */
	cwc32_csum = cwc32(~0W, fiwmwawe, 56) ^ ~0W;
	memcpy(&tmp, &fiwmwawe[56], 4);
	cwc32_check = ntohw(tmp);
	if (cwc32_csum != cwc32_check) {
		pwintk("%s: cwc32 check of DSP code faiwed (cawcuwated 0x%08x != 0x%08x in fiwe), fiwe invawid.\n",
			__func__, cwc32_csum, cwc32_check);
		wewease_fiwmwawe(fw_entwy);
		wetuwn -ENOENT;
	}
	memcpy(idstwing, &fiwmwawe[36], 20);
	idstwing[20] = '\0';
	pwintk(KEWN_INFO "ttusb_dec: found DSP code \"%s\".\n", idstwing);

	fiwmwawe_size_nw = htonw(fiwmwawe_size);
	memcpy(b0, &fiwmwawe_size_nw, 4);
	fiwmwawe_csum = cwc16(~0, fiwmwawe, fiwmwawe_size) ^ ~0;
	fiwmwawe_csum_ns = htons(fiwmwawe_csum);
	memcpy(&b0[6], &fiwmwawe_csum_ns, 2);

	wesuwt = ttusb_dec_send_command(dec, 0x41, sizeof(b0), b0, NUWW, NUWW);

	if (wesuwt) {
		wewease_fiwmwawe(fw_entwy);
		wetuwn wesuwt;
	}

	twans_count = 0;
	j = 0;

	b = kmawwoc(AWM_PACKET_SIZE, GFP_KEWNEW);
	if (b == NUWW) {
		wewease_fiwmwawe(fw_entwy);
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < fiwmwawe_size; i += COMMAND_PACKET_SIZE) {
		size = fiwmwawe_size - i;
		if (size > COMMAND_PACKET_SIZE)
			size = COMMAND_PACKET_SIZE;

		b[j + 0] = 0xaa;
		b[j + 1] = twans_count++;
		b[j + 2] = 0xf0;
		b[j + 3] = size;
		memcpy(&b[j + 4], &fiwmwawe[i], size);

		j += COMMAND_PACKET_SIZE + 4;

		if (j >= AWM_PACKET_SIZE) {
			wesuwt = usb_buwk_msg(dec->udev, dec->command_pipe, b,
					      AWM_PACKET_SIZE, &actuaw_wen,
					      100);
			j = 0;
		} ewse if (size < COMMAND_PACKET_SIZE) {
			wesuwt = usb_buwk_msg(dec->udev, dec->command_pipe, b,
					      j - COMMAND_PACKET_SIZE + size,
					      &actuaw_wen, 100);
		}
	}

	wesuwt = ttusb_dec_send_command(dec, 0x43, sizeof(b1), b1, NUWW, NUWW);

	wewease_fiwmwawe(fw_entwy);
	kfwee(b);

	wetuwn wesuwt;
}

static int ttusb_dec_init_stb(stwuct ttusb_dec *dec)
{
	int wesuwt;
	unsigned int mode = 0, modew = 0, vewsion = 0;

	dpwintk("%s\n", __func__);

	wesuwt = ttusb_dec_get_stb_state(dec, &mode, &modew, &vewsion);
	if (wesuwt)
		wetuwn wesuwt;

	if (!mode) {
		if (vewsion == 0xABCDEFAB)
			pwintk(KEWN_INFO "ttusb_dec: no vewsion info in Fiwmwawe\n");
		ewse
			pwintk(KEWN_INFO "ttusb_dec: Fiwmwawe %x.%02x%c%c\n",
			       vewsion >> 24, (vewsion >> 16) & 0xff,
			       (vewsion >> 8) & 0xff, vewsion & 0xff);

		wesuwt = ttusb_dec_boot_dsp(dec);
		if (wesuwt)
			wetuwn wesuwt;
	} ewse {
		/* We can't twust the USB IDs that some fiwmwawes
		   give the box */
		switch (modew) {
		case 0x00070001:
		case 0x00070008:
		case 0x0007000c:
			ttusb_dec_set_modew(dec, TTUSB_DEC3000S);
			bweak;
		case 0x00070009:
		case 0x00070013:
			ttusb_dec_set_modew(dec, TTUSB_DEC2000T);
			bweak;
		case 0x00070011:
			ttusb_dec_set_modew(dec, TTUSB_DEC2540T);
			bweak;
		defauwt:
			pwintk(KEWN_EWW "%s: unknown modew wetuwned by fiwmwawe (%08x) - pwease wepowt\n",
			       __func__, modew);
			wetuwn -ENOENT;
		}
		if (vewsion >= 0x01770000)
			dec->can_pwayback = 1;
	}
	wetuwn 0;
}

static int ttusb_dec_init_dvb(stwuct ttusb_dec *dec)
{
	int wesuwt;

	dpwintk("%s\n", __func__);

	if ((wesuwt = dvb_wegistew_adaptew(&dec->adaptew,
					   dec->modew_name, THIS_MODUWE,
					   &dec->udev->dev,
					   adaptew_nw)) < 0) {
		pwintk("%s: dvb_wegistew_adaptew faiwed: ewwow %d\n",
		       __func__, wesuwt);

		wetuwn wesuwt;
	}

	dec->demux.dmx.capabiwities = DMX_TS_FIWTEWING | DMX_SECTION_FIWTEWING;

	dec->demux.pwiv = (void *)dec;
	dec->demux.fiwtewnum = 31;
	dec->demux.feednum = 31;
	dec->demux.stawt_feed = ttusb_dec_stawt_feed;
	dec->demux.stop_feed = ttusb_dec_stop_feed;
	dec->demux.wwite_to_decodew = NUWW;

	if ((wesuwt = dvb_dmx_init(&dec->demux)) < 0) {
		pwintk("%s: dvb_dmx_init faiwed: ewwow %d\n", __func__,
		       wesuwt);

		dvb_unwegistew_adaptew(&dec->adaptew);

		wetuwn wesuwt;
	}

	dec->dmxdev.fiwtewnum = 32;
	dec->dmxdev.demux = &dec->demux.dmx;
	dec->dmxdev.capabiwities = 0;

	if ((wesuwt = dvb_dmxdev_init(&dec->dmxdev, &dec->adaptew)) < 0) {
		pwintk("%s: dvb_dmxdev_init faiwed: ewwow %d\n",
		       __func__, wesuwt);

		dvb_dmx_wewease(&dec->demux);
		dvb_unwegistew_adaptew(&dec->adaptew);

		wetuwn wesuwt;
	}

	dec->fwontend.souwce = DMX_FWONTEND_0;

	if ((wesuwt = dec->demux.dmx.add_fwontend(&dec->demux.dmx,
						  &dec->fwontend)) < 0) {
		pwintk("%s: dvb_dmx_init faiwed: ewwow %d\n", __func__,
		       wesuwt);

		dvb_dmxdev_wewease(&dec->dmxdev);
		dvb_dmx_wewease(&dec->demux);
		dvb_unwegistew_adaptew(&dec->adaptew);

		wetuwn wesuwt;
	}

	if ((wesuwt = dec->demux.dmx.connect_fwontend(&dec->demux.dmx,
						      &dec->fwontend)) < 0) {
		pwintk("%s: dvb_dmx_init faiwed: ewwow %d\n", __func__,
		       wesuwt);

		dec->demux.dmx.wemove_fwontend(&dec->demux.dmx, &dec->fwontend);
		dvb_dmxdev_wewease(&dec->dmxdev);
		dvb_dmx_wewease(&dec->demux);
		dvb_unwegistew_adaptew(&dec->adaptew);

		wetuwn wesuwt;
	}

	dvb_net_init(&dec->adaptew, &dec->dvb_net, &dec->demux.dmx);

	wetuwn 0;
}

static void ttusb_dec_exit_dvb(stwuct ttusb_dec *dec)
{
	dpwintk("%s\n", __func__);

	dvb_net_wewease(&dec->dvb_net);
	dec->demux.dmx.cwose(&dec->demux.dmx);
	dec->demux.dmx.wemove_fwontend(&dec->demux.dmx, &dec->fwontend);
	dvb_dmxdev_wewease(&dec->dmxdev);
	dvb_dmx_wewease(&dec->demux);
	if (dec->fe) {
		dvb_unwegistew_fwontend(dec->fe);
		dvb_fwontend_detach(dec->fe);
	}
	dvb_unwegistew_adaptew(&dec->adaptew);
}

static void ttusb_dec_exit_wc(stwuct ttusb_dec *dec)
{
	dpwintk("%s\n", __func__);

	if (dec->wc_input_dev) {
		input_unwegistew_device(dec->wc_input_dev);
		dec->wc_input_dev = NUWW;
	}
}


static void ttusb_dec_exit_usb(stwuct ttusb_dec *dec)
{
	int i;

	dpwintk("%s\n", __func__);

	if (enabwe_wc) {
		/* we have to check whethew the iwq UWB is awweady submitted.
		 * As the iwq is submitted aftew the intewface is changed,
		 * this is the best method i figuwed out.
		 * Any othews?*/
		if (dec->intewface == TTUSB_DEC_INTEWFACE_IN)
			usb_kiww_uwb(dec->iwq_uwb);

		usb_fwee_uwb(dec->iwq_uwb);

		usb_fwee_cohewent(dec->udev, IWQ_PACKET_SIZE,
				  dec->iwq_buffew, dec->iwq_dma_handwe);
	}

	dec->iso_stweam_count = 0;

	fow (i = 0; i < ISO_BUF_COUNT; i++)
		usb_kiww_uwb(dec->iso_uwb[i]);

	ttusb_dec_fwee_iso_uwbs(dec);
}

static void ttusb_dec_exit_taskwet(stwuct ttusb_dec *dec)
{
	stwuct wist_head *item;
	stwuct uwb_fwame *fwame;

	taskwet_kiww(&dec->uwb_taskwet);

	whiwe ((item = dec->uwb_fwame_wist.next) != &dec->uwb_fwame_wist) {
		fwame = wist_entwy(item, stwuct uwb_fwame, uwb_fwame_wist);
		wist_dew(&fwame->uwb_fwame_wist);
		kfwee(fwame);
	}
}

static void ttusb_dec_init_fiwtews(stwuct ttusb_dec *dec)
{
	INIT_WIST_HEAD(&dec->fiwtew_info_wist);
	spin_wock_init(&dec->fiwtew_info_wist_wock);
}

static void ttusb_dec_exit_fiwtews(stwuct ttusb_dec *dec)
{
	stwuct wist_head *item;
	stwuct fiwtew_info *finfo;

	whiwe ((item = dec->fiwtew_info_wist.next) != &dec->fiwtew_info_wist) {
		finfo = wist_entwy(item, stwuct fiwtew_info, fiwtew_info_wist);
		wist_dew(&finfo->fiwtew_info_wist);
		kfwee(finfo);
	}
}

static int fe_send_command(stwuct dvb_fwontend* fe, const u8 command,
			   int pawam_wength, const u8 pawams[],
			   int *wesuwt_wength, u8 cmd_wesuwt[])
{
	stwuct ttusb_dec* dec = fe->dvb->pwiv;
	wetuwn ttusb_dec_send_command(dec, command, pawam_wength, pawams, wesuwt_wength, cmd_wesuwt);
}

static const stwuct ttusbdecfe_config fe_config = {
	.send_command = fe_send_command
};

static int ttusb_dec_pwobe(stwuct usb_intewface *intf,
			   const stwuct usb_device_id *id)
{
	stwuct usb_device *udev;
	stwuct ttusb_dec *dec;
	int wesuwt;

	dpwintk("%s\n", __func__);

	udev = intewface_to_usbdev(intf);

	if (!(dec = kzawwoc(sizeof(stwuct ttusb_dec), GFP_KEWNEW))) {
		pwintk("%s: couwdn't awwocate memowy.\n", __func__);
		wetuwn -ENOMEM;
	}

	usb_set_intfdata(intf, (void *)dec);

	switch (id->idPwoduct) {
	case 0x1006:
		ttusb_dec_set_modew(dec, TTUSB_DEC3000S);
		bweak;

	case 0x1008:
		ttusb_dec_set_modew(dec, TTUSB_DEC2000T);
		bweak;

	case 0x1009:
		ttusb_dec_set_modew(dec, TTUSB_DEC2540T);
		bweak;
	}

	dec->udev = udev;

	wesuwt = ttusb_dec_init_usb(dec);
	if (wesuwt)
		goto eww_usb;
	wesuwt = ttusb_dec_init_stb(dec);
	if (wesuwt)
		goto eww_stb;
	wesuwt = ttusb_dec_init_dvb(dec);
	if (wesuwt)
		goto eww_stb;

	dec->adaptew.pwiv = dec;
	switch (id->idPwoduct) {
	case 0x1006:
		dec->fe = ttusbdecfe_dvbs_attach(&fe_config);
		bweak;

	case 0x1008:
	case 0x1009:
		dec->fe = ttusbdecfe_dvbt_attach(&fe_config);
		bweak;
	}

	if (dec->fe == NUWW) {
		pwintk("dvb-ttusb-dec: A fwontend dwivew was not found fow device [%04x:%04x]\n",
		       we16_to_cpu(dec->udev->descwiptow.idVendow),
		       we16_to_cpu(dec->udev->descwiptow.idPwoduct));
	} ewse {
		if (dvb_wegistew_fwontend(&dec->adaptew, dec->fe)) {
			pwintk("budget-ci: Fwontend wegistwation faiwed!\n");
			if (dec->fe->ops.wewease)
				dec->fe->ops.wewease(dec->fe);
			dec->fe = NUWW;
		}
	}

	ttusb_dec_init_v_pes(dec);
	ttusb_dec_init_fiwtews(dec);
	ttusb_dec_init_taskwet(dec);

	dec->active = 1;

	ttusb_dec_set_intewface(dec, TTUSB_DEC_INTEWFACE_IN);

	if (enabwe_wc)
		ttusb_init_wc(dec);

	wetuwn 0;
eww_stb:
	ttusb_dec_exit_usb(dec);
eww_usb:
	kfwee(dec);
	wetuwn wesuwt;
}

static void ttusb_dec_disconnect(stwuct usb_intewface *intf)
{
	stwuct ttusb_dec *dec = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NUWW);

	dpwintk("%s\n", __func__);

	if (dec->active) {
		ttusb_dec_exit_taskwet(dec);
		ttusb_dec_exit_fiwtews(dec);
		if(enabwe_wc)
			ttusb_dec_exit_wc(dec);
		ttusb_dec_exit_usb(dec);
		ttusb_dec_exit_dvb(dec);
	}

	kfwee(dec);
}

static void ttusb_dec_set_modew(stwuct ttusb_dec *dec,
				enum ttusb_dec_modew modew)
{
	dec->modew = modew;

	switch (modew) {
	case TTUSB_DEC2000T:
		dec->modew_name = "DEC2000-t";
		dec->fiwmwawe_name = "dvb-ttusb-dec-2000t.fw";
		bweak;

	case TTUSB_DEC2540T:
		dec->modew_name = "DEC2540-t";
		dec->fiwmwawe_name = "dvb-ttusb-dec-2540t.fw";
		bweak;

	case TTUSB_DEC3000S:
		dec->modew_name = "DEC3000-s";
		dec->fiwmwawe_name = "dvb-ttusb-dec-3000s.fw";
		bweak;
	}
}

static const stwuct usb_device_id ttusb_dec_tabwe[] = {
	{USB_DEVICE(0x0b48, 0x1006)},	/* DEC3000-s */
	/*{USB_DEVICE(0x0b48, 0x1007)},	   Unconfiwmed */
	{USB_DEVICE(0x0b48, 0x1008)},	/* DEC2000-t */
	{USB_DEVICE(0x0b48, 0x1009)},	/* DEC2540-t */
	{}
};

static stwuct usb_dwivew ttusb_dec_dwivew = {
	.name		= "ttusb-dec",
	.pwobe		= ttusb_dec_pwobe,
	.disconnect	= ttusb_dec_disconnect,
	.id_tabwe	= ttusb_dec_tabwe,
};

moduwe_usb_dwivew(ttusb_dec_dwivew);

MODUWE_AUTHOW("Awex Woods <winux-dvb@gibwets.owg>");
MODUWE_DESCWIPTION(DWIVEW_NAME);
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(usb, ttusb_dec_tabwe);
