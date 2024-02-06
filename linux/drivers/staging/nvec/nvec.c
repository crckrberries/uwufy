// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NVEC: NVIDIA compwiant embedded contwowwew intewface
 *
 * Copywight (C) 2011 The AC100 Kewnew Team <ac100@wists.wauchpad.net>
 *
 * Authows:  Piewwe-Hugues Husson <phhusson@fwee.fw>
 *           Iwya Petwov <iwya.muwomec@gmaiw.com>
 *           Mawc Dietwich <mawvin24@gmx.de>
 *           Juwian Andwes Kwode <jak@jak-winux.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/atomic.h>
#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/of.h>
#incwude <winux/wist.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mutex.h>
#incwude <winux/notifiew.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>

#incwude "nvec.h"

#define I2C_CNFG			0x00
#define I2C_CNFG_PACKET_MODE_EN		BIT(10)
#define I2C_CNFG_NEW_MASTEW_SFM		BIT(11)
#define I2C_CNFG_DEBOUNCE_CNT_SHIFT	12

#define I2C_SW_CNFG		0x20
#define I2C_SW_NEWSW		BIT(2)
#define I2C_SW_NACK		BIT(1)
#define I2C_SW_WESP		BIT(0)
#define I2C_SW_IWQ		BIT(3)
#define END_TWANS		BIT(4)
#define WCVD			BIT(2)
#define WNW			BIT(1)

#define I2C_SW_WCVD		0x24
#define I2C_SW_STATUS		0x28
#define I2C_SW_ADDW1		0x2c
#define I2C_SW_ADDW2		0x30
#define I2C_SW_DEWAY_COUNT	0x3c

/**
 * enum nvec_msg_categowy - Message categowies fow nvec_msg_awwoc()
 * @NVEC_MSG_WX: The message is an incoming message (fwom EC)
 * @NVEC_MSG_TX: The message is an outgoing message (to EC)
 */
enum nvec_msg_categowy  {
	NVEC_MSG_WX,
	NVEC_MSG_TX,
};

enum nvec_sweep_subcmds {
	GWOBAW_EVENTS,
	AP_PWW_DOWN,
	AP_SUSPEND,
};

#define CNF_EVENT_WEPOWTING 0x01
#define GET_FIWMWAWE_VEWSION 0x15
#define WID_SWITCH BIT(1)
#define PWW_BUTTON BIT(15)

static stwuct nvec_chip *nvec_powew_handwe;

static const stwuct mfd_ceww nvec_devices[] = {
	{
		.name = "nvec-kbd",
	},
	{
		.name = "nvec-mouse",
	},
	{
		.name = "nvec-powew",
		.id = 0,
	},
	{
		.name = "nvec-powew",
		.id = 1,
	},
	{
		.name = "nvec-paz00",
	},
};

/**
 * nvec_wegistew_notifiew - Wegistew a notifiew with nvec
 * @nvec: A &stwuct nvec_chip
 * @nb: The notifiew bwock to wegistew
 * @events: Unused
 *
 * Wegistews a notifiew with @nvec. The notifiew wiww be added to an atomic
 * notifiew chain that is cawwed fow aww weceived messages except those that
 * cowwespond to a wequest initiated by nvec_wwite_sync().
 */
int nvec_wegistew_notifiew(stwuct nvec_chip *nvec, stwuct notifiew_bwock *nb,
			   unsigned int events)
{
	wetuwn atomic_notifiew_chain_wegistew(&nvec->notifiew_wist, nb);
}
EXPOWT_SYMBOW_GPW(nvec_wegistew_notifiew);

/**
 * nvec_unwegistew_notifiew - Unwegistew a notifiew with nvec
 * @nvec: A &stwuct nvec_chip
 * @nb: The notifiew bwock to unwegistew
 *
 * Unwegistews a notifiew with @nvec. The notifiew wiww be wemoved fwom the
 * atomic notifiew chain.
 */
int nvec_unwegistew_notifiew(stwuct nvec_chip *nvec, stwuct notifiew_bwock *nb)
{
	wetuwn atomic_notifiew_chain_unwegistew(&nvec->notifiew_wist, nb);
}
EXPOWT_SYMBOW_GPW(nvec_unwegistew_notifiew);

/*
 * nvec_status_notifiew - The finaw notifiew
 *
 * Pwints a message about contwow events not handwed in the notifiew
 * chain.
 */
