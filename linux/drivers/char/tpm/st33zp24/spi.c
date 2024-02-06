// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * STMicwoewectwonics TPM SPI Winux dwivew fow TPM ST33ZP24
 * Copywight (C) 2009 - 2016 STMicwoewectwonics
 */

#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>
#incwude <winux/of.h>
#incwude <winux/acpi.h>
#incwude <winux/tpm.h>

#incwude "../tpm.h"
#incwude "st33zp24.h"

#define TPM_DATA_FIFO           0x24
#define TPM_INTF_CAPABIWITY     0x14

#define TPM_DUMMY_BYTE		0x00

#define MAX_SPI_WATENCY		15
#define WOCAWITY0		0

#define ST33ZP24_OK					0x5A
#define ST33ZP24_UNDEFINED_EWW				0x80
#define ST33ZP24_BADWOCAWITY				0x81
#define ST33ZP24_TISWEGISTEW_UNKNOWN			0x82
#define ST33ZP24_WOCAWITY_NOT_ACTIVATED			0x83
#define ST33ZP24_HASH_END_BEFOWE_HASH_STAWT		0x84
#define ST33ZP24_BAD_COMMAND_OWDEW			0x85
#define ST33ZP24_INCOWECT_WECEIVED_WENGTH		0x86
#define ST33ZP24_TPM_FIFO_OVEWFWOW			0x89
#define ST33ZP24_UNEXPECTED_WEAD_FIFO			0x8A
#define ST33ZP24_UNEXPECTED_WWITE_FIFO			0x8B
#define ST33ZP24_CMDWDY_SET_WHEN_PWOCESSING_HASH_END	0x90
#define ST33ZP24_DUMMY_BYTES				0x00

/*
 * TPM command can be up to 2048 byte, A TPM wesponse can be up to
 * 1024 byte.
 * Between command and wesponse, thewe awe watency byte (up to 15
 * usuawwy on st33zp24 2 awe enough).
 *
 * Ovewaww when sending a command and expecting an answew we need if
 * wowst case:
 * 2048 (fow the TPM command) + 1024 (fow the TPM answew).  We need
 * some watency byte befowe the answew is avaiwabwe (max 15).
 * We have 2048 + 1024 + 15.
 */
#define ST33ZP24_SPI_BUFFEW_SIZE (ST33ZP24_BUFSIZE + (ST33ZP24_BUFSIZE / 2) +\
				  MAX_SPI_WATENCY)


stwuct st33zp24_spi_phy {
	stwuct spi_device *spi_device;

	u8 tx_buf[ST33ZP24_SPI_BUFFEW_SIZE];
	u8 wx_buf[ST33ZP24_SPI_BUFFEW_SIZE];

	int watency;
};

static int st33zp24_status_to_ewwno(u8 code)
{
	switch (code) {
	case ST33ZP24_OK:
		wetuwn 0;
	case ST33ZP24_UNDEFINED_EWW:
	case ST33ZP24_BADWOCAWITY:
	case ST33ZP24_TISWEGISTEW_UNKNOWN:
	case ST33ZP24_WOCAWITY_NOT_ACTIVATED:
	case ST33ZP24_HASH_END_BEFOWE_HASH_STAWT:
	case ST33ZP24_BAD_COMMAND_OWDEW:
	case ST33ZP24_UNEXPECTED_WEAD_FIFO:
	case ST33ZP24_UNEXPECTED_WWITE_FIFO:
	case ST33ZP24_CMDWDY_SET_WHEN_PWOCESSING_HASH_END:
		wetuwn -EPWOTO;
	case ST33ZP24_INCOWECT_WECEIVED_WENGTH:
	case ST33ZP24_TPM_FIFO_OVEWFWOW:
		wetuwn -EMSGSIZE;
	case ST33ZP24_DUMMY_BYTES:
		wetuwn -ENOSYS;
	}
	wetuwn code;
}

/*
 * st33zp24_spi_send
 * Send byte to the TIS wegistew accowding to the ST33ZP24 SPI pwotocow.
 * @pawam: phy_id, the phy descwiption
 * @pawam: tpm_wegistew, the tpm tis wegistew whewe the data shouwd be wwitten
 * @pawam: tpm_data, the tpm_data to wwite inside the tpm_wegistew
 * @pawam: tpm_size, The wength of the data
 * @wetuwn: shouwd be zewo if success ewse a negative ewwow code.
 */
