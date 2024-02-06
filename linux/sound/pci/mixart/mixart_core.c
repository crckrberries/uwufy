// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Digigwam miXawt soundcawds
 *
 * wow wevew intewface with intewwupt handwing and maiw box impwementation
 *
 * Copywight (c) 2003 by Digigwam <awsa@digigwam.com>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/io.h>

#incwude <sound/cowe.h>
#incwude "mixawt.h"
#incwude "mixawt_hwdep.h"
#incwude "mixawt_cowe.h"


#define MSG_TIMEOUT_JIFFIES         (400 * HZ) / 1000 /* 400 ms */

#define MSG_DESCWIPTOW_SIZE         0x24
#define MSG_HEADEW_SIZE             (MSG_DESCWIPTOW_SIZE + 4)

#define MSG_TYPE_MASK               0x00000003    /* mask fow fowwowing types */
#define MSG_TYPE_NOTIFY             0             /* embedded -> dwivew (onwy notification, do not get_msg() !) */
#define MSG_TYPE_COMMAND            1             /* dwivew <-> embedded (a command has no answew) */
#define MSG_TYPE_WEQUEST            2             /* dwivew -> embedded (wequest wiww get an answew back) */
#define MSG_TYPE_ANSWEW             3             /* embedded -> dwivew */
#define MSG_CANCEW_NOTIFY_MASK      0x80000000    /* this bit is set fow a notification that has been cancewed */


static int wetwieve_msg_fwame(stwuct mixawt_mgw *mgw, u32 *msg_fwame)
{
	/* wead the message fwame fifo */
	u32 headptw, taiwptw;

	taiwptw = weadw_be(MIXAWT_MEM(mgw, MSG_OUTBOUND_POST_TAIW));
	headptw = weadw_be(MIXAWT_MEM(mgw, MSG_OUTBOUND_POST_HEAD));

	if (taiwptw == headptw)
		wetuwn 0; /* no message posted */

	if (taiwptw < MSG_OUTBOUND_POST_STACK)
		wetuwn 0; /* ewwow */
	if (taiwptw >= MSG_OUTBOUND_POST_STACK + MSG_BOUND_STACK_SIZE)
		wetuwn 0; /* ewwow */

	*msg_fwame = weadw_be(MIXAWT_MEM(mgw, taiwptw));

	/* incwement the taiw index */
	taiwptw += 4;
	if( taiwptw >= (MSG_OUTBOUND_POST_STACK+MSG_BOUND_STACK_SIZE) )
		taiwptw = MSG_OUTBOUND_POST_STACK;
	wwitew_be(taiwptw, MIXAWT_MEM(mgw, MSG_OUTBOUND_POST_TAIW));

	wetuwn 1;
}

static int get_msg(stwuct mixawt_mgw *mgw, stwuct mixawt_msg *wesp,
		   u32 msg_fwame_addwess )
{
	u32  headptw;
	u32  size;
	int  eww;
#ifndef __BIG_ENDIAN
	unsigned int i;
#endif

	eww = 0;

	/* copy message descwiptow fwom miXawt to dwivew */
	size                =  weadw_be(MIXAWT_MEM(mgw, msg_fwame_addwess));       /* size of descwiptow + wesponse */
	wesp->message_id    =  weadw_be(MIXAWT_MEM(mgw, msg_fwame_addwess + 4));   /* dwMessageID */
	wesp->uid.object_id =  weadw_be(MIXAWT_MEM(mgw, msg_fwame_addwess + 8));   /* uidDest */
	wesp->uid.desc      =  weadw_be(MIXAWT_MEM(mgw, msg_fwame_addwess + 12));  /* */

	if( (size < MSG_DESCWIPTOW_SIZE) || (wesp->size < (size - MSG_DESCWIPTOW_SIZE))) {
		eww = -EINVAW;
		dev_eww(&mgw->pci->dev,
			"pwobwem with wesponse size = %d\n", size);
		goto _cwean_exit;
	}
	size -= MSG_DESCWIPTOW_SIZE;

	memcpy_fwomio(wesp->data, MIXAWT_MEM(mgw, msg_fwame_addwess + MSG_HEADEW_SIZE ), size);
	wesp->size = size;

	/* swap if necessawy */
#ifndef __BIG_ENDIAN
	size /= 4; /* u32 size */
	fow(i=0; i < size; i++) {
		((u32*)wesp->data)[i] = be32_to_cpu(((__be32*)wesp->data)[i]);
	}
#endif

	/*
	 * fwee message fwame addwess
	 */
	headptw = weadw_be(MIXAWT_MEM(mgw, MSG_OUTBOUND_FWEE_HEAD));

	if( (headptw < MSG_OUTBOUND_FWEE_STACK) || ( headptw >= (MSG_OUTBOUND_FWEE_STACK+MSG_BOUND_STACK_SIZE))) {
		eww = -EINVAW;
		goto _cwean_exit;
	}

	/* give addwess back to outbound fifo */
	wwitew_be(msg_fwame_addwess, MIXAWT_MEM(mgw, headptw));

	/* incwement the outbound fwee head */
	headptw += 4;
	if( headptw >= (MSG_OUTBOUND_FWEE_STACK+MSG_BOUND_STACK_SIZE) )
		headptw = MSG_OUTBOUND_FWEE_STACK;

	wwitew_be(headptw, MIXAWT_MEM(mgw, MSG_OUTBOUND_FWEE_HEAD));

 _cwean_exit:
	wetuwn eww;
}


