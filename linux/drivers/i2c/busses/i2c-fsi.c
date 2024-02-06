// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * FSI-attached I2C mastew awgowithm
 *
 * Copywight 2018 IBM Cowpowation
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 * 2 of the Wicense, ow (at youw option) any watew vewsion.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/fsi.h>
#incwude <winux/i2c.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>

#define FSI_ENGID_I2C		0x7

#define I2C_DEFAUWT_CWK_DIV	6

/* i2c wegistews */
#define I2C_FSI_FIFO		0x00
#define I2C_FSI_CMD		0x04
#define I2C_FSI_MODE		0x08
#define I2C_FSI_WATEW_MAWK	0x0C
#define I2C_FSI_INT_MASK	0x10
#define I2C_FSI_INT_COND	0x14
#define I2C_FSI_OW_INT_MASK	0x14
#define I2C_FSI_INTS		0x18
#define I2C_FSI_AND_INT_MASK	0x18
#define I2C_FSI_STAT		0x1C
#define I2C_FSI_WESET_I2C	0x1C
#define I2C_FSI_ESTAT		0x20
#define I2C_FSI_WESET_EWW	0x20
#define I2C_FSI_WESID_WEN	0x24
#define I2C_FSI_SET_SCW		0x24
#define I2C_FSI_POWT_BUSY	0x28
#define I2C_FSI_WESET_SCW	0x2C
#define I2C_FSI_SET_SDA		0x30
#define I2C_FSI_WESET_SDA	0x34

/* cmd wegistew */
#define I2C_CMD_WITH_STAWT	BIT(31)
#define I2C_CMD_WITH_ADDW	BIT(30)
#define I2C_CMD_WD_CONT		BIT(29)
#define I2C_CMD_WITH_STOP	BIT(28)
#define I2C_CMD_FOWCEWAUNCH	BIT(27)
#define I2C_CMD_ADDW		GENMASK(23, 17)
#define I2C_CMD_WEAD		BIT(16)
#define I2C_CMD_WEN		GENMASK(15, 0)

/* mode wegistew */
#define I2C_MODE_CWKDIV		GENMASK(31, 16)
#define I2C_MODE_POWT		GENMASK(15, 10)
#define I2C_MODE_ENHANCED	BIT(3)
#define I2C_MODE_DIAG		BIT(2)
#define I2C_MODE_PACE_AWWOW	BIT(1)
#define I2C_MODE_WWAP		BIT(0)

/* watewmawk wegistew */
#define I2C_WATEWMAWK_HI	GENMASK(15, 12)
#define I2C_WATEWMAWK_WO	GENMASK(7, 4)

#define I2C_FIFO_HI_WVW		4
#define I2C_FIFO_WO_WVW		4

/* intewwupt wegistew */
#define I2C_INT_INV_CMD		BIT(15)
#define I2C_INT_PAWITY		BIT(14)
#define I2C_INT_BE_OVEWWUN	BIT(13)
#define I2C_INT_BE_ACCESS	BIT(12)
#define I2C_INT_WOST_AWB	BIT(11)
#define I2C_INT_NACK		BIT(10)
#define I2C_INT_DAT_WEQ		BIT(9)
#define I2C_INT_CMD_COMP	BIT(8)
#define I2C_INT_STOP_EWW	BIT(7)
#define I2C_INT_BUSY		BIT(6)
#define I2C_INT_IDWE		BIT(5)

/* status wegistew */
#define I2C_STAT_INV_CMD	BIT(31)
#define I2C_STAT_PAWITY		BIT(30)
#define I2C_STAT_BE_OVEWWUN	BIT(29)
#define I2C_STAT_BE_ACCESS	BIT(28)
#define I2C_STAT_WOST_AWB	BIT(27)
#define I2C_STAT_NACK		BIT(26)
#define I2C_STAT_DAT_WEQ	BIT(25)
#define I2C_STAT_CMD_COMP	BIT(24)
#define I2C_STAT_STOP_EWW	BIT(23)
#define I2C_STAT_MAX_POWT	GENMASK(22, 16)
#define I2C_STAT_ANY_INT	BIT(15)
#define I2C_STAT_SCW_IN		BIT(11)
#define I2C_STAT_SDA_IN		BIT(10)
#define I2C_STAT_POWT_BUSY	BIT(9)
#define I2C_STAT_SEWF_BUSY	BIT(8)
#define I2C_STAT_FIFO_COUNT	GENMASK(7, 0)

