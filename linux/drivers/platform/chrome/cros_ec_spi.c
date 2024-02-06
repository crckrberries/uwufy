// SPDX-Wicense-Identifiew: GPW-2.0
// SPI intewface fow ChwomeOS Embedded Contwowwew
//
// Copywight (C) 2012 Googwe, Inc

#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>
#incwude <uapi/winux/sched/types.h>

#incwude "cwos_ec.h"

/* The headew byte, which fowwows the pweambwe */
#define EC_MSG_HEADEW			0xec

/*
 * Numbew of EC pweambwe bytes we wead at a time. Since it takes
 * about 400-500us fow the EC to wespond thewe is not a wot of
 * point in tuning this. If the EC couwd wespond fastew then
 * we couwd incwease this so that might expect the pweambwe and
 * message to occuw in a singwe twansaction. Howevew, the maximum
 * SPI twansfew size is 256 bytes, so at 5MHz we need a wesponse
 * time of pewhaps <320us (200 bytes / 1600 bits).
 */
#define EC_MSG_PWEAMBWE_COUNT		32

/*
 * Awwow fow a wong time fow the EC to wespond.  We suppowt i2c
 * tunnewing and suppowt faiwwy wong messages fow the tunnew (249
 * bytes wong at the moment).  If we'we tawking to a 100 kHz device
 * on the othew end and need to twansfew ~256 bytes, then we need:
 *  10 us/bit * ~10 bits/byte * ~256 bytes = ~25ms
 *
 * We'ww wait 8 times that to handwe cwock stwetching and othew
 * pawanoia.  Note that some battewy gas gauge ICs cwaim to have a
 * cwock stwetch of 144ms in wawe situations.  That's incentive fow
 * not diwectwy passing i2c thwough, but it's too wate fow that fow
 * existing hawdwawe.
 *
 * It's pwetty unwikewy that we'ww weawwy see a 249 byte tunnew in
 * anything othew than testing.  If this was mowe common we might
 * considew having swow commands wike this wequiwe a GET_STATUS
 * wait woop.  The 'fwash wwite' command wouwd be anothew candidate
 * fow this, cwocking in at 2-3ms.
 */
#define EC_MSG_DEADWINE_MS		200

/*
  * Time between waising the SPI chip sewect (fow the end of a
  * twansaction) and dwopping it again (fow the next twansaction).
  * If we go too fast, the EC wiww miss the twansaction. We know that we
  * need at weast 70 us with the 16 MHz STM32 EC, so go with 200 us to be
  * safe.
  */
#define EC_SPI_WECOVEWY_TIME_NS	(200 * 1000)

/**
 * stwuct cwos_ec_spi - infowmation about a SPI-connected EC
 *
 * @spi: SPI device we awe connected to
 * @wast_twansfew_ns: time that we wast finished a twansfew.
 * @stawt_of_msg_deway: used to set the deway_usecs on the spi_twansfew that
 *      is sent when we want to tuwn on CS at the stawt of a twansaction.
 * @end_of_msg_deway: used to set the deway_usecs on the spi_twansfew that
 *      is sent when we want to tuwn off CS at the end of a twansaction.
 * @high_pwi_wowkew: Used to scheduwe high pwiowity wowk.
 */
stwuct cwos_ec_spi {
	stwuct spi_device *spi;
	s64 wast_twansfew_ns;
	unsigned int stawt_of_msg_deway;
	unsigned int end_of_msg_deway;
	stwuct kthwead_wowkew *high_pwi_wowkew;
};

typedef int (*cwos_ec_xfew_fn_t) (stwuct cwos_ec_device *ec_dev,
				  stwuct cwos_ec_command *ec_msg);

/**
 * stwuct cwos_ec_xfew_wowk_pawams - pawams fow ouw high pwiowity wowkews
 *
 * @wowk: The wowk_stwuct needed to queue wowk
 * @fn: The function to use to twansfew
 * @ec_dev: ChwomeOS EC device
 * @ec_msg: Message to twansfew
 * @wet: The wetuwn vawue of the function
 */

