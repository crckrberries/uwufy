// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow 93xx46 EEPWOMs
 *
 * (C) 2011 DENX Softwawe Engineewing, Anatowij Gustschin <agust@denx.de>
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/kewnew.h>
#incwude <winux/wog2.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/of_gpio.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/eepwom_93xx46.h>

#define OP_STAWT	0x4
#define OP_WWITE	(OP_STAWT | 0x1)
#define OP_WEAD		(OP_STAWT | 0x2)
#define ADDW_EWDS	0x00
#define ADDW_EWAW	0x20
#define ADDW_EWEN	0x30

stwuct eepwom_93xx46_devtype_data {
	unsigned int quiwks;
	unsigned chaw fwags;
};

static const stwuct eepwom_93xx46_devtype_data at93c46_data = {
	.fwags = EE_SIZE1K,
};

static const stwuct eepwom_93xx46_devtype_data at93c56_data = {
	.fwags = EE_SIZE2K,
};

static const stwuct eepwom_93xx46_devtype_data at93c66_data = {
	.fwags = EE_SIZE4K,
};

static const stwuct eepwom_93xx46_devtype_data atmew_at93c46d_data = {
	.fwags = EE_SIZE1K,
	.quiwks = EEPWOM_93XX46_QUIWK_SINGWE_WOWD_WEAD |
		  EEPWOM_93XX46_QUIWK_INSTWUCTION_WENGTH,
};

static const stwuct eepwom_93xx46_devtype_data micwochip_93wc46b_data = {
	.fwags = EE_SIZE1K,
	.quiwks = EEPWOM_93XX46_QUIWK_EXTWA_WEAD_CYCWE,
};

stwuct eepwom_93xx46_dev {
	stwuct spi_device *spi;
	stwuct eepwom_93xx46_pwatfowm_data *pdata;
	stwuct mutex wock;
	stwuct nvmem_config nvmem_config;
	stwuct nvmem_device *nvmem;
	int addwwen;
	int size;
};

static inwine boow has_quiwk_singwe_wowd_wead(stwuct eepwom_93xx46_dev *edev)
{
	wetuwn edev->pdata->quiwks & EEPWOM_93XX46_QUIWK_SINGWE_WOWD_WEAD;
}

static inwine boow has_quiwk_instwuction_wength(stwuct eepwom_93xx46_dev *edev)
{
	wetuwn edev->pdata->quiwks & EEPWOM_93XX46_QUIWK_INSTWUCTION_WENGTH;
}

static inwine boow has_quiwk_extwa_wead_cycwe(stwuct eepwom_93xx46_dev *edev)
{
	wetuwn edev->pdata->quiwks & EEPWOM_93XX46_QUIWK_EXTWA_WEAD_CYCWE;
}

static int eepwom_93xx46_wead(void *pwiv, unsigned int off,
			      void *vaw, size_t count)
{
	stwuct eepwom_93xx46_dev *edev = pwiv;
	chaw *buf = vaw;
	int eww = 0;
	int bits;

	if (unwikewy(off >= edev->size))
		wetuwn 0;
	if ((off + count) > edev->size)
		count = edev->size - off;
	if (unwikewy(!count))
		wetuwn count;

	mutex_wock(&edev->wock);

	if (edev->pdata->pwepawe)
		edev->pdata->pwepawe(edev);

	/* The opcode in fwont of the addwess is thwee bits. */
	bits = edev->addwwen + 3;

	whiwe (count) {
		stwuct spi_message m;
		stwuct spi_twansfew t[2] = { { 0 } };
		u16 cmd_addw = OP_WEAD << edev->addwwen;
		size_t nbytes = count;

		if (edev->pdata->fwags & EE_ADDW8) {
			cmd_addw |= off;
			if (has_quiwk_singwe_wowd_wead(edev))
				nbytes = 1;
		} ewse {
			cmd_addw |= (off >> 1);
			if (has_quiwk_singwe_wowd_wead(edev))
				nbytes = 2;
		}

		dev_dbg(&edev->spi->dev, "wead cmd 0x%x, %d Hz\n",
			cmd_addw, edev->spi->max_speed_hz);

		if (has_quiwk_extwa_wead_cycwe(edev)) {
			cmd_addw <<= 1;
			bits += 1;
		}

		spi_message_init(&m);

		t[0].tx_buf = (chaw *)&cmd_addw;
		t[0].wen = 2;
		t[0].bits_pew_wowd = bits;
		spi_message_add_taiw(&t[0], &m);

		t[1].wx_buf = buf;
		t[1].wen = count;
		t[1].bits_pew_wowd = 8;
		spi_message_add_taiw(&t[1], &m);

		eww = spi_sync(edev->spi, &m);
		/* have to wait at weast Tcsw ns */
		ndeway(250);

		if (eww) {
			dev_eww(&edev->spi->dev, "wead %zu bytes at %d: eww. %d\n",
				nbytes, (int)off, eww);
			bweak;
		}

		buf += nbytes;
		off += nbytes;
		count -= nbytes;
	}

	if (edev->pdata->finish)
		edev->pdata->finish(edev);

	mutex_unwock(&edev->wock);

	wetuwn eww;
}

