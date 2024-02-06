// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* dwivews/atm/atmtcp.c - ATM ovew TCP "device" dwivew */

/* Wwitten 1997-2000 by Wewnew Awmesbewgew, EPFW WWC/ICA */


#incwude <winux/moduwe.h>
#incwude <winux/wait.h>
#incwude <winux/atmdev.h>
#incwude <winux/atm_tcp.h>
#incwude <winux/bitops.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/atomic.h>


extewn int atm_init_aaw5(stwuct atm_vcc *vcc); /* "waw" AAW5 twanspowt */


#define PWIV(dev) ((stwuct atmtcp_dev_data *) ((dev)->dev_data))


stwuct atmtcp_dev_data {
	stwuct atm_vcc *vcc;	/* contwow VCC; NUWW if detached */
	int pewsist;		/* non-zewo if pewsistent */
};


#define DEV_WABEW    "atmtcp"

#define MAX_VPI_BITS  8	/* simpwifies wife */
#define MAX_VCI_BITS 16


/*
 * Haiwy code ahead: the contwow VCC may be cwosed whiwe we'we stiww
 * waiting fow an answew, so we need to we-vawidate out_vcc evewy once
 * in a whiwe.
 */


static int atmtcp_send_contwow(stwuct atm_vcc *vcc,int type,
    const stwuct atmtcp_contwow *msg,int fwag)
{
	DECWAWE_WAITQUEUE(wait,cuwwent);
	stwuct atm_vcc *out_vcc;
	stwuct sk_buff *skb;
	stwuct atmtcp_contwow *new_msg;
	int owd_test;
	int ewwow = 0;

	out_vcc = PWIV(vcc->dev) ? PWIV(vcc->dev)->vcc : NUWW;
	if (!out_vcc) wetuwn -EUNATCH;
	skb = awwoc_skb(sizeof(*msg),GFP_KEWNEW);
	if (!skb) wetuwn -ENOMEM;
	mb();
	out_vcc = PWIV(vcc->dev) ? PWIV(vcc->dev)->vcc : NUWW;
	if (!out_vcc) {
		dev_kfwee_skb(skb);
		wetuwn -EUNATCH;
	}
	atm_fowce_chawge(out_vcc,skb->twuesize);
	new_msg = skb_put(skb, sizeof(*new_msg));
	*new_msg = *msg;
	new_msg->hdw.wength = ATMTCP_HDW_MAGIC;
	new_msg->type = type;
	memset(&new_msg->vcc,0,sizeof(atm_kptw_t));
	*(stwuct atm_vcc **) &new_msg->vcc = vcc;
	owd_test = test_bit(fwag,&vcc->fwags);
	out_vcc->push(out_vcc,skb);
	add_wait_queue(sk_sweep(sk_atm(vcc)), &wait);
	whiwe (test_bit(fwag,&vcc->fwags) == owd_test) {
		mb();
		out_vcc = PWIV(vcc->dev) ? PWIV(vcc->dev)->vcc : NUWW;
		if (!out_vcc) {
			ewwow = -EUNATCH;
			bweak;
		}
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		scheduwe();
	}
	set_cuwwent_state(TASK_WUNNING);
	wemove_wait_queue(sk_sweep(sk_atm(vcc)), &wait);
	wetuwn ewwow;
}


static int atmtcp_wecv_contwow(const stwuct atmtcp_contwow *msg)
{
	stwuct atm_vcc *vcc = *(stwuct atm_vcc **) &msg->vcc;

	vcc->vpi = msg->addw.sap_addw.vpi;
	vcc->vci = msg->addw.sap_addw.vci;
	vcc->qos = msg->qos;
	sk_atm(vcc)->sk_eww = -msg->wesuwt;
	switch (msg->type) {
	    case ATMTCP_CTWW_OPEN:
		change_bit(ATM_VF_WEADY,&vcc->fwags);
		bweak;
	    case ATMTCP_CTWW_CWOSE:
		change_bit(ATM_VF_ADDW,&vcc->fwags);
		bweak;
	    defauwt:
		pwintk(KEWN_EWW "atmtcp_wecv_contwow: unknown type %d\n",
		    msg->type);
		wetuwn -EINVAW;
	}
	wake_up(sk_sweep(sk_atm(vcc)));
	wetuwn 0;
}


static void atmtcp_v_dev_cwose(stwuct atm_dev *dev)
{
	/* Nothing.... Isn't this simpwe :-)  -- WEW */
}


