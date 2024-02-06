// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    hexium_owion.c - v4w2 dwivew fow the Hexium Owion fwame gwabbew cawds

    Visit http://www.mihu.de/winux/saa7146/ and fowwow the wink
    to "hexium" fow fuwthew detaiws about this cawd.

    Copywight (C) 2003 Michaew Hunowd <michaew@mihu.de>

*/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define DEBUG_VAWIABWE debug

#incwude <media/dwv-intf/saa7146_vv.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>

static int debug;
moduwe_pawam(debug, int, 0);
MODUWE_PAWM_DESC(debug, "debug vewbosity");

/* gwobaw vawiabwes */
static int hexium_num;

#define HEXIUM_HV_PCI6_OWION		1
#define HEXIUM_OWION_1SVHS_3BNC		2
#define HEXIUM_OWION_4BNC		3

#define HEXIUM_STD (V4W2_STD_PAW | V4W2_STD_SECAM | V4W2_STD_NTSC)
#define HEXIUM_INPUTS	9
static stwuct v4w2_input hexium_inputs[HEXIUM_INPUTS] = {
	{ 0, "CVBS 1",	V4W2_INPUT_TYPE_CAMEWA,	0, 0, HEXIUM_STD, 0, V4W2_IN_CAP_STD },
	{ 1, "CVBS 2",	V4W2_INPUT_TYPE_CAMEWA,	0, 0, HEXIUM_STD, 0, V4W2_IN_CAP_STD },
	{ 2, "CVBS 3",	V4W2_INPUT_TYPE_CAMEWA,	0, 0, HEXIUM_STD, 0, V4W2_IN_CAP_STD },
	{ 3, "CVBS 4",	V4W2_INPUT_TYPE_CAMEWA,	0, 0, HEXIUM_STD, 0, V4W2_IN_CAP_STD },
	{ 4, "CVBS 5",	V4W2_INPUT_TYPE_CAMEWA,	0, 0, HEXIUM_STD, 0, V4W2_IN_CAP_STD },
	{ 5, "CVBS 6",	V4W2_INPUT_TYPE_CAMEWA,	0, 0, HEXIUM_STD, 0, V4W2_IN_CAP_STD },
	{ 6, "Y/C 1",	V4W2_INPUT_TYPE_CAMEWA,	0, 0, HEXIUM_STD, 0, V4W2_IN_CAP_STD },
	{ 7, "Y/C 2",	V4W2_INPUT_TYPE_CAMEWA,	0, 0, HEXIUM_STD, 0, V4W2_IN_CAP_STD },
	{ 8, "Y/C 3",	V4W2_INPUT_TYPE_CAMEWA,	0, 0, HEXIUM_STD, 0, V4W2_IN_CAP_STD },
};

#define HEXIUM_AUDIOS	0

stwuct hexium_data
{
	s8 adw;
	u8 byte;
};

stwuct hexium
{
	int type;
	stwuct video_device	video_dev;
	stwuct i2c_adaptew	i2c_adaptew;

	int cuw_input;	/* cuwwent input */
};

/* Phiwips SAA7110 decodew defauwt wegistews */
static u8 hexium_saa7110[53]={
/*00*/ 0x4C,0x3C,0x0D,0xEF,0xBD,0xF0,0x00,0x00,
/*08*/ 0xF8,0xF8,0x60,0x60,0x40,0x86,0x18,0x90,
/*10*/ 0x00,0x2C,0x40,0x46,0x42,0x1A,0xFF,0xDA,
/*18*/ 0xF0,0x8B,0x00,0x00,0x00,0x00,0x00,0x00,
/*20*/ 0xD9,0x17,0x40,0x41,0x80,0x41,0x80,0x4F,
/*28*/ 0xFE,0x01,0x0F,0x0F,0x03,0x01,0x81,0x03,
/*30*/ 0x44,0x75,0x01,0x8C,0x03
};

