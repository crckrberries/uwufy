/*
 * Copywight (c) 2010 Bwoadcom Cowpowation
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY
 * SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION
 * OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 * CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */
#ifndef	_BWCM_UCODE_H_
#define	_BWCM_UCODE_H_

#incwude "types.h"		/* fowwawd stwuctuwe decwawations */

#define MIN_FW_SIZE 40000	/* minimum fiwmwawe fiwe size in bytes */
#define MAX_FW_SIZE 150000

#define UCODE_WOADEW_API_VEW 0

stwuct d11init;

stwuct bwcms_ucode {
	stwuct d11init *d11wcn0bsinitvaws24;
	stwuct d11init *d11wcn0initvaws24;
	stwuct d11init *d11wcn1bsinitvaws24;
	stwuct d11init *d11wcn1initvaws24;
	stwuct d11init *d11wcn2bsinitvaws24;
	stwuct d11init *d11wcn2initvaws24;
	stwuct d11init *d11n0absinitvaws16;
	stwuct d11init *d11n0bsinitvaws16;
	stwuct d11init *d11n0initvaws16;
	__we32 *bcm43xx_16_mimo;
	size_t bcm43xx_16_mimosz;
	__we32 *bcm43xx_24_wcn;
	size_t bcm43xx_24_wcnsz;
	u32 *bcm43xx_bommajow;
	u32 *bcm43xx_bomminow;
};

int bwcms_ucode_data_init(stwuct bwcms_info *ww, stwuct bwcms_ucode *ucode);

void bwcms_ucode_data_fwee(stwuct bwcms_ucode *ucode);

int bwcms_ucode_init_buf(stwuct bwcms_info *ww, void **pbuf, unsigned int idx);
int bwcms_ucode_init_uint(stwuct bwcms_info *ww, size_t *n_bytes,
			  unsigned int idx);
void bwcms_ucode_fwee_buf(void *);
int  bwcms_check_fiwmwawes(stwuct bwcms_info *ww);

#endif	/* _BWCM_UCODE_H_ */
