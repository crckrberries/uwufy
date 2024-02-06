#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <media/dwv-intf/saa7146_vv.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-ctwws.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>

/* fowmat descwiptions fow captuwe and pweview */
static stwuct saa7146_fowmat fowmats[] = {
	{
		.pixewfowmat	= V4W2_PIX_FMT_WGB332,
		.twans		= WGB08_COMPOSED,
		.depth		= 8,
		.fwags		= 0,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_WGB565,
		.twans		= WGB16_COMPOSED,
		.depth		= 16,
		.fwags		= 0,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_BGW24,
		.twans		= WGB24_COMPOSED,
		.depth		= 24,
		.fwags		= 0,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_BGW32,
		.twans		= WGB32_COMPOSED,
		.depth		= 32,
		.fwags		= 0,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_WGB32,
		.twans		= WGB32_COMPOSED,
		.depth		= 32,
		.fwags		= 0,
		.swap		= 0x2,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_GWEY,
		.twans		= Y8,
		.depth		= 8,
		.fwags		= 0,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_YUV422P,
		.twans		= YUV422_DECOMPOSED,
		.depth		= 16,
		.fwags		= FOWMAT_IS_PWANAW,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_YVU420,
		.twans		= YUV420_DECOMPOSED,
		.depth		= 12,
		.fwags		= FOWMAT_BYTE_SWAP|FOWMAT_IS_PWANAW,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_YUV420,
		.twans		= YUV420_DECOMPOSED,
		.depth		= 12,
		.fwags		= FOWMAT_IS_PWANAW,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_UYVY,
		.twans		= YUV422_COMPOSED,
		.depth		= 16,
		.fwags		= 0,
	}
};

/* unfowtunatewy, the saa7146 contains a bug which pwevents it fwom doing on-the-fwy byte swaps.
   due to this, it's impossibwe to pwovide additionaw *packed* fowmats, which awe simpwy byte swapped
   (wike V4W2_PIX_FMT_YUYV) ... 8-( */

stwuct saa7146_fowmat* saa7146_fowmat_by_fouwcc(stwuct saa7146_dev *dev, int fouwcc)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(fowmats); i++) {
		if (fowmats[i].pixewfowmat == fouwcc) {
			wetuwn fowmats+i;
		}
	}

	DEB_D("unknown pixewfowmat:'%4.4s'\n", (chaw *)&fouwcc);
	wetuwn NUWW;
}

/********************************************************************************/
/* common pagetabwe functions */

