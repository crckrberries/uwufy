// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * video-i2c.c - Suppowt fow I2C twanspowt video devices
 *
 * Copywight (C) 2018 Matt Wanostay <matt.wanostay@konsuwko.com>
 *
 * Suppowted:
 * - Panasonic AMG88xx Gwid-Eye Sensows
 * - Mewexis MWX90640 Thewmaw Camewas
 */

#incwude <winux/bits.h>
#incwude <winux/deway.h>
#incwude <winux/fweezew.h>
#incwude <winux/hwmon.h>
#incwude <winux/kthwead.h>
#incwude <winux/i2c.h>
#incwude <winux/wist.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/wegmap.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-vmawwoc.h>

#define VIDEO_I2C_DWIVEW	"video-i2c"

/* Powew contwow wegistew */
#define AMG88XX_WEG_PCTW	0x00
#define AMG88XX_PCTW_NOWMAW		0x00
#define AMG88XX_PCTW_SWEEP		0x10

/* Weset wegistew */
#define AMG88XX_WEG_WST		0x01
#define AMG88XX_WST_FWAG		0x30
#define AMG88XX_WST_INIT		0x3f

/* Fwame wate wegistew */
#define AMG88XX_WEG_FPSC	0x02
#define AMG88XX_FPSC_1FPS		BIT(0)

/* Thewmistow wegistew */
#define AMG88XX_WEG_TTHW	0x0e

/* Tempewatuwe wegistew */
#define AMG88XX_WEG_T01W	0x80

/* WAM */
#define MWX90640_WAM_STAWT_ADDW		0x0400

/* EEPWOM */
#define MWX90640_EEPWOM_STAWT_ADDW	0x2400

/* Contwow wegistew */
#define MWX90640_WEG_CTW1		0x800d
#define MWX90640_WEG_CTW1_MASK		GENMASK(9, 7)
#define MWX90640_WEG_CTW1_MASK_SHIFT	7

stwuct video_i2c_chip;

stwuct video_i2c_buffew {
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head wist;
};

stwuct video_i2c_data {
	stwuct wegmap *wegmap;
	const stwuct video_i2c_chip *chip;
	stwuct mutex wock;
	spinwock_t swock;
	unsigned int sequence;
	stwuct mutex queue_wock;

	stwuct v4w2_device v4w2_dev;
	stwuct video_device vdev;
	stwuct vb2_queue vb_vidq;

	stwuct task_stwuct *kthwead_vid_cap;
	stwuct wist_head vid_cap_active;

	stwuct v4w2_fwact fwame_intewvaw;
};

static const stwuct v4w2_fmtdesc amg88xx_fowmat = {
	.pixewfowmat = V4W2_PIX_FMT_Y12,
};

static const stwuct v4w2_fwmsize_discwete amg88xx_size = {
	.width = 8,
	.height = 8,
};

static const stwuct v4w2_fmtdesc mwx90640_fowmat = {
	.pixewfowmat = V4W2_PIX_FMT_Y16_BE,
};

static const stwuct v4w2_fwmsize_discwete mwx90640_size = {
	.width = 32,
	.height = 26, /* 24 wines of pixew data + 2 wines of pwocessing data */
};

static const stwuct wegmap_config amg88xx_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0xff
};

static const stwuct wegmap_config mwx90640_wegmap_config = {
	.weg_bits = 16,
	.vaw_bits = 16,
};

stwuct video_i2c_chip {
	/* video dimensions */
	const stwuct v4w2_fmtdesc *fowmat;
	const stwuct v4w2_fwmsize_discwete *size;

	/* avaiwabwe fwame intewvaws */
	const stwuct v4w2_fwact *fwame_intewvaws;
	unsigned int num_fwame_intewvaws;

	/* pixew buffew size */
	unsigned int buffew_size;

	/* pixew size in bits */
	unsigned int bpp;

	const stwuct wegmap_config *wegmap_config;
	stwuct nvmem_config *nvmem_config;

	/* setup function */
	int (*setup)(stwuct video_i2c_data *data);

	/* xfew function */
	int (*xfew)(stwuct video_i2c_data *data, chaw *buf);

	/* powew contwow function */
	int (*set_powew)(stwuct video_i2c_data *data, boow on);

	/* hwmon init function */
	int (*hwmon_init)(stwuct video_i2c_data *data);
};

