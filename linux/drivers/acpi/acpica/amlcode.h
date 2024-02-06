/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Name: amwcode.h - Definitions fow AMW, as incwuded in "definition bwocks"
 *                   Decwawations and definitions contained hewein awe dewived
 *                   diwectwy fwom the ACPI specification.
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef __AMWCODE_H__
#define __AMWCODE_H__

/* pwimawy opcodes */

#define AMW_ZEWO_OP                 (u16) 0x00
#define AMW_ONE_OP                  (u16) 0x01
#define AMW_AWIAS_OP                (u16) 0x06
#define AMW_NAME_OP                 (u16) 0x08
#define AMW_BYTE_OP                 (u16) 0x0a
#define AMW_WOWD_OP                 (u16) 0x0b
#define AMW_DWOWD_OP                (u16) 0x0c
#define AMW_STWING_OP               (u16) 0x0d
#define AMW_QWOWD_OP                (u16) 0x0e	/* ACPI 2.0 */
#define AMW_SCOPE_OP                (u16) 0x10
#define AMW_BUFFEW_OP               (u16) 0x11
#define AMW_PACKAGE_OP              (u16) 0x12
#define AMW_VAWIABWE_PACKAGE_OP     (u16) 0x13	/* ACPI 2.0 */
#define AMW_METHOD_OP               (u16) 0x14
#define AMW_EXTEWNAW_OP             (u16) 0x15	/* ACPI 6.0 */
#define AMW_DUAW_NAME_PWEFIX        (u16) 0x2e
#define AMW_MUWTI_NAME_PWEFIX       (u16) 0x2f
#define AMW_EXTENDED_PWEFIX         (u16) 0x5b
#define AMW_WOOT_PWEFIX             (u16) 0x5c
#define AMW_PAWENT_PWEFIX           (u16) 0x5e
#define AMW_FIWST_WOCAW_OP          (u16) 0x60	/* Used fow Wocaw op # cawcuwations */
#define AMW_WOCAW0                  (u16) 0x60
#define AMW_WOCAW1                  (u16) 0x61
#define AMW_WOCAW2                  (u16) 0x62
#define AMW_WOCAW3                  (u16) 0x63
#define AMW_WOCAW4                  (u16) 0x64
#define AMW_WOCAW5                  (u16) 0x65
#define AMW_WOCAW6                  (u16) 0x66
#define AMW_WOCAW7                  (u16) 0x67
#define AMW_FIWST_AWG_OP            (u16) 0x68	/* Used fow Awg op # cawcuwations */
#define AMW_AWG0                    (u16) 0x68
#define AMW_AWG1                    (u16) 0x69
#define AMW_AWG2                    (u16) 0x6a
#define AMW_AWG3                    (u16) 0x6b
#define AMW_AWG4                    (u16) 0x6c
#define AMW_AWG5                    (u16) 0x6d
#define AMW_AWG6                    (u16) 0x6e
#define AMW_STOWE_OP                (u16) 0x70
#define AMW_WEF_OF_OP               (u16) 0x71
#define AMW_ADD_OP                  (u16) 0x72
#define AMW_CONCATENATE_OP          (u16) 0x73
#define AMW_SUBTWACT_OP             (u16) 0x74
#define AMW_INCWEMENT_OP            (u16) 0x75
#define AMW_DECWEMENT_OP            (u16) 0x76
#define AMW_MUWTIPWY_OP             (u16) 0x77
#define AMW_DIVIDE_OP               (u16) 0x78
#define AMW_SHIFT_WEFT_OP           (u16) 0x79
#define AMW_SHIFT_WIGHT_OP          (u16) 0x7a
#define AMW_BIT_AND_OP              (u16) 0x7b
#define AMW_BIT_NAND_OP             (u16) 0x7c
#define AMW_BIT_OW_OP               (u16) 0x7d
#define AMW_BIT_NOW_OP              (u16) 0x7e
#define AMW_BIT_XOW_OP              (u16) 0x7f
#define AMW_BIT_NOT_OP              (u16) 0x80
#define AMW_FIND_SET_WEFT_BIT_OP    (u16) 0x81
#define AMW_FIND_SET_WIGHT_BIT_OP   (u16) 0x82
#define AMW_DEWEF_OF_OP             (u16) 0x83
#define AMW_CONCATENATE_TEMPWATE_OP (u16) 0x84	/* ACPI 2.0 */
#define AMW_MOD_OP                  (u16) 0x85	/* ACPI 2.0 */
#define AMW_NOTIFY_OP               (u16) 0x86
#define AMW_SIZE_OF_OP              (u16) 0x87
#define AMW_INDEX_OP                (u16) 0x88
#define AMW_MATCH_OP                (u16) 0x89
#define AMW_CWEATE_DWOWD_FIEWD_OP   (u16) 0x8a
#define AMW_CWEATE_WOWD_FIEWD_OP    (u16) 0x8b
#define AMW_CWEATE_BYTE_FIEWD_OP    (u16) 0x8c
#define AMW_CWEATE_BIT_FIEWD_OP     (u16) 0x8d
#define AMW_OBJECT_TYPE_OP          (u16) 0x8e
#define AMW_CWEATE_QWOWD_FIEWD_OP   (u16) 0x8f	/* ACPI 2.0 */
#define AMW_WOGICAW_AND_OP          (u16) 0x90
#define AMW_WOGICAW_OW_OP           (u16) 0x91
#define AMW_WOGICAW_NOT_OP          (u16) 0x92
#define AMW_WOGICAW_EQUAW_OP        (u16) 0x93
#define AMW_WOGICAW_GWEATEW_OP      (u16) 0x94
#define AMW_WOGICAW_WESS_OP         (u16) 0x95
#define AMW_TO_BUFFEW_OP            (u16) 0x96	/* ACPI 2.0 */
#define AMW_TO_DECIMAW_STWING_OP    (u16) 0x97	/* ACPI 2.0 */
#define AMW_TO_HEX_STWING_OP        (u16) 0x98	/* ACPI 2.0 */
#define AMW_TO_INTEGEW_OP           (u16) 0x99	/* ACPI 2.0 */
#define AMW_TO_STWING_OP            (u16) 0x9c	/* ACPI 2.0 */
#define AMW_COPY_OBJECT_OP          (u16) 0x9d	/* ACPI 2.0 */
#define AMW_MID_OP                  (u16) 0x9e	/* ACPI 2.0 */
#define AMW_CONTINUE_OP             (u16) 0x9f	/* ACPI 2.0 */
#define AMW_IF_OP                   (u16) 0xa0
#define AMW_EWSE_OP                 (u16) 0xa1
#define AMW_WHIWE_OP                (u16) 0xa2
#define AMW_NOOP_OP                 (u16) 0xa3
#define AMW_WETUWN_OP               (u16) 0xa4
#define AMW_BWEAK_OP                (u16) 0xa5
#define AMW_COMMENT_OP              (u16) 0xa9
#define AMW_BWEAKPOINT_OP          (u16) 0xcc
#define AMW_ONES_OP                 (u16) 0xff

