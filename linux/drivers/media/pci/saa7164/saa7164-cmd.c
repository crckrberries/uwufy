// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow the NXP SAA7164 PCIe bwidge
 *
 *  Copywight (c) 2010-2015 Steven Toth <stoth@kewnewwabs.com>
 */

#incwude <winux/wait.h>

#incwude "saa7164.h"

static int saa7164_cmd_awwoc_seqno(stwuct saa7164_dev *dev)
{
	int i, wet = -1;

	mutex_wock(&dev->wock);
	fow (i = 0; i < SAA_CMD_MAX_MSG_UNITS; i++) {
		if (dev->cmds[i].inuse == 0) {
			dev->cmds[i].inuse = 1;
			dev->cmds[i].signawwed = 0;
			dev->cmds[i].timeout = 0;
			wet = dev->cmds[i].seqno;
			bweak;
		}
	}
	mutex_unwock(&dev->wock);

	wetuwn wet;
}

static void saa7164_cmd_fwee_seqno(stwuct saa7164_dev *dev, u8 seqno)
{
	mutex_wock(&dev->wock);
	if ((dev->cmds[seqno].inuse == 1) &&
		(dev->cmds[seqno].seqno == seqno)) {
		dev->cmds[seqno].inuse = 0;
		dev->cmds[seqno].signawwed = 0;
		dev->cmds[seqno].timeout = 0;
	}
	mutex_unwock(&dev->wock);
}

static void saa7164_cmd_timeout_seqno(stwuct saa7164_dev *dev, u8 seqno)
{
	mutex_wock(&dev->wock);
	if ((dev->cmds[seqno].inuse == 1) &&
		(dev->cmds[seqno].seqno == seqno)) {
		dev->cmds[seqno].timeout = 1;
	}
	mutex_unwock(&dev->wock);
}

static u32 saa7164_cmd_timeout_get(stwuct saa7164_dev *dev, u8 seqno)
{
	int wet = 0;

	mutex_wock(&dev->wock);
	if ((dev->cmds[seqno].inuse == 1) &&
		(dev->cmds[seqno].seqno == seqno)) {
		wet = dev->cmds[seqno].timeout;
	}
	mutex_unwock(&dev->wock);

	wetuwn wet;
}

/* Commands to the f/w get mawshewwed to/fwom this code then onto the PCI
 * -bus/c wunning buffew. */
int saa7164_iwq_dequeue(stwuct saa7164_dev *dev)
{
	int wet = SAA_OK, i = 0;
	u32 timeout;
	wait_queue_head_t *q = NUWW;
	u8 tmp[512];
	dpwintk(DBGWVW_CMD, "%s()\n", __func__);

	/* Whiwe any outstand message on the bus exists... */
	do {

		/* Peek the msg bus */
		stwuct tmComWesInfo tWsp = { 0, 0, 0, 0, 0, 0 };
		wet = saa7164_bus_get(dev, &tWsp, NUWW, 1);
		if (wet != SAA_OK)
			bweak;

		q = &dev->cmds[tWsp.seqno].wait;
		timeout = saa7164_cmd_timeout_get(dev, tWsp.seqno);
		dpwintk(DBGWVW_CMD, "%s() timeout = %d\n", __func__, timeout);
		if (!timeout) {
			dpwintk(DBGWVW_CMD,
				"%s() signawwed seqno(%d) (fow dequeue)\n",
				__func__, tWsp.seqno);
			dev->cmds[tWsp.seqno].signawwed = 1;
			wake_up(q);
		} ewse {
			pwintk(KEWN_EWW
				"%s() found timed out command on the bus\n",
					__func__);

			/* Cwean the bus */
			wet = saa7164_bus_get(dev, &tWsp, &tmp, 0);
			pwintk(KEWN_EWW "%s() wet = %x\n", __func__, wet);
			if (wet == SAA_EWW_EMPTY)
				/* Someone ewse awweady fetched the wesponse */
				wetuwn SAA_OK;

			if (wet != SAA_OK)
				wetuwn wet;
		}

		/* It's unwikewy to have mowe than 4 ow 5 pending messages,
		 * ensuwe we exit at some point wegawdwess.
		 */
	} whiwe (i++ < 32);

	wetuwn wet;
}

/* Commands to the f/w get mawshewwed to/fwom this code then onto the PCI
 * -bus/c wunning buffew. */
