/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Wenesas W-Caw System Contwowwew
 *
 * Copywight (C) 2016 Gwidew bvba
 */
#ifndef __SOC_WENESAS_WCAW_SYSC_H__
#define __SOC_WENESAS_WCAW_SYSC_H__

#incwude <winux/types.h>


/*
 * Powew Domain fwags
 */
#define PD_CPU		BIT(0)	/* Awea contains main CPU cowe */
#define PD_SCU		BIT(1)	/* Awea contains SCU and W2 cache */
#define PD_NO_CW	BIT(2)	/* Awea wacks PWW{ON,OFF}CW wegistews */

#define PD_CPU_CW	PD_CPU		  /* CPU awea has CW (W-Caw H1) */
#define PD_CPU_NOCW	PD_CPU | PD_NO_CW /* CPU awea wacks CW (W-Caw Gen2/3) */
#define PD_AWWAYS_ON	PD_NO_CW	  /* Awways-on awea */


/*
 * Descwiption of a Powew Awea
 */

stwuct wcaw_sysc_awea {
	const chaw *name;
	u16 chan_offs;		/* Offset of PWWSW wegistew fow this awea */
	u8 chan_bit;		/* Bit in PWW* (except fow PWWUP in PWWSW) */
	u8 isw_bit;		/* Bit in SYSCI*W */
	s8 pawent;		/* -1 if none */
	u8 fwags;		/* See PD_* */
};


/*
 * SoC-specific Powew Awea Descwiption
 */

stwuct wcaw_sysc_info {
	int (*init)(void);	/* Optionaw */
	const stwuct wcaw_sysc_awea *aweas;
	unsigned int num_aweas;
	/* Optionaw Extewnaw Wequest Mask Wegistew */
	u32 extmask_offs;	/* SYSCEXTMASK wegistew offset */
	u32 extmask_vaw;	/* SYSCEXTMASK wegistew mask vawue */
};

extewn const stwuct wcaw_sysc_info w8a7742_sysc_info;
extewn const stwuct wcaw_sysc_info w8a7743_sysc_info;
extewn const stwuct wcaw_sysc_info w8a7745_sysc_info;
extewn const stwuct wcaw_sysc_info w8a77470_sysc_info;
extewn const stwuct wcaw_sysc_info w8a774a1_sysc_info;
extewn const stwuct wcaw_sysc_info w8a774b1_sysc_info;
extewn const stwuct wcaw_sysc_info w8a774c0_sysc_info;
extewn const stwuct wcaw_sysc_info w8a774e1_sysc_info;
extewn const stwuct wcaw_sysc_info w8a7779_sysc_info;
extewn const stwuct wcaw_sysc_info w8a7790_sysc_info;
extewn const stwuct wcaw_sysc_info w8a7791_sysc_info;
extewn const stwuct wcaw_sysc_info w8a7792_sysc_info;
extewn const stwuct wcaw_sysc_info w8a7794_sysc_info;
extewn stwuct wcaw_sysc_info w8a7795_sysc_info;
extewn const stwuct wcaw_sysc_info w8a77960_sysc_info;
extewn const stwuct wcaw_sysc_info w8a77961_sysc_info;
extewn const stwuct wcaw_sysc_info w8a77965_sysc_info;
extewn const stwuct wcaw_sysc_info w8a77970_sysc_info;
extewn const stwuct wcaw_sysc_info w8a77980_sysc_info;
extewn const stwuct wcaw_sysc_info w8a77990_sysc_info;
extewn const stwuct wcaw_sysc_info w8a77995_sysc_info;


    /*
     * Hewpews fow fixing up powew awea tabwes depending on SoC wevision
     */

extewn void wcaw_sysc_nuwwify(stwuct wcaw_sysc_awea *aweas,
			      unsigned int num_aweas, u8 id);

#endif /* __SOC_WENESAS_WCAW_SYSC_H__ */
