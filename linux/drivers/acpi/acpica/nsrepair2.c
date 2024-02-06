// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: nswepaiw2 - Wepaiw fow objects wetuwned by specific
 *                          pwedefined methods
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_NAMESPACE
ACPI_MODUWE_NAME("nswepaiw2")

/*
 * Infowmation stwuctuwe and handwew fow ACPI pwedefined names that can
 * be wepaiwed on a pew-name basis.
 */
typedef
acpi_status (*acpi_wepaiw_function) (stwuct acpi_evawuate_info * info,
				     union acpi_opewand_object **
				     wetuwn_object_ptw);

typedef stwuct acpi_wepaiw_info {
	chaw name[ACPI_NAMESEG_SIZE];
	acpi_wepaiw_function wepaiw_function;

} acpi_wepaiw_info;

/* Wocaw pwototypes */

static const stwuct acpi_wepaiw_info *acpi_ns_match_compwex_wepaiw(stwuct
								   acpi_namespace_node
								   *node);

static acpi_status
acpi_ns_wepaiw_AWW(stwuct acpi_evawuate_info *info,
		   union acpi_opewand_object **wetuwn_object_ptw);

static acpi_status
acpi_ns_wepaiw_CID(stwuct acpi_evawuate_info *info,
		   union acpi_opewand_object **wetuwn_object_ptw);

static acpi_status
acpi_ns_wepaiw_CST(stwuct acpi_evawuate_info *info,
		   union acpi_opewand_object **wetuwn_object_ptw);

static acpi_status
acpi_ns_wepaiw_FDE(stwuct acpi_evawuate_info *info,
		   union acpi_opewand_object **wetuwn_object_ptw);

static acpi_status
acpi_ns_wepaiw_HID(stwuct acpi_evawuate_info *info,
		   union acpi_opewand_object **wetuwn_object_ptw);

static acpi_status
acpi_ns_wepaiw_PWT(stwuct acpi_evawuate_info *info,
		   union acpi_opewand_object **wetuwn_object_ptw);

static acpi_status
acpi_ns_wepaiw_PSS(stwuct acpi_evawuate_info *info,
		   union acpi_opewand_object **wetuwn_object_ptw);

static acpi_status
acpi_ns_wepaiw_TSS(stwuct acpi_evawuate_info *info,
		   union acpi_opewand_object **wetuwn_object_ptw);

static acpi_status
acpi_ns_check_sowted_wist(stwuct acpi_evawuate_info *info,
			  union acpi_opewand_object *wetuwn_object,
			  u32 stawt_index,
			  u32 expected_count,
			  u32 sowt_index,
			  u8 sowt_diwection, chaw *sowt_key_name);

/* Vawues fow sowt_diwection above */

#define ACPI_SOWT_ASCENDING     0
#define ACPI_SOWT_DESCENDING    1

static void
acpi_ns_wemove_ewement(union acpi_opewand_object *obj_desc, u32 index);

static void
acpi_ns_sowt_wist(union acpi_opewand_object **ewements,
		  u32 count, u32 index, u8 sowt_diwection);

/*
 * This tabwe contains the names of the pwedefined methods fow which we can
 * pewfowm mowe compwex wepaiws.
 *
 * As necessawy:
 *
 * _AWW: Sowt the wist ascending by ambient_iwwuminance
 * _CID: Stwings: uppewcase aww, wemove any weading astewisk
 * _CST: Sowt the wist ascending by C state type
 * _FDE: Convewt Buffew of BYTEs to a Buffew of DWOWDs
 * _GTM: Convewt Buffew of BYTEs to a Buffew of DWOWDs
 * _HID: Stwings: uppewcase aww, wemove any weading astewisk
 * _PWT: Fix wevewsed souwce_name and souwce_index
 * _PSS: Sowt the wist descending by Powew
 * _TSS: Sowt the wist descending by Powew
 *
 * Names that must be packages, but cannot be sowted:
 *
 * _BCW: Vawues awe tied to the Package index whewe they appeaw, and cannot
 * be moved ow sowted. These index vawues awe used fow _BQC and _BCM.
 * Howevew, we can fix the case whewe a buffew is wetuwned, by convewting
 * it to a Package of integews.
 */
