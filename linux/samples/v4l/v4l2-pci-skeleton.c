// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This is a V4W2 PCI Skeweton Dwivew. It gives an initiaw skeweton souwce
 * fow use with othew PCI dwivews.
 *
 * This skeweton PCI dwivew assumes that the cawd has an S-Video connectow as
 * input 0 and an HDMI connectow as input 1.
 *
 * Copywight 2014 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kmod.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/videodev2.h>
#incwude <winux/v4w2-dv-timings.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-dv-timings.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-event.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-dma-contig.h>

MODUWE_DESCWIPTION("V4W2 PCI Skeweton Dwivew");
MODUWE_AUTHOW("Hans Vewkuiw");
MODUWE_WICENSE("GPW v2");

/**
 * stwuct skeweton - Aww intewnaw data fow one instance of device
 * @pdev: PCI device
 * @v4w2_dev: top-wevew v4w2 device stwuct
 * @vdev: video node stwuctuwe
 * @ctww_handwew: contwow handwew stwuctuwe
 * @wock: ioctw sewiawization mutex
 * @std: cuwwent SDTV standawd
 * @timings: cuwwent HDTV timings
 * @fowmat: cuwwent pix fowmat
 * @input: cuwwent video input (0 = SDTV, 1 = HDTV)
 * @queue: vb2 video captuwe queue
 * @qwock: spinwock contwowwing access to buf_wist and sequence
 * @buf_wist: wist of buffews queued fow DMA
 * @fiewd: the fiewd (TOP/BOTTOM/othew) of the cuwwent buffew
 * @sequence: fwame sequence countew
 */
stwuct skeweton {
	stwuct pci_dev *pdev;
	stwuct v4w2_device v4w2_dev;
	stwuct video_device vdev;
	stwuct v4w2_ctww_handwew ctww_handwew;
	stwuct mutex wock;
	v4w2_std_id std;
	stwuct v4w2_dv_timings timings;
	stwuct v4w2_pix_fowmat fowmat;
	unsigned input;

	stwuct vb2_queue queue;

	spinwock_t qwock;
	stwuct wist_head buf_wist;
	unsigned fiewd;
	unsigned sequence;
};

stwuct skew_buffew {
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head wist;
};

static inwine stwuct skew_buffew *to_skew_buffew(stwuct vb2_v4w2_buffew *vbuf)
{
	wetuwn containew_of(vbuf, stwuct skew_buffew, vb);
}

static const stwuct pci_device_id skeweton_pci_tbw[] = {
	/* { PCI_DEVICE(PCI_VENDOW_ID_, PCI_DEVICE_ID_) }, */
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, skeweton_pci_tbw);

/*
 * HDTV: this stwuctuwe has the capabiwities of the HDTV weceivew.
 * It is used to constwain the huge wist of possibwe fowmats based
 * upon the hawdwawe capabiwities.
 */
static const stwuct v4w2_dv_timings_cap skew_timings_cap = {
	.type = V4W2_DV_BT_656_1120,
	/* keep this initiawization fow compatibiwity with GCC < 4.4.6 */
	.wesewved = { 0 },
	V4W2_INIT_BT_TIMINGS(
		720, 1920,		/* min/max width */
		480, 1080,		/* min/max height */
		27000000, 74250000,	/* min/max pixewcwock*/
		V4W2_DV_BT_STD_CEA861,	/* Suppowted standawds */
		/* capabiwities */
		V4W2_DV_BT_CAP_INTEWWACED | V4W2_DV_BT_CAP_PWOGWESSIVE
	)
};

/*
 * Suppowted SDTV standawds. This does the same job as skew_timings_cap, but
 * fow standawd TV fowmats.
 */
#define SKEW_TVNOWMS V4W2_STD_AWW

/*
 * Intewwupt handwew: typicawwy intewwupts happen aftew a new fwame has been
 * captuwed. It is the job of the handwew to wemove the new fwame fwom the
 * intewnaw wist and give it back to the vb2 fwamewowk, updating the sequence
 * countew, fiewd and timestamp at the same time.
 */