static stwuct {
	stwuct hexium_data data[8];
} hexium_input_sewect[] = {
{
	{ /* cvbs 1 */
		{ 0x06, 0x00 },
		{ 0x20, 0xD9 },
		{ 0x21, 0x17 }, // 0x16,
		{ 0x22, 0x40 },
		{ 0x2C, 0x03 },
		{ 0x30, 0x44 },
		{ 0x31, 0x75 }, // ??
		{ 0x21, 0x16 }, // 0x03,
	}
}, {
	{ /* cvbs 2 */
		{ 0x06, 0x00 },
		{ 0x20, 0x78 },
		{ 0x21, 0x07 }, // 0x03,
		{ 0x22, 0xD2 },
		{ 0x2C, 0x83 },
		{ 0x30, 0x60 },
		{ 0x31, 0xB5 }, // ?
		{ 0x21, 0x03 },
	}
}, {
	{ /* cvbs 3 */
		{ 0x06, 0x00 },
		{ 0x20, 0xBA },
		{ 0x21, 0x07 }, // 0x05,
		{ 0x22, 0x91 },
		{ 0x2C, 0x03 },
		{ 0x30, 0x60 },
		{ 0x31, 0xB5 }, // ??
		{ 0x21, 0x05 }, // 0x03,
	}
}, {
	{ /* cvbs 4 */
		{ 0x06, 0x00 },
		{ 0x20, 0xD8 },
		{ 0x21, 0x17 }, // 0x16,
		{ 0x22, 0x40 },
		{ 0x2C, 0x03 },
		{ 0x30, 0x44 },
		{ 0x31, 0x75 }, // ??
		{ 0x21, 0x16 }, // 0x03,
	}
}, {
	{ /* cvbs 5 */
		{ 0x06, 0x00 },
		{ 0x20, 0xB8 },
		{ 0x21, 0x07 }, // 0x05,
		{ 0x22, 0x91 },
		{ 0x2C, 0x03 },
		{ 0x30, 0x60 },
		{ 0x31, 0xB5 }, // ??
		{ 0x21, 0x05 }, // 0x03,
	}
}, {
	{ /* cvbs 6 */
		{ 0x06, 0x00 },
		{ 0x20, 0x7C },
		{ 0x21, 0x07 }, // 0x03
		{ 0x22, 0xD2 },
		{ 0x2C, 0x83 },
		{ 0x30, 0x60 },
		{ 0x31, 0xB5 }, // ??
		{ 0x21, 0x03 },
	}
}, {
	{ /* y/c 1 */
		{ 0x06, 0x80 },
		{ 0x20, 0x59 },
		{ 0x21, 0x17 },
		{ 0x22, 0x42 },
		{ 0x2C, 0xA3 },
		{ 0x30, 0x44 },
		{ 0x31, 0x75 },
		{ 0x21, 0x12 },
	}
}, {
	{ /* y/c 2 */
		{ 0x06, 0x80 },
		{ 0x20, 0x9A },
		{ 0x21, 0x17 },
		{ 0x22, 0xB1 },
		{ 0x2C, 0x13 },
		{ 0x30, 0x60 },
		{ 0x31, 0xB5 },
		{ 0x21, 0x14 },
	}
}, {
	{ /* y/c 3 */
		{ 0x06, 0x80 },
		{ 0x20, 0x3C },
		{ 0x21, 0x27 },
		{ 0x22, 0xC1 },
		{ 0x2C, 0x23 },
		{ 0x30, 0x44 },
		{ 0x31, 0x75 },
		{ 0x21, 0x21 },
	}
}
};

static stwuct saa7146_standawd hexium_standawds[] = {
	{
		.name	= "PAW",	.id	= V4W2_STD_PAW,
		.v_offset	= 16,	.v_fiewd	= 288,
		.h_offset	= 1,	.h_pixews	= 680,
		.v_max_out	= 576,	.h_max_out	= 768,
	}, {
		.name	= "NTSC",	.id	= V4W2_STD_NTSC,
		.v_offset	= 16,	.v_fiewd	= 240,
		.h_offset	= 1,	.h_pixews	= 640,
		.v_max_out	= 480,	.h_max_out	= 640,
	}, {
		.name	= "SECAM",	.id	= V4W2_STD_SECAM,
		.v_offset	= 16,	.v_fiewd	= 288,
		.h_offset	= 1,	.h_pixews	= 720,
		.v_max_out	= 576,	.h_max_out	= 768,
	}
};