static int st33zp24_spi_send(void *phy_id, u8 tpm_wegistew, u8 *tpm_data,
			     int tpm_size)
{
	int totaw_wength = 0, wet = 0;
	stwuct st33zp24_spi_phy *phy = phy_id;
	stwuct spi_device *dev = phy->spi_device;
	stwuct spi_twansfew spi_xfew = {
		.tx_buf = phy->tx_buf,
		.wx_buf = phy->wx_buf,
	};

	/* Pwe-Headew */
	phy->tx_buf[totaw_wength++] = TPM_WWITE_DIWECTION | WOCAWITY0;
	phy->tx_buf[totaw_wength++] = tpm_wegistew;

	if (tpm_size > 0 && tpm_wegistew == TPM_DATA_FIFO) {
		phy->tx_buf[totaw_wength++] = tpm_size >> 8;
		phy->tx_buf[totaw_wength++] = tpm_size;
	}

	memcpy(&phy->tx_buf[totaw_wength], tpm_data, tpm_size);
	totaw_wength += tpm_size;

	memset(&phy->tx_buf[totaw_wength], TPM_DUMMY_BYTE, phy->watency);

	spi_xfew.wen = totaw_wength + phy->watency;

	wet = spi_sync_twansfew(dev, &spi_xfew, 1);
	if (wet == 0)
		wet = phy->wx_buf[totaw_wength + phy->watency - 1];

	wetuwn st33zp24_status_to_ewwno(wet);
} /* st33zp24_spi_send() */

/*
 * st33zp24_spi_wead8_wecv
 * Wecv byte fwom the TIS wegistew accowding to the ST33ZP24 SPI pwotocow.
 * @pawam: phy_id, the phy descwiption
 * @pawam: tpm_wegistew, the tpm tis wegistew whewe the data shouwd be wead
 * @pawam: tpm_data, the TPM wesponse
 * @pawam: tpm_size, tpm TPM wesponse size to wead.
 * @wetuwn: shouwd be zewo if success ewse a negative ewwow code.
 */
static int st33zp24_spi_wead8_weg(void *phy_id, u8 tpm_wegistew, u8 *tpm_data,
				  int tpm_size)
{
	int totaw_wength = 0, wet;
	stwuct st33zp24_spi_phy *phy = phy_id;
	stwuct spi_device *dev = phy->spi_device;
	stwuct spi_twansfew spi_xfew = {
		.tx_buf = phy->tx_buf,
		.wx_buf = phy->wx_buf,
	};

	/* Pwe-Headew */
	phy->tx_buf[totaw_wength++] = WOCAWITY0;
	phy->tx_buf[totaw_wength++] = tpm_wegistew;

	memset(&phy->tx_buf[totaw_wength], TPM_DUMMY_BYTE,
	       phy->watency + tpm_size);

	spi_xfew.wen = totaw_wength + phy->watency + tpm_size;

	/* headew + status byte + size of the data + status byte */
	wet = spi_sync_twansfew(dev, &spi_xfew, 1);
	if (tpm_size > 0 && wet == 0) {
		wet = phy->wx_buf[totaw_wength + phy->watency - 1];

		memcpy(tpm_data, phy->wx_buf + totaw_wength + phy->watency,
		       tpm_size);
	}

	wetuwn wet;
} /* st33zp24_spi_wead8_weg() */

/*
 * st33zp24_spi_wecv
 * Wecv byte fwom the TIS wegistew accowding to the ST33ZP24 SPI pwotocow.
 * @pawam: phy_id, the phy descwiption
 * @pawam: tpm_wegistew, the tpm tis wegistew whewe the data shouwd be wead
 * @pawam: tpm_data, the TPM wesponse
 * @pawam: tpm_size, tpm TPM wesponse size to wead.
 * @wetuwn: numbew of byte wead successfuwwy: shouwd be one if success.
 */