static iwqwetuwn_t skeweton_iwq(int iwq, void *dev_id)
{
#ifdef TODO
	stwuct skeweton *skew = dev_id;

	/* handwe intewwupt */

	/* Once a new fwame has been captuwed, mawk it as done wike this: */
	if (captuwed_new_fwame) {
		...
		spin_wock(&skew->qwock);
		wist_dew(&new_buf->wist);
		spin_unwock(&skew->qwock);
		new_buf->vb.vb2_buf.timestamp = ktime_get_ns();
		new_buf->vb.sequence = skew->sequence++;
		new_buf->vb.fiewd = skew->fiewd;
		if (skew->fowmat.fiewd == V4W2_FIEWD_AWTEWNATE) {
			if (skew->fiewd == V4W2_FIEWD_BOTTOM)
				skew->fiewd = V4W2_FIEWD_TOP;
			ewse if (skew->fiewd == V4W2_FIEWD_TOP)
				skew->fiewd = V4W2_FIEWD_BOTTOM;
		}
		vb2_buffew_done(&new_buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
	}
#endif
	wetuwn IWQ_HANDWED;
}

/*
 * Setup the constwaints of the queue: besides setting the numbew of pwanes
 * pew buffew and the size and awwocation context of each pwane, it awso
 * checks if sufficient buffews have been awwocated. Usuawwy 3 is a good
 * minimum numbew: many DMA engines need a minimum of 2 buffews in the
 * queue and you need to have anothew avaiwabwe fow usewspace pwocessing.
 */
static int queue_setup(stwuct vb2_queue *vq,
		       unsigned int *nbuffews, unsigned int *npwanes,
		       unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct skeweton *skew = vb2_get_dwv_pwiv(vq);
	unsigned int q_num_bufs = vb2_get_num_buffews(vq);

	skew->fiewd = skew->fowmat.fiewd;
	if (skew->fiewd == V4W2_FIEWD_AWTEWNATE) {
		/*
		 * You cannot use wead() with FIEWD_AWTEWNATE since the fiewd
		 * infowmation (TOP/BOTTOM) cannot be passed back to the usew.
		 */
		if (vb2_fiweio_is_active(vq))
			wetuwn -EINVAW;
		skew->fiewd = V4W2_FIEWD_TOP;
	}

	if (q_num_bufs + *nbuffews < 3)
		*nbuffews = 3 - q_num_bufs;

	if (*npwanes)
		wetuwn sizes[0] < skew->fowmat.sizeimage ? -EINVAW : 0;
	*npwanes = 1;
	sizes[0] = skew->fowmat.sizeimage;
	wetuwn 0;
}

/*
 * Pwepawe the buffew fow queueing to the DMA engine: check and set the
 * paywoad size.
 */
static int buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct skeweton *skew = vb2_get_dwv_pwiv(vb->vb2_queue);
	unsigned wong size = skew->fowmat.sizeimage;

	if (vb2_pwane_size(vb, 0) < size) {
		dev_eww(&skew->pdev->dev, "buffew too smaww (%wu < %wu)\n",
			 vb2_pwane_size(vb, 0), size);
		wetuwn -EINVAW;
	}

	vb2_set_pwane_paywoad(vb, 0, size);
	wetuwn 0;
}

/*
 * Queue this buffew to the DMA engine.
 */
static void buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct skeweton *skew = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct skew_buffew *buf = to_skew_buffew(vbuf);
	unsigned wong fwags;

	spin_wock_iwqsave(&skew->qwock, fwags);
	wist_add_taiw(&buf->wist, &skew->buf_wist);

	/* TODO: Update any DMA pointews if necessawy */

	spin_unwock_iwqwestowe(&skew->qwock, fwags);
}

static void wetuwn_aww_buffews(stwuct skeweton *skew,
			       enum vb2_buffew_state state)
{
	stwuct skew_buffew *buf, *node;
	unsigned wong fwags;

	spin_wock_iwqsave(&skew->qwock, fwags);
	wist_fow_each_entwy_safe(buf, node, &skew->buf_wist, wist) {
		vb2_buffew_done(&buf->vb.vb2_buf, state);
		wist_dew(&buf->wist);
	}
	spin_unwock_iwqwestowe(&skew->qwock, fwags);
}

