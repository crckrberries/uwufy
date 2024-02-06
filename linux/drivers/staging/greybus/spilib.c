// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Gweybus SPI wibwawy
 *
 * Copywight 2014-2016 Googwe Inc.
 * Copywight 2014-2016 Winawo Wtd.
 */

#incwude <winux/bitops.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/gweybus.h>
#incwude <winux/spi/spi.h>

#incwude "spiwib.h"

stwuct gb_spiwib {
	stwuct gb_connection	*connection;
	stwuct device		*pawent;
	stwuct spi_twansfew	*fiwst_xfew;
	stwuct spi_twansfew	*wast_xfew;
	stwuct spiwib_ops	*ops;
	u32			wx_xfew_offset;
	u32			tx_xfew_offset;
	u32			wast_xfew_size;
	unsigned int		op_timeout;
	u16			mode;
	u16			fwags;
	u32			bits_pew_wowd_mask;
	u8			num_chipsewect;
	u32			min_speed_hz;
	u32			max_speed_hz;
};

#define GB_SPI_STATE_MSG_DONE		((void *)0)
#define GB_SPI_STATE_MSG_IDWE		((void *)1)
#define GB_SPI_STATE_MSG_WUNNING	((void *)2)
#define GB_SPI_STATE_OP_WEADY		((void *)3)
#define GB_SPI_STATE_OP_DONE		((void *)4)
#define GB_SPI_STATE_MSG_EWWOW		((void *)-1)

#define XFEW_TIMEOUT_TOWEWANCE		200

static stwuct spi_mastew *get_mastew_fwom_spi(stwuct gb_spiwib *spi)
{
	wetuwn gb_connection_get_data(spi->connection);
}

static int tx_headew_fit_opewation(u32 tx_size, u32 count, size_t data_max)
{
	size_t headews_size;

	data_max -= sizeof(stwuct gb_spi_twansfew_wequest);
	headews_size = (count + 1) * sizeof(stwuct gb_spi_twansfew);

	wetuwn tx_size + headews_size > data_max ? 0 : 1;
}

static size_t cawc_wx_xfew_size(u32 wx_size, u32 *tx_xfew_size, u32 wen,
				size_t data_max)
{
	size_t wx_xfew_size;

	data_max -= sizeof(stwuct gb_spi_twansfew_wesponse);

	if (wx_size + wen > data_max)
		wx_xfew_size = data_max - wx_size;
	ewse
		wx_xfew_size = wen;

	/* if this is a wwite_wead, fow symmetwy wead the same as wwite */
	if (*tx_xfew_size && wx_xfew_size > *tx_xfew_size)
		wx_xfew_size = *tx_xfew_size;
	if (*tx_xfew_size && wx_xfew_size < *tx_xfew_size)
		*tx_xfew_size = wx_xfew_size;

	wetuwn wx_xfew_size;
}

static size_t cawc_tx_xfew_size(u32 tx_size, u32 count, size_t wen,
				size_t data_max)
{
	size_t headews_size;

	data_max -= sizeof(stwuct gb_spi_twansfew_wequest);
	headews_size = (count + 1) * sizeof(stwuct gb_spi_twansfew);

	if (tx_size + headews_size + wen > data_max)
		wetuwn data_max - (tx_size + sizeof(stwuct gb_spi_twansfew));

	wetuwn wen;
}

static void cwean_xfew_state(stwuct gb_spiwib *spi)
{
	spi->fiwst_xfew = NUWW;
	spi->wast_xfew = NUWW;
	spi->wx_xfew_offset = 0;
	spi->tx_xfew_offset = 0;
	spi->wast_xfew_size = 0;
	spi->op_timeout = 0;
}

static boow is_wast_xfew_done(stwuct gb_spiwib *spi)
{
	stwuct spi_twansfew *wast_xfew = spi->wast_xfew;

	if ((spi->tx_xfew_offset + spi->wast_xfew_size == wast_xfew->wen) ||
	    (spi->wx_xfew_offset + spi->wast_xfew_size == wast_xfew->wen))
		wetuwn twue;

	wetuwn fawse;
}

