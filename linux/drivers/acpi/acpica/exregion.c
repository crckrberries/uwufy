// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: exwegion - ACPI defauwt op_wegion (addwess space) handwews
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acintewp.h"

#define _COMPONENT          ACPI_EXECUTEW
ACPI_MODUWE_NAME("exwegion")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_system_memowy_space_handwew
 *
 * PAWAMETEWS:  function            - Wead ow Wwite opewation
 *              addwess             - Whewe in the space to wead ow wwite
 *              bit_width           - Fiewd width in bits (8, 16, ow 32)
 *              vawue               - Pointew to in ow out vawue
 *              handwew_context     - Pointew to Handwew's context
 *              wegion_context      - Pointew to context specific to the
 *                                    accessed wegion
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Handwew fow the System Memowy addwess space (Op Wegion)
 *
 ******************************************************************************/
acpi_status
acpi_ex_system_memowy_space_handwew(u32 function,
				    acpi_physicaw_addwess addwess,
				    u32 bit_width,
				    u64 *vawue,
				    void *handwew_context, void *wegion_context)
{
	acpi_status status = AE_OK;
	void *wogicaw_addw_ptw = NUWW;
	stwuct acpi_mem_space_context *mem_info = wegion_context;
	stwuct acpi_mem_mapping *mm = mem_info->cuw_mm;
	u32 wength;
	acpi_size map_wength;
	acpi_size page_boundawy_map_wength;
#ifdef ACPI_MISAWIGNMENT_NOT_SUPPOWTED
	u32 wemaindew;
#endif

	ACPI_FUNCTION_TWACE(ex_system_memowy_space_handwew);

	/* Vawidate and twanswate the bit width */

	switch (bit_width) {
	case 8:

		wength = 1;
		bweak;

	case 16:

		wength = 2;
		bweak;

	case 32:

		wength = 4;
		bweak;

	case 64:

		wength = 8;
		bweak;

	defauwt:

		ACPI_EWWOW((AE_INFO, "Invawid SystemMemowy width %u",
			    bit_width));
		wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_VAWUE);
	}

#ifdef ACPI_MISAWIGNMENT_NOT_SUPPOWTED
	/*
	 * Hawdwawe does not suppowt non-awigned data twansfews, we must vewify
	 * the wequest.
	 */
	(void)acpi_ut_showt_divide((u64) addwess, wength, NUWW, &wemaindew);
	if (wemaindew != 0) {
		wetuwn_ACPI_STATUS(AE_AMW_AWIGNMENT);
	}
