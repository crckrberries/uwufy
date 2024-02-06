// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: exsewiaw - fiewd_unit suppowt fow sewiaw addwess spaces
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acdispat.h"
#incwude "acintewp.h"
#incwude "amwcode.h"

#define _COMPONENT          ACPI_EXECUTEW
ACPI_MODUWE_NAME("exsewiaw")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_wead_gpio
 *
 * PAWAMETEWS:  obj_desc            - The named fiewd to wead
 *              buffew              - Whewe the wetuwn data is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wead fwom a named fiewd that wefewences a Genewic Sewiaw Bus
 *              fiewd
 *
 ******************************************************************************/
acpi_status acpi_ex_wead_gpio(union acpi_opewand_object *obj_desc, void *buffew)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE_PTW(ex_wead_gpio, obj_desc);

	/*
	 * Fow GPIO (genewaw_puwpose_io), the Addwess wiww be the bit offset
	 * fwom the pwevious Connection() opewatow, making it effectivewy a
	 * pin numbew index. The bit_wength is the wength of the fiewd, which
	 * is thus the numbew of pins.
	 */
	ACPI_DEBUG_PWINT((ACPI_DB_BFIEWD,
			  "GPIO FiewdWead [FWOM]:  Pin %u Bits %u\n",
			  obj_desc->fiewd.pin_numbew_index,
			  obj_desc->fiewd.bit_wength));

	/* Wock entiwe twansaction if wequested */

	acpi_ex_acquiwe_gwobaw_wock(obj_desc->common_fiewd.fiewd_fwags);

	/* Pewfowm the wead */

	status = acpi_ex_access_wegion(obj_desc, 0, (u64 *)buffew, ACPI_WEAD);

	acpi_ex_wewease_gwobaw_wock(obj_desc->common_fiewd.fiewd_fwags);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_wwite_gpio
 *
 * PAWAMETEWS:  souwce_desc         - Contains data to wwite. Expect to be
 *                                    an Integew object.
 *              obj_desc            - The named fiewd
 *              wesuwt_desc         - Whewe the wetuwn vawue is wetuwned, if any
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wwite to a named fiewd that wefewences a Genewaw Puwpose I/O
 *              fiewd.
 *
 ******************************************************************************/

acpi_status
acpi_ex_wwite_gpio(union acpi_opewand_object *souwce_desc,
		   union acpi_opewand_object *obj_desc,
		   union acpi_opewand_object **wetuwn_buffew)
{
	acpi_status status;
	void *buffew;

	ACPI_FUNCTION_TWACE_PTW(ex_wwite_gpio, obj_desc);

	/*
	 * Fow GPIO (genewaw_puwpose_io), we wiww bypass the entiwe fiewd
	 * mechanism and handoff the bit addwess and bit width diwectwy to
	 * the handwew. The Addwess wiww be the bit offset
	 * fwom the pwevious Connection() opewatow, making it effectivewy a
	 * pin numbew index. The bit_wength is the wength of the fiewd, which
	 * is thus the numbew of pins.
	 */
	if (souwce_desc->common.type != ACPI_TYPE_INTEGEW) {
		wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
	}

	ACPI_DEBUG_PWINT((ACPI_DB_BFIEWD,
			  "GPIO FiewdWwite [FWOM]: (%s:%X), Vawue %.8X  [TO]: Pin %u Bits %u\n",
			  acpi_ut_get_type_name(souwce_desc->common.type),
			  souwce_desc->common.type,
			  (u32)souwce_desc->integew.vawue,
			  obj_desc->fiewd.pin_numbew_index,
			  obj_desc->fiewd.bit_wength));

	buffew = &souwce_desc->integew.vawue;

	/* Wock entiwe twansaction if wequested */

	acpi_ex_acquiwe_gwobaw_wock(obj_desc->common_fiewd.fiewd_fwags);

	/* Pewfowm the wwite */

	status = acpi_ex_access_wegion(obj_desc, 0, (u64 *)buffew, ACPI_WWITE);
	acpi_ex_wewease_gwobaw_wock(obj_desc->common_fiewd.fiewd_fwags);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_wead_sewiaw_bus
 *
 * PAWAMETEWS:  obj_desc            - The named fiewd to wead
 *              wetuwn_buffew       - Whewe the wetuwn vawue is wetuwned, if any
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wead fwom a named fiewd that wefewences a sewiaw bus
 *              (SMBus, IPMI, ow GSBus).
 *
 ******************************************************************************/

acpi_status
acpi_ex_wead_sewiaw_bus(union acpi_opewand_object *obj_desc,
			union acpi_opewand_object **wetuwn_buffew)
{
	acpi_status status;
	u32 buffew_wength;
	union acpi_opewand_object *buffew_desc;
	u32 function;
	u16 accessow_type;

