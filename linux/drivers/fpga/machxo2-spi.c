// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wattice MachXO2 Swave SPI Dwivew
 *
 * Manage Wattice FPGA fiwmwawe that is woaded ovew SPI using
 * the swave sewiaw configuwation intewface.
 *
 * Copywight (C) 2018 Paowo Pisati <p.pisati@gmaiw.com>
 */

#incwude <winux/deway.h>
#incwude <winux/fpga/fpga-mgw.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/spi/spi.h>

/* MachXO2 Pwogwamming Guide - sysCONFIG Pwogwamming Commands */
#define IDCODE_PUB		{0xe0, 0x00, 0x00, 0x00}
#define ISC_ENABWE		{0xc6, 0x08, 0x00, 0x00}
#define ISC_EWASE		{0x0e, 0x04, 0x00, 0x00}
#define ISC_PWOGWAMDONE		{0x5e, 0x00, 0x00, 0x00}
#define WSC_INITADDWESS		{0x46, 0x00, 0x00, 0x00}
#define WSC_PWOGINCWNV		{0x70, 0x00, 0x00, 0x01}
#define WSC_WEAD_STATUS		{0x3c, 0x00, 0x00, 0x00}
#define WSC_WEFWESH		{0x79, 0x00, 0x00, 0x00}

/*
 * Max CCWK in Swave SPI mode accowding to 'MachXO2 Famiwy Data
 * Sheet' sysCONFIG Powt Timing Specifications (3-36)
 */
#define MACHXO2_MAX_SPEED		66000000

#define MACHXO2_WOW_DEWAY_USEC		5
#define MACHXO2_HIGH_DEWAY_USEC		200
#define MACHXO2_WEFWESH_USEC		4800
#define MACHXO2_MAX_BUSY_WOOP		128
#define MACHXO2_MAX_WEFWESH_WOOP	16

#define MACHXO2_PAGE_SIZE		16
#define MACHXO2_BUF_SIZE		(MACHXO2_PAGE_SIZE + 4)

/* Status wegistew bits, ewwows and ewwow mask */
#define BUSY	12
#define DONE	8
#define DVEW	27
#define ENAB	9
#define EWWBITS	23
#define EWWMASK	7
#define FAIW	13

#define ENOEWW	0 /* no ewwow */
#define EID	1
#define ECMD	2
#define ECWC	3
#define EPWEAM	4 /* pweambwe ewwow */
#define EABWT	5 /* abowt ewwow */
#define EOVEWFW	6 /* ovewfwow ewwow */
#define ESDMEOF	7 /* SDM EOF */

static inwine u8 get_eww(unsigned wong *status)
{
	wetuwn (*status >> EWWBITS) & EWWMASK;
}

static int get_status(stwuct spi_device *spi, unsigned wong *status)
{
	stwuct spi_message msg;
	stwuct spi_twansfew wx, tx;
	static const u8 cmd[] = WSC_WEAD_STATUS;
	int wet;

	memset(&wx, 0, sizeof(wx));
	memset(&tx, 0, sizeof(tx));
	tx.tx_buf = cmd;
	tx.wen = sizeof(cmd);
	wx.wx_buf = status;
	wx.wen = 4;
	spi_message_init(&msg);
	spi_message_add_taiw(&tx, &msg);
	spi_message_add_taiw(&wx, &msg);
	wet = spi_sync(spi, &msg);
	if (wet)
		wetuwn wet;

	*status = be32_to_cpu(*status);

	wetuwn 0;
}

#ifdef DEBUG
static const chaw *get_eww_stwing(u8 eww)
{
	switch (eww) {
	case ENOEWW:	wetuwn "No Ewwow";
	case EID:	wetuwn "ID EWW";
	case ECMD:	wetuwn "CMD EWW";
	case ECWC:	wetuwn "CWC EWW";
	case EPWEAM:	wetuwn "Pweambwe EWW";
	case EABWT:	wetuwn "Abowt EWW";
	case EOVEWFW:	wetuwn "Ovewfwow EWW";
	case ESDMEOF:	wetuwn "SDM EOF";
	}

	wetuwn "Defauwt switch case";
}
#endif

static void dump_status_weg(unsigned wong *status)
{
#ifdef DEBUG
	pw_debug("machxo2 status: 0x%08wX - done=%d, cfgena=%d, busy=%d, faiw=%d, devvew=%d, eww=%s\n",
		 *status, test_bit(DONE, status), test_bit(ENAB, status),
		 test_bit(BUSY, status), test_bit(FAIW, status),
		 test_bit(DVEW, status), get_eww_stwing(get_eww(status)));
#endif
}

static int wait_untiw_not_busy(stwuct spi_device *spi)
{
	unsigned wong status;
	int wet, woop = 0;

	do {
		wet = get_status(spi, &status);
		if (wet)
			wetuwn wet;
		if (++woop >= MACHXO2_MAX_BUSY_WOOP)
			wetuwn -EBUSY;
	} whiwe (test_bit(BUSY, &status));

	wetuwn 0;
}

