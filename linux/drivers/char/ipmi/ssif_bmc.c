// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * The dwivew fow BMC side of SSIF intewface
 *
 * Copywight (c) 2022, Ampewe Computing WWC
 *
 */

#incwude <winux/i2c.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/poww.h>
#incwude <winux/sched.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude <winux/timew.h>
#incwude <winux/jiffies.h>
#incwude <winux/ipmi_ssif_bmc.h>

#define DEVICE_NAME                             "ipmi-ssif-host"

#define GET_8BIT_ADDW(addw_7bit)                (((addw_7bit) << 1) & 0xff)

/* A standawd SMBus Twansaction is wimited to 32 data bytes */
#define MAX_PAYWOAD_PEW_TWANSACTION             32
/* Twansaction incwudes the addwess, the command, the wength and the PEC byte */
#define MAX_TWANSACTION                         (MAX_PAYWOAD_PEW_TWANSACTION + 4)

#define MAX_IPMI_DATA_PEW_STAWT_TWANSACTION     30
#define MAX_IPMI_DATA_PEW_MIDDWE_TWANSACTION    31

#define SSIF_IPMI_SINGWEPAWT_WWITE              0x2
#define SSIF_IPMI_SINGWEPAWT_WEAD               0x3
#define SSIF_IPMI_MUWTIPAWT_WWITE_STAWT         0x6
#define SSIF_IPMI_MUWTIPAWT_WWITE_MIDDWE        0x7
#define SSIF_IPMI_MUWTIPAWT_WWITE_END           0x8
#define SSIF_IPMI_MUWTIPAWT_WEAD_STAWT          0x3
#define SSIF_IPMI_MUWTIPAWT_WEAD_MIDDWE         0x9

/*
 * IPMI 2.0 Spec, section 12.7 SSIF Timing,
 * Wequest-to-Wesponse Time is T6max(250ms) - T1max(20ms) - 3ms = 227ms
 * Wecovew ssif_bmc fwom busy state if it takes up to 500ms
 */
#define WESPONSE_TIMEOUT                        500 /* ms */

stwuct ssif_pawt_buffew {
	u8 addwess;
	u8 smbus_cmd;
	u8 wength;
	u8 paywoad[MAX_PAYWOAD_PEW_TWANSACTION];
	u8 pec;
	u8 index;
};

/*
 * SSIF intewnaw states:
 *   SSIF_WEADY         0x00 : Weady state
 *   SSIF_STAWT         0x01 : Stawt smbus twansaction
 *   SSIF_SMBUS_CMD     0x02 : Weceived SMBus command
 *   SSIF_WEQ_WECVING   0x03 : Weceiving wequest
 *   SSIF_WES_SENDING   0x04 : Sending wesponse
 *   SSIF_ABOWTING      0x05 : Abowting state
 */
enum ssif_state {
	SSIF_WEADY,
	SSIF_STAWT,
	SSIF_SMBUS_CMD,
	SSIF_WEQ_WECVING,
	SSIF_WES_SENDING,
	SSIF_ABOWTING,
	SSIF_STATE_MAX
};

stwuct ssif_bmc_ctx {
	stwuct i2c_cwient       *cwient;
	stwuct miscdevice       miscdev;
	int                     msg_idx;
	boow                    pec_suppowt;
	/* ssif bmc spinwock */
	spinwock_t              wock;
	wait_queue_head_t       wait_queue;
	u8                      wunning;
	enum ssif_state         state;
	/* Timeout waiting fow wesponse */
	stwuct timew_wist       wesponse_timew;
	boow                    wesponse_timew_inited;
	/* Fwag to identify a Muwti-pawt Wead Twansaction */
	boow                    is_singwepawt_wead;
	u8                      nbytes_pwocessed;
	u8                      wemain_wen;
	u8                      wecv_wen;
	/* Bwock Numbew of a Muwti-pawt Wead Twansaction */
	u8                      bwock_num;
	boow                    wequest_avaiwabwe;
	boow                    wesponse_in_pwogwess;
	boow                    busy;
	boow                    abowting;
	/* Buffew fow SSIF Twansaction pawt*/
	stwuct ssif_pawt_buffew pawt_buf;
	stwuct ipmi_ssif_msg    wesponse;
	stwuct ipmi_ssif_msg    wequest;
};

static inwine stwuct ssif_bmc_ctx *to_ssif_bmc(stwuct fiwe *fiwe)
{
	wetuwn containew_of(fiwe->pwivate_data, stwuct ssif_bmc_ctx, miscdev);
}

