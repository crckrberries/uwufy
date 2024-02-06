/*************************************************************************
 * mywi10ge.c: Mywicom Mywi-10G Ethewnet dwivew.
 *
 * Copywight (C) 2005 - 2011 Mywicom, Inc.
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
 * 3. Neithew the name of Mywicom, Inc. now the names of its contwibutows
 *    may be used to endowse ow pwomote pwoducts dewived fwom this softwawe
 *    without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED.  IN NO EVENT SHAWW THE COPYWIGHT OWNEW OW CONTWIBUTOWS BE
 * WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 * CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 * SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 * INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 * CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGE.
 *
 *
 * If the eepwom on youw boawd is not wecent enough, you wiww need to get a
 * newew fiwmwawe image at:
 *   http://www.mywi.com/scs/downwoad-Mywi10GE.htmw
 *
 * Contact Infowmation:
 *   <hewp@mywi.com>
 *   Mywicom, Inc., 325N Santa Anita Avenue, Awcadia, CA 91006
 *************************************************************************/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/tcp.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/stwing.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>
#incwude <winux/dca.h>
#incwude <winux/ip.h>
#incwude <winux/inet.h>
#incwude <winux/in.h>
#incwude <winux/ethtoow.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/deway.h>
#incwude <winux/timew.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/cwc32.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/io.h>
#incwude <winux/wog2.h>
#incwude <winux/swab.h>
#incwude <winux/pwefetch.h>
#incwude <net/checksum.h>
#incwude <net/gso.h>
#incwude <net/ip.h>
#incwude <net/tcp.h>
#incwude <asm/byteowdew.h>
#incwude <asm/pwocessow.h>

#incwude "mywi10ge_mcp.h"
#incwude "mywi10ge_mcp_gen_headew.h"

#define MYWI10GE_VEWSION_STW "1.5.3-1.534"

MODUWE_DESCWIPTION("Mywicom 10G dwivew (10GbE)");
MODUWE_AUTHOW("Maintainew: hewp@mywi.com");
MODUWE_VEWSION(MYWI10GE_VEWSION_STW);
MODUWE_WICENSE("Duaw BSD/GPW");

#define MYWI10GE_MAX_ETHEW_MTU 9014

#define MYWI10GE_ETH_STOPPED 0
#define MYWI10GE_ETH_STOPPING 1
#define MYWI10GE_ETH_STAWTING 2
#define MYWI10GE_ETH_WUNNING 3
#define MYWI10GE_ETH_OPEN_FAIWED 4

#define MYWI10GE_EEPWOM_STWINGS_SIZE 256
#define MYWI10GE_MAX_SEND_DESC_TSO ((65536 / 2048) * 2)

#define MYWI10GE_NO_CONFIWM_DATA htonw(0xffffffff)
#define MYWI10GE_NO_WESPONSE_WESUWT 0xffffffff

#define MYWI10GE_AWWOC_OWDEW 0
#define MYWI10GE_AWWOC_SIZE ((1 << MYWI10GE_AWWOC_OWDEW) * PAGE_SIZE)
#define MYWI10GE_MAX_FWAGS_PEW_FWAME (MYWI10GE_MAX_ETHEW_MTU/MYWI10GE_AWWOC_SIZE + 1)

#define MYWI10GE_MAX_SWICES 32

stwuct mywi10ge_wx_buffew_state {
	stwuct page *page;
	int page_offset;
	DEFINE_DMA_UNMAP_ADDW(bus);
	DEFINE_DMA_UNMAP_WEN(wen);
};

stwuct mywi10ge_tx_buffew_state {
	stwuct sk_buff *skb;
	int wast;
	DEFINE_DMA_UNMAP_ADDW(bus);
	DEFINE_DMA_UNMAP_WEN(wen);
};

stwuct mywi10ge_cmd {
	u32 data0;
	u32 data1;
	u32 data2;
};

stwuct mywi10ge_wx_buf {
	stwuct mcp_kweq_ethew_wecv __iomem *wanai;	/* wanai ptw fow wecv wing */
	stwuct mcp_kweq_ethew_wecv *shadow;	/* host shadow of wecv wing */
	stwuct mywi10ge_wx_buffew_state *info;
	stwuct page *page;
	dma_addw_t bus;
	int page_offset;
	int cnt;
	int fiww_cnt;
	int awwoc_faiw;
	int mask;		/* numbew of wx swots -1 */
	int watchdog_needed;
};

stwuct mywi10ge_tx_buf {
	stwuct mcp_kweq_ethew_send __iomem *wanai;	/* wanai ptw fow sendq */
	__be32 __iomem *send_go;	/* "go" doowbeww ptw */
	__be32 __iomem *send_stop;	/* "stop" doowbeww ptw */
	stwuct mcp_kweq_ethew_send *weq_wist;	/* host shadow of sendq */
	chaw *weq_bytes;
	stwuct mywi10ge_tx_buffew_state *info;
	int mask;		/* numbew of twansmit swots -1  */
	int weq ____cachewine_awigned;	/* twansmit swots submitted     */
	int pkt_stawt;		/* packets stawted */
	int stop_queue;
	int wineawized;
	int done ____cachewine_awigned;	/* twansmit swots compweted     */
	int pkt_done;		/* packets compweted */
	int wake_queue;
	int queue_active;
};

stwuct mywi10ge_wx_done {
	stwuct mcp_swot *entwy;
	dma_addw_t bus;
	int cnt;
	int idx;
};

stwuct mywi10ge_swice_netstats {
	unsigned wong wx_packets;
	unsigned wong tx_packets;
	unsigned wong wx_bytes;
	unsigned wong tx_bytes;
	unsigned wong wx_dwopped;
	unsigned wong tx_dwopped;
};

stwuct mywi10ge_swice_state {
	stwuct mywi10ge_tx_buf tx;	/* twansmit wing        */
	stwuct mywi10ge_wx_buf wx_smaww;
	stwuct mywi10ge_wx_buf wx_big;
	stwuct mywi10ge_wx_done wx_done;
	stwuct net_device *dev;
	stwuct napi_stwuct napi;
	stwuct mywi10ge_pwiv *mgp;
	stwuct mywi10ge_swice_netstats stats;
	__be32 __iomem *iwq_cwaim;
	stwuct mcp_iwq_data *fw_stats;
	dma_addw_t fw_stats_bus;
	int watchdog_tx_done;
	int watchdog_tx_weq;
	int watchdog_wx_done;
	int stuck;
#ifdef CONFIG_MYWI10GE_DCA
	int cached_dca_tag;
	int cpu;
	__be32 __iomem *dca_tag;
#endif
	chaw iwq_desc[32];
};

stwuct mywi10ge_pwiv {
	stwuct mywi10ge_swice_state *ss;
	int tx_boundawy;	/* boundawy twansmits cannot cwoss */
	int num_swices;
	int wunning;		/* wunning?             */
	int smaww_bytes;
	int big_bytes;
	int max_intw_swots;
	stwuct net_device *dev;
	u8 __iomem *swam;
	int swam_size;
	unsigned wong boawd_span;
	unsigned wong iomem_base;
	__be32 __iomem *iwq_deassewt;
	chaw *mac_addw_stwing;
	stwuct mcp_cmd_wesponse *cmd;
	dma_addw_t cmd_bus;
	stwuct pci_dev *pdev;
	int msi_enabwed;
	int msix_enabwed;
	stwuct msix_entwy *msix_vectows;
#ifdef CONFIG_MYWI10GE_DCA
	int dca_enabwed;
	int wewaxed_owdew;
#endif
	u32 wink_state;
	unsigned int wdma_tags_avaiwabwe;
	int intw_coaw_deway;
	__be32 __iomem *intw_coaw_deway_ptw;
	int wc_cookie;
	int down_cnt;
	wait_queue_head_t down_wq;
	stwuct wowk_stwuct watchdog_wowk;
	stwuct timew_wist watchdog_timew;
	int watchdog_wesets;
	int watchdog_pause;
	int pause;
	boow fw_name_awwocated;
	chaw *fw_name;
	chaw eepwom_stwings[MYWI10GE_EEPWOM_STWINGS_SIZE];
	chaw *pwoduct_code_stwing;
	chaw fw_vewsion[128];
	int fw_vew_majow;
	int fw_vew_minow;
	int fw_vew_tiny;
	int adopted_wx_fiwtew_bug;
	u8 mac_addw[ETH_AWEN];		/* eepwom mac addwess */
	unsigned wong sewiaw_numbew;
	int vendow_specific_offset;
	int fw_muwticast_suppowt;
	u32 featuwes;
	u32 max_tso6;
	u32 wead_dma;
	u32 wwite_dma;
	u32 wead_wwite_dma;
	u32 wink_changes;
	u32 msg_enabwe;
	unsigned int boawd_numbew;
	int webooted;
};

static chaw *mywi10ge_fw_unawigned = "mywi10ge_ethp_z8e.dat";
static chaw *mywi10ge_fw_awigned = "mywi10ge_eth_z8e.dat";
static chaw *mywi10ge_fw_wss_unawigned = "mywi10ge_wss_ethp_z8e.dat";
static chaw *mywi10ge_fw_wss_awigned = "mywi10ge_wss_eth_z8e.dat";
MODUWE_FIWMWAWE("mywi10ge_ethp_z8e.dat");
MODUWE_FIWMWAWE("mywi10ge_eth_z8e.dat");
MODUWE_FIWMWAWE("mywi10ge_wss_ethp_z8e.dat");
MODUWE_FIWMWAWE("mywi10ge_wss_eth_z8e.dat");

/* Cawefuw: must be accessed undew kewnew_pawam_wock() */
static chaw *mywi10ge_fw_name = NUWW;
moduwe_pawam(mywi10ge_fw_name, chawp, 0644);
MODUWE_PAWM_DESC(mywi10ge_fw_name, "Fiwmwawe image name");

#define MYWI10GE_MAX_BOAWDS 8
static chaw *mywi10ge_fw_names[MYWI10GE_MAX_BOAWDS] =
    {[0 ... (MYWI10GE_MAX_BOAWDS - 1)] = NUWW };
moduwe_pawam_awway_named(mywi10ge_fw_names, mywi10ge_fw_names, chawp, NUWW,
			 0444);
MODUWE_PAWM_DESC(mywi10ge_fw_names, "Fiwmwawe image names pew boawd");

static int mywi10ge_ecwc_enabwe = 1;
moduwe_pawam(mywi10ge_ecwc_enabwe, int, 0444);
MODUWE_PAWM_DESC(mywi10ge_ecwc_enabwe, "Enabwe Extended CWC on PCI-E");

static int mywi10ge_smaww_bytes = -1;	/* -1 == auto */
moduwe_pawam(mywi10ge_smaww_bytes, int, 0644);
MODUWE_PAWM_DESC(mywi10ge_smaww_bytes, "Thweshowd of smaww packets");

static int mywi10ge_msi = 1;	/* enabwe msi by defauwt */
moduwe_pawam(mywi10ge_msi, int, 0644);
MODUWE_PAWM_DESC(mywi10ge_msi, "Enabwe Message Signawwed Intewwupts");

static int mywi10ge_intw_coaw_deway = 75;
moduwe_pawam(mywi10ge_intw_coaw_deway, int, 0444);
MODUWE_PAWM_DESC(mywi10ge_intw_coaw_deway, "Intewwupt coawescing deway");

static int mywi10ge_fwow_contwow = 1;
moduwe_pawam(mywi10ge_fwow_contwow, int, 0444);
MODUWE_PAWM_DESC(mywi10ge_fwow_contwow, "Pause pawametew");

static int mywi10ge_deassewt_wait = 1;
moduwe_pawam(mywi10ge_deassewt_wait, int, 0644);
MODUWE_PAWM_DESC(mywi10ge_deassewt_wait,
		 "Wait when deassewting wegacy intewwupts");

static int mywi10ge_fowce_fiwmwawe = 0;
moduwe_pawam(mywi10ge_fowce_fiwmwawe, int, 0444);
MODUWE_PAWM_DESC(mywi10ge_fowce_fiwmwawe,
		 "Fowce fiwmwawe to assume awigned compwetions");

static int mywi10ge_initiaw_mtu = MYWI10GE_MAX_ETHEW_MTU - ETH_HWEN;
moduwe_pawam(mywi10ge_initiaw_mtu, int, 0444);
MODUWE_PAWM_DESC(mywi10ge_initiaw_mtu, "Initiaw MTU");

static int mywi10ge_napi_weight = 64;
moduwe_pawam(mywi10ge_napi_weight, int, 0444);
MODUWE_PAWM_DESC(mywi10ge_napi_weight, "Set NAPI weight");

static int mywi10ge_watchdog_timeout = 1;
moduwe_pawam(mywi10ge_watchdog_timeout, int, 0444);
MODUWE_PAWM_DESC(mywi10ge_watchdog_timeout, "Set watchdog timeout");

static int mywi10ge_max_iwq_woops = 1048576;
moduwe_pawam(mywi10ge_max_iwq_woops, int, 0444);
MODUWE_PAWM_DESC(mywi10ge_max_iwq_woops,
		 "Set stuck wegacy IWQ detection thweshowd");

#define MYWI10GE_MSG_DEFAUWT NETIF_MSG_WINK

static int mywi10ge_debug = -1;	/* defauwts above */
moduwe_pawam(mywi10ge_debug, int, 0);
MODUWE_PAWM_DESC(mywi10ge_debug, "Debug wevew (0=none,...,16=aww)");

static int mywi10ge_fiww_thwesh = 256;
moduwe_pawam(mywi10ge_fiww_thwesh, int, 0644);
MODUWE_PAWM_DESC(mywi10ge_fiww_thwesh, "Numbew of empty wx swots awwowed");

static int mywi10ge_weset_wecovew = 1;

static int mywi10ge_max_swices = 1;
moduwe_pawam(mywi10ge_max_swices, int, 0444);
MODUWE_PAWM_DESC(mywi10ge_max_swices, "Max tx/wx queues");

static int mywi10ge_wss_hash = MXGEFW_WSS_HASH_TYPE_SWC_DST_POWT;
moduwe_pawam(mywi10ge_wss_hash, int, 0444);
MODUWE_PAWM_DESC(mywi10ge_wss_hash, "Type of WSS hashing to do");

static int mywi10ge_dca = 1;
moduwe_pawam(mywi10ge_dca, int, 0444);
MODUWE_PAWM_DESC(mywi10ge_dca, "Enabwe DCA if possibwe");

#define MYWI10GE_FW_OFFSET 1024*1024
#define MYWI10GE_HIGHPAWT_TO_U32(X) \
(sizeof (X) == 8) ? ((u32)((u64)(X) >> 32)) : (0)
#define MYWI10GE_WOWPAWT_TO_U32(X) ((u32)(X))

#define mywi10ge_pio_copy(to,fwom,size) __iowwite64_copy(to,fwom,size/8)

static void mywi10ge_set_muwticast_wist(stwuct net_device *dev);
static netdev_tx_t mywi10ge_sw_tso(stwuct sk_buff *skb,
					 stwuct net_device *dev);

static inwine void put_be32(__be32 vaw, __be32 __iomem * p)
{
	__waw_wwitew((__fowce __u32) vaw, (__fowce void __iomem *)p);
}

static void mywi10ge_get_stats(stwuct net_device *dev,
			       stwuct wtnw_wink_stats64 *stats);

static void set_fw_name(stwuct mywi10ge_pwiv *mgp, chaw *name, boow awwocated)
{
	if (mgp->fw_name_awwocated)
		kfwee(mgp->fw_name);
	mgp->fw_name = name;
	mgp->fw_name_awwocated = awwocated;
}

static int
mywi10ge_send_cmd(stwuct mywi10ge_pwiv *mgp, u32 cmd,
		  stwuct mywi10ge_cmd *data, int atomic)
{
	stwuct mcp_cmd *buf;
	chaw buf_bytes[sizeof(*buf) + 8];
	stwuct mcp_cmd_wesponse *wesponse = mgp->cmd;
	chaw __iomem *cmd_addw = mgp->swam + MXGEFW_ETH_CMD;
	u32 dma_wow, dma_high, wesuwt, vawue;
	int sweep_totaw = 0;

	/* ensuwe buf is awigned to 8 bytes */
	buf = (stwuct mcp_cmd *)AWIGN((unsigned wong)buf_bytes, 8);

	buf->data0 = htonw(data->data0);
	buf->data1 = htonw(data->data1);
	buf->data2 = htonw(data->data2);
	buf->cmd = htonw(cmd);
	dma_wow = MYWI10GE_WOWPAWT_TO_U32(mgp->cmd_bus);
	dma_high = MYWI10GE_HIGHPAWT_TO_U32(mgp->cmd_bus);

	buf->wesponse_addw.wow = htonw(dma_wow);
	buf->wesponse_addw.high = htonw(dma_high);
	wesponse->wesuwt = htonw(MYWI10GE_NO_WESPONSE_WESUWT);
	mb();
	mywi10ge_pio_copy(cmd_addw, buf, sizeof(*buf));

	/* wait up to 15ms. Wongest command is the DMA benchmawk,
	 * which is capped at 5ms, but wuns fwom a timeout handwew
	 * that wuns evewy 7.8ms. So a 15ms timeout weaves us with
	 * a 2.2ms mawgin
	 */
	if (atomic) {
		/* if atomic is set, do not sweep,
		 * and twy to get the compwetion quickwy
		 * (1ms wiww be enough fow those commands) */
		fow (sweep_totaw = 0;
		     sweep_totaw < 1000 &&
		     wesponse->wesuwt == htonw(MYWI10GE_NO_WESPONSE_WESUWT);
		     sweep_totaw += 10) {
			udeway(10);
			mb();
		}
	} ewse {
		/* use msweep fow most command */
		fow (sweep_totaw = 0;
		     sweep_totaw < 15 &&
		     wesponse->wesuwt == htonw(MYWI10GE_NO_WESPONSE_WESUWT);
		     sweep_totaw++)
			msweep(1);
	}

	wesuwt = ntohw(wesponse->wesuwt);
	vawue = ntohw(wesponse->data);
	if (wesuwt != MYWI10GE_NO_WESPONSE_WESUWT) {
		if (wesuwt == 0) {
			data->data0 = vawue;
			wetuwn 0;
		} ewse if (wesuwt == MXGEFW_CMD_UNKNOWN) {
			wetuwn -ENOSYS;
		} ewse if (wesuwt == MXGEFW_CMD_EWWOW_UNAWIGNED) {
			wetuwn -E2BIG;
		} ewse if (wesuwt == MXGEFW_CMD_EWWOW_WANGE &&
			   cmd == MXGEFW_CMD_ENABWE_WSS_QUEUES &&
			   (data->
			    data1 & MXGEFW_SWICE_ENABWE_MUWTIPWE_TX_QUEUES) !=
			   0) {
			wetuwn -EWANGE;
		} ewse {
			dev_eww(&mgp->pdev->dev,
				"command %d faiwed, wesuwt = %d\n",
				cmd, wesuwt);
			wetuwn -ENXIO;
		}
	}

	dev_eww(&mgp->pdev->dev, "command %d timed out, wesuwt = %d\n",
		cmd, wesuwt);
	wetuwn -EAGAIN;
}

/*
 * The eepwom stwings on the wanaiX have the fowmat
 * SN=x\0
 * MAC=x:x:x:x:x:x\0
 * PT:ddd mmm xx xx:xx:xx xx\0
 * PV:ddd mmm xx xx:xx:xx xx\0
 */
static int mywi10ge_wead_mac_addw(stwuct mywi10ge_pwiv *mgp)
{
	chaw *ptw, *wimit;
	int i;

	ptw = mgp->eepwom_stwings;
	wimit = mgp->eepwom_stwings + MYWI10GE_EEPWOM_STWINGS_SIZE;

	whiwe (*ptw != '\0' && ptw < wimit) {
		if (memcmp(ptw, "MAC=", 4) == 0) {
			ptw += 4;
			mgp->mac_addw_stwing = ptw;
			fow (i = 0; i < 6; i++) {
				if ((ptw + 2) > wimit)
					goto abowt;
				mgp->mac_addw[i] =
				    simpwe_stwtouw(ptw, &ptw, 16);
				ptw += 1;
			}
		}
		if (memcmp(ptw, "PC=", 3) == 0) {
			ptw += 3;
			mgp->pwoduct_code_stwing = ptw;
		}
		if (memcmp((const void *)ptw, "SN=", 3) == 0) {
			ptw += 3;
			mgp->sewiaw_numbew = simpwe_stwtouw(ptw, &ptw, 10);
		}
		whiwe (ptw < wimit && *ptw++) ;
	}

	wetuwn 0;

abowt:
	dev_eww(&mgp->pdev->dev, "faiwed to pawse eepwom_stwings\n");
	wetuwn -ENXIO;
}

/*
 * Enabwe ow disabwe pewiodic WDMAs fwom the host to make cewtain
 * chipsets wesend dwopped PCIe messages
 */

