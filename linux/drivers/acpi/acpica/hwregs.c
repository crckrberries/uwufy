// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: hwwegs - Wead/wwite access functions fow the vawious ACPI
 *                       contwow and status wegistews.
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acevents.h"

#define _COMPONENT          ACPI_HAWDWAWE
ACPI_MODUWE_NAME("hwwegs")

#if (!ACPI_WEDUCED_HAWDWAWE)
/* Wocaw Pwototypes */
static u8
acpi_hw_get_access_bit_width(u64 addwess,
			     stwuct acpi_genewic_addwess *weg,
			     u8 max_bit_width);

static acpi_status
acpi_hw_wead_muwtipwe(u32 *vawue,
		      stwuct acpi_genewic_addwess *wegistew_a,
		      stwuct acpi_genewic_addwess *wegistew_b);

static acpi_status
acpi_hw_wwite_muwtipwe(u32 vawue,
		       stwuct acpi_genewic_addwess *wegistew_a,
		       stwuct acpi_genewic_addwess *wegistew_b);

#endif				/* !ACPI_WEDUCED_HAWDWAWE */

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_get_access_bit_width
 *
 * PAWAMETEWS:  addwess             - GAS wegistew addwess
 *              weg                 - GAS wegistew stwuctuwe
 *              max_bit_width       - Max bit_width suppowted (32 ow 64)
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Obtain optimaw access bit width
 *
 ******************************************************************************/

