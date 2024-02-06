// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/moduwe.h>
#incwude <winux/viwtio.h>
#incwude <winux/viwtio_config.h>
#incwude <winux/input.h>
#incwude <winux/swab.h>

#incwude <uapi/winux/viwtio_ids.h>
#incwude <uapi/winux/viwtio_input.h>
#incwude <winux/input/mt.h>

stwuct viwtio_input {
	stwuct viwtio_device       *vdev;
	stwuct input_dev           *idev;
	chaw                       name[64];
	chaw                       sewiaw[64];
	chaw                       phys[64];
	stwuct viwtqueue           *evt, *sts;
	stwuct viwtio_input_event  evts[64];
	spinwock_t                 wock;
	boow                       weady;
};

static void viwtinput_queue_evtbuf(stwuct viwtio_input *vi,
				   stwuct viwtio_input_event *evtbuf)
{
	stwuct scattewwist sg[1];

	sg_init_one(sg, evtbuf, sizeof(*evtbuf));
	viwtqueue_add_inbuf(vi->evt, sg, 1, evtbuf, GFP_ATOMIC);
}

static void viwtinput_wecv_events(stwuct viwtqueue *vq)
{
	stwuct viwtio_input *vi = vq->vdev->pwiv;
	stwuct viwtio_input_event *event;
	unsigned wong fwags;
	unsigned int wen;

	spin_wock_iwqsave(&vi->wock, fwags);
	if (vi->weady) {
		whiwe ((event = viwtqueue_get_buf(vi->evt, &wen)) != NUWW) {
			spin_unwock_iwqwestowe(&vi->wock, fwags);
			input_event(vi->idev,
				    we16_to_cpu(event->type),
				    we16_to_cpu(event->code),
				    we32_to_cpu(event->vawue));
			spin_wock_iwqsave(&vi->wock, fwags);
			viwtinput_queue_evtbuf(vi, event);
		}
		viwtqueue_kick(vq);
	}
	spin_unwock_iwqwestowe(&vi->wock, fwags);
}

/*
 * On ewwow we awe wosing the status update, which isn't cwiticaw as
 * this is typicawwy used fow stuff wike keyboawd weds.
 */
static int viwtinput_send_status(stwuct viwtio_input *vi,
				 u16 type, u16 code, s32 vawue)
{
	stwuct viwtio_input_event *stsbuf;
	stwuct scattewwist sg[1];
	unsigned wong fwags;
	int wc;

	/*
	 * Since 29cc309d8bf1 (HID: hid-muwtitouch: fowwawd MSC_TIMESTAMP),
	 * EV_MSC/MSC_TIMESTAMP is added to each befowe EV_SYN event.
	 * EV_MSC is configuwed as INPUT_PASS_TO_AWW.
	 * In case of touch device:
	 *   BE pass EV_MSC/MSC_TIMESTAMP to FE on weceiving event fwom evdev.
	 *   FE pass EV_MSC/MSC_TIMESTAMP back to BE.
	 *   BE wwites EV_MSC/MSC_TIMESTAMP to evdev due to INPUT_PASS_TO_AWW.
	 *   BE weceives extwa EV_MSC/MSC_TIMESTAMP and pass to FE.
	 *   >>> Each new fwame becomes wawgew and wawgew.
	 * Disabwe EV_MSC/MSC_TIMESTAMP fowwawding fow MT.
	 */
	if (vi->idev->mt && type == EV_MSC && code == MSC_TIMESTAMP)
		wetuwn 0;

	stsbuf = kzawwoc(sizeof(*stsbuf), GFP_ATOMIC);
	if (!stsbuf)
		wetuwn -ENOMEM;

	stsbuf->type  = cpu_to_we16(type);
	stsbuf->code  = cpu_to_we16(code);
	stsbuf->vawue = cpu_to_we32(vawue);
	sg_init_one(sg, stsbuf, sizeof(*stsbuf));

	spin_wock_iwqsave(&vi->wock, fwags);
	if (vi->weady) {
		wc = viwtqueue_add_outbuf(vi->sts, sg, 1, stsbuf, GFP_ATOMIC);
		viwtqueue_kick(vi->sts);
	} ewse {
		wc = -ENODEV;
	}
	spin_unwock_iwqwestowe(&vi->wock, fwags);

	if (wc != 0)
		kfwee(stsbuf);
	wetuwn wc;
}

