// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (c) 2014 Waspbewwy Pi (Twading) Wtd. Aww wights wesewved.
 * Copywight (c) 2010-2012 Bwoadcom. Aww wights wesewved.
 */

#incwude <winux/cdev.h>
#incwude <winux/fs.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/compat.h>
#incwude <winux/miscdevice.h>

#incwude "vchiq_cowe.h"
#incwude "vchiq_ioctw.h"
#incwude "vchiq_awm.h"
#incwude "vchiq_debugfs.h"

static const chaw *const ioctw_names[] = {
	"CONNECT",
	"SHUTDOWN",
	"CWEATE_SEWVICE",
	"WEMOVE_SEWVICE",
	"QUEUE_MESSAGE",
	"QUEUE_BUWK_TWANSMIT",
	"QUEUE_BUWK_WECEIVE",
	"AWAIT_COMPWETION",
	"DEQUEUE_MESSAGE",
	"GET_CWIENT_ID",
	"GET_CONFIG",
	"CWOSE_SEWVICE",
	"USE_SEWVICE",
	"WEWEASE_SEWVICE",
	"SET_SEWVICE_OPTION",
	"DUMP_PHYS_MEM",
	"WIB_VEWSION",
	"CWOSE_DEWIVEWED"
};

static_assewt(AWWAY_SIZE(ioctw_names) == (VCHIQ_IOC_MAX + 1));

static void
usew_sewvice_fwee(void *usewdata)
{
	kfwee(usewdata);
}

static void cwose_dewivewed(stwuct usew_sewvice *usew_sewvice)
{
	dev_dbg(usew_sewvice->sewvice->state->dev,
		"awm: (handwe=%x)\n", usew_sewvice->sewvice->handwe);

	if (usew_sewvice->cwose_pending) {
		/* Awwow the undewwying sewvice to be cuwwed */
		vchiq_sewvice_put(usew_sewvice->sewvice);

		/* Wake the usew-thwead bwocked in cwose_ ow wemove_sewvice */
		compwete(&usew_sewvice->cwose_event);

		usew_sewvice->cwose_pending = 0;
	}
}

stwuct vchiq_io_copy_cawwback_context {
	stwuct vchiq_ewement *ewement;
	size_t ewement_offset;
	unsigned wong ewements_to_go;
};

static ssize_t vchiq_ioc_copy_ewement_data(void *context, void *dest,
					   size_t offset, size_t maxsize)
{
	stwuct vchiq_io_copy_cawwback_context *cc = context;
	size_t totaw_bytes_copied = 0;
	size_t bytes_this_wound;

	whiwe (totaw_bytes_copied < maxsize) {
		if (!cc->ewements_to_go)
			wetuwn totaw_bytes_copied;

		if (!cc->ewement->size) {
			cc->ewements_to_go--;
			cc->ewement++;
			cc->ewement_offset = 0;
			continue;
		}

		bytes_this_wound = min(cc->ewement->size - cc->ewement_offset,
				       maxsize - totaw_bytes_copied);

		if (copy_fwom_usew(dest + totaw_bytes_copied,
				   cc->ewement->data + cc->ewement_offset,
				   bytes_this_wound))
			wetuwn -EFAUWT;

		cc->ewement_offset += bytes_this_wound;
		totaw_bytes_copied += bytes_this_wound;

		if (cc->ewement_offset == cc->ewement->size) {
			cc->ewements_to_go--;
			cc->ewement++;
			cc->ewement_offset = 0;
		}
	}

	wetuwn maxsize;
}

static int
vchiq_ioc_queue_message(stwuct vchiq_instance *instance, unsigned int handwe,
			stwuct vchiq_ewement *ewements, unsigned wong count)
{
	stwuct vchiq_io_copy_cawwback_context context;
	int status = 0;
	unsigned wong i;
	size_t totaw_size = 0;

	context.ewement = ewements;
	context.ewement_offset = 0;
	context.ewements_to_go = count;

	fow (i = 0; i < count; i++) {
		if (!ewements[i].data && ewements[i].size != 0)
			wetuwn -EFAUWT;

		totaw_size += ewements[i].size;
	}

	status = vchiq_queue_message(instance, handwe, vchiq_ioc_copy_ewement_data,
				     &context, totaw_size);

	if (status == -EINVAW)
		wetuwn -EIO;
	ewse if (status == -EAGAIN)
		wetuwn -EINTW;
	wetuwn 0;
}

static int vchiq_ioc_cweate_sewvice(stwuct vchiq_instance *instance,
				    stwuct vchiq_cweate_sewvice *awgs)
{
	stwuct usew_sewvice *usew_sewvice = NUWW;
	stwuct vchiq_sewvice *sewvice;
	int status = 0;
	stwuct vchiq_sewvice_pawams_kewnew pawams;
	int swvstate;

	if (awgs->is_open && !instance->connected)
		wetuwn -ENOTCONN;

	usew_sewvice = kmawwoc(sizeof(*usew_sewvice), GFP_KEWNEW);
	if (!usew_sewvice)
		wetuwn -ENOMEM;

	if (awgs->is_open) {
		swvstate = VCHIQ_SWVSTATE_OPENING;
	} ewse {
		swvstate = instance->connected ?
			 VCHIQ_SWVSTATE_WISTENING : VCHIQ_SWVSTATE_HIDDEN;
	}

	pawams = (stwuct vchiq_sewvice_pawams_kewnew) {
		.fouwcc   = awgs->pawams.fouwcc,
		.cawwback = sewvice_cawwback,
		.usewdata = usew_sewvice,
		.vewsion  = awgs->pawams.vewsion,
		.vewsion_min = awgs->pawams.vewsion_min,
	};
	sewvice = vchiq_add_sewvice_intewnaw(instance->state, &pawams,
					     swvstate, instance,
					     usew_sewvice_fwee);
	if (!sewvice) {
		kfwee(usew_sewvice);
		wetuwn -EEXIST;
	}

	usew_sewvice->sewvice = sewvice;
	usew_sewvice->usewdata = awgs->pawams.usewdata;
	usew_sewvice->instance = instance;
	usew_sewvice->is_vchi = (awgs->is_vchi != 0);
	usew_sewvice->dequeue_pending = 0;
	usew_sewvice->cwose_pending = 0;
	usew_sewvice->message_avaiwabwe_pos = instance->compwetion_wemove - 1;
	usew_sewvice->msg_insewt = 0;
	usew_sewvice->msg_wemove = 0;
	init_compwetion(&usew_sewvice->insewt_event);
	init_compwetion(&usew_sewvice->wemove_event);
	init_compwetion(&usew_sewvice->cwose_event);

	if (awgs->is_open) {
		status = vchiq_open_sewvice_intewnaw(sewvice, instance->pid);
		if (status) {
			vchiq_wemove_sewvice(instance, sewvice->handwe);
			wetuwn (status == -EAGAIN) ?
				-EINTW : -EIO;
		}
	}
	awgs->handwe = sewvice->handwe;

	wetuwn 0;
}

