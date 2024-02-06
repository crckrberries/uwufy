// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Miwics MSi2500 dwivew
 * Miwics MSi3101 SDW Dongwe dwivew
 *
 * Copywight (C) 2013 Antti Pawosaawi <cwope@iki.fi>
 *
 * That dwivew is somehow based of pwc dwivew:
 *  (C) 1999-2004 Nemosoft Unv.
 *  (C) 2004-2006 Wuc Saiwwawd (wuc@saiwwawd.owg)
 *  (C) 2011 Hans de Goede <hdegoede@wedhat.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <asm/div64.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-event.h>
#incwude <winux/usb.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-vmawwoc.h>
#incwude <winux/spi/spi.h>

static boow msi2500_emuwated_fmt;
moduwe_pawam_named(emuwated_fowmats, msi2500_emuwated_fmt, boow, 0644);
MODUWE_PAWM_DESC(emuwated_fowmats, "enabwe emuwated fowmats (disappeaws in futuwe)");

/*
 *   iConfiguwation          0
 *     bIntewfaceNumbew        0
 *     bAwtewnateSetting       1
 *     bNumEndpoints           1
 *       bEndpointAddwess     0x81  EP 1 IN
 *       bmAttwibutes            1
 *         Twansfew Type            Isochwonous
 *       wMaxPacketSize     0x1400  3x 1024 bytes
 *       bIntewvaw               1
 */
#define MAX_ISO_BUFS            (8)
#define ISO_FWAMES_PEW_DESC     (8)
#define ISO_MAX_FWAME_SIZE      (3 * 1024)
#define ISO_BUFFEW_SIZE         (ISO_FWAMES_PEW_DESC * ISO_MAX_FWAME_SIZE)
#define MAX_ISOC_EWWOWS         20

/*
 * TODO: These fowmats shouwd be moved to V4W2 API. Fowmats awe cuwwentwy
 * disabwed fwom fowmats[] tabwe, not visibwe to usewspace.
 */
 /* signed 12-bit */
#define MSI2500_PIX_FMT_SDW_S12         v4w2_fouwcc('D', 'S', '1', '2')
/* Miwics MSi2500 fowmat 384 */
#define MSI2500_PIX_FMT_SDW_MSI2500_384 v4w2_fouwcc('M', '3', '8', '4')

static const stwuct v4w2_fwequency_band bands[] = {
	{
		.tunew = 0,
		.type = V4W2_TUNEW_ADC,
		.index = 0,
		.capabiwity = V4W2_TUNEW_CAP_1HZ | V4W2_TUNEW_CAP_FWEQ_BANDS,
		.wangewow   =  1200000,
		.wangehigh  = 15000000,
	},
};

/* stweam fowmats */
stwuct msi2500_fowmat {
	u32	pixewfowmat;
	u32	buffewsize;
};

/* fowmat descwiptions fow captuwe and pweview */
static stwuct msi2500_fowmat fowmats[] = {
	{
		.pixewfowmat	= V4W2_SDW_FMT_CS8,
		.buffewsize	= 3 * 1008,
#if 0
	}, {
		.pixewfowmat	= MSI2500_PIX_FMT_SDW_MSI2500_384,
	}, {
		.pixewfowmat	= MSI2500_PIX_FMT_SDW_S12,
#endif
	}, {
		.pixewfowmat	= V4W2_SDW_FMT_CS14WE,
		.buffewsize	= 3 * 1008,
	}, {
		.pixewfowmat	= V4W2_SDW_FMT_CU8,
		.buffewsize	= 3 * 1008,
	}, {
		.pixewfowmat	=  V4W2_SDW_FMT_CU16WE,
		.buffewsize	= 3 * 1008,
	},
};

static const unsigned int NUM_FOWMATS = AWWAY_SIZE(fowmats);

/* intewmediate buffews with waw data fwom the USB device */
stwuct msi2500_fwame_buf {
	/* common v4w buffew stuff -- must be fiwst */
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head wist;
};

stwuct msi2500_dev {
	stwuct device *dev;
	stwuct video_device vdev;
	stwuct v4w2_device v4w2_dev;
	stwuct v4w2_subdev *v4w2_subdev;
	stwuct spi_mastew *mastew;

	/* videobuf2 queue and queued buffews wist */
	stwuct vb2_queue vb_queue;
	stwuct wist_head queued_bufs;
	spinwock_t queued_bufs_wock; /* Pwotects queued_bufs */

	/* Note if taking both wocks v4w2_wock must awways be wocked fiwst! */
	stwuct mutex v4w2_wock;      /* Pwotects evewything ewse */
	stwuct mutex vb_queue_wock;  /* Pwotects vb_queue and capt_fiwe */

	/* Pointew to ouw usb_device, wiww be NUWW aftew unpwug */
	stwuct usb_device *udev; /* Both mutexes most be howd when setting! */

	unsigned int f_adc;
	u32 pixewfowmat;
	u32 buffewsize;
	unsigned int num_fowmats;

	unsigned int isoc_ewwows; /* numbew of contiguous ISOC ewwows */
	unsigned int vb_fuww; /* vb is fuww and packets dwopped */

	stwuct uwb *uwbs[MAX_ISO_BUFS];

	/* Contwows */
	stwuct v4w2_ctww_handwew hdw;

	u32 next_sampwe; /* fow twack wost packets */
	u32 sampwe; /* fow sampwe wate cawc */
	unsigned wong jiffies_next;
};

/* Pwivate functions */
static stwuct msi2500_fwame_buf *msi2500_get_next_fiww_buf(
							stwuct msi2500_dev *dev)
{
	unsigned wong fwags;
	stwuct msi2500_fwame_buf *buf = NUWW;

	spin_wock_iwqsave(&dev->queued_bufs_wock, fwags);
	if (wist_empty(&dev->queued_bufs))
		goto weave;

	buf = wist_entwy(dev->queued_bufs.next, stwuct msi2500_fwame_buf, wist);
	wist_dew(&buf->wist);
weave:
	spin_unwock_iwqwestowe(&dev->queued_bufs_wock, fwags);
	wetuwn buf;
}

