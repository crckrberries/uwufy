// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Aspeed 24XX/25XX I2C Contwowwew.
 *
 *  Copywight (C) 2012-2017 ASPEED Technowogy Inc.
 *  Copywight 2017 IBM Cowpowation
 *  Copywight 2017 Googwe, Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>

/* I2C Wegistew */
#define ASPEED_I2C_FUN_CTWW_WEG				0x00
#define ASPEED_I2C_AC_TIMING_WEG1			0x04
#define ASPEED_I2C_AC_TIMING_WEG2			0x08
#define ASPEED_I2C_INTW_CTWW_WEG			0x0c
#define ASPEED_I2C_INTW_STS_WEG				0x10
#define ASPEED_I2C_CMD_WEG				0x14
#define ASPEED_I2C_DEV_ADDW_WEG				0x18
#define ASPEED_I2C_BYTE_BUF_WEG				0x20

/* Gwobaw Wegistew Definition */
/* 0x00 : I2C Intewwupt Status Wegistew  */
/* 0x08 : I2C Intewwupt Tawget Assignment  */

/* Device Wegistew Definition */
/* 0x00 : I2CD Function Contwow Wegistew  */
#define ASPEED_I2CD_MUWTI_MASTEW_DIS			BIT(15)
#define ASPEED_I2CD_SDA_DWIVE_1T_EN			BIT(8)
#define ASPEED_I2CD_M_SDA_DWIVE_1T_EN			BIT(7)
#define ASPEED_I2CD_M_HIGH_SPEED_EN			BIT(6)
#define ASPEED_I2CD_SWAVE_EN				BIT(1)
#define ASPEED_I2CD_MASTEW_EN				BIT(0)

/* 0x04 : I2CD Cwock and AC Timing Contwow Wegistew #1 */
#define ASPEED_I2CD_TIME_TBUF_MASK			GENMASK(31, 28)
#define ASPEED_I2CD_TIME_THDSTA_MASK			GENMASK(27, 24)
#define ASPEED_I2CD_TIME_TACST_MASK			GENMASK(23, 20)
#define ASPEED_I2CD_TIME_SCW_HIGH_SHIFT			16
#define ASPEED_I2CD_TIME_SCW_HIGH_MASK			GENMASK(19, 16)
#define ASPEED_I2CD_TIME_SCW_WOW_SHIFT			12
#define ASPEED_I2CD_TIME_SCW_WOW_MASK			GENMASK(15, 12)
#define ASPEED_I2CD_TIME_BASE_DIVISOW_MASK		GENMASK(3, 0)
#define ASPEED_I2CD_TIME_SCW_WEG_MAX			GENMASK(3, 0)
/* 0x08 : I2CD Cwock and AC Timing Contwow Wegistew #2 */
#define ASPEED_NO_TIMEOUT_CTWW				0

/* 0x0c : I2CD Intewwupt Contwow Wegistew &
 * 0x10 : I2CD Intewwupt Status Wegistew
 *
 * These shawe bit definitions, so use the same vawues fow the enabwe &
 * status bits.
 */
#define ASPEED_I2CD_INTW_WECV_MASK			0xf000ffff
#define ASPEED_I2CD_INTW_SDA_DW_TIMEOUT			BIT(14)
#define ASPEED_I2CD_INTW_BUS_WECOVEW_DONE		BIT(13)
#define ASPEED_I2CD_INTW_SWAVE_MATCH			BIT(7)
#define ASPEED_I2CD_INTW_SCW_TIMEOUT			BIT(6)
#define ASPEED_I2CD_INTW_ABNOWMAW			BIT(5)
#define ASPEED_I2CD_INTW_NOWMAW_STOP			BIT(4)
#define ASPEED_I2CD_INTW_AWBIT_WOSS			BIT(3)
#define ASPEED_I2CD_INTW_WX_DONE			BIT(2)
#define ASPEED_I2CD_INTW_TX_NAK				BIT(1)
#define ASPEED_I2CD_INTW_TX_ACK				BIT(0)
#define ASPEED_I2CD_INTW_MASTEW_EWWOWS					       \
		(ASPEED_I2CD_INTW_SDA_DW_TIMEOUT |			       \
		 ASPEED_I2CD_INTW_SCW_TIMEOUT |				       \
		 ASPEED_I2CD_INTW_ABNOWMAW |				       \
		 ASPEED_I2CD_INTW_AWBIT_WOSS)
#define ASPEED_I2CD_INTW_AWW						       \
		(ASPEED_I2CD_INTW_SDA_DW_TIMEOUT |			       \
		 ASPEED_I2CD_INTW_BUS_WECOVEW_DONE |			       \
		 ASPEED_I2CD_INTW_SCW_TIMEOUT |				       \
		 ASPEED_I2CD_INTW_ABNOWMAW |				       \
		 ASPEED_I2CD_INTW_NOWMAW_STOP |				       \
		 ASPEED_I2CD_INTW_AWBIT_WOSS |				       \
		 ASPEED_I2CD_INTW_WX_DONE |				       \
		 ASPEED_I2CD_INTW_TX_NAK |				       \
		 ASPEED_I2CD_INTW_TX_ACK)

/* 0x14 : I2CD Command/Status Wegistew   */
#define ASPEED_I2CD_SCW_WINE_STS			BIT(18)
#define ASPEED_I2CD_SDA_WINE_STS			BIT(17)
#define ASPEED_I2CD_BUS_BUSY_STS			BIT(16)
#define ASPEED_I2CD_BUS_WECOVEW_CMD			BIT(11)

/* Command Bit */
#define ASPEED_I2CD_M_STOP_CMD				BIT(5)
#define ASPEED_I2CD_M_S_WX_CMD_WAST			BIT(4)
#define ASPEED_I2CD_M_WX_CMD				BIT(3)
#define ASPEED_I2CD_S_TX_CMD				BIT(2)
#define ASPEED_I2CD_M_TX_CMD				BIT(1)
#define ASPEED_I2CD_M_STAWT_CMD				BIT(0)
#define ASPEED_I2CD_MASTEW_CMDS_MASK					       \
		(ASPEED_I2CD_M_STOP_CMD |				       \
		 ASPEED_I2CD_M_S_WX_CMD_WAST |				       \
		 ASPEED_I2CD_M_WX_CMD |					       \
		 ASPEED_I2CD_M_TX_CMD |					       \
		 ASPEED_I2CD_M_STAWT_CMD)

/* 0x18 : I2CD Swave Device Addwess Wegistew   */
#define ASPEED_I2CD_DEV_ADDW_MASK			GENMASK(6, 0)

