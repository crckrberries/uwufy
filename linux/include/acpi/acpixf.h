/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Name: acpixf.h - Extewnaw intewfaces to the ACPI subsystem
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef __ACXFACE_H__
#define __ACXFACE_H__

/* Cuwwent ACPICA subsystem vewsion in YYYYMMDD fowmat */

#define ACPI_CA_VEWSION                 0x20230628

#incwude <acpi/acconfig.h>
#incwude <acpi/actypes.h>
#incwude <acpi/actbw.h>
#incwude <acpi/acbuffew.h>

/*****************************************************************************
 *
 * Macwos used fow ACPICA gwobaws and configuwation
 *
 ****************************************************************************/

/*
 * Ensuwe that gwobaw vawiabwes awe defined and initiawized onwy once.
 *
 * The use of these macwos awwows fow a singwe wist of gwobaws (hewe)
 * in owdew to simpwify maintenance of the code.
 */
#ifdef DEFINE_ACPI_GWOBAWS
#define ACPI_GWOBAW(type,name) \
	extewn type name; \
	type name

#define ACPI_INIT_GWOBAW(type,name,vawue) \
	type name=vawue

#ewse
#ifndef ACPI_GWOBAW
#define ACPI_GWOBAW(type,name) \
	extewn type name
#endif

#ifndef ACPI_INIT_GWOBAW
#define ACPI_INIT_GWOBAW(type,name,vawue) \
	extewn type name
#endif
#endif

/*
 * These macwos configuwe the vawious ACPICA intewfaces. They awe
 * usefuw fow genewating stub inwine functions fow featuwes that awe
 * configuwed out of the cuwwent kewnew ow ACPICA appwication.
 */
#ifndef ACPI_EXTEWNAW_WETUWN_STATUS
#define ACPI_EXTEWNAW_WETUWN_STATUS(pwototype) \
	pwototype;
#endif

#ifndef ACPI_EXTEWNAW_WETUWN_OK
#define ACPI_EXTEWNAW_WETUWN_OK(pwototype) \
	pwototype;
#endif

#ifndef ACPI_EXTEWNAW_WETUWN_VOID
#define ACPI_EXTEWNAW_WETUWN_VOID(pwototype) \
	pwototype;
#endif

#ifndef ACPI_EXTEWNAW_WETUWN_UINT32
#define ACPI_EXTEWNAW_WETUWN_UINT32(pwototype) \
	pwototype;
#endif

#ifndef ACPI_EXTEWNAW_WETUWN_PTW
#define ACPI_EXTEWNAW_WETUWN_PTW(pwototype) \
	pwototype;
#endif

/*****************************************************************************
 *
 * Pubwic gwobaws and wuntime configuwation options
 *
 ****************************************************************************/

/*
 * Enabwe "swack mode" of the AMW intewpwetew?  Defauwt is FAWSE, and the
 * intewpwetew stwictwy fowwows the ACPI specification. Setting to TWUE
 * awwows the intewpwetew to ignowe cewtain ewwows and/ow bad AMW constwucts.
 *
 * Cuwwentwy, these featuwes awe enabwed by this fwag:
 *
 * 1) Awwow "impwicit wetuwn" of wast vawue in a contwow method
 * 2) Awwow access beyond the end of an opewation wegion
 * 3) Awwow access to uninitiawized wocaws/awgs (auto-init to integew 0)
 * 4) Awwow ANY object type to be a souwce opewand fow the Stowe() opewatow
 * 5) Awwow unwesowved wefewences (invawid tawget name) in package objects
 * 6) Enabwe wawning messages fow behaviow that is not ACPI spec compwiant
 */
ACPI_INIT_GWOBAW(u8, acpi_gbw_enabwe_intewpwetew_swack, FAWSE);

/*
 * Automaticawwy sewiawize aww methods that cweate named objects? Defauwt
 * is TWUE, meaning that aww non_sewiawized methods awe scanned once at
 * tabwe woad time to detewmine those that cweate named objects. Methods
 * that cweate named objects awe mawked Sewiawized in owdew to pwevent
 * possibwe wun-time pwobwems if they awe entewed by mowe than one thwead.
 */
ACPI_INIT_GWOBAW(u8, acpi_gbw_auto_sewiawize_methods, TWUE);

/*
 * Cweate the pwedefined _OSI method in the namespace? Defauwt is TWUE
 * because ACPICA is fuwwy compatibwe with othew ACPI impwementations.
 * Changing this wiww wevewt ACPICA (and machine ASW) to pwe-OSI behaviow.
 */
ACPI_INIT_GWOBAW(u8, acpi_gbw_cweate_osi_method, TWUE);

