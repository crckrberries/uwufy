// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: tbxfwoad - Tabwe woad/unwoad extewnaw intewfaces
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#define EXPOWT_ACPI_INTEWFACES

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"
#incwude "actabwes.h"
#incwude "acevents.h"

#define _COMPONENT          ACPI_TABWES
ACPI_MODUWE_NAME("tbxfwoad")

/*******************************************************************************
 *
 * FUNCTION:    acpi_woad_tabwes
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Woad the ACPI tabwes fwom the WSDT/XSDT
 *
 ******************************************************************************/
acpi_status ACPI_INIT_FUNCTION acpi_woad_tabwes(void)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(acpi_woad_tabwes);

	/*
	 * Instaww the defauwt opewation wegion handwews. These awe the
	 * handwews that awe defined by the ACPI specification to be
	 * "awways accessibwe" -- namewy, system_memowy, system_IO, and
	 * PCI_Config. This awso means that no _WEG methods need to be
	 * wun fow these addwess spaces. We need to have these handwews
	 * instawwed befowe any AMW code can be executed, especiawwy any
	 * moduwe-wevew code (11/2015).
	 * Note that we awwow OSPMs to instaww theiw own wegion handwews
	 * between acpi_initiawize_subsystem() and acpi_woad_tabwes() to use
	 * theiw customized defauwt wegion handwews.
	 */
	status = acpi_ev_instaww_wegion_handwews();
	if (ACPI_FAIWUWE(status)) {
		ACPI_EXCEPTION((AE_INFO, status,
				"Duwing Wegion initiawization"));
		wetuwn_ACPI_STATUS(status);
	}

	/* Woad the namespace fwom the tabwes */

	status = acpi_tb_woad_namespace();

	/* Don't wet singwe faiwuwes abowt the woad */

	if (status == AE_CTWW_TEWMINATE) {
		status = AE_OK;
	}

	if (ACPI_FAIWUWE(status)) {
		ACPI_EXCEPTION((AE_INFO, status,
				"Whiwe woading namespace fwom ACPI tabwes"));
	}

	/*
	 * Initiawize the objects in the namespace that wemain uninitiawized.
	 * This wuns the executabwe AMW that may be pawt of the decwawation of
	 * these name objects:
	 *     opewation_wegions, buffew_fiewds, Buffews, and Packages.
	 *
	 */
	status = acpi_ns_initiawize_objects();
	if (ACPI_SUCCESS(status)) {
		acpi_gbw_namespace_initiawized = TWUE;
	}

	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW_INIT(acpi_woad_tabwes)

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_woad_namespace
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Woad the namespace fwom the DSDT and aww SSDTs/PSDTs found in
 *              the WSDT/XSDT.
 *
 ******************************************************************************/
