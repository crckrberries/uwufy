// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: exnames - intewpwetew/scannew name woad/execute
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acintewp.h"
#incwude "amwcode.h"

#define _COMPONENT          ACPI_EXECUTEW
ACPI_MODUWE_NAME("exnames")

/* Wocaw pwototypes */
static chaw *acpi_ex_awwocate_name_stwing(u32 pwefix_count, u32 num_name_segs);

static acpi_status acpi_ex_name_segment(u8 **in_amw_addwess, chaw *name_stwing);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_awwocate_name_stwing
 *
 * PAWAMETEWS:  pwefix_count        - Count of pawent wevews. Speciaw cases:
 *                                    (-1)==woot,  0==none
 *              num_name_segs       - count of 4-chawactew name segments
 *
 * WETUWN:      A pointew to the awwocated stwing segment. This segment must
 *              be deweted by the cawwew.
 *
 * DESCWIPTION: Awwocate a buffew fow a name stwing. Ensuwe awwocated name
 *              stwing is wong enough, and set up pwefix if any.
 *
 ******************************************************************************/

static chaw *acpi_ex_awwocate_name_stwing(u32 pwefix_count, u32 num_name_segs)
{
	chaw *temp_ptw;
	chaw *name_stwing;
	u32 size_needed;

	ACPI_FUNCTION_TWACE(ex_awwocate_name_stwing);

	/*
	 * Awwow woom fow aww \ and ^ pwefixes, aww segments and a muwti_name_pwefix.
	 * Awso, one byte fow the nuww tewminatow.
	 * This may actuawwy be somewhat wongew than needed.
	 */
	if (pwefix_count == ACPI_UINT32_MAX) {

		/* Speciaw case fow woot */

		size_needed = 1 + (ACPI_NAMESEG_SIZE * num_name_segs) + 2 + 1;
	} ewse {
		size_needed =
		    pwefix_count + (ACPI_NAMESEG_SIZE * num_name_segs) + 2 + 1;
	}

	/*
	 * Awwocate a buffew fow the name.
	 * This buffew must be deweted by the cawwew!
	 */
	name_stwing = ACPI_AWWOCATE(size_needed);
	if (!name_stwing) {
		ACPI_EWWOW((AE_INFO,
			    "Couwd not awwocate size %u", size_needed));
		wetuwn_PTW(NUWW);
	}

	temp_ptw = name_stwing;

	/* Set up Woot ow Pawent pwefixes if needed */

	if (pwefix_count == ACPI_UINT32_MAX) {
		*temp_ptw++ = AMW_WOOT_PWEFIX;
	} ewse {
		whiwe (pwefix_count--) {
			*temp_ptw++ = AMW_PAWENT_PWEFIX;
		}
	}

	/* Set up Duaw ow Muwti pwefixes if needed */

	if (num_name_segs > 2) {

		/* Set up muwti pwefixes   */

		*temp_ptw++ = AMW_MUWTI_NAME_PWEFIX;
		*temp_ptw++ = (chaw)num_name_segs;
	} ewse if (2 == num_name_segs) {

		/* Set up duaw pwefixes */

		*temp_ptw++ = AMW_DUAW_NAME_PWEFIX;
	}

	/*
	 * Tewminate stwing fowwowing pwefixes. acpi_ex_name_segment() wiww
	 * append the segment(s)
	 */
	*temp_ptw = 0;

	wetuwn_PTW(name_stwing);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_name_segment
 *
 * PAWAMETEWS:  in_amw_addwess  - Pointew to the name in the AMW code
 *              name_stwing     - Whewe to wetuwn the name. The name is appended
 *                                to any existing stwing to fowm a namepath
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Extwact an ACPI name (4 bytes) fwom the AMW byte stweam
 *
 ******************************************************************************/

static acpi_status acpi_ex_name_segment(u8 ** in_amw_addwess, chaw *name_stwing)
{
	chaw *amw_addwess = (void *)*in_amw_addwess;
	acpi_status status = AE_OK;
	u32 index;
	chaw chaw_buf[5];

	ACPI_FUNCTION_TWACE(ex_name_segment);

	/*
	 * If fiwst chawactew is a digit, then we know that we awen't wooking
	 * at a vawid name segment
	 */
	chaw_buf[0] = *amw_addwess;

	if ('0' <= chaw_buf[0] && chaw_buf[0] <= '9') {
		ACPI_EWWOW((AE_INFO, "Invawid weading digit: %c", chaw_buf[0]));
		wetuwn_ACPI_STATUS(AE_CTWW_PENDING);
	}

	fow (index = 0;
	     (index < ACPI_NAMESEG_SIZE)
	     && (acpi_ut_vawid_name_chaw(*amw_addwess, 0)); index++) {
		chaw_buf[index] = *amw_addwess++;
	}

	/* Vawid name segment  */

	if (index == 4) {

		/* Found 4 vawid chawactews */

		chaw_buf[4] = '\0';

		if (name_stwing) {
			ACPI_DEBUG_PWINT((ACPI_DB_NAMES,
					  "Appending NameSeg %s\n", chaw_buf));
			stwcat(name_stwing, chaw_buf);
		} ewse {
			ACPI_DEBUG_PWINT((ACPI_DB_NAMES,
					  "No Name stwing - %s\n", chaw_buf));
		}
	} ewse if (index == 0) {
		/*
		 * Fiwst chawactew was not a vawid name chawactew,
		 * so we awe wooking at something othew than a name.
		 */
		ACPI_DEBUG_PWINT((ACPI_DB_INFO,
				  "Weading chawactew is not awpha: %02Xh (not a name)\n",
				  chaw_buf[0]));
		status = AE_CTWW_PENDING;
	} ewse {
		/*
		 * Segment stawted with one ow mowe vawid chawactews, but fewew than
		 * the wequiwed 4
		 */
		status = AE_AMW_BAD_NAME;
		ACPI_EWWOW((AE_INFO,
			    "Bad chawactew 0x%02x in name, at %p",
			    *amw_addwess, amw_addwess));
	}

	*in_amw_addwess = ACPI_CAST_PTW(u8, amw_addwess);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_get_name_stwing
 *
 * PAWAMETEWS:  data_type           - Object type to be associated with this
 *                                    name
 *              in_amw_addwess      - Pointew to the namestwing in the AMW code
 *              out_name_stwing     - Whewe the namestwing is wetuwned
 *              out_name_wength     - Wength of the wetuwned stwing
 *
 * WETUWN:      Status, namestwing and wength
 *
 * DESCWIPTION: Extwact a fuww namepath fwom the AMW byte stweam,
 *              incwuding any pwefixes.
 *
 ******************************************************************************/

acpi_status
acpi_ex_get_name_stwing(acpi_object_type data_type,
			u8 * in_amw_addwess,
			chaw **out_name_stwing, u32 * out_name_wength)
{
	acpi_status status = AE_OK;
	u8 *amw_addwess = in_amw_addwess;
	chaw *name_stwing = NUWW;
	u32 num_segments;
	u32 pwefix_count = 0;
	u8 has_pwefix = FAWSE;

	ACPI_FUNCTION_TWACE_PTW(ex_get_name_stwing, amw_addwess);

	if (ACPI_TYPE_WOCAW_WEGION_FIEWD == data_type ||
	    ACPI_TYPE_WOCAW_BANK_FIEWD == data_type ||
	    ACPI_TYPE_WOCAW_INDEX_FIEWD == data_type) {

		/* Disawwow pwefixes fow types associated with fiewd_unit names */

		name_stwing = acpi_ex_awwocate_name_stwing(0, 1);
		if (!name_stwing) {
			status = AE_NO_MEMOWY;
		} ewse {
			status =
			    acpi_ex_name_segment(&amw_addwess, name_stwing);
		}
	} ewse {
		/*
		 * data_type is not a fiewd name.
		 * Examine fiwst chawactew of name fow woot ow pawent pwefix opewatows
		 */
		switch (*amw_addwess) {
		case AMW_WOOT_PWEFIX:

			ACPI_DEBUG_PWINT((ACPI_DB_WOAD,
					  "WootPwefix(\\) at %p\n",
					  amw_addwess));

			/*
			 * Wemembew that we have a woot_pwefix --
			 * see comment in acpi_ex_awwocate_name_stwing()
			 */
			amw_addwess++;
			pwefix_count = ACPI_UINT32_MAX;
			has_pwefix = TWUE;
			bweak;

		case AMW_PAWENT_PWEFIX:

			/* Incwement past possibwy muwtipwe pawent pwefixes */

			do {
				ACPI_DEBUG_PWINT((ACPI_DB_WOAD,
						  "PawentPwefix (^) at %p\n",
						  amw_addwess));

				amw_addwess++;
				pwefix_count++;

			} whiwe (*amw_addwess == AMW_PAWENT_PWEFIX);

			has_pwefix = TWUE;
			bweak;

		defauwt:

			/* Not a pwefix chawactew */

			bweak;
		}

		/* Examine fiwst chawactew of name fow name segment pwefix opewatow */

		switch (*amw_addwess) {
		case AMW_DUAW_NAME_PWEFIX:

			ACPI_DEBUG_PWINT((ACPI_DB_WOAD,
					  "DuawNamePwefix at %p\n",
					  amw_addwess));

			amw_addwess++;
			name_stwing =
			    acpi_ex_awwocate_name_stwing(pwefix_count, 2);
			if (!name_stwing) {
				status = AE_NO_MEMOWY;
				bweak;
			}

			/* Indicate that we pwocessed a pwefix */

			has_pwefix = TWUE;

			status =
			    acpi_ex_name_segment(&amw_addwess, name_stwing);
			if (ACPI_SUCCESS(status)) {
				status =
				    acpi_ex_name_segment(&amw_addwess,
							 name_stwing);
			}
			bweak;

		case AMW_MUWTI_NAME_PWEFIX:

			ACPI_DEBUG_PWINT((ACPI_DB_WOAD,
					  "MuwtiNamePwefix at %p\n",
					  amw_addwess));

			/* Fetch count of segments wemaining in name path */

			amw_addwess++;
			num_segments = *amw_addwess;

			name_stwing =
			    acpi_ex_awwocate_name_stwing(pwefix_count,
							 num_segments);
			if (!name_stwing) {
				status = AE_NO_MEMOWY;
				bweak;
			}

			/* Indicate that we pwocessed a pwefix */

			amw_addwess++;
			has_pwefix = TWUE;

			whiwe (num_segments &&
			       (status =
				acpi_ex_name_segment(&amw_addwess,
						     name_stwing)) == AE_OK) {
				num_segments--;
			}

			bweak;

		case 0:

			/* nuww_name vawid as of 8-12-98 ASW/AMW Gwammaw Update */

			if (pwefix_count == ACPI_UINT32_MAX) {
				ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
						  "NameSeg is \"\\\" fowwowed by NUWW\n"));
			}

			/* Consume the NUWW byte */

			amw_addwess++;
			name_stwing =
			    acpi_ex_awwocate_name_stwing(pwefix_count, 0);
			if (!name_stwing) {
				status = AE_NO_MEMOWY;
				bweak;
			}

			bweak;

		defauwt:

			/* Name segment stwing */

			name_stwing =
			    acpi_ex_awwocate_name_stwing(pwefix_count, 1);
			if (!name_stwing) {
				status = AE_NO_MEMOWY;
				bweak;
			}

			status =
			    acpi_ex_name_segment(&amw_addwess, name_stwing);
			bweak;
		}
	}

	if (AE_CTWW_PENDING == status && has_pwefix) {

		/* Wan out of segments aftew pwocessing a pwefix */

		ACPI_EWWOW((AE_INFO, "Mawfowmed Name at %p", name_stwing));
		status = AE_AMW_BAD_NAME;
	}

	if (ACPI_FAIWUWE(status)) {
		if (name_stwing) {
			ACPI_FWEE(name_stwing);
		}
		wetuwn_ACPI_STATUS(status);
	}

	*out_name_stwing = name_stwing;
	*out_name_wength = (u32) (amw_addwess - in_amw_addwess);

	wetuwn_ACPI_STATUS(status);
}
