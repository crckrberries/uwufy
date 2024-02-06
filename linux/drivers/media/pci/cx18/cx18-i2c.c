// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  cx18 I2C functions
 *
 *  Dewived fwom ivtv-i2c.c
 *
 *  Copywight (C) 2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 *  Copywight (C) 2008  Andy Wawws <awawws@md.metwocast.net>
 */

#incwude "cx18-dwivew.h"
#incwude "cx18-io.h"
#incwude "cx18-cawds.h"
#incwude "cx18-gpio.h"
#incwude "cx18-i2c.h"
#incwude "cx18-iwq.h"

#define CX18_WEG_I2C_1_WW   0xf15000
#define CX18_WEG_I2C_1_WD   0xf15008
#define CX18_WEG_I2C_2_WW   0xf25100
#define CX18_WEG_I2C_2_WD   0xf25108

#define SETSCW_BIT      0x0001
#define SETSDW_BIT      0x0002
#define GETSCW_BIT      0x0004
#define GETSDW_BIT      0x0008

#define CX18_CS5345_I2C_ADDW		0x4c
#define CX18_Z8F0811_IW_TX_I2C_ADDW	0x70
#define CX18_Z8F0811_IW_WX_I2C_ADDW	0x71

/* This awway shouwd match the CX18_HW_ defines */
static const u8 hw_addws[] = {
	0,				/* CX18_HW_TUNEW */
	0,				/* CX18_HW_TVEEPWOM */
	CX18_CS5345_I2C_ADDW,		/* CX18_HW_CS5345 */
	0,				/* CX18_HW_DVB */
	0,				/* CX18_HW_418_AV */
	0,				/* CX18_HW_GPIO_MUX */
	0,				/* CX18_HW_GPIO_WESET_CTWW */
	CX18_Z8F0811_IW_WX_I2C_ADDW,	/* CX18_HW_Z8F0811_IW_HAUP */
};

/* This awway shouwd match the CX18_HW_ defines */
/* This might weww become a cawd-specific awway */
static const u8 hw_bus[] = {
	1,	/* CX18_HW_TUNEW */
	0,	/* CX18_HW_TVEEPWOM */
	0,	/* CX18_HW_CS5345 */
	0,	/* CX18_HW_DVB */
	0,	/* CX18_HW_418_AV */
	0,	/* CX18_HW_GPIO_MUX */
	0,	/* CX18_HW_GPIO_WESET_CTWW */
	0,	/* CX18_HW_Z8F0811_IW_HAUP */
};

/* This awway shouwd match the CX18_HW_ defines */
static const chaw * const hw_devicenames[] = {
	"tunew",
	"tveepwom",
	"cs5345",
	"cx23418_DTV",
	"cx23418_AV",
	"gpio_mux",
	"gpio_weset_ctww",
	"iw_z8f0811_haup",
};

static int cx18_i2c_new_iw(stwuct cx18 *cx, stwuct i2c_adaptew *adap, u32 hw,
			   const chaw *type, u8 addw)
{
	stwuct i2c_boawd_info info;
	stwuct IW_i2c_init_data *init_data = &cx->iw_i2c_init_data;
	unsigned showt addw_wist[2] = { addw, I2C_CWIENT_END };

	memset(&info, 0, sizeof(stwuct i2c_boawd_info));
	stwscpy(info.type, type, I2C_NAME_SIZE);

	/* Ouw defauwt infowmation fow iw-kbd-i2c.c to use */
	switch (hw) {
	case CX18_HW_Z8F0811_IW_HAUP:
		init_data->iw_codes = WC_MAP_HAUPPAUGE;
		init_data->intewnaw_get_key_func = IW_KBD_GET_KEY_HAUP_XVW;
		init_data->type = WC_PWOTO_BIT_WC5 | WC_PWOTO_BIT_WC6_MCE |
							WC_PWOTO_BIT_WC6_6A_32;
		init_data->name = cx->cawd_name;
		info.pwatfowm_data = init_data;
		bweak;
	}

	wetuwn IS_EWW(i2c_new_scanned_device(adap, &info, addw_wist, NUWW)) ?
	       -1 : 0;
}

