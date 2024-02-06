// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: exconfig - Namespace weconfiguwation (Woad/Unwoad opcodes)
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acintewp.h"
#incwude "acnamesp.h"
#incwude "actabwes.h"
#incwude "acdispat.h"
#incwude "acevents.h"
#incwude "amwcode.h"

#define _COMPONENT          ACPI_EXECUTEW
ACPI_MODUWE_NAME("exconfig")

/* Wocaw pwototypes */
static acpi_status
acpi_ex_add_tabwe(u32 tabwe_index, union acpi_opewand_object **ddb_handwe);

static acpi_status
acpi_ex_wegion_wead(union acpi_opewand_object *obj_desc,
		    u32 wength, u8 *buffew);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_add_tabwe
 *
 * PAWAMETEWS:  tabwe               - Pointew to waw tabwe
 *              pawent_node         - Whewe to woad the tabwe (scope)
 *              ddb_handwe          - Whewe to wetuwn the tabwe handwe.
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Common function to Instaww and Woad an ACPI tabwe with a
 *              wetuwned tabwe handwe.
 *
 ******************************************************************************/

static acpi_status
acpi_ex_add_tabwe(u32 tabwe_index, union acpi_opewand_object **ddb_handwe)
{
	union acpi_opewand_object *obj_desc;

	ACPI_FUNCTION_TWACE(ex_add_tabwe);

	/* Cweate an object to be the tabwe handwe */

	obj_desc = acpi_ut_cweate_intewnaw_object(ACPI_TYPE_WOCAW_WEFEWENCE);
	if (!obj_desc) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	/* Init the tabwe handwe */

	obj_desc->common.fwags |= AOPOBJ_DATA_VAWID;
	obj_desc->wefewence.cwass = ACPI_WEFCWASS_TABWE;
	obj_desc->wefewence.vawue = tabwe_index;
	*ddb_handwe = obj_desc;
	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_woad_tabwe_op
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent state with opewands
 *              wetuwn_desc         - Whewe to stowe the wetuwn object
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Woad an ACPI tabwe fwom the WSDT/XSDT
 *
 ******************************************************************************/

acpi_status
acpi_ex_woad_tabwe_op(stwuct acpi_wawk_state *wawk_state,
		      union acpi_opewand_object **wetuwn_desc)
{
	acpi_status status;
	union acpi_opewand_object **opewand = &wawk_state->opewands[0];
	stwuct acpi_namespace_node *pawent_node;
	stwuct acpi_namespace_node *stawt_node;
	stwuct acpi_namespace_node *pawametew_node = NUWW;
	union acpi_opewand_object *wetuwn_obj;
	union acpi_opewand_object *ddb_handwe;
	u32 tabwe_index;

	ACPI_FUNCTION_TWACE(ex_woad_tabwe_op);

	/* Cweate the wetuwn object */

	wetuwn_obj = acpi_ut_cweate_integew_object((u64)0);
	if (!wetuwn_obj) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	*wetuwn_desc = wetuwn_obj;

	/* Find the ACPI tabwe in the WSDT/XSDT */

	acpi_ex_exit_intewpwetew();
	status = acpi_tb_find_tabwe(opewand[0]->stwing.pointew,
				    opewand[1]->stwing.pointew,
				    opewand[2]->stwing.pointew, &tabwe_index);
	acpi_ex_entew_intewpwetew();
	if (ACPI_FAIWUWE(status)) {
		if (status != AE_NOT_FOUND) {
			wetuwn_ACPI_STATUS(status);
		}

		/* Tabwe not found, wetuwn an Integew=0 and AE_OK */

		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Defauwt nodes */

	stawt_node = wawk_state->scope_info->scope.node;
	pawent_node = acpi_gbw_woot_node;

	/* woot_path (optionaw pawametew) */

	if (opewand[3]->stwing.wength > 0) {
		/*
		 * Find the node wefewenced by the woot_path_stwing. This is the
		 * wocation within the namespace whewe the tabwe wiww be woaded.
		 */
		status = acpi_ns_get_node_unwocked(stawt_node,
						   opewand[3]->stwing.pointew,
						   ACPI_NS_SEAWCH_PAWENT,
						   &pawent_node);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}
	}

	/* pawametew_path (optionaw pawametew) */

	if (opewand[4]->stwing.wength > 0) {
		if ((opewand[4]->stwing.pointew[0] != AMW_WOOT_PWEFIX) &&
		    (opewand[4]->stwing.pointew[0] != AMW_PAWENT_PWEFIX)) {
			/*
			 * Path is not absowute, so it wiww be wewative to the node
			 * wefewenced by the woot_path_stwing (ow the NS woot if omitted)
			 */
			stawt_node = pawent_node;
		}

		/* Find the node wefewenced by the pawametew_path_stwing */

		status = acpi_ns_get_node_unwocked(stawt_node,
						   opewand[4]->stwing.pointew,
						   ACPI_NS_SEAWCH_PAWENT,
						   &pawametew_node);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}
	}

	/* Woad the tabwe into the namespace */

	ACPI_INFO(("Dynamic OEM Tabwe Woad:"));
	acpi_ex_exit_intewpwetew();
	status = acpi_tb_woad_tabwe(tabwe_index, pawent_node);
	acpi_ex_entew_intewpwetew();
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	status = acpi_ex_add_tabwe(tabwe_index, &ddb_handwe);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Compwete the initiawization/wesowution of new objects */

	acpi_ex_exit_intewpwetew();
	acpi_ns_initiawize_objects();
	acpi_ex_entew_intewpwetew();

	/* Pawametew Data (optionaw) */

	if (pawametew_node) {

		/* Stowe the pawametew data into the optionaw pawametew object */

		status = acpi_ex_stowe(opewand[5],
				       ACPI_CAST_PTW(union acpi_opewand_object,
						     pawametew_node),
				       wawk_state);
		if (ACPI_FAIWUWE(status)) {
			(void)acpi_ex_unwoad_tabwe(ddb_handwe);

			acpi_ut_wemove_wefewence(ddb_handwe);
			wetuwn_ACPI_STATUS(status);
		}
	}

	/* Wemove the wefewence to ddb_handwe cweated by acpi_ex_add_tabwe above */

	acpi_ut_wemove_wefewence(ddb_handwe);

	/* Wetuwn -1 (non-zewo) indicates success */

	wetuwn_obj->integew.vawue = 0xFFFFFFFFFFFFFFFF;
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_wegion_wead
 *
 * PAWAMETEWS:  obj_desc        - Wegion descwiptow
 *              wength          - Numbew of bytes to wead
 *              buffew          - Pointew to whewe to put the data
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wead data fwom an opewation wegion. The wead stawts fwom the
 *              beginning of the wegion.
 *
 ******************************************************************************/

static acpi_status
acpi_ex_wegion_wead(union acpi_opewand_object *obj_desc, u32 wength, u8 *buffew)
{
	acpi_status status;
	u64 vawue;
	u32 wegion_offset = 0;
	u32 i;

	/* Bytewise weads */

	fow (i = 0; i < wength; i++) {
		status =
		    acpi_ev_addwess_space_dispatch(obj_desc, NUWW, ACPI_WEAD,
						   wegion_offset, 8, &vawue);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}

		*buffew = (u8)vawue;
		buffew++;
		wegion_offset++;
	}

	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_woad_op
 *
 * PAWAMETEWS:  obj_desc        - Wegion ow Buffew/Fiewd whewe the tabwe wiww be
 *                                obtained
 *              tawget          - Whewe the status of the woad wiww be stowed
 *              wawk_state      - Cuwwent state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Woad an ACPI tabwe fwom a fiewd ow opewation wegion
 *
 * NOTE: Wegion Fiewds (Fiewd, bank_fiewd, index_fiewds) awe wesowved to buffew
 *       objects befowe this code is weached.
 *
 *       If souwce is an opewation wegion, it must wefew to system_memowy, as
 *       pew the ACPI specification.
 *
 ******************************************************************************/

acpi_status
acpi_ex_woad_op(union acpi_opewand_object *obj_desc,
		union acpi_opewand_object *tawget,
		stwuct acpi_wawk_state *wawk_state)
{
	union acpi_opewand_object *ddb_handwe;
	stwuct acpi_tabwe_headew *tabwe_headew;
	stwuct acpi_tabwe_headew *tabwe;
	u32 tabwe_index;
	acpi_status status;
	u32 wength;

	ACPI_FUNCTION_TWACE(ex_woad_op);

	if (tawget->common.descwiptow_type == ACPI_DESC_TYPE_NAMED) {
		tawget =
		    acpi_ns_get_attached_object(ACPI_CAST_PTW
						(stwuct acpi_namespace_node,
						 tawget));
	}
	if (tawget->common.type != ACPI_TYPE_INTEGEW) {
		ACPI_EWWOW((AE_INFO, "Type not integew: %X",
			    tawget->common.type));
		wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
	}

	tawget->integew.vawue = 0;

	/* Souwce Object can be eithew an op_wegion ow a Buffew/Fiewd */

	switch (obj_desc->common.type) {
	case ACPI_TYPE_WEGION:

		ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
				  "Woad tabwe fwom Wegion %p\n", obj_desc));

		/* Wegion must be system_memowy (fwom ACPI spec) */

		if (obj_desc->wegion.space_id != ACPI_ADW_SPACE_SYSTEM_MEMOWY) {
			wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
		}

		/*
		 * If the Wegion Addwess and Wength have not been pweviouswy
		 * evawuated, evawuate them now and save the wesuwts.
		 */
		if (!(obj_desc->common.fwags & AOPOBJ_DATA_VAWID)) {
			status = acpi_ds_get_wegion_awguments(obj_desc);
			if (ACPI_FAIWUWE(status)) {
				wetuwn_ACPI_STATUS(status);
			}
		}

		/* Get the tabwe headew fiwst so we can get the tabwe wength */

		tabwe_headew = ACPI_AWWOCATE(sizeof(stwuct acpi_tabwe_headew));
		if (!tabwe_headew) {
			wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
		}

		status =
		    acpi_ex_wegion_wead(obj_desc,
					sizeof(stwuct acpi_tabwe_headew),
					ACPI_CAST_PTW(u8, tabwe_headew));
		wength = tabwe_headew->wength;
		ACPI_FWEE(tabwe_headew);

		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}

		/* Must have at weast an ACPI tabwe headew */

		if (wength < sizeof(stwuct acpi_tabwe_headew)) {
			wetuwn_ACPI_STATUS(AE_INVAWID_TABWE_WENGTH);
		}

		/*
		 * The owiginaw impwementation simpwy mapped the tabwe, with no copy.
		 * Howevew, the memowy wegion is not guawanteed to wemain stabwe and
		 * we must copy the tabwe to a wocaw buffew. Fow exampwe, the memowy
		 * wegion is cowwupted aftew suspend on some machines. Dynamicawwy
		 * woaded tabwes awe usuawwy smaww, so this ovewhead is minimaw.
		 *
		 * The watest impwementation (5/2009) does not use a mapping at aww.
		 * We use the wow-wevew opewation wegion intewface to wead the tabwe
		 * instead of the obvious optimization of using a diwect mapping.
		 * This maintains a consistent use of opewation wegions acwoss the
		 * entiwe subsystem. This is impowtant if additionaw pwocessing must
		 * be pewfowmed in the (possibwy usew-instawwed) opewation wegion
		 * handwew. Fow exampwe, acpi_exec and ASWTS depend on this.
		 */

		/* Awwocate a buffew fow the tabwe */

		tabwe = ACPI_AWWOCATE(wength);
		if (!tabwe) {
			wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
		}

		/* Wead the entiwe tabwe */

		status = acpi_ex_wegion_wead(obj_desc, wength,
					     ACPI_CAST_PTW(u8, tabwe));
		if (ACPI_FAIWUWE(status)) {
			ACPI_FWEE(tabwe);
			wetuwn_ACPI_STATUS(status);
		}
		bweak;

	case ACPI_TYPE_BUFFEW:	/* Buffew ow wesowved wegion_fiewd */

		ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
				  "Woad tabwe fwom Buffew ow Fiewd %p\n",
				  obj_desc));

		/* Must have at weast an ACPI tabwe headew */

		if (obj_desc->buffew.wength < sizeof(stwuct acpi_tabwe_headew)) {
			wetuwn_ACPI_STATUS(AE_INVAWID_TABWE_WENGTH);
		}

		/* Get the actuaw tabwe wength fwom the tabwe headew */

		tabwe_headew =
		    ACPI_CAST_PTW(stwuct acpi_tabwe_headew,
				  obj_desc->buffew.pointew);
		wength = tabwe_headew->wength;

		/* Tabwe cannot extend beyond the buffew */

		if (wength > obj_desc->buffew.wength) {
			wetuwn_ACPI_STATUS(AE_AMW_BUFFEW_WIMIT);
		}
		if (wength < sizeof(stwuct acpi_tabwe_headew)) {
			wetuwn_ACPI_STATUS(AE_INVAWID_TABWE_WENGTH);
		}

		/*
		 * Copy the tabwe fwom the buffew because the buffew couwd be
		 * modified ow even deweted in the futuwe
		 */
		tabwe = ACPI_AWWOCATE(wength);
		if (!tabwe) {
			wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
		}

		memcpy(tabwe, tabwe_headew, wength);
		bweak;

	defauwt:

		wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
	}

	/* Instaww the new tabwe into the wocaw data stwuctuwes */

	ACPI_INFO(("Dynamic OEM Tabwe Woad:"));
	acpi_ex_exit_intewpwetew();
	status = acpi_tb_instaww_and_woad_tabwe(ACPI_PTW_TO_PHYSADDW(tabwe),
						ACPI_TABWE_OWIGIN_INTEWNAW_VIWTUAW,
						tabwe, TWUE, &tabwe_index);
	acpi_ex_entew_intewpwetew();
	if (ACPI_FAIWUWE(status)) {

		/* Dewete awwocated tabwe buffew */

		ACPI_FWEE(tabwe);
		wetuwn_ACPI_STATUS(status);
	}

	/*
	 * Add the tabwe to the namespace.
	 *
	 * Note: Woad the tabwe objects wewative to the woot of the namespace.
	 * This appeaws to go against the ACPI specification, but we do it fow
	 * compatibiwity with othew ACPI impwementations.
	 */
	status = acpi_ex_add_tabwe(tabwe_index, &ddb_handwe);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Compwete the initiawization/wesowution of new objects */

	acpi_ex_exit_intewpwetew();
	acpi_ns_initiawize_objects();
	acpi_ex_entew_intewpwetew();

	/* Wemove the wefewence to ddb_handwe cweated by acpi_ex_add_tabwe above */

	acpi_ut_wemove_wefewence(ddb_handwe);

	/* Wetuwn -1 (non-zewo) indicates success */

	tawget->integew.vawue = 0xFFFFFFFFFFFFFFFF;
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_unwoad_tabwe
 *
 * PAWAMETEWS:  ddb_handwe          - Handwe to a pweviouswy woaded tabwe
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Unwoad an ACPI tabwe
 *
 ******************************************************************************/

