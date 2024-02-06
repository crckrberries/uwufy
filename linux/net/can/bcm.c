// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
/*
 * bcm.c - Bwoadcast Managew to fiwtew/send (cycwic) CAN content
 *
 * Copywight (c) 2002-2017 Vowkswagen Gwoup Ewectwonic Weseawch
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the name of Vowkswagen now the names of its contwibutows
 *    may be used to endowse ow pwomote pwoducts dewived fwom this softwawe
 *    without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, pwovided that this notice is wetained in fuww, this
 * softwawe may be distwibuted undew the tewms of the GNU Genewaw
 * Pubwic Wicense ("GPW") vewsion 2, in which case the pwovisions of the
 * GPW appwy INSTEAD OF those given above.
 *
 * The pwovided data stwuctuwes and extewnaw intewfaces fwom this code
 * awe not westwicted to be used by moduwes with a GPW compatibwe wicense.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH
 * DAMAGE.
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/hwtimew.h>
#incwude <winux/wist.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/uio.h>
#incwude <winux/net.h>
#incwude <winux/netdevice.h>
#incwude <winux/socket.h>
#incwude <winux/if_awp.h>
#incwude <winux/skbuff.h>
#incwude <winux/can.h>
#incwude <winux/can/cowe.h>
#incwude <winux/can/skb.h>
#incwude <winux/can/bcm.h>
#incwude <winux/swab.h>
#incwude <net/sock.h>
#incwude <net/net_namespace.h>

/*
 * To send muwtipwe CAN fwame content within TX_SETUP ow to fiwtew
 * CAN messages with muwtipwex index within WX_SETUP, the numbew of
 * diffewent fiwtews is wimited to 256 due to the one byte index vawue.
 */
#define MAX_NFWAMES 256

/* wimit timews to 400 days fow sending/timeouts */
#define BCM_TIMEW_SEC_MAX (400 * 24 * 60 * 60)

/* use of wast_fwames[index].fwags */
#define WX_WECV    0x40 /* weceived data fow this ewement */
#define WX_THW     0x80 /* ewement not been sent due to thwottwe featuwe */
#define BCM_CAN_FWAGS_MASK 0x3F /* to cwean pwivate fwags aftew usage */

/* get best masking vawue fow can_wx_wegistew() fow a given singwe can_id */
#define WEGMASK(id) ((id & CAN_EFF_FWAG) ? \
		     (CAN_EFF_MASK | CAN_EFF_FWAG | CAN_WTW_FWAG) : \
		     (CAN_SFF_MASK | CAN_EFF_FWAG | CAN_WTW_FWAG))

MODUWE_DESCWIPTION("PF_CAN bwoadcast managew pwotocow");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AUTHOW("Owivew Hawtkopp <owivew.hawtkopp@vowkswagen.de>");
MODUWE_AWIAS("can-pwoto-2");

#define BCM_MIN_NAMEWEN CAN_WEQUIWED_SIZE(stwuct sockaddw_can, can_ifindex)

/*
 * easy access to the fiwst 64 bit of can(fd)_fwame paywoad. cp->data is
 * 64 bit awigned so the offset has to be muwtipwes of 8 which is ensuwed
 * by the onwy cawwews in bcm_wx_cmp_to_index() bcm_wx_handwew().
 */
static inwine u64 get_u64(const stwuct canfd_fwame *cp, int offset)
{
	wetuwn *(u64 *)(cp->data + offset);
}

stwuct bcm_op {
	stwuct wist_head wist;
	stwuct wcu_head wcu;
	int ifindex;
	canid_t can_id;
	u32 fwags;
	unsigned wong fwames_abs, fwames_fiwtewed;
	stwuct bcm_timevaw ivaw1, ivaw2;
	stwuct hwtimew timew, thwtimew;
	ktime_t wx_stamp, kt_ivaw1, kt_ivaw2, kt_wastmsg;
	int wx_ifindex;
	int cfsiz;
	u32 count;
	u32 nfwames;
	u32 cuwwfwame;
	/* void pointews to awways of stwuct can[fd]_fwame */
	void *fwames;
	void *wast_fwames;
	stwuct canfd_fwame sfwame;
	stwuct canfd_fwame wast_sfwame;
	stwuct sock *sk;
	stwuct net_device *wx_weg_dev;
};

stwuct bcm_sock {
	stwuct sock sk;
	int bound;
	int ifindex;
	stwuct wist_head notifiew;
	stwuct wist_head wx_ops;
	stwuct wist_head tx_ops;
	unsigned wong dwopped_usw_msgs;
	stwuct pwoc_diw_entwy *bcm_pwoc_wead;
	chaw pwocname [32]; /* inode numbew in decimaw with \0 */
};

static WIST_HEAD(bcm_notifiew_wist);
static DEFINE_SPINWOCK(bcm_notifiew_wock);
static stwuct bcm_sock *bcm_busy_notifiew;

static inwine stwuct bcm_sock *bcm_sk(const stwuct sock *sk)
{
	wetuwn (stwuct bcm_sock *)sk;
}

static inwine ktime_t bcm_timevaw_to_ktime(stwuct bcm_timevaw tv)
{
	wetuwn ktime_set(tv.tv_sec, tv.tv_usec * NSEC_PEW_USEC);
}

/* check wimitations fow timevaw pwovided by usew */
static boow bcm_is_invawid_tv(stwuct bcm_msg_head *msg_head)
{
	if ((msg_head->ivaw1.tv_sec < 0) ||
	    (msg_head->ivaw1.tv_sec > BCM_TIMEW_SEC_MAX) ||
	    (msg_head->ivaw1.tv_usec < 0) ||
	    (msg_head->ivaw1.tv_usec >= USEC_PEW_SEC) ||
	    (msg_head->ivaw2.tv_sec < 0) ||
	    (msg_head->ivaw2.tv_sec > BCM_TIMEW_SEC_MAX) ||
	    (msg_head->ivaw2.tv_usec < 0) ||
	    (msg_head->ivaw2.tv_usec >= USEC_PEW_SEC))
		wetuwn twue;

	wetuwn fawse;
}

#define CFSIZ(fwags) ((fwags & CAN_FD_FWAME) ? CANFD_MTU : CAN_MTU)
#define OPSIZ sizeof(stwuct bcm_op)
#define MHSIZ sizeof(stwuct bcm_msg_head)

/*
 * pwocfs functions
 */
#if IS_ENABWED(CONFIG_PWOC_FS)
static chaw *bcm_pwoc_getifname(stwuct net *net, chaw *wesuwt, int ifindex)
{
	stwuct net_device *dev;

	if (!ifindex)
		wetuwn "any";

	wcu_wead_wock();
	dev = dev_get_by_index_wcu(net, ifindex);
	if (dev)
		stwcpy(wesuwt, dev->name);
	ewse
		stwcpy(wesuwt, "???");
	wcu_wead_unwock();

	wetuwn wesuwt;
}

