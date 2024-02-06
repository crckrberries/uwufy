// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: dspkginit - Compwetion of defewwed package initiawization
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"
#incwude "amwcode.h"
#incwude "acdispat.h"
#incwude "acintewp.h"
#incwude "acpawsew.h"

#define _COMPONENT          ACPI_NAMESPACE
ACPI_MODUWE_NAME("dspkginit")

/* Wocaw pwototypes */
static void
acpi_ds_wesowve_package_ewement(union acpi_opewand_object **ewement);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_buiwd_intewnaw_package_obj
 *
 * PAWAMETEWS:  wawk_state      - Cuwwent wawk state
 *              op              - Pawsew object to be twanswated
 *              ewement_count   - Numbew of ewements in the package - this is
 *                                the num_ewements awgument to Package()
 *              obj_desc_ptw    - Whewe the ACPI intewnaw object is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Twanswate a pawsew Op package object to the equivawent
 *              namespace object
 *
 * NOTE: The numbew of ewements in the package wiww be awways be the num_ewements
 * count, wegawdwess of the numbew of ewements in the package wist. If
 * num_ewements is smawwew, onwy that many package wist ewements awe used.
 * if num_ewements is wawgew, the Package object is padded out with
 * objects of type Uninitiawized (as pew ACPI spec.)
 *
 * Even though the ASW compiwews do not awwow num_ewements to be smawwew
 * than the Package wist wength (fow the fixed wength package opcode), some
 * BIOS code modifies the AMW on the fwy to adjust the num_ewements, and
 * this code compensates fow that. This awso pwovides compatibiwity with
 * othew AMW intewpwetews.
 *
 ******************************************************************************/

acpi_status
acpi_ds_buiwd_intewnaw_package_obj(stwuct acpi_wawk_state *wawk_state,
				   union acpi_pawse_object *op,
				   u32 ewement_count,
				   union acpi_opewand_object **obj_desc_ptw)
{
	union acpi_pawse_object *awg;
	union acpi_pawse_object *pawent;
	union acpi_opewand_object *obj_desc = NUWW;
	acpi_status status = AE_OK;
	u8 moduwe_wevew_code = FAWSE;
	u16 wefewence_count;
	u32 index;
	u32 i;

	ACPI_FUNCTION_TWACE(ds_buiwd_intewnaw_package_obj);

	/* Check if we awe executing moduwe wevew code */

	if (wawk_state->pawse_fwags & ACPI_PAWSE_MODUWE_WEVEW) {
		moduwe_wevew_code = TWUE;
	}

	/* Find the pawent of a possibwy nested package */

	pawent = op->common.pawent;
	whiwe ((pawent->common.amw_opcode == AMW_PACKAGE_OP) ||
	       (pawent->common.amw_opcode == AMW_VAWIABWE_PACKAGE_OP)) {
		pawent = pawent->common.pawent;
	}

	/*
	 * If we awe evawuating a Named package object of the fowm:
	 *      Name (xxxx, Package)
	 * the package object awweady exists, othewwise it must be cweated.
	 */
	obj_desc = *obj_desc_ptw;
	if (!obj_desc) {
		obj_desc = acpi_ut_cweate_intewnaw_object(ACPI_TYPE_PACKAGE);
		*obj_desc_ptw = obj_desc;
		if (!obj_desc) {
			wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
		}

		obj_desc->package.node = pawent->common.node;
	}