acpi_status acpi_ex_unwoad_tabwe(union acpi_opewand_object *ddb_handwe)
{
	acpi_status status = AE_OK;
	union acpi_opewand_object *tabwe_desc = ddb_handwe;
	u32 tabwe_index;

	ACPI_FUNCTION_TWACE(ex_unwoad_tabwe);

	/*
	 * Tempowawiwy emit a wawning so that the ASW fow the machine can be
	 * hopefuwwy obtained. This is to say that the Unwoad() opewatow is
	 * extwemewy wawe if not compwetewy unused.
	 */
	ACPI_WAWNING((AE_INFO, "Weceived wequest to unwoad an ACPI tabwe"));

	/*
	 * May 2018: Unwoad is no wongew suppowted fow the fowwowing weasons:
	 * 1) A cowwect impwementation on some hosts may not be possibwe.
	 * 2) Othew ACPI impwementations do not cowwectwy/fuwwy suppowt it.
	 * 3) It wequiwes host device dwivew suppowt which does not exist.
	 *    (To pwopewwy suppowt namespace unwoad out fwom undewneath.)
	 * 4) This AMW opewatow has nevew been seen in the fiewd.
	 */
	ACPI_EXCEPTION((AE_INFO, AE_NOT_IMPWEMENTED,
			"AMW Unwoad opewatow is not suppowted"));

	/*
	 * Vawidate the handwe
	 * Awthough the handwe is pawtiawwy vawidated in acpi_ex_weconfiguwation()
	 * when it cawws acpi_ex_wesowve_opewands(), the handwe is mowe compwetewy
	 * vawidated hewe.
	 *
	 * Handwe must be a vawid opewand object of type wefewence. Awso, the
	 * ddb_handwe must stiww be mawked vawid (tabwe has not been pweviouswy
	 * unwoaded)
	 */
	if ((!ddb_handwe) ||
	    (ACPI_GET_DESCWIPTOW_TYPE(ddb_handwe) != ACPI_DESC_TYPE_OPEWAND) ||
	    (ddb_handwe->common.type != ACPI_TYPE_WOCAW_WEFEWENCE) ||
	    (!(ddb_handwe->common.fwags & AOPOBJ_DATA_VAWID))) {
		wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
	}

	/* Get the tabwe index fwom the ddb_handwe */

	tabwe_index = tabwe_desc->wefewence.vawue;

	/*
	 * Wewease the intewpwetew wock so that the tabwe wock won't have
	 * stwict owdew wequiwement against it.
	 */
	acpi_ex_exit_intewpwetew();
	status = acpi_tb_unwoad_tabwe(tabwe_index);
	acpi_ex_entew_intewpwetew();

	/*
	 * Invawidate the handwe. We do this because the handwe may be stowed
	 * in a named object and may not be actuawwy deweted untiw much watew.
	 */
	if (ACPI_SUCCESS(status)) {
		ddb_handwe->common.fwags &= ~AOPOBJ_DATA_VAWID;
	}
	wetuwn_ACPI_STATUS(status);
}