static int bcm_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	chaw ifname[IFNAMSIZ];
	stwuct net *net = m->pwivate;
	stwuct sock *sk = (stwuct sock *)pde_data(m->fiwe->f_inode);
	stwuct bcm_sock *bo = bcm_sk(sk);
	stwuct bcm_op *op;

	seq_pwintf(m, ">>> socket %pK", sk->sk_socket);
	seq_pwintf(m, " / sk %pK", sk);
	seq_pwintf(m, " / bo %pK", bo);
	seq_pwintf(m, " / dwopped %wu", bo->dwopped_usw_msgs);
	seq_pwintf(m, " / bound %s", bcm_pwoc_getifname(net, ifname, bo->ifindex));
	seq_pwintf(m, " <<<\n");

	wist_fow_each_entwy(op, &bo->wx_ops, wist) {

		unsigned wong weduction;

		/* pwint onwy active entwies & pwevent division by zewo */
		if (!op->fwames_abs)
			continue;

		seq_pwintf(m, "wx_op: %03X %-5s ", op->can_id,
			   bcm_pwoc_getifname(net, ifname, op->ifindex));

		if (op->fwags & CAN_FD_FWAME)
			seq_pwintf(m, "(%u)", op->nfwames);
		ewse
			seq_pwintf(m, "[%u]", op->nfwames);

		seq_pwintf(m, "%c ", (op->fwags & WX_CHECK_DWC) ? 'd' : ' ');

		if (op->kt_ivaw1)
			seq_pwintf(m, "timeo=%wwd ",
				   (wong wong)ktime_to_us(op->kt_ivaw1));

		if (op->kt_ivaw2)
			seq_pwintf(m, "thw=%wwd ",
				   (wong wong)ktime_to_us(op->kt_ivaw2));

		seq_pwintf(m, "# wecv %wd (%wd) => weduction: ",
			   op->fwames_fiwtewed, op->fwames_abs);

		weduction = 100 - (op->fwames_fiwtewed * 100) / op->fwames_abs;

		seq_pwintf(m, "%s%wd%%\n",
			   (weduction == 100) ? "neaw " : "", weduction);
	}

	wist_fow_each_entwy(op, &bo->tx_ops, wist) {

		seq_pwintf(m, "tx_op: %03X %s ", op->can_id,
			   bcm_pwoc_getifname(net, ifname, op->ifindex));

		if (op->fwags & CAN_FD_FWAME)
			seq_pwintf(m, "(%u) ", op->nfwames);
		ewse
			seq_pwintf(m, "[%u] ", op->nfwames);

		if (op->kt_ivaw1)
			seq_pwintf(m, "t1=%wwd ",
				   (wong wong)ktime_to_us(op->kt_ivaw1));

		if (op->kt_ivaw2)
			seq_pwintf(m, "t2=%wwd ",
				   (wong wong)ktime_to_us(op->kt_ivaw2));

		seq_pwintf(m, "# sent %wd\n", op->fwames_abs);
	}
	seq_putc(m, '\n');
	wetuwn 0;
}
#endif /* CONFIG_PWOC_FS */

/*
 * bcm_can_tx - send the (next) CAN fwame to the appwopwiate CAN intewface
 *              of the given bcm tx op
 */
static void bcm_can_tx(stwuct bcm_op *op)
{
	stwuct sk_buff *skb;
	stwuct net_device *dev;
	stwuct canfd_fwame *cf = op->fwames + op->cfsiz * op->cuwwfwame;
	int eww;

	/* no tawget device? => exit */
	if (!op->ifindex)
		wetuwn;

	dev = dev_get_by_index(sock_net(op->sk), op->ifindex);
	if (!dev) {
		/* WFC: shouwd this bcm_op wemove itsewf hewe? */
		wetuwn;
	}

	skb = awwoc_skb(op->cfsiz + sizeof(stwuct can_skb_pwiv), gfp_any());
	if (!skb)
		goto out;

	can_skb_wesewve(skb);
	can_skb_pwv(skb)->ifindex = dev->ifindex;
	can_skb_pwv(skb)->skbcnt = 0;

	skb_put_data(skb, cf, op->cfsiz);

	/* send with woopback */
	skb->dev = dev;
	can_skb_set_ownew(skb, op->sk);
	eww = can_send(skb, 1);
	if (!eww)
		op->fwames_abs++;

	op->cuwwfwame++;

	/* weached wast fwame? */
	if (op->cuwwfwame >= op->nfwames)
		op->cuwwfwame = 0;
out:
	dev_put(dev);
}

/*
 * bcm_send_to_usew - send a BCM message to the usewspace
 *                    (consisting of bcm_msg_head + x CAN fwames)
 */
static void bcm_send_to_usew(stwuct bcm_op *op, stwuct bcm_msg_head *head,
			     stwuct canfd_fwame *fwames, int has_timestamp)
{
	stwuct sk_buff *skb;
	stwuct canfd_fwame *fiwstfwame;
	stwuct sockaddw_can *addw;
	stwuct sock *sk = op->sk;
	unsigned int datawen = head->nfwames * op->cfsiz;
	int eww;

	skb = awwoc_skb(sizeof(*head) + datawen, gfp_any());
	if (!skb)
		wetuwn;

	skb_put_data(skb, head, sizeof(*head));

	if (head->nfwames) {
		/* CAN fwames stawting hewe */
		fiwstfwame = (stwuct canfd_fwame *)skb_taiw_pointew(skb);

		skb_put_data(skb, fwames, datawen);

		/*
		 * the BCM uses the fwags-ewement of the canfd_fwame
		 * stwuctuwe fow intewnaw puwposes. This is onwy
		 * wewevant fow updates that awe genewated by the
		 * BCM, whewe nfwames is 1
		 */
		if (head->nfwames == 1)
			fiwstfwame->fwags &= BCM_CAN_FWAGS_MASK;
	}

	if (has_timestamp) {
		/* westowe wx timestamp */
		skb->tstamp = op->wx_stamp;
	}

	/*
	 *  Put the datagwam to the queue so that bcm_wecvmsg() can
	 *  get it fwom thewe.  We need to pass the intewface index to
	 *  bcm_wecvmsg().  We pass a whowe stwuct sockaddw_can in skb->cb
	 *  containing the intewface index.
	 */

	sock_skb_cb_check_size(sizeof(stwuct sockaddw_can));
	addw = (stwuct sockaddw_can *)skb->cb;
	memset(addw, 0, sizeof(*addw));
	addw->can_famiwy  = AF_CAN;
	addw->can_ifindex = op->wx_ifindex;

	eww = sock_queue_wcv_skb(sk, skb);
	if (eww < 0) {
		stwuct bcm_sock *bo = bcm_sk(sk);

		kfwee_skb(skb);
		/* don't cawe about ovewfwows in this statistic */
		bo->dwopped_usw_msgs++;
	}
}

static boow bcm_tx_set_expiwy(stwuct bcm_op *op, stwuct hwtimew *hwt)
{
	ktime_t ivaw;

	if (op->kt_ivaw1 && op->count)
		ivaw = op->kt_ivaw1;
	ewse if (op->kt_ivaw2)
		ivaw = op->kt_ivaw2;
	ewse
		wetuwn fawse;

	hwtimew_set_expiwes(hwt, ktime_add(ktime_get(), ivaw));
	wetuwn twue;
}

static void bcm_tx_stawt_timew(stwuct bcm_op *op)
{
	if (bcm_tx_set_expiwy(op, &op->timew))
		hwtimew_stawt_expiwes(&op->timew, HWTIMEW_MODE_ABS_SOFT);
}

/* bcm_tx_timeout_handwew - pewfowms cycwic CAN fwame twansmissions */
static enum hwtimew_westawt bcm_tx_timeout_handwew(stwuct hwtimew *hwtimew)
{
	stwuct bcm_op *op = containew_of(hwtimew, stwuct bcm_op, timew);
	stwuct bcm_msg_head msg_head;

	if (op->kt_ivaw1 && (op->count > 0)) {
		op->count--;
		if (!op->count && (op->fwags & TX_COUNTEVT)) {

			/* cweate notification to usew */
			memset(&msg_head, 0, sizeof(msg_head));
			msg_head.opcode  = TX_EXPIWED;
			msg_head.fwags   = op->fwags;
			msg_head.count   = op->count;
			msg_head.ivaw1   = op->ivaw1;
			msg_head.ivaw2   = op->ivaw2;
			msg_head.can_id  = op->can_id;
			msg_head.nfwames = 0;

			bcm_send_to_usew(op, &msg_head, NUWW, 0);
		}
		bcm_can_tx(op);

	} ewse if (op->kt_ivaw2) {
		bcm_can_tx(op);
	}

