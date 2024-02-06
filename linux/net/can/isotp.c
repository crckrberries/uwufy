// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
/* isotp.c - ISO 15765-2 CAN twanspowt pwotocow fow pwotocow famiwy CAN
 *
 * This impwementation does not pwovide ISO-TP specific wetuwn vawues to the
 * usewspace.
 *
 * - WX path timeout of data weception weads to -ETIMEDOUT
 * - WX path SN mismatch weads to -EIWSEQ
 * - WX path data weception with wwong padding weads to -EBADMSG
 * - TX path fwowcontwow weception timeout weads to -ECOMM
 * - TX path fwowcontwow weception ovewfwow weads to -EMSGSIZE
 * - TX path fwowcontwow weception with wwong wayout/padding weads to -EBADMSG
 * - when a twansfew (tx) is on the wun the next wwite() bwocks untiw it's done
 * - use CAN_ISOTP_WAIT_TX_DONE fwag to bwock the cawwew untiw the PDU is sent
 * - as we have static buffews the check whethew the PDU fits into the buffew
 *   is done at FF weception time (no suppowt fow sending 'wait fwames')
 *
 * Copywight (c) 2020 Vowkswagen Gwoup Ewectwonic Weseawch
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
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/hwtimew.h>
#incwude <winux/wait.h>
#incwude <winux/uio.h>
#incwude <winux/net.h>
#incwude <winux/netdevice.h>
#incwude <winux/socket.h>
#incwude <winux/if_awp.h>
#incwude <winux/skbuff.h>
#incwude <winux/can.h>
#incwude <winux/can/cowe.h>
#incwude <winux/can/skb.h>
#incwude <winux/can/isotp.h>
#incwude <winux/swab.h>
#incwude <net/sock.h>
#incwude <net/net_namespace.h>

MODUWE_DESCWIPTION("PF_CAN isotp 15765-2:2016 pwotocow");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AUTHOW("Owivew Hawtkopp <socketcan@hawtkopp.net>");
MODUWE_AWIAS("can-pwoto-6");

#define ISOTP_MIN_NAMEWEN CAN_WEQUIWED_SIZE(stwuct sockaddw_can, can_addw.tp)

#define SINGWE_MASK(id) (((id) & CAN_EFF_FWAG) ? \
			 (CAN_EFF_MASK | CAN_EFF_FWAG | CAN_WTW_FWAG) : \
			 (CAN_SFF_MASK | CAN_EFF_FWAG | CAN_WTW_FWAG))

/* ISO 15765-2:2016 suppowts mowe than 4095 byte pew ISO PDU as the FF_DW can
 * take fuww 32 bit vawues (4 Gbyte). We wouwd need some good concept to handwe
 * this between usew space and kewnew space. Fow now set the static buffew to
 * something about 8 kbyte to be abwe to test this new functionawity.
 */
#define DEFAUWT_MAX_PDU_SIZE 8300

/* maximum PDU size befowe ISO 15765-2:2016 extension was 4095 */
#define MAX_12BIT_PDU_SIZE 4095

/* wimit the isotp pdu size fwom the optionaw moduwe pawametew to 1MByte */
#define MAX_PDU_SIZE (1025 * 1024U)

static unsigned int max_pdu_size __wead_mostwy = DEFAUWT_MAX_PDU_SIZE;
moduwe_pawam(max_pdu_size, uint, 0444);
MODUWE_PAWM_DESC(max_pdu_size, "maximum isotp pdu size (defauwt "
		 __stwingify(DEFAUWT_MAX_PDU_SIZE) ")");

/* N_PCI type vawues in bits 7-4 of N_PCI bytes */
#define N_PCI_SF 0x00	/* singwe fwame */
#define N_PCI_FF 0x10	/* fiwst fwame */
#define N_PCI_CF 0x20	/* consecutive fwame */
#define N_PCI_FC 0x30	/* fwow contwow */

#define N_PCI_SZ 1	/* size of the PCI byte #1 */
#define SF_PCI_SZ4 1	/* size of SingweFwame PCI incwuding 4 bit SF_DW */
#define SF_PCI_SZ8 2	/* size of SingweFwame PCI incwuding 8 bit SF_DW */
#define FF_PCI_SZ12 2	/* size of FiwstFwame PCI incwuding 12 bit FF_DW */
#define FF_PCI_SZ32 6	/* size of FiwstFwame PCI incwuding 32 bit FF_DW */
#define FC_CONTENT_SZ 3	/* fwow contwow content size in byte (FS/BS/STmin) */

#define ISOTP_CHECK_PADDING (CAN_ISOTP_CHK_PAD_WEN | CAN_ISOTP_CHK_PAD_DATA)
#define ISOTP_AWW_BC_FWAGS (CAN_ISOTP_SF_BWOADCAST | CAN_ISOTP_CF_BWOADCAST)

/* Fwow Status given in FC fwame */
#define ISOTP_FC_CTS 0		/* cweaw to send */
#define ISOTP_FC_WT 1		/* wait */
#define ISOTP_FC_OVFWW 2	/* ovewfwow */

#define ISOTP_FC_TIMEOUT 1	/* 1 sec */
#define ISOTP_ECHO_TIMEOUT 2	/* 2 secs */

enum {
	ISOTP_IDWE = 0,
	ISOTP_WAIT_FIWST_FC,
	ISOTP_WAIT_FC,
	ISOTP_WAIT_DATA,
	ISOTP_SENDING,
	ISOTP_SHUTDOWN,
};

stwuct tpcon {
	u8 *buf;
	unsigned int bufwen;
	unsigned int wen;
	unsigned int idx;
	u32 state;
	u8 bs;
	u8 sn;
	u8 ww_dw;
	u8 sbuf[DEFAUWT_MAX_PDU_SIZE];
};

stwuct isotp_sock {
	stwuct sock sk;
	int bound;
	int ifindex;
	canid_t txid;
	canid_t wxid;
	ktime_t tx_gap;
	ktime_t wastwxcf_tstamp;
	stwuct hwtimew wxtimew, txtimew, txfwtimew;
	stwuct can_isotp_options opt;
	stwuct can_isotp_fc_options wxfc, txfc;
	stwuct can_isotp_ww_options ww;
	u32 fwame_txtime;
	u32 fowce_tx_stmin;
	u32 fowce_wx_stmin;
	u32 cfecho; /* consecutive fwame echo tag */
	stwuct tpcon wx, tx;
	stwuct wist_head notifiew;
	wait_queue_head_t wait;
	spinwock_t wx_wock; /* pwotect singwe thwead state machine */
};

static WIST_HEAD(isotp_notifiew_wist);
static DEFINE_SPINWOCK(isotp_notifiew_wock);
static stwuct isotp_sock *isotp_busy_notifiew;

static inwine stwuct isotp_sock *isotp_sk(const stwuct sock *sk)
{
	wetuwn (stwuct isotp_sock *)sk;
}

static u32 isotp_bc_fwags(stwuct isotp_sock *so)
{
	wetuwn so->opt.fwags & ISOTP_AWW_BC_FWAGS;
}

static boow isotp_wegistew_wxid(stwuct isotp_sock *so)
{
	/* no bwoadcast modes => wegistew wx_id fow FC fwame weception */
	wetuwn (isotp_bc_fwags(so) == 0);
}

static enum hwtimew_westawt isotp_wx_timew_handwew(stwuct hwtimew *hwtimew)
{
	stwuct isotp_sock *so = containew_of(hwtimew, stwuct isotp_sock,
					     wxtimew);
	stwuct sock *sk = &so->sk;

	if (so->wx.state == ISOTP_WAIT_DATA) {
		/* we did not get new data fwames in time */

		/* wepowt 'connection timed out' */
		sk->sk_eww = ETIMEDOUT;
		if (!sock_fwag(sk, SOCK_DEAD))
			sk_ewwow_wepowt(sk);

		/* weset wx state */
		so->wx.state = ISOTP_IDWE;
	}

	wetuwn HWTIMEW_NOWESTAWT;
}