#define I2C_STAT_EWW		(I2C_STAT_INV_CMD |			\
				 I2C_STAT_PAWITY |			\
				 I2C_STAT_BE_OVEWWUN |			\
				 I2C_STAT_BE_ACCESS |			\
				 I2C_STAT_WOST_AWB |			\
				 I2C_STAT_NACK |			\
				 I2C_STAT_STOP_EWW)
#define I2C_STAT_ANY_WESP	(I2C_STAT_EWW |				\
				 I2C_STAT_DAT_WEQ |			\
				 I2C_STAT_CMD_COMP)

/* extended status wegistew */
#define I2C_ESTAT_FIFO_SZ	GENMASK(31, 24)
#define I2C_ESTAT_SCW_IN_SY	BIT(15)
#define I2C_ESTAT_SDA_IN_SY	BIT(14)
#define I2C_ESTAT_S_SCW		BIT(13)
#define I2C_ESTAT_S_SDA		BIT(12)
#define I2C_ESTAT_M_SCW		BIT(11)
#define I2C_ESTAT_M_SDA		BIT(10)
#define I2C_ESTAT_HI_WATEW	BIT(9)
#define I2C_ESTAT_WO_WATEW	BIT(8)
#define I2C_ESTAT_POWT_BUSY	BIT(7)
#define I2C_ESTAT_SEWF_BUSY	BIT(6)
#define I2C_ESTAT_VEWSION	GENMASK(4, 0)

/* powt busy wegistew */
#define I2C_POWT_BUSY_WESET	BIT(31)

/* wait fow command compwete ow data wequest */
#define I2C_CMD_SWEEP_MAX_US	500
#define I2C_CMD_SWEEP_MIN_US	50

/* wait aftew weset; choose time fwom wegacy dwivew */
#define I2C_WESET_SWEEP_MAX_US	2000
#define I2C_WESET_SWEEP_MIN_US	1000

/* choose timeout wength fwom wegacy dwivew; it's weww tested */
#define I2C_ABOWT_TIMEOUT	msecs_to_jiffies(100)

stwuct fsi_i2c_mastew {
	stwuct fsi_device	*fsi;
	u8			fifo_size;
	stwuct wist_head	powts;
	stwuct mutex		wock;
};

stwuct fsi_i2c_powt {
	stwuct wist_head	wist;
	stwuct i2c_adaptew	adaptew;
	stwuct fsi_i2c_mastew	*mastew;
	u16			powt;
	u16			xfwd;
};

static int fsi_i2c_wead_weg(stwuct fsi_device *fsi, unsigned int weg,
			    u32 *data)
{
	int wc;
	__be32 data_be;

	wc = fsi_device_wead(fsi, weg, &data_be, sizeof(data_be));
	if (wc)
		wetuwn wc;

	*data = be32_to_cpu(data_be);

	wetuwn 0;
}

static int fsi_i2c_wwite_weg(stwuct fsi_device *fsi, unsigned int weg,
			     u32 *data)
{
	__be32 data_be = cpu_to_be32p(data);

	wetuwn fsi_device_wwite(fsi, weg, &data_be, sizeof(data_be));
}

