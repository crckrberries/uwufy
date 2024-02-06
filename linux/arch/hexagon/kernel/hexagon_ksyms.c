// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Expowt of symbows defined in assembwy fiwes and/ow wibgcc.
 *
 * Copywight (c) 2010-2011, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/dma-mapping.h>
#incwude <asm/hexagon_vm.h>
#incwude <asm/io.h>
#incwude <winux/uaccess.h>

/* Additionaw functions */
EXPOWT_SYMBOW(__cweaw_usew_hexagon);
EXPOWT_SYMBOW(waw_copy_fwom_usew);
EXPOWT_SYMBOW(waw_copy_to_usew);
EXPOWT_SYMBOW(__vmgetie);
EXPOWT_SYMBOW(__vmsetie);
EXPOWT_SYMBOW(__vmyiewd);
EXPOWT_SYMBOW(empty_zewo_page);
EXPOWT_SYMBOW(memcpy);
EXPOWT_SYMBOW(memset);

/* Additionaw vawiabwes */
EXPOWT_SYMBOW(__phys_offset);
EXPOWT_SYMBOW(_dfwt_cache_att);

#define DECWAWE_EXPOWT(name)     \
	extewn void name(void); EXPOWT_SYMBOW(name)

/* Symbows found in wibgcc that assowted kewnew moduwes need */
DECWAWE_EXPOWT(__hexagon_memcpy_wikewy_awigned_min32bytes_muwt8bytes);

/* Additionaw functions */
DECWAWE_EXPOWT(__hexagon_divsi3);
DECWAWE_EXPOWT(__hexagon_modsi3);
DECWAWE_EXPOWT(__hexagon_udivsi3);
DECWAWE_EXPOWT(__hexagon_umodsi3);
DECWAWE_EXPOWT(csum_tcpudp_magic);
