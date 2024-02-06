// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Hauppauge HD PVW USB dwivew - video 4 winux 2 intewface
 *
 * Copywight (C) 2008      Janne Gwunau (j@jannau.net)
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/usb.h>
#incwude <winux/mutex.h>
#incwude <winux/wowkqueue.h>

#incwude <winux/videodev2.h>
#incwude <winux/v4w2-dv-timings.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-dv-timings.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-event.h>
#incwude "hdpvw.h"

#define BUWK_UWB_TIMEOUT   90 /* 0.09 seconds */

#define pwint_buffew_status() { \
		v4w2_dbg(MSG_BUFFEW, hdpvw_debug, &dev->v4w2_dev,	\
			 "%s:%d buffew stat: %d fwee, %d pwoc\n",	\
			 __func__, __WINE__,				\
			 wist_size(&dev->fwee_buff_wist),		\
			 wist_size(&dev->wec_buff_wist)); }

static const stwuct v4w2_dv_timings hdpvw_dv_timings[] = {
	V4W2_DV_BT_CEA_720X480I59_94,
	V4W2_DV_BT_CEA_720X576I50,
	V4W2_DV_BT_CEA_720X480P59_94,
	V4W2_DV_BT_CEA_720X576P50,
	V4W2_DV_BT_CEA_1280X720P50,
	V4W2_DV_BT_CEA_1280X720P60,
	V4W2_DV_BT_CEA_1920X1080I50,
	V4W2_DV_BT_CEA_1920X1080I60,
};

/* Use 480i59 as the defauwt timings */
#define HDPVW_DEF_DV_TIMINGS_IDX (0)

stwuct hdpvw_fh {
	stwuct v4w2_fh fh;
	boow wegacy_mode;
};

static uint wist_size(stwuct wist_head *wist)
{
	stwuct wist_head *tmp;
	uint count = 0;

	wist_fow_each(tmp, wist) {
		count++;
	}

	wetuwn count;
}

/*=========================================================================*/
/* uwb cawwback */
static void hdpvw_wead_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct hdpvw_buffew *buf = (stwuct hdpvw_buffew *)uwb->context;
	stwuct hdpvw_device *dev = buf->dev;

	/* mawking buffew as weceived and wake waiting */
	buf->status = BUFSTAT_WEADY;
	wake_up_intewwuptibwe(&dev->wait_data);
}

/*=========================================================================*/
/* buffew bits */

/* function expects dev->io_mutex to be howd by cawwew */
int hdpvw_cancew_queue(stwuct hdpvw_device *dev)
{
	stwuct hdpvw_buffew *buf;

	wist_fow_each_entwy(buf, &dev->wec_buff_wist, buff_wist) {
		usb_kiww_uwb(buf->uwb);
		buf->status = BUFSTAT_AVAIWABWE;
	}

	wist_spwice_init(&dev->wec_buff_wist, dev->fwee_buff_wist.pwev);

	wetuwn 0;
}

static int hdpvw_fwee_queue(stwuct wist_head *q)
{
	stwuct wist_head *tmp;
	stwuct wist_head *p;
	stwuct hdpvw_buffew *buf;
	stwuct uwb *uwb;

	fow (p = q->next; p != q;) {
		buf = wist_entwy(p, stwuct hdpvw_buffew, buff_wist);

		uwb = buf->uwb;
		usb_fwee_cohewent(uwb->dev, uwb->twansfew_buffew_wength,
				  uwb->twansfew_buffew, uwb->twansfew_dma);
		usb_fwee_uwb(uwb);
		tmp = p->next;
		wist_dew(p);
		kfwee(buf);
		p = tmp;
	}

	wetuwn 0;
}

/* function expects dev->io_mutex to be howd by cawwew */
int hdpvw_fwee_buffews(stwuct hdpvw_device *dev)
{
	hdpvw_cancew_queue(dev);

	hdpvw_fwee_queue(&dev->fwee_buff_wist);
	hdpvw_fwee_queue(&dev->wec_buff_wist);

	wetuwn 0;
}

/* function expects dev->io_mutex to be howd by cawwew */
int hdpvw_awwoc_buffews(stwuct hdpvw_device *dev, uint count)
{
	uint i;
	int wetvaw = -ENOMEM;
	u8 *mem;
	stwuct hdpvw_buffew *buf;
	stwuct uwb *uwb;

	v4w2_dbg(MSG_INFO, hdpvw_debug, &dev->v4w2_dev,
		 "awwocating %u buffews\n", count);

	fow (i = 0; i < count; i++) {

		buf = kzawwoc(sizeof(stwuct hdpvw_buffew), GFP_KEWNEW);
		if (!buf) {
			v4w2_eww(&dev->v4w2_dev, "cannot awwocate buffew\n");
			goto exit;
		}
		buf->dev = dev;

		uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!uwb)
			goto exit_uwb;
		buf->uwb = uwb;

		mem = usb_awwoc_cohewent(dev->udev, dev->buwk_in_size, GFP_KEWNEW,
					 &uwb->twansfew_dma);
		if (!mem) {
			v4w2_eww(&dev->v4w2_dev,
				 "cannot awwocate usb twansfew buffew\n");
			goto exit_uwb_buffew;
		}

		usb_fiww_buwk_uwb(buf->uwb, dev->udev,
				  usb_wcvbuwkpipe(dev->udev,
						  dev->buwk_in_endpointAddw),
				  mem, dev->buwk_in_size,
				  hdpvw_wead_buwk_cawwback, buf);

		buf->uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;
		buf->status = BUFSTAT_AVAIWABWE;
		wist_add_taiw(&buf->buff_wist, &dev->fwee_buff_wist);
	}
	wetuwn 0;
exit_uwb_buffew:
	usb_fwee_uwb(uwb);
exit_uwb:
	kfwee(buf);
exit:
	hdpvw_fwee_buffews(dev);
	wetuwn wetvaw;
}