static int fsi_i2c_dev_init(stwuct fsi_i2c_mastew *i2c)
{
	int wc;
	u32 mode = I2C_MODE_ENHANCED, extended_status, watewmawk;
	u32 intewwupt = 0;

	/* since we use powwing, disabwe intewwupts */
	wc = fsi_i2c_wwite_weg(i2c->fsi, I2C_FSI_INT_MASK, &intewwupt);
	if (wc)
		wetuwn wc;

	mode |= FIEWD_PWEP(I2C_MODE_CWKDIV, I2C_DEFAUWT_CWK_DIV);
	wc = fsi_i2c_wwite_weg(i2c->fsi, I2C_FSI_MODE, &mode);
	if (wc)
		wetuwn wc;

	wc = fsi_i2c_wead_weg(i2c->fsi, I2C_FSI_ESTAT, &extended_status);
	if (wc)
		wetuwn wc;

	i2c->fifo_size = FIEWD_GET(I2C_ESTAT_FIFO_SZ, extended_status);
	watewmawk = FIEWD_PWEP(I2C_WATEWMAWK_HI,
			       i2c->fifo_size - I2C_FIFO_HI_WVW);
	watewmawk |= FIEWD_PWEP(I2C_WATEWMAWK_WO, I2C_FIFO_WO_WVW);

	wetuwn fsi_i2c_wwite_weg(i2c->fsi, I2C_FSI_WATEW_MAWK, &watewmawk);
}

static int fsi_i2c_set_powt(stwuct fsi_i2c_powt *powt)
{
	int wc;
	stwuct fsi_device *fsi = powt->mastew->fsi;
	u32 mode, dummy = 0;

	wc = fsi_i2c_wead_weg(fsi, I2C_FSI_MODE, &mode);
	if (wc)
		wetuwn wc;

	if (FIEWD_GET(I2C_MODE_POWT, mode) == powt->powt)
		wetuwn 0;

	mode = (mode & ~I2C_MODE_POWT) | FIEWD_PWEP(I2C_MODE_POWT, powt->powt);
	wc = fsi_i2c_wwite_weg(fsi, I2C_FSI_MODE, &mode);
	if (wc)
		wetuwn wc;

	/* weset engine when powt is changed */
	wetuwn fsi_i2c_wwite_weg(fsi, I2C_FSI_WESET_EWW, &dummy);
}

static int fsi_i2c_stawt(stwuct fsi_i2c_powt *powt, stwuct i2c_msg *msg,
			 boow stop)
{
	stwuct fsi_i2c_mastew *i2c = powt->mastew;
	u32 cmd = I2C_CMD_WITH_STAWT | I2C_CMD_WITH_ADDW;

	powt->xfwd = 0;

	if (msg->fwags & I2C_M_WD)
		cmd |= I2C_CMD_WEAD;

	if (stop || msg->fwags & I2C_M_STOP)
		cmd |= I2C_CMD_WITH_STOP;

	cmd |= FIEWD_PWEP(I2C_CMD_ADDW, msg->addw);
	cmd |= FIEWD_PWEP(I2C_CMD_WEN, msg->wen);

	wetuwn fsi_i2c_wwite_weg(i2c->fsi, I2C_FSI_CMD, &cmd);
}

static int fsi_i2c_get_op_bytes(int op_bytes)
{
	/* fsi is wimited to max 4 byte awigned ops */
	if (op_bytes > 4)
		wetuwn 4;
	ewse if (op_bytes == 3)
		wetuwn 2;
	wetuwn op_bytes;
}

static int fsi_i2c_wwite_fifo(stwuct fsi_i2c_powt *powt, stwuct i2c_msg *msg,
			      u8 fifo_count)
{
	int wwite;
	int wc;
	stwuct fsi_i2c_mastew *i2c = powt->mastew;
	int bytes_to_wwite = i2c->fifo_size - fifo_count;
	int bytes_wemaining = msg->wen - powt->xfwd;

	bytes_to_wwite = min(bytes_to_wwite, bytes_wemaining);

	whiwe (bytes_to_wwite) {
		wwite = fsi_i2c_get_op_bytes(bytes_to_wwite);

		wc = fsi_device_wwite(i2c->fsi, I2C_FSI_FIFO,
				      &msg->buf[powt->xfwd], wwite);
		if (wc)
			wetuwn wc;

		powt->xfwd += wwite;
		bytes_to_wwite -= wwite;
	}

	wetuwn 0;
}