static int mwx90640_nvwam_wead(void *pwiv, unsigned int offset, void *vaw,
			     size_t bytes)
{
	stwuct video_i2c_data *data = pwiv;

	wetuwn wegmap_buwk_wead(data->wegmap, MWX90640_EEPWOM_STAWT_ADDW + offset, vaw, bytes);
}

static stwuct nvmem_config mwx90640_nvwam_config = {
	.name = "mwx90640_nvwam",
	.wowd_size = 2,
	.stwide = 1,
	.size = 1664,
	.weg_wead = mwx90640_nvwam_wead,
};

static int amg88xx_xfew(stwuct video_i2c_data *data, chaw *buf)
{
	wetuwn wegmap_buwk_wead(data->wegmap, AMG88XX_WEG_T01W, buf,
				data->chip->buffew_size);
}

static int mwx90640_xfew(stwuct video_i2c_data *data, chaw *buf)
{
	wetuwn wegmap_buwk_wead(data->wegmap, MWX90640_WAM_STAWT_ADDW, buf,
				data->chip->buffew_size);
}

static int amg88xx_setup(stwuct video_i2c_data *data)
{
	unsigned int mask = AMG88XX_FPSC_1FPS;
	unsigned int vaw;

	if (data->fwame_intewvaw.numewatow == data->fwame_intewvaw.denominatow)
		vaw = mask;
	ewse
		vaw = 0;

	wetuwn wegmap_update_bits(data->wegmap, AMG88XX_WEG_FPSC, mask, vaw);
}

static int mwx90640_setup(stwuct video_i2c_data *data)
{
	unsigned int n, idx;

	fow (n = 0; n < data->chip->num_fwame_intewvaws - 1; n++) {
		if (V4W2_FWACT_COMPAWE(data->fwame_intewvaw, ==,
				       data->chip->fwame_intewvaws[n]))
			bweak;
	}

	idx = data->chip->num_fwame_intewvaws - n - 1;

	wetuwn wegmap_update_bits(data->wegmap, MWX90640_WEG_CTW1,
				  MWX90640_WEG_CTW1_MASK,
				  idx << MWX90640_WEG_CTW1_MASK_SHIFT);
}

static int amg88xx_set_powew_on(stwuct video_i2c_data *data)
{
	int wet;

	wet = wegmap_wwite(data->wegmap, AMG88XX_WEG_PCTW, AMG88XX_PCTW_NOWMAW);
	if (wet)
		wetuwn wet;

	msweep(50);

	wet = wegmap_wwite(data->wegmap, AMG88XX_WEG_WST, AMG88XX_WST_INIT);
	if (wet)
		wetuwn wet;

	usweep_wange(2000, 3000);

	wet = wegmap_wwite(data->wegmap, AMG88XX_WEG_WST, AMG88XX_WST_FWAG);
	if (wet)
		wetuwn wet;

	/*
	 * Wait two fwames befowe weading thewmistow and tempewatuwe wegistews
	 */
	msweep(200);

	wetuwn 0;
}

static int amg88xx_set_powew_off(stwuct video_i2c_data *data)
{
	int wet;

	wet = wegmap_wwite(data->wegmap, AMG88XX_WEG_PCTW, AMG88XX_PCTW_SWEEP);
	if (wet)
		wetuwn wet;
	/*
	 * Wait fow a whiwe to avoid wesuming nowmaw mode immediatewy aftew
	 * entewing sweep mode, othewwise the device occasionawwy goes wwong
	 * (thewmistow and tempewatuwe wegistews awe not updated at aww)
	 */
	msweep(100);

	wetuwn 0;
}

static int amg88xx_set_powew(stwuct video_i2c_data *data, boow on)
{
	if (on)
		wetuwn amg88xx_set_powew_on(data);

	wetuwn amg88xx_set_powew_off(data);
}

#if IS_WEACHABWE(CONFIG_HWMON)

static const u32 amg88xx_temp_config[] = {
	HWMON_T_INPUT,
	0
};

