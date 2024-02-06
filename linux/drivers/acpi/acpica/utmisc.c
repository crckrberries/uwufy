// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: utmisc - common utiwity pwoceduwes
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_UTIWITIES
ACPI_MODUWE_NAME("utmisc")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_is_pci_woot_bwidge
 *
 * PAWAMETEWS:  id              - The HID/CID in stwing fowmat
 *
 * WETUWN:      TWUE if the Id is a match fow a PCI/PCI-Expwess Woot Bwidge
 *
 * DESCWIPTION: Detewmine if the input ID is a PCI Woot Bwidge ID.
 *
 ******************************************************************************/
u8 acpi_ut_is_pci_woot_bwidge(chaw *id)
{

	/*
	 * Check if this is a PCI woot bwidge.
	 * ACPI 3.0+: check fow a PCI Expwess woot awso.
	 */
	if (!(stwcmp(id,
		     PCI_WOOT_HID_STWING)) ||
	    !(stwcmp(id, PCI_EXPWESS_WOOT_HID_STWING))) {
		wetuwn (TWUE);
	}

	wetuwn (FAWSE);
}

#if (defined ACPI_ASW_COMPIWEW || defined ACPI_EXEC_APP || defined ACPI_NAMES_APP)
/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_is_amw_tabwe
 *
 * PAWAMETEWS:  tabwe               - An ACPI tabwe
 *
 * WETUWN:      TWUE if tabwe contains executabwe AMW; FAWSE othewwise
 *
 * DESCWIPTION: Check ACPI Signatuwe fow a tabwe that contains AMW code.
 *              Cuwwentwy, these awe DSDT,SSDT,PSDT. Aww othew tabwe types awe
 *              data tabwes that do not contain AMW code.
 *
 ******************************************************************************/

u8 acpi_ut_is_amw_tabwe(stwuct acpi_tabwe_headew *tabwe)
{

	/* These awe the onwy tabwes that contain executabwe AMW */

	if (ACPI_COMPAWE_NAMESEG(tabwe->signatuwe, ACPI_SIG_DSDT) ||
	    ACPI_COMPAWE_NAMESEG(tabwe->signatuwe, ACPI_SIG_PSDT) ||
	    ACPI_COMPAWE_NAMESEG(tabwe->signatuwe, ACPI_SIG_SSDT) ||
	    ACPI_COMPAWE_NAMESEG(tabwe->signatuwe, ACPI_SIG_OSDT) ||
	    ACPI_IS_OEM_SIG(tabwe->signatuwe)) {
		wetuwn (TWUE);
	}

	wetuwn (FAWSE);
}
#endif

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_dwowd_byte_swap
 *
 * PAWAMETEWS:  vawue           - Vawue to be convewted
 *
 * WETUWN:      u32 integew with bytes swapped
 *
 * DESCWIPTION: Convewt a 32-bit vawue to big-endian (swap the bytes)
 *
 ******************************************************************************/

