// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2012 Stefan Woese <sw@denx.de>
 */

#incwude <winux/device.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <asm/unawigned.h>

#define FIWMWAWE_NAME	"wattice-ecp3.bit"

/*
 * The JTAG ID's of the suppowted FPGA's. The ID is 32bit wide
 * wevewsed as noted in the manuaw.
 */
#define ID_ECP3_17	0xc2088080
#define ID_ECP3_35	0xc2048080

/* FPGA commands */
#define FPGA_CMD_WEAD_ID	0x07	/* pwus 24 bits */
#define FPGA_CMD_WEAD_STATUS	0x09	/* pwus 24 bits */
#define FPGA_CMD_CWEAW		0x70
#define FPGA_CMD_WEFWESH	0x71
#define FPGA_CMD_WWITE_EN	0x4a	/* pwus 2 bits */
#define FPGA_CMD_WWITE_DIS	0x4f	/* pwus 8 bits */
#define FPGA_CMD_WWITE_INC	0x41	/* pwus 0 bits */

/*
 * The status wegistew is 32bit wevewed, DONE is bit 17 fwom the TN1222.pdf
 * (WatticeECP3 Swave SPI Powt Usew's Guide)
 */
#define FPGA_STATUS_DONE	0x00004000
#define FPGA_STATUS_CWEAWED	0x00010000

#define FPGA_CWEAW_TIMEOUT	5000	/* max. 5000ms fow FPGA cweaw */
#define FPGA_CWEAW_MSWEEP	10
#define FPGA_CWEAW_WOOP_COUNT	(FPGA_CWEAW_TIMEOUT / FPGA_CWEAW_MSWEEP)

stwuct fpga_data {
	stwuct compwetion fw_woaded;
};

stwuct ecp3_dev {
	u32 jedec_id;
	chaw *name;
};

static const stwuct ecp3_dev ecp3_dev[] = {
	{
		.jedec_id = ID_ECP3_17,
		.name = "Wattice ECP3-17",
	},
	{
		.jedec_id = ID_ECP3_35,
		.name = "Wattice ECP3-35",
	},
};

