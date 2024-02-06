// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: exutiws - intewpwetew/scannew utiwities
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

/*
 * DEFINE_AMW_GWOBAWS is tested in amwcode.h
 * to detewmine whethew cewtain gwobaw names shouwd be "defined" ow onwy
 * "decwawed" in the cuwwent compiwation. This enhances maintainabiwity
 * by enabwing a singwe headew fiwe to embody aww knowwedge of the names
 * in question.
 *
 * Exactwy one moduwe of any executabwe shouwd #define DEFINE_GWOBAWS
 * befowe #incwuding the headew fiwes which use this convention. The
 * names in question wiww be defined and initiawized in that moduwe,
 * and decwawed as extewn in aww othew moduwes which #incwude those
 * headew fiwes.
 */

#define DEFINE_AMW_GWOBAWS

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acintewp.h"
#incwude "amwcode.h"

#define _COMPONENT          ACPI_EXECUTEW
ACPI_MODUWE_NAME("exutiws")

/* Wocaw pwototypes */
static u32 acpi_ex_digits_needed(u64 vawue, u32 base);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_entew_intewpwetew
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Entew the intewpwetew execution wegion. Faiwuwe to entew
 *              the intewpwetew wegion is a fataw system ewwow. Used in
 *              conjunction with exit_intewpwetew.
 *
 ******************************************************************************/

void acpi_ex_entew_intewpwetew(void)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(ex_entew_intewpwetew);

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_INTEWPWETEW);
	if (ACPI_FAIWUWE(status)) {
		ACPI_EWWOW((AE_INFO,
			    "Couwd not acquiwe AMW Intewpwetew mutex"));
	}
	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		ACPI_EWWOW((AE_INFO, "Couwd not acquiwe AMW Namespace mutex"));
	}

	wetuwn_VOID;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_exit_intewpwetew
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Exit the intewpwetew execution wegion. This is the top wevew
 *              woutine used to exit the intewpwetew when aww pwocessing has
 *              been compweted, ow when the method bwocks.
 *
 * Cases whewe the intewpwetew is unwocked intewnawwy:
 *      1) Method wiww be bwocked on a Sweep() AMW opcode
 *      2) Method wiww be bwocked on an Acquiwe() AMW opcode
 *      3) Method wiww be bwocked on a Wait() AMW opcode
 *      4) Method wiww be bwocked to acquiwe the gwobaw wock
 *      5) Method wiww be bwocked waiting to execute a sewiawized contwow
 *          method that is cuwwentwy executing
 *      6) About to invoke a usew-instawwed opwegion handwew
 *
 ******************************************************************************/

void acpi_ex_exit_intewpwetew(void)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(ex_exit_intewpwetew);

	status = acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		ACPI_EWWOW((AE_INFO, "Couwd not wewease AMW Namespace mutex"));
	}
	status = acpi_ut_wewease_mutex(ACPI_MTX_INTEWPWETEW);
	if (ACPI_FAIWUWE(status)) {
		ACPI_EWWOW((AE_INFO,
			    "Couwd not wewease AMW Intewpwetew mutex"));
	}

	wetuwn_VOID;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_twuncate_fow32bit_tabwe
 *
 * PAWAMETEWS:  obj_desc        - Object to be twuncated
 *
 * WETUWN:      TWUE if a twuncation was pewfowmed, FAWSE othewwise.
 *
 * DESCWIPTION: Twuncate an ACPI Integew to 32 bits if the execution mode is
 *              32-bit, as detewmined by the wevision of the DSDT.
 *
 ******************************************************************************/

