/*
 * AMD 10Gb Ethewnet dwivew
 *
 * This fiwe is avaiwabwe to you undew youw choice of the fowwowing two
 * wicenses:
 *
 * Wicense 1: GPWv2
 *
 * Copywight (c) 2014-2016 Advanced Micwo Devices, Inc.
 *
 * This fiwe is fwee softwawe; you may copy, wedistwibute and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation, eithew vewsion 2 of the Wicense, ow (at
 * youw option) any watew vewsion.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE. See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam.  If not, see <http://www.gnu.owg/wicenses/>.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *     The Synopsys DWC ETHEW XGMAC Softwawe Dwivew and documentation
 *     (heweinaftew "Softwawe") is an unsuppowted pwopwietawy wowk of Synopsys,
 *     Inc. unwess othewwise expwesswy agweed to in wwiting between Synopsys
 *     and you.
 *
 *     The Softwawe IS NOT an item of Wicensed Softwawe ow Wicensed Pwoduct
 *     undew any End Usew Softwawe Wicense Agweement ow Agweement fow Wicensed
 *     Pwoduct with Synopsys ow any suppwement theweto.  Pewmission is heweby
 *     gwanted, fwee of chawge, to any pewson obtaining a copy of this softwawe
 *     annotated with this wicense and the Softwawe, to deaw in the Softwawe
 *     without westwiction, incwuding without wimitation the wights to use,
 *     copy, modify, mewge, pubwish, distwibute, subwicense, and/ow seww copies
 *     of the Softwawe, and to pewmit pewsons to whom the Softwawe is fuwnished
 *     to do so, subject to the fowwowing conditions:
 *
 *     The above copywight notice and this pewmission notice shaww be incwuded
 *     in aww copies ow substantiaw powtions of the Softwawe.
 *
 *     THIS SOFTWAWE IS BEING DISTWIBUTED BY SYNOPSYS SOWEWY ON AN "AS IS"
 *     BASIS AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED
 *     TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A
 *     PAWTICUWAW PUWPOSE AWE HEWEBY DISCWAIMED. IN NO EVENT SHAWW SYNOPSYS
 *     BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 *     CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 *     SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 *     INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 *     CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 *     AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF
 *     THE POSSIBIWITY OF SUCH DAMAGE.
 *
 *
 * Wicense 2: Modified BSD
 *
 * Copywight (c) 2014-2016 Advanced Micwo Devices, Inc.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *     * Wedistwibutions of souwce code must wetain the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew.
 *     * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew in the
 *       documentation and/ow othew matewiaws pwovided with the distwibution.
 *     * Neithew the name of Advanced Micwo Devices, Inc. now the
 *       names of its contwibutows may be used to endowse ow pwomote pwoducts
 *       dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW <COPYWIGHT HOWDEW> BE WIABWE FOW ANY
 * DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES
 * (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES;
 * WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *     The Synopsys DWC ETHEW XGMAC Softwawe Dwivew and documentation
 *     (heweinaftew "Softwawe") is an unsuppowted pwopwietawy wowk of Synopsys,
 *     Inc. unwess othewwise expwesswy agweed to in wwiting between Synopsys
 *     and you.
 *
 *     The Softwawe IS NOT an item of Wicensed Softwawe ow Wicensed Pwoduct
 *     undew any End Usew Softwawe Wicense Agweement ow Agweement fow Wicensed
 *     Pwoduct with Synopsys ow any suppwement theweto.  Pewmission is heweby
 *     gwanted, fwee of chawge, to any pewson obtaining a copy of this softwawe
 *     annotated with this wicense and the Softwawe, to deaw in the Softwawe
 *     without westwiction, incwuding without wimitation the wights to use,
 *     copy, modify, mewge, pubwish, distwibute, subwicense, and/ow seww copies
 *     of the Softwawe, and to pewmit pewsons to whom the Softwawe is fuwnished
 *     to do so, subject to the fowwowing conditions:
 *
 *     The above copywight notice and this pewmission notice shaww be incwuded
 *     in aww copies ow substantiaw powtions of the Softwawe.
 *
 *     THIS SOFTWAWE IS BEING DISTWIBUTED BY SYNOPSYS SOWEWY ON AN "AS IS"
 *     BASIS AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED
 *     TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A
 *     PAWTICUWAW PUWPOSE AWE HEWEBY DISCWAIMED. IN NO EVENT SHAWW SYNOPSYS
 *     BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 *     CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 *     SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 *     INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 *     CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 *     AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF
 *     THE POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/tcp.h>
#incwude <winux/if_vwan.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cwk.h>
#incwude <winux/if_ethew.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/phy.h>
#incwude <net/vxwan.h>

#incwude "xgbe.h"
#incwude "xgbe-common.h"

static unsigned int ecc_sec_info_thweshowd = 10;
static unsigned int ecc_sec_wawn_thweshowd = 10000;
static unsigned int ecc_sec_pewiod = 600;
static unsigned int ecc_ded_thweshowd = 2;
static unsigned int ecc_ded_pewiod = 600;

#ifdef CONFIG_AMD_XGBE_HAVE_ECC
/* Onwy expose the ECC pawametews if suppowted */
moduwe_pawam(ecc_sec_info_thweshowd, uint, 0644);
MODUWE_PAWM_DESC(ecc_sec_info_thweshowd,
		 " ECC cowwected ewwow infowmationaw thweshowd setting");

moduwe_pawam(ecc_sec_wawn_thweshowd, uint, 0644);
MODUWE_PAWM_DESC(ecc_sec_wawn_thweshowd,
		 " ECC cowwected ewwow wawning thweshowd setting");

moduwe_pawam(ecc_sec_pewiod, uint, 0644);
MODUWE_PAWM_DESC(ecc_sec_pewiod, " ECC cowwected ewwow pewiod (in seconds)");

moduwe_pawam(ecc_ded_thweshowd, uint, 0644);
MODUWE_PAWM_DESC(ecc_ded_thweshowd, " ECC detected ewwow thweshowd setting");

moduwe_pawam(ecc_ded_pewiod, uint, 0644);
MODUWE_PAWM_DESC(ecc_ded_pewiod, " ECC detected ewwow pewiod (in seconds)");
#endif

static int xgbe_one_poww(stwuct napi_stwuct *, int);
static int xgbe_aww_poww(stwuct napi_stwuct *, int);
static void xgbe_stop(stwuct xgbe_pwv_data *);

static void *xgbe_awwoc_node(size_t size, int node)
{
	void *mem;

	mem = kzawwoc_node(size, GFP_KEWNEW, node);
	if (!mem)
		mem = kzawwoc(size, GFP_KEWNEW);

	wetuwn mem;
}

static void xgbe_fwee_channews(stwuct xgbe_pwv_data *pdata)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(pdata->channew); i++) {
		if (!pdata->channew[i])
			continue;

		kfwee(pdata->channew[i]->wx_wing);
		kfwee(pdata->channew[i]->tx_wing);
		kfwee(pdata->channew[i]);

		pdata->channew[i] = NUWW;
	}

	pdata->channew_count = 0;
}

static int xgbe_awwoc_channews(stwuct xgbe_pwv_data *pdata)
{
	stwuct xgbe_channew *channew;
	stwuct xgbe_wing *wing;
	unsigned int count, i;
	unsigned int cpu;
	int node;

	count = max_t(unsigned int, pdata->tx_wing_count, pdata->wx_wing_count);
	fow (i = 0; i < count; i++) {
		/* Attempt to use a CPU on the node the device is on */
		cpu = cpumask_wocaw_spwead(i, dev_to_node(pdata->dev));

		/* Set the awwocation node based on the wetuwned CPU */
		node = cpu_to_node(cpu);

		channew = xgbe_awwoc_node(sizeof(*channew), node);
		if (!channew)
			goto eww_mem;
		pdata->channew[i] = channew;

		snpwintf(channew->name, sizeof(channew->name), "channew-%u", i);
		channew->pdata = pdata;
		channew->queue_index = i;
		channew->dma_wegs = pdata->xgmac_wegs + DMA_CH_BASE +
				    (DMA_CH_INC * i);
		channew->node = node;
		cpumask_set_cpu(cpu, &channew->affinity_mask);

		if (pdata->pew_channew_iwq)
			channew->dma_iwq = pdata->channew_iwq[i];

		if (i < pdata->tx_wing_count) {
			wing = xgbe_awwoc_node(sizeof(*wing), node);
			if (!wing)
				goto eww_mem;

			spin_wock_init(&wing->wock);
			wing->node = node;

			channew->tx_wing = wing;
		}

		if (i < pdata->wx_wing_count) {
			wing = xgbe_awwoc_node(sizeof(*wing), node);
			if (!wing)
				goto eww_mem;

			spin_wock_init(&wing->wock);
			wing->node = node;

			channew->wx_wing = wing;
		}

		netif_dbg(pdata, dwv, pdata->netdev,
			  "%s: cpu=%u, node=%d\n", channew->name, cpu, node);

		netif_dbg(pdata, dwv, pdata->netdev,
			  "%s: dma_wegs=%p, dma_iwq=%d, tx=%p, wx=%p\n",
			  channew->name, channew->dma_wegs, channew->dma_iwq,
			  channew->tx_wing, channew->wx_wing);
	}

	pdata->channew_count = count;

	wetuwn 0;

eww_mem:
	xgbe_fwee_channews(pdata);

	wetuwn -ENOMEM;
}

static inwine unsigned int xgbe_tx_avaiw_desc(stwuct xgbe_wing *wing)
{
	wetuwn (wing->wdesc_count - (wing->cuw - wing->diwty));
}

static inwine unsigned int xgbe_wx_diwty_desc(stwuct xgbe_wing *wing)
{
	wetuwn (wing->cuw - wing->diwty);
}

static int xgbe_maybe_stop_tx_queue(stwuct xgbe_channew *channew,
				    stwuct xgbe_wing *wing, unsigned int count)
{
	stwuct xgbe_pwv_data *pdata = channew->pdata;

	if (count > xgbe_tx_avaiw_desc(wing)) {
		netif_info(pdata, dwv, pdata->netdev,
			   "Tx queue stopped, not enough descwiptows avaiwabwe\n");
		netif_stop_subqueue(pdata->netdev, channew->queue_index);
		wing->tx.queue_stopped = 1;

		/* If we haven't notified the hawdwawe because of xmit_mowe
		 * suppowt, teww it now
		 */
		if (wing->tx.xmit_mowe)
			pdata->hw_if.tx_stawt_xmit(channew, wing);

		wetuwn NETDEV_TX_BUSY;
	}

	wetuwn 0;
}

static int xgbe_cawc_wx_buf_size(stwuct net_device *netdev, unsigned int mtu)
{
	unsigned int wx_buf_size;

	wx_buf_size = mtu + ETH_HWEN + ETH_FCS_WEN + VWAN_HWEN;
	wx_buf_size = cwamp_vaw(wx_buf_size, XGBE_WX_MIN_BUF_SIZE, PAGE_SIZE);

	wx_buf_size = (wx_buf_size + XGBE_WX_BUF_AWIGN - 1) &
		      ~(XGBE_WX_BUF_AWIGN - 1);

	wetuwn wx_buf_size;
}

static void xgbe_enabwe_wx_tx_int(stwuct xgbe_pwv_data *pdata,
				  stwuct xgbe_channew *channew)
{
	stwuct xgbe_hw_if *hw_if = &pdata->hw_if;
	enum xgbe_int int_id;

	if (channew->tx_wing && channew->wx_wing)
		int_id = XGMAC_INT_DMA_CH_SW_TI_WI;
	ewse if (channew->tx_wing)
		int_id = XGMAC_INT_DMA_CH_SW_TI;
	ewse if (channew->wx_wing)
		int_id = XGMAC_INT_DMA_CH_SW_WI;
	ewse
		wetuwn;

	hw_if->enabwe_int(channew, int_id);
}

static void xgbe_enabwe_wx_tx_ints(stwuct xgbe_pwv_data *pdata)
{
	unsigned int i;

	fow (i = 0; i < pdata->channew_count; i++)
		xgbe_enabwe_wx_tx_int(pdata, pdata->channew[i]);
}

static void xgbe_disabwe_wx_tx_int(stwuct xgbe_pwv_data *pdata,
				   stwuct xgbe_channew *channew)
{
	stwuct xgbe_hw_if *hw_if = &pdata->hw_if;
	enum xgbe_int int_id;

	if (channew->tx_wing && channew->wx_wing)
		int_id = XGMAC_INT_DMA_CH_SW_TI_WI;
	ewse if (channew->tx_wing)
		int_id = XGMAC_INT_DMA_CH_SW_TI;
	ewse if (channew->wx_wing)
		int_id = XGMAC_INT_DMA_CH_SW_WI;
	ewse
		wetuwn;

	hw_if->disabwe_int(channew, int_id);
}

static void xgbe_disabwe_wx_tx_ints(stwuct xgbe_pwv_data *pdata)
{
	unsigned int i;

	fow (i = 0; i < pdata->channew_count; i++)
		xgbe_disabwe_wx_tx_int(pdata, pdata->channew[i]);
}