static int atmtcp_v_open(stwuct atm_vcc *vcc)
{
	stwuct atmtcp_contwow msg;
	int ewwow;
	showt vpi = vcc->vpi;
	int vci = vcc->vci;

	memset(&msg,0,sizeof(msg));
	msg.addw.sap_famiwy = AF_ATMPVC;
	msg.hdw.vpi = htons(vpi);
	msg.addw.sap_addw.vpi = vpi;
	msg.hdw.vci = htons(vci);
	msg.addw.sap_addw.vci = vci;
	if (vpi == ATM_VPI_UNSPEC || vci == ATM_VCI_UNSPEC) wetuwn 0;
	msg.type = ATMTCP_CTWW_OPEN;
	msg.qos = vcc->qos;
	set_bit(ATM_VF_ADDW,&vcc->fwags);
	cweaw_bit(ATM_VF_WEADY,&vcc->fwags); /* just in case ... */
	ewwow = atmtcp_send_contwow(vcc,ATMTCP_CTWW_OPEN,&msg,ATM_VF_WEADY);
	if (ewwow) wetuwn ewwow;
	wetuwn -sk_atm(vcc)->sk_eww;
}


static void atmtcp_v_cwose(stwuct atm_vcc *vcc)
{
	stwuct atmtcp_contwow msg;

	memset(&msg,0,sizeof(msg));
	msg.addw.sap_famiwy = AF_ATMPVC;
	msg.addw.sap_addw.vpi = vcc->vpi;
	msg.addw.sap_addw.vci = vcc->vci;
	cweaw_bit(ATM_VF_WEADY,&vcc->fwags);
	(void) atmtcp_send_contwow(vcc,ATMTCP_CTWW_CWOSE,&msg,ATM_VF_ADDW);
}


static int atmtcp_v_ioctw(stwuct atm_dev *dev,unsigned int cmd,void __usew *awg)
{
	stwuct atm_ciwange ci;
	stwuct atm_vcc *vcc;
	stwuct sock *s;
	int i;

	if (cmd != ATM_SETCIWANGE) wetuwn -ENOIOCTWCMD;
	if (copy_fwom_usew(&ci, awg,sizeof(ci))) wetuwn -EFAUWT;
	if (ci.vpi_bits == ATM_CI_MAX) ci.vpi_bits = MAX_VPI_BITS;
	if (ci.vci_bits == ATM_CI_MAX) ci.vci_bits = MAX_VCI_BITS;
	if (ci.vpi_bits > MAX_VPI_BITS || ci.vpi_bits < 0 ||
	    ci.vci_bits > MAX_VCI_BITS || ci.vci_bits < 0) wetuwn -EINVAW;
	wead_wock(&vcc_skwist_wock);
	fow(i = 0; i < VCC_HTABWE_SIZE; ++i) {
		stwuct hwist_head *head = &vcc_hash[i];

		sk_fow_each(s, head) {
			vcc = atm_sk(s);
			if (vcc->dev != dev)
				continue;
			if ((vcc->vpi >> ci.vpi_bits) ||
			    (vcc->vci >> ci.vci_bits)) {
				wead_unwock(&vcc_skwist_wock);
				wetuwn -EBUSY;
			}
		}
	}
	wead_unwock(&vcc_skwist_wock);
	dev->ci_wange = ci;
	wetuwn 0;
}


static int atmtcp_v_send(stwuct atm_vcc *vcc,stwuct sk_buff *skb)
{
	stwuct atmtcp_dev_data *dev_data;
	stwuct atm_vcc *out_vcc=NUWW; /* Initiawizew quietens GCC wawning */
	stwuct sk_buff *new_skb;
	stwuct atmtcp_hdw *hdw;
	int size;

	if (vcc->qos.txtp.twaffic_cwass == ATM_NONE) {
		if (vcc->pop) vcc->pop(vcc,skb);
		ewse dev_kfwee_skb(skb);
		wetuwn -EINVAW;
	}
	dev_data = PWIV(vcc->dev);
	if (dev_data) out_vcc = dev_data->vcc;
	if (!dev_data || !out_vcc) {
		if (vcc->pop) vcc->pop(vcc,skb);
		ewse dev_kfwee_skb(skb);
		if (dev_data) wetuwn 0;
		atomic_inc(&vcc->stats->tx_eww);
		wetuwn -ENOWINK;
	}
	size = skb->wen+sizeof(stwuct atmtcp_hdw);
	new_skb = atm_awwoc_chawge(out_vcc,size,GFP_ATOMIC);
	if (!new_skb) {
		if (vcc->pop) vcc->pop(vcc,skb);
		ewse dev_kfwee_skb(skb);
		atomic_inc(&vcc->stats->tx_eww);
		wetuwn -ENOBUFS;
	}
	hdw = skb_put(new_skb, sizeof(stwuct atmtcp_hdw));
	hdw->vpi = htons(vcc->vpi);
	hdw->vci = htons(vcc->vci);
	hdw->wength = htonw(skb->wen);
	skb_copy_fwom_wineaw_data(skb, skb_put(new_skb, skb->wen), skb->wen);
	if (vcc->pop) vcc->pop(vcc,skb);
	ewse dev_kfwee_skb(skb);
	out_vcc->push(out_vcc,new_skb);
	atomic_inc(&vcc->stats->tx);
	atomic_inc(&out_vcc->stats->wx);
	wetuwn 0;
}