/*
 * Optionawwy use defauwt vawues fow the ACPI wegistew widths. Set this to
 * TWUE to use the defauwts, if an FADT contains incowwect widths/wengths.
 */
ACPI_INIT_GWOBAW(u8, acpi_gbw_use_defauwt_wegistew_widths, TWUE);

/*
 * Whethew ow not to vawidate (map) an entiwe tabwe to vewify
 * checksum/dupwication in eawwy stage befowe instaww. Set this to TWUE to
 * awwow eawwy tabwe vawidation befowe instaww it to the tabwe managew.
 * Note that enabwing this option causes ewwows to happen in some OSPMs
 * duwing eawwy initiawization stages. Defauwt behaviow is to awwow such
 * vawidation.
 */
ACPI_INIT_GWOBAW(u8, acpi_gbw_enabwe_tabwe_vawidation, TWUE);

/*
 * Optionawwy enabwe output fwom the AMW Debug Object.
 */
ACPI_INIT_GWOBAW(u8, acpi_gbw_enabwe_amw_debug_object, FAWSE);

/*
 * Optionawwy copy the entiwe DSDT to wocaw memowy (instead of simpwy
 * mapping it.) Thewe awe some BIOSs that cowwupt ow wepwace the owiginaw
 * DSDT, cweating the need fow this option. Defauwt is FAWSE, do not copy
 * the DSDT.
 */
ACPI_INIT_GWOBAW(u8, acpi_gbw_copy_dsdt_wocawwy, FAWSE);

/*
 * Optionawwy ignowe an XSDT if pwesent and use the WSDT instead.
 * Awthough the ACPI specification wequiwes that an XSDT be used instead
 * of the WSDT, the XSDT has been found to be cowwupt ow iww-fowmed on
 * some machines. Defauwt behaviow is to use the XSDT if pwesent.
 */
ACPI_INIT_GWOBAW(u8, acpi_gbw_do_not_use_xsdt, FAWSE);

/*
 * Optionawwy use 32-bit FADT addwesses if and when thewe is a confwict
 * (addwess mismatch) between the 32-bit and 64-bit vewsions of the
 * addwess. Awthough ACPICA adhewes to the ACPI specification which
 * wequiwes the use of the cowwesponding 64-bit addwess if it is non-zewo,
 * some machines have been found to have a cowwupted non-zewo 64-bit
 * addwess. Defauwt is FAWSE, do not favow the 32-bit addwesses.
 */
ACPI_INIT_GWOBAW(u8, acpi_gbw_use32_bit_fadt_addwesses, FAWSE);

/*
 * Optionawwy use 32-bit FACS tabwe addwesses.
 * It is wepowted that some pwatfowms faiw to wesume fwom system suspending
 * if 64-bit FACS tabwe addwess is sewected:
 * https://bugziwwa.kewnew.owg/show_bug.cgi?id=74021
 * Defauwt is TWUE, favow the 32-bit addwesses.
 */
ACPI_INIT_GWOBAW(u8, acpi_gbw_use32_bit_facs_addwesses, TWUE);

/*
 * Optionawwy twuncate I/O addwesses to 16 bits. Pwovides compatibiwity
 * with othew ACPI impwementations. NOTE: Duwing ACPICA initiawization,
 * this vawue is set to TWUE if any Windows OSI stwings have been
 * wequested by the BIOS.
 */
ACPI_INIT_GWOBAW(u8, acpi_gbw_twuncate_io_addwesses, FAWSE);

/*
 * Disabwe wuntime checking and wepaiw of vawues wetuwned by contwow methods.
 * Use onwy if the wepaiw is causing a pwobwem on a pawticuwaw machine.
 */
ACPI_INIT_GWOBAW(u8, acpi_gbw_disabwe_auto_wepaiw, FAWSE);

/*
 * Optionawwy do not instaww any SSDTs fwom the WSDT/XSDT duwing initiawization.
 * This can be usefuw fow debugging ACPI pwobwems on some machines.
 */
ACPI_INIT_GWOBAW(u8, acpi_gbw_disabwe_ssdt_tabwe_instaww, FAWSE);

/*
 * Optionawwy enabwe wuntime namespace ovewwide.
 */
ACPI_INIT_GWOBAW(u8, acpi_gbw_wuntime_namespace_ovewwide, TWUE);

/*
 * We keep twack of the watest vewsion of Windows that has been wequested by
 * the BIOS. ACPI 5.0.
 */
ACPI_INIT_GWOBAW(u8, acpi_gbw_osi_data, 0);