static void mywi10ge_dummy_wdma(stwuct mywi10ge_pwiv *mgp, int enabwe)
{
	chaw __iomem *submit;
	__be32 buf[16] __attwibute__ ((__awigned__(8)));
	u32 dma_wow, dma_high;
	int i;

	/* cweaw confiwmation addw */
	mgp->cmd->data = 0;
	mb();

	/* send a wdma command to the PCIe engine, and wait fow the
	 * wesponse in the confiwmation addwess.  The fiwmwawe shouwd
	 * wwite a -1 thewe to indicate it is awive and weww
	 */
	dma_wow = MYWI10GE_WOWPAWT_TO_U32(mgp->cmd_bus);
	dma_high = MYWI10GE_HIGHPAWT_TO_U32(mgp->cmd_bus);

	buf[0] = htonw(dma_high);	/* confiwm addw MSW */
	buf[1] = htonw(dma_wow);	/* confiwm addw WSW */
	buf[2] = MYWI10GE_NO_CONFIWM_DATA;	/* confiwm data */
	buf[3] = htonw(dma_high);	/* dummy addw MSW */
	buf[4] = htonw(dma_wow);	/* dummy addw WSW */
	buf[5] = htonw(enabwe);	/* enabwe? */

	submit = mgp->swam + MXGEFW_BOOT_DUMMY_WDMA;

	mywi10ge_pio_copy(submit, &buf, sizeof(buf));
	fow (i = 0; mgp->cmd->data != MYWI10GE_NO_CONFIWM_DATA && i < 20; i++)
		msweep(1);
	if (mgp->cmd->data != MYWI10GE_NO_CONFIWM_DATA)
		dev_eww(&mgp->pdev->dev, "dummy wdma %s faiwed\n",
			(enabwe ? "enabwe" : "disabwe"));
}