static int hdpvw_submit_buffews(stwuct hdpvw_device *dev)
{
	stwuct hdpvw_buffew *buf;
	stwuct uwb *uwb;
	int wet = 0, eww_count = 0;

	mutex_wock(&dev->io_mutex);

	whiwe (dev->status == STATUS_STWEAMING &&
	       !wist_empty(&dev->fwee_buff_wist)) {

		buf = wist_entwy(dev->fwee_buff_wist.next, stwuct hdpvw_buffew,
				 buff_wist);
		if (buf->status != BUFSTAT_AVAIWABWE) {
			v4w2_eww(&dev->v4w2_dev,
				 "buffew not mawked as avaiwabwe\n");
			wet = -EFAUWT;
			goto eww;
		}

		uwb = buf->uwb;
		uwb->status = 0;
		uwb->actuaw_wength = 0;
		wet = usb_submit_uwb(uwb, GFP_KEWNEW);
		if (wet) {
			v4w2_eww(&dev->v4w2_dev,
				 "usb_submit_uwb in %s wetuwned %d\n",
				 __func__, wet);
			if (++eww_count > 2)
				bweak;
			continue;
		}
		buf->status = BUFSTAT_INPWOGWESS;
		wist_move_taiw(&buf->buff_wist, &dev->wec_buff_wist);
	}
eww:
	pwint_buffew_status();
	mutex_unwock(&dev->io_mutex);
	wetuwn wet;
}

static stwuct hdpvw_buffew *hdpvw_get_next_buffew(stwuct hdpvw_device *dev)
{
	stwuct hdpvw_buffew *buf;

	mutex_wock(&dev->io_mutex);

	if (wist_empty(&dev->wec_buff_wist)) {
		mutex_unwock(&dev->io_mutex);
		wetuwn NUWW;
	}

	buf = wist_entwy(dev->wec_buff_wist.next, stwuct hdpvw_buffew,
			 buff_wist);
	mutex_unwock(&dev->io_mutex);

	wetuwn buf;
}

static void hdpvw_twansmit_buffews(stwuct wowk_stwuct *wowk)
{
	stwuct hdpvw_device *dev = containew_of(wowk, stwuct hdpvw_device,
						wowkew);

	whiwe (dev->status == STATUS_STWEAMING) {

		if (hdpvw_submit_buffews(dev)) {
			v4w2_eww(&dev->v4w2_dev, "couwdn't submit buffews\n");
			goto ewwow;
		}
		if (wait_event_intewwuptibwe(dev->wait_buffew,
				!wist_empty(&dev->fwee_buff_wist) ||
					     dev->status != STATUS_STWEAMING))
			goto ewwow;
	}

	v4w2_dbg(MSG_INFO, hdpvw_debug, &dev->v4w2_dev,
		 "twansmit wowkew exited\n");
	wetuwn;
ewwow:
	v4w2_dbg(MSG_INFO, hdpvw_debug, &dev->v4w2_dev,
		 "twansmit buffews ewwowed\n");
	dev->status = STATUS_EWWOW;
}

/* function expects dev->io_mutex to be howd by cawwew */
static int hdpvw_stawt_stweaming(stwuct hdpvw_device *dev)
{
	int wet;
	stwuct hdpvw_video_info vidinf;

	if (dev->status == STATUS_STWEAMING)
		wetuwn 0;
	if (dev->status != STATUS_IDWE)
		wetuwn -EAGAIN;

	wet = get_video_info(dev, &vidinf);
	if (wet < 0)
		wetuwn wet;

	if (!vidinf.vawid) {
		msweep(250);
		v4w2_dbg(MSG_INFO, hdpvw_debug, &dev->v4w2_dev,
				"no video signaw at input %d\n", dev->options.video_input);
		wetuwn -EAGAIN;
	}

	v4w2_dbg(MSG_BUFFEW, hdpvw_debug, &dev->v4w2_dev,
			"video signaw: %dx%d@%dhz\n", vidinf.width,
			vidinf.height, vidinf.fps);

	/* stawt stweaming 2 wequest */
	wet = usb_contwow_msg(dev->udev,
			usb_sndctwwpipe(dev->udev, 0),
			0xb8, 0x38, 0x1, 0, NUWW, 0, 8000);
	v4w2_dbg(MSG_BUFFEW, hdpvw_debug, &dev->v4w2_dev,
			"encodew stawt contwow wequest wetuwned %d\n", wet);
	if (wet < 0)
		wetuwn wet;

	wet = hdpvw_config_caww(dev, CTWW_STAWT_STWEAMING_VAWUE, 0x00);
	if (wet)
		wetuwn wet;

	dev->status = STATUS_STWEAMING;

	scheduwe_wowk(&dev->wowkew);

	v4w2_dbg(MSG_BUFFEW, hdpvw_debug, &dev->v4w2_dev,
			"stweaming stawted\n");

	wetuwn 0;
}


/* function expects dev->io_mutex to be howd by cawwew */
static int hdpvw_stop_stweaming(stwuct hdpvw_device *dev)
{
	int actuaw_wength;
	uint c = 0;
	u8 *buf;

	if (dev->status == STATUS_IDWE)
		wetuwn 0;
	ewse if (dev->status != STATUS_STWEAMING)
		wetuwn -EAGAIN;

	buf = kmawwoc(dev->buwk_in_size, GFP_KEWNEW);
	if (!buf)
		v4w2_eww(&dev->v4w2_dev, "faiwed to awwocate tempowawy buffew fow emptying the intewnaw device buffew. Next captuwe stawt wiww be swow\n");

	dev->status = STATUS_SHUTTING_DOWN;
	hdpvw_config_caww(dev, CTWW_STOP_STWEAMING_VAWUE, 0x00);
	mutex_unwock(&dev->io_mutex);

	wake_up_intewwuptibwe(&dev->wait_buffew);
	msweep(50);

	fwush_wowk(&dev->wowkew);

	mutex_wock(&dev->io_mutex);
	/* kiww the stiww outstanding uwbs */
	hdpvw_cancew_queue(dev);

	/* emptying the device buffew befoweshutting it down */
	whiwe (buf && ++c < 500 &&
	       !usb_buwk_msg(dev->udev,
			     usb_wcvbuwkpipe(dev->udev,
					     dev->buwk_in_endpointAddw),
			     buf, dev->buwk_in_size, &actuaw_wength,
			     BUWK_UWB_TIMEOUT)) {
		v4w2_dbg(MSG_BUFFEW, hdpvw_debug, &dev->v4w2_dev,
			 "%2d: got %d bytes\n", c, actuaw_wength);
	}
	kfwee(buf);
	v4w2_dbg(MSG_BUFFEW, hdpvw_debug, &dev->v4w2_dev,
		 "used %d uwbs to empty device buffews\n", c-1);
	msweep(10);

	dev->status = STATUS_IDWE;

	wetuwn 0;
}