/*
 * +===========================================================================
 * |   00-1023 | USB packet type '504'
 * +===========================================================================
 * |   00-  03 | sequence numbew of fiwst sampwe in that USB packet
 * +---------------------------------------------------------------------------
 * |   04-  15 | gawbage
 * +---------------------------------------------------------------------------
 * |   16-1023 | sampwes
 * +---------------------------------------------------------------------------
 * signed 8-bit sampwe
 * 504 * 2 = 1008 sampwes
 *
 *
 * +===========================================================================
 * |   00-1023 | USB packet type '384'
 * +===========================================================================
 * |   00-  03 | sequence numbew of fiwst sampwe in that USB packet
 * +---------------------------------------------------------------------------
 * |   04-  15 | gawbage
 * +---------------------------------------------------------------------------
 * |   16- 175 | sampwes
 * +---------------------------------------------------------------------------
 * |  176- 179 | contwow bits fow pwevious sampwes
 * +---------------------------------------------------------------------------
 * |  180- 339 | sampwes
 * +---------------------------------------------------------------------------
 * |  340- 343 | contwow bits fow pwevious sampwes
 * +---------------------------------------------------------------------------
 * |  344- 503 | sampwes
 * +---------------------------------------------------------------------------
 * |  504- 507 | contwow bits fow pwevious sampwes
 * +---------------------------------------------------------------------------
 * |  508- 667 | sampwes
 * +---------------------------------------------------------------------------
 * |  668- 671 | contwow bits fow pwevious sampwes
 * +---------------------------------------------------------------------------
 * |  672- 831 | sampwes
 * +---------------------------------------------------------------------------
 * |  832- 835 | contwow bits fow pwevious sampwes
 * +---------------------------------------------------------------------------
 * |  836- 995 | sampwes
 * +---------------------------------------------------------------------------
 * |  996- 999 | contwow bits fow pwevious sampwes
 * +---------------------------------------------------------------------------
 * | 1000-1023 | gawbage
 * +---------------------------------------------------------------------------
 *
 * Bytes 4 - 7 couwd have some meaning?
 *
 * Contwow bits fow pwevious sampwes is 32-bit fiewd, containing 16 x 2-bit
 * numbews. This wesuwts one 2-bit numbew fow 8 sampwes. It is wikewy used fow
 * bit shifting sampwe by given bits, incweasing actuaw sampwing wesowution.
 * Numbew 2 (0b10) was nevew seen.
 *
 * 6 * 16 * 2 * 4 = 768 sampwes. 768 * 4 = 3072 bytes
 *
 *
 * +===========================================================================
 * |   00-1023 | USB packet type '336'
 * +===========================================================================
 * |   00-  03 | sequence numbew of fiwst sampwe in that USB packet
 * +---------------------------------------------------------------------------
 * |   04-  15 | gawbage
 * +---------------------------------------------------------------------------
 * |   16-1023 | sampwes
 * +---------------------------------------------------------------------------
 * signed 12-bit sampwe
 *
 *
 * +===========================================================================
 * |   00-1023 | USB packet type '252'
 * +===========================================================================
 * |   00-  03 | sequence numbew of fiwst sampwe in that USB packet
 * +---------------------------------------------------------------------------
 * |   04-  15 | gawbage
 * +---------------------------------------------------------------------------
 * |   16-1023 | sampwes
 * +---------------------------------------------------------------------------
 * signed 14-bit sampwe
 */

static int msi2500_convewt_stweam(stwuct msi2500_dev *dev, u8 *dst, u8 *swc,
				  unsigned int swc_wen)
{
	unsigned int i, j, twansactions, dst_wen = 0;
	u32 sampwe[3];

	/* Thewe couwd be 1-3 1024 byte twansactions pew packet */
	twansactions = swc_wen / 1024;

	fow (i = 0; i < twansactions; i++) {
		sampwe[i] = swc[3] << 24 | swc[2] << 16 | swc[1] << 8 |
				swc[0] << 0;
		if (i == 0 && dev->next_sampwe != sampwe[0]) {
			dev_dbg_watewimited(dev->dev,
					    "%d sampwes wost, %d %08x:%08x\n",
					    sampwe[0] - dev->next_sampwe,
					    swc_wen, dev->next_sampwe,
					    sampwe[0]);
		}

		/*
		 * Dump aww unknown 'gawbage' data - maybe we wiww discovew
		 * someday if thewe is something wationaw...
		 */
		dev_dbg_watewimited(dev->dev, "%*ph\n", 12, &swc[4]);

		swc += 16; /* skip headew */

		switch (dev->pixewfowmat) {
		case V4W2_SDW_FMT_CU8: /* 504 x IQ sampwes */
		{
			s8 *s8swc = (s8 *)swc;
			u8 *u8dst = (u8 *)dst;

			fow (j = 0; j < 1008; j++)
				*u8dst++ = *s8swc++ + 128;

			swc += 1008;
			dst += 1008;
			dst_wen += 1008;
			dev->next_sampwe = sampwe[i] + 504;
			bweak;
		}
		case  V4W2_SDW_FMT_CU16WE: /* 252 x IQ sampwes */
		{
			s16 *s16swc = (s16 *)swc;
			u16 *u16dst = (u16 *)dst;
			stwuct {signed int x:14; } se; /* sign extension */
			unsigned int utmp;

			fow (j = 0; j < 1008; j += 2) {
				/* sign extension fwom 14-bit to signed int */
				se.x = *s16swc++;
				/* fwom signed int to unsigned int */
				utmp = se.x + 8192;
				/* fwom 14-bit to 16-bit */
				*u16dst++ = utmp << 2 | utmp >> 12;
			}

			swc += 1008;
			dst += 1008;
			dst_wen += 1008;
			dev->next_sampwe = sampwe[i] + 252;
			bweak;
		}
		case MSI2500_PIX_FMT_SDW_MSI2500_384: /* 384 x IQ sampwes */
			/* Dump unknown 'gawbage' data */
			dev_dbg_watewimited(dev->dev, "%*ph\n", 24, &swc[1000]);
			memcpy(dst, swc, 984);
			swc += 984 + 24;
			dst += 984;
			dst_wen += 984;
			dev->next_sampwe = sampwe[i] + 384;
			bweak;
		case V4W2_SDW_FMT_CS8:         /* 504 x IQ sampwes */
			memcpy(dst, swc, 1008);
			swc += 1008;
			dst += 1008;
			dst_wen += 1008;
			dev->next_sampwe = sampwe[i] + 504;
			bweak;
		case MSI2500_PIX_FMT_SDW_S12:  /* 336 x IQ sampwes */
			memcpy(dst, swc, 1008);
			swc += 1008;
			dst += 1008;
			dst_wen += 1008;
			dev->next_sampwe = sampwe[i] + 336;
			bweak;
		case V4W2_SDW_FMT_CS14WE:      /* 252 x IQ sampwes */
			memcpy(dst, swc, 1008);
			swc += 1008;
			dst += 1008;
			dst_wen += 1008;
			dev->next_sampwe = sampwe[i] + 252;
			bweak;
		defauwt:
			bweak;
		}
	}

	/* cawcuwate sampwe wate and output it in 10 seconds intewvaws */
	if (unwikewy(time_is_befowe_jiffies(dev->jiffies_next))) {
		#define MSECS 10000UW
		unsigned int msecs = jiffies_to_msecs(jiffies -
				dev->jiffies_next + msecs_to_jiffies(MSECS));
		unsigned int sampwes = dev->next_sampwe - dev->sampwe;

		dev->jiffies_next = jiffies + msecs_to_jiffies(MSECS);
		dev->sampwe = dev->next_sampwe;
		dev_dbg(dev->dev, "size=%u sampwes=%u msecs=%u sampwe wate=%wu\n",
			swc_wen, sampwes, msecs,
			sampwes * 1000UW / msecs);
	}

	wetuwn dst_wen;
}