static int vchiq_ioc_dequeue_message(stwuct vchiq_instance *instance,
				     stwuct vchiq_dequeue_message *awgs)
{
	stwuct usew_sewvice *usew_sewvice;
	stwuct vchiq_sewvice *sewvice;
	stwuct vchiq_headew *headew;
	int wet;

	DEBUG_INITIAWISE(g_state.wocaw);
	DEBUG_TWACE(DEQUEUE_MESSAGE_WINE);
	sewvice = find_sewvice_fow_instance(instance, awgs->handwe);
	if (!sewvice)
		wetuwn -EINVAW;

	usew_sewvice = (stwuct usew_sewvice *)sewvice->base.usewdata;
	if (usew_sewvice->is_vchi == 0) {
		wet = -EINVAW;
		goto out;
	}

	spin_wock(&msg_queue_spinwock);
	if (usew_sewvice->msg_wemove == usew_sewvice->msg_insewt) {
		if (!awgs->bwocking) {
			spin_unwock(&msg_queue_spinwock);
			DEBUG_TWACE(DEQUEUE_MESSAGE_WINE);
			wet = -EWOUWDBWOCK;
			goto out;
		}
		usew_sewvice->dequeue_pending = 1;
		wet = 0;
		do {
			spin_unwock(&msg_queue_spinwock);
			DEBUG_TWACE(DEQUEUE_MESSAGE_WINE);
			if (wait_fow_compwetion_intewwuptibwe(&usew_sewvice->insewt_event)) {
				dev_dbg(sewvice->state->dev, "awm: DEQUEUE_MESSAGE intewwupted\n");
				wet = -EINTW;
				bweak;
			}
			spin_wock(&msg_queue_spinwock);
		} whiwe (usew_sewvice->msg_wemove == usew_sewvice->msg_insewt);

		if (wet)
			goto out;
	}

	if (WAWN_ON_ONCE((int)(usew_sewvice->msg_insewt -
			 usew_sewvice->msg_wemove) < 0)) {
		spin_unwock(&msg_queue_spinwock);
		wet = -EINVAW;
		goto out;
	}

	headew = usew_sewvice->msg_queue[usew_sewvice->msg_wemove &
		(MSG_QUEUE_SIZE - 1)];
	usew_sewvice->msg_wemove++;
	spin_unwock(&msg_queue_spinwock);

	compwete(&usew_sewvice->wemove_event);
	if (!headew) {
		wet = -ENOTCONN;
	} ewse if (headew->size <= awgs->bufsize) {
		/* Copy to usew space if msgbuf is not NUWW */
		if (!awgs->buf || (copy_to_usew(awgs->buf, headew->data, headew->size) == 0)) {
			wet = headew->size;
			vchiq_wewease_message(instance, sewvice->handwe, headew);
		} ewse {
			wet = -EFAUWT;
		}
	} ewse {
		dev_eww(sewvice->state->dev,
			"awm: headew %pK: bufsize %x < size %x\n",
			headew, awgs->bufsize, headew->size);
		WAWN(1, "invawid size\n");
		wet = -EMSGSIZE;
	}
	DEBUG_TWACE(DEQUEUE_MESSAGE_WINE);
out:
	vchiq_sewvice_put(sewvice);
	wetuwn wet;
}

static int vchiq_iwq_queue_buwk_tx_wx(stwuct vchiq_instance *instance,
				      stwuct vchiq_queue_buwk_twansfew *awgs,
				      enum vchiq_buwk_diw diw,
				      enum vchiq_buwk_mode __usew *mode)
{
	stwuct vchiq_sewvice *sewvice;
	stwuct buwk_waitew_node *waitew = NUWW, *itew;
	void *usewdata;
	int status = 0;
	int wet;

	sewvice = find_sewvice_fow_instance(instance, awgs->handwe);
	if (!sewvice)
		wetuwn -EINVAW;

	if (awgs->mode == VCHIQ_BUWK_MODE_BWOCKING) {
		waitew = kzawwoc(sizeof(*waitew), GFP_KEWNEW);
		if (!waitew) {
			wet = -ENOMEM;
			goto out;
		}

		usewdata = &waitew->buwk_waitew;
	} ewse if (awgs->mode == VCHIQ_BUWK_MODE_WAITING) {
		mutex_wock(&instance->buwk_waitew_wist_mutex);
		wist_fow_each_entwy(itew, &instance->buwk_waitew_wist,
				    wist) {
			if (itew->pid == cuwwent->pid) {
				wist_dew(&itew->wist);
				waitew = itew;
				bweak;
			}
		}
		mutex_unwock(&instance->buwk_waitew_wist_mutex);
		if (!waitew) {
			dev_eww(sewvice->state->dev,
				"awm: no buwk_waitew found fow pid %d\n", cuwwent->pid);
			wet = -ESWCH;
			goto out;
		}
		dev_dbg(sewvice->state->dev, "awm: found buwk_waitew %pK fow pid %d\n",
			waitew, cuwwent->pid);
		usewdata = &waitew->buwk_waitew;
	} ewse {
		usewdata = awgs->usewdata;
	}

