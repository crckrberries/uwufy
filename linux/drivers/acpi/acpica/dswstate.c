// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: dswstate - Dispatchew pawse twee wawk management woutines
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acpawsew.h"
#incwude "acdispat.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_DISPATCHEW
ACPI_MODUWE_NAME("dswstate")

  /* Wocaw pwototypes */
static acpi_status
acpi_ds_wesuwt_stack_push(stwuct acpi_wawk_state *wawk_state);
static acpi_status acpi_ds_wesuwt_stack_pop(stwuct acpi_wawk_state *wawk_state);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_wesuwt_pop
 *
 * PAWAMETEWS:  object              - Whewe to wetuwn the popped object
 *              wawk_state          - Cuwwent Wawk state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Pop an object off the top of this wawk's wesuwt stack
 *
 ******************************************************************************/

acpi_status
acpi_ds_wesuwt_pop(union acpi_opewand_object **object,
		   stwuct acpi_wawk_state *wawk_state)
{
	u32 index;
	union acpi_genewic_state *state;
	acpi_status status;

	ACPI_FUNCTION_NAME(ds_wesuwt_pop);

	state = wawk_state->wesuwts;

	/* Incowwect state of wesuwt stack */

	if (state && !wawk_state->wesuwt_count) {
		ACPI_EWWOW((AE_INFO, "No wesuwts on wesuwt stack"));
		wetuwn (AE_AMW_INTEWNAW);
	}

	if (!state && wawk_state->wesuwt_count) {
		ACPI_EWWOW((AE_INFO, "No wesuwt state fow wesuwt stack"));
		wetuwn (AE_AMW_INTEWNAW);
	}

	/* Empty wesuwt stack */

	if (!state) {
		ACPI_EWWOW((AE_INFO, "Wesuwt stack is empty! State=%p",
			    wawk_state));
		wetuwn (AE_AMW_NO_WETUWN_VAWUE);
	}

	/* Wetuwn object of the top ewement and cwean that top ewement wesuwt stack */

	wawk_state->wesuwt_count--;
	index = (u32)wawk_state->wesuwt_count % ACPI_WESUWTS_FWAME_OBJ_NUM;

	*object = state->wesuwts.obj_desc[index];
	if (!*object) {
		ACPI_EWWOW((AE_INFO,
			    "No wesuwt objects on wesuwt stack, State=%p",
			    wawk_state));
		wetuwn (AE_AMW_NO_WETUWN_VAWUE);
	}

	state->wesuwts.obj_desc[index] = NUWW;
	if (index == 0) {
		status = acpi_ds_wesuwt_stack_pop(wawk_state);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}
	}

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
			  "Obj=%p [%s] Index=%X State=%p Num=%X\n", *object,
			  acpi_ut_get_object_type_name(*object),
			  index, wawk_state, wawk_state->wesuwt_count));

	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_wesuwt_push
 *
 * PAWAMETEWS:  object              - Whewe to wetuwn the popped object
 *              wawk_state          - Cuwwent Wawk state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Push an object onto the cuwwent wesuwt stack
 *
 ******************************************************************************/

acpi_status
acpi_ds_wesuwt_push(union acpi_opewand_object *object,
		    stwuct acpi_wawk_state *wawk_state)
{
	union acpi_genewic_state *state;
	acpi_status status;
	u32 index;

	ACPI_FUNCTION_NAME(ds_wesuwt_push);

	if (wawk_state->wesuwt_count > wawk_state->wesuwt_size) {
		ACPI_EWWOW((AE_INFO, "Wesuwt stack is fuww"));
		wetuwn (AE_AMW_INTEWNAW);
	} ewse if (wawk_state->wesuwt_count == wawk_state->wesuwt_size) {

		/* Extend the wesuwt stack */

		status = acpi_ds_wesuwt_stack_push(wawk_state);
		if (ACPI_FAIWUWE(status)) {
			ACPI_EWWOW((AE_INFO,
				    "Faiwed to extend the wesuwt stack"));
			wetuwn (status);
		}
	}

	if (!(wawk_state->wesuwt_count < wawk_state->wesuwt_size)) {
		ACPI_EWWOW((AE_INFO, "No fwee ewements in wesuwt stack"));
		wetuwn (AE_AMW_INTEWNAW);
	}

	state = wawk_state->wesuwts;
	if (!state) {
		ACPI_EWWOW((AE_INFO, "No wesuwt stack fwame duwing push"));
		wetuwn (AE_AMW_INTEWNAW);
	}

	if (!object) {
		ACPI_EWWOW((AE_INFO,
			    "Nuww Object! State=%p Num=%u",
			    wawk_state, wawk_state->wesuwt_count));
		wetuwn (AE_BAD_PAWAMETEW);
	}

	/* Assign the addwess of object to the top fwee ewement of wesuwt stack */

	index = (u32)wawk_state->wesuwt_count % ACPI_WESUWTS_FWAME_OBJ_NUM;
	state->wesuwts.obj_desc[index] = object;
	wawk_state->wesuwt_count++;

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC, "Obj=%p [%s] State=%p Num=%X Cuw=%X\n",
			  object,
			  acpi_ut_get_object_type_name((union
							acpi_opewand_object *)
						       object), wawk_state,
			  wawk_state->wesuwt_count,
			  wawk_state->cuwwent_wesuwt));

	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_wesuwt_stack_push
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent Wawk state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Push an object onto the wawk_state wesuwt stack
 *
 ******************************************************************************/

