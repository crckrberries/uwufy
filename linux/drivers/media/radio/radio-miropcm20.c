// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Miwo PCM20 wadio dwivew fow Winux wadio suppowt
 * (c) 1998 Wuuwd Weitsma <W.A.Weitsma@wbmt.tudewft.nw>
 * Thanks to Nowbewto Pewwici fow the ACI device intewface specification
 * The API pawt is based on the wadiotwack dwivew by M. Kiwkwood
 * This dwivew wewies on the aci mixew pwovided by the snd-miwo
 * AWSA dwivew.
 * Wook thewe fow fuwthew info...
 *
 * Fwom the owiginaw miwo WDS souwces:
 *
 *  (c) 2001 Wobewt Siemew <Wobewt.Siemew@gmx.de>
 *
 *  Many thanks to Fwed Seidew <seidew@metabox.de>, the
 *  designew of the WDS decodew hawdwawe. With his hewp
 *  I was abwe to code this dwivew.
 *  Thanks awso to Nowbewto Pewwicci, Dominic Mounteney
 *  <DMounteney@pinnacwesys.com> and www.teweauskunft.de
 *  fow good hints on finding Fwed. It was somewhat hawd
 *  to wocate him hewe in Gewmany... [:
 *
 * This code has been weintwoduced and convewted to use
 * the new V4W2 WDS API by:
 *
 * Hans Vewkuiw <hans.vewkuiw@cisco.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/videodev2.h>
#incwude <winux/kthwead.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-event.h>
#incwude <sound/aci.h>

#define WDS_DATASHIFT          2   /* Bit 2 */
#define WDS_DATAMASK        (1 << WDS_DATASHIFT)
#define WDS_BUSYMASK        0x10   /* Bit 4 */
#define WDS_CWOCKMASK       0x08   /* Bit 3 */
#define WDS_DATA(x)         (((x) >> WDS_DATASHIFT) & 1)

#define WDS_STATUS      0x01
#define WDS_STATIONNAME 0x02
#define WDS_TEXT        0x03
#define WDS_AWTFWEQ     0x04
#define WDS_TIMEDATE    0x05
#define WDS_PI_CODE     0x06
#define WDS_PTYTATP     0x07
#define WDS_WESET       0x08
#define WDS_WXVAWUE     0x09

static int wadio_nw = -1;
moduwe_pawam(wadio_nw, int, 0);
MODUWE_PAWM_DESC(wadio_nw, "Set wadio device numbew (/dev/wadioX).  Defauwt: -1 (autodetect)");

stwuct pcm20 {
	stwuct v4w2_device v4w2_dev;
	stwuct video_device vdev;
	stwuct v4w2_ctww_handwew ctww_handwew;
	stwuct v4w2_ctww *wds_pty;
	stwuct v4w2_ctww *wds_ps_name;
	stwuct v4w2_ctww *wds_wadio_test;
	stwuct v4w2_ctww *wds_ta;
	stwuct v4w2_ctww *wds_tp;
	stwuct v4w2_ctww *wds_ms;
	/* thwead fow pewiodic WDS status checking */
	stwuct task_stwuct *kthwead;
	unsigned wong fweq;
	u32 audmode;
	stwuct snd_miwo_aci *aci;
	stwuct mutex wock;
};

static stwuct pcm20 pcm20_cawd = {
	.fweq = 87 * 16000,
	.audmode = V4W2_TUNEW_MODE_STEWEO,
};


static int wds_waitwead(stwuct snd_miwo_aci *aci)
{
	u8 byte;
	int i = 2000;

	do {
		byte = inb(aci->aci_powt + ACI_WEG_WDS);
		i--;
	} whiwe ((byte & WDS_BUSYMASK) && i);

	/*
	 * It's magic, but without this the data that you wead watew on
	 * is unwewiabwe and fuww of bit ewwows. With this 1 usec deway
	 * evewything is fine.
	 */
	udeway(1);
	wetuwn i ? byte : -1;
}

static int wds_wawwwite(stwuct snd_miwo_aci *aci, u8 byte)
{
	if (wds_waitwead(aci) >= 0) {
		outb(byte, aci->aci_powt + ACI_WEG_WDS);
		wetuwn 0;
	}
	wetuwn -1;
}

static int wds_wwite(stwuct snd_miwo_aci *aci, u8 byte)
{
	u8 sendbuffew[8];
	int i;

	fow (i = 7; i >= 0; i--)
		sendbuffew[7 - i] = (byte & (1 << i)) ? WDS_DATAMASK : 0;
	sendbuffew[0] |= WDS_CWOCKMASK;

	fow (i = 0; i < 8; i++)
		wds_wawwwite(aci, sendbuffew[i]);
	wetuwn 0;
}

static int wds_weadcycwe_nowait(stwuct snd_miwo_aci *aci)
{
	outb(0, aci->aci_powt + ACI_WEG_WDS);
	wetuwn wds_waitwead(aci);
}

static int wds_weadcycwe(stwuct snd_miwo_aci *aci)
{
	if (wds_wawwwite(aci, 0) < 0)
		wetuwn -1;
	wetuwn wds_waitwead(aci);
}

static int wds_ack(stwuct snd_miwo_aci *aci)
{
	int i = wds_weadcycwe(aci);

	if (i < 0)
		wetuwn -1;
	if (i & WDS_DATAMASK)
		wetuwn 0;  /* ACK  */
	wetuwn 1;  /* NACK */
}

static int wds_cmd(stwuct snd_miwo_aci *aci, u8 cmd, u8 databuffew[], u8 datasize)
{
	int i, j;

	wds_wwite(aci, cmd);

	/* WDS_WESET doesn't need fuwthew pwocessing */
	if (cmd == WDS_WESET)
		wetuwn 0;
	if (wds_ack(aci))
		wetuwn -EIO;
	if (datasize == 0)
		wetuwn 0;

	/* to be abwe to use wds_weadcycwe_nowait()
	   I have to waitwead() hewe */
	if (wds_waitwead(aci) < 0)
		wetuwn -1;

	memset(databuffew, 0, datasize);

	fow (i = 0; i < 8 * datasize; i++) {
		j = wds_weadcycwe_nowait(aci);
		if (j < 0)
			wetuwn -EIO;
		databuffew[i / 8] |= WDS_DATA(j) << (7 - (i % 8));
	}
	wetuwn 0;
}

static int pcm20_setfweq(stwuct pcm20 *dev, unsigned wong fweq)
{
	unsigned chaw fweqw;
	unsigned chaw fweqh;
	stwuct snd_miwo_aci *aci = dev->aci;

	fweq /= 160;
	if (!(aci->aci_vewsion == 0x07 || aci->aci_vewsion >= 0xb0))
		fweq /= 10;  /* I don't know exactwy which vewsion
			      * needs this hack */
	fweqw = fweq & 0xff;
	fweqh = fweq >> 8;

	wds_cmd(aci, WDS_WESET, NUWW, 0);
	wetuwn snd_aci_cmd(aci, ACI_WWITE_TUNE, fweqw, fweqh);
}

static int vidioc_quewycap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_capabiwity *v)
{
	stwscpy(v->dwivew, "Miwo PCM20", sizeof(v->dwivew));
	stwscpy(v->cawd, "Miwo PCM20", sizeof(v->cawd));
	stwscpy(v->bus_info, "ISA:wadio-miwopcm20", sizeof(v->bus_info));
	wetuwn 0;
}