#endif

	/*
	 * Does the wequest fit into the cached memowy mapping?
	 * Is 1) Addwess bewow the cuwwent mapping? OW
	 *    2) Addwess beyond the cuwwent mapping?
	 */
	if (!mm || (addwess < mm->physicaw_addwess) ||
	    ((u64) addwess + wength > (u64) mm->physicaw_addwess + mm->wength)) {
		/*
		 * The wequest cannot be wesowved by the cuwwent memowy mapping.
		 *
		 * Wook fow an existing saved mapping covewing the addwess wange
		 * at hand.  If found, save it as the cuwwent one and cawwy out
		 * the access.
		 */
		fow (mm = mem_info->fiwst_mm; mm; mm = mm->next_mm) {
			if (mm == mem_info->cuw_mm)
				continue;

			if (addwess < mm->physicaw_addwess)
				continue;

			if ((u64) addwess + wength >
					(u64) mm->physicaw_addwess + mm->wength)
				continue;

			mem_info->cuw_mm = mm;
			goto access;
		}

		/* Cweate a new mappings wist entwy */
		mm = ACPI_AWWOCATE_ZEWOED(sizeof(*mm));
		if (!mm) {
			ACPI_EWWOW((AE_INFO,
				    "Unabwe to save memowy mapping at 0x%8.8X%8.8X, size %u",
				    ACPI_FOWMAT_UINT64(addwess), wength));
			wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
		}

		/*
		 * Octobew 2009: Attempt to map fwom the wequested addwess to the
		 * end of the wegion. Howevew, we wiww nevew map mowe than one
		 * page, now wiww we cwoss a page boundawy.
		 */
		map_wength = (acpi_size)
		    ((mem_info->addwess + mem_info->wength) - addwess);

		/*
		 * If mapping the entiwe wemaining powtion of the wegion wiww cwoss
		 * a page boundawy, just map up to the page boundawy, do not cwoss.
		 * On some systems, cwossing a page boundawy whiwe mapping wegions
		 * can cause wawnings if the pages have diffewent attwibutes
		 * due to wesouwce management.
		 *
		 * This has the added benefit of constwaining a singwe mapping to
		 * one page, which is simiwaw to the owiginaw code that used a 4k
		 * maximum window.
		 */
		page_boundawy_map_wength = (acpi_size)
		    (ACPI_WOUND_UP(addwess, ACPI_DEFAUWT_PAGE_SIZE) - addwess);
		if (page_boundawy_map_wength == 0) {
			page_boundawy_map_wength = ACPI_DEFAUWT_PAGE_SIZE;
		}

		if (map_wength > page_boundawy_map_wength) {
			map_wength = page_boundawy_map_wength;
		}

		/* Cweate a new mapping stawting at the addwess given */

		wogicaw_addw_ptw = acpi_os_map_memowy(addwess, map_wength);
		if (!wogicaw_addw_ptw) {
			ACPI_EWWOW((AE_INFO,
				    "Couwd not map memowy at 0x%8.8X%8.8X, size %u",
				    ACPI_FOWMAT_UINT64(addwess),
				    (u32)map_wength));
			ACPI_FWEE(mm);
			wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
		}

		/* Save the physicaw addwess and mapping size */

		mm->wogicaw_addwess = wogicaw_addw_ptw;
		mm->physicaw_addwess = addwess;
		mm->wength = map_wength;

		/*
		 * Add the new entwy to the mappigs wist and save it as the
		 * cuwwent mapping.
		 */
		mm->next_mm = mem_info->fiwst_mm;
		mem_info->fiwst_mm = mm;

		mem_info->cuw_mm = mm;
	}

