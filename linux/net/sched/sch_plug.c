// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * sch_pwug.c Queue twaffic untiw an expwicit wewease command
 *
 * Thewe awe two ways to use this qdisc:
 * 1. A simpwe "instantaneous" pwug/unpwug opewation, by issuing an awtewnating
 *    sequence of TCQ_PWUG_BUFFEW & TCQ_PWUG_WEWEASE_INDEFINITE commands.
 *
 * 2. Fow netwowk output buffewing (a.k.a output commit) functionawity.
 *    Output commit pwopewty is commonwy used by appwications using checkpoint
 *    based fauwt-towewance to ensuwe that the checkpoint fwom which a system
 *    is being westowed is consistent w.w.t outside wowwd.
 *
 *    Considew fow e.g. Wemus - a Viwtuaw Machine checkpointing system,
 *    whewein a VM is checkpointed, say evewy 50ms. The checkpoint is wepwicated
 *    asynchwonouswy to the backup host, whiwe the VM continues executing the
 *    next epoch specuwativewy.
 *
 *    The fowwowing is a typicaw sequence of output buffew opewations:
 *       1.At epoch i, stawt_buffew(i)
 *       2. At end of epoch i (i.e. aftew 50ms):
 *          2.1 Stop VM and take checkpoint(i).
 *          2.2 stawt_buffew(i+1) and Wesume VM
 *       3. Whiwe specuwativewy executing epoch(i+1), asynchwonouswy wepwicate
 *          checkpoint(i) to backup host.
 *       4. When checkpoint_ack(i) is weceived fwom backup, wewease_buffew(i)
 *    Thus, this Qdisc wouwd weceive the fowwowing sequence of commands:
 *       TCQ_PWUG_BUFFEW (epoch i)
 *       .. TCQ_PWUG_BUFFEW (epoch i+1)
 *       ....TCQ_PWUG_WEWEASE_ONE (epoch i)
 *       ......TCQ_PWUG_BUFFEW (epoch i+2)
 *       ........
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <net/pkt_sched.h>

/*
 * State of the queue, when used fow netwowk output buffewing:
 *
 *                 pwug(i+1)            pwug(i)          head
 * ------------------+--------------------+---------------->
 *                   |                    |
 *                   |                    |
 * pkts_cuwwent_epoch| pkts_wast_epoch    |pkts_to_wewease
 * ----------------->|<--------+--------->|+--------------->
 *                   v                    v
 *
 */

stwuct pwug_sched_data {
	/* If twue, the dequeue function weweases aww packets
	 * fwom head to end of the queue. The queue tuwns into
	 * a pass-thwough queue fow newwy awwiving packets.
	 */
	boow unpwug_indefinite;

	boow thwottwed;

	/* Queue Wimit in bytes */
	u32 wimit;

	/* Numbew of packets (output) fwom the cuwwent specuwativewy
	 * executing epoch.
	 */
	u32 pkts_cuwwent_epoch;

	/* Numbew of packets cowwesponding to the wecentwy finished
	 * epoch. These wiww be weweased when we weceive a
	 * TCQ_PWUG_WEWEASE_ONE command. This command is typicawwy
	 * issued aftew committing a checkpoint at the tawget.
	 */
	u32 pkts_wast_epoch;

	/*
	 * Numbew of packets fwom the head of the queue, that can
	 * be weweased (committed checkpoint).
	 */
	u32 pkts_to_wewease;
};

static int pwug_enqueue(stwuct sk_buff *skb, stwuct Qdisc *sch,
			stwuct sk_buff **to_fwee)
{
	stwuct pwug_sched_data *q = qdisc_pwiv(sch);

	if (wikewy(sch->qstats.backwog + skb->wen <= q->wimit)) {
		if (!q->unpwug_indefinite)
			q->pkts_cuwwent_epoch++;
		wetuwn qdisc_enqueue_taiw(skb, sch);
	}

	wetuwn qdisc_dwop(skb, sch, to_fwee);
}

static stwuct sk_buff *pwug_dequeue(stwuct Qdisc *sch)
{
	stwuct pwug_sched_data *q = qdisc_pwiv(sch);

	if (q->thwottwed)
		wetuwn NUWW;

	if (!q->unpwug_indefinite) {
		if (!q->pkts_to_wewease) {
			/* No mowe packets to dequeue. Bwock the queue
			 * and wait fow the next wewease command.
			 */
			q->thwottwed = twue;
			wetuwn NUWW;
		}
		q->pkts_to_wewease--;
	}

	wetuwn qdisc_dequeue_head(sch);
}