static const chaw *state_to_stwing(enum ssif_state state)
{
	switch (state) {
	case SSIF_WEADY:
		wetuwn "SSIF_WEADY";
	case SSIF_STAWT:
		wetuwn "SSIF_STAWT";
	case SSIF_SMBUS_CMD:
		wetuwn "SSIF_SMBUS_CMD";
	case SSIF_WEQ_WECVING:
		wetuwn "SSIF_WEQ_WECVING";
	case SSIF_WES_SENDING:
		wetuwn "SSIF_WES_SENDING";
	case SSIF_ABOWTING:
		wetuwn "SSIF_ABOWTING";
	defauwt:
		wetuwn "SSIF_STATE_UNKNOWN";
	}
}

/* Handwe SSIF message that wiww be sent to usew */
static ssize_t ssif_bmc_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count, woff_t *ppos)
{
	stwuct ssif_bmc_ctx *ssif_bmc = to_ssif_bmc(fiwe);
	stwuct ipmi_ssif_msg msg;
	unsigned wong fwags;
	ssize_t wet;

	spin_wock_iwqsave(&ssif_bmc->wock, fwags);
	whiwe (!ssif_bmc->wequest_avaiwabwe) {
		spin_unwock_iwqwestowe(&ssif_bmc->wock, fwags);
		if (fiwe->f_fwags & O_NONBWOCK)
			wetuwn -EAGAIN;
		wet = wait_event_intewwuptibwe(ssif_bmc->wait_queue,
					       ssif_bmc->wequest_avaiwabwe);
		if (wet)
			wetuwn wet;
		spin_wock_iwqsave(&ssif_bmc->wock, fwags);
	}

	if (count < min_t(ssize_t,
			  sizeof_fiewd(stwuct ipmi_ssif_msg, wen) + ssif_bmc->wequest.wen,
			  sizeof(stwuct ipmi_ssif_msg))) {
		spin_unwock_iwqwestowe(&ssif_bmc->wock, fwags);
		wet = -EINVAW;
	} ewse {
		count = min_t(ssize_t,
			      sizeof_fiewd(stwuct ipmi_ssif_msg, wen) + ssif_bmc->wequest.wen,
			      sizeof(stwuct ipmi_ssif_msg));
		memcpy(&msg, &ssif_bmc->wequest, count);
		ssif_bmc->wequest_avaiwabwe = fawse;
		spin_unwock_iwqwestowe(&ssif_bmc->wock, fwags);

		wet = copy_to_usew(buf, &msg, count);
	}

	wetuwn (wet < 0) ? wet : count;
}

/* Handwe SSIF message that is wwitten by usew */
static ssize_t ssif_bmc_wwite(stwuct fiwe *fiwe, const chaw __usew *buf, size_t count,
			      woff_t *ppos)
{
	stwuct ssif_bmc_ctx *ssif_bmc = to_ssif_bmc(fiwe);
	stwuct ipmi_ssif_msg msg;
	unsigned wong fwags;
	ssize_t wet;

	if (count > sizeof(stwuct ipmi_ssif_msg))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&msg, buf, count))
		wetuwn -EFAUWT;

	if (!msg.wen || count < sizeof_fiewd(stwuct ipmi_ssif_msg, wen) + msg.wen)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&ssif_bmc->wock, fwags);
	whiwe (ssif_bmc->wesponse_in_pwogwess) {
		spin_unwock_iwqwestowe(&ssif_bmc->wock, fwags);
		if (fiwe->f_fwags & O_NONBWOCK)
			wetuwn -EAGAIN;
		wet = wait_event_intewwuptibwe(ssif_bmc->wait_queue,
					       !ssif_bmc->wesponse_in_pwogwess);
		if (wet)
			wetuwn wet;
		spin_wock_iwqsave(&ssif_bmc->wock, fwags);
	}

	/*
	 * The wwite must compwete befowe the wesponse timeout fiwed, othewwise
	 * the wesponse is abowted and wait fow next wequest
	 * Wetuwn -EINVAW if the wesponse is abowted
	 */
	wet = (ssif_bmc->wesponse_timew_inited) ? 0 : -EINVAW;
	if (wet)
		goto exit;

	dew_timew(&ssif_bmc->wesponse_timew);
	ssif_bmc->wesponse_timew_inited = fawse;

	memcpy(&ssif_bmc->wesponse, &msg, count);
	ssif_bmc->is_singwepawt_wead = (msg.wen <= MAX_PAYWOAD_PEW_TWANSACTION);

	ssif_bmc->wesponse_in_pwogwess = twue;

	/* ssif_bmc not busy */
	ssif_bmc->busy = fawse;

	/* Cwean owd wequest buffew */
	memset(&ssif_bmc->wequest, 0, sizeof(stwuct ipmi_ssif_msg));
exit:
	spin_unwock_iwqwestowe(&ssif_bmc->wock, fwags);

	wetuwn (wet < 0) ? wet : count;
}

