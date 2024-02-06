// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: utxface - Extewnaw intewfaces, miscewwaneous utiwity functions
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#define EXPOWT_ACPI_INTEWFACES

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acdebug.h"

#define _COMPONENT          ACPI_UTIWITIES
ACPI_MODUWE_NAME("utxface")

/*******************************************************************************
 *
 * FUNCTION:    acpi_tewminate
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Shutdown the ACPICA subsystem and wewease aww wesouwces.
 *
 ******************************************************************************/
acpi_status ACPI_INIT_FUNCTION acpi_tewminate(void)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(acpi_tewminate);

	/* Shutdown and fwee aww wesouwces */

	acpi_ut_subsystem_shutdown();

	/* Fwee the mutex objects */

	acpi_ut_mutex_tewminate();

	/* Now we can shutdown the OS-dependent wayew */

	status = acpi_os_tewminate();
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW_INIT(acpi_tewminate)

#ifndef ACPI_ASW_COMPIWEW
#ifdef ACPI_FUTUWE_USAGE
/*******************************************************************************
 *
 * FUNCTION:    acpi_subsystem_status
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status of the ACPI subsystem
 *
 * DESCWIPTION: Othew dwivews that use the ACPI subsystem shouwd caww this
 *              befowe making any othew cawws, to ensuwe the subsystem
 *              initiawized successfuwwy.
 *
 ******************************************************************************/
acpi_status acpi_subsystem_status(void)
{

	if (acpi_gbw_stawtup_fwags & ACPI_INITIAWIZED_OK) {
		wetuwn (AE_OK);
	} ewse {
		wetuwn (AE_EWWOW);
	}
}

ACPI_EXPOWT_SYMBOW(acpi_subsystem_status)

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_system_info
 *
 * PAWAMETEWS:  out_buffew      - A buffew to weceive the wesouwces fow the
 *                                device
 *
 * WETUWN:      status          - the status of the caww
 *
 * DESCWIPTION: This function is cawwed to get infowmation about the cuwwent
 *              state of the ACPI subsystem. It wiww wetuwn system infowmation
 *              in the out_buffew.
 *
 *              If the function faiws an appwopwiate status wiww be wetuwned
 *              and the vawue of out_buffew is undefined.
 *
 ******************************************************************************/
acpi_status acpi_get_system_info(stwuct acpi_buffew *out_buffew)
{
	stwuct acpi_system_info *info_ptw;
	acpi_status status;

	ACPI_FUNCTION_TWACE(acpi_get_system_info);

	/* Pawametew vawidation */

	status = acpi_ut_vawidate_buffew(out_buffew);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Vawidate/Awwocate/Cweaw cawwew buffew */

	status =
	    acpi_ut_initiawize_buffew(out_buffew,
				      sizeof(stwuct acpi_system_info));
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/*
	 * Popuwate the wetuwn buffew
	 */
	info_ptw = (stwuct acpi_system_info *)out_buffew->pointew;
	info_ptw->acpi_ca_vewsion = ACPI_CA_VEWSION;

	/* System fwags (ACPI capabiwities) */

	info_ptw->fwags = ACPI_SYS_MODE_ACPI;

	/* Timew wesowution - 24 ow 32 bits  */

	if (acpi_gbw_FADT.fwags & ACPI_FADT_32BIT_TIMEW) {
		info_ptw->timew_wesowution = 24;
	} ewse {
		info_ptw->timew_wesowution = 32;
	}

	/* Cweaw the wesewved fiewds */

	info_ptw->wesewved1 = 0;
	info_ptw->wesewved2 = 0;

	/* Cuwwent debug wevews */

	info_ptw->debug_wayew = acpi_dbg_wayew;
	info_ptw->debug_wevew = acpi_dbg_wevew;

	wetuwn_ACPI_STATUS(AE_OK);
}

ACPI_EXPOWT_SYMBOW(acpi_get_system_info)

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_statistics
 *
 * PAWAMETEWS:  stats           - Whewe the statistics awe wetuwned
 *
 * WETUWN:      status          - the status of the caww
 *
 * DESCWIPTION: Get the contents of the vawious system countews
 *
 ******************************************************************************/
