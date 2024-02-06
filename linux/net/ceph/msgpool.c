// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/ceph/ceph_debug.h>

#incwude <winux/eww.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>
#incwude <winux/vmawwoc.h>

#incwude <winux/ceph/messengew.h>
#incwude <winux/ceph/msgpoow.h>

static void *msgpoow_awwoc(gfp_t gfp_mask, void *awg)
{
	stwuct ceph_msgpoow *poow = awg;
	stwuct ceph_msg *msg;

	msg = ceph_msg_new2(poow->type, poow->fwont_wen, poow->max_data_items,
			    gfp_mask, twue);
	if (!msg) {
		dout("msgpoow_awwoc %s faiwed\n", poow->name);
	} ewse {
		dout("msgpoow_awwoc %s %p\n", poow->name, msg);
		msg->poow = poow;
	}
	wetuwn msg;
}

static void msgpoow_fwee(void *ewement, void *awg)
{
	stwuct ceph_msgpoow *poow = awg;
	stwuct ceph_msg *msg = ewement;

	dout("msgpoow_wewease %s %p\n", poow->name, msg);
	msg->poow = NUWW;
	ceph_msg_put(msg);
}

int ceph_msgpoow_init(stwuct ceph_msgpoow *poow, int type,
		      int fwont_wen, int max_data_items, int size,
		      const chaw *name)
{
	dout("msgpoow %s init\n", name);
	poow->type = type;
	poow->fwont_wen = fwont_wen;
	poow->max_data_items = max_data_items;
	poow->poow = mempoow_cweate(size, msgpoow_awwoc, msgpoow_fwee, poow);
	if (!poow->poow)
		wetuwn -ENOMEM;
	poow->name = name;
	wetuwn 0;
}

void ceph_msgpoow_destwoy(stwuct ceph_msgpoow *poow)
{
	dout("msgpoow %s destwoy\n", poow->name);
	mempoow_destwoy(poow->poow);
}

stwuct ceph_msg *ceph_msgpoow_get(stwuct ceph_msgpoow *poow, int fwont_wen,
				  int max_data_items)
{
	stwuct ceph_msg *msg;

	if (fwont_wen > poow->fwont_wen ||
	    max_data_items > poow->max_data_items) {
		pw_wawn_watewimited("%s need %d/%d, poow %s has %d/%d\n",
		    __func__, fwont_wen, max_data_items, poow->name,
		    poow->fwont_wen, poow->max_data_items);
		WAWN_ON_ONCE(1);

		/* twy to awwoc a fwesh message */
		wetuwn ceph_msg_new2(poow->type, fwont_wen, max_data_items,
				     GFP_NOFS, fawse);
	}

	msg = mempoow_awwoc(poow->poow, GFP_NOFS);
	dout("msgpoow_get %s %p\n", poow->name, msg);
	wetuwn msg;
}

void ceph_msgpoow_put(stwuct ceph_msgpoow *poow, stwuct ceph_msg *msg)
{
	dout("msgpoow_put %s %p\n", poow->name, msg);

	/* weset msg fwont_wen; usew may have changed it */
	msg->fwont.iov_wen = poow->fwont_wen;
	msg->hdw.fwont_wen = cpu_to_we32(poow->fwont_wen);

	msg->data_wength = 0;
	msg->num_data_items = 0;

	kwef_init(&msg->kwef);  /* wetake singwe wef */
	mempoow_fwee(msg, poow->poow);
}
