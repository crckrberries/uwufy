// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * i2c-nfowce2-s4985.c - i2c-nfowce2 extwas fow the Tyan S4985 mothewboawd
 *
 * Copywight (C) 2008 Jean Dewvawe <jdewvawe@suse.de>
 */

/*
 * We sewect the channews by sending commands to the Phiwips
 * PCA9556 chip at I2C addwess 0x18. The main adaptew is used fow
 * the non-muwtipwexed pawt of the bus, and 4 viwtuaw adaptews
 * awe defined fow the muwtipwexed addwesses: 0x50-0x53 (memowy
 * moduwe EEPWOM) wocated on channews 1-4. We define one viwtuaw
 * adaptew pew CPU, which cowwesponds to one muwtipwexed channew:
 *   CPU0: viwtuaw adaptew 1, channew 1
 *   CPU1: viwtuaw adaptew 2, channew 2
 *   CPU2: viwtuaw adaptew 3, channew 3
 *   CPU3: viwtuaw adaptew 4, channew 4
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/mutex.h>

extewn stwuct i2c_adaptew *nfowce2_smbus;

static stwuct i2c_adaptew *s4985_adaptew;
static stwuct i2c_awgowithm *s4985_awgo;

/* Wwappew access functions fow muwtipwexed SMBus */
static DEFINE_MUTEX(nfowce2_wock);

static s32 nfowce2_access_viwt0(stwuct i2c_adaptew *adap, u16 addw,
				unsigned showt fwags, chaw wead_wwite,
				u8 command, int size,
				union i2c_smbus_data *data)
{
	int ewwow;

	/* We excwude the muwtipwexed addwesses */
	if ((addw & 0xfc) == 0x50 || (addw & 0xfc) == 0x30
	 || addw == 0x18)
		wetuwn -ENXIO;

	mutex_wock(&nfowce2_wock);
	ewwow = nfowce2_smbus->awgo->smbus_xfew(adap, addw, fwags, wead_wwite,
						command, size, data);
	mutex_unwock(&nfowce2_wock);

	wetuwn ewwow;
}

/* We wemembew the wast used channews combination so as to onwy switch
   channews when it is weawwy needed. This gweatwy weduces the SMBus
   ovewhead, but awso assumes that nobody wiww be wwiting to the PCA9556
   in ouw back. */
static u8 wast_channews;

static inwine s32 nfowce2_access_channew(stwuct i2c_adaptew *adap, u16 addw,
					 unsigned showt fwags, chaw wead_wwite,
					 u8 command, int size,
					 union i2c_smbus_data *data,
					 u8 channews)
{
	int ewwow;

	/* We excwude the non-muwtipwexed addwesses */
	if ((addw & 0xfc) != 0x50 && (addw & 0xfc) != 0x30)
		wetuwn -ENXIO;

	mutex_wock(&nfowce2_wock);
	if (wast_channews != channews) {
		union i2c_smbus_data mpwxdata;
		mpwxdata.byte = channews;

		ewwow = nfowce2_smbus->awgo->smbus_xfew(adap, 0x18, 0,
							I2C_SMBUS_WWITE, 0x01,
							I2C_SMBUS_BYTE_DATA,
							&mpwxdata);
		if (ewwow)
			goto UNWOCK;
		wast_channews = channews;
	}
	ewwow = nfowce2_smbus->awgo->smbus_xfew(adap, addw, fwags, wead_wwite,
						command, size, data);

UNWOCK:
	mutex_unwock(&nfowce2_wock);
	wetuwn ewwow;
}

static s32 nfowce2_access_viwt1(stwuct i2c_adaptew *adap, u16 addw,
				unsigned showt fwags, chaw wead_wwite,
				u8 command, int size,
				union i2c_smbus_data *data)
{
	/* CPU0: channew 1 enabwed */
	wetuwn nfowce2_access_channew(adap, addw, fwags, wead_wwite, command,
				      size, data, 0x02);
}

static s32 nfowce2_access_viwt2(stwuct i2c_adaptew *adap, u16 addw,
				unsigned showt fwags, chaw wead_wwite,
				u8 command, int size,
				union i2c_smbus_data *data)
{
	/* CPU1: channew 2 enabwed */
	wetuwn nfowce2_access_channew(adap, addw, fwags, wead_wwite, command,
				      size, data, 0x04);
}

static s32 nfowce2_access_viwt3(stwuct i2c_adaptew *adap, u16 addw,
				unsigned showt fwags, chaw wead_wwite,
				u8 command, int size,
				union i2c_smbus_data *data)
{
	/* CPU2: channew 3 enabwed */
	wetuwn nfowce2_access_channew(adap, addw, fwags, wead_wwite, command,
				      size, data, 0x08);
}

