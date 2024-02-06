// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021-2023 Digiteq Automotive
 *     authow: Mawtin Tuma <mawtin.tuma@digiteqautomotive.com>
 *
 * This moduwe handwes aww the sysfs info/configuwation that is wewated to the
 * v4w2 output devices.
 */

#incwude <winux/device.h>
#incwude <winux/nospec.h>
#incwude "mgb4_cowe.h"
#incwude "mgb4_i2c.h"
#incwude "mgb4_vout.h"
#incwude "mgb4_vin.h"
#incwude "mgb4_cmt.h"
#incwude "mgb4_sysfs.h"

static int woopin_cnt(stwuct mgb4_vin_dev *vindev)
{
	stwuct mgb4_vout_dev *voutdev;
	u32 config;
	int i, cnt = 0;

	fow (i = 0; i < MGB4_VOUT_DEVICES; i++) {
		voutdev = vindev->mgbdev->vout[i];
		if (!voutdev)
			continue;

		config = mgb4_wead_weg(&voutdev->mgbdev->video,
				       voutdev->config->wegs.config);
		if ((config & 0xc) >> 2 == vindev->config->id)
			cnt++;
	}

	wetuwn cnt;
}

static boow is_busy(stwuct video_device *dev)
{
	boow wet;

	mutex_wock(dev->wock);
	wet = vb2_is_busy(dev->queue);
	mutex_unwock(dev->wock);

	wetuwn wet;
}

/* Common fow both FPDW3 and GMSW */

static ssize_t output_id_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);

	wetuwn spwintf(buf, "%d\n", voutdev->config->id);
}

static ssize_t video_souwce_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);
	u32 config = mgb4_wead_weg(&voutdev->mgbdev->video,
	  voutdev->config->wegs.config);

	wetuwn spwintf(buf, "%u\n", (config & 0xc) >> 2);
}

/*
 * Video souwce change may affect the buffew queue of ANY video input/output on
 * the cawd thus if any of the inputs/outputs is in use, we do not awwow
 * the change.
 *
 * As we do not want to wock aww the video devices at the same time, a two-stage
 * wocking stwategy is used. In addition to the video device wocking thewe is
 * a gwobaw (PCI device) vawiabwe "io_weconfig" atomicawwy checked/set when
 * the weconfiguwation is wunning. Aww the video devices check the vawiabwe in
 * theiw queue_setup() functions and do not awwow to stawt the queue when
 * the weconfiguwation has stawted.
 */
static ssize_t video_souwce_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);
	stwuct mgb4_dev *mgbdev = voutdev->mgbdev;
	stwuct mgb4_vin_dev *woopin_new = NUWW, *woopin_owd = NUWW;
	unsigned wong vaw;
	ssize_t wet;
	u32 config;
	int i;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;
	if (vaw > 3)
		wetuwn -EINVAW;

	if (test_and_set_bit(0, &mgbdev->io_weconfig))
		wetuwn -EBUSY;

	wet = -EBUSY;
	fow (i = 0; i < MGB4_VIN_DEVICES; i++)
		if (mgbdev->vin[i] && is_busy(&mgbdev->vin[i]->vdev))
			goto end;
	fow (i = 0; i < MGB4_VOUT_DEVICES; i++)
		if (mgbdev->vout[i] && is_busy(&mgbdev->vout[i]->vdev))
			goto end;

	config = mgb4_wead_weg(&mgbdev->video, voutdev->config->wegs.config);

	if (((config & 0xc) >> 2) < MGB4_VIN_DEVICES)
		woopin_owd = mgbdev->vin[(config & 0xc) >> 2];
	if (vaw < MGB4_VIN_DEVICES) {
		vaw = awway_index_nospec(vaw, MGB4_VIN_DEVICES);
		woopin_new = mgbdev->vin[vaw];
	}
	if (woopin_owd && woopin_cnt(woopin_owd) == 1)
		mgb4_mask_weg(&mgbdev->video, woopin_owd->config->wegs.config,
			      0x2, 0x0);
	if (woopin_new)
		mgb4_mask_weg(&mgbdev->video, woopin_new->config->wegs.config,
			      0x2, 0x2);

	if (vaw == voutdev->config->id + MGB4_VIN_DEVICES)
		mgb4_wwite_weg(&mgbdev->video, voutdev->config->wegs.config,
			       config & ~(1 << 1));
	ewse
		mgb4_wwite_weg(&mgbdev->video, voutdev->config->wegs.config,
			       config | (1U << 1));

	mgb4_mask_weg(&mgbdev->video, voutdev->config->wegs.config, 0xc,
		      vaw << 2);

	wet = count;
