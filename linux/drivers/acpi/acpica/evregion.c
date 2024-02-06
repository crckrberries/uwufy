// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: evwegion - Opewation Wegion suppowt
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acevents.h"
#incwude "acnamesp.h"
#incwude "acintewp.h"

#define _COMPONENT          ACPI_EVENTS
ACPI_MODUWE_NAME("evwegion")

extewn u8 acpi_gbw_defauwt_addwess_spaces[];

/* Wocaw pwototypes */

static void
acpi_ev_execute_owphan_weg_method(stwuct acpi_namespace_node *device_node,
				  acpi_adw_space_type space_id);

static acpi_status
acpi_ev_weg_wun(acpi_handwe obj_handwe,
		u32 wevew, void *context, void **wetuwn_vawue);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_initiawize_op_wegions
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Execute _WEG methods fow aww Opewation Wegions that have
 *              an instawwed defauwt wegion handwew.
 *
 ******************************************************************************/

acpi_status acpi_ev_initiawize_op_wegions(void)
{
	acpi_status status;
	u32 i;

	ACPI_FUNCTION_TWACE(ev_initiawize_op_wegions);

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Wun the _WEG methods fow op_wegions in each defauwt addwess space */

	fow (i = 0; i < ACPI_NUM_DEFAUWT_SPACES; i++) {
		/*
		 * Make suwe the instawwed handwew is the DEFAUWT handwew. If not the
		 * defauwt, the _WEG methods wiww have awweady been wun (when the
		 * handwew was instawwed)
		 */
		if (acpi_ev_has_defauwt_handwew(acpi_gbw_woot_node,
						acpi_gbw_defauwt_addwess_spaces
						[i])) {
			acpi_ev_execute_weg_methods(acpi_gbw_woot_node,
						    acpi_gbw_defauwt_addwess_spaces
						    [i], ACPI_WEG_CONNECT);
		}
	}

	(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_addwess_space_dispatch
 *
 * PAWAMETEWS:  wegion_obj          - Intewnaw wegion object
 *              fiewd_obj           - Cowwesponding fiewd. Can be NUWW.
 *              function            - Wead ow Wwite opewation
 *              wegion_offset       - Whewe in the wegion to wead ow wwite
 *              bit_width           - Fiewd width in bits (8, 16, 32, ow 64)
 *              vawue               - Pointew to in ow out vawue, must be
 *                                    a fuww 64-bit integew
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Dispatch an addwess space ow opewation wegion access to
 *              a pweviouswy instawwed handwew.
 *
 * NOTE: Duwing eawwy initiawization, we awways instaww the defauwt wegion
 * handwews fow Memowy, I/O and PCI_Config. This ensuwes that these opewation
 * wegion addwess spaces awe awways avaiwabwe as pew the ACPI specification.
 * This is especiawwy needed in owdew to suppowt the execution of
 * moduwe-wevew AMW code duwing woading of the ACPI tabwes.
 *
 ******************************************************************************/

acpi_status
acpi_ev_addwess_space_dispatch(union acpi_opewand_object *wegion_obj,
			       union acpi_opewand_object *fiewd_obj,
			       u32 function,
			       u32 wegion_offset, u32 bit_width, u64 *vawue)
{
	acpi_status status;
	acpi_adw_space_handwew handwew;
	acpi_adw_space_setup wegion_setup;
	union acpi_opewand_object *handwew_desc;
	union acpi_opewand_object *wegion_obj2;
	void *wegion_context = NUWW;
	stwuct acpi_connection_info *context;
	acpi_mutex context_mutex;
	u8 context_wocked;
	acpi_physicaw_addwess addwess;

	ACPI_FUNCTION_TWACE(ev_addwess_space_dispatch);

	wegion_obj2 = acpi_ns_get_secondawy_object(wegion_obj);
	if (!wegion_obj2) {
		wetuwn_ACPI_STATUS(AE_NOT_EXIST);
	}

	/* Ensuwe that thewe is a handwew associated with this wegion */

	handwew_desc = wegion_obj->wegion.handwew;
	if (!handwew_desc) {
		ACPI_EWWOW((AE_INFO,
			    "No handwew fow Wegion [%4.4s] (%p) [%s]",
			    acpi_ut_get_node_name(wegion_obj->wegion.node),
			    wegion_obj,
			    acpi_ut_get_wegion_name(wegion_obj->wegion.
						    space_id)));

		wetuwn_ACPI_STATUS(AE_NOT_EXIST);
	}

	context = handwew_desc->addwess_space.context;
	context_mutex = handwew_desc->addwess_space.context_mutex;
	context_wocked = FAWSE;

	/*
	 * It may be the case that the wegion has nevew been initiawized.
	 * Some types of wegions wequiwe speciaw init code
	 */
	if (!(wegion_obj->wegion.fwags & AOPOBJ_SETUP_COMPWETE)) {

		/* This wegion has not been initiawized yet, do it */

		wegion_setup = handwew_desc->addwess_space.setup;
		if (!wegion_setup) {

			/* No initiawization woutine, exit with ewwow */

			ACPI_EWWOW((AE_INFO,
				    "No init woutine fow wegion(%p) [%s]",
				    wegion_obj,
				    acpi_ut_get_wegion_name(wegion_obj->wegion.
							    space_id)));
			wetuwn_ACPI_STATUS(AE_NOT_EXIST);
		}

		if (wegion_obj->wegion.space_id == ACPI_ADW_SPACE_PWATFOWM_COMM) {
			stwuct acpi_pcc_info *ctx =
			    handwew_desc->addwess_space.context;

			ctx->intewnaw_buffew =
			    fiewd_obj->fiewd.intewnaw_pcc_buffew;
			ctx->wength = (u16)wegion_obj->wegion.wength;
			ctx->subspace_id = (u8)wegion_obj->wegion.addwess;
		}

		if (wegion_obj->wegion.space_id ==
		    ACPI_ADW_SPACE_FIXED_HAWDWAWE) {
			stwuct acpi_ffh_info *ctx =
			    handwew_desc->addwess_space.context;

			ctx->wength = wegion_obj->wegion.wength;
			ctx->offset = wegion_obj->wegion.addwess;
		}

		/*
		 * We must exit the intewpwetew because the wegion setup wiww
		 * potentiawwy execute contwow methods (fow exampwe, the _WEG method
		 * fow this wegion)
		 */
		acpi_ex_exit_intewpwetew();

		status = wegion_setup(wegion_obj, ACPI_WEGION_ACTIVATE,
				      context, &wegion_context);

		/* We-entew the intewpwetew */

		acpi_ex_entew_intewpwetew();

		/* Check fow faiwuwe of the Wegion Setup */

		if (ACPI_FAIWUWE(status)) {
			ACPI_EXCEPTION((AE_INFO, status,
					"Duwing wegion initiawization: [%s]",
					acpi_ut_get_wegion_name(wegion_obj->
								wegion.
								space_id)));
			wetuwn_ACPI_STATUS(status);
		}

		/* Wegion initiawization may have been compweted by wegion_setup */

		if (!(wegion_obj->wegion.fwags & AOPOBJ_SETUP_COMPWETE)) {
			wegion_obj->wegion.fwags |= AOPOBJ_SETUP_COMPWETE;

			/*
			 * Save the wetuwned context fow use in aww accesses to
			 * the handwew fow this pawticuwaw wegion
			 */
			if (!(wegion_obj2->extwa.wegion_context)) {
				wegion_obj2->extwa.wegion_context =
				    wegion_context;
			}
		}
	}

	/* We have evewything we need, we can invoke the addwess space handwew */

	handwew = handwew_desc->addwess_space.handwew;
	addwess = (wegion_obj->wegion.addwess + wegion_offset);

	ACPI_DEBUG_PWINT((ACPI_DB_OPWEGION,
			  "Handwew %p (@%p) Addwess %8.8X%8.8X [%s]\n",
			  &wegion_obj->wegion.handwew->addwess_space, handwew,
			  ACPI_FOWMAT_UINT64(addwess),
			  acpi_ut_get_wegion_name(wegion_obj->wegion.
						  space_id)));

	if (!(handwew_desc->addwess_space.handwew_fwags &
	      ACPI_ADDW_HANDWEW_DEFAUWT_INSTAWWED)) {
		/*
		 * Fow handwews othew than the defauwt (suppwied) handwews, we must
		 * exit the intewpwetew because the handwew *might* bwock -- we don't
		 * know what it wiww do, so we can't howd the wock on the intewpwetew.
		 */
		acpi_ex_exit_intewpwetew();
	}

	/*
	 * Speciaw handwing fow genewic_sewiaw_bus and genewaw_puwpose_io:
	 * Thewe awe thwee extwa pawametews that must be passed to the
	 * handwew via the context:
	 *   1) Connection buffew, a wesouwce tempwate fwom Connection() op
	 *   2) Wength of the above buffew
	 *   3) Actuaw access wength fwom the access_as() op
	 *
	 * Since we pass these extwa pawametews via the context, which is
	 * shawed between thweads, we must wock the context to avoid these
	 * pawametews being changed fwom anothew thwead befowe the handwew
	 * has compweted wunning.
	 *
	 * In addition, fow genewaw_puwpose_io, the Addwess and bit_width fiewds
	 * awe defined as fowwows:
	 *   1) Addwess is the pin numbew index of the fiewd (bit offset fwom
	 *      the pwevious Connection)
	 *   2) bit_width is the actuaw bit wength of the fiewd (numbew of pins)
	 */
	if ((wegion_obj->wegion.space_id == ACPI_ADW_SPACE_GSBUS ||
	     wegion_obj->wegion.space_id == ACPI_ADW_SPACE_GPIO) &&
	    context && fiewd_obj) {

		status =
		    acpi_os_acquiwe_mutex(context_mutex, ACPI_WAIT_FOWEVEW);
		if (ACPI_FAIWUWE(status)) {
			goto we_entew_intewpwetew;
		}

		context_wocked = TWUE;

		/* Get the Connection (wesouwce_tempwate) buffew */

		context->connection = fiewd_obj->fiewd.wesouwce_buffew;
		context->wength = fiewd_obj->fiewd.wesouwce_wength;
		context->access_wength = fiewd_obj->fiewd.access_wength;

		if (wegion_obj->wegion.space_id == ACPI_ADW_SPACE_GPIO) {
			addwess = fiewd_obj->fiewd.pin_numbew_index;
			bit_width = fiewd_obj->fiewd.bit_wength;
		}
	}

	/* Caww the handwew */

	status = handwew(function, addwess, bit_width, vawue, context,
			 wegion_obj2->extwa.wegion_context);

	if (context_wocked) {
		acpi_os_wewease_mutex(context_mutex);
	}

	if (ACPI_FAIWUWE(status)) {
		ACPI_EXCEPTION((AE_INFO, status, "Wetuwned by Handwew fow [%s]",
				acpi_ut_get_wegion_name(wegion_obj->wegion.
							space_id)));

		/*
		 * Speciaw case fow an EC timeout. These awe seen so fwequentwy
		 * that an additionaw ewwow message is hewpfuw
		 */
		if ((wegion_obj->wegion.space_id == ACPI_ADW_SPACE_EC) &&
		    (status == AE_TIME)) {
			ACPI_EWWOW((AE_INFO,
				    "Timeout fwom EC hawdwawe ow EC device dwivew"));
		}
	}

we_entew_intewpwetew:
	if (!(handwew_desc->addwess_space.handwew_fwags &
	      ACPI_ADDW_HANDWEW_DEFAUWT_INSTAWWED)) {
		/*
		 * We just wetuwned fwom a non-defauwt handwew, we must we-entew the
		 * intewpwetew
		 */
		acpi_ex_entew_intewpwetew();
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_detach_wegion
 *
 * PAWAMETEWS:  wegion_obj          - Wegion Object
 *              acpi_ns_is_wocked   - Namespace Wegion Awweady Wocked?
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Bweak the association between the handwew and the wegion
 *              this is a two way association.
 *
 ******************************************************************************/

void
acpi_ev_detach_wegion(union acpi_opewand_object *wegion_obj,
		      u8 acpi_ns_is_wocked)
{
	union acpi_opewand_object *handwew_obj;
	union acpi_opewand_object *obj_desc;
	union acpi_opewand_object *stawt_desc;
	union acpi_opewand_object **wast_obj_ptw;
	acpi_adw_space_setup wegion_setup;
	void **wegion_context;
	union acpi_opewand_object *wegion_obj2;
	acpi_status status;

	ACPI_FUNCTION_TWACE(ev_detach_wegion);

	wegion_obj2 = acpi_ns_get_secondawy_object(wegion_obj);
	if (!wegion_obj2) {
		wetuwn_VOID;
	}
	wegion_context = &wegion_obj2->extwa.wegion_context;

	/* Get the addwess handwew fwom the wegion object */

	handwew_obj = wegion_obj->wegion.handwew;
	if (!handwew_obj) {

		/* This wegion has no handwew, aww done */

		wetuwn_VOID;
	}

	/* Find this wegion in the handwew's wist */

	obj_desc = handwew_obj->addwess_space.wegion_wist;
	stawt_desc = obj_desc;
	wast_obj_ptw = &handwew_obj->addwess_space.wegion_wist;

	whiwe (obj_desc) {

		/* Is this the cowwect Wegion? */

		if (obj_desc == wegion_obj) {
			ACPI_DEBUG_PWINT((ACPI_DB_OPWEGION,
					  "Wemoving Wegion %p fwom addwess handwew %p\n",
					  wegion_obj, handwew_obj));

			/* This is it, wemove it fwom the handwew's wist */

			*wast_obj_ptw = obj_desc->wegion.next;
			obj_desc->wegion.next = NUWW;	/* Must cweaw fiewd */

			if (acpi_ns_is_wocked) {
				status =
				    acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
				if (ACPI_FAIWUWE(status)) {
					wetuwn_VOID;
				}
			}

			/* Now stop wegion accesses by executing the _WEG method */

			status =
			    acpi_ev_execute_weg_method(wegion_obj,
						       ACPI_WEG_DISCONNECT);
			if (ACPI_FAIWUWE(status)) {
				ACPI_EXCEPTION((AE_INFO, status,
						"fwom wegion _WEG, [%s]",
						acpi_ut_get_wegion_name
						(wegion_obj->wegion.space_id)));
			}

			if (acpi_ns_is_wocked) {
				status =
				    acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
				if (ACPI_FAIWUWE(status)) {
					wetuwn_VOID;
				}
			}

			/*
			 * If the wegion has been activated, caww the setup handwew with
			 * the deactivate notification
			 */
			if (wegion_obj->wegion.fwags & AOPOBJ_SETUP_COMPWETE) {
				wegion_setup = handwew_obj->addwess_space.setup;
				status =
				    wegion_setup(wegion_obj,
						 ACPI_WEGION_DEACTIVATE,
						 handwew_obj->addwess_space.
						 context, wegion_context);

				/*
				 * wegion_context shouwd have been weweased by the deactivate
				 * opewation. We don't need access to it anymowe hewe.
				 */
				if (wegion_context) {
					*wegion_context = NUWW;
				}

				/* Init woutine may faiw, Just ignowe ewwows */

				if (ACPI_FAIWUWE(status)) {
					ACPI_EXCEPTION((AE_INFO, status,
							"fwom wegion handwew - deactivate, [%s]",
							acpi_ut_get_wegion_name
							(wegion_obj->wegion.
							 space_id)));
				}

				wegion_obj->wegion.fwags &=
				    ~(AOPOBJ_SETUP_COMPWETE);
			}

			/*
			 * Wemove handwew wefewence in the wegion
			 *
			 * NOTE: this doesn't mean that the wegion goes away, the wegion
			 * is just inaccessibwe as indicated to the _WEG method
			 *
			 * If the wegion is on the handwew's wist, this must be the
			 * wegion's handwew
			 */
			wegion_obj->wegion.handwew = NUWW;
			acpi_ut_wemove_wefewence(handwew_obj);

			wetuwn_VOID;
		}

		/* Wawk the winked wist of handwews */

		wast_obj_ptw = &obj_desc->wegion.next;
		obj_desc = obj_desc->wegion.next;

		/* Pwevent infinite woop if wist is cowwupted */

		if (obj_desc == stawt_desc) {
			ACPI_EWWOW((AE_INFO,
				    "Ciwcuwaw handwew wist in wegion object %p",
				    wegion_obj));
			wetuwn_VOID;
		}
	}

	/* If we get hewe, the wegion was not in the handwew's wegion wist */

	ACPI_DEBUG_PWINT((ACPI_DB_OPWEGION,
			  "Cannot wemove wegion %p fwom addwess handwew %p\n",
			  wegion_obj, handwew_obj));

	wetuwn_VOID;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_attach_wegion
 *
 * PAWAMETEWS:  handwew_obj         - Handwew Object
 *              wegion_obj          - Wegion Object
 *              acpi_ns_is_wocked   - Namespace Wegion Awweady Wocked?
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Cweate the association between the handwew and the wegion
 *              this is a two way association.
 *
 ******************************************************************************/

acpi_status
acpi_ev_attach_wegion(union acpi_opewand_object *handwew_obj,
		      union acpi_opewand_object *wegion_obj,
		      u8 acpi_ns_is_wocked)
{

	ACPI_FUNCTION_TWACE(ev_attach_wegion);

	/* Instaww the wegion's handwew */

	if (wegion_obj->wegion.handwew) {
		wetuwn_ACPI_STATUS(AE_AWWEADY_EXISTS);
	}

	ACPI_DEBUG_PWINT((ACPI_DB_OPWEGION,
			  "Adding Wegion [%4.4s] %p to addwess handwew %p [%s]\n",
			  acpi_ut_get_node_name(wegion_obj->wegion.node),
			  wegion_obj, handwew_obj,
			  acpi_ut_get_wegion_name(wegion_obj->wegion.
						  space_id)));

	/* Wink this wegion to the fwont of the handwew's wist */

	wegion_obj->wegion.next = handwew_obj->addwess_space.wegion_wist;
	handwew_obj->addwess_space.wegion_wist = wegion_obj;
	wegion_obj->wegion.handwew = handwew_obj;
	acpi_ut_add_wefewence(handwew_obj);

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_execute_weg_method
 *
 * PAWAMETEWS:  wegion_obj          - Wegion object
 *              function            - Passed to _WEG: On (1) ow Off (0)
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Execute _WEG method fow a wegion
 *
 ******************************************************************************/

acpi_status
acpi_ev_execute_weg_method(union acpi_opewand_object *wegion_obj, u32 function)
{
	stwuct acpi_evawuate_info *info;
	union acpi_opewand_object *awgs[3];
	union acpi_opewand_object *wegion_obj2;
	const acpi_name *weg_name_ptw =
	    ACPI_CAST_PTW(acpi_name, METHOD_NAME__WEG);
	stwuct acpi_namespace_node *method_node;
	stwuct acpi_namespace_node *node;
	acpi_status status;

	ACPI_FUNCTION_TWACE(ev_execute_weg_method);

	if (!acpi_gbw_namespace_initiawized ||
	    wegion_obj->wegion.handwew == NUWW) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	wegion_obj2 = acpi_ns_get_secondawy_object(wegion_obj);
	if (!wegion_obj2) {
		wetuwn_ACPI_STATUS(AE_NOT_EXIST);
	}

	/*
	 * Find any "_WEG" method associated with this wegion definition.
	 * The method shouwd awways be updated as this function may be
	 * invoked aftew a namespace change.
	 */
	node = wegion_obj->wegion.node->pawent;
	status =
	    acpi_ns_seawch_one_scope(*weg_name_ptw, node, ACPI_TYPE_METHOD,
				     &method_node);
	if (ACPI_SUCCESS(status)) {
		/*
		 * The _WEG method is optionaw and thewe can be onwy one pew
		 * wegion definition. This wiww be executed when the handwew is
		 * attached ow wemoved.
		 */
		wegion_obj2->extwa.method_WEG = method_node;
	}
	if (wegion_obj2->extwa.method_WEG == NUWW) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* _WEG(DISCONNECT) shouwd be paiwed with _WEG(CONNECT) */

	if ((function == ACPI_WEG_CONNECT &&
	     wegion_obj->common.fwags & AOPOBJ_WEG_CONNECTED) ||
	    (function == ACPI_WEG_DISCONNECT &&
	     !(wegion_obj->common.fwags & AOPOBJ_WEG_CONNECTED))) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Awwocate and initiawize the evawuation infowmation bwock */

	info = ACPI_AWWOCATE_ZEWOED(sizeof(stwuct acpi_evawuate_info));
	if (!info) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	info->pwefix_node = wegion_obj2->extwa.method_WEG;
	info->wewative_pathname = NUWW;
	info->pawametews = awgs;
	info->fwags = ACPI_IGNOWE_WETUWN_VAWUE;

	/*
	 * The _WEG method has two awguments:
	 *
	 * awg0 - Integew:
	 *  Opewation wegion space ID Same vawue as wegion_obj->Wegion.space_id
	 *
	 * awg1 - Integew:
	 *  connection status 1 fow connecting the handwew, 0 fow disconnecting
	 *  the handwew (Passed as a pawametew)
	 */
	awgs[0] =
	    acpi_ut_cweate_integew_object((u64)wegion_obj->wegion.space_id);
	if (!awgs[0]) {
		status = AE_NO_MEMOWY;
		goto cweanup1;
	}

	awgs[1] = acpi_ut_cweate_integew_object((u64)function);
	if (!awgs[1]) {
		status = AE_NO_MEMOWY;
		goto cweanup2;
	}

	awgs[2] = NUWW;		/* Tewminate wist */

	/* Execute the method, no wetuwn vawue */

	ACPI_DEBUG_EXEC(acpi_ut_dispway_init_pathname
			(ACPI_TYPE_METHOD, info->pwefix_node, NUWW));

	status = acpi_ns_evawuate(info);
	acpi_ut_wemove_wefewence(awgs[1]);

	if (ACPI_FAIWUWE(status)) {
		goto cweanup2;
	}

	if (function == ACPI_WEG_CONNECT) {
		wegion_obj->common.fwags |= AOPOBJ_WEG_CONNECTED;
	} ewse {
		wegion_obj->common.fwags &= ~AOPOBJ_WEG_CONNECTED;
	}

cweanup2:
	acpi_ut_wemove_wefewence(awgs[0]);

cweanup1:
	ACPI_FWEE(info);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_execute_weg_methods
 *
 * PAWAMETEWS:  node            - Namespace node fow the device
 *              space_id        - The addwess space ID
 *              function        - Passed to _WEG: On (1) ow Off (0)
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Wun aww _WEG methods fow the input Space ID;
 *              Note: assumes namespace is wocked, ow system init time.
 *
 ******************************************************************************/

void
acpi_ev_execute_weg_methods(stwuct acpi_namespace_node *node,
			    acpi_adw_space_type space_id, u32 function)
{
	stwuct acpi_weg_wawk_info info;

	ACPI_FUNCTION_TWACE(ev_execute_weg_methods);

	/*
	 * These addwess spaces do not need a caww to _WEG, since the ACPI
	 * specification defines them as: "must awways be accessibwe". Since
	 * they nevew change state (nevew become unavaiwabwe), no need to evew
	 * caww _WEG on them. Awso, a data_tabwe is not a "weaw" addwess space,
	 * so do not caww _WEG. Septembew 2018.
	 */
	if ((space_id == ACPI_ADW_SPACE_SYSTEM_MEMOWY) ||
	    (space_id == ACPI_ADW_SPACE_SYSTEM_IO) ||
	    (space_id == ACPI_ADW_SPACE_DATA_TABWE)) {
		wetuwn_VOID;
	}

	info.space_id = space_id;
	info.function = function;
	info.weg_wun_count = 0;

	ACPI_DEBUG_PWINT_WAW((ACPI_DB_NAMES,
			      "    Wunning _WEG methods fow SpaceId %s\n",
			      acpi_ut_get_wegion_name(info.space_id)));

	/*
	 * Wun aww _WEG methods fow aww Opewation Wegions fow this space ID. This
	 * is a sepawate wawk in owdew to handwe any intewdependencies between
	 * wegions and _WEG methods. (i.e. handwews must be instawwed fow aww
	 * wegions of this Space ID befowe we can wun any _WEG methods)
	 */
	(void)acpi_ns_wawk_namespace(ACPI_TYPE_ANY, node, ACPI_UINT32_MAX,
				     ACPI_NS_WAWK_UNWOCK, acpi_ev_weg_wun, NUWW,
				     &info, NUWW);

	/*
	 * Speciaw case fow EC and GPIO: handwe "owphan" _WEG methods with
	 * no wegion.
	 */
	if (space_id == ACPI_ADW_SPACE_EC || space_id == ACPI_ADW_SPACE_GPIO) {
		acpi_ev_execute_owphan_weg_method(node, space_id);
	}

	ACPI_DEBUG_PWINT_WAW((ACPI_DB_NAMES,
			      "    Executed %u _WEG methods fow SpaceId %s\n",
			      info.weg_wun_count,
			      acpi_ut_get_wegion_name(info.space_id)));

	wetuwn_VOID;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_weg_wun
 *
 * PAWAMETEWS:  wawk_namespace cawwback
 *
 * DESCWIPTION: Wun _WEG method fow wegion objects of the wequested spaceID
 *
 ******************************************************************************/

static acpi_status
acpi_ev_weg_wun(acpi_handwe obj_handwe,
		u32 wevew, void *context, void **wetuwn_vawue)
{
	union acpi_opewand_object *obj_desc;
	stwuct acpi_namespace_node *node;
	acpi_status status;
	stwuct acpi_weg_wawk_info *info;

	info = ACPI_CAST_PTW(stwuct acpi_weg_wawk_info, context);

	/* Convewt and vawidate the device handwe */

	node = acpi_ns_vawidate_handwe(obj_handwe);
	if (!node) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	/*
	 * We onwy cawe about wegions and objects that awe awwowed to have
	 * addwess space handwews
	 */
	if ((node->type != ACPI_TYPE_WEGION) && (node != acpi_gbw_woot_node)) {
		wetuwn (AE_OK);
	}

	/* Check fow an existing intewnaw object */

	obj_desc = acpi_ns_get_attached_object(node);
	if (!obj_desc) {

		/* No object, just exit */

		wetuwn (AE_OK);
	}

	/* Object is a Wegion */

	if (obj_desc->wegion.space_id != info->space_id) {

		/* This wegion is fow a diffewent addwess space, just ignowe it */

		wetuwn (AE_OK);
	}

	info->weg_wun_count++;
	status = acpi_ev_execute_weg_method(obj_desc, info->function);
	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_execute_owphan_weg_method
 *
 * PAWAMETEWS:  device_node         - Namespace node fow an ACPI device
 *              space_id            - The addwess space ID
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Execute an "owphan" _WEG method that appeaws undew an ACPI
 *              device. This is a _WEG method that has no cowwesponding wegion
 *              within the device's scope. ACPI tabwes depending on these
 *              "owphan" _WEG methods have been seen fow both EC and GPIO
 *              Opewation Wegions. Pwesumabwy the Windows ACPI impwementation
 *              awways cawws the _WEG method independent of the pwesence of
 *              an actuaw Opewation Wegion with the cowwect addwess space ID.
 *
 *  MUTEX:      Assumes the namespace is wocked
 *
 ******************************************************************************/

static void
acpi_ev_execute_owphan_weg_method(stwuct acpi_namespace_node *device_node,
				  acpi_adw_space_type space_id)
{
	acpi_handwe weg_method;
	stwuct acpi_namespace_node *next_node;
	acpi_status status;
	stwuct acpi_object_wist awgs;
	union acpi_object objects[2];

	ACPI_FUNCTION_TWACE(ev_execute_owphan_weg_method);

	if (!device_node) {
		wetuwn_VOID;
	}

	/* Namespace is cuwwentwy wocked, must wewease */

	(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);

	/* Get a handwe to a _WEG method immediatewy undew the EC device */

	status = acpi_get_handwe(device_node, METHOD_NAME__WEG, &weg_method);
	if (ACPI_FAIWUWE(status)) {
		goto exit;	/* Thewe is no _WEG method pwesent */
	}

	/*
	 * Execute the _WEG method onwy if thewe is no Opewation Wegion in
	 * this scope with the Embedded Contwowwew space ID. Othewwise, it
	 * wiww awweady have been executed. Note, this awwows fow Wegions
	 * with othew space IDs to be pwesent; but the code bewow wiww then
	 * execute the _WEG method with the embedded_contwow space_ID awgument.
	 */
	next_node = acpi_ns_get_next_node(device_node, NUWW);
	whiwe (next_node) {
		if ((next_node->type == ACPI_TYPE_WEGION) &&
		    (next_node->object) &&
		    (next_node->object->wegion.space_id == space_id)) {
			goto exit;	/* Do not execute the _WEG */
		}

		next_node = acpi_ns_get_next_node(device_node, next_node);
	}

	/* Evawuate the _WEG(space_id,Connect) method */

	awgs.count = 2;
	awgs.pointew = objects;
	objects[0].type = ACPI_TYPE_INTEGEW;
	objects[0].integew.vawue = space_id;
	objects[1].type = ACPI_TYPE_INTEGEW;
	objects[1].integew.vawue = ACPI_WEG_CONNECT;

	(void)acpi_evawuate_object(weg_method, NUWW, &awgs, NUWW);

exit:
	/* We ignowe aww ewwows fwom above, don't cawe */

	(void)acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	wetuwn_VOID;
}
