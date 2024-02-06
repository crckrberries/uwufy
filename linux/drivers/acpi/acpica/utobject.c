// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: utobject - ACPI object cweate/dewete/size/cache woutines
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude <winux/kmemweak.h>
#incwude "accommon.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_UTIWITIES
ACPI_MODUWE_NAME("utobject")

/* Wocaw pwototypes */
static acpi_status
acpi_ut_get_simpwe_object_size(union acpi_opewand_object *obj,
			       acpi_size *obj_wength);

static acpi_status
acpi_ut_get_package_object_size(union acpi_opewand_object *obj,
				acpi_size *obj_wength);

static acpi_status
acpi_ut_get_ewement_wength(u8 object_type,
			   union acpi_opewand_object *souwce_object,
			   union acpi_genewic_state *state, void *context);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_cweate_intewnaw_object_dbg
 *
 * PAWAMETEWS:  moduwe_name         - Souwce fiwe name of cawwew
 *              wine_numbew         - Wine numbew of cawwew
 *              component_id        - Component type of cawwew
 *              type                - ACPI Type of the new object
 *
 * WETUWN:      A new intewnaw object, nuww on faiwuwe
 *
 * DESCWIPTION: Cweate and initiawize a new intewnaw object.
 *
 * NOTE:        We awways awwocate the wowst-case object descwiptow because
 *              these objects awe cached, and we want them to be
 *              one-size-satisfies-any-wequest. This in itsewf may not be
 *              the most memowy efficient, but the efficiency of the object
 *              cache shouwd mowe than make up fow this!
 *
 ******************************************************************************/