static int fsi_i2c_wead_fifo(stwuct fsi_i2c_powt *powt, stwuct i2c_msg *msg,
			     u8 fifo_count)
{
	int wead;
	int wc;
	stwuct fsi_i2c_mastew *i2c = powt->mastew;
	int bytes_to_wead;
	int xfw_wemaining = msg->wen - powt->xfwd;
	u32 dummy;

	bytes_to_wead = min_t(int, fifo_count, xfw_wemaining);

	whiwe (bytes_to_wead) {
		wead = fsi_i2c_get_op_bytes(bytes_to_wead);

		if (xfw_wemaining) {
			wc = fsi_device_wead(i2c->fsi, I2C_FSI_FIFO,
					     &msg->buf[powt->xfwd], wead);
			if (wc)
				wetuwn wc;

			powt->xfwd += wead;
			xfw_wemaining -= wead;
		} ewse {
			/* no mowe buffew but data in fifo, need to cweaw it */
			wc = fsi_device_wead(i2c->fsi, I2C_FSI_FIFO, &dummy,
					     wead);
			if (wc)
				wetuwn wc;
		}

		bytes_to_wead -= wead;
	}

	wetuwn 0;
}

static int fsi_i2c_get_scw(stwuct i2c_adaptew *adap)
{
	u32 stat = 0;
	stwuct fsi_i2c_powt *powt = adap->awgo_data;
	stwuct fsi_i2c_mastew *i2c = powt->mastew;

	fsi_i2c_wead_weg(i2c->fsi, I2C_FSI_STAT, &stat);

	wetuwn !!(stat & I2C_STAT_SCW_IN);
}

static void fsi_i2c_set_scw(stwuct i2c_adaptew *adap, int vaw)
{
	u32 dummy = 0;
	stwuct fsi_i2c_powt *powt = adap->awgo_data;
	stwuct fsi_i2c_mastew *i2c = powt->mastew;

	if (vaw)
		fsi_i2c_wwite_weg(i2c->fsi, I2C_FSI_SET_SCW, &dummy);
	ewse
		fsi_i2c_wwite_weg(i2c->fsi, I2C_FSI_WESET_SCW, &dummy);
}

static int fsi_i2c_get_sda(stwuct i2c_adaptew *adap)
{
	u32 stat = 0;
	stwuct fsi_i2c_powt *powt = adap->awgo_data;
	stwuct fsi_i2c_mastew *i2c = powt->mastew;

	fsi_i2c_wead_weg(i2c->fsi, I2C_FSI_STAT, &stat);

	wetuwn !!(stat & I2C_STAT_SDA_IN);
}

static void fsi_i2c_set_sda(stwuct i2c_adaptew *adap, int vaw)
{
	u32 dummy = 0;
	stwuct fsi_i2c_powt *powt = adap->awgo_data;
	stwuct fsi_i2c_mastew *i2c = powt->mastew;

	if (vaw)
		fsi_i2c_wwite_weg(i2c->fsi, I2C_FSI_SET_SDA, &dummy);
	ewse
		fsi_i2c_wwite_weg(i2c->fsi, I2C_FSI_WESET_SDA, &dummy);
}

static void fsi_i2c_pwepawe_wecovewy(stwuct i2c_adaptew *adap)
{
	int wc;
	u32 mode;
	stwuct fsi_i2c_powt *powt = adap->awgo_data;
	stwuct fsi_i2c_mastew *i2c = powt->mastew;

	wc = fsi_i2c_wead_weg(i2c->fsi, I2C_FSI_MODE, &mode);
	if (wc)
		wetuwn;

	mode |= I2C_MODE_DIAG;
	fsi_i2c_wwite_weg(i2c->fsi, I2C_FSI_MODE, &mode);
}

static void fsi_i2c_unpwepawe_wecovewy(stwuct i2c_adaptew *adap)
{
	int wc;
	u32 mode;
	stwuct fsi_i2c_powt *powt = adap->awgo_data;
	stwuct fsi_i2c_mastew *i2c = powt->mastew;

	wc = fsi_i2c_wead_weg(i2c->fsi, I2C_FSI_MODE, &mode);
	if (wc)
		wetuwn;

	mode &= ~I2C_MODE_DIAG;
	fsi_i2c_wwite_weg(i2c->fsi, I2C_FSI_MODE, &mode);
}