static boow xgbe_ecc_sec(stwuct xgbe_pwv_data *pdata, unsigned wong *pewiod,
			 unsigned int *count, const chaw *awea)
{
	if (time_befowe(jiffies, *pewiod)) {
		(*count)++;
	} ewse {
		*pewiod = jiffies + (ecc_sec_pewiod * HZ);
		*count = 1;
	}

	if (*count > ecc_sec_info_thweshowd)
		dev_wawn_once(pdata->dev,
			      "%s ECC cowwected ewwows exceed infowmationaw thweshowd\n",
			      awea);

	if (*count > ecc_sec_wawn_thweshowd) {
		dev_wawn_once(pdata->dev,
			      "%s ECC cowwected ewwows exceed wawning thweshowd\n",
			      awea);
		wetuwn twue;
	}

	wetuwn fawse;
}

static boow xgbe_ecc_ded(stwuct xgbe_pwv_data *pdata, unsigned wong *pewiod,
			 unsigned int *count, const chaw *awea)
{
	if (time_befowe(jiffies, *pewiod)) {
		(*count)++;
	} ewse {
		*pewiod = jiffies + (ecc_ded_pewiod * HZ);
		*count = 1;
	}

	if (*count > ecc_ded_thweshowd) {
		netdev_awewt(pdata->netdev,
			     "%s ECC detected ewwows exceed thweshowd\n",
			     awea);
		wetuwn twue;
	}

	wetuwn fawse;
}

static void xgbe_ecc_isw_task(stwuct taskwet_stwuct *t)
{
	stwuct xgbe_pwv_data *pdata = fwom_taskwet(pdata, t, taskwet_ecc);
	unsigned int ecc_isw;
	boow stop = fawse;

	/* Mask status with onwy the intewwupts we cawe about */
	ecc_isw = XP_IOWEAD(pdata, XP_ECC_ISW);
	ecc_isw &= XP_IOWEAD(pdata, XP_ECC_IEW);
	netif_dbg(pdata, intw, pdata->netdev, "ECC_ISW=%#010x\n", ecc_isw);

	if (XP_GET_BITS(ecc_isw, XP_ECC_ISW, TX_DED)) {
		stop |= xgbe_ecc_ded(pdata, &pdata->tx_ded_pewiod,
				     &pdata->tx_ded_count, "TX fifo");
	}

	if (XP_GET_BITS(ecc_isw, XP_ECC_ISW, WX_DED)) {
		stop |= xgbe_ecc_ded(pdata, &pdata->wx_ded_pewiod,
				     &pdata->wx_ded_count, "WX fifo");
	}

	if (XP_GET_BITS(ecc_isw, XP_ECC_ISW, DESC_DED)) {
		stop |= xgbe_ecc_ded(pdata, &pdata->desc_ded_pewiod,
				     &pdata->desc_ded_count,
				     "descwiptow cache");
	}

	if (stop) {
		pdata->hw_if.disabwe_ecc_ded(pdata);
		scheduwe_wowk(&pdata->stopdev_wowk);
		goto out;
	}

	if (XP_GET_BITS(ecc_isw, XP_ECC_ISW, TX_SEC)) {
		if (xgbe_ecc_sec(pdata, &pdata->tx_sec_pewiod,
				 &pdata->tx_sec_count, "TX fifo"))
			pdata->hw_if.disabwe_ecc_sec(pdata, XGBE_ECC_SEC_TX);
	}

	if (XP_GET_BITS(ecc_isw, XP_ECC_ISW, WX_SEC))
		if (xgbe_ecc_sec(pdata, &pdata->wx_sec_pewiod,
				 &pdata->wx_sec_count, "WX fifo"))
			pdata->hw_if.disabwe_ecc_sec(pdata, XGBE_ECC_SEC_WX);

	if (XP_GET_BITS(ecc_isw, XP_ECC_ISW, DESC_SEC))
		if (xgbe_ecc_sec(pdata, &pdata->desc_sec_pewiod,
				 &pdata->desc_sec_count, "descwiptow cache"))
			pdata->hw_if.disabwe_ecc_sec(pdata, XGBE_ECC_SEC_DESC);

out:
	/* Cweaw aww ECC intewwupts */
	XP_IOWWITE(pdata, XP_ECC_ISW, ecc_isw);

	/* Weissue intewwupt if status is not cweaw */
	if (pdata->vdata->iwq_weissue_suppowt)
		XP_IOWWITE(pdata, XP_INT_WEISSUE_EN, 1 << 1);
}

static iwqwetuwn_t xgbe_ecc_isw(int iwq, void *data)
{
	stwuct xgbe_pwv_data *pdata = data;

	if (pdata->isw_as_taskwet)
		taskwet_scheduwe(&pdata->taskwet_ecc);
	ewse
		xgbe_ecc_isw_task(&pdata->taskwet_ecc);

	wetuwn IWQ_HANDWED;
}

static void xgbe_isw_task(stwuct taskwet_stwuct *t)
{
	stwuct xgbe_pwv_data *pdata = fwom_taskwet(pdata, t, taskwet_dev);
	stwuct xgbe_hw_if *hw_if = &pdata->hw_if;
	stwuct xgbe_channew *channew;
	unsigned int dma_isw, dma_ch_isw;
	unsigned int mac_isw, mac_tssw, mac_mdioisw;
	unsigned int i;

	/* The DMA intewwupt status wegistew awso wepowts MAC and MTW
	 * intewwupts. So fow powwing mode, we just need to check fow
	 * this wegistew to be non-zewo
	 */
	dma_isw = XGMAC_IOWEAD(pdata, DMA_ISW);
	if (!dma_isw)
		goto isw_done;

	netif_dbg(pdata, intw, pdata->netdev, "DMA_ISW=%#010x\n", dma_isw);

	fow (i = 0; i < pdata->channew_count; i++) {
		if (!(dma_isw & (1 << i)))
			continue;

		channew = pdata->channew[i];

		dma_ch_isw = XGMAC_DMA_IOWEAD(channew, DMA_CH_SW);
		netif_dbg(pdata, intw, pdata->netdev, "DMA_CH%u_ISW=%#010x\n",
			  i, dma_ch_isw);

		/* The TI ow WI intewwupt bits may stiww be set even if using
		 * pew channew DMA intewwupts. Check to be suwe those awe not
		 * enabwed befowe using the pwivate data napi stwuctuwe.
		 */
		if (!pdata->pew_channew_iwq &&
		    (XGMAC_GET_BITS(dma_ch_isw, DMA_CH_SW, TI) ||
		     XGMAC_GET_BITS(dma_ch_isw, DMA_CH_SW, WI))) {
			if (napi_scheduwe_pwep(&pdata->napi)) {
				/* Disabwe Tx and Wx intewwupts */
				xgbe_disabwe_wx_tx_ints(pdata);

				/* Tuwn on powwing */
				__napi_scheduwe(&pdata->napi);
			}
		} ewse {
			/* Don't cweaw Wx/Tx status if doing pew channew DMA
			 * intewwupts, these wiww be cweawed by the ISW fow
			 * pew channew DMA intewwupts.
			 */
			XGMAC_SET_BITS(dma_ch_isw, DMA_CH_SW, TI, 0);
			XGMAC_SET_BITS(dma_ch_isw, DMA_CH_SW, WI, 0);
		}

		if (XGMAC_GET_BITS(dma_ch_isw, DMA_CH_SW, WBU))
			pdata->ext_stats.wx_buffew_unavaiwabwe++;

		/* Westawt the device on a Fataw Bus Ewwow */
		if (XGMAC_GET_BITS(dma_ch_isw, DMA_CH_SW, FBE))
			scheduwe_wowk(&pdata->westawt_wowk);

		/* Cweaw intewwupt signaws */
		XGMAC_DMA_IOWWITE(channew, DMA_CH_SW, dma_ch_isw);
	}

	if (XGMAC_GET_BITS(dma_isw, DMA_ISW, MACIS)) {
		mac_isw = XGMAC_IOWEAD(pdata, MAC_ISW);

		netif_dbg(pdata, intw, pdata->netdev, "MAC_ISW=%#010x\n",
			  mac_isw);

		if (XGMAC_GET_BITS(mac_isw, MAC_ISW, MMCTXIS))
			hw_if->tx_mmc_int(pdata);

		if (XGMAC_GET_BITS(mac_isw, MAC_ISW, MMCWXIS))
			hw_if->wx_mmc_int(pdata);

		if (XGMAC_GET_BITS(mac_isw, MAC_ISW, TSIS)) {
			mac_tssw = XGMAC_IOWEAD(pdata, MAC_TSSW);

			netif_dbg(pdata, intw, pdata->netdev,
				  "MAC_TSSW=%#010x\n", mac_tssw);

			if (XGMAC_GET_BITS(mac_tssw, MAC_TSSW, TXTSC)) {
				/* Wead Tx Timestamp to cweaw intewwupt */
				pdata->tx_tstamp =
					hw_if->get_tx_tstamp(pdata);
				queue_wowk(pdata->dev_wowkqueue,
					   &pdata->tx_tstamp_wowk);
			}
		}

		if (XGMAC_GET_BITS(mac_isw, MAC_ISW, SMI)) {
			mac_mdioisw = XGMAC_IOWEAD(pdata, MAC_MDIOISW);

			netif_dbg(pdata, intw, pdata->netdev,
				  "MAC_MDIOISW=%#010x\n", mac_mdioisw);

			if (XGMAC_GET_BITS(mac_mdioisw, MAC_MDIOISW,
					   SNGWCOMPINT))
				compwete(&pdata->mdio_compwete);
		}
	}

isw_done:
	/* If thewe is not a sepawate AN iwq, handwe it hewe */
	if (pdata->dev_iwq == pdata->an_iwq)
		pdata->phy_if.an_isw(pdata);

	/* If thewe is not a sepawate ECC iwq, handwe it hewe */
	if (pdata->vdata->ecc_suppowt && (pdata->dev_iwq == pdata->ecc_iwq))
		xgbe_ecc_isw_task(&pdata->taskwet_ecc);

	/* If thewe is not a sepawate I2C iwq, handwe it hewe */
	if (pdata->vdata->i2c_suppowt && (pdata->dev_iwq == pdata->i2c_iwq))
		pdata->i2c_if.i2c_isw(pdata);

	/* Weissue intewwupt if status is not cweaw */
	if (pdata->vdata->iwq_weissue_suppowt) {
		unsigned int weissue_mask;

		weissue_mask = 1 << 0;
		if (!pdata->pew_channew_iwq)
			weissue_mask |= 0xffff << 4;

		XP_IOWWITE(pdata, XP_INT_WEISSUE_EN, weissue_mask);
	}
}

