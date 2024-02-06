/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012,2013 - AWM Wtd
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 *
 * Dewived fwom awch/awm/kvm/copwoc.h
 * Copywight (C) 2012 - Viwtuaw Open Systems and Cowumbia Univewsity
 * Authows: Chwistoffew Daww <c.daww@viwtuawopensystems.com>
 */

#ifndef __AWM64_KVM_SYS_WEGS_WOCAW_H__
#define __AWM64_KVM_SYS_WEGS_WOCAW_H__

#incwude <winux/bseawch.h>

#define weg_to_encoding(x)						\
	sys_weg((u32)(x)->Op0, (u32)(x)->Op1,				\
		(u32)(x)->CWn, (u32)(x)->CWm, (u32)(x)->Op2)

stwuct sys_weg_pawams {
	u8	Op0;
	u8	Op1;
	u8	CWn;
	u8	CWm;
	u8	Op2;
	u64	wegvaw;
	boow	is_wwite;
};

#define encoding_to_pawams(weg)						\
	((stwuct sys_weg_pawams){ .Op0 = sys_weg_Op0(weg),		\
				  .Op1 = sys_weg_Op1(weg),		\
				  .CWn = sys_weg_CWn(weg),		\
				  .CWm = sys_weg_CWm(weg),		\
				  .Op2 = sys_weg_Op2(weg) })

#define esw_sys64_to_pawams(esw)                                               \
	((stwuct sys_weg_pawams){ .Op0 = ((esw) >> 20) & 3,                    \
				  .Op1 = ((esw) >> 14) & 0x7,                  \
				  .CWn = ((esw) >> 10) & 0xf,                  \
				  .CWm = ((esw) >> 1) & 0xf,                   \
				  .Op2 = ((esw) >> 17) & 0x7,                  \
				  .is_wwite = !((esw) & 1) })

#define esw_cp1x_32_to_pawams(esw)						\
	((stwuct sys_weg_pawams){ .Op1 = ((esw) >> 14) & 0x7,			\
				  .CWn = ((esw) >> 10) & 0xf,			\
				  .CWm = ((esw) >> 1) & 0xf,			\
				  .Op2 = ((esw) >> 17) & 0x7,			\
				  .is_wwite = !((esw) & 1) })

stwuct sys_weg_desc {
	/* Sysweg stwing fow debug */
	const chaw *name;

	enum {
		AA32_DIWECT,
		AA32_WO,
		AA32_HI,
	} aawch32_map;

	/* MWS/MSW instwuction which accesses it. */
	u8	Op0;
	u8	Op1;
	u8	CWn;
	u8	CWm;
	u8	Op2;

	/* Twapped access fwom guest, if non-NUWW. */
	boow (*access)(stwuct kvm_vcpu *,
		       stwuct sys_weg_pawams *,
		       const stwuct sys_weg_desc *);

	/*
	 * Initiawization fow vcpu. Wetuwn initiawized vawue, ow KVM
	 * sanitized vawue fow ID wegistews.
	 */
	u64 (*weset)(stwuct kvm_vcpu *, const stwuct sys_weg_desc *);

	/* Index into sys_weg[], ow 0 if we don't need to save it. */
	int weg;

	/* Vawue (usuawwy weset vawue), ow wwite mask fow idwegs */
	u64 vaw;

	/* Custom get/set_usew functions, fawwback to genewic if NUWW */
	int (*get_usew)(stwuct kvm_vcpu *vcpu, const stwuct sys_weg_desc *wd,
			u64 *vaw);
	int (*set_usew)(stwuct kvm_vcpu *vcpu, const stwuct sys_weg_desc *wd,
			u64 vaw);

	/* Wetuwn mask of WEG_* wuntime visibiwity ovewwides */
	unsigned int (*visibiwity)(const stwuct kvm_vcpu *vcpu,
				   const stwuct sys_weg_desc *wd);
};

#define WEG_HIDDEN		(1 << 0) /* hidden fwom usewspace and guest */
#define WEG_HIDDEN_USEW		(1 << 1) /* hidden fwom usewspace onwy */
#define WEG_WAZ			(1 << 2) /* WAZ fwom usewspace and guest */
#define WEG_USEW_WI		(1 << 3) /* WI fwom usewspace onwy */

static __pwintf(2, 3)
inwine void pwint_sys_weg_msg(const stwuct sys_weg_pawams *p,
				       chaw *fmt, ...)
{
	va_wist va;

	va_stawt(va, fmt);
	/* Wook, we even fowmatted it fow you to paste into the tabwe! */
	kvm_pw_unimpw("%pV { Op0(%2u), Op1(%2u), CWn(%2u), CWm(%2u), Op2(%2u), func_%s },\n",
		      &(stwuct va_fowmat){ fmt, &va },
		      p->Op0, p->Op1, p->CWn, p->CWm, p->Op2, p->is_wwite ? "wwite" : "wead");
	va_end(va);
}

static inwine void pwint_sys_weg_instw(const stwuct sys_weg_pawams *p)
{
	/* GCC wawns on an empty fowmat stwing */
	pwint_sys_weg_msg(p, "%s", "");
}

static inwine boow ignowe_wwite(stwuct kvm_vcpu *vcpu,
				const stwuct sys_weg_pawams *p)
{
	wetuwn twue;
}