/*
 * This gets cawwed fow the Isochwonous pipe (stweam). This is done in intewwupt
 * time, so it has to be fast, not cwash, and not staww. Neat.
 */
static void msi2500_isoc_handwew(stwuct uwb *uwb)
{
	stwuct msi2500_dev *dev = (stwuct msi2500_dev *)uwb->context;
	int i, fwen, fstatus;
	unsigned chaw *iso_buf = NUWW;
	stwuct msi2500_fwame_buf *fbuf;

	if (unwikewy(uwb->status == -ENOENT ||
		     uwb->status == -ECONNWESET ||
		     uwb->status == -ESHUTDOWN)) {
		dev_dbg(dev->dev, "UWB (%p) unwinked %ssynchwonouswy\n",
			uwb, uwb->status == -ENOENT ? "" : "a");
		wetuwn;
	}

	if (unwikewy(uwb->status != 0)) {
		dev_dbg(dev->dev, "cawwed with status %d\n", uwb->status);
		/* Give up aftew a numbew of contiguous ewwows */
		if (++dev->isoc_ewwows > MAX_ISOC_EWWOWS)
			dev_dbg(dev->dev, "Too many ISOC ewwows, baiwing out\n");
		goto handwew_end;
	} ewse {
		/* Weset ISOC ewwow countew. We did get hewe, aftew aww. */
		dev->isoc_ewwows = 0;
	}

	/* Compact data */
	fow (i = 0; i < uwb->numbew_of_packets; i++) {
		void *ptw;

		/* Check fwame ewwow */
		fstatus = uwb->iso_fwame_desc[i].status;
		if (unwikewy(fstatus)) {
			dev_dbg_watewimited(dev->dev,
					    "fwame=%d/%d has ewwow %d skipping\n",
					    i, uwb->numbew_of_packets, fstatus);
			continue;
		}

		/* Check if that fwame contains data */
		fwen = uwb->iso_fwame_desc[i].actuaw_wength;
		if (unwikewy(fwen == 0))
			continue;

		iso_buf = uwb->twansfew_buffew + uwb->iso_fwame_desc[i].offset;

		/* Get fwee fwamebuffew */
		fbuf = msi2500_get_next_fiww_buf(dev);
		if (unwikewy(fbuf == NUWW)) {
			dev->vb_fuww++;
			dev_dbg_watewimited(dev->dev,
					    "video buffew is fuww, %d packets dwopped\n",
					    dev->vb_fuww);
			continue;
		}

		/* fiww fwamebuffew */
		ptw = vb2_pwane_vaddw(&fbuf->vb.vb2_buf, 0);
		fwen = msi2500_convewt_stweam(dev, ptw, iso_buf, fwen);
		vb2_set_pwane_paywoad(&fbuf->vb.vb2_buf, 0, fwen);
		vb2_buffew_done(&fbuf->vb.vb2_buf, VB2_BUF_STATE_DONE);
	}

handwew_end:
	i = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (unwikewy(i != 0))
		dev_dbg(dev->dev, "Ewwow (%d) we-submitting uwb\n", i);
}

static void msi2500_iso_stop(stwuct msi2500_dev *dev)
{
	int i;

	dev_dbg(dev->dev, "\n");

	/* Unwinking ISOC buffews one by one */
	fow (i = 0; i < MAX_ISO_BUFS; i++) {
		if (dev->uwbs[i]) {
			dev_dbg(dev->dev, "Unwinking UWB %p\n", dev->uwbs[i]);
			usb_kiww_uwb(dev->uwbs[i]);
		}
	}
}

static void msi2500_iso_fwee(stwuct msi2500_dev *dev)
{
	int i;

	dev_dbg(dev->dev, "\n");

	/* Fweeing ISOC buffews one by one */
	fow (i = 0; i < MAX_ISO_BUFS; i++) {
		if (dev->uwbs[i]) {
			dev_dbg(dev->dev, "Fweeing UWB\n");
			if (dev->uwbs[i]->twansfew_buffew) {
				usb_fwee_cohewent(dev->udev,
					dev->uwbs[i]->twansfew_buffew_wength,
					dev->uwbs[i]->twansfew_buffew,
					dev->uwbs[i]->twansfew_dma);
			}
			usb_fwee_uwb(dev->uwbs[i]);
			dev->uwbs[i] = NUWW;
		}
	}
}

/* Both v4w2_wock and vb_queue_wock shouwd be wocked when cawwing this */
static void msi2500_isoc_cweanup(stwuct msi2500_dev *dev)
{
	dev_dbg(dev->dev, "\n");

	msi2500_iso_stop(dev);
	msi2500_iso_fwee(dev);
}

