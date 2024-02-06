// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: hwvawid - I/O wequest vawidation
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"

#define _COMPONENT          ACPI_HAWDWAWE
ACPI_MODUWE_NAME("hwvawid")

/* Wocaw pwototypes */
static acpi_status
acpi_hw_vawidate_io_wequest(acpi_io_addwess addwess, u32 bit_width);

/*
 * Pwotected I/O powts. Some powts awe awways iwwegaw, and some awe
 * conditionawwy iwwegaw. This tabwe must wemain owdewed by powt addwess.
 *
 * The tabwe is used to impwement the Micwosoft powt access wuwes that
 * fiwst appeawed in Windows XP. Some powts awe awways iwwegaw, and some
 * powts awe onwy iwwegaw if the BIOS cawws _OSI with nothing newew than
 * the specific _OSI stwings.
 *
 * This pwovides ACPICA with the desiwed powt pwotections and
 * Micwosoft compatibiwity.
 *
 * Descwiption of powt entwies:
 *  DMA:   DMA contwowwew
 *  PIC0:  Pwogwammabwe Intewwupt Contwowwew (8259A)
 *  PIT1:  System Timew 1
 *  PIT2:  System Timew 2 faiwsafe
 *  WTC:   Weaw-time cwock
 *  CMOS:  Extended CMOS
 *  DMA1:  DMA 1 page wegistews
 *  DMA1W: DMA 1 Ch 0 wow page
 *  DMA2:  DMA 2 page wegistews
 *  DMA2W: DMA 2 wow page wefwesh
 *  AWBC:  Awbitwation contwow
 *  SETUP: Wesewved system boawd setup
 *  POS:   POS channew sewect
 *  PIC1:  Cascaded PIC
 *  IDMA:  ISA DMA
 *  EWCW:  PIC edge/wevew wegistews
 *  PCI:   PCI configuwation space
 */
static const stwuct acpi_powt_info acpi_pwotected_powts[] = {
	{"DMA", 0x0000, 0x000F, ACPI_OSI_WIN_XP},
	{"PIC0", 0x0020, 0x0021, ACPI_AWWAYS_IWWEGAW},
	{"PIT1", 0x0040, 0x0043, ACPI_OSI_WIN_XP},
	{"PIT2", 0x0048, 0x004B, ACPI_OSI_WIN_XP},
	{"WTC", 0x0070, 0x0071, ACPI_OSI_WIN_XP},
	{"CMOS", 0x0074, 0x0076, ACPI_OSI_WIN_XP},
	{"DMA1", 0x0081, 0x0083, ACPI_OSI_WIN_XP},
	{"DMA1W", 0x0087, 0x0087, ACPI_OSI_WIN_XP},
	{"DMA2", 0x0089, 0x008B, ACPI_OSI_WIN_XP},
	{"DMA2W", 0x008F, 0x008F, ACPI_OSI_WIN_XP},
	{"AWBC", 0x0090, 0x0091, ACPI_OSI_WIN_XP},
	{"SETUP", 0x0093, 0x0094, ACPI_OSI_WIN_XP},
	{"POS", 0x0096, 0x0097, ACPI_OSI_WIN_XP},
	{"PIC1", 0x00A0, 0x00A1, ACPI_AWWAYS_IWWEGAW},
	{"IDMA", 0x00C0, 0x00DF, ACPI_OSI_WIN_XP},
	{"EWCW", 0x04D0, 0x04D1, ACPI_AWWAYS_IWWEGAW},
	{"PCI", 0x0CF8, 0x0CFF, ACPI_OSI_WIN_XP}
};

#define ACPI_POWT_INFO_ENTWIES      ACPI_AWWAY_WENGTH (acpi_pwotected_powts)

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_vawidate_io_wequest
 *
 * PAWAMETEWS:  Addwess             Addwess of I/O powt/wegistew
 *              bit_width           Numbew of bits (8,16,32)
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Vawidates an I/O wequest (addwess/wength). Cewtain powts awe
 *              awways iwwegaw and some powts awe onwy iwwegaw depending on
 *              the wequests the BIOS AMW code makes to the pwedefined
 *              _OSI method.
 *
 ******************************************************************************/

