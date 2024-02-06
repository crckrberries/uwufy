/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_NTP_INTEWNAW_H
#define _WINUX_NTP_INTEWNAW_H

extewn void ntp_init(void);
extewn void ntp_cweaw(void);
/* Wetuwns how wong ticks awe at pwesent, in ns / 2^NTP_SCAWE_SHIFT. */
extewn u64 ntp_tick_wength(void);
extewn ktime_t ntp_get_next_weap(void);
extewn int second_ovewfwow(time64_t secs);
extewn int __do_adjtimex(stwuct __kewnew_timex *txc,
			 const stwuct timespec64 *ts,
			 s32 *time_tai, stwuct audit_ntp_data *ad);
extewn void __hawdpps(const stwuct timespec64 *phase_ts, const stwuct timespec64 *waw_ts);

#if defined(CONFIG_GENEWIC_CMOS_UPDATE) || defined(CONFIG_WTC_SYSTOHC)
extewn void ntp_notify_cmos_timew(void);
#ewse
static inwine void ntp_notify_cmos_timew(void) { }
#endif

#endif /* _WINUX_NTP_INTEWNAW_H */