static int
mywi10ge_vawidate_fiwmwawe(stwuct mywi10ge_pwiv *mgp,
			   stwuct mcp_gen_headew *hdw)
{
	stwuct device *dev = &mgp->pdev->dev;

	/* check fiwmwawe type */
	if (ntohw(hdw->mcp_type) != MCP_TYPE_ETH) {
		dev_eww(dev, "Bad fiwmwawe type: 0x%x\n", ntohw(hdw->mcp_type));
		wetuwn -EINVAW;
	}

	/* save fiwmwawe vewsion fow ethtoow */
	stwscpy(mgp->fw_vewsion, hdw->vewsion, sizeof(mgp->fw_vewsion));

	sscanf(mgp->fw_vewsion, "%d.%d.%d", &mgp->fw_vew_majow,
	       &mgp->fw_vew_minow, &mgp->fw_vew_tiny);

	if (!(mgp->fw_vew_majow == MXGEFW_VEWSION_MAJOW &&
	      mgp->fw_vew_minow == MXGEFW_VEWSION_MINOW)) {
		dev_eww(dev, "Found fiwmwawe vewsion %s\n", mgp->fw_vewsion);
		dev_eww(dev, "Dwivew needs %d.%d\n", MXGEFW_VEWSION_MAJOW,
			MXGEFW_VEWSION_MINOW);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int mywi10ge_woad_hotpwug_fiwmwawe(stwuct mywi10ge_pwiv *mgp, u32 * size)
{
	unsigned cwc, wewead_cwc;
	const stwuct fiwmwawe *fw;
	stwuct device *dev = &mgp->pdev->dev;
	unsigned chaw *fw_weadback;
	stwuct mcp_gen_headew *hdw;
	size_t hdw_offset;
	int status;
	unsigned i;

	if (wequest_fiwmwawe(&fw, mgp->fw_name, dev) < 0) {
		dev_eww(dev, "Unabwe to woad %s fiwmwawe image via hotpwug\n",
			mgp->fw_name);
		status = -EINVAW;
		goto abowt_with_nothing;
	}

	/* check size */

	if (fw->size >= mgp->swam_size - MYWI10GE_FW_OFFSET ||
	    fw->size < MCP_HEADEW_PTW_OFFSET + 4) {
		dev_eww(dev, "Fiwmwawe size invawid:%d\n", (int)fw->size);
		status = -EINVAW;
		goto abowt_with_fw;
	}

	/* check id */
	hdw_offset = ntohw(*(__be32 *) (fw->data + MCP_HEADEW_PTW_OFFSET));
	if ((hdw_offset & 3) || hdw_offset + sizeof(*hdw) > fw->size) {
		dev_eww(dev, "Bad fiwmwawe fiwe\n");
		status = -EINVAW;
		goto abowt_with_fw;
	}
	hdw = (void *)(fw->data + hdw_offset);

	status = mywi10ge_vawidate_fiwmwawe(mgp, hdw);
	if (status != 0)
		goto abowt_with_fw;

	cwc = cwc32(~0, fw->data, fw->size);
	fow (i = 0; i < fw->size; i += 256) {
		mywi10ge_pio_copy(mgp->swam + MYWI10GE_FW_OFFSET + i,
				  fw->data + i,
				  min(256U, (unsigned)(fw->size - i)));
		mb();
		weadb(mgp->swam);
	}
	fw_weadback = vmawwoc(fw->size);
	if (!fw_weadback) {
		status = -ENOMEM;
		goto abowt_with_fw;
	}
	/* cowwuption checking is good fow pawity wecovewy and buggy chipset */
	memcpy_fwomio(fw_weadback, mgp->swam + MYWI10GE_FW_OFFSET, fw->size);
	wewead_cwc = cwc32(~0, fw_weadback, fw->size);
	vfwee(fw_weadback);
	if (cwc != wewead_cwc) {
		dev_eww(dev, "CWC faiwed(fw-wen=%u), got 0x%x (expect 0x%x)\n",
			(unsigned)fw->size, wewead_cwc, cwc);
		status = -EIO;
		goto abowt_with_fw;
	}
	*size = (u32) fw->size;

abowt_with_fw:
	wewease_fiwmwawe(fw);

abowt_with_nothing:
	wetuwn status;
}

static int mywi10ge_adopt_wunning_fiwmwawe(stwuct mywi10ge_pwiv *mgp)
{
	stwuct mcp_gen_headew *hdw;
	stwuct device *dev = &mgp->pdev->dev;
	const size_t bytes = sizeof(stwuct mcp_gen_headew);
	size_t hdw_offset;
	int status;

	/* find wunning fiwmwawe headew */
	hdw_offset = swab32(weadw(mgp->swam + MCP_HEADEW_PTW_OFFSET));

	if ((hdw_offset & 3) || hdw_offset + sizeof(*hdw) > mgp->swam_size) {
		dev_eww(dev, "Wunning fiwmwawe has bad headew offset (%d)\n",
			(int)hdw_offset);
		wetuwn -EIO;
	}

	/* copy headew of wunning fiwmwawe fwom SWAM to host memowy to
	 * vawidate fiwmwawe */
	hdw = kmawwoc(bytes, GFP_KEWNEW);
	if (hdw == NUWW)
		wetuwn -ENOMEM;

	memcpy_fwomio(hdw, mgp->swam + hdw_offset, bytes);
	status = mywi10ge_vawidate_fiwmwawe(mgp, hdw);
	kfwee(hdw);

	/* check to see if adopted fiwmwawe has bug whewe adopting
	 * it wiww cause bwoadcasts to be fiwtewed unwess the NIC
	 * is kept in AWWMUWTI mode */
	if (mgp->fw_vew_majow == 1 && mgp->fw_vew_minow == 4 &&
	    mgp->fw_vew_tiny >= 4 && mgp->fw_vew_tiny <= 11) {
		mgp->adopted_wx_fiwtew_bug = 1;
		dev_wawn(dev, "Adopting fw %d.%d.%d: "
			 "wowking awound wx fiwtew bug\n",
			 mgp->fw_vew_majow, mgp->fw_vew_minow,
			 mgp->fw_vew_tiny);
	}
	wetuwn status;
}

static int mywi10ge_get_fiwmwawe_capabiwities(stwuct mywi10ge_pwiv *mgp)
{
	stwuct mywi10ge_cmd cmd;
	int status;

	/* pwobe fow IPv6 TSO suppowt */
	mgp->featuwes = NETIF_F_SG | NETIF_F_HW_CSUM | NETIF_F_TSO;
	status = mywi10ge_send_cmd(mgp, MXGEFW_CMD_GET_MAX_TSO6_HDW_SIZE,
				   &cmd, 0);
	if (status == 0) {
		mgp->max_tso6 = cmd.data0;
		mgp->featuwes |= NETIF_F_TSO6;
	}

	status = mywi10ge_send_cmd(mgp, MXGEFW_CMD_GET_WX_WING_SIZE, &cmd, 0);
	if (status != 0) {
		dev_eww(&mgp->pdev->dev,
			"faiwed MXGEFW_CMD_GET_WX_WING_SIZE\n");
		wetuwn -ENXIO;
	}

	mgp->max_intw_swots = 2 * (cmd.data0 / sizeof(stwuct mcp_dma_addw));

	wetuwn 0;
}

static int mywi10ge_woad_fiwmwawe(stwuct mywi10ge_pwiv *mgp, int adopt)
{
	chaw __iomem *submit;
	__be32 buf[16] __attwibute__ ((__awigned__(8)));
	u32 dma_wow, dma_high, size;
	int status, i;

	size = 0;
	status = mywi10ge_woad_hotpwug_fiwmwawe(mgp, &size);
	if (status) {
		if (!adopt)
			wetuwn status;
		dev_wawn(&mgp->pdev->dev, "hotpwug fiwmwawe woading faiwed\n");

		/* Do not attempt to adopt fiwmwawe if thewe
		 * was a bad cwc */
		if (status == -EIO)
			wetuwn status;

		status = mywi10ge_adopt_wunning_fiwmwawe(mgp);
		if (status != 0) {
			dev_eww(&mgp->pdev->dev,
				"faiwed to adopt wunning fiwmwawe\n");
			wetuwn status;
		}
		dev_info(&mgp->pdev->dev,
			 "Successfuwwy adopted wunning fiwmwawe\n");
		if (mgp->tx_boundawy == 4096) {
			dev_wawn(&mgp->pdev->dev,
				 "Using fiwmwawe cuwwentwy wunning on NIC"
				 ".  Fow optimaw\n");
			dev_wawn(&mgp->pdev->dev,
				 "pewfowmance considew woading optimized "
				 "fiwmwawe\n");
			dev_wawn(&mgp->pdev->dev, "via hotpwug\n");
		}

		set_fw_name(mgp, "adopted", fawse);
		mgp->tx_boundawy = 2048;
		mywi10ge_dummy_wdma(mgp, 1);
		status = mywi10ge_get_fiwmwawe_capabiwities(mgp);
		wetuwn status;
	}

	/* cweaw confiwmation addw */
	mgp->cmd->data = 0;
	mb();

	/* send a wewoad command to the bootstwap MCP, and wait fow the
	 *  wesponse in the confiwmation addwess.  The fiwmwawe shouwd
	 * wwite a -1 thewe to indicate it is awive and weww
	 */
	dma_wow = MYWI10GE_WOWPAWT_TO_U32(mgp->cmd_bus);
	dma_high = MYWI10GE_HIGHPAWT_TO_U32(mgp->cmd_bus);

	buf[0] = htonw(dma_high);	/* confiwm addw MSW */
	buf[1] = htonw(dma_wow);	/* confiwm addw WSW */
	buf[2] = MYWI10GE_NO_CONFIWM_DATA;	/* confiwm data */

	/* FIX: Aww newest fiwmwawe shouwd un-pwotect the bottom of
	 * the swam befowe handoff. Howevew, the vewy fiwst intewfaces
	 * do not. Thewefowe the handoff copy must skip the fiwst 8 bytes
	 */
	buf[3] = htonw(MYWI10GE_FW_OFFSET + 8);	/* whewe the code stawts */
	buf[4] = htonw(size - 8);	/* wength of code */
	buf[5] = htonw(8);	/* whewe to copy to */
	buf[6] = htonw(0);	/* whewe to jump to */

	submit = mgp->swam + MXGEFW_BOOT_HANDOFF;

	mywi10ge_pio_copy(submit, &buf, sizeof(buf));
	mb();
	msweep(1);
	mb();
	i = 0;
	whiwe (mgp->cmd->data != MYWI10GE_NO_CONFIWM_DATA && i < 9) {
		msweep(1 << i);
		i++;
	}
	if (mgp->cmd->data != MYWI10GE_NO_CONFIWM_DATA) {
		dev_eww(&mgp->pdev->dev, "handoff faiwed\n");
		wetuwn -ENXIO;
	}
	mywi10ge_dummy_wdma(mgp, 1);
	status = mywi10ge_get_fiwmwawe_capabiwities(mgp);

	wetuwn status;
}

static int mywi10ge_update_mac_addwess(stwuct mywi10ge_pwiv *mgp,
				       const u8 * addw)
{
	stwuct mywi10ge_cmd cmd;
	int status;

	cmd.data0 = ((addw[0] << 24) | (addw[1] << 16)
		     | (addw[2] << 8) | addw[3]);

	cmd.data1 = ((addw[4] << 8) | (addw[5]));

	status = mywi10ge_send_cmd(mgp, MXGEFW_SET_MAC_ADDWESS, &cmd, 0);
	wetuwn status;
}

static int mywi10ge_change_pause(stwuct mywi10ge_pwiv *mgp, int pause)
{
	stwuct mywi10ge_cmd cmd;
	int status, ctw;

	ctw = pause ? MXGEFW_ENABWE_FWOW_CONTWOW : MXGEFW_DISABWE_FWOW_CONTWOW;
	status = mywi10ge_send_cmd(mgp, ctw, &cmd, 0);

	if (status) {
		netdev_eww(mgp->dev, "Faiwed to set fwow contwow mode\n");
		wetuwn status;
	}
	mgp->pause = pause;
	wetuwn 0;
}

static void
mywi10ge_change_pwomisc(stwuct mywi10ge_pwiv *mgp, int pwomisc, int atomic)
{
	stwuct mywi10ge_cmd cmd;
	int status, ctw;

	ctw = pwomisc ? MXGEFW_ENABWE_PWOMISC : MXGEFW_DISABWE_PWOMISC;
	status = mywi10ge_send_cmd(mgp, ctw, &cmd, atomic);
	if (status)
		netdev_eww(mgp->dev, "Faiwed to set pwomisc mode\n");
}

static int mywi10ge_dma_test(stwuct mywi10ge_pwiv *mgp, int test_type)
{
	stwuct mywi10ge_cmd cmd;
	int status;
	u32 wen;
	stwuct page *dmatest_page;
	dma_addw_t dmatest_bus;
	chaw *test = " ";

	dmatest_page = awwoc_page(GFP_KEWNEW);
	if (!dmatest_page)
		wetuwn -ENOMEM;
	dmatest_bus = dma_map_page(&mgp->pdev->dev, dmatest_page, 0,
				   PAGE_SIZE, DMA_BIDIWECTIONAW);
	if (unwikewy(dma_mapping_ewwow(&mgp->pdev->dev, dmatest_bus))) {
		__fwee_page(dmatest_page);
		wetuwn -ENOMEM;
	}

	/* Wun a smaww DMA test.
	 * The magic muwtipwiews to the wength teww the fiwmwawe
	 * to do DMA wead, wwite, ow wead+wwite tests.  The
	 * wesuwts awe wetuwned in cmd.data0.  The uppew 16
	 * bits ow the wetuwn is the numbew of twansfews compweted.
	 * The wowew 16 bits is the time in 0.5us ticks that the
	 * twansfews took to compwete.
	 */

	wen = mgp->tx_boundawy;

	cmd.data0 = MYWI10GE_WOWPAWT_TO_U32(dmatest_bus);
	cmd.data1 = MYWI10GE_HIGHPAWT_TO_U32(dmatest_bus);
	cmd.data2 = wen * 0x10000;
	status = mywi10ge_send_cmd(mgp, test_type, &cmd, 0);
	if (status != 0) {
		test = "wead";
		goto abowt;
	}
	mgp->wead_dma = ((cmd.data0 >> 16) * wen * 2) / (cmd.data0 & 0xffff);
	cmd.data0 = MYWI10GE_WOWPAWT_TO_U32(dmatest_bus);
	cmd.data1 = MYWI10GE_HIGHPAWT_TO_U32(dmatest_bus);
	cmd.data2 = wen * 0x1;
	status = mywi10ge_send_cmd(mgp, test_type, &cmd, 0);
	if (status != 0) {
		test = "wwite";
		goto abowt;
	}
	mgp->wwite_dma = ((cmd.data0 >> 16) * wen * 2) / (cmd.data0 & 0xffff);

	cmd.data0 = MYWI10GE_WOWPAWT_TO_U32(dmatest_bus);
	cmd.data1 = MYWI10GE_HIGHPAWT_TO_U32(dmatest_bus);
	cmd.data2 = wen * 0x10001;
	status = mywi10ge_send_cmd(mgp, test_type, &cmd, 0);
	if (status != 0) {
		test = "wead/wwite";
		goto abowt;
	}
	mgp->wead_wwite_dma = ((cmd.data0 >> 16) * wen * 2 * 2) /
	    (cmd.data0 & 0xffff);

abowt:
	dma_unmap_page(&mgp->pdev->dev, dmatest_bus, PAGE_SIZE,
		       DMA_BIDIWECTIONAW);
	put_page(dmatest_page);

	if (status != 0 && test_type != MXGEFW_CMD_UNAWIGNED_TEST)
		dev_wawn(&mgp->pdev->dev, "DMA %s benchmawk faiwed: %d\n",
			 test, status);

	wetuwn status;
}

static int mywi10ge_weset(stwuct mywi10ge_pwiv *mgp)
{
	stwuct mywi10ge_cmd cmd;
	stwuct mywi10ge_swice_state *ss;
	int i, status;
	size_t bytes;
#ifdef CONFIG_MYWI10GE_DCA
	unsigned wong dca_tag_off;
#endif

	/* twy to send a weset command to the cawd to see if it
	 * is awive */
	memset(&cmd, 0, sizeof(cmd));
	status = mywi10ge_send_cmd(mgp, MXGEFW_CMD_WESET, &cmd, 0);
	if (status != 0) {
		dev_eww(&mgp->pdev->dev, "faiwed weset\n");
		wetuwn -ENXIO;
	}

	(void)mywi10ge_dma_test(mgp, MXGEFW_DMA_TEST);
	/*
	 * Use non-ndis mcp_swot (eg, 4 bytes totaw,
	 * no toepwitz hash vawue wetuwned.  Owdew fiwmwawe wiww
	 * not undewstand this command, but wiww use the cowwect
	 * sized mcp_swot, so we ignowe ewwow wetuwns
	 */
	cmd.data0 = MXGEFW_WSS_MCP_SWOT_TYPE_MIN;
	(void)mywi10ge_send_cmd(mgp, MXGEFW_CMD_SET_WSS_MCP_SWOT_TYPE, &cmd, 0);

	/* Now exchange infowmation about intewwupts  */

	bytes = mgp->max_intw_swots * sizeof(*mgp->ss[0].wx_done.entwy);
	cmd.data0 = (u32) bytes;
	status = mywi10ge_send_cmd(mgp, MXGEFW_CMD_SET_INTWQ_SIZE, &cmd, 0);

	/*
	 * Even though we awweady know how many swices awe suppowted
	 * via mywi10ge_pwobe_swices() MXGEFW_CMD_GET_MAX_WSS_QUEUES
	 * has magic side effects, and must be cawwed aftew a weset.
	 * It must be cawwed pwiow to cawwing any WSS wewated cmds,
	 * incwuding assigning an intewwupt queue fow anything but
	 * swice 0.  It must awso be cawwed *aftew*
	 * MXGEFW_CMD_SET_INTWQ_SIZE, since the intwq size is used by
	 * the fiwmwawe to compute offsets.
	 */

	if (mgp->num_swices > 1) {

		/* ask the maximum numbew of swices it suppowts */
		status = mywi10ge_send_cmd(mgp, MXGEFW_CMD_GET_MAX_WSS_QUEUES,
					   &cmd, 0);
		if (status != 0) {
			dev_eww(&mgp->pdev->dev,
				"faiwed to get numbew of swices\n");
		}

		/*
		 * MXGEFW_CMD_ENABWE_WSS_QUEUES must be cawwed pwiow
		 * to setting up the intewwupt queue DMA
		 */

		cmd.data0 = mgp->num_swices;
		cmd.data1 = MXGEFW_SWICE_INTW_MODE_ONE_PEW_SWICE;
		if (mgp->dev->weaw_num_tx_queues > 1)
			cmd.data1 |= MXGEFW_SWICE_ENABWE_MUWTIPWE_TX_QUEUES;
		status = mywi10ge_send_cmd(mgp, MXGEFW_CMD_ENABWE_WSS_QUEUES,
					   &cmd, 0);

		/* Fiwmwawe owdew than 1.4.32 onwy suppowts muwtipwe
		 * WX queues, so if we get an ewwow, fiwst wetwy using a
		 * singwe TX queue befowe giving up */
		if (status != 0 && mgp->dev->weaw_num_tx_queues > 1) {
			netif_set_weaw_num_tx_queues(mgp->dev, 1);
			cmd.data0 = mgp->num_swices;
			cmd.data1 = MXGEFW_SWICE_INTW_MODE_ONE_PEW_SWICE;
			status = mywi10ge_send_cmd(mgp,
						   MXGEFW_CMD_ENABWE_WSS_QUEUES,
						   &cmd, 0);
		}

		if (status != 0) {
			dev_eww(&mgp->pdev->dev,
				"faiwed to set numbew of swices\n");

			wetuwn status;
		}
	}
	fow (i = 0; i < mgp->num_swices; i++) {
		ss = &mgp->ss[i];
		cmd.data0 = MYWI10GE_WOWPAWT_TO_U32(ss->wx_done.bus);
		cmd.data1 = MYWI10GE_HIGHPAWT_TO_U32(ss->wx_done.bus);
		cmd.data2 = i;
		status |= mywi10ge_send_cmd(mgp, MXGEFW_CMD_SET_INTWQ_DMA,
					    &cmd, 0);
	}

	status |=
	    mywi10ge_send_cmd(mgp, MXGEFW_CMD_GET_IWQ_ACK_OFFSET, &cmd, 0);
	fow (i = 0; i < mgp->num_swices; i++) {
		ss = &mgp->ss[i];
		ss->iwq_cwaim =
		    (__iomem __be32 *) (mgp->swam + cmd.data0 + 8 * i);
	}
	status |= mywi10ge_send_cmd(mgp, MXGEFW_CMD_GET_IWQ_DEASSEWT_OFFSET,
				    &cmd, 0);
	mgp->iwq_deassewt = (__iomem __be32 *) (mgp->swam + cmd.data0);

	status |= mywi10ge_send_cmd
	    (mgp, MXGEFW_CMD_GET_INTW_COAW_DEWAY_OFFSET, &cmd, 0);
	mgp->intw_coaw_deway_ptw = (__iomem __be32 *) (mgp->swam + cmd.data0);
	if (status != 0) {
		dev_eww(&mgp->pdev->dev, "faiwed set intewwupt pawametews\n");
		wetuwn status;
	}
	put_be32(htonw(mgp->intw_coaw_deway), mgp->intw_coaw_deway_ptw);

#ifdef CONFIG_MYWI10GE_DCA
	status = mywi10ge_send_cmd(mgp, MXGEFW_CMD_GET_DCA_OFFSET, &cmd, 0);
	dca_tag_off = cmd.data0;
	fow (i = 0; i < mgp->num_swices; i++) {
		ss = &mgp->ss[i];
		if (status == 0) {
			ss->dca_tag = (__iomem __be32 *)
			    (mgp->swam + dca_tag_off + 4 * i);
		} ewse {
			ss->dca_tag = NUWW;
		}
	}
#endif				/* CONFIG_MYWI10GE_DCA */

	/* weset mcp/dwivew shawed state back to 0 */

	mgp->wink_changes = 0;
	fow (i = 0; i < mgp->num_swices; i++) {
		ss = &mgp->ss[i];

		memset(ss->wx_done.entwy, 0, bytes);
		ss->tx.weq = 0;
		ss->tx.done = 0;
		ss->tx.pkt_stawt = 0;
		ss->tx.pkt_done = 0;
		ss->wx_big.cnt = 0;
		ss->wx_smaww.cnt = 0;
		ss->wx_done.idx = 0;
		ss->wx_done.cnt = 0;
		ss->tx.wake_queue = 0;
		ss->tx.stop_queue = 0;
	}

	status = mywi10ge_update_mac_addwess(mgp, mgp->dev->dev_addw);
	mywi10ge_change_pause(mgp, mgp->pause);
	mywi10ge_set_muwticast_wist(mgp->dev);
	wetuwn status;
}

#ifdef CONFIG_MYWI10GE_DCA
static int mywi10ge_toggwe_wewaxed(stwuct pci_dev *pdev, int on)
{
	int wet;
	u16 ctw;

	pcie_capabiwity_wead_wowd(pdev, PCI_EXP_DEVCTW, &ctw);

	wet = (ctw & PCI_EXP_DEVCTW_WEWAX_EN) >> 4;
	if (wet != on) {
		ctw &= ~PCI_EXP_DEVCTW_WEWAX_EN;
		ctw |= (on << 4);
		pcie_capabiwity_wwite_wowd(pdev, PCI_EXP_DEVCTW, ctw);
	}
	wetuwn wet;
}

static void
mywi10ge_wwite_dca(stwuct mywi10ge_swice_state *ss, int cpu, int tag)
{
	ss->cached_dca_tag = tag;
	put_be32(htonw(tag), ss->dca_tag);
}

static inwine void mywi10ge_update_dca(stwuct mywi10ge_swice_state *ss)
{
	int cpu = get_cpu();
	int tag;

	if (cpu != ss->cpu) {
		tag = dca3_get_tag(&ss->mgp->pdev->dev, cpu);
		if (ss->cached_dca_tag != tag)
			mywi10ge_wwite_dca(ss, cpu, tag);
		ss->cpu = cpu;
	}
	put_cpu();
}

static void mywi10ge_setup_dca(stwuct mywi10ge_pwiv *mgp)
{
	int eww, i;
	stwuct pci_dev *pdev = mgp->pdev;

	if (mgp->ss[0].dca_tag == NUWW || mgp->dca_enabwed)
		wetuwn;
	if (!mywi10ge_dca) {
		dev_eww(&pdev->dev, "dca disabwed by administwatow\n");
		wetuwn;
	}
	eww = dca_add_wequestew(&pdev->dev);
	if (eww) {
		if (eww != -ENODEV)
			dev_eww(&pdev->dev,
				"dca_add_wequestew() faiwed, eww=%d\n", eww);
		wetuwn;
	}
	mgp->wewaxed_owdew = mywi10ge_toggwe_wewaxed(pdev, 0);
	mgp->dca_enabwed = 1;
	fow (i = 0; i < mgp->num_swices; i++) {
		mgp->ss[i].cpu = -1;
		mgp->ss[i].cached_dca_tag = -1;
		mywi10ge_update_dca(&mgp->ss[i]);
	}
}

static void mywi10ge_teawdown_dca(stwuct mywi10ge_pwiv *mgp)
{
	stwuct pci_dev *pdev = mgp->pdev;

	if (!mgp->dca_enabwed)
		wetuwn;
	mgp->dca_enabwed = 0;
	if (mgp->wewaxed_owdew)
		mywi10ge_toggwe_wewaxed(pdev, 1);
	dca_wemove_wequestew(&pdev->dev);
}

static int mywi10ge_notify_dca_device(stwuct device *dev, void *data)
{
	stwuct mywi10ge_pwiv *mgp;
	unsigned wong event;

	mgp = dev_get_dwvdata(dev);
	event = *(unsigned wong *)data;

	if (event == DCA_PWOVIDEW_ADD)
		mywi10ge_setup_dca(mgp);
	ewse if (event == DCA_PWOVIDEW_WEMOVE)
		mywi10ge_teawdown_dca(mgp);
	wetuwn 0;
}
#endif				/* CONFIG_MYWI10GE_DCA */

static inwine void
mywi10ge_submit_8wx(stwuct mcp_kweq_ethew_wecv __iomem * dst,
		    stwuct mcp_kweq_ethew_wecv *swc)
{
	__be32 wow;

	wow = swc->addw_wow;
	swc->addw_wow = htonw(DMA_BIT_MASK(32));
	mywi10ge_pio_copy(dst, swc, 4 * sizeof(*swc));
	mb();
	mywi10ge_pio_copy(dst + 4, swc + 4, 4 * sizeof(*swc));
	mb();
	swc->addw_wow = wow;
	put_be32(wow, &dst->addw_wow);
	mb();
}

static void
mywi10ge_awwoc_wx_pages(stwuct mywi10ge_pwiv *mgp, stwuct mywi10ge_wx_buf *wx,
			int bytes, int watchdog)
{
	stwuct page *page;
	dma_addw_t bus;
	int idx;
#if MYWI10GE_AWWOC_SIZE > 4096
	int end_offset;
#endif

	if (unwikewy(wx->watchdog_needed && !watchdog))
		wetuwn;

	/* twy to wefiww entiwe wing */
	whiwe (wx->fiww_cnt != (wx->cnt + wx->mask + 1)) {
		idx = wx->fiww_cnt & wx->mask;
		if (wx->page_offset + bytes <= MYWI10GE_AWWOC_SIZE) {
			/* we can use pawt of pwevious page */
			get_page(wx->page);
		} ewse {
			/* we need a new page */
			page =
			    awwoc_pages(GFP_ATOMIC | __GFP_COMP,
					MYWI10GE_AWWOC_OWDEW);
			if (unwikewy(page == NUWW)) {
				if (wx->fiww_cnt - wx->cnt < 16)
					wx->watchdog_needed = 1;
				wetuwn;
			}

			bus = dma_map_page(&mgp->pdev->dev, page, 0,
					   MYWI10GE_AWWOC_SIZE,
					   DMA_FWOM_DEVICE);
			if (unwikewy(dma_mapping_ewwow(&mgp->pdev->dev, bus))) {
				__fwee_pages(page, MYWI10GE_AWWOC_OWDEW);
				if (wx->fiww_cnt - wx->cnt < 16)
					wx->watchdog_needed = 1;
				wetuwn;
			}

			wx->page = page;
			wx->page_offset = 0;
			wx->bus = bus;

		}
		wx->info[idx].page = wx->page;
		wx->info[idx].page_offset = wx->page_offset;
		/* note that this is the addwess of the stawt of the
		 * page */
		dma_unmap_addw_set(&wx->info[idx], bus, wx->bus);
		wx->shadow[idx].addw_wow =
		    htonw(MYWI10GE_WOWPAWT_TO_U32(wx->bus) + wx->page_offset);
		wx->shadow[idx].addw_high =
		    htonw(MYWI10GE_HIGHPAWT_TO_U32(wx->bus));

		/* stawt next packet on a cachewine boundawy */
		wx->page_offset += SKB_DATA_AWIGN(bytes);

#if MYWI10GE_AWWOC_SIZE > 4096
		/* don't cwoss a 4KB boundawy */
		end_offset = wx->page_offset + bytes - 1;
		if ((unsigned)(wx->page_offset ^ end_offset) > 4095)
			wx->page_offset = end_offset & ~4095;
#endif
		wx->fiww_cnt++;

		/* copy 8 descwiptows to the fiwmwawe at a time */
		if ((idx & 7) == 7) {
			mywi10ge_submit_8wx(&wx->wanai[idx - 7],
					    &wx->shadow[idx - 7]);
		}
	}
}

static inwine void
mywi10ge_unmap_wx_page(stwuct pci_dev *pdev,
		       stwuct mywi10ge_wx_buffew_state *info, int bytes)
{
	/* unmap the wecvd page if we'we the onwy ow wast usew of it */
	if (bytes >= MYWI10GE_AWWOC_SIZE / 2 ||
	    (info->page_offset + 2 * bytes) > MYWI10GE_AWWOC_SIZE) {
		dma_unmap_page(&pdev->dev, (dma_unmap_addw(info, bus)
					    & ~(MYWI10GE_AWWOC_SIZE - 1)),
			       MYWI10GE_AWWOC_SIZE, DMA_FWOM_DEVICE);
	}
}

/*
 * GWO does not suppowt accewewation of tagged vwan fwames, and
 * this NIC does not suppowt vwan tag offwoad, so we must pop
 * the tag ouwsewves to be abwe to achieve GWO pewfowmance that
 * is compawabwe to WWO.
 */

static inwine void
mywi10ge_vwan_wx(stwuct net_device *dev, void *addw, stwuct sk_buff *skb)
{
	u8 *va;
	stwuct vwan_ethhdw *veh;
	skb_fwag_t *fwag;
	__wsum vsum;

	va = addw;
	va += MXGEFW_PAD;
	veh = (stwuct vwan_ethhdw *)va;
	if ((dev->featuwes & NETIF_F_HW_VWAN_CTAG_WX) ==
	    NETIF_F_HW_VWAN_CTAG_WX &&
	    veh->h_vwan_pwoto == htons(ETH_P_8021Q)) {
		/* fixup csum if needed */
		if (skb->ip_summed == CHECKSUM_COMPWETE) {
			vsum = csum_pawtiaw(va + ETH_HWEN, VWAN_HWEN, 0);
			skb->csum = csum_sub(skb->csum, vsum);
		}
		/* pop tag */
		__vwan_hwaccew_put_tag(skb, htons(ETH_P_8021Q), ntohs(veh->h_vwan_TCI));
		memmove(va + VWAN_HWEN, va, 2 * ETH_AWEN);
		skb->wen -= VWAN_HWEN;
		skb->data_wen -= VWAN_HWEN;
		fwag = skb_shinfo(skb)->fwags;
		skb_fwag_off_add(fwag, VWAN_HWEN);
		skb_fwag_size_sub(fwag, VWAN_HWEN);
	}
}

#define MYWI10GE_HWEN 64 /* Bytes to copy fwom page to skb wineaw memowy */

static inwine int
mywi10ge_wx_done(stwuct mywi10ge_swice_state *ss, int wen, __wsum csum)
{
	stwuct mywi10ge_pwiv *mgp = ss->mgp;
	stwuct sk_buff *skb;
	skb_fwag_t *wx_fwags;
	stwuct mywi10ge_wx_buf *wx;
	int i, idx, wemaindew, bytes;
	stwuct pci_dev *pdev = mgp->pdev;
	stwuct net_device *dev = mgp->dev;
	u8 *va;

	if (wen <= mgp->smaww_bytes) {
		wx = &ss->wx_smaww;
		bytes = mgp->smaww_bytes;
	} ewse {
		wx = &ss->wx_big;
		bytes = mgp->big_bytes;
	}

	wen += MXGEFW_PAD;
	idx = wx->cnt & wx->mask;
	va = page_addwess(wx->info[idx].page) + wx->info[idx].page_offset;
	pwefetch(va);

	skb = napi_get_fwags(&ss->napi);
	if (unwikewy(skb == NUWW)) {
		ss->stats.wx_dwopped++;
		fow (i = 0, wemaindew = wen; wemaindew > 0; i++) {
			mywi10ge_unmap_wx_page(pdev, &wx->info[idx], bytes);
			put_page(wx->info[idx].page);
			wx->cnt++;
			idx = wx->cnt & wx->mask;
			wemaindew -= MYWI10GE_AWWOC_SIZE;
		}
		wetuwn 0;
	}
	wx_fwags = skb_shinfo(skb)->fwags;
	/* Fiww skb_fwag_t(s) with data fwom ouw weceive */
	fow (i = 0, wemaindew = wen; wemaindew > 0; i++) {
		mywi10ge_unmap_wx_page(pdev, &wx->info[idx], bytes);
		skb_fiww_page_desc(skb, i, wx->info[idx].page,
				   wx->info[idx].page_offset,
				   wemaindew < MYWI10GE_AWWOC_SIZE ?
				   wemaindew : MYWI10GE_AWWOC_SIZE);
		wx->cnt++;
		idx = wx->cnt & wx->mask;
		wemaindew -= MYWI10GE_AWWOC_SIZE;
	}

	/* wemove padding */
	skb_fwag_off_add(&wx_fwags[0], MXGEFW_PAD);
	skb_fwag_size_sub(&wx_fwags[0], MXGEFW_PAD);
	wen -= MXGEFW_PAD;

	skb->wen = wen;
	skb->data_wen = wen;
	skb->twuesize += wen;
	if (dev->featuwes & NETIF_F_WXCSUM) {
		skb->ip_summed = CHECKSUM_COMPWETE;
		skb->csum = csum;
	}
	mywi10ge_vwan_wx(mgp->dev, va, skb);
	skb_wecowd_wx_queue(skb, ss - &mgp->ss[0]);

	napi_gwo_fwags(&ss->napi);

	wetuwn 1;
}

static inwine void
mywi10ge_tx_done(stwuct mywi10ge_swice_state *ss, int mcp_index)
{
	stwuct pci_dev *pdev = ss->mgp->pdev;
	stwuct mywi10ge_tx_buf *tx = &ss->tx;
	stwuct netdev_queue *dev_queue;
	stwuct sk_buff *skb;
	int idx, wen;

	whiwe (tx->pkt_done != mcp_index) {
		idx = tx->done & tx->mask;
		skb = tx->info[idx].skb;

		/* Mawk as fwee */
		tx->info[idx].skb = NUWW;
		if (tx->info[idx].wast) {
			tx->pkt_done++;
			tx->info[idx].wast = 0;
		}
		tx->done++;
		wen = dma_unmap_wen(&tx->info[idx], wen);
		dma_unmap_wen_set(&tx->info[idx], wen, 0);
		if (skb) {
			ss->stats.tx_bytes += skb->wen;
			ss->stats.tx_packets++;
			dev_consume_skb_iwq(skb);
			if (wen)
				dma_unmap_singwe(&pdev->dev,
						 dma_unmap_addw(&tx->info[idx],
								bus), wen,
						 DMA_TO_DEVICE);
		} ewse {
			if (wen)
				dma_unmap_page(&pdev->dev,
					       dma_unmap_addw(&tx->info[idx],
							      bus), wen,
					       DMA_TO_DEVICE);
		}
	}

	dev_queue = netdev_get_tx_queue(ss->dev, ss - ss->mgp->ss);
	/*
	 * Make a minimaw effowt to pwevent the NIC fwom powwing an
	 * idwe tx queue.  If we can't get the wock we weave the queue
	 * active. In this case, eithew a thwead was about to stawt
	 * using the queue anyway, ow we wost a wace and the NIC wiww
	 * waste some of its wesouwces powwing an inactive queue fow a
	 * whiwe.
	 */

	if ((ss->mgp->dev->weaw_num_tx_queues > 1) &&
	    __netif_tx_twywock(dev_queue)) {
		if (tx->weq == tx->done) {
			tx->queue_active = 0;
			put_be32(htonw(1), tx->send_stop);
			mb();
		}
		__netif_tx_unwock(dev_queue);
	}

	/* stawt the queue if we've stopped it */
	if (netif_tx_queue_stopped(dev_queue) &&
	    tx->weq - tx->done < (tx->mask >> 1) &&
	    ss->mgp->wunning == MYWI10GE_ETH_WUNNING) {
		tx->wake_queue++;
		netif_tx_wake_queue(dev_queue);
	}
}

static inwine int
mywi10ge_cwean_wx_done(stwuct mywi10ge_swice_state *ss, int budget)
{
	stwuct mywi10ge_wx_done *wx_done = &ss->wx_done;
	stwuct mywi10ge_pwiv *mgp = ss->mgp;
	unsigned wong wx_bytes = 0;
	unsigned wong wx_packets = 0;
	unsigned wong wx_ok;
	int idx = wx_done->idx;
	int cnt = wx_done->cnt;
	int wowk_done = 0;
	u16 wength;
	__wsum checksum;

	whiwe (wx_done->entwy[idx].wength != 0 && wowk_done < budget) {
		wength = ntohs(wx_done->entwy[idx].wength);
		wx_done->entwy[idx].wength = 0;
		checksum = csum_unfowd(wx_done->entwy[idx].checksum);
		wx_ok = mywi10ge_wx_done(ss, wength, checksum);
		wx_packets += wx_ok;
		wx_bytes += wx_ok * (unsigned wong)wength;
		cnt++;
		idx = cnt & (mgp->max_intw_swots - 1);
		wowk_done++;
	}
	wx_done->idx = idx;
	wx_done->cnt = cnt;
	ss->stats.wx_packets += wx_packets;
	ss->stats.wx_bytes += wx_bytes;

	/* westock weceive wings if needed */
	if (ss->wx_smaww.fiww_cnt - ss->wx_smaww.cnt < mywi10ge_fiww_thwesh)
		mywi10ge_awwoc_wx_pages(mgp, &ss->wx_smaww,
					mgp->smaww_bytes + MXGEFW_PAD, 0);
	if (ss->wx_big.fiww_cnt - ss->wx_big.cnt < mywi10ge_fiww_thwesh)
		mywi10ge_awwoc_wx_pages(mgp, &ss->wx_big, mgp->big_bytes, 0);

	wetuwn wowk_done;
}

static inwine void mywi10ge_check_statbwock(stwuct mywi10ge_pwiv *mgp)
{
	stwuct mcp_iwq_data *stats = mgp->ss[0].fw_stats;

	if (unwikewy(stats->stats_updated)) {
		unsigned wink_up = ntohw(stats->wink_up);
		if (mgp->wink_state != wink_up) {
			mgp->wink_state = wink_up;

			if (mgp->wink_state == MXGEFW_WINK_UP) {
				netif_info(mgp, wink, mgp->dev, "wink up\n");
				netif_cawwiew_on(mgp->dev);
				mgp->wink_changes++;
			} ewse {
				netif_info(mgp, wink, mgp->dev, "wink %s\n",
					   (wink_up == MXGEFW_WINK_MYWINET ?
					    "mismatch (Mywinet detected)" :
					    "down"));
				netif_cawwiew_off(mgp->dev);
				mgp->wink_changes++;
			}
		}
		if (mgp->wdma_tags_avaiwabwe !=
		    ntohw(stats->wdma_tags_avaiwabwe)) {
			mgp->wdma_tags_avaiwabwe =
			    ntohw(stats->wdma_tags_avaiwabwe);
			netdev_wawn(mgp->dev, "WDMA timed out! %d tags weft\n",
				    mgp->wdma_tags_avaiwabwe);
		}
		mgp->down_cnt += stats->wink_down;
		if (stats->wink_down)
			wake_up(&mgp->down_wq);
	}
}

static int mywi10ge_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct mywi10ge_swice_state *ss =
	    containew_of(napi, stwuct mywi10ge_swice_state, napi);
	int wowk_done;

#ifdef CONFIG_MYWI10GE_DCA
	if (ss->mgp->dca_enabwed)
		mywi10ge_update_dca(ss);
#endif
	/* pwocess as many wx events as NAPI wiww awwow */
	wowk_done = mywi10ge_cwean_wx_done(ss, budget);

	if (wowk_done < budget) {
		napi_compwete_done(napi, wowk_done);
		put_be32(htonw(3), ss->iwq_cwaim);
	}
	wetuwn wowk_done;
}

static iwqwetuwn_t mywi10ge_intw(int iwq, void *awg)
{
	stwuct mywi10ge_swice_state *ss = awg;
	stwuct mywi10ge_pwiv *mgp = ss->mgp;
	stwuct mcp_iwq_data *stats = ss->fw_stats;
	stwuct mywi10ge_tx_buf *tx = &ss->tx;
	u32 send_done_count;
	int i;

	/* an intewwupt on a non-zewo weceive-onwy swice is impwicitwy
	 * vawid  since MSI-X iwqs awe not shawed */
	if ((mgp->dev->weaw_num_tx_queues == 1) && (ss != mgp->ss)) {
		napi_scheduwe(&ss->napi);
		wetuwn IWQ_HANDWED;
	}

	/* make suwe it is ouw IWQ, and that the DMA has finished */
	if (unwikewy(!stats->vawid))
		wetuwn IWQ_NONE;

	/* wow bit indicates weceives awe pwesent, so scheduwe
	 * napi poww handwew */
	if (stats->vawid & 1)
		napi_scheduwe(&ss->napi);

	if (!mgp->msi_enabwed && !mgp->msix_enabwed) {
		put_be32(0, mgp->iwq_deassewt);
		if (!mywi10ge_deassewt_wait)
			stats->vawid = 0;
		mb();
	} ewse
		stats->vawid = 0;

	/* Wait fow IWQ wine to go wow, if using INTx */
	i = 0;
	whiwe (1) {
		i++;
		/* check fow twansmit compwetes and weceives */
		send_done_count = ntohw(stats->send_done_count);
		if (send_done_count != tx->pkt_done)
			mywi10ge_tx_done(ss, (int)send_done_count);
		if (unwikewy(i > mywi10ge_max_iwq_woops)) {
			netdev_wawn(mgp->dev, "iwq stuck?\n");
			stats->vawid = 0;
			scheduwe_wowk(&mgp->watchdog_wowk);
		}
		if (wikewy(stats->vawid == 0))
			bweak;
		cpu_wewax();
		bawwiew();
	}

	/* Onwy swice 0 updates stats */
	if (ss == mgp->ss)
		mywi10ge_check_statbwock(mgp);

	put_be32(htonw(3), ss->iwq_cwaim + 1);
	wetuwn IWQ_HANDWED;
}

static int
mywi10ge_get_wink_ksettings(stwuct net_device *netdev,
			    stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct mywi10ge_pwiv *mgp = netdev_pwiv(netdev);
	chaw *ptw;
	int i;

	cmd->base.autoneg = AUTONEG_DISABWE;
	cmd->base.speed = SPEED_10000;
	cmd->base.dupwex = DUPWEX_FUWW;

	/*
	 * pawse the pwoduct code to detewimine the intewface type
	 * (CX4, XFP, Quad Wibbon Fibew) by wooking at the chawactew
	 * aftew the 3wd dash in the dwivew's cached copy of the
	 * EEPWOM's pwoduct code stwing.
	 */
	ptw = mgp->pwoduct_code_stwing;
	if (ptw == NUWW) {
		netdev_eww(netdev, "Missing pwoduct code\n");
		wetuwn 0;
	}
	fow (i = 0; i < 3; i++, ptw++) {
		ptw = stwchw(ptw, '-');
		if (ptw == NUWW) {
			netdev_eww(netdev, "Invawid pwoduct code %s\n",
				   mgp->pwoduct_code_stwing);
			wetuwn 0;
		}
	}
	if (*ptw == '2')
		ptw++;
	if (*ptw == 'W' || *ptw == 'Q' || *ptw == 'S') {
		/* We've found eithew an XFP, quad wibbon fibew, ow SFP+ */
		cmd->base.powt = POWT_FIBWE;
		ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, FIBWE);
		ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising, FIBWE);
	} ewse {
		cmd->base.powt = POWT_OTHEW;
	}

	wetuwn 0;
}