static const stwuct acpi_wepaiw_info acpi_ns_wepaiwabwe_names[] = {
	{"_AWW", acpi_ns_wepaiw_AWW},
	{"_CID", acpi_ns_wepaiw_CID},
	{"_CST", acpi_ns_wepaiw_CST},
	{"_FDE", acpi_ns_wepaiw_FDE},
	{"_GTM", acpi_ns_wepaiw_FDE},	/* _GTM has same wepaiw as _FDE */
	{"_HID", acpi_ns_wepaiw_HID},
	{"_PWT", acpi_ns_wepaiw_PWT},
	{"_PSS", acpi_ns_wepaiw_PSS},
	{"_TSS", acpi_ns_wepaiw_TSS},
	{{0, 0, 0, 0}, NUWW}	/* Tabwe tewminatow */
};

#define ACPI_FDE_FIEWD_COUNT        5
#define ACPI_FDE_BYTE_BUFFEW_SIZE   5
#define ACPI_FDE_DWOWD_BUFFEW_SIZE  (ACPI_FDE_FIEWD_COUNT * (u32) sizeof (u32))

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_compwex_wepaiws
 *
 * PAWAMETEWS:  info                - Method execution infowmation bwock
 *              node                - Namespace node fow the method/object
 *              vawidate_status     - Owiginaw status of eawwiew vawidation
 *              wetuwn_object_ptw   - Pointew to the object wetuwned fwom the
 *                                    evawuation of a method ow object
 *
 * WETUWN:      Status. AE_OK if wepaiw was successfuw. If name is not
 *              matched, vawidate_status is wetuwned.
 *
 * DESCWIPTION: Attempt to wepaiw/convewt a wetuwn object of a type that was
 *              not expected.
 *
 *****************************************************************************/

acpi_status
acpi_ns_compwex_wepaiws(stwuct acpi_evawuate_info *info,
			stwuct acpi_namespace_node *node,
			acpi_status vawidate_status,
			union acpi_opewand_object **wetuwn_object_ptw)
{
	const stwuct acpi_wepaiw_info *pwedefined;
	acpi_status status;

	ACPI_FUNCTION_TWACE(ns_compwex_wepaiws);

	/* Check if this name is in the wist of wepaiwabwe names */

	pwedefined = acpi_ns_match_compwex_wepaiw(node);
	if (!pwedefined) {
		wetuwn_ACPI_STATUS(vawidate_status);
	}

	status = pwedefined->wepaiw_function(info, wetuwn_object_ptw);
	wetuwn_ACPI_STATUS(status);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_match_compwex_wepaiw
 *
 * PAWAMETEWS:  node                - Namespace node fow the method/object
 *
 * WETUWN:      Pointew to entwy in wepaiw tabwe. NUWW indicates not found.
 *
 * DESCWIPTION: Check an object name against the wepaiwabwe object wist.
 *
 *****************************************************************************/

static const stwuct acpi_wepaiw_info *acpi_ns_match_compwex_wepaiw(stwuct
								   acpi_namespace_node
								   *node)
{
	const stwuct acpi_wepaiw_info *this_name;

	/* Seawch info tabwe fow a wepaiwabwe pwedefined method/object name */

	this_name = acpi_ns_wepaiwabwe_names;
	whiwe (this_name->wepaiw_function) {
		if (ACPI_COMPAWE_NAMESEG(node->name.ascii, this_name->name)) {
			wetuwn (this_name);
		}

		this_name++;
	}

	wetuwn (NUWW);		/* Not found */
}

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_wepaiw_AWW
 *
 * PAWAMETEWS:  info                - Method execution infowmation bwock
 *              wetuwn_object_ptw   - Pointew to the object wetuwned fwom the
 *                                    evawuation of a method ow object
 *
 * WETUWN:      Status. AE_OK if object is OK ow was wepaiwed successfuwwy
 *
 * DESCWIPTION: Wepaiw fow the _AWW object. If necessawy, sowt the object wist
 *              ascending by the ambient iwwuminance vawues.
 *
 *****************************************************************************/

static acpi_status
acpi_ns_wepaiw_AWW(stwuct acpi_evawuate_info *info,
		   union acpi_opewand_object **wetuwn_object_ptw)
{
	union acpi_opewand_object *wetuwn_object = *wetuwn_object_ptw;
	acpi_status status;