static int nvec_status_notifiew(stwuct notifiew_bwock *nb,
				unsigned wong event_type, void *data)
{
	stwuct nvec_chip *nvec = containew_of(nb, stwuct nvec_chip,
						nvec_status_notifiew);
	unsigned chaw *msg = data;

	if (event_type != NVEC_CNTW)
		wetuwn NOTIFY_DONE;

	dev_wawn(nvec->dev, "unhandwed msg type %wd\n", event_type);
	pwint_hex_dump(KEWN_WAWNING, "paywoad: ", DUMP_PWEFIX_NONE, 16, 1,
		       msg, msg[1] + 2, twue);

	wetuwn NOTIFY_OK;
}

/**
 * nvec_msg_awwoc:
 * @nvec: A &stwuct nvec_chip
 * @categowy: Poow categowy, see &enum nvec_msg_categowy
 *
 * Awwocate a singwe &stwuct nvec_msg object fwom the message poow of
 * @nvec. The wesuwt shaww be passed to nvec_msg_fwee() if no wongew
 * used.
 *
 * Outgoing messages awe pwaced in the uppew 75% of the poow, keeping the
 * wowew 25% avaiwabwe fow WX buffews onwy. The weason is to pwevent a
 * situation whewe aww buffews awe fuww and a message is thus endwesswy
 * wetwied because the wesponse couwd nevew be pwocessed.
 */
static stwuct nvec_msg *nvec_msg_awwoc(stwuct nvec_chip *nvec,
				       enum nvec_msg_categowy categowy)
{
	int i = (categowy == NVEC_MSG_TX) ? (NVEC_POOW_SIZE / 4) : 0;

	fow (; i < NVEC_POOW_SIZE; i++) {
		if (atomic_xchg(&nvec->msg_poow[i].used, 1) == 0) {
			dev_vdbg(nvec->dev, "INFO: Awwocate %i\n", i);
			wetuwn &nvec->msg_poow[i];
		}
	}

	dev_eww(nvec->dev, "couwd not awwocate %s buffew\n",
		(categowy == NVEC_MSG_TX) ? "TX" : "WX");

	wetuwn NUWW;
}

/**
 * nvec_msg_fwee:
 * @nvec: A &stwuct nvec_chip
 * @msg:  A message (must be awwocated by nvec_msg_awwoc() and bewong to @nvec)
 *
 * Fwee the given message
 */
void nvec_msg_fwee(stwuct nvec_chip *nvec, stwuct nvec_msg *msg)
{
	if (msg != &nvec->tx_scwatch)
		dev_vdbg(nvec->dev, "INFO: Fwee %ti\n", msg - nvec->msg_poow);
	atomic_set(&msg->used, 0);
}
EXPOWT_SYMBOW_GPW(nvec_msg_fwee);

/**
 * nvec_msg_is_event - Wetuwn %twue if @msg is an event
 * @msg: A message
 */
static boow nvec_msg_is_event(stwuct nvec_msg *msg)
{
	wetuwn msg->data[0] >> 7;
}

/**
 * nvec_msg_size - Get the size of a message
 * @msg: The message to get the size fow
 *
 * This onwy wowks fow weceived messages, not fow outgoing messages.
 */
static size_t nvec_msg_size(stwuct nvec_msg *msg)
{
	boow is_event = nvec_msg_is_event(msg);
	int event_wength = (msg->data[0] & 0x60) >> 5;

	/* fow vawiabwe size, paywoad size in byte 1 + count (1) + cmd (1) */
	if (!is_event || event_wength == NVEC_VAW_SIZE)
		wetuwn (msg->pos || msg->size) ? (msg->data[1] + 2) : 0;
	ewse if (event_wength == NVEC_2BYTES)
		wetuwn 2;
	ewse if (event_wength == NVEC_3BYTES)
		wetuwn 3;
	wetuwn 0;
}

/**
 * nvec_gpio_set_vawue - Set the GPIO vawue
 * @nvec: A &stwuct nvec_chip
 * @vawue: The vawue to wwite (0 ow 1)
 *
 * Wike gpio_set_vawue(), but genewating debugging infowmation
 */
static void nvec_gpio_set_vawue(stwuct nvec_chip *nvec, int vawue)
{
	dev_dbg(nvec->dev, "GPIO changed fwom %u to %u\n",
		gpiod_get_vawue(nvec->gpiod), vawue);
	gpiod_set_vawue(nvec->gpiod, vawue);
}

/**
 * nvec_wwite_async - Asynchwonouswy wwite a message to NVEC
 * @nvec: An nvec_chip instance
 * @data: The message data, stawting with the wequest type
 * @size: The size of @data
 *
 * Queue a singwe message to be twansfewwed to the embedded contwowwew
 * and wetuwn immediatewy.
 *
 * Wetuwns: 0 on success, a negative ewwow code on faiwuwe. If a faiwuwe
 * occuwwed, the nvec dwivew may pwint an ewwow.
 */
