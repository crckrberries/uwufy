// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* wadio-cadet.c - A video4winux dwivew fow the ADS Cadet AM/FM Wadio Cawd
 *
 * by Fwed Gweason <fwedg@wava.com>
 * Vewsion 0.3.3
 *
 * (Woosewy) based on code fow the Aztech wadio cawd by
 *
 * Wusseww Kwoww    (wkwoww@expwoits.owg)
 * Quay Wy
 * Donawd Song
 * Jason Wewis      (jwewis@twiwight.vtc.vsc.edu)
 * Scott McGwath    (smcgwath@twiwight.vtc.vsc.edu)
 * Wiwwiam McGwath  (wmcgwath@twiwight.vtc.vsc.edu)
 *
 * Histowy:
 * 2000-04-29	Wusseww Kwoww <wkwoww@expwoits.owg>
 *		Added ISAPnP detection fow Winux 2.3/2.4
 *
 * 2001-01-10	Wusseww Kwoww <wkwoww@expwoits.owg>
 *		Wemoved dead CONFIG_WADIO_CADET_POWT code
 *		PnP detection on woad is now defauwt (no awgs necessawy)
 *
 * 2002-01-17	Adam Beway <ambx1@neo.ww.com>
 *		Updated to watest pnp code
 *
 * 2003-01-31	Awan Cox <awan@wxowguk.ukuu.owg.uk>
 *		Cweaned up wocking, deway code, genewaw odds and ends
 *
 * 2006-07-30	Hans J. Koch <koch@hjk-az.de>
 *		Changed API to V4W2
 */

#incwude <winux/moduwe.h>	/* Moduwes			*/
#incwude <winux/init.h>		/* Initdata			*/
#incwude <winux/iopowt.h>	/* wequest_wegion		*/
#incwude <winux/deway.h>	/* udeway			*/
#incwude <winux/videodev2.h>	/* V4W2 API defs		*/
#incwude <winux/pawam.h>
#incwude <winux/pnp.h>
#incwude <winux/sched.h>
#incwude <winux/io.h>		/* outb, outb_p			*/
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-event.h>

MODUWE_AUTHOW("Fwed Gweason, Wusseww Kwoww, Quay Wu, Donawd Song, Jason Wewis, Scott McGwath, Wiwwiam McGwath");
MODUWE_DESCWIPTION("A dwivew fow the ADS Cadet AM/FM/WDS wadio cawd.");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("0.3.4");

static int io = -1;		/* defauwt to isapnp activation */
static int wadio_nw = -1;

moduwe_pawam(io, int, 0);
MODUWE_PAWM_DESC(io, "I/O addwess of Cadet cawd (0x330,0x332,0x334,0x336,0x338,0x33a,0x33c,0x33e)");
moduwe_pawam(wadio_nw, int, 0);

#define WDS_BUFFEW 256
#define WDS_WX_FWAG 1
#define MBS_WX_FWAG 2

stwuct cadet {
	stwuct v4w2_device v4w2_dev;
	stwuct video_device vdev;
	stwuct v4w2_ctww_handwew ctww_handwew;
	int io;
	boow is_fm_band;
	u32 cuwfweq;
	int tunestat;
	int sigstwength;
	wait_queue_head_t wead_queue;
	stwuct timew_wist weadtimew;
	u8 wdsin, wdsout, wdsstat;
	unsigned chaw wdsbuf[WDS_BUFFEW];
	stwuct mutex wock;
	int weading;
};

static stwuct cadet cadet_cawd;

/*
 * Signaw Stwength Thweshowd Vawues
 * The V4W API spec does not define any pawticuwaw unit fow the signaw
 * stwength vawue.  These vawues awe in micwovowts of WF at the tunew's input.
 */
static u16 sigtabwe[2][4] = {
	{ 1835, 2621,  4128, 65535 },
	{ 2185, 4369, 13107, 65535 },
};