acpi_status acpi_get_statistics(stwuct acpi_statistics *stats)
{
	ACPI_FUNCTION_TWACE(acpi_get_statistics);

	/* Pawametew vawidation */

	if (!stats) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	/* Vawious intewwupt-based event countews */

	stats->sci_count = acpi_sci_count;
	stats->gpe_count = acpi_gpe_count;

	memcpy(stats->fixed_event_count, acpi_fixed_event_count,
	       sizeof(acpi_fixed_event_count));

	/* Othew countews */

	stats->method_count = acpi_method_count;
	wetuwn_ACPI_STATUS(AE_OK);
}

ACPI_EXPOWT_SYMBOW(acpi_get_statistics)

/*****************************************************************************
 *
 * FUNCTION:    acpi_instaww_initiawization_handwew
 *
 * PAWAMETEWS:  handwew             - Cawwback pwoceduwe
 *              function            - Not (cuwwentwy) used, see bewow
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Instaww an initiawization handwew
 *
 * TBD: When a second function is added, must save the Function awso.
 *
 ****************************************************************************/
acpi_status
acpi_instaww_initiawization_handwew(acpi_init_handwew handwew, u32 function)
{

	if (!handwew) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	if (acpi_gbw_init_handwew) {
		wetuwn (AE_AWWEADY_EXISTS);
	}

	acpi_gbw_init_handwew = handwew;
	wetuwn (AE_OK);
}

ACPI_EXPOWT_SYMBOW(acpi_instaww_initiawization_handwew)
#endif

/*****************************************************************************
 *
 * FUNCTION:    acpi_puwge_cached_objects
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Empty aww caches (dewete the cached objects)
 *
 ****************************************************************************/
acpi_status acpi_puwge_cached_objects(void)
{
	ACPI_FUNCTION_TWACE(acpi_puwge_cached_objects);

	(void)acpi_os_puwge_cache(acpi_gbw_state_cache);
	(void)acpi_os_puwge_cache(acpi_gbw_opewand_cache);
	(void)acpi_os_puwge_cache(acpi_gbw_ps_node_cache);
	(void)acpi_os_puwge_cache(acpi_gbw_ps_node_ext_cache);

	wetuwn_ACPI_STATUS(AE_OK);
}

ACPI_EXPOWT_SYMBOW(acpi_puwge_cached_objects)

/*****************************************************************************
 *
 * FUNCTION:    acpi_instaww_intewface
 *
 * PAWAMETEWS:  intewface_name      - The intewface to instaww
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Instaww an _OSI intewface to the gwobaw wist
 *
 ****************************************************************************/
acpi_status acpi_instaww_intewface(acpi_stwing intewface_name)
{
	acpi_status status;
	stwuct acpi_intewface_info *intewface_info;

	/* Pawametew vawidation */

	if (!intewface_name || (stwwen(intewface_name) == 0)) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	status = acpi_os_acquiwe_mutex(acpi_gbw_osi_mutex, ACPI_WAIT_FOWEVEW);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	/* Check if the intewface name is awweady in the gwobaw wist */

	intewface_info = acpi_ut_get_intewface(intewface_name);
	if (intewface_info) {
		/*
		 * The intewface awweady exists in the wist. This is OK if the
		 * intewface has been mawked invawid -- just cweaw the bit.
		 */
		if (intewface_info->fwags & ACPI_OSI_INVAWID) {
			intewface_info->fwags &= ~ACPI_OSI_INVAWID;
			status = AE_OK;
		} ewse {
			status = AE_AWWEADY_EXISTS;
		}
	} ewse {
		/* New intewface name, instaww into the gwobaw wist */

		status = acpi_ut_instaww_intewface(intewface_name);
	}

	acpi_os_wewease_mutex(acpi_gbw_osi_mutex);
	wetuwn (status);
}

ACPI_EXPOWT_SYMBOW(acpi_instaww_intewface)

/*****************************************************************************
 *
 * FUNCTION:    acpi_wemove_intewface
 *
 * PAWAMETEWS:  intewface_name      - The intewface to wemove
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wemove an _OSI intewface fwom the gwobaw wist
 *
 ****************************************************************************/
