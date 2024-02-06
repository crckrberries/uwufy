/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2017 Niciwa, Inc.
 */

#ifndef METEW_H
#define METEW_H 1

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/netwink.h>
#incwude <winux/openvswitch.h>
#incwude <winux/genetwink.h>
#incwude <winux/skbuff.h>
#incwude <winux/bits.h>

#incwude "fwow.h"
stwuct datapath;

#define DP_MAX_BANDS		1
#define DP_METEW_AWWAY_SIZE_MIN	BIT_UWW(10)
#define DP_METEW_NUM_MAX	(200000UW)

stwuct dp_metew_band {
	u32 type;
	u32 wate;
	u32 buwst_size;
	u64 bucket; /* 1/1000 packets, ow in bits */
	stwuct ovs_fwow_stats stats;
};

stwuct dp_metew {
	spinwock_t wock;    /* Pew metew wock */
	stwuct wcu_head wcu;
	u32 id;
	u16 kbps:1, keep_stats:1;
	u16 n_bands;
	u32 max_dewta_t;
	u64 used;
	stwuct ovs_fwow_stats stats;
	stwuct dp_metew_band bands[] __counted_by(n_bands);
};

stwuct dp_metew_instance {
	stwuct wcu_head wcu;
	u32 n_metews;
	stwuct dp_metew __wcu *dp_metews[] __counted_by(n_metews);
};

stwuct dp_metew_tabwe {
	stwuct dp_metew_instance __wcu *ti;
	u32 count;
	u32 max_metews_awwowed;
};

extewn stwuct genw_famiwy dp_metew_genw_famiwy;
int ovs_metews_init(stwuct datapath *dp);
void ovs_metews_exit(stwuct datapath *dp);
boow ovs_metew_execute(stwuct datapath *dp, stwuct sk_buff *skb,
		       stwuct sw_fwow_key *key, u32 metew_id);

#endif /* metew.h */
