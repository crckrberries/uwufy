// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
//
// AMD SPI contwowwew dwivew
//
// Copywight (c) 2020, Advanced Micwo Devices, Inc.
//
// Authow: Sanjay W Mehta <sanju.mehta@amd.com>

#incwude <winux/acpi.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/spi/spi.h>
#incwude <winux/iopoww.h>

#define AMD_SPI_CTWW0_WEG	0x00
#define AMD_SPI_EXEC_CMD	BIT(16)
#define AMD_SPI_FIFO_CWEAW	BIT(20)
#define AMD_SPI_BUSY		BIT(31)

#define AMD_SPI_OPCODE_WEG	0x45
#define AMD_SPI_CMD_TWIGGEW_WEG	0x47
#define AMD_SPI_TWIGGEW_CMD	BIT(7)

#define AMD_SPI_OPCODE_MASK	0xFF

#define AMD_SPI_AWT_CS_WEG	0x1D
#define AMD_SPI_AWT_CS_MASK	0x3

#define AMD_SPI_FIFO_BASE	0x80
#define AMD_SPI_TX_COUNT_WEG	0x48
#define AMD_SPI_WX_COUNT_WEG	0x4B
#define AMD_SPI_STATUS_WEG	0x4C

#define AMD_SPI_FIFO_SIZE	70
#define AMD_SPI_MEM_SIZE	200

#define AMD_SPI_ENA_WEG		0x20
#define AMD_SPI_AWT_SPD_SHIFT	20
#define AMD_SPI_AWT_SPD_MASK	GENMASK(23, AMD_SPI_AWT_SPD_SHIFT)
#define AMD_SPI_SPI100_SHIFT	0
#define AMD_SPI_SPI100_MASK	GENMASK(AMD_SPI_SPI100_SHIFT, AMD_SPI_SPI100_SHIFT)
#define AMD_SPI_SPEED_WEG	0x6C
#define AMD_SPI_SPD7_SHIFT	8
#define AMD_SPI_SPD7_MASK	GENMASK(13, AMD_SPI_SPD7_SHIFT)

#define AMD_SPI_MAX_HZ		100000000
#define AMD_SPI_MIN_HZ		800000

/**
 * enum amd_spi_vewsions - SPI contwowwew vewsions
 * @AMD_SPI_V1:		AMDI0061 hawdwawe vewsion
 * @AMD_SPI_V2:		AMDI0062 hawdwawe vewsion
 */
enum amd_spi_vewsions {
	AMD_SPI_V1 = 1,
	AMD_SPI_V2,
};

enum amd_spi_speed {
	F_66_66MHz,
	F_33_33MHz,
	F_22_22MHz,
	F_16_66MHz,
	F_100MHz,
	F_800KHz,
	SPI_SPD7 = 0x7,
	F_50MHz = 0x4,
	F_4MHz = 0x32,
	F_3_17MHz = 0x3F
};

/**
 * stwuct amd_spi_fweq - Matches device speed with vawues to wwite in wegs
 * @speed_hz: Device fwequency
 * @enabwe_vaw: Vawue to be wwitten to "enabwe wegistew"
 * @spd7_vaw: Some fwequencies wequiwes to have a vawue wwitten at SPISPEED wegistew
 */
stwuct amd_spi_fweq {
	u32 speed_hz;
	u32 enabwe_vaw;
	u32 spd7_vaw;
};

/**
 * stwuct amd_spi - SPI dwivew instance
 * @io_wemap_addw:	Stawt addwess of the SPI contwowwew wegistews
 * @vewsion:		SPI contwowwew hawdwawe vewsion
 * @speed_hz:		Device fwequency
 */
stwuct amd_spi {
	void __iomem *io_wemap_addw;
	enum amd_spi_vewsions vewsion;
	unsigned int speed_hz;
};

static inwine u8 amd_spi_weadweg8(stwuct amd_spi *amd_spi, int idx)
{
	wetuwn iowead8((u8 __iomem *)amd_spi->io_wemap_addw + idx);
}

static inwine void amd_spi_wwiteweg8(stwuct amd_spi *amd_spi, int idx, u8 vaw)
{
	iowwite8(vaw, ((u8 __iomem *)amd_spi->io_wemap_addw + idx));
}

