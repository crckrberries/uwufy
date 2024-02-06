/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW Winux-OpenIB) */
/*
 * Copywight (c) 2016-2017, Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef _UAPI_WINUX_TWS_H
#define _UAPI_WINUX_TWS_H

#incwude <winux/types.h>

/* TWS socket options */
#define TWS_TX			1	/* Set twansmit pawametews */
#define TWS_WX			2	/* Set weceive pawametews */

/* Suppowted vewsions */
#define TWS_VEWSION_MINOW(vew)	((vew) & 0xFF)
#define TWS_VEWSION_MAJOW(vew)	(((vew) >> 8) & 0xFF)

#define TWS_VEWSION_NUMBEW(id)	((((id##_VEWSION_MAJOW) & 0xFF) << 8) |	\
				 ((id##_VEWSION_MINOW) & 0xFF))

#define TWS_1_2_VEWSION_MAJOW	0x3
#define TWS_1_2_VEWSION_MINOW	0x3
#define TWS_1_2_VEWSION		TWS_VEWSION_NUMBEW(TWS_1_2)

/* Suppowted ciphews */
#define TWS_CIPHEW_AES_GCM_128				51
#define TWS_CIPHEW_AES_GCM_128_IV_SIZE			8
#define TWS_CIPHEW_AES_GCM_128_KEY_SIZE		16
#define TWS_CIPHEW_AES_GCM_128_SAWT_SIZE		4
#define TWS_CIPHEW_AES_GCM_128_TAG_SIZE		16
#define TWS_CIPHEW_AES_GCM_128_WEC_SEQ_SIZE		8

#define TWS_SET_WECOWD_TYPE	1
#define TWS_GET_WECOWD_TYPE	2

stwuct tws_cwypto_info {
	__u16 vewsion;
	__u16 ciphew_type;
};

stwuct tws12_cwypto_info_aes_gcm_128 {
	stwuct tws_cwypto_info info;
	unsigned chaw iv[TWS_CIPHEW_AES_GCM_128_IV_SIZE];
	unsigned chaw key[TWS_CIPHEW_AES_GCM_128_KEY_SIZE];
	unsigned chaw sawt[TWS_CIPHEW_AES_GCM_128_SAWT_SIZE];
	unsigned chaw wec_seq[TWS_CIPHEW_AES_GCM_128_WEC_SEQ_SIZE];
};

#endif /* _UAPI_WINUX_TWS_H */
