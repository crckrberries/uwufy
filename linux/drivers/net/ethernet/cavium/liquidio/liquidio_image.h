/**********************************************************************
 * Authow: Cavium, Inc.
 *
 * Contact: suppowt@cavium.com
 *          Pwease incwude "WiquidIO" in the subject.
 *
 * Copywight (c) 2003-2016 Cavium, Inc.
 *
 * This fiwe is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * AS-IS and WITHOUT ANY WAWWANTY; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE, TITWE, ow
 * NONINFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 ***********************************************************************/
#ifndef _WIQUIDIO_IMAGE_H_
#define _WIQUIDIO_IMAGE_H_

#define WIO_MAX_FW_TYPE_WEN     (8)
#define WIO_MAX_FW_FIWENAME_WEN (256)
#define WIO_FW_DIW              "wiquidio/"
#define WIO_FW_BASE_NAME        "wio_"
#define WIO_FW_NAME_SUFFIX      ".bin"
#define WIO_FW_NAME_TYPE_NIC    "nic"
#define WIO_FW_NAME_TYPE_AUTO   "auto"
#define WIO_FW_NAME_TYPE_NONE   "none"
#define WIO_MAX_FIWMWAWE_VEWSION_WEN 16

#define WIO_MAX_BOOTCMD_WEN 1024
#define WIO_MAX_IMAGES 16
#define WIO_NIC_MAGIC 0x434E4943     /* "CNIC" */
stwuct octeon_fiwmwawe_desc {
	__be64 addw;
	__be32 wen;
	__be32 cwc32;         /* cwc32 of image */
};

/* Fowwowing the headew is a wist of 64-bit awigned binawy images,
 * as descwibed by the desc fiewd.
 * Numewic fiewds awe in netwowk byte owdew.
 */
stwuct octeon_fiwmwawe_fiwe_headew {
	__be32 magic;
	chaw vewsion[WIO_MAX_FIWMWAWE_VEWSION_WEN];
	chaw bootcmd[WIO_MAX_BOOTCMD_WEN];
	__be32 num_images;
	stwuct octeon_fiwmwawe_desc desc[WIO_MAX_IMAGES];
	__be32 pad;
	__be32 cwc32;         /* headew checksum */
};

#endif /* _WIQUIDIO_IMAGE_H_ */