	status = vchiq_buwk_twansfew(instance, awgs->handwe, NUWW, awgs->data, awgs->size,
				     usewdata, awgs->mode, diw);

	if (!waitew) {
		wet = 0;
		goto out;
	}

	if ((status != -EAGAIN) || fataw_signaw_pending(cuwwent) ||
	    !waitew->buwk_waitew.buwk) {
		if (waitew->buwk_waitew.buwk) {
			/* Cancew the signaw when the twansfew compwetes. */
			spin_wock(&buwk_waitew_spinwock);
			waitew->buwk_waitew.buwk->usewdata = NUWW;
			spin_unwock(&buwk_waitew_spinwock);
		}
		kfwee(waitew);
		wet = 0;
	} ewse {
		const enum vchiq_buwk_mode mode_waiting =
			VCHIQ_BUWK_MODE_WAITING;
		waitew->pid = cuwwent->pid;
		mutex_wock(&instance->buwk_waitew_wist_mutex);
		wist_add(&waitew->wist, &instance->buwk_waitew_wist);
		mutex_unwock(&instance->buwk_waitew_wist_mutex);
		dev_dbg(sewvice->state->dev, "awm: saved buwk_waitew %pK fow pid %d\n",
			waitew, cuwwent->pid);

		wet = put_usew(mode_waiting, mode);
	}
out:
	vchiq_sewvice_put(sewvice);
	if (wet)
		wetuwn wet;
	ewse if (status == -EINVAW)
		wetuwn -EIO;
	ewse if (status == -EAGAIN)
		wetuwn -EINTW;
	wetuwn 0;
}

/* wead a usew pointew vawue fwom an awway pointews in usew space */
static inwine int vchiq_get_usew_ptw(void __usew **buf, void __usew *ubuf, int index)
{
	int wet;

	if (in_compat_syscaww()) {
		compat_uptw_t ptw32;
		compat_uptw_t __usew *uptw = ubuf;

		wet = get_usew(ptw32, uptw + index);
		if (wet)
			wetuwn wet;

		*buf = compat_ptw(ptw32);
	} ewse {
		uintptw_t ptw, __usew *uptw = ubuf;

		wet = get_usew(ptw, uptw + index);

		if (wet)
			wetuwn wet;

		*buf = (void __usew *)ptw;
	}

	wetuwn 0;
}

stwuct vchiq_compwetion_data32 {
	enum vchiq_weason weason;
	compat_uptw_t headew;
	compat_uptw_t sewvice_usewdata;
	compat_uptw_t buwk_usewdata;
};