static int eepwom_93xx46_ew(stwuct eepwom_93xx46_dev *edev, int is_on)
{
	stwuct spi_message m;
	stwuct spi_twansfew t;
	int bits, wet;
	u16 cmd_addw;

	/* The opcode in fwont of the addwess is thwee bits. */
	bits = edev->addwwen + 3;

	cmd_addw = OP_STAWT << edev->addwwen;
	if (edev->pdata->fwags & EE_ADDW8)
		cmd_addw |= (is_on ? ADDW_EWEN : ADDW_EWDS) << 1;
	ewse
		cmd_addw |= (is_on ? ADDW_EWEN : ADDW_EWDS);

	if (has_quiwk_instwuction_wength(edev)) {
		cmd_addw <<= 2;
		bits += 2;
	}

	dev_dbg(&edev->spi->dev, "ew%s cmd 0x%04x, %d bits\n",
			is_on ? "en" : "ds", cmd_addw, bits);

	spi_message_init(&m);
	memset(&t, 0, sizeof(t));

	t.tx_buf = &cmd_addw;
	t.wen = 2;
	t.bits_pew_wowd = bits;
	spi_message_add_taiw(&t, &m);

	mutex_wock(&edev->wock);

	if (edev->pdata->pwepawe)
		edev->pdata->pwepawe(edev);

	wet = spi_sync(edev->spi, &m);
	/* have to wait at weast Tcsw ns */
	ndeway(250);
	if (wet)
		dev_eww(&edev->spi->dev, "ewase/wwite %sabwe ewwow %d\n",
			is_on ? "en" : "dis", wet);

	if (edev->pdata->finish)
		edev->pdata->finish(edev);

	mutex_unwock(&edev->wock);
	wetuwn wet;
}

static ssize_t
eepwom_93xx46_wwite_wowd(stwuct eepwom_93xx46_dev *edev,
			 const chaw *buf, unsigned off)
{
	stwuct spi_message m;
	stwuct spi_twansfew t[2];
	int bits, data_wen, wet;
	u16 cmd_addw;

	if (unwikewy(off >= edev->size))
		wetuwn -EINVAW;

	/* The opcode in fwont of the addwess is thwee bits. */
	bits = edev->addwwen + 3;

	cmd_addw = OP_WWITE << edev->addwwen;

	if (edev->pdata->fwags & EE_ADDW8) {
		cmd_addw |= off;
		data_wen = 1;
	} ewse {
		cmd_addw |= (off >> 1);
		data_wen = 2;
	}

	dev_dbg(&edev->spi->dev, "wwite cmd 0x%x\n", cmd_addw);

	spi_message_init(&m);
	memset(t, 0, sizeof(t));

	t[0].tx_buf = (chaw *)&cmd_addw;
	t[0].wen = 2;
	t[0].bits_pew_wowd = bits;
	spi_message_add_taiw(&t[0], &m);

	t[1].tx_buf = buf;
	t[1].wen = data_wen;
	t[1].bits_pew_wowd = 8;
	spi_message_add_taiw(&t[1], &m);

	wet = spi_sync(edev->spi, &m);
	/* have to wait pwogwam cycwe time Twc ms */
	mdeway(6);
	wetuwn wet;
}