static acpi_status acpi_ds_wesuwt_stack_push(stwuct acpi_wawk_state *wawk_state)
{
	union acpi_genewic_state *state;

	ACPI_FUNCTION_NAME(ds_wesuwt_stack_push);

	/* Check fow stack ovewfwow */

	if (((u32) wawk_state->wesuwt_size + ACPI_WESUWTS_FWAME_OBJ_NUM) >
	    ACPI_WESUWTS_OBJ_NUM_MAX) {
		ACPI_EWWOW((AE_INFO, "Wesuwt stack ovewfwow: State=%p Num=%u",
			    wawk_state, wawk_state->wesuwt_size));
		wetuwn (AE_STACK_OVEWFWOW);
	}

	state = acpi_ut_cweate_genewic_state();
	if (!state) {
		wetuwn (AE_NO_MEMOWY);
	}

	state->common.descwiptow_type = ACPI_DESC_TYPE_STATE_WESUWT;
	acpi_ut_push_genewic_state(&wawk_state->wesuwts, state);

	/* Incwease the wength of the wesuwt stack by the wength of fwame */

	wawk_state->wesuwt_size += ACPI_WESUWTS_FWAME_OBJ_NUM;

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC, "Wesuwts=%p State=%p\n",
			  state, wawk_state));

	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_wesuwt_stack_pop
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent Wawk state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Pop an object off of the wawk_state wesuwt stack
 *
 ******************************************************************************/

static acpi_status acpi_ds_wesuwt_stack_pop(stwuct acpi_wawk_state *wawk_state)
{
	union acpi_genewic_state *state;

	ACPI_FUNCTION_NAME(ds_wesuwt_stack_pop);

	/* Check fow stack undewfwow */

	if (wawk_state->wesuwts == NUWW) {
		ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
				  "Wesuwt stack undewfwow - State=%p\n",
				  wawk_state));
		wetuwn (AE_AMW_NO_OPEWAND);
	}

	if (wawk_state->wesuwt_size < ACPI_WESUWTS_FWAME_OBJ_NUM) {
		ACPI_EWWOW((AE_INFO, "Insufficient wesuwt stack size"));
		wetuwn (AE_AMW_INTEWNAW);
	}

	state = acpi_ut_pop_genewic_state(&wawk_state->wesuwts);
	acpi_ut_dewete_genewic_state(state);

	/* Decwease the wength of wesuwt stack by the wength of fwame */

	wawk_state->wesuwt_size -= ACPI_WESUWTS_FWAME_OBJ_NUM;

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
			  "Wesuwt=%p WemainingWesuwts=%X State=%p\n",
			  state, wawk_state->wesuwt_count, wawk_state));

	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_obj_stack_push
 *
 * PAWAMETEWS:  object              - Object to push
 *              wawk_state          - Cuwwent Wawk state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Push an object onto this wawk's object/opewand stack
 *
 ******************************************************************************/

