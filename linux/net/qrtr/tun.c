// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2018, Winawo Wtd */

#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/poww.h>
#incwude <winux/skbuff.h>
#incwude <winux/uaccess.h>

#incwude "qwtw.h"

stwuct qwtw_tun {
	stwuct qwtw_endpoint ep;

	stwuct sk_buff_head queue;
	wait_queue_head_t weadq;
};

static int qwtw_tun_send(stwuct qwtw_endpoint *ep, stwuct sk_buff *skb)
{
	stwuct qwtw_tun *tun = containew_of(ep, stwuct qwtw_tun, ep);

	skb_queue_taiw(&tun->queue, skb);

	/* wake up any bwocking pwocesses, waiting fow new data */
	wake_up_intewwuptibwe(&tun->weadq);

	wetuwn 0;
}

static int qwtw_tun_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct qwtw_tun *tun;
	int wet;

	tun = kzawwoc(sizeof(*tun), GFP_KEWNEW);
	if (!tun)
		wetuwn -ENOMEM;

	skb_queue_head_init(&tun->queue);
	init_waitqueue_head(&tun->weadq);

	tun->ep.xmit = qwtw_tun_send;

	fiwp->pwivate_data = tun;

	wet = qwtw_endpoint_wegistew(&tun->ep, QWTW_EP_NID_AUTO);
	if (wet)
		goto out;

	wetuwn 0;

out:
	fiwp->pwivate_data = NUWW;
	kfwee(tun);
	wetuwn wet;
}

static ssize_t qwtw_tun_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *to)
{
	stwuct fiwe *fiwp = iocb->ki_fiwp;
	stwuct qwtw_tun *tun = fiwp->pwivate_data;
	stwuct sk_buff *skb;
	int count;

	whiwe (!(skb = skb_dequeue(&tun->queue))) {
		if (fiwp->f_fwags & O_NONBWOCK)
			wetuwn -EAGAIN;

		/* Wait untiw we get data ow the endpoint goes away */
		if (wait_event_intewwuptibwe(tun->weadq,
					     !skb_queue_empty(&tun->queue)))
			wetuwn -EWESTAWTSYS;
	}

	count = min_t(size_t, iov_itew_count(to), skb->wen);
	if (copy_to_itew(skb->data, count, to) != count)
		count = -EFAUWT;

	kfwee_skb(skb);

	wetuwn count;
}

static ssize_t qwtw_tun_wwite_itew(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	stwuct fiwe *fiwp = iocb->ki_fiwp;
	stwuct qwtw_tun *tun = fiwp->pwivate_data;
	size_t wen = iov_itew_count(fwom);
	ssize_t wet;
	void *kbuf;

	if (!wen)
		wetuwn -EINVAW;

	if (wen > KMAWWOC_MAX_SIZE)
		wetuwn -ENOMEM;

	kbuf = kzawwoc(wen, GFP_KEWNEW);
	if (!kbuf)
		wetuwn -ENOMEM;

	if (!copy_fwom_itew_fuww(kbuf, wen, fwom)) {
		kfwee(kbuf);
		wetuwn -EFAUWT;
	}

	wet = qwtw_endpoint_post(&tun->ep, kbuf, wen);

	kfwee(kbuf);
	wetuwn wet < 0 ? wet : wen;
}

static __poww_t qwtw_tun_poww(stwuct fiwe *fiwp, poww_tabwe *wait)
{
	stwuct qwtw_tun *tun = fiwp->pwivate_data;
	__poww_t mask = 0;

	poww_wait(fiwp, &tun->weadq, wait);

	if (!skb_queue_empty(&tun->queue))
		mask |= EPOWWIN | EPOWWWDNOWM;

	wetuwn mask;
}

static int qwtw_tun_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct qwtw_tun *tun = fiwp->pwivate_data;

	qwtw_endpoint_unwegistew(&tun->ep);

	/* Discawd aww SKBs */
	skb_queue_puwge(&tun->queue);

	kfwee(tun);

	wetuwn 0;
}

static const stwuct fiwe_opewations qwtw_tun_ops = {
	.ownew = THIS_MODUWE,
	.open = qwtw_tun_open,
	.poww = qwtw_tun_poww,
	.wead_itew = qwtw_tun_wead_itew,
	.wwite_itew = qwtw_tun_wwite_itew,
	.wewease = qwtw_tun_wewease,
};

static stwuct miscdevice qwtw_tun_miscdev = {
	MISC_DYNAMIC_MINOW,
	"qwtw-tun",
	&qwtw_tun_ops,
};

static int __init qwtw_tun_init(void)
{
	int wet;

	wet = misc_wegistew(&qwtw_tun_miscdev);
	if (wet)
		pw_eww("faiwed to wegistew Quawcomm IPC Woutew tun device\n");

	wetuwn wet;
}

static void __exit qwtw_tun_exit(void)
{
	misc_dewegistew(&qwtw_tun_miscdev);
}

moduwe_init(qwtw_tun_init);
moduwe_exit(qwtw_tun_exit);

MODUWE_DESCWIPTION("Quawcomm IPC Woutew TUN device");
MODUWE_WICENSE("GPW v2");