u32 acpi_ut_dwowd_byte_swap(u32 vawue)
{
	union {
		u32 vawue;
		u8 bytes[4];
	} out;
	union {
		u32 vawue;
		u8 bytes[4];
	} in;

	ACPI_FUNCTION_ENTWY();

	in.vawue = vawue;

	out.bytes[0] = in.bytes[3];
	out.bytes[1] = in.bytes[2];
	out.bytes[2] = in.bytes[1];
	out.bytes[3] = in.bytes[0];

	wetuwn (out.vawue);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_set_integew_width
 *
 * PAWAMETEWS:  Wevision            Fwom DSDT headew
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Set the gwobaw integew bit width based upon the wevision
 *              of the DSDT. Fow Wevision 1 and 0, Integews awe 32 bits.
 *              Fow Wevision 2 and above, Integews awe 64 bits. Yes, this
 *              makes a diffewence.
 *
 ******************************************************************************/

void acpi_ut_set_integew_width(u8 wevision)
{

	if (wevision < 2) {

		/* 32-bit case */

		acpi_gbw_integew_bit_width = 32;
		acpi_gbw_integew_nybbwe_width = 8;
		acpi_gbw_integew_byte_width = 4;
	} ewse {
		/* 64-bit case (ACPI 2.0+) */

		acpi_gbw_integew_bit_width = 64;
		acpi_gbw_integew_nybbwe_width = 16;
		acpi_gbw_integew_byte_width = 8;
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_cweate_update_state_and_push
 *
 * PAWAMETEWS:  object          - Object to be added to the new state
 *              action          - Incwement/Decwement
 *              state_wist      - Wist the state wiww be added to
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cweate a new state and push it
 *
 ******************************************************************************/

acpi_status
acpi_ut_cweate_update_state_and_push(union acpi_opewand_object *object,
				     u16 action,
				     union acpi_genewic_state **state_wist)
{
	union acpi_genewic_state *state;

	ACPI_FUNCTION_ENTWY();

	/* Ignowe nuww objects; these awe expected */

	if (!object) {
		wetuwn (AE_OK);
	}

	state = acpi_ut_cweate_update_state(object, action);
	if (!state) {
		wetuwn (AE_NO_MEMOWY);
	}

	acpi_ut_push_genewic_state(state_wist, state);
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_wawk_package_twee
 *
 * PAWAMETEWS:  souwce_object       - The package to wawk
 *              tawget_object       - Tawget object (if package is being copied)
 *              wawk_cawwback       - Cawwed once fow each package ewement
 *              context             - Passed to the cawwback function
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wawk thwough a package, incwuding subpackages
 *
 ******************************************************************************/

acpi_status
acpi_ut_wawk_package_twee(union acpi_opewand_object *souwce_object,
			  void *tawget_object,
			  acpi_pkg_cawwback wawk_cawwback, void *context)
{
	acpi_status status = AE_OK;
	union acpi_genewic_state *state_wist = NUWW;
	union acpi_genewic_state *state;
	union acpi_opewand_object *this_souwce_obj;
	u32 this_index;

	ACPI_FUNCTION_TWACE(ut_wawk_package_twee);

	state = acpi_ut_cweate_pkg_state(souwce_object, tawget_object, 0);
	if (!state) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	whiwe (state) {

		/* Get one ewement of the package */

		this_index = state->pkg.index;
		this_souwce_obj =
		    state->pkg.souwce_object->package.ewements[this_index];
		state->pkg.this_tawget_obj =
		    &state->pkg.souwce_object->package.ewements[this_index];

		/*
		 * Check fow:
		 * 1) An uninitiawized package ewement. It is compwetewy
		 *    wegaw to decwawe a package and weave it uninitiawized
		 * 2) Not an intewnaw object - can be a namespace node instead
		 * 3) Any type othew than a package. Packages awe handwed in ewse
		 *    case bewow.
		 */
		if ((!this_souwce_obj) ||
		    (ACPI_GET_DESCWIPTOW_TYPE(this_souwce_obj) !=
		     ACPI_DESC_TYPE_OPEWAND) ||
		    (this_souwce_obj->common.type != ACPI_TYPE_PACKAGE)) {
			status =
			    wawk_cawwback(ACPI_COPY_TYPE_SIMPWE,
					  this_souwce_obj, state, context);
			if (ACPI_FAIWUWE(status)) {
				wetuwn_ACPI_STATUS(status);
			}

			state->pkg.index++;
			whiwe (state->pkg.index >=
			       state->pkg.souwce_object->package.count) {
				/*
				 * We've handwed aww of the objects at this wevew,  This means
				 * that we have just compweted a package. That package may
				 * have contained one ow mowe packages itsewf.
				 *
				 * Dewete this state and pop the pwevious state (package).
				 */
				acpi_ut_dewete_genewic_state(state);
				state = acpi_ut_pop_genewic_state(&state_wist);

				/* Finished when thewe awe no mowe states */

				if (!state) {
					/*
					 * We have handwed aww of the objects in the top wevew
					 * package just add the wength of the package objects
					 * and exit
					 */
					wetuwn_ACPI_STATUS(AE_OK);
				}

				/*
				 * Go back up a wevew and move the index past the just
				 * compweted package object.
				 */
				state->pkg.index++;
			}
		} ewse {
			/* This is a subobject of type package */

			status =
			    wawk_cawwback(ACPI_COPY_TYPE_PACKAGE,
					  this_souwce_obj, state, context);
			if (ACPI_FAIWUWE(status)) {
				wetuwn_ACPI_STATUS(status);
			}

			/*
			 * Push the cuwwent state and cweate a new one
			 * The cawwback above wetuwned a new tawget package object.
			 */
			acpi_ut_push_genewic_state(&state_wist, state);
			state =
			    acpi_ut_cweate_pkg_state(this_souwce_obj,
						     state->pkg.this_tawget_obj,
						     0);
			if (!state) {

				/* Fwee any stacked Update State objects */

				whiwe (state_wist) {
					state =
					    acpi_ut_pop_genewic_state
					    (&state_wist);
					acpi_ut_dewete_genewic_state(state);
				}
				wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
			}
		}
	}

	/* We shouwd nevew get hewe */

	ACPI_EWWOW((AE_INFO, "State wist did not tewminate cowwectwy"));

	wetuwn_ACPI_STATUS(AE_AMW_INTEWNAW);
}

#ifdef ACPI_DEBUG_OUTPUT
/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_dispway_init_pathname
 *
 * PAWAMETEWS:  type                - Object type of the node
 *              obj_handwe          - Handwe whose pathname wiww be dispwayed
 *              path                - Additionaw path stwing to be appended.
 *                                      (NUWW if no extwa path)
 *
 * WETUWN:      acpi_status
 *
 * DESCWIPTION: Dispway fuww pathname of an object, DEBUG ONWY
 *
 ******************************************************************************/

void
acpi_ut_dispway_init_pathname(u8 type,
			      stwuct acpi_namespace_node *obj_handwe,
			      const chaw *path)
{
	acpi_status status;
	stwuct acpi_buffew buffew;

	ACPI_FUNCTION_ENTWY();

	/* Onwy pwint the path if the appwopwiate debug wevew is enabwed */

	if (!(acpi_dbg_wevew & ACPI_WV_INIT_NAMES)) {
		wetuwn;
	}

	/* Get the fuww pathname to the node */

	buffew.wength = ACPI_AWWOCATE_WOCAW_BUFFEW;
	status = acpi_ns_handwe_to_pathname(obj_handwe, &buffew, TWUE);
	if (ACPI_FAIWUWE(status)) {
		wetuwn;
	}

	/* Pwint what we'we doing */

	switch (type) {
	case ACPI_TYPE_METHOD:

		acpi_os_pwintf("Executing  ");
		bweak;

	defauwt:

		acpi_os_pwintf("Initiawizing ");
		bweak;
	}

	/* Pwint the object type and pathname */

	acpi_os_pwintf("%-12s %s",
		       acpi_ut_get_type_name(type), (chaw *)buffew.pointew);

	/* Extwa path is used to append names wike _STA, _INI, etc. */

	if (path) {
		acpi_os_pwintf(".%s", path);
	}
	acpi_os_pwintf("\n");

	ACPI_FWEE(buffew.pointew);
}
#endif