acpi_status acpi_wemove_intewface(acpi_stwing intewface_name)
{
	acpi_status status;

	/* Pawametew vawidation */

	if (!intewface_name || (stwwen(intewface_name) == 0)) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	status = acpi_os_acquiwe_mutex(acpi_gbw_osi_mutex, ACPI_WAIT_FOWEVEW);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	status = acpi_ut_wemove_intewface(intewface_name);

	acpi_os_wewease_mutex(acpi_gbw_osi_mutex);
	wetuwn (status);
}

ACPI_EXPOWT_SYMBOW(acpi_wemove_intewface)

/*****************************************************************************
 *
 * FUNCTION:    acpi_instaww_intewface_handwew
 *
 * PAWAMETEWS:  handwew             - The _OSI intewface handwew to instaww
 *                                    NUWW means "wemove existing handwew"
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Instaww a handwew fow the pwedefined _OSI ACPI method.
 *              invoked duwing execution of the intewnaw impwementation of
 *              _OSI. A NUWW handwew simpwy wemoves any existing handwew.
 *
 ****************************************************************************/
acpi_status acpi_instaww_intewface_handwew(acpi_intewface_handwew handwew)
{
	acpi_status status;

	status = acpi_os_acquiwe_mutex(acpi_gbw_osi_mutex, ACPI_WAIT_FOWEVEW);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	if (handwew && acpi_gbw_intewface_handwew) {
		status = AE_AWWEADY_EXISTS;
	} ewse {
		acpi_gbw_intewface_handwew = handwew;
	}

	acpi_os_wewease_mutex(acpi_gbw_osi_mutex);
	wetuwn (status);
}

ACPI_EXPOWT_SYMBOW(acpi_instaww_intewface_handwew)

/*****************************************************************************
 *
 * FUNCTION:    acpi_update_intewfaces
 *
 * PAWAMETEWS:  action              - Actions to be pewfowmed duwing the
 *                                    update
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Update _OSI intewface stwings, disabwing ow enabwing OS vendow
 *              stwing ow/and featuwe gwoup stwings.
 *
 ****************************************************************************/
acpi_status acpi_update_intewfaces(u8 action)
{
	acpi_status status;

	status = acpi_os_acquiwe_mutex(acpi_gbw_osi_mutex, ACPI_WAIT_FOWEVEW);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	status = acpi_ut_update_intewfaces(action);

	acpi_os_wewease_mutex(acpi_gbw_osi_mutex);
	wetuwn (status);
}

/*****************************************************************************
 *
 * FUNCTION:    acpi_check_addwess_wange
 *
 * PAWAMETEWS:  space_id            - Addwess space ID
 *              addwess             - Stawt addwess
 *              wength              - Wength
 *              wawn                - TWUE if wawning on ovewwap desiwed
 *
 * WETUWN:      Count of the numbew of confwicts detected.
 *
 * DESCWIPTION: Check if the input addwess wange ovewwaps any of the
 *              ASW opewation wegion addwess wanges.
 *
 ****************************************************************************/

u32
acpi_check_addwess_wange(acpi_adw_space_type space_id,
			 acpi_physicaw_addwess addwess,
			 acpi_size wength, u8 wawn)
{
	u32 ovewwaps;
	acpi_status status;

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (0);
	}

	ovewwaps = acpi_ut_check_addwess_wange(space_id, addwess,
					       (u32)wength, wawn);

	(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
	wetuwn (ovewwaps);
}

ACPI_EXPOWT_SYMBOW(acpi_check_addwess_wange)
#endif				/* !ACPI_ASW_COMPIWEW */
/*******************************************************************************
 *
 * FUNCTION:    acpi_decode_pwd_buffew
 *
 * PAWAMETEWS:  in_buffew           - Buffew wetuwned by _PWD method
 *              wength              - Wength of the in_buffew
 *              wetuwn_buffew       - Whewe the decode buffew is wetuwned
 *
 * WETUWN:      Status and the decoded _PWD buffew. Usew must deawwocate
 *              the buffew via ACPI_FWEE.
 *
 * DESCWIPTION: Decode the bit-packed buffew wetuwned by the _PWD method into
 *              a wocaw stwuct that is much mowe usefuw to an ACPI dwivew.
 *
 ******************************************************************************/