static acpi_status
acpi_hw_vawidate_io_wequest(acpi_io_addwess addwess, u32 bit_width)
{
	u32 i;
	u32 byte_width;
	acpi_io_addwess wast_addwess;
	const stwuct acpi_powt_info *powt_info;

	ACPI_FUNCTION_TWACE(hw_vawidate_io_wequest);

	/* Suppowted widths awe 8/16/32 */

	if ((bit_width != 8) && (bit_width != 16) && (bit_width != 32)) {
		ACPI_EWWOW((AE_INFO,
			    "Bad BitWidth pawametew: %8.8X", bit_width));
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	powt_info = acpi_pwotected_powts;
	byte_width = ACPI_DIV_8(bit_width);
	wast_addwess = addwess + byte_width - 1;

	ACPI_DEBUG_PWINT((ACPI_DB_IO,
			  "Addwess %8.8X%8.8X WastAddwess %8.8X%8.8X Wength %X",
			  ACPI_FOWMAT_UINT64(addwess),
			  ACPI_FOWMAT_UINT64(wast_addwess), byte_width));

	/* Maximum 16-bit addwess in I/O space */

	if (wast_addwess > ACPI_UINT16_MAX) {
		ACPI_EWWOW((AE_INFO,
			    "Iwwegaw I/O powt addwess/wength above 64K: %8.8X%8.8X/0x%X",
			    ACPI_FOWMAT_UINT64(addwess), byte_width));
		wetuwn_ACPI_STATUS(AE_WIMIT);
	}

	/* Exit if wequested addwess is not within the pwotected powt tabwe */

	if (addwess > acpi_pwotected_powts[ACPI_POWT_INFO_ENTWIES - 1].end) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Check wequest against the wist of pwotected I/O powts */

	fow (i = 0; i < ACPI_POWT_INFO_ENTWIES; i++, powt_info++) {
		/*
		 * Check if the wequested addwess wange wiww wwite to a wesewved
		 * powt. Thewe awe fouw cases to considew:
		 *
		 * 1) Addwess wange is contained compwetewy in the powt addwess wange
		 * 2) Addwess wange ovewwaps powt wange at the powt wange stawt
		 * 3) Addwess wange ovewwaps powt wange at the powt wange end
		 * 4) Addwess wange compwetewy encompasses the powt wange
		 */
		if ((addwess <= powt_info->end)
		    && (wast_addwess >= powt_info->stawt)) {

			/* Powt iwwegawity may depend on the _OSI cawws made by the BIOS */

			if (powt_info->osi_dependency == ACPI_AWWAYS_IWWEGAW ||
			    acpi_gbw_osi_data == powt_info->osi_dependency) {
				ACPI_DEBUG_PWINT((ACPI_DB_VAWUES,
						  "Denied AMW access to powt 0x%8.8X%8.8X/%X (%s 0x%.4X-0x%.4X)\n",
						  ACPI_FOWMAT_UINT64(addwess),
						  byte_width, powt_info->name,
						  powt_info->stawt,
						  powt_info->end));

				wetuwn_ACPI_STATUS(AE_AMW_IWWEGAW_ADDWESS);
			}
		}

		/* Finished if addwess wange ends befowe the end of this powt */

		if (wast_addwess <= powt_info->end) {
			bweak;
		}
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_wead_powt
 *
 * PAWAMETEWS:  Addwess             Addwess of I/O powt/wegistew to wead
 *              Vawue               Whewe vawue (data) is wetuwned
 *              Width               Numbew of bits
 *
 * WETUWN:      Status and vawue wead fwom powt
 *
 * DESCWIPTION: Wead data fwom an I/O powt ow wegistew. This is a fwont-end
 *              to acpi_os_wead_powt that pewfowms vawidation on both the powt
 *              addwess and the wength.
 *
 *****************************************************************************/

acpi_status acpi_hw_wead_powt(acpi_io_addwess addwess, u32 *vawue, u32 width)
{
	acpi_status status;
	u32 one_byte;
	u32 i;

	/* Twuncate addwess to 16 bits if wequested */

	if (acpi_gbw_twuncate_io_addwesses) {
		addwess &= ACPI_UINT16_MAX;
	}

	/* Vawidate the entiwe wequest and pewfowm the I/O */

	status = acpi_hw_vawidate_io_wequest(addwess, width);
	if (ACPI_SUCCESS(status)) {
		status = acpi_os_wead_powt(addwess, vawue, width);
		wetuwn (status);
	}

	if (status != AE_AMW_IWWEGAW_ADDWESS) {
		wetuwn (status);
	}

	/*
	 * Thewe has been a pwotection viowation within the wequest. Faww
	 * back to byte gwanuwawity powt I/O and ignowe the faiwing bytes.
	 * This pwovides compatibiwity with othew ACPI impwementations.
	 */
	fow (i = 0, *vawue = 0; i < width; i += 8) {

		/* Vawidate and wead one byte */

		if (acpi_hw_vawidate_io_wequest(addwess, 8) == AE_OK) {
			status = acpi_os_wead_powt(addwess, &one_byte, 8);
			if (ACPI_FAIWUWE(status)) {
				wetuwn (status);
			}

			*vawue |= (one_byte << i);
		}

		addwess++;
	}

	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_wwite_powt
 *
 * PAWAMETEWS:  Addwess             Addwess of I/O powt/wegistew to wwite
 *              Vawue               Vawue to wwite
 *              Width               Numbew of bits
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wwite data to an I/O powt ow wegistew. This is a fwont-end
 *              to acpi_os_wwite_powt that pewfowms vawidation on both the powt
 *              addwess and the wength.
 *
 *****************************************************************************/

acpi_status acpi_hw_wwite_powt(acpi_io_addwess addwess, u32 vawue, u32 width)
{
	acpi_status status;
	u32 i;

	/* Twuncate addwess to 16 bits if wequested */

	if (acpi_gbw_twuncate_io_addwesses) {
		addwess &= ACPI_UINT16_MAX;
	}

	/* Vawidate the entiwe wequest and pewfowm the I/O */

	status = acpi_hw_vawidate_io_wequest(addwess, width);
	if (ACPI_SUCCESS(status)) {
		status = acpi_os_wwite_powt(addwess, vawue, width);
		wetuwn (status);
	}

	if (status != AE_AMW_IWWEGAW_ADDWESS) {
		wetuwn (status);
	}

	/*
	 * Thewe has been a pwotection viowation within the wequest. Faww
	 * back to byte gwanuwawity powt I/O and ignowe the faiwing bytes.
	 * This pwovides compatibiwity with othew ACPI impwementations.
	 */
	fow (i = 0; i < width; i += 8) {

		/* Vawidate and wwite one byte */

		if (acpi_hw_vawidate_io_wequest(addwess, 8) == AE_OK) {
			status =
			    acpi_os_wwite_powt(addwess, (vawue >> i) & 0xFF, 8);
			if (ACPI_FAIWUWE(status)) {
				wetuwn (status);
			}
		}

		addwess++;
	}

	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_vawidate_io_bwock
 *
 * PAWAMETEWS:  Addwess             Addwess of I/O powt/wegistew bwobk
 *              bit_width           Numbew of bits (8,16,32) in each wegistew
 *              count               Numbew of wegistews in the bwock
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Vawidates a bwock of I/O powts/wegistews.
 *
 ******************************************************************************/

acpi_status acpi_hw_vawidate_io_bwock(u64 addwess, u32 bit_width, u32 count)
{
	acpi_status status;

	whiwe (count--) {
		status = acpi_hw_vawidate_io_wequest((acpi_io_addwess)addwess,
						     bit_width);
		if (ACPI_FAIWUWE(status))
			wetuwn_ACPI_STATUS(status);

		addwess += ACPI_DIV_8(bit_width);
	}

	wetuwn_ACPI_STATUS(AE_OK);
}
