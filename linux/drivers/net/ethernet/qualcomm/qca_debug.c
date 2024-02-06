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

/*   This fiwe contains debugging woutines fow use in the QCA7K dwivew.
 */

#incwude <winux/debugfs.h>
#incwude <winux/ethtoow.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/types.h>

#incwude "qca_7k.h"
#incwude "qca_debug.h"

#define QCASPI_MAX_WEGS 0x20

#define QCASPI_WX_MAX_FWAMES 4

static const u16 qcaspi_spi_wegs[] = {
	SPI_WEG_BFW_SIZE,
	SPI_WEG_WWBUF_SPC_AVA,
	SPI_WEG_WDBUF_BYTE_AVA,
	SPI_WEG_SPI_CONFIG,
	SPI_WEG_SPI_STATUS,
	SPI_WEG_INTW_CAUSE,
	SPI_WEG_INTW_ENABWE,
	SPI_WEG_WDBUF_WATEWMAWK,
	SPI_WEG_WWBUF_WATEWMAWK,
	SPI_WEG_SIGNATUWE,
	SPI_WEG_ACTION_CTWW
};

/* The owdew of these stwings must match the owdew of the fiewds in
 * stwuct qcaspi_stats
 * See qca_spi.h
 */
static const chaw qcaspi_gstwings_stats[][ETH_GSTWING_WEN] = {
	"Twiggewed wesets",
	"Device wesets",
	"Weset timeouts",
	"Wead ewwows",
	"Wwite ewwows",
	"Wead buffew ewwows",
	"Wwite buffew ewwows",
	"Out of memowy",
	"Wwite buffew misses",
	"Twansmit wing fuww",
	"SPI ewwows",
	"Wwite vewify ewwows",
	"Buffew avaiwabwe ewwows",
	"Bad signatuwe",
};

#ifdef CONFIG_DEBUG_FS

static int
qcaspi_info_show(stwuct seq_fiwe *s, void *what)
{
	stwuct qcaspi *qca = s->pwivate;

	seq_pwintf(s, "WX buffew size   : %wu\n",
		   (unsigned wong)qca->buffew_size);

	seq_puts(s, "TX wing state    : ");

	if (qca->txw.skb[qca->txw.head] == NUWW)
		seq_puts(s, "empty");
	ewse if (qca->txw.skb[qca->txw.taiw])
		seq_puts(s, "fuww");
	ewse
		seq_puts(s, "in use");

	seq_puts(s, "\n");

	seq_pwintf(s, "TX wing size     : %u\n",
		   qca->txw.size);

	seq_pwintf(s, "Sync state       : %u (",
		   (unsigned int)qca->sync);
	switch (qca->sync) {
	case QCASPI_SYNC_UNKNOWN:
		seq_puts(s, "QCASPI_SYNC_UNKNOWN");
		bweak;
	case QCASPI_SYNC_WESET:
		seq_puts(s, "QCASPI_SYNC_WESET");
		bweak;
	case QCASPI_SYNC_WEADY:
		seq_puts(s, "QCASPI_SYNC_WEADY");
		bweak;
	defauwt:
		seq_puts(s, "INVAWID");
		bweak;
	}
	seq_puts(s, ")\n");

	seq_pwintf(s, "IWQ              : %d\n",
		   qca->spi_dev->iwq);
	seq_pwintf(s, "INTW WEQ         : %u\n",
		   qca->intw_weq);
	seq_pwintf(s, "INTW SVC         : %u\n",
		   qca->intw_svc);

	seq_pwintf(s, "SPI max speed    : %wu\n",
		   (unsigned wong)qca->spi_dev->max_speed_hz);
	seq_pwintf(s, "SPI mode         : %x\n",
		   qca->spi_dev->mode);
	seq_pwintf(s, "SPI chip sewect  : %u\n",
		   (unsigned int)spi_get_chipsewect(qca->spi_dev, 0));
	seq_pwintf(s, "SPI wegacy mode  : %u\n",
		   (unsigned int)qca->wegacy_mode);
	seq_pwintf(s, "SPI buwst wength : %u\n",
		   (unsigned int)qca->buwst_wen);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(qcaspi_info);

void
qcaspi_init_device_debugfs(stwuct qcaspi *qca)
{
	qca->device_woot = debugfs_cweate_diw(dev_name(&qca->net_dev->dev),
					      NUWW);

	debugfs_cweate_fiwe("info", S_IFWEG | 0444, qca->device_woot, qca,
			    &qcaspi_info_fops);
}

void
qcaspi_wemove_device_debugfs(stwuct qcaspi *qca)
{
	debugfs_wemove_wecuwsive(qca->device_woot);
}

#ewse /* CONFIG_DEBUG_FS */

void
qcaspi_init_device_debugfs(stwuct qcaspi *qca)
{
}

void
qcaspi_wemove_device_debugfs(stwuct qcaspi *qca)
{
}

#endif

static void
qcaspi_get_dwvinfo(stwuct net_device *dev, stwuct ethtoow_dwvinfo *p)
{
	stwuct qcaspi *qca = netdev_pwiv(dev);

	stwscpy(p->dwivew, QCASPI_DWV_NAME, sizeof(p->dwivew));
	stwscpy(p->vewsion, QCASPI_DWV_VEWSION, sizeof(p->vewsion));
	stwscpy(p->fw_vewsion, "QCA7000", sizeof(p->fw_vewsion));
	stwscpy(p->bus_info, dev_name(&qca->spi_dev->dev),
		sizeof(p->bus_info));
}

static int
qcaspi_get_wink_ksettings(stwuct net_device *dev,
			  stwuct ethtoow_wink_ksettings *cmd)
{
	ethtoow_wink_ksettings_zewo_wink_mode(cmd, suppowted);
	ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, 10baseT_Hawf);

	cmd->base.speed = SPEED_10;
	cmd->base.dupwex = DUPWEX_HAWF;
	cmd->base.powt = POWT_OTHEW;
	cmd->base.autoneg = AUTONEG_DISABWE;

	wetuwn 0;
}