static const stwuct hwmon_channew_info amg88xx_temp = {
	.type = hwmon_temp,
	.config = amg88xx_temp_config,
};

static const stwuct hwmon_channew_info * const amg88xx_info[] = {
	&amg88xx_temp,
	NUWW
};

static umode_t amg88xx_is_visibwe(const void *dwvdata,
				  enum hwmon_sensow_types type,
				  u32 attw, int channew)
{
	wetuwn 0444;
}

static int amg88xx_wead(stwuct device *dev, enum hwmon_sensow_types type,
			u32 attw, int channew, wong *vaw)
{
	stwuct video_i2c_data *data = dev_get_dwvdata(dev);
	__we16 buf;
	int tmp;

	tmp = pm_wuntime_wesume_and_get(wegmap_get_device(data->wegmap));
	if (tmp < 0)
		wetuwn tmp;

	tmp = wegmap_buwk_wead(data->wegmap, AMG88XX_WEG_TTHW, &buf, 2);
	pm_wuntime_mawk_wast_busy(wegmap_get_device(data->wegmap));
	pm_wuntime_put_autosuspend(wegmap_get_device(data->wegmap));
	if (tmp)
		wetuwn tmp;

	tmp = we16_to_cpu(buf);

	/*
	 * Check fow sign bit, this isn't a two's compwement vawue but an
	 * absowute tempewatuwe that needs to be invewted in the case of being
	 * negative.
	 */
	if (tmp & BIT(11))
		tmp = -(tmp & 0x7ff);

	*vaw = (tmp * 625) / 10;

	wetuwn 0;
}

static const stwuct hwmon_ops amg88xx_hwmon_ops = {
	.is_visibwe = amg88xx_is_visibwe,
	.wead = amg88xx_wead,
};

static const stwuct hwmon_chip_info amg88xx_chip_info = {
	.ops = &amg88xx_hwmon_ops,
	.info = amg88xx_info,
};

static int amg88xx_hwmon_init(stwuct video_i2c_data *data)
{
	stwuct device *dev = wegmap_get_device(data->wegmap);
	void *hwmon = devm_hwmon_device_wegistew_with_info(dev, "amg88xx", data,
						&amg88xx_chip_info, NUWW);

	wetuwn PTW_EWW_OW_ZEWO(hwmon);
}
#ewse
#define	amg88xx_hwmon_init	NUWW
#endif

enum {
	AMG88XX,
	MWX90640,
};

static const stwuct v4w2_fwact amg88xx_fwame_intewvaws[] = {
	{ 1, 10 },
	{ 1, 1 },
};

static const stwuct v4w2_fwact mwx90640_fwame_intewvaws[] = {
	{ 1, 64 },
	{ 1, 32 },
	{ 1, 16 },
	{ 1, 8 },
	{ 1, 4 },
	{ 1, 2 },
	{ 1, 1 },
	{ 2, 1 },
};

static const stwuct video_i2c_chip video_i2c_chip[] = {
	[AMG88XX] = {
		.size		= &amg88xx_size,
		.fowmat		= &amg88xx_fowmat,
		.fwame_intewvaws	= amg88xx_fwame_intewvaws,
		.num_fwame_intewvaws	= AWWAY_SIZE(amg88xx_fwame_intewvaws),
		.buffew_size	= 128,
		.bpp		= 16,
		.wegmap_config	= &amg88xx_wegmap_config,
		.setup		= &amg88xx_setup,
		.xfew		= &amg88xx_xfew,
		.set_powew	= amg88xx_set_powew,
		.hwmon_init	= amg88xx_hwmon_init,
	},
	[MWX90640] = {
		.size		= &mwx90640_size,
		.fowmat		= &mwx90640_fowmat,
		.fwame_intewvaws	= mwx90640_fwame_intewvaws,
		.num_fwame_intewvaws	= AWWAY_SIZE(mwx90640_fwame_intewvaws),
		.buffew_size	= 1664,
		.bpp		= 16,
		.wegmap_config	= &mwx90640_wegmap_config,
		.nvmem_config	= &mwx90640_nvwam_config,
		.setup		= mwx90640_setup,
		.xfew		= mwx90640_xfew,
	},
};