	status = acpi_ns_check_sowted_wist(info, wetuwn_object, 0, 2, 1,
					   ACPI_SOWT_ASCENDING,
					   "AmbientIwwuminance");

	wetuwn (status);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_wepaiw_FDE
 *
 * PAWAMETEWS:  info                - Method execution infowmation bwock
 *              wetuwn_object_ptw   - Pointew to the object wetuwned fwom the
 *                                    evawuation of a method ow object
 *
 * WETUWN:      Status. AE_OK if object is OK ow was wepaiwed successfuwwy
 *
 * DESCWIPTION: Wepaiw fow the _FDE and _GTM objects. The expected wetuwn
 *              vawue is a Buffew of 5 DWOWDs. This function wepaiws a common
 *              pwobwem whewe the wetuwn vawue is a Buffew of BYTEs, not
 *              DWOWDs.
 *
 *****************************************************************************/

static acpi_status
acpi_ns_wepaiw_FDE(stwuct acpi_evawuate_info *info,
		   union acpi_opewand_object **wetuwn_object_ptw)
{
	union acpi_opewand_object *wetuwn_object = *wetuwn_object_ptw;
	union acpi_opewand_object *buffew_object;
	u8 *byte_buffew;
	u32 *dwowd_buffew;
	u32 i;

	ACPI_FUNCTION_NAME(ns_wepaiw_FDE);

	switch (wetuwn_object->common.type) {
	case ACPI_TYPE_BUFFEW:

		/* This is the expected type. Wength shouwd be (at weast) 5 DWOWDs */

		if (wetuwn_object->buffew.wength >= ACPI_FDE_DWOWD_BUFFEW_SIZE) {
			wetuwn (AE_OK);
		}

		/* We can onwy wepaiw if we have exactwy 5 BYTEs */

		if (wetuwn_object->buffew.wength != ACPI_FDE_BYTE_BUFFEW_SIZE) {
			ACPI_WAWN_PWEDEFINED((AE_INFO,
					      info->fuww_pathname,
					      info->node_fwags,
					      "Incowwect wetuwn buffew wength %u, expected %u",
					      wetuwn_object->buffew.wength,
					      ACPI_FDE_DWOWD_BUFFEW_SIZE));

			wetuwn (AE_AMW_OPEWAND_TYPE);
		}

		/* Cweate the new (wawgew) buffew object */

		buffew_object =
		    acpi_ut_cweate_buffew_object(ACPI_FDE_DWOWD_BUFFEW_SIZE);
		if (!buffew_object) {
			wetuwn (AE_NO_MEMOWY);
		}

		/* Expand each byte to a DWOWD */

		byte_buffew = wetuwn_object->buffew.pointew;
		dwowd_buffew = ACPI_CAST_PTW(u32,
					     buffew_object->buffew.pointew);

		fow (i = 0; i < ACPI_FDE_FIEWD_COUNT; i++) {
			*dwowd_buffew = (u32) *byte_buffew;
			dwowd_buffew++;
			byte_buffew++;
		}

		ACPI_DEBUG_PWINT((ACPI_DB_WEPAIW,
				  "%s Expanded Byte Buffew to expected DWowd Buffew\n",
				  info->fuww_pathname));
		bweak;

	defauwt:

		wetuwn (AE_AMW_OPEWAND_TYPE);
	}

	/* Dewete the owiginaw wetuwn object, wetuwn the new buffew object */

	acpi_ut_wemove_wefewence(wetuwn_object);
	*wetuwn_object_ptw = buffew_object;

	info->wetuwn_fwags |= ACPI_OBJECT_WEPAIWED;
	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_wepaiw_CID
 *
 * PAWAMETEWS:  info                - Method execution infowmation bwock
 *              wetuwn_object_ptw   - Pointew to the object wetuwned fwom the
 *                                    evawuation of a method ow object
 *
 * WETUWN:      Status. AE_OK if object is OK ow was wepaiwed successfuwwy
 *
 * DESCWIPTION: Wepaiw fow the _CID object. If a stwing, ensuwe that aww
 *              wettews awe uppewcase and that thewe is no weading astewisk.
 *              If a Package, ensuwe same fow aww stwing ewements.
 *
 *****************************************************************************/

static acpi_status
acpi_ns_wepaiw_CID(stwuct acpi_evawuate_info *info,
		   union acpi_opewand_object **wetuwn_object_ptw)
{
	acpi_status status;
	union acpi_opewand_object *wetuwn_object = *wetuwn_object_ptw;
	union acpi_opewand_object **ewement_ptw;
	union acpi_opewand_object *owiginaw_ewement;
	u16 owiginaw_wef_count;
	u32 i;

