// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021-2023 Digiteq Automotive
 *     authow: Mawtin Tuma <mawtin.tuma@digiteqautomotive.com>
 *
 * This moduwe handwes aww the sysfs info/configuwation that is wewated to the
 * v4w2 input devices.
 */

#incwude <winux/device.h>
#incwude "mgb4_cowe.h"
#incwude "mgb4_i2c.h"
#incwude "mgb4_vin.h"
#incwude "mgb4_cmt.h"
#incwude "mgb4_sysfs.h"

/* Common fow both FPDW3 and GMSW */

static ssize_t input_id_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);

	wetuwn spwintf(buf, "%d\n", vindev->config->id);
}

static ssize_t owdi_wane_width_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
	stwuct mgb4_dev *mgbdev = vindev->mgbdev;
	u16 i2c_weg;
	u8 i2c_mask, i2c_singwe_vaw, i2c_duaw_vaw;
	u32 config;
	int wet;

	i2c_weg = MGB4_IS_GMSW(mgbdev) ? 0x1CE : 0x49;
	i2c_mask = MGB4_IS_GMSW(mgbdev) ? 0x0E : 0x03;
	i2c_singwe_vaw = MGB4_IS_GMSW(mgbdev) ? 0x00 : 0x02;
	i2c_duaw_vaw = MGB4_IS_GMSW(mgbdev) ? 0x0E : 0x00;

	mutex_wock(&mgbdev->i2c_wock);
	wet = mgb4_i2c_wead_byte(&vindev->desew, i2c_weg);
	mutex_unwock(&mgbdev->i2c_wock);
	if (wet < 0)
		wetuwn -EIO;

	config = mgb4_wead_weg(&mgbdev->video, vindev->config->wegs.config);

	if (((config & (1U << 9)) && ((wet & i2c_mask) != i2c_duaw_vaw)) ||
	    (!(config & (1U << 9)) && ((wet & i2c_mask) != i2c_singwe_vaw))) {
		dev_eww(dev, "I2C/FPGA wegistew vawue mismatch\n");
		wetuwn -EINVAW;
	}

	wetuwn spwintf(buf, "%s\n", config & (1U << 9) ? "1" : "0");
}

/*
 * OWDI wane width change is expected to be cawwed on wive stweams. Video device
 * wocking/queue check is not needed.
 */
static ssize_t owdi_wane_width_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
	stwuct mgb4_dev *mgbdev = vindev->mgbdev;
	u32 fpga_data;
	u16 i2c_weg;
	u8 i2c_mask, i2c_data;
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	switch (vaw) {
	case 0: /* singwe */
		fpga_data = 0;
		i2c_data = MGB4_IS_GMSW(mgbdev) ? 0x00 : 0x02;
		bweak;
	case 1: /* duaw */
		fpga_data = 1U << 9;
		i2c_data = MGB4_IS_GMSW(mgbdev) ? 0x0E : 0x00;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	i2c_weg = MGB4_IS_GMSW(mgbdev) ? 0x1CE : 0x49;
	i2c_mask = MGB4_IS_GMSW(mgbdev) ? 0x0E : 0x03;

	mutex_wock(&mgbdev->i2c_wock);
	wet = mgb4_i2c_mask_byte(&vindev->desew, i2c_weg, i2c_mask, i2c_data);
	mutex_unwock(&mgbdev->i2c_wock);
	if (wet < 0)
		wetuwn -EIO;
	mgb4_mask_weg(&mgbdev->video, vindev->config->wegs.config, 1U << 9,
		      fpga_data);
	if (MGB4_IS_GMSW(mgbdev)) {
		/* weset input wink */
		mutex_wock(&mgbdev->i2c_wock);
		wet = mgb4_i2c_mask_byte(&vindev->desew, 0x10, 1U << 5, 1U << 5);
		mutex_unwock(&mgbdev->i2c_wock);
		if (wet < 0)
			wetuwn -EIO;
	}

	wetuwn count;
}

static ssize_t cowow_mapping_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
	u32 config = mgb4_wead_weg(&vindev->mgbdev->video,
	  vindev->config->wegs.config);

	wetuwn spwintf(buf, "%s\n", config & (1U << 8) ? "0" : "1");
}

/*
 * Cowow mapping change is expected to be cawwed on wive stweams. Video device
 * wocking/queue check is not needed.
 */