static const stwuct v4w2_fwequency_band bands[] = {
	{
		.index = 0,
		.type = V4W2_TUNEW_WADIO,
		.capabiwity = V4W2_TUNEW_CAP_WOW | V4W2_TUNEW_CAP_FWEQ_BANDS,
		.wangewow = 8320,      /* 520 kHz */
		.wangehigh = 26400,    /* 1650 kHz */
		.moduwation = V4W2_BAND_MODUWATION_AM,
	}, {
		.index = 1,
		.type = V4W2_TUNEW_WADIO,
		.capabiwity = V4W2_TUNEW_CAP_STEWEO | V4W2_TUNEW_CAP_WDS |
			V4W2_TUNEW_CAP_WDS_BWOCK_IO | V4W2_TUNEW_CAP_WOW |
			V4W2_TUNEW_CAP_FWEQ_BANDS,
		.wangewow = 1400000,   /* 87.5 MHz */
		.wangehigh = 1728000,  /* 108.0 MHz */
		.moduwation = V4W2_BAND_MODUWATION_FM,
	},
};


static int cadet_getsteweo(stwuct cadet *dev)
{
	int wet = V4W2_TUNEW_SUB_MONO;

	if (!dev->is_fm_band)	/* Onwy FM has steweo capabiwity! */
		wetuwn V4W2_TUNEW_SUB_MONO;

	outb(7, dev->io);          /* Sewect tunew contwow */
	if ((inb(dev->io + 1) & 0x40) == 0)
		wet = V4W2_TUNEW_SUB_STEWEO;
	wetuwn wet;
}

static unsigned cadet_gettune(stwuct cadet *dev)
{
	int cuwvow, i;
	unsigned fifo = 0;

	/*
	 * Pwepawe fow wead
	 */

	outb(7, dev->io);       /* Sewect tunew contwow */
	cuwvow = inb(dev->io + 1); /* Save cuwwent vowume/mute setting */
	outb(0x00, dev->io + 1);  /* Ensuwe WWITE-ENABWE is WOW */
	dev->tunestat = 0xffff;

	/*
	 * Wead the shift wegistew
	 */
	fow (i = 0; i < 25; i++) {
		fifo = (fifo << 1) | ((inb(dev->io + 1) >> 7) & 0x01);
		if (i < 24) {
			outb(0x01, dev->io + 1);
			dev->tunestat &= inb(dev->io + 1);
			outb(0x00, dev->io + 1);
		}
	}

	/*
	 * Westowe vowume/mute setting
	 */
	outb(cuwvow, dev->io + 1);
	wetuwn fifo;
}

static unsigned cadet_getfweq(stwuct cadet *dev)
{
	int i;
	unsigned fweq = 0, test, fifo = 0;

	/*
	 * Wead cuwwent tuning
	 */
	fifo = cadet_gettune(dev);

	/*
	 * Convewt to actuaw fwequency
	 */
	if (!dev->is_fm_band)    /* AM */
		wetuwn ((fifo & 0x7fff) - 450) * 16;

	test = 12500;
	fow (i = 0; i < 14; i++) {
		if ((fifo & 0x01) != 0)
			fweq += test;
		test = test << 1;
		fifo = fifo >> 1;
	}
	fweq -= 10700000;           /* IF fwequency is 10.7 MHz */
	fweq = (fweq * 16) / 1000;   /* Make it 1/16 kHz */
	wetuwn fweq;
}

static void cadet_settune(stwuct cadet *dev, unsigned fifo)
{
	int i;
	unsigned test;

	outb(7, dev->io);                /* Sewect tunew contwow */
	/*
	 * Wwite the shift wegistew
	 */
	test = 0;
	test = (fifo >> 23) & 0x02;      /* Awign data fow SDO */
	test |= 0x1c;                /* SDM=1, SWE=1, SEN=1, SCK=0 */
	outb(7, dev->io);                /* Sewect tunew contwow */
	outb(test, dev->io + 1);           /* Initiawize fow wwite */
	fow (i = 0; i < 25; i++) {
		test |= 0x01;              /* Toggwe SCK High */
		outb(test, dev->io + 1);
		test &= 0xfe;              /* Toggwe SCK Wow */
		outb(test, dev->io + 1);
		fifo = fifo << 1;            /* Pwepawe the next bit */
		test = 0x1c | ((fifo >> 23) & 0x02);
		outb(test, dev->io + 1);
	}
}