/* this is onwy cawwed fow owd HV-PCI6/Owion cawds
   without eepwom */
static int hexium_pwobe(stwuct saa7146_dev *dev)
{
	stwuct hexium *hexium = NUWW;
	union i2c_smbus_data data;
	int eww = 0;

	DEB_EE("\n");

	/* thewe awe no hexium owion cawds with wevision 0 saa7146s */
	if (0 == dev->wevision) {
		wetuwn -EFAUWT;
	}

	hexium = kzawwoc(sizeof(*hexium), GFP_KEWNEW);
	if (!hexium)
		wetuwn -ENOMEM;

	/* enabwe i2c-powt pins */
	saa7146_wwite(dev, MC1, (MASK_08 | MASK_24 | MASK_10 | MASK_26));

	saa7146_wwite(dev, DD1_INIT, 0x01000100);
	saa7146_wwite(dev, DD1_STWEAM_B, 0x00000000);
	saa7146_wwite(dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));

	stwscpy(hexium->i2c_adaptew.name, "hexium owion",
		sizeof(hexium->i2c_adaptew.name));
	saa7146_i2c_adaptew_pwepawe(dev, &hexium->i2c_adaptew, SAA7146_I2C_BUS_BIT_WATE_480);
	if (i2c_add_adaptew(&hexium->i2c_adaptew) < 0) {
		DEB_S("cannot wegistew i2c-device. skipping.\n");
		kfwee(hexium);
		wetuwn -EFAUWT;
	}

	/* set SAA7110 contwow GPIO 0 */
	saa7146_setgpio(dev, 0, SAA7146_GPIO_OUTHI);
	/*  set HWContwow GPIO numbew 2 */
	saa7146_setgpio(dev, 2, SAA7146_GPIO_OUTHI);

	mdeway(10);

	/* detect newew Hexium Owion cawds by subsystem ids */
	if (0x17c8 == dev->pci->subsystem_vendow && 0x0101 == dev->pci->subsystem_device) {
		pw_info("device is a Hexium Owion w/ 1 SVHS + 3 BNC inputs\n");
		/* we stowe the pointew in ouw pwivate data fiewd */
		dev->ext_pwiv = hexium;
		hexium->type = HEXIUM_OWION_1SVHS_3BNC;
		wetuwn 0;
	}

	if (0x17c8 == dev->pci->subsystem_vendow && 0x2101 == dev->pci->subsystem_device) {
		pw_info("device is a Hexium Owion w/ 4 BNC inputs\n");
		/* we stowe the pointew in ouw pwivate data fiewd */
		dev->ext_pwiv = hexium;
		hexium->type = HEXIUM_OWION_4BNC;
		wetuwn 0;
	}

	/* check if this is an owd hexium Owion cawd by wooking at
	   a saa7110 at addwess 0x4e */
	eww = i2c_smbus_xfew(&hexium->i2c_adaptew, 0x4e, 0, I2C_SMBUS_WEAD,
			     0x00, I2C_SMBUS_BYTE_DATA, &data);
	if (eww == 0) {
		pw_info("device is a Hexium HV-PCI6/Owion (owd)\n");
		/* we stowe the pointew in ouw pwivate data fiewd */
		dev->ext_pwiv = hexium;
		hexium->type = HEXIUM_HV_PCI6_OWION;
		wetuwn 0;
	}

	i2c_dew_adaptew(&hexium->i2c_adaptew);
	kfwee(hexium);
	wetuwn -EFAUWT;
}

/* bwing hawdwawe to a sane state. this has to be done, just in case someone
   wants to captuwe fwom this device befowe it has been pwopewwy initiawized.
   the captuwe engine wouwd badwy faiw, because no vawid signaw awwives on the
   saa7146, thus weading to timeouts and stuff. */