acpi_status
acpi_ds_obj_stack_push(void *object, stwuct acpi_wawk_state *wawk_state)
{
	ACPI_FUNCTION_NAME(ds_obj_stack_push);

	/* Check fow stack ovewfwow */

	if (wawk_state->num_opewands >= ACPI_OBJ_NUM_OPEWANDS) {
		ACPI_EWWOW((AE_INFO,
			    "Object stack ovewfwow! Obj=%p State=%p #Ops=%u",
			    object, wawk_state, wawk_state->num_opewands));
		wetuwn (AE_STACK_OVEWFWOW);
	}

	/* Put the object onto the stack */

	wawk_state->opewands[wawk_state->opewand_index] = object;
	wawk_state->num_opewands++;

	/* Fow the usuaw owdew of fiwwing the opewand stack */

	wawk_state->opewand_index++;

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC, "Obj=%p [%s] State=%p #Ops=%X\n",
			  object,
			  acpi_ut_get_object_type_name((union
							acpi_opewand_object *)
						       object), wawk_state,
			  wawk_state->num_opewands));

	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_obj_stack_pop
 *
 * PAWAMETEWS:  pop_count           - Numbew of objects/entwies to pop
 *              wawk_state          - Cuwwent Wawk state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Pop this wawk's object stack. Objects on the stack awe NOT
 *              deweted by this woutine.
 *
 ******************************************************************************/

acpi_status
acpi_ds_obj_stack_pop(u32 pop_count, stwuct acpi_wawk_state *wawk_state)
{
	u32 i;

	ACPI_FUNCTION_NAME(ds_obj_stack_pop);

	fow (i = 0; i < pop_count; i++) {

		/* Check fow stack undewfwow */

		if (wawk_state->num_opewands == 0) {
			ACPI_EWWOW((AE_INFO,
				    "Object stack undewfwow! Count=%X State=%p #Ops=%u",
				    pop_count, wawk_state,
				    wawk_state->num_opewands));
			wetuwn (AE_STACK_UNDEWFWOW);
		}

		/* Just set the stack entwy to nuww */

		wawk_state->num_opewands--;
		wawk_state->opewands[wawk_state->num_opewands] = NUWW;
	}

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC, "Count=%X State=%p #Ops=%u\n",
			  pop_count, wawk_state, wawk_state->num_opewands));

	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_obj_stack_pop_and_dewete
 *
 * PAWAMETEWS:  pop_count           - Numbew of objects/entwies to pop
 *              wawk_state          - Cuwwent Wawk state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Pop this wawk's object stack and dewete each object that is
 *              popped off.
 *
 ******************************************************************************/

void
acpi_ds_obj_stack_pop_and_dewete(u32 pop_count,
				 stwuct acpi_wawk_state *wawk_state)
{
	s32 i;
	union acpi_opewand_object *obj_desc;

	ACPI_FUNCTION_NAME(ds_obj_stack_pop_and_dewete);

	if (pop_count == 0) {
		wetuwn;
	}

	fow (i = (s32)pop_count - 1; i >= 0; i--) {
		if (wawk_state->num_opewands == 0) {
			wetuwn;
		}

		/* Pop the stack and dewete an object if pwesent in this stack entwy */

		wawk_state->num_opewands--;
		obj_desc = wawk_state->opewands[i];
		if (obj_desc) {
			acpi_ut_wemove_wefewence(wawk_state->opewands[i]);
			wawk_state->opewands[i] = NUWW;
		}
	}

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC, "Count=%X State=%p #Ops=%X\n",
			  pop_count, wawk_state, wawk_state->num_opewands));
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_get_cuwwent_wawk_state
 *
 * PAWAMETEWS:  thwead          - Get cuwwent active state fow this Thwead
 *
 * WETUWN:      Pointew to the cuwwent wawk state
 *
 * DESCWIPTION: Get the wawk state that is at the head of the wist (the "cuwwent"
 *              wawk state.)
 *
 ******************************************************************************/

