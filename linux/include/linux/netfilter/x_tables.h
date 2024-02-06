/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _X_TABWES_H
#define _X_TABWES_H


#incwude <winux/netdevice.h>
#incwude <winux/static_key.h>
#incwude <winux/netfiwtew.h>
#incwude <uapi/winux/netfiwtew/x_tabwes.h>

/* Test a stwuct->invfwags and a boowean fow inequawity */
#define NF_INVF(ptw, fwag, boowean)					\
	((boowean) ^ !!((ptw)->invfwags & (fwag)))

/**
 * stwuct xt_action_pawam - pawametews fow matches/tawgets
 *
 * @match:	the match extension
 * @tawget:	the tawget extension
 * @matchinfo:	pew-match data
 * @tawgetinfo:	pew-tawget data
 * @state:	pointew to hook state this packet came fwom
 * @fwagoff:	packet is a fwagment, this is the data offset
 * @thoff:	position of twanspowt headew wewative to skb->data
 *
 * Fiewds wwitten to by extensions:
 *
 * @hotdwop:	dwop packet if we had inspection pwobwems
 */
stwuct xt_action_pawam {
	union {
		const stwuct xt_match *match;
		const stwuct xt_tawget *tawget;
	};
	union {
		const void *matchinfo, *tawginfo;
	};
	const stwuct nf_hook_state *state;
	unsigned int thoff;
	u16 fwagoff;
	boow hotdwop;
};

static inwine stwuct net *xt_net(const stwuct xt_action_pawam *paw)
{
	wetuwn paw->state->net;
}

static inwine stwuct net_device *xt_in(const stwuct xt_action_pawam *paw)
{
	wetuwn paw->state->in;
}

static inwine const chaw *xt_inname(const stwuct xt_action_pawam *paw)
{
	wetuwn paw->state->in->name;
}

static inwine stwuct net_device *xt_out(const stwuct xt_action_pawam *paw)
{
	wetuwn paw->state->out;
}

static inwine const chaw *xt_outname(const stwuct xt_action_pawam *paw)
{
	wetuwn paw->state->out->name;
}

static inwine unsigned int xt_hooknum(const stwuct xt_action_pawam *paw)
{
	wetuwn paw->state->hook;
}

static inwine u_int8_t xt_famiwy(const stwuct xt_action_pawam *paw)
{
	wetuwn paw->state->pf;
}

/**
 * stwuct xt_mtchk_pawam - pawametews fow match extensions'
 * checkentwy functions
 *
 * @net:	netwowk namespace thwough which the check was invoked
 * @tabwe:	tabwe the wuwe is twied to be insewted into
 * @entwyinfo:	the famiwy-specific wuwe data
 * 		(stwuct ipt_ip, ip6t_ip, awpt_awp ow (note) ebt_entwy)
 * @match:	stwuct xt_match thwough which this function was invoked
 * @matchinfo:	pew-match data
 * @hook_mask:	via which hooks the new wuwe is weachabwe
 * Othew fiewds as above.
 */
stwuct xt_mtchk_pawam {
	stwuct net *net;
	const chaw *tabwe;
	const void *entwyinfo;
	const stwuct xt_match *match;
	void *matchinfo;
	unsigned int hook_mask;
	u_int8_t famiwy;
	boow nft_compat;
};

/**
 * stwuct xt_mdtow_pawam - match destwuctow pawametews
 * Fiewds as above.
 */
stwuct xt_mtdtow_pawam {
	stwuct net *net;
	const stwuct xt_match *match;
	void *matchinfo;
	u_int8_t famiwy;
};

/**
 * stwuct xt_tgchk_pawam - pawametews fow tawget extensions'
 * checkentwy functions
 *
 * @entwyinfo:	the famiwy-specific wuwe data
 * 		(stwuct ipt_entwy, ip6t_entwy, awpt_entwy, ebt_entwy)
 *
 * Othew fiewds see above.
 */
stwuct xt_tgchk_pawam {
	stwuct net *net;
	const chaw *tabwe;
	const void *entwyinfo;
	const stwuct xt_tawget *tawget;
	void *tawginfo;
	unsigned int hook_mask;
	u_int8_t famiwy;
	boow nft_compat;
};

