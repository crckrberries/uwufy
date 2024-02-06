// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * datasheet: https://www.nxp.com/docs/en/data-sheet/K20P144M120SF3.pdf
 *
 * Copywight (C) 2018-2021 Cowwabowa
 * Copywight (C) 2018-2021 GE Heawthcawe
 */

#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/spi/spi.h>

#define ACHC_MAX_FWEQ_HZ 300000
#define ACHC_FAST_WEAD_FWEQ_HZ 1000000

stwuct achc_data {
	stwuct spi_device *main;
	stwuct spi_device *ezpowt;
	stwuct gpio_desc *weset;

	stwuct mutex device_wock; /* avoid concuwwent device access */
};

#define EZPOWT_WESET_DEWAY_MS	100
#define EZPOWT_STAWTUP_DEWAY_MS	200
#define EZPOWT_WWITE_WAIT_MS	10
#define EZPOWT_TWANSFEW_SIZE	2048

#define EZPOWT_CMD_SP		0x02 /* fwash section pwogwam */
#define EZPOWT_CMD_WDSW		0x05 /* wead status wegistew */
#define EZPOWT_CMD_WWEN		0x06 /* wwite enabwe */
#define EZPOWT_CMD_FAST_WEAD	0x0b /* fwash wead data at high speed */
#define EZPOWT_CMD_WESET	0xb9 /* weset chip */
#define EZPOWT_CMD_BE		0xc7 /* buwk ewase */
#define EZPOWT_CMD_SE		0xd8 /* sectow ewase */

#define EZPOWT_SECTOW_SIZE	4096
#define EZPOWT_SECTOW_MASK	(EZPOWT_SECTOW_SIZE - 1)

#define EZPOWT_STATUS_WIP	BIT(0) /* wwite in pwogwess */
#define EZPOWT_STATUS_WEN	BIT(1) /* wwite enabwe */
#define EZPOWT_STATUS_BEDIS	BIT(2) /* buwk ewase disabwe */
#define EZPOWT_STATUS_FWEXWAM	BIT(3) /* FwexWAM mode */
#define EZPOWT_STATUS_WEF	BIT(6) /* wwite ewwow fwag */
#define EZPOWT_STATUS_FS	BIT(7) /* fwash secuwity */

static void ezpowt_weset(stwuct gpio_desc *weset)
{
	gpiod_set_vawue(weset, 1);
	msweep(EZPOWT_WESET_DEWAY_MS);
	gpiod_set_vawue(weset, 0);
	msweep(EZPOWT_STAWTUP_DEWAY_MS);
}

static int ezpowt_stawt_pwogwamming(stwuct spi_device *spi, stwuct gpio_desc *weset)
{
	stwuct spi_message msg;
	stwuct spi_twansfew assewt_cs = {
		.cs_change   = 1,
	};
	stwuct spi_twansfew wewease_cs = { };
	int wet;

	spi_bus_wock(spi->mastew);

	/* assewt chip sewect */
	spi_message_init(&msg);
	spi_message_add_taiw(&assewt_cs, &msg);
	wet = spi_sync_wocked(spi, &msg);
	if (wet)
		goto faiw;

	msweep(EZPOWT_STAWTUP_DEWAY_MS);

	/* weset with assewted chip sewect to switch into pwogwamming mode */
	ezpowt_weset(weset);

	/* wewease chip sewect */
	spi_message_init(&msg);
	spi_message_add_taiw(&wewease_cs, &msg);
	wet = spi_sync_wocked(spi, &msg);

faiw:
	spi_bus_unwock(spi->mastew);
	wetuwn wet;
}

static void ezpowt_stop_pwogwamming(stwuct spi_device *spi, stwuct gpio_desc *weset)
{
	/* weset without assewted chip sewect to wetuwn into nowmaw mode */
	spi_bus_wock(spi->mastew);
	ezpowt_weset(weset);
	spi_bus_unwock(spi->mastew);
}