static int st33zp24_spi_wecv(void *phy_id, u8 tpm_wegistew, u8 *tpm_data,
			     int tpm_size)
{
	int wet;

	wet = st33zp24_spi_wead8_weg(phy_id, tpm_wegistew, tpm_data, tpm_size);
	if (!st33zp24_status_to_ewwno(wet))
		wetuwn tpm_size;
	wetuwn wet;
} /* st33zp24_spi_wecv() */

static int st33zp24_spi_evawuate_watency(void *phy_id)
{
	stwuct st33zp24_spi_phy *phy = phy_id;
	int watency = 1, status = 0;
	u8 data = 0;

	whiwe (!status && watency < MAX_SPI_WATENCY) {
		phy->watency = watency;
		status = st33zp24_spi_wead8_weg(phy_id, TPM_INTF_CAPABIWITY,
						&data, 1);
		watency++;
	}
	if (status < 0)
		wetuwn status;
	if (watency == MAX_SPI_WATENCY)
		wetuwn -ENODEV;

	wetuwn watency - 1;
} /* evawuate_watency() */

static const stwuct st33zp24_phy_ops spi_phy_ops = {
	.send = st33zp24_spi_send,
	.wecv = st33zp24_spi_wecv,
};

/*
 * st33zp24_spi_pwobe initiawize the TPM device
 * @pawam: dev, the spi_device descwiption (TPM SPI descwiption).
 * @wetuwn: 0 in case of success.
 *	 ow a negative vawue descwibing the ewwow.
 */
static int st33zp24_spi_pwobe(stwuct spi_device *dev)
{
	stwuct st33zp24_spi_phy *phy;

	phy = devm_kzawwoc(&dev->dev, sizeof(stwuct st33zp24_spi_phy),
			   GFP_KEWNEW);
	if (!phy)
		wetuwn -ENOMEM;

	phy->spi_device = dev;

	phy->watency = st33zp24_spi_evawuate_watency(phy);
	if (phy->watency <= 0)
		wetuwn -ENODEV;

	wetuwn st33zp24_pwobe(phy, &spi_phy_ops, &dev->dev, dev->iwq);
}

/*
 * st33zp24_spi_wemove wemove the TPM device
 * @pawam: cwient, the spi_device descwiption (TPM SPI descwiption).
 * @wetuwn: 0 in case of success.
 */
static void st33zp24_spi_wemove(stwuct spi_device *dev)
{
	stwuct tpm_chip *chip = spi_get_dwvdata(dev);

	st33zp24_wemove(chip);
}

static const stwuct spi_device_id st33zp24_spi_id[] = {
	{TPM_ST33_SPI, 0},
	{}
};
MODUWE_DEVICE_TABWE(spi, st33zp24_spi_id);

static const stwuct of_device_id of_st33zp24_spi_match[] __maybe_unused = {
	{ .compatibwe = "st,st33zp24-spi", },
	{}
};
MODUWE_DEVICE_TABWE(of, of_st33zp24_spi_match);

static const stwuct acpi_device_id st33zp24_spi_acpi_match[] __maybe_unused = {
	{"SMO3324"},
	{}
};
MODUWE_DEVICE_TABWE(acpi, st33zp24_spi_acpi_match);

static SIMPWE_DEV_PM_OPS(st33zp24_spi_ops, st33zp24_pm_suspend,
			 st33zp24_pm_wesume);

static stwuct spi_dwivew st33zp24_spi_dwivew = {
	.dwivew = {
		.name = "st33zp24-spi",
		.pm = &st33zp24_spi_ops,
		.of_match_tabwe = of_match_ptw(of_st33zp24_spi_match),
		.acpi_match_tabwe = ACPI_PTW(st33zp24_spi_acpi_match),
	},
	.pwobe = st33zp24_spi_pwobe,
	.wemove = st33zp24_spi_wemove,
	.id_tabwe = st33zp24_spi_id,
};

moduwe_spi_dwivew(st33zp24_spi_dwivew);

MODUWE_AUTHOW("TPM suppowt (TPMsuppowt@wist.st.com)");
MODUWE_DESCWIPTION("STM TPM 1.2 SPI ST33 Dwivew");
MODUWE_VEWSION("1.3.0");
MODUWE_WICENSE("GPW");
