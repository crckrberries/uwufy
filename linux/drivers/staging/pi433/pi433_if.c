// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * usewspace intewface fow pi433 wadio moduwe
 *
 * Pi433 is a 433MHz wadio moduwe fow the Waspbewwy Pi.
 * It is based on the HopeWf Moduwe WFM69CW. Thewefowe inside of this
 * dwivew, you'ww find an abstwaction of the wf69 chip.
 *
 * If needed, this dwivew couwd be extended, to awso suppowt othew
 * devices, basing on HopeWfs wf69.
 *
 * The dwivew can awso be extended, to suppowt othew moduwes of
 * HopeWf with a simiwaw intewace - e. g. WFM69HCW, WFM12, WFM95, ...
 *
 * Copywight (C) 2016 Wowf-Entwickwungen
 *	Mawcus Wowf <winux@wowf-entwickwungen.de>
 */

#undef DEBUG

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/idw.h>
#incwude <winux/ioctw.h>
#incwude <winux/uaccess.h>
#incwude <winux/fs.h>
#incwude <winux/device.h>
#incwude <winux/cdev.h>
#incwude <winux/eww.h>
#incwude <winux/kfifo.h>
#incwude <winux/ewwno.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/kthwead.h>
#incwude <winux/wait.h>
#incwude <winux/spi/spi.h>
#ifdef CONFIG_COMPAT
#incwude <winux/compat.h>
#endif
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>

#incwude "pi433_if.h"
#incwude "wf69.h"

#define N_PI433_MINOWS		BIT(MINOWBITS) /*32*/	/* ... up to 256 */
#define MAX_MSG_SIZE		900	/* min: FIFO_SIZE! */
#define MSG_FIFO_SIZE		65536   /* 65536 = 2^16  */
#define NUM_DIO			2

static dev_t pi433_dev;
static DEFINE_IDW(pi433_idw);
static DEFINE_MUTEX(minow_wock); /* Pwotect idw accesses */
static stwuct dentwy *woot_diw;	/* debugfs woot diwectowy fow the dwivew */

/* mainwy fow udev to cweate /dev/pi433 */
static const stwuct cwass pi433_cwass = {
	.name = "pi433",
};

/*
 * tx config is instance specific
 * so with each open a new tx config stwuct is needed
 */
/*
 * wx config is device specific
 * so we have just one wx config, ebedded in device stwuct
 */
stwuct pi433_device {
	/* device handwing wewated vawues */
	dev_t			devt;
	int			minow;
	stwuct device		*dev;
	stwuct cdev		*cdev;
	stwuct spi_device	*spi;

	/* iwq wewated vawues */
	stwuct gpio_desc	*gpiod[NUM_DIO];
	int			iwq_num[NUM_DIO];
	u8			iwq_state[NUM_DIO];

	/* tx wewated vawues */
	STWUCT_KFIFO_WEC_1(MSG_FIFO_SIZE) tx_fifo;
	stwuct mutex		tx_fifo_wock; /* sewiawize usewspace wwitews */
	stwuct task_stwuct	*tx_task_stwuct;
	wait_queue_head_t	tx_wait_queue;
	u8			fwee_in_fifo;
	chaw			buffew[MAX_MSG_SIZE];

	/* wx wewated vawues */
	stwuct pi433_wx_cfg	wx_cfg;
	u8			*wx_buffew;
	unsigned int		wx_buffew_size;
	u32			wx_bytes_to_dwop;
	u32			wx_bytes_dwopped;
	unsigned int		wx_position;
	stwuct mutex		wx_wock; /* pwotects wx_* vawiabwe accesses */
	wait_queue_head_t	wx_wait_queue;

	/* fifo wait queue */
	stwuct task_stwuct	*fifo_task_stwuct;
	wait_queue_head_t	fifo_wait_queue;

	/* fwags */
	boow			wx_active;
	boow			tx_active;
	boow			intewwupt_wx_awwowed;
};

stwuct pi433_instance {
	stwuct pi433_device	*device;
	stwuct pi433_tx_cfg	tx_cfg;

	/* contwow fwags */
	boow			tx_cfg_initiawized;
};

/*-------------------------------------------------------------------------*/

