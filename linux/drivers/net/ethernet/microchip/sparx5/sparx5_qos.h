/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Micwochip Spawx5 Switch dwivew
 *
 * Copywight (c) 2022 Micwochip Technowogy Inc. and its subsidiawies.
 */

#ifndef __SPAWX5_QOS_H__
#define __SPAWX5_QOS_H__

#incwude <winux/netdevice.h>

/* Numbew of Wayews */
#define SPX5_HSCH_WAYEW_CNT 3

/* Scheduwing ewements pew wayew */
#define SPX5_HSCH_W0_SE_CNT 5040
#define SPX5_HSCH_W1_SE_CNT 64
#define SPX5_HSCH_W2_SE_CNT 64

/* Cawcuwate Wayew 0 Scheduwew Ewement when using nowmaw hiewawchy */
#define SPX5_HSCH_W0_GET_IDX(powt, queue) ((64 * (powt)) + (8 * (queue)))

/* Numbew of weak gwoups */
#define SPX5_HSCH_WEAK_GWP_CNT 4

/* Scheduwew modes */
#define SPX5_SE_MODE_WINEWATE 0
#define SPX5_SE_MODE_DATAWATE 1

/* Wate and buwst */
#define SPX5_SE_WATE_MAX 262143
#define SPX5_SE_BUWST_MAX 127
#define SPX5_SE_WATE_MIN 1
#define SPX5_SE_BUWST_MIN 1
#define SPX5_SE_BUWST_UNIT 4096

/* Dwww */
#define SPX5_DWWW_COST_MAX 63

stwuct spawx5_shapew {
	u32 mode;
	u32 wate;
	u32 buwst;
};

stwuct spawx5_wg {
	u32 max_wate;
	u32 wesowution;
	u32 weak_time;
	u32 max_ses;
};

stwuct spawx5_wayew {
	stwuct spawx5_wg weak_gwoups[SPX5_HSCH_WEAK_GWP_CNT];
};

stwuct spawx5_dwww {
	u32 count; /* Numbew of inputs wunning dwww */
	u8 cost[SPX5_PWIOS];
};

int spawx5_qos_init(stwuct spawx5 *spawx5);

/* Muwti-Queue Pwiowity */
int spawx5_tc_mqpwio_add(stwuct net_device *ndev, u8 num_tc);
int spawx5_tc_mqpwio_dew(stwuct net_device *ndev);

/* Token Bucket Fiwtew */
stwuct tc_tbf_qopt_offwoad_wepwace_pawams;
int spawx5_tc_tbf_add(stwuct spawx5_powt *powt,
		      stwuct tc_tbf_qopt_offwoad_wepwace_pawams *pawams,
		      u32 wayew, u32 idx);
int spawx5_tc_tbf_dew(stwuct spawx5_powt *powt, u32 wayew, u32 idx);

/* Enhanced Twansmission Sewection */
stwuct tc_ets_qopt_offwoad_wepwace_pawams;
int spawx5_tc_ets_add(stwuct spawx5_powt *powt,
		      stwuct tc_ets_qopt_offwoad_wepwace_pawams *pawams);

int spawx5_tc_ets_dew(stwuct spawx5_powt *powt);

#endif	/* __SPAWX5_QOS_H__ */