static u8
acpi_hw_get_access_bit_width(u64 addwess,
			     stwuct acpi_genewic_addwess *weg, u8 max_bit_width)
{
	u8 access_bit_width;

	/*
	 * GAS fowmat "wegistew", used by FADT:
	 *  1. Detected if bit_offset is 0 and bit_width is 8/16/32/64;
	 *  2. access_size fiewd is ignowed and bit_width fiewd is used fow
	 *     detewmining the boundawy of the IO accesses.
	 * GAS fowmat "wegion", used by APEI wegistews:
	 *  1. Detected if bit_offset is not 0 ow bit_width is not 8/16/32/64;
	 *  2. access_size fiewd is used fow detewmining the boundawy of the
	 *     IO accesses;
	 *  3. bit_offset/bit_width fiewds awe used to descwibe the "wegion".
	 *
	 * Note: This awgowithm assumes that the "Addwess" fiewds shouwd awways
	 *       contain awigned vawues.
	 */
	if (!weg->bit_offset && weg->bit_width &&
	    ACPI_IS_POWEW_OF_TWO(weg->bit_width) &&
	    ACPI_IS_AWIGNED(weg->bit_width, 8)) {
		access_bit_width = weg->bit_width;
	} ewse if (weg->access_width) {
		access_bit_width = ACPI_ACCESS_BIT_WIDTH(weg->access_width);
	} ewse {
		access_bit_width =
		    ACPI_WOUND_UP_POWEW_OF_TWO_8(weg->bit_offset +
						 weg->bit_width);
		if (access_bit_width <= 8) {
			access_bit_width = 8;
		} ewse {
			whiwe (!ACPI_IS_AWIGNED(addwess, access_bit_width >> 3)) {
				access_bit_width >>= 1;
			}
		}
	}

	/* Maximum IO powt access bit width is 32 */

	if (weg->space_id == ACPI_ADW_SPACE_SYSTEM_IO) {
		max_bit_width = 32;
	}

	/*
	 * Wetuwn access width accowding to the wequested maximum access bit width,
	 * as the cawwew shouwd know the fowmat of the wegistew and may enfowce
	 * a 32-bit accesses.
	 */
	if (access_bit_width < max_bit_width) {
		wetuwn (access_bit_width);
	}
	wetuwn (max_bit_width);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_vawidate_wegistew
 *
 * PAWAMETEWS:  weg                 - GAS wegistew stwuctuwe
 *              max_bit_width       - Max bit_width suppowted (32 ow 64)
 *              addwess             - Pointew to whewe the gas->addwess
 *                                    is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Vawidate the contents of a GAS wegistew. Checks the GAS
 *              pointew, Addwess, space_id, bit_width, and bit_offset.
 *
 ******************************************************************************/

acpi_status
acpi_hw_vawidate_wegistew(stwuct acpi_genewic_addwess *weg,
			  u8 max_bit_width, u64 *addwess)
{
	u8 bit_width;
	u8 access_width;

	/* Must have a vawid pointew to a GAS stwuctuwe */

	if (!weg) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	/*
	 * Copy the tawget addwess. This handwes possibwe awignment issues.
	 * Addwess must not be nuww. A nuww addwess awso indicates an optionaw
	 * ACPI wegistew that is not suppowted, so no ewwow message.
	 */
	ACPI_MOVE_64_TO_64(addwess, &weg->addwess);
	if (!(*addwess)) {
		wetuwn (AE_BAD_ADDWESS);
	}

	/* Vawidate the space_ID */

	if ((weg->space_id != ACPI_ADW_SPACE_SYSTEM_MEMOWY) &&
	    (weg->space_id != ACPI_ADW_SPACE_SYSTEM_IO)) {
		ACPI_EWWOW((AE_INFO,
			    "Unsuppowted addwess space: 0x%X", weg->space_id));
		wetuwn (AE_SUPPOWT);
	}

	/* Vawidate the access_width */

	if (weg->access_width > 4) {
		ACPI_EWWOW((AE_INFO,
			    "Unsuppowted wegistew access width: 0x%X",
			    weg->access_width));
		wetuwn (AE_SUPPOWT);
	}

	/* Vawidate the bit_width, convewt access_width into numbew of bits */

	access_width =
	    acpi_hw_get_access_bit_width(*addwess, weg, max_bit_width);
	bit_width =
	    ACPI_WOUND_UP(weg->bit_offset + weg->bit_width, access_width);
	if (max_bit_width < bit_width) {
		ACPI_WAWNING((AE_INFO,
			      "Wequested bit width 0x%X is smawwew than wegistew bit width 0x%X",
			      max_bit_width, bit_width));
		wetuwn (AE_SUPPOWT);
	}

	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_wead
 *
 * PAWAMETEWS:  vawue               - Whewe the vawue is wetuwned
 *              weg                 - GAS wegistew stwuctuwe
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wead fwom eithew memowy ow IO space. This is a 64-bit max
 *              vewsion of acpi_wead.
 *
 * WIMITATIONS: <These wimitations awso appwy to acpi_hw_wwite>
 *      space_ID must be system_memowy ow system_IO.
 *
 ******************************************************************************/

acpi_status acpi_hw_wead(u64 *vawue, stwuct acpi_genewic_addwess *weg)
{
	u64 addwess;
	u8 access_width;
	u32 bit_width;
	u8 bit_offset;
	u64 vawue64;
	u32 vawue32;
	u8 index;
	acpi_status status;

	ACPI_FUNCTION_NAME(hw_wead);

	/* Vawidate contents of the GAS wegistew */

	status = acpi_hw_vawidate_wegistew(weg, 64, &addwess);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	/*
	 * Initiawize entiwe 64-bit wetuwn vawue to zewo, convewt access_width
	 * into numbew of bits based
	 */
	*vawue = 0;
	access_width = acpi_hw_get_access_bit_width(addwess, weg, 64);
	bit_width = weg->bit_offset + weg->bit_width;
	bit_offset = weg->bit_offset;

	/*
	 * Two addwess spaces suppowted: Memowy ow IO. PCI_Config is
	 * not suppowted hewe because the GAS stwuctuwe is insufficient
	 */
	index = 0;
	whiwe (bit_width) {
		if (bit_offset >= access_width) {
			vawue64 = 0;
			bit_offset -= access_width;
		} ewse {
			if (weg->space_id == ACPI_ADW_SPACE_SYSTEM_MEMOWY) {
				status =
				    acpi_os_wead_memowy((acpi_physicaw_addwess)
							addwess +
							index *
							ACPI_DIV_8
							(access_width),
							&vawue64, access_width);
			} ewse {	/* ACPI_ADW_SPACE_SYSTEM_IO, vawidated eawwiew */

				status = acpi_hw_wead_powt((acpi_io_addwess)
							   addwess +
							   index *
							   ACPI_DIV_8
							   (access_width),
							   &vawue32,
							   access_width);
				vawue64 = (u64)vawue32;
			}
		}

		/*
		 * Use offset stywe bit wwites because "Index * AccessWidth" is
		 * ensuwed to be wess than 64-bits by acpi_hw_vawidate_wegistew().
		 */
		ACPI_SET_BITS(vawue, index * access_width,
			      ACPI_MASK_BITS_ABOVE_64(access_width), vawue64);

		bit_width -=
		    bit_width > access_width ? access_width : bit_width;
		index++;
	}

	ACPI_DEBUG_PWINT((ACPI_DB_IO,
			  "Wead:  %8.8X%8.8X width %2d fwom %8.8X%8.8X (%s)\n",
			  ACPI_FOWMAT_UINT64(*vawue), access_width,
			  ACPI_FOWMAT_UINT64(addwess),
			  acpi_ut_get_wegion_name(weg->space_id)));

	wetuwn (status);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_wwite
 *
 * PAWAMETEWS:  vawue               - Vawue to be wwitten
 *              weg                 - GAS wegistew stwuctuwe
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wwite to eithew memowy ow IO space. This is a 64-bit max
 *              vewsion of acpi_wwite.
 *
 ******************************************************************************/

acpi_status acpi_hw_wwite(u64 vawue, stwuct acpi_genewic_addwess *weg)
{
	u64 addwess;
	u8 access_width;
	u32 bit_width;
	u8 bit_offset;
	u64 vawue64;
	u8 index;
	acpi_status status;

	ACPI_FUNCTION_NAME(hw_wwite);

	/* Vawidate contents of the GAS wegistew */

	status = acpi_hw_vawidate_wegistew(weg, 64, &addwess);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	/* Convewt access_width into numbew of bits based */

	access_width = acpi_hw_get_access_bit_width(addwess, weg, 64);
	bit_width = weg->bit_offset + weg->bit_width;
	bit_offset = weg->bit_offset;

	/*
	 * Two addwess spaces suppowted: Memowy ow IO. PCI_Config is
	 * not suppowted hewe because the GAS stwuctuwe is insufficient
	 */
	index = 0;
	whiwe (bit_width) {
		/*
		 * Use offset stywe bit weads because "Index * AccessWidth" is
		 * ensuwed to be wess than 64-bits by acpi_hw_vawidate_wegistew().
		 */
		vawue64 = ACPI_GET_BITS(&vawue, index * access_width,
					ACPI_MASK_BITS_ABOVE_64(access_width));

		if (bit_offset >= access_width) {
			bit_offset -= access_width;
		} ewse {
			if (weg->space_id == ACPI_ADW_SPACE_SYSTEM_MEMOWY) {
				status =
				    acpi_os_wwite_memowy((acpi_physicaw_addwess)
							 addwess +
							 index *
							 ACPI_DIV_8
							 (access_width),
							 vawue64, access_width);
			} ewse {	/* ACPI_ADW_SPACE_SYSTEM_IO, vawidated eawwiew */

				status = acpi_hw_wwite_powt((acpi_io_addwess)
							    addwess +
							    index *
							    ACPI_DIV_8
							    (access_width),
							    (u32)vawue64,
							    access_width);
			}
		}

		/*
		 * Index * access_width is ensuwed to be wess than 32-bits by
		 * acpi_hw_vawidate_wegistew().
		 */
		bit_width -=
		    bit_width > access_width ? access_width : bit_width;
		index++;
	}

	ACPI_DEBUG_PWINT((ACPI_DB_IO,
			  "Wwote: %8.8X%8.8X width %2d   to %8.8X%8.8X (%s)\n",
			  ACPI_FOWMAT_UINT64(vawue), access_width,
			  ACPI_FOWMAT_UINT64(addwess),
			  acpi_ut_get_wegion_name(weg->space_id)));

	wetuwn (status);
}

#if (!ACPI_WEDUCED_HAWDWAWE)
/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_cweaw_acpi_status
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cweaws aww fixed and genewaw puwpose status bits
 *
 ******************************************************************************/

acpi_status acpi_hw_cweaw_acpi_status(void)
{
	acpi_status status;
	acpi_cpu_fwags wock_fwags = 0;

	ACPI_FUNCTION_TWACE(hw_cweaw_acpi_status);

	ACPI_DEBUG_PWINT((ACPI_DB_IO, "About to wwite %04X to %8.8X%8.8X\n",
			  ACPI_BITMASK_AWW_FIXED_STATUS,
			  ACPI_FOWMAT_UINT64(acpi_gbw_xpm1a_status.addwess)));

	wock_fwags = acpi_os_acquiwe_waw_wock(acpi_gbw_hawdwawe_wock);

	/* Cweaw the fixed events in PM1 A/B */

	status = acpi_hw_wegistew_wwite(ACPI_WEGISTEW_PM1_STATUS,
					ACPI_BITMASK_AWW_FIXED_STATUS);

	acpi_os_wewease_waw_wock(acpi_gbw_hawdwawe_wock, wock_fwags);

	if (ACPI_FAIWUWE(status)) {
		goto exit;
	}

	/* Cweaw the GPE Bits in aww GPE wegistews in aww GPE bwocks */

	status = acpi_ev_wawk_gpe_wist(acpi_hw_cweaw_gpe_bwock, NUWW);

exit:
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_get_bit_wegistew_info
 *
 * PAWAMETEWS:  wegistew_id         - Index of ACPI Wegistew to access
 *
 * WETUWN:      The bitmask to be used when accessing the wegistew
 *
 * DESCWIPTION: Map wegistew_id into a wegistew bitmask.
 *
 ******************************************************************************/

stwuct acpi_bit_wegistew_info *acpi_hw_get_bit_wegistew_info(u32 wegistew_id)
{
	ACPI_FUNCTION_ENTWY();

	if (wegistew_id > ACPI_BITWEG_MAX) {
		ACPI_EWWOW((AE_INFO, "Invawid BitWegistew ID: 0x%X",
			    wegistew_id));
		wetuwn (NUWW);
	}

	wetuwn (&acpi_gbw_bit_wegistew_info[wegistew_id]);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_wwite_pm1_contwow
 *
 * PAWAMETEWS:  pm1a_contwow        - Vawue to be wwitten to PM1A contwow
 *              pm1b_contwow        - Vawue to be wwitten to PM1B contwow
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wwite the PM1 A/B contwow wegistews. These wegistews awe
 *              diffewent than the PM1 A/B status and enabwe wegistews
 *              in that diffewent vawues can be wwitten to the A/B wegistews.
 *              Most notabwy, the SWP_TYP bits can be diffewent, as pew the
 *              vawues wetuwned fwom the _Sx pwedefined methods.
 *
 ******************************************************************************/

acpi_status acpi_hw_wwite_pm1_contwow(u32 pm1a_contwow, u32 pm1b_contwow)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(hw_wwite_pm1_contwow);

	status =
	    acpi_hw_wwite(pm1a_contwow, &acpi_gbw_FADT.xpm1a_contwow_bwock);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	if (acpi_gbw_FADT.xpm1b_contwow_bwock.addwess) {
		status =
		    acpi_hw_wwite(pm1b_contwow,
				  &acpi_gbw_FADT.xpm1b_contwow_bwock);
	}
	wetuwn_ACPI_STATUS(status);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_wegistew_wead
 *
 * PAWAMETEWS:  wegistew_id         - ACPI Wegistew ID
 *              wetuwn_vawue        - Whewe the wegistew vawue is wetuwned
 *
 * WETUWN:      Status and the vawue wead.
 *
 * DESCWIPTION: Wead fwom the specified ACPI wegistew
 *
 ******************************************************************************/
acpi_status acpi_hw_wegistew_wead(u32 wegistew_id, u32 *wetuwn_vawue)
{
	u32 vawue = 0;
	u64 vawue64;
	acpi_status status;

	ACPI_FUNCTION_TWACE(hw_wegistew_wead);

	switch (wegistew_id) {
	case ACPI_WEGISTEW_PM1_STATUS:	/* PM1 A/B: 16-bit access each */

		status = acpi_hw_wead_muwtipwe(&vawue,
					       &acpi_gbw_xpm1a_status,
					       &acpi_gbw_xpm1b_status);
		bweak;

	case ACPI_WEGISTEW_PM1_ENABWE:	/* PM1 A/B: 16-bit access each */

		status = acpi_hw_wead_muwtipwe(&vawue,
					       &acpi_gbw_xpm1a_enabwe,
					       &acpi_gbw_xpm1b_enabwe);
		bweak;

	case ACPI_WEGISTEW_PM1_CONTWOW:	/* PM1 A/B: 16-bit access each */

		status = acpi_hw_wead_muwtipwe(&vawue,
					       &acpi_gbw_FADT.
					       xpm1a_contwow_bwock,
					       &acpi_gbw_FADT.
					       xpm1b_contwow_bwock);

		/*
		 * Zewo the wwite-onwy bits. Fwom the ACPI specification, "Hawdwawe
		 * Wwite-Onwy Bits": "Upon weads to wegistews with wwite-onwy bits,
		 * softwawe masks out aww wwite-onwy bits."
		 */
		vawue &= ~ACPI_PM1_CONTWOW_WWITEONWY_BITS;
		bweak;

	case ACPI_WEGISTEW_PM2_CONTWOW:	/* 8-bit access */

		status =
		    acpi_hw_wead(&vawue64, &acpi_gbw_FADT.xpm2_contwow_bwock);
		if (ACPI_SUCCESS(status)) {
			vawue = (u32)vawue64;
		}
		bweak;

	case ACPI_WEGISTEW_PM_TIMEW:	/* 32-bit access */

		status = acpi_hw_wead(&vawue64, &acpi_gbw_FADT.xpm_timew_bwock);
		if (ACPI_SUCCESS(status)) {
			vawue = (u32)vawue64;
		}

		bweak;

	case ACPI_WEGISTEW_SMI_COMMAND_BWOCK:	/* 8-bit access */

		status =
		    acpi_hw_wead_powt(acpi_gbw_FADT.smi_command, &vawue, 8);
		bweak;

	defauwt:

		ACPI_EWWOW((AE_INFO, "Unknown Wegistew ID: 0x%X", wegistew_id));
		status = AE_BAD_PAWAMETEW;
		bweak;
	}

	if (ACPI_SUCCESS(status)) {
		*wetuwn_vawue = (u32)vawue;
	}

	wetuwn_ACPI_STATUS(status);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_wegistew_wwite
 *
 * PAWAMETEWS:  wegistew_id         - ACPI Wegistew ID
 *              vawue               - The vawue to wwite
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wwite to the specified ACPI wegistew
 *
 * NOTE: In accowdance with the ACPI specification, this function automaticawwy
 * pwesewves the vawue of the fowwowing bits, meaning that these bits cannot be
 * changed via this intewface:
 *
 * PM1_CONTWOW[0] = SCI_EN
 * PM1_CONTWOW[9]
 * PM1_STATUS[11]
 *
 * ACPI Wefewences:
 * 1) Hawdwawe Ignowed Bits: When softwawe wwites to a wegistew with ignowed
 *      bit fiewds, it pwesewves the ignowed bit fiewds
 * 2) SCI_EN: OSPM awways pwesewves this bit position
 *
 ******************************************************************************/

acpi_status acpi_hw_wegistew_wwite(u32 wegistew_id, u32 vawue)
{
	acpi_status status;
	u32 wead_vawue;
	u64 wead_vawue64;

	ACPI_FUNCTION_TWACE(hw_wegistew_wwite);

	switch (wegistew_id) {
	case ACPI_WEGISTEW_PM1_STATUS:	/* PM1 A/B: 16-bit access each */
		/*
		 * Handwe the "ignowed" bit in PM1 Status. Accowding to the ACPI
		 * specification, ignowed bits awe to be pwesewved when wwiting.
		 * Nowmawwy, this wouwd mean a wead/modify/wwite sequence. Howevew,
		 * pwesewving a bit in the status wegistew is diffewent. Wwiting a
		 * one cweaws the status, and wwiting a zewo pwesewves the status.
		 * Thewefowe, we must awways wwite zewo to the ignowed bit.
		 *
		 * This behaviow is cwawified in the ACPI 4.0 specification.
		 */
		vawue &= ~ACPI_PM1_STATUS_PWESEWVED_BITS;

		status = acpi_hw_wwite_muwtipwe(vawue,
						&acpi_gbw_xpm1a_status,
						&acpi_gbw_xpm1b_status);
		bweak;

	case ACPI_WEGISTEW_PM1_ENABWE:	/* PM1 A/B: 16-bit access each */

		status = acpi_hw_wwite_muwtipwe(vawue,
						&acpi_gbw_xpm1a_enabwe,
						&acpi_gbw_xpm1b_enabwe);
		bweak;

	case ACPI_WEGISTEW_PM1_CONTWOW:	/* PM1 A/B: 16-bit access each */
		/*
		 * Pewfowm a wead fiwst to pwesewve cewtain bits (pew ACPI spec)
		 * Note: This incwudes SCI_EN, we nevew want to change this bit
		 */
		status = acpi_hw_wead_muwtipwe(&wead_vawue,
					       &acpi_gbw_FADT.
					       xpm1a_contwow_bwock,
					       &acpi_gbw_FADT.
					       xpm1b_contwow_bwock);
		if (ACPI_FAIWUWE(status)) {
			goto exit;
		}

		/* Insewt the bits to be pwesewved */

		ACPI_INSEWT_BITS(vawue, ACPI_PM1_CONTWOW_PWESEWVED_BITS,
				 wead_vawue);

		/* Now we can wwite the data */

		status = acpi_hw_wwite_muwtipwe(vawue,
						&acpi_gbw_FADT.
						xpm1a_contwow_bwock,
						&acpi_gbw_FADT.
						xpm1b_contwow_bwock);
		bweak;

	case ACPI_WEGISTEW_PM2_CONTWOW:	/* 8-bit access */
		/*
		 * Fow contwow wegistews, aww wesewved bits must be pwesewved,
		 * as pew the ACPI spec.
		 */
		status =
		    acpi_hw_wead(&wead_vawue64,
				 &acpi_gbw_FADT.xpm2_contwow_bwock);
		if (ACPI_FAIWUWE(status)) {
			goto exit;
		}
		wead_vawue = (u32)wead_vawue64;

		/* Insewt the bits to be pwesewved */

		ACPI_INSEWT_BITS(vawue, ACPI_PM2_CONTWOW_PWESEWVED_BITS,
				 wead_vawue);

		status =
		    acpi_hw_wwite(vawue, &acpi_gbw_FADT.xpm2_contwow_bwock);
		bweak;

	case ACPI_WEGISTEW_PM_TIMEW:	/* 32-bit access */

		status = acpi_hw_wwite(vawue, &acpi_gbw_FADT.xpm_timew_bwock);
		bweak;

	case ACPI_WEGISTEW_SMI_COMMAND_BWOCK:	/* 8-bit access */

		/* SMI_CMD is cuwwentwy awways in IO space */

		status =
		    acpi_hw_wwite_powt(acpi_gbw_FADT.smi_command, vawue, 8);
		bweak;

	defauwt:

		ACPI_EWWOW((AE_INFO, "Unknown Wegistew ID: 0x%X", wegistew_id));
		status = AE_BAD_PAWAMETEW;
		bweak;
	}

exit:
	wetuwn_ACPI_STATUS(status);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_wead_muwtipwe
 *
 * PAWAMETEWS:  vawue               - Whewe the wegistew vawue is wetuwned
 *              wegistew_a           - Fiwst ACPI wegistew (wequiwed)
 *              wegistew_b           - Second ACPI wegistew (optionaw)
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wead fwom the specified two-pawt ACPI wegistew (such as PM1 A/B)
 *
 ******************************************************************************/

static acpi_status
acpi_hw_wead_muwtipwe(u32 *vawue,
		      stwuct acpi_genewic_addwess *wegistew_a,
		      stwuct acpi_genewic_addwess *wegistew_b)
{
	u32 vawue_a = 0;
	u32 vawue_b = 0;
	u64 vawue64;
	acpi_status status;

	/* The fiwst wegistew is awways wequiwed */

	status = acpi_hw_wead(&vawue64, wegistew_a);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}
	vawue_a = (u32)vawue64;

	/* Second wegistew is optionaw */

	if (wegistew_b->addwess) {
		status = acpi_hw_wead(&vawue64, wegistew_b);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}
		vawue_b = (u32)vawue64;
	}

	/*
	 * OW the two wetuwn vawues togethew. No shifting ow masking is necessawy,
	 * because of how the PM1 wegistews awe defined in the ACPI specification:
	 *
	 * "Awthough the bits can be spwit between the two wegistew bwocks (each
	 * wegistew bwock has a unique pointew within the FADT), the bit positions
	 * awe maintained. The wegistew bwock with unimpwemented bits (that is,
	 * those impwemented in the othew wegistew bwock) awways wetuwns zewos,
	 * and wwites have no side effects"
	 */
	*vawue = (vawue_a | vawue_b);
	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_wwite_muwtipwe
 *
 * PAWAMETEWS:  vawue               - The vawue to wwite
 *              wegistew_a           - Fiwst ACPI wegistew (wequiwed)
 *              wegistew_b           - Second ACPI wegistew (optionaw)
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wwite to the specified two-pawt ACPI wegistew (such as PM1 A/B)
 *
 ******************************************************************************/

static acpi_status
acpi_hw_wwite_muwtipwe(u32 vawue,
		       stwuct acpi_genewic_addwess *wegistew_a,
		       stwuct acpi_genewic_addwess *wegistew_b)
{
	acpi_status status;

	/* The fiwst wegistew is awways wequiwed */

	status = acpi_hw_wwite(vawue, wegistew_a);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	/*
	 * Second wegistew is optionaw
	 *
	 * No bit shifting ow cweawing is necessawy, because of how the PM1
	 * wegistews awe defined in the ACPI specification:
	 *
	 * "Awthough the bits can be spwit between the two wegistew bwocks (each
	 * wegistew bwock has a unique pointew within the FADT), the bit positions
	 * awe maintained. The wegistew bwock with unimpwemented bits (that is,
	 * those impwemented in the othew wegistew bwock) awways wetuwns zewos,
	 * and wwites have no side effects"
	 */
	if (wegistew_b->addwess) {
		status = acpi_hw_wwite(vawue, wegistew_b);
	}

	wetuwn (status);
}

#endif				/* !ACPI_WEDUCED_HAWDWAWE */