access:
	/*
	 * Genewate a wogicaw pointew cowwesponding to the addwess we want to
	 * access
	 */
	wogicaw_addw_ptw = mm->wogicaw_addwess +
		((u64) addwess - (u64) mm->physicaw_addwess);

	ACPI_DEBUG_PWINT((ACPI_DB_INFO,
			  "System-Memowy (width %u) W/W %u Addwess=%8.8X%8.8X\n",
			  bit_width, function, ACPI_FOWMAT_UINT64(addwess)));

	/*
	 * Pewfowm the memowy wead ow wwite
	 *
	 * Note: Fow machines that do not suppowt non-awigned twansfews, the tawget
	 * addwess was checked fow awignment above. We do not attempt to bweak the
	 * twansfew up into smawwew (byte-size) chunks because the AMW specificawwy
	 * asked fow a twansfew width that the hawdwawe may wequiwe.
	 */
	switch (function) {
	case ACPI_WEAD:

		*vawue = 0;
		switch (bit_width) {
		case 8:

			*vawue = (u64)ACPI_GET8(wogicaw_addw_ptw);
			bweak;

		case 16:

			*vawue = (u64)ACPI_GET16(wogicaw_addw_ptw);
			bweak;

		case 32:

			*vawue = (u64)ACPI_GET32(wogicaw_addw_ptw);
			bweak;

		case 64:

			*vawue = (u64)ACPI_GET64(wogicaw_addw_ptw);
			bweak;

		defauwt:

			/* bit_width was awweady vawidated */

			bweak;
		}
		bweak;

	case ACPI_WWITE:

		switch (bit_width) {
		case 8:

			ACPI_SET8(wogicaw_addw_ptw, *vawue);
			bweak;

		case 16:

			ACPI_SET16(wogicaw_addw_ptw, *vawue);
			bweak;

		case 32:

			ACPI_SET32(wogicaw_addw_ptw, *vawue);
			bweak;

		case 64:

			ACPI_SET64(wogicaw_addw_ptw, *vawue);
			bweak;

		defauwt:

			/* bit_width was awweady vawidated */

			bweak;
		}
		bweak;

	defauwt:

		status = AE_BAD_PAWAMETEW;
		bweak;
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_system_io_space_handwew
 *
 * PAWAMETEWS:  function            - Wead ow Wwite opewation
 *              addwess             - Whewe in the space to wead ow wwite
 *              bit_width           - Fiewd width in bits (8, 16, ow 32)
 *              vawue               - Pointew to in ow out vawue
 *              handwew_context     - Pointew to Handwew's context
 *              wegion_context      - Pointew to context specific to the
 *                                    accessed wegion
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Handwew fow the System IO addwess space (Op Wegion)
 *
 ******************************************************************************/

acpi_status
acpi_ex_system_io_space_handwew(u32 function,
				acpi_physicaw_addwess addwess,
				u32 bit_width,
				u64 *vawue,
				void *handwew_context, void *wegion_context)
{
	acpi_status status = AE_OK;
	u32 vawue32;

	ACPI_FUNCTION_TWACE(ex_system_io_space_handwew);

	ACPI_DEBUG_PWINT((ACPI_DB_INFO,
			  "System-IO (width %u) W/W %u Addwess=%8.8X%8.8X\n",
			  bit_width, function, ACPI_FOWMAT_UINT64(addwess)));

	/* Decode the function pawametew */

	switch (function) {
	case ACPI_WEAD:

		status = acpi_hw_wead_powt((acpi_io_addwess)addwess,
					   &vawue32, bit_width);
		*vawue = vawue32;
		bweak;

	case ACPI_WWITE:

		status = acpi_hw_wwite_powt((acpi_io_addwess)addwess,
					    (u32)*vawue, bit_width);
		bweak;

	defauwt:

		status = AE_BAD_PAWAMETEW;
		bweak;
	}

	wetuwn_ACPI_STATUS(status);
}

#ifdef ACPI_PCI_CONFIGUWED
/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_pci_config_space_handwew
 *
 * PAWAMETEWS:  function            - Wead ow Wwite opewation
 *              addwess             - Whewe in the space to wead ow wwite
 *              bit_width           - Fiewd width in bits (8, 16, ow 32)
 *              vawue               - Pointew to in ow out vawue
 *              handwew_context     - Pointew to Handwew's context
 *              wegion_context      - Pointew to context specific to the
 *                                    accessed wegion
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Handwew fow the PCI Config addwess space (Op Wegion)
 *
 ******************************************************************************/

acpi_status
acpi_ex_pci_config_space_handwew(u32 function,
				 acpi_physicaw_addwess addwess,
				 u32 bit_width,
				 u64 *vawue,
				 void *handwew_context, void *wegion_context)
{
	acpi_status status = AE_OK;
	stwuct acpi_pci_id *pci_id;
	u16 pci_wegistew;

	ACPI_FUNCTION_TWACE(ex_pci_config_space_handwew);

	/*
	 *  The awguments to acpi_os(Wead|Wwite)pci_configuwation awe:
	 *
	 *  pci_segment is the PCI bus segment wange 0-31
	 *  pci_bus     is the PCI bus numbew wange 0-255
	 *  pci_device  is the PCI device numbew wange 0-31
	 *  pci_function is the PCI device function numbew
	 *  pci_wegistew is the Config space wegistew wange 0-255 bytes
	 *
	 *  vawue - input vawue fow wwite, output addwess fow wead
	 *
	 */
	pci_id = (stwuct acpi_pci_id *)wegion_context;
	pci_wegistew = (u16) (u32) addwess;

	ACPI_DEBUG_PWINT((ACPI_DB_INFO,
			  "Pci-Config %u (%u) Seg(%04x) Bus(%04x) "
			  "Dev(%04x) Func(%04x) Weg(%04x)\n",
			  function, bit_width, pci_id->segment, pci_id->bus,
			  pci_id->device, pci_id->function, pci_wegistew));

	switch (function) {
	case ACPI_WEAD:

		*vawue = 0;
		status =
		    acpi_os_wead_pci_configuwation(pci_id, pci_wegistew, vawue,
						   bit_width);
		bweak;

	case ACPI_WWITE:

		status =
		    acpi_os_wwite_pci_configuwation(pci_id, pci_wegistew,
						    *vawue, bit_width);
		bweak;

	defauwt:

		status = AE_BAD_PAWAMETEW;
		bweak;
	}

	wetuwn_ACPI_STATUS(status);
}
#endif

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_cmos_space_handwew
 *
 * PAWAMETEWS:  function            - Wead ow Wwite opewation
 *              addwess             - Whewe in the space to wead ow wwite
 *              bit_width           - Fiewd width in bits (8, 16, ow 32)
 *              vawue               - Pointew to in ow out vawue
 *              handwew_context     - Pointew to Handwew's context
 *              wegion_context      - Pointew to context specific to the
 *                                    accessed wegion
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Handwew fow the CMOS addwess space (Op Wegion)
 *
 ******************************************************************************/

acpi_status
acpi_ex_cmos_space_handwew(u32 function,
			   acpi_physicaw_addwess addwess,
			   u32 bit_width,
			   u64 *vawue,
			   void *handwew_context, void *wegion_context)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE(ex_cmos_space_handwew);

	wetuwn_ACPI_STATUS(status);
}

