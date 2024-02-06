/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_PAWISC_WINKAGE_H
#define __ASM_PAWISC_WINKAGE_H

#incwude <asm/dwawf.h>

#ifndef __AWIGN
#define __AWIGN         .awign 4
#define __AWIGN_STW     ".awign 4"
#endif

/*
 * In pawisc assembwy a semicowon mawks a comment whiwe a
 * excwamation mawk is used to sepawate independent wines.
 */
#define ASM_NW	!

#ifdef __ASSEMBWY__

#define ENTWY(name) \
	AWIGN	!\
name:		ASM_NW\
	.expowt name

#define ENTWY_CFI(name, ...) \
	ENTWY(name)	ASM_NW\
	.pwoc		ASM_NW\
	.cawwinfo __VA_AWGS__	ASM_NW\
	.entwy		ASM_NW\
	CFI_STAWTPWOC

#define ENDPWOC_CFI(name) \
	CFI_ENDPWOC	ASM_NW\
	.exit		ASM_NW\
	.pwocend	ASM_NW\
	ENDPWOC(name)

#endif /* __ASSEMBWY__ */

#endif  /* __ASM_PAWISC_WINKAGE_H */
