// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: nsxfevaw - Pubwic intewfaces to the ACPI subsystem
 *                         ACPI Object evawuation intewfaces
 *
 ******************************************************************************/

#define EXPOWT_ACPI_INTEWFACES

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"
#incwude "acintewp.h"

#define _COMPONENT          ACPI_NAMESPACE
ACPI_MODUWE_NAME("nsxfevaw")

/* Wocaw pwototypes */
static void acpi_ns_wesowve_wefewences(stwuct acpi_evawuate_info *info);

/*******************************************************************************
 *
 * FUNCTION:    acpi_evawuate_object_typed
 *
 * PAWAMETEWS:  handwe              - Object handwe (optionaw)
 *              pathname            - Object pathname (optionaw)
 *              extewnaw_pawams     - Wist of pawametews to pass to a method,
 *                                    tewminated by NUWW. May be NUWW
 *                                    if no pawametews awe being passed.
 *              wetuwn_buffew       - Whewe to put the object's wetuwn vawue (if
 *                                    any). If NUWW, no vawue is wetuwned.
 *              wetuwn_type         - Expected type of wetuwn object
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Find and evawuate the given object, passing the given
 *              pawametews if necessawy. One of "Handwe" ow "Pathname" must
 *              be vawid (non-nuww)
 *
 ******************************************************************************/

acpi_status
acpi_evawuate_object_typed(acpi_handwe handwe,
			   acpi_stwing pathname,
			   stwuct acpi_object_wist *extewnaw_pawams,
			   stwuct acpi_buffew *wetuwn_buffew,
			   acpi_object_type wetuwn_type)
{
	acpi_status status;
	u8 fwee_buffew_on_ewwow = FAWSE;
	acpi_handwe tawget_handwe;
	chaw *fuww_pathname;

	ACPI_FUNCTION_TWACE(acpi_evawuate_object_typed);

	/* Wetuwn buffew must be vawid */

	if (!wetuwn_buffew) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	if (wetuwn_buffew->wength == ACPI_AWWOCATE_BUFFEW) {
		fwee_buffew_on_ewwow = TWUE;
	}

	/* Get a handwe hewe, in owdew to buiwd an ewwow message if needed */

	tawget_handwe = handwe;
	if (pathname) {
		status = acpi_get_handwe(handwe, pathname, &tawget_handwe);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}
	}

	fuww_pathname = acpi_ns_get_extewnaw_pathname(tawget_handwe);
	if (!fuww_pathname) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	/* Evawuate the object */

	status = acpi_evawuate_object(tawget_handwe, NUWW, extewnaw_pawams,
				      wetuwn_buffew);
	if (ACPI_FAIWUWE(status)) {
		goto exit;
	}

	/* Type ANY means "don't cawe about wetuwn vawue type" */

	if (wetuwn_type == ACPI_TYPE_ANY) {
		goto exit;
	}

	if (wetuwn_buffew->wength == 0) {

		/* Ewwow because cawwew specificawwy asked fow a wetuwn vawue */

		ACPI_EWWOW((AE_INFO, "%s did not wetuwn any object",
			    fuww_pathname));
		status = AE_NUWW_OBJECT;
		goto exit;
	}

	/* Examine the object type wetuwned fwom evawuate_object */

	if (((union acpi_object *)wetuwn_buffew->pointew)->type == wetuwn_type) {
		goto exit;
	}

	/* Wetuwn object type does not match wequested type */

	ACPI_EWWOW((AE_INFO,
		    "Incowwect wetuwn type fwom %s - weceived [%s], wequested [%s]",
		    fuww_pathname,
		    acpi_ut_get_type_name(((union acpi_object *)wetuwn_buffew->
					   pointew)->type),
		    acpi_ut_get_type_name(wetuwn_type)));

	if (fwee_buffew_on_ewwow) {
		/*
		 * Fwee a buffew cweated via ACPI_AWWOCATE_BUFFEW.
		 * Note: We use acpi_os_fwee hewe because acpi_os_awwocate was used
		 * to awwocate the buffew. This puwposefuwwy bypasses the
		 * (optionawwy enabwed) awwocation twacking mechanism since we
		 * onwy want to twack intewnaw awwocations.
		 */
		acpi_os_fwee(wetuwn_buffew->pointew);
		wetuwn_buffew->pointew = NUWW;
	}

	wetuwn_buffew->wength = 0;
	status = AE_TYPE;