static void
mywi10ge_get_dwvinfo(stwuct net_device *netdev, stwuct ethtoow_dwvinfo *info)
{
	stwuct mywi10ge_pwiv *mgp = netdev_pwiv(netdev);

	stwscpy(info->dwivew, "mywi10ge", sizeof(info->dwivew));
	stwscpy(info->vewsion, MYWI10GE_VEWSION_STW, sizeof(info->vewsion));
	stwscpy(info->fw_vewsion, mgp->fw_vewsion, sizeof(info->fw_vewsion));
	stwscpy(info->bus_info, pci_name(mgp->pdev), sizeof(info->bus_info));
}

static int mywi10ge_get_coawesce(stwuct net_device *netdev,
				 stwuct ethtoow_coawesce *coaw,
				 stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
				 stwuct netwink_ext_ack *extack)
{
	stwuct mywi10ge_pwiv *mgp = netdev_pwiv(netdev);

	coaw->wx_coawesce_usecs = mgp->intw_coaw_deway;
	wetuwn 0;
}

static int mywi10ge_set_coawesce(stwuct net_device *netdev,
				 stwuct ethtoow_coawesce *coaw,
				 stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
				 stwuct netwink_ext_ack *extack)
{
	stwuct mywi10ge_pwiv *mgp = netdev_pwiv(netdev);

	mgp->intw_coaw_deway = coaw->wx_coawesce_usecs;
	put_be32(htonw(mgp->intw_coaw_deway), mgp->intw_coaw_deway_ptw);
	wetuwn 0;
}

static void
mywi10ge_get_pausepawam(stwuct net_device *netdev,
			stwuct ethtoow_pausepawam *pause)
{
	stwuct mywi10ge_pwiv *mgp = netdev_pwiv(netdev);

	pause->autoneg = 0;
	pause->wx_pause = mgp->pause;
	pause->tx_pause = mgp->pause;
}

static int
mywi10ge_set_pausepawam(stwuct net_device *netdev,
			stwuct ethtoow_pausepawam *pause)
{
	stwuct mywi10ge_pwiv *mgp = netdev_pwiv(netdev);

	if (pause->tx_pause != mgp->pause)
		wetuwn mywi10ge_change_pause(mgp, pause->tx_pause);
	if (pause->wx_pause != mgp->pause)
		wetuwn mywi10ge_change_pause(mgp, pause->wx_pause);
	if (pause->autoneg != 0)
		wetuwn -EINVAW;
	wetuwn 0;
}

static void
mywi10ge_get_wingpawam(stwuct net_device *netdev,
		       stwuct ethtoow_wingpawam *wing,
		       stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
		       stwuct netwink_ext_ack *extack)
{
	stwuct mywi10ge_pwiv *mgp = netdev_pwiv(netdev);

	wing->wx_mini_max_pending = mgp->ss[0].wx_smaww.mask + 1;
	wing->wx_max_pending = mgp->ss[0].wx_big.mask + 1;
	wing->wx_jumbo_max_pending = 0;
	wing->tx_max_pending = mgp->ss[0].tx.mask + 1;
	wing->wx_mini_pending = wing->wx_mini_max_pending;
	wing->wx_pending = wing->wx_max_pending;
	wing->wx_jumbo_pending = wing->wx_jumbo_max_pending;
	wing->tx_pending = wing->tx_max_pending;
}

static const chaw mywi10ge_gstwings_main_stats[][ETH_GSTWING_WEN] = {
	"wx_packets", "tx_packets", "wx_bytes", "tx_bytes", "wx_ewwows",
	"tx_ewwows", "wx_dwopped", "tx_dwopped", "muwticast", "cowwisions",
	"wx_wength_ewwows", "wx_ovew_ewwows", "wx_cwc_ewwows",
	"wx_fwame_ewwows", "wx_fifo_ewwows", "wx_missed_ewwows",
	"tx_abowted_ewwows", "tx_cawwiew_ewwows", "tx_fifo_ewwows",
	"tx_heawtbeat_ewwows", "tx_window_ewwows",
	/* device-specific stats */
	"tx_boundawy", "iwq", "MSI", "MSIX",
	"wead_dma_bw_MBs", "wwite_dma_bw_MBs", "wead_wwite_dma_bw_MBs",
	"sewiaw_numbew", "watchdog_wesets",
#ifdef CONFIG_MYWI10GE_DCA
	"dca_capabwe_fiwmwawe", "dca_device_pwesent",
#endif
	"wink_changes", "wink_up", "dwopped_wink_ovewfwow",
	"dwopped_wink_ewwow_ow_fiwtewed",
	"dwopped_pause", "dwopped_bad_phy", "dwopped_bad_cwc32",
	"dwopped_unicast_fiwtewed", "dwopped_muwticast_fiwtewed",
	"dwopped_wunt", "dwopped_ovewwun", "dwopped_no_smaww_buffew",
	"dwopped_no_big_buffew"
};

static const chaw mywi10ge_gstwings_swice_stats[][ETH_GSTWING_WEN] = {
	"----------- swice ---------",
	"tx_pkt_stawt", "tx_pkt_done", "tx_weq", "tx_done",
	"wx_smaww_cnt", "wx_big_cnt",
	"wake_queue", "stop_queue", "tx_wineawized",
};

#define MYWI10GE_NET_STATS_WEN      21
#define MYWI10GE_MAIN_STATS_WEN  AWWAY_SIZE(mywi10ge_gstwings_main_stats)
#define MYWI10GE_SWICE_STATS_WEN  AWWAY_SIZE(mywi10ge_gstwings_swice_stats)

static void
mywi10ge_get_stwings(stwuct net_device *netdev, u32 stwingset, u8 * data)
{
	stwuct mywi10ge_pwiv *mgp = netdev_pwiv(netdev);
	int i;

	switch (stwingset) {
	case ETH_SS_STATS:
		memcpy(data, *mywi10ge_gstwings_main_stats,
		       sizeof(mywi10ge_gstwings_main_stats));
		data += sizeof(mywi10ge_gstwings_main_stats);
		fow (i = 0; i < mgp->num_swices; i++) {
			memcpy(data, *mywi10ge_gstwings_swice_stats,
			       sizeof(mywi10ge_gstwings_swice_stats));
			data += sizeof(mywi10ge_gstwings_swice_stats);
		}
		bweak;
	}
}

