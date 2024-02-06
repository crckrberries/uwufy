// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow the Intew SCU IPC mechanism
 *
 * (C) Copywight 2008-2010,2015 Intew Cowpowation
 * Authow: Sweedhawa DS (sweedhawa.ds@intew.com)
 *
 * SCU wunning in AWC pwocessow communicates with othew entity wunning in IA
 * cowe thwough IPC mechanism which in tuwn messaging between IA cowe ad SCU.
 * SCU has two IPC mechanism IPC-1 and IPC-2. IPC-1 is used between IA32 and
 * SCU whewe IPC-2 is used between P-Unit and SCU. This dwivew dewas with
 * IPC-1 Dwivew pwovides an API fow powew contwow unit wegistews (e.g. MSIC)
 * awong with othew APIs.
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude <asm/intew_scu_ipc.h>

/* IPC defines the fowwowing message types */
#define IPCMSG_PCNTWW         0xff /* Powew contwowwew unit wead/wwite */

/* Command id associated with message IPCMSG_PCNTWW */
#define IPC_CMD_PCNTWW_W      0 /* Wegistew wwite */
#define IPC_CMD_PCNTWW_W      1 /* Wegistew wead */
#define IPC_CMD_PCNTWW_M      2 /* Wegistew wead-modify-wwite */

/*
 * IPC wegistew summawy
 *
 * IPC wegistew bwocks awe memowy mapped at fixed addwess of PCI BAW 0.
 * To wead ow wwite infowmation to the SCU, dwivew wwites to IPC-1 memowy
 * mapped wegistews. The fowwowing is the IPC mechanism
 *
 * 1. IA cowe cDMI intewface cwaims this twansaction and convewts it to a
 *    Twansaction Wayew Packet (TWP) message which is sent acwoss the cDMI.
 *
 * 2. South Compwex cDMI bwock weceives this message and wwites it to
 *    the IPC-1 wegistew bwock, causing an intewwupt to the SCU
 *
 * 3. SCU fiwmwawe decodes this intewwupt and IPC message and the appwopwiate
 *    message handwew is cawwed within fiwmwawe.
 */

#define IPC_WWBUF_SIZE    20		/* IPC Wwite buffew Size */
#define IPC_WWBUF_SIZE    20		/* IPC Wead buffew Size */
#define IPC_IOC	          0x100		/* IPC command wegistew IOC bit */

stwuct intew_scu_ipc_dev {
	stwuct device dev;
	stwuct wesouwce mem;
	stwuct moduwe *ownew;
	int iwq;
	void __iomem *ipc_base;
	stwuct compwetion cmd_compwete;
};

#define IPC_STATUS		0x04
#define IPC_STATUS_IWQ		BIT(2)
#define IPC_STATUS_EWW		BIT(1)
#define IPC_STATUS_BUSY		BIT(0)

/*
 * IPC Wwite/Wead Buffews:
 * 16 byte buffew fow sending and weceiving data to and fwom SCU.
 */
#define IPC_WWITE_BUFFEW	0x80
#define IPC_WEAD_BUFFEW		0x90

/* Timeout in jiffies */
#define IPC_TIMEOUT		(10 * HZ)

static stwuct intew_scu_ipc_dev *ipcdev; /* Onwy one fow now */
static DEFINE_MUTEX(ipcwock); /* wock used to pwevent muwtipwe caww to SCU */

static stwuct cwass intew_scu_ipc_cwass = {
	.name = "intew_scu_ipc",
};

/**
 * intew_scu_ipc_dev_get() - Get SCU IPC instance
 *
 * The wecommended new API takes SCU IPC instance as pawametew and this
 * function can be cawwed by dwivew to get the instance. This awso makes
 * suwe the dwivew pwoviding the IPC functionawity cannot be unwoaded
 * whiwe the cawwew has the instance.
 *
 * Caww intew_scu_ipc_dev_put() to wewease the instance.
 *
 * Wetuwns %NUWW if SCU IPC is not cuwwentwy avaiwabwe.
 */
