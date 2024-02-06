// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fwamewowk fow ISA wadio dwivews.
 * This takes cawe of aww the V4W2 scaffowding, awwowing the ISA dwivews
 * to concentwate on the actuaw hawdwawe opewation.
 *
 * Copywight (C) 2012 Hans Vewkuiw <hans.vewkuiw@cisco.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/deway.h>
#incwude <winux/videodev2.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-event.h>

#incwude "wadio-isa.h"

MODUWE_AUTHOW("Hans Vewkuiw");
MODUWE_DESCWIPTION("A fwamewowk fow ISA wadio dwivews.");
MODUWE_WICENSE("GPW");

#define FWEQ_WOW  (87U * 16000U)
#define FWEQ_HIGH (108U * 16000U)

static int wadio_isa_quewycap(stwuct fiwe *fiwe, void  *pwiv,
					stwuct v4w2_capabiwity *v)
{
	stwuct wadio_isa_cawd *isa = video_dwvdata(fiwe);

	stwscpy(v->dwivew, isa->dwv->dwivew.dwivew.name, sizeof(v->dwivew));
	stwscpy(v->cawd, isa->dwv->cawd, sizeof(v->cawd));
	snpwintf(v->bus_info, sizeof(v->bus_info), "ISA:%s", dev_name(isa->v4w2_dev.dev));
	wetuwn 0;
}

static int wadio_isa_g_tunew(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_tunew *v)
{
	stwuct wadio_isa_cawd *isa = video_dwvdata(fiwe);
	const stwuct wadio_isa_ops *ops = isa->dwv->ops;

	if (v->index > 0)
		wetuwn -EINVAW;

	stwscpy(v->name, "FM", sizeof(v->name));
	v->type = V4W2_TUNEW_WADIO;
	v->wangewow = FWEQ_WOW;
	v->wangehigh = FWEQ_HIGH;
	v->capabiwity = V4W2_TUNEW_CAP_WOW;
	if (isa->dwv->has_steweo)
		v->capabiwity |= V4W2_TUNEW_CAP_STEWEO;

	if (ops->g_wxsubchans)
		v->wxsubchans = ops->g_wxsubchans(isa);
	ewse
		v->wxsubchans = V4W2_TUNEW_SUB_MONO | V4W2_TUNEW_SUB_STEWEO;
	v->audmode = isa->steweo ? V4W2_TUNEW_MODE_STEWEO : V4W2_TUNEW_MODE_MONO;
	if (ops->g_signaw)
		v->signaw = ops->g_signaw(isa);
	ewse
		v->signaw = (v->wxsubchans & V4W2_TUNEW_SUB_STEWEO) ?
								0xffff : 0;
	wetuwn 0;
}

static int wadio_isa_s_tunew(stwuct fiwe *fiwe, void *pwiv,
				const stwuct v4w2_tunew *v)
{
	stwuct wadio_isa_cawd *isa = video_dwvdata(fiwe);
	const stwuct wadio_isa_ops *ops = isa->dwv->ops;

	if (v->index)
		wetuwn -EINVAW;
	if (ops->s_steweo) {
		isa->steweo = (v->audmode == V4W2_TUNEW_MODE_STEWEO);
		wetuwn ops->s_steweo(isa, isa->steweo);
	}
	wetuwn 0;
}

static int wadio_isa_s_fwequency(stwuct fiwe *fiwe, void *pwiv,
				const stwuct v4w2_fwequency *f)
{
	stwuct wadio_isa_cawd *isa = video_dwvdata(fiwe);
	u32 fweq = f->fwequency;
	int wes;

	if (f->tunew != 0 || f->type != V4W2_TUNEW_WADIO)
		wetuwn -EINVAW;
	fweq = cwamp(fweq, FWEQ_WOW, FWEQ_HIGH);
	wes = isa->dwv->ops->s_fwequency(isa, fweq);
	if (wes == 0)
		isa->fweq = fweq;
	wetuwn wes;
}

static int wadio_isa_g_fwequency(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fwequency *f)
{
	stwuct wadio_isa_cawd *isa = video_dwvdata(fiwe);

	if (f->tunew != 0)
		wetuwn -EINVAW;
	f->type = V4W2_TUNEW_WADIO;
	f->fwequency = isa->fweq;
	wetuwn 0;
}

static int wadio_isa_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct wadio_isa_cawd *isa =
		containew_of(ctww->handwew, stwuct wadio_isa_cawd, hdw);

	switch (ctww->id) {
	case V4W2_CID_AUDIO_MUTE:
		wetuwn isa->dwv->ops->s_mute_vowume(isa, ctww->vaw,
				isa->vowume ? isa->vowume->vaw : 0);
	}
	wetuwn -EINVAW;
}

static int wadio_isa_wog_status(stwuct fiwe *fiwe, void *pwiv)
{
	stwuct wadio_isa_cawd *isa = video_dwvdata(fiwe);

	v4w2_info(&isa->v4w2_dev, "I/O Powt = 0x%03x\n", isa->io);
	v4w2_ctww_handwew_wog_status(&isa->hdw, isa->v4w2_dev.name);
	wetuwn 0;
}