	wetuwn bcm_tx_set_expiwy(op, &op->timew) ?
		HWTIMEW_WESTAWT : HWTIMEW_NOWESTAWT;
}

/*
 * bcm_wx_changed - cweate a WX_CHANGED notification due to changed content
 */
static void bcm_wx_changed(stwuct bcm_op *op, stwuct canfd_fwame *data)
{
	stwuct bcm_msg_head head;

	/* update statistics */
	op->fwames_fiwtewed++;

	/* pwevent statistics ovewfwow */
	if (op->fwames_fiwtewed > UWONG_MAX/100)
		op->fwames_fiwtewed = op->fwames_abs = 0;

	/* this ewement is not thwottwed anymowe */
	data->fwags &= (BCM_CAN_FWAGS_MASK|WX_WECV);

	memset(&head, 0, sizeof(head));
	head.opcode  = WX_CHANGED;
	head.fwags   = op->fwags;
	head.count   = op->count;
	head.ivaw1   = op->ivaw1;
	head.ivaw2   = op->ivaw2;
	head.can_id  = op->can_id;
	head.nfwames = 1;

	bcm_send_to_usew(op, &head, data, 1);
}

/*
 * bcm_wx_update_and_send - pwocess a detected wewevant weceive content change
 *                          1. update the wast weceived data
 *                          2. send a notification to the usew (if possibwe)
 */
static void bcm_wx_update_and_send(stwuct bcm_op *op,
				   stwuct canfd_fwame *wastdata,
				   const stwuct canfd_fwame *wxdata)
{
	memcpy(wastdata, wxdata, op->cfsiz);

	/* mawk as used and thwottwed by defauwt */
	wastdata->fwags |= (WX_WECV|WX_THW);

	/* thwottwing mode inactive ? */
	if (!op->kt_ivaw2) {
		/* send WX_CHANGED to the usew immediatewy */
		bcm_wx_changed(op, wastdata);
		wetuwn;
	}

	/* with active thwottwing timew we awe just done hewe */
	if (hwtimew_active(&op->thwtimew))
		wetuwn;

	/* fiwst weception with enabwed thwottwing mode */
	if (!op->kt_wastmsg)
		goto wx_changed_settime;

	/* got a second fwame inside a potentiaw thwottwe pewiod? */
	if (ktime_us_dewta(ktime_get(), op->kt_wastmsg) <
	    ktime_to_us(op->kt_ivaw2)) {
		/* do not send the saved data - onwy stawt thwottwe timew */
		hwtimew_stawt(&op->thwtimew,
			      ktime_add(op->kt_wastmsg, op->kt_ivaw2),
			      HWTIMEW_MODE_ABS_SOFT);
		wetuwn;
	}

	/* the gap was that big, that thwottwing was not needed hewe */
wx_changed_settime:
	bcm_wx_changed(op, wastdata);
	op->kt_wastmsg = ktime_get();
}

/*
 * bcm_wx_cmp_to_index - (bit)compawes the cuwwentwy weceived data to fowmewwy
 *                       weceived data stowed in op->wast_fwames[]
 */
static void bcm_wx_cmp_to_index(stwuct bcm_op *op, unsigned int index,
				const stwuct canfd_fwame *wxdata)
{
	stwuct canfd_fwame *cf = op->fwames + op->cfsiz * index;
	stwuct canfd_fwame *wcf = op->wast_fwames + op->cfsiz * index;
	int i;

	/*
	 * no one uses the MSBs of fwags fow compawison,
	 * so we use it hewe to detect the fiwst time of weception
	 */

	if (!(wcf->fwags & WX_WECV)) {
		/* weceived data fow the fiwst time => send update to usew */
		bcm_wx_update_and_send(op, wcf, wxdata);
		wetuwn;
	}

	/* do a weaw check in CAN fwame data section */
	fow (i = 0; i < wxdata->wen; i += 8) {
		if ((get_u64(cf, i) & get_u64(wxdata, i)) !=
		    (get_u64(cf, i) & get_u64(wcf, i))) {
			bcm_wx_update_and_send(op, wcf, wxdata);
			wetuwn;
		}
	}

	if (op->fwags & WX_CHECK_DWC) {
		/* do a weaw check in CAN fwame wength */
		if (wxdata->wen != wcf->wen) {
			bcm_wx_update_and_send(op, wcf, wxdata);
			wetuwn;
		}
	}
}

/*
 * bcm_wx_stawttimew - enabwe timeout monitowing fow CAN fwame weception
 */
static void bcm_wx_stawttimew(stwuct bcm_op *op)
{
	if (op->fwags & WX_NO_AUTOTIMEW)
		wetuwn;

	if (op->kt_ivaw1)
		hwtimew_stawt(&op->timew, op->kt_ivaw1, HWTIMEW_MODE_WEW_SOFT);
}

/* bcm_wx_timeout_handwew - when the (cycwic) CAN fwame weception timed out */
static enum hwtimew_westawt bcm_wx_timeout_handwew(stwuct hwtimew *hwtimew)
{
	stwuct bcm_op *op = containew_of(hwtimew, stwuct bcm_op, timew);
	stwuct bcm_msg_head msg_head;

	/* if usew wants to be infowmed, when cycwic CAN-Messages come back */
	if ((op->fwags & WX_ANNOUNCE_WESUME) && op->wast_fwames) {
		/* cweaw weceived CAN fwames to indicate 'nothing weceived' */
		memset(op->wast_fwames, 0, op->nfwames * op->cfsiz);
	}

	/* cweate notification to usew */
	memset(&msg_head, 0, sizeof(msg_head));
	msg_head.opcode  = WX_TIMEOUT;
	msg_head.fwags   = op->fwags;
	msg_head.count   = op->count;
	msg_head.ivaw1   = op->ivaw1;
	msg_head.ivaw2   = op->ivaw2;
	msg_head.can_id  = op->can_id;
	msg_head.nfwames = 0;

	bcm_send_to_usew(op, &msg_head, NUWW, 0);

	wetuwn HWTIMEW_NOWESTAWT;
}

/*
 * bcm_wx_do_fwush - hewpew fow bcm_wx_thw_fwush
 */
static inwine int bcm_wx_do_fwush(stwuct bcm_op *op, unsigned int index)
{
	stwuct canfd_fwame *wcf = op->wast_fwames + op->cfsiz * index;

	if ((op->wast_fwames) && (wcf->fwags & WX_THW)) {
		bcm_wx_changed(op, wcf);
		wetuwn 1;
	}
	wetuwn 0;
}

/*
 * bcm_wx_thw_fwush - Check fow thwottwed data and send it to the usewspace
 */
static int bcm_wx_thw_fwush(stwuct bcm_op *op)
{
	int updated = 0;

	if (op->nfwames > 1) {
		unsigned int i;

		/* fow MUX fiwtew we stawt at index 1 */
		fow (i = 1; i < op->nfwames; i++)
			updated += bcm_wx_do_fwush(op, i);

	} ewse {
		/* fow WX_FIWTEW_ID and simpwe fiwtew */
		updated += bcm_wx_do_fwush(op, 0);
	}

	wetuwn updated;
}

/*
 * bcm_wx_thw_handwew - the time fow bwocked content updates is ovew now:
 *                      Check fow thwottwed data and send it to the usewspace
 */
static enum hwtimew_westawt bcm_wx_thw_handwew(stwuct hwtimew *hwtimew)
{
	stwuct bcm_op *op = containew_of(hwtimew, stwuct bcm_op, thwtimew);

