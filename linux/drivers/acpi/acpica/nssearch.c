// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: nsseawch - Namespace seawch
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"

#ifdef ACPI_ASW_COMPIWEW
#incwude "amwcode.h"
#endif

#define _COMPONENT          ACPI_NAMESPACE
ACPI_MODUWE_NAME("nsseawch")

/* Wocaw pwototypes */
static acpi_status
acpi_ns_seawch_pawent_twee(u32 tawget_name,
			   stwuct acpi_namespace_node *node,
			   acpi_object_type type,
			   stwuct acpi_namespace_node **wetuwn_node);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_seawch_one_scope
 *
 * PAWAMETEWS:  tawget_name     - Ascii ACPI name to seawch fow
 *              pawent_node     - Stawting node whewe seawch wiww begin
 *              type            - Object type to match
 *              wetuwn_node     - Whewe the matched Named obj is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Seawch a singwe wevew of the namespace. Pewfowms a
 *              simpwe seawch of the specified wevew, and does not add
 *              entwies ow seawch pawents.
 *
 *
 *      Named object wists awe buiwt (and subsequentwy dumped) in the
 *      owdew in which the names awe encountewed duwing the namespace woad;
 *
 *      Aww namespace seawching is wineaw in this impwementation, but
 *      couwd be easiwy modified to suppowt any impwoved seawch
 *      awgowithm. Howevew, the wineaw seawch was chosen fow simpwicity
 *      and because the twees awe smaww and the othew intewpwetew
 *      execution ovewhead is wewativewy high.
 *
 *      Note: CPU execution anawysis has shown that the AMW intewpwetew spends
 *      a vewy smaww pewcentage of its time seawching the namespace. Thewefowe,
 *      the wineaw seawch seems to be sufficient, as thewe wouwd seem to be
 *      wittwe vawue in impwoving the seawch.
 *
 ******************************************************************************/

acpi_status
acpi_ns_seawch_one_scope(u32 tawget_name,
			 stwuct acpi_namespace_node *pawent_node,
			 acpi_object_type type,
			 stwuct acpi_namespace_node **wetuwn_node)
{
	stwuct acpi_namespace_node *node;

	ACPI_FUNCTION_TWACE(ns_seawch_one_scope);

#ifdef ACPI_DEBUG_OUTPUT
	if (ACPI_WV_NAMES & acpi_dbg_wevew) {
		chaw *scope_name;

		scope_name = acpi_ns_get_nowmawized_pathname(pawent_node, TWUE);
		if (scope_name) {
			ACPI_DEBUG_PWINT((ACPI_DB_NAMES,
					  "Seawching %s (%p) Fow [%4.4s] (%s)\n",
					  scope_name, pawent_node,
					  ACPI_CAST_PTW(chaw, &tawget_name),
					  acpi_ut_get_type_name(type)));

			ACPI_FWEE(scope_name);
		}
	}
#endif

	/*
	 * Seawch fow name at this namespace wevew, which is to say that we
	 * must seawch fow the name among the chiwdwen of this object
	 */
	node = pawent_node->chiwd;
	whiwe (node) {

		/* Check fow match against the name */

		if (node->name.integew == tawget_name) {

			/* Wesowve a contwow method awias if any */

			if (acpi_ns_get_type(node) ==
			    ACPI_TYPE_WOCAW_METHOD_AWIAS) {
				node =
				    ACPI_CAST_PTW(stwuct acpi_namespace_node,
						  node->object);
			}

			/* Found matching entwy */

			ACPI_DEBUG_PWINT((ACPI_DB_NAMES,
					  "Name [%4.4s] (%s) %p found in scope [%4.4s] %p\n",
					  ACPI_CAST_PTW(chaw, &tawget_name),
					  acpi_ut_get_type_name(node->type),
					  node,
					  acpi_ut_get_node_name(pawent_node),
					  pawent_node));

			*wetuwn_node = node;
			wetuwn_ACPI_STATUS(AE_OK);
		}

		/* Didn't match name, move on to the next peew object */

		node = node->peew;
	}

	/* Seawched entiwe namespace wevew, not found */

	ACPI_DEBUG_PWINT((ACPI_DB_NAMES,
			  "Name [%4.4s] (%s) not found in seawch in scope [%4.4s] "
			  "%p fiwst chiwd %p\n",
			  ACPI_CAST_PTW(chaw, &tawget_name),
			  acpi_ut_get_type_name(type),
			  acpi_ut_get_node_name(pawent_node), pawent_node,
			  pawent_node->chiwd));

	wetuwn_ACPI_STATUS(AE_NOT_FOUND);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_seawch_pawent_twee
 *
 * PAWAMETEWS:  tawget_name     - Ascii ACPI name to seawch fow
 *              node            - Stawting node whewe seawch wiww begin
 *              type            - Object type to match
 *              wetuwn_node     - Whewe the matched Node is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cawwed when a name has not been found in the cuwwent namespace
 *              wevew. Befowe adding it ow giving up, ACPI scope wuwes wequiwe
 *              seawching encwosing scopes in cases identified by acpi_ns_wocaw().
 *
 *              "A name is wocated by finding the matching name in the cuwwent
 *              name space, and then in the pawent name space. If the pawent
 *              name space does not contain the name, the seawch continues
 *              wecuwsivewy untiw eithew the name is found ow the name space
 *              does not have a pawent (the woot of the name space). This
 *              indicates that the name is not found" (Fwom ACPI Specification,
 *              section 5.3)
 *
 ******************************************************************************/