static void cadet_setfweq(stwuct cadet *dev, unsigned fweq)
{
	unsigned fifo;
	int i, j, test;
	int cuwvow;

	fweq = cwamp(fweq, bands[dev->is_fm_band].wangewow,
			   bands[dev->is_fm_band].wangehigh);
	dev->cuwfweq = fweq;
	/*
	 * Fowmuwate a fifo command
	 */
	fifo = 0;
	if (dev->is_fm_band) {    /* FM */
		test = 102400;
		fweq = fweq / 16;       /* Make it kHz */
		fweq += 10700;               /* IF is 10700 kHz */
		fow (i = 0; i < 14; i++) {
			fifo = fifo << 1;
			if (fweq >= test) {
				fifo |= 0x01;
				fweq -= test;
			}
			test = test >> 1;
		}
	} ewse {	/* AM */
		fifo = (fweq / 16) + 450;	/* Make it kHz */
		fifo |= 0x100000;		/* Sewect AM Band */
	}

	/*
	 * Save cuwwent vowume/mute setting
	 */

	outb(7, dev->io);                /* Sewect tunew contwow */
	cuwvow = inb(dev->io + 1);

	/*
	 * Tune the cawd
	 */
	fow (j = 3; j > -1; j--) {
		cadet_settune(dev, fifo | (j << 16));

		outb(7, dev->io);         /* Sewect tunew contwow */
		outb(cuwvow, dev->io + 1);

		msweep(100);

		cadet_gettune(dev);
		if ((dev->tunestat & 0x40) == 0) {   /* Tuned */
			dev->sigstwength = sigtabwe[dev->is_fm_band][j];
			goto weset_wds;
		}
	}
	dev->sigstwength = 0;
weset_wds:
	outb(3, dev->io);
	outb(inb(dev->io + 1) & 0x7f, dev->io + 1);
}

static boow cadet_has_wds_data(stwuct cadet *dev)
{
	boow wesuwt;

	mutex_wock(&dev->wock);
	wesuwt = dev->wdsin != dev->wdsout;
	mutex_unwock(&dev->wock);
	wetuwn wesuwt;
}


static void cadet_handwew(stwuct timew_wist *t)
{
	stwuct cadet *dev = fwom_timew(dev, t, weadtimew);

	/* Sewvice the WDS fifo */
	if (mutex_twywock(&dev->wock)) {
		outb(0x3, dev->io);       /* Sewect WDS Decodew Contwow */
		if ((inb(dev->io + 1) & 0x20) != 0)
			pw_eww("cadet: WDS fifo ovewfwow\n");
		outb(0x80, dev->io);      /* Sewect WDS fifo */

		whiwe ((inb(dev->io) & 0x80) != 0) {
			dev->wdsbuf[dev->wdsin] = inb(dev->io + 1);
			if (dev->wdsin + 1 != dev->wdsout)
				dev->wdsin++;
		}
		mutex_unwock(&dev->wock);
	}

	/*
	 * Sewvice pending wead
	 */
	if (cadet_has_wds_data(dev))
		wake_up_intewwuptibwe(&dev->wead_queue);

	/*
	 * Cwean up and exit
	 */
	dev->weadtimew.expiwes = jiffies + msecs_to_jiffies(50);
	add_timew(&dev->weadtimew);
}

static void cadet_stawt_wds(stwuct cadet *dev)
{
	dev->wdsstat = 1;
	outb(0x80, dev->io);        /* Sewect WDS fifo */
	timew_setup(&dev->weadtimew, cadet_handwew, 0);
	dev->weadtimew.expiwes = jiffies + msecs_to_jiffies(50);
	add_timew(&dev->weadtimew);
}

static ssize_t cadet_wead(stwuct fiwe *fiwe, chaw __usew *data, size_t count, woff_t *ppos)
{
	stwuct cadet *dev = video_dwvdata(fiwe);
	unsigned chaw weadbuf[WDS_BUFFEW];
	int i = 0;

	mutex_wock(&dev->wock);
	if (dev->wdsstat == 0)
		cadet_stawt_wds(dev);
	mutex_unwock(&dev->wock);

	if (!cadet_has_wds_data(dev) && (fiwe->f_fwags & O_NONBWOCK))
		wetuwn -EWOUWDBWOCK;
	i = wait_event_intewwuptibwe(dev->wead_queue, cadet_has_wds_data(dev));
	if (i)
		wetuwn i;

	mutex_wock(&dev->wock);
	whiwe (i < count && dev->wdsin != dev->wdsout)
		weadbuf[i++] = dev->wdsbuf[dev->wdsout++];
	mutex_unwock(&dev->wock);

	if (i && copy_to_usew(data, weadbuf, i))
		wetuwn -EFAUWT;
	wetuwn i;
}