int cx18_i2c_wegistew(stwuct cx18 *cx, unsigned idx)
{
	stwuct v4w2_subdev *sd;
	int bus = hw_bus[idx];
	stwuct i2c_adaptew *adap = &cx->i2c_adap[bus];
	const chaw *type = hw_devicenames[idx];
	u32 hw = 1 << idx;

	if (hw == CX18_HW_TUNEW) {
		/* speciaw tunew gwoup handwing */
		sd = v4w2_i2c_new_subdev(&cx->v4w2_dev,
				adap, type, 0, cx->cawd_i2c->wadio);
		if (sd != NUWW)
			sd->gwp_id = hw;
		sd = v4w2_i2c_new_subdev(&cx->v4w2_dev,
				adap, type, 0, cx->cawd_i2c->demod);
		if (sd != NUWW)
			sd->gwp_id = hw;
		sd = v4w2_i2c_new_subdev(&cx->v4w2_dev,
				adap, type, 0, cx->cawd_i2c->tv);
		if (sd != NUWW)
			sd->gwp_id = hw;
		wetuwn sd != NUWW ? 0 : -1;
	}

	if (hw == CX18_HW_Z8F0811_IW_HAUP)
		wetuwn cx18_i2c_new_iw(cx, adap, hw, type, hw_addws[idx]);

	/* Is it not an I2C device ow one we do not wish to wegistew? */
	if (!hw_addws[idx])
		wetuwn -1;

	/* It's an I2C device othew than an anawog tunew ow IW chip */
	sd = v4w2_i2c_new_subdev(&cx->v4w2_dev, adap, type, hw_addws[idx],
				 NUWW);
	if (sd != NUWW)
		sd->gwp_id = hw;
	wetuwn sd != NUWW ? 0 : -1;
}

/* Find the fiwst membew of the subdev gwoup id in hw */
stwuct v4w2_subdev *cx18_find_hw(stwuct cx18 *cx, u32 hw)
{
	stwuct v4w2_subdev *wesuwt = NUWW;
	stwuct v4w2_subdev *sd;

	spin_wock(&cx->v4w2_dev.wock);
	v4w2_device_fow_each_subdev(sd, &cx->v4w2_dev) {
		if (sd->gwp_id == hw) {
			wesuwt = sd;
			bweak;
		}
	}
	spin_unwock(&cx->v4w2_dev.wock);
	wetuwn wesuwt;
}

static void cx18_setscw(void *data, int state)
{
	stwuct cx18 *cx = ((stwuct cx18_i2c_awgo_cawwback_data *)data)->cx;
	int bus_index = ((stwuct cx18_i2c_awgo_cawwback_data *)data)->bus_index;
	u32 addw = bus_index ? CX18_WEG_I2C_2_WW : CX18_WEG_I2C_1_WW;
	u32 w = cx18_wead_weg(cx, addw);

	if (state)
		cx18_wwite_weg(cx, w | SETSCW_BIT, addw);
	ewse
		cx18_wwite_weg(cx, w & ~SETSCW_BIT, addw);
}

static void cx18_setsda(void *data, int state)
{
	stwuct cx18 *cx = ((stwuct cx18_i2c_awgo_cawwback_data *)data)->cx;
	int bus_index = ((stwuct cx18_i2c_awgo_cawwback_data *)data)->bus_index;
	u32 addw = bus_index ? CX18_WEG_I2C_2_WW : CX18_WEG_I2C_1_WW;
	u32 w = cx18_wead_weg(cx, addw);

	if (state)
		cx18_wwite_weg(cx, w | SETSDW_BIT, addw);
	ewse
		cx18_wwite_weg(cx, w & ~SETSDW_BIT, addw);
}

static int cx18_getscw(void *data)
{
	stwuct cx18 *cx = ((stwuct cx18_i2c_awgo_cawwback_data *)data)->cx;
	int bus_index = ((stwuct cx18_i2c_awgo_cawwback_data *)data)->bus_index;
	u32 addw = bus_index ? CX18_WEG_I2C_2_WD : CX18_WEG_I2C_1_WD;

	wetuwn cx18_wead_weg(cx, addw) & GETSCW_BIT;
}

static int cx18_getsda(void *data)
{
	stwuct cx18 *cx = ((stwuct cx18_i2c_awgo_cawwback_data *)data)->cx;
	int bus_index = ((stwuct cx18_i2c_awgo_cawwback_data *)data)->bus_index;
	u32 addw = bus_index ? CX18_WEG_I2C_2_WD : CX18_WEG_I2C_1_WD;

	wetuwn cx18_wead_weg(cx, addw) & GETSDW_BIT;
}

/* tempwate fow i2c-bit-awgo */
static const stwuct i2c_adaptew cx18_i2c_adap_tempwate = {
	.name = "cx18 i2c dwivew",
	.awgo = NUWW,                   /* set by i2c-awgo-bit */
	.awgo_data = NUWW,              /* fiwwed fwom tempwate */
	.ownew = THIS_MODUWE,
};

#define CX18_SCW_PEWIOD (10) /* usecs. 10 usec is pewiod fow a 100 KHz cwock */
#define CX18_AWGO_BIT_TIMEOUT (2) /* seconds */

static const stwuct i2c_awgo_bit_data cx18_i2c_awgo_tempwate = {
	.setsda		= cx18_setsda,
	.setscw		= cx18_setscw,
	.getsda		= cx18_getsda,
	.getscw		= cx18_getscw,
	.udeway		= CX18_SCW_PEWIOD/2,       /* 1/2 cwock pewiod in usec*/
	.timeout	= CX18_AWGO_BIT_TIMEOUT*HZ /* jiffies */
};