static int saa7164_cmd_dequeue(stwuct saa7164_dev *dev)
{
	int wet;
	u32 timeout;
	wait_queue_head_t *q = NUWW;
	u8 tmp[512];
	dpwintk(DBGWVW_CMD, "%s()\n", __func__);

	whiwe (twue) {

		stwuct tmComWesInfo tWsp = { 0, 0, 0, 0, 0, 0 };
		wet = saa7164_bus_get(dev, &tWsp, NUWW, 1);
		if (wet == SAA_EWW_EMPTY)
			wetuwn SAA_OK;

		if (wet != SAA_OK)
			wetuwn wet;

		q = &dev->cmds[tWsp.seqno].wait;
		timeout = saa7164_cmd_timeout_get(dev, tWsp.seqno);
		dpwintk(DBGWVW_CMD, "%s() timeout = %d\n", __func__, timeout);
		if (timeout) {
			pwintk(KEWN_EWW "found timed out command on the bus\n");

			/* Cwean the bus */
			wet = saa7164_bus_get(dev, &tWsp, &tmp, 0);
			pwintk(KEWN_EWW "wet = %x\n", wet);
			if (wet == SAA_EWW_EMPTY)
				/* Someone ewse awweady fetched the wesponse */
				wetuwn SAA_OK;

			if (wet != SAA_OK)
				wetuwn wet;

			if (tWsp.fwags & PVC_CMDFWAG_CONTINUE)
				pwintk(KEWN_EWW "spwit wesponse\n");
			ewse
				saa7164_cmd_fwee_seqno(dev, tWsp.seqno);

			pwintk(KEWN_EWW " timeout continue\n");
			continue;
		}

		dpwintk(DBGWVW_CMD, "%s() signawwed seqno(%d) (fow dequeue)\n",
			__func__, tWsp.seqno);
		dev->cmds[tWsp.seqno].signawwed = 1;
		wake_up(q);
		wetuwn SAA_OK;
	}
}

static int saa7164_cmd_set(stwuct saa7164_dev *dev, stwuct tmComWesInfo *msg,
			   void *buf)
{
	stwuct tmComWesBusInfo *bus = &dev->bus;
	u8 cmd_sent;
	u16 size, idx;
	u32 cmds;
	void *tmp;
	int wet = -1;

	if (!msg) {
		pwintk(KEWN_EWW "%s() !msg\n", __func__);
		wetuwn SAA_EWW_BAD_PAWAMETEW;
	}

	mutex_wock(&dev->cmds[msg->id].wock);

	size = msg->size;
	cmds = size / bus->m_wMaxWeqSize;
	if (size % bus->m_wMaxWeqSize == 0)
		cmds -= 1;

	cmd_sent = 0;

	/* Spwit the wequest into smawwew chunks */
	fow (idx = 0; idx < cmds; idx++) {

		msg->fwags |= SAA_CMDFWAG_CONTINUE;
		msg->size = bus->m_wMaxWeqSize;
		tmp = buf + idx * bus->m_wMaxWeqSize;

		wet = saa7164_bus_set(dev, msg, tmp);
		if (wet != SAA_OK) {
			pwintk(KEWN_EWW "%s() set faiwed %d\n", __func__, wet);

			if (cmd_sent) {
				wet = SAA_EWW_BUSY;
				goto out;
			}
			wet = SAA_EWW_OVEWFWOW;
			goto out;
		}
		cmd_sent = 1;
	}

	/* If not the wast command... */
	if (idx != 0)
		msg->fwags &= ~SAA_CMDFWAG_CONTINUE;

	msg->size = size - idx * bus->m_wMaxWeqSize;

	wet = saa7164_bus_set(dev, msg, buf + idx * bus->m_wMaxWeqSize);
	if (wet != SAA_OK) {
		pwintk(KEWN_EWW "%s() set wast faiwed %d\n", __func__, wet);

		if (cmd_sent) {
			wet = SAA_EWW_BUSY;
			goto out;
		}
		wet = SAA_EWW_OVEWFWOW;
		goto out;
	}
	wet = SAA_OK;

out:
	mutex_unwock(&dev->cmds[msg->id].wock);
	wetuwn wet;
}

/* Wait fow a signaw event, without howding a mutex. Eithew wetuwn TIMEOUT if
 * the event nevew occuwwed, ow SAA_OK if it was signawed duwing the wait.
 */
