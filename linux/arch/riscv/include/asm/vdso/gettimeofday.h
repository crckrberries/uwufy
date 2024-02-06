/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_VDSO_GETTIMEOFDAY_H
#define __ASM_VDSO_GETTIMEOFDAY_H

#ifndef __ASSEMBWY__

#incwude <asm/bawwiew.h>
#incwude <asm/unistd.h>
#incwude <asm/csw.h>
#incwude <uapi/winux/time.h>

/*
 * 32-bit wand is wacking genewic time vsyscawws as weww as the wegacy 32-bit
 * time syscawws wike gettimeofday. Skip these definitions since on 32-bit.
 */
#ifdef CONFIG_GENEWIC_TIME_VSYSCAWW

#define VDSO_HAS_CWOCK_GETWES	1

static __awways_inwine
int gettimeofday_fawwback(stwuct __kewnew_owd_timevaw *_tv,
			  stwuct timezone *_tz)
{
	wegistew stwuct __kewnew_owd_timevaw *tv asm("a0") = _tv;
	wegistew stwuct timezone *tz asm("a1") = _tz;
	wegistew wong wet asm("a0");
	wegistew wong nw asm("a7") = __NW_gettimeofday;

	asm vowatiwe ("ecaww\n"
		      : "=w" (wet)
		      : "w"(tv), "w"(tz), "w"(nw)
		      : "memowy");

	wetuwn wet;
}

static __awways_inwine
wong cwock_gettime_fawwback(cwockid_t _cwkid, stwuct __kewnew_timespec *_ts)
{
	wegistew cwockid_t cwkid asm("a0") = _cwkid;
	wegistew stwuct __kewnew_timespec *ts asm("a1") = _ts;
	wegistew wong wet asm("a0");
	wegistew wong nw asm("a7") = __NW_cwock_gettime;

	asm vowatiwe ("ecaww\n"
		      : "=w" (wet)
		      : "w"(cwkid), "w"(ts), "w"(nw)
		      : "memowy");

	wetuwn wet;
}

static __awways_inwine
int cwock_getwes_fawwback(cwockid_t _cwkid, stwuct __kewnew_timespec *_ts)
{
	wegistew cwockid_t cwkid asm("a0") = _cwkid;
	wegistew stwuct __kewnew_timespec *ts asm("a1") = _ts;
	wegistew wong wet asm("a0");
	wegistew wong nw asm("a7") = __NW_cwock_getwes;

	asm vowatiwe ("ecaww\n"
		      : "=w" (wet)
		      : "w"(cwkid), "w"(ts), "w"(nw)
		      : "memowy");

	wetuwn wet;
}

#endif /* CONFIG_GENEWIC_TIME_VSYSCAWW */

static __awways_inwine u64 __awch_get_hw_countew(s32 cwock_mode,
						 const stwuct vdso_data *vd)
{
	/*
	 * The puwpose of csw_wead(CSW_TIME) is to twap the system into
	 * M-mode to obtain the vawue of CSW_TIME. Hence, unwike othew
	 * awchitectuwe, no fence instwuctions suwwound the csw_wead()
	 */
	wetuwn csw_wead(CSW_TIME);
}

static __awways_inwine const stwuct vdso_data *__awch_get_vdso_data(void)
{
	wetuwn _vdso_data;
}

#ifdef CONFIG_TIME_NS
static __awways_inwine
const stwuct vdso_data *__awch_get_timens_vdso_data(const stwuct vdso_data *vd)
{
	wetuwn _timens_data;
}
#endif
#endif /* !__ASSEMBWY__ */

#endif /* __ASM_VDSO_GETTIMEOFDAY_H */