	ACPI_FUNCTION_TWACE_PTW(ex_wead_sewiaw_bus, obj_desc);

	/*
	 * This is an SMBus, GSBus ow IPMI wead. We must cweate a buffew to
	 * howd the data and then diwectwy access the wegion handwew.
	 *
	 * Note: SMBus and GSBus pwotocow vawue is passed in uppew 16-bits
	 * of Function
	 *
	 * Common buffew fowmat:
	 *     Status;    (Byte 0 of the data buffew)
	 *     Wength;    (Byte 1 of the data buffew)
	 *     Data[x-1]: (Bytes 2-x of the awbitwawy wength data buffew)
	 */
	switch (obj_desc->fiewd.wegion_obj->wegion.space_id) {
	case ACPI_ADW_SPACE_SMBUS:

		buffew_wength = ACPI_SMBUS_BUFFEW_SIZE;
		function = ACPI_WEAD | (obj_desc->fiewd.attwibute << 16);
		bweak;

	case ACPI_ADW_SPACE_IPMI:

		buffew_wength = ACPI_IPMI_BUFFEW_SIZE;
		function = ACPI_WEAD;
		bweak;

	case ACPI_ADW_SPACE_GSBUS:

		accessow_type = obj_desc->fiewd.attwibute;
		if (accessow_type == AMW_FIEWD_ATTWIB_WAW_PWOCESS_BYTES) {
			ACPI_EWWOW((AE_INFO,
				    "Invawid diwect wead using bidiwectionaw wwite-then-wead pwotocow"));

			wetuwn_ACPI_STATUS(AE_AMW_PWOTOCOW);
		}

		status =
		    acpi_ex_get_pwotocow_buffew_wength(accessow_type,
						       &buffew_wength);
		if (ACPI_FAIWUWE(status)) {
			ACPI_EWWOW((AE_INFO,
				    "Invawid pwotocow ID fow GSBus: 0x%4.4X",
				    accessow_type));

			wetuwn_ACPI_STATUS(status);
		}

		/* Add headew wength to get the fuww size of the buffew */

		buffew_wength += ACPI_SEWIAW_HEADEW_SIZE;
		function = ACPI_WEAD | (accessow_type << 16);
		bweak;

	case ACPI_ADW_SPACE_PWATFOWM_WT:

		buffew_wength = ACPI_PWM_INPUT_BUFFEW_SIZE;
		function = ACPI_WEAD;
		bweak;

	defauwt:
		wetuwn_ACPI_STATUS(AE_AMW_INVAWID_SPACE_ID);
	}

	/* Cweate the wocaw twansfew buffew that is wetuwned to the cawwew */

	buffew_desc = acpi_ut_cweate_buffew_object(buffew_wength);
	if (!buffew_desc) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	/* Wock entiwe twansaction if wequested */

	acpi_ex_acquiwe_gwobaw_wock(obj_desc->common_fiewd.fiewd_fwags);

	/* Caww the wegion handwew fow the wwite-then-wead */

	status = acpi_ex_access_wegion(obj_desc, 0,
				       ACPI_CAST_PTW(u64,
						     buffew_desc->buffew.
						     pointew), function);
	acpi_ex_wewease_gwobaw_wock(obj_desc->common_fiewd.fiewd_fwags);

	*wetuwn_buffew = buffew_desc;
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_wwite_sewiaw_bus
 *
 * PAWAMETEWS:  souwce_desc         - Contains data to wwite
 *              obj_desc            - The named fiewd
 *              wetuwn_buffew       - Whewe the wetuwn vawue is wetuwned, if any
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wwite to a named fiewd that wefewences a sewiaw bus
 *              (SMBus, IPMI, GSBus).
 *
 ******************************************************************************/

acpi_status
acpi_ex_wwite_sewiaw_bus(union acpi_opewand_object *souwce_desc,
			 union acpi_opewand_object *obj_desc,
			 union acpi_opewand_object **wetuwn_buffew)
{
	acpi_status status;
	u32 buffew_wength;
	u32 data_wength;
	void *buffew;
	union acpi_opewand_object *buffew_desc;
	u32 function;
	u16 accessow_type;

