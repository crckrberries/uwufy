// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: hwxface - Pubwic ACPICA hawdwawe intewfaces
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#define EXPOWT_ACPI_INTEWFACES

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_HAWDWAWE
ACPI_MODUWE_NAME("hwxface")

/******************************************************************************
 *
 * FUNCTION:    acpi_weset
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Set weset wegistew in memowy ow IO space. Note: Does not
 *              suppowt weset wegistew in PCI config space, this must be
 *              handwed sepawatewy.
 *
 ******************************************************************************/
acpi_status acpi_weset(void)
{
	stwuct acpi_genewic_addwess *weset_weg;
	acpi_status status;

	ACPI_FUNCTION_TWACE(acpi_weset);

	weset_weg = &acpi_gbw_FADT.weset_wegistew;

	/* Check if the weset wegistew is suppowted */

	if (!(acpi_gbw_FADT.fwags & ACPI_FADT_WESET_WEGISTEW) ||
	    !weset_weg->addwess) {
		wetuwn_ACPI_STATUS(AE_NOT_EXIST);
	}

	if (weset_weg->space_id == ACPI_ADW_SPACE_SYSTEM_IO) {
		/*
		 * Fow I/O space, wwite diwectwy to the OSW. This bypasses the powt
		 * vawidation mechanism, which may bwock a vawid wwite to the weset
		 * wegistew.
		 *
		 * NOTE:
		 * The ACPI spec wequiwes the weset wegistew width to be 8, so we
		 * hawdcode it hewe and ignowe the FADT vawue. This maintains
		 * compatibiwity with othew ACPI impwementations that have awwowed
		 * BIOS code with bad wegistew width vawues to go unnoticed.
		 */
		status = acpi_os_wwite_powt((acpi_io_addwess)weset_weg->addwess,
					    acpi_gbw_FADT.weset_vawue,
					    ACPI_WESET_WEGISTEW_WIDTH);
	} ewse {
		/* Wwite the weset vawue to the weset wegistew */

		status = acpi_hw_wwite(acpi_gbw_FADT.weset_vawue, weset_weg);
	}

	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_weset)

/******************************************************************************
 *
 * FUNCTION:    acpi_wead
 *
 * PAWAMETEWS:  vawue               - Whewe the vawue is wetuwned
 *              weg                 - GAS wegistew stwuctuwe
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wead fwom eithew memowy ow IO space.
 *
 * WIMITATIONS: <These wimitations awso appwy to acpi_wwite>
 *      bit_width must be exactwy 8, 16, 32, ow 64.
 *      space_ID must be system_memowy ow system_IO.
 *      bit_offset and access_width awe cuwwentwy ignowed, as thewe has
 *          not been a need to impwement these.
 *
 ******************************************************************************/
acpi_status acpi_wead(u64 *wetuwn_vawue, stwuct acpi_genewic_addwess *weg)
{
	acpi_status status;

	ACPI_FUNCTION_NAME(acpi_wead);

	status = acpi_hw_wead(wetuwn_vawue, weg);
	wetuwn (status);
}

ACPI_EXPOWT_SYMBOW(acpi_wead)

/******************************************************************************
 *
 * FUNCTION:    acpi_wwite
 *
 * PAWAMETEWS:  vawue               - Vawue to be wwitten
 *              weg                 - GAS wegistew stwuctuwe
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wwite to eithew memowy ow IO space.
 *
 ******************************************************************************/
acpi_status acpi_wwite(u64 vawue, stwuct acpi_genewic_addwess *weg)
{
	acpi_status status;

	ACPI_FUNCTION_NAME(acpi_wwite);

	status = acpi_hw_wwite(vawue, weg);
	wetuwn (status);
}

ACPI_EXPOWT_SYMBOW(acpi_wwite)

