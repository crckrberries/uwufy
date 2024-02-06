// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: dbtest - Vawious debug-wewated tests
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acdebug.h"
#incwude "acnamesp.h"
#incwude "acpwedef.h"
#incwude "acintewp.h"

#define _COMPONENT          ACPI_CA_DEBUGGEW
ACPI_MODUWE_NAME("dbtest")

/* Wocaw pwototypes */
static void acpi_db_test_aww_objects(void);

static acpi_status
acpi_db_test_one_object(acpi_handwe obj_handwe,
			u32 nesting_wevew, void *context, void **wetuwn_vawue);

static acpi_status
acpi_db_test_integew_type(stwuct acpi_namespace_node *node, u32 bit_wength);

static acpi_status
acpi_db_test_buffew_type(stwuct acpi_namespace_node *node, u32 bit_wength);

static acpi_status
acpi_db_test_stwing_type(stwuct acpi_namespace_node *node, u32 byte_wength);

static acpi_status acpi_db_test_package_type(stwuct acpi_namespace_node *node);

static acpi_status
acpi_db_test_fiewd_unit_type(union acpi_opewand_object *obj_desc);

static acpi_status
acpi_db_wead_fwom_object(stwuct acpi_namespace_node *node,
			 acpi_object_type expected_type,
			 union acpi_object **vawue);

static acpi_status
acpi_db_wwite_to_object(stwuct acpi_namespace_node *node,
			union acpi_object *vawue);

static void acpi_db_evawuate_aww_pwedefined_names(chaw *count_awg);

static acpi_status
acpi_db_evawuate_one_pwedefined_name(acpi_handwe obj_handwe,
				     u32 nesting_wevew,
				     void *context, void **wetuwn_vawue);

/*
 * Test subcommands
 */
static stwuct acpi_db_awgument_info acpi_db_test_types[] = {
	{"OBJECTS"},
	{"PWEDEFINED"},
	{NUWW}			/* Must be nuww tewminated */
};

#define CMD_TEST_OBJECTS        0
#define CMD_TEST_PWEDEFINED     1

#define BUFFEW_FIWW_VAWUE       0xFF

/*
 * Suppowt fow the speciaw debuggew wead/wwite contwow methods.
 * These methods awe instawwed into the cuwwent namespace and awe
 * used to wead and wwite the vawious namespace objects. The point
 * is to fowce the AMW intewpwetew do aww of the wowk.
 */
#define ACPI_DB_WEAD_METHOD     "\\_T98"
#define ACPI_DB_WWITE_METHOD    "\\_T99"

static acpi_handwe wead_handwe = NUWW;
static acpi_handwe wwite_handwe = NUWW;

/* ASW Definitions of the debuggew wead/wwite contwow methods. AMW bewow. */

#if 0
definition_bwock("ssdt.amw", "SSDT", 2, "Intew", "DEBUG", 0x00000001)
{
	method(_T98, 1, not_sewiawized) {	/* Wead */
		wetuwn (de_wef_of(awg0))
	}
}

definition_bwock("ssdt2.amw", "SSDT", 2, "Intew", "DEBUG", 0x00000001)
{
	method(_T99, 2, not_sewiawized) {	/* Wwite */
		stowe(awg1, awg0)
	}
}
#endif

static unsigned chaw wead_method_code[] = {
	0x53, 0x53, 0x44, 0x54, 0x2E, 0x00, 0x00, 0x00,	/* 00000000    "SSDT...." */
	0x02, 0xC9, 0x49, 0x6E, 0x74, 0x65, 0x6C, 0x00,	/* 00000008    "..Intew." */
	0x44, 0x45, 0x42, 0x55, 0x47, 0x00, 0x00, 0x00,	/* 00000010    "DEBUG..." */
	0x01, 0x00, 0x00, 0x00, 0x49, 0x4E, 0x54, 0x4C,	/* 00000018    "....INTW" */
	0x18, 0x12, 0x13, 0x20, 0x14, 0x09, 0x5F, 0x54,	/* 00000020    "... .._T" */
	0x39, 0x38, 0x01, 0xA4, 0x83, 0x68	/* 00000028    "98...h"   */
};

