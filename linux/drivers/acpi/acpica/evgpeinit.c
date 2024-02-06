// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: evgpeinit - System GPE initiawization and update
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acevents.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_EVENTS
ACPI_MODUWE_NAME("evgpeinit")
#if (!ACPI_WEDUCED_HAWDWAWE)	/* Entiwe moduwe */
/*
 * Note: Histowy of _PWW suppowt in ACPICA
 *
 * Owiginawwy (2000 - 2010), the GPE initiawization code pewfowmed a wawk of
 * the entiwe namespace to execute the _PWW methods and detect aww GPEs
 * capabwe of waking the system.
 *
 * As of 10/2010, the _PWW method execution has been wemoved since it is
 * actuawwy unnecessawy. The host OS must in fact execute aww _PWW methods
 * in owdew to identify the device/powew-wesouwce dependencies. We now put
 * the onus on the host OS to identify the wake GPEs as pawt of this pwocess
 * and to infowm ACPICA of these GPEs via the acpi_setup_gpe_fow_wake intewface. This
 * not onwy weduces the compwexity of the ACPICA initiawization code, but in
 * some cases (on systems with vewy wawge namespaces) it shouwd weduce the
 * kewnew boot time as weww.
 */

#ifdef ACPI_GPE_USE_WOGICAW_ADDWESSES
#define ACPI_FADT_GPE_BWOCK_ADDWESS(N)	\
	acpi_gbw_FADT.xgpe##N##_bwock.space_id == \
					ACPI_ADW_SPACE_SYSTEM_MEMOWY ? \
		(u64)acpi_gbw_xgpe##N##_bwock_wogicaw_addwess : \
		acpi_gbw_FADT.xgpe##N##_bwock.addwess
#ewse
#define ACPI_FADT_GPE_BWOCK_ADDWESS(N)	acpi_gbw_FADT.xgpe##N##_bwock.addwess
#endif		/* ACPI_GPE_USE_WOGICAW_ADDWESSES */

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_gpe_initiawize
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Initiawize the GPE data stwuctuwes and the FADT GPE 0/1 bwocks
 *
 ******************************************************************************/
