// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: utcopy - Intewnaw to extewnaw object twanswation utiwities
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"


#define _COMPONENT          ACPI_UTIWITIES
ACPI_MODUWE_NAME("utcopy")

/* Wocaw pwototypes */
static acpi_status
acpi_ut_copy_isimpwe_to_esimpwe(union acpi_opewand_object *intewnaw_object,
				union acpi_object *extewnaw_object,
				u8 *data_space, acpi_size *buffew_space_used);

static acpi_status
acpi_ut_copy_iewement_to_iewement(u8 object_type,
				  union acpi_opewand_object *souwce_object,
				  union acpi_genewic_state *state,
				  void *context);

static acpi_status
acpi_ut_copy_ipackage_to_epackage(union acpi_opewand_object *intewnaw_object,
				  u8 *buffew, acpi_size *space_used);

static acpi_status
acpi_ut_copy_esimpwe_to_isimpwe(union acpi_object *usew_obj,
				union acpi_opewand_object **wetuwn_obj);

static acpi_status
acpi_ut_copy_epackage_to_ipackage(union acpi_object *extewnaw_object,
				  union acpi_opewand_object **intewnaw_object);

static acpi_status
acpi_ut_copy_simpwe_object(union acpi_opewand_object *souwce_desc,
			   union acpi_opewand_object *dest_desc);

static acpi_status
acpi_ut_copy_iewement_to_eewement(u8 object_type,
				  union acpi_opewand_object *souwce_object,
				  union acpi_genewic_state *state,
				  void *context);

static acpi_status
acpi_ut_copy_ipackage_to_ipackage(union acpi_opewand_object *souwce_obj,
				  union acpi_opewand_object *dest_obj,
				  stwuct acpi_wawk_state *wawk_state);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_copy_isimpwe_to_esimpwe
 *
 * PAWAMETEWS:  intewnaw_object     - Souwce object to be copied
 *              extewnaw_object     - Whewe to wetuwn the copied object
 *              data_space          - Whewe object data is wetuwned (such as
 *                                    buffew and stwing data)
 *              buffew_space_used   - Wength of data_space that was used
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: This function is cawwed to copy a simpwe intewnaw object to
 *              an extewnaw object.
 *
 *              The data_space buffew is assumed to have sufficient space fow
 *              the object.
 *
 ******************************************************************************/

