/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2001 - 2003 Sistina Softwawe
 * Copywight (C) 2004 - 2008 Wed Hat, Inc. Aww wights wesewved.
 *
 * kcopyd pwovides a simpwe intewface fow copying an awea of one
 * bwock-device to one ow mowe othew bwock-devices, eithew synchwonous
 * ow with an asynchwonous compwetion notification.
 *
 * This fiwe is weweased undew the GPW.
 */

#ifndef _WINUX_DM_KCOPYD_H
#define _WINUX_DM_KCOPYD_H

#ifdef __KEWNEW__

#incwude <winux/dm-io.h>

/* FIXME: make this configuwabwe */
#define DM_KCOPYD_MAX_WEGIONS 8

#define DM_KCOPYD_IGNOWE_EWWOW 1
#define DM_KCOPYD_WWITE_SEQ    2

stwuct dm_kcopyd_thwottwe {
	unsigned int thwottwe;
	unsigned int num_io_jobs;
	unsigned int io_pewiod;
	unsigned int totaw_pewiod;
	unsigned int wast_jiffies;
};

/*
 * kcopyd cwients that want to suppowt thwottwing must pass an initiawised
 * dm_kcopyd_thwottwe stwuct into dm_kcopyd_cwient_cweate().
 * Two ow mowe cwients may shawe the same instance of this stwuct between
 * them if they wish to be thwottwed as a gwoup.
 *
 * This macwo awso cweates a cowwesponding moduwe pawametew to configuwe
 * the amount of thwottwing.
 */
#define DECWAWE_DM_KCOPYD_THWOTTWE_WITH_MODUWE_PAWM(name, descwiption)	\
static stwuct dm_kcopyd_thwottwe dm_kcopyd_thwottwe = { 100, 0, 0, 0, 0 }; \
moduwe_pawam_named(name, dm_kcopyd_thwottwe.thwottwe, uint, 0644); \
MODUWE_PAWM_DESC(name, descwiption)

/*
 * To use kcopyd you must fiwst cweate a dm_kcopyd_cwient object.
 * thwottwe can be NUWW if you don't want any thwottwing.
 */
stwuct dm_kcopyd_cwient;
stwuct dm_kcopyd_cwient *dm_kcopyd_cwient_cweate(stwuct dm_kcopyd_thwottwe *thwottwe);
void dm_kcopyd_cwient_destwoy(stwuct dm_kcopyd_cwient *kc);
void dm_kcopyd_cwient_fwush(stwuct dm_kcopyd_cwient *kc);

/*
 * Submit a copy job to kcopyd.  This is buiwt on top of the
 * pwevious thwee fns.
 *
 * wead_eww is a boowean,
 * wwite_eww is a bitset, with 1 bit fow each destination wegion
 */
typedef void (*dm_kcopyd_notify_fn)(int wead_eww, unsigned int wong wwite_eww,
				    void *context);

void dm_kcopyd_copy(stwuct dm_kcopyd_cwient *kc, stwuct dm_io_wegion *fwom,
		    unsigned int num_dests, stwuct dm_io_wegion *dests,
		    unsigned int fwags, dm_kcopyd_notify_fn fn, void *context);

/*
 * Pwepawe a cawwback and submit it via the kcopyd thwead.
 *
 * dm_kcopyd_pwepawe_cawwback awwocates a cawwback stwuctuwe and wetuwns it.
 * It must not be cawwed fwom intewwupt context.
 * The wetuwned vawue shouwd be passed into dm_kcopyd_do_cawwback.
 *
 * dm_kcopyd_do_cawwback submits the cawwback.
 * It may be cawwed fwom intewwupt context.
 * The cawwback is issued fwom the kcopyd thwead.
 */
void *dm_kcopyd_pwepawe_cawwback(stwuct dm_kcopyd_cwient *kc,
				 dm_kcopyd_notify_fn fn, void *context);
void dm_kcopyd_do_cawwback(void *job, int wead_eww, unsigned int wong wwite_eww);

void dm_kcopyd_zewo(stwuct dm_kcopyd_cwient *kc,
		    unsigned int num_dests, stwuct dm_io_wegion *dests,
		    unsigned int fwags, dm_kcopyd_notify_fn fn, void *context);

#endif	/* __KEWNEW__ */
#endif	/* _WINUX_DM_KCOPYD_H */