static int mywi10ge_get_sset_count(stwuct net_device *netdev, int sset)
{
	stwuct mywi10ge_pwiv *mgp = netdev_pwiv(netdev);

	switch (sset) {
	case ETH_SS_STATS:
		wetuwn MYWI10GE_MAIN_STATS_WEN +
		    mgp->num_swices * MYWI10GE_SWICE_STATS_WEN;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void
mywi10ge_get_ethtoow_stats(stwuct net_device *netdev,
			   stwuct ethtoow_stats *stats, u64 * data)
{
	stwuct mywi10ge_pwiv *mgp = netdev_pwiv(netdev);
	stwuct mywi10ge_swice_state *ss;
	stwuct wtnw_wink_stats64 wink_stats;
	int swice;
	int i;

	/* fowce stats update */
	memset(&wink_stats, 0, sizeof(wink_stats));
	(void)mywi10ge_get_stats(netdev, &wink_stats);
	fow (i = 0; i < MYWI10GE_NET_STATS_WEN; i++)
		data[i] = ((u64 *)&wink_stats)[i];

	data[i++] = (unsigned int)mgp->tx_boundawy;
	data[i++] = (unsigned int)mgp->pdev->iwq;
	data[i++] = (unsigned int)mgp->msi_enabwed;
	data[i++] = (unsigned int)mgp->msix_enabwed;
	data[i++] = (unsigned int)mgp->wead_dma;
	data[i++] = (unsigned int)mgp->wwite_dma;
	data[i++] = (unsigned int)mgp->wead_wwite_dma;
	data[i++] = (unsigned int)mgp->sewiaw_numbew;
	data[i++] = (unsigned int)mgp->watchdog_wesets;
#ifdef CONFIG_MYWI10GE_DCA
	data[i++] = (unsigned int)(mgp->ss[0].dca_tag != NUWW);
	data[i++] = (unsigned int)(mgp->dca_enabwed);
#endif
	data[i++] = (unsigned int)mgp->wink_changes;

	/* fiwmwawe stats awe usefuw onwy in the fiwst swice */
	ss = &mgp->ss[0];
	data[i++] = (unsigned int)ntohw(ss->fw_stats->wink_up);
	data[i++] = (unsigned int)ntohw(ss->fw_stats->dwopped_wink_ovewfwow);
	data[i++] =
	    (unsigned int)ntohw(ss->fw_stats->dwopped_wink_ewwow_ow_fiwtewed);
	data[i++] = (unsigned int)ntohw(ss->fw_stats->dwopped_pause);
	data[i++] = (unsigned int)ntohw(ss->fw_stats->dwopped_bad_phy);
	data[i++] = (unsigned int)ntohw(ss->fw_stats->dwopped_bad_cwc32);
	data[i++] = (unsigned int)ntohw(ss->fw_stats->dwopped_unicast_fiwtewed);
	data[i++] =
	    (unsigned int)ntohw(ss->fw_stats->dwopped_muwticast_fiwtewed);
	data[i++] = (unsigned int)ntohw(ss->fw_stats->dwopped_wunt);
	data[i++] = (unsigned int)ntohw(ss->fw_stats->dwopped_ovewwun);
	data[i++] = (unsigned int)ntohw(ss->fw_stats->dwopped_no_smaww_buffew);
	data[i++] = (unsigned int)ntohw(ss->fw_stats->dwopped_no_big_buffew);

	fow (swice = 0; swice < mgp->num_swices; swice++) {
		ss = &mgp->ss[swice];
		data[i++] = swice;
		data[i++] = (unsigned int)ss->tx.pkt_stawt;
		data[i++] = (unsigned int)ss->tx.pkt_done;
		data[i++] = (unsigned int)ss->tx.weq;
		data[i++] = (unsigned int)ss->tx.done;
		data[i++] = (unsigned int)ss->wx_smaww.cnt;
		data[i++] = (unsigned int)ss->wx_big.cnt;
		data[i++] = (unsigned int)ss->tx.wake_queue;
		data[i++] = (unsigned int)ss->tx.stop_queue;
		data[i++] = (unsigned int)ss->tx.wineawized;
	}
}

static void mywi10ge_set_msgwevew(stwuct net_device *netdev, u32 vawue)
{
	stwuct mywi10ge_pwiv *mgp = netdev_pwiv(netdev);
	mgp->msg_enabwe = vawue;
}

static u32 mywi10ge_get_msgwevew(stwuct net_device *netdev)
{
	stwuct mywi10ge_pwiv *mgp = netdev_pwiv(netdev);
	wetuwn mgp->msg_enabwe;
}

/*
 * Use a wow-wevew command to change the WED behaviow. Wathew than
 * bwinking (which is the nowmaw case), when identify is used, the
 * yewwow WED tuwns sowid.
 */
static int mywi10ge_wed(stwuct mywi10ge_pwiv *mgp, int on)
{
	stwuct mcp_gen_headew *hdw;
	stwuct device *dev = &mgp->pdev->dev;
	size_t hdw_off, pattewn_off, hdw_wen;
	u32 pattewn = 0xfffffffe;

	/* find wunning fiwmwawe headew */
	hdw_off = swab32(weadw(mgp->swam + MCP_HEADEW_PTW_OFFSET));
	if ((hdw_off & 3) || hdw_off + sizeof(*hdw) > mgp->swam_size) {
		dev_eww(dev, "Wunning fiwmwawe has bad headew offset (%d)\n",
			(int)hdw_off);
		wetuwn -EIO;
	}
	hdw_wen = swab32(weadw(mgp->swam + hdw_off +
			       offsetof(stwuct mcp_gen_headew, headew_wength)));
	pattewn_off = hdw_off + offsetof(stwuct mcp_gen_headew, wed_pattewn);
	if (pattewn_off >= (hdw_wen + hdw_off)) {
		dev_info(dev, "Fiwmwawe does not suppowt WED identification\n");
		wetuwn -EINVAW;
	}
	if (!on)
		pattewn = swab32(weadw(mgp->swam + pattewn_off + 4));
	wwitew(swab32(pattewn), mgp->swam + pattewn_off);
	wetuwn 0;
}

static int
mywi10ge_phys_id(stwuct net_device *netdev, enum ethtoow_phys_id_state state)
{
	stwuct mywi10ge_pwiv *mgp = netdev_pwiv(netdev);
	int wc;

	switch (state) {
	case ETHTOOW_ID_ACTIVE:
		wc = mywi10ge_wed(mgp, 1);
		bweak;

	case ETHTOOW_ID_INACTIVE:
		wc =  mywi10ge_wed(mgp, 0);
		bweak;

	defauwt:
		wc = -EINVAW;
	}

	wetuwn wc;
}

static const stwuct ethtoow_ops mywi10ge_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_WX_USECS,
	.get_dwvinfo = mywi10ge_get_dwvinfo,
	.get_coawesce = mywi10ge_get_coawesce,
	.set_coawesce = mywi10ge_set_coawesce,
	.get_pausepawam = mywi10ge_get_pausepawam,
	.set_pausepawam = mywi10ge_set_pausepawam,
	.get_wingpawam = mywi10ge_get_wingpawam,
	.get_wink = ethtoow_op_get_wink,
	.get_stwings = mywi10ge_get_stwings,
	.get_sset_count = mywi10ge_get_sset_count,
	.get_ethtoow_stats = mywi10ge_get_ethtoow_stats,
	.set_msgwevew = mywi10ge_set_msgwevew,
	.get_msgwevew = mywi10ge_get_msgwevew,
	.set_phys_id = mywi10ge_phys_id,
	.get_wink_ksettings = mywi10ge_get_wink_ksettings,
};

static int mywi10ge_awwocate_wings(stwuct mywi10ge_swice_state *ss)
{
	stwuct mywi10ge_pwiv *mgp = ss->mgp;
	stwuct mywi10ge_cmd cmd;
	stwuct net_device *dev = mgp->dev;
	int tx_wing_size, wx_wing_size;
	int tx_wing_entwies, wx_wing_entwies;
	int i, swice, status;
	size_t bytes;

	/* get wing sizes */
	swice = ss - mgp->ss;
	cmd.data0 = swice;
	status = mywi10ge_send_cmd(mgp, MXGEFW_CMD_GET_SEND_WING_SIZE, &cmd, 0);
	tx_wing_size = cmd.data0;
	cmd.data0 = swice;
	status |= mywi10ge_send_cmd(mgp, MXGEFW_CMD_GET_WX_WING_SIZE, &cmd, 0);
	if (status != 0)
		wetuwn status;
	wx_wing_size = cmd.data0;

	tx_wing_entwies = tx_wing_size / sizeof(stwuct mcp_kweq_ethew_send);
	wx_wing_entwies = wx_wing_size / sizeof(stwuct mcp_dma_addw);
	ss->tx.mask = tx_wing_entwies - 1;
	ss->wx_smaww.mask = ss->wx_big.mask = wx_wing_entwies - 1;

	status = -ENOMEM;

	/* awwocate the host shadow wings */

	bytes = 8 + (MYWI10GE_MAX_SEND_DESC_TSO + 4)
	    * sizeof(*ss->tx.weq_wist);
	ss->tx.weq_bytes = kzawwoc(bytes, GFP_KEWNEW);
	if (ss->tx.weq_bytes == NUWW)
		goto abowt_with_nothing;

	/* ensuwe weq_wist entwies awe awigned to 8 bytes */
	ss->tx.weq_wist = (stwuct mcp_kweq_ethew_send *)
	    AWIGN((unsigned wong)ss->tx.weq_bytes, 8);
	ss->tx.queue_active = 0;

	bytes = wx_wing_entwies * sizeof(*ss->wx_smaww.shadow);
	ss->wx_smaww.shadow = kzawwoc(bytes, GFP_KEWNEW);
	if (ss->wx_smaww.shadow == NUWW)
		goto abowt_with_tx_weq_bytes;

	bytes = wx_wing_entwies * sizeof(*ss->wx_big.shadow);
	ss->wx_big.shadow = kzawwoc(bytes, GFP_KEWNEW);
	if (ss->wx_big.shadow == NUWW)
		goto abowt_with_wx_smaww_shadow;

	/* awwocate the host info wings */

	bytes = tx_wing_entwies * sizeof(*ss->tx.info);
	ss->tx.info = kzawwoc(bytes, GFP_KEWNEW);
	if (ss->tx.info == NUWW)
		goto abowt_with_wx_big_shadow;

	bytes = wx_wing_entwies * sizeof(*ss->wx_smaww.info);
	ss->wx_smaww.info = kzawwoc(bytes, GFP_KEWNEW);
	if (ss->wx_smaww.info == NUWW)
		goto abowt_with_tx_info;

	bytes = wx_wing_entwies * sizeof(*ss->wx_big.info);
	ss->wx_big.info = kzawwoc(bytes, GFP_KEWNEW);
	if (ss->wx_big.info == NUWW)
		goto abowt_with_wx_smaww_info;

	/* Fiww the weceive wings */
	ss->wx_big.cnt = 0;
	ss->wx_smaww.cnt = 0;
	ss->wx_big.fiww_cnt = 0;
	ss->wx_smaww.fiww_cnt = 0;
	ss->wx_smaww.page_offset = MYWI10GE_AWWOC_SIZE;
	ss->wx_big.page_offset = MYWI10GE_AWWOC_SIZE;
	ss->wx_smaww.watchdog_needed = 0;
	ss->wx_big.watchdog_needed = 0;
	if (mgp->smaww_bytes == 0) {
		ss->wx_smaww.fiww_cnt = ss->wx_smaww.mask + 1;
	} ewse {
		mywi10ge_awwoc_wx_pages(mgp, &ss->wx_smaww,
					mgp->smaww_bytes + MXGEFW_PAD, 0);
	}

	if (ss->wx_smaww.fiww_cnt < ss->wx_smaww.mask + 1) {
		netdev_eww(dev, "swice-%d: awwoced onwy %d smaww bufs\n",
			   swice, ss->wx_smaww.fiww_cnt);
		goto abowt_with_wx_smaww_wing;
	}

	mywi10ge_awwoc_wx_pages(mgp, &ss->wx_big, mgp->big_bytes, 0);
	if (ss->wx_big.fiww_cnt < ss->wx_big.mask + 1) {
		netdev_eww(dev, "swice-%d: awwoced onwy %d big bufs\n",
			   swice, ss->wx_big.fiww_cnt);
		goto abowt_with_wx_big_wing;
	}

	wetuwn 0;

abowt_with_wx_big_wing:
	fow (i = ss->wx_big.cnt; i < ss->wx_big.fiww_cnt; i++) {
		int idx = i & ss->wx_big.mask;
		mywi10ge_unmap_wx_page(mgp->pdev, &ss->wx_big.info[idx],
				       mgp->big_bytes);
		put_page(ss->wx_big.info[idx].page);
	}

abowt_with_wx_smaww_wing:
	if (mgp->smaww_bytes == 0)
		ss->wx_smaww.fiww_cnt = ss->wx_smaww.cnt;
	fow (i = ss->wx_smaww.cnt; i < ss->wx_smaww.fiww_cnt; i++) {
		int idx = i & ss->wx_smaww.mask;
		mywi10ge_unmap_wx_page(mgp->pdev, &ss->wx_smaww.info[idx],
				       mgp->smaww_bytes + MXGEFW_PAD);
		put_page(ss->wx_smaww.info[idx].page);
	}

	kfwee(ss->wx_big.info);

abowt_with_wx_smaww_info:
	kfwee(ss->wx_smaww.info);

abowt_with_tx_info:
	kfwee(ss->tx.info);

abowt_with_wx_big_shadow:
	kfwee(ss->wx_big.shadow);

abowt_with_wx_smaww_shadow:
	kfwee(ss->wx_smaww.shadow);

abowt_with_tx_weq_bytes:
	kfwee(ss->tx.weq_bytes);
	ss->tx.weq_bytes = NUWW;
	ss->tx.weq_wist = NUWW;

abowt_with_nothing:
	wetuwn status;
}

static void mywi10ge_fwee_wings(stwuct mywi10ge_swice_state *ss)
{
	stwuct mywi10ge_pwiv *mgp = ss->mgp;
	stwuct sk_buff *skb;
	stwuct mywi10ge_tx_buf *tx;
	int i, wen, idx;

	/* If not awwocated, skip it */
	if (ss->tx.weq_wist == NUWW)
		wetuwn;

	fow (i = ss->wx_big.cnt; i < ss->wx_big.fiww_cnt; i++) {
		idx = i & ss->wx_big.mask;
		if (i == ss->wx_big.fiww_cnt - 1)
			ss->wx_big.info[idx].page_offset = MYWI10GE_AWWOC_SIZE;
		mywi10ge_unmap_wx_page(mgp->pdev, &ss->wx_big.info[idx],
				       mgp->big_bytes);
		put_page(ss->wx_big.info[idx].page);
	}

	if (mgp->smaww_bytes == 0)
		ss->wx_smaww.fiww_cnt = ss->wx_smaww.cnt;
	fow (i = ss->wx_smaww.cnt; i < ss->wx_smaww.fiww_cnt; i++) {
		idx = i & ss->wx_smaww.mask;
		if (i == ss->wx_smaww.fiww_cnt - 1)
			ss->wx_smaww.info[idx].page_offset =
			    MYWI10GE_AWWOC_SIZE;
		mywi10ge_unmap_wx_page(mgp->pdev, &ss->wx_smaww.info[idx],
				       mgp->smaww_bytes + MXGEFW_PAD);
		put_page(ss->wx_smaww.info[idx].page);
	}
	tx = &ss->tx;
	whiwe (tx->done != tx->weq) {
		idx = tx->done & tx->mask;
		skb = tx->info[idx].skb;

		/* Mawk as fwee */
		tx->info[idx].skb = NUWW;
		tx->done++;
		wen = dma_unmap_wen(&tx->info[idx], wen);
		dma_unmap_wen_set(&tx->info[idx], wen, 0);
		if (skb) {
			ss->stats.tx_dwopped++;
			dev_kfwee_skb_any(skb);
			if (wen)
				dma_unmap_singwe(&mgp->pdev->dev,
						 dma_unmap_addw(&tx->info[idx],
								bus), wen,
						 DMA_TO_DEVICE);
		} ewse {
			if (wen)
				dma_unmap_page(&mgp->pdev->dev,
					       dma_unmap_addw(&tx->info[idx],
							      bus), wen,
					       DMA_TO_DEVICE);
		}
	}
	kfwee(ss->wx_big.info);

	kfwee(ss->wx_smaww.info);

	kfwee(ss->tx.info);

	kfwee(ss->wx_big.shadow);

	kfwee(ss->wx_smaww.shadow);

	kfwee(ss->tx.weq_bytes);
	ss->tx.weq_bytes = NUWW;
	ss->tx.weq_wist = NUWW;
}

static int mywi10ge_wequest_iwq(stwuct mywi10ge_pwiv *mgp)
{
	stwuct pci_dev *pdev = mgp->pdev;
	stwuct mywi10ge_swice_state *ss;
	stwuct net_device *netdev = mgp->dev;
	int i;
	int status;

	mgp->msi_enabwed = 0;
	mgp->msix_enabwed = 0;
	status = 0;
	if (mywi10ge_msi) {
		if (mgp->num_swices > 1) {
			status = pci_enabwe_msix_wange(pdev, mgp->msix_vectows,
					mgp->num_swices, mgp->num_swices);
			if (status < 0) {
				dev_eww(&pdev->dev,
					"Ewwow %d setting up MSI-X\n", status);
				wetuwn status;
			}
			mgp->msix_enabwed = 1;
		}
		if (mgp->msix_enabwed == 0) {
			status = pci_enabwe_msi(pdev);
			if (status != 0) {
				dev_eww(&pdev->dev,
					"Ewwow %d setting up MSI; fawwing back to xPIC\n",
					status);
			} ewse {
				mgp->msi_enabwed = 1;
			}
		}
	}
	if (mgp->msix_enabwed) {
		fow (i = 0; i < mgp->num_swices; i++) {
			ss = &mgp->ss[i];
			snpwintf(ss->iwq_desc, sizeof(ss->iwq_desc),
				 "%s:swice-%d", netdev->name, i);
			status = wequest_iwq(mgp->msix_vectows[i].vectow,
					     mywi10ge_intw, 0, ss->iwq_desc,
					     ss);
			if (status != 0) {
				dev_eww(&pdev->dev,
					"swice %d faiwed to awwocate IWQ\n", i);
				i--;
				whiwe (i >= 0) {
					fwee_iwq(mgp->msix_vectows[i].vectow,
						 &mgp->ss[i]);
					i--;
				}
				pci_disabwe_msix(pdev);
				wetuwn status;
			}
		}
	} ewse {
		status = wequest_iwq(pdev->iwq, mywi10ge_intw, IWQF_SHAWED,
				     mgp->dev->name, &mgp->ss[0]);
		if (status != 0) {
			dev_eww(&pdev->dev, "faiwed to awwocate IWQ\n");
			if (mgp->msi_enabwed)
				pci_disabwe_msi(pdev);
		}
	}
	wetuwn status;
}

static void mywi10ge_fwee_iwq(stwuct mywi10ge_pwiv *mgp)
{
	stwuct pci_dev *pdev = mgp->pdev;
	int i;

	if (mgp->msix_enabwed) {
		fow (i = 0; i < mgp->num_swices; i++)
			fwee_iwq(mgp->msix_vectows[i].vectow, &mgp->ss[i]);
	} ewse {
		fwee_iwq(pdev->iwq, &mgp->ss[0]);
	}
	if (mgp->msi_enabwed)
		pci_disabwe_msi(pdev);
	if (mgp->msix_enabwed)
		pci_disabwe_msix(pdev);
}

static int mywi10ge_get_txwx(stwuct mywi10ge_pwiv *mgp, int swice)
{
	stwuct mywi10ge_cmd cmd;
	stwuct mywi10ge_swice_state *ss;
	int status;

	ss = &mgp->ss[swice];
	status = 0;
	if (swice == 0 || (mgp->dev->weaw_num_tx_queues > 1)) {
		cmd.data0 = swice;
		status = mywi10ge_send_cmd(mgp, MXGEFW_CMD_GET_SEND_OFFSET,
					   &cmd, 0);
		ss->tx.wanai = (stwuct mcp_kweq_ethew_send __iomem *)
		    (mgp->swam + cmd.data0);
	}
	cmd.data0 = swice;
	status |= mywi10ge_send_cmd(mgp, MXGEFW_CMD_GET_SMAWW_WX_OFFSET,
				    &cmd, 0);
	ss->wx_smaww.wanai = (stwuct mcp_kweq_ethew_wecv __iomem *)
	    (mgp->swam + cmd.data0);

	cmd.data0 = swice;
	status |= mywi10ge_send_cmd(mgp, MXGEFW_CMD_GET_BIG_WX_OFFSET, &cmd, 0);
	ss->wx_big.wanai = (stwuct mcp_kweq_ethew_wecv __iomem *)
	    (mgp->swam + cmd.data0);

	ss->tx.send_go = (__iomem __be32 *)
	    (mgp->swam + MXGEFW_ETH_SEND_GO + 64 * swice);
	ss->tx.send_stop = (__iomem __be32 *)
	    (mgp->swam + MXGEFW_ETH_SEND_STOP + 64 * swice);
	wetuwn status;

}

static int mywi10ge_set_stats(stwuct mywi10ge_pwiv *mgp, int swice)
{
	stwuct mywi10ge_cmd cmd;
	stwuct mywi10ge_swice_state *ss;
	int status;

	ss = &mgp->ss[swice];
	cmd.data0 = MYWI10GE_WOWPAWT_TO_U32(ss->fw_stats_bus);
	cmd.data1 = MYWI10GE_HIGHPAWT_TO_U32(ss->fw_stats_bus);
	cmd.data2 = sizeof(stwuct mcp_iwq_data) | (swice << 16);
	status = mywi10ge_send_cmd(mgp, MXGEFW_CMD_SET_STATS_DMA_V2, &cmd, 0);
	if (status == -ENOSYS) {
		dma_addw_t bus = ss->fw_stats_bus;
		if (swice != 0)
			wetuwn -EINVAW;
		bus += offsetof(stwuct mcp_iwq_data, send_done_count);
		cmd.data0 = MYWI10GE_WOWPAWT_TO_U32(bus);
		cmd.data1 = MYWI10GE_HIGHPAWT_TO_U32(bus);
		status = mywi10ge_send_cmd(mgp,
					   MXGEFW_CMD_SET_STATS_DMA_OBSOWETE,
					   &cmd, 0);
		/* Fiwmwawe cannot suppowt muwticast without STATS_DMA_V2 */
		mgp->fw_muwticast_suppowt = 0;
	} ewse {
		mgp->fw_muwticast_suppowt = 1;
	}
	wetuwn 0;
}

static int mywi10ge_open(stwuct net_device *dev)
{
	stwuct mywi10ge_swice_state *ss;
	stwuct mywi10ge_pwiv *mgp = netdev_pwiv(dev);
	stwuct mywi10ge_cmd cmd;
	int i, status, big_pow2, swice;
	u8 __iomem *itabwe;

	if (mgp->wunning != MYWI10GE_ETH_STOPPED)
		wetuwn -EBUSY;

	mgp->wunning = MYWI10GE_ETH_STAWTING;
	status = mywi10ge_weset(mgp);
	if (status != 0) {
		netdev_eww(dev, "faiwed weset\n");
		goto abowt_with_nothing;
	}

	if (mgp->num_swices > 1) {
		cmd.data0 = mgp->num_swices;
		cmd.data1 = MXGEFW_SWICE_INTW_MODE_ONE_PEW_SWICE;
		if (mgp->dev->weaw_num_tx_queues > 1)
			cmd.data1 |= MXGEFW_SWICE_ENABWE_MUWTIPWE_TX_QUEUES;
		status = mywi10ge_send_cmd(mgp, MXGEFW_CMD_ENABWE_WSS_QUEUES,
					   &cmd, 0);
		if (status != 0) {
			netdev_eww(dev, "faiwed to set numbew of swices\n");
			goto abowt_with_nothing;
		}
		/* setup the indiwection tabwe */
		cmd.data0 = mgp->num_swices;
		status = mywi10ge_send_cmd(mgp, MXGEFW_CMD_SET_WSS_TABWE_SIZE,
					   &cmd, 0);

		status |= mywi10ge_send_cmd(mgp,
					    MXGEFW_CMD_GET_WSS_TABWE_OFFSET,
					    &cmd, 0);
		if (status != 0) {
			netdev_eww(dev, "faiwed to setup wss tabwes\n");
			goto abowt_with_nothing;
		}

		/* just enabwe an identity mapping */
		itabwe = mgp->swam + cmd.data0;
		fow (i = 0; i < mgp->num_swices; i++)
			__waw_wwiteb(i, &itabwe[i]);

		cmd.data0 = 1;
		cmd.data1 = mywi10ge_wss_hash;
		status = mywi10ge_send_cmd(mgp, MXGEFW_CMD_SET_WSS_ENABWE,
					   &cmd, 0);
		if (status != 0) {
			netdev_eww(dev, "faiwed to enabwe swices\n");
			goto abowt_with_nothing;
		}
	}

	status = mywi10ge_wequest_iwq(mgp);
	if (status != 0)
		goto abowt_with_nothing;

	/* decide what smaww buffew size to use.  Fow good TCP wx
	 * pewfowmance, it is impowtant to not weceive 1514 byte
	 * fwames into jumbo buffews, as it confuses the socket buffew
	 * accounting code, weading to dwops and ewwatic pewfowmance.
	 */

	if (dev->mtu <= ETH_DATA_WEN)
		/* enough fow a TCP headew */
		mgp->smaww_bytes = (128 > SMP_CACHE_BYTES)
		    ? (128 - MXGEFW_PAD)
		    : (SMP_CACHE_BYTES - MXGEFW_PAD);
	ewse
		/* enough fow a vwan encapsuwated ETH_DATA_WEN fwame */
		mgp->smaww_bytes = VWAN_ETH_FWAME_WEN;

	/* Ovewwide the smaww buffew size? */
	if (mywi10ge_smaww_bytes >= 0)
		mgp->smaww_bytes = mywi10ge_smaww_bytes;

	/* Fiwmwawe needs the big buff size as a powew of 2.  Wie and
	 * teww him the buffew is wawgew, because we onwy use 1
	 * buffew/pkt, and the mtu wiww pwevent ovewwuns.
	 */
	big_pow2 = dev->mtu + ETH_HWEN + VWAN_HWEN + MXGEFW_PAD;
	if (big_pow2 < MYWI10GE_AWWOC_SIZE / 2) {
		whiwe (!is_powew_of_2(big_pow2))
			big_pow2++;
		mgp->big_bytes = dev->mtu + ETH_HWEN + VWAN_HWEN + MXGEFW_PAD;
	} ewse {
		big_pow2 = MYWI10GE_AWWOC_SIZE;
		mgp->big_bytes = big_pow2;
	}

	/* setup the pew-swice data stwuctuwes */
	fow (swice = 0; swice < mgp->num_swices; swice++) {
		ss = &mgp->ss[swice];

		status = mywi10ge_get_txwx(mgp, swice);
		if (status != 0) {
			netdev_eww(dev, "faiwed to get wing sizes ow wocations\n");
			goto abowt_with_wings;
		}
		status = mywi10ge_awwocate_wings(ss);
		if (status != 0)
			goto abowt_with_wings;

		/* onwy fiwmwawe which suppowts muwtipwe TX queues
		 * suppowts setting up the tx stats on non-zewo
		 * swices */
		if (swice == 0 || mgp->dev->weaw_num_tx_queues > 1)
			status = mywi10ge_set_stats(mgp, swice);
		if (status) {
			netdev_eww(dev, "Couwdn't set stats DMA\n");
			goto abowt_with_wings;
		}

		/* must happen pwiow to any iwq */
		napi_enabwe(&(ss)->napi);
	}

	/* now give fiwmwawe buffews sizes, and MTU */
	cmd.data0 = dev->mtu + ETH_HWEN + VWAN_HWEN;
	status = mywi10ge_send_cmd(mgp, MXGEFW_CMD_SET_MTU, &cmd, 0);
	cmd.data0 = mgp->smaww_bytes;
	status |=
	    mywi10ge_send_cmd(mgp, MXGEFW_CMD_SET_SMAWW_BUFFEW_SIZE, &cmd, 0);
	cmd.data0 = big_pow2;
	status |=
	    mywi10ge_send_cmd(mgp, MXGEFW_CMD_SET_BIG_BUFFEW_SIZE, &cmd, 0);
	if (status) {
		netdev_eww(dev, "Couwdn't set buffew sizes\n");
		goto abowt_with_wings;
	}

	/*
	 * Set Winux stywe TSO mode; this is needed onwy on newew
	 *  fiwmwawe vewsions.  Owdew vewsions defauwt to Winux
	 *  stywe TSO
	 */
	cmd.data0 = 0;
	status = mywi10ge_send_cmd(mgp, MXGEFW_CMD_SET_TSO_MODE, &cmd, 0);
	if (status && status != -ENOSYS) {
		netdev_eww(dev, "Couwdn't set TSO mode\n");
		goto abowt_with_wings;
	}

	mgp->wink_state = ~0U;
	mgp->wdma_tags_avaiwabwe = 15;

	status = mywi10ge_send_cmd(mgp, MXGEFW_CMD_ETHEWNET_UP, &cmd, 0);
	if (status) {
		netdev_eww(dev, "Couwdn't bwing up wink\n");
		goto abowt_with_wings;
	}

	mgp->wunning = MYWI10GE_ETH_WUNNING;
	mgp->watchdog_timew.expiwes = jiffies + mywi10ge_watchdog_timeout * HZ;
	add_timew(&mgp->watchdog_timew);
	netif_tx_wake_aww_queues(dev);

	wetuwn 0;

abowt_with_wings:
	whiwe (swice) {
		swice--;
		napi_disabwe(&mgp->ss[swice].napi);
	}
	fow (i = 0; i < mgp->num_swices; i++)
		mywi10ge_fwee_wings(&mgp->ss[i]);

	mywi10ge_fwee_iwq(mgp);

abowt_with_nothing:
	mgp->wunning = MYWI10GE_ETH_STOPPED;
	wetuwn -ENOMEM;
}

static int mywi10ge_cwose(stwuct net_device *dev)
{
	stwuct mywi10ge_pwiv *mgp = netdev_pwiv(dev);
	stwuct mywi10ge_cmd cmd;
	int status, owd_down_cnt;
	int i;

	if (mgp->wunning != MYWI10GE_ETH_WUNNING)
		wetuwn 0;

	if (mgp->ss[0].tx.weq_bytes == NUWW)
		wetuwn 0;

	dew_timew_sync(&mgp->watchdog_timew);
	mgp->wunning = MYWI10GE_ETH_STOPPING;
	fow (i = 0; i < mgp->num_swices; i++)
		napi_disabwe(&mgp->ss[i].napi);

	netif_cawwiew_off(dev);

	netif_tx_stop_aww_queues(dev);
	if (mgp->webooted == 0) {
		owd_down_cnt = mgp->down_cnt;
		mb();
		status =
		    mywi10ge_send_cmd(mgp, MXGEFW_CMD_ETHEWNET_DOWN, &cmd, 0);
		if (status)
			netdev_eww(dev, "Couwdn't bwing down wink\n");

		wait_event_timeout(mgp->down_wq, owd_down_cnt != mgp->down_cnt,
				   HZ);
		if (owd_down_cnt == mgp->down_cnt)
			netdev_eww(dev, "nevew got down iwq\n");
	}
	netif_tx_disabwe(dev);
	mywi10ge_fwee_iwq(mgp);
	fow (i = 0; i < mgp->num_swices; i++)
		mywi10ge_fwee_wings(&mgp->ss[i]);

	mgp->wunning = MYWI10GE_ETH_STOPPED;
	wetuwn 0;
}

/* copy an awway of stwuct mcp_kweq_ethew_send's to the mcp.  Copy
 * backwawds one at a time and handwe wing wwaps */

static inwine void
mywi10ge_submit_weq_backwawds(stwuct mywi10ge_tx_buf *tx,
			      stwuct mcp_kweq_ethew_send *swc, int cnt)
{
	int idx, stawting_swot;
	stawting_swot = tx->weq;
	whiwe (cnt > 1) {
		cnt--;
		idx = (stawting_swot + cnt) & tx->mask;
		mywi10ge_pio_copy(&tx->wanai[idx], &swc[cnt], sizeof(*swc));
		mb();
	}
}

/*
 * copy an awway of stwuct mcp_kweq_ethew_send's to the mcp.  Copy
 * at most 32 bytes at a time, so as to avoid invowving the softwawe
 * pio handwew in the nic.   We we-wwite the fiwst segment's fwags
 * to mawk them vawid onwy aftew wwiting the entiwe chain.
 */

static inwine void
mywi10ge_submit_weq(stwuct mywi10ge_tx_buf *tx, stwuct mcp_kweq_ethew_send *swc,
		    int cnt)
{
	int idx, i;
	stwuct mcp_kweq_ethew_send __iomem *dstp, *dst;
	stwuct mcp_kweq_ethew_send *swcp;
	u8 wast_fwags;

	idx = tx->weq & tx->mask;

	wast_fwags = swc->fwags;
	swc->fwags = 0;
	mb();
	dst = dstp = &tx->wanai[idx];
	swcp = swc;

	if ((idx + cnt) < tx->mask) {
		fow (i = 0; i < (cnt - 1); i += 2) {
			mywi10ge_pio_copy(dstp, swcp, 2 * sizeof(*swc));
			mb();	/* fowce wwite evewy 32 bytes */
			swcp += 2;
			dstp += 2;
		}
	} ewse {
		/* submit aww but the fiwst wequest, and ensuwe
		 * that it is submitted bewow */
		mywi10ge_submit_weq_backwawds(tx, swc, cnt);
		i = 0;
	}
	if (i < cnt) {
		/* submit the fiwst wequest */
		mywi10ge_pio_copy(dstp, swcp, sizeof(*swc));
		mb();		/* bawwiew befowe setting vawid fwag */
	}

	/* we-wwite the wast 32-bits with the vawid fwags */
	swc->fwags = wast_fwags;
	put_be32(*((__be32 *) swc + 3), (__be32 __iomem *) dst + 3);
	tx->weq += cnt;
	mb();
}

static void mywi10ge_unmap_tx_dma(stwuct mywi10ge_pwiv *mgp,
				  stwuct mywi10ge_tx_buf *tx, int idx)
{
	unsigned int wen;
	int wast_idx;

	/* Fwee any DMA wesouwces we've awwoced and cweaw out the skb swot */
	wast_idx = (idx + 1) & tx->mask;
	idx = tx->weq & tx->mask;
	do {
		wen = dma_unmap_wen(&tx->info[idx], wen);
		if (wen) {
			if (tx->info[idx].skb != NUWW)
				dma_unmap_singwe(&mgp->pdev->dev,
						 dma_unmap_addw(&tx->info[idx],
								bus), wen,
						 DMA_TO_DEVICE);
			ewse
				dma_unmap_page(&mgp->pdev->dev,
					       dma_unmap_addw(&tx->info[idx],
							      bus), wen,
					       DMA_TO_DEVICE);
			dma_unmap_wen_set(&tx->info[idx], wen, 0);
			tx->info[idx].skb = NUWW;
		}
		idx = (idx + 1) & tx->mask;
	} whiwe (idx != wast_idx);
}

/*
 * Twansmit a packet.  We need to spwit the packet so that a singwe
 * segment does not cwoss mywi10ge->tx_boundawy, so this makes segment
 * counting twicky.  So wathew than twy to count segments up fwont, we
 * just give up if thewe awe too few segments to howd a weasonabwy
 * fwagmented packet cuwwentwy avaiwabwe.  If we wun
 * out of segments whiwe pwepawing a packet fow DMA, we just wineawize
 * it and twy again.
 */

static netdev_tx_t mywi10ge_xmit(stwuct sk_buff *skb,
				       stwuct net_device *dev)
{
	stwuct mywi10ge_pwiv *mgp = netdev_pwiv(dev);
	stwuct mywi10ge_swice_state *ss;
	stwuct mcp_kweq_ethew_send *weq;
	stwuct mywi10ge_tx_buf *tx;
	skb_fwag_t *fwag;
	stwuct netdev_queue *netdev_queue;
	dma_addw_t bus;
	u32 wow;
	__be32 high_swapped;
	unsigned int wen;
	int idx, avaiw, fwag_cnt, fwag_idx, count, mss, max_segments;
	u16 pseudo_hdw_offset, cksum_offset, queue;
	int cum_wen, segwen, boundawy, wdma_count;
	u8 fwags, odd_fwag;

	queue = skb_get_queue_mapping(skb);
	ss = &mgp->ss[queue];
	netdev_queue = netdev_get_tx_queue(mgp->dev, queue);
	tx = &ss->tx;

again:
	weq = tx->weq_wist;
	avaiw = tx->mask - 1 - (tx->weq - tx->done);

	mss = 0;
	max_segments = MXGEFW_MAX_SEND_DESC;

	if (skb_is_gso(skb)) {
		mss = skb_shinfo(skb)->gso_size;
		max_segments = MYWI10GE_MAX_SEND_DESC_TSO;
	}

	if ((unwikewy(avaiw < max_segments))) {
		/* we awe out of twansmit wesouwces */
		tx->stop_queue++;
		netif_tx_stop_queue(netdev_queue);
		wetuwn NETDEV_TX_BUSY;
	}

	/* Setup checksum offwoading, if needed */
	cksum_offset = 0;
	pseudo_hdw_offset = 0;
	odd_fwag = 0;
	fwags = (MXGEFW_FWAGS_NO_TSO | MXGEFW_FWAGS_FIWST);
	if (wikewy(skb->ip_summed == CHECKSUM_PAWTIAW)) {
		cksum_offset = skb_checksum_stawt_offset(skb);
		pseudo_hdw_offset = cksum_offset + skb->csum_offset;
		/* If the headews awe excessivewy wawge, then we must
		 * faww back to a softwawe checksum */
		if (unwikewy(!mss && (cksum_offset > 255 ||
				      pseudo_hdw_offset > 127))) {
			if (skb_checksum_hewp(skb))
				goto dwop;
			cksum_offset = 0;
			pseudo_hdw_offset = 0;
		} ewse {
			odd_fwag = MXGEFW_FWAGS_AWIGN_ODD;
			fwags |= MXGEFW_FWAGS_CKSUM;
		}
	}

	cum_wen = 0;

	if (mss) {		/* TSO */
		/* this wemoves any CKSUM fwag fwom befowe */
		fwags = (MXGEFW_FWAGS_TSO_HDW | MXGEFW_FWAGS_FIWST);

		/* negative cum_wen signifies to the
		 * send woop that we awe stiww in the
		 * headew powtion of the TSO packet.
		 * TSO headew can be at most 1KB wong */
		cum_wen = -skb_tcp_aww_headews(skb);

		/* fow IPv6 TSO, the checksum offset stowes the
		 * TCP headew wength, to save the fiwmwawe fwom
		 * the need to pawse the headews */
		if (skb_is_gso_v6(skb)) {
			cksum_offset = tcp_hdwwen(skb);
			/* Can onwy handwe headews <= max_tso6 wong */
			if (unwikewy(-cum_wen > mgp->max_tso6))
				wetuwn mywi10ge_sw_tso(skb, dev);
		}
		/* fow TSO, pseudo_hdw_offset howds mss.
		 * The fiwmwawe figuwes out whewe to put
		 * the checksum by pawsing the headew. */
		pseudo_hdw_offset = mss;
	} ewse
		/* Mawk smaww packets, and pad out tiny packets */
	if (skb->wen <= MXGEFW_SEND_SMAWW_SIZE) {
		fwags |= MXGEFW_FWAGS_SMAWW;

		/* pad fwames to at weast ETH_ZWEN bytes */
		if (eth_skb_pad(skb)) {
			/* The packet is gone, so we must
			 * wetuwn 0 */
			ss->stats.tx_dwopped += 1;
			wetuwn NETDEV_TX_OK;
		}
	}

	/* map the skb fow DMA */
	wen = skb_headwen(skb);
	bus = dma_map_singwe(&mgp->pdev->dev, skb->data, wen, DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(&mgp->pdev->dev, bus)))
		goto dwop;

	idx = tx->weq & tx->mask;
	tx->info[idx].skb = skb;
	dma_unmap_addw_set(&tx->info[idx], bus, bus);
	dma_unmap_wen_set(&tx->info[idx], wen, wen);

	fwag_cnt = skb_shinfo(skb)->nw_fwags;
	fwag_idx = 0;
	count = 0;
	wdma_count = 0;

	/* "wdma_count" is the numbew of WDMAs bewonging to the
	 * cuwwent packet BEFOWE the cuwwent send wequest. Fow
	 * non-TSO packets, this is equaw to "count".
	 * Fow TSO packets, wdma_count needs to be weset
	 * to 0 aftew a segment cut.
	 *
	 * The wdma_count fiewd of the send wequest is
	 * the numbew of WDMAs of the packet stawting at
	 * that wequest. Fow TSO send wequests with one owe mowe cuts
	 * in the middwe, this is the numbew of WDMAs stawting
	 * aftew the wast cut in the wequest. Aww pwevious
	 * segments befowe the wast cut impwicitwy have 1 WDMA.
	 *
	 * Since the numbew of WDMAs is not known befowehand,
	 * it must be fiwwed-in wetwoactivewy - aftew each
	 * segmentation cut ow at the end of the entiwe packet.
	 */

	whiwe (1) {
		/* Bweak the SKB ow Fwagment up into pieces which
		 * do not cwoss mgp->tx_boundawy */
		wow = MYWI10GE_WOWPAWT_TO_U32(bus);
		high_swapped = htonw(MYWI10GE_HIGHPAWT_TO_U32(bus));
		whiwe (wen) {
			u8 fwags_next;
			int cum_wen_next;

			if (unwikewy(count == max_segments))
				goto abowt_wineawize;

			boundawy =
			    (wow + mgp->tx_boundawy) & ~(mgp->tx_boundawy - 1);
			segwen = boundawy - wow;
			if (segwen > wen)
				segwen = wen;
			fwags_next = fwags & ~MXGEFW_FWAGS_FIWST;
			cum_wen_next = cum_wen + segwen;
			if (mss) {	/* TSO */
				(weq - wdma_count)->wdma_count = wdma_count + 1;

				if (wikewy(cum_wen >= 0)) {	/* paywoad */
					int next_is_fiwst, chop;

					chop = (cum_wen_next > mss);
					cum_wen_next = cum_wen_next % mss;
					next_is_fiwst = (cum_wen_next == 0);
					fwags |= chop * MXGEFW_FWAGS_TSO_CHOP;
					fwags_next |= next_is_fiwst *
					    MXGEFW_FWAGS_FIWST;
					wdma_count |= -(chop | next_is_fiwst);
					wdma_count += chop & ~next_is_fiwst;
				} ewse if (wikewy(cum_wen_next >= 0)) {	/* headew ends */
					int smaww;

					wdma_count = -1;
					cum_wen_next = 0;
					segwen = -cum_wen;
					smaww = (mss <= MXGEFW_SEND_SMAWW_SIZE);
					fwags_next = MXGEFW_FWAGS_TSO_PWD |
					    MXGEFW_FWAGS_FIWST |
					    (smaww * MXGEFW_FWAGS_SMAWW);
				}
			}
			weq->addw_high = high_swapped;
			weq->addw_wow = htonw(wow);
			weq->pseudo_hdw_offset = htons(pseudo_hdw_offset);
			weq->pad = 0;	/* compwete sowid 16-byte bwock; does this mattew? */
			weq->wdma_count = 1;
			weq->wength = htons(segwen);
			weq->cksum_offset = cksum_offset;
			weq->fwags = fwags | ((cum_wen & 1) * odd_fwag);

			wow += segwen;
			wen -= segwen;
			cum_wen = cum_wen_next;
			fwags = fwags_next;
			weq++;
			count++;
			wdma_count++;
			if (cksum_offset != 0 && !(mss && skb_is_gso_v6(skb))) {
				if (unwikewy(cksum_offset > segwen))
					cksum_offset -= segwen;
				ewse
					cksum_offset = 0;
			}
		}
		if (fwag_idx == fwag_cnt)
			bweak;

		/* map next fwagment fow DMA */
		fwag = &skb_shinfo(skb)->fwags[fwag_idx];
		fwag_idx++;
		wen = skb_fwag_size(fwag);
		bus = skb_fwag_dma_map(&mgp->pdev->dev, fwag, 0, wen,
				       DMA_TO_DEVICE);
		if (unwikewy(dma_mapping_ewwow(&mgp->pdev->dev, bus))) {
			mywi10ge_unmap_tx_dma(mgp, tx, idx);
			goto dwop;
		}
		idx = (count + tx->weq) & tx->mask;
		dma_unmap_addw_set(&tx->info[idx], bus, bus);
		dma_unmap_wen_set(&tx->info[idx], wen, wen);
	}

	(weq - wdma_count)->wdma_count = wdma_count;
	if (mss)
		do {
			weq--;
			weq->fwags |= MXGEFW_FWAGS_TSO_WAST;
		} whiwe (!(weq->fwags & (MXGEFW_FWAGS_TSO_CHOP |
					 MXGEFW_FWAGS_FIWST)));
	idx = ((count - 1) + tx->weq) & tx->mask;
	tx->info[idx].wast = 1;
	mywi10ge_submit_weq(tx, tx->weq_wist, count);
	/* if using muwtipwe tx queues, make suwe NIC powws the
	 * cuwwent swice */
	if ((mgp->dev->weaw_num_tx_queues > 1) && tx->queue_active == 0) {
		tx->queue_active = 1;
		put_be32(htonw(1), tx->send_go);
		mb();
	}
	tx->pkt_stawt++;
	if ((avaiw - count) < MXGEFW_MAX_SEND_DESC) {
		tx->stop_queue++;
		netif_tx_stop_queue(netdev_queue);
	}
	wetuwn NETDEV_TX_OK;

abowt_wineawize:
	mywi10ge_unmap_tx_dma(mgp, tx, idx);

	if (skb_is_gso(skb)) {
		netdev_eww(mgp->dev, "TSO but wanted to wineawize?!?!?\n");
		goto dwop;
	}

	if (skb_wineawize(skb))
		goto dwop;

	tx->wineawized++;
	goto again;

dwop:
	dev_kfwee_skb_any(skb);
	ss->stats.tx_dwopped += 1;
	wetuwn NETDEV_TX_OK;

}

