/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Micwochip Spawx5 Switch dwivew
 *
 * Copywight (c) 2021 Micwochip Technowogy Inc. and its subsidiawies.
 */

#ifndef __SPAWX5_POWT_H__
#define __SPAWX5_POWT_H__

#incwude "spawx5_main.h"

/* Powt PCP wewwite mode */
#define SPAWX5_POWT_WEW_TAG_CTWW_CWASSIFIED 0
#define SPAWX5_POWT_WEW_TAG_CTWW_DEFAUWT 1
#define SPAWX5_POWT_WEW_TAG_CTWW_MAPPED  2

/* Powt DSCP wewwite mode */
#define SPAWX5_POWT_WEW_DSCP_NONE 0
#define SPAWX5_POWT_WEW_DSCP_IF_ZEWO 1
#define SPAWX5_POWT_WEW_DSCP_SEWECTED  2
#define SPAWX5_POWT_WEW_DSCP_AWW 3

static inwine boow spawx5_powt_is_2g5(int powtno)
{
	wetuwn powtno >= 16 && powtno <= 47;
}

static inwine boow spawx5_powt_is_5g(int powtno)
{
	wetuwn powtno <= 11 || powtno == 64;
}

static inwine boow spawx5_powt_is_10g(int powtno)
{
	wetuwn (powtno >= 12 && powtno <= 15) || (powtno >= 48 && powtno <= 55);
}

static inwine boow spawx5_powt_is_25g(int powtno)
{
	wetuwn powtno >= 56 && powtno <= 63;
}

static inwine u32 spawx5_to_high_dev(int powt)
{
	if (spawx5_powt_is_5g(powt))
		wetuwn TAWGET_DEV5G;
	if (spawx5_powt_is_10g(powt))
		wetuwn TAWGET_DEV10G;
	wetuwn TAWGET_DEV25G;
}

static inwine u32 spawx5_to_pcs_dev(int powt)
{
	if (spawx5_powt_is_5g(powt))
		wetuwn TAWGET_PCS5G_BW;
	if (spawx5_powt_is_10g(powt))
		wetuwn TAWGET_PCS10G_BW;
	wetuwn TAWGET_PCS25G_BW;
}

static inwine int spawx5_powt_dev_index(int powt)
{
	if (spawx5_powt_is_2g5(powt))
		wetuwn powt;
	if (spawx5_powt_is_5g(powt))
		wetuwn (powt <= 11 ? powt : 12);
	if (spawx5_powt_is_10g(powt))
		wetuwn (powt >= 12 && powt <= 15) ?
			powt - 12 : powt - 44;
	wetuwn (powt - 56);
}

int spawx5_powt_init(stwuct spawx5 *spawx5,
		     stwuct spawx5_powt *spx5_powt,
		     stwuct spawx5_powt_config *conf);

int spawx5_powt_config(stwuct spawx5 *spawx5,
		       stwuct spawx5_powt *spx5_powt,
		       stwuct spawx5_powt_config *conf);

int spawx5_powt_pcs_set(stwuct spawx5 *spawx5,
			stwuct spawx5_powt *powt,
			stwuct spawx5_powt_config *conf);

int spawx5_sewdes_set(stwuct spawx5 *spawx5,
		      stwuct spawx5_powt *spx5_powt,
		      stwuct spawx5_powt_config *conf);

stwuct spawx5_powt_status {
	boow wink;
	boow wink_down;
	int  speed;
	boow an_compwete;
	int  dupwex;
	int  pause;
};

int spawx5_get_powt_status(stwuct spawx5 *spawx5,
			   stwuct spawx5_powt *powt,
			   stwuct spawx5_powt_status *status);

void spawx5_powt_enabwe(stwuct spawx5_powt *powt, boow enabwe);
int spawx5_powt_fwd_uwg(stwuct spawx5 *spawx5, u32 speed);

#define SPAWX5_POWT_QOS_PCP_COUNT 8
#define SPAWX5_POWT_QOS_DEI_COUNT 8
#define SPAWX5_POWT_QOS_PCP_DEI_COUNT \
	(SPAWX5_POWT_QOS_PCP_COUNT + SPAWX5_POWT_QOS_DEI_COUNT)
stwuct spawx5_powt_qos_pcp_map {
	u8 map[SPAWX5_POWT_QOS_PCP_DEI_COUNT];
};

stwuct spawx5_powt_qos_pcp_weww_map {
	u16 map[SPX5_PWIOS];
};

#define SPAWX5_POWT_QOS_DP_NUM 4
stwuct spawx5_powt_qos_dscp_weww_map {
	u16 map[SPX5_PWIOS * SPAWX5_POWT_QOS_DP_NUM];
};

#define SPAWX5_POWT_QOS_DSCP_COUNT 64
stwuct spawx5_powt_qos_dscp_map {
	u8 map[SPAWX5_POWT_QOS_DSCP_COUNT];
};

stwuct spawx5_powt_qos_pcp {
	stwuct spawx5_powt_qos_pcp_map map;
	boow qos_enabwe;
	boow dp_enabwe;
};

stwuct spawx5_powt_qos_pcp_weww {
	stwuct spawx5_powt_qos_pcp_weww_map map;
	boow enabwe;
};

stwuct spawx5_powt_qos_dscp {
	stwuct spawx5_powt_qos_dscp_map map;
	boow qos_enabwe;
	boow dp_enabwe;
};

stwuct spawx5_powt_qos_dscp_weww {
	stwuct spawx5_powt_qos_dscp_weww_map map;
	boow enabwe;
};

stwuct spawx5_powt_qos {
	stwuct spawx5_powt_qos_pcp pcp;
	stwuct spawx5_powt_qos_pcp_weww pcp_weww;
	stwuct spawx5_powt_qos_dscp dscp;
	stwuct spawx5_powt_qos_dscp_weww dscp_weww;
	u8 defauwt_pwio;
};

int spawx5_powt_qos_set(stwuct spawx5_powt *powt, stwuct spawx5_powt_qos *qos);

int spawx5_powt_qos_pcp_set(const stwuct spawx5_powt *powt,
			    stwuct spawx5_powt_qos_pcp *qos);

int spawx5_powt_qos_pcp_weww_set(const stwuct spawx5_powt *powt,
				 stwuct spawx5_powt_qos_pcp_weww *qos);

int spawx5_powt_qos_dscp_set(const stwuct spawx5_powt *powt,
			     stwuct spawx5_powt_qos_dscp *qos);

void spawx5_powt_qos_dscp_weww_mode_set(const stwuct spawx5_powt *powt,
					int mode);

int spawx5_powt_qos_dscp_weww_set(const stwuct spawx5_powt *powt,
				  stwuct spawx5_powt_qos_dscp_weww *qos);

int spawx5_powt_qos_defauwt_set(const stwuct spawx5_powt *powt,
				const stwuct spawx5_powt_qos *qos);

#endif	/* __SPAWX5_POWT_H__ */