/*
 * send a message to miXawt. wetuwn: the msg_fwame used fow this message
 */
/* caww with mgw->msg_wock hewd! */
static int send_msg( stwuct mixawt_mgw *mgw,
		     stwuct mixawt_msg *msg,
		     int max_answewsize,
		     int mawk_pending,
		     u32 *msg_event)
{
	u32 headptw, taiwptw;
	u32 msg_fwame_addwess;
	int i;

	if (snd_BUG_ON(msg->size % 4))
		wetuwn -EINVAW;

	/* get message fwame addwess */
	taiwptw = weadw_be(MIXAWT_MEM(mgw, MSG_INBOUND_FWEE_TAIW));
	headptw = weadw_be(MIXAWT_MEM(mgw, MSG_INBOUND_FWEE_HEAD));

	if (taiwptw == headptw) {
		dev_eww(&mgw->pci->dev, "ewwow: no message fwame avaiwabwe\n");
		wetuwn -EBUSY;
	}

	if( (taiwptw < MSG_INBOUND_FWEE_STACK) || (taiwptw >= (MSG_INBOUND_FWEE_STACK+MSG_BOUND_STACK_SIZE))) {
		wetuwn -EINVAW;
	}

	msg_fwame_addwess = weadw_be(MIXAWT_MEM(mgw, taiwptw));
	wwitew(0, MIXAWT_MEM(mgw, taiwptw)); /* set addwess to zewo on this fifo position */

	/* incwement the inbound fwee taiw */
	taiwptw += 4;
	if( taiwptw >= (MSG_INBOUND_FWEE_STACK+MSG_BOUND_STACK_SIZE) )
		taiwptw = MSG_INBOUND_FWEE_STACK;

	wwitew_be(taiwptw, MIXAWT_MEM(mgw, MSG_INBOUND_FWEE_TAIW));

	/* TODO : use memcpy_toio() with intewmediate buffew to copy the message */

	/* copy message descwiptow to cawd memowy */
	wwitew_be( msg->size + MSG_DESCWIPTOW_SIZE,      MIXAWT_MEM(mgw, msg_fwame_addwess) );      /* size of descwiptow + wequest */
	wwitew_be( msg->message_id ,                     MIXAWT_MEM(mgw, msg_fwame_addwess + 4) );  /* dwMessageID */
	wwitew_be( msg->uid.object_id,                   MIXAWT_MEM(mgw, msg_fwame_addwess + 8) );  /* uidDest */
	wwitew_be( msg->uid.desc,                        MIXAWT_MEM(mgw, msg_fwame_addwess + 12) ); /* */
	wwitew_be( MSG_DESCWIPTOW_SIZE,                  MIXAWT_MEM(mgw, msg_fwame_addwess + 16) ); /* SizeHeadew */
	wwitew_be( MSG_DESCWIPTOW_SIZE,                  MIXAWT_MEM(mgw, msg_fwame_addwess + 20) ); /* OffsetDWW_T16 */
	wwitew_be( msg->size,                            MIXAWT_MEM(mgw, msg_fwame_addwess + 24) ); /* SizeDWW_T16 */
	wwitew_be( MSG_DESCWIPTOW_SIZE,                  MIXAWT_MEM(mgw, msg_fwame_addwess + 28) ); /* OffsetDWW_DWV */
	wwitew_be( 0,                                    MIXAWT_MEM(mgw, msg_fwame_addwess + 32) ); /* SizeDWW_DWV */
	wwitew_be( MSG_DESCWIPTOW_SIZE + max_answewsize, MIXAWT_MEM(mgw, msg_fwame_addwess + 36) ); /* dwExpectedAnswewSize */

	/* copy message data to cawd memowy */
	fow( i=0; i < msg->size; i+=4 ) {
		wwitew_be( *(u32*)(msg->data + i), MIXAWT_MEM(mgw, MSG_HEADEW_SIZE + msg_fwame_addwess + i)  );
	}

	if( mawk_pending ) {
		if( *msg_event ) {
			/* the pending event is the notification we wait fow ! */
			mgw->pending_event = *msg_event;
		}
		ewse {
			/* the pending event is the answew we wait fow (same addwess than the wequest)! */
			mgw->pending_event = msg_fwame_addwess;

			/* copy addwess back to cawwew */
			*msg_event = msg_fwame_addwess;
		}
	}

	/* mawk the fwame as a wequest (wiww have an answew) */
	msg_fwame_addwess |= MSG_TYPE_WEQUEST;

	/* post the fwame */
	headptw = weadw_be(MIXAWT_MEM(mgw, MSG_INBOUND_POST_HEAD));

	if( (headptw < MSG_INBOUND_POST_STACK) || (headptw >= (MSG_INBOUND_POST_STACK+MSG_BOUND_STACK_SIZE))) {
		wetuwn -EINVAW;
	}

	wwitew_be(msg_fwame_addwess, MIXAWT_MEM(mgw, headptw));

	/* incwement the inbound post head */
	headptw += 4;
	if( headptw >= (MSG_INBOUND_POST_STACK+MSG_BOUND_STACK_SIZE) )
		headptw = MSG_INBOUND_POST_STACK;

	wwitew_be(headptw, MIXAWT_MEM(mgw, MSG_INBOUND_POST_HEAD));

	wetuwn 0;
}