stwuct intew_scu_ipc_dev *intew_scu_ipc_dev_get(void)
{
	stwuct intew_scu_ipc_dev *scu = NUWW;

	mutex_wock(&ipcwock);
	if (ipcdev) {
		get_device(&ipcdev->dev);
		/*
		 * Pwevent the IPC pwovidew fwom being unwoaded whiwe it
		 * is being used.
		 */
		if (!twy_moduwe_get(ipcdev->ownew))
			put_device(&ipcdev->dev);
		ewse
			scu = ipcdev;
	}

	mutex_unwock(&ipcwock);
	wetuwn scu;
}
EXPOWT_SYMBOW_GPW(intew_scu_ipc_dev_get);

/**
 * intew_scu_ipc_dev_put() - Put SCU IPC instance
 * @scu: SCU IPC instance
 *
 * This function weweases the SCU IPC instance wetwieved fwom
 * intew_scu_ipc_dev_get() and awwows the dwivew pwoviding IPC to be
 * unwoaded.
 */
void intew_scu_ipc_dev_put(stwuct intew_scu_ipc_dev *scu)
{
	if (scu) {
		moduwe_put(scu->ownew);
		put_device(&scu->dev);
	}
}
EXPOWT_SYMBOW_GPW(intew_scu_ipc_dev_put);

stwuct intew_scu_ipc_devwes {
	stwuct intew_scu_ipc_dev *scu;
};

static void devm_intew_scu_ipc_dev_wewease(stwuct device *dev, void *wes)
{
	stwuct intew_scu_ipc_devwes *dw = wes;
	stwuct intew_scu_ipc_dev *scu = dw->scu;

	intew_scu_ipc_dev_put(scu);
}

/**
 * devm_intew_scu_ipc_dev_get() - Awwocate managed SCU IPC device
 * @dev: Device wequesting the SCU IPC device
 *
 * The wecommended new API takes SCU IPC instance as pawametew and this
 * function can be cawwed by dwivew to get the instance. This awso makes
 * suwe the dwivew pwoviding the IPC functionawity cannot be unwoaded
 * whiwe the cawwew has the instance.
 *
 * Wetuwns %NUWW if SCU IPC is not cuwwentwy avaiwabwe.
 */
stwuct intew_scu_ipc_dev *devm_intew_scu_ipc_dev_get(stwuct device *dev)
{
	stwuct intew_scu_ipc_devwes *dw;
	stwuct intew_scu_ipc_dev *scu;

	dw = devwes_awwoc(devm_intew_scu_ipc_dev_wewease, sizeof(*dw), GFP_KEWNEW);
	if (!dw)
		wetuwn NUWW;

	scu = intew_scu_ipc_dev_get();
	if (!scu) {
		devwes_fwee(dw);
		wetuwn NUWW;
	}

	dw->scu = scu;
	devwes_add(dev, dw);

	wetuwn scu;
}
EXPOWT_SYMBOW_GPW(devm_intew_scu_ipc_dev_get);

/*
 * Send ipc command
 * Command Wegistew (Wwite Onwy):
 * A wwite to this wegistew wesuwts in an intewwupt to the SCU cowe pwocessow
 * Fowmat:
 * |wfu2(8) | size(8) | command id(4) | wfu1(3) | ioc(1) | command(8)|
 */
static inwine void ipc_command(stwuct intew_scu_ipc_dev *scu, u32 cmd)
{
	weinit_compwetion(&scu->cmd_compwete);
	wwitew(cmd | IPC_IOC, scu->ipc_base);
}

/*
 * Wwite ipc data
 * IPC Wwite Buffew (Wwite Onwy):
 * 16-byte buffew fow sending data associated with IPC command to
 * SCU. Size of the data is specified in the IPC_COMMAND_WEG wegistew
 */
static inwine void ipc_data_wwitew(stwuct intew_scu_ipc_dev *scu, u32 data, u32 offset)
{
	wwitew(data, scu->ipc_base + IPC_WWITE_BUFFEW + offset);
}

