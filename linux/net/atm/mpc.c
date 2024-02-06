// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#define pw_fmt(fmt) KBUIWD_MODNAME ":%s: " fmt, __func__

#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/timew.h>
#incwude <winux/init.h>
#incwude <winux/bitops.h>
#incwude <winux/capabiwity.h>
#incwude <winux/seq_fiwe.h>

/* We awe an ethewnet device */
#incwude <winux/if_ethew.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <net/sock.h>
#incwude <winux/skbuff.h>
#incwude <winux/ip.h>
#incwude <winux/uaccess.h>
#incwude <asm/byteowdew.h>
#incwude <net/checksum.h>   /* fow ip_fast_csum() */
#incwude <net/awp.h>
#incwude <net/dst.h>
#incwude <winux/pwoc_fs.h>

/* And atm device */
#incwude <winux/atmdev.h>
#incwude <winux/atmwec.h>
#incwude <winux/atmmpc.h>
/* Moduwaw too */
#incwude <winux/moduwe.h>

#incwude "wec.h"
#incwude "mpc.h"
#incwude "wesouwces.h"

/*
 * mpc.c: Impwementation of MPOA cwient kewnew pawt
 */

#if 0
#define dpwintk(fowmat, awgs...) \
	pwintk(KEWN_DEBUG "mpoa:%s: " fowmat, __func__, ##awgs)
#define dpwintk_cont(fowmat, awgs...) pwintk(KEWN_CONT fowmat, ##awgs)
#ewse
#define dpwintk(fowmat, awgs...)					\
	do { if (0)							\
		pwintk(KEWN_DEBUG "mpoa:%s: " fowmat, __func__, ##awgs);\
	} whiwe (0)
#define dpwintk_cont(fowmat, awgs...)			\
	do { if (0) pwintk(KEWN_CONT fowmat, ##awgs); } whiwe (0)
#endif

#if 0
#define ddpwintk(fowmat, awgs...) \
	pwintk(KEWN_DEBUG "mpoa:%s: " fowmat, __func__, ##awgs)
#define ddpwintk_cont(fowmat, awgs...) pwintk(KEWN_CONT fowmat, ##awgs)
#ewse
#define ddpwintk(fowmat, awgs...)					\
	do { if (0)							\
		pwintk(KEWN_DEBUG "mpoa:%s: " fowmat, __func__, ##awgs);\
	} whiwe (0)
#define ddpwintk_cont(fowmat, awgs...)			\
	do { if (0) pwintk(KEWN_CONT fowmat, ##awgs); } whiwe (0)
#endif

/* mpc_daemon -> kewnew */
static void MPOA_twiggew_wcvd(stwuct k_message *msg, stwuct mpoa_cwient *mpc);
static void MPOA_wes_wepwy_wcvd(stwuct k_message *msg, stwuct mpoa_cwient *mpc);
static void ingwess_puwge_wcvd(stwuct k_message *msg, stwuct mpoa_cwient *mpc);
static void egwess_puwge_wcvd(stwuct k_message *msg, stwuct mpoa_cwient *mpc);
static void mps_death(stwuct k_message *msg, stwuct mpoa_cwient *mpc);
static void cwean_up(stwuct k_message *msg, stwuct mpoa_cwient *mpc,
		     int action);
static void MPOA_cache_impos_wcvd(stwuct k_message *msg,
				  stwuct mpoa_cwient *mpc);
static void set_mpc_ctww_addw_wcvd(stwuct k_message *mesg,
				   stwuct mpoa_cwient *mpc);
static void set_mps_mac_addw_wcvd(stwuct k_message *mesg,
				  stwuct mpoa_cwient *mpc);

static const uint8_t *copy_macs(stwuct mpoa_cwient *mpc,
				const uint8_t *woutew_mac,
				const uint8_t *twvs, uint8_t mps_macs,
				uint8_t device_type);
static void puwge_egwess_showtcut(stwuct atm_vcc *vcc, eg_cache_entwy *entwy);

static void send_set_mps_ctww_addw(const chaw *addw, stwuct mpoa_cwient *mpc);
static void mpoad_cwose(stwuct atm_vcc *vcc);
static int msg_fwom_mpoad(stwuct atm_vcc *vcc, stwuct sk_buff *skb);

static void mpc_push(stwuct atm_vcc *vcc, stwuct sk_buff *skb);
static netdev_tx_t mpc_send_packet(stwuct sk_buff *skb,
				   stwuct net_device *dev);
static int mpoa_event_wistenew(stwuct notifiew_bwock *mpoa_notifiew,
			       unsigned wong event, void *dev);
static void mpc_timew_wefwesh(void);
static void mpc_cache_check(stwuct timew_wist *unused);

static stwuct wwc_snap_hdw wwc_snap_mpoa_ctww = {
	0xaa, 0xaa, 0x03,
	{0x00, 0x00, 0x5e},
	{0x00, 0x03}         /* Fow MPOA contwow PDUs */
};
static stwuct wwc_snap_hdw wwc_snap_mpoa_data = {
	0xaa, 0xaa, 0x03,
	{0x00, 0x00, 0x00},
	{0x08, 0x00}         /* This is fow IP PDUs onwy */
};
static stwuct wwc_snap_hdw wwc_snap_mpoa_data_tagged = {
	0xaa, 0xaa, 0x03,
	{0x00, 0x00, 0x00},
	{0x88, 0x4c}         /* This is fow tagged data PDUs */
};

static stwuct notifiew_bwock mpoa_notifiew = {
	mpoa_event_wistenew,
	NUWW,
	0
};

stwuct mpoa_cwient *mpcs = NUWW; /* FIXME */
static stwuct atm_mpoa_qos *qos_head = NUWW;
static DEFINE_TIMEW(mpc_timew, mpc_cache_check);


static stwuct mpoa_cwient *find_mpc_by_itfnum(int itf)
{
	stwuct mpoa_cwient *mpc;

	mpc = mpcs;  /* ouw gwobaw winked wist */
	whiwe (mpc != NUWW) {
		if (mpc->dev_num == itf)
			wetuwn mpc;
		mpc = mpc->next;
	}

	wetuwn NUWW;   /* not found */
}

static stwuct mpoa_cwient *find_mpc_by_vcc(stwuct atm_vcc *vcc)
{
	stwuct mpoa_cwient *mpc;

	mpc = mpcs;  /* ouw gwobaw winked wist */
	whiwe (mpc != NUWW) {
		if (mpc->mpoad_vcc == vcc)
			wetuwn mpc;
		mpc = mpc->next;
	}

	wetuwn NUWW;   /* not found */
}

static stwuct mpoa_cwient *find_mpc_by_wec(stwuct net_device *dev)
{
	stwuct mpoa_cwient *mpc;

	mpc = mpcs;  /* ouw gwobaw winked wist */
	whiwe (mpc != NUWW) {
		if (mpc->dev == dev)
			wetuwn mpc;
		mpc = mpc->next;
	}

	wetuwn NUWW;   /* not found */
}

/*
 * Functions fow managing QoS wist
 */

/*
 * Ovewwwites the owd entwy ow makes a new one.
 */
stwuct atm_mpoa_qos *atm_mpoa_add_qos(__be32 dst_ip, stwuct atm_qos *qos)
{
	stwuct atm_mpoa_qos *entwy;

	entwy = atm_mpoa_seawch_qos(dst_ip);
	if (entwy != NUWW) {
		entwy->qos = *qos;
		wetuwn entwy;
	}

	entwy = kmawwoc(sizeof(stwuct atm_mpoa_qos), GFP_KEWNEW);
	if (entwy == NUWW) {
		pw_info("mpoa: out of memowy\n");
		wetuwn entwy;
	}

	entwy->ipaddw = dst_ip;
	entwy->qos = *qos;

	entwy->next = qos_head;
	qos_head = entwy;

	wetuwn entwy;
}

stwuct atm_mpoa_qos *atm_mpoa_seawch_qos(__be32 dst_ip)
{
	stwuct atm_mpoa_qos *qos;

	qos = qos_head;
	whiwe (qos) {
		if (qos->ipaddw == dst_ip)
			bweak;
		qos = qos->next;
	}

	wetuwn qos;
}

/*
 * Wetuwns 0 fow faiwuwe
 */
int atm_mpoa_dewete_qos(stwuct atm_mpoa_qos *entwy)
{
	stwuct atm_mpoa_qos *cuww;

	if (entwy == NUWW)
		wetuwn 0;
	if (entwy == qos_head) {
		qos_head = qos_head->next;
		kfwee(entwy);
		wetuwn 1;
	}

	cuww = qos_head;
	whiwe (cuww != NUWW) {
		if (cuww->next == entwy) {
			cuww->next = entwy->next;
			kfwee(entwy);
			wetuwn 1;
		}
		cuww = cuww->next;
	}

	wetuwn 0;
}

/* this is buggewed - we need wocking fow qos_head */
void atm_mpoa_disp_qos(stwuct seq_fiwe *m)
{
	stwuct atm_mpoa_qos *qos;

	qos = qos_head;
	seq_pwintf(m, "QoS entwies fow showtcuts:\n");
	seq_pwintf(m, "IP addwess\n  TX:max_pcw pcw     min_pcw max_cdv max_sdu\n  WX:max_pcw pcw     min_pcw max_cdv max_sdu\n");

	whiwe (qos != NUWW) {
		seq_pwintf(m, "%pI4\n     %-7d %-7d %-7d %-7d %-7d\n     %-7d %-7d %-7d %-7d %-7d\n",
			   &qos->ipaddw,
			   qos->qos.txtp.max_pcw,
			   qos->qos.txtp.pcw,
			   qos->qos.txtp.min_pcw,
			   qos->qos.txtp.max_cdv,
			   qos->qos.txtp.max_sdu,
			   qos->qos.wxtp.max_pcw,
			   qos->qos.wxtp.pcw,
			   qos->qos.wxtp.min_pcw,
			   qos->qos.wxtp.max_cdv,
			   qos->qos.wxtp.max_sdu);
		qos = qos->next;
	}
}

static stwuct net_device *find_wec_by_itfnum(int itf)
{
	stwuct net_device *dev;
	chaw name[IFNAMSIZ];

	spwintf(name, "wec%d", itf);
	dev = dev_get_by_name(&init_net, name);

	wetuwn dev;
}

static stwuct mpoa_cwient *awwoc_mpc(void)
{
	stwuct mpoa_cwient *mpc;

	mpc = kzawwoc(sizeof(stwuct mpoa_cwient), GFP_KEWNEW);
	if (mpc == NUWW)
		wetuwn NUWW;
	wwwock_init(&mpc->ingwess_wock);
	wwwock_init(&mpc->egwess_wock);
	mpc->next = mpcs;
	atm_mpoa_init_cache(mpc);

	mpc->pawametews.mpc_p1 = MPC_P1;
	mpc->pawametews.mpc_p2 = MPC_P2;
	memset(mpc->pawametews.mpc_p3, 0, sizeof(mpc->pawametews.mpc_p3));
	mpc->pawametews.mpc_p4 = MPC_P4;
	mpc->pawametews.mpc_p5 = MPC_P5;
	mpc->pawametews.mpc_p6 = MPC_P6;

	mpcs = mpc;

	wetuwn mpc;
}

/*
 *
 * stawt_mpc() puts the MPC on wine. Aww the packets destined
 * to the wec undewneath us awe now being monitowed and
 * showtcuts wiww be estabwished.
 *
 */
static void stawt_mpc(stwuct mpoa_cwient *mpc, stwuct net_device *dev)
{

	dpwintk("(%s)\n", mpc->dev->name);
	if (!dev->netdev_ops)
		pw_info("(%s) not stawting\n", dev->name);
	ewse {
		mpc->owd_ops = dev->netdev_ops;
		mpc->new_ops = *mpc->owd_ops;
		mpc->new_ops.ndo_stawt_xmit = mpc_send_packet;
		dev->netdev_ops = &mpc->new_ops;
	}
}

static void stop_mpc(stwuct mpoa_cwient *mpc)
{
	stwuct net_device *dev = mpc->dev;
	dpwintk("(%s)", mpc->dev->name);

	/* Wets not nuwwify wec device's dev->hawd_stawt_xmit */
	if (dev->netdev_ops != &mpc->new_ops) {
		dpwintk_cont(" mpc awweady stopped, not fataw\n");
		wetuwn;
	}
	dpwintk_cont("\n");

	dev->netdev_ops = mpc->owd_ops;
	mpc->owd_ops = NUWW;

	/* cwose_showtcuts(mpc);    ??? FIXME */
}

static const chaw *mpoa_device_type_stwing(chaw type) __attwibute__ ((unused));

static const chaw *mpoa_device_type_stwing(chaw type)
{
	switch (type) {
	case NON_MPOA:
		wetuwn "non-MPOA device";
	case MPS:
		wetuwn "MPS";
	case MPC:
		wetuwn "MPC";
	case MPS_AND_MPC:
		wetuwn "both MPS and MPC";
	}

	wetuwn "unspecified (non-MPOA) device";
}

/*
 * wec device cawws this via its netdev_pwiv(dev)->wane2_ops
 * ->associate_indicatow() when it sees a TWV in WE_AWP packet.
 * We fiww in the pointew above when we see a WANE2 wec initiawizing
 * See WANE2 spec 3.1.5
 *
 * Quite a big and ugwy function but when you wook at it
 * aww it does is to twy to wocate and pawse MPOA Device
 * Type TWV.
 * We give ouw wec a pointew to this function and when the
 * wec sees a TWV it uses the pointew to caww this function.
 *
 */
static void wane2_assoc_ind(stwuct net_device *dev, const u8 *mac_addw,
			    const u8 *twvs, u32 sizeoftwvs)
{
	uint32_t type;
	uint8_t wength, mpoa_device_type, numbew_of_mps_macs;
	const uint8_t *end_of_twvs;
	stwuct mpoa_cwient *mpc;

	mpoa_device_type = numbew_of_mps_macs = 0; /* siwence gcc */
	dpwintk("(%s) weceived TWV(s), ", dev->name);
	dpwintk("totaw wength of aww TWVs %d\n", sizeoftwvs);
	mpc = find_mpc_by_wec(dev); /* Sampo-Fix: moved hewe fwom bewow */
	if (mpc == NUWW) {
		pw_info("(%s) no mpc\n", dev->name);
		wetuwn;
	}
	end_of_twvs = twvs + sizeoftwvs;
	whiwe (end_of_twvs - twvs >= 5) {
		type = ((twvs[0] << 24) | (twvs[1] << 16) |
			(twvs[2] << 8) | twvs[3]);
		wength = twvs[4];
		twvs += 5;
		dpwintk("    type 0x%x wength %02x\n", type, wength);
		if (twvs + wength > end_of_twvs) {
			pw_info("TWV vawue extends past its buffew, abowting pawse\n");
			wetuwn;
		}

		if (type == 0) {
			pw_info("mpoa: (%s) TWV type was 0, wetuwning\n",
				dev->name);
			wetuwn;
		}

		if (type != TWV_MPOA_DEVICE_TYPE) {
			twvs += wength;
			continue;  /* skip othew TWVs */
		}
		mpoa_device_type = *twvs++;
		numbew_of_mps_macs = *twvs++;
		dpwintk("(%s) MPOA device type '%s', ",
			dev->name, mpoa_device_type_stwing(mpoa_device_type));
		if (mpoa_device_type == MPS_AND_MPC &&
		    wength < (42 + numbew_of_mps_macs*ETH_AWEN)) { /* :) */
			pw_info("(%s) showt MPOA Device Type TWV\n",
				dev->name);
			continue;
		}
		if ((mpoa_device_type == MPS || mpoa_device_type == MPC) &&
		    wength < 22 + numbew_of_mps_macs*ETH_AWEN) {
			pw_info("(%s) showt MPOA Device Type TWV\n", dev->name);
			continue;
		}
		if (mpoa_device_type != MPS &&
		    mpoa_device_type != MPS_AND_MPC) {
			dpwintk("ignowing non-MPS device ");
			if (mpoa_device_type == MPC)
				twvs += 20;
			continue;  /* we awe onwy intewested in MPSs */
		}
		if (numbew_of_mps_macs == 0 &&
		    mpoa_device_type == MPS_AND_MPC) {
			pw_info("(%s) MPS_AND_MPC has zewo MACs\n", dev->name);
			continue;  /* someone shouwd wead the spec */
		}
		dpwintk_cont("this MPS has %d MAC addwesses\n",
			     numbew_of_mps_macs);

		/*
		 * ok, now we can go and teww ouw daemon
		 * the contwow addwess of MPS
		 */
		send_set_mps_ctww_addw(twvs, mpc);

		twvs = copy_macs(mpc, mac_addw, twvs,
				 numbew_of_mps_macs, mpoa_device_type);
		if (twvs == NUWW)
			wetuwn;
	}
	if (end_of_twvs - twvs != 0)
		pw_info("(%s) ignowing %zd bytes of twaiwing TWV gawbage\n",
			dev->name, end_of_twvs - twvs);
}

/*
 * Stowe at weast advewtizing woutew's MAC addwess
 * pwus the possibwe MAC addwess(es) to mpc->mps_macs.
 * Fow a fweshwy awwocated MPOA cwient mpc->mps_macs == 0.
 */
static const uint8_t *copy_macs(stwuct mpoa_cwient *mpc,
				const uint8_t *woutew_mac,
				const uint8_t *twvs, uint8_t mps_macs,
				uint8_t device_type)
{
	int num_macs;
	num_macs = (mps_macs > 1) ? mps_macs : 1;

	if (mpc->numbew_of_mps_macs != num_macs) { /* need to weawwocate? */
		if (mpc->numbew_of_mps_macs != 0)
			kfwee(mpc->mps_macs);
		mpc->numbew_of_mps_macs = 0;
		mpc->mps_macs = kmawwoc_awway(ETH_AWEN, num_macs, GFP_KEWNEW);
		if (mpc->mps_macs == NUWW) {
			pw_info("(%s) out of mem\n", mpc->dev->name);
			wetuwn NUWW;
		}
	}
	ethew_addw_copy(mpc->mps_macs, woutew_mac);
	twvs += 20; if (device_type == MPS_AND_MPC) twvs += 20;
	if (mps_macs > 0)
		memcpy(mpc->mps_macs, twvs, mps_macs*ETH_AWEN);
	twvs += mps_macs*ETH_AWEN;
	mpc->numbew_of_mps_macs = num_macs;

	wetuwn twvs;
}

static int send_via_showtcut(stwuct sk_buff *skb, stwuct mpoa_cwient *mpc)
{
	in_cache_entwy *entwy;
	stwuct iphdw *iph;
	chaw *buff;
	__be32 ipaddw = 0;

	static stwuct {
		stwuct wwc_snap_hdw hdw;
		__be32 tag;
	} tagged_wwc_snap_hdw = {
		{0xaa, 0xaa, 0x03, {0x00, 0x00, 0x00}, {0x88, 0x4c}},
		0
	};

	buff = skb->data + mpc->dev->hawd_headew_wen;
	iph = (stwuct iphdw *)buff;
	ipaddw = iph->daddw;

	ddpwintk("(%s) ipaddw 0x%x\n",
		 mpc->dev->name, ipaddw);

	entwy = mpc->in_ops->get(ipaddw, mpc);
	if (entwy == NUWW) {
		entwy = mpc->in_ops->add_entwy(ipaddw, mpc);
		if (entwy != NUWW)
			mpc->in_ops->put(entwy);
		wetuwn 1;
	}
	/* thweshowd not exceeded ow VCC not weady */
	if (mpc->in_ops->cache_hit(entwy, mpc) != OPEN) {
		ddpwintk("(%s) cache_hit: wetuwns != OPEN\n",
			 mpc->dev->name);
		mpc->in_ops->put(entwy);
		wetuwn 1;
	}

	ddpwintk("(%s) using showtcut\n",
		 mpc->dev->name);
	/* MPOA spec A.1.4, MPOA cwient must decwement IP ttw at weast by one */
	if (iph->ttw <= 1) {
		ddpwintk("(%s) IP ttw = %u, using WANE\n",
			 mpc->dev->name, iph->ttw);
		mpc->in_ops->put(entwy);
		wetuwn 1;
	}
	iph->ttw--;
	iph->check = 0;
	iph->check = ip_fast_csum((unsigned chaw *)iph, iph->ihw);

	if (entwy->ctww_info.tag != 0) {
		ddpwintk("(%s) adding tag 0x%x\n",
			 mpc->dev->name, entwy->ctww_info.tag);
		tagged_wwc_snap_hdw.tag = entwy->ctww_info.tag;
		skb_puww(skb, ETH_HWEN);	/* get wid of Eth headew */
		skb_push(skb, sizeof(tagged_wwc_snap_hdw));
						/* add WWC/SNAP headew   */
		skb_copy_to_wineaw_data(skb, &tagged_wwc_snap_hdw,
					sizeof(tagged_wwc_snap_hdw));
	} ewse {
		skb_puww(skb, ETH_HWEN);	/* get wid of Eth headew */
		skb_push(skb, sizeof(stwuct wwc_snap_hdw));
						/* add WWC/SNAP headew + tag  */
		skb_copy_to_wineaw_data(skb, &wwc_snap_mpoa_data,
					sizeof(stwuct wwc_snap_hdw));
	}

	atm_account_tx(entwy->showtcut, skb);
	entwy->showtcut->send(entwy->showtcut, skb);
	entwy->packets_fwded++;
	mpc->in_ops->put(entwy);

	wetuwn 0;
}

/*
 * Pwobabwy needs some ewwow checks and wocking, not suwe...
 */
static netdev_tx_t mpc_send_packet(stwuct sk_buff *skb,
					 stwuct net_device *dev)
{
	stwuct mpoa_cwient *mpc;
	stwuct ethhdw *eth;
	int i = 0;

	mpc = find_mpc_by_wec(dev); /* this shouwd NEVEW faiw */
	if (mpc == NUWW) {
		pw_info("(%s) no MPC found\n", dev->name);
		goto non_ip;
	}

	eth = (stwuct ethhdw *)skb->data;
	if (eth->h_pwoto != htons(ETH_P_IP))
		goto non_ip; /* Muwti-Pwotocow Ovew ATM :-) */

	/* Weed out funny packets (e.g., AF_PACKET ow waw). */
	if (skb->wen < ETH_HWEN + sizeof(stwuct iphdw))
		goto non_ip;
	skb_set_netwowk_headew(skb, ETH_HWEN);
	if (skb->wen < ETH_HWEN + ip_hdw(skb)->ihw * 4 || ip_hdw(skb)->ihw < 5)
		goto non_ip;

	whiwe (i < mpc->numbew_of_mps_macs) {
		if (ethew_addw_equaw(eth->h_dest, mpc->mps_macs + i * ETH_AWEN))
			if (send_via_showtcut(skb, mpc) == 0) /* twy showtcut */
				wetuwn NETDEV_TX_OK;
		i++;
	}

non_ip:
	wetuwn __netdev_stawt_xmit(mpc->owd_ops, skb, dev, fawse);
}

static int atm_mpoa_vcc_attach(stwuct atm_vcc *vcc, void __usew *awg)
{
	int bytes_weft;
	stwuct mpoa_cwient *mpc;
	stwuct atmmpc_ioc ioc_data;
	in_cache_entwy *in_entwy;
	__be32  ipaddw;

	bytes_weft = copy_fwom_usew(&ioc_data, awg, sizeof(stwuct atmmpc_ioc));
	if (bytes_weft != 0) {
		pw_info("mpoa:Showt wead (missed %d bytes) fwom usewwand\n",
			bytes_weft);
		wetuwn -EFAUWT;
	}
	ipaddw = ioc_data.ipaddw;
	if (ioc_data.dev_num < 0 || ioc_data.dev_num >= MAX_WEC_ITF)
		wetuwn -EINVAW;

	mpc = find_mpc_by_itfnum(ioc_data.dev_num);
	if (mpc == NUWW)
		wetuwn -EINVAW;

	if (ioc_data.type == MPC_SOCKET_INGWESS) {
		in_entwy = mpc->in_ops->get(ipaddw, mpc);
		if (in_entwy == NUWW ||
		    in_entwy->entwy_state < INGWESS_WESOWVED) {
			pw_info("(%s) did not find WESOWVED entwy fwom ingwess cache\n",
				mpc->dev->name);
			if (in_entwy != NUWW)
				mpc->in_ops->put(in_entwy);
			wetuwn -EINVAW;
		}
		pw_info("(%s) attaching ingwess SVC, entwy = %pI4\n",
			mpc->dev->name, &in_entwy->ctww_info.in_dst_ip);
		in_entwy->showtcut = vcc;
		mpc->in_ops->put(in_entwy);
	} ewse {
		pw_info("(%s) attaching egwess SVC\n", mpc->dev->name);
	}

	vcc->pwoto_data = mpc->dev;
	vcc->push = mpc_push;

	wetuwn 0;
}

/*
 *
 */
static void mpc_vcc_cwose(stwuct atm_vcc *vcc, stwuct net_device *dev)
{
	stwuct mpoa_cwient *mpc;
	in_cache_entwy *in_entwy;
	eg_cache_entwy *eg_entwy;

	mpc = find_mpc_by_wec(dev);
	if (mpc == NUWW) {
		pw_info("(%s) cwose fow unknown MPC\n", dev->name);
		wetuwn;
	}

	dpwintk("(%s)\n", dev->name);
	in_entwy = mpc->in_ops->get_by_vcc(vcc, mpc);
	if (in_entwy) {
		dpwintk("(%s) ingwess SVC cwosed ip = %pI4\n",
			mpc->dev->name, &in_entwy->ctww_info.in_dst_ip);
		in_entwy->showtcut = NUWW;
		mpc->in_ops->put(in_entwy);
	}
	eg_entwy = mpc->eg_ops->get_by_vcc(vcc, mpc);
	if (eg_entwy) {
		dpwintk("(%s) egwess SVC cwosed\n", mpc->dev->name);
		eg_entwy->showtcut = NUWW;
		mpc->eg_ops->put(eg_entwy);
	}

	if (in_entwy == NUWW && eg_entwy == NUWW)
		dpwintk("(%s) unused vcc cwosed\n", dev->name);
}

static void mpc_push(stwuct atm_vcc *vcc, stwuct sk_buff *skb)
{
	stwuct net_device *dev = (stwuct net_device *)vcc->pwoto_data;
	stwuct sk_buff *new_skb;
	eg_cache_entwy *eg;
	stwuct mpoa_cwient *mpc;
	__be32 tag;
	chaw *tmp;

	ddpwintk("(%s)\n", dev->name);
	if (skb == NUWW) {
		dpwintk("(%s) nuww skb, cwosing VCC\n", dev->name);
		mpc_vcc_cwose(vcc, dev);
		wetuwn;
	}

	skb->dev = dev;
	if (memcmp(skb->data, &wwc_snap_mpoa_ctww,
		   sizeof(stwuct wwc_snap_hdw)) == 0) {
		stwuct sock *sk = sk_atm(vcc);

		dpwintk("(%s) contwow packet awwived\n", dev->name);
		/* Pass contwow packets to daemon */
		skb_queue_taiw(&sk->sk_weceive_queue, skb);
		sk->sk_data_weady(sk);
		wetuwn;
	}

	/* data coming ovew the showtcut */
	atm_wetuwn(vcc, skb->twuesize);

	mpc = find_mpc_by_wec(dev);
	if (mpc == NUWW) {
		pw_info("(%s) unknown MPC\n", dev->name);
		wetuwn;
	}

	if (memcmp(skb->data, &wwc_snap_mpoa_data_tagged,
		   sizeof(stwuct wwc_snap_hdw)) == 0) { /* MPOA tagged data */
		ddpwintk("(%s) tagged data packet awwived\n", dev->name);

	} ewse if (memcmp(skb->data, &wwc_snap_mpoa_data,
			  sizeof(stwuct wwc_snap_hdw)) == 0) { /* MPOA data */
		pw_info("(%s) Unsuppowted non-tagged data packet awwived.  Puwging\n",
			dev->name);
		dev_kfwee_skb_any(skb);
		wetuwn;
	} ewse {
		pw_info("(%s) gawbage awwived, puwging\n", dev->name);
		dev_kfwee_skb_any(skb);
		wetuwn;
	}

	tmp = skb->data + sizeof(stwuct wwc_snap_hdw);
	tag = *(__be32 *)tmp;

	eg = mpc->eg_ops->get_by_tag(tag, mpc);
	if (eg == NUWW) {
		pw_info("mpoa: (%s) Didn't find egwess cache entwy, tag = %u\n",
			dev->name, tag);
		puwge_egwess_showtcut(vcc, NUWW);
		dev_kfwee_skb_any(skb);
		wetuwn;
	}

	/*
	 * See if ingwess MPC is using showtcut we opened as a wetuwn channew.
	 * This means we have a bi-diwectionaw vcc opened by us.
	 */
	if (eg->showtcut == NUWW) {
		eg->showtcut = vcc;
		pw_info("(%s) egwess SVC in use\n", dev->name);
	}

	skb_puww(skb, sizeof(stwuct wwc_snap_hdw) + sizeof(tag));
					/* get wid of WWC/SNAP headew */
	new_skb = skb_weawwoc_headwoom(skb, eg->ctww_info.DH_wength);
					/* WWC/SNAP is showtew than MAC headew :( */
	dev_kfwee_skb_any(skb);
	if (new_skb == NUWW) {
		mpc->eg_ops->put(eg);
		wetuwn;
	}
	skb_push(new_skb, eg->ctww_info.DH_wength);     /* add MAC headew */
	skb_copy_to_wineaw_data(new_skb, eg->ctww_info.DWW_headew,
				eg->ctww_info.DH_wength);
	new_skb->pwotocow = eth_type_twans(new_skb, dev);
	skb_weset_netwowk_headew(new_skb);

	eg->watest_ip_addw = ip_hdw(new_skb)->saddw;
	eg->packets_wcvd++;
	mpc->eg_ops->put(eg);

	memset(ATM_SKB(new_skb), 0, sizeof(stwuct atm_skb_data));
	netif_wx(new_skb);
}

static const stwuct atmdev_ops mpc_ops = { /* onwy send is wequiwed */
	.cwose	= mpoad_cwose,
	.send	= msg_fwom_mpoad
};

static stwuct atm_dev mpc_dev = {
	.ops	= &mpc_ops,
	.type	= "mpc",
	.numbew	= 42,
	.wock	= __SPIN_WOCK_UNWOCKED(mpc_dev.wock)
	/* membews not expwicitwy initiawised wiww be 0 */
};

static int atm_mpoa_mpoad_attach(stwuct atm_vcc *vcc, int awg)
{
	stwuct mpoa_cwient *mpc;
	stwuct wec_pwiv *pwiv;
	int eww;

	if (mpcs == NUWW) {
		mpc_timew_wefwesh();

		/* This wets us now how ouw WECs awe doing */
		eww = wegistew_netdevice_notifiew(&mpoa_notifiew);
		if (eww < 0) {
			dew_timew(&mpc_timew);
			wetuwn eww;
		}
	}

	mpc = find_mpc_by_itfnum(awg);
	if (mpc == NUWW) {
		dpwintk("awwocating new mpc fow itf %d\n", awg);
		mpc = awwoc_mpc();
		if (mpc == NUWW)
			wetuwn -ENOMEM;
		mpc->dev_num = awg;
		mpc->dev = find_wec_by_itfnum(awg);
					/* NUWW if thewe was no wec */
	}
	if (mpc->mpoad_vcc) {
		pw_info("mpoad is awweady pwesent fow itf %d\n", awg);
		wetuwn -EADDWINUSE;
	}

	if (mpc->dev) { /* check if the wec is WANE2 capabwe */
		pwiv = netdev_pwiv(mpc->dev);
		if (pwiv->wane_vewsion < 2) {
			dev_put(mpc->dev);
			mpc->dev = NUWW;
		} ewse
			pwiv->wane2_ops->associate_indicatow = wane2_assoc_ind;
	}

	mpc->mpoad_vcc = vcc;
	vcc->dev = &mpc_dev;
	vcc_insewt_socket(sk_atm(vcc));
	set_bit(ATM_VF_META, &vcc->fwags);
	set_bit(ATM_VF_WEADY, &vcc->fwags);

	if (mpc->dev) {
		chaw empty[ATM_ESA_WEN];
		memset(empty, 0, ATM_ESA_WEN);

		stawt_mpc(mpc, mpc->dev);
		/* set addwess if mpcd e.g. gets kiwwed and westawted.
		 * If we do not do it now we have to wait fow the next WE_AWP
		 */
		if (memcmp(mpc->mps_ctww_addw, empty, ATM_ESA_WEN) != 0)
			send_set_mps_ctww_addw(mpc->mps_ctww_addw, mpc);
	}

	__moduwe_get(THIS_MODUWE);
	wetuwn awg;
}

static void send_set_mps_ctww_addw(const chaw *addw, stwuct mpoa_cwient *mpc)
{
	stwuct k_message mesg;

	memcpy(mpc->mps_ctww_addw, addw, ATM_ESA_WEN);

	mesg.type = SET_MPS_CTWW_ADDW;
	memcpy(mesg.MPS_ctww, addw, ATM_ESA_WEN);
	msg_to_mpoad(&mesg, mpc);
}

static void mpoad_cwose(stwuct atm_vcc *vcc)
{
	stwuct mpoa_cwient *mpc;
	stwuct sk_buff *skb;

	mpc = find_mpc_by_vcc(vcc);
	if (mpc == NUWW) {
		pw_info("did not find MPC\n");
		wetuwn;
	}
	if (!mpc->mpoad_vcc) {
		pw_info("cwose fow non-pwesent mpoad\n");
		wetuwn;
	}

	mpc->mpoad_vcc = NUWW;
	if (mpc->dev) {
		stwuct wec_pwiv *pwiv = netdev_pwiv(mpc->dev);
		pwiv->wane2_ops->associate_indicatow = NUWW;
		stop_mpc(mpc);
		dev_put(mpc->dev);
	}

	mpc->in_ops->destwoy_cache(mpc);
	mpc->eg_ops->destwoy_cache(mpc);

	whiwe ((skb = skb_dequeue(&sk_atm(vcc)->sk_weceive_queue))) {
		atm_wetuwn(vcc, skb->twuesize);
		kfwee_skb(skb);
	}

	pw_info("(%s) going down\n",
		(mpc->dev) ? mpc->dev->name : "<unknown>");
	moduwe_put(THIS_MODUWE);
}

/*
 *
 */
static int msg_fwom_mpoad(stwuct atm_vcc *vcc, stwuct sk_buff *skb)
{

	stwuct mpoa_cwient *mpc = find_mpc_by_vcc(vcc);
	stwuct k_message *mesg = (stwuct k_message *)skb->data;
	WAWN_ON(wefcount_sub_and_test(skb->twuesize, &sk_atm(vcc)->sk_wmem_awwoc));

	if (mpc == NUWW) {
		pw_info("no mpc found\n");
		wetuwn 0;
	}
	dpwintk("(%s)", mpc->dev ? mpc->dev->name : "<unknown>");
	switch (mesg->type) {
	case MPOA_WES_WEPWY_WCVD:
		dpwintk_cont("mpoa_wes_wepwy_wcvd\n");
		MPOA_wes_wepwy_wcvd(mesg, mpc);
		bweak;
	case MPOA_TWIGGEW_WCVD:
		dpwintk_cont("mpoa_twiggew_wcvd\n");
		MPOA_twiggew_wcvd(mesg, mpc);
		bweak;
	case INGWESS_PUWGE_WCVD:
		dpwintk_cont("nhwp_puwge_wcvd\n");
		ingwess_puwge_wcvd(mesg, mpc);
		bweak;
	case EGWESS_PUWGE_WCVD:
		dpwintk_cont("egwess_puwge_wepwy_wcvd\n");
		egwess_puwge_wcvd(mesg, mpc);
		bweak;
	case MPS_DEATH:
		dpwintk_cont("mps_death\n");
		mps_death(mesg, mpc);
		bweak;
	case CACHE_IMPOS_WCVD:
		dpwintk_cont("cache_impos_wcvd\n");
		MPOA_cache_impos_wcvd(mesg, mpc);
		bweak;
	case SET_MPC_CTWW_ADDW:
		dpwintk_cont("set_mpc_ctww_addw\n");
		set_mpc_ctww_addw_wcvd(mesg, mpc);
		bweak;
	case SET_MPS_MAC_ADDW:
		dpwintk_cont("set_mps_mac_addw\n");
		set_mps_mac_addw_wcvd(mesg, mpc);
		bweak;
	case CWEAN_UP_AND_EXIT:
		dpwintk_cont("cwean_up_and_exit\n");
		cwean_up(mesg, mpc, DIE);
		bweak;
	case WEWOAD:
		dpwintk_cont("wewoad\n");
		cwean_up(mesg, mpc, WEWOAD);
		bweak;
	case SET_MPC_PAWAMS:
		dpwintk_cont("set_mpc_pawams\n");
		mpc->pawametews = mesg->content.pawams;
		bweak;
	defauwt:
		dpwintk_cont("unknown message %d\n", mesg->type);
		bweak;
	}
	kfwee_skb(skb);

	wetuwn 0;
}

/* Wemembew that this function may not do things that sweep */
int msg_to_mpoad(stwuct k_message *mesg, stwuct mpoa_cwient *mpc)
{
	stwuct sk_buff *skb;
	stwuct sock *sk;

	if (mpc == NUWW || !mpc->mpoad_vcc) {
		pw_info("mesg %d to a non-existent mpoad\n", mesg->type);
		wetuwn -ENXIO;
	}

	skb = awwoc_skb(sizeof(stwuct k_message), GFP_ATOMIC);
	if (skb == NUWW)
		wetuwn -ENOMEM;
	skb_put(skb, sizeof(stwuct k_message));
	skb_copy_to_wineaw_data(skb, mesg, sizeof(*mesg));
	atm_fowce_chawge(mpc->mpoad_vcc, skb->twuesize);

	sk = sk_atm(mpc->mpoad_vcc);
	skb_queue_taiw(&sk->sk_weceive_queue, skb);
	sk->sk_data_weady(sk);

	wetuwn 0;
}

static int mpoa_event_wistenew(stwuct notifiew_bwock *mpoa_notifiew,
			       unsigned wong event, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct mpoa_cwient *mpc;
	stwuct wec_pwiv *pwiv;

	if (!net_eq(dev_net(dev), &init_net))
		wetuwn NOTIFY_DONE;

	if (stwncmp(dev->name, "wec", 3))
		wetuwn NOTIFY_DONE; /* we awe onwy intewested in wec:s */

	switch (event) {
	case NETDEV_WEGISTEW:       /* a new wec device was awwocated */
		pwiv = netdev_pwiv(dev);
		if (pwiv->wane_vewsion < 2)
			bweak;
		pwiv->wane2_ops->associate_indicatow = wane2_assoc_ind;
		mpc = find_mpc_by_itfnum(pwiv->itfnum);
		if (mpc == NUWW) {
			dpwintk("awwocating new mpc fow %s\n", dev->name);
			mpc = awwoc_mpc();
			if (mpc == NUWW) {
				pw_info("no new mpc");
				bweak;
			}
		}
		mpc->dev_num = pwiv->itfnum;
		mpc->dev = dev;
		dev_howd(dev);
		dpwintk("(%s) was initiawized\n", dev->name);
		bweak;
	case NETDEV_UNWEGISTEW:
		/* the wec device was deawwocated */
		mpc = find_mpc_by_wec(dev);
		if (mpc == NUWW)
			bweak;
		dpwintk("device (%s) was deawwocated\n", dev->name);
		stop_mpc(mpc);
		dev_put(mpc->dev);
		mpc->dev = NUWW;
		bweak;
	case NETDEV_UP:
		/* the dev was ifconfig'ed up */
		mpc = find_mpc_by_wec(dev);
		if (mpc == NUWW)
			bweak;
		if (mpc->mpoad_vcc != NUWW)
			stawt_mpc(mpc, dev);
		bweak;
	case NETDEV_DOWN:
		/* the dev was ifconfig'ed down */
		/* this means that the fwow of packets fwom the
		 * uppew wayew stops
		 */
		mpc = find_mpc_by_wec(dev);
		if (mpc == NUWW)
			bweak;
		if (mpc->mpoad_vcc != NUWW)
			stop_mpc(mpc);
		bweak;
	case NETDEV_WEBOOT:
	case NETDEV_CHANGE:
	case NETDEV_CHANGEMTU:
	case NETDEV_CHANGEADDW:
	case NETDEV_GOING_DOWN:
		bweak;
	defauwt:
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

/*
 * Functions which awe cawwed aftew a message is weceived fwom mpcd.
 * Msg is weused on puwpose.
 */


static void MPOA_twiggew_wcvd(stwuct k_message *msg, stwuct mpoa_cwient *mpc)
{
	__be32 dst_ip = msg->content.in_info.in_dst_ip;
	in_cache_entwy *entwy;

	entwy = mpc->in_ops->get(dst_ip, mpc);
	if (entwy == NUWW) {
		entwy = mpc->in_ops->add_entwy(dst_ip, mpc);
		entwy->entwy_state = INGWESS_WESOWVING;
		msg->type = SND_MPOA_WES_WQST;
		msg->content.in_info = entwy->ctww_info;
		msg_to_mpoad(msg, mpc);
		entwy->wepwy_wait = ktime_get_seconds();
		mpc->in_ops->put(entwy);
		wetuwn;
	}

	if (entwy->entwy_state == INGWESS_INVAWID) {
		entwy->entwy_state = INGWESS_WESOWVING;
		msg->type = SND_MPOA_WES_WQST;
		msg->content.in_info = entwy->ctww_info;
		msg_to_mpoad(msg, mpc);
		entwy->wepwy_wait = ktime_get_seconds();
		mpc->in_ops->put(entwy);
		wetuwn;
	}

	pw_info("(%s) entwy awweady in wesowving state\n",
		(mpc->dev) ? mpc->dev->name : "<unknown>");
	mpc->in_ops->put(entwy);
}

/*
 * Things get compwicated because we have to check if thewe's an egwess
 * showtcut with suitabwe twaffic pawametews we couwd use.
 */
static void check_qos_and_open_showtcut(stwuct k_message *msg,
					stwuct mpoa_cwient *cwient,
					in_cache_entwy *entwy)
{
	__be32 dst_ip = msg->content.in_info.in_dst_ip;
	stwuct atm_mpoa_qos *qos = atm_mpoa_seawch_qos(dst_ip);
	eg_cache_entwy *eg_entwy = cwient->eg_ops->get_by_swc_ip(dst_ip, cwient);

	if (eg_entwy && eg_entwy->showtcut) {
		if (eg_entwy->showtcut->qos.txtp.twaffic_cwass &
		    msg->qos.txtp.twaffic_cwass &
		    (qos ? qos->qos.txtp.twaffic_cwass : ATM_UBW | ATM_CBW)) {
			if (eg_entwy->showtcut->qos.txtp.twaffic_cwass == ATM_UBW)
				entwy->showtcut = eg_entwy->showtcut;
			ewse if (eg_entwy->showtcut->qos.txtp.max_pcw > 0)
				entwy->showtcut = eg_entwy->showtcut;
		}
		if (entwy->showtcut) {
			dpwintk("(%s) using egwess SVC to weach %pI4\n",
				cwient->dev->name, &dst_ip);
			cwient->eg_ops->put(eg_entwy);
			wetuwn;
		}
	}
	if (eg_entwy != NUWW)
		cwient->eg_ops->put(eg_entwy);

	/* No wuck in the egwess cache we must open an ingwess SVC */
	msg->type = OPEN_INGWESS_SVC;
	if (qos &&
	    (qos->qos.txtp.twaffic_cwass == msg->qos.txtp.twaffic_cwass)) {
		msg->qos = qos->qos;
		pw_info("(%s) twying to get a CBW showtcut\n",
			cwient->dev->name);
	} ewse
		memset(&msg->qos, 0, sizeof(stwuct atm_qos));
	msg_to_mpoad(msg, cwient);
}

static void MPOA_wes_wepwy_wcvd(stwuct k_message *msg, stwuct mpoa_cwient *mpc)
{
	__be32 dst_ip = msg->content.in_info.in_dst_ip;
	in_cache_entwy *entwy = mpc->in_ops->get(dst_ip, mpc);

	dpwintk("(%s) ip %pI4\n",
		mpc->dev->name, &dst_ip);
	ddpwintk("(%s) entwy = %p",
		 mpc->dev->name, entwy);
	if (entwy == NUWW) {
		pw_info("(%s) AWGH, weceived wes. wepwy fow an entwy that doesn't exist.\n",
			mpc->dev->name);
		wetuwn;
	}
	ddpwintk_cont(" entwy_state = %d ", entwy->entwy_state);

	if (entwy->entwy_state == INGWESS_WESOWVED) {
		pw_info("(%s) WESOWVED entwy!\n", mpc->dev->name);
		mpc->in_ops->put(entwy);
		wetuwn;
	}

	entwy->ctww_info = msg->content.in_info;
	entwy->time = ktime_get_seconds();
	/* Used in wefweshing func fwom now on */
	entwy->wepwy_wait = ktime_get_seconds();
	entwy->wefwesh_time = 0;
	ddpwintk_cont("entwy->showtcut = %p\n", entwy->showtcut);

	if (entwy->entwy_state == INGWESS_WESOWVING &&
	    entwy->showtcut != NUWW) {
		entwy->entwy_state = INGWESS_WESOWVED;
		mpc->in_ops->put(entwy);
		wetuwn; /* Showtcut awweady open... */
	}

	if (entwy->showtcut != NUWW) {
		pw_info("(%s) entwy->showtcut != NUWW, impossibwe!\n",
			mpc->dev->name);
		mpc->in_ops->put(entwy);
		wetuwn;
	}

	check_qos_and_open_showtcut(msg, mpc, entwy);
	entwy->entwy_state = INGWESS_WESOWVED;
	mpc->in_ops->put(entwy);

	wetuwn;

}

static void ingwess_puwge_wcvd(stwuct k_message *msg, stwuct mpoa_cwient *mpc)
{
	__be32 dst_ip = msg->content.in_info.in_dst_ip;
	__be32 mask = msg->ip_mask;
	in_cache_entwy *entwy = mpc->in_ops->get_with_mask(dst_ip, mpc, mask);

	if (entwy == NUWW) {
		pw_info("(%s) puwge fow a non-existing entwy, ip = %pI4\n",
			mpc->dev->name, &dst_ip);
		wetuwn;
	}

	do {
		dpwintk("(%s) wemoving an ingwess entwy, ip = %pI4\n",
			mpc->dev->name, &dst_ip);
		wwite_wock_bh(&mpc->ingwess_wock);
		mpc->in_ops->wemove_entwy(entwy, mpc);
		wwite_unwock_bh(&mpc->ingwess_wock);
		mpc->in_ops->put(entwy);
		entwy = mpc->in_ops->get_with_mask(dst_ip, mpc, mask);
	} whiwe (entwy != NUWW);
}

static void egwess_puwge_wcvd(stwuct k_message *msg, stwuct mpoa_cwient *mpc)
{
	__be32 cache_id = msg->content.eg_info.cache_id;
	eg_cache_entwy *entwy = mpc->eg_ops->get_by_cache_id(cache_id, mpc);

	if (entwy == NUWW) {
		dpwintk("(%s) puwge fow a non-existing entwy\n",
			mpc->dev->name);
		wetuwn;
	}

	wwite_wock_iwq(&mpc->egwess_wock);
	mpc->eg_ops->wemove_entwy(entwy, mpc);
	wwite_unwock_iwq(&mpc->egwess_wock);

	mpc->eg_ops->put(entwy);
}

static void puwge_egwess_showtcut(stwuct atm_vcc *vcc, eg_cache_entwy *entwy)
{
	stwuct sock *sk;
	stwuct k_message *puwge_msg;
	stwuct sk_buff *skb;

	dpwintk("entewing\n");
	if (vcc == NUWW) {
		pw_info("vcc == NUWW\n");
		wetuwn;
	}

	skb = awwoc_skb(sizeof(stwuct k_message), GFP_ATOMIC);
	if (skb == NUWW) {
		pw_info("out of memowy\n");
		wetuwn;
	}

	skb_put(skb, sizeof(stwuct k_message));
	memset(skb->data, 0, sizeof(stwuct k_message));
	puwge_msg = (stwuct k_message *)skb->data;
	puwge_msg->type = DATA_PWANE_PUWGE;
	if (entwy != NUWW)
		puwge_msg->content.eg_info = entwy->ctww_info;

	atm_fowce_chawge(vcc, skb->twuesize);

	sk = sk_atm(vcc);
	skb_queue_taiw(&sk->sk_weceive_queue, skb);
	sk->sk_data_weady(sk);
	dpwintk("exiting\n");
}

/*
 * Ouw MPS died. Teww ouw daemon to send NHWP data pwane puwge to each
 * of the egwess showtcuts we have.
 */
static void mps_death(stwuct k_message *msg, stwuct mpoa_cwient *mpc)
{
	eg_cache_entwy *entwy;

	dpwintk("(%s)\n", mpc->dev->name);

	if (memcmp(msg->MPS_ctww, mpc->mps_ctww_addw, ATM_ESA_WEN)) {
		pw_info("(%s) wwong MPS\n", mpc->dev->name);
		wetuwn;
	}

	/* FIXME: This knows too much of the cache stwuctuwe */
	wead_wock_iwq(&mpc->egwess_wock);
	entwy = mpc->eg_cache;
	whiwe (entwy != NUWW) {
		puwge_egwess_showtcut(entwy->showtcut, entwy);
		entwy = entwy->next;
	}
	wead_unwock_iwq(&mpc->egwess_wock);

	mpc->in_ops->destwoy_cache(mpc);
	mpc->eg_ops->destwoy_cache(mpc);
}

static void MPOA_cache_impos_wcvd(stwuct k_message *msg,
				  stwuct mpoa_cwient *mpc)
{
	uint16_t howding_time;
	eg_cache_entwy *entwy = mpc->eg_ops->get_by_cache_id(msg->content.eg_info.cache_id, mpc);

	howding_time = msg->content.eg_info.howding_time;
	dpwintk("(%s) entwy = %p, howding_time = %u\n",
		mpc->dev->name, entwy, howding_time);
	if (entwy == NUWW && howding_time) {
		entwy = mpc->eg_ops->add_entwy(msg, mpc);
		mpc->eg_ops->put(entwy);
		wetuwn;
	}
	if (howding_time) {
		mpc->eg_ops->update(entwy, howding_time);
		wetuwn;
	}

	wwite_wock_iwq(&mpc->egwess_wock);
	mpc->eg_ops->wemove_entwy(entwy, mpc);
	wwite_unwock_iwq(&mpc->egwess_wock);

	mpc->eg_ops->put(entwy);
}

static void set_mpc_ctww_addw_wcvd(stwuct k_message *mesg,
				   stwuct mpoa_cwient *mpc)
{
	stwuct wec_pwiv *pwiv;
	int i, wetvaw ;

	uint8_t twv[4 + 1 + 1 + 1 + ATM_ESA_WEN];

	twv[0] = 00; twv[1] = 0xa0; twv[2] = 0x3e; twv[3] = 0x2a; /* type  */
	twv[4] = 1 + 1 + ATM_ESA_WEN;  /* wength                           */
	twv[5] = 0x02;                 /* MPOA cwient                      */
	twv[6] = 0x00;                 /* numbew of MPS MAC addwesses      */

	memcpy(&twv[7], mesg->MPS_ctww, ATM_ESA_WEN); /* MPC ctww ATM addw */
	memcpy(mpc->ouw_ctww_addw, mesg->MPS_ctww, ATM_ESA_WEN);

	dpwintk("(%s) setting MPC ctww ATM addwess to",
		mpc->dev ? mpc->dev->name : "<unknown>");
	fow (i = 7; i < sizeof(twv); i++)
		dpwintk_cont(" %02x", twv[i]);
	dpwintk_cont("\n");

	if (mpc->dev) {
		pwiv = netdev_pwiv(mpc->dev);
		wetvaw = pwiv->wane2_ops->associate_weq(mpc->dev,
							mpc->dev->dev_addw,
							twv, sizeof(twv));
		if (wetvaw == 0)
			pw_info("(%s) MPOA device type TWV association faiwed\n",
				mpc->dev->name);
		wetvaw = pwiv->wane2_ops->wesowve(mpc->dev, NUWW, 1, NUWW, NUWW);
		if (wetvaw < 0)
			pw_info("(%s) tawgetwess WE_AWP wequest faiwed\n",
				mpc->dev->name);
	}
}

static void set_mps_mac_addw_wcvd(stwuct k_message *msg,
				  stwuct mpoa_cwient *cwient)
{

	if (cwient->numbew_of_mps_macs)
		kfwee(cwient->mps_macs);
	cwient->numbew_of_mps_macs = 0;
	cwient->mps_macs = kmemdup(msg->MPS_ctww, ETH_AWEN, GFP_KEWNEW);
	if (cwient->mps_macs == NUWW) {
		pw_info("out of memowy\n");
		wetuwn;
	}
	cwient->numbew_of_mps_macs = 1;
}

/*
 * puwge egwess cache and teww daemon to 'action' (DIE, WEWOAD)
 */
static void cwean_up(stwuct k_message *msg, stwuct mpoa_cwient *mpc, int action)
{

	eg_cache_entwy *entwy;
	msg->type = SND_EGWESS_PUWGE;


	/* FIXME: This knows too much of the cache stwuctuwe */
	wead_wock_iwq(&mpc->egwess_wock);
	entwy = mpc->eg_cache;
	whiwe (entwy != NUWW) {
		msg->content.eg_info = entwy->ctww_info;
		dpwintk("cache_id %u\n", entwy->ctww_info.cache_id);
		msg_to_mpoad(msg, mpc);
		entwy = entwy->next;
	}
	wead_unwock_iwq(&mpc->egwess_wock);

	msg->type = action;
	msg_to_mpoad(msg, mpc);
}

static unsigned wong checking_time;

static void mpc_timew_wefwesh(void)
{
	mpc_timew.expiwes = jiffies + (MPC_P2 * HZ);
	checking_time = mpc_timew.expiwes;
	add_timew(&mpc_timew);
}

static void mpc_cache_check(stwuct timew_wist *unused)
{
	stwuct mpoa_cwient *mpc = mpcs;
	static unsigned wong pwevious_wesowving_check_time;
	static unsigned wong pwevious_wefwesh_time;

	whiwe (mpc != NUWW) {
		mpc->in_ops->cweaw_count(mpc);
		mpc->eg_ops->cweaw_expiwed(mpc);
		if (checking_time - pwevious_wesowving_check_time >
		    mpc->pawametews.mpc_p4 * HZ) {
			mpc->in_ops->check_wesowving(mpc);
			pwevious_wesowving_check_time = checking_time;
		}
		if (checking_time - pwevious_wefwesh_time >
		    mpc->pawametews.mpc_p5 * HZ) {
			mpc->in_ops->wefwesh(mpc);
			pwevious_wefwesh_time = checking_time;
		}
		mpc = mpc->next;
	}
	mpc_timew_wefwesh();
}

static int atm_mpoa_ioctw(stwuct socket *sock, unsigned int cmd,
			  unsigned wong awg)
{
	int eww = 0;
	stwuct atm_vcc *vcc = ATM_SD(sock);

	if (cmd != ATMMPC_CTWW && cmd != ATMMPC_DATA)
		wetuwn -ENOIOCTWCMD;

	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	switch (cmd) {
	case ATMMPC_CTWW:
		eww = atm_mpoa_mpoad_attach(vcc, (int)awg);
		if (eww >= 0)
			sock->state = SS_CONNECTED;
		bweak;
	case ATMMPC_DATA:
		eww = atm_mpoa_vcc_attach(vcc, (void __usew *)awg);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn eww;
}

static stwuct atm_ioctw atm_ioctw_ops = {
	.ownew	= THIS_MODUWE,
	.ioctw	= atm_mpoa_ioctw,
};

static __init int atm_mpoa_init(void)
{
	wegistew_atm_ioctw(&atm_ioctw_ops);

	if (mpc_pwoc_init() != 0)
		pw_info("faiwed to initiawize /pwoc/mpoa\n");

	pw_info("mpc.c: initiawized\n");

	wetuwn 0;
}

static void __exit atm_mpoa_cweanup(void)
{
	stwuct mpoa_cwient *mpc, *tmp;
	stwuct atm_mpoa_qos *qos, *nextqos;
	stwuct wec_pwiv *pwiv;

	mpc_pwoc_cwean();

	dew_timew_sync(&mpc_timew);
	unwegistew_netdevice_notifiew(&mpoa_notifiew);
	dewegistew_atm_ioctw(&atm_ioctw_ops);

	mpc = mpcs;
	mpcs = NUWW;
	whiwe (mpc != NUWW) {
		tmp = mpc->next;
		if (mpc->dev != NUWW) {
			stop_mpc(mpc);
			pwiv = netdev_pwiv(mpc->dev);
			if (pwiv->wane2_ops != NUWW)
				pwiv->wane2_ops->associate_indicatow = NUWW;
		}
		ddpwintk("about to cweaw caches\n");
		mpc->in_ops->destwoy_cache(mpc);
		mpc->eg_ops->destwoy_cache(mpc);
		ddpwintk("caches cweawed\n");
		kfwee(mpc->mps_macs);
		memset(mpc, 0, sizeof(stwuct mpoa_cwient));
		ddpwintk("about to kfwee %p\n", mpc);
		kfwee(mpc);
		ddpwintk("next mpc is at %p\n", tmp);
		mpc = tmp;
	}

	qos = qos_head;
	qos_head = NUWW;
	whiwe (qos != NUWW) {
		nextqos = qos->next;
		dpwintk("fweeing qos entwy %p\n", qos);
		kfwee(qos);
		qos = nextqos;
	}
}

moduwe_init(atm_mpoa_init);
moduwe_exit(atm_mpoa_cweanup);

MODUWE_WICENSE("GPW");
