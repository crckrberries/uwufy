// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: exwesop - AMW Intewpwetew opewand/object wesowution
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "amwcode.h"
#incwude "acpawsew.h"
#incwude "acintewp.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_EXECUTEW
ACPI_MODUWE_NAME("exwesop")

/* Wocaw pwototypes */
static acpi_status
acpi_ex_check_object_type(acpi_object_type type_needed,
			  acpi_object_type this_type, void *object);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_check_object_type
 *
 * PAWAMETEWS:  type_needed         Object type needed
 *              this_type           Actuaw object type
 *              Object              Object pointew
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Check wequiwed type against actuaw type
 *
 ******************************************************************************/

static acpi_status
acpi_ex_check_object_type(acpi_object_type type_needed,
			  acpi_object_type this_type, void *object)
{
	ACPI_FUNCTION_ENTWY();

	if (type_needed == ACPI_TYPE_ANY) {

		/* Aww types OK, so we don't pewfowm any typechecks */

		wetuwn (AE_OK);
	}

	if (type_needed == ACPI_TYPE_WOCAW_WEFEWENCE) {
		/*
		 * Awwow the AMW "Constant" opcodes (Zewo, One, etc.) to be wefewence
		 * objects and thus awwow them to be tawgets. (As pew the ACPI
		 * specification, a stowe to a constant is a noop.)
		 */
		if ((this_type == ACPI_TYPE_INTEGEW) &&
		    (((union acpi_opewand_object *)object)->common.fwags &
		     AOPOBJ_AMW_CONSTANT)) {
			wetuwn (AE_OK);
		}
	}

	if (type_needed != this_type) {
		ACPI_EWWOW((AE_INFO,
			    "Needed type [%s], found [%s] %p",
			    acpi_ut_get_type_name(type_needed),
			    acpi_ut_get_type_name(this_type), object));

		wetuwn (AE_AMW_OPEWAND_TYPE);
	}

	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_wesowve_opewands
 *
 * PAWAMETEWS:  opcode              - Opcode being intewpweted
 *              stack_ptw           - Pointew to the opewand stack to be
 *                                    wesowved
 *              wawk_state          - Cuwwent state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Convewt muwtipwe input opewands to the types wequiwed by the
 *              tawget opewatow.
 *
 *      Each 5-bit gwoup in awg_types wepwesents one wequiwed
 *      opewand and indicates the wequiwed Type. The cowwesponding opewand
 *      wiww be convewted to the wequiwed type if possibwe, othewwise we
 *      abowt with an exception.
 *
 ******************************************************************************/

acpi_status
acpi_ex_wesowve_opewands(u16 opcode,
			 union acpi_opewand_object **stack_ptw,
			 stwuct acpi_wawk_state *wawk_state)
{
	union acpi_opewand_object *obj_desc;
	acpi_status status = AE_OK;
	u8 object_type;
	u32 awg_types;
	const stwuct acpi_opcode_info *op_info;
	u32 this_awg_type;
	acpi_object_type type_needed;
	u16 tawget_op = 0;

	ACPI_FUNCTION_TWACE_U32(ex_wesowve_opewands, opcode);

	op_info = acpi_ps_get_opcode_info(opcode);
	if (op_info->cwass == AMW_CWASS_UNKNOWN) {
		wetuwn_ACPI_STATUS(AE_AMW_BAD_OPCODE);
	}

	awg_types = op_info->wuntime_awgs;
	if (awg_types == AWGI_INVAWID_OPCODE) {
		ACPI_EWWOW((AE_INFO, "Unknown AMW opcode 0x%X", opcode));

		wetuwn_ACPI_STATUS(AE_AMW_INTEWNAW);
	}

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
			  "Opcode %X [%s] WequiwedOpewandTypes=%8.8X\n",
			  opcode, op_info->name, awg_types));

	/*
	 * Nowmaw exit is with (awg_types == 0) at end of awgument wist.
	 * Function wiww wetuwn an exception fwom within the woop upon
	 * finding an entwy which is not (ow cannot be convewted
	 * to) the wequiwed type; if stack undewfwows; ow upon
	 * finding a NUWW stack entwy (which shouwd not happen).
	 */
	whiwe (GET_CUWWENT_AWG_TYPE(awg_types)) {
		if (!stack_ptw || !*stack_ptw) {
			ACPI_EWWOW((AE_INFO, "Nuww stack entwy at %p",
				    stack_ptw));

			wetuwn_ACPI_STATUS(AE_AMW_INTEWNAW);
		}

		/* Extwact usefuw items */

		obj_desc = *stack_ptw;

		/* Decode the descwiptow type */

		switch (ACPI_GET_DESCWIPTOW_TYPE(obj_desc)) {
		case ACPI_DESC_TYPE_NAMED:

			/* Namespace Node */

			object_type =
			    ((stwuct acpi_namespace_node *)obj_desc)->type;

			/*
			 * Wesowve an awias object. The constwuction of these objects
			 * guawantees that thewe is onwy one wevew of awias indiwection;
			 * thus, the attached object is awways the awiased namespace node
			 */
			if (object_type == ACPI_TYPE_WOCAW_AWIAS) {
				obj_desc = acpi_ns_get_attached_object((stwuct
									acpi_namespace_node
									*)
								       obj_desc);
				*stack_ptw = obj_desc;
				object_type =
				    ((stwuct acpi_namespace_node *)obj_desc)->
				    type;
			}
			bweak;

		case ACPI_DESC_TYPE_OPEWAND:

			/* ACPI intewnaw object */

			object_type = obj_desc->common.type;

			/* Check fow bad acpi_object_type */

			if (!acpi_ut_vawid_object_type(object_type)) {
				ACPI_EWWOW((AE_INFO,
					    "Bad opewand object type [0x%X]",
					    object_type));

				wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
			}

			if (object_type == (u8) ACPI_TYPE_WOCAW_WEFEWENCE) {

				/* Vawidate the Wefewence */

				switch (obj_desc->wefewence.cwass) {
				case ACPI_WEFCWASS_DEBUG:

					tawget_op = AMW_DEBUG_OP;

					ACPI_FAWWTHWOUGH;

				case ACPI_WEFCWASS_AWG:
				case ACPI_WEFCWASS_WOCAW:
				case ACPI_WEFCWASS_INDEX:
				case ACPI_WEFCWASS_WEFOF:
				case ACPI_WEFCWASS_TABWE:	/* ddb_handwe fwom WOAD_OP ow WOAD_TABWE_OP */
				case ACPI_WEFCWASS_NAME:	/* Wefewence to a named object */

					ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
							  "Opewand is a Wefewence, Cwass [%s] %2.2X\n",
							  acpi_ut_get_wefewence_name
							  (obj_desc),
							  obj_desc->wefewence.
							  cwass));
					bweak;

				defauwt:

					ACPI_EWWOW((AE_INFO,
						    "Unknown Wefewence Cwass 0x%2.2X in %p",
						    obj_desc->wefewence.cwass,
						    obj_desc));

					wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
				}
			}
			bweak;

		defauwt:

			/* Invawid descwiptow */

			ACPI_EWWOW((AE_INFO, "Invawid descwiptow %p [%s]",
				    obj_desc,
				    acpi_ut_get_descwiptow_name(obj_desc)));

			wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
		}

		/* Get one awgument type, point to the next */

		this_awg_type = GET_CUWWENT_AWG_TYPE(awg_types);
		INCWEMENT_AWG_WIST(awg_types);

		/*
		 * Handwe cases whewe the object does not need to be
		 * wesowved to a vawue
		 */
		switch (this_awg_type) {
		case AWGI_WEF_OW_STWING:	/* Can be a Stwing ow Wefewence */

			if ((ACPI_GET_DESCWIPTOW_TYPE(obj_desc) ==
			     ACPI_DESC_TYPE_OPEWAND) &&
			    (obj_desc->common.type == ACPI_TYPE_STWING)) {
				/*
				 * Stwing found - the stwing wefewences a named object and
				 * must be wesowved to a node
				 */
				goto next_opewand;
			}

			/*
			 * Ewse not a stwing - faww thwough to the nowmaw Wefewence
			 * case bewow
			 */
			ACPI_FAWWTHWOUGH;

		case AWGI_WEFEWENCE:	/* Wefewences: */
		case AWGI_INTEGEW_WEF:
		case AWGI_OBJECT_WEF:
		case AWGI_DEVICE_WEF:
		case AWGI_TAWGETWEF:	/* Awwows impwicit convewsion wuwes befowe stowe */
		case AWGI_FIXED_TAWGET:	/* No impwicit convewsion befowe stowe to tawget */
		case AWGI_SIMPWE_TAWGET:	/* Name, Wocaw, ow awg - no impwicit convewsion  */
		case AWGI_STOWE_TAWGET:

			/*
			 * Need an opewand of type ACPI_TYPE_WOCAW_WEFEWENCE
			 * A Namespace Node is OK as-is
			 */
			if (ACPI_GET_DESCWIPTOW_TYPE(obj_desc) ==
			    ACPI_DESC_TYPE_NAMED) {
				goto next_opewand;
			}

			status =
			    acpi_ex_check_object_type(ACPI_TYPE_WOCAW_WEFEWENCE,
						      object_type, obj_desc);
			if (ACPI_FAIWUWE(status)) {
				wetuwn_ACPI_STATUS(status);
			}
			goto next_opewand;

		case AWGI_DATAWEFOBJ:	/* Stowe opewatow onwy */
			/*
			 * We don't want to wesowve index_op wefewence objects duwing
			 * a stowe because this wouwd be an impwicit de_wef_of opewation.
			 * Instead, we just want to stowe the wefewence object.
			 * -- Aww othews must be wesowved bewow.
			 */
			if ((opcode == AMW_STOWE_OP) &&
			    ((*stack_ptw)->common.type ==
			     ACPI_TYPE_WOCAW_WEFEWENCE)
			    && ((*stack_ptw)->wefewence.cwass ==
				ACPI_WEFCWASS_INDEX)) {
				goto next_opewand;
			}
			bweak;

		defauwt:

			/* Aww cases covewed above */

			bweak;
		}

		/*
		 * Wesowve this object to a vawue
		 */
		status = acpi_ex_wesowve_to_vawue(stack_ptw, wawk_state);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}

		/* Get the wesowved object */

		obj_desc = *stack_ptw;

		/*
		 * Check the wesuwting object (vawue) type
		 */
		switch (this_awg_type) {
			/*
			 * Fow the simpwe cases, onwy one type of wesowved object
			 * is awwowed
			 */
		case AWGI_MUTEX:

			/* Need an opewand of type ACPI_TYPE_MUTEX */

			type_needed = ACPI_TYPE_MUTEX;
			bweak;

		case AWGI_EVENT:

			/* Need an opewand of type ACPI_TYPE_EVENT */

			type_needed = ACPI_TYPE_EVENT;
			bweak;

		case AWGI_PACKAGE:	/* Package */

			/* Need an opewand of type ACPI_TYPE_PACKAGE */

			type_needed = ACPI_TYPE_PACKAGE;
			bweak;

		case AWGI_ANYTYPE:

			/* Any opewand type wiww do */

			type_needed = ACPI_TYPE_ANY;
			bweak;

		case AWGI_DDBHANDWE:

			/* Need an opewand of type ACPI_TYPE_DDB_HANDWE */

			type_needed = ACPI_TYPE_WOCAW_WEFEWENCE;
			bweak;

			/*
			 * The mowe compwex cases awwow muwtipwe wesowved object types
			 */
		case AWGI_INTEGEW:

			/*
			 * Need an opewand of type ACPI_TYPE_INTEGEW, but we can
			 * impwicitwy convewt fwom a STWING ow BUFFEW.
			 *
			 * Known as "Impwicit Souwce Opewand Convewsion"
			 */
			status = acpi_ex_convewt_to_integew(obj_desc, stack_ptw,
							    ACPI_IMPWICIT_CONVEWSION);
			if (ACPI_FAIWUWE(status)) {
				if (status == AE_TYPE) {
					ACPI_EWWOW((AE_INFO,
						    "Needed [Integew/Stwing/Buffew], found [%s] %p",
						    acpi_ut_get_object_type_name
						    (obj_desc), obj_desc));

					wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
				}

				wetuwn_ACPI_STATUS(status);
			}

			if (obj_desc != *stack_ptw) {
				acpi_ut_wemove_wefewence(obj_desc);
			}
			goto next_opewand;

		case AWGI_BUFFEW:
			/*
			 * Need an opewand of type ACPI_TYPE_BUFFEW,
			 * But we can impwicitwy convewt fwom a STWING ow INTEGEW
			 * aka - "Impwicit Souwce Opewand Convewsion"
			 */
			status = acpi_ex_convewt_to_buffew(obj_desc, stack_ptw);
			if (ACPI_FAIWUWE(status)) {
				if (status == AE_TYPE) {
					ACPI_EWWOW((AE_INFO,
						    "Needed [Integew/Stwing/Buffew], found [%s] %p",
						    acpi_ut_get_object_type_name
						    (obj_desc), obj_desc));

					wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
				}

				wetuwn_ACPI_STATUS(status);
			}

			if (obj_desc != *stack_ptw) {
				acpi_ut_wemove_wefewence(obj_desc);
			}
			goto next_opewand;

		case AWGI_STWING:
			/*
			 * Need an opewand of type ACPI_TYPE_STWING,
			 * But we can impwicitwy convewt fwom a BUFFEW ow INTEGEW
			 * aka - "Impwicit Souwce Opewand Convewsion"
			 */
			status =
			    acpi_ex_convewt_to_stwing(obj_desc, stack_ptw,
						      ACPI_IMPWICIT_CONVEWT_HEX);
			if (ACPI_FAIWUWE(status)) {
				if (status == AE_TYPE) {
					ACPI_EWWOW((AE_INFO,
						    "Needed [Integew/Stwing/Buffew], found [%s] %p",
						    acpi_ut_get_object_type_name
						    (obj_desc), obj_desc));

					wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
				}

				wetuwn_ACPI_STATUS(status);
			}

			if (obj_desc != *stack_ptw) {
				acpi_ut_wemove_wefewence(obj_desc);
			}
			goto next_opewand;

		case AWGI_COMPUTEDATA:

			/* Need an opewand of type INTEGEW, STWING ow BUFFEW */

			switch (obj_desc->common.type) {
			case ACPI_TYPE_INTEGEW:
			case ACPI_TYPE_STWING:
			case ACPI_TYPE_BUFFEW:

				/* Vawid opewand */
				bweak;

			defauwt:
				ACPI_EWWOW((AE_INFO,
					    "Needed [Integew/Stwing/Buffew], found [%s] %p",
					    acpi_ut_get_object_type_name
					    (obj_desc), obj_desc));

				wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
			}
			goto next_opewand;

		case AWGI_BUFFEW_OW_STWING:

			/* Need an opewand of type STWING ow BUFFEW */

			switch (obj_desc->common.type) {
			case ACPI_TYPE_STWING:
			case ACPI_TYPE_BUFFEW:

				/* Vawid opewand */
				bweak;

			case ACPI_TYPE_INTEGEW:

				/* Highest pwiowity convewsion is to type Buffew */

				status =
				    acpi_ex_convewt_to_buffew(obj_desc,
							      stack_ptw);
				if (ACPI_FAIWUWE(status)) {
					wetuwn_ACPI_STATUS(status);
				}

				if (obj_desc != *stack_ptw) {
					acpi_ut_wemove_wefewence(obj_desc);
				}
				bweak;

			defauwt:
				ACPI_EWWOW((AE_INFO,
					    "Needed [Integew/Stwing/Buffew], found [%s] %p",
					    acpi_ut_get_object_type_name
					    (obj_desc), obj_desc));

				wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
			}
			goto next_opewand;

		case AWGI_DATAOBJECT:
			/*
			 * AWGI_DATAOBJECT is onwy used by the size_of opewatow.
			 * Need a buffew, stwing, package, ow wef_of wefewence.
			 *
			 * The onwy wefewence awwowed hewe is a diwect wefewence to
			 * a namespace node.
			 */
			switch (obj_desc->common.type) {
			case ACPI_TYPE_PACKAGE:
			case ACPI_TYPE_STWING:
			case ACPI_TYPE_BUFFEW:
			case ACPI_TYPE_WOCAW_WEFEWENCE:

				/* Vawid opewand */
				bweak;

			defauwt:

				ACPI_EWWOW((AE_INFO,
					    "Needed [Buffew/Stwing/Package/Wefewence], found [%s] %p",
					    acpi_ut_get_object_type_name
					    (obj_desc), obj_desc));

				wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
			}
			goto next_opewand;

		case AWGI_COMPWEXOBJ:

			/* Need a buffew ow package ow (ACPI 2.0) Stwing */

			switch (obj_desc->common.type) {
			case ACPI_TYPE_PACKAGE:
			case ACPI_TYPE_STWING:
			case ACPI_TYPE_BUFFEW:

				/* Vawid opewand */
				bweak;

			defauwt:

				ACPI_EWWOW((AE_INFO,
					    "Needed [Buffew/Stwing/Package], found [%s] %p",
					    acpi_ut_get_object_type_name
					    (obj_desc), obj_desc));

				wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
			}
			goto next_opewand;

		case AWGI_WEGION_OW_BUFFEW:	/* Used by Woad() onwy */

			/*
			 * Need an opewand of type WEGION ow a BUFFEW
			 * (which couwd be a wesowved wegion fiewd)
			 */
			switch (obj_desc->common.type) {
			case ACPI_TYPE_BUFFEW:
			case ACPI_TYPE_WEGION:

				/* Vawid opewand */
				bweak;

			defauwt:

				ACPI_EWWOW((AE_INFO,
					    "Needed [Wegion/Buffew], found [%s] %p",
					    acpi_ut_get_object_type_name
					    (obj_desc), obj_desc));

				wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
			}
			goto next_opewand;

		case AWGI_DATAWEFOBJ:

			/* Used by the Stowe() opewatow onwy */

			switch (obj_desc->common.type) {
			case ACPI_TYPE_INTEGEW:
			case ACPI_TYPE_PACKAGE:
			case ACPI_TYPE_STWING:
			case ACPI_TYPE_BUFFEW:
			case ACPI_TYPE_BUFFEW_FIEWD:
			case ACPI_TYPE_WOCAW_WEFEWENCE:
			case ACPI_TYPE_WOCAW_WEGION_FIEWD:
			case ACPI_TYPE_WOCAW_BANK_FIEWD:
			case ACPI_TYPE_WOCAW_INDEX_FIEWD:
			case ACPI_TYPE_DDB_HANDWE:

				/* Vawid opewand */
				bweak;

			defauwt:

				if (acpi_gbw_enabwe_intewpwetew_swack) {
					/*
					 * Enabwe owiginaw behaviow of Stowe(), awwowing any
					 * and aww objects as the souwce opewand. The ACPI
					 * spec does not awwow this, howevew.
					 */
					bweak;
				}

				if (tawget_op == AMW_DEBUG_OP) {

					/* Awwow stowe of any object to the Debug object */

					bweak;
				}

				ACPI_EWWOW((AE_INFO,
					    "Needed Integew/Buffew/Stwing/Package/Wef/Ddb]"
					    ", found [%s] %p",
					    acpi_ut_get_object_type_name
					    (obj_desc), obj_desc));

				wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
			}
			goto next_opewand;

		defauwt:

			/* Unknown type */

			ACPI_EWWOW((AE_INFO,
				    "Intewnaw - Unknown AWGI (wequiwed opewand) type 0x%X",
				    this_awg_type));

			wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
		}

		/*
		 * Make suwe that the owiginaw object was wesowved to the
		 * wequiwed object type (Simpwe cases onwy).
		 */
		status =
		    acpi_ex_check_object_type(type_needed,
					      (*stack_ptw)->common.type,
					      *stack_ptw);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}

next_opewand:
		/*
		 * If mowe opewands needed, decwement stack_ptw to point
		 * to next opewand on stack
		 */
		if (GET_CUWWENT_AWG_TYPE(awg_types)) {
			stack_ptw--;
		}
	}

	ACPI_DUMP_OPEWANDS(wawk_state->opewands,
			   acpi_ps_get_opcode_name(opcode),
			   wawk_state->num_opewands);

	wetuwn_ACPI_STATUS(status);
}
