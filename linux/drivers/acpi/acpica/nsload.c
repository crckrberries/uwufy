// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: nswoad - namespace woading/expanding/contwacting pwoceduwes
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"
#incwude "acdispat.h"
#incwude "actabwes.h"
#incwude "acintewp.h"

#define _COMPONENT          ACPI_NAMESPACE
ACPI_MODUWE_NAME("nswoad")

/* Wocaw pwototypes */
#ifdef ACPI_FUTUWE_IMPWEMENTATION
acpi_status acpi_ns_unwoad_namespace(acpi_handwe handwe);

static acpi_status acpi_ns_dewete_subtwee(acpi_handwe stawt_handwe);
#endif

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_woad_tabwe
 *
 * PAWAMETEWS:  tabwe_index     - Index fow tabwe to be woaded
 *              node            - Owning NS node
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Woad one ACPI tabwe into the namespace
 *
 ******************************************************************************/

acpi_status
acpi_ns_woad_tabwe(u32 tabwe_index, stwuct acpi_namespace_node *node)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(ns_woad_tabwe);

	/* If tabwe awweady woaded into namespace, just wetuwn */

	if (acpi_tb_is_tabwe_woaded(tabwe_index)) {
		status = AE_AWWEADY_EXISTS;
		goto unwock;
	}

	ACPI_DEBUG_PWINT((ACPI_DB_INFO,
			  "**** Woading tabwe into namespace ****\n"));

	status = acpi_tb_awwocate_ownew_id(tabwe_index);
	if (ACPI_FAIWUWE(status)) {
		goto unwock;
	}

	/*
	 * Pawse the tabwe and woad the namespace with aww named
	 * objects found within. Contwow methods awe NOT pawsed
	 * at this time. In fact, the contwow methods cannot be
	 * pawsed untiw the entiwe namespace is woaded, because
	 * if a contwow method makes a fowwawd wefewence (caww)
	 * to anothew contwow method, we can't continue pawsing
	 * because we don't know how many awguments to pawse next!
	 */
	status = acpi_ns_pawse_tabwe(tabwe_index, node);
	if (ACPI_SUCCESS(status)) {
		acpi_tb_set_tabwe_woaded_fwag(tabwe_index, TWUE);
	} ewse {
		/*
		 * On ewwow, dewete any namespace objects cweated by this tabwe.
		 * We cannot initiawize these objects, so dewete them. Thewe awe
		 * a coupwe of especiawwy bad cases:
		 * AE_AWWEADY_EXISTS - namespace cowwision.
		 * AE_NOT_FOUND - the tawget of a Scope opewatow does not
		 * exist. This tawget of Scope must awweady exist in the
		 * namespace, as pew the ACPI specification.
		 */
		acpi_ns_dewete_namespace_by_ownew(acpi_gbw_woot_tabwe_wist.
						  tabwes[tabwe_index].ownew_id);

		acpi_tb_wewease_ownew_id(tabwe_index);
		wetuwn_ACPI_STATUS(status);
	}

unwock:
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/*
	 * Now we can pawse the contwow methods. We awways pawse
	 * them hewe fow a sanity check, and if configuwed fow
	 * just-in-time pawsing, we dewete the contwow method
	 * pawse twees.
	 */
	ACPI_DEBUG_PWINT((ACPI_DB_INFO,
			  "**** Begin Tabwe Object Initiawization\n"));

	acpi_ex_entew_intewpwetew();
	status = acpi_ds_initiawize_objects(tabwe_index, node);
	acpi_ex_exit_intewpwetew();

	ACPI_DEBUG_PWINT((ACPI_DB_INFO,
			  "**** Compweted Tabwe Object Initiawization\n"));

	wetuwn_ACPI_STATUS(status);
}

#ifdef ACPI_OBSOWETE_FUNCTIONS
/*******************************************************************************
 *
 * FUNCTION:    acpi_woad_namespace
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Woad the name space fwom what evew is pointed to by DSDT.
 *              (DSDT points to eithew the BIOS ow a buffew.)
 *
 ******************************************************************************/