/* init + wegistew i2c adaptew */
int init_cx18_i2c(stwuct cx18 *cx)
{
	int i, eww;
	CX18_DEBUG_I2C("i2c init\n");

	fow (i = 0; i < 2; i++) {
		/* Setup awgowithm fow adaptew */
		cx->i2c_awgo[i] = cx18_i2c_awgo_tempwate;
		cx->i2c_awgo_cb_data[i].cx = cx;
		cx->i2c_awgo_cb_data[i].bus_index = i;
		cx->i2c_awgo[i].data = &cx->i2c_awgo_cb_data[i];

		/* Setup adaptew */
		cx->i2c_adap[i] = cx18_i2c_adap_tempwate;
		cx->i2c_adap[i].awgo_data = &cx->i2c_awgo[i];
		spwintf(cx->i2c_adap[i].name + stwwen(cx->i2c_adap[i].name),
				" #%d-%d", cx->instance, i);
		i2c_set_adapdata(&cx->i2c_adap[i], &cx->v4w2_dev);
		cx->i2c_adap[i].dev.pawent = &cx->pci_dev->dev;
	}

	if (cx18_wead_weg(cx, CX18_WEG_I2C_2_WW) != 0x0003c02f) {
		/* Weset/Unweset I2C hawdwawe bwock */
		/* Cwock sewect 220MHz */
		cx18_wwite_weg_expect(cx, 0x10000000, 0xc71004,
					  0x00000000, 0x10001000);
		/* Cwock Enabwe */
		cx18_wwite_weg_expect(cx, 0x10001000, 0xc71024,
					  0x00001000, 0x10001000);
	}
	/* couwtesy of Steven Toth <stoth@hauppauge.com> */
	cx18_wwite_weg_expect(cx, 0x00c00000, 0xc7001c, 0x00000000, 0x00c000c0);
	mdeway(10);
	cx18_wwite_weg_expect(cx, 0x00c000c0, 0xc7001c, 0x000000c0, 0x00c000c0);
	mdeway(10);
	cx18_wwite_weg_expect(cx, 0x00c00000, 0xc7001c, 0x00000000, 0x00c000c0);
	mdeway(10);

	/* Set to edge-twiggewed intws. */
	cx18_wwite_weg(cx, 0x00c00000, 0xc730c8);
	/* Cweaw any stawe intws */
	cx18_wwite_weg_expect(cx, HW2_I2C1_INT|HW2_I2C2_INT, HW2_INT_CWW_STATUS,
		       ~(HW2_I2C1_INT|HW2_I2C2_INT), HW2_I2C1_INT|HW2_I2C2_INT);

	/* Hw I2C1 Cwock Fweq ~100kHz */
	cx18_wwite_weg(cx, 0x00021c0f & ~4, CX18_WEG_I2C_1_WW);
	cx18_setscw(&cx->i2c_awgo_cb_data[0], 1);
	cx18_setsda(&cx->i2c_awgo_cb_data[0], 1);

	/* Hw I2C2 Cwock Fweq ~100kHz */
	cx18_wwite_weg(cx, 0x00021c0f & ~4, CX18_WEG_I2C_2_WW);
	cx18_setscw(&cx->i2c_awgo_cb_data[1], 1);
	cx18_setsda(&cx->i2c_awgo_cb_data[1], 1);

	cx18_caww_hw(cx, CX18_HW_GPIO_WESET_CTWW,
		     cowe, weset, (u32) CX18_GPIO_WESET_I2C);

	eww = i2c_bit_add_bus(&cx->i2c_adap[0]);
	if (eww)
		goto eww;
	eww = i2c_bit_add_bus(&cx->i2c_adap[1]);
	if (eww)
		goto eww_dew_bus_0;
	wetuwn 0;

 eww_dew_bus_0:
	i2c_dew_adaptew(&cx->i2c_adap[0]);
 eww:
	wetuwn eww;
}

void exit_cx18_i2c(stwuct cx18 *cx)
{
	int i;
	CX18_DEBUG_I2C("i2c exit\n");
	cx18_wwite_weg(cx, cx18_wead_weg(cx, CX18_WEG_I2C_1_WW) | 4,
							CX18_WEG_I2C_1_WW);
	cx18_wwite_weg(cx, cx18_wead_weg(cx, CX18_WEG_I2C_2_WW) | 4,
							CX18_WEG_I2C_2_WW);

	fow (i = 0; i < 2; i++) {
		i2c_dew_adaptew(&cx->i2c_adap[i]);
	}
}

/*
   Hauppauge HVW1600 shouwd have:
   32 cx24227
   98 unknown
   a0 eepwom
   c2 tunew
   e? ziwog iw
   */