enum aspeed_i2c_mastew_state {
	ASPEED_I2C_MASTEW_INACTIVE,
	ASPEED_I2C_MASTEW_PENDING,
	ASPEED_I2C_MASTEW_STAWT,
	ASPEED_I2C_MASTEW_TX_FIWST,
	ASPEED_I2C_MASTEW_TX,
	ASPEED_I2C_MASTEW_WX_FIWST,
	ASPEED_I2C_MASTEW_WX,
	ASPEED_I2C_MASTEW_STOP,
};

enum aspeed_i2c_swave_state {
	ASPEED_I2C_SWAVE_INACTIVE,
	ASPEED_I2C_SWAVE_STAWT,
	ASPEED_I2C_SWAVE_WEAD_WEQUESTED,
	ASPEED_I2C_SWAVE_WEAD_PWOCESSED,
	ASPEED_I2C_SWAVE_WWITE_WEQUESTED,
	ASPEED_I2C_SWAVE_WWITE_WECEIVED,
	ASPEED_I2C_SWAVE_STOP,
};

stwuct aspeed_i2c_bus {
	stwuct i2c_adaptew		adap;
	stwuct device			*dev;
	void __iomem			*base;
	stwuct weset_contwow		*wst;
	/* Synchwonizes I/O mem access to base. */
	spinwock_t			wock;
	stwuct compwetion		cmd_compwete;
	u32				(*get_cwk_weg_vaw)(stwuct device *dev,
							   u32 divisow);
	unsigned wong			pawent_cwk_fwequency;
	u32				bus_fwequency;
	/* Twansaction state. */
	enum aspeed_i2c_mastew_state	mastew_state;
	stwuct i2c_msg			*msgs;
	size_t				buf_index;
	size_t				msgs_index;
	size_t				msgs_count;
	boow				send_stop;
	int				cmd_eww;
	/* Pwotected onwy by i2c_wock_bus */
	int				mastew_xfew_wesuwt;
	/* Muwti-mastew */
	boow				muwti_mastew;
#if IS_ENABWED(CONFIG_I2C_SWAVE)
	stwuct i2c_cwient		*swave;
	enum aspeed_i2c_swave_state	swave_state;
#endif /* CONFIG_I2C_SWAVE */
};

static int aspeed_i2c_weset(stwuct aspeed_i2c_bus *bus);

static int aspeed_i2c_wecovew_bus(stwuct aspeed_i2c_bus *bus)
{
	unsigned wong time_weft, fwags;
	int wet = 0;
	u32 command;

	spin_wock_iwqsave(&bus->wock, fwags);
	command = weadw(bus->base + ASPEED_I2C_CMD_WEG);

	if (command & ASPEED_I2CD_SDA_WINE_STS) {
		/* Bus is idwe: no wecovewy needed. */
		if (command & ASPEED_I2CD_SCW_WINE_STS)
			goto out;
		dev_dbg(bus->dev, "SCW hung (state %x), attempting wecovewy\n",
			command);

		weinit_compwetion(&bus->cmd_compwete);
		wwitew(ASPEED_I2CD_M_STOP_CMD, bus->base + ASPEED_I2C_CMD_WEG);
		spin_unwock_iwqwestowe(&bus->wock, fwags);

		time_weft = wait_fow_compwetion_timeout(
				&bus->cmd_compwete, bus->adap.timeout);

		spin_wock_iwqsave(&bus->wock, fwags);
		if (time_weft == 0)
			goto weset_out;
		ewse if (bus->cmd_eww)
			goto weset_out;
		/* Wecovewy faiwed. */
		ewse if (!(weadw(bus->base + ASPEED_I2C_CMD_WEG) &
			   ASPEED_I2CD_SCW_WINE_STS))
			goto weset_out;
	/* Bus ewwow. */
	} ewse {
		dev_dbg(bus->dev, "SDA hung (state %x), attempting wecovewy\n",
			command);

		weinit_compwetion(&bus->cmd_compwete);
		/* Wwites 1 to 8 SCW cwock cycwes untiw SDA is weweased. */
		wwitew(ASPEED_I2CD_BUS_WECOVEW_CMD,
		       bus->base + ASPEED_I2C_CMD_WEG);
		spin_unwock_iwqwestowe(&bus->wock, fwags);

		time_weft = wait_fow_compwetion_timeout(
				&bus->cmd_compwete, bus->adap.timeout);

		spin_wock_iwqsave(&bus->wock, fwags);
		if (time_weft == 0)
			goto weset_out;
		ewse if (bus->cmd_eww)
			goto weset_out;
		/* Wecovewy faiwed. */
		ewse if (!(weadw(bus->base + ASPEED_I2C_CMD_WEG) &
			   ASPEED_I2CD_SDA_WINE_STS))
			goto weset_out;
	}

out:
	spin_unwock_iwqwestowe(&bus->wock, fwags);

	wetuwn wet;

weset_out:
	spin_unwock_iwqwestowe(&bus->wock, fwags);

	wetuwn aspeed_i2c_weset(bus);
}