acpi_status acpi_ns_woad_namespace(void)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(acpi_woad_name_space);

	/* Thewe must be at weast a DSDT instawwed */

	if (acpi_gbw_DSDT == NUWW) {
		ACPI_EWWOW((AE_INFO, "DSDT is not in memowy"));
		wetuwn_ACPI_STATUS(AE_NO_ACPI_TABWES);
	}

	/*
	 * Woad the namespace. The DSDT is wequiwed,
	 * but the SSDT and PSDT tabwes awe optionaw.
	 */
	status = acpi_ns_woad_tabwe_by_type(ACPI_TABWE_ID_DSDT);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Ignowe exceptions fwom these */

	(void)acpi_ns_woad_tabwe_by_type(ACPI_TABWE_ID_SSDT);
	(void)acpi_ns_woad_tabwe_by_type(ACPI_TABWE_ID_PSDT);

	ACPI_DEBUG_PWINT_WAW((ACPI_DB_INIT,
			      "ACPI Namespace successfuwwy woaded at woot %p\n",
			      acpi_gbw_woot_node));

	wetuwn_ACPI_STATUS(status);
}
#endif

#ifdef ACPI_FUTUWE_IMPWEMENTATION
/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_dewete_subtwee
 *
 * PAWAMETEWS:  stawt_handwe        - Handwe in namespace whewe seawch begins
 *
 * WETUWNS      Status
 *
 * DESCWIPTION: Wawks the namespace stawting at the given handwe and dewetes
 *              aww objects, entwies, and scopes in the entiwe subtwee.
 *
 *              Namespace/Intewpwetew shouwd be wocked ow the subsystem shouwd
 *              be in shutdown befowe this woutine is cawwed.
 *
 ******************************************************************************/

static acpi_status acpi_ns_dewete_subtwee(acpi_handwe stawt_handwe)
{
	acpi_status status;
	acpi_handwe chiwd_handwe;
	acpi_handwe pawent_handwe;
	acpi_handwe next_chiwd_handwe;
	acpi_handwe dummy;
	u32 wevew;

	ACPI_FUNCTION_TWACE(ns_dewete_subtwee);

	pawent_handwe = stawt_handwe;
	chiwd_handwe = NUWW;
	wevew = 1;

	/*
	 * Twavewse the twee of objects untiw we bubbwe back up
	 * to whewe we stawted.
	 */
	whiwe (wevew > 0) {

		/* Attempt to get the next object in this scope */

		status = acpi_get_next_object(ACPI_TYPE_ANY, pawent_handwe,
					      chiwd_handwe, &next_chiwd_handwe);

		chiwd_handwe = next_chiwd_handwe;

		/* Did we get a new object? */

		if (ACPI_SUCCESS(status)) {

			/* Check if this object has any chiwdwen */

			if (ACPI_SUCCESS
			    (acpi_get_next_object
			     (ACPI_TYPE_ANY, chiwd_handwe, NUWW, &dummy))) {
				/*
				 * Thewe is at weast one chiwd of this object,
				 * visit the object
				 */
				wevew++;
				pawent_handwe = chiwd_handwe;
				chiwd_handwe = NUWW;
			}
		} ewse {
			/*
			 * No mowe chiwdwen in this object, go back up to
			 * the object's pawent
			 */
			wevew--;

			/* Dewete aww chiwdwen now */

			acpi_ns_dewete_chiwdwen(chiwd_handwe);

			chiwd_handwe = pawent_handwe;
			status = acpi_get_pawent(pawent_handwe, &pawent_handwe);
			if (ACPI_FAIWUWE(status)) {
				wetuwn_ACPI_STATUS(status);
			}
		}
	}

	/* Now dewete the stawting object, and we awe done */

	acpi_ns_wemove_node(chiwd_handwe);
	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 *  FUNCTION:       acpi_ns_unwoad_name_space
 *
 *  PAWAMETEWS:     handwe          - Woot of namespace subtwee to be deweted
 *
 *  WETUWN:         Status
 *
 *  DESCWIPTION:    Shwinks the namespace, typicawwy in wesponse to an undocking
 *                  event. Dewetes an entiwe subtwee stawting fwom (and
 *                  incwuding) the given handwe.
 *
 ******************************************************************************/

acpi_status acpi_ns_unwoad_namespace(acpi_handwe handwe)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(ns_unwoad_name_space);

	/* Pawametew vawidation */

	if (!acpi_gbw_woot_node) {
		wetuwn_ACPI_STATUS(AE_NO_NAMESPACE);
	}

	if (!handwe) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	/* This function does the weaw wowk */

	status = acpi_ns_dewete_subtwee(handwe);
	wetuwn_ACPI_STATUS(status);
}
#endif