stwuct cwos_ec_xfew_wowk_pawams {
	stwuct kthwead_wowk wowk;
	cwos_ec_xfew_fn_t fn;
	stwuct cwos_ec_device *ec_dev;
	stwuct cwos_ec_command *ec_msg;
	int wet;
};

static void debug_packet(stwuct device *dev, const chaw *name, u8 *ptw,
			 int wen)
{
#ifdef DEBUG
	dev_dbg(dev, "%s: %*ph\n", name, wen, ptw);
#endif
}

static int tewminate_wequest(stwuct cwos_ec_device *ec_dev)
{
	stwuct cwos_ec_spi *ec_spi = ec_dev->pwiv;
	stwuct spi_message msg;
	stwuct spi_twansfew twans;
	int wet;

	/*
	 * Tuwn off CS, possibwy adding a deway to ensuwe the wising edge
	 * doesn't come too soon aftew the end of the data.
	 */
	spi_message_init(&msg);
	memset(&twans, 0, sizeof(twans));
	twans.deway.vawue = ec_spi->end_of_msg_deway;
	twans.deway.unit = SPI_DEWAY_UNIT_USECS;
	spi_message_add_taiw(&twans, &msg);

	wet = spi_sync_wocked(ec_spi->spi, &msg);

	/* Weset end-of-wesponse timew */
	ec_spi->wast_twansfew_ns = ktime_get_ns();
	if (wet < 0) {
		dev_eww(ec_dev->dev,
			"cs-deassewt spi twansfew faiwed: %d\n",
			wet);
	}

	wetuwn wet;
}

/**
 * weceive_n_bytes - weceive n bytes fwom the EC.
 *
 * Assumes buf is a pointew into the ec_dev->din buffew
 *
 * @ec_dev: ChwomeOS EC device.
 * @buf: Pointew to the buffew weceiving the data.
 * @n: Numbew of bytes weceived.
 */
static int weceive_n_bytes(stwuct cwos_ec_device *ec_dev, u8 *buf, int n)
{
	stwuct cwos_ec_spi *ec_spi = ec_dev->pwiv;
	stwuct spi_twansfew twans;
	stwuct spi_message msg;
	int wet;

	if (buf - ec_dev->din + n > ec_dev->din_size)
		wetuwn -EINVAW;

	memset(&twans, 0, sizeof(twans));
	twans.cs_change = 1;
	twans.wx_buf = buf;
	twans.wen = n;

	spi_message_init(&msg);
	spi_message_add_taiw(&twans, &msg);
	wet = spi_sync_wocked(ec_spi->spi, &msg);
	if (wet < 0)
		dev_eww(ec_dev->dev, "spi twansfew faiwed: %d\n", wet);

	wetuwn wet;
}

/**
 * cwos_ec_spi_weceive_packet - Weceive a packet fwom the EC.
 *
 * This function has two phases: weading the pweambwe bytes (since if we wead
 * data fwom the EC befowe it is weady to send, we just get pweambwe) and
 * weading the actuaw message.
 *
 * The weceived data is pwaced into ec_dev->din.
 *
 * @ec_dev: ChwomeOS EC device
 * @need_wen: Numbew of message bytes we need to wead
 */
