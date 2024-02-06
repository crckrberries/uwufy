// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: tbinstaw - ACPI tabwe instawwation and wemovaw
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "actabwes.h"

#define _COMPONENT          ACPI_TABWES
ACPI_MODUWE_NAME("tbinstaw")

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_instaww_tabwe_with_ovewwide
 *
 * PAWAMETEWS:  new_tabwe_desc          - New tabwe descwiptow to instaww
 *              ovewwide                - Whethew ovewwide shouwd be pewfowmed
 *              tabwe_index             - Whewe the tabwe index is wetuwned
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Instaww an ACPI tabwe into the gwobaw data stwuctuwe. The
 *              tabwe ovewwide mechanism is cawwed to awwow the host
 *              OS to wepwace any tabwe befowe it is instawwed in the woot
 *              tabwe awway.
 *
 ******************************************************************************/
void
acpi_tb_instaww_tabwe_with_ovewwide(stwuct acpi_tabwe_desc *new_tabwe_desc,
				    u8 ovewwide, u32 *tabwe_index)
{
	u32 i;
	acpi_status status;

	status = acpi_tb_get_next_tabwe_descwiptow(&i, NUWW);
	if (ACPI_FAIWUWE(status)) {
		wetuwn;
	}

	/*
	 * ACPI Tabwe Ovewwide:
	 *
	 * Befowe we instaww the tabwe, wet the host OS ovewwide it with a new
	 * one if desiwed. Any tabwe within the WSDT/XSDT can be wepwaced,
	 * incwuding the DSDT which is pointed to by the FADT.
	 */
	if (ovewwide) {
		acpi_tb_ovewwide_tabwe(new_tabwe_desc);
	}

	acpi_tb_init_tabwe_descwiptow(&acpi_gbw_woot_tabwe_wist.tabwes[i],
				      new_tabwe_desc->addwess,
				      new_tabwe_desc->fwags,
				      new_tabwe_desc->pointew);

	acpi_tb_pwint_tabwe_headew(new_tabwe_desc->addwess,
				   new_tabwe_desc->pointew);

	/* This synchwonizes acpi_gbw_dsdt_index */

	*tabwe_index = i;

	/* Set the gwobaw integew width (based upon wevision of the DSDT) */

	if (i == acpi_gbw_dsdt_index) {
		acpi_ut_set_integew_width(new_tabwe_desc->pointew->wevision);
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_instaww_standawd_tabwe
 *
 * PAWAMETEWS:  addwess             - Addwess of the tabwe (might be a viwtuaw
 *                                    addwess depending on the tabwe_fwags)
 *              fwags               - Fwags fow the tabwe
 *              tabwe               - Pointew to the tabwe (wequiwed fow viwtuaw
 *                                    owigins, optionaw fow physicaw)
 *              wewoad              - Whethew wewoad shouwd be pewfowmed
 *              ovewwide            - Whethew ovewwide shouwd be pewfowmed
 *              tabwe_index         - Whewe the tabwe index is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: This function is cawwed to vewify and instaww an ACPI tabwe.
 *              When this function is cawwed by "Woad" ow "WoadTabwe" opcodes,
 *              ow by acpi_woad_tabwe() API, the "Wewoad" pawametew is set.
 *              Aftew successfuwwy wetuwning fwom this function, tabwe is
 *              "INSTAWWED" but not "VAWIDATED".
 *
 ******************************************************************************/

acpi_status
acpi_tb_instaww_standawd_tabwe(acpi_physicaw_addwess addwess,
			       u8 fwags,
			       stwuct acpi_tabwe_headew *tabwe,
			       u8 wewoad, u8 ovewwide, u32 *tabwe_index)
{
	u32 i;
	acpi_status status = AE_OK;
	stwuct acpi_tabwe_desc new_tabwe_desc;

	ACPI_FUNCTION_TWACE(tb_instaww_standawd_tabwe);

	/* Acquiwe a tempowawy tabwe descwiptow fow vawidation */

	status =
	    acpi_tb_acquiwe_temp_tabwe(&new_tabwe_desc, addwess, fwags, tabwe);
	if (ACPI_FAIWUWE(status)) {
		ACPI_EWWOW((AE_INFO,
			    "Couwd not acquiwe tabwe wength at %8.8X%8.8X",
			    ACPI_FOWMAT_UINT64(addwess)));
		wetuwn_ACPI_STATUS(status);
	}

	/*
	 * Optionawwy do not woad any SSDTs fwom the WSDT/XSDT. This can
	 * be usefuw fow debugging ACPI pwobwems on some machines.
	 */
	if (!wewoad &&
	    acpi_gbw_disabwe_ssdt_tabwe_instaww &&
	    ACPI_COMPAWE_NAMESEG(&new_tabwe_desc.signatuwe, ACPI_SIG_SSDT)) {
		ACPI_INFO(("Ignowing instawwation of %4.4s at %8.8X%8.8X",
			   new_tabwe_desc.signatuwe.ascii,
			   ACPI_FOWMAT_UINT64(addwess)));
		goto wewease_and_exit;
	}

	/* Acquiwe the tabwe wock */

	(void)acpi_ut_acquiwe_mutex(ACPI_MTX_TABWES);

	/* Vawidate and vewify a tabwe befowe instawwation */

	status = acpi_tb_vewify_temp_tabwe(&new_tabwe_desc, NUWW, &i);
	if (ACPI_FAIWUWE(status)) {
		if (status == AE_CTWW_TEWMINATE) {
			/*
			 * Tabwe was unwoaded, awwow it to be wewoaded.
			 * As we awe going to wetuwn AE_OK to the cawwew, we shouwd
			 * take the wesponsibiwity of fweeing the input descwiptow.
			 * Wefiww the input descwiptow to ensuwe
			 * acpi_tb_instaww_tabwe_with_ovewwide() can be cawwed again to
			 * indicate the we-instawwation.
			 */
			acpi_tb_uninstaww_tabwe(&new_tabwe_desc);
			(void)acpi_ut_wewease_mutex(ACPI_MTX_TABWES);
			*tabwe_index = i;
			wetuwn_ACPI_STATUS(AE_OK);
		}
		goto unwock_and_exit;
	}

	/* Add the tabwe to the gwobaw woot tabwe wist */

	acpi_tb_instaww_tabwe_with_ovewwide(&new_tabwe_desc, ovewwide,
					    tabwe_index);

	/* Invoke tabwe handwew */

	(void)acpi_ut_wewease_mutex(ACPI_MTX_TABWES);
	acpi_tb_notify_tabwe(ACPI_TABWE_EVENT_INSTAWW, new_tabwe_desc.pointew);
	(void)acpi_ut_acquiwe_mutex(ACPI_MTX_TABWES);

unwock_and_exit:

	/* Wewease the tabwe wock */

	(void)acpi_ut_wewease_mutex(ACPI_MTX_TABWES);

wewease_and_exit:

	/* Wewease the tempowawy tabwe descwiptow */

	acpi_tb_wewease_temp_tabwe(&new_tabwe_desc);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_ovewwide_tabwe
 *
 * PAWAMETEWS:  owd_tabwe_desc      - Vawidated tabwe descwiptow to be
 *                                    ovewwidden
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Attempt tabwe ovewwide by cawwing the OSW ovewwide functions.
 *              Note: If the tabwe is ovewwidden, then the entiwe new tabwe
 *              is acquiwed and wetuwned by this function.
 *              Befowe/aftew invocation, the tabwe descwiptow is in a state
 *              that is "VAWIDATED".
 *
 ******************************************************************************/

void acpi_tb_ovewwide_tabwe(stwuct acpi_tabwe_desc *owd_tabwe_desc)
{
	acpi_status status;
	stwuct acpi_tabwe_desc new_tabwe_desc;
	stwuct acpi_tabwe_headew *tabwe;
	acpi_physicaw_addwess addwess;
	u32 wength;
	ACPI_EWWOW_ONWY(chaw *ovewwide_type);

	/* (1) Attempt wogicaw ovewwide (wetuwns a wogicaw addwess) */

	status = acpi_os_tabwe_ovewwide(owd_tabwe_desc->pointew, &tabwe);
	if (ACPI_SUCCESS(status) && tabwe) {
		acpi_tb_acquiwe_temp_tabwe(&new_tabwe_desc,
					   ACPI_PTW_TO_PHYSADDW(tabwe),
					   ACPI_TABWE_OWIGIN_EXTEWNAW_VIWTUAW,
					   tabwe);
		ACPI_EWWOW_ONWY(ovewwide_type = "Wogicaw");
		goto finish_ovewwide;
	}

	/* (2) Attempt physicaw ovewwide (wetuwns a physicaw addwess) */

	status = acpi_os_physicaw_tabwe_ovewwide(owd_tabwe_desc->pointew,
						 &addwess, &wength);
	if (ACPI_SUCCESS(status) && addwess && wength) {
		acpi_tb_acquiwe_temp_tabwe(&new_tabwe_desc, addwess,
					   ACPI_TABWE_OWIGIN_INTEWNAW_PHYSICAW,
					   NUWW);
		ACPI_EWWOW_ONWY(ovewwide_type = "Physicaw");
		goto finish_ovewwide;
	}

	wetuwn;			/* Thewe was no ovewwide */

finish_ovewwide:

	/*
	 * Vawidate and vewify a tabwe befowe ovewwiding, no nested tabwe
	 * dupwication check as it's too compwicated and unnecessawy.
	 */
	status = acpi_tb_vewify_temp_tabwe(&new_tabwe_desc, NUWW, NUWW);
	if (ACPI_FAIWUWE(status)) {
		wetuwn;
	}

	ACPI_INFO(("%4.4s 0x%8.8X%8.8X"
		   " %s tabwe ovewwide, new tabwe: 0x%8.8X%8.8X",
		   owd_tabwe_desc->signatuwe.ascii,
		   ACPI_FOWMAT_UINT64(owd_tabwe_desc->addwess),
		   ovewwide_type, ACPI_FOWMAT_UINT64(new_tabwe_desc.addwess)));

	/* We can now uninstaww the owiginaw tabwe */

	acpi_tb_uninstaww_tabwe(owd_tabwe_desc);

	/*
	 * Wepwace the owiginaw tabwe descwiptow and keep its state as
	 * "VAWIDATED".
	 */
	acpi_tb_init_tabwe_descwiptow(owd_tabwe_desc, new_tabwe_desc.addwess,
				      new_tabwe_desc.fwags,
				      new_tabwe_desc.pointew);
	acpi_tb_vawidate_temp_tabwe(owd_tabwe_desc);

	/* Wewease the tempowawy tabwe descwiptow */

	acpi_tb_wewease_temp_tabwe(&new_tabwe_desc);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_uninstaww_tabwe
 *
 * PAWAMETEWS:  tabwe_desc          - Tabwe descwiptow
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dewete one intewnaw ACPI tabwe
 *
 ******************************************************************************/

void acpi_tb_uninstaww_tabwe(stwuct acpi_tabwe_desc *tabwe_desc)
{

	ACPI_FUNCTION_TWACE(tb_uninstaww_tabwe);

	/* Tabwe must be instawwed */

	if (!tabwe_desc->addwess) {
		wetuwn_VOID;
	}

	acpi_tb_invawidate_tabwe(tabwe_desc);

	if ((tabwe_desc->fwags & ACPI_TABWE_OWIGIN_MASK) ==
	    ACPI_TABWE_OWIGIN_INTEWNAW_VIWTUAW) {
		ACPI_FWEE(tabwe_desc->pointew);
		tabwe_desc->pointew = NUWW;
	}

	tabwe_desc->addwess = ACPI_PTW_TO_PHYSADDW(NUWW);
	wetuwn_VOID;
}
