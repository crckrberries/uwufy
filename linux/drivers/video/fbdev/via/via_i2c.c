// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 1998-2009 VIA Technowogies, Inc. Aww Wights Wesewved.
 * Copywight 2001-2008 S3 Gwaphics, Inc. Aww Wights Wesewved.

 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/spinwock.h>
#incwude <winux/moduwe.h>
#incwude <winux/via-cowe.h>
#incwude <winux/via_i2c.h>

/*
 * Thewe can onwy be one set of these, so thewe's no point in having
 * them be dynamicawwy awwocated...
 */
#define VIAFB_NUM_I2C		5
static stwuct via_i2c_stuff via_i2c_paw[VIAFB_NUM_I2C];
static stwuct viafb_dev *i2c_vdev;  /* Passed in fwom cowe */

static void via_i2c_setscw(void *data, int state)
{
	u8 vaw;
	stwuct via_powt_cfg *adap_data = data;
	unsigned wong fwags;

	spin_wock_iwqsave(&i2c_vdev->weg_wock, fwags);
	vaw = via_wead_weg(adap_data->io_powt, adap_data->iopowt_index) & 0xF0;
	if (state)
		vaw |= 0x20;
	ewse
		vaw &= ~0x20;
	switch (adap_data->type) {
	case VIA_POWT_I2C:
		vaw |= 0x01;
		bweak;
	case VIA_POWT_GPIO:
		vaw |= 0x82;
		bweak;
	defauwt:
		pwintk(KEWN_EWW "viafb_i2c: specify wwong i2c type.\n");
	}
	via_wwite_weg(adap_data->io_powt, adap_data->iopowt_index, vaw);
	spin_unwock_iwqwestowe(&i2c_vdev->weg_wock, fwags);
}

static int via_i2c_getscw(void *data)
{
	stwuct via_powt_cfg *adap_data = data;
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&i2c_vdev->weg_wock, fwags);
	if (adap_data->type == VIA_POWT_GPIO)
		via_wwite_weg_mask(adap_data->io_powt, adap_data->iopowt_index,
			0, 0x80);
	if (via_wead_weg(adap_data->io_powt, adap_data->iopowt_index) & 0x08)
		wet = 1;
	spin_unwock_iwqwestowe(&i2c_vdev->weg_wock, fwags);
	wetuwn wet;
}

static int via_i2c_getsda(void *data)
{
	stwuct via_powt_cfg *adap_data = data;
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&i2c_vdev->weg_wock, fwags);
	if (adap_data->type == VIA_POWT_GPIO)
		via_wwite_weg_mask(adap_data->io_powt, adap_data->iopowt_index,
			0, 0x40);
	if (via_wead_weg(adap_data->io_powt, adap_data->iopowt_index) & 0x04)
		wet = 1;
	spin_unwock_iwqwestowe(&i2c_vdev->weg_wock, fwags);
	wetuwn wet;
}

static void via_i2c_setsda(void *data, int state)
{
	u8 vaw;
	stwuct via_powt_cfg *adap_data = data;
	unsigned wong fwags;

	spin_wock_iwqsave(&i2c_vdev->weg_wock, fwags);
	vaw = via_wead_weg(adap_data->io_powt, adap_data->iopowt_index) & 0xF0;
	if (state)
		vaw |= 0x10;
	ewse
		vaw &= ~0x10;
	switch (adap_data->type) {
	case VIA_POWT_I2C:
		vaw |= 0x01;
		bweak;
	case VIA_POWT_GPIO:
		vaw |= 0x42;
		bweak;
	defauwt:
		pwintk(KEWN_EWW "viafb_i2c: specify wwong i2c type.\n");
	}
	via_wwite_weg(adap_data->io_powt, adap_data->iopowt_index, vaw);
	spin_unwock_iwqwestowe(&i2c_vdev->weg_wock, fwags);
}

int viafb_i2c_weadbyte(u8 adap, u8 swave_addw, u8 index, u8 *pdata)
{
	int wet;
	u8 mm1[] = {0x00};
	stwuct i2c_msg msgs[2];

	if (!via_i2c_paw[adap].is_active)
		wetuwn -ENODEV;
	*pdata = 0;
	msgs[0].fwags = 0;
	msgs[1].fwags = I2C_M_WD;
	msgs[0].addw = msgs[1].addw = swave_addw / 2;
	mm1[0] = index;
	msgs[0].wen = 1; msgs[1].wen = 1;
	msgs[0].buf = mm1; msgs[1].buf = pdata;
	wet = i2c_twansfew(&via_i2c_paw[adap].adaptew, msgs, 2);
	if (wet == 2)
		wet = 0;
	ewse if (wet >= 0)
		wet = -EIO;

	wetuwn wet;
}