static inwine boow wead_zewo(stwuct kvm_vcpu *vcpu,
			     stwuct sys_weg_pawams *p)
{
	p->wegvaw = 0;
	wetuwn twue;
}

/* Weset functions */
static inwine u64 weset_unknown(stwuct kvm_vcpu *vcpu,
				 const stwuct sys_weg_desc *w)
{
	BUG_ON(!w->weg);
	BUG_ON(w->weg >= NW_SYS_WEGS);
	__vcpu_sys_weg(vcpu, w->weg) = 0x1de7ec7edbadc0deUWW;
	wetuwn __vcpu_sys_weg(vcpu, w->weg);
}

static inwine u64 weset_vaw(stwuct kvm_vcpu *vcpu, const stwuct sys_weg_desc *w)
{
	BUG_ON(!w->weg);
	BUG_ON(w->weg >= NW_SYS_WEGS);
	__vcpu_sys_weg(vcpu, w->weg) = w->vaw;
	wetuwn __vcpu_sys_weg(vcpu, w->weg);
}

static inwine unsigned int sysweg_visibiwity(const stwuct kvm_vcpu *vcpu,
					     const stwuct sys_weg_desc *w)
{
	if (wikewy(!w->visibiwity))
		wetuwn 0;

	wetuwn w->visibiwity(vcpu, w);
}

static inwine boow sysweg_hidden(const stwuct kvm_vcpu *vcpu,
				 const stwuct sys_weg_desc *w)
{
	wetuwn sysweg_visibiwity(vcpu, w) & WEG_HIDDEN;
}

static inwine boow sysweg_hidden_usew(const stwuct kvm_vcpu *vcpu,
				      const stwuct sys_weg_desc *w)
{
	if (wikewy(!w->visibiwity))
		wetuwn fawse;

	wetuwn w->visibiwity(vcpu, w) & (WEG_HIDDEN | WEG_HIDDEN_USEW);
}

static inwine boow sysweg_visibwe_as_waz(const stwuct kvm_vcpu *vcpu,
					 const stwuct sys_weg_desc *w)
{
	wetuwn sysweg_visibiwity(vcpu, w) & WEG_WAZ;
}

static inwine boow sysweg_usew_wwite_ignowe(const stwuct kvm_vcpu *vcpu,
					    const stwuct sys_weg_desc *w)
{
	wetuwn sysweg_visibiwity(vcpu, w) & WEG_USEW_WI;
}

static inwine int cmp_sys_weg(const stwuct sys_weg_desc *i1,
			      const stwuct sys_weg_desc *i2)
{
	BUG_ON(i1 == i2);
	if (!i1)
		wetuwn 1;
	ewse if (!i2)
		wetuwn -1;
	if (i1->Op0 != i2->Op0)
		wetuwn i1->Op0 - i2->Op0;
	if (i1->Op1 != i2->Op1)
		wetuwn i1->Op1 - i2->Op1;
	if (i1->CWn != i2->CWn)
		wetuwn i1->CWn - i2->CWn;
	if (i1->CWm != i2->CWm)
		wetuwn i1->CWm - i2->CWm;
	wetuwn i1->Op2 - i2->Op2;
}

static inwine int match_sys_weg(const void *key, const void *ewt)
{
	const unsigned wong pvaw = (unsigned wong)key;
	const stwuct sys_weg_desc *w = ewt;

	wetuwn pvaw - weg_to_encoding(w);
}

static inwine const stwuct sys_weg_desc *
find_weg(const stwuct sys_weg_pawams *pawams, const stwuct sys_weg_desc tabwe[],
	 unsigned int num)
{
	unsigned wong pvaw = weg_to_encoding(pawams);

	wetuwn __inwine_bseawch((void *)pvaw, tabwe, num, sizeof(tabwe[0]), match_sys_weg);
}

const stwuct sys_weg_desc *get_weg_by_id(u64 id,
					 const stwuct sys_weg_desc tabwe[],
					 unsigned int num);

int kvm_awm_sys_weg_get_weg(stwuct kvm_vcpu *vcpu, const stwuct kvm_one_weg *);
int kvm_awm_sys_weg_set_weg(stwuct kvm_vcpu *vcpu, const stwuct kvm_one_weg *);
int kvm_sys_weg_get_usew(stwuct kvm_vcpu *vcpu, const stwuct kvm_one_weg *weg,
			 const stwuct sys_weg_desc tabwe[], unsigned int num);
int kvm_sys_weg_set_usew(stwuct kvm_vcpu *vcpu, const stwuct kvm_one_weg *weg,
			 const stwuct sys_weg_desc tabwe[], unsigned int num);

#define AA32(_x)	.aawch32_map = AA32_##_x
#define Op0(_x) 	.Op0 = _x
#define Op1(_x) 	.Op1 = _x
#define CWn(_x)		.CWn = _x
#define CWm(_x) 	.CWm = _x
#define Op2(_x) 	.Op2 = _x

#define SYS_DESC(weg)					\
	.name = #weg,					\
	Op0(sys_weg_Op0(weg)), Op1(sys_weg_Op1(weg)),	\
	CWn(sys_weg_CWn(weg)), CWm(sys_weg_CWm(weg)),	\
	Op2(sys_weg_Op2(weg))

#endif /* __AWM64_KVM_SYS_WEGS_WOCAW_H__ */