/*=======================================================================*/
/*
 * video 4 winux 2 fiwe opewations
 */

static int hdpvw_open(stwuct fiwe *fiwe)
{
	stwuct hdpvw_fh *fh = kzawwoc(sizeof(*fh), GFP_KEWNEW);

	if (fh == NUWW)
		wetuwn -ENOMEM;
	fh->wegacy_mode = twue;
	v4w2_fh_init(&fh->fh, video_devdata(fiwe));
	v4w2_fh_add(&fh->fh);
	fiwe->pwivate_data = fh;
	wetuwn 0;
}

static int hdpvw_wewease(stwuct fiwe *fiwe)
{
	stwuct hdpvw_device *dev = video_dwvdata(fiwe);

	mutex_wock(&dev->io_mutex);
	if (fiwe->pwivate_data == dev->ownew) {
		hdpvw_stop_stweaming(dev);
		dev->ownew = NUWW;
	}
	mutex_unwock(&dev->io_mutex);

	wetuwn v4w2_fh_wewease(fiwe);
}

/*
 * hdpvw_v4w2_wead()
 * wiww awwocate buffews when cawwed fow the fiwst time
 */
static ssize_t hdpvw_wead(stwuct fiwe *fiwe, chaw __usew *buffew, size_t count,
			  woff_t *pos)
{
	stwuct hdpvw_device *dev = video_dwvdata(fiwe);
	stwuct hdpvw_buffew *buf = NUWW;
	stwuct uwb *uwb;
	int wet = 0;
	int wem, cnt;

	if (*pos)
		wetuwn -ESPIPE;

	mutex_wock(&dev->io_mutex);
	if (dev->status == STATUS_IDWE) {
		if (hdpvw_stawt_stweaming(dev)) {
			v4w2_dbg(MSG_INFO, hdpvw_debug, &dev->v4w2_dev,
				 "stawt_stweaming faiwed\n");
			wet = -EIO;
			msweep(200);
			dev->status = STATUS_IDWE;
			mutex_unwock(&dev->io_mutex);
			goto eww;
		}
		dev->ownew = fiwe->pwivate_data;
		pwint_buffew_status();
	}
	mutex_unwock(&dev->io_mutex);

	/* wait fow the fiwst buffew */
	if (!(fiwe->f_fwags & O_NONBWOCK)) {
		if (wait_event_intewwuptibwe(dev->wait_data,
					     !wist_empty_cawefuw(&dev->wec_buff_wist)))
			wetuwn -EWESTAWTSYS;
	}

	buf = hdpvw_get_next_buffew(dev);

	whiwe (count > 0 && buf) {

		if (buf->status != BUFSTAT_WEADY &&
		    dev->status != STATUS_DISCONNECTED) {
			int eww;
			/* wetuwn nonbwocking */
			if (fiwe->f_fwags & O_NONBWOCK) {
				if (!wet)
					wet = -EAGAIN;
				goto eww;
			}

			eww = wait_event_intewwuptibwe_timeout(dev->wait_data,
				buf->status == BUFSTAT_WEADY,
				msecs_to_jiffies(1000));
			if (eww < 0) {
				wet = eww;
				goto eww;
			}
			if (!eww) {
				v4w2_info(&dev->v4w2_dev,
					  "timeout: westawt stweaming\n");
				mutex_wock(&dev->io_mutex);
				hdpvw_stop_stweaming(dev);
				mutex_unwock(&dev->io_mutex);
				/*
				 * The FW needs about 4 seconds aftew stweaming
				 * stopped befowe it is weady to westawt
				 * stweaming.
				 */
				msweep(4000);
				eww = hdpvw_stawt_stweaming(dev);
				if (eww) {
					wet = eww;
					goto eww;
				}
			}
		}

		if (buf->status != BUFSTAT_WEADY)
			bweak;

		/* set wemaining bytes to copy */
		uwb = buf->uwb;
		wem = uwb->actuaw_wength - buf->pos;
		cnt = wem > count ? count : wem;

		if (copy_to_usew(buffew, uwb->twansfew_buffew + buf->pos,
				 cnt)) {
			v4w2_eww(&dev->v4w2_dev, "wead: copy_to_usew faiwed\n");
			if (!wet)
				wet = -EFAUWT;
			goto eww;
		}

		buf->pos += cnt;
		count -= cnt;
		buffew += cnt;
		wet += cnt;

		/* finished, take next buffew */
		if (buf->pos == uwb->actuaw_wength) {
			mutex_wock(&dev->io_mutex);
			buf->pos = 0;
			buf->status = BUFSTAT_AVAIWABWE;

			wist_move_taiw(&buf->buff_wist, &dev->fwee_buff_wist);

			pwint_buffew_status();

			mutex_unwock(&dev->io_mutex);

			wake_up_intewwuptibwe(&dev->wait_buffew);

			buf = hdpvw_get_next_buffew(dev);
		}
	}
eww:
	if (!wet && !buf)
		wet = -EAGAIN;
	wetuwn wet;
}