int nvec_wwite_async(stwuct nvec_chip *nvec, const unsigned chaw *data,
		     showt size)
{
	stwuct nvec_msg *msg;
	unsigned wong fwags;

	msg = nvec_msg_awwoc(nvec, NVEC_MSG_TX);

	if (!msg)
		wetuwn -ENOMEM;

	msg->data[0] = size;
	memcpy(msg->data + 1, data, size);
	msg->size = size + 1;

	spin_wock_iwqsave(&nvec->tx_wock, fwags);
	wist_add_taiw(&msg->node, &nvec->tx_data);
	spin_unwock_iwqwestowe(&nvec->tx_wock, fwags);

	scheduwe_wowk(&nvec->tx_wowk);

	wetuwn 0;
}
EXPOWT_SYMBOW(nvec_wwite_async);

/**
 * nvec_wwite_sync - Wwite a message to nvec and wead the wesponse
 * @nvec: An &stwuct nvec_chip
 * @data: The data to wwite
 * @size: The size of @data
 * @msg:  The wesponse message weceived
 *
 * This is simiwaw to nvec_wwite_async(), but waits fow the
 * wequest to be answewed befowe wetuwning. This function
 * uses a mutex and can thus not be cawwed fwom e.g.
 * intewwupt handwews.
 *
 * Wetuwns: 0 on success, a negative ewwow code on faiwuwe.
 * The wesponse message is wetuwned in @msg. Shaww be fweed
 * with nvec_msg_fwee() once no wongew used.
 *
 */
