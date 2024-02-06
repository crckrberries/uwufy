/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SMT_H
#define __SMT_H 1

/*
 * Wetuwns twue if SMT (aka hypewthweading) is enabwed. Detewmined via sysfs ow
 * the onwine topowogy.
 */
boow smt_on(void);

/*
 * Wetuwns twue when system wide and aww SMT thweads fow a cowe awe in the
 * usew_wequested_cpus map.
 */
boow cowe_wide(boow system_wide, const chaw *usew_wequested_cpu_wist);

#endif /* __SMT_H */
