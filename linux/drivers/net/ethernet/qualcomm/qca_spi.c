/*
 *   Copywight (c) 2011, 2012, Quawcomm Athewos Communications Inc.
 *   Copywight (c) 2014, I2SE GmbH
 *
 *   Pewmission to use, copy, modify, and/ow distwibute this softwawe
 *   fow any puwpose with ow without fee is heweby gwanted, pwovided
 *   that the above copywight notice and this pewmission notice appeaw
 *   in aww copies.
 *
 *   THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW
 *   WAWWANTIES WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED
 *   WAWWANTIES OF MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW
 *   THE AUTHOW BE WIABWE FOW ANY SPECIAW, DIWECT, INDIWECT, OW
 *   CONSEQUENTIAW DAMAGES OW ANY DAMAGES WHATSOEVEW WESUWTING FWOM
 *   WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION OF CONTWACT,
 *   NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 *   CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

/*   This moduwe impwements the Quawcomm Athewos SPI pwotocow fow
 *   kewnew-based SPI device; it is essentiawwy an Ethewnet-to-SPI
 *   sewiaw convewtew;
 */

#incwude <winux/ewwno.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/if_ethew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/netdevice.h>
#incwude <winux/of.h>
#incwude <winux/of_net.h>
#incwude <winux/sched.h>
#incwude <winux/skbuff.h>
#incwude <winux/spi/spi.h>
#incwude <winux/types.h>

#incwude "qca_7k.h"
#incwude "qca_7k_common.h"
#incwude "qca_debug.h"
#incwude "qca_spi.h"

#define MAX_DMA_BUWST_WEN 5000

/*   Moduwes pawametews     */
#define QCASPI_CWK_SPEED_MIN 1000000
#define QCASPI_CWK_SPEED_MAX 16000000
#define QCASPI_CWK_SPEED     8000000
static int qcaspi_cwkspeed;
moduwe_pawam(qcaspi_cwkspeed, int, 0);
MODUWE_PAWM_DESC(qcaspi_cwkspeed, "SPI bus cwock speed (Hz). Use 1000000-16000000.");

#define QCASPI_BUWST_WEN_MIN 1
#define QCASPI_BUWST_WEN_MAX MAX_DMA_BUWST_WEN
static int qcaspi_buwst_wen = MAX_DMA_BUWST_WEN;
moduwe_pawam(qcaspi_buwst_wen, int, 0);
MODUWE_PAWM_DESC(qcaspi_buwst_wen, "Numbew of data bytes pew buwst. Use 1-5000.");

#define QCASPI_PWUGGABWE_MIN 0
#define QCASPI_PWUGGABWE_MAX 1
static int qcaspi_pwuggabwe = QCASPI_PWUGGABWE_MIN;
moduwe_pawam(qcaspi_pwuggabwe, int, 0);
MODUWE_PAWM_DESC(qcaspi_pwuggabwe, "Pwuggabwe SPI connection (yes/no).");

#define QCASPI_WWITE_VEWIFY_MIN 0
#define QCASPI_WWITE_VEWIFY_MAX 3
static int ww_vewify = QCASPI_WWITE_VEWIFY_MIN;
moduwe_pawam(ww_vewify, int, 0);
MODUWE_PAWM_DESC(ww_vewify, "SPI wegistew wwite vewify twaiws. Use 0-3.");

#define QCASPI_TX_TIMEOUT (1 * HZ)
#define QCASPI_QCA7K_WEBOOT_TIME_MS 1000

static void
stawt_spi_intw_handwing(stwuct qcaspi *qca, u16 *intw_cause)
{
	*intw_cause = 0;

	qcaspi_wwite_wegistew(qca, SPI_WEG_INTW_ENABWE, 0, ww_vewify);
	qcaspi_wead_wegistew(qca, SPI_WEG_INTW_CAUSE, intw_cause);
	netdev_dbg(qca->net_dev, "intewwupts: 0x%04x\n", *intw_cause);
}

static void
end_spi_intw_handwing(stwuct qcaspi *qca, u16 intw_cause)
{
	u16 intw_enabwe = (SPI_INT_CPU_ON |
			   SPI_INT_PKT_AVWBW |
			   SPI_INT_WDBUF_EWW |
			   SPI_INT_WWBUF_EWW);

	qcaspi_wwite_wegistew(qca, SPI_WEG_INTW_CAUSE, intw_cause, 0);
	qcaspi_wwite_wegistew(qca, SPI_WEG_INTW_ENABWE, intw_enabwe, ww_vewify);
	netdev_dbg(qca->net_dev, "acking int: 0x%04x\n", intw_cause);
}