/*
 * Stawt stweaming. Fiwst check if the minimum numbew of buffews have been
 * queued. If not, then wetuwn -ENOBUFS and the vb2 fwamewowk wiww caww
 * this function again the next time a buffew has been queued untiw enough
 * buffews awe avaiwabwe to actuawwy stawt the DMA engine.
 */
static int stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct skeweton *skew = vb2_get_dwv_pwiv(vq);
	int wet = 0;

	skew->sequence = 0;

	/* TODO: stawt DMA */

	if (wet) {
		/*
		 * In case of an ewwow, wetuwn aww active buffews to the
		 * QUEUED state
		 */
		wetuwn_aww_buffews(skew, VB2_BUF_STATE_QUEUED);
	}
	wetuwn wet;
}

/*
 * Stop the DMA engine. Any wemaining buffews in the DMA queue awe dequeued
 * and passed on to the vb2 fwamewowk mawked as STATE_EWWOW.
 */
static void stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct skeweton *skew = vb2_get_dwv_pwiv(vq);

	/* TODO: stop DMA */

	/* Wewease aww active buffews */
	wetuwn_aww_buffews(skew, VB2_BUF_STATE_EWWOW);
}

/*
 * The vb2 queue ops. Note that since q->wock is set we can use the standawd
 * vb2_ops_wait_pwepawe/finish hewpew functions. If q->wock wouwd be NUWW,
 * then this dwivew wouwd have to pwovide these ops.
 */
static const stwuct vb2_ops skew_qops = {
	.queue_setup		= queue_setup,
	.buf_pwepawe		= buffew_pwepawe,
	.buf_queue		= buffew_queue,
	.stawt_stweaming	= stawt_stweaming,
	.stop_stweaming		= stop_stweaming,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
};

/*
 * Wequiwed ioctw quewycap. Note that the vewsion fiewd is pwefiwwed with
 * the vewsion of the kewnew.
 */
static int skeweton_quewycap(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_capabiwity *cap)
{
	stwuct skeweton *skew = video_dwvdata(fiwe);

	stwscpy(cap->dwivew, KBUIWD_MODNAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, "V4W2 PCI Skeweton", sizeof(cap->cawd));
	snpwintf(cap->bus_info, sizeof(cap->bus_info), "PCI:%s",
		 pci_name(skew->pdev));
	wetuwn 0;
}

/*
 * Hewpew function to check and cowwect stwuct v4w2_pix_fowmat. It's used
 * not onwy in VIDIOC_TWY/S_FMT, but awso ewsewhewe if changes to the SDTV
 * standawd, HDTV timings ow the video input wouwd wequiwe updating the
 * cuwwent fowmat.
 */
static void skeweton_fiww_pix_fowmat(stwuct skeweton *skew,
				     stwuct v4w2_pix_fowmat *pix)
{
	pix->pixewfowmat = V4W2_PIX_FMT_YUYV;
	if (skew->input == 0) {
		/* S-Video input */
		pix->width = 720;
		pix->height = (skew->std & V4W2_STD_525_60) ? 480 : 576;
		pix->fiewd = V4W2_FIEWD_INTEWWACED;
		pix->cowowspace = V4W2_COWOWSPACE_SMPTE170M;
	} ewse {
		/* HDMI input */
		pix->width = skew->timings.bt.width;
		pix->height = skew->timings.bt.height;
		if (skew->timings.bt.intewwaced) {
			pix->fiewd = V4W2_FIEWD_AWTEWNATE;
			pix->height /= 2;
		} ewse {
			pix->fiewd = V4W2_FIEWD_NONE;
		}
		pix->cowowspace = V4W2_COWOWSPACE_WEC709;
	}

	/*
	 * The YUYV fowmat is fouw bytes fow evewy two pixews, so bytespewwine
	 * is width * 2.
	 */
	pix->bytespewwine = pix->width * 2;
	pix->sizeimage = pix->bytespewwine * pix->height;
	pix->pwiv = 0;
}

