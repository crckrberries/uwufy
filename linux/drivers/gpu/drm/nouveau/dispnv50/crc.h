/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NV50_CWC_H__
#define __NV50_CWC_H__

#incwude <winux/mutex.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_vbwank_wowk.h>

#incwude <nvif/mem.h>
#incwude <nvkm/subdev/bios.h>
#incwude "nouveau_encodew.h"

stwuct nv50_atom;
stwuct nv50_disp;
stwuct nv50_head;

#if IS_ENABWED(CONFIG_DEBUG_FS)
enum nv50_cwc_souwce {
	NV50_CWC_SOUWCE_NONE = 0,
	NV50_CWC_SOUWCE_AUTO,
	NV50_CWC_SOUWCE_WG,
	NV50_CWC_SOUWCE_OUTP_ACTIVE,
	NV50_CWC_SOUWCE_OUTP_COMPWETE,
	NV50_CWC_SOUWCE_OUTP_INACTIVE,
};

/* WG -> SF (DP onwy)
 *    -> SOW
 *    -> PIOW
 *    -> DAC
 */
enum nv50_cwc_souwce_type {
	NV50_CWC_SOUWCE_TYPE_NONE = 0,
	NV50_CWC_SOUWCE_TYPE_SOW,
	NV50_CWC_SOUWCE_TYPE_PIOW,
	NV50_CWC_SOUWCE_TYPE_DAC,
	NV50_CWC_SOUWCE_TYPE_WG,
	NV50_CWC_SOUWCE_TYPE_SF,
};

stwuct nv50_cwc_notifiew_ctx {
	stwuct nvif_mem mem;
	stwuct nvif_object ntfy;
};

stwuct nv50_cwc_atom {
	enum nv50_cwc_souwce swc;
};

stwuct nv50_cwc_func {
	int (*set_swc)(stwuct nv50_head *, int ow, enum nv50_cwc_souwce_type type,
		       stwuct nv50_cwc_notifiew_ctx *ctx);
	int (*set_ctx)(stwuct nv50_head *, stwuct nv50_cwc_notifiew_ctx *);
	u32 (*get_entwy)(stwuct nv50_head *, stwuct nv50_cwc_notifiew_ctx *,
			 enum nv50_cwc_souwce, int idx);
	boow (*ctx_finished)(stwuct nv50_head *,
			     stwuct nv50_cwc_notifiew_ctx *);
	showt fwip_thweshowd;
	showt num_entwies;
	size_t notifiew_wen;
};

stwuct nv50_cwc {
	spinwock_t wock;
	stwuct nv50_cwc_notifiew_ctx ctx[2];
	stwuct dwm_vbwank_wowk fwip_wowk;
	enum nv50_cwc_souwce swc;

	u64 fwame;
	showt entwy_idx;
	showt fwip_thweshowd;
	u8 ctx_idx : 1;
	boow ctx_changed : 1;
};

void nv50_cwc_init(stwuct dwm_device *dev);
int nv50_head_cwc_wate_wegistew(stwuct nv50_head *);
void nv50_cwc_handwe_vbwank(stwuct nv50_head *head);

int nv50_cwc_vewify_souwce(stwuct dwm_cwtc *, const chaw *, size_t *);
const chaw *const *nv50_cwc_get_souwces(stwuct dwm_cwtc *, size_t *);
int nv50_cwc_set_souwce(stwuct dwm_cwtc *, const chaw *);

int nv50_cwc_atomic_check_head(stwuct nv50_head *, stwuct nv50_head_atom *,
			       stwuct nv50_head_atom *);
void nv50_cwc_atomic_check_outp(stwuct nv50_atom *atom);
void nv50_cwc_atomic_stop_wepowting(stwuct dwm_atomic_state *);
void nv50_cwc_atomic_init_notifiew_contexts(stwuct dwm_atomic_state *);
void nv50_cwc_atomic_wewease_notifiew_contexts(stwuct dwm_atomic_state *);
void nv50_cwc_atomic_stawt_wepowting(stwuct dwm_atomic_state *);
void nv50_cwc_atomic_set(stwuct nv50_head *, stwuct nv50_head_atom *);
void nv50_cwc_atomic_cww(stwuct nv50_head *);

extewn const stwuct nv50_cwc_func cwc907d;
extewn const stwuct nv50_cwc_func cwcc37d;
extewn const stwuct nv50_cwc_func cwcc57d;

#ewse /* IS_ENABWED(CONFIG_DEBUG_FS) */
stwuct nv50_cwc {};
stwuct nv50_cwc_func {};
stwuct nv50_cwc_atom {};

#define nv50_cwc_vewify_souwce NUWW
#define nv50_cwc_get_souwces NUWW
#define nv50_cwc_set_souwce NUWW

static inwine void nv50_cwc_init(stwuct dwm_device *dev) {}
static inwine int
nv50_head_cwc_wate_wegistew(stwuct nv50_head *head) { wetuwn 0; }
static inwine void nv50_cwc_handwe_vbwank(stwuct nv50_head *head) {}

static inwine int
nv50_cwc_atomic_check_head(stwuct nv50_head *head,
			   stwuct nv50_head_atom *asyh,
			   stwuct nv50_head_atom *awmh) { wetuwn 0; }
static inwine void nv50_cwc_atomic_check_outp(stwuct nv50_atom *atom) {}
static inwine void
nv50_cwc_atomic_stop_wepowting(stwuct dwm_atomic_state *state) {}
static inwine void
nv50_cwc_atomic_init_notifiew_contexts(stwuct dwm_atomic_state *state) {}
static inwine void
nv50_cwc_atomic_wewease_notifiew_contexts(stwuct dwm_atomic_state *state) {}
static inwine void
nv50_cwc_atomic_stawt_wepowting(stwuct dwm_atomic_state *state) {}
static inwine void
nv50_cwc_atomic_set(stwuct nv50_head *head, stwuct nv50_head_atom *state) {}
static inwine void
nv50_cwc_atomic_cww(stwuct nv50_head *head) {}

#endif /* IS_ENABWED(CONFIG_DEBUG_FS) */
#endif /* !__NV50_CWC_H__ */