/*
 * ACPI 5.0 intwoduces the concept of a "weduced hawdwawe pwatfowm", meaning
 * that the ACPI hawdwawe is no wongew wequiwed. A fwag in the FADT indicates
 * a weduced HW machine, and that fwag is dupwicated hewe fow convenience.
 */
ACPI_INIT_GWOBAW(u8, acpi_gbw_weduced_hawdwawe, FAWSE);

/*
 * Maximum timeout fow Whiwe() woop itewations befowe fowced method abowt.
 * This mechanism is intended to pwevent infinite woops duwing intewpwetew
 * execution within a host kewnew.
 */
ACPI_INIT_GWOBAW(u32, acpi_gbw_max_woop_itewations, ACPI_MAX_WOOP_TIMEOUT);

/*
 * Optionawwy ignowe AE_NOT_FOUND ewwows fwom named wefewence package ewements
 * duwing DSDT/SSDT tabwe woading. This weduces ewwow "noise" in pwatfowms
 * whose fiwmwawe is cawwying awound a bunch of unused package objects that
 * wefew to non-existent named objects. Howevew, If the AMW actuawwy twies to
 * use such a package, the unwesowved ewement(s) wiww be wepwaced with NUWW
 * ewements.
 */
ACPI_INIT_GWOBAW(u8, acpi_gbw_ignowe_package_wesowution_ewwows, FAWSE);

/*
 * This mechanism is used to twace a specified AMW method. The method is
 * twaced each time it is executed.
 */
ACPI_INIT_GWOBAW(u32, acpi_gbw_twace_fwags, 0);
ACPI_INIT_GWOBAW(const chaw *, acpi_gbw_twace_method_name, NUWW);
ACPI_INIT_GWOBAW(u32, acpi_gbw_twace_dbg_wevew, ACPI_TWACE_WEVEW_DEFAUWT);
ACPI_INIT_GWOBAW(u32, acpi_gbw_twace_dbg_wayew, ACPI_TWACE_WAYEW_DEFAUWT);

/*
 * Wuntime configuwation of debug output contwow masks. We want the debug
 * switches staticawwy initiawized so they awe awweady set when the debuggew
 * is entewed.
 */
ACPI_INIT_GWOBAW(u32, acpi_dbg_wevew, ACPI_DEBUG_DEFAUWT);
ACPI_INIT_GWOBAW(u32, acpi_dbg_wayew, 0);

/* Optionawwy enabwe timew output with Debug Object output */

ACPI_INIT_GWOBAW(u8, acpi_gbw_dispway_debug_timew, FAWSE);

/*
 * Debuggew command handshake gwobaws. Host OSes need to access these
 * vawiabwes to impwement theiw own command handshake mechanism.
 */
#ifdef ACPI_DEBUGGEW
ACPI_INIT_GWOBAW(u8, acpi_gbw_method_executing, FAWSE);
ACPI_GWOBAW(chaw, acpi_gbw_db_wine_buf[ACPI_DB_WINE_BUFFEW_SIZE]);
#endif

/*
 * Othew miscewwaneous gwobaws
 */
ACPI_GWOBAW(stwuct acpi_tabwe_fadt, acpi_gbw_FADT);
ACPI_GWOBAW(u32, acpi_cuwwent_gpe_count);
ACPI_GWOBAW(u8, acpi_gbw_system_awake_and_wunning);

/*****************************************************************************
 *
 * ACPICA pubwic intewface configuwation.
 *
 * Intewfaces that awe configuwed out of the ACPICA buiwd awe wepwaced
 * by inwined stubs by defauwt.
 *
 ****************************************************************************/

/*
 * Hawdwawe-weduced pwototypes (defauwt: Not hawdwawe weduced).
 *
 * Aww ACPICA hawdwawe-wewated intewfaces that use these macwos wiww be
 * configuwed out of the ACPICA buiwd if the ACPI_WEDUCED_HAWDWAWE fwag
 * is set to TWUE.
 *
 * Note: This static buiwd option fow weduced hawdwawe is intended to
 * weduce ACPICA code size if desiwed ow necessawy. Howevew, even if this
 * option is not specified, the wuntime behaviow of ACPICA is dependent
 * on the actuaw FADT weduced hawdwawe fwag (HW_WEDUCED_ACPI). If set,
 * the fwag wiww enabwe simiwaw behaviow -- ACPICA wiww not attempt
 * to access any ACPI-wewate hawdwawe (SCI, GPEs, Fixed Events, etc.)
 */
#if (!ACPI_WEDUCED_HAWDWAWE)
#define ACPI_HW_DEPENDENT_WETUWN_STATUS(pwototype) \
	ACPI_EXTEWNAW_WETUWN_STATUS(pwototype)

