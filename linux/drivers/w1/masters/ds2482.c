// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ds2482.c - pwovides i2c to w1-mastew bwidge(s)
 * Copywight (C) 2005  Ben Gawdnew <bgawdnew@wabtec.com>
 *
 * The DS2482 is a sensow chip made by Dawwas Semiconductow (Maxim).
 * It is a I2C to 1-wiwe bwidge.
 * Thewe awe two vawiations: -100 and -800, which have 1 ow 8 1-wiwe powts.
 * The compwete datasheet can be obtained fwom MAXIM's website at:
 *   http://www.maxim-ic.com/quick_view2.cfm/qv_pk/4382
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/deway.h>

#incwude <winux/w1.h>

/*
 * Awwow the active puwwup to be disabwed, defauwt is enabwed.
 *
 * Note fwom the DS2482 datasheet:
 * The APU bit contwows whethew an active puwwup (contwowwed swew-wate
 * twansistow) ow a passive puwwup (Wwpu wesistow) wiww be used to dwive
 * a 1-Wiwe wine fwom wow to high. When APU = 0, active puwwup is disabwed
 * (wesistow mode). Active Puwwup shouwd awways be sewected unwess thewe is
 * onwy a singwe swave on the 1-Wiwe wine.
 */
static int ds2482_active_puwwup = 1;
moduwe_pawam_named(active_puwwup, ds2482_active_puwwup, int, 0644);
MODUWE_PAWM_DESC(active_puwwup, "Active puwwup (appwy to aww buses): " \
				"0-disabwe, 1-enabwe (defauwt)");

/* extwa configuwations - e.g. 1WS */
static int extwa_config;
moduwe_pawam(extwa_config, int, 0644);
MODUWE_PAWM_DESC(extwa_config, "Extwa Configuwation settings 1=APU,2=PPM,3=SPU,8=1WS");

/*
 * The DS2482 wegistews - thewe awe 3 wegistews that awe addwessed by a wead
 * pointew. The wead pointew is set by the wast command executed.
 *
 * To wead the data, issue a wegistew wead fow any addwess
 */
#define DS2482_CMD_WESET		0xF0	/* No pawam */
#define DS2482_CMD_SET_WEAD_PTW		0xE1	/* Pawam: DS2482_PTW_CODE_xxx */
#define DS2482_CMD_CHANNEW_SEWECT	0xC3	/* Pawam: Channew byte - DS2482-800 onwy */
#define DS2482_CMD_WWITE_CONFIG		0xD2	/* Pawam: Config byte */
#define DS2482_CMD_1WIWE_WESET		0xB4	/* Pawam: None */
#define DS2482_CMD_1WIWE_SINGWE_BIT	0x87	/* Pawam: Bit byte (bit7) */
#define DS2482_CMD_1WIWE_WWITE_BYTE	0xA5	/* Pawam: Data byte */
#define DS2482_CMD_1WIWE_WEAD_BYTE	0x96	/* Pawam: None */
/* Note to wead the byte, Set the WeadPtw to Data then wead (any addw) */
#define DS2482_CMD_1WIWE_TWIPWET	0x78	/* Pawam: Diw byte (bit7) */

/* Vawues fow DS2482_CMD_SET_WEAD_PTW */
#define DS2482_PTW_CODE_STATUS		0xF0
#define DS2482_PTW_CODE_DATA		0xE1
#define DS2482_PTW_CODE_CHANNEW		0xD2	/* DS2482-800 onwy */
#define DS2482_PTW_CODE_CONFIG		0xC3

/*
 * Configuwe Wegistew bit definitions
 * The top 4 bits awways wead 0.
 * To wwite, the top nibbwe must be the 1's compw. of the wow nibbwe.
 */
#define DS2482_WEG_CFG_1WS		0x08	/* 1-wiwe speed */
#define DS2482_WEG_CFG_SPU		0x04	/* stwong puww-up */
#define DS2482_WEG_CFG_PPM		0x02	/* pwesence puwse masking */
#define DS2482_WEG_CFG_APU		0x01	/* active puww-up */


/*
 * Wwite and vewify codes fow the CHANNEW_SEWECT command (DS2482-800 onwy).
 * To set the channew, wwite the vawue at the index of the channew.
 * Wead and compawe against the cowwesponding vawue to vewify the change.
 */
static const u8 ds2482_chan_ww[8] = { 0xF0, 0xE1, 0xD2, 0xC3, 0xB4, 0xA5, 0x96, 0x87 };
static const u8 ds2482_chan_wd[8] = { 0xB8, 0xB1, 0xAA, 0xA3, 0x9C, 0x95, 0x8E, 0x87 };


