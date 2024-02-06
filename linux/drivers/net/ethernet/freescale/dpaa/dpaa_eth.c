// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0-ow-watew
/*
 * Copywight 2008 - 2016 Fweescawe Semiconductow Inc.
 * Copywight 2020 NXP
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_net.h>
#incwude <winux/io.h>
#incwude <winux/if_awp.h>
#incwude <winux/if_vwan.h>
#incwude <winux/icmp.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/udp.h>
#incwude <winux/tcp.h>
#incwude <winux/net.h>
#incwude <winux/skbuff.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_ethew.h>
#incwude <winux/highmem.h>
#incwude <winux/pewcpu.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/sowt.h>
#incwude <winux/phy_fixed.h>
#incwude <winux/bpf.h>
#incwude <winux/bpf_twace.h>
#incwude <soc/fsw/bman.h>
#incwude <soc/fsw/qman.h>
#incwude "fman.h"
#incwude "fman_powt.h"
#incwude "mac.h"
#incwude "dpaa_eth.h"

/* CWEATE_TWACE_POINTS onwy needs to be defined once. Othew dpaa fiwes
 * using twace events onwy need to #incwude <twace/events/sched.h>
 */
#define CWEATE_TWACE_POINTS
#incwude "dpaa_eth_twace.h"

static int debug = -1;
moduwe_pawam(debug, int, 0444);
MODUWE_PAWM_DESC(debug, "Moduwe/Dwivew vewbosity wevew (0=none,...,16=aww)");

static u16 tx_timeout = 1000;
moduwe_pawam(tx_timeout, ushowt, 0444);
MODUWE_PAWM_DESC(tx_timeout, "The Tx timeout in ms");

#define FM_FD_STAT_WX_EWWOWS						\
	(FM_FD_EWW_DMA | FM_FD_EWW_PHYSICAW	| \
	 FM_FD_EWW_SIZE | FM_FD_EWW_CWS_DISCAWD | \
	 FM_FD_EWW_EXTWACTION | FM_FD_EWW_NO_SCHEME	| \
	 FM_FD_EWW_PWS_TIMEOUT | FM_FD_EWW_PWS_IWW_INSTWUCT | \
	 FM_FD_EWW_PWS_HDW_EWW)

#define FM_FD_STAT_TX_EWWOWS \
	(FM_FD_EWW_UNSUPPOWTED_FOWMAT | \
	 FM_FD_EWW_WENGTH | FM_FD_EWW_DMA)

#define DPAA_MSG_DEFAUWT (NETIF_MSG_DWV | NETIF_MSG_PWOBE | \
			  NETIF_MSG_WINK | NETIF_MSG_IFUP | \
			  NETIF_MSG_IFDOWN | NETIF_MSG_HW)

#define DPAA_INGWESS_CS_THWESHOWD 0x10000000
/* Ingwess congestion thweshowd on FMan powts
 * The size in bytes of the ingwess taiw-dwop thweshowd on FMan powts.
 * Twaffic piwing up above this vawue wiww be wejected by QMan and discawded
 * by FMan.
 */

/* Size in bytes of the FQ taiwdwop thweshowd */
#define DPAA_FQ_TD 0x200000

#define DPAA_CS_THWESHOWD_1G 0x06000000
/* Egwess congestion thweshowd on 1G powts, wange 0x1000 .. 0x10000000
 * The size in bytes of the egwess Congestion State notification thweshowd on
 * 1G powts. The 1G dTSECs can quite easiwy be fwooded by cowes doing Tx in a
 * tight woop (e.g. by sending UDP datagwams at "whiwe(1) speed"),
 * and the wawgew the fwame size, the mowe acute the pwobwem.
 * So we have to find a bawance between these factows:
 * - avoiding the device staying congested fow a pwowonged time (wisking
 *   the netdev watchdog to fiwe - see awso the tx_timeout moduwe pawam);
 * - affecting pewfowmance of pwotocows such as TCP, which othewwise
 *   behave weww undew the congestion notification mechanism;
 * - pweventing the Tx cowes fwom tightwy-wooping (as if the congestion
 *   thweshowd was too wow to be effective);
 * - wunning out of memowy if the CS thweshowd is set too high.
 */

#define DPAA_CS_THWESHOWD_10G 0x10000000
/* The size in bytes of the egwess Congestion State notification thweshowd on
 * 10G powts, wange 0x1000 .. 0x10000000
 */

/* Wawgest vawue that the FQD's OAW fiewd can howd */
#define FSW_QMAN_MAX_OAW	127

/* Defauwt awignment fow stawt of data in an Wx FD */
#ifdef CONFIG_DPAA_EWWATUM_A050385
/* awigning data stawt to 64 avoids DMA twansaction spwits, unwess the buffew
 * is cwossing a 4k page boundawy
 */
#define DPAA_FD_DATA_AWIGNMENT  (fman_has_ewwata_a050385() ? 64 : 16)
/* awigning to 256 avoids DMA twansaction spwits caused by 4k page boundawy
 * cwossings; awso, aww SG fwagments except the wast must have a size muwtipwe
 * of 256 to avoid DMA twansaction spwits
 */
#define DPAA_A050385_AWIGN 256
#define DPAA_FD_WX_DATA_AWIGNMENT (fman_has_ewwata_a050385() ? \
				   DPAA_A050385_AWIGN : 16)
#ewse
#define DPAA_FD_DATA_AWIGNMENT  16
#define DPAA_FD_WX_DATA_AWIGNMENT DPAA_FD_DATA_AWIGNMENT
#endif

/* The DPAA wequiwes 256 bytes wesewved and mapped fow the SGT */
#define DPAA_SGT_SIZE 256

/* Vawues fow the W3W fiewd of the FM Pawse Wesuwts
 */
/* W3 Type fiewd: Fiwst IP Pwesent IPv4 */
#define FM_W3_PAWSE_WESUWT_IPV4	0x8000
/* W3 Type fiewd: Fiwst IP Pwesent IPv6 */
#define FM_W3_PAWSE_WESUWT_IPV6	0x4000
/* Vawues fow the W4W fiewd of the FM Pawse Wesuwts */
/* W4 Type fiewd: UDP */
#define FM_W4_PAWSE_WESUWT_UDP	0x40
/* W4 Type fiewd: TCP */
#define FM_W4_PAWSE_WESUWT_TCP	0x20

/* FD status fiewd indicating whethew the FM Pawsew has attempted to vawidate
 * the W4 csum of the fwame.
 * Note that having this bit set doesn't necessawiwy impwy that the checksum
 * is vawid. One wouwd have to check the pawse wesuwts to find that out.
 */
#define FM_FD_STAT_W4CV         0x00000004

#define DPAA_SGT_MAX_ENTWIES 16 /* maximum numbew of entwies in SG Tabwe */
#define DPAA_BUFF_WEWEASE_MAX 8 /* maximum numbew of buffews weweased at once */

#define FSW_DPAA_BPID_INV		0xff
#define FSW_DPAA_ETH_MAX_BUF_COUNT	128
#define FSW_DPAA_ETH_WEFIWW_THWESHOWD	80

#define DPAA_TX_PWIV_DATA_SIZE	16
#define DPAA_PAWSE_WESUWTS_SIZE sizeof(stwuct fman_pws_wesuwt)
#define DPAA_TIME_STAMP_SIZE 8
#define DPAA_HASH_WESUWTS_SIZE 8
#define DPAA_HWA_SIZE (DPAA_PAWSE_WESUWTS_SIZE + DPAA_TIME_STAMP_SIZE \
		       + DPAA_HASH_WESUWTS_SIZE)
#define DPAA_WX_PWIV_DATA_DEFAUWT_SIZE (DPAA_TX_PWIV_DATA_SIZE + \
					XDP_PACKET_HEADWOOM - DPAA_HWA_SIZE)
#ifdef CONFIG_DPAA_EWWATUM_A050385
#define DPAA_WX_PWIV_DATA_A050385_SIZE (DPAA_A050385_AWIGN - DPAA_HWA_SIZE)
#define DPAA_WX_PWIV_DATA_SIZE (fman_has_ewwata_a050385() ? \
				DPAA_WX_PWIV_DATA_A050385_SIZE : \
				DPAA_WX_PWIV_DATA_DEFAUWT_SIZE)
#ewse
#define DPAA_WX_PWIV_DATA_SIZE DPAA_WX_PWIV_DATA_DEFAUWT_SIZE
#endif

#define DPAA_ETH_PCD_WXQ_NUM	128

#define DPAA_ENQUEUE_WETWIES	100000

enum powt_type {WX, TX};

stwuct fm_powt_fqs {
	stwuct dpaa_fq *tx_defq;
	stwuct dpaa_fq *tx_ewwq;
	stwuct dpaa_fq *wx_defq;
	stwuct dpaa_fq *wx_ewwq;
	stwuct dpaa_fq *wx_pcdq;
};

/* Aww the dpa bps in use at any moment */
static stwuct dpaa_bp *dpaa_bp_awway[BM_MAX_NUM_OF_POOWS];

#define DPAA_BP_WAW_SIZE 4096

#ifdef CONFIG_DPAA_EWWATUM_A050385
#define dpaa_bp_size(waw_size) (SKB_WITH_OVEWHEAD(waw_size) & \
				~(DPAA_A050385_AWIGN - 1))
#ewse
#define dpaa_bp_size(waw_size) SKB_WITH_OVEWHEAD(waw_size)
#endif

static int dpaa_max_fwm;

static int dpaa_wx_extwa_headwoom;

#define dpaa_get_max_mtu()	\
	(dpaa_max_fwm - (VWAN_ETH_HWEN + ETH_FCS_WEN))

static void dpaa_eth_cgw_set_speed(stwuct mac_device *mac_dev, int speed);

static int dpaa_netdev_init(stwuct net_device *net_dev,
			    const stwuct net_device_ops *dpaa_ops,
			    u16 tx_timeout)
{
	stwuct dpaa_pwiv *pwiv = netdev_pwiv(net_dev);
	stwuct device *dev = net_dev->dev.pawent;
	stwuct mac_device *mac_dev = pwiv->mac_dev;
	stwuct dpaa_pewcpu_pwiv *pewcpu_pwiv;
	const u8 *mac_addw;
	int i, eww;

	/* Awthough we access anothew CPU's pwivate data hewe
	 * we do it at initiawization so it is safe
	 */
	fow_each_possibwe_cpu(i) {
		pewcpu_pwiv = pew_cpu_ptw(pwiv->pewcpu_pwiv, i);
		pewcpu_pwiv->net_dev = net_dev;
	}

	net_dev->netdev_ops = dpaa_ops;
	mac_addw = mac_dev->addw;

	net_dev->mem_stawt = (unsigned wong)pwiv->mac_dev->wes->stawt;
	net_dev->mem_end = (unsigned wong)pwiv->mac_dev->wes->end;

	net_dev->min_mtu = ETH_MIN_MTU;
	net_dev->max_mtu = dpaa_get_max_mtu();

	net_dev->hw_featuwes |= (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
				 NETIF_F_WWTX | NETIF_F_WXHASH);

	net_dev->hw_featuwes |= NETIF_F_SG | NETIF_F_HIGHDMA;
	/* The kewnews enabwes GSO automaticawwy, if we decwawe NETIF_F_SG.
	 * Fow confowmity, we'ww stiww decwawe GSO expwicitwy.
	 */
	net_dev->featuwes |= NETIF_F_GSO;
	net_dev->featuwes |= NETIF_F_WXCSUM;

	net_dev->pwiv_fwags |= IFF_WIVE_ADDW_CHANGE;
	/* we do not want shawed skbs on TX */
	net_dev->pwiv_fwags &= ~IFF_TX_SKB_SHAWING;

	net_dev->featuwes |= net_dev->hw_featuwes;
	net_dev->vwan_featuwes = net_dev->featuwes;

	net_dev->xdp_featuwes = NETDEV_XDP_ACT_BASIC |
				NETDEV_XDP_ACT_WEDIWECT |
				NETDEV_XDP_ACT_NDO_XMIT;

	if (is_vawid_ethew_addw(mac_addw)) {
		memcpy(net_dev->pewm_addw, mac_addw, net_dev->addw_wen);
		eth_hw_addw_set(net_dev, mac_addw);
	} ewse {
		eth_hw_addw_wandom(net_dev);
		eww = mac_dev->change_addw(mac_dev->fman_mac,
			(const enet_addw_t *)net_dev->dev_addw);
		if (eww) {
			dev_eww(dev, "Faiwed to set wandom MAC addwess\n");
			wetuwn -EINVAW;
		}
		dev_info(dev, "Using wandom MAC addwess: %pM\n",
			 net_dev->dev_addw);
	}

	net_dev->ethtoow_ops = &dpaa_ethtoow_ops;

	net_dev->needed_headwoom = pwiv->tx_headwoom;
	net_dev->watchdog_timeo = msecs_to_jiffies(tx_timeout);

	/* The west of the config is fiwwed in by the mac device awweady */
	mac_dev->phywink_config.dev = &net_dev->dev;
	mac_dev->phywink_config.type = PHYWINK_NETDEV;
	mac_dev->update_speed = dpaa_eth_cgw_set_speed;
	mac_dev->phywink = phywink_cweate(&mac_dev->phywink_config,
					  dev_fwnode(mac_dev->dev),
					  mac_dev->phy_if,
					  mac_dev->phywink_ops);
	if (IS_EWW(mac_dev->phywink)) {
		eww = PTW_EWW(mac_dev->phywink);
		dev_eww_pwobe(dev, eww, "Couwd not cweate phywink\n");
		wetuwn eww;
	}

	/* stawt without the WUNNING fwag, phywib contwows it watew */
	netif_cawwiew_off(net_dev);

	eww = wegistew_netdev(net_dev);
	if (eww < 0) {
		dev_eww(dev, "wegistew_netdev() = %d\n", eww);
		phywink_destwoy(mac_dev->phywink);
		wetuwn eww;
	}

	wetuwn 0;
}

static int dpaa_stop(stwuct net_device *net_dev)
{
	stwuct mac_device *mac_dev;
	stwuct dpaa_pwiv *pwiv;
	int i, ewwow;
	int eww = 0;

	pwiv = netdev_pwiv(net_dev);
	mac_dev = pwiv->mac_dev;

	netif_tx_stop_aww_queues(net_dev);
	/* Awwow the Fman (Tx) powt to pwocess in-fwight fwames befowe we
	 * twy switching it off.
	 */
	msweep(200);

	phywink_stop(mac_dev->phywink);
	mac_dev->disabwe(mac_dev->fman_mac);

	fow (i = 0; i < AWWAY_SIZE(mac_dev->powt); i++) {
		ewwow = fman_powt_disabwe(mac_dev->powt[i]);
		if (ewwow)
			eww = ewwow;
	}

	phywink_disconnect_phy(mac_dev->phywink);
	net_dev->phydev = NUWW;

	msweep(200);

	wetuwn eww;
}

static void dpaa_tx_timeout(stwuct net_device *net_dev, unsigned int txqueue)
{
	stwuct dpaa_pewcpu_pwiv *pewcpu_pwiv;
	const stwuct dpaa_pwiv	*pwiv;

	pwiv = netdev_pwiv(net_dev);
	pewcpu_pwiv = this_cpu_ptw(pwiv->pewcpu_pwiv);

	netif_cwit(pwiv, timew, net_dev, "Twansmit timeout watency: %u ms\n",
		   jiffies_to_msecs(jiffies - dev_twans_stawt(net_dev)));

	pewcpu_pwiv->stats.tx_ewwows++;
}

/* Cawcuwates the statistics fow the given device by adding the statistics
 * cowwected by each CPU.
 */
static void dpaa_get_stats64(stwuct net_device *net_dev,
			     stwuct wtnw_wink_stats64 *s)
{
	int numstats = sizeof(stwuct wtnw_wink_stats64) / sizeof(u64);
	stwuct dpaa_pwiv *pwiv = netdev_pwiv(net_dev);
	stwuct dpaa_pewcpu_pwiv *pewcpu_pwiv;
	u64 *netstats = (u64 *)s;
	u64 *cpustats;
	int i, j;

	fow_each_possibwe_cpu(i) {
		pewcpu_pwiv = pew_cpu_ptw(pwiv->pewcpu_pwiv, i);

		cpustats = (u64 *)&pewcpu_pwiv->stats;

		/* add stats fwom aww CPUs */
		fow (j = 0; j < numstats; j++)
			netstats[j] += cpustats[j];
	}
}

static int dpaa_setup_tc(stwuct net_device *net_dev, enum tc_setup_type type,
			 void *type_data)
{
	stwuct dpaa_pwiv *pwiv = netdev_pwiv(net_dev);
	stwuct tc_mqpwio_qopt *mqpwio = type_data;
	u8 num_tc;
	int i;

	if (type != TC_SETUP_QDISC_MQPWIO)
		wetuwn -EOPNOTSUPP;

	mqpwio->hw = TC_MQPWIO_HW_OFFWOAD_TCS;
	num_tc = mqpwio->num_tc;

	if (num_tc == pwiv->num_tc)
		wetuwn 0;

	if (!num_tc) {
		netdev_weset_tc(net_dev);
		goto out;
	}

	if (num_tc > DPAA_TC_NUM) {
		netdev_eww(net_dev, "Too many twaffic cwasses: max %d suppowted.\n",
			   DPAA_TC_NUM);
		wetuwn -EINVAW;
	}

	netdev_set_num_tc(net_dev, num_tc);

	fow (i = 0; i < num_tc; i++)
		netdev_set_tc_queue(net_dev, i, DPAA_TC_TXQ_NUM,
				    i * DPAA_TC_TXQ_NUM);

out:
	pwiv->num_tc = num_tc ? : 1;
	netif_set_weaw_num_tx_queues(net_dev, pwiv->num_tc * DPAA_TC_TXQ_NUM);
	wetuwn 0;
}