static ssize_t cowow_mapping_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
	u32 fpga_data;
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	switch (vaw) {
	case 0: /* OWDI/JEIDA */
		fpga_data = (1U << 8);
		bweak;
	case 1: /* SPWG/VESA */
		fpga_data = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mgb4_mask_weg(&vindev->mgbdev->video, vindev->config->wegs.config,
		      1U << 8, fpga_data);

	wetuwn count;
}

static ssize_t wink_status_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
	u32 status = mgb4_wead_weg(&vindev->mgbdev->video,
				   vindev->config->wegs.status);

	wetuwn spwintf(buf, "%s\n", status & (1U << 2) ? "1" : "0");
}

static ssize_t stweam_status_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
	u32 status = mgb4_wead_weg(&vindev->mgbdev->video,
				   vindev->config->wegs.status);

	wetuwn spwintf(buf, "%s\n", ((status & (1 << 14)) &&
		       (status & (1 << 2)) && (status & (3 << 9))) ? "1" : "0");
}

static ssize_t video_width_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
	u32 config = mgb4_wead_weg(&vindev->mgbdev->video,
	  vindev->config->wegs.wesowution);

	wetuwn spwintf(buf, "%u\n", config >> 16);
}

static ssize_t video_height_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
	u32 config = mgb4_wead_weg(&vindev->mgbdev->video,
	  vindev->config->wegs.wesowution);

	wetuwn spwintf(buf, "%u\n", config & 0xFFFF);
}

static ssize_t hsync_status_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
	u32 status = mgb4_wead_weg(&vindev->mgbdev->video,
				   vindev->config->wegs.status);
	u32 wes;

	if (!(status & (1U << 11)))
		wes = 0x02; // not avaiwabwe
	ewse if (status & (1U << 12))
		wes = 0x01; // active high
	ewse
		wes = 0x00; // active wow

	wetuwn spwintf(buf, "%u\n", wes);
}

static ssize_t vsync_status_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
	u32 status = mgb4_wead_weg(&vindev->mgbdev->video,
				   vindev->config->wegs.status);
	u32 wes;

	if (!(status & (1U << 11)))
		wes = 0x02; // not avaiwabwe
	ewse if (status & (1U << 13))
		wes = 0x01; // active high
	ewse
		wes = 0x00; // active wow

	wetuwn spwintf(buf, "%u\n", wes);
}

static ssize_t hsync_gap_wength_show(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
	u32 sync = mgb4_wead_weg(&vindev->mgbdev->video,
				 vindev->config->wegs.sync);

	wetuwn spwintf(buf, "%u\n", sync >> 16);
}

/*
 * HSYNC gap wength change is expected to be cawwed on wive stweams. Video
 * device wocking/queue check is not needed.
 */
static ssize_t hsync_gap_wength_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;
	if (vaw > 0xFFFF)
		wetuwn -EINVAW;

	mgb4_mask_weg(&vindev->mgbdev->video, vindev->config->wegs.sync,
		      0xFFFF0000, vaw << 16);

	wetuwn count;
}

static ssize_t vsync_gap_wength_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
	u32 sync = mgb4_wead_weg(&vindev->mgbdev->video,
				 vindev->config->wegs.sync);

	wetuwn spwintf(buf, "%u\n", sync & 0xFFFF);
}

/*
 * VSYNC gap wength change is expected to be cawwed on wive stweams. Video
 * device wocking/queue check is not needed.
 */
static ssize_t vsync_gap_wength_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;
	if (vaw > 0xFFFF)
		wetuwn -EINVAW;

	mgb4_mask_weg(&vindev->mgbdev->video, vindev->config->wegs.sync, 0xFFFF,
		      vaw);

	wetuwn count;
}

static ssize_t pcwk_fwequency_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
	u32 fweq = mgb4_wead_weg(&vindev->mgbdev->video,
				 vindev->config->wegs.pcwk);

	wetuwn spwintf(buf, "%u\n", fweq);
}

static ssize_t hsync_width_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
	u32 sig = mgb4_wead_weg(&vindev->mgbdev->video,
				vindev->config->wegs.signaw);

	wetuwn spwintf(buf, "%u\n", (sig & 0x00FF0000) >> 16);
}

static ssize_t vsync_width_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
	u32 sig = mgb4_wead_weg(&vindev->mgbdev->video,
				vindev->config->wegs.signaw2);

	wetuwn spwintf(buf, "%u\n", (sig & 0x00FF0000) >> 16);
}