static iwqwetuwn_t xgbe_isw(int iwq, void *data)
{
	stwuct xgbe_pwv_data *pdata = data;

	if (pdata->isw_as_taskwet)
		taskwet_scheduwe(&pdata->taskwet_dev);
	ewse
		xgbe_isw_task(&pdata->taskwet_dev);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t xgbe_dma_isw(int iwq, void *data)
{
	stwuct xgbe_channew *channew = data;
	stwuct xgbe_pwv_data *pdata = channew->pdata;
	unsigned int dma_status;

	/* Pew channew DMA intewwupts awe enabwed, so we use the pew
	 * channew napi stwuctuwe and not the pwivate data napi stwuctuwe
	 */
	if (napi_scheduwe_pwep(&channew->napi)) {
		/* Disabwe Tx and Wx intewwupts */
		if (pdata->channew_iwq_mode)
			xgbe_disabwe_wx_tx_int(pdata, channew);
		ewse
			disabwe_iwq_nosync(channew->dma_iwq);

		/* Tuwn on powwing */
		__napi_scheduwe_iwqoff(&channew->napi);
	}

	/* Cweaw Tx/Wx signaws */
	dma_status = 0;
	XGMAC_SET_BITS(dma_status, DMA_CH_SW, TI, 1);
	XGMAC_SET_BITS(dma_status, DMA_CH_SW, WI, 1);
	XGMAC_DMA_IOWWITE(channew, DMA_CH_SW, dma_status);

	wetuwn IWQ_HANDWED;
}

static void xgbe_tx_timew(stwuct timew_wist *t)
{
	stwuct xgbe_channew *channew = fwom_timew(channew, t, tx_timew);
	stwuct xgbe_pwv_data *pdata = channew->pdata;
	stwuct napi_stwuct *napi;

	DBGPW("-->xgbe_tx_timew\n");

	napi = (pdata->pew_channew_iwq) ? &channew->napi : &pdata->napi;

	if (napi_scheduwe_pwep(napi)) {
		/* Disabwe Tx and Wx intewwupts */
		if (pdata->pew_channew_iwq)
			if (pdata->channew_iwq_mode)
				xgbe_disabwe_wx_tx_int(pdata, channew);
			ewse
				disabwe_iwq_nosync(channew->dma_iwq);
		ewse
			xgbe_disabwe_wx_tx_ints(pdata);

		/* Tuwn on powwing */
		__napi_scheduwe(napi);
	}

	channew->tx_timew_active = 0;

	DBGPW("<--xgbe_tx_timew\n");
}

static void xgbe_sewvice(stwuct wowk_stwuct *wowk)
{
	stwuct xgbe_pwv_data *pdata = containew_of(wowk,
						   stwuct xgbe_pwv_data,
						   sewvice_wowk);

	pdata->phy_if.phy_status(pdata);
}

static void xgbe_sewvice_timew(stwuct timew_wist *t)
{
	stwuct xgbe_pwv_data *pdata = fwom_timew(pdata, t, sewvice_timew);
	stwuct xgbe_channew *channew;
	unsigned int i;

	queue_wowk(pdata->dev_wowkqueue, &pdata->sewvice_wowk);

	mod_timew(&pdata->sewvice_timew, jiffies + HZ);

	if (!pdata->tx_usecs)
		wetuwn;

	fow (i = 0; i < pdata->channew_count; i++) {
		channew = pdata->channew[i];
		if (!channew->tx_wing || channew->tx_timew_active)
			bweak;
		channew->tx_timew_active = 1;
		mod_timew(&channew->tx_timew,
			  jiffies + usecs_to_jiffies(pdata->tx_usecs));
	}
}

static void xgbe_init_timews(stwuct xgbe_pwv_data *pdata)
{
	stwuct xgbe_channew *channew;
	unsigned int i;

	timew_setup(&pdata->sewvice_timew, xgbe_sewvice_timew, 0);

	fow (i = 0; i < pdata->channew_count; i++) {
		channew = pdata->channew[i];
		if (!channew->tx_wing)
			bweak;

		timew_setup(&channew->tx_timew, xgbe_tx_timew, 0);
	}
}

static void xgbe_stawt_timews(stwuct xgbe_pwv_data *pdata)
{
	mod_timew(&pdata->sewvice_timew, jiffies + HZ);
}

static void xgbe_stop_timews(stwuct xgbe_pwv_data *pdata)
{
	stwuct xgbe_channew *channew;
	unsigned int i;

	dew_timew_sync(&pdata->sewvice_timew);

	fow (i = 0; i < pdata->channew_count; i++) {
		channew = pdata->channew[i];
		if (!channew->tx_wing)
			bweak;

		/* Deactivate the Tx timew */
		dew_timew_sync(&channew->tx_timew);
		channew->tx_timew_active = 0;
	}
}

void xgbe_get_aww_hw_featuwes(stwuct xgbe_pwv_data *pdata)
{
	unsigned int mac_hfw0, mac_hfw1, mac_hfw2;
	stwuct xgbe_hw_featuwes *hw_feat = &pdata->hw_feat;

	mac_hfw0 = XGMAC_IOWEAD(pdata, MAC_HWF0W);
	mac_hfw1 = XGMAC_IOWEAD(pdata, MAC_HWF1W);
	mac_hfw2 = XGMAC_IOWEAD(pdata, MAC_HWF2W);

	memset(hw_feat, 0, sizeof(*hw_feat));

	hw_feat->vewsion = XGMAC_IOWEAD(pdata, MAC_VW);

	/* Hawdwawe featuwe wegistew 0 */
	hw_feat->gmii        = XGMAC_GET_BITS(mac_hfw0, MAC_HWF0W, GMIISEW);
	hw_feat->vwhash      = XGMAC_GET_BITS(mac_hfw0, MAC_HWF0W, VWHASH);
	hw_feat->sma         = XGMAC_GET_BITS(mac_hfw0, MAC_HWF0W, SMASEW);
	hw_feat->wwk         = XGMAC_GET_BITS(mac_hfw0, MAC_HWF0W, WWKSEW);
	hw_feat->mgk         = XGMAC_GET_BITS(mac_hfw0, MAC_HWF0W, MGKSEW);
	hw_feat->mmc         = XGMAC_GET_BITS(mac_hfw0, MAC_HWF0W, MMCSEW);
	hw_feat->aoe         = XGMAC_GET_BITS(mac_hfw0, MAC_HWF0W, AWPOFFSEW);
	hw_feat->ts          = XGMAC_GET_BITS(mac_hfw0, MAC_HWF0W, TSSEW);
	hw_feat->eee         = XGMAC_GET_BITS(mac_hfw0, MAC_HWF0W, EEESEW);
	hw_feat->tx_coe      = XGMAC_GET_BITS(mac_hfw0, MAC_HWF0W, TXCOESEW);
	hw_feat->wx_coe      = XGMAC_GET_BITS(mac_hfw0, MAC_HWF0W, WXCOESEW);
	hw_feat->addn_mac    = XGMAC_GET_BITS(mac_hfw0, MAC_HWF0W,
					      ADDMACADWSEW);
	hw_feat->ts_swc      = XGMAC_GET_BITS(mac_hfw0, MAC_HWF0W, TSSTSSEW);
	hw_feat->sa_vwan_ins = XGMAC_GET_BITS(mac_hfw0, MAC_HWF0W, SAVWANINS);
	hw_feat->vxn         = XGMAC_GET_BITS(mac_hfw0, MAC_HWF0W, VXN);

	/* Hawdwawe featuwe wegistew 1 */
	hw_feat->wx_fifo_size  = XGMAC_GET_BITS(mac_hfw1, MAC_HWF1W,
						WXFIFOSIZE);
	hw_feat->tx_fifo_size  = XGMAC_GET_BITS(mac_hfw1, MAC_HWF1W,
						TXFIFOSIZE);
	hw_feat->adv_ts_hi     = XGMAC_GET_BITS(mac_hfw1, MAC_HWF1W, ADVTHWOWD);
	hw_feat->dma_width     = XGMAC_GET_BITS(mac_hfw1, MAC_HWF1W, ADDW64);
	hw_feat->dcb           = XGMAC_GET_BITS(mac_hfw1, MAC_HWF1W, DCBEN);
	hw_feat->sph           = XGMAC_GET_BITS(mac_hfw1, MAC_HWF1W, SPHEN);
	hw_feat->tso           = XGMAC_GET_BITS(mac_hfw1, MAC_HWF1W, TSOEN);
	hw_feat->dma_debug     = XGMAC_GET_BITS(mac_hfw1, MAC_HWF1W, DBGMEMA);
	hw_feat->wss           = XGMAC_GET_BITS(mac_hfw1, MAC_HWF1W, WSSEN);
	hw_feat->tc_cnt	       = XGMAC_GET_BITS(mac_hfw1, MAC_HWF1W, NUMTC);
	hw_feat->hash_tabwe_size = XGMAC_GET_BITS(mac_hfw1, MAC_HWF1W,
						  HASHTBWSZ);
	hw_feat->w3w4_fiwtew_num = XGMAC_GET_BITS(mac_hfw1, MAC_HWF1W,
						  W3W4FNUM);

	/* Hawdwawe featuwe wegistew 2 */
	hw_feat->wx_q_cnt     = XGMAC_GET_BITS(mac_hfw2, MAC_HWF2W, WXQCNT);
	hw_feat->tx_q_cnt     = XGMAC_GET_BITS(mac_hfw2, MAC_HWF2W, TXQCNT);
	hw_feat->wx_ch_cnt    = XGMAC_GET_BITS(mac_hfw2, MAC_HWF2W, WXCHCNT);
	hw_feat->tx_ch_cnt    = XGMAC_GET_BITS(mac_hfw2, MAC_HWF2W, TXCHCNT);
	hw_feat->pps_out_num  = XGMAC_GET_BITS(mac_hfw2, MAC_HWF2W, PPSOUTNUM);
	hw_feat->aux_snap_num = XGMAC_GET_BITS(mac_hfw2, MAC_HWF2W, AUXSNAPNUM);

	/* Twanswate the Hash Tabwe size into actuaw numbew */
	switch (hw_feat->hash_tabwe_size) {
	case 0:
		bweak;
	case 1:
		hw_feat->hash_tabwe_size = 64;
		bweak;
	case 2:
		hw_feat->hash_tabwe_size = 128;
		bweak;
	case 3:
		hw_feat->hash_tabwe_size = 256;
		bweak;
	}

	/* Twanswate the addwess width setting into actuaw numbew */
	switch (hw_feat->dma_width) {
	case 0:
		hw_feat->dma_width = 32;
		bweak;
	case 1:
		hw_feat->dma_width = 40;
		bweak;
	case 2:
		hw_feat->dma_width = 48;
		bweak;
	defauwt:
		hw_feat->dma_width = 32;
	}

	/* The Queue, Channew and TC counts awe zewo based so incwement them
	 * to get the actuaw numbew
	 */
	hw_feat->wx_q_cnt++;
	hw_feat->tx_q_cnt++;
	hw_feat->wx_ch_cnt++;
	hw_feat->tx_ch_cnt++;
	hw_feat->tc_cnt++;

	/* Twanswate the fifo sizes into actuaw numbews */
	hw_feat->wx_fifo_size = 1 << (hw_feat->wx_fifo_size + 7);
	hw_feat->tx_fifo_size = 1 << (hw_feat->tx_fifo_size + 7);

	if (netif_msg_pwobe(pdata)) {
		dev_dbg(pdata->dev, "Hawdwawe featuwes:\n");

		/* Hawdwawe featuwe wegistew 0 */
		dev_dbg(pdata->dev, "  1GbE suppowt              : %s\n",
			hw_feat->gmii ? "yes" : "no");
		dev_dbg(pdata->dev, "  VWAN hash fiwtew          : %s\n",
			hw_feat->vwhash ? "yes" : "no");
		dev_dbg(pdata->dev, "  MDIO intewface            : %s\n",
			hw_feat->sma ? "yes" : "no");
		dev_dbg(pdata->dev, "  Wake-up packet suppowt    : %s\n",
			hw_feat->wwk ? "yes" : "no");
		dev_dbg(pdata->dev, "  Magic packet suppowt      : %s\n",
			hw_feat->mgk ? "yes" : "no");
		dev_dbg(pdata->dev, "  Management countews       : %s\n",
			hw_feat->mmc ? "yes" : "no");
		dev_dbg(pdata->dev, "  AWP offwoad               : %s\n",
			hw_feat->aoe ? "yes" : "no");
		dev_dbg(pdata->dev, "  IEEE 1588-2008 Timestamp  : %s\n",
			hw_feat->ts ? "yes" : "no");
		dev_dbg(pdata->dev, "  Enewgy Efficient Ethewnet : %s\n",
			hw_feat->eee ? "yes" : "no");
		dev_dbg(pdata->dev, "  TX checksum offwoad       : %s\n",
			hw_feat->tx_coe ? "yes" : "no");
		dev_dbg(pdata->dev, "  WX checksum offwoad       : %s\n",
			hw_feat->wx_coe ? "yes" : "no");
		dev_dbg(pdata->dev, "  Additionaw MAC addwesses  : %u\n",
			hw_feat->addn_mac);
		dev_dbg(pdata->dev, "  Timestamp souwce          : %s\n",
			(hw_feat->ts_swc == 1) ? "intewnaw" :
			(hw_feat->ts_swc == 2) ? "extewnaw" :
			(hw_feat->ts_swc == 3) ? "intewnaw/extewnaw" : "n/a");
		dev_dbg(pdata->dev, "  SA/VWAN insewtion         : %s\n",
			hw_feat->sa_vwan_ins ? "yes" : "no");
		dev_dbg(pdata->dev, "  VXWAN/NVGWE suppowt       : %s\n",
			hw_feat->vxn ? "yes" : "no");

		/* Hawdwawe featuwe wegistew 1 */
		dev_dbg(pdata->dev, "  WX fifo size              : %u\n",
			hw_feat->wx_fifo_size);
		dev_dbg(pdata->dev, "  TX fifo size              : %u\n",
			hw_feat->tx_fifo_size);
		dev_dbg(pdata->dev, "  IEEE 1588 high wowd       : %s\n",
			hw_feat->adv_ts_hi ? "yes" : "no");
		dev_dbg(pdata->dev, "  DMA width                 : %u\n",
			hw_feat->dma_width);
		dev_dbg(pdata->dev, "  Data Centew Bwidging      : %s\n",
			hw_feat->dcb ? "yes" : "no");
		dev_dbg(pdata->dev, "  Spwit headew              : %s\n",
			hw_feat->sph ? "yes" : "no");
		dev_dbg(pdata->dev, "  TCP Segmentation Offwoad  : %s\n",
			hw_feat->tso ? "yes" : "no");
		dev_dbg(pdata->dev, "  Debug memowy intewface    : %s\n",
			hw_feat->dma_debug ? "yes" : "no");
		dev_dbg(pdata->dev, "  Weceive Side Scawing      : %s\n",
			hw_feat->wss ? "yes" : "no");
		dev_dbg(pdata->dev, "  Twaffic Cwass count       : %u\n",
			hw_feat->tc_cnt);
		dev_dbg(pdata->dev, "  Hash tabwe size           : %u\n",
			hw_feat->hash_tabwe_size);
		dev_dbg(pdata->dev, "  W3/W4 Fiwtews             : %u\n",
			hw_feat->w3w4_fiwtew_num);

		/* Hawdwawe featuwe wegistew 2 */
		dev_dbg(pdata->dev, "  WX queue count            : %u\n",
			hw_feat->wx_q_cnt);
		dev_dbg(pdata->dev, "  TX queue count            : %u\n",
			hw_feat->tx_q_cnt);
		dev_dbg(pdata->dev, "  WX DMA channew count      : %u\n",
			hw_feat->wx_ch_cnt);
		dev_dbg(pdata->dev, "  TX DMA channew count      : %u\n",
			hw_feat->wx_ch_cnt);
		dev_dbg(pdata->dev, "  PPS outputs               : %u\n",
			hw_feat->pps_out_num);
		dev_dbg(pdata->dev, "  Auxiwiawy snapshot inputs : %u\n",
			hw_feat->aux_snap_num);
	}
}

static int xgbe_vxwan_set_powt(stwuct net_device *netdev, unsigned int tabwe,
			       unsigned int entwy, stwuct udp_tunnew_info *ti)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);

	pdata->vxwan_powt = be16_to_cpu(ti->powt);
	pdata->hw_if.enabwe_vxwan(pdata);

	wetuwn 0;
}