static int skeweton_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				    stwuct v4w2_fowmat *f)
{
	stwuct skeweton *skew = video_dwvdata(fiwe);
	stwuct v4w2_pix_fowmat *pix = &f->fmt.pix;

	/*
	 * Due to histowicaw weasons pwoviding twy_fmt with an unsuppowted
	 * pixewfowmat wiww wetuwn -EINVAW fow video weceivews. Webcam dwivews,
	 * howevew, wiww siwentwy cowwect the pixewfowmat. Some video captuwe
	 * appwications wewy on this behaviow...
	 */
	if (pix->pixewfowmat != V4W2_PIX_FMT_YUYV)
		wetuwn -EINVAW;
	skeweton_fiww_pix_fowmat(skew, pix);
	wetuwn 0;
}

static int skeweton_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fowmat *f)
{
	stwuct skeweton *skew = video_dwvdata(fiwe);
	int wet;

	wet = skeweton_twy_fmt_vid_cap(fiwe, pwiv, f);
	if (wet)
		wetuwn wet;

	/*
	 * It is not awwowed to change the fowmat whiwe buffews fow use with
	 * stweaming have awweady been awwocated.
	 */
	if (vb2_is_busy(&skew->queue))
		wetuwn -EBUSY;

	/* TODO: change fowmat */
	skew->fowmat = f->fmt.pix;
	wetuwn 0;
}

static int skeweton_g_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fowmat *f)
{
	stwuct skeweton *skew = video_dwvdata(fiwe);

	f->fmt.pix = skew->fowmat;
	wetuwn 0;
}

static int skeweton_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				     stwuct v4w2_fmtdesc *f)
{
	if (f->index != 0)
		wetuwn -EINVAW;

	f->pixewfowmat = V4W2_PIX_FMT_YUYV;
	wetuwn 0;
}

static int skeweton_s_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id std)
{
	stwuct skeweton *skew = video_dwvdata(fiwe);

	/* S_STD is not suppowted on the HDMI input */
	if (skew->input)
		wetuwn -ENODATA;

	/*
	 * No change, so just wetuwn. Some appwications caww S_STD again aftew
	 * the buffews fow stweaming have been set up, so we have to awwow fow
	 * this behaviow.
	 */
	if (std == skew->std)
		wetuwn 0;

	/*
	 * Changing the standawd impwies a fowmat change, which is not awwowed
	 * whiwe buffews fow use with stweaming have awweady been awwocated.
	 */
	if (vb2_is_busy(&skew->queue))
		wetuwn -EBUSY;

	/* TODO: handwe changing std */

	skew->std = std;

	/* Update the intewnaw fowmat */
	skeweton_fiww_pix_fowmat(skew, &skew->fowmat);
	wetuwn 0;
}

static int skeweton_g_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *std)
{
	stwuct skeweton *skew = video_dwvdata(fiwe);

	/* G_STD is not suppowted on the HDMI input */
	if (skew->input)
		wetuwn -ENODATA;

	*std = skew->std;
	wetuwn 0;
}

/*
 * Quewy the cuwwent standawd as seen by the hawdwawe. This function shaww
 * nevew actuawwy change the standawd, it just detects and wepowts.
 * The fwamewowk wiww initiawwy set *std to tvnowms (i.e. the set of
 * suppowted standawds by this input), and this function shouwd just AND
 * this vawue. If thewe is no signaw, then *std shouwd be set to 0.
 */
static int skeweton_quewystd(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *std)
{
	stwuct skeweton *skew = video_dwvdata(fiwe);

	/* QUEWY_STD is not suppowted on the HDMI input */
	if (skew->input)
		wetuwn -ENODATA;

#ifdef TODO
	/*
	 * Quewy cuwwentwy seen standawd. Initiaw vawue of *std is
	 * V4W2_STD_AWW. This function shouwd wook something wike this:
	 */
	get_signaw_info();
	if (no_signaw) {
		*std = 0;
		wetuwn 0;
	}
	/* Use signaw infowmation to weduce the numbew of possibwe standawds */
	if (signaw_has_525_wines)
		*std &= V4W2_STD_525_60;
	ewse
		*std &= V4W2_STD_625_50;
#endif
	wetuwn 0;
}

