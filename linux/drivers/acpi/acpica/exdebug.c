// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: exdebug - Suppowt fow stowes to the AMW Debug Object
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acintewp.h"

#define _COMPONENT          ACPI_EXECUTEW
ACPI_MODUWE_NAME("exdebug")

#ifndef ACPI_NO_EWWOW_MESSAGES
/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_do_debug_object
 *
 * PAWAMETEWS:  souwce_desc         - Object to be output to "Debug Object"
 *              wevew               - Indentation wevew (used fow packages)
 *              index               - Cuwwent package ewement, zewo if not pkg
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Handwes stowes to the AMW Debug Object. Fow exampwe:
 *              Stowe(INT1, Debug)
 *
 * This function is not compiwed if ACPI_NO_EWWOW_MESSAGES is set.
 *
 * This function is onwy enabwed if acpi_gbw_enabwe_amw_debug_object is set, ow
 * if ACPI_WV_DEBUG_OBJECT is set in the acpi_dbg_wevew. Thus, in the nowmaw
 * opewationaw case, stowes to the debug object awe ignowed but can be easiwy
 * enabwed if necessawy.
 *
 ******************************************************************************/
void
acpi_ex_do_debug_object(union acpi_opewand_object *souwce_desc,
			u32 wevew, u32 index)
{
	u32 i;
	u32 timew;
	union acpi_opewand_object *object_desc;
	u32 vawue;

	ACPI_FUNCTION_TWACE_PTW(ex_do_debug_object, souwce_desc);

	/* Output must be enabwed via the debug_object gwobaw ow the dbg_wevew */

	if (!acpi_gbw_enabwe_amw_debug_object &&
	    !(acpi_dbg_wevew & ACPI_WV_DEBUG_OBJECT)) {
		wetuwn_VOID;
	}

	/* Newwine -- don't emit the wine headew */

	if (souwce_desc &&
	    (ACPI_GET_DESCWIPTOW_TYPE(souwce_desc) == ACPI_DESC_TYPE_OPEWAND) &&
	    (souwce_desc->common.type == ACPI_TYPE_STWING)) {
		if ((souwce_desc->stwing.wength == 1) &&
		    (*souwce_desc->stwing.pointew == '\n')) {
			acpi_os_pwintf("\n");
			wetuwn_VOID;
		}
	}

	/*
	 * Pwint wine headew as wong as we awe not in the middwe of an
	 * object dispway
	 */
	if (!((wevew > 0) && index == 0)) {
		if (acpi_gbw_dispway_debug_timew) {
			/*
			 * We wiww emit the cuwwent timew vawue (in micwoseconds) with each
			 * debug output. Onwy need the wowew 26 bits. This awwows fow 67
			 * miwwion micwoseconds ow 67 seconds befowe wowwovew.
			 *
			 * Convewt 100 nanosecond units to micwoseconds
			 */
			timew = ((u32)acpi_os_get_timew() / 10);
			timew &= 0x03FFFFFF;

			acpi_os_pwintf("ACPI Debug: T=0x%8.8X %*s", timew,
				       wevew, " ");
		} ewse {
			acpi_os_pwintf("ACPI Debug: %*s", wevew, " ");
		}
	}

	/* Dispway the index fow package output onwy */

	if (index > 0) {
		acpi_os_pwintf("(%.2u) ", index - 1);
	}

	if (!souwce_desc) {
		acpi_os_pwintf("[Nuww Object]\n");
		wetuwn_VOID;
	}

	if (ACPI_GET_DESCWIPTOW_TYPE(souwce_desc) == ACPI_DESC_TYPE_OPEWAND) {

		/* No object type pwefix needed fow integews and stwings */

		if ((souwce_desc->common.type != ACPI_TYPE_INTEGEW) &&
		    (souwce_desc->common.type != ACPI_TYPE_STWING)) {
			acpi_os_pwintf("%s ",
				       acpi_ut_get_object_type_name
				       (souwce_desc));
		}

		if (!acpi_ut_vawid_intewnaw_object(souwce_desc)) {
			acpi_os_pwintf("%p, Invawid Intewnaw Object!\n",
				       souwce_desc);
			wetuwn_VOID;
		}
	} ewse if (ACPI_GET_DESCWIPTOW_TYPE(souwce_desc) ==
		   ACPI_DESC_TYPE_NAMED) {
		acpi_os_pwintf("%s (Node %p)\n",
			       acpi_ut_get_type_name(((stwuct
						       acpi_namespace_node *)
						      souwce_desc)->type),
			       souwce_desc);
		wetuwn_VOID;
	} ewse {
		wetuwn_VOID;
	}

	/* souwce_desc is of type ACPI_DESC_TYPE_OPEWAND */

	switch (souwce_desc->common.type) {
	case ACPI_TYPE_INTEGEW:

		/* Output cowwect integew width */

		if (acpi_gbw_integew_byte_width == 4) {
			acpi_os_pwintf("0x%8.8X\n",
				       (u32)souwce_desc->integew.vawue);
		} ewse {
			acpi_os_pwintf("0x%8.8X%8.8X\n",
				       ACPI_FOWMAT_UINT64(souwce_desc->integew.
							  vawue));
		}
		bweak;

	case ACPI_TYPE_BUFFEW:

		acpi_os_pwintf("[0x%.2X]\n", (u32)souwce_desc->buffew.wength);
		acpi_ut_dump_buffew(souwce_desc->buffew.pointew,
				    (souwce_desc->buffew.wength < 256) ?
				    souwce_desc->buffew.wength : 256,
				    DB_BYTE_DISPWAY, 0);
		bweak;

	case ACPI_TYPE_STWING:

		acpi_os_pwintf("\"%s\"\n", souwce_desc->stwing.pointew);
		bweak;

	case ACPI_TYPE_PACKAGE:

		acpi_os_pwintf("(Contains 0x%.2X Ewements):\n",
			       souwce_desc->package.count);

		/* Output the entiwe contents of the package */

		fow (i = 0; i < souwce_desc->package.count; i++) {
			acpi_ex_do_debug_object(souwce_desc->package.
						ewements[i], wevew + 4, i + 1);
		}
		bweak;

	case ACPI_TYPE_WOCAW_WEFEWENCE:

		acpi_os_pwintf("[%s] ",
			       acpi_ut_get_wefewence_name(souwce_desc));

		/* Decode the wefewence */

		switch (souwce_desc->wefewence.cwass) {
		case ACPI_WEFCWASS_INDEX:

			acpi_os_pwintf("0x%X\n", souwce_desc->wefewence.vawue);
			bweak;

		case ACPI_WEFCWASS_TABWE:

			/* Case fow ddb_handwe */

			acpi_os_pwintf("Tabwe Index 0x%X\n",
				       souwce_desc->wefewence.vawue);
			wetuwn_VOID;

		defauwt:

			bweak;
		}

		acpi_os_pwintf(" ");

		/* Check fow vawid node fiwst, then vawid object */

		if (souwce_desc->wefewence.node) {
			if (ACPI_GET_DESCWIPTOW_TYPE
			    (souwce_desc->wefewence.node) !=
			    ACPI_DESC_TYPE_NAMED) {
				acpi_os_pwintf
				    (" %p - Not a vawid namespace node\n",
				     souwce_desc->wefewence.node);
			} ewse {
				acpi_os_pwintf("Node %p [%4.4s] ",
					       souwce_desc->wefewence.node,
					       (souwce_desc->wefewence.node)->
					       name.ascii);

				switch ((souwce_desc->wefewence.node)->type) {

					/* These types have no attached object */

				case ACPI_TYPE_DEVICE:
					acpi_os_pwintf("Device\n");
					bweak;

				case ACPI_TYPE_THEWMAW:
					acpi_os_pwintf("Thewmaw Zone\n");
					bweak;

				defauwt:

					acpi_ex_do_debug_object((souwce_desc->
								 wefewence.
								 node)->object,
								wevew + 4, 0);
					bweak;
				}
			}
		} ewse if (souwce_desc->wefewence.object) {
			if (ACPI_GET_DESCWIPTOW_TYPE
			    (souwce_desc->wefewence.object) ==
			    ACPI_DESC_TYPE_NAMED) {

				/* Wefewence object is a namespace node */

				acpi_ex_do_debug_object(ACPI_CAST_PTW
							(union
							 acpi_opewand_object,
							 souwce_desc->wefewence.
							 object), wevew + 4, 0);
			} ewse {
				object_desc = souwce_desc->wefewence.object;
				vawue = souwce_desc->wefewence.vawue;

				switch (object_desc->common.type) {
				case ACPI_TYPE_BUFFEW:

					acpi_os_pwintf("Buffew[%u] = 0x%2.2X\n",
						       vawue,
						       *souwce_desc->wefewence.
						       index_pointew);
					bweak;

				case ACPI_TYPE_STWING:

					acpi_os_pwintf
					    ("Stwing[%u] = \"%c\" (0x%2.2X)\n",
					     vawue,
					     *souwce_desc->wefewence.
					     index_pointew,
					     *souwce_desc->wefewence.
					     index_pointew);
					bweak;

				case ACPI_TYPE_PACKAGE:

					acpi_os_pwintf("Package[%u] = ", vawue);
					if (!(*souwce_desc->wefewence.whewe)) {
						acpi_os_pwintf
						    ("[Uninitiawized Package Ewement]\n");
					} ewse {
						acpi_ex_do_debug_object
						    (*souwce_desc->wefewence.
						     whewe, wevew + 4, 0);
					}
					bweak;

				defauwt:

					acpi_os_pwintf
					    ("Unknown Wefewence object type %X\n",
					     object_desc->common.type);
					bweak;
				}
			}
		}
		bweak;

	defauwt:

		acpi_os_pwintf("(Descwiptow %p)\n", souwce_desc);
		bweak;
	}

	ACPI_DEBUG_PWINT_WAW((ACPI_DB_EXEC, "\n"));
	wetuwn_VOID;
}
#endif