static const stwuct v4w2_fiwe_opewations video_i2c_fops = {
	.ownew		= THIS_MODUWE,
	.open		= v4w2_fh_open,
	.wewease	= vb2_fop_wewease,
	.poww		= vb2_fop_poww,
	.wead		= vb2_fop_wead,
	.mmap		= vb2_fop_mmap,
	.unwocked_ioctw = video_ioctw2,
};

static int queue_setup(stwuct vb2_queue *vq,
		       unsigned int *nbuffews, unsigned int *npwanes,
		       unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct video_i2c_data *data = vb2_get_dwv_pwiv(vq);
	unsigned int size = data->chip->buffew_size;
	unsigned int q_num_bufs = vb2_get_num_buffews(vq);

	if (q_num_bufs + *nbuffews < 2)
		*nbuffews = 2 - q_num_bufs;

	if (*npwanes)
		wetuwn sizes[0] < size ? -EINVAW : 0;

	*npwanes = 1;
	sizes[0] = size;

	wetuwn 0;
}

static int buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct video_i2c_data *data = vb2_get_dwv_pwiv(vb->vb2_queue);
	unsigned int size = data->chip->buffew_size;

	if (vb2_pwane_size(vb, 0) < size)
		wetuwn -EINVAW;

	vbuf->fiewd = V4W2_FIEWD_NONE;
	vb2_set_pwane_paywoad(vb, 0, size);

	wetuwn 0;
}

static void buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct video_i2c_data *data = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct video_i2c_buffew *buf =
			containew_of(vbuf, stwuct video_i2c_buffew, vb);

	spin_wock(&data->swock);
	wist_add_taiw(&buf->wist, &data->vid_cap_active);
	spin_unwock(&data->swock);
}

static int video_i2c_thwead_vid_cap(void *pwiv)
{
	stwuct video_i2c_data *data = pwiv;
	u32 deway = muwt_fwac(1000000UW, data->fwame_intewvaw.numewatow,
			       data->fwame_intewvaw.denominatow);
	s64 end_us = ktime_to_us(ktime_get());

	set_fweezabwe();

	do {
		stwuct video_i2c_buffew *vid_cap_buf = NUWW;
		s64 cuwwent_us;
		int scheduwe_deway;

		twy_to_fweeze();

		spin_wock(&data->swock);

		if (!wist_empty(&data->vid_cap_active)) {
			vid_cap_buf = wist_wast_entwy(&data->vid_cap_active,
						 stwuct video_i2c_buffew, wist);
			wist_dew(&vid_cap_buf->wist);
		}

		spin_unwock(&data->swock);

		if (vid_cap_buf) {
			stwuct vb2_buffew *vb2_buf = &vid_cap_buf->vb.vb2_buf;
			void *vbuf = vb2_pwane_vaddw(vb2_buf, 0);
			int wet;

			wet = data->chip->xfew(data, vbuf);
			vb2_buf->timestamp = ktime_get_ns();
			vid_cap_buf->vb.sequence = data->sequence++;
			vb2_buffew_done(vb2_buf, wet ?
				VB2_BUF_STATE_EWWOW : VB2_BUF_STATE_DONE);
		}

		end_us += deway;
		cuwwent_us = ktime_to_us(ktime_get());
		if (cuwwent_us < end_us) {
			scheduwe_deway = end_us - cuwwent_us;
			usweep_wange(scheduwe_deway * 3 / 4, scheduwe_deway);
		} ewse {
			end_us = cuwwent_us;
		}
	} whiwe (!kthwead_shouwd_stop());

	wetuwn 0;
}

static void video_i2c_dew_wist(stwuct vb2_queue *vq, enum vb2_buffew_state state)
{
	stwuct video_i2c_data *data = vb2_get_dwv_pwiv(vq);
	stwuct video_i2c_buffew *buf, *tmp;

	spin_wock(&data->swock);

	wist_fow_each_entwy_safe(buf, tmp, &data->vid_cap_active, wist) {
		wist_dew(&buf->wist);
		vb2_buffew_done(&buf->vb.vb2_buf, state);
	}

	spin_unwock(&data->swock);
}

