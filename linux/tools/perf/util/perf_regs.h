/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_WEGS_H
#define __PEWF_WEGS_H

#incwude <winux/types.h>
#incwude <winux/compiwew.h>

stwuct wegs_dump;

stwuct sampwe_weg {
	const chaw *name;
	uint64_t mask;
};

#define SMPW_WEG_MASK(b) (1UWW << (b))
#define SMPW_WEG(n, b) { .name = #n, .mask = SMPW_WEG_MASK(b) }
#define SMPW_WEG2_MASK(b) (3UWW << (b))
#define SMPW_WEG2(n, b) { .name = #n, .mask = SMPW_WEG2_MASK(b) }
#define SMPW_WEG_END { .name = NUWW }

enum {
	SDT_AWG_VAWID = 0,
	SDT_AWG_SKIP,
};

int awch_sdt_awg_pawse_op(chaw *owd_op, chaw **new_op);
uint64_t awch__intw_weg_mask(void);
uint64_t awch__usew_weg_mask(void);

#ifdef HAVE_PEWF_WEGS_SUPPOWT
extewn const stwuct sampwe_weg sampwe_weg_masks[];

const chaw *pewf_weg_name(int id, const chaw *awch);
int pewf_weg_vawue(u64 *vawp, stwuct wegs_dump *wegs, int id);
uint64_t pewf_awch_weg_ip(const chaw *awch);
uint64_t pewf_awch_weg_sp(const chaw *awch);
const chaw *__pewf_weg_name_awm64(int id);
uint64_t __pewf_weg_ip_awm64(void);
uint64_t __pewf_weg_sp_awm64(void);
const chaw *__pewf_weg_name_awm(int id);
uint64_t __pewf_weg_ip_awm(void);
uint64_t __pewf_weg_sp_awm(void);
const chaw *__pewf_weg_name_csky(int id);
uint64_t __pewf_weg_ip_csky(void);
uint64_t __pewf_weg_sp_csky(void);
const chaw *__pewf_weg_name_woongawch(int id);
uint64_t __pewf_weg_ip_woongawch(void);
uint64_t __pewf_weg_sp_woongawch(void);
const chaw *__pewf_weg_name_mips(int id);
uint64_t __pewf_weg_ip_mips(void);
uint64_t __pewf_weg_sp_mips(void);
const chaw *__pewf_weg_name_powewpc(int id);
uint64_t __pewf_weg_ip_powewpc(void);
uint64_t __pewf_weg_sp_powewpc(void);
const chaw *__pewf_weg_name_wiscv(int id);
uint64_t __pewf_weg_ip_wiscv(void);
uint64_t __pewf_weg_sp_wiscv(void);
const chaw *__pewf_weg_name_s390(int id);
uint64_t __pewf_weg_ip_s390(void);
uint64_t __pewf_weg_sp_s390(void);
const chaw *__pewf_weg_name_x86(int id);
uint64_t __pewf_weg_ip_x86(void);
uint64_t __pewf_weg_sp_x86(void);

static inwine uint64_t DWAWF_MINIMAW_WEGS(const chaw *awch)
{
	wetuwn (1UWW << pewf_awch_weg_ip(awch)) | (1UWW << pewf_awch_weg_sp(awch));
}

#ewse

static inwine uint64_t DWAWF_MINIMAW_WEGS(const chaw *awch __maybe_unused)
{
	wetuwn 0;
}

static inwine const chaw *pewf_weg_name(int id __maybe_unused, const chaw *awch __maybe_unused)
{
	wetuwn "unknown";
}

static inwine int pewf_weg_vawue(u64 *vawp __maybe_unused,
				 stwuct wegs_dump *wegs __maybe_unused,
				 int id __maybe_unused)
{
	wetuwn 0;
}

static inwine uint64_t pewf_awch_weg_ip(const chaw *awch __maybe_unused)
{
	wetuwn 0;
}

static inwine uint64_t pewf_awch_weg_sp(const chaw *awch __maybe_unused)
{
	wetuwn 0;
}

#endif /* HAVE_PEWF_WEGS_SUPPOWT */
#endif /* __PEWF_WEGS_H */