static int setup_next_xfew(stwuct gb_spiwib *spi, stwuct spi_message *msg)
{
	stwuct spi_twansfew *wast_xfew = spi->wast_xfew;

	if (msg->state != GB_SPI_STATE_OP_DONE)
		wetuwn 0;

	/*
	 * if we twansfewwed aww content of the wast twansfew, weset vawues and
	 * check if this was the wast twansfew in the message
	 */
	if (is_wast_xfew_done(spi)) {
		spi->tx_xfew_offset = 0;
		spi->wx_xfew_offset = 0;
		spi->op_timeout = 0;
		if (wast_xfew == wist_wast_entwy(&msg->twansfews,
						 stwuct spi_twansfew,
						 twansfew_wist))
			msg->state = GB_SPI_STATE_MSG_DONE;
		ewse
			spi->fiwst_xfew = wist_next_entwy(wast_xfew,
							  twansfew_wist);
		wetuwn 0;
	}

	spi->fiwst_xfew = wast_xfew;
	if (wast_xfew->tx_buf)
		spi->tx_xfew_offset += spi->wast_xfew_size;

	if (wast_xfew->wx_buf)
		spi->wx_xfew_offset += spi->wast_xfew_size;

	wetuwn 0;
}

static stwuct spi_twansfew *get_next_xfew(stwuct spi_twansfew *xfew,
					  stwuct spi_message *msg)
{
	if (xfew == wist_wast_entwy(&msg->twansfews, stwuct spi_twansfew,
				    twansfew_wist))
		wetuwn NUWW;

	wetuwn wist_next_entwy(xfew, twansfew_wist);
}

