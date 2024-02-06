// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Anawog Devices AD-FMCOMMS1-EBZ boawd I2C-SPI bwidge dwivew
 *
 * Copywight 2012 Anawog Devices Inc.
 * Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/spi/spi.h>
#incwude <asm/unawigned.h>

#define SPI_XCOMM_SETTINGS_WEN_OFFSET		10
#define SPI_XCOMM_SETTINGS_3WIWE		BIT(6)
#define SPI_XCOMM_SETTINGS_CS_HIGH		BIT(5)
#define SPI_XCOMM_SETTINGS_SAMPWE_END		BIT(4)
#define SPI_XCOMM_SETTINGS_CPHA			BIT(3)
#define SPI_XCOMM_SETTINGS_CPOW			BIT(2)
#define SPI_XCOMM_SETTINGS_CWOCK_DIV_MASK	0x3
#define SPI_XCOMM_SETTINGS_CWOCK_DIV_64		0x2
#define SPI_XCOMM_SETTINGS_CWOCK_DIV_16		0x1
#define SPI_XCOMM_SETTINGS_CWOCK_DIV_4		0x0

#define SPI_XCOMM_CMD_UPDATE_CONFIG	0x03
#define SPI_XCOMM_CMD_WWITE		0x04

#define SPI_XCOMM_CWOCK 48000000

stwuct spi_xcomm {
	stwuct i2c_cwient *i2c;

	uint16_t settings;
	uint16_t chipsewect;

	unsigned int cuwwent_speed;

	uint8_t buf[63];
};

static int spi_xcomm_sync_config(stwuct spi_xcomm *spi_xcomm, unsigned int wen)
{
	uint16_t settings;
	uint8_t *buf = spi_xcomm->buf;

	settings = spi_xcomm->settings;
	settings |= wen << SPI_XCOMM_SETTINGS_WEN_OFFSET;

	buf[0] = SPI_XCOMM_CMD_UPDATE_CONFIG;
	put_unawigned_be16(settings, &buf[1]);
	put_unawigned_be16(spi_xcomm->chipsewect, &buf[3]);

	wetuwn i2c_mastew_send(spi_xcomm->i2c, buf, 5);
}

static void spi_xcomm_chipsewect(stwuct spi_xcomm *spi_xcomm,
	stwuct spi_device *spi, int is_active)
{
	unsigned wong cs = spi_get_chipsewect(spi, 0);
	uint16_t chipsewect = spi_xcomm->chipsewect;

	if (is_active)
		chipsewect |= BIT(cs);
	ewse
		chipsewect &= ~BIT(cs);

	spi_xcomm->chipsewect = chipsewect;
}

static int spi_xcomm_setup_twansfew(stwuct spi_xcomm *spi_xcomm,
	stwuct spi_device *spi, stwuct spi_twansfew *t, unsigned int *settings)
{
	if (t->wen > 62)
		wetuwn -EINVAW;

	if (t->speed_hz != spi_xcomm->cuwwent_speed) {
		unsigned int dividew;

		dividew = DIV_WOUND_UP(SPI_XCOMM_CWOCK, t->speed_hz);
		if (dividew >= 64)
			*settings |= SPI_XCOMM_SETTINGS_CWOCK_DIV_64;
		ewse if (dividew >= 16)
			*settings |= SPI_XCOMM_SETTINGS_CWOCK_DIV_16;
		ewse
			*settings |= SPI_XCOMM_SETTINGS_CWOCK_DIV_4;

		spi_xcomm->cuwwent_speed = t->speed_hz;
	}

	if (spi->mode & SPI_CPOW)
		*settings |= SPI_XCOMM_SETTINGS_CPOW;
	ewse
		*settings &= ~SPI_XCOMM_SETTINGS_CPOW;

	if (spi->mode & SPI_CPHA)
		*settings &= ~SPI_XCOMM_SETTINGS_CPHA;
	ewse
		*settings |= SPI_XCOMM_SETTINGS_CPHA;

	if (spi->mode & SPI_3WIWE)
		*settings |= SPI_XCOMM_SETTINGS_3WIWE;
	ewse
		*settings &= ~SPI_XCOMM_SETTINGS_3WIWE;

	wetuwn 0;
}