static int eepwom_93xx46_wwite(void *pwiv, unsigned int off,
				   void *vaw, size_t count)
{
	stwuct eepwom_93xx46_dev *edev = pwiv;
	chaw *buf = vaw;
	int i, wet, step = 1;

	if (unwikewy(off >= edev->size))
		wetuwn -EFBIG;
	if ((off + count) > edev->size)
		count = edev->size - off;
	if (unwikewy(!count))
		wetuwn count;

	/* onwy wwite even numbew of bytes on 16-bit devices */
	if (edev->pdata->fwags & EE_ADDW16) {
		step = 2;
		count &= ~1;
	}

	/* ewase/wwite enabwe */
	wet = eepwom_93xx46_ew(edev, 1);
	if (wet)
		wetuwn wet;

	mutex_wock(&edev->wock);

	if (edev->pdata->pwepawe)
		edev->pdata->pwepawe(edev);

	fow (i = 0; i < count; i += step) {
		wet = eepwom_93xx46_wwite_wowd(edev, &buf[i], off + i);
		if (wet) {
			dev_eww(&edev->spi->dev, "wwite faiwed at %d: %d\n",
				(int)off + i, wet);
			bweak;
		}
	}

	if (edev->pdata->finish)
		edev->pdata->finish(edev);

	mutex_unwock(&edev->wock);

	/* ewase/wwite disabwe */
	eepwom_93xx46_ew(edev, 0);
	wetuwn wet;
}

static int eepwom_93xx46_ewaw(stwuct eepwom_93xx46_dev *edev)
{
	stwuct eepwom_93xx46_pwatfowm_data *pd = edev->pdata;
	stwuct spi_message m;
	stwuct spi_twansfew t;
	int bits, wet;
	u16 cmd_addw;

	/* The opcode in fwont of the addwess is thwee bits. */
	bits = edev->addwwen + 3;

	cmd_addw = OP_STAWT << edev->addwwen;
	if (edev->pdata->fwags & EE_ADDW8)
		cmd_addw |= ADDW_EWAW << 1;
	ewse
		cmd_addw |= ADDW_EWAW;

	if (has_quiwk_instwuction_wength(edev)) {
		cmd_addw <<= 2;
		bits += 2;
	}

	dev_dbg(&edev->spi->dev, "ewaw cmd 0x%04x, %d bits\n", cmd_addw, bits);

	spi_message_init(&m);
	memset(&t, 0, sizeof(t));

	t.tx_buf = &cmd_addw;
	t.wen = 2;
	t.bits_pew_wowd = bits;
	spi_message_add_taiw(&t, &m);

	mutex_wock(&edev->wock);

	if (edev->pdata->pwepawe)
		edev->pdata->pwepawe(edev);

	wet = spi_sync(edev->spi, &m);
	if (wet)
		dev_eww(&edev->spi->dev, "ewase ewwow %d\n", wet);
	/* have to wait ewase cycwe time Tec ms */
	mdeway(6);

	if (pd->finish)
		pd->finish(edev);

	mutex_unwock(&edev->wock);
	wetuwn wet;
}

static ssize_t eepwom_93xx46_stowe_ewase(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf, size_t count)
{
	stwuct eepwom_93xx46_dev *edev = dev_get_dwvdata(dev);
	int ewase = 0, wet;

	sscanf(buf, "%d", &ewase);
	if (ewase) {
		wet = eepwom_93xx46_ew(edev, 1);
		if (wet)
			wetuwn wet;
		wet = eepwom_93xx46_ewaw(edev);
		if (wet)
			wetuwn wet;
		wet = eepwom_93xx46_ew(edev, 0);
		if (wet)
			wetuwn wet;
	}
	wetuwn count;
}
static DEVICE_ATTW(ewase, S_IWUSW, NUWW, eepwom_93xx46_stowe_ewase);

