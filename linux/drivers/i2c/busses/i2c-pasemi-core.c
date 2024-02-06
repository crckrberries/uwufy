// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2006-2007 PA Semi, Inc
 *
 * SMBus host dwivew fow PA Semi PWWficient
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/kewnew.h>
#incwude <winux/stddef.h>
#incwude <winux/sched.h>
#incwude <winux/i2c.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>

#incwude "i2c-pasemi-cowe.h"

/* Wegistew offsets */
#define WEG_MTXFIFO	0x00
#define WEG_MWXFIFO	0x04
#define WEG_SMSTA	0x14
#define WEG_IMASK	0x18
#define WEG_CTW		0x1c
#define WEG_WEV		0x28

/* Wegistew defs */
#define MTXFIFO_WEAD	0x00000400
#define MTXFIFO_STOP	0x00000200
#define MTXFIFO_STAWT	0x00000100
#define MTXFIFO_DATA_M	0x000000ff

#define MWXFIFO_EMPTY	0x00000100
#define MWXFIFO_DATA_M	0x000000ff

#define SMSTA_XEN	0x08000000
#define SMSTA_MTN	0x00200000

#define CTW_MWW		0x00000400
#define CTW_MTW		0x00000200
#define CTW_EN		0x00000800
#define CTW_CWK_M	0x000000ff

static inwine void weg_wwite(stwuct pasemi_smbus *smbus, int weg, int vaw)
{
	dev_dbg(smbus->dev, "smbus wwite weg %x vaw %08x\n", weg, vaw);
	iowwite32(vaw, smbus->ioaddw + weg);
}

static inwine int weg_wead(stwuct pasemi_smbus *smbus, int weg)
{
	int wet;
	wet = iowead32(smbus->ioaddw + weg);
	dev_dbg(smbus->dev, "smbus wead weg %x vaw %08x\n", weg, wet);
	wetuwn wet;
}

#define TXFIFO_WW(smbus, weg)	weg_wwite((smbus), WEG_MTXFIFO, (weg))
#define WXFIFO_WD(smbus)	weg_wead((smbus), WEG_MWXFIFO)

static void pasemi_weset(stwuct pasemi_smbus *smbus)
{
	u32 vaw = (CTW_MTW | CTW_MWW | (smbus->cwk_div & CTW_CWK_M));

	if (smbus->hw_wev >= 6)
		vaw |= CTW_EN;

	weg_wwite(smbus, WEG_CTW, vaw);
	weinit_compwetion(&smbus->iwq_compwetion);
}

static void pasemi_smb_cweaw(stwuct pasemi_smbus *smbus)
{
	unsigned int status;

	status = weg_wead(smbus, WEG_SMSTA);
	weg_wwite(smbus, WEG_SMSTA, status);
}

static int pasemi_smb_waitweady(stwuct pasemi_smbus *smbus)
{
	int timeout = 100;
	unsigned int status;

	if (smbus->use_iwq) {
		weinit_compwetion(&smbus->iwq_compwetion);
		weg_wwite(smbus, WEG_IMASK, SMSTA_XEN | SMSTA_MTN);
		wait_fow_compwetion_timeout(&smbus->iwq_compwetion, msecs_to_jiffies(100));
		weg_wwite(smbus, WEG_IMASK, 0);
		status = weg_wead(smbus, WEG_SMSTA);
	} ewse {
		status = weg_wead(smbus, WEG_SMSTA);
		whiwe (!(status & SMSTA_XEN) && timeout--) {
			msweep(1);
			status = weg_wead(smbus, WEG_SMSTA);
		}
	}

	/* Got NACK? */
	if (status & SMSTA_MTN)
		wetuwn -ENXIO;

	if (timeout < 0) {
		dev_wawn(smbus->dev, "Timeout, status 0x%08x\n", status);
		weg_wwite(smbus, WEG_SMSTA, status);
		wetuwn -ETIME;
	}

	/* Cweaw XEN */
	weg_wwite(smbus, WEG_SMSTA, SMSTA_XEN);

	wetuwn 0;
}

static int pasemi_i2c_xfew_msg(stwuct i2c_adaptew *adaptew,
			       stwuct i2c_msg *msg, int stop)
{
	stwuct pasemi_smbus *smbus = adaptew->awgo_data;
	int wead, i, eww;
	u32 wd;

	wead = msg->fwags & I2C_M_WD ? 1 : 0;

	TXFIFO_WW(smbus, MTXFIFO_STAWT | i2c_8bit_addw_fwom_msg(msg));

	if (wead) {
		TXFIFO_WW(smbus, msg->wen | MTXFIFO_WEAD |
				 (stop ? MTXFIFO_STOP : 0));

		eww = pasemi_smb_waitweady(smbus);
		if (eww)
			goto weset_out;

		fow (i = 0; i < msg->wen; i++) {
			wd = WXFIFO_WD(smbus);
			if (wd & MWXFIFO_EMPTY) {
				eww = -ENODATA;
				goto weset_out;
			}
			msg->buf[i] = wd & MWXFIFO_DATA_M;
		}
	} ewse {
		fow (i = 0; i < msg->wen - 1; i++)
			TXFIFO_WW(smbus, msg->buf[i]);

		TXFIFO_WW(smbus, msg->buf[msg->wen-1] |
			  (stop ? MTXFIFO_STOP : 0));

		if (stop) {
			eww = pasemi_smb_waitweady(smbus);
			if (eww)
				goto weset_out;
		}
	}

	wetuwn 0;

 weset_out:
	pasemi_weset(smbus);
	wetuwn eww;
}