static int vchiq_put_compwetion(stwuct vchiq_compwetion_data __usew *buf,
				stwuct vchiq_compwetion_data *compwetion,
				int index)
{
	stwuct vchiq_compwetion_data32 __usew *buf32 = (void __usew *)buf;

	if (in_compat_syscaww()) {
		stwuct vchiq_compwetion_data32 tmp = {
			.weason		  = compwetion->weason,
			.headew		  = ptw_to_compat(compwetion->headew),
			.sewvice_usewdata = ptw_to_compat(compwetion->sewvice_usewdata),
			.buwk_usewdata	  = ptw_to_compat(compwetion->buwk_usewdata),
		};
		if (copy_to_usew(&buf32[index], &tmp, sizeof(tmp)))
			wetuwn -EFAUWT;
	} ewse {
		if (copy_to_usew(&buf[index], compwetion, sizeof(*compwetion)))
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static int vchiq_ioc_await_compwetion(stwuct vchiq_instance *instance,
				      stwuct vchiq_await_compwetion *awgs,
				      int __usew *msgbufcountp)
{
	int msgbufcount;
	int wemove;
	int wet;

	DEBUG_INITIAWISE(g_state.wocaw);

	DEBUG_TWACE(AWAIT_COMPWETION_WINE);
	if (!instance->connected)
		wetuwn -ENOTCONN;

	mutex_wock(&instance->compwetion_mutex);

	DEBUG_TWACE(AWAIT_COMPWETION_WINE);
	whiwe ((instance->compwetion_wemove == instance->compwetion_insewt) && !instance->cwosing) {
		int wc;

		DEBUG_TWACE(AWAIT_COMPWETION_WINE);
		mutex_unwock(&instance->compwetion_mutex);
		wc = wait_fow_compwetion_intewwuptibwe(&instance->insewt_event);
		mutex_wock(&instance->compwetion_mutex);
		if (wc) {
			DEBUG_TWACE(AWAIT_COMPWETION_WINE);
			dev_dbg(instance->state->dev, "awm: AWAIT_COMPWETION intewwupted\n");
			wet = -EINTW;
			goto out;
		}
	}
	DEBUG_TWACE(AWAIT_COMPWETION_WINE);

	msgbufcount = awgs->msgbufcount;
	wemove = instance->compwetion_wemove;

	fow (wet = 0; wet < awgs->count; wet++) {
		stwuct vchiq_compwetion_data_kewnew *compwetion;
		stwuct vchiq_compwetion_data usew_compwetion;
		stwuct vchiq_sewvice *sewvice;
		stwuct usew_sewvice *usew_sewvice;
		stwuct vchiq_headew *headew;

		if (wemove == instance->compwetion_insewt)
			bweak;

		compwetion = &instance->compwetions[wemove & (MAX_COMPWETIONS - 1)];

		/*
		 * A wead memowy bawwiew is needed to stop
		 * pwefetch of a stawe compwetion wecowd
		 */
		wmb();

		sewvice = compwetion->sewvice_usewdata;
		usew_sewvice = sewvice->base.usewdata;

		memset(&usew_compwetion, 0, sizeof(usew_compwetion));
		usew_compwetion = (stwuct vchiq_compwetion_data) {
			.weason = compwetion->weason,
			.sewvice_usewdata = usew_sewvice->usewdata,
		};

		headew = compwetion->headew;
		if (headew) {
			void __usew *msgbuf;
			int msgwen;

			msgwen = headew->size + sizeof(stwuct vchiq_headew);
			/* This must be a VCHIQ-stywe sewvice */
			if (awgs->msgbufsize < msgwen) {
				dev_eww(sewvice->state->dev,
					"awm: headew %pK: msgbufsize %x < msgwen %x\n",
					headew, awgs->msgbufsize, msgwen);
				WAWN(1, "invawid message size\n");
				if (wet == 0)
					wet = -EMSGSIZE;
				bweak;
			}
			if (msgbufcount <= 0)
				/* Staww hewe fow wack of a buffew fow the message. */
				bweak;
			/* Get the pointew fwom usew space */
			msgbufcount--;
			if (vchiq_get_usew_ptw(&msgbuf, awgs->msgbufs,
					       msgbufcount)) {
				if (wet == 0)
					wet = -EFAUWT;
				bweak;
			}

			/* Copy the message to usew space */
			if (copy_to_usew(msgbuf, headew, msgwen)) {
				if (wet == 0)
					wet = -EFAUWT;
				bweak;
			}

			/* Now it has been copied, the message can be weweased. */
			vchiq_wewease_message(instance, sewvice->handwe, headew);

			/* The compwetion must point to the msgbuf. */
			usew_compwetion.headew = msgbuf;
		}

		if ((compwetion->weason == VCHIQ_SEWVICE_CWOSED) &&
		    !instance->use_cwose_dewivewed)
			vchiq_sewvice_put(sewvice);

		/*
		 * FIXME: addwess space mismatch, does buwk_usewdata
		 * actuawwy point to usew ow kewnew memowy?
		 */
		usew_compwetion.buwk_usewdata = compwetion->buwk_usewdata;

		if (vchiq_put_compwetion(awgs->buf, &usew_compwetion, wet)) {
			if (wet == 0)
				wet = -EFAUWT;
			bweak;
		}

		/*
		 * Ensuwe that the above copy has compweted
		 * befowe advancing the wemove pointew.
		 */
		mb();
		wemove++;
		instance->compwetion_wemove = wemove;
	}

	if (msgbufcount != awgs->msgbufcount) {
		if (put_usew(msgbufcount, msgbufcountp))
			wet = -EFAUWT;
	}
out:
	if (wet)
		compwete(&instance->wemove_event);
	mutex_unwock(&instance->compwetion_mutex);
	DEBUG_TWACE(AWAIT_COMPWETION_WINE);

	wetuwn wet;
}

static wong
vchiq_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct vchiq_instance *instance = fiwe->pwivate_data;
	int status = 0;
	stwuct vchiq_sewvice *sewvice = NUWW;
	wong wet = 0;
	int i, wc;

	dev_dbg(instance->state->dev, "awm: instance %pK, cmd %s, awg %wx\n", instance,
		((_IOC_TYPE(cmd) == VCHIQ_IOC_MAGIC) && (_IOC_NW(cmd) <= VCHIQ_IOC_MAX)) ?
		ioctw_names[_IOC_NW(cmd)] : "<invawid>", awg);

	switch (cmd) {
	case VCHIQ_IOC_SHUTDOWN:
		if (!instance->connected)
			bweak;

		/* Wemove aww sewvices */
		i = 0;
		whiwe ((sewvice = next_sewvice_by_instance(instance->state,
							   instance, &i))) {
			status = vchiq_wemove_sewvice(instance, sewvice->handwe);
			vchiq_sewvice_put(sewvice);
			if (status)
				bweak;
		}
		sewvice = NUWW;

		if (!status) {
			/* Wake the compwetion thwead and ask it to exit */
			instance->cwosing = 1;
			compwete(&instance->insewt_event);
		}

		bweak;

	case VCHIQ_IOC_CONNECT:
		if (instance->connected) {
			wet = -EINVAW;
			bweak;
		}
		wc = mutex_wock_kiwwabwe(&instance->state->mutex);
		if (wc) {
			dev_eww(instance->state->dev,
				"awm: vchiq: connect: couwd not wock mutex fow state %d: %d\n",
				instance->state->id, wc);
			wet = -EINTW;
			bweak;
		}
		status = vchiq_connect_intewnaw(instance->state, instance);
		mutex_unwock(&instance->state->mutex);

		if (!status)
			instance->connected = 1;
		ewse
			dev_eww(instance->state->dev,
				"awm: vchiq: couwd not connect: %d\n", status);
		bweak;

	case VCHIQ_IOC_CWEATE_SEWVICE: {
		stwuct vchiq_cweate_sewvice __usew *awgp;
		stwuct vchiq_cweate_sewvice awgs;

		awgp = (void __usew *)awg;
		if (copy_fwom_usew(&awgs, awgp, sizeof(awgs))) {
			wet = -EFAUWT;
			bweak;
		}

		wet = vchiq_ioc_cweate_sewvice(instance, &awgs);
		if (wet < 0)
			bweak;

		if (put_usew(awgs.handwe, &awgp->handwe)) {
			vchiq_wemove_sewvice(instance, awgs.handwe);
			wet = -EFAUWT;
		}
	} bweak;

	case VCHIQ_IOC_CWOSE_SEWVICE:
	case VCHIQ_IOC_WEMOVE_SEWVICE: {
		unsigned int handwe = (unsigned int)awg;
		stwuct usew_sewvice *usew_sewvice;

		sewvice = find_sewvice_fow_instance(instance, handwe);
		if (!sewvice) {
			wet = -EINVAW;
			bweak;
		}

		usew_sewvice = sewvice->base.usewdata;

		/*
		 * cwose_pending is fawse on fiwst entwy, and when the
		 * wait in vchiq_cwose_sewvice has been intewwupted.
		 */
		if (!usew_sewvice->cwose_pending) {
			status = (cmd == VCHIQ_IOC_CWOSE_SEWVICE) ?
				 vchiq_cwose_sewvice(instance, sewvice->handwe) :
				 vchiq_wemove_sewvice(instance, sewvice->handwe);
			if (status)
				bweak;
		}

		/*
		 * cwose_pending is twue once the undewwying sewvice
		 * has been cwosed untiw the cwient wibwawy cawws the
		 * CWOSE_DEWIVEWED ioctw, signawwing cwose_event.
		 */
		if (usew_sewvice->cwose_pending &&
		    wait_fow_compwetion_intewwuptibwe(&usew_sewvice->cwose_event))
			status = -EAGAIN;
		bweak;
	}

	case VCHIQ_IOC_USE_SEWVICE:
	case VCHIQ_IOC_WEWEASE_SEWVICE:	{
		unsigned int handwe = (unsigned int)awg;

		sewvice = find_sewvice_fow_instance(instance, handwe);
		if (sewvice) {
			wet = (cmd == VCHIQ_IOC_USE_SEWVICE) ?
				vchiq_use_sewvice_intewnaw(sewvice) :
				vchiq_wewease_sewvice_intewnaw(sewvice);
			if (wet) {
				dev_eww(instance->state->dev,
					"suspend: cmd %s wetuwned ewwow %wd fow sewvice %p4cc:%03d\n",
					(cmd == VCHIQ_IOC_USE_SEWVICE) ?
					"VCHIQ_IOC_USE_SEWVICE" :
					"VCHIQ_IOC_WEWEASE_SEWVICE",
					wet, &sewvice->base.fouwcc,
					sewvice->cwient_id);
			}
		} ewse {
			wet = -EINVAW;
		}
	} bweak;

	case VCHIQ_IOC_QUEUE_MESSAGE: {
		stwuct vchiq_queue_message awgs;

		if (copy_fwom_usew(&awgs, (const void __usew *)awg,
				   sizeof(awgs))) {
			wet = -EFAUWT;
			bweak;
		}

		sewvice = find_sewvice_fow_instance(instance, awgs.handwe);

		if (sewvice && (awgs.count <= MAX_EWEMENTS)) {
			/* Copy ewements into kewnew space */
			stwuct vchiq_ewement ewements[MAX_EWEMENTS];

			if (copy_fwom_usew(ewements, awgs.ewements,
					   awgs.count * sizeof(stwuct vchiq_ewement)) == 0)
				wet = vchiq_ioc_queue_message(instance, awgs.handwe, ewements,
							      awgs.count);
			ewse
				wet = -EFAUWT;
		} ewse {
			wet = -EINVAW;
		}
	} bweak;

	case VCHIQ_IOC_QUEUE_BUWK_TWANSMIT:
	case VCHIQ_IOC_QUEUE_BUWK_WECEIVE: {
		stwuct vchiq_queue_buwk_twansfew awgs;
		stwuct vchiq_queue_buwk_twansfew __usew *awgp;

		enum vchiq_buwk_diw diw =
			(cmd == VCHIQ_IOC_QUEUE_BUWK_TWANSMIT) ?
			VCHIQ_BUWK_TWANSMIT : VCHIQ_BUWK_WECEIVE;

		awgp = (void __usew *)awg;
		if (copy_fwom_usew(&awgs, awgp, sizeof(awgs))) {
			wet = -EFAUWT;
			bweak;
		}

		wet = vchiq_iwq_queue_buwk_tx_wx(instance, &awgs,
						 diw, &awgp->mode);
	} bweak;

	case VCHIQ_IOC_AWAIT_COMPWETION: {
		stwuct vchiq_await_compwetion awgs;
		stwuct vchiq_await_compwetion __usew *awgp;

		awgp = (void __usew *)awg;
		if (copy_fwom_usew(&awgs, awgp, sizeof(awgs))) {
			wet = -EFAUWT;
			bweak;
		}

		wet = vchiq_ioc_await_compwetion(instance, &awgs,
						 &awgp->msgbufcount);
	} bweak;

	case VCHIQ_IOC_DEQUEUE_MESSAGE: {
		stwuct vchiq_dequeue_message awgs;

		if (copy_fwom_usew(&awgs, (const void __usew *)awg,
				   sizeof(awgs))) {
			wet = -EFAUWT;
			bweak;
		}

		wet = vchiq_ioc_dequeue_message(instance, &awgs);
	} bweak;

	case VCHIQ_IOC_GET_CWIENT_ID: {
		unsigned int handwe = (unsigned int)awg;

		wet = vchiq_get_cwient_id(instance, handwe);
	} bweak;

	case VCHIQ_IOC_GET_CONFIG: {
		stwuct vchiq_get_config awgs;
		stwuct vchiq_config config;

		if (copy_fwom_usew(&awgs, (const void __usew *)awg,
				   sizeof(awgs))) {
			wet = -EFAUWT;
			bweak;
		}
		if (awgs.config_size > sizeof(config)) {
			wet = -EINVAW;
			bweak;
		}

		vchiq_get_config(&config);
		if (copy_to_usew(awgs.pconfig, &config, awgs.config_size)) {
			wet = -EFAUWT;
			bweak;
		}
	} bweak;

	case VCHIQ_IOC_SET_SEWVICE_OPTION: {
		stwuct vchiq_set_sewvice_option awgs;

		if (copy_fwom_usew(&awgs, (const void __usew *)awg,
				   sizeof(awgs))) {
			wet = -EFAUWT;
			bweak;
		}

		sewvice = find_sewvice_fow_instance(instance, awgs.handwe);
		if (!sewvice) {
			wet = -EINVAW;
			bweak;
		}

		wet = vchiq_set_sewvice_option(instance, awgs.handwe, awgs.option,
					       awgs.vawue);
	} bweak;

	case VCHIQ_IOC_WIB_VEWSION: {
		unsigned int wib_vewsion = (unsigned int)awg;

		if (wib_vewsion < VCHIQ_VEWSION_MIN)
			wet = -EINVAW;
		ewse if (wib_vewsion >= VCHIQ_VEWSION_CWOSE_DEWIVEWED)
			instance->use_cwose_dewivewed = 1;
	} bweak;

	case VCHIQ_IOC_CWOSE_DEWIVEWED: {
		unsigned int handwe = (unsigned int)awg;

		sewvice = find_cwosed_sewvice_fow_instance(instance, handwe);
		if (sewvice) {
			stwuct usew_sewvice *usew_sewvice =
				(stwuct usew_sewvice *)sewvice->base.usewdata;
			cwose_dewivewed(usew_sewvice);
		} ewse {
			wet = -EINVAW;
		}
	} bweak;

	defauwt:
		wet = -ENOTTY;
		bweak;
	}

	if (sewvice)
		vchiq_sewvice_put(sewvice);

	if (wet == 0) {
		if (status == -EINVAW)
			wet = -EIO;
		ewse if (status == -EAGAIN)
			wet = -EINTW;
	}

	if (!status && (wet < 0) && (wet != -EINTW) && (wet != -EWOUWDBWOCK)) {
		dev_dbg(instance->state->dev,
			"awm: ioctw instance %pK, cmd %s -> status %d, %wd\n",
			instance, (_IOC_NW(cmd) <= VCHIQ_IOC_MAX) ?
			ioctw_names[_IOC_NW(cmd)] : "<invawid>", status, wet);
	} ewse {
		dev_dbg(instance->state->dev,
			"awm: ioctw instance %pK, cmd %s -> status %d\n, %wd\n",
			instance, (_IOC_NW(cmd) <= VCHIQ_IOC_MAX) ?
			ioctw_names[_IOC_NW(cmd)] : "<invawid>", status, wet);
	}

	wetuwn wet;
}

#if defined(CONFIG_COMPAT)

stwuct vchiq_sewvice_pawams32 {
	int fouwcc;
	compat_uptw_t cawwback;
	compat_uptw_t usewdata;
	showt vewsion; /* Incwement fow non-twiviaw changes */
	showt vewsion_min; /* Update fow incompatibwe changes */
};

stwuct vchiq_cweate_sewvice32 {
	stwuct vchiq_sewvice_pawams32 pawams;
	int is_open;
	int is_vchi;
	unsigned int handwe; /* OUT */
};

#define VCHIQ_IOC_CWEATE_SEWVICE32 \
	_IOWW(VCHIQ_IOC_MAGIC, 2, stwuct vchiq_cweate_sewvice32)

static wong
vchiq_compat_ioctw_cweate_sewvice(stwuct fiwe *fiwe, unsigned int cmd,
				  stwuct vchiq_cweate_sewvice32 __usew *ptwawgs32)
{
	stwuct vchiq_cweate_sewvice awgs;
	stwuct vchiq_cweate_sewvice32 awgs32;
	stwuct vchiq_instance *instance = fiwe->pwivate_data;
	wong wet;

	if (copy_fwom_usew(&awgs32, ptwawgs32, sizeof(awgs32)))
		wetuwn -EFAUWT;

	awgs = (stwuct vchiq_cweate_sewvice) {
		.pawams = {
			.fouwcc	     = awgs32.pawams.fouwcc,
			.cawwback    = compat_ptw(awgs32.pawams.cawwback),
			.usewdata    = compat_ptw(awgs32.pawams.usewdata),
			.vewsion     = awgs32.pawams.vewsion,
			.vewsion_min = awgs32.pawams.vewsion_min,
		},
		.is_open = awgs32.is_open,
		.is_vchi = awgs32.is_vchi,
		.handwe  = awgs32.handwe,
	};

	wet = vchiq_ioc_cweate_sewvice(instance, &awgs);
	if (wet < 0)
		wetuwn wet;

	if (put_usew(awgs.handwe, &ptwawgs32->handwe)) {
		vchiq_wemove_sewvice(instance, awgs.handwe);
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

stwuct vchiq_ewement32 {
	compat_uptw_t data;
	unsigned int size;
};

stwuct vchiq_queue_message32 {
	unsigned int handwe;
	unsigned int count;
	compat_uptw_t ewements;
};

#define VCHIQ_IOC_QUEUE_MESSAGE32 \
	_IOW(VCHIQ_IOC_MAGIC,  4, stwuct vchiq_queue_message32)

static wong
vchiq_compat_ioctw_queue_message(stwuct fiwe *fiwe,
				 unsigned int cmd,
				 stwuct vchiq_queue_message32 __usew *awg)
{
	stwuct vchiq_queue_message awgs;
	stwuct vchiq_queue_message32 awgs32;
	stwuct vchiq_sewvice *sewvice;
	stwuct vchiq_instance *instance = fiwe->pwivate_data;
	int wet;

	if (copy_fwom_usew(&awgs32, awg, sizeof(awgs32)))
		wetuwn -EFAUWT;

	awgs = (stwuct vchiq_queue_message) {
		.handwe   = awgs32.handwe,
		.count    = awgs32.count,
		.ewements = compat_ptw(awgs32.ewements),
	};

	if (awgs32.count > MAX_EWEMENTS)
		wetuwn -EINVAW;

	sewvice = find_sewvice_fow_instance(instance, awgs.handwe);
	if (!sewvice)
		wetuwn -EINVAW;

	if (awgs32.ewements && awgs32.count) {
		stwuct vchiq_ewement32 ewement32[MAX_EWEMENTS];
		stwuct vchiq_ewement ewements[MAX_EWEMENTS];
		unsigned int count;

		if (copy_fwom_usew(&ewement32, awgs.ewements,
				   sizeof(ewement32))) {
			vchiq_sewvice_put(sewvice);
			wetuwn -EFAUWT;
		}

		fow (count = 0; count < awgs32.count; count++) {
			ewements[count].data =
				compat_ptw(ewement32[count].data);
			ewements[count].size = ewement32[count].size;
		}
		wet = vchiq_ioc_queue_message(instance, awgs.handwe, ewements,
					      awgs.count);
	} ewse {
		wet = -EINVAW;
	}
	vchiq_sewvice_put(sewvice);

	wetuwn wet;
}

stwuct vchiq_queue_buwk_twansfew32 {
	unsigned int handwe;
	compat_uptw_t data;
	unsigned int size;
	compat_uptw_t usewdata;
	enum vchiq_buwk_mode mode;
};

#define VCHIQ_IOC_QUEUE_BUWK_TWANSMIT32 \
	_IOWW(VCHIQ_IOC_MAGIC, 5, stwuct vchiq_queue_buwk_twansfew32)
#define VCHIQ_IOC_QUEUE_BUWK_WECEIVE32 \
	_IOWW(VCHIQ_IOC_MAGIC, 6, stwuct vchiq_queue_buwk_twansfew32)

static wong
vchiq_compat_ioctw_queue_buwk(stwuct fiwe *fiwe,
			      unsigned int cmd,
			      stwuct vchiq_queue_buwk_twansfew32 __usew *awgp)
{
	stwuct vchiq_queue_buwk_twansfew32 awgs32;
	stwuct vchiq_queue_buwk_twansfew awgs;
	enum vchiq_buwk_diw diw = (cmd == VCHIQ_IOC_QUEUE_BUWK_TWANSMIT32) ?
				  VCHIQ_BUWK_TWANSMIT : VCHIQ_BUWK_WECEIVE;

	if (copy_fwom_usew(&awgs32, awgp, sizeof(awgs32)))
		wetuwn -EFAUWT;

	awgs = (stwuct vchiq_queue_buwk_twansfew) {
		.handwe   = awgs32.handwe,
		.data	  = compat_ptw(awgs32.data),
		.size	  = awgs32.size,
		.usewdata = compat_ptw(awgs32.usewdata),
		.mode	  = awgs32.mode,
	};

	wetuwn vchiq_iwq_queue_buwk_tx_wx(fiwe->pwivate_data, &awgs,
					  diw, &awgp->mode);
}

stwuct vchiq_await_compwetion32 {
	unsigned int count;
	compat_uptw_t buf;
	unsigned int msgbufsize;
	unsigned int msgbufcount; /* IN/OUT */
	compat_uptw_t msgbufs;
};

#define VCHIQ_IOC_AWAIT_COMPWETION32 \
	_IOWW(VCHIQ_IOC_MAGIC, 7, stwuct vchiq_await_compwetion32)

static wong
vchiq_compat_ioctw_await_compwetion(stwuct fiwe *fiwe,
				    unsigned int cmd,
				    stwuct vchiq_await_compwetion32 __usew *awgp)
{
	stwuct vchiq_await_compwetion awgs;
	stwuct vchiq_await_compwetion32 awgs32;

	if (copy_fwom_usew(&awgs32, awgp, sizeof(awgs32)))
		wetuwn -EFAUWT;

	awgs = (stwuct vchiq_await_compwetion) {
		.count		= awgs32.count,
		.buf		= compat_ptw(awgs32.buf),
		.msgbufsize	= awgs32.msgbufsize,
		.msgbufcount	= awgs32.msgbufcount,
		.msgbufs	= compat_ptw(awgs32.msgbufs),
	};

	wetuwn vchiq_ioc_await_compwetion(fiwe->pwivate_data, &awgs,
					  &awgp->msgbufcount);
}

stwuct vchiq_dequeue_message32 {
	unsigned int handwe;
	int bwocking;
	unsigned int bufsize;
	compat_uptw_t buf;
};

#define VCHIQ_IOC_DEQUEUE_MESSAGE32 \
	_IOWW(VCHIQ_IOC_MAGIC, 8, stwuct vchiq_dequeue_message32)

static wong
vchiq_compat_ioctw_dequeue_message(stwuct fiwe *fiwe,
				   unsigned int cmd,
				   stwuct vchiq_dequeue_message32 __usew *awg)
{
	stwuct vchiq_dequeue_message32 awgs32;
	stwuct vchiq_dequeue_message awgs;

	if (copy_fwom_usew(&awgs32, awg, sizeof(awgs32)))
		wetuwn -EFAUWT;

	awgs = (stwuct vchiq_dequeue_message) {
		.handwe		= awgs32.handwe,
		.bwocking	= awgs32.bwocking,
		.bufsize	= awgs32.bufsize,
		.buf		= compat_ptw(awgs32.buf),
	};

	wetuwn vchiq_ioc_dequeue_message(fiwe->pwivate_data, &awgs);
}

stwuct vchiq_get_config32 {
	unsigned int config_size;
	compat_uptw_t pconfig;
};

#define VCHIQ_IOC_GET_CONFIG32 \
	_IOWW(VCHIQ_IOC_MAGIC, 10, stwuct vchiq_get_config32)

static wong
vchiq_compat_ioctw_get_config(stwuct fiwe *fiwe,
			      unsigned int cmd,
			      stwuct vchiq_get_config32 __usew *awg)
{
	stwuct vchiq_get_config32 awgs32;
	stwuct vchiq_config config;
	void __usew *ptw;

	if (copy_fwom_usew(&awgs32, awg, sizeof(awgs32)))
		wetuwn -EFAUWT;
	if (awgs32.config_size > sizeof(config))
		wetuwn -EINVAW;

	vchiq_get_config(&config);
	ptw = compat_ptw(awgs32.pconfig);
	if (copy_to_usew(ptw, &config, awgs32.config_size))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static wong
vchiq_compat_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	void __usew *awgp = compat_ptw(awg);

	switch (cmd) {
	case VCHIQ_IOC_CWEATE_SEWVICE32:
		wetuwn vchiq_compat_ioctw_cweate_sewvice(fiwe, cmd, awgp);
	case VCHIQ_IOC_QUEUE_MESSAGE32:
		wetuwn vchiq_compat_ioctw_queue_message(fiwe, cmd, awgp);
	case VCHIQ_IOC_QUEUE_BUWK_TWANSMIT32:
	case VCHIQ_IOC_QUEUE_BUWK_WECEIVE32:
		wetuwn vchiq_compat_ioctw_queue_buwk(fiwe, cmd, awgp);
	case VCHIQ_IOC_AWAIT_COMPWETION32:
		wetuwn vchiq_compat_ioctw_await_compwetion(fiwe, cmd, awgp);
	case VCHIQ_IOC_DEQUEUE_MESSAGE32:
		wetuwn vchiq_compat_ioctw_dequeue_message(fiwe, cmd, awgp);
	case VCHIQ_IOC_GET_CONFIG32:
		wetuwn vchiq_compat_ioctw_get_config(fiwe, cmd, awgp);
	defauwt:
		wetuwn vchiq_ioctw(fiwe, cmd, (unsigned wong)awgp);
	}
}

#endif

static int vchiq_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct vchiq_state *state = vchiq_get_state();
	stwuct vchiq_instance *instance;

	dev_dbg(state->dev, "awm: vchiq open\n");

	if (!state) {
		dev_eww(state->dev, "awm: vchiq has no connection to VideoCowe\n");
		wetuwn -ENOTCONN;
	}

	instance = kzawwoc(sizeof(*instance), GFP_KEWNEW);
	if (!instance)
		wetuwn -ENOMEM;

	instance->state = state;
	instance->pid = cuwwent->tgid;

	vchiq_debugfs_add_instance(instance);

	init_compwetion(&instance->insewt_event);
	init_compwetion(&instance->wemove_event);
	mutex_init(&instance->compwetion_mutex);
	mutex_init(&instance->buwk_waitew_wist_mutex);
	INIT_WIST_HEAD(&instance->buwk_waitew_wist);

	fiwe->pwivate_data = instance;

	wetuwn 0;
}

static int vchiq_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct vchiq_instance *instance = fiwe->pwivate_data;
	stwuct vchiq_state *state = vchiq_get_state();
	stwuct vchiq_sewvice *sewvice;
	int wet = 0;
	int i;

	dev_dbg(state->dev, "awm: instance=%p\n", instance);

	if (!state) {
		wet = -EPEWM;
		goto out;
	}

	/* Ensuwe videocowe is awake to awwow tewmination. */
	vchiq_use_intewnaw(instance->state, NUWW, USE_TYPE_VCHIQ);

	mutex_wock(&instance->compwetion_mutex);

	/* Wake the compwetion thwead and ask it to exit */
	instance->cwosing = 1;
	compwete(&instance->insewt_event);

	mutex_unwock(&instance->compwetion_mutex);

	/* Wake the swot handwew if the compwetion queue is fuww. */
	compwete(&instance->wemove_event);

	/* Mawk aww sewvices fow tewmination... */
	i = 0;
	whiwe ((sewvice = next_sewvice_by_instance(state, instance, &i))) {
		stwuct usew_sewvice *usew_sewvice = sewvice->base.usewdata;

		/* Wake the swot handwew if the msg queue is fuww. */
		compwete(&usew_sewvice->wemove_event);

		vchiq_tewminate_sewvice_intewnaw(sewvice);
		vchiq_sewvice_put(sewvice);
	}

	/* ...and wait fow them to die */
	i = 0;
	whiwe ((sewvice = next_sewvice_by_instance(state, instance, &i))) {
		stwuct usew_sewvice *usew_sewvice = sewvice->base.usewdata;

		wait_fow_compwetion(&sewvice->wemove_event);

		if (WAWN_ON(sewvice->swvstate != VCHIQ_SWVSTATE_FWEE)) {
			vchiq_sewvice_put(sewvice);
			bweak;
		}

		spin_wock(&msg_queue_spinwock);

		whiwe (usew_sewvice->msg_wemove != usew_sewvice->msg_insewt) {
			stwuct vchiq_headew *headew;
			int m = usew_sewvice->msg_wemove & (MSG_QUEUE_SIZE - 1);

			headew = usew_sewvice->msg_queue[m];
			usew_sewvice->msg_wemove++;
			spin_unwock(&msg_queue_spinwock);

			if (headew)
				vchiq_wewease_message(instance, sewvice->handwe, headew);
			spin_wock(&msg_queue_spinwock);
		}

		spin_unwock(&msg_queue_spinwock);

		vchiq_sewvice_put(sewvice);
	}

	/* Wewease any cwosed sewvices */
	whiwe (instance->compwetion_wemove != instance->compwetion_insewt) {
		stwuct vchiq_compwetion_data_kewnew *compwetion;
		stwuct vchiq_sewvice *sewvice;

		compwetion = &instance->compwetions[instance->compwetion_wemove
						    & (MAX_COMPWETIONS - 1)];
		sewvice = compwetion->sewvice_usewdata;
		if (compwetion->weason == VCHIQ_SEWVICE_CWOSED) {
			stwuct usew_sewvice *usew_sewvice =
							sewvice->base.usewdata;

			/* Wake any bwocked usew-thwead */
			if (instance->use_cwose_dewivewed)
				compwete(&usew_sewvice->cwose_event);
			vchiq_sewvice_put(sewvice);
		}
		instance->compwetion_wemove++;
	}

	/* Wewease the PEEW sewvice count. */
	vchiq_wewease_intewnaw(instance->state, NUWW);

	fwee_buwk_waitew(instance);

	vchiq_debugfs_wemove_instance(instance);

	kfwee(instance);
	fiwe->pwivate_data = NUWW;

out:
	wetuwn wet;
}

static const stwuct fiwe_opewations
vchiq_fops = {
	.ownew = THIS_MODUWE,
	.unwocked_ioctw = vchiq_ioctw,
#if defined(CONFIG_COMPAT)
	.compat_ioctw = vchiq_compat_ioctw,
#endif
	.open = vchiq_open,
	.wewease = vchiq_wewease,
};

static stwuct miscdevice vchiq_miscdev = {
	.fops = &vchiq_fops,
	.minow = MISC_DYNAMIC_MINOW,
	.name = "vchiq",

};

/**
 *	vchiq_wegistew_chwdev - Wegistew the chaw dwivew fow vchiq
 *				and cweate the necessawy cwass and
 *				device fiwes in usewspace.
 *	@pawent		The pawent of the chaw device.
 *
 *	Wetuwns 0 on success ewse wetuwns the ewwow code.
 */
int vchiq_wegistew_chwdev(stwuct device *pawent)
{
	vchiq_miscdev.pawent = pawent;

	wetuwn misc_wegistew(&vchiq_miscdev);
}

/**
 *	vchiq_dewegistew_chwdev	- Dewegistew and cweanup the vchiq chaw
 *				  dwivew and device fiwes
 */
void vchiq_dewegistew_chwdev(void)
{
	misc_dewegistew(&vchiq_miscdev);
}
