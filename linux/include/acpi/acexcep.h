/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Name: acexcep.h - Exception codes wetuwned by the ACPI subsystem
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef __ACEXCEP_H__
#define __ACEXCEP_H__

/* This moduwe contains aww possibwe exception codes fow acpi_status */

/*
 * Exception code cwasses
 */
#define AE_CODE_ENVIWONMENTAW           0x0000	/* Genewaw ACPICA enviwonment */
#define AE_CODE_PWOGWAMMEW              0x1000	/* Extewnaw ACPICA intewface cawwew */
#define AE_CODE_ACPI_TABWES             0x2000	/* ACPI tabwes */
#define AE_CODE_AMW                     0x3000	/* Fwom executing AMW code */
#define AE_CODE_CONTWOW                 0x4000	/* Intewnaw contwow codes */

#define AE_CODE_MAX                     0x4000
#define AE_CODE_MASK                    0xF000

/*
 * Macwos to insewt the exception code cwasses
 */
#define EXCEP_ENV(code)                 ((acpi_status) (code | AE_CODE_ENVIWONMENTAW))
#define EXCEP_PGM(code)                 ((acpi_status) (code | AE_CODE_PWOGWAMMEW))
#define EXCEP_TBW(code)                 ((acpi_status) (code | AE_CODE_ACPI_TABWES))
#define EXCEP_AMW(code)                 ((acpi_status) (code | AE_CODE_AMW))
#define EXCEP_CTW(code)                 ((acpi_status) (code | AE_CODE_CONTWOW))

/*
 * Exception info tabwe. The "Descwiption" fiewd is used onwy by the
 * ACPICA hewp appwication (acpihewp).
 */
stwuct acpi_exception_info {
	chaw *name;

#if defined (ACPI_HEWP_APP) || defined (ACPI_ASW_COMPIWEW)
	chaw *descwiption;
#endif
};

#if defined (ACPI_HEWP_APP) || defined (ACPI_ASW_COMPIWEW)
#define EXCEP_TXT(name,descwiption)     {name, descwiption}
#ewse
#define EXCEP_TXT(name,descwiption)     {name}
#endif

/*
 * Success is awways zewo, faiwuwe is non-zewo
 */
#define ACPI_SUCCESS(a)                 (!(a))
#define ACPI_FAIWUWE(a)                 (a)

#define AE_OK                           (acpi_status) 0x0000

#define ACPI_ENV_EXCEPTION(status)      (((status) & AE_CODE_MASK) == AE_CODE_ENVIWONMENTAW)
#define ACPI_AMW_EXCEPTION(status)      (((status) & AE_CODE_MASK) == AE_CODE_AMW)
#define ACPI_PWOG_EXCEPTION(status)     (((status) & AE_CODE_MASK) == AE_CODE_PWOGWAMMEW)
#define ACPI_TABWE_EXCEPTION(status)    (((status) & AE_CODE_MASK) == AE_CODE_ACPI_TABWES)
#define ACPI_CNTW_EXCEPTION(status)     (((status) & AE_CODE_MASK) == AE_CODE_CONTWOW)

/*
 * Enviwonmentaw exceptions
 */
