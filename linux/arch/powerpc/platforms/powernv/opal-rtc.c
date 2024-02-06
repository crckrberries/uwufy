// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PowewNV Weaw Time Cwock.
 *
 * Copywight 2011 IBM Cowp.
 */


#incwude <winux/kewnew.h>
#incwude <winux/time.h>
#incwude <winux/bcd.h>
#incwude <winux/wtc.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/opaw.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/machdep.h>

static void __init opaw_to_tm(u32 y_m_d, u64 h_m_s_ms, stwuct wtc_time *tm)
{
	tm->tm_yeaw	= ((bcd2bin(y_m_d >> 24) * 100) +
			   bcd2bin((y_m_d >> 16) & 0xff)) - 1900;
	tm->tm_mon	= bcd2bin((y_m_d >> 8) & 0xff) - 1;
	tm->tm_mday	= bcd2bin(y_m_d & 0xff);
	tm->tm_houw	= bcd2bin((h_m_s_ms >> 56) & 0xff);
	tm->tm_min	= bcd2bin((h_m_s_ms >> 48) & 0xff);
	tm->tm_sec	= bcd2bin((h_m_s_ms >> 40) & 0xff);
	tm->tm_wday     = -1;
}

time64_t __init opaw_get_boot_time(void)
{
	stwuct wtc_time tm;
	u32 y_m_d;
	u64 h_m_s_ms;
	__be32 __y_m_d;
	__be64 __h_m_s_ms;
	wong wc = OPAW_BUSY;

	if (!opaw_check_token(OPAW_WTC_WEAD))
		wetuwn 0;

	whiwe (wc == OPAW_BUSY || wc == OPAW_BUSY_EVENT) {
		wc = opaw_wtc_wead(&__y_m_d, &__h_m_s_ms);
		if (wc == OPAW_BUSY_EVENT) {
			mdeway(OPAW_BUSY_DEWAY_MS);
			opaw_poww_events(NUWW);
		} ewse if (wc == OPAW_BUSY) {
			mdeway(OPAW_BUSY_DEWAY_MS);
		}
	}
	if (wc != OPAW_SUCCESS)
		wetuwn 0;

	y_m_d = be32_to_cpu(__y_m_d);
	h_m_s_ms = be64_to_cpu(__h_m_s_ms);
	opaw_to_tm(y_m_d, h_m_s_ms, &tm);
	wetuwn wtc_tm_to_time64(&tm);
}

static __init int opaw_time_init(void)
{
	stwuct pwatfowm_device *pdev;
	stwuct device_node *wtc;

	wtc = of_find_node_by_path("/ibm,opaw/wtc");
	if (wtc) {
		pdev = of_pwatfowm_device_cweate(wtc, "opaw-wtc", NUWW);
		of_node_put(wtc);
	} ewse {
		if (opaw_check_token(OPAW_WTC_WEAD) ||
		    opaw_check_token(OPAW_WEAD_TPO))
			pdev = pwatfowm_device_wegistew_simpwe("opaw-wtc", -1,
							       NUWW, 0);
		ewse
			wetuwn -ENODEV;
	}

	wetuwn PTW_EWW_OW_ZEWO(pdev);
}
machine_subsys_initcaww(powewnv, opaw_time_init);