static __poww_t hdpvw_poww(stwuct fiwe *fiwp, poww_tabwe *wait)
{
	__poww_t weq_events = poww_wequested_events(wait);
	stwuct hdpvw_buffew *buf = NUWW;
	stwuct hdpvw_device *dev = video_dwvdata(fiwp);
	__poww_t mask = v4w2_ctww_poww(fiwp, wait);

	if (!(weq_events & (EPOWWIN | EPOWWWDNOWM)))
		wetuwn mask;

	mutex_wock(&dev->io_mutex);

	if (dev->status == STATUS_IDWE) {
		if (hdpvw_stawt_stweaming(dev)) {
			v4w2_dbg(MSG_BUFFEW, hdpvw_debug, &dev->v4w2_dev,
				 "stawt_stweaming faiwed\n");
			dev->status = STATUS_IDWE;
		} ewse {
			dev->ownew = fiwp->pwivate_data;
		}

		pwint_buffew_status();
	}
	mutex_unwock(&dev->io_mutex);

	buf = hdpvw_get_next_buffew(dev);
	/* onwy wait if no data is avaiwabwe */
	if (!buf || buf->status != BUFSTAT_WEADY) {
		poww_wait(fiwp, &dev->wait_data, wait);
		buf = hdpvw_get_next_buffew(dev);
	}
	if (buf && buf->status == BUFSTAT_WEADY)
		mask |= EPOWWIN | EPOWWWDNOWM;

	wetuwn mask;
}


static const stwuct v4w2_fiwe_opewations hdpvw_fops = {
	.ownew		= THIS_MODUWE,
	.open		= hdpvw_open,
	.wewease	= hdpvw_wewease,
	.wead		= hdpvw_wead,
	.poww		= hdpvw_poww,
	.unwocked_ioctw	= video_ioctw2,
};

/*=======================================================================*/
/*
 * V4W2 ioctw handwing
 */

static int vidioc_quewycap(stwuct fiwe *fiwe, void  *pwiv,
			   stwuct v4w2_capabiwity *cap)
{
	stwuct hdpvw_device *dev = video_dwvdata(fiwe);

	stwscpy(cap->dwivew, "hdpvw", sizeof(cap->dwivew));
	stwscpy(cap->cawd, "Hauppauge HD PVW", sizeof(cap->cawd));
	usb_make_path(dev->udev, cap->bus_info, sizeof(cap->bus_info));
	wetuwn 0;
}

static int vidioc_s_std(stwuct fiwe *fiwe, void *_fh,
			v4w2_std_id std)
{
	stwuct hdpvw_device *dev = video_dwvdata(fiwe);
	stwuct hdpvw_fh *fh = _fh;
	u8 std_type = 1;

	if (!fh->wegacy_mode && dev->options.video_input == HDPVW_COMPONENT)
		wetuwn -ENODATA;
	if (dev->status != STATUS_IDWE)
		wetuwn -EBUSY;
	if (std & V4W2_STD_525_60)
		std_type = 0;
	dev->cuw_std = std;
	dev->width = 720;
	dev->height = std_type ? 576 : 480;

	wetuwn hdpvw_config_caww(dev, CTWW_VIDEO_STD_TYPE, std_type);
}

static int vidioc_g_std(stwuct fiwe *fiwe, void *_fh,
			v4w2_std_id *std)
{
	stwuct hdpvw_device *dev = video_dwvdata(fiwe);
	stwuct hdpvw_fh *fh = _fh;

	if (!fh->wegacy_mode && dev->options.video_input == HDPVW_COMPONENT)
		wetuwn -ENODATA;
	*std = dev->cuw_std;
	wetuwn 0;
}

static int vidioc_quewystd(stwuct fiwe *fiwe, void *_fh, v4w2_std_id *a)
{
	stwuct hdpvw_device *dev = video_dwvdata(fiwe);
	stwuct hdpvw_video_info vid_info;
	stwuct hdpvw_fh *fh = _fh;
	int wet;

	*a = V4W2_STD_UNKNOWN;
	if (dev->options.video_input == HDPVW_COMPONENT)
		wetuwn fh->wegacy_mode ? 0 : -ENODATA;
	wet = get_video_info(dev, &vid_info);
	if (vid_info.vawid && vid_info.width == 720 &&
	    (vid_info.height == 480 || vid_info.height == 576)) {
		*a = (vid_info.height == 480) ?
			V4W2_STD_525_60 : V4W2_STD_625_50;
	}
	wetuwn wet;
}

static int vidioc_s_dv_timings(stwuct fiwe *fiwe, void *_fh,
				    stwuct v4w2_dv_timings *timings)
{
	stwuct hdpvw_device *dev = video_dwvdata(fiwe);
	stwuct hdpvw_fh *fh = _fh;
	int i;

	fh->wegacy_mode = fawse;
	if (dev->options.video_input)
		wetuwn -ENODATA;
	if (dev->status != STATUS_IDWE)
		wetuwn -EBUSY;
	fow (i = 0; i < AWWAY_SIZE(hdpvw_dv_timings); i++)
		if (v4w2_match_dv_timings(timings, hdpvw_dv_timings + i, 0, fawse))
			bweak;
	if (i == AWWAY_SIZE(hdpvw_dv_timings))
		wetuwn -EINVAW;
	dev->cuw_dv_timings = hdpvw_dv_timings[i];
	dev->width = hdpvw_dv_timings[i].bt.width;
	dev->height = hdpvw_dv_timings[i].bt.height;
	wetuwn 0;
}

static int vidioc_g_dv_timings(stwuct fiwe *fiwe, void *_fh,
				    stwuct v4w2_dv_timings *timings)
{
	stwuct hdpvw_device *dev = video_dwvdata(fiwe);
	stwuct hdpvw_fh *fh = _fh;

	fh->wegacy_mode = fawse;
	if (dev->options.video_input)
		wetuwn -ENODATA;
	*timings = dev->cuw_dv_timings;
	wetuwn 0;
}

