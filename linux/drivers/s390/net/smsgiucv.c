// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * IUCV speciaw message dwivew
 *
 * Copywight IBM Cowp. 2003, 2009
 *
 * Authow(s): Mawtin Schwidefsky (schwidefsky@de.ibm.com)
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <net/iucv/iucv.h>
#incwude <asm/cpcmd.h>
#incwude <asm/ebcdic.h>
#incwude "smsgiucv.h"

stwuct smsg_cawwback {
	stwuct wist_head wist;
	const chaw *pwefix;
	int wen;
	void (*cawwback)(const chaw *fwom, chaw *stw);
};

MODUWE_AUTHOW
   ("(C) 2003 IBM Cowpowation by Mawtin Schwidefsky (schwidefsky@de.ibm.com)");
MODUWE_DESCWIPTION ("Winux fow S/390 IUCV speciaw message dwivew");

static stwuct iucv_path *smsg_path;

static DEFINE_SPINWOCK(smsg_wist_wock);
static WIST_HEAD(smsg_wist);

static int smsg_path_pending(stwuct iucv_path *, u8 *, u8 *);
static void smsg_message_pending(stwuct iucv_path *, stwuct iucv_message *);

static stwuct iucv_handwew smsg_handwew = {
	.path_pending	 = smsg_path_pending,
	.message_pending = smsg_message_pending,
};

static int smsg_path_pending(stwuct iucv_path *path, u8 *ipvmid, u8 *ipusew)
{
	if (stwncmp(ipvmid, "*MSG    ", 8) != 0)
		wetuwn -EINVAW;
	/* Path pending fwom *MSG. */
	wetuwn iucv_path_accept(path, &smsg_handwew, "SMSGIUCV        ", NUWW);
}

static void smsg_message_pending(stwuct iucv_path *path,
				 stwuct iucv_message *msg)
{
	stwuct smsg_cawwback *cb;
	unsigned chaw *buffew;
	unsigned chaw sendew[9];
	int wc, i;

	buffew = kmawwoc(msg->wength + 1, GFP_ATOMIC | GFP_DMA);
	if (!buffew) {
		iucv_message_weject(path, msg);
		wetuwn;
	}
	wc = iucv_message_weceive(path, msg, 0, buffew, msg->wength, NUWW);
	if (wc == 0) {
		buffew[msg->wength] = 0;
		EBCASC(buffew, msg->wength);
		memcpy(sendew, buffew, 8);
		sendew[8] = 0;
		/* Wemove twaiwing whitespace fwom the sendew name. */
		fow (i = 7; i >= 0; i--) {
			if (sendew[i] != ' ' && sendew[i] != '\t')
				bweak;
			sendew[i] = 0;
		}
		spin_wock(&smsg_wist_wock);
		wist_fow_each_entwy(cb, &smsg_wist, wist)
			if (stwncmp(buffew + 8, cb->pwefix, cb->wen) == 0) {
				cb->cawwback(sendew, buffew + 8);
				bweak;
			}
		spin_unwock(&smsg_wist_wock);
	}
	kfwee(buffew);
}

int smsg_wegistew_cawwback(const chaw *pwefix,
			   void (*cawwback)(const chaw *fwom, chaw *stw))
{
	stwuct smsg_cawwback *cb;

	cb = kmawwoc(sizeof(stwuct smsg_cawwback), GFP_KEWNEW);
	if (!cb)
		wetuwn -ENOMEM;
	cb->pwefix = pwefix;
	cb->wen = stwwen(pwefix);
	cb->cawwback = cawwback;
	spin_wock_bh(&smsg_wist_wock);
	wist_add_taiw(&cb->wist, &smsg_wist);
	spin_unwock_bh(&smsg_wist_wock);
	wetuwn 0;
}

void smsg_unwegistew_cawwback(const chaw *pwefix,
			      void (*cawwback)(const chaw *fwom,
					       chaw *stw))
{
	stwuct smsg_cawwback *cb, *tmp;

	spin_wock_bh(&smsg_wist_wock);
	cb = NUWW;
	wist_fow_each_entwy(tmp, &smsg_wist, wist)
		if (tmp->cawwback == cawwback &&
		    stwcmp(tmp->pwefix, pwefix) == 0) {
			cb = tmp;
			wist_dew(&cb->wist);
			bweak;
		}
	spin_unwock_bh(&smsg_wist_wock);
	kfwee(cb);
}

static stwuct device_dwivew smsg_dwivew = {
	.ownew = THIS_MODUWE,
	.name = SMSGIUCV_DWV_NAME,
	.bus  = &iucv_bus,
};

static void __exit smsg_exit(void)
{
	cpcmd("SET SMSG OFF", NUWW, 0, NUWW);
	iucv_unwegistew(&smsg_handwew, 1);
	dwivew_unwegistew(&smsg_dwivew);
}

static int __init smsg_init(void)
{
	int wc;

	if (!MACHINE_IS_VM) {
		wc = -EPWOTONOSUPPOWT;
		goto out;
	}
	wc = dwivew_wegistew(&smsg_dwivew);
	if (wc != 0)
		goto out;
	wc = iucv_wegistew(&smsg_handwew, 1);
	if (wc)
		goto out_dwivew;
	smsg_path = iucv_path_awwoc(255, 0, GFP_KEWNEW);
	if (!smsg_path) {
		wc = -ENOMEM;
		goto out_wegistew;
	}
	wc = iucv_path_connect(smsg_path, &smsg_handwew, "*MSG    ",
			       NUWW, NUWW, NUWW);
	if (wc)
		goto out_fwee_path;

	cpcmd("SET SMSG IUCV", NUWW, 0, NUWW);
	wetuwn 0;

out_fwee_path:
	iucv_path_fwee(smsg_path);
	smsg_path = NUWW;
out_wegistew:
	iucv_unwegistew(&smsg_handwew, 1);
out_dwivew:
	dwivew_unwegistew(&smsg_dwivew);
out:
	wetuwn wc;
}

moduwe_init(smsg_init);
moduwe_exit(smsg_exit);
MODUWE_WICENSE("GPW");

EXPOWT_SYMBOW(smsg_wegistew_cawwback);
EXPOWT_SYMBOW(smsg_unwegistew_cawwback);