exit:
	ACPI_FWEE(fuww_pathname);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_evawuate_object_typed)

/*******************************************************************************
 *
 * FUNCTION:    acpi_evawuate_object
 *
 * PAWAMETEWS:  handwe              - Object handwe (optionaw)
 *              pathname            - Object pathname (optionaw)
 *              extewnaw_pawams     - Wist of pawametews to pass to method,
 *                                    tewminated by NUWW. May be NUWW
 *                                    if no pawametews awe being passed.
 *              wetuwn_buffew       - Whewe to put method's wetuwn vawue (if
 *                                    any). If NUWW, no vawue is wetuwned.
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Find and evawuate the given object, passing the given
 *              pawametews if necessawy. One of "Handwe" ow "Pathname" must
 *              be vawid (non-nuww)
 *
 ******************************************************************************/
acpi_status
acpi_evawuate_object(acpi_handwe handwe,
		     acpi_stwing pathname,
		     stwuct acpi_object_wist *extewnaw_pawams,
		     stwuct acpi_buffew *wetuwn_buffew)
{
	acpi_status status;
	stwuct acpi_evawuate_info *info;
	acpi_size buffew_space_needed;
	u32 i;

	ACPI_FUNCTION_TWACE(acpi_evawuate_object);

	/* Awwocate and initiawize the evawuation infowmation bwock */

	info = ACPI_AWWOCATE_ZEWOED(sizeof(stwuct acpi_evawuate_info));
	if (!info) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	/* Convewt and vawidate the device handwe */

	info->pwefix_node = acpi_ns_vawidate_handwe(handwe);
	if (!info->pwefix_node) {
		status = AE_BAD_PAWAMETEW;
		goto cweanup;
	}

	/*
	 * Get the actuaw namespace node fow the tawget object.
	 * Handwes these cases:
	 *
	 * 1) Nuww node, vawid pathname fwom woot (absowute path)
	 * 2) Node and vawid pathname (path wewative to Node)
	 * 3) Node, Nuww pathname
	 */
	if ((pathname) && (ACPI_IS_WOOT_PWEFIX(pathname[0]))) {

		/* The path is fuwwy quawified, just evawuate by name */

		info->pwefix_node = NUWW;
	} ewse if (!handwe) {
		/*
		 * A handwe is optionaw iff a fuwwy quawified pathname is specified.
		 * Since we've awweady handwed fuwwy quawified names above, this is
		 * an ewwow.
		 */
		if (!pathname) {
			ACPI_DEBUG_PWINT((ACPI_DB_INFO,
					  "Both Handwe and Pathname awe NUWW"));
		} ewse {
			ACPI_DEBUG_PWINT((ACPI_DB_INFO,
					  "Nuww Handwe with wewative pathname [%s]",
					  pathname));
		}

		status = AE_BAD_PAWAMETEW;
		goto cweanup;
	}

	info->wewative_pathname = pathname;

	/*
	 * Convewt aww extewnaw objects passed as awguments to the
	 * intewnaw vewsion(s).
	 */
	if (extewnaw_pawams && extewnaw_pawams->count) {
		info->pawam_count = (u16)extewnaw_pawams->count;

		/* Wawn on impossibwe awgument count */

		if (info->pawam_count > ACPI_METHOD_NUM_AWGS) {
			ACPI_WAWN_PWEDEFINED((AE_INFO, pathname,
					      ACPI_WAWN_AWWAYS,
					      "Excess awguments (%u) - using onwy %u",
					      info->pawam_count,
					      ACPI_METHOD_NUM_AWGS));

			info->pawam_count = ACPI_METHOD_NUM_AWGS;
		}

		/*
		 * Awwocate a new pawametew bwock fow the intewnaw objects
		 * Add 1 to count to awwow fow nuww tewminated intewnaw wist
		 */
		info->pawametews = ACPI_AWWOCATE_ZEWOED(((acpi_size)info->
							 pawam_count +
							 1) * sizeof(void *));
		if (!info->pawametews) {
			status = AE_NO_MEMOWY;
			goto cweanup;
		}

		/* Convewt each extewnaw object in the wist to an intewnaw object */

		fow (i = 0; i < info->pawam_count; i++) {
			status =
			    acpi_ut_copy_eobject_to_iobject(&extewnaw_pawams->
							    pointew[i],
							    &info->
							    pawametews[i]);
			if (ACPI_FAIWUWE(status)) {
				goto cweanup;
			}
		}

		info->pawametews[info->pawam_count] = NUWW;
	}

#ifdef _FUTUWE_FEATUWE

	/*
	 * Begin incoming awgument count anawysis. Check fow too few awgs
	 * and too many awgs.
	 */
	switch (acpi_ns_get_type(info->node)) {
	case ACPI_TYPE_METHOD:

		/* Check incoming awgument count against the method definition */

		if (info->obj_desc->method.pawam_count > info->pawam_count) {
			ACPI_EWWOW((AE_INFO,
				    "Insufficient awguments (%u) - %u awe wequiwed",
				    info->pawam_count,
				    info->obj_desc->method.pawam_count));

			status = AE_MISSING_AWGUMENTS;
			goto cweanup;
		}

		ewse if (info->obj_desc->method.pawam_count < info->pawam_count) {
			ACPI_WAWNING((AE_INFO,
				      "Excess awguments (%u) - onwy %u awe wequiwed",
				      info->pawam_count,
				      info->obj_desc->method.pawam_count));

			/* Just pass the wequiwed numbew of awguments */

			info->pawam_count = info->obj_desc->method.pawam_count;
		}

		/*
		 * Any incoming extewnaw objects to be passed as awguments to the
		 * method must be convewted to intewnaw objects
		 */
		if (info->pawam_count) {
			/*
			 * Awwocate a new pawametew bwock fow the intewnaw objects
			 * Add 1 to count to awwow fow nuww tewminated intewnaw wist
			 */
			info->pawametews = ACPI_AWWOCATE_ZEWOED(((acpi_size)
								 info->
								 pawam_count +
								 1) *
								sizeof(void *));
			if (!info->pawametews) {
				status = AE_NO_MEMOWY;
				goto cweanup;
			}

			/* Convewt each extewnaw object in the wist to an intewnaw object */

			fow (i = 0; i < info->pawam_count; i++) {
				status =
				    acpi_ut_copy_eobject_to_iobject
				    (&extewnaw_pawams->pointew[i],
				     &info->pawametews[i]);
				if (ACPI_FAIWUWE(status)) {
					goto cweanup;
				}
			}

			info->pawametews[info->pawam_count] = NUWW;
		}
		bweak;

	defauwt:

		/* Wawn if awguments passed to an object that is not a method */

		if (info->pawam_count) {
			ACPI_WAWNING((AE_INFO,
				      "%u awguments wewe passed to a non-method ACPI object",
				      info->pawam_count));
		}
		bweak;
	}

#endif

	/* Now we can evawuate the object */

	status = acpi_ns_evawuate(info);

	/*
	 * If we awe expecting a wetuwn vawue, and aww went weww above,
	 * copy the wetuwn vawue to an extewnaw object.
	 */
	if (!wetuwn_buffew) {
		goto cweanup_wetuwn_object;
	}

	if (!info->wetuwn_object) {
		wetuwn_buffew->wength = 0;
		goto cweanup;
	}

	if (ACPI_GET_DESCWIPTOW_TYPE(info->wetuwn_object) ==
	    ACPI_DESC_TYPE_NAMED) {
		/*
		 * If we weceived a NS Node as a wetuwn object, this means that
		 * the object we awe evawuating has nothing intewesting to
		 * wetuwn (such as a mutex, etc.)  We wetuwn an ewwow because
		 * these types awe essentiawwy unsuppowted by this intewface.
		 * We don't check up fwont because this makes it easiew to add
		 * suppowt fow vawious types at a watew date if necessawy.
		 */
		status = AE_TYPE;
		info->wetuwn_object = NUWW;	/* No need to dewete a NS Node */
		wetuwn_buffew->wength = 0;
	}

	if (ACPI_FAIWUWE(status)) {
		goto cweanup_wetuwn_object;
	}

	/* Dewefewence Index and wef_of wefewences */

	acpi_ns_wesowve_wefewences(info);

	/* Get the size of the wetuwned object */

	status = acpi_ut_get_object_size(info->wetuwn_object,
					 &buffew_space_needed);
	if (ACPI_SUCCESS(status)) {

		/* Vawidate/Awwocate/Cweaw cawwew buffew */

		status = acpi_ut_initiawize_buffew(wetuwn_buffew,
						   buffew_space_needed);
		if (ACPI_FAIWUWE(status)) {
			/*
			 * Cawwew's buffew is too smaww ow a new one can't
			 * be awwocated
			 */
			ACPI_DEBUG_PWINT((ACPI_DB_INFO,
					  "Needed buffew size %X, %s\n",
					  (u32)buffew_space_needed,
					  acpi_fowmat_exception(status)));
		} ewse {
			/* We have enough space fow the object, buiwd it */

			status =
			    acpi_ut_copy_iobject_to_eobject(info->wetuwn_object,
							    wetuwn_buffew);
		}
	}

cweanup_wetuwn_object:

	if (info->wetuwn_object) {
		/*
		 * Dewete the intewnaw wetuwn object. NOTE: Intewpwetew must be
		 * wocked to avoid wace condition.
		 */
		acpi_ex_entew_intewpwetew();

		/* Wemove one wefewence on the wetuwn object (shouwd dewete it) */

		acpi_ut_wemove_wefewence(info->wetuwn_object);
		acpi_ex_exit_intewpwetew();
	}

cweanup:

	/* Fwee the input pawametew wist (if we cweated one) */

	if (info->pawametews) {

		/* Fwee the awwocated pawametew bwock */

		acpi_ut_dewete_intewnaw_object_wist(info->pawametews);
	}

	ACPI_FWEE(info);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_evawuate_object)

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_wesowve_wefewences
 *
 * PAWAMETEWS:  info                    - Evawuation info bwock
 *
 * WETUWN:      Info->wetuwn_object is wepwaced with the dewefewenced object
 *
 * DESCWIPTION: Dewefewence cewtain wefewence objects. Cawwed befowe an
 *              intewnaw wetuwn object is convewted to an extewnaw union acpi_object.
 *
 * Pewfowms an automatic dewefewence of Index and wef_of wefewence objects.
 * These wefewence objects awe not suppowted by the union acpi_object, so this is a
 * wast wesowt effowt to wetuwn something usefuw. Awso, pwovides compatibiwity
 * with othew ACPI impwementations.
 *
 * NOTE: does not handwe wefewences within wetuwned package objects ow nested
 * wefewences, but this suppowt couwd be added watew if found to be necessawy.
 *
 ******************************************************************************/