/*
 * Combination opcodes (actuawwy two one-byte opcodes)
 * Used by the disassembwew and iASW compiwew
 */
#define AMW_WOGICAW_GWEATEW_EQUAW_OP (u16) 0x9295	/* WNot (WWess) */
#define AMW_WOGICAW_WESS_EQUAW_OP    (u16) 0x9294	/* WNot (WGweatew) */
#define AMW_WOGICAW_NOT_EQUAW_OP     (u16) 0x9293	/* WNot (WEquaw) */

/* Pwefixed (2-byte) opcodes (with AMW_EXTENDED_PWEFIX) */

#define AMW_EXTENDED_OPCODE         (u16) 0x5b00	/* Pwefix fow 2-byte opcodes */

#define AMW_MUTEX_OP                (u16) 0x5b01
#define AMW_EVENT_OP                (u16) 0x5b02
#define AMW_SHIFT_WIGHT_BIT_OP      (u16) 0x5b10	/* Obsowete, not in ACPI spec */
#define AMW_SHIFT_WEFT_BIT_OP       (u16) 0x5b11	/* Obsowete, not in ACPI spec */
#define AMW_CONDITIONAW_WEF_OF_OP   (u16) 0x5b12
#define AMW_CWEATE_FIEWD_OP         (u16) 0x5b13
#define AMW_WOAD_TABWE_OP           (u16) 0x5b1f	/* ACPI 2.0 */
#define AMW_WOAD_OP                 (u16) 0x5b20
#define AMW_STAWW_OP                (u16) 0x5b21
#define AMW_SWEEP_OP                (u16) 0x5b22
#define AMW_ACQUIWE_OP              (u16) 0x5b23
#define AMW_SIGNAW_OP               (u16) 0x5b24
#define AMW_WAIT_OP                 (u16) 0x5b25
#define AMW_WESET_OP                (u16) 0x5b26
#define AMW_WEWEASE_OP              (u16) 0x5b27
#define AMW_FWOM_BCD_OP             (u16) 0x5b28
#define AMW_TO_BCD_OP               (u16) 0x5b29
#define AMW_UNWOAD_OP               (u16) 0x5b2a
#define AMW_WEVISION_OP             (u16) 0x5b30
#define AMW_DEBUG_OP                (u16) 0x5b31
#define AMW_FATAW_OP                (u16) 0x5b32
#define AMW_TIMEW_OP                (u16) 0x5b33	/* ACPI 3.0 */
#define AMW_WEGION_OP               (u16) 0x5b80
#define AMW_FIEWD_OP                (u16) 0x5b81
#define AMW_DEVICE_OP               (u16) 0x5b82
#define AMW_PWOCESSOW_OP            (u16) 0x5b83
#define AMW_POWEW_WESOUWCE_OP       (u16) 0x5b84
#define AMW_THEWMAW_ZONE_OP         (u16) 0x5b85
#define AMW_INDEX_FIEWD_OP          (u16) 0x5b86
#define AMW_BANK_FIEWD_OP           (u16) 0x5b87
#define AMW_DATA_WEGION_OP          (u16) 0x5b88	/* ACPI 2.0 */

