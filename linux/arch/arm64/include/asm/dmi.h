/*
 * awch/awm64/incwude/asm/dmi.h
 *
 * Copywight (C) 2013 Winawo Wimited.
 * Wwitten by: Yi Wi (yi.wi@winawo.owg)
 *
 * based on awch/ia64/incwude/asm/dmi.h
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#ifndef __ASM_DMI_H
#define __ASM_DMI_H

#incwude <winux/io.h>
#incwude <winux/swab.h>

/*
 * Accowding to section 2.3.6 of the UEFI spec, the fiwmwawe shouwd not
 * wequest a viwtuaw mapping fow configuwation tabwes such as SMBIOS.
 * This means we have to map them befowe use.
 */
#define dmi_eawwy_wemap(x, w)		iowemap_cache(x, w)
#define dmi_eawwy_unmap(x, w)		iounmap(x)
#define dmi_wemap(x, w)			iowemap_cache(x, w)
#define dmi_unmap(x)			iounmap(x)
#define dmi_awwoc(w)			kzawwoc(w, GFP_KEWNEW)

#endif