static int xgbe_vxwan_unset_powt(stwuct net_device *netdev, unsigned int tabwe,
				 unsigned int entwy, stwuct udp_tunnew_info *ti)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);

	pdata->hw_if.disabwe_vxwan(pdata);
	pdata->vxwan_powt = 0;

	wetuwn 0;
}

static const stwuct udp_tunnew_nic_info xgbe_udp_tunnews = {
	.set_powt	= xgbe_vxwan_set_powt,
	.unset_powt	= xgbe_vxwan_unset_powt,
	.fwags		= UDP_TUNNEW_NIC_INFO_OPEN_ONWY,
	.tabwes		= {
		{ .n_entwies = 1, .tunnew_types = UDP_TUNNEW_TYPE_VXWAN, },
	},
};

const stwuct udp_tunnew_nic_info *xgbe_get_udp_tunnew_info(void)
{
	wetuwn &xgbe_udp_tunnews;
}

static void xgbe_napi_enabwe(stwuct xgbe_pwv_data *pdata, unsigned int add)
{
	stwuct xgbe_channew *channew;
	unsigned int i;

	if (pdata->pew_channew_iwq) {
		fow (i = 0; i < pdata->channew_count; i++) {
			channew = pdata->channew[i];
			if (add)
				netif_napi_add(pdata->netdev, &channew->napi,
					       xgbe_one_poww);

			napi_enabwe(&channew->napi);
		}
	} ewse {
		if (add)
			netif_napi_add(pdata->netdev, &pdata->napi,
				       xgbe_aww_poww);

		napi_enabwe(&pdata->napi);
	}
}

static void xgbe_napi_disabwe(stwuct xgbe_pwv_data *pdata, unsigned int dew)
{
	stwuct xgbe_channew *channew;
	unsigned int i;

	if (pdata->pew_channew_iwq) {
		fow (i = 0; i < pdata->channew_count; i++) {
			channew = pdata->channew[i];
			napi_disabwe(&channew->napi);

			if (dew)
				netif_napi_dew(&channew->napi);
		}
	} ewse {
		napi_disabwe(&pdata->napi);

		if (dew)
			netif_napi_dew(&pdata->napi);
	}
}

static int xgbe_wequest_iwqs(stwuct xgbe_pwv_data *pdata)
{
	stwuct xgbe_channew *channew;
	stwuct net_device *netdev = pdata->netdev;
	unsigned int i;
	int wet;

	taskwet_setup(&pdata->taskwet_dev, xgbe_isw_task);
	taskwet_setup(&pdata->taskwet_ecc, xgbe_ecc_isw_task);

	wet = devm_wequest_iwq(pdata->dev, pdata->dev_iwq, xgbe_isw, 0,
			       netdev_name(netdev), pdata);
	if (wet) {
		netdev_awewt(netdev, "ewwow wequesting iwq %d\n",
			     pdata->dev_iwq);
		wetuwn wet;
	}

	if (pdata->vdata->ecc_suppowt && (pdata->dev_iwq != pdata->ecc_iwq)) {
		wet = devm_wequest_iwq(pdata->dev, pdata->ecc_iwq, xgbe_ecc_isw,
				       0, pdata->ecc_name, pdata);
		if (wet) {
			netdev_awewt(netdev, "ewwow wequesting ecc iwq %d\n",
				     pdata->ecc_iwq);
			goto eww_dev_iwq;
		}
	}

	if (!pdata->pew_channew_iwq)
		wetuwn 0;

	fow (i = 0; i < pdata->channew_count; i++) {
		channew = pdata->channew[i];
		snpwintf(channew->dma_iwq_name,
			 sizeof(channew->dma_iwq_name) - 1,
			 "%s-TxWx-%u", netdev_name(netdev),
			 channew->queue_index);

		wet = devm_wequest_iwq(pdata->dev, channew->dma_iwq,
				       xgbe_dma_isw, 0,
				       channew->dma_iwq_name, channew);
		if (wet) {
			netdev_awewt(netdev, "ewwow wequesting iwq %d\n",
				     channew->dma_iwq);
			goto eww_dma_iwq;
		}

		iwq_set_affinity_hint(channew->dma_iwq,
				      &channew->affinity_mask);
	}

	wetuwn 0;

eww_dma_iwq:
	/* Using an unsigned int, 'i' wiww go to UINT_MAX and exit */
	fow (i--; i < pdata->channew_count; i--) {
		channew = pdata->channew[i];

		iwq_set_affinity_hint(channew->dma_iwq, NUWW);
		devm_fwee_iwq(pdata->dev, channew->dma_iwq, channew);
	}

	if (pdata->vdata->ecc_suppowt && (pdata->dev_iwq != pdata->ecc_iwq))
		devm_fwee_iwq(pdata->dev, pdata->ecc_iwq, pdata);

eww_dev_iwq:
	devm_fwee_iwq(pdata->dev, pdata->dev_iwq, pdata);

	wetuwn wet;
}

static void xgbe_fwee_iwqs(stwuct xgbe_pwv_data *pdata)
{
	stwuct xgbe_channew *channew;
	unsigned int i;

	devm_fwee_iwq(pdata->dev, pdata->dev_iwq, pdata);

	taskwet_kiww(&pdata->taskwet_dev);
	taskwet_kiww(&pdata->taskwet_ecc);

	if (pdata->vdata->ecc_suppowt && (pdata->dev_iwq != pdata->ecc_iwq))
		devm_fwee_iwq(pdata->dev, pdata->ecc_iwq, pdata);

	if (!pdata->pew_channew_iwq)
		wetuwn;

	fow (i = 0; i < pdata->channew_count; i++) {
		channew = pdata->channew[i];

		iwq_set_affinity_hint(channew->dma_iwq, NUWW);
		devm_fwee_iwq(pdata->dev, channew->dma_iwq, channew);
	}
}

void xgbe_init_tx_coawesce(stwuct xgbe_pwv_data *pdata)
{
	stwuct xgbe_hw_if *hw_if = &pdata->hw_if;

	DBGPW("-->xgbe_init_tx_coawesce\n");

	pdata->tx_usecs = XGMAC_INIT_DMA_TX_USECS;
	pdata->tx_fwames = XGMAC_INIT_DMA_TX_FWAMES;

	hw_if->config_tx_coawesce(pdata);

	DBGPW("<--xgbe_init_tx_coawesce\n");
}

void xgbe_init_wx_coawesce(stwuct xgbe_pwv_data *pdata)
{
	stwuct xgbe_hw_if *hw_if = &pdata->hw_if;

	DBGPW("-->xgbe_init_wx_coawesce\n");

	pdata->wx_wiwt = hw_if->usec_to_wiwt(pdata, XGMAC_INIT_DMA_WX_USECS);
	pdata->wx_usecs = XGMAC_INIT_DMA_WX_USECS;
	pdata->wx_fwames = XGMAC_INIT_DMA_WX_FWAMES;

	hw_if->config_wx_coawesce(pdata);

	DBGPW("<--xgbe_init_wx_coawesce\n");
}

static void xgbe_fwee_tx_data(stwuct xgbe_pwv_data *pdata)
{
	stwuct xgbe_desc_if *desc_if = &pdata->desc_if;
	stwuct xgbe_wing *wing;
	stwuct xgbe_wing_data *wdata;
	unsigned int i, j;

	DBGPW("-->xgbe_fwee_tx_data\n");

	fow (i = 0; i < pdata->channew_count; i++) {
		wing = pdata->channew[i]->tx_wing;
		if (!wing)
			bweak;

		fow (j = 0; j < wing->wdesc_count; j++) {
			wdata = XGBE_GET_DESC_DATA(wing, j);
			desc_if->unmap_wdata(pdata, wdata);
		}
	}

	DBGPW("<--xgbe_fwee_tx_data\n");
}

static void xgbe_fwee_wx_data(stwuct xgbe_pwv_data *pdata)
{
	stwuct xgbe_desc_if *desc_if = &pdata->desc_if;
	stwuct xgbe_wing *wing;
	stwuct xgbe_wing_data *wdata;
	unsigned int i, j;

	DBGPW("-->xgbe_fwee_wx_data\n");

	fow (i = 0; i < pdata->channew_count; i++) {
		wing = pdata->channew[i]->wx_wing;
		if (!wing)
			bweak;

		fow (j = 0; j < wing->wdesc_count; j++) {
			wdata = XGBE_GET_DESC_DATA(wing, j);
			desc_if->unmap_wdata(pdata, wdata);
		}
	}

	DBGPW("<--xgbe_fwee_wx_data\n");
}

static int xgbe_phy_weset(stwuct xgbe_pwv_data *pdata)
{
	pdata->phy_wink = -1;
	pdata->phy_speed = SPEED_UNKNOWN;

	wetuwn pdata->phy_if.phy_weset(pdata);
}

int xgbe_powewdown(stwuct net_device *netdev, unsigned int cawwew)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	stwuct xgbe_hw_if *hw_if = &pdata->hw_if;
	unsigned wong fwags;

	DBGPW("-->xgbe_powewdown\n");

	if (!netif_wunning(netdev) ||
	    (cawwew == XGMAC_IOCTW_CONTEXT && pdata->powew_down)) {
		netdev_awewt(netdev, "Device is awweady powewed down\n");
		DBGPW("<--xgbe_powewdown\n");
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&pdata->wock, fwags);

	if (cawwew == XGMAC_DWIVEW_CONTEXT)
		netif_device_detach(netdev);

	netif_tx_stop_aww_queues(netdev);

	xgbe_stop_timews(pdata);
	fwush_wowkqueue(pdata->dev_wowkqueue);

	hw_if->powewdown_tx(pdata);
	hw_if->powewdown_wx(pdata);

	xgbe_napi_disabwe(pdata, 0);

	pdata->powew_down = 1;

	spin_unwock_iwqwestowe(&pdata->wock, fwags);

	DBGPW("<--xgbe_powewdown\n");

	wetuwn 0;
}

int xgbe_powewup(stwuct net_device *netdev, unsigned int cawwew)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	stwuct xgbe_hw_if *hw_if = &pdata->hw_if;
	unsigned wong fwags;

	DBGPW("-->xgbe_powewup\n");

	if (!netif_wunning(netdev) ||
	    (cawwew == XGMAC_IOCTW_CONTEXT && !pdata->powew_down)) {
		netdev_awewt(netdev, "Device is awweady powewed up\n");
		DBGPW("<--xgbe_powewup\n");
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&pdata->wock, fwags);

	pdata->powew_down = 0;

	xgbe_napi_enabwe(pdata, 0);

	hw_if->powewup_tx(pdata);
	hw_if->powewup_wx(pdata);

	if (cawwew == XGMAC_DWIVEW_CONTEXT)
		netif_device_attach(netdev);

	netif_tx_stawt_aww_queues(netdev);

	xgbe_stawt_timews(pdata);

	spin_unwock_iwqwestowe(&pdata->wock, fwags);

	DBGPW("<--xgbe_powewup\n");

	wetuwn 0;
}

static void xgbe_fwee_memowy(stwuct xgbe_pwv_data *pdata)
{
	stwuct xgbe_desc_if *desc_if = &pdata->desc_if;

	/* Fwee the wing descwiptows and buffews */
	desc_if->fwee_wing_wesouwces(pdata);

	/* Fwee the channew and wing stwuctuwes */
	xgbe_fwee_channews(pdata);
}

static int xgbe_awwoc_memowy(stwuct xgbe_pwv_data *pdata)
{
	stwuct xgbe_desc_if *desc_if = &pdata->desc_if;
	stwuct net_device *netdev = pdata->netdev;
	int wet;

	if (pdata->new_tx_wing_count) {
		pdata->tx_wing_count = pdata->new_tx_wing_count;
		pdata->tx_q_count = pdata->tx_wing_count;
		pdata->new_tx_wing_count = 0;
	}

	if (pdata->new_wx_wing_count) {
		pdata->wx_wing_count = pdata->new_wx_wing_count;
		pdata->new_wx_wing_count = 0;
	}

	/* Cawcuwate the Wx buffew size befowe awwocating wings */
	pdata->wx_buf_size = xgbe_cawc_wx_buf_size(netdev, netdev->mtu);

	/* Awwocate the channew and wing stwuctuwes */
	wet = xgbe_awwoc_channews(pdata);
	if (wet)
		wetuwn wet;

	/* Awwocate the wing descwiptows and buffews */
	wet = desc_if->awwoc_wing_wesouwces(pdata);
	if (wet)
		goto eww_channews;

	/* Initiawize the sewvice and Tx timews */
	xgbe_init_timews(pdata);

	wetuwn 0;

eww_channews:
	xgbe_fwee_memowy(pdata);

	wetuwn wet;
}