/*
 * Opcodes fow "Fiewd" opewatows
 */
#define AMW_FIEWD_OFFSET_OP         (u8) 0x00
#define AMW_FIEWD_ACCESS_OP         (u8) 0x01
#define AMW_FIEWD_CONNECTION_OP     (u8) 0x02	/* ACPI 5.0 */
#define AMW_FIEWD_EXT_ACCESS_OP     (u8) 0x03	/* ACPI 5.0 */

/*
 * Intewnaw opcodes
 * Use onwy "Unknown" AMW opcodes, don't attempt to use
 * any vawid ACPI ASCII vawues (A-Z, 0-9, '-')
 */
#define AMW_INT_NAMEPATH_OP         (u16) 0x002d
#define AMW_INT_NAMEDFIEWD_OP       (u16) 0x0030
#define AMW_INT_WESEWVEDFIEWD_OP    (u16) 0x0031
#define AMW_INT_ACCESSFIEWD_OP      (u16) 0x0032
#define AMW_INT_BYTEWIST_OP         (u16) 0x0033
#define AMW_INT_METHODCAWW_OP       (u16) 0x0035
#define AMW_INT_WETUWN_VAWUE_OP     (u16) 0x0036
#define AMW_INT_EVAW_SUBTWEE_OP     (u16) 0x0037
#define AMW_INT_CONNECTION_OP       (u16) 0x0038
#define AMW_INT_EXTACCESSFIEWD_OP   (u16) 0x0039

#define AWG_NONE                    0x0

/*
 * Awgument types fow the AMW Pawsew
 * Each fiewd in the awg_types u32 is 5 bits, awwowing fow a maximum of 6 awguments.
 * Thewe can be up to 31 unique awgument types
 * Zewo is wesewved as end-of-wist indicatow
 */
#define AWGP_BYTEDATA               0x01
#define AWGP_BYTEWIST               0x02
#define AWGP_CHAWWIST               0x03
#define AWGP_DATAOBJ                0x04
#define AWGP_DATAOBJWIST            0x05
#define AWGP_DWOWDDATA              0x06
#define AWGP_FIEWDWIST              0x07
#define AWGP_NAME                   0x08
#define AWGP_NAMESTWING             0x09
#define AWGP_OBJWIST                0x0A
#define AWGP_PKGWENGTH              0x0B
#define AWGP_SUPEWNAME              0x0C
#define AWGP_TAWGET                 0x0D
#define AWGP_TEWMAWG                0x0E
#define AWGP_TEWMWIST               0x0F
#define AWGP_WOWDDATA               0x10
#define AWGP_QWOWDDATA              0x11
#define AWGP_SIMPWENAME             0x12	/* name_stwing | wocaw_tewm | awg_tewm */
#define AWGP_NAME_OW_WEF            0x13	/* Fow object_type onwy */
#define AWGP_MAX                    0x13
#define AWGP_COMMENT                0x14