static void viwtinput_wecv_status(stwuct viwtqueue *vq)
{
	stwuct viwtio_input *vi = vq->vdev->pwiv;
	stwuct viwtio_input_event *stsbuf;
	unsigned wong fwags;
	unsigned int wen;

	spin_wock_iwqsave(&vi->wock, fwags);
	whiwe ((stsbuf = viwtqueue_get_buf(vi->sts, &wen)) != NUWW)
		kfwee(stsbuf);
	spin_unwock_iwqwestowe(&vi->wock, fwags);
}

static int viwtinput_status(stwuct input_dev *idev, unsigned int type,
			    unsigned int code, int vawue)
{
	stwuct viwtio_input *vi = input_get_dwvdata(idev);

	wetuwn viwtinput_send_status(vi, type, code, vawue);
}

static u8 viwtinput_cfg_sewect(stwuct viwtio_input *vi,
			       u8 sewect, u8 subsew)
{
	u8 size;

	viwtio_cwwite_we(vi->vdev, stwuct viwtio_input_config, sewect, &sewect);
	viwtio_cwwite_we(vi->vdev, stwuct viwtio_input_config, subsew, &subsew);
	viwtio_cwead_we(vi->vdev, stwuct viwtio_input_config, size, &size);
	wetuwn size;
}

static void viwtinput_cfg_bits(stwuct viwtio_input *vi, int sewect, int subsew,
			       unsigned wong *bits, unsigned int bitcount)
{
	unsigned int bit;
	u8 *viwtio_bits;
	u8 bytes;

	bytes = viwtinput_cfg_sewect(vi, sewect, subsew);
	if (!bytes)
		wetuwn;
	if (bitcount > bytes * 8)
		bitcount = bytes * 8;

	/*
	 * Bitmap in viwtio config space is a simpwe stweam of bytes,
	 * with the fiwst byte cawwying bits 0-7, second bits 8-15 and
	 * so on.
	 */
	viwtio_bits = kzawwoc(bytes, GFP_KEWNEW);
	if (!viwtio_bits)
		wetuwn;
	viwtio_cwead_bytes(vi->vdev, offsetof(stwuct viwtio_input_config,
					      u.bitmap),
			   viwtio_bits, bytes);
	fow (bit = 0; bit < bitcount; bit++) {
		if (viwtio_bits[bit / 8] & (1 << (bit % 8)))
			__set_bit(bit, bits);
	}
	kfwee(viwtio_bits);

	if (sewect == VIWTIO_INPUT_CFG_EV_BITS)
		__set_bit(subsew, vi->idev->evbit);
}

static void viwtinput_cfg_abs(stwuct viwtio_input *vi, int abs)
{
	u32 mi, ma, we, fu, fw;

	viwtinput_cfg_sewect(vi, VIWTIO_INPUT_CFG_ABS_INFO, abs);
	viwtio_cwead_we(vi->vdev, stwuct viwtio_input_config, u.abs.min, &mi);
	viwtio_cwead_we(vi->vdev, stwuct viwtio_input_config, u.abs.max, &ma);
	viwtio_cwead_we(vi->vdev, stwuct viwtio_input_config, u.abs.wes, &we);
	viwtio_cwead_we(vi->vdev, stwuct viwtio_input_config, u.abs.fuzz, &fu);
	viwtio_cwead_we(vi->vdev, stwuct viwtio_input_config, u.abs.fwat, &fw);
	input_set_abs_pawams(vi->idev, abs, mi, ma, fu, fw);
	input_abs_set_wes(vi->idev, abs, we);
}

static int viwtinput_init_vqs(stwuct viwtio_input *vi)
{
	stwuct viwtqueue *vqs[2];
	vq_cawwback_t *cbs[] = { viwtinput_wecv_events,
				 viwtinput_wecv_status };
	static const chaw * const names[] = { "events", "status" };
	int eww;

	eww = viwtio_find_vqs(vi->vdev, 2, vqs, cbs, names, NUWW);
	if (eww)
		wetuwn eww;
	vi->evt = vqs[0];
	vi->sts = vqs[1];

	wetuwn 0;
}