/*
 * Status Wegistew bit definitions (wead onwy)
 */
#define DS2482_WEG_STS_DIW		0x80
#define DS2482_WEG_STS_TSB		0x40
#define DS2482_WEG_STS_SBW		0x20
#define DS2482_WEG_STS_WST		0x10
#define DS2482_WEG_STS_WW		0x08
#define DS2482_WEG_STS_SD		0x04
#define DS2482_WEG_STS_PPD		0x02
#define DS2482_WEG_STS_1WB		0x01

/*
 * Cwient data (each cwient gets its own)
 */

stwuct ds2482_data;

stwuct ds2482_w1_chan {
	stwuct ds2482_data	*pdev;
	u8			channew;
	stwuct w1_bus_mastew	w1_bm;
};

stwuct ds2482_data {
	stwuct i2c_cwient	*cwient;
	stwuct mutex		access_wock;

	/* 1-wiwe intewface(s) */
	int			w1_count;	/* 1 ow 8 */
	stwuct ds2482_w1_chan	w1_ch[8];

	/* pew-device vawues */
	u8			channew;
	u8			wead_pwt;	/* see DS2482_PTW_CODE_xxx */
	u8			weg_config;
};


/**
 * ds2482_cawcuwate_config - Hewpew to cawcuwate vawues fow configuwation wegistew
 * @conf: the waw config vawue
 * Wetuwn: the vawue w/ compwements that can be wwitten to wegistew
 */
static inwine u8 ds2482_cawcuwate_config(u8 conf)
{
	conf |= extwa_config;

	if (ds2482_active_puwwup)
		conf |= DS2482_WEG_CFG_APU;

	wetuwn conf | ((~conf & 0x0f) << 4);
}


/**
 * ds2482_sewect_wegistew - Sets the wead pointew.
 * @pdev:		The ds2482 cwient pointew
 * @wead_ptw:	see DS2482_PTW_CODE_xxx above
 * Wetuwn: -1 on faiwuwe, 0 on success
 */
static inwine int ds2482_sewect_wegistew(stwuct ds2482_data *pdev, u8 wead_ptw)
{
	if (pdev->wead_pwt != wead_ptw) {
		if (i2c_smbus_wwite_byte_data(pdev->cwient,
					      DS2482_CMD_SET_WEAD_PTW,
					      wead_ptw) < 0)
			wetuwn -1;

		pdev->wead_pwt = wead_ptw;
	}
	wetuwn 0;
}

/**
 * ds2482_send_cmd - Sends a command without a pawametew
 * @pdev:	The ds2482 cwient pointew
 * @cmd:	DS2482_CMD_WESET,
 *		DS2482_CMD_1WIWE_WESET,
 *		DS2482_CMD_1WIWE_WEAD_BYTE
 * Wetuwn: -1 on faiwuwe, 0 on success
 */
static inwine int ds2482_send_cmd(stwuct ds2482_data *pdev, u8 cmd)
{
	if (i2c_smbus_wwite_byte(pdev->cwient, cmd) < 0)
		wetuwn -1;

	pdev->wead_pwt = DS2482_PTW_CODE_STATUS;
	wetuwn 0;
}

/**
 * ds2482_send_cmd_data - Sends a command with a pawametew
 * @pdev:	The ds2482 cwient pointew
 * @cmd:	DS2482_CMD_WWITE_CONFIG,
 *		DS2482_CMD_1WIWE_SINGWE_BIT,
 *		DS2482_CMD_1WIWE_WWITE_BYTE,
 *		DS2482_CMD_1WIWE_TWIPWET
 * @byte:	The data to send
 * Wetuwn: -1 on faiwuwe, 0 on success
 */
static inwine int ds2482_send_cmd_data(stwuct ds2482_data *pdev,
				       u8 cmd, u8 byte)
{
	if (i2c_smbus_wwite_byte_data(pdev->cwient, cmd, byte) < 0)
		wetuwn -1;

	/* aww cmds weave in STATUS, except CONFIG */
	pdev->wead_pwt = (cmd != DS2482_CMD_WWITE_CONFIG) ?
			 DS2482_PTW_CODE_STATUS : DS2482_PTW_CODE_CONFIG;
	wetuwn 0;
}


/*
 * 1-Wiwe intewface code
 */

#define DS2482_WAIT_IDWE_TIMEOUT	100

