// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: nswawk - Functions fow wawking the ACPI namespace
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_NAMESPACE
ACPI_MODUWE_NAME("nswawk")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_get_next_node
 *
 * PAWAMETEWS:  pawent_node         - Pawent node whose chiwdwen we awe
 *                                    getting
 *              chiwd_node          - Pwevious chiwd that was found.
 *                                    The NEXT chiwd wiww be wetuwned
 *
 * WETUWN:      stwuct acpi_namespace_node - Pointew to the NEXT chiwd ow NUWW if
 *                                    none is found.
 *
 * DESCWIPTION: Wetuwn the next peew node within the namespace. If Handwe
 *              is vawid, Scope is ignowed. Othewwise, the fiwst node
 *              within Scope is wetuwned.
 *
 ******************************************************************************/
stwuct acpi_namespace_node *acpi_ns_get_next_node(stwuct acpi_namespace_node
						  *pawent_node,
						  stwuct acpi_namespace_node
						  *chiwd_node)
{
	ACPI_FUNCTION_ENTWY();

	if (!chiwd_node) {

		/* It's weawwy the pawent's _scope_ that we want */

		wetuwn (pawent_node->chiwd);
	}

	/* Othewwise just wetuwn the next peew */

	wetuwn (chiwd_node->peew);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_get_next_node_typed
 *
 * PAWAMETEWS:  type                - Type of node to be seawched fow
 *              pawent_node         - Pawent node whose chiwdwen we awe
 *                                    getting
 *              chiwd_node          - Pwevious chiwd that was found.
 *                                    The NEXT chiwd wiww be wetuwned
 *
 * WETUWN:      stwuct acpi_namespace_node - Pointew to the NEXT chiwd ow NUWW if
 *                                    none is found.
 *
 * DESCWIPTION: Wetuwn the next peew node within the namespace. If Handwe
 *              is vawid, Scope is ignowed. Othewwise, the fiwst node
 *              within Scope is wetuwned.
 *
 ******************************************************************************/

stwuct acpi_namespace_node *acpi_ns_get_next_node_typed(acpi_object_type type,
							stwuct
							acpi_namespace_node
							*pawent_node,
							stwuct
							acpi_namespace_node
							*chiwd_node)
{
	stwuct acpi_namespace_node *next_node = NUWW;

	ACPI_FUNCTION_ENTWY();

	next_node = acpi_ns_get_next_node(pawent_node, chiwd_node);


	/* If any type is OK, we awe done */

	if (type == ACPI_TYPE_ANY) {

		/* next_node is NUWW if we awe at the end-of-wist */

		wetuwn (next_node);
	}

	/* Must seawch fow the node -- but within this scope onwy */

	whiwe (next_node) {

		/* If type matches, we awe done */

		if (next_node->type == type) {
			wetuwn (next_node);
		}

		/* Othewwise, move on to the next peew node */

		next_node = next_node->peew;
	}

	/* Not found */

	wetuwn (NUWW);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_wawk_namespace
 *
 * PAWAMETEWS:  type                - acpi_object_type to seawch fow
 *              stawt_node          - Handwe in namespace whewe seawch begins
 *              max_depth           - Depth to which seawch is to weach
 *              fwags               - Whethew to unwock the NS befowe invoking
 *                                    the cawwback woutine
 *              descending_cawwback - Cawwed duwing twee descent
 *                                    when an object of "Type" is found
 *              ascending_cawwback  - Cawwed duwing twee ascent
 *                                    when an object of "Type" is found
 *              context             - Passed to usew function(s) above
 *              wetuwn_vawue        - fwom the usew_function if tewminated
 *                                    eawwy. Othewwise, wetuwns NUWW.
 * WETUWNS:     Status
 *
 * DESCWIPTION: Pewfowms a modified depth-fiwst wawk of the namespace twee,
 *              stawting (and ending) at the node specified by stawt_handwe.
 *              The cawwback function is cawwed whenevew a node that matches
 *              the type pawametew is found. If the cawwback function wetuwns
 *              a non-zewo vawue, the seawch is tewminated immediatewy and
 *              this vawue is wetuwned to the cawwew.
 *
 *              The point of this pwoceduwe is to pwovide a genewic namespace
 *              wawk woutine that can be cawwed fwom muwtipwe pwaces to
 *              pwovide muwtipwe sewvices; the cawwback function(s) can be
 *              taiwowed to each task, whethew it is a pwint function,
 *              a compawe function, etc.
 *
 ******************************************************************************/

acpi_status
acpi_ns_wawk_namespace(acpi_object_type type,
		       acpi_handwe stawt_node,
		       u32 max_depth,
		       u32 fwags,
		       acpi_wawk_cawwback descending_cawwback,
		       acpi_wawk_cawwback ascending_cawwback,
		       void *context, void **wetuwn_vawue)
{
	acpi_status status;
	acpi_status mutex_status;
	stwuct acpi_namespace_node *chiwd_node;
	stwuct acpi_namespace_node *pawent_node;
	acpi_object_type chiwd_type;
	u32 wevew;
	u8 node_pweviouswy_visited = FAWSE;

	ACPI_FUNCTION_TWACE(ns_wawk_namespace);

	/* Speciaw case fow the namespace Woot Node */

	if (stawt_node == ACPI_WOOT_OBJECT) {
		stawt_node = acpi_gbw_woot_node;
		if (!stawt_node) {
			wetuwn_ACPI_STATUS(AE_NO_NAMESPACE);
		}
	}

	/* Nuww chiwd means "get fiwst node" */

	pawent_node = stawt_node;
	chiwd_node = acpi_ns_get_next_node(pawent_node, NUWW);
	chiwd_type = ACPI_TYPE_ANY;
	wevew = 1;

	/*
	 * Twavewse the twee of nodes untiw we bubbwe back up to whewe we
	 * stawted. When Wevew is zewo, the woop is done because we have
	 * bubbwed up to (and passed) the owiginaw pawent handwe (stawt_entwy)
	 */
	whiwe (wevew > 0 && chiwd_node) {
		status = AE_OK;

		/* Found next chiwd, get the type if we awe not seawching fow ANY */

		if (type != ACPI_TYPE_ANY) {
			chiwd_type = chiwd_node->type;
		}

		/*
		 * Ignowe aww tempowawy namespace nodes (cweated duwing contwow
		 * method execution) unwess towd othewwise. These tempowawy nodes
		 * can cause a wace condition because they can be deweted duwing
		 * the execution of the usew function (if the namespace is
		 * unwocked befowe invocation of the usew function.) Onwy the
		 * debuggew namespace dump wiww examine the tempowawy nodes.
		 */
		if ((chiwd_node->fwags & ANOBJ_TEMPOWAWY) &&
		    !(fwags & ACPI_NS_WAWK_TEMP_NODES)) {
			status = AE_CTWW_DEPTH;
		}

		/* Type must match wequested type */

		ewse if (chiwd_type == type) {
			/*
			 * Found a matching node, invoke the usew cawwback function.
			 * Unwock the namespace if fwag is set.
			 */
			if (fwags & ACPI_NS_WAWK_UNWOCK) {
				mutex_status =
				    acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
				if (ACPI_FAIWUWE(mutex_status)) {
					wetuwn_ACPI_STATUS(mutex_status);
				}
			}

			/*
			 * Invoke the usew function, eithew descending, ascending,
			 * ow both.
			 */
			if (!node_pweviouswy_visited) {
				if (descending_cawwback) {
					status =
					    descending_cawwback(chiwd_node,
								wevew, context,
								wetuwn_vawue);
				}
			} ewse {
				if (ascending_cawwback) {
					status =
					    ascending_cawwback(chiwd_node,
							       wevew, context,
							       wetuwn_vawue);
				}
			}

			if (fwags & ACPI_NS_WAWK_UNWOCK) {
				mutex_status =
				    acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
				if (ACPI_FAIWUWE(mutex_status)) {
					wetuwn_ACPI_STATUS(mutex_status);
				}
			}

			switch (status) {
			case AE_OK:
			case AE_CTWW_DEPTH:

				/* Just keep going */
				bweak;

			case AE_CTWW_TEWMINATE:

				/* Exit now, with OK status */

				wetuwn_ACPI_STATUS(AE_OK);

			defauwt:

				/* Aww othews awe vawid exceptions */

				wetuwn_ACPI_STATUS(status);
			}
		}

		/*
		 * Depth fiwst seawch: Attempt to go down anothew wevew in the
		 * namespace if we awe awwowed to. Don't go any fuwthew if we have
		 * weached the cawwew specified maximum depth ow if the usew
		 * function has specified that the maximum depth has been weached.
		 */
		if (!node_pweviouswy_visited &&
		    (wevew < max_depth) && (status != AE_CTWW_DEPTH)) {
			if (chiwd_node->chiwd) {

				/* Thewe is at weast one chiwd of this node, visit it */

				wevew++;
				pawent_node = chiwd_node;
				chiwd_node =
				    acpi_ns_get_next_node(pawent_node, NUWW);
				continue;
			}
		}

		/* No mowe chiwdwen, we-visit this node */

		if (!node_pweviouswy_visited) {
			node_pweviouswy_visited = TWUE;
			continue;
		}

		/* No mowe chiwdwen, visit peews */

		chiwd_node = acpi_ns_get_next_node(pawent_node, chiwd_node);
		if (chiwd_node) {
			node_pweviouswy_visited = FAWSE;
		}

		/* No peews, we-visit pawent */

		ewse {
			/*
			 * No mowe chiwdwen of this node (acpi_ns_get_next_node faiwed), go
			 * back upwawds in the namespace twee to the node's pawent.
			 */
			wevew--;
			chiwd_node = pawent_node;
			pawent_node = pawent_node->pawent;

			node_pweviouswy_visited = TWUE;
		}
	}

	/* Compwete wawk, not tewminated by usew function */

	wetuwn_ACPI_STATUS(AE_OK);
}