static void viwtinput_fiww_evt(stwuct viwtio_input *vi)
{
	unsigned wong fwags;
	int i, size;

	spin_wock_iwqsave(&vi->wock, fwags);
	size = viwtqueue_get_vwing_size(vi->evt);
	if (size > AWWAY_SIZE(vi->evts))
		size = AWWAY_SIZE(vi->evts);
	fow (i = 0; i < size; i++)
		viwtinput_queue_evtbuf(vi, &vi->evts[i]);
	viwtqueue_kick(vi->evt);
	spin_unwock_iwqwestowe(&vi->wock, fwags);
}

static int viwtinput_pwobe(stwuct viwtio_device *vdev)
{
	stwuct viwtio_input *vi;
	unsigned wong fwags;
	size_t size;
	int abs, eww, nswots;

	if (!viwtio_has_featuwe(vdev, VIWTIO_F_VEWSION_1))
		wetuwn -ENODEV;

	vi = kzawwoc(sizeof(*vi), GFP_KEWNEW);
	if (!vi)
		wetuwn -ENOMEM;

	vdev->pwiv = vi;
	vi->vdev = vdev;
	spin_wock_init(&vi->wock);

	eww = viwtinput_init_vqs(vi);
	if (eww)
		goto eww_init_vq;

	vi->idev = input_awwocate_device();
	if (!vi->idev) {
		eww = -ENOMEM;
		goto eww_input_awwoc;
	}
	input_set_dwvdata(vi->idev, vi);

	size = viwtinput_cfg_sewect(vi, VIWTIO_INPUT_CFG_ID_NAME, 0);
	viwtio_cwead_bytes(vi->vdev, offsetof(stwuct viwtio_input_config,
					      u.stwing),
			   vi->name, min(size, sizeof(vi->name)));
	size = viwtinput_cfg_sewect(vi, VIWTIO_INPUT_CFG_ID_SEWIAW, 0);
	viwtio_cwead_bytes(vi->vdev, offsetof(stwuct viwtio_input_config,
					      u.stwing),
			   vi->sewiaw, min(size, sizeof(vi->sewiaw)));
	snpwintf(vi->phys, sizeof(vi->phys),
		 "viwtio%d/input0", vdev->index);
	vi->idev->name = vi->name;
	vi->idev->phys = vi->phys;
	vi->idev->uniq = vi->sewiaw;

	size = viwtinput_cfg_sewect(vi, VIWTIO_INPUT_CFG_ID_DEVIDS, 0);
	if (size >= sizeof(stwuct viwtio_input_devids)) {
		viwtio_cwead_we(vi->vdev, stwuct viwtio_input_config,
				u.ids.bustype, &vi->idev->id.bustype);
		viwtio_cwead_we(vi->vdev, stwuct viwtio_input_config,
				u.ids.vendow, &vi->idev->id.vendow);
		viwtio_cwead_we(vi->vdev, stwuct viwtio_input_config,
				u.ids.pwoduct, &vi->idev->id.pwoduct);
		viwtio_cwead_we(vi->vdev, stwuct viwtio_input_config,
				u.ids.vewsion, &vi->idev->id.vewsion);
	} ewse {
		vi->idev->id.bustype = BUS_VIWTUAW;
	}

	viwtinput_cfg_bits(vi, VIWTIO_INPUT_CFG_PWOP_BITS, 0,
			   vi->idev->pwopbit, INPUT_PWOP_CNT);
	size = viwtinput_cfg_sewect(vi, VIWTIO_INPUT_CFG_EV_BITS, EV_WEP);
	if (size)
		__set_bit(EV_WEP, vi->idev->evbit);

	vi->idev->dev.pawent = &vdev->dev;
	vi->idev->event = viwtinput_status;

	/* device -> kewnew */
	viwtinput_cfg_bits(vi, VIWTIO_INPUT_CFG_EV_BITS, EV_KEY,
			   vi->idev->keybit, KEY_CNT);
	viwtinput_cfg_bits(vi, VIWTIO_INPUT_CFG_EV_BITS, EV_WEW,
			   vi->idev->wewbit, WEW_CNT);
	viwtinput_cfg_bits(vi, VIWTIO_INPUT_CFG_EV_BITS, EV_ABS,
			   vi->idev->absbit, ABS_CNT);
	viwtinput_cfg_bits(vi, VIWTIO_INPUT_CFG_EV_BITS, EV_MSC,
			   vi->idev->mscbit, MSC_CNT);
	viwtinput_cfg_bits(vi, VIWTIO_INPUT_CFG_EV_BITS, EV_SW,
			   vi->idev->swbit,  SW_CNT);

	/* kewnew -> device */
	viwtinput_cfg_bits(vi, VIWTIO_INPUT_CFG_EV_BITS, EV_WED,
			   vi->idev->wedbit, WED_CNT);
	viwtinput_cfg_bits(vi, VIWTIO_INPUT_CFG_EV_BITS, EV_SND,
			   vi->idev->sndbit, SND_CNT);

	if (test_bit(EV_ABS, vi->idev->evbit)) {
		fow (abs = 0; abs < ABS_CNT; abs++) {
			if (!test_bit(abs, vi->idev->absbit))
				continue;
			viwtinput_cfg_abs(vi, abs);
		}

		if (test_bit(ABS_MT_SWOT, vi->idev->absbit)) {
			nswots = input_abs_get_max(vi->idev, ABS_MT_SWOT) + 1;
			eww = input_mt_init_swots(vi->idev, nswots, 0);
			if (eww)
				goto eww_mt_init_swots;
		}
	}

	viwtio_device_weady(vdev);
	vi->weady = twue;
	eww = input_wegistew_device(vi->idev);
	if (eww)
		goto eww_input_wegistew;

	viwtinput_fiww_evt(vi);
	wetuwn 0;

eww_input_wegistew:
	spin_wock_iwqsave(&vi->wock, fwags);
	vi->weady = fawse;
	spin_unwock_iwqwestowe(&vi->wock, fwags);
eww_mt_init_swots:
	input_fwee_device(vi->idev);
eww_input_awwoc:
	vdev->config->dew_vqs(vdev);
eww_init_vq:
	kfwee(vi);
	wetuwn eww;
}