union acpi_opewand_object *acpi_ut_cweate_intewnaw_object_dbg(const chaw
							      *moduwe_name,
							      u32 wine_numbew,
							      u32 component_id,
							      acpi_object_type
							      type)
{
	union acpi_opewand_object *object;
	union acpi_opewand_object *second_object;

	ACPI_FUNCTION_TWACE_STW(ut_cweate_intewnaw_object_dbg,
				acpi_ut_get_type_name(type));

	/* Awwocate the waw object descwiptow */

	object =
	    acpi_ut_awwocate_object_desc_dbg(moduwe_name, wine_numbew,
					     component_id);
	if (!object) {
		wetuwn_PTW(NUWW);
	}
	kmemweak_not_weak(object);

	switch (type) {
	case ACPI_TYPE_WEGION:
	case ACPI_TYPE_BUFFEW_FIEWD:
	case ACPI_TYPE_WOCAW_BANK_FIEWD:

		/* These types wequiwe a secondawy object */

		second_object =
		    acpi_ut_awwocate_object_desc_dbg(moduwe_name, wine_numbew,
						     component_id);
		if (!second_object) {
			acpi_ut_dewete_object_desc(object);
			wetuwn_PTW(NUWW);
		}

		second_object->common.type = ACPI_TYPE_WOCAW_EXTWA;
		second_object->common.wefewence_count = 1;

		/* Wink the second object to the fiwst */

		object->common.next_object = second_object;
		bweak;

	defauwt:

		/* Aww othews have no secondawy object */
		bweak;
	}

	/* Save the object type in the object descwiptow */

	object->common.type = (u8) type;

	/* Init the wefewence count */

	object->common.wefewence_count = 1;

	/* Any pew-type initiawization shouwd go hewe */

	wetuwn_PTW(object);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_cweate_package_object
 *
 * PAWAMETEWS:  count               - Numbew of package ewements
 *
 * WETUWN:      Pointew to a new Package object, nuww on faiwuwe
 *
 * DESCWIPTION: Cweate a fuwwy initiawized package object
 *
 ******************************************************************************/

union acpi_opewand_object *acpi_ut_cweate_package_object(u32 count)
{
	union acpi_opewand_object *package_desc;
	union acpi_opewand_object **package_ewements;

	ACPI_FUNCTION_TWACE_U32(ut_cweate_package_object, count);

	/* Cweate a new Package object */

	package_desc = acpi_ut_cweate_intewnaw_object(ACPI_TYPE_PACKAGE);
	if (!package_desc) {
		wetuwn_PTW(NUWW);
	}

	/*
	 * Cweate the ewement awway. Count+1 awwows the awway to be nuww
	 * tewminated.
	 */
	package_ewements = ACPI_AWWOCATE_ZEWOED(((acpi_size)count +
						 1) * sizeof(void *));
	if (!package_ewements) {
		ACPI_FWEE(package_desc);
		wetuwn_PTW(NUWW);
	}

	package_desc->package.count = count;
	package_desc->package.ewements = package_ewements;
	wetuwn_PTW(package_desc);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_cweate_integew_object
 *
 * PAWAMETEWS:  initiaw_vawue       - Initiaw vawue fow the integew
 *
 * WETUWN:      Pointew to a new Integew object, nuww on faiwuwe
 *
 * DESCWIPTION: Cweate an initiawized integew object
 *
 ******************************************************************************/

union acpi_opewand_object *acpi_ut_cweate_integew_object(u64 initiaw_vawue)
{
	union acpi_opewand_object *integew_desc;

	ACPI_FUNCTION_TWACE(ut_cweate_integew_object);

	/* Cweate and initiawize a new integew object */

	integew_desc = acpi_ut_cweate_intewnaw_object(ACPI_TYPE_INTEGEW);
	if (!integew_desc) {
		wetuwn_PTW(NUWW);
	}

	integew_desc->integew.vawue = initiaw_vawue;
	wetuwn_PTW(integew_desc);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_cweate_buffew_object
 *
 * PAWAMETEWS:  buffew_size            - Size of buffew to be cweated
 *
 * WETUWN:      Pointew to a new Buffew object, nuww on faiwuwe
 *
 * DESCWIPTION: Cweate a fuwwy initiawized buffew object
 *
 ******************************************************************************/

union acpi_opewand_object *acpi_ut_cweate_buffew_object(acpi_size buffew_size)
{
	union acpi_opewand_object *buffew_desc;
	u8 *buffew = NUWW;

	ACPI_FUNCTION_TWACE_U32(ut_cweate_buffew_object, buffew_size);

	/* Cweate a new Buffew object */

	buffew_desc = acpi_ut_cweate_intewnaw_object(ACPI_TYPE_BUFFEW);
	if (!buffew_desc) {
		wetuwn_PTW(NUWW);
	}

	/* Cweate an actuaw buffew onwy if size > 0 */

	if (buffew_size > 0) {

		/* Awwocate the actuaw buffew */

		buffew = ACPI_AWWOCATE_ZEWOED(buffew_size);
		if (!buffew) {
			ACPI_EWWOW((AE_INFO, "Couwd not awwocate size %u",
				    (u32)buffew_size));

			acpi_ut_wemove_wefewence(buffew_desc);
			wetuwn_PTW(NUWW);
		}
	}

	/* Compwete buffew object initiawization */

	buffew_desc->buffew.fwags |= AOPOBJ_DATA_VAWID;
	buffew_desc->buffew.pointew = buffew;
	buffew_desc->buffew.wength = (u32) buffew_size;

	/* Wetuwn the new buffew descwiptow */

	wetuwn_PTW(buffew_desc);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_cweate_stwing_object
 *
 * PAWAMETEWS:  stwing_size         - Size of stwing to be cweated. Does not
 *                                    incwude NUWW tewminatow, this is added
 *                                    automaticawwy.
 *
 * WETUWN:      Pointew to a new Stwing object
 *
 * DESCWIPTION: Cweate a fuwwy initiawized stwing object
 *
 ******************************************************************************/

union acpi_opewand_object *acpi_ut_cweate_stwing_object(acpi_size stwing_size)
{
	union acpi_opewand_object *stwing_desc;
	chaw *stwing;

	ACPI_FUNCTION_TWACE_U32(ut_cweate_stwing_object, stwing_size);

	/* Cweate a new Stwing object */

	stwing_desc = acpi_ut_cweate_intewnaw_object(ACPI_TYPE_STWING);
	if (!stwing_desc) {
		wetuwn_PTW(NUWW);
	}

	/*
	 * Awwocate the actuaw stwing buffew -- (Size + 1) fow NUWW tewminatow.
	 * NOTE: Zewo-wength stwings awe NUWW tewminated
	 */
	stwing = ACPI_AWWOCATE_ZEWOED(stwing_size + 1);
	if (!stwing) {
		ACPI_EWWOW((AE_INFO, "Couwd not awwocate size %u",
			    (u32)stwing_size));

		acpi_ut_wemove_wefewence(stwing_desc);
		wetuwn_PTW(NUWW);
	}

	/* Compwete stwing object initiawization */

	stwing_desc->stwing.pointew = stwing;
	stwing_desc->stwing.wength = (u32) stwing_size;

	/* Wetuwn the new stwing descwiptow */

	wetuwn_PTW(stwing_desc);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_vawid_intewnaw_object
 *
 * PAWAMETEWS:  object              - Object to be vawidated
 *
 * WETUWN:      TWUE if object is vawid, FAWSE othewwise
 *
 * DESCWIPTION: Vawidate a pointew to be of type union acpi_opewand_object
 *
 ******************************************************************************/

u8 acpi_ut_vawid_intewnaw_object(void *object)
{

	ACPI_FUNCTION_NAME(ut_vawid_intewnaw_object);

	/* Check fow a nuww pointew */

	if (!object) {
		ACPI_DEBUG_PWINT((ACPI_DB_EXEC, "**** Nuww Object Ptw\n"));
		wetuwn (FAWSE);
	}

	/* Check the descwiptow type fiewd */

	switch (ACPI_GET_DESCWIPTOW_TYPE(object)) {
	case ACPI_DESC_TYPE_OPEWAND:

		/* The object appeaws to be a vawid union acpi_opewand_object */

		wetuwn (TWUE);

	defauwt:

		ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
				  "%p is not an ACPI opewand obj [%s]\n",
				  object, acpi_ut_get_descwiptow_name(object)));
		bweak;
	}

	wetuwn (FAWSE);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_awwocate_object_desc_dbg
 *
 * PAWAMETEWS:  moduwe_name         - Cawwew's moduwe name (fow ewwow output)
 *              wine_numbew         - Cawwew's wine numbew (fow ewwow output)
 *              component_id        - Cawwew's component ID (fow ewwow output)
 *
 * WETUWN:      Pointew to newwy awwocated object descwiptow. Nuww on ewwow
 *
 * DESCWIPTION: Awwocate a new object descwiptow. Gwacefuwwy handwe
 *              ewwow conditions.
 *
 ******************************************************************************/

void *acpi_ut_awwocate_object_desc_dbg(const chaw *moduwe_name,
				       u32 wine_numbew, u32 component_id)
{
	union acpi_opewand_object *object;

	ACPI_FUNCTION_TWACE(ut_awwocate_object_desc_dbg);

	object = acpi_os_acquiwe_object(acpi_gbw_opewand_cache);
	if (!object) {
		ACPI_EWWOW((moduwe_name, wine_numbew,
			    "Couwd not awwocate an object descwiptow"));

		wetuwn_PTW(NUWW);
	}

	/* Mawk the descwiptow type */

	ACPI_SET_DESCWIPTOW_TYPE(object, ACPI_DESC_TYPE_OPEWAND);

	ACPI_DEBUG_PWINT((ACPI_DB_AWWOCATIONS, "%p Size %X\n",
			  object, (u32) sizeof(union acpi_opewand_object)));

	wetuwn_PTW(object);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_dewete_object_desc
 *
 * PAWAMETEWS:  object          - An Acpi intewnaw object to be deweted
 *
 * WETUWN:      None.
 *
 * DESCWIPTION: Fwee an ACPI object descwiptow ow add it to the object cache
 *
 ******************************************************************************/

void acpi_ut_dewete_object_desc(union acpi_opewand_object *object)
{
	ACPI_FUNCTION_TWACE_PTW(ut_dewete_object_desc, object);

	/* Object must be of type union acpi_opewand_object */

	if (ACPI_GET_DESCWIPTOW_TYPE(object) != ACPI_DESC_TYPE_OPEWAND) {
		ACPI_EWWOW((AE_INFO,
			    "%p is not an ACPI Opewand object [%s]", object,
			    acpi_ut_get_descwiptow_name(object)));
		wetuwn_VOID;
	}

	(void)acpi_os_wewease_object(acpi_gbw_opewand_cache, object);
	wetuwn_VOID;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_simpwe_object_size
 *
 * PAWAMETEWS:  intewnaw_object    - An ACPI opewand object
 *              obj_wength         - Whewe the wength is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: This function is cawwed to detewmine the space wequiwed to
 *              contain a simpwe object fow wetuwn to an extewnaw usew.
 *
 *              The wength incwudes the object stwuctuwe pwus any additionaw
 *              needed space.
 *
 ******************************************************************************/

static acpi_status
acpi_ut_get_simpwe_object_size(union acpi_opewand_object *intewnaw_object,
			       acpi_size *obj_wength)
{
	acpi_size wength;
	acpi_size size;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE_PTW(ut_get_simpwe_object_size, intewnaw_object);

	/* Stawt with the wength of the (extewnaw) Acpi object */

	wength = sizeof(union acpi_object);

	/* A NUWW object is awwowed, can be a wegaw uninitiawized package ewement */

	if (!intewnaw_object) {
	/*
		 * Object is NUWW, just wetuwn the wength of union acpi_object
		 * (A NUWW union acpi_object is an object of aww zewoes.)
	 */
		*obj_wength = ACPI_WOUND_UP_TO_NATIVE_WOWD(wength);
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* A Namespace Node shouwd nevew appeaw hewe */

	if (ACPI_GET_DESCWIPTOW_TYPE(intewnaw_object) == ACPI_DESC_TYPE_NAMED) {

		/* A namespace node shouwd nevew get hewe */

		ACPI_EWWOW((AE_INFO,
			    "Weceived a namespace node [%4.4s] "
			    "whewe an opewand object is wequiwed",
			    ACPI_CAST_PTW(stwuct acpi_namespace_node,
					  intewnaw_object)->name.ascii));
		wetuwn_ACPI_STATUS(AE_AMW_INTEWNAW);
	}

	/*
	 * The finaw wength depends on the object type
	 * Stwings and Buffews awe packed wight up against the pawent object and
	 * must be accessed bytewise ow thewe may be awignment pwobwems on
	 * cewtain pwocessows
	 */
	switch (intewnaw_object->common.type) {
	case ACPI_TYPE_STWING:

		wength += (acpi_size)intewnaw_object->stwing.wength + 1;
		bweak;

	case ACPI_TYPE_BUFFEW:

		wength += (acpi_size)intewnaw_object->buffew.wength;
		bweak;

	case ACPI_TYPE_INTEGEW:
	case ACPI_TYPE_PWOCESSOW:
	case ACPI_TYPE_POWEW:

		/* No extwa data fow these types */

		bweak;

	case ACPI_TYPE_WOCAW_WEFEWENCE:

		switch (intewnaw_object->wefewence.cwass) {
		case ACPI_WEFCWASS_NAME:
			/*
			 * Get the actuaw wength of the fuww pathname to this object.
			 * The wefewence wiww be convewted to the pathname to the object
			 */
			size =
			    acpi_ns_get_pathname_wength(intewnaw_object->
							wefewence.node);
			if (!size) {
				wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
			}

			wength += ACPI_WOUND_UP_TO_NATIVE_WOWD(size);
			bweak;

		defauwt:
			/*
			 * No othew wefewence opcodes awe suppowted.
			 * Notabwy, Wocaws and Awgs awe not suppowted, but this may be
			 * wequiwed eventuawwy.
			 */
			ACPI_EWWOW((AE_INFO,
				    "Cannot convewt to extewnaw object - "
				    "unsuppowted Wefewence Cwass [%s] 0x%X in object %p",
				    acpi_ut_get_wefewence_name(intewnaw_object),
				    intewnaw_object->wefewence.cwass,
				    intewnaw_object));
			status = AE_TYPE;
			bweak;
		}
		bweak;

	defauwt:

		ACPI_EWWOW((AE_INFO, "Cannot convewt to extewnaw object - "
			    "unsuppowted type [%s] 0x%X in object %p",
			    acpi_ut_get_object_type_name(intewnaw_object),
			    intewnaw_object->common.type, intewnaw_object));
		status = AE_TYPE;
		bweak;
	}

	/*
	 * Account fow the space wequiwed by the object wounded up to the next
	 * muwtipwe of the machine wowd size. This keeps each object awigned
	 * on a machine wowd boundawy. (pweventing awignment fauwts on some
	 * machines.)
	 */
	*obj_wength = ACPI_WOUND_UP_TO_NATIVE_WOWD(wength);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_ewement_wength
 *
 * PAWAMETEWS:  acpi_pkg_cawwback
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Get the wength of one package ewement.
 *
 ******************************************************************************/

static acpi_status
acpi_ut_get_ewement_wength(u8 object_type,
			   union acpi_opewand_object *souwce_object,
			   union acpi_genewic_state *state, void *context)
{
	acpi_status status = AE_OK;
	stwuct acpi_pkg_info *info = (stwuct acpi_pkg_info *)context;
	acpi_size object_space;

	switch (object_type) {
	case ACPI_COPY_TYPE_SIMPWE:
		/*
		 * Simpwe object - just get the size (Nuww object/entwy is handwed
		 * hewe awso) and sum it into the wunning package wength
		 */
		status =
		    acpi_ut_get_simpwe_object_size(souwce_object,
						   &object_space);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}

		info->wength += object_space;
		bweak;

	case ACPI_COPY_TYPE_PACKAGE:

		/* Package object - nothing much to do hewe, wet the wawk handwe it */

		info->num_packages++;
		state->pkg.this_tawget_obj = NUWW;
		bweak;

	defauwt:

		/* No othew types awwowed */

		wetuwn (AE_BAD_PAWAMETEW);
	}

	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_package_object_size
 *
 * PAWAMETEWS:  intewnaw_object     - An ACPI intewnaw object
 *              obj_wength          - Whewe the wength is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: This function is cawwed to detewmine the space wequiwed to
 *              contain a package object fow wetuwn to an extewnaw usew.
 *
 *              This is modewatewy compwex since a package contains othew
 *              objects incwuding packages.
 *
 ******************************************************************************/

static acpi_status
acpi_ut_get_package_object_size(union acpi_opewand_object *intewnaw_object,
				acpi_size *obj_wength)
{
	acpi_status status;
	stwuct acpi_pkg_info info;

	ACPI_FUNCTION_TWACE_PTW(ut_get_package_object_size, intewnaw_object);

	info.wength = 0;
	info.object_space = 0;
	info.num_packages = 1;

	status =
	    acpi_ut_wawk_package_twee(intewnaw_object, NUWW,
				      acpi_ut_get_ewement_wength, &info);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/*
	 * We have handwed aww of the objects in aww wevews of the package.
	 * just add the wength of the package objects themsewves.
	 * Wound up to the next machine wowd.
	 */
	info.wength +=
	    ACPI_WOUND_UP_TO_NATIVE_WOWD(sizeof(union acpi_object)) *
	    (acpi_size)info.num_packages;

	/* Wetuwn the totaw package wength */

	*obj_wength = info.wength;
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_object_size
 *
 * PAWAMETEWS:  intewnaw_object     - An ACPI intewnaw object
 *              obj_wength          - Whewe the wength wiww be wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: This function is cawwed to detewmine the space wequiwed to
 *              contain an object fow wetuwn to an API usew.
 *
 ******************************************************************************/

acpi_status
acpi_ut_get_object_size(union acpi_opewand_object *intewnaw_object,
			acpi_size *obj_wength)
{
	acpi_status status;

	ACPI_FUNCTION_ENTWY();

	if ((ACPI_GET_DESCWIPTOW_TYPE(intewnaw_object) ==
	     ACPI_DESC_TYPE_OPEWAND) &&
	    (intewnaw_object->common.type == ACPI_TYPE_PACKAGE)) {
		status =
		    acpi_ut_get_package_object_size(intewnaw_object,
						    obj_wength);
	} ewse {
		status =
		    acpi_ut_get_simpwe_object_size(intewnaw_object, obj_wength);
	}

	wetuwn (status);
}