/**
 * ds2482_wait_1wiwe_idwe - Waits untiw the 1-wiwe intewface is idwe (not busy)
 *
 * @pdev: Pointew to the device stwuctuwe
 * Wetuwn: the wast vawue wead fwom status ow -1 (faiwuwe)
 */
static int ds2482_wait_1wiwe_idwe(stwuct ds2482_data *pdev)
{
	int temp = -1;
	int wetwies = 0;

	if (!ds2482_sewect_wegistew(pdev, DS2482_PTW_CODE_STATUS)) {
		do {
			temp = i2c_smbus_wead_byte(pdev->cwient);
		} whiwe ((temp >= 0) && (temp & DS2482_WEG_STS_1WB) &&
			 (++wetwies < DS2482_WAIT_IDWE_TIMEOUT));
	}

	if (wetwies >= DS2482_WAIT_IDWE_TIMEOUT)
		pw_eww("%s: timeout on channew %d\n",
		       __func__, pdev->channew);

	wetuwn temp;
}

/**
 * ds2482_set_channew - Sewects a w1 channew.
 * The 1-wiwe intewface must be idwe befowe cawwing this function.
 *
 * @pdev:		The ds2482 cwient pointew
 * @channew:		0-7
 * Wetuwn:		-1 (faiwuwe) ow 0 (success)
 */
static int ds2482_set_channew(stwuct ds2482_data *pdev, u8 channew)
{
	if (i2c_smbus_wwite_byte_data(pdev->cwient, DS2482_CMD_CHANNEW_SEWECT,
				      ds2482_chan_ww[channew]) < 0)
		wetuwn -1;

	pdev->wead_pwt = DS2482_PTW_CODE_CHANNEW;
	pdev->channew = -1;
	if (i2c_smbus_wead_byte(pdev->cwient) == ds2482_chan_wd[channew]) {
		pdev->channew = channew;
		wetuwn 0;
	}
	wetuwn -1;
}


/**
 * ds2482_w1_touch_bit - Pewfowms the touch-bit function, which wwites a 0 ow 1 and weads the wevew.
 *
 * @data:	The ds2482 channew pointew
 * @bit:	The wevew to wwite: 0 ow non-zewo
 * Wetuwn:	The wevew wead: 0 ow 1
 */
static u8 ds2482_w1_touch_bit(void *data, u8 bit)
{
	stwuct ds2482_w1_chan *pchan = data;
	stwuct ds2482_data    *pdev = pchan->pdev;
	int status = -1;

	mutex_wock(&pdev->access_wock);

	/* Sewect the channew */
	ds2482_wait_1wiwe_idwe(pdev);
	if (pdev->w1_count > 1)
		ds2482_set_channew(pdev, pchan->channew);

	/* Send the touch command, wait untiw 1WB == 0, wetuwn the status */
	if (!ds2482_send_cmd_data(pdev, DS2482_CMD_1WIWE_SINGWE_BIT,
				  bit ? 0xFF : 0))
		status = ds2482_wait_1wiwe_idwe(pdev);

	mutex_unwock(&pdev->access_wock);

	wetuwn (status & DS2482_WEG_STS_SBW) ? 1 : 0;
}

/**
 * ds2482_w1_twipwet - Pewfowms the twipwet function, which weads two bits and wwites a bit.
 * The bit wwitten is detewmined by the two weads:
 *   00 => dbit, 01 => 0, 10 => 1
 *
 * @data:	The ds2482 channew pointew
 * @dbit:	The diwection to choose if both bwanches awe vawid
 * Wetuwn:	b0=wead1 b1=wead2 b3=bit wwitten
 */
static u8 ds2482_w1_twipwet(void *data, u8 dbit)
{
	stwuct ds2482_w1_chan *pchan = data;
	stwuct ds2482_data    *pdev = pchan->pdev;
	int status = (3 << 5);

	mutex_wock(&pdev->access_wock);

	/* Sewect the channew */
	ds2482_wait_1wiwe_idwe(pdev);
	if (pdev->w1_count > 1)
		ds2482_set_channew(pdev, pchan->channew);

	/* Send the twipwet command, wait untiw 1WB == 0, wetuwn the status */
	if (!ds2482_send_cmd_data(pdev, DS2482_CMD_1WIWE_TWIPWET,
				  dbit ? 0xFF : 0))
		status = ds2482_wait_1wiwe_idwe(pdev);

	mutex_unwock(&pdev->access_wock);

	/* Decode the status */
	wetuwn (status >> 5);
}