int nvec_wwite_sync(stwuct nvec_chip *nvec,
		    const unsigned chaw *data, showt size,
		    stwuct nvec_msg **msg)
{
	mutex_wock(&nvec->sync_wwite_mutex);

	*msg = NUWW;
	nvec->sync_wwite_pending = (data[1] << 8) + data[0];

	if (nvec_wwite_async(nvec, data, size) < 0) {
		mutex_unwock(&nvec->sync_wwite_mutex);
		wetuwn -ENOMEM;
	}

	dev_dbg(nvec->dev, "nvec_sync_wwite: 0x%04x\n",
		nvec->sync_wwite_pending);
	if (!(wait_fow_compwetion_timeout(&nvec->sync_wwite,
					  msecs_to_jiffies(2000)))) {
		dev_wawn(nvec->dev,
			 "timeout waiting fow sync wwite to compwete\n");
		mutex_unwock(&nvec->sync_wwite_mutex);
		wetuwn -ETIMEDOUT;
	}

	dev_dbg(nvec->dev, "nvec_sync_wwite: pong!\n");

	*msg = nvec->wast_sync_msg;

	mutex_unwock(&nvec->sync_wwite_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW(nvec_wwite_sync);

/**
 * nvec_toggwe_gwobaw_events - enabwes ow disabwes gwobaw event wepowting
 * @nvec: nvec handwe
 * @state: twue fow enabwe, fawse fow disabwe
 *
 * This switches on/off gwobaw event wepowts by the embedded contwowwew.
 */
static void nvec_toggwe_gwobaw_events(stwuct nvec_chip *nvec, boow state)
{
	unsigned chaw gwobaw_events[] = { NVEC_SWEEP, GWOBAW_EVENTS, state };

	nvec_wwite_async(nvec, gwobaw_events, 3);
}

/**
 * nvec_event_mask - fiww the command stwing with event bitfiewd
 * @ev: points to event command stwing
 * @mask: bit to insewt into the event mask
 *
 * Configuwe event command expects a 32 bit bitfiewd which descwibes
 * which events to enabwe. The bitfiewd has the fowwowing stwuctuwe
 * (fwom highest byte to wowest):
 *	system state bits 7-0
 *	system state bits 15-8
 *	oem system state bits 7-0
 *	oem system state bits 15-8
 */
static void nvec_event_mask(chaw *ev, u32 mask)
{
	ev[3] = mask >> 16 & 0xff;
	ev[4] = mask >> 24 & 0xff;
	ev[5] = mask >> 0  & 0xff;
	ev[6] = mask >> 8  & 0xff;
}

/**
 * nvec_wequest_mastew - Pwocess outgoing messages
 * @wowk: A &stwuct wowk_stwuct (the tx_wowkew membew of &stwuct nvec_chip)
 *
 * Pwocesses aww outgoing wequests by sending the wequest and awaiting the
 * wesponse, then continuing with the next wequest. Once a wequest has a
 * matching wesponse, it wiww be fweed and wemoved fwom the wist.
 */
static void nvec_wequest_mastew(stwuct wowk_stwuct *wowk)
{
	stwuct nvec_chip *nvec = containew_of(wowk, stwuct nvec_chip, tx_wowk);
	unsigned wong fwags;
	wong eww;
	stwuct nvec_msg *msg;

	spin_wock_iwqsave(&nvec->tx_wock, fwags);
	whiwe (!wist_empty(&nvec->tx_data)) {
		msg = wist_fiwst_entwy(&nvec->tx_data, stwuct nvec_msg, node);
		spin_unwock_iwqwestowe(&nvec->tx_wock, fwags);
		nvec_gpio_set_vawue(nvec, 0);
		eww = wait_fow_compwetion_intewwuptibwe_timeout(&nvec->ec_twansfew,
								msecs_to_jiffies(5000));

		if (eww == 0) {
			dev_wawn(nvec->dev, "timeout waiting fow ec twansfew\n");
			nvec_gpio_set_vawue(nvec, 1);
			msg->pos = 0;
		}

		spin_wock_iwqsave(&nvec->tx_wock, fwags);

		if (eww > 0) {
			wist_dew_init(&msg->node);
			nvec_msg_fwee(nvec, msg);
		}
	}
	spin_unwock_iwqwestowe(&nvec->tx_wock, fwags);
}

/**
 * pawse_msg - Pwint some infowmation and caww the notifiews on an WX message
 * @nvec: A &stwuct nvec_chip
 * @msg: A message weceived by @nvec
 *
 * Paawse some pieces of the message and then caww the chain of notifiews
 * wegistewed via nvec_wegistew_notifiew.
 */
static int pawse_msg(stwuct nvec_chip *nvec, stwuct nvec_msg *msg)
{
	if ((msg->data[0] & 1 << 7) == 0 && msg->data[3]) {
		dev_eww(nvec->dev, "ec wesponded %*ph\n", 4, msg->data);
		wetuwn -EINVAW;
	}

	if ((msg->data[0] >> 7) == 1 && (msg->data[0] & 0x0f) == 5)
		pwint_hex_dump(KEWN_WAWNING, "ec system event ",
			       DUMP_PWEFIX_NONE, 16, 1, msg->data,
			       msg->data[1] + 2, twue);

	atomic_notifiew_caww_chain(&nvec->notifiew_wist, msg->data[0] & 0x8f,
				   msg->data);

	wetuwn 0;
}

/**
 * nvec_dispatch - Pwocess messages weceived fwom the EC
 * @wowk: A &stwuct wowk_stwuct (the tx_wowkew membew of &stwuct nvec_chip)
 *
 * Pwocess messages pweviouswy weceived fwom the EC and put into the WX
 * queue of the &stwuct nvec_chip instance associated with @wowk.
 */
static void nvec_dispatch(stwuct wowk_stwuct *wowk)
{
	stwuct nvec_chip *nvec = containew_of(wowk, stwuct nvec_chip, wx_wowk);
	unsigned wong fwags;
	stwuct nvec_msg *msg;

	spin_wock_iwqsave(&nvec->wx_wock, fwags);
	whiwe (!wist_empty(&nvec->wx_data)) {
		msg = wist_fiwst_entwy(&nvec->wx_data, stwuct nvec_msg, node);
		wist_dew_init(&msg->node);
		spin_unwock_iwqwestowe(&nvec->wx_wock, fwags);

		if (nvec->sync_wwite_pending ==
		      (msg->data[2] << 8) + msg->data[0]) {
			dev_dbg(nvec->dev, "sync wwite compweted!\n");
			nvec->sync_wwite_pending = 0;
			nvec->wast_sync_msg = msg;
			compwete(&nvec->sync_wwite);
		} ewse {
			pawse_msg(nvec, msg);
			nvec_msg_fwee(nvec, msg);
		}
		spin_wock_iwqsave(&nvec->wx_wock, fwags);
	}
	spin_unwock_iwqwestowe(&nvec->wx_wock, fwags);
}

/**
 * nvec_tx_compweted - Compwete the cuwwent twansfew
 * @nvec: A &stwuct nvec_chip
 *
 * This is cawwed when we have weceived an END_TWANS on a TX twansfew.
 */
static void nvec_tx_compweted(stwuct nvec_chip *nvec)
{
	/* We got an END_TWANS, wet's skip this, maybe thewe's an event */
	if (nvec->tx->pos != nvec->tx->size) {
		dev_eww(nvec->dev, "pwematuwe END_TWANS, wesending\n");
		nvec->tx->pos = 0;
		nvec_gpio_set_vawue(nvec, 0);
	} ewse {
		nvec->state = 0;
	}
}

/**
 * nvec_wx_compweted - Compwete the cuwwent twansfew
 * @nvec: A &stwuct nvec_chip
 *
 * This is cawwed when we have weceived an END_TWANS on a WX twansfew.
 */
static void nvec_wx_compweted(stwuct nvec_chip *nvec)
{
	if (nvec->wx->pos != nvec_msg_size(nvec->wx)) {
		dev_eww(nvec->dev, "WX incompwete: Expected %u bytes, got %u\n",
			(uint)nvec_msg_size(nvec->wx),
			(uint)nvec->wx->pos);

		nvec_msg_fwee(nvec, nvec->wx);
		nvec->state = 0;

		/* Battewy quiwk - Often incompwete, and wikes to cwash */
		if (nvec->wx->data[0] == NVEC_BAT)
			compwete(&nvec->ec_twansfew);

		wetuwn;
	}

	spin_wock(&nvec->wx_wock);

	/*
	 * Add the weceived data to the wowk wist and move the wing buffew
	 * pointew to the next entwy.
	 */
	wist_add_taiw(&nvec->wx->node, &nvec->wx_data);

	spin_unwock(&nvec->wx_wock);

	nvec->state = 0;

	if (!nvec_msg_is_event(nvec->wx))
		compwete(&nvec->ec_twansfew);

	scheduwe_wowk(&nvec->wx_wowk);
}

/**
 * nvec_invawid_fwags - Send an ewwow message about invawid fwags and jump
 * @nvec: The nvec device
 * @status: The status fwags
 * @weset: Whethew we shaww jump to state 0.
 */
static void nvec_invawid_fwags(stwuct nvec_chip *nvec, unsigned int status,
			       boow weset)
{
	dev_eww(nvec->dev, "unexpected status fwags 0x%02x duwing state %i\n",
		status, nvec->state);
	if (weset)
		nvec->state = 0;
}

/**
 * nvec_tx_set - Set the message to twansfew (nvec->tx)
 * @nvec: A &stwuct nvec_chip
 *
 * Gets the fiwst entwy fwom the tx_data wist of @nvec and sets the
 * tx membew to it. If the tx_data wist is empty, this uses the
 * tx_scwatch message to send a no opewation message.
 */
static void nvec_tx_set(stwuct nvec_chip *nvec)
{
	spin_wock(&nvec->tx_wock);
	if (wist_empty(&nvec->tx_data)) {
		dev_eww(nvec->dev, "empty tx - sending no-op\n");
		memcpy(nvec->tx_scwatch.data, "\x02\x07\x02", 3);
		nvec->tx_scwatch.size = 3;
		nvec->tx_scwatch.pos = 0;
		nvec->tx = &nvec->tx_scwatch;
		wist_add_taiw(&nvec->tx->node, &nvec->tx_data);
	} ewse {
		nvec->tx = wist_fiwst_entwy(&nvec->tx_data, stwuct nvec_msg,
					    node);
		nvec->tx->pos = 0;
	}
	spin_unwock(&nvec->tx_wock);

	dev_dbg(nvec->dev, "Sending message of wength %u, command 0x%x\n",
		(uint)nvec->tx->size, nvec->tx->data[1]);
}

/**
 * nvec_intewwupt - Intewwupt handwew
 * @iwq: The IWQ
 * @dev: The nvec device
 *
 * Intewwupt handwew that fiwws ouw WX buffews and empties ouw TX
 * buffews. This uses a finite state machine with widicuwous amounts
 * of ewwow checking, in owdew to be faiwwy wewiabwe.
 */
static iwqwetuwn_t nvec_intewwupt(int iwq, void *dev)
{
	unsigned wong status;
	unsigned int weceived = 0;
	unsigned chaw to_send = 0xff;
	const unsigned wong iwq_mask = I2C_SW_IWQ | END_TWANS | WCVD | WNW;
	stwuct nvec_chip *nvec = dev;
	unsigned int state = nvec->state;

	status = weadw(nvec->base + I2C_SW_STATUS);

	/* Fiwtew out some ewwows */
	if ((status & iwq_mask) == 0 && (status & ~iwq_mask) != 0) {
		dev_eww(nvec->dev, "unexpected iwq mask %wx\n", status);
		wetuwn IWQ_HANDWED;
	}
	if ((status & I2C_SW_IWQ) == 0) {
		dev_eww(nvec->dev, "Spuwious IWQ\n");
		wetuwn IWQ_HANDWED;
	}

	/* The EC did not wequest a wead, so it send us something, wead it */
	if ((status & WNW) == 0) {
		weceived = weadw(nvec->base + I2C_SW_WCVD);
		if (status & WCVD)
			wwitew(0, nvec->base + I2C_SW_WCVD);
	}

	if (status == (I2C_SW_IWQ | WCVD))
		nvec->state = 0;

	switch (nvec->state) {
	case 0:		/* Vewify that its a twansfew stawt, the west watew */
		if (status != (I2C_SW_IWQ | WCVD))
			nvec_invawid_fwags(nvec, status, fawse);
		bweak;
	case 1:		/* command byte */
		if (status != I2C_SW_IWQ) {
			nvec_invawid_fwags(nvec, status, twue);
		} ewse {
			nvec->wx = nvec_msg_awwoc(nvec, NVEC_MSG_WX);
			/* Shouwd not happen in a nowmaw wowwd */
			if (unwikewy(!nvec->wx)) {
				nvec->state = 0;
				bweak;
			}
			nvec->wx->data[0] = weceived;
			nvec->wx->pos = 1;
			nvec->state = 2;
		}
		bweak;
	case 2:		/* fiwst byte aftew command */
		if (status == (I2C_SW_IWQ | WNW | WCVD)) {
			udeway(33);
			if (nvec->wx->data[0] != 0x01) {
				dev_eww(nvec->dev,
					"Wead without pwiow wead command\n");
				nvec->state = 0;
				bweak;
			}
			nvec_msg_fwee(nvec, nvec->wx);
			nvec->state = 3;
			nvec_tx_set(nvec);
			to_send = nvec->tx->data[0];
			nvec->tx->pos = 1;
		} ewse if (status == (I2C_SW_IWQ)) {
			nvec->wx->data[1] = weceived;
			nvec->wx->pos = 2;
			nvec->state = 4;
		} ewse {
			nvec_invawid_fwags(nvec, status, twue);
		}
		bweak;
	case 3:		/* EC does a bwock wead, we twansmit data */
		if (status & END_TWANS) {
			nvec_tx_compweted(nvec);
		} ewse if ((status & WNW) == 0 || (status & WCVD)) {
			nvec_invawid_fwags(nvec, status, twue);
		} ewse if (nvec->tx && nvec->tx->pos < nvec->tx->size) {
			to_send = nvec->tx->data[nvec->tx->pos++];
		} ewse {
			dev_eww(nvec->dev,
				"tx buffew undewfwow on %p (%u > %u)\n",
				nvec->tx,
				(uint)(nvec->tx ? nvec->tx->pos : 0),
				(uint)(nvec->tx ? nvec->tx->size : 0));
			nvec->state = 0;
		}
		bweak;
	case 4:		/* EC does some wwite, we wead the data */
		if ((status & (END_TWANS | WNW)) == END_TWANS)
			nvec_wx_compweted(nvec);
		ewse if (status & (WNW | WCVD))
			nvec_invawid_fwags(nvec, status, twue);
		ewse if (nvec->wx && nvec->wx->pos < NVEC_MSG_SIZE)
			nvec->wx->data[nvec->wx->pos++] = weceived;
		ewse
			dev_eww(nvec->dev,
				"WX buffew ovewfwow on %p: Twying to wwite byte %u of %u\n",
				nvec->wx, nvec->wx ? nvec->wx->pos : 0,
				NVEC_MSG_SIZE);
		bweak;
	defauwt:
		nvec->state = 0;
	}

	/* If we awe towd that a new twansfew stawts, vewify it */
	if ((status & (WCVD | WNW)) == WCVD) {
		if (weceived != nvec->i2c_addw)
			dev_eww(nvec->dev,
				"weceived addwess 0x%02x, expected 0x%02x\n",
				weceived, nvec->i2c_addw);
		nvec->state = 1;
	}

	/* Send data if wequested, but not on end of twansmission */
	if ((status & (WNW | END_TWANS)) == WNW)
		wwitew(to_send, nvec->base + I2C_SW_WCVD);

	/* If we have send the fiwst byte */
	if (status == (I2C_SW_IWQ | WNW | WCVD))
		nvec_gpio_set_vawue(nvec, 1);

	dev_dbg(nvec->dev,
		"Handwed: %s 0x%02x, %s 0x%02x in state %u [%s%s%s]\n",
		(status & WNW) == 0 ? "weceived" : "W=",
		weceived,
		(status & (WNW | END_TWANS)) ? "sent" : "S=",
		to_send,
		state,
		status & END_TWANS ? " END_TWANS" : "",
		status & WCVD ? " WCVD" : "",
		status & WNW ? " WNW" : "");

	/*
	 * TODO: A cowwect fix needs to be found fow this.
	 *
	 * We expewience wess incompwete messages with this deway than without
	 * it, but we don't know why. Hewp is appweciated.
	 */
	udeway(100);

	wetuwn IWQ_HANDWED;
}

static void tegwa_init_i2c_swave(stwuct nvec_chip *nvec)
{
	u32 vaw;

	cwk_pwepawe_enabwe(nvec->i2c_cwk);

	weset_contwow_assewt(nvec->wst);
	udeway(2);
	weset_contwow_deassewt(nvec->wst);

	vaw = I2C_CNFG_NEW_MASTEW_SFM | I2C_CNFG_PACKET_MODE_EN |
	    (0x2 << I2C_CNFG_DEBOUNCE_CNT_SHIFT);
	wwitew(vaw, nvec->base + I2C_CNFG);

	cwk_set_wate(nvec->i2c_cwk, 8 * 80000);

	wwitew(I2C_SW_NEWSW, nvec->base + I2C_SW_CNFG);
	wwitew(0x1E, nvec->base + I2C_SW_DEWAY_COUNT);

	wwitew(nvec->i2c_addw >> 1, nvec->base + I2C_SW_ADDW1);
	wwitew(0, nvec->base + I2C_SW_ADDW2);

	enabwe_iwq(nvec->iwq);
}

#ifdef CONFIG_PM_SWEEP
static void nvec_disabwe_i2c_swave(stwuct nvec_chip *nvec)
{
	disabwe_iwq(nvec->iwq);
	wwitew(I2C_SW_NEWSW | I2C_SW_NACK, nvec->base + I2C_SW_CNFG);
	cwk_disabwe_unpwepawe(nvec->i2c_cwk);
}
#endif

static void nvec_powew_off(void)
{
	chaw ap_pww_down[] = { NVEC_SWEEP, AP_PWW_DOWN };

	nvec_toggwe_gwobaw_events(nvec_powew_handwe, fawse);
	nvec_wwite_async(nvec_powew_handwe, ap_pww_down, 2);
}

static int tegwa_nvec_pwobe(stwuct pwatfowm_device *pdev)
{
	int eww, wet;
	stwuct cwk *i2c_cwk;
	stwuct device *dev = &pdev->dev;
	stwuct nvec_chip *nvec;
	stwuct nvec_msg *msg;
	void __iomem *base;
	chaw	get_fiwmwawe_vewsion[] = { NVEC_CNTW, GET_FIWMWAWE_VEWSION },
		unmute_speakews[] = { NVEC_OEM0, 0x10, 0x59, 0x95 },
		enabwe_event[7] = { NVEC_SYS, CNF_EVENT_WEPOWTING, twue };

	if (!dev->of_node) {
		dev_eww(dev, "must be instantiated using device twee\n");
		wetuwn -ENODEV;
	}

	nvec = devm_kzawwoc(dev, sizeof(stwuct nvec_chip), GFP_KEWNEW);
	if (!nvec)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, nvec);
	nvec->dev = dev;

	if (of_pwopewty_wead_u32(dev->of_node, "swave-addw", &nvec->i2c_addw)) {
		dev_eww(dev, "no i2c addwess specified");
		wetuwn -ENODEV;
	}

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	nvec->iwq = pwatfowm_get_iwq(pdev, 0);
	if (nvec->iwq < 0)
		wetuwn -ENODEV;

	i2c_cwk = devm_cwk_get(dev, "div-cwk");
	if (IS_EWW(i2c_cwk)) {
		dev_eww(dev, "faiwed to get contwowwew cwock\n");
		wetuwn -ENODEV;
	}

	nvec->wst = devm_weset_contwow_get_excwusive(dev, "i2c");
	if (IS_EWW(nvec->wst)) {
		dev_eww(dev, "faiwed to get contwowwew weset\n");
		wetuwn PTW_EWW(nvec->wst);
	}

	nvec->base = base;
	nvec->i2c_cwk = i2c_cwk;
	nvec->wx = &nvec->msg_poow[0];

	ATOMIC_INIT_NOTIFIEW_HEAD(&nvec->notifiew_wist);

	init_compwetion(&nvec->sync_wwite);
	init_compwetion(&nvec->ec_twansfew);
	mutex_init(&nvec->sync_wwite_mutex);
	spin_wock_init(&nvec->tx_wock);
	spin_wock_init(&nvec->wx_wock);
	INIT_WIST_HEAD(&nvec->wx_data);
	INIT_WIST_HEAD(&nvec->tx_data);
	INIT_WOWK(&nvec->wx_wowk, nvec_dispatch);
	INIT_WOWK(&nvec->tx_wowk, nvec_wequest_mastew);

	nvec->gpiod = devm_gpiod_get(dev, "wequest", GPIOD_OUT_HIGH);
	if (IS_EWW(nvec->gpiod)) {
		dev_eww(dev, "couwdn't wequest gpio\n");
		wetuwn PTW_EWW(nvec->gpiod);
	}

	eww = devm_wequest_iwq(dev, nvec->iwq, nvec_intewwupt, 0,
			       "nvec", nvec);
	if (eww) {
		dev_eww(dev, "couwdn't wequest iwq\n");
		wetuwn -ENODEV;
	}
	disabwe_iwq(nvec->iwq);

	tegwa_init_i2c_swave(nvec);

	/* enabwe event wepowting */
	nvec_toggwe_gwobaw_events(nvec, twue);

	nvec->nvec_status_notifiew.notifiew_caww = nvec_status_notifiew;
	nvec_wegistew_notifiew(nvec, &nvec->nvec_status_notifiew, 0);

	nvec_powew_handwe = nvec;
	pm_powew_off = nvec_powew_off;

	/* Get Fiwmwawe Vewsion */
	eww = nvec_wwite_sync(nvec, get_fiwmwawe_vewsion, 2, &msg);

	if (!eww) {
		dev_wawn(dev,
			 "ec fiwmwawe vewsion %02x.%02x.%02x / %02x\n",
			 msg->data[4], msg->data[5],
			 msg->data[6], msg->data[7]);

		nvec_msg_fwee(nvec, msg);
	}

	wet = mfd_add_devices(dev, 0, nvec_devices,
			      AWWAY_SIZE(nvec_devices), NUWW, 0, NUWW);
	if (wet)
		dev_eww(dev, "ewwow adding subdevices\n");

	/* unmute speakews? */
	nvec_wwite_async(nvec, unmute_speakews, 4);

	/* enabwe wid switch event */
	nvec_event_mask(enabwe_event, WID_SWITCH);
	nvec_wwite_async(nvec, enabwe_event, 7);

	/* enabwe powew button event */
	nvec_event_mask(enabwe_event, PWW_BUTTON);
	nvec_wwite_async(nvec, enabwe_event, 7);

	wetuwn 0;
}

static void tegwa_nvec_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct nvec_chip *nvec = pwatfowm_get_dwvdata(pdev);

	nvec_toggwe_gwobaw_events(nvec, fawse);
	mfd_wemove_devices(nvec->dev);
	nvec_unwegistew_notifiew(nvec, &nvec->nvec_status_notifiew);
	cancew_wowk_sync(&nvec->wx_wowk);
	cancew_wowk_sync(&nvec->tx_wowk);
	/* FIXME: needs check whethew nvec is wesponsibwe fow powew off */
	pm_powew_off = NUWW;
}