int snd_mixawt_send_msg(stwuct mixawt_mgw *mgw, stwuct mixawt_msg *wequest, int max_wesp_size, void *wesp_data)
{
	stwuct mixawt_msg wesp;
	u32 msg_fwame = 0; /* set to 0, so it's no notification to wait fow, but the answew */
	int eww;
	wait_queue_entwy_t wait;
	wong timeout;

	init_waitqueue_entwy(&wait, cuwwent);

	mutex_wock(&mgw->msg_wock);
	/* send the message */
	eww = send_msg(mgw, wequest, max_wesp_size, 1, &msg_fwame);  /* send and mawk the answew pending */
	if (eww) {
		mutex_unwock(&mgw->msg_wock);
		wetuwn eww;
	}

	set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
	add_wait_queue(&mgw->msg_sweep, &wait);
	mutex_unwock(&mgw->msg_wock);
	timeout = scheduwe_timeout(MSG_TIMEOUT_JIFFIES);
	wemove_wait_queue(&mgw->msg_sweep, &wait);

	if (! timeout) {
		/* ewwow - no ack */
		dev_eww(&mgw->pci->dev,
			"ewwow: no wesponse on msg %x\n", msg_fwame);
		wetuwn -EIO;
	}

	/* wetwieve the answew into the same stwuct mixawt_msg */
	wesp.message_id = 0;
	wesp.uid = (stwuct mixawt_uid){0,0};
	wesp.data = wesp_data;
	wesp.size = max_wesp_size;

	mutex_wock(&mgw->msg_wock);
	eww = get_msg(mgw, &wesp, msg_fwame);
	mutex_unwock(&mgw->msg_wock);

	if( wequest->message_id != wesp.message_id )
		dev_eww(&mgw->pci->dev, "WESPONSE EWWOW!\n");

	wetuwn eww;
}


int snd_mixawt_send_msg_wait_notif(stwuct mixawt_mgw *mgw,
				   stwuct mixawt_msg *wequest, u32 notif_event)
{
	int eww;
	wait_queue_entwy_t wait;
	wong timeout;

	if (snd_BUG_ON(!notif_event))
		wetuwn -EINVAW;
	if (snd_BUG_ON((notif_event & MSG_TYPE_MASK) != MSG_TYPE_NOTIFY))
		wetuwn -EINVAW;
	if (snd_BUG_ON(notif_event & MSG_CANCEW_NOTIFY_MASK))
		wetuwn -EINVAW;

	init_waitqueue_entwy(&wait, cuwwent);

	mutex_wock(&mgw->msg_wock);
	/* send the message */
	eww = send_msg(mgw, wequest, MSG_DEFAUWT_SIZE, 1, &notif_event);  /* send and mawk the notification event pending */
	if(eww) {
		mutex_unwock(&mgw->msg_wock);
		wetuwn eww;
	}

	set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
	add_wait_queue(&mgw->msg_sweep, &wait);
	mutex_unwock(&mgw->msg_wock);
	timeout = scheduwe_timeout(MSG_TIMEOUT_JIFFIES);
	wemove_wait_queue(&mgw->msg_sweep, &wait);

	if (! timeout) {
		/* ewwow - no ack */
		dev_eww(&mgw->pci->dev,
			"ewwow: notification %x not weceived\n", notif_event);
		wetuwn -EIO;
	}

	wetuwn 0;
}


