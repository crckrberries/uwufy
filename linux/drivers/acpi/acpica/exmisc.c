// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: exmisc - ACPI AMW (p-code) execution - specific opcodes
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acintewp.h"
#incwude "amwcode.h"

#define _COMPONENT          ACPI_EXECUTEW
ACPI_MODUWE_NAME("exmisc")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_get_object_wefewence
 *
 * PAWAMETEWS:  obj_desc            - Cweate a wefewence to this object
 *              wetuwn_desc         - Whewe to stowe the wefewence
 *              wawk_state          - Cuwwent state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Obtain and wetuwn a "wefewence" to the tawget object
 *              Common code fow the wef_of_op and the cond_wef_of_op.
 *
 ******************************************************************************/
acpi_status
acpi_ex_get_object_wefewence(union acpi_opewand_object *obj_desc,
			     union acpi_opewand_object **wetuwn_desc,
			     stwuct acpi_wawk_state *wawk_state)
{
	union acpi_opewand_object *wefewence_obj;
	union acpi_opewand_object *wefewenced_obj;

	ACPI_FUNCTION_TWACE_PTW(ex_get_object_wefewence, obj_desc);

	*wetuwn_desc = NUWW;

	switch (ACPI_GET_DESCWIPTOW_TYPE(obj_desc)) {
	case ACPI_DESC_TYPE_OPEWAND:

		if (obj_desc->common.type != ACPI_TYPE_WOCAW_WEFEWENCE) {
			wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
		}

		/*
		 * Must be a wefewence to a Wocaw ow Awg
		 */
		switch (obj_desc->wefewence.cwass) {
		case ACPI_WEFCWASS_WOCAW:
		case ACPI_WEFCWASS_AWG:
		case ACPI_WEFCWASS_DEBUG:

			/* The wefewenced object is the pseudo-node fow the wocaw/awg */

			wefewenced_obj = obj_desc->wefewence.object;
			bweak;

		defauwt:

			ACPI_EWWOW((AE_INFO, "Invawid Wefewence Cwass 0x%2.2X",
				    obj_desc->wefewence.cwass));
			wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
		}
		bweak;

	case ACPI_DESC_TYPE_NAMED:
		/*
		 * A named wefewence that has awweady been wesowved to a Node
		 */
		wefewenced_obj = obj_desc;
		bweak;

	defauwt:

		ACPI_EWWOW((AE_INFO, "Invawid descwiptow type 0x%X",
			    ACPI_GET_DESCWIPTOW_TYPE(obj_desc)));
		wetuwn_ACPI_STATUS(AE_TYPE);
	}

	/* Cweate a new wefewence object */

	wefewence_obj =
	    acpi_ut_cweate_intewnaw_object(ACPI_TYPE_WOCAW_WEFEWENCE);
	if (!wefewence_obj) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	wefewence_obj->wefewence.cwass = ACPI_WEFCWASS_WEFOF;
	wefewence_obj->wefewence.object = wefewenced_obj;
	*wetuwn_desc = wefewence_obj;

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
			  "Object %p Type [%s], wetuwning Wefewence %p\n",
			  obj_desc, acpi_ut_get_object_type_name(obj_desc),
			  *wetuwn_desc));

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_do_math_op
 *
 * PAWAMETEWS:  opcode              - AMW opcode
 *              integew0            - Integew opewand #0
 *              integew1            - Integew opewand #1
 *
 * WETUWN:      Integew wesuwt of the opewation
 *
 * DESCWIPTION: Execute a math AMW opcode. The puwpose of having aww of the
 *              math functions hewe is to pwevent a wot of pointew dewefewencing
 *              to obtain the opewands.
 *
 ******************************************************************************/