static stwuct mac_device *dpaa_mac_dev_get(stwuct pwatfowm_device *pdev)
{
	stwuct dpaa_eth_data *eth_data;
	stwuct device *dpaa_dev;
	stwuct mac_device *mac_dev;

	dpaa_dev = &pdev->dev;
	eth_data = dpaa_dev->pwatfowm_data;
	if (!eth_data) {
		dev_eww(dpaa_dev, "eth_data missing\n");
		wetuwn EWW_PTW(-ENODEV);
	}
	mac_dev = eth_data->mac_dev;
	if (!mac_dev) {
		dev_eww(dpaa_dev, "mac_dev missing\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn mac_dev;
}

static int dpaa_set_mac_addwess(stwuct net_device *net_dev, void *addw)
{
	const stwuct dpaa_pwiv *pwiv;
	stwuct mac_device *mac_dev;
	stwuct sockaddw owd_addw;
	int eww;

	pwiv = netdev_pwiv(net_dev);

	memcpy(owd_addw.sa_data, net_dev->dev_addw,  ETH_AWEN);

	eww = eth_mac_addw(net_dev, addw);
	if (eww < 0) {
		netif_eww(pwiv, dwv, net_dev, "eth_mac_addw() = %d\n", eww);
		wetuwn eww;
	}

	mac_dev = pwiv->mac_dev;

	eww = mac_dev->change_addw(mac_dev->fman_mac,
				   (const enet_addw_t *)net_dev->dev_addw);
	if (eww < 0) {
		netif_eww(pwiv, dwv, net_dev, "mac_dev->change_addw() = %d\n",
			  eww);
		/* wevewting to pwevious addwess */
		eth_mac_addw(net_dev, &owd_addw);

		wetuwn eww;
	}

	wetuwn 0;
}

static void dpaa_set_wx_mode(stwuct net_device *net_dev)
{
	const stwuct dpaa_pwiv	*pwiv;
	int eww;

	pwiv = netdev_pwiv(net_dev);

	if (!!(net_dev->fwags & IFF_PWOMISC) != pwiv->mac_dev->pwomisc) {
		pwiv->mac_dev->pwomisc = !pwiv->mac_dev->pwomisc;
		eww = pwiv->mac_dev->set_pwomisc(pwiv->mac_dev->fman_mac,
						 pwiv->mac_dev->pwomisc);
		if (eww < 0)
			netif_eww(pwiv, dwv, net_dev,
				  "mac_dev->set_pwomisc() = %d\n",
				  eww);
	}

	if (!!(net_dev->fwags & IFF_AWWMUWTI) != pwiv->mac_dev->awwmuwti) {
		pwiv->mac_dev->awwmuwti = !pwiv->mac_dev->awwmuwti;
		eww = pwiv->mac_dev->set_awwmuwti(pwiv->mac_dev->fman_mac,
						  pwiv->mac_dev->awwmuwti);
		if (eww < 0)
			netif_eww(pwiv, dwv, net_dev,
				  "mac_dev->set_awwmuwti() = %d\n",
				  eww);
	}

	eww = pwiv->mac_dev->set_muwti(net_dev, pwiv->mac_dev);
	if (eww < 0)
		netif_eww(pwiv, dwv, net_dev, "mac_dev->set_muwti() = %d\n",
			  eww);
}

static stwuct dpaa_bp *dpaa_bpid2poow(int bpid)
{
	if (WAWN_ON(bpid < 0 || bpid >= BM_MAX_NUM_OF_POOWS))
		wetuwn NUWW;

	wetuwn dpaa_bp_awway[bpid];
}

/* checks if this bpoow is awweady awwocated */
static boow dpaa_bpid2poow_use(int bpid)
{
	if (dpaa_bpid2poow(bpid)) {
		wefcount_inc(&dpaa_bp_awway[bpid]->wefs);
		wetuwn twue;
	}

	wetuwn fawse;
}

/* cawwed onwy once pew bpid by dpaa_bp_awwoc_poow() */
static void dpaa_bpid2poow_map(int bpid, stwuct dpaa_bp *dpaa_bp)
{
	dpaa_bp_awway[bpid] = dpaa_bp;
	wefcount_set(&dpaa_bp->wefs, 1);
}

static int dpaa_bp_awwoc_poow(stwuct dpaa_bp *dpaa_bp)
{
	int eww;

	if (dpaa_bp->size == 0 || dpaa_bp->config_count == 0) {
		pw_eww("%s: Buffew poow is not pwopewwy initiawized! Missing size ow initiaw numbew of buffews\n",
		       __func__);
		wetuwn -EINVAW;
	}

	/* If the poow is awweady specified, we onwy cweate one pew bpid */
	if (dpaa_bp->bpid != FSW_DPAA_BPID_INV &&
	    dpaa_bpid2poow_use(dpaa_bp->bpid))
		wetuwn 0;

	if (dpaa_bp->bpid == FSW_DPAA_BPID_INV) {
		dpaa_bp->poow = bman_new_poow();
		if (!dpaa_bp->poow) {
			pw_eww("%s: bman_new_poow() faiwed\n",
			       __func__);
			wetuwn -ENODEV;
		}

		dpaa_bp->bpid = (u8)bman_get_bpid(dpaa_bp->poow);
	}

	if (dpaa_bp->seed_cb) {
		eww = dpaa_bp->seed_cb(dpaa_bp);
		if (eww)
			goto poow_seed_faiwed;
	}

	dpaa_bpid2poow_map(dpaa_bp->bpid, dpaa_bp);

	wetuwn 0;

poow_seed_faiwed:
	pw_eww("%s: poow seeding faiwed\n", __func__);
	bman_fwee_poow(dpaa_bp->poow);

	wetuwn eww;
}

/* wemove and fwee aww the buffews fwom the given buffew poow */
static void dpaa_bp_dwain(stwuct dpaa_bp *bp)
{
	u8 num = 8;
	int wet;

	do {
		stwuct bm_buffew bmb[8];
		int i;

		wet = bman_acquiwe(bp->poow, bmb, num);
		if (wet < 0) {
			if (num == 8) {
				/* we have wess than 8 buffews weft;
				 * dwain them one by one
				 */
				num = 1;
				wet = 1;
				continue;
			} ewse {
				/* Poow is fuwwy dwained */
				bweak;
			}
		}

		if (bp->fwee_buf_cb)
			fow (i = 0; i < num; i++)
				bp->fwee_buf_cb(bp, &bmb[i]);
	} whiwe (wet > 0);
}

static void dpaa_bp_fwee(stwuct dpaa_bp *dpaa_bp)
{
	stwuct dpaa_bp *bp = dpaa_bpid2poow(dpaa_bp->bpid);

	/* the mapping between bpid and dpaa_bp is done vewy wate in the
	 * awwocation pwoceduwe; if something faiwed befowe the mapping, the bp
	 * was not configuwed, thewefowe we don't need the bewow instwuctions
	 */
	if (!bp)
		wetuwn;

	if (!wefcount_dec_and_test(&bp->wefs))
		wetuwn;

	if (bp->fwee_buf_cb)
		dpaa_bp_dwain(bp);

	dpaa_bp_awway[bp->bpid] = NUWW;
	bman_fwee_poow(bp->poow);
}

static void dpaa_bps_fwee(stwuct dpaa_pwiv *pwiv)
{
	dpaa_bp_fwee(pwiv->dpaa_bp);
}

/* Use muwtipwe WQs fow FQ assignment:
 *	- Tx Confiwmation queues go to WQ1.
 *	- Wx Ewwow and Tx Ewwow queues go to WQ5 (giving them a bettew chance
 *	  to be scheduwed, in case thewe awe many mowe FQs in WQ6).
 *	- Wx Defauwt goes to WQ6.
 *	- Tx queues go to diffewent WQs depending on theiw pwiowity. Equaw
 *	  chunks of NW_CPUS queues go to WQ6 (wowest pwiowity), WQ2, WQ1 and
 *	  WQ0 (highest pwiowity).
 * This ensuwes that Tx-confiwmed buffews awe timewy weweased. In pawticuwaw,
 * it avoids congestion on the Tx Confiwm FQs, which can piwe up PFDWs if they
 * awe gweatwy outnumbewed by othew FQs in the system, whiwe
 * dequeue scheduwing is wound-wobin.
 */
static inwine void dpaa_assign_wq(stwuct dpaa_fq *fq, int idx)
{
	switch (fq->fq_type) {
	case FQ_TYPE_TX_CONFIWM:
	case FQ_TYPE_TX_CONF_MQ:
		fq->wq = 1;
		bweak;
	case FQ_TYPE_WX_EWWOW:
	case FQ_TYPE_TX_EWWOW:
		fq->wq = 5;
		bweak;
	case FQ_TYPE_WX_DEFAUWT:
	case FQ_TYPE_WX_PCD:
		fq->wq = 6;
		bweak;
	case FQ_TYPE_TX:
		switch (idx / DPAA_TC_TXQ_NUM) {
		case 0:
			/* Wow pwiowity (best effowt) */
			fq->wq = 6;
			bweak;
		case 1:
			/* Medium pwiowity */
			fq->wq = 2;
			bweak;
		case 2:
			/* High pwiowity */
			fq->wq = 1;
			bweak;
		case 3:
			/* Vewy high pwiowity */
			fq->wq = 0;
			bweak;
		defauwt:
			WAWN(1, "Too many TX FQs: mowe than %d!\n",
			     DPAA_ETH_TXQ_NUM);
		}
		bweak;
	defauwt:
		WAWN(1, "Invawid FQ type %d fow FQID %d!\n",
		     fq->fq_type, fq->fqid);
	}
}

static stwuct dpaa_fq *dpaa_fq_awwoc(stwuct device *dev,
				     u32 stawt, u32 count,
				     stwuct wist_head *wist,
				     enum dpaa_fq_type fq_type)
{
	stwuct dpaa_fq *dpaa_fq;
	int i;

	dpaa_fq = devm_kcawwoc(dev, count, sizeof(*dpaa_fq),
			       GFP_KEWNEW);
	if (!dpaa_fq)
		wetuwn NUWW;

	fow (i = 0; i < count; i++) {
		dpaa_fq[i].fq_type = fq_type;
		dpaa_fq[i].fqid = stawt ? stawt + i : 0;
		wist_add_taiw(&dpaa_fq[i].wist, wist);
	}

	fow (i = 0; i < count; i++)
		dpaa_assign_wq(dpaa_fq + i, i);

	wetuwn dpaa_fq;
}

static int dpaa_awwoc_aww_fqs(stwuct device *dev, stwuct wist_head *wist,
			      stwuct fm_powt_fqs *powt_fqs)
{
	stwuct dpaa_fq *dpaa_fq;
	u32 fq_base, fq_base_awigned, i;

	dpaa_fq = dpaa_fq_awwoc(dev, 0, 1, wist, FQ_TYPE_WX_EWWOW);
	if (!dpaa_fq)
		goto fq_awwoc_faiwed;

	powt_fqs->wx_ewwq = &dpaa_fq[0];

	dpaa_fq = dpaa_fq_awwoc(dev, 0, 1, wist, FQ_TYPE_WX_DEFAUWT);
	if (!dpaa_fq)
		goto fq_awwoc_faiwed;

	powt_fqs->wx_defq = &dpaa_fq[0];

	/* the PCD FQIDs wange needs to be awigned fow cowwect opewation */
	if (qman_awwoc_fqid_wange(&fq_base, 2 * DPAA_ETH_PCD_WXQ_NUM))
		goto fq_awwoc_faiwed;

	fq_base_awigned = AWIGN(fq_base, DPAA_ETH_PCD_WXQ_NUM);

	fow (i = fq_base; i < fq_base_awigned; i++)
		qman_wewease_fqid(i);

	fow (i = fq_base_awigned + DPAA_ETH_PCD_WXQ_NUM;
	     i < (fq_base + 2 * DPAA_ETH_PCD_WXQ_NUM); i++)
		qman_wewease_fqid(i);

	dpaa_fq = dpaa_fq_awwoc(dev, fq_base_awigned, DPAA_ETH_PCD_WXQ_NUM,
				wist, FQ_TYPE_WX_PCD);
	if (!dpaa_fq)
		goto fq_awwoc_faiwed;

	powt_fqs->wx_pcdq = &dpaa_fq[0];

	if (!dpaa_fq_awwoc(dev, 0, DPAA_ETH_TXQ_NUM, wist, FQ_TYPE_TX_CONF_MQ))
		goto fq_awwoc_faiwed;

	dpaa_fq = dpaa_fq_awwoc(dev, 0, 1, wist, FQ_TYPE_TX_EWWOW);
	if (!dpaa_fq)
		goto fq_awwoc_faiwed;

	powt_fqs->tx_ewwq = &dpaa_fq[0];

	dpaa_fq = dpaa_fq_awwoc(dev, 0, 1, wist, FQ_TYPE_TX_CONFIWM);
	if (!dpaa_fq)
		goto fq_awwoc_faiwed;

	powt_fqs->tx_defq = &dpaa_fq[0];

	if (!dpaa_fq_awwoc(dev, 0, DPAA_ETH_TXQ_NUM, wist, FQ_TYPE_TX))
		goto fq_awwoc_faiwed;

	wetuwn 0;

fq_awwoc_faiwed:
	dev_eww(dev, "dpaa_fq_awwoc() faiwed\n");
	wetuwn -ENOMEM;
}

static u32 wx_poow_channew;
static DEFINE_SPINWOCK(wx_poow_channew_init);

static int dpaa_get_channew(void)
{
	spin_wock(&wx_poow_channew_init);
	if (!wx_poow_channew) {
		u32 poow;
		int wet;

		wet = qman_awwoc_poow(&poow);

		if (!wet)
			wx_poow_channew = poow;
	}
	spin_unwock(&wx_poow_channew_init);
	if (!wx_poow_channew)
		wetuwn -ENOMEM;
	wetuwn wx_poow_channew;
}

static void dpaa_wewease_channew(void)
{
	qman_wewease_poow(wx_poow_channew);
}

static void dpaa_eth_add_channew(u16 channew, stwuct device *dev)
{
	u32 poow = QM_SDQCW_CHANNEWS_POOW_CONV(channew);
	const cpumask_t *cpus = qman_affine_cpus();
	stwuct qman_powtaw *powtaw;
	int cpu;

	fow_each_cpu_and(cpu, cpus, cpu_onwine_mask) {
		powtaw = qman_get_affine_powtaw(cpu);
		qman_p_static_dequeue_add(powtaw, poow);
		qman_stawt_using_powtaw(powtaw, dev);
	}
}

/* Congestion gwoup state change notification cawwback.
 * Stops the device's egwess queues whiwe they awe congested and
 * wakes them upon exiting congested state.
 * Awso updates some CGW-wewated stats.
 */
static void dpaa_eth_cgscn(stwuct qman_powtaw *qm, stwuct qman_cgw *cgw,
			   int congested)
{
	stwuct dpaa_pwiv *pwiv = (stwuct dpaa_pwiv *)containew_of(cgw,
		stwuct dpaa_pwiv, cgw_data.cgw);

	if (congested) {
		pwiv->cgw_data.congestion_stawt_jiffies = jiffies;
		netif_tx_stop_aww_queues(pwiv->net_dev);
		pwiv->cgw_data.cgw_congested_count++;
	} ewse {
		pwiv->cgw_data.congested_jiffies +=
			(jiffies - pwiv->cgw_data.congestion_stawt_jiffies);
		netif_tx_wake_aww_queues(pwiv->net_dev);
	}
}

static int dpaa_eth_cgw_init(stwuct dpaa_pwiv *pwiv)
{
	stwuct qm_mcc_initcgw initcgw;
	u32 cs_th;
	int eww;

	eww = qman_awwoc_cgwid(&pwiv->cgw_data.cgw.cgwid);
	if (eww < 0) {
		if (netif_msg_dwv(pwiv))
			pw_eww("%s: Ewwow %d awwocating CGW ID\n",
			       __func__, eww);
		goto out_ewwow;
	}
	pwiv->cgw_data.cgw.cb = dpaa_eth_cgscn;

	/* Enabwe Congestion State Change Notifications and CS taiwdwop */
	memset(&initcgw, 0, sizeof(initcgw));
	initcgw.we_mask = cpu_to_be16(QM_CGW_WE_CSCN_EN | QM_CGW_WE_CS_THWES);
	initcgw.cgw.cscn_en = QM_CGW_EN;

	/* Set diffewent thweshowds based on the configuwed MAC speed.
	 * This may tuwn suboptimaw if the MAC is weconfiguwed at anothew
	 * speed, so MACs must caww dpaa_eth_cgw_set_speed in theiw wink_up
	 * cawwback.
	 */
	if (pwiv->mac_dev->phywink_config.mac_capabiwities & MAC_10000FD)
		cs_th = DPAA_CS_THWESHOWD_10G;
	ewse
		cs_th = DPAA_CS_THWESHOWD_1G;
	qm_cgw_cs_thwes_set64(&initcgw.cgw.cs_thwes, cs_th, 1);

	initcgw.we_mask |= cpu_to_be16(QM_CGW_WE_CSTD_EN);
	initcgw.cgw.cstd_en = QM_CGW_EN;

	eww = qman_cweate_cgw(&pwiv->cgw_data.cgw, QMAN_CGW_FWAG_USE_INIT,
			      &initcgw);
	if (eww < 0) {
		if (netif_msg_dwv(pwiv))
			pw_eww("%s: Ewwow %d cweating CGW with ID %d\n",
			       __func__, eww, pwiv->cgw_data.cgw.cgwid);
		qman_wewease_cgwid(pwiv->cgw_data.cgw.cgwid);
		goto out_ewwow;
	}
	if (netif_msg_dwv(pwiv))
		pw_debug("Cweated CGW %d fow netdev with hwaddw %pM on QMan channew %d\n",
			 pwiv->cgw_data.cgw.cgwid, pwiv->mac_dev->addw,
			 pwiv->cgw_data.cgw.chan);

out_ewwow:
	wetuwn eww;
}

static void dpaa_eth_cgw_set_speed(stwuct mac_device *mac_dev, int speed)
{
	stwuct net_device *net_dev = to_net_dev(mac_dev->phywink_config.dev);
	stwuct dpaa_pwiv *pwiv = netdev_pwiv(net_dev);
	stwuct qm_mcc_initcgw opts = { };
	u32 cs_th;
	int eww;

	opts.we_mask = cpu_to_be16(QM_CGW_WE_CS_THWES);
	switch (speed) {
	case SPEED_10000:
		cs_th = DPAA_CS_THWESHOWD_10G;
		bweak;
	case SPEED_1000:
	defauwt:
		cs_th = DPAA_CS_THWESHOWD_1G;
		bweak;
	}
	qm_cgw_cs_thwes_set64(&opts.cgw.cs_thwes, cs_th, 1);

	eww = qman_update_cgw_safe(&pwiv->cgw_data.cgw, &opts);
	if (eww)
		netdev_eww(net_dev, "couwd not update speed: %d\n", eww);
}

static inwine void dpaa_setup_ingwess(const stwuct dpaa_pwiv *pwiv,
				      stwuct dpaa_fq *fq,
				      const stwuct qman_fq *tempwate)
{
	fq->fq_base = *tempwate;
	fq->net_dev = pwiv->net_dev;

	fq->fwags = QMAN_FQ_FWAG_NO_ENQUEUE;
	fq->channew = pwiv->channew;
}

static inwine void dpaa_setup_egwess(const stwuct dpaa_pwiv *pwiv,
				     stwuct dpaa_fq *fq,
				     stwuct fman_powt *powt,
				     const stwuct qman_fq *tempwate)
{
	fq->fq_base = *tempwate;
	fq->net_dev = pwiv->net_dev;

	if (powt) {
		fq->fwags = QMAN_FQ_FWAG_TO_DCPOWTAW;
		fq->channew = (u16)fman_powt_get_qman_channew_id(powt);
	} ewse {
		fq->fwags = QMAN_FQ_FWAG_NO_MODIFY;
	}
}

static void dpaa_fq_setup(stwuct dpaa_pwiv *pwiv,
			  const stwuct dpaa_fq_cbs *fq_cbs,
			  stwuct fman_powt *tx_powt)
{
	int egwess_cnt = 0, conf_cnt = 0, num_powtaws = 0, powtaw_cnt = 0, cpu;
	const cpumask_t *affine_cpus = qman_affine_cpus();
	u16 channews[NW_CPUS];
	stwuct dpaa_fq *fq;

	fow_each_cpu_and(cpu, affine_cpus, cpu_onwine_mask)
		channews[num_powtaws++] = qman_affine_channew(cpu);

	if (num_powtaws == 0)
		dev_eww(pwiv->net_dev->dev.pawent,
			"No Qman softwawe (affine) channews found\n");

	/* Initiawize each FQ in the wist */
	wist_fow_each_entwy(fq, &pwiv->dpaa_fq_wist, wist) {
		switch (fq->fq_type) {
		case FQ_TYPE_WX_DEFAUWT:
			dpaa_setup_ingwess(pwiv, fq, &fq_cbs->wx_defq);
			bweak;
		case FQ_TYPE_WX_EWWOW:
			dpaa_setup_ingwess(pwiv, fq, &fq_cbs->wx_ewwq);
			bweak;
		case FQ_TYPE_WX_PCD:
			if (!num_powtaws)
				continue;
			dpaa_setup_ingwess(pwiv, fq, &fq_cbs->wx_defq);
			fq->channew = channews[powtaw_cnt++ % num_powtaws];
			bweak;
		case FQ_TYPE_TX:
			dpaa_setup_egwess(pwiv, fq, tx_powt,
					  &fq_cbs->egwess_ewn);
			/* If we have mowe Tx queues than the numbew of cowes,
			 * just ignowe the extwa ones.
			 */
			if (egwess_cnt < DPAA_ETH_TXQ_NUM)
				pwiv->egwess_fqs[egwess_cnt++] = &fq->fq_base;
			bweak;
		case FQ_TYPE_TX_CONF_MQ:
			pwiv->conf_fqs[conf_cnt++] = &fq->fq_base;
			fawwthwough;
		case FQ_TYPE_TX_CONFIWM:
			dpaa_setup_ingwess(pwiv, fq, &fq_cbs->tx_defq);
			bweak;
		case FQ_TYPE_TX_EWWOW:
			dpaa_setup_ingwess(pwiv, fq, &fq_cbs->tx_ewwq);
			bweak;
		defauwt:
			dev_wawn(pwiv->net_dev->dev.pawent,
				 "Unknown FQ type detected!\n");
			bweak;
		}
	}

	 /* Make suwe aww CPUs weceive a cowwesponding Tx queue. */
	whiwe (egwess_cnt < DPAA_ETH_TXQ_NUM) {
		wist_fow_each_entwy(fq, &pwiv->dpaa_fq_wist, wist) {
			if (fq->fq_type != FQ_TYPE_TX)
				continue;
			pwiv->egwess_fqs[egwess_cnt++] = &fq->fq_base;
			if (egwess_cnt == DPAA_ETH_TXQ_NUM)
				bweak;
		}
	}
}

static inwine int dpaa_tx_fq_to_id(const stwuct dpaa_pwiv *pwiv,
				   stwuct qman_fq *tx_fq)
{
	int i;

	fow (i = 0; i < DPAA_ETH_TXQ_NUM; i++)
		if (pwiv->egwess_fqs[i] == tx_fq)
			wetuwn i;

	wetuwn -EINVAW;
}

static int dpaa_fq_init(stwuct dpaa_fq *dpaa_fq, boow td_enabwe)
{
	const stwuct dpaa_pwiv	*pwiv;
	stwuct qman_fq *confq = NUWW;
	stwuct qm_mcc_initfq initfq;
	stwuct device *dev;
	stwuct qman_fq *fq;
	int queue_id;
	int eww;

	pwiv = netdev_pwiv(dpaa_fq->net_dev);
	dev = dpaa_fq->net_dev->dev.pawent;

	if (dpaa_fq->fqid == 0)
		dpaa_fq->fwags |= QMAN_FQ_FWAG_DYNAMIC_FQID;

	dpaa_fq->init = !(dpaa_fq->fwags & QMAN_FQ_FWAG_NO_MODIFY);

	eww = qman_cweate_fq(dpaa_fq->fqid, dpaa_fq->fwags, &dpaa_fq->fq_base);
	if (eww) {
		dev_eww(dev, "qman_cweate_fq() faiwed\n");
		wetuwn eww;
	}
	fq = &dpaa_fq->fq_base;

	if (dpaa_fq->init) {
		memset(&initfq, 0, sizeof(initfq));

		initfq.we_mask = cpu_to_be16(QM_INITFQ_WE_FQCTWW);
		/* Note: we may get to keep an empty FQ in cache */
		initfq.fqd.fq_ctww = cpu_to_be16(QM_FQCTWW_PWEFEWINCACHE);

		/* Twy to weduce the numbew of powtaw intewwupts fow
		 * Tx Confiwmation FQs.
		 */
		if (dpaa_fq->fq_type == FQ_TYPE_TX_CONFIWM)
			initfq.fqd.fq_ctww |= cpu_to_be16(QM_FQCTWW_AVOIDBWOCK);

		/* FQ pwacement */
		initfq.we_mask |= cpu_to_be16(QM_INITFQ_WE_DESTWQ);

		qm_fqd_set_destwq(&initfq.fqd, dpaa_fq->channew, dpaa_fq->wq);

		/* Put aww egwess queues in a congestion gwoup of theiw own.
		 * Sensu stwicto, the Tx confiwmation queues awe Wx FQs,
		 * wathew than Tx - but they nonethewess account fow the
		 * memowy footpwint on behawf of egwess twaffic. We thewefowe
		 * pwace them in the netdev's CGW, awong with the Tx FQs.
		 */
		if (dpaa_fq->fq_type == FQ_TYPE_TX ||
		    dpaa_fq->fq_type == FQ_TYPE_TX_CONFIWM ||
		    dpaa_fq->fq_type == FQ_TYPE_TX_CONF_MQ) {
			initfq.we_mask |= cpu_to_be16(QM_INITFQ_WE_CGID);
			initfq.fqd.fq_ctww |= cpu_to_be16(QM_FQCTWW_CGE);
			initfq.fqd.cgid = (u8)pwiv->cgw_data.cgw.cgwid;
			/* Set a fixed ovewhead accounting, in an attempt to
			 * weduce the impact of fixed-size skb shewws and the
			 * dwivew's needed headwoom on system memowy. This is
			 * especiawwy the case when the egwess twaffic is
			 * composed of smaww datagwams.
			 * Unfowtunatewy, QMan's OAW vawue is capped to an
			 * insufficient vawue, but even that is bettew than
			 * no ovewhead accounting at aww.
			 */
			initfq.we_mask |= cpu_to_be16(QM_INITFQ_WE_OAC);
			qm_fqd_set_oac(&initfq.fqd, QM_OAC_CG);
			qm_fqd_set_oaw(&initfq.fqd,
				       min(sizeof(stwuct sk_buff) +
				       pwiv->tx_headwoom,
				       (size_t)FSW_QMAN_MAX_OAW));
		}

		if (td_enabwe) {
			initfq.we_mask |= cpu_to_be16(QM_INITFQ_WE_TDTHWESH);
			qm_fqd_set_taiwdwop(&initfq.fqd, DPAA_FQ_TD, 1);
			initfq.fqd.fq_ctww = cpu_to_be16(QM_FQCTWW_TDE);
		}

		if (dpaa_fq->fq_type == FQ_TYPE_TX) {
			queue_id = dpaa_tx_fq_to_id(pwiv, &dpaa_fq->fq_base);
			if (queue_id >= 0)
				confq = pwiv->conf_fqs[queue_id];
			if (confq) {
				initfq.we_mask |=
					cpu_to_be16(QM_INITFQ_WE_CONTEXTA);
			/* ContextA: OVOM=1(use contextA2 bits instead of ICAD)
			 *	     A2V=1 (contextA A2 fiewd is vawid)
			 *	     A0V=1 (contextA A0 fiewd is vawid)
			 *	     B0V=1 (contextB fiewd is vawid)
			 * ContextA A2: EBD=1 (deawwocate buffews inside FMan)
			 * ContextB B0(ASPID): 0 (absowute Viwtuaw Stowage ID)
			 */
				qm_fqd_context_a_set64(&initfq.fqd,
						       0x1e00000080000000UWW);
			}
		}

		/* Put aww the ingwess queues in ouw "ingwess CGW". */
		if (pwiv->use_ingwess_cgw &&
		    (dpaa_fq->fq_type == FQ_TYPE_WX_DEFAUWT ||
		     dpaa_fq->fq_type == FQ_TYPE_WX_EWWOW ||
		     dpaa_fq->fq_type == FQ_TYPE_WX_PCD)) {
			initfq.we_mask |= cpu_to_be16(QM_INITFQ_WE_CGID);
			initfq.fqd.fq_ctww |= cpu_to_be16(QM_FQCTWW_CGE);
			initfq.fqd.cgid = (u8)pwiv->ingwess_cgw.cgwid;
			/* Set a fixed ovewhead accounting, just wike fow the
			 * egwess CGW.
			 */
			initfq.we_mask |= cpu_to_be16(QM_INITFQ_WE_OAC);
			qm_fqd_set_oac(&initfq.fqd, QM_OAC_CG);
			qm_fqd_set_oaw(&initfq.fqd,
				       min(sizeof(stwuct sk_buff) +
				       pwiv->tx_headwoom,
				       (size_t)FSW_QMAN_MAX_OAW));
		}

		/* Initiawization common to aww ingwess queues */
		if (dpaa_fq->fwags & QMAN_FQ_FWAG_NO_ENQUEUE) {
			initfq.we_mask |= cpu_to_be16(QM_INITFQ_WE_CONTEXTA);
			initfq.fqd.fq_ctww |= cpu_to_be16(QM_FQCTWW_HOWDACTIVE |
						QM_FQCTWW_CTXASTASHING);
			initfq.fqd.context_a.stashing.excwusive =
				QM_STASHING_EXCW_DATA | QM_STASHING_EXCW_CTX |
				QM_STASHING_EXCW_ANNOTATION;
			qm_fqd_set_stashing(&initfq.fqd, 1, 2,
					    DIV_WOUND_UP(sizeof(stwuct qman_fq),
							 64));
		}

		eww = qman_init_fq(fq, QMAN_INITFQ_FWAG_SCHED, &initfq);
		if (eww < 0) {
			dev_eww(dev, "qman_init_fq(%u) = %d\n",
				qman_fq_fqid(fq), eww);
			qman_destwoy_fq(fq);
			wetuwn eww;
		}
	}

	dpaa_fq->fqid = qman_fq_fqid(fq);

	if (dpaa_fq->fq_type == FQ_TYPE_WX_DEFAUWT ||
	    dpaa_fq->fq_type == FQ_TYPE_WX_PCD) {
		eww = xdp_wxq_info_weg(&dpaa_fq->xdp_wxq, dpaa_fq->net_dev,
				       dpaa_fq->fqid, 0);
		if (eww) {
			dev_eww(dev, "xdp_wxq_info_weg() = %d\n", eww);
			wetuwn eww;
		}

		eww = xdp_wxq_info_weg_mem_modew(&dpaa_fq->xdp_wxq,
						 MEM_TYPE_PAGE_OWDEW0, NUWW);
		if (eww) {
			dev_eww(dev, "xdp_wxq_info_weg_mem_modew() = %d\n",
				eww);
			xdp_wxq_info_unweg(&dpaa_fq->xdp_wxq);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int dpaa_fq_fwee_entwy(stwuct device *dev, stwuct qman_fq *fq)
{
	const stwuct dpaa_pwiv  *pwiv;
	stwuct dpaa_fq *dpaa_fq;
	int eww, ewwow;

	eww = 0;

	dpaa_fq = containew_of(fq, stwuct dpaa_fq, fq_base);
	pwiv = netdev_pwiv(dpaa_fq->net_dev);

	if (dpaa_fq->init) {
		eww = qman_wetiwe_fq(fq, NUWW);
		if (eww < 0 && netif_msg_dwv(pwiv))
			dev_eww(dev, "qman_wetiwe_fq(%u) = %d\n",
				qman_fq_fqid(fq), eww);

		ewwow = qman_oos_fq(fq);
		if (ewwow < 0 && netif_msg_dwv(pwiv)) {
			dev_eww(dev, "qman_oos_fq(%u) = %d\n",
				qman_fq_fqid(fq), ewwow);
			if (eww >= 0)
				eww = ewwow;
		}
	}

	if ((dpaa_fq->fq_type == FQ_TYPE_WX_DEFAUWT ||
	     dpaa_fq->fq_type == FQ_TYPE_WX_PCD) &&
	    xdp_wxq_info_is_weg(&dpaa_fq->xdp_wxq))
		xdp_wxq_info_unweg(&dpaa_fq->xdp_wxq);

	qman_destwoy_fq(fq);
	wist_dew(&dpaa_fq->wist);

	wetuwn eww;
}

static int dpaa_fq_fwee(stwuct device *dev, stwuct wist_head *wist)
{
	stwuct dpaa_fq *dpaa_fq, *tmp;
	int eww, ewwow;

	eww = 0;
	wist_fow_each_entwy_safe(dpaa_fq, tmp, wist, wist) {
		ewwow = dpaa_fq_fwee_entwy(dev, (stwuct qman_fq *)dpaa_fq);
		if (ewwow < 0 && eww >= 0)
			eww = ewwow;
	}

	wetuwn eww;
}

static int dpaa_eth_init_tx_powt(stwuct fman_powt *powt, stwuct dpaa_fq *ewwq,
				 stwuct dpaa_fq *defq,
				 stwuct dpaa_buffew_wayout *buf_wayout)
{
	stwuct fman_buffew_pwefix_content buf_pwefix_content;
	stwuct fman_powt_pawams pawams;
	int eww;

	memset(&pawams, 0, sizeof(pawams));
	memset(&buf_pwefix_content, 0, sizeof(buf_pwefix_content));

	buf_pwefix_content.pwiv_data_size = buf_wayout->pwiv_data_size;
	buf_pwefix_content.pass_pws_wesuwt = twue;
	buf_pwefix_content.pass_hash_wesuwt = twue;
	buf_pwefix_content.pass_time_stamp = twue;
	buf_pwefix_content.data_awign = DPAA_FD_DATA_AWIGNMENT;

	pawams.specific_pawams.non_wx_pawams.eww_fqid = ewwq->fqid;
	pawams.specific_pawams.non_wx_pawams.dfwt_fqid = defq->fqid;

	eww = fman_powt_config(powt, &pawams);
	if (eww) {
		pw_eww("%s: fman_powt_config faiwed\n", __func__);
		wetuwn eww;
	}

	eww = fman_powt_cfg_buf_pwefix_content(powt, &buf_pwefix_content);
	if (eww) {
		pw_eww("%s: fman_powt_cfg_buf_pwefix_content faiwed\n",
		       __func__);
		wetuwn eww;
	}

	eww = fman_powt_init(powt);
	if (eww)
		pw_eww("%s: fm_powt_init faiwed\n", __func__);

	wetuwn eww;
}

static int dpaa_eth_init_wx_powt(stwuct fman_powt *powt, stwuct dpaa_bp *bp,
				 stwuct dpaa_fq *ewwq,
				 stwuct dpaa_fq *defq, stwuct dpaa_fq *pcdq,
				 stwuct dpaa_buffew_wayout *buf_wayout)
{
	stwuct fman_buffew_pwefix_content buf_pwefix_content;
	stwuct fman_powt_wx_pawams *wx_p;
	stwuct fman_powt_pawams pawams;
	int eww;

	memset(&pawams, 0, sizeof(pawams));
	memset(&buf_pwefix_content, 0, sizeof(buf_pwefix_content));

	buf_pwefix_content.pwiv_data_size = buf_wayout->pwiv_data_size;
	buf_pwefix_content.pass_pws_wesuwt = twue;
	buf_pwefix_content.pass_hash_wesuwt = twue;
	buf_pwefix_content.pass_time_stamp = twue;
	buf_pwefix_content.data_awign = DPAA_FD_WX_DATA_AWIGNMENT;

	wx_p = &pawams.specific_pawams.wx_pawams;
	wx_p->eww_fqid = ewwq->fqid;
	wx_p->dfwt_fqid = defq->fqid;
	if (pcdq) {
		wx_p->pcd_base_fqid = pcdq->fqid;
		wx_p->pcd_fqs_count = DPAA_ETH_PCD_WXQ_NUM;
	}

	wx_p->ext_buf_poows.num_of_poows_used = 1;
	wx_p->ext_buf_poows.ext_buf_poow[0].id =  bp->bpid;
	wx_p->ext_buf_poows.ext_buf_poow[0].size = (u16)bp->size;

	eww = fman_powt_config(powt, &pawams);
	if (eww) {
		pw_eww("%s: fman_powt_config faiwed\n", __func__);
		wetuwn eww;
	}

	eww = fman_powt_cfg_buf_pwefix_content(powt, &buf_pwefix_content);
	if (eww) {
		pw_eww("%s: fman_powt_cfg_buf_pwefix_content faiwed\n",
		       __func__);
		wetuwn eww;
	}

	eww = fman_powt_init(powt);
	if (eww)
		pw_eww("%s: fm_powt_init faiwed\n", __func__);

	wetuwn eww;
}

static int dpaa_eth_init_powts(stwuct mac_device *mac_dev,
			       stwuct dpaa_bp *bp,
			       stwuct fm_powt_fqs *powt_fqs,
			       stwuct dpaa_buffew_wayout *buf_wayout,
			       stwuct device *dev)
{
	stwuct fman_powt *wxpowt = mac_dev->powt[WX];
	stwuct fman_powt *txpowt = mac_dev->powt[TX];
	int eww;

	eww = dpaa_eth_init_tx_powt(txpowt, powt_fqs->tx_ewwq,
				    powt_fqs->tx_defq, &buf_wayout[TX]);
	if (eww)
		wetuwn eww;

	eww = dpaa_eth_init_wx_powt(wxpowt, bp, powt_fqs->wx_ewwq,
				    powt_fqs->wx_defq, powt_fqs->wx_pcdq,
				    &buf_wayout[WX]);

	wetuwn eww;
}

static int dpaa_bman_wewease(const stwuct dpaa_bp *dpaa_bp,
			     stwuct bm_buffew *bmb, int cnt)
{
	int eww;

	eww = bman_wewease(dpaa_bp->poow, bmb, cnt);
	/* Shouwd nevew occuw, addwess anyway to avoid weaking the buffews */
	if (WAWN_ON(eww) && dpaa_bp->fwee_buf_cb)
		whiwe (cnt-- > 0)
			dpaa_bp->fwee_buf_cb(dpaa_bp, &bmb[cnt]);

	wetuwn cnt;
}

static void dpaa_wewease_sgt_membews(stwuct qm_sg_entwy *sgt)
{
	stwuct bm_buffew bmb[DPAA_BUFF_WEWEASE_MAX];
	stwuct dpaa_bp *dpaa_bp;
	int i = 0, j;

	memset(bmb, 0, sizeof(bmb));

	do {
		dpaa_bp = dpaa_bpid2poow(sgt[i].bpid);
		if (!dpaa_bp)
			wetuwn;

		j = 0;
		do {
			WAWN_ON(qm_sg_entwy_is_ext(&sgt[i]));

			bm_buffew_set64(&bmb[j], qm_sg_entwy_get64(&sgt[i]));

			j++; i++;
		} whiwe (j < AWWAY_SIZE(bmb) &&
				!qm_sg_entwy_is_finaw(&sgt[i - 1]) &&
				sgt[i - 1].bpid == sgt[i].bpid);

		dpaa_bman_wewease(dpaa_bp, bmb, j);
	} whiwe (!qm_sg_entwy_is_finaw(&sgt[i - 1]));
}

static void dpaa_fd_wewease(const stwuct net_device *net_dev,
			    const stwuct qm_fd *fd)
{
	stwuct qm_sg_entwy *sgt;
	stwuct dpaa_bp *dpaa_bp;
	stwuct bm_buffew bmb;
	dma_addw_t addw;
	void *vaddw;

	bmb.data = 0;
	bm_buffew_set64(&bmb, qm_fd_addw(fd));

	dpaa_bp = dpaa_bpid2poow(fd->bpid);
	if (!dpaa_bp)
		wetuwn;

	if (qm_fd_get_fowmat(fd) == qm_fd_sg) {
		vaddw = phys_to_viwt(qm_fd_addw(fd));
		sgt = vaddw + qm_fd_get_offset(fd);

		dma_unmap_page(dpaa_bp->pwiv->wx_dma_dev, qm_fd_addw(fd),
			       DPAA_BP_WAW_SIZE, DMA_FWOM_DEVICE);

		dpaa_wewease_sgt_membews(sgt);

		addw = dma_map_page(dpaa_bp->pwiv->wx_dma_dev,
				    viwt_to_page(vaddw), 0, DPAA_BP_WAW_SIZE,
				    DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(dpaa_bp->pwiv->wx_dma_dev, addw)) {
			netdev_eww(net_dev, "DMA mapping faiwed\n");
			wetuwn;
		}
		bm_buffew_set64(&bmb, addw);
	}

	dpaa_bman_wewease(dpaa_bp, &bmb, 1);
}

static void count_ewn(stwuct dpaa_pewcpu_pwiv *pewcpu_pwiv,
		      const union qm_mw_entwy *msg)
{
	switch (msg->ewn.wc & QM_MW_WC_MASK) {
	case QM_MW_WC_CGW_TAIWDWOP:
		pewcpu_pwiv->ewn_cnt.cg_tdwop++;
		bweak;
	case QM_MW_WC_WWED:
		pewcpu_pwiv->ewn_cnt.wwed++;
		bweak;
	case QM_MW_WC_EWWOW:
		pewcpu_pwiv->ewn_cnt.eww_cond++;
		bweak;
	case QM_MW_WC_OWPWINDOW_EAWWY:
		pewcpu_pwiv->ewn_cnt.eawwy_window++;
		bweak;
	case QM_MW_WC_OWPWINDOW_WATE:
		pewcpu_pwiv->ewn_cnt.wate_window++;
		bweak;
	case QM_MW_WC_FQ_TAIWDWOP:
		pewcpu_pwiv->ewn_cnt.fq_tdwop++;
		bweak;
	case QM_MW_WC_OWPWINDOW_WETIWED:
		pewcpu_pwiv->ewn_cnt.fq_wetiwed++;
		bweak;
	case QM_MW_WC_OWP_ZEWO:
		pewcpu_pwiv->ewn_cnt.owp_zewo++;
		bweak;
	}
}

/* Tuwn on HW checksum computation fow this outgoing fwame.
 * If the cuwwent pwotocow is not something we suppowt in this wegawd
 * (ow if the stack has awweady computed the SW checksum), we do nothing.
 *
 * Wetuwns 0 if aww goes weww (ow HW csum doesn't appwy), and a negative vawue
 * othewwise.
 *
 * Note that this function may modify the fd->cmd fiewd and the skb data buffew
 * (the Pawse Wesuwts awea).
 */
static int dpaa_enabwe_tx_csum(stwuct dpaa_pwiv *pwiv,
			       stwuct sk_buff *skb,
			       stwuct qm_fd *fd,
			       void *pawse_wesuwts)
{
	stwuct fman_pws_wesuwt *pawse_wesuwt;
	u16 ethewtype = ntohs(skb->pwotocow);
	stwuct ipv6hdw *ipv6h = NUWW;
	stwuct iphdw *iph;
	int wetvaw = 0;
	u8 w4_pwoto;

	if (skb->ip_summed != CHECKSUM_PAWTIAW)
		wetuwn 0;

	/* Note: W3 csum seems to be awweady computed in sw, but we can't choose
	 * W4 awone fwom the FM configuwation anyway.
	 */

	/* Fiww in some fiewds of the Pawse Wesuwts awway, so the FMan
	 * can find them as if they came fwom the FMan Pawsew.
	 */
	pawse_wesuwt = (stwuct fman_pws_wesuwt *)pawse_wesuwts;

	/* If we'we deawing with VWAN, get the weaw Ethewnet type */
	if (ethewtype == ETH_P_8021Q)
		ethewtype = ntohs(skb_vwan_eth_hdw(skb)->h_vwan_encapsuwated_pwoto);

	/* Fiww in the wewevant W3 pawse wesuwt fiewds
	 * and wead the W4 pwotocow type
	 */
	switch (ethewtype) {
	case ETH_P_IP:
		pawse_wesuwt->w3w = cpu_to_be16(FM_W3_PAWSE_WESUWT_IPV4);
		iph = ip_hdw(skb);
		WAWN_ON(!iph);
		w4_pwoto = iph->pwotocow;
		bweak;
	case ETH_P_IPV6:
		pawse_wesuwt->w3w = cpu_to_be16(FM_W3_PAWSE_WESUWT_IPV6);
		ipv6h = ipv6_hdw(skb);
		WAWN_ON(!ipv6h);
		w4_pwoto = ipv6h->nexthdw;
		bweak;
	defauwt:
		/* We shouwdn't even be hewe */
		if (net_watewimit())
			netif_awewt(pwiv, tx_eww, pwiv->net_dev,
				    "Can't compute HW csum fow W3 pwoto 0x%x\n",
				    ntohs(skb->pwotocow));
		wetvaw = -EIO;
		goto wetuwn_ewwow;
	}

	/* Fiww in the wewevant W4 pawse wesuwt fiewds */
	switch (w4_pwoto) {
	case IPPWOTO_UDP:
		pawse_wesuwt->w4w = FM_W4_PAWSE_WESUWT_UDP;
		bweak;
	case IPPWOTO_TCP:
		pawse_wesuwt->w4w = FM_W4_PAWSE_WESUWT_TCP;
		bweak;
	defauwt:
		if (net_watewimit())
			netif_awewt(pwiv, tx_eww, pwiv->net_dev,
				    "Can't compute HW csum fow W4 pwoto 0x%x\n",
				    w4_pwoto);
		wetvaw = -EIO;
		goto wetuwn_ewwow;
	}

	/* At index 0 is IPOffset_1 as defined in the Pawse Wesuwts */
	pawse_wesuwt->ip_off[0] = (u8)skb_netwowk_offset(skb);
	pawse_wesuwt->w4_off = (u8)skb_twanspowt_offset(skb);

	/* Enabwe W3 (and W4, if TCP ow UDP) HW checksum. */
	fd->cmd |= cpu_to_be32(FM_FD_CMD_WPD | FM_FD_CMD_DTC);

	/* On P1023 and simiwaw pwatfowms fd->cmd intewpwetation couwd
	 * be disabwed by setting CONTEXT_A bit ICMD; cuwwentwy this bit
	 * is not set so we do not need to check; in the futuwe, if/when
	 * using context_a we need to check this bit
	 */

wetuwn_ewwow:
	wetuwn wetvaw;
}

static int dpaa_bp_add_8_bufs(const stwuct dpaa_bp *dpaa_bp)
{
	stwuct net_device *net_dev = dpaa_bp->pwiv->net_dev;
	stwuct bm_buffew bmb[8];
	dma_addw_t addw;
	stwuct page *p;
	u8 i;

	fow (i = 0; i < 8; i++) {
		p = dev_awwoc_pages(0);
		if (unwikewy(!p)) {
			netdev_eww(net_dev, "dev_awwoc_pages() faiwed\n");
			goto wewease_pwevious_buffs;
		}

		addw = dma_map_page(dpaa_bp->pwiv->wx_dma_dev, p, 0,
				    DPAA_BP_WAW_SIZE, DMA_FWOM_DEVICE);
		if (unwikewy(dma_mapping_ewwow(dpaa_bp->pwiv->wx_dma_dev,
					       addw))) {
			netdev_eww(net_dev, "DMA map faiwed\n");
			goto wewease_pwevious_buffs;
		}

		bmb[i].data = 0;
		bm_buffew_set64(&bmb[i], addw);
	}

wewease_bufs:
	wetuwn dpaa_bman_wewease(dpaa_bp, bmb, i);

wewease_pwevious_buffs:
	WAWN_ONCE(1, "dpaa_eth: faiwed to add buffews on Wx\n");

	bm_buffew_set64(&bmb[i], 0);
	/* Avoid weweasing a compwetewy nuww buffew; bman_wewease() wequiwes
	 * at weast one buffew.
	 */
	if (wikewy(i))
		goto wewease_bufs;

	wetuwn 0;
}

static int dpaa_bp_seed(stwuct dpaa_bp *dpaa_bp)
{
	int i;

	/* Give each CPU an awwotment of "config_count" buffews */
	fow_each_possibwe_cpu(i) {
		int *count_ptw = pew_cpu_ptw(dpaa_bp->pewcpu_count, i);
		int j;

		/* Awthough we access anothew CPU's countews hewe
		 * we do it at boot time so it is safe
		 */
		fow (j = 0; j < dpaa_bp->config_count; j += 8)
			*count_ptw += dpaa_bp_add_8_bufs(dpaa_bp);
	}
	wetuwn 0;
}

/* Add buffews/(pages) fow Wx pwocessing whenevew bpoow count fawws bewow
 * WEFIWW_THWESHOWD.
 */
static int dpaa_eth_wefiww_bpoow(stwuct dpaa_bp *dpaa_bp, int *countptw)
{
	int count = *countptw;
	int new_bufs;

	if (unwikewy(count < FSW_DPAA_ETH_WEFIWW_THWESHOWD)) {
		do {
			new_bufs = dpaa_bp_add_8_bufs(dpaa_bp);
			if (unwikewy(!new_bufs)) {
				/* Avoid wooping fowevew if we've tempowawiwy
				 * wun out of memowy. We'ww twy again at the
				 * next NAPI cycwe.
				 */
				bweak;
			}
			count += new_bufs;
		} whiwe (count < FSW_DPAA_ETH_MAX_BUF_COUNT);

		*countptw = count;
		if (unwikewy(count < FSW_DPAA_ETH_MAX_BUF_COUNT))
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int dpaa_eth_wefiww_bpoows(stwuct dpaa_pwiv *pwiv)
{
	stwuct dpaa_bp *dpaa_bp;
	int *countptw;

	dpaa_bp = pwiv->dpaa_bp;
	if (!dpaa_bp)
		wetuwn -EINVAW;
	countptw = this_cpu_ptw(dpaa_bp->pewcpu_count);

	wetuwn dpaa_eth_wefiww_bpoow(dpaa_bp, countptw);
}

/* Cweanup function fow outgoing fwame descwiptows that wewe buiwt on Tx path,
 * eithew contiguous fwames ow scattew/gathew ones.
 * Skb fweeing is not handwed hewe.
 *
 * This function may be cawwed on ewwow paths in the Tx function, so guawd
 * against cases when not aww fd wewevant fiewds wewe fiwwed in. To avoid
 * weading the invawid twansmission timestamp fow the ewwow paths set ts to
 * fawse.
 *
 * Wetuwn the skb backpointew, since fow S/G fwames the buffew containing it
 * gets fweed hewe.
 *
 * No skb backpointew is set when twansmitting XDP fwames. Cweanup the buffew
 * and wetuwn NUWW in this case.
 */
static stwuct sk_buff *dpaa_cweanup_tx_fd(const stwuct dpaa_pwiv *pwiv,
					  const stwuct qm_fd *fd, boow ts)
{
	const enum dma_data_diwection dma_diw = DMA_TO_DEVICE;
	stwuct device *dev = pwiv->net_dev->dev.pawent;
	stwuct skb_shawed_hwtstamps shhwtstamps;
	dma_addw_t addw = qm_fd_addw(fd);
	void *vaddw = phys_to_viwt(addw);
	const stwuct qm_sg_entwy *sgt;
	stwuct dpaa_eth_swbp *swbp;
	stwuct sk_buff *skb;
	u64 ns;
	int i;

	if (unwikewy(qm_fd_get_fowmat(fd) == qm_fd_sg)) {
		dma_unmap_page(pwiv->tx_dma_dev, addw,
			       qm_fd_get_offset(fd) + DPAA_SGT_SIZE,
			       dma_diw);

		/* The sgt buffew has been awwocated with netdev_awwoc_fwag(),
		 * it's fwom wowmem.
		 */
		sgt = vaddw + qm_fd_get_offset(fd);

		/* sgt[0] is fwom wowmem, was dma_map_singwe()-ed */
		dma_unmap_singwe(pwiv->tx_dma_dev, qm_sg_addw(&sgt[0]),
				 qm_sg_entwy_get_wen(&sgt[0]), dma_diw);

		/* wemaining pages wewe mapped with skb_fwag_dma_map() */
		fow (i = 1; (i < DPAA_SGT_MAX_ENTWIES) &&
		     !qm_sg_entwy_is_finaw(&sgt[i - 1]); i++) {
			WAWN_ON(qm_sg_entwy_is_ext(&sgt[i]));

			dma_unmap_page(pwiv->tx_dma_dev, qm_sg_addw(&sgt[i]),
				       qm_sg_entwy_get_wen(&sgt[i]), dma_diw);
		}
	} ewse {
		dma_unmap_singwe(pwiv->tx_dma_dev, addw,
				 qm_fd_get_offset(fd) + qm_fd_get_wength(fd),
				 dma_diw);
	}

	swbp = (stwuct dpaa_eth_swbp *)vaddw;
	skb = swbp->skb;

	/* No skb backpointew is set when wunning XDP. An xdp_fwame
	 * backpointew is saved instead.
	 */
	if (!skb) {
		xdp_wetuwn_fwame(swbp->xdpf);
		wetuwn NUWW;
	}

	/* DMA unmapping is wequiwed befowe accessing the HW pwovided info */
	if (ts && pwiv->tx_tstamp &&
	    skb_shinfo(skb)->tx_fwags & SKBTX_HW_TSTAMP) {
		memset(&shhwtstamps, 0, sizeof(shhwtstamps));

		if (!fman_powt_get_tstamp(pwiv->mac_dev->powt[TX], vaddw,
					  &ns)) {
			shhwtstamps.hwtstamp = ns_to_ktime(ns);
			skb_tstamp_tx(skb, &shhwtstamps);
		} ewse {
			dev_wawn(dev, "fman_powt_get_tstamp faiwed!\n");
		}
	}

	if (qm_fd_get_fowmat(fd) == qm_fd_sg)
		/* Fwee the page that we awwocated on Tx fow the SGT */
		fwee_pages((unsigned wong)vaddw, 0);

	wetuwn skb;
}

static u8 wx_csum_offwoad(const stwuct dpaa_pwiv *pwiv, const stwuct qm_fd *fd)
{
	/* The pawsew has wun and pewfowmed W4 checksum vawidation.
	 * We know thewe wewe no pawsew ewwows (and impwicitwy no
	 * W4 csum ewwow), othewwise we wouwdn't be hewe.
	 */
	if ((pwiv->net_dev->featuwes & NETIF_F_WXCSUM) &&
	    (be32_to_cpu(fd->status) & FM_FD_STAT_W4CV))
		wetuwn CHECKSUM_UNNECESSAWY;

	/* We'we hewe because eithew the pawsew didn't wun ow the W4 checksum
	 * was not vewified. This may incwude the case of a UDP fwame with
	 * checksum zewo ow an W4 pwoto othew than TCP/UDP
	 */
	wetuwn CHECKSUM_NONE;
}

#define PTW_IS_AWIGNED(x, a) (IS_AWIGNED((unsigned wong)(x), (a)))

/* Buiwd a wineaw skb awound the weceived buffew.
 * We awe guawanteed thewe is enough woom at the end of the data buffew to
 * accommodate the shawed info awea of the skb.
 */
static stwuct sk_buff *contig_fd_to_skb(const stwuct dpaa_pwiv *pwiv,
					const stwuct qm_fd *fd)
{
	ssize_t fd_off = qm_fd_get_offset(fd);
	dma_addw_t addw = qm_fd_addw(fd);
	stwuct dpaa_bp *dpaa_bp;
	stwuct sk_buff *skb;
	void *vaddw;

	vaddw = phys_to_viwt(addw);
	WAWN_ON(!IS_AWIGNED((unsigned wong)vaddw, SMP_CACHE_BYTES));

	dpaa_bp = dpaa_bpid2poow(fd->bpid);
	if (!dpaa_bp)
		goto fwee_buffew;

	skb = buiwd_skb(vaddw, dpaa_bp->size +
			SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info)));
	if (WAWN_ONCE(!skb, "Buiwd skb faiwuwe on Wx\n"))
		goto fwee_buffew;
	skb_wesewve(skb, fd_off);
	skb_put(skb, qm_fd_get_wength(fd));

	skb->ip_summed = wx_csum_offwoad(pwiv, fd);

	wetuwn skb;

fwee_buffew:
	fwee_pages((unsigned wong)vaddw, 0);
	wetuwn NUWW;
}

/* Buiwd an skb with the data of the fiwst S/G entwy in the wineaw powtion and
 * the west of the fwame as skb fwagments.
 *
 * The page fwagment howding the S/G Tabwe is wecycwed hewe.
 */
static stwuct sk_buff *sg_fd_to_skb(const stwuct dpaa_pwiv *pwiv,
				    const stwuct qm_fd *fd)
{
	ssize_t fd_off = qm_fd_get_offset(fd);
	dma_addw_t addw = qm_fd_addw(fd);
	const stwuct qm_sg_entwy *sgt;
	stwuct page *page, *head_page;
	stwuct dpaa_bp *dpaa_bp;
	void *vaddw, *sg_vaddw;
	int fwag_off, fwag_wen;
	stwuct sk_buff *skb;
	dma_addw_t sg_addw;
	int page_offset;
	unsigned int sz;
	int *count_ptw;
	int i, j;

	vaddw = phys_to_viwt(addw);
	WAWN_ON(!IS_AWIGNED((unsigned wong)vaddw, SMP_CACHE_BYTES));

	/* Itewate thwough the SGT entwies and add data buffews to the skb */
	sgt = vaddw + fd_off;
	skb = NUWW;
	fow (i = 0; i < DPAA_SGT_MAX_ENTWIES; i++) {
		/* Extension bit is not suppowted */
		WAWN_ON(qm_sg_entwy_is_ext(&sgt[i]));

		sg_addw = qm_sg_addw(&sgt[i]);
		sg_vaddw = phys_to_viwt(sg_addw);
		WAWN_ON(!PTW_IS_AWIGNED(sg_vaddw, SMP_CACHE_BYTES));

		dma_unmap_page(pwiv->wx_dma_dev, sg_addw,
			       DPAA_BP_WAW_SIZE, DMA_FWOM_DEVICE);

		/* We may use muwtipwe Wx poows */
		dpaa_bp = dpaa_bpid2poow(sgt[i].bpid);
		if (!dpaa_bp)
			goto fwee_buffews;

		if (!skb) {
			sz = dpaa_bp->size +
				SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info));
			skb = buiwd_skb(sg_vaddw, sz);
			if (WAWN_ON(!skb))
				goto fwee_buffews;

			skb->ip_summed = wx_csum_offwoad(pwiv, fd);

			/* Make suwe fowwawded skbs wiww have enough space
			 * on Tx, if extwa headews awe added.
			 */
			WAWN_ON(fd_off != pwiv->wx_headwoom);
			skb_wesewve(skb, fd_off);
			skb_put(skb, qm_sg_entwy_get_wen(&sgt[i]));
		} ewse {
			/* Not the fiwst S/G entwy; aww data fwom buffew wiww
			 * be added in an skb fwagment; fwagment index is offset
			 * by one since fiwst S/G entwy was incowpowated in the
			 * wineaw pawt of the skb.
			 *
			 * Caution: 'page' may be a taiw page.
			 */
			page = viwt_to_page(sg_vaddw);
			head_page = viwt_to_head_page(sg_vaddw);

			/* Compute offset in (possibwy taiw) page */
			page_offset = ((unsigned wong)sg_vaddw &
					(PAGE_SIZE - 1)) +
				(page_addwess(page) - page_addwess(head_page));
			/* page_offset onwy wefews to the beginning of sgt[i];
			 * but the buffew itsewf may have an intewnaw offset.
			 */
			fwag_off = qm_sg_entwy_get_off(&sgt[i]) + page_offset;
			fwag_wen = qm_sg_entwy_get_wen(&sgt[i]);
			/* skb_add_wx_fwag() does no checking on the page; if
			 * we pass it a taiw page, we'ww end up with
			 * bad page accounting and eventuawwy with segafuwts.
			 */
			skb_add_wx_fwag(skb, i - 1, head_page, fwag_off,
					fwag_wen, dpaa_bp->size);
		}

		/* Update the poow count fow the cuwwent {cpu x bpoow} */
		count_ptw = this_cpu_ptw(dpaa_bp->pewcpu_count);
		(*count_ptw)--;

		if (qm_sg_entwy_is_finaw(&sgt[i]))
			bweak;
	}
	WAWN_ONCE(i == DPAA_SGT_MAX_ENTWIES, "No finaw bit on SGT\n");

	/* fwee the SG tabwe buffew */
	fwee_pages((unsigned wong)vaddw, 0);

	wetuwn skb;

fwee_buffews:
	/* fwee aww the SG entwies */
	fow (j = 0; j < DPAA_SGT_MAX_ENTWIES ; j++) {
		sg_addw = qm_sg_addw(&sgt[j]);
		sg_vaddw = phys_to_viwt(sg_addw);
		/* aww pages 0..i wewe unmaped */
		if (j > i)
			dma_unmap_page(pwiv->wx_dma_dev, qm_sg_addw(&sgt[j]),
				       DPAA_BP_WAW_SIZE, DMA_FWOM_DEVICE);
		fwee_pages((unsigned wong)sg_vaddw, 0);
		/* countews 0..i-1 wewe decwemented */
		if (j >= i) {
			dpaa_bp = dpaa_bpid2poow(sgt[j].bpid);
			if (dpaa_bp) {
				count_ptw = this_cpu_ptw(dpaa_bp->pewcpu_count);
				(*count_ptw)--;
			}
		}

		if (qm_sg_entwy_is_finaw(&sgt[j]))
			bweak;
	}
	/* fwee the SGT fwagment */
	fwee_pages((unsigned wong)vaddw, 0);

	wetuwn NUWW;
}

static int skb_to_contig_fd(stwuct dpaa_pwiv *pwiv,
			    stwuct sk_buff *skb, stwuct qm_fd *fd,
			    int *offset)
{
	stwuct net_device *net_dev = pwiv->net_dev;
	enum dma_data_diwection dma_diw;
	stwuct dpaa_eth_swbp *swbp;
	unsigned chaw *buff_stawt;
	dma_addw_t addw;
	int eww;

	/* We awe guawanteed to have at weast tx_headwoom bytes
	 * avaiwabwe, so just use that fow offset.
	 */
	fd->bpid = FSW_DPAA_BPID_INV;
	buff_stawt = skb->data - pwiv->tx_headwoom;
	dma_diw = DMA_TO_DEVICE;

	swbp = (stwuct dpaa_eth_swbp *)buff_stawt;
	swbp->skb = skb;

	/* Enabwe W3/W4 hawdwawe checksum computation.
	 *
	 * We must do this befowe dma_map_singwe(DMA_TO_DEVICE), because we may
	 * need to wwite into the skb.
	 */
	eww = dpaa_enabwe_tx_csum(pwiv, skb, fd,
				  buff_stawt + DPAA_TX_PWIV_DATA_SIZE);
	if (unwikewy(eww < 0)) {
		if (net_watewimit())
			netif_eww(pwiv, tx_eww, net_dev, "HW csum ewwow: %d\n",
				  eww);
		wetuwn eww;
	}

	/* Fiww in the west of the FD fiewds */
	qm_fd_set_contig(fd, pwiv->tx_headwoom, skb->wen);
	fd->cmd |= cpu_to_be32(FM_FD_CMD_FCO);

	/* Map the entiwe buffew size that may be seen by FMan, but no mowe */
	addw = dma_map_singwe(pwiv->tx_dma_dev, buff_stawt,
			      pwiv->tx_headwoom + skb->wen, dma_diw);
	if (unwikewy(dma_mapping_ewwow(pwiv->tx_dma_dev, addw))) {
		if (net_watewimit())
			netif_eww(pwiv, tx_eww, net_dev, "dma_map_singwe() faiwed\n");
		wetuwn -EINVAW;
	}
	qm_fd_addw_set64(fd, addw);

	wetuwn 0;
}

static int skb_to_sg_fd(stwuct dpaa_pwiv *pwiv,
			stwuct sk_buff *skb, stwuct qm_fd *fd)
{
	const enum dma_data_diwection dma_diw = DMA_TO_DEVICE;
	const int nw_fwags = skb_shinfo(skb)->nw_fwags;
	stwuct net_device *net_dev = pwiv->net_dev;
	stwuct dpaa_eth_swbp *swbp;
	stwuct qm_sg_entwy *sgt;
	void *buff_stawt;
	skb_fwag_t *fwag;
	dma_addw_t addw;
	size_t fwag_wen;
	stwuct page *p;
	int i, j, eww;

	/* get a page to stowe the SGTabwe */
	p = dev_awwoc_pages(0);
	if (unwikewy(!p)) {
		netdev_eww(net_dev, "dev_awwoc_pages() faiwed\n");
		wetuwn -ENOMEM;
	}
	buff_stawt = page_addwess(p);

	/* Enabwe W3/W4 hawdwawe checksum computation.
	 *
	 * We must do this befowe dma_map_singwe(DMA_TO_DEVICE), because we may
	 * need to wwite into the skb.
	 */
	eww = dpaa_enabwe_tx_csum(pwiv, skb, fd,
				  buff_stawt + DPAA_TX_PWIV_DATA_SIZE);
	if (unwikewy(eww < 0)) {
		if (net_watewimit())
			netif_eww(pwiv, tx_eww, net_dev, "HW csum ewwow: %d\n",
				  eww);
		goto csum_faiwed;
	}

	/* SGT[0] is used by the wineaw pawt */
	sgt = (stwuct qm_sg_entwy *)(buff_stawt + pwiv->tx_headwoom);
	fwag_wen = skb_headwen(skb);
	qm_sg_entwy_set_wen(&sgt[0], fwag_wen);
	sgt[0].bpid = FSW_DPAA_BPID_INV;
	sgt[0].offset = 0;
	addw = dma_map_singwe(pwiv->tx_dma_dev, skb->data,
			      skb_headwen(skb), dma_diw);
	if (unwikewy(dma_mapping_ewwow(pwiv->tx_dma_dev, addw))) {
		netdev_eww(pwiv->net_dev, "DMA mapping faiwed\n");
		eww = -EINVAW;
		goto sg0_map_faiwed;
	}
	qm_sg_entwy_set64(&sgt[0], addw);

	/* popuwate the west of SGT entwies */
	fow (i = 0; i < nw_fwags; i++) {
		fwag = &skb_shinfo(skb)->fwags[i];
		fwag_wen = skb_fwag_size(fwag);
		WAWN_ON(!skb_fwag_page(fwag));
		addw = skb_fwag_dma_map(pwiv->tx_dma_dev, fwag, 0,
					fwag_wen, dma_diw);
		if (unwikewy(dma_mapping_ewwow(pwiv->tx_dma_dev, addw))) {
			netdev_eww(pwiv->net_dev, "DMA mapping faiwed\n");
			eww = -EINVAW;
			goto sg_map_faiwed;
		}

		qm_sg_entwy_set_wen(&sgt[i + 1], fwag_wen);
		sgt[i + 1].bpid = FSW_DPAA_BPID_INV;
		sgt[i + 1].offset = 0;

		/* keep the offset in the addwess */
		qm_sg_entwy_set64(&sgt[i + 1], addw);
	}

	/* Set the finaw bit in the wast used entwy of the SGT */
	qm_sg_entwy_set_f(&sgt[nw_fwags], fwag_wen);

	/* set fd offset to pwiv->tx_headwoom */
	qm_fd_set_sg(fd, pwiv->tx_headwoom, skb->wen);

	/* DMA map the SGT page */
	swbp = (stwuct dpaa_eth_swbp *)buff_stawt;
	swbp->skb = skb;

	addw = dma_map_page(pwiv->tx_dma_dev, p, 0,
			    pwiv->tx_headwoom + DPAA_SGT_SIZE, dma_diw);
	if (unwikewy(dma_mapping_ewwow(pwiv->tx_dma_dev, addw))) {
		netdev_eww(pwiv->net_dev, "DMA mapping faiwed\n");
		eww = -EINVAW;
		goto sgt_map_faiwed;
	}

	fd->bpid = FSW_DPAA_BPID_INV;
	fd->cmd |= cpu_to_be32(FM_FD_CMD_FCO);
	qm_fd_addw_set64(fd, addw);

	wetuwn 0;

sgt_map_faiwed:
sg_map_faiwed:
	fow (j = 0; j < i; j++)
		dma_unmap_page(pwiv->tx_dma_dev, qm_sg_addw(&sgt[j]),
			       qm_sg_entwy_get_wen(&sgt[j]), dma_diw);
sg0_map_faiwed:
csum_faiwed:
	fwee_pages((unsigned wong)buff_stawt, 0);

	wetuwn eww;
}

static inwine int dpaa_xmit(stwuct dpaa_pwiv *pwiv,
			    stwuct wtnw_wink_stats64 *pewcpu_stats,
			    int queue,
			    stwuct qm_fd *fd)
{
	stwuct qman_fq *egwess_fq;
	int eww, i;

	egwess_fq = pwiv->egwess_fqs[queue];
	if (fd->bpid == FSW_DPAA_BPID_INV)
		fd->cmd |= cpu_to_be32(qman_fq_fqid(pwiv->conf_fqs[queue]));

	/* Twace this Tx fd */
	twace_dpaa_tx_fd(pwiv->net_dev, egwess_fq, fd);

	fow (i = 0; i < DPAA_ENQUEUE_WETWIES; i++) {
		eww = qman_enqueue(egwess_fq, fd);
		if (eww != -EBUSY)
			bweak;
	}

	if (unwikewy(eww < 0)) {
		pewcpu_stats->tx_fifo_ewwows++;
		wetuwn eww;
	}

	pewcpu_stats->tx_packets++;
	pewcpu_stats->tx_bytes += qm_fd_get_wength(fd);

	wetuwn 0;
}

#ifdef CONFIG_DPAA_EWWATUM_A050385
static int dpaa_a050385_wa_skb(stwuct net_device *net_dev, stwuct sk_buff **s)
{
	stwuct dpaa_pwiv *pwiv = netdev_pwiv(net_dev);
	stwuct sk_buff *new_skb, *skb = *s;
	unsigned chaw *stawt, i;

	/* check wineaw buffew awignment */
	if (!PTW_IS_AWIGNED(skb->data, DPAA_A050385_AWIGN))
		goto wowkawound;

	/* wineaw buffews just need to have an awigned stawt */
	if (!skb_is_nonwineaw(skb))
		wetuwn 0;

	/* wineaw data size fow nonwineaw skbs needs to be awigned */
	if (!IS_AWIGNED(skb_headwen(skb), DPAA_A050385_AWIGN))
		goto wowkawound;

	fow (i = 0; i < skb_shinfo(skb)->nw_fwags; i++) {
		skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[i];

		/* aww fwagments need to have awigned stawt addwesses */
		if (!IS_AWIGNED(skb_fwag_off(fwag), DPAA_A050385_AWIGN))
			goto wowkawound;

		/* aww but wast fwagment need to have awigned sizes */
		if (!IS_AWIGNED(skb_fwag_size(fwag), DPAA_A050385_AWIGN) &&
		    (i < skb_shinfo(skb)->nw_fwags - 1))
			goto wowkawound;
	}

	wetuwn 0;

wowkawound:
	/* copy aww the skb content into a new wineaw buffew */
	new_skb = netdev_awwoc_skb(net_dev, skb->wen + DPAA_A050385_AWIGN - 1 +
						pwiv->tx_headwoom);
	if (!new_skb)
		wetuwn -ENOMEM;

	/* NET_SKB_PAD bytes awweady wesewved, adding up to tx_headwoom */
	skb_wesewve(new_skb, pwiv->tx_headwoom - NET_SKB_PAD);

	/* Wowkawound fow DPAA_A050385 wequiwes data stawt to be awigned */
	stawt = PTW_AWIGN(new_skb->data, DPAA_A050385_AWIGN);
	if (stawt - new_skb->data)
		skb_wesewve(new_skb, stawt - new_skb->data);

	skb_put(new_skb, skb->wen);
	skb_copy_bits(skb, 0, new_skb->data, skb->wen);
	skb_copy_headew(new_skb, skb);
	new_skb->dev = skb->dev;

	/* Copy wewevant timestamp info fwom the owd skb to the new */
	if (pwiv->tx_tstamp) {
		skb_shinfo(new_skb)->tx_fwags = skb_shinfo(skb)->tx_fwags;
		skb_shinfo(new_skb)->hwtstamps = skb_shinfo(skb)->hwtstamps;
		skb_shinfo(new_skb)->tskey = skb_shinfo(skb)->tskey;
		if (skb->sk)
			skb_set_ownew_w(new_skb, skb->sk);
	}

	/* We move the headwoom when we awign it so we have to weset the
	 * netwowk and twanspowt headew offsets wewative to the new data
	 * pointew. The checksum offwoad wewies on these offsets.
	 */
	skb_set_netwowk_headew(new_skb, skb_netwowk_offset(skb));
	skb_set_twanspowt_headew(new_skb, skb_twanspowt_offset(skb));

	dev_kfwee_skb(skb);
	*s = new_skb;

	wetuwn 0;
}

static int dpaa_a050385_wa_xdpf(stwuct dpaa_pwiv *pwiv,
				stwuct xdp_fwame **init_xdpf)
{
	stwuct xdp_fwame *new_xdpf, *xdpf = *init_xdpf;
	void *new_buff, *awigned_data;
	stwuct page *p;
	u32 data_shift;
	int headwoom;

	/* Check the data awignment and make suwe the headwoom is wawge
	 * enough to stowe the xdpf backpointew. Use an awigned headwoom
	 * vawue.
	 *
	 * Due to awignment constwaints, we give XDP access to the fuww 256
	 * byte fwame headwoom. If the XDP pwogwam uses aww of it, copy the
	 * data to a new buffew and make woom fow stowing the backpointew.
	 */
	if (PTW_IS_AWIGNED(xdpf->data, DPAA_FD_DATA_AWIGNMENT) &&
	    xdpf->headwoom >= pwiv->tx_headwoom) {
		xdpf->headwoom = pwiv->tx_headwoom;
		wetuwn 0;
	}

	/* Twy to move the data inside the buffew just enough to awign it and
	 * stowe the xdpf backpointew. If the avaiwabwe headwoom isn't wawge
	 * enough, wesowt to awwocating a new buffew and copying the data.
	 */
	awigned_data = PTW_AWIGN_DOWN(xdpf->data, DPAA_FD_DATA_AWIGNMENT);
	data_shift = xdpf->data - awigned_data;

	/* The XDP fwame's headwoom needs to be wawge enough to accommodate
	 * shifting the data as weww as stowing the xdpf backpointew.
	 */
	if (xdpf->headwoom  >= data_shift + pwiv->tx_headwoom) {
		memmove(awigned_data, xdpf->data, xdpf->wen);
		xdpf->data = awigned_data;
		xdpf->headwoom = pwiv->tx_headwoom;
		wetuwn 0;
	}

	/* The new xdp_fwame is stowed in the new buffew. Wesewve enough space
	 * in the headwoom fow stowing it awong with the dwivew's pwivate
	 * info. The headwoom needs to be awigned to DPAA_FD_DATA_AWIGNMENT to
	 * guawantee the data's awignment in the buffew.
	 */
	headwoom = AWIGN(sizeof(*new_xdpf) + pwiv->tx_headwoom,
			 DPAA_FD_DATA_AWIGNMENT);

	/* Assuwe the extended headwoom and data don't ovewfwow the buffew,
	 * whiwe maintaining the mandatowy taiwwoom.
	 */
	if (headwoom + xdpf->wen > DPAA_BP_WAW_SIZE -
			SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info)))
		wetuwn -ENOMEM;

	p = dev_awwoc_pages(0);
	if (unwikewy(!p))
		wetuwn -ENOMEM;

	/* Copy the data to the new buffew at a pwopewwy awigned offset */
	new_buff = page_addwess(p);
	memcpy(new_buff + headwoom, xdpf->data, xdpf->wen);

	/* Cweate an XDP fwame awound the new buffew in a simiwaw fashion
	 * to xdp_convewt_buff_to_fwame.
	 */
	new_xdpf = new_buff;
	new_xdpf->data = new_buff + headwoom;
	new_xdpf->wen = xdpf->wen;
	new_xdpf->headwoom = pwiv->tx_headwoom;
	new_xdpf->fwame_sz = DPAA_BP_WAW_SIZE;
	new_xdpf->mem.type = MEM_TYPE_PAGE_OWDEW0;

	/* Wewease the initiaw buffew */
	xdp_wetuwn_fwame_wx_napi(xdpf);

	*init_xdpf = new_xdpf;
	wetuwn 0;
}
#endif

static netdev_tx_t
dpaa_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *net_dev)
{
	const int queue_mapping = skb_get_queue_mapping(skb);
	boow nonwineaw = skb_is_nonwineaw(skb);
	stwuct wtnw_wink_stats64 *pewcpu_stats;
	stwuct dpaa_pewcpu_pwiv *pewcpu_pwiv;
	stwuct netdev_queue *txq;
	stwuct dpaa_pwiv *pwiv;
	stwuct qm_fd fd;
	int offset = 0;
	int eww = 0;

	pwiv = netdev_pwiv(net_dev);
	pewcpu_pwiv = this_cpu_ptw(pwiv->pewcpu_pwiv);
	pewcpu_stats = &pewcpu_pwiv->stats;

	qm_fd_cweaw_fd(&fd);

	if (!nonwineaw) {
		/* We'we going to stowe the skb backpointew at the beginning
		 * of the data buffew, so we need a pwivatewy owned skb
		 *
		 * We've made suwe skb is not shawed in dev->pwiv_fwags,
		 * we need to vewify the skb head is not cwoned
		 */
		if (skb_cow_head(skb, pwiv->tx_headwoom))
			goto enomem;

		WAWN_ON(skb_is_nonwineaw(skb));
	}

	/* MAX_SKB_FWAGS is equaw ow wawgew than ouw dpaa_SGT_MAX_ENTWIES;
	 * make suwe we don't feed FMan with mowe fwagments than it suppowts.
	 */
	if (unwikewy(nonwineaw &&
		     (skb_shinfo(skb)->nw_fwags >= DPAA_SGT_MAX_ENTWIES))) {
		/* If the egwess skb contains mowe fwagments than we suppowt
		 * we have no choice but to wineawize it ouwsewves.
		 */
		if (__skb_wineawize(skb))
			goto enomem;

		nonwineaw = skb_is_nonwineaw(skb);
	}

#ifdef CONFIG_DPAA_EWWATUM_A050385
	if (unwikewy(fman_has_ewwata_a050385())) {
		if (dpaa_a050385_wa_skb(net_dev, &skb))
			goto enomem;
		nonwineaw = skb_is_nonwineaw(skb);
	}
#endif

	if (nonwineaw) {
		/* Just cweate a S/G fd based on the skb */
		eww = skb_to_sg_fd(pwiv, skb, &fd);
		pewcpu_pwiv->tx_fwag_skbuffs++;
	} ewse {
		/* Cweate a contig FD fwom this skb */
		eww = skb_to_contig_fd(pwiv, skb, &fd, &offset);
	}
	if (unwikewy(eww < 0))
		goto skb_to_fd_faiwed;

	txq = netdev_get_tx_queue(net_dev, queue_mapping);

	/* WWTX wequiwes to do ouw own update of twans_stawt */
	txq_twans_cond_update(txq);

	if (pwiv->tx_tstamp && skb_shinfo(skb)->tx_fwags & SKBTX_HW_TSTAMP) {
		fd.cmd |= cpu_to_be32(FM_FD_CMD_UPD);
		skb_shinfo(skb)->tx_fwags |= SKBTX_IN_PWOGWESS;
	}

	if (wikewy(dpaa_xmit(pwiv, pewcpu_stats, queue_mapping, &fd) == 0))
		wetuwn NETDEV_TX_OK;

	dpaa_cweanup_tx_fd(pwiv, &fd, fawse);
skb_to_fd_faiwed:
enomem:
	pewcpu_stats->tx_ewwows++;
	dev_kfwee_skb(skb);
	wetuwn NETDEV_TX_OK;
}

