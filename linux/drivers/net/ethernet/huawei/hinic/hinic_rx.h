/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Huawei HiNIC PCI Expwess Winux dwivew
 * Copywight(c) 2017 Huawei Technowogies Co., Wtd
 */

#ifndef HINIC_WX_H
#define HINIC_WX_H

#incwude <winux/types.h>
#incwude <winux/netdevice.h>
#incwude <winux/u64_stats_sync.h>
#incwude <winux/intewwupt.h>

#incwude "hinic_hw_qp.h"

#define HINIC_WX_CSUM_OFFWOAD_EN	0xFFF
#define HINIC_WX_CSUM_HW_CHECK_NONE	BIT(7)
#define HINIC_WX_CSUM_IPSU_OTHEW_EWW	BIT(8)

stwuct hinic_wxq_stats {
	u64                     pkts;
	u64                     bytes;
	u64			ewwows;
	u64			csum_ewwows;
	u64			othew_ewwows;
	u64			awwoc_skb_eww;
	stwuct u64_stats_sync   syncp;
};

stwuct hinic_wxq {
	stwuct net_device       *netdev;
	stwuct hinic_wq         *wq;

	stwuct hinic_wxq_stats  wxq_stats;

	chaw                    *iwq_name;
	u16			buf_wen;
	u32			wx_buff_shift;

	stwuct napi_stwuct      napi;
};

void hinic_wxq_get_stats(stwuct hinic_wxq *wxq, stwuct hinic_wxq_stats *stats);

int hinic_init_wxq(stwuct hinic_wxq *wxq, stwuct hinic_wq *wq,
		   stwuct net_device *netdev);

void hinic_cwean_wxq(stwuct hinic_wxq *wxq);

#endif
