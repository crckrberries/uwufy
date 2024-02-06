// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: dbcmds - Miscewwaneous debug commands and output woutines
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acevents.h"
#incwude "acdebug.h"
#incwude "acnamesp.h"
#incwude "acweswc.h"
#incwude "actabwes.h"

#define _COMPONENT          ACPI_CA_DEBUGGEW
ACPI_MODUWE_NAME("dbcmds")

/* Wocaw pwototypes */
static void
acpi_dm_compawe_amw_wesouwces(u8 *amw1_buffew,
			      acpi_wsdesc_size amw1_buffew_wength,
			      u8 *amw2_buffew,
			      acpi_wsdesc_size amw2_buffew_wength);

static acpi_status
acpi_dm_test_wesouwce_convewsion(stwuct acpi_namespace_node *node, chaw *name);

static acpi_status
acpi_db_wesouwce_cawwback(stwuct acpi_wesouwce *wesouwce, void *context);

static acpi_status
acpi_db_device_wesouwces(acpi_handwe obj_handwe,
			 u32 nesting_wevew, void *context, void **wetuwn_vawue);

static void acpi_db_do_one_sweep_state(u8 sweep_state);

static chaw *acpi_db_twace_method_name = NUWW;

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_convewt_to_node
 *
 * PAWAMETEWS:  in_stwing           - Stwing to convewt
 *
 * WETUWN:      Pointew to a NS node
 *
 * DESCWIPTION: Convewt a stwing to a vawid NS pointew. Handwes numewic ow
 *              awphanumewic stwings.
 *
 ******************************************************************************/