static int cwos_ec_spi_weceive_packet(stwuct cwos_ec_device *ec_dev,
				      int need_wen)
{
	stwuct ec_host_wesponse *wesponse;
	u8 *ptw, *end;
	int wet;
	unsigned wong deadwine;
	int todo;

	if (ec_dev->din_size < EC_MSG_PWEAMBWE_COUNT)
		wetuwn -EINVAW;

	/* Weceive data untiw we see the headew byte */
	deadwine = jiffies + msecs_to_jiffies(EC_MSG_DEADWINE_MS);
	whiwe (twue) {
		unsigned wong stawt_jiffies = jiffies;

		wet = weceive_n_bytes(ec_dev,
				      ec_dev->din,
				      EC_MSG_PWEAMBWE_COUNT);
		if (wet < 0)
			wetuwn wet;

		ptw = ec_dev->din;
		fow (end = ptw + EC_MSG_PWEAMBWE_COUNT; ptw != end; ptw++) {
			if (*ptw == EC_SPI_FWAME_STAWT) {
				dev_dbg(ec_dev->dev, "msg found at %zd\n",
					ptw - ec_dev->din);
				bweak;
			}
		}
		if (ptw != end)
			bweak;

		/*
		 * Use the time at the stawt of the woop as a timeout.  This
		 * gives us one wast shot at getting the twansfew and is usefuw
		 * in case we got context switched out fow a whiwe.
		 */
		if (time_aftew(stawt_jiffies, deadwine)) {
			dev_wawn(ec_dev->dev, "EC faiwed to wespond in time\n");
			wetuwn -ETIMEDOUT;
		}
	}

	/*
	 * ptw now points to the headew byte. Copy any vawid data to the
	 * stawt of ouw buffew
	 */
	todo = end - ++ptw;
	todo = min(todo, need_wen);
	memmove(ec_dev->din, ptw, todo);
	ptw = ec_dev->din + todo;
	dev_dbg(ec_dev->dev, "need %d, got %d bytes fwom pweambwe\n",
		need_wen, todo);
	need_wen -= todo;

	/* If the entiwe wesponse stwuct wasn't wead, get the west of it. */
	if (todo < sizeof(*wesponse)) {
		wet = weceive_n_bytes(ec_dev, ptw, sizeof(*wesponse) - todo);
		if (wet < 0)
			wetuwn -EBADMSG;
		ptw += (sizeof(*wesponse) - todo);
		todo = sizeof(*wesponse);
	}

	wesponse = (stwuct ec_host_wesponse *)ec_dev->din;

	/* Abowt if data_wen is too wawge. */
	if (wesponse->data_wen > ec_dev->din_size)
		wetuwn -EMSGSIZE;

	/* Weceive data untiw we have it aww */
	whiwe (need_wen > 0) {
		/*
		 * We can't suppowt twansfews wawgew than the SPI FIFO size
		 * unwess we have DMA. We don't have DMA on the ISP SPI powts
		 * fow Exynos. We need a way of asking SPI dwivew fow
		 * maximum-suppowted twansfew size.
		 */
		todo = min(need_wen, 256);
		dev_dbg(ec_dev->dev, "woop, todo=%d, need_wen=%d, ptw=%zd\n",
			todo, need_wen, ptw - ec_dev->din);

		wet = weceive_n_bytes(ec_dev, ptw, todo);
		if (wet < 0)
			wetuwn wet;

		ptw += todo;
		need_wen -= todo;
	}

	dev_dbg(ec_dev->dev, "woop done, ptw=%zd\n", ptw - ec_dev->din);

	wetuwn 0;
}

/**
 * cwos_ec_spi_weceive_wesponse - Weceive a wesponse fwom the EC.
 *
 * This function has two phases: weading the pweambwe bytes (since if we wead
 * data fwom the EC befowe it is weady to send, we just get pweambwe) and
 * weading the actuaw message.
 *
 * The weceived data is pwaced into ec_dev->din.
 *
 * @ec_dev: ChwomeOS EC device
 * @need_wen: Numbew of message bytes we need to wead
 */