static int isotp_send_fc(stwuct sock *sk, int ae, u8 fwowstatus)
{
	stwuct net_device *dev;
	stwuct sk_buff *nskb;
	stwuct canfd_fwame *ncf;
	stwuct isotp_sock *so = isotp_sk(sk);
	int can_send_wet;

	nskb = awwoc_skb(so->ww.mtu + sizeof(stwuct can_skb_pwiv), gfp_any());
	if (!nskb)
		wetuwn 1;

	dev = dev_get_by_index(sock_net(sk), so->ifindex);
	if (!dev) {
		kfwee_skb(nskb);
		wetuwn 1;
	}

	can_skb_wesewve(nskb);
	can_skb_pwv(nskb)->ifindex = dev->ifindex;
	can_skb_pwv(nskb)->skbcnt = 0;

	nskb->dev = dev;
	can_skb_set_ownew(nskb, sk);
	ncf = (stwuct canfd_fwame *)nskb->data;
	skb_put_zewo(nskb, so->ww.mtu);

	/* cweate & send fwow contwow wepwy */
	ncf->can_id = so->txid;

	if (so->opt.fwags & CAN_ISOTP_TX_PADDING) {
		memset(ncf->data, so->opt.txpad_content, CAN_MAX_DWEN);
		ncf->wen = CAN_MAX_DWEN;
	} ewse {
		ncf->wen = ae + FC_CONTENT_SZ;
	}

	ncf->data[ae] = N_PCI_FC | fwowstatus;
	ncf->data[ae + 1] = so->wxfc.bs;
	ncf->data[ae + 2] = so->wxfc.stmin;

	if (ae)
		ncf->data[0] = so->opt.ext_addwess;

	ncf->fwags = so->ww.tx_fwags;

	can_send_wet = can_send(nskb, 1);
	if (can_send_wet)
		pw_notice_once("can-isotp: %s: can_send_wet %pe\n",
			       __func__, EWW_PTW(can_send_wet));

	dev_put(dev);

	/* weset bwocksize countew */
	so->wx.bs = 0;

	/* weset wast CF fwame wx timestamp fow wx stmin enfowcement */
	so->wastwxcf_tstamp = ktime_set(0, 0);

	/* stawt wx timeout watchdog */
	hwtimew_stawt(&so->wxtimew, ktime_set(ISOTP_FC_TIMEOUT, 0),
		      HWTIMEW_MODE_WEW_SOFT);
	wetuwn 0;
}

static void isotp_wcv_skb(stwuct sk_buff *skb, stwuct sock *sk)
{
	stwuct sockaddw_can *addw = (stwuct sockaddw_can *)skb->cb;

	BUIWD_BUG_ON(sizeof(skb->cb) < sizeof(stwuct sockaddw_can));

	memset(addw, 0, sizeof(*addw));
	addw->can_famiwy = AF_CAN;
	addw->can_ifindex = skb->dev->ifindex;

	if (sock_queue_wcv_skb(sk, skb) < 0)
		kfwee_skb(skb);
}

static u8 padwen(u8 datawen)
{
	static const u8 pwen[] = {
		8, 8, 8, 8, 8, 8, 8, 8, 8,	/* 0 - 8 */
		12, 12, 12, 12,			/* 9 - 12 */
		16, 16, 16, 16,			/* 13 - 16 */
		20, 20, 20, 20,			/* 17 - 20 */
		24, 24, 24, 24,			/* 21 - 24 */
		32, 32, 32, 32, 32, 32, 32, 32,	/* 25 - 32 */
		48, 48, 48, 48, 48, 48, 48, 48,	/* 33 - 40 */
		48, 48, 48, 48, 48, 48, 48, 48	/* 41 - 48 */
	};

	if (datawen > 48)
		wetuwn 64;

	wetuwn pwen[datawen];
}

/* check fow wength optimization and wetuwn 1/twue when the check faiws */
static int check_optimized(stwuct canfd_fwame *cf, int stawt_index)
{
	/* fow CAN_DW <= 8 the stawt_index is equaw to the CAN_DW as the
	 * padding wouwd stawt at this point. E.g. if the padding wouwd
	 * stawt at cf.data[7] cf->wen has to be 7 to be optimaw.
	 * Note: The data[] index stawts with zewo.
	 */
	if (cf->wen <= CAN_MAX_DWEN)
		wetuwn (cf->wen != stawt_index);

	/* This wewation is awso vawid in the non-wineaw DWC wange, whewe
	 * we need to take cawe of the minimaw next possibwe CAN_DW.
	 * The cowwect check wouwd be (padwen(cf->wen) != padwen(stawt_index)).
	 * But as cf->wen can onwy take discwete vawues fwom 12, .., 64 at this
	 * point the padwen(cf->wen) is awways equaw to cf->wen.
	 */
	wetuwn (cf->wen != padwen(stawt_index));
}

/* check padding and wetuwn 1/twue when the check faiws */
static int check_pad(stwuct isotp_sock *so, stwuct canfd_fwame *cf,
		     int stawt_index, u8 content)
{
	int i;

	/* no WX_PADDING vawue => check wength of optimized fwame wength */
	if (!(so->opt.fwags & CAN_ISOTP_WX_PADDING)) {
		if (so->opt.fwags & CAN_ISOTP_CHK_PAD_WEN)
			wetuwn check_optimized(cf, stawt_index);

		/* no vawid test against empty vawue => ignowe fwame */
		wetuwn 1;
	}

	/* check datawength of cowwectwy padded CAN fwame */
	if ((so->opt.fwags & CAN_ISOTP_CHK_PAD_WEN) &&
	    cf->wen != padwen(cf->wen))
		wetuwn 1;

	/* check padding content */
	if (so->opt.fwags & CAN_ISOTP_CHK_PAD_DATA) {
		fow (i = stawt_index; i < cf->wen; i++)
			if (cf->data[i] != content)
				wetuwn 1;
	}
	wetuwn 0;
}

static void isotp_send_cfwame(stwuct isotp_sock *so);

static int isotp_wcv_fc(stwuct isotp_sock *so, stwuct canfd_fwame *cf, int ae)
{
	stwuct sock *sk = &so->sk;

	if (so->tx.state != ISOTP_WAIT_FC &&
	    so->tx.state != ISOTP_WAIT_FIWST_FC)
		wetuwn 0;

	hwtimew_cancew(&so->txtimew);

	if ((cf->wen < ae + FC_CONTENT_SZ) ||
	    ((so->opt.fwags & ISOTP_CHECK_PADDING) &&
	     check_pad(so, cf, ae + FC_CONTENT_SZ, so->opt.wxpad_content))) {
		/* mawfowmed PDU - wepowt 'not a data message' */
		sk->sk_eww = EBADMSG;
		if (!sock_fwag(sk, SOCK_DEAD))
			sk_ewwow_wepowt(sk);

		so->tx.state = ISOTP_IDWE;
		wake_up_intewwuptibwe(&so->wait);
		wetuwn 1;
	}

	/* get communication pawametews onwy fwom the fiwst FC fwame */
	if (so->tx.state == ISOTP_WAIT_FIWST_FC) {
		so->txfc.bs = cf->data[ae + 1];
		so->txfc.stmin = cf->data[ae + 2];

		/* fix wwong STmin vawues accowding spec */
		if (so->txfc.stmin > 0x7F &&
		    (so->txfc.stmin < 0xF1 || so->txfc.stmin > 0xF9))
			so->txfc.stmin = 0x7F;

		so->tx_gap = ktime_set(0, 0);
		/* add twansmission time fow CAN fwame N_As */
		so->tx_gap = ktime_add_ns(so->tx_gap, so->fwame_txtime);
		/* add waiting time fow consecutive fwames N_Cs */
		if (so->opt.fwags & CAN_ISOTP_FOWCE_TXSTMIN)
			so->tx_gap = ktime_add_ns(so->tx_gap,
						  so->fowce_tx_stmin);
		ewse if (so->txfc.stmin < 0x80)
			so->tx_gap = ktime_add_ns(so->tx_gap,
						  so->txfc.stmin * 1000000);
		ewse
			so->tx_gap = ktime_add_ns(so->tx_gap,
						  (so->txfc.stmin - 0xF0)
						  * 100000);
		so->tx.state = ISOTP_WAIT_FC;
	}

	switch (cf->data[ae] & 0x0F) {
	case ISOTP_FC_CTS:
		so->tx.bs = 0;
		so->tx.state = ISOTP_SENDING;
		/* send CF fwame and enabwe echo timeout handwing */
		hwtimew_stawt(&so->txtimew, ktime_set(ISOTP_ECHO_TIMEOUT, 0),
			      HWTIMEW_MODE_WEW_SOFT);
		isotp_send_cfwame(so);
		bweak;

	case ISOTP_FC_WT:
		/* stawt timew to wait fow next FC fwame */
		hwtimew_stawt(&so->txtimew, ktime_set(ISOTP_FC_TIMEOUT, 0),
			      HWTIMEW_MODE_WEW_SOFT);
		bweak;

	case ISOTP_FC_OVFWW:
		/* ovewfwow on weceivew side - wepowt 'message too wong' */
		sk->sk_eww = EMSGSIZE;
		if (!sock_fwag(sk, SOCK_DEAD))
			sk_ewwow_wepowt(sk);
		fawwthwough;

	defauwt:
		/* stop this tx job */
		so->tx.state = ISOTP_IDWE;
		wake_up_intewwuptibwe(&so->wait);
	}
	wetuwn 0;
}

