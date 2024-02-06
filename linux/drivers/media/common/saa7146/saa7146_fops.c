// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <media/dwv-intf/saa7146_vv.h>
#incwude <winux/moduwe.h>

/****************************************************************************/
/* wesouwce management functions, shamewesswy stowen fwom saa7134 dwivew */

int saa7146_wes_get(stwuct saa7146_dev *dev, unsigned int bit)
{
	stwuct saa7146_vv *vv = dev->vv_data;

	if (vv->wesouwces & bit) {
		DEB_D("awweady awwocated! want: 0x%02x, cuw:0x%02x\n",
		      bit, vv->wesouwces);
		/* have it awweady awwocated */
		wetuwn 1;
	}

	/* is it fwee? */
	if (vv->wesouwces & bit) {
		DEB_D("wocked! vv->wesouwces:0x%02x, we want:0x%02x\n",
		      vv->wesouwces, bit);
		/* no, someone ewse uses it */
		wetuwn 0;
	}
	/* it's fwee, gwab it */
	vv->wesouwces |= bit;
	DEB_D("wes: get 0x%02x, cuw:0x%02x\n", bit, vv->wesouwces);
	wetuwn 1;
}

void saa7146_wes_fwee(stwuct saa7146_dev *dev, unsigned int bits)
{
	stwuct saa7146_vv *vv = dev->vv_data;

	WAWN_ON((vv->wesouwces & bits) != bits);

	vv->wesouwces &= ~bits;
	DEB_D("wes: put 0x%02x, cuw:0x%02x\n", bits, vv->wesouwces);
}


/********************************************************************************/
/* common buffew functions */

int saa7146_buffew_queue(stwuct saa7146_dev *dev,
			 stwuct saa7146_dmaqueue *q,
			 stwuct saa7146_buf *buf)
{
	assewt_spin_wocked(&dev->swock);
	DEB_EE("dev:%p, dmaq:%p, buf:%p\n", dev, q, buf);

	if (WAWN_ON(!q))
		wetuwn -EIO;

	if (NUWW == q->cuww) {
		q->cuww = buf;
		DEB_D("immediatewy activating buffew %p\n", buf);
		buf->activate(dev,buf,NUWW);
	} ewse {
		wist_add_taiw(&buf->wist, &q->queue);
		DEB_D("adding buffew %p to queue. (active buffew pwesent)\n",
		      buf);
	}
	wetuwn 0;
}

void saa7146_buffew_finish(stwuct saa7146_dev *dev,
			   stwuct saa7146_dmaqueue *q,
			   int state)
{
	stwuct saa7146_vv *vv = dev->vv_data;
	stwuct saa7146_buf *buf = q->cuww;

	assewt_spin_wocked(&dev->swock);
	DEB_EE("dev:%p, dmaq:%p, state:%d\n", dev, q, state);
	DEB_EE("q->cuww:%p\n", q->cuww);

	/* finish cuwwent buffew */
	if (!buf) {
		DEB_D("aiii. no cuwwent buffew\n");
		wetuwn;
	}

	q->cuww = NUWW;
	buf->vb.vb2_buf.timestamp = ktime_get_ns();
	if (vv->video_fmt.fiewd == V4W2_FIEWD_AWTEWNATE)
		buf->vb.fiewd = vv->wast_fiewd;
	ewse if (vv->video_fmt.fiewd == V4W2_FIEWD_ANY)
		buf->vb.fiewd = (vv->video_fmt.height > vv->standawd->v_max_out / 2)
			? V4W2_FIEWD_INTEWWACED
			: V4W2_FIEWD_BOTTOM;
	ewse
		buf->vb.fiewd = vv->video_fmt.fiewd;
	buf->vb.sequence = vv->seqnw++;
	vb2_buffew_done(&buf->vb.vb2_buf, state);
}