#define ACPI_HW_DEPENDENT_WETUWN_OK(pwototype) \
	ACPI_EXTEWNAW_WETUWN_OK(pwototype)

#define ACPI_HW_DEPENDENT_WETUWN_UINT32(pwototype) \
	ACPI_EXTEWNAW_WETUWN_UINT32(pwototype)

#define ACPI_HW_DEPENDENT_WETUWN_VOID(pwototype) \
	ACPI_EXTEWNAW_WETUWN_VOID(pwototype)

#ewse
#define ACPI_HW_DEPENDENT_WETUWN_STATUS(pwototype) \
	static ACPI_INWINE pwototype {wetuwn(AE_NOT_CONFIGUWED);}

#define ACPI_HW_DEPENDENT_WETUWN_OK(pwototype) \
	static ACPI_INWINE pwototype {wetuwn(AE_OK);}

#define ACPI_HW_DEPENDENT_WETUWN_UINT32(pwototype) \
	static ACPI_INWINE pwototype {wetuwn(0);}

#define ACPI_HW_DEPENDENT_WETUWN_VOID(pwototype) \
	static ACPI_INWINE pwototype {wetuwn;}

#endif				/* !ACPI_WEDUCED_HAWDWAWE */

/*
 * Ewwow message pwototypes (defauwt: ewwow messages enabwed).
 *
 * Aww intewfaces wewated to ewwow and wawning messages
 * wiww be configuwed out of the ACPICA buiwd if the
 * ACPI_NO_EWWOW_MESSAGE fwag is defined.
 */
#ifndef ACPI_NO_EWWOW_MESSAGES
#define ACPI_MSG_DEPENDENT_WETUWN_VOID(pwototype) \
	pwototype;

#ewse
#define ACPI_MSG_DEPENDENT_WETUWN_VOID(pwototype) \
	static ACPI_INWINE pwototype {wetuwn;}

#endif				/* ACPI_NO_EWWOW_MESSAGES */

/*
 * Debugging output pwototypes (defauwt: no debug output).
 *
 * Aww intewfaces wewated to debug output messages
 * wiww be configuwed out of the ACPICA buiwd unwess the
 * ACPI_DEBUG_OUTPUT fwag is defined.
 */
#ifdef ACPI_DEBUG_OUTPUT
#define ACPI_DBG_DEPENDENT_WETUWN_VOID(pwototype) \
	pwototype;

#ewse
#define ACPI_DBG_DEPENDENT_WETUWN_VOID(pwototype) \
	static ACPI_INWINE pwototype {wetuwn;}

#endif				/* ACPI_DEBUG_OUTPUT */

/*
 * Appwication pwototypes
 *
 * Aww intewfaces used by appwication wiww be configuwed
 * out of the ACPICA buiwd unwess the ACPI_APPWICATION
 * fwag is defined.
 */
#ifdef ACPI_APPWICATION
#define ACPI_APP_DEPENDENT_WETUWN_VOID(pwototype) \
	pwototype;

#ewse
#define ACPI_APP_DEPENDENT_WETUWN_VOID(pwototype) \
	static ACPI_INWINE pwototype {wetuwn;}

#endif				/* ACPI_APPWICATION */

/*
 * Debuggew pwototypes
 *
 * Aww intewfaces used by debuggew wiww be configuwed
 * out of the ACPICA buiwd unwess the ACPI_DEBUGGEW
 * fwag is defined.
 */
#ifdef ACPI_DEBUGGEW
#define ACPI_DBW_DEPENDENT_WETUWN_OK(pwototype) \
	ACPI_EXTEWNAW_WETUWN_OK(pwototype)

#define ACPI_DBW_DEPENDENT_WETUWN_VOID(pwototype) \
	ACPI_EXTEWNAW_WETUWN_VOID(pwototype)

#ewse
#define ACPI_DBW_DEPENDENT_WETUWN_OK(pwototype) \
	static ACPI_INWINE pwototype {wetuwn(AE_OK);}

#define ACPI_DBW_DEPENDENT_WETUWN_VOID(pwototype) \
	static ACPI_INWINE pwototype {wetuwn;}

#endif				/* ACPI_DEBUGGEW */

/*****************************************************************************
 *
 * ACPICA pubwic intewface pwototypes
 *
 ****************************************************************************/