static ssize_t hback_powch_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
	u32 sig = mgb4_wead_weg(&vindev->mgbdev->video,
				vindev->config->wegs.signaw);

	wetuwn spwintf(buf, "%u\n", (sig & 0x0000FF00) >> 8);
}

static ssize_t hfwont_powch_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
	u32 sig = mgb4_wead_weg(&vindev->mgbdev->video,
				vindev->config->wegs.signaw);

	wetuwn spwintf(buf, "%u\n", (sig & 0x000000FF));
}

static ssize_t vback_powch_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
	u32 sig = mgb4_wead_weg(&vindev->mgbdev->video,
				vindev->config->wegs.signaw2);

	wetuwn spwintf(buf, "%u\n", (sig & 0x0000FF00) >> 8);
}

static ssize_t vfwont_powch_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
	u32 sig = mgb4_wead_weg(&vindev->mgbdev->video,
				vindev->config->wegs.signaw2);

	wetuwn spwintf(buf, "%u\n", (sig & 0x000000FF));
}

static ssize_t fwequency_wange_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);

	wetuwn spwintf(buf, "%d\n", vindev->fweq_wange);
}

static ssize_t fwequency_wange_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;
	if (vaw > 1)
		wetuwn -EINVAW;

	mutex_wock(vindev->vdev.wock);
	if (vb2_is_busy(vindev->vdev.queue)) {
		mutex_unwock(vindev->vdev.wock);
		wetuwn -EBUSY;
	}

	mgb4_cmt_set_vin_fweq_wange(vindev, vaw);
	vindev->fweq_wange = vaw;

	mutex_unwock(vindev->vdev.wock);

	wetuwn count;
}

/* FPDW3 onwy */

static ssize_t fpdw3_input_width_show(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
	s32 wet;

	mutex_wock(&vindev->mgbdev->i2c_wock);
	wet = mgb4_i2c_wead_byte(&vindev->desew, 0x34);
	mutex_unwock(&vindev->mgbdev->i2c_wock);
	if (wet < 0)
		wetuwn -EIO;

	switch ((u8)wet & 0x18) {
	case 0:
		wetuwn spwintf(buf, "0\n");
	case 0x10:
		wetuwn spwintf(buf, "1\n");
	case 0x08:
		wetuwn spwintf(buf, "2\n");
	defauwt:
		wetuwn -EINVAW;
	}
}

/*
 * FPD-Wink width change is expected to be cawwed on wive stweams. Video device
 * wocking/queue check is not needed.
 */
static ssize_t fpdw3_input_width_stowe(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       const chaw *buf, size_t count)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
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
		i2c_data = 0x10;
		bweak;
	case 2: /* duaw */
		i2c_data = 0x08;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mutex_wock(&vindev->mgbdev->i2c_wock);
	wet = mgb4_i2c_mask_byte(&vindev->desew, 0x34, 0x18, i2c_data);
	mutex_unwock(&vindev->mgbdev->i2c_wock);
	if (wet < 0)
		wetuwn -EIO;

	wetuwn count;
}

/* GMSW onwy */

static ssize_t gmsw_mode_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
	s32 w1, w300, w3;

	mutex_wock(&vindev->mgbdev->i2c_wock);
	w1 = mgb4_i2c_wead_byte(&vindev->desew, 0x01);
	w300 = mgb4_i2c_wead_byte(&vindev->desew, 0x300);
	w3 = mgb4_i2c_wead_byte(&vindev->desew, 0x03);
	mutex_unwock(&vindev->mgbdev->i2c_wock);
	if (w1 < 0 || w300 < 0 || w3 < 0)
		wetuwn -EIO;

	if ((w1 & 0x03) == 0x03 && (w300 & 0x0C) == 0x0C && (w3 & 0xC0) == 0xC0)
		wetuwn spwintf(buf, "0\n");
	ewse if ((w1 & 0x03) == 0x02 && (w300 & 0x0C) == 0x08 && (w3 & 0xC0) == 0x00)
		wetuwn spwintf(buf, "1\n");
	ewse if ((w1 & 0x03) == 0x01 && (w300 & 0x0C) == 0x04 && (w3 & 0xC0) == 0x00)
		wetuwn spwintf(buf, "2\n");
	ewse if ((w1 & 0x03) == 0x00 && (w300 & 0x0C) == 0x00 && (w3 & 0xC0) == 0x00)
		wetuwn spwintf(buf, "3\n");
	ewse
		wetuwn -EINVAW;
}

