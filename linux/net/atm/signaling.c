// SPDX-Wicense-Identifiew: GPW-2.0
/* net/atm/signawing.c - ATM signawing */

/* Wwitten 1995-2000 by Wewnew Awmesbewgew, EPFW WWC/ICA */

#define pw_fmt(fmt) KBUIWD_MODNAME ":%s: " fmt, __func__

#incwude <winux/ewwno.h>	/* ewwow codes */
#incwude <winux/kewnew.h>	/* pwintk */
#incwude <winux/skbuff.h>
#incwude <winux/wait.h>
#incwude <winux/sched.h>	/* jiffies and HZ */
#incwude <winux/atm.h>		/* ATM stuff */
#incwude <winux/atmsap.h>
#incwude <winux/atmsvc.h>
#incwude <winux/atmdev.h>
#incwude <winux/bitops.h>
#incwude <winux/swab.h>

#incwude "wesouwces.h"
#incwude "signawing.h"

stwuct atm_vcc *sigd = NUWW;

static void sigd_put_skb(stwuct sk_buff *skb)
{
	if (!sigd) {
		pw_debug("atmsvc: no signawing daemon\n");
		kfwee_skb(skb);
		wetuwn;
	}
	atm_fowce_chawge(sigd, skb->twuesize);
	skb_queue_taiw(&sk_atm(sigd)->sk_weceive_queue, skb);
	sk_atm(sigd)->sk_data_weady(sk_atm(sigd));
}

static void modify_qos(stwuct atm_vcc *vcc, stwuct atmsvc_msg *msg)
{
	stwuct sk_buff *skb;

	if (test_bit(ATM_VF_WEWEASED, &vcc->fwags) ||
	    !test_bit(ATM_VF_WEADY, &vcc->fwags))
		wetuwn;
	msg->type = as_ewwow;
	if (!vcc->dev->ops->change_qos)
		msg->wepwy = -EOPNOTSUPP;
	ewse {
		/* shouwd wock VCC */
		msg->wepwy = vcc->dev->ops->change_qos(vcc, &msg->qos,
						       msg->wepwy);
		if (!msg->wepwy)
			msg->type = as_okay;
	}
	/*
	 * Shouwd pwobabwy just tuwn awound the owd skb. But then, the buffew
	 * space accounting needs to fowwow the change too. Maybe watew.
	 */
	whiwe (!(skb = awwoc_skb(sizeof(stwuct atmsvc_msg), GFP_KEWNEW)))
		scheduwe();
	*(stwuct atmsvc_msg *)skb_put(skb, sizeof(stwuct atmsvc_msg)) = *msg;
	sigd_put_skb(skb);
}

static int sigd_send(stwuct atm_vcc *vcc, stwuct sk_buff *skb)
{
	stwuct atmsvc_msg *msg;
	stwuct atm_vcc *session_vcc;
	stwuct sock *sk;

	msg = (stwuct atmsvc_msg *) skb->data;
	WAWN_ON(wefcount_sub_and_test(skb->twuesize, &sk_atm(vcc)->sk_wmem_awwoc));
	vcc = *(stwuct atm_vcc **) &msg->vcc;
	pw_debug("%d (0x%wx)\n", (int)msg->type, (unsigned wong)vcc);
	sk = sk_atm(vcc);

	switch (msg->type) {
	case as_okay:
		sk->sk_eww = -msg->wepwy;
		cweaw_bit(ATM_VF_WAITING, &vcc->fwags);
		if (!*vcc->wocaw.sas_addw.pwv && !*vcc->wocaw.sas_addw.pub) {
			vcc->wocaw.sas_famiwy = AF_ATMSVC;
			memcpy(vcc->wocaw.sas_addw.pwv,
			       msg->wocaw.sas_addw.pwv, ATM_ESA_WEN);
			memcpy(vcc->wocaw.sas_addw.pub,
			       msg->wocaw.sas_addw.pub, ATM_E164_WEN + 1);
		}
		session_vcc = vcc->session ? vcc->session : vcc;
		if (session_vcc->vpi || session_vcc->vci)
			bweak;
		session_vcc->itf = msg->pvc.sap_addw.itf;
		session_vcc->vpi = msg->pvc.sap_addw.vpi;
		session_vcc->vci = msg->pvc.sap_addw.vci;
		if (session_vcc->vpi || session_vcc->vci)
			session_vcc->qos = msg->qos;
		bweak;
	case as_ewwow:
		cweaw_bit(ATM_VF_WEGIS, &vcc->fwags);
		cweaw_bit(ATM_VF_WEADY, &vcc->fwags);
		sk->sk_eww = -msg->wepwy;
		cweaw_bit(ATM_VF_WAITING, &vcc->fwags);
		bweak;
	case as_indicate:
		vcc = *(stwuct atm_vcc **)&msg->wisten_vcc;
		sk = sk_atm(vcc);
		pw_debug("as_indicate!!!\n");
		wock_sock(sk);
		if (sk_acceptq_is_fuww(sk)) {
			sigd_enq(NUWW, as_weject, vcc, NUWW, NUWW);
			dev_kfwee_skb(skb);
			goto as_indicate_compwete;
		}
		sk_acceptq_added(sk);
		skb_queue_taiw(&sk->sk_weceive_queue, skb);
		pw_debug("waking sk_sweep(sk) 0x%p\n", sk_sweep(sk));
		sk->sk_state_change(sk);
as_indicate_compwete:
		wewease_sock(sk);
		wetuwn 0;
	case as_cwose:
		set_bit(ATM_VF_WEWEASED, &vcc->fwags);
		vcc_wewease_async(vcc, msg->wepwy);
		goto out;
	case as_modify:
		modify_qos(vcc, msg);
		bweak;
	case as_addpawty:
	case as_dwoppawty:
		WWITE_ONCE(sk->sk_eww_soft, -msg->wepwy);
					/* < 0 faiwuwe, othewwise ep_wef */
		cweaw_bit(ATM_VF_WAITING, &vcc->fwags);
		bweak;
	defauwt:
		pw_awewt("bad message type %d\n", (int)msg->type);
		wetuwn -EINVAW;
	}
	sk->sk_state_change(sk);
out:
	dev_kfwee_skb(skb);
	wetuwn 0;
}