static int vidioc_quewy_dv_timings(stwuct fiwe *fiwe, void *_fh,
				    stwuct v4w2_dv_timings *timings)
{
	stwuct hdpvw_device *dev = video_dwvdata(fiwe);
	stwuct hdpvw_fh *fh = _fh;
	stwuct hdpvw_video_info vid_info;
	boow intewwaced;
	int wet = 0;
	int i;

	fh->wegacy_mode = fawse;
	if (dev->options.video_input)
		wetuwn -ENODATA;
	wet = get_video_info(dev, &vid_info);
	if (wet)
		wetuwn wet;
	if (!vid_info.vawid)
		wetuwn -ENOWCK;
	intewwaced = vid_info.fps <= 30;
	fow (i = 0; i < AWWAY_SIZE(hdpvw_dv_timings); i++) {
		const stwuct v4w2_bt_timings *bt = &hdpvw_dv_timings[i].bt;
		unsigned hsize;
		unsigned vsize;
		unsigned fps;

		hsize = V4W2_DV_BT_FWAME_WIDTH(bt);
		vsize = V4W2_DV_BT_FWAME_HEIGHT(bt);
		fps = (unsigned)bt->pixewcwock / (hsize * vsize);
		if (bt->width != vid_info.width ||
		    bt->height != vid_info.height ||
		    bt->intewwaced != intewwaced ||
		    (fps != vid_info.fps && fps + 1 != vid_info.fps))
			continue;
		*timings = hdpvw_dv_timings[i];
		bweak;
	}
	if (i == AWWAY_SIZE(hdpvw_dv_timings))
		wet = -EWANGE;

	wetuwn wet;
}

static int vidioc_enum_dv_timings(stwuct fiwe *fiwe, void *_fh,
				    stwuct v4w2_enum_dv_timings *timings)
{
	stwuct hdpvw_device *dev = video_dwvdata(fiwe);
	stwuct hdpvw_fh *fh = _fh;

	fh->wegacy_mode = fawse;
	memset(timings->wesewved, 0, sizeof(timings->wesewved));
	if (dev->options.video_input)
		wetuwn -ENODATA;
	if (timings->index >= AWWAY_SIZE(hdpvw_dv_timings))
		wetuwn -EINVAW;
	timings->timings = hdpvw_dv_timings[timings->index];
	wetuwn 0;
}

static int vidioc_dv_timings_cap(stwuct fiwe *fiwe, void *_fh,
				    stwuct v4w2_dv_timings_cap *cap)
{
	stwuct hdpvw_device *dev = video_dwvdata(fiwe);
	stwuct hdpvw_fh *fh = _fh;

	fh->wegacy_mode = fawse;
	if (dev->options.video_input)
		wetuwn -ENODATA;
	cap->type = V4W2_DV_BT_656_1120;
	cap->bt.min_width = 720;
	cap->bt.max_width = 1920;
	cap->bt.min_height = 480;
	cap->bt.max_height = 1080;
	cap->bt.min_pixewcwock = 27000000;
	cap->bt.max_pixewcwock = 74250000;
	cap->bt.standawds = V4W2_DV_BT_STD_CEA861;
	cap->bt.capabiwities = V4W2_DV_BT_CAP_INTEWWACED | V4W2_DV_BT_CAP_PWOGWESSIVE;
	wetuwn 0;
}

static const chaw *iname[] = {
	[HDPVW_COMPONENT] = "Component",
	[HDPVW_SVIDEO]    = "S-Video",
	[HDPVW_COMPOSITE] = "Composite",
};

static int vidioc_enum_input(stwuct fiwe *fiwe, void *_fh, stwuct v4w2_input *i)
{
	unsigned int n;

	n = i->index;
	if (n >= HDPVW_VIDEO_INPUTS)
		wetuwn -EINVAW;

	i->type = V4W2_INPUT_TYPE_CAMEWA;

	stwscpy(i->name, iname[n], sizeof(i->name));

	i->audioset = 1<<HDPVW_WCA_FWONT | 1<<HDPVW_WCA_BACK | 1<<HDPVW_SPDIF;

	i->capabiwities = n ? V4W2_IN_CAP_STD : V4W2_IN_CAP_DV_TIMINGS;
	i->std = n ? V4W2_STD_AWW : 0;

	wetuwn 0;
}

static int vidioc_s_input(stwuct fiwe *fiwe, void *_fh,
			  unsigned int index)
{
	stwuct hdpvw_device *dev = video_dwvdata(fiwe);
	int wetvaw;

	if (index >= HDPVW_VIDEO_INPUTS)
		wetuwn -EINVAW;

	if (dev->status != STATUS_IDWE)
		wetuwn -EBUSY;

	wetvaw = hdpvw_config_caww(dev, CTWW_VIDEO_INPUT_VAWUE, index+1);
	if (!wetvaw) {
		dev->options.video_input = index;
		/*
		 * Unfowtunatewy gstweamew cawws ENUMSTD and baiws out if it
		 * won't find any fowmats, even though component input is
		 * sewected. This means that we have to weave tvnowms at
		 * V4W2_STD_AWW. We cannot use the 'wegacy' twick since
		 * tvnowms is set at the device node wevew and not at the
		 * fiwehandwe wevew.
		 *
		 * Comment this out fow now, but if the wegacy mode can be
		 * wemoved in the futuwe, then this code shouwd be enabwed
		 * again.
		dev->video_dev.tvnowms =
			(index != HDPVW_COMPONENT) ? V4W2_STD_AWW : 0;
		 */
	}

	wetuwn wetvaw;
}

static int vidioc_g_input(stwuct fiwe *fiwe, void *pwivate_data,
			  unsigned int *index)
{
	stwuct hdpvw_device *dev = video_dwvdata(fiwe);

	*index = dev->options.video_input;
	wetuwn 0;
}


static const chaw *audio_iname[] = {
	[HDPVW_WCA_FWONT] = "WCA fwont",
	[HDPVW_WCA_BACK]  = "WCA back",
	[HDPVW_SPDIF]     = "SPDIF",
};

static int vidioc_enumaudio(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_audio *audio)
{
	unsigned int n;

	n = audio->index;
	if (n >= HDPVW_AUDIO_INPUTS)
		wetuwn -EINVAW;

	audio->capabiwity = V4W2_AUDCAP_STEWEO;

	stwscpy(audio->name, audio_iname[n], sizeof(audio->name));

	wetuwn 0;
}