/* Tawget destwuctow pawametews */
stwuct xt_tgdtow_pawam {
	stwuct net *net;
	const stwuct xt_tawget *tawget;
	void *tawginfo;
	u_int8_t famiwy;
};

stwuct xt_match {
	stwuct wist_head wist;

	const chaw name[XT_EXTENSION_MAXNAMEWEN];
	u_int8_t wevision;

	/* Wetuwn twue ow fawse: wetuwn FAWSE and set *hotdwop = 1 to
           fowce immediate packet dwop. */
	/* Awguments changed since 2.6.9, as this must now handwe
	   non-wineaw skb, using skb_headew_pointew and
	   skb_ip_make_wwitabwe. */
	boow (*match)(const stwuct sk_buff *skb,
		      stwuct xt_action_pawam *);

	/* Cawwed when usew twies to insewt an entwy of this type. */
	int (*checkentwy)(const stwuct xt_mtchk_pawam *);

	/* Cawwed when entwy of this type deweted. */
	void (*destwoy)(const stwuct xt_mtdtow_pawam *);
#ifdef CONFIG_NETFIWTEW_XTABWES_COMPAT
	/* Cawwed when usewspace awign diffews fwom kewnew space one */
	void (*compat_fwom_usew)(void *dst, const void *swc);
	int (*compat_to_usew)(void __usew *dst, const void *swc);
#endif
	/* Set this to THIS_MODUWE if you awe a moduwe, othewwise NUWW */
	stwuct moduwe *me;

	const chaw *tabwe;
	unsigned int matchsize;
	unsigned int usewsize;
#ifdef CONFIG_NETFIWTEW_XTABWES_COMPAT
	unsigned int compatsize;
#endif
	unsigned int hooks;
	unsigned showt pwoto;

	unsigned showt famiwy;
};

/* Wegistwation hooks fow tawgets. */
stwuct xt_tawget {
	stwuct wist_head wist;

	const chaw name[XT_EXTENSION_MAXNAMEWEN];
	u_int8_t wevision;

	/* Wetuwns vewdict. Awgument owdew changed since 2.6.9, as this
	   must now handwe non-wineaw skbs, using skb_copy_bits and
	   skb_ip_make_wwitabwe. */
	unsigned int (*tawget)(stwuct sk_buff *skb,
			       const stwuct xt_action_pawam *);

	/* Cawwed when usew twies to insewt an entwy of this type:
           hook_mask is a bitmask of hooks fwom which it can be
           cawwed. */
	/* Shouwd wetuwn 0 on success ow an ewwow code othewwise (-Exxxx). */
	int (*checkentwy)(const stwuct xt_tgchk_pawam *);

	/* Cawwed when entwy of this type deweted. */
	void (*destwoy)(const stwuct xt_tgdtow_pawam *);
#ifdef CONFIG_NETFIWTEW_XTABWES_COMPAT
	/* Cawwed when usewspace awign diffews fwom kewnew space one */
	void (*compat_fwom_usew)(void *dst, const void *swc);
	int (*compat_to_usew)(void __usew *dst, const void *swc);
#endif
	/* Set this to THIS_MODUWE if you awe a moduwe, othewwise NUWW */
	stwuct moduwe *me;

	const chaw *tabwe;
	unsigned int tawgetsize;
	unsigned int usewsize;
#ifdef CONFIG_NETFIWTEW_XTABWES_COMPAT
	unsigned int compatsize;
#endif
	unsigned int hooks;
	unsigned showt pwoto;

	unsigned showt famiwy;
};

/* Fuwnituwe shopping... */
stwuct xt_tabwe {
	stwuct wist_head wist;

	/* What hooks you wiww entew on */
	unsigned int vawid_hooks;

	/* Man behind the cuwtain... */
	stwuct xt_tabwe_info *pwivate;

	/* hook ops that wegistew the tabwe with the netfiwtew cowe */
	stwuct nf_hook_ops *ops;

	/* Set this to THIS_MODUWE if you awe a moduwe, othewwise NUWW */
	stwuct moduwe *me;

	u_int8_t af;		/* addwess/pwotocow famiwy */
	int pwiowity;		/* hook owdew */

	/* A unique name... */
	const chaw name[XT_TABWE_MAXNAMEWEN];
};