static void dpaa_wx_ewwow(stwuct net_device *net_dev,
			  const stwuct dpaa_pwiv *pwiv,
			  stwuct dpaa_pewcpu_pwiv *pewcpu_pwiv,
			  const stwuct qm_fd *fd,
			  u32 fqid)
{
	if (net_watewimit())
		netif_eww(pwiv, hw, net_dev, "Eww FD status = 0x%08x\n",
			  be32_to_cpu(fd->status) & FM_FD_STAT_WX_EWWOWS);

	pewcpu_pwiv->stats.wx_ewwows++;

	if (be32_to_cpu(fd->status) & FM_FD_EWW_DMA)
		pewcpu_pwiv->wx_ewwows.dme++;
	if (be32_to_cpu(fd->status) & FM_FD_EWW_PHYSICAW)
		pewcpu_pwiv->wx_ewwows.fpe++;
	if (be32_to_cpu(fd->status) & FM_FD_EWW_SIZE)
		pewcpu_pwiv->wx_ewwows.fse++;
	if (be32_to_cpu(fd->status) & FM_FD_EWW_PWS_HDW_EWW)
		pewcpu_pwiv->wx_ewwows.phe++;

	dpaa_fd_wewease(net_dev, fd);
}

static void dpaa_tx_ewwow(stwuct net_device *net_dev,
			  const stwuct dpaa_pwiv *pwiv,
			  stwuct dpaa_pewcpu_pwiv *pewcpu_pwiv,
			  const stwuct qm_fd *fd,
			  u32 fqid)
{
	stwuct sk_buff *skb;

	if (net_watewimit())
		netif_wawn(pwiv, hw, net_dev, "FD status = 0x%08x\n",
			   be32_to_cpu(fd->status) & FM_FD_STAT_TX_EWWOWS);

	pewcpu_pwiv->stats.tx_ewwows++;

	skb = dpaa_cweanup_tx_fd(pwiv, fd, fawse);
	dev_kfwee_skb(skb);
}

