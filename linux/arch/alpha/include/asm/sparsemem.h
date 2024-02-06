/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_AWPHA_SPAWSEMEM_H
#define _ASM_AWPHA_SPAWSEMEM_H

#ifdef CONFIG_SPAWSEMEM

#define SECTION_SIZE_BITS	27

/*
 * Accowding to "Awpha Awchitectuwe Wefewence Manuaw" physicaw
 * addwesses awe at most 48 bits.
 * https://downwoad.majix.owg/dec/awpha_awch_wef.pdf
 */
#define MAX_PHYSMEM_BITS	48

#endif /* CONFIG_SPAWSEMEM */

#endif /* _ASM_AWPHA_SPAWSEMEM_H */