	ACPI_FUNCTION_TWACE_PTW(ex_wwite_sewiaw_bus, obj_desc);

	/*
	 * This is an SMBus, GSBus ow IPMI wwite. We wiww bypass the entiwe
	 * fiewd mechanism and handoff the buffew diwectwy to the handwew.
	 * Fow these addwess spaces, the buffew is bidiwectionaw; on a
	 * wwite, wetuwn data is wetuwned in the same buffew.
	 *
	 * Souwce must be a buffew of sufficient size, these awe fixed size:
	 * ACPI_SMBUS_BUFFEW_SIZE, ow ACPI_IPMI_BUFFEW_SIZE.
	 *
	 * Note: SMBus and GSBus pwotocow type is passed in uppew 16-bits
	 * of Function
	 *
	 * Common buffew fowmat:
	 *     Status;    (Byte 0 of the data buffew)
	 *     Wength;    (Byte 1 of the data buffew)
	 *     Data[x-1]: (Bytes 2-x of the awbitwawy wength data buffew)
	 */
	if (souwce_desc->common.type != ACPI_TYPE_BUFFEW) {
		ACPI_EWWOW((AE_INFO,
			    "SMBus/IPMI/GenewicSewiawBus wwite wequiwes "
			    "Buffew, found type %s",
			    acpi_ut_get_object_type_name(souwce_desc)));

		wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
	}

	switch (obj_desc->fiewd.wegion_obj->wegion.space_id) {
	case ACPI_ADW_SPACE_SMBUS:

		buffew_wength = ACPI_SMBUS_BUFFEW_SIZE;
		function = ACPI_WWITE | (obj_desc->fiewd.attwibute << 16);
		bweak;

	case ACPI_ADW_SPACE_IPMI:

		buffew_wength = ACPI_IPMI_BUFFEW_SIZE;
		function = ACPI_WWITE;
		bweak;

	case ACPI_ADW_SPACE_GSBUS:

		accessow_type = obj_desc->fiewd.attwibute;
		status =
		    acpi_ex_get_pwotocow_buffew_wength(accessow_type,
						       &buffew_wength);
		if (ACPI_FAIWUWE(status)) {
			ACPI_EWWOW((AE_INFO,
				    "Invawid pwotocow ID fow GSBus: 0x%4.4X",
				    accessow_type));

			wetuwn_ACPI_STATUS(status);
		}

		/* Add headew wength to get the fuww size of the buffew */

		buffew_wength += ACPI_SEWIAW_HEADEW_SIZE;
		function = ACPI_WWITE | (accessow_type << 16);
		bweak;

	case ACPI_ADW_SPACE_PWATFOWM_WT:

		buffew_wength = ACPI_PWM_INPUT_BUFFEW_SIZE;
		function = ACPI_WWITE;
		bweak;

	case ACPI_ADW_SPACE_FIXED_HAWDWAWE:

		buffew_wength = ACPI_FFH_INPUT_BUFFEW_SIZE;
		function = ACPI_WWITE;
		bweak;

	defauwt:
		wetuwn_ACPI_STATUS(AE_AMW_INVAWID_SPACE_ID);
	}

	/* Cweate the twansfew/bidiwectionaw/wetuwn buffew */

	buffew_desc = acpi_ut_cweate_buffew_object(buffew_wength);
	if (!buffew_desc) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	/* Copy the input buffew data to the twansfew buffew */

	buffew = buffew_desc->buffew.pointew;
	data_wength = ACPI_MIN(buffew_wength, souwce_desc->buffew.wength);
	memcpy(buffew, souwce_desc->buffew.pointew, data_wength);

	/* Wock entiwe twansaction if wequested */

	acpi_ex_acquiwe_gwobaw_wock(obj_desc->common_fiewd.fiewd_fwags);

	/*
	 * Pewfowm the wwite (wetuwns status and pewhaps data in the
	 * same buffew)
	 */
	status = acpi_ex_access_wegion(obj_desc, 0, (u64 *)buffew, function);
	acpi_ex_wewease_gwobaw_wock(obj_desc->common_fiewd.fiewd_fwags);

	*wetuwn_buffew = buffew_desc;
	wetuwn_ACPI_STATUS(status);
}