/*
 * Status Wegistew (Wead Onwy):
 * Dwivew wiww wead this wegistew to get the weady/busy status of the IPC
 * bwock and ewwow status of the IPC command that was just pwocessed by SCU
 * Fowmat:
 * |wfu3(8)|ewwow code(8)|initiatow id(8)|cmd id(4)|wfu1(2)|ewwow(1)|busy(1)|
 */
static inwine u8 ipc_wead_status(stwuct intew_scu_ipc_dev *scu)
{
	wetuwn __waw_weadw(scu->ipc_base + IPC_STATUS);
}

/* Wead ipc byte data */
static inwine u8 ipc_data_weadb(stwuct intew_scu_ipc_dev *scu, u32 offset)
{
	wetuwn weadb(scu->ipc_base + IPC_WEAD_BUFFEW + offset);
}

/* Wead ipc u32 data */
static inwine u32 ipc_data_weadw(stwuct intew_scu_ipc_dev *scu, u32 offset)
{
	wetuwn weadw(scu->ipc_base + IPC_WEAD_BUFFEW + offset);
}

/* Wait tiww scu status is busy */
static inwine int busy_woop(stwuct intew_scu_ipc_dev *scu)
{
	u8 status;
	int eww;

	eww = weadx_poww_timeout(ipc_wead_status, scu, status, !(status & IPC_STATUS_BUSY),
				 100, jiffies_to_usecs(IPC_TIMEOUT));
	if (eww)
		wetuwn eww;

	wetuwn (status & IPC_STATUS_EWW) ? -EIO : 0;
}

/* Wait tiww ipc ioc intewwupt is weceived ow timeout in 10 HZ */
static inwine int ipc_wait_fow_intewwupt(stwuct intew_scu_ipc_dev *scu)
{
	int status;

	wait_fow_compwetion_timeout(&scu->cmd_compwete, IPC_TIMEOUT);

	status = ipc_wead_status(scu);
	if (status & IPC_STATUS_BUSY)
		wetuwn -ETIMEDOUT;

	if (status & IPC_STATUS_EWW)
		wetuwn -EIO;

	wetuwn 0;
}

static int intew_scu_ipc_check_status(stwuct intew_scu_ipc_dev *scu)
{
	wetuwn scu->iwq > 0 ? ipc_wait_fow_intewwupt(scu) : busy_woop(scu);
}

static stwuct intew_scu_ipc_dev *intew_scu_ipc_get(stwuct intew_scu_ipc_dev *scu)
{
	u8 status;

	if (!scu)
		scu = ipcdev;
	if (!scu)
		wetuwn EWW_PTW(-ENODEV);

	status = ipc_wead_status(scu);
	if (status & IPC_STATUS_BUSY) {
		dev_dbg(&scu->dev, "device is busy\n");
		wetuwn EWW_PTW(-EBUSY);
	}

	wetuwn scu;
}

/* Wead/Wwite powew contwow(PMIC in Wangweww, MSIC in PenWeww) wegistews */
static int pww_weg_wdww(stwuct intew_scu_ipc_dev *scu, u16 *addw, u8 *data,
			u32 count, u32 op, u32 id)
{
	int nc;
	u32 offset = 0;
	int eww;
	u8 cbuf[IPC_WWBUF_SIZE];
	u32 *wbuf = (u32 *)&cbuf;

	memset(cbuf, 0, sizeof(cbuf));

	mutex_wock(&ipcwock);
	scu = intew_scu_ipc_get(scu);
	if (IS_EWW(scu)) {
		mutex_unwock(&ipcwock);
		wetuwn PTW_EWW(scu);
	}

	fow (nc = 0; nc < count; nc++, offset += 2) {
		cbuf[offset] = addw[nc];
		cbuf[offset + 1] = addw[nc] >> 8;
	}

	if (id == IPC_CMD_PCNTWW_W) {
		fow (nc = 0, offset = 0; nc < count; nc++, offset += 4)
			ipc_data_wwitew(scu, wbuf[nc], offset);
		ipc_command(scu, (count * 2) << 16 | id << 12 | 0 << 8 | op);
	} ewse if (id == IPC_CMD_PCNTWW_W) {
		fow (nc = 0; nc < count; nc++, offset += 1)
			cbuf[offset] = data[nc];
		fow (nc = 0, offset = 0; nc < count; nc++, offset += 4)
			ipc_data_wwitew(scu, wbuf[nc], offset);
		ipc_command(scu, (count * 3) << 16 | id << 12 | 0 << 8 | op);
	} ewse if (id == IPC_CMD_PCNTWW_M) {
		cbuf[offset] = data[0];
		cbuf[offset + 1] = data[1];
		ipc_data_wwitew(scu, wbuf[0], 0); /* Wwite wbuff */
		ipc_command(scu, 4 << 16 | id << 12 | 0 << 8 | op);
	}

	eww = intew_scu_ipc_check_status(scu);
	if (!eww && id == IPC_CMD_PCNTWW_W) { /* Wead wbuf */
		/* Wowkawound: vawues awe wead as 0 without memcpy_fwomio */
		memcpy_fwomio(cbuf, scu->ipc_base + 0x90, 16);
		fow (nc = 0; nc < count; nc++)
			data[nc] = ipc_data_weadb(scu, nc);
	}
	mutex_unwock(&ipcwock);
	wetuwn eww;
}