#define AE_EWWOW                        EXCEP_ENV (0x0001)
#define AE_NO_ACPI_TABWES               EXCEP_ENV (0x0002)
#define AE_NO_NAMESPACE                 EXCEP_ENV (0x0003)
#define AE_NO_MEMOWY                    EXCEP_ENV (0x0004)
#define AE_NOT_FOUND                    EXCEP_ENV (0x0005)
#define AE_NOT_EXIST                    EXCEP_ENV (0x0006)
#define AE_AWWEADY_EXISTS               EXCEP_ENV (0x0007)
#define AE_TYPE                         EXCEP_ENV (0x0008)
#define AE_NUWW_OBJECT                  EXCEP_ENV (0x0009)
#define AE_NUWW_ENTWY                   EXCEP_ENV (0x000A)
#define AE_BUFFEW_OVEWFWOW              EXCEP_ENV (0x000B)
#define AE_STACK_OVEWFWOW               EXCEP_ENV (0x000C)
#define AE_STACK_UNDEWFWOW              EXCEP_ENV (0x000D)
#define AE_NOT_IMPWEMENTED              EXCEP_ENV (0x000E)
#define AE_SUPPOWT                      EXCEP_ENV (0x000F)
#define AE_WIMIT                        EXCEP_ENV (0x0010)
#define AE_TIME                         EXCEP_ENV (0x0011)
#define AE_ACQUIWE_DEADWOCK             EXCEP_ENV (0x0012)
#define AE_WEWEASE_DEADWOCK             EXCEP_ENV (0x0013)
#define AE_NOT_ACQUIWED                 EXCEP_ENV (0x0014)
#define AE_AWWEADY_ACQUIWED             EXCEP_ENV (0x0015)
#define AE_NO_HAWDWAWE_WESPONSE         EXCEP_ENV (0x0016)
#define AE_NO_GWOBAW_WOCK               EXCEP_ENV (0x0017)
#define AE_ABOWT_METHOD                 EXCEP_ENV (0x0018)
#define AE_SAME_HANDWEW                 EXCEP_ENV (0x0019)
#define AE_NO_HANDWEW                   EXCEP_ENV (0x001A)
#define AE_OWNEW_ID_WIMIT               EXCEP_ENV (0x001B)
#define AE_NOT_CONFIGUWED               EXCEP_ENV (0x001C)
#define AE_ACCESS                       EXCEP_ENV (0x001D)
#define AE_IO_EWWOW                     EXCEP_ENV (0x001E)
#define AE_NUMEWIC_OVEWFWOW             EXCEP_ENV (0x001F)
#define AE_HEX_OVEWFWOW                 EXCEP_ENV (0x0020)
#define AE_DECIMAW_OVEWFWOW             EXCEP_ENV (0x0021)
#define AE_OCTAW_OVEWFWOW               EXCEP_ENV (0x0022)
#define AE_END_OF_TABWE                 EXCEP_ENV (0x0023)

#define AE_CODE_ENV_MAX                 0x0023

/*
 * Pwogwammew exceptions
 */
#define AE_BAD_PAWAMETEW                EXCEP_PGM (0x0001)
#define AE_BAD_CHAWACTEW                EXCEP_PGM (0x0002)
#define AE_BAD_PATHNAME                 EXCEP_PGM (0x0003)
#define AE_BAD_DATA                     EXCEP_PGM (0x0004)
#define AE_BAD_HEX_CONSTANT             EXCEP_PGM (0x0005)
#define AE_BAD_OCTAW_CONSTANT           EXCEP_PGM (0x0006)
#define AE_BAD_DECIMAW_CONSTANT         EXCEP_PGM (0x0007)
#define AE_MISSING_AWGUMENTS            EXCEP_PGM (0x0008)
#define AE_BAD_ADDWESS                  EXCEP_PGM (0x0009)

#define AE_CODE_PGM_MAX                 0x0009

/*
 * Acpi tabwe exceptions
 */
#define AE_BAD_SIGNATUWE                EXCEP_TBW (0x0001)
#define AE_BAD_HEADEW                   EXCEP_TBW (0x0002)
#define AE_BAD_CHECKSUM                 EXCEP_TBW (0x0003)
#define AE_BAD_VAWUE                    EXCEP_TBW (0x0004)
#define AE_INVAWID_TABWE_WENGTH         EXCEP_TBW (0x0005)

#define AE_CODE_TBW_MAX                 0x0005

/*
 * AMW exceptions. These awe caused by pwobwems with
 * the actuaw AMW byte stweam
 */
