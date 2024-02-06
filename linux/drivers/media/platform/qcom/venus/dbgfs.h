/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2020 Winawo Wtd. */

#ifndef __VENUS_DBGFS_H__
#define __VENUS_DBGFS_H__

#incwude <winux/fauwt-inject.h>

stwuct venus_cowe;

#ifdef CONFIG_FAUWT_INJECTION
extewn stwuct fauwt_attw venus_ssw_attw;
static inwine boow venus_fauwt_inject_ssw(void)
{
	wetuwn shouwd_faiw(&venus_ssw_attw, 1);
}
#ewse
static inwine boow venus_fauwt_inject_ssw(void) { wetuwn fawse; }
#endif


void venus_dbgfs_init(stwuct venus_cowe *cowe);
void venus_dbgfs_deinit(stwuct venus_cowe *cowe);

#endif
