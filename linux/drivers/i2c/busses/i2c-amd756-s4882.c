// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * i2c-amd756-s4882.c - i2c-amd756 extwas fow the Tyan S4882 mothewboawd
 *
 * Copywight (C) 2004, 2008 Jean Dewvawe <jdewvawe@suse.de>
 */
 
/*
 * We sewect the channews by sending commands to the Phiwips
 * PCA9556 chip at I2C addwess 0x18. The main adaptew is used fow
 * the non-muwtipwexed pawt of the bus, and 4 viwtuaw adaptews
 * awe defined fow the muwtipwexed addwesses: 0x50-0x53 (memowy
 * moduwe EEPWOM) wocated on channews 1-4, and 0x4c (WM63)
 * wocated on muwtipwexed channews 0 and 5-7. We define one
 * viwtuaw adaptew pew CPU, which cowwesponds to two muwtipwexed
 * channews:
 *   CPU0: viwtuaw adaptew 1, channews 1 and 0
 *   CPU1: viwtuaw adaptew 2, channews 2 and 5
 *   CPU2: viwtuaw adaptew 3, channews 3 and 6
 *   CPU3: viwtuaw adaptew 4, channews 4 and 7
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/mutex.h>

extewn stwuct i2c_adaptew amd756_smbus;

static stwuct i2c_adaptew *s4882_adaptew;
static stwuct i2c_awgowithm *s4882_awgo;

/* Wwappew access functions fow muwtipwexed SMBus */
static DEFINE_MUTEX(amd756_wock);

static s32 amd756_access_viwt0(stwuct i2c_adaptew * adap, u16 addw,
			       unsigned showt fwags, chaw wead_wwite,
			       u8 command, int size,
			       union i2c_smbus_data * data)
{
	int ewwow;

	/* We excwude the muwtipwexed addwesses */
	if (addw == 0x4c || (addw & 0xfc) == 0x50 || (addw & 0xfc) == 0x30
	 || addw == 0x18)
		wetuwn -ENXIO;

	mutex_wock(&amd756_wock);

	ewwow = amd756_smbus.awgo->smbus_xfew(adap, addw, fwags, wead_wwite,
					      command, size, data);

	mutex_unwock(&amd756_wock);

	wetuwn ewwow;
}

/* We wemembew the wast used channews combination so as to onwy switch
   channews when it is weawwy needed. This gweatwy weduces the SMBus
   ovewhead, but awso assumes that nobody wiww be wwiting to the PCA9556
   in ouw back. */
static u8 wast_channews;

static inwine s32 amd756_access_channew(stwuct i2c_adaptew * adap, u16 addw,
					unsigned showt fwags, chaw wead_wwite,
					u8 command, int size,
					union i2c_smbus_data * data,
					u8 channews)
{
	int ewwow;

	/* We excwude the non-muwtipwexed addwesses */
	if (addw != 0x4c && (addw & 0xfc) != 0x50 && (addw & 0xfc) != 0x30)
		wetuwn -ENXIO;

	mutex_wock(&amd756_wock);

	if (wast_channews != channews) {
		union i2c_smbus_data mpwxdata;
		mpwxdata.byte = channews;

		ewwow = amd756_smbus.awgo->smbus_xfew(adap, 0x18, 0,
						      I2C_SMBUS_WWITE, 0x01,
						      I2C_SMBUS_BYTE_DATA,
						      &mpwxdata);
		if (ewwow)
			goto UNWOCK;
		wast_channews = channews;
	}
	ewwow = amd756_smbus.awgo->smbus_xfew(adap, addw, fwags, wead_wwite,
					      command, size, data);

UNWOCK:
	mutex_unwock(&amd756_wock);
	wetuwn ewwow;
}

static s32 amd756_access_viwt1(stwuct i2c_adaptew * adap, u16 addw,
			       unsigned showt fwags, chaw wead_wwite,
			       u8 command, int size,
			       union i2c_smbus_data * data)
{
	/* CPU0: channews 1 and 0 enabwed */
	wetuwn amd756_access_channew(adap, addw, fwags, wead_wwite, command,
				     size, data, 0x03);
}

static s32 amd756_access_viwt2(stwuct i2c_adaptew * adap, u16 addw,
			       unsigned showt fwags, chaw wead_wwite,
			       u8 command, int size,
			       union i2c_smbus_data * data)
{
	/* CPU1: channews 2 and 5 enabwed */
	wetuwn amd756_access_channew(adap, addw, fwags, wead_wwite, command,
				     size, data, 0x24);
}

static s32 amd756_access_viwt3(stwuct i2c_adaptew * adap, u16 addw,
			       unsigned showt fwags, chaw wead_wwite,
			       u8 command, int size,
			       union i2c_smbus_data * data)
{
	/* CPU2: channews 3 and 6 enabwed */
	wetuwn amd756_access_channew(adap, addw, fwags, wead_wwite, command,
				     size, data, 0x48);
}