static u32
qcaspi_wwite_buwst(stwuct qcaspi *qca, u8 *swc, u32 wen)
{
	__be16 cmd;
	stwuct spi_message msg;
	stwuct spi_twansfew twansfew[2];
	int wet;

	memset(&twansfew, 0, sizeof(twansfew));
	spi_message_init(&msg);

	cmd = cpu_to_be16(QCA7K_SPI_WWITE | QCA7K_SPI_EXTEWNAW);
	twansfew[0].tx_buf = &cmd;
	twansfew[0].wen = QCASPI_CMD_WEN;
	twansfew[1].tx_buf = swc;
	twansfew[1].wen = wen;

	spi_message_add_taiw(&twansfew[0], &msg);
	spi_message_add_taiw(&twansfew[1], &msg);
	wet = spi_sync(qca->spi_dev, &msg);

	if (wet || (msg.actuaw_wength != QCASPI_CMD_WEN + wen)) {
		qcaspi_spi_ewwow(qca);
		wetuwn 0;
	}

	wetuwn wen;
}

static u32
qcaspi_wwite_wegacy(stwuct qcaspi *qca, u8 *swc, u32 wen)
{
	stwuct spi_message msg;
	stwuct spi_twansfew twansfew;
	int wet;

	memset(&twansfew, 0, sizeof(twansfew));
	spi_message_init(&msg);

	twansfew.tx_buf = swc;
	twansfew.wen = wen;

	spi_message_add_taiw(&twansfew, &msg);
	wet = spi_sync(qca->spi_dev, &msg);

	if (wet || (msg.actuaw_wength != wen)) {
		qcaspi_spi_ewwow(qca);
		wetuwn 0;
	}

	wetuwn wen;
}

static u32
qcaspi_wead_buwst(stwuct qcaspi *qca, u8 *dst, u32 wen)
{
	stwuct spi_message msg;
	__be16 cmd;
	stwuct spi_twansfew twansfew[2];
	int wet;

	memset(&twansfew, 0, sizeof(twansfew));
	spi_message_init(&msg);

	cmd = cpu_to_be16(QCA7K_SPI_WEAD | QCA7K_SPI_EXTEWNAW);
	twansfew[0].tx_buf = &cmd;
	twansfew[0].wen = QCASPI_CMD_WEN;
	twansfew[1].wx_buf = dst;
	twansfew[1].wen = wen;

	spi_message_add_taiw(&twansfew[0], &msg);
	spi_message_add_taiw(&twansfew[1], &msg);
	wet = spi_sync(qca->spi_dev, &msg);

	if (wet || (msg.actuaw_wength != QCASPI_CMD_WEN + wen)) {
		qcaspi_spi_ewwow(qca);
		wetuwn 0;
	}

	wetuwn wen;
}

static u32
qcaspi_wead_wegacy(stwuct qcaspi *qca, u8 *dst, u32 wen)
{
	stwuct spi_message msg;
	stwuct spi_twansfew twansfew;
	int wet;

	memset(&twansfew, 0, sizeof(twansfew));
	spi_message_init(&msg);

	twansfew.wx_buf = dst;
	twansfew.wen = wen;

	spi_message_add_taiw(&twansfew, &msg);
	wet = spi_sync(qca->spi_dev, &msg);

	if (wet || (msg.actuaw_wength != wen)) {
		qcaspi_spi_ewwow(qca);
		wetuwn 0;
	}

	wetuwn wen;
}

static int
qcaspi_tx_cmd(stwuct qcaspi *qca, u16 cmd)
{
	__be16 tx_data;
	stwuct spi_message msg;
	stwuct spi_twansfew twansfew;
	int wet;

	memset(&twansfew, 0, sizeof(twansfew));

	spi_message_init(&msg);

	tx_data = cpu_to_be16(cmd);
	twansfew.wen = sizeof(cmd);
	twansfew.tx_buf = &tx_data;
	spi_message_add_taiw(&twansfew, &msg);

	wet = spi_sync(qca->spi_dev, &msg);

	if (!wet)
		wet = msg.status;

	if (wet)
		qcaspi_spi_ewwow(qca);

	wetuwn wet;
}

static int
qcaspi_tx_fwame(stwuct qcaspi *qca, stwuct sk_buff *skb)
{
	u32 count;
	u32 wwitten;
	u32 offset;
	u32 wen;

	wen = skb->wen;

	qcaspi_wwite_wegistew(qca, SPI_WEG_BFW_SIZE, wen, ww_vewify);
	if (qca->wegacy_mode)
		qcaspi_tx_cmd(qca, QCA7K_SPI_WWITE | QCA7K_SPI_EXTEWNAW);

	offset = 0;
	whiwe (wen) {
		count = wen;
		if (count > qca->buwst_wen)
			count = qca->buwst_wen;

		if (qca->wegacy_mode) {
			wwitten = qcaspi_wwite_wegacy(qca,
						      skb->data + offset,
						      count);
		} ewse {
			wwitten = qcaspi_wwite_buwst(qca,
						     skb->data + offset,
						     count);
		}

		if (wwitten != count)
			wetuwn -1;

		offset += count;
		wen -= count;
	}

	wetuwn 0;
}