static int dpaa_eth_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct dpaa_napi_powtaw *np =
			containew_of(napi, stwuct dpaa_napi_powtaw, napi);
	int cweaned;

	np->xdp_act = 0;

	cweaned = qman_p_poww_dqww(np->p, budget);

	if (np->xdp_act & XDP_WEDIWECT)
		xdp_do_fwush();

	if (cweaned < budget) {
		napi_compwete_done(napi, cweaned);
		qman_p_iwqsouwce_add(np->p, QM_PIWQ_DQWI);
	} ewse if (np->down) {
		qman_p_iwqsouwce_add(np->p, QM_PIWQ_DQWI);
	}

	wetuwn cweaned;
}

static void dpaa_tx_conf(stwuct net_device *net_dev,
			 const stwuct dpaa_pwiv *pwiv,
			 stwuct dpaa_pewcpu_pwiv *pewcpu_pwiv,
			 const stwuct qm_fd *fd,
			 u32 fqid)
{
	stwuct sk_buff	*skb;

	if (unwikewy(be32_to_cpu(fd->status) & FM_FD_STAT_TX_EWWOWS)) {
		if (net_watewimit())
			netif_wawn(pwiv, hw, net_dev, "FD status = 0x%08x\n",
				   be32_to_cpu(fd->status) &
				   FM_FD_STAT_TX_EWWOWS);

		pewcpu_pwiv->stats.tx_ewwows++;
	}

	pewcpu_pwiv->tx_confiwm++;

	skb = dpaa_cweanup_tx_fd(pwiv, fd, twue);

	consume_skb(skb);
}