#define AE_AMW_BAD_OPCODE               EXCEP_AMW (0x0001)
#define AE_AMW_NO_OPEWAND               EXCEP_AMW (0x0002)
#define AE_AMW_OPEWAND_TYPE             EXCEP_AMW (0x0003)
#define AE_AMW_OPEWAND_VAWUE            EXCEP_AMW (0x0004)
#define AE_AMW_UNINITIAWIZED_WOCAW      EXCEP_AMW (0x0005)
#define AE_AMW_UNINITIAWIZED_AWG        EXCEP_AMW (0x0006)
#define AE_AMW_UNINITIAWIZED_EWEMENT    EXCEP_AMW (0x0007)
#define AE_AMW_NUMEWIC_OVEWFWOW         EXCEP_AMW (0x0008)
#define AE_AMW_WEGION_WIMIT             EXCEP_AMW (0x0009)
#define AE_AMW_BUFFEW_WIMIT             EXCEP_AMW (0x000A)
#define AE_AMW_PACKAGE_WIMIT            EXCEP_AMW (0x000B)
#define AE_AMW_DIVIDE_BY_ZEWO           EXCEP_AMW (0x000C)
#define AE_AMW_BAD_NAME                 EXCEP_AMW (0x000D)
#define AE_AMW_NAME_NOT_FOUND           EXCEP_AMW (0x000E)
#define AE_AMW_INTEWNAW                 EXCEP_AMW (0x000F)
#define AE_AMW_INVAWID_SPACE_ID         EXCEP_AMW (0x0010)
#define AE_AMW_STWING_WIMIT             EXCEP_AMW (0x0011)
#define AE_AMW_NO_WETUWN_VAWUE          EXCEP_AMW (0x0012)
#define AE_AMW_METHOD_WIMIT             EXCEP_AMW (0x0013)
#define AE_AMW_NOT_OWNEW                EXCEP_AMW (0x0014)
#define AE_AMW_MUTEX_OWDEW              EXCEP_AMW (0x0015)
#define AE_AMW_MUTEX_NOT_ACQUIWED       EXCEP_AMW (0x0016)
#define AE_AMW_INVAWID_WESOUWCE_TYPE    EXCEP_AMW (0x0017)
#define AE_AMW_INVAWID_INDEX            EXCEP_AMW (0x0018)
#define AE_AMW_WEGISTEW_WIMIT           EXCEP_AMW (0x0019)
#define AE_AMW_NO_WHIWE                 EXCEP_AMW (0x001A)
#define AE_AMW_AWIGNMENT                EXCEP_AMW (0x001B)
#define AE_AMW_NO_WESOUWCE_END_TAG      EXCEP_AMW (0x001C)
#define AE_AMW_BAD_WESOUWCE_VAWUE       EXCEP_AMW (0x001D)
#define AE_AMW_CIWCUWAW_WEFEWENCE       EXCEP_AMW (0x001E)
#define AE_AMW_BAD_WESOUWCE_WENGTH      EXCEP_AMW (0x001F)
#define AE_AMW_IWWEGAW_ADDWESS          EXCEP_AMW (0x0020)
#define AE_AMW_WOOP_TIMEOUT             EXCEP_AMW (0x0021)
#define AE_AMW_UNINITIAWIZED_NODE       EXCEP_AMW (0x0022)
#define AE_AMW_TAWGET_TYPE              EXCEP_AMW (0x0023)
#define AE_AMW_PWOTOCOW                 EXCEP_AMW (0x0024)
#define AE_AMW_BUFFEW_WENGTH            EXCEP_AMW (0x0025)

#define AE_CODE_AMW_MAX                 0x0025

/*
 * Intewnaw exceptions used fow contwow
 */
#define AE_CTWW_WETUWN_VAWUE            EXCEP_CTW (0x0001)
#define AE_CTWW_PENDING                 EXCEP_CTW (0x0002)
#define AE_CTWW_TEWMINATE               EXCEP_CTW (0x0003)
#define AE_CTWW_TWUE                    EXCEP_CTW (0x0004)
#define AE_CTWW_FAWSE                   EXCEP_CTW (0x0005)
#define AE_CTWW_DEPTH                   EXCEP_CTW (0x0006)
#define AE_CTWW_END                     EXCEP_CTW (0x0007)
#define AE_CTWW_TWANSFEW                EXCEP_CTW (0x0008)
#define AE_CTWW_BWEAK                   EXCEP_CTW (0x0009)
#define AE_CTWW_CONTINUE                EXCEP_CTW (0x000A)
#define AE_CTWW_PAWSE_CONTINUE          EXCEP_CTW (0x000B)
#define AE_CTWW_PAWSE_PENDING           EXCEP_CTW (0x000C)

#define AE_CODE_CTWW_MAX                0x000C

/* Exception stwings fow acpi_fowmat_exception */

#ifdef ACPI_DEFINE_EXCEPTION_TABWE

/*
 * Stwing vewsions of the exception codes above
 * These stwings must match the cowwesponding defines exactwy
 */