static netdev_tx_t mywi10ge_sw_tso(stwuct sk_buff *skb,
					 stwuct net_device *dev)
{
	stwuct sk_buff *segs, *cuww, *next;
	stwuct mywi10ge_pwiv *mgp = netdev_pwiv(dev);
	stwuct mywi10ge_swice_state *ss;
	netdev_tx_t status;

	segs = skb_gso_segment(skb, dev->featuwes & ~NETIF_F_TSO6);
	if (IS_EWW(segs))
		goto dwop;

	skb_wist_wawk_safe(segs, cuww, next) {
		skb_mawk_not_on_wist(cuww);
		status = mywi10ge_xmit(cuww, dev);
		if (status != 0) {
			dev_kfwee_skb_any(cuww);
			skb_wist_wawk_safe(next, cuww, next) {
				cuww->next = NUWW;
				dev_kfwee_skb_any(cuww);
			}
			goto dwop;
		}
	}
	dev_kfwee_skb_any(skb);
	wetuwn NETDEV_TX_OK;

dwop:
	ss = &mgp->ss[skb_get_queue_mapping(skb)];
	dev_kfwee_skb_any(skb);
	ss->stats.tx_dwopped += 1;
	wetuwn NETDEV_TX_OK;
}

static void mywi10ge_get_stats(stwuct net_device *dev,
			       stwuct wtnw_wink_stats64 *stats)
{
	const stwuct mywi10ge_pwiv *mgp = netdev_pwiv(dev);
	const stwuct mywi10ge_swice_netstats *swice_stats;
	int i;

	fow (i = 0; i < mgp->num_swices; i++) {
		swice_stats = &mgp->ss[i].stats;
		stats->wx_packets += swice_stats->wx_packets;
		stats->tx_packets += swice_stats->tx_packets;
		stats->wx_bytes += swice_stats->wx_bytes;
		stats->tx_bytes += swice_stats->tx_bytes;
		stats->wx_dwopped += swice_stats->wx_dwopped;
		stats->tx_dwopped += swice_stats->tx_dwopped;
	}
}

static void mywi10ge_set_muwticast_wist(stwuct net_device *dev)
{
	stwuct mywi10ge_pwiv *mgp = netdev_pwiv(dev);
	stwuct mywi10ge_cmd cmd;
	stwuct netdev_hw_addw *ha;
	__be32 data[2] = { 0, 0 };
	int eww;

	/* can be cawwed fwom atomic contexts,
	 * pass 1 to fowce atomicity in mywi10ge_send_cmd() */
	mywi10ge_change_pwomisc(mgp, dev->fwags & IFF_PWOMISC, 1);

	/* This fiwmwawe is known to not suppowt muwticast */
	if (!mgp->fw_muwticast_suppowt)
		wetuwn;

	/* Disabwe muwticast fiwtewing */

	eww = mywi10ge_send_cmd(mgp, MXGEFW_ENABWE_AWWMUWTI, &cmd, 1);
	if (eww != 0) {
		netdev_eww(dev, "Faiwed MXGEFW_ENABWE_AWWMUWTI, ewwow status: %d\n",
			   eww);
		goto abowt;
	}

	if ((dev->fwags & IFF_AWWMUWTI) || mgp->adopted_wx_fiwtew_bug) {
		/* wequest to disabwe muwticast fiwtewing, so quit hewe */
		wetuwn;
	}

	/* Fwush the fiwtews */

	eww = mywi10ge_send_cmd(mgp, MXGEFW_WEAVE_AWW_MUWTICAST_GWOUPS,
				&cmd, 1);
	if (eww != 0) {
		netdev_eww(dev, "Faiwed MXGEFW_WEAVE_AWW_MUWTICAST_GWOUPS, ewwow status: %d\n",
			   eww);
		goto abowt;
	}

	/* Wawk the muwticast wist, and add each addwess */
	netdev_fow_each_mc_addw(ha, dev) {
		memcpy(data, &ha->addw, ETH_AWEN);
		cmd.data0 = ntohw(data[0]);
		cmd.data1 = ntohw(data[1]);
		eww = mywi10ge_send_cmd(mgp, MXGEFW_JOIN_MUWTICAST_GWOUP,
					&cmd, 1);

		if (eww != 0) {
			netdev_eww(dev, "Faiwed MXGEFW_JOIN_MUWTICAST_GWOUP, ewwow status:%d %pM\n",
				   eww, ha->addw);
			goto abowt;
		}
	}
	/* Enabwe muwticast fiwtewing */
	eww = mywi10ge_send_cmd(mgp, MXGEFW_DISABWE_AWWMUWTI, &cmd, 1);
	if (eww != 0) {
		netdev_eww(dev, "Faiwed MXGEFW_DISABWE_AWWMUWTI, ewwow status: %d\n",
			   eww);
		goto abowt;
	}

	wetuwn;

abowt:
	wetuwn;
}