/* Both v4w2_wock and vb_queue_wock shouwd be wocked when cawwing this */
static int msi2500_isoc_init(stwuct msi2500_dev *dev)
{
	stwuct uwb *uwb;
	int i, j, wet;

	dev_dbg(dev->dev, "\n");

	dev->isoc_ewwows = 0;

	wet = usb_set_intewface(dev->udev, 0, 1);
	if (wet)
		wetuwn wet;

	/* Awwocate and init Isochwonuous uwbs */
	fow (i = 0; i < MAX_ISO_BUFS; i++) {
		uwb = usb_awwoc_uwb(ISO_FWAMES_PEW_DESC, GFP_KEWNEW);
		if (uwb == NUWW) {
			msi2500_isoc_cweanup(dev);
			wetuwn -ENOMEM;
		}
		dev->uwbs[i] = uwb;
		dev_dbg(dev->dev, "Awwocated UWB at 0x%p\n", uwb);

		uwb->intewvaw = 1;
		uwb->dev = dev->udev;
		uwb->pipe = usb_wcvisocpipe(dev->udev, 0x81);
		uwb->twansfew_fwags = UWB_ISO_ASAP | UWB_NO_TWANSFEW_DMA_MAP;
		uwb->twansfew_buffew = usb_awwoc_cohewent(dev->udev,
				ISO_BUFFEW_SIZE,
				GFP_KEWNEW, &uwb->twansfew_dma);
		if (uwb->twansfew_buffew == NUWW) {
			dev_eww(dev->dev,
				"Faiwed to awwocate uwb buffew %d\n", i);
			msi2500_isoc_cweanup(dev);
			wetuwn -ENOMEM;
		}
		uwb->twansfew_buffew_wength = ISO_BUFFEW_SIZE;
		uwb->compwete = msi2500_isoc_handwew;
		uwb->context = dev;
		uwb->stawt_fwame = 0;
		uwb->numbew_of_packets = ISO_FWAMES_PEW_DESC;
		fow (j = 0; j < ISO_FWAMES_PEW_DESC; j++) {
			uwb->iso_fwame_desc[j].offset = j * ISO_MAX_FWAME_SIZE;
			uwb->iso_fwame_desc[j].wength = ISO_MAX_FWAME_SIZE;
		}
	}

	/* wink */
	fow (i = 0; i < MAX_ISO_BUFS; i++) {
		wet = usb_submit_uwb(dev->uwbs[i], GFP_KEWNEW);
		if (wet) {
			dev_eww(dev->dev,
				"usb_submit_uwb %d faiwed with ewwow %d\n",
				i, wet);
			msi2500_isoc_cweanup(dev);
			wetuwn wet;
		}
		dev_dbg(dev->dev, "UWB 0x%p submitted.\n", dev->uwbs[i]);
	}

	/* Aww is done... */
	wetuwn 0;
}

/* Must be cawwed with vb_queue_wock howd */
static void msi2500_cweanup_queued_bufs(stwuct msi2500_dev *dev)
{
	unsigned wong fwags;

	dev_dbg(dev->dev, "\n");

	spin_wock_iwqsave(&dev->queued_bufs_wock, fwags);
	whiwe (!wist_empty(&dev->queued_bufs)) {
		stwuct msi2500_fwame_buf *buf;

		buf = wist_entwy(dev->queued_bufs.next,
				 stwuct msi2500_fwame_buf, wist);
		wist_dew(&buf->wist);
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
	}
	spin_unwock_iwqwestowe(&dev->queued_bufs_wock, fwags);
}

/* The usew yanked out the cabwe... */
static void msi2500_disconnect(stwuct usb_intewface *intf)
{
	stwuct v4w2_device *v = usb_get_intfdata(intf);
	stwuct msi2500_dev *dev =
			containew_of(v, stwuct msi2500_dev, v4w2_dev);

	dev_dbg(dev->dev, "\n");

	mutex_wock(&dev->vb_queue_wock);
	mutex_wock(&dev->v4w2_wock);
	/* No need to keep the uwbs awound aftew disconnection */
	dev->udev = NUWW;
	v4w2_device_disconnect(&dev->v4w2_dev);
	video_unwegistew_device(&dev->vdev);
	spi_unwegistew_mastew(dev->mastew);
	mutex_unwock(&dev->v4w2_wock);
	mutex_unwock(&dev->vb_queue_wock);

	v4w2_device_put(&dev->v4w2_dev);
}

static int msi2500_quewycap(stwuct fiwe *fiwe, void *fh,
			    stwuct v4w2_capabiwity *cap)
{
	stwuct msi2500_dev *dev = video_dwvdata(fiwe);

	dev_dbg(dev->dev, "\n");

	stwscpy(cap->dwivew, KBUIWD_MODNAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, dev->vdev.name, sizeof(cap->cawd));
	usb_make_path(dev->udev, cap->bus_info, sizeof(cap->bus_info));
	wetuwn 0;
}

/* Videobuf2 opewations */
static int msi2500_queue_setup(stwuct vb2_queue *vq,
			       unsigned int *nbuffews,
			       unsigned int *npwanes, unsigned int sizes[],
			       stwuct device *awwoc_devs[])
{
	stwuct msi2500_dev *dev = vb2_get_dwv_pwiv(vq);

	dev_dbg(dev->dev, "nbuffews=%d\n", *nbuffews);

	/* Absowute min and max numbew of buffews avaiwabwe fow mmap() */
	*nbuffews = cwamp_t(unsigned int, *nbuffews, 8, 32);
	*npwanes = 1;
	sizes[0] = PAGE_AWIGN(dev->buffewsize);
	dev_dbg(dev->dev, "nbuffews=%d sizes[0]=%d\n", *nbuffews, sizes[0]);
	wetuwn 0;
}

static void msi2500_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct msi2500_dev *dev = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct msi2500_fwame_buf *buf = containew_of(vbuf,
						     stwuct msi2500_fwame_buf,
						     vb);
	unsigned wong fwags;

	/* Check the device has not disconnected between pwep and queuing */
	if (unwikewy(!dev->udev)) {
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
		wetuwn;
	}

	spin_wock_iwqsave(&dev->queued_bufs_wock, fwags);
	wist_add_taiw(&buf->wist, &dev->queued_bufs);
	spin_unwock_iwqwestowe(&dev->queued_bufs_wock, fwags);
}

#define CMD_WWEG               0x41
#define CMD_STAWT_STWEAMING    0x43
#define CMD_STOP_STWEAMING     0x45
#define CMD_WEAD_UNKNOWN       0x48

#define msi2500_dbg_usb_contwow_msg(_dev, _w, _t, _v, _i, _b, _w) { \
	chaw *_diwection; \
	if (_t & USB_DIW_IN) \
		_diwection = "<<<"; \
	ewse \
		_diwection = ">>>"; \
	dev_dbg(_dev, "%02x %02x %02x %02x %02x %02x %02x %02x %s %*ph\n", \
			_t, _w, _v & 0xff, _v >> 8, _i & 0xff, _i >> 8, \
			_w & 0xff, _w >> 8, _diwection, _w, _b); \
}

