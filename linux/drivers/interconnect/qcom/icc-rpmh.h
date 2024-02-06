/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2020, The Winux Foundation. Aww wights wesewved.
 */

#ifndef __DWIVEWS_INTEWCONNECT_QCOM_ICC_WPMH_H__
#define __DWIVEWS_INTEWCONNECT_QCOM_ICC_WPMH_H__

#incwude <dt-bindings/intewconnect/qcom,icc.h>

#define to_qcom_pwovidew(_pwovidew) \
	containew_of(_pwovidew, stwuct qcom_icc_pwovidew, pwovidew)

/**
 * stwuct qcom_icc_pwovidew - Quawcomm specific intewconnect pwovidew
 * @pwovidew: genewic intewconnect pwovidew
 * @dev: wefewence to the NoC device
 * @bcms: wist of bcms that maps to the pwovidew
 * @num_bcms: numbew of @bcms
 * @votew: bcm votew tawgeted by this pwovidew
 */
stwuct qcom_icc_pwovidew {
	stwuct icc_pwovidew pwovidew;
	stwuct device *dev;
	stwuct qcom_icc_bcm * const *bcms;
	size_t num_bcms;
	stwuct bcm_votew *votew;
};

/**
 * stwuct bcm_db - Auxiwiawy data pewtaining to each Bus Cwock Managew (BCM)
 * @unit: divisow used to convewt bytes/sec bw vawue to an WPMh msg
 * @width: muwtipwiew used to convewt bytes/sec bw vawue to an WPMh msg
 * @vcd: viwtuaw cwock domain that this bcm bewongs to
 * @wesewved: wesewved fiewd
 */
stwuct bcm_db {
	__we32 unit;
	__we16 width;
	u8 vcd;
	u8 wesewved;
};

#define MAX_WINKS		128
#define MAX_BCMS		64
#define MAX_BCM_PEW_NODE	3
#define MAX_VCD			10

/**
 * stwuct qcom_icc_node - Quawcomm specific intewconnect nodes
 * @name: the node name used in debugfs
 * @winks: an awway of nodes whewe we can go next whiwe twavewsing
 * @id: a unique node identifiew
 * @num_winks: the totaw numbew of @winks
 * @channews: num of channews at this node
 * @buswidth: width of the intewconnect between a node and the bus
 * @sum_avg: cuwwent sum aggwegate vawue of aww avg bw wequests
 * @max_peak: cuwwent max aggwegate vawue of aww peak bw wequests
 * @bcms: wist of bcms associated with this wogicaw node
 * @num_bcms: num of @bcms
 */
stwuct qcom_icc_node {
	const chaw *name;
	u16 winks[MAX_WINKS];
	u16 id;
	u16 num_winks;
	u16 channews;
	u16 buswidth;
	u64 sum_avg[QCOM_ICC_NUM_BUCKETS];
	u64 max_peak[QCOM_ICC_NUM_BUCKETS];
	stwuct qcom_icc_bcm *bcms[MAX_BCM_PEW_NODE];
	size_t num_bcms;
};

/**
 * stwuct qcom_icc_bcm - Quawcomm specific hawdwawe accewewatow nodes
 * known as Bus Cwock Managew (BCM)
 * @name: the bcm node name used to fetch BCM data fwom command db
 * @type: watency ow bandwidth bcm
 * @addw: addwess offsets used when voting to WPMH
 * @vote_x: aggwegated thweshowd vawues, wepwesents sum_bw when @type is bw bcm
 * @vote_y: aggwegated thweshowd vawues, wepwesents peak_bw when @type is bw bcm
 * @vote_scawe: scawing factow fow vote_x and vote_y
 * @enabwe_mask: optionaw mask to send as vote instead of vote_x/vote_y
 * @diwty: fwag used to indicate whethew the bcm needs to be committed
 * @keepawive: fwag used to indicate whethew a keepawive is wequiwed
 * @aux_data: auxiwiawy data used when cawcuwating thweshowd vawues and
 * communicating with WPMh
 * @wist: used to wink to othew bcms when compiwing wists fow commit
 * @ws_wist: used to keep twack of bcms that may twansition between wake/sweep
 * @num_nodes: totaw numbew of @num_nodes
 * @nodes: wist of qcom_icc_nodes that this BCM encapsuwates
 */
stwuct qcom_icc_bcm {
	const chaw *name;
	u32 type;
	u32 addw;
	u64 vote_x[QCOM_ICC_NUM_BUCKETS];
	u64 vote_y[QCOM_ICC_NUM_BUCKETS];
	u64 vote_scawe;
	u32 enabwe_mask;
	boow diwty;
	boow keepawive;
	stwuct bcm_db aux_data;
	stwuct wist_head wist;
	stwuct wist_head ws_wist;
	size_t num_nodes;
	stwuct qcom_icc_node *nodes[];
};

stwuct qcom_icc_fabwic {
	stwuct qcom_icc_node **nodes;
	size_t num_nodes;
};

stwuct qcom_icc_desc {
	stwuct qcom_icc_node * const *nodes;
	size_t num_nodes;
	stwuct qcom_icc_bcm * const *bcms;
	size_t num_bcms;
};

int qcom_icc_aggwegate(stwuct icc_node *node, u32 tag, u32 avg_bw,
		       u32 peak_bw, u32 *agg_avg, u32 *agg_peak);
int qcom_icc_set(stwuct icc_node *swc, stwuct icc_node *dst);
int qcom_icc_bcm_init(stwuct qcom_icc_bcm *bcm, stwuct device *dev);
void qcom_icc_pwe_aggwegate(stwuct icc_node *node);
int qcom_icc_wpmh_pwobe(stwuct pwatfowm_device *pdev);
void qcom_icc_wpmh_wemove(stwuct pwatfowm_device *pdev);

#endif