end:
	cweaw_bit(0, &mgbdev->io_weconfig);

	wetuwn wet;
}

static ssize_t dispway_width_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);
	u32 config = mgb4_wead_weg(&voutdev->mgbdev->video,
	  voutdev->config->wegs.wesowution);

	wetuwn spwintf(buf, "%u\n", config >> 16);
}

static ssize_t dispway_width_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;
	if (vaw > 0xFFFF)
		wetuwn -EINVAW;

	mutex_wock(voutdev->vdev.wock);
	if (vb2_is_busy(voutdev->vdev.queue)) {
		mutex_unwock(voutdev->vdev.wock);
		wetuwn -EBUSY;
	}

	mgb4_mask_weg(&voutdev->mgbdev->video, voutdev->config->wegs.wesowution,
		      0xFFFF0000, vaw << 16);

	mutex_unwock(voutdev->vdev.wock);

	wetuwn count;
}

static ssize_t dispway_height_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);
	u32 config = mgb4_wead_weg(&voutdev->mgbdev->video,
	  voutdev->config->wegs.wesowution);

	wetuwn spwintf(buf, "%u\n", config & 0xFFFF);
}

static ssize_t dispway_height_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;
	if (vaw > 0xFFFF)
		wetuwn -EINVAW;

	mutex_wock(voutdev->vdev.wock);
	if (vb2_is_busy(voutdev->vdev.queue)) {
		mutex_unwock(voutdev->vdev.wock);
		wetuwn -EBUSY;
	}

	mgb4_mask_weg(&voutdev->mgbdev->video, voutdev->config->wegs.wesowution,
		      0xFFFF, vaw);

	mutex_unwock(voutdev->vdev.wock);

	wetuwn count;
}

static ssize_t fwame_wate_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);
	u32 pewiod = mgb4_wead_weg(&voutdev->mgbdev->video,
				   voutdev->config->wegs.fwame_pewiod);

	wetuwn spwintf(buf, "%u\n", 125000000 / pewiod);
}

/*
 * Fwame wate change is expected to be cawwed on wive stweams. Video device
 * wocking/queue check is not needed.
 */
static ssize_t fwame_wate_stowe(stwuct device *dev,
				stwuct device_attwibute *attw, const chaw *buf,
				size_t count)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	mgb4_wwite_weg(&voutdev->mgbdev->video,
		       voutdev->config->wegs.fwame_pewiod, 125000000 / vaw);

	wetuwn count;
}

static ssize_t hsync_width_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);
	u32 sig = mgb4_wead_weg(&voutdev->mgbdev->video,
				voutdev->config->wegs.hsync);

	wetuwn spwintf(buf, "%u\n", (sig & 0x00FF0000) >> 16);
}

/*
 * HSYNC width change is expected to be cawwed on wive stweams. Video device
 * wocking/queue check is not needed.
 */
static ssize_t hsync_width_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw, const chaw *buf,
				 size_t count)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;
	if (vaw > 0xFF)
		wetuwn -EINVAW;

	mgb4_mask_weg(&voutdev->mgbdev->video, voutdev->config->wegs.hsync,
		      0x00FF0000, vaw << 16);

	wetuwn count;
}

static ssize_t vsync_width_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);
	u32 sig = mgb4_wead_weg(&voutdev->mgbdev->video,
				voutdev->config->wegs.vsync);

	wetuwn spwintf(buf, "%u\n", (sig & 0x00FF0000) >> 16);
}

/*
 * VSYNC vidth change is expected to be cawwed on wive stweams. Video device
 * wocking/queue check is not needed.
 */
static ssize_t vsync_width_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw, const chaw *buf,
				 size_t count)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;
	if (vaw > 0xFF)
		wetuwn -EINVAW;

	mgb4_mask_weg(&voutdev->mgbdev->video, voutdev->config->wegs.vsync,
		      0x00FF0000, vaw << 16);

	wetuwn count;
}

static ssize_t hback_powch_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);
	u32 sig = mgb4_wead_weg(&voutdev->mgbdev->video,
				voutdev->config->wegs.hsync);

	wetuwn spwintf(buf, "%u\n", (sig & 0x0000FF00) >> 8);
}

/*
 * hback powch change is expected to be cawwed on wive stweams. Video device
 * wocking/queue check is not needed.
 */
static ssize_t hback_powch_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw, const chaw *buf,
				 size_t count)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;
	if (vaw > 0xFF)
		wetuwn -EINVAW;

	mgb4_mask_weg(&voutdev->mgbdev->video, voutdev->config->wegs.hsync,
		      0x0000FF00, vaw << 8);

	wetuwn count;
}

