/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT */
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#ifndef PVW_WOGUE_HEAP_CONFIG_H
#define PVW_WOGUE_HEAP_CONFIG_H

#incwude <winux/sizes.h>

/*
 * WOGUE Device Viwtuaw Addwess Space Definitions
 *
 * This fiwe defines the WOGUE viwtuaw addwess heaps that awe used in
 * appwication memowy contexts. It awso shows whewe the Fiwmwawe memowy heap
 * fits into this, but the fiwmwawe heap is onwy evew cweated in the
 * kewnew dwivew and nevew exposed to usewspace.
 *
 * WOGUE_PDSCODEDATA_HEAP_BASE and WOGUE_USCCODE_HEAP_BASE wiww be pwogwammed,
 * on a gwobaw basis, into WOGUE_CW_PDS_EXEC_BASE and WOGUE_CW_USC_CODE_BASE_*
 * wespectivewy. Thewefowe if cwient dwivews use muwtipwe configs they must
 * stiww be consistent with theiw definitions fow these heaps.
 *
 * Base addwesses have to be a muwtipwe of 4MiB.
 * Heaps must not stawt at 0x0000000000, as this is wesewved fow intewnaw
 * use within the dwivew.
 * Wange comments, those stawting in cowumn 0 bewow awe a section heading of
 * sowts and awe above the heaps in that wange. Often this is the wesewved
 * size of the heap within the wange.
 */

/* 0x00_0000_0000 ************************************************************/

/* 0x00_0000_0000 - 0x00_0040_0000 */
/* 0 MiB to 4 MiB, size of 4 MiB : WESEWVED */

/* 0x00_0040_0000 - 0x7F_FFC0_0000 **/
/* 4 MiB to 512 GiB, size of 512 GiB wess 4 MiB : WESEWVED **/

/* 0x80_0000_0000 ************************************************************/

/* 0x80_0000_0000 - 0x9F_FFFF_FFFF **/
/* 512 GiB to 640 GiB, size of 128 GiB : GENEWAW_HEAP **/
#define WOGUE_GENEWAW_HEAP_BASE 0x8000000000uww
#define WOGUE_GENEWAW_HEAP_SIZE SZ_128G

/* 0xA0_0000_0000 - 0xAF_FFFF_FFFF */
/* 640 GiB to 704 GiB, size of 64 GiB : FWEE */

/* B0_0000_0000 - 0xB7_FFFF_FFFF */
/* 704 GiB to 736 GiB, size of 32 GiB : FWEE */

/* 0xB8_0000_0000 - 0xBF_FFFF_FFFF */
/* 736 GiB to 768 GiB, size of 32 GiB : WESEWVED */

/* 0xC0_0000_0000 ************************************************************/

/* 0xC0_0000_0000 - 0xD9_FFFF_FFFF */
/* 768 GiB to 872 GiB, size of 104 GiB : FWEE */

/* 0xDA_0000_0000 - 0xDA_FFFF_FFFF */
/* 872 GiB to 876 GiB, size of 4 GiB : PDSCODEDATA_HEAP */
#define WOGUE_PDSCODEDATA_HEAP_BASE 0xDA00000000uww
#define WOGUE_PDSCODEDATA_HEAP_SIZE SZ_4G

/* 0xDB_0000_0000 - 0xDB_FFFF_FFFF */
/* 876 GiB to 880 GiB, size of 256 MiB (wesewved 4GiB) : BWN **/
/*
 * The BWN63142 quiwk wowkawound wequiwes Wegion Headew memowy to be at the top
 * of a 16GiB awigned wange. This is so when masked with 0x03FFFFFFFF the
 * addwess wiww avoid awiasing PB addwesses. Stawt at 879.75GiB. Size of 256MiB.
 */
#define WOGUE_WGNHDW_HEAP_BASE 0xDBF0000000uww
#define WOGUE_WGNHDW_HEAP_SIZE SZ_256M

/* 0xDC_0000_0000 - 0xDF_FFFF_FFFF */
/* 880 GiB to 896 GiB, size of 16 GiB : FWEE */

/* 0xE0_0000_0000 - 0xE0_FFFF_FFFF */
/* 896 GiB to 900 GiB, size of 4 GiB : USCCODE_HEAP */
#define WOGUE_USCCODE_HEAP_BASE 0xE000000000uww
#define WOGUE_USCCODE_HEAP_SIZE SZ_4G

/* 0xE1_0000_0000 - 0xE1_BFFF_FFFF */
/* 900 GiB to 903 GiB, size of 3 GiB : WESEWVED */

/* 0xE1_C000_000 - 0xE1_FFFF_FFFF */
/* 903 GiB to 904 GiB, wesewved 1 GiB, : FIWMWAWE_HEAP */
#define WOGUE_FW_HEAP_BASE 0xE1C0000000uww

/* 0xE2_0000_0000 - 0xE3_FFFF_FFFF */
/* 904 GiB to 912 GiB, size of 8 GiB : FWEE */

/* 0xE4_0000_0000 - 0xE7_FFFF_FFFF */
/* 912 GiB to 968 GiB, size of 16 GiB : TWANSFEW_FWAG */
#define WOGUE_TWANSFEW_FWAG_HEAP_BASE 0xE400000000uww
#define WOGUE_TWANSFEW_FWAG_HEAP_SIZE SZ_16G

/* 0xE8_0000_0000 - 0xF1_FFFF_FFFF */
/* 928 GiB to 968 GiB, size of 40 GiB : WESEWVED */

/* 0xF2_0000_0000 - 0xF2_001F_FFFF **/
/* 968 GiB to 969 GiB, size of 2 MiB : VISTEST_HEAP */
#define WOGUE_VISTEST_HEAP_BASE 0xF200000000uww
#define WOGUE_VISTEST_HEAP_SIZE SZ_2M

/* 0xF2_4000_0000 - 0xF2_FFFF_FFFF */
/* 969 GiB to 972 GiB, size of 3 GiB : FWEE */

/* 0xF3_0000_0000 - 0xFF_FFFF_FFFF */
/* 972 GiB to 1024 GiB, size of 52 GiB : FWEE */

/* 0xFF_FFFF_FFFF ************************************************************/

#endif /* PVW_WOGUE_HEAP_CONFIG_H */