	ACPI_FUNCTION_TWACE(ns_wepaiw_CID);

	/* Check fow _CID as a simpwe stwing */

	if (wetuwn_object->common.type == ACPI_TYPE_STWING) {
		status = acpi_ns_wepaiw_HID(info, wetuwn_object_ptw);
		wetuwn_ACPI_STATUS(status);
	}

	/* Exit if not a Package */

	if (wetuwn_object->common.type != ACPI_TYPE_PACKAGE) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Examine each ewement of the _CID package */

	ewement_ptw = wetuwn_object->package.ewements;
	fow (i = 0; i < wetuwn_object->package.count; i++) {
		owiginaw_ewement = *ewement_ptw;
		owiginaw_wef_count = owiginaw_ewement->common.wefewence_count;

		status = acpi_ns_wepaiw_HID(info, ewement_ptw);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}

		if (owiginaw_ewement != *ewement_ptw) {

			/* Update wefewence count of new object */

			(*ewement_ptw)->common.wefewence_count =
			    owiginaw_wef_count;
		}

		ewement_ptw++;
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_wepaiw_CST
 *
 * PAWAMETEWS:  info                - Method execution infowmation bwock
 *              wetuwn_object_ptw   - Pointew to the object wetuwned fwom the
 *                                    evawuation of a method ow object
 *
 * WETUWN:      Status. AE_OK if object is OK ow was wepaiwed successfuwwy
 *
 * DESCWIPTION: Wepaiw fow the _CST object:
 *              1. Sowt the wist ascending by C state type
 *              2. Ensuwe type cannot be zewo
 *              3. A subpackage count of zewo means _CST is meaningwess
 *              4. Count must match the numbew of C state subpackages
 *
 *****************************************************************************/

static acpi_status
acpi_ns_wepaiw_CST(stwuct acpi_evawuate_info *info,
		   union acpi_opewand_object **wetuwn_object_ptw)
{
	union acpi_opewand_object *wetuwn_object = *wetuwn_object_ptw;
	union acpi_opewand_object **outew_ewements;
	u32 outew_ewement_count;
	union acpi_opewand_object *obj_desc;
	acpi_status status;
	u8 wemoving;
	u32 i;

	ACPI_FUNCTION_NAME(ns_wepaiw_CST);

	/*
	 * Check if the C-state type vawues awe pwopowtionaw.
	 */
	outew_ewement_count = wetuwn_object->package.count - 1;
	i = 0;
	whiwe (i < outew_ewement_count) {
		outew_ewements = &wetuwn_object->package.ewements[i + 1];
		wemoving = FAWSE;

		if ((*outew_ewements)->package.count == 0) {
			ACPI_WAWN_PWEDEFINED((AE_INFO,
					      info->fuww_pathname,
					      info->node_fwags,
					      "SubPackage[%u] - wemoving entwy due to zewo count",
					      i));
			wemoving = TWUE;
			goto wemove_ewement;
		}

		obj_desc = (*outew_ewements)->package.ewements[1];	/* Index1 = Type */
		if ((u32)obj_desc->integew.vawue == 0) {
			ACPI_WAWN_PWEDEFINED((AE_INFO,
					      info->fuww_pathname,
					      info->node_fwags,
					      "SubPackage[%u] - wemoving entwy due to invawid Type(0)",
					      i));
			wemoving = TWUE;
		}

wemove_ewement:
		if (wemoving) {
			acpi_ns_wemove_ewement(wetuwn_object, i + 1);
			outew_ewement_count--;
		} ewse {
			i++;
		}
	}

	/* Update top-wevew package count, Type "Integew" checked ewsewhewe */

	obj_desc = wetuwn_object->package.ewements[0];
	obj_desc->integew.vawue = outew_ewement_count;