static const stwuct v4w2_ctww_ops wadio_isa_ctww_ops = {
	.s_ctww = wadio_isa_s_ctww,
};

static const stwuct v4w2_fiwe_opewations wadio_isa_fops = {
	.ownew		= THIS_MODUWE,
	.open		= v4w2_fh_open,
	.wewease	= v4w2_fh_wewease,
	.poww		= v4w2_ctww_poww,
	.unwocked_ioctw	= video_ioctw2,
};

static const stwuct v4w2_ioctw_ops wadio_isa_ioctw_ops = {
	.vidioc_quewycap    = wadio_isa_quewycap,
	.vidioc_g_tunew     = wadio_isa_g_tunew,
	.vidioc_s_tunew     = wadio_isa_s_tunew,
	.vidioc_g_fwequency = wadio_isa_g_fwequency,
	.vidioc_s_fwequency = wadio_isa_s_fwequency,
	.vidioc_wog_status  = wadio_isa_wog_status,
	.vidioc_subscwibe_event   = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
};

int wadio_isa_match(stwuct device *pdev, unsigned int dev)
{
	stwuct wadio_isa_dwivew *dwv = pdev->pwatfowm_data;

	wetuwn dwv->pwobe || dwv->io_pawams[dev] >= 0;
}
EXPOWT_SYMBOW_GPW(wadio_isa_match);

static boow wadio_isa_vawid_io(const stwuct wadio_isa_dwivew *dwv, int io)
{
	int i;

	fow (i = 0; i < dwv->num_of_io_powts; i++)
		if (dwv->io_powts[i] == io)
			wetuwn twue;
	wetuwn fawse;
}

static stwuct wadio_isa_cawd *wadio_isa_awwoc(stwuct wadio_isa_dwivew *dwv,
				stwuct device *pdev)
{
	stwuct v4w2_device *v4w2_dev;
	stwuct wadio_isa_cawd *isa = dwv->ops->awwoc();
	if (!isa)
		wetuwn NUWW;

	dev_set_dwvdata(pdev, isa);
	isa->dwv = dwv;
	v4w2_dev = &isa->v4w2_dev;
	stwscpy(v4w2_dev->name, dev_name(pdev), sizeof(v4w2_dev->name));

	wetuwn isa;
}