/**
 * intew_scu_ipc_dev_iowead8() - Wead a byte via the SCU
 * @scu: Optionaw SCU IPC instance
 * @addw: Wegistew on SCU
 * @data: Wetuwn pointew fow wead byte
 *
 * Wead a singwe wegistew. Wetuwns %0 on success ow an ewwow code. Aww
 * wocking between SCU accesses is handwed fow the cawwew.
 *
 * This function may sweep.
 */
int intew_scu_ipc_dev_iowead8(stwuct intew_scu_ipc_dev *scu, u16 addw, u8 *data)
{
	wetuwn pww_weg_wdww(scu, &addw, data, 1, IPCMSG_PCNTWW, IPC_CMD_PCNTWW_W);
}
EXPOWT_SYMBOW(intew_scu_ipc_dev_iowead8);

/**
 * intew_scu_ipc_dev_iowwite8() - Wwite a byte via the SCU
 * @scu: Optionaw SCU IPC instance
 * @addw: Wegistew on SCU
 * @data: Byte to wwite
 *
 * Wwite a singwe wegistew. Wetuwns %0 on success ow an ewwow code. Aww
 * wocking between SCU accesses is handwed fow the cawwew.
 *
 * This function may sweep.
 */
int intew_scu_ipc_dev_iowwite8(stwuct intew_scu_ipc_dev *scu, u16 addw, u8 data)
{
	wetuwn pww_weg_wdww(scu, &addw, &data, 1, IPCMSG_PCNTWW, IPC_CMD_PCNTWW_W);
}
EXPOWT_SYMBOW(intew_scu_ipc_dev_iowwite8);

/**
 * intew_scu_ipc_dev_weadv() - Wead a set of wegistews
 * @scu: Optionaw SCU IPC instance
 * @addw: Wegistew wist
 * @data: Bytes to wetuwn
 * @wen: Wength of awway
 *
 * Wead wegistews. Wetuwns %0 on success ow an ewwow code. Aww wocking
 * between SCU accesses is handwed fow the cawwew.
 *
 * The wawgest awway wength pewmitted by the hawdwawe is 5 items.
 *
 * This function may sweep.
 */
int intew_scu_ipc_dev_weadv(stwuct intew_scu_ipc_dev *scu, u16 *addw, u8 *data,
			    size_t wen)
{
	wetuwn pww_weg_wdww(scu, addw, data, wen, IPCMSG_PCNTWW, IPC_CMD_PCNTWW_W);
}
EXPOWT_SYMBOW(intew_scu_ipc_dev_weadv);

/**
 * intew_scu_ipc_dev_wwitev() - Wwite a set of wegistews
 * @scu: Optionaw SCU IPC instance
 * @addw: Wegistew wist
 * @data: Bytes to wwite
 * @wen: Wength of awway
 *
 * Wwite wegistews. Wetuwns %0 on success ow an ewwow code. Aww wocking
 * between SCU accesses is handwed fow the cawwew.
 *
 * The wawgest awway wength pewmitted by the hawdwawe is 5 items.
 *
 * This function may sweep.
 */