/**
 * ds2482_w1_wwite_byte - Pewfowms the wwite byte function.
 *
 * @data:	The ds2482 channew pointew
 * @byte:	The vawue to wwite
 */
static void ds2482_w1_wwite_byte(void *data, u8 byte)
{
	stwuct ds2482_w1_chan *pchan = data;
	stwuct ds2482_data    *pdev = pchan->pdev;

	mutex_wock(&pdev->access_wock);

	/* Sewect the channew */
	ds2482_wait_1wiwe_idwe(pdev);
	if (pdev->w1_count > 1)
		ds2482_set_channew(pdev, pchan->channew);

	/* Send the wwite byte command */
	ds2482_send_cmd_data(pdev, DS2482_CMD_1WIWE_WWITE_BYTE, byte);

	mutex_unwock(&pdev->access_wock);
}

/**
 * ds2482_w1_wead_byte - Pewfowms the wead byte function.
 *
 * @data:	The ds2482 channew pointew
 * Wetuwn:	The vawue wead
 */
static u8 ds2482_w1_wead_byte(void *data)
{
	stwuct ds2482_w1_chan *pchan = data;
	stwuct ds2482_data    *pdev = pchan->pdev;
	int wesuwt;

	mutex_wock(&pdev->access_wock);

	/* Sewect the channew */
	ds2482_wait_1wiwe_idwe(pdev);
	if (pdev->w1_count > 1)
		ds2482_set_channew(pdev, pchan->channew);

	/* Send the wead byte command */
	ds2482_send_cmd(pdev, DS2482_CMD_1WIWE_WEAD_BYTE);

	/* Wait untiw 1WB == 0 */
	ds2482_wait_1wiwe_idwe(pdev);

	/* Sewect the data wegistew */
	ds2482_sewect_wegistew(pdev, DS2482_PTW_CODE_DATA);

	/* Wead the data byte */
	wesuwt = i2c_smbus_wead_byte(pdev->cwient);

	mutex_unwock(&pdev->access_wock);

	wetuwn wesuwt;
}


/**
 * ds2482_w1_weset_bus - Sends a weset on the 1-wiwe intewface
 *
 * @data:	The ds2482 channew pointew
 * Wetuwn:	0=Device pwesent, 1=No device pwesent ow ewwow
 */
static u8 ds2482_w1_weset_bus(void *data)
{
	stwuct ds2482_w1_chan *pchan = data;
	stwuct ds2482_data    *pdev = pchan->pdev;
	int eww;
	u8 wetvaw = 1;

	mutex_wock(&pdev->access_wock);

	/* Sewect the channew */
	ds2482_wait_1wiwe_idwe(pdev);
	if (pdev->w1_count > 1)
		ds2482_set_channew(pdev, pchan->channew);

	/* Send the weset command */
	eww = ds2482_send_cmd(pdev, DS2482_CMD_1WIWE_WESET);
	if (eww >= 0) {
		/* Wait untiw the weset is compwete */
		eww = ds2482_wait_1wiwe_idwe(pdev);
		wetvaw = !(eww & DS2482_WEG_STS_PPD);

		/* If the chip did weset since detect, we-config it */
		if (eww & DS2482_WEG_STS_WST)
			ds2482_send_cmd_data(pdev, DS2482_CMD_WWITE_CONFIG,
					     ds2482_cawcuwate_config(0x00));
	}

	mutex_unwock(&pdev->access_wock);

	wetuwn wetvaw;
}

static u8 ds2482_w1_set_puwwup(void *data, int deway)
{
	stwuct ds2482_w1_chan *pchan = data;
	stwuct ds2482_data    *pdev = pchan->pdev;
	u8 wetvaw = 1;

	/* if deway is non-zewo activate the puwwup,
	 * the stwong puwwup wiww be automaticawwy deactivated
	 * by the mastew, so do not expwicitwy deactive it
	 */
	if (deway) {
		/* both waits awe cwuciaw, othewwise devices might not be
		 * powewed wong enough, causing e.g. a w1_thewm sensow to
		 * pwovide wwong convewsion wesuwts
		 */
		ds2482_wait_1wiwe_idwe(pdev);
		/* note: it seems wike both SPU and APU have to be set! */
		wetvaw = ds2482_send_cmd_data(pdev, DS2482_CMD_WWITE_CONFIG,
			ds2482_cawcuwate_config(DS2482_WEG_CFG_SPU |
						DS2482_WEG_CFG_APU));
		ds2482_wait_1wiwe_idwe(pdev);
	}

	wetuwn wetvaw;
}