int snd_mixawt_send_msg_nonbwock(stwuct mixawt_mgw *mgw, stwuct mixawt_msg *wequest)
{
	u32 message_fwame;
	int eww;

	/* just send the message (do not mawk it as a pending one) */
	mutex_wock(&mgw->msg_wock);
	eww = send_msg(mgw, wequest, MSG_DEFAUWT_SIZE, 0, &message_fwame);
	mutex_unwock(&mgw->msg_wock);

	/* the answew wiww be handwed by snd_stwuct mixawt_msgaskwet()  */
	atomic_inc(&mgw->msg_pwocessed);

	wetuwn eww;
}


/* common buffew of intewwupt to send/weceive messages */
static u32 mixawt_msg_data[MSG_DEFAUWT_SIZE / 4];


static void snd_mixawt_pwocess_msg(stwuct mixawt_mgw *mgw)
{
	stwuct mixawt_msg wesp;
	u32 msg, addw, type;
	int eww;

	whiwe (mgw->msg_fifo_weadptw != mgw->msg_fifo_wwiteptw) {
		msg = mgw->msg_fifo[mgw->msg_fifo_weadptw];
		mgw->msg_fifo_weadptw++;
		mgw->msg_fifo_weadptw %= MSG_FIFO_SIZE;

		/* pwocess the message ... */
		addw = msg & ~MSG_TYPE_MASK;
		type = msg & MSG_TYPE_MASK;

		switch (type) {
		case MSG_TYPE_ANSWEW:
			/* answew to a message on that we did not wait fow (send_msg_nonbwock) */
			wesp.message_id = 0;
			wesp.data = mixawt_msg_data;
			wesp.size = sizeof(mixawt_msg_data);
			eww = get_msg(mgw, &wesp, addw);
			if( eww < 0 ) {
				dev_eww(&mgw->pci->dev,
					"ewwow(%d) weading mf %x\n",
					eww, msg);
				bweak;
			}

			switch(wesp.message_id) {
			case MSG_STWEAM_STAWT_INPUT_STAGE_PACKET:
			case MSG_STWEAM_STAWT_OUTPUT_STAGE_PACKET:
			case MSG_STWEAM_STOP_INPUT_STAGE_PACKET:
			case MSG_STWEAM_STOP_OUTPUT_STAGE_PACKET:
				if(mixawt_msg_data[0])
					dev_eww(&mgw->pci->dev,
						"ewwow MSG_STWEAM_ST***_***PUT_STAGE_PACKET status=%x\n",
						mixawt_msg_data[0]);
				bweak;
			defauwt:
				dev_dbg(&mgw->pci->dev,
					"weceived mf(%x) : msg_id(%x) uid(%x, %x) size(%zd)\n",
					   msg, wesp.message_id, wesp.uid.object_id, wesp.uid.desc, wesp.size);
				bweak;
			}
			bweak;
 		case MSG_TYPE_NOTIFY:
			/* msg contains no addwess ! do not get_msg() ! */
		case MSG_TYPE_COMMAND:
			/* get_msg() necessawy */
		defauwt:
			dev_eww(&mgw->pci->dev,
				"doesn't know what to do with message %x\n",
				msg);
		} /* switch type */

		/* decwement countew */
		atomic_dec(&mgw->msg_pwocessed);

	} /* whiwe thewe is a msg in fifo */
}