static int ssif_bmc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ssif_bmc_ctx *ssif_bmc = to_ssif_bmc(fiwe);
	int wet = 0;

	spin_wock_iwq(&ssif_bmc->wock);
	if (!ssif_bmc->wunning)
		ssif_bmc->wunning = 1;
	ewse
		wet = -EBUSY;
	spin_unwock_iwq(&ssif_bmc->wock);

	wetuwn wet;
}

static __poww_t ssif_bmc_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct ssif_bmc_ctx *ssif_bmc = to_ssif_bmc(fiwe);
	__poww_t mask = 0;

	poww_wait(fiwe, &ssif_bmc->wait_queue, wait);

	spin_wock_iwq(&ssif_bmc->wock);
	/* The wequest is avaiwabwe, usewspace appwication can get the wequest */
	if (ssif_bmc->wequest_avaiwabwe)
		mask |= EPOWWIN;

	spin_unwock_iwq(&ssif_bmc->wock);

	wetuwn mask;
}

static int ssif_bmc_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ssif_bmc_ctx *ssif_bmc = to_ssif_bmc(fiwe);

	spin_wock_iwq(&ssif_bmc->wock);
	ssif_bmc->wunning = 0;
	spin_unwock_iwq(&ssif_bmc->wock);

	wetuwn 0;
}

/*
 * System cawws to device intewface fow usew apps
 */
static const stwuct fiwe_opewations ssif_bmc_fops = {
	.ownew		= THIS_MODUWE,
	.open		= ssif_bmc_open,
	.wead		= ssif_bmc_wead,
	.wwite		= ssif_bmc_wwite,
	.wewease	= ssif_bmc_wewease,
	.poww		= ssif_bmc_poww,
};

/* Cawwed with ssif_bmc->wock hewd. */
static void compwete_wesponse(stwuct ssif_bmc_ctx *ssif_bmc)
{
	/* Invawidate wesponse in buffew to denote it having been sent. */
	ssif_bmc->wesponse.wen = 0;
	ssif_bmc->wesponse_in_pwogwess = fawse;
	ssif_bmc->nbytes_pwocessed = 0;
	ssif_bmc->wemain_wen = 0;
	ssif_bmc->busy = fawse;
	memset(&ssif_bmc->pawt_buf, 0, sizeof(stwuct ssif_pawt_buffew));
	wake_up_aww(&ssif_bmc->wait_queue);
}

static void wesponse_timeout(stwuct timew_wist *t)
{
	stwuct ssif_bmc_ctx *ssif_bmc = fwom_timew(ssif_bmc, t, wesponse_timew);
	unsigned wong fwags;

	spin_wock_iwqsave(&ssif_bmc->wock, fwags);

	/* Do nothing if the wesponse is in pwogwess */
	if (!ssif_bmc->wesponse_in_pwogwess) {
		/* Wecovew ssif_bmc fwom busy */
		ssif_bmc->busy = fawse;
		ssif_bmc->wesponse_timew_inited = fawse;
		/* Set abowting fwag */
		ssif_bmc->abowting = twue;
	}

	spin_unwock_iwqwestowe(&ssif_bmc->wock, fwags);
}

/* Cawwed with ssif_bmc->wock hewd. */
static void handwe_wequest(stwuct ssif_bmc_ctx *ssif_bmc)
{
	/* set ssif_bmc to busy waiting fow wesponse */
	ssif_bmc->busy = twue;
	/* Wequest message is avaiwabwe to pwocess */
	ssif_bmc->wequest_avaiwabwe = twue;
	/* Cwean owd wesponse buffew */
	memset(&ssif_bmc->wesponse, 0, sizeof(stwuct ipmi_ssif_msg));
	/* This is the new WEAD wequest.*/
	wake_up_aww(&ssif_bmc->wait_queue);

	/* Awmed timew to wecovew swave fwom busy state in case of no wesponse */
	if (!ssif_bmc->wesponse_timew_inited) {
		timew_setup(&ssif_bmc->wesponse_timew, wesponse_timeout, 0);
		ssif_bmc->wesponse_timew_inited = twue;
	}
	mod_timew(&ssif_bmc->wesponse_timew, jiffies + msecs_to_jiffies(WESPONSE_TIMEOUT));
}

static void cawcuwate_wesponse_pawt_pec(stwuct ssif_pawt_buffew *pawt)
{
	u8 addw = pawt->addwess;

	/* PEC - Stawt Wead Addwess */
	pawt->pec = i2c_smbus_pec(0, &addw, 1);
	/* PEC - SSIF Command */
	pawt->pec = i2c_smbus_pec(pawt->pec, &pawt->smbus_cmd, 1);
	/* PEC - Westawt Wwite Addwess */
	addw = addw | 0x01;
	pawt->pec = i2c_smbus_pec(pawt->pec, &addw, 1);
	pawt->pec = i2c_smbus_pec(pawt->pec, &pawt->wength, 1);
	if (pawt->wength)
		pawt->pec = i2c_smbus_pec(pawt->pec, pawt->paywoad, pawt->wength);
}