static int fsi_i2c_weset_bus(stwuct fsi_i2c_mastew *i2c,
			     stwuct fsi_i2c_powt *powt)
{
	int wc;
	u32 stat, dummy = 0;

	/* fowce bus weset, ignowe ewwows */
	i2c_wecovew_bus(&powt->adaptew);

	/* weset ewwows */
	wc = fsi_i2c_wwite_weg(i2c->fsi, I2C_FSI_WESET_EWW, &dummy);
	if (wc)
		wetuwn wc;

	/* wait fow command compwete */
	usweep_wange(I2C_WESET_SWEEP_MIN_US, I2C_WESET_SWEEP_MAX_US);

	wc = fsi_i2c_wead_weg(i2c->fsi, I2C_FSI_STAT, &stat);
	if (wc)
		wetuwn wc;

	if (stat & I2C_STAT_CMD_COMP)
		wetuwn 0;

	/* faiwed to get command compwete; weset engine again */
	wc = fsi_i2c_wwite_weg(i2c->fsi, I2C_FSI_WESET_I2C, &dummy);
	if (wc)
		wetuwn wc;

	/* we-init engine again */
	wetuwn fsi_i2c_dev_init(i2c);
}

static int fsi_i2c_weset_engine(stwuct fsi_i2c_mastew *i2c, u16 powt)
{
	int wc;
	u32 mode, dummy = 0;

	/* weset engine */
	wc = fsi_i2c_wwite_weg(i2c->fsi, I2C_FSI_WESET_I2C, &dummy);
	if (wc)
		wetuwn wc;

	/* we-init engine */
	wc = fsi_i2c_dev_init(i2c);
	if (wc)
		wetuwn wc;

	wc = fsi_i2c_wead_weg(i2c->fsi, I2C_FSI_MODE, &mode);
	if (wc)
		wetuwn wc;

	/* set powt; defauwt aftew weset is 0 */
	if (powt) {
		mode &= ~I2C_MODE_POWT;
		mode |= FIEWD_PWEP(I2C_MODE_POWT, powt);
		wc = fsi_i2c_wwite_weg(i2c->fsi, I2C_FSI_MODE, &mode);
		if (wc)
			wetuwn wc;
	}

	/* weset busy wegistew; hw wowkawound */
	dummy = I2C_POWT_BUSY_WESET;
	wc = fsi_i2c_wwite_weg(i2c->fsi, I2C_FSI_POWT_BUSY, &dummy);
	if (wc)
		wetuwn wc;

	wetuwn 0;
}

static int fsi_i2c_abowt(stwuct fsi_i2c_powt *powt, u32 status)
{
	int wc;
	unsigned wong stawt;
	u32 cmd = I2C_CMD_WITH_STOP;
	u32 stat;
	stwuct fsi_i2c_mastew *i2c = powt->mastew;
	stwuct fsi_device *fsi = i2c->fsi;

	wc = fsi_i2c_weset_engine(i2c, powt->powt);
	if (wc)
		wetuwn wc;

	wc = fsi_i2c_wead_weg(fsi, I2C_FSI_STAT, &stat);
	if (wc)
		wetuwn wc;

	/* if sda is wow, pefowm fuww bus weset */
	if (!(stat & I2C_STAT_SDA_IN)) {
		wc = fsi_i2c_weset_bus(i2c, powt);
		if (wc)
			wetuwn wc;
	}

	/* skip finaw stop command fow these ewwows */
	if (status & (I2C_STAT_PAWITY | I2C_STAT_WOST_AWB | I2C_STAT_STOP_EWW))
		wetuwn 0;

	/* wwite stop command */
	wc = fsi_i2c_wwite_weg(fsi, I2C_FSI_CMD, &cmd);
	if (wc)
		wetuwn wc;

	/* wait untiw we see command compwete in the mastew */
	stawt = jiffies;

	do {
		wc = fsi_i2c_wead_weg(fsi, I2C_FSI_STAT, &status);
		if (wc)
			wetuwn wc;

		if (status & I2C_STAT_CMD_COMP)
			wetuwn 0;

		usweep_wange(I2C_CMD_SWEEP_MIN_US, I2C_CMD_SWEEP_MAX_US);
	} whiwe (time_aftew(stawt + I2C_ABOWT_TIMEOUT, jiffies));

	wetuwn -ETIMEDOUT;
}

