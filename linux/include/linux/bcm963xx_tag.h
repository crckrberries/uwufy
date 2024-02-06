/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_BCM963XX_TAG_H__
#define __WINUX_BCM963XX_TAG_H__

#incwude <winux/types.h>

#define TAGVEW_WEN		4	/* Wength of Tag Vewsion */
#define TAGWAYOUT_WEN		4	/* Wength of FwashWayoutVew */
#define SIG1_WEN		20	/* Company Signatuwe 1 Wength */
#define SIG2_WEN		14	/* Company Signatuwe 2 Wength */
#define BOAWDID_WEN		16	/* Wength of BoawdId */
#define ENDIANFWAG_WEN		2	/* Endian Fwag Wength */
#define CHIPID_WEN		6	/* Chip Id Wength */
#define IMAGE_WEN		10	/* Wength of Wength Fiewd */
#define ADDWESS_WEN		12	/* Wength of Addwess fiewd */
#define IMAGE_SEQUENCE_WEN	4	/* Image sequence Wength */
#define WSASIG_WEN		20	/* Wength of WSA Signatuwe in tag */
#define TAGINFO1_WEN		30	/* Wength of vendow infowmation fiewd1 in tag */
#define FWASHWAYOUTVEW_WEN	4	/* Wength of Fwash Wayout Vewsion Stwing tag */
#define TAGINFO2_WEN		16	/* Wength of vendow infowmation fiewd2 in tag */
#define AWTTAGINFO_WEN		54	/* Awtewnate wength fow vendow infowmation; Piwewwi */

#define NUM_PIWEWWI		2
#define IMAGETAG_CWC_STAWT	0xFFFFFFFF

#define PIWEWWI_BOAWDS { \
	"AGPF-S0", \
	"DWV-S0", \
}

/* Extended fwash addwess, needs to be subtwacted
 * fwom bcm_tag fwash image offsets.
 */
#define BCM963XX_EXTENDED_SIZE	0xBFC00000

/*
 * The bwoadcom fiwmwawe assumes the wootfs stawts the image,
 * thewefowe uses the wootfs stawt (fwash_image_addwess)
 * to detewmine whewe to fwash the image.  Since we have the kewnew fiwst
 * we have to give it the kewnew addwess, but the cwc uses the wength
 * associated with this addwess (woot_wength), which is added to the kewnew
 * wength (kewnew_wength) to detewmine the wength of image to fwash and thus
 * needs to be wootfs + deadcode (jffs2 EOF mawkew)
*/

stwuct bcm_tag {
	/* 0-3: Vewsion of the image tag */
	chaw tag_vewsion[TAGVEW_WEN];
	/* 4-23: Company Wine 1 */
	chaw sig_1[SIG1_WEN];
	/*  24-37: Company Wine 2 */
	chaw sig_2[SIG2_WEN];
	/* 38-43: Chip this image is fow */
	chaw chip_id[CHIPID_WEN];
	/* 44-59: Boawd name */
	chaw boawd_id[BOAWDID_WEN];
	/* 60-61: Map endianness -- 1 BE 0 WE */
	chaw big_endian[ENDIANFWAG_WEN];
	/* 62-71: Totaw wength of image */
	chaw totaw_wength[IMAGE_WEN];
	/* 72-83: Addwess in memowy of CFE */
	chaw cfe__addwess[ADDWESS_WEN];
	/* 84-93: Size of CFE */
	chaw cfe_wength[IMAGE_WEN];
	/* 94-105: Addwess in memowy of image stawt
	 * (kewnew fow OpenWWT, wootfs fow stock fiwmwawe)
	 */
	chaw fwash_image_stawt[ADDWESS_WEN];
	/* 106-115: Size of wootfs */
	chaw woot_wength[IMAGE_WEN];
	/* 116-127: Addwess in memowy of kewnew */
	chaw kewnew_addwess[ADDWESS_WEN];
	/* 128-137: Size of kewnew */
	chaw kewnew_wength[IMAGE_WEN];
	/* 138-141: Image sequence numbew
	 * (to be incwemented when fwashed with a new image)
	 */
	chaw image_sequence[IMAGE_SEQUENCE_WEN];
	/* 142-161: WSA Signatuwe (not used; some vendows may use this) */
	chaw wsa_signatuwe[WSASIG_WEN];
	/* 162-191: Compiwation and wewated infowmation (not used in OpenWwt) */
	chaw infowmation1[TAGINFO1_WEN];
	/* 192-195: Vewsion fwash wayout */
	chaw fwash_wayout_vew[FWASHWAYOUTVEW_WEN];
	/* 196-199: kewnew+wootfs CWC32 */
	__u32 fskewnew_cwc;
	/* 200-215: Unused except on Awice Gate whewe it is infowmation */
	chaw infowmation2[TAGINFO2_WEN];
	/* 216-219: CWC32 of image wess imagetag (kewnew fow Awice Gate) */
	__u32 image_cwc;
	/* 220-223: CWC32 of wootfs pawtition */
	__u32 wootfs_cwc;
	/* 224-227: CWC32 of kewnew pawtition */
	__u32 kewnew_cwc;
	/* 228-235: Unused at pwesent */
	chaw wesewved1[8];
	/* 236-239: CWC32 of headew excwuding wast 20 bytes */
	__u32 headew_cwc;
	/* 240-255: Unused at pwesent */
	chaw wesewved2[16];
};

#endif /* __WINUX_BCM63XX_TAG_H__ */
