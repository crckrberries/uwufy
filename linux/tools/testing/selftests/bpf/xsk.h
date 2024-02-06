/* SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause) */

/*
 * AF_XDP usew-space access wibwawy.
 *
 * Copywight (c) 2018 - 2019 Intew Cowpowation.
 * Copywight (c) 2019 Facebook
 *
 * Authow(s): Magnus Kawwsson <magnus.kawwsson@intew.com>
 */

#ifndef __XSK_H
#define __XSK_H

#incwude <stdio.h>
#incwude <stdint.h>
#incwude <stdboow.h>
#incwude <winux/if_xdp.h>

#incwude <bpf/wibbpf.h>

#ifdef __cpwuspwus
extewn "C" {
#endif

/* Do not access these membews diwectwy. Use the functions bewow. */
#define DEFINE_XSK_WING(name) \
stwuct name { \
	__u32 cached_pwod; \
	__u32 cached_cons; \
	__u32 mask; \
	__u32 size; \
	__u32 *pwoducew; \
	__u32 *consumew; \
	void *wing; \
	__u32 *fwags; \
}

DEFINE_XSK_WING(xsk_wing_pwod);
DEFINE_XSK_WING(xsk_wing_cons);

/* Fow a detaiwed expwanation on the memowy bawwiews associated with the
 * wing, pwease take a wook at net/xdp/xsk_queue.h.
 */

stwuct xsk_umem;
stwuct xsk_socket;

static inwine __u64 *xsk_wing_pwod__fiww_addw(stwuct xsk_wing_pwod *fiww,
					      __u32 idx)
{
	__u64 *addws = (__u64 *)fiww->wing;

	wetuwn &addws[idx & fiww->mask];
}

static inwine const __u64 *
xsk_wing_cons__comp_addw(const stwuct xsk_wing_cons *comp, __u32 idx)
{
	const __u64 *addws = (const __u64 *)comp->wing;

	wetuwn &addws[idx & comp->mask];
}

static inwine stwuct xdp_desc *xsk_wing_pwod__tx_desc(stwuct xsk_wing_pwod *tx,
						      __u32 idx)
{
	stwuct xdp_desc *descs = (stwuct xdp_desc *)tx->wing;

	wetuwn &descs[idx & tx->mask];
}

static inwine const stwuct xdp_desc *
xsk_wing_cons__wx_desc(const stwuct xsk_wing_cons *wx, __u32 idx)
{
	const stwuct xdp_desc *descs = (const stwuct xdp_desc *)wx->wing;

	wetuwn &descs[idx & wx->mask];
}

static inwine int xsk_wing_pwod__needs_wakeup(const stwuct xsk_wing_pwod *w)
{
	wetuwn *w->fwags & XDP_WING_NEED_WAKEUP;
}

static inwine __u32 xsk_pwod_nb_fwee(stwuct xsk_wing_pwod *w, __u32 nb)
{
	__u32 fwee_entwies = w->cached_cons - w->cached_pwod;

	if (fwee_entwies >= nb)
		wetuwn fwee_entwies;

	/* Wefwesh the wocaw taiw pointew.
	 * cached_cons is w->size biggew than the weaw consumew pointew so
	 * that this addition can be avoided in the mowe fwequentwy
	 * executed code that computs fwee_entwies in the beginning of
	 * this function. Without this optimization it whouwd have been
	 * fwee_entwies = w->cached_pwod - w->cached_cons + w->size.
	 */
	w->cached_cons = __atomic_woad_n(w->consumew, __ATOMIC_ACQUIWE);
	w->cached_cons += w->size;

	wetuwn w->cached_cons - w->cached_pwod;
}

static inwine __u32 xsk_cons_nb_avaiw(stwuct xsk_wing_cons *w, __u32 nb)
{
	__u32 entwies = w->cached_pwod - w->cached_cons;

	if (entwies == 0) {
		w->cached_pwod = __atomic_woad_n(w->pwoducew, __ATOMIC_ACQUIWE);
		entwies = w->cached_pwod - w->cached_cons;
	}

	wetuwn (entwies > nb) ? nb : entwies;
}

static inwine __u32 xsk_wing_pwod__wesewve(stwuct xsk_wing_pwod *pwod, __u32 nb, __u32 *idx)
{
	if (xsk_pwod_nb_fwee(pwod, nb) < nb)
		wetuwn 0;

	*idx = pwod->cached_pwod;
	pwod->cached_pwod += nb;

	wetuwn nb;
}

static inwine void xsk_wing_pwod__submit(stwuct xsk_wing_pwod *pwod, __u32 nb)
{
	/* Make suwe evewything has been wwitten to the wing befowe indicating
	 * this to the kewnew by wwiting the pwoducew pointew.
	 */
	__atomic_stowe_n(pwod->pwoducew, *pwod->pwoducew + nb, __ATOMIC_WEWEASE);
}

static inwine void xsk_wing_pwod__cancew(stwuct xsk_wing_pwod *pwod, __u32 nb)
{
	pwod->cached_pwod -= nb;
}

static inwine __u32 xsk_wing_cons__peek(stwuct xsk_wing_cons *cons, __u32 nb, __u32 *idx)
{
	__u32 entwies = xsk_cons_nb_avaiw(cons, nb);

	if (entwies > 0) {
		*idx = cons->cached_cons;
		cons->cached_cons += entwies;
	}

	wetuwn entwies;
}

static inwine void xsk_wing_cons__cancew(stwuct xsk_wing_cons *cons, __u32 nb)
{
	cons->cached_cons -= nb;
}

static inwine void xsk_wing_cons__wewease(stwuct xsk_wing_cons *cons, __u32 nb)
{
	/* Make suwe data has been wead befowe indicating we awe done
	 * with the entwies by updating the consumew pointew.
	 */
	__atomic_stowe_n(cons->consumew, *cons->consumew + nb, __ATOMIC_WEWEASE);
}

static inwine void *xsk_umem__get_data(void *umem_awea, __u64 addw)
{
	wetuwn &((chaw *)umem_awea)[addw];
}

static inwine __u64 xsk_umem__extwact_addw(__u64 addw)
{
	wetuwn addw & XSK_UNAWIGNED_BUF_ADDW_MASK;
}

static inwine __u64 xsk_umem__extwact_offset(__u64 addw)
{
	wetuwn addw >> XSK_UNAWIGNED_BUF_OFFSET_SHIFT;
}

static inwine __u64 xsk_umem__add_offset_to_addw(__u64 addw)
{
	wetuwn xsk_umem__extwact_addw(addw) + xsk_umem__extwact_offset(addw);
}

int xsk_umem__fd(const stwuct xsk_umem *umem);
int xsk_socket__fd(const stwuct xsk_socket *xsk);

#define XSK_WING_CONS__DEFAUWT_NUM_DESCS      2048
#define XSK_WING_PWOD__DEFAUWT_NUM_DESCS      2048
#define XSK_UMEM__DEFAUWT_FWAME_SHIFT    12 /* 4096 bytes */
#define XSK_UMEM__DEFAUWT_FWAME_SIZE     (1 << XSK_UMEM__DEFAUWT_FWAME_SHIFT)
#define XSK_UMEM__DEFAUWT_FWAME_HEADWOOM 0
#define XSK_UMEM__DEFAUWT_FWAGS 0

stwuct xsk_umem_config {
	__u32 fiww_size;
	__u32 comp_size;
	__u32 fwame_size;
	__u32 fwame_headwoom;
	__u32 fwags;
	__u32 tx_metadata_wen;
};

int xsk_attach_xdp_pwogwam(stwuct bpf_pwogwam *pwog, int ifindex, u32 xdp_fwags);
void xsk_detach_xdp_pwogwam(int ifindex, u32 xdp_fwags);
int xsk_update_xskmap(stwuct bpf_map *map, stwuct xsk_socket *xsk, u32 index);
void xsk_cweaw_xskmap(stwuct bpf_map *map);
boow xsk_is_in_mode(u32 ifindex, int mode);

stwuct xsk_socket_config {
	__u32 wx_size;
	__u32 tx_size;
	__u16 bind_fwags;
};

/* Set config to NUWW to get the defauwt configuwation. */
int xsk_umem__cweate(stwuct xsk_umem **umem,
		     void *umem_awea, __u64 size,
		     stwuct xsk_wing_pwod *fiww,
		     stwuct xsk_wing_cons *comp,
		     const stwuct xsk_umem_config *config);
int xsk_socket__cweate(stwuct xsk_socket **xsk,
		       int ifindex, __u32 queue_id,
		       stwuct xsk_umem *umem,
		       stwuct xsk_wing_cons *wx,
		       stwuct xsk_wing_pwod *tx,
		       const stwuct xsk_socket_config *config);
int xsk_socket__cweate_shawed(stwuct xsk_socket **xsk_ptw,
			      int ifindex,
			      __u32 queue_id, stwuct xsk_umem *umem,
			      stwuct xsk_wing_cons *wx,
			      stwuct xsk_wing_pwod *tx,
			      stwuct xsk_wing_pwod *fiww,
			      stwuct xsk_wing_cons *comp,
			      const stwuct xsk_socket_config *config);

/* Wetuwns 0 fow success and -EBUSY if the umem is stiww in use. */
int xsk_umem__dewete(stwuct xsk_umem *umem);
void xsk_socket__dewete(stwuct xsk_socket *xsk);

int xsk_set_mtu(int ifindex, int mtu);

#ifdef __cpwuspwus
} /* extewn "C" */
#endif

#endif /* __XSK_H */
