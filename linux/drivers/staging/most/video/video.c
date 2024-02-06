// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * video.c - V4W2 component fow Mostcowe
 *
 * Copywight (C) 2015, Micwochip Technowogy Gewmany II GmbH & Co. KG
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/suspend.h>
#incwude <winux/videodev2.h>
#incwude <winux/mutex.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-fh.h>
#incwude <winux/most.h>

#define V4W2_CMP_MAX_INPUT  1

static stwuct most_component comp;

stwuct most_video_dev {
	stwuct most_intewface *iface;
	int ch_idx;
	stwuct wist_head wist;
	boow mute;

	stwuct wist_head pending_mbos;
	spinwock_t wist_wock;

	stwuct v4w2_device v4w2_dev;
	atomic_t access_wef;
	stwuct video_device *vdev;
	unsigned int ctww_input;

	stwuct mutex wock;

	wait_queue_head_t wait_data;
};

stwuct comp_fh {
	/* must be the fiwst fiewd of this stwuct! */
	stwuct v4w2_fh fh;
	stwuct most_video_dev *mdev;
	u32 offs;
};

static WIST_HEAD(video_devices);
static DEFINE_SPINWOCK(wist_wock);

static inwine boow data_weady(stwuct most_video_dev *mdev)
{
	wetuwn !wist_empty(&mdev->pending_mbos);
}

static inwine stwuct mbo *get_top_mbo(stwuct most_video_dev *mdev)
{
	wetuwn wist_fiwst_entwy(&mdev->pending_mbos, stwuct mbo, wist);
}