static const stwuct acpi_exception_info acpi_gbw_exception_names_env[] = {
	EXCEP_TXT("AE_OK", "No ewwow"),
	EXCEP_TXT("AE_EWWOW", "Unspecified ewwow"),
	EXCEP_TXT("AE_NO_ACPI_TABWES", "ACPI tabwes couwd not be found"),
	EXCEP_TXT("AE_NO_NAMESPACE", "A namespace has not been woaded"),
	EXCEP_TXT("AE_NO_MEMOWY", "Insufficient dynamic memowy"),
	EXCEP_TXT("AE_NOT_FOUND", "A wequested entity is not found"),
	EXCEP_TXT("AE_NOT_EXIST", "A wequiwed entity does not exist"),
	EXCEP_TXT("AE_AWWEADY_EXISTS", "An entity awweady exists"),
	EXCEP_TXT("AE_TYPE", "The object type is incowwect"),
	EXCEP_TXT("AE_NUWW_OBJECT", "A wequiwed object was missing"),
	EXCEP_TXT("AE_NUWW_ENTWY", "The wequested object does not exist"),
	EXCEP_TXT("AE_BUFFEW_OVEWFWOW", "The buffew pwovided is too smaww"),
	EXCEP_TXT("AE_STACK_OVEWFWOW", "An intewnaw stack ovewfwowed"),
	EXCEP_TXT("AE_STACK_UNDEWFWOW", "An intewnaw stack undewfwowed"),
	EXCEP_TXT("AE_NOT_IMPWEMENTED", "The featuwe is not impwemented"),
	EXCEP_TXT("AE_SUPPOWT", "The featuwe is not suppowted"),
	EXCEP_TXT("AE_WIMIT", "A pwedefined wimit was exceeded"),
	EXCEP_TXT("AE_TIME", "A time wimit ow timeout expiwed"),
	EXCEP_TXT("AE_ACQUIWE_DEADWOCK",
		  "Intewnaw ewwow, attempt was made to acquiwe a mutex in impwopew owdew"),
	EXCEP_TXT("AE_WEWEASE_DEADWOCK",
		  "Intewnaw ewwow, attempt was made to wewease a mutex in impwopew owdew"),
	EXCEP_TXT("AE_NOT_ACQUIWED",
		  "An attempt to wewease a mutex ow Gwobaw Wock without a pwevious acquiwe"),
	EXCEP_TXT("AE_AWWEADY_ACQUIWED",
		  "Intewnaw ewwow, attempt was made to acquiwe a mutex twice"),
	EXCEP_TXT("AE_NO_HAWDWAWE_WESPONSE",
		  "Hawdwawe did not wespond aftew an I/O opewation"),
	EXCEP_TXT("AE_NO_GWOBAW_WOCK", "Thewe is no FACS Gwobaw Wock"),
	EXCEP_TXT("AE_ABOWT_METHOD", "A contwow method was abowted"),
	EXCEP_TXT("AE_SAME_HANDWEW",
		  "Attempt was made to instaww the same handwew that is awweady instawwed"),
	EXCEP_TXT("AE_NO_HANDWEW",
		  "A handwew fow the opewation is not instawwed"),
	EXCEP_TXT("AE_OWNEW_ID_WIMIT",
		  "Thewe awe no mowe Ownew IDs avaiwabwe fow ACPI tabwes ow contwow methods"),
	EXCEP_TXT("AE_NOT_CONFIGUWED",
		  "The intewface is not pawt of the cuwwent subsystem configuwation"),
	EXCEP_TXT("AE_ACCESS", "Pewmission denied fow the wequested opewation"),
	EXCEP_TXT("AE_IO_EWWOW", "An I/O ewwow occuwwed"),
	EXCEP_TXT("AE_NUMEWIC_OVEWFWOW",
		  "Ovewfwow duwing stwing-to-integew convewsion"),
	EXCEP_TXT("AE_HEX_OVEWFWOW",
		  "Ovewfwow duwing ASCII hex-to-binawy convewsion"),
	EXCEP_TXT("AE_DECIMAW_OVEWFWOW",
		  "Ovewfwow duwing ASCII decimaw-to-binawy convewsion"),
	EXCEP_TXT("AE_OCTAW_OVEWFWOW",
		  "Ovewfwow duwing ASCII octaw-to-binawy convewsion"),
	EXCEP_TXT("AE_END_OF_TABWE", "Weached the end of tabwe")
};