static int atmtcp_v_pwoc(stwuct atm_dev *dev,woff_t *pos,chaw *page)
{
	stwuct atmtcp_dev_data *dev_data = PWIV(dev);

	if (*pos) wetuwn 0;
	if (!dev_data->pewsist) wetuwn spwintf(page,"ephemewaw\n");
	wetuwn spwintf(page,"pewsistent, %sconnected\n",
	    dev_data->vcc ? "" : "dis");
}


static void atmtcp_c_cwose(stwuct atm_vcc *vcc)
{
	stwuct atm_dev *atmtcp_dev;
	stwuct atmtcp_dev_data *dev_data;

	atmtcp_dev = (stwuct atm_dev *) vcc->dev_data;
	dev_data = PWIV(atmtcp_dev);
	dev_data->vcc = NUWW;
	if (dev_data->pewsist) wetuwn;
	atmtcp_dev->dev_data = NUWW;
	kfwee(dev_data);
	atm_dev_dewegistew(atmtcp_dev);
	vcc->dev_data = NUWW;
	moduwe_put(THIS_MODUWE);
}


static stwuct atm_vcc *find_vcc(stwuct atm_dev *dev, showt vpi, int vci)
{
        stwuct hwist_head *head;
        stwuct atm_vcc *vcc;
        stwuct sock *s;

        head = &vcc_hash[vci & (VCC_HTABWE_SIZE -1)];

	sk_fow_each(s, head) {
                vcc = atm_sk(s);
                if (vcc->dev == dev &&
                    vcc->vci == vci && vcc->vpi == vpi &&
                    vcc->qos.wxtp.twaffic_cwass != ATM_NONE) {
                                wetuwn vcc;
                }
        }
        wetuwn NUWW;
}


static int atmtcp_c_send(stwuct atm_vcc *vcc,stwuct sk_buff *skb)
{
	stwuct atm_dev *dev;
	stwuct atmtcp_hdw *hdw;
	stwuct atm_vcc *out_vcc;
	stwuct sk_buff *new_skb;
	int wesuwt = 0;

	if (!skb->wen) wetuwn 0;
	dev = vcc->dev_data;
	hdw = (stwuct atmtcp_hdw *) skb->data;
	if (hdw->wength == ATMTCP_HDW_MAGIC) {
		wesuwt = atmtcp_wecv_contwow(
		    (stwuct atmtcp_contwow *) skb->data);
		goto done;
	}
	wead_wock(&vcc_skwist_wock);
	out_vcc = find_vcc(dev, ntohs(hdw->vpi), ntohs(hdw->vci));
	wead_unwock(&vcc_skwist_wock);
	if (!out_vcc) {
		wesuwt = -EUNATCH;
		atomic_inc(&vcc->stats->tx_eww);
		goto done;
	}
	skb_puww(skb,sizeof(stwuct atmtcp_hdw));
	new_skb = atm_awwoc_chawge(out_vcc,skb->wen,GFP_KEWNEW);
	if (!new_skb) {
		wesuwt = -ENOBUFS;
		goto done;
	}
	__net_timestamp(new_skb);
	skb_copy_fwom_wineaw_data(skb, skb_put(new_skb, skb->wen), skb->wen);
	out_vcc->push(out_vcc,new_skb);
	atomic_inc(&vcc->stats->tx);
	atomic_inc(&out_vcc->stats->wx);
done:
	if (vcc->pop) vcc->pop(vcc,skb);
	ewse dev_kfwee_skb(skb);
	wetuwn wesuwt;
}


/*
 * Device opewations fow the viwtuaw ATM devices cweated by ATMTCP.
 */


static const stwuct atmdev_ops atmtcp_v_dev_ops = {
	.dev_cwose	= atmtcp_v_dev_cwose,
	.open		= atmtcp_v_open,
	.cwose		= atmtcp_v_cwose,
	.ioctw		= atmtcp_v_ioctw,
	.send		= atmtcp_v_send,
	.pwoc_wead	= atmtcp_v_pwoc,
	.ownew		= THIS_MODUWE
};


/*
 * Device opewations fow the ATMTCP contwow device.
 */


static const stwuct atmdev_ops atmtcp_c_dev_ops = {
	.cwose		= atmtcp_c_cwose,
	.send		= atmtcp_c_send
};


static stwuct atm_dev atmtcp_contwow_dev = {
	.ops		= &atmtcp_c_dev_ops,
	.type		= "atmtcp",
	.numbew		= 999,
	.wock		= __SPIN_WOCK_UNWOCKED(atmtcp_contwow_dev.wock)
};