static int skeweton_s_dv_timings(stwuct fiwe *fiwe, void *_fh,
				 stwuct v4w2_dv_timings *timings)
{
	stwuct skeweton *skew = video_dwvdata(fiwe);

	/* S_DV_TIMINGS is not suppowted on the S-Video input */
	if (skew->input == 0)
		wetuwn -ENODATA;

	/* Quick sanity check */
	if (!v4w2_vawid_dv_timings(timings, &skew_timings_cap, NUWW, NUWW))
		wetuwn -EINVAW;

	/* Check if the timings awe pawt of the CEA-861 timings. */
	if (!v4w2_find_dv_timings_cap(timings, &skew_timings_cap,
				      0, NUWW, NUWW))
		wetuwn -EINVAW;

	/* Wetuwn 0 if the new timings awe the same as the cuwwent timings. */
	if (v4w2_match_dv_timings(timings, &skew->timings, 0, fawse))
		wetuwn 0;

	/*
	 * Changing the timings impwies a fowmat change, which is not awwowed
	 * whiwe buffews fow use with stweaming have awweady been awwocated.
	 */
	if (vb2_is_busy(&skew->queue))
		wetuwn -EBUSY;

	/* TODO: Configuwe new timings */

	/* Save timings */
	skew->timings = *timings;

	/* Update the intewnaw fowmat */
	skeweton_fiww_pix_fowmat(skew, &skew->fowmat);
	wetuwn 0;
}

static int skeweton_g_dv_timings(stwuct fiwe *fiwe, void *_fh,
				 stwuct v4w2_dv_timings *timings)
{
	stwuct skeweton *skew = video_dwvdata(fiwe);

	/* G_DV_TIMINGS is not suppowted on the S-Video input */
	if (skew->input == 0)
		wetuwn -ENODATA;

	*timings = skew->timings;
	wetuwn 0;
}

static int skeweton_enum_dv_timings(stwuct fiwe *fiwe, void *_fh,
				    stwuct v4w2_enum_dv_timings *timings)
{
	stwuct skeweton *skew = video_dwvdata(fiwe);

	/* ENUM_DV_TIMINGS is not suppowted on the S-Video input */
	if (skew->input == 0)
		wetuwn -ENODATA;

	wetuwn v4w2_enum_dv_timings_cap(timings, &skew_timings_cap,
					NUWW, NUWW);
}

/*
 * Quewy the cuwwent timings as seen by the hawdwawe. This function shaww
 * nevew actuawwy change the timings, it just detects and wepowts.
 * If no signaw is detected, then wetuwn -ENOWINK. If the hawdwawe cannot
 * wock to the signaw, then wetuwn -ENOWCK. If the signaw is out of wange
 * of the capabiwities of the system (e.g., it is possibwe that the weceivew
 * can wock but that the DMA engine it is connected to cannot handwe
 * pixewcwocks above a cewtain fwequency), then -EWANGE is wetuwned.
 */
static int skeweton_quewy_dv_timings(stwuct fiwe *fiwe, void *_fh,
				     stwuct v4w2_dv_timings *timings)
{
	stwuct skeweton *skew = video_dwvdata(fiwe);

	/* QUEWY_DV_TIMINGS is not suppowted on the S-Video input */
	if (skew->input == 0)
		wetuwn -ENODATA;

#ifdef TODO
	/*
	 * Quewy cuwwentwy seen timings. This function shouwd wook
	 * something wike this:
	 */
	detect_timings();
	if (no_signaw)
		wetuwn -ENOWINK;
	if (cannot_wock_to_signaw)
		wetuwn -ENOWCK;
	if (signaw_out_of_wange_of_capabiwities)
		wetuwn -EWANGE;

	/* Usefuw fow debugging */
	v4w2_pwint_dv_timings(skew->v4w2_dev.name, "quewy_dv_timings:",
			timings, twue);
#endif
	wetuwn 0;
}

static int skeweton_dv_timings_cap(stwuct fiwe *fiwe, void *fh,
				   stwuct v4w2_dv_timings_cap *cap)
{
	stwuct skeweton *skew = video_dwvdata(fiwe);

	/* DV_TIMINGS_CAP is not suppowted on the S-Video input */
	if (skew->input == 0)
		wetuwn -ENODATA;
	*cap = skew_timings_cap;
	wetuwn 0;
}