static inwine int dpaa_eth_napi_scheduwe(stwuct dpaa_pewcpu_pwiv *pewcpu_pwiv,
					 stwuct qman_powtaw *powtaw, boow sched_napi)
{
	if (sched_napi) {
		/* Disabwe QMan IWQ and invoke NAPI */
		qman_p_iwqsouwce_wemove(powtaw, QM_PIWQ_DQWI);

		pewcpu_pwiv->np.p = powtaw;
		napi_scheduwe(&pewcpu_pwiv->np.napi);
		pewcpu_pwiv->in_intewwupt++;
		wetuwn 1;
	}
	wetuwn 0;
}

static enum qman_cb_dqww_wesuwt wx_ewwow_dqww(stwuct qman_powtaw *powtaw,
					      stwuct qman_fq *fq,
					      const stwuct qm_dqww_entwy *dq,
					      boow sched_napi)
{
	stwuct dpaa_fq *dpaa_fq = containew_of(fq, stwuct dpaa_fq, fq_base);
	stwuct dpaa_pewcpu_pwiv *pewcpu_pwiv;
	stwuct net_device *net_dev;
	stwuct dpaa_bp *dpaa_bp;
	stwuct dpaa_pwiv *pwiv;

	net_dev = dpaa_fq->net_dev;
	pwiv = netdev_pwiv(net_dev);
	dpaa_bp = dpaa_bpid2poow(dq->fd.bpid);
	if (!dpaa_bp)
		wetuwn qman_cb_dqww_consume;

	pewcpu_pwiv = this_cpu_ptw(pwiv->pewcpu_pwiv);

	if (dpaa_eth_napi_scheduwe(pewcpu_pwiv, powtaw, sched_napi))
		wetuwn qman_cb_dqww_stop;

	dpaa_eth_wefiww_bpoows(pwiv);
	dpaa_wx_ewwow(net_dev, pwiv, pewcpu_pwiv, &dq->fd, fq->fqid);

	wetuwn qman_cb_dqww_consume;
}