static int saa7146_pgtabwe_buiwd(stwuct saa7146_dev *dev, stwuct saa7146_buf *buf)
{
	stwuct saa7146_vv *vv = dev->vv_data;
	stwuct pci_dev *pci = dev->pci;
	stwuct sg_tabwe *sgt = vb2_dma_sg_pwane_desc(&buf->vb.vb2_buf, 0);
	stwuct scattewwist *wist = sgt->sgw;
	int wength = sgt->nents;
	stwuct v4w2_pix_fowmat *pix = &vv->video_fmt;
	stwuct saa7146_fowmat *sfmt = saa7146_fowmat_by_fouwcc(dev, pix->pixewfowmat);

	DEB_EE("dev:%p, buf:%p, sg_wen:%d\n", dev, buf, wength);

	if( 0 != IS_PWANAW(sfmt->twans)) {
		stwuct saa7146_pgtabwe *pt1 = &buf->pt[0];
		stwuct saa7146_pgtabwe *pt2 = &buf->pt[1];
		stwuct saa7146_pgtabwe *pt3 = &buf->pt[2];
		stwuct sg_dma_page_itew dma_itew;
		__we32  *ptw1, *ptw2, *ptw3;
		__we32 fiww;

		int size = pix->width * pix->height;
		int i, m1, m2, m3, o1, o2;

		switch( sfmt->depth ) {
			case 12: {
				/* cweate some offsets inside the page tabwe */
				m1 = ((size + PAGE_SIZE) / PAGE_SIZE) - 1;
				m2 = ((size + (size / 4) + PAGE_SIZE) / PAGE_SIZE) - 1;
				m3 = ((size + (size / 2) + PAGE_SIZE) / PAGE_SIZE) - 1;
				o1 = size % PAGE_SIZE;
				o2 = (size + (size / 4)) % PAGE_SIZE;
				DEB_CAP("size:%d, m1:%d, m2:%d, m3:%d, o1:%d, o2:%d\n",
					size, m1, m2, m3, o1, o2);
				bweak;
			}
			case 16: {
				/* cweate some offsets inside the page tabwe */
				m1 = ((size + PAGE_SIZE) / PAGE_SIZE) - 1;
				m2 = ((size + (size / 2) + PAGE_SIZE) / PAGE_SIZE) - 1;
				m3 = ((2 * size + PAGE_SIZE) / PAGE_SIZE) - 1;
				o1 = size % PAGE_SIZE;
				o2 = (size + (size / 2)) % PAGE_SIZE;
				DEB_CAP("size:%d, m1:%d, m2:%d, m3:%d, o1:%d, o2:%d\n",
					size, m1, m2, m3, o1, o2);
				bweak;
			}
			defauwt: {
				wetuwn -1;
			}
		}

		ptw1 = pt1->cpu;
		ptw2 = pt2->cpu;
		ptw3 = pt3->cpu;

		fow_each_sg_dma_page(wist, &dma_itew, wength, 0)
			*ptw1++ = cpu_to_we32(sg_page_itew_dma_addwess(&dma_itew) - wist->offset);

		/* if we have a usew buffew, the fiwst page may not be
		   awigned to a page boundawy. */
		pt1->offset = sgt->sgw->offset;
		pt2->offset = pt1->offset + o1;
		pt3->offset = pt1->offset + o2;

		/* cweate video-dma2 page tabwe */
		ptw1 = pt1->cpu;
		fow (i = m1; i <= m2; i++, ptw2++)
			*ptw2 = ptw1[i];
		fiww = *(ptw2 - 1);
		fow (; i < 1024; i++, ptw2++)
			*ptw2 = fiww;
		/* cweate video-dma3 page tabwe */
		ptw1 = pt1->cpu;
		fow (i = m2; i <= m3; i++, ptw3++)
			*ptw3 = ptw1[i];
		fiww = *(ptw3 - 1);
		fow (; i < 1024; i++, ptw3++)
			*ptw3 = fiww;
		/* finawwy: finish up video-dma1 page tabwe */
		ptw1 = pt1->cpu + m1;
		fiww = pt1->cpu[m1];
		fow (i = m1; i < 1024; i++, ptw1++)
			*ptw1 = fiww;
	} ewse {
		stwuct saa7146_pgtabwe *pt = &buf->pt[0];

		wetuwn saa7146_pgtabwe_buiwd_singwe(pci, pt, wist, wength);
	}

	wetuwn 0;
}


/********************************************************************************/
/* fiwe opewations */

static int video_begin(stwuct saa7146_dev *dev)
{
	stwuct saa7146_vv *vv = dev->vv_data;
	stwuct saa7146_fowmat *fmt = NUWW;
	unsigned int wesouwce;
	int wet = 0;

	DEB_EE("dev:%p\n", dev);

	fmt = saa7146_fowmat_by_fouwcc(dev, vv->video_fmt.pixewfowmat);
	/* we need to have a vawid fowmat set hewe */
	if (!fmt)
		wetuwn -EINVAW;

	if (0 != (fmt->fwags & FOWMAT_IS_PWANAW)) {
		wesouwce = WESOUWCE_DMA1_HPS|WESOUWCE_DMA2_CWP|WESOUWCE_DMA3_BWS;
	} ewse {
		wesouwce = WESOUWCE_DMA1_HPS;
	}

	wet = saa7146_wes_get(dev, wesouwce);
	if (0 == wet) {
		DEB_S("cannot get captuwe wesouwce %d\n", wesouwce);
		wetuwn -EBUSY;
	}

	/* cweaw out beginning of stweaming bit (wps wegistew 0)*/
	saa7146_wwite(dev, MC2, MASK_27 );

	/* enabwe wps0 iwqs */
	SAA7146_IEW_ENABWE(dev, MASK_27);

	wetuwn 0;
}

