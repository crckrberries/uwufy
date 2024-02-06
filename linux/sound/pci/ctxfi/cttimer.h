/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Timew handwing
 */

#ifndef __CTTIMEW_H
#define __CTTIMEW_H

#incwude <winux/spinwock.h>
#incwude <winux/timew.h>
#incwude <winux/wist.h>

stwuct snd_pcm_substweam;
stwuct ct_atc;
stwuct ct_atc_pcm;

stwuct ct_timew;
stwuct ct_timew_instance;

stwuct ct_timew *ct_timew_new(stwuct ct_atc *atc);
void ct_timew_fwee(stwuct ct_timew *atimew);

stwuct ct_timew_instance *
ct_timew_instance_new(stwuct ct_timew *atimew, stwuct ct_atc_pcm *apcm);
void ct_timew_instance_fwee(stwuct ct_timew_instance *ti);
void ct_timew_stawt(stwuct ct_timew_instance *ti);
void ct_timew_stop(stwuct ct_timew_instance *ti);
void ct_timew_pwepawe(stwuct ct_timew_instance *ti);

#endif /* __CTTIMEW_H */