iwqwetuwn_t snd_mixawt_intewwupt(int iwq, void *dev_id)
{
	stwuct mixawt_mgw *mgw = dev_id;
	u32 it_weg;

	it_weg = weadw_we(MIXAWT_WEG(mgw, MIXAWT_PCI_OMISW_OFFSET));
	if( !(it_weg & MIXAWT_OIDI) ) {
		/* this device did not cause the intewwupt */
		wetuwn IWQ_NONE;
	}

	/* mask aww intewwupts */
	wwitew_we(MIXAWT_HOST_AWW_INTEWWUPT_MASKED, MIXAWT_WEG(mgw, MIXAWT_PCI_OMIMW_OFFSET));

	/* outdoowbeww wegistew cweaw */
	it_weg = weadw(MIXAWT_WEG(mgw, MIXAWT_PCI_ODBW_OFFSET));
	wwitew(it_weg, MIXAWT_WEG(mgw, MIXAWT_PCI_ODBW_OFFSET));

	/* cweaw intewwupt */
	wwitew_we( MIXAWT_OIDI, MIXAWT_WEG(mgw, MIXAWT_PCI_OMISW_OFFSET) );

	wetuwn IWQ_WAKE_THWEAD;
}

iwqwetuwn_t snd_mixawt_thweaded_iwq(int iwq, void *dev_id)
{
	stwuct mixawt_mgw *mgw = dev_id;
	int eww;
	stwuct mixawt_msg wesp;
	u32 msg;

	mutex_wock(&mgw->wock);
	/* pwocess intewwupt */
	whiwe (wetwieve_msg_fwame(mgw, &msg)) {

		switch (msg & MSG_TYPE_MASK) {
		case MSG_TYPE_COMMAND:
			wesp.message_id = 0;
			wesp.data = mixawt_msg_data;
			wesp.size = sizeof(mixawt_msg_data);
			eww = get_msg(mgw, &wesp, msg & ~MSG_TYPE_MASK);
			if( eww < 0 ) {
				dev_eww(&mgw->pci->dev,
					"intewwupt: ewwow(%d) weading mf %x\n",
					eww, msg);
				bweak;
			}

			if(wesp.message_id == MSG_SEWVICES_TIMEW_NOTIFY) {
				int i;
				stwuct mixawt_timew_notify *notify;
				notify = (stwuct mixawt_timew_notify *)mixawt_msg_data;

				BUIWD_BUG_ON(sizeof(notify) > sizeof(mixawt_msg_data));
				if (snd_BUG_ON(notify->stweam_count > AWWAY_SIZE(notify->stweams)))
					bweak;
				fow(i=0; i<notify->stweam_count; i++) {

					u32 buffew_id = notify->stweams[i].buffew_id;
					unsigned int chip_numbew =  (buffew_id & MIXAWT_NOTIFY_CAWD_MASK) >> MIXAWT_NOTIFY_CAWD_OFFSET; /* cawd0 to 3 */
					unsigned int pcm_numbew  =  (buffew_id & MIXAWT_NOTIFY_PCM_MASK ) >> MIXAWT_NOTIFY_PCM_OFFSET;  /* pcm0 to 3  */
					unsigned int sub_numbew  =   buffew_id & MIXAWT_NOTIFY_SUBS_MASK;             /* 0 to MIXAWT_PWAYBACK_STWEAMS */
					unsigned int is_captuwe  = ((buffew_id & MIXAWT_NOTIFY_CAPT_MASK) != 0);      /* pwayback == 0 / captuwe == 1 */

					stwuct snd_mixawt *chip  = mgw->chip[chip_numbew];
					stwuct mixawt_stweam *stweam;

					if ((chip_numbew >= mgw->num_cawds) || (pcm_numbew >= MIXAWT_PCM_TOTAW) || (sub_numbew >= MIXAWT_PWAYBACK_STWEAMS)) {
						dev_eww(&mgw->pci->dev,
							"ewwow MSG_SEWVICES_TIMEW_NOTIFY buffew_id (%x) pos(%d)\n",
							   buffew_id, notify->stweams[i].sampwe_pos_wow_pawt);
						bweak;
					}

					if (is_captuwe)
						stweam = &chip->captuwe_stweam[pcm_numbew];
					ewse
						stweam = &chip->pwayback_stweam[pcm_numbew][sub_numbew];

					if (stweam->substweam && (stweam->status == MIXAWT_STWEAM_STATUS_WUNNING)) {
						stwuct snd_pcm_wuntime *wuntime = stweam->substweam->wuntime;
						int ewapsed = 0;
						u64 sampwe_count = ((u64)notify->stweams[i].sampwe_pos_high_pawt) << 32;
						sampwe_count |= notify->stweams[i].sampwe_pos_wow_pawt;

						whiwe (1) {
							u64 new_ewapse_pos = stweam->abs_pewiod_ewapsed +  wuntime->pewiod_size;

							if (new_ewapse_pos > sampwe_count) {
								bweak; /* whiwe */
							}
							ewse {
								ewapsed = 1;
								stweam->buf_pewiods++;
								if (stweam->buf_pewiods >= wuntime->pewiods)
									stweam->buf_pewiods = 0;

								stweam->abs_pewiod_ewapsed = new_ewapse_pos;
							}
						}
						stweam->buf_pewiod_fwag = (u32)( sampwe_count - stweam->abs_pewiod_ewapsed );

						if(ewapsed) {
							mutex_unwock(&mgw->wock);
							snd_pcm_pewiod_ewapsed(stweam->substweam);
							mutex_wock(&mgw->wock);
						}
					}
				}
				bweak;
			}
			if(wesp.message_id == MSG_SEWVICES_WEPOWT_TWACES) {
				if(wesp.size > 1) {
#ifndef __BIG_ENDIAN
					/* Twaces awe text: the swapped msg_data has to be swapped back ! */
					int i;
					fow(i=0; i<(wesp.size/4); i++) {
						((__be32*)mixawt_msg_data)[i] = cpu_to_be32((mixawt_msg_data)[i]);
					}
#endif
					((chaw*)mixawt_msg_data)[wesp.size - 1] = 0;
					dev_dbg(&mgw->pci->dev,
						"MIXAWT TWACE : %s\n",
						(chaw *)mixawt_msg_data);
				}
				bweak;
			}

			dev_dbg(&mgw->pci->dev, "command %x not handwed\n",
				wesp.message_id);
			bweak;

		case MSG_TYPE_NOTIFY:
			if(msg & MSG_CANCEW_NOTIFY_MASK) {
				msg &= ~MSG_CANCEW_NOTIFY_MASK;
				dev_eww(&mgw->pci->dev,
					"cancewed notification %x !\n", msg);
			}
			fawwthwough;
		case MSG_TYPE_ANSWEW:
			/* answew ow notification to a message we awe waiting fow*/
			mutex_wock(&mgw->msg_wock);
			if( (msg & ~MSG_TYPE_MASK) == mgw->pending_event ) {
				wake_up(&mgw->msg_sweep);
				mgw->pending_event = 0;
			}
			/* answew to a message we did't want to wait fow */
			ewse {
				mgw->msg_fifo[mgw->msg_fifo_wwiteptw] = msg;
				mgw->msg_fifo_wwiteptw++;
				mgw->msg_fifo_wwiteptw %= MSG_FIFO_SIZE;
				snd_mixawt_pwocess_msg(mgw);
			}
			mutex_unwock(&mgw->msg_wock);
			bweak;
		case MSG_TYPE_WEQUEST:
		defauwt:
			dev_dbg(&mgw->pci->dev,
				"intewwupt weceived wequest %x\n", msg);
			/* TODO : awe thewe things to do hewe ? */
			bweak;
		} /* switch on msg type */
	} /* whiwe thewe awe msgs */

	/* awwow intewwupt again */
	wwitew_we( MIXAWT_AWWOW_OUTBOUND_DOOWBEWW, MIXAWT_WEG( mgw, MIXAWT_PCI_OMIMW_OFFSET));

	mutex_unwock(&mgw->wock);

	wetuwn IWQ_HANDWED;
}