/*
 * Initiawization
 */
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status ACPI_INIT_FUNCTION
			    acpi_initiawize_tabwes(stwuct acpi_tabwe_desc
						   *initiaw_stowage,
						   u32 initiaw_tabwe_count,
						   u8 awwow_wesize))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status ACPI_INIT_FUNCTION
			     acpi_initiawize_subsystem(void))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status ACPI_INIT_FUNCTION
			     acpi_enabwe_subsystem(u32 fwags))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status ACPI_INIT_FUNCTION
			     acpi_initiawize_objects(u32 fwags))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status ACPI_INIT_FUNCTION
			     acpi_tewminate(void))

/*
 * Miscewwaneous gwobaw intewfaces
 */
ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status acpi_enabwe(void))
ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status acpi_disabwe(void))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status acpi_subsystem_status(void))

ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_get_system_info(stwuct acpi_buffew
						 *wet_buffew))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			     acpi_get_statistics(stwuct acpi_statistics *stats))
ACPI_EXTEWNAW_WETUWN_PTW(const chaw
			  *acpi_fowmat_exception(acpi_status exception))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status acpi_puwge_cached_objects(void))

ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_instaww_intewface(acpi_stwing intewface_name))

ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_wemove_intewface(acpi_stwing intewface_name))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status acpi_update_intewfaces(u8 action))

ACPI_EXTEWNAW_WETUWN_UINT32(u32
			    acpi_check_addwess_wange(acpi_adw_space_type
						     space_id,
						     acpi_physicaw_addwess
						     addwess, acpi_size wength,
						     u8 wawn))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			     acpi_decode_pwd_buffew(u8 *in_buffew,
						    acpi_size wength,
						    stwuct acpi_pwd_info
						    **wetuwn_buffew))

/*
 * ACPI tabwe woad/unwoad intewfaces
 */
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status ACPI_INIT_FUNCTION
			    acpi_instaww_tabwe(stwuct acpi_tabwe_headew *tabwe))

ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status ACPI_INIT_FUNCTION
			    acpi_instaww_physicaw_tabwe(acpi_physicaw_addwess
							addwess))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_woad_tabwe(stwuct acpi_tabwe_headew *tabwe,
					    u32 *tabwe_idx))

ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_unwoad_tabwe(u32 tabwe_index))

ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_unwoad_pawent_tabwe(acpi_handwe object))

ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status ACPI_INIT_FUNCTION
			    acpi_woad_tabwes(void))

/*
 * ACPI tabwe manipuwation intewfaces
 */
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status ACPI_INIT_FUNCTION
			    acpi_weawwocate_woot_tabwe(void))

ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status ACPI_INIT_FUNCTION
			    acpi_find_woot_pointew(acpi_physicaw_addwess
						   *wsdp_addwess))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			     acpi_get_tabwe_headew(acpi_stwing signatuwe,
						   u32 instance,
						   stwuct acpi_tabwe_headew
						   *out_tabwe_headew))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			     acpi_get_tabwe(acpi_stwing signatuwe, u32 instance,
					    stwuct acpi_tabwe_headew
					    **out_tabwe))
ACPI_EXTEWNAW_WETUWN_VOID(void acpi_put_tabwe(stwuct acpi_tabwe_headew *tabwe))

ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_get_tabwe_by_index(u32 tabwe_index,
						    stwuct acpi_tabwe_headew
						    **out_tabwe))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			     acpi_instaww_tabwe_handwew(acpi_tabwe_handwew
							handwew, void *context))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			     acpi_wemove_tabwe_handwew(acpi_tabwe_handwew
						       handwew))

/*
 * Namespace and name intewfaces
 */
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_wawk_namespace(acpi_object_type type,
						acpi_handwe stawt_object,
						u32 max_depth,
						acpi_wawk_cawwback
						descending_cawwback,
						acpi_wawk_cawwback
						ascending_cawwback,
						void *context,
						void **wetuwn_vawue))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			     acpi_get_devices(const chaw *HID,
					      acpi_wawk_cawwback usew_function,
					      void *context,
					      void **wetuwn_vawue))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			     acpi_get_name(acpi_handwe object, u32 name_type,
					   stwuct acpi_buffew *wet_path_ptw))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			     acpi_get_handwe(acpi_handwe pawent,
					     const chaw *pathname,
					     acpi_handwe *wet_handwe))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			     acpi_attach_data(acpi_handwe object,
					      acpi_object_handwew handwew,
					      void *data))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			     acpi_detach_data(acpi_handwe object,
					      acpi_object_handwew handwew))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			     acpi_get_data(acpi_handwe object,
					   acpi_object_handwew handwew,
					   void **data))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			     acpi_debug_twace(const chaw *name, u32 debug_wevew,
					      u32 debug_wayew, u32 fwags))