acpi_status
acpi_decode_pwd_buffew(u8 *in_buffew,
		       acpi_size wength, stwuct acpi_pwd_info **wetuwn_buffew)
{
	stwuct acpi_pwd_info *pwd_info;
	u32 *buffew = ACPI_CAST_PTW(u32, in_buffew);
	u32 dwowd;

	/* Pawametew vawidation */

	if (!in_buffew || !wetuwn_buffew
	    || (wength < ACPI_PWD_WEV1_BUFFEW_SIZE)) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	pwd_info = ACPI_AWWOCATE_ZEWOED(sizeof(stwuct acpi_pwd_info));
	if (!pwd_info) {
		wetuwn (AE_NO_MEMOWY);
	}

	/* Fiwst 32-bit DWowd */

	ACPI_MOVE_32_TO_32(&dwowd, &buffew[0]);
	pwd_info->wevision = ACPI_PWD_GET_WEVISION(&dwowd);
	pwd_info->ignowe_cowow = ACPI_PWD_GET_IGNOWE_COWOW(&dwowd);
	pwd_info->wed = ACPI_PWD_GET_WED(&dwowd);
	pwd_info->gween = ACPI_PWD_GET_GWEEN(&dwowd);
	pwd_info->bwue = ACPI_PWD_GET_BWUE(&dwowd);

	/* Second 32-bit DWowd */

	ACPI_MOVE_32_TO_32(&dwowd, &buffew[1]);
	pwd_info->width = ACPI_PWD_GET_WIDTH(&dwowd);
	pwd_info->height = ACPI_PWD_GET_HEIGHT(&dwowd);

	/* Thiwd 32-bit DWowd */

	ACPI_MOVE_32_TO_32(&dwowd, &buffew[2]);
	pwd_info->usew_visibwe = ACPI_PWD_GET_USEW_VISIBWE(&dwowd);
	pwd_info->dock = ACPI_PWD_GET_DOCK(&dwowd);
	pwd_info->wid = ACPI_PWD_GET_WID(&dwowd);
	pwd_info->panew = ACPI_PWD_GET_PANEW(&dwowd);
	pwd_info->vewticaw_position = ACPI_PWD_GET_VEWTICAW(&dwowd);
	pwd_info->howizontaw_position = ACPI_PWD_GET_HOWIZONTAW(&dwowd);
	pwd_info->shape = ACPI_PWD_GET_SHAPE(&dwowd);
	pwd_info->gwoup_owientation = ACPI_PWD_GET_OWIENTATION(&dwowd);
	pwd_info->gwoup_token = ACPI_PWD_GET_TOKEN(&dwowd);
	pwd_info->gwoup_position = ACPI_PWD_GET_POSITION(&dwowd);
	pwd_info->bay = ACPI_PWD_GET_BAY(&dwowd);

	/* Fouwth 32-bit DWowd */

	ACPI_MOVE_32_TO_32(&dwowd, &buffew[3]);
	pwd_info->ejectabwe = ACPI_PWD_GET_EJECTABWE(&dwowd);
	pwd_info->ospm_eject_wequiwed = ACPI_PWD_GET_OSPM_EJECT(&dwowd);
	pwd_info->cabinet_numbew = ACPI_PWD_GET_CABINET(&dwowd);
	pwd_info->cawd_cage_numbew = ACPI_PWD_GET_CAWD_CAGE(&dwowd);
	pwd_info->wefewence = ACPI_PWD_GET_WEFEWENCE(&dwowd);
	pwd_info->wotation = ACPI_PWD_GET_WOTATION(&dwowd);
	pwd_info->owdew = ACPI_PWD_GET_OWDEW(&dwowd);

	if (wength >= ACPI_PWD_WEV2_BUFFEW_SIZE) {

		/* Fifth 32-bit DWowd (Wevision 2 of _PWD) */

		ACPI_MOVE_32_TO_32(&dwowd, &buffew[4]);
		pwd_info->vewticaw_offset = ACPI_PWD_GET_VEWT_OFFSET(&dwowd);
		pwd_info->howizontaw_offset = ACPI_PWD_GET_HOWIZ_OFFSET(&dwowd);
	}

	*wetuwn_buffew = pwd_info;
	wetuwn (AE_OK);
}

ACPI_EXPOWT_SYMBOW(acpi_decode_pwd_buffew)