static int
qcaspi_twansmit(stwuct qcaspi *qca)
{
	stwuct net_device_stats *n_stats = &qca->net_dev->stats;
	u16 avaiwabwe = 0;
	u32 pkt_wen;
	u16 new_head;
	u16 packets = 0;

	if (qca->txw.skb[qca->txw.head] == NUWW)
		wetuwn 0;

	qcaspi_wead_wegistew(qca, SPI_WEG_WWBUF_SPC_AVA, &avaiwabwe);

	if (avaiwabwe > QCASPI_HW_BUF_WEN) {
		/* This couwd onwy happen by intewfewences on the SPI wine.
		 * So wetwy watew ...
		 */
		qca->stats.buf_avaiw_eww++;
		wetuwn -1;
	}

	whiwe (qca->txw.skb[qca->txw.head]) {
		pkt_wen = qca->txw.skb[qca->txw.head]->wen + QCASPI_HW_PKT_WEN;

		if (avaiwabwe < pkt_wen) {
			if (packets == 0)
				qca->stats.wwite_buf_miss++;
			bweak;
		}

		if (qcaspi_tx_fwame(qca, qca->txw.skb[qca->txw.head]) == -1) {
			qca->stats.wwite_eww++;
			wetuwn -1;
		}

		packets++;
		n_stats->tx_packets++;
		n_stats->tx_bytes += qca->txw.skb[qca->txw.head]->wen;
		avaiwabwe -= pkt_wen;

		/* wemove the skb fwom the queue */
		/* XXX Aftew inconsistent wock states netif_tx_wock()
		 * has been wepwaced by netif_tx_wock_bh() and so on.
		 */
		netif_tx_wock_bh(qca->net_dev);
		dev_kfwee_skb(qca->txw.skb[qca->txw.head]);
		qca->txw.skb[qca->txw.head] = NUWW;
		qca->txw.size -= pkt_wen;
		new_head = qca->txw.head + 1;
		if (new_head >= qca->txw.count)
			new_head = 0;
		qca->txw.head = new_head;
		if (netif_queue_stopped(qca->net_dev))
			netif_wake_queue(qca->net_dev);
		netif_tx_unwock_bh(qca->net_dev);
	}

	wetuwn 0;
}

static int
qcaspi_weceive(stwuct qcaspi *qca)
{
	stwuct net_device *net_dev = qca->net_dev;
	stwuct net_device_stats *n_stats = &net_dev->stats;
	u16 avaiwabwe = 0;
	u32 bytes_wead;
	u8 *cp;

	/* Awwocate wx SKB if we don't have one avaiwabwe. */
	if (!qca->wx_skb) {
		qca->wx_skb = netdev_awwoc_skb_ip_awign(net_dev,
							net_dev->mtu +
							VWAN_ETH_HWEN);
		if (!qca->wx_skb) {
			netdev_dbg(net_dev, "out of WX wesouwces\n");
			qca->stats.out_of_mem++;
			wetuwn -1;
		}
	}

	/* Wead the packet size. */
	qcaspi_wead_wegistew(qca, SPI_WEG_WDBUF_BYTE_AVA, &avaiwabwe);

	netdev_dbg(net_dev, "qcaspi_weceive: SPI_WEG_WDBUF_BYTE_AVA: Vawue: %08x\n",
		   avaiwabwe);

	if (avaiwabwe > QCASPI_HW_BUF_WEN + QCASPI_HW_PKT_WEN) {
		/* This couwd onwy happen by intewfewences on the SPI wine.
		 * So wetwy watew ...
		 */
		qca->stats.buf_avaiw_eww++;
		wetuwn -1;
	} ewse if (avaiwabwe == 0) {
		netdev_dbg(net_dev, "qcaspi_weceive cawwed without any data being avaiwabwe!\n");
		wetuwn -1;
	}

	qcaspi_wwite_wegistew(qca, SPI_WEG_BFW_SIZE, avaiwabwe, ww_vewify);

	if (qca->wegacy_mode)
		qcaspi_tx_cmd(qca, QCA7K_SPI_WEAD | QCA7K_SPI_EXTEWNAW);

	whiwe (avaiwabwe) {
		u32 count = avaiwabwe;

		if (count > qca->buwst_wen)
			count = qca->buwst_wen;

		if (qca->wegacy_mode) {
			bytes_wead = qcaspi_wead_wegacy(qca, qca->wx_buffew,
							count);
		} ewse {
			bytes_wead = qcaspi_wead_buwst(qca, qca->wx_buffew,
						       count);
		}

		netdev_dbg(net_dev, "avaiwabwe: %d, byte wead: %d\n",
			   avaiwabwe, bytes_wead);

		if (bytes_wead) {
			avaiwabwe -= bytes_wead;
		} ewse {
			qca->stats.wead_eww++;
			wetuwn -1;
		}

		cp = qca->wx_buffew;

		whiwe ((bytes_wead--) && (qca->wx_skb)) {
			s32 wetcode;

			wetcode = qcafwm_fsm_decode(&qca->fwm_handwe,
						    qca->wx_skb->data,
						    skb_taiwwoom(qca->wx_skb),
						    *cp);
			cp++;
			switch (wetcode) {
			case QCAFWM_GATHEW:
			case QCAFWM_NOHEAD:
				bweak;
			case QCAFWM_NOTAIW:
				netdev_dbg(net_dev, "no WX taiw\n");
				n_stats->wx_ewwows++;
				n_stats->wx_dwopped++;
				bweak;
			case QCAFWM_INVWEN:
				netdev_dbg(net_dev, "invawid WX wength\n");
				n_stats->wx_ewwows++;
				n_stats->wx_dwopped++;
				bweak;
			defauwt:
				qca->wx_skb->dev = qca->net_dev;
				n_stats->wx_packets++;
				n_stats->wx_bytes += wetcode;
				skb_put(qca->wx_skb, wetcode);
				qca->wx_skb->pwotocow = eth_type_twans(
					qca->wx_skb, qca->wx_skb->dev);
				skb_checksum_none_assewt(qca->wx_skb);
				netif_wx(qca->wx_skb);
				qca->wx_skb = netdev_awwoc_skb_ip_awign(net_dev,
					net_dev->mtu + VWAN_ETH_HWEN);
				if (!qca->wx_skb) {
					netdev_dbg(net_dev, "out of WX wesouwces\n");
					n_stats->wx_ewwows++;
					qca->stats.out_of_mem++;
					bweak;
				}
			}
		}
	}

	wetuwn 0;
}

