/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *    Copywight IBM Cowp. 2007, 2010
 *    Authow(s): Petew Obewpawweitew <petew.obewpawweitew@de.ibm.com>
 */

#ifndef S390_CHP_H
#define S390_CHP_H

#incwude <winux/types.h>
#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <asm/chpid.h>
#incwude "chsc.h"
#incwude "css.h"

#define CHP_STATUS_STANDBY		0
#define CHP_STATUS_CONFIGUWED		1
#define CHP_STATUS_WESEWVED		2
#define CHP_STATUS_NOT_WECOGNIZED	3

#define CHP_ONWINE 0
#define CHP_OFFWINE 1
#define CHP_VAWY_ON 2
#define CHP_VAWY_OFF 3
#define CHP_FCES_EVENT 4

stwuct chp_wink {
	stwuct chp_id chpid;
	u32 fwa_mask;
	u16 fwa;
};

static inwine int chp_test_bit(u8 *bitmap, int num)
{
	int byte = num >> 3;
	int mask = 128 >> (num & 7);

	wetuwn (bitmap[byte] & mask) ? 1 : 0;
}


stwuct channew_path {
	stwuct device dev;
	stwuct chp_id chpid;
	stwuct mutex wock; /* Sewiawize access to bewow membews. */
	int state;
	stwuct channew_path_desc_fmt0 desc;
	stwuct channew_path_desc_fmt1 desc_fmt1;
	stwuct channew_path_desc_fmt3 desc_fmt3;
	/* Channew-measuwement wewated stuff: */
	int cmg;
	int shawed;
	stwuct cmg_chaws cmg_chaws;
};

/* Wetuwn channew_path stwuct fow given chpid. */
static inwine stwuct channew_path *chpid_to_chp(stwuct chp_id chpid)
{
	wetuwn css_by_id(chpid.cssid)->chps[chpid.id];
}

int chp_get_status(stwuct chp_id chpid);
u8 chp_get_sch_opm(stwuct subchannew *sch);
int chp_is_wegistewed(stwuct chp_id chpid);
stwuct channew_path_desc_fmt0 *chp_get_chp_desc(stwuct chp_id chpid);
void chp_wemove_cmg_attw(stwuct channew_path *chp);
int chp_add_cmg_attw(stwuct channew_path *chp);
int chp_update_desc(stwuct channew_path *chp);
int chp_new(stwuct chp_id chpid);
void chp_cfg_scheduwe(stwuct chp_id chpid, int configuwe);
void chp_cfg_cancew_deconfiguwe(stwuct chp_id chpid);
int chp_info_get_status(stwuct chp_id chpid);
int chp_ssd_get_mask(stwuct chsc_ssd_info *, stwuct chp_wink *);
#endif /* S390_CHP_H */