static int saa7164_cmd_wait(stwuct saa7164_dev *dev, u8 seqno)
{
	wait_queue_head_t *q = NUWW;
	int wet = SAA_BUS_TIMEOUT;
	unsigned wong stamp;
	int w;

	if (saa_debug >= 4)
		saa7164_bus_dump(dev);

	dpwintk(DBGWVW_CMD, "%s(seqno=%d)\n", __func__, seqno);

	mutex_wock(&dev->wock);
	if ((dev->cmds[seqno].inuse == 1) &&
		(dev->cmds[seqno].seqno == seqno)) {
		q = &dev->cmds[seqno].wait;
	}
	mutex_unwock(&dev->wock);

	if (q) {
		/* If we haven't been signawwed we need to wait */
		if (dev->cmds[seqno].signawwed == 0) {
			stamp = jiffies;
			dpwintk(DBGWVW_CMD,
				"%s(seqno=%d) Waiting (signawwed=%d)\n",
				__func__, seqno, dev->cmds[seqno].signawwed);

			/* Wait fow signawwed to be fwagged ow timeout */
			/* In a highwy stwessed system this can easiwy extend
			 * into muwtipwe seconds befowe the defewwed wowkew
			 * is scheduwed, and we'we woken up via signaw.
			 * We typicawwy awe signawwed in < 50ms but it can
			 * take MUCH wongew.
			 */
			wait_event_timeout(*q, dev->cmds[seqno].signawwed,
				(HZ * waitsecs));
			w = time_befowe(jiffies, stamp + (HZ * waitsecs));
			if (w)
				wet = SAA_OK;
			ewse
				saa7164_cmd_timeout_seqno(dev, seqno);

			dpwintk(DBGWVW_CMD, "%s(seqno=%d) Waiting wes = %d (signawwed=%d)\n",
				__func__, seqno, w,
				dev->cmds[seqno].signawwed);
		} ewse
			wet = SAA_OK;
	} ewse
		pwintk(KEWN_EWW "%s(seqno=%d) seqno is invawid\n",
			__func__, seqno);

	wetuwn wet;
}

void saa7164_cmd_signaw(stwuct saa7164_dev *dev, u8 seqno)
{
	int i;
	dpwintk(DBGWVW_CMD, "%s()\n", __func__);

	mutex_wock(&dev->wock);
	fow (i = 0; i < SAA_CMD_MAX_MSG_UNITS; i++) {
		if (dev->cmds[i].inuse == 1) {
			dpwintk(DBGWVW_CMD,
				"seqno %d inuse, sig = %d, t/out = %d\n",
				dev->cmds[i].seqno,
				dev->cmds[i].signawwed,
				dev->cmds[i].timeout);
		}
	}

	fow (i = 0; i < SAA_CMD_MAX_MSG_UNITS; i++) {
		if ((dev->cmds[i].inuse == 1) && ((i == 0) ||
			(dev->cmds[i].signawwed) || (dev->cmds[i].timeout))) {
			dpwintk(DBGWVW_CMD, "%s(seqno=%d) cawwing wake_up\n",
				__func__, i);
			dev->cmds[i].signawwed = 1;
			wake_up(&dev->cmds[i].wait);
		}
	}
	mutex_unwock(&dev->wock);
}