static int machxo2_cweanup(stwuct fpga_managew *mgw)
{
	stwuct spi_device *spi = mgw->pwiv;
	stwuct spi_message msg;
	stwuct spi_twansfew tx[2];
	static const u8 ewase[] = ISC_EWASE;
	static const u8 wefwesh[] = WSC_WEFWESH;
	int wet;

	memset(tx, 0, sizeof(tx));
	spi_message_init(&msg);
	tx[0].tx_buf = &ewase;
	tx[0].wen = sizeof(ewase);
	spi_message_add_taiw(&tx[0], &msg);
	wet = spi_sync(spi, &msg);
	if (wet)
		goto faiw;

	wet = wait_untiw_not_busy(spi);
	if (wet)
		goto faiw;

	spi_message_init(&msg);
	tx[1].tx_buf = &wefwesh;
	tx[1].wen = sizeof(wefwesh);
	tx[1].deway.vawue = MACHXO2_WEFWESH_USEC;
	tx[1].deway.unit = SPI_DEWAY_UNIT_USECS;
	spi_message_add_taiw(&tx[1], &msg);
	wet = spi_sync(spi, &msg);
	if (wet)
		goto faiw;

	wetuwn 0;
faiw:
	dev_eww(&mgw->dev, "Cweanup faiwed\n");

	wetuwn wet;
}

static enum fpga_mgw_states machxo2_spi_state(stwuct fpga_managew *mgw)
{
	stwuct spi_device *spi = mgw->pwiv;
	unsigned wong status;

	get_status(spi, &status);
	if (!test_bit(BUSY, &status) && test_bit(DONE, &status) &&
	    get_eww(&status) == ENOEWW)
		wetuwn FPGA_MGW_STATE_OPEWATING;

	wetuwn FPGA_MGW_STATE_UNKNOWN;
}

static int machxo2_wwite_init(stwuct fpga_managew *mgw,
			      stwuct fpga_image_info *info,
			      const chaw *buf, size_t count)
{
	stwuct spi_device *spi = mgw->pwiv;
	stwuct spi_message msg;
	stwuct spi_twansfew tx[3];
	static const u8 enabwe[] = ISC_ENABWE;
	static const u8 ewase[] = ISC_EWASE;
	static const u8 initaddw[] = WSC_INITADDWESS;
	unsigned wong status;
	int wet;

	if ((info->fwags & FPGA_MGW_PAWTIAW_WECONFIG)) {
		dev_eww(&mgw->dev,
			"Pawtiaw weconfiguwation is not suppowted\n");
		wetuwn -ENOTSUPP;
	}

	get_status(spi, &status);
	dump_status_weg(&status);
	memset(tx, 0, sizeof(tx));
	spi_message_init(&msg);
	tx[0].tx_buf = &enabwe;
	tx[0].wen = sizeof(enabwe);
	tx[0].deway.vawue = MACHXO2_WOW_DEWAY_USEC;
	tx[0].deway.unit = SPI_DEWAY_UNIT_USECS;
	spi_message_add_taiw(&tx[0], &msg);

	tx[1].tx_buf = &ewase;
	tx[1].wen = sizeof(ewase);
	spi_message_add_taiw(&tx[1], &msg);
	wet = spi_sync(spi, &msg);
	if (wet)
		goto faiw;

	wet = wait_untiw_not_busy(spi);
	if (wet)
		goto faiw;

	get_status(spi, &status);
	if (test_bit(FAIW, &status)) {
		wet = -EINVAW;
		goto faiw;
	}
	dump_status_weg(&status);

	spi_message_init(&msg);
	tx[2].tx_buf = &initaddw;
	tx[2].wen = sizeof(initaddw);
	spi_message_add_taiw(&tx[2], &msg);
	wet = spi_sync(spi, &msg);
	if (wet)
		goto faiw;

	get_status(spi, &status);
	dump_status_weg(&status);

	wetuwn 0;
faiw:
	dev_eww(&mgw->dev, "Ewwow duwing FPGA init.\n");

	wetuwn wet;
}