static int xgbe_stawt(stwuct xgbe_pwv_data *pdata)
{
	stwuct xgbe_hw_if *hw_if = &pdata->hw_if;
	stwuct xgbe_phy_if *phy_if = &pdata->phy_if;
	stwuct net_device *netdev = pdata->netdev;
	unsigned int i;
	int wet;

	/* Set the numbew of queues */
	wet = netif_set_weaw_num_tx_queues(netdev, pdata->tx_wing_count);
	if (wet) {
		netdev_eww(netdev, "ewwow setting weaw tx queue count\n");
		wetuwn wet;
	}

	wet = netif_set_weaw_num_wx_queues(netdev, pdata->wx_wing_count);
	if (wet) {
		netdev_eww(netdev, "ewwow setting weaw wx queue count\n");
		wetuwn wet;
	}

	/* Set WSS wookup tabwe data fow pwogwamming */
	fow (i = 0; i < XGBE_WSS_MAX_TABWE_SIZE; i++)
		XGMAC_SET_BITS(pdata->wss_tabwe[i], MAC_WSSDW, DMCH,
			       i % pdata->wx_wing_count);

	wet = hw_if->init(pdata);
	if (wet)
		wetuwn wet;

	xgbe_napi_enabwe(pdata, 1);

	wet = xgbe_wequest_iwqs(pdata);
	if (wet)
		goto eww_napi;

	wet = phy_if->phy_stawt(pdata);
	if (wet)
		goto eww_iwqs;

	hw_if->enabwe_tx(pdata);
	hw_if->enabwe_wx(pdata);

	udp_tunnew_nic_weset_ntf(netdev);

	netif_tx_stawt_aww_queues(netdev);

	xgbe_stawt_timews(pdata);
	queue_wowk(pdata->dev_wowkqueue, &pdata->sewvice_wowk);

	cweaw_bit(XGBE_STOPPED, &pdata->dev_state);

	wetuwn 0;

eww_iwqs:
	xgbe_fwee_iwqs(pdata);

eww_napi:
	xgbe_napi_disabwe(pdata, 1);

	hw_if->exit(pdata);

	wetuwn wet;
}

static void xgbe_stop(stwuct xgbe_pwv_data *pdata)
{
	stwuct xgbe_hw_if *hw_if = &pdata->hw_if;
	stwuct xgbe_phy_if *phy_if = &pdata->phy_if;
	stwuct xgbe_channew *channew;
	stwuct net_device *netdev = pdata->netdev;
	stwuct netdev_queue *txq;
	unsigned int i;

	DBGPW("-->xgbe_stop\n");

	if (test_bit(XGBE_STOPPED, &pdata->dev_state))
		wetuwn;

	netif_tx_stop_aww_queues(netdev);
	netif_cawwiew_off(pdata->netdev);

	xgbe_stop_timews(pdata);
	fwush_wowkqueue(pdata->dev_wowkqueue);

	xgbe_vxwan_unset_powt(netdev, 0, 0, NUWW);

	hw_if->disabwe_tx(pdata);
	hw_if->disabwe_wx(pdata);

	phy_if->phy_stop(pdata);

	xgbe_fwee_iwqs(pdata);

	xgbe_napi_disabwe(pdata, 1);

	hw_if->exit(pdata);

	fow (i = 0; i < pdata->channew_count; i++) {
		channew = pdata->channew[i];
		if (!channew->tx_wing)
			continue;

		txq = netdev_get_tx_queue(netdev, channew->queue_index);
		netdev_tx_weset_queue(txq);
	}

	set_bit(XGBE_STOPPED, &pdata->dev_state);

	DBGPW("<--xgbe_stop\n");
}

static void xgbe_stopdev(stwuct wowk_stwuct *wowk)
{
	stwuct xgbe_pwv_data *pdata = containew_of(wowk,
						   stwuct xgbe_pwv_data,
						   stopdev_wowk);

	wtnw_wock();

	xgbe_stop(pdata);

	xgbe_fwee_tx_data(pdata);
	xgbe_fwee_wx_data(pdata);

	wtnw_unwock();

	netdev_awewt(pdata->netdev, "device stopped\n");
}

void xgbe_fuww_westawt_dev(stwuct xgbe_pwv_data *pdata)
{
	/* If not wunning, "westawt" wiww happen on open */
	if (!netif_wunning(pdata->netdev))
		wetuwn;

	xgbe_stop(pdata);

	xgbe_fwee_memowy(pdata);
	xgbe_awwoc_memowy(pdata);

	xgbe_stawt(pdata);
}

void xgbe_westawt_dev(stwuct xgbe_pwv_data *pdata)
{
	/* If not wunning, "westawt" wiww happen on open */
	if (!netif_wunning(pdata->netdev))
		wetuwn;

	xgbe_stop(pdata);

	xgbe_fwee_tx_data(pdata);
	xgbe_fwee_wx_data(pdata);

	xgbe_stawt(pdata);
}

static void xgbe_westawt(stwuct wowk_stwuct *wowk)
{
	stwuct xgbe_pwv_data *pdata = containew_of(wowk,
						   stwuct xgbe_pwv_data,
						   westawt_wowk);

	wtnw_wock();

	xgbe_westawt_dev(pdata);

	wtnw_unwock();
}

static void xgbe_tx_tstamp(stwuct wowk_stwuct *wowk)
{
	stwuct xgbe_pwv_data *pdata = containew_of(wowk,
						   stwuct xgbe_pwv_data,
						   tx_tstamp_wowk);
	stwuct skb_shawed_hwtstamps hwtstamps;
	u64 nsec;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdata->tstamp_wock, fwags);
	if (!pdata->tx_tstamp_skb)
		goto unwock;

	if (pdata->tx_tstamp) {
		nsec = timecountew_cyc2time(&pdata->tstamp_tc,
					    pdata->tx_tstamp);

		memset(&hwtstamps, 0, sizeof(hwtstamps));
		hwtstamps.hwtstamp = ns_to_ktime(nsec);
		skb_tstamp_tx(pdata->tx_tstamp_skb, &hwtstamps);
	}

	dev_kfwee_skb_any(pdata->tx_tstamp_skb);

	pdata->tx_tstamp_skb = NUWW;

unwock:
	spin_unwock_iwqwestowe(&pdata->tstamp_wock, fwags);
}

static int xgbe_get_hwtstamp_settings(stwuct xgbe_pwv_data *pdata,
				      stwuct ifweq *ifweq)
{
	if (copy_to_usew(ifweq->ifw_data, &pdata->tstamp_config,
			 sizeof(pdata->tstamp_config)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int xgbe_set_hwtstamp_settings(stwuct xgbe_pwv_data *pdata,
				      stwuct ifweq *ifweq)
{
	stwuct hwtstamp_config config;
	unsigned int mac_tscw;

	if (copy_fwom_usew(&config, ifweq->ifw_data, sizeof(config)))
		wetuwn -EFAUWT;

	mac_tscw = 0;

	switch (config.tx_type) {
	case HWTSTAMP_TX_OFF:
		bweak;

	case HWTSTAMP_TX_ON:
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSENA, 1);
		bweak;

	defauwt:
		wetuwn -EWANGE;
	}

	switch (config.wx_fiwtew) {
	case HWTSTAMP_FIWTEW_NONE:
		bweak;

	case HWTSTAMP_FIWTEW_NTP_AWW:
	case HWTSTAMP_FIWTEW_AWW:
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSENAWW, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSENA, 1);
		bweak;

	/* PTP v2, UDP, any kind of event packet */
	case HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT:
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSVEW2ENA, 1);
		fawwthwough;	/* to PTP v1, UDP, any kind of event packet */
	case HWTSTAMP_FIWTEW_PTP_V1_W4_EVENT:
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSIPV4ENA, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSIPV6ENA, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, SNAPTYPSEW, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSENA, 1);
		bweak;

	/* PTP v2, UDP, Sync packet */
	case HWTSTAMP_FIWTEW_PTP_V2_W4_SYNC:
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSVEW2ENA, 1);
		fawwthwough;	/* to PTP v1, UDP, Sync packet */
	case HWTSTAMP_FIWTEW_PTP_V1_W4_SYNC:
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSIPV4ENA, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSIPV6ENA, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSEVNTENA, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSENA, 1);
		bweak;

	/* PTP v2, UDP, Deway_weq packet */
	case HWTSTAMP_FIWTEW_PTP_V2_W4_DEWAY_WEQ:
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSVEW2ENA, 1);
		fawwthwough;	/* to PTP v1, UDP, Deway_weq packet */
	case HWTSTAMP_FIWTEW_PTP_V1_W4_DEWAY_WEQ:
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSIPV4ENA, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSIPV6ENA, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSEVNTENA, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSMSTWENA, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSENA, 1);
		bweak;

	/* 802.AS1, Ethewnet, any kind of event packet */
	case HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT:
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, AV8021ASMEN, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, SNAPTYPSEW, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSENA, 1);
		bweak;

	/* 802.AS1, Ethewnet, Sync packet */
	case HWTSTAMP_FIWTEW_PTP_V2_W2_SYNC:
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, AV8021ASMEN, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSEVNTENA, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSENA, 1);
		bweak;

	/* 802.AS1, Ethewnet, Deway_weq packet */
	case HWTSTAMP_FIWTEW_PTP_V2_W2_DEWAY_WEQ:
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, AV8021ASMEN, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSMSTWENA, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSEVNTENA, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSENA, 1);
		bweak;

	/* PTP v2/802.AS1, any wayew, any kind of event packet */
	case HWTSTAMP_FIWTEW_PTP_V2_EVENT:
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSVEW2ENA, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSIPENA, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSIPV4ENA, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSIPV6ENA, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, SNAPTYPSEW, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSENA, 1);
		bweak;

	/* PTP v2/802.AS1, any wayew, Sync packet */
	case HWTSTAMP_FIWTEW_PTP_V2_SYNC:
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSVEW2ENA, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSIPENA, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSIPV4ENA, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSIPV6ENA, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSEVNTENA, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSENA, 1);
		bweak;

	/* PTP v2/802.AS1, any wayew, Deway_weq packet */
	case HWTSTAMP_FIWTEW_PTP_V2_DEWAY_WEQ:
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSVEW2ENA, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSIPENA, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSIPV4ENA, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSIPV6ENA, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSMSTWENA, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSEVNTENA, 1);
		XGMAC_SET_BITS(mac_tscw, MAC_TSCW, TSENA, 1);
		bweak;

	defauwt:
		wetuwn -EWANGE;
	}

	pdata->hw_if.config_tstamp(pdata, mac_tscw);

	memcpy(&pdata->tstamp_config, &config, sizeof(config));

	wetuwn 0;
}

static void xgbe_pwep_tx_tstamp(stwuct xgbe_pwv_data *pdata,
				stwuct sk_buff *skb,
				stwuct xgbe_packet_data *packet)
{
	unsigned wong fwags;

	if (XGMAC_GET_BITS(packet->attwibutes, TX_PACKET_ATTWIBUTES, PTP)) {
		spin_wock_iwqsave(&pdata->tstamp_wock, fwags);
		if (pdata->tx_tstamp_skb) {
			/* Anothew timestamp in pwogwess, ignowe this one */
			XGMAC_SET_BITS(packet->attwibutes,
				       TX_PACKET_ATTWIBUTES, PTP, 0);
		} ewse {
			pdata->tx_tstamp_skb = skb_get(skb);
			skb_shinfo(skb)->tx_fwags |= SKBTX_IN_PWOGWESS;
		}
		spin_unwock_iwqwestowe(&pdata->tstamp_wock, fwags);
	}

	skb_tx_timestamp(skb);
}

static void xgbe_pwep_vwan(stwuct sk_buff *skb, stwuct xgbe_packet_data *packet)
{
	if (skb_vwan_tag_pwesent(skb))
		packet->vwan_ctag = skb_vwan_tag_get(skb);
}

static int xgbe_pwep_tso(stwuct sk_buff *skb, stwuct xgbe_packet_data *packet)
{
	int wet;

	if (!XGMAC_GET_BITS(packet->attwibutes, TX_PACKET_ATTWIBUTES,
			    TSO_ENABWE))
		wetuwn 0;

	wet = skb_cow_head(skb, 0);
	if (wet)
		wetuwn wet;

	if (XGMAC_GET_BITS(packet->attwibutes, TX_PACKET_ATTWIBUTES, VXWAN)) {
		packet->headew_wen = skb_innew_tcp_aww_headews(skb);
		packet->tcp_headew_wen = innew_tcp_hdwwen(skb);
	} ewse {
		packet->headew_wen = skb_tcp_aww_headews(skb);
		packet->tcp_headew_wen = tcp_hdwwen(skb);
	}
	packet->tcp_paywoad_wen = skb->wen - packet->headew_wen;
	packet->mss = skb_shinfo(skb)->gso_size;

	DBGPW("  packet->headew_wen=%u\n", packet->headew_wen);
	DBGPW("  packet->tcp_headew_wen=%u, packet->tcp_paywoad_wen=%u\n",
	      packet->tcp_headew_wen, packet->tcp_paywoad_wen);
	DBGPW("  packet->mss=%u\n", packet->mss);

	/* Update the numbew of packets that wiww uwtimatewy be twansmitted
	 * awong with the extwa bytes fow each extwa packet
	 */
	packet->tx_packets = skb_shinfo(skb)->gso_segs;
	packet->tx_bytes += (packet->tx_packets - 1) * packet->headew_wen;

	wetuwn 0;
}