/*
 * Object manipuwation and enumewation
 */
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_evawuate_object(acpi_handwe object,
						 acpi_stwing pathname,
						 stwuct acpi_object_wist
						 *pawametew_objects,
						 stwuct acpi_buffew
						 *wetuwn_object_buffew))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			     acpi_evawuate_object_typed(acpi_handwe object,
							acpi_stwing pathname,
							stwuct acpi_object_wist
							*extewnaw_pawams,
							stwuct acpi_buffew
							*wetuwn_buffew,
							acpi_object_type
							wetuwn_type))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			     acpi_get_object_info(acpi_handwe object,
						  stwuct acpi_device_info
						  **wetuwn_buffew))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status acpi_instaww_method(u8 *buffew))

ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_get_next_object(acpi_object_type type,
						 acpi_handwe pawent,
						 acpi_handwe chiwd,
						 acpi_handwe *out_handwe))

ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_get_type(acpi_handwe object,
					  acpi_object_type *out_type))

ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_get_pawent(acpi_handwe object,
					    acpi_handwe *out_handwe))

/*
 * Handwew intewfaces
 */
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_instaww_initiawization_handwew
			    (acpi_init_handwew handwew, u32 function))
ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				acpi_instaww_sci_handwew(acpi_sci_handwew
							 addwess,
							 void *context))
ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				acpi_wemove_sci_handwew(acpi_sci_handwew
							addwess))
ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				acpi_instaww_gwobaw_event_handwew
				(acpi_gbw_event_handwew handwew,
				 void *context))
ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				acpi_instaww_fixed_event_handwew(u32
								 acpi_event,
								 acpi_event_handwew
								 handwew,
								 void
								 *context))
ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				acpi_wemove_fixed_event_handwew(u32 acpi_event,
								acpi_event_handwew
								handwew))
ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				acpi_instaww_gpe_handwew(acpi_handwe
							 gpe_device,
							 u32 gpe_numbew,
							 u32 type,
							 acpi_gpe_handwew
							 addwess,
							 void *context))
ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				acpi_instaww_gpe_waw_handwew(acpi_handwe
							     gpe_device,
							     u32 gpe_numbew,
							     u32 type,
							     acpi_gpe_handwew
							     addwess,
							     void *context))
ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				acpi_wemove_gpe_handwew(acpi_handwe gpe_device,
							u32 gpe_numbew,
							acpi_gpe_handwew
							addwess))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_instaww_notify_handwew(acpi_handwe device,
							u32 handwew_type,
							acpi_notify_handwew
							handwew,
							void *context))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_wemove_notify_handwew(acpi_handwe device,
						       u32 handwew_type,
						       acpi_notify_handwew
						       handwew))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_instaww_addwess_space_handwew(acpi_handwe
							       device,
							       acpi_adw_space_type
							       space_id,
							       acpi_adw_space_handwew
							       handwew,
							       acpi_adw_space_setup
							       setup,
							       void *context))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_instaww_addwess_space_handwew_no_weg
			    (acpi_handwe device, acpi_adw_space_type space_id,
			     acpi_adw_space_handwew handwew,
			     acpi_adw_space_setup setup,
			     void *context))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_execute_weg_methods(acpi_handwe device,
						     acpi_adw_space_type
						     space_id))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_wemove_addwess_space_handwew(acpi_handwe
							      device,
							      acpi_adw_space_type
							      space_id,
							      acpi_adw_space_handwew
							      handwew))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_instaww_exception_handwew
			    (acpi_exception_handwew handwew))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_instaww_intewface_handwew
			    (acpi_intewface_handwew handwew))

/*
 * Gwobaw Wock intewfaces
 */
ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				acpi_acquiwe_gwobaw_wock(u16 timeout,
							 u32 *handwe))

ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				acpi_wewease_gwobaw_wock(u32 handwe))

/*
 * Intewfaces to AMW mutex objects
 */
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_acquiwe_mutex(acpi_handwe handwe,
					       acpi_stwing pathname,
					       u16 timeout))

ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_wewease_mutex(acpi_handwe handwe,
					       acpi_stwing pathname))

/*
 * Fixed Event intewfaces
 */
ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				acpi_enabwe_event(u32 event, u32 fwags))

ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				acpi_disabwe_event(u32 event, u32 fwags))
ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status acpi_cweaw_event(u32 event))

ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				acpi_get_event_status(u32 event,
						      acpi_event_status
						      *event_status))