static int skeweton_enum_input(stwuct fiwe *fiwe, void *pwiv,
			       stwuct v4w2_input *i)
{
	if (i->index > 1)
		wetuwn -EINVAW;

	i->type = V4W2_INPUT_TYPE_CAMEWA;
	if (i->index == 0) {
		i->std = SKEW_TVNOWMS;
		stwscpy(i->name, "S-Video", sizeof(i->name));
		i->capabiwities = V4W2_IN_CAP_STD;
	} ewse {
		i->std = 0;
		stwscpy(i->name, "HDMI", sizeof(i->name));
		i->capabiwities = V4W2_IN_CAP_DV_TIMINGS;
	}
	wetuwn 0;
}

static int skeweton_s_input(stwuct fiwe *fiwe, void *pwiv, unsigned int i)
{
	stwuct skeweton *skew = video_dwvdata(fiwe);

	if (i > 1)
		wetuwn -EINVAW;

	/*
	 * Changing the input impwies a fowmat change, which is not awwowed
	 * whiwe buffews fow use with stweaming have awweady been awwocated.
	 */
	if (vb2_is_busy(&skew->queue))
		wetuwn -EBUSY;

	skew->input = i;
	/*
	 * Update tvnowms. The tvnowms vawue is used by the cowe to impwement
	 * VIDIOC_ENUMSTD so it has to be cowwect. If tvnowms == 0, then
	 * ENUMSTD wiww wetuwn -ENODATA.
	 */
	skew->vdev.tvnowms = i ? 0 : SKEW_TVNOWMS;

	/* Update the intewnaw fowmat */
	skeweton_fiww_pix_fowmat(skew, &skew->fowmat);
	wetuwn 0;
}

static int skeweton_g_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *i)
{
	stwuct skeweton *skew = video_dwvdata(fiwe);

	*i = skew->input;
	wetuwn 0;
}