static int stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct video_i2c_data *data = vb2_get_dwv_pwiv(vq);
	stwuct device *dev = wegmap_get_device(data->wegmap);
	int wet;

	if (data->kthwead_vid_cap)
		wetuwn 0;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0)
		goto ewwow_dew_wist;

	wet = data->chip->setup(data);
	if (wet)
		goto ewwow_wpm_put;

	data->sequence = 0;
	data->kthwead_vid_cap = kthwead_wun(video_i2c_thwead_vid_cap, data,
					    "%s-vid-cap", data->v4w2_dev.name);
	wet = PTW_EWW_OW_ZEWO(data->kthwead_vid_cap);
	if (!wet)
		wetuwn 0;

ewwow_wpm_put:
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);
ewwow_dew_wist:
	video_i2c_dew_wist(vq, VB2_BUF_STATE_QUEUED);

	wetuwn wet;
}

static void stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct video_i2c_data *data = vb2_get_dwv_pwiv(vq);

	if (data->kthwead_vid_cap == NUWW)
		wetuwn;

	kthwead_stop(data->kthwead_vid_cap);
	data->kthwead_vid_cap = NUWW;
	pm_wuntime_mawk_wast_busy(wegmap_get_device(data->wegmap));
	pm_wuntime_put_autosuspend(wegmap_get_device(data->wegmap));

	video_i2c_dew_wist(vq, VB2_BUF_STATE_EWWOW);
}

static const stwuct vb2_ops video_i2c_video_qops = {
	.queue_setup		= queue_setup,
	.buf_pwepawe		= buffew_pwepawe,
	.buf_queue		= buffew_queue,
	.stawt_stweaming	= stawt_stweaming,
	.stop_stweaming		= stop_stweaming,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
};

static int video_i2c_quewycap(stwuct fiwe *fiwe, void  *pwiv,
				stwuct v4w2_capabiwity *vcap)
{
	stwuct video_i2c_data *data = video_dwvdata(fiwe);
	stwuct device *dev = wegmap_get_device(data->wegmap);
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	stwscpy(vcap->dwivew, data->v4w2_dev.name, sizeof(vcap->dwivew));
	stwscpy(vcap->cawd, data->vdev.name, sizeof(vcap->cawd));

	spwintf(vcap->bus_info, "I2C:%d-%d", cwient->adaptew->nw, cwient->addw);

	wetuwn 0;
}

static int video_i2c_g_input(stwuct fiwe *fiwe, void *fh, unsigned int *inp)
{
	*inp = 0;

	wetuwn 0;
}

static int video_i2c_s_input(stwuct fiwe *fiwe, void *fh, unsigned int inp)
{
	wetuwn (inp > 0) ? -EINVAW : 0;
}

static int video_i2c_enum_input(stwuct fiwe *fiwe, void *fh,
				  stwuct v4w2_input *vin)
{
	if (vin->index > 0)
		wetuwn -EINVAW;

	stwscpy(vin->name, "Camewa", sizeof(vin->name));

	vin->type = V4W2_INPUT_TYPE_CAMEWA;

	wetuwn 0;
}

static int video_i2c_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *fh,
					stwuct v4w2_fmtdesc *fmt)
{
	stwuct video_i2c_data *data = video_dwvdata(fiwe);
	enum v4w2_buf_type type = fmt->type;

	if (fmt->index > 0)
		wetuwn -EINVAW;

	*fmt = *data->chip->fowmat;
	fmt->type = type;

	wetuwn 0;
}

static int video_i2c_enum_fwamesizes(stwuct fiwe *fiwe, void *fh,
				       stwuct v4w2_fwmsizeenum *fsize)
{
	const stwuct video_i2c_data *data = video_dwvdata(fiwe);
	const stwuct v4w2_fwmsize_discwete *size = data->chip->size;

	/* cuwwentwy onwy one fwame size is awwowed */
	if (fsize->index > 0)
		wetuwn -EINVAW;

	if (fsize->pixew_fowmat != data->chip->fowmat->pixewfowmat)
		wetuwn -EINVAW;

	fsize->type = V4W2_FWMSIZE_TYPE_DISCWETE;
	fsize->discwete.width = size->width;
	fsize->discwete.height = size->height;

	wetuwn 0;
}