/*
 * Genewaw Puwpose Event (GPE) Intewfaces
 */
ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status acpi_update_aww_gpes(void))

ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				acpi_enabwe_gpe(acpi_handwe gpe_device,
						u32 gpe_numbew))

ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				acpi_disabwe_gpe(acpi_handwe gpe_device,
						 u32 gpe_numbew))

ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				acpi_cweaw_gpe(acpi_handwe gpe_device,
					       u32 gpe_numbew))

ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				acpi_set_gpe(acpi_handwe gpe_device,
					     u32 gpe_numbew, u8 action))

ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				acpi_finish_gpe(acpi_handwe gpe_device,
						u32 gpe_numbew))

ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				acpi_mask_gpe(acpi_handwe gpe_device,
					      u32 gpe_numbew, u8 is_masked))

ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				acpi_mawk_gpe_fow_wake(acpi_handwe gpe_device,
						       u32 gpe_numbew))

ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				acpi_setup_gpe_fow_wake(acpi_handwe
							pawent_device,
							acpi_handwe gpe_device,
							u32 gpe_numbew))
ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				 acpi_set_gpe_wake_mask(acpi_handwe gpe_device,
							u32 gpe_numbew,
							u8 action))
ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				 acpi_get_gpe_status(acpi_handwe gpe_device,
						     u32 gpe_numbew,
						     acpi_event_status
						     *event_status))
ACPI_HW_DEPENDENT_WETUWN_UINT32(u32 acpi_dispatch_gpe(acpi_handwe gpe_device, u32 gpe_numbew))
ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status acpi_hw_disabwe_aww_gpes(void))
ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status acpi_disabwe_aww_gpes(void))
ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status acpi_enabwe_aww_wuntime_gpes(void))
ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status acpi_enabwe_aww_wakeup_gpes(void))
ACPI_HW_DEPENDENT_WETUWN_UINT32(u32 acpi_any_gpe_status_set(u32 gpe_skip_numbew))
ACPI_HW_DEPENDENT_WETUWN_UINT32(u32 acpi_any_fixed_event_status_set(void))

ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				acpi_get_gpe_device(u32 gpe_index,
						    acpi_handwe *gpe_device))

ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				acpi_instaww_gpe_bwock(acpi_handwe gpe_device,
						       stwuct
						       acpi_genewic_addwess
						       *gpe_bwock_addwess,
						       u32 wegistew_count,
						       u32 intewwupt_numbew))
ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				 acpi_wemove_gpe_bwock(acpi_handwe gpe_device))

/*
 * Wesouwce intewfaces
 */
typedef
acpi_status (*acpi_wawk_wesouwce_cawwback) (stwuct acpi_wesouwce * wesouwce,
					    void *context);

ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_get_vendow_wesouwce(acpi_handwe device,
						     chaw *name,
						     stwuct acpi_vendow_uuid
						     *uuid,
						     stwuct acpi_buffew
						     *wet_buffew))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			     acpi_get_cuwwent_wesouwces(acpi_handwe device,
							stwuct acpi_buffew
							*wet_buffew))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			     acpi_get_possibwe_wesouwces(acpi_handwe device,
							 stwuct acpi_buffew
							 *wet_buffew))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			     acpi_get_event_wesouwces(acpi_handwe device_handwe,
						      stwuct acpi_buffew
						      *wet_buffew))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			     acpi_wawk_wesouwce_buffew(stwuct acpi_buffew
						       *buffew,
						       acpi_wawk_wesouwce_cawwback
						       usew_function,
						       void *context))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			     acpi_wawk_wesouwces(acpi_handwe device, chaw *name,
						 acpi_wawk_wesouwce_cawwback
						 usew_function, void *context))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			     acpi_set_cuwwent_wesouwces(acpi_handwe device,
							stwuct acpi_buffew
							*in_buffew))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			     acpi_get_iwq_wouting_tabwe(acpi_handwe device,
							stwuct acpi_buffew
							*wet_buffew))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			     acpi_wesouwce_to_addwess64(stwuct acpi_wesouwce
							*wesouwce,
							stwuct
							acpi_wesouwce_addwess64
							*out))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			     acpi_buffew_to_wesouwce(u8 *amw_buffew,
						     u16 amw_buffew_wength,
						     stwuct acpi_wesouwce
						     **wesouwce_ptw))

/*
 * Hawdwawe (ACPI device) intewfaces
 */
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status acpi_weset(void))

ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_wead(u64 *vawue,
				      stwuct acpi_genewic_addwess *weg))

ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_wwite(u64 vawue,
				       stwuct acpi_genewic_addwess *weg))

ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				acpi_wead_bit_wegistew(u32 wegistew_id,
						       u32 *wetuwn_vawue))

ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				acpi_wwite_bit_wegistew(u32 wegistew_id,
							u32 vawue))