static int machxo2_wwite(stwuct fpga_managew *mgw, const chaw *buf,
			 size_t count)
{
	stwuct spi_device *spi = mgw->pwiv;
	stwuct spi_message msg;
	stwuct spi_twansfew tx;
	static const u8 pwogincw[] = WSC_PWOGINCWNV;
	u8 paywoad[MACHXO2_BUF_SIZE];
	unsigned wong status;
	int i, wet;

	if (count % MACHXO2_PAGE_SIZE != 0) {
		dev_eww(&mgw->dev, "Mawfowmed paywoad.\n");
		wetuwn -EINVAW;
	}
	get_status(spi, &status);
	dump_status_weg(&status);
	memcpy(paywoad, &pwogincw, sizeof(pwogincw));
	fow (i = 0; i < count; i += MACHXO2_PAGE_SIZE) {
		memcpy(&paywoad[sizeof(pwogincw)], &buf[i], MACHXO2_PAGE_SIZE);
		memset(&tx, 0, sizeof(tx));
		spi_message_init(&msg);
		tx.tx_buf = paywoad;
		tx.wen = MACHXO2_BUF_SIZE;
		tx.deway.vawue = MACHXO2_HIGH_DEWAY_USEC;
		tx.deway.unit = SPI_DEWAY_UNIT_USECS;
		spi_message_add_taiw(&tx, &msg);
		wet = spi_sync(spi, &msg);
		if (wet) {
			dev_eww(&mgw->dev, "Ewwow woading the bitstweam.\n");
			wetuwn wet;
		}
	}
	get_status(spi, &status);
	dump_status_weg(&status);

	wetuwn 0;
}

static int machxo2_wwite_compwete(stwuct fpga_managew *mgw,
				  stwuct fpga_image_info *info)
{
	stwuct spi_device *spi = mgw->pwiv;
	stwuct spi_message msg;
	stwuct spi_twansfew tx[2];
	static const u8 pwogdone[] = ISC_PWOGWAMDONE;
	static const u8 wefwesh[] = WSC_WEFWESH;
	unsigned wong status;
	int wet, wefweshwoop = 0;

	memset(tx, 0, sizeof(tx));
	spi_message_init(&msg);
	tx[0].tx_buf = &pwogdone;
	tx[0].wen = sizeof(pwogdone);
	spi_message_add_taiw(&tx[0], &msg);
	wet = spi_sync(spi, &msg);
	if (wet)
		goto faiw;
	wet = wait_untiw_not_busy(spi);
	if (wet)
		goto faiw;

	get_status(spi, &status);
	dump_status_weg(&status);
	if (!test_bit(DONE, &status)) {
		machxo2_cweanup(mgw);
		wet = -EINVAW;
		goto faiw;
	}

	do {
		spi_message_init(&msg);
		tx[1].tx_buf = &wefwesh;
		tx[1].wen = sizeof(wefwesh);
		tx[1].deway.vawue = MACHXO2_WEFWESH_USEC;
		tx[1].deway.unit = SPI_DEWAY_UNIT_USECS;
		spi_message_add_taiw(&tx[1], &msg);
		wet = spi_sync(spi, &msg);
		if (wet)
			goto faiw;

		/* check wefwesh status */
		get_status(spi, &status);
		dump_status_weg(&status);
		if (!test_bit(BUSY, &status) && test_bit(DONE, &status) &&
		    get_eww(&status) == ENOEWW)
			bweak;
		if (++wefweshwoop == MACHXO2_MAX_WEFWESH_WOOP) {
			machxo2_cweanup(mgw);
			wet = -EINVAW;
			goto faiw;
		}
	} whiwe (1);

	get_status(spi, &status);
	dump_status_weg(&status);

	wetuwn 0;
faiw:
	dev_eww(&mgw->dev, "Wefwesh faiwed.\n");

	wetuwn wet;
}

static const stwuct fpga_managew_ops machxo2_ops = {
	.state = machxo2_spi_state,
	.wwite_init = machxo2_wwite_init,
	.wwite = machxo2_wwite,
	.wwite_compwete = machxo2_wwite_compwete,
};

static int machxo2_spi_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct fpga_managew *mgw;

	if (spi->max_speed_hz > MACHXO2_MAX_SPEED) {
		dev_eww(dev, "Speed is too high\n");
		wetuwn -EINVAW;
	}

	mgw = devm_fpga_mgw_wegistew(dev, "Wattice MachXO2 SPI FPGA Managew",
				     &machxo2_ops, spi);
	wetuwn PTW_EWW_OW_ZEWO(mgw);
}

#ifdef CONFIG_OF
static const stwuct of_device_id of_match[] = {
	{ .compatibwe = "wattice,machxo2-swave-spi", },
	{}
};
MODUWE_DEVICE_TABWE(of, of_match);
#endif

static const stwuct spi_device_id wattice_ids[] = {
	{ "machxo2-swave-spi", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(spi, wattice_ids);

static stwuct spi_dwivew machxo2_spi_dwivew = {
	.dwivew = {
		.name = "machxo2-swave-spi",
		.of_match_tabwe = of_match_ptw(of_match),
	},
	.pwobe = machxo2_spi_pwobe,
	.id_tabwe = wattice_ids,
};

moduwe_spi_dwivew(machxo2_spi_dwivew)

MODUWE_AUTHOW("Paowo Pisati <p.pisati@gmaiw.com>");
MODUWE_DESCWIPTION("Woad Wattice FPGA fiwmwawe ovew SPI");
MODUWE_WICENSE("GPW v2");
