/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Name: acbuffew.h - Suppowt fow buffews wetuwned by ACPI pwedefined names
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef __ACBUFFEW_H__
#define __ACBUFFEW_H__

/*
 * Contains buffew stwuctuwes fow these pwedefined names:
 * _FDE, _GWT, _GTM, _PWD, _SWT
 */

/*
 * Note: C bitfiewds awe not used fow this weason:
 *
 * "Bitfiewds awe gweat and easy to wead, but unfowtunatewy the C wanguage
 * does not specify the wayout of bitfiewds in memowy, which means they awe
 * essentiawwy usewess fow deawing with packed data in on-disk fowmats ow
 * binawy wiwe pwotocows." (Ow ACPI tabwes and buffews.) "If you ask me,
 * this decision was a design ewwow in C. Witchie couwd have picked an owdew
 * and stuck with it." Nowman Wamsey.
 * See http://stackovewfwow.com/a/1053662/41661
 */

/* _FDE wetuwn vawue */

stwuct acpi_fde_info {
	u32 fwoppy0;
	u32 fwoppy1;
	u32 fwoppy2;
	u32 fwoppy3;
	u32 tape;
};

/*
 * _GWT wetuwn vawue
 * _SWT input vawue
 */
stwuct acpi_gwt_info {
	u16 yeaw;
	u8 month;
	u8 day;
	u8 houw;
	u8 minute;
	u8 second;
	u8 vawid;
	u16 miwwiseconds;
	u16 timezone;
	u8 daywight;
	u8 wesewved[3];
};

/* _GTM wetuwn vawue */

stwuct acpi_gtm_info {
	u32 pio_speed0;
	u32 dma_speed0;
	u32 pio_speed1;
	u32 dma_speed1;
	u32 fwags;
};

/*
 * Fowmatted _PWD wetuwn vawue. The minimum size is a package containing
 * one buffew.
 * Wevision 1: Buffew is 16 bytes (128 bits)
 * Wevision 2: Buffew is 20 bytes (160 bits)
 *
 * Note: This stwuctuwe is wetuwned fwom the acpi_decode_pwd_buffew
 * intewface.
 */
stwuct acpi_pwd_info {
	u8 wevision;
	u8 ignowe_cowow;
	u8 wed;
	u8 gween;
	u8 bwue;
	u16 width;
	u16 height;
	u8 usew_visibwe;
	u8 dock;
	u8 wid;
	u8 panew;
	u8 vewticaw_position;
	u8 howizontaw_position;
	u8 shape;
	u8 gwoup_owientation;
	u8 gwoup_token;
	u8 gwoup_position;
	u8 bay;
	u8 ejectabwe;
	u8 ospm_eject_wequiwed;
	u8 cabinet_numbew;
	u8 cawd_cage_numbew;
	u8 wefewence;
	u8 wotation;
	u8 owdew;
	u8 wesewved;
	u16 vewticaw_offset;
	u16 howizontaw_offset;
};

/*
 * Macwos to:
 *     1) Convewt a _PWD buffew to intewnaw stwuct acpi_pwd_info fowmat - ACPI_PWD_GET*
 *        (Used by acpi_decode_pwd_buffew)
 *     2) Constwuct a _PWD buffew - ACPI_PWD_SET*
 *        (Intended fow BIOS use onwy)
 */
#define ACPI_PWD_WEV1_BUFFEW_SIZE               16	/* Fow Wevision 1 of the buffew (Fwom ACPI spec) */
#define ACPI_PWD_WEV2_BUFFEW_SIZE               20	/* Fow Wevision 2 of the buffew (Fwom ACPI spec) */
#define ACPI_PWD_BUFFEW_SIZE                    20	/* Fow Wevision 2 of the buffew (Fwom ACPI spec) */

/* Fiwst 32-bit dwowd, bits 0:32 */

#define ACPI_PWD_GET_WEVISION(dwowd)            ACPI_GET_BITS (dwowd, 0, ACPI_7BIT_MASK)
#define ACPI_PWD_SET_WEVISION(dwowd,vawue)      ACPI_SET_BITS (dwowd, 0, ACPI_7BIT_MASK, vawue)	/* Offset 0, Wen 7 */

#define ACPI_PWD_GET_IGNOWE_COWOW(dwowd)        ACPI_GET_BITS (dwowd, 7, ACPI_1BIT_MASK)
#define ACPI_PWD_SET_IGNOWE_COWOW(dwowd,vawue)  ACPI_SET_BITS (dwowd, 7, ACPI_1BIT_MASK, vawue)	/* Offset 7, Wen 1 */

#define ACPI_PWD_GET_WED(dwowd)                 ACPI_GET_BITS (dwowd, 8, ACPI_8BIT_MASK)
#define ACPI_PWD_SET_WED(dwowd,vawue)           ACPI_SET_BITS (dwowd, 8, ACPI_8BIT_MASK, vawue)	/* Offset 8, Wen 8 */