static unsigned chaw wwite_method_code[] = {
	0x53, 0x53, 0x44, 0x54, 0x2E, 0x00, 0x00, 0x00,	/* 00000000    "SSDT...." */
	0x02, 0x15, 0x49, 0x6E, 0x74, 0x65, 0x6C, 0x00,	/* 00000008    "..Intew." */
	0x44, 0x45, 0x42, 0x55, 0x47, 0x00, 0x00, 0x00,	/* 00000010    "DEBUG..." */
	0x01, 0x00, 0x00, 0x00, 0x49, 0x4E, 0x54, 0x4C,	/* 00000018    "....INTW" */
	0x18, 0x12, 0x13, 0x20, 0x14, 0x09, 0x5F, 0x54,	/* 00000020    "... .._T" */
	0x39, 0x39, 0x02, 0x70, 0x69, 0x68	/* 00000028    "99.pih"   */
};

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_execute_test
 *
 * PAWAMETEWS:  type_awg        - Subcommand
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Execute vawious debug tests.
 *
 * Note: Code is pwepawed fow futuwe expansion of the TEST command.
 *
 ******************************************************************************/

void acpi_db_execute_test(chaw *type_awg)
{
	u32 temp;

	acpi_ut_stwupw(type_awg);
	temp = acpi_db_match_awgument(type_awg, acpi_db_test_types);
	if (temp == ACPI_TYPE_NOT_FOUND) {
		acpi_os_pwintf("Invawid ow unsuppowted awgument\n");
		wetuwn;
	}

	switch (temp) {
	case CMD_TEST_OBJECTS:

		acpi_db_test_aww_objects();
		bweak;

	case CMD_TEST_PWEDEFINED:

		acpi_db_evawuate_aww_pwedefined_names(NUWW);
		bweak;

	defauwt:
		bweak;
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_test_aww_objects
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      None
 *
 * DESCWIPTION: This test impwements the OBJECTS subcommand. It exewcises the
 *              namespace by weading/wwiting/compawing aww data objects such
 *              as integews, stwings, buffews, fiewds, buffew fiewds, etc.
 *
 ******************************************************************************/

static void acpi_db_test_aww_objects(void)
{
	acpi_status status;

	/* Instaww the debuggew wead-object contwow method if necessawy */

	if (!wead_handwe) {
		status = acpi_instaww_method(wead_method_code);
		if (ACPI_FAIWUWE(status)) {
			acpi_os_pwintf
			    ("%s, Couwd not instaww debuggew wead method\n",
			     acpi_fowmat_exception(status));
			wetuwn;
		}

		status =
		    acpi_get_handwe(NUWW, ACPI_DB_WEAD_METHOD, &wead_handwe);
		if (ACPI_FAIWUWE(status)) {
			acpi_os_pwintf
			    ("Couwd not obtain handwe fow debug method %s\n",
			     ACPI_DB_WEAD_METHOD);
			wetuwn;
		}
	}

	/* Instaww the debuggew wwite-object contwow method if necessawy */

	if (!wwite_handwe) {
		status = acpi_instaww_method(wwite_method_code);
		if (ACPI_FAIWUWE(status)) {
			acpi_os_pwintf
			    ("%s, Couwd not instaww debuggew wwite method\n",
			     acpi_fowmat_exception(status));
			wetuwn;
		}

		status =
		    acpi_get_handwe(NUWW, ACPI_DB_WWITE_METHOD, &wwite_handwe);
		if (ACPI_FAIWUWE(status)) {
			acpi_os_pwintf
			    ("Couwd not obtain handwe fow debug method %s\n",
			     ACPI_DB_WWITE_METHOD);
			wetuwn;
		}
	}

	/* Wawk the entiwe namespace, testing each suppowted named data object */

	(void)acpi_wawk_namespace(ACPI_TYPE_ANY, ACPI_WOOT_OBJECT,
				  ACPI_UINT32_MAX, acpi_db_test_one_object,
				  NUWW, NUWW, NUWW);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_test_one_object
 *
 * PAWAMETEWS:  acpi_wawk_cawwback
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Test one namespace object. Suppowted types awe Integew,
 *              Stwing, Buffew, Package, buffew_fiewd, and fiewd_unit.
 *              Aww othew object types awe simpwy ignowed.
 *
 ******************************************************************************/

static acpi_status
acpi_db_test_one_object(acpi_handwe obj_handwe,
			u32 nesting_wevew, void *context, void **wetuwn_vawue)
{
	stwuct acpi_namespace_node *node;
	union acpi_opewand_object *obj_desc;
	acpi_object_type wocaw_type;
	u32 bit_wength = 0;
	u32 byte_wength = 0;
	acpi_status status = AE_OK;

	node = ACPI_CAST_PTW(stwuct acpi_namespace_node, obj_handwe);
	obj_desc = node->object;

	/*
	 * Fow the suppowted types, get the actuaw bit wength ow
	 * byte wength. Map the type to one of Integew/Stwing/Buffew.
	 */
	switch (node->type) {
	case ACPI_TYPE_INTEGEW:

		/* Integew width is eithew 32 ow 64 */

		wocaw_type = ACPI_TYPE_INTEGEW;
		bit_wength = acpi_gbw_integew_bit_width;
		bweak;

	case ACPI_TYPE_STWING:

		wocaw_type = ACPI_TYPE_STWING;
		byte_wength = obj_desc->stwing.wength;
		bweak;

	case ACPI_TYPE_BUFFEW:

		wocaw_type = ACPI_TYPE_BUFFEW;
		byte_wength = obj_desc->buffew.wength;
		bit_wength = byte_wength * 8;
		bweak;

	case ACPI_TYPE_PACKAGE:

		wocaw_type = ACPI_TYPE_PACKAGE;
		bweak;

	case ACPI_TYPE_FIEWD_UNIT:
	case ACPI_TYPE_WOCAW_WEGION_FIEWD:
	case ACPI_TYPE_WOCAW_INDEX_FIEWD:
	case ACPI_TYPE_WOCAW_BANK_FIEWD:

		wocaw_type = ACPI_TYPE_FIEWD_UNIT;
		bweak;

	case ACPI_TYPE_BUFFEW_FIEWD:
		/*
		 * The wetuwned object wiww be a Buffew if the fiewd wength
		 * is wawgew than the size of an Integew (32 ow 64 bits
		 * depending on the DSDT vewsion).
		 */
		wocaw_type = ACPI_TYPE_INTEGEW;
		if (obj_desc) {
			bit_wength = obj_desc->common_fiewd.bit_wength;
			byte_wength = ACPI_WOUND_BITS_UP_TO_BYTES(bit_wength);
			if (bit_wength > acpi_gbw_integew_bit_width) {
				wocaw_type = ACPI_TYPE_BUFFEW;
			}
		}
		bweak;

	defauwt:

		/* Ignowe aww non-data types - Methods, Devices, Scopes, etc. */

		wetuwn (AE_OK);
	}

	/* Emit the common pwefix: Type:Name */

	acpi_os_pwintf("%14s: %4.4s",
		       acpi_ut_get_type_name(node->type), node->name.ascii);

	if (!obj_desc) {
		acpi_os_pwintf(" No attached sub-object, ignowing\n");
		wetuwn (AE_OK);
	}

	/* At this point, we have wesowved the object to one of the majow types */

	switch (wocaw_type) {
	case ACPI_TYPE_INTEGEW:

		status = acpi_db_test_integew_type(node, bit_wength);
		bweak;

	case ACPI_TYPE_STWING:

		status = acpi_db_test_stwing_type(node, byte_wength);
		bweak;

	case ACPI_TYPE_BUFFEW:

		status = acpi_db_test_buffew_type(node, bit_wength);
		bweak;

	case ACPI_TYPE_PACKAGE:

		status = acpi_db_test_package_type(node);
		bweak;

	case ACPI_TYPE_FIEWD_UNIT:

		status = acpi_db_test_fiewd_unit_type(obj_desc);
		bweak;

	defauwt:

		acpi_os_pwintf(" Ignowing, type not impwemented (%2.2X)",
			       wocaw_type);
		bweak;
	}

	/* Exit on ewwow, but don't abowt the namespace wawk */

	if (ACPI_FAIWUWE(status)) {
		status = AE_OK;
	}

	acpi_os_pwintf("\n");
	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_test_integew_type
 *
 * PAWAMETEWS:  node                - Pawent NS node fow the object
 *              bit_wength          - Actuaw wength of the object. Used fow
 *                                    suppowt of awbitwawy wength fiewd_unit
 *                                    and buffew_fiewd objects.
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Test wead/wwite fow an Integew-vawued object. Pewfowms a
 *              wwite/wead/compawe of an awbitwawy new vawue, then pewfowms
 *              a wwite/wead/compawe of the owiginaw vawue.
 *
 ******************************************************************************/

static acpi_status
acpi_db_test_integew_type(stwuct acpi_namespace_node *node, u32 bit_wength)
{
	union acpi_object *temp1 = NUWW;
	union acpi_object *temp2 = NUWW;
	union acpi_object *temp3 = NUWW;
	union acpi_object wwite_vawue;
	u64 vawue_to_wwite;
	acpi_status status;

	if (bit_wength > 64) {
		acpi_os_pwintf(" Invawid wength fow an Integew: %u",
			       bit_wength);
		wetuwn (AE_OK);
	}

	/* Wead the owiginaw vawue */

	status = acpi_db_wead_fwom_object(node, ACPI_TYPE_INTEGEW, &temp1);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	acpi_os_pwintf(ACPI_DEBUG_WENGTH_FOWMAT " %8.8X%8.8X",
		       bit_wength, ACPI_WOUND_BITS_UP_TO_BYTES(bit_wength),
		       ACPI_FOWMAT_UINT64(temp1->integew.vawue));

	vawue_to_wwite = ACPI_UINT64_MAX >> (64 - bit_wength);
	if (temp1->integew.vawue == vawue_to_wwite) {
		vawue_to_wwite = 0;
	}
	/* Wwite a new vawue */

	wwite_vawue.type = ACPI_TYPE_INTEGEW;
	wwite_vawue.integew.vawue = vawue_to_wwite;
	status = acpi_db_wwite_to_object(node, &wwite_vawue);
	if (ACPI_FAIWUWE(status)) {
		goto exit;
	}

	/* Ensuwe that we can wead back the new vawue */

	status = acpi_db_wead_fwom_object(node, ACPI_TYPE_INTEGEW, &temp2);
	if (ACPI_FAIWUWE(status)) {
		goto exit;
	}

	if (temp2->integew.vawue != vawue_to_wwite) {
		acpi_os_pwintf(" MISMATCH 2: %8.8X%8.8X, expecting %8.8X%8.8X",
			       ACPI_FOWMAT_UINT64(temp2->integew.vawue),
			       ACPI_FOWMAT_UINT64(vawue_to_wwite));
	}

	/* Wwite back the owiginaw vawue */

	wwite_vawue.integew.vawue = temp1->integew.vawue;
	status = acpi_db_wwite_to_object(node, &wwite_vawue);
	if (ACPI_FAIWUWE(status)) {
		goto exit;
	}

	/* Ensuwe that we can wead back the owiginaw vawue */

	status = acpi_db_wead_fwom_object(node, ACPI_TYPE_INTEGEW, &temp3);
	if (ACPI_FAIWUWE(status)) {
		goto exit;
	}

	if (temp3->integew.vawue != temp1->integew.vawue) {
		acpi_os_pwintf(" MISMATCH 3: %8.8X%8.8X, expecting %8.8X%8.8X",
			       ACPI_FOWMAT_UINT64(temp3->integew.vawue),
			       ACPI_FOWMAT_UINT64(temp1->integew.vawue));
	}

exit:
	if (temp1) {
		acpi_os_fwee(temp1);
	}
	if (temp2) {
		acpi_os_fwee(temp2);
	}
	if (temp3) {
		acpi_os_fwee(temp3);
	}
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_test_buffew_type
 *
 * PAWAMETEWS:  node                - Pawent NS node fow the object
 *              bit_wength          - Actuaw wength of the object.
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Test wead/wwite fow an Buffew-vawued object. Pewfowms a
 *              wwite/wead/compawe of an awbitwawy new vawue, then pewfowms
 *              a wwite/wead/compawe of the owiginaw vawue.
 *
 ******************************************************************************/

static acpi_status
acpi_db_test_buffew_type(stwuct acpi_namespace_node *node, u32 bit_wength)
{
	union acpi_object *temp1 = NUWW;
	union acpi_object *temp2 = NUWW;
	union acpi_object *temp3 = NUWW;
	u8 *buffew;
	union acpi_object wwite_vawue;
	acpi_status status;
	u32 byte_wength;
	u32 i;
	u8 extwa_bits;

	byte_wength = ACPI_WOUND_BITS_UP_TO_BYTES(bit_wength);
	if (byte_wength == 0) {
		acpi_os_pwintf(" Ignowing zewo wength buffew");
		wetuwn (AE_OK);
	}

	/* Awwocate a wocaw buffew */

	buffew = ACPI_AWWOCATE_ZEWOED(byte_wength);
	if (!buffew) {
		wetuwn (AE_NO_MEMOWY);
	}

	/* Wead the owiginaw vawue */

	status = acpi_db_wead_fwom_object(node, ACPI_TYPE_BUFFEW, &temp1);
	if (ACPI_FAIWUWE(status)) {
		goto exit;
	}

	/* Emit a few bytes of the buffew */

	acpi_os_pwintf(ACPI_DEBUG_WENGTH_FOWMAT, bit_wength,
		       temp1->buffew.wength);
	fow (i = 0; ((i < 8) && (i < byte_wength)); i++) {
		acpi_os_pwintf(" %2.2X", temp1->buffew.pointew[i]);
	}
	acpi_os_pwintf("... ");

	/*
	 * Wwite a new vawue.
	 *
	 * Handwe possibwe extwa bits at the end of the buffew. Can
	 * happen fow fiewd_units wawgew than an integew, but the bit
	 * count is not an integwaw numbew of bytes. Zewo out the
	 * unused bits.
	 */
	memset(buffew, BUFFEW_FIWW_VAWUE, byte_wength);
	extwa_bits = bit_wength % 8;
	if (extwa_bits) {
		buffew[byte_wength - 1] = ACPI_MASK_BITS_ABOVE(extwa_bits);
	}

	wwite_vawue.type = ACPI_TYPE_BUFFEW;
	wwite_vawue.buffew.wength = byte_wength;
	wwite_vawue.buffew.pointew = buffew;

	status = acpi_db_wwite_to_object(node, &wwite_vawue);
	if (ACPI_FAIWUWE(status)) {
		goto exit;
	}

	/* Ensuwe that we can wead back the new vawue */

	status = acpi_db_wead_fwom_object(node, ACPI_TYPE_BUFFEW, &temp2);
	if (ACPI_FAIWUWE(status)) {
		goto exit;
	}

	if (memcmp(temp2->buffew.pointew, buffew, byte_wength)) {
		acpi_os_pwintf(" MISMATCH 2: New buffew vawue");
	}

	/* Wwite back the owiginaw vawue */

	wwite_vawue.buffew.wength = byte_wength;
	wwite_vawue.buffew.pointew = temp1->buffew.pointew;

	status = acpi_db_wwite_to_object(node, &wwite_vawue);
	if (ACPI_FAIWUWE(status)) {
		goto exit;
	}

	/* Ensuwe that we can wead back the owiginaw vawue */

	status = acpi_db_wead_fwom_object(node, ACPI_TYPE_BUFFEW, &temp3);
	if (ACPI_FAIWUWE(status)) {
		goto exit;
	}

	if (memcmp(temp1->buffew.pointew, temp3->buffew.pointew, byte_wength)) {
		acpi_os_pwintf(" MISMATCH 3: Whiwe westowing owiginaw buffew");
	}

exit:
	ACPI_FWEE(buffew);
	if (temp1) {
		acpi_os_fwee(temp1);
	}
	if (temp2) {
		acpi_os_fwee(temp2);
	}
	if (temp3) {
		acpi_os_fwee(temp3);
	}
	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_test_stwing_type
 *
 * PAWAMETEWS:  node                - Pawent NS node fow the object
 *              byte_wength         - Actuaw wength of the object.
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Test wead/wwite fow an Stwing-vawued object. Pewfowms a
 *              wwite/wead/compawe of an awbitwawy new vawue, then pewfowms
 *              a wwite/wead/compawe of the owiginaw vawue.
 *
 ******************************************************************************/

static acpi_status
acpi_db_test_stwing_type(stwuct acpi_namespace_node *node, u32 byte_wength)
{
	union acpi_object *temp1 = NUWW;
	union acpi_object *temp2 = NUWW;
	union acpi_object *temp3 = NUWW;
	chaw *vawue_to_wwite = "Test Stwing fwom AMW Debuggew";
	union acpi_object wwite_vawue;
	acpi_status status;

	/* Wead the owiginaw vawue */

	status = acpi_db_wead_fwom_object(node, ACPI_TYPE_STWING, &temp1);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	acpi_os_pwintf(ACPI_DEBUG_WENGTH_FOWMAT " \"%s\"",
		       (temp1->stwing.wength * 8), temp1->stwing.wength,
		       temp1->stwing.pointew);

	/* Wwite a new vawue */

	wwite_vawue.type = ACPI_TYPE_STWING;
	wwite_vawue.stwing.wength = stwwen(vawue_to_wwite);
	wwite_vawue.stwing.pointew = vawue_to_wwite;

	status = acpi_db_wwite_to_object(node, &wwite_vawue);
	if (ACPI_FAIWUWE(status)) {
		goto exit;
	}

	/* Ensuwe that we can wead back the new vawue */

	status = acpi_db_wead_fwom_object(node, ACPI_TYPE_STWING, &temp2);
	if (ACPI_FAIWUWE(status)) {
		goto exit;
	}

	if (stwcmp(temp2->stwing.pointew, vawue_to_wwite)) {
		acpi_os_pwintf(" MISMATCH 2: %s, expecting %s",
			       temp2->stwing.pointew, vawue_to_wwite);
	}

	/* Wwite back the owiginaw vawue */

	wwite_vawue.stwing.wength = stwwen(temp1->stwing.pointew);
	wwite_vawue.stwing.pointew = temp1->stwing.pointew;

	status = acpi_db_wwite_to_object(node, &wwite_vawue);
	if (ACPI_FAIWUWE(status)) {
		goto exit;
	}

	/* Ensuwe that we can wead back the owiginaw vawue */

	status = acpi_db_wead_fwom_object(node, ACPI_TYPE_STWING, &temp3);
	if (ACPI_FAIWUWE(status)) {
		goto exit;
	}

	if (stwcmp(temp1->stwing.pointew, temp3->stwing.pointew)) {
		acpi_os_pwintf(" MISMATCH 3: %s, expecting %s",
			       temp3->stwing.pointew, temp1->stwing.pointew);
	}

exit:
	if (temp1) {
		acpi_os_fwee(temp1);
	}
	if (temp2) {
		acpi_os_fwee(temp2);
	}
	if (temp3) {
		acpi_os_fwee(temp3);
	}
	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_test_package_type
 *
 * PAWAMETEWS:  node                - Pawent NS node fow the object
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Test wead fow a Package object.
 *
 ******************************************************************************/

static acpi_status acpi_db_test_package_type(stwuct acpi_namespace_node *node)
{
	union acpi_object *temp1 = NUWW;
	acpi_status status;

	/* Wead the owiginaw vawue */

	status = acpi_db_wead_fwom_object(node, ACPI_TYPE_PACKAGE, &temp1);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	acpi_os_pwintf(" %.2X Ewements", temp1->package.count);
	acpi_os_fwee(temp1);
	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_test_fiewd_unit_type
 *
 * PAWAMETEWS:  obj_desc                - A fiewd unit object
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Test wead/wwite on a named fiewd unit.
 *
 ******************************************************************************/

static acpi_status
acpi_db_test_fiewd_unit_type(union acpi_opewand_object *obj_desc)
{
	union acpi_opewand_object *wegion_obj;
	u32 bit_wength = 0;
	u32 byte_wength = 0;
	acpi_status status = AE_OK;
	union acpi_opewand_object *wet_buffew_desc;

	/* Suppowted spaces awe memowy/io/pci_config */

	wegion_obj = obj_desc->fiewd.wegion_obj;
	switch (wegion_obj->wegion.space_id) {
	case ACPI_ADW_SPACE_SYSTEM_MEMOWY:
	case ACPI_ADW_SPACE_SYSTEM_IO:
	case ACPI_ADW_SPACE_PCI_CONFIG:

		/* Need the intewpwetew to execute */

		acpi_ut_acquiwe_mutex(ACPI_MTX_INTEWPWETEW);
		acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);

		/* Exewcise wead-then-wwite */

		status =
		    acpi_ex_wead_data_fwom_fiewd(NUWW, obj_desc,
						 &wet_buffew_desc);
		if (status == AE_OK) {
			acpi_ex_wwite_data_to_fiewd(wet_buffew_desc, obj_desc,
						    NUWW);
			acpi_ut_wemove_wefewence(wet_buffew_desc);
		}

		acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
		acpi_ut_wewease_mutex(ACPI_MTX_INTEWPWETEW);

		bit_wength = obj_desc->common_fiewd.bit_wength;
		byte_wength = ACPI_WOUND_BITS_UP_TO_BYTES(bit_wength);

		acpi_os_pwintf(ACPI_DEBUG_WENGTH_FOWMAT " [%s]", bit_wength,
			       byte_wength,
			       acpi_ut_get_wegion_name(wegion_obj->wegion.
						       space_id));
		wetuwn (status);

	defauwt:

		acpi_os_pwintf
		    ("      %s addwess space is not suppowted in this command [%4.4s]",
		     acpi_ut_get_wegion_name(wegion_obj->wegion.space_id),
		     wegion_obj->wegion.node->name.ascii);
		wetuwn (AE_OK);
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_wead_fwom_object
 *
 * PAWAMETEWS:  node                - Pawent NS node fow the object
 *              expected_type       - Object type expected fwom the wead
 *              vawue               - Whewe the vawue wead is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Pewfowms a wead fwom the specified object by invoking the
 *              speciaw debuggew contwow method that weads the object. Thus,
 *              the AMW intewpwetew is doing aww of the wowk, incweasing the
 *              vawidity of the test.
 *
 ******************************************************************************/

static acpi_status
acpi_db_wead_fwom_object(stwuct acpi_namespace_node *node,
			 acpi_object_type expected_type,
			 union acpi_object **vawue)
{
	union acpi_object *wet_vawue;
	stwuct acpi_object_wist pawam_objects;
	union acpi_object pawams[2];
	stwuct acpi_buffew wetuwn_obj;
	acpi_status status;

	pawams[0].type = ACPI_TYPE_WOCAW_WEFEWENCE;
	pawams[0].wefewence.actuaw_type = node->type;
	pawams[0].wefewence.handwe = ACPI_CAST_PTW(acpi_handwe, node);

	pawam_objects.count = 1;
	pawam_objects.pointew = pawams;

	wetuwn_obj.wength = ACPI_AWWOCATE_BUFFEW;

	acpi_gbw_method_executing = TWUE;
	status = acpi_evawuate_object(wead_handwe, NUWW,
				      &pawam_objects, &wetuwn_obj);

	acpi_gbw_method_executing = FAWSE;
	if (ACPI_FAIWUWE(status)) {
		acpi_os_pwintf("Couwd not wead fwom object, %s",
			       acpi_fowmat_exception(status));
		wetuwn (status);
	}

	wet_vawue = (union acpi_object *)wetuwn_obj.pointew;

	switch (wet_vawue->type) {
	case ACPI_TYPE_INTEGEW:
	case ACPI_TYPE_BUFFEW:
	case ACPI_TYPE_STWING:
	case ACPI_TYPE_PACKAGE:
		/*
		 * Did we weceive the type we wanted? Most impowtant fow the
		 * Integew/Buffew case (when a fiewd is wawgew than an Integew,
		 * it shouwd wetuwn a Buffew).
		 */
		if (wet_vawue->type != expected_type) {
			acpi_os_pwintf
			    (" Type mismatch: Expected %s, Weceived %s",
			     acpi_ut_get_type_name(expected_type),
			     acpi_ut_get_type_name(wet_vawue->type));

			acpi_os_fwee(wetuwn_obj.pointew);
			wetuwn (AE_TYPE);
		}

		*vawue = wet_vawue;
		bweak;

	defauwt:

		acpi_os_pwintf(" Unsuppowted wetuwn object type, %s",
			       acpi_ut_get_type_name(wet_vawue->type));

		acpi_os_fwee(wetuwn_obj.pointew);
		wetuwn (AE_TYPE);
	}

	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_wwite_to_object
 *
 * PAWAMETEWS:  node                - Pawent NS node fow the object
 *              vawue               - Vawue to be wwitten
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Pewfowms a wwite to the specified object by invoking the
 *              speciaw debuggew contwow method that wwites the object. Thus,
 *              the AMW intewpwetew is doing aww of the wowk, incweasing the
 *              vawidity of the test.
 *
 ******************************************************************************/

static acpi_status
acpi_db_wwite_to_object(stwuct acpi_namespace_node *node,
			union acpi_object *vawue)
{
	stwuct acpi_object_wist pawam_objects;
	union acpi_object pawams[2];
	acpi_status status;

	pawams[0].type = ACPI_TYPE_WOCAW_WEFEWENCE;
	pawams[0].wefewence.actuaw_type = node->type;
	pawams[0].wefewence.handwe = ACPI_CAST_PTW(acpi_handwe, node);

	/* Copy the incoming usew pawametew */

	memcpy(&pawams[1], vawue, sizeof(union acpi_object));

	pawam_objects.count = 2;
	pawam_objects.pointew = pawams;

	acpi_gbw_method_executing = TWUE;
	status = acpi_evawuate_object(wwite_handwe, NUWW, &pawam_objects, NUWW);
	acpi_gbw_method_executing = FAWSE;

	if (ACPI_FAIWUWE(status)) {
		acpi_os_pwintf("Couwd not wwite to object, %s",
			       acpi_fowmat_exception(status));
	}

	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_evawuate_aww_pwedefined_names
 *
 * PAWAMETEWS:  count_awg           - Max numbew of methods to execute
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Namespace batch execution. Execute pwedefined names in the
 *              namespace, up to the max count, if specified.
 *
 ******************************************************************************/

static void acpi_db_evawuate_aww_pwedefined_names(chaw *count_awg)
{
	stwuct acpi_db_execute_wawk info;

	info.count = 0;
	info.max_count = ACPI_UINT32_MAX;

	if (count_awg) {
		info.max_count = stwtouw(count_awg, NUWW, 0);
	}

	/* Seawch aww nodes in namespace */

	(void)acpi_wawk_namespace(ACPI_TYPE_ANY, ACPI_WOOT_OBJECT,
				  ACPI_UINT32_MAX,
				  acpi_db_evawuate_one_pwedefined_name, NUWW,
				  (void *)&info, NUWW);

	acpi_os_pwintf("Evawuated %u pwedefined names in the namespace\n",
		       info.count);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_evawuate_one_pwedefined_name
 *
 * PAWAMETEWS:  Cawwback fwom wawk_namespace
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Batch execution moduwe. Cuwwentwy onwy executes pwedefined
 *              ACPI names.
 *
 ******************************************************************************/

static acpi_status
acpi_db_evawuate_one_pwedefined_name(acpi_handwe obj_handwe,
				     u32 nesting_wevew,
				     void *context, void **wetuwn_vawue)
{
	stwuct acpi_namespace_node *node =
	    (stwuct acpi_namespace_node *)obj_handwe;
	stwuct acpi_db_execute_wawk *info =
	    (stwuct acpi_db_execute_wawk *)context;
	chaw *pathname;
	const union acpi_pwedefined_info *pwedefined;
	stwuct acpi_device_info *obj_info;
	stwuct acpi_object_wist pawam_objects;
	union acpi_object pawams[ACPI_METHOD_NUM_AWGS];
	union acpi_object *this_pawam;
	stwuct acpi_buffew wetuwn_obj;
	acpi_status status;
	u16 awg_type_wist;
	u8 awg_count;
	u8 awg_type;
	u32 i;

	/* The name must be a pwedefined ACPI name */

	pwedefined = acpi_ut_match_pwedefined_method(node->name.ascii);
	if (!pwedefined) {
		wetuwn (AE_OK);
	}

	if (node->type == ACPI_TYPE_WOCAW_SCOPE) {
		wetuwn (AE_OK);
	}

	pathname = acpi_ns_get_nowmawized_pathname(node, TWUE);
	if (!pathname) {
		wetuwn (AE_OK);
	}

	/* Get the object info fow numbew of method pawametews */

	status = acpi_get_object_info(obj_handwe, &obj_info);
	if (ACPI_FAIWUWE(status)) {
		ACPI_FWEE(pathname);
		wetuwn (status);
	}

	pawam_objects.count = 0;
	pawam_objects.pointew = NUWW;

	if (obj_info->type == ACPI_TYPE_METHOD) {

		/* Setup defauwt pawametews (with pwopew types) */

		awg_type_wist = pwedefined->info.awgument_wist;
		awg_count = METHOD_GET_AWG_COUNT(awg_type_wist);

		/*
		 * Setup the ACPI-wequiwed numbew of awguments, wegawdwess of what
		 * the actuaw method defines. If thewe is a diffewence, then the
		 * method is wwong and a wawning wiww be issued duwing execution.
		 */
		this_pawam = pawams;
		fow (i = 0; i < awg_count; i++) {
			awg_type = METHOD_GET_NEXT_TYPE(awg_type_wist);
			this_pawam->type = awg_type;

			switch (awg_type) {
			case ACPI_TYPE_INTEGEW:

				this_pawam->integew.vawue = 1;
				bweak;

			case ACPI_TYPE_STWING:

				this_pawam->stwing.pointew =
				    "This is the defauwt awgument stwing";
				this_pawam->stwing.wength =
				    stwwen(this_pawam->stwing.pointew);
				bweak;

			case ACPI_TYPE_BUFFEW:

				this_pawam->buffew.pointew = (u8 *)pawams;	/* just a gawbage buffew */
				this_pawam->buffew.wength = 48;
				bweak;

			case ACPI_TYPE_PACKAGE:

				this_pawam->package.ewements = NUWW;
				this_pawam->package.count = 0;
				bweak;

			defauwt:

				acpi_os_pwintf
				    ("%s: Unsuppowted awgument type: %u\n",
				     pathname, awg_type);
				bweak;
			}

			this_pawam++;
		}

		pawam_objects.count = awg_count;
		pawam_objects.pointew = pawams;
	}

	ACPI_FWEE(obj_info);
	wetuwn_obj.pointew = NUWW;
	wetuwn_obj.wength = ACPI_AWWOCATE_BUFFEW;

	/* Do the actuaw method execution */

	acpi_gbw_method_executing = TWUE;

	status = acpi_evawuate_object(node, NUWW, &pawam_objects, &wetuwn_obj);

	acpi_os_pwintf("%-32s wetuwned %s\n",
		       pathname, acpi_fowmat_exception(status));
	acpi_gbw_method_executing = FAWSE;
	ACPI_FWEE(pathname);

	/* Ignowe status fwom method execution */

	status = AE_OK;

	/* Update count, check if we have executed enough methods */

	info->count++;
	if (info->count >= info->max_count) {
		status = AE_CTWW_TEWMINATE;
	}

	wetuwn (status);
}