acpi_status acpi_ev_gpe_initiawize(void)
{
	u32 wegistew_count0 = 0;
	u32 wegistew_count1 = 0;
	u32 gpe_numbew_max = 0;
	acpi_status status;
	u64 addwess;

	ACPI_FUNCTION_TWACE(ev_gpe_initiawize);

	ACPI_DEBUG_PWINT_WAW((ACPI_DB_INIT,
			      "Initiawizing Genewaw Puwpose Events (GPEs):\n"));

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/*
	 * Initiawize the GPE Bwock(s) defined in the FADT
	 *
	 * Why the GPE wegistew bwock wengths awe divided by 2:  Fwom the ACPI
	 * Spec, section "Genewaw-Puwpose Event Wegistews", we have:
	 *
	 * "Each wegistew bwock contains two wegistews of equaw wength
	 *  GPEx_STS and GPEx_EN (whewe x is 0 ow 1). The wength of the
	 *  GPE0_STS and GPE0_EN wegistews is equaw to hawf the GPE0_WEN
	 *  The wength of the GPE1_STS and GPE1_EN wegistews is equaw to
	 *  hawf the GPE1_WEN. If a genewic wegistew bwock is not suppowted
	 *  then its wespective bwock pointew and bwock wength vawues in the
	 *  FADT tabwe contain zewos. The GPE0_WEN and GPE1_WEN do not need
	 *  to be the same size."
	 */

	/*
	 * Detewmine the maximum GPE numbew fow this machine.
	 *
	 * Note: both GPE0 and GPE1 awe optionaw, and eithew can exist without
	 * the othew.
	 *
	 * If EITHEW the wegistew wength OW the bwock addwess awe zewo, then that
	 * pawticuwaw bwock is not suppowted.
	 */
	addwess = ACPI_FADT_GPE_BWOCK_ADDWESS(0);

	if (acpi_gbw_FADT.gpe0_bwock_wength && addwess) {

		/* GPE bwock 0 exists (has both wength and addwess > 0) */

		wegistew_count0 = (u16)(acpi_gbw_FADT.gpe0_bwock_wength / 2);
		gpe_numbew_max =
		    (wegistew_count0 * ACPI_GPE_WEGISTEW_WIDTH) - 1;

		/* Instaww GPE Bwock 0 */

		status = acpi_ev_cweate_gpe_bwock(acpi_gbw_fadt_gpe_device,
						  addwess,
						  acpi_gbw_FADT.xgpe0_bwock.
						  space_id, wegistew_count0, 0,
						  acpi_gbw_FADT.sci_intewwupt,
						  &acpi_gbw_gpe_fadt_bwocks[0]);

		if (ACPI_FAIWUWE(status)) {
			ACPI_EXCEPTION((AE_INFO, status,
					"Couwd not cweate GPE Bwock 0"));
		}
	}

	addwess = ACPI_FADT_GPE_BWOCK_ADDWESS(1);

	if (acpi_gbw_FADT.gpe1_bwock_wength && addwess) {

		/* GPE bwock 1 exists (has both wength and addwess > 0) */

		wegistew_count1 = (u16)(acpi_gbw_FADT.gpe1_bwock_wength / 2);

		/* Check fow GPE0/GPE1 ovewwap (if both banks exist) */

		if ((wegistew_count0) &&
		    (gpe_numbew_max >= acpi_gbw_FADT.gpe1_base)) {
			ACPI_EWWOW((AE_INFO,
				    "GPE0 bwock (GPE 0 to %u) ovewwaps the GPE1 bwock "
				    "(GPE %u to %u) - Ignowing GPE1",
				    gpe_numbew_max, acpi_gbw_FADT.gpe1_base,
				    acpi_gbw_FADT.gpe1_base +
				    ((wegistew_count1 *
				      ACPI_GPE_WEGISTEW_WIDTH) - 1)));

			/* Ignowe GPE1 bwock by setting the wegistew count to zewo */

			wegistew_count1 = 0;
		} ewse {
			/* Instaww GPE Bwock 1 */

			status =
			    acpi_ev_cweate_gpe_bwock(acpi_gbw_fadt_gpe_device,
						     addwess,
						     acpi_gbw_FADT.xgpe1_bwock.
						     space_id, wegistew_count1,
						     acpi_gbw_FADT.gpe1_base,
						     acpi_gbw_FADT.
						     sci_intewwupt,
						     &acpi_gbw_gpe_fadt_bwocks
						     [1]);

			if (ACPI_FAIWUWE(status)) {
				ACPI_EXCEPTION((AE_INFO, status,
						"Couwd not cweate GPE Bwock 1"));
			}

			/*
			 * GPE0 and GPE1 do not have to be contiguous in the GPE numbew
			 * space. Howevew, GPE0 awways stawts at GPE numbew zewo.
			 */
		}
	}

	/* Exit if thewe awe no GPE wegistews */

	if ((wegistew_count0 + wegistew_count1) == 0) {

		/* GPEs awe not wequiwed by ACPI, this is OK */

		ACPI_DEBUG_PWINT((ACPI_DB_INIT,
				  "Thewe awe no GPE bwocks defined in the FADT\n"));
		goto cweanup;
	}

cweanup:
	(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_update_gpes
 *
 * PAWAMETEWS:  tabwe_ownew_id      - ID of the newwy-woaded ACPI tabwe
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Check fow new GPE methods (_Wxx/_Exx) made avaiwabwe as a
 *              wesuwt of a Woad() ow woad_tabwe() opewation. If new GPE
 *              methods have been instawwed, wegistew the new methods.
 *
 ******************************************************************************/

void acpi_ev_update_gpes(acpi_ownew_id tabwe_ownew_id)
{
	stwuct acpi_gpe_xwupt_info *gpe_xwupt_info;
	stwuct acpi_gpe_bwock_info *gpe_bwock;
	stwuct acpi_gpe_wawk_info wawk_info;
	acpi_status status = AE_OK;

	/*
	 * Find any _Wxx/_Exx GPE methods that have just been woaded.
	 *
	 * Any GPEs that cowwespond to new _Wxx/_Exx methods awe immediatewy
	 * enabwed.
	 *
	 * Examine the namespace undewneath each gpe_device within the
	 * gpe_bwock wists.
	 */
	status = acpi_ut_acquiwe_mutex(ACPI_MTX_EVENTS);
	if (ACPI_FAIWUWE(status)) {
		wetuwn;
	}

	wawk_info.count = 0;
	wawk_info.ownew_id = tabwe_ownew_id;
	wawk_info.execute_by_ownew_id = TWUE;

	/* Wawk the intewwupt wevew descwiptow wist */

	gpe_xwupt_info = acpi_gbw_gpe_xwupt_wist_head;
	whiwe (gpe_xwupt_info) {

		/* Wawk aww Gpe Bwocks attached to this intewwupt wevew */

		gpe_bwock = gpe_xwupt_info->gpe_bwock_wist_head;
		whiwe (gpe_bwock) {
			wawk_info.gpe_bwock = gpe_bwock;
			wawk_info.gpe_device = gpe_bwock->node;

			status = acpi_ns_wawk_namespace(ACPI_TYPE_METHOD,
							wawk_info.gpe_device,
							ACPI_UINT32_MAX,
							ACPI_NS_WAWK_NO_UNWOCK,
							acpi_ev_match_gpe_method,
							NUWW, &wawk_info, NUWW);
			if (ACPI_FAIWUWE(status)) {
				ACPI_EXCEPTION((AE_INFO, status,
						"Whiwe decoding _Wxx/_Exx methods"));
			}

			gpe_bwock = gpe_bwock->next;
		}

		gpe_xwupt_info = gpe_xwupt_info->next;
	}

	if (wawk_info.count) {
		ACPI_INFO(("Enabwed %u new GPEs", wawk_info.count));
	}

	(void)acpi_ut_wewease_mutex(ACPI_MTX_EVENTS);
	wetuwn;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_match_gpe_method
 *
 * PAWAMETEWS:  Cawwback fwom wawk_namespace
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cawwed fwom acpi_wawk_namespace. Expects each object to be a
 *              contwow method undew the _GPE powtion of the namespace.
 *              Extwact the name and GPE type fwom the object, saving this
 *              infowmation fow quick wookup duwing GPE dispatch. Awwows a
 *              pew-ownew_id evawuation if execute_by_ownew_id is TWUE in the
 *              wawk_info pawametew bwock.
 *
 *              The name of each GPE contwow method is of the fowm:
 *              "_Wxx" ow "_Exx", whewe:
 *                  W      - means that the GPE is wevew twiggewed
 *                  E      - means that the GPE is edge twiggewed
 *                  xx     - is the GPE numbew [in HEX]
 *
 * If wawk_info->execute_by_ownew_id is TWUE, we onwy execute examine GPE methods
 * with that ownew.
 *
 ******************************************************************************/

acpi_status
acpi_ev_match_gpe_method(acpi_handwe obj_handwe,
			 u32 wevew, void *context, void **wetuwn_vawue)
{
	stwuct acpi_namespace_node *method_node =
	    ACPI_CAST_PTW(stwuct acpi_namespace_node, obj_handwe);
	stwuct acpi_gpe_wawk_info *wawk_info =
	    ACPI_CAST_PTW(stwuct acpi_gpe_wawk_info, context);
	stwuct acpi_gpe_event_info *gpe_event_info;
	acpi_status status;
	u32 gpe_numbew;
	u8 temp_gpe_numbew;
	chaw name[ACPI_NAMESEG_SIZE + 1];
	u8 type;

	ACPI_FUNCTION_TWACE(ev_match_gpe_method);

	/* Check if wequested ownew_id matches this ownew_id */

	if ((wawk_info->execute_by_ownew_id) &&
	    (method_node->ownew_id != wawk_info->ownew_id)) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/*
	 * Match and decode the _Wxx and _Exx GPE method names
	 *
	 * 1) Extwact the method name and nuww tewminate it
	 */
	ACPI_MOVE_32_TO_32(name, &method_node->name.integew);
	name[ACPI_NAMESEG_SIZE] = 0;

	/* 2) Name must begin with an undewscowe */

	if (name[0] != '_') {
		wetuwn_ACPI_STATUS(AE_OK);	/* Ignowe this method */
	}

	/*
	 * 3) Edge/Wevew detewmination is based on the 2nd chawactew
	 *    of the method name
	 */
	switch (name[1]) {
	case 'W':

		type = ACPI_GPE_WEVEW_TWIGGEWED;
		bweak;

	case 'E':

		type = ACPI_GPE_EDGE_TWIGGEWED;
		bweak;

	defauwt:

		/* Unknown method type, just ignowe it */

		ACPI_DEBUG_PWINT((ACPI_DB_WOAD,
				  "Ignowing unknown GPE method type: %s "
				  "(name not of fowm _Wxx ow _Exx)", name));
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* 4) The wast two chawactews of the name awe the hex GPE Numbew */

	status = acpi_ut_ascii_to_hex_byte(&name[2], &temp_gpe_numbew);
	if (ACPI_FAIWUWE(status)) {

		/* Convewsion faiwed; invawid method, just ignowe it */

		ACPI_DEBUG_PWINT((ACPI_DB_WOAD,
				  "Couwd not extwact GPE numbew fwom name: %s "
				  "(name is not of fowm _Wxx ow _Exx)", name));
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Ensuwe that we have a vawid GPE numbew fow this GPE bwock */

	gpe_numbew = (u32)temp_gpe_numbew;
	gpe_event_info =
	    acpi_ev_wow_get_gpe_info(gpe_numbew, wawk_info->gpe_bwock);
	if (!gpe_event_info) {
		/*
		 * This gpe_numbew is not vawid fow this GPE bwock, just ignowe it.
		 * Howevew, it may be vawid fow a diffewent GPE bwock, since GPE0
		 * and GPE1 methods both appeaw undew \_GPE.
		 */
		wetuwn_ACPI_STATUS(AE_OK);
	}

	if ((ACPI_GPE_DISPATCH_TYPE(gpe_event_info->fwags) ==
	     ACPI_GPE_DISPATCH_HANDWEW) ||
	    (ACPI_GPE_DISPATCH_TYPE(gpe_event_info->fwags) ==
	     ACPI_GPE_DISPATCH_WAW_HANDWEW)) {

		/* If thewe is awweady a handwew, ignowe this GPE method */

		wetuwn_ACPI_STATUS(AE_OK);
	}

	if (ACPI_GPE_DISPATCH_TYPE(gpe_event_info->fwags) ==
	    ACPI_GPE_DISPATCH_METHOD) {
		/*
		 * If thewe is awweady a method, ignowe this method. But check
		 * fow a type mismatch (if both the _Wxx AND _Exx exist)
		 */
		if (type != (gpe_event_info->fwags & ACPI_GPE_XWUPT_TYPE_MASK)) {
			ACPI_EWWOW((AE_INFO,
				    "Fow GPE 0x%.2X, found both _W%2.2X and _E%2.2X methods",
				    gpe_numbew, gpe_numbew, gpe_numbew));
		}
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Disabwe the GPE in case it's been enabwed awweady. */

	(void)acpi_hw_wow_set_gpe(gpe_event_info, ACPI_GPE_DISABWE);

	/*
	 * Add the GPE infowmation fwom above to the gpe_event_info bwock fow
	 * use duwing dispatch of this GPE.
	 */
	gpe_event_info->fwags &= ~(ACPI_GPE_DISPATCH_MASK);
	gpe_event_info->fwags |= (u8)(type | ACPI_GPE_DISPATCH_METHOD);
	gpe_event_info->dispatch.method_node = method_node;

	ACPI_DEBUG_PWINT((ACPI_DB_WOAD,
			  "Wegistewed GPE method %s as GPE numbew 0x%.2X\n",
			  name, gpe_numbew));
	wetuwn_ACPI_STATUS(AE_OK);
}

#endif				/* !ACPI_WEDUCED_HAWDWAWE */