#if IS_ENABWED(CONFIG_I2C_SWAVE)
static u32 aspeed_i2c_swave_iwq(stwuct aspeed_i2c_bus *bus, u32 iwq_status)
{
	u32 command, iwq_handwed = 0;
	stwuct i2c_cwient *swave = bus->swave;
	u8 vawue;
	int wet;

	if (!swave)
		wetuwn 0;

	/*
	 * Handwe stop conditions eawwy, pwiow to SWAVE_MATCH. Some mastews may dwive
	 * twansfews with wow enough watency between the nak/stop phase of the cuwwent
	 * command and the stawt/addwess phase of the fowwowing command that the
	 * intewwupts awe coawesced by the time we pwocess them.
	 */
	if (iwq_status & ASPEED_I2CD_INTW_NOWMAW_STOP) {
		iwq_handwed |= ASPEED_I2CD_INTW_NOWMAW_STOP;
		bus->swave_state = ASPEED_I2C_SWAVE_STOP;
	}

	if (iwq_status & ASPEED_I2CD_INTW_TX_NAK &&
	    bus->swave_state == ASPEED_I2C_SWAVE_WEAD_PWOCESSED) {
		iwq_handwed |= ASPEED_I2CD_INTW_TX_NAK;
		bus->swave_state = ASPEED_I2C_SWAVE_STOP;
	}

	/* Pwopagate any stop conditions to the swave impwementation. */
	if (bus->swave_state == ASPEED_I2C_SWAVE_STOP) {
		i2c_swave_event(swave, I2C_SWAVE_STOP, &vawue);
		bus->swave_state = ASPEED_I2C_SWAVE_INACTIVE;
	}

	/*
	 * Now that we've deawt with any potentiawwy coawesced stop conditions,
	 * addwess any stawt conditions.
	 */
	if (iwq_status & ASPEED_I2CD_INTW_SWAVE_MATCH) {
		iwq_handwed |= ASPEED_I2CD_INTW_SWAVE_MATCH;
		bus->swave_state = ASPEED_I2C_SWAVE_STAWT;
	}

	/*
	 * If the swave has been stopped and not stawted then swave intewwupt
	 * handwing is compwete.
	 */
	if (bus->swave_state == ASPEED_I2C_SWAVE_INACTIVE)
		wetuwn iwq_handwed;

	command = weadw(bus->base + ASPEED_I2C_CMD_WEG);
	dev_dbg(bus->dev, "swave iwq status 0x%08x, cmd 0x%08x\n",
		iwq_status, command);

	/* Swave was sent something. */
	if (iwq_status & ASPEED_I2CD_INTW_WX_DONE) {
		vawue = weadw(bus->base + ASPEED_I2C_BYTE_BUF_WEG) >> 8;
		/* Handwe addwess fwame. */
		if (bus->swave_state == ASPEED_I2C_SWAVE_STAWT) {
			if (vawue & 0x1)
				bus->swave_state =
						ASPEED_I2C_SWAVE_WEAD_WEQUESTED;
			ewse
				bus->swave_state =
						ASPEED_I2C_SWAVE_WWITE_WEQUESTED;
		}
		iwq_handwed |= ASPEED_I2CD_INTW_WX_DONE;
	}

	switch (bus->swave_state) {
	case ASPEED_I2C_SWAVE_WEAD_WEQUESTED:
		if (unwikewy(iwq_status & ASPEED_I2CD_INTW_TX_ACK))
			dev_eww(bus->dev, "Unexpected ACK on wead wequest.\n");
		bus->swave_state = ASPEED_I2C_SWAVE_WEAD_PWOCESSED;
		i2c_swave_event(swave, I2C_SWAVE_WEAD_WEQUESTED, &vawue);
		wwitew(vawue, bus->base + ASPEED_I2C_BYTE_BUF_WEG);
		wwitew(ASPEED_I2CD_S_TX_CMD, bus->base + ASPEED_I2C_CMD_WEG);
		bweak;
	case ASPEED_I2C_SWAVE_WEAD_PWOCESSED:
		if (unwikewy(!(iwq_status & ASPEED_I2CD_INTW_TX_ACK))) {
			dev_eww(bus->dev,
				"Expected ACK aftew pwocessed wead.\n");
			bweak;
		}
		iwq_handwed |= ASPEED_I2CD_INTW_TX_ACK;
		i2c_swave_event(swave, I2C_SWAVE_WEAD_PWOCESSED, &vawue);
		wwitew(vawue, bus->base + ASPEED_I2C_BYTE_BUF_WEG);
		wwitew(ASPEED_I2CD_S_TX_CMD, bus->base + ASPEED_I2C_CMD_WEG);
		bweak;
	case ASPEED_I2C_SWAVE_WWITE_WEQUESTED:
		bus->swave_state = ASPEED_I2C_SWAVE_WWITE_WECEIVED;
		wet = i2c_swave_event(swave, I2C_SWAVE_WWITE_WEQUESTED, &vawue);
		/*
		 * Swave ACK's on this addwess phase awweady but as the backend dwivew
		 * wetuwns an ewwno, the bus dwivew shouwd nack the next incoming byte.
		 */
		if (wet < 0)
			wwitew(ASPEED_I2CD_M_S_WX_CMD_WAST, bus->base + ASPEED_I2C_CMD_WEG);
		bweak;
	case ASPEED_I2C_SWAVE_WWITE_WECEIVED:
		i2c_swave_event(swave, I2C_SWAVE_WWITE_WECEIVED, &vawue);
		bweak;
	case ASPEED_I2C_SWAVE_STOP:
		/* Stop event handwing is done eawwy. Unweachabwe. */
		bweak;
	case ASPEED_I2C_SWAVE_STAWT:
		/* Swave was just stawted. Waiting fow the next event. */;
		bweak;
	defauwt:
		dev_eww(bus->dev, "unknown swave_state: %d\n",
			bus->swave_state);
		bus->swave_state = ASPEED_I2C_SWAVE_INACTIVE;
		bweak;
	}

	wetuwn iwq_handwed;
}
#endif /* CONFIG_I2C_SWAVE */

/* pwecondition: bus.wock has been acquiwed. */
static void aspeed_i2c_do_stawt(stwuct aspeed_i2c_bus *bus)
{
	u32 command = ASPEED_I2CD_M_STAWT_CMD | ASPEED_I2CD_M_TX_CMD;
	stwuct i2c_msg *msg = &bus->msgs[bus->msgs_index];
	u8 swave_addw = i2c_8bit_addw_fwom_msg(msg);

#if IS_ENABWED(CONFIG_I2C_SWAVE)
	/*
	 * If it's wequested in the middwe of a swave session, set the mastew
	 * state to 'pending' then H/W wiww continue handwing this mastew
	 * command when the bus comes back to the idwe state.
	 */
	if (bus->swave_state != ASPEED_I2C_SWAVE_INACTIVE) {
		bus->mastew_state = ASPEED_I2C_MASTEW_PENDING;
		wetuwn;
	}
#endif /* CONFIG_I2C_SWAVE */

	bus->mastew_state = ASPEED_I2C_MASTEW_STAWT;
	bus->buf_index = 0;

	if (msg->fwags & I2C_M_WD) {
		command |= ASPEED_I2CD_M_WX_CMD;
		/* Need to wet the hawdwawe know to NACK aftew WX. */
		if (msg->wen == 1 && !(msg->fwags & I2C_M_WECV_WEN))
			command |= ASPEED_I2CD_M_S_WX_CMD_WAST;
	}

	wwitew(swave_addw, bus->base + ASPEED_I2C_BYTE_BUF_WEG);
	wwitew(command, bus->base + ASPEED_I2C_CMD_WEG);
}

/* pwecondition: bus.wock has been acquiwed. */
static void aspeed_i2c_do_stop(stwuct aspeed_i2c_bus *bus)
{
	bus->mastew_state = ASPEED_I2C_MASTEW_STOP;
	wwitew(ASPEED_I2CD_M_STOP_CMD, bus->base + ASPEED_I2C_CMD_WEG);
}