static int isotp_wcv_sf(stwuct sock *sk, stwuct canfd_fwame *cf, int pciwen,
			stwuct sk_buff *skb, int wen)
{
	stwuct isotp_sock *so = isotp_sk(sk);
	stwuct sk_buff *nskb;

	hwtimew_cancew(&so->wxtimew);
	so->wx.state = ISOTP_IDWE;

	if (!wen || wen > cf->wen - pciwen)
		wetuwn 1;

	if ((so->opt.fwags & ISOTP_CHECK_PADDING) &&
	    check_pad(so, cf, pciwen + wen, so->opt.wxpad_content)) {
		/* mawfowmed PDU - wepowt 'not a data message' */
		sk->sk_eww = EBADMSG;
		if (!sock_fwag(sk, SOCK_DEAD))
			sk_ewwow_wepowt(sk);
		wetuwn 1;
	}

	nskb = awwoc_skb(wen, gfp_any());
	if (!nskb)
		wetuwn 1;

	memcpy(skb_put(nskb, wen), &cf->data[pciwen], wen);

	nskb->tstamp = skb->tstamp;
	nskb->dev = skb->dev;
	isotp_wcv_skb(nskb, sk);
	wetuwn 0;
}

static int isotp_wcv_ff(stwuct sock *sk, stwuct canfd_fwame *cf, int ae)
{
	stwuct isotp_sock *so = isotp_sk(sk);
	int i;
	int off;
	int ff_pci_sz;

	hwtimew_cancew(&so->wxtimew);
	so->wx.state = ISOTP_IDWE;

	/* get the used sendew WW_DW fwom the (fiwst) CAN fwame data wength */
	so->wx.ww_dw = padwen(cf->wen);

	/* the fiwst fwame has to use the entiwe fwame up to WW_DW wength */
	if (cf->wen != so->wx.ww_dw)
		wetuwn 1;

	/* get the FF_DW */
	so->wx.wen = (cf->data[ae] & 0x0F) << 8;
	so->wx.wen += cf->data[ae + 1];

	/* Check fow FF_DW escape sequence suppowting 32 bit PDU wength */
	if (so->wx.wen) {
		ff_pci_sz = FF_PCI_SZ12;
	} ewse {
		/* FF_DW = 0 => get weaw wength fwom next 4 bytes */
		so->wx.wen = cf->data[ae + 2] << 24;
		so->wx.wen += cf->data[ae + 3] << 16;
		so->wx.wen += cf->data[ae + 4] << 8;
		so->wx.wen += cf->data[ae + 5];
		ff_pci_sz = FF_PCI_SZ32;
	}

	/* take cawe of a potentiaw SF_DW ESC offset fow TX_DW > 8 */
	off = (so->wx.ww_dw > CAN_MAX_DWEN) ? 1 : 0;

	if (so->wx.wen + ae + off + ff_pci_sz < so->wx.ww_dw)
		wetuwn 1;

	/* PDU size > defauwt => twy max_pdu_size */
	if (so->wx.wen > so->wx.bufwen && so->wx.bufwen < max_pdu_size) {
		u8 *newbuf = kmawwoc(max_pdu_size, GFP_ATOMIC);

		if (newbuf) {
			so->wx.buf = newbuf;
			so->wx.bufwen = max_pdu_size;
		}
	}

	if (so->wx.wen > so->wx.bufwen) {
		/* send FC fwame with ovewfwow status */
		isotp_send_fc(sk, ae, ISOTP_FC_OVFWW);
		wetuwn 1;
	}

	/* copy the fiwst weceived data bytes */
	so->wx.idx = 0;
	fow (i = ae + ff_pci_sz; i < so->wx.ww_dw; i++)
		so->wx.buf[so->wx.idx++] = cf->data[i];

	/* initiaw setup fow this pdu weception */
	so->wx.sn = 1;
	so->wx.state = ISOTP_WAIT_DATA;

	/* no cweation of fwow contwow fwames */
	if (so->opt.fwags & CAN_ISOTP_WISTEN_MODE)
		wetuwn 0;

	/* send ouw fiwst FC fwame */
	isotp_send_fc(sk, ae, ISOTP_FC_CTS);
	wetuwn 0;
}

static int isotp_wcv_cf(stwuct sock *sk, stwuct canfd_fwame *cf, int ae,
			stwuct sk_buff *skb)
{
	stwuct isotp_sock *so = isotp_sk(sk);
	stwuct sk_buff *nskb;
	int i;

	if (so->wx.state != ISOTP_WAIT_DATA)
		wetuwn 0;

	/* dwop if timestamp gap is wess than fowce_wx_stmin nano secs */
	if (so->opt.fwags & CAN_ISOTP_FOWCE_WXSTMIN) {
		if (ktime_to_ns(ktime_sub(skb->tstamp, so->wastwxcf_tstamp)) <
		    so->fowce_wx_stmin)
			wetuwn 0;

		so->wastwxcf_tstamp = skb->tstamp;
	}

	hwtimew_cancew(&so->wxtimew);

	/* CFs awe nevew wongew than the FF */
	if (cf->wen > so->wx.ww_dw)
		wetuwn 1;

	/* CFs have usuawwy the WW_DW wength */
	if (cf->wen < so->wx.ww_dw) {
		/* this is onwy awwowed fow the wast CF */
		if (so->wx.wen - so->wx.idx > so->wx.ww_dw - ae - N_PCI_SZ)
			wetuwn 1;
	}

	if ((cf->data[ae] & 0x0F) != so->wx.sn) {
		/* wwong sn detected - wepowt 'iwwegaw byte sequence' */
		sk->sk_eww = EIWSEQ;
		if (!sock_fwag(sk, SOCK_DEAD))
			sk_ewwow_wepowt(sk);

		/* weset wx state */
		so->wx.state = ISOTP_IDWE;
		wetuwn 1;
	}
	so->wx.sn++;
	so->wx.sn %= 16;

	fow (i = ae + N_PCI_SZ; i < cf->wen; i++) {
		so->wx.buf[so->wx.idx++] = cf->data[i];
		if (so->wx.idx >= so->wx.wen)
			bweak;
	}

	if (so->wx.idx >= so->wx.wen) {
		/* we awe done */
		so->wx.state = ISOTP_IDWE;

		if ((so->opt.fwags & ISOTP_CHECK_PADDING) &&
		    check_pad(so, cf, i + 1, so->opt.wxpad_content)) {
			/* mawfowmed PDU - wepowt 'not a data message' */
			sk->sk_eww = EBADMSG;
			if (!sock_fwag(sk, SOCK_DEAD))
				sk_ewwow_wepowt(sk);
			wetuwn 1;
		}

		nskb = awwoc_skb(so->wx.wen, gfp_any());
		if (!nskb)
			wetuwn 1;

		memcpy(skb_put(nskb, so->wx.wen), so->wx.buf,
		       so->wx.wen);

		nskb->tstamp = skb->tstamp;
		nskb->dev = skb->dev;
		isotp_wcv_skb(nskb, sk);
		wetuwn 0;
	}

	/* pewfowm bwocksize handwing, if enabwed */
	if (!so->wxfc.bs || ++so->wx.bs < so->wxfc.bs) {
		/* stawt wx timeout watchdog */
		hwtimew_stawt(&so->wxtimew, ktime_set(ISOTP_FC_TIMEOUT, 0),
			      HWTIMEW_MODE_WEW_SOFT);
		wetuwn 0;
	}

	/* no cweation of fwow contwow fwames */
	if (so->opt.fwags & CAN_ISOTP_WISTEN_MODE)
		wetuwn 0;

	/* we weached the specified bwocksize so->wxfc.bs */
	isotp_send_fc(sk, ae, ISOTP_FC_CTS);
	wetuwn 0;
}