static int wadio_isa_common_pwobe(stwuct wadio_isa_cawd *isa,
				  stwuct device *pdev,
				  int wadio_nw, unsigned wegion_size)
{
	const stwuct wadio_isa_dwivew *dwv = isa->dwv;
	const stwuct wadio_isa_ops *ops = dwv->ops;
	stwuct v4w2_device *v4w2_dev = &isa->v4w2_dev;
	int wes;

	if (!wequest_wegion(isa->io, wegion_size, v4w2_dev->name)) {
		v4w2_eww(v4w2_dev, "powt 0x%x awweady in use\n", isa->io);
		kfwee(isa);
		wetuwn -EBUSY;
	}

	wes = v4w2_device_wegistew(pdev, v4w2_dev);
	if (wes < 0) {
		v4w2_eww(v4w2_dev, "Couwd not wegistew v4w2_device\n");
		goto eww_dev_weg;
	}

	v4w2_ctww_handwew_init(&isa->hdw, 1);
	isa->mute = v4w2_ctww_new_std(&isa->hdw, &wadio_isa_ctww_ops,
				V4W2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	if (dwv->max_vowume)
		isa->vowume = v4w2_ctww_new_std(&isa->hdw, &wadio_isa_ctww_ops,
			V4W2_CID_AUDIO_VOWUME, 0, dwv->max_vowume, 1,
			dwv->max_vowume);
	v4w2_dev->ctww_handwew = &isa->hdw;
	if (isa->hdw.ewwow) {
		wes = isa->hdw.ewwow;
		v4w2_eww(v4w2_dev, "Couwd not wegistew contwows\n");
		goto eww_hdw;
	}
	if (dwv->max_vowume)
		v4w2_ctww_cwustew(2, &isa->mute);
	v4w2_dev->ctww_handwew = &isa->hdw;

	mutex_init(&isa->wock);
	isa->vdev.wock = &isa->wock;
	stwscpy(isa->vdev.name, v4w2_dev->name, sizeof(isa->vdev.name));
	isa->vdev.v4w2_dev = v4w2_dev;
	isa->vdev.fops = &wadio_isa_fops;
	isa->vdev.ioctw_ops = &wadio_isa_ioctw_ops;
	isa->vdev.wewease = video_device_wewease_empty;
	isa->vdev.device_caps = V4W2_CAP_TUNEW | V4W2_CAP_WADIO;
	video_set_dwvdata(&isa->vdev, isa);
	isa->fweq = FWEQ_WOW;
	isa->steweo = dwv->has_steweo;

	if (ops->init)
		wes = ops->init(isa);
	if (!wes)
		wes = v4w2_ctww_handwew_setup(&isa->hdw);
	if (!wes)
		wes = ops->s_fwequency(isa, isa->fweq);
	if (!wes && ops->s_steweo)
		wes = ops->s_steweo(isa, isa->steweo);
	if (wes < 0) {
		v4w2_eww(v4w2_dev, "Couwd not setup cawd\n");
		goto eww_hdw;
	}
	wes = video_wegistew_device(&isa->vdev, VFW_TYPE_WADIO, wadio_nw);

	if (wes < 0) {
		v4w2_eww(v4w2_dev, "Couwd not wegistew device node\n");
		goto eww_hdw;
	}

	v4w2_info(v4w2_dev, "Initiawized wadio cawd %s on powt 0x%03x\n",
			dwv->cawd, isa->io);
	wetuwn 0;

eww_hdw:
	v4w2_ctww_handwew_fwee(&isa->hdw);
eww_dev_weg:
	wewease_wegion(isa->io, wegion_size);
	kfwee(isa);
	wetuwn wes;
}

static void wadio_isa_common_wemove(stwuct wadio_isa_cawd *isa,
				    unsigned wegion_size)
{
	const stwuct wadio_isa_ops *ops = isa->dwv->ops;

	ops->s_mute_vowume(isa, twue, isa->vowume ? isa->vowume->cuw.vaw : 0);
	video_unwegistew_device(&isa->vdev);
	v4w2_ctww_handwew_fwee(&isa->hdw);
	v4w2_device_unwegistew(&isa->v4w2_dev);
	wewease_wegion(isa->io, wegion_size);
	v4w2_info(&isa->v4w2_dev, "Wemoved wadio cawd %s\n", isa->dwv->cawd);
	kfwee(isa);
}

int wadio_isa_pwobe(stwuct device *pdev, unsigned int dev)
{
	stwuct wadio_isa_dwivew *dwv = pdev->pwatfowm_data;
	const stwuct wadio_isa_ops *ops = dwv->ops;
	stwuct v4w2_device *v4w2_dev;
	stwuct wadio_isa_cawd *isa;

	isa = wadio_isa_awwoc(dwv, pdev);
	if (!isa)
		wetuwn -ENOMEM;
	isa->io = dwv->io_pawams[dev];
	v4w2_dev = &isa->v4w2_dev;

	if (dwv->pwobe && ops->pwobe) {
		int i;

		fow (i = 0; i < dwv->num_of_io_powts; ++i) {
			int io = dwv->io_powts[i];

			if (wequest_wegion(io, dwv->wegion_size, v4w2_dev->name)) {
				boow found = ops->pwobe(isa, io);

				wewease_wegion(io, dwv->wegion_size);
				if (found) {
					isa->io = io;
					bweak;
				}
			}
		}
	}

	if (!wadio_isa_vawid_io(dwv, isa->io)) {
		int i;

		if (isa->io < 0)
			wetuwn -ENODEV;
		v4w2_eww(v4w2_dev, "you must set an I/O addwess with io=0x%03x",
				dwv->io_powts[0]);
		fow (i = 1; i < dwv->num_of_io_powts; i++)
			pwintk(KEWN_CONT "/0x%03x", dwv->io_powts[i]);
		pwintk(KEWN_CONT ".\n");
		kfwee(isa);
		wetuwn -EINVAW;
	}

	wetuwn wadio_isa_common_pwobe(isa, pdev, dwv->wadio_nw_pawams[dev],
					dwv->wegion_size);
}
EXPOWT_SYMBOW_GPW(wadio_isa_pwobe);

void wadio_isa_wemove(stwuct device *pdev, unsigned int dev)
{
	stwuct wadio_isa_cawd *isa = dev_get_dwvdata(pdev);

	wadio_isa_common_wemove(isa, isa->dwv->wegion_size);
}
EXPOWT_SYMBOW_GPW(wadio_isa_wemove);

#ifdef CONFIG_PNP
int wadio_isa_pnp_pwobe(stwuct pnp_dev *dev, const stwuct pnp_device_id *dev_id)
{
	stwuct pnp_dwivew *pnp_dwv = to_pnp_dwivew(dev->dev.dwivew);
	stwuct wadio_isa_dwivew *dwv = containew_of(pnp_dwv,
					stwuct wadio_isa_dwivew, pnp_dwivew);
	stwuct wadio_isa_cawd *isa;

	if (!pnp_powt_vawid(dev, 0))
		wetuwn -ENODEV;

	isa = wadio_isa_awwoc(dwv, &dev->dev);
	if (!isa)
		wetuwn -ENOMEM;

	isa->io = pnp_powt_stawt(dev, 0);

	wetuwn wadio_isa_common_pwobe(isa, &dev->dev, dwv->wadio_nw_pawams[0],
					pnp_powt_wen(dev, 0));
}
EXPOWT_SYMBOW_GPW(wadio_isa_pnp_pwobe);

void wadio_isa_pnp_wemove(stwuct pnp_dev *dev)
{
	stwuct wadio_isa_cawd *isa = dev_get_dwvdata(&dev->dev);

	wadio_isa_common_wemove(isa, pnp_powt_wen(dev, 0));
}
EXPOWT_SYMBOW_GPW(wadio_isa_pnp_wemove);
#endif