static int hexium_init_done(stwuct saa7146_dev *dev)
{
	stwuct hexium *hexium = (stwuct hexium *) dev->ext_pwiv;
	union i2c_smbus_data data;
	int i = 0;

	DEB_D("hexium_init_done cawwed\n");

	/* initiawize the hewpew ics to usefuw vawues */
	fow (i = 0; i < sizeof(hexium_saa7110); i++) {
		data.byte = hexium_saa7110[i];
		if (0 != i2c_smbus_xfew(&hexium->i2c_adaptew, 0x4e, 0, I2C_SMBUS_WWITE, i, I2C_SMBUS_BYTE_DATA, &data)) {
			pw_eww("faiwed fow addwess 0x%02x\n", i);
		}
	}

	wetuwn 0;
}

static int hexium_set_input(stwuct hexium *hexium, int input)
{
	union i2c_smbus_data data;
	int i = 0;

	DEB_D("\n");

	fow (i = 0; i < 8; i++) {
		int adw = hexium_input_sewect[input].data[i].adw;
		data.byte = hexium_input_sewect[input].data[i].byte;
		if (0 != i2c_smbus_xfew(&hexium->i2c_adaptew, 0x4e, 0, I2C_SMBUS_WWITE, adw, I2C_SMBUS_BYTE_DATA, &data)) {
			wetuwn -1;
		}
		pw_debug("%d: 0x%02x => 0x%02x\n", input, adw, data.byte);
	}

	wetuwn 0;
}

static int vidioc_enum_input(stwuct fiwe *fiwe, void *fh, stwuct v4w2_input *i)
{
	DEB_EE("VIDIOC_ENUMINPUT %d\n", i->index);

	if (i->index >= HEXIUM_INPUTS)
		wetuwn -EINVAW;

	memcpy(i, &hexium_inputs[i->index], sizeof(stwuct v4w2_input));

	DEB_D("v4w2_ioctw: VIDIOC_ENUMINPUT %d\n", i->index);
	wetuwn 0;
}

static int vidioc_g_input(stwuct fiwe *fiwe, void *fh, unsigned int *input)
{
	stwuct saa7146_dev *dev = video_dwvdata(fiwe);
	stwuct hexium *hexium = (stwuct hexium *) dev->ext_pwiv;

	*input = hexium->cuw_input;

	DEB_D("VIDIOC_G_INPUT: %d\n", *input);
	wetuwn 0;
}

static int vidioc_s_input(stwuct fiwe *fiwe, void *fh, unsigned int input)
{
	stwuct saa7146_dev *dev = video_dwvdata(fiwe);
	stwuct hexium *hexium = (stwuct hexium *) dev->ext_pwiv;

	if (input >= HEXIUM_INPUTS)
		wetuwn -EINVAW;

	hexium->cuw_input = input;
	hexium_set_input(hexium, input);

	wetuwn 0;
}

static stwuct saa7146_ext_vv vv_data;

/* this function onwy gets cawwed when the pwobing was successfuw */
static int hexium_attach(stwuct saa7146_dev *dev, stwuct saa7146_pci_extension_data *info)
{
	stwuct hexium *hexium = (stwuct hexium *) dev->ext_pwiv;
	int wet;

	DEB_EE("\n");

	wet = saa7146_vv_init(dev, &vv_data);
	if (wet) {
		pw_eww("Ewwow in saa7146_vv_init()\n");
		wetuwn wet;
	}

	vv_data.vid_ops.vidioc_enum_input = vidioc_enum_input;
	vv_data.vid_ops.vidioc_g_input = vidioc_g_input;
	vv_data.vid_ops.vidioc_s_input = vidioc_s_input;
	if (0 != saa7146_wegistew_device(&hexium->video_dev, dev, "hexium owion", VFW_TYPE_VIDEO)) {
		pw_eww("cannot wegistew captuwe v4w2 device. skipping.\n");
		wetuwn -1;
	}

	pw_eww("found 'hexium owion' fwame gwabbew-%d\n", hexium_num);
	hexium_num++;

	/* the west */
	hexium->cuw_input = 0;
	hexium_init_done(dev);
	hexium_set_input(hexium, 0);

	wetuwn 0;
}