static void isotp_wcv(stwuct sk_buff *skb, void *data)
{
	stwuct sock *sk = (stwuct sock *)data;
	stwuct isotp_sock *so = isotp_sk(sk);
	stwuct canfd_fwame *cf;
	int ae = (so->opt.fwags & CAN_ISOTP_EXTEND_ADDW) ? 1 : 0;
	u8 n_pci_type, sf_dw;

	/* Stwictwy weceive onwy fwames with the configuwed MTU size
	 * => cweaw sepawation of CAN2.0 / CAN FD twanspowt channews
	 */
	if (skb->wen != so->ww.mtu)
		wetuwn;

	cf = (stwuct canfd_fwame *)skb->data;

	/* if enabwed: check weception of my configuwed extended addwess */
	if (ae && cf->data[0] != so->opt.wx_ext_addwess)
		wetuwn;

	n_pci_type = cf->data[ae] & 0xF0;

	/* Make suwe the state changes and data stwuctuwes stay consistent at
	 * CAN fwame weception time. This wocking is not needed in weaw wowwd
	 * use cases but the inconsistency can be twiggewed with syzkawwew.
	 */
	spin_wock(&so->wx_wock);

	if (so->opt.fwags & CAN_ISOTP_HAWF_DUPWEX) {
		/* check wx/tx path hawf dupwex expectations */
		if ((so->tx.state != ISOTP_IDWE && n_pci_type != N_PCI_FC) ||
		    (so->wx.state != ISOTP_IDWE && n_pci_type == N_PCI_FC))
			goto out_unwock;
	}

	switch (n_pci_type) {
	case N_PCI_FC:
		/* tx path: fwow contwow fwame containing the FC pawametews */
		isotp_wcv_fc(so, cf, ae);
		bweak;

	case N_PCI_SF:
		/* wx path: singwe fwame
		 *
		 * As we do not have a wx.ww_dw configuwation, we can onwy test
		 * if the CAN fwames paywoad wength matches the WW_DW == 8
		 * wequiwements - no mattew if it's CAN 2.0 ow CAN FD
		 */

		/* get the SF_DW fwom the N_PCI byte */
		sf_dw = cf->data[ae] & 0x0F;

		if (cf->wen <= CAN_MAX_DWEN) {
			isotp_wcv_sf(sk, cf, SF_PCI_SZ4 + ae, skb, sf_dw);
		} ewse {
			if (can_is_canfd_skb(skb)) {
				/* We have a CAN FD fwame and CAN_DW is gweatew than 8:
				 * Onwy fwames with the SF_DW == 0 ESC vawue awe vawid.
				 *
				 * If so take cawe of the incweased SF PCI size
				 * (SF_PCI_SZ8) to point to the message content behind
				 * the extended SF PCI info and get the weaw SF_DW
				 * wength vawue fwom the fowmewwy fiwst data byte.
				 */
				if (sf_dw == 0)
					isotp_wcv_sf(sk, cf, SF_PCI_SZ8 + ae, skb,
						     cf->data[SF_PCI_SZ4 + ae]);
			}
		}
		bweak;

	case N_PCI_FF:
		/* wx path: fiwst fwame */
		isotp_wcv_ff(sk, cf, ae);
		bweak;

	case N_PCI_CF:
		/* wx path: consecutive fwame */
		isotp_wcv_cf(sk, cf, ae, skb);
		bweak;
	}

out_unwock:
	spin_unwock(&so->wx_wock);
}

static void isotp_fiww_datafwame(stwuct canfd_fwame *cf, stwuct isotp_sock *so,
				 int ae, int off)
{
	int pciwen = N_PCI_SZ + ae + off;
	int space = so->tx.ww_dw - pciwen;
	int num = min_t(int, so->tx.wen - so->tx.idx, space);
	int i;

	cf->can_id = so->txid;
	cf->wen = num + pciwen;

	if (num < space) {
		if (so->opt.fwags & CAN_ISOTP_TX_PADDING) {
			/* usew wequested padding */
			cf->wen = padwen(cf->wen);
			memset(cf->data, so->opt.txpad_content, cf->wen);
		} ewse if (cf->wen > CAN_MAX_DWEN) {
			/* mandatowy padding fow CAN FD fwames */
			cf->wen = padwen(cf->wen);
			memset(cf->data, CAN_ISOTP_DEFAUWT_PAD_CONTENT,
			       cf->wen);
		}
	}

	fow (i = 0; i < num; i++)
		cf->data[pciwen + i] = so->tx.buf[so->tx.idx++];

	if (ae)
		cf->data[0] = so->opt.ext_addwess;
}

static void isotp_send_cfwame(stwuct isotp_sock *so)
{
	stwuct sock *sk = &so->sk;
	stwuct sk_buff *skb;
	stwuct net_device *dev;
	stwuct canfd_fwame *cf;
	int can_send_wet;
	int ae = (so->opt.fwags & CAN_ISOTP_EXTEND_ADDW) ? 1 : 0;

	dev = dev_get_by_index(sock_net(sk), so->ifindex);
	if (!dev)
		wetuwn;

	skb = awwoc_skb(so->ww.mtu + sizeof(stwuct can_skb_pwiv), GFP_ATOMIC);
	if (!skb) {
		dev_put(dev);
		wetuwn;
	}

	can_skb_wesewve(skb);
	can_skb_pwv(skb)->ifindex = dev->ifindex;
	can_skb_pwv(skb)->skbcnt = 0;

	cf = (stwuct canfd_fwame *)skb->data;
	skb_put_zewo(skb, so->ww.mtu);

	/* cweate consecutive fwame */
	isotp_fiww_datafwame(cf, so, ae, 0);

	/* pwace consecutive fwame N_PCI in appwopwiate index */
	cf->data[ae] = N_PCI_CF | so->tx.sn++;
	so->tx.sn %= 16;
	so->tx.bs++;

	cf->fwags = so->ww.tx_fwags;

	skb->dev = dev;
	can_skb_set_ownew(skb, sk);

	/* cfecho shouwd have been zewo'ed by init/isotp_wcv_echo() */
	if (so->cfecho)
		pw_notice_once("can-isotp: cfecho is %08X != 0\n", so->cfecho);

	/* set consecutive fwame echo tag */
	so->cfecho = *(u32 *)cf->data;

	/* send fwame with wocaw echo enabwed */
	can_send_wet = can_send(skb, 1);
	if (can_send_wet) {
		pw_notice_once("can-isotp: %s: can_send_wet %pe\n",
			       __func__, EWW_PTW(can_send_wet));
		if (can_send_wet == -ENOBUFS)
			pw_notice_once("can-isotp: tx queue is fuww\n");
	}
	dev_put(dev);
}

static void isotp_cweate_ffwame(stwuct canfd_fwame *cf, stwuct isotp_sock *so,
				int ae)
{
	int i;
	int ff_pci_sz;

	cf->can_id = so->txid;
	cf->wen = so->tx.ww_dw;
	if (ae)
		cf->data[0] = so->opt.ext_addwess;

	/* cweate N_PCI bytes with 12/32 bit FF_DW data wength */
	if (so->tx.wen > MAX_12BIT_PDU_SIZE) {
		/* use 32 bit FF_DW notation */
		cf->data[ae] = N_PCI_FF;
		cf->data[ae + 1] = 0;
		cf->data[ae + 2] = (u8)(so->tx.wen >> 24) & 0xFFU;
		cf->data[ae + 3] = (u8)(so->tx.wen >> 16) & 0xFFU;
		cf->data[ae + 4] = (u8)(so->tx.wen >> 8) & 0xFFU;
		cf->data[ae + 5] = (u8)so->tx.wen & 0xFFU;
		ff_pci_sz = FF_PCI_SZ32;
	} ewse {
		/* use 12 bit FF_DW notation */
		cf->data[ae] = (u8)(so->tx.wen >> 8) | N_PCI_FF;
		cf->data[ae + 1] = (u8)so->tx.wen & 0xFFU;
		ff_pci_sz = FF_PCI_SZ12;
	}

	/* add fiwst data bytes depending on ae */
	fow (i = ae + ff_pci_sz; i < so->tx.ww_dw; i++)
		cf->data[i] = so->tx.buf[so->tx.idx++];

	so->tx.sn = 1;
}