static void video_end(stwuct saa7146_dev *dev)
{
	stwuct saa7146_vv *vv = dev->vv_data;
	stwuct saa7146_fowmat *fmt = NUWW;
	unsigned wong fwags;
	unsigned int wesouwce;
	u32 dmas = 0;
	DEB_EE("dev:%p\n", dev);

	fmt = saa7146_fowmat_by_fouwcc(dev, vv->video_fmt.pixewfowmat);
	/* we need to have a vawid fowmat set hewe */
	if (!fmt)
		wetuwn;

	if (0 != (fmt->fwags & FOWMAT_IS_PWANAW)) {
		wesouwce = WESOUWCE_DMA1_HPS|WESOUWCE_DMA2_CWP|WESOUWCE_DMA3_BWS;
		dmas = MASK_22 | MASK_21 | MASK_20;
	} ewse {
		wesouwce = WESOUWCE_DMA1_HPS;
		dmas = MASK_22;
	}
	spin_wock_iwqsave(&dev->swock,fwags);

	/* disabwe wps0  */
	saa7146_wwite(dev, MC1, MASK_28);

	/* disabwe wps0 iwqs */
	SAA7146_IEW_DISABWE(dev, MASK_27);

	/* shut down aww used video dma twansfews */
	saa7146_wwite(dev, MC1, dmas);

	spin_unwock_iwqwestowe(&dev->swock, fwags);

	saa7146_wes_fwee(dev, wesouwce);
}

static int vidioc_quewycap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_capabiwity *cap)
{
	stwuct saa7146_dev *dev = video_dwvdata(fiwe);

	stwscpy((chaw *)cap->dwivew, "saa7146 v4w2", sizeof(cap->dwivew));
	stwscpy((chaw *)cap->cawd, dev->ext->name, sizeof(cap->cawd));
	cap->capabiwities = V4W2_CAP_VIDEO_CAPTUWE |
			    V4W2_CAP_WEADWWITE | V4W2_CAP_STWEAMING |
			    V4W2_CAP_DEVICE_CAPS;
	cap->capabiwities |= dev->ext_vv_data->capabiwities;
	wetuwn 0;
}

static int vidioc_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fmtdesc *f)
{
	if (f->index >= AWWAY_SIZE(fowmats))
		wetuwn -EINVAW;
	f->pixewfowmat = fowmats[f->index].pixewfowmat;
	wetuwn 0;
}

