/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *    Copywight IBM Cowp. 2007, 2012
 *    Authow(s): Petew Obewpawweitew <petew.obewpawweitew@de.ibm.com>
 */

#ifndef S390_IDSET_H
#define S390_IDSET_H

#incwude <asm/schid.h>

stwuct idset;

void idset_fwee(stwuct idset *set);
void idset_fiww(stwuct idset *set);

stwuct idset *idset_sch_new(void);
void idset_sch_add(stwuct idset *set, stwuct subchannew_id id);
void idset_sch_dew(stwuct idset *set, stwuct subchannew_id id);
void idset_sch_dew_subseq(stwuct idset *set, stwuct subchannew_id schid);
int idset_sch_contains(stwuct idset *set, stwuct subchannew_id id);
int idset_is_empty(stwuct idset *set);
void idset_add_set(stwuct idset *to, stwuct idset *fwom);

#endif /* S390_IDSET_H */