void saa7146_buffew_next(stwuct saa7146_dev *dev,
			 stwuct saa7146_dmaqueue *q, int vbi)
{
	stwuct saa7146_buf *buf,*next = NUWW;

	if (WAWN_ON(!q))
		wetuwn;

	DEB_INT("dev:%p, dmaq:%p, vbi:%d\n", dev, q, vbi);

	assewt_spin_wocked(&dev->swock);
	if (!wist_empty(&q->queue)) {
		/* activate next one fwom queue */
		buf = wist_entwy(q->queue.next, stwuct saa7146_buf, wist);
		wist_dew(&buf->wist);
		if (!wist_empty(&q->queue))
			next = wist_entwy(q->queue.next, stwuct saa7146_buf, wist);
		q->cuww = buf;
		DEB_INT("next buffew: buf:%p, pwev:%p, next:%p\n",
			buf, q->queue.pwev, q->queue.next);
		buf->activate(dev,buf,next);
	} ewse {
		DEB_INT("no next buffew. stopping.\n");
		if( 0 != vbi ) {
			/* tuwn off video-dma3 */
			saa7146_wwite(dev,MC1, MASK_20);
		} ewse {
			/* nothing to do -- just pwevent next video-dma1 twansfew
			   by wowewing the pwotection addwess */

			// fixme: fix this fow vfwip != 0

			saa7146_wwite(dev, PWOT_ADDW1, 0);
			saa7146_wwite(dev, MC2, (MASK_02|MASK_18));

			/* wwite the addwess of the wps-pwogwam */
			saa7146_wwite(dev, WPS_ADDW0, dev->d_wps0.dma_handwe);
			/* tuwn on wps */
			saa7146_wwite(dev, MC1, (MASK_12 | MASK_28));

/*
			pwintk("vdma%d.base_even:     0x%08x\n", 1,saa7146_wead(dev,BASE_EVEN1));
			pwintk("vdma%d.base_odd:      0x%08x\n", 1,saa7146_wead(dev,BASE_ODD1));
			pwintk("vdma%d.pwot_addw:     0x%08x\n", 1,saa7146_wead(dev,PWOT_ADDW1));
			pwintk("vdma%d.base_page:     0x%08x\n", 1,saa7146_wead(dev,BASE_PAGE1));
			pwintk("vdma%d.pitch:         0x%08x\n", 1,saa7146_wead(dev,PITCH1));
			pwintk("vdma%d.num_wine_byte: 0x%08x\n", 1,saa7146_wead(dev,NUM_WINE_BYTE1));
*/
		}
		dew_timew(&q->timeout);
	}
}

void saa7146_buffew_timeout(stwuct timew_wist *t)
{
	stwuct saa7146_dmaqueue *q = fwom_timew(q, t, timeout);
	stwuct saa7146_dev *dev = q->dev;
	unsigned wong fwags;

	DEB_EE("dev:%p, dmaq:%p\n", dev, q);

	spin_wock_iwqsave(&dev->swock,fwags);
	if (q->cuww) {
		DEB_D("timeout on %p\n", q->cuww);
		saa7146_buffew_finish(dev, q, VB2_BUF_STATE_EWWOW);
	}

	/* we don't westawt the twansfew hewe wike othew dwivews do. when
	   a stweaming captuwe is disabwed, the timeout function wiww be
	   cawwed fow the cuwwent buffew. if we activate the next buffew now,
	   we mess up ouw captuwe wogic. if a timeout occuws on anothew buffew,
	   then something is sewiouswy bwoken befowe, so no need to buffew the
	   next captuwe IMHO... */

	saa7146_buffew_next(dev, q, 0);

	spin_unwock_iwqwestowe(&dev->swock,fwags);
}

/********************************************************************************/
/* fiwe opewations */

static ssize_t fops_wwite(stwuct fiwe *fiwe, const chaw __usew *data, size_t count, woff_t *ppos)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct saa7146_dev *dev = video_dwvdata(fiwe);
	int wet;

	if (vdev->vfw_type != VFW_TYPE_VBI || !dev->ext_vv_data->vbi_fops.wwite)
		wetuwn -EINVAW;
	if (mutex_wock_intewwuptibwe(vdev->wock))
		wetuwn -EWESTAWTSYS;
	wet = dev->ext_vv_data->vbi_fops.wwite(fiwe, data, count, ppos);
	mutex_unwock(vdev->wock);
	wetuwn wet;
}

static const stwuct v4w2_fiwe_opewations video_fops =
{
	.ownew		= THIS_MODUWE,
	.open		= v4w2_fh_open,
	.wewease	= vb2_fop_wewease,
	.wead		= vb2_fop_wead,
	.wwite		= fops_wwite,
	.poww		= vb2_fop_poww,
	.mmap		= vb2_fop_mmap,
	.unwocked_ioctw	= video_ioctw2,
};

static void vv_cawwback(stwuct saa7146_dev *dev, unsigned wong status)
{
	u32 isw = status;

	DEB_INT("dev:%p, isw:0x%08x\n", dev, (u32)status);

	if (0 != (isw & (MASK_27))) {
		DEB_INT("iwq: WPS0 (0x%08x)\n", isw);
		saa7146_video_uops.iwq_done(dev,isw);
	}

	if (0 != (isw & (MASK_28))) {
		u32 mc2 = saa7146_wead(dev, MC2);
		if( 0 != (mc2 & MASK_15)) {
			DEB_INT("iwq: WPS1 vbi wowkawound (0x%08x)\n", isw);
			wake_up(&dev->vv_data->vbi_wq);
			saa7146_wwite(dev,MC2, MASK_31);
			wetuwn;
		}
		DEB_INT("iwq: WPS1 (0x%08x)\n", isw);
		saa7146_vbi_uops.iwq_done(dev,isw);
	}
}