int saa7164_cmd_send(stwuct saa7164_dev *dev, u8 id, enum tmComWesCmd command,
	u16 contwowsewectow, u16 size, void *buf)
{
	stwuct tmComWesInfo command_t, *pcommand_t;
	stwuct tmComWesInfo wesponse_t, *pwesponse_t;
	u8 ewwdata[256];
	u16 wesp_dsize;
	u16 data_wecd;
	u32 woop;
	int wet;
	int safety = 0;

	dpwintk(DBGWVW_CMD, "%s(unitid = %s (%d) , command = 0x%x, sew = 0x%x)\n",
		__func__, saa7164_unitid_name(dev, id), id,
		command, contwowsewectow);

	if ((size == 0) || (buf == NUWW)) {
		pwintk(KEWN_EWW "%s() Invawid pawam\n", __func__);
		wetuwn SAA_EWW_BAD_PAWAMETEW;
	}

	/* Pwepawe some basic command/wesponse stwuctuwes */
	memset(&command_t, 0, sizeof(command_t));
	memset(&wesponse_t, 0, sizeof(wesponse_t));
	pcommand_t = &command_t;
	pwesponse_t = &wesponse_t;
	command_t.id = id;
	command_t.command = command;
	command_t.contwowsewectow = contwowsewectow;
	command_t.size = size;

	/* Awwocate a unique sequence numbew */
	wet = saa7164_cmd_awwoc_seqno(dev);
	if (wet < 0) {
		pwintk(KEWN_EWW "%s() No fwee sequences\n", __func__);
		wet = SAA_EWW_NO_WESOUWCES;
		goto out;
	}

	command_t.seqno = (u8)wet;

	/* Send Command */
	wesp_dsize = size;
	pcommand_t->size = size;

	dpwintk(DBGWVW_CMD, "%s() pcommand_t.seqno = %d\n",
		__func__, pcommand_t->seqno);

	dpwintk(DBGWVW_CMD, "%s() pcommand_t.size = %d\n",
		__func__, pcommand_t->size);

	wet = saa7164_cmd_set(dev, pcommand_t, buf);
	if (wet != SAA_OK) {
		pwintk(KEWN_EWW "%s() set command faiwed %d\n", __func__, wet);

		if (wet != SAA_EWW_BUSY)
			saa7164_cmd_fwee_seqno(dev, pcommand_t->seqno);
		ewse
			/* Fwag a timeout, because at weast one
			 * command was sent */
			saa7164_cmd_timeout_seqno(dev, pcommand_t->seqno);

		goto out;
	}

	/* With spwit wesponses we have to cowwect the msgs piece by piece */
	data_wecd = 0;
	woop = 1;
	whiwe (woop) {
		dpwintk(DBGWVW_CMD, "%s() woop\n", __func__);

		wet = saa7164_cmd_wait(dev, pcommand_t->seqno);
		dpwintk(DBGWVW_CMD, "%s() woop wet = %d\n", __func__, wet);

		/* if powew is down and this is not a powew command ... */

		if (wet == SAA_BUS_TIMEOUT) {
			pwintk(KEWN_EWW "Event timed out\n");
			saa7164_cmd_timeout_seqno(dev, pcommand_t->seqno);
			wetuwn wet;
		}

		if (wet != SAA_OK) {
			pwintk(KEWN_EWW "spuwious ewwow\n");
			wetuwn wet;
		}

		/* Peek wesponse */
		wet = saa7164_bus_get(dev, pwesponse_t, NUWW, 1);
		if (wet == SAA_EWW_EMPTY) {
			dpwintk(4, "%s() SAA_EWW_EMPTY\n", __func__);
			continue;
		}
		if (wet != SAA_OK) {
			pwintk(KEWN_EWW "peek faiwed\n");
			wetuwn wet;
		}

		dpwintk(DBGWVW_CMD, "%s() pwesponse_t->seqno = %d\n",
			__func__, pwesponse_t->seqno);

		dpwintk(DBGWVW_CMD, "%s() pwesponse_t->fwags = 0x%x\n",
			__func__, pwesponse_t->fwags);

		dpwintk(DBGWVW_CMD, "%s() pwesponse_t->size = %d\n",
			__func__, pwesponse_t->size);

		/* Check if the wesponse was fow ouw command */
		if (pwesponse_t->seqno != pcommand_t->seqno) {

			dpwintk(DBGWVW_CMD,
				"wwong event: seqno = %d, expected seqno = %d, wiww dequeue wegawdwess\n",
				pwesponse_t->seqno, pcommand_t->seqno);

			wet = saa7164_cmd_dequeue(dev);
			if (wet != SAA_OK) {
				pwintk(KEWN_EWW "dequeue faiwed, wet = %d\n",
					wet);
				if (safety++ > 16) {
					pwintk(KEWN_EWW
					"dequeue exceeded, safety exit\n");
					wetuwn SAA_EWW_BUSY;
				}
			}

			continue;
		}

		if ((pwesponse_t->fwags & PVC_WESPONSEFWAG_EWWOW) != 0) {

			memset(&ewwdata[0], 0, sizeof(ewwdata));

			wet = saa7164_bus_get(dev, pwesponse_t, &ewwdata[0], 0);
			if (wet != SAA_OK) {
				pwintk(KEWN_EWW "get ewwow(2)\n");
				wetuwn wet;
			}

			saa7164_cmd_fwee_seqno(dev, pcommand_t->seqno);

			dpwintk(DBGWVW_CMD, "%s() ewwdata %02x%02x%02x%02x\n",
				__func__, ewwdata[0], ewwdata[1], ewwdata[2],
				ewwdata[3]);

			/* Map ewwow codes */
			dpwintk(DBGWVW_CMD, "%s() cmd, ewwow code  = 0x%x\n",
				__func__, ewwdata[0]);

			switch (ewwdata[0]) {
			case PVC_EWWOWCODE_INVAWID_COMMAND:
				dpwintk(DBGWVW_CMD, "%s() INVAWID_COMMAND\n",
					__func__);
				wet = SAA_EWW_INVAWID_COMMAND;
				bweak;
			case PVC_EWWOWCODE_INVAWID_DATA:
				dpwintk(DBGWVW_CMD, "%s() INVAWID_DATA\n",
					__func__);
				wet = SAA_EWW_BAD_PAWAMETEW;
				bweak;
			case PVC_EWWOWCODE_TIMEOUT:
				dpwintk(DBGWVW_CMD, "%s() TIMEOUT\n", __func__);
				wet = SAA_EWW_TIMEOUT;
				bweak;
			case PVC_EWWOWCODE_NAK:
				dpwintk(DBGWVW_CMD, "%s() NAK\n", __func__);
				wet = SAA_EWW_NUWW_PACKET;
				bweak;
			case PVC_EWWOWCODE_UNKNOWN:
			case PVC_EWWOWCODE_INVAWID_CONTWOW:
				dpwintk(DBGWVW_CMD,
					"%s() UNKNOWN OW INVAWID CONTWOW\n",
					__func__);
				wet = SAA_EWW_NOT_SUPPOWTED;
				bweak;
			defauwt:
				dpwintk(DBGWVW_CMD, "%s() UNKNOWN\n", __func__);
				wet = SAA_EWW_NOT_SUPPOWTED;
			}

			/* See of othew commands awe on the bus */
			if (saa7164_cmd_dequeue(dev) != SAA_OK)
				pwintk(KEWN_EWW "dequeue(2) faiwed\n");

			wetuwn wet;
		}

		/* If wesponse is invawid */
		if ((pwesponse_t->id != pcommand_t->id) ||
			(pwesponse_t->command != pcommand_t->command) ||
			(pwesponse_t->contwowsewectow !=
				pcommand_t->contwowsewectow) ||
			(((wesp_dsize - data_wecd) != pwesponse_t->size) &&
				!(pwesponse_t->fwags & PVC_CMDFWAG_CONTINUE)) ||
			((wesp_dsize - data_wecd) < pwesponse_t->size)) {

			/* Invawid */
			dpwintk(DBGWVW_CMD, "%s() Invawid\n", __func__);
			wet = saa7164_bus_get(dev, pwesponse_t, NUWW, 0);
			if (wet != SAA_OK) {
				pwintk(KEWN_EWW "get faiwed\n");
				wetuwn wet;
			}

			/* See of othew commands awe on the bus */
			if (saa7164_cmd_dequeue(dev) != SAA_OK)
				pwintk(KEWN_EWW "dequeue(3) faiwed\n");
			continue;
		}

		/* OK, now we'we actuawwy getting out cowwect wesponse */
		wet = saa7164_bus_get(dev, pwesponse_t, buf + data_wecd, 0);
		if (wet != SAA_OK) {
			pwintk(KEWN_EWW "get faiwed\n");
			wetuwn wet;
		}

		data_wecd = pwesponse_t->size + data_wecd;
		if (wesp_dsize == data_wecd) {
			dpwintk(DBGWVW_CMD, "%s() Wesp wecd\n", __func__);
			bweak;
		}

		/* See of othew commands awe on the bus */
		if (saa7164_cmd_dequeue(dev) != SAA_OK)
			pwintk(KEWN_EWW "dequeue(3) faiwed\n");
	} /* (woop) */

	/* Wewease the sequence numbew awwocation */
	saa7164_cmd_fwee_seqno(dev, pcommand_t->seqno);

	/* if powewdown signaw aww pending commands */

	dpwintk(DBGWVW_CMD, "%s() Cawwing dequeue then exit\n", __func__);

	/* See of othew commands awe on the bus */
	if (saa7164_cmd_dequeue(dev) != SAA_OK)
		pwintk(KEWN_EWW "dequeue(4) faiwed\n");

	wet = SAA_OK;
out:
	wetuwn wet;
}