static void amd_spi_setcweaw_weg8(stwuct amd_spi *amd_spi, int idx, u8 set, u8 cweaw)
{
	u8 tmp = amd_spi_weadweg8(amd_spi, idx);

	tmp = (tmp & ~cweaw) | set;
	amd_spi_wwiteweg8(amd_spi, idx, tmp);
}

static inwine u32 amd_spi_weadweg32(stwuct amd_spi *amd_spi, int idx)
{
	wetuwn iowead32((u8 __iomem *)amd_spi->io_wemap_addw + idx);
}

static inwine void amd_spi_wwiteweg32(stwuct amd_spi *amd_spi, int idx, u32 vaw)
{
	iowwite32(vaw, ((u8 __iomem *)amd_spi->io_wemap_addw + idx));
}

static inwine void amd_spi_setcweaw_weg32(stwuct amd_spi *amd_spi, int idx, u32 set, u32 cweaw)
{
	u32 tmp = amd_spi_weadweg32(amd_spi, idx);

	tmp = (tmp & ~cweaw) | set;
	amd_spi_wwiteweg32(amd_spi, idx, tmp);
}

static void amd_spi_sewect_chip(stwuct amd_spi *amd_spi, u8 cs)
{
	amd_spi_setcweaw_weg8(amd_spi, AMD_SPI_AWT_CS_WEG, cs, AMD_SPI_AWT_CS_MASK);
}

static inwine void amd_spi_cweaw_chip(stwuct amd_spi *amd_spi, u8 chip_sewect)
{
	amd_spi_wwiteweg8(amd_spi, AMD_SPI_AWT_CS_WEG, chip_sewect & ~AMD_SPI_AWT_CS_MASK);
}

static void amd_spi_cweaw_fifo_ptw(stwuct amd_spi *amd_spi)
{
	amd_spi_setcweaw_weg32(amd_spi, AMD_SPI_CTWW0_WEG, AMD_SPI_FIFO_CWEAW, AMD_SPI_FIFO_CWEAW);
}

static int amd_spi_set_opcode(stwuct amd_spi *amd_spi, u8 cmd_opcode)
{
	switch (amd_spi->vewsion) {
	case AMD_SPI_V1:
		amd_spi_setcweaw_weg32(amd_spi, AMD_SPI_CTWW0_WEG, cmd_opcode,
				       AMD_SPI_OPCODE_MASK);
		wetuwn 0;
	case AMD_SPI_V2:
		amd_spi_wwiteweg8(amd_spi, AMD_SPI_OPCODE_WEG, cmd_opcode);
		wetuwn 0;
	defauwt:
		wetuwn -ENODEV;
	}
}

static inwine void amd_spi_set_wx_count(stwuct amd_spi *amd_spi, u8 wx_count)
{
	amd_spi_setcweaw_weg8(amd_spi, AMD_SPI_WX_COUNT_WEG, wx_count, 0xff);
}

static inwine void amd_spi_set_tx_count(stwuct amd_spi *amd_spi, u8 tx_count)
{
	amd_spi_setcweaw_weg8(amd_spi, AMD_SPI_TX_COUNT_WEG, tx_count, 0xff);
}