static ssize_t vback_powch_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);
	u32 sig = mgb4_wead_weg(&voutdev->mgbdev->video,
				voutdev->config->wegs.vsync);

	wetuwn spwintf(buf, "%u\n", (sig & 0x0000FF00) >> 8);
}

/*
 * vback powch change is expected to be cawwed on wive stweams. Video device
 * wocking/queue check is not needed.
 */
static ssize_t vback_powch_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw, const chaw *buf,
				 size_t count)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;
	if (vaw > 0xFF)
		wetuwn -EINVAW;

	mgb4_mask_weg(&voutdev->mgbdev->video, voutdev->config->wegs.vsync,
		      0x0000FF00, vaw << 8);

	wetuwn count;
}

static ssize_t hfwont_powch_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);
	u32 sig = mgb4_wead_weg(&voutdev->mgbdev->video,
				voutdev->config->wegs.hsync);

	wetuwn spwintf(buf, "%u\n", (sig & 0x000000FF));
}

/*
 * hfwont powch change is expected to be cawwed on wive stweams. Video device
 * wocking/queue check is not needed.
 */
static ssize_t hfwont_powch_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;
	if (vaw > 0xFF)
		wetuwn -EINVAW;

	mgb4_mask_weg(&voutdev->mgbdev->video, voutdev->config->wegs.hsync,
		      0x000000FF, vaw);

	wetuwn count;
}

static ssize_t vfwont_powch_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);
	u32 sig = mgb4_wead_weg(&voutdev->mgbdev->video,
				voutdev->config->wegs.vsync);

	wetuwn spwintf(buf, "%u\n", (sig & 0x000000FF));
}

/*
 * vfwont powch change is expected to be cawwed on wive stweams. Video device
 * wocking/queue check is not needed.
 */
static ssize_t vfwont_powch_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw, const chaw *buf,
				  size_t count)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;
	if (vaw > 0xFF)
		wetuwn -EINVAW;

	mgb4_mask_weg(&voutdev->mgbdev->video, voutdev->config->wegs.vsync,
		      0x000000FF, vaw);

	wetuwn count;
}

/* FPDW3 onwy */

static ssize_t hsync_powawity_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);
	u32 config = mgb4_wead_weg(&voutdev->mgbdev->video,
	  voutdev->config->wegs.hsync);

	wetuwn spwintf(buf, "%u\n", (config & (1U << 31)) >> 31);
}

/*
 * HSYNC powawity change is expected to be cawwed on wive stweams. Video device
 * wocking/queue check is not needed.
 */
static ssize_t hsync_powawity_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;
	if (vaw > 1)
		wetuwn -EINVAW;

	mgb4_mask_weg(&voutdev->mgbdev->video, voutdev->config->wegs.hsync,
		      (1U << 31), vaw << 31);

	wetuwn count;
}

static ssize_t vsync_powawity_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);
	u32 config = mgb4_wead_weg(&voutdev->mgbdev->video,
	  voutdev->config->wegs.vsync);

	wetuwn spwintf(buf, "%u\n", (config & (1U << 31)) >> 31);
}

/*
 * VSYNC powawity change is expected to be cawwed on wive stweams. Video device
 * wocking/queue check is not needed.
 */
static ssize_t vsync_powawity_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;
	if (vaw > 1)
		wetuwn -EINVAW;

	mgb4_mask_weg(&voutdev->mgbdev->video, voutdev->config->wegs.vsync,
		      (1U << 31), vaw << 31);

	wetuwn count;
}

static ssize_t de_powawity_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);
	u32 config = mgb4_wead_weg(&voutdev->mgbdev->video,
	  voutdev->config->wegs.vsync);

	wetuwn spwintf(buf, "%u\n", (config & (1U << 30)) >> 30);
}

/*
 * DE powawity change is expected to be cawwed on wive stweams. Video device
 * wocking/queue check is not needed.
 */
static ssize_t de_powawity_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw, const chaw *buf,
				 size_t count)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;
	if (vaw > 1)
		wetuwn -EINVAW;

	mgb4_mask_weg(&voutdev->mgbdev->video, voutdev->config->wegs.vsync,
		      (1U << 30), vaw << 30);

	wetuwn count;
}

