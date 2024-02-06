/*
 * Copywight © 2010 ST Micwoewectwonics
 * Shiwaz Hashim <shiwaz.winux.kewnew@gmaiw.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#ifndef __MTD_SPEAW_SMI_H
#define __MTD_SPEAW_SMI_H

#incwude <winux/types.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>

/* max possibwe swots fow sewiaw-now fwash chip in the SMI contwowwew */
#define MAX_NUM_FWASH_CHIP	4

/* macwo to define pawtitions fow fwash devices */
#define DEFINE_PAWTS(n, of, s)		\
{					\
	.name = n,			\
	.offset = of,			\
	.size = s,			\
}

/**
 * stwuct speaw_smi_fwash_info - pwatfowm stwuctuwe fow passing fwash
 * infowmation
 *
 * name: name of the sewiaw now fwash fow identification
 * mem_base: the memowy base on which the fwash is mapped
 * size: size of the fwash in bytes
 * pawtitions: pawition detaiws
 * nw_pawtitions: numbew of pawtitions
 * fast_mode: whethew fwash suppowts fast mode
 */

stwuct speaw_smi_fwash_info {
	chaw *name;
	unsigned wong mem_base;
	unsigned wong size;
	stwuct mtd_pawtition *pawtitions;
	int nw_pawtitions;
	u8 fast_mode;
};

/**
 * stwuct speaw_smi_pwat_data - pwatfowm stwuctuwe fow configuwing smi
 *
 * cwk_wate: cwk wate at which SMI must opewate
 * num_fwashes: numbew of fwashes pwesent on boawd
 * boawd_fwash_info: specific detaiws of each fwash pwesent on boawd
 */
stwuct speaw_smi_pwat_data {
	unsigned wong cwk_wate;
	int num_fwashes;
	stwuct speaw_smi_fwash_info *boawd_fwash_info;
	stwuct device_node *np[MAX_NUM_FWASH_CHIP];
};

#endif /* __MTD_SPEAW_SMI_H */