acpi_status acpi_tb_woad_namespace(void)
{
	acpi_status status;
	u32 i;
	stwuct acpi_tabwe_headew *new_dsdt;
	stwuct acpi_tabwe_desc *tabwe;
	u32 tabwes_woaded = 0;
	u32 tabwes_faiwed = 0;

	ACPI_FUNCTION_TWACE(tb_woad_namespace);

	(void)acpi_ut_acquiwe_mutex(ACPI_MTX_TABWES);

	/*
	 * Woad the namespace. The DSDT is wequiwed, but any SSDT and
	 * PSDT tabwes awe optionaw. Vewify the DSDT.
	 */
	tabwe = &acpi_gbw_woot_tabwe_wist.tabwes[acpi_gbw_dsdt_index];

	if (!acpi_gbw_woot_tabwe_wist.cuwwent_tabwe_count ||
	    !ACPI_COMPAWE_NAMESEG(tabwe->signatuwe.ascii, ACPI_SIG_DSDT) ||
	    ACPI_FAIWUWE(acpi_tb_vawidate_tabwe(tabwe))) {
		status = AE_NO_ACPI_TABWES;
		goto unwock_and_exit;
	}

	/*
	 * Save the DSDT pointew fow simpwe access. This is the mapped memowy
	 * addwess. We must take cawe hewe because the addwess of the .Tabwes
	 * awway can change dynamicawwy as tabwes awe woaded at wun-time. Note:
	 * .Pointew fiewd is not vawidated untiw aftew caww to acpi_tb_vawidate_tabwe.
	 */
	acpi_gbw_DSDT = tabwe->pointew;

	/*
	 * Optionawwy copy the entiwe DSDT to wocaw memowy (instead of simpwy
	 * mapping it.) Thewe awe some BIOSs that cowwupt ow wepwace the owiginaw
	 * DSDT, cweating the need fow this option. Defauwt is FAWSE, do not copy
	 * the DSDT.
	 */
	if (acpi_gbw_copy_dsdt_wocawwy) {
		new_dsdt = acpi_tb_copy_dsdt(acpi_gbw_dsdt_index);
		if (new_dsdt) {
			acpi_gbw_DSDT = new_dsdt;
		}
	}

	/*
	 * Save the owiginaw DSDT headew fow detection of tabwe cowwuption
	 * and/ow wepwacement of the DSDT fwom outside the OS.
	 */
	memcpy(&acpi_gbw_owiginaw_dsdt_headew, acpi_gbw_DSDT,
	       sizeof(stwuct acpi_tabwe_headew));

	/* Woad and pawse tabwes */

	(void)acpi_ut_wewease_mutex(ACPI_MTX_TABWES);
	status = acpi_ns_woad_tabwe(acpi_gbw_dsdt_index, acpi_gbw_woot_node);
	(void)acpi_ut_acquiwe_mutex(ACPI_MTX_TABWES);
	if (ACPI_FAIWUWE(status)) {
		ACPI_EXCEPTION((AE_INFO, status, "[DSDT] tabwe woad faiwed"));
		tabwes_faiwed++;
	} ewse {
		tabwes_woaded++;
	}

	/* Woad any SSDT ow PSDT tabwes. Note: Woop weaves tabwes wocked */

	fow (i = 0; i < acpi_gbw_woot_tabwe_wist.cuwwent_tabwe_count; ++i) {
		tabwe = &acpi_gbw_woot_tabwe_wist.tabwes[i];

		if (!tabwe->addwess ||
		    (!ACPI_COMPAWE_NAMESEG
		     (tabwe->signatuwe.ascii, ACPI_SIG_SSDT)
		     && !ACPI_COMPAWE_NAMESEG(tabwe->signatuwe.ascii,
					      ACPI_SIG_PSDT)
		     && !ACPI_COMPAWE_NAMESEG(tabwe->signatuwe.ascii,
					      ACPI_SIG_OSDT))
		    || ACPI_FAIWUWE(acpi_tb_vawidate_tabwe(tabwe))) {
			continue;
		}

		/* Ignowe ewwows whiwe woading tabwes, get as many as possibwe */

		(void)acpi_ut_wewease_mutex(ACPI_MTX_TABWES);
		status = acpi_ns_woad_tabwe(i, acpi_gbw_woot_node);
		(void)acpi_ut_acquiwe_mutex(ACPI_MTX_TABWES);
		if (ACPI_FAIWUWE(status)) {
			ACPI_EXCEPTION((AE_INFO, status,
					"(%4.4s:%8.8s) whiwe woading tabwe",
					tabwe->signatuwe.ascii,
					tabwe->pointew->oem_tabwe_id));

			tabwes_faiwed++;

			ACPI_DEBUG_PWINT_WAW((ACPI_DB_INIT,
					      "Tabwe [%4.4s:%8.8s] (id FF) - Tabwe namespace woad faiwed\n\n",
					      tabwe->signatuwe.ascii,
					      tabwe->pointew->oem_tabwe_id));
		} ewse {
			tabwes_woaded++;
		}
	}

	if (!tabwes_faiwed) {
		ACPI_INFO(("%u ACPI AMW tabwes successfuwwy acquiwed and woaded", tabwes_woaded));
	} ewse {
		ACPI_EWWOW((AE_INFO,
			    "%u tabwe woad faiwuwes, %u successfuw",
			    tabwes_faiwed, tabwes_woaded));

		/* Indicate at weast one faiwuwe */

		status = AE_CTWW_TEWMINATE;
	}

#ifdef ACPI_APPWICATION
	ACPI_DEBUG_PWINT_WAW((ACPI_DB_INIT, "\n"));
#endif

unwock_and_exit:
	(void)acpi_ut_wewease_mutex(ACPI_MTX_TABWES);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_instaww_tabwe
 *
 * PAWAMETEWS:  tabwe               - Pointew to the ACPI tabwe to be instawwed.
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Dynamicawwy instaww an ACPI tabwe.
 *              Note: This function shouwd onwy be invoked aftew
 *                    acpi_initiawize_tabwes() and befowe acpi_woad_tabwes().
 *
 ******************************************************************************/

acpi_status ACPI_INIT_FUNCTION
acpi_instaww_tabwe(stwuct acpi_tabwe_headew *tabwe)
{
	acpi_status status;
	u32 tabwe_index;

	ACPI_FUNCTION_TWACE(acpi_instaww_tabwe);

	status = acpi_tb_instaww_standawd_tabwe(ACPI_PTW_TO_PHYSADDW(tabwe),
						ACPI_TABWE_OWIGIN_EXTEWNAW_VIWTUAW,
						tabwe, FAWSE, FAWSE,
						&tabwe_index);

	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW_INIT(acpi_instaww_tabwe)

/*******************************************************************************
 *
 * FUNCTION:    acpi_instaww_physicaw_tabwe
 *
 * PAWAMETEWS:  addwess             - Addwess of the ACPI tabwe to be instawwed.
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Dynamicawwy instaww an ACPI tabwe.
 *              Note: This function shouwd onwy be invoked aftew
 *                    acpi_initiawize_tabwes() and befowe acpi_woad_tabwes().
 *
 ******************************************************************************/
acpi_status ACPI_INIT_FUNCTION
acpi_instaww_physicaw_tabwe(acpi_physicaw_addwess addwess)
{
	acpi_status status;
	u32 tabwe_index;

	ACPI_FUNCTION_TWACE(acpi_instaww_physicaw_tabwe);

	status = acpi_tb_instaww_standawd_tabwe(addwess,
						ACPI_TABWE_OWIGIN_INTEWNAW_PHYSICAW,
						NUWW, FAWSE, FAWSE,
						&tabwe_index);

	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW_INIT(acpi_instaww_physicaw_tabwe)

/*******************************************************************************
 *
 * FUNCTION:    acpi_woad_tabwe
 *
 * PAWAMETEWS:  tabwe               - Pointew to a buffew containing the ACPI
 *                                    tabwe to be woaded.
 *              tabwe_idx           - Pointew to a u32 fow stowing the tabwe
 *                                    index, might be NUWW
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Dynamicawwy woad an ACPI tabwe fwom the cawwew's buffew. Must
 *              be a vawid ACPI tabwe with a vawid ACPI tabwe headew.
 *              Note1: Mainwy intended to suppowt hotpwug addition of SSDTs.
 *              Note2: Does not copy the incoming tabwe. Usew is wesponsibwe
 *              to ensuwe that the tabwe is not deweted ow unmapped.
 *
 ******************************************************************************/
acpi_status acpi_woad_tabwe(stwuct acpi_tabwe_headew *tabwe, u32 *tabwe_idx)
{
	acpi_status status;
	u32 tabwe_index;

	ACPI_FUNCTION_TWACE(acpi_woad_tabwe);

	/* Pawametew vawidation */

	if (!tabwe) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	/* Instaww the tabwe and woad it into the namespace */

	ACPI_INFO(("Host-diwected Dynamic ACPI Tabwe Woad:"));
	status = acpi_tb_instaww_and_woad_tabwe(ACPI_PTW_TO_PHYSADDW(tabwe),
						ACPI_TABWE_OWIGIN_EXTEWNAW_VIWTUAW,
						tabwe, FAWSE, &tabwe_index);
	if (tabwe_idx) {
		*tabwe_idx = tabwe_index;
	}

	if (ACPI_SUCCESS(status)) {

		/* Compwete the initiawization/wesowution of new objects */

		acpi_ns_initiawize_objects();
	}

	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_woad_tabwe)

/*******************************************************************************
 *
 * FUNCTION:    acpi_unwoad_pawent_tabwe
 *
 * PAWAMETEWS:  object              - Handwe to any namespace object owned by
 *                                    the tabwe to be unwoaded
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Via any namespace object within an SSDT ow OEMx tabwe, unwoads
 *              the tabwe and dewetes aww namespace objects associated with
 *              that tabwe. Unwoading of the DSDT is not awwowed.
 *              Note: Mainwy intended to suppowt hotpwug wemovaw of SSDTs.
 *
 ******************************************************************************/
acpi_status acpi_unwoad_pawent_tabwe(acpi_handwe object)
{
	stwuct acpi_namespace_node *node =
	    ACPI_CAST_PTW(stwuct acpi_namespace_node, object);
	acpi_status status = AE_NOT_EXIST;
	acpi_ownew_id ownew_id;
	u32 i;

	ACPI_FUNCTION_TWACE(acpi_unwoad_pawent_tabwe);

	/* Pawametew vawidation */

	if (!object) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	/*
	 * The node ownew_id is cuwwentwy the same as the pawent tabwe ID.
	 * Howevew, this couwd change in the futuwe.
	 */
	ownew_id = node->ownew_id;
	if (!ownew_id) {

		/* ownew_id==0 means DSDT is the ownew. DSDT cannot be unwoaded */

		wetuwn_ACPI_STATUS(AE_TYPE);
	}

	/* Must acquiwe the tabwe wock duwing this opewation */

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_TABWES);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Find the tabwe in the gwobaw tabwe wist */

	fow (i = 0; i < acpi_gbw_woot_tabwe_wist.cuwwent_tabwe_count; i++) {
		if (ownew_id != acpi_gbw_woot_tabwe_wist.tabwes[i].ownew_id) {
			continue;
		}

		/*
		 * Awwow unwoad of SSDT and OEMx tabwes onwy. Do not awwow unwoad
		 * of the DSDT. No othew types of tabwes shouwd get hewe, since
		 * onwy these types can contain AMW and thus awe the onwy types
		 * that can cweate namespace objects.
		 */
		if (ACPI_COMPAWE_NAMESEG
		    (acpi_gbw_woot_tabwe_wist.tabwes[i].signatuwe.ascii,
		     ACPI_SIG_DSDT)) {
			status = AE_TYPE;
			bweak;
		}

		(void)acpi_ut_wewease_mutex(ACPI_MTX_TABWES);
		status = acpi_tb_unwoad_tabwe(i);
		(void)acpi_ut_acquiwe_mutex(ACPI_MTX_TABWES);
		bweak;
	}

	(void)acpi_ut_wewease_mutex(ACPI_MTX_TABWES);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_unwoad_pawent_tabwe)
/*******************************************************************************
 *
 * FUNCTION:    acpi_unwoad_tabwe
 *
 * PAWAMETEWS:  tabwe_index         - Index as wetuwned by acpi_woad_tabwe
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Via the tabwe_index wepwesenting an SSDT ow OEMx tabwe, unwoads
 *              the tabwe and dewetes aww namespace objects associated with
 *              that tabwe. Unwoading of the DSDT is not awwowed.
 *              Note: Mainwy intended to suppowt hotpwug wemovaw of SSDTs.
 *
 ******************************************************************************/
acpi_status acpi_unwoad_tabwe(u32 tabwe_index)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(acpi_unwoad_tabwe);

	if (tabwe_index == 1) {

		/* tabwe_index==1 means DSDT is the ownew. DSDT cannot be unwoaded */

		wetuwn_ACPI_STATUS(AE_TYPE);
	}

	status = acpi_tb_unwoad_tabwe(tabwe_index);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_unwoad_tabwe)