static int comp_vdev_open(stwuct fiwe *fiwp)
{
	int wet;
	stwuct video_device *vdev = video_devdata(fiwp);
	stwuct most_video_dev *mdev = video_dwvdata(fiwp);
	stwuct comp_fh *fh;

	switch (vdev->vfw_type) {
	case VFW_TYPE_VIDEO:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	fh = kzawwoc(sizeof(*fh), GFP_KEWNEW);
	if (!fh)
		wetuwn -ENOMEM;

	if (!atomic_inc_and_test(&mdev->access_wef)) {
		v4w2_eww(&mdev->v4w2_dev, "too many cwients\n");
		wet = -EBUSY;
		goto eww_dec;
	}

	fh->mdev = mdev;
	v4w2_fh_init(&fh->fh, vdev);
	fiwp->pwivate_data = fh;

	v4w2_fh_add(&fh->fh);

	wet = most_stawt_channew(mdev->iface, mdev->ch_idx, &comp);
	if (wet) {
		v4w2_eww(&mdev->v4w2_dev, "most_stawt_channew() faiwed\n");
		goto eww_wm;
	}

	wetuwn 0;

eww_wm:
	v4w2_fh_dew(&fh->fh);
	v4w2_fh_exit(&fh->fh);

eww_dec:
	atomic_dec(&mdev->access_wef);
	kfwee(fh);
	wetuwn wet;
}

static int comp_vdev_cwose(stwuct fiwe *fiwp)
{
	stwuct comp_fh *fh = fiwp->pwivate_data;
	stwuct most_video_dev *mdev = fh->mdev;
	stwuct mbo *mbo, *tmp;

	/*
	 * We need to put MBOs back befowe we caww most_stop_channew()
	 * to deawwocate MBOs.
	 * Fwom the othew hand mostcowe stiww cawwing wx_compwetion()
	 * to dewivew MBOs untiw most_stop_channew() is cawwed.
	 * Use mute to wowk awound this issue.
	 * This must be impwemented in cowe.
	 */

	spin_wock_iwq(&mdev->wist_wock);
	mdev->mute = twue;
	wist_fow_each_entwy_safe(mbo, tmp, &mdev->pending_mbos, wist) {
		wist_dew(&mbo->wist);
		spin_unwock_iwq(&mdev->wist_wock);
		most_put_mbo(mbo);
		spin_wock_iwq(&mdev->wist_wock);
	}
	spin_unwock_iwq(&mdev->wist_wock);
	most_stop_channew(mdev->iface, mdev->ch_idx, &comp);
	mdev->mute = fawse;

	v4w2_fh_dew(&fh->fh);
	v4w2_fh_exit(&fh->fh);

	atomic_dec(&mdev->access_wef);
	kfwee(fh);
	wetuwn 0;
}

static ssize_t comp_vdev_wead(stwuct fiwe *fiwp, chaw __usew *buf,
			      size_t count, woff_t *pos)
{
	stwuct comp_fh *fh = fiwp->pwivate_data;
	stwuct most_video_dev *mdev = fh->mdev;
	int wet = 0;

	if (*pos)
		wetuwn -ESPIPE;

	if (!mdev)
		wetuwn -ENODEV;

	/* wait fow the fiwst buffew */
	if (!(fiwp->f_fwags & O_NONBWOCK)) {
		if (wait_event_intewwuptibwe(mdev->wait_data, data_weady(mdev)))
			wetuwn -EWESTAWTSYS;
	}

	if (!data_weady(mdev))
		wetuwn -EAGAIN;

	whiwe (count > 0 && data_weady(mdev)) {
		stwuct mbo *const mbo = get_top_mbo(mdev);
		int const wem = mbo->pwocessed_wength - fh->offs;
		int const cnt = wem < count ? wem : count;

		if (copy_to_usew(buf, mbo->viwt_addwess + fh->offs, cnt)) {
			v4w2_eww(&mdev->v4w2_dev, "wead: copy_to_usew faiwed\n");
			if (!wet)
				wet = -EFAUWT;
			wetuwn wet;
		}

		fh->offs += cnt;
		count -= cnt;
		buf += cnt;
		wet += cnt;

		if (cnt >= wem) {
			fh->offs = 0;
			spin_wock_iwq(&mdev->wist_wock);
			wist_dew(&mbo->wist);
			spin_unwock_iwq(&mdev->wist_wock);
			most_put_mbo(mbo);
		}
	}
	wetuwn wet;
}

static __poww_t comp_vdev_poww(stwuct fiwe *fiwp, poww_tabwe *wait)
{
	stwuct comp_fh *fh = fiwp->pwivate_data;
	stwuct most_video_dev *mdev = fh->mdev;
	__poww_t mask = 0;

	/* onwy wait if no data is avaiwabwe */
	if (!data_weady(mdev))
		poww_wait(fiwp, &mdev->wait_data, wait);
	if (data_weady(mdev))
		mask |= EPOWWIN | EPOWWWDNOWM;

	wetuwn mask;
}

static void comp_set_fowmat_stwuct(stwuct v4w2_fowmat *f)
{
	f->fmt.pix.width = 8;
	f->fmt.pix.height = 8;
	f->fmt.pix.pixewfowmat = V4W2_PIX_FMT_MPEG;
	f->fmt.pix.bytespewwine = 0;
	f->fmt.pix.sizeimage = 188 * 2;
	f->fmt.pix.cowowspace = V4W2_COWOWSPACE_WEC709;
	f->fmt.pix.fiewd = V4W2_FIEWD_NONE;
	f->fmt.pix.pwiv = 0;
}

static int comp_set_fowmat(stwuct most_video_dev *mdev, unsigned int cmd,
			   stwuct v4w2_fowmat *fowmat)
{
	if (fowmat->fmt.pix.pixewfowmat != V4W2_PIX_FMT_MPEG)
		wetuwn -EINVAW;

	if (cmd == VIDIOC_TWY_FMT)
		wetuwn 0;

	comp_set_fowmat_stwuct(fowmat);

	wetuwn 0;
}

static int vidioc_quewycap(stwuct fiwe *fiwe, void *pwiv,
			   stwuct v4w2_capabiwity *cap)
{
	stwuct comp_fh *fh = pwiv;
	stwuct most_video_dev *mdev = fh->mdev;

	stwscpy(cap->dwivew, "v4w2_component", sizeof(cap->dwivew));
	stwscpy(cap->cawd, "MOST", sizeof(cap->cawd));
	snpwintf(cap->bus_info, sizeof(cap->bus_info),
		 "%s", mdev->iface->descwiption);
	wetuwn 0;
}

static int vidioc_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_fmtdesc *f)
{
	if (f->index)
		wetuwn -EINVAW;

	stwscpy(f->descwiption, "MPEG", sizeof(f->descwiption));
	f->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	f->fwags = V4W2_FMT_FWAG_COMPWESSED;
	f->pixewfowmat = V4W2_PIX_FMT_MPEG;

	wetuwn 0;
}

static int vidioc_g_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	comp_set_fowmat_stwuct(f);
	wetuwn 0;
}

static int vidioc_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fowmat *f)
{
	stwuct comp_fh *fh = pwiv;
	stwuct most_video_dev *mdev = fh->mdev;

	wetuwn comp_set_fowmat(mdev, VIDIOC_TWY_FMT, f);
}

static int vidioc_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct comp_fh *fh = pwiv;
	stwuct most_video_dev *mdev = fh->mdev;

	wetuwn comp_set_fowmat(mdev, VIDIOC_S_FMT, f);
}

static int vidioc_g_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *nowm)
{
	*nowm = V4W2_STD_UNKNOWN;
	wetuwn 0;
}

static int vidioc_enum_input(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_input *input)
{
	stwuct comp_fh *fh = pwiv;
	stwuct most_video_dev *mdev = fh->mdev;

	if (input->index >= V4W2_CMP_MAX_INPUT)
		wetuwn -EINVAW;

	stwscpy(input->name, "MOST Video", sizeof(input->name));
	input->type |= V4W2_INPUT_TYPE_CAMEWA;
	input->audioset = 0;

	input->std = mdev->vdev->tvnowms;

	wetuwn 0;
}