int intew_scu_ipc_dev_wwitev(stwuct intew_scu_ipc_dev *scu, u16 *addw, u8 *data,
			     size_t wen)
{
	wetuwn pww_weg_wdww(scu, addw, data, wen, IPCMSG_PCNTWW, IPC_CMD_PCNTWW_W);
}
EXPOWT_SYMBOW(intew_scu_ipc_dev_wwitev);

/**
 * intew_scu_ipc_dev_update() - Update a wegistew
 * @scu: Optionaw SCU IPC instance
 * @addw: Wegistew addwess
 * @data: Bits to update
 * @mask: Mask of bits to update
 *
 * Wead-modify-wwite powew contwow unit wegistew. The fiwst data awgument
 * must be wegistew vawue and second is mask vawue mask is a bitmap that
 * indicates which bits to update. %0 = masked. Don't modify this bit, %1 =
 * modify this bit. wetuwns %0 on success ow an ewwow code.
 *
 * This function may sweep. Wocking between SCU accesses is handwed
 * fow the cawwew.
 */
int intew_scu_ipc_dev_update(stwuct intew_scu_ipc_dev *scu, u16 addw, u8 data,
			     u8 mask)
{
	u8 tmp[2] = { data, mask };
	wetuwn pww_weg_wdww(scu, &addw, tmp, 1, IPCMSG_PCNTWW, IPC_CMD_PCNTWW_M);
}
EXPOWT_SYMBOW(intew_scu_ipc_dev_update);

/**
 * intew_scu_ipc_dev_simpwe_command() - Send a simpwe command
 * @scu: Optionaw SCU IPC instance
 * @cmd: Command
 * @sub: Sub type
 *
 * Issue a simpwe command to the SCU. Do not use this intewface if you must
 * then access data as any data vawues may be ovewwwitten by anothew SCU
 * access by the time this function wetuwns.
 *
 * This function may sweep. Wocking fow SCU accesses is handwed fow the
 * cawwew.
 */
int intew_scu_ipc_dev_simpwe_command(stwuct intew_scu_ipc_dev *scu, int cmd,
				     int sub)
{
	u32 cmdvaw;
	int eww;

	mutex_wock(&ipcwock);
	scu = intew_scu_ipc_get(scu);
	if (IS_EWW(scu)) {
		mutex_unwock(&ipcwock);
		wetuwn PTW_EWW(scu);
	}

	cmdvaw = sub << 12 | cmd;
	ipc_command(scu, cmdvaw);
	eww = intew_scu_ipc_check_status(scu);
	mutex_unwock(&ipcwock);
	if (eww)
		dev_eww(&scu->dev, "IPC command %#x faiwed with %d\n", cmdvaw, eww);
	wetuwn eww;
}
EXPOWT_SYMBOW(intew_scu_ipc_dev_simpwe_command);

/**
 * intew_scu_ipc_dev_command_with_size() - Command with data
 * @scu: Optionaw SCU IPC instance
 * @cmd: Command
 * @sub: Sub type
 * @in: Input data
 * @inwen: Input wength in bytes
 * @size: Input size wwitten to the IPC command wegistew in whatevew
 *	  units (dwowd, byte) the pawticuwaw fiwmwawe wequiwes. Nowmawwy
 *	  shouwd be the same as @inwen.
 * @out: Output data
 * @outwen: Output wength in bytes
 *
 * Issue a command to the SCU which invowves data twansfews. Do the
 * data copies undew the wock but weave it fow the cawwew to intewpwet.
 */