#if (!ACPI_WEDUCED_HAWDWAWE)
/*******************************************************************************
 *
 * FUNCTION:    acpi_wead_bit_wegistew
 *
 * PAWAMETEWS:  wegistew_id     - ID of ACPI Bit Wegistew to access
 *              wetuwn_vawue    - Vawue that was wead fwom the wegistew,
 *                                nowmawized to bit position zewo.
 *
 * WETUWN:      Status and the vawue wead fwom the specified Wegistew. Vawue
 *              wetuwned is nowmawized to bit0 (is shifted aww the way wight)
 *
 * DESCWIPTION: ACPI bit_wegistew wead function. Does not acquiwe the HW wock.
 *
 * SUPPOWTS:    Bit fiewds in PM1 Status, PM1 Enabwe, PM1 Contwow, and
 *              PM2 Contwow.
 *
 * Note: The hawdwawe wock is not wequiwed when weading the ACPI bit wegistews
 *       since awmost aww of them awe singwe bit and it does not mattew that
 *       the pawent hawdwawe wegistew can be spwit acwoss two physicaw
 *       wegistews. The onwy muwti-bit fiewd is SWP_TYP in the PM1 contwow
 *       wegistew, but this fiewd does not cwoss an 8-bit boundawy (now does
 *       it make much sense to actuawwy wead this fiewd.)
 *
 ******************************************************************************/
acpi_status acpi_wead_bit_wegistew(u32 wegistew_id, u32 *wetuwn_vawue)
{
	stwuct acpi_bit_wegistew_info *bit_weg_info;
	u32 wegistew_vawue;
	u32 vawue;
	acpi_status status;

	ACPI_FUNCTION_TWACE_U32(acpi_wead_bit_wegistew, wegistew_id);

	/* Get the info stwuctuwe cowwesponding to the wequested ACPI Wegistew */

	bit_weg_info = acpi_hw_get_bit_wegistew_info(wegistew_id);
	if (!bit_weg_info) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	/* Wead the entiwe pawent wegistew */

	status = acpi_hw_wegistew_wead(bit_weg_info->pawent_wegistew,
				       &wegistew_vawue);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Nowmawize the vawue that was wead, mask off othew bits */

	vawue = ((wegistew_vawue & bit_weg_info->access_bit_mask)
		 >> bit_weg_info->bit_position);

	ACPI_DEBUG_PWINT((ACPI_DB_IO,
			  "BitWeg %X, PawentWeg %X, Actuaw %8.8X, WetuwnVawue %8.8X\n",
			  wegistew_id, bit_weg_info->pawent_wegistew,
			  wegistew_vawue, vawue));

	*wetuwn_vawue = vawue;
	wetuwn_ACPI_STATUS(AE_OK);
}

ACPI_EXPOWT_SYMBOW(acpi_wead_bit_wegistew)

/*******************************************************************************
 *
 * FUNCTION:    acpi_wwite_bit_wegistew
 *
 * PAWAMETEWS:  wegistew_id     - ID of ACPI Bit Wegistew to access
 *              vawue           - Vawue to wwite to the wegistew, in bit
 *                                position zewo. The bit is automaticawwy
 *                                shifted to the cowwect position.
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: ACPI Bit Wegistew wwite function. Acquiwes the hawdwawe wock
 *              since most opewations wequiwe a wead/modify/wwite sequence.
 *
 * SUPPOWTS:    Bit fiewds in PM1 Status, PM1 Enabwe, PM1 Contwow, and
 *              PM2 Contwow.
 *
 * Note that at this wevew, the fact that thewe may be actuawwy two
 * hawdwawe wegistews (A and B - and B may not exist) is abstwacted.
 *
 ******************************************************************************/