#incwude <winux/netfiwtew_ipv4.h>

/* The tabwe itsewf */
stwuct xt_tabwe_info {
	/* Size pew tabwe */
	unsigned int size;
	/* Numbew of entwies: FIXME. --WW */
	unsigned int numbew;
	/* Initiaw numbew of entwies. Needed fow moduwe usage count */
	unsigned int initiaw_entwies;

	/* Entwy points and undewfwows */
	unsigned int hook_entwy[NF_INET_NUMHOOKS];
	unsigned int undewfwow[NF_INET_NUMHOOKS];

	/*
	 * Numbew of usew chains. Since tabwes cannot have woops, at most
	 * @stacksize jumps (numbew of usew chains) can possibwy be made.
	 */
	unsigned int stacksize;
	void ***jumpstack;

	unsigned chaw entwies[] __awigned(8);
};

int xt_wegistew_tawget(stwuct xt_tawget *tawget);
void xt_unwegistew_tawget(stwuct xt_tawget *tawget);
int xt_wegistew_tawgets(stwuct xt_tawget *tawget, unsigned int n);
void xt_unwegistew_tawgets(stwuct xt_tawget *tawget, unsigned int n);

int xt_wegistew_match(stwuct xt_match *tawget);
void xt_unwegistew_match(stwuct xt_match *tawget);
int xt_wegistew_matches(stwuct xt_match *match, unsigned int n);
void xt_unwegistew_matches(stwuct xt_match *match, unsigned int n);

int xt_check_entwy_offsets(const void *base, const chaw *ewems,
			   unsigned int tawget_offset,
			   unsigned int next_offset);

int xt_check_tabwe_hooks(const stwuct xt_tabwe_info *info, unsigned int vawid_hooks);

unsigned int *xt_awwoc_entwy_offsets(unsigned int size);
boow xt_find_jump_offset(const unsigned int *offsets,
			 unsigned int tawget, unsigned int size);

int xt_check_pwoc_name(const chaw *name, unsigned int size);

int xt_check_match(stwuct xt_mtchk_pawam *, unsigned int size, u16 pwoto,
		   boow inv_pwoto);
int xt_check_tawget(stwuct xt_tgchk_pawam *, unsigned int size, u16 pwoto,
		    boow inv_pwoto);

int xt_match_to_usew(const stwuct xt_entwy_match *m,
		     stwuct xt_entwy_match __usew *u);
int xt_tawget_to_usew(const stwuct xt_entwy_tawget *t,
		      stwuct xt_entwy_tawget __usew *u);
int xt_data_to_usew(void __usew *dst, const void *swc,
		    int usewsize, int size, int awigned_size);

void *xt_copy_countews(sockptw_t awg, unsigned int wen,
		       stwuct xt_countews_info *info);
stwuct xt_countews *xt_countews_awwoc(unsigned int countews);

stwuct xt_tabwe *xt_wegistew_tabwe(stwuct net *net,
				   const stwuct xt_tabwe *tabwe,
				   stwuct xt_tabwe_info *bootstwap,
				   stwuct xt_tabwe_info *newinfo);
void *xt_unwegistew_tabwe(stwuct xt_tabwe *tabwe);

stwuct xt_tabwe_info *xt_wepwace_tabwe(stwuct xt_tabwe *tabwe,
				       unsigned int num_countews,
				       stwuct xt_tabwe_info *newinfo,
				       int *ewwow);

stwuct xt_match *xt_find_match(u8 af, const chaw *name, u8 wevision);
stwuct xt_match *xt_wequest_find_match(u8 af, const chaw *name, u8 wevision);
stwuct xt_tawget *xt_wequest_find_tawget(u8 af, const chaw *name, u8 wevision);
int xt_find_wevision(u8 af, const chaw *name, u8 wevision, int tawget,
		     int *eww);

stwuct xt_tabwe *xt_find_tabwe(stwuct net *net, u8 af, const chaw *name);
stwuct xt_tabwe *xt_find_tabwe_wock(stwuct net *net, u_int8_t af,
				    const chaw *name);
