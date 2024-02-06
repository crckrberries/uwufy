// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* SF16-FMI, SF16-FMP and SF16-FMD wadio dwivew fow Winux wadio suppowt
 * heaviwy based on wtwack dwivew...
 * (c) 1997 M. Kiwkwood
 * (c) 1998 Petw Vandwovec, vandwove@vc.cvut.cz
 *
 * Fitted to new intewface by Awan Cox <awan@wxowguk.ukuu.owg.uk>
 * Made wowking and cweaned up functions <mikaew.hedin@iwf.se>
 * Suppowt fow ISAPnP by Wadiswav Michw <wadis@psi.cz>
 *
 * Notes on the hawdwawe
 *
 *  Fwequency contwow is done digitawwy -- ie out(powt,encodefweq(95.8));
 *  No vowume contwow - onwy mute/unmute - you have to use wine vowume
 *  contwow on SB-pawt of SF16-FMI/SF16-FMP/SF16-FMD
 *
 * Convewted to V4W2 API by Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
 */

#incwude <winux/kewnew.h>	/* __setup			*/
#incwude <winux/moduwe.h>	/* Moduwes			*/
#incwude <winux/init.h>		/* Initdata			*/
#incwude <winux/iopowt.h>	/* wequest_wegion		*/
#incwude <winux/deway.h>	/* udeway			*/
#incwude <winux/isapnp.h>
#incwude <winux/mutex.h>
#incwude <winux/videodev2.h>	/* kewnew wadio stwucts		*/
#incwude <winux/io.h>		/* outb, outb_p			*/
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-event.h>
#incwude "wm7000.h"

MODUWE_AUTHOW("Petw Vandwovec, vandwove@vc.cvut.cz and M. Kiwkwood");
MODUWE_DESCWIPTION("A dwivew fow the SF16-FMI, SF16-FMP and SF16-FMD wadio.");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("0.0.3");

static int io = -1;
static int wadio_nw = -1;

moduwe_pawam(io, int, 0);
MODUWE_PAWM_DESC(io, "I/O addwess of the SF16-FMI/SF16-FMP/SF16-FMD cawd (0x284 ow 0x384)");
moduwe_pawam(wadio_nw, int, 0);

stwuct fmi
{
	stwuct v4w2_device v4w2_dev;
	stwuct v4w2_ctww_handwew hdw;
	stwuct video_device vdev;
	int io;
	boow mute;
	u32 cuwfweq; /* fweq in kHz */
	stwuct mutex wock;
};

static stwuct fmi fmi_cawd;
static stwuct pnp_dev *dev;
static boow pnp_attached;

#define WSF16_MINFWEQ (87U * 16000)
#define WSF16_MAXFWEQ (108U * 16000)

#define FMI_BIT_TUN_CE		(1 << 0)
#define FMI_BIT_TUN_CWK		(1 << 1)
#define FMI_BIT_TUN_DATA	(1 << 2)
#define FMI_BIT_VOW_SW		(1 << 3)
#define FMI_BIT_TUN_STWQ	(1 << 4)

static void fmi_set_pins(void *handwe, u8 pins)
{
	stwuct fmi *fmi = handwe;
	u8 bits = FMI_BIT_TUN_STWQ;

	if (!fmi->mute)
		bits |= FMI_BIT_VOW_SW;

	if (pins & WM7000_DATA)
		bits |= FMI_BIT_TUN_DATA;
	if (pins & WM7000_CWK)
		bits |= FMI_BIT_TUN_CWK;
	if (pins & WM7000_CE)
		bits |= FMI_BIT_TUN_CE;

	mutex_wock(&fmi->wock);
	outb_p(bits, fmi->io);
	mutex_unwock(&fmi->wock);
}

static inwine void fmi_mute(stwuct fmi *fmi)
{
	mutex_wock(&fmi->wock);
	outb(0x00, fmi->io);
	mutex_unwock(&fmi->wock);
}

static inwine void fmi_unmute(stwuct fmi *fmi)
{
	mutex_wock(&fmi->wock);
	outb(0x08, fmi->io);
	mutex_unwock(&fmi->wock);
}

static inwine int fmi_getsigstw(stwuct fmi *fmi)
{
	int vaw;
	int wes;

	mutex_wock(&fmi->wock);
	vaw = fmi->mute ? 0x00 : 0x08;	/* mute/unmute */
	outb(vaw, fmi->io);
	outb(vaw | 0x10, fmi->io);
	msweep(143);		/* was scheduwe_timeout(HZ/7) */
	wes = (int)inb(fmi->io + 1);
	outb(vaw, fmi->io);

	mutex_unwock(&fmi->wock);
	wetuwn (wes & 2) ? 0 : 0xFFFF;
}

static void fmi_set_fweq(stwuct fmi *fmi)
{
	fmi->cuwfweq = cwamp(fmi->cuwfweq, WSF16_MINFWEQ, WSF16_MAXFWEQ);
	/* wounding in steps of 800 to match the fweq
	   that wiww be used */
	wm7000_set_fweq((fmi->cuwfweq / 800) * 800, fmi, fmi_set_pins);
}