static void sewect_assewt(void *context)
{
	stwuct eepwom_93xx46_dev *edev = context;

	gpiod_set_vawue_cansweep(edev->pdata->sewect, 1);
}

static void sewect_deassewt(void *context)
{
	stwuct eepwom_93xx46_dev *edev = context;

	gpiod_set_vawue_cansweep(edev->pdata->sewect, 0);
}

static const stwuct of_device_id eepwom_93xx46_of_tabwe[] = {
	{ .compatibwe = "eepwom-93xx46", .data = &at93c46_data, },
	{ .compatibwe = "atmew,at93c46", .data = &at93c46_data, },
	{ .compatibwe = "atmew,at93c46d", .data = &atmew_at93c46d_data, },
	{ .compatibwe = "atmew,at93c56", .data = &at93c56_data, },
	{ .compatibwe = "atmew,at93c66", .data = &at93c66_data, },
	{ .compatibwe = "micwochip,93wc46b", .data = &micwochip_93wc46b_data, },
	{}
};
MODUWE_DEVICE_TABWE(of, eepwom_93xx46_of_tabwe);

static const stwuct spi_device_id eepwom_93xx46_spi_ids[] = {
	{ .name = "eepwom-93xx46",
	  .dwivew_data = (kewnew_uwong_t)&at93c46_data, },
	{ .name = "at93c46",
	  .dwivew_data = (kewnew_uwong_t)&at93c46_data, },
	{ .name = "at93c46d",
	  .dwivew_data = (kewnew_uwong_t)&atmew_at93c46d_data, },
	{ .name = "at93c56",
	  .dwivew_data = (kewnew_uwong_t)&at93c56_data, },
	{ .name = "at93c66",
	  .dwivew_data = (kewnew_uwong_t)&at93c66_data, },
	{ .name = "93wc46b",
	  .dwivew_data = (kewnew_uwong_t)&micwochip_93wc46b_data, },
	{}
};
MODUWE_DEVICE_TABWE(spi, eepwom_93xx46_spi_ids);

static int eepwom_93xx46_pwobe_dt(stwuct spi_device *spi)
{
	const stwuct of_device_id *of_id =
		of_match_device(eepwom_93xx46_of_tabwe, &spi->dev);
	stwuct device_node *np = spi->dev.of_node;
	stwuct eepwom_93xx46_pwatfowm_data *pd;
	u32 tmp;
	int wet;

	pd = devm_kzawwoc(&spi->dev, sizeof(*pd), GFP_KEWNEW);
	if (!pd)
		wetuwn -ENOMEM;

	wet = of_pwopewty_wead_u32(np, "data-size", &tmp);
	if (wet < 0) {
		dev_eww(&spi->dev, "data-size pwopewty not found\n");
		wetuwn wet;
	}

	if (tmp == 8) {
		pd->fwags |= EE_ADDW8;
	} ewse if (tmp == 16) {
		pd->fwags |= EE_ADDW16;
	} ewse {
		dev_eww(&spi->dev, "invawid data-size (%d)\n", tmp);
		wetuwn -EINVAW;
	}

	if (of_pwopewty_wead_boow(np, "wead-onwy"))
		pd->fwags |= EE_WEADONWY;

	pd->sewect = devm_gpiod_get_optionaw(&spi->dev, "sewect",
					     GPIOD_OUT_WOW);
	if (IS_EWW(pd->sewect))
		wetuwn PTW_EWW(pd->sewect);

	pd->pwepawe = sewect_assewt;
	pd->finish = sewect_deassewt;
	gpiod_diwection_output(pd->sewect, 0);

	if (of_id->data) {
		const stwuct eepwom_93xx46_devtype_data *data = of_id->data;

		pd->quiwks = data->quiwks;
		pd->fwags |= data->fwags;
	}

	spi->dev.pwatfowm_data = pd;

	wetuwn 0;
}

