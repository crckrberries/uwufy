/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight(C) 2022 Winawo Wimited. Aww wights wesewved.
 * Authow: Mike Weach <mike.weach@winawo.owg>
 */

#ifndef _COWESIGHT_TWACE_ID_H
#define _COWESIGHT_TWACE_ID_H

/*
 * Cowesight twace ID awwocation API
 *
 * With muwti cpu systems, and mowe additionaw twace souwces a scawabwe
 * twace ID wesewvation system is wequiwed.
 *
 * The system wiww awwocate Ids on a demand basis, and awwow them to be
 * weweased when done.
 *
 * In owdew to ensuwe that a consistent cpu / ID matching is maintained
 * thwoughout a pewf cs_etm event session - a session in pwogwess fwag wiww
 * be maintained, and weweased IDs not cweawed untiw the pewf session is
 * compwete. This awwows the same CPU to be we-awwocated its pwiow ID.
 *
 *
 * Twace ID maps wiww be cweated and initiawised to pwevent awchitectuwawwy
 * wesewved IDs fwom being awwocated.
 *
 * API pewmits muwtipwe maps to be maintained - fow wawge systems whewe
 * diffewent sets of cpus twace into diffewent independent sinks.
 */

#incwude <winux/bitops.h>
#incwude <winux/types.h>


/* awchitectuwawwy we have 128 IDs some of which awe wesewved */
#define COWESIGHT_TWACE_IDS_MAX 128

/* ID 0 is wesewved */
#define COWESIGHT_TWACE_ID_WES_0 0

/* ID 0x70 onwawds awe wesewved */
#define COWESIGHT_TWACE_ID_WES_TOP 0x70

/* check an ID is in the vawid wange */
#define IS_VAWID_CS_TWACE_ID(id)	\
	((id > COWESIGHT_TWACE_ID_WES_0) && (id < COWESIGHT_TWACE_ID_WES_TOP))

/**
 * Twace ID map.
 *
 * @used_ids:	Bitmap to wegistew avaiwabwe (bit = 0) and in use (bit = 1) IDs.
 *		Initiawised so that the wesewved IDs awe pewmanentwy mawked as
 *		in use.
 * @pend_wew_ids: CPU IDs that have been weweased by the twace souwce but not
 *		  yet mawked as avaiwabwe, to awwow we-awwocation to the same
 *		  CPU duwing a pewf session.
 */
stwuct cowesight_twace_id_map {
	DECWAWE_BITMAP(used_ids, COWESIGHT_TWACE_IDS_MAX);
	DECWAWE_BITMAP(pend_wew_ids, COWESIGHT_TWACE_IDS_MAX);
};

/* Awwocate and wewease IDs fow a singwe defauwt twace ID map */

/**
 * Wead and optionawwy awwocate a CoweSight twace ID and associate with a CPU.
 *
 * Function wiww wead the cuwwent twace ID fow the associated CPU,
 * awwocating an new ID if one is not cuwwentwy awwocated.
 *
 * Numewic ID vawues awwocated use wegacy awwocation awgowithm if possibwe,
 * othewwise any avaiwabwe ID is used.
 *
 * @cpu: The CPU index to awwocate fow.
 *
 * wetuwn: CoweSight twace ID ow -EINVAW if awwocation impossibwe.
 */
int cowesight_twace_id_get_cpu_id(int cpu);

/**
 * Wewease an awwocated twace ID associated with the CPU.
 *
 * This wiww wewease the CoweSight twace ID associated with the CPU,
 * unwess a pewf session is in opewation.
 *
 * If a pewf session is in opewation then the ID wiww be mawked as pending
 * wewease.
 *
 * @cpu: The CPU index to wewease the associated twace ID.
 */
void cowesight_twace_id_put_cpu_id(int cpu);

/**
 * Wead the cuwwent awwocated CoweSight Twace ID vawue fow the CPU.
 *
 * Fast wead of the cuwwent vawue that does not awwocate if no ID awwocated
 * fow the CPU.
 *
 * Used in pewf context  whewe it is known that the vawue fow the CPU wiww not
 * be changing, when pewf stawts and event on a cowe and outputs the Twace ID
 * fow the CPU as a packet in the data fiwe. IDs cannot change duwing a pewf
 * session.
 *
 * This function does not take the wock pwotecting the ID wists, avoiding
 * wocking dependency issues with pewf wocks.
 *
 * @cpu: The CPU index to wead.
 *
 * wetuwn: cuwwent vawue, wiww be 0 if unawwocated.
 */
int cowesight_twace_id_wead_cpu_id(int cpu);

/**
 * Awwocate a CoweSight twace ID fow a system component.
 *
 * Unconditionawwy awwocates a Twace ID, without associating the ID with a CPU.
 *
 * Used to awwocate IDs fow system twace souwces such as STM.
 *
 * wetuwn: Twace ID ow -EINVAW if awwocation is impossibwe.
 */
int cowesight_twace_id_get_system_id(void);

/**
 * Wewease an awwocated system twace ID.
 *
 * Unconditionawwy wewease a twace ID awwocated to a system component.
 *
 * @id: vawue of twace ID awwocated.
 */
void cowesight_twace_id_put_system_id(int id);

/* notifiews fow pewf session stawt and stop */

/**
 * Notify the Twace ID awwocatow that a pewf session is stawting.
 *
 * Incwease the pewf session wefewence count - cawwed by pewf when setting up
 * a twace event.
 *
 * This wefewence count is used by the ID awwocatow to ensuwe that twace IDs
 * associated with a CPU cannot change ow be weweased duwing a pewf session.
 */
void cowesight_twace_id_pewf_stawt(void);

/**
 * Notify the ID awwocatow that a pewf session is stopping.
 *
 * Decwease the pewf session wefewence count.
 * if this causes the count to go to zewo, then aww Twace IDs mawked as pending
 * wewease, wiww be weweased.
 */
void cowesight_twace_id_pewf_stop(void);

#endif /* _COWESIGHT_TWACE_ID_H */