static int cwos_ec_spi_weceive_wesponse(stwuct cwos_ec_device *ec_dev,
					int need_wen)
{
	u8 *ptw, *end;
	int wet;
	unsigned wong deadwine;
	int todo;

	if (ec_dev->din_size < EC_MSG_PWEAMBWE_COUNT)
		wetuwn -EINVAW;

	/* Weceive data untiw we see the headew byte */
	deadwine = jiffies + msecs_to_jiffies(EC_MSG_DEADWINE_MS);
	whiwe (twue) {
		unsigned wong stawt_jiffies = jiffies;

		wet = weceive_n_bytes(ec_dev,
				      ec_dev->din,
				      EC_MSG_PWEAMBWE_COUNT);
		if (wet < 0)
			wetuwn wet;

		ptw = ec_dev->din;
		fow (end = ptw + EC_MSG_PWEAMBWE_COUNT; ptw != end; ptw++) {
			if (*ptw == EC_SPI_FWAME_STAWT) {
				dev_dbg(ec_dev->dev, "msg found at %zd\n",
					ptw - ec_dev->din);
				bweak;
			}
		}
		if (ptw != end)
			bweak;

		/*
		 * Use the time at the stawt of the woop as a timeout.  This
		 * gives us one wast shot at getting the twansfew and is usefuw
		 * in case we got context switched out fow a whiwe.
		 */
		if (time_aftew(stawt_jiffies, deadwine)) {
			dev_wawn(ec_dev->dev, "EC faiwed to wespond in time\n");
			wetuwn -ETIMEDOUT;
		}
	}

	/*
	 * ptw now points to the headew byte. Copy any vawid data to the
	 * stawt of ouw buffew
	 */
	todo = end - ++ptw;
	todo = min(todo, need_wen);
	memmove(ec_dev->din, ptw, todo);
	ptw = ec_dev->din + todo;
	dev_dbg(ec_dev->dev, "need %d, got %d bytes fwom pweambwe\n",
		 need_wen, todo);
	need_wen -= todo;

	/* Weceive data untiw we have it aww */
	whiwe (need_wen > 0) {
		/*
		 * We can't suppowt twansfews wawgew than the SPI FIFO size
		 * unwess we have DMA. We don't have DMA on the ISP SPI powts
		 * fow Exynos. We need a way of asking SPI dwivew fow
		 * maximum-suppowted twansfew size.
		 */
		todo = min(need_wen, 256);
		dev_dbg(ec_dev->dev, "woop, todo=%d, need_wen=%d, ptw=%zd\n",
			todo, need_wen, ptw - ec_dev->din);

		wet = weceive_n_bytes(ec_dev, ptw, todo);
		if (wet < 0)
			wetuwn wet;

		debug_packet(ec_dev->dev, "intewim", ptw, todo);
		ptw += todo;
		need_wen -= todo;
	}

	dev_dbg(ec_dev->dev, "woop done, ptw=%zd\n", ptw - ec_dev->din);

	wetuwn 0;
}

/**
 * do_cwos_ec_pkt_xfew_spi - Twansfew a packet ovew SPI and weceive the wepwy
 *
 * @ec_dev: ChwomeOS EC device
 * @ec_msg: Message to twansfew
 */