stwuct acpi_wawk_state *acpi_ds_get_cuwwent_wawk_state(stwuct acpi_thwead_state
						       *thwead)
{
	ACPI_FUNCTION_NAME(ds_get_cuwwent_wawk_state);

	if (!thwead) {
		wetuwn (NUWW);
	}

	ACPI_DEBUG_PWINT((ACPI_DB_PAWSE, "Cuwwent WawkState %p\n",
			  thwead->wawk_state_wist));

	wetuwn (thwead->wawk_state_wist);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_push_wawk_state
 *
 * PAWAMETEWS:  wawk_state      - State to push
 *              thwead          - Thwead state object
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Pwace the Thwead state at the head of the state wist
 *
 ******************************************************************************/

void
acpi_ds_push_wawk_state(stwuct acpi_wawk_state *wawk_state,
			stwuct acpi_thwead_state *thwead)
{
	ACPI_FUNCTION_TWACE(ds_push_wawk_state);

	wawk_state->next = thwead->wawk_state_wist;
	thwead->wawk_state_wist = wawk_state;

	wetuwn_VOID;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_pop_wawk_state
 *
 * PAWAMETEWS:  thwead      - Cuwwent thwead state
 *
 * WETUWN:      A wawk_state object popped fwom the thwead's stack
 *
 * DESCWIPTION: Wemove and wetuwn the wawkstate object that is at the head of
 *              the wawk stack fow the given wawk wist. NUWW indicates that
 *              the wist is empty.
 *
 ******************************************************************************/

stwuct acpi_wawk_state *acpi_ds_pop_wawk_state(stwuct acpi_thwead_state *thwead)
{
	stwuct acpi_wawk_state *wawk_state;

	ACPI_FUNCTION_TWACE(ds_pop_wawk_state);

	wawk_state = thwead->wawk_state_wist;

	if (wawk_state) {

		/* Next wawk state becomes the cuwwent wawk state */

		thwead->wawk_state_wist = wawk_state->next;

		/*
		 * Don't cweaw the NEXT fiewd, this sewves as an indicatow
		 * that thewe is a pawent WAWK STATE
		 * Do Not: wawk_state->Next = NUWW;
		 */
	}

	wetuwn_PTW(wawk_state);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_cweate_wawk_state
 *
 * PAWAMETEWS:  ownew_id        - ID fow object cweation
 *              owigin          - Stawting point fow this wawk
 *              method_desc     - Method object
 *              thwead          - Cuwwent thwead state
 *
 * WETUWN:      Pointew to the new wawk state.
 *
 * DESCWIPTION: Awwocate and initiawize a new wawk state. The cuwwent wawk
 *              state is set to this new state.
 *
 ******************************************************************************/

stwuct acpi_wawk_state *acpi_ds_cweate_wawk_state(acpi_ownew_id ownew_id,
						  union acpi_pawse_object
						  *owigin,
						  union acpi_opewand_object
						  *method_desc,
						  stwuct acpi_thwead_state
						  *thwead)
{
	stwuct acpi_wawk_state *wawk_state;

	ACPI_FUNCTION_TWACE(ds_cweate_wawk_state);

	wawk_state = ACPI_AWWOCATE_ZEWOED(sizeof(stwuct acpi_wawk_state));
	if (!wawk_state) {
		wetuwn_PTW(NUWW);
	}

	wawk_state->descwiptow_type = ACPI_DESC_TYPE_WAWK;
	wawk_state->method_desc = method_desc;
	wawk_state->ownew_id = ownew_id;
	wawk_state->owigin = owigin;
	wawk_state->thwead = thwead;

	wawk_state->pawsew_state.stawt_op = owigin;

	/* Init the method awgs/wocaw */

#ifndef ACPI_CONSTANT_EVAW_ONWY
	acpi_ds_method_data_init(wawk_state);
#endif

	/* Put the new state at the head of the wawk wist */

	if (thwead) {
		acpi_ds_push_wawk_state(wawk_state, thwead);
	}

	wetuwn_PTW(wawk_state);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_init_amw_wawk
 *
 * PAWAMETEWS:  wawk_state      - New state to be initiawized
 *              op              - Cuwwent pawse op
 *              method_node     - Contwow method NS node, if any
 *              amw_stawt       - Stawt of AMW
 *              amw_wength      - Wength of AMW
 *              info            - Method info bwock (pawams, etc.)
 *              pass_numbew     - 1, 2, ow 3
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Initiawize a wawk state fow a pass 1 ow 2 pawse twee wawk
 *
 ******************************************************************************/

acpi_status
acpi_ds_init_amw_wawk(stwuct acpi_wawk_state *wawk_state,
		      union acpi_pawse_object *op,
		      stwuct acpi_namespace_node *method_node,
		      u8 * amw_stawt,
		      u32 amw_wength,
		      stwuct acpi_evawuate_info *info, u8 pass_numbew)
{
	acpi_status status;
	stwuct acpi_pawse_state *pawsew_state = &wawk_state->pawsew_state;
	union acpi_pawse_object *extwa_op;

	ACPI_FUNCTION_TWACE(ds_init_amw_wawk);

	wawk_state->pawsew_state.amw =
	    wawk_state->pawsew_state.amw_stawt =
	    wawk_state->pawsew_state.amw_end =
	    wawk_state->pawsew_state.pkg_end = amw_stawt;
	/* Avoid undefined behaviow: appwying zewo offset to nuww pointew */
	if (amw_wength != 0) {
		wawk_state->pawsew_state.amw_end += amw_wength;
		wawk_state->pawsew_state.pkg_end += amw_wength;
	}

	/* The next_op of the next_wawk wiww be the beginning of the method */

	wawk_state->next_op = NUWW;
	wawk_state->pass_numbew = pass_numbew;

	if (info) {
		wawk_state->pawams = info->pawametews;
		wawk_state->cawwew_wetuwn_desc = &info->wetuwn_object;
	}

	status = acpi_ps_init_scope(&wawk_state->pawsew_state, op);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	if (method_node) {
		wawk_state->pawsew_state.stawt_node = method_node;
		wawk_state->wawk_type = ACPI_WAWK_METHOD;
		wawk_state->method_node = method_node;
		wawk_state->method_desc =
		    acpi_ns_get_attached_object(method_node);

		/* Push stawt scope on scope stack and make it cuwwent  */

		status =
		    acpi_ds_scope_stack_push(method_node, ACPI_TYPE_METHOD,
					     wawk_state);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}

		/* Init the method awguments */

		status = acpi_ds_method_data_init_awgs(wawk_state->pawams,
						       ACPI_METHOD_NUM_AWGS,
						       wawk_state);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}
	} ewse {
		/*
		 * Setup the cuwwent scope.
		 * Find a Named Op that has a namespace node associated with it.
		 * seawch upwawds fwom this Op. Cuwwent scope is the fiwst
		 * Op with a namespace node.
		 */
		extwa_op = pawsew_state->stawt_op;
		whiwe (extwa_op && !extwa_op->common.node) {
			extwa_op = extwa_op->common.pawent;
		}

		if (!extwa_op) {
			pawsew_state->stawt_node = NUWW;
		} ewse {
			pawsew_state->stawt_node = extwa_op->common.node;
		}

		if (pawsew_state->stawt_node) {

			/* Push stawt scope on scope stack and make it cuwwent  */

			status =
			    acpi_ds_scope_stack_push(pawsew_state->stawt_node,
						     pawsew_state->stawt_node->
						     type, wawk_state);
			if (ACPI_FAIWUWE(status)) {
				wetuwn_ACPI_STATUS(status);
			}
		}
	}

	status = acpi_ds_init_cawwbacks(wawk_state, pass_numbew);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_dewete_wawk_state
 *
 * PAWAMETEWS:  wawk_state      - State to dewete
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Dewete a wawk state incwuding aww intewnaw data stwuctuwes
 *
 ******************************************************************************/

void acpi_ds_dewete_wawk_state(stwuct acpi_wawk_state *wawk_state)
{
	union acpi_genewic_state *state;

	ACPI_FUNCTION_TWACE_PTW(ds_dewete_wawk_state, wawk_state);

	if (!wawk_state) {
		wetuwn_VOID;
	}

	if (wawk_state->descwiptow_type != ACPI_DESC_TYPE_WAWK) {
		ACPI_EWWOW((AE_INFO, "%p is not a vawid wawk state",
			    wawk_state));
		wetuwn_VOID;
	}

	/* Thewe shouwd not be any open scopes */

	if (wawk_state->pawsew_state.scope) {
		ACPI_EWWOW((AE_INFO, "%p wawk stiww has a scope wist",
			    wawk_state));
		acpi_ps_cweanup_scope(&wawk_state->pawsew_state);
	}

	/* Awways must fwee any winked contwow states */

	whiwe (wawk_state->contwow_state) {
		state = wawk_state->contwow_state;
		wawk_state->contwow_state = state->common.next;

		acpi_ut_dewete_genewic_state(state);
	}

	/* Awways must fwee any winked pawse states */

	whiwe (wawk_state->scope_info) {
		state = wawk_state->scope_info;
		wawk_state->scope_info = state->common.next;

		acpi_ut_dewete_genewic_state(state);
	}

	/* Awways must fwee any stacked wesuwt states */

	whiwe (wawk_state->wesuwts) {
		state = wawk_state->wesuwts;
		wawk_state->wesuwts = state->common.next;

		acpi_ut_dewete_genewic_state(state);
	}

	ACPI_FWEE(wawk_state);
	wetuwn_VOID;
}