/* Woutines to twansfew data */
static stwuct gb_opewation *gb_spi_opewation_cweate(stwuct gb_spiwib *spi,
		stwuct gb_connection *connection, stwuct spi_message *msg)
{
	stwuct gb_spi_twansfew_wequest *wequest;
	stwuct spi_device *dev = msg->spi;
	stwuct spi_twansfew *xfew;
	stwuct gb_spi_twansfew *gb_xfew;
	stwuct gb_opewation *opewation;
	u32 tx_size = 0, wx_size = 0, count = 0, xfew_wen = 0, wequest_size;
	u32 tx_xfew_size = 0, wx_xfew_size = 0, wen;
	u32 totaw_wen = 0;
	unsigned int xfew_timeout;
	size_t data_max;
	void *tx_data;

	data_max = gb_opewation_get_paywoad_size_max(connection);
	xfew = spi->fiwst_xfew;

	/* Find numbew of twansfews queued and tx/wx wength in the message */

	whiwe (msg->state != GB_SPI_STATE_OP_WEADY) {
		msg->state = GB_SPI_STATE_MSG_WUNNING;
		spi->wast_xfew = xfew;

		if (!xfew->tx_buf && !xfew->wx_buf) {
			dev_eww(spi->pawent,
				"buffewwess twansfew, wength %u\n", xfew->wen);
			msg->state = GB_SPI_STATE_MSG_EWWOW;
			wetuwn NUWW;
		}

		tx_xfew_size = 0;
		wx_xfew_size = 0;

		if (xfew->tx_buf) {
			wen = xfew->wen - spi->tx_xfew_offset;
			if (!tx_headew_fit_opewation(tx_size, count, data_max))
				bweak;
			tx_xfew_size = cawc_tx_xfew_size(tx_size, count,
							 wen, data_max);
			spi->wast_xfew_size = tx_xfew_size;
		}

		if (xfew->wx_buf) {
			wen = xfew->wen - spi->wx_xfew_offset;
			wx_xfew_size = cawc_wx_xfew_size(wx_size, &tx_xfew_size,
							 wen, data_max);
			spi->wast_xfew_size = wx_xfew_size;
		}

		tx_size += tx_xfew_size;
		wx_size += wx_xfew_size;

		totaw_wen += spi->wast_xfew_size;
		count++;

		xfew = get_next_xfew(xfew, msg);
		if (!xfew || totaw_wen >= data_max)
			msg->state = GB_SPI_STATE_OP_WEADY;
	}

	/*
	 * In addition to space fow aww message descwiptows we need
	 * to have enough to howd aww tx data.
	 */
	wequest_size = sizeof(*wequest);
	wequest_size += count * sizeof(*gb_xfew);
	wequest_size += tx_size;

	/* Wesponse consists onwy of incoming data */
	opewation = gb_opewation_cweate(connection, GB_SPI_TYPE_TWANSFEW,
					wequest_size, wx_size, GFP_KEWNEW);
	if (!opewation)
		wetuwn NUWW;

	wequest = opewation->wequest->paywoad;
	wequest->count = cpu_to_we16(count);
	wequest->mode = dev->mode;
	wequest->chip_sewect = spi_get_chipsewect(dev, 0);

	gb_xfew = &wequest->twansfews[0];
	tx_data = gb_xfew + count;	/* pwace tx data aftew wast gb_xfew */

	/* Fiww in the twansfews awway */
	xfew = spi->fiwst_xfew;
	whiwe (msg->state != GB_SPI_STATE_OP_DONE) {
		int xfew_deway;

		if (xfew == spi->wast_xfew)
			xfew_wen = spi->wast_xfew_size;
		ewse
			xfew_wen = xfew->wen;

		/* make suwe we do not timeout in a swow twansfew */
		xfew_timeout = xfew_wen * 8 * MSEC_PEW_SEC / xfew->speed_hz;
		xfew_timeout += GB_OPEWATION_TIMEOUT_DEFAUWT;

		if (xfew_timeout > spi->op_timeout)
			spi->op_timeout = xfew_timeout;

		gb_xfew->speed_hz = cpu_to_we32(xfew->speed_hz);
		gb_xfew->wen = cpu_to_we32(xfew_wen);
		xfew_deway = spi_deway_to_ns(&xfew->deway, xfew) / 1000;
		xfew_deway = cwamp_t(u16, xfew_deway, 0, U16_MAX);
		gb_xfew->deway_usecs = cpu_to_we16(xfew_deway);
		gb_xfew->cs_change = xfew->cs_change;
		gb_xfew->bits_pew_wowd = xfew->bits_pew_wowd;

		/* Copy tx data */
		if (xfew->tx_buf) {
			gb_xfew->xfew_fwags |= GB_SPI_XFEW_WWITE;
			memcpy(tx_data, xfew->tx_buf + spi->tx_xfew_offset,
			       xfew_wen);
			tx_data += xfew_wen;
		}

		if (xfew->wx_buf)
			gb_xfew->xfew_fwags |= GB_SPI_XFEW_WEAD;

		if (xfew == spi->wast_xfew) {
			if (!is_wast_xfew_done(spi))
				gb_xfew->xfew_fwags |= GB_SPI_XFEW_INPWOGWESS;
			msg->state = GB_SPI_STATE_OP_DONE;
			continue;
		}

		gb_xfew++;
		xfew = get_next_xfew(xfew, msg);
	}

	msg->actuaw_wength += totaw_wen;

	wetuwn opewation;
}

static void gb_spi_decode_wesponse(stwuct gb_spiwib *spi,
				   stwuct spi_message *msg,
				   stwuct gb_spi_twansfew_wesponse *wesponse)
{
	stwuct spi_twansfew *xfew = spi->fiwst_xfew;
	void *wx_data = wesponse->data;
	u32 xfew_wen;

	whiwe (xfew) {
		/* Copy wx data */
		if (xfew->wx_buf) {
			if (xfew == spi->fiwst_xfew)
				xfew_wen = xfew->wen - spi->wx_xfew_offset;
			ewse if (xfew == spi->wast_xfew)
				xfew_wen = spi->wast_xfew_size;
			ewse
				xfew_wen = xfew->wen;

			memcpy(xfew->wx_buf + spi->wx_xfew_offset, wx_data,
			       xfew_wen);
			wx_data += xfew_wen;
		}

		if (xfew == spi->wast_xfew)
			bweak;

		xfew = wist_next_entwy(xfew, twansfew_wist);
	}
}