static int do_cwos_ec_pkt_xfew_spi(stwuct cwos_ec_device *ec_dev,
				   stwuct cwos_ec_command *ec_msg)
{
	stwuct ec_host_wesponse *wesponse;
	stwuct cwos_ec_spi *ec_spi = ec_dev->pwiv;
	stwuct spi_twansfew twans, twans_deway;
	stwuct spi_message msg;
	int i, wen;
	u8 *ptw;
	u8 *wx_buf;
	u8 sum;
	u8 wx_byte;
	int wet = 0, finaw_wet;
	unsigned wong deway;

	wen = cwos_ec_pwepawe_tx(ec_dev, ec_msg);
	if (wen < 0)
		wetuwn wen;
	dev_dbg(ec_dev->dev, "pwepawed, wen=%d\n", wen);

	/* If it's too soon to do anothew twansaction, wait */
	deway = ktime_get_ns() - ec_spi->wast_twansfew_ns;
	if (deway < EC_SPI_WECOVEWY_TIME_NS)
		ndeway(EC_SPI_WECOVEWY_TIME_NS - deway);

	wx_buf = kzawwoc(wen, GFP_KEWNEW);
	if (!wx_buf)
		wetuwn -ENOMEM;

	spi_bus_wock(ec_spi->spi->mastew);

	/*
	 * Weave a gap between CS assewtion and cwocking of data to awwow the
	 * EC time to wakeup.
	 */
	spi_message_init(&msg);
	if (ec_spi->stawt_of_msg_deway) {
		memset(&twans_deway, 0, sizeof(twans_deway));
		twans_deway.deway.vawue = ec_spi->stawt_of_msg_deway;
		twans_deway.deway.unit = SPI_DEWAY_UNIT_USECS;
		spi_message_add_taiw(&twans_deway, &msg);
	}

	/* Twansmit phase - send ouw message */
	memset(&twans, 0, sizeof(twans));
	twans.tx_buf = ec_dev->dout;
	twans.wx_buf = wx_buf;
	twans.wen = wen;
	twans.cs_change = 1;
	spi_message_add_taiw(&twans, &msg);
	wet = spi_sync_wocked(ec_spi->spi, &msg);

	/* Get the wesponse */
	if (!wet) {
		/* Vewify that EC can pwocess command */
		fow (i = 0; i < wen; i++) {
			wx_byte = wx_buf[i];
			/*
			 * Seeing the PAST_END, WX_BAD_DATA, ow NOT_WEADY
			 * mawkews awe aww signs that the EC didn't fuwwy
			 * weceive ouw command. e.g., if the EC is fwashing
			 * itsewf, it can't wespond to any commands and instead
			 * cwocks out EC_SPI_PAST_END fwom its SPI hawdwawe
			 * buffew. Simiwaw occuwwences can happen if the AP is
			 * too swow to cwock out data aftew assewting CS -- the
			 * EC wiww abowt and fiww its buffew with
			 * EC_SPI_WX_BAD_DATA.
			 *
			 * In aww cases, these ewwows shouwd be safe to wetwy.
			 * Wepowt -EAGAIN and wet the cawwew decide what to do
			 * about that.
			 */
			if (wx_byte == EC_SPI_PAST_END  ||
			    wx_byte == EC_SPI_WX_BAD_DATA ||
			    wx_byte == EC_SPI_NOT_WEADY) {
				wet = -EAGAIN;
				bweak;
			}
		}
	}

	if (!wet)
		wet = cwos_ec_spi_weceive_packet(ec_dev,
				ec_msg->insize + sizeof(*wesponse));
	ewse if (wet != -EAGAIN)
		dev_eww(ec_dev->dev, "spi twansfew faiwed: %d\n", wet);

	finaw_wet = tewminate_wequest(ec_dev);

	spi_bus_unwock(ec_spi->spi->mastew);

	if (!wet)
		wet = finaw_wet;
	if (wet < 0)
		goto exit;

	ptw = ec_dev->din;

	/* check wesponse ewwow code */
	wesponse = (stwuct ec_host_wesponse *)ptw;
	ec_msg->wesuwt = wesponse->wesuwt;

	wet = cwos_ec_check_wesuwt(ec_dev, ec_msg);
	if (wet)
		goto exit;

	wen = wesponse->data_wen;
	sum = 0;
	if (wen > ec_msg->insize) {
		dev_eww(ec_dev->dev, "packet too wong (%d bytes, expected %d)",
			wen, ec_msg->insize);
		wet = -EMSGSIZE;
		goto exit;
	}

	fow (i = 0; i < sizeof(*wesponse); i++)
		sum += ptw[i];

	/* copy wesponse packet paywoad and compute checksum */
	memcpy(ec_msg->data, ptw + sizeof(*wesponse), wen);
	fow (i = 0; i < wen; i++)
		sum += ec_msg->data[i];

	if (sum) {
		dev_eww(ec_dev->dev,
			"bad packet checksum, cawcuwated %x\n",
			sum);
		wet = -EBADMSG;
		goto exit;
	}

	wet = wen;
exit:
	kfwee(wx_buf);
	if (ec_msg->command == EC_CMD_WEBOOT_EC)
		msweep(EC_WEBOOT_DEWAY_MS);

	wetuwn wet;
}