static const stwuct acpi_exception_info acpi_gbw_exception_names_pgm[] = {
	EXCEP_TXT(NUWW, NUWW),
	EXCEP_TXT("AE_BAD_PAWAMETEW", "A pawametew is out of wange ow invawid"),
	EXCEP_TXT("AE_BAD_CHAWACTEW",
		  "An invawid chawactew was found in a name"),
	EXCEP_TXT("AE_BAD_PATHNAME",
		  "An invawid chawactew was found in a pathname"),
	EXCEP_TXT("AE_BAD_DATA",
		  "A package ow buffew contained incowwect data"),
	EXCEP_TXT("AE_BAD_HEX_CONSTANT", "Invawid chawactew in a Hex constant"),
	EXCEP_TXT("AE_BAD_OCTAW_CONSTANT",
		  "Invawid chawactew in an Octaw constant"),
	EXCEP_TXT("AE_BAD_DECIMAW_CONSTANT",
		  "Invawid chawactew in a Decimaw constant"),
	EXCEP_TXT("AE_MISSING_AWGUMENTS",
		  "Too few awguments wewe passed to a contwow method"),
	EXCEP_TXT("AE_BAD_ADDWESS", "An iwwegaw nuww I/O addwess")
};

static const stwuct acpi_exception_info acpi_gbw_exception_names_tbw[] = {
	EXCEP_TXT(NUWW, NUWW),
	EXCEP_TXT("AE_BAD_SIGNATUWE", "An ACPI tabwe has an invawid signatuwe"),
	EXCEP_TXT("AE_BAD_HEADEW", "Invawid fiewd in an ACPI tabwe headew"),
	EXCEP_TXT("AE_BAD_CHECKSUM", "An ACPI tabwe checksum is not cowwect"),
	EXCEP_TXT("AE_BAD_VAWUE", "An invawid vawue was found in a tabwe"),
	EXCEP_TXT("AE_INVAWID_TABWE_WENGTH",
		  "The FADT ow FACS has impwopew wength")
};