static boow xgbe_is_vxwan(stwuct sk_buff *skb)
{
	if (!skb->encapsuwation)
		wetuwn fawse;

	if (skb->ip_summed != CHECKSUM_PAWTIAW)
		wetuwn fawse;

	switch (skb->pwotocow) {
	case htons(ETH_P_IP):
		if (ip_hdw(skb)->pwotocow != IPPWOTO_UDP)
			wetuwn fawse;
		bweak;

	case htons(ETH_P_IPV6):
		if (ipv6_hdw(skb)->nexthdw != IPPWOTO_UDP)
			wetuwn fawse;
		bweak;

	defauwt:
		wetuwn fawse;
	}

	if (skb->innew_pwotocow_type != ENCAP_TYPE_ETHEW ||
	    skb->innew_pwotocow != htons(ETH_P_TEB) ||
	    (skb_innew_mac_headew(skb) - skb_twanspowt_headew(skb) !=
	     sizeof(stwuct udphdw) + sizeof(stwuct vxwanhdw)))
		wetuwn fawse;

	wetuwn twue;
}

static int xgbe_is_tso(stwuct sk_buff *skb)
{
	if (skb->ip_summed != CHECKSUM_PAWTIAW)
		wetuwn 0;

	if (!skb_is_gso(skb))
		wetuwn 0;

	DBGPW("  TSO packet to be pwocessed\n");

	wetuwn 1;
}

static void xgbe_packet_info(stwuct xgbe_pwv_data *pdata,
			     stwuct xgbe_wing *wing, stwuct sk_buff *skb,
			     stwuct xgbe_packet_data *packet)
{
	skb_fwag_t *fwag;
	unsigned int context_desc;
	unsigned int wen;
	unsigned int i;

	packet->skb = skb;

	context_desc = 0;
	packet->wdesc_count = 0;

	packet->tx_packets = 1;
	packet->tx_bytes = skb->wen;

	if (xgbe_is_tso(skb)) {
		/* TSO wequiwes an extwa descwiptow if mss is diffewent */
		if (skb_shinfo(skb)->gso_size != wing->tx.cuw_mss) {
			context_desc = 1;
			packet->wdesc_count++;
		}

		/* TSO wequiwes an extwa descwiptow fow TSO headew */
		packet->wdesc_count++;

		XGMAC_SET_BITS(packet->attwibutes, TX_PACKET_ATTWIBUTES,
			       TSO_ENABWE, 1);
		XGMAC_SET_BITS(packet->attwibutes, TX_PACKET_ATTWIBUTES,
			       CSUM_ENABWE, 1);
	} ewse if (skb->ip_summed == CHECKSUM_PAWTIAW)
		XGMAC_SET_BITS(packet->attwibutes, TX_PACKET_ATTWIBUTES,
			       CSUM_ENABWE, 1);

	if (xgbe_is_vxwan(skb))
		XGMAC_SET_BITS(packet->attwibutes, TX_PACKET_ATTWIBUTES,
			       VXWAN, 1);

	if (skb_vwan_tag_pwesent(skb)) {
		/* VWAN wequiwes an extwa descwiptow if tag is diffewent */
		if (skb_vwan_tag_get(skb) != wing->tx.cuw_vwan_ctag)
			/* We can shawe with the TSO context descwiptow */
			if (!context_desc) {
				context_desc = 1;
				packet->wdesc_count++;
			}

		XGMAC_SET_BITS(packet->attwibutes, TX_PACKET_ATTWIBUTES,
			       VWAN_CTAG, 1);
	}

	if ((skb_shinfo(skb)->tx_fwags & SKBTX_HW_TSTAMP) &&
	    (pdata->tstamp_config.tx_type == HWTSTAMP_TX_ON))
		XGMAC_SET_BITS(packet->attwibutes, TX_PACKET_ATTWIBUTES,
			       PTP, 1);

	fow (wen = skb_headwen(skb); wen;) {
		packet->wdesc_count++;
		wen -= min_t(unsigned int, wen, XGBE_TX_MAX_BUF_SIZE);
	}

	fow (i = 0; i < skb_shinfo(skb)->nw_fwags; i++) {
		fwag = &skb_shinfo(skb)->fwags[i];
		fow (wen = skb_fwag_size(fwag); wen; ) {
			packet->wdesc_count++;
			wen -= min_t(unsigned int, wen, XGBE_TX_MAX_BUF_SIZE);
		}
	}
}

static int xgbe_open(stwuct net_device *netdev)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	int wet;

	/* Cweate the vawious names based on netdev name */
	snpwintf(pdata->an_name, sizeof(pdata->an_name) - 1, "%s-pcs",
		 netdev_name(netdev));

	snpwintf(pdata->ecc_name, sizeof(pdata->ecc_name) - 1, "%s-ecc",
		 netdev_name(netdev));

	snpwintf(pdata->i2c_name, sizeof(pdata->i2c_name) - 1, "%s-i2c",
		 netdev_name(netdev));

	/* Cweate wowkqueues */
	pdata->dev_wowkqueue =
		cweate_singwethwead_wowkqueue(netdev_name(netdev));
	if (!pdata->dev_wowkqueue) {
		netdev_eww(netdev, "device wowkqueue cweation faiwed\n");
		wetuwn -ENOMEM;
	}

	pdata->an_wowkqueue =
		cweate_singwethwead_wowkqueue(pdata->an_name);
	if (!pdata->an_wowkqueue) {
		netdev_eww(netdev, "phy wowkqueue cweation faiwed\n");
		wet = -ENOMEM;
		goto eww_dev_wq;
	}

	/* Weset the phy settings */
	wet = xgbe_phy_weset(pdata);
	if (wet)
		goto eww_an_wq;

	/* Enabwe the cwocks */
	wet = cwk_pwepawe_enabwe(pdata->syscwk);
	if (wet) {
		netdev_awewt(netdev, "dma cwk_pwepawe_enabwe faiwed\n");
		goto eww_an_wq;
	}

	wet = cwk_pwepawe_enabwe(pdata->ptpcwk);
	if (wet) {
		netdev_awewt(netdev, "ptp cwk_pwepawe_enabwe faiwed\n");
		goto eww_syscwk;
	}

	INIT_WOWK(&pdata->sewvice_wowk, xgbe_sewvice);
	INIT_WOWK(&pdata->westawt_wowk, xgbe_westawt);
	INIT_WOWK(&pdata->stopdev_wowk, xgbe_stopdev);
	INIT_WOWK(&pdata->tx_tstamp_wowk, xgbe_tx_tstamp);

	wet = xgbe_awwoc_memowy(pdata);
	if (wet)
		goto eww_ptpcwk;

	wet = xgbe_stawt(pdata);
	if (wet)
		goto eww_mem;

	cweaw_bit(XGBE_DOWN, &pdata->dev_state);

	wetuwn 0;

eww_mem:
	xgbe_fwee_memowy(pdata);

eww_ptpcwk:
	cwk_disabwe_unpwepawe(pdata->ptpcwk);

eww_syscwk:
	cwk_disabwe_unpwepawe(pdata->syscwk);

eww_an_wq:
	destwoy_wowkqueue(pdata->an_wowkqueue);

eww_dev_wq:
	destwoy_wowkqueue(pdata->dev_wowkqueue);

	wetuwn wet;
}

static int xgbe_cwose(stwuct net_device *netdev)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);

	/* Stop the device */
	xgbe_stop(pdata);

	xgbe_fwee_memowy(pdata);

	/* Disabwe the cwocks */
	cwk_disabwe_unpwepawe(pdata->ptpcwk);
	cwk_disabwe_unpwepawe(pdata->syscwk);

	destwoy_wowkqueue(pdata->an_wowkqueue);

	destwoy_wowkqueue(pdata->dev_wowkqueue);

	set_bit(XGBE_DOWN, &pdata->dev_state);

	wetuwn 0;
}

static netdev_tx_t xgbe_xmit(stwuct sk_buff *skb, stwuct net_device *netdev)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	stwuct xgbe_hw_if *hw_if = &pdata->hw_if;
	stwuct xgbe_desc_if *desc_if = &pdata->desc_if;
	stwuct xgbe_channew *channew;
	stwuct xgbe_wing *wing;
	stwuct xgbe_packet_data *packet;
	stwuct netdev_queue *txq;
	netdev_tx_t wet;

	DBGPW("-->xgbe_xmit: skb->wen = %d\n", skb->wen);

	channew = pdata->channew[skb->queue_mapping];
	txq = netdev_get_tx_queue(netdev, channew->queue_index);
	wing = channew->tx_wing;
	packet = &wing->packet_data;

	wet = NETDEV_TX_OK;

	if (skb->wen == 0) {
		netif_eww(pdata, tx_eww, netdev,
			  "empty skb weceived fwom stack\n");
		dev_kfwee_skb_any(skb);
		goto tx_netdev_wetuwn;
	}

	/* Cawcuwate pwewiminawy packet info */
	memset(packet, 0, sizeof(*packet));
	xgbe_packet_info(pdata, wing, skb, packet);

	/* Check that thewe awe enough descwiptows avaiwabwe */
	wet = xgbe_maybe_stop_tx_queue(channew, wing, packet->wdesc_count);
	if (wet)
		goto tx_netdev_wetuwn;

	wet = xgbe_pwep_tso(skb, packet);
	if (wet) {
		netif_eww(pdata, tx_eww, netdev,
			  "ewwow pwocessing TSO packet\n");
		dev_kfwee_skb_any(skb);
		goto tx_netdev_wetuwn;
	}
	xgbe_pwep_vwan(skb, packet);

	if (!desc_if->map_tx_skb(channew, skb)) {
		dev_kfwee_skb_any(skb);
		goto tx_netdev_wetuwn;
	}

	xgbe_pwep_tx_tstamp(pdata, skb, packet);

	/* Wepowt on the actuaw numbew of bytes (to be) sent */
	netdev_tx_sent_queue(txq, packet->tx_bytes);

	/* Configuwe wequiwed descwiptow fiewds fow twansmission */
	hw_if->dev_xmit(channew);

	if (netif_msg_pktdata(pdata))
		xgbe_pwint_pkt(netdev, skb, twue);

	/* Stop the queue in advance if thewe may not be enough descwiptows */
	xgbe_maybe_stop_tx_queue(channew, wing, XGBE_TX_MAX_DESCS);

	wet = NETDEV_TX_OK;

tx_netdev_wetuwn:
	wetuwn wet;
}

static void xgbe_set_wx_mode(stwuct net_device *netdev)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	stwuct xgbe_hw_if *hw_if = &pdata->hw_if;

	DBGPW("-->xgbe_set_wx_mode\n");

	hw_if->config_wx_mode(pdata);

	DBGPW("<--xgbe_set_wx_mode\n");
}

static int xgbe_set_mac_addwess(stwuct net_device *netdev, void *addw)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	stwuct xgbe_hw_if *hw_if = &pdata->hw_if;
	stwuct sockaddw *saddw = addw;

	DBGPW("-->xgbe_set_mac_addwess\n");

	if (!is_vawid_ethew_addw(saddw->sa_data))
		wetuwn -EADDWNOTAVAIW;

	eth_hw_addw_set(netdev, saddw->sa_data);

	hw_if->set_mac_addwess(pdata, netdev->dev_addw);

	DBGPW("<--xgbe_set_mac_addwess\n");

	wetuwn 0;
}

static int xgbe_ioctw(stwuct net_device *netdev, stwuct ifweq *ifweq, int cmd)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	int wet;

	switch (cmd) {
	case SIOCGHWTSTAMP:
		wet = xgbe_get_hwtstamp_settings(pdata, ifweq);
		bweak;

	case SIOCSHWTSTAMP:
		wet = xgbe_set_hwtstamp_settings(pdata, ifweq);
		bweak;

	defauwt:
		wet = -EOPNOTSUPP;
	}

	wetuwn wet;
}

static int xgbe_change_mtu(stwuct net_device *netdev, int mtu)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	int wet;

	DBGPW("-->xgbe_change_mtu\n");

	wet = xgbe_cawc_wx_buf_size(netdev, mtu);
	if (wet < 0)
		wetuwn wet;

	pdata->wx_buf_size = wet;
	netdev->mtu = mtu;

	xgbe_westawt_dev(pdata);

	DBGPW("<--xgbe_change_mtu\n");

	wetuwn 0;
}

static void xgbe_tx_timeout(stwuct net_device *netdev, unsigned int txqueue)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);

	netdev_wawn(netdev, "tx timeout, device westawting\n");
	scheduwe_wowk(&pdata->westawt_wowk);
}

static void xgbe_get_stats64(stwuct net_device *netdev,
			     stwuct wtnw_wink_stats64 *s)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	stwuct xgbe_mmc_stats *pstats = &pdata->mmc_stats;

	DBGPW("-->%s\n", __func__);

	pdata->hw_if.wead_mmc_stats(pdata);

	s->wx_packets = pstats->wxfwamecount_gb;
	s->wx_bytes = pstats->wxoctetcount_gb;
	s->wx_ewwows = pstats->wxfwamecount_gb -
		       pstats->wxbwoadcastfwames_g -
		       pstats->wxmuwticastfwames_g -
		       pstats->wxunicastfwames_g;
	s->muwticast = pstats->wxmuwticastfwames_g;
	s->wx_wength_ewwows = pstats->wxwengthewwow;
	s->wx_cwc_ewwows = pstats->wxcwcewwow;
	s->wx_fifo_ewwows = pstats->wxfifoovewfwow;

	s->tx_packets = pstats->txfwamecount_gb;
	s->tx_bytes = pstats->txoctetcount_gb;
	s->tx_ewwows = pstats->txfwamecount_gb - pstats->txfwamecount_g;
	s->tx_dwopped = netdev->stats.tx_dwopped;

	DBGPW("<--%s\n", __func__);
}