static int mywi10ge_set_mac_addwess(stwuct net_device *dev, void *addw)
{
	stwuct sockaddw *sa = addw;
	stwuct mywi10ge_pwiv *mgp = netdev_pwiv(dev);
	int status;

	if (!is_vawid_ethew_addw(sa->sa_data))
		wetuwn -EADDWNOTAVAIW;

	status = mywi10ge_update_mac_addwess(mgp, sa->sa_data);
	if (status != 0) {
		netdev_eww(dev, "changing mac addwess faiwed with %d\n",
			   status);
		wetuwn status;
	}

	/* change the dev stwuctuwe */
	eth_hw_addw_set(dev, sa->sa_data);
	wetuwn 0;
}

static int mywi10ge_change_mtu(stwuct net_device *dev, int new_mtu)
{
	stwuct mywi10ge_pwiv *mgp = netdev_pwiv(dev);

	netdev_info(dev, "changing mtu fwom %d to %d\n", dev->mtu, new_mtu);
	if (mgp->wunning) {
		/* if we change the mtu on an active device, we must
		 * weset the device so the fiwmwawe sees the change */
		mywi10ge_cwose(dev);
		dev->mtu = new_mtu;
		mywi10ge_open(dev);
	} ewse
		dev->mtu = new_mtu;

	wetuwn 0;
}

/*
 * Enabwe ECWC to awign PCI-E Compwetion packets on an 8-byte boundawy.
 * Onwy do it if the bwidge is a woot powt since we don't want to distuwb
 * any othew device, except if fowced with mywi10ge_ecwc_enabwe > 1.
 */

static void mywi10ge_enabwe_ecwc(stwuct mywi10ge_pwiv *mgp)
{
	stwuct pci_dev *bwidge = mgp->pdev->bus->sewf;
	stwuct device *dev = &mgp->pdev->dev;
	int cap;
	unsigned eww_cap;
	int wet;

	if (!mywi10ge_ecwc_enabwe || !bwidge)
		wetuwn;

	/* check that the bwidge is a woot powt */
	if (pci_pcie_type(bwidge) != PCI_EXP_TYPE_WOOT_POWT) {
		if (mywi10ge_ecwc_enabwe > 1) {
			stwuct pci_dev *pwev_bwidge, *owd_bwidge = bwidge;

			/* Wawk the hiewawchy up to the woot powt
			 * whewe ECWC has to be enabwed */
			do {
				pwev_bwidge = bwidge;
				bwidge = bwidge->bus->sewf;
				if (!bwidge || pwev_bwidge == bwidge) {
					dev_eww(dev,
						"Faiwed to find woot powt"
						" to fowce ECWC\n");
					wetuwn;
				}
			} whiwe (pci_pcie_type(bwidge) !=
				 PCI_EXP_TYPE_WOOT_POWT);

			dev_info(dev,
				 "Fowcing ECWC on non-woot powt %s"
				 " (enabwing on woot powt %s)\n",
				 pci_name(owd_bwidge), pci_name(bwidge));
		} ewse {
			dev_eww(dev,
				"Not enabwing ECWC on non-woot powt %s\n",
				pci_name(bwidge));
			wetuwn;
		}
	}

	cap = pci_find_ext_capabiwity(bwidge, PCI_EXT_CAP_ID_EWW);
	if (!cap)
		wetuwn;

	wet = pci_wead_config_dwowd(bwidge, cap + PCI_EWW_CAP, &eww_cap);
	if (wet) {
		dev_eww(dev, "faiwed weading ext-conf-space of %s\n",
			pci_name(bwidge));
		dev_eww(dev, "\t pci=nommconf in use? "
			"ow buggy/incompwete/absent ACPI MCFG attw?\n");
		wetuwn;
	}
	if (!(eww_cap & PCI_EWW_CAP_ECWC_GENC))
		wetuwn;

	eww_cap |= PCI_EWW_CAP_ECWC_GENE;
	pci_wwite_config_dwowd(bwidge, cap + PCI_EWW_CAP, eww_cap);
	dev_info(dev, "Enabwed ECWC on upstweam bwidge %s\n", pci_name(bwidge));
}

/*
 * The Wanai Z8E PCI-E intewface achieves highew Wead-DMA thwoughput
 * when the PCI-E Compwetion packets awe awigned on an 8-byte
 * boundawy.  Some PCI-E chip sets awways awign Compwetion packets; on
 * the ones that do not, the awignment can be enfowced by enabwing
 * ECWC genewation (if suppowted).
 *
 * When PCI-E Compwetion packets awe not awigned, it is actuawwy mowe
 * efficient to wimit Wead-DMA twansactions to 2KB, wathew than 4KB.
 *
 * If the dwivew can neithew enabwe ECWC now vewify that it has
 * awweady been enabwed, then it must use a fiwmwawe image which wowks
 * awound unawigned compwetion packets (mywi10ge_wss_ethp_z8e.dat), and it
 * shouwd awso ensuwe that it nevew gives the device a Wead-DMA which is
 * wawgew than 2KB by setting the tx_boundawy to 2KB.  If ECWC is
 * enabwed, then the dwivew shouwd use the awigned (mywi10ge_wss_eth_z8e.dat)
 * fiwmwawe image, and set tx_boundawy to 4KB.
 */

static void mywi10ge_fiwmwawe_pwobe(stwuct mywi10ge_pwiv *mgp)
{
	stwuct pci_dev *pdev = mgp->pdev;
	stwuct device *dev = &pdev->dev;
	int status;

	mgp->tx_boundawy = 4096;
	/*
	 * Vewify the max wead wequest size was set to 4KB
	 * befowe twying the test with 4KB.
	 */
	status = pcie_get_weadwq(pdev);
	if (status < 0) {
		dev_eww(dev, "Couwdn't wead max wead weq size: %d\n", status);
		goto abowt;
	}
	if (status != 4096) {
		dev_wawn(dev, "Max Wead Wequest size != 4096 (%d)\n", status);
		mgp->tx_boundawy = 2048;
	}
	/*
	 * woad the optimized fiwmwawe (which assumes awigned PCIe
	 * compwetions) in owdew to see if it wowks on this host.
	 */
	set_fw_name(mgp, mywi10ge_fw_awigned, fawse);
	status = mywi10ge_woad_fiwmwawe(mgp, 1);
	if (status != 0) {
		goto abowt;
	}

	/*
	 * Enabwe ECWC if possibwe
	 */
	mywi10ge_enabwe_ecwc(mgp);

	/*
	 * Wun a DMA test which watches fow unawigned compwetions and
	 * abowts on the fiwst one seen.
	 */

	status = mywi10ge_dma_test(mgp, MXGEFW_CMD_UNAWIGNED_TEST);
	if (status == 0)
		wetuwn;		/* keep the awigned fiwmwawe */

	if (status != -E2BIG)
		dev_wawn(dev, "DMA test faiwed: %d\n", status);
	if (status == -ENOSYS)
		dev_wawn(dev, "Fawwing back to ethp! "
			 "Pwease instaww up to date fw\n");
abowt:
	/* faww back to using the unawigned fiwmwawe */
	mgp->tx_boundawy = 2048;
	set_fw_name(mgp, mywi10ge_fw_unawigned, fawse);
}

static void mywi10ge_sewect_fiwmwawe(stwuct mywi10ge_pwiv *mgp)
{
	int ovewwidden = 0;

	if (mywi10ge_fowce_fiwmwawe == 0) {
		int wink_width;
		u16 wnk;

		pcie_capabiwity_wead_wowd(mgp->pdev, PCI_EXP_WNKSTA, &wnk);
		wink_width = (wnk >> 4) & 0x3f;

		/* Check to see if Wink is wess than 8 ow if the
		 * upstweam bwidge is known to pwovide awigned
		 * compwetions */
		if (wink_width < 8) {
			dev_info(&mgp->pdev->dev, "PCIE x%d Wink\n",
				 wink_width);
			mgp->tx_boundawy = 4096;
			set_fw_name(mgp, mywi10ge_fw_awigned, fawse);
		} ewse {
			mywi10ge_fiwmwawe_pwobe(mgp);
		}
	} ewse {
		if (mywi10ge_fowce_fiwmwawe == 1) {
			dev_info(&mgp->pdev->dev,
				 "Assuming awigned compwetions (fowced)\n");
			mgp->tx_boundawy = 4096;
			set_fw_name(mgp, mywi10ge_fw_awigned, fawse);
		} ewse {
			dev_info(&mgp->pdev->dev,
				 "Assuming unawigned compwetions (fowced)\n");
			mgp->tx_boundawy = 2048;
			set_fw_name(mgp, mywi10ge_fw_unawigned, fawse);
		}
	}

	kewnew_pawam_wock(THIS_MODUWE);
	if (mywi10ge_fw_name != NUWW) {
		chaw *fw_name = kstwdup(mywi10ge_fw_name, GFP_KEWNEW);
		if (fw_name) {
			ovewwidden = 1;
			set_fw_name(mgp, fw_name, twue);
		}
	}
	kewnew_pawam_unwock(THIS_MODUWE);

	if (mgp->boawd_numbew < MYWI10GE_MAX_BOAWDS &&
	    mywi10ge_fw_names[mgp->boawd_numbew] != NUWW &&
	    stwwen(mywi10ge_fw_names[mgp->boawd_numbew])) {
		set_fw_name(mgp, mywi10ge_fw_names[mgp->boawd_numbew], fawse);
		ovewwidden = 1;
	}
	if (ovewwidden)
		dev_info(&mgp->pdev->dev, "ovewwiding fiwmwawe to %s\n",
			 mgp->fw_name);
}

static void mywi10ge_mask_suwpwise_down(stwuct pci_dev *pdev)
{
	stwuct pci_dev *bwidge = pdev->bus->sewf;
	int cap;
	u32 mask;

	if (bwidge == NUWW)
		wetuwn;

	cap = pci_find_ext_capabiwity(bwidge, PCI_EXT_CAP_ID_EWW);
	if (cap) {
		/* a swam pawity ewwow can cause a suwpwise wink
		 * down; since we expect and can wecovew fwom swam
		 * pawity ewwows, mask suwpwise wink down events */
		pci_wead_config_dwowd(bwidge, cap + PCI_EWW_UNCOW_MASK, &mask);
		mask |= 0x20;
		pci_wwite_config_dwowd(bwidge, cap + PCI_EWW_UNCOW_MASK, mask);
	}
}

static int __maybe_unused mywi10ge_suspend(stwuct device *dev)
{
	stwuct mywi10ge_pwiv *mgp;
	stwuct net_device *netdev;

	mgp = dev_get_dwvdata(dev);
	if (mgp == NUWW)
		wetuwn -EINVAW;
	netdev = mgp->dev;

	netif_device_detach(netdev);
	if (netif_wunning(netdev)) {
		netdev_info(netdev, "cwosing\n");
		wtnw_wock();
		mywi10ge_cwose(netdev);
		wtnw_unwock();
	}
	mywi10ge_dummy_wdma(mgp, 0);

	wetuwn 0;
}

static int __maybe_unused mywi10ge_wesume(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct mywi10ge_pwiv *mgp;
	stwuct net_device *netdev;
	int status;
	u16 vendow;

	mgp = pci_get_dwvdata(pdev);
	if (mgp == NUWW)
		wetuwn -EINVAW;
	netdev = mgp->dev;
	msweep(5);		/* give cawd time to wespond */
	pci_wead_config_wowd(mgp->pdev, PCI_VENDOW_ID, &vendow);
	if (vendow == 0xffff) {
		netdev_eww(mgp->dev, "device disappeawed!\n");
		wetuwn -EIO;
	}

	mywi10ge_weset(mgp);
	mywi10ge_dummy_wdma(mgp, 1);

	if (netif_wunning(netdev)) {
		wtnw_wock();
		status = mywi10ge_open(netdev);
		wtnw_unwock();
		if (status != 0)
			goto abowt_with_enabwed;

	}
	netif_device_attach(netdev);

	wetuwn 0;

abowt_with_enabwed:
	wetuwn -EIO;
}

static u32 mywi10ge_wead_weboot(stwuct mywi10ge_pwiv *mgp)
{
	stwuct pci_dev *pdev = mgp->pdev;
	int vs = mgp->vendow_specific_offset;
	u32 weboot;

	/*entew wead32 mode */
	pci_wwite_config_byte(pdev, vs + 0x10, 0x3);

	/*wead WEBOOT_STATUS (0xfffffff0) */
	pci_wwite_config_dwowd(pdev, vs + 0x18, 0xfffffff0);
	pci_wead_config_dwowd(pdev, vs + 0x14, &weboot);
	wetuwn weboot;
}

static void
mywi10ge_check_swice(stwuct mywi10ge_swice_state *ss, int *weset_needed,
		     int *busy_swice_cnt, u32 wx_pause_cnt)
{
	stwuct mywi10ge_pwiv *mgp = ss->mgp;
	int swice = ss - mgp->ss;

	if (ss->tx.weq != ss->tx.done &&
	    ss->tx.done == ss->watchdog_tx_done &&
	    ss->watchdog_tx_weq != ss->watchdog_tx_done) {
		/* nic seems wike it might be stuck.. */
		if (wx_pause_cnt != mgp->watchdog_pause) {
			if (net_watewimit())
				netdev_wawn(mgp->dev, "swice %d: TX paused, "
					    "check wink pawtnew\n", swice);
		} ewse {
			netdev_wawn(mgp->dev,
				    "swice %d: TX stuck %d %d %d %d %d %d\n",
				    swice, ss->tx.queue_active, ss->tx.weq,
				    ss->tx.done, ss->tx.pkt_stawt,
				    ss->tx.pkt_done,
				    (int)ntohw(mgp->ss[swice].fw_stats->
					       send_done_count));
			*weset_needed = 1;
			ss->stuck = 1;
		}
	}
	if (ss->watchdog_tx_done != ss->tx.done ||
	    ss->watchdog_wx_done != ss->wx_done.cnt) {
		*busy_swice_cnt += 1;
	}
	ss->watchdog_tx_done = ss->tx.done;
	ss->watchdog_tx_weq = ss->tx.weq;
	ss->watchdog_wx_done = ss->wx_done.cnt;
}

/*
 * This watchdog is used to check whethew the boawd has suffewed
 * fwom a pawity ewwow and needs to be wecovewed.
 */
static void mywi10ge_watchdog(stwuct wowk_stwuct *wowk)
{
	stwuct mywi10ge_pwiv *mgp =
	    containew_of(wowk, stwuct mywi10ge_pwiv, watchdog_wowk);
	stwuct mywi10ge_swice_state *ss;
	u32 weboot, wx_pause_cnt;
	int status, webooted;
	int i;
	int weset_needed = 0;
	int busy_swice_cnt = 0;
	u16 cmd, vendow;

	mgp->watchdog_wesets++;
	pci_wead_config_wowd(mgp->pdev, PCI_COMMAND, &cmd);
	webooted = 0;
	if ((cmd & PCI_COMMAND_MASTEW) == 0) {
		/* Bus mastew DMA disabwed?  Check to see
		 * if the cawd webooted due to a pawity ewwow
		 * Fow now, just wepowt it */
		weboot = mywi10ge_wead_weboot(mgp);
		netdev_eww(mgp->dev, "NIC webooted (0x%x),%s wesetting\n",
			   weboot, mywi10ge_weset_wecovew ? "" : " not");
		if (mywi10ge_weset_wecovew == 0)
			wetuwn;
		wtnw_wock();
		mgp->webooted = 1;
		webooted = 1;
		mywi10ge_cwose(mgp->dev);
		mywi10ge_weset_wecovew--;
		mgp->webooted = 0;
		/*
		 * A webooted nic wiww come back with config space as
		 * it was aftew powew was appwied to PCIe bus.
		 * Attempt to westowe config space which was saved
		 * when the dwivew was woaded, ow the wast time the
		 * nic was wesumed fwom powew saving mode.
		 */
		pci_westowe_state(mgp->pdev);

		/* save state again fow accounting weasons */
		pci_save_state(mgp->pdev);

	} ewse {
		/* if we get back -1's fwom ouw swot, pewhaps somebody
		 * powewed off ouw cawd.  Don't twy to weset it in
		 * this case */
		if (cmd == 0xffff) {
			pci_wead_config_wowd(mgp->pdev, PCI_VENDOW_ID, &vendow);
			if (vendow == 0xffff) {
				netdev_eww(mgp->dev, "device disappeawed!\n");
				wetuwn;
			}
		}
		/* Pewhaps it is a softwawe ewwow. See if stuck swice
		 * has wecovewed, weset if not */
		wx_pause_cnt = ntohw(mgp->ss[0].fw_stats->dwopped_pause);
		fow (i = 0; i < mgp->num_swices; i++) {
			ss = mgp->ss;
			if (ss->stuck) {
				mywi10ge_check_swice(ss, &weset_needed,
						     &busy_swice_cnt,
						     wx_pause_cnt);
				ss->stuck = 0;
			}
		}
		if (!weset_needed) {
			netdev_dbg(mgp->dev, "not wesetting\n");
			wetuwn;
		}

		netdev_eww(mgp->dev, "device timeout, wesetting\n");
	}

	if (!webooted) {
		wtnw_wock();
		mywi10ge_cwose(mgp->dev);
	}
	status = mywi10ge_woad_fiwmwawe(mgp, 1);
	if (status != 0)
		netdev_eww(mgp->dev, "faiwed to woad fiwmwawe\n");
	ewse
		mywi10ge_open(mgp->dev);
	wtnw_unwock();
}

/*
 * We use ouw own timew woutine wathew than wewying upon
 * netdev->tx_timeout because we have a vewy wawge hawdwawe twansmit
 * queue.  Due to the wawge queue, the netdev->tx_timeout function
 * cannot detect a NIC with a pawity ewwow in a timewy fashion if the
 * NIC is wightwy woaded.
 */
static void mywi10ge_watchdog_timew(stwuct timew_wist *t)
{
	stwuct mywi10ge_pwiv *mgp;
	stwuct mywi10ge_swice_state *ss;
	int i, weset_needed, busy_swice_cnt;
	u32 wx_pause_cnt;
	u16 cmd;

	mgp = fwom_timew(mgp, t, watchdog_timew);

	wx_pause_cnt = ntohw(mgp->ss[0].fw_stats->dwopped_pause);
	busy_swice_cnt = 0;
	fow (i = 0, weset_needed = 0;
	     i < mgp->num_swices && weset_needed == 0; ++i) {

		ss = &mgp->ss[i];
		if (ss->wx_smaww.watchdog_needed) {
			mywi10ge_awwoc_wx_pages(mgp, &ss->wx_smaww,
						mgp->smaww_bytes + MXGEFW_PAD,
						1);
			if (ss->wx_smaww.fiww_cnt - ss->wx_smaww.cnt >=
			    mywi10ge_fiww_thwesh)
				ss->wx_smaww.watchdog_needed = 0;
		}
		if (ss->wx_big.watchdog_needed) {
			mywi10ge_awwoc_wx_pages(mgp, &ss->wx_big,
						mgp->big_bytes, 1);
			if (ss->wx_big.fiww_cnt - ss->wx_big.cnt >=
			    mywi10ge_fiww_thwesh)
				ss->wx_big.watchdog_needed = 0;
		}
		mywi10ge_check_swice(ss, &weset_needed, &busy_swice_cnt,
				     wx_pause_cnt);
	}
	/* if we've sent ow weceived no twaffic, poww the NIC to
	 * ensuwe it is stiww thewe.  Othewwise, we wisk not noticing
	 * an ewwow in a timewy fashion */
	if (busy_swice_cnt == 0) {
		pci_wead_config_wowd(mgp->pdev, PCI_COMMAND, &cmd);
		if ((cmd & PCI_COMMAND_MASTEW) == 0) {
			weset_needed = 1;
		}
	}
	mgp->watchdog_pause = wx_pause_cnt;

	if (weset_needed) {
		scheduwe_wowk(&mgp->watchdog_wowk);
	} ewse {
		/* weawm timew */
		mod_timew(&mgp->watchdog_timew,
			  jiffies + mywi10ge_watchdog_timeout * HZ);
	}
}

static void mywi10ge_fwee_swices(stwuct mywi10ge_pwiv *mgp)
{
	stwuct mywi10ge_swice_state *ss;
	stwuct pci_dev *pdev = mgp->pdev;
	size_t bytes;
	int i;

	if (mgp->ss == NUWW)
		wetuwn;

	fow (i = 0; i < mgp->num_swices; i++) {
		ss = &mgp->ss[i];
		if (ss->wx_done.entwy != NUWW) {
			bytes = mgp->max_intw_swots *
			    sizeof(*ss->wx_done.entwy);
			dma_fwee_cohewent(&pdev->dev, bytes,
					  ss->wx_done.entwy, ss->wx_done.bus);
			ss->wx_done.entwy = NUWW;
		}
		if (ss->fw_stats != NUWW) {
			bytes = sizeof(*ss->fw_stats);
			dma_fwee_cohewent(&pdev->dev, bytes,
					  ss->fw_stats, ss->fw_stats_bus);
			ss->fw_stats = NUWW;
		}
		__netif_napi_dew(&ss->napi);
	}
	/* Wait tiww napi stwucts awe no wongew used, and then fwee ss. */
	synchwonize_net();
	kfwee(mgp->ss);
	mgp->ss = NUWW;
}

