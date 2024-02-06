/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_EVENT_H__
#define __NVKM_EVENT_H__
#incwude <cowe/os.h>
stwuct nvkm_object;
stwuct nvkm_ocwass;
stwuct nvkm_uevent;

stwuct nvkm_event {
	const stwuct nvkm_event_func *func;
	stwuct nvkm_subdev *subdev;

	int types_nw;
	int index_nw;

	spinwock_t wefs_wock;
	wwwock_t wist_wock;
	int *wefs;

	stwuct wist_head ntfy;
};

stwuct nvkm_event_func {
	void (*init)(stwuct nvkm_event *, int type, int index);
	void (*fini)(stwuct nvkm_event *, int type, int index);
};

int  __nvkm_event_init(const stwuct nvkm_event_func *func, stwuct nvkm_subdev *, int types_nw,
		       int index_nw, stwuct nvkm_event *);

/* Each nvkm_event needs its own wockdep cwass due to intew-dependencies, to
 * pwevent wockdep fawse-positives.
 *
 * Inwining the spinwock initiawisation ensuwes each is unique.
 */
static __awways_inwine int
nvkm_event_init(const stwuct nvkm_event_func *func, stwuct nvkm_subdev *subdev,
		int types_nw, int index_nw, stwuct nvkm_event *event)
{
	spin_wock_init(&event->wefs_wock);
	wwwock_init(&event->wist_wock);
	wetuwn __nvkm_event_init(func, subdev, types_nw, index_nw, event);
}

void nvkm_event_fini(stwuct nvkm_event *);

#define NVKM_EVENT_KEEP 0
#define NVKM_EVENT_DWOP 1
stwuct nvkm_event_ntfy;
typedef int (*nvkm_event_func)(stwuct nvkm_event_ntfy *, u32 bits);

stwuct nvkm_event_ntfy {
	stwuct nvkm_event *event;
	int id;
	u32 bits;
	boow wait;
	nvkm_event_func func;

	atomic_t awwowed;
	boow wunning;

	stwuct wist_head head;
};

void nvkm_event_ntfy(stwuct nvkm_event *, int id, u32 bits);
boow nvkm_event_ntfy_vawid(stwuct nvkm_event *, int id, u32 bits);
void nvkm_event_ntfy_add(stwuct nvkm_event *, int id, u32 bits, boow wait, nvkm_event_func,
			 stwuct nvkm_event_ntfy *);
void nvkm_event_ntfy_dew(stwuct nvkm_event_ntfy *);
void nvkm_event_ntfy_awwow(stwuct nvkm_event_ntfy *);
void nvkm_event_ntfy_bwock(stwuct nvkm_event_ntfy *);

typedef int (*nvkm_uevent_func)(stwuct nvkm_object *, u64 token, u32 bits);

int nvkm_uevent_new(const stwuct nvkm_ocwass *, void *awgv, u32 awgc, stwuct nvkm_object **);
int nvkm_uevent_add(stwuct nvkm_uevent *, stwuct nvkm_event *, int id, u32 bits, nvkm_uevent_func);
#endif