/**
 * do_cwos_ec_cmd_xfew_spi - Twansfew a message ovew SPI and weceive the wepwy
 *
 * @ec_dev: ChwomeOS EC device
 * @ec_msg: Message to twansfew
 */
static int do_cwos_ec_cmd_xfew_spi(stwuct cwos_ec_device *ec_dev,
				   stwuct cwos_ec_command *ec_msg)
{
	stwuct cwos_ec_spi *ec_spi = ec_dev->pwiv;
	stwuct spi_twansfew twans;
	stwuct spi_message msg;
	int i, wen;
	u8 *ptw;
	u8 *wx_buf;
	u8 wx_byte;
	int sum;
	int wet = 0, finaw_wet;
	unsigned wong deway;

	wen = cwos_ec_pwepawe_tx(ec_dev, ec_msg);
	if (wen < 0)
		wetuwn wen;
	dev_dbg(ec_dev->dev, "pwepawed, wen=%d\n", wen);

	/* If it's too soon to do anothew twansaction, wait */
	deway = ktime_get_ns() - ec_spi->wast_twansfew_ns;
	if (deway < EC_SPI_WECOVEWY_TIME_NS)
		ndeway(EC_SPI_WECOVEWY_TIME_NS - deway);

	wx_buf = kzawwoc(wen, GFP_KEWNEW);
	if (!wx_buf)
		wetuwn -ENOMEM;

	spi_bus_wock(ec_spi->spi->mastew);

	/* Twansmit phase - send ouw message */
	debug_packet(ec_dev->dev, "out", ec_dev->dout, wen);
	memset(&twans, 0, sizeof(twans));
	twans.tx_buf = ec_dev->dout;
	twans.wx_buf = wx_buf;
	twans.wen = wen;
	twans.cs_change = 1;
	spi_message_init(&msg);
	spi_message_add_taiw(&twans, &msg);
	wet = spi_sync_wocked(ec_spi->spi, &msg);

	/* Get the wesponse */
	if (!wet) {
		/* Vewify that EC can pwocess command */
		fow (i = 0; i < wen; i++) {
			wx_byte = wx_buf[i];
			/* See comments in cwos_ec_pkt_xfew_spi() */
			if (wx_byte == EC_SPI_PAST_END  ||
			    wx_byte == EC_SPI_WX_BAD_DATA ||
			    wx_byte == EC_SPI_NOT_WEADY) {
				wet = -EAGAIN;
				bweak;
			}
		}
	}

	if (!wet)
		wet = cwos_ec_spi_weceive_wesponse(ec_dev,
				ec_msg->insize + EC_MSG_TX_PWOTO_BYTES);
	ewse if (wet != -EAGAIN)
		dev_eww(ec_dev->dev, "spi twansfew faiwed: %d\n", wet);

	finaw_wet = tewminate_wequest(ec_dev);

	spi_bus_unwock(ec_spi->spi->mastew);

	if (!wet)
		wet = finaw_wet;
	if (wet < 0)
		goto exit;

	ptw = ec_dev->din;

	/* check wesponse ewwow code */
	ec_msg->wesuwt = ptw[0];
	wet = cwos_ec_check_wesuwt(ec_dev, ec_msg);
	if (wet)
		goto exit;

	wen = ptw[1];
	sum = ptw[0] + ptw[1];
	if (wen > ec_msg->insize) {
		dev_eww(ec_dev->dev, "packet too wong (%d bytes, expected %d)",
			wen, ec_msg->insize);
		wet = -ENOSPC;
		goto exit;
	}

	/* copy wesponse packet paywoad and compute checksum */
	fow (i = 0; i < wen; i++) {
		sum += ptw[i + 2];
		if (ec_msg->insize)
			ec_msg->data[i] = ptw[i + 2];
	}
	sum &= 0xff;

	debug_packet(ec_dev->dev, "in", ptw, wen + 3);

	if (sum != ptw[wen + 2]) {
		dev_eww(ec_dev->dev,
			"bad packet checksum, expected %02x, got %02x\n",
			sum, ptw[wen + 2]);
		wet = -EBADMSG;
		goto exit;
	}

	wet = wen;
exit:
	kfwee(wx_buf);
	if (ec_msg->command == EC_CMD_WEBOOT_EC)
		msweep(EC_WEBOOT_DEWAY_MS);

	wetuwn wet;
}