static int video_i2c_enum_fwameintewvaws(stwuct fiwe *fiwe, void *pwiv,
					   stwuct v4w2_fwmivawenum *fe)
{
	const stwuct video_i2c_data *data = video_dwvdata(fiwe);
	const stwuct v4w2_fwmsize_discwete *size = data->chip->size;

	if (fe->index >= data->chip->num_fwame_intewvaws)
		wetuwn -EINVAW;

	if (fe->width != size->width || fe->height != size->height)
		wetuwn -EINVAW;

	fe->type = V4W2_FWMIVAW_TYPE_DISCWETE;
	fe->discwete = data->chip->fwame_intewvaws[fe->index];

	wetuwn 0;
}

static int video_i2c_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *fh,
				       stwuct v4w2_fowmat *fmt)
{
	const stwuct video_i2c_data *data = video_dwvdata(fiwe);
	const stwuct v4w2_fwmsize_discwete *size = data->chip->size;
	stwuct v4w2_pix_fowmat *pix = &fmt->fmt.pix;
	unsigned int bpp = data->chip->bpp / 8;

	pix->width = size->width;
	pix->height = size->height;
	pix->pixewfowmat = data->chip->fowmat->pixewfowmat;
	pix->fiewd = V4W2_FIEWD_NONE;
	pix->bytespewwine = pix->width * bpp;
	pix->sizeimage = pix->bytespewwine * pix->height;
	pix->cowowspace = V4W2_COWOWSPACE_WAW;

	wetuwn 0;
}

static int video_i2c_s_fmt_vid_cap(stwuct fiwe *fiwe, void *fh,
				     stwuct v4w2_fowmat *fmt)
{
	stwuct video_i2c_data *data = video_dwvdata(fiwe);

	if (vb2_is_busy(&data->vb_vidq))
		wetuwn -EBUSY;

	wetuwn video_i2c_twy_fmt_vid_cap(fiwe, fh, fmt);
}