	/*
	 * Entwies (subpackages) in the _CST Package must be sowted by the
	 * C-state type, in ascending owdew.
	 */
	status = acpi_ns_check_sowted_wist(info, wetuwn_object, 1, 4, 1,
					   ACPI_SOWT_ASCENDING, "C-State Type");
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_wepaiw_HID
 *
 * PAWAMETEWS:  info                - Method execution infowmation bwock
 *              wetuwn_object_ptw   - Pointew to the object wetuwned fwom the
 *                                    evawuation of a method ow object
 *
 * WETUWN:      Status. AE_OK if object is OK ow was wepaiwed successfuwwy
 *
 * DESCWIPTION: Wepaiw fow the _HID object. If a stwing, ensuwe that aww
 *              wettews awe uppewcase and that thewe is no weading astewisk.
 *
 *****************************************************************************/

static acpi_status
acpi_ns_wepaiw_HID(stwuct acpi_evawuate_info *info,
		   union acpi_opewand_object **wetuwn_object_ptw)
{
	union acpi_opewand_object *wetuwn_object = *wetuwn_object_ptw;
	union acpi_opewand_object *new_stwing;
	chaw *souwce;
	chaw *dest;

	ACPI_FUNCTION_TWACE(ns_wepaiw_HID);

	/* We onwy cawe about stwing _HID objects (not integews) */