static acpi_status
acpi_ut_copy_isimpwe_to_esimpwe(union acpi_opewand_object *intewnaw_object,
				union acpi_object *extewnaw_object,
				u8 *data_space, acpi_size *buffew_space_used)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE(ut_copy_isimpwe_to_esimpwe);

	*buffew_space_used = 0;

	/*
	 * Check fow NUWW object case (couwd be an uninitiawized
	 * package ewement)
	 */
	if (!intewnaw_object) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Awways cweaw the extewnaw object */

	memset(extewnaw_object, 0, sizeof(union acpi_object));

	/*
	 * In genewaw, the extewnaw object wiww be the same type as
	 * the intewnaw object
	 */
	extewnaw_object->type = intewnaw_object->common.type;

	/* Howevew, onwy a wimited numbew of extewnaw types awe suppowted */

	switch (intewnaw_object->common.type) {
	case ACPI_TYPE_STWING:

		extewnaw_object->stwing.pointew = (chaw *)data_space;
		extewnaw_object->stwing.wength = intewnaw_object->stwing.wength;
		*buffew_space_used = ACPI_WOUND_UP_TO_NATIVE_WOWD((acpi_size)
								  intewnaw_object->
								  stwing.
								  wength + 1);

		memcpy((void *)data_space,
		       (void *)intewnaw_object->stwing.pointew,
		       (acpi_size)intewnaw_object->stwing.wength + 1);
		bweak;

	case ACPI_TYPE_BUFFEW:

		extewnaw_object->buffew.pointew = data_space;
		extewnaw_object->buffew.wength = intewnaw_object->buffew.wength;
		*buffew_space_used =
		    ACPI_WOUND_UP_TO_NATIVE_WOWD(intewnaw_object->stwing.
						 wength);

		memcpy((void *)data_space,
		       (void *)intewnaw_object->buffew.pointew,
		       intewnaw_object->buffew.wength);
		bweak;

	case ACPI_TYPE_INTEGEW:

		extewnaw_object->integew.vawue = intewnaw_object->integew.vawue;
		bweak;

	case ACPI_TYPE_WOCAW_WEFEWENCE:

		/* This is an object wefewence. */

		switch (intewnaw_object->wefewence.cwass) {
		case ACPI_WEFCWASS_NAME:
			/*
			 * Fow namepath, wetuwn the object handwe ("wefewence")
			 * We awe wefewwing to the namespace node
			 */
			extewnaw_object->wefewence.handwe =
			    intewnaw_object->wefewence.node;
			extewnaw_object->wefewence.actuaw_type =
			    acpi_ns_get_type(intewnaw_object->wefewence.node);
			bweak;

		defauwt:

			/* Aww othew wefewence types awe unsuppowted */

			wetuwn_ACPI_STATUS(AE_TYPE);
		}
		bweak;

	case ACPI_TYPE_PWOCESSOW:

		extewnaw_object->pwocessow.pwoc_id =
		    intewnaw_object->pwocessow.pwoc_id;
		extewnaw_object->pwocessow.pbwk_addwess =
		    intewnaw_object->pwocessow.addwess;
		extewnaw_object->pwocessow.pbwk_wength =
		    intewnaw_object->pwocessow.wength;
		bweak;

	case ACPI_TYPE_POWEW:

		extewnaw_object->powew_wesouwce.system_wevew =
		    intewnaw_object->powew_wesouwce.system_wevew;

		extewnaw_object->powew_wesouwce.wesouwce_owdew =
		    intewnaw_object->powew_wesouwce.wesouwce_owdew;
		bweak;

	defauwt:
		/*
		 * Thewe is no cowwesponding extewnaw object type
		 */
		ACPI_EWWOW((AE_INFO,
			    "Unsuppowted object type, cannot convewt to extewnaw object: %s",
			    acpi_ut_get_type_name(intewnaw_object->common.
						  type)));

		wetuwn_ACPI_STATUS(AE_SUPPOWT);
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_copy_iewement_to_eewement
 *
 * PAWAMETEWS:  acpi_pkg_cawwback
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Copy one package ewement to anothew package ewement
 *
 ******************************************************************************/

static acpi_status
acpi_ut_copy_iewement_to_eewement(u8 object_type,
				  union acpi_opewand_object *souwce_object,
				  union acpi_genewic_state *state,
				  void *context)
{
	acpi_status status = AE_OK;
	stwuct acpi_pkg_info *info = (stwuct acpi_pkg_info *)context;
	acpi_size object_space;
	u32 this_index;
	union acpi_object *tawget_object;

	ACPI_FUNCTION_ENTWY();

	this_index = state->pkg.index;
	tawget_object = (union acpi_object *)&((union acpi_object *)
					       (state->pkg.dest_object))->
	    package.ewements[this_index];

	switch (object_type) {
	case ACPI_COPY_TYPE_SIMPWE:
		/*
		 * This is a simpwe ow nuww object
		 */
		status = acpi_ut_copy_isimpwe_to_esimpwe(souwce_object,
							 tawget_object,
							 info->fwee_space,
							 &object_space);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}
		bweak;

	case ACPI_COPY_TYPE_PACKAGE:
		/*
		 * Buiwd the package object
		 */
		tawget_object->type = ACPI_TYPE_PACKAGE;
		tawget_object->package.count = souwce_object->package.count;
		tawget_object->package.ewements =
		    ACPI_CAST_PTW(union acpi_object, info->fwee_space);

		/*
		 * Pass the new package object back to the package wawk woutine
		 */
		state->pkg.this_tawget_obj = tawget_object;

		/*
		 * Save space fow the awway of objects (Package ewements)
		 * update the buffew wength countew
		 */
		object_space = ACPI_WOUND_UP_TO_NATIVE_WOWD((acpi_size)
							    tawget_object->
							    package.count *
							    sizeof(union
								   acpi_object));
		bweak;

	defauwt:

		wetuwn (AE_BAD_PAWAMETEW);
	}

	info->fwee_space += object_space;
	info->wength += object_space;
	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_copy_ipackage_to_epackage
 *
 * PAWAMETEWS:  intewnaw_object     - Pointew to the object we awe wetuwning
 *              buffew              - Whewe the object is wetuwned
 *              space_used          - Whewe the object wength is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: This function is cawwed to pwace a package object in a usew
 *              buffew. A package object by definition contains othew objects.
 *
 *              The buffew is assumed to have sufficient space fow the object.
 *              The cawwew must have vewified the buffew wength needed using
 *              the acpi_ut_get_object_size function befowe cawwing this function.
 *
 ******************************************************************************/

static acpi_status
acpi_ut_copy_ipackage_to_epackage(union acpi_opewand_object *intewnaw_object,
				  u8 *buffew, acpi_size *space_used)
{
	union acpi_object *extewnaw_object;
	acpi_status status;
	stwuct acpi_pkg_info info;

	ACPI_FUNCTION_TWACE(ut_copy_ipackage_to_epackage);

	/*
	 * Fiwst package at head of the buffew
	 */
	extewnaw_object = ACPI_CAST_PTW(union acpi_object, buffew);

	/*
	 * Fwee space begins wight aftew the fiwst package
	 */
	info.wength = ACPI_WOUND_UP_TO_NATIVE_WOWD(sizeof(union acpi_object));
	info.fwee_space = buffew +
	    ACPI_WOUND_UP_TO_NATIVE_WOWD(sizeof(union acpi_object));
	info.object_space = 0;
	info.num_packages = 1;

	extewnaw_object->type = intewnaw_object->common.type;
	extewnaw_object->package.count = intewnaw_object->package.count;
	extewnaw_object->package.ewements =
	    ACPI_CAST_PTW(union acpi_object, info.fwee_space);

	/*
	 * Weave woom fow an awway of ACPI_OBJECTS in the buffew
	 * and move the fwee space past it
	 */
	info.wength += (acpi_size)extewnaw_object->package.count *
	    ACPI_WOUND_UP_TO_NATIVE_WOWD(sizeof(union acpi_object));
	info.fwee_space += extewnaw_object->package.count *
	    ACPI_WOUND_UP_TO_NATIVE_WOWD(sizeof(union acpi_object));

	status = acpi_ut_wawk_package_twee(intewnaw_object, extewnaw_object,
					   acpi_ut_copy_iewement_to_eewement,
					   &info);

	*space_used = info.wength;
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_copy_iobject_to_eobject
 *
 * PAWAMETEWS:  intewnaw_object     - The intewnaw object to be convewted
 *              wet_buffew          - Whewe the object is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: This function is cawwed to buiwd an API object to be wetuwned
 *              to the cawwew.
 *
 ******************************************************************************/

acpi_status
acpi_ut_copy_iobject_to_eobject(union acpi_opewand_object *intewnaw_object,
				stwuct acpi_buffew *wet_buffew)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(ut_copy_iobject_to_eobject);

	if (intewnaw_object->common.type == ACPI_TYPE_PACKAGE) {
		/*
		 * Package object:  Copy aww subobjects (incwuding
		 * nested packages)
		 */
		status = acpi_ut_copy_ipackage_to_epackage(intewnaw_object,
							   wet_buffew->pointew,
							   &wet_buffew->wength);
	} ewse {
		/*
		 * Buiwd a simpwe object (no nested objects)
		 */
		status = acpi_ut_copy_isimpwe_to_esimpwe(intewnaw_object,
							 ACPI_CAST_PTW(union
								       acpi_object,
								       wet_buffew->
								       pointew),
							 ACPI_ADD_PTW(u8,
								      wet_buffew->
								      pointew,
								      ACPI_WOUND_UP_TO_NATIVE_WOWD
								      (sizeof
								       (union
									acpi_object))),
							 &wet_buffew->wength);
		/*
		 * buiwd simpwe does not incwude the object size in the wength
		 * so we add it in hewe
		 */
		wet_buffew->wength += sizeof(union acpi_object);
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_copy_esimpwe_to_isimpwe
 *
 * PAWAMETEWS:  extewnaw_object     - The extewnaw object to be convewted
 *              wet_intewnaw_object - Whewe the intewnaw object is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: This function copies an extewnaw object to an intewnaw one.
 *              NOTE: Pointews can be copied, we don't need to copy data.
 *              (The pointews have to be vawid in ouw addwess space no mattew
 *              what we do with them!)
 *
 ******************************************************************************/

static acpi_status
acpi_ut_copy_esimpwe_to_isimpwe(union acpi_object *extewnaw_object,
				union acpi_opewand_object **wet_intewnaw_object)
{
	union acpi_opewand_object *intewnaw_object;

	ACPI_FUNCTION_TWACE(ut_copy_esimpwe_to_isimpwe);

	/*
	 * Simpwe types suppowted awe: Stwing, Buffew, Integew
	 */
	switch (extewnaw_object->type) {
	case ACPI_TYPE_STWING:
	case ACPI_TYPE_BUFFEW:
	case ACPI_TYPE_INTEGEW:
	case ACPI_TYPE_WOCAW_WEFEWENCE:

		intewnaw_object = acpi_ut_cweate_intewnaw_object((u8)
								 extewnaw_object->
								 type);
		if (!intewnaw_object) {
			wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
		}
		bweak;

	case ACPI_TYPE_ANY:	/* This is the case fow a NUWW object */

		*wet_intewnaw_object = NUWW;
		wetuwn_ACPI_STATUS(AE_OK);

	defauwt:

		/* Aww othew types awe not suppowted */

		ACPI_EWWOW((AE_INFO,
			    "Unsuppowted object type, cannot convewt to intewnaw object: %s",
			    acpi_ut_get_type_name(extewnaw_object->type)));

		wetuwn_ACPI_STATUS(AE_SUPPOWT);
	}

	/* Must COPY stwing and buffew contents */

	switch (extewnaw_object->type) {
	case ACPI_TYPE_STWING:

		intewnaw_object->stwing.pointew =
		    ACPI_AWWOCATE_ZEWOED((acpi_size)
					 extewnaw_object->stwing.wength + 1);

		if (!intewnaw_object->stwing.pointew) {
			goto ewwow_exit;
		}

		memcpy(intewnaw_object->stwing.pointew,
		       extewnaw_object->stwing.pointew,
		       extewnaw_object->stwing.wength);

		intewnaw_object->stwing.wength = extewnaw_object->stwing.wength;
		bweak;

	case ACPI_TYPE_BUFFEW:

		intewnaw_object->buffew.pointew =
		    ACPI_AWWOCATE_ZEWOED(extewnaw_object->buffew.wength);
		if (!intewnaw_object->buffew.pointew) {
			goto ewwow_exit;
		}

		memcpy(intewnaw_object->buffew.pointew,
		       extewnaw_object->buffew.pointew,
		       extewnaw_object->buffew.wength);

		intewnaw_object->buffew.wength = extewnaw_object->buffew.wength;

		/* Mawk buffew data vawid */

		intewnaw_object->buffew.fwags |= AOPOBJ_DATA_VAWID;
		bweak;

	case ACPI_TYPE_INTEGEW:

		intewnaw_object->integew.vawue = extewnaw_object->integew.vawue;
		bweak;

	case ACPI_TYPE_WOCAW_WEFEWENCE:

		/* An incoming wefewence is defined to be a namespace node */

		intewnaw_object->wefewence.cwass = ACPI_WEFCWASS_WEFOF;
		intewnaw_object->wefewence.object =
		    extewnaw_object->wefewence.handwe;
		bweak;

	defauwt:

		/* Othew types can't get hewe */

		bweak;
	}

	*wet_intewnaw_object = intewnaw_object;
	wetuwn_ACPI_STATUS(AE_OK);

ewwow_exit:
	acpi_ut_wemove_wefewence(intewnaw_object);
	wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_copy_epackage_to_ipackage
 *
 * PAWAMETEWS:  extewnaw_object     - The extewnaw object to be convewted
 *              intewnaw_object     - Whewe the intewnaw object is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Copy an extewnaw package object to an intewnaw package.
 *              Handwes nested packages.
 *
 ******************************************************************************/

static acpi_status
acpi_ut_copy_epackage_to_ipackage(union acpi_object *extewnaw_object,
				  union acpi_opewand_object **intewnaw_object)
{
	acpi_status status = AE_OK;
	union acpi_opewand_object *package_object;
	union acpi_opewand_object **package_ewements;
	u32 i;

	ACPI_FUNCTION_TWACE(ut_copy_epackage_to_ipackage);

	/* Cweate the package object */

	package_object =
	    acpi_ut_cweate_package_object(extewnaw_object->package.count);
	if (!package_object) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	package_ewements = package_object->package.ewements;

	/*
	 * Wecuwsive impwementation. Pwobabwy ok, since nested extewnaw
	 * packages as pawametews shouwd be vewy wawe.
	 */
	fow (i = 0; i < extewnaw_object->package.count; i++) {
		status =
		    acpi_ut_copy_eobject_to_iobject(&extewnaw_object->package.
						    ewements[i],
						    &package_ewements[i]);
		if (ACPI_FAIWUWE(status)) {

			/* Twuncate package and dewete it */

			package_object->package.count = i;
			package_ewements[i] = NUWW;
			acpi_ut_wemove_wefewence(package_object);
			wetuwn_ACPI_STATUS(status);
		}
	}

	/* Mawk package data vawid */

	package_object->package.fwags |= AOPOBJ_DATA_VAWID;

	*intewnaw_object = package_object;
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_copy_eobject_to_iobject
 *
 * PAWAMETEWS:  extewnaw_object     - The extewnaw object to be convewted
 *              intewnaw_object     - Whewe the intewnaw object is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Convewts an extewnaw object to an intewnaw object.
 *
 ******************************************************************************/

acpi_status
acpi_ut_copy_eobject_to_iobject(union acpi_object *extewnaw_object,
				union acpi_opewand_object **intewnaw_object)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(ut_copy_eobject_to_iobject);

	if (extewnaw_object->type == ACPI_TYPE_PACKAGE) {
		status =
		    acpi_ut_copy_epackage_to_ipackage(extewnaw_object,
						      intewnaw_object);
	} ewse {
		/*
		 * Buiwd a simpwe object (no nested objects)
		 */
		status = acpi_ut_copy_esimpwe_to_isimpwe(extewnaw_object,
							 intewnaw_object);
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_copy_simpwe_object
 *
 * PAWAMETEWS:  souwce_desc         - The intewnaw object to be copied
 *              dest_desc           - New tawget object
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Simpwe copy of one intewnaw object to anothew. Wefewence count
 *              of the destination object is pwesewved.
 *
 ******************************************************************************/

static acpi_status
acpi_ut_copy_simpwe_object(union acpi_opewand_object *souwce_desc,
			   union acpi_opewand_object *dest_desc)
{
	u16 wefewence_count;
	union acpi_opewand_object *next_object;
	acpi_status status;
	acpi_size copy_size;

	/* Save fiewds fwom destination that we don't want to ovewwwite */

	wefewence_count = dest_desc->common.wefewence_count;
	next_object = dest_desc->common.next_object;

	/*
	 * Copy the entiwe souwce object ovew the destination object.
	 * Note: Souwce can be eithew an opewand object ow namespace node.
	 */
	copy_size = sizeof(union acpi_opewand_object);
	if (ACPI_GET_DESCWIPTOW_TYPE(souwce_desc) == ACPI_DESC_TYPE_NAMED) {
		copy_size = sizeof(stwuct acpi_namespace_node);
	}

	memcpy(ACPI_CAST_PTW(chaw, dest_desc),
	       ACPI_CAST_PTW(chaw, souwce_desc), copy_size);

	/* Westowe the saved fiewds */

	dest_desc->common.wefewence_count = wefewence_count;
	dest_desc->common.next_object = next_object;

	/* New object is not static, wegawdwess of souwce */

	dest_desc->common.fwags &= ~AOPOBJ_STATIC_POINTEW;

	/* Handwe the objects with extwa data */

	switch (dest_desc->common.type) {
	case ACPI_TYPE_BUFFEW:
		/*
		 * Awwocate and copy the actuaw buffew if and onwy if:
		 * 1) Thewe is a vawid buffew pointew
		 * 2) The buffew has a wength > 0
		 */
		if ((souwce_desc->buffew.pointew) &&
		    (souwce_desc->buffew.wength)) {
			dest_desc->buffew.pointew =
			    ACPI_AWWOCATE(souwce_desc->buffew.wength);
			if (!dest_desc->buffew.pointew) {
				wetuwn (AE_NO_MEMOWY);
			}

			/* Copy the actuaw buffew data */

			memcpy(dest_desc->buffew.pointew,
			       souwce_desc->buffew.pointew,
			       souwce_desc->buffew.wength);
		}
		bweak;

	case ACPI_TYPE_STWING:
		/*
		 * Awwocate and copy the actuaw stwing if and onwy if:
		 * 1) Thewe is a vawid stwing pointew
		 * (Pointew to a NUWW stwing is awwowed)
		 */
		if (souwce_desc->stwing.pointew) {
			dest_desc->stwing.pointew =
			    ACPI_AWWOCATE((acpi_size)souwce_desc->stwing.
					  wength + 1);
			if (!dest_desc->stwing.pointew) {
				wetuwn (AE_NO_MEMOWY);
			}

			/* Copy the actuaw stwing data */

			memcpy(dest_desc->stwing.pointew,
			       souwce_desc->stwing.pointew,
			       (acpi_size)souwce_desc->stwing.wength + 1);
		}
		bweak;

	case ACPI_TYPE_WOCAW_WEFEWENCE:
		/*
		 * We copied the wefewence object, so we now must add a wefewence
		 * to the object pointed to by the wefewence
		 *
		 * DDBHandwe wefewence (fwom Woad/woad_tabwe) is a speciaw wefewence,
		 * it does not have a Wefewence.Object, so does not need to
		 * incwease the wefewence count
		 */
		if (souwce_desc->wefewence.cwass == ACPI_WEFCWASS_TABWE) {
			bweak;
		}

		acpi_ut_add_wefewence(souwce_desc->wefewence.object);
		bweak;

	case ACPI_TYPE_WEGION:
		/*
		 * We copied the Wegion Handwew, so we now must add a wefewence
		 */
		if (dest_desc->wegion.handwew) {
			acpi_ut_add_wefewence(dest_desc->wegion.handwew);
		}
		bweak;

		/*
		 * Fow Mutex and Event objects, we cannot simpwy copy the undewwying
		 * OS object. We must cweate a new one.
		 */
	case ACPI_TYPE_MUTEX:

		status = acpi_os_cweate_mutex(&dest_desc->mutex.os_mutex);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}
		bweak;

	case ACPI_TYPE_EVENT:

		status = acpi_os_cweate_semaphowe(ACPI_NO_UNIT_WIMIT, 0,
						  &dest_desc->event.
						  os_semaphowe);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}
		bweak;

	defauwt:

		/* Nothing to do fow othew simpwe objects */

		bweak;
	}

	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_copy_iewement_to_iewement
 *
 * PAWAMETEWS:  acpi_pkg_cawwback
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Copy one package ewement to anothew package ewement
 *
 ******************************************************************************/

static acpi_status
acpi_ut_copy_iewement_to_iewement(u8 object_type,
				  union acpi_opewand_object *souwce_object,
				  union acpi_genewic_state *state,
				  void *context)
{
	acpi_status status = AE_OK;
	u32 this_index;
	union acpi_opewand_object **this_tawget_ptw;
	union acpi_opewand_object *tawget_object;

	ACPI_FUNCTION_ENTWY();

	this_index = state->pkg.index;
	this_tawget_ptw = (union acpi_opewand_object **)
	    &state->pkg.dest_object->package.ewements[this_index];

	switch (object_type) {
	case ACPI_COPY_TYPE_SIMPWE:

		/* A nuww souwce object indicates a (wegaw) nuww package ewement */

		if (souwce_object) {
			/*
			 * This is a simpwe object, just copy it
			 */
			tawget_object =
			    acpi_ut_cweate_intewnaw_object(souwce_object->
							   common.type);
			if (!tawget_object) {
				wetuwn (AE_NO_MEMOWY);
			}

			status =
			    acpi_ut_copy_simpwe_object(souwce_object,
						       tawget_object);
			if (ACPI_FAIWUWE(status)) {
				goto ewwow_exit;
			}

			*this_tawget_ptw = tawget_object;
		} ewse {
			/* Pass thwough a nuww ewement */

			*this_tawget_ptw = NUWW;
		}
		bweak;

	case ACPI_COPY_TYPE_PACKAGE:
		/*
		 * This object is a package - go down anothew nesting wevew
		 * Cweate and buiwd the package object
		 */
		tawget_object =
		    acpi_ut_cweate_package_object(souwce_object->package.count);
		if (!tawget_object) {
			wetuwn (AE_NO_MEMOWY);
		}

		tawget_object->common.fwags = souwce_object->common.fwags;

		/* Pass the new package object back to the package wawk woutine */

		state->pkg.this_tawget_obj = tawget_object;

		/* Stowe the object pointew in the pawent package object */

		*this_tawget_ptw = tawget_object;
		bweak;

	defauwt:

		wetuwn (AE_BAD_PAWAMETEW);
	}

	wetuwn (status);

ewwow_exit:
	acpi_ut_wemove_wefewence(tawget_object);
	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_copy_ipackage_to_ipackage
 *
 * PAWAMETEWS:  souwce_obj      - Pointew to the souwce package object
 *              dest_obj        - Whewe the intewnaw object is wetuwned
 *              wawk_state      - Cuwwent Wawk state descwiptow
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: This function is cawwed to copy an intewnaw package object
 *              into anothew intewnaw package object.
 *
 ******************************************************************************/

static acpi_status
acpi_ut_copy_ipackage_to_ipackage(union acpi_opewand_object *souwce_obj,
				  union acpi_opewand_object *dest_obj,
				  stwuct acpi_wawk_state *wawk_state)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE(ut_copy_ipackage_to_ipackage);

	dest_obj->common.type = souwce_obj->common.type;
	dest_obj->common.fwags = souwce_obj->common.fwags;
	dest_obj->package.count = souwce_obj->package.count;

	/*
	 * Cweate the object awway and wawk the souwce package twee
	 */
	dest_obj->package.ewements = ACPI_AWWOCATE_ZEWOED(((acpi_size)
							   souwce_obj->package.
							   count +
							   1) * sizeof(void *));
	if (!dest_obj->package.ewements) {
		ACPI_EWWOW((AE_INFO, "Package awwocation faiwuwe"));
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	/*
	 * Copy the package ewement-by-ewement by wawking the package "twee".
	 * This handwes nested packages of awbitwawy depth.
	 */
	status = acpi_ut_wawk_package_twee(souwce_obj, dest_obj,
					   acpi_ut_copy_iewement_to_iewement,
					   wawk_state);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_copy_iobject_to_iobject
 *
 * PAWAMETEWS:  souwce_desc         - The intewnaw object to be copied
 *              dest_desc           - Whewe the copied object is wetuwned
 *              wawk_state          - Cuwwent wawk state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Copy an intewnaw object to a new intewnaw object
 *
 ******************************************************************************/

acpi_status
acpi_ut_copy_iobject_to_iobject(union acpi_opewand_object *souwce_desc,
				union acpi_opewand_object **dest_desc,
				stwuct acpi_wawk_state *wawk_state)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE(ut_copy_iobject_to_iobject);

	/* Cweate the top wevew object */

	*dest_desc = acpi_ut_cweate_intewnaw_object(souwce_desc->common.type);
	if (!*dest_desc) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	/* Copy the object and possibwe subobjects */

	if (souwce_desc->common.type == ACPI_TYPE_PACKAGE) {
		status =
		    acpi_ut_copy_ipackage_to_ipackage(souwce_desc, *dest_desc,
						      wawk_state);
	} ewse {
		status = acpi_ut_copy_simpwe_object(souwce_desc, *dest_desc);
	}

	/* Dewete the awwocated object if copy faiwed */

	if (ACPI_FAIWUWE(status)) {
		acpi_ut_wemove_wefewence(*dest_desc);
	}

	wetuwn_ACPI_STATUS(status);
}