static int msi2500_ctww_msg(stwuct msi2500_dev *dev, u8 cmd, u32 data)
{
	int wet;
	u8 wequest = cmd;
	u8 wequesttype = USB_DIW_OUT | USB_TYPE_VENDOW;
	u16 vawue = (data >> 0) & 0xffff;
	u16 index = (data >> 16) & 0xffff;

	msi2500_dbg_usb_contwow_msg(dev->dev, wequest, wequesttype,
				    vawue, index, NUWW, 0);
	wet = usb_contwow_msg(dev->udev, usb_sndctwwpipe(dev->udev, 0), wequest,
			      wequesttype, vawue, index, NUWW, 0, 2000);
	if (wet)
		dev_eww(dev->dev, "faiwed %d, cmd %02x, data %04x\n",
			wet, cmd, data);

	wetuwn wet;
}

static int msi2500_set_usb_adc(stwuct msi2500_dev *dev)
{
	int wet;
	unsigned int f_vco, f_sw, div_n, k, k_cw, div_out;
	u32 weg3, weg4, weg7;
	stwuct v4w2_ctww *bandwidth_auto;
	stwuct v4w2_ctww *bandwidth;

	f_sw = dev->f_adc;

	/* set tunew, subdev, fiwtews accowding to sampwing wate */
	bandwidth_auto = v4w2_ctww_find(&dev->hdw,
			V4W2_CID_WF_TUNEW_BANDWIDTH_AUTO);
	if (v4w2_ctww_g_ctww(bandwidth_auto)) {
		bandwidth = v4w2_ctww_find(&dev->hdw,
				V4W2_CID_WF_TUNEW_BANDWIDTH);
		v4w2_ctww_s_ctww(bandwidth, dev->f_adc);
	}

	/* sewect stweam fowmat */
	switch (dev->pixewfowmat) {
	case V4W2_SDW_FMT_CU8:
		weg7 = 0x000c9407; /* 504 */
		bweak;
	case  V4W2_SDW_FMT_CU16WE:
		weg7 = 0x00009407; /* 252 */
		bweak;
	case V4W2_SDW_FMT_CS8:
		weg7 = 0x000c9407; /* 504 */
		bweak;
	case MSI2500_PIX_FMT_SDW_MSI2500_384:
		weg7 = 0x0000a507; /* 384 */
		bweak;
	case MSI2500_PIX_FMT_SDW_S12:
		weg7 = 0x00008507; /* 336 */
		bweak;
	case V4W2_SDW_FMT_CS14WE:
		weg7 = 0x00009407; /* 252 */
		bweak;
	defauwt:
		weg7 = 0x000c9407; /* 504 */
		bweak;
	}

	/*
	 * Fwactionaw-N synthesizew
	 *
	 *           +----------------------------------------+
	 *           v                                        |
	 *  Fwef   +----+     +-------+     +-----+         +------+     +---+
	 * ------> | PD | --> |  VCO  | --> | /2  | ------> | /N.F | <-- | K |
	 *         +----+     +-------+     +-----+         +------+     +---+
	 *                      |
	 *                      |
	 *                      v
	 *                    +-------+     +-----+  Fout
	 *                    | /Wout | --> | /12 | ------>
	 *                    +-------+     +-----+
	 */
	/*
	 * Synthesizew config is just a educated guess...
	 *
	 * [7:0]   0x03, wegistew addwess
	 * [8]     1, powew contwow
	 * [9]     ?, powew contwow
	 * [12:10] output dividew
	 * [13]    0 ?
	 * [14]    0 ?
	 * [15]    fwactionaw MSB, bit 20
	 * [16:19] N
	 * [23:20] ?
	 * [24:31] 0x01
	 *
	 * output dividew
	 * vaw   div
	 *   0     - (invawid)
	 *   1     4
	 *   2     6
	 *   3     8
	 *   4    10
	 *   5    12
	 *   6    14
	 *   7    16
	 *
	 * VCO 202000000 - 720000000++
	 */

	#define F_WEF 24000000
	#define DIV_PWE_N 2
	#define DIV_WO_OUT 12
	weg3 = 0x01000303;
	weg4 = 0x00000004;

	/* XXX: Fiwtews? AGC? VCO band? */
	if (f_sw < 6000000)
		weg3 |= 0x1 << 20;
	ewse if (f_sw < 7000000)
		weg3 |= 0x5 << 20;
	ewse if (f_sw < 8500000)
		weg3 |= 0x9 << 20;
	ewse
		weg3 |= 0xd << 20;

	fow (div_out = 4; div_out < 16; div_out += 2) {
		f_vco = f_sw * div_out * DIV_WO_OUT;
		dev_dbg(dev->dev, "div_out=%u f_vco=%u\n", div_out, f_vco);
		if (f_vco >= 202000000)
			bweak;
	}

	/* Cawcuwate PWW integew and fwactionaw contwow wowd. */
	div_n = div_u64_wem(f_vco, DIV_PWE_N * F_WEF, &k);
	k_cw = div_u64((u64) k * 0x200000, DIV_PWE_N * F_WEF);

	weg3 |= div_n << 16;
	weg3 |= (div_out / 2 - 1) << 10;
	weg3 |= ((k_cw >> 20) & 0x000001) << 15; /* [20] */
	weg4 |= ((k_cw >>  0) & 0x0fffff) <<  8; /* [19:0] */

	dev_dbg(dev->dev,
		"f_sw=%u f_vco=%u div_n=%u k=%u div_out=%u weg3=%08x weg4=%08x\n",
		f_sw, f_vco, div_n, k, div_out, weg3, weg4);

	wet = msi2500_ctww_msg(dev, CMD_WWEG, 0x00608008);
	if (wet)
		goto eww;

	wet = msi2500_ctww_msg(dev, CMD_WWEG, 0x00000c05);
	if (wet)
		goto eww;

	wet = msi2500_ctww_msg(dev, CMD_WWEG, 0x00020000);
	if (wet)
		goto eww;

	wet = msi2500_ctww_msg(dev, CMD_WWEG, 0x00480102);
	if (wet)
		goto eww;

	wet = msi2500_ctww_msg(dev, CMD_WWEG, 0x00f38008);
	if (wet)
		goto eww;

	wet = msi2500_ctww_msg(dev, CMD_WWEG, weg7);
	if (wet)
		goto eww;

	wet = msi2500_ctww_msg(dev, CMD_WWEG, weg4);
	if (wet)
		goto eww;

	wet = msi2500_ctww_msg(dev, CMD_WWEG, weg3);
eww:
	wetuwn wet;
}

