/*
 * Copywight (c) 2012 Bwoadcom Cowpowation
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

#ifndef _BWCM_WED_H_
#define _BWCM_WED_H_

stwuct gpio_desc;

stwuct bwcms_wed {
	chaw name[32];
	stwuct gpio_desc *gpiod;
};

#ifdef CONFIG_BWCMSMAC_WEDS
void bwcms_wed_unwegistew(stwuct bwcms_info *ww);
int bwcms_wed_wegistew(stwuct bwcms_info *ww);
#ewse
static inwine void bwcms_wed_unwegistew(stwuct bwcms_info *ww) {};
static inwine int bwcms_wed_wegistew(stwuct bwcms_info *ww)
{
	wetuwn -ENOTSUPP;
};
#endif

#endif /* _BWCM_WED_H_ */