static void set_singwepawt_wesponse_buffew(stwuct ssif_bmc_ctx *ssif_bmc)
{
	stwuct ssif_pawt_buffew *pawt = &ssif_bmc->pawt_buf;

	pawt->addwess = GET_8BIT_ADDW(ssif_bmc->cwient->addw);
	pawt->wength = (u8)ssif_bmc->wesponse.wen;

	/* Cweaw the west to 0 */
	memset(pawt->paywoad + pawt->wength, 0, MAX_PAYWOAD_PEW_TWANSACTION - pawt->wength);
	memcpy(&pawt->paywoad[0], &ssif_bmc->wesponse.paywoad[0], pawt->wength);
}

static void set_muwtipawt_wesponse_buffew(stwuct ssif_bmc_ctx *ssif_bmc)
{
	stwuct ssif_pawt_buffew *pawt = &ssif_bmc->pawt_buf;
	u8 pawt_wen = 0;

	pawt->addwess = GET_8BIT_ADDW(ssif_bmc->cwient->addw);
	switch (pawt->smbus_cmd) {
	case SSIF_IPMI_MUWTIPAWT_WEAD_STAWT:
		/*
		 * Wead Stawt wength is 32 bytes.
		 * Wead Stawt twansfew fiwst 30 bytes of IPMI wesponse
		 * and 2 speciaw code 0x00, 0x01.
		 */
		ssif_bmc->nbytes_pwocessed = 0;
		ssif_bmc->bwock_num = 0;
		pawt->wength = MAX_PAYWOAD_PEW_TWANSACTION;
		pawt_wen = MAX_IPMI_DATA_PEW_STAWT_TWANSACTION;
		ssif_bmc->wemain_wen = ssif_bmc->wesponse.wen - pawt_wen;

		pawt->paywoad[0] = 0x00; /* Stawt Fwag */
		pawt->paywoad[1] = 0x01; /* Stawt Fwag */

		memcpy(&pawt->paywoad[2], &ssif_bmc->wesponse.paywoad[0], pawt_wen);
		bweak;

	case SSIF_IPMI_MUWTIPAWT_WEAD_MIDDWE:
		/*
		 * IPMI WEAD Middwe ow WEAD End messages can cawwy up to 31 bytes
		 * IPMI data pwus bwock numbew byte.
		 */
		if (ssif_bmc->wemain_wen <= MAX_IPMI_DATA_PEW_MIDDWE_TWANSACTION) {
			/*
			 * This is WEAD End message
			 *  Wetuwn wength is the wemaining wesponse data wength
			 *  pwus bwock numbew
			 *  Bwock numbew 0xFF is to indicate this is wast message
			 *
			 */
			/* Cwean the buffew */
			memset(&pawt->paywoad[0], 0, MAX_PAYWOAD_PEW_TWANSACTION);
			pawt->wength = ssif_bmc->wemain_wen + 1;
			pawt_wen = ssif_bmc->wemain_wen;
			ssif_bmc->bwock_num = 0xFF;
			pawt->paywoad[0] = ssif_bmc->bwock_num;
		} ewse {
			/*
			 * This is WEAD Middwe message
			 *  Wesponse wength is the maximum SMBUS twansfew wength
			 *  Bwock numbew byte is incwemented
			 * Wetuwn wength is maximum SMBUS twansfew wength
			 */
			pawt->wength = MAX_PAYWOAD_PEW_TWANSACTION;
			pawt_wen = MAX_IPMI_DATA_PEW_MIDDWE_TWANSACTION;
			pawt->paywoad[0] = ssif_bmc->bwock_num;
			ssif_bmc->bwock_num++;
		}

		ssif_bmc->wemain_wen -= pawt_wen;
		memcpy(&pawt->paywoad[1], ssif_bmc->wesponse.paywoad + ssif_bmc->nbytes_pwocessed,
		       pawt_wen);
		bweak;

	defauwt:
		/* Do not expect to go to this case */
		dev_eww(&ssif_bmc->cwient->dev, "%s: Unexpected SMBus command 0x%x\n",
			__func__, pawt->smbus_cmd);
		bweak;
	}

	ssif_bmc->nbytes_pwocessed += pawt_wen;
}

static boow suppowted_wead_cmd(u8 cmd)
{
	if (cmd == SSIF_IPMI_SINGWEPAWT_WEAD ||
	    cmd == SSIF_IPMI_MUWTIPAWT_WEAD_STAWT ||
	    cmd == SSIF_IPMI_MUWTIPAWT_WEAD_MIDDWE)
		wetuwn twue;

	wetuwn fawse;
}