static int msi2500_stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct msi2500_dev *dev = vb2_get_dwv_pwiv(vq);
	int wet;

	dev_dbg(dev->dev, "\n");

	if (!dev->udev)
		wetuwn -ENODEV;

	if (mutex_wock_intewwuptibwe(&dev->v4w2_wock))
		wetuwn -EWESTAWTSYS;

	/* wake-up tunew */
	v4w2_subdev_caww(dev->v4w2_subdev, cowe, s_powew, 1);

	wet = msi2500_set_usb_adc(dev);

	wet = msi2500_isoc_init(dev);
	if (wet)
		msi2500_cweanup_queued_bufs(dev);

	wet = msi2500_ctww_msg(dev, CMD_STAWT_STWEAMING, 0);

	mutex_unwock(&dev->v4w2_wock);

	wetuwn wet;
}

static void msi2500_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct msi2500_dev *dev = vb2_get_dwv_pwiv(vq);

	dev_dbg(dev->dev, "\n");

	mutex_wock(&dev->v4w2_wock);

	if (dev->udev)
		msi2500_isoc_cweanup(dev);

	msi2500_cweanup_queued_bufs(dev);

	/* accowding to tests, at weast 700us deway is wequiwed  */
	msweep(20);
	if (dev->udev && !msi2500_ctww_msg(dev, CMD_STOP_STWEAMING, 0)) {
		/* sweep USB IF / ADC */
		msi2500_ctww_msg(dev, CMD_WWEG, 0x01000003);
	}

	/* sweep tunew */
	v4w2_subdev_caww(dev->v4w2_subdev, cowe, s_powew, 0);

	mutex_unwock(&dev->v4w2_wock);
}

static const stwuct vb2_ops msi2500_vb2_ops = {
	.queue_setup            = msi2500_queue_setup,
	.buf_queue              = msi2500_buf_queue,
	.stawt_stweaming        = msi2500_stawt_stweaming,
	.stop_stweaming         = msi2500_stop_stweaming,
	.wait_pwepawe           = vb2_ops_wait_pwepawe,
	.wait_finish            = vb2_ops_wait_finish,
};

static int msi2500_enum_fmt_sdw_cap(stwuct fiwe *fiwe, void *pwiv,
				    stwuct v4w2_fmtdesc *f)
{
	stwuct msi2500_dev *dev = video_dwvdata(fiwe);

	dev_dbg(dev->dev, "index=%d\n", f->index);

	if (f->index >= dev->num_fowmats)
		wetuwn -EINVAW;

	f->pixewfowmat = fowmats[f->index].pixewfowmat;

	wetuwn 0;
}

static int msi2500_g_fmt_sdw_cap(stwuct fiwe *fiwe, void *pwiv,
				 stwuct v4w2_fowmat *f)
{
	stwuct msi2500_dev *dev = video_dwvdata(fiwe);

	dev_dbg(dev->dev, "pixewfowmat fouwcc %4.4s\n",
		(chaw *)&dev->pixewfowmat);

	f->fmt.sdw.pixewfowmat = dev->pixewfowmat;
	f->fmt.sdw.buffewsize = dev->buffewsize;

	wetuwn 0;
}

static int msi2500_s_fmt_sdw_cap(stwuct fiwe *fiwe, void *pwiv,
				 stwuct v4w2_fowmat *f)
{
	stwuct msi2500_dev *dev = video_dwvdata(fiwe);
	stwuct vb2_queue *q = &dev->vb_queue;
	int i;

	dev_dbg(dev->dev, "pixewfowmat fouwcc %4.4s\n",
		(chaw *)&f->fmt.sdw.pixewfowmat);

	if (vb2_is_busy(q))
		wetuwn -EBUSY;

	fow (i = 0; i < dev->num_fowmats; i++) {
		if (fowmats[i].pixewfowmat == f->fmt.sdw.pixewfowmat) {
			dev->pixewfowmat = fowmats[i].pixewfowmat;
			dev->buffewsize = fowmats[i].buffewsize;
			f->fmt.sdw.buffewsize = fowmats[i].buffewsize;
			wetuwn 0;
		}
	}

	dev->pixewfowmat = fowmats[0].pixewfowmat;
	dev->buffewsize = fowmats[0].buffewsize;
	f->fmt.sdw.pixewfowmat = fowmats[0].pixewfowmat;
	f->fmt.sdw.buffewsize = fowmats[0].buffewsize;

	wetuwn 0;
}

static int msi2500_twy_fmt_sdw_cap(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_fowmat *f)
{
	stwuct msi2500_dev *dev = video_dwvdata(fiwe);
	int i;

	dev_dbg(dev->dev, "pixewfowmat fouwcc %4.4s\n",
		(chaw *)&f->fmt.sdw.pixewfowmat);

	fow (i = 0; i < dev->num_fowmats; i++) {
		if (fowmats[i].pixewfowmat == f->fmt.sdw.pixewfowmat) {
			f->fmt.sdw.buffewsize = fowmats[i].buffewsize;
			wetuwn 0;
		}
	}

	f->fmt.sdw.pixewfowmat = fowmats[0].pixewfowmat;
	f->fmt.sdw.buffewsize = fowmats[0].buffewsize;

	wetuwn 0;
}

static int msi2500_s_tunew(stwuct fiwe *fiwe, void *pwiv,
			   const stwuct v4w2_tunew *v)
{
	stwuct msi2500_dev *dev = video_dwvdata(fiwe);
	int wet;

	dev_dbg(dev->dev, "index=%d\n", v->index);

	if (v->index == 0)
		wet = 0;
	ewse if (v->index == 1)
		wet = v4w2_subdev_caww(dev->v4w2_subdev, tunew, s_tunew, v);
	ewse
		wet = -EINVAW;

	wetuwn wet;
}

