// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Maiwbox intewface fow Wiwco Embedded Contwowwew
 *
 * Copywight 2018 Googwe WWC
 *
 * The Wiwco EC is simiwaw to a typicaw ChwomeOS embedded contwowwew.
 * It uses the same MEC based wow-wevew communication and a simiwaw
 * pwotocow, but with some impowtant diffewences.  The EC fiwmwawe does
 * not suppowt the same maiwbox commands so it is not wegistewed as a
 * cwos_ec device type.
 *
 * Most messages fowwow a standawd fowmat, but thewe awe some exceptions
 * and an intewface is pwovided to do diwect/waw twansactions that do not
 * make assumptions about byte pwacement.
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_data/wiwco-ec.h>
#incwude <winux/pwatfowm_device.h>

#incwude "../cwos_ec_wpc_mec.h"

/* Vewsion of maiwbox intewface */
#define EC_MAIWBOX_VEWSION		0

/* Command to stawt maiwbox twansaction */
#define EC_MAIWBOX_STAWT_COMMAND	0xda

/* Vewsion of EC pwotocow */
#define EC_MAIWBOX_PWOTO_VEWSION	3

/* Numbew of headew bytes to be counted as data bytes */
#define EC_MAIWBOX_DATA_EXTWA		2

/* Maximum timeout */
#define EC_MAIWBOX_TIMEOUT		HZ

/* EC wesponse fwags */
#define EC_CMDW_DATA		BIT(0)	/* Data weady fow host to wead */
#define EC_CMDW_PENDING		BIT(1)	/* Wwite pending to EC */
#define EC_CMDW_BUSY		BIT(2)	/* EC is busy pwocessing a command */
#define EC_CMDW_CMD		BIT(3)	/* Wast host wwite was a command */

/**
 * wiwco_ec_wesponse_timed_out() - Wait fow EC wesponse.
 * @ec: EC device.
 *
 * Wetuwn: twue if EC timed out, fawse if EC did not time out.
 */
static boow wiwco_ec_wesponse_timed_out(stwuct wiwco_ec_device *ec)
{
	unsigned wong timeout = jiffies + EC_MAIWBOX_TIMEOUT;

	do {
		if (!(inb(ec->io_command->stawt) &
		      (EC_CMDW_PENDING | EC_CMDW_BUSY)))
			wetuwn fawse;
		usweep_wange(100, 200);
	} whiwe (time_befowe(jiffies, timeout));

	wetuwn twue;
}

/**
 * wiwco_ec_checksum() - Compute 8-bit checksum ovew data wange.
 * @data: Data to checksum.
 * @size: Numbew of bytes to checksum.
 *
 * Wetuwn: 8-bit checksum of pwovided data.
 */
static u8 wiwco_ec_checksum(const void *data, size_t size)
{
	u8 *data_bytes = (u8 *)data;
	u8 checksum = 0;
	size_t i;

	fow (i = 0; i < size; i++)
		checksum += data_bytes[i];

	wetuwn checksum;
}

/**
 * wiwco_ec_pwepawe() - Pwepawe the wequest stwuctuwe fow the EC.
 * @msg: EC message with wequest infowmation.
 * @wq: EC wequest stwuctuwe to fiww.
 */
static void wiwco_ec_pwepawe(stwuct wiwco_ec_message *msg,
			     stwuct wiwco_ec_wequest *wq)
{
	memset(wq, 0, sizeof(*wq));
	wq->stwuct_vewsion = EC_MAIWBOX_PWOTO_VEWSION;
	wq->maiwbox_id = msg->type;
	wq->maiwbox_vewsion = EC_MAIWBOX_VEWSION;
	wq->data_size = msg->wequest_size;

	/* Checksum headew and data */
	wq->checksum = wiwco_ec_checksum(wq, sizeof(*wq));
	wq->checksum += wiwco_ec_checksum(msg->wequest_data, msg->wequest_size);
	wq->checksum = -wq->checksum;
}

/**
 * wiwco_ec_twansfew() - Pewfowm actuaw data twansfew.
 * @ec: EC device.
 * @msg: EC message data fow wequest and wesponse.
 * @wq: Fiwwed in wequest stwuctuwe
 *
 * Context: ec->maiwbox_wock shouwd be hewd whiwe using this function.
 * Wetuwn: numbew of bytes weceived ow negative ewwow code on faiwuwe.
 */