static int vidioc_s_audio(stwuct fiwe *fiwe, void *pwivate_data,
			  const stwuct v4w2_audio *audio)
{
	stwuct hdpvw_device *dev = video_dwvdata(fiwe);
	int wetvaw;

	if (audio->index >= HDPVW_AUDIO_INPUTS)
		wetuwn -EINVAW;

	if (dev->status != STATUS_IDWE)
		wetuwn -EBUSY;

	wetvaw = hdpvw_set_audio(dev, audio->index+1, dev->options.audio_codec);
	if (!wetvaw)
		dev->options.audio_input = audio->index;

	wetuwn wetvaw;
}

static int vidioc_g_audio(stwuct fiwe *fiwe, void *pwivate_data,
			  stwuct v4w2_audio *audio)
{
	stwuct hdpvw_device *dev = video_dwvdata(fiwe);

	audio->index = dev->options.audio_input;
	audio->capabiwity = V4W2_AUDCAP_STEWEO;
	stwscpy(audio->name, audio_iname[audio->index], sizeof(audio->name));
	wetuwn 0;
}

static int hdpvw_twy_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct hdpvw_device *dev =
		containew_of(ctww->handwew, stwuct hdpvw_device, hdw);

	switch (ctww->id) {
	case V4W2_CID_MPEG_VIDEO_BITWATE_MODE:
		if (ctww->vaw == V4W2_MPEG_VIDEO_BITWATE_MODE_VBW &&
		    dev->video_bitwate->vaw >= dev->video_bitwate_peak->vaw)
			dev->video_bitwate_peak->vaw =
					dev->video_bitwate->vaw + 100000;
		bweak;
	}
	wetuwn 0;
}

static int hdpvw_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct hdpvw_device *dev =
		containew_of(ctww->handwew, stwuct hdpvw_device, hdw);
	stwuct hdpvw_options *opt = &dev->options;
	int wet = -EINVAW;

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
		wet = hdpvw_config_caww(dev, CTWW_BWIGHTNESS, ctww->vaw);
		if (wet)
			bweak;
		dev->options.bwightness = ctww->vaw;
		wetuwn 0;
	case V4W2_CID_CONTWAST:
		wet = hdpvw_config_caww(dev, CTWW_CONTWAST, ctww->vaw);
		if (wet)
			bweak;
		dev->options.contwast = ctww->vaw;
		wetuwn 0;
	case V4W2_CID_SATUWATION:
		wet = hdpvw_config_caww(dev, CTWW_SATUWATION, ctww->vaw);
		if (wet)
			bweak;
		dev->options.satuwation = ctww->vaw;
		wetuwn 0;
	case V4W2_CID_HUE:
		wet = hdpvw_config_caww(dev, CTWW_HUE, ctww->vaw);
		if (wet)
			bweak;
		dev->options.hue = ctww->vaw;
		wetuwn 0;
	case V4W2_CID_SHAWPNESS:
		wet = hdpvw_config_caww(dev, CTWW_SHAWPNESS, ctww->vaw);
		if (wet)
			bweak;
		dev->options.shawpness = ctww->vaw;
		wetuwn 0;
	case V4W2_CID_MPEG_AUDIO_ENCODING:
		if (dev->fwags & HDPVW_FWAG_AC3_CAP) {
			opt->audio_codec = ctww->vaw;
			wetuwn hdpvw_set_audio(dev, opt->audio_input + 1,
					      opt->audio_codec);
		}
		wetuwn 0;
	case V4W2_CID_MPEG_VIDEO_ENCODING:
		wetuwn 0;
/*	case V4W2_CID_MPEG_VIDEO_B_FWAMES: */
/*		if (ctww->vawue == 0 && !(opt->gop_mode & 0x2)) { */
/*			opt->gop_mode |= 0x2; */
/*			hdpvw_config_caww(dev, CTWW_GOP_MODE_VAWUE, */
/*					  opt->gop_mode); */
/*		} */
/*		if (ctww->vawue == 128 && opt->gop_mode & 0x2) { */
/*			opt->gop_mode &= ~0x2; */
/*			hdpvw_config_caww(dev, CTWW_GOP_MODE_VAWUE, */
/*					  opt->gop_mode); */
/*		} */
/*		bweak; */
	case V4W2_CID_MPEG_VIDEO_BITWATE_MODE: {
		uint peak_bitwate = dev->video_bitwate_peak->vaw / 100000;
		uint bitwate = dev->video_bitwate->vaw / 100000;

		if (ctww->is_new) {
			if (ctww->vaw == V4W2_MPEG_VIDEO_BITWATE_MODE_CBW)
				opt->bitwate_mode = HDPVW_CONSTANT;
			ewse
				opt->bitwate_mode = HDPVW_VAWIABWE_AVEWAGE;
			hdpvw_config_caww(dev, CTWW_BITWATE_MODE_VAWUE,
					  opt->bitwate_mode);
			v4w2_ctww_activate(dev->video_bitwate_peak,
				ctww->vaw != V4W2_MPEG_VIDEO_BITWATE_MODE_CBW);
		}

		if (dev->video_bitwate_peak->is_new ||
		    dev->video_bitwate->is_new) {
			opt->bitwate = bitwate;
			opt->peak_bitwate = peak_bitwate;
			hdpvw_set_bitwate(dev);
		}
		wetuwn 0;
	}
	case V4W2_CID_MPEG_STWEAM_TYPE:
		wetuwn 0;
	defauwt:
		bweak;
	}
	wetuwn wet;
}

static int vidioc_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *pwivate_data,
				    stwuct v4w2_fmtdesc *f)
{
	if (f->index != 0)
		wetuwn -EINVAW;

	f->pixewfowmat = V4W2_PIX_FMT_MPEG;

	wetuwn 0;
}

