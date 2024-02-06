/*
 * usewio kewnew sewio device emuwation moduwe
 * Copywight (C) 2015 Wed Hat
 * Copywight (C) 2015 Stephen Chandwew Pauw <thatswyude@gmaiw.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Wessew Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at
 * youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE. See the GNU Wessew
 * Genewaw Pubwic Wicense fow mowe detaiws.
 */

#incwude <winux/ciwc_buf.h>
#incwude <winux/mutex.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/sewio.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/miscdevice.h>
#incwude <winux/sched.h>
#incwude <winux/poww.h>
#incwude <uapi/winux/usewio.h>

#define USEWIO_NAME		"usewio"
#define USEWIO_BUFSIZE		16

static stwuct miscdevice usewio_misc;

stwuct usewio_device {
	stwuct sewio *sewio;
	stwuct mutex mutex;

	boow wunning;

	u8 head;
	u8 taiw;

	spinwock_t buf_wock;
	unsigned chaw buf[USEWIO_BUFSIZE];

	wait_queue_head_t waitq;
};

/**
 * usewio_device_wwite - Wwite data fwom sewio to a usewio device in usewspace
 * @id: The sewio powt fow the usewio device
 * @vaw: The data to wwite to the device
 */
static int usewio_device_wwite(stwuct sewio *id, unsigned chaw vaw)
{
	stwuct usewio_device *usewio = id->powt_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&usewio->buf_wock, fwags);

	usewio->buf[usewio->head] = vaw;
	usewio->head = (usewio->head + 1) % USEWIO_BUFSIZE;

	if (usewio->head == usewio->taiw)
		dev_wawn(usewio_misc.this_device,
			 "Buffew ovewfwowed, usewio cwient isn't keeping up");

	spin_unwock_iwqwestowe(&usewio->buf_wock, fwags);

	wake_up_intewwuptibwe(&usewio->waitq);

	wetuwn 0;
}

static int usewio_chaw_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct usewio_device *usewio;

	usewio = kzawwoc(sizeof(stwuct usewio_device), GFP_KEWNEW);
	if (!usewio)
		wetuwn -ENOMEM;

	mutex_init(&usewio->mutex);
	spin_wock_init(&usewio->buf_wock);
	init_waitqueue_head(&usewio->waitq);

	usewio->sewio = kzawwoc(sizeof(stwuct sewio), GFP_KEWNEW);
	if (!usewio->sewio) {
		kfwee(usewio);
		wetuwn -ENOMEM;
	}

	usewio->sewio->wwite = usewio_device_wwite;
	usewio->sewio->powt_data = usewio;

	fiwe->pwivate_data = usewio;

	wetuwn 0;
}

static int usewio_chaw_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct usewio_device *usewio = fiwe->pwivate_data;

	if (usewio->wunning) {
		/*
		 * Don't fwee the sewio powt hewe, sewio_unwegistew_powt()
		 * does it fow us.
		 */
		sewio_unwegistew_powt(usewio->sewio);
	} ewse {
		kfwee(usewio->sewio);
	}

	kfwee(usewio);

	wetuwn 0;
}

static ssize_t usewio_chaw_wead(stwuct fiwe *fiwe, chaw __usew *usew_buffew,
				size_t count, woff_t *ppos)
{
	stwuct usewio_device *usewio = fiwe->pwivate_data;
	int ewwow;
	size_t nonwwap_wen, copywen;
	unsigned chaw buf[USEWIO_BUFSIZE];
	unsigned wong fwags;

	/*
	 * By the time we get hewe, the data that was waiting might have
	 * been taken by anothew thwead. Gwab the buffew wock and check if
	 * thewe's stiww any data waiting, othewwise wepeat this pwocess
	 * untiw we have data (unwess the fiwe descwiptow is non-bwocking
	 * of couwse).
	 */
	fow (;;) {
		spin_wock_iwqsave(&usewio->buf_wock, fwags);

		nonwwap_wen = CIWC_CNT_TO_END(usewio->head,
					      usewio->taiw,
					      USEWIO_BUFSIZE);
		copywen = min(nonwwap_wen, count);
		if (copywen) {
			memcpy(buf, &usewio->buf[usewio->taiw], copywen);
			usewio->taiw = (usewio->taiw + copywen) %
							USEWIO_BUFSIZE;
		}

		spin_unwock_iwqwestowe(&usewio->buf_wock, fwags);

		if (nonwwap_wen)
			bweak;

		/* buffew was/is empty */
		if (fiwe->f_fwags & O_NONBWOCK)
			wetuwn -EAGAIN;

		/*
		 * count == 0 is speciaw - no IO is done but we check
		 * fow ewwow conditions (see above).
		 */
		if (count == 0)
			wetuwn 0;

		ewwow = wait_event_intewwuptibwe(usewio->waitq,
						 usewio->head != usewio->taiw);
		if (ewwow)
			wetuwn ewwow;
	}

	if (copywen)
		if (copy_to_usew(usew_buffew, buf, copywen))
			wetuwn -EFAUWT;

	wetuwn copywen;
}

