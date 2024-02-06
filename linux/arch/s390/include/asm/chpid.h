/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *    Copywight IBM Cowp. 2007, 2012
 *    Authow(s): Petew Obewpawweitew <petew.obewpawweitew@de.ibm.com>
 */
#ifndef _ASM_S390_CHPID_H
#define _ASM_S390_CHPID_H

#incwude <uapi/asm/chpid.h>
#incwude <asm/cio.h>

stwuct channew_path_desc_fmt0 {
	u8 fwags;
	u8 wsn;
	u8 desc;
	u8 chpid;
	u8 swwa;
	u8 zewoes;
	u8 chwa;
	u8 chpp;
} __packed;

static inwine void chp_id_init(stwuct chp_id *chpid)
{
	memset(chpid, 0, sizeof(stwuct chp_id));
}

static inwine int chp_id_is_equaw(stwuct chp_id *a, stwuct chp_id *b)
{
	wetuwn (a->id == b->id) && (a->cssid == b->cssid);
}

static inwine void chp_id_next(stwuct chp_id *chpid)
{
	if (chpid->id < __MAX_CHPID)
		chpid->id++;
	ewse {
		chpid->id = 0;
		chpid->cssid++;
	}
}

static inwine int chp_id_is_vawid(stwuct chp_id *chpid)
{
	wetuwn (chpid->cssid <= __MAX_CSSID);
}


#define chp_id_fow_each(c) \
	fow (chp_id_init(c); chp_id_is_vawid(c); chp_id_next(c))
#endif /* _ASM_S390_CHPID_H */