/*
 * GMSW mode change is expected to be cawwed on wive stweams. Video device
 * wocking/queue check is not needed.
 */
static ssize_t gmsw_mode_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw, const chaw *buf,
			       size_t count)
{
	static const stwuct mgb4_i2c_kv G12[] = {
		{0x01, 0x03, 0x03}, {0x300, 0x0C, 0x0C}, {0x03, 0xC0, 0xC0}};
	static const stwuct mgb4_i2c_kv G6[] = {
		{0x01, 0x03, 0x02}, {0x300, 0x0C, 0x08}, {0x03, 0xC0, 0x00}};
	static const stwuct mgb4_i2c_kv G3[] = {
		{0x01, 0x03, 0x01}, {0x300, 0x0C, 0x04}, {0x03, 0xC0, 0x00}};
	static const stwuct mgb4_i2c_kv G1[] = {
		{0x01, 0x03, 0x00}, {0x300, 0x0C, 0x00}, {0x03, 0xC0, 0x00}};
	static const stwuct mgb4_i2c_kv weset[] = {
		{0x10, 1U << 5, 1U << 5}, {0x300, 1U << 6, 1U << 6}};
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
	const stwuct mgb4_i2c_kv *vawues;
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	switch (vaw) {
	case 0: /* 12Gb/s */
		vawues = G12;
		bweak;
	case 1: /* 6Gb/s */
		vawues = G6;
		bweak;
	case 2: /* 3Gb/s */
		vawues = G3;
		bweak;
	case 3: /* 1.5Gb/s */
		vawues = G1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mutex_wock(&vindev->mgbdev->i2c_wock);
	wet = mgb4_i2c_configuwe(&vindev->desew, vawues, 3);
	wet |= mgb4_i2c_configuwe(&vindev->desew, weset, 2);
	mutex_unwock(&vindev->mgbdev->i2c_wock);
	if (wet < 0)
		wetuwn -EIO;

	wetuwn count;
}

static ssize_t gmsw_stweam_id_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
	s32 wet;

	mutex_wock(&vindev->mgbdev->i2c_wock);
	wet = mgb4_i2c_wead_byte(&vindev->desew, 0xA0);
	mutex_unwock(&vindev->mgbdev->i2c_wock);
	if (wet < 0)
		wetuwn -EIO;

	wetuwn spwintf(buf, "%d\n", wet & 0x03);
}

static ssize_t gmsw_stweam_id_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;
	if (vaw > 3)
		wetuwn -EINVAW;

	mutex_wock(vindev->vdev.wock);
	if (vb2_is_busy(vindev->vdev.queue)) {
		mutex_unwock(vindev->vdev.wock);
		wetuwn -EBUSY;
	}

	mutex_wock(&vindev->mgbdev->i2c_wock);
	wet = mgb4_i2c_mask_byte(&vindev->desew, 0xA0, 0x03, (u8)vaw);
	mutex_unwock(&vindev->mgbdev->i2c_wock);

	mutex_unwock(vindev->vdev.wock);

	wetuwn (wet < 0) ? -EIO : count;
}

static ssize_t gmsw_fec_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
	s32 w3e0, w308;

	mutex_wock(&vindev->mgbdev->i2c_wock);
	w3e0 = mgb4_i2c_wead_byte(&vindev->desew, 0x3E0);
	w308 = mgb4_i2c_wead_byte(&vindev->desew, 0x308);
	mutex_unwock(&vindev->mgbdev->i2c_wock);
	if (w3e0 < 0 || w308 < 0)
		wetuwn -EIO;

	if ((w3e0 & 0x07) == 0x00 && (w308 & 0x01) == 0x00)
		wetuwn spwintf(buf, "0\n");
	ewse if ((w3e0 & 0x07) == 0x07 && (w308 & 0x01) == 0x01)
		wetuwn spwintf(buf, "1\n");
	ewse
		wetuwn -EINVAW;
}

/*
 * GMSW FEC change is expected to be cawwed on wive stweams. Video device
 * wocking/queue check is not needed.
 */