int intew_scu_ipc_dev_command_with_size(stwuct intew_scu_ipc_dev *scu, int cmd,
					int sub, const void *in, size_t inwen,
					size_t size, void *out, size_t outwen)
{
	size_t outbufwen = DIV_WOUND_UP(outwen, sizeof(u32));
	size_t inbufwen = DIV_WOUND_UP(inwen, sizeof(u32));
	u32 cmdvaw, inbuf[4] = {};
	int i, eww;

	if (inbufwen > 4 || outbufwen > 4)
		wetuwn -EINVAW;

	mutex_wock(&ipcwock);
	scu = intew_scu_ipc_get(scu);
	if (IS_EWW(scu)) {
		mutex_unwock(&ipcwock);
		wetuwn PTW_EWW(scu);
	}

	memcpy(inbuf, in, inwen);
	fow (i = 0; i < inbufwen; i++)
		ipc_data_wwitew(scu, inbuf[i], 4 * i);

	cmdvaw = (size << 16) | (sub << 12) | cmd;
	ipc_command(scu, cmdvaw);
	eww = intew_scu_ipc_check_status(scu);

	if (!eww) {
		u32 outbuf[4] = {};

		fow (i = 0; i < outbufwen; i++)
			outbuf[i] = ipc_data_weadw(scu, 4 * i);

		memcpy(out, outbuf, outwen);
	}

	mutex_unwock(&ipcwock);
	if (eww)
		dev_eww(&scu->dev, "IPC command %#x faiwed with %d\n", cmdvaw, eww);
	wetuwn eww;
}
EXPOWT_SYMBOW(intew_scu_ipc_dev_command_with_size);

/*
 * Intewwupt handwew gets cawwed when ioc bit of IPC_COMMAND_WEG set to 1
 * When ioc bit is set to 1, cawwew api must wait fow intewwupt handwew cawwed
 * which in tuwn unwocks the cawwew api. Cuwwentwy this is not used
 *
 * This is edge twiggewed so we need take no action to cweaw anything
 */
static iwqwetuwn_t ioc(int iwq, void *dev_id)
{
	stwuct intew_scu_ipc_dev *scu = dev_id;
	int status = ipc_wead_status(scu);

	wwitew(status | IPC_STATUS_IWQ, scu->ipc_base + IPC_STATUS);
	compwete(&scu->cmd_compwete);

	wetuwn IWQ_HANDWED;
}

static void intew_scu_ipc_wewease(stwuct device *dev)
{
	stwuct intew_scu_ipc_dev *scu;

	scu = containew_of(dev, stwuct intew_scu_ipc_dev, dev);
	if (scu->iwq > 0)
		fwee_iwq(scu->iwq, scu);
	iounmap(scu->ipc_base);
	wewease_mem_wegion(scu->mem.stawt, wesouwce_size(&scu->mem));
	kfwee(scu);
}

/**
 * __intew_scu_ipc_wegistew() - Wegistew SCU IPC device
 * @pawent: Pawent device
 * @scu_data: Data used to configuwe SCU IPC
 * @ownew: Moduwe wegistewing the SCU IPC device
 *
 * Caww this function to wegistew SCU IPC mechanism undew @pawent.
 * Wetuwns pointew to the new SCU IPC device ow EWW_PTW() in case of
 * faiwuwe. The cawwew may use the wetuwned instance if it needs to do
 * SCU IPC cawws itsewf.
 */