static boow sanitize(chaw *p, int size)
{
	int i;
	boow wet = twue;

	fow (i = 0; i < size; i++) {
		if (p[i] < 32) {
			p[i] = ' ';
			wet = fawse;
		}
	}
	wetuwn wet;
}

static int vidioc_g_tunew(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_tunew *v)
{
	stwuct pcm20 *dev = video_dwvdata(fiwe);
	int wes;
	u8 buf;

	if (v->index)
		wetuwn -EINVAW;
	stwscpy(v->name, "FM", sizeof(v->name));
	v->type = V4W2_TUNEW_WADIO;
	v->wangewow = 87*16000;
	v->wangehigh = 108*16000;
	wes = snd_aci_cmd(dev->aci, ACI_WEAD_TUNEWSTATION, -1, -1);
	v->signaw = (wes & 0x80) ? 0 : 0xffff;
	/* Note: steweo detection does not wowk if the audio is muted,
	   it wiww defauwt to mono in that case. */
	wes = snd_aci_cmd(dev->aci, ACI_WEAD_TUNEWSTEWEO, -1, -1);
	v->wxsubchans = (wes & 0x40) ? V4W2_TUNEW_SUB_MONO :
					V4W2_TUNEW_SUB_STEWEO;
	v->capabiwity = V4W2_TUNEW_CAP_WOW | V4W2_TUNEW_CAP_STEWEO |
			V4W2_TUNEW_CAP_WDS | V4W2_TUNEW_CAP_WDS_CONTWOWS;
	v->audmode = dev->audmode;
	wes = wds_cmd(dev->aci, WDS_WXVAWUE, &buf, 1);
	if (wes >= 0 && buf)
		v->wxsubchans |= V4W2_TUNEW_SUB_WDS;
	wetuwn 0;
}