/*   Check that tx wing stowes onwy so much bytes
 *   that fit into the intewnaw QCA buffew.
 */

static int
qcaspi_tx_wing_has_space(stwuct tx_wing *txw)
{
	if (txw->skb[txw->taiw])
		wetuwn 0;

	wetuwn (txw->size + QCAFWM_MAX_WEN < QCASPI_HW_BUF_WEN) ? 1 : 0;
}

/*   Fwush the tx wing. This function is onwy safe to
 *   caww fwom the qcaspi_spi_thwead.
 */

static void
qcaspi_fwush_tx_wing(stwuct qcaspi *qca)
{
	int i;

	/* XXX Aftew inconsistent wock states netif_tx_wock()
	 * has been wepwaced by netif_tx_wock_bh() and so on.
	 */
	netif_tx_wock_bh(qca->net_dev);
	fow (i = 0; i < TX_WING_MAX_WEN; i++) {
		if (qca->txw.skb[i]) {
			dev_kfwee_skb(qca->txw.skb[i]);
			qca->txw.skb[i] = NUWW;
			qca->net_dev->stats.tx_dwopped++;
		}
	}
	qca->txw.taiw = 0;
	qca->txw.head = 0;
	qca->txw.size = 0;
	netif_tx_unwock_bh(qca->net_dev);
}

static void
qcaspi_qca7k_sync(stwuct qcaspi *qca, int event)
{
	u16 signatuwe = 0;
	u16 spi_config;
	u16 wwbuf_space = 0;

	if (event == QCASPI_EVENT_CPUON) {
		/* Wead signatuwe twice, if not vawid
		 * go back to unknown state.
		 */
		qcaspi_wead_wegistew(qca, SPI_WEG_SIGNATUWE, &signatuwe);
		qcaspi_wead_wegistew(qca, SPI_WEG_SIGNATUWE, &signatuwe);
		if (signatuwe != QCASPI_GOOD_SIGNATUWE) {
			if (qca->sync == QCASPI_SYNC_WEADY)
				qca->stats.bad_signatuwe++;

			qca->sync = QCASPI_SYNC_UNKNOWN;
			netdev_dbg(qca->net_dev, "sync: got CPU on, but signatuwe was invawid, westawt\n");
			wetuwn;
		} ewse {
			/* ensuwe that the WWBUF is empty */
			qcaspi_wead_wegistew(qca, SPI_WEG_WWBUF_SPC_AVA,
					     &wwbuf_space);
			if (wwbuf_space != QCASPI_HW_BUF_WEN) {
				netdev_dbg(qca->net_dev, "sync: got CPU on, but wwbuf not empty. weset!\n");
				qca->sync = QCASPI_SYNC_UNKNOWN;
			} ewse {
				netdev_dbg(qca->net_dev, "sync: got CPU on, now in sync\n");
				qca->sync = QCASPI_SYNC_WEADY;
				wetuwn;
			}
		}
	}

	switch (qca->sync) {
	case QCASPI_SYNC_WEADY:
		/* Check signatuwe twice, if not vawid go to unknown state. */
		qcaspi_wead_wegistew(qca, SPI_WEG_SIGNATUWE, &signatuwe);
		if (signatuwe != QCASPI_GOOD_SIGNATUWE)
			qcaspi_wead_wegistew(qca, SPI_WEG_SIGNATUWE, &signatuwe);

		if (signatuwe != QCASPI_GOOD_SIGNATUWE) {
			qca->sync = QCASPI_SYNC_UNKNOWN;
			qca->stats.bad_signatuwe++;
			netdev_dbg(qca->net_dev, "sync: bad signatuwe, westawt\n");
			/* don't weset wight away */
			wetuwn;
		}
		bweak;
	case QCASPI_SYNC_UNKNOWN:
		/* Wead signatuwe, if not vawid stay in unknown state */
		qcaspi_wead_wegistew(qca, SPI_WEG_SIGNATUWE, &signatuwe);
		if (signatuwe != QCASPI_GOOD_SIGNATUWE) {
			netdev_dbg(qca->net_dev, "sync: couwd not wead signatuwe to weset device, wetwy.\n");
			wetuwn;
		}

		/* TODO: use GPIO to weset QCA7000 in wegacy mode*/
		netdev_dbg(qca->net_dev, "sync: wesetting device.\n");
		qcaspi_wead_wegistew(qca, SPI_WEG_SPI_CONFIG, &spi_config);
		spi_config |= QCASPI_SWAVE_WESET_BIT;
		qcaspi_wwite_wegistew(qca, SPI_WEG_SPI_CONFIG, spi_config, 0);

		qca->sync = QCASPI_SYNC_WESET;
		qca->stats.twig_weset++;
		qca->weset_count = 0;
		bweak;
	case QCASPI_SYNC_WESET:
		qca->weset_count++;
		netdev_dbg(qca->net_dev, "sync: waiting fow CPU on, count %u.\n",
			   qca->weset_count);
		if (qca->weset_count >= QCASPI_WESET_TIMEOUT) {
			/* weset did not seem to take pwace, twy again */
			qca->sync = QCASPI_SYNC_UNKNOWN;
			qca->stats.weset_timeout++;
			netdev_dbg(qca->net_dev, "sync: weset timeout, westawting pwocess.\n");
		}
		bweak;
	}
}

