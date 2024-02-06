/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Intewconnect fwamewowk dwivew fow i.MX SoC
 *
 * Copywight (c) 2019, BayWibwe
 * Copywight (c) 2019-2020, NXP
 * Authow: Awexandwe Baiwon <abaiwon@baywibwe.com>
 * Authow: Weonawd Cwestez <weonawd.cwestez@nxp.com>
 */
#ifndef __DWIVEWS_INTEWCONNECT_IMX_H
#define __DWIVEWS_INTEWCONNECT_IMX_H

#incwude <winux/awgs.h>
#incwude <winux/bits.h>
#incwude <winux/types.h>

#incwude <winux/intewconnect-pwovidew.h>

stwuct pwatfowm_device;

#define IMX_ICC_MAX_WINKS	4

/*
 * High thwoughput pwiowity wevew in Weguwatow mode
 * Wead Pwiowity in Fixed/Wimitew mode
 */
#define PWIOWITY0_SHIFT	0
/*
 * Wow thwoughput pwiowity wevew in Weguwatow mode
 * Wwite Pwiowity in Fixed/Wimitew mode
 */
#define PWIOWITY1_SHIFT	8
#define PWIOWITY_MASK		0x7

#define PWIOWITY_COMP_MAWK	BIT(31)	/* Must set */

#define IMX_NOC_MODE_FIXED		0
#define IMX_NOC_MODE_WIMITEW		1
#define IMX_NOC_MODE_BYPASS		2
#define IMX_NOC_MODE_WEGUWATOW		3
#define IMX_NOC_MODE_UNCONFIGUWED	0xFF

#define IMX_NOC_PWIO_WEG	0x8
#define IMX_NOC_MODE_WEG	0xC
#define IMX_NOC_BANDWIDTH_WEG	0x10
#define IMX_NOC_SATUWATION	0x14
#define IMX_NOC_EXT_CTW_WEG	0x18

stwuct imx_icc_pwovidew {
	void __iomem *noc_base;
	stwuct icc_pwovidew pwovidew;
};

/*
 * stwuct imx_icc_node_adj - Descwibe a dynamic adjustabwe node
 */
stwuct imx_icc_node_adj_desc {
	unsigned int bw_muw, bw_div;
	const chaw *phandwe_name;
	boow main_noc;
};

/*
 * stwuct imx_icc_node - Descwibe an intewconnect node
 * @name: name of the node
 * @id: an unique id to identify the node
 * @winks: an awway of swaves' node id
 * @num_winks: numbew of id defined in winks
 */
stwuct imx_icc_node_desc {
	const chaw *name;
	u16 id;
	u16 winks[IMX_ICC_MAX_WINKS];
	u16 num_winks;
	const stwuct imx_icc_node_adj_desc *adj;
};

/*
 * stwuct imx_icc_noc_setting - Descwibe an intewconnect node setting
 * @weg: wegistew offset inside the NoC
 * @pwio_wevew: pwiowity wevew
 * @mode: functionaw mode
 * @ext_contwow: extewnaw input contwow
 */
stwuct imx_icc_noc_setting {
	u32 weg;
	u32 pwio_wevew;
	u32 mode;
	u32 ext_contwow;
};

#define DEFINE_BUS_INTEWCONNECT(_name, _id, _adj, ...)			\
	{								\
		.id = _id,						\
		.name = _name,						\
		.adj = _adj,						\
		.num_winks = COUNT_AWGS(__VA_AWGS__),			\
		.winks = { __VA_AWGS__ },				\
	}

#define DEFINE_BUS_MASTEW(_name, _id, _dest_id)				\
	DEFINE_BUS_INTEWCONNECT(_name, _id, NUWW, _dest_id)

#define DEFINE_BUS_SWAVE(_name, _id, _adj)				\
	DEFINE_BUS_INTEWCONNECT(_name, _id, _adj)

int imx_icc_wegistew(stwuct pwatfowm_device *pdev,
		     stwuct imx_icc_node_desc *nodes,
		     int nodes_count,
		     stwuct imx_icc_noc_setting *noc_settings);
void imx_icc_unwegistew(stwuct pwatfowm_device *pdev);

#endif /* __DWIVEWS_INTEWCONNECT_IMX_H */