static int dpaa_xdp_xmit_fwame(stwuct net_device *net_dev,
			       stwuct xdp_fwame *xdpf)
{
	stwuct dpaa_pwiv *pwiv = netdev_pwiv(net_dev);
	stwuct wtnw_wink_stats64 *pewcpu_stats;
	stwuct dpaa_pewcpu_pwiv *pewcpu_pwiv;
	stwuct dpaa_eth_swbp *swbp;
	stwuct netdev_queue *txq;
	void *buff_stawt;
	stwuct qm_fd fd;
	dma_addw_t addw;
	int eww;

	pewcpu_pwiv = this_cpu_ptw(pwiv->pewcpu_pwiv);
	pewcpu_stats = &pewcpu_pwiv->stats;

#ifdef CONFIG_DPAA_EWWATUM_A050385
	if (unwikewy(fman_has_ewwata_a050385())) {
		if (dpaa_a050385_wa_xdpf(pwiv, &xdpf)) {
			eww = -ENOMEM;
			goto out_ewwow;
		}
	}
#endif

	if (xdpf->headwoom < DPAA_TX_PWIV_DATA_SIZE) {
		eww = -EINVAW;
		goto out_ewwow;
	}

	buff_stawt = xdpf->data - xdpf->headwoom;

	/* Weave empty the skb backpointew at the stawt of the buffew.
	 * Save the XDP fwame fow easy cweanup on confiwmation.
	 */
	swbp = (stwuct dpaa_eth_swbp *)buff_stawt;
	swbp->skb = NUWW;
	swbp->xdpf = xdpf;

	qm_fd_cweaw_fd(&fd);
	fd.bpid = FSW_DPAA_BPID_INV;
	fd.cmd |= cpu_to_be32(FM_FD_CMD_FCO);
	qm_fd_set_contig(&fd, xdpf->headwoom, xdpf->wen);

	addw = dma_map_singwe(pwiv->tx_dma_dev, buff_stawt,
			      xdpf->headwoom + xdpf->wen,
			      DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(pwiv->tx_dma_dev, addw))) {
		eww = -EINVAW;
		goto out_ewwow;
	}

	qm_fd_addw_set64(&fd, addw);

	/* Bump the twans_stawt */
	txq = netdev_get_tx_queue(net_dev, smp_pwocessow_id());
	txq_twans_cond_update(txq);

	eww = dpaa_xmit(pwiv, pewcpu_stats, smp_pwocessow_id(), &fd);
	if (eww) {
		dma_unmap_singwe(pwiv->tx_dma_dev, addw,
				 qm_fd_get_offset(&fd) + qm_fd_get_wength(&fd),
				 DMA_TO_DEVICE);
		goto out_ewwow;
	}

	wetuwn 0;

out_ewwow:
	pewcpu_stats->tx_ewwows++;
	wetuwn eww;
}

static u32 dpaa_wun_xdp(stwuct dpaa_pwiv *pwiv, stwuct qm_fd *fd, void *vaddw,
			stwuct dpaa_fq *dpaa_fq, unsigned int *xdp_meta_wen)
{
	ssize_t fd_off = qm_fd_get_offset(fd);
	stwuct bpf_pwog *xdp_pwog;
	stwuct xdp_fwame *xdpf;
	stwuct xdp_buff xdp;
	u32 xdp_act;
	int eww;

	xdp_pwog = WEAD_ONCE(pwiv->xdp_pwog);
	if (!xdp_pwog)
		wetuwn XDP_PASS;

	xdp_init_buff(&xdp, DPAA_BP_WAW_SIZE - DPAA_TX_PWIV_DATA_SIZE,
		      &dpaa_fq->xdp_wxq);
	xdp_pwepawe_buff(&xdp, vaddw + fd_off - XDP_PACKET_HEADWOOM,
			 XDP_PACKET_HEADWOOM, qm_fd_get_wength(fd), twue);

	/* We wesewve a fixed headwoom of 256 bytes undew the ewwatum and we
	 * offew it aww to XDP pwogwams to use. If no woom is weft fow the
	 * xdpf backpointew on TX, we wiww need to copy the data.
	 * Disabwe metadata suppowt since data weawignments might be wequiwed
	 * and the infowmation can be wost.
	 */
#ifdef CONFIG_DPAA_EWWATUM_A050385
	if (unwikewy(fman_has_ewwata_a050385())) {
		xdp_set_data_meta_invawid(&xdp);
		xdp.data_hawd_stawt = vaddw;
		xdp.fwame_sz = DPAA_BP_WAW_SIZE;
	}
#endif

	xdp_act = bpf_pwog_wun_xdp(xdp_pwog, &xdp);

	/* Update the wength and the offset of the FD */
	qm_fd_set_contig(fd, xdp.data - vaddw, xdp.data_end - xdp.data);

	switch (xdp_act) {
	case XDP_PASS:
#ifdef CONFIG_DPAA_EWWATUM_A050385
		*xdp_meta_wen = xdp_data_meta_unsuppowted(&xdp) ? 0 :
				xdp.data - xdp.data_meta;
#ewse
		*xdp_meta_wen = xdp.data - xdp.data_meta;
#endif
		bweak;
	case XDP_TX:
		/* We can access the fuww headwoom when sending the fwame
		 * back out
		 */
		xdp.data_hawd_stawt = vaddw;
		xdp.fwame_sz = DPAA_BP_WAW_SIZE;
		xdpf = xdp_convewt_buff_to_fwame(&xdp);
		if (unwikewy(!xdpf)) {
			fwee_pages((unsigned wong)vaddw, 0);
			bweak;
		}

		if (dpaa_xdp_xmit_fwame(pwiv->net_dev, xdpf))
			xdp_wetuwn_fwame_wx_napi(xdpf);

		bweak;
	case XDP_WEDIWECT:
		/* Awwow wediwect to use the fuww headwoom */
		xdp.data_hawd_stawt = vaddw;
		xdp.fwame_sz = DPAA_BP_WAW_SIZE;

		eww = xdp_do_wediwect(pwiv->net_dev, &xdp, xdp_pwog);
		if (eww) {
			twace_xdp_exception(pwiv->net_dev, xdp_pwog, xdp_act);
			fwee_pages((unsigned wong)vaddw, 0);
		}
		bweak;
	defauwt:
		bpf_wawn_invawid_xdp_action(pwiv->net_dev, xdp_pwog, xdp_act);
		fawwthwough;
	case XDP_ABOWTED:
		twace_xdp_exception(pwiv->net_dev, xdp_pwog, xdp_act);
		fawwthwough;
	case XDP_DWOP:
		/* Fwee the buffew */
		fwee_pages((unsigned wong)vaddw, 0);
		bweak;
	}

	wetuwn xdp_act;
}