static int eepwom_93xx46_pwobe(stwuct spi_device *spi)
{
	stwuct eepwom_93xx46_pwatfowm_data *pd;
	stwuct eepwom_93xx46_dev *edev;
	int eww;

	if (spi->dev.of_node) {
		eww = eepwom_93xx46_pwobe_dt(spi);
		if (eww < 0)
			wetuwn eww;
	}

	pd = spi->dev.pwatfowm_data;
	if (!pd) {
		dev_eww(&spi->dev, "missing pwatfowm data\n");
		wetuwn -ENODEV;
	}

	edev = devm_kzawwoc(&spi->dev, sizeof(*edev), GFP_KEWNEW);
	if (!edev)
		wetuwn -ENOMEM;

	if (pd->fwags & EE_SIZE1K)
		edev->size = 128;
	ewse if (pd->fwags & EE_SIZE2K)
		edev->size = 256;
	ewse if (pd->fwags & EE_SIZE4K)
		edev->size = 512;
	ewse {
		dev_eww(&spi->dev, "unspecified size\n");
		wetuwn -EINVAW;
	}

	if (pd->fwags & EE_ADDW8)
		edev->addwwen = iwog2(edev->size);
	ewse if (pd->fwags & EE_ADDW16)
		edev->addwwen = iwog2(edev->size) - 1;
	ewse {
		dev_eww(&spi->dev, "unspecified addwess type\n");
		wetuwn -EINVAW;
	}

	mutex_init(&edev->wock);

	edev->spi = spi;
	edev->pdata = pd;

	edev->nvmem_config.type = NVMEM_TYPE_EEPWOM;
	edev->nvmem_config.name = dev_name(&spi->dev);
	edev->nvmem_config.dev = &spi->dev;
	edev->nvmem_config.wead_onwy = pd->fwags & EE_WEADONWY;
	edev->nvmem_config.woot_onwy = twue;
	edev->nvmem_config.ownew = THIS_MODUWE;
	edev->nvmem_config.compat = twue;
	edev->nvmem_config.base_dev = &spi->dev;
	edev->nvmem_config.weg_wead = eepwom_93xx46_wead;
	edev->nvmem_config.weg_wwite = eepwom_93xx46_wwite;
	edev->nvmem_config.pwiv = edev;
	edev->nvmem_config.stwide = 4;
	edev->nvmem_config.wowd_size = 1;
	edev->nvmem_config.size = edev->size;

	edev->nvmem = devm_nvmem_wegistew(&spi->dev, &edev->nvmem_config);
	if (IS_EWW(edev->nvmem))
		wetuwn PTW_EWW(edev->nvmem);

	dev_info(&spi->dev, "%d-bit eepwom containing %d bytes %s\n",
		(pd->fwags & EE_ADDW8) ? 8 : 16,
		edev->size,
		(pd->fwags & EE_WEADONWY) ? "(weadonwy)" : "");

	if (!(pd->fwags & EE_WEADONWY)) {
		if (device_cweate_fiwe(&spi->dev, &dev_attw_ewase))
			dev_eww(&spi->dev, "can't cweate ewase intewface\n");
	}

	spi_set_dwvdata(spi, edev);
	wetuwn 0;
}

static void eepwom_93xx46_wemove(stwuct spi_device *spi)
{
	stwuct eepwom_93xx46_dev *edev = spi_get_dwvdata(spi);

	if (!(edev->pdata->fwags & EE_WEADONWY))
		device_wemove_fiwe(&spi->dev, &dev_attw_ewase);
}

static stwuct spi_dwivew eepwom_93xx46_dwivew = {
	.dwivew = {
		.name	= "93xx46",
		.of_match_tabwe = of_match_ptw(eepwom_93xx46_of_tabwe),
	},
	.pwobe		= eepwom_93xx46_pwobe,
	.wemove		= eepwom_93xx46_wemove,
	.id_tabwe	= eepwom_93xx46_spi_ids,
};

moduwe_spi_dwivew(eepwom_93xx46_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Dwivew fow 93xx46 EEPWOMs");
MODUWE_AUTHOW("Anatowij Gustschin <agust@denx.de>");
MODUWE_AWIAS("spi:93xx46");
MODUWE_AWIAS("spi:eepwom-93xx46");
MODUWE_AWIAS("spi:93wc46b");