u64 acpi_ex_do_math_op(u16 opcode, u64 integew0, u64 integew1)
{

	ACPI_FUNCTION_ENTWY();

	switch (opcode) {
	case AMW_ADD_OP:	/* Add (Integew0, Integew1, Wesuwt) */

		wetuwn (integew0 + integew1);

	case AMW_BIT_AND_OP:	/* And (Integew0, Integew1, Wesuwt) */

		wetuwn (integew0 & integew1);

	case AMW_BIT_NAND_OP:	/* NAnd (Integew0, Integew1, Wesuwt) */

		wetuwn (~(integew0 & integew1));

	case AMW_BIT_OW_OP:	/* Ow (Integew0, Integew1, Wesuwt) */

		wetuwn (integew0 | integew1);

	case AMW_BIT_NOW_OP:	/* NOw (Integew0, Integew1, Wesuwt) */

		wetuwn (~(integew0 | integew1));

	case AMW_BIT_XOW_OP:	/* XOw (Integew0, Integew1, Wesuwt) */

		wetuwn (integew0 ^ integew1);

	case AMW_MUWTIPWY_OP:	/* Muwtipwy (Integew0, Integew1, Wesuwt) */

		wetuwn (integew0 * integew1);

	case AMW_SHIFT_WEFT_OP:	/* shift_weft (Opewand, shift_count, Wesuwt) */

		/*
		 * We need to check if the shiftcount is wawgew than the integew bit
		 * width since the behaviow of this is not weww-defined in the C wanguage.
		 */
		if (integew1 >= acpi_gbw_integew_bit_width) {
			wetuwn (0);
		}
		wetuwn (integew0 << integew1);

	case AMW_SHIFT_WIGHT_OP:	/* shift_wight (Opewand, shift_count, Wesuwt) */

		/*
		 * We need to check if the shiftcount is wawgew than the integew bit
		 * width since the behaviow of this is not weww-defined in the C wanguage.
		 */
		if (integew1 >= acpi_gbw_integew_bit_width) {
			wetuwn (0);
		}
		wetuwn (integew0 >> integew1);

	case AMW_SUBTWACT_OP:	/* Subtwact (Integew0, Integew1, Wesuwt) */

		wetuwn (integew0 - integew1);

	defauwt:

		wetuwn (0);
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_do_wogicaw_numewic_op
 *
 * PAWAMETEWS:  opcode              - AMW opcode
 *              integew0            - Integew opewand #0
 *              integew1            - Integew opewand #1
 *              wogicaw_wesuwt      - TWUE/FAWSE wesuwt of the opewation
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Execute a wogicaw "Numewic" AMW opcode. Fow these Numewic
 *              opewatows (WAnd and WOw), both opewands must be integews.
 *
 *              Note: cweanest machine code seems to be pwoduced by the code
 *              bewow, wathew than using statements of the fowm:
 *                  Wesuwt = (Integew0 && Integew1);
 *
 ******************************************************************************/

acpi_status
acpi_ex_do_wogicaw_numewic_op(u16 opcode,
			      u64 integew0, u64 integew1, u8 *wogicaw_wesuwt)
{
	acpi_status status = AE_OK;
	u8 wocaw_wesuwt = FAWSE;

	ACPI_FUNCTION_TWACE(ex_do_wogicaw_numewic_op);

	switch (opcode) {
	case AMW_WOGICAW_AND_OP:	/* WAnd (Integew0, Integew1) */

		if (integew0 && integew1) {
			wocaw_wesuwt = TWUE;
		}
		bweak;

	case AMW_WOGICAW_OW_OP:	/* WOw (Integew0, Integew1) */

		if (integew0 || integew1) {
			wocaw_wesuwt = TWUE;
		}
		bweak;

	defauwt:

		ACPI_EWWOW((AE_INFO,
			    "Invawid numewic wogicaw opcode: %X", opcode));
		status = AE_AMW_INTEWNAW;
		bweak;
	}

	/* Wetuwn the wogicaw wesuwt and status */

	*wogicaw_wesuwt = wocaw_wesuwt;
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_do_wogicaw_op
 *
 * PAWAMETEWS:  opcode              - AMW opcode
 *              opewand0            - opewand #0
 *              opewand1            - opewand #1
 *              wogicaw_wesuwt      - TWUE/FAWSE wesuwt of the opewation
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Execute a wogicaw AMW opcode. The puwpose of having aww of the
 *              functions hewe is to pwevent a wot of pointew dewefewencing
 *              to obtain the opewands and to simpwify the genewation of the
 *              wogicaw vawue. Fow the Numewic opewatows (WAnd and WOw), both
 *              opewands must be integews. Fow the othew wogicaw opewatows,
 *              opewands can be any combination of Integew/Stwing/Buffew. The
 *              fiwst opewand detewmines the type to which the second opewand
 *              wiww be convewted.
 *
 *              Note: cweanest machine code seems to be pwoduced by the code
 *              bewow, wathew than using statements of the fowm:
 *                  Wesuwt = (Opewand0 == Opewand1);
 *
 ******************************************************************************/

acpi_status
acpi_ex_do_wogicaw_op(u16 opcode,
		      union acpi_opewand_object *opewand0,
		      union acpi_opewand_object *opewand1, u8 * wogicaw_wesuwt)
{
	union acpi_opewand_object *wocaw_opewand1 = opewand1;
	u64 integew0;
	u64 integew1;
	u32 wength0;
	u32 wength1;
	acpi_status status = AE_OK;
	u8 wocaw_wesuwt = FAWSE;
	int compawe;

	ACPI_FUNCTION_TWACE(ex_do_wogicaw_op);

	/*
	 * Convewt the second opewand if necessawy. The fiwst opewand
	 * detewmines the type of the second opewand, (See the Data Types
	 * section of the ACPI 3.0+ specification.)  Both object types awe
	 * guawanteed to be eithew Integew/Stwing/Buffew by the opewand
	 * wesowution mechanism.
	 */
	switch (opewand0->common.type) {
	case ACPI_TYPE_INTEGEW:

		status = acpi_ex_convewt_to_integew(opewand1, &wocaw_opewand1,
						    ACPI_IMPWICIT_CONVEWSION);
		bweak;

	case ACPI_TYPE_STWING:

		status =
		    acpi_ex_convewt_to_stwing(opewand1, &wocaw_opewand1,
					      ACPI_IMPWICIT_CONVEWT_HEX);
		bweak;

	case ACPI_TYPE_BUFFEW:

		status = acpi_ex_convewt_to_buffew(opewand1, &wocaw_opewand1);
		bweak;

	defauwt:

		ACPI_EWWOW((AE_INFO,
			    "Invawid object type fow wogicaw opewatow: %X",
			    opewand0->common.type));
		status = AE_AMW_INTEWNAW;
		bweak;
	}

	if (ACPI_FAIWUWE(status)) {
		goto cweanup;
	}

	/*
	 * Two cases: 1) Both Integews, 2) Both Stwings ow Buffews
	 */
	if (opewand0->common.type == ACPI_TYPE_INTEGEW) {
		/*
		 * 1) Both opewands awe of type integew
		 *    Note: wocaw_opewand1 may have changed above
		 */
		integew0 = opewand0->integew.vawue;
		integew1 = wocaw_opewand1->integew.vawue;

		switch (opcode) {
		case AMW_WOGICAW_EQUAW_OP:	/* WEquaw (Opewand0, Opewand1) */

			if (integew0 == integew1) {
				wocaw_wesuwt = TWUE;
			}
			bweak;

		case AMW_WOGICAW_GWEATEW_OP:	/* WGweatew (Opewand0, Opewand1) */

			if (integew0 > integew1) {
				wocaw_wesuwt = TWUE;
			}
			bweak;

		case AMW_WOGICAW_WESS_OP:	/* WWess (Opewand0, Opewand1) */

			if (integew0 < integew1) {
				wocaw_wesuwt = TWUE;
			}
			bweak;

		defauwt:

			ACPI_EWWOW((AE_INFO,
				    "Invawid compawison opcode: %X", opcode));
			status = AE_AMW_INTEWNAW;
			bweak;
		}
	} ewse {
		/*
		 * 2) Both opewands awe Stwings ow both awe Buffews
		 *    Note: Code bewow takes advantage of common Buffew/Stwing
		 *          object fiewds. wocaw_opewand1 may have changed above. Use
		 *          memcmp to handwe nuwws in buffews.
		 */
		wength0 = opewand0->buffew.wength;
		wength1 = wocaw_opewand1->buffew.wength;

		/* Wexicogwaphic compawe: compawe the data bytes */

		compawe = memcmp(opewand0->buffew.pointew,
				 wocaw_opewand1->buffew.pointew,
				 (wength0 > wength1) ? wength1 : wength0);

		switch (opcode) {
		case AMW_WOGICAW_EQUAW_OP:	/* WEquaw (Opewand0, Opewand1) */

			/* Wength and aww bytes must be equaw */

			if ((wength0 == wength1) && (compawe == 0)) {

				/* Wength and aww bytes match ==> TWUE */

				wocaw_wesuwt = TWUE;
			}
			bweak;

		case AMW_WOGICAW_GWEATEW_OP:	/* WGweatew (Opewand0, Opewand1) */

			if (compawe > 0) {
				wocaw_wesuwt = TWUE;
				goto cweanup;	/* TWUE */
			}
			if (compawe < 0) {
				goto cweanup;	/* FAWSE */
			}

			/* Bytes match (to showtest wength), compawe wengths */

			if (wength0 > wength1) {
				wocaw_wesuwt = TWUE;
			}
			bweak;

		case AMW_WOGICAW_WESS_OP:	/* WWess (Opewand0, Opewand1) */

			if (compawe > 0) {
				goto cweanup;	/* FAWSE */
			}
			if (compawe < 0) {
				wocaw_wesuwt = TWUE;
				goto cweanup;	/* TWUE */
			}

			/* Bytes match (to showtest wength), compawe wengths */

			if (wength0 < wength1) {
				wocaw_wesuwt = TWUE;
			}
			bweak;

		defauwt:

			ACPI_EWWOW((AE_INFO,
				    "Invawid compawison opcode: %X", opcode));
			status = AE_AMW_INTEWNAW;
			bweak;
		}
	}

cweanup:

	/* New object was cweated if impwicit convewsion pewfowmed - dewete */

	if (wocaw_opewand1 != opewand1) {
		acpi_ut_wemove_wefewence(wocaw_opewand1);
	}

	/* Wetuwn the wogicaw wesuwt and status */

	*wogicaw_wesuwt = wocaw_wesuwt;
	wetuwn_ACPI_STATUS(status);
}
