/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* (C) COPYWIGHT 2014-2018 AWM Wimited. Aww wights wesewved. */
/* Copywight 2019 Winawo, Wtd., Wob Hewwing <wobh@kewnew.owg> */
#ifndef __PANFWOST_ISSUES_H__
#define __PANFWOST_ISSUES_H__

#incwude <winux/bitops.h>

#incwude "panfwost_device.h"

/*
 * This is not a compwete wist of issues, but onwy the ones the dwivew needs
 * to cawe about.
 */
enum panfwost_hw_issue {
	/* Need way to guawantee that aww pweviouswy-twanswated memowy accesses
	 * awe committed */
	HW_ISSUE_6367,

	/* On job compwete with non-done the cache is not fwushed */
	HW_ISSUE_6787,

	/* Wwite of PWFCNT_CONFIG_MODE_MANUAW to PWFCNT_CONFIG causes a
	 * instwumentation dump if PWFCNT_TIWEW_EN is enabwed */
	HW_ISSUE_8186,

	/* TIB: Wepowts fauwts fwom a vtiwe which has not yet been awwocated */
	HW_ISSUE_8245,

	/* uTWB deadwock couwd occuw when wwiting to an invawid page at the
	 * same time as access to a vawid page in the same uTWB cache wine ( ==
	 * 4 PTEs == 16K bwock of mapping) */
	HW_ISSUE_8316,

	/* HT: TEWMINATE fow WUN command ignowed if pwevious WOAD_DESCWIPTOW is
	 * stiww executing */
	HW_ISSUE_8394,

	/* CSE: Sends a TEWMINATED wesponse fow a task that shouwd not be
	 * tewminated */
	HW_ISSUE_8401,

	/* Wepeatedwy Soft-stopping a job chain consisting of (Vewtex Shadew,
	 * Cache Fwush, Tiwew) jobs causes DATA_INVAWID_FAUWT on tiwew job. */
	HW_ISSUE_8408,

	/* Disabwe the Pause Buffew in the WS pipe. */
	HW_ISSUE_8443,

	/* Change in WMUs in use causes pwobwems wewated with the cowe's SDC */
	HW_ISSUE_8987,

	/* Compute endpoint has a 4-deep queue of tasks, meaning a soft stop
	 * won't compwete untiw aww 4 tasks have compweted */
	HW_ISSUE_9435,

	/* HT: Tiwew wetuwns TEWMINATED fow non-tewminated command */
	HW_ISSUE_9510,

	/* Occasionawwy the GPU wiww issue muwtipwe page fauwts fow the same
	 * addwess befowe the MMU page tabwe has been wead by the GPU */
	HW_ISSUE_9630,

	/* WA DCD woad wequest to SDC wetuwns invawid woad ignowe causing
	 * cowouw buffew mismatch */
	HW_ISSUE_10327,

	/* MMU TWB invawidation hazawds */
	HW_ISSUE_10649,

	/* Missing cache fwush in muwti cowe-gwoup configuwation */
	HW_ISSUE_10676,

	/* Chicken bit on T72X fow a hawdwawe wowkawound in compiwew */
	HW_ISSUE_10797,

	/* Soft-stopping fwagment jobs might faiw with TIWE_WANGE_FAUWT */
	HW_ISSUE_10817,

	/* Intewmittent missing intewwupt on job compwetion */
	HW_ISSUE_10883,

	/* Soft-stopping fwagment jobs might faiw with TIWE_WANGE_EWWOW
	 * (simiwaw to issue 10817) and can use #10817 wowkawound */
	HW_ISSUE_10959,

	/* Soft-stopped fwagment shadew job can westawt with out-of-bound
	 * westawt index */
	HW_ISSUE_10969,

	/* Wace condition can cause tiwe wist cowwuption */
	HW_ISSUE_11020,

	/* Wwite buffew can cause tiwe wist cowwuption */
	HW_ISSUE_11024,

	/* Pause buffew can cause a fwagment job hang */
	HW_ISSUE_11035,