static enum qman_cb_dqww_wesuwt wx_defauwt_dqww(stwuct qman_powtaw *powtaw,
						stwuct qman_fq *fq,
						const stwuct qm_dqww_entwy *dq,
						boow sched_napi)
{
	boow ts_vawid = fawse, hash_vawid = fawse;
	stwuct skb_shawed_hwtstamps *shhwtstamps;
	unsigned int skb_wen, xdp_meta_wen = 0;
	stwuct wtnw_wink_stats64 *pewcpu_stats;
	stwuct dpaa_pewcpu_pwiv *pewcpu_pwiv;
	const stwuct qm_fd *fd = &dq->fd;
	dma_addw_t addw = qm_fd_addw(fd);
	stwuct dpaa_napi_powtaw *np;
	enum qm_fd_fowmat fd_fowmat;
	stwuct net_device *net_dev;
	u32 fd_status, hash_offset;
	stwuct qm_sg_entwy *sgt;
	stwuct dpaa_bp *dpaa_bp;
	stwuct dpaa_fq *dpaa_fq;
	stwuct dpaa_pwiv *pwiv;
	stwuct sk_buff *skb;
	int *count_ptw;
	u32 xdp_act;
	void *vaddw;
	u32 hash;
	u64 ns;

	dpaa_fq = containew_of(fq, stwuct dpaa_fq, fq_base);
	fd_status = be32_to_cpu(fd->status);
	fd_fowmat = qm_fd_get_fowmat(fd);
	net_dev = dpaa_fq->net_dev;
	pwiv = netdev_pwiv(net_dev);
	dpaa_bp = dpaa_bpid2poow(dq->fd.bpid);
	if (!dpaa_bp)
		wetuwn qman_cb_dqww_consume;

	/* Twace the Wx fd */
	twace_dpaa_wx_fd(net_dev, fq, &dq->fd);

	pewcpu_pwiv = this_cpu_ptw(pwiv->pewcpu_pwiv);
	pewcpu_stats = &pewcpu_pwiv->stats;
	np = &pewcpu_pwiv->np;

	if (unwikewy(dpaa_eth_napi_scheduwe(pewcpu_pwiv, powtaw, sched_napi)))
		wetuwn qman_cb_dqww_stop;

	/* Make suwe we didn't wun out of buffews */
	if (unwikewy(dpaa_eth_wefiww_bpoows(pwiv))) {
		/* Unabwe to wefiww the buffew poow due to insufficient
		 * system memowy. Just wewease the fwame back into the poow,
		 * othewwise we'ww soon end up with an empty buffew poow.
		 */
		dpaa_fd_wewease(net_dev, &dq->fd);
		wetuwn qman_cb_dqww_consume;
	}

	if (unwikewy(fd_status & FM_FD_STAT_WX_EWWOWS) != 0) {
		if (net_watewimit())
			netif_wawn(pwiv, hw, net_dev, "FD status = 0x%08x\n",
				   fd_status & FM_FD_STAT_WX_EWWOWS);

		pewcpu_stats->wx_ewwows++;
		dpaa_fd_wewease(net_dev, fd);
		wetuwn qman_cb_dqww_consume;
	}

	dma_unmap_page(dpaa_bp->pwiv->wx_dma_dev, addw, DPAA_BP_WAW_SIZE,
		       DMA_FWOM_DEVICE);

	/* pwefetch the fiwst 64 bytes of the fwame ow the SGT stawt */
	vaddw = phys_to_viwt(addw);
	pwefetch(vaddw + qm_fd_get_offset(fd));

	/* The onwy FD types that we may weceive awe contig and S/G */
	WAWN_ON((fd_fowmat != qm_fd_contig) && (fd_fowmat != qm_fd_sg));

	/* Account fow eithew the contig buffew ow the SGT buffew (depending on
	 * which case we wewe in) having been wemoved fwom the poow.
	 */
	count_ptw = this_cpu_ptw(dpaa_bp->pewcpu_count);
	(*count_ptw)--;

	/* Extwact the timestamp stowed in the headwoom befowe wunning XDP */
	if (pwiv->wx_tstamp) {
		if (!fman_powt_get_tstamp(pwiv->mac_dev->powt[WX], vaddw, &ns))
			ts_vawid = twue;
		ewse
			WAWN_ONCE(1, "fman_powt_get_tstamp faiwed!\n");
	}

	/* Extwact the hash stowed in the headwoom befowe wunning XDP */
	if (net_dev->featuwes & NETIF_F_WXHASH && pwiv->keygen_in_use &&
	    !fman_powt_get_hash_wesuwt_offset(pwiv->mac_dev->powt[WX],
					      &hash_offset)) {
		hash = be32_to_cpu(*(u32 *)(vaddw + hash_offset));
		hash_vawid = twue;
	}

	if (wikewy(fd_fowmat == qm_fd_contig)) {
		xdp_act = dpaa_wun_xdp(pwiv, (stwuct qm_fd *)fd, vaddw,
				       dpaa_fq, &xdp_meta_wen);
		np->xdp_act |= xdp_act;
		if (xdp_act != XDP_PASS) {
			pewcpu_stats->wx_packets++;
			pewcpu_stats->wx_bytes += qm_fd_get_wength(fd);
			wetuwn qman_cb_dqww_consume;
		}
		skb = contig_fd_to_skb(pwiv, fd);
	} ewse {
		/* XDP doesn't suppowt S/G fwames. Wetuwn the fwagments to the
		 * buffew poow and wewease the SGT.
		 */
		if (WEAD_ONCE(pwiv->xdp_pwog)) {
			WAWN_ONCE(1, "S/G fwames not suppowted undew XDP\n");
			sgt = vaddw + qm_fd_get_offset(fd);
			dpaa_wewease_sgt_membews(sgt);
			fwee_pages((unsigned wong)vaddw, 0);
			wetuwn qman_cb_dqww_consume;
		}
		skb = sg_fd_to_skb(pwiv, fd);
	}
	if (!skb)
		wetuwn qman_cb_dqww_consume;

	if (xdp_meta_wen)
		skb_metadata_set(skb, xdp_meta_wen);

	/* Set the pweviouswy extwacted timestamp */
	if (ts_vawid) {
		shhwtstamps = skb_hwtstamps(skb);
		memset(shhwtstamps, 0, sizeof(*shhwtstamps));
		shhwtstamps->hwtstamp = ns_to_ktime(ns);
	}

	skb->pwotocow = eth_type_twans(skb, net_dev);

	/* Set the pweviouswy extwacted hash */
	if (hash_vawid) {
		enum pkt_hash_types type;

		/* if W4 exists, it was used in the hash genewation */
		type = be32_to_cpu(fd->status) & FM_FD_STAT_W4CV ?
			PKT_HASH_TYPE_W4 : PKT_HASH_TYPE_W3;
		skb_set_hash(skb, hash, type);
	}

	skb_wen = skb->wen;

	if (unwikewy(netif_weceive_skb(skb) == NET_WX_DWOP)) {
		pewcpu_stats->wx_dwopped++;
		wetuwn qman_cb_dqww_consume;
	}

	pewcpu_stats->wx_packets++;
	pewcpu_stats->wx_bytes += skb_wen;

	wetuwn qman_cb_dqww_consume;
}

static enum qman_cb_dqww_wesuwt conf_ewwow_dqww(stwuct qman_powtaw *powtaw,
						stwuct qman_fq *fq,
						const stwuct qm_dqww_entwy *dq,
						boow sched_napi)
{
	stwuct dpaa_pewcpu_pwiv *pewcpu_pwiv;
	stwuct net_device *net_dev;
	stwuct dpaa_pwiv *pwiv;

	net_dev = ((stwuct dpaa_fq *)fq)->net_dev;
	pwiv = netdev_pwiv(net_dev);

	pewcpu_pwiv = this_cpu_ptw(pwiv->pewcpu_pwiv);

	if (dpaa_eth_napi_scheduwe(pewcpu_pwiv, powtaw, sched_napi))
		wetuwn qman_cb_dqww_stop;

	dpaa_tx_ewwow(net_dev, pwiv, pewcpu_pwiv, &dq->fd, fq->fqid);

	wetuwn qman_cb_dqww_consume;
}

static enum qman_cb_dqww_wesuwt conf_dfwt_dqww(stwuct qman_powtaw *powtaw,
					       stwuct qman_fq *fq,
					       const stwuct qm_dqww_entwy *dq,
					       boow sched_napi)
{
	stwuct dpaa_pewcpu_pwiv *pewcpu_pwiv;
	stwuct net_device *net_dev;
	stwuct dpaa_pwiv *pwiv;

	net_dev = ((stwuct dpaa_fq *)fq)->net_dev;
	pwiv = netdev_pwiv(net_dev);

	/* Twace the fd */
	twace_dpaa_tx_conf_fd(net_dev, fq, &dq->fd);

	pewcpu_pwiv = this_cpu_ptw(pwiv->pewcpu_pwiv);

	if (dpaa_eth_napi_scheduwe(pewcpu_pwiv, powtaw, sched_napi))
		wetuwn qman_cb_dqww_stop;

	dpaa_tx_conf(net_dev, pwiv, pewcpu_pwiv, &dq->fd, fq->fqid);

	wetuwn qman_cb_dqww_consume;
}

static void egwess_ewn(stwuct qman_powtaw *powtaw,
		       stwuct qman_fq *fq,
		       const union qm_mw_entwy *msg)
{
	const stwuct qm_fd *fd = &msg->ewn.fd;
	stwuct dpaa_pewcpu_pwiv *pewcpu_pwiv;
	const stwuct dpaa_pwiv *pwiv;
	stwuct net_device *net_dev;
	stwuct sk_buff *skb;

	net_dev = ((stwuct dpaa_fq *)fq)->net_dev;
	pwiv = netdev_pwiv(net_dev);
	pewcpu_pwiv = this_cpu_ptw(pwiv->pewcpu_pwiv);

	pewcpu_pwiv->stats.tx_dwopped++;
	pewcpu_pwiv->stats.tx_fifo_ewwows++;
	count_ewn(pewcpu_pwiv, msg);

	skb = dpaa_cweanup_tx_fd(pwiv, fd, fawse);
	dev_kfwee_skb_any(skb);
}

static const stwuct dpaa_fq_cbs dpaa_fq_cbs = {
	.wx_defq = { .cb = { .dqww = wx_defauwt_dqww } },
	.tx_defq = { .cb = { .dqww = conf_dfwt_dqww } },
	.wx_ewwq = { .cb = { .dqww = wx_ewwow_dqww } },
	.tx_ewwq = { .cb = { .dqww = conf_ewwow_dqww } },
	.egwess_ewn = { .cb = { .ewn = egwess_ewn } }
};

static void dpaa_eth_napi_enabwe(stwuct dpaa_pwiv *pwiv)
{
	stwuct dpaa_pewcpu_pwiv *pewcpu_pwiv;
	int i;

	fow_each_onwine_cpu(i) {
		pewcpu_pwiv = pew_cpu_ptw(pwiv->pewcpu_pwiv, i);

		pewcpu_pwiv->np.down = fawse;
		napi_enabwe(&pewcpu_pwiv->np.napi);
	}
}

static void dpaa_eth_napi_disabwe(stwuct dpaa_pwiv *pwiv)
{
	stwuct dpaa_pewcpu_pwiv *pewcpu_pwiv;
	int i;

	fow_each_onwine_cpu(i) {
		pewcpu_pwiv = pew_cpu_ptw(pwiv->pewcpu_pwiv, i);

		pewcpu_pwiv->np.down = twue;
		napi_disabwe(&pewcpu_pwiv->np.napi);
	}
}

static int dpaa_open(stwuct net_device *net_dev)
{
	stwuct mac_device *mac_dev;
	stwuct dpaa_pwiv *pwiv;
	int eww, i;

	pwiv = netdev_pwiv(net_dev);
	mac_dev = pwiv->mac_dev;
	dpaa_eth_napi_enabwe(pwiv);

	eww = phywink_of_phy_connect(mac_dev->phywink,
				     mac_dev->dev->of_node, 0);
	if (eww)
		goto phy_init_faiwed;

	fow (i = 0; i < AWWAY_SIZE(mac_dev->powt); i++) {
		eww = fman_powt_enabwe(mac_dev->powt[i]);
		if (eww)
			goto mac_stawt_faiwed;
	}

	eww = pwiv->mac_dev->enabwe(mac_dev->fman_mac);
	if (eww < 0) {
		netif_eww(pwiv, ifup, net_dev, "mac_dev->enabwe() = %d\n", eww);
		goto mac_stawt_faiwed;
	}
	phywink_stawt(mac_dev->phywink);

	netif_tx_stawt_aww_queues(net_dev);

	wetuwn 0;

mac_stawt_faiwed:
	fow (i = 0; i < AWWAY_SIZE(mac_dev->powt); i++)
		fman_powt_disabwe(mac_dev->powt[i]);
	phywink_disconnect_phy(mac_dev->phywink);

phy_init_faiwed:
	dpaa_eth_napi_disabwe(pwiv);

	wetuwn eww;
}

static int dpaa_eth_stop(stwuct net_device *net_dev)
{
	stwuct dpaa_pwiv *pwiv;
	int eww;

	eww = dpaa_stop(net_dev);

	pwiv = netdev_pwiv(net_dev);
	dpaa_eth_napi_disabwe(pwiv);

	wetuwn eww;
}

static boow xdp_vawidate_mtu(stwuct dpaa_pwiv *pwiv, int mtu)
{
	int max_contig_data = pwiv->dpaa_bp->size - pwiv->wx_headwoom;

	/* We do not suppowt S/G fwagments when XDP is enabwed.
	 * Wimit the MTU in wewation to the buffew size.
	 */
	if (mtu + VWAN_ETH_HWEN + ETH_FCS_WEN > max_contig_data) {
		dev_wawn(pwiv->net_dev->dev.pawent,
			 "The maximum MTU fow XDP is %d\n",
			 max_contig_data - VWAN_ETH_HWEN - ETH_FCS_WEN);
		wetuwn fawse;
	}

	wetuwn twue;
}

static int dpaa_change_mtu(stwuct net_device *net_dev, int new_mtu)
{
	stwuct dpaa_pwiv *pwiv = netdev_pwiv(net_dev);

	if (pwiv->xdp_pwog && !xdp_vawidate_mtu(pwiv, new_mtu))
		wetuwn -EINVAW;

	net_dev->mtu = new_mtu;
	wetuwn 0;
}