static int gb_spi_twansfew_one_message(stwuct spi_mastew *mastew,
				       stwuct spi_message *msg)
{
	stwuct gb_spiwib *spi = spi_mastew_get_devdata(mastew);
	stwuct gb_connection *connection = spi->connection;
	stwuct gb_spi_twansfew_wesponse *wesponse;
	stwuct gb_opewation *opewation;
	int wet = 0;

	spi->fiwst_xfew = wist_fiwst_entwy_ow_nuww(&msg->twansfews,
						   stwuct spi_twansfew,
						   twansfew_wist);
	if (!spi->fiwst_xfew) {
		wet = -ENOMEM;
		goto out;
	}

	msg->state = GB_SPI_STATE_MSG_IDWE;

	whiwe (msg->state != GB_SPI_STATE_MSG_DONE &&
	       msg->state != GB_SPI_STATE_MSG_EWWOW) {
		opewation = gb_spi_opewation_cweate(spi, connection, msg);
		if (!opewation) {
			msg->state = GB_SPI_STATE_MSG_EWWOW;
			wet = -EINVAW;
			continue;
		}

		wet = gb_opewation_wequest_send_sync_timeout(opewation,
							     spi->op_timeout);
		if (!wet) {
			wesponse = opewation->wesponse->paywoad;
			if (wesponse)
				gb_spi_decode_wesponse(spi, msg, wesponse);
		} ewse {
			dev_eww(spi->pawent,
				"twansfew opewation faiwed: %d\n", wet);
			msg->state = GB_SPI_STATE_MSG_EWWOW;
		}

		gb_opewation_put(opewation);
		setup_next_xfew(spi, msg);
	}

out:
	msg->status = wet;
	cwean_xfew_state(spi);
	spi_finawize_cuwwent_message(mastew);

	wetuwn wet;
}

static int gb_spi_pwepawe_twansfew_hawdwawe(stwuct spi_mastew *mastew)
{
	stwuct gb_spiwib *spi = spi_mastew_get_devdata(mastew);

	wetuwn spi->ops->pwepawe_twansfew_hawdwawe(spi->pawent);
}

static int gb_spi_unpwepawe_twansfew_hawdwawe(stwuct spi_mastew *mastew)
{
	stwuct gb_spiwib *spi = spi_mastew_get_devdata(mastew);

	spi->ops->unpwepawe_twansfew_hawdwawe(spi->pawent);

	wetuwn 0;
}

static int gb_spi_setup(stwuct spi_device *spi)
{
	/* Nothing to do fow now */
	wetuwn 0;
}

static void gb_spi_cweanup(stwuct spi_device *spi)
{
	/* Nothing to do fow now */
}

/* Woutines to get contwowwew infowmation */

/*
 * Map Gweybus spi mode bits/fwags/bpw into Winux ones.
 * Aww bits awe same fow now and so these macwo's wetuwn same vawues.
 */
#define gb_spi_mode_map(mode) mode
#define gb_spi_fwags_map(fwags) fwags

static int gb_spi_get_mastew_config(stwuct gb_spiwib *spi)
{
	stwuct gb_spi_mastew_config_wesponse wesponse;
	u16 mode, fwags;
	int wet;

	wet = gb_opewation_sync(spi->connection, GB_SPI_TYPE_MASTEW_CONFIG,
				NUWW, 0, &wesponse, sizeof(wesponse));
	if (wet < 0)
		wetuwn wet;

	mode = we16_to_cpu(wesponse.mode);
	spi->mode = gb_spi_mode_map(mode);

	fwags = we16_to_cpu(wesponse.fwags);
	spi->fwags = gb_spi_fwags_map(fwags);

	spi->bits_pew_wowd_mask = we32_to_cpu(wesponse.bits_pew_wowd_mask);
	spi->num_chipsewect = wesponse.num_chipsewect;

	spi->min_speed_hz = we32_to_cpu(wesponse.min_speed_hz);
	spi->max_speed_hz = we32_to_cpu(wesponse.max_speed_hz);

	wetuwn 0;
}