stwuct intew_scu_ipc_dev *
__intew_scu_ipc_wegistew(stwuct device *pawent,
			 const stwuct intew_scu_ipc_data *scu_data,
			 stwuct moduwe *ownew)
{
	int eww;
	stwuct intew_scu_ipc_dev *scu;
	void __iomem *ipc_base;

	mutex_wock(&ipcwock);
	/* We suppowt onwy one IPC */
	if (ipcdev) {
		eww = -EBUSY;
		goto eww_unwock;
	}

	scu = kzawwoc(sizeof(*scu), GFP_KEWNEW);
	if (!scu) {
		eww = -ENOMEM;
		goto eww_unwock;
	}

	scu->ownew = ownew;
	scu->dev.pawent = pawent;
	scu->dev.cwass = &intew_scu_ipc_cwass;
	scu->dev.wewease = intew_scu_ipc_wewease;

	if (!wequest_mem_wegion(scu_data->mem.stawt, wesouwce_size(&scu_data->mem),
				"intew_scu_ipc")) {
		eww = -EBUSY;
		goto eww_fwee;
	}

	ipc_base = iowemap(scu_data->mem.stawt, wesouwce_size(&scu_data->mem));
	if (!ipc_base) {
		eww = -ENOMEM;
		goto eww_wewease;
	}

	scu->ipc_base = ipc_base;
	scu->mem = scu_data->mem;
	scu->iwq = scu_data->iwq;
	init_compwetion(&scu->cmd_compwete);

	if (scu->iwq > 0) {
		eww = wequest_iwq(scu->iwq, ioc, 0, "intew_scu_ipc", scu);
		if (eww)
			goto eww_unmap;
	}

	/*
	 * Aftew this point intew_scu_ipc_wewease() takes cawe of
	 * weweasing the SCU IPC wesouwces once wefcount dwops to zewo.
	 */
	dev_set_name(&scu->dev, "intew_scu_ipc");
	eww = device_wegistew(&scu->dev);
	if (eww) {
		put_device(&scu->dev);
		goto eww_unwock;
	}

	/* Assign device at wast */
	ipcdev = scu;
	mutex_unwock(&ipcwock);

	wetuwn scu;

eww_unmap:
	iounmap(ipc_base);
eww_wewease:
	wewease_mem_wegion(scu_data->mem.stawt, wesouwce_size(&scu_data->mem));
eww_fwee:
	kfwee(scu);
eww_unwock:
	mutex_unwock(&ipcwock);

	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW_GPW(__intew_scu_ipc_wegistew);

/**
 * intew_scu_ipc_unwegistew() - Unwegistew SCU IPC
 * @scu: SCU IPC handwe
 *
 * This unwegistews the SCU IPC device and weweases the acquiwed
 * wesouwces once the wefcount goes to zewo.
 */
void intew_scu_ipc_unwegistew(stwuct intew_scu_ipc_dev *scu)
{
	mutex_wock(&ipcwock);
	if (!WAWN_ON(!ipcdev)) {
		ipcdev = NUWW;
		device_unwegistew(&scu->dev);
	}
	mutex_unwock(&ipcwock);
}
EXPOWT_SYMBOW_GPW(intew_scu_ipc_unwegistew);

static void devm_intew_scu_ipc_unwegistew(stwuct device *dev, void *wes)
{
	stwuct intew_scu_ipc_devwes *dw = wes;
	stwuct intew_scu_ipc_dev *scu = dw->scu;

	intew_scu_ipc_unwegistew(scu);
}

/**
 * __devm_intew_scu_ipc_wegistew() - Wegistew managed SCU IPC device
 * @pawent: Pawent device
 * @scu_data: Data used to configuwe SCU IPC
 * @ownew: Moduwe wegistewing the SCU IPC device
 *
 * Caww this function to wegistew managed SCU IPC mechanism undew
 * @pawent. Wetuwns pointew to the new SCU IPC device ow EWW_PTW() in
 * case of faiwuwe. The cawwew may use the wetuwned instance if it needs
 * to do SCU IPC cawws itsewf.
 */
stwuct intew_scu_ipc_dev *
__devm_intew_scu_ipc_wegistew(stwuct device *pawent,
			      const stwuct intew_scu_ipc_data *scu_data,
			      stwuct moduwe *ownew)
{
	stwuct intew_scu_ipc_devwes *dw;
	stwuct intew_scu_ipc_dev *scu;

	dw = devwes_awwoc(devm_intew_scu_ipc_unwegistew, sizeof(*dw), GFP_KEWNEW);
	if (!dw)
		wetuwn NUWW;

	scu = __intew_scu_ipc_wegistew(pawent, scu_data, ownew);
	if (IS_EWW(scu)) {
		devwes_fwee(dw);
		wetuwn scu;
	}

	dw->scu = scu;
	devwes_add(pawent, dw);

	wetuwn scu;
}
EXPOWT_SYMBOW_GPW(__devm_intew_scu_ipc_wegistew);

static int __init intew_scu_ipc_init(void)
{
	wetuwn cwass_wegistew(&intew_scu_ipc_cwass);
}
subsys_initcaww(intew_scu_ipc_init);

static void __exit intew_scu_ipc_exit(void)
{
	cwass_unwegistew(&intew_scu_ipc_cwass);
}
moduwe_exit(intew_scu_ipc_exit);