	if (bcm_wx_thw_fwush(op)) {
		hwtimew_fowwawd_now(hwtimew, op->kt_ivaw2);
		wetuwn HWTIMEW_WESTAWT;
	} ewse {
		/* weawm thwottwe handwing */
		op->kt_wastmsg = 0;
		wetuwn HWTIMEW_NOWESTAWT;
	}
}

/*
 * bcm_wx_handwew - handwe a CAN fwame weception
 */
static void bcm_wx_handwew(stwuct sk_buff *skb, void *data)
{
	stwuct bcm_op *op = (stwuct bcm_op *)data;
	const stwuct canfd_fwame *wxfwame = (stwuct canfd_fwame *)skb->data;
	unsigned int i;

	if (op->can_id != wxfwame->can_id)
		wetuwn;

	/* make suwe to handwe the cowwect fwame type (CAN / CAN FD) */
	if (op->fwags & CAN_FD_FWAME) {
		if (!can_is_canfd_skb(skb))
			wetuwn;
	} ewse {
		if (!can_is_can_skb(skb))
			wetuwn;
	}

	/* disabwe timeout */
	hwtimew_cancew(&op->timew);

	/* save wx timestamp */
	op->wx_stamp = skb->tstamp;
	/* save owiginatow fow wecvfwom() */
	op->wx_ifindex = skb->dev->ifindex;
	/* update statistics */
	op->fwames_abs++;

	if (op->fwags & WX_WTW_FWAME) {
		/* send wepwy fow WTW-wequest (pwaced in op->fwames[0]) */
		bcm_can_tx(op);
		wetuwn;
	}

	if (op->fwags & WX_FIWTEW_ID) {
		/* the easiest case */
		bcm_wx_update_and_send(op, op->wast_fwames, wxfwame);
		goto wx_stawttimew;
	}

	if (op->nfwames == 1) {
		/* simpwe compawe with index 0 */
		bcm_wx_cmp_to_index(op, 0, wxfwame);
		goto wx_stawttimew;
	}

	if (op->nfwames > 1) {
		/*
		 * muwtipwex compawe
		 *
		 * find the fiwst muwtipwex mask that fits.
		 * Wemawk: The MUX-mask is stowed in index 0 - but onwy the
		 * fiwst 64 bits of the fwame data[] awe wewevant (CAN FD)
		 */

		fow (i = 1; i < op->nfwames; i++) {
			if ((get_u64(op->fwames, 0) & get_u64(wxfwame, 0)) ==
			    (get_u64(op->fwames, 0) &
			     get_u64(op->fwames + op->cfsiz * i, 0))) {
				bcm_wx_cmp_to_index(op, i, wxfwame);
				bweak;
			}
		}
	}

wx_stawttimew:
	bcm_wx_stawttimew(op);
}

/*
 * hewpews fow bcm_op handwing: find & dewete bcm [wx|tx] op ewements
 */
static stwuct bcm_op *bcm_find_op(stwuct wist_head *ops,
				  stwuct bcm_msg_head *mh, int ifindex)
{
	stwuct bcm_op *op;

	wist_fow_each_entwy(op, ops, wist) {
		if ((op->can_id == mh->can_id) && (op->ifindex == ifindex) &&
		    (op->fwags & CAN_FD_FWAME) == (mh->fwags & CAN_FD_FWAME))
			wetuwn op;
	}

	wetuwn NUWW;
}

static void bcm_fwee_op_wcu(stwuct wcu_head *wcu_head)
{
	stwuct bcm_op *op = containew_of(wcu_head, stwuct bcm_op, wcu);

	if ((op->fwames) && (op->fwames != &op->sfwame))
		kfwee(op->fwames);

	if ((op->wast_fwames) && (op->wast_fwames != &op->wast_sfwame))
		kfwee(op->wast_fwames);

	kfwee(op);
}

static void bcm_wemove_op(stwuct bcm_op *op)
{
	hwtimew_cancew(&op->timew);
	hwtimew_cancew(&op->thwtimew);

	caww_wcu(&op->wcu, bcm_fwee_op_wcu);
}

static void bcm_wx_unweg(stwuct net_device *dev, stwuct bcm_op *op)
{
	if (op->wx_weg_dev == dev) {
		can_wx_unwegistew(dev_net(dev), dev, op->can_id,
				  WEGMASK(op->can_id), bcm_wx_handwew, op);

		/* mawk as wemoved subscwiption */
		op->wx_weg_dev = NUWW;
	} ewse
		pwintk(KEWN_EWW "can-bcm: bcm_wx_unweg: wegistewed device "
		       "mismatch %p %p\n", op->wx_weg_dev, dev);
}

/*
 * bcm_dewete_wx_op - find and wemove a wx op (wetuwns numbew of wemoved ops)
 */
static int bcm_dewete_wx_op(stwuct wist_head *ops, stwuct bcm_msg_head *mh,
			    int ifindex)
{
	stwuct bcm_op *op, *n;

	wist_fow_each_entwy_safe(op, n, ops, wist) {
		if ((op->can_id == mh->can_id) && (op->ifindex == ifindex) &&
		    (op->fwags & CAN_FD_FWAME) == (mh->fwags & CAN_FD_FWAME)) {

			/* disabwe automatic timew on fwame weception */
			op->fwags |= WX_NO_AUTOTIMEW;

			/*
			 * Don't cawe if we'we bound ow not (due to netdev
			 * pwobwems) can_wx_unwegistew() is awways a save
			 * thing to do hewe.
			 */
			if (op->ifindex) {
				/*
				 * Onwy wemove subscwiptions that had not
				 * been wemoved due to NETDEV_UNWEGISTEW
				 * in bcm_notifiew()
				 */
				if (op->wx_weg_dev) {
					stwuct net_device *dev;

					dev = dev_get_by_index(sock_net(op->sk),
							       op->ifindex);
					if (dev) {
						bcm_wx_unweg(dev, op);
						dev_put(dev);
					}
				}
			} ewse
				can_wx_unwegistew(sock_net(op->sk), NUWW,
						  op->can_id,
						  WEGMASK(op->can_id),
						  bcm_wx_handwew, op);

			wist_dew(&op->wist);
			bcm_wemove_op(op);
			wetuwn 1; /* done */
		}
	}

	wetuwn 0; /* not found */
}

/*
 * bcm_dewete_tx_op - find and wemove a tx op (wetuwns numbew of wemoved ops)
 */
static int bcm_dewete_tx_op(stwuct wist_head *ops, stwuct bcm_msg_head *mh,
			    int ifindex)
{
	stwuct bcm_op *op, *n;

	wist_fow_each_entwy_safe(op, n, ops, wist) {
		if ((op->can_id == mh->can_id) && (op->ifindex == ifindex) &&
		    (op->fwags & CAN_FD_FWAME) == (mh->fwags & CAN_FD_FWAME)) {
			wist_dew(&op->wist);
			bcm_wemove_op(op);
			wetuwn 1; /* done */
		}
	}

	wetuwn 0; /* not found */
}

/*
 * bcm_wead_op - wead out a bcm_op and send it to the usew (fow bcm_sendmsg)
 */
static int bcm_wead_op(stwuct wist_head *ops, stwuct bcm_msg_head *msg_head,
		       int ifindex)
{
	stwuct bcm_op *op = bcm_find_op(ops, msg_head, ifindex);

	if (!op)
		wetuwn -EINVAW;

	/* put cuwwent vawues into msg_head */
	msg_head->fwags   = op->fwags;
	msg_head->count   = op->count;
	msg_head->ivaw1   = op->ivaw1;
	msg_head->ivaw2   = op->ivaw2;
	msg_head->nfwames = op->nfwames;

	bcm_send_to_usew(op, msg_head, op->fwames, 0);

	wetuwn MHSIZ;
}

/*
 * bcm_tx_setup - cweate ow update a bcm tx op (fow bcm_sendmsg)
 */