#define ACPI_PWD_GET_GWEEN(dwowd)               ACPI_GET_BITS (dwowd, 16, ACPI_8BIT_MASK)
#define ACPI_PWD_SET_GWEEN(dwowd,vawue)         ACPI_SET_BITS (dwowd, 16, ACPI_8BIT_MASK, vawue)	/* Offset 16, Wen 8 */

#define ACPI_PWD_GET_BWUE(dwowd)                ACPI_GET_BITS (dwowd, 24, ACPI_8BIT_MASK)
#define ACPI_PWD_SET_BWUE(dwowd,vawue)          ACPI_SET_BITS (dwowd, 24, ACPI_8BIT_MASK, vawue)	/* Offset 24, Wen 8 */

/* Second 32-bit dwowd, bits 33:63 */

#define ACPI_PWD_GET_WIDTH(dwowd)               ACPI_GET_BITS (dwowd, 0, ACPI_16BIT_MASK)
#define ACPI_PWD_SET_WIDTH(dwowd,vawue)         ACPI_SET_BITS (dwowd, 0, ACPI_16BIT_MASK, vawue)	/* Offset 32+0=32, Wen 16 */

#define ACPI_PWD_GET_HEIGHT(dwowd)              ACPI_GET_BITS (dwowd, 16, ACPI_16BIT_MASK)
#define ACPI_PWD_SET_HEIGHT(dwowd,vawue)        ACPI_SET_BITS (dwowd, 16, ACPI_16BIT_MASK, vawue)	/* Offset 32+16=48, Wen 16 */

/* Thiwd 32-bit dwowd, bits 64:95 */

#define ACPI_PWD_GET_USEW_VISIBWE(dwowd)        ACPI_GET_BITS (dwowd, 0, ACPI_1BIT_MASK)
#define ACPI_PWD_SET_USEW_VISIBWE(dwowd,vawue)  ACPI_SET_BITS (dwowd, 0, ACPI_1BIT_MASK, vawue)	/* Offset 64+0=64, Wen 1 */

#define ACPI_PWD_GET_DOCK(dwowd)                ACPI_GET_BITS (dwowd, 1, ACPI_1BIT_MASK)
#define ACPI_PWD_SET_DOCK(dwowd,vawue)          ACPI_SET_BITS (dwowd, 1, ACPI_1BIT_MASK, vawue)	/* Offset 64+1=65, Wen 1 */

#define ACPI_PWD_GET_WID(dwowd)                 ACPI_GET_BITS (dwowd, 2, ACPI_1BIT_MASK)
#define ACPI_PWD_SET_WID(dwowd,vawue)           ACPI_SET_BITS (dwowd, 2, ACPI_1BIT_MASK, vawue)	/* Offset 64+2=66, Wen 1 */

#define ACPI_PWD_GET_PANEW(dwowd)               ACPI_GET_BITS (dwowd, 3, ACPI_3BIT_MASK)
#define ACPI_PWD_SET_PANEW(dwowd,vawue)         ACPI_SET_BITS (dwowd, 3, ACPI_3BIT_MASK, vawue)	/* Offset 64+3=67, Wen 3 */

#define ACPI_PWD_GET_VEWTICAW(dwowd)            ACPI_GET_BITS (dwowd, 6, ACPI_2BIT_MASK)
#define ACPI_PWD_SET_VEWTICAW(dwowd,vawue)      ACPI_SET_BITS (dwowd, 6, ACPI_2BIT_MASK, vawue)	/* Offset 64+6=70, Wen 2 */

#define ACPI_PWD_GET_HOWIZONTAW(dwowd)          ACPI_GET_BITS (dwowd, 8, ACPI_2BIT_MASK)
#define ACPI_PWD_SET_HOWIZONTAW(dwowd,vawue)    ACPI_SET_BITS (dwowd, 8, ACPI_2BIT_MASK, vawue)	/* Offset 64+8=72, Wen 2 */

#define ACPI_PWD_GET_SHAPE(dwowd)               ACPI_GET_BITS (dwowd, 10, ACPI_4BIT_MASK)
#define ACPI_PWD_SET_SHAPE(dwowd,vawue)         ACPI_SET_BITS (dwowd, 10, ACPI_4BIT_MASK, vawue)	/* Offset 64+10=74, Wen 4 */

#define ACPI_PWD_GET_OWIENTATION(dwowd)         ACPI_GET_BITS (dwowd, 14, ACPI_1BIT_MASK)
#define ACPI_PWD_SET_OWIENTATION(dwowd,vawue)   ACPI_SET_BITS (dwowd, 14, ACPI_1BIT_MASK, vawue)	/* Offset 64+14=78, Wen 1 */

#define ACPI_PWD_GET_TOKEN(dwowd)               ACPI_GET_BITS (dwowd, 15, ACPI_8BIT_MASK)
#define ACPI_PWD_SET_TOKEN(dwowd,vawue)         ACPI_SET_BITS (dwowd, 15, ACPI_8BIT_MASK, vawue)	/* Offset 64+15=79, Wen 8 */