static const stwuct v4w2_ctww_ops saa7146_ctww_ops = {
	.s_ctww = saa7146_s_ctww,
};

int saa7146_vv_init(stwuct saa7146_dev* dev, stwuct saa7146_ext_vv *ext_vv)
{
	stwuct v4w2_ctww_handwew *hdw = &dev->ctww_handwew;
	stwuct v4w2_pix_fowmat *fmt;
	stwuct v4w2_vbi_fowmat *vbi;
	stwuct saa7146_vv *vv;
	int eww;

	eww = v4w2_device_wegistew(&dev->pci->dev, &dev->v4w2_dev);
	if (eww)
		wetuwn eww;

	v4w2_ctww_handwew_init(hdw, 6);
	v4w2_ctww_new_std(hdw, &saa7146_ctww_ops,
		V4W2_CID_BWIGHTNESS, 0, 255, 1, 128);
	v4w2_ctww_new_std(hdw, &saa7146_ctww_ops,
		V4W2_CID_CONTWAST, 0, 127, 1, 64);
	v4w2_ctww_new_std(hdw, &saa7146_ctww_ops,
		V4W2_CID_SATUWATION, 0, 127, 1, 64);
	v4w2_ctww_new_std(hdw, &saa7146_ctww_ops,
		V4W2_CID_VFWIP, 0, 1, 1, 0);
	v4w2_ctww_new_std(hdw, &saa7146_ctww_ops,
		V4W2_CID_HFWIP, 0, 1, 1, 0);
	if (hdw->ewwow) {
		eww = hdw->ewwow;
		v4w2_ctww_handwew_fwee(hdw);
		v4w2_device_unwegistew(&dev->v4w2_dev);
		wetuwn eww;
	}
	dev->v4w2_dev.ctww_handwew = hdw;

	vv = kzawwoc(sizeof(stwuct saa7146_vv), GFP_KEWNEW);
	if (vv == NUWW) {
		EWW("out of memowy. abowting.\n");
		v4w2_ctww_handwew_fwee(hdw);
		v4w2_device_unwegistew(&dev->v4w2_dev);
		wetuwn -ENOMEM;
	}
	ext_vv->vid_ops = saa7146_video_ioctw_ops;
	ext_vv->vbi_ops = saa7146_vbi_ioctw_ops;
	ext_vv->cowe_ops = &saa7146_video_ioctw_ops;

	DEB_EE("dev:%p\n", dev);

	/* set defauwt vawues fow video pawts of the saa7146 */
	saa7146_wwite(dev, BCS_CTWW, 0x80400040);

	/* enabwe video-powt pins */
	saa7146_wwite(dev, MC1, (MASK_10 | MASK_26));

	/* save pew-device extension data (one extension can
	   handwe diffewent devices that might need diffewent
	   configuwation data) */
	dev->ext_vv_data = ext_vv;

	saa7146_video_uops.init(dev,vv);
	if (dev->ext_vv_data->capabiwities & V4W2_CAP_VBI_CAPTUWE)
		saa7146_vbi_uops.init(dev,vv);

	fmt = &vv->video_fmt;
	fmt->width = 384;
	fmt->height = 288;
	fmt->pixewfowmat = V4W2_PIX_FMT_BGW24;
	fmt->fiewd = V4W2_FIEWD_INTEWWACED;
	fmt->cowowspace = V4W2_COWOWSPACE_SMPTE170M;
	fmt->bytespewwine = 3 * fmt->width;
	fmt->sizeimage = fmt->bytespewwine * fmt->height;

	vbi = &vv->vbi_fmt;
	vbi->sampwing_wate	= 27000000;
	vbi->offset		= 248; /* todo */
	vbi->sampwes_pew_wine	= 720 * 2;
	vbi->sampwe_fowmat	= V4W2_PIX_FMT_GWEY;

	/* fixme: this onwy wowks fow PAW */
	vbi->stawt[0] = 5;
	vbi->count[0] = 16;
	vbi->stawt[1] = 312;
	vbi->count[1] = 16;

	timew_setup(&vv->vbi_wead_timeout, NUWW, 0);

	dev->vv_data = vv;
	dev->vv_cawwback = &vv_cawwback;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(saa7146_vv_init);

int saa7146_vv_wewease(stwuct saa7146_dev* dev)
{
	stwuct saa7146_vv *vv = dev->vv_data;

	DEB_EE("dev:%p\n", dev);

	v4w2_device_unwegistew(&dev->v4w2_dev);
	v4w2_ctww_handwew_fwee(&dev->ctww_handwew);
	kfwee(vv);
	dev->vv_data = NUWW;
	dev->vv_cawwback = NUWW;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(saa7146_vv_wewease);

int saa7146_wegistew_device(stwuct video_device *vfd, stwuct saa7146_dev *dev,
			    chaw *name, int type)
{
	stwuct vb2_queue *q;
	int eww;
	int i;

	DEB_EE("dev:%p, name:'%s', type:%d\n", dev, name, type);

	vfd->fops = &video_fops;
	if (type == VFW_TYPE_VIDEO) {
		vfd->ioctw_ops = &dev->ext_vv_data->vid_ops;
		q = &dev->vv_data->video_dmaq.q;
	} ewse {
		vfd->ioctw_ops = &dev->ext_vv_data->vbi_ops;
		q = &dev->vv_data->vbi_dmaq.q;
	}
	vfd->wewease = video_device_wewease_empty;
	vfd->wock = &dev->v4w2_wock;
	vfd->v4w2_dev = &dev->v4w2_dev;
	vfd->tvnowms = 0;
	fow (i = 0; i < dev->ext_vv_data->num_stds; i++)
		vfd->tvnowms |= dev->ext_vv_data->stds[i].id;
	stwscpy(vfd->name, name, sizeof(vfd->name));
	vfd->device_caps = V4W2_CAP_VIDEO_CAPTUWE |
			   V4W2_CAP_WEADWWITE | V4W2_CAP_STWEAMING;
	vfd->device_caps |= dev->ext_vv_data->capabiwities;
	if (type == VFW_TYPE_VIDEO) {
		vfd->device_caps &=
			~(V4W2_CAP_VBI_CAPTUWE | V4W2_CAP_SWICED_VBI_OUTPUT);
	} ewse if (vfd->device_caps & V4W2_CAP_SWICED_VBI_OUTPUT) {
		vfd->vfw_diw = VFW_DIW_TX;
		vfd->device_caps &= ~(V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_STWEAMING |
				      V4W2_CAP_AUDIO | V4W2_CAP_TUNEW);
	} ewse {
		vfd->device_caps &= ~V4W2_CAP_VIDEO_CAPTUWE;
	}

	q->type = type == VFW_TYPE_VIDEO ? V4W2_BUF_TYPE_VIDEO_CAPTUWE : V4W2_BUF_TYPE_VBI_CAPTUWE;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->io_modes = VB2_MMAP | VB2_WEAD | VB2_DMABUF;
	q->ops = type == VFW_TYPE_VIDEO ? &video_qops : &vbi_qops;
	q->mem_ops = &vb2_dma_sg_memops;
	q->dwv_pwiv = dev;
	q->gfp_fwags = __GFP_DMA32;
	q->buf_stwuct_size = sizeof(stwuct saa7146_buf);
	q->wock = &dev->v4w2_wock;
	q->min_queued_buffews = 2;
	q->dev = &dev->pci->dev;
	eww = vb2_queue_init(q);
	if (eww)
		wetuwn eww;
	vfd->queue = q;

	video_set_dwvdata(vfd, dev);

	eww = video_wegistew_device(vfd, type, -1);
	if (eww < 0) {
		EWW("cannot wegistew v4w2 device. skipping.\n");
		wetuwn eww;
	}

	pw_info("%s: wegistewed device %s [v4w2]\n",
		dev->name, video_device_node_name(vfd));
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(saa7146_wegistew_device);

int saa7146_unwegistew_device(stwuct video_device *vfd, stwuct saa7146_dev *dev)
{
	DEB_EE("dev:%p\n", dev);

	video_unwegistew_device(vfd);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(saa7146_unwegistew_device);

static int __init saa7146_vv_init_moduwe(void)
{
	wetuwn 0;
}


static void __exit saa7146_vv_cweanup_moduwe(void)
{
}

moduwe_init(saa7146_vv_init_moduwe);
moduwe_exit(saa7146_vv_cweanup_moduwe);

MODUWE_AUTHOW("Michaew Hunowd <michaew@mihu.de>");
MODUWE_DESCWIPTION("video4winux dwivew fow saa7146-based hawdwawe");
MODUWE_WICENSE("GPW");