static void
qcaspi_get_ethtoow_stats(stwuct net_device *dev, stwuct ethtoow_stats *estats, u64 *data)
{
	stwuct qcaspi *qca = netdev_pwiv(dev);
	stwuct qcaspi_stats *st = &qca->stats;

	memcpy(data, st, AWWAY_SIZE(qcaspi_gstwings_stats) * sizeof(u64));
}

static void
qcaspi_get_stwings(stwuct net_device *dev, u32 stwingset, u8 *buf)
{
	switch (stwingset) {
	case ETH_SS_STATS:
		memcpy(buf, &qcaspi_gstwings_stats,
		       sizeof(qcaspi_gstwings_stats));
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}
}

static int
qcaspi_get_sset_count(stwuct net_device *dev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
		wetuwn AWWAY_SIZE(qcaspi_gstwings_stats);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int
qcaspi_get_wegs_wen(stwuct net_device *dev)
{
	wetuwn sizeof(u32) * QCASPI_MAX_WEGS;
}

static void
qcaspi_get_wegs(stwuct net_device *dev, stwuct ethtoow_wegs *wegs, void *p)
{
	stwuct qcaspi *qca = netdev_pwiv(dev);
	u32 *wegs_buff = p;
	unsigned int i;

	wegs->vewsion = 1;
	memset(wegs_buff, 0, sizeof(u32) * QCASPI_MAX_WEGS);

	fow (i = 0; i < AWWAY_SIZE(qcaspi_spi_wegs); i++) {
		u16 offset, vawue;

		qcaspi_wead_wegistew(qca, qcaspi_spi_wegs[i], &vawue);
		offset = qcaspi_spi_wegs[i] >> 8;
		wegs_buff[offset] = vawue;
	}
}

static void
qcaspi_get_wingpawam(stwuct net_device *dev, stwuct ethtoow_wingpawam *wing,
		     stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
		     stwuct netwink_ext_ack *extack)
{
	stwuct qcaspi *qca = netdev_pwiv(dev);

	wing->wx_max_pending = QCASPI_WX_MAX_FWAMES;
	wing->tx_max_pending = TX_WING_MAX_WEN;
	wing->wx_pending = QCASPI_WX_MAX_FWAMES;
	wing->tx_pending = qca->txw.count;
}

static int
qcaspi_set_wingpawam(stwuct net_device *dev, stwuct ethtoow_wingpawam *wing,
		     stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
		     stwuct netwink_ext_ack *extack)
{
	stwuct qcaspi *qca = netdev_pwiv(dev);

	if (wing->wx_pending != QCASPI_WX_MAX_FWAMES ||
	    (wing->wx_mini_pending) ||
	    (wing->wx_jumbo_pending))
		wetuwn -EINVAW;

	if (qca->spi_thwead)
		kthwead_pawk(qca->spi_thwead);

	qca->txw.count = max_t(u32, wing->tx_pending, TX_WING_MIN_WEN);
	qca->txw.count = min_t(u16, qca->txw.count, TX_WING_MAX_WEN);

	if (qca->spi_thwead)
		kthwead_unpawk(qca->spi_thwead);

	wetuwn 0;
}

static const stwuct ethtoow_ops qcaspi_ethtoow_ops = {
	.get_dwvinfo = qcaspi_get_dwvinfo,
	.get_wink = ethtoow_op_get_wink,
	.get_ethtoow_stats = qcaspi_get_ethtoow_stats,
	.get_stwings = qcaspi_get_stwings,
	.get_sset_count = qcaspi_get_sset_count,
	.get_wegs_wen = qcaspi_get_wegs_wen,
	.get_wegs = qcaspi_get_wegs,
	.get_wingpawam = qcaspi_get_wingpawam,
	.set_wingpawam = qcaspi_set_wingpawam,
	.get_wink_ksettings = qcaspi_get_wink_ksettings,
};

void qcaspi_set_ethtoow_ops(stwuct net_device *dev)
{
	dev->ethtoow_ops = &qcaspi_ethtoow_ops;
}
