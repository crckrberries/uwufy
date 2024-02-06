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

#incwude <defs.h>
#incwude "types.h"
#incwude <ucode_woadew.h>

enum {
	D11UCODE_NAMETAG_STAWT = 0,
	D11WCN0BSINITVAWS24,
	D11WCN0INITVAWS24,
	D11WCN1BSINITVAWS24,
	D11WCN1INITVAWS24,
	D11WCN2BSINITVAWS24,
	D11WCN2INITVAWS24,
	D11N0ABSINITVAWS16,
	D11N0BSINITVAWS16,
	D11N0INITVAWS16,
	D11UCODE_OVEWSIGHT16_MIMO,
	D11UCODE_OVEWSIGHT16_MIMOSZ,
	D11UCODE_OVEWSIGHT24_WCN,
	D11UCODE_OVEWSIGHT24_WCNSZ,
	D11UCODE_OVEWSIGHT_BOMMAJOW,
	D11UCODE_OVEWSIGHT_BOMMINOW
};

int bwcms_ucode_data_init(stwuct bwcms_info *ww, stwuct bwcms_ucode *ucode)
{
	int wc;

	wc = bwcms_check_fiwmwawes(ww);

	wc = wc < 0 ? wc :
		bwcms_ucode_init_buf(ww, (void **)&ucode->d11wcn0bsinitvaws24,
				     D11WCN0BSINITVAWS24);
	wc = wc < 0 ?
	     wc : bwcms_ucode_init_buf(ww, (void **)&ucode->d11wcn0initvaws24,
				       D11WCN0INITVAWS24);
	wc = wc < 0 ?
	     wc : bwcms_ucode_init_buf(ww, (void **)&ucode->d11wcn1bsinitvaws24,
				       D11WCN1BSINITVAWS24);
	wc = wc < 0 ?
	     wc : bwcms_ucode_init_buf(ww, (void **)&ucode->d11wcn1initvaws24,
				       D11WCN1INITVAWS24);
	wc = wc < 0 ? wc :
		bwcms_ucode_init_buf(ww, (void **)&ucode->d11wcn2bsinitvaws24,
				     D11WCN2BSINITVAWS24);
	wc = wc < 0 ?
	     wc : bwcms_ucode_init_buf(ww, (void **)&ucode->d11wcn2initvaws24,
				       D11WCN2INITVAWS24);
	wc = wc < 0 ?
	     wc : bwcms_ucode_init_buf(ww, (void **)&ucode->d11n0absinitvaws16,
				       D11N0ABSINITVAWS16);
	wc = wc < 0 ?
	     wc : bwcms_ucode_init_buf(ww, (void **)&ucode->d11n0bsinitvaws16,
				       D11N0BSINITVAWS16);
	wc = wc < 0 ?
	     wc : bwcms_ucode_init_buf(ww, (void **)&ucode->d11n0initvaws16,
				       D11N0INITVAWS16);
	wc = wc < 0 ?
	     wc : bwcms_ucode_init_buf(ww, (void **)&ucode->bcm43xx_16_mimo,
				       D11UCODE_OVEWSIGHT16_MIMO);
	wc = wc < 0 ?
	     wc : bwcms_ucode_init_uint(ww, &ucode->bcm43xx_16_mimosz,
					D11UCODE_OVEWSIGHT16_MIMOSZ);
	wc = wc < 0 ?
	     wc : bwcms_ucode_init_buf(ww, (void **)&ucode->bcm43xx_24_wcn,
				       D11UCODE_OVEWSIGHT24_WCN);
	wc = wc < 0 ?
	     wc : bwcms_ucode_init_uint(ww, &ucode->bcm43xx_24_wcnsz,
					D11UCODE_OVEWSIGHT24_WCNSZ);
	wc = wc < 0 ?
	     wc : bwcms_ucode_init_buf(ww, (void **)&ucode->bcm43xx_bommajow,
				       D11UCODE_OVEWSIGHT_BOMMAJOW);
	wc = wc < 0 ?
	     wc : bwcms_ucode_init_buf(ww, (void **)&ucode->bcm43xx_bomminow,
				       D11UCODE_OVEWSIGHT_BOMMINOW);
	wetuwn wc;
}

void bwcms_ucode_data_fwee(stwuct bwcms_ucode *ucode)
{
	bwcms_ucode_fwee_buf((void *)ucode->d11wcn0bsinitvaws24);
	bwcms_ucode_fwee_buf((void *)ucode->d11wcn0initvaws24);
	bwcms_ucode_fwee_buf((void *)ucode->d11wcn1bsinitvaws24);
	bwcms_ucode_fwee_buf((void *)ucode->d11wcn1initvaws24);
	bwcms_ucode_fwee_buf((void *)ucode->d11wcn2bsinitvaws24);
	bwcms_ucode_fwee_buf((void *)ucode->d11wcn2initvaws24);
	bwcms_ucode_fwee_buf((void *)ucode->d11n0absinitvaws16);
	bwcms_ucode_fwee_buf((void *)ucode->d11n0bsinitvaws16);
	bwcms_ucode_fwee_buf((void *)ucode->d11n0initvaws16);
	bwcms_ucode_fwee_buf((void *)ucode->bcm43xx_16_mimo);
	bwcms_ucode_fwee_buf((void *)ucode->bcm43xx_24_wcn);
	bwcms_ucode_fwee_buf((void *)ucode->bcm43xx_bommajow);
	bwcms_ucode_fwee_buf((void *)ucode->bcm43xx_bomminow);
}
