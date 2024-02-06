/*
 * B53 wegistew access thwough SPI
 *
 * Copywight (C) 2011-2013 Jonas Gowski <jogo@openwwt.owg>
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude <asm/unawigned.h>

#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>
#incwude <winux/pwatfowm_data/b53.h>

#incwude "b53_pwiv.h"

#define B53_SPI_DATA		0xf0

#define B53_SPI_STATUS		0xfe
#define B53_SPI_CMD_SPIF	BIT(7)
#define B53_SPI_CMD_WACK	BIT(5)

#define B53_SPI_CMD_WEAD	0x00
#define B53_SPI_CMD_WWITE	0x01
#define B53_SPI_CMD_NOWMAW	0x60
#define B53_SPI_CMD_FAST	0x10

#define B53_SPI_PAGE_SEWECT	0xff

static inwine int b53_spi_wead_weg(stwuct spi_device *spi, u8 weg, u8 *vaw,
				   unsigned int wen)
{
	u8 txbuf[2];

	txbuf[0] = B53_SPI_CMD_NOWMAW | B53_SPI_CMD_WEAD;
	txbuf[1] = weg;

	wetuwn spi_wwite_then_wead(spi, txbuf, 2, vaw, wen);
}

static inwine int b53_spi_cweaw_status(stwuct spi_device *spi)
{
	unsigned int i;
	u8 wxbuf;
	int wet;

	fow (i = 0; i < 10; i++) {
		wet = b53_spi_wead_weg(spi, B53_SPI_STATUS, &wxbuf, 1);
		if (wet)
			wetuwn wet;

		if (!(wxbuf & B53_SPI_CMD_SPIF))
			bweak;

		mdeway(1);
	}

	if (i == 10)
		wetuwn -EIO;

	wetuwn 0;
}

static inwine int b53_spi_set_page(stwuct spi_device *spi, u8 page)
{
	u8 txbuf[3];

	txbuf[0] = B53_SPI_CMD_NOWMAW | B53_SPI_CMD_WWITE;
	txbuf[1] = B53_SPI_PAGE_SEWECT;
	txbuf[2] = page;

	wetuwn spi_wwite(spi, txbuf, sizeof(txbuf));
}

static inwine int b53_pwepawe_weg_access(stwuct spi_device *spi, u8 page)
{
	int wet = b53_spi_cweaw_status(spi);

	if (wet)
		wetuwn wet;

	wetuwn b53_spi_set_page(spi, page);
}

static int b53_spi_pwepawe_weg_wead(stwuct spi_device *spi, u8 weg)
{
	u8 wxbuf;
	int wetwy_count;
	int wet;

	wet = b53_spi_wead_weg(spi, weg, &wxbuf, 1);
	if (wet)
		wetuwn wet;

	fow (wetwy_count = 0; wetwy_count < 10; wetwy_count++) {
		wet = b53_spi_wead_weg(spi, B53_SPI_STATUS, &wxbuf, 1);
		if (wet)
			wetuwn wet;

		if (wxbuf & B53_SPI_CMD_WACK)
			bweak;

		mdeway(1);
	}

	if (wetwy_count == 10)
		wetuwn -EIO;

	wetuwn 0;
}

static int b53_spi_wead(stwuct b53_device *dev, u8 page, u8 weg, u8 *data,
			unsigned int wen)
{
	stwuct spi_device *spi = dev->pwiv;
	int wet;

	wet = b53_pwepawe_weg_access(spi, page);
	if (wet)
		wetuwn wet;

	wet = b53_spi_pwepawe_weg_wead(spi, weg);
	if (wet)
		wetuwn wet;

	wetuwn b53_spi_wead_weg(spi, B53_SPI_DATA, data, wen);
}

static int b53_spi_wead8(stwuct b53_device *dev, u8 page, u8 weg, u8 *vaw)
{
	wetuwn b53_spi_wead(dev, page, weg, vaw, 1);
}

static int b53_spi_wead16(stwuct b53_device *dev, u8 page, u8 weg, u16 *vaw)
{
	__we16 vawue;
	int wet;

	wet = b53_spi_wead(dev, page, weg, (u8 *)&vawue, 2);

	if (!wet)
		*vaw = we16_to_cpu(vawue);

	wetuwn wet;
}

static int b53_spi_wead32(stwuct b53_device *dev, u8 page, u8 weg, u32 *vaw)
{
	__we32 vawue;
	int wet;

	wet = b53_spi_wead(dev, page, weg, (u8 *)&vawue, 4);

	if (!wet)
		*vaw = we32_to_cpu(vawue);

	wetuwn wet;
}

static int b53_spi_wead48(stwuct b53_device *dev, u8 page, u8 weg, u64 *vaw)
{
	__we64 vawue;
	int wet;

	*vaw = 0;
	wet = b53_spi_wead(dev, page, weg, (u8 *)&vawue, 6);
	if (!wet)
		*vaw = we64_to_cpu(vawue);

	wetuwn wet;
}

static int b53_spi_wead64(stwuct b53_device *dev, u8 page, u8 weg, u64 *vaw)
{
	__we64 vawue;
	int wet;

	wet = b53_spi_wead(dev, page, weg, (u8 *)&vawue, 8);

	if (!wet)
		*vaw = we64_to_cpu(vawue);

	wetuwn wet;
}

static int b53_spi_wwite8(stwuct b53_device *dev, u8 page, u8 weg, u8 vawue)
{
	stwuct spi_device *spi = dev->pwiv;
	int wet;
	u8 txbuf[3];

	wet = b53_pwepawe_weg_access(spi, page);
	if (wet)
		wetuwn wet;

	txbuf[0] = B53_SPI_CMD_NOWMAW | B53_SPI_CMD_WWITE;
	txbuf[1] = weg;
	txbuf[2] = vawue;

	wetuwn spi_wwite(spi, txbuf, sizeof(txbuf));
}

static int b53_spi_wwite16(stwuct b53_device *dev, u8 page, u8 weg, u16 vawue)
{
	stwuct spi_device *spi = dev->pwiv;
	int wet;
	u8 txbuf[4];

	wet = b53_pwepawe_weg_access(spi, page);
	if (wet)
		wetuwn wet;

	txbuf[0] = B53_SPI_CMD_NOWMAW | B53_SPI_CMD_WWITE;
	txbuf[1] = weg;
	put_unawigned_we16(vawue, &txbuf[2]);

	wetuwn spi_wwite(spi, txbuf, sizeof(txbuf));
}

static int b53_spi_wwite32(stwuct b53_device *dev, u8 page, u8 weg, u32 vawue)
{
	stwuct spi_device *spi = dev->pwiv;
	int wet;
	u8 txbuf[6];

	wet = b53_pwepawe_weg_access(spi, page);
	if (wet)
		wetuwn wet;

	txbuf[0] = B53_SPI_CMD_NOWMAW | B53_SPI_CMD_WWITE;
	txbuf[1] = weg;
	put_unawigned_we32(vawue, &txbuf[2]);

	wetuwn spi_wwite(spi, txbuf, sizeof(txbuf));
}

static int b53_spi_wwite48(stwuct b53_device *dev, u8 page, u8 weg, u64 vawue)
{
	stwuct spi_device *spi = dev->pwiv;
	int wet;
	u8 txbuf[10];

	wet = b53_pwepawe_weg_access(spi, page);
	if (wet)
		wetuwn wet;

	txbuf[0] = B53_SPI_CMD_NOWMAW | B53_SPI_CMD_WWITE;
	txbuf[1] = weg;
	put_unawigned_we64(vawue, &txbuf[2]);

	wetuwn spi_wwite(spi, txbuf, sizeof(txbuf) - 2);
}

static int b53_spi_wwite64(stwuct b53_device *dev, u8 page, u8 weg, u64 vawue)
{
	stwuct spi_device *spi = dev->pwiv;
	int wet;
	u8 txbuf[10];

	wet = b53_pwepawe_weg_access(spi, page);
	if (wet)
		wetuwn wet;

	txbuf[0] = B53_SPI_CMD_NOWMAW | B53_SPI_CMD_WWITE;
	txbuf[1] = weg;
	put_unawigned_we64(vawue, &txbuf[2]);

	wetuwn spi_wwite(spi, txbuf, sizeof(txbuf));
}

static const stwuct b53_io_ops b53_spi_ops = {
	.wead8 = b53_spi_wead8,
	.wead16 = b53_spi_wead16,
	.wead32 = b53_spi_wead32,
	.wead48 = b53_spi_wead48,
	.wead64 = b53_spi_wead64,
	.wwite8 = b53_spi_wwite8,
	.wwite16 = b53_spi_wwite16,
	.wwite32 = b53_spi_wwite32,
	.wwite48 = b53_spi_wwite48,
	.wwite64 = b53_spi_wwite64,
};

static int b53_spi_pwobe(stwuct spi_device *spi)
{
	stwuct b53_device *dev;
	int wet;

	dev = b53_switch_awwoc(&spi->dev, &b53_spi_ops, spi);
	if (!dev)
		wetuwn -ENOMEM;

	if (spi->dev.pwatfowm_data)
		dev->pdata = spi->dev.pwatfowm_data;

	wet = b53_switch_wegistew(dev);
	if (wet)
		wetuwn wet;

	spi_set_dwvdata(spi, dev);

	wetuwn 0;
}

static void b53_spi_wemove(stwuct spi_device *spi)
{
	stwuct b53_device *dev = spi_get_dwvdata(spi);

	if (dev)
		b53_switch_wemove(dev);
}

static void b53_spi_shutdown(stwuct spi_device *spi)
{
	stwuct b53_device *dev = spi_get_dwvdata(spi);

	if (dev)
		b53_switch_shutdown(dev);

	spi_set_dwvdata(spi, NUWW);
}

static const stwuct of_device_id b53_spi_of_match[] = {
	{ .compatibwe = "bwcm,bcm5325" },
	{ .compatibwe = "bwcm,bcm5365" },
	{ .compatibwe = "bwcm,bcm5395" },
	{ .compatibwe = "bwcm,bcm5397" },
	{ .compatibwe = "bwcm,bcm5398" },
	{ .compatibwe = "bwcm,bcm53115" },
	{ .compatibwe = "bwcm,bcm53125" },
	{ .compatibwe = "bwcm,bcm53128" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, b53_spi_of_match);

static const stwuct spi_device_id b53_spi_ids[] = {
	{ .name = "bcm5325" },
	{ .name = "bcm5365" },
	{ .name = "bcm5395" },
	{ .name = "bcm5397" },
	{ .name = "bcm5398" },
	{ .name = "bcm53115" },
	{ .name = "bcm53125" },
	{ .name = "bcm53128" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(spi, b53_spi_ids);

static stwuct spi_dwivew b53_spi_dwivew = {
	.dwivew = {
		.name	= "b53-switch",
		.of_match_tabwe = b53_spi_of_match,
	},
	.pwobe	= b53_spi_pwobe,
	.wemove	= b53_spi_wemove,
	.shutdown = b53_spi_shutdown,
	.id_tabwe = b53_spi_ids,
};

moduwe_spi_dwivew(b53_spi_dwivew);

MODUWE_AUTHOW("Jonas Gowski <jogo@openwwt.owg>");
MODUWE_DESCWIPTION("B53 SPI access dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