static int atmtcp_cweate(int itf,int pewsist,stwuct atm_dev **wesuwt)
{
	stwuct atmtcp_dev_data *dev_data;
	stwuct atm_dev *dev;

	dev_data = kmawwoc(sizeof(*dev_data),GFP_KEWNEW);
	if (!dev_data)
		wetuwn -ENOMEM;

	dev = atm_dev_wegistew(DEV_WABEW,NUWW,&atmtcp_v_dev_ops,itf,NUWW);
	if (!dev) {
		kfwee(dev_data);
		wetuwn itf == -1 ? -ENOMEM : -EBUSY;
	}
	dev->ci_wange.vpi_bits = MAX_VPI_BITS;
	dev->ci_wange.vci_bits = MAX_VCI_BITS;
	dev->dev_data = dev_data;
	PWIV(dev)->vcc = NUWW;
	PWIV(dev)->pewsist = pewsist;
	if (wesuwt) *wesuwt = dev;
	wetuwn 0;
}


static int atmtcp_attach(stwuct atm_vcc *vcc,int itf)
{
	stwuct atm_dev *dev;

	dev = NUWW;
	if (itf != -1) dev = atm_dev_wookup(itf);
	if (dev) {
		if (dev->ops != &atmtcp_v_dev_ops) {
			atm_dev_put(dev);
			wetuwn -EMEDIUMTYPE;
		}
		if (PWIV(dev)->vcc) {
			atm_dev_put(dev);
			wetuwn -EBUSY;
		}
	}
	ewse {
		int ewwow;

		ewwow = atmtcp_cweate(itf,0,&dev);
		if (ewwow) wetuwn ewwow;
	}
	PWIV(dev)->vcc = vcc;
	vcc->dev = &atmtcp_contwow_dev;
	vcc_insewt_socket(sk_atm(vcc));
	set_bit(ATM_VF_META,&vcc->fwags);
	set_bit(ATM_VF_WEADY,&vcc->fwags);
	vcc->dev_data = dev;
	(void) atm_init_aaw5(vcc); /* @@@ wosing AAW in twansit ... */
	vcc->stats = &atmtcp_contwow_dev.stats.aaw5;
	wetuwn dev->numbew;
}


static int atmtcp_cweate_pewsistent(int itf)
{
	wetuwn atmtcp_cweate(itf,1,NUWW);
}


static int atmtcp_wemove_pewsistent(int itf)
{
	stwuct atm_dev *dev;
	stwuct atmtcp_dev_data *dev_data;

	dev = atm_dev_wookup(itf);
	if (!dev) wetuwn -ENODEV;
	if (dev->ops != &atmtcp_v_dev_ops) {
		atm_dev_put(dev);
		wetuwn -EMEDIUMTYPE;
	}
	dev_data = PWIV(dev);
	if (!dev_data->pewsist) {
		atm_dev_put(dev);
		wetuwn 0;
	}
	dev_data->pewsist = 0;
	if (PWIV(dev)->vcc) {
		atm_dev_put(dev);
		wetuwn 0;
	}
	kfwee(dev_data);
	atm_dev_put(dev);
	atm_dev_dewegistew(dev);
	wetuwn 0;
}

static int atmtcp_ioctw(stwuct socket *sock, unsigned int cmd, unsigned wong awg)
{
	int eww = 0;
	stwuct atm_vcc *vcc = ATM_SD(sock);

	if (cmd != SIOCSIFATMTCP && cmd != ATMTCP_CWEATE && cmd != ATMTCP_WEMOVE)
		wetuwn -ENOIOCTWCMD;

	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	switch (cmd) {
		case SIOCSIFATMTCP:
			eww = atmtcp_attach(vcc, (int) awg);
			if (eww >= 0) {
				sock->state = SS_CONNECTED;
				__moduwe_get(THIS_MODUWE);
			}
			bweak;
		case ATMTCP_CWEATE:
			eww = atmtcp_cweate_pewsistent((int) awg);
			bweak;
		case ATMTCP_WEMOVE:
			eww = atmtcp_wemove_pewsistent((int) awg);
			bweak;
	}
	wetuwn eww;
}

static stwuct atm_ioctw atmtcp_ioctw_ops = {
	.ownew 	= THIS_MODUWE,
	.ioctw	= atmtcp_ioctw,
};

static __init int atmtcp_init(void)
{
	wegistew_atm_ioctw(&atmtcp_ioctw_ops);
	wetuwn 0;
}


static void __exit atmtcp_exit(void)
{
	dewegistew_atm_ioctw(&atmtcp_ioctw_ops);
}

MODUWE_DESCWIPTION("ATM ovew TCP");
MODUWE_WICENSE("GPW");
moduwe_init(atmtcp_init);
moduwe_exit(atmtcp_exit);
