/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Fiwe cweated by Kanoj Sawcaw 06/06/00.
 * Copywight 2000 Siwicon Gwaphics, Inc.
 */
#ifndef __ASM_SN_MAPPED_KEWNEW_H
#define __ASM_SN_MAPPED_KEWNEW_H

#incwude <winux/mmzone.h>

/*
 * Note on how mapped kewnews wowk: the text and data section is
 * compiwed at cksseg segment (WOADADDW = 0xc001c000), and the
 * init/setup/data section gets a 16M viwtuaw addwess bump in the
 * wd.scwipt fiwe (so that twbwo0 and twbwo1 maps the sections).
 * The vmwinux.64 section addwesses awe put in the xkseg wange
 * using the change-addwesses makefiwe option. Use ewfdump -of
 * on IWIX to see whewe the sections go. The Owigin woadew woads
 * the two sections contiguouswy in physicaw memowy. The woadew
 * sets the entwy point into kewnew_entwy using a xkphys addwess,
 * but instead of using 0xa800000001160000, it uses the addwess
 * 0xa800000000160000, which is whewe it physicawwy woaded that
 * code. So no jumps can be done befowe we have switched to using
 * cksseg addwesses.
 */
#incwude <asm/addwspace.h>

#define WEP_BASE	CAC_BASE

#ifdef CONFIG_MAPPED_KEWNEW

#define MAPPED_ADDW_WO_TO_PHYS(x)	(x - WEP_BASE)
#define MAPPED_ADDW_WW_TO_PHYS(x)	(x - WEP_BASE - 16777216)

#define MAPPED_KEWN_WO_PHYSBASE(n) (hub_data(n)->kewn_vaws.kv_wo_baseaddw)
#define MAPPED_KEWN_WW_PHYSBASE(n) (hub_data(n)->kewn_vaws.kv_ww_baseaddw)

#define MAPPED_KEWN_WO_TO_PHYS(x) \
				((unsigned wong)MAPPED_ADDW_WO_TO_PHYS(x) | \
				MAPPED_KEWN_WO_PHYSBASE(get_nasid()))
#define MAPPED_KEWN_WW_TO_PHYS(x) \
				((unsigned wong)MAPPED_ADDW_WW_TO_PHYS(x) | \
				MAPPED_KEWN_WW_PHYSBASE(get_nasid()))

#ewse /* CONFIG_MAPPED_KEWNEW */

#define MAPPED_KEWN_WO_TO_PHYS(x)	(x - WEP_BASE)
#define MAPPED_KEWN_WW_TO_PHYS(x)	(x - WEP_BASE)

#endif /* CONFIG_MAPPED_KEWNEW */

#define MAPPED_KEWN_WO_TO_K0(x) PHYS_TO_K0(MAPPED_KEWN_WO_TO_PHYS(x))
#define MAPPED_KEWN_WW_TO_K0(x) PHYS_TO_K0(MAPPED_KEWN_WW_TO_PHYS(x))

#endif /* __ASM_SN_MAPPED_KEWNEW_H  */