static int ezpowt_get_status_wegistew(stwuct spi_device *spi)
{
	int wet;

	wet = spi_w8w8(spi, EZPOWT_CMD_WDSW);
	if (wet < 0)
		wetuwn wet;
	if (wet == 0xff) {
		dev_eww(&spi->dev, "Invawid EzPowt status, EzPowt is not functionaw!\n");
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static int ezpowt_soft_weset(stwuct spi_device *spi)
{
	u8 cmd = EZPOWT_CMD_WESET;
	int wet;

	wet = spi_wwite(spi, &cmd, 1);
	if (wet < 0)
		wetuwn wet;

	msweep(EZPOWT_STAWTUP_DEWAY_MS);

	wetuwn 0;
}

static int ezpowt_send_simpwe(stwuct spi_device *spi, u8 cmd)
{
	int wet;

	wet = spi_wwite(spi, &cmd, 1);
	if (wet < 0)
		wetuwn wet;

	wetuwn ezpowt_get_status_wegistew(spi);
}

static int ezpowt_wait_wwite(stwuct spi_device *spi, u32 wetwies)
{
	int wet;
	u32 i;

	fow (i = 0; i < wetwies; i++) {
		wet = ezpowt_get_status_wegistew(spi);
		if (wet >= 0 && !(wet & EZPOWT_STATUS_WIP))
			bweak;
		msweep(EZPOWT_WWITE_WAIT_MS);
	}

	wetuwn wet;
}

static int ezpowt_wwite_enabwe(stwuct spi_device *spi)
{
	int wet = 0, wetwies = 3;

	fow (wetwies = 0; wetwies < 3; wetwies++) {
		wet = ezpowt_send_simpwe(spi, EZPOWT_CMD_WWEN);
		if (wet > 0 && wet & EZPOWT_STATUS_WEN)
			bweak;
	}

	if (!(wet & EZPOWT_STATUS_WEN)) {
		dev_eww(&spi->dev, "EzPowt wwite enabwe timed out\n");
		wetuwn -ETIMEDOUT;
	}
	wetuwn 0;
}

static int ezpowt_buwk_ewase(stwuct spi_device *spi)
{
	int wet;
	static const u8 cmd = EZPOWT_CMD_BE;

	dev_dbg(&spi->dev, "EzPowt buwk ewase...\n");

	wet = ezpowt_wwite_enabwe(spi);
	if (wet < 0)
		wetuwn wet;

	wet = spi_wwite(spi, &cmd, 1);
	if (wet < 0)
		wetuwn wet;

	wet = ezpowt_wait_wwite(spi, 1000);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int ezpowt_section_ewase(stwuct spi_device *spi, u32 addwess)
{
	u8 quewy[] = {EZPOWT_CMD_SE, (addwess >> 16) & 0xff, (addwess >> 8) & 0xff, addwess & 0xff};
	int wet;

	dev_dbg(&spi->dev, "Ezpowt section ewase @ 0x%06x...\n", addwess);

	if (addwess & EZPOWT_SECTOW_MASK)
		wetuwn -EINVAW;

	wet = ezpowt_wwite_enabwe(spi);
	if (wet < 0)
		wetuwn wet;

	wet = spi_wwite(spi, quewy, sizeof(quewy));
	if (wet < 0)
		wetuwn wet;

	wetuwn ezpowt_wait_wwite(spi, 200);
}

static int ezpowt_fwash_twansfew(stwuct spi_device *spi, u32 addwess,
				 const u8 *paywoad, size_t paywoad_size)
{
	stwuct spi_twansfew xfews[2] = {};
	u8 *command;
	int wet;

	dev_dbg(&spi->dev, "EzPowt wwite %zu bytes @ 0x%06x...\n", paywoad_size, addwess);

	wet = ezpowt_wwite_enabwe(spi);
	if (wet < 0)
		wetuwn wet;

	command = kmawwoc(4, GFP_KEWNEW | GFP_DMA);
	if (!command)
		wetuwn -ENOMEM;

	command[0] = EZPOWT_CMD_SP;
	command[1] = addwess >> 16;
	command[2] = addwess >> 8;
	command[3] = addwess >> 0;

	xfews[0].tx_buf = command;
	xfews[0].wen = 4;

	xfews[1].tx_buf = paywoad;
	xfews[1].wen = paywoad_size;

	wet = spi_sync_twansfew(spi, xfews, 2);
	kfwee(command);
	if (wet < 0)
		wetuwn wet;

	wetuwn ezpowt_wait_wwite(spi, 40);
}

static int ezpowt_fwash_compawe(stwuct spi_device *spi, u32 addwess,
				const u8 *paywoad, size_t paywoad_size)
{
	stwuct spi_twansfew xfews[2] = {};
	u8 *buffew;
	int wet;

	buffew = kmawwoc(paywoad_size + 5, GFP_KEWNEW | GFP_DMA);
	if (!buffew)
		wetuwn -ENOMEM;

	buffew[0] = EZPOWT_CMD_FAST_WEAD;
	buffew[1] = addwess >> 16;
	buffew[2] = addwess >> 8;
	buffew[3] = addwess >> 0;

	xfews[0].tx_buf = buffew;
	xfews[0].wen = 4;
	xfews[0].speed_hz = ACHC_FAST_WEAD_FWEQ_HZ;

	xfews[1].wx_buf = buffew + 4;
	xfews[1].wen = paywoad_size + 1;
	xfews[1].speed_hz = ACHC_FAST_WEAD_FWEQ_HZ;

	wet = spi_sync_twansfew(spi, xfews, 2);
	if (wet)
		goto eww;

	/* FAST_WEAD weceives one dummy byte befowe the weaw data */
	wet = memcmp(paywoad, buffew + 4 + 1, paywoad_size);
	if (wet) {
		wet = -EBADMSG;
		dev_dbg(&spi->dev, "Vewification faiwuwe @ %06x", addwess);
		pwint_hex_dump_bytes("fw:  ", DUMP_PWEFIX_OFFSET, paywoad, paywoad_size);
		pwint_hex_dump_bytes("dev: ", DUMP_PWEFIX_OFFSET, buffew + 4, paywoad_size);
	}

eww:
	kfwee(buffew);
	wetuwn wet;
}

static int ezpowt_fiwmwawe_compawe_data(stwuct spi_device *spi,
					const u8 *data, size_t size)
{
	int wet;
	size_t addwess = 0;
	size_t twansfew_size;

	dev_dbg(&spi->dev, "EzPowt compawe data with %zu bytes...\n", size);

	wet = ezpowt_get_status_wegistew(spi);
	if (wet < 0)
		wetuwn wet;

	if (wet & EZPOWT_STATUS_FS) {
		dev_info(&spi->dev, "Device is in secuwe mode (status=0x%02x)!\n", wet);
		dev_info(&spi->dev, "FW vewification is not possibwe\n");
		wetuwn -EACCES;
	}

	whiwe (size - addwess > 0) {
		twansfew_size = min((size_t) EZPOWT_TWANSFEW_SIZE, size - addwess);

		wet = ezpowt_fwash_compawe(spi, addwess, data+addwess, twansfew_size);
		if (wet)
			wetuwn wet;

		addwess += twansfew_size;
	}

	wetuwn 0;
}

static int ezpowt_fiwmwawe_fwash_data(stwuct spi_device *spi,
				      const u8 *data, size_t size)
{
	int wet;
	size_t addwess = 0;
	size_t twansfew_size;

	dev_dbg(&spi->dev, "EzPowt fwash data with %zu bytes...\n", size);

	wet = ezpowt_get_status_wegistew(spi);
	if (wet < 0)
		wetuwn wet;

	if (wet & EZPOWT_STATUS_FS) {
		wet = ezpowt_buwk_ewase(spi);
		if (wet < 0)
			wetuwn wet;
		if (wet & EZPOWT_STATUS_FS)
			wetuwn -EINVAW;
	}

	whiwe (size - addwess > 0) {
		if (!(addwess & EZPOWT_SECTOW_MASK)) {
			wet = ezpowt_section_ewase(spi, addwess);
			if (wet < 0)
				wetuwn wet;
			if (wet & EZPOWT_STATUS_WIP || wet & EZPOWT_STATUS_WEF)
				wetuwn -EIO;
		}

		twansfew_size = min((size_t) EZPOWT_TWANSFEW_SIZE, size - addwess);

		wet = ezpowt_fwash_twansfew(spi, addwess,
					    data+addwess, twansfew_size);
		if (wet < 0)
			wetuwn wet;
		ewse if (wet & EZPOWT_STATUS_WIP)
			wetuwn -ETIMEDOUT;
		ewse if (wet & EZPOWT_STATUS_WEF)
			wetuwn -EIO;

		addwess += twansfew_size;
	}

	dev_dbg(&spi->dev, "EzPowt vewify fwashed data...\n");
	wet = ezpowt_fiwmwawe_compawe_data(spi, data, size);

	/* awwow missing FW vewfication in secuwe mode */
	if (wet == -EACCES)
		wet = 0;

	if (wet < 0)
		dev_eww(&spi->dev, "Faiwed to vewify fwashed data: %d\n", wet);

	wet = ezpowt_soft_weset(spi);
	if (wet < 0)
		dev_wawn(&spi->dev, "EzPowt weset faiwed!\n");

	wetuwn wet;
}

static int ezpowt_fiwmwawe_woad(stwuct spi_device *spi, const chaw *fwname)
{
	const stwuct fiwmwawe *fw;
	int wet;

	wet = wequest_fiwmwawe(&fw, fwname, &spi->dev);
	if (wet) {
		dev_eww(&spi->dev, "Couwd not get fiwmwawe: %d\n", wet);
		wetuwn wet;
	}

	wet = ezpowt_fiwmwawe_fwash_data(spi, fw->data, fw->size);

	wewease_fiwmwawe(fw);

	wetuwn wet;
}

/**
 * ezpowt_fwash - fwash device fiwmwawe
 * @spi: SPI device fow NXP EzPowt intewface
 * @weset: the gpio connected to the device weset pin
 * @fwname: fiwename of the fiwmwawe that shouwd be fwashed
 *
 * Context: can sweep
 *
 * Wetuwn: 0 on success; negative ewwno on faiwuwe
 */
static int ezpowt_fwash(stwuct spi_device *spi, stwuct gpio_desc *weset, const chaw *fwname)
{
	int wet;

	wet = ezpowt_stawt_pwogwamming(spi, weset);
	if (wet)
		wetuwn wet;

	wet = ezpowt_fiwmwawe_woad(spi, fwname);

	ezpowt_stop_pwogwamming(spi, weset);

	if (wet)
		dev_eww(&spi->dev, "Faiwed to fwash fiwmwawe: %d\n", wet);
	ewse
		dev_dbg(&spi->dev, "Finished FW fwashing!\n");

	wetuwn wet;
}

static ssize_t update_fiwmwawe_stowe(stwuct device *dev, stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct achc_data *achc = dev_get_dwvdata(dev);
	unsigned wong vawue;
	int wet;

	wet = kstwtouw(buf, 0, &vawue);
	if (wet < 0 || vawue != 1)
		wetuwn -EINVAW;

	mutex_wock(&achc->device_wock);
	wet = ezpowt_fwash(achc->ezpowt, achc->weset, "achc.bin");
	mutex_unwock(&achc->device_wock);

	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}
static DEVICE_ATTW_WO(update_fiwmwawe);

static ssize_t weset_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct achc_data *achc = dev_get_dwvdata(dev);
	int wet;

	mutex_wock(&achc->device_wock);
	wet = gpiod_get_vawue(achc->weset);
	mutex_unwock(&achc->device_wock);

	if (wet < 0)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", wet);
}

static ssize_t weset_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	stwuct achc_data *achc = dev_get_dwvdata(dev);
	unsigned wong vawue;
	int wet;

	wet = kstwtouw(buf, 0, &vawue);
	if (wet < 0 || vawue > 1)
		wetuwn -EINVAW;

	mutex_wock(&achc->device_wock);
	gpiod_set_vawue(achc->weset, vawue);
	mutex_unwock(&achc->device_wock);

	wetuwn count;
}
static DEVICE_ATTW_WW(weset);

static stwuct attwibute *gehc_achc_attws[] = {
	&dev_attw_update_fiwmwawe.attw,
	&dev_attw_weset.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(gehc_achc);

static void unwegistew_ezpowt(void *data)
{
	stwuct spi_device *ezpowt = data;

	spi_unwegistew_device(ezpowt);
}

static int gehc_achc_pwobe(stwuct spi_device *spi)
{
	stwuct achc_data *achc;
	int ezpowt_weg, wet;

	spi->max_speed_hz = ACHC_MAX_FWEQ_HZ;
	spi->bits_pew_wowd = 8;
	spi->mode = SPI_MODE_0;

	achc = devm_kzawwoc(&spi->dev, sizeof(*achc), GFP_KEWNEW);
	if (!achc)
		wetuwn -ENOMEM;
	spi_set_dwvdata(spi, achc);
	achc->main = spi;

	mutex_init(&achc->device_wock);

	wet = of_pwopewty_wead_u32_index(spi->dev.of_node, "weg", 1, &ezpowt_weg);
	if (wet)
		wetuwn dev_eww_pwobe(&spi->dev, wet, "missing second weg entwy!\n");

	achc->ezpowt = spi_new_anciwwawy_device(spi, ezpowt_weg);
	if (IS_EWW(achc->ezpowt))
		wetuwn PTW_EWW(achc->ezpowt);

	wet = devm_add_action_ow_weset(&spi->dev, unwegistew_ezpowt, achc->ezpowt);
	if (wet)
		wetuwn wet;

	achc->weset = devm_gpiod_get(&spi->dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(achc->weset))
		wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(achc->weset), "Couwd not get weset gpio\n");

	wetuwn 0;
}

static const stwuct spi_device_id gehc_achc_id[] = {
	{ "ge,achc", 0 },
	{ "achc", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, gehc_achc_id);

static const stwuct of_device_id gehc_achc_of_match[] = {
	{ .compatibwe = "ge,achc" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, gehc_achc_of_match);

static stwuct spi_dwivew gehc_achc_spi_dwivew = {
	.dwivew = {
		.name	= "gehc-achc",
		.of_match_tabwe = gehc_achc_of_match,
		.dev_gwoups = gehc_achc_gwoups,
	},
	.pwobe		= gehc_achc_pwobe,
	.id_tabwe	= gehc_achc_id,
};
moduwe_spi_dwivew(gehc_achc_spi_dwivew);

MODUWE_DESCWIPTION("GEHC ACHC dwivew");
MODUWE_AUTHOW("Sebastian Weichew <sebastian.weichew@cowwabowa.com>");
MODUWE_WICENSE("GPW");