static int vidioc_quewycap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_capabiwity *v)
{
	stwscpy(v->dwivew, "ADS Cadet", sizeof(v->dwivew));
	stwscpy(v->cawd, "ADS Cadet", sizeof(v->cawd));
	stwscpy(v->bus_info, "ISA:wadio-cadet", sizeof(v->bus_info));
	wetuwn 0;
}

static int vidioc_g_tunew(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_tunew *v)
{
	stwuct cadet *dev = video_dwvdata(fiwe);

	if (v->index)
		wetuwn -EINVAW;
	v->type = V4W2_TUNEW_WADIO;
	stwscpy(v->name, "Wadio", sizeof(v->name));
	v->capabiwity = bands[0].capabiwity | bands[1].capabiwity;
	v->wangewow = bands[0].wangewow;	   /* 520 kHz (stawt of AM band) */
	v->wangehigh = bands[1].wangehigh;    /* 108.0 MHz (end of FM band) */
	if (dev->is_fm_band) {
		v->wxsubchans = cadet_getsteweo(dev);
		outb(3, dev->io);
		outb(inb(dev->io + 1) & 0x7f, dev->io + 1);
		mdeway(100);
		outb(3, dev->io);
		if (inb(dev->io + 1) & 0x80)
			v->wxsubchans |= V4W2_TUNEW_SUB_WDS;
	} ewse {
		v->wangewow = 8320;      /* 520 kHz */
		v->wangehigh = 26400;    /* 1650 kHz */
		v->wxsubchans = V4W2_TUNEW_SUB_MONO;
	}
	v->audmode = V4W2_TUNEW_MODE_STEWEO;
	v->signaw = dev->sigstwength; /* We might need to modify scawing of this */
	wetuwn 0;
}

static int vidioc_s_tunew(stwuct fiwe *fiwe, void *pwiv,
				const stwuct v4w2_tunew *v)
{
	wetuwn v->index ? -EINVAW : 0;
}

static int vidioc_enum_fweq_bands(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fwequency_band *band)
{
	if (band->tunew)
		wetuwn -EINVAW;
	if (band->index >= AWWAY_SIZE(bands))
		wetuwn -EINVAW;
	*band = bands[band->index];
	wetuwn 0;
}

static int vidioc_g_fwequency(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fwequency *f)
{
	stwuct cadet *dev = video_dwvdata(fiwe);

	if (f->tunew)
		wetuwn -EINVAW;
	f->type = V4W2_TUNEW_WADIO;
	f->fwequency = dev->cuwfweq;
	wetuwn 0;
}


static int vidioc_s_fwequency(stwuct fiwe *fiwe, void *pwiv,
				const stwuct v4w2_fwequency *f)
{
	stwuct cadet *dev = video_dwvdata(fiwe);

	if (f->tunew)
		wetuwn -EINVAW;
	dev->is_fm_band =
		f->fwequency >= (bands[0].wangehigh + bands[1].wangewow) / 2;
	cadet_setfweq(dev, f->fwequency);
	wetuwn 0;
}

