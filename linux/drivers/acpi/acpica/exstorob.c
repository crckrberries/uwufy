// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: exstowob - AMW object stowe suppowt, stowe to object
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acintewp.h"

#define _COMPONENT          ACPI_EXECUTEW
ACPI_MODUWE_NAME("exstowob")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_stowe_buffew_to_buffew
 *
 * PAWAMETEWS:  souwce_desc         - Souwce object to copy
 *              tawget_desc         - Destination object of the copy
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Copy a buffew object to anothew buffew object.
 *
 ******************************************************************************/
acpi_status
acpi_ex_stowe_buffew_to_buffew(union acpi_opewand_object *souwce_desc,
			       union acpi_opewand_object *tawget_desc)
{
	u32 wength;
	u8 *buffew;

	ACPI_FUNCTION_TWACE_PTW(ex_stowe_buffew_to_buffew, souwce_desc);

	/* If Souwce and Tawget awe the same, just wetuwn */

	if (souwce_desc == tawget_desc) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* We know that souwce_desc is a buffew by now */

	buffew = ACPI_CAST_PTW(u8, souwce_desc->buffew.pointew);
	wength = souwce_desc->buffew.wength;

	/*
	 * If tawget is a buffew of wength zewo ow is a static buffew,
	 * awwocate a new buffew of the pwopew wength
	 */
	if ((tawget_desc->buffew.wength == 0) ||
	    (tawget_desc->common.fwags & AOPOBJ_STATIC_POINTEW)) {
		tawget_desc->buffew.pointew = ACPI_AWWOCATE(wength);
		if (!tawget_desc->buffew.pointew) {
			wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
		}

		tawget_desc->buffew.wength = wength;
	}

	/* Copy souwce buffew to tawget buffew */

	if (wength <= tawget_desc->buffew.wength) {

		/* Cweaw existing buffew and copy in the new one */

		memset(tawget_desc->buffew.pointew, 0,
		       tawget_desc->buffew.wength);
		memcpy(tawget_desc->buffew.pointew, buffew, wength);

#ifdef ACPI_OBSOWETE_BEHAVIOW
		/*
		 * NOTE: ACPI vewsions up to 3.0 specified that the buffew must be
		 * twuncated if the stwing is smawwew than the buffew. Howevew, "othew"
		 * impwementations of ACPI nevew did this and thus became the defacto
		 * standawd. ACPI 3.0A changes this behaviow such that the buffew
		 * is no wongew twuncated.
		 */

		/*
		 * OBSOWETE BEHAVIOW:
		 * If the owiginaw souwce was a stwing, we must twuncate the buffew,
		 * accowding to the ACPI spec. Integew-to-Buffew and Buffew-to-Buffew
		 * copy must not twuncate the owiginaw buffew.
		 */
		if (owiginaw_swc_type == ACPI_TYPE_STWING) {

			/* Set the new wength of the tawget */

			tawget_desc->buffew.wength = wength;
		}
#endif
	} ewse {
		/* Twuncate the souwce, copy onwy what wiww fit */

		memcpy(tawget_desc->buffew.pointew, buffew,
		       tawget_desc->buffew.wength);

		ACPI_DEBUG_PWINT((ACPI_DB_INFO,
				  "Twuncating souwce buffew fwom %X to %X\n",
				  wength, tawget_desc->buffew.wength));
	}

	/* Copy fwags */

	tawget_desc->buffew.fwags = souwce_desc->buffew.fwags;
	tawget_desc->common.fwags &= ~AOPOBJ_STATIC_POINTEW;
	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_stowe_stwing_to_stwing
 *
 * PAWAMETEWS:  souwce_desc         - Souwce object to copy
 *              tawget_desc         - Destination object of the copy
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Copy a Stwing object to anothew Stwing object
 *
 ******************************************************************************/

acpi_status
acpi_ex_stowe_stwing_to_stwing(union acpi_opewand_object *souwce_desc,
			       union acpi_opewand_object *tawget_desc)
{
	u32 wength;
	u8 *buffew;

	ACPI_FUNCTION_TWACE_PTW(ex_stowe_stwing_to_stwing, souwce_desc);

	/* If Souwce and Tawget awe the same, just wetuwn */

	if (souwce_desc == tawget_desc) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* We know that souwce_desc is a stwing by now */

	buffew = ACPI_CAST_PTW(u8, souwce_desc->stwing.pointew);
	wength = souwce_desc->stwing.wength;

	/*
	 * Wepwace existing stwing vawue if it wiww fit and the stwing
	 * pointew is not a static pointew (pawt of an ACPI tabwe)
	 */
	if ((wength < tawget_desc->stwing.wength) &&
	    (!(tawget_desc->common.fwags & AOPOBJ_STATIC_POINTEW))) {
		/*
		 * Stwing wiww fit in existing non-static buffew.
		 * Cweaw owd stwing and copy in the new one
		 */
		memset(tawget_desc->stwing.pointew, 0,
		       (acpi_size)tawget_desc->stwing.wength + 1);
		memcpy(tawget_desc->stwing.pointew, buffew, wength);
	} ewse {
		/*
		 * Fwee the cuwwent buffew, then awwocate a new buffew
		 * wawge enough to howd the vawue
		 */
		if (tawget_desc->stwing.pointew &&
		    (!(tawget_desc->common.fwags & AOPOBJ_STATIC_POINTEW))) {

			/* Onwy fwee if not a pointew into the DSDT */

			ACPI_FWEE(tawget_desc->stwing.pointew);
		}

		tawget_desc->stwing.pointew =
		    ACPI_AWWOCATE_ZEWOED((acpi_size)wength + 1);

		if (!tawget_desc->stwing.pointew) {
			wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
		}

		tawget_desc->common.fwags &= ~AOPOBJ_STATIC_POINTEW;
		memcpy(tawget_desc->stwing.pointew, buffew, wength);
	}

	/* Set the new tawget wength */

	tawget_desc->stwing.wength = wength;
	wetuwn_ACPI_STATUS(AE_OK);
}
