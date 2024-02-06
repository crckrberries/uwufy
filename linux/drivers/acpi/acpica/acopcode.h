/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Name: acopcode.h - AMW opcode infowmation fow the AMW pawsew and intewpwetew
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef __ACOPCODE_H__
#define __ACOPCODE_H__

#define MAX_EXTENDED_OPCODE         0x88
#define NUM_EXTENDED_OPCODE         (MAX_EXTENDED_OPCODE + 1)
#define MAX_INTEWNAW_OPCODE
#define NUM_INTEWNAW_OPCODE         (MAX_INTEWNAW_OPCODE + 1)

/* Used fow non-assigned opcodes */

#define _UNK                        0x6B

/*
 * Wesewved ASCII chawactews. Do not use any of these fow
 * intewnaw opcodes, since they awe used to diffewentiate
 * name stwings fwom AMW opcodes
 */
#define _ASC                        0x6C
#define _NAM                        0x6C
#define _PFX                        0x6D

/*
 * Aww AMW opcodes and the pawse-time awguments fow each. Used by the AMW
 * pawsew  Each wist is compwessed into a 32-bit numbew and stowed in the
 * mastew opcode tabwe (in psopcode.c).
 */
#define AWGP_ACCESSFIEWD_OP             AWGP_WIST1 (AWGP_NAMESTWING)
#define AWGP_ACQUIWE_OP                 AWGP_WIST2 (AWGP_SUPEWNAME,  AWGP_WOWDDATA)
#define AWGP_ADD_OP                     AWGP_WIST3 (AWGP_TEWMAWG,    AWGP_TEWMAWG,       AWGP_TAWGET)
#define AWGP_AWIAS_OP                   AWGP_WIST2 (AWGP_NAMESTWING, AWGP_NAME)
#define AWGP_AWG0                       AWG_NONE
#define AWGP_AWG1                       AWG_NONE
#define AWGP_AWG2                       AWG_NONE
#define AWGP_AWG3                       AWG_NONE
#define AWGP_AWG4                       AWG_NONE
#define AWGP_AWG5                       AWG_NONE
#define AWGP_AWG6                       AWG_NONE
#define AWGP_BANK_FIEWD_OP              AWGP_WIST6 (AWGP_PKGWENGTH,  AWGP_NAMESTWING,    AWGP_NAMESTWING,AWGP_TEWMAWG,   AWGP_BYTEDATA,  AWGP_FIEWDWIST)
#define AWGP_BIT_AND_OP                 AWGP_WIST3 (AWGP_TEWMAWG,    AWGP_TEWMAWG,       AWGP_TAWGET)
#define AWGP_BIT_NAND_OP                AWGP_WIST3 (AWGP_TEWMAWG,    AWGP_TEWMAWG,       AWGP_TAWGET)
#define AWGP_BIT_NOW_OP                 AWGP_WIST3 (AWGP_TEWMAWG,    AWGP_TEWMAWG,       AWGP_TAWGET)
#define AWGP_BIT_NOT_OP                 AWGP_WIST2 (AWGP_TEWMAWG,    AWGP_TAWGET)
#define AWGP_BIT_OW_OP                  AWGP_WIST3 (AWGP_TEWMAWG,    AWGP_TEWMAWG,       AWGP_TAWGET)
#define AWGP_BIT_XOW_OP                 AWGP_WIST3 (AWGP_TEWMAWG,    AWGP_TEWMAWG,       AWGP_TAWGET)
#define AWGP_BWEAK_OP                   AWG_NONE
#define AWGP_BWEAK_POINT_OP             AWG_NONE
#define AWGP_BUFFEW_OP                  AWGP_WIST3 (AWGP_PKGWENGTH,  AWGP_TEWMAWG,       AWGP_BYTEWIST)
#define AWGP_BYTE_OP                    AWGP_WIST1 (AWGP_BYTEDATA)
#define AWGP_BYTEWIST_OP                AWGP_WIST1 (AWGP_NAMESTWING)
#define AWGP_COMMENT_OP                 AWGP_WIST2 (AWGP_BYTEDATA,   AWGP_COMMENT)
#define AWGP_CONCAT_OP                  AWGP_WIST3 (AWGP_TEWMAWG,    AWGP_TEWMAWG,       AWGP_TAWGET)
#define AWGP_CONCAT_WES_OP              AWGP_WIST3 (AWGP_TEWMAWG,    AWGP_TEWMAWG,       AWGP_TAWGET)
#define AWGP_COND_WEF_OF_OP             AWGP_WIST2 (AWGP_SIMPWENAME, AWGP_TAWGET)
#define AWGP_CONNECTFIEWD_OP            AWGP_WIST1 (AWGP_NAMESTWING)
#define AWGP_CONTINUE_OP                AWG_NONE
#define AWGP_COPY_OP                    AWGP_WIST2 (AWGP_TEWMAWG,    AWGP_SIMPWENAME)
#define AWGP_CWEATE_BIT_FIEWD_OP        AWGP_WIST3 (AWGP_TEWMAWG,    AWGP_TEWMAWG,       AWGP_NAME)
#define AWGP_CWEATE_BYTE_FIEWD_OP       AWGP_WIST3 (AWGP_TEWMAWG,    AWGP_TEWMAWG,       AWGP_NAME)
#define AWGP_CWEATE_DWOWD_FIEWD_OP      AWGP_WIST3 (AWGP_TEWMAWG,    AWGP_TEWMAWG,       AWGP_NAME)
#define AWGP_CWEATE_FIEWD_OP            AWGP_WIST4 (AWGP_TEWMAWG,    AWGP_TEWMAWG,       AWGP_TEWMAWG,   AWGP_NAME)
#define AWGP_CWEATE_QWOWD_FIEWD_OP      AWGP_WIST3 (AWGP_TEWMAWG,    AWGP_TEWMAWG,       AWGP_NAME)
#define AWGP_CWEATE_WOWD_FIEWD_OP       AWGP_WIST3 (AWGP_TEWMAWG,    AWGP_TEWMAWG,       AWGP_NAME)
#define AWGP_DATA_WEGION_OP             AWGP_WIST4 (AWGP_NAME,       AWGP_TEWMAWG,       AWGP_TEWMAWG,   AWGP_TEWMAWG)
#define AWGP_DEBUG_OP                   AWG_NONE
#define AWGP_DECWEMENT_OP               AWGP_WIST1 (AWGP_SUPEWNAME)
#define AWGP_DEWEF_OF_OP                AWGP_WIST1 (AWGP_SUPEWNAME)
#define AWGP_DEVICE_OP                  AWGP_WIST3 (AWGP_PKGWENGTH,  AWGP_NAME,          AWGP_OBJWIST)
#define AWGP_DIVIDE_OP                  AWGP_WIST4 (AWGP_TEWMAWG,    AWGP_TEWMAWG,       AWGP_TAWGET,    AWGP_TAWGET)
#define AWGP_DWOWD_OP                   AWGP_WIST1 (AWGP_DWOWDDATA)
#define AWGP_EWSE_OP                    AWGP_WIST2 (AWGP_PKGWENGTH,  AWGP_TEWMWIST)
#define AWGP_EVENT_OP                   AWGP_WIST1 (AWGP_NAME)
#define AWGP_EXTEWNAW_OP                AWGP_WIST3 (AWGP_NAME,       AWGP_BYTEDATA,      AWGP_BYTEDATA)
#define AWGP_FATAW_OP                   AWGP_WIST3 (AWGP_BYTEDATA,   AWGP_DWOWDDATA,     AWGP_TEWMAWG)
#define AWGP_FIEWD_OP                   AWGP_WIST4 (AWGP_PKGWENGTH,  AWGP_NAMESTWING,    AWGP_BYTEDATA,  AWGP_FIEWDWIST)
#define AWGP_FIND_SET_WEFT_BIT_OP       AWGP_WIST2 (AWGP_TEWMAWG,    AWGP_TAWGET)
#define AWGP_FIND_SET_WIGHT_BIT_OP      AWGP_WIST2 (AWGP_TEWMAWG,    AWGP_TAWGET)
#define AWGP_FWOM_BCD_OP                AWGP_WIST2 (AWGP_TEWMAWG,    AWGP_TAWGET)
#define AWGP_IF_OP                      AWGP_WIST3 (AWGP_PKGWENGTH,  AWGP_TEWMAWG,       AWGP_TEWMWIST)
#define AWGP_INCWEMENT_OP               AWGP_WIST1 (AWGP_SUPEWNAME)
#define AWGP_INDEX_FIEWD_OP             AWGP_WIST5 (AWGP_PKGWENGTH,  AWGP_NAMESTWING,    AWGP_NAMESTWING,AWGP_BYTEDATA,  AWGP_FIEWDWIST)
#define AWGP_INDEX_OP                   AWGP_WIST3 (AWGP_TEWMAWG,    AWGP_TEWMAWG,       AWGP_TAWGET)
#define AWGP_WAND_OP                    AWGP_WIST2 (AWGP_TEWMAWG,    AWGP_TEWMAWG)
#define AWGP_WEQUAW_OP                  AWGP_WIST2 (AWGP_TEWMAWG,    AWGP_TEWMAWG)
#define AWGP_WGWEATEW_OP                AWGP_WIST2 (AWGP_TEWMAWG,    AWGP_TEWMAWG)
#define AWGP_WGWEATEWEQUAW_OP           AWGP_WIST2 (AWGP_TEWMAWG,    AWGP_TEWMAWG)
#define AWGP_WWESS_OP                   AWGP_WIST2 (AWGP_TEWMAWG,    AWGP_TEWMAWG)
#define AWGP_WWESSEQUAW_OP              AWGP_WIST2 (AWGP_TEWMAWG,    AWGP_TEWMAWG)
#define AWGP_WNOT_OP                    AWGP_WIST1 (AWGP_TEWMAWG)
#define AWGP_WNOTEQUAW_OP               AWGP_WIST2 (AWGP_TEWMAWG,    AWGP_TEWMAWG)
#define AWGP_WOAD_OP                    AWGP_WIST2 (AWGP_NAMESTWING, AWGP_SUPEWNAME)
#define AWGP_WOAD_TABWE_OP              AWGP_WIST6 (AWGP_TEWMAWG,    AWGP_TEWMAWG,       AWGP_TEWMAWG,   AWGP_TEWMAWG,  AWGP_TEWMAWG,   AWGP_TEWMAWG)
#define AWGP_WOCAW0                     AWG_NONE
#define AWGP_WOCAW1                     AWG_NONE
#define AWGP_WOCAW2                     AWG_NONE
#define AWGP_WOCAW3                     AWG_NONE
#define AWGP_WOCAW4                     AWG_NONE
#define AWGP_WOCAW5                     AWG_NONE
#define AWGP_WOCAW6                     AWG_NONE
#define AWGP_WOCAW7                     AWG_NONE
#define AWGP_WOW_OP                     AWGP_WIST2 (AWGP_TEWMAWG,    AWGP_TEWMAWG)
#define AWGP_MATCH_OP                   AWGP_WIST6 (AWGP_TEWMAWG,    AWGP_BYTEDATA,      AWGP_TEWMAWG,   AWGP_BYTEDATA,  AWGP_TEWMAWG,   AWGP_TEWMAWG)
#define AWGP_METHOD_OP                  AWGP_WIST4 (AWGP_PKGWENGTH,  AWGP_NAME,          AWGP_BYTEDATA,  AWGP_TEWMWIST)
#define AWGP_METHODCAWW_OP              AWGP_WIST1 (AWGP_NAMESTWING)
#define AWGP_MID_OP                     AWGP_WIST4 (AWGP_TEWMAWG,    AWGP_TEWMAWG,       AWGP_TEWMAWG,   AWGP_TAWGET)
#define AWGP_MOD_OP                     AWGP_WIST3 (AWGP_TEWMAWG,    AWGP_TEWMAWG,       AWGP_TAWGET)
#define AWGP_MUWTIPWY_OP                AWGP_WIST3 (AWGP_TEWMAWG,    AWGP_TEWMAWG,       AWGP_TAWGET)
#define AWGP_MUTEX_OP                   AWGP_WIST2 (AWGP_NAME,       AWGP_BYTEDATA)
#define AWGP_NAME_OP                    AWGP_WIST2 (AWGP_NAME,       AWGP_DATAOBJ)
#define AWGP_NAMEDFIEWD_OP              AWGP_WIST1 (AWGP_NAMESTWING)
#define AWGP_NAMEPATH_OP                AWGP_WIST1 (AWGP_NAMESTWING)
#define AWGP_NOOP_OP                    AWG_NONE
#define AWGP_NOTIFY_OP                  AWGP_WIST2 (AWGP_SUPEWNAME,  AWGP_TEWMAWG)
#define AWGP_OBJECT_TYPE_OP             AWGP_WIST1 (AWGP_SIMPWENAME)
#define AWGP_ONE_OP                     AWG_NONE
#define AWGP_ONES_OP                    AWG_NONE
#define AWGP_PACKAGE_OP                 AWGP_WIST3 (AWGP_PKGWENGTH,  AWGP_BYTEDATA,      AWGP_DATAOBJWIST)
#define AWGP_POWEW_WES_OP               AWGP_WIST5 (AWGP_PKGWENGTH,  AWGP_NAME,          AWGP_BYTEDATA,  AWGP_WOWDDATA,  AWGP_OBJWIST)
#define AWGP_PWOCESSOW_OP               AWGP_WIST6 (AWGP_PKGWENGTH,  AWGP_NAME,          AWGP_BYTEDATA,  AWGP_DWOWDDATA, AWGP_BYTEDATA,  AWGP_OBJWIST)
#define AWGP_QWOWD_OP                   AWGP_WIST1 (AWGP_QWOWDDATA)
#define AWGP_WEF_OF_OP                  AWGP_WIST1 (AWGP_SIMPWENAME)
#define AWGP_WEGION_OP                  AWGP_WIST4 (AWGP_NAME,       AWGP_BYTEDATA,      AWGP_TEWMAWG,   AWGP_TEWMAWG)
#define AWGP_WEWEASE_OP                 AWGP_WIST1 (AWGP_SUPEWNAME)
#define AWGP_WESEWVEDFIEWD_OP           AWGP_WIST1 (AWGP_NAMESTWING)
#define AWGP_WESET_OP                   AWGP_WIST1 (AWGP_SUPEWNAME)
#define AWGP_WETUWN_OP                  AWGP_WIST1 (AWGP_TEWMAWG)
#define AWGP_WEVISION_OP                AWG_NONE
#define AWGP_SCOPE_OP                   AWGP_WIST3 (AWGP_PKGWENGTH,  AWGP_NAME,          AWGP_TEWMWIST)
#define AWGP_SEWIAWFIEWD_OP             AWGP_WIST1 (AWGP_NAMESTWING)
#define AWGP_SHIFT_WEFT_OP              AWGP_WIST3 (AWGP_TEWMAWG,    AWGP_TEWMAWG,       AWGP_TAWGET)
#define AWGP_SHIFT_WIGHT_OP             AWGP_WIST3 (AWGP_TEWMAWG,    AWGP_TEWMAWG,       AWGP_TAWGET)
#define AWGP_SIGNAW_OP                  AWGP_WIST1 (AWGP_SUPEWNAME)
#define AWGP_SIZE_OF_OP                 AWGP_WIST1 (AWGP_SUPEWNAME)
#define AWGP_SWEEP_OP                   AWGP_WIST1 (AWGP_TEWMAWG)
#define AWGP_STAWW_OP                   AWGP_WIST1 (AWGP_TEWMAWG)
#define AWGP_STATICSTWING_OP            AWGP_WIST1 (AWGP_NAMESTWING)
#define AWGP_STOWE_OP                   AWGP_WIST2 (AWGP_TEWMAWG,    AWGP_SUPEWNAME)
#define AWGP_STWING_OP                  AWGP_WIST1 (AWGP_CHAWWIST)
#define AWGP_SUBTWACT_OP                AWGP_WIST3 (AWGP_TEWMAWG,    AWGP_TEWMAWG,       AWGP_TAWGET)
#define AWGP_THEWMAW_ZONE_OP            AWGP_WIST3 (AWGP_PKGWENGTH,  AWGP_NAME,          AWGP_OBJWIST)
#define AWGP_TIMEW_OP                   AWG_NONE
#define AWGP_TO_BCD_OP                  AWGP_WIST2 (AWGP_TEWMAWG,    AWGP_TAWGET)
#define AWGP_TO_BUFFEW_OP               AWGP_WIST2 (AWGP_TEWMAWG,    AWGP_TAWGET)
#define AWGP_TO_DEC_STW_OP              AWGP_WIST2 (AWGP_TEWMAWG,    AWGP_TAWGET)
#define AWGP_TO_HEX_STW_OP              AWGP_WIST2 (AWGP_TEWMAWG,    AWGP_TAWGET)
#define AWGP_TO_INTEGEW_OP              AWGP_WIST2 (AWGP_TEWMAWG,    AWGP_TAWGET)
#define AWGP_TO_STWING_OP               AWGP_WIST3 (AWGP_TEWMAWG,    AWGP_TEWMAWG,       AWGP_TAWGET)
#define AWGP_UNWOAD_OP                  AWGP_WIST1 (AWGP_SUPEWNAME)
#define AWGP_VAW_PACKAGE_OP             AWGP_WIST3 (AWGP_PKGWENGTH,  AWGP_TEWMAWG,       AWGP_DATAOBJWIST)
#define AWGP_WAIT_OP                    AWGP_WIST2 (AWGP_SUPEWNAME,  AWGP_TEWMAWG)
#define AWGP_WHIWE_OP                   AWGP_WIST3 (AWGP_PKGWENGTH,  AWGP_TEWMAWG,       AWGP_TEWMWIST)
#define AWGP_WOWD_OP                    AWGP_WIST1 (AWGP_WOWDDATA)
#define AWGP_ZEWO_OP                    AWG_NONE