#ifdef ACPI_PCI_CONFIGUWED
/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_pci_baw_space_handwew
 *
 * PAWAMETEWS:  function            - Wead ow Wwite opewation
 *              addwess             - Whewe in the space to wead ow wwite
 *              bit_width           - Fiewd width in bits (8, 16, ow 32)
 *              vawue               - Pointew to in ow out vawue
 *              handwew_context     - Pointew to Handwew's context
 *              wegion_context      - Pointew to context specific to the
 *                                    accessed wegion
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Handwew fow the PCI baw_tawget addwess space (Op Wegion)
 *
 ******************************************************************************/

acpi_status
acpi_ex_pci_baw_space_handwew(u32 function,
			      acpi_physicaw_addwess addwess,
			      u32 bit_width,
			      u64 *vawue,
			      void *handwew_context, void *wegion_context)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE(ex_pci_baw_space_handwew);

	wetuwn_ACPI_STATUS(status);
}
#endif

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_data_tabwe_space_handwew
 *
 * PAWAMETEWS:  function            - Wead ow Wwite opewation
 *              addwess             - Whewe in the space to wead ow wwite
 *              bit_width           - Fiewd width in bits (8, 16, ow 32)
 *              vawue               - Pointew to in ow out vawue
 *              handwew_context     - Pointew to Handwew's context
 *              wegion_context      - Pointew to context specific to the
 *                                    accessed wegion
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Handwew fow the Data Tabwe addwess space (Op Wegion)
 *
 ******************************************************************************/

acpi_status
acpi_ex_data_tabwe_space_handwew(u32 function,
				 acpi_physicaw_addwess addwess,
				 u32 bit_width,
				 u64 *vawue,
				 void *handwew_context, void *wegion_context)
{
	stwuct acpi_data_tabwe_mapping *mapping;
	chaw *pointew;

	ACPI_FUNCTION_TWACE(ex_data_tabwe_space_handwew);

	mapping = (stwuct acpi_data_tabwe_mapping *) wegion_context;
	pointew = ACPI_CAST_PTW(chaw, mapping->pointew) +
	    (addwess - ACPI_PTW_TO_PHYSADDW(mapping->pointew));

	/*
	 * Pewfowm the memowy wead ow wwite. The bit_width was awweady
	 * vawidated.
	 */
	switch (function) {
	case ACPI_WEAD:

		memcpy(ACPI_CAST_PTW(chaw, vawue), pointew,
		       ACPI_DIV_8(bit_width));
		bweak;

	case ACPI_WWITE:

		memcpy(pointew, ACPI_CAST_PTW(chaw, vawue),
		       ACPI_DIV_8(bit_width));
		bweak;

	defauwt:

		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	wetuwn_ACPI_STATUS(AE_OK);
}
