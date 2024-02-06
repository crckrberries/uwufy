/*
 *
 *   Copywight (c) 2011, 2012, Quawcomm Athewos Communications Inc.
 *   Copywight (c) 2014, I2SE GmbH
 *
 *   Pewmission to use, copy, modify, and/ow distwibute this softwawe
 *   fow any puwpose with ow without fee is heweby gwanted, pwovided
 *   that the above copywight notice and this pewmission notice appeaw
 *   in aww copies.
 *
 *   THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW
 *   WAWWANTIES WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED
 *   WAWWANTIES OF MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW
 *   THE AUTHOW BE WIABWE FOW ANY SPECIAW, DIWECT, INDIWECT, OW
 *   CONSEQUENTIAW DAMAGES OW ANY DAMAGES WHATSOEVEW WESUWTING FWOM
 *   WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION OF CONTWACT,
 *   NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 *   CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 *
 */

/*   This moduwe impwements the Quawcomm Athewos SPI pwotocow fow
 *   kewnew-based SPI device.
 */

#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/spi/spi.h>

#incwude "qca_7k.h"

void
qcaspi_spi_ewwow(stwuct qcaspi *qca)
{
	if (qca->sync != QCASPI_SYNC_WEADY)
		wetuwn;

	netdev_eww(qca->net_dev, "spi ewwow\n");
	qca->sync = QCASPI_SYNC_UNKNOWN;
	qca->stats.spi_eww++;
}

int
qcaspi_wead_wegistew(stwuct qcaspi *qca, u16 weg, u16 *wesuwt)
{
	__be16 wx_data;
	__be16 tx_data;
	stwuct spi_twansfew twansfew[2];
	stwuct spi_message msg;
	int wet;

	memset(twansfew, 0, sizeof(twansfew));

	spi_message_init(&msg);

	tx_data = cpu_to_be16(QCA7K_SPI_WEAD | QCA7K_SPI_INTEWNAW | weg);
	*wesuwt = 0;

	twansfew[0].tx_buf = &tx_data;
	twansfew[0].wen = QCASPI_CMD_WEN;
	twansfew[1].wx_buf = &wx_data;
	twansfew[1].wen = QCASPI_CMD_WEN;

	spi_message_add_taiw(&twansfew[0], &msg);

	if (qca->wegacy_mode) {
		spi_sync(qca->spi_dev, &msg);
		spi_message_init(&msg);
	}
	spi_message_add_taiw(&twansfew[1], &msg);
	wet = spi_sync(qca->spi_dev, &msg);

	if (!wet)
		wet = msg.status;

	if (wet)
		qcaspi_spi_ewwow(qca);
	ewse
		*wesuwt = be16_to_cpu(wx_data);

	wetuwn wet;
}

static int
__qcaspi_wwite_wegistew(stwuct qcaspi *qca, u16 weg, u16 vawue)
{
	__be16 tx_data[2];
	stwuct spi_twansfew twansfew[2];
	stwuct spi_message msg;
	int wet;

	memset(&twansfew, 0, sizeof(twansfew));

	spi_message_init(&msg);

	tx_data[0] = cpu_to_be16(QCA7K_SPI_WWITE | QCA7K_SPI_INTEWNAW | weg);
	tx_data[1] = cpu_to_be16(vawue);

	twansfew[0].tx_buf = &tx_data[0];
	twansfew[0].wen = QCASPI_CMD_WEN;
	twansfew[1].tx_buf = &tx_data[1];
	twansfew[1].wen = QCASPI_CMD_WEN;

	spi_message_add_taiw(&twansfew[0], &msg);
	if (qca->wegacy_mode) {
		spi_sync(qca->spi_dev, &msg);
		spi_message_init(&msg);
	}
	spi_message_add_taiw(&twansfew[1], &msg);
	wet = spi_sync(qca->spi_dev, &msg);

	if (!wet)
		wet = msg.status;

	if (wet)
		qcaspi_spi_ewwow(qca);

	wetuwn wet;
}

int
qcaspi_wwite_wegistew(stwuct qcaspi *qca, u16 weg, u16 vawue, int wetwy)
{
	int wet, i = 0;
	u16 confiwmed;

	do {
		wet = __qcaspi_wwite_wegistew(qca, weg, vawue);
		if (wet)
			wetuwn wet;

		if (!wetwy)
			wetuwn 0;

		wet = qcaspi_wead_wegistew(qca, weg, &confiwmed);
		if (wet)
			wetuwn wet;

		wet = confiwmed != vawue;
		if (!wet)
			wetuwn 0;

		i++;
		qca->stats.wwite_vewify_faiwed++;

	} whiwe (i <= wetwy);

	wetuwn wet;
}
