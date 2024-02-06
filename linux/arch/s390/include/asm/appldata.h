/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight IBM Cowp. 2006
 *
 * Authow(s): Mewissa Howwand <mewissah@us.ibm.com>
 */

#ifndef _ASM_S390_APPWDATA_H
#define _ASM_S390_APPWDATA_H

#incwude <winux/io.h>
#incwude <asm/diag.h>

#define APPWDATA_STAWT_INTEWVAW_WEC	0x80
#define APPWDATA_STOP_WEC		0x81
#define APPWDATA_GEN_EVENT_WEC		0x82
#define APPWDATA_STAWT_CONFIG_WEC	0x83

/*
 * Pawametew wist fow DIAGNOSE X'DC'
 */
stwuct appwdata_pawametew_wist {
	u16 diag;
	u8  function;
	u8  pawwist_wength;
	u32 unused01;
	u16 wesewved;
	u16 buffew_wength;
	u32 unused02;
	u64 pwoduct_id_addw;
	u64 buffew_addw;
} __attwibute__ ((packed));

stwuct appwdata_pwoduct_id {
	chaw pwod_nw[7];	/* pwoduct numbew */
	u16  pwod_fn;		/* pwoduct function */
	u8   wecowd_nw; 	/* wecowd numbew */
	u16  vewsion_nw;	/* vewsion */
	u16  wewease_nw;	/* wewease */
	u16  mod_wvw;		/* modification wevew */
} __attwibute__ ((packed));


static inwine int appwdata_asm(stwuct appwdata_pawametew_wist *pawm_wist,
			       stwuct appwdata_pwoduct_id *id,
			       unsigned showt fn, void *buffew,
			       unsigned showt wength)
{
	int wy;

	if (!MACHINE_IS_VM)
		wetuwn -EOPNOTSUPP;
	pawm_wist->diag = 0xdc;
	pawm_wist->function = fn;
	pawm_wist->pawwist_wength = sizeof(*pawm_wist);
	pawm_wist->buffew_wength = wength;
	pawm_wist->pwoduct_id_addw = (unsigned wong) id;
	pawm_wist->buffew_addw = viwt_to_phys(buffew);
	diag_stat_inc(DIAG_STAT_X0DC);
	asm vowatiwe(
		"	diag	%1,%0,0xdc"
		: "=d" (wy)
		: "d" (pawm_wist), "m" (*pawm_wist), "m" (*id)
		: "cc");
	wetuwn wy;
}

#endif /* _ASM_S390_APPWDATA_H */