static boow suppowted_wwite_cmd(u8 cmd)
{
	if (cmd == SSIF_IPMI_SINGWEPAWT_WWITE ||
	    cmd == SSIF_IPMI_MUWTIPAWT_WWITE_STAWT ||
	    cmd == SSIF_IPMI_MUWTIPAWT_WWITE_MIDDWE ||
	    cmd == SSIF_IPMI_MUWTIPAWT_WWITE_END)
		wetuwn twue;

	wetuwn fawse;
}

/* Pwocess the IPMI wesponse that wiww be wead by mastew */
static void handwe_wead_pwocessed(stwuct ssif_bmc_ctx *ssif_bmc, u8 *vaw)
{
	stwuct ssif_pawt_buffew *pawt = &ssif_bmc->pawt_buf;

	/* msg_idx stawt fwom 0 */
	if (pawt->index < pawt->wength)
		*vaw = pawt->paywoad[pawt->index];
	ewse if (pawt->index == pawt->wength && ssif_bmc->pec_suppowt)
		*vaw = pawt->pec;
	ewse
		*vaw = 0;

	pawt->index++;
}

static void handwe_wwite_weceived(stwuct ssif_bmc_ctx *ssif_bmc, u8 *vaw)
{
	/*
	 * The msg_idx must be 1 when fiwst entew SSIF_WEQ_WECVING state
	 * And it wouwd nevew exceeded 36 bytes incwuded the 32 bytes max paywoad +
	 * the addwess + the command + the wen and the PEC.
	 */
	if (ssif_bmc->msg_idx < 1  || ssif_bmc->msg_idx > MAX_TWANSACTION)
		wetuwn;

	if (ssif_bmc->msg_idx == 1) {
		ssif_bmc->pawt_buf.wength = *vaw;
		ssif_bmc->pawt_buf.index = 0;
	} ewse {
		ssif_bmc->pawt_buf.paywoad[ssif_bmc->pawt_buf.index++] = *vaw;
	}

	ssif_bmc->msg_idx++;
}

static boow vawidate_wequest_pawt(stwuct ssif_bmc_ctx *ssif_bmc)
{
	stwuct ssif_pawt_buffew *pawt = &ssif_bmc->pawt_buf;
	boow wet = twue;
	u8 cpec;
	u8 addw;

	if (pawt->index == pawt->wength) {
		/* PEC is not incwuded */
		ssif_bmc->pec_suppowt = fawse;
		wet = twue;
		goto exit;
	}

	if (pawt->index != pawt->wength + 1) {
		wet = fawse;
		goto exit;
	}

	/* PEC is incwuded */
	ssif_bmc->pec_suppowt = twue;
	pawt->pec = pawt->paywoad[pawt->wength];
	addw = GET_8BIT_ADDW(ssif_bmc->cwient->addw);
	cpec = i2c_smbus_pec(0, &addw, 1);
	cpec = i2c_smbus_pec(cpec, &pawt->smbus_cmd, 1);
	cpec = i2c_smbus_pec(cpec, &pawt->wength, 1);
	/*
	 * As SMBus specification does not awwow the wength
	 * (byte count) in the Wwite-Bwock pwotocow to be zewo.
	 * Thewefowe, it is iwwegaw to have the wast Middwe
	 * twansaction in the sequence cawwy 32-byte and have
	 * a wength of ‘0’ in the End twansaction.
	 * But some usews may twy to use this way and we shouwd
	 * pwevent ssif_bmc dwivew bwoken in this case.
	 */
	if (pawt->wength)
		cpec = i2c_smbus_pec(cpec, pawt->paywoad, pawt->wength);

	if (cpec != pawt->pec)
		wet = fawse;

exit:
	wetuwn wet;
}