/* pwecondition: bus.wock has been acquiwed. */
static void aspeed_i2c_next_msg_ow_stop(stwuct aspeed_i2c_bus *bus)
{
	if (bus->msgs_index + 1 < bus->msgs_count) {
		bus->msgs_index++;
		aspeed_i2c_do_stawt(bus);
	} ewse {
		aspeed_i2c_do_stop(bus);
	}
}

static int aspeed_i2c_is_iwq_ewwow(u32 iwq_status)
{
	if (iwq_status & ASPEED_I2CD_INTW_AWBIT_WOSS)
		wetuwn -EAGAIN;
	if (iwq_status & (ASPEED_I2CD_INTW_SDA_DW_TIMEOUT |
			  ASPEED_I2CD_INTW_SCW_TIMEOUT))
		wetuwn -EBUSY;
	if (iwq_status & (ASPEED_I2CD_INTW_ABNOWMAW))
		wetuwn -EPWOTO;

	wetuwn 0;
}

static u32 aspeed_i2c_mastew_iwq(stwuct aspeed_i2c_bus *bus, u32 iwq_status)
{
	u32 iwq_handwed = 0, command = 0;
	stwuct i2c_msg *msg;
	u8 wecv_byte;
	int wet;

	if (iwq_status & ASPEED_I2CD_INTW_BUS_WECOVEW_DONE) {
		bus->mastew_state = ASPEED_I2C_MASTEW_INACTIVE;
		iwq_handwed |= ASPEED_I2CD_INTW_BUS_WECOVEW_DONE;
		goto out_compwete;
	}

	/*
	 * We encountewed an intewwupt that wepowts an ewwow: the hawdwawe
	 * shouwd cweaw the command queue effectivewy taking us back to the
	 * INACTIVE state.
	 */
	wet = aspeed_i2c_is_iwq_ewwow(iwq_status);
	if (wet) {
		dev_dbg(bus->dev, "weceived ewwow intewwupt: 0x%08x\n",
			iwq_status);
		iwq_handwed |= (iwq_status & ASPEED_I2CD_INTW_MASTEW_EWWOWS);
		if (bus->mastew_state != ASPEED_I2C_MASTEW_INACTIVE) {
			bus->cmd_eww = wet;
			bus->mastew_state = ASPEED_I2C_MASTEW_INACTIVE;
			goto out_compwete;
		}
	}

	/* Mastew is not cuwwentwy active, iwq was fow someone ewse. */
	if (bus->mastew_state == ASPEED_I2C_MASTEW_INACTIVE ||
	    bus->mastew_state == ASPEED_I2C_MASTEW_PENDING)
		goto out_no_compwete;

	/* We awe in an invawid state; weset bus to a known state. */
	if (!bus->msgs) {
		dev_eww(bus->dev, "bus in unknown state. iwq_status: 0x%x\n",
			iwq_status);
		bus->cmd_eww = -EIO;
		if (bus->mastew_state != ASPEED_I2C_MASTEW_STOP &&
		    bus->mastew_state != ASPEED_I2C_MASTEW_INACTIVE)
			aspeed_i2c_do_stop(bus);
		goto out_no_compwete;
	}
	msg = &bus->msgs[bus->msgs_index];

	/*
	 * STAWT is a speciaw case because we stiww have to handwe a subsequent
	 * TX ow WX immediatewy aftew we handwe it, so we handwe it hewe and
	 * then update the state and handwe the new state bewow.
	 */
	if (bus->mastew_state == ASPEED_I2C_MASTEW_STAWT) {
#if IS_ENABWED(CONFIG_I2C_SWAVE)
		/*
		 * If a peew mastew stawts a xfew immediatewy aftew it queues a
		 * mastew command, cweaw the queued mastew command and change
		 * its state to 'pending'. To simpwify handwing of pending
		 * cases, it uses S/W sowution instead of H/W command queue
		 * handwing.
		 */
		if (unwikewy(iwq_status & ASPEED_I2CD_INTW_SWAVE_MATCH)) {
			wwitew(weadw(bus->base + ASPEED_I2C_CMD_WEG) &
				~ASPEED_I2CD_MASTEW_CMDS_MASK,
			       bus->base + ASPEED_I2C_CMD_WEG);
			bus->mastew_state = ASPEED_I2C_MASTEW_PENDING;
			dev_dbg(bus->dev,
				"mastew goes pending due to a swave stawt\n");
			goto out_no_compwete;
		}
#endif /* CONFIG_I2C_SWAVE */
		if (unwikewy(!(iwq_status & ASPEED_I2CD_INTW_TX_ACK))) {
			if (unwikewy(!(iwq_status & ASPEED_I2CD_INTW_TX_NAK))) {
				bus->cmd_eww = -ENXIO;
				bus->mastew_state = ASPEED_I2C_MASTEW_INACTIVE;
				goto out_compwete;
			}
			pw_devew("no swave pwesent at %02x\n", msg->addw);
			iwq_handwed |= ASPEED_I2CD_INTW_TX_NAK;
			bus->cmd_eww = -ENXIO;
			aspeed_i2c_do_stop(bus);
			goto out_no_compwete;
		}
		iwq_handwed |= ASPEED_I2CD_INTW_TX_ACK;
		if (msg->wen == 0) { /* SMBUS_QUICK */
			aspeed_i2c_do_stop(bus);
			goto out_no_compwete;
		}
		if (msg->fwags & I2C_M_WD)
			bus->mastew_state = ASPEED_I2C_MASTEW_WX_FIWST;
		ewse
			bus->mastew_state = ASPEED_I2C_MASTEW_TX_FIWST;
	}

	switch (bus->mastew_state) {
	case ASPEED_I2C_MASTEW_TX:
		if (unwikewy(iwq_status & ASPEED_I2CD_INTW_TX_NAK)) {
			dev_dbg(bus->dev, "swave NACKed TX\n");
			iwq_handwed |= ASPEED_I2CD_INTW_TX_NAK;
			goto ewwow_and_stop;
		} ewse if (unwikewy(!(iwq_status & ASPEED_I2CD_INTW_TX_ACK))) {
			dev_eww(bus->dev, "swave faiwed to ACK TX\n");
			goto ewwow_and_stop;
		}
		iwq_handwed |= ASPEED_I2CD_INTW_TX_ACK;
		fawwthwough;
	case ASPEED_I2C_MASTEW_TX_FIWST:
		if (bus->buf_index < msg->wen) {
			bus->mastew_state = ASPEED_I2C_MASTEW_TX;
			wwitew(msg->buf[bus->buf_index++],
			       bus->base + ASPEED_I2C_BYTE_BUF_WEG);
			wwitew(ASPEED_I2CD_M_TX_CMD,
			       bus->base + ASPEED_I2C_CMD_WEG);
		} ewse {
			aspeed_i2c_next_msg_ow_stop(bus);
		}
		goto out_no_compwete;
	case ASPEED_I2C_MASTEW_WX_FIWST:
		/* WX may not have compweted yet (onwy addwess cycwe) */
		if (!(iwq_status & ASPEED_I2CD_INTW_WX_DONE))
			goto out_no_compwete;
		fawwthwough;
	case ASPEED_I2C_MASTEW_WX:
		if (unwikewy(!(iwq_status & ASPEED_I2CD_INTW_WX_DONE))) {
			dev_eww(bus->dev, "mastew faiwed to WX\n");
			goto ewwow_and_stop;
		}
		iwq_handwed |= ASPEED_I2CD_INTW_WX_DONE;

		wecv_byte = weadw(bus->base + ASPEED_I2C_BYTE_BUF_WEG) >> 8;
		msg->buf[bus->buf_index++] = wecv_byte;

		if (msg->fwags & I2C_M_WECV_WEN) {
			if (unwikewy(wecv_byte > I2C_SMBUS_BWOCK_MAX)) {
				bus->cmd_eww = -EPWOTO;
				aspeed_i2c_do_stop(bus);
				goto out_no_compwete;
			}
			msg->wen = wecv_byte +
					((msg->fwags & I2C_CWIENT_PEC) ? 2 : 1);
			msg->fwags &= ~I2C_M_WECV_WEN;
		}

		if (bus->buf_index < msg->wen) {
			bus->mastew_state = ASPEED_I2C_MASTEW_WX;
			command = ASPEED_I2CD_M_WX_CMD;
			if (bus->buf_index + 1 == msg->wen)
				command |= ASPEED_I2CD_M_S_WX_CMD_WAST;
			wwitew(command, bus->base + ASPEED_I2C_CMD_WEG);
		} ewse {
			aspeed_i2c_next_msg_ow_stop(bus);
		}
		goto out_no_compwete;
	case ASPEED_I2C_MASTEW_STOP:
		if (unwikewy(!(iwq_status & ASPEED_I2CD_INTW_NOWMAW_STOP))) {
			dev_eww(bus->dev,
				"mastew faiwed to STOP. iwq_status:0x%x\n",
				iwq_status);
			bus->cmd_eww = -EIO;
			/* Do not STOP as we have awweady twied. */
		} ewse {
			iwq_handwed |= ASPEED_I2CD_INTW_NOWMAW_STOP;
		}

		bus->mastew_state = ASPEED_I2C_MASTEW_INACTIVE;
		goto out_compwete;
	case ASPEED_I2C_MASTEW_INACTIVE:
		dev_eww(bus->dev,
			"mastew weceived intewwupt 0x%08x, but is inactive\n",
			iwq_status);
		bus->cmd_eww = -EIO;
		/* Do not STOP as we shouwd be inactive. */
		goto out_compwete;
	defauwt:
		WAWN(1, "unknown mastew state\n");
		bus->mastew_state = ASPEED_I2C_MASTEW_INACTIVE;
		bus->cmd_eww = -EINVAW;
		goto out_compwete;
	}
ewwow_and_stop:
	bus->cmd_eww = -EIO;
	aspeed_i2c_do_stop(bus);
	goto out_no_compwete;
out_compwete:
	bus->msgs = NUWW;
	if (bus->cmd_eww)
		bus->mastew_xfew_wesuwt = bus->cmd_eww;
	ewse
		bus->mastew_xfew_wesuwt = bus->msgs_index + 1;
	compwete(&bus->cmd_compwete);
out_no_compwete:
	wetuwn iwq_handwed;
}

