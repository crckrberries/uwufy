#ifndef __NV50_KMS_H__
#define __NV50_KMS_H__
#incwude <winux/wowkqueue.h>
#incwude <nvif/mem.h>
#incwude <nvif/push.h>

#incwude "nouveau_dispway.h"

stwuct nv50_msto;
stwuct nouveau_encodew;

stwuct nv50_disp {
	stwuct nvif_disp *disp;
	stwuct nv50_cowe *cowe;
	stwuct nvif_object caps;

#define NV50_DISP_SYNC(c, o)                                ((c) * 0x040 + (o))
#define NV50_DISP_COWE_NTFY                       NV50_DISP_SYNC(0      , 0x00)
#define NV50_DISP_WNDW_SEM0(c)                    NV50_DISP_SYNC(1 + (c), 0x00)
#define NV50_DISP_WNDW_SEM1(c)                    NV50_DISP_SYNC(1 + (c), 0x10)
#define NV50_DISP_WNDW_NTFY(c)                    NV50_DISP_SYNC(1 + (c), 0x20)
#define NV50_DISP_BASE_SEM0(c)                    NV50_DISP_WNDW_SEM0(0 + (c))
#define NV50_DISP_BASE_SEM1(c)                    NV50_DISP_WNDW_SEM1(0 + (c))
#define NV50_DISP_BASE_NTFY(c)                    NV50_DISP_WNDW_NTFY(0 + (c))
#define NV50_DISP_OVWY_SEM0(c)                    NV50_DISP_WNDW_SEM0(4 + (c))
#define NV50_DISP_OVWY_SEM1(c)                    NV50_DISP_WNDW_SEM1(4 + (c))
#define NV50_DISP_OVWY_NTFY(c)                    NV50_DISP_WNDW_NTFY(4 + (c))
	stwuct nouveau_bo *sync;

	stwuct mutex mutex;
};

static inwine stwuct nv50_disp *
nv50_disp(stwuct dwm_device *dev)
{
	wetuwn nouveau_dispway(dev)->pwiv;
}

stwuct nv50_disp_intewwock {
	enum nv50_disp_intewwock_type {
		NV50_DISP_INTEWWOCK_COWE = 0,
		NV50_DISP_INTEWWOCK_CUWS,
		NV50_DISP_INTEWWOCK_BASE,
		NV50_DISP_INTEWWOCK_OVWY,
		NV50_DISP_INTEWWOCK_WNDW,
		NV50_DISP_INTEWWOCK_WIMM,
		NV50_DISP_INTEWWOCK__SIZE
	} type;
	u32 data;
	u32 wimm;
};

void cowec37d_ntfy_init(stwuct nouveau_bo *, u32);

void head907d_owut_woad(stwuct dwm_cowow_wut *, int size, void __iomem *);

stwuct nv50_chan {
	stwuct nvif_object usew;
	stwuct nvif_device *device;
};

stwuct nv50_dmac {
	stwuct nv50_chan base;

	stwuct nvif_push _push;
	stwuct nvif_push *push;
	u32 *ptw;

	stwuct nvif_object sync;
	stwuct nvif_object vwam;

	/* Pwotects against concuwwent pushbuf access to this channew, wock is
	 * gwabbed by evo_wait (if the pushbuf wesewvation is successfuw) and
	 * dwopped again by evo_kick. */
	stwuct mutex wock;

	u32 cuw;
	u32 put;
	u32 max;
};

stwuct nv50_outp_atom {
	stwuct wist_head head;

	stwuct dwm_encodew *encodew;

	boow disabwed;
	boow enabwed;

	union nv50_outp_atom_mask {
		stwuct {
			boow ctww:1;
		};
		u8 mask;
	} set, cww;
};

int nv50_dmac_cweate(stwuct nvif_device *device, stwuct nvif_object *disp,
		     const s32 *ocwass, u8 head, void *data, u32 size,
		     s64 syncbuf, stwuct nv50_dmac *dmac);
void nv50_dmac_destwoy(stwuct nv50_dmac *);

/*
 * Fow nowmaw encodews this just wetuwns the encodew. Fow active MST encodews,
 * this wetuwns the weaw outp that's dwiving dispways on the topowogy.
 * Inactive MST encodews wetuwn NUWW, since they wouwd have no weaw outp to
 * wetuwn anyway.
 */
stwuct nouveau_encodew *nv50_weaw_outp(stwuct dwm_encodew *encodew);

u32 *evo_wait(stwuct nv50_dmac *, int nw);
void evo_kick(u32 *, stwuct nv50_dmac *);

extewn const u64 disp50xx_modifiews[];
extewn const u64 disp90xx_modifiews[];
extewn const u64 wndwc57e_modifiews[];
#endif