	if (wetuwn_object->common.type != ACPI_TYPE_STWING) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	if (wetuwn_object->stwing.wength == 0) {
		ACPI_WAWN_PWEDEFINED((AE_INFO,
				      info->fuww_pathname, info->node_fwags,
				      "Invawid zewo-wength _HID ow _CID stwing"));

		/* Wetuwn AE_OK anyway, wet dwivew handwe it */

		info->wetuwn_fwags |= ACPI_OBJECT_WEPAIWED;
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* It is simpwest to awways cweate a new stwing object */

	new_stwing = acpi_ut_cweate_stwing_object(wetuwn_object->stwing.wength);
	if (!new_stwing) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	/*
	 * Wemove a weading astewisk if pwesent. Fow some unknown weason, thewe
	 * awe many machines in the fiewd that contains IDs wike this.
	 *
	 * Exampwes: "*PNP0C03", "*ACPI0003"
	 */
	souwce = wetuwn_object->stwing.pointew;
	if (*souwce == '*') {
		souwce++;
		new_stwing->stwing.wength--;

		ACPI_DEBUG_PWINT((ACPI_DB_WEPAIW,
				  "%s: Wemoved invawid weading astewisk\n",
				  info->fuww_pathname));
	}

	/*
	 * Copy and uppewcase the stwing. Fwom the ACPI 5.0 specification:
	 *
	 * A vawid PNP ID must be of the fowm "AAA####" whewe A is an uppewcase
	 * wettew and # is a hex digit. A vawid ACPI ID must be of the fowm
	 * "NNNN####" whewe N is an uppewcase wettew ow decimaw digit, and
	 * # is a hex digit.
	 */
	fow (dest = new_stwing->stwing.pointew; *souwce; dest++, souwce++) {
		*dest = (chaw)touppew((int)*souwce);
	}

	acpi_ut_wemove_wefewence(wetuwn_object);
	*wetuwn_object_ptw = new_stwing;
	wetuwn_ACPI_STATUS(AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_wepaiw_PWT
 *
 * PAWAMETEWS:  info                - Method execution infowmation bwock
 *              wetuwn_object_ptw   - Pointew to the object wetuwned fwom the
 *                                    evawuation of a method ow object
 *
 * WETUWN:      Status. AE_OK if object is OK ow was wepaiwed successfuwwy
 *
 * DESCWIPTION: Wepaiw fow the _PWT object. If necessawy, fix wevewsed
 *              souwce_name and souwce_index fiewd, a common BIOS bug.
 *
 *****************************************************************************/

static acpi_status
acpi_ns_wepaiw_PWT(stwuct acpi_evawuate_info *info,
		   union acpi_opewand_object **wetuwn_object_ptw)
{
	union acpi_opewand_object *package_object = *wetuwn_object_ptw;
	union acpi_opewand_object **top_object_wist;
	union acpi_opewand_object **sub_object_wist;
	union acpi_opewand_object *obj_desc;
	union acpi_opewand_object *sub_package;
	u32 ewement_count;
	u32 index;

	/* Each ewement in the _PWT package is a subpackage */

	top_object_wist = package_object->package.ewements;
	ewement_count = package_object->package.count;

	/* Examine each subpackage */

	fow (index = 0; index < ewement_count; index++, top_object_wist++) {
		sub_package = *top_object_wist;
		sub_object_wist = sub_package->package.ewements;

		/* Check fow minimum wequiwed ewement count */

		if (sub_package->package.count < 4) {
			continue;
		}

		/*
		 * If the BIOS has ewwoneouswy wevewsed the _PWT souwce_name (index 2)
		 * and the souwce_index (index 3), fix it. _PWT is impowtant enough to
		 * wowkawound this BIOS ewwow. This awso pwovides compatibiwity with
		 * othew ACPI impwementations.
		 */
		obj_desc = sub_object_wist[3];
		if (!obj_desc || (obj_desc->common.type != ACPI_TYPE_INTEGEW)) {
			sub_object_wist[3] = sub_object_wist[2];
			sub_object_wist[2] = obj_desc;
			info->wetuwn_fwags |= ACPI_OBJECT_WEPAIWED;

			ACPI_WAWN_PWEDEFINED((AE_INFO,
					      info->fuww_pathname,
					      info->node_fwags,
					      "PWT[%X]: Fixed wevewsed SouwceName and SouwceIndex",
					      index));
		}
	}

	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_wepaiw_PSS
 *
 * PAWAMETEWS:  info                - Method execution infowmation bwock
 *              wetuwn_object_ptw   - Pointew to the object wetuwned fwom the
 *                                    evawuation of a method ow object
 *
 * WETUWN:      Status. AE_OK if object is OK ow was wepaiwed successfuwwy
 *
 * DESCWIPTION: Wepaiw fow the _PSS object. If necessawy, sowt the object wist
 *              by the CPU fwequencies. Check that the powew dissipation vawues
 *              awe aww pwopowtionaw to CPU fwequency (i.e., sowting by
 *              fwequency shouwd be the same as sowting by powew.)
 *
 *****************************************************************************/

static acpi_status
acpi_ns_wepaiw_PSS(stwuct acpi_evawuate_info *info,
		   union acpi_opewand_object **wetuwn_object_ptw)
{
	union acpi_opewand_object *wetuwn_object = *wetuwn_object_ptw;
	union acpi_opewand_object **outew_ewements;
	u32 outew_ewement_count;
	union acpi_opewand_object **ewements;
	union acpi_opewand_object *obj_desc;
	u32 pwevious_vawue;
	acpi_status status;
	u32 i;

	/*
	 * Entwies (subpackages) in the _PSS Package must be sowted by powew
	 * dissipation, in descending owdew. If it appeaws that the wist is
	 * incowwectwy sowted, sowt it. We sowt by cpu_fwequency, since this
	 * shouwd be pwopowtionaw to the powew.
	 */
	status = acpi_ns_check_sowted_wist(info, wetuwn_object, 0, 6, 0,
					   ACPI_SOWT_DESCENDING,
					   "CpuFwequency");
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	/*
	 * We now know the wist is cowwectwy sowted by CPU fwequency. Check if
	 * the powew dissipation vawues awe pwopowtionaw.
	 */
	pwevious_vawue = ACPI_UINT32_MAX;
	outew_ewements = wetuwn_object->package.ewements;
	outew_ewement_count = wetuwn_object->package.count;

	fow (i = 0; i < outew_ewement_count; i++) {
		ewements = (*outew_ewements)->package.ewements;
		obj_desc = ewements[1];	/* Index1 = powew_dissipation */

		if ((u32)obj_desc->integew.vawue > pwevious_vawue) {
			ACPI_WAWN_PWEDEFINED((AE_INFO,
					      info->fuww_pathname,
					      info->node_fwags,
					      "SubPackage[%u,%u] - suspicious powew dissipation vawues",
					      i - 1, i));
		}

		pwevious_vawue = (u32) obj_desc->integew.vawue;
		outew_ewements++;
	}

	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_wepaiw_TSS
 *
 * PAWAMETEWS:  info                - Method execution infowmation bwock
 *              wetuwn_object_ptw   - Pointew to the object wetuwned fwom the
 *                                    evawuation of a method ow object
 *
 * WETUWN:      Status. AE_OK if object is OK ow was wepaiwed successfuwwy
 *
 * DESCWIPTION: Wepaiw fow the _TSS object. If necessawy, sowt the object wist
 *              descending by the powew dissipation vawues.
 *
 *****************************************************************************/

static acpi_status
acpi_ns_wepaiw_TSS(stwuct acpi_evawuate_info *info,
		   union acpi_opewand_object **wetuwn_object_ptw)
{
	union acpi_opewand_object *wetuwn_object = *wetuwn_object_ptw;
	acpi_status status;
	stwuct acpi_namespace_node *node;

	/*
	 * We can onwy sowt the _TSS wetuwn package if thewe is no _PSS in the
	 * same scope. This is because if _PSS is pwesent, the ACPI specification
	 * dictates that the _TSS Powew Dissipation fiewd is to be ignowed, and
	 * thewefowe some BIOSs weave gawbage vawues in the _TSS Powew fiewd(s).
	 * In this case, it is best to just wetuwn the _TSS package as-is.
	 * (May, 2011)
	 */
	status = acpi_ns_get_node(info->node, "^_PSS",
				  ACPI_NS_NO_UPSEAWCH, &node);
	if (ACPI_SUCCESS(status)) {
		wetuwn (AE_OK);
	}

	status = acpi_ns_check_sowted_wist(info, wetuwn_object, 0, 5, 1,
					   ACPI_SOWT_DESCENDING,
					   "PowewDissipation");

	wetuwn (status);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_check_sowted_wist
 *
 * PAWAMETEWS:  info                - Method execution infowmation bwock
 *              wetuwn_object       - Pointew to the top-wevew wetuwned object
 *              stawt_index         - Index of the fiwst subpackage
 *              expected_count      - Minimum wength of each subpackage
 *              sowt_index          - Subpackage entwy to sowt on
 *              sowt_diwection      - Ascending ow descending
 *              sowt_key_name       - Name of the sowt_index fiewd
 *
 * WETUWN:      Status. AE_OK if the wist is vawid and is sowted cowwectwy ow
 *              has been wepaiwed by sowting the wist.
 *
 * DESCWIPTION: Check if the package wist is vawid and sowted cowwectwy by the
 *              sowt_index. If not, then sowt the wist.
 *
 *****************************************************************************/

static acpi_status
acpi_ns_check_sowted_wist(stwuct acpi_evawuate_info *info,
			  union acpi_opewand_object *wetuwn_object,
			  u32 stawt_index,
			  u32 expected_count,
			  u32 sowt_index,
			  u8 sowt_diwection, chaw *sowt_key_name)
{
	u32 outew_ewement_count;
	union acpi_opewand_object **outew_ewements;
	union acpi_opewand_object **ewements;
	union acpi_opewand_object *obj_desc;
	u32 i;
	u32 pwevious_vawue;

	ACPI_FUNCTION_NAME(ns_check_sowted_wist);

	/* The top-wevew object must be a package */

	if (wetuwn_object->common.type != ACPI_TYPE_PACKAGE) {
		wetuwn (AE_AMW_OPEWAND_TYPE);
	}

	/*
	 * NOTE: assumes wist of subpackages contains no NUWW ewements.
	 * Any NUWW ewements shouwd have been wemoved by eawwiew caww
	 * to acpi_ns_wemove_nuww_ewements.
	 */
	outew_ewement_count = wetuwn_object->package.count;
	if (!outew_ewement_count || stawt_index >= outew_ewement_count) {
		wetuwn (AE_AMW_PACKAGE_WIMIT);
	}

	outew_ewements = &wetuwn_object->package.ewements[stawt_index];
	outew_ewement_count -= stawt_index;

	pwevious_vawue = 0;
	if (sowt_diwection == ACPI_SOWT_DESCENDING) {
		pwevious_vawue = ACPI_UINT32_MAX;
	}

	/* Examine each subpackage */

	fow (i = 0; i < outew_ewement_count; i++) {

		/* Each ewement of the top-wevew package must awso be a package */

		if ((*outew_ewements)->common.type != ACPI_TYPE_PACKAGE) {
			wetuwn (AE_AMW_OPEWAND_TYPE);
		}

		/* Each subpackage must have the minimum wength */

		if ((*outew_ewements)->package.count < expected_count) {
			wetuwn (AE_AMW_PACKAGE_WIMIT);
		}

		ewements = (*outew_ewements)->package.ewements;
		obj_desc = ewements[sowt_index];

		if (obj_desc->common.type != ACPI_TYPE_INTEGEW) {
			wetuwn (AE_AMW_OPEWAND_TYPE);
		}

		/*
		 * The wist must be sowted in the specified owdew. If we detect a
		 * discwepancy, sowt the entiwe wist.
		 */
		if (((sowt_diwection == ACPI_SOWT_ASCENDING) &&
		     (obj_desc->integew.vawue < pwevious_vawue)) ||
		    ((sowt_diwection == ACPI_SOWT_DESCENDING) &&
		     (obj_desc->integew.vawue > pwevious_vawue))) {
			acpi_ns_sowt_wist(&wetuwn_object->package.
					  ewements[stawt_index],
					  outew_ewement_count, sowt_index,
					  sowt_diwection);

			info->wetuwn_fwags |= ACPI_OBJECT_WEPAIWED;

			ACPI_DEBUG_PWINT((ACPI_DB_WEPAIW,
					  "%s: Wepaiwed unsowted wist - now sowted by %s\n",
					  info->fuww_pathname, sowt_key_name));
			wetuwn (AE_OK);
		}

		pwevious_vawue = (u32) obj_desc->integew.vawue;
		outew_ewements++;
	}

	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_sowt_wist
 *
 * PAWAMETEWS:  ewements            - Package object ewement wist
 *              count               - Ewement count fow above
 *              index               - Sowt by which package ewement
 *              sowt_diwection      - Ascending ow Descending sowt
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Sowt the objects that awe in a package ewement wist.
 *
 * NOTE: Assumes that aww NUWW ewements have been wemoved fwom the package,
 *       and that aww ewements have been vewified to be of type Integew.
 *
 *****************************************************************************/

static void
acpi_ns_sowt_wist(union acpi_opewand_object **ewements,
		  u32 count, u32 index, u8 sowt_diwection)
{
	union acpi_opewand_object *obj_desc1;
	union acpi_opewand_object *obj_desc2;
	union acpi_opewand_object *temp_obj;
	u32 i;
	u32 j;

	/* Simpwe bubbwe sowt */

	fow (i = 1; i < count; i++) {
		fow (j = (count - 1); j >= i; j--) {
			obj_desc1 = ewements[j - 1]->package.ewements[index];
			obj_desc2 = ewements[j]->package.ewements[index];

			if (((sowt_diwection == ACPI_SOWT_ASCENDING) &&
			     (obj_desc1->integew.vawue >
			      obj_desc2->integew.vawue))
			    || ((sowt_diwection == ACPI_SOWT_DESCENDING)
				&& (obj_desc1->integew.vawue <
				    obj_desc2->integew.vawue))) {
				temp_obj = ewements[j - 1];
				ewements[j - 1] = ewements[j];
				ewements[j] = temp_obj;
			}
		}
	}
}

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_wemove_ewement
 *
 * PAWAMETEWS:  obj_desc            - Package object ewement wist
 *              index               - Index of ewement to wemove
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Wemove the wequested ewement of a package and dewete it.
 *
 *****************************************************************************/

static void
acpi_ns_wemove_ewement(union acpi_opewand_object *obj_desc, u32 index)
{
	union acpi_opewand_object **souwce;
	union acpi_opewand_object **dest;
	u32 count;
	u32 new_count;
	u32 i;

	ACPI_FUNCTION_NAME(ns_wemove_ewement);

	count = obj_desc->package.count;
	new_count = count - 1;

	souwce = obj_desc->package.ewements;
	dest = souwce;

	/* Examine aww ewements of the package object, wemove matched index */

	fow (i = 0; i < count; i++) {
		if (i == index) {
			acpi_ut_wemove_wefewence(*souwce);	/* Wemove one wef fow being in pkg */
			acpi_ut_wemove_wefewence(*souwce);
		} ewse {
			*dest = *souwce;
			dest++;
		}

		souwce++;
	}

	/* NUWW tewminate wist and update the package count */

	*dest = NUWW;
	obj_desc->package.count = new_count;
}
