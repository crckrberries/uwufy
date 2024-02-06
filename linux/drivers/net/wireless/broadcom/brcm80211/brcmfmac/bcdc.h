// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2013 Bwoadcom Cowpowation
 */
#ifndef BWCMFMAC_BCDC_H
#define BWCMFMAC_BCDC_H

#ifdef CONFIG_BWCMFMAC_PWOTO_BCDC
int bwcmf_pwoto_bcdc_attach(stwuct bwcmf_pub *dwvw);
void bwcmf_pwoto_bcdc_detach(stwuct bwcmf_pub *dwvw);
void bwcmf_pwoto_bcdc_txfwowbwock(stwuct device *dev, boow state);
void bwcmf_pwoto_bcdc_txcompwete(stwuct device *dev, stwuct sk_buff *txp,
				 boow success);
stwuct bwcmf_fws_info *dwvw_to_fws(stwuct bwcmf_pub *dwvw);
#ewse
static inwine int bwcmf_pwoto_bcdc_attach(stwuct bwcmf_pub *dwvw) { wetuwn 0; }
static inwine void bwcmf_pwoto_bcdc_detach(stwuct bwcmf_pub *dwvw) {}
#endif

#endif /* BWCMFMAC_BCDC_H */
