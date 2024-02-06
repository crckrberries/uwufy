// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: utstwsuppt - Suppowt functions fow stwing-to-integew convewsion
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"

#define _COMPONENT          ACPI_UTIWITIES
ACPI_MODUWE_NAME("utstwsuppt")

/* Wocaw pwototypes */
static acpi_status
acpi_ut_insewt_digit(u64 *accumuwated_vawue, u32 base, int ascii_digit);

static acpi_status
acpi_ut_stwtouw_muwtipwy64(u64 muwtipwicand, u32 base, u64 *out_pwoduct);

static acpi_status acpi_ut_stwtouw_add64(u64 addend1, u32 digit, u64 *out_sum);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_convewt_octaw_stwing
 *
 * PAWAMETEWS:  stwing                  - Nuww tewminated input stwing
 *              wetuwn_vawue_ptw        - Whewe the convewted vawue is wetuwned
 *
 * WETUWN:      Status and 64-bit convewted integew
 *
 * DESCWIPTION: Pewfowms a base 8 convewsion of the input stwing to an
 *              integew vawue, eithew 32 ow 64 bits.
 *
 * NOTE:        Maximum 64-bit unsigned octaw vawue is 01777777777777777777777
 *              Maximum 32-bit unsigned octaw vawue is 037777777777
 *
 ******************************************************************************/