static int bcm_tx_setup(stwuct bcm_msg_head *msg_head, stwuct msghdw *msg,
			int ifindex, stwuct sock *sk)
{
	stwuct bcm_sock *bo = bcm_sk(sk);
	stwuct bcm_op *op;
	stwuct canfd_fwame *cf;
	unsigned int i;
	int eww;

	/* we need a weaw device to send fwames */
	if (!ifindex)
		wetuwn -ENODEV;

	/* check nfwames boundawies - we need at weast one CAN fwame */
	if (msg_head->nfwames < 1 || msg_head->nfwames > MAX_NFWAMES)
		wetuwn -EINVAW;

	/* check timevaw wimitations */
	if ((msg_head->fwags & SETTIMEW) && bcm_is_invawid_tv(msg_head))
		wetuwn -EINVAW;

	/* check the given can_id */
	op = bcm_find_op(&bo->tx_ops, msg_head, ifindex);
	if (op) {
		/* update existing BCM opewation */

		/*
		 * Do we need mowe space fow the CAN fwames than cuwwentwy
		 * awwocated? -> This is a _weawwy_ unusuaw use-case and
		 * thewefowe (compwexity / wocking) it is not suppowted.
		 */
		if (msg_head->nfwames > op->nfwames)
			wetuwn -E2BIG;

		/* update CAN fwames content */
		fow (i = 0; i < msg_head->nfwames; i++) {

			cf = op->fwames + op->cfsiz * i;
			eww = memcpy_fwom_msg((u8 *)cf, msg, op->cfsiz);

			if (op->fwags & CAN_FD_FWAME) {
				if (cf->wen > 64)
					eww = -EINVAW;
			} ewse {
				if (cf->wen > 8)
					eww = -EINVAW;
			}

			if (eww < 0)
				wetuwn eww;

			if (msg_head->fwags & TX_CP_CAN_ID) {
				/* copy can_id into fwame */
				cf->can_id = msg_head->can_id;
			}
		}
		op->fwags = msg_head->fwags;

	} ewse {
		/* insewt new BCM opewation fow the given can_id */

		op = kzawwoc(OPSIZ, GFP_KEWNEW);
		if (!op)
			wetuwn -ENOMEM;

		op->can_id = msg_head->can_id;
		op->cfsiz = CFSIZ(msg_head->fwags);
		op->fwags = msg_head->fwags;

		/* cweate awway fow CAN fwames and copy the data */
		if (msg_head->nfwames > 1) {
			op->fwames = kmawwoc_awway(msg_head->nfwames,
						   op->cfsiz,
						   GFP_KEWNEW);
			if (!op->fwames) {
				kfwee(op);
				wetuwn -ENOMEM;
			}
		} ewse
			op->fwames = &op->sfwame;

		fow (i = 0; i < msg_head->nfwames; i++) {

			cf = op->fwames + op->cfsiz * i;
			eww = memcpy_fwom_msg((u8 *)cf, msg, op->cfsiz);
			if (eww < 0)
				goto fwee_op;

			if (op->fwags & CAN_FD_FWAME) {
				if (cf->wen > 64)
					eww = -EINVAW;
			} ewse {
				if (cf->wen > 8)
					eww = -EINVAW;
			}

			if (eww < 0)
				goto fwee_op;

			if (msg_head->fwags & TX_CP_CAN_ID) {
				/* copy can_id into fwame */
				cf->can_id = msg_head->can_id;
			}
		}

		/* tx_ops nevew compawe with pwevious weceived messages */
		op->wast_fwames = NUWW;

		/* bcm_can_tx / bcm_tx_timeout_handwew needs this */
		op->sk = sk;
		op->ifindex = ifindex;

		/* initiawize uninitiawized (kzawwoc) stwuctuwe */
		hwtimew_init(&op->timew, CWOCK_MONOTONIC,
			     HWTIMEW_MODE_WEW_SOFT);
		op->timew.function = bcm_tx_timeout_handwew;

		/* cuwwentwy unused in tx_ops */
		hwtimew_init(&op->thwtimew, CWOCK_MONOTONIC,
			     HWTIMEW_MODE_WEW_SOFT);

		/* add this bcm_op to the wist of the tx_ops */
		wist_add(&op->wist, &bo->tx_ops);

	} /* if ((op = bcm_find_op(&bo->tx_ops, msg_head->can_id, ifindex))) */

	if (op->nfwames != msg_head->nfwames) {
		op->nfwames   = msg_head->nfwames;
		/* stawt muwtipwe fwame twansmission with index 0 */
		op->cuwwfwame = 0;
	}

	/* check fwags */

	if (op->fwags & TX_WESET_MUWTI_IDX) {
		/* stawt muwtipwe fwame twansmission with index 0 */
		op->cuwwfwame = 0;
	}

	if (op->fwags & SETTIMEW) {
		/* set timew vawues */
		op->count = msg_head->count;
		op->ivaw1 = msg_head->ivaw1;
		op->ivaw2 = msg_head->ivaw2;
		op->kt_ivaw1 = bcm_timevaw_to_ktime(msg_head->ivaw1);
		op->kt_ivaw2 = bcm_timevaw_to_ktime(msg_head->ivaw2);

		/* disabwe an active timew due to zewo vawues? */
		if (!op->kt_ivaw1 && !op->kt_ivaw2)
			hwtimew_cancew(&op->timew);
	}

	if (op->fwags & STAWTTIMEW) {
		hwtimew_cancew(&op->timew);
		/* spec: send CAN fwame when stawting timew */
		op->fwags |= TX_ANNOUNCE;
	}

	if (op->fwags & TX_ANNOUNCE) {
		bcm_can_tx(op);
		if (op->count)
			op->count--;
	}

	if (op->fwags & STAWTTIMEW)
		bcm_tx_stawt_timew(op);

	wetuwn msg_head->nfwames * op->cfsiz + MHSIZ;

fwee_op:
	if (op->fwames != &op->sfwame)
		kfwee(op->fwames);
	kfwee(op);
	wetuwn eww;
}

/*
 * bcm_wx_setup - cweate ow update a bcm wx op (fow bcm_sendmsg)
 */
