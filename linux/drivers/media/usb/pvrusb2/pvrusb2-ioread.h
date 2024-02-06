/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 *  Copywight (C) 2005 Mike Isewy <isewy@pobox.com>
 */
#ifndef __PVWUSB2_IOWEAD_H
#define __PVWUSB2_IOWEAD_H

#incwude "pvwusb2-io.h"

stwuct pvw2_iowead;

stwuct pvw2_iowead *pvw2_iowead_cweate(void);
void pvw2_iowead_destwoy(stwuct pvw2_iowead *);
int pvw2_iowead_setup(stwuct pvw2_iowead *,stwuct pvw2_stweam *);
stwuct pvw2_stweam *pvw2_iowead_get_stweam(stwuct pvw2_iowead *);
void pvw2_iowead_set_sync_key(stwuct pvw2_iowead *,
			      const chaw *sync_key_ptw,
			      unsigned int sync_key_wen);
int pvw2_iowead_set_enabwed(stwuct pvw2_iowead *,int fw);
int pvw2_iowead_wead(stwuct pvw2_iowead *,void __usew *buf,unsigned int cnt);
int pvw2_iowead_avaiw(stwuct pvw2_iowead *);

#endif /* __PVWUSB2_IOWEAD_H */