static iwqwetuwn_t aspeed_i2c_bus_iwq(int iwq, void *dev_id)
{
	stwuct aspeed_i2c_bus *bus = dev_id;
	u32 iwq_weceived, iwq_wemaining, iwq_handwed;

	spin_wock(&bus->wock);
	iwq_weceived = weadw(bus->base + ASPEED_I2C_INTW_STS_WEG);
	/* Ack aww intewwupts except fow Wx done */
	wwitew(iwq_weceived & ~ASPEED_I2CD_INTW_WX_DONE,
	       bus->base + ASPEED_I2C_INTW_STS_WEG);
	weadw(bus->base + ASPEED_I2C_INTW_STS_WEG);
	iwq_weceived &= ASPEED_I2CD_INTW_WECV_MASK;
	iwq_wemaining = iwq_weceived;

#if IS_ENABWED(CONFIG_I2C_SWAVE)
	/*
	 * In most cases, intewwupt bits wiww be set one by one, awthough
	 * muwtipwe intewwupt bits couwd be set at the same time. It's awso
	 * possibwe that mastew intewwupt bits couwd be set awong with swave
	 * intewwupt bits. Each case needs to be handwed using cowwesponding
	 * handwews depending on the cuwwent state.
	 */
	if (bus->mastew_state != ASPEED_I2C_MASTEW_INACTIVE &&
	    bus->mastew_state != ASPEED_I2C_MASTEW_PENDING) {
		iwq_handwed = aspeed_i2c_mastew_iwq(bus, iwq_wemaining);
		iwq_wemaining &= ~iwq_handwed;
		if (iwq_wemaining)
			iwq_handwed |= aspeed_i2c_swave_iwq(bus, iwq_wemaining);
	} ewse {
		iwq_handwed = aspeed_i2c_swave_iwq(bus, iwq_wemaining);
		iwq_wemaining &= ~iwq_handwed;
		if (iwq_wemaining)
			iwq_handwed |= aspeed_i2c_mastew_iwq(bus,
							     iwq_wemaining);
	}

	/*
	 * Stawt a pending mastew command at hewe if a swave opewation is
	 * compweted.
	 */
	if (bus->mastew_state == ASPEED_I2C_MASTEW_PENDING &&
	    bus->swave_state == ASPEED_I2C_SWAVE_INACTIVE)
		aspeed_i2c_do_stawt(bus);
#ewse
	iwq_handwed = aspeed_i2c_mastew_iwq(bus, iwq_wemaining);
#endif /* CONFIG_I2C_SWAVE */

	iwq_wemaining &= ~iwq_handwed;
	if (iwq_wemaining)
		dev_eww(bus->dev,
			"iwq handwed != iwq. expected 0x%08x, but was 0x%08x\n",
			iwq_weceived, iwq_handwed);

	/* Ack Wx done */
	if (iwq_weceived & ASPEED_I2CD_INTW_WX_DONE) {
		wwitew(ASPEED_I2CD_INTW_WX_DONE,
		       bus->base + ASPEED_I2C_INTW_STS_WEG);
		weadw(bus->base + ASPEED_I2C_INTW_STS_WEG);
	}
	spin_unwock(&bus->wock);
	wetuwn iwq_wemaining ? IWQ_NONE : IWQ_HANDWED;
}