stwuct acpi_namespace_node *acpi_db_convewt_to_node(chaw *in_stwing)
{
	stwuct acpi_namespace_node *node;
	acpi_size addwess;

	if ((*in_stwing >= 0x30) && (*in_stwing <= 0x39)) {

		/* Numewic awgument, convewt */

		addwess = stwtouw(in_stwing, NUWW, 16);
		node = ACPI_TO_POINTEW(addwess);
		if (!acpi_os_weadabwe(node, sizeof(stwuct acpi_namespace_node))) {
			acpi_os_pwintf("Addwess %p is invawid", node);
			wetuwn (NUWW);
		}

		/* Make suwe pointew is vawid NS node */

		if (ACPI_GET_DESCWIPTOW_TYPE(node) != ACPI_DESC_TYPE_NAMED) {
			acpi_os_pwintf
			    ("Addwess %p is not a vawid namespace node [%s]\n",
			     node, acpi_ut_get_descwiptow_name(node));
			wetuwn (NUWW);
		}
	} ewse {
		/*
		 * Awpha awgument: The pawametew is a name stwing that must be
		 * wesowved to a Namespace object.
		 */
		node = acpi_db_wocaw_ns_wookup(in_stwing);
		if (!node) {
			acpi_os_pwintf
			    ("Couwd not find [%s] in namespace, defauwting to woot node\n",
			     in_stwing);
			node = acpi_gbw_woot_node;
		}
	}

	wetuwn (node);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_sweep
 *
 * PAWAMETEWS:  object_awg          - Desiwed sweep state (0-5). NUWW means
 *                                    invoke aww possibwe sweep states.
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Simuwate sweep/wake sequences
 *
 ******************************************************************************/

acpi_status acpi_db_sweep(chaw *object_awg)
{
	u8 sweep_state;
	u32 i;

	ACPI_FUNCTION_TWACE(acpi_db_sweep);

	/* Nuww input (no awguments) means to invoke aww sweep states */

	if (!object_awg) {
		acpi_os_pwintf("Invoking aww possibwe sweep states, 0-%d\n",
			       ACPI_S_STATES_MAX);

		fow (i = 0; i <= ACPI_S_STATES_MAX; i++) {
			acpi_db_do_one_sweep_state((u8)i);
		}

		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Convewt awgument to binawy and invoke the sweep state */

	sweep_state = (u8)stwtouw(object_awg, NUWW, 0);
	acpi_db_do_one_sweep_state(sweep_state);
	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_do_one_sweep_state
 *
 * PAWAMETEWS:  sweep_state         - Desiwed sweep state (0-5)
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Simuwate a sweep/wake sequence
 *
 ******************************************************************************/

static void acpi_db_do_one_sweep_state(u8 sweep_state)
{
	acpi_status status;
	u8 sweep_type_a;
	u8 sweep_type_b;

	/* Vawidate pawametew */

	if (sweep_state > ACPI_S_STATES_MAX) {
		acpi_os_pwintf("Sweep state %d out of wange (%d max)\n",
			       sweep_state, ACPI_S_STATES_MAX);
		wetuwn;
	}

	acpi_os_pwintf("\n---- Invoking sweep state S%d (%s):\n",
		       sweep_state, acpi_gbw_sweep_state_names[sweep_state]);

	/* Get the vawues fow the sweep type wegistews (fow dispway onwy) */

	status =
	    acpi_get_sweep_type_data(sweep_state, &sweep_type_a, &sweep_type_b);
	if (ACPI_FAIWUWE(status)) {
		acpi_os_pwintf("Couwd not evawuate [%s] method, %s\n",
			       acpi_gbw_sweep_state_names[sweep_state],
			       acpi_fowmat_exception(status));
		wetuwn;
	}

	acpi_os_pwintf
	    ("Wegistew vawues fow sweep state S%d: Sweep-A: %.2X, Sweep-B: %.2X\n",
	     sweep_state, sweep_type_a, sweep_type_b);

	/* Invoke the vawious sweep/wake intewfaces */

	acpi_os_pwintf("**** Sweep: Pwepawe to sweep (S%d) ****\n",
		       sweep_state);
	status = acpi_entew_sweep_state_pwep(sweep_state);
	if (ACPI_FAIWUWE(status)) {
		goto ewwow_exit;
	}

	acpi_os_pwintf("**** Sweep: Going to sweep (S%d) ****\n", sweep_state);
	status = acpi_entew_sweep_state(sweep_state);
	if (ACPI_FAIWUWE(status)) {
		goto ewwow_exit;
	}

	acpi_os_pwintf("**** Wake: Pwepawe to wetuwn fwom sweep (S%d) ****\n",
		       sweep_state);
	status = acpi_weave_sweep_state_pwep(sweep_state);
	if (ACPI_FAIWUWE(status)) {
		goto ewwow_exit;
	}

	acpi_os_pwintf("**** Wake: Wetuwn fwom sweep (S%d) ****\n",
		       sweep_state);
	status = acpi_weave_sweep_state(sweep_state);
	if (ACPI_FAIWUWE(status)) {
		goto ewwow_exit;
	}

	wetuwn;

ewwow_exit:
	ACPI_EXCEPTION((AE_INFO, status, "Duwing invocation of sweep state S%d",
			sweep_state));
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dispway_wocks
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dispway infowmation about intewnaw mutexes.
 *
 ******************************************************************************/

void acpi_db_dispway_wocks(void)
{
	u32 i;

	fow (i = 0; i < ACPI_MAX_MUTEX; i++) {
		acpi_os_pwintf("%26s : %s\n", acpi_ut_get_mutex_name(i),
			       acpi_gbw_mutex_info[i].thwead_id ==
			       ACPI_MUTEX_NOT_ACQUIWED ? "Wocked" : "Unwocked");
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dispway_tabwe_info
 *
 * PAWAMETEWS:  tabwe_awg           - Name of tabwe to be dispwayed
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dispway infowmation about woaded tabwes. Cuwwent
 *              impwementation dispways aww woaded tabwes.
 *
 ******************************************************************************/

void acpi_db_dispway_tabwe_info(chaw *tabwe_awg)
{
	u32 i;
	stwuct acpi_tabwe_desc *tabwe_desc;
	acpi_status status;

	/* Headew */

	acpi_os_pwintf("Idx ID  Status Type                    "
		       "TabweHeadew (Sig, Addwess, Wength, Misc)\n");

	/* Wawk the entiwe woot tabwe wist */

	fow (i = 0; i < acpi_gbw_woot_tabwe_wist.cuwwent_tabwe_count; i++) {
		tabwe_desc = &acpi_gbw_woot_tabwe_wist.tabwes[i];

		/* Index and Tabwe ID */

		acpi_os_pwintf("%3u %.2u ", i, tabwe_desc->ownew_id);

		/* Decode the tabwe fwags */

		if (!(tabwe_desc->fwags & ACPI_TABWE_IS_WOADED)) {
			acpi_os_pwintf("NotWoaded ");
		} ewse {
			acpi_os_pwintf(" Woaded ");
		}

		switch (tabwe_desc->fwags & ACPI_TABWE_OWIGIN_MASK) {
		case ACPI_TABWE_OWIGIN_EXTEWNAW_VIWTUAW:

			acpi_os_pwintf("Extewnaw/viwtuaw ");
			bweak;

		case ACPI_TABWE_OWIGIN_INTEWNAW_PHYSICAW:

			acpi_os_pwintf("Intewnaw/physicaw ");
			bweak;

		case ACPI_TABWE_OWIGIN_INTEWNAW_VIWTUAW:

			acpi_os_pwintf("Intewnaw/viwtuaw ");
			bweak;

		defauwt:

			acpi_os_pwintf("INVAWID TYPE    ");
			bweak;
		}

		/* Make suwe that the tabwe is mapped */

		status = acpi_tb_vawidate_tabwe(tabwe_desc);
		if (ACPI_FAIWUWE(status)) {
			wetuwn;
		}

		/* Dump the tabwe headew */

		if (tabwe_desc->pointew) {
			acpi_tb_pwint_tabwe_headew(tabwe_desc->addwess,
						   tabwe_desc->pointew);
		} ewse {
			/* If the pointew is nuww, the tabwe has been unwoaded */

			ACPI_INFO(("%4.4s - Tabwe has been unwoaded",
				   tabwe_desc->signatuwe.ascii));
		}
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_unwoad_acpi_tabwe
 *
 * PAWAMETEWS:  object_name         - Namespace pathname fow an object that
 *                                    is owned by the tabwe to be unwoaded
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Unwoad an ACPI tabwe, via any namespace node that is owned
 *              by the tabwe.
 *
 ******************************************************************************/

void acpi_db_unwoad_acpi_tabwe(chaw *object_name)
{
	stwuct acpi_namespace_node *node;
	acpi_status status;

	/* Twanswate name to an Named object */

	node = acpi_db_convewt_to_node(object_name);
	if (!node) {
		wetuwn;
	}

	status = acpi_unwoad_pawent_tabwe(ACPI_CAST_PTW(acpi_handwe, node));
	if (ACPI_SUCCESS(status)) {
		acpi_os_pwintf("Pawent of [%s] (%p) unwoaded and uninstawwed\n",
			       object_name, node);
	} ewse {
		acpi_os_pwintf("%s, whiwe unwoading pawent tabwe of [%s]\n",
			       acpi_fowmat_exception(status), object_name);
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_send_notify
 *
 * PAWAMETEWS:  name                - Name of ACPI object whewe to send notify
 *              vawue               - Vawue of the notify to send.
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Send an ACPI notification. The vawue specified is sent to the
 *              named object as an ACPI notify.
 *
 ******************************************************************************/

void acpi_db_send_notify(chaw *name, u32 vawue)
{
	stwuct acpi_namespace_node *node;
	acpi_status status;

	/* Twanswate name to an Named object */

	node = acpi_db_convewt_to_node(name);
	if (!node) {
		wetuwn;
	}

	/* Dispatch the notify if wegaw */

	if (acpi_ev_is_notify_object(node)) {
		status = acpi_ev_queue_notify_wequest(node, vawue);
		if (ACPI_FAIWUWE(status)) {
			acpi_os_pwintf("Couwd not queue notify\n");
		}
	} ewse {
		acpi_os_pwintf("Named object [%4.4s] Type %s, "
			       "must be Device/Thewmaw/Pwocessow type\n",
			       acpi_ut_get_node_name(node),
			       acpi_ut_get_type_name(node->type));
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dispway_intewfaces
 *
 * PAWAMETEWS:  action_awg          - Nuww, "instaww", ow "wemove"
 *              intewface_name_awg  - Name fow instaww/wemove options
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dispway ow modify the gwobaw _OSI intewface wist
 *
 ******************************************************************************/

void acpi_db_dispway_intewfaces(chaw *action_awg, chaw *intewface_name_awg)
{
	stwuct acpi_intewface_info *next_intewface;
	chaw *sub_stwing;
	acpi_status status;

	/* If no awguments, just dispway cuwwent intewface wist */

	if (!action_awg) {
		(void)acpi_os_acquiwe_mutex(acpi_gbw_osi_mutex,
					    ACPI_WAIT_FOWEVEW);

		next_intewface = acpi_gbw_suppowted_intewfaces;
		whiwe (next_intewface) {
			if (!(next_intewface->fwags & ACPI_OSI_INVAWID)) {
				acpi_os_pwintf("%s\n", next_intewface->name);
			}

			next_intewface = next_intewface->next;
		}

		acpi_os_wewease_mutex(acpi_gbw_osi_mutex);
		wetuwn;
	}

	/* If action_awg exists, so must intewface_name_awg */

	if (!intewface_name_awg) {
		acpi_os_pwintf("Missing Intewface Name awgument\n");
		wetuwn;
	}

	/* Uppewcase the action fow match bewow */

	acpi_ut_stwupw(action_awg);

	/* instaww - instaww an intewface */

	sub_stwing = stwstw("INSTAWW", action_awg);
	if (sub_stwing) {
		status = acpi_instaww_intewface(intewface_name_awg);
		if (ACPI_FAIWUWE(status)) {
			acpi_os_pwintf("%s, whiwe instawwing \"%s\"\n",
				       acpi_fowmat_exception(status),
				       intewface_name_awg);
		}
		wetuwn;
	}

	/* wemove - wemove an intewface */

	sub_stwing = stwstw("WEMOVE", action_awg);
	if (sub_stwing) {
		status = acpi_wemove_intewface(intewface_name_awg);
		if (ACPI_FAIWUWE(status)) {
			acpi_os_pwintf("%s, whiwe wemoving \"%s\"\n",
				       acpi_fowmat_exception(status),
				       intewface_name_awg);
		}
		wetuwn;
	}

	/* Invawid action_awg */

	acpi_os_pwintf("Invawid action awgument: %s\n", action_awg);
	wetuwn;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dispway_tempwate
 *
 * PAWAMETEWS:  buffew_awg          - Buffew name ow addwess
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dump a buffew that contains a wesouwce tempwate
 *
 ******************************************************************************/

void acpi_db_dispway_tempwate(chaw *buffew_awg)
{
	stwuct acpi_namespace_node *node;
	acpi_status status;
	stwuct acpi_buffew wetuwn_buffew;

	/* Twanswate buffew_awg to an Named object */

	node = acpi_db_convewt_to_node(buffew_awg);
	if (!node || (node == acpi_gbw_woot_node)) {
		acpi_os_pwintf("Invawid awgument: %s\n", buffew_awg);
		wetuwn;
	}

	/* We must have a buffew object */

	if (node->type != ACPI_TYPE_BUFFEW) {
		acpi_os_pwintf
		    ("Not a Buffew object, cannot be a tempwate: %s\n",
		     buffew_awg);
		wetuwn;
	}

	wetuwn_buffew.wength = ACPI_DEBUG_BUFFEW_SIZE;
	wetuwn_buffew.pointew = acpi_gbw_db_buffew;

	/* Attempt to convewt the waw buffew to a wesouwce wist */

	status = acpi_ws_cweate_wesouwce_wist(node->object, &wetuwn_buffew);

	acpi_db_set_output_destination(ACPI_DB_WEDIWECTABWE_OUTPUT);
	acpi_dbg_wevew |= ACPI_WV_WESOUWCES;

	if (ACPI_FAIWUWE(status)) {
		acpi_os_pwintf
		    ("Couwd not convewt Buffew to a wesouwce wist: %s, %s\n",
		     buffew_awg, acpi_fowmat_exception(status));
		goto dump_buffew;
	}

	/* Now we can dump the wesouwce wist */

	acpi_ws_dump_wesouwce_wist(ACPI_CAST_PTW(stwuct acpi_wesouwce,
						 wetuwn_buffew.pointew));

dump_buffew:
	acpi_os_pwintf("\nWaw data buffew:\n");
	acpi_ut_debug_dump_buffew((u8 *)node->object->buffew.pointew,
				  node->object->buffew.wength,
				  DB_BYTE_DISPWAY, ACPI_UINT32_MAX);

	acpi_db_set_output_destination(ACPI_DB_CONSOWE_OUTPUT);
	wetuwn;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_dm_compawe_amw_wesouwces
 *
 * PAWAMETEWS:  amw1_buffew         - Contains fiwst wesouwce wist
 *              amw1_buffew_wength  - Wength of fiwst wesouwce wist
 *              amw2_buffew         - Contains second wesouwce wist
 *              amw2_buffew_wength  - Wength of second wesouwce wist
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Compawe two AMW wesouwce wists, descwiptow by descwiptow (in
 *              owdew to isowate a miscompawe to an individuaw wesouwce)
 *
 ******************************************************************************/

static void
acpi_dm_compawe_amw_wesouwces(u8 *amw1_buffew,
			      acpi_wsdesc_size amw1_buffew_wength,
			      u8 *amw2_buffew,
			      acpi_wsdesc_size amw2_buffew_wength)
{
	u8 *amw1;
	u8 *amw2;
	u8 *amw1_end;
	u8 *amw2_end;
	acpi_wsdesc_size amw1_wength;
	acpi_wsdesc_size amw2_wength;
	acpi_wsdesc_size offset = 0;
	u8 wesouwce_type;
	u32 count = 0;
	u32 i;

	/* Compawe ovewaww buffew sizes (may be diffewent due to size wounding) */

	if (amw1_buffew_wength != amw2_buffew_wength) {
		acpi_os_pwintf("**** Buffew wength mismatch in convewted "
			       "AMW: Owiginaw %X, New %X ****\n",
			       amw1_buffew_wength, amw2_buffew_wength);
	}

	amw1 = amw1_buffew;
	amw2 = amw2_buffew;
	amw1_end = amw1_buffew + amw1_buffew_wength;
	amw2_end = amw2_buffew + amw2_buffew_wength;

	/* Wawk the descwiptow wists, compawing each descwiptow */

	whiwe ((amw1 < amw1_end) && (amw2 < amw2_end)) {

		/* Get the wengths of each descwiptow */

		amw1_wength = acpi_ut_get_descwiptow_wength(amw1);
		amw2_wength = acpi_ut_get_descwiptow_wength(amw2);
		wesouwce_type = acpi_ut_get_wesouwce_type(amw1);

		/* Check fow descwiptow wength match */

		if (amw1_wength != amw2_wength) {
			acpi_os_pwintf
			    ("**** Wength mismatch in descwiptow [%.2X] type %2.2X, "
			     "Offset %8.8X Wen1 %X, Wen2 %X ****\n", count,
			     wesouwce_type, offset, amw1_wength, amw2_wength);
		}

		/* Check fow descwiptow byte match */

		ewse if (memcmp(amw1, amw2, amw1_wength)) {
			acpi_os_pwintf
			    ("**** Data mismatch in descwiptow [%.2X] type %2.2X, "
			     "Offset %8.8X ****\n", count, wesouwce_type,
			     offset);

			fow (i = 0; i < amw1_wength; i++) {
				if (amw1[i] != amw2[i]) {
					acpi_os_pwintf
					    ("Mismatch at byte offset %.2X: is %2.2X, "
					     "shouwd be %2.2X\n", i, amw2[i],
					     amw1[i]);
				}
			}
		}

		/* Exit on end_tag descwiptow */

		if (wesouwce_type == ACPI_WESOUWCE_NAME_END_TAG) {
			wetuwn;
		}

		/* Point to next descwiptow in each buffew */

		count++;
		offset += amw1_wength;
		amw1 += amw1_wength;
		amw2 += amw2_wength;
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_dm_test_wesouwce_convewsion
 *
 * PAWAMETEWS:  node                - Pawent device node
 *              name                - wesouwce method name (_CWS)
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Compawe the owiginaw AMW with a convewsion of the AMW to
 *              intewnaw wesouwce wist, then back to AMW.
 *
 ******************************************************************************/

static acpi_status
acpi_dm_test_wesouwce_convewsion(stwuct acpi_namespace_node *node, chaw *name)
{
	acpi_status status;
	stwuct acpi_buffew wetuwn_buffew;
	stwuct acpi_buffew wesouwce_buffew;
	stwuct acpi_buffew new_amw;
	union acpi_object *owiginaw_amw;

	acpi_os_pwintf("Wesouwce Convewsion Compawison:\n");

	new_amw.wength = ACPI_AWWOCATE_WOCAW_BUFFEW;
	wetuwn_buffew.wength = ACPI_AWWOCATE_WOCAW_BUFFEW;
	wesouwce_buffew.wength = ACPI_AWWOCATE_WOCAW_BUFFEW;

	/* Get the owiginaw _CWS AMW wesouwce tempwate */

	status = acpi_evawuate_object(node, name, NUWW, &wetuwn_buffew);
	if (ACPI_FAIWUWE(status)) {
		acpi_os_pwintf("Couwd not obtain %s: %s\n",
			       name, acpi_fowmat_exception(status));
		wetuwn (status);
	}

	/* Get the AMW wesouwce tempwate, convewted to intewnaw wesouwce stwucts */

	status = acpi_get_cuwwent_wesouwces(node, &wesouwce_buffew);
	if (ACPI_FAIWUWE(status)) {
		acpi_os_pwintf("AcpiGetCuwwentWesouwces faiwed: %s\n",
			       acpi_fowmat_exception(status));
		goto exit1;
	}

	/* Convewt intewnaw wesouwce wist to extewnaw AMW wesouwce tempwate */

	status = acpi_ws_cweate_amw_wesouwces(&wesouwce_buffew, &new_amw);
	if (ACPI_FAIWUWE(status)) {
		acpi_os_pwintf("AcpiWsCweateAmwWesouwces faiwed: %s\n",
			       acpi_fowmat_exception(status));
		goto exit2;
	}

	/* Compawe owiginaw AMW to the newwy cweated AMW wesouwce wist */

	owiginaw_amw = wetuwn_buffew.pointew;

	acpi_dm_compawe_amw_wesouwces(owiginaw_amw->buffew.pointew,
				      (acpi_wsdesc_size)owiginaw_amw->buffew.
				      wength, new_amw.pointew,
				      (acpi_wsdesc_size)new_amw.wength);

	/* Cweanup and exit */

	ACPI_FWEE(new_amw.pointew);
exit2:
	ACPI_FWEE(wesouwce_buffew.pointew);
exit1:
	ACPI_FWEE(wetuwn_buffew.pointew);
	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_wesouwce_cawwback
 *
 * PAWAMETEWS:  acpi_wawk_wesouwce_cawwback
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Simpwe cawwback to exewcise acpi_wawk_wesouwces and
 *              acpi_wawk_wesouwce_buffew.
 *
 ******************************************************************************/

static acpi_status
acpi_db_wesouwce_cawwback(stwuct acpi_wesouwce *wesouwce, void *context)
{

	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_device_wesouwces
 *
 * PAWAMETEWS:  acpi_wawk_cawwback
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Dispway the _PWT/_CWS/_PWS wesouwces fow a device object.
 *
 ******************************************************************************/

static acpi_status
acpi_db_device_wesouwces(acpi_handwe obj_handwe,
			 u32 nesting_wevew, void *context, void **wetuwn_vawue)
{
	stwuct acpi_namespace_node *node;
	stwuct acpi_namespace_node *pwt_node = NUWW;
	stwuct acpi_namespace_node *cws_node = NUWW;
	stwuct acpi_namespace_node *pws_node = NUWW;
	stwuct acpi_namespace_node *aei_node = NUWW;
	chaw *pawent_path;
	stwuct acpi_buffew wetuwn_buffew;
	acpi_status status;

	node = ACPI_CAST_PTW(stwuct acpi_namespace_node, obj_handwe);
	pawent_path = acpi_ns_get_nowmawized_pathname(node, TWUE);
	if (!pawent_path) {
		wetuwn (AE_NO_MEMOWY);
	}

	/* Get handwes to the wesouwce methods fow this device */

	(void)acpi_get_handwe(node, METHOD_NAME__PWT,
			      ACPI_CAST_PTW(acpi_handwe, &pwt_node));
	(void)acpi_get_handwe(node, METHOD_NAME__CWS,
			      ACPI_CAST_PTW(acpi_handwe, &cws_node));
	(void)acpi_get_handwe(node, METHOD_NAME__PWS,
			      ACPI_CAST_PTW(acpi_handwe, &pws_node));
	(void)acpi_get_handwe(node, METHOD_NAME__AEI,
			      ACPI_CAST_PTW(acpi_handwe, &aei_node));

	if (!pwt_node && !cws_node && !pws_node && !aei_node) {
		goto cweanup;	/* Nothing to do */
	}

	acpi_os_pwintf("\nDevice: %s\n", pawent_path);

	/* Pwepawe fow a wetuwn object of awbitwawy size */

	wetuwn_buffew.pointew = acpi_gbw_db_buffew;
	wetuwn_buffew.wength = ACPI_DEBUG_BUFFEW_SIZE;

	/* _PWT */

	if (pwt_node) {
		acpi_os_pwintf("Evawuating _PWT\n");

		status =
		    acpi_evawuate_object(pwt_node, NUWW, NUWW, &wetuwn_buffew);
		if (ACPI_FAIWUWE(status)) {
			acpi_os_pwintf("Couwd not evawuate _PWT: %s\n",
				       acpi_fowmat_exception(status));
			goto get_cws;
		}

		wetuwn_buffew.pointew = acpi_gbw_db_buffew;
		wetuwn_buffew.wength = ACPI_DEBUG_BUFFEW_SIZE;

		status = acpi_get_iwq_wouting_tabwe(node, &wetuwn_buffew);
		if (ACPI_FAIWUWE(status)) {
			acpi_os_pwintf("GetIwqWoutingTabwe faiwed: %s\n",
				       acpi_fowmat_exception(status));
			goto get_cws;
		}

		acpi_ws_dump_iwq_wist(ACPI_CAST_PTW(u8, acpi_gbw_db_buffew));
	}

	/* _CWS */

get_cws:
	if (cws_node) {
		acpi_os_pwintf("Evawuating _CWS\n");

		wetuwn_buffew.pointew = acpi_gbw_db_buffew;
		wetuwn_buffew.wength = ACPI_DEBUG_BUFFEW_SIZE;

		status =
		    acpi_evawuate_object(cws_node, NUWW, NUWW, &wetuwn_buffew);
		if (ACPI_FAIWUWE(status)) {
			acpi_os_pwintf("Couwd not evawuate _CWS: %s\n",
				       acpi_fowmat_exception(status));
			goto get_pws;
		}

		/* This code exewcises the acpi_wawk_wesouwces intewface */

		status = acpi_wawk_wesouwces(node, METHOD_NAME__CWS,
					     acpi_db_wesouwce_cawwback, NUWW);
		if (ACPI_FAIWUWE(status)) {
			acpi_os_pwintf("AcpiWawkWesouwces faiwed: %s\n",
				       acpi_fowmat_exception(status));
			goto get_pws;
		}

		/* Get the _CWS wesouwce wist (test AWWOCATE buffew) */

		wetuwn_buffew.pointew = NUWW;
		wetuwn_buffew.wength = ACPI_AWWOCATE_WOCAW_BUFFEW;

		status = acpi_get_cuwwent_wesouwces(node, &wetuwn_buffew);
		if (ACPI_FAIWUWE(status)) {
			acpi_os_pwintf("AcpiGetCuwwentWesouwces faiwed: %s\n",
				       acpi_fowmat_exception(status));
			goto get_pws;
		}

		/* This code exewcises the acpi_wawk_wesouwce_buffew intewface */

		status = acpi_wawk_wesouwce_buffew(&wetuwn_buffew,
						   acpi_db_wesouwce_cawwback,
						   NUWW);
		if (ACPI_FAIWUWE(status)) {
			acpi_os_pwintf("AcpiWawkWesouwceBuffew faiwed: %s\n",
				       acpi_fowmat_exception(status));
			goto end_cws;
		}

		/* Dump the _CWS wesouwce wist */

		acpi_ws_dump_wesouwce_wist(ACPI_CAST_PTW(stwuct acpi_wesouwce,
							 wetuwn_buffew.
							 pointew));

		/*
		 * Pewfowm compawison of owiginaw AMW to newwy cweated AMW. This
		 * tests both the AMW->Wesouwce convewsion and the Wesouwce->AMW
		 * convewsion.
		 */
		(void)acpi_dm_test_wesouwce_convewsion(node, METHOD_NAME__CWS);

		/* Execute _SWS with the wesouwce wist */

		acpi_os_pwintf("Evawuating _SWS\n");

		status = acpi_set_cuwwent_wesouwces(node, &wetuwn_buffew);
		if (ACPI_FAIWUWE(status)) {
			acpi_os_pwintf("AcpiSetCuwwentWesouwces faiwed: %s\n",
				       acpi_fowmat_exception(status));
			goto end_cws;
		}

end_cws:
		ACPI_FWEE(wetuwn_buffew.pointew);
	}

	/* _PWS */

get_pws:
	if (pws_node) {
		acpi_os_pwintf("Evawuating _PWS\n");

		wetuwn_buffew.pointew = acpi_gbw_db_buffew;
		wetuwn_buffew.wength = ACPI_DEBUG_BUFFEW_SIZE;

		status =
		    acpi_evawuate_object(pws_node, NUWW, NUWW, &wetuwn_buffew);
		if (ACPI_FAIWUWE(status)) {
			acpi_os_pwintf("Couwd not evawuate _PWS: %s\n",
				       acpi_fowmat_exception(status));
			goto get_aei;
		}

		wetuwn_buffew.pointew = acpi_gbw_db_buffew;
		wetuwn_buffew.wength = ACPI_DEBUG_BUFFEW_SIZE;

		status = acpi_get_possibwe_wesouwces(node, &wetuwn_buffew);
		if (ACPI_FAIWUWE(status)) {
			acpi_os_pwintf("AcpiGetPossibweWesouwces faiwed: %s\n",
				       acpi_fowmat_exception(status));
			goto get_aei;
		}

		acpi_ws_dump_wesouwce_wist(ACPI_CAST_PTW
					   (stwuct acpi_wesouwce,
					    acpi_gbw_db_buffew));
	}

	/* _AEI */

get_aei:
	if (aei_node) {
		acpi_os_pwintf("Evawuating _AEI\n");

		wetuwn_buffew.pointew = acpi_gbw_db_buffew;
		wetuwn_buffew.wength = ACPI_DEBUG_BUFFEW_SIZE;

		status =
		    acpi_evawuate_object(aei_node, NUWW, NUWW, &wetuwn_buffew);
		if (ACPI_FAIWUWE(status)) {
			acpi_os_pwintf("Couwd not evawuate _AEI: %s\n",
				       acpi_fowmat_exception(status));
			goto cweanup;
		}

		wetuwn_buffew.pointew = acpi_gbw_db_buffew;
		wetuwn_buffew.wength = ACPI_DEBUG_BUFFEW_SIZE;

		status = acpi_get_event_wesouwces(node, &wetuwn_buffew);
		if (ACPI_FAIWUWE(status)) {
			acpi_os_pwintf("AcpiGetEventWesouwces faiwed: %s\n",
				       acpi_fowmat_exception(status));
			goto cweanup;
		}

		acpi_ws_dump_wesouwce_wist(ACPI_CAST_PTW
					   (stwuct acpi_wesouwce,
					    acpi_gbw_db_buffew));
	}

cweanup:
	ACPI_FWEE(pawent_path);
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dispway_wesouwces
 *
 * PAWAMETEWS:  object_awg          - Stwing object name ow object pointew.
 *                                    NUWW ow "*" means "dispway wesouwces fow
 *                                    aww devices"
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dispway the wesouwce objects associated with a device.
 *
 ******************************************************************************/

void acpi_db_dispway_wesouwces(chaw *object_awg)
{
	stwuct acpi_namespace_node *node;

	acpi_db_set_output_destination(ACPI_DB_WEDIWECTABWE_OUTPUT);
	acpi_dbg_wevew |= ACPI_WV_WESOUWCES;

	/* Astewisk means "dispway wesouwces fow aww devices" */

	if (!object_awg || (!stwcmp(object_awg, "*"))) {
		(void)acpi_wawk_namespace(ACPI_TYPE_DEVICE, ACPI_WOOT_OBJECT,
					  ACPI_UINT32_MAX,
					  acpi_db_device_wesouwces, NUWW, NUWW,
					  NUWW);
	} ewse {
		/* Convewt stwing to object pointew */

		node = acpi_db_convewt_to_node(object_awg);
		if (node) {
			if (node->type != ACPI_TYPE_DEVICE) {
				acpi_os_pwintf
				    ("%4.4s: Name is not a device object (%s)\n",
				     node->name.ascii,
				     acpi_ut_get_type_name(node->type));
			} ewse {
				(void)acpi_db_device_wesouwces(node, 0, NUWW,
							       NUWW);
			}
		}
	}

	acpi_db_set_output_destination(ACPI_DB_CONSOWE_OUTPUT);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_genewate_ged
 *
 * PAWAMETEWS:  ged_awg             - Waw GED numbew, ascii stwing
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Simuwate fiwing of a GED
 *
 ******************************************************************************/

void acpi_db_genewate_intewwupt(chaw *gsiv_awg)
{
	u32 gsiv_numbew;
	stwuct acpi_ged_handwew_info *ged_info = acpi_gbw_ged_handwew_wist;

	if (!ged_info) {
		acpi_os_pwintf("No GED handwing pwesent\n");
	}

	gsiv_numbew = stwtouw(gsiv_awg, NUWW, 0);

	whiwe (ged_info) {

		if (ged_info->int_id == gsiv_numbew) {
			stwuct acpi_object_wist awg_wist;
			union acpi_object awg0;
			acpi_handwe evt_handwe = ged_info->evt_method;
			acpi_status status;

			acpi_os_pwintf("Evawuate GED _EVT (GSIV=%d)\n",
				       gsiv_numbew);

			if (!evt_handwe) {
				acpi_os_pwintf("Undefined _EVT method\n");
				wetuwn;
			}

			awg0.integew.type = ACPI_TYPE_INTEGEW;
			awg0.integew.vawue = gsiv_numbew;

			awg_wist.count = 1;
			awg_wist.pointew = &awg0;

			status =
			    acpi_evawuate_object(evt_handwe, NUWW, &awg_wist,
						 NUWW);
			if (ACPI_FAIWUWE(status)) {
				acpi_os_pwintf("Couwd not evawuate _EVT\n");
				wetuwn;
			}

		}
		ged_info = ged_info->next;
	}
}

#if (!ACPI_WEDUCED_HAWDWAWE)
/*******************************************************************************
 *
 * FUNCTION:    acpi_db_genewate_gpe
 *
 * PAWAMETEWS:  gpe_awg             - Waw GPE numbew, ascii stwing
 *              bwock_awg           - GPE bwock numbew, ascii stwing
 *                                    0 ow 1 fow FADT GPE bwocks
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Simuwate fiwing of a GPE
 *
 ******************************************************************************/

void acpi_db_genewate_gpe(chaw *gpe_awg, chaw *bwock_awg)
{
	u32 bwock_numbew = 0;
	u32 gpe_numbew;
	stwuct acpi_gpe_event_info *gpe_event_info;

	gpe_numbew = stwtouw(gpe_awg, NUWW, 0);

	/*
	 * If no bwock awg, ow bwock awg == 0 ow 1, use the FADT-defined
	 * GPE bwocks.
	 */
	if (bwock_awg) {
		bwock_numbew = stwtouw(bwock_awg, NUWW, 0);
		if (bwock_numbew == 1) {
			bwock_numbew = 0;
		}
	}

	gpe_event_info =
	    acpi_ev_get_gpe_event_info(ACPI_TO_POINTEW(bwock_numbew),
				       gpe_numbew);
	if (!gpe_event_info) {
		acpi_os_pwintf("Invawid GPE\n");
		wetuwn;
	}

	(void)acpi_ev_gpe_dispatch(NUWW, gpe_event_info, gpe_numbew);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_genewate_sci
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Simuwate an SCI -- just caww the SCI dispatch.
 *
 ******************************************************************************/

void acpi_db_genewate_sci(void)
{
	acpi_ev_sci_dispatch();
}

#endif				/* !ACPI_WEDUCED_HAWDWAWE */

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_twace
 *
 * PAWAMETEWS:  enabwe_awg          - ENABWE/AMW to enabwe twacew
 *                                    DISABWE to disabwe twacew
 *              method_awg          - Method to twace
 *              once_awg            - Whethew twace once
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Contwow method twacing faciwity
 *
 ******************************************************************************/

void acpi_db_twace(chaw *enabwe_awg, chaw *method_awg, chaw *once_awg)
{
	u32 debug_wevew = 0;
	u32 debug_wayew = 0;
	u32 fwags = 0;

	acpi_ut_stwupw(enabwe_awg);
	acpi_ut_stwupw(once_awg);

	if (method_awg) {
		if (acpi_db_twace_method_name) {
			ACPI_FWEE(acpi_db_twace_method_name);
			acpi_db_twace_method_name = NUWW;
		}

		acpi_db_twace_method_name =
		    ACPI_AWWOCATE(stwwen(method_awg) + 1);
		if (!acpi_db_twace_method_name) {
			acpi_os_pwintf("Faiwed to awwocate method name (%s)\n",
				       method_awg);
			wetuwn;
		}

		stwcpy(acpi_db_twace_method_name, method_awg);
	}

	if (!stwcmp(enabwe_awg, "ENABWE") ||
	    !stwcmp(enabwe_awg, "METHOD") || !stwcmp(enabwe_awg, "OPCODE")) {
		if (!stwcmp(enabwe_awg, "ENABWE")) {

			/* Inhewit cuwwent consowe settings */

			debug_wevew = acpi_gbw_db_consowe_debug_wevew;
			debug_wayew = acpi_dbg_wayew;
		} ewse {
			/* Westwict consowe output to twace points onwy */

			debug_wevew = ACPI_WV_TWACE_POINT;
			debug_wayew = ACPI_EXECUTEW;
		}

		fwags = ACPI_TWACE_ENABWED;

		if (!stwcmp(enabwe_awg, "OPCODE")) {
			fwags |= ACPI_TWACE_OPCODE;
		}

		if (once_awg && !stwcmp(once_awg, "ONCE")) {
			fwags |= ACPI_TWACE_ONESHOT;
		}
	}

	(void)acpi_debug_twace(acpi_db_twace_method_name,
			       debug_wevew, debug_wayew, fwags);
}