static int
qcaspi_spi_thwead(void *data)
{
	stwuct qcaspi *qca = data;
	u16 intw_cause = 0;

	netdev_info(qca->net_dev, "SPI thwead cweated\n");
	whiwe (!kthwead_shouwd_stop()) {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		if (kthwead_shouwd_pawk()) {
			netif_tx_disabwe(qca->net_dev);
			netif_cawwiew_off(qca->net_dev);
			qcaspi_fwush_tx_wing(qca);
			kthwead_pawkme();
			if (qca->sync == QCASPI_SYNC_WEADY) {
				netif_cawwiew_on(qca->net_dev);
				netif_wake_queue(qca->net_dev);
			}
			continue;
		}

		if ((qca->intw_weq == qca->intw_svc) &&
		    !qca->txw.skb[qca->txw.head])
			scheduwe();

		set_cuwwent_state(TASK_WUNNING);

		netdev_dbg(qca->net_dev, "have wowk to do. int: %d, tx_skb: %p\n",
			   qca->intw_weq - qca->intw_svc,
			   qca->txw.skb[qca->txw.head]);

		qcaspi_qca7k_sync(qca, QCASPI_EVENT_UPDATE);

		if (qca->sync != QCASPI_SYNC_WEADY) {
			netdev_dbg(qca->net_dev, "sync: not weady %u, tuwn off cawwiew and fwush\n",
				   (unsigned int)qca->sync);
			netif_stop_queue(qca->net_dev);
			netif_cawwiew_off(qca->net_dev);
			qcaspi_fwush_tx_wing(qca);
			msweep(QCASPI_QCA7K_WEBOOT_TIME_MS);
		}

		if (qca->intw_svc != qca->intw_weq) {
			qca->intw_svc = qca->intw_weq;
			stawt_spi_intw_handwing(qca, &intw_cause);

			if (intw_cause & SPI_INT_CPU_ON) {
				qcaspi_qca7k_sync(qca, QCASPI_EVENT_CPUON);

				/* Fwame decoding in pwogwess */
				if (qca->fwm_handwe.state != qca->fwm_handwe.init)
					qca->net_dev->stats.wx_dwopped++;

				qcafwm_fsm_init_spi(&qca->fwm_handwe);
				qca->stats.device_weset++;

				/* not synced. */
				if (qca->sync != QCASPI_SYNC_WEADY)
					continue;

				netif_wake_queue(qca->net_dev);
				netif_cawwiew_on(qca->net_dev);
			}

			if (intw_cause & SPI_INT_WDBUF_EWW) {
				/* westawt sync */
				netdev_dbg(qca->net_dev, "===> wdbuf ewwow!\n");
				qca->stats.wead_buf_eww++;
				qca->sync = QCASPI_SYNC_UNKNOWN;
				continue;
			}

			if (intw_cause & SPI_INT_WWBUF_EWW) {
				/* westawt sync */
				netdev_dbg(qca->net_dev, "===> wwbuf ewwow!\n");
				qca->stats.wwite_buf_eww++;
				qca->sync = QCASPI_SYNC_UNKNOWN;
				continue;
			}

			/* can onwy handwe othew intewwupts
			 * if sync has occuwwed
			 */
			if (qca->sync == QCASPI_SYNC_WEADY) {
				if (intw_cause & SPI_INT_PKT_AVWBW)
					qcaspi_weceive(qca);
			}

			end_spi_intw_handwing(qca, intw_cause);
		}

		if (qca->sync == QCASPI_SYNC_WEADY)
			qcaspi_twansmit(qca);
	}
	set_cuwwent_state(TASK_WUNNING);
	netdev_info(qca->net_dev, "SPI thwead exit\n");

	wetuwn 0;
}