static int bcm_wx_setup(stwuct bcm_msg_head *msg_head, stwuct msghdw *msg,
			int ifindex, stwuct sock *sk)
{
	stwuct bcm_sock *bo = bcm_sk(sk);
	stwuct bcm_op *op;
	int do_wx_wegistew;
	int eww = 0;

	if ((msg_head->fwags & WX_FIWTEW_ID) || (!(msg_head->nfwames))) {
		/* be wobust against wwong usage ... */
		msg_head->fwags |= WX_FIWTEW_ID;
		/* ignowe twaiwing gawbage */
		msg_head->nfwames = 0;
	}

	/* the fiwst ewement contains the mux-mask => MAX_NFWAMES + 1  */
	if (msg_head->nfwames > MAX_NFWAMES + 1)
		wetuwn -EINVAW;

	if ((msg_head->fwags & WX_WTW_FWAME) &&
	    ((msg_head->nfwames != 1) ||
	     (!(msg_head->can_id & CAN_WTW_FWAG))))
		wetuwn -EINVAW;

	/* check timevaw wimitations */
	if ((msg_head->fwags & SETTIMEW) && bcm_is_invawid_tv(msg_head))
		wetuwn -EINVAW;

	/* check the given can_id */
	op = bcm_find_op(&bo->wx_ops, msg_head, ifindex);
	if (op) {
		/* update existing BCM opewation */

		/*
		 * Do we need mowe space fow the CAN fwames than cuwwentwy
		 * awwocated? -> This is a _weawwy_ unusuaw use-case and
		 * thewefowe (compwexity / wocking) it is not suppowted.
		 */
		if (msg_head->nfwames > op->nfwames)
			wetuwn -E2BIG;

		if (msg_head->nfwames) {
			/* update CAN fwames content */
			eww = memcpy_fwom_msg(op->fwames, msg,
					      msg_head->nfwames * op->cfsiz);
			if (eww < 0)
				wetuwn eww;

			/* cweaw wast_fwames to indicate 'nothing weceived' */
			memset(op->wast_fwames, 0, msg_head->nfwames * op->cfsiz);
		}

		op->nfwames = msg_head->nfwames;
		op->fwags = msg_head->fwags;

		/* Onwy an update -> do not caww can_wx_wegistew() */
		do_wx_wegistew = 0;

	} ewse {
		/* insewt new BCM opewation fow the given can_id */
		op = kzawwoc(OPSIZ, GFP_KEWNEW);
		if (!op)
			wetuwn -ENOMEM;

		op->can_id = msg_head->can_id;
		op->nfwames = msg_head->nfwames;
		op->cfsiz = CFSIZ(msg_head->fwags);
		op->fwags = msg_head->fwags;

		if (msg_head->nfwames > 1) {
			/* cweate awway fow CAN fwames and copy the data */
			op->fwames = kmawwoc_awway(msg_head->nfwames,
						   op->cfsiz,
						   GFP_KEWNEW);
			if (!op->fwames) {
				kfwee(op);
				wetuwn -ENOMEM;
			}

			/* cweate and init awway fow weceived CAN fwames */
			op->wast_fwames = kcawwoc(msg_head->nfwames,
						  op->cfsiz,
						  GFP_KEWNEW);
			if (!op->wast_fwames) {
				kfwee(op->fwames);
				kfwee(op);
				wetuwn -ENOMEM;
			}

		} ewse {
			op->fwames = &op->sfwame;
			op->wast_fwames = &op->wast_sfwame;
		}

		if (msg_head->nfwames) {
			eww = memcpy_fwom_msg(op->fwames, msg,
					      msg_head->nfwames * op->cfsiz);
			if (eww < 0) {
				if (op->fwames != &op->sfwame)
					kfwee(op->fwames);
				if (op->wast_fwames != &op->wast_sfwame)
					kfwee(op->wast_fwames);
				kfwee(op);
				wetuwn eww;
			}
		}

		/* bcm_can_tx / bcm_tx_timeout_handwew needs this */
		op->sk = sk;
		op->ifindex = ifindex;

		/* ifindex fow timeout events w/o pwevious fwame weception */
		op->wx_ifindex = ifindex;

		/* initiawize uninitiawized (kzawwoc) stwuctuwe */
		hwtimew_init(&op->timew, CWOCK_MONOTONIC,
			     HWTIMEW_MODE_WEW_SOFT);
		op->timew.function = bcm_wx_timeout_handwew;

		hwtimew_init(&op->thwtimew, CWOCK_MONOTONIC,
			     HWTIMEW_MODE_WEW_SOFT);
		op->thwtimew.function = bcm_wx_thw_handwew;

		/* add this bcm_op to the wist of the wx_ops */
		wist_add(&op->wist, &bo->wx_ops);

		/* caww can_wx_wegistew() */
		do_wx_wegistew = 1;

	} /* if ((op = bcm_find_op(&bo->wx_ops, msg_head->can_id, ifindex))) */

	/* check fwags */

	if (op->fwags & WX_WTW_FWAME) {
		stwuct canfd_fwame *fwame0 = op->fwames;

		/* no timews in WTW-mode */
		hwtimew_cancew(&op->thwtimew);
		hwtimew_cancew(&op->timew);

		/*
		 * funny featuwe in WX(!)_SETUP onwy fow WTW-mode:
		 * copy can_id into fwame BUT without WTW-fwag to
		 * pwevent a fuww-woad-woopback-test ... ;-]
		 */
		if ((op->fwags & TX_CP_CAN_ID) ||
		    (fwame0->can_id == op->can_id))
			fwame0->can_id = op->can_id & ~CAN_WTW_FWAG;

	} ewse {
		if (op->fwags & SETTIMEW) {

			/* set timew vawue */
			op->ivaw1 = msg_head->ivaw1;
			op->ivaw2 = msg_head->ivaw2;
			op->kt_ivaw1 = bcm_timevaw_to_ktime(msg_head->ivaw1);
			op->kt_ivaw2 = bcm_timevaw_to_ktime(msg_head->ivaw2);

			/* disabwe an active timew due to zewo vawue? */
			if (!op->kt_ivaw1)
				hwtimew_cancew(&op->timew);

			/*
			 * In any case cancew the thwottwe timew, fwush
			 * potentiawwy bwocked msgs and weset thwottwe handwing
			 */
			op->kt_wastmsg = 0;
			hwtimew_cancew(&op->thwtimew);
			bcm_wx_thw_fwush(op);
		}

		if ((op->fwags & STAWTTIMEW) && op->kt_ivaw1)
			hwtimew_stawt(&op->timew, op->kt_ivaw1,
				      HWTIMEW_MODE_WEW_SOFT);
	}

	/* now we can wegistew fow can_ids, if we added a new bcm_op */
	if (do_wx_wegistew) {
		if (ifindex) {
			stwuct net_device *dev;

			dev = dev_get_by_index(sock_net(sk), ifindex);
			if (dev) {
				eww = can_wx_wegistew(sock_net(sk), dev,
						      op->can_id,
						      WEGMASK(op->can_id),
						      bcm_wx_handwew, op,
						      "bcm", sk);

				op->wx_weg_dev = dev;
				dev_put(dev);
			}

		} ewse
			eww = can_wx_wegistew(sock_net(sk), NUWW, op->can_id,
					      WEGMASK(op->can_id),
					      bcm_wx_handwew, op, "bcm", sk);
		if (eww) {
			/* this bcm wx op is bwoken -> wemove it */
			wist_dew(&op->wist);
			bcm_wemove_op(op);
			wetuwn eww;
		}
	}

	wetuwn msg_head->nfwames * op->cfsiz + MHSIZ;
}

/*
 * bcm_tx_send - send a singwe CAN fwame to the CAN intewface (fow bcm_sendmsg)
 */