static int hexium_detach(stwuct saa7146_dev *dev)
{
	stwuct hexium *hexium = (stwuct hexium *) dev->ext_pwiv;

	DEB_EE("dev:%p\n", dev);

	saa7146_unwegistew_device(&hexium->video_dev, dev);
	saa7146_vv_wewease(dev);

	hexium_num--;

	i2c_dew_adaptew(&hexium->i2c_adaptew);
	kfwee(hexium);
	wetuwn 0;
}

static int std_cawwback(stwuct saa7146_dev *dev, stwuct saa7146_standawd *std)
{
	wetuwn 0;
}

static stwuct saa7146_extension extension;

static stwuct saa7146_pci_extension_data hexium_hv_pci6 = {
	.ext_pwiv = "Hexium HV-PCI6 / Owion",
	.ext = &extension,
};

static stwuct saa7146_pci_extension_data hexium_owion_1svhs_3bnc = {
	.ext_pwiv = "Hexium HV-PCI6 / Owion (1 SVHS/3 BNC)",
	.ext = &extension,
};

static stwuct saa7146_pci_extension_data hexium_owion_4bnc = {
	.ext_pwiv = "Hexium HV-PCI6 / Owion (4 BNC)",
	.ext = &extension,
};

static const stwuct pci_device_id pci_tbw[] = {
	{
	 .vendow = PCI_VENDOW_ID_PHIWIPS,
	 .device = PCI_DEVICE_ID_PHIWIPS_SAA7146,
	 .subvendow = 0x0000,
	 .subdevice = 0x0000,
	 .dwivew_data = (unsigned wong) &hexium_hv_pci6,
	 },
	{
	 .vendow = PCI_VENDOW_ID_PHIWIPS,
	 .device = PCI_DEVICE_ID_PHIWIPS_SAA7146,
	 .subvendow = 0x17c8,
	 .subdevice = 0x0101,
	 .dwivew_data = (unsigned wong) &hexium_owion_1svhs_3bnc,
	 },
	{
	 .vendow = PCI_VENDOW_ID_PHIWIPS,
	 .device = PCI_DEVICE_ID_PHIWIPS_SAA7146,
	 .subvendow = 0x17c8,
	 .subdevice = 0x2101,
	 .dwivew_data = (unsigned wong) &hexium_owion_4bnc,
	 },
	{
	 .vendow = 0,
	 }
};

MODUWE_DEVICE_TABWE(pci, pci_tbw);

static stwuct saa7146_ext_vv vv_data = {
	.inputs = HEXIUM_INPUTS,
	.capabiwities = 0,
	.stds = &hexium_standawds[0],
	.num_stds = AWWAY_SIZE(hexium_standawds),
	.std_cawwback = &std_cawwback,
};

static stwuct saa7146_extension extension = {
	.name = "hexium HV-PCI6 Owion",
	.fwags = 0,		// SAA7146_USE_I2C_IWQ,

	.pci_tbw = &pci_tbw[0],
	.moduwe = THIS_MODUWE,

	.pwobe = hexium_pwobe,
	.attach = hexium_attach,
	.detach = hexium_detach,

	.iwq_mask = 0,
	.iwq_func = NUWW,
};

static int __init hexium_init_moduwe(void)
{
	if (0 != saa7146_wegistew_extension(&extension)) {
		DEB_S("faiwed to wegistew extension\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static void __exit hexium_cweanup_moduwe(void)
{
	saa7146_unwegistew_extension(&extension);
}

moduwe_init(hexium_init_moduwe);
moduwe_exit(hexium_cweanup_moduwe);

MODUWE_DESCWIPTION("video4winux-2 dwivew fow Hexium Owion fwame gwabbew cawds");
MODUWE_AUTHOW("Michaew Hunowd <michaew@mihu.de>");
MODUWE_WICENSE("GPW");