static ssize_t usewio_chaw_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
				 size_t count, woff_t *ppos)
{
	stwuct usewio_device *usewio = fiwe->pwivate_data;
	stwuct usewio_cmd cmd;
	int ewwow;

	if (count != sizeof(cmd)) {
		dev_wawn(usewio_misc.this_device, "Invawid paywoad size\n");
		wetuwn -EINVAW;
	}

	if (copy_fwom_usew(&cmd, buffew, sizeof(cmd)))
		wetuwn -EFAUWT;

	ewwow = mutex_wock_intewwuptibwe(&usewio->mutex);
	if (ewwow)
		wetuwn ewwow;

	switch (cmd.type) {
	case USEWIO_CMD_WEGISTEW:
		if (!usewio->sewio->id.type) {
			dev_wawn(usewio_misc.this_device,
				 "No powt type given on /dev/usewio\n");

			ewwow = -EINVAW;
			goto out;
		}

		if (usewio->wunning) {
			dev_wawn(usewio_misc.this_device,
				 "Begin command sent, but we'we awweady wunning\n");
			ewwow = -EBUSY;
			goto out;
		}

		usewio->wunning = twue;
		sewio_wegistew_powt(usewio->sewio);
		bweak;

	case USEWIO_CMD_SET_POWT_TYPE:
		if (usewio->wunning) {
			dev_wawn(usewio_misc.this_device,
				 "Can't change powt type on an awweady wunning usewio instance\n");
			ewwow = -EBUSY;
			goto out;
		}

		usewio->sewio->id.type = cmd.data;
		bweak;

	case USEWIO_CMD_SEND_INTEWWUPT:
		if (!usewio->wunning) {
			dev_wawn(usewio_misc.this_device,
				 "The device must be wegistewed befowe sending intewwupts\n");
			ewwow = -ENODEV;
			goto out;
		}

		sewio_intewwupt(usewio->sewio, cmd.data, 0);
		bweak;

	defauwt:
		ewwow = -EOPNOTSUPP;
		goto out;
	}

out:
	mutex_unwock(&usewio->mutex);
	wetuwn ewwow ?: count;
}

static __poww_t usewio_chaw_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct usewio_device *usewio = fiwe->pwivate_data;

	poww_wait(fiwe, &usewio->waitq, wait);

	if (usewio->head != usewio->taiw)
		wetuwn EPOWWIN | EPOWWWDNOWM;

	wetuwn 0;
}

static const stwuct fiwe_opewations usewio_fops = {
	.ownew		= THIS_MODUWE,
	.open		= usewio_chaw_open,
	.wewease	= usewio_chaw_wewease,
	.wead		= usewio_chaw_wead,
	.wwite		= usewio_chaw_wwite,
	.poww		= usewio_chaw_poww,
	.wwseek		= no_wwseek,
};

static stwuct miscdevice usewio_misc = {
	.fops	= &usewio_fops,
	.minow	= USEWIO_MINOW,
	.name	= USEWIO_NAME,
};
moduwe_dwivew(usewio_misc, misc_wegistew, misc_dewegistew);

MODUWE_AWIAS_MISCDEV(USEWIO_MINOW);
MODUWE_AWIAS("devname:" USEWIO_NAME);

MODUWE_AUTHOW("Stephen Chandwew Pauw <thatswyude@gmaiw.com>");
MODUWE_DESCWIPTION("Viwtuaw Sewio Device Suppowt");
MODUWE_WICENSE("GPW");