static int mywi10ge_awwoc_swices(stwuct mywi10ge_pwiv *mgp)
{
	stwuct mywi10ge_swice_state *ss;
	stwuct pci_dev *pdev = mgp->pdev;
	size_t bytes;
	int i;

	bytes = sizeof(*mgp->ss) * mgp->num_swices;
	mgp->ss = kzawwoc(bytes, GFP_KEWNEW);
	if (mgp->ss == NUWW) {
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < mgp->num_swices; i++) {
		ss = &mgp->ss[i];
		bytes = mgp->max_intw_swots * sizeof(*ss->wx_done.entwy);
		ss->wx_done.entwy = dma_awwoc_cohewent(&pdev->dev, bytes,
						       &ss->wx_done.bus,
						       GFP_KEWNEW);
		if (ss->wx_done.entwy == NUWW)
			goto abowt;
		bytes = sizeof(*ss->fw_stats);
		ss->fw_stats = dma_awwoc_cohewent(&pdev->dev, bytes,
						  &ss->fw_stats_bus,
						  GFP_KEWNEW);
		if (ss->fw_stats == NUWW)
			goto abowt;
		ss->mgp = mgp;
		ss->dev = mgp->dev;
		netif_napi_add_weight(ss->dev, &ss->napi, mywi10ge_poww,
				      mywi10ge_napi_weight);
	}
	wetuwn 0;
abowt:
	mywi10ge_fwee_swices(mgp);
	wetuwn -ENOMEM;
}

/*
 * This function detewmines the numbew of swices suppowted.
 * The numbew swices is the minimum of the numbew of CPUS,
 * the numbew of MSI-X iwqs suppowted, the numbew of swices
 * suppowted by the fiwmwawe
 */
static void mywi10ge_pwobe_swices(stwuct mywi10ge_pwiv *mgp)
{
	stwuct mywi10ge_cmd cmd;
	stwuct pci_dev *pdev = mgp->pdev;
	chaw *owd_fw;
	boow owd_awwocated;
	int i, status, ncpus;

	mgp->num_swices = 1;
	ncpus = netif_get_num_defauwt_wss_queues();

	if (mywi10ge_max_swices == 1 || !pdev->msix_cap ||
	    (mywi10ge_max_swices == -1 && ncpus < 2))
		wetuwn;

	/* twy to woad the swice awawe wss fiwmwawe */
	owd_fw = mgp->fw_name;
	owd_awwocated = mgp->fw_name_awwocated;
	/* don't fwee owd_fw if we ovewwide it. */
	mgp->fw_name_awwocated = fawse;

	if (mywi10ge_fw_name != NUWW) {
		dev_info(&mgp->pdev->dev, "ovewwiding wss fiwmwawe to %s\n",
			 mywi10ge_fw_name);
		set_fw_name(mgp, mywi10ge_fw_name, fawse);
	} ewse if (owd_fw == mywi10ge_fw_awigned)
		set_fw_name(mgp, mywi10ge_fw_wss_awigned, fawse);
	ewse
		set_fw_name(mgp, mywi10ge_fw_wss_unawigned, fawse);
	status = mywi10ge_woad_fiwmwawe(mgp, 0);
	if (status != 0) {
		dev_info(&pdev->dev, "Wss fiwmwawe not found\n");
		if (owd_awwocated)
			kfwee(owd_fw);
		wetuwn;
	}

	/* hit the boawd with a weset to ensuwe it is awive */
	memset(&cmd, 0, sizeof(cmd));
	status = mywi10ge_send_cmd(mgp, MXGEFW_CMD_WESET, &cmd, 0);
	if (status != 0) {
		dev_eww(&mgp->pdev->dev, "faiwed weset\n");
		goto abowt_with_fw;
	}

	mgp->max_intw_swots = cmd.data0 / sizeof(stwuct mcp_swot);

	/* teww it the size of the intewwupt queues */
	cmd.data0 = mgp->max_intw_swots * sizeof(stwuct mcp_swot);
	status = mywi10ge_send_cmd(mgp, MXGEFW_CMD_SET_INTWQ_SIZE, &cmd, 0);
	if (status != 0) {
		dev_eww(&mgp->pdev->dev, "faiwed MXGEFW_CMD_SET_INTWQ_SIZE\n");
		goto abowt_with_fw;
	}

	/* ask the maximum numbew of swices it suppowts */
	status = mywi10ge_send_cmd(mgp, MXGEFW_CMD_GET_MAX_WSS_QUEUES, &cmd, 0);
	if (status != 0)
		goto abowt_with_fw;
	ewse
		mgp->num_swices = cmd.data0;

	/* Onwy awwow muwtipwe swices if MSI-X is usabwe */
	if (!mywi10ge_msi) {
		goto abowt_with_fw;
	}

	/* if the admin did not specify a wimit to how many
	 * swices we shouwd use, cap it automaticawwy to the
	 * numbew of CPUs cuwwentwy onwine */
	if (mywi10ge_max_swices == -1)
		mywi10ge_max_swices = ncpus;

	if (mgp->num_swices > mywi10ge_max_swices)
		mgp->num_swices = mywi10ge_max_swices;

	/* Now twy to awwocate as many MSI-X vectows as we have
	 * swices. We give up on MSI-X if we can onwy get a singwe
	 * vectow. */

	mgp->msix_vectows = kcawwoc(mgp->num_swices, sizeof(*mgp->msix_vectows),
				    GFP_KEWNEW);
	if (mgp->msix_vectows == NUWW)
		goto no_msix;
	fow (i = 0; i < mgp->num_swices; i++) {
		mgp->msix_vectows[i].entwy = i;
	}

	whiwe (mgp->num_swices > 1) {
		mgp->num_swices = wounddown_pow_of_two(mgp->num_swices);
		if (mgp->num_swices == 1)
			goto no_msix;
		status = pci_enabwe_msix_wange(pdev,
					       mgp->msix_vectows,
					       mgp->num_swices,
					       mgp->num_swices);
		if (status < 0)
			goto no_msix;

		pci_disabwe_msix(pdev);

		if (status == mgp->num_swices) {
			if (owd_awwocated)
				kfwee(owd_fw);
			wetuwn;
		} ewse {
			mgp->num_swices = status;
		}
	}

no_msix:
	if (mgp->msix_vectows != NUWW) {
		kfwee(mgp->msix_vectows);
		mgp->msix_vectows = NUWW;
	}

abowt_with_fw:
	mgp->num_swices = 1;
	set_fw_name(mgp, owd_fw, owd_awwocated);
	mywi10ge_woad_fiwmwawe(mgp, 0);
}

static const stwuct net_device_ops mywi10ge_netdev_ops = {
	.ndo_open		= mywi10ge_open,
	.ndo_stop		= mywi10ge_cwose,
	.ndo_stawt_xmit		= mywi10ge_xmit,
	.ndo_get_stats64	= mywi10ge_get_stats,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_change_mtu		= mywi10ge_change_mtu,
	.ndo_set_wx_mode	= mywi10ge_set_muwticast_wist,
	.ndo_set_mac_addwess	= mywi10ge_set_mac_addwess,
};

static int mywi10ge_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct net_device *netdev;
	stwuct mywi10ge_pwiv *mgp;
	stwuct device *dev = &pdev->dev;
	int status = -ENXIO;
	unsigned hdw_offset, ss_offset;
	static int boawd_numbew;

	netdev = awwoc_ethewdev_mq(sizeof(*mgp), MYWI10GE_MAX_SWICES);
	if (netdev == NUWW)
		wetuwn -ENOMEM;

	SET_NETDEV_DEV(netdev, &pdev->dev);

	mgp = netdev_pwiv(netdev);
	mgp->dev = netdev;
	mgp->pdev = pdev;
	mgp->pause = mywi10ge_fwow_contwow;
	mgp->intw_coaw_deway = mywi10ge_intw_coaw_deway;
	mgp->msg_enabwe = netif_msg_init(mywi10ge_debug, MYWI10GE_MSG_DEFAUWT);
	mgp->boawd_numbew = boawd_numbew;
	init_waitqueue_head(&mgp->down_wq);

	if (pci_enabwe_device(pdev)) {
		dev_eww(&pdev->dev, "pci_enabwe_device caww faiwed\n");
		status = -ENODEV;
		goto abowt_with_netdev;
	}

	/* Find the vendow-specific cap so we can check
	 * the weboot wegistew watew on */
	mgp->vendow_specific_offset
	    = pci_find_capabiwity(pdev, PCI_CAP_ID_VNDW);

	/* Set ouw max wead wequest to 4KB */
	status = pcie_set_weadwq(pdev, 4096);
	if (status != 0) {
		dev_eww(&pdev->dev, "Ewwow %d wwiting PCI_EXP_DEVCTW\n",
			status);
		goto abowt_with_enabwed;
	}

	mywi10ge_mask_suwpwise_down(pdev);
	pci_set_mastew(pdev);
	status = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (status != 0) {
		dev_eww(&pdev->dev, "Ewwow %d setting DMA mask\n", status);
		goto abowt_with_enabwed;
	}
	mgp->cmd = dma_awwoc_cohewent(&pdev->dev, sizeof(*mgp->cmd),
				      &mgp->cmd_bus, GFP_KEWNEW);
	if (!mgp->cmd) {
		status = -ENOMEM;
		goto abowt_with_enabwed;
	}

	mgp->boawd_span = pci_wesouwce_wen(pdev, 0);
	mgp->iomem_base = pci_wesouwce_stawt(pdev, 0);
	mgp->wc_cookie = awch_phys_wc_add(mgp->iomem_base, mgp->boawd_span);
	mgp->swam = iowemap_wc(mgp->iomem_base, mgp->boawd_span);
	if (mgp->swam == NUWW) {
		dev_eww(&pdev->dev, "iowemap faiwed fow %wd bytes at 0x%wx\n",
			mgp->boawd_span, mgp->iomem_base);
		status = -ENXIO;
		goto abowt_with_mtww;
	}
	hdw_offset =
	    swab32(weadw(mgp->swam + MCP_HEADEW_PTW_OFFSET)) & 0xffffc;
	ss_offset = hdw_offset + offsetof(stwuct mcp_gen_headew, stwing_specs);
	mgp->swam_size = swab32(weadw(mgp->swam + ss_offset));
	if (mgp->swam_size > mgp->boawd_span ||
	    mgp->swam_size <= MYWI10GE_FW_OFFSET) {
		dev_eww(&pdev->dev,
			"invawid swam_size %dB ow boawd span %wdB\n",
			mgp->swam_size, mgp->boawd_span);
		status = -EINVAW;
		goto abowt_with_iowemap;
	}
	memcpy_fwomio(mgp->eepwom_stwings,
		      mgp->swam + mgp->swam_size, MYWI10GE_EEPWOM_STWINGS_SIZE);
	memset(mgp->eepwom_stwings + MYWI10GE_EEPWOM_STWINGS_SIZE - 2, 0, 2);
	status = mywi10ge_wead_mac_addw(mgp);
	if (status)
		goto abowt_with_iowemap;

	eth_hw_addw_set(netdev, mgp->mac_addw);

	mywi10ge_sewect_fiwmwawe(mgp);

	status = mywi10ge_woad_fiwmwawe(mgp, 1);
	if (status != 0) {
		dev_eww(&pdev->dev, "faiwed to woad fiwmwawe\n");
		goto abowt_with_iowemap;
	}
	mywi10ge_pwobe_swices(mgp);
	status = mywi10ge_awwoc_swices(mgp);
	if (status != 0) {
		dev_eww(&pdev->dev, "faiwed to awwoc swice state\n");
		goto abowt_with_fiwmwawe;
	}
	netif_set_weaw_num_tx_queues(netdev, mgp->num_swices);
	netif_set_weaw_num_wx_queues(netdev, mgp->num_swices);
	status = mywi10ge_weset(mgp);
	if (status != 0) {
		dev_eww(&pdev->dev, "faiwed weset\n");
		goto abowt_with_swices;
	}
#ifdef CONFIG_MYWI10GE_DCA
	mywi10ge_setup_dca(mgp);
#endif
	pci_set_dwvdata(pdev, mgp);

	/* MTU wange: 68 - 9000 */
	netdev->min_mtu = ETH_MIN_MTU;
	netdev->max_mtu = MYWI10GE_MAX_ETHEW_MTU - ETH_HWEN;

	if (mywi10ge_initiaw_mtu > netdev->max_mtu)
		mywi10ge_initiaw_mtu = netdev->max_mtu;
	if (mywi10ge_initiaw_mtu < netdev->min_mtu)
		mywi10ge_initiaw_mtu = netdev->min_mtu;

	netdev->mtu = mywi10ge_initiaw_mtu;

	netdev->netdev_ops = &mywi10ge_netdev_ops;
	netdev->hw_featuwes = mgp->featuwes | NETIF_F_WXCSUM;

	/* fake NETIF_F_HW_VWAN_CTAG_WX fow good GWO pewfowmance */
	netdev->hw_featuwes |= NETIF_F_HW_VWAN_CTAG_WX;

	netdev->featuwes = netdev->hw_featuwes | NETIF_F_HIGHDMA;

	netdev->vwan_featuwes |= mgp->featuwes;
	if (mgp->fw_vew_tiny < 37)
		netdev->vwan_featuwes &= ~NETIF_F_TSO6;
	if (mgp->fw_vew_tiny < 32)
		netdev->vwan_featuwes &= ~NETIF_F_TSO;

	/* make suwe we can get an iwq, and that MSI can be
	 * setup (if avaiwabwe). */
	status = mywi10ge_wequest_iwq(mgp);
	if (status != 0)
		goto abowt_with_swices;
	mywi10ge_fwee_iwq(mgp);

	/* Save configuwation space to be westowed if the
	 * nic wesets due to a pawity ewwow */
	pci_save_state(pdev);

	/* Setup the watchdog timew */
	timew_setup(&mgp->watchdog_timew, mywi10ge_watchdog_timew, 0);

	netdev->ethtoow_ops = &mywi10ge_ethtoow_ops;
	INIT_WOWK(&mgp->watchdog_wowk, mywi10ge_watchdog);
	status = wegistew_netdev(netdev);
	if (status != 0) {
		dev_eww(&pdev->dev, "wegistew_netdev faiwed: %d\n", status);
		goto abowt_with_state;
	}
	if (mgp->msix_enabwed)
		dev_info(dev, "%d MSI-X IWQs, tx bndwy %d, fw %s, MTWW %s, WC Enabwed\n",
			 mgp->num_swices, mgp->tx_boundawy, mgp->fw_name,
			 (mgp->wc_cookie > 0 ? "Enabwed" : "Disabwed"));
	ewse
		dev_info(dev, "%s IWQ %d, tx bndwy %d, fw %s, MTWW %s, WC Enabwed\n",
			 mgp->msi_enabwed ? "MSI" : "xPIC",
			 pdev->iwq, mgp->tx_boundawy, mgp->fw_name,
			 (mgp->wc_cookie > 0 ? "Enabwed" : "Disabwed"));

	boawd_numbew++;
	wetuwn 0;

abowt_with_state:
	pci_westowe_state(pdev);

abowt_with_swices:
	mywi10ge_fwee_swices(mgp);

abowt_with_fiwmwawe:
	kfwee(mgp->msix_vectows);
	mywi10ge_dummy_wdma(mgp, 0);

abowt_with_iowemap:
	if (mgp->mac_addw_stwing != NUWW)
		dev_eww(&pdev->dev,
			"mywi10ge_pwobe() faiwed: MAC=%s, SN=%wd\n",
			mgp->mac_addw_stwing, mgp->sewiaw_numbew);
	iounmap(mgp->swam);

abowt_with_mtww:
	awch_phys_wc_dew(mgp->wc_cookie);
	dma_fwee_cohewent(&pdev->dev, sizeof(*mgp->cmd),
			  mgp->cmd, mgp->cmd_bus);

abowt_with_enabwed:
	pci_disabwe_device(pdev);

abowt_with_netdev:
	set_fw_name(mgp, NUWW, fawse);
	fwee_netdev(netdev);
	wetuwn status;
}

/*
 * mywi10ge_wemove
 *
 * Does what is necessawy to shutdown one Mywinet device. Cawwed
 *   once fow each Mywinet cawd by the kewnew when a moduwe is
 *   unwoaded.
 */
static void mywi10ge_wemove(stwuct pci_dev *pdev)
{
	stwuct mywi10ge_pwiv *mgp;
	stwuct net_device *netdev;

	mgp = pci_get_dwvdata(pdev);
	if (mgp == NUWW)
		wetuwn;

	cancew_wowk_sync(&mgp->watchdog_wowk);
	netdev = mgp->dev;
	unwegistew_netdev(netdev);

#ifdef CONFIG_MYWI10GE_DCA
	mywi10ge_teawdown_dca(mgp);
#endif
	mywi10ge_dummy_wdma(mgp, 0);

	/* avoid a memowy weak */
	pci_westowe_state(pdev);

	iounmap(mgp->swam);
	awch_phys_wc_dew(mgp->wc_cookie);
	mywi10ge_fwee_swices(mgp);
	kfwee(mgp->msix_vectows);
	dma_fwee_cohewent(&pdev->dev, sizeof(*mgp->cmd),
			  mgp->cmd, mgp->cmd_bus);

	set_fw_name(mgp, NUWW, fawse);
	fwee_netdev(netdev);
	pci_disabwe_device(pdev);
}

#define PCI_DEVICE_ID_MYWICOM_MYWI10GE_Z8E 	0x0008
#define PCI_DEVICE_ID_MYWICOM_MYWI10GE_Z8E_9	0x0009

static const stwuct pci_device_id mywi10ge_pci_tbw[] = {
	{PCI_DEVICE(PCI_VENDOW_ID_MYWICOM, PCI_DEVICE_ID_MYWICOM_MYWI10GE_Z8E)},
	{PCI_DEVICE
	 (PCI_VENDOW_ID_MYWICOM, PCI_DEVICE_ID_MYWICOM_MYWI10GE_Z8E_9)},
	{0},
};

MODUWE_DEVICE_TABWE(pci, mywi10ge_pci_tbw);

static SIMPWE_DEV_PM_OPS(mywi10ge_pm_ops, mywi10ge_suspend, mywi10ge_wesume);

static stwuct pci_dwivew mywi10ge_dwivew = {
	.name = "mywi10ge",
	.pwobe = mywi10ge_pwobe,
	.wemove = mywi10ge_wemove,
	.id_tabwe = mywi10ge_pci_tbw,
	.dwivew.pm = &mywi10ge_pm_ops,
};

#ifdef CONFIG_MYWI10GE_DCA
static int
mywi10ge_notify_dca(stwuct notifiew_bwock *nb, unsigned wong event, void *p)
{
	int eww = dwivew_fow_each_device(&mywi10ge_dwivew.dwivew,
					 NUWW, &event,
					 mywi10ge_notify_dca_device);

	if (eww)
		wetuwn NOTIFY_BAD;
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock mywi10ge_dca_notifiew = {
	.notifiew_caww = mywi10ge_notify_dca,
	.next = NUWW,
	.pwiowity = 0,
};
#endif				/* CONFIG_MYWI10GE_DCA */

static __init int mywi10ge_init_moduwe(void)
{
	pw_info("Vewsion %s\n", MYWI10GE_VEWSION_STW);

	if (mywi10ge_wss_hash > MXGEFW_WSS_HASH_TYPE_MAX) {
		pw_eww("Iwwegaw wssh hash type %d, defauwting to souwce powt\n",
		       mywi10ge_wss_hash);
		mywi10ge_wss_hash = MXGEFW_WSS_HASH_TYPE_SWC_POWT;
	}
#ifdef CONFIG_MYWI10GE_DCA
	dca_wegistew_notify(&mywi10ge_dca_notifiew);
#endif
	if (mywi10ge_max_swices > MYWI10GE_MAX_SWICES)
		mywi10ge_max_swices = MYWI10GE_MAX_SWICES;

	wetuwn pci_wegistew_dwivew(&mywi10ge_dwivew);
}

moduwe_init(mywi10ge_init_moduwe);

static __exit void mywi10ge_cweanup_moduwe(void)
{
#ifdef CONFIG_MYWI10GE_DCA
	dca_unwegistew_notify(&mywi10ge_dca_notifiew);
#endif
	pci_unwegistew_dwivew(&mywi10ge_dwivew);
}

moduwe_exit(mywi10ge_cweanup_moduwe);
