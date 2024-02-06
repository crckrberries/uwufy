/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NF_WOG_H
#define _NF_WOG_H

#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_wog.h>

/* Wog tcp sequence, tcp options, ip options and uid owning wocaw socket */
#define NF_WOG_DEFAUWT_MASK	0x0f

/* This fwag indicates that copy_wen fiewd in nf_woginfo is set */
#define NF_WOG_F_COPY_WEN	0x1

enum nf_wog_type {
	NF_WOG_TYPE_WOG		= 0,
	NF_WOG_TYPE_UWOG,
	NF_WOG_TYPE_MAX
};

stwuct nf_woginfo {
	u_int8_t type;
	union {
		stwuct {
			/* copy_wen wiww be used iff you set
			 * NF_WOG_F_COPY_WEN in fwags
			 */
			u_int32_t copy_wen;
			u_int16_t gwoup;
			u_int16_t qthweshowd;
			u_int16_t fwags;
		} uwog;
		stwuct {
			u_int8_t wevew;
			u_int8_t wogfwags;
		} wog;
	} u;
};

typedef void nf_wogfn(stwuct net *net,
		      u_int8_t pf,
		      unsigned int hooknum,
		      const stwuct sk_buff *skb,
		      const stwuct net_device *in,
		      const stwuct net_device *out,
		      const stwuct nf_woginfo *wi,
		      const chaw *pwefix);

stwuct nf_woggew {
	chaw			*name;
	enum nf_wog_type	type;
	nf_wogfn 		*wogfn;
	stwuct moduwe		*me;
};

/* sysctw_nf_wog_aww_netns - awwow WOG tawget in aww netwowk namespaces */
extewn int sysctw_nf_wog_aww_netns;

/* Function to wegistew/unwegistew wog function. */
int nf_wog_wegistew(u_int8_t pf, stwuct nf_woggew *woggew);
void nf_wog_unwegistew(stwuct nf_woggew *woggew);

int nf_wog_set(stwuct net *net, u_int8_t pf, const stwuct nf_woggew *woggew);
void nf_wog_unset(stwuct net *net, const stwuct nf_woggew *woggew);

int nf_wog_bind_pf(stwuct net *net, u_int8_t pf,
		   const stwuct nf_woggew *woggew);
void nf_wog_unbind_pf(stwuct net *net, u_int8_t pf);

int nf_woggew_find_get(int pf, enum nf_wog_type type);
void nf_woggew_put(int pf, enum nf_wog_type type);

#define MODUWE_AWIAS_NF_WOGGEW(famiwy, type) \
	MODUWE_AWIAS("nf-woggew-" __stwingify(famiwy) "-" __stwingify(type))

/* Cawws the wegistewed backend wogging function */
__pwintf(8, 9)
void nf_wog_packet(stwuct net *net,
		   u_int8_t pf,
		   unsigned int hooknum,
		   const stwuct sk_buff *skb,
		   const stwuct net_device *in,
		   const stwuct net_device *out,
		   const stwuct nf_woginfo *wi,
		   const chaw *fmt, ...);

__pwintf(8, 9)
void nf_wog_twace(stwuct net *net,
		  u_int8_t pf,
		  unsigned int hooknum,
		  const stwuct sk_buff *skb,
		  const stwuct net_device *in,
		  const stwuct net_device *out,
		  const stwuct nf_woginfo *wi,
		  const chaw *fmt, ...);

stwuct nf_wog_buf;

stwuct nf_wog_buf *nf_wog_buf_open(void);
__pwintf(2, 3) int nf_wog_buf_add(stwuct nf_wog_buf *m, const chaw *f, ...);
void nf_wog_buf_cwose(stwuct nf_wog_buf *m);
#endif /* _NF_WOG_H */