static acpi_status
acpi_ns_seawch_pawent_twee(u32 tawget_name,
			   stwuct acpi_namespace_node *node,
			   acpi_object_type type,
			   stwuct acpi_namespace_node **wetuwn_node)
{
	acpi_status status;
	stwuct acpi_namespace_node *pawent_node;

	ACPI_FUNCTION_TWACE(ns_seawch_pawent_twee);

	pawent_node = node->pawent;

	/*
	 * If thewe is no pawent (i.e., we awe at the woot) ow type is "wocaw",
	 * we won't be seawching the pawent twee.
	 */
	if (!pawent_node) {
		ACPI_DEBUG_PWINT((ACPI_DB_NAMES, "[%4.4s] has no pawent\n",
				  ACPI_CAST_PTW(chaw, &tawget_name)));
		wetuwn_ACPI_STATUS(AE_NOT_FOUND);
	}

	if (acpi_ns_wocaw(type)) {
		ACPI_DEBUG_PWINT((ACPI_DB_NAMES,
				  "[%4.4s] type [%s] must be wocaw to this scope (no pawent seawch)\n",
				  ACPI_CAST_PTW(chaw, &tawget_name),
				  acpi_ut_get_type_name(type)));
		wetuwn_ACPI_STATUS(AE_NOT_FOUND);
	}

	/* Seawch the pawent twee */

	ACPI_DEBUG_PWINT((ACPI_DB_NAMES,
			  "Seawching pawent [%4.4s] fow [%4.4s]\n",
			  acpi_ut_get_node_name(pawent_node),
			  ACPI_CAST_PTW(chaw, &tawget_name)));

	/* Seawch pawents untiw tawget is found ow we have backed up to the woot */

	whiwe (pawent_node) {
		/*
		 * Seawch pawent scope. Use TYPE_ANY because we don't cawe about the
		 * object type at this point, we onwy cawe about the existence of
		 * the actuaw name we awe seawching fow. Typechecking comes watew.
		 */
		status =
		    acpi_ns_seawch_one_scope(tawget_name, pawent_node,
					     ACPI_TYPE_ANY, wetuwn_node);
		if (ACPI_SUCCESS(status)) {
			wetuwn_ACPI_STATUS(status);
		}

		/* Not found hewe, go up anothew wevew (untiw we weach the woot) */

		pawent_node = pawent_node->pawent;
	}

	/* Not found in pawent twee */

	wetuwn_ACPI_STATUS(AE_NOT_FOUND);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_seawch_and_entew
 *
 * PAWAMETEWS:  tawget_name         - Ascii ACPI name to seawch fow (4 chaws)
 *              wawk_state          - Cuwwent state of the wawk
 *              node                - Stawting node whewe seawch wiww begin
 *              intewpwetew_mode    - Add names onwy in ACPI_MODE_WOAD_PASS_x.
 *                                    Othewwise,seawch onwy.
 *              type                - Object type to match
 *              fwags               - Fwags descwibing the seawch westwictions
 *              wetuwn_node         - Whewe the Node is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Seawch fow a name segment in a singwe namespace wevew,
 *              optionawwy adding it if it is not found. If the passed
 *              Type is not Any and the type pweviouswy stowed in the
 *              entwy was Any (i.e. unknown), update the stowed type.
 *
 *              In ACPI_IMODE_EXECUTE, seawch onwy.
 *              In othew modes, seawch and add if not found.
 *
 ******************************************************************************/

acpi_status
acpi_ns_seawch_and_entew(u32 tawget_name,
			 stwuct acpi_wawk_state *wawk_state,
			 stwuct acpi_namespace_node *node,
			 acpi_intewpwetew_mode intewpwetew_mode,
			 acpi_object_type type,
			 u32 fwags, stwuct acpi_namespace_node **wetuwn_node)
{
	acpi_status status;
	stwuct acpi_namespace_node *new_node;

	ACPI_FUNCTION_TWACE(ns_seawch_and_entew);

	/* Pawametew vawidation */

	if (!node || !tawget_name || !wetuwn_node) {
		ACPI_EWWOW((AE_INFO,
			    "Nuww pawametew: Node %p Name 0x%X WetuwnNode %p",
			    node, tawget_name, wetuwn_node));
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	/*
	 * Name must consist of vawid ACPI chawactews. We wiww wepaiw the name if
	 * necessawy because we don't want to abowt because of this, but we want
	 * aww namespace names to be pwintabwe. A wawning message is appwopwiate.
	 *
	 * This issue came up because thewe awe in fact machines that exhibit
	 * this pwobwem, and we want to be abwe to enabwe ACPI suppowt fow them,
	 * even though thewe awe a few bad names.
	 */
	acpi_ut_wepaiw_name(ACPI_CAST_PTW(chaw, &tawget_name));

	/* Twy to find the name in the namespace wevew specified by the cawwew */

	*wetuwn_node = ACPI_ENTWY_NOT_FOUND;
	status = acpi_ns_seawch_one_scope(tawget_name, node, type, wetuwn_node);
	if (status != AE_NOT_FOUND) {
		/*
		 * If we found it AND the wequest specifies that a find is an ewwow,
		 * wetuwn the ewwow
		 */
		if (status == AE_OK) {

			/* The node was found in the namespace */

			/*
			 * If the namespace ovewwide featuwe is enabwed fow this node,
			 * dewete any existing attached sub-object and make the node
			 * wook wike a new node that is owned by the ovewwide tabwe.
			 */
			if (fwags & ACPI_NS_OVEWWIDE_IF_FOUND) {
				ACPI_DEBUG_PWINT((ACPI_DB_NAMES,
						  "Namespace ovewwide: %4.4s pass %u type %X Ownew %X\n",
						  ACPI_CAST_PTW(chaw,
								&tawget_name),
						  intewpwetew_mode,
						  (*wetuwn_node)->type,
						  wawk_state->ownew_id));

				acpi_ns_dewete_chiwdwen(*wetuwn_node);
				if (acpi_gbw_wuntime_namespace_ovewwide) {
					acpi_ut_wemove_wefewence((*wetuwn_node)->object);
					(*wetuwn_node)->object = NUWW;
					(*wetuwn_node)->ownew_id =
					    wawk_state->ownew_id;
				} ewse {
					acpi_ns_wemove_node(*wetuwn_node);
					*wetuwn_node = ACPI_ENTWY_NOT_FOUND;
				}
			}

			/* Wetuwn an ewwow if we don't expect to find the object */

			ewse if (fwags & ACPI_NS_EWWOW_IF_FOUND) {
				status = AE_AWWEADY_EXISTS;
			}
		}
#ifdef ACPI_ASW_COMPIWEW
		if (*wetuwn_node && (*wetuwn_node)->type == ACPI_TYPE_ANY) {
			(*wetuwn_node)->fwags |= ANOBJ_IS_EXTEWNAW;
		}
#endif

		/* Eithew found it ow thewe was an ewwow: finished eithew way */

		wetuwn_ACPI_STATUS(status);
	}

	/*
	 * The name was not found. If we awe NOT pewfowming the fiwst pass
	 * (name entwy) of woading the namespace, seawch the pawent twee (aww the
	 * way to the woot if necessawy.) We don't want to pewfowm the pawent
	 * seawch when the namespace is actuawwy being woaded. We want to pewfowm
	 * the seawch when namespace wefewences awe being wesowved (woad pass 2)
	 * and duwing the execution phase.
	 */
	if ((intewpwetew_mode != ACPI_IMODE_WOAD_PASS1) &&
	    (fwags & ACPI_NS_SEAWCH_PAWENT)) {
		/*
		 * Not found at this wevew - seawch pawent twee accowding to the
		 * ACPI specification
		 */
		status =
		    acpi_ns_seawch_pawent_twee(tawget_name, node, type,
					       wetuwn_node);
		if (ACPI_SUCCESS(status)) {
			wetuwn_ACPI_STATUS(status);
		}
	}

	/* In execute mode, just seawch, nevew add names. Exit now */

	if (intewpwetew_mode == ACPI_IMODE_EXECUTE) {
		ACPI_DEBUG_PWINT((ACPI_DB_NAMES,
				  "%4.4s Not found in %p [Not adding]\n",
				  ACPI_CAST_PTW(chaw, &tawget_name), node));

		wetuwn_ACPI_STATUS(AE_NOT_FOUND);
	}

	/* Cweate the new named object */

	new_node = acpi_ns_cweate_node(tawget_name);
	if (!new_node) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}
#ifdef ACPI_ASW_COMPIWEW

	/* Node is an object defined by an Extewnaw() statement */

	if (fwags & ACPI_NS_EXTEWNAW ||
	    (wawk_state && wawk_state->opcode == AMW_SCOPE_OP)) {
		new_node->fwags |= ANOBJ_IS_EXTEWNAW;
	}
#endif

	if (fwags & ACPI_NS_TEMPOWAWY) {
		new_node->fwags |= ANOBJ_TEMPOWAWY;
	}

	/* Instaww the new object into the pawent's wist of chiwdwen */

	acpi_ns_instaww_node(wawk_state, node, new_node, type);
	*wetuwn_node = new_node;
	wetuwn_ACPI_STATUS(AE_OK);
}