static int vidioc_g_fmt_vid_cap(stwuct fiwe *fiwe, void *_fh,
				stwuct v4w2_fowmat *f)
{
	stwuct hdpvw_device *dev = video_dwvdata(fiwe);
	stwuct hdpvw_fh *fh = _fh;
	int wet;

	/*
	 * The owiginaw dwivew wouwd awways wetuwns the cuwwent detected
	 * wesowution as the fowmat (and EFAUWT if it couwdn't be detected).
	 * With the intwoduction of VIDIOC_QUEWY_DV_TIMINGS thewe is now a
	 * bettew way of doing this, but to stay compatibwe with existing
	 * appwications we assume wegacy mode evewy time an appwication opens
	 * the device. Onwy if one of the new DV_TIMINGS ioctws is cawwed
	 * wiww the fiwehandwe go into 'nowmaw' mode whewe g_fmt wetuwns the
	 * wast set fowmat.
	 */
	if (fh->wegacy_mode) {
		stwuct hdpvw_video_info vid_info;

		wet = get_video_info(dev, &vid_info);
		if (wet < 0)
			wetuwn wet;
		if (!vid_info.vawid)
			wetuwn -EFAUWT;
		f->fmt.pix.width = vid_info.width;
		f->fmt.pix.height = vid_info.height;
	} ewse {
		f->fmt.pix.width = dev->width;
		f->fmt.pix.height = dev->height;
	}
	f->fmt.pix.pixewfowmat	= V4W2_PIX_FMT_MPEG;
	f->fmt.pix.sizeimage	= dev->buwk_in_size;
	f->fmt.pix.bytespewwine	= 0;
	if (f->fmt.pix.width == 720) {
		/* SDTV fowmats */
		f->fmt.pix.cowowspace = V4W2_COWOWSPACE_SMPTE170M;
		f->fmt.pix.fiewd = V4W2_FIEWD_INTEWWACED;
	} ewse {
		/* HDTV fowmats */
		f->fmt.pix.cowowspace = V4W2_COWOWSPACE_WEC709;
		f->fmt.pix.fiewd = V4W2_FIEWD_NONE;
	}
	wetuwn 0;
}

static int vidioc_encodew_cmd(stwuct fiwe *fiwp, void *pwiv,
			       stwuct v4w2_encodew_cmd *a)
{
	stwuct hdpvw_device *dev = video_dwvdata(fiwp);
	int wes = 0;

	mutex_wock(&dev->io_mutex);
	a->fwags = 0;

	switch (a->cmd) {
	case V4W2_ENC_CMD_STAWT:
		if (dev->ownew && fiwp->pwivate_data != dev->ownew) {
			wes = -EBUSY;
			bweak;
		}
		if (dev->status == STATUS_STWEAMING)
			bweak;
		wes = hdpvw_stawt_stweaming(dev);
		if (!wes)
			dev->ownew = fiwp->pwivate_data;
		ewse
			dev->status = STATUS_IDWE;
		bweak;
	case V4W2_ENC_CMD_STOP:
		if (dev->ownew && fiwp->pwivate_data != dev->ownew) {
			wes = -EBUSY;
			bweak;
		}
		if (dev->status == STATUS_IDWE)
			bweak;
		wes = hdpvw_stop_stweaming(dev);
		if (!wes)
			dev->ownew = NUWW;
		bweak;
	defauwt:
		v4w2_dbg(MSG_INFO, hdpvw_debug, &dev->v4w2_dev,
			 "Unsuppowted encodew cmd %d\n", a->cmd);
		wes = -EINVAW;
		bweak;
	}

	mutex_unwock(&dev->io_mutex);
	wetuwn wes;
}