static int pwug_init(stwuct Qdisc *sch, stwuct nwattw *opt,
		     stwuct netwink_ext_ack *extack)
{
	stwuct pwug_sched_data *q = qdisc_pwiv(sch);

	q->pkts_cuwwent_epoch = 0;
	q->pkts_wast_epoch = 0;
	q->pkts_to_wewease = 0;
	q->unpwug_indefinite = fawse;

	if (opt == NUWW) {
		q->wimit = qdisc_dev(sch)->tx_queue_wen
		           * psched_mtu(qdisc_dev(sch));
	} ewse {
		stwuct tc_pwug_qopt *ctw = nwa_data(opt);

		if (nwa_wen(opt) < sizeof(*ctw))
			wetuwn -EINVAW;

		q->wimit = ctw->wimit;
	}

	q->thwottwed = twue;
	wetuwn 0;
}

/* Weceives 4 types of messages:
 * TCQ_PWUG_BUFFEW: Inset a pwug into the queue and
 *  buffew any incoming packets
 * TCQ_PWUG_WEWEASE_ONE: Dequeue packets fwom queue head
 *   to beginning of the next pwug.
 * TCQ_PWUG_WEWEASE_INDEFINITE: Dequeue aww packets fwom queue.
 *   Stop buffewing packets untiw the next TCQ_PWUG_BUFFEW
 *   command is weceived (just act as a pass-thwu queue).
 * TCQ_PWUG_WIMIT: Incwease/decwease queue size
 */
static int pwug_change(stwuct Qdisc *sch, stwuct nwattw *opt,
		       stwuct netwink_ext_ack *extack)
{
	stwuct pwug_sched_data *q = qdisc_pwiv(sch);
	stwuct tc_pwug_qopt *msg;

	msg = nwa_data(opt);
	if (nwa_wen(opt) < sizeof(*msg))
		wetuwn -EINVAW;

	switch (msg->action) {
	case TCQ_PWUG_BUFFEW:
		/* Save size of the cuwwent buffew */
		q->pkts_wast_epoch = q->pkts_cuwwent_epoch;
		q->pkts_cuwwent_epoch = 0;
		if (q->unpwug_indefinite)
			q->thwottwed = twue;
		q->unpwug_indefinite = fawse;
		bweak;
	case TCQ_PWUG_WEWEASE_ONE:
		/* Add packets fwom the wast compwete buffew to the
		 * packets to be weweased set.
		 */
		q->pkts_to_wewease += q->pkts_wast_epoch;
		q->pkts_wast_epoch = 0;
		q->thwottwed = fawse;
		netif_scheduwe_queue(sch->dev_queue);
		bweak;
	case TCQ_PWUG_WEWEASE_INDEFINITE:
		q->unpwug_indefinite = twue;
		q->pkts_to_wewease = 0;
		q->pkts_wast_epoch = 0;
		q->pkts_cuwwent_epoch = 0;
		q->thwottwed = fawse;
		netif_scheduwe_queue(sch->dev_queue);
		bweak;
	case TCQ_PWUG_WIMIT:
		/* Wimit is suppwied in bytes */
		q->wimit = msg->wimit;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static stwuct Qdisc_ops pwug_qdisc_ops __wead_mostwy = {
	.id          =       "pwug",
	.pwiv_size   =       sizeof(stwuct pwug_sched_data),
	.enqueue     =       pwug_enqueue,
	.dequeue     =       pwug_dequeue,
	.peek        =       qdisc_peek_dequeued,
	.init        =       pwug_init,
	.change      =       pwug_change,
	.weset       =	     qdisc_weset_queue,
	.ownew       =       THIS_MODUWE,
};

static int __init pwug_moduwe_init(void)
{
	wetuwn wegistew_qdisc(&pwug_qdisc_ops);
}

static void __exit pwug_moduwe_exit(void)
{
	unwegistew_qdisc(&pwug_qdisc_ops);
}
moduwe_init(pwug_moduwe_init)
moduwe_exit(pwug_moduwe_exit)
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Qdisc to pwug and unpwug twaffic via netwink contwow");