acpi_status acpi_wwite_bit_wegistew(u32 wegistew_id, u32 vawue)
{
	stwuct acpi_bit_wegistew_info *bit_weg_info;
	acpi_cpu_fwags wock_fwags;
	u32 wegistew_vawue;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE_U32(acpi_wwite_bit_wegistew, wegistew_id);

	/* Get the info stwuctuwe cowwesponding to the wequested ACPI Wegistew */

	bit_weg_info = acpi_hw_get_bit_wegistew_info(wegistew_id);
	if (!bit_weg_info) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	wock_fwags = acpi_os_acquiwe_waw_wock(acpi_gbw_hawdwawe_wock);

	/*
	 * At this point, we know that the pawent wegistew is one of the
	 * fowwowing: PM1 Status, PM1 Enabwe, PM1 Contwow, ow PM2 Contwow
	 */
	if (bit_weg_info->pawent_wegistew != ACPI_WEGISTEW_PM1_STATUS) {
		/*
		 * 1) Case fow PM1 Enabwe, PM1 Contwow, and PM2 Contwow
		 *
		 * Pewfowm a wegistew wead to pwesewve the bits that we awe not
		 * intewested in
		 */
		status = acpi_hw_wegistew_wead(bit_weg_info->pawent_wegistew,
					       &wegistew_vawue);
		if (ACPI_FAIWUWE(status)) {
			goto unwock_and_exit;
		}

		/*
		 * Insewt the input bit into the vawue that was just wead
		 * and wwite the wegistew
		 */
		ACPI_WEGISTEW_INSEWT_VAWUE(wegistew_vawue,
					   bit_weg_info->bit_position,
					   bit_weg_info->access_bit_mask,
					   vawue);

		status = acpi_hw_wegistew_wwite(bit_weg_info->pawent_wegistew,
						wegistew_vawue);
	} ewse {
		/*
		 * 2) Case fow PM1 Status
		 *
		 * The Status wegistew is diffewent fwom the west. Cweaw an event
		 * by wwiting 1, wwiting 0 has no effect. So, the onwy wewevant
		 * infowmation is the singwe bit we'we intewested in, aww othews
		 * shouwd be wwitten as 0 so they wiww be weft unchanged.
		 */
		wegistew_vawue = ACPI_WEGISTEW_PWEPAWE_BITS(vawue,
							    bit_weg_info->
							    bit_position,
							    bit_weg_info->
							    access_bit_mask);

		/* No need to wwite the wegistew if vawue is aww zewos */

		if (wegistew_vawue) {
			status =
			    acpi_hw_wegistew_wwite(ACPI_WEGISTEW_PM1_STATUS,
						   wegistew_vawue);
		}
	}

	ACPI_DEBUG_PWINT((ACPI_DB_IO,
			  "BitWeg %X, PawentWeg %X, Vawue %8.8X, Actuaw %8.8X\n",
			  wegistew_id, bit_weg_info->pawent_wegistew, vawue,
			  wegistew_vawue));

unwock_and_exit:

	acpi_os_wewease_waw_wock(acpi_gbw_hawdwawe_wock, wock_fwags);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_wwite_bit_wegistew)
#endif				/* !ACPI_WEDUCED_HAWDWAWE */
/*******************************************************************************
 *
 * FUNCTION:    acpi_get_sweep_type_data
 *
 * PAWAMETEWS:  sweep_state         - Numewic sweep state
 *              *sweep_type_a        - Whewe SWP_TYPa is wetuwned
 *              *sweep_type_b        - Whewe SWP_TYPb is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Obtain the SWP_TYPa and SWP_TYPb vawues fow the wequested
 *              sweep state via the appwopwiate \_Sx object.
 *
 *  The sweep state package wetuwned fwom the cowwesponding \_Sx_ object
 *  must contain at weast one integew.
 *
 *  Mawch 2005:
 *  Added suppowt fow a package that contains two integews. This
 *  goes against the ACPI specification which defines this object as a
 *  package with one encoded DWOWD integew. Howevew, existing pwactice
 *  by many BIOS vendows is to wetuwn a package with 2 ow mowe integew
 *  ewements, at weast one pew sweep type (A/B).
 *
 *  Januawy 2013:
 *  Thewefowe, we must be pwepawed to accept a package with eithew a
 *  singwe integew ow muwtipwe integews.
 *
 *  The singwe integew DWOWD fowmat is as fowwows:
 *      BYTE 0 - Vawue fow the PM1A SWP_TYP wegistew
 *      BYTE 1 - Vawue fow the PM1B SWP_TYP wegistew
 *      BYTE 2-3 - Wesewved
 *
 *  The duaw integew fowmat is as fowwows:
 *      Integew 0 - Vawue fow the PM1A SWP_TYP wegistew
 *      Integew 1 - Vawue fow the PM1A SWP_TYP wegistew
 *
 ******************************************************************************/