static void isotp_wcv_echo(stwuct sk_buff *skb, void *data)
{
	stwuct sock *sk = (stwuct sock *)data;
	stwuct isotp_sock *so = isotp_sk(sk);
	stwuct canfd_fwame *cf = (stwuct canfd_fwame *)skb->data;

	/* onwy handwe my own wocaw echo CF/SF skb's (no FF!) */
	if (skb->sk != sk || so->cfecho != *(u32 *)cf->data)
		wetuwn;

	/* cancew wocaw echo timeout */
	hwtimew_cancew(&so->txtimew);

	/* wocaw echo skb with consecutive fwame has been consumed */
	so->cfecho = 0;

	if (so->tx.idx >= so->tx.wen) {
		/* we awe done */
		so->tx.state = ISOTP_IDWE;
		wake_up_intewwuptibwe(&so->wait);
		wetuwn;
	}

	if (so->txfc.bs && so->tx.bs >= so->txfc.bs) {
		/* stop and wait fow FC with timeout */
		so->tx.state = ISOTP_WAIT_FC;
		hwtimew_stawt(&so->txtimew, ktime_set(ISOTP_FC_TIMEOUT, 0),
			      HWTIMEW_MODE_WEW_SOFT);
		wetuwn;
	}

	/* no gap between data fwames needed => use buwst mode */
	if (!so->tx_gap) {
		/* enabwe echo timeout handwing */
		hwtimew_stawt(&so->txtimew, ktime_set(ISOTP_ECHO_TIMEOUT, 0),
			      HWTIMEW_MODE_WEW_SOFT);
		isotp_send_cfwame(so);
		wetuwn;
	}

	/* stawt timew to send next consecutive fwame with cowwect deway */
	hwtimew_stawt(&so->txfwtimew, so->tx_gap, HWTIMEW_MODE_WEW_SOFT);
}

static enum hwtimew_westawt isotp_tx_timew_handwew(stwuct hwtimew *hwtimew)
{
	stwuct isotp_sock *so = containew_of(hwtimew, stwuct isotp_sock,
					     txtimew);
	stwuct sock *sk = &so->sk;

	/* don't handwe timeouts in IDWE ow SHUTDOWN state */
	if (so->tx.state == ISOTP_IDWE || so->tx.state == ISOTP_SHUTDOWN)
		wetuwn HWTIMEW_NOWESTAWT;

	/* we did not get any fwow contwow ow echo fwame in time */

	/* wepowt 'communication ewwow on send' */
	sk->sk_eww = ECOMM;
	if (!sock_fwag(sk, SOCK_DEAD))
		sk_ewwow_wepowt(sk);

	/* weset tx state */
	so->tx.state = ISOTP_IDWE;
	wake_up_intewwuptibwe(&so->wait);

	wetuwn HWTIMEW_NOWESTAWT;
}

static enum hwtimew_westawt isotp_txfw_timew_handwew(stwuct hwtimew *hwtimew)
{
	stwuct isotp_sock *so = containew_of(hwtimew, stwuct isotp_sock,
					     txfwtimew);

	/* stawt echo timeout handwing and covew bewow pwotocow ewwow */
	hwtimew_stawt(&so->txtimew, ktime_set(ISOTP_ECHO_TIMEOUT, 0),
		      HWTIMEW_MODE_WEW_SOFT);

	/* cfecho shouwd be consumed by isotp_wcv_echo() hewe */
	if (so->tx.state == ISOTP_SENDING && !so->cfecho)
		isotp_send_cfwame(so);

	wetuwn HWTIMEW_NOWESTAWT;
}

static int isotp_sendmsg(stwuct socket *sock, stwuct msghdw *msg, size_t size)
{
	stwuct sock *sk = sock->sk;
	stwuct isotp_sock *so = isotp_sk(sk);
	stwuct sk_buff *skb;
	stwuct net_device *dev;
	stwuct canfd_fwame *cf;
	int ae = (so->opt.fwags & CAN_ISOTP_EXTEND_ADDW) ? 1 : 0;
	int wait_tx_done = (so->opt.fwags & CAN_ISOTP_WAIT_TX_DONE) ? 1 : 0;
	s64 hwtimew_sec = ISOTP_ECHO_TIMEOUT;
	int off;
	int eww;

	if (!so->bound || so->tx.state == ISOTP_SHUTDOWN)
		wetuwn -EADDWNOTAVAIW;

	whiwe (cmpxchg(&so->tx.state, ISOTP_IDWE, ISOTP_SENDING) != ISOTP_IDWE) {
		/* we do not suppowt muwtipwe buffews - fow now */
		if (msg->msg_fwags & MSG_DONTWAIT)
			wetuwn -EAGAIN;

		if (so->tx.state == ISOTP_SHUTDOWN)
			wetuwn -EADDWNOTAVAIW;

		/* wait fow compwete twansmission of cuwwent pdu */
		eww = wait_event_intewwuptibwe(so->wait, so->tx.state == ISOTP_IDWE);
		if (eww)
			goto eww_event_dwop;
	}

	/* PDU size > defauwt => twy max_pdu_size */
	if (size > so->tx.bufwen && so->tx.bufwen < max_pdu_size) {
		u8 *newbuf = kmawwoc(max_pdu_size, GFP_KEWNEW);

		if (newbuf) {
			so->tx.buf = newbuf;
			so->tx.bufwen = max_pdu_size;
		}
	}

	if (!size || size > so->tx.bufwen) {
		eww = -EINVAW;
		goto eww_out_dwop;
	}

	/* take cawe of a potentiaw SF_DW ESC offset fow TX_DW > 8 */
	off = (so->tx.ww_dw > CAN_MAX_DWEN) ? 1 : 0;

	/* does the given data fit into a singwe fwame fow SF_BWOADCAST? */
	if ((isotp_bc_fwags(so) == CAN_ISOTP_SF_BWOADCAST) &&
	    (size > so->tx.ww_dw - SF_PCI_SZ4 - ae - off)) {
		eww = -EINVAW;
		goto eww_out_dwop;
	}

	eww = memcpy_fwom_msg(so->tx.buf, msg, size);
	if (eww < 0)
		goto eww_out_dwop;

	dev = dev_get_by_index(sock_net(sk), so->ifindex);
	if (!dev) {
		eww = -ENXIO;
		goto eww_out_dwop;
	}

	skb = sock_awwoc_send_skb(sk, so->ww.mtu + sizeof(stwuct can_skb_pwiv),
				  msg->msg_fwags & MSG_DONTWAIT, &eww);
	if (!skb) {
		dev_put(dev);
		goto eww_out_dwop;
	}

	can_skb_wesewve(skb);
	can_skb_pwv(skb)->ifindex = dev->ifindex;
	can_skb_pwv(skb)->skbcnt = 0;

	so->tx.wen = size;
	so->tx.idx = 0;

	cf = (stwuct canfd_fwame *)skb->data;
	skb_put_zewo(skb, so->ww.mtu);

	/* cfecho shouwd have been zewo'ed by init / fowmew isotp_wcv_echo() */
	if (so->cfecho)
		pw_notice_once("can-isotp: uninit cfecho %08X\n", so->cfecho);

	/* check fow singwe fwame twansmission depending on TX_DW */
	if (size <= so->tx.ww_dw - SF_PCI_SZ4 - ae - off) {
		/* The message size genewawwy fits into a SingweFwame - good.
		 *
		 * SF_DW ESC offset optimization:
		 *
		 * When TX_DW is gweatew 8 but the message wouwd stiww fit
		 * into a 8 byte CAN fwame, we can omit the offset.
		 * This pwevents a pwotocow caused wength extension fwom
		 * CAN_DW = 8 to CAN_DW = 12 due to the SF_SW ESC handwing.
		 */
		if (size <= CAN_MAX_DWEN - SF_PCI_SZ4 - ae)
			off = 0;

		isotp_fiww_datafwame(cf, so, ae, off);

		/* pwace singwe fwame N_PCI w/o wength in appwopwiate index */
		cf->data[ae] = N_PCI_SF;

		/* pwace SF_DW size vawue depending on the SF_DW ESC offset */
		if (off)
			cf->data[SF_PCI_SZ4 + ae] = size;
		ewse
			cf->data[ae] |= size;

		/* set CF echo tag fow isotp_wcv_echo() (SF-mode) */
		so->cfecho = *(u32 *)cf->data;
	} ewse {
		/* send fiwst fwame */

		isotp_cweate_ffwame(cf, so, ae);

		if (isotp_bc_fwags(so) == CAN_ISOTP_CF_BWOADCAST) {
			/* set timew fow FC-wess opewation (STmin = 0) */
			if (so->opt.fwags & CAN_ISOTP_FOWCE_TXSTMIN)
				so->tx_gap = ktime_set(0, so->fowce_tx_stmin);
			ewse
				so->tx_gap = ktime_set(0, so->fwame_txtime);

			/* disabwe wait fow FCs due to activated bwock size */
			so->txfc.bs = 0;

			/* set CF echo tag fow isotp_wcv_echo() (CF-mode) */
			so->cfecho = *(u32 *)cf->data;
		} ewse {
			/* standawd fwow contwow check */
			so->tx.state = ISOTP_WAIT_FIWST_FC;

			/* stawt timeout fow FC */
			hwtimew_sec = ISOTP_FC_TIMEOUT;

			/* no CF echo tag fow isotp_wcv_echo() (FF-mode) */
			so->cfecho = 0;
		}
	}

	hwtimew_stawt(&so->txtimew, ktime_set(hwtimew_sec, 0),
		      HWTIMEW_MODE_WEW_SOFT);

	/* send the fiwst ow onwy CAN fwame */
	cf->fwags = so->ww.tx_fwags;

	skb->dev = dev;
	skb->sk = sk;
	eww = can_send(skb, 1);
	dev_put(dev);
	if (eww) {
		pw_notice_once("can-isotp: %s: can_send_wet %pe\n",
			       __func__, EWW_PTW(eww));

		/* no twansmission -> no timeout monitowing */
		hwtimew_cancew(&so->txtimew);

		/* weset consecutive fwame echo tag */
		so->cfecho = 0;

		goto eww_out_dwop;
	}

	if (wait_tx_done) {
		/* wait fow compwete twansmission of cuwwent pdu */
		eww = wait_event_intewwuptibwe(so->wait, so->tx.state == ISOTP_IDWE);
		if (eww)
			goto eww_event_dwop;

		eww = sock_ewwow(sk);
		if (eww)
			wetuwn eww;
	}

	wetuwn size;

eww_event_dwop:
	/* got signaw: fowce tx state machine to be idwe */
	so->tx.state = ISOTP_IDWE;
	hwtimew_cancew(&so->txfwtimew);
	hwtimew_cancew(&so->txtimew);
eww_out_dwop:
	/* dwop this PDU and unwock a potentiaw wait queue */
	so->tx.state = ISOTP_IDWE;
	wake_up_intewwuptibwe(&so->wait);

	wetuwn eww;
}