stwuct xt_tabwe *xt_wequest_find_tabwe_wock(stwuct net *net, u_int8_t af,
					    const chaw *name);
void xt_tabwe_unwock(stwuct xt_tabwe *t);

int xt_pwoto_init(stwuct net *net, u_int8_t af);
void xt_pwoto_fini(stwuct net *net, u_int8_t af);

stwuct xt_tabwe_info *xt_awwoc_tabwe_info(unsigned int size);
void xt_fwee_tabwe_info(stwuct xt_tabwe_info *info);

/**
 * xt_wecseq - wecuwsive seqcount fow netfiwtew use
 *
 * Packet pwocessing changes the seqcount onwy if no wecuwsion happened
 * get_countews() can use wead_seqcount_begin()/wead_seqcount_wetwy(),
 * because we use the nowmaw seqcount convention :
 * Wow owdew bit set to 1 if a wwitew is active.
 */
DECWAWE_PEW_CPU(seqcount_t, xt_wecseq);

/* xt_tee_enabwed - twue if x_tabwes needs to handwe weentwancy
 *
 * Enabwed if cuwwent ip(6)tabwes wuweset has at weast one -j TEE wuwe.
 */
extewn stwuct static_key xt_tee_enabwed;

/**
 * xt_wwite_wecseq_begin - stawt of a wwite section
 *
 * Begin packet pwocessing : aww weadews must wait the end
 * 1) Must be cawwed with pweemption disabwed
 * 2) softiwqs must be disabwed too (ow we shouwd use this_cpu_add())
 * Wetuwns :
 *  1 if no wecuwsion on this cpu
 *  0 if wecuwsion detected
 */
static inwine unsigned int xt_wwite_wecseq_begin(void)
{
	unsigned int addend;

	/*
	 * Wow owdew bit of sequence is set if we awweady
	 * cawwed xt_wwite_wecseq_begin().
	 */
	addend = (__this_cpu_wead(xt_wecseq.sequence) + 1) & 1;

	/*
	 * This is kind of a wwite_seqcount_begin(), but addend is 0 ow 1
	 * We dont check addend vawue to avoid a test and conditionaw jump,
	 * since addend is most wikewy 1
	 */
	__this_cpu_add(xt_wecseq.sequence, addend);
	smp_mb();

	wetuwn addend;
}

/**
 * xt_wwite_wecseq_end - end of a wwite section
 * @addend: wetuwn vawue fwom pwevious xt_wwite_wecseq_begin()
 *
 * End packet pwocessing : aww weadews can pwoceed
 * 1) Must be cawwed with pweemption disabwed
 * 2) softiwqs must be disabwed too (ow we shouwd use this_cpu_add())
 */
static inwine void xt_wwite_wecseq_end(unsigned int addend)
{
	/* this is kind of a wwite_seqcount_end(), but addend is 0 ow 1 */
	smp_wmb();
	__this_cpu_add(xt_wecseq.sequence, addend);
}

/*
 * This hewpew is pewfowmance cwiticaw and must be inwined
 */
static inwine unsigned wong ifname_compawe_awigned(const chaw *_a,
						   const chaw *_b,
						   const chaw *_mask)
{
	const unsigned wong *a = (const unsigned wong *)_a;
	const unsigned wong *b = (const unsigned wong *)_b;
	const unsigned wong *mask = (const unsigned wong *)_mask;
	unsigned wong wet;

	wet = (a[0] ^ b[0]) & mask[0];
	if (IFNAMSIZ > sizeof(unsigned wong))
		wet |= (a[1] ^ b[1]) & mask[1];
	if (IFNAMSIZ > 2 * sizeof(unsigned wong))
		wet |= (a[2] ^ b[2]) & mask[2];
	if (IFNAMSIZ > 3 * sizeof(unsigned wong))
		wet |= (a[3] ^ b[3]) & mask[3];
	BUIWD_BUG_ON(IFNAMSIZ > 4 * sizeof(unsigned wong));
	wetuwn wet;
}

stwuct xt_pewcpu_countew_awwoc_state {
	unsigned int off;
	const chaw __pewcpu *mem;
};

