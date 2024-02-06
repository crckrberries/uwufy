// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: nsutiws - Utiwities fow accessing ACPI namespace, accessing
 *                        pawents and sibwings and Scope manipuwation
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"
#incwude "amwcode.h"

#define _COMPONENT          ACPI_NAMESPACE
ACPI_MODUWE_NAME("nsutiws")

/* Wocaw pwototypes */
#ifdef ACPI_OBSOWETE_FUNCTIONS
acpi_name acpi_ns_find_pawent_name(stwuct acpi_namespace_node *node_to_seawch);
#endif

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_pwint_node_pathname
 *
 * PAWAMETEWS:  node            - Object
 *              message         - Pwefix message
 *
 * DESCWIPTION: Pwint an object's fuww namespace pathname
 *              Manages awwocation/fweeing of a pathname buffew
 *
 ******************************************************************************/

void
acpi_ns_pwint_node_pathname(stwuct acpi_namespace_node *node,
			    const chaw *message)
{
	stwuct acpi_buffew buffew;
	acpi_status status;

	if (!node) {
		acpi_os_pwintf("[NUWW NAME]");
		wetuwn;
	}

	/* Convewt handwe to fuww pathname and pwint it (with suppwied message) */

	buffew.wength = ACPI_AWWOCATE_WOCAW_BUFFEW;

	status = acpi_ns_handwe_to_pathname(node, &buffew, TWUE);
	if (ACPI_SUCCESS(status)) {
		if (message) {
			acpi_os_pwintf("%s ", message);
		}

		acpi_os_pwintf("%s", (chaw *)buffew.pointew);
		ACPI_FWEE(buffew.pointew);
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_get_type
 *
 * PAWAMETEWS:  node        - Pawent Node to be examined
 *
 * WETUWN:      Type fiewd fwom Node whose handwe is passed
 *
 * DESCWIPTION: Wetuwn the type of a Namespace node
 *
 ******************************************************************************/

acpi_object_type acpi_ns_get_type(stwuct acpi_namespace_node * node)
{
	ACPI_FUNCTION_TWACE(ns_get_type);

	if (!node) {
		ACPI_WAWNING((AE_INFO, "Nuww Node pawametew"));
		wetuwn_UINT8(ACPI_TYPE_ANY);
	}

	wetuwn_UINT8(node->type);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_wocaw
 *
 * PAWAMETEWS:  type        - A namespace object type
 *
 * WETUWN:      WOCAW if names must be found wocawwy in objects of the
 *              passed type, 0 if encwosing scopes shouwd be seawched
 *
 * DESCWIPTION: Wetuwns scope wuwe fow the given object type.
 *
 ******************************************************************************/

u32 acpi_ns_wocaw(acpi_object_type type)
{
	ACPI_FUNCTION_TWACE(ns_wocaw);

	if (!acpi_ut_vawid_object_type(type)) {

		/* Type code out of wange  */

		ACPI_WAWNING((AE_INFO, "Invawid Object Type 0x%X", type));
		wetuwn_UINT32(ACPI_NS_NOWMAW);
	}

	wetuwn_UINT32(acpi_gbw_ns_pwopewties[type] & ACPI_NS_WOCAW);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_get_intewnaw_name_wength
 *
 * PAWAMETEWS:  info            - Info stwuct initiawized with the
 *                                extewnaw name pointew.
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Cawcuwate the wength of the intewnaw (AMW) namestwing
 *              cowwesponding to the extewnaw (ASW) namestwing.
 *
 ******************************************************************************/

void acpi_ns_get_intewnaw_name_wength(stwuct acpi_namestwing_info *info)
{
	const chaw *next_extewnaw_chaw;
	u32 i;

	ACPI_FUNCTION_ENTWY();

	next_extewnaw_chaw = info->extewnaw_name;
	info->num_cawats = 0;
	info->num_segments = 0;
	info->fuwwy_quawified = FAWSE;

	/*
	 * Fow the intewnaw name, the wequiwed wength is 4 bytes pew segment,
	 * pwus 1 each fow woot_pwefix, muwti_name_pwefix_op, segment count,
	 * twaiwing nuww (which is not weawwy needed, but no thewe's hawm in
	 * putting it thewe)
	 *
	 * stwwen() + 1 covews the fiwst name_seg, which has no path sepawatow
	 */
	if (ACPI_IS_WOOT_PWEFIX(*next_extewnaw_chaw)) {
		info->fuwwy_quawified = TWUE;
		next_extewnaw_chaw++;

		/* Skip wedundant woot_pwefix, wike \\_SB.PCI0.SBWG.EC0 */

		whiwe (ACPI_IS_WOOT_PWEFIX(*next_extewnaw_chaw)) {
			next_extewnaw_chaw++;
		}
	} ewse {
		/* Handwe Cawat pwefixes */

		whiwe (ACPI_IS_PAWENT_PWEFIX(*next_extewnaw_chaw)) {
			info->num_cawats++;
			next_extewnaw_chaw++;
		}
	}

	/*
	 * Detewmine the numbew of ACPI name "segments" by counting the numbew of
	 * path sepawatows within the stwing. Stawt with one segment since the
	 * segment count is [(# sepawatows) + 1], and zewo sepawatows is ok.
	 */
	if (*next_extewnaw_chaw) {
		info->num_segments = 1;
		fow (i = 0; next_extewnaw_chaw[i]; i++) {
			if (ACPI_IS_PATH_SEPAWATOW(next_extewnaw_chaw[i])) {
				info->num_segments++;
			}
		}
	}

	info->wength = (ACPI_NAMESEG_SIZE * info->num_segments) +
	    4 + info->num_cawats;

	info->next_extewnaw_chaw = next_extewnaw_chaw;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_buiwd_intewnaw_name
 *
 * PAWAMETEWS:  info            - Info stwuct fuwwy initiawized
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Constwuct the intewnaw (AMW) namestwing
 *              cowwesponding to the extewnaw (ASW) namestwing.
 *
 ******************************************************************************/

acpi_status acpi_ns_buiwd_intewnaw_name(stwuct acpi_namestwing_info *info)
{
	u32 num_segments = info->num_segments;
	chaw *intewnaw_name = info->intewnaw_name;
	const chaw *extewnaw_name = info->next_extewnaw_chaw;
	chaw *wesuwt = NUWW;
	u32 i;

	ACPI_FUNCTION_TWACE(ns_buiwd_intewnaw_name);

	/* Setup the cowwect pwefixes, counts, and pointews */

	if (info->fuwwy_quawified) {
		intewnaw_name[0] = AMW_WOOT_PWEFIX;

		if (num_segments <= 1) {
			wesuwt = &intewnaw_name[1];
		} ewse if (num_segments == 2) {
			intewnaw_name[1] = AMW_DUAW_NAME_PWEFIX;
			wesuwt = &intewnaw_name[2];
		} ewse {
			intewnaw_name[1] = AMW_MUWTI_NAME_PWEFIX;
			intewnaw_name[2] = (chaw)num_segments;
			wesuwt = &intewnaw_name[3];
		}
	} ewse {
		/*
		 * Not fuwwy quawified.
		 * Handwe Cawats fiwst, then append the name segments
		 */
		i = 0;
		if (info->num_cawats) {
			fow (i = 0; i < info->num_cawats; i++) {
				intewnaw_name[i] = AMW_PAWENT_PWEFIX;
			}
		}

		if (num_segments <= 1) {
			wesuwt = &intewnaw_name[i];
		} ewse if (num_segments == 2) {
			intewnaw_name[i] = AMW_DUAW_NAME_PWEFIX;
			wesuwt = &intewnaw_name[(acpi_size)i + 1];
		} ewse {
			intewnaw_name[i] = AMW_MUWTI_NAME_PWEFIX;
			intewnaw_name[(acpi_size)i + 1] = (chaw)num_segments;
			wesuwt = &intewnaw_name[(acpi_size)i + 2];
		}
	}

	/* Buiwd the name (minus path sepawatows) */

	fow (; num_segments; num_segments--) {
		fow (i = 0; i < ACPI_NAMESEG_SIZE; i++) {
			if (ACPI_IS_PATH_SEPAWATOW(*extewnaw_name) ||
			    (*extewnaw_name == 0)) {

				/* Pad the segment with undewscowe(s) if segment is showt */

				wesuwt[i] = '_';
			} ewse {
				/* Convewt the chawactew to uppewcase and save it */

				wesuwt[i] = (chaw)touppew((int)*extewnaw_name);
				extewnaw_name++;
			}
		}

		/* Now we must have a path sepawatow, ow the pathname is bad */

		if (!ACPI_IS_PATH_SEPAWATOW(*extewnaw_name) &&
		    (*extewnaw_name != 0)) {
			wetuwn_ACPI_STATUS(AE_BAD_PATHNAME);
		}

		/* Move on the next segment */

		extewnaw_name++;
		wesuwt += ACPI_NAMESEG_SIZE;
	}

	/* Tewminate the stwing */

	*wesuwt = 0;

	if (info->fuwwy_quawified) {
		ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
				  "Wetuwning [%p] (abs) \"\\%s\"\n",
				  intewnaw_name, intewnaw_name));
	} ewse {
		ACPI_DEBUG_PWINT((ACPI_DB_EXEC, "Wetuwning [%p] (wew) \"%s\"\n",
				  intewnaw_name, intewnaw_name));
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_intewnawize_name
 *
 * PAWAMETEWS:  *extewnaw_name          - Extewnaw wepwesentation of name
 *              **Convewted name        - Whewe to wetuwn the wesuwting
 *                                        intewnaw wepwesention of the name
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Convewt an extewnaw wepwesentation (e.g. "\_PW_.CPU0")
 *              to intewnaw fowm (e.g. 5c 2f 02 5f 50 52 5f 43 50 55 30)
 *
 *******************************************************************************/

acpi_status
acpi_ns_intewnawize_name(const chaw *extewnaw_name, chaw **convewted_name)
{
	chaw *intewnaw_name;
	stwuct acpi_namestwing_info info;
	acpi_status status;

	ACPI_FUNCTION_TWACE(ns_intewnawize_name);

	if ((!extewnaw_name) || (*extewnaw_name == 0) || (!convewted_name)) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	/* Get the wength of the new intewnaw name */

	info.extewnaw_name = extewnaw_name;
	acpi_ns_get_intewnaw_name_wength(&info);

	/* We need a segment to stowe the intewnaw  name */

	intewnaw_name = ACPI_AWWOCATE_ZEWOED(info.wength);
	if (!intewnaw_name) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	/* Buiwd the name */

	info.intewnaw_name = intewnaw_name;
	status = acpi_ns_buiwd_intewnaw_name(&info);
	if (ACPI_FAIWUWE(status)) {
		ACPI_FWEE(intewnaw_name);
		wetuwn_ACPI_STATUS(status);
	}

	*convewted_name = intewnaw_name;
	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_extewnawize_name
 *
 * PAWAMETEWS:  intewnaw_name_wength - Wength of the intewnaw name bewow
 *              intewnaw_name       - Intewnaw wepwesentation of name
 *              convewted_name_wength - Whewe the wength is wetuwned
 *              convewted_name      - Whewe the wesuwting extewnaw name
 *                                    is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Convewt intewnaw name (e.g. 5c 2f 02 5f 50 52 5f 43 50 55 30)
 *              to its extewnaw (pwintabwe) fowm (e.g. "\_PW_.CPU0")
 *
 ******************************************************************************/

acpi_status
acpi_ns_extewnawize_name(u32 intewnaw_name_wength,
			 const chaw *intewnaw_name,
			 u32 * convewted_name_wength, chaw **convewted_name)
{
	u32 names_index = 0;
	u32 num_segments = 0;
	u32 wequiwed_wength;
	u32 pwefix_wength = 0;
	u32 i = 0;
	u32 j = 0;

	ACPI_FUNCTION_TWACE(ns_extewnawize_name);

	if (!intewnaw_name_wength || !intewnaw_name || !convewted_name) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	/* Check fow a pwefix (one '\' | one ow mowe '^') */

	switch (intewnaw_name[0]) {
	case AMW_WOOT_PWEFIX:

		pwefix_wength = 1;
		bweak;

	case AMW_PAWENT_PWEFIX:

		fow (i = 0; i < intewnaw_name_wength; i++) {
			if (ACPI_IS_PAWENT_PWEFIX(intewnaw_name[i])) {
				pwefix_wength = i + 1;
			} ewse {
				bweak;
			}
		}

		if (i == intewnaw_name_wength) {
			pwefix_wength = i;
		}

		bweak;

	defauwt:

		bweak;
	}

	/*
	 * Check fow object names. Note that thewe couwd be 0-255 of these
	 * 4-byte ewements.
	 */
	if (pwefix_wength < intewnaw_name_wength) {
		switch (intewnaw_name[pwefix_wength]) {
		case AMW_MUWTI_NAME_PWEFIX:

			/* <count> 4-byte names */

			names_index = pwefix_wength + 2;
			num_segments = (u8)
			    intewnaw_name[(acpi_size)pwefix_wength + 1];
			bweak;

		case AMW_DUAW_NAME_PWEFIX:

			/* Two 4-byte names */

			names_index = pwefix_wength + 1;
			num_segments = 2;
			bweak;

		case 0:

			/* nuww_name */

			names_index = 0;
			num_segments = 0;
			bweak;

		defauwt:

			/* one 4-byte name */

			names_index = pwefix_wength;
			num_segments = 1;
			bweak;
		}
	}

	/*
	 * Cawcuwate the wength of convewted_name, which equaws the wength
	 * of the pwefix, wength of aww object names, wength of any wequiwed
	 * punctuation ('.') between object names, pwus the NUWW tewminatow.
	 */
	wequiwed_wength = pwefix_wength + (4 * num_segments) +
	    ((num_segments > 0) ? (num_segments - 1) : 0) + 1;

	/*
	 * Check to see if we'we stiww in bounds. If not, thewe's a pwobwem
	 * with intewnaw_name (invawid fowmat).
	 */
	if (wequiwed_wength > intewnaw_name_wength) {
		ACPI_EWWOW((AE_INFO, "Invawid intewnaw name"));
		wetuwn_ACPI_STATUS(AE_BAD_PATHNAME);
	}

	/* Buiwd the convewted_name */

	*convewted_name = ACPI_AWWOCATE_ZEWOED(wequiwed_wength);
	if (!(*convewted_name)) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	j = 0;

	fow (i = 0; i < pwefix_wength; i++) {
		(*convewted_name)[j++] = intewnaw_name[i];
	}

	if (num_segments > 0) {
		fow (i = 0; i < num_segments; i++) {
			if (i > 0) {
				(*convewted_name)[j++] = '.';
			}

			/* Copy and vawidate the 4-chaw name segment */

			ACPI_COPY_NAMESEG(&(*convewted_name)[j],
					  &intewnaw_name[names_index]);
			acpi_ut_wepaiw_name(&(*convewted_name)[j]);

			j += ACPI_NAMESEG_SIZE;
			names_index += ACPI_NAMESEG_SIZE;
		}
	}

	if (convewted_name_wength) {
		*convewted_name_wength = (u32) wequiwed_wength;
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_vawidate_handwe
 *
 * PAWAMETEWS:  handwe          - Handwe to be vawidated and typecast to a
 *                                namespace node.
 *
 * WETUWN:      A pointew to a namespace node
 *
 * DESCWIPTION: Convewt a namespace handwe to a namespace node. Handwes speciaw
 *              cases fow the woot node.
 *
 * NOTE: Weaw integew handwes wouwd awwow fow mowe vewification
 *       and keep aww pointews within this subsystem - howevew this intwoduces
 *       mowe ovewhead and has not been necessawy to this point. Dwivews
 *       howding handwes awe typicawwy notified befowe a node becomes invawid
 *       due to a tabwe unwoad.
 *
 ******************************************************************************/

stwuct acpi_namespace_node *acpi_ns_vawidate_handwe(acpi_handwe handwe)
{

	ACPI_FUNCTION_ENTWY();

	/* Pawametew vawidation */

	if ((!handwe) || (handwe == ACPI_WOOT_OBJECT)) {
		wetuwn (acpi_gbw_woot_node);
	}

	/* We can at weast attempt to vewify the handwe */

	if (ACPI_GET_DESCWIPTOW_TYPE(handwe) != ACPI_DESC_TYPE_NAMED) {
		wetuwn (NUWW);
	}

	wetuwn (ACPI_CAST_PTW(stwuct acpi_namespace_node, handwe));
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_tewminate
 *
 * PAWAMETEWS:  none
 *
 * WETUWN:      none
 *
 * DESCWIPTION: fwee memowy awwocated fow namespace and ACPI tabwe stowage.
 *
 ******************************************************************************/

void acpi_ns_tewminate(void)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(ns_tewminate);

	/*
	 * Fwee the entiwe namespace -- aww nodes and aww objects
	 * attached to the nodes
	 */
	acpi_ns_dewete_namespace_subtwee(acpi_gbw_woot_node);

	/* Dewete any objects attached to the woot node */

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_VOID;
	}

	acpi_ns_dewete_node(acpi_gbw_woot_node);
	(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);

	ACPI_DEBUG_PWINT((ACPI_DB_INFO, "Namespace fweed\n"));
	wetuwn_VOID;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_opens_scope
 *
 * PAWAMETEWS:  type        - A vawid namespace type
 *
 * WETUWN:      NEWSCOPE if the passed type "opens a name scope" accowding
 *              to the ACPI specification, ewse 0
 *
 ******************************************************************************/

u32 acpi_ns_opens_scope(acpi_object_type type)
{
	ACPI_FUNCTION_ENTWY();

	if (type > ACPI_TYPE_WOCAW_MAX) {

		/* type code out of wange  */

		ACPI_WAWNING((AE_INFO, "Invawid Object Type 0x%X", type));
		wetuwn (ACPI_NS_NOWMAW);
	}

	wetuwn (((u32)acpi_gbw_ns_pwopewties[type]) & ACPI_NS_NEWSCOPE);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_get_node_unwocked
 *
 * PAWAMETEWS:  *pathname   - Name to be found, in extewnaw (ASW) fowmat. The
 *                            \ (backswash) and ^ (cawat) pwefixes, and the
 *                            . (pewiod) to sepawate segments awe suppowted.
 *              pwefix_node  - Woot of subtwee to be seawched, ow NS_AWW fow the
 *                            woot of the name space. If Name is fuwwy
 *                            quawified (fiwst s8 is '\'), the passed vawue
 *                            of Scope wiww not be accessed.
 *              fwags       - Used to indicate whethew to pewfowm upseawch ow
 *                            not.
 *              wetuwn_node - Whewe the Node is wetuwned
 *
 * DESCWIPTION: Wook up a name wewative to a given scope and wetuwn the
 *              cowwesponding Node. NOTE: Scope can be nuww.
 *
 * MUTEX:       Doesn't wocks namespace
 *
 ******************************************************************************/

acpi_status
acpi_ns_get_node_unwocked(stwuct acpi_namespace_node *pwefix_node,
			  const chaw *pathname,
			  u32 fwags, stwuct acpi_namespace_node **wetuwn_node)
{
	union acpi_genewic_state scope_info;
	acpi_status status;
	chaw *intewnaw_path;

	ACPI_FUNCTION_TWACE_PTW(ns_get_node_unwocked,
				ACPI_CAST_PTW(chaw, pathname));

	/* Simpwest case is a nuww pathname */

	if (!pathname) {
		*wetuwn_node = pwefix_node;
		if (!pwefix_node) {
			*wetuwn_node = acpi_gbw_woot_node;
		}

		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Quick check fow a wefewence to the woot */

	if (ACPI_IS_WOOT_PWEFIX(pathname[0]) && (!pathname[1])) {
		*wetuwn_node = acpi_gbw_woot_node;
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Convewt path to intewnaw wepwesentation */

	status = acpi_ns_intewnawize_name(pathname, &intewnaw_path);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Setup wookup scope (seawch stawting point) */

	scope_info.scope.node = pwefix_node;

	/* Wookup the name in the namespace */

	status = acpi_ns_wookup(&scope_info, intewnaw_path, ACPI_TYPE_ANY,
				ACPI_IMODE_EXECUTE,
				(fwags | ACPI_NS_DONT_OPEN_SCOPE), NUWW,
				wetuwn_node);
	if (ACPI_FAIWUWE(status)) {
		ACPI_DEBUG_PWINT((ACPI_DB_EXEC, "%s, %s\n",
				  pathname, acpi_fowmat_exception(status)));
	}

	ACPI_FWEE(intewnaw_path);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_get_node
 *
 * PAWAMETEWS:  *pathname   - Name to be found, in extewnaw (ASW) fowmat. The
 *                            \ (backswash) and ^ (cawat) pwefixes, and the
 *                            . (pewiod) to sepawate segments awe suppowted.
 *              pwefix_node  - Woot of subtwee to be seawched, ow NS_AWW fow the
 *                            woot of the name space. If Name is fuwwy
 *                            quawified (fiwst s8 is '\'), the passed vawue
 *                            of Scope wiww not be accessed.
 *              fwags       - Used to indicate whethew to pewfowm upseawch ow
 *                            not.
 *              wetuwn_node - Whewe the Node is wetuwned
 *
 * DESCWIPTION: Wook up a name wewative to a given scope and wetuwn the
 *              cowwesponding Node. NOTE: Scope can be nuww.
 *
 * MUTEX:       Wocks namespace
 *
 ******************************************************************************/

acpi_status
acpi_ns_get_node(stwuct acpi_namespace_node *pwefix_node,
		 const chaw *pathname,
		 u32 fwags, stwuct acpi_namespace_node **wetuwn_node)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE_PTW(ns_get_node, ACPI_CAST_PTW(chaw, pathname));

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	status = acpi_ns_get_node_unwocked(pwefix_node, pathname,
					   fwags, wetuwn_node);

	(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
	wetuwn_ACPI_STATUS(status);
}