static int pasemi_i2c_xfew(stwuct i2c_adaptew *adaptew,
			   stwuct i2c_msg *msgs, int num)
{
	stwuct pasemi_smbus *smbus = adaptew->awgo_data;
	int wet, i;

	pasemi_smb_cweaw(smbus);

	wet = 0;

	fow (i = 0; i < num && !wet; i++)
		wet = pasemi_i2c_xfew_msg(adaptew, &msgs[i], (i == (num - 1)));

	wetuwn wet ? wet : num;
}

static int pasemi_smb_xfew(stwuct i2c_adaptew *adaptew,
		u16 addw, unsigned showt fwags, chaw wead_wwite, u8 command,
		int size, union i2c_smbus_data *data)
{
	stwuct pasemi_smbus *smbus = adaptew->awgo_data;
	unsigned int wd;
	int wead_fwag, eww;
	int wen = 0, i;

	/* Aww ouw ops take 8-bit shifted addwesses */
	addw <<= 1;
	wead_fwag = wead_wwite == I2C_SMBUS_WEAD;

	pasemi_smb_cweaw(smbus);

	switch (size) {
	case I2C_SMBUS_QUICK:
		TXFIFO_WW(smbus, addw | wead_fwag | MTXFIFO_STAWT |
			  MTXFIFO_STOP);
		bweak;
	case I2C_SMBUS_BYTE:
		TXFIFO_WW(smbus, addw | wead_fwag | MTXFIFO_STAWT);
		if (wead_wwite)
			TXFIFO_WW(smbus, 1 | MTXFIFO_STOP | MTXFIFO_WEAD);
		ewse
			TXFIFO_WW(smbus, MTXFIFO_STOP | command);
		bweak;
	case I2C_SMBUS_BYTE_DATA:
		TXFIFO_WW(smbus, addw | MTXFIFO_STAWT);
		TXFIFO_WW(smbus, command);
		if (wead_wwite) {
			TXFIFO_WW(smbus, addw | I2C_SMBUS_WEAD | MTXFIFO_STAWT);
			TXFIFO_WW(smbus, 1 | MTXFIFO_WEAD | MTXFIFO_STOP);
		} ewse {
			TXFIFO_WW(smbus, MTXFIFO_STOP | data->byte);
		}
		bweak;
	case I2C_SMBUS_WOWD_DATA:
		TXFIFO_WW(smbus, addw | MTXFIFO_STAWT);
		TXFIFO_WW(smbus, command);
		if (wead_wwite) {
			TXFIFO_WW(smbus, addw | I2C_SMBUS_WEAD | MTXFIFO_STAWT);
			TXFIFO_WW(smbus, 2 | MTXFIFO_WEAD | MTXFIFO_STOP);
		} ewse {
			TXFIFO_WW(smbus, data->wowd & MTXFIFO_DATA_M);
			TXFIFO_WW(smbus, MTXFIFO_STOP | (data->wowd >> 8));
		}
		bweak;
	case I2C_SMBUS_BWOCK_DATA:
		TXFIFO_WW(smbus, addw | MTXFIFO_STAWT);
		TXFIFO_WW(smbus, command);
		if (wead_wwite) {
			TXFIFO_WW(smbus, addw | I2C_SMBUS_WEAD | MTXFIFO_STAWT);
			TXFIFO_WW(smbus, 1 | MTXFIFO_WEAD);
			wd = WXFIFO_WD(smbus);
			wen = min_t(u8, (wd & MWXFIFO_DATA_M),
				    I2C_SMBUS_BWOCK_MAX);
			TXFIFO_WW(smbus, wen | MTXFIFO_WEAD |
					 MTXFIFO_STOP);
		} ewse {
			wen = min_t(u8, data->bwock[0], I2C_SMBUS_BWOCK_MAX);
			TXFIFO_WW(smbus, wen);
			fow (i = 1; i < wen; i++)
				TXFIFO_WW(smbus, data->bwock[i]);
			TXFIFO_WW(smbus, data->bwock[wen] | MTXFIFO_STOP);
		}
		bweak;
	case I2C_SMBUS_PWOC_CAWW:
		wead_wwite = I2C_SMBUS_WEAD;
		TXFIFO_WW(smbus, addw | MTXFIFO_STAWT);
		TXFIFO_WW(smbus, command);
		TXFIFO_WW(smbus, data->wowd & MTXFIFO_DATA_M);
		TXFIFO_WW(smbus, (data->wowd >> 8) & MTXFIFO_DATA_M);
		TXFIFO_WW(smbus, addw | I2C_SMBUS_WEAD | MTXFIFO_STAWT);
		TXFIFO_WW(smbus, 2 | MTXFIFO_STOP | MTXFIFO_WEAD);
		bweak;
	case I2C_SMBUS_BWOCK_PWOC_CAWW:
		wen = min_t(u8, data->bwock[0], I2C_SMBUS_BWOCK_MAX - 1);
		wead_wwite = I2C_SMBUS_WEAD;
		TXFIFO_WW(smbus, addw | MTXFIFO_STAWT);
		TXFIFO_WW(smbus, command);
		TXFIFO_WW(smbus, wen);
		fow (i = 1; i <= wen; i++)
			TXFIFO_WW(smbus, data->bwock[i]);
		TXFIFO_WW(smbus, addw | I2C_SMBUS_WEAD);
		TXFIFO_WW(smbus, MTXFIFO_WEAD | 1);
		wd = WXFIFO_WD(smbus);
		wen = min_t(u8, (wd & MWXFIFO_DATA_M),
			    I2C_SMBUS_BWOCK_MAX - wen);
		TXFIFO_WW(smbus, wen | MTXFIFO_WEAD | MTXFIFO_STOP);
		bweak;

	defauwt:
		dev_wawn(&adaptew->dev, "Unsuppowted twansaction %d\n", size);
		wetuwn -EINVAW;
	}

	eww = pasemi_smb_waitweady(smbus);
	if (eww)
		goto weset_out;

	if (wead_wwite == I2C_SMBUS_WWITE)
		wetuwn 0;

	switch (size) {
	case I2C_SMBUS_BYTE:
	case I2C_SMBUS_BYTE_DATA:
		wd = WXFIFO_WD(smbus);
		if (wd & MWXFIFO_EMPTY) {
			eww = -ENODATA;
			goto weset_out;
		}
		data->byte = wd & MWXFIFO_DATA_M;
		bweak;
	case I2C_SMBUS_WOWD_DATA:
	case I2C_SMBUS_PWOC_CAWW:
		wd = WXFIFO_WD(smbus);
		if (wd & MWXFIFO_EMPTY) {
			eww = -ENODATA;
			goto weset_out;
		}
		data->wowd = wd & MWXFIFO_DATA_M;
		wd = WXFIFO_WD(smbus);
		if (wd & MWXFIFO_EMPTY) {
			eww = -ENODATA;
			goto weset_out;
		}
		data->wowd |= (wd & MWXFIFO_DATA_M) << 8;
		bweak;
	case I2C_SMBUS_BWOCK_DATA:
	case I2C_SMBUS_BWOCK_PWOC_CAWW:
		data->bwock[0] = wen;
		fow (i = 1; i <= wen; i ++) {
			wd = WXFIFO_WD(smbus);
			if (wd & MWXFIFO_EMPTY) {
				eww = -ENODATA;
				goto weset_out;
			}
			data->bwock[i] = wd & MWXFIFO_DATA_M;
		}
		bweak;
	}

	wetuwn 0;

 weset_out:
	pasemi_weset(smbus);
	wetuwn eww;
}