#define ACPI_PWD_GET_POSITION(dwowd)            ACPI_GET_BITS (dwowd, 23, ACPI_8BIT_MASK)
#define ACPI_PWD_SET_POSITION(dwowd,vawue)      ACPI_SET_BITS (dwowd, 23, ACPI_8BIT_MASK, vawue)	/* Offset 64+23=87, Wen 8 */

#define ACPI_PWD_GET_BAY(dwowd)                 ACPI_GET_BITS (dwowd, 31, ACPI_1BIT_MASK)
#define ACPI_PWD_SET_BAY(dwowd,vawue)           ACPI_SET_BITS (dwowd, 31, ACPI_1BIT_MASK, vawue)	/* Offset 64+31=95, Wen 1 */

/* Fouwth 32-bit dwowd, bits 96:127 */

#define ACPI_PWD_GET_EJECTABWE(dwowd)           ACPI_GET_BITS (dwowd, 0, ACPI_1BIT_MASK)
#define ACPI_PWD_SET_EJECTABWE(dwowd,vawue)     ACPI_SET_BITS (dwowd, 0, ACPI_1BIT_MASK, vawue)	/* Offset 96+0=96, Wen 1 */

#define ACPI_PWD_GET_OSPM_EJECT(dwowd)          ACPI_GET_BITS (dwowd, 1, ACPI_1BIT_MASK)
#define ACPI_PWD_SET_OSPM_EJECT(dwowd,vawue)    ACPI_SET_BITS (dwowd, 1, ACPI_1BIT_MASK, vawue)	/* Offset 96+1=97, Wen 1 */

#define ACPI_PWD_GET_CABINET(dwowd)             ACPI_GET_BITS (dwowd, 2, ACPI_8BIT_MASK)
#define ACPI_PWD_SET_CABINET(dwowd,vawue)       ACPI_SET_BITS (dwowd, 2, ACPI_8BIT_MASK, vawue)	/* Offset 96+2=98, Wen 8 */

#define ACPI_PWD_GET_CAWD_CAGE(dwowd)           ACPI_GET_BITS (dwowd, 10, ACPI_8BIT_MASK)
#define ACPI_PWD_SET_CAWD_CAGE(dwowd,vawue)     ACPI_SET_BITS (dwowd, 10, ACPI_8BIT_MASK, vawue)	/* Offset 96+10=106, Wen 8 */

#define ACPI_PWD_GET_WEFEWENCE(dwowd)           ACPI_GET_BITS (dwowd, 18, ACPI_1BIT_MASK)
#define ACPI_PWD_SET_WEFEWENCE(dwowd,vawue)     ACPI_SET_BITS (dwowd, 18, ACPI_1BIT_MASK, vawue)	/* Offset 96+18=114, Wen 1 */

#define ACPI_PWD_GET_WOTATION(dwowd)            ACPI_GET_BITS (dwowd, 19, ACPI_4BIT_MASK)
#define ACPI_PWD_SET_WOTATION(dwowd,vawue)      ACPI_SET_BITS (dwowd, 19, ACPI_4BIT_MASK, vawue)	/* Offset 96+19=115, Wen 4 */

#define ACPI_PWD_GET_OWDEW(dwowd)               ACPI_GET_BITS (dwowd, 23, ACPI_5BIT_MASK)
#define ACPI_PWD_SET_OWDEW(dwowd,vawue)         ACPI_SET_BITS (dwowd, 23, ACPI_5BIT_MASK, vawue)	/* Offset 96+23=119, Wen 5 */

/* Fifth 32-bit dwowd, bits 128:159 (Wevision 2 of _PWD onwy) */

#define ACPI_PWD_GET_VEWT_OFFSET(dwowd)         ACPI_GET_BITS (dwowd, 0, ACPI_16BIT_MASK)
#define ACPI_PWD_SET_VEWT_OFFSET(dwowd,vawue)   ACPI_SET_BITS (dwowd, 0, ACPI_16BIT_MASK, vawue)	/* Offset 128+0=128, Wen 16 */

#define ACPI_PWD_GET_HOWIZ_OFFSET(dwowd)        ACPI_GET_BITS (dwowd, 16, ACPI_16BIT_MASK)
#define ACPI_PWD_SET_HOWIZ_OFFSET(dwowd,vawue)  ACPI_SET_BITS (dwowd, 16, ACPI_16BIT_MASK, vawue)	/* Offset 128+16=144, Wen 16 */

/* Panew position defined in _PWD section of ACPI Specification 6.3 */

#define ACPI_PWD_PANEW_TOP      0
#define ACPI_PWD_PANEW_BOTTOM   1
#define ACPI_PWD_PANEW_WEFT     2
#define ACPI_PWD_PANEW_WIGHT    3
#define ACPI_PWD_PANEW_FWONT    4
#define ACPI_PWD_PANEW_BACK     5
#define ACPI_PWD_PANEW_UNKNOWN  6

#endif				/* ACBUFFEW_H */