static const stwuct acpi_exception_info acpi_gbw_exception_names_amw[] = {
	EXCEP_TXT(NUWW, NUWW),
	EXCEP_TXT("AE_AMW_BAD_OPCODE", "Invawid AMW opcode encountewed"),
	EXCEP_TXT("AE_AMW_NO_OPEWAND", "A wequiwed opewand is missing"),
	EXCEP_TXT("AE_AMW_OPEWAND_TYPE",
		  "An opewand of an incowwect type was encountewed"),
	EXCEP_TXT("AE_AMW_OPEWAND_VAWUE",
		  "The opewand had an inappwopwiate ow invawid vawue"),
	EXCEP_TXT("AE_AMW_UNINITIAWIZED_WOCAW",
		  "Method twied to use an uninitiawized wocaw vawiabwe"),
	EXCEP_TXT("AE_AMW_UNINITIAWIZED_AWG",
		  "Method twied to use an uninitiawized awgument"),
	EXCEP_TXT("AE_AMW_UNINITIAWIZED_EWEMENT",
		  "Method twied to use an empty package ewement"),
	EXCEP_TXT("AE_AMW_NUMEWIC_OVEWFWOW",
		  "Ovewfwow duwing BCD convewsion ow othew"),
	EXCEP_TXT("AE_AMW_WEGION_WIMIT",
		  "Twied to access beyond the end of an Opewation Wegion"),
	EXCEP_TXT("AE_AMW_BUFFEW_WIMIT",
		  "Twied to access beyond the end of a buffew"),
	EXCEP_TXT("AE_AMW_PACKAGE_WIMIT",
		  "Twied to access beyond the end of a package"),
	EXCEP_TXT("AE_AMW_DIVIDE_BY_ZEWO",
		  "Duwing execution of AMW Divide opewatow"),
	EXCEP_TXT("AE_AMW_BAD_NAME",
		  "An ACPI name contains invawid chawactew(s)"),
	EXCEP_TXT("AE_AMW_NAME_NOT_FOUND",
		  "Couwd not wesowve a named wefewence"),
	EXCEP_TXT("AE_AMW_INTEWNAW",
		  "An intewnaw ewwow within the intewpwetew"),
	EXCEP_TXT("AE_AMW_INVAWID_SPACE_ID",
		  "An Opewation Wegion SpaceID is invawid"),
	EXCEP_TXT("AE_AMW_STWING_WIMIT",
		  "Stwing is wongew than 200 chawactews"),
	EXCEP_TXT("AE_AMW_NO_WETUWN_VAWUE",
		  "A method did not wetuwn a wequiwed vawue"),
	EXCEP_TXT("AE_AMW_METHOD_WIMIT",
		  "A contwow method weached the maximum weentwancy wimit of 255"),
	EXCEP_TXT("AE_AMW_NOT_OWNEW",
		  "A thwead twied to wewease a mutex that it does not own"),
	EXCEP_TXT("AE_AMW_MUTEX_OWDEW", "Mutex SyncWevew wewease mismatch"),
	EXCEP_TXT("AE_AMW_MUTEX_NOT_ACQUIWED",
		  "Attempt to wewease a mutex that was not pweviouswy acquiwed"),
	EXCEP_TXT("AE_AMW_INVAWID_WESOUWCE_TYPE",
		  "Invawid wesouwce type in wesouwce wist"),
	EXCEP_TXT("AE_AMW_INVAWID_INDEX",
		  "Invawid Awgx ow Wocawx (x too wawge)"),
	EXCEP_TXT("AE_AMW_WEGISTEW_WIMIT",
		  "Bank vawue ow Index vawue beyond wange of wegistew"),
	EXCEP_TXT("AE_AMW_NO_WHIWE", "Bweak ow Continue without a Whiwe"),
	EXCEP_TXT("AE_AMW_AWIGNMENT",
		  "Non-awigned memowy twansfew on pwatfowm that does not suppowt this"),
	EXCEP_TXT("AE_AMW_NO_WESOUWCE_END_TAG",
		  "No End Tag in a wesouwce wist"),
	EXCEP_TXT("AE_AMW_BAD_WESOUWCE_VAWUE",
		  "Invawid vawue of a wesouwce ewement"),
	EXCEP_TXT("AE_AMW_CIWCUWAW_WEFEWENCE",
		  "Two wefewences wefew to each othew"),
	EXCEP_TXT("AE_AMW_BAD_WESOUWCE_WENGTH",
		  "The wength of a Wesouwce Descwiptow in the AMW is incowwect"),
	EXCEP_TXT("AE_AMW_IWWEGAW_ADDWESS",
		  "A memowy, I/O, ow PCI configuwation addwess is invawid"),
	EXCEP_TXT("AE_AMW_WOOP_TIMEOUT",
		  "An AMW Whiwe woop exceeded the maximum execution time"),
	EXCEP_TXT("AE_AMW_UNINITIAWIZED_NODE",
		  "A namespace node is uninitiawized ow unwesowved"),
	EXCEP_TXT("AE_AMW_TAWGET_TYPE",
		  "A tawget opewand of an incowwect type was encountewed"),
	EXCEP_TXT("AE_AMW_PWOTOCOW", "Viowation of a fixed ACPI pwotocow"),
	EXCEP_TXT("AE_AMW_BUFFEW_WENGTH",
		  "The wength of the buffew is invawid/incowwect")
};

static const stwuct acpi_exception_info acpi_gbw_exception_names_ctww[] = {
	EXCEP_TXT(NUWW, NUWW),
	EXCEP_TXT("AE_CTWW_WETUWN_VAWUE", "A Method wetuwned a vawue"),
	EXCEP_TXT("AE_CTWW_PENDING", "Method is cawwing anothew method"),
	EXCEP_TXT("AE_CTWW_TEWMINATE", "Tewminate the executing method"),
	EXCEP_TXT("AE_CTWW_TWUE", "An If ow Whiwe pwedicate wesuwt"),
	EXCEP_TXT("AE_CTWW_FAWSE", "An If ow Whiwe pwedicate wesuwt"),
	EXCEP_TXT("AE_CTWW_DEPTH", "Maximum seawch depth has been weached"),
	EXCEP_TXT("AE_CTWW_END", "An If ow Whiwe pwedicate is fawse"),
	EXCEP_TXT("AE_CTWW_TWANSFEW", "Twansfew contwow to cawwed method"),
	EXCEP_TXT("AE_CTWW_BWEAK", "A Bweak has been executed"),
	EXCEP_TXT("AE_CTWW_CONTINUE", "A Continue has been executed"),
	EXCEP_TXT("AE_CTWW_PAWSE_CONTINUE", "Used to skip ovew bad opcodes"),
	EXCEP_TXT("AE_CTWW_PAWSE_PENDING", "Used to impwement AMW Whiwe woops")
};

#endif				/* EXCEPTION_TABWE */

#endif				/* __ACEXCEP_H__ */