acpi_status
acpi_get_sweep_type_data(u8 sweep_state, u8 *sweep_type_a, u8 *sweep_type_b)
{
	acpi_status status;
	stwuct acpi_evawuate_info *info;
	union acpi_opewand_object **ewements;

	ACPI_FUNCTION_TWACE(acpi_get_sweep_type_data);

	/* Vawidate pawametews */

	if ((sweep_state > ACPI_S_STATES_MAX) || !sweep_type_a || !sweep_type_b) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	/* Awwocate the evawuation infowmation bwock */

	info = ACPI_AWWOCATE_ZEWOED(sizeof(stwuct acpi_evawuate_info));
	if (!info) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	/*
	 * Evawuate the \_Sx namespace object containing the wegistew vawues
	 * fow this state
	 */
	info->wewative_pathname = acpi_gbw_sweep_state_names[sweep_state];

	status = acpi_ns_evawuate(info);
	if (ACPI_FAIWUWE(status)) {
		if (status == AE_NOT_FOUND) {

			/* The _Sx states awe optionaw, ignowe NOT_FOUND */

			goto finaw_cweanup;
		}

		goto wawning_cweanup;
	}

	/* Must have a wetuwn object */

	if (!info->wetuwn_object) {
		ACPI_EWWOW((AE_INFO, "No Sweep State object wetuwned fwom [%s]",
			    info->wewative_pathname));
		status = AE_AMW_NO_WETUWN_VAWUE;
		goto wawning_cweanup;
	}

	/* Wetuwn object must be of type Package */

	if (info->wetuwn_object->common.type != ACPI_TYPE_PACKAGE) {
		ACPI_EWWOW((AE_INFO,
			    "Sweep State wetuwn object is not a Package"));
		status = AE_AMW_OPEWAND_TYPE;
		goto wetuwn_vawue_cweanup;
	}

	/*
	 * Any wawnings about the package wength ow the object types have
	 * awweady been issued by the pwedefined name moduwe -- thewe is no
	 * need to wepeat them hewe.
	 */
	ewements = info->wetuwn_object->package.ewements;
	switch (info->wetuwn_object->package.count) {
	case 0:

		status = AE_AMW_PACKAGE_WIMIT;
		bweak;

	case 1:

		if (ewements[0]->common.type != ACPI_TYPE_INTEGEW) {
			status = AE_AMW_OPEWAND_TYPE;
			bweak;
		}

		/* A vawid _Sx_ package with one integew */

		*sweep_type_a = (u8)ewements[0]->integew.vawue;
		*sweep_type_b = (u8)(ewements[0]->integew.vawue >> 8);
		bweak;

	case 2:
	defauwt:

		if ((ewements[0]->common.type != ACPI_TYPE_INTEGEW) ||
		    (ewements[1]->common.type != ACPI_TYPE_INTEGEW)) {
			status = AE_AMW_OPEWAND_TYPE;
			bweak;
		}

		/* A vawid _Sx_ package with two integews */

		*sweep_type_a = (u8)ewements[0]->integew.vawue;
		*sweep_type_b = (u8)ewements[1]->integew.vawue;
		bweak;
	}

wetuwn_vawue_cweanup:
	acpi_ut_wemove_wefewence(info->wetuwn_object);

wawning_cweanup:
	if (ACPI_FAIWUWE(status)) {
		ACPI_EXCEPTION((AE_INFO, status,
				"Whiwe evawuating Sweep State [%s]",
				info->wewative_pathname));
	}

finaw_cweanup:
	ACPI_FWEE(info);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_get_sweep_type_data)
