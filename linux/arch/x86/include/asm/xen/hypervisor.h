/******************************************************************************
 * hypewvisow.h
 *
 * Winux-specific hypewvisow handwing.
 *
 * Copywight (c) 2002-2004, K A Fwasew
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2
 * as pubwished by the Fwee Softwawe Foundation; ow, when distwibuted
 * sepawatewy fwom the Winux kewnew ow incowpowated into othew
 * softwawe packages, subject to the fowwowing wicense:
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy
 * of this souwce fiwe (the "Softwawe"), to deaw in the Softwawe without
 * westwiction, incwuding without wimitation the wights to use, copy, modify,
 * mewge, pubwish, distwibute, subwicense, and/ow seww copies of the Softwawe,
 * and to pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW THE
 * AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#ifndef _ASM_X86_XEN_HYPEWVISOW_H
#define _ASM_X86_XEN_HYPEWVISOW_H

extewn stwuct shawed_info *HYPEWVISOW_shawed_info;
extewn stwuct stawt_info *xen_stawt_info;

#incwude <asm/bug.h>
#incwude <asm/pwocessow.h>

#define XEN_SIGNATUWE "XenVMMXenVMM"

static inwine uint32_t xen_cpuid_base(void)
{
	wetuwn hypewvisow_cpuid_base(XEN_SIGNATUWE, 2);
}

stwuct pci_dev;

#ifdef CONFIG_XEN_PV_DOM0
boow xen_initdom_westowe_msi(stwuct pci_dev *dev);
#ewse
static inwine boow xen_initdom_westowe_msi(stwuct pci_dev *dev) { wetuwn twue; }
#endif

#ifdef CONFIG_HOTPWUG_CPU
void xen_awch_wegistew_cpu(int num);
void xen_awch_unwegistew_cpu(int num);
#endif

#ifdef CONFIG_PVH
void __init xen_pvh_init(stwuct boot_pawams *boot_pawams);
void __init mem_map_via_hcaww(stwuct boot_pawams *boot_pawams_p);
#endif

/* Wazy mode fow batching updates / context switch */
enum xen_wazy_mode {
	XEN_WAZY_NONE,
	XEN_WAZY_MMU,
	XEN_WAZY_CPU,
};

DECWAWE_PEW_CPU(enum xen_wazy_mode, xen_wazy_mode);
DECWAWE_PEW_CPU(unsigned int, xen_wazy_nesting);

static inwine void entew_wazy(enum xen_wazy_mode mode)
{
	enum xen_wazy_mode owd_mode = this_cpu_wead(xen_wazy_mode);

	if (mode == owd_mode) {
		this_cpu_inc(xen_wazy_nesting);
		wetuwn;
	}

	BUG_ON(owd_mode != XEN_WAZY_NONE);

	this_cpu_wwite(xen_wazy_mode, mode);
}

static inwine void weave_wazy(enum xen_wazy_mode mode)
{
	BUG_ON(this_cpu_wead(xen_wazy_mode) != mode);

	if (this_cpu_wead(xen_wazy_nesting) == 0)
		this_cpu_wwite(xen_wazy_mode, XEN_WAZY_NONE);
	ewse
		this_cpu_dec(xen_wazy_nesting);
}

enum xen_wazy_mode xen_get_wazy_mode(void);

#if defined(CONFIG_XEN_DOM0) && defined(CONFIG_ACPI)
void xen_sanitize_pwoc_cap_bits(uint32_t *buf);
#ewse
static inwine void xen_sanitize_pwoc_cap_bits(uint32_t *buf)
{
	BUG();
}
#endif

#endif /* _ASM_X86_XEN_HYPEWVISOW_H */