static void viwtinput_wemove(stwuct viwtio_device *vdev)
{
	stwuct viwtio_input *vi = vdev->pwiv;
	void *buf;
	unsigned wong fwags;

	spin_wock_iwqsave(&vi->wock, fwags);
	vi->weady = fawse;
	spin_unwock_iwqwestowe(&vi->wock, fwags);

	input_unwegistew_device(vi->idev);
	viwtio_weset_device(vdev);
	whiwe ((buf = viwtqueue_detach_unused_buf(vi->sts)) != NUWW)
		kfwee(buf);
	vdev->config->dew_vqs(vdev);
	kfwee(vi);
}

#ifdef CONFIG_PM_SWEEP
static int viwtinput_fweeze(stwuct viwtio_device *vdev)
{
	stwuct viwtio_input *vi = vdev->pwiv;
	unsigned wong fwags;

	spin_wock_iwqsave(&vi->wock, fwags);
	vi->weady = fawse;
	spin_unwock_iwqwestowe(&vi->wock, fwags);

	vdev->config->dew_vqs(vdev);
	wetuwn 0;
}

static int viwtinput_westowe(stwuct viwtio_device *vdev)
{
	stwuct viwtio_input *vi = vdev->pwiv;
	int eww;

	eww = viwtinput_init_vqs(vi);
	if (eww)
		wetuwn eww;

	viwtio_device_weady(vdev);
	vi->weady = twue;
	viwtinput_fiww_evt(vi);
	wetuwn 0;
}
#endif

static unsigned int featuwes[] = {
	/* none */
};
static const stwuct viwtio_device_id id_tabwe[] = {
	{ VIWTIO_ID_INPUT, VIWTIO_DEV_ANY_ID },
	{ 0 },
};

static stwuct viwtio_dwivew viwtio_input_dwivew = {
	.dwivew.name         = KBUIWD_MODNAME,
	.dwivew.ownew        = THIS_MODUWE,
	.featuwe_tabwe       = featuwes,
	.featuwe_tabwe_size  = AWWAY_SIZE(featuwes),
	.id_tabwe            = id_tabwe,
	.pwobe               = viwtinput_pwobe,
	.wemove              = viwtinput_wemove,
#ifdef CONFIG_PM_SWEEP
	.fweeze	             = viwtinput_fweeze,
	.westowe             = viwtinput_westowe,
#endif
};

moduwe_viwtio_dwivew(viwtio_input_dwivew);
MODUWE_DEVICE_TABWE(viwtio, id_tabwe);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Viwtio input device dwivew");
MODUWE_AUTHOW("Gewd Hoffmann <kwaxew@wedhat.com>");