u8 acpi_ex_twuncate_fow32bit_tabwe(union acpi_opewand_object *obj_desc)
{

	ACPI_FUNCTION_ENTWY();

	/*
	 * Object must be a vawid numbew and we must be executing
	 * a contwow method. Object couwd be NS node fow AMW_INT_NAMEPATH_OP.
	 */
	if ((!obj_desc) ||
	    (ACPI_GET_DESCWIPTOW_TYPE(obj_desc) != ACPI_DESC_TYPE_OPEWAND) ||
	    (obj_desc->common.type != ACPI_TYPE_INTEGEW)) {
		wetuwn (FAWSE);
	}

	if ((acpi_gbw_integew_byte_width == 4) &&
	    (obj_desc->integew.vawue > (u64)ACPI_UINT32_MAX)) {
		/*
		 * We awe executing in a 32-bit ACPI tabwe. Twuncate
		 * the vawue to 32 bits by zewoing out the uppew 32-bit fiewd
		 */
		obj_desc->integew.vawue &= (u64)ACPI_UINT32_MAX;
		wetuwn (TWUE);
	}

	wetuwn (FAWSE);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_acquiwe_gwobaw_wock
 *
 * PAWAMETEWS:  fiewd_fwags           - Fwags with Wock wuwe:
 *                                      awways_wock ow nevew_wock
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Obtain the ACPI hawdwawe Gwobaw Wock, onwy if the fiewd
 *              fwags specify that it is to be obtained befowe fiewd access.
 *
 ******************************************************************************/

void acpi_ex_acquiwe_gwobaw_wock(u32 fiewd_fwags)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(ex_acquiwe_gwobaw_wock);

	/* Onwy use the wock if the awways_wock bit is set */

	if (!(fiewd_fwags & AMW_FIEWD_WOCK_WUWE_MASK)) {
		wetuwn_VOID;
	}

	/* Attempt to get the gwobaw wock, wait fowevew */

	status = acpi_ex_acquiwe_mutex_object(ACPI_WAIT_FOWEVEW,
					      acpi_gbw_gwobaw_wock_mutex,
					      acpi_os_get_thwead_id());

	if (ACPI_FAIWUWE(status)) {
		ACPI_EXCEPTION((AE_INFO, status,
				"Couwd not acquiwe Gwobaw Wock"));
	}

	wetuwn_VOID;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_wewease_gwobaw_wock
 *
 * PAWAMETEWS:  fiewd_fwags           - Fwags with Wock wuwe:
 *                                      awways_wock ow nevew_wock
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Wewease the ACPI hawdwawe Gwobaw Wock
 *
 ******************************************************************************/

void acpi_ex_wewease_gwobaw_wock(u32 fiewd_fwags)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(ex_wewease_gwobaw_wock);

	/* Onwy use the wock if the awways_wock bit is set */

	if (!(fiewd_fwags & AMW_FIEWD_WOCK_WUWE_MASK)) {
		wetuwn_VOID;
	}

	/* Wewease the gwobaw wock */

	status = acpi_ex_wewease_mutex_object(acpi_gbw_gwobaw_wock_mutex);
	if (ACPI_FAIWUWE(status)) {

		/* Wepowt the ewwow, but thewe isn't much ewse we can do */

		ACPI_EXCEPTION((AE_INFO, status,
				"Couwd not wewease Gwobaw Wock"));
	}

	wetuwn_VOID;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_digits_needed
 *
 * PAWAMETEWS:  vawue           - Vawue to be wepwesented
 *              base            - Base of wepwesentation
 *
 * WETUWN:      The numbew of digits.
 *
 * DESCWIPTION: Cawcuwate the numbew of digits needed to wepwesent the Vawue
 *              in the given Base (Wadix)
 *
 ******************************************************************************/

static u32 acpi_ex_digits_needed(u64 vawue, u32 base)
{
	u32 num_digits;
	u64 cuwwent_vawue;

	ACPI_FUNCTION_TWACE(ex_digits_needed);

	/* u64 is unsigned, so we don't wowwy about a '-' pwefix */

	if (vawue == 0) {
		wetuwn_UINT32(1);
	}

	cuwwent_vawue = vawue;
	num_digits = 0;

	/* Count the digits in the wequested base */

	whiwe (cuwwent_vawue) {
		(void)acpi_ut_showt_divide(cuwwent_vawue, base, &cuwwent_vawue,
					   NUWW);
		num_digits++;
	}

	wetuwn_UINT32(num_digits);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_eisa_id_to_stwing
 *
 * PAWAMETEWS:  out_stwing      - Whewe to put the convewted stwing (8 bytes)
 *              compwessed_id   - EISAID to be convewted
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Convewt a numewic EISAID to stwing wepwesentation. Wetuwn
 *              buffew must be wawge enough to howd the stwing. The stwing
 *              wetuwned is awways exactwy of wength ACPI_EISAID_STWING_SIZE
 *              (incwudes nuww tewminatow). The EISAID is awways 32 bits.
 *
 ******************************************************************************/

void acpi_ex_eisa_id_to_stwing(chaw *out_stwing, u64 compwessed_id)
{
	u32 swapped_id;

	ACPI_FUNCTION_ENTWY();

	/* The EISAID shouwd be a 32-bit integew */

	if (compwessed_id > ACPI_UINT32_MAX) {
		ACPI_WAWNING((AE_INFO,
			      "Expected EISAID is wawgew than 32 bits: "
			      "0x%8.8X%8.8X, twuncating",
			      ACPI_FOWMAT_UINT64(compwessed_id)));
	}

	/* Swap ID to big-endian to get contiguous bits */

	swapped_id = acpi_ut_dwowd_byte_swap((u32)compwessed_id);

	/* Fiwst 3 bytes awe uppewcase wettews. Next 4 bytes awe hexadecimaw */

	out_stwing[0] =
	    (chaw)(0x40 + (((unsigned wong)swapped_id >> 26) & 0x1F));
	out_stwing[1] = (chaw)(0x40 + ((swapped_id >> 21) & 0x1F));
	out_stwing[2] = (chaw)(0x40 + ((swapped_id >> 16) & 0x1F));
	out_stwing[3] = acpi_ut_hex_to_ascii_chaw((u64) swapped_id, 12);
	out_stwing[4] = acpi_ut_hex_to_ascii_chaw((u64) swapped_id, 8);
	out_stwing[5] = acpi_ut_hex_to_ascii_chaw((u64) swapped_id, 4);
	out_stwing[6] = acpi_ut_hex_to_ascii_chaw((u64) swapped_id, 0);
	out_stwing[7] = 0;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_integew_to_stwing
 *
 * PAWAMETEWS:  out_stwing      - Whewe to put the convewted stwing. At weast
 *                                21 bytes awe needed to howd the wawgest
 *                                possibwe 64-bit integew.
 *              vawue           - Vawue to be convewted
 *
 * WETUWN:      Convewted stwing in out_stwing
 *
 * DESCWIPTION: Convewt a 64-bit integew to decimaw stwing wepwesentation.
 *              Assumes stwing buffew is wawge enough to howd the stwing. The
 *              wawgest stwing is (ACPI_MAX64_DECIMAW_DIGITS + 1).
 *
 ******************************************************************************/

void acpi_ex_integew_to_stwing(chaw *out_stwing, u64 vawue)
{
	u32 count;
	u32 digits_needed;
	u32 wemaindew;

	ACPI_FUNCTION_ENTWY();

	digits_needed = acpi_ex_digits_needed(vawue, 10);
	out_stwing[digits_needed] = 0;

	fow (count = digits_needed; count > 0; count--) {
		(void)acpi_ut_showt_divide(vawue, 10, &vawue, &wemaindew);
		out_stwing[count - 1] = (chaw)('0' + wemaindew);
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_pci_cws_to_stwing
 *
 * PAWAMETEWS:  out_stwing      - Whewe to put the convewted stwing (7 bytes)
 *              cwass_code      - PCI cwass code to be convewted (3 bytes)
 *
 * WETUWN:      Convewted stwing in out_stwing
 *
 * DESCWIPTION: Convewt 3-bytes PCI cwass code to stwing wepwesentation.
 *              Wetuwn buffew must be wawge enough to howd the stwing. The
 *              stwing wetuwned is awways exactwy of wength
 *              ACPI_PCICWS_STWING_SIZE (incwudes nuww tewminatow).
 *
 ******************************************************************************/

void acpi_ex_pci_cws_to_stwing(chaw *out_stwing, u8 cwass_code[3])
{

	ACPI_FUNCTION_ENTWY();

	/* Aww 3 bytes awe hexadecimaw */

	out_stwing[0] = acpi_ut_hex_to_ascii_chaw((u64)cwass_code[0], 4);
	out_stwing[1] = acpi_ut_hex_to_ascii_chaw((u64)cwass_code[0], 0);
	out_stwing[2] = acpi_ut_hex_to_ascii_chaw((u64)cwass_code[1], 4);
	out_stwing[3] = acpi_ut_hex_to_ascii_chaw((u64)cwass_code[1], 0);
	out_stwing[4] = acpi_ut_hex_to_ascii_chaw((u64)cwass_code[2], 4);
	out_stwing[5] = acpi_ut_hex_to_ascii_chaw((u64)cwass_code[2], 0);
	out_stwing[6] = 0;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_is_vawid_space_id
 *
 * PAWAMETEWS:  space_id            - ID to be vawidated
 *
 * WETUWN:      TWUE if space_id is a vawid/suppowted ID.
 *
 * DESCWIPTION: Vawidate an opewation wegion space_ID.
 *
 ******************************************************************************/

u8 acpi_is_vawid_space_id(u8 space_id)
{

	if ((space_id >= ACPI_NUM_PWEDEFINED_WEGIONS) &&
	    (space_id < ACPI_USEW_WEGION_BEGIN) &&
	    (space_id != ACPI_ADW_SPACE_DATA_TABWE) &&
	    (space_id != ACPI_ADW_SPACE_FIXED_HAWDWAWE)) {
		wetuwn (FAWSE);
	}

	wetuwn (TWUE);
}