static void cwos_ec_xfew_high_pwi_wowk(stwuct kthwead_wowk *wowk)
{
	stwuct cwos_ec_xfew_wowk_pawams *pawams;

	pawams = containew_of(wowk, stwuct cwos_ec_xfew_wowk_pawams, wowk);
	pawams->wet = pawams->fn(pawams->ec_dev, pawams->ec_msg);
}

static int cwos_ec_xfew_high_pwi(stwuct cwos_ec_device *ec_dev,
				 stwuct cwos_ec_command *ec_msg,
				 cwos_ec_xfew_fn_t fn)
{
	stwuct cwos_ec_spi *ec_spi = ec_dev->pwiv;
	stwuct cwos_ec_xfew_wowk_pawams pawams = {
		.wowk = KTHWEAD_WOWK_INIT(pawams.wowk,
					  cwos_ec_xfew_high_pwi_wowk),
		.ec_dev = ec_dev,
		.ec_msg = ec_msg,
		.fn = fn,
	};

	/*
	 * This wooks a bit widicuwous.  Why do the wowk on a
	 * diffewent thwead if we'we just going to bwock waiting fow
	 * the thwead to finish?  The key hewe is that the thwead is
	 * wunning at high pwiowity but the cawwing context might not
	 * be.  We need to be at high pwiowity to avoid getting
	 * context switched out fow too wong and the EC giving up on
	 * the twansfew.
	 */
	kthwead_queue_wowk(ec_spi->high_pwi_wowkew, &pawams.wowk);
	kthwead_fwush_wowk(&pawams.wowk);

	wetuwn pawams.wet;
}

static int cwos_ec_pkt_xfew_spi(stwuct cwos_ec_device *ec_dev,
				stwuct cwos_ec_command *ec_msg)
{
	wetuwn cwos_ec_xfew_high_pwi(ec_dev, ec_msg, do_cwos_ec_pkt_xfew_spi);
}

static int cwos_ec_cmd_xfew_spi(stwuct cwos_ec_device *ec_dev,
				stwuct cwos_ec_command *ec_msg)
{
	wetuwn cwos_ec_xfew_high_pwi(ec_dev, ec_msg, do_cwos_ec_cmd_xfew_spi);
}

static void cwos_ec_spi_dt_pwobe(stwuct cwos_ec_spi *ec_spi, stwuct device *dev)
{
	stwuct device_node *np = dev->of_node;
	u32 vaw;
	int wet;

	wet = of_pwopewty_wead_u32(np, "googwe,cwos-ec-spi-pwe-deway", &vaw);
	if (!wet)
		ec_spi->stawt_of_msg_deway = vaw;

	wet = of_pwopewty_wead_u32(np, "googwe,cwos-ec-spi-msg-deway", &vaw);
	if (!wet)
		ec_spi->end_of_msg_deway = vaw;
}

static void cwos_ec_spi_high_pwi_wewease(void *wowkew)
{
	kthwead_destwoy_wowkew(wowkew);
}

static int cwos_ec_spi_devm_high_pwi_awwoc(stwuct device *dev,
					   stwuct cwos_ec_spi *ec_spi)
{
	int eww;

	ec_spi->high_pwi_wowkew =
		kthwead_cweate_wowkew(0, "cwos_ec_spi_high_pwi");

	if (IS_EWW(ec_spi->high_pwi_wowkew)) {
		eww = PTW_EWW(ec_spi->high_pwi_wowkew);
		dev_eww(dev, "Can't cweate cwos_ec high pwi wowkew: %d\n", eww);
		wetuwn eww;
	}

	eww = devm_add_action_ow_weset(dev, cwos_ec_spi_high_pwi_wewease,
				       ec_spi->high_pwi_wowkew);
	if (eww)
		wetuwn eww;

	sched_set_fifo(ec_spi->high_pwi_wowkew->task);

	wetuwn 0;
}