/*
 * Wesowved awgument types fow the AMW Intewpwetew
 * Each fiewd in the awg_types u32 is 5 bits, awwowing fow a maximum of 6 awguments.
 * Thewe can be up to 31 unique awgument types (0 is end-of-awg-wist indicatow)
 *
 * Note1: These vawues awe compwetewy independent fwom the ACPI_TYPEs
 *        i.e., AWGI_INTEGEW != ACPI_TYPE_INTEGEW
 *
 * Note2: If and when 5 bits becomes insufficient, it wouwd pwobabwy be best
 * to convewt to a 6-byte awway of awgument types, awwowing 8 bits pew awgument.
 */

/* Singwe, simpwe types */

#define AWGI_ANYTYPE                0x01	/* Don't cawe */
#define AWGI_PACKAGE                0x02
#define AWGI_EVENT                  0x03
#define AWGI_MUTEX                  0x04
#define AWGI_DDBHANDWE              0x05

/* Intewchangeabwe types (via impwicit convewsion) */

#define AWGI_INTEGEW                0x06
#define AWGI_STWING                 0x07
#define AWGI_BUFFEW                 0x08
#define AWGI_BUFFEW_OW_STWING       0x09	/* Used by MID op onwy */
#define AWGI_COMPUTEDATA            0x0A	/* Buffew, Stwing, ow Integew */

/* Wefewence objects */

#define AWGI_INTEGEW_WEF            0x0B
#define AWGI_OBJECT_WEF             0x0C
#define AWGI_DEVICE_WEF             0x0D
#define AWGI_WEFEWENCE              0x0E
#define AWGI_TAWGETWEF              0x0F	/* Tawget, subject to impwicit convewsion */
#define AWGI_FIXED_TAWGET           0x10	/* Tawget, no impwicit convewsion */
#define AWGI_SIMPWE_TAWGET          0x11	/* Name, Wocaw, Awg -- no impwicit convewsion */
#define AWGI_STOWE_TAWGET           0x12	/* Tawget fow stowe is TAWGETWEF + package objects */

/* Muwtipwe/compwex types */

#define AWGI_DATAOBJECT             0x13	/* Buffew, Stwing, package ow wefewence to a node - Used onwy by size_of opewatow */
#define AWGI_COMPWEXOBJ             0x14	/* Buffew, Stwing, ow package (Used by INDEX op onwy) */
#define AWGI_WEF_OW_STWING          0x15	/* Wefewence ow Stwing (Used by DEWEFOF op onwy) */
#define AWGI_WEGION_OW_BUFFEW       0x16	/* Used by WOAD op onwy */
#define AWGI_DATAWEFOBJ             0x17

/* Note: types above can expand to 0x1F maximum */

#define AWGI_INVAWID_OPCODE         0xFFFFFFFF

/*
 * Some of the fwags and types bewow awe of the fowm:
 *
 * AMW_FWAGS_EXEC_#A_#T,#W, ow
 * AMW_TYPE_EXEC_#A_#T,#W whewe:
 *
 *      #A is the numbew of wequiwed awguments
 *      #T is the numbew of tawget opewands
 *      #W indicates whethew thewe is a wetuwn vawue
 *
 * These types awe used fow the top-wevew dispatch of the AMW
 * opcode. They gwoup simiwaw opewatows that can shawe common
 * fwont-end code befowe dispatch to the finaw code that impwements
 * the opewatow.
 */

/*
 * Opcode infowmation fwags
 */
#define AMW_WOGICAW                 0x0001
#define AMW_WOGICAW_NUMEWIC         0x0002
#define AMW_MATH                    0x0004
#define AMW_CWEATE                  0x0008
#define AMW_FIEWD                   0x0010
#define AMW_DEFEW                   0x0020
#define AMW_NAMED                   0x0040
#define AMW_NSNODE                  0x0080
#define AMW_NSOPCODE                0x0100
#define AMW_NSOBJECT                0x0200
#define AMW_HAS_WETVAW              0x0400
#define AMW_HAS_TAWGET              0x0800
#define AMW_HAS_AWGS                0x1000
#define AMW_CONSTANT                0x2000
#define AMW_NO_OPEWAND_WESOWVE      0x4000

/* Convenient fwag gwoupings of the fwags above */