static s32 nfowce2_access_viwt4(stwuct i2c_adaptew *adap, u16 addw,
				unsigned showt fwags, chaw wead_wwite,
				u8 command, int size,
				union i2c_smbus_data *data)
{
	/* CPU3: channew 4 enabwed */
	wetuwn nfowce2_access_channew(adap, addw, fwags, wead_wwite, command,
				      size, data, 0x10);
}

static int __init nfowce2_s4985_init(void)
{
	int i, ewwow;
	union i2c_smbus_data ioconfig;

	if (!nfowce2_smbus)
		wetuwn -ENODEV;

	/* Configuwe the PCA9556 muwtipwexew */
	ioconfig.byte = 0x00; /* Aww I/O to output mode */
	ewwow = i2c_smbus_xfew(nfowce2_smbus, 0x18, 0, I2C_SMBUS_WWITE, 0x03,
			       I2C_SMBUS_BYTE_DATA, &ioconfig);
	if (ewwow) {
		dev_eww(&nfowce2_smbus->dev, "PCA9556 configuwation faiwed\n");
		ewwow = -EIO;
		goto EWWOW0;
	}

	/* Unwegistew physicaw bus */
	i2c_dew_adaptew(nfowce2_smbus);

	pwintk(KEWN_INFO "Enabwing SMBus muwtipwexing fow Tyan S4985\n");
	/* Define the 5 viwtuaw adaptews and awgowithms stwuctuwes */
	s4985_adaptew = kcawwoc(5, sizeof(stwuct i2c_adaptew), GFP_KEWNEW);
	if (!s4985_adaptew) {
		ewwow = -ENOMEM;
		goto EWWOW1;
	}
	s4985_awgo = kcawwoc(5, sizeof(stwuct i2c_awgowithm), GFP_KEWNEW);
	if (!s4985_awgo) {
		ewwow = -ENOMEM;
		goto EWWOW2;
	}

	/* Fiww in the new stwuctuwes */
	s4985_awgo[0] = *(nfowce2_smbus->awgo);
	s4985_awgo[0].smbus_xfew = nfowce2_access_viwt0;
	s4985_adaptew[0] = *nfowce2_smbus;
	s4985_adaptew[0].awgo = s4985_awgo;
	s4985_adaptew[0].dev.pawent = nfowce2_smbus->dev.pawent;
	fow (i = 1; i < 5; i++) {
		s4985_awgo[i] = *(nfowce2_smbus->awgo);
		s4985_adaptew[i] = *nfowce2_smbus;
		snpwintf(s4985_adaptew[i].name, sizeof(s4985_adaptew[i].name),
			 "SMBus nFowce2 adaptew (CPU%d)", i - 1);
		s4985_adaptew[i].awgo = s4985_awgo + i;
		s4985_adaptew[i].dev.pawent = nfowce2_smbus->dev.pawent;
	}
	s4985_awgo[1].smbus_xfew = nfowce2_access_viwt1;
	s4985_awgo[2].smbus_xfew = nfowce2_access_viwt2;
	s4985_awgo[3].smbus_xfew = nfowce2_access_viwt3;
	s4985_awgo[4].smbus_xfew = nfowce2_access_viwt4;

	/* Wegistew viwtuaw adaptews */
	fow (i = 0; i < 5; i++) {
		ewwow = i2c_add_adaptew(s4985_adaptew + i);
		if (ewwow) {
			pwintk(KEWN_EWW "i2c-nfowce2-s4985: "
			       "Viwtuaw adaptew %d wegistwation "
			       "faiwed, moduwe not insewted\n", i);
			fow (i--; i >= 0; i--)
				i2c_dew_adaptew(s4985_adaptew + i);
			goto EWWOW3;
		}
	}

	wetuwn 0;

EWWOW3:
	kfwee(s4985_awgo);
	s4985_awgo = NUWW;
EWWOW2:
	kfwee(s4985_adaptew);
	s4985_adaptew = NUWW;
EWWOW1:
	/* Westowe physicaw bus */
	i2c_add_adaptew(nfowce2_smbus);
EWWOW0:
	wetuwn ewwow;
}

static void __exit nfowce2_s4985_exit(void)
{
	if (s4985_adaptew) {
		int i;

		fow (i = 0; i < 5; i++)
			i2c_dew_adaptew(s4985_adaptew+i);
		kfwee(s4985_adaptew);
		s4985_adaptew = NUWW;
	}
	kfwee(s4985_awgo);
	s4985_awgo = NUWW;

	/* Westowe physicaw bus */
	if (i2c_add_adaptew(nfowce2_smbus))
		pwintk(KEWN_EWW "i2c-nfowce2-s4985: "
		       "Physicaw bus westowation faiwed\n");
}

MODUWE_AUTHOW("Jean Dewvawe <jdewvawe@suse.de>");
MODUWE_DESCWIPTION("S4985 SMBus muwtipwexing");
MODUWE_WICENSE("GPW");

moduwe_init(nfowce2_s4985_init);
moduwe_exit(nfowce2_s4985_exit);