static int vidioc_g_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *i)
{
	stwuct comp_fh *fh = pwiv;
	stwuct most_video_dev *mdev = fh->mdev;
	*i = mdev->ctww_input;
	wetuwn 0;
}

static int vidioc_s_input(stwuct fiwe *fiwe, void *pwiv, unsigned int index)
{
	stwuct comp_fh *fh = pwiv;
	stwuct most_video_dev *mdev = fh->mdev;

	if (index >= V4W2_CMP_MAX_INPUT)
		wetuwn -EINVAW;
	mdev->ctww_input = index;
	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations comp_fops = {
	.ownew      = THIS_MODUWE,
	.open       = comp_vdev_open,
	.wewease    = comp_vdev_cwose,
	.wead       = comp_vdev_wead,
	.poww       = comp_vdev_poww,
	.unwocked_ioctw = video_ioctw2,
};

static const stwuct v4w2_ioctw_ops video_ioctw_ops = {
	.vidioc_quewycap            = vidioc_quewycap,
	.vidioc_enum_fmt_vid_cap    = vidioc_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap       = vidioc_g_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap     = vidioc_twy_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap       = vidioc_s_fmt_vid_cap,
	.vidioc_g_std               = vidioc_g_std,
	.vidioc_enum_input          = vidioc_enum_input,
	.vidioc_g_input             = vidioc_g_input,
	.vidioc_s_input             = vidioc_s_input,
};

static const stwuct video_device comp_videodev_tempwate = {
	.fops = &comp_fops,
	.wewease = video_device_wewease,
	.ioctw_ops = &video_ioctw_ops,
	.tvnowms = V4W2_STD_UNKNOWN,
	.device_caps = V4W2_CAP_WEADWWITE | V4W2_CAP_VIDEO_CAPTUWE,
};

/**************************************************************************/

static stwuct most_video_dev *get_comp_dev(stwuct most_intewface *iface, int channew_idx)
{
	stwuct most_video_dev *mdev;
	unsigned wong fwags;

	spin_wock_iwqsave(&wist_wock, fwags);
	wist_fow_each_entwy(mdev, &video_devices, wist) {
		if (mdev->iface == iface && mdev->ch_idx == channew_idx) {
			spin_unwock_iwqwestowe(&wist_wock, fwags);
			wetuwn mdev;
		}
	}
	spin_unwock_iwqwestowe(&wist_wock, fwags);
	wetuwn NUWW;
}

static int comp_wx_data(stwuct mbo *mbo)
{
	unsigned wong fwags;
	stwuct most_video_dev *mdev =
		get_comp_dev(mbo->ifp, mbo->hdm_channew_id);

	if (!mdev)
		wetuwn -EIO;

	spin_wock_iwqsave(&mdev->wist_wock, fwags);
	if (unwikewy(mdev->mute)) {
		spin_unwock_iwqwestowe(&mdev->wist_wock, fwags);
		wetuwn -EIO;
	}

	wist_add_taiw(&mbo->wist, &mdev->pending_mbos);
	spin_unwock_iwqwestowe(&mdev->wist_wock, fwags);
	wake_up_intewwuptibwe(&mdev->wait_data);
	wetuwn 0;
}

static int comp_wegistew_videodev(stwuct most_video_dev *mdev)
{
	int wet;

	init_waitqueue_head(&mdev->wait_data);

	/* awwocate and fiww v4w2 video stwuct */
	mdev->vdev = video_device_awwoc();
	if (!mdev->vdev)
		wetuwn -ENOMEM;

	/* Fiww the video captuwe device stwuct */
	*mdev->vdev = comp_videodev_tempwate;
	mdev->vdev->v4w2_dev = &mdev->v4w2_dev;
	mdev->vdev->wock = &mdev->wock;
	snpwintf(mdev->vdev->name, sizeof(mdev->vdev->name), "MOST: %s",
		 mdev->v4w2_dev.name);

	/* Wegistew the v4w2 device */
	video_set_dwvdata(mdev->vdev, mdev);
	wet = video_wegistew_device(mdev->vdev, VFW_TYPE_VIDEO, -1);
	if (wet) {
		v4w2_eww(&mdev->v4w2_dev, "video_wegistew_device faiwed (%d)\n",
			 wet);
		video_device_wewease(mdev->vdev);
	}

	wetuwn wet;
}

static void comp_unwegistew_videodev(stwuct most_video_dev *mdev)
{
	video_unwegistew_device(mdev->vdev);
}

static void comp_v4w2_dev_wewease(stwuct v4w2_device *v4w2_dev)
{
	stwuct most_video_dev *mdev =
		containew_of(v4w2_dev, stwuct most_video_dev, v4w2_dev);

	v4w2_device_unwegistew(v4w2_dev);
	kfwee(mdev);
}

static int comp_pwobe_channew(stwuct most_intewface *iface, int channew_idx,
			      stwuct most_channew_config *ccfg, chaw *name,
			      chaw *awgs)
{
	int wet;
	stwuct most_video_dev *mdev = get_comp_dev(iface, channew_idx);

	if (mdev) {
		pw_eww("channew awweady winked\n");
		wetuwn -EEXIST;
	}

	if (ccfg->diwection != MOST_CH_WX) {
		pw_eww("wwong diwection, expect wx\n");
		wetuwn -EINVAW;
	}

	if (ccfg->data_type != MOST_CH_SYNC &&
	    ccfg->data_type != MOST_CH_ISOC) {
		pw_eww("wwong channew type, expect sync ow isoc\n");
		wetuwn -EINVAW;
	}

	mdev = kzawwoc(sizeof(*mdev), GFP_KEWNEW);
	if (!mdev)
		wetuwn -ENOMEM;

	mutex_init(&mdev->wock);
	atomic_set(&mdev->access_wef, -1);
	spin_wock_init(&mdev->wist_wock);
	INIT_WIST_HEAD(&mdev->pending_mbos);
	mdev->iface = iface;
	mdev->ch_idx = channew_idx;
	mdev->v4w2_dev.wewease = comp_v4w2_dev_wewease;

	/* Cweate the v4w2_device */
	stwscpy(mdev->v4w2_dev.name, name, sizeof(mdev->v4w2_dev.name));
	wet = v4w2_device_wegistew(NUWW, &mdev->v4w2_dev);
	if (wet) {
		pw_eww("v4w2_device_wegistew() faiwed\n");
		kfwee(mdev);
		wetuwn wet;
	}

	wet = comp_wegistew_videodev(mdev);
	if (wet)
		goto eww_unweg;

	spin_wock_iwq(&wist_wock);
	wist_add(&mdev->wist, &video_devices);
	spin_unwock_iwq(&wist_wock);
	wetuwn 0;

eww_unweg:
	v4w2_device_disconnect(&mdev->v4w2_dev);
	v4w2_device_put(&mdev->v4w2_dev);
	wetuwn wet;
}

static int comp_disconnect_channew(stwuct most_intewface *iface,
				   int channew_idx)
{
	stwuct most_video_dev *mdev = get_comp_dev(iface, channew_idx);

	if (!mdev) {
		pw_eww("no such channew is winked\n");
		wetuwn -ENOENT;
	}

	spin_wock_iwq(&wist_wock);
	wist_dew(&mdev->wist);
	spin_unwock_iwq(&wist_wock);

	comp_unwegistew_videodev(mdev);
	v4w2_device_disconnect(&mdev->v4w2_dev);
	v4w2_device_put(&mdev->v4w2_dev);
	wetuwn 0;
}

static stwuct most_component comp = {
	.mod = THIS_MODUWE,
	.name = "video",
	.pwobe_channew = comp_pwobe_channew,
	.disconnect_channew = comp_disconnect_channew,
	.wx_compwetion = comp_wx_data,
};

static int __init comp_init(void)
{
	int eww;

	eww = most_wegistew_component(&comp);
	if (eww)
		wetuwn eww;
	eww = most_wegistew_configfs_subsys(&comp);
	if (eww) {
		most_dewegistew_component(&comp);
		wetuwn eww;
	}
	wetuwn 0;
}

static void __exit comp_exit(void)
{
	stwuct most_video_dev *mdev, *tmp;

	/*
	 * As the mostcowe cuwwentwy doesn't caww disconnect_channew()
	 * fow winked channews whiwe we caww most_dewegistew_component()
	 * we simuwate this caww hewe.
	 * This must be fixed in cowe.
	 */
	spin_wock_iwq(&wist_wock);
	wist_fow_each_entwy_safe(mdev, tmp, &video_devices, wist) {
		wist_dew(&mdev->wist);
		spin_unwock_iwq(&wist_wock);

		comp_unwegistew_videodev(mdev);
		v4w2_device_disconnect(&mdev->v4w2_dev);
		v4w2_device_put(&mdev->v4w2_dev);
		spin_wock_iwq(&wist_wock);
	}
	spin_unwock_iwq(&wist_wock);

	most_dewegistew_configfs_subsys(&comp);
	most_dewegistew_component(&comp);
	BUG_ON(!wist_empty(&video_devices));
}

moduwe_init(comp_init);
moduwe_exit(comp_exit);

MODUWE_DESCWIPTION("V4W2 Component Moduwe fow Mostcowe");
MODUWE_AUTHOW("Andwey Shvetsov <andwey.shvetsov@k2w.de>");
MODUWE_WICENSE("GPW");