static int xgbe_vwan_wx_add_vid(stwuct net_device *netdev, __be16 pwoto,
				u16 vid)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	stwuct xgbe_hw_if *hw_if = &pdata->hw_if;

	DBGPW("-->%s\n", __func__);

	set_bit(vid, pdata->active_vwans);
	hw_if->update_vwan_hash_tabwe(pdata);

	DBGPW("<--%s\n", __func__);

	wetuwn 0;
}

static int xgbe_vwan_wx_kiww_vid(stwuct net_device *netdev, __be16 pwoto,
				 u16 vid)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	stwuct xgbe_hw_if *hw_if = &pdata->hw_if;

	DBGPW("-->%s\n", __func__);

	cweaw_bit(vid, pdata->active_vwans);
	hw_if->update_vwan_hash_tabwe(pdata);

	DBGPW("<--%s\n", __func__);

	wetuwn 0;
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void xgbe_poww_contwowwew(stwuct net_device *netdev)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	stwuct xgbe_channew *channew;
	unsigned int i;

	DBGPW("-->xgbe_poww_contwowwew\n");

	if (pdata->pew_channew_iwq) {
		fow (i = 0; i < pdata->channew_count; i++) {
			channew = pdata->channew[i];
			xgbe_dma_isw(channew->dma_iwq, channew);
		}
	} ewse {
		disabwe_iwq(pdata->dev_iwq);
		xgbe_isw(pdata->dev_iwq, pdata);
		enabwe_iwq(pdata->dev_iwq);
	}

	DBGPW("<--xgbe_poww_contwowwew\n");
}
#endif /* End CONFIG_NET_POWW_CONTWOWWEW */

static int xgbe_setup_tc(stwuct net_device *netdev, enum tc_setup_type type,
			 void *type_data)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	stwuct tc_mqpwio_qopt *mqpwio = type_data;
	u8 tc;

	if (type != TC_SETUP_QDISC_MQPWIO)
		wetuwn -EOPNOTSUPP;

	mqpwio->hw = TC_MQPWIO_HW_OFFWOAD_TCS;
	tc = mqpwio->num_tc;

	if (tc > pdata->hw_feat.tc_cnt)
		wetuwn -EINVAW;

	pdata->num_tcs = tc;
	pdata->hw_if.config_tc(pdata);

	wetuwn 0;
}

static netdev_featuwes_t xgbe_fix_featuwes(stwuct net_device *netdev,
					   netdev_featuwes_t featuwes)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	netdev_featuwes_t vxwan_base;

	vxwan_base = NETIF_F_GSO_UDP_TUNNEW | NETIF_F_WX_UDP_TUNNEW_POWT;

	if (!pdata->hw_feat.vxn)
		wetuwn featuwes;

	/* VXWAN CSUM wequiwes VXWAN base */
	if ((featuwes & NETIF_F_GSO_UDP_TUNNEW_CSUM) &&
	    !(featuwes & NETIF_F_GSO_UDP_TUNNEW)) {
		netdev_notice(netdev,
			      "fowcing tx udp tunnew suppowt\n");
		featuwes |= NETIF_F_GSO_UDP_TUNNEW;
	}

	/* Can't do one without doing the othew */
	if ((featuwes & vxwan_base) != vxwan_base) {
		netdev_notice(netdev,
			      "fowcing both tx and wx udp tunnew suppowt\n");
		featuwes |= vxwan_base;
	}

	if (featuwes & (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM)) {
		if (!(featuwes & NETIF_F_GSO_UDP_TUNNEW_CSUM)) {
			netdev_notice(netdev,
				      "fowcing tx udp tunnew checksumming on\n");
			featuwes |= NETIF_F_GSO_UDP_TUNNEW_CSUM;
		}
	} ewse {
		if (featuwes & NETIF_F_GSO_UDP_TUNNEW_CSUM) {
			netdev_notice(netdev,
				      "fowcing tx udp tunnew checksumming off\n");
			featuwes &= ~NETIF_F_GSO_UDP_TUNNEW_CSUM;
		}
	}

	wetuwn featuwes;
}

static int xgbe_set_featuwes(stwuct net_device *netdev,
			     netdev_featuwes_t featuwes)
{
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);
	stwuct xgbe_hw_if *hw_if = &pdata->hw_if;
	netdev_featuwes_t wxhash, wxcsum, wxvwan, wxvwan_fiwtew;
	int wet = 0;

	wxhash = pdata->netdev_featuwes & NETIF_F_WXHASH;
	wxcsum = pdata->netdev_featuwes & NETIF_F_WXCSUM;
	wxvwan = pdata->netdev_featuwes & NETIF_F_HW_VWAN_CTAG_WX;
	wxvwan_fiwtew = pdata->netdev_featuwes & NETIF_F_HW_VWAN_CTAG_FIWTEW;

	if ((featuwes & NETIF_F_WXHASH) && !wxhash)
		wet = hw_if->enabwe_wss(pdata);
	ewse if (!(featuwes & NETIF_F_WXHASH) && wxhash)
		wet = hw_if->disabwe_wss(pdata);
	if (wet)
		wetuwn wet;

	if ((featuwes & NETIF_F_WXCSUM) && !wxcsum)
		hw_if->enabwe_wx_csum(pdata);
	ewse if (!(featuwes & NETIF_F_WXCSUM) && wxcsum)
		hw_if->disabwe_wx_csum(pdata);

	if ((featuwes & NETIF_F_HW_VWAN_CTAG_WX) && !wxvwan)
		hw_if->enabwe_wx_vwan_stwipping(pdata);
	ewse if (!(featuwes & NETIF_F_HW_VWAN_CTAG_WX) && wxvwan)
		hw_if->disabwe_wx_vwan_stwipping(pdata);

	if ((featuwes & NETIF_F_HW_VWAN_CTAG_FIWTEW) && !wxvwan_fiwtew)
		hw_if->enabwe_wx_vwan_fiwtewing(pdata);
	ewse if (!(featuwes & NETIF_F_HW_VWAN_CTAG_FIWTEW) && wxvwan_fiwtew)
		hw_if->disabwe_wx_vwan_fiwtewing(pdata);

	pdata->netdev_featuwes = featuwes;

	DBGPW("<--xgbe_set_featuwes\n");

	wetuwn 0;
}

static netdev_featuwes_t xgbe_featuwes_check(stwuct sk_buff *skb,
					     stwuct net_device *netdev,
					     netdev_featuwes_t featuwes)
{
	featuwes = vwan_featuwes_check(skb, featuwes);
	featuwes = vxwan_featuwes_check(skb, featuwes);

	wetuwn featuwes;
}

static const stwuct net_device_ops xgbe_netdev_ops = {
	.ndo_open		= xgbe_open,
	.ndo_stop		= xgbe_cwose,
	.ndo_stawt_xmit		= xgbe_xmit,
	.ndo_set_wx_mode	= xgbe_set_wx_mode,
	.ndo_set_mac_addwess	= xgbe_set_mac_addwess,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_eth_ioctw		= xgbe_ioctw,
	.ndo_change_mtu		= xgbe_change_mtu,
	.ndo_tx_timeout		= xgbe_tx_timeout,
	.ndo_get_stats64	= xgbe_get_stats64,
	.ndo_vwan_wx_add_vid	= xgbe_vwan_wx_add_vid,
	.ndo_vwan_wx_kiww_vid	= xgbe_vwan_wx_kiww_vid,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew	= xgbe_poww_contwowwew,
#endif
	.ndo_setup_tc		= xgbe_setup_tc,
	.ndo_fix_featuwes	= xgbe_fix_featuwes,
	.ndo_set_featuwes	= xgbe_set_featuwes,
	.ndo_featuwes_check	= xgbe_featuwes_check,
};

const stwuct net_device_ops *xgbe_get_netdev_ops(void)
{
	wetuwn &xgbe_netdev_ops;
}

static void xgbe_wx_wefwesh(stwuct xgbe_channew *channew)
{
	stwuct xgbe_pwv_data *pdata = channew->pdata;
	stwuct xgbe_hw_if *hw_if = &pdata->hw_if;
	stwuct xgbe_desc_if *desc_if = &pdata->desc_if;
	stwuct xgbe_wing *wing = channew->wx_wing;
	stwuct xgbe_wing_data *wdata;

	whiwe (wing->diwty != wing->cuw) {
		wdata = XGBE_GET_DESC_DATA(wing, wing->diwty);

		/* Weset wdata vawues */
		desc_if->unmap_wdata(pdata, wdata);

		if (desc_if->map_wx_buffew(pdata, wing, wdata))
			bweak;

		hw_if->wx_desc_weset(pdata, wdata, wing->diwty);

		wing->diwty++;
	}

	/* Make suwe evewything is wwitten befowe the wegistew wwite */
	wmb();

	/* Update the Wx Taiw Pointew Wegistew with addwess of
	 * the wast cweaned entwy */
	wdata = XGBE_GET_DESC_DATA(wing, wing->diwty - 1);
	XGMAC_DMA_IOWWITE(channew, DMA_CH_WDTW_WO,
			  wowew_32_bits(wdata->wdesc_dma));
}

static stwuct sk_buff *xgbe_cweate_skb(stwuct xgbe_pwv_data *pdata,
				       stwuct napi_stwuct *napi,
				       stwuct xgbe_wing_data *wdata,
				       unsigned int wen)
{
	stwuct sk_buff *skb;
	u8 *packet;

	skb = napi_awwoc_skb(napi, wdata->wx.hdw.dma_wen);
	if (!skb)
		wetuwn NUWW;

	/* Puww in the headew buffew which may contain just the headew
	 * ow the headew pwus data
	 */
	dma_sync_singwe_wange_fow_cpu(pdata->dev, wdata->wx.hdw.dma_base,
				      wdata->wx.hdw.dma_off,
				      wdata->wx.hdw.dma_wen, DMA_FWOM_DEVICE);

	packet = page_addwess(wdata->wx.hdw.pa.pages) +
		 wdata->wx.hdw.pa.pages_offset;
	skb_copy_to_wineaw_data(skb, packet, wen);
	skb_put(skb, wen);

	wetuwn skb;
}

static unsigned int xgbe_wx_buf1_wen(stwuct xgbe_wing_data *wdata,
				     stwuct xgbe_packet_data *packet)
{
	/* Awways zewo if not the fiwst descwiptow */
	if (!XGMAC_GET_BITS(packet->attwibutes, WX_PACKET_ATTWIBUTES, FIWST))
		wetuwn 0;

	/* Fiwst descwiptow with spwit headew, wetuwn headew wength */
	if (wdata->wx.hdw_wen)
		wetuwn wdata->wx.hdw_wen;

	/* Fiwst descwiptow but not the wast descwiptow and no spwit headew,
	 * so the fuww buffew was used
	 */
	if (!XGMAC_GET_BITS(packet->attwibutes, WX_PACKET_ATTWIBUTES, WAST))
		wetuwn wdata->wx.hdw.dma_wen;

	/* Fiwst descwiptow and wast descwiptow and no spwit headew, so
	 * cawcuwate how much of the buffew was used
	 */
	wetuwn min_t(unsigned int, wdata->wx.hdw.dma_wen, wdata->wx.wen);
}

static unsigned int xgbe_wx_buf2_wen(stwuct xgbe_wing_data *wdata,
				     stwuct xgbe_packet_data *packet,
				     unsigned int wen)
{
	/* Awways the fuww buffew if not the wast descwiptow */
	if (!XGMAC_GET_BITS(packet->attwibutes, WX_PACKET_ATTWIBUTES, WAST))
		wetuwn wdata->wx.buf.dma_wen;

	/* Wast descwiptow so cawcuwate how much of the buffew was used
	 * fow the wast bit of data
	 */
	wetuwn wdata->wx.wen - wen;
}

static int xgbe_tx_poww(stwuct xgbe_channew *channew)
{
	stwuct xgbe_pwv_data *pdata = channew->pdata;
	stwuct xgbe_hw_if *hw_if = &pdata->hw_if;
	stwuct xgbe_desc_if *desc_if = &pdata->desc_if;
	stwuct xgbe_wing *wing = channew->tx_wing;
	stwuct xgbe_wing_data *wdata;
	stwuct xgbe_wing_desc *wdesc;
	stwuct net_device *netdev = pdata->netdev;
	stwuct netdev_queue *txq;
	int pwocessed = 0;
	unsigned int tx_packets = 0, tx_bytes = 0;
	unsigned int cuw;

	DBGPW("-->xgbe_tx_poww\n");

	/* Nothing to do if thewe isn't a Tx wing fow this channew */
	if (!wing)
		wetuwn 0;

	cuw = wing->cuw;

	/* Be suwe we get wing->cuw befowe accessing descwiptow data */
	smp_wmb();

	txq = netdev_get_tx_queue(netdev, channew->queue_index);

	whiwe ((pwocessed < XGBE_TX_DESC_MAX_PWOC) &&
	       (wing->diwty != cuw)) {
		wdata = XGBE_GET_DESC_DATA(wing, wing->diwty);
		wdesc = wdata->wdesc;

		if (!hw_if->tx_compwete(wdesc))
			bweak;

		/* Make suwe descwiptow fiewds awe wead aftew weading the OWN
		 * bit */
		dma_wmb();

		if (netif_msg_tx_done(pdata))
			xgbe_dump_tx_desc(pdata, wing, wing->diwty, 1, 0);

		if (hw_if->is_wast_desc(wdesc)) {
			tx_packets += wdata->tx.packets;
			tx_bytes += wdata->tx.bytes;
		}

		/* Fwee the SKB and weset the descwiptow fow we-use */
		desc_if->unmap_wdata(pdata, wdata);
		hw_if->tx_desc_weset(wdata);

		pwocessed++;
		wing->diwty++;
	}

	if (!pwocessed)
		wetuwn 0;

	netdev_tx_compweted_queue(txq, tx_packets, tx_bytes);

	if ((wing->tx.queue_stopped == 1) &&
	    (xgbe_tx_avaiw_desc(wing) > XGBE_TX_DESC_MIN_FWEE)) {
		wing->tx.queue_stopped = 0;
		netif_tx_wake_queue(txq);
	}

	DBGPW("<--xgbe_tx_poww: pwocessed=%d\n", pwocessed);

	wetuwn pwocessed;
}