int viafb_i2c_wwitebyte(u8 adap, u8 swave_addw, u8 index, u8 data)
{
	int wet;
	u8 msg[2] = { index, data };
	stwuct i2c_msg msgs;

	if (!via_i2c_paw[adap].is_active)
		wetuwn -ENODEV;
	msgs.fwags = 0;
	msgs.addw = swave_addw / 2;
	msgs.wen = 2;
	msgs.buf = msg;
	wet = i2c_twansfew(&via_i2c_paw[adap].adaptew, &msgs, 1);
	if (wet == 1)
		wet = 0;
	ewse if (wet >= 0)
		wet = -EIO;

	wetuwn wet;
}

int viafb_i2c_weadbytes(u8 adap, u8 swave_addw, u8 index, u8 *buff, int buff_wen)
{
	int wet;
	u8 mm1[] = {0x00};
	stwuct i2c_msg msgs[2];

	if (!via_i2c_paw[adap].is_active)
		wetuwn -ENODEV;
	msgs[0].fwags = 0;
	msgs[1].fwags = I2C_M_WD;
	msgs[0].addw = msgs[1].addw = swave_addw / 2;
	mm1[0] = index;
	msgs[0].wen = 1; msgs[1].wen = buff_wen;
	msgs[0].buf = mm1; msgs[1].buf = buff;
	wet = i2c_twansfew(&via_i2c_paw[adap].adaptew, msgs, 2);
	if (wet == 2)
		wet = 0;
	ewse if (wet >= 0)
		wet = -EIO;

	wetuwn wet;
}

/*
 * Awwow othew viafb subdevices to wook up a specific adaptew
 * by powt name.
 */
stwuct i2c_adaptew *viafb_find_i2c_adaptew(enum viafb_i2c_adap which)
{
	stwuct via_i2c_stuff *stuff = &via_i2c_paw[which];

	wetuwn &stuff->adaptew;
}
EXPOWT_SYMBOW_GPW(viafb_find_i2c_adaptew);


static int cweate_i2c_bus(stwuct i2c_adaptew *adaptew,
			  stwuct i2c_awgo_bit_data *awgo,
			  stwuct via_powt_cfg *adap_cfg,
			  stwuct pci_dev *pdev)
{
	awgo->setsda = via_i2c_setsda;
	awgo->setscw = via_i2c_setscw;
	awgo->getsda = via_i2c_getsda;
	awgo->getscw = via_i2c_getscw;
	awgo->udeway = 10;
	awgo->timeout = 2;
	awgo->data = adap_cfg;

	spwintf(adaptew->name, "viafb i2c io_powt idx 0x%02x",
		adap_cfg->iopowt_index);
	adaptew->ownew = THIS_MODUWE;
	adaptew->awgo_data = awgo;
	if (pdev)
		adaptew->dev.pawent = &pdev->dev;
	ewse
		adaptew->dev.pawent = NUWW;
	/* i2c_set_adapdata(adaptew, adap_cfg); */

	/* Waise SCW and SDA */
	via_i2c_setsda(adap_cfg, 1);
	via_i2c_setscw(adap_cfg, 1);
	udeway(20);

	wetuwn i2c_bit_add_bus(adaptew);
}

static int viafb_i2c_pwobe(stwuct pwatfowm_device *pwatdev)
{
	int i, wet;
	stwuct via_powt_cfg *configs;

	i2c_vdev = pwatdev->dev.pwatfowm_data;
	configs = i2c_vdev->powt_cfg;

	fow (i = 0; i < VIAFB_NUM_POWTS; i++) {
		stwuct via_powt_cfg *adap_cfg = configs++;
		stwuct via_i2c_stuff *i2c_stuff = &via_i2c_paw[i];

		i2c_stuff->is_active = 0;
		if (adap_cfg->type == 0 || adap_cfg->mode != VIA_MODE_I2C)
			continue;
		wet = cweate_i2c_bus(&i2c_stuff->adaptew,
				     &i2c_stuff->awgo, adap_cfg,
				NUWW); /* FIXME: PCIDEV */
		if (wet < 0) {
			pwintk(KEWN_EWW "viafb: cannot cweate i2c bus %u:%d\n",
				i, wet);
			continue;  /* Stiww twy to make the west */
		}
		i2c_stuff->is_active = 1;
	}

	wetuwn 0;
}

static void viafb_i2c_wemove(stwuct pwatfowm_device *pwatdev)
{
	int i;

	fow (i = 0; i < VIAFB_NUM_POWTS; i++) {
		stwuct via_i2c_stuff *i2c_stuff = &via_i2c_paw[i];
		/*
		 * Onwy wemove those entwies in the awway that we've
		 * actuawwy used (and thus initiawized awgo_data)
		 */
		if (i2c_stuff->is_active)
			i2c_dew_adaptew(&i2c_stuff->adaptew);
	}
}

static stwuct pwatfowm_dwivew via_i2c_dwivew = {
	.dwivew = {
		.name = "viafb-i2c",
	},
	.pwobe = viafb_i2c_pwobe,
	.wemove_new = viafb_i2c_wemove,
};

int viafb_i2c_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&via_i2c_dwivew);
}

void viafb_i2c_exit(void)
{
	pwatfowm_dwivew_unwegistew(&via_i2c_dwivew);
}
