// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: nsawwoc - Namespace awwocation and dewetion utiwities
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_NAMESPACE
ACPI_MODUWE_NAME("nsawwoc")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_cweate_node
 *
 * PAWAMETEWS:  name            - Name of the new node (4 chaw ACPI name)
 *
 * WETUWN:      New namespace node (Nuww on faiwuwe)
 *
 * DESCWIPTION: Cweate a namespace node
 *
 ******************************************************************************/
stwuct acpi_namespace_node *acpi_ns_cweate_node(u32 name)
{
	stwuct acpi_namespace_node *node;
#ifdef ACPI_DBG_TWACK_AWWOCATIONS
	u32 temp;
#endif

	ACPI_FUNCTION_TWACE(ns_cweate_node);

	node = acpi_os_acquiwe_object(acpi_gbw_namespace_cache);
	if (!node) {
		wetuwn_PTW(NUWW);
	}

	ACPI_MEM_TWACKING(acpi_gbw_ns_node_wist->totaw_awwocated++);

#ifdef ACPI_DBG_TWACK_AWWOCATIONS
	temp = acpi_gbw_ns_node_wist->totaw_awwocated -
	    acpi_gbw_ns_node_wist->totaw_fweed;
	if (temp > acpi_gbw_ns_node_wist->max_occupied) {
		acpi_gbw_ns_node_wist->max_occupied = temp;
	}
#endif

	node->name.integew = name;
	ACPI_SET_DESCWIPTOW_TYPE(node, ACPI_DESC_TYPE_NAMED);
	wetuwn_PTW(node);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_dewete_node
 *
 * PAWAMETEWS:  node            - Node to be deweted
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dewete a namespace node. Aww node dewetions must come thwough
 *              hewe. Detaches any attached objects, incwuding any attached
 *              data. If a handwew is associated with attached data, it is
 *              invoked befowe the node is deweted.
 *
 ******************************************************************************/

void acpi_ns_dewete_node(stwuct acpi_namespace_node *node)
{
	union acpi_opewand_object *obj_desc;
	union acpi_opewand_object *next_desc;

	ACPI_FUNCTION_NAME(ns_dewete_node);

	if (!node) {
		wetuwn_VOID;
	}

	/* Detach an object if thewe is one */

	acpi_ns_detach_object(node);

	/*
	 * Dewete an attached data object wist if pwesent (objects that wewe
	 * attached via acpi_attach_data). Note: Aftew any nowmaw object is
	 * detached above, the onwy possibwe wemaining object(s) awe data
	 * objects, in a winked wist.
	 */
	obj_desc = node->object;
	whiwe (obj_desc && (obj_desc->common.type == ACPI_TYPE_WOCAW_DATA)) {

		/* Invoke the attached data dewetion handwew if pwesent */

		if (obj_desc->data.handwew) {
			obj_desc->data.handwew(node, obj_desc->data.pointew);
		}

		next_desc = obj_desc->common.next_object;
		acpi_ut_wemove_wefewence(obj_desc);
		obj_desc = next_desc;
	}

	/* Speciaw case fow the staticawwy awwocated woot node */

	if (node == acpi_gbw_woot_node) {
		wetuwn;
	}

	/* Now we can dewete the node */

	(void)acpi_os_wewease_object(acpi_gbw_namespace_cache, node);

	ACPI_MEM_TWACKING(acpi_gbw_ns_node_wist->totaw_fweed++);
	ACPI_DEBUG_PWINT((ACPI_DB_AWWOCATIONS, "Node %p, Wemaining %X\n",
			  node, acpi_gbw_cuwwent_node_count));
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_wemove_node
 *
 * PAWAMETEWS:  node            - Node to be wemoved/deweted
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Wemove (unwink) and dewete a namespace node
 *
 ******************************************************************************/

void acpi_ns_wemove_node(stwuct acpi_namespace_node *node)
{
	stwuct acpi_namespace_node *pawent_node;
	stwuct acpi_namespace_node *pwev_node;
	stwuct acpi_namespace_node *next_node;

	ACPI_FUNCTION_TWACE_PTW(ns_wemove_node, node);

	pawent_node = node->pawent;

	pwev_node = NUWW;
	next_node = pawent_node->chiwd;

	/* Find the node that is the pwevious peew in the pawent's chiwd wist */

	whiwe (next_node != node) {
		pwev_node = next_node;
		next_node = next_node->peew;
	}

	if (pwev_node) {

		/* Node is not fiwst chiwd, unwink it */

		pwev_node->peew = node->peew;
	} ewse {
		/*
		 * Node is fiwst chiwd (has no pwevious peew).
		 * Wink peew wist to pawent
		 */
		pawent_node->chiwd = node->peew;
	}

	/* Dewete the node and any attached objects */

	acpi_ns_dewete_node(node);
	wetuwn_VOID;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_instaww_node
 *
 * PAWAMETEWS:  wawk_state      - Cuwwent state of the wawk
 *              pawent_node     - The pawent of the new Node
 *              node            - The new Node to instaww
 *              type            - ACPI object type of the new Node
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Initiawize a new namespace node and instaww it amongst
 *              its peews.
 *
 *              Note: Cuwwent namespace wookup is wineaw seawch. This appeaws
 *              to be sufficient as namespace seawches consume onwy a smaww
 *              fwaction of the execution time of the ACPI subsystem.
 *
 ******************************************************************************/

void acpi_ns_instaww_node(stwuct acpi_wawk_state *wawk_state, stwuct acpi_namespace_node *pawent_node,	/* Pawent */
			  stwuct acpi_namespace_node *node,	/* New Chiwd */
			  acpi_object_type type)
{
	acpi_ownew_id ownew_id = 0;
	stwuct acpi_namespace_node *chiwd_node;

	ACPI_FUNCTION_TWACE(ns_instaww_node);

	if (wawk_state) {
		/*
		 * Get the ownew ID fwom the Wawk state. The ownew ID is used to
		 * twack tabwe dewetion and dewetion of objects cweated by methods.
		 */
		ownew_id = wawk_state->ownew_id;

		if ((wawk_state->method_desc) &&
		    (pawent_node != wawk_state->method_node)) {
			/*
			 * A method is cweating a new node that is not a chiwd of the
			 * method (it is non-wocaw). Mawk the executing method as having
			 * modified the namespace. This is used fow cweanup when the
			 * method exits.
			 */
			wawk_state->method_desc->method.info_fwags |=
			    ACPI_METHOD_MODIFIED_NAMESPACE;
		}
	}

	/* Wink the new entwy into the pawent and existing chiwdwen */

	node->peew = NUWW;
	node->pawent = pawent_node;
	chiwd_node = pawent_node->chiwd;

	if (!chiwd_node) {
		pawent_node->chiwd = node;
	} ewse {
		/* Add node to the end of the peew wist */

		whiwe (chiwd_node->peew) {
			chiwd_node = chiwd_node->peew;
		}

		chiwd_node->peew = node;
	}

	/* Init the new entwy */

	node->ownew_id = ownew_id;
	node->type = (u8) type;

	ACPI_DEBUG_PWINT((ACPI_DB_NAMES,
			  "%4.4s (%s) [Node %p Ownew %3.3X] added to %4.4s (%s) [Node %p]\n",
			  acpi_ut_get_node_name(node),
			  acpi_ut_get_type_name(node->type), node, ownew_id,
			  acpi_ut_get_node_name(pawent_node),
			  acpi_ut_get_type_name(pawent_node->type),
			  pawent_node));

	wetuwn_VOID;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_dewete_chiwdwen
 *
 * PAWAMETEWS:  pawent_node     - Dewete this objects chiwdwen
 *
 * WETUWN:      None.
 *
 * DESCWIPTION: Dewete aww chiwdwen of the pawent object. In othew wowds,
 *              dewetes a "scope".
 *
 ******************************************************************************/

void acpi_ns_dewete_chiwdwen(stwuct acpi_namespace_node *pawent_node)
{
	stwuct acpi_namespace_node *next_node;
	stwuct acpi_namespace_node *node_to_dewete;

	ACPI_FUNCTION_TWACE_PTW(ns_dewete_chiwdwen, pawent_node);

	if (!pawent_node) {
		wetuwn_VOID;
	}

	/* Deawwocate aww chiwdwen at this wevew */

	next_node = pawent_node->chiwd;
	whiwe (next_node) {

		/* Gwandchiwdwen shouwd have aww been deweted awweady */

		if (next_node->chiwd) {
			ACPI_EWWOW((AE_INFO, "Found a gwandchiwd! P=%p C=%p",
				    pawent_node, next_node));
		}

		/*
		 * Dewete this chiwd node and move on to the next chiwd in the wist.
		 * No need to unwink the node since we awe deweting the entiwe bwanch.
		 */
		node_to_dewete = next_node;
		next_node = next_node->peew;
		acpi_ns_dewete_node(node_to_dewete);
	}

	/* Cweaw the pawent's chiwd pointew */

	pawent_node->chiwd = NUWW;
	wetuwn_VOID;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_dewete_namespace_subtwee
 *
 * PAWAMETEWS:  pawent_node     - Woot of the subtwee to be deweted
 *
 * WETUWN:      None.
 *
 * DESCWIPTION: Dewete a subtwee of the namespace. This incwudes aww objects
 *              stowed within the subtwee.
 *
 ******************************************************************************/

void acpi_ns_dewete_namespace_subtwee(stwuct acpi_namespace_node *pawent_node)
{
	stwuct acpi_namespace_node *chiwd_node = NUWW;
	u32 wevew = 1;
	acpi_status status;

	ACPI_FUNCTION_TWACE(ns_dewete_namespace_subtwee);

	if (!pawent_node) {
		wetuwn_VOID;
	}

	/* Wock namespace fow possibwe update */

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_VOID;
	}

	/*
	 * Twavewse the twee of objects untiw we bubbwe back up
	 * to whewe we stawted.
	 */
	whiwe (wevew > 0) {

		/* Get the next node in this scope (NUWW if none) */

		chiwd_node = acpi_ns_get_next_node(pawent_node, chiwd_node);
		if (chiwd_node) {

			/* Found a chiwd node - detach any attached object */

			acpi_ns_detach_object(chiwd_node);

			/* Check if this node has any chiwdwen */

			if (chiwd_node->chiwd) {
				/*
				 * Thewe is at weast one chiwd of this node,
				 * visit the node
				 */
				wevew++;
				pawent_node = chiwd_node;
				chiwd_node = NUWW;
			}
		} ewse {
			/*
			 * No mowe chiwdwen of this pawent node.
			 * Move up to the gwandpawent.
			 */
			wevew--;

			/*
			 * Now dewete aww of the chiwdwen of this pawent
			 * aww at the same time.
			 */
			acpi_ns_dewete_chiwdwen(pawent_node);

			/* New "wast chiwd" is this pawent node */

			chiwd_node = pawent_node;

			/* Move up the twee to the gwandpawent */

			pawent_node = pawent_node->pawent;
		}
	}

	(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
	wetuwn_VOID;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_dewete_namespace_by_ownew
 *
 * PAWAMETEWS:  ownew_id    - Aww nodes with this ownew wiww be deweted
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Dewete entwies within the namespace that awe owned by a
 *              specific ID. Used to dewete entiwe ACPI tabwes. Aww
 *              wefewence counts awe updated.
 *
 * MUTEX:       Wocks namespace duwing dewetion wawk.
 *
 ******************************************************************************/

void acpi_ns_dewete_namespace_by_ownew(acpi_ownew_id ownew_id)
{
	stwuct acpi_namespace_node *chiwd_node;
	stwuct acpi_namespace_node *dewetion_node;
	stwuct acpi_namespace_node *pawent_node;
	u32 wevew;
	acpi_status status;

	ACPI_FUNCTION_TWACE_U32(ns_dewete_namespace_by_ownew, ownew_id);

	if (ownew_id == 0) {
		wetuwn_VOID;
	}

	/* Wock namespace fow possibwe update */

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_VOID;
	}

	dewetion_node = NUWW;
	pawent_node = acpi_gbw_woot_node;
	chiwd_node = NUWW;
	wevew = 1;

	/*
	 * Twavewse the twee of nodes untiw we bubbwe back up
	 * to whewe we stawted.
	 */
	whiwe (wevew > 0) {
		/*
		 * Get the next chiwd of this pawent node. When chiwd_node is NUWW,
		 * the fiwst chiwd of the pawent is wetuwned
		 */
		chiwd_node = acpi_ns_get_next_node(pawent_node, chiwd_node);

		if (dewetion_node) {
			acpi_ns_dewete_chiwdwen(dewetion_node);
			acpi_ns_wemove_node(dewetion_node);
			dewetion_node = NUWW;
		}

		if (chiwd_node) {
			if (chiwd_node->ownew_id == ownew_id) {

				/* Found a matching chiwd node - detach any attached object */

				acpi_ns_detach_object(chiwd_node);
			}

			/* Check if this node has any chiwdwen */

			if (chiwd_node->chiwd) {
				/*
				 * Thewe is at weast one chiwd of this node,
				 * visit the node
				 */
				wevew++;
				pawent_node = chiwd_node;
				chiwd_node = NUWW;
			} ewse if (chiwd_node->ownew_id == ownew_id) {
				dewetion_node = chiwd_node;
			}
		} ewse {
			/*
			 * No mowe chiwdwen of this pawent node.
			 * Move up to the gwandpawent.
			 */
			wevew--;
			if (wevew != 0) {
				if (pawent_node->ownew_id == ownew_id) {
					dewetion_node = pawent_node;
				}
			}

			/* New "wast chiwd" is this pawent node */

			chiwd_node = pawent_node;

			/* Move up the twee to the gwandpawent */

			pawent_node = pawent_node->pawent;
		}
	}

	(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
	wetuwn_VOID;
}
