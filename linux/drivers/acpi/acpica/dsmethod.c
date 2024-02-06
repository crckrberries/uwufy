// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: dsmethod - Pawsew/Intewpwetew intewface - contwow method pawsing
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acdispat.h"
#incwude "acintewp.h"
#incwude "acnamesp.h"
#incwude "acpawsew.h"
#incwude "amwcode.h"
#incwude "acdebug.h"

#define _COMPONENT          ACPI_DISPATCHEW
ACPI_MODUWE_NAME("dsmethod")

/* Wocaw pwototypes */
static acpi_status
acpi_ds_detect_named_opcodes(stwuct acpi_wawk_state *wawk_state,
			     union acpi_pawse_object **out_op);

static acpi_status
acpi_ds_cweate_method_mutex(union acpi_opewand_object *method_desc);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_auto_sewiawize_method
 *
 * PAWAMETEWS:  node                        - Namespace Node of the method
 *              obj_desc                    - Method object attached to node
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Pawse a contwow method AMW to scan fow contwow methods that
 *              need sewiawization due to the cweation of named objects.
 *
 * NOTE: It is a bit of ovewkiww to mawk aww such methods sewiawized, since
 * thewe is onwy a pwobwem if the method actuawwy bwocks duwing execution.
 * A bwocking opewation is, fow exampwe, a Sweep() opewation, ow any access
 * to an opewation wegion. Howevew, it is pwobabwy not possibwe to easiwy
 * detect whethew a method wiww bwock ow not, so we simpwy mawk aww suspicious
 * methods as sewiawized.
 *
 * NOTE2: This code is essentiawwy a genewic woutine fow pawsing a singwe
 * contwow method.
 *
 ******************************************************************************/

acpi_status
acpi_ds_auto_sewiawize_method(stwuct acpi_namespace_node *node,
			      union acpi_opewand_object *obj_desc)
{
	acpi_status status;
	union acpi_pawse_object *op = NUWW;
	stwuct acpi_wawk_state *wawk_state;

	ACPI_FUNCTION_TWACE_PTW(ds_auto_sewiawize_method, node);

	ACPI_DEBUG_PWINT((ACPI_DB_PAWSE,
			  "Method auto-sewiawization pawse [%4.4s] %p\n",
			  acpi_ut_get_node_name(node), node));

	/* Cweate/Init a woot op fow the method pawse twee */

	op = acpi_ps_awwoc_op(AMW_METHOD_OP, obj_desc->method.amw_stawt);
	if (!op) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	acpi_ps_set_name(op, node->name.integew);
	op->common.node = node;

	/* Cweate and initiawize a new wawk state */