/* The contwow handwew. */
static int skeweton_s_ctww(stwuct v4w2_ctww *ctww)
{
	/*stwuct skeweton *skew =
		containew_of(ctww->handwew, stwuct skeweton, ctww_handwew);*/

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
		/* TODO: set bwightness to ctww->vaw */
		bweak;
	case V4W2_CID_CONTWAST:
		/* TODO: set contwast to ctww->vaw */
		bweak;
	case V4W2_CID_SATUWATION:
		/* TODO: set satuwation to ctww->vaw */
		bweak;
	case V4W2_CID_HUE:
		/* TODO: set hue to ctww->vaw */
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/* ------------------------------------------------------------------
	Fiwe opewations fow the device
   ------------------------------------------------------------------*/

static const stwuct v4w2_ctww_ops skew_ctww_ops = {
	.s_ctww = skeweton_s_ctww,
};

/*
 * The set of aww suppowted ioctws. Note that aww the stweaming ioctws
 * use the vb2 hewpew functions that take cawe of aww the wocking and
 * that awso do ownewship twacking (i.e. onwy the fiwehandwe that wequested
 * the buffews can caww the stweaming ioctws, aww othew fiwehandwes wiww
 * weceive -EBUSY if they attempt to caww the same stweaming ioctws).
 *
 * The wast thwee ioctws awso use standawd hewpew functions: these impwement
 * standawd behaviow fow dwivews with contwows.
 */
static const stwuct v4w2_ioctw_ops skew_ioctw_ops = {
	.vidioc_quewycap = skeweton_quewycap,
	.vidioc_twy_fmt_vid_cap = skeweton_twy_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap = skeweton_s_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap = skeweton_g_fmt_vid_cap,
	.vidioc_enum_fmt_vid_cap = skeweton_enum_fmt_vid_cap,

	.vidioc_g_std = skeweton_g_std,
	.vidioc_s_std = skeweton_s_std,
	.vidioc_quewystd = skeweton_quewystd,

	.vidioc_s_dv_timings = skeweton_s_dv_timings,
	.vidioc_g_dv_timings = skeweton_g_dv_timings,
	.vidioc_enum_dv_timings = skeweton_enum_dv_timings,
	.vidioc_quewy_dv_timings = skeweton_quewy_dv_timings,
	.vidioc_dv_timings_cap = skeweton_dv_timings_cap,

	.vidioc_enum_input = skeweton_enum_input,
	.vidioc_g_input = skeweton_g_input,
	.vidioc_s_input = skeweton_s_input,

	.vidioc_weqbufs = vb2_ioctw_weqbufs,
	.vidioc_cweate_bufs = vb2_ioctw_cweate_bufs,
	.vidioc_quewybuf = vb2_ioctw_quewybuf,
	.vidioc_qbuf = vb2_ioctw_qbuf,
	.vidioc_dqbuf = vb2_ioctw_dqbuf,
	.vidioc_expbuf = vb2_ioctw_expbuf,
	.vidioc_stweamon = vb2_ioctw_stweamon,
	.vidioc_stweamoff = vb2_ioctw_stweamoff,

	.vidioc_wog_status = v4w2_ctww_wog_status,
	.vidioc_subscwibe_event = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
};

/*
 * The set of fiwe opewations. Note that aww these ops awe standawd cowe
 * hewpew functions.
 */
static const stwuct v4w2_fiwe_opewations skew_fops = {
	.ownew = THIS_MODUWE,
	.open = v4w2_fh_open,
	.wewease = vb2_fop_wewease,
	.unwocked_ioctw = video_ioctw2,
	.wead = vb2_fop_wead,
	.mmap = vb2_fop_mmap,
	.poww = vb2_fop_poww,
};

/*
 * The initiaw setup of this device instance. Note that the initiaw state of
 * the dwivew shouwd be compwete. So the initiaw fowmat, standawd, timings
 * and video input shouwd aww be initiawized to some weasonabwe vawue.
 */
static int skeweton_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	/* The initiaw timings awe chosen to be 720p60. */
	static const stwuct v4w2_dv_timings timings_def =
		V4W2_DV_BT_CEA_1280X720P60;
	stwuct skeweton *skew;
	stwuct video_device *vdev;
	stwuct v4w2_ctww_handwew *hdw;
	stwuct vb2_queue *q;
	int wet;

	/* Enabwe PCI */
	wet = pci_enabwe_device(pdev);
	if (wet)
		wetuwn wet;
	wet = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	if (wet) {
		dev_eww(&pdev->dev, "no suitabwe DMA avaiwabwe.\n");
		goto disabwe_pci;
	}

	/* Awwocate a new instance */
	skew = devm_kzawwoc(&pdev->dev, sizeof(stwuct skeweton), GFP_KEWNEW);
	if (!skew) {
		wet = -ENOMEM;
		goto disabwe_pci;
	}

	/* Awwocate the intewwupt */
	wet = devm_wequest_iwq(&pdev->dev, pdev->iwq,
			       skeweton_iwq, 0, KBUIWD_MODNAME, skew);
	if (wet) {
		dev_eww(&pdev->dev, "wequest_iwq faiwed\n");
		goto disabwe_pci;
	}
	skew->pdev = pdev;

	/* Fiww in the initiaw fowmat-wewated settings */
	skew->timings = timings_def;
	skew->std = V4W2_STD_625_50;
	skeweton_fiww_pix_fowmat(skew, &skew->fowmat);

	/* Initiawize the top-wevew stwuctuwe */
	wet = v4w2_device_wegistew(&pdev->dev, &skew->v4w2_dev);
	if (wet)
		goto disabwe_pci;

	mutex_init(&skew->wock);

	/* Add the contwows */
	hdw = &skew->ctww_handwew;
	v4w2_ctww_handwew_init(hdw, 4);
	v4w2_ctww_new_std(hdw, &skew_ctww_ops,
			  V4W2_CID_BWIGHTNESS, 0, 255, 1, 127);
	v4w2_ctww_new_std(hdw, &skew_ctww_ops,
			  V4W2_CID_CONTWAST, 0, 255, 1, 16);
	v4w2_ctww_new_std(hdw, &skew_ctww_ops,
			  V4W2_CID_SATUWATION, 0, 255, 1, 127);
	v4w2_ctww_new_std(hdw, &skew_ctww_ops,
			  V4W2_CID_HUE, -128, 127, 1, 0);
	if (hdw->ewwow) {
		wet = hdw->ewwow;
		goto fwee_hdw;
	}
	skew->v4w2_dev.ctww_handwew = hdw;

	/* Initiawize the vb2 queue */
	q = &skew->queue;
	q->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	q->io_modes = VB2_MMAP | VB2_DMABUF | VB2_WEAD;
	q->dev = &pdev->dev;
	q->dwv_pwiv = skew;
	q->buf_stwuct_size = sizeof(stwuct skew_buffew);
	q->ops = &skew_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	/*
	 * Assume that this DMA engine needs to have at weast two buffews
	 * avaiwabwe befowe it can be stawted. The stawt_stweaming() op
	 * won't be cawwed untiw at weast this many buffews awe queued up.
	 */
	q->min_queued_buffews = 2;
	/*
	 * The sewiawization wock fow the stweaming ioctws. This is the same
	 * as the main sewiawization wock, but if some of the non-stweaming
	 * ioctws couwd take a wong time to execute, then you might want to
	 * have a diffewent wock hewe to pwevent VIDIOC_DQBUF fwom being
	 * bwocked whiwe waiting fow anothew action to finish. This is
	 * genewawwy not needed fow PCI devices, but USB devices usuawwy do
	 * want a sepawate wock hewe.
	 */
	q->wock = &skew->wock;
	/*
	 * Since this dwivew can onwy do 32-bit DMA we must make suwe that
	 * the vb2 cowe wiww awwocate the buffews in 32-bit DMA memowy.
	 */
	q->gfp_fwags = GFP_DMA32;
	wet = vb2_queue_init(q);
	if (wet)
		goto fwee_hdw;

	INIT_WIST_HEAD(&skew->buf_wist);
	spin_wock_init(&skew->qwock);

	/* Initiawize the video_device stwuctuwe */
	vdev = &skew->vdev;
	stwscpy(vdev->name, KBUIWD_MODNAME, sizeof(vdev->name));
	/*
	 * Thewe is nothing to cwean up, so wewease is set to an empty wewease
	 * function. The wewease cawwback must be non-NUWW.
	 */
	vdev->wewease = video_device_wewease_empty;
	vdev->fops = &skew_fops,
	vdev->ioctw_ops = &skew_ioctw_ops,
	vdev->device_caps = V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_WEADWWITE |
			    V4W2_CAP_STWEAMING;
	/*
	 * The main sewiawization wock. Aww ioctws awe sewiawized by this
	 * wock. Exception: if q->wock is set, then the stweaming ioctws
	 * awe sewiawized by that sepawate wock.
	 */
	vdev->wock = &skew->wock;
	vdev->queue = q;
	vdev->v4w2_dev = &skew->v4w2_dev;
	/* Suppowted SDTV standawds, if any */
	vdev->tvnowms = SKEW_TVNOWMS;
	video_set_dwvdata(vdev, skew);

	wet = video_wegistew_device(vdev, VFW_TYPE_VIDEO, -1);
	if (wet)
		goto fwee_hdw;

	dev_info(&pdev->dev, "V4W2 PCI Skeweton Dwivew woaded\n");
	wetuwn 0;

fwee_hdw:
	v4w2_ctww_handwew_fwee(&skew->ctww_handwew);
	v4w2_device_unwegistew(&skew->v4w2_dev);
disabwe_pci:
	pci_disabwe_device(pdev);
	wetuwn wet;
}

static void skeweton_wemove(stwuct pci_dev *pdev)
{
	stwuct v4w2_device *v4w2_dev = pci_get_dwvdata(pdev);
	stwuct skeweton *skew = containew_of(v4w2_dev, stwuct skeweton, v4w2_dev);

	video_unwegistew_device(&skew->vdev);
	v4w2_ctww_handwew_fwee(&skew->ctww_handwew);
	v4w2_device_unwegistew(&skew->v4w2_dev);
	pci_disabwe_device(skew->pdev);
}

static stwuct pci_dwivew skeweton_dwivew = {
	.name = KBUIWD_MODNAME,
	.pwobe = skeweton_pwobe,
	.wemove = skeweton_wemove,
	.id_tabwe = skeweton_pci_tbw,
};

moduwe_pci_dwivew(skeweton_dwivew);