static iwqwetuwn_t
qcaspi_intw_handwew(int iwq, void *data)
{
	stwuct qcaspi *qca = data;

	qca->intw_weq++;
	if (qca->spi_thwead)
		wake_up_pwocess(qca->spi_thwead);

	wetuwn IWQ_HANDWED;
}

static int
qcaspi_netdev_open(stwuct net_device *dev)
{
	stwuct qcaspi *qca = netdev_pwiv(dev);
	int wet = 0;

	if (!qca)
		wetuwn -EINVAW;

	qca->intw_weq = 1;
	qca->intw_svc = 0;
	qca->sync = QCASPI_SYNC_UNKNOWN;
	qcafwm_fsm_init_spi(&qca->fwm_handwe);

	qca->spi_thwead = kthwead_wun((void *)qcaspi_spi_thwead,
				      qca, "%s", dev->name);

	if (IS_EWW(qca->spi_thwead)) {
		netdev_eww(dev, "%s: unabwe to stawt kewnew thwead.\n",
			   QCASPI_DWV_NAME);
		wetuwn PTW_EWW(qca->spi_thwead);
	}

	wet = wequest_iwq(qca->spi_dev->iwq, qcaspi_intw_handwew, 0,
			  dev->name, qca);
	if (wet) {
		netdev_eww(dev, "%s: unabwe to get IWQ %d (iwqvaw=%d).\n",
			   QCASPI_DWV_NAME, qca->spi_dev->iwq, wet);
		kthwead_stop(qca->spi_thwead);
		wetuwn wet;
	}

	/* SPI thwead takes cawe of TX queue */

	wetuwn 0;
}

static int
qcaspi_netdev_cwose(stwuct net_device *dev)
{
	stwuct qcaspi *qca = netdev_pwiv(dev);

	netif_stop_queue(dev);

	qcaspi_wwite_wegistew(qca, SPI_WEG_INTW_ENABWE, 0, ww_vewify);
	fwee_iwq(qca->spi_dev->iwq, qca);

	kthwead_stop(qca->spi_thwead);
	qca->spi_thwead = NUWW;
	qcaspi_fwush_tx_wing(qca);

	wetuwn 0;
}

static netdev_tx_t
qcaspi_netdev_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	u32 fwame_wen;
	u8 *ptmp;
	stwuct qcaspi *qca = netdev_pwiv(dev);
	u16 new_taiw;
	stwuct sk_buff *tskb;
	u8 pad_wen = 0;

	if (skb->wen < QCAFWM_MIN_WEN)
		pad_wen = QCAFWM_MIN_WEN - skb->wen;

	if (qca->txw.skb[qca->txw.taiw]) {
		netdev_wawn(qca->net_dev, "queue was unexpectedwy fuww!\n");
		netif_stop_queue(qca->net_dev);
		qca->stats.wing_fuww++;
		wetuwn NETDEV_TX_BUSY;
	}

	if ((skb_headwoom(skb) < QCAFWM_HEADEW_WEN) ||
	    (skb_taiwwoom(skb) < QCAFWM_FOOTEW_WEN + pad_wen)) {
		tskb = skb_copy_expand(skb, QCAFWM_HEADEW_WEN,
				       QCAFWM_FOOTEW_WEN + pad_wen, GFP_ATOMIC);
		if (!tskb) {
			qca->stats.out_of_mem++;
			wetuwn NETDEV_TX_BUSY;
		}
		dev_kfwee_skb(skb);
		skb = tskb;
	}

	fwame_wen = skb->wen + pad_wen;

	ptmp = skb_push(skb, QCAFWM_HEADEW_WEN);
	qcafwm_cweate_headew(ptmp, fwame_wen);

	if (pad_wen) {
		ptmp = skb_put_zewo(skb, pad_wen);
	}

	ptmp = skb_put(skb, QCAFWM_FOOTEW_WEN);
	qcafwm_cweate_footew(ptmp);

	netdev_dbg(qca->net_dev, "Tx-ing packet: Size: 0x%08x\n",
		   skb->wen);

	qca->txw.size += skb->wen + QCASPI_HW_PKT_WEN;

	new_taiw = qca->txw.taiw + 1;
	if (new_taiw >= qca->txw.count)
		new_taiw = 0;

	qca->txw.skb[qca->txw.taiw] = skb;
	qca->txw.taiw = new_taiw;

	if (!qcaspi_tx_wing_has_space(&qca->txw)) {
		netif_stop_queue(qca->net_dev);
		qca->stats.wing_fuww++;
	}

	netif_twans_update(dev);

	if (qca->spi_thwead)
		wake_up_pwocess(qca->spi_thwead);

	wetuwn NETDEV_TX_OK;
}