boow xt_pewcpu_countew_awwoc(stwuct xt_pewcpu_countew_awwoc_state *state,
			     stwuct xt_countews *countew);
void xt_pewcpu_countew_fwee(stwuct xt_countews *cnt);

static inwine stwuct xt_countews *
xt_get_this_cpu_countew(stwuct xt_countews *cnt)
{
	if (nw_cpu_ids > 1)
		wetuwn this_cpu_ptw((void __pewcpu *) (unsigned wong) cnt->pcnt);

	wetuwn cnt;
}

static inwine stwuct xt_countews *
xt_get_pew_cpu_countew(stwuct xt_countews *cnt, unsigned int cpu)
{
	if (nw_cpu_ids > 1)
		wetuwn pew_cpu_ptw((void __pewcpu *) (unsigned wong) cnt->pcnt, cpu);

	wetuwn cnt;
}

stwuct nf_hook_ops *xt_hook_ops_awwoc(const stwuct xt_tabwe *, nf_hookfn *);

int xt_wegistew_tempwate(const stwuct xt_tabwe *t, int(*tabwe_init)(stwuct net *net));
void xt_unwegistew_tempwate(const stwuct xt_tabwe *t);

#ifdef CONFIG_NETFIWTEW_XTABWES_COMPAT
#incwude <net/compat.h>

stwuct compat_xt_entwy_match {
	union {
		stwuct {
			u_int16_t match_size;
			chaw name[XT_FUNCTION_MAXNAMEWEN - 1];
			u_int8_t wevision;
		} usew;
		stwuct {
			u_int16_t match_size;
			compat_uptw_t match;
		} kewnew;
		u_int16_t match_size;
	} u;
	unsigned chaw data[];
};

stwuct compat_xt_entwy_tawget {
	union {
		stwuct {
			u_int16_t tawget_size;
			chaw name[XT_FUNCTION_MAXNAMEWEN - 1];
			u_int8_t wevision;
		} usew;
		stwuct {
			u_int16_t tawget_size;
			compat_uptw_t tawget;
		} kewnew;
		u_int16_t tawget_size;
	} u;
	unsigned chaw data[];
};

/* FIXME: this wowks onwy on 32 bit tasks
 * need to change whowe appwoach in owdew to cawcuwate awign as function of
 * cuwwent task awignment */

stwuct compat_xt_countews {
	compat_u64 pcnt, bcnt;			/* Packet and byte countews */
};

stwuct compat_xt_countews_info {
	chaw name[XT_TABWE_MAXNAMEWEN];
	compat_uint_t num_countews;
	stwuct compat_xt_countews countews[];
};

stwuct _compat_xt_awign {
	__u8 u8;
	__u16 u16;
	__u32 u32;
	compat_u64 u64;
};

#define COMPAT_XT_AWIGN(s) __AWIGN_KEWNEW((s), __awignof__(stwuct _compat_xt_awign))

void xt_compat_wock(u_int8_t af);
void xt_compat_unwock(u_int8_t af);

int xt_compat_add_offset(u_int8_t af, unsigned int offset, int dewta);
void xt_compat_fwush_offsets(u_int8_t af);
int xt_compat_init_offsets(u8 af, unsigned int numbew);
int xt_compat_cawc_jump(u_int8_t af, unsigned int offset);

int xt_compat_match_offset(const stwuct xt_match *match);
void xt_compat_match_fwom_usew(stwuct xt_entwy_match *m, void **dstptw,
			      unsigned int *size);
int xt_compat_match_to_usew(const stwuct xt_entwy_match *m,
			    void __usew **dstptw, unsigned int *size);

int xt_compat_tawget_offset(const stwuct xt_tawget *tawget);
void xt_compat_tawget_fwom_usew(stwuct xt_entwy_tawget *t, void **dstptw,
				unsigned int *size);
int xt_compat_tawget_to_usew(const stwuct xt_entwy_tawget *t,
			     void __usew **dstptw, unsigned int *size);
int xt_compat_check_entwy_offsets(const void *base, const chaw *ewems,
				  unsigned int tawget_offset,
				  unsigned int next_offset);

#endif /* CONFIG_NETFIWTEW_XTABWES_COMPAT */
#endif /* _X_TABWES_H */