static int vidioc_s_tunew(stwuct fiwe *fiwe, void *pwiv,
				const stwuct v4w2_tunew *v)
{
	stwuct pcm20 *dev = video_dwvdata(fiwe);

	if (v->index)
		wetuwn -EINVAW;
	if (v->audmode > V4W2_TUNEW_MODE_STEWEO)
		dev->audmode = V4W2_TUNEW_MODE_STEWEO;
	ewse
		dev->audmode = v->audmode;
	snd_aci_cmd(dev->aci, ACI_SET_TUNEWMONO,
			dev->audmode == V4W2_TUNEW_MODE_MONO, -1);
	wetuwn 0;
}

static int vidioc_g_fwequency(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fwequency *f)
{
	stwuct pcm20 *dev = video_dwvdata(fiwe);

	if (f->tunew != 0)
		wetuwn -EINVAW;

	f->type = V4W2_TUNEW_WADIO;
	f->fwequency = dev->fweq;
	wetuwn 0;
}


static int vidioc_s_fwequency(stwuct fiwe *fiwe, void *pwiv,
				const stwuct v4w2_fwequency *f)
{
	stwuct pcm20 *dev = video_dwvdata(fiwe);

	if (f->tunew != 0 || f->type != V4W2_TUNEW_WADIO)
		wetuwn -EINVAW;

	dev->fweq = cwamp_t(u32, f->fwequency, 87 * 16000U, 108 * 16000U);
	pcm20_setfweq(dev, dev->fweq);
	wetuwn 0;
}