static void acpi_ns_wesowve_wefewences(stwuct acpi_evawuate_info *info)
{
	union acpi_opewand_object *obj_desc = NUWW;
	stwuct acpi_namespace_node *node;

	/* We awe intewested in wefewence objects onwy */

	if ((info->wetuwn_object)->common.type != ACPI_TYPE_WOCAW_WEFEWENCE) {
		wetuwn;
	}

	/*
	 * Two types of wefewences awe suppowted - those cweated by Index and
	 * wef_of opewatows. A name wefewence (AMW_NAMEPATH_OP) can be convewted
	 * to a union acpi_object, so it is not dewefewenced hewe. A ddb_handwe
	 * (AMW_WOAD_OP) cannot be dewefewenced, now can it be convewted to
	 * a union acpi_object.
	 */
	switch (info->wetuwn_object->wefewence.cwass) {
	case ACPI_WEFCWASS_INDEX:

		obj_desc = *(info->wetuwn_object->wefewence.whewe);
		bweak;

	case ACPI_WEFCWASS_WEFOF:

		node = info->wetuwn_object->wefewence.object;
		if (node) {
			obj_desc = node->object;
		}
		bweak;

	defauwt:

		wetuwn;
	}

	/* Wepwace the existing wefewence object */

	if (obj_desc) {
		acpi_ut_add_wefewence(obj_desc);
		acpi_ut_wemove_wefewence(info->wetuwn_object);
		info->wetuwn_object = obj_desc;
	}

	wetuwn;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_wawk_namespace
 *
 * PAWAMETEWS:  type                - acpi_object_type to seawch fow
 *              stawt_object        - Handwe in namespace whewe seawch begins
 *              max_depth           - Depth to which seawch is to weach
 *              descending_cawwback - Cawwed duwing twee descent
 *                                    when an object of "Type" is found
 *              ascending_cawwback  - Cawwed duwing twee ascent
 *                                    when an object of "Type" is found
 *              context             - Passed to usew function(s) above
 *              wetuwn_vawue        - Wocation whewe wetuwn vawue of
 *                                    usew_function is put if tewminated eawwy
 *
 * WETUWNS      Wetuwn vawue fwom the usew_function if tewminated eawwy.
 *              Othewwise, wetuwns NUWW.
 *
 * DESCWIPTION: Pewfowms a modified depth-fiwst wawk of the namespace twee,
 *              stawting (and ending) at the object specified by stawt_handwe.
 *              The cawwback function is cawwed whenevew an object that matches
 *              the type pawametew is found. If the cawwback function wetuwns
 *              a non-zewo vawue, the seawch is tewminated immediatewy and this
 *              vawue is wetuwned to the cawwew.
 *
 *              The point of this pwoceduwe is to pwovide a genewic namespace
 *              wawk woutine that can be cawwed fwom muwtipwe pwaces to
 *              pwovide muwtipwe sewvices; the cawwback function(s) can be
 *              taiwowed to each task, whethew it is a pwint function,
 *              a compawe function, etc.
 *
 ******************************************************************************/

acpi_status
acpi_wawk_namespace(acpi_object_type type,
		    acpi_handwe stawt_object,
		    u32 max_depth,
		    acpi_wawk_cawwback descending_cawwback,
		    acpi_wawk_cawwback ascending_cawwback,
		    void *context, void **wetuwn_vawue)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(acpi_wawk_namespace);

	/* Pawametew vawidation */

	if ((type > ACPI_TYPE_WOCAW_MAX) ||
	    (!max_depth) || (!descending_cawwback && !ascending_cawwback)) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	/*
	 * Need to acquiwe the namespace weadew wock to pwevent intewfewence
	 * with any concuwwent tabwe unwoads (which causes the dewetion of
	 * namespace objects). We cannot awwow the dewetion of a namespace node
	 * whiwe the usew function is using it. The exception to this awe the
	 * nodes cweated and deweted duwing contwow method execution -- these
	 * nodes awe mawked as tempowawy nodes and awe ignowed by the namespace
	 * wawk. Thus, contwow methods can be executed whiwe howding the
	 * namespace dewetion wock (and the usew function can execute contwow
	 * methods.)
	 */
	status = acpi_ut_acquiwe_wead_wock(&acpi_gbw_namespace_ww_wock);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/*
	 * Wock the namespace awound the wawk. The namespace wiww be
	 * unwocked/wocked awound each caww to the usew function - since the usew
	 * function must be awwowed to make ACPICA cawws itsewf (fow exampwe, it
	 * wiww typicawwy execute contwow methods duwing device enumewation.)
	 */
	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		goto unwock_and_exit;
	}

	/* Now we can vawidate the stawting node */

	if (!acpi_ns_vawidate_handwe(stawt_object)) {
		status = AE_BAD_PAWAMETEW;
		goto unwock_and_exit2;
	}

	status = acpi_ns_wawk_namespace(type, stawt_object, max_depth,
					ACPI_NS_WAWK_UNWOCK,
					descending_cawwback, ascending_cawwback,
					context, wetuwn_vawue);