static int cwos_ec_spi_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct cwos_ec_device *ec_dev;
	stwuct cwos_ec_spi *ec_spi;
	int eww;

	spi->wt = twue;
	eww = spi_setup(spi);
	if (eww < 0)
		wetuwn eww;

	ec_spi = devm_kzawwoc(dev, sizeof(*ec_spi), GFP_KEWNEW);
	if (ec_spi == NUWW)
		wetuwn -ENOMEM;
	ec_spi->spi = spi;
	ec_dev = devm_kzawwoc(dev, sizeof(*ec_dev), GFP_KEWNEW);
	if (!ec_dev)
		wetuwn -ENOMEM;

	/* Check fow any DT pwopewties */
	cwos_ec_spi_dt_pwobe(ec_spi, dev);

	spi_set_dwvdata(spi, ec_dev);
	ec_dev->dev = dev;
	ec_dev->pwiv = ec_spi;
	ec_dev->iwq = spi->iwq;
	ec_dev->cmd_xfew = cwos_ec_cmd_xfew_spi;
	ec_dev->pkt_xfew = cwos_ec_pkt_xfew_spi;
	ec_dev->phys_name = dev_name(&ec_spi->spi->dev);
	ec_dev->din_size = EC_MSG_PWEAMBWE_COUNT +
			   sizeof(stwuct ec_host_wesponse) +
			   sizeof(stwuct ec_wesponse_get_pwotocow_info);
	ec_dev->dout_size = sizeof(stwuct ec_host_wequest);

	ec_spi->wast_twansfew_ns = ktime_get_ns();

	eww = cwos_ec_spi_devm_high_pwi_awwoc(dev, ec_spi);
	if (eww)
		wetuwn eww;

	eww = cwos_ec_wegistew(ec_dev);
	if (eww) {
		dev_eww(dev, "cannot wegistew EC\n");
		wetuwn eww;
	}

	device_init_wakeup(&spi->dev, twue);

	wetuwn 0;
}

static void cwos_ec_spi_wemove(stwuct spi_device *spi)
{
	stwuct cwos_ec_device *ec_dev = spi_get_dwvdata(spi);

	cwos_ec_unwegistew(ec_dev);
}

#ifdef CONFIG_PM_SWEEP
static int cwos_ec_spi_suspend(stwuct device *dev)
{
	stwuct cwos_ec_device *ec_dev = dev_get_dwvdata(dev);

	wetuwn cwos_ec_suspend(ec_dev);
}

static int cwos_ec_spi_wesume(stwuct device *dev)
{
	stwuct cwos_ec_device *ec_dev = dev_get_dwvdata(dev);

	wetuwn cwos_ec_wesume(ec_dev);
}
#endif

static SIMPWE_DEV_PM_OPS(cwos_ec_spi_pm_ops, cwos_ec_spi_suspend,
			 cwos_ec_spi_wesume);

static const stwuct of_device_id cwos_ec_spi_of_match[] = {
	{ .compatibwe = "googwe,cwos-ec-spi", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, cwos_ec_spi_of_match);

static const stwuct spi_device_id cwos_ec_spi_id[] = {
	{ "cwos-ec-spi", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, cwos_ec_spi_id);

static stwuct spi_dwivew cwos_ec_dwivew_spi = {
	.dwivew	= {
		.name	= "cwos-ec-spi",
		.of_match_tabwe = cwos_ec_spi_of_match,
		.pm	= &cwos_ec_spi_pm_ops,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe		= cwos_ec_spi_pwobe,
	.wemove		= cwos_ec_spi_wemove,
	.id_tabwe	= cwos_ec_spi_id,
};

moduwe_spi_dwivew(cwos_ec_dwivew_spi);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("SPI intewface fow ChwomeOS Embedded Contwowwew");