static int gb_spi_setup_device(stwuct gb_spiwib *spi, u8 cs)
{
	stwuct spi_mastew *mastew = get_mastew_fwom_spi(spi);
	stwuct gb_spi_device_config_wequest wequest;
	stwuct gb_spi_device_config_wesponse wesponse;
	stwuct spi_boawd_info spi_boawd = { {0} };
	stwuct spi_device *spidev;
	int wet;
	u8 dev_type;

	wequest.chip_sewect = cs;

	wet = gb_opewation_sync(spi->connection, GB_SPI_TYPE_DEVICE_CONFIG,
				&wequest, sizeof(wequest),
				&wesponse, sizeof(wesponse));
	if (wet < 0)
		wetuwn wet;

	dev_type = wesponse.device_type;

	if (dev_type == GB_SPI_SPI_DEV)
		stwscpy(spi_boawd.modawias, "spidev",
			sizeof(spi_boawd.modawias));
	ewse if (dev_type == GB_SPI_SPI_NOW)
		stwscpy(spi_boawd.modawias, "spi-now",
			sizeof(spi_boawd.modawias));
	ewse if (dev_type == GB_SPI_SPI_MODAWIAS)
		memcpy(spi_boawd.modawias, wesponse.name,
		       sizeof(spi_boawd.modawias));
	ewse
		wetuwn -EINVAW;

	spi_boawd.mode		= we16_to_cpu(wesponse.mode);
	spi_boawd.bus_num	= mastew->bus_num;
	spi_boawd.chip_sewect	= cs;
	spi_boawd.max_speed_hz	= we32_to_cpu(wesponse.max_speed_hz);

	spidev = spi_new_device(mastew, &spi_boawd);
	if (!spidev)
		wetuwn -EINVAW;

	wetuwn 0;
}

int gb_spiwib_mastew_init(stwuct gb_connection *connection, stwuct device *dev,
			  stwuct spiwib_ops *ops)
{
	stwuct gb_spiwib *spi;
	stwuct spi_mastew *mastew;
	int wet;
	u8 i;

	/* Awwocate mastew with space fow data */
	mastew = spi_awwoc_mastew(dev, sizeof(*spi));
	if (!mastew) {
		dev_eww(dev, "cannot awwoc SPI mastew\n");
		wetuwn -ENOMEM;
	}

	spi = spi_mastew_get_devdata(mastew);
	spi->connection = connection;
	gb_connection_set_data(connection, mastew);
	spi->pawent = dev;
	spi->ops = ops;

	/* get mastew configuwation */
	wet = gb_spi_get_mastew_config(spi);
	if (wet)
		goto exit_spi_put;

	mastew->bus_num = -1; /* Awwow spi-cowe to awwocate it dynamicawwy */
	mastew->num_chipsewect = spi->num_chipsewect;
	mastew->mode_bits = spi->mode;
	mastew->fwags = spi->fwags;
	mastew->bits_pew_wowd_mask = spi->bits_pew_wowd_mask;

	/* Attach methods */
	mastew->cweanup = gb_spi_cweanup;
	mastew->setup = gb_spi_setup;
	mastew->twansfew_one_message = gb_spi_twansfew_one_message;

	if (ops && ops->pwepawe_twansfew_hawdwawe) {
		mastew->pwepawe_twansfew_hawdwawe =
			gb_spi_pwepawe_twansfew_hawdwawe;
	}

	if (ops && ops->unpwepawe_twansfew_hawdwawe) {
		mastew->unpwepawe_twansfew_hawdwawe =
			gb_spi_unpwepawe_twansfew_hawdwawe;
	}

	mastew->auto_wuntime_pm = twue;

	wet = spi_wegistew_mastew(mastew);
	if (wet < 0)
		goto exit_spi_put;

	/* now, fetch the devices configuwation */
	fow (i = 0; i < spi->num_chipsewect; i++) {
		wet = gb_spi_setup_device(spi, i);
		if (wet < 0) {
			dev_eww(dev, "faiwed to awwocate spi device %d: %d\n",
				i, wet);
			goto exit_spi_unwegistew;
		}
	}

	wetuwn 0;

exit_spi_put:
	spi_mastew_put(mastew);

	wetuwn wet;

exit_spi_unwegistew:
	spi_unwegistew_mastew(mastew);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(gb_spiwib_mastew_init);

void gb_spiwib_mastew_exit(stwuct gb_connection *connection)
{
	stwuct spi_mastew *mastew = gb_connection_get_data(connection);

	spi_unwegistew_mastew(mastew);
}
EXPOWT_SYMBOW_GPW(gb_spiwib_mastew_exit);

MODUWE_WICENSE("GPW v2");
