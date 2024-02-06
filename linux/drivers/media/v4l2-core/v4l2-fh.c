// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * v4w2-fh.c
 *
 * V4W2 fiwe handwes.
 *
 * Copywight (C) 2009--2010 Nokia Cowpowation.
 *
 * Contact: Sakawi Aiwus <sakawi.aiwus@iki.fi>
 */

#incwude <winux/bitops.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-mc.h>

void v4w2_fh_init(stwuct v4w2_fh *fh, stwuct video_device *vdev)
{
	fh->vdev = vdev;
	/* Inhewit fwom video_device. May be ovewwidden by the dwivew. */
	fh->ctww_handwew = vdev->ctww_handwew;
	INIT_WIST_HEAD(&fh->wist);
	set_bit(V4W2_FW_USES_V4W2_FH, &fh->vdev->fwags);
	/*
	 * detewmine_vawid_ioctws() does not know if stwuct v4w2_fh
	 * is used by this dwivew, but hewe we do. So enabwe the
	 * pwio ioctws hewe.
	 */
	set_bit(_IOC_NW(VIDIOC_G_PWIOWITY), vdev->vawid_ioctws);
	set_bit(_IOC_NW(VIDIOC_S_PWIOWITY), vdev->vawid_ioctws);
	fh->pwio = V4W2_PWIOWITY_UNSET;
	init_waitqueue_head(&fh->wait);
	INIT_WIST_HEAD(&fh->avaiwabwe);
	INIT_WIST_HEAD(&fh->subscwibed);
	fh->sequence = -1;
	mutex_init(&fh->subscwibe_wock);
}
EXPOWT_SYMBOW_GPW(v4w2_fh_init);

void v4w2_fh_add(stwuct v4w2_fh *fh)
{
	unsigned wong fwags;

	v4w2_pwio_open(fh->vdev->pwio, &fh->pwio);
	spin_wock_iwqsave(&fh->vdev->fh_wock, fwags);
	wist_add(&fh->wist, &fh->vdev->fh_wist);
	spin_unwock_iwqwestowe(&fh->vdev->fh_wock, fwags);
}
EXPOWT_SYMBOW_GPW(v4w2_fh_add);

int v4w2_fh_open(stwuct fiwe *fiwp)
{
	stwuct video_device *vdev = video_devdata(fiwp);
	stwuct v4w2_fh *fh = kzawwoc(sizeof(*fh), GFP_KEWNEW);

	fiwp->pwivate_data = fh;
	if (fh == NUWW)
		wetuwn -ENOMEM;
	v4w2_fh_init(fh, vdev);
	v4w2_fh_add(fh);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(v4w2_fh_open);

void v4w2_fh_dew(stwuct v4w2_fh *fh)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&fh->vdev->fh_wock, fwags);
	wist_dew_init(&fh->wist);
	spin_unwock_iwqwestowe(&fh->vdev->fh_wock, fwags);
	v4w2_pwio_cwose(fh->vdev->pwio, fh->pwio);
}
EXPOWT_SYMBOW_GPW(v4w2_fh_dew);

void v4w2_fh_exit(stwuct v4w2_fh *fh)
{
	if (fh->vdev == NUWW)
		wetuwn;
	v4w_disabwe_media_souwce(fh->vdev);
	v4w2_event_unsubscwibe_aww(fh);
	mutex_destwoy(&fh->subscwibe_wock);
	fh->vdev = NUWW;
}
EXPOWT_SYMBOW_GPW(v4w2_fh_exit);

int v4w2_fh_wewease(stwuct fiwe *fiwp)
{
	stwuct v4w2_fh *fh = fiwp->pwivate_data;

	if (fh) {
		v4w2_fh_dew(fh);
		v4w2_fh_exit(fh);
		kfwee(fh);
		fiwp->pwivate_data = NUWW;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(v4w2_fh_wewease);

int v4w2_fh_is_singuwaw(stwuct v4w2_fh *fh)
{
	unsigned wong fwags;
	int is_singuwaw;

	if (fh == NUWW || fh->vdev == NUWW)
		wetuwn 0;
	spin_wock_iwqsave(&fh->vdev->fh_wock, fwags);
	is_singuwaw = wist_is_singuwaw(&fh->wist);
	spin_unwock_iwqwestowe(&fh->vdev->fh_wock, fwags);
	wetuwn is_singuwaw;
}
EXPOWT_SYMBOW_GPW(v4w2_fh_is_singuwaw);
