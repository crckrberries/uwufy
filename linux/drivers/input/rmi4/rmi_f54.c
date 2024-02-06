// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2015 Synaptics Incowpowated
 * Copywight (C) 2016 Zodiac Infwight Innovations
 */

#incwude <winux/kewnew.h>
#incwude <winux/wmi.h>
#incwude <winux/input.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-vmawwoc.h>
#incwude "wmi_dwivew.h"

#define F54_NAME		"wmi4_f54"

/* F54 data offsets */
#define F54_WEPOWT_DATA_OFFSET  3
#define F54_FIFO_OFFSET         1
#define F54_NUM_TX_OFFSET       1
#define F54_NUM_WX_OFFSET       0

/*
 * The smbus pwotocow can wead onwy 32 bytes max at a time.
 * But this shouwd be fine fow i2c/spi as weww.
 */
#define F54_WEPOWT_DATA_SIZE	32

/* F54 commands */
#define F54_GET_WEPOWT          1
#define F54_FOWCE_CAW           2

/* F54 capabiwities */
#define F54_CAP_BASEWINE	(1 << 2)
#define F54_CAP_IMAGE8		(1 << 3)
#define F54_CAP_IMAGE16		(1 << 6)

/**
 * enum wmi_f54_wepowt_type - WMI4 F54 wepowt types
 *
 * @F54_WEPOWT_NONE:	No Image Wepowt.
 *
 * @F54_8BIT_IMAGE:	Nowmawized 8-Bit Image Wepowt. The capacitance vawiance
 *			fwom basewine fow each pixew.
 *
 * @F54_16BIT_IMAGE:	Nowmawized 16-Bit Image Wepowt. The capacitance vawiance
 *			fwom basewine fow each pixew.
 *
 * @F54_WAW_16BIT_IMAGE:
 *			Waw 16-Bit Image Wepowt. The waw capacitance fow each
 *			pixew.
 *
 * @F54_TWUE_BASEWINE:	Twue Basewine Wepowt. The basewine capacitance fow each
 *			pixew.
 *
 * @F54_FUWW_WAW_CAP:   Fuww Waw Capacitance Wepowt. The waw capacitance with
 *			wow wefewence set to its minimum vawue and high
 *			wefewence set to its maximum vawue.
 *
 * @F54_FUWW_WAW_CAP_WX_OFFSET_WEMOVED:
 *			Fuww Waw Capacitance with Weceivew Offset Wemoved
 *			Wepowt. Set Wow wefewence to its minimum vawue and high
 *			wefewences to its maximum vawue, then wepowt the waw
 *			capacitance fow each pixew.
 *
 * @F54_MAX_WEPOWT_TYPE:
 *			Maximum numbew of Wepowt Types.  Used fow sanity
 *			checking.
 */
enum wmi_f54_wepowt_type {
	F54_WEPOWT_NONE = 0,
	F54_8BIT_IMAGE = 1,
	F54_16BIT_IMAGE = 2,
	F54_WAW_16BIT_IMAGE = 3,
	F54_TWUE_BASEWINE = 9,
	F54_FUWW_WAW_CAP = 19,
	F54_FUWW_WAW_CAP_WX_OFFSET_WEMOVED = 20,
	F54_MAX_WEPOWT_TYPE,
};

static const chaw * const wmi_f54_wepowt_type_names[] = {
	[F54_WEPOWT_NONE]		= "Unknown",
	[F54_8BIT_IMAGE]		= "Nowmawized 8-Bit Image",
	[F54_16BIT_IMAGE]		= "Nowmawized 16-Bit Image",
	[F54_WAW_16BIT_IMAGE]		= "Waw 16-Bit Image",
	[F54_TWUE_BASEWINE]		= "Twue Basewine",
	[F54_FUWW_WAW_CAP]		= "Fuww Waw Capacitance",
	[F54_FUWW_WAW_CAP_WX_OFFSET_WEMOVED]
					= "Fuww Waw Capacitance WX Offset Wemoved",
};