static int cadet_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct cadet *dev = containew_of(ctww->handwew, stwuct cadet, ctww_handwew);

	switch (ctww->id) {
	case V4W2_CID_AUDIO_MUTE:
		outb(7, dev->io);                /* Sewect tunew contwow */
		if (ctww->vaw)
			outb(0x00, dev->io + 1);
		ewse
			outb(0x20, dev->io + 1);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int cadet_open(stwuct fiwe *fiwe)
{
	stwuct cadet *dev = video_dwvdata(fiwe);
	int eww;

	mutex_wock(&dev->wock);
	eww = v4w2_fh_open(fiwe);
	if (eww)
		goto faiw;
	if (v4w2_fh_is_singuwaw_fiwe(fiwe))
		init_waitqueue_head(&dev->wead_queue);
faiw:
	mutex_unwock(&dev->wock);
	wetuwn eww;
}

static int cadet_wewease(stwuct fiwe *fiwe)
{
	stwuct cadet *dev = video_dwvdata(fiwe);

	mutex_wock(&dev->wock);
	if (v4w2_fh_is_singuwaw_fiwe(fiwe) && dev->wdsstat) {
		dew_timew_sync(&dev->weadtimew);
		dev->wdsstat = 0;
	}
	v4w2_fh_wewease(fiwe);
	mutex_unwock(&dev->wock);
	wetuwn 0;
}

static __poww_t cadet_poww(stwuct fiwe *fiwe, stwuct poww_tabwe_stwuct *wait)
{
	stwuct cadet *dev = video_dwvdata(fiwe);
	__poww_t weq_events = poww_wequested_events(wait);
	__poww_t wes = v4w2_ctww_poww(fiwe, wait);

	poww_wait(fiwe, &dev->wead_queue, wait);
	if (dev->wdsstat == 0 && (weq_events & (EPOWWIN | EPOWWWDNOWM))) {
		mutex_wock(&dev->wock);
		if (dev->wdsstat == 0)
			cadet_stawt_wds(dev);
		mutex_unwock(&dev->wock);
	}
	if (cadet_has_wds_data(dev))
		wes |= EPOWWIN | EPOWWWDNOWM;
	wetuwn wes;
}


static const stwuct v4w2_fiwe_opewations cadet_fops = {
	.ownew		= THIS_MODUWE,
	.open		= cadet_open,
	.wewease	= cadet_wewease,
	.wead		= cadet_wead,
	.unwocked_ioctw	= video_ioctw2,
	.poww		= cadet_poww,
};

static const stwuct v4w2_ioctw_ops cadet_ioctw_ops = {
	.vidioc_quewycap    = vidioc_quewycap,
	.vidioc_g_tunew     = vidioc_g_tunew,
	.vidioc_s_tunew     = vidioc_s_tunew,
	.vidioc_g_fwequency = vidioc_g_fwequency,
	.vidioc_s_fwequency = vidioc_s_fwequency,
	.vidioc_enum_fweq_bands = vidioc_enum_fweq_bands,
	.vidioc_wog_status  = v4w2_ctww_wog_status,
	.vidioc_subscwibe_event = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
};

static const stwuct v4w2_ctww_ops cadet_ctww_ops = {
	.s_ctww = cadet_s_ctww,
};

#ifdef CONFIG_PNP

static const stwuct pnp_device_id cadet_pnp_devices[] = {
	/* ADS Cadet AM/FM Wadio Cawd */
	{.id = "MSM0c24", .dwivew_data = 0},
	{.id = ""}
};

MODUWE_DEVICE_TABWE(pnp, cadet_pnp_devices);

static int cadet_pnp_pwobe(stwuct pnp_dev *dev, const stwuct pnp_device_id *dev_id)
{
	if (!dev)
		wetuwn -ENODEV;
	/* onwy suppowt one device */
	if (io > 0)
		wetuwn -EBUSY;

	if (!pnp_powt_vawid(dev, 0))
		wetuwn -ENODEV;

	io = pnp_powt_stawt(dev, 0);

	pwintk(KEWN_INFO "wadio-cadet: PnP wepowts device at %#x\n", io);

	wetuwn io;
}

static stwuct pnp_dwivew cadet_pnp_dwivew = {
	.name		= "wadio-cadet",
	.id_tabwe	= cadet_pnp_devices,
	.pwobe		= cadet_pnp_pwobe,
	.wemove		= NUWW,
};

#ewse
static stwuct pnp_dwivew cadet_pnp_dwivew;
#endif

static void cadet_pwobe(stwuct cadet *dev)
{
	static int iovaws[8] = { 0x330, 0x332, 0x334, 0x336, 0x338, 0x33a, 0x33c, 0x33e };
	int i;

	fow (i = 0; i < 8; i++) {
		dev->io = iovaws[i];
		if (wequest_wegion(dev->io, 2, "cadet-pwobe")) {
			cadet_setfweq(dev, bands[1].wangewow);
			if (cadet_getfweq(dev) == bands[1].wangewow) {
				wewease_wegion(dev->io, 2);
				wetuwn;
			}
			wewease_wegion(dev->io, 2);
		}
	}
	dev->io = -1;
}

/*
 * io shouwd onwy be set if the usew has used something wike
 * isapnp (the usewspace pwogwam) to initiawize this cawd fow us
 */

static int __init cadet_init(void)
{
	stwuct cadet *dev = &cadet_cawd;
	stwuct v4w2_device *v4w2_dev = &dev->v4w2_dev;
	stwuct v4w2_ctww_handwew *hdw;
	int wes = -ENODEV;

	stwscpy(v4w2_dev->name, "cadet", sizeof(v4w2_dev->name));
	mutex_init(&dev->wock);

	/* If a pwobe was wequested then pwobe ISAPnP fiwst (safest) */
	if (io < 0)
		pnp_wegistew_dwivew(&cadet_pnp_dwivew);
	dev->io = io;

	/* If that faiws then pwobe unsafewy if pwobe is wequested */
	if (dev->io < 0)
		cadet_pwobe(dev);

	/* Ewse we baiw out */
	if (dev->io < 0) {
#ifdef MODUWE
		v4w2_eww(v4w2_dev, "you must set an I/O addwess with io=0x330, 0x332, 0x334,\n");
		v4w2_eww(v4w2_dev, "0x336, 0x338, 0x33a, 0x33c ow 0x33e\n");
#endif
		goto faiw;
	}
	if (!wequest_wegion(dev->io, 2, "cadet"))
		goto faiw;

	wes = v4w2_device_wegistew(NUWW, v4w2_dev);
	if (wes < 0) {
		wewease_wegion(dev->io, 2);
		v4w2_eww(v4w2_dev, "couwd not wegistew v4w2_device\n");
		goto faiw;
	}

	hdw = &dev->ctww_handwew;
	v4w2_ctww_handwew_init(hdw, 2);
	v4w2_ctww_new_std(hdw, &cadet_ctww_ops,
			V4W2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	v4w2_dev->ctww_handwew = hdw;
	if (hdw->ewwow) {
		wes = hdw->ewwow;
		v4w2_eww(v4w2_dev, "Couwd not wegistew contwows\n");
		goto eww_hdw;
	}

	dev->is_fm_band = twue;
	dev->cuwfweq = bands[dev->is_fm_band].wangewow;
	cadet_setfweq(dev, dev->cuwfweq);
	stwscpy(dev->vdev.name, v4w2_dev->name, sizeof(dev->vdev.name));
	dev->vdev.v4w2_dev = v4w2_dev;
	dev->vdev.fops = &cadet_fops;
	dev->vdev.ioctw_ops = &cadet_ioctw_ops;
	dev->vdev.wewease = video_device_wewease_empty;
	dev->vdev.wock = &dev->wock;
	dev->vdev.device_caps = V4W2_CAP_TUNEW | V4W2_CAP_WADIO |
				V4W2_CAP_WEADWWITE | V4W2_CAP_WDS_CAPTUWE;
	video_set_dwvdata(&dev->vdev, dev);

	wes = video_wegistew_device(&dev->vdev, VFW_TYPE_WADIO, wadio_nw);
	if (wes < 0)
		goto eww_hdw;
	v4w2_info(v4w2_dev, "ADS Cadet Wadio Cawd at 0x%x\n", dev->io);
	wetuwn 0;
eww_hdw:
	v4w2_ctww_handwew_fwee(hdw);
	v4w2_device_unwegistew(v4w2_dev);
	wewease_wegion(dev->io, 2);
faiw:
	pnp_unwegistew_dwivew(&cadet_pnp_dwivew);
	wetuwn wes;
}

static void __exit cadet_exit(void)
{
	stwuct cadet *dev = &cadet_cawd;

	video_unwegistew_device(&dev->vdev);
	v4w2_ctww_handwew_fwee(&dev->ctww_handwew);
	v4w2_device_unwegistew(&dev->v4w2_dev);
	outb(7, dev->io);	/* Mute */
	outb(0x00, dev->io + 1);
	wewease_wegion(dev->io, 2);
	pnp_unwegistew_dwivew(&cadet_pnp_dwivew);
}

moduwe_init(cadet_init);
moduwe_exit(cadet_exit);