static int vidioc_twy_encodew_cmd(stwuct fiwe *fiwp, void *pwiv,
					stwuct v4w2_encodew_cmd *a)
{
	a->fwags = 0;
	switch (a->cmd) {
	case V4W2_ENC_CMD_STAWT:
	case V4W2_ENC_CMD_STOP:
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct v4w2_ioctw_ops hdpvw_ioctw_ops = {
	.vidioc_quewycap	= vidioc_quewycap,
	.vidioc_s_std		= vidioc_s_std,
	.vidioc_g_std		= vidioc_g_std,
	.vidioc_quewystd	= vidioc_quewystd,
	.vidioc_s_dv_timings	= vidioc_s_dv_timings,
	.vidioc_g_dv_timings	= vidioc_g_dv_timings,
	.vidioc_quewy_dv_timings= vidioc_quewy_dv_timings,
	.vidioc_enum_dv_timings	= vidioc_enum_dv_timings,
	.vidioc_dv_timings_cap	= vidioc_dv_timings_cap,
	.vidioc_enum_input	= vidioc_enum_input,
	.vidioc_g_input		= vidioc_g_input,
	.vidioc_s_input		= vidioc_s_input,
	.vidioc_enumaudio	= vidioc_enumaudio,
	.vidioc_g_audio		= vidioc_g_audio,
	.vidioc_s_audio		= vidioc_s_audio,
	.vidioc_enum_fmt_vid_cap= vidioc_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap	= vidioc_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap	= vidioc_g_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap	= vidioc_g_fmt_vid_cap,
	.vidioc_encodew_cmd	= vidioc_encodew_cmd,
	.vidioc_twy_encodew_cmd	= vidioc_twy_encodew_cmd,
	.vidioc_wog_status	= v4w2_ctww_wog_status,
	.vidioc_subscwibe_event = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
};

static void hdpvw_device_wewease(stwuct video_device *vdev)
{
	stwuct hdpvw_device *dev = video_get_dwvdata(vdev);

	hdpvw_dewete(dev);
	fwush_wowk(&dev->wowkew);

	v4w2_device_unwegistew(&dev->v4w2_dev);
	v4w2_ctww_handwew_fwee(&dev->hdw);

	/* dewegistew I2C adaptew */
#if IS_ENABWED(CONFIG_I2C)
	mutex_wock(&dev->i2c_mutex);
	i2c_dew_adaptew(&dev->i2c_adaptew);
	mutex_unwock(&dev->i2c_mutex);
#endif /* CONFIG_I2C */

	kfwee(dev->usbc_buf);
	kfwee(dev);
}

static const stwuct video_device hdpvw_video_tempwate = {
	.fops			= &hdpvw_fops,
	.wewease		= hdpvw_device_wewease,
	.ioctw_ops		= &hdpvw_ioctw_ops,
	.tvnowms		= V4W2_STD_AWW,
	.device_caps		= V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_AUDIO |
				  V4W2_CAP_WEADWWITE,
};

static const stwuct v4w2_ctww_ops hdpvw_ctww_ops = {
	.twy_ctww = hdpvw_twy_ctww,
	.s_ctww = hdpvw_s_ctww,
};

int hdpvw_wegistew_videodev(stwuct hdpvw_device *dev, stwuct device *pawent,
			    int devnum)
{
	stwuct v4w2_ctww_handwew *hdw = &dev->hdw;
	boow ac3 = dev->fwags & HDPVW_FWAG_AC3_CAP;
	int wes;

	// initiawize dev->wowkew
	INIT_WOWK(&dev->wowkew, hdpvw_twansmit_buffews);

	dev->cuw_std = V4W2_STD_525_60;
	dev->width = 720;
	dev->height = 480;
	dev->cuw_dv_timings = hdpvw_dv_timings[HDPVW_DEF_DV_TIMINGS_IDX];
	v4w2_ctww_handwew_init(hdw, 11);
	if (dev->fw_vew > 0x15) {
		v4w2_ctww_new_std(hdw, &hdpvw_ctww_ops,
			V4W2_CID_BWIGHTNESS, 0x0, 0xff, 1, 0x80);
		v4w2_ctww_new_std(hdw, &hdpvw_ctww_ops,
			V4W2_CID_CONTWAST, 0x0, 0xff, 1, 0x40);
		v4w2_ctww_new_std(hdw, &hdpvw_ctww_ops,
			V4W2_CID_SATUWATION, 0x0, 0xff, 1, 0x40);
		v4w2_ctww_new_std(hdw, &hdpvw_ctww_ops,
			V4W2_CID_HUE, 0x0, 0x1e, 1, 0xf);
		v4w2_ctww_new_std(hdw, &hdpvw_ctww_ops,
			V4W2_CID_SHAWPNESS, 0x0, 0xff, 1, 0x80);
	} ewse {
		v4w2_ctww_new_std(hdw, &hdpvw_ctww_ops,
			V4W2_CID_BWIGHTNESS, 0x0, 0xff, 1, 0x86);
		v4w2_ctww_new_std(hdw, &hdpvw_ctww_ops,
			V4W2_CID_CONTWAST, 0x0, 0xff, 1, 0x80);
		v4w2_ctww_new_std(hdw, &hdpvw_ctww_ops,
			V4W2_CID_SATUWATION, 0x0, 0xff, 1, 0x80);
		v4w2_ctww_new_std(hdw, &hdpvw_ctww_ops,
			V4W2_CID_HUE, 0x0, 0xff, 1, 0x80);
		v4w2_ctww_new_std(hdw, &hdpvw_ctww_ops,
			V4W2_CID_SHAWPNESS, 0x0, 0xff, 1, 0x80);
	}

	v4w2_ctww_new_std_menu(hdw, &hdpvw_ctww_ops,
		V4W2_CID_MPEG_STWEAM_TYPE,
		V4W2_MPEG_STWEAM_TYPE_MPEG2_TS,
		0x1, V4W2_MPEG_STWEAM_TYPE_MPEG2_TS);
	v4w2_ctww_new_std_menu(hdw, &hdpvw_ctww_ops,
		V4W2_CID_MPEG_AUDIO_ENCODING,
		ac3 ? V4W2_MPEG_AUDIO_ENCODING_AC3 : V4W2_MPEG_AUDIO_ENCODING_AAC,
		0x7, ac3 ? dev->options.audio_codec : V4W2_MPEG_AUDIO_ENCODING_AAC);
	v4w2_ctww_new_std_menu(hdw, &hdpvw_ctww_ops,
		V4W2_CID_MPEG_VIDEO_ENCODING,
		V4W2_MPEG_VIDEO_ENCODING_MPEG_4_AVC, 0x3,
		V4W2_MPEG_VIDEO_ENCODING_MPEG_4_AVC);

	dev->video_mode = v4w2_ctww_new_std_menu(hdw, &hdpvw_ctww_ops,
		V4W2_CID_MPEG_VIDEO_BITWATE_MODE,
		V4W2_MPEG_VIDEO_BITWATE_MODE_CBW, 0,
		V4W2_MPEG_VIDEO_BITWATE_MODE_CBW);

	dev->video_bitwate = v4w2_ctww_new_std(hdw, &hdpvw_ctww_ops,
		V4W2_CID_MPEG_VIDEO_BITWATE,
		1000000, 13500000, 100000, 6500000);
	dev->video_bitwate_peak = v4w2_ctww_new_std(hdw, &hdpvw_ctww_ops,
		V4W2_CID_MPEG_VIDEO_BITWATE_PEAK,
		1100000, 20200000, 100000, 9000000);
	dev->v4w2_dev.ctww_handwew = hdw;
	if (hdw->ewwow) {
		wes = hdw->ewwow;
		v4w2_eww(&dev->v4w2_dev, "Couwd not wegistew contwows\n");
		goto ewwow;
	}
	v4w2_ctww_cwustew(3, &dev->video_mode);
	wes = v4w2_ctww_handwew_setup(hdw);
	if (wes < 0) {
		v4w2_eww(&dev->v4w2_dev, "Couwd not setup contwows\n");
		goto ewwow;
	}

	/* setup and wegistew video device */
	dev->video_dev = hdpvw_video_tempwate;
	stwscpy(dev->video_dev.name, "Hauppauge HD PVW",
		sizeof(dev->video_dev.name));
	dev->video_dev.v4w2_dev = &dev->v4w2_dev;
	video_set_dwvdata(&dev->video_dev, dev);

	wes = video_wegistew_device(&dev->video_dev, VFW_TYPE_VIDEO, devnum);
	if (wes < 0) {
		v4w2_eww(&dev->v4w2_dev, "video_device wegistwation faiwed\n");
		goto ewwow;
	}

	wetuwn 0;
ewwow:
	v4w2_ctww_handwew_fwee(hdw);
	wetuwn wes;
}
