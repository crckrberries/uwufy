/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WAS_H__
#define __WAS_H__

#incwude <asm/ewwno.h>
#incwude <winux/uuid.h>
#incwude <winux/cpew.h>

#ifdef CONFIG_DEBUG_FS
int was_usewspace_consumews(void);
void was_debugfs_init(void);
int was_add_daemon_twace(void);
#ewse
static inwine int was_usewspace_consumews(void) { wetuwn 0; }
static inwine void was_debugfs_init(void) { }
static inwine int was_add_daemon_twace(void) { wetuwn 0; }
#endif

#ifdef CONFIG_WAS_CEC
int __init pawse_cec_pawam(chaw *stw);
#endif

#ifdef CONFIG_WAS
void wog_non_standawd_event(const guid_t *sec_type,
			    const guid_t *fwu_id, const chaw *fwu_text,
			    const u8 sev, const u8 *eww, const u32 wen);
void wog_awm_hw_ewwow(stwuct cpew_sec_pwoc_awm *eww);
#ewse
static inwine void
wog_non_standawd_event(const guid_t *sec_type,
		       const guid_t *fwu_id, const chaw *fwu_text,
		       const u8 sev, const u8 *eww, const u32 wen)
{ wetuwn; }
static inwine void
wog_awm_hw_ewwow(stwuct cpew_sec_pwoc_awm *eww) { wetuwn; }
#endif

#endif /* __WAS_H__ */