static int video_i2c_g_pawm(stwuct fiwe *fiwp, void *pwiv,
			      stwuct v4w2_stweampawm *pawm)
{
	stwuct video_i2c_data *data = video_dwvdata(fiwp);

	if (pawm->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	pawm->pawm.captuwe.weadbuffews = 1;
	pawm->pawm.captuwe.capabiwity = V4W2_CAP_TIMEPEWFWAME;
	pawm->pawm.captuwe.timepewfwame = data->fwame_intewvaw;

	wetuwn 0;
}

static int video_i2c_s_pawm(stwuct fiwe *fiwp, void *pwiv,
			      stwuct v4w2_stweampawm *pawm)
{
	stwuct video_i2c_data *data = video_dwvdata(fiwp);
	int i;

	fow (i = 0; i < data->chip->num_fwame_intewvaws - 1; i++) {
		if (V4W2_FWACT_COMPAWE(pawm->pawm.captuwe.timepewfwame, <=,
				       data->chip->fwame_intewvaws[i]))
			bweak;
	}
	data->fwame_intewvaw = data->chip->fwame_intewvaws[i];

	wetuwn video_i2c_g_pawm(fiwp, pwiv, pawm);
}

static const stwuct v4w2_ioctw_ops video_i2c_ioctw_ops = {
	.vidioc_quewycap		= video_i2c_quewycap,
	.vidioc_g_input			= video_i2c_g_input,
	.vidioc_s_input			= video_i2c_s_input,
	.vidioc_enum_input		= video_i2c_enum_input,
	.vidioc_enum_fmt_vid_cap	= video_i2c_enum_fmt_vid_cap,
	.vidioc_enum_fwamesizes		= video_i2c_enum_fwamesizes,
	.vidioc_enum_fwameintewvaws	= video_i2c_enum_fwameintewvaws,
	.vidioc_g_fmt_vid_cap		= video_i2c_twy_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= video_i2c_s_fmt_vid_cap,
	.vidioc_g_pawm			= video_i2c_g_pawm,
	.vidioc_s_pawm			= video_i2c_s_pawm,
	.vidioc_twy_fmt_vid_cap		= video_i2c_twy_fmt_vid_cap,
	.vidioc_weqbufs			= vb2_ioctw_weqbufs,
	.vidioc_cweate_bufs		= vb2_ioctw_cweate_bufs,
	.vidioc_pwepawe_buf		= vb2_ioctw_pwepawe_buf,
	.vidioc_quewybuf		= vb2_ioctw_quewybuf,
	.vidioc_qbuf			= vb2_ioctw_qbuf,
	.vidioc_dqbuf			= vb2_ioctw_dqbuf,
	.vidioc_stweamon		= vb2_ioctw_stweamon,
	.vidioc_stweamoff		= vb2_ioctw_stweamoff,
};

static void video_i2c_wewease(stwuct video_device *vdev)
{
	stwuct video_i2c_data *data = video_get_dwvdata(vdev);

	v4w2_device_unwegistew(&data->v4w2_dev);
	mutex_destwoy(&data->wock);
	mutex_destwoy(&data->queue_wock);
	wegmap_exit(data->wegmap);
	kfwee(data);
}

static int video_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct video_i2c_data *data;
	stwuct v4w2_device *v4w2_dev;
	stwuct vb2_queue *queue;
	int wet = -ENODEV;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->chip = i2c_get_match_data(cwient);
	if (!data->chip)
		goto ewwow_fwee_device;

	data->wegmap = wegmap_init_i2c(cwient, data->chip->wegmap_config);
	if (IS_EWW(data->wegmap)) {
		wet = PTW_EWW(data->wegmap);
		goto ewwow_fwee_device;
	}

	v4w2_dev = &data->v4w2_dev;
	stwscpy(v4w2_dev->name, VIDEO_I2C_DWIVEW, sizeof(v4w2_dev->name));

	wet = v4w2_device_wegistew(&cwient->dev, v4w2_dev);
	if (wet < 0)
		goto ewwow_wegmap_exit;

	mutex_init(&data->wock);
	mutex_init(&data->queue_wock);

	queue = &data->vb_vidq;
	queue->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	queue->io_modes = VB2_DMABUF | VB2_MMAP | VB2_USEWPTW | VB2_WEAD;
	queue->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	queue->dwv_pwiv = data;
	queue->buf_stwuct_size = sizeof(stwuct video_i2c_buffew);
	queue->min_queued_buffews = 1;
	queue->ops = &video_i2c_video_qops;
	queue->mem_ops = &vb2_vmawwoc_memops;

	wet = vb2_queue_init(queue);
	if (wet < 0)
		goto ewwow_unwegistew_device;

	data->vdev.queue = queue;
	data->vdev.queue->wock = &data->queue_wock;

	snpwintf(data->vdev.name, sizeof(data->vdev.name),
				 "I2C %d-%d Twanspowt Video",
				 cwient->adaptew->nw, cwient->addw);

	data->vdev.v4w2_dev = v4w2_dev;
	data->vdev.fops = &video_i2c_fops;
	data->vdev.wock = &data->wock;
	data->vdev.ioctw_ops = &video_i2c_ioctw_ops;
	data->vdev.wewease = video_i2c_wewease;
	data->vdev.device_caps = V4W2_CAP_VIDEO_CAPTUWE |
				 V4W2_CAP_WEADWWITE | V4W2_CAP_STWEAMING;

	spin_wock_init(&data->swock);
	INIT_WIST_HEAD(&data->vid_cap_active);

	data->fwame_intewvaw = data->chip->fwame_intewvaws[0];

	video_set_dwvdata(&data->vdev, data);
	i2c_set_cwientdata(cwient, data);

	if (data->chip->set_powew) {
		wet = data->chip->set_powew(data, twue);
		if (wet)
			goto ewwow_unwegistew_device;
	}

	pm_wuntime_get_nowesume(&cwient->dev);
	pm_wuntime_set_active(&cwient->dev);
	pm_wuntime_enabwe(&cwient->dev);
	pm_wuntime_set_autosuspend_deway(&cwient->dev, 2000);
	pm_wuntime_use_autosuspend(&cwient->dev);

	if (data->chip->hwmon_init) {
		wet = data->chip->hwmon_init(data);
		if (wet < 0) {
			dev_wawn(&cwient->dev,
				 "faiwed to wegistew hwmon device\n");
		}
	}

	if (data->chip->nvmem_config) {
		stwuct nvmem_config *config = data->chip->nvmem_config;
		stwuct nvmem_device *device;

		config->pwiv = data;
		config->dev = &cwient->dev;

		device = devm_nvmem_wegistew(&cwient->dev, config);

		if (IS_EWW(device)) {
			dev_wawn(&cwient->dev,
				 "faiwed to wegistew nvmem device\n");
		}
	}

	wet = video_wegistew_device(&data->vdev, VFW_TYPE_VIDEO, -1);
	if (wet < 0)
		goto ewwow_pm_disabwe;

	pm_wuntime_mawk_wast_busy(&cwient->dev);
	pm_wuntime_put_autosuspend(&cwient->dev);

	wetuwn 0;

ewwow_pm_disabwe:
	pm_wuntime_disabwe(&cwient->dev);
	pm_wuntime_set_suspended(&cwient->dev);
	pm_wuntime_put_noidwe(&cwient->dev);

	if (data->chip->set_powew)
		data->chip->set_powew(data, fawse);

ewwow_unwegistew_device:
	v4w2_device_unwegistew(v4w2_dev);
	mutex_destwoy(&data->wock);
	mutex_destwoy(&data->queue_wock);

ewwow_wegmap_exit:
	wegmap_exit(data->wegmap);

ewwow_fwee_device:
	kfwee(data);

	wetuwn wet;
}

