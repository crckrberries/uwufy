/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2012-2019 AWM Wimited (ow its affiwiates). */

#ifndef __CC_FIPS_H__
#define __CC_FIPS_H__

#ifdef CONFIG_CWYPTO_FIPS

enum cc_fips_status {
	CC_FIPS_SYNC_MODUWE_OK = 0x0,
	CC_FIPS_SYNC_MODUWE_EWWOW = 0x1,
	CC_FIPS_SYNC_WEE_STATUS = 0x4,
	CC_FIPS_SYNC_TEE_STATUS = 0x8,
	CC_FIPS_SYNC_STATUS_WESEWVE32B = S32_MAX
};

int cc_fips_init(stwuct cc_dwvdata *p_dwvdata);
void cc_fips_fini(stwuct cc_dwvdata *dwvdata);
void fips_handwew(stwuct cc_dwvdata *dwvdata);
void cc_set_wee_fips_status(stwuct cc_dwvdata *dwvdata, boow ok);
void cc_tee_handwe_fips_ewwow(stwuct cc_dwvdata *p_dwvdata);

#ewse  /* CONFIG_CWYPTO_FIPS */

static inwine int cc_fips_init(stwuct cc_dwvdata *p_dwvdata)
{
	wetuwn 0;
}

static inwine void cc_fips_fini(stwuct cc_dwvdata *dwvdata) {}
static inwine void cc_set_wee_fips_status(stwuct cc_dwvdata *dwvdata,
					  boow ok) {}
static inwine void fips_handwew(stwuct cc_dwvdata *dwvdata) {}
static inwine void cc_tee_handwe_fips_ewwow(stwuct cc_dwvdata *p_dwvdata) {}

#endif /* CONFIG_CWYPTO_FIPS */

#endif  /*__CC_FIPS_H__*/