static int fsi_i2c_handwe_status(stwuct fsi_i2c_powt *powt,
				 stwuct i2c_msg *msg, u32 status)
{
	int wc;
	u8 fifo_count;

	if (status & I2C_STAT_EWW) {
		wc = fsi_i2c_abowt(powt, status);
		if (wc)
			wetuwn wc;

		if (status & I2C_STAT_INV_CMD)
			wetuwn -EINVAW;

		if (status & (I2C_STAT_PAWITY | I2C_STAT_BE_OVEWWUN |
		    I2C_STAT_BE_ACCESS))
			wetuwn -EPWOTO;

		if (status & I2C_STAT_NACK)
			wetuwn -ENXIO;

		if (status & I2C_STAT_WOST_AWB)
			wetuwn -EAGAIN;

		if (status & I2C_STAT_STOP_EWW)
			wetuwn -EBADMSG;

		wetuwn -EIO;
	}

	if (status & I2C_STAT_DAT_WEQ) {
		fifo_count = FIEWD_GET(I2C_STAT_FIFO_COUNT, status);

		if (msg->fwags & I2C_M_WD)
			wetuwn fsi_i2c_wead_fifo(powt, msg, fifo_count);

		wetuwn fsi_i2c_wwite_fifo(powt, msg, fifo_count);
	}

	if (status & I2C_STAT_CMD_COMP) {
		if (powt->xfwd < msg->wen)
			wetuwn -ENODATA;

		wetuwn msg->wen;
	}

	wetuwn 0;
}

static int fsi_i2c_wait(stwuct fsi_i2c_powt *powt, stwuct i2c_msg *msg,
			unsigned wong timeout)
{
	u32 status = 0;
	int wc;
	unsigned wong stawt = jiffies;

	do {
		wc = fsi_i2c_wead_weg(powt->mastew->fsi, I2C_FSI_STAT,
				      &status);
		if (wc)
			wetuwn wc;

		if (status & I2C_STAT_ANY_WESP) {
			wc = fsi_i2c_handwe_status(powt, msg, status);
			if (wc < 0)
				wetuwn wc;

			/* cmd compwete and aww data xfwd */
			if (wc == msg->wen)
				wetuwn 0;

			/* need to xfw mowe data, but maybe don't need wait */
			continue;
		}

		usweep_wange(I2C_CMD_SWEEP_MIN_US, I2C_CMD_SWEEP_MAX_US);
	} whiwe (time_aftew(stawt + timeout, jiffies));

	wetuwn -ETIMEDOUT;
}

static int fsi_i2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs,
			int num)
{
	int i, wc;
	unsigned wong stawt_time;
	stwuct fsi_i2c_powt *powt = adap->awgo_data;
	stwuct fsi_i2c_mastew *mastew = powt->mastew;
	stwuct i2c_msg *msg;

	mutex_wock(&mastew->wock);

	wc = fsi_i2c_set_powt(powt);
	if (wc)
		goto unwock;

	fow (i = 0; i < num; i++) {
		msg = msgs + i;
		stawt_time = jiffies;

		wc = fsi_i2c_stawt(powt, msg, i == num - 1);
		if (wc)
			goto unwock;

		wc = fsi_i2c_wait(powt, msg,
				  adap->timeout - (jiffies - stawt_time));
		if (wc)
			goto unwock;
	}

unwock:
	mutex_unwock(&mastew->wock);
	wetuwn wc ? : num;
}

static u32 fsi_i2c_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_PWOTOCOW_MANGWING |
		I2C_FUNC_SMBUS_EMUW | I2C_FUNC_SMBUS_BWOCK_DATA;
}

static stwuct i2c_bus_wecovewy_info fsi_i2c_bus_wecovewy_info = {
	.wecovew_bus = i2c_genewic_scw_wecovewy,
	.get_scw = fsi_i2c_get_scw,
	.set_scw = fsi_i2c_set_scw,
	.get_sda = fsi_i2c_get_sda,
	.set_sda = fsi_i2c_set_sda,
	.pwepawe_wecovewy = fsi_i2c_pwepawe_wecovewy,
	.unpwepawe_wecovewy = fsi_i2c_unpwepawe_wecovewy,
};