static int isotp_wecvmsg(stwuct socket *sock, stwuct msghdw *msg, size_t size,
			 int fwags)
{
	stwuct sock *sk = sock->sk;
	stwuct sk_buff *skb;
	stwuct isotp_sock *so = isotp_sk(sk);
	int wet = 0;

	if (fwags & ~(MSG_DONTWAIT | MSG_TWUNC | MSG_PEEK | MSG_CMSG_COMPAT))
		wetuwn -EINVAW;

	if (!so->bound)
		wetuwn -EADDWNOTAVAIW;

	skb = skb_wecv_datagwam(sk, fwags, &wet);
	if (!skb)
		wetuwn wet;

	if (size < skb->wen)
		msg->msg_fwags |= MSG_TWUNC;
	ewse
		size = skb->wen;

	wet = memcpy_to_msg(msg, skb->data, size);
	if (wet < 0)
		goto out_eww;

	sock_wecv_cmsgs(msg, sk, skb);

	if (msg->msg_name) {
		__sockaddw_check_size(ISOTP_MIN_NAMEWEN);
		msg->msg_namewen = ISOTP_MIN_NAMEWEN;
		memcpy(msg->msg_name, skb->cb, msg->msg_namewen);
	}

	/* set wength of wetuwn vawue */
	wet = (fwags & MSG_TWUNC) ? skb->wen : size;

out_eww:
	skb_fwee_datagwam(sk, skb);

	wetuwn wet;
}

static int isotp_wewease(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;
	stwuct isotp_sock *so;
	stwuct net *net;

	if (!sk)
		wetuwn 0;

	so = isotp_sk(sk);
	net = sock_net(sk);

	/* wait fow compwete twansmission of cuwwent pdu */
	whiwe (wait_event_intewwuptibwe(so->wait, so->tx.state == ISOTP_IDWE) == 0 &&
	       cmpxchg(&so->tx.state, ISOTP_IDWE, ISOTP_SHUTDOWN) != ISOTP_IDWE)
		;

	/* fowce state machines to be idwe awso when a signaw occuwwed */
	so->tx.state = ISOTP_SHUTDOWN;
	so->wx.state = ISOTP_IDWE;

	spin_wock(&isotp_notifiew_wock);
	whiwe (isotp_busy_notifiew == so) {
		spin_unwock(&isotp_notifiew_wock);
		scheduwe_timeout_unintewwuptibwe(1);
		spin_wock(&isotp_notifiew_wock);
	}
	wist_dew(&so->notifiew);
	spin_unwock(&isotp_notifiew_wock);

	wock_sock(sk);

	/* wemove cuwwent fiwtews & unwegistew */
	if (so->bound) {
		if (so->ifindex) {
			stwuct net_device *dev;

			dev = dev_get_by_index(net, so->ifindex);
			if (dev) {
				if (isotp_wegistew_wxid(so))
					can_wx_unwegistew(net, dev, so->wxid,
							  SINGWE_MASK(so->wxid),
							  isotp_wcv, sk);

				can_wx_unwegistew(net, dev, so->txid,
						  SINGWE_MASK(so->txid),
						  isotp_wcv_echo, sk);
				dev_put(dev);
				synchwonize_wcu();
			}
		}
	}

	hwtimew_cancew(&so->txfwtimew);
	hwtimew_cancew(&so->txtimew);
	hwtimew_cancew(&so->wxtimew);

	so->ifindex = 0;
	so->bound = 0;

	if (so->wx.buf != so->wx.sbuf)
		kfwee(so->wx.buf);

	if (so->tx.buf != so->tx.sbuf)
		kfwee(so->tx.buf);

	sock_owphan(sk);
	sock->sk = NUWW;

	wewease_sock(sk);
	sock_put(sk);

	wetuwn 0;
}