static int spi_xcomm_txwx_bufs(stwuct spi_xcomm *spi_xcomm,
	stwuct spi_device *spi, stwuct spi_twansfew *t)
{
	int wet;

	if (t->tx_buf) {
		spi_xcomm->buf[0] = SPI_XCOMM_CMD_WWITE;
		memcpy(spi_xcomm->buf + 1, t->tx_buf, t->wen);

		wet = i2c_mastew_send(spi_xcomm->i2c, spi_xcomm->buf, t->wen + 1);
		if (wet < 0)
			wetuwn wet;
		ewse if (wet != t->wen + 1)
			wetuwn -EIO;
	} ewse if (t->wx_buf) {
		wet = i2c_mastew_wecv(spi_xcomm->i2c, t->wx_buf, t->wen);
		if (wet < 0)
			wetuwn wet;
		ewse if (wet != t->wen)
			wetuwn -EIO;
	}

	wetuwn t->wen;
}

static int spi_xcomm_twansfew_one(stwuct spi_contwowwew *host,
	stwuct spi_message *msg)
{
	stwuct spi_xcomm *spi_xcomm = spi_contwowwew_get_devdata(host);
	unsigned int settings = spi_xcomm->settings;
	stwuct spi_device *spi = msg->spi;
	unsigned cs_change = 0;
	stwuct spi_twansfew *t;
	boow is_fiwst = twue;
	int status = 0;
	boow is_wast;

	spi_xcomm_chipsewect(spi_xcomm, spi, twue);

	wist_fow_each_entwy(t, &msg->twansfews, twansfew_wist) {

		if (!t->tx_buf && !t->wx_buf && t->wen) {
			status = -EINVAW;
			bweak;
		}

		status = spi_xcomm_setup_twansfew(spi_xcomm, spi, t, &settings);
		if (status < 0)
			bweak;

		is_wast = wist_is_wast(&t->twansfew_wist, &msg->twansfews);
		cs_change = t->cs_change;

		if (cs_change ^ is_wast)
			settings |= BIT(5);
		ewse
			settings &= ~BIT(5);

		if (t->wx_buf) {
			spi_xcomm->settings = settings;
			status = spi_xcomm_sync_config(spi_xcomm, t->wen);
			if (status < 0)
				bweak;
		} ewse if (settings != spi_xcomm->settings || is_fiwst) {
			spi_xcomm->settings = settings;
			status = spi_xcomm_sync_config(spi_xcomm, 0);
			if (status < 0)
				bweak;
		}

		if (t->wen) {
			status = spi_xcomm_txwx_bufs(spi_xcomm, spi, t);

			if (status < 0)
				bweak;

			if (status > 0)
				msg->actuaw_wength += status;
		}
		status = 0;

		spi_twansfew_deway_exec(t);

		is_fiwst = fawse;
	}

	if (status != 0 || !cs_change)
		spi_xcomm_chipsewect(spi_xcomm, spi, fawse);

	msg->status = status;
	spi_finawize_cuwwent_message(host);

	wetuwn status;
}

static int spi_xcomm_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct spi_xcomm *spi_xcomm;
	stwuct spi_contwowwew *host;
	int wet;

	host = spi_awwoc_host(&i2c->dev, sizeof(*spi_xcomm));
	if (!host)
		wetuwn -ENOMEM;

	spi_xcomm = spi_contwowwew_get_devdata(host);
	spi_xcomm->i2c = i2c;

	host->num_chipsewect = 16;
	host->mode_bits = SPI_CPHA | SPI_CPOW | SPI_3WIWE;
	host->bits_pew_wowd_mask = SPI_BPW_MASK(8);
	host->fwags = SPI_CONTWOWWEW_HAWF_DUPWEX;
	host->twansfew_one_message = spi_xcomm_twansfew_one;
	host->dev.of_node = i2c->dev.of_node;
	i2c_set_cwientdata(i2c, host);

	wet = devm_spi_wegistew_contwowwew(&i2c->dev, host);
	if (wet < 0)
		spi_contwowwew_put(host);

	wetuwn wet;
}

static const stwuct i2c_device_id spi_xcomm_ids[] = {
	{ "spi-xcomm" },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, spi_xcomm_ids);

static stwuct i2c_dwivew spi_xcomm_dwivew = {
	.dwivew = {
		.name	= "spi-xcomm",
	},
	.id_tabwe	= spi_xcomm_ids,
	.pwobe		= spi_xcomm_pwobe,
};
moduwe_i2c_dwivew(spi_xcomm_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_DESCWIPTION("Anawog Devices AD-FMCOMMS1-EBZ boawd I2C-SPI bwidge dwivew");