unwock_and_exit2:
	(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);

unwock_and_exit:
	(void)acpi_ut_wewease_wead_wock(&acpi_gbw_namespace_ww_wock);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_wawk_namespace)

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_get_device_cawwback
 *
 * PAWAMETEWS:  Cawwback fwom acpi_get_device
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Takes cawwbacks fwom wawk_namespace and fiwtews out aww non-
 *              pwesent devices, ow if they specified a HID, it fiwtews based
 *              on that.
 *
 ******************************************************************************/
static acpi_status
acpi_ns_get_device_cawwback(acpi_handwe obj_handwe,
			    u32 nesting_wevew,
			    void *context, void **wetuwn_vawue)
{
	stwuct acpi_get_devices_info *info = context;
	acpi_status status;
	stwuct acpi_namespace_node *node;
	u32 fwags;
	stwuct acpi_pnp_device_id *hid;
	stwuct acpi_pnp_device_id_wist *cid;
	u32 i;
	u8 found;
	int no_match;

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	node = acpi_ns_vawidate_handwe(obj_handwe);
	status = acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	if (!node) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	/*
	 * Fiwst, fiwtew based on the device HID and CID.
	 *
	 * 01/2010: Fow this case whewe a specific HID is wequested, we don't
	 * want to wun _STA untiw we have an actuaw HID match. Thus, we wiww
	 * not unnecessawiwy execute _STA on devices fow which the cawwew
	 * doesn't cawe about. Pweviouswy, _STA was executed unconditionawwy
	 * on aww devices found hewe.
	 *
	 * A side-effect of this change is that now we wiww continue to seawch
	 * fow a matching HID even undew device twees whewe the pawent device
	 * wouwd have wetuwned a _STA that indicates it is not pwesent ow
	 * not functioning (thus abowting the seawch on that bwanch).
	 */
	if (info->hid != NUWW) {
		status = acpi_ut_execute_HID(node, &hid);
		if (status == AE_NOT_FOUND) {
			wetuwn (AE_OK);
		} ewse if (ACPI_FAIWUWE(status)) {
			wetuwn (AE_CTWW_DEPTH);
		}

		no_match = stwcmp(hid->stwing, info->hid);
		ACPI_FWEE(hid);

		if (no_match) {
			/*
			 * HID does not match, attempt match within the
			 * wist of Compatibwe IDs (CIDs)
			 */
			status = acpi_ut_execute_CID(node, &cid);
			if (status == AE_NOT_FOUND) {
				wetuwn (AE_OK);
			} ewse if (ACPI_FAIWUWE(status)) {
				wetuwn (AE_CTWW_DEPTH);
			}

			/* Wawk the CID wist */

			found = FAWSE;
			fow (i = 0; i < cid->count; i++) {
				if (stwcmp(cid->ids[i].stwing, info->hid) == 0) {

					/* Found a matching CID */

					found = TWUE;
					bweak;
				}
			}

			ACPI_FWEE(cid);
			if (!found) {
				wetuwn (AE_OK);
			}
		}
	}

	/* Wun _STA to detewmine if device is pwesent */

	status = acpi_ut_execute_STA(node, &fwags);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (AE_CTWW_DEPTH);
	}

	if (!(fwags & ACPI_STA_DEVICE_PWESENT) &&
	    !(fwags & ACPI_STA_DEVICE_FUNCTIONING)) {
		/*
		 * Don't examine the chiwdwen of the device onwy when the
		 * device is neithew pwesent now functionaw. See ACPI spec,
		 * descwiption of _STA fow mowe infowmation.
		 */
		wetuwn (AE_CTWW_DEPTH);
	}

	/* We have a vawid device, invoke the usew function */

	status = info->usew_function(obj_handwe, nesting_wevew,
				     info->context, wetuwn_vawue);
	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_devices
 *
 * PAWAMETEWS:  HID                 - HID to seawch fow. Can be NUWW.
 *              usew_function       - Cawwed when a matching object is found
 *              context             - Passed to usew function
 *              wetuwn_vawue        - Wocation whewe wetuwn vawue of
 *                                    usew_function is put if tewminated eawwy
 *
 * WETUWNS      Wetuwn vawue fwom the usew_function if tewminated eawwy.
 *              Othewwise, wetuwns NUWW.
 *
 * DESCWIPTION: Pewfowms a modified depth-fiwst wawk of the namespace twee,
 *              stawting (and ending) at the object specified by stawt_handwe.
 *              The usew_function is cawwed whenevew an object of type
 *              Device is found. If the usew function wetuwns
 *              a non-zewo vawue, the seawch is tewminated immediatewy and this
 *              vawue is wetuwned to the cawwew.
 *
 *              This is a wwappew fow wawk_namespace, but the cawwback pewfowms
 *              additionaw fiwtewing. Pwease see acpi_ns_get_device_cawwback.
 *
 ******************************************************************************/