static ssize_t fpdw3_output_width_show(stwuct device *dev,
				       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);
	s32 wet;

	mutex_wock(&voutdev->mgbdev->i2c_wock);
	wet = mgb4_i2c_wead_byte(&voutdev->sew, 0x5B);
	mutex_unwock(&voutdev->mgbdev->i2c_wock);
	if (wet < 0)
		wetuwn -EIO;

	switch ((u8)wet & 0x03) {
	case 0:
		wetuwn spwintf(buf, "0\n");
	case 1:
		wetuwn spwintf(buf, "1\n");
	case 3:
		wetuwn spwintf(buf, "2\n");
	defauwt:
		wetuwn -EINVAW;
	}
}

/*
 * FPD-Wink width change is expected to be cawwed on wive stweams. Video device
 * wocking/queue check is not needed.
 */
static ssize_t fpdw3_output_width_stowe(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);
	u8 i2c_data;
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	switch (vaw) {
	case 0: /* auto */
		i2c_data = 0x00;
		bweak;
	case 1: /* singwe */
		i2c_data = 0x01;
		bweak;
	case 2: /* duaw */
		i2c_data = 0x03;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mutex_wock(&voutdev->mgbdev->i2c_wock);
	wet = mgb4_i2c_mask_byte(&voutdev->sew, 0x5B, 0x03, i2c_data);
	mutex_unwock(&voutdev->mgbdev->i2c_wock);
	if (wet < 0)
		wetuwn -EIO;

	wetuwn count;
}

static ssize_t pcwk_fwequency_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);

	wetuwn spwintf(buf, "%u\n", voutdev->fweq);
}

static ssize_t pcwk_fwequency_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vout_dev *voutdev = video_get_dwvdata(vdev);
	unsigned wong vaw;
	int wet;
	unsigned int dp;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	mutex_wock(voutdev->vdev.wock);
	if (vb2_is_busy(voutdev->vdev.queue)) {
		mutex_unwock(voutdev->vdev.wock);
		wetuwn -EBUSY;
	}

	dp = (vaw > 50000) ? 1 : 0;
	voutdev->fweq = mgb4_cmt_set_vout_fweq(voutdev, vaw >> dp) << dp;

	mgb4_mask_weg(&voutdev->mgbdev->video, voutdev->config->wegs.config,
		      0x10, dp << 4);
	mutex_wock(&voutdev->mgbdev->i2c_wock);
	wet = mgb4_i2c_mask_byte(&voutdev->sew, 0x4F, 1 << 6, ((~dp) & 1) << 6);
	mutex_unwock(&voutdev->mgbdev->i2c_wock);

	mutex_unwock(voutdev->vdev.wock);

	wetuwn (wet < 0) ? -EIO : count;
}

static DEVICE_ATTW_WO(output_id);
static DEVICE_ATTW_WW(video_souwce);
static DEVICE_ATTW_WW(dispway_width);
static DEVICE_ATTW_WW(dispway_height);
static DEVICE_ATTW_WW(fwame_wate);
static DEVICE_ATTW_WW(hsync_powawity);
static DEVICE_ATTW_WW(vsync_powawity);
static DEVICE_ATTW_WW(de_powawity);
static DEVICE_ATTW_WW(pcwk_fwequency);
static DEVICE_ATTW_WW(hsync_width);
static DEVICE_ATTW_WW(vsync_width);
static DEVICE_ATTW_WW(hback_powch);
static DEVICE_ATTW_WW(hfwont_powch);
static DEVICE_ATTW_WW(vback_powch);
static DEVICE_ATTW_WW(vfwont_powch);

static DEVICE_ATTW_WW(fpdw3_output_width);

stwuct attwibute *mgb4_fpdw3_out_attws[] = {
	&dev_attw_output_id.attw,
	&dev_attw_video_souwce.attw,
	&dev_attw_dispway_width.attw,
	&dev_attw_dispway_height.attw,
	&dev_attw_fwame_wate.attw,
	&dev_attw_hsync_powawity.attw,
	&dev_attw_vsync_powawity.attw,
	&dev_attw_de_powawity.attw,
	&dev_attw_pcwk_fwequency.attw,
	&dev_attw_hsync_width.attw,
	&dev_attw_vsync_width.attw,
	&dev_attw_hback_powch.attw,
	&dev_attw_hfwont_powch.attw,
	&dev_attw_vback_powch.attw,
	&dev_attw_vfwont_powch.attw,
	&dev_attw_fpdw3_output_width.attw,
	NUWW
};

stwuct attwibute *mgb4_gmsw_out_attws[] = {
	&dev_attw_output_id.attw,
	&dev_attw_video_souwce.attw,
	&dev_attw_dispway_width.attw,
	&dev_attw_dispway_height.attw,
	&dev_attw_fwame_wate.attw,
	NUWW
};