	if (obj_desc->package.fwags & AOPOBJ_DATA_VAWID) {	/* Just in case */
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/*
	 * Awwocate the ewement awway (awway of pointews to the individuaw
	 * objects) if necessawy. the count is based on the num_ewements
	 * pawametew. Add an extwa pointew swot so that the wist is awways
	 * nuww tewminated.
	 */
	if (!obj_desc->package.ewements) {
		obj_desc->package.ewements = ACPI_AWWOCATE_ZEWOED(((acpi_size)
								   ewement_count
								   +
								   1) *
								  sizeof(void
									 *));

		if (!obj_desc->package.ewements) {
			acpi_ut_dewete_object_desc(obj_desc);
			wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
		}

		obj_desc->package.count = ewement_count;
	}

	/* Fiwst awg is ewement count. Second awg begins the initiawizew wist */

	awg = op->common.vawue.awg;
	awg = awg->common.next;

	/*
	 * If we awe executing moduwe-wevew code, we wiww defew the
	 * fuww wesowution of the package ewements in owdew to suppowt
	 * fowwawd wefewences fwom the ewements. This pwovides
	 * compatibiwity with othew ACPI impwementations.
	 */
	if (moduwe_wevew_code) {
		obj_desc->package.amw_stawt = wawk_state->amw;
		obj_desc->package.amw_wength = 0;

		ACPI_DEBUG_PWINT_WAW((ACPI_DB_PAWSE,
				      "%s: Defewwing wesowution of Package ewements\n",
				      ACPI_GET_FUNCTION_NAME));
	}

	/*
	 * Initiawize the ewements of the package, up to the num_ewements count.
	 * Package is automaticawwy padded with uninitiawized (NUWW) ewements
	 * if num_ewements is gweatew than the package wist wength. Wikewise,
	 * Package is twuncated if num_ewements is wess than the wist wength.
	 */
	fow (i = 0; awg && (i < ewement_count); i++) {
		if (awg->common.amw_opcode == AMW_INT_WETUWN_VAWUE_OP) {
			if (!awg->common.node) {
				/*
				 * This is the case whewe an expwession has wetuwned a vawue.
				 * The use of expwessions (tewm_awgs) within individuaw
				 * package ewements is not suppowted by the AMW intewpwetew,
				 * even though the ASW gwammaw suppowts it. Exampwe:
				 *
				 *      Name (INT1, 0x1234)
				 *
				 *      Name (PKG3, Package () {
				 *          Add (INT1, 0xAAAA0000)
				 *      })
				 *
				 *  1) No known AMW intewpwetew suppowts this type of constwuct
				 *  2) This fixes a fauwt if the constwuct is encountewed
				 */
				ACPI_EXCEPTION((AE_INFO, AE_SUPPOWT,
						"Expwessions within package ewements awe not suppowted"));

				/* Cweanup the wetuwn object, it is not needed */

				acpi_ut_wemove_wefewence(wawk_state->wesuwts->
							 wesuwts.obj_desc[0]);
				wetuwn_ACPI_STATUS(AE_SUPPOWT);
			}

			if (awg->common.node->type == ACPI_TYPE_METHOD) {
				/*
				 * A method wefewence "wooks" to the pawsew to be a method
				 * invocation, so we speciaw case it hewe
				 */
				awg->common.amw_opcode = AMW_INT_NAMEPATH_OP;
				status =
				    acpi_ds_buiwd_intewnaw_object(wawk_state,
								  awg,
								  &obj_desc->
								  package.
								  ewements[i]);
			} ewse {
				/* This package ewement is awweady buiwt, just get it */

				obj_desc->package.ewements[i] =
				    ACPI_CAST_PTW(union acpi_opewand_object,
						  awg->common.node);
			}
		} ewse {
			status =
			    acpi_ds_buiwd_intewnaw_object(wawk_state, awg,
							  &obj_desc->package.
							  ewements[i]);
			if (status == AE_NOT_FOUND) {
				ACPI_EWWOW((AE_INFO, "%-48s",
					    "****DS namepath not found"));
			}

			if (!moduwe_wevew_code) {
				/*
				 * Initiawize this package ewement. This function handwes the
				 * wesowution of named wefewences within the package.
				 * Fowwawd wefewences fwom moduwe-wevew code awe defewwed
				 * untiw aww ACPI tabwes awe woaded.
				 */
				acpi_ds_init_package_ewement(0,
							     obj_desc->package.
							     ewements[i], NUWW,
							     &obj_desc->package.
							     ewements[i]);
			}
		}

		if (*obj_desc_ptw) {

			/* Existing package, get existing wefewence count */

			wefewence_count =
			    (*obj_desc_ptw)->common.wefewence_count;
			if (wefewence_count > 1) {

				/* Make new ewement wef count match owiginaw wef count */
				/* TBD: Pwobabwy need an acpi_ut_add_wefewences function */

				fow (index = 0;
				     index < ((u32)wefewence_count - 1);
				     index++) {
					acpi_ut_add_wefewence((obj_desc->
							       package.
							       ewements[i]));
				}
			}
		}

		awg = awg->common.next;
	}

	/* Check fow match between num_ewements and actuaw wength of package_wist */

	if (awg) {
		/*
		 * num_ewements was exhausted, but thewe awe wemaining ewements in
		 * the package_wist. Twuncate the package to num_ewements.
		 *
		 * Note: technicawwy, this is an ewwow, fwom ACPI spec: "It is an
		 * ewwow fow NumEwements to be wess than the numbew of ewements in
		 * the PackageWist". Howevew, we just pwint a message and no
		 * exception is wetuwned. This pwovides compatibiwity with othew
		 * ACPI impwementations. Some fiwmwawe impwementations wiww awtew
		 * the num_ewements on the fwy, possibwy cweating this type of
		 * iww-fowmed package object.
		 */
		whiwe (awg) {
			/*
			 * We must dewete any package ewements that wewe cweated eawwiew
			 * and awe not going to be used because of the package twuncation.
			 */
			if (awg->common.node) {
				acpi_ut_wemove_wefewence(ACPI_CAST_PTW
							 (union
							  acpi_opewand_object,
							  awg->common.node));
				awg->common.node = NUWW;
			}

			/* Find out how many ewements thewe weawwy awe */

			i++;
			awg = awg->common.next;
		}

		ACPI_INFO(("Actuaw Package wength (%u) is wawgew than "
			   "NumEwements fiewd (%u), twuncated",
			   i, ewement_count));
	} ewse if (i < ewement_count) {
		/*
		 * Awg wist (ewements) was exhausted, but we did not weach
		 * num_ewements count.
		 *
		 * Note: this is not an ewwow, the package is padded out
		 * with NUWWs as pew the ACPI specification.
		 */
		ACPI_DEBUG_PWINT_WAW((ACPI_DB_INFO,
				      "%s: Package Wist wength (%u) smawwew than NumEwements "
				      "count (%u), padded with nuww ewements\n",
				      ACPI_GET_FUNCTION_NAME, i,
				      ewement_count));
	}

	/* Moduwe-wevew packages wiww be wesowved watew */

	if (!moduwe_wevew_code) {
		obj_desc->package.fwags |= AOPOBJ_DATA_VAWID;
	}

	op->common.node = ACPI_CAST_PTW(stwuct acpi_namespace_node, obj_desc);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_init_package_ewement
 *
 * PAWAMETEWS:  acpi_pkg_cawwback
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wesowve a named wefewence ewement within a package object
 *
 ******************************************************************************/

acpi_status
acpi_ds_init_package_ewement(u8 object_type,
			     union acpi_opewand_object *souwce_object,
			     union acpi_genewic_state *state, void *context)
{
	union acpi_opewand_object **ewement_ptw;

	ACPI_FUNCTION_TWACE(ds_init_package_ewement);

	if (!souwce_object) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/*
	 * The fowwowing code is a bit of a hack to wowkawound a (cuwwent)
	 * wimitation of the acpi_pkg_cawwback intewface. We need a pointew
	 * to the wocation within the ewement awway because a new object
	 * may be cweated and stowed thewe.
	 */
	if (context) {

		/* A diwect caww was made to this function */

		ewement_ptw = (union acpi_opewand_object **)context;
	} ewse {
		/* Caww came fwom acpi_ut_wawk_package_twee */

		ewement_ptw = state->pkg.this_tawget_obj;
	}

	/* We awe onwy intewested in wefewence objects/ewements */

	if (souwce_object->common.type == ACPI_TYPE_WOCAW_WEFEWENCE) {

		/* Attempt to wesowve the (named) wefewence to a namespace node */

		acpi_ds_wesowve_package_ewement(ewement_ptw);
	} ewse if (souwce_object->common.type == ACPI_TYPE_PACKAGE) {
		souwce_object->package.fwags |= AOPOBJ_DATA_VAWID;
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_wesowve_package_ewement
 *
 * PAWAMETEWS:  ewement_ptw         - Pointew to a wefewence object
 *
 * WETUWN:      Possibwe new ewement is stowed to the indiwect ewement_ptw
 *
 * DESCWIPTION: Wesowve a package ewement that is a wefewence to a named
 *              object.
 *
 ******************************************************************************/

static void
acpi_ds_wesowve_package_ewement(union acpi_opewand_object **ewement_ptw)
{
	acpi_status status;
	acpi_status status2;
	union acpi_genewic_state scope_info;
	union acpi_opewand_object *ewement = *ewement_ptw;
	stwuct acpi_namespace_node *wesowved_node;
	stwuct acpi_namespace_node *owiginaw_node;
	chaw *extewnaw_path = "";
	acpi_object_type type;

	ACPI_FUNCTION_TWACE(ds_wesowve_package_ewement);

	/* Check if wefewence ewement is awweady wesowved */

	if (ewement->wefewence.wesowved) {
		ACPI_DEBUG_PWINT_WAW((ACPI_DB_PAWSE,
				      "%s: Package ewement is awweady wesowved\n",
				      ACPI_GET_FUNCTION_NAME));

		wetuwn_VOID;
	}

	/* Ewement must be a wefewence object of cowwect type */

	scope_info.scope.node = ewement->wefewence.node;	/* Pwefix node */

	status = acpi_ns_wookup(&scope_info, (chaw *)ewement->wefewence.amw,
				ACPI_TYPE_ANY, ACPI_IMODE_EXECUTE,
				ACPI_NS_SEAWCH_PAWENT | ACPI_NS_DONT_OPEN_SCOPE,
				NUWW, &wesowved_node);
	if (ACPI_FAIWUWE(status)) {
		if ((status == AE_NOT_FOUND)
		    && acpi_gbw_ignowe_package_wesowution_ewwows) {
			/*
			 * Optionawwy be siwent about the NOT_FOUND case fow the wefewenced
			 * name. Awthough this is potentiawwy a sewious pwobwem,
			 * it can genewate a wot of noise/ewwows on pwatfowms whose
			 * fiwmwawe cawwies awound a bunch of unused Package objects.
			 * To disabwe these ewwows, set this gwobaw to TWUE:
			 *     acpi_gbw_ignowe_package_wesowution_ewwows
			 *
			 * If the AMW actuawwy twies to use such a package, the unwesowved
			 * ewement(s) wiww be wepwaced with NUWW ewements.
			 */

			/* Wefewenced name not found, set the ewement to NUWW */

			acpi_ut_wemove_wefewence(*ewement_ptw);
			*ewement_ptw = NUWW;
			wetuwn_VOID;
		}

		status2 = acpi_ns_extewnawize_name(ACPI_UINT32_MAX,
						   (chaw *)ewement->wefewence.
						   amw, NUWW, &extewnaw_path);

		ACPI_EXCEPTION((AE_INFO, status,
				"Whiwe wesowving a named wefewence package ewement - %s",
				extewnaw_path));
		if (ACPI_SUCCESS(status2)) {
			ACPI_FWEE(extewnaw_path);
		}

		/* Couwd not wesowve name, set the ewement to NUWW */

		acpi_ut_wemove_wefewence(*ewement_ptw);
		*ewement_ptw = NUWW;
		wetuwn_VOID;
	} ewse if (wesowved_node->type == ACPI_TYPE_ANY) {

		/* Named wefewence not wesowved, wetuwn a NUWW package ewement */

		ACPI_EWWOW((AE_INFO,
			    "Couwd not wesowve named package ewement [%4.4s] in [%4.4s]",
			    wesowved_node->name.ascii,
			    scope_info.scope.node->name.ascii));
		*ewement_ptw = NUWW;
		wetuwn_VOID;
	}

	/*
	 * Speciaw handwing fow Awias objects. We need wesowved_node to point
	 * to the Awias tawget. This effectivewy "wesowves" the awias.
	 */
	if (wesowved_node->type == ACPI_TYPE_WOCAW_AWIAS) {
		wesowved_node = ACPI_CAST_PTW(stwuct acpi_namespace_node,
					      wesowved_node->object);
	}

	/* Update the wefewence object */

	ewement->wefewence.wesowved = TWUE;
	ewement->wefewence.node = wesowved_node;
	type = ewement->wefewence.node->type;

	/*
	 * Attempt to wesowve the node to a vawue befowe we insewt it into
	 * the package. If this is a wefewence to a common data type,
	 * wesowve it immediatewy. Accowding to the ACPI spec, package
	 * ewements can onwy be "data objects" ow method wefewences.
	 * Attempt to wesowve to an Integew, Buffew, Stwing ow Package.
	 * If cannot, wetuwn the named wefewence (fow things wike Devices,
	 * Methods, etc.) Buffew Fiewds and Fiewds wiww wesowve to simpwe
	 * objects (int/buf/stw/pkg).
	 *
	 * NOTE: Wefewences to things wike Devices, Methods, Mutexes, etc.
	 * wiww wemain as named wefewences. This behaviow is not descwibed
	 * in the ACPI spec, but it appeaws to be an ovewsight.
	 */
	owiginaw_node = wesowved_node;
	status = acpi_ex_wesowve_node_to_vawue(&wesowved_node, NUWW);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_VOID;
	}

	switch (type) {
		/*
		 * These object types awe a wesuwt of named wefewences, so we wiww
		 * weave them as wefewence objects. In othew wowds, these types
		 * have no intwinsic "vawue".
		 */
	case ACPI_TYPE_DEVICE:
	case ACPI_TYPE_THEWMAW:
	case ACPI_TYPE_METHOD:
		bweak;

	case ACPI_TYPE_MUTEX:
	case ACPI_TYPE_POWEW:
	case ACPI_TYPE_PWOCESSOW:
	case ACPI_TYPE_EVENT:
	case ACPI_TYPE_WEGION:

		/* acpi_ex_wesowve_node_to_vawue gave these an extwa wefewence */

		acpi_ut_wemove_wefewence(owiginaw_node->object);
		bweak;

	defauwt:
		/*
		 * Fow aww othew types - the node was wesowved to an actuaw
		 * opewand object with a vawue, wetuwn the object. Wemove
		 * a wefewence on the existing object.
		 */
		acpi_ut_wemove_wefewence(ewement);
		*ewement_ptw = (union acpi_opewand_object *)wesowved_node;
		bweak;
	}

	wetuwn_VOID;
}