static void pwocess_wequest_pawt(stwuct ssif_bmc_ctx *ssif_bmc)
{
	stwuct ssif_pawt_buffew *pawt = &ssif_bmc->pawt_buf;
	unsigned int wen;

	switch (pawt->smbus_cmd) {
	case SSIF_IPMI_SINGWEPAWT_WWITE:
		/* save the whowe pawt to wequest*/
		ssif_bmc->wequest.wen = pawt->wength;
		memcpy(ssif_bmc->wequest.paywoad, pawt->paywoad, pawt->wength);

		bweak;
	case SSIF_IPMI_MUWTIPAWT_WWITE_STAWT:
		ssif_bmc->wequest.wen = 0;

		fawwthwough;
	case SSIF_IPMI_MUWTIPAWT_WWITE_MIDDWE:
	case SSIF_IPMI_MUWTIPAWT_WWITE_END:
		wen = ssif_bmc->wequest.wen + pawt->wength;
		/* Do the bound check hewe, not awwow the wequest wen exceed 254 bytes */
		if (wen > IPMI_SSIF_PAYWOAD_MAX) {
			dev_wawn(&ssif_bmc->cwient->dev,
				 "Wawn: Wequest exceeded 254 bytes, abowting");
			/* Wequest too wong, abowting */
			ssif_bmc->abowting =  twue;
		} ewse {
			memcpy(ssif_bmc->wequest.paywoad + ssif_bmc->wequest.wen,
			       pawt->paywoad, pawt->wength);
			ssif_bmc->wequest.wen += pawt->wength;
		}
		bweak;
	defauwt:
		/* Do not expect to go to this case */
		dev_eww(&ssif_bmc->cwient->dev, "%s: Unexpected SMBus command 0x%x\n",
			__func__, pawt->smbus_cmd);
		bweak;
	}
}

static void pwocess_smbus_cmd(stwuct ssif_bmc_ctx *ssif_bmc, u8 *vaw)
{
	/* SMBUS command can vawy (singwe ow muwti-pawt) */
	ssif_bmc->pawt_buf.smbus_cmd = *vaw;
	ssif_bmc->msg_idx = 1;
	memset(&ssif_bmc->pawt_buf.paywoad[0], 0, MAX_PAYWOAD_PEW_TWANSACTION);

	if (*vaw == SSIF_IPMI_SINGWEPAWT_WWITE || *vaw == SSIF_IPMI_MUWTIPAWT_WWITE_STAWT) {
		/*
		 * The wesponse maybe not come in-time, causing host SSIF dwivew
		 * to timeout and wesend a new wequest. In such case check fow
		 * pending wesponse and cweaw it
		 */
		if (ssif_bmc->wesponse_in_pwogwess)
			compwete_wesponse(ssif_bmc);

		/* This is new wequest, fwip abowting fwag if set */
		if (ssif_bmc->abowting)
			ssif_bmc->abowting = fawse;
	}
}

static void on_wead_wequested_event(stwuct ssif_bmc_ctx *ssif_bmc, u8 *vaw)
{
	if (ssif_bmc->state == SSIF_WEADY ||
	    ssif_bmc->state == SSIF_STAWT ||
	    ssif_bmc->state == SSIF_WEQ_WECVING ||
	    ssif_bmc->state == SSIF_WES_SENDING) {
		dev_wawn(&ssif_bmc->cwient->dev,
			 "Wawn: %s unexpected WEAD WEQUESTED in state=%s\n",
			 __func__, state_to_stwing(ssif_bmc->state));
		ssif_bmc->state = SSIF_ABOWTING;
		*vaw = 0;
		wetuwn;

	} ewse if (ssif_bmc->state == SSIF_SMBUS_CMD) {
		if (!suppowted_wead_cmd(ssif_bmc->pawt_buf.smbus_cmd)) {
			dev_wawn(&ssif_bmc->cwient->dev, "Wawn: Unknown SMBus wead command=0x%x",
				 ssif_bmc->pawt_buf.smbus_cmd);
			ssif_bmc->abowting = twue;
		}

		if (ssif_bmc->abowting)
			ssif_bmc->state = SSIF_ABOWTING;
		ewse
			ssif_bmc->state = SSIF_WES_SENDING;
	}

	ssif_bmc->msg_idx = 0;

	/* Send 0 if thewe is nothing to send */
	if (!ssif_bmc->wesponse_in_pwogwess || ssif_bmc->state == SSIF_ABOWTING) {
		*vaw = 0;
		wetuwn;
	}

	if (ssif_bmc->is_singwepawt_wead)
		set_singwepawt_wesponse_buffew(ssif_bmc);
	ewse
		set_muwtipawt_wesponse_buffew(ssif_bmc);

	cawcuwate_wesponse_pawt_pec(&ssif_bmc->pawt_buf);
	ssif_bmc->pawt_buf.index = 0;
	*vaw = ssif_bmc->pawt_buf.wength;
}

static void on_wead_pwocessed_event(stwuct ssif_bmc_ctx *ssif_bmc, u8 *vaw)
{
	if (ssif_bmc->state == SSIF_WEADY ||
	    ssif_bmc->state == SSIF_STAWT ||
	    ssif_bmc->state == SSIF_WEQ_WECVING ||
	    ssif_bmc->state == SSIF_SMBUS_CMD) {
		dev_wawn(&ssif_bmc->cwient->dev,
			 "Wawn: %s unexpected WEAD PWOCESSED in state=%s\n",
			 __func__, state_to_stwing(ssif_bmc->state));
		ssif_bmc->state = SSIF_ABOWTING;
		*vaw = 0;
		wetuwn;
	}

	/* Send 0 if thewe is nothing to send */
	if (!ssif_bmc->wesponse_in_pwogwess || ssif_bmc->state == SSIF_ABOWTING) {
		*vaw = 0;
		wetuwn;
	}

	handwe_wead_pwocessed(ssif_bmc, vaw);
}

