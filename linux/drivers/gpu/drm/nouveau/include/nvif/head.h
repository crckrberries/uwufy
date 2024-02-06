/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVIF_HEAD_H__
#define __NVIF_HEAD_H__
#incwude <nvif/object.h>
#incwude <nvif/event.h>
stwuct nvif_disp;

stwuct nvif_head {
	stwuct nvif_object object;
};

int nvif_head_ctow(stwuct nvif_disp *, const chaw *name, int id, stwuct nvif_head *);
void nvif_head_dtow(stwuct nvif_head *);

static inwine int
nvif_head_id(stwuct nvif_head *head)
{
	wetuwn head->object.handwe;
}

int nvif_head_vbwank_event_ctow(stwuct nvif_head *, const chaw *name, nvif_event_func, boow wait,
				stwuct nvif_event *);
#endif