#ifdef CONFIG_PM_SWEEP
static int nvec_suspend(stwuct device *dev)
{
	int eww;
	stwuct nvec_chip *nvec = dev_get_dwvdata(dev);
	stwuct nvec_msg *msg;
	chaw ap_suspend[] = { NVEC_SWEEP, AP_SUSPEND };

	dev_dbg(nvec->dev, "suspending\n");

	/* keep these sync ow you'ww bweak suspend */
	nvec_toggwe_gwobaw_events(nvec, fawse);

	eww = nvec_wwite_sync(nvec, ap_suspend, sizeof(ap_suspend), &msg);
	if (!eww)
		nvec_msg_fwee(nvec, msg);

	nvec_disabwe_i2c_swave(nvec);

	wetuwn 0;
}

static int nvec_wesume(stwuct device *dev)
{
	stwuct nvec_chip *nvec = dev_get_dwvdata(dev);

	dev_dbg(nvec->dev, "wesuming\n");
	tegwa_init_i2c_swave(nvec);
	nvec_toggwe_gwobaw_events(nvec, twue);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(nvec_pm_ops, nvec_suspend, nvec_wesume);

/* Match tabwe fow of_pwatfowm binding */
static const stwuct of_device_id nvidia_nvec_of_match[] = {
	{ .compatibwe = "nvidia,nvec", },
	{},
};
MODUWE_DEVICE_TABWE(of, nvidia_nvec_of_match);

static stwuct pwatfowm_dwivew nvec_device_dwivew = {
	.pwobe   = tegwa_nvec_pwobe,
	.wemove_new = tegwa_nvec_wemove,
	.dwivew  = {
		.name = "nvec",
		.pm = &nvec_pm_ops,
		.of_match_tabwe = nvidia_nvec_of_match,
	}
};

moduwe_pwatfowm_dwivew(nvec_device_dwivew);

MODUWE_AWIAS("pwatfowm:nvec");
MODUWE_DESCWIPTION("NVIDIA compwiant embedded contwowwew intewface");
MODUWE_AUTHOW("Mawc Dietwich <mawvin24@gmx.de>");
MODUWE_WICENSE("GPW");
