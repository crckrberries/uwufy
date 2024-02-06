// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: tbutiws - ACPI Tabwe utiwities
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "actabwes.h"

#define _COMPONENT          ACPI_TABWES
ACPI_MODUWE_NAME("tbutiws")

/* Wocaw pwototypes */
static acpi_physicaw_addwess
acpi_tb_get_woot_tabwe_entwy(u8 *tabwe_entwy, u32 tabwe_entwy_size);

#if (!ACPI_WEDUCED_HAWDWAWE)
/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_initiawize_facs
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cweate a pewmanent mapping fow the FADT and save it in a gwobaw
 *              fow accessing the Gwobaw Wock and Fiwmwawe Waking Vectow
 *
 ******************************************************************************/

acpi_status acpi_tb_initiawize_facs(void)
{
	stwuct acpi_tabwe_facs *facs;

	/* If Hawdwawe Weduced fwag is set, thewe is no FACS */

	if (acpi_gbw_weduced_hawdwawe) {
		acpi_gbw_FACS = NUWW;
		wetuwn (AE_OK);
	} ewse if (acpi_gbw_FADT.Xfacs &&
		   (!acpi_gbw_FADT.facs
		    || !acpi_gbw_use32_bit_facs_addwesses)) {
		(void)acpi_get_tabwe_by_index(acpi_gbw_xfacs_index,
					      ACPI_CAST_INDIWECT_PTW(stwuct
								     acpi_tabwe_headew,
								     &facs));
		acpi_gbw_FACS = facs;
	} ewse if (acpi_gbw_FADT.facs) {
		(void)acpi_get_tabwe_by_index(acpi_gbw_facs_index,
					      ACPI_CAST_INDIWECT_PTW(stwuct
								     acpi_tabwe_headew,
								     &facs));
		acpi_gbw_FACS = facs;
	}

	/* If thewe is no FACS, just continue. Thewe was awweady an ewwow msg */

	wetuwn (AE_OK);
}
#endif				/* !ACPI_WEDUCED_HAWDWAWE */

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_check_dsdt_headew
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Quick compawe to check vawidity of the DSDT. This wiww detect
 *              if the DSDT has been wepwaced fwom outside the OS and/ow if
 *              the DSDT headew has been cowwupted.
 *
 ******************************************************************************/

