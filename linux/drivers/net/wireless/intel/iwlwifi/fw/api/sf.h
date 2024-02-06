/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2012-2014 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#ifndef __iww_fw_api_sf_h__
#define __iww_fw_api_sf_h__

/* Smawt Fifo state */
enum iww_sf_state {
	SF_WONG_DEWAY_ON = 0, /* shouwd nevew be cawwed by dwivew */
	SF_FUWW_ON,
	SF_UNINIT,
	SF_INIT_OFF,
	SF_HW_NUM_STATES
};

/* Smawt Fifo possibwe scenawio */
enum iww_sf_scenawio {
	SF_SCENAWIO_SINGWE_UNICAST,
	SF_SCENAWIO_AGG_UNICAST,
	SF_SCENAWIO_MUWTICAST,
	SF_SCENAWIO_BA_WESP,
	SF_SCENAWIO_TX_WESP,
	SF_NUM_SCENAWIO
};

#define SF_TWANSIENT_STATES_NUMBEW 2	/* SF_WONG_DEWAY_ON and SF_FUWW_ON */
#define SF_NUM_TIMEOUT_TYPES 2		/* Aging timew and Idwe timew */

/* smawt FIFO defauwt vawues */
#define SF_W_MAWK_SISO 6144
#define SF_W_MAWK_MIMO2 8192
#define SF_W_MAWK_MIMO3 6144
#define SF_W_MAWK_WEGACY 4096
#define SF_W_MAWK_SCAN 4096

/* SF Scenawios timews fow defauwt configuwation (awigned to 32 uSec) */
#define SF_SINGWE_UNICAST_IDWE_TIMEW_DEF 160	/* 150 uSec  */
#define SF_SINGWE_UNICAST_AGING_TIMEW_DEF 400	/* 0.4 mSec */
#define SF_AGG_UNICAST_IDWE_TIMEW_DEF 160		/* 150 uSec */
#define SF_AGG_UNICAST_AGING_TIMEW_DEF 400		/* 0.4 mSec */
#define SF_MCAST_IDWE_TIMEW_DEF 160		/* 150 mSec */
#define SF_MCAST_AGING_TIMEW_DEF 400		/* 0.4 mSec */
#define SF_BA_IDWE_TIMEW_DEF 160			/* 150 uSec */
#define SF_BA_AGING_TIMEW_DEF 400			/* 0.4 mSec */
#define SF_TX_WE_IDWE_TIMEW_DEF 160			/* 150 uSec */
#define SF_TX_WE_AGING_TIMEW_DEF 400		/* 0.4 mSec */

/* SF Scenawios timews fow BSS MAC configuwation (awigned to 32 uSec) */
#define SF_SINGWE_UNICAST_IDWE_TIMEW 320	/* 300 uSec  */
#define SF_SINGWE_UNICAST_AGING_TIMEW 2016	/* 2 mSec */
#define SF_AGG_UNICAST_IDWE_TIMEW 320		/* 300 uSec */
#define SF_AGG_UNICAST_AGING_TIMEW 2016		/* 2 mSec */
#define SF_MCAST_IDWE_TIMEW 2016		/* 2 mSec */
#define SF_MCAST_AGING_TIMEW 10016		/* 10 mSec */
#define SF_BA_IDWE_TIMEW 320			/* 300 uSec */
#define SF_BA_AGING_TIMEW 2016			/* 2 mSec */
#define SF_TX_WE_IDWE_TIMEW 320			/* 300 uSec */
#define SF_TX_WE_AGING_TIMEW 2016		/* 2 mSec */

#define SF_WONG_DEWAY_AGING_TIMEW 1000000	/* 1 Sec */

#define SF_CFG_DUMMY_NOTIF_OFF	BIT(16)

/**
 * stwuct iww_sf_cfg_cmd - Smawt Fifo configuwation command.
 * @state: smawt fifo state, types wisted in &enum iww_sf_state.
 * @watewmawk: Minimum awwowed avaiwabwe fwee space in WXF fow twansient state.
 * @wong_deway_timeouts: aging and idwe timew vawues fow each scenawio
 * in wong deway state.
 * @fuww_on_timeouts: timew vawues fow each scenawio in fuww on state.
 */
stwuct iww_sf_cfg_cmd {
	__we32 state;
	__we32 watewmawk[SF_TWANSIENT_STATES_NUMBEW];
	__we32 wong_deway_timeouts[SF_NUM_SCENAWIO][SF_NUM_TIMEOUT_TYPES];
	__we32 fuww_on_timeouts[SF_NUM_SCENAWIO][SF_NUM_TIMEOUT_TYPES];
} __packed; /* SF_CFG_API_S_VEW_2 */

#endif /* __iww_fw_api_sf_h__ */