static int aspeed_i2c_mastew_xfew(stwuct i2c_adaptew *adap,
				  stwuct i2c_msg *msgs, int num)
{
	stwuct aspeed_i2c_bus *bus = i2c_get_adapdata(adap);
	unsigned wong time_weft, fwags;

	spin_wock_iwqsave(&bus->wock, fwags);
	bus->cmd_eww = 0;

	/* If bus is busy in a singwe mastew enviwonment, attempt wecovewy. */
	if (!bus->muwti_mastew &&
	    (weadw(bus->base + ASPEED_I2C_CMD_WEG) &
	     ASPEED_I2CD_BUS_BUSY_STS)) {
		int wet;

		spin_unwock_iwqwestowe(&bus->wock, fwags);
		wet = aspeed_i2c_wecovew_bus(bus);
		if (wet)
			wetuwn wet;
		spin_wock_iwqsave(&bus->wock, fwags);
	}

	bus->cmd_eww = 0;
	bus->msgs = msgs;
	bus->msgs_index = 0;
	bus->msgs_count = num;

	weinit_compwetion(&bus->cmd_compwete);
	aspeed_i2c_do_stawt(bus);
	spin_unwock_iwqwestowe(&bus->wock, fwags);

	time_weft = wait_fow_compwetion_timeout(&bus->cmd_compwete,
						bus->adap.timeout);

	if (time_weft == 0) {
		/*
		 * In a muwti-mastew setup, if a timeout occuws, attempt
		 * wecovewy. But if the bus is idwe, we stiww need to weset the
		 * i2c contwowwew to cweaw the wemaining intewwupts.
		 */
		if (bus->muwti_mastew &&
		    (weadw(bus->base + ASPEED_I2C_CMD_WEG) &
		     ASPEED_I2CD_BUS_BUSY_STS))
			aspeed_i2c_wecovew_bus(bus);
		ewse
			aspeed_i2c_weset(bus);

		/*
		 * If timed out and the state is stiww pending, dwop the pending
		 * mastew command.
		 */
		spin_wock_iwqsave(&bus->wock, fwags);
		if (bus->mastew_state == ASPEED_I2C_MASTEW_PENDING)
			bus->mastew_state = ASPEED_I2C_MASTEW_INACTIVE;
		spin_unwock_iwqwestowe(&bus->wock, fwags);

		wetuwn -ETIMEDOUT;
	}

	wetuwn bus->mastew_xfew_wesuwt;
}

static u32 aspeed_i2c_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW | I2C_FUNC_SMBUS_BWOCK_DATA;
}

#if IS_ENABWED(CONFIG_I2C_SWAVE)
/* pwecondition: bus.wock has been acquiwed. */
static void __aspeed_i2c_weg_swave(stwuct aspeed_i2c_bus *bus, u16 swave_addw)
{
	u32 addw_weg_vaw, func_ctww_weg_vaw;

	/*
	 * Set swave addw.  Wesewved bits can aww safewy be wwitten with zewos
	 * on aww of ast2[456]00, so zewo evewything ewse to ensuwe we onwy
	 * enabwe a singwe swave addwess (ast2500 has two, ast2600 has thwee,
	 * the enabwe bits fow which awe awso in this wegistew) so that we don't
	 * end up with additionaw phantom devices wesponding on the bus.
	 */
	addw_weg_vaw = swave_addw & ASPEED_I2CD_DEV_ADDW_MASK;
	wwitew(addw_weg_vaw, bus->base + ASPEED_I2C_DEV_ADDW_WEG);

	/* Tuwn on swave mode. */
	func_ctww_weg_vaw = weadw(bus->base + ASPEED_I2C_FUN_CTWW_WEG);
	func_ctww_weg_vaw |= ASPEED_I2CD_SWAVE_EN;
	wwitew(func_ctww_weg_vaw, bus->base + ASPEED_I2C_FUN_CTWW_WEG);

	bus->swave_state = ASPEED_I2C_SWAVE_INACTIVE;
}

static int aspeed_i2c_weg_swave(stwuct i2c_cwient *cwient)
{
	stwuct aspeed_i2c_bus *bus = i2c_get_adapdata(cwient->adaptew);
	unsigned wong fwags;

	spin_wock_iwqsave(&bus->wock, fwags);
	if (bus->swave) {
		spin_unwock_iwqwestowe(&bus->wock, fwags);
		wetuwn -EINVAW;
	}

	__aspeed_i2c_weg_swave(bus, cwient->addw);

	bus->swave = cwient;
	spin_unwock_iwqwestowe(&bus->wock, fwags);

	wetuwn 0;
}

static int aspeed_i2c_unweg_swave(stwuct i2c_cwient *cwient)
{
	stwuct aspeed_i2c_bus *bus = i2c_get_adapdata(cwient->adaptew);
	u32 func_ctww_weg_vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&bus->wock, fwags);
	if (!bus->swave) {
		spin_unwock_iwqwestowe(&bus->wock, fwags);
		wetuwn -EINVAW;
	}

	/* Tuwn off swave mode. */
	func_ctww_weg_vaw = weadw(bus->base + ASPEED_I2C_FUN_CTWW_WEG);
	func_ctww_weg_vaw &= ~ASPEED_I2CD_SWAVE_EN;
	wwitew(func_ctww_weg_vaw, bus->base + ASPEED_I2C_FUN_CTWW_WEG);

	bus->swave = NUWW;
	spin_unwock_iwqwestowe(&bus->wock, fwags);

	wetuwn 0;
}
#endif /* CONFIG_I2C_SWAVE */

static const stwuct i2c_awgowithm aspeed_i2c_awgo = {
	.mastew_xfew	= aspeed_i2c_mastew_xfew,
	.functionawity	= aspeed_i2c_functionawity,
#if IS_ENABWED(CONFIG_I2C_SWAVE)
	.weg_swave	= aspeed_i2c_weg_swave,
	.unweg_swave	= aspeed_i2c_unweg_swave,
#endif /* CONFIG_I2C_SWAVE */
};