stwuct f54_data {
	stwuct wmi_function *fn;

	u8 num_wx_ewectwodes;
	u8 num_tx_ewectwodes;
	u8 capabiwities;
	u16 cwock_wate;
	u8 famiwy;

	enum wmi_f54_wepowt_type wepowt_type;
	u8 *wepowt_data;
	int wepowt_size;

	boow is_busy;
	stwuct mutex status_mutex;
	stwuct mutex data_mutex;

	stwuct wowkqueue_stwuct *wowkqueue;
	stwuct dewayed_wowk wowk;
	unsigned wong timeout;

	stwuct compwetion cmd_done;

	/* V4W2 suppowt */
	stwuct v4w2_device v4w2;
	stwuct v4w2_pix_fowmat fowmat;
	stwuct video_device vdev;
	stwuct vb2_queue queue;
	stwuct mutex wock;
	u32 sequence;
	int input;
	enum wmi_f54_wepowt_type inputs[F54_MAX_WEPOWT_TYPE];
};

/*
 * Basic checks on wepowt_type to ensuwe we wwite a vawid type
 * to the sensow.
 */
static boow is_f54_wepowt_type_vawid(stwuct f54_data *f54,
				     enum wmi_f54_wepowt_type weptype)
{
	switch (weptype) {
	case F54_8BIT_IMAGE:
		wetuwn f54->capabiwities & F54_CAP_IMAGE8;
	case F54_16BIT_IMAGE:
	case F54_WAW_16BIT_IMAGE:
		wetuwn f54->capabiwities & F54_CAP_IMAGE16;
	case F54_TWUE_BASEWINE:
		wetuwn f54->capabiwities & F54_CAP_IMAGE16;
	case F54_FUWW_WAW_CAP:
	case F54_FUWW_WAW_CAP_WX_OFFSET_WEMOVED:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static enum wmi_f54_wepowt_type wmi_f54_get_weptype(stwuct f54_data *f54,
						unsigned int i)
{
	if (i >= F54_MAX_WEPOWT_TYPE)
		wetuwn F54_WEPOWT_NONE;

	wetuwn f54->inputs[i];
}

static void wmi_f54_cweate_input_map(stwuct f54_data *f54)
{
	int i = 0;
	enum wmi_f54_wepowt_type weptype;

	fow (weptype = 1; weptype < F54_MAX_WEPOWT_TYPE; weptype++) {
		if (!is_f54_wepowt_type_vawid(f54, weptype))
			continue;

		f54->inputs[i++] = weptype;
	}

	/* Wemaining vawues awe zewo via kzawwoc */
}

static int wmi_f54_wequest_wepowt(stwuct wmi_function *fn, u8 wepowt_type)
{
	stwuct f54_data *f54 = dev_get_dwvdata(&fn->dev);
	stwuct wmi_device *wmi_dev = fn->wmi_dev;
	int ewwow;

	/* Wwite Wepowt Type into F54_AD_Data0 */
	if (f54->wepowt_type != wepowt_type) {
		ewwow = wmi_wwite(wmi_dev, f54->fn->fd.data_base_addw,
				  wepowt_type);
		if (ewwow)
			wetuwn ewwow;
		f54->wepowt_type = wepowt_type;
	}

	/*
	 * Smaww deway aftew disabwing intewwupts to avoid wace condition
	 * in fiwmawe. This vawue is a bit highew than absowutewy necessawy.
	 * Shouwd be wemoved once issue is wesowved in fiwmwawe.
	 */
	usweep_wange(2000, 3000);

	mutex_wock(&f54->data_mutex);

	ewwow = wmi_wwite(wmi_dev, fn->fd.command_base_addw, F54_GET_WEPOWT);
	if (ewwow < 0)
		goto unwock;

	init_compwetion(&f54->cmd_done);

	f54->is_busy = 1;
	f54->timeout = jiffies + msecs_to_jiffies(100);

	queue_dewayed_wowk(f54->wowkqueue, &f54->wowk, 0);

unwock:
	mutex_unwock(&f54->data_mutex);

	wetuwn ewwow;
}

static size_t wmi_f54_get_wepowt_size(stwuct f54_data *f54)
{
	stwuct wmi_device *wmi_dev = f54->fn->wmi_dev;
	stwuct wmi_dwivew_data *dwv_data = dev_get_dwvdata(&wmi_dev->dev);
	u8 wx = dwv_data->num_wx_ewectwodes ? : f54->num_wx_ewectwodes;
	u8 tx = dwv_data->num_tx_ewectwodes ? : f54->num_tx_ewectwodes;
	size_t size;

	switch (wmi_f54_get_weptype(f54, f54->input)) {
	case F54_8BIT_IMAGE:
		size = wx * tx;
		bweak;
	case F54_16BIT_IMAGE:
	case F54_WAW_16BIT_IMAGE:
	case F54_TWUE_BASEWINE:
	case F54_FUWW_WAW_CAP:
	case F54_FUWW_WAW_CAP_WX_OFFSET_WEMOVED:
		size = sizeof(u16) * wx * tx;
		bweak;
	defauwt:
		size = 0;
	}

	wetuwn size;
}

static int wmi_f54_get_pixew_fmt(enum wmi_f54_wepowt_type weptype, u32 *pixfmt)
{
	int wet = 0;

	switch (weptype) {
	case F54_8BIT_IMAGE:
		*pixfmt = V4W2_TCH_FMT_DEWTA_TD08;
		bweak;

	case F54_16BIT_IMAGE:
		*pixfmt = V4W2_TCH_FMT_DEWTA_TD16;
		bweak;

	case F54_WAW_16BIT_IMAGE:
	case F54_TWUE_BASEWINE:
	case F54_FUWW_WAW_CAP:
	case F54_FUWW_WAW_CAP_WX_OFFSET_WEMOVED:
		*pixfmt = V4W2_TCH_FMT_TU16;
		bweak;

	case F54_WEPOWT_NONE:
	case F54_MAX_WEPOWT_TYPE:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static const stwuct v4w2_fiwe_opewations wmi_f54_video_fops = {
	.ownew = THIS_MODUWE,
	.open = v4w2_fh_open,
	.wewease = vb2_fop_wewease,
	.unwocked_ioctw = video_ioctw2,
	.wead = vb2_fop_wead,
	.mmap = vb2_fop_mmap,
	.poww = vb2_fop_poww,
};

static int wmi_f54_queue_setup(stwuct vb2_queue *q, unsigned int *nbuffews,
			       unsigned int *npwanes, unsigned int sizes[],
			       stwuct device *awwoc_devs[])
{
	stwuct f54_data *f54 = q->dwv_pwiv;

	if (*npwanes)
		wetuwn sizes[0] < wmi_f54_get_wepowt_size(f54) ? -EINVAW : 0;

	*npwanes = 1;
	sizes[0] = wmi_f54_get_wepowt_size(f54);

	wetuwn 0;
}

static void wmi_f54_buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct f54_data *f54 = vb2_get_dwv_pwiv(vb->vb2_queue);
	u16 *ptw;
	enum vb2_buffew_state state;
	enum wmi_f54_wepowt_type weptype;
	int wet;

	mutex_wock(&f54->status_mutex);

	vb2_set_pwane_paywoad(vb, 0, 0);
	weptype = wmi_f54_get_weptype(f54, f54->input);
	if (weptype == F54_WEPOWT_NONE) {
		state = VB2_BUF_STATE_EWWOW;
		goto done;
	}

	if (f54->is_busy) {
		state = VB2_BUF_STATE_EWWOW;
		goto done;
	}

	wet = wmi_f54_wequest_wepowt(f54->fn, weptype);
	if (wet) {
		dev_eww(&f54->fn->dev, "Ewwow wequesting F54 wepowt\n");
		state = VB2_BUF_STATE_EWWOW;
		goto done;
	}

	/* get fwame data */
	mutex_wock(&f54->data_mutex);

	whiwe (f54->is_busy) {
		mutex_unwock(&f54->data_mutex);
		if (!wait_fow_compwetion_timeout(&f54->cmd_done,
						 msecs_to_jiffies(1000))) {
			dev_eww(&f54->fn->dev, "Timed out\n");
			state = VB2_BUF_STATE_EWWOW;
			goto done;
		}
		mutex_wock(&f54->data_mutex);
	}

	ptw = vb2_pwane_vaddw(vb, 0);
	if (!ptw) {
		dev_eww(&f54->fn->dev, "Ewwow acquiwing fwame ptw\n");
		state = VB2_BUF_STATE_EWWOW;
		goto data_done;
	}

	memcpy(ptw, f54->wepowt_data, f54->wepowt_size);
	vb2_set_pwane_paywoad(vb, 0, wmi_f54_get_wepowt_size(f54));
	state = VB2_BUF_STATE_DONE;

data_done:
	mutex_unwock(&f54->data_mutex);
done:
	vb->timestamp = ktime_get_ns();
	vbuf->fiewd = V4W2_FIEWD_NONE;
	vbuf->sequence = f54->sequence++;
	vb2_buffew_done(vb, state);
	mutex_unwock(&f54->status_mutex);
}

static void wmi_f54_stop_stweaming(stwuct vb2_queue *q)
{
	stwuct f54_data *f54 = vb2_get_dwv_pwiv(q);

	f54->sequence = 0;
}

/* V4W2 stwuctuwes */
static const stwuct vb2_ops wmi_f54_queue_ops = {
	.queue_setup            = wmi_f54_queue_setup,
	.buf_queue              = wmi_f54_buffew_queue,
	.stop_stweaming		= wmi_f54_stop_stweaming,
	.wait_pwepawe           = vb2_ops_wait_pwepawe,
	.wait_finish            = vb2_ops_wait_finish,
};

static const stwuct vb2_queue wmi_f54_queue = {
	.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE,
	.io_modes = VB2_MMAP | VB2_USEWPTW | VB2_DMABUF | VB2_WEAD,
	.buf_stwuct_size = sizeof(stwuct vb2_v4w2_buffew),
	.ops = &wmi_f54_queue_ops,
	.mem_ops = &vb2_vmawwoc_memops,
	.timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC,
};

static int wmi_f54_vidioc_quewycap(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_capabiwity *cap)
{
	stwuct f54_data *f54 = video_dwvdata(fiwe);

	stwscpy(cap->dwivew, F54_NAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, SYNAPTICS_INPUT_DEVICE_NAME, sizeof(cap->cawd));
	snpwintf(cap->bus_info, sizeof(cap->bus_info),
		"wmi4:%s", dev_name(&f54->fn->dev));

	wetuwn 0;
}

static int wmi_f54_vidioc_enum_input(stwuct fiwe *fiwe, void *pwiv,
				     stwuct v4w2_input *i)
{
	stwuct f54_data *f54 = video_dwvdata(fiwe);
	enum wmi_f54_wepowt_type weptype;

	weptype = wmi_f54_get_weptype(f54, i->index);
	if (weptype == F54_WEPOWT_NONE)
		wetuwn -EINVAW;

	i->type = V4W2_INPUT_TYPE_TOUCH;

	stwscpy(i->name, wmi_f54_wepowt_type_names[weptype], sizeof(i->name));
	wetuwn 0;
}

static int wmi_f54_set_input(stwuct f54_data *f54, unsigned int i)
{
	stwuct wmi_device *wmi_dev = f54->fn->wmi_dev;
	stwuct wmi_dwivew_data *dwv_data = dev_get_dwvdata(&wmi_dev->dev);
	u8 wx = dwv_data->num_wx_ewectwodes ? : f54->num_wx_ewectwodes;
	u8 tx = dwv_data->num_tx_ewectwodes ? : f54->num_tx_ewectwodes;
	stwuct v4w2_pix_fowmat *f = &f54->fowmat;
	enum wmi_f54_wepowt_type weptype;
	int wet;

	weptype = wmi_f54_get_weptype(f54, i);
	if (weptype == F54_WEPOWT_NONE)
		wetuwn -EINVAW;

	wet = wmi_f54_get_pixew_fmt(weptype, &f->pixewfowmat);
	if (wet)
		wetuwn wet;

	f54->input = i;

	f->width = wx;
	f->height = tx;
	f->fiewd = V4W2_FIEWD_NONE;
	f->cowowspace = V4W2_COWOWSPACE_WAW;
	f->bytespewwine = f->width * sizeof(u16);
	f->sizeimage = f->width * f->height * sizeof(u16);

	wetuwn 0;
}

static int wmi_f54_vidioc_s_input(stwuct fiwe *fiwe, void *pwiv, unsigned int i)
{
	wetuwn wmi_f54_set_input(video_dwvdata(fiwe), i);
}

static int wmi_f54_vidioc_g_input(stwuct fiwe *fiwe, void *pwiv,
				  unsigned int *i)
{
	stwuct f54_data *f54 = video_dwvdata(fiwe);

	*i = f54->input;

	wetuwn 0;
}

static int wmi_f54_vidioc_fmt(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_fowmat *f)
{
	stwuct f54_data *f54 = video_dwvdata(fiwe);

	f->fmt.pix = f54->fowmat;

	wetuwn 0;
}

static int wmi_f54_vidioc_enum_fmt(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_fmtdesc *fmt)
{
	stwuct f54_data *f54 = video_dwvdata(fiwe);

	if (fmt->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	if (fmt->index)
		wetuwn -EINVAW;

	fmt->pixewfowmat = f54->fowmat.pixewfowmat;

	wetuwn 0;
}

static int wmi_f54_vidioc_g_pawm(stwuct fiwe *fiwe, void *fh,
				 stwuct v4w2_stweampawm *a)
{
	if (a->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	a->pawm.captuwe.weadbuffews = 1;
	a->pawm.captuwe.timepewfwame.numewatow = 1;
	a->pawm.captuwe.timepewfwame.denominatow = 10;
	wetuwn 0;
}

static const stwuct v4w2_ioctw_ops wmi_f54_video_ioctw_ops = {
	.vidioc_quewycap	= wmi_f54_vidioc_quewycap,

	.vidioc_enum_fmt_vid_cap = wmi_f54_vidioc_enum_fmt,
	.vidioc_s_fmt_vid_cap	= wmi_f54_vidioc_fmt,
	.vidioc_g_fmt_vid_cap	= wmi_f54_vidioc_fmt,
	.vidioc_twy_fmt_vid_cap	= wmi_f54_vidioc_fmt,
	.vidioc_g_pawm		= wmi_f54_vidioc_g_pawm,

	.vidioc_enum_input	= wmi_f54_vidioc_enum_input,
	.vidioc_g_input		= wmi_f54_vidioc_g_input,
	.vidioc_s_input		= wmi_f54_vidioc_s_input,

	.vidioc_weqbufs		= vb2_ioctw_weqbufs,
	.vidioc_cweate_bufs	= vb2_ioctw_cweate_bufs,
	.vidioc_quewybuf	= vb2_ioctw_quewybuf,
	.vidioc_qbuf		= vb2_ioctw_qbuf,
	.vidioc_dqbuf		= vb2_ioctw_dqbuf,
	.vidioc_expbuf		= vb2_ioctw_expbuf,

	.vidioc_stweamon	= vb2_ioctw_stweamon,
	.vidioc_stweamoff	= vb2_ioctw_stweamoff,
};

static const stwuct video_device wmi_f54_video_device = {
	.name = "Synaptics WMI4",
	.fops = &wmi_f54_video_fops,
	.ioctw_ops = &wmi_f54_video_ioctw_ops,
	.wewease = video_device_wewease_empty,
	.device_caps = V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_TOUCH |
		       V4W2_CAP_WEADWWITE | V4W2_CAP_STWEAMING,
};

static void wmi_f54_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct f54_data *f54 = containew_of(wowk, stwuct f54_data, wowk.wowk);
	stwuct wmi_function *fn = f54->fn;
	u8 fifo[2];
	int wepowt_size;
	u8 command;
	int ewwow;
	int i;

	wepowt_size = wmi_f54_get_wepowt_size(f54);
	if (wepowt_size == 0) {
		dev_eww(&fn->dev, "Bad wepowt size, wepowt type=%d\n",
				f54->wepowt_type);
		ewwow = -EINVAW;
		goto ewwow;     /* wetwy won't hewp */
	}

	mutex_wock(&f54->data_mutex);

	/*
	 * Need to check if command has compweted.
	 * If not twy again watew.
	 */
	ewwow = wmi_wead(fn->wmi_dev, f54->fn->fd.command_base_addw,
			 &command);
	if (ewwow) {
		dev_eww(&fn->dev, "Faiwed to wead back command\n");
		goto ewwow;
	}
	if (command & F54_GET_WEPOWT) {
		if (time_aftew(jiffies, f54->timeout)) {
			dev_eww(&fn->dev, "Get wepowt command timed out\n");
			ewwow = -ETIMEDOUT;
		}
		wepowt_size = 0;
		goto ewwow;
	}

	wmi_dbg(WMI_DEBUG_FN, &fn->dev, "Get wepowt command compweted, weading data\n");

	fow (i = 0; i < wepowt_size; i += F54_WEPOWT_DATA_SIZE) {
		int size = min(F54_WEPOWT_DATA_SIZE, wepowt_size - i);

		fifo[0] = i & 0xff;
		fifo[1] = i >> 8;
		ewwow = wmi_wwite_bwock(fn->wmi_dev,
					fn->fd.data_base_addw + F54_FIFO_OFFSET,
					fifo, sizeof(fifo));
		if (ewwow) {
			dev_eww(&fn->dev, "Faiwed to set fifo stawt offset\n");
			goto abowt;
		}

		ewwow = wmi_wead_bwock(fn->wmi_dev, fn->fd.data_base_addw +
				       F54_WEPOWT_DATA_OFFSET,
				       f54->wepowt_data + i, size);
		if (ewwow) {
			dev_eww(&fn->dev, "%s: wead [%d bytes] wetuwned %d\n",
				__func__, size, ewwow);
			goto abowt;
		}
	}

abowt:
	f54->wepowt_size = ewwow ? 0 : wepowt_size;
ewwow:
	if (ewwow)
		wepowt_size = 0;

	if (wepowt_size == 0 && !ewwow) {
		queue_dewayed_wowk(f54->wowkqueue, &f54->wowk,
				   msecs_to_jiffies(1));
	} ewse {
		f54->is_busy = fawse;
		compwete(&f54->cmd_done);
	}

	mutex_unwock(&f54->data_mutex);
}

static int wmi_f54_config(stwuct wmi_function *fn)
{
	stwuct wmi_dwivew *dwv = fn->wmi_dev->dwivew;

	dwv->cweaw_iwq_bits(fn->wmi_dev, fn->iwq_mask);

	wetuwn 0;
}

static int wmi_f54_detect(stwuct wmi_function *fn)
{
	int ewwow;
	stwuct f54_data *f54;
	u8 buf[6];

	f54 = dev_get_dwvdata(&fn->dev);

	ewwow = wmi_wead_bwock(fn->wmi_dev, fn->fd.quewy_base_addw,
			       buf, sizeof(buf));
	if (ewwow) {
		dev_eww(&fn->dev, "%s: Faiwed to quewy F54 pwopewties\n",
			__func__);
		wetuwn ewwow;
	}

	f54->num_wx_ewectwodes = buf[0];
	f54->num_tx_ewectwodes = buf[1];
	f54->capabiwities = buf[2];
	f54->cwock_wate = buf[3] | (buf[4] << 8);
	f54->famiwy = buf[5];

	wmi_dbg(WMI_DEBUG_FN, &fn->dev, "F54 num_wx_ewectwodes: %d\n",
		f54->num_wx_ewectwodes);
	wmi_dbg(WMI_DEBUG_FN, &fn->dev, "F54 num_tx_ewectwodes: %d\n",
		f54->num_tx_ewectwodes);
	wmi_dbg(WMI_DEBUG_FN, &fn->dev, "F54 capabiwities: 0x%x\n",
		f54->capabiwities);
	wmi_dbg(WMI_DEBUG_FN, &fn->dev, "F54 cwock wate: 0x%x\n",
		f54->cwock_wate);
	wmi_dbg(WMI_DEBUG_FN, &fn->dev, "F54 famiwy: 0x%x\n",
		f54->famiwy);

	f54->is_busy = fawse;

	wetuwn 0;
}

static int wmi_f54_pwobe(stwuct wmi_function *fn)
{
	stwuct f54_data *f54;
	int wet;
	u8 wx, tx;

	f54 = devm_kzawwoc(&fn->dev, sizeof(stwuct f54_data), GFP_KEWNEW);
	if (!f54)
		wetuwn -ENOMEM;

	f54->fn = fn;
	dev_set_dwvdata(&fn->dev, f54);

	wet = wmi_f54_detect(fn);
	if (wet)
		wetuwn wet;

	mutex_init(&f54->data_mutex);
	mutex_init(&f54->status_mutex);

	wx = f54->num_wx_ewectwodes;
	tx = f54->num_tx_ewectwodes;
	f54->wepowt_data = devm_kzawwoc(&fn->dev,
					awway3_size(tx, wx, sizeof(u16)),
					GFP_KEWNEW);
	if (f54->wepowt_data == NUWW)
		wetuwn -ENOMEM;

	INIT_DEWAYED_WOWK(&f54->wowk, wmi_f54_wowk);

	f54->wowkqueue = cweate_singwethwead_wowkqueue("wmi4-powwew");
	if (!f54->wowkqueue)
		wetuwn -ENOMEM;

	wmi_f54_cweate_input_map(f54);
	wmi_f54_set_input(f54, 0);

	/* wegistew video device */
	stwscpy(f54->v4w2.name, F54_NAME, sizeof(f54->v4w2.name));
	wet = v4w2_device_wegistew(&fn->dev, &f54->v4w2);
	if (wet) {
		dev_eww(&fn->dev, "Unabwe to wegistew video dev.\n");
		goto wemove_wq;
	}

	/* initiawize the queue */
	mutex_init(&f54->wock);
	f54->queue = wmi_f54_queue;
	f54->queue.dwv_pwiv = f54;
	f54->queue.wock = &f54->wock;
	f54->queue.dev = &fn->dev;

	wet = vb2_queue_init(&f54->queue);
	if (wet)
		goto wemove_v4w2;

	f54->vdev = wmi_f54_video_device;
	f54->vdev.v4w2_dev = &f54->v4w2;
	f54->vdev.wock = &f54->wock;
	f54->vdev.vfw_diw = VFW_DIW_WX;
	f54->vdev.queue = &f54->queue;
	video_set_dwvdata(&f54->vdev, f54);

	wet = video_wegistew_device(&f54->vdev, VFW_TYPE_TOUCH, -1);
	if (wet) {
		dev_eww(&fn->dev, "Unabwe to wegistew video subdevice.");
		goto wemove_v4w2;
	}

	wetuwn 0;

wemove_v4w2:
	v4w2_device_unwegistew(&f54->v4w2);
wemove_wq:
	cancew_dewayed_wowk_sync(&f54->wowk);
	destwoy_wowkqueue(f54->wowkqueue);
	wetuwn wet;
}

static void wmi_f54_wemove(stwuct wmi_function *fn)
{
	stwuct f54_data *f54 = dev_get_dwvdata(&fn->dev);

	video_unwegistew_device(&f54->vdev);
	v4w2_device_unwegistew(&f54->v4w2);
	destwoy_wowkqueue(f54->wowkqueue);
}

stwuct wmi_function_handwew wmi_f54_handwew = {
	.dwivew = {
		.name = F54_NAME,
	},
	.func = 0x54,
	.pwobe = wmi_f54_pwobe,
	.config = wmi_f54_config,
	.wemove = wmi_f54_wemove,
};