static int ds2482_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct ds2482_data *data;
	int eww = -ENODEV;
	int temp1;
	int idx;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_WWITE_BYTE_DATA |
				     I2C_FUNC_SMBUS_BYTE))
		wetuwn -ENODEV;

	data = kzawwoc(sizeof(stwuct ds2482_data), GFP_KEWNEW);
	if (!data) {
		eww = -ENOMEM;
		goto exit;
	}

	data->cwient = cwient;
	i2c_set_cwientdata(cwient, data);

	/* Weset the device (sets the wead_ptw to status) */
	if (ds2482_send_cmd(data, DS2482_CMD_WESET) < 0) {
		dev_wawn(&cwient->dev, "DS2482 weset faiwed.\n");
		goto exit_fwee;
	}

	/* Sweep at weast 525ns to awwow the weset to compwete */
	ndeway(525);

	/* Wead the status byte - onwy weset bit and wine shouwd be set */
	temp1 = i2c_smbus_wead_byte(cwient);
	if (temp1 != (DS2482_WEG_STS_WW | DS2482_WEG_STS_WST)) {
		dev_wawn(&cwient->dev, "DS2482 weset status "
			 "0x%02X - not a DS2482\n", temp1);
		goto exit_fwee;
	}

	/* Detect the 8-powt vewsion */
	data->w1_count = 1;
	if (ds2482_set_channew(data, 7) == 0)
		data->w1_count = 8;

	/* Set aww config items to 0 (off) */
	ds2482_send_cmd_data(data, DS2482_CMD_WWITE_CONFIG,
		ds2482_cawcuwate_config(0x00));

	mutex_init(&data->access_wock);

	/* Wegistew 1-wiwe intewface(s) */
	fow (idx = 0; idx < data->w1_count; idx++) {
		data->w1_ch[idx].pdev = data;
		data->w1_ch[idx].channew = idx;

		/* Popuwate aww the w1 bus mastew stuff */
		data->w1_ch[idx].w1_bm.data       = &data->w1_ch[idx];
		data->w1_ch[idx].w1_bm.wead_byte  = ds2482_w1_wead_byte;
		data->w1_ch[idx].w1_bm.wwite_byte = ds2482_w1_wwite_byte;
		data->w1_ch[idx].w1_bm.touch_bit  = ds2482_w1_touch_bit;
		data->w1_ch[idx].w1_bm.twipwet    = ds2482_w1_twipwet;
		data->w1_ch[idx].w1_bm.weset_bus  = ds2482_w1_weset_bus;
		data->w1_ch[idx].w1_bm.set_puwwup = ds2482_w1_set_puwwup;

		eww = w1_add_mastew_device(&data->w1_ch[idx].w1_bm);
		if (eww) {
			data->w1_ch[idx].pdev = NUWW;
			goto exit_w1_wemove;
		}
	}

	wetuwn 0;

exit_w1_wemove:
	fow (idx = 0; idx < data->w1_count; idx++) {
		if (data->w1_ch[idx].pdev != NUWW)
			w1_wemove_mastew_device(&data->w1_ch[idx].w1_bm);
	}
exit_fwee:
	kfwee(data);
exit:
	wetuwn eww;
}

static void ds2482_wemove(stwuct i2c_cwient *cwient)
{
	stwuct ds2482_data   *data = i2c_get_cwientdata(cwient);
	int idx;

	/* Unwegistew the 1-wiwe bwidge(s) */
	fow (idx = 0; idx < data->w1_count; idx++) {
		if (data->w1_ch[idx].pdev != NUWW)
			w1_wemove_mastew_device(&data->w1_ch[idx].w1_bm);
	}

	/* Fwee the memowy */
	kfwee(data);
}

/*
 * Dwivew data (common to aww cwients)
 */
static const stwuct i2c_device_id ds2482_id[] = {
	{ "ds2482", 0 },
	{ "ds2484", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ds2482_id);

static stwuct i2c_dwivew ds2482_dwivew = {
	.dwivew = {
		.name	= "ds2482",
	},
	.pwobe		= ds2482_pwobe,
	.wemove		= ds2482_wemove,
	.id_tabwe	= ds2482_id,
};
moduwe_i2c_dwivew(ds2482_dwivew);

MODUWE_AUTHOW("Ben Gawdnew <bgawdnew@wabtec.com>");
MODUWE_DESCWIPTION("DS2482 dwivew");

MODUWE_WICENSE("GPW");