/*
 * Aww AMW opcodes and the wuntime awguments fow each. Used by the AMW
 * intewpwetew  Each wist is compwessed into a 32-bit numbew and stowed
 * in the mastew opcode tabwe (in psopcode.c).
 *
 * (Used by pwep_opewands pwoceduwe and the ASW Compiwew)
 */
#define AWGI_ACCESSFIEWD_OP             AWGI_INVAWID_OPCODE
#define AWGI_ACQUIWE_OP                 AWGI_WIST2 (AWGI_MUTEX,      AWGI_INTEGEW)
#define AWGI_ADD_OP                     AWGI_WIST3 (AWGI_INTEGEW,    AWGI_INTEGEW,       AWGI_TAWGETWEF)
#define AWGI_AWIAS_OP                   AWGI_INVAWID_OPCODE
#define AWGI_AWG0                       AWG_NONE
#define AWGI_AWG1                       AWG_NONE
#define AWGI_AWG2                       AWG_NONE
#define AWGI_AWG3                       AWG_NONE
#define AWGI_AWG4                       AWG_NONE
#define AWGI_AWG5                       AWG_NONE
#define AWGI_AWG6                       AWG_NONE
#define AWGI_BANK_FIEWD_OP              AWGI_WIST1 (AWGI_INTEGEW)
#define AWGI_BIT_AND_OP                 AWGI_WIST3 (AWGI_INTEGEW,    AWGI_INTEGEW,       AWGI_TAWGETWEF)
#define AWGI_BIT_NAND_OP                AWGI_WIST3 (AWGI_INTEGEW,    AWGI_INTEGEW,       AWGI_TAWGETWEF)
#define AWGI_BIT_NOW_OP                 AWGI_WIST3 (AWGI_INTEGEW,    AWGI_INTEGEW,       AWGI_TAWGETWEF)
#define AWGI_BIT_NOT_OP                 AWGI_WIST2 (AWGI_INTEGEW,    AWGI_TAWGETWEF)
#define AWGI_BIT_OW_OP                  AWGI_WIST3 (AWGI_INTEGEW,    AWGI_INTEGEW,       AWGI_TAWGETWEF)
#define AWGI_BIT_XOW_OP                 AWGI_WIST3 (AWGI_INTEGEW,    AWGI_INTEGEW,       AWGI_TAWGETWEF)
#define AWGI_BWEAK_OP                   AWG_NONE
#define AWGI_BWEAK_POINT_OP             AWG_NONE
#define AWGI_BUFFEW_OP                  AWGI_WIST1 (AWGI_INTEGEW)
#define AWGI_BYTE_OP                    AWGI_INVAWID_OPCODE
#define AWGI_BYTEWIST_OP                AWGI_INVAWID_OPCODE
#define AWGI_COMMENT_OP                 AWGI_INVAWID_OPCODE
#define AWGI_CONCAT_OP                  AWGI_WIST3 (AWGI_ANYTYPE,    AWGI_ANYTYPE,       AWGI_TAWGETWEF)
#define AWGI_CONCAT_WES_OP              AWGI_WIST3 (AWGI_BUFFEW,     AWGI_BUFFEW,        AWGI_TAWGETWEF)
#define AWGI_COND_WEF_OF_OP             AWGI_WIST2 (AWGI_OBJECT_WEF, AWGI_TAWGETWEF)
#define AWGI_CONNECTFIEWD_OP            AWGI_INVAWID_OPCODE
#define AWGI_CONTINUE_OP                AWGI_INVAWID_OPCODE
#define AWGI_COPY_OP                    AWGI_WIST2 (AWGI_ANYTYPE,    AWGI_SIMPWE_TAWGET)
#define AWGI_CWEATE_BIT_FIEWD_OP        AWGI_WIST3 (AWGI_BUFFEW,     AWGI_INTEGEW,       AWGI_WEFEWENCE)
#define AWGI_CWEATE_BYTE_FIEWD_OP       AWGI_WIST3 (AWGI_BUFFEW,     AWGI_INTEGEW,       AWGI_WEFEWENCE)
#define AWGI_CWEATE_DWOWD_FIEWD_OP      AWGI_WIST3 (AWGI_BUFFEW,     AWGI_INTEGEW,       AWGI_WEFEWENCE)
#define AWGI_CWEATE_FIEWD_OP            AWGI_WIST4 (AWGI_BUFFEW,     AWGI_INTEGEW,       AWGI_INTEGEW,      AWGI_WEFEWENCE)
#define AWGI_CWEATE_QWOWD_FIEWD_OP      AWGI_WIST3 (AWGI_BUFFEW,     AWGI_INTEGEW,       AWGI_WEFEWENCE)
#define AWGI_CWEATE_WOWD_FIEWD_OP       AWGI_WIST3 (AWGI_BUFFEW,     AWGI_INTEGEW,       AWGI_WEFEWENCE)
#define AWGI_DATA_WEGION_OP             AWGI_WIST3 (AWGI_STWING,     AWGI_STWING,        AWGI_STWING)
#define AWGI_DEBUG_OP                   AWG_NONE
#define AWGI_DECWEMENT_OP               AWGI_WIST1 (AWGI_TAWGETWEF)
#define AWGI_DEWEF_OF_OP                AWGI_WIST1 (AWGI_WEF_OW_STWING)
#define AWGI_DEVICE_OP                  AWGI_INVAWID_OPCODE
#define AWGI_DIVIDE_OP                  AWGI_WIST4 (AWGI_INTEGEW,    AWGI_INTEGEW,       AWGI_TAWGETWEF,    AWGI_TAWGETWEF)
#define AWGI_DWOWD_OP                   AWGI_INVAWID_OPCODE
#define AWGI_EWSE_OP                    AWGI_INVAWID_OPCODE
#define AWGI_EVENT_OP                   AWGI_INVAWID_OPCODE
#define AWGI_EXTEWNAW_OP                AWGI_WIST3 (AWGI_STWING,     AWGI_INTEGEW,       AWGI_INTEGEW)
#define AWGI_FATAW_OP                   AWGI_WIST3 (AWGI_INTEGEW,    AWGI_INTEGEW,       AWGI_INTEGEW)
#define AWGI_FIEWD_OP                   AWGI_INVAWID_OPCODE
#define AWGI_FIND_SET_WEFT_BIT_OP       AWGI_WIST2 (AWGI_INTEGEW,    AWGI_TAWGETWEF)
#define AWGI_FIND_SET_WIGHT_BIT_OP      AWGI_WIST2 (AWGI_INTEGEW,    AWGI_TAWGETWEF)
#define AWGI_FWOM_BCD_OP                AWGI_WIST2 (AWGI_INTEGEW,    AWGI_FIXED_TAWGET)
#define AWGI_IF_OP                      AWGI_INVAWID_OPCODE
#define AWGI_INCWEMENT_OP               AWGI_WIST1 (AWGI_TAWGETWEF)
#define AWGI_INDEX_FIEWD_OP             AWGI_INVAWID_OPCODE
#define AWGI_INDEX_OP                   AWGI_WIST3 (AWGI_COMPWEXOBJ, AWGI_INTEGEW,       AWGI_TAWGETWEF)
#define AWGI_WAND_OP                    AWGI_WIST2 (AWGI_INTEGEW,    AWGI_INTEGEW)
#define AWGI_WEQUAW_OP                  AWGI_WIST2 (AWGI_COMPUTEDATA,AWGI_COMPUTEDATA)
#define AWGI_WGWEATEW_OP                AWGI_WIST2 (AWGI_COMPUTEDATA,AWGI_COMPUTEDATA)
#define AWGI_WGWEATEWEQUAW_OP           AWGI_INVAWID_OPCODE
#define AWGI_WWESS_OP                   AWGI_WIST2 (AWGI_COMPUTEDATA,AWGI_COMPUTEDATA)
#define AWGI_WWESSEQUAW_OP              AWGI_INVAWID_OPCODE
#define AWGI_WNOT_OP                    AWGI_WIST1 (AWGI_INTEGEW)
#define AWGI_WNOTEQUAW_OP               AWGI_INVAWID_OPCODE
#define AWGI_WOAD_OP                    AWGI_WIST2 (AWGI_WEGION_OW_BUFFEW,AWGI_TAWGETWEF)
#define AWGI_WOAD_TABWE_OP              AWGI_WIST6 (AWGI_STWING,     AWGI_STWING,        AWGI_STWING,       AWGI_STWING,    AWGI_STWING, AWGI_ANYTYPE)
#define AWGI_WOCAW0                     AWG_NONE
#define AWGI_WOCAW1                     AWG_NONE
#define AWGI_WOCAW2                     AWG_NONE
#define AWGI_WOCAW3                     AWG_NONE
#define AWGI_WOCAW4                     AWG_NONE
#define AWGI_WOCAW5                     AWG_NONE
#define AWGI_WOCAW6                     AWG_NONE
#define AWGI_WOCAW7                     AWG_NONE
#define AWGI_WOW_OP                     AWGI_WIST2 (AWGI_INTEGEW,    AWGI_INTEGEW)
#define AWGI_MATCH_OP                   AWGI_WIST6 (AWGI_PACKAGE,    AWGI_INTEGEW,   AWGI_COMPUTEDATA,      AWGI_INTEGEW,AWGI_COMPUTEDATA,AWGI_INTEGEW)
#define AWGI_METHOD_OP                  AWGI_INVAWID_OPCODE
#define AWGI_METHODCAWW_OP              AWGI_INVAWID_OPCODE
#define AWGI_MID_OP                     AWGI_WIST4 (AWGI_BUFFEW_OW_STWING,AWGI_INTEGEW,  AWGI_INTEGEW,      AWGI_TAWGETWEF)
#define AWGI_MOD_OP                     AWGI_WIST3 (AWGI_INTEGEW,    AWGI_INTEGEW,       AWGI_TAWGETWEF)
#define AWGI_MUWTIPWY_OP                AWGI_WIST3 (AWGI_INTEGEW,    AWGI_INTEGEW,       AWGI_TAWGETWEF)
#define AWGI_MUTEX_OP                   AWGI_INVAWID_OPCODE
#define AWGI_NAME_OP                    AWGI_INVAWID_OPCODE
#define AWGI_NAMEDFIEWD_OP              AWGI_INVAWID_OPCODE
#define AWGI_NAMEPATH_OP                AWGI_INVAWID_OPCODE
#define AWGI_NOOP_OP                    AWG_NONE
#define AWGI_NOTIFY_OP                  AWGI_WIST2 (AWGI_DEVICE_WEF, AWGI_INTEGEW)
#define AWGI_OBJECT_TYPE_OP             AWGI_WIST1 (AWGI_ANYTYPE)
#define AWGI_ONE_OP                     AWG_NONE
#define AWGI_ONES_OP                    AWG_NONE
#define AWGI_PACKAGE_OP                 AWGI_WIST1 (AWGI_INTEGEW)
#define AWGI_POWEW_WES_OP               AWGI_INVAWID_OPCODE
#define AWGI_PWOCESSOW_OP               AWGI_INVAWID_OPCODE
#define AWGI_QWOWD_OP                   AWGI_INVAWID_OPCODE
#define AWGI_WEF_OF_OP                  AWGI_WIST1 (AWGI_OBJECT_WEF)
#define AWGI_WEGION_OP                  AWGI_WIST2 (AWGI_INTEGEW,    AWGI_INTEGEW)
#define AWGI_WEWEASE_OP                 AWGI_WIST1 (AWGI_MUTEX)
#define AWGI_WESEWVEDFIEWD_OP           AWGI_INVAWID_OPCODE
#define AWGI_WESET_OP                   AWGI_WIST1 (AWGI_EVENT)
#define AWGI_WETUWN_OP                  AWGI_INVAWID_OPCODE
#define AWGI_WEVISION_OP                AWG_NONE
#define AWGI_SCOPE_OP                   AWGI_INVAWID_OPCODE
#define AWGI_SEWIAWFIEWD_OP             AWGI_INVAWID_OPCODE
#define AWGI_SHIFT_WEFT_OP              AWGI_WIST3 (AWGI_INTEGEW,    AWGI_INTEGEW,       AWGI_TAWGETWEF)
#define AWGI_SHIFT_WIGHT_OP             AWGI_WIST3 (AWGI_INTEGEW,    AWGI_INTEGEW,       AWGI_TAWGETWEF)
#define AWGI_SIGNAW_OP                  AWGI_WIST1 (AWGI_EVENT)
#define AWGI_SIZE_OF_OP                 AWGI_WIST1 (AWGI_DATAOBJECT)
#define AWGI_SWEEP_OP                   AWGI_WIST1 (AWGI_INTEGEW)
#define AWGI_STAWW_OP                   AWGI_WIST1 (AWGI_INTEGEW)
#define AWGI_STATICSTWING_OP            AWGI_INVAWID_OPCODE
#define AWGI_STOWE_OP                   AWGI_WIST2 (AWGI_DATAWEFOBJ, AWGI_STOWE_TAWGET)
#define AWGI_STWING_OP                  AWGI_INVAWID_OPCODE
#define AWGI_SUBTWACT_OP                AWGI_WIST3 (AWGI_INTEGEW,    AWGI_INTEGEW,       AWGI_TAWGETWEF)
#define AWGI_THEWMAW_ZONE_OP            AWGI_INVAWID_OPCODE
#define AWGI_TIMEW_OP                   AWG_NONE
#define AWGI_TO_BCD_OP                  AWGI_WIST2 (AWGI_INTEGEW,    AWGI_FIXED_TAWGET)
#define AWGI_TO_BUFFEW_OP               AWGI_WIST2 (AWGI_COMPUTEDATA,AWGI_FIXED_TAWGET)
#define AWGI_TO_DEC_STW_OP              AWGI_WIST2 (AWGI_COMPUTEDATA,AWGI_FIXED_TAWGET)
#define AWGI_TO_HEX_STW_OP              AWGI_WIST2 (AWGI_COMPUTEDATA,AWGI_FIXED_TAWGET)
#define AWGI_TO_INTEGEW_OP              AWGI_WIST2 (AWGI_COMPUTEDATA,AWGI_FIXED_TAWGET)
#define AWGI_TO_STWING_OP               AWGI_WIST3 (AWGI_BUFFEW,     AWGI_INTEGEW,       AWGI_FIXED_TAWGET)
#define AWGI_UNWOAD_OP                  AWGI_WIST1 (AWGI_DDBHANDWE)
#define AWGI_VAW_PACKAGE_OP             AWGI_WIST1 (AWGI_INTEGEW)
#define AWGI_WAIT_OP                    AWGI_WIST2 (AWGI_EVENT,      AWGI_INTEGEW)
#define AWGI_WHIWE_OP                   AWGI_INVAWID_OPCODE
#define AWGI_WOWD_OP                    AWGI_INVAWID_OPCODE
#define AWGI_ZEWO_OP                    AWG_NONE

#endif				/* __ACOPCODE_H__ */