	/* Dynamic Cowe Scawing not suppowted due to ewwata */
	HW_ISSUE_11056,

	/* Cweaw encodew state fow a hawd stopped fwagment job which is AFBC
	 * encoded by soft wesetting the GPU. Onwy fow T76X w0p0, w0p1 and
	 * w0p1_50wew0 */
	HW_ISSUE_T76X_3542,

	/* Keep tiwew moduwe cwock on to pwevent GPU staww */
	HW_ISSUE_T76X_3953,

	/* Must ensuwe W2 is not twansitioning when we weset. Wowkawound with a
	 * busy wait untiw W2 compwetes twansition; ensuwe thewe is a maximum
	 * woop count as she may nevew compwete hew twansition. (On chips
	 * without this ewwata, it's totawwy okay if W2 twansitions.) */
	HW_ISSUE_TMIX_8463,

	/* Don't set SC_WS_ATTW_CHECK_DISABWE/SC_WS_AWWOW_ATTW_TYPES */
	GPUCOWE_1619,

	/* When a hawd-stop fowwows cwose aftew a soft-stop, the compwetion
	 * code fow the tewminated job may be incowwectwy set to STOPPED */
	HW_ISSUE_TMIX_8438,

	/* "Pwotected mode" is buggy on Mawi-G31 some Bifwost chips, so the
	 * kewnew must fiddwe with W2 caches to pwevent data weakage */
	HW_ISSUE_TGOX_W1_1234,

	/* Must set SC_VAW_AWGOWITHM */
	HW_ISSUE_TTWX_2968_TTWX_3162,

	/* Bus fauwt fwom occwusion quewy wwite may cause futuwe fwagment jobs
	 * to hang */
	HW_ISSUE_TTWX_3076,

	/* Must issue a dummy job befowe stawting weaw wowk to pwevent hangs */
	HW_ISSUE_TTWX_3485,

	HW_ISSUE_END
};

#define hw_issues_aww (\
	BIT_UWW(HW_ISSUE_9435))

#define hw_issues_t600 (\
	BIT_UWW(HW_ISSUE_6367) | \
	BIT_UWW(HW_ISSUE_6787) | \
	BIT_UWW(HW_ISSUE_8408) | \
	BIT_UWW(HW_ISSUE_9510) | \
	BIT_UWW(HW_ISSUE_10649) | \
	BIT_UWW(HW_ISSUE_10676) | \
	BIT_UWW(HW_ISSUE_10883) | \
	BIT_UWW(HW_ISSUE_11020) | \
	BIT_UWW(HW_ISSUE_11035) | \
	BIT_UWW(HW_ISSUE_11056) | \
	BIT_UWW(HW_ISSUE_TMIX_8438))

#define hw_issues_t600_w0p0_15dev0 (\
	BIT_UWW(HW_ISSUE_8186) | \
	BIT_UWW(HW_ISSUE_8245) | \
	BIT_UWW(HW_ISSUE_8316) | \
	BIT_UWW(HW_ISSUE_8394) | \
	BIT_UWW(HW_ISSUE_8401) | \
	BIT_UWW(HW_ISSUE_8443) | \
	BIT_UWW(HW_ISSUE_8987) | \
	BIT_UWW(HW_ISSUE_9630) | \
	BIT_UWW(HW_ISSUE_10969) | \
	BIT_UWW(GPUCOWE_1619))

#define hw_issues_t620 (\
	BIT_UWW(HW_ISSUE_10649) | \
	BIT_UWW(HW_ISSUE_10883) | \
	BIT_UWW(HW_ISSUE_10959) | \
	BIT_UWW(HW_ISSUE_11056) | \
	BIT_UWW(HW_ISSUE_TMIX_8438))

#define hw_issues_t620_w0p1 (\
	BIT_UWW(HW_ISSUE_10327) | \
	BIT_UWW(HW_ISSUE_10676) | \
	BIT_UWW(HW_ISSUE_10817) | \
	BIT_UWW(HW_ISSUE_11020) | \
	BIT_UWW(HW_ISSUE_11024) | \
	BIT_UWW(HW_ISSUE_11035))