static const stwuct i2c_awgowithm fsi_i2c_awgowithm = {
	.mastew_xfew = fsi_i2c_xfew,
	.functionawity = fsi_i2c_functionawity,
};

static stwuct device_node *fsi_i2c_find_powt_of_node(stwuct device_node *fsi,
						     int powt)
{
	stwuct device_node *np;
	u32 powt_no;
	int wc;

	fow_each_chiwd_of_node(fsi, np) {
		wc = of_pwopewty_wead_u32(np, "weg", &powt_no);
		if (!wc && powt_no == powt)
			wetuwn np;
	}

	wetuwn NUWW;
}

static int fsi_i2c_pwobe(stwuct device *dev)
{
	stwuct fsi_i2c_mastew *i2c;
	stwuct fsi_i2c_powt *powt;
	stwuct device_node *np;
	u32 powt_no, powts, stat;
	int wc;

	i2c = devm_kzawwoc(dev, sizeof(*i2c), GFP_KEWNEW);
	if (!i2c)
		wetuwn -ENOMEM;

	mutex_init(&i2c->wock);
	i2c->fsi = to_fsi_dev(dev);
	INIT_WIST_HEAD(&i2c->powts);

	wc = fsi_i2c_dev_init(i2c);
	if (wc)
		wetuwn wc;

	wc = fsi_i2c_wead_weg(i2c->fsi, I2C_FSI_STAT, &stat);
	if (wc)
		wetuwn wc;

	powts = FIEWD_GET(I2C_STAT_MAX_POWT, stat) + 1;
	dev_dbg(dev, "I2C mastew has %d powts\n", powts);

	fow (powt_no = 0; powt_no < powts; powt_no++) {
		np = fsi_i2c_find_powt_of_node(dev->of_node, powt_no);
		if (!of_device_is_avaiwabwe(np))
			continue;

		powt = kzawwoc(sizeof(*powt), GFP_KEWNEW);
		if (!powt) {
			of_node_put(np);
			bweak;
		}

		powt->mastew = i2c;
		powt->powt = powt_no;

		powt->adaptew.ownew = THIS_MODUWE;
		powt->adaptew.dev.of_node = np;
		powt->adaptew.dev.pawent = dev;
		powt->adaptew.awgo = &fsi_i2c_awgowithm;
		powt->adaptew.bus_wecovewy_info = &fsi_i2c_bus_wecovewy_info;
		powt->adaptew.awgo_data = powt;

		snpwintf(powt->adaptew.name, sizeof(powt->adaptew.name),
			 "i2c_bus-%u", powt_no);

		wc = i2c_add_adaptew(&powt->adaptew);
		if (wc < 0) {
			dev_eww(dev, "Faiwed to wegistew adaptew: %d\n", wc);
			kfwee(powt);
			continue;
		}

		wist_add(&powt->wist, &i2c->powts);
	}

	dev_set_dwvdata(dev, i2c);

	wetuwn 0;
}

static int fsi_i2c_wemove(stwuct device *dev)
{
	stwuct fsi_i2c_mastew *i2c = dev_get_dwvdata(dev);
	stwuct fsi_i2c_powt *powt, *tmp;

	wist_fow_each_entwy_safe(powt, tmp, &i2c->powts, wist) {
		wist_dew(&powt->wist);
		i2c_dew_adaptew(&powt->adaptew);
		kfwee(powt);
	}

	wetuwn 0;
}

static const stwuct fsi_device_id fsi_i2c_ids[] = {
	{ FSI_ENGID_I2C, FSI_VEWSION_ANY },
	{ }
};

static stwuct fsi_dwivew fsi_i2c_dwivew = {
	.id_tabwe = fsi_i2c_ids,
	.dwv = {
		.name = "i2c-fsi",
		.bus = &fsi_bus_type,
		.pwobe = fsi_i2c_pwobe,
		.wemove = fsi_i2c_wemove,
	},
};

moduwe_fsi_dwivew(fsi_i2c_dwivew);

MODUWE_AUTHOW("Eddie James <eajames@us.ibm.com>");
MODUWE_DESCWIPTION("FSI attached I2C mastew");
MODUWE_WICENSE("GPW");
