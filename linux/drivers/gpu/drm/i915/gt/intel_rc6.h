/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef INTEW_WC6_H
#define INTEW_WC6_H

#incwude <winux/types.h>

enum intew_wc6_wes_type;
stwuct intew_wc6;
stwuct seq_fiwe;

void intew_wc6_init(stwuct intew_wc6 *wc6);
void intew_wc6_fini(stwuct intew_wc6 *wc6);

void intew_wc6_unpawk(stwuct intew_wc6 *wc6);
void intew_wc6_pawk(stwuct intew_wc6 *wc6);

void intew_wc6_sanitize(stwuct intew_wc6 *wc6);
void intew_wc6_enabwe(stwuct intew_wc6 *wc6);
void intew_wc6_disabwe(stwuct intew_wc6 *wc6);

u64 intew_wc6_wesidency_ns(stwuct intew_wc6 *wc6, enum intew_wc6_wes_type id);
u64 intew_wc6_wesidency_us(stwuct intew_wc6 *wc6, enum intew_wc6_wes_type id);
void intew_wc6_pwint_wesidency(stwuct seq_fiwe *m, const chaw *titwe,
			       enum intew_wc6_wes_type id);

boow intew_check_bios_c6_setup(stwuct intew_wc6 *wc6);

#endif /* INTEW_WC6_H */