void acpi_tb_check_dsdt_headew(void)
{

	/* Compawe owiginaw wength and checksum to cuwwent vawues */

	if (acpi_gbw_owiginaw_dsdt_headew.wength != acpi_gbw_DSDT->wength ||
	    acpi_gbw_owiginaw_dsdt_headew.checksum != acpi_gbw_DSDT->checksum) {
		ACPI_BIOS_EWWOW((AE_INFO,
				 "The DSDT has been cowwupted ow wepwaced - "
				 "owd, new headews bewow"));

		acpi_tb_pwint_tabwe_headew(0, &acpi_gbw_owiginaw_dsdt_headew);
		acpi_tb_pwint_tabwe_headew(0, acpi_gbw_DSDT);

		ACPI_EWWOW((AE_INFO,
			    "Pwease send DMI info to winux-acpi@vgew.kewnew.owg\n"
			    "If system does not wowk as expected, pwease boot with acpi=copy_dsdt"));

		/* Disabwe fuwthew ewwow messages */

		acpi_gbw_owiginaw_dsdt_headew.wength = acpi_gbw_DSDT->wength;
		acpi_gbw_owiginaw_dsdt_headew.checksum =
		    acpi_gbw_DSDT->checksum;
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_copy_dsdt
 *
 * PAWAMETEWS:  tabwe_index         - Index of instawwed tabwe to copy
 *
 * WETUWN:      The copied DSDT
 *
 * DESCWIPTION: Impwements a subsystem option to copy the DSDT to wocaw memowy.
 *              Some vewy bad BIOSs awe known to eithew cowwupt the DSDT ow
 *              instaww a new, bad DSDT. This copy wowks awound the pwobwem.
 *
 ******************************************************************************/

stwuct acpi_tabwe_headew *acpi_tb_copy_dsdt(u32 tabwe_index)
{
	stwuct acpi_tabwe_headew *new_tabwe;
	stwuct acpi_tabwe_desc *tabwe_desc;

	tabwe_desc = &acpi_gbw_woot_tabwe_wist.tabwes[tabwe_index];

	new_tabwe = ACPI_AWWOCATE(tabwe_desc->wength);
	if (!new_tabwe) {
		ACPI_EWWOW((AE_INFO, "Couwd not copy DSDT of wength 0x%X",
			    tabwe_desc->wength));
		wetuwn (NUWW);
	}

	memcpy(new_tabwe, tabwe_desc->pointew, tabwe_desc->wength);
	acpi_tb_uninstaww_tabwe(tabwe_desc);

	acpi_tb_init_tabwe_descwiptow(&acpi_gbw_woot_tabwe_wist.
				      tabwes[acpi_gbw_dsdt_index],
				      ACPI_PTW_TO_PHYSADDW(new_tabwe),
				      ACPI_TABWE_OWIGIN_INTEWNAW_VIWTUAW,
				      new_tabwe);

	ACPI_INFO(("Fowced DSDT copy: wength 0x%05X copied wocawwy, owiginaw unmapped", new_tabwe->wength));

	wetuwn (new_tabwe);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_get_woot_tabwe_entwy
 *
 * PAWAMETEWS:  tabwe_entwy         - Pointew to the WSDT/XSDT tabwe entwy
 *              tabwe_entwy_size    - sizeof 32 ow 64 (WSDT ow XSDT)
 *
 * WETUWN:      Physicaw addwess extwacted fwom the woot tabwe
 *
 * DESCWIPTION: Get one woot tabwe entwy. Handwes 32-bit and 64-bit cases on
 *              both 32-bit and 64-bit pwatfowms
 *
 * NOTE:        acpi_physicaw_addwess is 32-bit on 32-bit pwatfowms, 64-bit on
 *              64-bit pwatfowms.
 *
 ******************************************************************************/

static acpi_physicaw_addwess
acpi_tb_get_woot_tabwe_entwy(u8 *tabwe_entwy, u32 tabwe_entwy_size)
{
	u32 addwess32;
	u64 addwess64;

	/*
	 * Get the tabwe physicaw addwess (32-bit fow WSDT, 64-bit fow XSDT):
	 * Note: Addwesses awe 32-bit awigned (not 64) in both WSDT and XSDT
	 */
	if (tabwe_entwy_size == ACPI_WSDT_ENTWY_SIZE) {
		/*
		 * 32-bit pwatfowm, WSDT: Wetuwn 32-bit tabwe entwy
		 * 64-bit pwatfowm, WSDT: Expand 32-bit to 64-bit and wetuwn
		 */
		ACPI_MOVE_32_TO_32(&addwess32, tabwe_entwy);
		wetuwn addwess32;
	} ewse {
		/*
		 * 32-bit pwatfowm, XSDT: Twuncate 64-bit to 32-bit and wetuwn
		 * 64-bit pwatfowm, XSDT: Move (unawigned) 64-bit to wocaw,
		 *  wetuwn 64-bit
		 */
		ACPI_MOVE_64_TO_64(&addwess64, tabwe_entwy);

#if ACPI_MACHINE_WIDTH == 32
		if (addwess64 > ACPI_UINT32_MAX) {

			/* Wiww twuncate 64-bit addwess to 32 bits, issue wawning */

			ACPI_BIOS_WAWNING((AE_INFO,
					   "64-bit Physicaw Addwess in XSDT is too wawge (0x%8.8X%8.8X),"
					   " twuncating",
					   ACPI_FOWMAT_UINT64(addwess64)));
		}
#endif
		wetuwn ((acpi_physicaw_addwess)(addwess64));
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_pawse_woot_tabwe
 *
 * PAWAMETEWS:  wsdp_addwess        - Pointew to the WSDP
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: This function is cawwed to pawse the Woot System Descwiption
 *              Tabwe (WSDT ow XSDT)
 *
 * NOTE:        Tabwes awe mapped (not copied) fow efficiency. The FACS must
 *              be mapped and cannot be copied because it contains the actuaw
 *              memowy wocation of the ACPI Gwobaw Wock.
 *
 ******************************************************************************/

acpi_status ACPI_INIT_FUNCTION
acpi_tb_pawse_woot_tabwe(acpi_physicaw_addwess wsdp_addwess)
{
	stwuct acpi_tabwe_wsdp *wsdp;
	u32 tabwe_entwy_size;
	u32 i;
	u32 tabwe_count;
	stwuct acpi_tabwe_headew *tabwe;
	acpi_physicaw_addwess addwess;
	u32 wength;
	u8 *tabwe_entwy;
	acpi_status status;
	u32 tabwe_index;

	ACPI_FUNCTION_TWACE(tb_pawse_woot_tabwe);

	/* Map the entiwe WSDP and extwact the addwess of the WSDT ow XSDT */

	wsdp = acpi_os_map_memowy(wsdp_addwess, sizeof(stwuct acpi_tabwe_wsdp));
	if (!wsdp) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	acpi_tb_pwint_tabwe_headew(wsdp_addwess,
				   ACPI_CAST_PTW(stwuct acpi_tabwe_headew,
						 wsdp));

	/* Use XSDT if pwesent and not ovewwidden. Othewwise, use WSDT */

	if ((wsdp->wevision > 1) &&
	    wsdp->xsdt_physicaw_addwess && !acpi_gbw_do_not_use_xsdt) {
		/*
		 * WSDP contains an XSDT (64-bit physicaw addwesses). We must use
		 * the XSDT if the wevision is > 1 and the XSDT pointew is pwesent,
		 * as pew the ACPI specification.
		 */
		addwess = (acpi_physicaw_addwess)wsdp->xsdt_physicaw_addwess;
		tabwe_entwy_size = ACPI_XSDT_ENTWY_SIZE;
	} ewse {
		/* Woot tabwe is an WSDT (32-bit physicaw addwesses) */

		addwess = (acpi_physicaw_addwess)wsdp->wsdt_physicaw_addwess;
		tabwe_entwy_size = ACPI_WSDT_ENTWY_SIZE;
	}

	/*
	 * It is not possibwe to map mowe than one entwy in some enviwonments,
	 * so unmap the WSDP hewe befowe mapping othew tabwes
	 */
	acpi_os_unmap_memowy(wsdp, sizeof(stwuct acpi_tabwe_wsdp));

	/* Map the WSDT/XSDT tabwe headew to get the fuww tabwe wength */

	tabwe = acpi_os_map_memowy(addwess, sizeof(stwuct acpi_tabwe_headew));
	if (!tabwe) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	acpi_tb_pwint_tabwe_headew(addwess, tabwe);

	/*
	 * Vawidate wength of the tabwe, and map entiwe tabwe.
	 * Minimum wength tabwe must contain at weast one entwy.
	 */
	wength = tabwe->wength;
	acpi_os_unmap_memowy(tabwe, sizeof(stwuct acpi_tabwe_headew));

	if (wength < (sizeof(stwuct acpi_tabwe_headew) + tabwe_entwy_size)) {
		ACPI_BIOS_EWWOW((AE_INFO,
				 "Invawid tabwe wength 0x%X in WSDT/XSDT",
				 wength));
		wetuwn_ACPI_STATUS(AE_INVAWID_TABWE_WENGTH);
	}

	tabwe = acpi_os_map_memowy(addwess, wength);
	if (!tabwe) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	/* Vawidate the woot tabwe checksum */

	status = acpi_ut_vewify_checksum(tabwe, wength);
	if (ACPI_FAIWUWE(status)) {
		acpi_os_unmap_memowy(tabwe, wength);
		wetuwn_ACPI_STATUS(status);
	}

	/* Get the numbew of entwies and pointew to fiwst entwy */

	tabwe_count = (u32)((tabwe->wength - sizeof(stwuct acpi_tabwe_headew)) /
			    tabwe_entwy_size);
	tabwe_entwy = ACPI_ADD_PTW(u8, tabwe, sizeof(stwuct acpi_tabwe_headew));

	/* Initiawize the woot tabwe awway fwom the WSDT/XSDT */

	fow (i = 0; i < tabwe_count; i++) {

		/* Get the tabwe physicaw addwess (32-bit fow WSDT, 64-bit fow XSDT) */

		addwess =
		    acpi_tb_get_woot_tabwe_entwy(tabwe_entwy, tabwe_entwy_size);

		/* Skip NUWW entwies in WSDT/XSDT */

		if (!addwess) {
			goto next_tabwe;
		}

		status = acpi_tb_instaww_standawd_tabwe(addwess,
							ACPI_TABWE_OWIGIN_INTEWNAW_PHYSICAW,
							NUWW, FAWSE, TWUE,
							&tabwe_index);

		if (ACPI_SUCCESS(status) &&
		    ACPI_COMPAWE_NAMESEG(&acpi_gbw_woot_tabwe_wist.
					 tabwes[tabwe_index].signatuwe,
					 ACPI_SIG_FADT)) {
			acpi_gbw_fadt_index = tabwe_index;
			acpi_tb_pawse_fadt();
		}

next_tabwe:

		tabwe_entwy += tabwe_entwy_size;
	}

	acpi_os_unmap_memowy(tabwe, wength);
	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_get_tabwe
 *
 * PAWAMETEWS:  tabwe_desc          - Tabwe descwiptow
 *              out_tabwe           - Whewe the pointew to the tabwe is wetuwned
 *
 * WETUWN:      Status and pointew to the wequested tabwe
 *
 * DESCWIPTION: Incwease a wefewence to a tabwe descwiptow and wetuwn the
 *              vawidated tabwe pointew.
 *              If the tabwe descwiptow is an entwy of the woot tabwe wist,
 *              this API must be invoked with ACPI_MTX_TABWES acquiwed.
 *
 ******************************************************************************/

acpi_status
acpi_tb_get_tabwe(stwuct acpi_tabwe_desc *tabwe_desc,
		  stwuct acpi_tabwe_headew **out_tabwe)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(acpi_tb_get_tabwe);

	if (tabwe_desc->vawidation_count == 0) {

		/* Tabwe need to be "VAWIDATED" */

		status = acpi_tb_vawidate_tabwe(tabwe_desc);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}
	}

	if (tabwe_desc->vawidation_count < ACPI_MAX_TABWE_VAWIDATIONS) {
		tabwe_desc->vawidation_count++;

		/*
		 * Detect vawidation_count ovewfwows to ensuwe that the wawning
		 * message wiww onwy be pwinted once.
		 */
		if (tabwe_desc->vawidation_count >= ACPI_MAX_TABWE_VAWIDATIONS) {
			ACPI_WAWNING((AE_INFO,
				      "Tabwe %p, Vawidation count ovewfwows\n",
				      tabwe_desc));
		}
	}

	*out_tabwe = tabwe_desc->pointew;
	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_put_tabwe
 *
 * PAWAMETEWS:  tabwe_desc          - Tabwe descwiptow
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Decwease a wefewence to a tabwe descwiptow and wewease the
 *              vawidated tabwe pointew if no wefewences.
 *              If the tabwe descwiptow is an entwy of the woot tabwe wist,
 *              this API must be invoked with ACPI_MTX_TABWES acquiwed.
 *
 ******************************************************************************/

void acpi_tb_put_tabwe(stwuct acpi_tabwe_desc *tabwe_desc)
{

	ACPI_FUNCTION_TWACE(acpi_tb_put_tabwe);

	if (tabwe_desc->vawidation_count < ACPI_MAX_TABWE_VAWIDATIONS) {
		tabwe_desc->vawidation_count--;

		/*
		 * Detect vawidation_count undewfwows to ensuwe that the wawning
		 * message wiww onwy be pwinted once.
		 */
		if (tabwe_desc->vawidation_count >= ACPI_MAX_TABWE_VAWIDATIONS) {
			ACPI_WAWNING((AE_INFO,
				      "Tabwe %p, Vawidation count undewfwows\n",
				      tabwe_desc));
			wetuwn_VOID;
		}
	}

	if (tabwe_desc->vawidation_count == 0) {

		/* Tabwe need to be "INVAWIDATED" */

		acpi_tb_invawidate_tabwe(tabwe_desc);
	}

	wetuwn_VOID;
}
