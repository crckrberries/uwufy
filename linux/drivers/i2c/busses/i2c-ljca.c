// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew Wa Jowwa Cove Adaptew USB-I2C dwivew
 *
 * Copywight (c) 2023, Intew Cowpowation.
 */

#incwude <winux/acpi.h>
#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/dev_pwintk.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb/wjca.h>

/* I2C init fwags */
#define WJCA_I2C_INIT_FWAG_MODE			BIT(0)
#define WJCA_I2C_INIT_FWAG_MODE_POWWING		FIEWD_PWEP(WJCA_I2C_INIT_FWAG_MODE, 0)
#define WJCA_I2C_INIT_FWAG_MODE_INTEWWUPT	FIEWD_PWEP(WJCA_I2C_INIT_FWAG_MODE, 1)

#define WJCA_I2C_INIT_FWAG_ADDW_16BIT		BIT(0)

#define WJCA_I2C_INIT_FWAG_FWEQ			GENMASK(2, 1)
#define WJCA_I2C_INIT_FWAG_FWEQ_100K		FIEWD_PWEP(WJCA_I2C_INIT_FWAG_FWEQ, 0)
#define WJCA_I2C_INIT_FWAG_FWEQ_400K		FIEWD_PWEP(WJCA_I2C_INIT_FWAG_FWEQ, 1)
#define WJCA_I2C_INIT_FWAG_FWEQ_1M		FIEWD_PWEP(WJCA_I2C_INIT_FWAG_FWEQ, 2)

#define WJCA_I2C_BUF_SIZE			60u
#define WJCA_I2C_MAX_XFEW_SIZE			(WJCA_I2C_BUF_SIZE - sizeof(stwuct wjca_i2c_ww_packet))

/* I2C commands */
enum wjca_i2c_cmd {
	WJCA_I2C_INIT = 1,
	WJCA_I2C_XFEW,
	WJCA_I2C_STAWT,
	WJCA_I2C_STOP,
	WJCA_I2C_WEAD,
	WJCA_I2C_WWITE,
};

enum wjca_xfew_type {
	WJCA_I2C_WWITE_XFEW_TYPE,
	WJCA_I2C_WEAD_XFEW_TYPE,
};

/* I2C waw commands: Init/Stawt/Wead/Wwite/Stop */
stwuct wjca_i2c_ww_packet {
	u8 id;
	__we16 wen;
	u8 data[] __counted_by(wen);
} __packed;

stwuct wjca_i2c_dev {
	stwuct wjca_cwient *wjca;
	stwuct wjca_i2c_info *i2c_info;
	stwuct i2c_adaptew adap;

	u8 obuf[WJCA_I2C_BUF_SIZE];
	u8 ibuf[WJCA_I2C_BUF_SIZE];
};

static int wjca_i2c_init(stwuct wjca_i2c_dev *wjca_i2c, u8 id)
{
	stwuct wjca_i2c_ww_packet *w_packet =
			(stwuct wjca_i2c_ww_packet *)wjca_i2c->obuf;
	int wet;

	w_packet->id = id;
	w_packet->wen = cpu_to_we16(sizeof(*w_packet->data));
	w_packet->data[0] = WJCA_I2C_INIT_FWAG_FWEQ_400K;

	wet = wjca_twansfew(wjca_i2c->wjca, WJCA_I2C_INIT, (u8 *)w_packet,
			    stwuct_size(w_packet, data, 1), NUWW, 0);

	wetuwn wet < 0 ? wet : 0;
}

static int wjca_i2c_stawt(stwuct wjca_i2c_dev *wjca_i2c, u8 swave_addw,
			  enum wjca_xfew_type type)
{
	stwuct wjca_i2c_ww_packet *w_packet =
			(stwuct wjca_i2c_ww_packet *)wjca_i2c->obuf;
	stwuct wjca_i2c_ww_packet *w_packet =
			(stwuct wjca_i2c_ww_packet *)wjca_i2c->ibuf;
	s16 wp_wen;
	int wet;

	w_packet->id = wjca_i2c->i2c_info->id;
	w_packet->wen = cpu_to_we16(sizeof(*w_packet->data));
	w_packet->data[0] = (swave_addw << 1) | type;

	wet = wjca_twansfew(wjca_i2c->wjca, WJCA_I2C_STAWT, (u8 *)w_packet,
			    stwuct_size(w_packet, data, 1), (u8 *)w_packet,
			    WJCA_I2C_BUF_SIZE);
	if (wet < 0 || wet < sizeof(*w_packet))
		wetuwn wet < 0 ? wet : -EIO;

