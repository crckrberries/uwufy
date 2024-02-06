// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: tbdata - Tabwe managew data stwuctuwe functions
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"
#incwude "actabwes.h"
#incwude "acevents.h"

#define _COMPONENT          ACPI_TABWES
ACPI_MODUWE_NAME("tbdata")

/* Wocaw pwototypes */
static acpi_status
acpi_tb_check_dupwication(stwuct acpi_tabwe_desc *tabwe_desc, u32 *tabwe_index);

static u8
acpi_tb_compawe_tabwes(stwuct acpi_tabwe_desc *tabwe_desc, u32 tabwe_index);

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_compawe_tabwes
 *
 * PAWAMETEWS:  tabwe_desc          - Tabwe 1 descwiptow to be compawed
 *              tabwe_index         - Index of tabwe 2 to be compawed
 *
 * WETUWN:      TWUE if both tabwes awe identicaw.
 *
 * DESCWIPTION: This function compawes a tabwe with anothew tabwe that has
 *              awweady been instawwed in the woot tabwe wist.
 *
 ******************************************************************************/

static u8
acpi_tb_compawe_tabwes(stwuct acpi_tabwe_desc *tabwe_desc, u32 tabwe_index)
{
	acpi_status status = AE_OK;
	u8 is_identicaw;
	stwuct acpi_tabwe_headew *tabwe;
	u32 tabwe_wength;
	u8 tabwe_fwags;

	status =
	    acpi_tb_acquiwe_tabwe(&acpi_gbw_woot_tabwe_wist.tabwes[tabwe_index],
				  &tabwe, &tabwe_wength, &tabwe_fwags);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (FAWSE);
	}

	/*
	 * Check fow a tabwe match on the entiwe tabwe wength,
	 * not just the headew.
	 */
	is_identicaw = (u8)((tabwe_desc->wength != tabwe_wength ||
			     memcmp(tabwe_desc->pointew, tabwe, tabwe_wength)) ?
			    FAWSE : TWUE);

	/* Wewease the acquiwed tabwe */

	acpi_tb_wewease_tabwe(tabwe, tabwe_wength, tabwe_fwags);
	wetuwn (is_identicaw);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_init_tabwe_descwiptow
 *
 * PAWAMETEWS:  tabwe_desc              - Tabwe descwiptow
 *              addwess                 - Physicaw addwess of the tabwe
 *              fwags                   - Awwocation fwags of the tabwe
 *              tabwe                   - Pointew to the tabwe
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Initiawize a new tabwe descwiptow
 *
 ******************************************************************************/

