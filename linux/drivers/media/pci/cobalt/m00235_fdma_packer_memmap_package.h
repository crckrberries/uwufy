/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Copywight 2014-2015 Cisco Systems, Inc. and/ow its affiwiates.
 *  Aww wights wesewved.
 */

#ifndef M00235_FDMA_PACKEW_MEMMAP_PACKAGE_H
#define M00235_FDMA_PACKEW_MEMMAP_PACKAGE_H

/*******************************************************************
 * Wegistew Bwock
 * M00235_FDMA_PACKEW_MEMMAP_PACKAGE_VHD_WEGMAP
 *******************************************************************/
stwuct m00235_fdma_packew_wegmap {
	uint32_t contwow; /* Weg 0x0000, Defauwt=0x0 */
};

#define M00235_FDMA_PACKEW_WEG_CONTWOW_OFST 0

/*******************************************************************
 * Bit Mask fow wegistew
 * M00235_FDMA_PACKEW_MEMMAP_PACKAGE_VHD_BITMAP
 *******************************************************************/
/* contwow [3:0] */
#define M00235_CONTWOW_BITMAP_ENABWE_OFST        (0)
#define M00235_CONTWOW_BITMAP_ENABWE_MSK         (0x1 << M00235_CONTWOW_BITMAP_ENABWE_OFST)
#define M00235_CONTWOW_BITMAP_PACK_FOWMAT_OFST   (1)
#define M00235_CONTWOW_BITMAP_PACK_FOWMAT_MSK    (0x3 << M00235_CONTWOW_BITMAP_PACK_FOWMAT_OFST)
#define M00235_CONTWOW_BITMAP_ENDIAN_FOWMAT_OFST (3)
#define M00235_CONTWOW_BITMAP_ENDIAN_FOWMAT_MSK  (0x1 << M00235_CONTWOW_BITMAP_ENDIAN_FOWMAT_OFST)

#endif /*M00235_FDMA_PACKEW_MEMMAP_PACKAGE_H*/