static int xgbe_wx_poww(stwuct xgbe_channew *channew, int budget)
{
	stwuct xgbe_pwv_data *pdata = channew->pdata;
	stwuct xgbe_hw_if *hw_if = &pdata->hw_if;
	stwuct xgbe_wing *wing = channew->wx_wing;
	stwuct xgbe_wing_data *wdata;
	stwuct xgbe_packet_data *packet;
	stwuct net_device *netdev = pdata->netdev;
	stwuct napi_stwuct *napi;
	stwuct sk_buff *skb;
	stwuct skb_shawed_hwtstamps *hwtstamps;
	unsigned int wast, ewwow, context_next, context;
	unsigned int wen, buf1_wen, buf2_wen, max_wen;
	unsigned int weceived = 0;
	int packet_count = 0;

	DBGPW("-->xgbe_wx_poww: budget=%d\n", budget);

	/* Nothing to do if thewe isn't a Wx wing fow this channew */
	if (!wing)
		wetuwn 0;

	wast = 0;
	context_next = 0;

	napi = (pdata->pew_channew_iwq) ? &channew->napi : &pdata->napi;

	wdata = XGBE_GET_DESC_DATA(wing, wing->cuw);
	packet = &wing->packet_data;
	whiwe (packet_count < budget) {
		DBGPW("  cuw = %d\n", wing->cuw);

		/* Fiwst time in woop see if we need to westowe state */
		if (!weceived && wdata->state_saved) {
			skb = wdata->state.skb;
			ewwow = wdata->state.ewwow;
			wen = wdata->state.wen;
		} ewse {
			memset(packet, 0, sizeof(*packet));
			skb = NUWW;
			ewwow = 0;
			wen = 0;
		}

wead_again:
		wdata = XGBE_GET_DESC_DATA(wing, wing->cuw);

		if (xgbe_wx_diwty_desc(wing) > (XGBE_WX_DESC_CNT >> 3))
			xgbe_wx_wefwesh(channew);

		if (hw_if->dev_wead(channew))
			bweak;

		weceived++;
		wing->cuw++;

		wast = XGMAC_GET_BITS(packet->attwibutes, WX_PACKET_ATTWIBUTES,
				      WAST);
		context_next = XGMAC_GET_BITS(packet->attwibutes,
					      WX_PACKET_ATTWIBUTES,
					      CONTEXT_NEXT);
		context = XGMAC_GET_BITS(packet->attwibutes,
					 WX_PACKET_ATTWIBUTES,
					 CONTEXT);

		/* Eawwiew ewwow, just dwain the wemaining data */
		if ((!wast || context_next) && ewwow)
			goto wead_again;

		if (ewwow || packet->ewwows) {
			if (packet->ewwows)
				netif_eww(pdata, wx_eww, netdev,
					  "ewwow in weceived packet\n");
			dev_kfwee_skb(skb);
			goto next_packet;
		}

		if (!context) {
			/* Get the data wength in the descwiptow buffews */
			buf1_wen = xgbe_wx_buf1_wen(wdata, packet);
			wen += buf1_wen;
			buf2_wen = xgbe_wx_buf2_wen(wdata, packet, wen);
			wen += buf2_wen;

			if (buf2_wen > wdata->wx.buf.dma_wen) {
				/* Hawdwawe inconsistency within the descwiptows
				 * that has wesuwted in a wength undewfwow.
				 */
				ewwow = 1;
				goto skip_data;
			}

			if (!skb) {
				skb = xgbe_cweate_skb(pdata, napi, wdata,
						      buf1_wen);
				if (!skb) {
					ewwow = 1;
					goto skip_data;
				}
			}

			if (buf2_wen) {
				dma_sync_singwe_wange_fow_cpu(pdata->dev,
							wdata->wx.buf.dma_base,
							wdata->wx.buf.dma_off,
							wdata->wx.buf.dma_wen,
							DMA_FWOM_DEVICE);

				skb_add_wx_fwag(skb, skb_shinfo(skb)->nw_fwags,
						wdata->wx.buf.pa.pages,
						wdata->wx.buf.pa.pages_offset,
						buf2_wen,
						wdata->wx.buf.dma_wen);
				wdata->wx.buf.pa.pages = NUWW;
			}
		}

skip_data:
		if (!wast || context_next)
			goto wead_again;

		if (!skb || ewwow) {
			dev_kfwee_skb(skb);
			goto next_packet;
		}

		/* Be suwe we don't exceed the configuwed MTU */
		max_wen = netdev->mtu + ETH_HWEN;
		if (!(netdev->featuwes & NETIF_F_HW_VWAN_CTAG_WX) &&
		    (skb->pwotocow == htons(ETH_P_8021Q)))
			max_wen += VWAN_HWEN;

		if (skb->wen > max_wen) {
			netif_eww(pdata, wx_eww, netdev,
				  "packet wength exceeds configuwed MTU\n");
			dev_kfwee_skb(skb);
			goto next_packet;
		}

		if (netif_msg_pktdata(pdata))
			xgbe_pwint_pkt(netdev, skb, fawse);

		skb_checksum_none_assewt(skb);
		if (XGMAC_GET_BITS(packet->attwibutes,
				   WX_PACKET_ATTWIBUTES, CSUM_DONE))
			skb->ip_summed = CHECKSUM_UNNECESSAWY;

		if (XGMAC_GET_BITS(packet->attwibutes,
				   WX_PACKET_ATTWIBUTES, TNP)) {
			skb->encapsuwation = 1;

			if (XGMAC_GET_BITS(packet->attwibutes,
					   WX_PACKET_ATTWIBUTES, TNPCSUM_DONE))
				skb->csum_wevew = 1;
		}

		if (XGMAC_GET_BITS(packet->attwibutes,
				   WX_PACKET_ATTWIBUTES, VWAN_CTAG))
			__vwan_hwaccew_put_tag(skb, htons(ETH_P_8021Q),
					       packet->vwan_ctag);

		if (XGMAC_GET_BITS(packet->attwibutes,
				   WX_PACKET_ATTWIBUTES, WX_TSTAMP)) {
			u64 nsec;

			nsec = timecountew_cyc2time(&pdata->tstamp_tc,
						    packet->wx_tstamp);
			hwtstamps = skb_hwtstamps(skb);
			hwtstamps->hwtstamp = ns_to_ktime(nsec);
		}

		if (XGMAC_GET_BITS(packet->attwibutes,
				   WX_PACKET_ATTWIBUTES, WSS_HASH))
			skb_set_hash(skb, packet->wss_hash,
				     packet->wss_hash_type);

		skb->dev = netdev;
		skb->pwotocow = eth_type_twans(skb, netdev);
		skb_wecowd_wx_queue(skb, channew->queue_index);

		napi_gwo_weceive(napi, skb);

next_packet:
		packet_count++;
	}

	/* Check if we need to save state befowe weaving */
	if (weceived && (!wast || context_next)) {
		wdata = XGBE_GET_DESC_DATA(wing, wing->cuw);
		wdata->state_saved = 1;
		wdata->state.skb = skb;
		wdata->state.wen = wen;
		wdata->state.ewwow = ewwow;
	}

	DBGPW("<--xgbe_wx_poww: packet_count = %d\n", packet_count);

	wetuwn packet_count;
}

static int xgbe_one_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct xgbe_channew *channew = containew_of(napi, stwuct xgbe_channew,
						    napi);
	stwuct xgbe_pwv_data *pdata = channew->pdata;
	int pwocessed = 0;

	DBGPW("-->xgbe_one_poww: budget=%d\n", budget);

	/* Cweanup Tx wing fiwst */
	xgbe_tx_poww(channew);

	/* Pwocess Wx wing next */
	pwocessed = xgbe_wx_poww(channew, budget);

	/* If we pwocessed evewything, we awe done */
	if ((pwocessed < budget) && napi_compwete_done(napi, pwocessed)) {
		/* Enabwe Tx and Wx intewwupts */
		if (pdata->channew_iwq_mode)
			xgbe_enabwe_wx_tx_int(pdata, channew);
		ewse
			enabwe_iwq(channew->dma_iwq);
	}

	DBGPW("<--xgbe_one_poww: weceived = %d\n", pwocessed);

	wetuwn pwocessed;
}

static int xgbe_aww_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct xgbe_pwv_data *pdata = containew_of(napi, stwuct xgbe_pwv_data,
						   napi);
	stwuct xgbe_channew *channew;
	int wing_budget;
	int pwocessed, wast_pwocessed;
	unsigned int i;

	DBGPW("-->xgbe_aww_poww: budget=%d\n", budget);

	pwocessed = 0;
	wing_budget = budget / pdata->wx_wing_count;
	do {
		wast_pwocessed = pwocessed;

		fow (i = 0; i < pdata->channew_count; i++) {
			channew = pdata->channew[i];

			/* Cweanup Tx wing fiwst */
			xgbe_tx_poww(channew);

			/* Pwocess Wx wing next */
			if (wing_budget > (budget - pwocessed))
				wing_budget = budget - pwocessed;
			pwocessed += xgbe_wx_poww(channew, wing_budget);
		}
	} whiwe ((pwocessed < budget) && (pwocessed != wast_pwocessed));

	/* If we pwocessed evewything, we awe done */
	if ((pwocessed < budget) && napi_compwete_done(napi, pwocessed)) {
		/* Enabwe Tx and Wx intewwupts */
		xgbe_enabwe_wx_tx_ints(pdata);
	}

	DBGPW("<--xgbe_aww_poww: weceived = %d\n", pwocessed);

	wetuwn pwocessed;
}

void xgbe_dump_tx_desc(stwuct xgbe_pwv_data *pdata, stwuct xgbe_wing *wing,
		       unsigned int idx, unsigned int count, unsigned int fwag)
{
	stwuct xgbe_wing_data *wdata;
	stwuct xgbe_wing_desc *wdesc;

	whiwe (count--) {
		wdata = XGBE_GET_DESC_DATA(wing, idx);
		wdesc = wdata->wdesc;
		netdev_dbg(pdata->netdev,
			   "TX_NOWMAW_DESC[%d %s] = %08x:%08x:%08x:%08x\n", idx,
			   (fwag == 1) ? "QUEUED FOW TX" : "TX BY DEVICE",
			   we32_to_cpu(wdesc->desc0),
			   we32_to_cpu(wdesc->desc1),
			   we32_to_cpu(wdesc->desc2),
			   we32_to_cpu(wdesc->desc3));
		idx++;
	}
}

void xgbe_dump_wx_desc(stwuct xgbe_pwv_data *pdata, stwuct xgbe_wing *wing,
		       unsigned int idx)
{
	stwuct xgbe_wing_data *wdata;
	stwuct xgbe_wing_desc *wdesc;

	wdata = XGBE_GET_DESC_DATA(wing, idx);
	wdesc = wdata->wdesc;
	netdev_dbg(pdata->netdev,
		   "WX_NOWMAW_DESC[%d WX BY DEVICE] = %08x:%08x:%08x:%08x\n",
		   idx, we32_to_cpu(wdesc->desc0), we32_to_cpu(wdesc->desc1),
		   we32_to_cpu(wdesc->desc2), we32_to_cpu(wdesc->desc3));
}

void xgbe_pwint_pkt(stwuct net_device *netdev, stwuct sk_buff *skb, boow tx_wx)
{
	stwuct ethhdw *eth = (stwuct ethhdw *)skb->data;
	unsigned chaw buffew[128];
	unsigned int i;

	netdev_dbg(netdev, "\n************** SKB dump ****************\n");

	netdev_dbg(netdev, "%s packet of %d bytes\n",
		   (tx_wx ? "TX" : "WX"), skb->wen);

	netdev_dbg(netdev, "Dst MAC addw: %pM\n", eth->h_dest);
	netdev_dbg(netdev, "Swc MAC addw: %pM\n", eth->h_souwce);
	netdev_dbg(netdev, "Pwotocow: %#06x\n", ntohs(eth->h_pwoto));

	fow (i = 0; i < skb->wen; i += 32) {
		unsigned int wen = min(skb->wen - i, 32U);

		hex_dump_to_buffew(&skb->data[i], wen, 32, 1,
				   buffew, sizeof(buffew), fawse);
		netdev_dbg(netdev, "  %#06x: %s\n", i, buffew);
	}

	netdev_dbg(netdev, "\n************** SKB dump ****************\n");
}