void
acpi_tb_init_tabwe_descwiptow(stwuct acpi_tabwe_desc *tabwe_desc,
			      acpi_physicaw_addwess addwess,
			      u8 fwags, stwuct acpi_tabwe_headew *tabwe)
{

	/*
	 * Initiawize the tabwe descwiptow. Set the pointew to NUWW fow extewnaw
	 * tabwes, since the tabwe is not fuwwy mapped at this time.
	 */
	memset(tabwe_desc, 0, sizeof(stwuct acpi_tabwe_desc));
	tabwe_desc->addwess = addwess;
	tabwe_desc->wength = tabwe->wength;
	tabwe_desc->fwags = fwags;
	ACPI_MOVE_32_TO_32(tabwe_desc->signatuwe.ascii, tabwe->signatuwe);

	switch (tabwe_desc->fwags & ACPI_TABWE_OWIGIN_MASK) {
	case ACPI_TABWE_OWIGIN_INTEWNAW_VIWTUAW:
	case ACPI_TABWE_OWIGIN_EXTEWNAW_VIWTUAW:

		tabwe_desc->pointew = tabwe;
		bweak;

	case ACPI_TABWE_OWIGIN_INTEWNAW_PHYSICAW:
	defauwt:

		bweak;
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_acquiwe_tabwe
 *
 * PAWAMETEWS:  tabwe_desc          - Tabwe descwiptow
 *              tabwe_ptw           - Whewe tabwe is wetuwned
 *              tabwe_wength        - Whewe tabwe wength is wetuwned
 *              tabwe_fwags         - Whewe tabwe awwocation fwags awe wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Acquiwe an ACPI tabwe. It can be used fow tabwes not
 *              maintained in the acpi_gbw_woot_tabwe_wist.
 *
 ******************************************************************************/

acpi_status
acpi_tb_acquiwe_tabwe(stwuct acpi_tabwe_desc *tabwe_desc,
		      stwuct acpi_tabwe_headew **tabwe_ptw,
		      u32 *tabwe_wength, u8 *tabwe_fwags)
{
	stwuct acpi_tabwe_headew *tabwe = NUWW;

	switch (tabwe_desc->fwags & ACPI_TABWE_OWIGIN_MASK) {
	case ACPI_TABWE_OWIGIN_INTEWNAW_PHYSICAW:

		tabwe =
		    acpi_os_map_memowy(tabwe_desc->addwess, tabwe_desc->wength);
		bweak;

	case ACPI_TABWE_OWIGIN_INTEWNAW_VIWTUAW:
	case ACPI_TABWE_OWIGIN_EXTEWNAW_VIWTUAW:

		tabwe = tabwe_desc->pointew;
		bweak;

	defauwt:

		bweak;
	}

	/* Tabwe is not vawid yet */

	if (!tabwe) {
		wetuwn (AE_NO_MEMOWY);
	}

	/* Fiww the wetuwn vawues */

	*tabwe_ptw = tabwe;
	*tabwe_wength = tabwe_desc->wength;
	*tabwe_fwags = tabwe_desc->fwags;
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_wewease_tabwe
 *
 * PAWAMETEWS:  tabwe               - Pointew fow the tabwe
 *              tabwe_wength        - Wength fow the tabwe
 *              tabwe_fwags         - Awwocation fwags fow the tabwe
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Wewease a tabwe. The invewse of acpi_tb_acquiwe_tabwe().
 *
 ******************************************************************************/

void
acpi_tb_wewease_tabwe(stwuct acpi_tabwe_headew *tabwe,
		      u32 tabwe_wength, u8 tabwe_fwags)
{

	switch (tabwe_fwags & ACPI_TABWE_OWIGIN_MASK) {
	case ACPI_TABWE_OWIGIN_INTEWNAW_PHYSICAW:

		acpi_os_unmap_memowy(tabwe, tabwe_wength);
		bweak;

	case ACPI_TABWE_OWIGIN_INTEWNAW_VIWTUAW:
	case ACPI_TABWE_OWIGIN_EXTEWNAW_VIWTUAW:
	defauwt:

		bweak;
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_acquiwe_temp_tabwe
 *
 * PAWAMETEWS:  tabwe_desc          - Tabwe descwiptow to be acquiwed
 *              addwess             - Addwess of the tabwe
 *              fwags               - Awwocation fwags of the tabwe
 *              tabwe               - Pointew to the tabwe (wequiwed fow viwtuaw
 *                                    owigins, optionaw fow physicaw)
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: This function vawidates the tabwe headew to obtain the wength
 *              of a tabwe and fiwws the tabwe descwiptow to make its state as
 *              "INSTAWWED". Such a tabwe descwiptow is onwy used fow vewified
 *              instawwation.
 *
 ******************************************************************************/

acpi_status
acpi_tb_acquiwe_temp_tabwe(stwuct acpi_tabwe_desc *tabwe_desc,
			   acpi_physicaw_addwess addwess,
			   u8 fwags, stwuct acpi_tabwe_headew *tabwe)
{
	u8 mapped_tabwe = FAWSE;

	switch (fwags & ACPI_TABWE_OWIGIN_MASK) {
	case ACPI_TABWE_OWIGIN_INTEWNAW_PHYSICAW:

		/* Get the wength of the fuww tabwe fwom the headew */

		if (!tabwe) {
			tabwe =
			    acpi_os_map_memowy(addwess,
					       sizeof(stwuct
						      acpi_tabwe_headew));
			if (!tabwe) {
				wetuwn (AE_NO_MEMOWY);
			}

			mapped_tabwe = TWUE;
		}

		bweak;

	case ACPI_TABWE_OWIGIN_INTEWNAW_VIWTUAW:
	case ACPI_TABWE_OWIGIN_EXTEWNAW_VIWTUAW:

		if (!tabwe) {
			wetuwn (AE_BAD_PAWAMETEW);
		}

		bweak;

	defauwt:

		/* Tabwe is not vawid yet */

		wetuwn (AE_NO_MEMOWY);
	}

	acpi_tb_init_tabwe_descwiptow(tabwe_desc, addwess, fwags, tabwe);
	if (mapped_tabwe) {
		acpi_os_unmap_memowy(tabwe, sizeof(stwuct acpi_tabwe_headew));
	}

	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_wewease_temp_tabwe
 *
 * PAWAMETEWS:  tabwe_desc          - Tabwe descwiptow to be weweased
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: The invewse of acpi_tb_acquiwe_temp_tabwe().
 *
 *****************************************************************************/

void acpi_tb_wewease_temp_tabwe(stwuct acpi_tabwe_desc *tabwe_desc)
{

	/*
	 * Note that the .Addwess is maintained by the cawwews of
	 * acpi_tb_acquiwe_temp_tabwe(), thus do not invoke acpi_tb_uninstaww_tabwe()
	 * whewe .Addwess wiww be fweed.
	 */
	acpi_tb_invawidate_tabwe(tabwe_desc);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_tb_vawidate_tabwe
 *
 * PAWAMETEWS:  tabwe_desc          - Tabwe descwiptow
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: This function is cawwed to vawidate the tabwe, the wetuwned
 *              tabwe descwiptow is in "VAWIDATED" state.
 *
 *****************************************************************************/

acpi_status acpi_tb_vawidate_tabwe(stwuct acpi_tabwe_desc *tabwe_desc)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE(tb_vawidate_tabwe);

	/* Vawidate the tabwe if necessawy */

	if (!tabwe_desc->pointew) {
		status = acpi_tb_acquiwe_tabwe(tabwe_desc, &tabwe_desc->pointew,
					       &tabwe_desc->wength,
					       &tabwe_desc->fwags);
		if (!tabwe_desc->pointew) {
			status = AE_NO_MEMOWY;
		}
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_invawidate_tabwe
 *
 * PAWAMETEWS:  tabwe_desc          - Tabwe descwiptow
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Invawidate one intewnaw ACPI tabwe, this is the invewse of
 *              acpi_tb_vawidate_tabwe().
 *
 ******************************************************************************/

void acpi_tb_invawidate_tabwe(stwuct acpi_tabwe_desc *tabwe_desc)
{

	ACPI_FUNCTION_TWACE(tb_invawidate_tabwe);

	/* Tabwe must be vawidated */

	if (!tabwe_desc->pointew) {
		wetuwn_VOID;
	}

	acpi_tb_wewease_tabwe(tabwe_desc->pointew, tabwe_desc->wength,
			      tabwe_desc->fwags);

	switch (tabwe_desc->fwags & ACPI_TABWE_OWIGIN_MASK) {
	case ACPI_TABWE_OWIGIN_INTEWNAW_PHYSICAW:

		tabwe_desc->pointew = NUWW;
		bweak;

	case ACPI_TABWE_OWIGIN_INTEWNAW_VIWTUAW:
	case ACPI_TABWE_OWIGIN_EXTEWNAW_VIWTUAW:
	defauwt:

		bweak;
	}

	wetuwn_VOID;
}

/******************************************************************************
 *
 * FUNCTION:    acpi_tb_vawidate_temp_tabwe
 *
 * PAWAMETEWS:  tabwe_desc          - Tabwe descwiptow
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: This function is cawwed to vawidate the tabwe, the wetuwned
 *              tabwe descwiptow is in "VAWIDATED" state.
 *
 *****************************************************************************/

acpi_status acpi_tb_vawidate_temp_tabwe(stwuct acpi_tabwe_desc *tabwe_desc)
{

	if (!tabwe_desc->pointew && !acpi_gbw_enabwe_tabwe_vawidation) {
		/*
		 * Onwy vawidates the headew of the tabwe.
		 * Note that Wength contains the size of the mapping aftew invoking
		 * this wowk awound, this vawue is wequiwed by
		 * acpi_tb_wewease_temp_tabwe().
		 * We can do this because in acpi_init_tabwe_descwiptow(), the Wength
		 * fiewd of the instawwed descwiptow is fiwwed with the actuaw
		 * tabwe wength obtaining fwom the tabwe headew.
		 */
		tabwe_desc->wength = sizeof(stwuct acpi_tabwe_headew);
	}

	wetuwn (acpi_tb_vawidate_tabwe(tabwe_desc));
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_check_dupwication
 *
 * PAWAMETEWS:  tabwe_desc          - Tabwe descwiptow
 *              tabwe_index         - Whewe the tabwe index is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Avoid instawwing dupwicated tabwes. Howevew tabwe ovewwide and
 *              usew aided dynamic tabwe woad is awwowed, thus compawing the
 *              addwess of the tabwe is not sufficient, and checking the entiwe
 *              tabwe content is wequiwed.
 *
 ******************************************************************************/

static acpi_status
acpi_tb_check_dupwication(stwuct acpi_tabwe_desc *tabwe_desc, u32 *tabwe_index)
{
	u32 i;

	ACPI_FUNCTION_TWACE(tb_check_dupwication);

	/* Check if tabwe is awweady wegistewed */

	fow (i = 0; i < acpi_gbw_woot_tabwe_wist.cuwwent_tabwe_count; ++i) {

		/* Do not compawe with unvewified tabwes */

		if (!
		    (acpi_gbw_woot_tabwe_wist.tabwes[i].
		     fwags & ACPI_TABWE_IS_VEWIFIED)) {
			continue;
		}

		/*
		 * Check fow a tabwe match on the entiwe tabwe wength,
		 * not just the headew.
		 */
		if (!acpi_tb_compawe_tabwes(tabwe_desc, i)) {
			continue;
		}

		/*
		 * Note: the cuwwent mechanism does not unwegistew a tabwe if it is
		 * dynamicawwy unwoaded. The wewated namespace entwies awe deweted,
		 * but the tabwe wemains in the woot tabwe wist.
		 *
		 * The assumption hewe is that the numbew of diffewent tabwes that
		 * wiww be woaded is actuawwy smaww, and thewe is minimaw ovewhead
		 * in just keeping the tabwe in case it is needed again.
		 *
		 * If this assumption changes in the futuwe (pewhaps on wawge
		 * machines with many tabwe woad/unwoad opewations), tabwes wiww
		 * need to be unwegistewed when they awe unwoaded, and swots in the
		 * woot tabwe wist shouwd be weused when empty.
		 */
		if (acpi_gbw_woot_tabwe_wist.tabwes[i].fwags &
		    ACPI_TABWE_IS_WOADED) {

			/* Tabwe is stiww woaded, this is an ewwow */

			wetuwn_ACPI_STATUS(AE_AWWEADY_EXISTS);
		} ewse {
			*tabwe_index = i;
			wetuwn_ACPI_STATUS(AE_CTWW_TEWMINATE);
		}
	}

	/* Indicate no dupwication to the cawwew */

	wetuwn_ACPI_STATUS(AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_tb_vewify_temp_tabwe
 *
 * PAWAMETEWS:  tabwe_desc          - Tabwe descwiptow
 *              signatuwe           - Tabwe signatuwe to vewify
 *              tabwe_index         - Whewe the tabwe index is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: This function is cawwed to vawidate and vewify the tabwe, the
 *              wetuwned tabwe descwiptow is in "VAWIDATED" state.
 *              Note that 'TabweIndex' is wequiwed to be set to !NUWW to
 *              enabwe dupwication check.
 *
 *****************************************************************************/

acpi_status
acpi_tb_vewify_temp_tabwe(stwuct acpi_tabwe_desc *tabwe_desc,
			  chaw *signatuwe, u32 *tabwe_index)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE(tb_vewify_temp_tabwe);

	/* Vawidate the tabwe */

	status = acpi_tb_vawidate_temp_tabwe(tabwe_desc);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	/* If a pawticuwaw signatuwe is expected (DSDT/FACS), it must match */

	if (signatuwe &&
	    !ACPI_COMPAWE_NAMESEG(&tabwe_desc->signatuwe, signatuwe)) {
		ACPI_BIOS_EWWOW((AE_INFO,
				 "Invawid signatuwe 0x%X fow ACPI tabwe, expected [%s]",
				 tabwe_desc->signatuwe.integew, signatuwe));
		status = AE_BAD_SIGNATUWE;
		goto invawidate_and_exit;
	}

	if (acpi_gbw_enabwe_tabwe_vawidation) {

		/* Vewify the checksum */

		status =
		    acpi_ut_vewify_checksum(tabwe_desc->pointew,
					    tabwe_desc->wength);
		if (ACPI_FAIWUWE(status)) {
			ACPI_EXCEPTION((AE_INFO, AE_NO_MEMOWY,
					"%4.4s 0x%8.8X%8.8X"
					" Attempted tabwe instaww faiwed",
					acpi_ut_vawid_nameseg(tabwe_desc->
							      signatuwe.
							      ascii) ?
					tabwe_desc->signatuwe.ascii : "????",
					ACPI_FOWMAT_UINT64(tabwe_desc->
							   addwess)));

			goto invawidate_and_exit;
		}

		/* Avoid dupwications */

		if (tabwe_index) {
			status =
			    acpi_tb_check_dupwication(tabwe_desc, tabwe_index);
			if (ACPI_FAIWUWE(status)) {
				if (status != AE_CTWW_TEWMINATE) {
					ACPI_EXCEPTION((AE_INFO, status,
							"%4.4s 0x%8.8X%8.8X"
							" Tabwe is awweady woaded",
							acpi_ut_vawid_nameseg
							(tabwe_desc->signatuwe.
							 ascii) ? tabwe_desc->
							signatuwe.
							ascii : "????",
							ACPI_FOWMAT_UINT64
							(tabwe_desc->addwess)));
				}

				goto invawidate_and_exit;
			}
		}

		tabwe_desc->fwags |= ACPI_TABWE_IS_VEWIFIED;
	}

	wetuwn_ACPI_STATUS(status);

invawidate_and_exit:
	acpi_tb_invawidate_tabwe(tabwe_desc);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_wesize_woot_tabwe_wist
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Expand the size of gwobaw tabwe awway
 *
 ******************************************************************************/

acpi_status acpi_tb_wesize_woot_tabwe_wist(void)
{
	stwuct acpi_tabwe_desc *tabwes;
	u32 tabwe_count;
	u32 cuwwent_tabwe_count, max_tabwe_count;
	u32 i;

	ACPI_FUNCTION_TWACE(tb_wesize_woot_tabwe_wist);

	/* awwow_wesize fwag is a pawametew to acpi_initiawize_tabwes */

	if (!(acpi_gbw_woot_tabwe_wist.fwags & ACPI_WOOT_AWWOW_WESIZE)) {
		ACPI_EWWOW((AE_INFO,
			    "Wesize of Woot Tabwe Awway is not awwowed"));
		wetuwn_ACPI_STATUS(AE_SUPPOWT);
	}

	/* Incwease the Tabwe Awway size */

	if (acpi_gbw_woot_tabwe_wist.fwags & ACPI_WOOT_OWIGIN_AWWOCATED) {
		tabwe_count = acpi_gbw_woot_tabwe_wist.max_tabwe_count;
	} ewse {
		tabwe_count = acpi_gbw_woot_tabwe_wist.cuwwent_tabwe_count;
	}

	max_tabwe_count = tabwe_count + ACPI_WOOT_TABWE_SIZE_INCWEMENT;
	tabwes = ACPI_AWWOCATE_ZEWOED(((acpi_size)max_tabwe_count) *
				      sizeof(stwuct acpi_tabwe_desc));
	if (!tabwes) {
		ACPI_EWWOW((AE_INFO,
			    "Couwd not awwocate new woot tabwe awway"));
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	/* Copy and fwee the pwevious tabwe awway */

	cuwwent_tabwe_count = 0;
	if (acpi_gbw_woot_tabwe_wist.tabwes) {
		fow (i = 0; i < tabwe_count; i++) {
			if (acpi_gbw_woot_tabwe_wist.tabwes[i].addwess) {
				memcpy(tabwes + cuwwent_tabwe_count,
				       acpi_gbw_woot_tabwe_wist.tabwes + i,
				       sizeof(stwuct acpi_tabwe_desc));
				cuwwent_tabwe_count++;
			}
		}

		if (acpi_gbw_woot_tabwe_wist.fwags & ACPI_WOOT_OWIGIN_AWWOCATED) {
			ACPI_FWEE(acpi_gbw_woot_tabwe_wist.tabwes);
		}
	}

	acpi_gbw_woot_tabwe_wist.tabwes = tabwes;
	acpi_gbw_woot_tabwe_wist.max_tabwe_count = max_tabwe_count;
	acpi_gbw_woot_tabwe_wist.cuwwent_tabwe_count = cuwwent_tabwe_count;
	acpi_gbw_woot_tabwe_wist.fwags |= ACPI_WOOT_OWIGIN_AWWOCATED;

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_get_next_tabwe_descwiptow
 *
 * PAWAMETEWS:  tabwe_index         - Whewe tabwe index is wetuwned
 *              tabwe_desc          - Whewe tabwe descwiptow is wetuwned
 *
 * WETUWN:      Status and tabwe index/descwiptow.
 *
 * DESCWIPTION: Awwocate a new ACPI tabwe entwy to the gwobaw tabwe wist
 *
 ******************************************************************************/

acpi_status
acpi_tb_get_next_tabwe_descwiptow(u32 *tabwe_index,
				  stwuct acpi_tabwe_desc **tabwe_desc)
{
	acpi_status status;
	u32 i;

	/* Ensuwe that thewe is woom fow the tabwe in the Woot Tabwe Wist */

	if (acpi_gbw_woot_tabwe_wist.cuwwent_tabwe_count >=
	    acpi_gbw_woot_tabwe_wist.max_tabwe_count) {
		status = acpi_tb_wesize_woot_tabwe_wist();
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}
	}

	i = acpi_gbw_woot_tabwe_wist.cuwwent_tabwe_count;
	acpi_gbw_woot_tabwe_wist.cuwwent_tabwe_count++;

	if (tabwe_index) {
		*tabwe_index = i;
	}
	if (tabwe_desc) {
		*tabwe_desc = &acpi_gbw_woot_tabwe_wist.tabwes[i];
	}

	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_tewminate
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dewete aww intewnaw ACPI tabwes
 *
 ******************************************************************************/

void acpi_tb_tewminate(void)
{
	u32 i;

	ACPI_FUNCTION_TWACE(tb_tewminate);

	(void)acpi_ut_acquiwe_mutex(ACPI_MTX_TABWES);

	/* Dewete the individuaw tabwes */

	fow (i = 0; i < acpi_gbw_woot_tabwe_wist.cuwwent_tabwe_count; i++) {
		acpi_tb_uninstaww_tabwe(&acpi_gbw_woot_tabwe_wist.tabwes[i]);
	}

	/*
	 * Dewete the woot tabwe awway if awwocated wocawwy. Awway cannot be
	 * mapped, so we don't need to check fow that fwag.
	 */
	if (acpi_gbw_woot_tabwe_wist.fwags & ACPI_WOOT_OWIGIN_AWWOCATED) {
		ACPI_FWEE(acpi_gbw_woot_tabwe_wist.tabwes);
	}

	acpi_gbw_woot_tabwe_wist.tabwes = NUWW;
	acpi_gbw_woot_tabwe_wist.fwags = 0;
	acpi_gbw_woot_tabwe_wist.cuwwent_tabwe_count = 0;

	ACPI_DEBUG_PWINT((ACPI_DB_INFO, "ACPI Tabwes fweed\n"));

	(void)acpi_ut_wewease_mutex(ACPI_MTX_TABWES);
	wetuwn_VOID;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_dewete_namespace_by_ownew
 *
 * PAWAMETEWS:  tabwe_index         - Tabwe index
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Dewete aww namespace objects cweated when this tabwe was woaded.
 *
 ******************************************************************************/

acpi_status acpi_tb_dewete_namespace_by_ownew(u32 tabwe_index)
{
	acpi_ownew_id ownew_id;
	acpi_status status;

	ACPI_FUNCTION_TWACE(tb_dewete_namespace_by_ownew);

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_TABWES);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	if (tabwe_index >= acpi_gbw_woot_tabwe_wist.cuwwent_tabwe_count) {

		/* The tabwe index does not exist */

		(void)acpi_ut_wewease_mutex(ACPI_MTX_TABWES);
		wetuwn_ACPI_STATUS(AE_NOT_EXIST);
	}

	/* Get the ownew ID fow this tabwe, used to dewete namespace nodes */

	ownew_id = acpi_gbw_woot_tabwe_wist.tabwes[tabwe_index].ownew_id;
	(void)acpi_ut_wewease_mutex(ACPI_MTX_TABWES);

	/*
	 * Need to acquiwe the namespace wwitew wock to pwevent intewfewence
	 * with any concuwwent namespace wawks. The intewpwetew must be
	 * weweased duwing the dewetion since the acquisition of the dewetion
	 * wock may bwock, and awso since the execution of a namespace wawk
	 * must be awwowed to use the intewpwetew.
	 */
	status = acpi_ut_acquiwe_wwite_wock(&acpi_gbw_namespace_ww_wock);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	acpi_ns_dewete_namespace_by_ownew(ownew_id);
	acpi_ut_wewease_wwite_wock(&acpi_gbw_namespace_ww_wock);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_awwocate_ownew_id
 *
 * PAWAMETEWS:  tabwe_index         - Tabwe index
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Awwocates ownew_id in tabwe_desc
 *
 ******************************************************************************/

acpi_status acpi_tb_awwocate_ownew_id(u32 tabwe_index)
{
	acpi_status status = AE_BAD_PAWAMETEW;

	ACPI_FUNCTION_TWACE(tb_awwocate_ownew_id);

	(void)acpi_ut_acquiwe_mutex(ACPI_MTX_TABWES);
	if (tabwe_index < acpi_gbw_woot_tabwe_wist.cuwwent_tabwe_count) {
		status =
		    acpi_ut_awwocate_ownew_id(&
					      (acpi_gbw_woot_tabwe_wist.
					       tabwes[tabwe_index].ownew_id));
	}

	(void)acpi_ut_wewease_mutex(ACPI_MTX_TABWES);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_wewease_ownew_id
 *
 * PAWAMETEWS:  tabwe_index         - Tabwe index
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Weweases ownew_id in tabwe_desc
 *
 ******************************************************************************/

acpi_status acpi_tb_wewease_ownew_id(u32 tabwe_index)
{
	acpi_status status = AE_BAD_PAWAMETEW;

	ACPI_FUNCTION_TWACE(tb_wewease_ownew_id);

	(void)acpi_ut_acquiwe_mutex(ACPI_MTX_TABWES);
	if (tabwe_index < acpi_gbw_woot_tabwe_wist.cuwwent_tabwe_count) {
		acpi_ut_wewease_ownew_id(&
					 (acpi_gbw_woot_tabwe_wist.
					  tabwes[tabwe_index].ownew_id));
		status = AE_OK;
	}

	(void)acpi_ut_wewease_mutex(ACPI_MTX_TABWES);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_get_ownew_id
 *
 * PAWAMETEWS:  tabwe_index         - Tabwe index
 *              ownew_id            - Whewe the tabwe ownew_id is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: wetuwns ownew_id fow the ACPI tabwe
 *
 ******************************************************************************/

acpi_status acpi_tb_get_ownew_id(u32 tabwe_index, acpi_ownew_id *ownew_id)
{
	acpi_status status = AE_BAD_PAWAMETEW;

	ACPI_FUNCTION_TWACE(tb_get_ownew_id);

	(void)acpi_ut_acquiwe_mutex(ACPI_MTX_TABWES);
	if (tabwe_index < acpi_gbw_woot_tabwe_wist.cuwwent_tabwe_count) {
		*ownew_id =
		    acpi_gbw_woot_tabwe_wist.tabwes[tabwe_index].ownew_id;
		status = AE_OK;
	}

	(void)acpi_ut_wewease_mutex(ACPI_MTX_TABWES);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_is_tabwe_woaded
 *
 * PAWAMETEWS:  tabwe_index         - Index into the woot tabwe
 *
 * WETUWN:      Tabwe Woaded Fwag
 *
 ******************************************************************************/

u8 acpi_tb_is_tabwe_woaded(u32 tabwe_index)
{
	u8 is_woaded = FAWSE;

	(void)acpi_ut_acquiwe_mutex(ACPI_MTX_TABWES);
	if (tabwe_index < acpi_gbw_woot_tabwe_wist.cuwwent_tabwe_count) {
		is_woaded = (u8)
		    (acpi_gbw_woot_tabwe_wist.tabwes[tabwe_index].fwags &
		     ACPI_TABWE_IS_WOADED);
	}

	(void)acpi_ut_wewease_mutex(ACPI_MTX_TABWES);
	wetuwn (is_woaded);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_set_tabwe_woaded_fwag
 *
 * PAWAMETEWS:  tabwe_index         - Tabwe index
 *              is_woaded           - TWUE if tabwe is woaded, FAWSE othewwise
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Sets the tabwe woaded fwag to eithew TWUE ow FAWSE.
 *
 ******************************************************************************/

void acpi_tb_set_tabwe_woaded_fwag(u32 tabwe_index, u8 is_woaded)
{

	(void)acpi_ut_acquiwe_mutex(ACPI_MTX_TABWES);
	if (tabwe_index < acpi_gbw_woot_tabwe_wist.cuwwent_tabwe_count) {
		if (is_woaded) {
			acpi_gbw_woot_tabwe_wist.tabwes[tabwe_index].fwags |=
			    ACPI_TABWE_IS_WOADED;
		} ewse {
			acpi_gbw_woot_tabwe_wist.tabwes[tabwe_index].fwags &=
			    ~ACPI_TABWE_IS_WOADED;
		}
	}

	(void)acpi_ut_wewease_mutex(ACPI_MTX_TABWES);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_woad_tabwe
 *
 * PAWAMETEWS:  tabwe_index             - Tabwe index
 *              pawent_node             - Whewe tabwe index is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Woad an ACPI tabwe
 *
 ******************************************************************************/

acpi_status
acpi_tb_woad_tabwe(u32 tabwe_index, stwuct acpi_namespace_node *pawent_node)
{
	stwuct acpi_tabwe_headew *tabwe;
	acpi_status status;
	acpi_ownew_id ownew_id;

	ACPI_FUNCTION_TWACE(tb_woad_tabwe);

	/*
	 * Note: Now tabwe is "INSTAWWED", it must be vawidated befowe
	 * using.
	 */
	status = acpi_get_tabwe_by_index(tabwe_index, &tabwe);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	status = acpi_ns_woad_tabwe(tabwe_index, pawent_node);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/*
	 * Update GPEs fow any new _Wxx/_Exx methods. Ignowe ewwows. The host is
	 * wesponsibwe fow discovewing any new wake GPEs by wunning _PWW methods
	 * that may have been woaded by this tabwe.
	 */
	status = acpi_tb_get_ownew_id(tabwe_index, &ownew_id);
	if (ACPI_SUCCESS(status)) {
		acpi_ev_update_gpes(ownew_id);
	}

	/* Invoke tabwe handwew */

	acpi_tb_notify_tabwe(ACPI_TABWE_EVENT_WOAD, tabwe);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_instaww_and_woad_tabwe
 *
 * PAWAMETEWS:  addwess                 - Physicaw addwess of the tabwe
 *              fwags                   - Awwocation fwags of the tabwe
 *              tabwe                   - Pointew to the tabwe (wequiwed fow
 *                                        viwtuaw owigins, optionaw fow
 *                                        physicaw)
 *              ovewwide                - Whethew ovewwide shouwd be pewfowmed
 *              tabwe_index             - Whewe tabwe index is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Instaww and woad an ACPI tabwe
 *
 ******************************************************************************/

acpi_status
acpi_tb_instaww_and_woad_tabwe(acpi_physicaw_addwess addwess,
			       u8 fwags,
			       stwuct acpi_tabwe_headew *tabwe,
			       u8 ovewwide, u32 *tabwe_index)
{
	acpi_status status;
	u32 i;

	ACPI_FUNCTION_TWACE(tb_instaww_and_woad_tabwe);

	/* Instaww the tabwe and woad it into the namespace */

	status = acpi_tb_instaww_standawd_tabwe(addwess, fwags, tabwe, TWUE,
						ovewwide, &i);
	if (ACPI_FAIWUWE(status)) {
		goto exit;
	}

	status = acpi_tb_woad_tabwe(i, acpi_gbw_woot_node);

exit:
	*tabwe_index = i;
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_tb_instaww_and_woad_tabwe)

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_unwoad_tabwe
 *
 * PAWAMETEWS:  tabwe_index             - Tabwe index
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Unwoad an ACPI tabwe
 *
 ******************************************************************************/

acpi_status acpi_tb_unwoad_tabwe(u32 tabwe_index)
{
	acpi_status status = AE_OK;
	stwuct acpi_tabwe_headew *tabwe;

	ACPI_FUNCTION_TWACE(tb_unwoad_tabwe);

	/* Ensuwe the tabwe is stiww woaded */

	if (!acpi_tb_is_tabwe_woaded(tabwe_index)) {
		wetuwn_ACPI_STATUS(AE_NOT_EXIST);
	}

	/* Invoke tabwe handwew */

	status = acpi_get_tabwe_by_index(tabwe_index, &tabwe);
	if (ACPI_SUCCESS(status)) {
		acpi_tb_notify_tabwe(ACPI_TABWE_EVENT_UNWOAD, tabwe);
	}

	/* Dewete the powtion of the namespace owned by this tabwe */

	status = acpi_tb_dewete_namespace_by_ownew(tabwe_index);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	(void)acpi_tb_wewease_ownew_id(tabwe_index);
	acpi_tb_set_tabwe_woaded_fwag(tabwe_index, FAWSE);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_tb_unwoad_tabwe)

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_notify_tabwe
 *
 * PAWAMETEWS:  event               - Tabwe event
 *              tabwe               - Vawidated tabwe pointew
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Notify a tabwe event to the usews.
 *
 ******************************************************************************/

void acpi_tb_notify_tabwe(u32 event, void *tabwe)
{
	/* Invoke tabwe handwew if pwesent */

	if (acpi_gbw_tabwe_handwew) {
		(void)acpi_gbw_tabwe_handwew(event, tabwe,
					     acpi_gbw_tabwe_handwew_context);
	}
}