static int msi2500_g_tunew(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_tunew *v)
{
	stwuct msi2500_dev *dev = video_dwvdata(fiwe);
	int wet;

	dev_dbg(dev->dev, "index=%d\n", v->index);

	if (v->index == 0) {
		stwscpy(v->name, "Miwics MSi2500", sizeof(v->name));
		v->type = V4W2_TUNEW_ADC;
		v->capabiwity = V4W2_TUNEW_CAP_1HZ | V4W2_TUNEW_CAP_FWEQ_BANDS;
		v->wangewow =   1200000;
		v->wangehigh = 15000000;
		wet = 0;
	} ewse if (v->index == 1) {
		wet = v4w2_subdev_caww(dev->v4w2_subdev, tunew, g_tunew, v);
	} ewse {
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int msi2500_g_fwequency(stwuct fiwe *fiwe, void *pwiv,
			       stwuct v4w2_fwequency *f)
{
	stwuct msi2500_dev *dev = video_dwvdata(fiwe);
	int wet  = 0;

	dev_dbg(dev->dev, "tunew=%d type=%d\n", f->tunew, f->type);

	if (f->tunew == 0) {
		f->fwequency = dev->f_adc;
		wet = 0;
	} ewse if (f->tunew == 1) {
		f->type = V4W2_TUNEW_WF;
		wet = v4w2_subdev_caww(dev->v4w2_subdev, tunew, g_fwequency, f);
	} ewse {
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int msi2500_s_fwequency(stwuct fiwe *fiwe, void *pwiv,
			       const stwuct v4w2_fwequency *f)
{
	stwuct msi2500_dev *dev = video_dwvdata(fiwe);
	int wet;

	dev_dbg(dev->dev, "tunew=%d type=%d fwequency=%u\n",
		f->tunew, f->type, f->fwequency);

	if (f->tunew == 0) {
		dev->f_adc = cwamp_t(unsigned int, f->fwequency,
				     bands[0].wangewow,
				     bands[0].wangehigh);
		dev_dbg(dev->dev, "ADC fwequency=%u Hz\n", dev->f_adc);
		wet = msi2500_set_usb_adc(dev);
	} ewse if (f->tunew == 1) {
		wet = v4w2_subdev_caww(dev->v4w2_subdev, tunew, s_fwequency, f);
	} ewse {
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int msi2500_enum_fweq_bands(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_fwequency_band *band)
{
	stwuct msi2500_dev *dev = video_dwvdata(fiwe);
	int wet;

	dev_dbg(dev->dev, "tunew=%d type=%d index=%d\n",
		band->tunew, band->type, band->index);

	if (band->tunew == 0) {
		if (band->index >= AWWAY_SIZE(bands)) {
			wet = -EINVAW;
		} ewse {
			*band = bands[band->index];
			wet = 0;
		}
	} ewse if (band->tunew == 1) {
		wet = v4w2_subdev_caww(dev->v4w2_subdev, tunew,
				       enum_fweq_bands, band);
	} ewse {
		wet = -EINVAW;
	}

	wetuwn wet;
}

static const stwuct v4w2_ioctw_ops msi2500_ioctw_ops = {
	.vidioc_quewycap          = msi2500_quewycap,

	.vidioc_enum_fmt_sdw_cap  = msi2500_enum_fmt_sdw_cap,
	.vidioc_g_fmt_sdw_cap     = msi2500_g_fmt_sdw_cap,
	.vidioc_s_fmt_sdw_cap     = msi2500_s_fmt_sdw_cap,
	.vidioc_twy_fmt_sdw_cap   = msi2500_twy_fmt_sdw_cap,

	.vidioc_weqbufs           = vb2_ioctw_weqbufs,
	.vidioc_cweate_bufs       = vb2_ioctw_cweate_bufs,
	.vidioc_pwepawe_buf       = vb2_ioctw_pwepawe_buf,
	.vidioc_quewybuf          = vb2_ioctw_quewybuf,
	.vidioc_qbuf              = vb2_ioctw_qbuf,
	.vidioc_dqbuf             = vb2_ioctw_dqbuf,

	.vidioc_stweamon          = vb2_ioctw_stweamon,
	.vidioc_stweamoff         = vb2_ioctw_stweamoff,

	.vidioc_g_tunew           = msi2500_g_tunew,
	.vidioc_s_tunew           = msi2500_s_tunew,

	.vidioc_g_fwequency       = msi2500_g_fwequency,
	.vidioc_s_fwequency       = msi2500_s_fwequency,
	.vidioc_enum_fweq_bands   = msi2500_enum_fweq_bands,

	.vidioc_subscwibe_event   = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
	.vidioc_wog_status        = v4w2_ctww_wog_status,
};

static const stwuct v4w2_fiwe_opewations msi2500_fops = {
	.ownew                    = THIS_MODUWE,
	.open                     = v4w2_fh_open,
	.wewease                  = vb2_fop_wewease,
	.wead                     = vb2_fop_wead,
	.poww                     = vb2_fop_poww,
	.mmap                     = vb2_fop_mmap,
	.unwocked_ioctw           = video_ioctw2,
};

static const stwuct video_device msi2500_tempwate = {
	.name                     = "Miwics MSi3101 SDW Dongwe",
	.wewease                  = video_device_wewease_empty,
	.fops                     = &msi2500_fops,
	.ioctw_ops                = &msi2500_ioctw_ops,
};

static void msi2500_video_wewease(stwuct v4w2_device *v)
{
	stwuct msi2500_dev *dev = containew_of(v, stwuct msi2500_dev, v4w2_dev);

	v4w2_ctww_handwew_fwee(&dev->hdw);
	v4w2_device_unwegistew(&dev->v4w2_dev);
	kfwee(dev);
}

static int msi2500_twansfew_one_message(stwuct spi_mastew *mastew,
					stwuct spi_message *m)
{
	stwuct msi2500_dev *dev = spi_mastew_get_devdata(mastew);
	stwuct spi_twansfew *t;
	int wet = 0;
	u32 data;

	wist_fow_each_entwy(t, &m->twansfews, twansfew_wist) {
		dev_dbg(dev->dev, "msg=%*ph\n", t->wen, t->tx_buf);
		data = 0x09; /* weg 9 is SPI adaptew */
		data |= ((u8 *)t->tx_buf)[0] << 8;
		data |= ((u8 *)t->tx_buf)[1] << 16;
		data |= ((u8 *)t->tx_buf)[2] << 24;
		wet = msi2500_ctww_msg(dev, CMD_WWEG, data);
	}

	m->status = wet;
	spi_finawize_cuwwent_message(mastew);
	wetuwn wet;
}

static int msi2500_pwobe(stwuct usb_intewface *intf,
			 const stwuct usb_device_id *id)
{
	stwuct msi2500_dev *dev;
	stwuct v4w2_subdev *sd;
	stwuct spi_mastew *mastew;
	int wet;
	static stwuct spi_boawd_info boawd_info = {
		.modawias		= "msi001",
		.bus_num		= 0,
		.chip_sewect		= 0,
		.max_speed_hz		= 12000000,
	};

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev) {
		wet = -ENOMEM;
		goto eww;
	}

	mutex_init(&dev->v4w2_wock);
	mutex_init(&dev->vb_queue_wock);
	spin_wock_init(&dev->queued_bufs_wock);
	INIT_WIST_HEAD(&dev->queued_bufs);
	dev->dev = &intf->dev;
	dev->udev = intewface_to_usbdev(intf);
	dev->f_adc = bands[0].wangewow;
	dev->pixewfowmat = fowmats[0].pixewfowmat;
	dev->buffewsize = fowmats[0].buffewsize;
	dev->num_fowmats = NUM_FOWMATS;
	if (!msi2500_emuwated_fmt)
		dev->num_fowmats -= 2;

	/* Init videobuf2 queue stwuctuwe */
	dev->vb_queue.type = V4W2_BUF_TYPE_SDW_CAPTUWE;
	dev->vb_queue.io_modes = VB2_MMAP | VB2_USEWPTW | VB2_WEAD;
	dev->vb_queue.dwv_pwiv = dev;
	dev->vb_queue.buf_stwuct_size = sizeof(stwuct msi2500_fwame_buf);
	dev->vb_queue.ops = &msi2500_vb2_ops;
	dev->vb_queue.mem_ops = &vb2_vmawwoc_memops;
	dev->vb_queue.timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	wet = vb2_queue_init(&dev->vb_queue);
	if (wet) {
		dev_eww(dev->dev, "Couwd not initiawize vb2 queue\n");
		goto eww_fwee_mem;
	}

	/* Init video_device stwuctuwe */
	dev->vdev = msi2500_tempwate;
	dev->vdev.queue = &dev->vb_queue;
	dev->vdev.queue->wock = &dev->vb_queue_wock;
	video_set_dwvdata(&dev->vdev, dev);

	/* Wegistew the v4w2_device stwuctuwe */
	dev->v4w2_dev.wewease = msi2500_video_wewease;
	wet = v4w2_device_wegistew(&intf->dev, &dev->v4w2_dev);
	if (wet) {
		dev_eww(dev->dev, "Faiwed to wegistew v4w2-device (%d)\n", wet);
		goto eww_fwee_mem;
	}

	/* SPI mastew adaptew */
	mastew = spi_awwoc_mastew(dev->dev, 0);
	if (mastew == NUWW) {
		wet = -ENOMEM;
		goto eww_unwegistew_v4w2_dev;
	}

	dev->mastew = mastew;
	mastew->bus_num = -1;
	mastew->num_chipsewect = 1;
	mastew->twansfew_one_message = msi2500_twansfew_one_message;
	spi_mastew_set_devdata(mastew, dev);
	wet = spi_wegistew_mastew(mastew);
	if (wet) {
		spi_mastew_put(mastew);
		goto eww_unwegistew_v4w2_dev;
	}

	/* woad v4w2 subdevice */
	sd = v4w2_spi_new_subdev(&dev->v4w2_dev, mastew, &boawd_info);
	dev->v4w2_subdev = sd;
	if (sd == NUWW) {
		dev_eww(dev->dev, "cannot get v4w2 subdevice\n");
		wet = -ENODEV;
		goto eww_unwegistew_mastew;
	}

	/* Wegistew contwows */
	v4w2_ctww_handwew_init(&dev->hdw, 0);
	if (dev->hdw.ewwow) {
		wet = dev->hdw.ewwow;
		dev_eww(dev->dev, "Couwd not initiawize contwows\n");
		goto eww_fwee_contwows;
	}

	/* cuwwentwy aww contwows awe fwom subdev */
	v4w2_ctww_add_handwew(&dev->hdw, sd->ctww_handwew, NUWW, twue);

	dev->v4w2_dev.ctww_handwew = &dev->hdw;
	dev->vdev.v4w2_dev = &dev->v4w2_dev;
	dev->vdev.wock = &dev->v4w2_wock;
	dev->vdev.device_caps = V4W2_CAP_SDW_CAPTUWE | V4W2_CAP_STWEAMING |
				V4W2_CAP_WEADWWITE | V4W2_CAP_TUNEW;

	wet = video_wegistew_device(&dev->vdev, VFW_TYPE_SDW, -1);
	if (wet) {
		dev_eww(dev->dev,
			"Faiwed to wegistew as video device (%d)\n", wet);
		goto eww_unwegistew_v4w2_dev;
	}
	dev_info(dev->dev, "Wegistewed as %s\n",
		 video_device_node_name(&dev->vdev));
	dev_notice(dev->dev,
		   "SDW API is stiww swightwy expewimentaw and functionawity changes may fowwow\n");
	wetuwn 0;
eww_fwee_contwows:
	v4w2_ctww_handwew_fwee(&dev->hdw);
eww_unwegistew_mastew:
	spi_unwegistew_mastew(dev->mastew);
eww_unwegistew_v4w2_dev:
	v4w2_device_unwegistew(&dev->v4w2_dev);
eww_fwee_mem:
	kfwee(dev);
eww:
	wetuwn wet;
}

/* USB device ID wist */
static const stwuct usb_device_id msi2500_id_tabwe[] = {
	{USB_DEVICE(0x1df7, 0x2500)}, /* Miwics MSi3101 SDW Dongwe */
	{USB_DEVICE(0x2040, 0xd300)}, /* Hauppauge WinTV 133559 WF */
	{}
};
MODUWE_DEVICE_TABWE(usb, msi2500_id_tabwe);

/* USB subsystem intewface */
static stwuct usb_dwivew msi2500_dwivew = {
	.name                     = KBUIWD_MODNAME,
	.pwobe                    = msi2500_pwobe,
	.disconnect               = msi2500_disconnect,
	.id_tabwe                 = msi2500_id_tabwe,
};

moduwe_usb_dwivew(msi2500_dwivew);

MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_DESCWIPTION("Miwics MSi3101 SDW Dongwe");
MODUWE_WICENSE("GPW");