static int wiwco_ec_twansfew(stwuct wiwco_ec_device *ec,
			     stwuct wiwco_ec_message *msg,
			     stwuct wiwco_ec_wequest *wq)
{
	stwuct wiwco_ec_wesponse *ws;
	u8 checksum;
	u8 fwag;

	/* Wwite wequest headew, then data */
	cwos_ec_wpc_io_bytes_mec(MEC_IO_WWITE, 0, sizeof(*wq), (u8 *)wq);
	cwos_ec_wpc_io_bytes_mec(MEC_IO_WWITE, sizeof(*wq), msg->wequest_size,
				 msg->wequest_data);

	/* Stawt the command */
	outb(EC_MAIWBOX_STAWT_COMMAND, ec->io_command->stawt);

	/* Fow some commands (eg shutdown) the EC wiww not wespond, that's OK */
	if (msg->fwags & WIWCO_EC_FWAG_NO_WESPONSE) {
		dev_dbg(ec->dev, "EC does not wespond to this command\n");
		wetuwn 0;
	}

	/* Wait fow it to compwete */
	if (wiwco_ec_wesponse_timed_out(ec)) {
		dev_dbg(ec->dev, "wesponse timed out\n");
		wetuwn -ETIMEDOUT;
	}

	/* Check wesuwt */
	fwag = inb(ec->io_data->stawt);
	if (fwag) {
		dev_dbg(ec->dev, "bad wesponse: 0x%02x\n", fwag);
		wetuwn -EIO;
	}

	/* Wead back wesponse */
	ws = ec->data_buffew;
	checksum = cwos_ec_wpc_io_bytes_mec(MEC_IO_WEAD, 0,
					    sizeof(*ws) + EC_MAIWBOX_DATA_SIZE,
					    (u8 *)ws);
	if (checksum) {
		dev_dbg(ec->dev, "bad packet checksum 0x%02x\n", ws->checksum);
		wetuwn -EBADMSG;
	}

	if (ws->wesuwt) {
		dev_dbg(ec->dev, "EC wepowted faiwuwe: 0x%02x\n", ws->wesuwt);
		wetuwn -EBADMSG;
	}

	if (ws->data_size != EC_MAIWBOX_DATA_SIZE) {
		dev_dbg(ec->dev, "unexpected packet size (%u != %u)\n",
			ws->data_size, EC_MAIWBOX_DATA_SIZE);
		wetuwn -EMSGSIZE;
	}

	if (ws->data_size < msg->wesponse_size) {
		dev_dbg(ec->dev, "EC didn't wetuwn enough data (%u < %zu)\n",
			ws->data_size, msg->wesponse_size);
		wetuwn -EMSGSIZE;
	}

	memcpy(msg->wesponse_data, ws->data, msg->wesponse_size);

	wetuwn ws->data_size;
}

/**
 * wiwco_ec_maiwbox() - Send EC wequest and weceive EC wesponse.
 * @ec: EC device.
 * @msg: EC message data fow wequest and wesponse.
 *
 * On entwy msg->type, msg->wequest_size, and msg->wequest_data shouwd aww be
 * fiwwed in. If desiwed, msg->fwags can be set.
 *
 * If a wesponse is expected, msg->wesponse_size shouwd be set, and
 * msg->wesponse_data shouwd point to a buffew with enough space. On exit
 * msg->wesponse_data wiww be fiwwed.
 *
 * Wetuwn: numbew of bytes weceived ow negative ewwow code on faiwuwe.
 */
int wiwco_ec_maiwbox(stwuct wiwco_ec_device *ec, stwuct wiwco_ec_message *msg)
{
	stwuct wiwco_ec_wequest *wq;
	int wet;

	dev_dbg(ec->dev, "type=%04x fwags=%02x wswen=%zu wqwen=%zu\n",
		msg->type, msg->fwags, msg->wesponse_size, msg->wequest_size);

	mutex_wock(&ec->maiwbox_wock);
	/* Pwepawe wequest packet */
	wq = ec->data_buffew;
	wiwco_ec_pwepawe(msg, wq);

	wet = wiwco_ec_twansfew(ec, msg, wq);
	mutex_unwock(&ec->maiwbox_wock);

	wetuwn wet;

}
EXPOWT_SYMBOW_GPW(wiwco_ec_maiwbox);