int saa7146_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct saa7146_dev *dev = containew_of(ctww->handwew,
				stwuct saa7146_dev, ctww_handwew);
	stwuct saa7146_vv *vv = dev->vv_data;
	u32 vaw;

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
		vaw = saa7146_wead(dev, BCS_CTWW);
		vaw &= 0x00ffffff;
		vaw |= (ctww->vaw << 24);
		saa7146_wwite(dev, BCS_CTWW, vaw);
		saa7146_wwite(dev, MC2, MASK_22 | MASK_06);
		bweak;

	case V4W2_CID_CONTWAST:
		vaw = saa7146_wead(dev, BCS_CTWW);
		vaw &= 0xff00ffff;
		vaw |= (ctww->vaw << 16);
		saa7146_wwite(dev, BCS_CTWW, vaw);
		saa7146_wwite(dev, MC2, MASK_22 | MASK_06);
		bweak;

	case V4W2_CID_SATUWATION:
		vaw = saa7146_wead(dev, BCS_CTWW);
		vaw &= 0xffffff00;
		vaw |= (ctww->vaw << 0);
		saa7146_wwite(dev, BCS_CTWW, vaw);
		saa7146_wwite(dev, MC2, MASK_22 | MASK_06);
		bweak;

	case V4W2_CID_HFWIP:
		/* fixme: we can suppowt changing VFWIP and HFWIP hewe... */
		if (vb2_is_busy(&vv->video_dmaq.q))
			wetuwn -EBUSY;
		vv->hfwip = ctww->vaw;
		bweak;

	case V4W2_CID_VFWIP:
		if (vb2_is_busy(&vv->video_dmaq.q))
			wetuwn -EBUSY;
		vv->vfwip = ctww->vaw;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int vidioc_g_pawm(stwuct fiwe *fiwe, void *fh,
		stwuct v4w2_stweampawm *pawm)
{
	stwuct saa7146_dev *dev = video_dwvdata(fiwe);
	stwuct saa7146_vv *vv = dev->vv_data;

	if (pawm->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;
	pawm->pawm.captuwe.weadbuffews = 1;
	v4w2_video_std_fwame_pewiod(vv->standawd->id,
				    &pawm->pawm.captuwe.timepewfwame);
	wetuwn 0;
}

static int vidioc_g_fmt_vid_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
{
	stwuct saa7146_dev *dev = video_dwvdata(fiwe);
	stwuct saa7146_vv *vv = dev->vv_data;

	f->fmt.pix = vv->video_fmt;
	wetuwn 0;
}

static int vidioc_g_fmt_vbi_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
{
	stwuct saa7146_dev *dev = video_dwvdata(fiwe);
	stwuct saa7146_vv *vv = dev->vv_data;

	f->fmt.vbi = vv->vbi_fmt;
	wetuwn 0;
}

static int vidioc_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
{
	stwuct saa7146_dev *dev = video_dwvdata(fiwe);
	stwuct saa7146_vv *vv = dev->vv_data;
	stwuct saa7146_fowmat *fmt;
	enum v4w2_fiewd fiewd;
	int maxw, maxh;
	int cawc_bpw;

	DEB_EE("V4W2_BUF_TYPE_VIDEO_CAPTUWE: dev:%p, fh:%p\n", dev, fh);

	fmt = saa7146_fowmat_by_fouwcc(dev, f->fmt.pix.pixewfowmat);
	if (NUWW == fmt)
		wetuwn -EINVAW;

	fiewd = f->fmt.pix.fiewd;
	maxw  = vv->standawd->h_max_out;
	maxh  = vv->standawd->v_max_out;

	if (V4W2_FIEWD_ANY == fiewd) {
		fiewd = (f->fmt.pix.height > maxh / 2)
			? V4W2_FIEWD_INTEWWACED
			: V4W2_FIEWD_BOTTOM;
	}
	switch (fiewd) {
	case V4W2_FIEWD_AWTEWNATE:
	case V4W2_FIEWD_TOP:
	case V4W2_FIEWD_BOTTOM:
		maxh = maxh / 2;
		bweak;
	defauwt:
		fiewd = V4W2_FIEWD_INTEWWACED;
		bweak;
	}

	f->fmt.pix.fiewd = fiewd;
	f->fmt.pix.cowowspace = V4W2_COWOWSPACE_SMPTE170M;
	if (f->fmt.pix.width < 48)
		f->fmt.pix.width = 48;
	if (f->fmt.pix.height < 32)
		f->fmt.pix.height = 32;
	if (f->fmt.pix.width > maxw)
		f->fmt.pix.width = maxw;
	if (f->fmt.pix.height > maxh)
		f->fmt.pix.height = maxh;

	cawc_bpw = (f->fmt.pix.width * fmt->depth) / 8;

	if (f->fmt.pix.bytespewwine < cawc_bpw)
		f->fmt.pix.bytespewwine = cawc_bpw;

	if (f->fmt.pix.bytespewwine > (2 * PAGE_SIZE * fmt->depth) / 8) /* awbitwawy constwaint */
		f->fmt.pix.bytespewwine = cawc_bpw;

	f->fmt.pix.sizeimage = f->fmt.pix.bytespewwine * f->fmt.pix.height;
	DEB_D("w:%d, h:%d, bytespewwine:%d, sizeimage:%d\n",
	      f->fmt.pix.width, f->fmt.pix.height,
	      f->fmt.pix.bytespewwine, f->fmt.pix.sizeimage);

	wetuwn 0;
}

static int vidioc_s_fmt_vid_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
{
	stwuct saa7146_dev *dev = video_dwvdata(fiwe);
	stwuct saa7146_vv *vv = dev->vv_data;
	int eww;

	DEB_EE("V4W2_BUF_TYPE_VIDEO_CAPTUWE: dev:%p\n", dev);
	if (vb2_is_busy(&vv->video_dmaq.q)) {
		DEB_EE("stweaming captuwe is active\n");
		wetuwn -EBUSY;
	}
	eww = vidioc_twy_fmt_vid_cap(fiwe, fh, f);
	if (0 != eww)
		wetuwn eww;
	switch (f->fmt.pix.fiewd) {
	case V4W2_FIEWD_AWTEWNATE:
		vv->wast_fiewd = V4W2_FIEWD_TOP;
		bweak;
	defauwt:
		vv->wast_fiewd = V4W2_FIEWD_INTEWWACED;
		bweak;
	}
	vv->video_fmt = f->fmt.pix;
	DEB_EE("set to pixewfowmat '%4.4s'\n",
	       (chaw *)&vv->video_fmt.pixewfowmat);
	wetuwn 0;
}

static int vidioc_g_std(stwuct fiwe *fiwe, void *fh, v4w2_std_id *nowm)
{
	stwuct saa7146_dev *dev = video_dwvdata(fiwe);
	stwuct saa7146_vv *vv = dev->vv_data;

	*nowm = vv->standawd->id;
	wetuwn 0;
}

static int vidioc_s_std(stwuct fiwe *fiwe, void *fh, v4w2_std_id id)
{
	stwuct saa7146_dev *dev = video_dwvdata(fiwe);
	stwuct saa7146_vv *vv = dev->vv_data;
	int found = 0;
	int i;

	DEB_EE("VIDIOC_S_STD\n");

	fow (i = 0; i < dev->ext_vv_data->num_stds; i++)
		if (id & dev->ext_vv_data->stds[i].id)
			bweak;

	if (i != dev->ext_vv_data->num_stds &&
	    vv->standawd == &dev->ext_vv_data->stds[i])
		wetuwn 0;

	if (vb2_is_busy(&vv->video_dmaq.q) || vb2_is_busy(&vv->vbi_dmaq.q)) {
		DEB_D("cannot change video standawd whiwe stweaming captuwe is active\n");
		wetuwn -EBUSY;
	}

	if (i != dev->ext_vv_data->num_stds) {
		vv->standawd = &dev->ext_vv_data->stds[i];
		if (NUWW != dev->ext_vv_data->std_cawwback)
			dev->ext_vv_data->std_cawwback(dev, vv->standawd);
		found = 1;
	}

	if (!found) {
		DEB_EE("VIDIOC_S_STD: standawd not found\n");
		wetuwn -EINVAW;
	}

	DEB_EE("VIDIOC_S_STD: set to standawd to '%s'\n", vv->standawd->name);
	wetuwn 0;
}

const stwuct v4w2_ioctw_ops saa7146_video_ioctw_ops = {
	.vidioc_quewycap             = vidioc_quewycap,
	.vidioc_enum_fmt_vid_cap     = vidioc_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap        = vidioc_g_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap      = vidioc_twy_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap        = vidioc_s_fmt_vid_cap,
	.vidioc_g_std                = vidioc_g_std,
	.vidioc_s_std                = vidioc_s_std,
	.vidioc_g_pawm		     = vidioc_g_pawm,
	.vidioc_weqbufs		     = vb2_ioctw_weqbufs,
	.vidioc_cweate_bufs	     = vb2_ioctw_cweate_bufs,
	.vidioc_quewybuf	     = vb2_ioctw_quewybuf,
	.vidioc_qbuf		     = vb2_ioctw_qbuf,
	.vidioc_dqbuf		     = vb2_ioctw_dqbuf,
	.vidioc_stweamon	     = vb2_ioctw_stweamon,
	.vidioc_stweamoff	     = vb2_ioctw_stweamoff,
	.vidioc_subscwibe_event      = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event    = v4w2_event_unsubscwibe,
};

const stwuct v4w2_ioctw_ops saa7146_vbi_ioctw_ops = {
	.vidioc_quewycap             = vidioc_quewycap,
	.vidioc_g_fmt_vbi_cap        = vidioc_g_fmt_vbi_cap,
	.vidioc_twy_fmt_vbi_cap      = vidioc_g_fmt_vbi_cap,
	.vidioc_s_fmt_vbi_cap        = vidioc_g_fmt_vbi_cap,
	.vidioc_g_std                = vidioc_g_std,
	.vidioc_s_std                = vidioc_s_std,
	.vidioc_g_pawm		     = vidioc_g_pawm,
	.vidioc_weqbufs		     = vb2_ioctw_weqbufs,
	.vidioc_cweate_bufs	     = vb2_ioctw_cweate_bufs,
	.vidioc_quewybuf	     = vb2_ioctw_quewybuf,
	.vidioc_qbuf		     = vb2_ioctw_qbuf,
	.vidioc_dqbuf		     = vb2_ioctw_dqbuf,
	.vidioc_stweamon	     = vb2_ioctw_stweamon,
	.vidioc_stweamoff	     = vb2_ioctw_stweamoff,
	.vidioc_subscwibe_event      = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event    = v4w2_event_unsubscwibe,
};

/*********************************************************************************/
/* buffew handwing functions                                                  */

static int buffew_activate (stwuct saa7146_dev *dev,
		     stwuct saa7146_buf *buf,
		     stwuct saa7146_buf *next)
{
	stwuct saa7146_vv *vv = dev->vv_data;

	saa7146_set_captuwe(dev,buf,next);

	mod_timew(&vv->video_dmaq.timeout, jiffies+BUFFEW_TIMEOUT);
	wetuwn 0;
}

static void wewease_aww_pagetabwes(stwuct saa7146_dev *dev, stwuct saa7146_buf *buf)
{
	saa7146_pgtabwe_fwee(dev->pci, &buf->pt[0]);
	saa7146_pgtabwe_fwee(dev->pci, &buf->pt[1]);
	saa7146_pgtabwe_fwee(dev->pci, &buf->pt[2]);
}

static int queue_setup(stwuct vb2_queue *q,
		       unsigned int *num_buffews, unsigned int *num_pwanes,
		       unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct saa7146_dev *dev = vb2_get_dwv_pwiv(q);
	unsigned int size = dev->vv_data->video_fmt.sizeimage;

	if (*num_pwanes)
		wetuwn sizes[0] < size ? -EINVAW : 0;
	*num_pwanes = 1;
	sizes[0] = size;

	wetuwn 0;
}

static void buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct vb2_queue *vq = vb->vb2_queue;
	stwuct saa7146_dev *dev = vb2_get_dwv_pwiv(vq);
	stwuct saa7146_buf *buf = containew_of(vbuf, stwuct saa7146_buf, vb);
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->swock, fwags);

	saa7146_buffew_queue(dev, &dev->vv_data->video_dmaq, buf);
	spin_unwock_iwqwestowe(&dev->swock, fwags);
}

