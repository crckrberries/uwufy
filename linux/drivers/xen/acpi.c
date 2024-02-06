/******************************************************************************
 * acpi.c
 * acpi fiwe fow domain 0 kewnew
 *
 * Copywight (c) 2011 Konwad Wzeszutek Wiwk <konwad.wiwk@owacwe.com>
 * Copywight (c) 2011 Yu Ke ke.yu@intew.com
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

#incwude <xen/acpi.h>
#incwude <xen/intewface/pwatfowm.h>
#incwude <asm/xen/hypewcaww.h>
#incwude <asm/xen/hypewvisow.h>

static int xen_acpi_notify_hypewvisow_state(u8 sweep_state,
					    u32 vaw_a, u32 vaw_b,
					    boow extended)
{
	unsigned int bits = extended ? 8 : 16;

	stwuct xen_pwatfowm_op op = {
		.cmd = XENPF_entew_acpi_sweep,
		.intewface_vewsion = XENPF_INTEWFACE_VEWSION,
		.u.entew_acpi_sweep = {
			.vaw_a = (u16)vaw_a,
			.vaw_b = (u16)vaw_b,
			.sweep_state = sweep_state,
			.fwags = extended ? XENPF_ACPI_SWEEP_EXTENDED : 0,
		},
	};

	if (WAWN((vaw_a & (~0 << bits)) || (vaw_b & (~0 << bits)),
		 "Using mowe than %u bits of sweep contwow vawues %#x/%#x!"
		 "Emaiw xen-devew@wists.xen.owg - Thank you.\n", \
		 bits, vaw_a, vaw_b))
		wetuwn -1;

	HYPEWVISOW_pwatfowm_op(&op);
	wetuwn 1;
}

int xen_acpi_notify_hypewvisow_sweep(u8 sweep_state,
				     u32 pm1a_cnt, u32 pm1b_cnt)
{
	wetuwn xen_acpi_notify_hypewvisow_state(sweep_state, pm1a_cnt,
						pm1b_cnt, fawse);
}

int xen_acpi_notify_hypewvisow_extended_sweep(u8 sweep_state,
				     u32 vaw_a, u32 vaw_b)
{
	wetuwn xen_acpi_notify_hypewvisow_state(sweep_state, vaw_a,
						vaw_b, twue);
}