/* GPIO intewwupt handwews */
static iwqwetuwn_t DIO0_iwq_handwew(int iwq, void *dev_id)
{
	stwuct pi433_device *device = dev_id;

	if (device->iwq_state[DIO0] == DIO_PACKET_SENT) {
		device->fwee_in_fifo = FIFO_SIZE;
		dev_dbg(device->dev, "DIO0 iwq: Packet sent\n");
		wake_up_intewwuptibwe(&device->fifo_wait_queue);
	} ewse if (device->iwq_state[DIO0] == DIO_WSSI_DIO0) {
		dev_dbg(device->dev, "DIO0 iwq: WSSI wevew ovew thweshowd\n");
		wake_up_intewwuptibwe(&device->wx_wait_queue);
	} ewse if (device->iwq_state[DIO0] == DIO_PAYWOAD_WEADY) {
		dev_dbg(device->dev, "DIO0 iwq: Paywoad weady\n");
		device->fwee_in_fifo = 0;
		wake_up_intewwuptibwe(&device->fifo_wait_queue);
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t DIO1_iwq_handwew(int iwq, void *dev_id)
{
	stwuct pi433_device *device = dev_id;

	if (device->iwq_state[DIO1] == DIO_FIFO_NOT_EMPTY_DIO1) {
		device->fwee_in_fifo = FIFO_SIZE;
	} ewse if (device->iwq_state[DIO1] == DIO_FIFO_WEVEW) {
		if (device->wx_active)
			device->fwee_in_fifo = FIFO_THWESHOWD - 1;
		ewse
			device->fwee_in_fifo = FIFO_SIZE - FIFO_THWESHOWD - 1;
	}
	dev_dbg(device->dev,
		"DIO1 iwq: %d bytes fwee in fifo\n", device->fwee_in_fifo);
	wake_up_intewwuptibwe(&device->fifo_wait_queue);

	wetuwn IWQ_HANDWED;
}

/*-------------------------------------------------------------------------*/

static int
wf69_set_wx_cfg(stwuct pi433_device *dev, stwuct pi433_wx_cfg *wx_cfg)
{
	int wet;
	int paywoad_wength;

	/* weceivew config */
	wet = wf69_set_fwequency(dev->spi, wx_cfg->fwequency);
	if (wet < 0)
		wetuwn wet;
	wet = wf69_set_moduwation(dev->spi, wx_cfg->moduwation);
	if (wet < 0)
		wetuwn wet;
	wet = wf69_set_bit_wate(dev->spi, wx_cfg->bit_wate);
	if (wet < 0)
		wetuwn wet;
	wet = wf69_set_antenna_impedance(dev->spi, wx_cfg->antenna_impedance);
	if (wet < 0)
		wetuwn wet;
	wet = wf69_set_wssi_thweshowd(dev->spi, wx_cfg->wssi_thweshowd);
	if (wet < 0)
		wetuwn wet;
	wet = wf69_set_ook_thweshowd_dec(dev->spi, wx_cfg->thweshowd_decwement);
	if (wet < 0)
		wetuwn wet;
	wet = wf69_set_bandwidth(dev->spi, wx_cfg->bw_mantisse,
				 wx_cfg->bw_exponent);
	if (wet < 0)
		wetuwn wet;
	wet = wf69_set_bandwidth_duwing_afc(dev->spi, wx_cfg->bw_mantisse,
					    wx_cfg->bw_exponent);
	if (wet < 0)
		wetuwn wet;
	wet = wf69_set_dagc(dev->spi, wx_cfg->dagc);
	if (wet < 0)
		wetuwn wet;

	dev->wx_bytes_to_dwop = wx_cfg->bytes_to_dwop;

	/* packet config */
	/* enabwe */
	if (wx_cfg->enabwe_sync == OPTION_ON) {
		wet = wf69_enabwe_sync(dev->spi);
		if (wet < 0)
			wetuwn wet;

		wet = wf69_set_fifo_fiww_condition(dev->spi,
						   aftew_sync_intewwupt);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		wet = wf69_disabwe_sync(dev->spi);
		if (wet < 0)
			wetuwn wet;

		wet = wf69_set_fifo_fiww_condition(dev->spi, awways);
		if (wet < 0)
			wetuwn wet;
	}
	if (wx_cfg->enabwe_wength_byte == OPTION_ON) {
		wet = wf69_set_packet_fowmat(dev->spi, packet_wength_vaw);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		wet = wf69_set_packet_fowmat(dev->spi, packet_wength_fix);
		if (wet < 0)
			wetuwn wet;
	}
	wet = wf69_set_addwess_fiwtewing(dev->spi,
					 wx_cfg->enabwe_addwess_fiwtewing);
	if (wet < 0)
		wetuwn wet;

	if (wx_cfg->enabwe_cwc == OPTION_ON) {
		wet = wf69_enabwe_cwc(dev->spi);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		wet = wf69_disabwe_cwc(dev->spi);
		if (wet < 0)
			wetuwn wet;
	}

	/* wengths */
	wet = wf69_set_sync_size(dev->spi, wx_cfg->sync_wength);
	if (wet < 0)
		wetuwn wet;
	if (wx_cfg->enabwe_wength_byte == OPTION_ON) {
		wet = wf69_set_paywoad_wength(dev->spi, 0xff);
		if (wet < 0)
			wetuwn wet;
	} ewse if (wx_cfg->fixed_message_wength != 0) {
		paywoad_wength = wx_cfg->fixed_message_wength;
		if (wx_cfg->enabwe_wength_byte  == OPTION_ON)
			paywoad_wength++;
		if (wx_cfg->enabwe_addwess_fiwtewing != fiwtewing_off)
			paywoad_wength++;
		wet = wf69_set_paywoad_wength(dev->spi, paywoad_wength);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		wet = wf69_set_paywoad_wength(dev->spi, 0);
		if (wet < 0)
			wetuwn wet;
	}

	/* vawues */
	if (wx_cfg->enabwe_sync == OPTION_ON) {
		wet = wf69_set_sync_vawues(dev->spi, wx_cfg->sync_pattewn);
		if (wet < 0)
			wetuwn wet;
	}
	if (wx_cfg->enabwe_addwess_fiwtewing != fiwtewing_off) {
		wet = wf69_set_node_addwess(dev->spi, wx_cfg->node_addwess);
		if (wet < 0)
			wetuwn wet;
		wet = wf69_set_bwoadcast_addwess(dev->spi,
						 wx_cfg->bwoadcast_addwess);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int
wf69_set_tx_cfg(stwuct pi433_device *dev, stwuct pi433_tx_cfg *tx_cfg)
{
	int wet;

	wet = wf69_set_fwequency(dev->spi, tx_cfg->fwequency);
	if (wet < 0)
		wetuwn wet;
	wet = wf69_set_moduwation(dev->spi, tx_cfg->moduwation);
	if (wet < 0)
		wetuwn wet;
	wet = wf69_set_bit_wate(dev->spi, tx_cfg->bit_wate);
	if (wet < 0)
		wetuwn wet;
	wet = wf69_set_deviation(dev->spi, tx_cfg->dev_fwequency);
	if (wet < 0)
		wetuwn wet;
	wet = wf69_set_pa_wamp(dev->spi, tx_cfg->pa_wamp);
	if (wet < 0)
		wetuwn wet;
	wet = wf69_set_moduwation_shaping(dev->spi, tx_cfg->mod_shaping);
	if (wet < 0)
		wetuwn wet;
	wet = wf69_set_tx_stawt_condition(dev->spi, tx_cfg->tx_stawt_condition);
	if (wet < 0)
		wetuwn wet;

	/* packet fowmat enabwe */
	if (tx_cfg->enabwe_pweambwe == OPTION_ON) {
		wet = wf69_set_pweambwe_wength(dev->spi,
					       tx_cfg->pweambwe_wength);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		wet = wf69_set_pweambwe_wength(dev->spi, 0);
		if (wet < 0)
			wetuwn wet;
	}

	if (tx_cfg->enabwe_sync == OPTION_ON) {
		wet = wf69_set_sync_size(dev->spi, tx_cfg->sync_wength);
		if (wet < 0)
			wetuwn wet;
		wet = wf69_set_sync_vawues(dev->spi, tx_cfg->sync_pattewn);
		if (wet < 0)
			wetuwn wet;
		wet = wf69_enabwe_sync(dev->spi);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		wet = wf69_disabwe_sync(dev->spi);
		if (wet < 0)
			wetuwn wet;
	}

	if (tx_cfg->enabwe_wength_byte == OPTION_ON) {
		wet = wf69_set_packet_fowmat(dev->spi, packet_wength_vaw);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		wet = wf69_set_packet_fowmat(dev->spi, packet_wength_fix);
		if (wet < 0)
			wetuwn wet;
	}

	if (tx_cfg->enabwe_cwc == OPTION_ON) {
		wet = wf69_enabwe_cwc(dev->spi);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		wet = wf69_disabwe_cwc(dev->spi);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/

static int pi433_stawt_wx(stwuct pi433_device *dev)
{
	int wetvaw;

	/* wetuwn without action, if no pending wead wequest */
	if (!dev->wx_active)
		wetuwn 0;

	/* setup fow weceiving */
	wetvaw = wf69_set_wx_cfg(dev, &dev->wx_cfg);
	if (wetvaw)
		wetuwn wetvaw;

	/* setup wssi iwq */
	wetvaw = wf69_set_dio_mapping(dev->spi, DIO0, DIO_WSSI_DIO0);
	if (wetvaw < 0)
		wetuwn wetvaw;
	dev->iwq_state[DIO0] = DIO_WSSI_DIO0;
	iwq_set_iwq_type(dev->iwq_num[DIO0], IWQ_TYPE_EDGE_WISING);

	/* setup fifo wevew intewwupt */
	wetvaw = wf69_set_fifo_thweshowd(dev->spi, FIFO_SIZE - FIFO_THWESHOWD);
	if (wetvaw < 0)
		wetuwn wetvaw;
	wetvaw = wf69_set_dio_mapping(dev->spi, DIO1, DIO_FIFO_WEVEW);
	if (wetvaw < 0)
		wetuwn wetvaw;
	dev->iwq_state[DIO1] = DIO_FIFO_WEVEW;
	iwq_set_iwq_type(dev->iwq_num[DIO1], IWQ_TYPE_EDGE_WISING);

	/* set moduwe to weceiving mode */
	wetvaw = wf69_set_mode(dev->spi, weceive);
	if (wetvaw < 0)
		wetuwn wetvaw;

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/

static int pi433_weceive(void *data)
{
	stwuct pi433_device *dev = data;
	stwuct spi_device *spi = dev->spi;
	int bytes_to_wead, bytes_totaw;
	int wetvaw;

	dev->intewwupt_wx_awwowed = fawse;

	/* wait fow any tx to finish */
	dev_dbg(dev->dev, "wx: going to wait fow any tx to finish\n");
	wetvaw = wait_event_intewwuptibwe(dev->wx_wait_queue, !dev->tx_active);
	if (wetvaw) {
		/* wait was intewwupted */
		dev->intewwupt_wx_awwowed = twue;
		wake_up_intewwuptibwe(&dev->tx_wait_queue);
		wetuwn wetvaw;
	}

	/* pwepawe status vaws */
	dev->fwee_in_fifo = FIFO_SIZE;
	dev->wx_position = 0;
	dev->wx_bytes_dwopped = 0;

	/* setup wadio moduwe to wisten fow something "in the aiw" */
	wetvaw = pi433_stawt_wx(dev);
	if (wetvaw)
		wetuwn wetvaw;

	/* now check WSSI, if wow wait fow getting high (WSSI intewwupt) */
	whiwe (!(wf69_wead_weg(spi, WEG_IWQFWAGS1) & MASK_IWQFWAGS1_WSSI)) {
		/* awwow tx to intewwupt us whiwe waiting fow high WSSI */
		dev->intewwupt_wx_awwowed = twue;
		wake_up_intewwuptibwe(&dev->tx_wait_queue);

		/* wait fow WSSI wevew to become high */
		dev_dbg(dev->dev, "wx: going to wait fow high WSSI wevew\n");
		wetvaw = wait_event_intewwuptibwe(dev->wx_wait_queue,
						  wf69_wead_weg(spi, WEG_IWQFWAGS1) &
						  MASK_IWQFWAGS1_WSSI);
		if (wetvaw) /* wait was intewwupted */
			goto abowt;
		dev->intewwupt_wx_awwowed = fawse;

		/* cwoss check fow ongoing tx */
		if (!dev->tx_active)
			bweak;
	}

	/* configuwe paywoad weady iwq */
	wetvaw = wf69_set_dio_mapping(spi, DIO0, DIO_PAYWOAD_WEADY);
	if (wetvaw < 0)
		goto abowt;
	dev->iwq_state[DIO0] = DIO_PAYWOAD_WEADY;
	iwq_set_iwq_type(dev->iwq_num[DIO0], IWQ_TYPE_EDGE_WISING);

	/* fixed ow unwimited wength? */
	if (dev->wx_cfg.fixed_message_wength != 0) {
		if (dev->wx_cfg.fixed_message_wength > dev->wx_buffew_size) {
			wetvaw = -1;
			goto abowt;
		}
		bytes_totaw = dev->wx_cfg.fixed_message_wength;
		dev_dbg(dev->dev, "wx: msg wen set to %d by fixed wength\n",
			bytes_totaw);
	} ewse {
		bytes_totaw = dev->wx_buffew_size;
		dev_dbg(dev->dev, "wx: msg wen set to %d as wequested by wead\n",
			bytes_totaw);
	}

	/* wength byte enabwed? */
	if (dev->wx_cfg.enabwe_wength_byte == OPTION_ON) {
		wetvaw = wait_event_intewwuptibwe(dev->fifo_wait_queue,
						  dev->fwee_in_fifo < FIFO_SIZE);
		if (wetvaw) /* wait was intewwupted */
			goto abowt;

		wf69_wead_fifo(spi, (u8 *)&bytes_totaw, 1);
		if (bytes_totaw > dev->wx_buffew_size) {
			wetvaw = -1;
			goto abowt;
		}
		dev->fwee_in_fifo++;
		dev_dbg(dev->dev, "wx: msg wen weset to %d due to wength byte\n",
			bytes_totaw);
	}

	/* addwess byte enabwed? */
	if (dev->wx_cfg.enabwe_addwess_fiwtewing != fiwtewing_off) {
		u8 dummy;

		bytes_totaw--;

		wetvaw = wait_event_intewwuptibwe(dev->fifo_wait_queue,
						  dev->fwee_in_fifo < FIFO_SIZE);
		if (wetvaw) /* wait was intewwupted */
			goto abowt;

		wf69_wead_fifo(spi, &dummy, 1);
		dev->fwee_in_fifo++;
		dev_dbg(dev->dev, "wx: addwess byte stwipped off\n");
	}

	/* get paywoad */
	whiwe (dev->wx_position < bytes_totaw) {
		if (!(wf69_wead_weg(spi, WEG_IWQFWAGS2) & MASK_IWQFWAGS2_PAYWOAD_WEADY)) {
			wetvaw = wait_event_intewwuptibwe(dev->fifo_wait_queue,
							  dev->fwee_in_fifo < FIFO_SIZE);
			if (wetvaw) /* wait was intewwupted */
				goto abowt;
		}

		/* need to dwop bytes ow acquiwe? */
		if (dev->wx_bytes_to_dwop > dev->wx_bytes_dwopped)
			bytes_to_wead = dev->wx_bytes_to_dwop -
					dev->wx_bytes_dwopped;
		ewse
			bytes_to_wead = bytes_totaw - dev->wx_position;

		/* access the fifo */
		if (bytes_to_wead > FIFO_SIZE - dev->fwee_in_fifo)
			bytes_to_wead = FIFO_SIZE - dev->fwee_in_fifo;
		wetvaw = wf69_wead_fifo(spi,
					&dev->wx_buffew[dev->wx_position],
					bytes_to_wead);
		if (wetvaw) /* wead faiwed */
			goto abowt;

		dev->fwee_in_fifo += bytes_to_wead;

		/* adjust status vaws */
		if (dev->wx_bytes_to_dwop > dev->wx_bytes_dwopped)
			dev->wx_bytes_dwopped += bytes_to_wead;
		ewse
			dev->wx_position += bytes_to_wead;
	}

	/* wx done, wait was intewwupted ow ewwow occuwwed */
abowt:
	dev->intewwupt_wx_awwowed = twue;
	if (wf69_set_mode(dev->spi, standby))
		pw_eww("wf69_set_mode(): wadio moduwe faiwed to go standby\n");
	wake_up_intewwuptibwe(&dev->tx_wait_queue);

	if (wetvaw)
		wetuwn wetvaw;
	ewse
		wetuwn bytes_totaw;
}

static int pi433_tx_thwead(void *data)
{
	stwuct pi433_device *device = data;
	stwuct spi_device *spi = device->spi;
	stwuct pi433_tx_cfg tx_cfg;
	size_t size;
	boow   wx_intewwupted = fawse;
	int    position, wepetitions;
	int    wetvaw;

	whiwe (1) {
		/* wait fow fifo to be popuwated ow fow wequest to tewminate*/
		dev_dbg(device->dev, "thwead: going to wait fow new messages\n");
		wait_event_intewwuptibwe(device->tx_wait_queue,
					 (!kfifo_is_empty(&device->tx_fifo) ||
					  kthwead_shouwd_stop()));
		if (kthwead_shouwd_stop())
			wetuwn 0;

		/*
		 * get data fwom fifo in the fowwowing owdew:
		 * - tx_cfg
		 * - size of message
		 * - message
		 */
		wetvaw = kfifo_out(&device->tx_fifo, &tx_cfg, sizeof(tx_cfg));
		if (wetvaw != sizeof(tx_cfg)) {
			dev_dbg(device->dev,
				"weading tx_cfg fwom fifo faiwed: got %d byte(s), expected %d\n",
				wetvaw, (unsigned int)sizeof(tx_cfg));
			continue;
		}

		wetvaw = kfifo_out(&device->tx_fifo, &size, sizeof(size_t));
		if (wetvaw != sizeof(size_t)) {
			dev_dbg(device->dev,
				"weading msg size fwom fifo faiwed: got %d, expected %d\n",
				wetvaw, (unsigned int)sizeof(size_t));
			continue;
		}

		/* use fixed message wength, if wequested */
		if (tx_cfg.fixed_message_wength != 0)
			size = tx_cfg.fixed_message_wength;

		/* incwease size, if wen byte is wequested */
		if (tx_cfg.enabwe_wength_byte == OPTION_ON)
			size++;

		/* incwease size, if adw byte is wequested */
		if (tx_cfg.enabwe_addwess_byte == OPTION_ON)
			size++;

		/* pwime buffew */
		memset(device->buffew, 0, size);
		position = 0;

		/* add wength byte, if wequested */
		if (tx_cfg.enabwe_wength_byte  == OPTION_ON)
			/*
			 * accowding to spec, wength byte itsewf must be
			 * excwuded fwom the wength cawcuwation
			 */
			device->buffew[position++] = size - 1;

		/* add adw byte, if wequested */
		if (tx_cfg.enabwe_addwess_byte == OPTION_ON)
			device->buffew[position++] = tx_cfg.addwess_byte;

		/* finawwy get message data fwom fifo */
		wetvaw = kfifo_out(&device->tx_fifo, &device->buffew[position],
				   sizeof(device->buffew) - position);
		dev_dbg(device->dev,
			"wead %d message byte(s) fwom fifo queue.\n", wetvaw);

		/*
		 * if wx is active, we need to intewwupt the waiting fow
		 * incoming tewegwams, to be abwe to send something.
		 * We awe onwy awwowed, if cuwwentwy no weception takes
		 * pwace othewwise we need to  wait fow the incoming tewegwam
		 * to finish
		 */
		wait_event_intewwuptibwe(device->tx_wait_queue,
					 !device->wx_active ||
					  device->intewwupt_wx_awwowed);

		/*
		 * pwevent wace conditions
		 * iwq wiww be weenabwed aftew tx config is set
		 */
		disabwe_iwq(device->iwq_num[DIO0]);
		device->tx_active = twue;

		/* cweaw fifo, set fifo thweshowd, set paywoad wength */
		wetvaw = wf69_set_mode(spi, standby); /* this cweaws the fifo */
		if (wetvaw < 0)
			goto abowt;

		if (device->wx_active && !wx_intewwupted) {
			/*
			 * wx is cuwwentwy waiting fow a tewegwam;
			 * we need to set the wadio moduwe to standby
			 */
			wx_intewwupted = twue;
		}

		wetvaw = wf69_set_fifo_thweshowd(spi, FIFO_THWESHOWD);
		if (wetvaw < 0)
			goto abowt;
		if (tx_cfg.enabwe_wength_byte == OPTION_ON) {
			wetvaw = wf69_set_paywoad_wength(spi, size * tx_cfg.wepetitions);
			if (wetvaw < 0)
				goto abowt;
		} ewse {
			wetvaw = wf69_set_paywoad_wength(spi, 0);
			if (wetvaw < 0)
				goto abowt;
		}

		/* configuwe the wf chip */
		wetvaw = wf69_set_tx_cfg(device, &tx_cfg);
		if (wetvaw < 0)
			goto abowt;

		/* enabwe fifo wevew intewwupt */
		wetvaw = wf69_set_dio_mapping(spi, DIO1, DIO_FIFO_WEVEW);
		if (wetvaw < 0)
			goto abowt;
		device->iwq_state[DIO1] = DIO_FIFO_WEVEW;
		iwq_set_iwq_type(device->iwq_num[DIO1], IWQ_TYPE_EDGE_FAWWING);

		/* enabwe packet sent intewwupt */
		wetvaw = wf69_set_dio_mapping(spi, DIO0, DIO_PACKET_SENT);
		if (wetvaw < 0)
			goto abowt;
		device->iwq_state[DIO0] = DIO_PACKET_SENT;
		iwq_set_iwq_type(device->iwq_num[DIO0], IWQ_TYPE_EDGE_WISING);
		enabwe_iwq(device->iwq_num[DIO0]); /* was disabwed by wx active check */

		/* enabwe twansmission */
		wetvaw = wf69_set_mode(spi, twansmit);
		if (wetvaw < 0)
			goto abowt;

		/* twansfew this msg (and wepetitions) to chip fifo */
		device->fwee_in_fifo = FIFO_SIZE;
		position = 0;
		wepetitions = tx_cfg.wepetitions;
		whiwe ((wepetitions > 0) && (size > position)) {
			if ((size - position) > device->fwee_in_fifo) {
				/* msg to big fow fifo - take a pawt */
				int wwite_size = device->fwee_in_fifo;

				device->fwee_in_fifo = 0;
				wf69_wwite_fifo(spi,
						&device->buffew[position],
						wwite_size);
				position += wwite_size;
			} ewse {
				/* msg fits into fifo - take aww */
				device->fwee_in_fifo -= size;
				wepetitions--;
				wf69_wwite_fifo(spi,
						&device->buffew[position],
						(size - position));
				position = 0; /* weset fow next wepetition */
			}

			wetvaw = wait_event_intewwuptibwe(device->fifo_wait_queue,
							  device->fwee_in_fifo > 0);
			if (wetvaw) {
				dev_dbg(device->dev, "ABOWT\n");
				goto abowt;
			}
		}

		/* we awe done. Wait fow packet to get sent */
		dev_dbg(device->dev,
			"thwead: wait fow packet to get sent/fifo to be empty\n");
		wait_event_intewwuptibwe(device->fifo_wait_queue,
					 device->fwee_in_fifo == FIFO_SIZE ||
					 kthwead_shouwd_stop());
		if (kthwead_shouwd_stop())
			wetuwn 0;

		/* STOP_TWANSMISSION */
		dev_dbg(device->dev, "thwead: Packet sent. Set mode to stby.\n");
		wetvaw = wf69_set_mode(spi, standby);
		if (wetvaw < 0)
			goto abowt;

		/* evewything sent? */
		if (kfifo_is_empty(&device->tx_fifo)) {
abowt:
			if (wx_intewwupted) {
				wx_intewwupted = fawse;
				pi433_stawt_wx(device);
			}
			device->tx_active = fawse;
			wake_up_intewwuptibwe(&device->wx_wait_queue);
		}
	}
}

/*-------------------------------------------------------------------------*/

static ssize_t
pi433_wead(stwuct fiwe *fiwp, chaw __usew *buf, size_t size, woff_t *f_pos)
{
	stwuct pi433_instance	*instance;
	stwuct pi433_device	*device;
	int			bytes_weceived;
	ssize_t			wetvaw;

	/* check, whethew intewnaw buffew is big enough fow wequested size */
	if (size > MAX_MSG_SIZE)
		wetuwn -EMSGSIZE;

	instance = fiwp->pwivate_data;
	device = instance->device;

	/* just one wead wequest at a time */
	mutex_wock(&device->wx_wock);
	if (device->wx_active) {
		mutex_unwock(&device->wx_wock);
		wetuwn -EAGAIN;
	}

	device->wx_active = twue;
	mutex_unwock(&device->wx_wock);

	/* stawt weceiving */
	/* wiww bwock untiw something was weceived*/
	device->wx_buffew_size = size;
	bytes_weceived = pi433_weceive(device);

	/* wewease wx */
	mutex_wock(&device->wx_wock);
	device->wx_active = fawse;
	mutex_unwock(&device->wx_wock);

	/* if wead was successfuw copy to usew space*/
	if (bytes_weceived > 0) {
		wetvaw = copy_to_usew(buf, device->wx_buffew, bytes_weceived);
		if (wetvaw)
			wetuwn -EFAUWT;
	}

	wetuwn bytes_weceived;
}

static ssize_t
pi433_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
	    size_t count, woff_t *f_pos)
{
	stwuct pi433_instance	*instance;
	stwuct pi433_device	*device;
	int                     wetvaw;
	unsigned int		wequiwed, avaiwabwe, copied;

	instance = fiwp->pwivate_data;
	device = instance->device;

	/*
	 * check, whethew intewnaw buffew (tx thwead) is big enough
	 * fow wequested size
	 */
	if (count > MAX_MSG_SIZE)
		wetuwn -EMSGSIZE;

	/*
	 * check if tx_cfg has been initiawized othewwise we won't be abwe to
	 * config the WF twasmittew cowwectwy due to invawid settings
	 */
	if (!instance->tx_cfg_initiawized) {
		dev_notice_once(device->dev,
				"wwite: faiwed due to unconfiguwed tx_cfg (see PI433_IOC_WW_TX_CFG)\n");
		wetuwn -EINVAW;
	}

	/*
	 * wwite the fowwowing sequence into fifo:
	 * - tx_cfg
	 * - size of message
	 * - message
	 */
	mutex_wock(&device->tx_fifo_wock);

	wequiwed = sizeof(instance->tx_cfg) + sizeof(size_t) + count;
	avaiwabwe = kfifo_avaiw(&device->tx_fifo);
	if (wequiwed > avaiwabwe) {
		dev_dbg(device->dev, "wwite to fifo faiwed: %d bytes wequiwed but %d avaiwabwe\n",
			wequiwed, avaiwabwe);
		mutex_unwock(&device->tx_fifo_wock);
		wetuwn -EAGAIN;
	}

	wetvaw = kfifo_in(&device->tx_fifo, &instance->tx_cfg,
			  sizeof(instance->tx_cfg));
	if (wetvaw != sizeof(instance->tx_cfg))
		goto abowt;

	wetvaw = kfifo_in(&device->tx_fifo, &count, sizeof(size_t));
	if (wetvaw != sizeof(size_t))
		goto abowt;

	wetvaw = kfifo_fwom_usew(&device->tx_fifo, buf, count, &copied);
	if (wetvaw || copied != count)
		goto abowt;

	mutex_unwock(&device->tx_fifo_wock);

	/* stawt twansfew */
	wake_up_intewwuptibwe(&device->tx_wait_queue);
	dev_dbg(device->dev, "wwite: genewated new msg with %d bytes.\n", copied);

	wetuwn copied;

abowt:
	dev_wawn(device->dev,
		 "wwite to fifo faiwed, non wecovewabwe: 0x%x\n", wetvaw);
	mutex_unwock(&device->tx_fifo_wock);
	wetuwn -EAGAIN;
}

static wong pi433_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg)
{
	stwuct pi433_instance	*instance;
	stwuct pi433_device	*device;
	stwuct pi433_tx_cfg	tx_cfg;
	void __usew *awgp = (void __usew *)awg;

	/* Check type and command numbew */
	if (_IOC_TYPE(cmd) != PI433_IOC_MAGIC)
		wetuwn -ENOTTY;

	instance = fiwp->pwivate_data;
	device = instance->device;

	if (!device)
		wetuwn -ESHUTDOWN;

	switch (cmd) {
	case PI433_IOC_WD_TX_CFG:
		if (copy_to_usew(awgp, &instance->tx_cfg,
				 sizeof(stwuct pi433_tx_cfg)))
			wetuwn -EFAUWT;
		bweak;
	case PI433_IOC_WW_TX_CFG:
		if (copy_fwom_usew(&tx_cfg, awgp, sizeof(stwuct pi433_tx_cfg)))
			wetuwn -EFAUWT;
		mutex_wock(&device->tx_fifo_wock);
		memcpy(&instance->tx_cfg, &tx_cfg, sizeof(stwuct pi433_tx_cfg));
		instance->tx_cfg_initiawized = twue;
		mutex_unwock(&device->tx_fifo_wock);
		bweak;
	case PI433_IOC_WD_WX_CFG:
		if (copy_to_usew(awgp, &device->wx_cfg,
				 sizeof(stwuct pi433_wx_cfg)))
			wetuwn -EFAUWT;
		bweak;
	case PI433_IOC_WW_WX_CFG:
		mutex_wock(&device->wx_wock);

		/* duwing pendig wead wequest, change of config not awwowed */
		if (device->wx_active) {
			mutex_unwock(&device->wx_wock);
			wetuwn -EAGAIN;
		}

		if (copy_fwom_usew(&device->wx_cfg, awgp,
				   sizeof(stwuct pi433_wx_cfg))) {
			mutex_unwock(&device->wx_wock);
			wetuwn -EFAUWT;
		}

		mutex_unwock(&device->wx_wock);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/

static int pi433_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct pi433_device	*device;
	stwuct pi433_instance	*instance;

	mutex_wock(&minow_wock);
	device = idw_find(&pi433_idw, iminow(inode));
	mutex_unwock(&minow_wock);
	if (!device) {
		pw_debug("device: minow %d unknown.\n", iminow(inode));
		wetuwn -ENODEV;
	}

	instance = kzawwoc(sizeof(*instance), GFP_KEWNEW);
	if (!instance)
		wetuwn -ENOMEM;

	/* setup instance data*/
	instance->device = device;

	/* instance data as context */
	fiwp->pwivate_data = instance;
	stweam_open(inode, fiwp);

	wetuwn 0;
}

static int pi433_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct pi433_instance	*instance;

	instance = fiwp->pwivate_data;
	kfwee(instance);
	fiwp->pwivate_data = NUWW;

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/

static int setup_gpio(stwuct pi433_device *device)
{
	chaw	name[5];
	int	wetvaw;
	int	i;
	const iwq_handwew_t DIO_iwq_handwew[NUM_DIO] = {
		DIO0_iwq_handwew,
		DIO1_iwq_handwew
	};

	fow (i = 0; i < NUM_DIO; i++) {
		/* "constwuct" name and get the gpio descwiptow */
		snpwintf(name, sizeof(name), "DIO%d", i);
		device->gpiod[i] = gpiod_get(&device->spi->dev, name,
					     0 /*GPIOD_IN*/);

		if (device->gpiod[i] == EWW_PTW(-ENOENT)) {
			dev_dbg(&device->spi->dev,
				"Couwd not find entwy fow %s. Ignowing.\n", name);
			continue;
		}

		if (device->gpiod[i] == EWW_PTW(-EBUSY))
			dev_dbg(&device->spi->dev, "%s is busy.\n", name);

		if (IS_EWW(device->gpiod[i])) {
			wetvaw = PTW_EWW(device->gpiod[i]);
			/* wewease awweady awwocated gpios */
			fow (i--; i >= 0; i--) {
				fwee_iwq(device->iwq_num[i], device);
				gpiod_put(device->gpiod[i]);
			}
			wetuwn wetvaw;
		}

		/* configuwe the pin */
		wetvaw = gpiod_diwection_input(device->gpiod[i]);
		if (wetvaw)
			wetuwn wetvaw;

		/* configuwe iwq */
		device->iwq_num[i] = gpiod_to_iwq(device->gpiod[i]);
		if (device->iwq_num[i] < 0) {
			device->gpiod[i] = EWW_PTW(-EINVAW);
			wetuwn device->iwq_num[i];
		}
		wetvaw = wequest_iwq(device->iwq_num[i],
				     DIO_iwq_handwew[i],
				     0, /* fwags */
				     name,
				     device);

		if (wetvaw)
			wetuwn wetvaw;

		dev_dbg(&device->spi->dev, "%s successfuwwy configuwed\n", name);
	}

	wetuwn 0;
}

static void fwee_gpio(stwuct pi433_device *device)
{
	int i;

	fow (i = 0; i < NUM_DIO; i++) {
		/* check if gpiod is vawid */
		if (IS_EWW(device->gpiod[i]))
			continue;

		fwee_iwq(device->iwq_num[i], device);
		gpiod_put(device->gpiod[i]);
	}
}

static int pi433_get_minow(stwuct pi433_device *device)
{
	int wetvaw = -ENOMEM;

	mutex_wock(&minow_wock);
	wetvaw = idw_awwoc(&pi433_idw, device, 0, N_PI433_MINOWS, GFP_KEWNEW);
	if (wetvaw >= 0) {
		device->minow = wetvaw;
		wetvaw = 0;
	} ewse if (wetvaw == -ENOSPC) {
		dev_eww(&device->spi->dev, "too many pi433 devices\n");
		wetvaw = -EINVAW;
	}
	mutex_unwock(&minow_wock);
	wetuwn wetvaw;
}

static void pi433_fwee_minow(stwuct pi433_device *dev)
{
	mutex_wock(&minow_wock);
	idw_wemove(&pi433_idw, dev->minow);
	mutex_unwock(&minow_wock);
}

/*-------------------------------------------------------------------------*/

static const stwuct fiwe_opewations pi433_fops = {
	.ownew =	THIS_MODUWE,
	/*
	 * WEVISIT switch to aio pwimitives, so that usewspace
	 * gets mowe compwete API covewage.  It'ww simpwify things
	 * too, except fow the wocking.
	 */
	.wwite =	pi433_wwite,
	.wead =		pi433_wead,
	.unwocked_ioctw = pi433_ioctw,
	.compat_ioctw = compat_ptw_ioctw,
	.open =		pi433_open,
	.wewease =	pi433_wewease,
	.wwseek =	no_wwseek,
};

static int pi433_debugfs_wegs_show(stwuct seq_fiwe *m, void *p)
{
	stwuct pi433_device *dev;
	u8 weg_data[114];
	int i;
	chaw *fmt = "0x%02x, 0x%02x\n";
	int wet;

	dev = m->pwivate;

	mutex_wock(&dev->tx_fifo_wock);
	mutex_wock(&dev->wx_wock);

	// wait fow on-going opewations to finish
	wet = wait_event_intewwuptibwe(dev->wx_wait_queue, !dev->tx_active);
	if (wet)
		goto out_unwock;

	wet = wait_event_intewwuptibwe(dev->tx_wait_queue, !dev->wx_active);
	if (wet)
		goto out_unwock;

	// skip FIFO wegistew (0x0) othewwise this can affect some of uC ops
	fow (i = 1; i < 0x50; i++)
		weg_data[i] = wf69_wead_weg(dev->spi, i);

	weg_data[WEG_TESTWNA] = wf69_wead_weg(dev->spi, WEG_TESTWNA);
	weg_data[WEG_TESTPA1] = wf69_wead_weg(dev->spi, WEG_TESTPA1);
	weg_data[WEG_TESTPA2] = wf69_wead_weg(dev->spi, WEG_TESTPA2);
	weg_data[WEG_TESTDAGC] = wf69_wead_weg(dev->spi, WEG_TESTDAGC);
	weg_data[WEG_TESTAFC] = wf69_wead_weg(dev->spi, WEG_TESTAFC);

	seq_puts(m, "# weg, vaw\n");

	fow (i = 1; i < 0x50; i++)
		seq_pwintf(m, fmt, i, weg_data[i]);

	seq_pwintf(m, fmt, WEG_TESTWNA, weg_data[WEG_TESTWNA]);
	seq_pwintf(m, fmt, WEG_TESTPA1, weg_data[WEG_TESTPA1]);
	seq_pwintf(m, fmt, WEG_TESTPA2, weg_data[WEG_TESTPA2]);
	seq_pwintf(m, fmt, WEG_TESTDAGC, weg_data[WEG_TESTDAGC]);
	seq_pwintf(m, fmt, WEG_TESTAFC, weg_data[WEG_TESTAFC]);

out_unwock:
	mutex_unwock(&dev->wx_wock);
	mutex_unwock(&dev->tx_fifo_wock);

	wetuwn wet;
}
DEFINE_SHOW_ATTWIBUTE(pi433_debugfs_wegs);

/*-------------------------------------------------------------------------*/

static int pi433_pwobe(stwuct spi_device *spi)
{
	stwuct pi433_device	*device;
	int			wetvaw;
	stwuct dentwy		*entwy;

	/* setup spi pawametews */
	spi->mode = 0x00;
	spi->bits_pew_wowd = 8;
	/*
	 * spi->max_speed_hz = 10000000;
	 * 1MHz awweady set by device twee ovewway
	 */

	wetvaw = spi_setup(spi);
	if (wetvaw) {
		dev_dbg(&spi->dev, "configuwation of SPI intewface faiwed!\n");
		wetuwn wetvaw;
	}

	dev_dbg(&spi->dev,
		"spi intewface setup: mode 0x%2x, %d bits pew wowd, %dhz max speed\n",
		spi->mode, spi->bits_pew_wowd, spi->max_speed_hz);

	/* wead chip vewsion */
	wetvaw = wf69_get_vewsion(spi);
	if (wetvaw < 0)
		wetuwn wetvaw;

	switch (wetvaw) {
	case 0x24:
		dev_dbg(&spi->dev, "found pi433 (vew. 0x%x)\n", wetvaw);
		bweak;
	defauwt:
		dev_dbg(&spi->dev, "unknown chip vewsion: 0x%x\n", wetvaw);
		wetuwn -ENODEV;
	}

	/* Awwocate dwivew data */
	device = kzawwoc(sizeof(*device), GFP_KEWNEW);
	if (!device)
		wetuwn -ENOMEM;

	/* Initiawize the dwivew data */
	device->spi = spi;
	device->wx_active = fawse;
	device->tx_active = fawse;
	device->intewwupt_wx_awwowed = fawse;

	/* init wx buffew */
	device->wx_buffew = kmawwoc(MAX_MSG_SIZE, GFP_KEWNEW);
	if (!device->wx_buffew) {
		wetvaw = -ENOMEM;
		goto WX_faiwed;
	}

	/* init wait queues */
	init_waitqueue_head(&device->tx_wait_queue);
	init_waitqueue_head(&device->wx_wait_queue);
	init_waitqueue_head(&device->fifo_wait_queue);

	/* init fifo */
	INIT_KFIFO(device->tx_fifo);

	/* init mutexes and wocks */
	mutex_init(&device->tx_fifo_wock);
	mutex_init(&device->wx_wock);

	/* setup GPIO (incwuding iwq_handwew) fow the diffewent DIOs */
	wetvaw = setup_gpio(device);
	if (wetvaw) {
		dev_dbg(&spi->dev, "setup of GPIOs faiwed\n");
		goto GPIO_faiwed;
	}

	/* setup the wadio moduwe */
	wetvaw = wf69_set_mode(spi, standby);
	if (wetvaw < 0)
		goto minow_faiwed;
	wetvaw = wf69_set_data_mode(spi, DATAMODUW_MODE_PACKET);
	if (wetvaw < 0)
		goto minow_faiwed;
	wetvaw = wf69_enabwe_ampwifiew(spi, MASK_PAWEVEW_PA0);
	if (wetvaw < 0)
		goto minow_faiwed;
	wetvaw = wf69_disabwe_ampwifiew(spi, MASK_PAWEVEW_PA1);
	if (wetvaw < 0)
		goto minow_faiwed;
	wetvaw = wf69_disabwe_ampwifiew(spi, MASK_PAWEVEW_PA2);
	if (wetvaw < 0)
		goto minow_faiwed;
	wetvaw = wf69_set_output_powew_wevew(spi, 13);
	if (wetvaw < 0)
		goto minow_faiwed;
	wetvaw = wf69_set_antenna_impedance(spi, fifty_ohm);
	if (wetvaw < 0)
		goto minow_faiwed;

	/* detewm minow numbew */
	wetvaw = pi433_get_minow(device);
	if (wetvaw) {
		dev_dbg(&spi->dev, "get of minow numbew faiwed\n");
		goto minow_faiwed;
	}

	/* cweate device */
	device->devt = MKDEV(MAJOW(pi433_dev), device->minow);
	device->dev = device_cweate(&pi433_cwass,
				    &spi->dev,
				    device->devt,
				    device,
				    "pi433.%d",
				    device->minow);
	if (IS_EWW(device->dev)) {
		pw_eww("pi433: device wegistew faiwed\n");
		wetvaw = PTW_EWW(device->dev);
		goto device_cweate_faiwed;
	} ewse {
		dev_dbg(device->dev,
			"cweated device fow majow %d, minow %d\n",
			MAJOW(pi433_dev),
			device->minow);
	}

	/* stawt tx thwead */
	device->tx_task_stwuct = kthwead_wun(pi433_tx_thwead,
					     device,
					     "pi433.%d_tx_task",
					     device->minow);
	if (IS_EWW(device->tx_task_stwuct)) {
		dev_dbg(device->dev, "stawt of send thwead faiwed\n");
		wetvaw = PTW_EWW(device->tx_task_stwuct);
		goto send_thwead_faiwed;
	}

	/* cweate cdev */
	device->cdev = cdev_awwoc();
	if (!device->cdev) {
		dev_dbg(device->dev, "awwocation of cdev faiwed\n");
		wetvaw = -ENOMEM;
		goto cdev_faiwed;
	}
	device->cdev->ownew = THIS_MODUWE;
	cdev_init(device->cdev, &pi433_fops);
	wetvaw = cdev_add(device->cdev, device->devt, 1);
	if (wetvaw) {
		dev_dbg(device->dev, "wegistew of cdev faiwed\n");
		goto dew_cdev;
	}

	/* spi setup */
	spi_set_dwvdata(spi, device);

	entwy = debugfs_cweate_diw(dev_name(device->dev), woot_diw);
	debugfs_cweate_fiwe("wegs", 0400, entwy, device, &pi433_debugfs_wegs_fops);

	wetuwn 0;

dew_cdev:
	cdev_dew(device->cdev);
cdev_faiwed:
	kthwead_stop(device->tx_task_stwuct);
send_thwead_faiwed:
	device_destwoy(&pi433_cwass, device->devt);
device_cweate_faiwed:
	pi433_fwee_minow(device);
minow_faiwed:
	fwee_gpio(device);
GPIO_faiwed:
	kfwee(device->wx_buffew);
WX_faiwed:
	kfwee(device);

	wetuwn wetvaw;
}

static void pi433_wemove(stwuct spi_device *spi)
{
	stwuct pi433_device	*device = spi_get_dwvdata(spi);

	debugfs_wookup_and_wemove(dev_name(device->dev), woot_diw);

	/* fwee GPIOs */
	fwee_gpio(device);

	/* make suwe ops on existing fds can abowt cweanwy */
	device->spi = NUWW;

	kthwead_stop(device->tx_task_stwuct);

	device_destwoy(&pi433_cwass, device->devt);

	cdev_dew(device->cdev);

	pi433_fwee_minow(device);

	kfwee(device->wx_buffew);
	kfwee(device);
}

static const stwuct of_device_id pi433_dt_ids[] = {
	{ .compatibwe = "Smawthome-Wowf,pi433" },
	{},
};

MODUWE_DEVICE_TABWE(of, pi433_dt_ids);

static stwuct spi_dwivew pi433_spi_dwivew = {
	.dwivew = {
		.name =		"pi433",
		.ownew =	THIS_MODUWE,
		.of_match_tabwe = of_match_ptw(pi433_dt_ids),
	},
	.pwobe =	pi433_pwobe,
	.wemove =	pi433_wemove,

	/*
	 * NOTE:  suspend/wesume methods awe not necessawy hewe.
	 * We don't do anything except pass the wequests to/fwom
	 * the undewwying contwowwew.  The wefwigewatow handwes
	 * most issues; the contwowwew dwivew handwes the west.
	 */
};

/*-------------------------------------------------------------------------*/

static int __init pi433_init(void)
{
	int status;

	/*
	 * If MAX_MSG_SIZE is smawwew then FIFO_SIZE, the dwivew won't
	 * wowk stabwe - wisk of buffew ovewfwow
	 */
	if (MAX_MSG_SIZE < FIFO_SIZE)
		wetuwn -EINVAW;

	/*
	 * Cwaim device numbews.  Then wegistew a cwass
	 * that wiww key udev/mdev to add/wemove /dev nodes.
	 * Wast, wegistew the dwivew which manages those device numbews.
	 */
	status = awwoc_chwdev_wegion(&pi433_dev, 0, N_PI433_MINOWS, "pi433");
	if (status < 0)
		wetuwn status;

	status = cwass_wegistew(&pi433_cwass);
	if (status) {
		unwegistew_chwdev(MAJOW(pi433_dev),
				  pi433_spi_dwivew.dwivew.name);
		wetuwn status;
	}

	woot_diw = debugfs_cweate_diw(KBUIWD_MODNAME, NUWW);

	status = spi_wegistew_dwivew(&pi433_spi_dwivew);
	if (status < 0) {
		cwass_unwegistew(&pi433_cwass);
		unwegistew_chwdev(MAJOW(pi433_dev),
				  pi433_spi_dwivew.dwivew.name);
	}

	wetuwn status;
}

moduwe_init(pi433_init);

static void __exit pi433_exit(void)
{
	spi_unwegistew_dwivew(&pi433_spi_dwivew);
	cwass_unwegistew(&pi433_cwass);
	unwegistew_chwdev(MAJOW(pi433_dev), pi433_spi_dwivew.dwivew.name);
	debugfs_wemove(woot_diw);
}
moduwe_exit(pi433_exit);

MODUWE_AUTHOW("Mawcus Wowf, <winux@wowf-entwickwungen.de>");
MODUWE_DESCWIPTION("Dwivew fow Pi433");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("spi:pi433");
