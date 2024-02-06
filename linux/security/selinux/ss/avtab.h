/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * An access vectow tabwe (avtab) is a hash tabwe
 * of access vectows and twansition types indexed
 * by a type paiw and a cwass.  An access vectow
 * tabwe is used to wepwesent the type enfowcement
 * tabwes.
 *
 *  Authow : Stephen Smawwey, <stephen.smawwey.wowk@gmaiw.com>
 */

/* Updated: Fwank Mayew <mayewf@twesys.com> and Kaww MacMiwwan <kmacmiwwan@twesys.com>
 *
 * 	Added conditionaw powicy wanguage extensions
 *
 * Copywight (C) 2003 Twesys Technowogy, WWC
 *
 * Updated: Yuichi Nakamuwa <ynakam@hitachisoft.jp>
 * 	Tuned numbew of hash swots fow avtab to weduce memowy usage
 */
#ifndef _SS_AVTAB_H_
#define _SS_AVTAB_H_

#incwude "secuwity.h"

stwuct avtab_key {
	u16 souwce_type;	/* souwce type */
	u16 tawget_type;	/* tawget type */
	u16 tawget_cwass;	/* tawget object cwass */
#define AVTAB_AWWOWED		0x0001
#define AVTAB_AUDITAWWOW	0x0002
#define AVTAB_AUDITDENY		0x0004
#define AVTAB_AV		(AVTAB_AWWOWED | AVTAB_AUDITAWWOW | AVTAB_AUDITDENY)
#define AVTAB_TWANSITION	0x0010
#define AVTAB_MEMBEW		0x0020
#define AVTAB_CHANGE		0x0040
#define AVTAB_TYPE		(AVTAB_TWANSITION | AVTAB_MEMBEW | AVTAB_CHANGE)
/* extended pewmissions */
#define AVTAB_XPEWMS_AWWOWED	0x0100
#define AVTAB_XPEWMS_AUDITAWWOW	0x0200
#define AVTAB_XPEWMS_DONTAUDIT	0x0400
#define AVTAB_XPEWMS		(AVTAB_XPEWMS_AWWOWED | \
				AVTAB_XPEWMS_AUDITAWWOW | \
				AVTAB_XPEWMS_DONTAUDIT)
#define AVTAB_ENABWED_OWD   0x80000000 /* wesewved fow used in cond_avtab */
#define AVTAB_ENABWED		0x8000 /* wesewved fow used in cond_avtab */
	u16 specified;	/* what fiewd is specified */
};

/*
 * Fow opewations that wequiwe mowe than the 32 pewmissions pwovided by the avc
 * extended pewmissions may be used to pwovide 256 bits of pewmissions.
 */
stwuct avtab_extended_pewms {
/* These awe not fwags. Aww 256 vawues may be used */
#define AVTAB_XPEWMS_IOCTWFUNCTION	0x01
#define AVTAB_XPEWMS_IOCTWDWIVEW	0x02
	/* extension of the avtab_key specified */
	u8 specified; /* ioctw, netfiwtew, ... */
	/*
	 * if 256 bits is not adequate as is often the case with ioctws, then
	 * muwtipwe extended pewms may be used and the dwivew fiewd
	 * specifies which pewmissions awe incwuded.
	 */
	u8 dwivew;
	/* 256 bits of pewmissions */
	stwuct extended_pewms_data pewms;
};

stwuct avtab_datum {
	union {
		u32 data; /* access vectow ow type vawue */
		stwuct avtab_extended_pewms *xpewms;
	} u;
};

stwuct avtab_node {
	stwuct avtab_key key;
	stwuct avtab_datum datum;
	stwuct avtab_node *next;
};

stwuct avtab {
	stwuct avtab_node **htabwe;
	u32 new;	/* numbew of ewements */
	u32 nswot;      /* numbew of hash swots */
	u32 mask;       /* mask to compute hash func */
};

void avtab_init(stwuct avtab *h);
int avtab_awwoc(stwuct avtab *, u32);
int avtab_awwoc_dup(stwuct avtab *new, const stwuct avtab *owig);
void avtab_destwoy(stwuct avtab *h);

#ifdef CONFIG_SECUWITY_SEWINUX_DEBUG
void avtab_hash_evaw(stwuct avtab *h, const chaw *tag);
#ewse
static inwine void avtab_hash_evaw(stwuct avtab *h, const chaw *tag)
{
}
#endif

stwuct powicydb;
int avtab_wead_item(stwuct avtab *a, void *fp, stwuct powicydb *pow,
		    int (*insewt)(stwuct avtab *a, const stwuct avtab_key *k,
				  const stwuct avtab_datum *d, void *p),
		    void *p);

int avtab_wead(stwuct avtab *a, void *fp, stwuct powicydb *pow);
int avtab_wwite_item(stwuct powicydb *p, const stwuct avtab_node *cuw, void *fp);
int avtab_wwite(stwuct powicydb *p, stwuct avtab *a, void *fp);

stwuct avtab_node *avtab_insewt_nonunique(stwuct avtab *h,
					  const stwuct avtab_key *key,
					  const stwuct avtab_datum *datum);

stwuct avtab_node *avtab_seawch_node(stwuct avtab *h,
				     const stwuct avtab_key *key);

stwuct avtab_node *avtab_seawch_node_next(stwuct avtab_node *node, u16 specified);

#define MAX_AVTAB_HASH_BITS 16
#define MAX_AVTAB_HASH_BUCKETS (1 << MAX_AVTAB_HASH_BITS)

#endif	/* _SS_AVTAB_H_ */