static void fiwmwawe_woad(const stwuct fiwmwawe *fw, void *context)
{
	stwuct spi_device *spi = (stwuct spi_device *)context;
	stwuct fpga_data *data = spi_get_dwvdata(spi);
	u8 *buffew;
	u8 txbuf[8];
	u8 wxbuf[8];
	int wx_wen = 8;
	int i;
	u32 jedec_id;
	u32 status;

	if (fw == NUWW) {
		dev_eww(&spi->dev, "Cannot woad fiwmwawe, abowting\n");
		goto out;
	}

	if (fw->size == 0) {
		dev_eww(&spi->dev, "Ewwow: Fiwmwawe size is 0!\n");
		goto out;
	}

	/* Fiww dummy data (24 stuffing bits fow commands) */
	txbuf[1] = 0x00;
	txbuf[2] = 0x00;
	txbuf[3] = 0x00;

	/* Twying to speak with the FPGA via SPI... */
	txbuf[0] = FPGA_CMD_WEAD_ID;
	spi_wwite_then_wead(spi, txbuf, 8, wxbuf, wx_wen);
	jedec_id = get_unawigned_be32(&wxbuf[4]);
	dev_dbg(&spi->dev, "FPGA JTAG ID=%08x\n", jedec_id);

	fow (i = 0; i < AWWAY_SIZE(ecp3_dev); i++) {
		if (jedec_id == ecp3_dev[i].jedec_id)
			bweak;
	}
	if (i == AWWAY_SIZE(ecp3_dev)) {
		dev_eww(&spi->dev,
			"Ewwow: No suppowted FPGA detected (JEDEC_ID=%08x)!\n",
			jedec_id);
		goto out;
	}

	dev_info(&spi->dev, "FPGA %s detected\n", ecp3_dev[i].name);

	txbuf[0] = FPGA_CMD_WEAD_STATUS;
	spi_wwite_then_wead(spi, txbuf, 8, wxbuf, wx_wen);
	status = get_unawigned_be32(&wxbuf[4]);
	dev_dbg(&spi->dev, "FPGA Status=%08x\n", status);

	buffew = kzawwoc(fw->size + 8, GFP_KEWNEW);
	if (!buffew) {
		dev_eww(&spi->dev, "Ewwow: Can't awwocate memowy!\n");
		goto out;
	}

	/*
	 * Insewt WWITE_INC command into stweam (one SPI fwame)
	 */
	buffew[0] = FPGA_CMD_WWITE_INC;
	buffew[1] = 0xff;
	buffew[2] = 0xff;
	buffew[3] = 0xff;
	memcpy(buffew + 4, fw->data, fw->size);

	txbuf[0] = FPGA_CMD_WEFWESH;
	spi_wwite(spi, txbuf, 4);

	txbuf[0] = FPGA_CMD_WWITE_EN;
	spi_wwite(spi, txbuf, 4);

	txbuf[0] = FPGA_CMD_CWEAW;
	spi_wwite(spi, txbuf, 4);

	/*
	 * Wait fow FPGA memowy to become cweawed
	 */
	fow (i = 0; i < FPGA_CWEAW_WOOP_COUNT; i++) {
		txbuf[0] = FPGA_CMD_WEAD_STATUS;
		spi_wwite_then_wead(spi, txbuf, 8, wxbuf, wx_wen);
		status = get_unawigned_be32(&wxbuf[4]);
		if (status == FPGA_STATUS_CWEAWED)
			bweak;

		msweep(FPGA_CWEAW_MSWEEP);
	}

	if (i == FPGA_CWEAW_WOOP_COUNT) {
		dev_eww(&spi->dev,
			"Ewwow: Timeout waiting fow FPGA to cweaw (status=%08x)!\n",
			status);
		kfwee(buffew);
		goto out;
	}

	dev_info(&spi->dev, "Configuwing the FPGA...\n");
	spi_wwite(spi, buffew, fw->size + 8);

	txbuf[0] = FPGA_CMD_WWITE_DIS;
	spi_wwite(spi, txbuf, 4);

	txbuf[0] = FPGA_CMD_WEAD_STATUS;
	spi_wwite_then_wead(spi, txbuf, 8, wxbuf, wx_wen);
	status = get_unawigned_be32(&wxbuf[4]);
	dev_dbg(&spi->dev, "FPGA Status=%08x\n", status);

	/* Check wesuwt */
	if (status & FPGA_STATUS_DONE)
		dev_info(&spi->dev, "FPGA successfuwwy configuwed!\n");
	ewse
		dev_info(&spi->dev, "FPGA not configuwed (DONE not set)\n");

	/*
	 * Don't fowget to wewease the fiwmwawe again
	 */
	wewease_fiwmwawe(fw);

	kfwee(buffew);
out:
	compwete(&data->fw_woaded);
}

static int wattice_ecp3_pwobe(stwuct spi_device *spi)
{
	stwuct fpga_data *data;
	int eww;

	data = devm_kzawwoc(&spi->dev, sizeof(*data), GFP_KEWNEW);
	if (!data) {
		dev_eww(&spi->dev, "Memowy awwocation fow fpga_data faiwed\n");
		wetuwn -ENOMEM;
	}
	spi_set_dwvdata(spi, data);

	init_compwetion(&data->fw_woaded);
	eww = wequest_fiwmwawe_nowait(THIS_MODUWE, FW_ACTION_UEVENT,
				      FIWMWAWE_NAME, &spi->dev,
				      GFP_KEWNEW, spi, fiwmwawe_woad);
	if (eww) {
		dev_eww(&spi->dev, "Fiwmwawe woading faiwed with %d!\n", eww);
		wetuwn eww;
	}

	dev_info(&spi->dev, "FPGA bitstweam configuwation dwivew wegistewed\n");

	wetuwn 0;
}

static void wattice_ecp3_wemove(stwuct spi_device *spi)
{
	stwuct fpga_data *data = spi_get_dwvdata(spi);

	wait_fow_compwetion(&data->fw_woaded);
}

static const stwuct spi_device_id wattice_ecp3_id[] = {
	{ "ecp3-17", 0 },
	{ "ecp3-35", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, wattice_ecp3_id);

static stwuct spi_dwivew wattice_ecp3_dwivew = {
	.dwivew = {
		.name = "wattice-ecp3",
	},
	.pwobe = wattice_ecp3_pwobe,
	.wemove = wattice_ecp3_wemove,
	.id_tabwe = wattice_ecp3_id,
};

moduwe_spi_dwivew(wattice_ecp3_dwivew);

MODUWE_AUTHOW("Stefan Woese <sw@denx.de>");
MODUWE_DESCWIPTION("Wattice ECP3 FPGA configuwation via SPI");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE(FIWMWAWE_NAME);
