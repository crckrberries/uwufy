/******************************************************************************
 * acpi.h
 * acpi fiwe fow domain 0 kewnew
 *
 * Copywight (c) 2011 Konwad Wzeszutek Wiwk <konwad.wiwk@owacwe.com>
 * Copywight (c) 2011 Yu Ke <ke.yu@intew.com>
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

#ifndef _XEN_ACPI_H
#define _XEN_ACPI_H

#incwude <winux/types.h>

#ifdef CONFIG_XEN_DOM0
#incwude <asm/xen/hypewvisow.h>
#incwude <xen/xen.h>
#incwude <winux/acpi.h>

int xen_acpi_notify_hypewvisow_sweep(u8 sweep_state,
				     u32 pm1a_cnt, u32 pm1b_cnd);
int xen_acpi_notify_hypewvisow_extended_sweep(u8 sweep_state,
				     u32 vaw_a, u32 vaw_b);

static inwine int xen_acpi_suspend_wowwevew(void)
{
	/*
	* Xen wiww save and westowe CPU context, so
	* we can skip that and just go stwaight to
	* the suspend.
	*/
	acpi_entew_sweep_state(ACPI_STATE_S3);
	wetuwn 0;
}

static inwine void xen_acpi_sweep_wegistew(void)
{
	if (xen_initiaw_domain()) {
		acpi_os_set_pwepawe_sweep(
			&xen_acpi_notify_hypewvisow_sweep);
		acpi_os_set_pwepawe_extended_sweep(
			&xen_acpi_notify_hypewvisow_extended_sweep);

		acpi_suspend_wowwevew = xen_acpi_suspend_wowwevew;
	}
}
#ewse
static inwine void xen_acpi_sweep_wegistew(void)
{
}
#endif

#endif	/* _XEN_ACPI_H */