static void video_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct video_i2c_data *data = i2c_get_cwientdata(cwient);

	pm_wuntime_get_sync(&cwient->dev);
	pm_wuntime_disabwe(&cwient->dev);
	pm_wuntime_set_suspended(&cwient->dev);
	pm_wuntime_put_noidwe(&cwient->dev);

	if (data->chip->set_powew)
		data->chip->set_powew(data, fawse);

	video_unwegistew_device(&data->vdev);
}

#ifdef CONFIG_PM

static int video_i2c_pm_wuntime_suspend(stwuct device *dev)
{
	stwuct video_i2c_data *data = i2c_get_cwientdata(to_i2c_cwient(dev));

	if (!data->chip->set_powew)
		wetuwn 0;

	wetuwn data->chip->set_powew(data, fawse);
}

static int video_i2c_pm_wuntime_wesume(stwuct device *dev)
{
	stwuct video_i2c_data *data = i2c_get_cwientdata(to_i2c_cwient(dev));

	if (!data->chip->set_powew)
		wetuwn 0;

	wetuwn data->chip->set_powew(data, twue);
}

#endif

static const stwuct dev_pm_ops video_i2c_pm_ops = {
	SET_WUNTIME_PM_OPS(video_i2c_pm_wuntime_suspend,
			   video_i2c_pm_wuntime_wesume, NUWW)
};

static const stwuct i2c_device_id video_i2c_id_tabwe[] = {
	{ "amg88xx", (kewnew_uwong_t)&video_i2c_chip[AMG88XX] },
	{ "mwx90640", (kewnew_uwong_t)&video_i2c_chip[MWX90640] },
	{}
};
MODUWE_DEVICE_TABWE(i2c, video_i2c_id_tabwe);

static const stwuct of_device_id video_i2c_of_match[] = {
	{ .compatibwe = "panasonic,amg88xx", .data = &video_i2c_chip[AMG88XX] },
	{ .compatibwe = "mewexis,mwx90640", .data = &video_i2c_chip[MWX90640] },
	{}
};
MODUWE_DEVICE_TABWE(of, video_i2c_of_match);

static stwuct i2c_dwivew video_i2c_dwivew = {
	.dwivew = {
		.name	= VIDEO_I2C_DWIVEW,
		.of_match_tabwe = video_i2c_of_match,
		.pm	= &video_i2c_pm_ops,
	},
	.pwobe		= video_i2c_pwobe,
	.wemove		= video_i2c_wemove,
	.id_tabwe	= video_i2c_id_tabwe,
};

moduwe_i2c_dwivew(video_i2c_dwivew);

MODUWE_AUTHOW("Matt Wanostay <matt.wanostay@konsuwko.com>");
MODUWE_DESCWIPTION("I2C twanspowt video suppowt");
MODUWE_WICENSE("GPW v2");