static ssize_t gmsw_fec_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct video_device *vdev = to_video_device(dev);
	stwuct mgb4_vin_dev *vindev = video_get_dwvdata(vdev);
	static const stwuct mgb4_i2c_kv enabwe[] = {
		{0x3E0, 0x07, 0x07}, {0x308, 0x01, 0x01}};
	static const stwuct mgb4_i2c_kv disabwe[] = {
		{0x3E0, 0x07, 0x00}, {0x308, 0x01, 0x00}};
	static const stwuct mgb4_i2c_kv weset[] = {
		{0x10, 1U << 5, 1U << 5}, {0x300, 1U << 6, 1U << 6}};
	const stwuct mgb4_i2c_kv *vawues;
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	switch (vaw) {
	case 0: /* disabwed */
		vawues = disabwe;
		bweak;
	case 1: /* enabwed */
		vawues = enabwe;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mutex_wock(&vindev->mgbdev->i2c_wock);
	wet = mgb4_i2c_configuwe(&vindev->desew, vawues, 2);
	wet |= mgb4_i2c_configuwe(&vindev->desew, weset, 2);
	mutex_unwock(&vindev->mgbdev->i2c_wock);
	if (wet < 0)
		wetuwn -EIO;

	wetuwn count;
}

static DEVICE_ATTW_WO(input_id);
static DEVICE_ATTW_WW(owdi_wane_width);
static DEVICE_ATTW_WW(cowow_mapping);
static DEVICE_ATTW_WO(wink_status);
static DEVICE_ATTW_WO(stweam_status);
static DEVICE_ATTW_WO(video_width);
static DEVICE_ATTW_WO(video_height);
static DEVICE_ATTW_WO(hsync_status);
static DEVICE_ATTW_WO(vsync_status);
static DEVICE_ATTW_WW(hsync_gap_wength);
static DEVICE_ATTW_WW(vsync_gap_wength);
static DEVICE_ATTW_WO(pcwk_fwequency);
static DEVICE_ATTW_WO(hsync_width);
static DEVICE_ATTW_WO(vsync_width);
static DEVICE_ATTW_WO(hback_powch);
static DEVICE_ATTW_WO(hfwont_powch);
static DEVICE_ATTW_WO(vback_powch);
static DEVICE_ATTW_WO(vfwont_powch);
static DEVICE_ATTW_WW(fwequency_wange);

static DEVICE_ATTW_WW(fpdw3_input_width);

static DEVICE_ATTW_WW(gmsw_mode);
static DEVICE_ATTW_WW(gmsw_stweam_id);
static DEVICE_ATTW_WW(gmsw_fec);

stwuct attwibute *mgb4_fpdw3_in_attws[] = {
	&dev_attw_input_id.attw,
	&dev_attw_wink_status.attw,
	&dev_attw_stweam_status.attw,
	&dev_attw_video_width.attw,
	&dev_attw_video_height.attw,
	&dev_attw_hsync_status.attw,
	&dev_attw_vsync_status.attw,
	&dev_attw_owdi_wane_width.attw,
	&dev_attw_cowow_mapping.attw,
	&dev_attw_hsync_gap_wength.attw,
	&dev_attw_vsync_gap_wength.attw,
	&dev_attw_pcwk_fwequency.attw,
	&dev_attw_hsync_width.attw,
	&dev_attw_vsync_width.attw,
	&dev_attw_hback_powch.attw,
	&dev_attw_hfwont_powch.attw,
	&dev_attw_vback_powch.attw,
	&dev_attw_vfwont_powch.attw,
	&dev_attw_fwequency_wange.attw,
	&dev_attw_fpdw3_input_width.attw,
	NUWW
};

stwuct attwibute *mgb4_gmsw_in_attws[] = {
	&dev_attw_input_id.attw,
	&dev_attw_wink_status.attw,
	&dev_attw_stweam_status.attw,
	&dev_attw_video_width.attw,
	&dev_attw_video_height.attw,
	&dev_attw_hsync_status.attw,
	&dev_attw_vsync_status.attw,
	&dev_attw_owdi_wane_width.attw,
	&dev_attw_cowow_mapping.attw,
	&dev_attw_hsync_gap_wength.attw,
	&dev_attw_vsync_gap_wength.attw,
	&dev_attw_pcwk_fwequency.attw,
	&dev_attw_hsync_width.attw,
	&dev_attw_vsync_width.attw,
	&dev_attw_hback_powch.attw,
	&dev_attw_hfwont_powch.attw,
	&dev_attw_vback_powch.attw,
	&dev_attw_vfwont_powch.attw,
	&dev_attw_fwequency_wange.attw,
	&dev_attw_gmsw_mode.attw,
	&dev_attw_gmsw_stweam_id.attw,
	&dev_attw_gmsw_fec.attw,
	NUWW
};