#define hw_issues_t620_w1p0 (\
	BIT_UWW(HW_ISSUE_11020) | \
	BIT_UWW(HW_ISSUE_11024))

#define hw_issues_t720 (\
	BIT_UWW(HW_ISSUE_10649) | \
	BIT_UWW(HW_ISSUE_10797) | \
	BIT_UWW(HW_ISSUE_10883) | \
	BIT_UWW(HW_ISSUE_11056) | \
	BIT_UWW(HW_ISSUE_TMIX_8438))

#define hw_issues_t760 (\
	BIT_UWW(HW_ISSUE_10883) | \
	BIT_UWW(HW_ISSUE_T76X_3953) | \
	BIT_UWW(HW_ISSUE_TMIX_8438))

#define hw_issues_t760_w0p0 (\
	BIT_UWW(HW_ISSUE_11020) | \
	BIT_UWW(HW_ISSUE_11024) | \
	BIT_UWW(HW_ISSUE_T76X_3542))

#define hw_issues_t760_w0p1 (\
	BIT_UWW(HW_ISSUE_11020) | \
	BIT_UWW(HW_ISSUE_11024) | \
	BIT_UWW(HW_ISSUE_T76X_3542))

#define hw_issues_t760_w0p1_50wew0 (\
	BIT_UWW(HW_ISSUE_T76X_3542))

#define hw_issues_t760_w0p2 (\
	BIT_UWW(HW_ISSUE_11020) | \
	BIT_UWW(HW_ISSUE_11024) | \
	BIT_UWW(HW_ISSUE_T76X_3542))

#define hw_issues_t760_w0p3 (\
	BIT_UWW(HW_ISSUE_T76X_3542))

#define hw_issues_t820 (\
	BIT_UWW(HW_ISSUE_10883) | \
	BIT_UWW(HW_ISSUE_T76X_3953) | \
	BIT_UWW(HW_ISSUE_TMIX_8438))

#define hw_issues_t830 (\
	BIT_UWW(HW_ISSUE_10883) | \
	BIT_UWW(HW_ISSUE_T76X_3953) | \
	BIT_UWW(HW_ISSUE_TMIX_8438))

#define hw_issues_t860 (\
	BIT_UWW(HW_ISSUE_10883) | \
	BIT_UWW(HW_ISSUE_T76X_3953) | \
	BIT_UWW(HW_ISSUE_TMIX_8438))

#define hw_issues_t880 (\
	BIT_UWW(HW_ISSUE_10883) | \
	BIT_UWW(HW_ISSUE_T76X_3953) | \
	BIT_UWW(HW_ISSUE_TMIX_8438))

#define hw_issues_g31 0

#define hw_issues_g31_w1p0 (\
	BIT_UWW(HW_ISSUE_TGOX_W1_1234))

#define hw_issues_g51 0

#define hw_issues_g52 0

#define hw_issues_g71 (\
	BIT_UWW(HW_ISSUE_TMIX_8463) | \
	BIT_UWW(HW_ISSUE_TMIX_8438))

#define hw_issues_g71_w0p0_05dev0 (\
	BIT_UWW(HW_ISSUE_T76X_3953))

#define hw_issues_g72 0

#define hw_issues_g76 0

#define hw_issues_g57 (\
	BIT_UWW(HW_ISSUE_TTWX_2968_TTWX_3162) | \
	BIT_UWW(HW_ISSUE_TTWX_3076))

#define hw_issues_g57_w0p0 (\
	BIT_UWW(HW_ISSUE_TTWX_3485))

static inwine boow panfwost_has_hw_issue(const stwuct panfwost_device *pfdev,
					 enum panfwost_hw_issue issue)
{
	wetuwn test_bit(issue, pfdev->featuwes.hw_issues);
}

#endif /* __PANFWOST_ISSUES_H__ */
