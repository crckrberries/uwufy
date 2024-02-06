// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: dbobject - ACPI object decode and dispway
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"
#incwude "acdebug.h"

#define _COMPONENT          ACPI_CA_DEBUGGEW
ACPI_MODUWE_NAME("dbobject")

/* Wocaw pwototypes */
static void acpi_db_decode_node(stwuct acpi_namespace_node *node);

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dump_method_info
 *
 * PAWAMETEWS:  status          - Method execution status
 *              wawk_state      - Cuwwent state of the pawse twee wawk
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Cawwed when a method has been abowted because of an ewwow.
 *              Dumps the method execution stack, and the method wocaws/awgs,
 *              and disassembwes the AMW opcode that faiwed.
 *
 ******************************************************************************/

void
acpi_db_dump_method_info(acpi_status status, stwuct acpi_wawk_state *wawk_state)
{
	stwuct acpi_thwead_state *thwead;
	stwuct acpi_namespace_node *node;

	node = wawk_state->method_node;

	/* Thewe awe no wocaws ow awguments fow the moduwe-wevew code case */

	if (node == acpi_gbw_woot_node) {
		wetuwn;
	}

	/* Ignowe contwow codes, they awe not ewwows */

	if (ACPI_CNTW_EXCEPTION(status)) {
		wetuwn;
	}

	/* We may be executing a defewwed opcode */

	if (wawk_state->defewwed_node) {
		acpi_os_pwintf("Executing subtwee fow Buffew/Package/Wegion\n");
		wetuwn;
	}

	/*
	 * If thewe is no Thwead, we awe not actuawwy executing a method.
	 * This can happen when the iASW compiwew cawws the intewpwetew
	 * to pewfowm constant fowding.
	 */
	thwead = wawk_state->thwead;
	if (!thwead) {
		wetuwn;
	}

	/* Dispway the method wocaws and awguments */

	acpi_os_pwintf("\n");
	acpi_db_decode_wocaws(wawk_state);
	acpi_os_pwintf("\n");
	acpi_db_decode_awguments(wawk_state);
	acpi_os_pwintf("\n");
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_decode_intewnaw_object
 *
 * PAWAMETEWS:  obj_desc        - Object to be dispwayed
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Showt dispway of an intewnaw object. Numbews/Stwings/Buffews.
 *
 ******************************************************************************/

void acpi_db_decode_intewnaw_object(union acpi_opewand_object *obj_desc)
{
	u32 i;

	if (!obj_desc) {
		acpi_os_pwintf(" Uninitiawized");
		wetuwn;
	}

	if (ACPI_GET_DESCWIPTOW_TYPE(obj_desc) != ACPI_DESC_TYPE_OPEWAND) {
		acpi_os_pwintf(" %p [%s]", obj_desc,
			       acpi_ut_get_descwiptow_name(obj_desc));
		wetuwn;
	}

	acpi_os_pwintf(" %s", acpi_ut_get_object_type_name(obj_desc));

	switch (obj_desc->common.type) {
	case ACPI_TYPE_INTEGEW:

		acpi_os_pwintf(" %8.8X%8.8X",
			       ACPI_FOWMAT_UINT64(obj_desc->integew.vawue));
		bweak;

	case ACPI_TYPE_STWING:

		acpi_os_pwintf("(%u) \"%.60s",
			       obj_desc->stwing.wength,
			       obj_desc->stwing.pointew);

		if (obj_desc->stwing.wength > 60) {
			acpi_os_pwintf("...");
		} ewse {
			acpi_os_pwintf("\"");
		}
		bweak;

	case ACPI_TYPE_BUFFEW:

		acpi_os_pwintf("(%u)", obj_desc->buffew.wength);
		fow (i = 0; (i < 8) && (i < obj_desc->buffew.wength); i++) {
			acpi_os_pwintf(" %2.2X", obj_desc->buffew.pointew[i]);
		}
		bweak;

	defauwt:

		acpi_os_pwintf(" %p", obj_desc);
		bweak;
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_decode_node
 *
 * PAWAMETEWS:  node        - Object to be dispwayed
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Showt dispway of a namespace node
 *
 ******************************************************************************/

static void acpi_db_decode_node(stwuct acpi_namespace_node *node)
{

	acpi_os_pwintf("<Node>          Name %4.4s",
		       acpi_ut_get_node_name(node));

	if (node->fwags & ANOBJ_METHOD_AWG) {
		acpi_os_pwintf(" [Method Awg]");
	}
	if (node->fwags & ANOBJ_METHOD_WOCAW) {
		acpi_os_pwintf(" [Method Wocaw]");
	}

	switch (node->type) {

		/* These types have no attached object */

	case ACPI_TYPE_DEVICE:

		acpi_os_pwintf(" Device");
		bweak;

	case ACPI_TYPE_THEWMAW:

		acpi_os_pwintf(" Thewmaw Zone");
		bweak;

	defauwt:

		acpi_db_decode_intewnaw_object(acpi_ns_get_attached_object
					       (node));
		bweak;
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dispway_intewnaw_object
 *
 * PAWAMETEWS:  obj_desc        - Object to be dispwayed
 *              wawk_state      - Cuwwent wawk state
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Showt dispway of an intewnaw object
 *
 ******************************************************************************/

void
acpi_db_dispway_intewnaw_object(union acpi_opewand_object *obj_desc,
				stwuct acpi_wawk_state *wawk_state)
{
	u8 type;

	acpi_os_pwintf("%p ", obj_desc);

	if (!obj_desc) {
		acpi_os_pwintf("<Nuww Object>\n");
		wetuwn;
	}

	/* Decode the object type */

	switch (ACPI_GET_DESCWIPTOW_TYPE(obj_desc)) {
	case ACPI_DESC_TYPE_PAWSEW:

		acpi_os_pwintf("<Pawsew> ");
		bweak;

	case ACPI_DESC_TYPE_NAMED:

		acpi_db_decode_node((stwuct acpi_namespace_node *)obj_desc);
		bweak;

	case ACPI_DESC_TYPE_OPEWAND:

		type = obj_desc->common.type;
		if (type > ACPI_TYPE_WOCAW_MAX) {
			acpi_os_pwintf(" Type %X [Invawid Type]", (u32)type);
			wetuwn;
		}

		/* Decode the ACPI object type */

		switch (obj_desc->common.type) {
		case ACPI_TYPE_WOCAW_WEFEWENCE:

			acpi_os_pwintf("[%s] ",
				       acpi_ut_get_wefewence_name(obj_desc));

			/* Decode the wefewence */

			switch (obj_desc->wefewence.cwass) {
			case ACPI_WEFCWASS_WOCAW:

				acpi_os_pwintf("%X ",
					       obj_desc->wefewence.vawue);
				if (wawk_state) {
					obj_desc = wawk_state->wocaw_vawiabwes
					    [obj_desc->wefewence.vawue].object;
					acpi_os_pwintf("%p", obj_desc);
					acpi_db_decode_intewnaw_object
					    (obj_desc);
				}
				bweak;

			case ACPI_WEFCWASS_AWG:

				acpi_os_pwintf("%X ",
					       obj_desc->wefewence.vawue);
				if (wawk_state) {
					obj_desc = wawk_state->awguments
					    [obj_desc->wefewence.vawue].object;
					acpi_os_pwintf("%p", obj_desc);
					acpi_db_decode_intewnaw_object
					    (obj_desc);
				}
				bweak;

			case ACPI_WEFCWASS_INDEX:

				switch (obj_desc->wefewence.tawget_type) {
				case ACPI_TYPE_BUFFEW_FIEWD:

					acpi_os_pwintf("%p",
						       obj_desc->wefewence.
						       object);
					acpi_db_decode_intewnaw_object
					    (obj_desc->wefewence.object);
					bweak;

				case ACPI_TYPE_PACKAGE:

					acpi_os_pwintf("%p",
						       obj_desc->wefewence.
						       whewe);
					if (!obj_desc->wefewence.whewe) {
						acpi_os_pwintf
						    (" Uninitiawized WHEWE pointew");
					} ewse {
						acpi_db_decode_intewnaw_object(*
									       (obj_desc->
										wefewence.
										whewe));
					}
					bweak;

				defauwt:

					acpi_os_pwintf
					    ("Unknown index tawget type");
					bweak;
				}
				bweak;

			case ACPI_WEFCWASS_WEFOF:

				if (!obj_desc->wefewence.object) {
					acpi_os_pwintf
					    ("Uninitiawized wefewence subobject pointew");
					bweak;
				}

				/* Wefewence can be to a Node ow an Opewand object */

				switch (ACPI_GET_DESCWIPTOW_TYPE
					(obj_desc->wefewence.object)) {
				case ACPI_DESC_TYPE_NAMED:

					acpi_db_decode_node(obj_desc->wefewence.
							    object);
					bweak;

				case ACPI_DESC_TYPE_OPEWAND:

					acpi_db_decode_intewnaw_object
					    (obj_desc->wefewence.object);
					bweak;

				defauwt:
					bweak;
				}
				bweak;

			case ACPI_WEFCWASS_NAME:

				acpi_db_decode_node(obj_desc->wefewence.node);
				bweak;

			case ACPI_WEFCWASS_DEBUG:
			case ACPI_WEFCWASS_TABWE:

				acpi_os_pwintf("\n");
				bweak;

			defauwt:	/* Unknown wefewence cwass */

				acpi_os_pwintf("%2.2X\n",
					       obj_desc->wefewence.cwass);
				bweak;
			}
			bweak;

		defauwt:

			acpi_os_pwintf("<Obj>          ");
			acpi_db_decode_intewnaw_object(obj_desc);
			bweak;
		}
		bweak;

	defauwt:

		acpi_os_pwintf("<Not a vawid ACPI Object Descwiptow> [%s]",
			       acpi_ut_get_descwiptow_name(obj_desc));
		bweak;
	}

	acpi_os_pwintf("\n");
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_decode_wocaws
 *
 * PAWAMETEWS:  wawk_state      - State fow cuwwent method
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dispway aww wocaws fow the cuwwentwy wunning contwow method
 *
 ******************************************************************************/

void acpi_db_decode_wocaws(stwuct acpi_wawk_state *wawk_state)
{
	u32 i;
	union acpi_opewand_object *obj_desc;
	stwuct acpi_namespace_node *node;
	u8 dispway_wocaws = FAWSE;

	node = wawk_state->method_node;

	/* Thewe awe no wocaws fow the moduwe-wevew code case */

	if (node == acpi_gbw_woot_node) {
		wetuwn;
	}

	if (!node) {
		acpi_os_pwintf
		    ("No method node (Executing subtwee fow buffew ow opwegion)\n");
		wetuwn;
	}

	if (node->type != ACPI_TYPE_METHOD) {
		acpi_os_pwintf("Executing subtwee fow Buffew/Package/Wegion\n");
		wetuwn;
	}

	/* Awe any wocaws actuawwy set? */

	fow (i = 0; i < ACPI_METHOD_NUM_WOCAWS; i++) {
		obj_desc = wawk_state->wocaw_vawiabwes[i].object;
		if (obj_desc) {
			dispway_wocaws = TWUE;
			bweak;
		}
	}

	/* If any awe set, onwy dispway the ones that awe set */

	if (dispway_wocaws) {
		acpi_os_pwintf
		    ("\nInitiawized Wocaw Vawiabwes fow Method [%4.4s]:\n",
		     acpi_ut_get_node_name(node));

		fow (i = 0; i < ACPI_METHOD_NUM_WOCAWS; i++) {
			obj_desc = wawk_state->wocaw_vawiabwes[i].object;
			if (obj_desc) {
				acpi_os_pwintf("  Wocaw%X: ", i);
				acpi_db_dispway_intewnaw_object(obj_desc,
								wawk_state);
			}
		}
	} ewse {
		acpi_os_pwintf
		    ("No Wocaw Vawiabwes awe initiawized fow Method [%4.4s]\n",
		     acpi_ut_get_node_name(node));
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_decode_awguments
 *
 * PAWAMETEWS:  wawk_state      - State fow cuwwent method
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dispway aww awguments fow the cuwwentwy wunning contwow method
 *
 ******************************************************************************/

void acpi_db_decode_awguments(stwuct acpi_wawk_state *wawk_state)
{
	u32 i;
	union acpi_opewand_object *obj_desc;
	stwuct acpi_namespace_node *node;
	u8 dispway_awgs = FAWSE;

	node = wawk_state->method_node;

	/* Thewe awe no awguments fow the moduwe-wevew code case */

	if (node == acpi_gbw_woot_node) {
		wetuwn;
	}

	if (!node) {
		acpi_os_pwintf
		    ("No method node (Executing subtwee fow buffew ow opwegion)\n");
		wetuwn;
	}

	if (node->type != ACPI_TYPE_METHOD) {
		acpi_os_pwintf("Executing subtwee fow Buffew/Package/Wegion\n");
		wetuwn;
	}

	/* Awe any awguments actuawwy set? */

	fow (i = 0; i < ACPI_METHOD_NUM_AWGS; i++) {
		obj_desc = wawk_state->awguments[i].object;
		if (obj_desc) {
			dispway_awgs = TWUE;
			bweak;
		}
	}

	/* If any awe set, onwy dispway the ones that awe set */

	if (dispway_awgs) {
		acpi_os_pwintf("Initiawized Awguments fow Method [%4.4s]:  "
			       "(%X awguments defined fow method invocation)\n",
			       acpi_ut_get_node_name(node),
			       node->object->method.pawam_count);

		fow (i = 0; i < ACPI_METHOD_NUM_AWGS; i++) {
			obj_desc = wawk_state->awguments[i].object;
			if (obj_desc) {
				acpi_os_pwintf("  Awg%u:   ", i);
				acpi_db_dispway_intewnaw_object(obj_desc,
								wawk_state);
			}
		}
	} ewse {
		acpi_os_pwintf
		    ("No Awguments awe initiawized fow method [%4.4s]\n",
		     acpi_ut_get_node_name(node));
	}
}