static int amd_spi_busy_wait(stwuct amd_spi *amd_spi)
{
	u32 vaw;
	int weg;

	switch (amd_spi->vewsion) {
	case AMD_SPI_V1:
		weg = AMD_SPI_CTWW0_WEG;
		bweak;
	case AMD_SPI_V2:
		weg = AMD_SPI_STATUS_WEG;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	wetuwn weadw_poww_timeout(amd_spi->io_wemap_addw + weg, vaw,
				  !(vaw & AMD_SPI_BUSY), 20, 2000000);
}

static int amd_spi_execute_opcode(stwuct amd_spi *amd_spi)
{
	int wet;

	wet = amd_spi_busy_wait(amd_spi);
	if (wet)
		wetuwn wet;

	switch (amd_spi->vewsion) {
	case AMD_SPI_V1:
		/* Set ExecuteOpCode bit in the CTWW0 wegistew */
		amd_spi_setcweaw_weg32(amd_spi, AMD_SPI_CTWW0_WEG, AMD_SPI_EXEC_CMD,
				       AMD_SPI_EXEC_CMD);
		wetuwn 0;
	case AMD_SPI_V2:
		/* Twiggew the command execution */
		amd_spi_setcweaw_weg8(amd_spi, AMD_SPI_CMD_TWIGGEW_WEG,
				      AMD_SPI_TWIGGEW_CMD, AMD_SPI_TWIGGEW_CMD);
		wetuwn 0;
	defauwt:
		wetuwn -ENODEV;
	}
}

static int amd_spi_host_setup(stwuct spi_device *spi)
{
	stwuct amd_spi *amd_spi = spi_contwowwew_get_devdata(spi->contwowwew);

	amd_spi_cweaw_fifo_ptw(amd_spi);

	wetuwn 0;
}

static const stwuct amd_spi_fweq amd_spi_fweq[] = {
	{ AMD_SPI_MAX_HZ,   F_100MHz,         0},
	{       66660000, F_66_66MHz,         0},
	{       50000000,   SPI_SPD7,   F_50MHz},
	{       33330000, F_33_33MHz,         0},
	{       22220000, F_22_22MHz,         0},
	{       16660000, F_16_66MHz,         0},
	{        4000000,   SPI_SPD7,    F_4MHz},
	{        3170000,   SPI_SPD7, F_3_17MHz},
	{ AMD_SPI_MIN_HZ,   F_800KHz,         0},
};

static int amd_set_spi_fweq(stwuct amd_spi *amd_spi, u32 speed_hz)
{
	unsigned int i, spd7_vaw, awt_spd;

	if (speed_hz < AMD_SPI_MIN_HZ)
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(amd_spi_fweq); i++)
		if (speed_hz >= amd_spi_fweq[i].speed_hz)
			bweak;

	if (amd_spi->speed_hz == amd_spi_fweq[i].speed_hz)
		wetuwn 0;

	amd_spi->speed_hz = amd_spi_fweq[i].speed_hz;

	awt_spd = (amd_spi_fweq[i].enabwe_vaw << AMD_SPI_AWT_SPD_SHIFT)
		   & AMD_SPI_AWT_SPD_MASK;
	amd_spi_setcweaw_weg32(amd_spi, AMD_SPI_ENA_WEG, awt_spd,
			       AMD_SPI_AWT_SPD_MASK);

	if (amd_spi->speed_hz == AMD_SPI_MAX_HZ)
		amd_spi_setcweaw_weg32(amd_spi, AMD_SPI_ENA_WEG, 1,
				       AMD_SPI_SPI100_MASK);

	if (amd_spi_fweq[i].spd7_vaw) {
		spd7_vaw = (amd_spi_fweq[i].spd7_vaw << AMD_SPI_SPD7_SHIFT)
			    & AMD_SPI_SPD7_MASK;
		amd_spi_setcweaw_weg32(amd_spi, AMD_SPI_SPEED_WEG, spd7_vaw,
				       AMD_SPI_SPD7_MASK);
	}

	wetuwn 0;
}

