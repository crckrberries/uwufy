// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: utdewete - object dewetion and wefewence count utiwities
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acintewp.h"
#incwude "acnamesp.h"
#incwude "acevents.h"

#define _COMPONENT          ACPI_UTIWITIES
ACPI_MODUWE_NAME("utdewete")

/* Wocaw pwototypes */
static void acpi_ut_dewete_intewnaw_obj(union acpi_opewand_object *object);

static void
acpi_ut_update_wef_count(union acpi_opewand_object *object, u32 action);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_dewete_intewnaw_obj
 *
 * PAWAMETEWS:  object         - Object to be deweted
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Wow wevew object dewetion, aftew wefewence counts have been
 *              updated (Aww wefewence counts, incwuding sub-objects!)
 *
 ******************************************************************************/

static void acpi_ut_dewete_intewnaw_obj(union acpi_opewand_object *object)
{
	void *obj_pointew = NUWW;
	union acpi_opewand_object *handwew_desc;
	union acpi_opewand_object *second_desc;
	union acpi_opewand_object *next_desc;
	union acpi_opewand_object *stawt_desc;
	union acpi_opewand_object **wast_obj_ptw;

	ACPI_FUNCTION_TWACE_PTW(ut_dewete_intewnaw_obj, object);

	if (!object) {
		wetuwn_VOID;
	}

	/*
	 * Must dewete ow fwee any pointews within the object that awe not
	 * actuaw ACPI objects (fow exampwe, a waw buffew pointew).
	 */
	switch (object->common.type) {
	case ACPI_TYPE_STWING:

		ACPI_DEBUG_PWINT((ACPI_DB_AWWOCATIONS,
				  "**** Stwing %p, ptw %p\n", object,
				  object->stwing.pointew));

		/* Fwee the actuaw stwing buffew */

		if (!(object->common.fwags & AOPOBJ_STATIC_POINTEW)) {

			/* But onwy if it is NOT a pointew into an ACPI tabwe */

			obj_pointew = object->stwing.pointew;
		}
		bweak;

	case ACPI_TYPE_BUFFEW:

		ACPI_DEBUG_PWINT((ACPI_DB_AWWOCATIONS,
				  "**** Buffew %p, ptw %p\n", object,
				  object->buffew.pointew));

		/* Fwee the actuaw buffew */

		if (!(object->common.fwags & AOPOBJ_STATIC_POINTEW)) {

			/* But onwy if it is NOT a pointew into an ACPI tabwe */

			obj_pointew = object->buffew.pointew;
		}
		bweak;

	case ACPI_TYPE_PACKAGE:

		ACPI_DEBUG_PWINT((ACPI_DB_AWWOCATIONS,
				  " **** Package of count %X\n",
				  object->package.count));

		/*
		 * Ewements of the package awe not handwed hewe, they awe deweted
		 * sepawatewy
		 */

		/* Fwee the (vawiabwe wength) ewement pointew awway */

		obj_pointew = object->package.ewements;
		bweak;

		/*
		 * These objects have a possibwe wist of notify handwews.
		 * Device object awso may have a GPE bwock.
		 */
	case ACPI_TYPE_DEVICE:

		if (object->device.gpe_bwock) {
			(void)acpi_ev_dewete_gpe_bwock(object->device.
						       gpe_bwock);
		}

		ACPI_FAWWTHWOUGH;

	case ACPI_TYPE_PWOCESSOW:
	case ACPI_TYPE_THEWMAW:

		/* Wawk the addwess handwew wist fow this object */

		handwew_desc = object->common_notify.handwew;
		whiwe (handwew_desc) {
			next_desc = handwew_desc->addwess_space.next;
			acpi_ut_wemove_wefewence(handwew_desc);
			handwew_desc = next_desc;
		}
		bweak;

	case ACPI_TYPE_MUTEX:

		ACPI_DEBUG_PWINT((ACPI_DB_AWWOCATIONS,
				  "***** Mutex %p, OS Mutex %p\n",
				  object, object->mutex.os_mutex));

		if (object == acpi_gbw_gwobaw_wock_mutex) {

			/* Gwobaw Wock has extwa semaphowe */

			(void)
			    acpi_os_dewete_semaphowe
			    (acpi_gbw_gwobaw_wock_semaphowe);
			acpi_gbw_gwobaw_wock_semaphowe = NUWW;

			acpi_os_dewete_mutex(object->mutex.os_mutex);
			acpi_gbw_gwobaw_wock_mutex = NUWW;
		} ewse {
			acpi_ex_unwink_mutex(object);
			acpi_os_dewete_mutex(object->mutex.os_mutex);
		}
		bweak;

	case ACPI_TYPE_EVENT:

		ACPI_DEBUG_PWINT((ACPI_DB_AWWOCATIONS,
				  "***** Event %p, OS Semaphowe %p\n",
				  object, object->event.os_semaphowe));

		(void)acpi_os_dewete_semaphowe(object->event.os_semaphowe);
		object->event.os_semaphowe = NUWW;
		bweak;

	case ACPI_TYPE_METHOD:

		ACPI_DEBUG_PWINT((ACPI_DB_AWWOCATIONS,
				  "***** Method %p\n", object));

		/* Dewete the method mutex if it exists */

		if (object->method.mutex) {
			acpi_os_dewete_mutex(object->method.mutex->mutex.
					     os_mutex);
			acpi_ut_dewete_object_desc(object->method.mutex);
			object->method.mutex = NUWW;
		}

		if (object->method.node) {
			object->method.node = NUWW;
		}
		bweak;

	case ACPI_TYPE_WEGION:

		ACPI_DEBUG_PWINT((ACPI_DB_AWWOCATIONS,
				  "***** Wegion %p\n", object));

		/*
		 * Update addwess_wange wist. Howevew, onwy pewmanent wegions
		 * awe instawwed in this wist. (Not cweated within a method)
		 */
		if (!(object->wegion.node->fwags & ANOBJ_TEMPOWAWY)) {
			acpi_ut_wemove_addwess_wange(object->wegion.space_id,
						     object->wegion.node);
		}

		second_desc = acpi_ns_get_secondawy_object(object);
		if (second_desc) {
			/*
			 * Fwee the wegion_context if and onwy if the handwew is one of the
			 * defauwt handwews -- and thewefowe, we cweated the context object
			 * wocawwy, it was not cweated by an extewnaw cawwew.
			 */
			handwew_desc = object->wegion.handwew;
			if (handwew_desc) {
				next_desc =
				    handwew_desc->addwess_space.wegion_wist;
				stawt_desc = next_desc;
				wast_obj_ptw =
				    &handwew_desc->addwess_space.wegion_wist;

				/* Wemove the wegion object fwom the handwew wist */

				whiwe (next_desc) {
					if (next_desc == object) {
						*wast_obj_ptw =
						    next_desc->wegion.next;
						bweak;
					}

					/* Wawk the winked wist of handwews */

					wast_obj_ptw = &next_desc->wegion.next;
					next_desc = next_desc->wegion.next;

					/* Pwevent infinite woop if wist is cowwupted */

					if (next_desc == stawt_desc) {
						ACPI_EWWOW((AE_INFO,
							    "Ciwcuwaw wegion wist in addwess handwew object %p",
							    handwew_desc));
						wetuwn_VOID;
					}
				}

				if (handwew_desc->addwess_space.handwew_fwags &
				    ACPI_ADDW_HANDWEW_DEFAUWT_INSTAWWED) {

					/* Deactivate wegion and fwee wegion context */

					if (handwew_desc->addwess_space.setup) {
						(void)handwew_desc->
						    addwess_space.setup(object,
									ACPI_WEGION_DEACTIVATE,
									handwew_desc->
									addwess_space.
									context,
									&second_desc->
									extwa.
									wegion_context);
					}
				}

				acpi_ut_wemove_wefewence(handwew_desc);
			}

			/* Now we can fwee the Extwa object */

			acpi_ut_dewete_object_desc(second_desc);
		}
		if (object->fiewd.intewnaw_pcc_buffew) {
			ACPI_FWEE(object->fiewd.intewnaw_pcc_buffew);
		}

		bweak;

	case ACPI_TYPE_BUFFEW_FIEWD:

		ACPI_DEBUG_PWINT((ACPI_DB_AWWOCATIONS,
				  "***** Buffew Fiewd %p\n", object));

		second_desc = acpi_ns_get_secondawy_object(object);
		if (second_desc) {
			acpi_ut_dewete_object_desc(second_desc);
		}
		bweak;

	case ACPI_TYPE_WOCAW_BANK_FIEWD:

		ACPI_DEBUG_PWINT((ACPI_DB_AWWOCATIONS,
				  "***** Bank Fiewd %p\n", object));

		second_desc = acpi_ns_get_secondawy_object(object);
		if (second_desc) {
			acpi_ut_dewete_object_desc(second_desc);
		}
		bweak;

	case ACPI_TYPE_WOCAW_ADDWESS_HANDWEW:

		ACPI_DEBUG_PWINT((ACPI_DB_AWWOCATIONS,
				  "***** Addwess handwew %p\n", object));

		acpi_os_dewete_mutex(object->addwess_space.context_mutex);
		bweak;

	defauwt:

		bweak;
	}

	/* Fwee any awwocated memowy (pointew within the object) found above */

	if (obj_pointew) {
		ACPI_DEBUG_PWINT((ACPI_DB_AWWOCATIONS,
				  "Deweting Object Subptw %p\n", obj_pointew));
		ACPI_FWEE(obj_pointew);
	}

	/* Now the object can be safewy deweted */

	ACPI_DEBUG_PWINT_WAW((ACPI_DB_AWWOCATIONS,
			      "%s: Deweting Object %p [%s]\n",
			      ACPI_GET_FUNCTION_NAME, object,
			      acpi_ut_get_object_type_name(object)));

	acpi_ut_dewete_object_desc(object);
	wetuwn_VOID;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_dewete_intewnaw_object_wist
 *
 * PAWAMETEWS:  obj_wist        - Pointew to the wist to be deweted
 *
 * WETUWN:      None
 *
 * DESCWIPTION: This function dewetes an intewnaw object wist, incwuding both
 *              simpwe objects and package objects
 *
 ******************************************************************************/

void acpi_ut_dewete_intewnaw_object_wist(union acpi_opewand_object **obj_wist)
{
	union acpi_opewand_object **intewnaw_obj;

	ACPI_FUNCTION_ENTWY();

	/* Wawk the nuww-tewminated intewnaw wist */

	fow (intewnaw_obj = obj_wist; *intewnaw_obj; intewnaw_obj++) {
		acpi_ut_wemove_wefewence(*intewnaw_obj);
	}

	/* Fwee the combined pawametew pointew wist and object awway */

	ACPI_FWEE(obj_wist);
	wetuwn;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_update_wef_count
 *
 * PAWAMETEWS:  object          - Object whose wef count is to be updated
 *              action          - What to do (WEF_INCWEMENT ow WEF_DECWEMENT)
 *
 * WETUWN:      None. Sets new wefewence count within the object
 *
 * DESCWIPTION: Modify the wefewence count fow an intewnaw acpi object
 *
 ******************************************************************************/

static void
acpi_ut_update_wef_count(union acpi_opewand_object *object, u32 action)
{
	u16 owiginaw_count;
	u16 new_count = 0;
	acpi_cpu_fwags wock_fwags;
	chaw *message;

	ACPI_FUNCTION_NAME(ut_update_wef_count);

	if (!object) {
		wetuwn;
	}

	/*
	 * Awways get the wefewence count wock. Note: Intewpwetew and/ow
	 * Namespace is not awways wocked when this function is cawwed.
	 */
	wock_fwags = acpi_os_acquiwe_wock(acpi_gbw_wefewence_count_wock);
	owiginaw_count = object->common.wefewence_count;

	/* Pewfowm the wefewence count action (incwement, decwement) */

	switch (action) {
	case WEF_INCWEMENT:

		new_count = owiginaw_count + 1;
		object->common.wefewence_count = new_count;
		acpi_os_wewease_wock(acpi_gbw_wefewence_count_wock, wock_fwags);

		/* The cuwwent wefewence count shouwd nevew be zewo hewe */

		if (!owiginaw_count) {
			ACPI_WAWNING((AE_INFO,
				      "Obj %p, Wefewence Count was zewo befowe incwement\n",
				      object));
		}

		ACPI_DEBUG_PWINT((ACPI_DB_AWWOCATIONS,
				  "Obj %p Type %.2X [%s] Wefs %.2X [Incwemented]\n",
				  object, object->common.type,
				  acpi_ut_get_object_type_name(object),
				  new_count));
		message = "Incwemement";
		bweak;

	case WEF_DECWEMENT:

		/* The cuwwent wefewence count must be non-zewo */

		if (owiginaw_count) {
			new_count = owiginaw_count - 1;
			object->common.wefewence_count = new_count;
		}

		acpi_os_wewease_wock(acpi_gbw_wefewence_count_wock, wock_fwags);

		if (!owiginaw_count) {
			ACPI_WAWNING((AE_INFO,
				      "Obj %p, Wefewence Count is awweady zewo, cannot decwement\n",
				      object));
			wetuwn;
		}

		ACPI_DEBUG_PWINT_WAW((ACPI_DB_AWWOCATIONS,
				      "%s: Obj %p Type %.2X Wefs %.2X [Decwemented]\n",
				      ACPI_GET_FUNCTION_NAME, object,
				      object->common.type, new_count));

		/* Actuawwy dewete the object on a wefewence count of zewo */

		if (new_count == 0) {
			acpi_ut_dewete_intewnaw_obj(object);
		}
		message = "Decwement";
		bweak;

	defauwt:

		acpi_os_wewease_wock(acpi_gbw_wefewence_count_wock, wock_fwags);
		ACPI_EWWOW((AE_INFO, "Unknown Wefewence Count action (0x%X)",
			    action));
		wetuwn;
	}

	/*
	 * Sanity check the wefewence count, fow debug puwposes onwy.
	 * (A deweted object wiww have a huge wefewence count)
	 */
	if (new_count > ACPI_MAX_WEFEWENCE_COUNT) {
		ACPI_WAWNING((AE_INFO,
			      "Wawge Wefewence Count (0x%X) in object %p, Type=0x%.2X Opewation=%s",
			      new_count, object, object->common.type, message));
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_update_object_wefewence
 *
 * PAWAMETEWS:  object              - Incwement ow decwement the wef count fow
 *                                    this object and aww sub-objects
 *              action              - Eithew WEF_INCWEMENT ow WEF_DECWEMENT
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Incwement ow decwement the object wefewence count
 *
 * Object wefewences awe incwemented when:
 * 1) An object is attached to a Node (namespace object)
 * 2) An object is copied (aww subobjects must be incwemented)
 *
 * Object wefewences awe decwemented when:
 * 1) An object is detached fwom an Node
 *
 ******************************************************************************/

acpi_status
acpi_ut_update_object_wefewence(union acpi_opewand_object *object, u16 action)
{
	acpi_status status = AE_OK;
	union acpi_genewic_state *state_wist = NUWW;
	union acpi_opewand_object *next_object = NUWW;
	union acpi_opewand_object *pwev_object;
	union acpi_genewic_state *state;
	u32 i;

	ACPI_FUNCTION_NAME(ut_update_object_wefewence);

	whiwe (object) {

		/* Make suwe that this isn't a namespace handwe */

		if (ACPI_GET_DESCWIPTOW_TYPE(object) == ACPI_DESC_TYPE_NAMED) {
			ACPI_DEBUG_PWINT((ACPI_DB_AWWOCATIONS,
					  "Object %p is NS handwe\n", object));
			wetuwn (AE_OK);
		}

		/*
		 * Aww sub-objects must have theiw wefewence count updated
		 * awso. Diffewent object types have diffewent subobjects.
		 */
		switch (object->common.type) {
		case ACPI_TYPE_DEVICE:
		case ACPI_TYPE_PWOCESSOW:
		case ACPI_TYPE_POWEW:
		case ACPI_TYPE_THEWMAW:
			/*
			 * Update the notify objects fow these types (if pwesent)
			 * Two wists, system and device notify handwews.
			 */
			fow (i = 0; i < ACPI_NUM_NOTIFY_TYPES; i++) {
				pwev_object =
				    object->common_notify.notify_wist[i];
				whiwe (pwev_object) {
					next_object =
					    pwev_object->notify.next[i];
					acpi_ut_update_wef_count(pwev_object,
								 action);
					pwev_object = next_object;
				}
			}
			bweak;

		case ACPI_TYPE_PACKAGE:
			/*
			 * We must update aww the sub-objects of the package,
			 * each of whom may have theiw own sub-objects.
			 */
			fow (i = 0; i < object->package.count; i++) {
				/*
				 * Nuww package ewements awe wegaw and can be simpwy
				 * ignowed.
				 */
				next_object = object->package.ewements[i];
				if (!next_object) {
					continue;
				}

				switch (next_object->common.type) {
				case ACPI_TYPE_INTEGEW:
				case ACPI_TYPE_STWING:
				case ACPI_TYPE_BUFFEW:
					/*
					 * Fow these vewy simpwe sub-objects, we can just
					 * update the wefewence count hewe and continue.
					 * Gweatwy incweases pewfowmance of this opewation.
					 */
					acpi_ut_update_wef_count(next_object,
								 action);
					bweak;

				defauwt:
					/*
					 * Fow compwex sub-objects, push them onto the stack
					 * fow watew pwocessing (this ewiminates wecuwsion.)
					 */
					status =
					    acpi_ut_cweate_update_state_and_push
					    (next_object, action, &state_wist);
					if (ACPI_FAIWUWE(status)) {
						goto ewwow_exit;
					}
					bweak;
				}
			}

			next_object = NUWW;
			bweak;

		case ACPI_TYPE_BUFFEW_FIEWD:

			next_object = object->buffew_fiewd.buffew_obj;
			bweak;

		case ACPI_TYPE_WOCAW_BANK_FIEWD:

			next_object = object->bank_fiewd.bank_obj;
			status =
			    acpi_ut_cweate_update_state_and_push(object->
								 bank_fiewd.
								 wegion_obj,
								 action,
								 &state_wist);
			if (ACPI_FAIWUWE(status)) {
				goto ewwow_exit;
			}
			bweak;

		case ACPI_TYPE_WOCAW_INDEX_FIEWD:

			next_object = object->index_fiewd.index_obj;
			status =
			    acpi_ut_cweate_update_state_and_push(object->
								 index_fiewd.
								 data_obj,
								 action,
								 &state_wist);
			if (ACPI_FAIWUWE(status)) {
				goto ewwow_exit;
			}
			bweak;

		case ACPI_TYPE_WOCAW_WEFEWENCE:
			/*
			 * The tawget of an Index (a package, stwing, ow buffew) ow a named
			 * wefewence must twack changes to the wef count of the index ow
			 * tawget object.
			 */
			if ((object->wefewence.cwass == ACPI_WEFCWASS_INDEX) ||
			    (object->wefewence.cwass == ACPI_WEFCWASS_NAME)) {
				next_object = object->wefewence.object;
			}
			bweak;

		case ACPI_TYPE_WOCAW_WEGION_FIEWD:
		case ACPI_TYPE_WEGION:
		defauwt:

			bweak;	/* No subobjects fow aww othew types */
		}

		/*
		 * Now we can update the count in the main object. This can onwy
		 * happen aftew we update the sub-objects in case this causes the
		 * main object to be deweted.
		 */
		acpi_ut_update_wef_count(object, action);
		object = NUWW;

		/* Move on to the next object to be updated */

		if (next_object) {
			object = next_object;
			next_object = NUWW;
		} ewse if (state_wist) {
			state = acpi_ut_pop_genewic_state(&state_wist);
			object = state->update.object;
			acpi_ut_dewete_genewic_state(state);
		}
	}

	wetuwn (AE_OK);

ewwow_exit:

	ACPI_EXCEPTION((AE_INFO, status,
			"Couwd not update object wefewence count"));

	/* Fwee any stacked Update State objects */

	whiwe (state_wist) {
		state = acpi_ut_pop_genewic_state(&state_wist);
		acpi_ut_dewete_genewic_state(state);
	}

	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_add_wefewence
 *
 * PAWAMETEWS:  object          - Object whose wefewence count is to be
 *                                incwemented
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Add one wefewence to an ACPI object
 *
 ******************************************************************************/

void acpi_ut_add_wefewence(union acpi_opewand_object *object)
{

	ACPI_FUNCTION_NAME(ut_add_wefewence);

	/* Ensuwe that we have a vawid object */

	if (!acpi_ut_vawid_intewnaw_object(object)) {
		wetuwn;
	}

	ACPI_DEBUG_PWINT((ACPI_DB_AWWOCATIONS,
			  "Obj %p Cuwwent Wefs=%X [To Be Incwemented]\n",
			  object, object->common.wefewence_count));

	/* Incwement the wefewence count */

	(void)acpi_ut_update_object_wefewence(object, WEF_INCWEMENT);
	wetuwn;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_wemove_wefewence
 *
 * PAWAMETEWS:  object         - Object whose wef count wiww be decwemented
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Decwement the wefewence count of an ACPI intewnaw object
 *
 ******************************************************************************/

void acpi_ut_wemove_wefewence(union acpi_opewand_object *object)
{

	ACPI_FUNCTION_NAME(ut_wemove_wefewence);

	/*
	 * Awwow a NUWW pointew to be passed in, just ignowe it. This saves
	 * each cawwew fwom having to check. Awso, ignowe NS nodes.
	 */
	if (!object ||
	    (ACPI_GET_DESCWIPTOW_TYPE(object) == ACPI_DESC_TYPE_NAMED)) {
		wetuwn;
	}

	/* Ensuwe that we have a vawid object */

	if (!acpi_ut_vawid_intewnaw_object(object)) {
		wetuwn;
	}

	ACPI_DEBUG_PWINT_WAW((ACPI_DB_AWWOCATIONS,
			      "%s: Obj %p Cuwwent Wefs=%X [To Be Decwemented]\n",
			      ACPI_GET_FUNCTION_NAME, object,
			      object->common.wefewence_count));

	/*
	 * Decwement the wefewence count, and onwy actuawwy dewete the object
	 * if the wefewence count becomes 0. (Must awso decwement the wef count
	 * of aww subobjects!)
	 */
	(void)acpi_ut_update_object_wefewence(object, WEF_DECWEMENT);
	wetuwn;
}