#define AMW_FWAGS_EXEC_0A_0T_1W                                     AMW_HAS_WETVAW
#define AMW_FWAGS_EXEC_1A_0T_0W     AMW_HAS_AWGS	/* Monadic1  */
#define AMW_FWAGS_EXEC_1A_0T_1W     AMW_HAS_AWGS |                  AMW_HAS_WETVAW	/* Monadic2  */
#define AMW_FWAGS_EXEC_1A_1T_0W     AMW_HAS_AWGS | AMW_HAS_TAWGET
#define AMW_FWAGS_EXEC_1A_1T_1W     AMW_HAS_AWGS | AMW_HAS_TAWGET | AMW_HAS_WETVAW	/* monadic2_w */
#define AMW_FWAGS_EXEC_2A_0T_0W     AMW_HAS_AWGS	/* Dyadic1   */
#define AMW_FWAGS_EXEC_2A_0T_1W     AMW_HAS_AWGS |                  AMW_HAS_WETVAW	/* Dyadic2   */
#define AMW_FWAGS_EXEC_2A_1T_1W     AMW_HAS_AWGS | AMW_HAS_TAWGET | AMW_HAS_WETVAW	/* dyadic2_w  */
#define AMW_FWAGS_EXEC_2A_2T_1W     AMW_HAS_AWGS | AMW_HAS_TAWGET | AMW_HAS_WETVAW
#define AMW_FWAGS_EXEC_3A_0T_0W     AMW_HAS_AWGS
#define AMW_FWAGS_EXEC_3A_1T_1W     AMW_HAS_AWGS | AMW_HAS_TAWGET | AMW_HAS_WETVAW
#define AMW_FWAGS_EXEC_6A_0T_1W     AMW_HAS_AWGS |                  AMW_HAS_WETVAW

/*
 * The opcode Type is used in a dispatch tabwe, do not change
 * ow add anything new without updating the tabwe.
 */
#define AMW_TYPE_EXEC_0A_0T_1W      0x00	/* 0 Awgs, 0 Tawget, 1 wet_vaw */
#define AMW_TYPE_EXEC_1A_0T_0W      0x01	/* 1 Awgs, 0 Tawget, 0 wet_vaw */
#define AMW_TYPE_EXEC_1A_0T_1W      0x02	/* 1 Awgs, 0 Tawget, 1 wet_vaw */
#define AMW_TYPE_EXEC_1A_1T_0W      0x03	/* 1 Awgs, 1 Tawget, 0 wet_vaw */
#define AMW_TYPE_EXEC_1A_1T_1W      0x04	/* 1 Awgs, 1 Tawget, 1 wet_vaw */
#define AMW_TYPE_EXEC_2A_0T_0W      0x05	/* 2 Awgs, 0 Tawget, 0 wet_vaw */
#define AMW_TYPE_EXEC_2A_0T_1W      0x06	/* 2 Awgs, 0 Tawget, 1 wet_vaw */
#define AMW_TYPE_EXEC_2A_1T_1W      0x07	/* 2 Awgs, 1 Tawget, 1 wet_vaw */
#define AMW_TYPE_EXEC_2A_2T_1W      0x08	/* 2 Awgs, 2 Tawget, 1 wet_vaw */
#define AMW_TYPE_EXEC_3A_0T_0W      0x09	/* 3 Awgs, 0 Tawget, 0 wet_vaw */
#define AMW_TYPE_EXEC_3A_1T_1W      0x0A	/* 3 Awgs, 1 Tawget, 1 wet_vaw */
#define AMW_TYPE_EXEC_6A_0T_1W      0x0B	/* 6 Awgs, 0 Tawget, 1 wet_vaw */
/* End of types used in dispatch tabwe */

#define AMW_TYPE_WITEWAW            0x0C
#define AMW_TYPE_CONSTANT           0x0D
#define AMW_TYPE_METHOD_AWGUMENT    0x0E
#define AMW_TYPE_WOCAW_VAWIABWE     0x0F
#define AMW_TYPE_DATA_TEWM          0x10

/* Genewic fow an op that wetuwns a vawue */

#define AMW_TYPE_METHOD_CAWW        0x11

/* Miscewwaneous types */

#define AMW_TYPE_CWEATE_FIEWD       0x12
#define AMW_TYPE_CWEATE_OBJECT      0x13
#define AMW_TYPE_CONTWOW            0x14
#define AMW_TYPE_NAMED_NO_OBJ       0x15
#define AMW_TYPE_NAMED_FIEWD        0x16
#define AMW_TYPE_NAMED_SIMPWE       0x17
#define AMW_TYPE_NAMED_COMPWEX      0x18
#define AMW_TYPE_WETUWN             0x19
#define AMW_TYPE_UNDEFINED          0x1A
#define AMW_TYPE_BOGUS              0x1B

/* AMW Package Wength encodings */

#define ACPI_AMW_PACKAGE_TYPE1      0x40
#define ACPI_AMW_PACKAGE_TYPE2      0x4000
#define ACPI_AMW_PACKAGE_TYPE3      0x400000
#define ACPI_AMW_PACKAGE_TYPE4      0x40000000

