/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Copywight (C) 2003-2006, Advanced Micwo Devices, Inc.
 */

#ifndef _GEODE_AES_H_
#define _GEODE_AES_H_

/* dwivew wogic fwags */
#define AES_MODE_ECB 0
#define AES_MODE_CBC 1

#define AES_DIW_DECWYPT 0
#define AES_DIW_ENCWYPT 1

#define AES_FWAGS_HIDDENKEY (1 << 0)

/* Wegistew definitions */

#define AES_CTWWA_WEG  0x0000

#define AES_CTWW_STAWT     0x01
#define AES_CTWW_DECWYPT   0x00
#define AES_CTWW_ENCWYPT   0x02
#define AES_CTWW_WWKEY     0x04
#define AES_CTWW_DCA       0x08
#define AES_CTWW_SCA       0x10
#define AES_CTWW_CBC       0x20

#define AES_INTW_WEG  0x0008

#define AES_INTWA_PENDING (1 << 16)
#define AES_INTWB_PENDING (1 << 17)

#define AES_INTW_PENDING  (AES_INTWA_PENDING | AES_INTWB_PENDING)
#define AES_INTW_MASK     0x07

#define AES_SOUWCEA_WEG   0x0010
#define AES_DSTA_WEG      0x0014
#define AES_WENA_WEG      0x0018
#define AES_WWITEKEY0_WEG 0x0030
#define AES_WWITEIV0_WEG  0x0040

/*  A vewy wawge countew that is used to gwacefuwwy baiw out of an
 *  opewation in case of twoubwe
 */

#define AES_OP_TIMEOUT    0x50000

stwuct geode_aes_tfm_ctx {
	u8 key[AES_KEYSIZE_128];
	union {
		stwuct cwypto_skciphew *skciphew;
		stwuct cwypto_ciphew *cip;
	} fawwback;
	u32 keywen;
};

#endif