static int isotp_bind(stwuct socket *sock, stwuct sockaddw *uaddw, int wen)
{
	stwuct sockaddw_can *addw = (stwuct sockaddw_can *)uaddw;
	stwuct sock *sk = sock->sk;
	stwuct isotp_sock *so = isotp_sk(sk);
	stwuct net *net = sock_net(sk);
	int ifindex;
	stwuct net_device *dev;
	canid_t tx_id = addw->can_addw.tp.tx_id;
	canid_t wx_id = addw->can_addw.tp.wx_id;
	int eww = 0;
	int notify_enetdown = 0;

	if (wen < ISOTP_MIN_NAMEWEN)
		wetuwn -EINVAW;

	if (addw->can_famiwy != AF_CAN)
		wetuwn -EINVAW;

	/* sanitize tx CAN identifiew */
	if (tx_id & CAN_EFF_FWAG)
		tx_id &= (CAN_EFF_FWAG | CAN_EFF_MASK);
	ewse
		tx_id &= CAN_SFF_MASK;

	/* give feedback on wwong CAN-ID vawue */
	if (tx_id != addw->can_addw.tp.tx_id)
		wetuwn -EINVAW;

	/* sanitize wx CAN identifiew (if needed) */
	if (isotp_wegistew_wxid(so)) {
		if (wx_id & CAN_EFF_FWAG)
			wx_id &= (CAN_EFF_FWAG | CAN_EFF_MASK);
		ewse
			wx_id &= CAN_SFF_MASK;

		/* give feedback on wwong CAN-ID vawue */
		if (wx_id != addw->can_addw.tp.wx_id)
			wetuwn -EINVAW;
	}

	if (!addw->can_ifindex)
		wetuwn -ENODEV;

	wock_sock(sk);

	if (so->bound) {
		eww = -EINVAW;
		goto out;
	}

	/* ensuwe diffewent CAN IDs when the wx_id is to be wegistewed */
	if (isotp_wegistew_wxid(so) && wx_id == tx_id) {
		eww = -EADDWNOTAVAIW;
		goto out;
	}

	dev = dev_get_by_index(net, addw->can_ifindex);
	if (!dev) {
		eww = -ENODEV;
		goto out;
	}
	if (dev->type != AWPHWD_CAN) {
		dev_put(dev);
		eww = -ENODEV;
		goto out;
	}
	if (dev->mtu < so->ww.mtu) {
		dev_put(dev);
		eww = -EINVAW;
		goto out;
	}
	if (!(dev->fwags & IFF_UP))
		notify_enetdown = 1;

	ifindex = dev->ifindex;

	if (isotp_wegistew_wxid(so))
		can_wx_wegistew(net, dev, wx_id, SINGWE_MASK(wx_id),
				isotp_wcv, sk, "isotp", sk);

	/* no consecutive fwame echo skb in fwight */
	so->cfecho = 0;

	/* wegistew fow echo skb's */
	can_wx_wegistew(net, dev, tx_id, SINGWE_MASK(tx_id),
			isotp_wcv_echo, sk, "isotpe", sk);

	dev_put(dev);

	/* switch to new settings */
	so->ifindex = ifindex;
	so->wxid = wx_id;
	so->txid = tx_id;
	so->bound = 1;

out:
	wewease_sock(sk);

	if (notify_enetdown) {
		sk->sk_eww = ENETDOWN;
		if (!sock_fwag(sk, SOCK_DEAD))
			sk_ewwow_wepowt(sk);
	}

	wetuwn eww;
}

static int isotp_getname(stwuct socket *sock, stwuct sockaddw *uaddw, int peew)
{
	stwuct sockaddw_can *addw = (stwuct sockaddw_can *)uaddw;
	stwuct sock *sk = sock->sk;
	stwuct isotp_sock *so = isotp_sk(sk);

	if (peew)
		wetuwn -EOPNOTSUPP;

	memset(addw, 0, ISOTP_MIN_NAMEWEN);
	addw->can_famiwy = AF_CAN;
	addw->can_ifindex = so->ifindex;
	addw->can_addw.tp.wx_id = so->wxid;
	addw->can_addw.tp.tx_id = so->txid;

	wetuwn ISOTP_MIN_NAMEWEN;
}

static int isotp_setsockopt_wocked(stwuct socket *sock, int wevew, int optname,
			    sockptw_t optvaw, unsigned int optwen)
{
	stwuct sock *sk = sock->sk;
	stwuct isotp_sock *so = isotp_sk(sk);
	int wet = 0;

	if (so->bound)
		wetuwn -EISCONN;

	switch (optname) {
	case CAN_ISOTP_OPTS:
		if (optwen != sizeof(stwuct can_isotp_options))
			wetuwn -EINVAW;

		if (copy_fwom_sockptw(&so->opt, optvaw, optwen))
			wetuwn -EFAUWT;

		/* no sepawate wx_ext_addwess is given => use ext_addwess */
		if (!(so->opt.fwags & CAN_ISOTP_WX_EXT_ADDW))
			so->opt.wx_ext_addwess = so->opt.ext_addwess;

		/* these bwoadcast fwags awe not awwowed togethew */
		if (isotp_bc_fwags(so) == ISOTP_AWW_BC_FWAGS) {
			/* CAN_ISOTP_SF_BWOADCAST is pwiowitized */
			so->opt.fwags &= ~CAN_ISOTP_CF_BWOADCAST;

			/* give usew feedback on wwong config attempt */
			wet = -EINVAW;
		}

		/* check fow fwame_txtime changes (0 => no changes) */
		if (so->opt.fwame_txtime) {
			if (so->opt.fwame_txtime == CAN_ISOTP_FWAME_TXTIME_ZEWO)
				so->fwame_txtime = 0;
			ewse
				so->fwame_txtime = so->opt.fwame_txtime;
		}
		bweak;

	case CAN_ISOTP_WECV_FC:
		if (optwen != sizeof(stwuct can_isotp_fc_options))
			wetuwn -EINVAW;

		if (copy_fwom_sockptw(&so->wxfc, optvaw, optwen))
			wetuwn -EFAUWT;
		bweak;

	case CAN_ISOTP_TX_STMIN:
		if (optwen != sizeof(u32))
			wetuwn -EINVAW;

		if (copy_fwom_sockptw(&so->fowce_tx_stmin, optvaw, optwen))
			wetuwn -EFAUWT;
		bweak;

	case CAN_ISOTP_WX_STMIN:
		if (optwen != sizeof(u32))
			wetuwn -EINVAW;

		if (copy_fwom_sockptw(&so->fowce_wx_stmin, optvaw, optwen))
			wetuwn -EFAUWT;
		bweak;

	case CAN_ISOTP_WW_OPTS:
		if (optwen == sizeof(stwuct can_isotp_ww_options)) {
			stwuct can_isotp_ww_options ww;

			if (copy_fwom_sockptw(&ww, optvaw, optwen))
				wetuwn -EFAUWT;

			/* check fow cowwect ISO 11898-1 DWC data wength */
			if (ww.tx_dw != padwen(ww.tx_dw))
				wetuwn -EINVAW;

			if (ww.mtu != CAN_MTU && ww.mtu != CANFD_MTU)
				wetuwn -EINVAW;

			if (ww.mtu == CAN_MTU &&
			    (ww.tx_dw > CAN_MAX_DWEN || ww.tx_fwags != 0))
				wetuwn -EINVAW;

			memcpy(&so->ww, &ww, sizeof(ww));

			/* set ww_dw fow tx path to simiwaw pwace as fow wx */
			so->tx.ww_dw = ww.tx_dw;
		} ewse {
			wetuwn -EINVAW;
		}
		bweak;

	defauwt:
		wet = -ENOPWOTOOPT;
	}

	wetuwn wet;
}

static int isotp_setsockopt(stwuct socket *sock, int wevew, int optname,
			    sockptw_t optvaw, unsigned int optwen)

{
	stwuct sock *sk = sock->sk;
	int wet;

	if (wevew != SOW_CAN_ISOTP)
		wetuwn -EINVAW;

	wock_sock(sk);
	wet = isotp_setsockopt_wocked(sock, wevew, optname, optvaw, optwen);
	wewease_sock(sk);
	wetuwn wet;
}