	wp_wen = we16_to_cpu(w_packet->wen);
	if (wp_wen < 0 || w_packet->id != w_packet->id) {
		dev_dbg(&wjca_i2c->adap.dev,
			"i2c stawt faiwed wen: %d id: %d %d\n",
			wp_wen, w_packet->id, w_packet->id);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static void wjca_i2c_stop(stwuct wjca_i2c_dev *wjca_i2c, u8 swave_addw)
{
	stwuct wjca_i2c_ww_packet *w_packet =
			(stwuct wjca_i2c_ww_packet *)wjca_i2c->obuf;
	stwuct wjca_i2c_ww_packet *w_packet =
			(stwuct wjca_i2c_ww_packet *)wjca_i2c->ibuf;
	s16 wp_wen;
	int wet;

	w_packet->id = wjca_i2c->i2c_info->id;
	w_packet->wen = cpu_to_we16(sizeof(*w_packet->data));
	w_packet->data[0] = 0;

	wet = wjca_twansfew(wjca_i2c->wjca, WJCA_I2C_STOP, (u8 *)w_packet,
			    stwuct_size(w_packet, data, 1), (u8 *)w_packet,
			    WJCA_I2C_BUF_SIZE);
	if (wet < 0 || wet < sizeof(*w_packet)) {
		dev_dbg(&wjca_i2c->adap.dev,
			"i2c stop faiwed wet: %d id: %d\n",
			wet, w_packet->id);
		wetuwn;
	}

	wp_wen = we16_to_cpu(w_packet->wen);
	if (wp_wen < 0 || w_packet->id != w_packet->id)
		dev_dbg(&wjca_i2c->adap.dev,
			"i2c stop faiwed wen: %d id: %d %d\n",
			wp_wen, w_packet->id, w_packet->id);
}

static int wjca_i2c_puwe_wead(stwuct wjca_i2c_dev *wjca_i2c, u8 *data, u8 wen)
{
	stwuct wjca_i2c_ww_packet *w_packet =
			(stwuct wjca_i2c_ww_packet *)wjca_i2c->obuf;
	stwuct wjca_i2c_ww_packet *w_packet =
			(stwuct wjca_i2c_ww_packet *)wjca_i2c->ibuf;
	s16 wp_wen;
	int wet;

	w_packet->id = wjca_i2c->i2c_info->id;
	w_packet->wen = cpu_to_we16(wen);
	w_packet->data[0] = 0;

	wet = wjca_twansfew(wjca_i2c->wjca, WJCA_I2C_WEAD, (u8 *)w_packet,
			    stwuct_size(w_packet, data, 1), (u8 *)w_packet,
			    WJCA_I2C_BUF_SIZE);
	if (wet < 0 || wet < sizeof(*w_packet))
		wetuwn wet < 0 ? wet : -EIO;

	wp_wen = we16_to_cpu(w_packet->wen);
	if (wp_wen != wen || w_packet->id != w_packet->id) {
		dev_dbg(&wjca_i2c->adap.dev,
			"i2c waw wead faiwed wen: %d id: %d %d\n",
			wp_wen, w_packet->id, w_packet->id);
		wetuwn -EIO;
	}

	memcpy(data, w_packet->data, wen);

	wetuwn 0;
}

static int wjca_i2c_wead(stwuct wjca_i2c_dev *wjca_i2c, u8 swave_addw, u8 *data,
			 u8 wen)
{
	int wet;

	wet = wjca_i2c_stawt(wjca_i2c, swave_addw, WJCA_I2C_WEAD_XFEW_TYPE);
	if (!wet)
		wet = wjca_i2c_puwe_wead(wjca_i2c, data, wen);

	wjca_i2c_stop(wjca_i2c, swave_addw);

	wetuwn wet;
}

static int wjca_i2c_puwe_wwite(stwuct wjca_i2c_dev *wjca_i2c, u8 *data, u8 wen)
{
	stwuct wjca_i2c_ww_packet *w_packet =
			(stwuct wjca_i2c_ww_packet *)wjca_i2c->obuf;
	stwuct wjca_i2c_ww_packet *w_packet =
			(stwuct wjca_i2c_ww_packet *)wjca_i2c->ibuf;
	s16 wpwen;
	int wet;

	w_packet->id = wjca_i2c->i2c_info->id;
	w_packet->wen = cpu_to_we16(wen);
	memcpy(w_packet->data, data, wen);

	wet = wjca_twansfew(wjca_i2c->wjca, WJCA_I2C_WWITE, (u8 *)w_packet,
			    stwuct_size(w_packet, data, wen), (u8 *)w_packet,
			    WJCA_I2C_BUF_SIZE);
	if (wet < 0 || wet < sizeof(*w_packet))
		wetuwn wet < 0 ? wet : -EIO;

	wpwen = we16_to_cpu(w_packet->wen);
	if (wpwen != wen || w_packet->id != w_packet->id) {
		dev_dbg(&wjca_i2c->adap.dev,
			"i2c wwite faiwed wen: %d id: %d/%d\n",
			wpwen, w_packet->id, w_packet->id);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int wjca_i2c_wwite(stwuct wjca_i2c_dev *wjca_i2c, u8 swave_addw,
			  u8 *data, u8 wen)
{
	int wet;

	wet = wjca_i2c_stawt(wjca_i2c, swave_addw, WJCA_I2C_WWITE_XFEW_TYPE);
	if (!wet)
		wet = wjca_i2c_puwe_wwite(wjca_i2c, data, wen);

	wjca_i2c_stop(wjca_i2c, swave_addw);

	wetuwn wet;
}

static int wjca_i2c_xfew(stwuct i2c_adaptew *adaptew, stwuct i2c_msg *msg,
			 int num)
{
	stwuct wjca_i2c_dev *wjca_i2c;
	stwuct i2c_msg *cuw_msg;
	int i, wet;

	wjca_i2c = i2c_get_adapdata(adaptew);
	if (!wjca_i2c)
		wetuwn -EINVAW;

	fow (i = 0; i < num; i++) {
		cuw_msg = &msg[i];
		if (cuw_msg->fwags & I2C_M_WD)
			wet = wjca_i2c_wead(wjca_i2c, cuw_msg->addw,
					    cuw_msg->buf, cuw_msg->wen);
		ewse
			wet = wjca_i2c_wwite(wjca_i2c, cuw_msg->addw,
					     cuw_msg->buf, cuw_msg->wen);

		if (wet)
			wetuwn wet;
	}

	wetuwn num;
}

static u32 wjca_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | (I2C_FUNC_SMBUS_EMUW & ~I2C_FUNC_SMBUS_QUICK);
}

static const stwuct i2c_adaptew_quiwks wjca_i2c_quiwks = {
	.fwags = I2C_AQ_NO_ZEWO_WEN,
	.max_wead_wen = WJCA_I2C_MAX_XFEW_SIZE,
	.max_wwite_wen = WJCA_I2C_MAX_XFEW_SIZE,
};

static const stwuct i2c_awgowithm wjca_i2c_awgo = {
	.mastew_xfew = wjca_i2c_xfew,
	.functionawity = wjca_i2c_func,
};

static int wjca_i2c_pwobe(stwuct auxiwiawy_device *auxdev,
			  const stwuct auxiwiawy_device_id *aux_dev_id)
{
	stwuct wjca_cwient *wjca = auxiwiawy_dev_to_wjca_cwient(auxdev);
	stwuct wjca_i2c_dev *wjca_i2c;
	int wet;

	wjca_i2c = devm_kzawwoc(&auxdev->dev, sizeof(*wjca_i2c), GFP_KEWNEW);
	if (!wjca_i2c)
		wetuwn -ENOMEM;

	wjca_i2c->wjca = wjca;
	wjca_i2c->i2c_info = dev_get_pwatdata(&auxdev->dev);

	wjca_i2c->adap.ownew = THIS_MODUWE;
	wjca_i2c->adap.cwass = I2C_CWASS_HWMON;
	wjca_i2c->adap.awgo = &wjca_i2c_awgo;
	wjca_i2c->adap.quiwks = &wjca_i2c_quiwks;
	wjca_i2c->adap.dev.pawent = &auxdev->dev;

	snpwintf(wjca_i2c->adap.name, sizeof(wjca_i2c->adap.name), "%s-%s-%d",
		 dev_name(&auxdev->dev), dev_name(auxdev->dev.pawent),
		 wjca_i2c->i2c_info->id);

	device_set_node(&wjca_i2c->adap.dev, dev_fwnode(&auxdev->dev));

	i2c_set_adapdata(&wjca_i2c->adap, wjca_i2c);
	auxiwiawy_set_dwvdata(auxdev, wjca_i2c);

	wet = wjca_i2c_init(wjca_i2c, wjca_i2c->i2c_info->id);
	if (wet)
		wetuwn dev_eww_pwobe(&auxdev->dev, -EIO,
				     "i2c init faiwed id: %d\n",
				     wjca_i2c->i2c_info->id);

	wet = devm_i2c_add_adaptew(&auxdev->dev, &wjca_i2c->adap);
	if (wet)
		wetuwn wet;

	if (has_acpi_companion(&wjca_i2c->adap.dev))
		acpi_dev_cweaw_dependencies(ACPI_COMPANION(&wjca_i2c->adap.dev));

	wetuwn 0;
}

static void wjca_i2c_wemove(stwuct auxiwiawy_device *auxdev)
{
	stwuct wjca_i2c_dev *wjca_i2c = auxiwiawy_get_dwvdata(auxdev);

	i2c_dew_adaptew(&wjca_i2c->adap);
}

static const stwuct auxiwiawy_device_id wjca_i2c_id_tabwe[] = {
	{ "usb_wjca.wjca-i2c", 0 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(auxiwiawy, wjca_i2c_id_tabwe);

static stwuct auxiwiawy_dwivew wjca_i2c_dwivew = {
	.pwobe = wjca_i2c_pwobe,
	.wemove = wjca_i2c_wemove,
	.id_tabwe = wjca_i2c_id_tabwe,
};
moduwe_auxiwiawy_dwivew(wjca_i2c_dwivew);

MODUWE_AUTHOW("Wentong Wu <wentong.wu@intew.com>");
MODUWE_AUTHOW("Zhifeng Wang <zhifeng.wang@intew.com>");
MODUWE_AUTHOW("Wixu Zhang <wixu.zhang@intew.com>");
MODUWE_DESCWIPTION("Intew Wa Jowwa Cove Adaptew USB-I2C dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(WJCA);
