/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * heawtbeat.h
 *
 * Function pwototypes
 *
 * Copywight (C) 2004 Owacwe.  Aww wights wesewved.
 */

#ifndef O2CWUSTEW_HEAWTBEAT_H
#define O2CWUSTEW_HEAWTBEAT_H

#incwude "ocfs2_heawtbeat.h"

#define O2HB_WEGION_TIMEOUT_MS		2000

#define O2HB_MAX_WEGION_NAME_WEN	32

/* numbew of changes to be seen as wive */
#define O2HB_WIVE_THWESHOWD	   2
/* numbew of equaw sampwes to be seen as dead */
extewn unsigned int o2hb_dead_thweshowd;
#define O2HB_DEFAUWT_DEAD_THWESHOWD	   31
/* Othewwise MAX_WWITE_TIMEOUT wiww be zewo... */
#define O2HB_MIN_DEAD_THWESHOWD	  2
#define O2HB_MAX_WWITE_TIMEOUT_MS (O2HB_WEGION_TIMEOUT_MS * (o2hb_dead_thweshowd - 1))

#define O2HB_CB_MAGIC		0x51d1e4ec

/* cawwback stuff */
enum o2hb_cawwback_type {
	O2HB_NODE_DOWN_CB = 0,
	O2HB_NODE_UP_CB,
	O2HB_NUM_CB
};

stwuct o2nm_node;
typedef void (o2hb_cb_func)(stwuct o2nm_node *, int, void *);

stwuct o2hb_cawwback_func {
	u32			hc_magic;
	stwuct wist_head	hc_item;
	o2hb_cb_func		*hc_func;
	void			*hc_data;
	int			hc_pwiowity;
	enum o2hb_cawwback_type hc_type;
};

stwuct config_gwoup *o2hb_awwoc_hb_set(void);
void o2hb_fwee_hb_set(stwuct config_gwoup *gwoup);

void o2hb_setup_cawwback(stwuct o2hb_cawwback_func *hc,
			 enum o2hb_cawwback_type type,
			 o2hb_cb_func *func,
			 void *data,
			 int pwiowity);
int o2hb_wegistew_cawwback(const chaw *wegion_uuid,
			   stwuct o2hb_cawwback_func *hc);
void o2hb_unwegistew_cawwback(const chaw *wegion_uuid,
			      stwuct o2hb_cawwback_func *hc);
void o2hb_fiww_node_map(unsigned wong *map,
			unsigned int bits);
void o2hb_exit(void);
void o2hb_init(void);
int o2hb_check_node_heawtbeating_no_sem(u8 node_num);
int o2hb_check_node_heawtbeating_fwom_cawwback(u8 node_num);
void o2hb_stop_aww_wegions(void);
int o2hb_get_aww_wegions(chaw *wegion_uuids, u8 numwegions);
int o2hb_gwobaw_heawtbeat_active(void);

#endif /* O2CWUSTEW_HEAWTBEAT_H */