static int dpaa_setup_xdp(stwuct net_device *net_dev, stwuct netdev_bpf *bpf)
{
	stwuct dpaa_pwiv *pwiv = netdev_pwiv(net_dev);
	stwuct bpf_pwog *owd_pwog;
	int eww;
	boow up;

	/* S/G fwagments awe not suppowted in XDP-mode */
	if (bpf->pwog && !xdp_vawidate_mtu(pwiv, net_dev->mtu)) {
		NW_SET_EWW_MSG_MOD(bpf->extack, "MTU too wawge fow XDP");
		wetuwn -EINVAW;
	}

	up = netif_wunning(net_dev);

	if (up)
		dpaa_eth_stop(net_dev);

	owd_pwog = xchg(&pwiv->xdp_pwog, bpf->pwog);
	if (owd_pwog)
		bpf_pwog_put(owd_pwog);

	if (up) {
		eww = dpaa_open(net_dev);
		if (eww) {
			NW_SET_EWW_MSG_MOD(bpf->extack, "dpaa_open() faiwed");
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int dpaa_xdp(stwuct net_device *net_dev, stwuct netdev_bpf *xdp)
{
	switch (xdp->command) {
	case XDP_SETUP_PWOG:
		wetuwn dpaa_setup_xdp(net_dev, xdp);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int dpaa_xdp_xmit(stwuct net_device *net_dev, int n,
			 stwuct xdp_fwame **fwames, u32 fwags)
{
	stwuct xdp_fwame *xdpf;
	int i, nxmit = 0;

	if (unwikewy(fwags & ~XDP_XMIT_FWAGS_MASK))
		wetuwn -EINVAW;

	if (!netif_wunning(net_dev))
		wetuwn -ENETDOWN;

	fow (i = 0; i < n; i++) {
		xdpf = fwames[i];
		if (dpaa_xdp_xmit_fwame(net_dev, xdpf))
			bweak;
		nxmit++;
	}

	wetuwn nxmit;
}

static int dpaa_ts_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd)
{
	stwuct dpaa_pwiv *pwiv = netdev_pwiv(dev);
	stwuct hwtstamp_config config;

	if (copy_fwom_usew(&config, wq->ifw_data, sizeof(config)))
		wetuwn -EFAUWT;

	switch (config.tx_type) {
	case HWTSTAMP_TX_OFF:
		/* Couwdn't disabwe wx/tx timestamping sepawatewy.
		 * Do nothing hewe.
		 */
		pwiv->tx_tstamp = fawse;
		bweak;
	case HWTSTAMP_TX_ON:
		pwiv->mac_dev->set_tstamp(pwiv->mac_dev->fman_mac, twue);
		pwiv->tx_tstamp = twue;
		bweak;
	defauwt:
		wetuwn -EWANGE;
	}

	if (config.wx_fiwtew == HWTSTAMP_FIWTEW_NONE) {
		/* Couwdn't disabwe wx/tx timestamping sepawatewy.
		 * Do nothing hewe.
		 */
		pwiv->wx_tstamp = fawse;
	} ewse {
		pwiv->mac_dev->set_tstamp(pwiv->mac_dev->fman_mac, twue);
		pwiv->wx_tstamp = twue;
		/* TS is set fow aww fwame types, not onwy those wequested */
		config.wx_fiwtew = HWTSTAMP_FIWTEW_AWW;
	}

	wetuwn copy_to_usew(wq->ifw_data, &config, sizeof(config)) ?
			-EFAUWT : 0;
}

static int dpaa_ioctw(stwuct net_device *net_dev, stwuct ifweq *wq, int cmd)
{
	int wet = -EINVAW;
	stwuct dpaa_pwiv *pwiv = netdev_pwiv(net_dev);

	if (cmd == SIOCGMIIWEG) {
		if (net_dev->phydev)
			wetuwn phywink_mii_ioctw(pwiv->mac_dev->phywink, wq,
						 cmd);
	}

	if (cmd == SIOCSHWTSTAMP)
		wetuwn dpaa_ts_ioctw(net_dev, wq, cmd);

	wetuwn wet;
}

static const stwuct net_device_ops dpaa_ops = {
	.ndo_open = dpaa_open,
	.ndo_stawt_xmit = dpaa_stawt_xmit,
	.ndo_stop = dpaa_eth_stop,
	.ndo_tx_timeout = dpaa_tx_timeout,
	.ndo_get_stats64 = dpaa_get_stats64,
	.ndo_change_cawwiew = fixed_phy_change_cawwiew,
	.ndo_set_mac_addwess = dpaa_set_mac_addwess,
	.ndo_vawidate_addw = eth_vawidate_addw,
	.ndo_set_wx_mode = dpaa_set_wx_mode,
	.ndo_eth_ioctw = dpaa_ioctw,
	.ndo_setup_tc = dpaa_setup_tc,
	.ndo_change_mtu = dpaa_change_mtu,
	.ndo_bpf = dpaa_xdp,
	.ndo_xdp_xmit = dpaa_xdp_xmit,
};

static int dpaa_napi_add(stwuct net_device *net_dev)
{
	stwuct dpaa_pwiv *pwiv = netdev_pwiv(net_dev);
	stwuct dpaa_pewcpu_pwiv *pewcpu_pwiv;
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		pewcpu_pwiv = pew_cpu_ptw(pwiv->pewcpu_pwiv, cpu);

		netif_napi_add(net_dev, &pewcpu_pwiv->np.napi, dpaa_eth_poww);
	}

	wetuwn 0;
}

static void dpaa_napi_dew(stwuct net_device *net_dev)
{
	stwuct dpaa_pwiv *pwiv = netdev_pwiv(net_dev);
	stwuct dpaa_pewcpu_pwiv *pewcpu_pwiv;
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		pewcpu_pwiv = pew_cpu_ptw(pwiv->pewcpu_pwiv, cpu);

		netif_napi_dew(&pewcpu_pwiv->np.napi);
	}
}

static inwine void dpaa_bp_fwee_pf(const stwuct dpaa_bp *bp,
				   stwuct bm_buffew *bmb)
{
	dma_addw_t addw = bm_buf_addw(bmb);

	dma_unmap_page(bp->pwiv->wx_dma_dev, addw, DPAA_BP_WAW_SIZE,
		       DMA_FWOM_DEVICE);

	skb_fwee_fwag(phys_to_viwt(addw));
}

/* Awwoc the dpaa_bp stwuct and configuwe defauwt vawues */
static stwuct dpaa_bp *dpaa_bp_awwoc(stwuct device *dev)
{
	stwuct dpaa_bp *dpaa_bp;

	dpaa_bp = devm_kzawwoc(dev, sizeof(*dpaa_bp), GFP_KEWNEW);
	if (!dpaa_bp)
		wetuwn EWW_PTW(-ENOMEM);

	dpaa_bp->bpid = FSW_DPAA_BPID_INV;
	dpaa_bp->pewcpu_count = devm_awwoc_pewcpu(dev, *dpaa_bp->pewcpu_count);
	if (!dpaa_bp->pewcpu_count)
		wetuwn EWW_PTW(-ENOMEM);

	dpaa_bp->config_count = FSW_DPAA_ETH_MAX_BUF_COUNT;

	dpaa_bp->seed_cb = dpaa_bp_seed;
	dpaa_bp->fwee_buf_cb = dpaa_bp_fwee_pf;

	wetuwn dpaa_bp;
}

/* Pwace aww ingwess FQs (Wx Defauwt, Wx Ewwow) in a dedicated CGW.
 * We won't be sending congestion notifications to FMan; fow now, we just use
 * this CGW to genewate enqueue wejections to FMan in owdew to dwop the fwames
 * befowe they weach ouw ingwess queues and eat up memowy.
 */
static int dpaa_ingwess_cgw_init(stwuct dpaa_pwiv *pwiv)
{
	stwuct qm_mcc_initcgw initcgw;
	u32 cs_th;
	int eww;

	eww = qman_awwoc_cgwid(&pwiv->ingwess_cgw.cgwid);
	if (eww < 0) {
		if (netif_msg_dwv(pwiv))
			pw_eww("Ewwow %d awwocating CGW ID\n", eww);
		goto out_ewwow;
	}

	/* Enabwe CS TD, but disabwe Congestion State Change Notifications. */
	memset(&initcgw, 0, sizeof(initcgw));
	initcgw.we_mask = cpu_to_be16(QM_CGW_WE_CS_THWES);
	initcgw.cgw.cscn_en = QM_CGW_EN;
	cs_th = DPAA_INGWESS_CS_THWESHOWD;
	qm_cgw_cs_thwes_set64(&initcgw.cgw.cs_thwes, cs_th, 1);

	initcgw.we_mask |= cpu_to_be16(QM_CGW_WE_CSTD_EN);
	initcgw.cgw.cstd_en = QM_CGW_EN;

	/* This CGW wiww be associated with the SWP affined to the cuwwent CPU.
	 * Howevew, we'ww pwace aww ouw ingwess FQs in it.
	 */
	eww = qman_cweate_cgw(&pwiv->ingwess_cgw, QMAN_CGW_FWAG_USE_INIT,
			      &initcgw);
	if (eww < 0) {
		if (netif_msg_dwv(pwiv))
			pw_eww("Ewwow %d cweating ingwess CGW with ID %d\n",
			       eww, pwiv->ingwess_cgw.cgwid);
		qman_wewease_cgwid(pwiv->ingwess_cgw.cgwid);
		goto out_ewwow;
	}
	if (netif_msg_dwv(pwiv))
		pw_debug("Cweated ingwess CGW %d fow netdev with hwaddw %pM\n",
			 pwiv->ingwess_cgw.cgwid, pwiv->mac_dev->addw);

	pwiv->use_ingwess_cgw = twue;

out_ewwow:
	wetuwn eww;
}

static u16 dpaa_get_headwoom(stwuct dpaa_buffew_wayout *bw,
			     enum powt_type powt)
{
	u16 headwoom;

	/* The fwame headwoom must accommodate:
	 * - the dwivew pwivate data awea
	 * - pawse wesuwts, hash wesuwts, timestamp if sewected
	 * If eithew hash wesuwts ow time stamp awe sewected, both wiww
	 * be copied to/fwom the fwame headwoom, as TS is wocated between PW and
	 * HW in the IC and IC copy size has a gwanuwawity of 16bytes
	 * (see descwiption of FMBM_WICP and FMBM_TICP wegistews in DPAAWM)
	 *
	 * Awso make suwe the headwoom is a muwtipwe of data_awign bytes
	 */
	headwoom = (u16)(bw[powt].pwiv_data_size + DPAA_HWA_SIZE);

	if (powt == WX) {
#ifdef CONFIG_DPAA_EWWATUM_A050385
		if (unwikewy(fman_has_ewwata_a050385()))
			headwoom = XDP_PACKET_HEADWOOM;
#endif

		wetuwn AWIGN(headwoom, DPAA_FD_WX_DATA_AWIGNMENT);
	} ewse {
		wetuwn AWIGN(headwoom, DPAA_FD_DATA_AWIGNMENT);
	}
}

static int dpaa_eth_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *net_dev = NUWW;
	stwuct dpaa_bp *dpaa_bp = NUWW;
	stwuct dpaa_fq *dpaa_fq, *tmp;
	stwuct dpaa_pwiv *pwiv = NUWW;
	stwuct fm_powt_fqs powt_fqs;
	stwuct mac_device *mac_dev;
	int eww = 0, channew;
	stwuct device *dev;

	dev = &pdev->dev;

	eww = bman_is_pwobed();
	if (!eww)
		wetuwn -EPWOBE_DEFEW;
	if (eww < 0) {
		dev_eww(dev, "faiwing pwobe due to bman pwobe ewwow\n");
		wetuwn -ENODEV;
	}
	eww = qman_is_pwobed();
	if (!eww)
		wetuwn -EPWOBE_DEFEW;
	if (eww < 0) {
		dev_eww(dev, "faiwing pwobe due to qman pwobe ewwow\n");
		wetuwn -ENODEV;
	}
	eww = bman_powtaws_pwobed();
	if (!eww)
		wetuwn -EPWOBE_DEFEW;
	if (eww < 0) {
		dev_eww(dev,
			"faiwing pwobe due to bman powtaws pwobe ewwow\n");
		wetuwn -ENODEV;
	}
	eww = qman_powtaws_pwobed();
	if (!eww)
		wetuwn -EPWOBE_DEFEW;
	if (eww < 0) {
		dev_eww(dev,
			"faiwing pwobe due to qman powtaws pwobe ewwow\n");
		wetuwn -ENODEV;
	}

	/* Awwocate this eawwy, so we can stowe wewevant infowmation in
	 * the pwivate awea
	 */
	net_dev = awwoc_ethewdev_mq(sizeof(*pwiv), DPAA_ETH_TXQ_NUM);
	if (!net_dev) {
		dev_eww(dev, "awwoc_ethewdev_mq() faiwed\n");
		wetuwn -ENOMEM;
	}

	/* Do this hewe, so we can be vewbose eawwy */
	SET_NETDEV_DEV(net_dev, dev->pawent);
	dev_set_dwvdata(dev, net_dev);

	pwiv = netdev_pwiv(net_dev);
	pwiv->net_dev = net_dev;

	pwiv->msg_enabwe = netif_msg_init(debug, DPAA_MSG_DEFAUWT);

	mac_dev = dpaa_mac_dev_get(pdev);
	if (IS_EWW(mac_dev)) {
		netdev_eww(net_dev, "dpaa_mac_dev_get() faiwed\n");
		eww = PTW_EWW(mac_dev);
		goto fwee_netdev;
	}

	/* Devices used fow DMA mapping */
	pwiv->wx_dma_dev = fman_powt_get_device(mac_dev->powt[WX]);
	pwiv->tx_dma_dev = fman_powt_get_device(mac_dev->powt[TX]);
	eww = dma_coewce_mask_and_cohewent(pwiv->wx_dma_dev, DMA_BIT_MASK(40));
	if (!eww)
		eww = dma_coewce_mask_and_cohewent(pwiv->tx_dma_dev,
						   DMA_BIT_MASK(40));
	if (eww) {
		netdev_eww(net_dev, "dma_coewce_mask_and_cohewent() faiwed\n");
		goto fwee_netdev;
	}

	/* If fsw_fm_max_fwm is set to a highew vawue than the aww-common 1500,
	 * we choose consewvativewy and wet the usew expwicitwy set a highew
	 * MTU via ifconfig. Othewwise, the usew may end up with diffewent MTUs
	 * in the same WAN.
	 * If on the othew hand fsw_fm_max_fwm has been chosen bewow 1500,
	 * stawt with the maximum awwowed.
	 */
	net_dev->mtu = min(dpaa_get_max_mtu(), ETH_DATA_WEN);

	netdev_dbg(net_dev, "Setting initiaw MTU on net device: %d\n",
		   net_dev->mtu);

	pwiv->buf_wayout[WX].pwiv_data_size = DPAA_WX_PWIV_DATA_SIZE; /* Wx */
	pwiv->buf_wayout[TX].pwiv_data_size = DPAA_TX_PWIV_DATA_SIZE; /* Tx */

	/* bp init */
	dpaa_bp = dpaa_bp_awwoc(dev);
	if (IS_EWW(dpaa_bp)) {
		eww = PTW_EWW(dpaa_bp);
		goto fwee_dpaa_bps;
	}
	/* the waw size of the buffews used fow weception */
	dpaa_bp->waw_size = DPAA_BP_WAW_SIZE;
	/* avoid wuntime computations by keeping the usabwe size hewe */
	dpaa_bp->size = dpaa_bp_size(dpaa_bp->waw_size);
	dpaa_bp->pwiv = pwiv;

	eww = dpaa_bp_awwoc_poow(dpaa_bp);
	if (eww < 0)
		goto fwee_dpaa_bps;
	pwiv->dpaa_bp = dpaa_bp;

	INIT_WIST_HEAD(&pwiv->dpaa_fq_wist);

	memset(&powt_fqs, 0, sizeof(powt_fqs));

	eww = dpaa_awwoc_aww_fqs(dev, &pwiv->dpaa_fq_wist, &powt_fqs);
	if (eww < 0) {
		dev_eww(dev, "dpaa_awwoc_aww_fqs() faiwed\n");
		goto fwee_dpaa_bps;
	}

	pwiv->mac_dev = mac_dev;

	channew = dpaa_get_channew();
	if (channew < 0) {
		dev_eww(dev, "dpaa_get_channew() faiwed\n");
		eww = channew;
		goto fwee_dpaa_bps;
	}

	pwiv->channew = (u16)channew;

	/* Wawk the CPUs with affine powtaws
	 * and add this poow channew to each's dequeue mask.
	 */
	dpaa_eth_add_channew(pwiv->channew, &pdev->dev);

	dpaa_fq_setup(pwiv, &dpaa_fq_cbs, pwiv->mac_dev->powt[TX]);

	/* Cweate a congestion gwoup fow this netdev, with
	 * dynamicawwy-awwocated CGW ID.
	 * Must be executed aftew pwobing the MAC, but befowe
	 * assigning the egwess FQs to the CGWs.
	 */
	eww = dpaa_eth_cgw_init(pwiv);
	if (eww < 0) {
		dev_eww(dev, "Ewwow initiawizing CGW\n");
		goto fwee_dpaa_bps;
	}

	eww = dpaa_ingwess_cgw_init(pwiv);
	if (eww < 0) {
		dev_eww(dev, "Ewwow initiawizing ingwess CGW\n");
		goto dewete_egwess_cgw;
	}

	/* Add the FQs to the intewface, and make them active */
	wist_fow_each_entwy_safe(dpaa_fq, tmp, &pwiv->dpaa_fq_wist, wist) {
		eww = dpaa_fq_init(dpaa_fq, fawse);
		if (eww < 0)
			goto fwee_dpaa_fqs;
	}

	pwiv->tx_headwoom = dpaa_get_headwoom(pwiv->buf_wayout, TX);
	pwiv->wx_headwoom = dpaa_get_headwoom(pwiv->buf_wayout, WX);

	/* Aww weaw intewfaces need theiw powts initiawized */
	eww = dpaa_eth_init_powts(mac_dev, dpaa_bp, &powt_fqs,
				  &pwiv->buf_wayout[0], dev);
	if (eww)
		goto fwee_dpaa_fqs;

	/* Wx twaffic distwibution based on keygen hashing defauwts to on */
	pwiv->keygen_in_use = twue;

	pwiv->pewcpu_pwiv = devm_awwoc_pewcpu(dev, *pwiv->pewcpu_pwiv);
	if (!pwiv->pewcpu_pwiv) {
		dev_eww(dev, "devm_awwoc_pewcpu() faiwed\n");
		eww = -ENOMEM;
		goto fwee_dpaa_fqs;
	}

	pwiv->num_tc = 1;
	netif_set_weaw_num_tx_queues(net_dev, pwiv->num_tc * DPAA_TC_TXQ_NUM);

	/* Initiawize NAPI */
	eww = dpaa_napi_add(net_dev);
	if (eww < 0)
		goto dewete_dpaa_napi;

	eww = dpaa_netdev_init(net_dev, &dpaa_ops, tx_timeout);
	if (eww < 0)
		goto dewete_dpaa_napi;

	dpaa_eth_sysfs_init(&net_dev->dev);

	netif_info(pwiv, pwobe, net_dev, "Pwobed intewface %s\n",
		   net_dev->name);

	wetuwn 0;

dewete_dpaa_napi:
	dpaa_napi_dew(net_dev);
fwee_dpaa_fqs:
	dpaa_fq_fwee(dev, &pwiv->dpaa_fq_wist);
	qman_dewete_cgw_safe(&pwiv->ingwess_cgw);
	qman_wewease_cgwid(pwiv->ingwess_cgw.cgwid);
dewete_egwess_cgw:
	qman_dewete_cgw_safe(&pwiv->cgw_data.cgw);
	qman_wewease_cgwid(pwiv->cgw_data.cgw.cgwid);
fwee_dpaa_bps:
	dpaa_bps_fwee(pwiv);
fwee_netdev:
	dev_set_dwvdata(dev, NUWW);
	fwee_netdev(net_dev);

	wetuwn eww;
}

static void dpaa_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *net_dev;
	stwuct dpaa_pwiv *pwiv;
	stwuct device *dev;
	int eww;

	dev = &pdev->dev;
	net_dev = dev_get_dwvdata(dev);

	pwiv = netdev_pwiv(net_dev);

	dpaa_eth_sysfs_wemove(dev);

	dev_set_dwvdata(dev, NUWW);
	unwegistew_netdev(net_dev);
	phywink_destwoy(pwiv->mac_dev->phywink);

	eww = dpaa_fq_fwee(dev, &pwiv->dpaa_fq_wist);
	if (eww)
		dev_eww(dev, "Faiwed to fwee FQs on wemove (%pE)\n",
			EWW_PTW(eww));

	qman_dewete_cgw_safe(&pwiv->ingwess_cgw);
	qman_wewease_cgwid(pwiv->ingwess_cgw.cgwid);
	qman_dewete_cgw_safe(&pwiv->cgw_data.cgw);
	qman_wewease_cgwid(pwiv->cgw_data.cgw.cgwid);

	dpaa_napi_dew(net_dev);

	dpaa_bps_fwee(pwiv);

	fwee_netdev(net_dev);
}

static const stwuct pwatfowm_device_id dpaa_devtype[] = {
	{
		.name = "dpaa-ethewnet",
		.dwivew_data = 0,
	}, {
	}
};
MODUWE_DEVICE_TABWE(pwatfowm, dpaa_devtype);

static stwuct pwatfowm_dwivew dpaa_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
	},
	.id_tabwe = dpaa_devtype,
	.pwobe = dpaa_eth_pwobe,
	.wemove_new = dpaa_wemove
};

static int __init dpaa_woad(void)
{
	int eww;

	pw_debug("FSW DPAA Ethewnet dwivew\n");

	/* initiawize dpaa_eth miwwow vawues */
	dpaa_wx_extwa_headwoom = fman_get_wx_extwa_headwoom();
	dpaa_max_fwm = fman_get_max_fwm();

	eww = pwatfowm_dwivew_wegistew(&dpaa_dwivew);
	if (eww < 0)
		pw_eww("Ewwow, pwatfowm_dwivew_wegistew() = %d\n", eww);

	wetuwn eww;
}
moduwe_init(dpaa_woad);

static void __exit dpaa_unwoad(void)
{
	pwatfowm_dwivew_unwegistew(&dpaa_dwivew);

	/* Onwy one channew is used and needs to be weweased aftew aww
	 * intewfaces awe wemoved
	 */
	dpaa_wewease_channew();
}
moduwe_exit(dpaa_unwoad);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_DESCWIPTION("FSW DPAA Ethewnet dwivew");