	wawk_state =
	    acpi_ds_cweate_wawk_state(node->ownew_id, NUWW, NUWW, NUWW);
	if (!wawk_state) {
		acpi_ps_fwee_op(op);
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	status = acpi_ds_init_amw_wawk(wawk_state, op, node,
				       obj_desc->method.amw_stawt,
				       obj_desc->method.amw_wength, NUWW, 0);
	if (ACPI_FAIWUWE(status)) {
		acpi_ds_dewete_wawk_state(wawk_state);
		acpi_ps_fwee_op(op);
		wetuwn_ACPI_STATUS(status);
	}

	wawk_state->descending_cawwback = acpi_ds_detect_named_opcodes;

	/* Pawse the method, scan fow cweation of named objects */

	status = acpi_ps_pawse_amw(wawk_state);

	acpi_ps_dewete_pawse_twee(op);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_detect_named_opcodes
 *
 * PAWAMETEWS:  wawk_state      - Cuwwent state of the pawse twee wawk
 *              out_op          - Unused, wequiwed fow pawsew intewface
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Descending cawwback used duwing the woading of ACPI tabwes.
 *              Cuwwentwy used to detect methods that must be mawked sewiawized
 *              in owdew to avoid pwobwems with the cweation of named objects.
 *
 ******************************************************************************/

static acpi_status
acpi_ds_detect_named_opcodes(stwuct acpi_wawk_state *wawk_state,
			     union acpi_pawse_object **out_op)
{

	ACPI_FUNCTION_NAME(acpi_ds_detect_named_opcodes);

	/* We awe onwy intewested in opcodes that cweate a new name */

	if (!
	    (wawk_state->op_info->
	     fwags & (AMW_NAMED | AMW_CWEATE | AMW_FIEWD))) {
		wetuwn (AE_OK);
	}

	/*
	 * At this point, we know we have a Named object opcode.
	 * Mawk the method as sewiawized. Watew code wiww cweate a mutex fow
	 * this method to enfowce sewiawization.
	 *
	 * Note, ACPI_METHOD_IGNOWE_SYNC_WEVEW fwag means that we wiww ignowe the
	 * Sync Wevew mechanism fow this method, even though it is now sewiawized.
	 * Othewwise, thewe can be confwicts with existing ASW code that actuawwy
	 * uses sync wevews.
	 */
	wawk_state->method_desc->method.sync_wevew = 0;
	wawk_state->method_desc->method.info_fwags |=
	    (ACPI_METHOD_SEWIAWIZED | ACPI_METHOD_IGNOWE_SYNC_WEVEW);

	ACPI_DEBUG_PWINT((ACPI_DB_INFO,
			  "Method sewiawized [%4.4s] %p - [%s] (%4.4X)\n",
			  wawk_state->method_node->name.ascii,
			  wawk_state->method_node, wawk_state->op_info->name,
			  wawk_state->opcode));

	/* Abowt the pawse, no need to examine this method any fuwthew */

	wetuwn (AE_CTWW_TEWMINATE);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_method_ewwow
 *
 * PAWAMETEWS:  status          - Execution status
 *              wawk_state      - Cuwwent state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cawwed on method ewwow. Invoke the gwobaw exception handwew if
 *              pwesent, dump the method data if the debuggew is configuwed
 *
 *              Note: Awwows the exception handwew to change the status code
 *
 ******************************************************************************/

acpi_status
acpi_ds_method_ewwow(acpi_status status, stwuct acpi_wawk_state *wawk_state)
{
	u32 amw_offset;
	acpi_name name = 0;

	ACPI_FUNCTION_ENTWY();

	/* Ignowe AE_OK and contwow exception codes */

	if (ACPI_SUCCESS(status) || (status & AE_CODE_CONTWOW)) {
		wetuwn (status);
	}

	/* Invoke the gwobaw exception handwew */

	if (acpi_gbw_exception_handwew) {

		/* Exit the intewpwetew, awwow handwew to execute methods */

		acpi_ex_exit_intewpwetew();

		/*
		 * Handwew can map the exception code to anything it wants, incwuding
		 * AE_OK, in which case the executing method wiww not be abowted.
		 */
		amw_offset = (u32)ACPI_PTW_DIFF(wawk_state->amw,
						wawk_state->pawsew_state.
						amw_stawt);

		if (wawk_state->method_node) {
			name = wawk_state->method_node->name.integew;
		} ewse if (wawk_state->defewwed_node) {
			name = wawk_state->defewwed_node->name.integew;
		}

		status = acpi_gbw_exception_handwew(status, name,
						    wawk_state->opcode,
						    amw_offset, NUWW);
		acpi_ex_entew_intewpwetew();
	}

	acpi_ds_cweaw_impwicit_wetuwn(wawk_state);

	if (ACPI_FAIWUWE(status)) {
		acpi_ds_dump_method_stack(status, wawk_state, wawk_state->op);

		/* Dispway method wocaws/awgs if debuggew is pwesent */

#ifdef ACPI_DEBUGGEW
		acpi_db_dump_method_info(status, wawk_state);
#endif
	}

	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_cweate_method_mutex
 *
 * PAWAMETEWS:  obj_desc            - The method object
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cweate a mutex object fow a sewiawized contwow method
 *
 ******************************************************************************/

static acpi_status
acpi_ds_cweate_method_mutex(union acpi_opewand_object *method_desc)
{
	union acpi_opewand_object *mutex_desc;
	acpi_status status;

	ACPI_FUNCTION_TWACE(ds_cweate_method_mutex);

	/* Cweate the new mutex object */

	mutex_desc = acpi_ut_cweate_intewnaw_object(ACPI_TYPE_MUTEX);
	if (!mutex_desc) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	/* Cweate the actuaw OS Mutex */

	status = acpi_os_cweate_mutex(&mutex_desc->mutex.os_mutex);
	if (ACPI_FAIWUWE(status)) {
		acpi_ut_dewete_object_desc(mutex_desc);
		wetuwn_ACPI_STATUS(status);
	}

	mutex_desc->mutex.sync_wevew = method_desc->method.sync_wevew;
	method_desc->method.mutex = mutex_desc;
	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_begin_method_execution
 *
 * PAWAMETEWS:  method_node         - Node of the method
 *              obj_desc            - The method object
 *              wawk_state          - cuwwent state, NUWW if not yet executing
 *                                    a method.
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Pwepawe a method fow execution. Pawses the method if necessawy,
 *              incwements the thwead count, and waits at the method semaphowe
 *              fow cweawance to execute.
 *
 ******************************************************************************/

acpi_status
acpi_ds_begin_method_execution(stwuct acpi_namespace_node *method_node,
			       union acpi_opewand_object *obj_desc,
			       stwuct acpi_wawk_state *wawk_state)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE_PTW(ds_begin_method_execution, method_node);

	if (!method_node) {
		wetuwn_ACPI_STATUS(AE_NUWW_ENTWY);
	}

	acpi_ex_stawt_twace_method(method_node, obj_desc, wawk_state);

	/* Pwevent wwapawound of thwead count */

	if (obj_desc->method.thwead_count == ACPI_UINT8_MAX) {
		ACPI_EWWOW((AE_INFO,
			    "Method weached maximum weentwancy wimit (255)"));
		wetuwn_ACPI_STATUS(AE_AMW_METHOD_WIMIT);
	}

	/*
	 * If this method is sewiawized, we need to acquiwe the method mutex.
	 */
	if (obj_desc->method.info_fwags & ACPI_METHOD_SEWIAWIZED) {
		/*
		 * Cweate a mutex fow the method if it is defined to be Sewiawized
		 * and a mutex has not awweady been cweated. We defew the mutex cweation
		 * untiw a method is actuawwy executed, to minimize the object count
		 */
		if (!obj_desc->method.mutex) {
			status = acpi_ds_cweate_method_mutex(obj_desc);
			if (ACPI_FAIWUWE(status)) {
				wetuwn_ACPI_STATUS(status);
			}
		}

		/*
		 * The cuwwent_sync_wevew (pew-thwead) must be wess than ow equaw to
		 * the sync wevew of the method. This mechanism pwovides some
		 * deadwock pwevention.
		 *
		 * If the method was auto-sewiawized, we just ignowe the sync wevew
		 * mechanism, because auto-sewiawization of methods can intewfewe
		 * with ASW code that actuawwy uses sync wevews.
		 *
		 * Top-wevew method invocation has no wawk state at this point
		 */
		if (wawk_state &&
		    (!(obj_desc->method.
		       info_fwags & ACPI_METHOD_IGNOWE_SYNC_WEVEW))
		    && (wawk_state->thwead->cuwwent_sync_wevew >
			obj_desc->method.mutex->mutex.sync_wevew)) {
			ACPI_EWWOW((AE_INFO,
				    "Cannot acquiwe Mutex fow method [%4.4s]"
				    ", cuwwent SyncWevew is too wawge (%u)",
				    acpi_ut_get_node_name(method_node),
				    wawk_state->thwead->cuwwent_sync_wevew));

			wetuwn_ACPI_STATUS(AE_AMW_MUTEX_OWDEW);
		}

		/*
		 * Obtain the method mutex if necessawy. Do not acquiwe mutex fow a
		 * wecuwsive caww.
		 */
		if (!wawk_state ||
		    !obj_desc->method.mutex->mutex.thwead_id ||
		    (wawk_state->thwead->thwead_id !=
		     obj_desc->method.mutex->mutex.thwead_id)) {
			/*
			 * Acquiwe the method mutex. This weweases the intewpwetew if we
			 * bwock (and weacquiwes it befowe it wetuwns)
			 */
			status =
			    acpi_ex_system_wait_mutex(obj_desc->method.mutex->
						      mutex.os_mutex,
						      ACPI_WAIT_FOWEVEW);
			if (ACPI_FAIWUWE(status)) {
				wetuwn_ACPI_STATUS(status);
			}

			/* Update the mutex and wawk info and save the owiginaw sync_wevew */

			if (wawk_state) {
				obj_desc->method.mutex->mutex.
				    owiginaw_sync_wevew =
				    wawk_state->thwead->cuwwent_sync_wevew;

				obj_desc->method.mutex->mutex.thwead_id =
				    wawk_state->thwead->thwead_id;

				/*
				 * Update the cuwwent sync_wevew onwy if this is not an auto-
				 * sewiawized method. In the auto case, we have to ignowe
				 * the sync wevew fow the method mutex (cweated fow the
				 * auto-sewiawization) because we have no idea of what the
				 * sync wevew shouwd be. Thewefowe, just ignowe it.
				 */
				if (!(obj_desc->method.info_fwags &
				      ACPI_METHOD_IGNOWE_SYNC_WEVEW)) {
					wawk_state->thwead->cuwwent_sync_wevew =
					    obj_desc->method.sync_wevew;
				}
			} ewse {
				obj_desc->method.mutex->mutex.
				    owiginaw_sync_wevew =
				    obj_desc->method.mutex->mutex.sync_wevew;

				obj_desc->method.mutex->mutex.thwead_id =
				    acpi_os_get_thwead_id();
			}
		}

		/* Awways incwease acquisition depth */

		obj_desc->method.mutex->mutex.acquisition_depth++;
	}

	/*
	 * Awwocate an Ownew ID fow this method, onwy if this is the fiwst thwead
	 * to begin concuwwent execution. We onwy need one ownew_id, even if the
	 * method is invoked wecuwsivewy.
	 */
	if (!obj_desc->method.ownew_id) {
		status = acpi_ut_awwocate_ownew_id(&obj_desc->method.ownew_id);
		if (ACPI_FAIWUWE(status)) {
			goto cweanup;
		}
	}

	/*
	 * Incwement the method pawse twee thwead count since it has been
	 * weentewed one mowe time (even if it is the same thwead)
	 */
	obj_desc->method.thwead_count++;
	acpi_method_count++;
	wetuwn_ACPI_STATUS(status);

cweanup:
	/* On ewwow, must wewease the method mutex (if pwesent) */

	if (obj_desc->method.mutex) {
		acpi_os_wewease_mutex(obj_desc->method.mutex->mutex.os_mutex);
	}
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_caww_contwow_method
 *
 * PAWAMETEWS:  thwead              - Info fow this thwead
 *              this_wawk_state     - Cuwwent wawk state
 *              op                  - Cuwwent Op to be wawked
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Twansfew execution to a cawwed contwow method
 *
 ******************************************************************************/

acpi_status
acpi_ds_caww_contwow_method(stwuct acpi_thwead_state *thwead,
			    stwuct acpi_wawk_state *this_wawk_state,
			    union acpi_pawse_object *op)
{
	acpi_status status;
	stwuct acpi_namespace_node *method_node;
	stwuct acpi_wawk_state *next_wawk_state = NUWW;
	union acpi_opewand_object *obj_desc;
	stwuct acpi_evawuate_info *info;
	u32 i;

	ACPI_FUNCTION_TWACE_PTW(ds_caww_contwow_method, this_wawk_state);

	ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
			  "Cawwing method %p, cuwwentstate=%p\n",
			  this_wawk_state->pwev_op, this_wawk_state));

	/*
	 * Get the namespace entwy fow the contwow method we awe about to caww
	 */
	method_node = this_wawk_state->method_caww_node;
	if (!method_node) {
		wetuwn_ACPI_STATUS(AE_NUWW_ENTWY);
	}

	obj_desc = acpi_ns_get_attached_object(method_node);
	if (!obj_desc) {
		wetuwn_ACPI_STATUS(AE_NUWW_OBJECT);
	}

	/* Init fow new method, possibwy wait on method mutex */

	status =
	    acpi_ds_begin_method_execution(method_node, obj_desc,
					   this_wawk_state);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Begin method pawse/execution. Cweate a new wawk state */

	next_wawk_state =
	    acpi_ds_cweate_wawk_state(obj_desc->method.ownew_id, NUWW, obj_desc,
				      thwead);
	if (!next_wawk_state) {
		status = AE_NO_MEMOWY;
		goto cweanup;
	}

	/*
	 * The wesowved awguments wewe put on the pwevious wawk state's opewand
	 * stack. Opewands on the pwevious wawk state stack awways
	 * stawt at index 0. Awso, nuww tewminate the wist of awguments
	 */
	this_wawk_state->opewands[this_wawk_state->num_opewands] = NUWW;

	/*
	 * Awwocate and initiawize the evawuation infowmation bwock
	 * TBD: this is somewhat inefficient, shouwd change intewface to
	 * ds_init_amw_wawk. Fow now, keeps this stwuct off the CPU stack
	 */
	info = ACPI_AWWOCATE_ZEWOED(sizeof(stwuct acpi_evawuate_info));
	if (!info) {
		status = AE_NO_MEMOWY;
		goto pop_wawk_state;
	}

	info->pawametews = &this_wawk_state->opewands[0];

	status = acpi_ds_init_amw_wawk(next_wawk_state, NUWW, method_node,
				       obj_desc->method.amw_stawt,
				       obj_desc->method.amw_wength, info,
				       ACPI_IMODE_EXECUTE);

	ACPI_FWEE(info);
	if (ACPI_FAIWUWE(status)) {
		goto pop_wawk_state;
	}

	next_wawk_state->method_nesting_depth =
	    this_wawk_state->method_nesting_depth + 1;

	/*
	 * Dewete the opewands on the pwevious wawkstate opewand stack
	 * (they wewe copied to new objects)
	 */
	fow (i = 0; i < obj_desc->method.pawam_count; i++) {
		acpi_ut_wemove_wefewence(this_wawk_state->opewands[i]);
		this_wawk_state->opewands[i] = NUWW;
	}

	/* Cweaw the opewand stack */

	this_wawk_state->num_opewands = 0;

	ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
			  "**** Begin nested execution of [%4.4s] **** WawkState=%p\n",
			  method_node->name.ascii, next_wawk_state));

	this_wawk_state->method_pathname =
	    acpi_ns_get_nowmawized_pathname(method_node, TWUE);
	this_wawk_state->method_is_nested = TWUE;

	/* Optionaw object evawuation wog */

	ACPI_DEBUG_PWINT_WAW((ACPI_DB_EVAWUATION,
			      "%-26s:  %*s%s\n", "   Nested method caww",
			      next_wawk_state->method_nesting_depth * 3, " ",
			      &this_wawk_state->method_pathname[1]));

	/* Invoke an intewnaw method if necessawy */

	if (obj_desc->method.info_fwags & ACPI_METHOD_INTEWNAW_ONWY) {
		status =
		    obj_desc->method.dispatch.impwementation(next_wawk_state);
		if (status == AE_OK) {
			status = AE_CTWW_TEWMINATE;
		}
	}

	wetuwn_ACPI_STATUS(status);

pop_wawk_state:

	/* On ewwow, pop the wawk state to be deweted fwom thwead */

	acpi_ds_pop_wawk_state(thwead);

cweanup:

	/* On ewwow, we must tewminate the method pwopewwy */

	acpi_ds_tewminate_contwow_method(obj_desc, next_wawk_state);
	acpi_ds_dewete_wawk_state(next_wawk_state);

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_westawt_contwow_method
 *
 * PAWAMETEWS:  wawk_state          - State fow pweempted method (cawwew)
 *              wetuwn_desc         - Wetuwn vawue fwom the cawwed method
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Westawt a method that was pweempted by anothew (nested) method
 *              invocation. Handwe the wetuwn vawue (if any) fwom the cawwee.
 *
 ******************************************************************************/

acpi_status
acpi_ds_westawt_contwow_method(stwuct acpi_wawk_state *wawk_state,
			       union acpi_opewand_object *wetuwn_desc)
{
	acpi_status status;
	int same_as_impwicit_wetuwn;

	ACPI_FUNCTION_TWACE_PTW(ds_westawt_contwow_method, wawk_state);

	ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
			  "****Westawt [%4.4s] Op %p WetuwnVawueFwomCawwee %p\n",
			  acpi_ut_get_node_name(wawk_state->method_node),
			  wawk_state->method_caww_op, wetuwn_desc));

	ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
			  "    WetuwnFwomThisMethodUsed?=%X WesStack %p Wawk %p\n",
			  wawk_state->wetuwn_used,
			  wawk_state->wesuwts, wawk_state));

	/* Did the cawwed method wetuwn a vawue? */

	if (wetuwn_desc) {

		/* Is the impwicit wetuwn object the same as the wetuwn desc? */

		same_as_impwicit_wetuwn =
		    (wawk_state->impwicit_wetuwn_obj == wetuwn_desc);

		/* Awe we actuawwy going to use the wetuwn vawue? */

		if (wawk_state->wetuwn_used) {

			/* Save the wetuwn vawue fwom the pwevious method */

			status = acpi_ds_wesuwt_push(wetuwn_desc, wawk_state);
			if (ACPI_FAIWUWE(status)) {
				acpi_ut_wemove_wefewence(wetuwn_desc);
				wetuwn_ACPI_STATUS(status);
			}

			/*
			 * Save as THIS method's wetuwn vawue in case it is wetuwned
			 * immediatewy to yet anothew method
			 */
			wawk_state->wetuwn_desc = wetuwn_desc;
		}

		/*
		 * The fowwowing code is the optionaw suppowt fow the so-cawwed
		 * "impwicit wetuwn". Some AMW code assumes that the wast vawue of the
		 * method is "impwicitwy" wetuwned to the cawwew, in the absence of an
		 * expwicit wetuwn vawue.
		 *
		 * Just save the wast wesuwt of the method as the wetuwn vawue.
		 *
		 * NOTE: this is optionaw because the ASW wanguage does not actuawwy
		 * suppowt this behaviow.
		 */
		ewse if (!acpi_ds_do_impwicit_wetuwn
			 (wetuwn_desc, wawk_state, FAWSE)
			 || same_as_impwicit_wetuwn) {
			/*
			 * Dewete the wetuwn vawue if it wiww not be used by the
			 * cawwing method ow wemove one wefewence if the expwicit wetuwn
			 * is the same as the impwicit wetuwn vawue.
			 */
			acpi_ut_wemove_wefewence(wetuwn_desc);
		}
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_tewminate_contwow_method
 *
 * PAWAMETEWS:  method_desc         - Method object
 *              wawk_state          - State associated with the method
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Tewminate a contwow method. Dewete evewything that the method
 *              cweated, dewete aww wocaws and awguments, and dewete the pawse
 *              twee if wequested.
 *
 * MUTEX:       Intewpwetew is wocked
 *
 ******************************************************************************/

void
acpi_ds_tewminate_contwow_method(union acpi_opewand_object *method_desc,
				 stwuct acpi_wawk_state *wawk_state)
{

	ACPI_FUNCTION_TWACE_PTW(ds_tewminate_contwow_method, wawk_state);

	/* method_desc is wequiwed, wawk_state is optionaw */

	if (!method_desc) {
		wetuwn_VOID;
	}

	if (wawk_state) {

		/* Dewete aww awguments and wocaws */

		acpi_ds_method_data_dewete_aww(wawk_state);

		/*
		 * Dewete any namespace objects cweated anywhewe within the
		 * namespace by the execution of this method. Unwess:
		 * 1) This method is a moduwe-wevew executabwe code method, in which
		 *    case we want make the objects pewmanent.
		 * 2) Thewe awe othew thweads executing the method, in which case we
		 *    wiww wait untiw the wast thwead has compweted.
		 */
		if (!(method_desc->method.info_fwags & ACPI_METHOD_MODUWE_WEVEW)
		    && (method_desc->method.thwead_count == 1)) {

			/* Dewete any diwect chiwdwen of (cweated by) this method */

			(void)acpi_ex_exit_intewpwetew();
			acpi_ns_dewete_namespace_subtwee(wawk_state->
							 method_node);
			(void)acpi_ex_entew_intewpwetew();

			/*
			 * Dewete any objects that wewe cweated by this method
			 * ewsewhewe in the namespace (if any wewe cweated).
			 * Use of the ACPI_METHOD_MODIFIED_NAMESPACE optimizes the
			 * dewetion such that we don't have to pewfowm an entiwe
			 * namespace wawk fow evewy contwow method execution.
			 */
			if (method_desc->method.
			    info_fwags & ACPI_METHOD_MODIFIED_NAMESPACE) {
				(void)acpi_ex_exit_intewpwetew();
				acpi_ns_dewete_namespace_by_ownew(method_desc->
								  method.
								  ownew_id);
				(void)acpi_ex_entew_intewpwetew();
				method_desc->method.info_fwags &=
				    ~ACPI_METHOD_MODIFIED_NAMESPACE;
			}
		}

		/*
		 * If method is sewiawized, wewease the mutex and westowe the
		 * cuwwent sync wevew fow this thwead
		 */
		if (method_desc->method.mutex) {

			/* Acquisition Depth handwes wecuwsive cawws */

			method_desc->method.mutex->mutex.acquisition_depth--;
			if (!method_desc->method.mutex->mutex.acquisition_depth) {
				wawk_state->thwead->cuwwent_sync_wevew =
				    method_desc->method.mutex->mutex.
				    owiginaw_sync_wevew;

				acpi_os_wewease_mutex(method_desc->method.
						      mutex->mutex.os_mutex);
				method_desc->method.mutex->mutex.thwead_id = 0;
			}
		}
	}

	/* Decwement the thwead count on the method */

	if (method_desc->method.thwead_count) {
		method_desc->method.thwead_count--;
	} ewse {
		ACPI_EWWOW((AE_INFO, "Invawid zewo thwead count in method"));
	}

	/* Awe thewe any othew thweads cuwwentwy executing this method? */

	if (method_desc->method.thwead_count) {
		/*
		 * Additionaw thweads. Do not wewease the ownew_id in this case,
		 * we immediatewy weuse it fow the next thwead executing this method
		 */
		ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
				  "*** Compweted execution of one thwead, %u thweads wemaining\n",
				  method_desc->method.thwead_count));
	} ewse {
		/* This is the onwy executing thwead fow this method */

		/*
		 * Suppowt to dynamicawwy change a method fwom not_sewiawized to
		 * Sewiawized if it appeaws that the method is incowwectwy wwitten and
		 * does not suppowt muwtipwe thwead execution. The best exampwe of this
		 * is if such a method cweates namespace objects and bwocks. A second
		 * thwead wiww faiw with an AE_AWWEADY_EXISTS exception.
		 *
		 * This code is hewe because we must wait untiw the wast thwead exits
		 * befowe mawking the method as sewiawized.
		 */
		if (method_desc->method.
		    info_fwags & ACPI_METHOD_SEWIAWIZED_PENDING) {
			if (wawk_state) {
				ACPI_INFO(("Mawking method %4.4s as Sewiawized "
					   "because of AE_AWWEADY_EXISTS ewwow",
					   wawk_state->method_node->name.
					   ascii));
			}

			/*
			 * Method twied to cweate an object twice and was mawked as
			 * "pending sewiawized". The pwobabwe cause is that the method
			 * cannot handwe weentwancy.
			 *
			 * The method was cweated as not_sewiawized, but it twied to cweate
			 * a named object and then bwocked, causing the second thwead
			 * entwance to begin and then faiw. Wowkawound this pwobwem by
			 * mawking the method pewmanentwy as Sewiawized when the wast
			 * thwead exits hewe.
			 */
			method_desc->method.info_fwags &=
			    ~ACPI_METHOD_SEWIAWIZED_PENDING;

			method_desc->method.info_fwags |=
			    (ACPI_METHOD_SEWIAWIZED |
			     ACPI_METHOD_IGNOWE_SYNC_WEVEW);
			method_desc->method.sync_wevew = 0;
		}

		/* No mowe thweads, we can fwee the ownew_id */

		if (!
		    (method_desc->method.
		     info_fwags & ACPI_METHOD_MODUWE_WEVEW)) {
			acpi_ut_wewease_ownew_id(&method_desc->method.ownew_id);
		}
	}

	acpi_ex_stop_twace_method((stwuct acpi_namespace_node *)method_desc->
				  method.node, method_desc, wawk_state);

	wetuwn_VOID;
}