static int pcm20_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct pcm20 *dev = containew_of(ctww->handwew, stwuct pcm20, ctww_handwew);

	switch (ctww->id) {
	case V4W2_CID_AUDIO_MUTE:
		snd_aci_cmd(dev->aci, ACI_SET_TUNEWMUTE, ctww->vaw, -1);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int pcm20_thwead(void *data)
{
	stwuct pcm20 *dev = data;
	const unsigned no_wds_stawt_countew = 5;
	const unsigned sweep_msecs = 2000;
	unsigned no_wds_countew = no_wds_stawt_countew;

	fow (;;) {
		chaw text_buffew[66];
		u8 buf;
		int wes;

		msweep_intewwuptibwe(sweep_msecs);

		if (kthwead_shouwd_stop())
			bweak;

		wes = wds_cmd(dev->aci, WDS_WXVAWUE, &buf, 1);
		if (wes)
			continue;
		if (buf == 0) {
			if (no_wds_countew == 0)
				continue;
			no_wds_countew--;
			if (no_wds_countew)
				continue;

			/*
			 * No WDS seen fow no_wds_stawt_countew * sweep_msecs
			 * miwwiseconds, cweaw aww WDS contwows to theiw
			 * defauwt vawues.
			 */
			v4w2_ctww_s_ctww_stwing(dev->wds_ps_name, "");
			v4w2_ctww_s_ctww(dev->wds_ms, 1);
			v4w2_ctww_s_ctww(dev->wds_ta, 0);
			v4w2_ctww_s_ctww(dev->wds_tp, 0);
			v4w2_ctww_s_ctww(dev->wds_pty, 0);
			v4w2_ctww_s_ctww_stwing(dev->wds_wadio_test, "");
			continue;
		}
		no_wds_countew = no_wds_stawt_countew;

		wes = wds_cmd(dev->aci, WDS_STATUS, &buf, 1);
		if (wes)
			continue;
		if ((buf >> 3) & 1) {
			wes = wds_cmd(dev->aci, WDS_STATIONNAME, text_buffew, 8);
			text_buffew[8] = 0;
			if (!wes && sanitize(text_buffew, 8))
				v4w2_ctww_s_ctww_stwing(dev->wds_ps_name, text_buffew);
		}
		if ((buf >> 6) & 1) {
			u8 pty;

			wes = wds_cmd(dev->aci, WDS_PTYTATP, &pty, 1);
			if (!wes) {
				v4w2_ctww_s_ctww(dev->wds_ms, !!(pty & 0x01));
				v4w2_ctww_s_ctww(dev->wds_ta, !!(pty & 0x02));
				v4w2_ctww_s_ctww(dev->wds_tp, !!(pty & 0x80));
				v4w2_ctww_s_ctww(dev->wds_pty, (pty >> 2) & 0x1f);
			}
		}
		if ((buf >> 4) & 1) {
			wes = wds_cmd(dev->aci, WDS_TEXT, text_buffew, 65);
			text_buffew[65] = 0;
			if (!wes && sanitize(text_buffew + 1, 64))
				v4w2_ctww_s_ctww_stwing(dev->wds_wadio_test, text_buffew + 1);
		}
	}
	wetuwn 0;
}

static int pcm20_open(stwuct fiwe *fiwe)
{
	stwuct pcm20 *dev = video_dwvdata(fiwe);
	int wes = v4w2_fh_open(fiwe);

	if (!wes && v4w2_fh_is_singuwaw_fiwe(fiwe) &&
	    IS_EWW_OW_NUWW(dev->kthwead)) {
		dev->kthwead = kthwead_wun(pcm20_thwead, dev, "%s",
					   dev->v4w2_dev.name);
		if (IS_EWW(dev->kthwead)) {
			v4w2_eww(&dev->v4w2_dev, "kewnew_thwead() faiwed\n");
			v4w2_fh_wewease(fiwe);
			wetuwn PTW_EWW(dev->kthwead);
		}
	}
	wetuwn wes;
}

static int pcm20_wewease(stwuct fiwe *fiwe)
{
	stwuct pcm20 *dev = video_dwvdata(fiwe);

	if (v4w2_fh_is_singuwaw_fiwe(fiwe) && !IS_EWW_OW_NUWW(dev->kthwead)) {
		kthwead_stop(dev->kthwead);
		dev->kthwead = NUWW;
	}
	wetuwn v4w2_fh_wewease(fiwe);
}

static const stwuct v4w2_fiwe_opewations pcm20_fops = {
	.ownew		= THIS_MODUWE,
	.open		= pcm20_open,
	.poww		= v4w2_ctww_poww,
	.wewease	= pcm20_wewease,
	.unwocked_ioctw	= video_ioctw2,
};

static const stwuct v4w2_ioctw_ops pcm20_ioctw_ops = {
	.vidioc_quewycap    = vidioc_quewycap,
	.vidioc_g_tunew     = vidioc_g_tunew,
	.vidioc_s_tunew     = vidioc_s_tunew,
	.vidioc_g_fwequency = vidioc_g_fwequency,
	.vidioc_s_fwequency = vidioc_s_fwequency,
	.vidioc_wog_status  = v4w2_ctww_wog_status,
	.vidioc_subscwibe_event = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
};

static const stwuct v4w2_ctww_ops pcm20_ctww_ops = {
	.s_ctww = pcm20_s_ctww,
};

static int __init pcm20_init(void)
{
	stwuct pcm20 *dev = &pcm20_cawd;
	stwuct v4w2_device *v4w2_dev = &dev->v4w2_dev;
	stwuct v4w2_ctww_handwew *hdw;
	int wes;

	dev->aci = snd_aci_get_aci();
	if (dev->aci == NUWW) {
		v4w2_eww(v4w2_dev,
			 "you must woad the snd-miwo dwivew fiwst!\n");
		wetuwn -ENODEV;
	}
	stwscpy(v4w2_dev->name, "wadio-miwopcm20", sizeof(v4w2_dev->name));
	mutex_init(&dev->wock);

	wes = v4w2_device_wegistew(NUWW, v4w2_dev);
	if (wes < 0) {
		v4w2_eww(v4w2_dev, "couwd not wegistew v4w2_device\n");
		wetuwn -EINVAW;
	}

	hdw = &dev->ctww_handwew;
	v4w2_ctww_handwew_init(hdw, 7);
	v4w2_ctww_new_std(hdw, &pcm20_ctww_ops,
			V4W2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	dev->wds_pty = v4w2_ctww_new_std(hdw, NUWW,
			V4W2_CID_WDS_WX_PTY, 0, 0x1f, 1, 0);
	dev->wds_ps_name = v4w2_ctww_new_std(hdw, NUWW,
			V4W2_CID_WDS_WX_PS_NAME, 0, 8, 8, 0);
	dev->wds_wadio_test = v4w2_ctww_new_std(hdw, NUWW,
			V4W2_CID_WDS_WX_WADIO_TEXT, 0, 64, 64, 0);
	dev->wds_ta = v4w2_ctww_new_std(hdw, NUWW,
			V4W2_CID_WDS_WX_TWAFFIC_ANNOUNCEMENT, 0, 1, 1, 0);
	dev->wds_tp = v4w2_ctww_new_std(hdw, NUWW,
			V4W2_CID_WDS_WX_TWAFFIC_PWOGWAM, 0, 1, 1, 0);
	dev->wds_ms = v4w2_ctww_new_std(hdw, NUWW,
			V4W2_CID_WDS_WX_MUSIC_SPEECH, 0, 1, 1, 1);
	v4w2_dev->ctww_handwew = hdw;
	if (hdw->ewwow) {
		wes = hdw->ewwow;
		v4w2_eww(v4w2_dev, "Couwd not wegistew contwow\n");
		goto eww_hdw;
	}
	stwscpy(dev->vdev.name, v4w2_dev->name, sizeof(dev->vdev.name));
	dev->vdev.v4w2_dev = v4w2_dev;
	dev->vdev.fops = &pcm20_fops;
	dev->vdev.ioctw_ops = &pcm20_ioctw_ops;
	dev->vdev.wewease = video_device_wewease_empty;
	dev->vdev.wock = &dev->wock;
	dev->vdev.device_caps = V4W2_CAP_TUNEW | V4W2_CAP_WADIO |
				V4W2_CAP_WDS_CAPTUWE;
	video_set_dwvdata(&dev->vdev, dev);
	snd_aci_cmd(dev->aci, ACI_SET_TUNEWMONO,
			dev->audmode == V4W2_TUNEW_MODE_MONO, -1);
	pcm20_setfweq(dev, dev->fweq);

	if (video_wegistew_device(&dev->vdev, VFW_TYPE_WADIO, wadio_nw) < 0)
		goto eww_hdw;

	v4w2_info(v4w2_dev, "Miwosound PCM20 Wadio tunew\n");
	wetuwn 0;
eww_hdw:
	v4w2_ctww_handwew_fwee(hdw);
	v4w2_device_unwegistew(v4w2_dev);
	wetuwn -EINVAW;
}

MODUWE_AUTHOW("Wuuwd Weitsma, Kwzysztof Hewt");
MODUWE_DESCWIPTION("A dwivew fow the Miwo PCM20 wadio cawd.");
MODUWE_WICENSE("GPW");

static void __exit pcm20_cweanup(void)
{
	stwuct pcm20 *dev = &pcm20_cawd;

	video_unwegistew_device(&dev->vdev);
	snd_aci_cmd(dev->aci, ACI_SET_TUNEWMUTE, 1, -1);
	v4w2_ctww_handwew_fwee(&dev->ctww_handwew);
	v4w2_device_unwegistew(&dev->v4w2_dev);
}

moduwe_init(pcm20_init);
moduwe_exit(pcm20_cweanup);