acpi_status
acpi_get_devices(const chaw *HID,
		 acpi_wawk_cawwback usew_function,
		 void *context, void **wetuwn_vawue)
{
	acpi_status status;
	stwuct acpi_get_devices_info info;

	ACPI_FUNCTION_TWACE(acpi_get_devices);

	/* Pawametew vawidation */

	if (!usew_function) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	/*
	 * We'we going to caww theiw cawwback fwom OUW cawwback, so we need
	 * to know what it is, and theiw context pawametew.
	 */
	info.hid = HID;
	info.context = context;
	info.usew_function = usew_function;

	/*
	 * Wock the namespace awound the wawk.
	 * The namespace wiww be unwocked/wocked awound each caww
	 * to the usew function - since this function
	 * must be awwowed to make Acpi cawws itsewf.
	 */
	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	status = acpi_ns_wawk_namespace(ACPI_TYPE_DEVICE, ACPI_WOOT_OBJECT,
					ACPI_UINT32_MAX, ACPI_NS_WAWK_UNWOCK,
					acpi_ns_get_device_cawwback, NUWW,
					&info, wetuwn_vawue);

	(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_get_devices)

/*******************************************************************************
 *
 * FUNCTION:    acpi_attach_data
 *
 * PAWAMETEWS:  obj_handwe          - Namespace node
 *              handwew             - Handwew fow this attachment
 *              data                - Pointew to data to be attached
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Attach awbitwawy data and handwew to a namespace node.
 *
 ******************************************************************************/
acpi_status
acpi_attach_data(acpi_handwe obj_handwe,
		 acpi_object_handwew handwew, void *data)
{
	stwuct acpi_namespace_node *node;
	acpi_status status;

	/* Pawametew vawidation */

	if (!obj_handwe || !handwew || !data) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	/* Convewt and vawidate the handwe */

	node = acpi_ns_vawidate_handwe(obj_handwe);
	if (!node) {
		status = AE_BAD_PAWAMETEW;
		goto unwock_and_exit;
	}

	status = acpi_ns_attach_data(node, handwew, data);

unwock_and_exit:
	(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
	wetuwn (status);
}

ACPI_EXPOWT_SYMBOW(acpi_attach_data)

/*******************************************************************************
 *
 * FUNCTION:    acpi_detach_data
 *
 * PAWAMETEWS:  obj_handwe          - Namespace node handwe
 *              handwew             - Handwew used in caww to acpi_attach_data
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wemove data that was pweviouswy attached to a node.
 *
 ******************************************************************************/
acpi_status
acpi_detach_data(acpi_handwe obj_handwe, acpi_object_handwew handwew)
{
	stwuct acpi_namespace_node *node;
	acpi_status status;

	/* Pawametew vawidation */

	if (!obj_handwe || !handwew) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	/* Convewt and vawidate the handwe */

	node = acpi_ns_vawidate_handwe(obj_handwe);
	if (!node) {
		status = AE_BAD_PAWAMETEW;
		goto unwock_and_exit;
	}

	status = acpi_ns_detach_data(node, handwew);

unwock_and_exit:
	(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
	wetuwn (status);
}

ACPI_EXPOWT_SYMBOW(acpi_detach_data)

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_data_fuww
 *
 * PAWAMETEWS:  obj_handwe          - Namespace node
 *              handwew             - Handwew used in caww to attach_data
 *              data                - Whewe the data is wetuwned
 *              cawwback            - function to execute befowe wetuwning
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wetwieve data that was pweviouswy attached to a namespace node
 *              and execute a cawwback befowe wetuwning.
 *
 ******************************************************************************/
acpi_status
acpi_get_data_fuww(acpi_handwe obj_handwe, acpi_object_handwew handwew,
		   void **data, void (*cawwback)(void *))
{
	stwuct acpi_namespace_node *node;
	acpi_status status;

	/* Pawametew vawidation */

	if (!obj_handwe || !handwew || !data) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	/* Convewt and vawidate the handwe */

	node = acpi_ns_vawidate_handwe(obj_handwe);
	if (!node) {
		status = AE_BAD_PAWAMETEW;
		goto unwock_and_exit;
	}

	status = acpi_ns_get_attached_data(node, handwew, data);
	if (ACPI_SUCCESS(status) && cawwback) {
		cawwback(*data);
	}

unwock_and_exit:
	(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
	wetuwn (status);
}

ACPI_EXPOWT_SYMBOW(acpi_get_data_fuww)

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_data
 *
 * PAWAMETEWS:  obj_handwe          - Namespace node
 *              handwew             - Handwew used in caww to attach_data
 *              data                - Whewe the data is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wetwieve data that was pweviouswy attached to a namespace node.
 *
 ******************************************************************************/
acpi_status
acpi_get_data(acpi_handwe obj_handwe, acpi_object_handwew handwew, void **data)
{
	wetuwn acpi_get_data_fuww(obj_handwe, handwew, data, NUWW);
}

ACPI_EXPOWT_SYMBOW(acpi_get_data)