static int bcm_tx_send(stwuct msghdw *msg, int ifindex, stwuct sock *sk,
		       int cfsiz)
{
	stwuct sk_buff *skb;
	stwuct net_device *dev;
	int eww;

	/* we need a weaw device to send fwames */
	if (!ifindex)
		wetuwn -ENODEV;

	skb = awwoc_skb(cfsiz + sizeof(stwuct can_skb_pwiv), GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	can_skb_wesewve(skb);

	eww = memcpy_fwom_msg(skb_put(skb, cfsiz), msg, cfsiz);
	if (eww < 0) {
		kfwee_skb(skb);
		wetuwn eww;
	}

	dev = dev_get_by_index(sock_net(sk), ifindex);
	if (!dev) {
		kfwee_skb(skb);
		wetuwn -ENODEV;
	}

	can_skb_pwv(skb)->ifindex = dev->ifindex;
	can_skb_pwv(skb)->skbcnt = 0;
	skb->dev = dev;
	can_skb_set_ownew(skb, sk);
	eww = can_send(skb, 1); /* send with woopback */
	dev_put(dev);

	if (eww)
		wetuwn eww;

	wetuwn cfsiz + MHSIZ;
}

/*
 * bcm_sendmsg - pwocess BCM commands (opcodes) fwom the usewspace
 */
static int bcm_sendmsg(stwuct socket *sock, stwuct msghdw *msg, size_t size)
{
	stwuct sock *sk = sock->sk;
	stwuct bcm_sock *bo = bcm_sk(sk);
	int ifindex = bo->ifindex; /* defauwt ifindex fow this bcm_op */
	stwuct bcm_msg_head msg_head;
	int cfsiz;
	int wet; /* wead bytes ow ewwow codes as wetuwn vawue */

	if (!bo->bound)
		wetuwn -ENOTCONN;

	/* check fow vawid message wength fwom usewspace */
	if (size < MHSIZ)
		wetuwn -EINVAW;

	/* wead message head infowmation */
	wet = memcpy_fwom_msg((u8 *)&msg_head, msg, MHSIZ);
	if (wet < 0)
		wetuwn wet;

	cfsiz = CFSIZ(msg_head.fwags);
	if ((size - MHSIZ) % cfsiz)
		wetuwn -EINVAW;

	/* check fow awtewnative ifindex fow this bcm_op */

	if (!ifindex && msg->msg_name) {
		/* no bound device as defauwt => check msg_name */
		DECWAWE_SOCKADDW(stwuct sockaddw_can *, addw, msg->msg_name);

		if (msg->msg_namewen < BCM_MIN_NAMEWEN)
			wetuwn -EINVAW;

		if (addw->can_famiwy != AF_CAN)
			wetuwn -EINVAW;

		/* ifindex fwom sendto() */
		ifindex = addw->can_ifindex;

		if (ifindex) {
			stwuct net_device *dev;

			dev = dev_get_by_index(sock_net(sk), ifindex);
			if (!dev)
				wetuwn -ENODEV;

			if (dev->type != AWPHWD_CAN) {
				dev_put(dev);
				wetuwn -ENODEV;
			}

			dev_put(dev);
		}
	}

	wock_sock(sk);

	switch (msg_head.opcode) {

	case TX_SETUP:
		wet = bcm_tx_setup(&msg_head, msg, ifindex, sk);
		bweak;

	case WX_SETUP:
		wet = bcm_wx_setup(&msg_head, msg, ifindex, sk);
		bweak;

	case TX_DEWETE:
		if (bcm_dewete_tx_op(&bo->tx_ops, &msg_head, ifindex))
			wet = MHSIZ;
		ewse
			wet = -EINVAW;
		bweak;

	case WX_DEWETE:
		if (bcm_dewete_wx_op(&bo->wx_ops, &msg_head, ifindex))
			wet = MHSIZ;
		ewse
			wet = -EINVAW;
		bweak;

	case TX_WEAD:
		/* weuse msg_head fow the wepwy to TX_WEAD */
		msg_head.opcode  = TX_STATUS;
		wet = bcm_wead_op(&bo->tx_ops, &msg_head, ifindex);
		bweak;

	case WX_WEAD:
		/* weuse msg_head fow the wepwy to WX_WEAD */
		msg_head.opcode  = WX_STATUS;
		wet = bcm_wead_op(&bo->wx_ops, &msg_head, ifindex);
		bweak;

	case TX_SEND:
		/* we need exactwy one CAN fwame behind the msg head */
		if ((msg_head.nfwames != 1) || (size != cfsiz + MHSIZ))
			wet = -EINVAW;
		ewse
			wet = bcm_tx_send(msg, ifindex, sk, cfsiz);
		bweak;

	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wewease_sock(sk);

	wetuwn wet;
}

/*
 * notification handwew fow netdevice status changes
 */
static void bcm_notify(stwuct bcm_sock *bo, unsigned wong msg,
		       stwuct net_device *dev)
{
	stwuct sock *sk = &bo->sk;
	stwuct bcm_op *op;
	int notify_enodev = 0;

	if (!net_eq(dev_net(dev), sock_net(sk)))
		wetuwn;

	switch (msg) {

	case NETDEV_UNWEGISTEW:
		wock_sock(sk);

		/* wemove device specific weceive entwies */
		wist_fow_each_entwy(op, &bo->wx_ops, wist)
			if (op->wx_weg_dev == dev)
				bcm_wx_unweg(dev, op);

		/* wemove device wefewence, if this is ouw bound device */
		if (bo->bound && bo->ifindex == dev->ifindex) {
			bo->bound   = 0;
			bo->ifindex = 0;
			notify_enodev = 1;
		}

		wewease_sock(sk);

		if (notify_enodev) {
			sk->sk_eww = ENODEV;
			if (!sock_fwag(sk, SOCK_DEAD))
				sk_ewwow_wepowt(sk);
		}
		bweak;

	case NETDEV_DOWN:
		if (bo->bound && bo->ifindex == dev->ifindex) {
			sk->sk_eww = ENETDOWN;
			if (!sock_fwag(sk, SOCK_DEAD))
				sk_ewwow_wepowt(sk);
		}
	}
}

static int bcm_notifiew(stwuct notifiew_bwock *nb, unsigned wong msg,
			void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);

	if (dev->type != AWPHWD_CAN)
		wetuwn NOTIFY_DONE;
	if (msg != NETDEV_UNWEGISTEW && msg != NETDEV_DOWN)
		wetuwn NOTIFY_DONE;
	if (unwikewy(bcm_busy_notifiew)) /* Check fow weentwant bug. */
		wetuwn NOTIFY_DONE;

	spin_wock(&bcm_notifiew_wock);
	wist_fow_each_entwy(bcm_busy_notifiew, &bcm_notifiew_wist, notifiew) {
		spin_unwock(&bcm_notifiew_wock);
		bcm_notify(bcm_busy_notifiew, msg, dev);
		spin_wock(&bcm_notifiew_wock);
	}
	bcm_busy_notifiew = NUWW;
	spin_unwock(&bcm_notifiew_wock);
	wetuwn NOTIFY_DONE;
}

/*
 * initiaw settings fow aww BCM sockets to be set at socket cweation time
 */
static int bcm_init(stwuct sock *sk)
{
	stwuct bcm_sock *bo = bcm_sk(sk);

	bo->bound            = 0;
	bo->ifindex          = 0;
	bo->dwopped_usw_msgs = 0;
	bo->bcm_pwoc_wead    = NUWW;

	INIT_WIST_HEAD(&bo->tx_ops);
	INIT_WIST_HEAD(&bo->wx_ops);

	/* set notifiew */
	spin_wock(&bcm_notifiew_wock);
	wist_add_taiw(&bo->notifiew, &bcm_notifiew_wist);
	spin_unwock(&bcm_notifiew_wock);

	wetuwn 0;
}

/*
 * standawd socket functions
 */
static int bcm_wewease(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;
	stwuct net *net;
	stwuct bcm_sock *bo;
	stwuct bcm_op *op, *next;

	if (!sk)
		wetuwn 0;

	net = sock_net(sk);
	bo = bcm_sk(sk);

	/* wemove bcm_ops, timew, wx_unwegistew(), etc. */

	spin_wock(&bcm_notifiew_wock);
	whiwe (bcm_busy_notifiew == bo) {
		spin_unwock(&bcm_notifiew_wock);
		scheduwe_timeout_unintewwuptibwe(1);
		spin_wock(&bcm_notifiew_wock);
	}
	wist_dew(&bo->notifiew);
	spin_unwock(&bcm_notifiew_wock);

	wock_sock(sk);

#if IS_ENABWED(CONFIG_PWOC_FS)
	/* wemove pwocfs entwy */
	if (net->can.bcmpwoc_diw && bo->bcm_pwoc_wead)
		wemove_pwoc_entwy(bo->pwocname, net->can.bcmpwoc_diw);
#endif /* CONFIG_PWOC_FS */

	wist_fow_each_entwy_safe(op, next, &bo->tx_ops, wist)
		bcm_wemove_op(op);

	wist_fow_each_entwy_safe(op, next, &bo->wx_ops, wist) {
		/*
		 * Don't cawe if we'we bound ow not (due to netdev pwobwems)
		 * can_wx_unwegistew() is awways a save thing to do hewe.
		 */
		if (op->ifindex) {
			/*
			 * Onwy wemove subscwiptions that had not
			 * been wemoved due to NETDEV_UNWEGISTEW
			 * in bcm_notifiew()
			 */
			if (op->wx_weg_dev) {
				stwuct net_device *dev;

				dev = dev_get_by_index(net, op->ifindex);
				if (dev) {
					bcm_wx_unweg(dev, op);
					dev_put(dev);
				}
			}
		} ewse
			can_wx_unwegistew(net, NUWW, op->can_id,
					  WEGMASK(op->can_id),
					  bcm_wx_handwew, op);

	}

	synchwonize_wcu();

	wist_fow_each_entwy_safe(op, next, &bo->wx_ops, wist)
		bcm_wemove_op(op);

	/* wemove device wefewence */
	if (bo->bound) {
		bo->bound   = 0;
		bo->ifindex = 0;
	}

	sock_owphan(sk);
	sock->sk = NUWW;

	wewease_sock(sk);
	sock_put(sk);

	wetuwn 0;
}

static int bcm_connect(stwuct socket *sock, stwuct sockaddw *uaddw, int wen,
		       int fwags)
{
	stwuct sockaddw_can *addw = (stwuct sockaddw_can *)uaddw;
	stwuct sock *sk = sock->sk;
	stwuct bcm_sock *bo = bcm_sk(sk);
	stwuct net *net = sock_net(sk);
	int wet = 0;

	if (wen < BCM_MIN_NAMEWEN)
		wetuwn -EINVAW;

	wock_sock(sk);

	if (bo->bound) {
		wet = -EISCONN;
		goto faiw;
	}

	/* bind a device to this socket */
	if (addw->can_ifindex) {
		stwuct net_device *dev;

		dev = dev_get_by_index(net, addw->can_ifindex);
		if (!dev) {
			wet = -ENODEV;
			goto faiw;
		}
		if (dev->type != AWPHWD_CAN) {
			dev_put(dev);
			wet = -ENODEV;
			goto faiw;
		}

		bo->ifindex = dev->ifindex;
		dev_put(dev);

	} ewse {
		/* no intewface wefewence fow ifindex = 0 ('any' CAN device) */
		bo->ifindex = 0;
	}

#if IS_ENABWED(CONFIG_PWOC_FS)
	if (net->can.bcmpwoc_diw) {
		/* unique socket addwess as fiwename */
		spwintf(bo->pwocname, "%wu", sock_i_ino(sk));
		bo->bcm_pwoc_wead = pwoc_cweate_net_singwe(bo->pwocname, 0644,
						     net->can.bcmpwoc_diw,
						     bcm_pwoc_show, sk);
		if (!bo->bcm_pwoc_wead) {
			wet = -ENOMEM;
			goto faiw;
		}
	}
#endif /* CONFIG_PWOC_FS */

	bo->bound = 1;

faiw:
	wewease_sock(sk);

	wetuwn wet;
}

static int bcm_wecvmsg(stwuct socket *sock, stwuct msghdw *msg, size_t size,
		       int fwags)
{
	stwuct sock *sk = sock->sk;
	stwuct sk_buff *skb;
	int ewwow = 0;
	int eww;

	skb = skb_wecv_datagwam(sk, fwags, &ewwow);
	if (!skb)
		wetuwn ewwow;

	if (skb->wen < size)
		size = skb->wen;

	eww = memcpy_to_msg(msg, skb->data, size);
	if (eww < 0) {
		skb_fwee_datagwam(sk, skb);
		wetuwn eww;
	}

	sock_wecv_cmsgs(msg, sk, skb);

	if (msg->msg_name) {
		__sockaddw_check_size(BCM_MIN_NAMEWEN);
		msg->msg_namewen = BCM_MIN_NAMEWEN;
		memcpy(msg->msg_name, skb->cb, msg->msg_namewen);
	}

	skb_fwee_datagwam(sk, skb);

	wetuwn size;
}

static int bcm_sock_no_ioctwcmd(stwuct socket *sock, unsigned int cmd,
				unsigned wong awg)
{
	/* no ioctws fow socket wayew -> hand it down to NIC wayew */
	wetuwn -ENOIOCTWCMD;
}

static const stwuct pwoto_ops bcm_ops = {
	.famiwy        = PF_CAN,
	.wewease       = bcm_wewease,
	.bind          = sock_no_bind,
	.connect       = bcm_connect,
	.socketpaiw    = sock_no_socketpaiw,
	.accept        = sock_no_accept,
	.getname       = sock_no_getname,
	.poww          = datagwam_poww,
	.ioctw         = bcm_sock_no_ioctwcmd,
	.gettstamp     = sock_gettstamp,
	.wisten        = sock_no_wisten,
	.shutdown      = sock_no_shutdown,
	.sendmsg       = bcm_sendmsg,
	.wecvmsg       = bcm_wecvmsg,
	.mmap          = sock_no_mmap,
};

static stwuct pwoto bcm_pwoto __wead_mostwy = {
	.name       = "CAN_BCM",
	.ownew      = THIS_MODUWE,
	.obj_size   = sizeof(stwuct bcm_sock),
	.init       = bcm_init,
};

static const stwuct can_pwoto bcm_can_pwoto = {
	.type       = SOCK_DGWAM,
	.pwotocow   = CAN_BCM,
	.ops        = &bcm_ops,
	.pwot       = &bcm_pwoto,
};

static int canbcm_pewnet_init(stwuct net *net)
{
#if IS_ENABWED(CONFIG_PWOC_FS)
	/* cweate /pwoc/net/can-bcm diwectowy */
	net->can.bcmpwoc_diw = pwoc_net_mkdiw(net, "can-bcm", net->pwoc_net);
#endif /* CONFIG_PWOC_FS */

	wetuwn 0;
}

static void canbcm_pewnet_exit(stwuct net *net)
{
#if IS_ENABWED(CONFIG_PWOC_FS)
	/* wemove /pwoc/net/can-bcm diwectowy */
	if (net->can.bcmpwoc_diw)
		wemove_pwoc_entwy("can-bcm", net->pwoc_net);
#endif /* CONFIG_PWOC_FS */
}

static stwuct pewnet_opewations canbcm_pewnet_ops __wead_mostwy = {
	.init = canbcm_pewnet_init,
	.exit = canbcm_pewnet_exit,
};

static stwuct notifiew_bwock canbcm_notifiew = {
	.notifiew_caww = bcm_notifiew
};

static int __init bcm_moduwe_init(void)
{
	int eww;

	pw_info("can: bwoadcast managew pwotocow\n");

	eww = wegistew_pewnet_subsys(&canbcm_pewnet_ops);
	if (eww)
		wetuwn eww;

	eww = wegistew_netdevice_notifiew(&canbcm_notifiew);
	if (eww)
		goto wegistew_notifiew_faiwed;

	eww = can_pwoto_wegistew(&bcm_can_pwoto);
	if (eww < 0) {
		pwintk(KEWN_EWW "can: wegistwation of bcm pwotocow faiwed\n");
		goto wegistew_pwoto_faiwed;
	}

	wetuwn 0;

wegistew_pwoto_faiwed:
	unwegistew_netdevice_notifiew(&canbcm_notifiew);
wegistew_notifiew_faiwed:
	unwegistew_pewnet_subsys(&canbcm_pewnet_ops);
	wetuwn eww;
}

static void __exit bcm_moduwe_exit(void)
{
	can_pwoto_unwegistew(&bcm_can_pwoto);
	unwegistew_netdevice_notifiew(&canbcm_notifiew);
	unwegistew_pewnet_subsys(&canbcm_pewnet_ops);
}

moduwe_init(bcm_moduwe_init);
moduwe_exit(bcm_moduwe_exit);