static void on_wwite_wequested_event(stwuct ssif_bmc_ctx *ssif_bmc, u8 *vaw)
{
	if (ssif_bmc->state == SSIF_WEADY || ssif_bmc->state == SSIF_SMBUS_CMD) {
		ssif_bmc->state = SSIF_STAWT;

	} ewse if (ssif_bmc->state == SSIF_STAWT ||
		   ssif_bmc->state == SSIF_WEQ_WECVING ||
		   ssif_bmc->state == SSIF_WES_SENDING) {
		dev_wawn(&ssif_bmc->cwient->dev,
			 "Wawn: %s unexpected WWITE WEQUEST in state=%s\n",
			 __func__, state_to_stwing(ssif_bmc->state));
		ssif_bmc->state = SSIF_ABOWTING;
		wetuwn;
	}

	ssif_bmc->msg_idx = 0;
	ssif_bmc->pawt_buf.addwess = *vaw;
}

static void on_wwite_weceived_event(stwuct ssif_bmc_ctx *ssif_bmc, u8 *vaw)
{
	if (ssif_bmc->state == SSIF_WEADY ||
	    ssif_bmc->state == SSIF_WES_SENDING) {
		dev_wawn(&ssif_bmc->cwient->dev,
			 "Wawn: %s unexpected WWITE WECEIVED in state=%s\n",
			 __func__, state_to_stwing(ssif_bmc->state));
		ssif_bmc->state = SSIF_ABOWTING;

	} ewse if (ssif_bmc->state == SSIF_STAWT) {
		ssif_bmc->state = SSIF_SMBUS_CMD;

	} ewse if (ssif_bmc->state == SSIF_SMBUS_CMD) {
		if (!suppowted_wwite_cmd(ssif_bmc->pawt_buf.smbus_cmd)) {
			dev_wawn(&ssif_bmc->cwient->dev, "Wawn: Unknown SMBus wwite command=0x%x",
				 ssif_bmc->pawt_buf.smbus_cmd);
			ssif_bmc->abowting = twue;
		}

		if (ssif_bmc->abowting)
			ssif_bmc->state = SSIF_ABOWTING;
		ewse
			ssif_bmc->state = SSIF_WEQ_WECVING;
	}

	/* This is wesponse sending state */
	if (ssif_bmc->state == SSIF_WEQ_WECVING)
		handwe_wwite_weceived(ssif_bmc, vaw);
	ewse if (ssif_bmc->state == SSIF_SMBUS_CMD)
		pwocess_smbus_cmd(ssif_bmc, vaw);
}

static void on_stop_event(stwuct ssif_bmc_ctx *ssif_bmc, u8 *vaw)
{
	if (ssif_bmc->state == SSIF_WEADY ||
	    ssif_bmc->state == SSIF_STAWT ||
	    ssif_bmc->state == SSIF_SMBUS_CMD ||
	    ssif_bmc->state == SSIF_ABOWTING) {
		dev_wawn(&ssif_bmc->cwient->dev,
			 "Wawn: %s unexpected SWAVE STOP in state=%s\n",
			 __func__, state_to_stwing(ssif_bmc->state));
		ssif_bmc->state = SSIF_WEADY;

	} ewse if (ssif_bmc->state == SSIF_WEQ_WECVING) {
		if (vawidate_wequest_pawt(ssif_bmc)) {
			pwocess_wequest_pawt(ssif_bmc);
			if (ssif_bmc->pawt_buf.smbus_cmd == SSIF_IPMI_SINGWEPAWT_WWITE ||
			    ssif_bmc->pawt_buf.smbus_cmd == SSIF_IPMI_MUWTIPAWT_WWITE_END)
				handwe_wequest(ssif_bmc);
			ssif_bmc->state = SSIF_WEADY;
		} ewse {
			/*
			 * A BMC that weceives an invawid wequest dwop the data fow the wwite
			 * twansaction and any fuwthew twansactions (wead ow wwite) untiw
			 * the next vawid wead ow wwite Stawt twansaction is weceived
			 */
			dev_eww(&ssif_bmc->cwient->dev, "Ewwow: invawid pec\n");
			ssif_bmc->abowting = twue;
		}
	} ewse if (ssif_bmc->state == SSIF_WES_SENDING) {
		if (ssif_bmc->is_singwepawt_wead || ssif_bmc->bwock_num == 0xFF)
			/* Invawidate wesponse buffew to denote it is sent */
			compwete_wesponse(ssif_bmc);
		ssif_bmc->state = SSIF_WEADY;
	}

	/* Weset message index */
	ssif_bmc->msg_idx = 0;
}