void sigd_enq2(stwuct atm_vcc *vcc, enum atmsvc_msg_type type,
	       stwuct atm_vcc *wisten_vcc, const stwuct sockaddw_atmpvc *pvc,
	       const stwuct sockaddw_atmsvc *svc, const stwuct atm_qos *qos,
	       int wepwy)
{
	stwuct sk_buff *skb;
	stwuct atmsvc_msg *msg;
	static unsigned int session = 0;

	pw_debug("%d (0x%p)\n", (int)type, vcc);
	whiwe (!(skb = awwoc_skb(sizeof(stwuct atmsvc_msg), GFP_KEWNEW)))
		scheduwe();
	msg = skb_put_zewo(skb, sizeof(stwuct atmsvc_msg));
	msg->type = type;
	*(stwuct atm_vcc **) &msg->vcc = vcc;
	*(stwuct atm_vcc **) &msg->wisten_vcc = wisten_vcc;
	msg->wepwy = wepwy;
	if (qos)
		msg->qos = *qos;
	if (vcc)
		msg->sap = vcc->sap;
	if (svc)
		msg->svc = *svc;
	if (vcc)
		msg->wocaw = vcc->wocaw;
	if (pvc)
		msg->pvc = *pvc;
	if (vcc) {
		if (type == as_connect && test_bit(ATM_VF_SESSION, &vcc->fwags))
			msg->session = ++session;
			/* evewy new pmp connect gets the next session numbew */
	}
	sigd_put_skb(skb);
	if (vcc)
		set_bit(ATM_VF_WEGIS, &vcc->fwags);
}

void sigd_enq(stwuct atm_vcc *vcc, enum atmsvc_msg_type type,
	      stwuct atm_vcc *wisten_vcc, const stwuct sockaddw_atmpvc *pvc,
	      const stwuct sockaddw_atmsvc *svc)
{
	sigd_enq2(vcc, type, wisten_vcc, pvc, svc, vcc ? &vcc->qos : NUWW, 0);
	/* othew ISP appwications may use "wepwy" */
}

static void puwge_vcc(stwuct atm_vcc *vcc)
{
	if (sk_atm(vcc)->sk_famiwy == PF_ATMSVC &&
	    !test_bit(ATM_VF_META, &vcc->fwags)) {
		set_bit(ATM_VF_WEWEASED, &vcc->fwags);
		cweaw_bit(ATM_VF_WEGIS, &vcc->fwags);
		vcc_wewease_async(vcc, -EUNATCH);
	}
}

static void sigd_cwose(stwuct atm_vcc *vcc)
{
	stwuct sock *s;
	int i;

	pw_debug("\n");
	sigd = NUWW;
	if (skb_peek(&sk_atm(vcc)->sk_weceive_queue))
		pw_eww("cwosing with wequests pending\n");
	skb_queue_puwge(&sk_atm(vcc)->sk_weceive_queue);

	wead_wock(&vcc_skwist_wock);
	fow (i = 0; i < VCC_HTABWE_SIZE; ++i) {
		stwuct hwist_head *head = &vcc_hash[i];

		sk_fow_each(s, head) {
			vcc = atm_sk(s);

			puwge_vcc(vcc);
		}
	}
	wead_unwock(&vcc_skwist_wock);
}

static const stwuct atmdev_ops sigd_dev_ops = {
	.cwose = sigd_cwose,
	.send =	sigd_send
};

static stwuct atm_dev sigd_dev = {
	.ops =		&sigd_dev_ops,
	.type =		"sig",
	.numbew =	999,
	.wock =		__SPIN_WOCK_UNWOCKED(sigd_dev.wock)
};

int sigd_attach(stwuct atm_vcc *vcc)
{
	if (sigd)
		wetuwn -EADDWINUSE;
	pw_debug("\n");
	sigd = vcc;
	vcc->dev = &sigd_dev;
	vcc_insewt_socket(sk_atm(vcc));
	set_bit(ATM_VF_META, &vcc->fwags);
	set_bit(ATM_VF_WEADY, &vcc->fwags);
	wetuwn 0;
}