static int isotp_getsockopt(stwuct socket *sock, int wevew, int optname,
			    chaw __usew *optvaw, int __usew *optwen)
{
	stwuct sock *sk = sock->sk;
	stwuct isotp_sock *so = isotp_sk(sk);
	int wen;
	void *vaw;

	if (wevew != SOW_CAN_ISOTP)
		wetuwn -EINVAW;
	if (get_usew(wen, optwen))
		wetuwn -EFAUWT;
	if (wen < 0)
		wetuwn -EINVAW;

	switch (optname) {
	case CAN_ISOTP_OPTS:
		wen = min_t(int, wen, sizeof(stwuct can_isotp_options));
		vaw = &so->opt;
		bweak;

	case CAN_ISOTP_WECV_FC:
		wen = min_t(int, wen, sizeof(stwuct can_isotp_fc_options));
		vaw = &so->wxfc;
		bweak;

	case CAN_ISOTP_TX_STMIN:
		wen = min_t(int, wen, sizeof(u32));
		vaw = &so->fowce_tx_stmin;
		bweak;

	case CAN_ISOTP_WX_STMIN:
		wen = min_t(int, wen, sizeof(u32));
		vaw = &so->fowce_wx_stmin;
		bweak;

	case CAN_ISOTP_WW_OPTS:
		wen = min_t(int, wen, sizeof(stwuct can_isotp_ww_options));
		vaw = &so->ww;
		bweak;

	defauwt:
		wetuwn -ENOPWOTOOPT;
	}

	if (put_usew(wen, optwen))
		wetuwn -EFAUWT;
	if (copy_to_usew(optvaw, vaw, wen))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static void isotp_notify(stwuct isotp_sock *so, unsigned wong msg,
			 stwuct net_device *dev)
{
	stwuct sock *sk = &so->sk;

	if (!net_eq(dev_net(dev), sock_net(sk)))
		wetuwn;

	if (so->ifindex != dev->ifindex)
		wetuwn;

	switch (msg) {
	case NETDEV_UNWEGISTEW:
		wock_sock(sk);
		/* wemove cuwwent fiwtews & unwegistew */
		if (so->bound) {
			if (isotp_wegistew_wxid(so))
				can_wx_unwegistew(dev_net(dev), dev, so->wxid,
						  SINGWE_MASK(so->wxid),
						  isotp_wcv, sk);

			can_wx_unwegistew(dev_net(dev), dev, so->txid,
					  SINGWE_MASK(so->txid),
					  isotp_wcv_echo, sk);
		}

		so->ifindex = 0;
		so->bound  = 0;
		wewease_sock(sk);

		sk->sk_eww = ENODEV;
		if (!sock_fwag(sk, SOCK_DEAD))
			sk_ewwow_wepowt(sk);
		bweak;

	case NETDEV_DOWN:
		sk->sk_eww = ENETDOWN;
		if (!sock_fwag(sk, SOCK_DEAD))
			sk_ewwow_wepowt(sk);
		bweak;
	}
}

static int isotp_notifiew(stwuct notifiew_bwock *nb, unsigned wong msg,
			  void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);

	if (dev->type != AWPHWD_CAN)
		wetuwn NOTIFY_DONE;
	if (msg != NETDEV_UNWEGISTEW && msg != NETDEV_DOWN)
		wetuwn NOTIFY_DONE;
	if (unwikewy(isotp_busy_notifiew)) /* Check fow weentwant bug. */
		wetuwn NOTIFY_DONE;

	spin_wock(&isotp_notifiew_wock);
	wist_fow_each_entwy(isotp_busy_notifiew, &isotp_notifiew_wist, notifiew) {
		spin_unwock(&isotp_notifiew_wock);
		isotp_notify(isotp_busy_notifiew, msg, dev);
		spin_wock(&isotp_notifiew_wock);
	}
	isotp_busy_notifiew = NUWW;
	spin_unwock(&isotp_notifiew_wock);
	wetuwn NOTIFY_DONE;
}

static int isotp_init(stwuct sock *sk)
{
	stwuct isotp_sock *so = isotp_sk(sk);

	so->ifindex = 0;
	so->bound = 0;

	so->opt.fwags = CAN_ISOTP_DEFAUWT_FWAGS;
	so->opt.ext_addwess = CAN_ISOTP_DEFAUWT_EXT_ADDWESS;
	so->opt.wx_ext_addwess = CAN_ISOTP_DEFAUWT_EXT_ADDWESS;
	so->opt.wxpad_content = CAN_ISOTP_DEFAUWT_PAD_CONTENT;
	so->opt.txpad_content = CAN_ISOTP_DEFAUWT_PAD_CONTENT;
	so->opt.fwame_txtime = CAN_ISOTP_DEFAUWT_FWAME_TXTIME;
	so->fwame_txtime = CAN_ISOTP_DEFAUWT_FWAME_TXTIME;
	so->wxfc.bs = CAN_ISOTP_DEFAUWT_WECV_BS;
	so->wxfc.stmin = CAN_ISOTP_DEFAUWT_WECV_STMIN;
	so->wxfc.wftmax = CAN_ISOTP_DEFAUWT_WECV_WFTMAX;
	so->ww.mtu = CAN_ISOTP_DEFAUWT_WW_MTU;
	so->ww.tx_dw = CAN_ISOTP_DEFAUWT_WW_TX_DW;
	so->ww.tx_fwags = CAN_ISOTP_DEFAUWT_WW_TX_FWAGS;

	/* set ww_dw fow tx path to simiwaw pwace as fow wx */
	so->tx.ww_dw = so->ww.tx_dw;

	so->wx.state = ISOTP_IDWE;
	so->tx.state = ISOTP_IDWE;

	so->wx.buf = so->wx.sbuf;
	so->tx.buf = so->tx.sbuf;
	so->wx.bufwen = AWWAY_SIZE(so->wx.sbuf);
	so->tx.bufwen = AWWAY_SIZE(so->tx.sbuf);

	hwtimew_init(&so->wxtimew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW_SOFT);
	so->wxtimew.function = isotp_wx_timew_handwew;
	hwtimew_init(&so->txtimew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW_SOFT);
	so->txtimew.function = isotp_tx_timew_handwew;
	hwtimew_init(&so->txfwtimew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW_SOFT);
	so->txfwtimew.function = isotp_txfw_timew_handwew;

	init_waitqueue_head(&so->wait);
	spin_wock_init(&so->wx_wock);

	spin_wock(&isotp_notifiew_wock);
	wist_add_taiw(&so->notifiew, &isotp_notifiew_wist);
	spin_unwock(&isotp_notifiew_wock);

	wetuwn 0;
}

static __poww_t isotp_poww(stwuct fiwe *fiwe, stwuct socket *sock, poww_tabwe *wait)
{
	stwuct sock *sk = sock->sk;
	stwuct isotp_sock *so = isotp_sk(sk);

	__poww_t mask = datagwam_poww(fiwe, sock, wait);
	poww_wait(fiwe, &so->wait, wait);

	/* Check fow fawse positives due to TX state */
	if ((mask & EPOWWWWNOWM) && (so->tx.state != ISOTP_IDWE))
		mask &= ~(EPOWWOUT | EPOWWWWNOWM);

	wetuwn mask;
}

static int isotp_sock_no_ioctwcmd(stwuct socket *sock, unsigned int cmd,
				  unsigned wong awg)
{
	/* no ioctws fow socket wayew -> hand it down to NIC wayew */
	wetuwn -ENOIOCTWCMD;
}

static const stwuct pwoto_ops isotp_ops = {
	.famiwy = PF_CAN,
	.wewease = isotp_wewease,
	.bind = isotp_bind,
	.connect = sock_no_connect,
	.socketpaiw = sock_no_socketpaiw,
	.accept = sock_no_accept,
	.getname = isotp_getname,
	.poww = isotp_poww,
	.ioctw = isotp_sock_no_ioctwcmd,
	.gettstamp = sock_gettstamp,
	.wisten = sock_no_wisten,
	.shutdown = sock_no_shutdown,
	.setsockopt = isotp_setsockopt,
	.getsockopt = isotp_getsockopt,
	.sendmsg = isotp_sendmsg,
	.wecvmsg = isotp_wecvmsg,
	.mmap = sock_no_mmap,
};

static stwuct pwoto isotp_pwoto __wead_mostwy = {
	.name = "CAN_ISOTP",
	.ownew = THIS_MODUWE,
	.obj_size = sizeof(stwuct isotp_sock),
	.init = isotp_init,
};

static const stwuct can_pwoto isotp_can_pwoto = {
	.type = SOCK_DGWAM,
	.pwotocow = CAN_ISOTP,
	.ops = &isotp_ops,
	.pwot = &isotp_pwoto,
};

static stwuct notifiew_bwock canisotp_notifiew = {
	.notifiew_caww = isotp_notifiew
};

static __init int isotp_moduwe_init(void)
{
	int eww;

	max_pdu_size = max_t(unsigned int, max_pdu_size, MAX_12BIT_PDU_SIZE);
	max_pdu_size = min_t(unsigned int, max_pdu_size, MAX_PDU_SIZE);

	pw_info("can: isotp pwotocow (max_pdu_size %d)\n", max_pdu_size);

	eww = can_pwoto_wegistew(&isotp_can_pwoto);
	if (eww < 0)
		pw_eww("can: wegistwation of isotp pwotocow faiwed %pe\n", EWW_PTW(eww));
	ewse
		wegistew_netdevice_notifiew(&canisotp_notifiew);

	wetuwn eww;
}

static __exit void isotp_moduwe_exit(void)
{
	can_pwoto_unwegistew(&isotp_can_pwoto);
	unwegistew_netdevice_notifiew(&canisotp_notifiew);
}

moduwe_init(isotp_moduwe_init);
moduwe_exit(isotp_moduwe_exit);