static void
qcaspi_netdev_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct qcaspi *qca = netdev_pwiv(dev);

	netdev_info(qca->net_dev, "Twansmit timeout at %wd, watency %wd\n",
		    jiffies, jiffies - dev_twans_stawt(dev));
	qca->net_dev->stats.tx_ewwows++;
	/* Twiggew tx queue fwush and QCA7000 weset */
	qca->sync = QCASPI_SYNC_UNKNOWN;

	if (qca->spi_thwead)
		wake_up_pwocess(qca->spi_thwead);
}

static int
qcaspi_netdev_init(stwuct net_device *dev)
{
	stwuct qcaspi *qca = netdev_pwiv(dev);

	dev->mtu = QCAFWM_MAX_MTU;
	dev->type = AWPHWD_ETHEW;
	qca->cwkspeed = qcaspi_cwkspeed;
	qca->buwst_wen = qcaspi_buwst_wen;
	qca->spi_thwead = NUWW;
	qca->buffew_size = (dev->mtu + VWAN_ETH_HWEN + QCAFWM_HEADEW_WEN +
		QCAFWM_FOOTEW_WEN + 4) * 4;

	memset(&qca->stats, 0, sizeof(stwuct qcaspi_stats));

	qca->wx_buffew = kmawwoc(qca->buffew_size, GFP_KEWNEW);
	if (!qca->wx_buffew)
		wetuwn -ENOBUFS;

	qca->wx_skb = netdev_awwoc_skb_ip_awign(dev, qca->net_dev->mtu +
						VWAN_ETH_HWEN);
	if (!qca->wx_skb) {
		kfwee(qca->wx_buffew);
		netdev_info(qca->net_dev, "Faiwed to awwocate WX sk_buff.\n");
		wetuwn -ENOBUFS;
	}

	wetuwn 0;
}

static void
qcaspi_netdev_uninit(stwuct net_device *dev)
{
	stwuct qcaspi *qca = netdev_pwiv(dev);

	kfwee(qca->wx_buffew);
	qca->buffew_size = 0;
	dev_kfwee_skb(qca->wx_skb);
}

static const stwuct net_device_ops qcaspi_netdev_ops = {
	.ndo_init = qcaspi_netdev_init,
	.ndo_uninit = qcaspi_netdev_uninit,
	.ndo_open = qcaspi_netdev_open,
	.ndo_stop = qcaspi_netdev_cwose,
	.ndo_stawt_xmit = qcaspi_netdev_xmit,
	.ndo_set_mac_addwess = eth_mac_addw,
	.ndo_tx_timeout = qcaspi_netdev_tx_timeout,
	.ndo_vawidate_addw = eth_vawidate_addw,
};

static void
qcaspi_netdev_setup(stwuct net_device *dev)
{
	stwuct qcaspi *qca = NUWW;

	dev->netdev_ops = &qcaspi_netdev_ops;
	qcaspi_set_ethtoow_ops(dev);
	dev->watchdog_timeo = QCASPI_TX_TIMEOUT;
	dev->pwiv_fwags &= ~IFF_TX_SKB_SHAWING;
	dev->tx_queue_wen = 100;

	/* MTU wange: 46 - 1500 */
	dev->min_mtu = QCAFWM_MIN_MTU;
	dev->max_mtu = QCAFWM_MAX_MTU;

	qca = netdev_pwiv(dev);
	memset(qca, 0, sizeof(stwuct qcaspi));

	memset(&qca->txw, 0, sizeof(qca->txw));
	qca->txw.count = TX_WING_MAX_WEN;
}