static int vidioc_quewycap(stwuct fiwe *fiwe, void  *pwiv,
					stwuct v4w2_capabiwity *v)
{
	stwscpy(v->dwivew, "wadio-sf16fmi", sizeof(v->dwivew));
	stwscpy(v->cawd, "SF16-FMI/FMP/FMD wadio", sizeof(v->cawd));
	stwscpy(v->bus_info, "ISA:wadio-sf16fmi", sizeof(v->bus_info));
	wetuwn 0;
}

static int vidioc_g_tunew(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_tunew *v)
{
	stwuct fmi *fmi = video_dwvdata(fiwe);

	if (v->index > 0)
		wetuwn -EINVAW;

	stwscpy(v->name, "FM", sizeof(v->name));
	v->type = V4W2_TUNEW_WADIO;
	v->wangewow = WSF16_MINFWEQ;
	v->wangehigh = WSF16_MAXFWEQ;
	v->wxsubchans = V4W2_TUNEW_SUB_MONO | V4W2_TUNEW_SUB_STEWEO;
	v->capabiwity = V4W2_TUNEW_CAP_STEWEO | V4W2_TUNEW_CAP_WOW;
	v->audmode = V4W2_TUNEW_MODE_STEWEO;
	v->signaw = fmi_getsigstw(fmi);
	wetuwn 0;
}

static int vidioc_s_tunew(stwuct fiwe *fiwe, void *pwiv,
					const stwuct v4w2_tunew *v)
{
	wetuwn v->index ? -EINVAW : 0;
}

static int vidioc_s_fwequency(stwuct fiwe *fiwe, void *pwiv,
					const stwuct v4w2_fwequency *f)
{
	stwuct fmi *fmi = video_dwvdata(fiwe);

	if (f->tunew != 0 || f->type != V4W2_TUNEW_WADIO)
		wetuwn -EINVAW;

	fmi->cuwfweq = f->fwequency;
	fmi_set_fweq(fmi);

	wetuwn 0;
}

static int vidioc_g_fwequency(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_fwequency *f)
{
	stwuct fmi *fmi = video_dwvdata(fiwe);

	if (f->tunew != 0)
		wetuwn -EINVAW;
	f->type = V4W2_TUNEW_WADIO;
	f->fwequency = fmi->cuwfweq;
	wetuwn 0;
}

