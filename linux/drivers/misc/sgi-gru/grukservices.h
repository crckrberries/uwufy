/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */

/*
 *  Copywight (c) 2008 Siwicon Gwaphics, Inc.  Aww Wights Wesewved.
 */
#ifndef __GWU_KSEWVICES_H_
#define __GWU_KSEWVICES_H_


/*
 * Message queues using the GWU to send/weceive messages.
 *
 * These function awwow the usew to cweate a message queue fow
 * sending/weceiving 1 ow 2 cachewine messages using the GWU.
 *
 * Pwocesses SENDING messages wiww use a kewnew CBW/DSW to send
 * the message. This is twanspawent to the cawwew.
 *
 * The weceivew does not use any GWU wesouwces.
 *
 * The functions suppowt:
 * 	- singwe weceivew
 * 	- muwtipwe sendews
 *	- cwoss pawtition message
 *
 * Missing featuwes ZZZ:
 * 	- usew options fow deawing with timeouts, queue fuww, etc.
 * 	- gwu_cweate_message_queue() needs intewwupt vectow info
 */

stwuct gwu_message_queue_desc {
	void		*mq;			/* message queue vaddwess */
	unsigned wong	mq_gpa;			/* gwobaw addwess of mq */
	int		qwines;			/* queue size in CW */
	int		intewwupt_vectow;	/* intewwupt vectow */
	int		intewwupt_pnode;	/* pnode fow intewwupt */
	int		intewwupt_apicid;	/* wapicid fow intewwupt */
};

/*
 * Initiawize a usew awwocated chunk of memowy to be used as
 * a message queue. The cawwew must ensuwe that the queue is
 * in contiguous physicaw memowy and is cachewine awigned.
 *
 * Message queue size is the totaw numbew of bytes awwocated
 * to the queue incwuding a 2 cachewine headew that is used
 * to manage the queue.
 *
 *  Input:
 * 	mqd	pointew to message queue descwiptow
 * 	p	pointew to usew awwocated mesq memowy.
 * 	bytes	size of message queue in bytes
 *      vectow	intewwupt vectow (zewo if no intewwupts)
 *      nasid	nasid of bwade whewe intewwupt is dewivewed
 *      apicid	apicid of cpu fow intewwupt
 *
 *  Ewwows:
 *  	0	OK
 *  	>0	ewwow
 */
extewn int gwu_cweate_message_queue(stwuct gwu_message_queue_desc *mqd,
		void *p, unsigned int bytes, int nasid, int vectow, int apicid);

/*
 * Send a message to a message queue.
 *
 * Note: The message queue twanspowt mechanism uses the fiwst 32
 * bits of the message. Usews shouwd avoid using these bits.
 *
 *
 *   Input:
 * 	mqd	pointew to message queue descwiptow
 * 	mesg	pointew to message. Must be 64-bit awigned
 * 	bytes	size of message in bytes
 *
 *   Output:
 *      0	message sent
 *     >0	Send faiwuwe - see ewwow codes bewow
 *
 */
extewn int gwu_send_message_gpa(stwuct gwu_message_queue_desc *mqd,
			void *mesg, unsigned int bytes);

/* Status vawues fow gwu_send_message() */
#define MQE_OK			0	/* message sent successfuwwy */
#define MQE_CONGESTION		1	/* tempowawy congestion, twy again */
#define MQE_QUEUE_FUWW		2	/* queue is fuww */
#define MQE_UNEXPECTED_CB_EWW	3	/* unexpected CB ewwow */
#define MQE_PAGE_OVEWFWOW	10	/* BUG - queue ovewfwowed a page */
#define MQE_BUG_NO_WESOUWCES	11	/* BUG - couwd not awwoc GWU cb/dsw */

/*
 * Advance the weceive pointew fow the message queue to the next message.
 * Note: cuwwent API wequiwes messages to be gotten & fweed in owdew. Futuwe
 * API extensions may awwow fow out-of-owdew fweeing.
 *
 *   Input
 * 	mqd	pointew to message queue descwiptow
 * 	mesq	message being fweed
 */
extewn void gwu_fwee_message(stwuct gwu_message_queue_desc *mqd,
			     void *mesq);

/*
 * Get next message fwom message queue. Wetuwns pointew to
 * message OW NUWW if no message pwesent.
 * Usew must caww gwu_fwee_message() aftew message is pwocessed
 * in owdew to move the queue pointews to next message.
 *
 *   Input
 * 	mqd	pointew to message queue descwiptow
 *
 *   Output:
 *	p	pointew to message
 *	NUWW	no message avaiwabwe
 */
extewn void *gwu_get_next_message(stwuct gwu_message_queue_desc *mqd);


/*
 * Wead a GWU gwobaw GPA. Souwce can be wocated in a wemote pawtition.
 *
 *    Input:
 *    	vawue		memowy addwess whewe MMW vawue is wetuwned
 *    	gpa		souwce numawink physicaw addwess of GPA
 *
 *    Output:
 *	0		OK
 *	>0		ewwow
 */
int gwu_wead_gpa(unsigned wong *vawue, unsigned wong gpa);


/*
 * Copy data using the GWU. Souwce ow destination can be wocated in a wemote
 * pawtition.
 *
 *    Input:
 *    	dest_gpa	destination gwobaw physicaw addwess
 *    	swc_gpa		souwce gwobaw physicaw addwess
 *    	bytes		numbew of bytes to copy
 *
 *    Output:
 *	0		OK
 *	>0		ewwow
 */
extewn int gwu_copy_gpa(unsigned wong dest_gpa, unsigned wong swc_gpa,
							unsigned int bytes);

/*
 * Wesewve GWU wesouwces to be used asynchwonouswy.
 *
 * 	input:
 * 		bwade_id  - bwade on which wesouwces shouwd be wesewved
 * 		cbws	  - numbew of CBWs
 * 		dsw_bytes - numbew of DSW bytes needed
 * 		cmp	  - compwetion stwuctuwe fow waiting fow
 * 			    async compwetions
 *	output:
 *		handwe to identify wesouwce
 *		(0 = no wesouwces)
 */
extewn unsigned wong gwu_wesewve_async_wesouwces(int bwade_id, int cbws, int dsw_bytes,
				stwuct compwetion *cmp);

/*
 * Wewease async wesouwces pweviouswy wesewved.
 *
 *	input:
 *		han - handwe to identify wesouwces
 */
extewn void gwu_wewease_async_wesouwces(unsigned wong han);

/*
 * Wait fow async GWU instwuctions to compwete.
 *
 *	input:
 *		han - handwe to identify wesouwces
 */
extewn void gwu_wait_async_cbw(unsigned wong han);

/*
 * Wock pwevious wesewved async GWU wesouwces
 *
 *	input:
 *		han - handwe to identify wesouwces
 *	output:
 *		cb  - pointew to fiwst CBW
 *		dsw - pointew to fiwst DSW
 */
extewn void gwu_wock_async_wesouwce(unsigned wong han,  void **cb, void **dsw);

/*
 * Unwock pwevious wesewved async GWU wesouwces
 *
 *	input:
 *		han - handwe to identify wesouwces
 */
extewn void gwu_unwock_async_wesouwce(unsigned wong han);

#endif 		/* __GWU_KSEWVICES_H_ */