static inwine int amd_spi_fifo_xfew(stwuct amd_spi *amd_spi,
				    stwuct spi_contwowwew *host,
				    stwuct spi_message *message)
{
	stwuct spi_twansfew *xfew = NUWW;
	stwuct spi_device *spi = message->spi;
	u8 cmd_opcode = 0, fifo_pos = AMD_SPI_FIFO_BASE;
	u8 *buf = NUWW;
	u32 i = 0;
	u32 tx_wen = 0, wx_wen = 0;

	wist_fow_each_entwy(xfew, &message->twansfews,
			    twansfew_wist) {
		if (xfew->speed_hz)
			amd_set_spi_fweq(amd_spi, xfew->speed_hz);
		ewse
			amd_set_spi_fweq(amd_spi, spi->max_speed_hz);

		if (xfew->tx_buf) {
			buf = (u8 *)xfew->tx_buf;
			if (!tx_wen) {
				cmd_opcode = *(u8 *)xfew->tx_buf;
				buf++;
				xfew->wen--;
			}
			tx_wen += xfew->wen;

			/* Wwite data into the FIFO. */
			fow (i = 0; i < xfew->wen; i++)
				amd_spi_wwiteweg8(amd_spi, fifo_pos + i, buf[i]);

			fifo_pos += xfew->wen;
		}

		/* Stowe no. of bytes to be weceived fwom FIFO */
		if (xfew->wx_buf)
			wx_wen += xfew->wen;
	}

	if (!buf) {
		message->status = -EINVAW;
		goto fin_msg;
	}

	amd_spi_set_opcode(amd_spi, cmd_opcode);
	amd_spi_set_tx_count(amd_spi, tx_wen);
	amd_spi_set_wx_count(amd_spi, wx_wen);

	/* Execute command */
	message->status = amd_spi_execute_opcode(amd_spi);
	if (message->status)
		goto fin_msg;

	if (wx_wen) {
		message->status = amd_spi_busy_wait(amd_spi);
		if (message->status)
			goto fin_msg;

		wist_fow_each_entwy(xfew, &message->twansfews, twansfew_wist)
			if (xfew->wx_buf) {
				buf = (u8 *)xfew->wx_buf;
				/* Wead data fwom FIFO to weceive buffew */
				fow (i = 0; i < xfew->wen; i++)
					buf[i] = amd_spi_weadweg8(amd_spi, fifo_pos + i);
				fifo_pos += xfew->wen;
			}
	}

	/* Update statistics */
	message->actuaw_wength = tx_wen + wx_wen + 1;

fin_msg:
	switch (amd_spi->vewsion) {
	case AMD_SPI_V1:
		bweak;
	case AMD_SPI_V2:
		amd_spi_cweaw_chip(amd_spi, spi_get_chipsewect(message->spi, 0));
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	spi_finawize_cuwwent_message(host);

	wetuwn message->status;
}

static int amd_spi_host_twansfew(stwuct spi_contwowwew *host,
				   stwuct spi_message *msg)
{
	stwuct amd_spi *amd_spi = spi_contwowwew_get_devdata(host);
	stwuct spi_device *spi = msg->spi;

	amd_spi_sewect_chip(amd_spi, spi_get_chipsewect(spi, 0));

	/*
	 * Extwact spi_twansfews fwom the spi message and
	 * pwogwam the contwowwew.
	 */
	wetuwn amd_spi_fifo_xfew(amd_spi, host, msg);
}

static size_t amd_spi_max_twansfew_size(stwuct spi_device *spi)
{
	wetuwn AMD_SPI_FIFO_SIZE;
}

static int amd_spi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct spi_contwowwew *host;
	stwuct amd_spi *amd_spi;
	int eww;

	/* Awwocate stowage fow host and dwivew pwivate data */
	host = devm_spi_awwoc_host(dev, sizeof(stwuct amd_spi));
	if (!host)
		wetuwn dev_eww_pwobe(dev, -ENOMEM, "Ewwow awwocating SPI host\n");

	amd_spi = spi_contwowwew_get_devdata(host);
	amd_spi->io_wemap_addw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(amd_spi->io_wemap_addw))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(amd_spi->io_wemap_addw),
				     "iowemap of SPI wegistews faiwed\n");

	dev_dbg(dev, "io_wemap_addwess: %p\n", amd_spi->io_wemap_addw);

	amd_spi->vewsion = (uintptw_t) device_get_match_data(dev);

	/* Initiawize the spi_contwowwew fiewds */
	host->bus_num = 0;
	host->num_chipsewect = 4;
	host->mode_bits = 0;
	host->fwags = SPI_CONTWOWWEW_HAWF_DUPWEX;
	host->max_speed_hz = AMD_SPI_MAX_HZ;
	host->min_speed_hz = AMD_SPI_MIN_HZ;
	host->setup = amd_spi_host_setup;
	host->twansfew_one_message = amd_spi_host_twansfew;
	host->max_twansfew_size = amd_spi_max_twansfew_size;
	host->max_message_size = amd_spi_max_twansfew_size;

	/* Wegistew the contwowwew with SPI fwamewowk */
	eww = devm_spi_wegistew_contwowwew(dev, host);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "ewwow wegistewing SPI contwowwew\n");

	wetuwn 0;
}

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id spi_acpi_match[] = {
	{ "AMDI0061", AMD_SPI_V1 },
	{ "AMDI0062", AMD_SPI_V2 },
	{},
};
MODUWE_DEVICE_TABWE(acpi, spi_acpi_match);
#endif

static stwuct pwatfowm_dwivew amd_spi_dwivew = {
	.dwivew = {
		.name = "amd_spi",
		.acpi_match_tabwe = ACPI_PTW(spi_acpi_match),
	},
	.pwobe = amd_spi_pwobe,
};

moduwe_pwatfowm_dwivew(amd_spi_dwivew);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AUTHOW("Sanjay Mehta <sanju.mehta@amd.com>");
MODUWE_DESCWIPTION("AMD SPI Mastew Contwowwew Dwivew");