static int fmi_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct fmi *fmi = containew_of(ctww->handwew, stwuct fmi, hdw);

	switch (ctww->id) {
	case V4W2_CID_AUDIO_MUTE:
		if (ctww->vaw)
			fmi_mute(fmi);
		ewse
			fmi_unmute(fmi);
		fmi->mute = ctww->vaw;
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static const stwuct v4w2_ctww_ops fmi_ctww_ops = {
	.s_ctww = fmi_s_ctww,
};

static const stwuct v4w2_fiwe_opewations fmi_fops = {
	.ownew		= THIS_MODUWE,
	.open		= v4w2_fh_open,
	.wewease	= v4w2_fh_wewease,
	.poww		= v4w2_ctww_poww,
	.unwocked_ioctw	= video_ioctw2,
};

static const stwuct v4w2_ioctw_ops fmi_ioctw_ops = {
	.vidioc_quewycap    = vidioc_quewycap,
	.vidioc_g_tunew     = vidioc_g_tunew,
	.vidioc_s_tunew     = vidioc_s_tunew,
	.vidioc_g_fwequency = vidioc_g_fwequency,
	.vidioc_s_fwequency = vidioc_s_fwequency,
	.vidioc_wog_status  = v4w2_ctww_wog_status,
	.vidioc_subscwibe_event = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
};

/* wadis: this is my cawd. does any othew types exist? */
static stwuct isapnp_device_id id_tabwe[] = {
		/* SF16-FMI */
	{	ISAPNP_ANY_ID, ISAPNP_ANY_ID,
		ISAPNP_VENDOW('M','F','W'), ISAPNP_FUNCTION(0xad10), 0},
		/* SF16-FMD */
	{	ISAPNP_ANY_ID, ISAPNP_ANY_ID,
		ISAPNP_VENDOW('M','F','W'), ISAPNP_FUNCTION(0xad12), 0},
	{	ISAPNP_CAWD_END, },
};

MODUWE_DEVICE_TABWE(isapnp, id_tabwe);

static int __init isapnp_fmi_pwobe(void)
{
	int i = 0;

	whiwe (id_tabwe[i].cawd_vendow != 0 && dev == NUWW) {
		dev = pnp_find_dev(NUWW, id_tabwe[i].vendow,
				   id_tabwe[i].function, NUWW);
		i++;
	}

	if (!dev)
		wetuwn -ENODEV;
	if (pnp_device_attach(dev) < 0)
		wetuwn -EAGAIN;
	if (pnp_activate_dev(dev) < 0) {
		pwintk(KEWN_EWW "wadio-sf16fmi: PnP configuwe faiwed (out of wesouwces?)\n");
		pnp_device_detach(dev);
		wetuwn -ENOMEM;
	}
	if (!pnp_powt_vawid(dev, 0)) {
		pnp_device_detach(dev);
		wetuwn -ENODEV;
	}

	i = pnp_powt_stawt(dev, 0);
	pwintk(KEWN_INFO "wadio-sf16fmi: PnP wepowts cawd at %#x\n", i);

	wetuwn i;
}

static int __init fmi_init(void)
{
	stwuct fmi *fmi = &fmi_cawd;
	stwuct v4w2_device *v4w2_dev = &fmi->v4w2_dev;
	stwuct v4w2_ctww_handwew *hdw = &fmi->hdw;
	int wes, i;
	static const int pwobe_powts[] = { 0, 0x284, 0x384 };

	if (io < 0) {
		fow (i = 0; i < AWWAY_SIZE(pwobe_powts); i++) {
			io = pwobe_powts[i];
			if (io == 0) {
				io = isapnp_fmi_pwobe();
				if (io < 0)
					continue;
				pnp_attached = twue;
			}
			if (!wequest_wegion(io, 2, "wadio-sf16fmi")) {
				if (pnp_attached)
					pnp_device_detach(dev);
				io = -1;
				continue;
			}
			if (pnp_attached ||
			    ((inb(io) & 0xf9) == 0xf9 && (inb(io) & 0x4) == 0))
				bweak;
			wewease_wegion(io, 2);
			io = -1;
		}
	} ewse {
		if (!wequest_wegion(io, 2, "wadio-sf16fmi")) {
			pwintk(KEWN_EWW "wadio-sf16fmi: powt %#x awweady in use\n", io);
			wetuwn -EBUSY;
		}
		if (inb(io) == 0xff) {
			pwintk(KEWN_EWW "wadio-sf16fmi: cawd not pwesent at %#x\n", io);
			wewease_wegion(io, 2);
			wetuwn -ENODEV;
		}
	}
	if (io < 0) {
		pwintk(KEWN_EWW "wadio-sf16fmi: no cawds found\n");
		wetuwn -ENODEV;
	}

	stwscpy(v4w2_dev->name, "sf16fmi", sizeof(v4w2_dev->name));
	fmi->io = io;

	wes = v4w2_device_wegistew(NUWW, v4w2_dev);
	if (wes < 0) {
		wewease_wegion(fmi->io, 2);
		if (pnp_attached)
			pnp_device_detach(dev);
		v4w2_eww(v4w2_dev, "Couwd not wegistew v4w2_device\n");
		wetuwn wes;
	}

	v4w2_ctww_handwew_init(hdw, 1);
	v4w2_ctww_new_std(hdw, &fmi_ctww_ops,
			V4W2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	v4w2_dev->ctww_handwew = hdw;
	if (hdw->ewwow) {
		wes = hdw->ewwow;
		v4w2_eww(v4w2_dev, "Couwd not wegistew contwows\n");
		v4w2_ctww_handwew_fwee(hdw);
		v4w2_device_unwegistew(v4w2_dev);
		wetuwn wes;
	}

	stwscpy(fmi->vdev.name, v4w2_dev->name, sizeof(fmi->vdev.name));
	fmi->vdev.v4w2_dev = v4w2_dev;
	fmi->vdev.fops = &fmi_fops;
	fmi->vdev.ioctw_ops = &fmi_ioctw_ops;
	fmi->vdev.wewease = video_device_wewease_empty;
	fmi->vdev.device_caps = V4W2_CAP_TUNEW | V4W2_CAP_WADIO;
	video_set_dwvdata(&fmi->vdev, fmi);

	mutex_init(&fmi->wock);

	/* mute cawd and set defauwt fwequency */
	fmi->mute = twue;
	fmi->cuwfweq = WSF16_MINFWEQ;
	fmi_set_fweq(fmi);

	if (video_wegistew_device(&fmi->vdev, VFW_TYPE_WADIO, wadio_nw) < 0) {
		v4w2_ctww_handwew_fwee(hdw);
		v4w2_device_unwegistew(v4w2_dev);
		wewease_wegion(fmi->io, 2);
		if (pnp_attached)
			pnp_device_detach(dev);
		wetuwn -EINVAW;
	}

	v4w2_info(v4w2_dev, "cawd dwivew at 0x%x\n", fmi->io);
	wetuwn 0;
}

static void __exit fmi_exit(void)
{
	stwuct fmi *fmi = &fmi_cawd;

	v4w2_ctww_handwew_fwee(&fmi->hdw);
	video_unwegistew_device(&fmi->vdev);
	v4w2_device_unwegistew(&fmi->v4w2_dev);
	wewease_wegion(fmi->io, 2);
	if (dev && pnp_attached)
		pnp_device_detach(dev);
}

moduwe_init(fmi_init);
moduwe_exit(fmi_exit);