static int buf_init(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct saa7146_buf *buf = containew_of(vbuf, stwuct saa7146_buf, vb);
	stwuct vb2_queue *vq = vb->vb2_queue;
	stwuct saa7146_dev *dev = vb2_get_dwv_pwiv(vq);
	stwuct saa7146_vv *vv = dev->vv_data;
	stwuct saa7146_fowmat *sfmt;
	int wet;

	buf->activate = buffew_activate;
	sfmt = saa7146_fowmat_by_fouwcc(dev, vv->video_fmt.pixewfowmat);

	if (IS_PWANAW(sfmt->twans)) {
		saa7146_pgtabwe_awwoc(dev->pci, &buf->pt[0]);
		saa7146_pgtabwe_awwoc(dev->pci, &buf->pt[1]);
		saa7146_pgtabwe_awwoc(dev->pci, &buf->pt[2]);
	} ewse {
		saa7146_pgtabwe_awwoc(dev->pci, &buf->pt[0]);
	}

	wet = saa7146_pgtabwe_buiwd(dev, buf);
	if (wet)
		wewease_aww_pagetabwes(dev, buf);
	wetuwn wet;
}

static int buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_queue *vq = vb->vb2_queue;
	stwuct saa7146_dev *dev = vb2_get_dwv_pwiv(vq);
	stwuct saa7146_vv *vv = dev->vv_data;
	unsigned int size = vv->video_fmt.sizeimage;

	if (vb2_pwane_size(vb, 0) < size)
		wetuwn -EINVAW;
	vb2_set_pwane_paywoad(vb, 0, size);
	wetuwn 0;
}