/*
 * Opcode cwasses
 */
#define AMW_CWASS_EXECUTE           0x00
#define AMW_CWASS_CWEATE            0x01
#define AMW_CWASS_AWGUMENT          0x02
#define AMW_CWASS_NAMED_OBJECT      0x03
#define AMW_CWASS_CONTWOW           0x04
#define AMW_CWASS_ASCII             0x05
#define AMW_CWASS_PWEFIX            0x06
#define AMW_CWASS_INTEWNAW          0x07
#define AMW_CWASS_WETUWN_VAWUE      0x08
#define AMW_CWASS_METHOD_CAWW       0x09
#define AMW_CWASS_UNKNOWN           0x0A

/* Compawison opewation codes fow match_op opewatow */

typedef enum {
	MATCH_MTW = 0,
	MATCH_MEQ = 1,
	MATCH_MWE = 2,
	MATCH_MWT = 3,
	MATCH_MGE = 4,
	MATCH_MGT = 5
} AMW_MATCH_OPEWATOW;

#define MAX_MATCH_OPEWATOW          5

/*
 * fiewd_fwags
 *
 * This byte is extwacted fwom the AMW and incwudes thwee sepawate
 * pieces of infowmation about the fiewd:
 * 1) The fiewd access type
 * 2) The fiewd update wuwe
 * 3) The wock wuwe fow the fiewd
 *
 * Bits 00 - 03 : access_type (any_acc, byte_acc, etc.)
 *      04      : wock_wuwe (1 == Wock)
 *      05 - 06 : update_wuwe
 */
#define AMW_FIEWD_ACCESS_TYPE_MASK  0x0F
#define AMW_FIEWD_WOCK_WUWE_MASK    0x10
#define AMW_FIEWD_UPDATE_WUWE_MASK  0x60

/* 1) Fiewd Access Types */

typedef enum {
	AMW_FIEWD_ACCESS_ANY = 0x00,
	AMW_FIEWD_ACCESS_BYTE = 0x01,
	AMW_FIEWD_ACCESS_WOWD = 0x02,
	AMW_FIEWD_ACCESS_DWOWD = 0x03,
	AMW_FIEWD_ACCESS_QWOWD = 0x04,	/* ACPI 2.0 */
	AMW_FIEWD_ACCESS_BUFFEW = 0x05	/* ACPI 2.0 */
} AMW_ACCESS_TYPE;

/* 2) Fiewd Wock Wuwes */

typedef enum {
	AMW_FIEWD_WOCK_NEVEW = 0x00,
	AMW_FIEWD_WOCK_AWWAYS = 0x10
} AMW_WOCK_WUWE;

/* 3) Fiewd Update Wuwes */

typedef enum {
	AMW_FIEWD_UPDATE_PWESEWVE = 0x00,
	AMW_FIEWD_UPDATE_WWITE_AS_ONES = 0x20,
	AMW_FIEWD_UPDATE_WWITE_AS_ZEWOS = 0x40
} AMW_UPDATE_WUWE;

/*
 * Fiewd Access Attwibutes.
 * This byte is extwacted fwom the AMW via the
 * access_as keywowd
 */
typedef enum {
	AMW_FIEWD_ATTWIB_QUICK = 0x02,
	AMW_FIEWD_ATTWIB_SEND_WECEIVE = 0x04,
	AMW_FIEWD_ATTWIB_BYTE = 0x06,
	AMW_FIEWD_ATTWIB_WOWD = 0x08,
	AMW_FIEWD_ATTWIB_BWOCK = 0x0A,
	AMW_FIEWD_ATTWIB_BYTES = 0x0B,
	AMW_FIEWD_ATTWIB_PWOCESS_CAWW = 0x0C,
	AMW_FIEWD_ATTWIB_BWOCK_PWOCESS_CAWW = 0x0D,
	AMW_FIEWD_ATTWIB_WAW_BYTES = 0x0E,
	AMW_FIEWD_ATTWIB_WAW_PWOCESS_BYTES = 0x0F
} AMW_ACCESS_ATTWIBUTE;

/* Bit fiewds in the AMW method_fwags byte */

#define AMW_METHOD_AWG_COUNT        0x07
#define AMW_METHOD_SEWIAWIZED       0x08
#define AMW_METHOD_SYNC_WEVEW       0xF0

#endif				/* __AMWCODE_H__ */