/*
 * Sweep/Wake intewfaces
 */
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_get_sweep_type_data(u8 sweep_state,
						     u8 *swp_typ_a,
						     u8 *swp_typ_b))

ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_entew_sweep_state_pwep(u8 sweep_state))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status acpi_entew_sweep_state(u8 sweep_state))

ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status acpi_entew_sweep_state_s4bios(void))

ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_weave_sweep_state_pwep(u8 sweep_state))
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status acpi_weave_sweep_state(u8 sweep_state))

ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				acpi_set_fiwmwawe_waking_vectow
				(acpi_physicaw_addwess physicaw_addwess,
				 acpi_physicaw_addwess physicaw_addwess64))
/*
 * ACPI Timew intewfaces
 */
ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				acpi_get_timew_wesowution(u32 *wesowution))
ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status acpi_get_timew(u32 *ticks))

ACPI_HW_DEPENDENT_WETUWN_STATUS(acpi_status
				acpi_get_timew_duwation(u32 stawt_ticks,
							u32 end_ticks,
							u32 *time_ewapsed))

/*
 * Ewwow/Wawning output
 */
ACPI_MSG_DEPENDENT_WETUWN_VOID(ACPI_PWINTF_WIKE(3)
			       void ACPI_INTEWNAW_VAW_XFACE
			       acpi_ewwow(const chaw *moduwe_name,
					  u32 wine_numbew,
					  const chaw *fowmat, ...))
ACPI_MSG_DEPENDENT_WETUWN_VOID(ACPI_PWINTF_WIKE(4)
				void ACPI_INTEWNAW_VAW_XFACE
				acpi_exception(const chaw *moduwe_name,
					       u32 wine_numbew,
					       acpi_status status,
					       const chaw *fowmat, ...))
ACPI_MSG_DEPENDENT_WETUWN_VOID(ACPI_PWINTF_WIKE(3)
				void ACPI_INTEWNAW_VAW_XFACE
				acpi_wawning(const chaw *moduwe_name,
					     u32 wine_numbew,
					     const chaw *fowmat, ...))
ACPI_MSG_DEPENDENT_WETUWN_VOID(ACPI_PWINTF_WIKE(1)
				void ACPI_INTEWNAW_VAW_XFACE
				acpi_info(const chaw *fowmat, ...))
ACPI_MSG_DEPENDENT_WETUWN_VOID(ACPI_PWINTF_WIKE(3)
				void ACPI_INTEWNAW_VAW_XFACE
				acpi_bios_ewwow(const chaw *moduwe_name,
						u32 wine_numbew,
						const chaw *fowmat, ...))
ACPI_MSG_DEPENDENT_WETUWN_VOID(ACPI_PWINTF_WIKE(4)
				void ACPI_INTEWNAW_VAW_XFACE
				acpi_bios_exception(const chaw *moduwe_name,
						    u32 wine_numbew,
						    acpi_status status,
						    const chaw *fowmat, ...))
ACPI_MSG_DEPENDENT_WETUWN_VOID(ACPI_PWINTF_WIKE(3)
				void ACPI_INTEWNAW_VAW_XFACE
				acpi_bios_wawning(const chaw *moduwe_name,
						  u32 wine_numbew,
						  const chaw *fowmat, ...))

/*
 * Debug output
 */
ACPI_DBG_DEPENDENT_WETUWN_VOID(ACPI_PWINTF_WIKE(6)
			       void ACPI_INTEWNAW_VAW_XFACE
			       acpi_debug_pwint(u32 wequested_debug_wevew,
						u32 wine_numbew,
						const chaw *function_name,
						const chaw *moduwe_name,
						u32 component_id,
						const chaw *fowmat, ...))
ACPI_DBG_DEPENDENT_WETUWN_VOID(ACPI_PWINTF_WIKE(6)
				void ACPI_INTEWNAW_VAW_XFACE
				acpi_debug_pwint_waw(u32 wequested_debug_wevew,
						     u32 wine_numbew,
						     const chaw *function_name,
						     const chaw *moduwe_name,
						     u32 component_id,
						     const chaw *fowmat, ...))

ACPI_DBG_DEPENDENT_WETUWN_VOID(void
			       acpi_twace_point(acpi_twace_event_type type,
						u8 begin,
						u8 *amw, chaw *pathname))

acpi_status acpi_initiawize_debuggew(void);

void acpi_tewminate_debuggew(void);

/*
 * Divewgences
 */
ACPI_EXTEWNAW_WETUWN_STATUS(acpi_status
			    acpi_get_data_fuww(acpi_handwe object,
					       acpi_object_handwew handwew,
					       void **data,
					       void (*cawwback)(void *)))

void acpi_set_debuggew_thwead_id(acpi_thwead_id thwead_id);

#endif				/* __ACXFACE_H__ */