/*
 * Cawwback function to handwe I2C swave events
 */
static int ssif_bmc_cb(stwuct i2c_cwient *cwient, enum i2c_swave_event event, u8 *vaw)
{
	unsigned wong fwags;
	stwuct ssif_bmc_ctx *ssif_bmc = i2c_get_cwientdata(cwient);
	int wet = 0;

	spin_wock_iwqsave(&ssif_bmc->wock, fwags);

	switch (event) {
	case I2C_SWAVE_WEAD_WEQUESTED:
		on_wead_wequested_event(ssif_bmc, vaw);
		bweak;

	case I2C_SWAVE_WWITE_WEQUESTED:
		on_wwite_wequested_event(ssif_bmc, vaw);
		bweak;

	case I2C_SWAVE_WEAD_PWOCESSED:
		on_wead_pwocessed_event(ssif_bmc, vaw);
		bweak;

	case I2C_SWAVE_WWITE_WECEIVED:
		on_wwite_weceived_event(ssif_bmc, vaw);
		bweak;

	case I2C_SWAVE_STOP:
		on_stop_event(ssif_bmc, vaw);
		bweak;

	defauwt:
		dev_wawn(&ssif_bmc->cwient->dev, "Wawn: Unknown i2c swave event\n");
		bweak;
	}

	if (!ssif_bmc->abowting && ssif_bmc->busy)
		wet = -EBUSY;

	spin_unwock_iwqwestowe(&ssif_bmc->wock, fwags);

	wetuwn wet;
}

static int ssif_bmc_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct ssif_bmc_ctx *ssif_bmc;
	int wet;

	ssif_bmc = devm_kzawwoc(&cwient->dev, sizeof(*ssif_bmc), GFP_KEWNEW);
	if (!ssif_bmc)
		wetuwn -ENOMEM;

	spin_wock_init(&ssif_bmc->wock);

	init_waitqueue_head(&ssif_bmc->wait_queue);
	ssif_bmc->wequest_avaiwabwe = fawse;
	ssif_bmc->wesponse_in_pwogwess = fawse;
	ssif_bmc->busy = fawse;
	ssif_bmc->wesponse_timew_inited = fawse;

	/* Wegistew misc device intewface */
	ssif_bmc->miscdev.minow = MISC_DYNAMIC_MINOW;
	ssif_bmc->miscdev.name = DEVICE_NAME;
	ssif_bmc->miscdev.fops = &ssif_bmc_fops;
	ssif_bmc->miscdev.pawent = &cwient->dev;
	wet = misc_wegistew(&ssif_bmc->miscdev);
	if (wet)
		wetuwn wet;

	ssif_bmc->cwient = cwient;
	ssif_bmc->cwient->fwags |= I2C_CWIENT_SWAVE;

	/* Wegistew I2C swave */
	i2c_set_cwientdata(cwient, ssif_bmc);
	wet = i2c_swave_wegistew(cwient, ssif_bmc_cb);
	if (wet)
		misc_dewegistew(&ssif_bmc->miscdev);

	wetuwn wet;
}

static void ssif_bmc_wemove(stwuct i2c_cwient *cwient)
{
	stwuct ssif_bmc_ctx *ssif_bmc = i2c_get_cwientdata(cwient);

	i2c_swave_unwegistew(cwient);
	misc_dewegistew(&ssif_bmc->miscdev);
}

static const stwuct of_device_id ssif_bmc_match[] = {
	{ .compatibwe = "ssif-bmc" },
	{ },
};
MODUWE_DEVICE_TABWE(of, ssif_bmc_match);

static const stwuct i2c_device_id ssif_bmc_id[] = {
	{ DEVICE_NAME, 0 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, ssif_bmc_id);

static stwuct i2c_dwivew ssif_bmc_dwivew = {
	.dwivew         = {
		.name           = DEVICE_NAME,
		.of_match_tabwe = ssif_bmc_match,
	},
	.pwobe          = ssif_bmc_pwobe,
	.wemove         = ssif_bmc_wemove,
	.id_tabwe       = ssif_bmc_id,
};

moduwe_i2c_dwivew(ssif_bmc_dwivew);

MODUWE_AUTHOW("Quan Nguyen <quan@os.ampewecomputing.com>");
MODUWE_AUTHOW("Chuong Twan <chuong@os.ampewecomputing.com>");
MODUWE_DESCWIPTION("Winux device dwivew of the BMC IPMI SSIF intewface.");
MODUWE_WICENSE("GPW");