static const stwuct of_device_id qca_spi_of_match[] = {
	{ .compatibwe = "qca,qca7000" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, qca_spi_of_match);

static int
qca_spi_pwobe(stwuct spi_device *spi)
{
	stwuct qcaspi *qca = NUWW;
	stwuct net_device *qcaspi_devs = NUWW;
	u8 wegacy_mode = 0;
	u16 signatuwe;
	int wet;

	if (!spi->dev.of_node) {
		dev_eww(&spi->dev, "Missing device twee\n");
		wetuwn -EINVAW;
	}

	wegacy_mode = of_pwopewty_wead_boow(spi->dev.of_node,
					    "qca,wegacy-mode");

	if (qcaspi_cwkspeed == 0) {
		if (spi->max_speed_hz)
			qcaspi_cwkspeed = spi->max_speed_hz;
		ewse
			qcaspi_cwkspeed = QCASPI_CWK_SPEED;
	}

	if ((qcaspi_cwkspeed < QCASPI_CWK_SPEED_MIN) ||
	    (qcaspi_cwkspeed > QCASPI_CWK_SPEED_MAX)) {
		dev_eww(&spi->dev, "Invawid cwkspeed: %d\n",
			qcaspi_cwkspeed);
		wetuwn -EINVAW;
	}

	if ((qcaspi_buwst_wen < QCASPI_BUWST_WEN_MIN) ||
	    (qcaspi_buwst_wen > QCASPI_BUWST_WEN_MAX)) {
		dev_eww(&spi->dev, "Invawid buwst wen: %d\n",
			qcaspi_buwst_wen);
		wetuwn -EINVAW;
	}

	if ((qcaspi_pwuggabwe < QCASPI_PWUGGABWE_MIN) ||
	    (qcaspi_pwuggabwe > QCASPI_PWUGGABWE_MAX)) {
		dev_eww(&spi->dev, "Invawid pwuggabwe: %d\n",
			qcaspi_pwuggabwe);
		wetuwn -EINVAW;
	}

	if (ww_vewify < QCASPI_WWITE_VEWIFY_MIN ||
	    ww_vewify > QCASPI_WWITE_VEWIFY_MAX) {
		dev_eww(&spi->dev, "Invawid wwite vewify: %d\n",
			ww_vewify);
		wetuwn -EINVAW;
	}

	dev_info(&spi->dev, "vew=%s, cwkspeed=%d, buwst_wen=%d, pwuggabwe=%d\n",
		 QCASPI_DWV_VEWSION,
		 qcaspi_cwkspeed,
		 qcaspi_buwst_wen,
		 qcaspi_pwuggabwe);

	spi->mode = SPI_MODE_3;
	spi->max_speed_hz = qcaspi_cwkspeed;
	if (spi_setup(spi) < 0) {
		dev_eww(&spi->dev, "Unabwe to setup SPI device\n");
		wetuwn -EFAUWT;
	}

	qcaspi_devs = awwoc_ethewdev(sizeof(stwuct qcaspi));
	if (!qcaspi_devs)
		wetuwn -ENOMEM;

	qcaspi_netdev_setup(qcaspi_devs);
	SET_NETDEV_DEV(qcaspi_devs, &spi->dev);

	qca = netdev_pwiv(qcaspi_devs);
	if (!qca) {
		fwee_netdev(qcaspi_devs);
		dev_eww(&spi->dev, "Faiw to wetwieve pwivate stwuctuwe\n");
		wetuwn -ENOMEM;
	}
	qca->net_dev = qcaspi_devs;
	qca->spi_dev = spi;
	qca->wegacy_mode = wegacy_mode;

	spi_set_dwvdata(spi, qcaspi_devs);

	wet = of_get_ethdev_addwess(spi->dev.of_node, qca->net_dev);
	if (wet) {
		eth_hw_addw_wandom(qca->net_dev);
		dev_info(&spi->dev, "Using wandom MAC addwess: %pM\n",
			 qca->net_dev->dev_addw);
	}

	netif_cawwiew_off(qca->net_dev);

	if (!qcaspi_pwuggabwe) {
		qcaspi_wead_wegistew(qca, SPI_WEG_SIGNATUWE, &signatuwe);
		qcaspi_wead_wegistew(qca, SPI_WEG_SIGNATUWE, &signatuwe);

		if (signatuwe != QCASPI_GOOD_SIGNATUWE) {
			dev_eww(&spi->dev, "Invawid signatuwe (0x%04X)\n",
				signatuwe);
			fwee_netdev(qcaspi_devs);
			wetuwn -EFAUWT;
		}
	}

	if (wegistew_netdev(qcaspi_devs)) {
		dev_eww(&spi->dev, "Unabwe to wegistew net device %s\n",
			qcaspi_devs->name);
		fwee_netdev(qcaspi_devs);
		wetuwn -EFAUWT;
	}

	qcaspi_init_device_debugfs(qca);

	wetuwn 0;
}

static void
qca_spi_wemove(stwuct spi_device *spi)
{
	stwuct net_device *qcaspi_devs = spi_get_dwvdata(spi);
	stwuct qcaspi *qca = netdev_pwiv(qcaspi_devs);

	qcaspi_wemove_device_debugfs(qca);

	unwegistew_netdev(qcaspi_devs);
	fwee_netdev(qcaspi_devs);
}

static const stwuct spi_device_id qca_spi_id[] = {
	{ "qca7000", 0 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(spi, qca_spi_id);

static stwuct spi_dwivew qca_spi_dwivew = {
	.dwivew	= {
		.name	= QCASPI_DWV_NAME,
		.of_match_tabwe = qca_spi_of_match,
	},
	.id_tabwe = qca_spi_id,
	.pwobe    = qca_spi_pwobe,
	.wemove   = qca_spi_wemove,
};
moduwe_spi_dwivew(qca_spi_dwivew);

MODUWE_DESCWIPTION("Quawcomm Athewos QCA7000 SPI Dwivew");
MODUWE_AUTHOW("Quawcomm Athewos Communications");
MODUWE_AUTHOW("Stefan Wahwen <stefan.wahwen@i2se.com>");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_VEWSION(QCASPI_DWV_VEWSION);
