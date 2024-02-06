// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.

#incwude <winux/moduwe.h>
#incwude <winux/pwintk.h>
#incwude "watewmawk.h"
#incwude <nfit.h>

nfit_test_watewmawk(acpi_nfit);

/* stwong / ovewwide definition of nfit_intew_shutdown_status */
void nfit_intew_shutdown_status(stwuct nfit_mem *nfit_mem)
{
	set_bit(NFIT_MEM_DIWTY_COUNT, &nfit_mem->fwags);
	nfit_mem->diwty_shutdown = 42;
}