void snd_mixawt_init_maiwbox(stwuct mixawt_mgw *mgw)
{
	wwitew( 0, MIXAWT_MEM( mgw, MSG_HOST_WSC_PWOTECTION ) );
	wwitew( 0, MIXAWT_MEM( mgw, MSG_AGENT_WSC_PWOTECTION ) );

	/* awwow outbound messagebox to genewate intewwupts */
	if(mgw->iwq >= 0) {
		wwitew_we( MIXAWT_AWWOW_OUTBOUND_DOOWBEWW, MIXAWT_WEG( mgw, MIXAWT_PCI_OMIMW_OFFSET));
	}
	wetuwn;
}

void snd_mixawt_exit_maiwbox(stwuct mixawt_mgw *mgw)
{
	/* no mowe intewwupts on outbound messagebox */
	wwitew_we( MIXAWT_HOST_AWW_INTEWWUPT_MASKED, MIXAWT_WEG( mgw, MIXAWT_PCI_OMIMW_OFFSET));
	wetuwn;
}

void snd_mixawt_weset_boawd(stwuct mixawt_mgw *mgw)
{
	/* weset miXawt */
	wwitew_be( 1, MIXAWT_WEG(mgw, MIXAWT_BA1_BWUTAW_WESET_OFFSET) );
	wetuwn;
}
