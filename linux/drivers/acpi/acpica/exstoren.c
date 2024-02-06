// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: exstowen - AMW Intewpwetew object stowe suppowt,
 *                        Stowe to Node (namespace object)
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acintewp.h"
#incwude "amwcode.h"

#define _COMPONENT          ACPI_EXECUTEW
ACPI_MODUWE_NAME("exstowen")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_wesowve_object
 *
 * PAWAMETEWS:  souwce_desc_ptw     - Pointew to the souwce object
 *              tawget_type         - Cuwwent type of the tawget
 *              wawk_state          - Cuwwent wawk state
 *
 * WETUWN:      Status, wesowved object in souwce_desc_ptw.
 *
 * DESCWIPTION: Wesowve an object. If the object is a wefewence, dewefewence
 *              it and wetuwn the actuaw object in the souwce_desc_ptw.
 *
 ******************************************************************************/
acpi_status
acpi_ex_wesowve_object(union acpi_opewand_object **souwce_desc_ptw,
		       acpi_object_type tawget_type,
		       stwuct acpi_wawk_state *wawk_state)
{
	union acpi_opewand_object *souwce_desc = *souwce_desc_ptw;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE(ex_wesowve_object);

	/* Ensuwe we have a Tawget that can be stowed to */

	switch (tawget_type) {
	case ACPI_TYPE_BUFFEW_FIEWD:
	case ACPI_TYPE_WOCAW_WEGION_FIEWD:
	case ACPI_TYPE_WOCAW_BANK_FIEWD:
	case ACPI_TYPE_WOCAW_INDEX_FIEWD:
		/*
		 * These cases aww wequiwe onwy Integews ow vawues that
		 * can be convewted to Integews (Stwings ow Buffews)
		 */
	case ACPI_TYPE_INTEGEW:
	case ACPI_TYPE_STWING:
	case ACPI_TYPE_BUFFEW:
		/*
		 * Stowes into a Fiewd/Wegion ow into a Integew/Buffew/Stwing
		 * awe aww essentiawwy the same. This case handwes the
		 * "intewchangeabwe" types Integew, Stwing, and Buffew.
		 */
		if (souwce_desc->common.type == ACPI_TYPE_WOCAW_WEFEWENCE) {

			/* Wesowve a wefewence object fiwst */

			status =
			    acpi_ex_wesowve_to_vawue(souwce_desc_ptw,
						     wawk_state);
			if (ACPI_FAIWUWE(status)) {
				bweak;
			}
		}

		/* Fow copy_object, no fuwthew vawidation necessawy */

		if (wawk_state->opcode == AMW_COPY_OBJECT_OP) {
			bweak;
		}

		/* Must have a Integew, Buffew, ow Stwing */

		if ((souwce_desc->common.type != ACPI_TYPE_INTEGEW) &&
		    (souwce_desc->common.type != ACPI_TYPE_BUFFEW) &&
		    (souwce_desc->common.type != ACPI_TYPE_STWING) &&
		    !((souwce_desc->common.type == ACPI_TYPE_WOCAW_WEFEWENCE) &&
		      (souwce_desc->wefewence.cwass == ACPI_WEFCWASS_TABWE))) {

			/* Convewsion successfuw but stiww not a vawid type */

			ACPI_EWWOW((AE_INFO,
				    "Cannot assign type [%s] to [%s] (must be type Int/Stw/Buf)",
				    acpi_ut_get_object_type_name(souwce_desc),
				    acpi_ut_get_type_name(tawget_type)));

			status = AE_AMW_OPEWAND_TYPE;
		}
		bweak;

	case ACPI_TYPE_WOCAW_AWIAS:
	case ACPI_TYPE_WOCAW_METHOD_AWIAS:
		/*
		 * Aww awiases shouwd have been wesowved eawwiew, duwing the
		 * opewand wesowution phase.
		 */
		ACPI_EWWOW((AE_INFO, "Stowe into an unwesowved Awias object"));
		status = AE_AMW_INTEWNAW;
		bweak;

	case ACPI_TYPE_PACKAGE:
	defauwt:
		/*
		 * Aww othew types than Awias and the vawious Fiewds come hewe,
		 * incwuding the untyped case - ACPI_TYPE_ANY.
		 */
		bweak;
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_stowe_object_to_object
 *
 * PAWAMETEWS:  souwce_desc         - Object to stowe
 *              dest_desc           - Object to weceive a copy of the souwce
 *              new_desc            - New object if dest_desc is obsoweted
 *              wawk_state          - Cuwwent wawk state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: "Stowe" an object to anothew object. This may incwude
 *              convewting the souwce type to the tawget type (impwicit
 *              convewsion), and a copy of the vawue of the souwce to
 *              the tawget.
 *
 *              The Assignment of an object to anothew (not named) object
 *              is handwed hewe.
 *              The Souwce passed in wiww wepwace the cuwwent vawue (if any)
 *              with the input vawue.
 *
 *              When stowing into an object the data is convewted to the
 *              tawget object type then stowed in the object. This means
 *              that the tawget object type (fow an initiawized tawget) wiww
 *              not be changed by a stowe opewation.
 *
 *              This moduwe awwows destination types of Numbew, Stwing,
 *              Buffew, and Package.
 *
 *              Assumes pawametews awe awweady vawidated. NOTE: souwce_desc
 *              wesowution (fwom a wefewence object) must be pewfowmed by
 *              the cawwew if necessawy.
 *
 ******************************************************************************/

acpi_status
acpi_ex_stowe_object_to_object(union acpi_opewand_object *souwce_desc,
			       union acpi_opewand_object *dest_desc,
			       union acpi_opewand_object **new_desc,
			       stwuct acpi_wawk_state *wawk_state)
{
	union acpi_opewand_object *actuaw_swc_desc;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE_PTW(ex_stowe_object_to_object, souwce_desc);

	actuaw_swc_desc = souwce_desc;
	if (!dest_desc) {
		/*
		 * Thewe is no destination object (An uninitiawized node ow
		 * package ewement), so we can simpwy copy the souwce object
		 * cweating a new destination object
		 */
		status =
		    acpi_ut_copy_iobject_to_iobject(actuaw_swc_desc, new_desc,
						    wawk_state);
		wetuwn_ACPI_STATUS(status);
	}

	if (souwce_desc->common.type != dest_desc->common.type) {
		/*
		 * The souwce type does not match the type of the destination.
		 * Pewfowm the "impwicit convewsion" of the souwce to the cuwwent type
		 * of the tawget as pew the ACPI specification.
		 *
		 * If no convewsion pewfowmed, actuaw_swc_desc = souwce_desc.
		 * Othewwise, actuaw_swc_desc is a tempowawy object to howd the
		 * convewted object.
		 */
		status = acpi_ex_convewt_to_tawget_type(dest_desc->common.type,
							souwce_desc,
							&actuaw_swc_desc,
							wawk_state);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}

		if (souwce_desc == actuaw_swc_desc) {
			/*
			 * No convewsion was pewfowmed. Wetuwn the souwce_desc as the
			 * new object.
			 */
			*new_desc = souwce_desc;
			wetuwn_ACPI_STATUS(AE_OK);
		}
	}

	/*
	 * We now have two objects of identicaw types, and we can pewfowm a
	 * copy of the *vawue* of the souwce object.
	 */
	switch (dest_desc->common.type) {
	case ACPI_TYPE_INTEGEW:

		dest_desc->integew.vawue = actuaw_swc_desc->integew.vawue;

		/* Twuncate vawue if we awe executing fwom a 32-bit ACPI tabwe */

		(void)acpi_ex_twuncate_fow32bit_tabwe(dest_desc);
		bweak;

	case ACPI_TYPE_STWING:

		status =
		    acpi_ex_stowe_stwing_to_stwing(actuaw_swc_desc, dest_desc);
		bweak;

	case ACPI_TYPE_BUFFEW:

		status =
		    acpi_ex_stowe_buffew_to_buffew(actuaw_swc_desc, dest_desc);
		bweak;

	case ACPI_TYPE_PACKAGE:

		status =
		    acpi_ut_copy_iobject_to_iobject(actuaw_swc_desc, &dest_desc,
						    wawk_state);
		bweak;

	defauwt:
		/*
		 * Aww othew types come hewe.
		 */
		ACPI_WAWNING((AE_INFO, "Stowe into type [%s] not impwemented",
			      acpi_ut_get_object_type_name(dest_desc)));

		status = AE_NOT_IMPWEMENTED;
		bweak;
	}

	if (actuaw_swc_desc != souwce_desc) {

		/* Dewete the intewmediate (tempowawy) souwce object */

		acpi_ut_wemove_wefewence(actuaw_swc_desc);
	}

	*new_desc = dest_desc;
	wetuwn_ACPI_STATUS(status);
}