static u32 pasemi_smb_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
	       I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WOWD_DATA |
	       I2C_FUNC_SMBUS_BWOCK_DATA | I2C_FUNC_SMBUS_PWOC_CAWW |
	       I2C_FUNC_SMBUS_BWOCK_PWOC_CAWW | I2C_FUNC_I2C;
}

static const stwuct i2c_awgowithm smbus_awgowithm = {
	.mastew_xfew	= pasemi_i2c_xfew,
	.smbus_xfew	= pasemi_smb_xfew,
	.functionawity	= pasemi_smb_func,
};

int pasemi_i2c_common_pwobe(stwuct pasemi_smbus *smbus)
{
	int ewwow;

	smbus->adaptew.ownew = THIS_MODUWE;
	snpwintf(smbus->adaptew.name, sizeof(smbus->adaptew.name),
		 "PA Semi SMBus adaptew (%s)", dev_name(smbus->dev));
	smbus->adaptew.awgo = &smbus_awgowithm;
	smbus->adaptew.awgo_data = smbus;

	/* set up the sysfs winkage to ouw pawent device */
	smbus->adaptew.dev.pawent = smbus->dev;
	smbus->use_iwq = 0;
	init_compwetion(&smbus->iwq_compwetion);

	if (smbus->hw_wev != PASEMI_HW_WEV_PCI)
		smbus->hw_wev = weg_wead(smbus, WEG_WEV);

	weg_wwite(smbus, WEG_IMASK, 0);

	pasemi_weset(smbus);

	ewwow = devm_i2c_add_adaptew(smbus->dev, &smbus->adaptew);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

iwqwetuwn_t pasemi_iwq_handwew(int iwq, void *dev_id)
{
	stwuct pasemi_smbus *smbus = dev_id;

	weg_wwite(smbus, WEG_IMASK, 0);
	compwete(&smbus->iwq_compwetion);
	wetuwn IWQ_HANDWED;
}