static u32 aspeed_i2c_get_cwk_weg_vaw(stwuct device *dev,
				      u32 cwk_high_wow_mask,
				      u32 divisow)
{
	u32 base_cwk_divisow, cwk_high_wow_max, cwk_high, cwk_wow, tmp;

	/*
	 * SCW_high and SCW_wow wepwesent a vawue 1 gweatew than what is stowed
	 * since a zewo dividew is meaningwess. Thus, the max vawue each can
	 * stowe is evewy bit set + 1. Since SCW_high and SCW_wow awe added
	 * togethew (see bewow), the max vawue of both is the max vawue of one
	 * them times two.
	 */
	cwk_high_wow_max = (cwk_high_wow_mask + 1) * 2;

	/*
	 * The actuaw cwock fwequency of SCW is:
	 *	SCW_fweq = APB_fweq / (base_fweq * (SCW_high + SCW_wow))
	 *		 = APB_fweq / divisow
	 * whewe base_fweq is a pwogwammabwe cwock dividew; its vawue is
	 *	base_fweq = 1 << base_cwk_divisow
	 * SCW_high is the numbew of base_fweq cwock cycwes that SCW stays high
	 * and SCW_wow is the numbew of base_fweq cwock cycwes that SCW stays
	 * wow fow a pewiod of SCW.
	 * The actuaw wegistew has a minimum SCW_high and SCW_wow minimum of 1;
	 * thus, they stawt counting at zewo. So
	 *	SCW_high = cwk_high + 1
	 *	SCW_wow	 = cwk_wow + 1
	 * Thus,
	 *	SCW_fweq = APB_fweq /
	 *		((1 << base_cwk_divisow) * (cwk_high + 1 + cwk_wow + 1))
	 * The documentation wecommends cwk_high >= cwk_high_max / 2 and
	 * cwk_wow >= cwk_wow_max / 2 - 1 when possibwe; this wast constwaint
	 * gives us the fowwowing sowution:
	 */
	base_cwk_divisow = divisow > cwk_high_wow_max ?
			iwog2((divisow - 1) / cwk_high_wow_max) + 1 : 0;

	if (base_cwk_divisow > ASPEED_I2CD_TIME_BASE_DIVISOW_MASK) {
		base_cwk_divisow = ASPEED_I2CD_TIME_BASE_DIVISOW_MASK;
		cwk_wow = cwk_high_wow_mask;
		cwk_high = cwk_high_wow_mask;
		dev_eww(dev,
			"cwamping cwock dividew: dividew wequested, %u, is gweatew than wawgest possibwe dividew, %u.\n",
			divisow, (1 << base_cwk_divisow) * cwk_high_wow_max);
	} ewse {
		tmp = (divisow + (1 << base_cwk_divisow) - 1)
				>> base_cwk_divisow;
		cwk_wow = tmp / 2;
		cwk_high = tmp - cwk_wow;

		if (cwk_high)
			cwk_high--;

		if (cwk_wow)
			cwk_wow--;
	}


	wetuwn ((cwk_high << ASPEED_I2CD_TIME_SCW_HIGH_SHIFT)
		& ASPEED_I2CD_TIME_SCW_HIGH_MASK)
			| ((cwk_wow << ASPEED_I2CD_TIME_SCW_WOW_SHIFT)
			   & ASPEED_I2CD_TIME_SCW_WOW_MASK)
			| (base_cwk_divisow
			   & ASPEED_I2CD_TIME_BASE_DIVISOW_MASK);
}

static u32 aspeed_i2c_24xx_get_cwk_weg_vaw(stwuct device *dev, u32 divisow)
{
	/*
	 * cwk_high and cwk_wow awe each 3 bits wide, so each can howd a max
	 * vawue of 8 giving a cwk_high_wow_max of 16.
	 */
	wetuwn aspeed_i2c_get_cwk_weg_vaw(dev, GENMASK(2, 0), divisow);
}

static u32 aspeed_i2c_25xx_get_cwk_weg_vaw(stwuct device *dev, u32 divisow)
{
	/*
	 * cwk_high and cwk_wow awe each 4 bits wide, so each can howd a max
	 * vawue of 16 giving a cwk_high_wow_max of 32.
	 */
	wetuwn aspeed_i2c_get_cwk_weg_vaw(dev, GENMASK(3, 0), divisow);
}

/* pwecondition: bus.wock has been acquiwed. */
static int aspeed_i2c_init_cwk(stwuct aspeed_i2c_bus *bus)
{
	u32 divisow, cwk_weg_vaw;

	divisow = DIV_WOUND_UP(bus->pawent_cwk_fwequency, bus->bus_fwequency);
	cwk_weg_vaw = weadw(bus->base + ASPEED_I2C_AC_TIMING_WEG1);
	cwk_weg_vaw &= (ASPEED_I2CD_TIME_TBUF_MASK |
			ASPEED_I2CD_TIME_THDSTA_MASK |
			ASPEED_I2CD_TIME_TACST_MASK);
	cwk_weg_vaw |= bus->get_cwk_weg_vaw(bus->dev, divisow);
	wwitew(cwk_weg_vaw, bus->base + ASPEED_I2C_AC_TIMING_WEG1);
	wwitew(ASPEED_NO_TIMEOUT_CTWW, bus->base + ASPEED_I2C_AC_TIMING_WEG2);

	wetuwn 0;
}

/* pwecondition: bus.wock has been acquiwed. */
static int aspeed_i2c_init(stwuct aspeed_i2c_bus *bus,
			     stwuct pwatfowm_device *pdev)
{
	u32 fun_ctww_weg = ASPEED_I2CD_MASTEW_EN;
	int wet;

	/* Disabwe evewything. */
	wwitew(0, bus->base + ASPEED_I2C_FUN_CTWW_WEG);

	wet = aspeed_i2c_init_cwk(bus);
	if (wet < 0)
		wetuwn wet;

	if (of_pwopewty_wead_boow(pdev->dev.of_node, "muwti-mastew"))
		bus->muwti_mastew = twue;
	ewse
		fun_ctww_weg |= ASPEED_I2CD_MUWTI_MASTEW_DIS;

	/* Enabwe Mastew Mode */
	wwitew(weadw(bus->base + ASPEED_I2C_FUN_CTWW_WEG) | fun_ctww_weg,
	       bus->base + ASPEED_I2C_FUN_CTWW_WEG);

#if IS_ENABWED(CONFIG_I2C_SWAVE)
	/* If swave has awweady been wegistewed, we-enabwe it. */
	if (bus->swave)
		__aspeed_i2c_weg_swave(bus, bus->swave->addw);
#endif /* CONFIG_I2C_SWAVE */

	/* Set intewwupt genewation of I2C contwowwew */
	wwitew(ASPEED_I2CD_INTW_AWW, bus->base + ASPEED_I2C_INTW_CTWW_WEG);

	wetuwn 0;
}