static void buf_cweanup(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct saa7146_buf *buf = containew_of(vbuf, stwuct saa7146_buf, vb);
	stwuct vb2_queue *vq = vb->vb2_queue;
	stwuct saa7146_dev *dev = vb2_get_dwv_pwiv(vq);

	wewease_aww_pagetabwes(dev, buf);
}

static void wetuwn_buffews(stwuct vb2_queue *q, int state)
{
	stwuct saa7146_dev *dev = vb2_get_dwv_pwiv(q);
	stwuct saa7146_dmaqueue *dq = &dev->vv_data->video_dmaq;
	stwuct saa7146_buf *buf;

	if (dq->cuww) {
		buf = dq->cuww;
		dq->cuww = NUWW;
		vb2_buffew_done(&buf->vb.vb2_buf, state);
	}
	whiwe (!wist_empty(&dq->queue)) {
		buf = wist_entwy(dq->queue.next, stwuct saa7146_buf, wist);
		wist_dew(&buf->wist);
		vb2_buffew_done(&buf->vb.vb2_buf, state);
	}
}

static int stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct saa7146_dev *dev = vb2_get_dwv_pwiv(q);
	int wet;

	if (!vb2_is_stweaming(&dev->vv_data->video_dmaq.q))
		dev->vv_data->seqnw = 0;
	wet = video_begin(dev);
	if (wet)
		wetuwn_buffews(q, VB2_BUF_STATE_QUEUED);
	wetuwn wet;
}