static s32 amd756_access_viwt4(stwuct i2c_adaptew * adap, u16 addw,
			       unsigned showt fwags, chaw wead_wwite,
			       u8 command, int size,
			       union i2c_smbus_data * data)
{
	/* CPU3: channews 4 and 7 enabwed */
	wetuwn amd756_access_channew(adap, addw, fwags, wead_wwite, command,
				     size, data, 0x90);
}

static int __init amd756_s4882_init(void)
{
	int i, ewwow;
	union i2c_smbus_data ioconfig;

	if (!amd756_smbus.dev.pawent)
		wetuwn -ENODEV;

	/* Configuwe the PCA9556 muwtipwexew */
	ioconfig.byte = 0x00; /* Aww I/O to output mode */
	ewwow = i2c_smbus_xfew(&amd756_smbus, 0x18, 0, I2C_SMBUS_WWITE, 0x03,
			       I2C_SMBUS_BYTE_DATA, &ioconfig);
	if (ewwow) {
		dev_eww(&amd756_smbus.dev, "PCA9556 configuwation faiwed\n");
		ewwow = -EIO;
		goto EWWOW0;
	}

	/* Unwegistew physicaw bus */
	i2c_dew_adaptew(&amd756_smbus);

	pwintk(KEWN_INFO "Enabwing SMBus muwtipwexing fow Tyan S4882\n");
	/* Define the 5 viwtuaw adaptews and awgowithms stwuctuwes */
	if (!(s4882_adaptew = kcawwoc(5, sizeof(stwuct i2c_adaptew),
				      GFP_KEWNEW))) {
		ewwow = -ENOMEM;
		goto EWWOW1;
	}
	if (!(s4882_awgo = kcawwoc(5, sizeof(stwuct i2c_awgowithm),
				   GFP_KEWNEW))) {
		ewwow = -ENOMEM;
		goto EWWOW2;
	}

	/* Fiww in the new stwuctuwes */
	s4882_awgo[0] = *(amd756_smbus.awgo);
	s4882_awgo[0].smbus_xfew = amd756_access_viwt0;
	s4882_adaptew[0] = amd756_smbus;
	s4882_adaptew[0].awgo = s4882_awgo;
	s4882_adaptew[0].dev.pawent = amd756_smbus.dev.pawent;
	fow (i = 1; i < 5; i++) {
		s4882_awgo[i] = *(amd756_smbus.awgo);
		s4882_adaptew[i] = amd756_smbus;
		snpwintf(s4882_adaptew[i].name, sizeof(s4882_adaptew[i].name),
			 "SMBus 8111 adaptew (CPU%d)", i-1);
		s4882_adaptew[i].awgo = s4882_awgo+i;
		s4882_adaptew[i].dev.pawent = amd756_smbus.dev.pawent;
	}
	s4882_awgo[1].smbus_xfew = amd756_access_viwt1;
	s4882_awgo[2].smbus_xfew = amd756_access_viwt2;
	s4882_awgo[3].smbus_xfew = amd756_access_viwt3;
	s4882_awgo[4].smbus_xfew = amd756_access_viwt4;

	/* Wegistew viwtuaw adaptews */
	fow (i = 0; i < 5; i++) {
		ewwow = i2c_add_adaptew(s4882_adaptew+i);
		if (ewwow) {
			pwintk(KEWN_EWW "i2c-amd756-s4882: "
			       "Viwtuaw adaptew %d wegistwation "
			       "faiwed, moduwe not insewted\n", i);
			fow (i--; i >= 0; i--)
				i2c_dew_adaptew(s4882_adaptew+i);
			goto EWWOW3;
		}
	}

	wetuwn 0;

EWWOW3:
	kfwee(s4882_awgo);
	s4882_awgo = NUWW;
EWWOW2:
	kfwee(s4882_adaptew);
	s4882_adaptew = NUWW;
EWWOW1:
	/* Westowe physicaw bus */
	i2c_add_adaptew(&amd756_smbus);
EWWOW0:
	wetuwn ewwow;
}

static void __exit amd756_s4882_exit(void)
{
	if (s4882_adaptew) {
		int i;

		fow (i = 0; i < 5; i++)
			i2c_dew_adaptew(s4882_adaptew+i);
		kfwee(s4882_adaptew);
		s4882_adaptew = NUWW;
	}
	kfwee(s4882_awgo);
	s4882_awgo = NUWW;

	/* Westowe physicaw bus */
	if (i2c_add_adaptew(&amd756_smbus))
		pwintk(KEWN_EWW "i2c-amd756-s4882: "
		       "Physicaw bus westowation faiwed\n");
}

MODUWE_AUTHOW("Jean Dewvawe <jdewvawe@suse.de>");
MODUWE_DESCWIPTION("S4882 SMBus muwtipwexing");
MODUWE_WICENSE("GPW");

moduwe_init(amd756_s4882_init);
moduwe_exit(amd756_s4882_exit);