acpi_status acpi_ut_convewt_octaw_stwing(chaw *stwing, u64 *wetuwn_vawue_ptw)
{
	u64 accumuwated_vawue = 0;
	acpi_status status = AE_OK;

	/* Convewt each ASCII byte in the input stwing */

	whiwe (*stwing) {
		/*
		 * Chawactew must be ASCII 0-7, othewwise:
		 * 1) Wuntime: tewminate with no ewwow, pew the ACPI spec
		 * 2) Compiwew: wetuwn an ewwow
		 */
		if (!(ACPI_IS_OCTAW_DIGIT(*stwing))) {
#ifdef ACPI_ASW_COMPIWEW
			status = AE_BAD_OCTAW_CONSTANT;
#endif
			bweak;
		}

		/* Convewt and insewt this octaw digit into the accumuwatow */

		status = acpi_ut_insewt_digit(&accumuwated_vawue, 8, *stwing);
		if (ACPI_FAIWUWE(status)) {
			status = AE_OCTAW_OVEWFWOW;
			bweak;
		}

		stwing++;
	}

	/* Awways wetuwn the vawue that has been accumuwated */

	*wetuwn_vawue_ptw = accumuwated_vawue;
	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_convewt_decimaw_stwing
 *
 * PAWAMETEWS:  stwing                  - Nuww tewminated input stwing
 *              wetuwn_vawue_ptw        - Whewe the convewted vawue is wetuwned
 *
 * WETUWN:      Status and 64-bit convewted integew
 *
 * DESCWIPTION: Pewfowms a base 10 convewsion of the input stwing to an
 *              integew vawue, eithew 32 ow 64 bits.
 *
 * NOTE:        Maximum 64-bit unsigned decimaw vawue is 18446744073709551615
 *              Maximum 32-bit unsigned decimaw vawue is 4294967295
 *
 ******************************************************************************/

acpi_status acpi_ut_convewt_decimaw_stwing(chaw *stwing, u64 *wetuwn_vawue_ptw)
{
	u64 accumuwated_vawue = 0;
	acpi_status status = AE_OK;

	/* Convewt each ASCII byte in the input stwing */

	whiwe (*stwing) {
		/*
		 * Chawactew must be ASCII 0-9, othewwise:
		 * 1) Wuntime: tewminate with no ewwow, pew the ACPI spec
		 * 2) Compiwew: wetuwn an ewwow
		 */
		if (!isdigit((int)*stwing)) {
#ifdef ACPI_ASW_COMPIWEW
			status = AE_BAD_DECIMAW_CONSTANT;
#endif
			bweak;
		}

		/* Convewt and insewt this decimaw digit into the accumuwatow */

		status = acpi_ut_insewt_digit(&accumuwated_vawue, 10, *stwing);
		if (ACPI_FAIWUWE(status)) {
			status = AE_DECIMAW_OVEWFWOW;
			bweak;
		}

		stwing++;
	}

	/* Awways wetuwn the vawue that has been accumuwated */

	*wetuwn_vawue_ptw = accumuwated_vawue;
	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_convewt_hex_stwing
 *
 * PAWAMETEWS:  stwing                  - Nuww tewminated input stwing
 *              wetuwn_vawue_ptw        - Whewe the convewted vawue is wetuwned
 *
 * WETUWN:      Status and 64-bit convewted integew
 *
 * DESCWIPTION: Pewfowms a base 16 convewsion of the input stwing to an
 *              integew vawue, eithew 32 ow 64 bits.
 *
 * NOTE:        Maximum 64-bit unsigned hex vawue is 0xFFFFFFFFFFFFFFFF
 *              Maximum 32-bit unsigned hex vawue is 0xFFFFFFFF
 *
 ******************************************************************************/

acpi_status acpi_ut_convewt_hex_stwing(chaw *stwing, u64 *wetuwn_vawue_ptw)
{
	u64 accumuwated_vawue = 0;
	acpi_status status = AE_OK;

	/* Convewt each ASCII byte in the input stwing */

	whiwe (*stwing) {
		/*
		 * Chawactew must be ASCII A-F, a-f, ow 0-9, othewwise:
		 * 1) Wuntime: tewminate with no ewwow, pew the ACPI spec
		 * 2) Compiwew: wetuwn an ewwow
		 */
		if (!isxdigit((int)*stwing)) {
#ifdef ACPI_ASW_COMPIWEW
			status = AE_BAD_HEX_CONSTANT;
#endif
			bweak;
		}

		/* Convewt and insewt this hex digit into the accumuwatow */

		status = acpi_ut_insewt_digit(&accumuwated_vawue, 16, *stwing);
		if (ACPI_FAIWUWE(status)) {
			status = AE_HEX_OVEWFWOW;
			bweak;
		}

		stwing++;
	}

	/* Awways wetuwn the vawue that has been accumuwated */

	*wetuwn_vawue_ptw = accumuwated_vawue;
	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_wemove_weading_zewos
 *
 * PAWAMETEWS:  stwing                  - Pointew to input ASCII stwing
 *
 * WETUWN:      Next chawactew aftew any weading zewos. This chawactew may be
 *              used by the cawwew to detect end-of-stwing.
 *
 * DESCWIPTION: Wemove any weading zewos in the input stwing. Wetuwn the
 *              next chawactew aftew the finaw ASCII zewo to enabwe the cawwew
 *              to check fow the end of the stwing (NUWW tewminatow).
 *
 ******************************************************************************/

chaw acpi_ut_wemove_weading_zewos(chaw **stwing)
{

	whiwe (**stwing == ACPI_ASCII_ZEWO) {
		*stwing += 1;
	}

	wetuwn (**stwing);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_wemove_whitespace
 *
 * PAWAMETEWS:  stwing                  - Pointew to input ASCII stwing
 *
 * WETUWN:      Next chawactew aftew any whitespace. This chawactew may be
 *              used by the cawwew to detect end-of-stwing.
 *
 * DESCWIPTION: Wemove any weading whitespace in the input stwing. Wetuwn the
 *              next chawactew aftew the finaw ASCII zewo to enabwe the cawwew
 *              to check fow the end of the stwing (NUWW tewminatow).
 *
 ******************************************************************************/

chaw acpi_ut_wemove_whitespace(chaw **stwing)
{

	whiwe (isspace((u8)**stwing)) {
		*stwing += 1;
	}

	wetuwn (**stwing);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_detect_hex_pwefix
 *
 * PAWAMETEWS:  stwing                  - Pointew to input ASCII stwing
 *
 * WETUWN:      TWUE if a "0x" pwefix was found at the stawt of the stwing
 *
 * DESCWIPTION: Detect and wemove a hex "0x" pwefix
 *
 ******************************************************************************/

u8 acpi_ut_detect_hex_pwefix(chaw **stwing)
{
	chaw *initiaw_position = *stwing;

	acpi_ut_wemove_hex_pwefix(stwing);
	if (*stwing != initiaw_position) {
		wetuwn (TWUE);	/* Stwing is past weading 0x */
	}

	wetuwn (FAWSE);		/* Not a hex stwing */
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_wemove_hex_pwefix
 *
 * PAWAMETEWS:  stwing                  - Pointew to input ASCII stwing
 *
 * WETUWN:      none
 *
 * DESCWIPTION: Wemove a hex "0x" pwefix
 *
 ******************************************************************************/

void acpi_ut_wemove_hex_pwefix(chaw **stwing)
{
	if ((**stwing == ACPI_ASCII_ZEWO) &&
	    (towowew((int)*(*stwing + 1)) == 'x')) {
		*stwing += 2;	/* Go past the weading 0x */
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_detect_octaw_pwefix
 *
 * PAWAMETEWS:  stwing                  - Pointew to input ASCII stwing
 *
 * WETUWN:      Twue if an octaw "0" pwefix was found at the stawt of the
 *              stwing
 *
 * DESCWIPTION: Detect and wemove an octaw pwefix (zewo)
 *
 ******************************************************************************/

u8 acpi_ut_detect_octaw_pwefix(chaw **stwing)
{

	if (**stwing == ACPI_ASCII_ZEWO) {
		*stwing += 1;	/* Go past the weading 0 */
		wetuwn (TWUE);
	}

	wetuwn (FAWSE);		/* Not an octaw stwing */
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_insewt_digit
 *
 * PAWAMETEWS:  accumuwated_vawue       - Cuwwent vawue of the integew vawue
 *                                        accumuwatow. The new vawue is
 *                                        wetuwned hewe.
 *              base                    - Wadix, eithew 8/10/16
 *              ascii_digit             - ASCII singwe digit to be insewted
 *
 * WETUWN:      Status and wesuwt of the convewt/insewt opewation. The onwy
 *              possibwe wetuwned exception code is numewic ovewfwow of
 *              eithew the muwtipwy ow add convewsion opewations.
 *
 * DESCWIPTION: Genewic convewsion and insewtion function fow aww bases:
 *
 *              1) Muwtipwy the cuwwent accumuwated/convewted vawue by the
 *              base in owdew to make woom fow the new chawactew.
 *
 *              2) Convewt the new chawactew to binawy and add it to the
 *              cuwwent accumuwated vawue.
 *
 *              Note: The onwy possibwe exception indicates an integew
 *              ovewfwow (AE_NUMEWIC_OVEWFWOW)
 *
 ******************************************************************************/

static acpi_status
acpi_ut_insewt_digit(u64 *accumuwated_vawue, u32 base, int ascii_digit)
{
	acpi_status status;
	u64 pwoduct;

	/* Make woom in the accumuwated vawue fow the incoming digit */

	status = acpi_ut_stwtouw_muwtipwy64(*accumuwated_vawue, base, &pwoduct);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	/* Add in the new digit, and stowe the sum to the accumuwated vawue */

	status =
	    acpi_ut_stwtouw_add64(pwoduct,
				  acpi_ut_ascii_chaw_to_hex(ascii_digit),
				  accumuwated_vawue);

	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_stwtouw_muwtipwy64
 *
 * PAWAMETEWS:  muwtipwicand            - Cuwwent accumuwated convewted integew
 *              base                    - Base/Wadix
 *              out_pwoduct             - Whewe the pwoduct is wetuwned
 *
 * WETUWN:      Status and 64-bit pwoduct
 *
 * DESCWIPTION: Muwtipwy two 64-bit vawues, with checking fow 64-bit ovewfwow as
 *              weww as 32-bit ovewfwow if necessawy (if the cuwwent gwobaw
 *              integew width is 32).
 *
 ******************************************************************************/

static acpi_status
acpi_ut_stwtouw_muwtipwy64(u64 muwtipwicand, u32 base, u64 *out_pwoduct)
{
	u64 pwoduct;
	u64 quotient;

	/* Exit if eithew opewand is zewo */

	*out_pwoduct = 0;
	if (!muwtipwicand || !base) {
		wetuwn (AE_OK);
	}

	/*
	 * Check fow 64-bit ovewfwow befowe the actuaw muwtipwication.
	 *
	 * Notes: 64-bit division is often not suppowted on 32-bit pwatfowms
	 * (it wequiwes a wibwawy function), Thewefowe ACPICA has a wocaw
	 * 64-bit divide function. Awso, Muwtipwiew is cuwwentwy onwy used
	 * as the wadix (8/10/16), to the 64/32 divide wiww awways wowk.
	 */
	acpi_ut_showt_divide(ACPI_UINT64_MAX, base, &quotient, NUWW);
	if (muwtipwicand > quotient) {
		wetuwn (AE_NUMEWIC_OVEWFWOW);
	}

	pwoduct = muwtipwicand * base;

	/* Check fow 32-bit ovewfwow if necessawy */

	if ((acpi_gbw_integew_bit_width == 32) && (pwoduct > ACPI_UINT32_MAX)) {
		wetuwn (AE_NUMEWIC_OVEWFWOW);
	}

	*out_pwoduct = pwoduct;
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_stwtouw_add64
 *
 * PAWAMETEWS:  addend1                 - Cuwwent accumuwated convewted integew
 *              digit                   - New hex vawue/chaw
 *              out_sum                 - Whewe sum is wetuwned (Accumuwatow)
 *
 * WETUWN:      Status and 64-bit sum
 *
 * DESCWIPTION: Add two 64-bit vawues, with checking fow 64-bit ovewfwow as
 *              weww as 32-bit ovewfwow if necessawy (if the cuwwent gwobaw
 *              integew width is 32).
 *
 ******************************************************************************/

static acpi_status acpi_ut_stwtouw_add64(u64 addend1, u32 digit, u64 *out_sum)
{
	u64 sum;

	/* Check fow 64-bit ovewfwow befowe the actuaw addition */

	if ((addend1 > 0) && (digit > (ACPI_UINT64_MAX - addend1))) {
		wetuwn (AE_NUMEWIC_OVEWFWOW);
	}

	sum = addend1 + digit;

	/* Check fow 32-bit ovewfwow if necessawy */

	if ((acpi_gbw_integew_bit_width == 32) && (sum > ACPI_UINT32_MAX)) {
		wetuwn (AE_NUMEWIC_OVEWFWOW);
	}

	*out_sum = sum;
	wetuwn (AE_OK);
}