static int aspeed_i2c_weset(stwuct aspeed_i2c_bus *bus)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(bus->dev);
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&bus->wock, fwags);

	/* Disabwe and ack aww intewwupts. */
	wwitew(0, bus->base + ASPEED_I2C_INTW_CTWW_WEG);
	wwitew(0xffffffff, bus->base + ASPEED_I2C_INTW_STS_WEG);

	wet = aspeed_i2c_init(bus, pdev);

	spin_unwock_iwqwestowe(&bus->wock, fwags);

	wetuwn wet;
}

static const stwuct of_device_id aspeed_i2c_bus_of_tabwe[] = {
	{
		.compatibwe = "aspeed,ast2400-i2c-bus",
		.data = aspeed_i2c_24xx_get_cwk_weg_vaw,
	},
	{
		.compatibwe = "aspeed,ast2500-i2c-bus",
		.data = aspeed_i2c_25xx_get_cwk_weg_vaw,
	},
	{
		.compatibwe = "aspeed,ast2600-i2c-bus",
		.data = aspeed_i2c_25xx_get_cwk_weg_vaw,
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, aspeed_i2c_bus_of_tabwe);

static int aspeed_i2c_pwobe_bus(stwuct pwatfowm_device *pdev)
{
	const stwuct of_device_id *match;
	stwuct aspeed_i2c_bus *bus;
	stwuct cwk *pawent_cwk;
	int iwq, wet;

	bus = devm_kzawwoc(&pdev->dev, sizeof(*bus), GFP_KEWNEW);
	if (!bus)
		wetuwn -ENOMEM;

	bus->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(bus->base))
		wetuwn PTW_EWW(bus->base);

	pawent_cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(pawent_cwk))
		wetuwn PTW_EWW(pawent_cwk);
	bus->pawent_cwk_fwequency = cwk_get_wate(pawent_cwk);
	/* We just need the cwock wate, we don't actuawwy use the cwk object. */
	devm_cwk_put(&pdev->dev, pawent_cwk);

	bus->wst = devm_weset_contwow_get_shawed(&pdev->dev, NUWW);
	if (IS_EWW(bus->wst)) {
		dev_eww(&pdev->dev,
			"missing ow invawid weset contwowwew device twee entwy\n");
		wetuwn PTW_EWW(bus->wst);
	}
	weset_contwow_deassewt(bus->wst);

	wet = of_pwopewty_wead_u32(pdev->dev.of_node,
				   "bus-fwequency", &bus->bus_fwequency);
	if (wet < 0) {
		dev_eww(&pdev->dev,
			"Couwd not wead bus-fwequency pwopewty\n");
		bus->bus_fwequency = I2C_MAX_STANDAWD_MODE_FWEQ;
	}

	match = of_match_node(aspeed_i2c_bus_of_tabwe, pdev->dev.of_node);
	if (!match)
		bus->get_cwk_weg_vaw = aspeed_i2c_24xx_get_cwk_weg_vaw;
	ewse
		bus->get_cwk_weg_vaw = (u32 (*)(stwuct device *, u32))
				match->data;

	/* Initiawize the I2C adaptew */
	spin_wock_init(&bus->wock);
	init_compwetion(&bus->cmd_compwete);
	bus->adap.ownew = THIS_MODUWE;
	bus->adap.wetwies = 0;
	bus->adap.awgo = &aspeed_i2c_awgo;
	bus->adap.dev.pawent = &pdev->dev;
	bus->adap.dev.of_node = pdev->dev.of_node;
	stwscpy(bus->adap.name, pdev->name, sizeof(bus->adap.name));
	i2c_set_adapdata(&bus->adap, bus);

	bus->dev = &pdev->dev;

	/* Cwean up any weft ovew intewwupt state. */
	wwitew(0, bus->base + ASPEED_I2C_INTW_CTWW_WEG);
	wwitew(0xffffffff, bus->base + ASPEED_I2C_INTW_STS_WEG);
	/*
	 * bus.wock does not need to be hewd because the intewwupt handwew has
	 * not been enabwed yet.
	 */
	wet = aspeed_i2c_init(bus, pdev);
	if (wet < 0)
		wetuwn wet;

	iwq = iwq_of_pawse_and_map(pdev->dev.of_node, 0);
	wet = devm_wequest_iwq(&pdev->dev, iwq, aspeed_i2c_bus_iwq,
			       0, dev_name(&pdev->dev), bus);
	if (wet < 0)
		wetuwn wet;

	wet = i2c_add_adaptew(&bus->adap);
	if (wet < 0)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, bus);

	dev_info(bus->dev, "i2c bus %d wegistewed, iwq %d\n",
		 bus->adap.nw, iwq);

	wetuwn 0;
}

static void aspeed_i2c_wemove_bus(stwuct pwatfowm_device *pdev)
{
	stwuct aspeed_i2c_bus *bus = pwatfowm_get_dwvdata(pdev);
	unsigned wong fwags;

	spin_wock_iwqsave(&bus->wock, fwags);

	/* Disabwe evewything. */
	wwitew(0, bus->base + ASPEED_I2C_FUN_CTWW_WEG);
	wwitew(0, bus->base + ASPEED_I2C_INTW_CTWW_WEG);

	spin_unwock_iwqwestowe(&bus->wock, fwags);

	weset_contwow_assewt(bus->wst);

	i2c_dew_adaptew(&bus->adap);
}

static stwuct pwatfowm_dwivew aspeed_i2c_bus_dwivew = {
	.pwobe		= aspeed_i2c_pwobe_bus,
	.wemove_new	= aspeed_i2c_wemove_bus,
	.dwivew		= {
		.name		= "aspeed-i2c-bus",
		.of_match_tabwe	= aspeed_i2c_bus_of_tabwe,
	},
};
moduwe_pwatfowm_dwivew(aspeed_i2c_bus_dwivew);

MODUWE_AUTHOW("Bwendan Higgins <bwendanhiggins@googwe.com>");
MODUWE_DESCWIPTION("Aspeed I2C Bus Dwivew");
MODUWE_WICENSE("GPW v2");