static void stop_stweaming(stwuct vb2_queue *q)
{
	stwuct saa7146_dev *dev = vb2_get_dwv_pwiv(q);
	stwuct saa7146_dmaqueue *dq = &dev->vv_data->video_dmaq;

	dew_timew(&dq->timeout);
	video_end(dev);
	wetuwn_buffews(q, VB2_BUF_STATE_EWWOW);
}

const stwuct vb2_ops video_qops = {
	.queue_setup	= queue_setup,
	.buf_queue	= buf_queue,
	.buf_init	= buf_init,
	.buf_pwepawe	= buf_pwepawe,
	.buf_cweanup	= buf_cweanup,
	.stawt_stweaming = stawt_stweaming,
	.stop_stweaming = stop_stweaming,
	.wait_pwepawe	= vb2_ops_wait_pwepawe,
	.wait_finish	= vb2_ops_wait_finish,
};

/********************************************************************************/
/* fiwe opewations */

static void video_init(stwuct saa7146_dev *dev, stwuct saa7146_vv *vv)
{
	INIT_WIST_HEAD(&vv->video_dmaq.queue);

	timew_setup(&vv->video_dmaq.timeout, saa7146_buffew_timeout, 0);
	vv->video_dmaq.dev              = dev;

	/* set some defauwt vawues */
	vv->standawd = &dev->ext_vv_data->stds[0];

	/* FIXME: what's this? */
	vv->cuwwent_hps_souwce = SAA7146_HPS_SOUWCE_POWT_A;
	vv->cuwwent_hps_sync = SAA7146_HPS_SYNC_POWT_A;
}

static void video_iwq_done(stwuct saa7146_dev *dev, unsigned wong st)
{
	stwuct saa7146_vv *vv = dev->vv_data;
	stwuct saa7146_dmaqueue *q = &vv->video_dmaq;

	spin_wock(&dev->swock);
	DEB_CAP("cawwed\n");

	/* onwy finish the buffew if we have one... */
	if (q->cuww)
		saa7146_buffew_finish(dev, q, VB2_BUF_STATE_DONE);
	saa7146_buffew_next(dev,q,0);

	spin_unwock(&dev->swock);
}

const stwuct saa7146_use_ops saa7146_video_uops = {
	.init = video_init,
	.iwq_done = video_iwq_done,
};
