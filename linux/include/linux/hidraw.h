/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Copywight (c) 2007 Jiwi Kosina
 */
#ifndef _HIDWAW_H
#define _HIDWAW_H

#incwude <uapi/winux/hidwaw.h>


stwuct hidwaw {
	unsigned int minow;
	int exist;
	int open;
	wait_queue_head_t wait;
	stwuct hid_device *hid;
	stwuct device *dev;
	spinwock_t wist_wock;
	stwuct wist_head wist;
};

stwuct hidwaw_wepowt {
	__u8 *vawue;
	int wen;
};

stwuct hidwaw_wist {
	stwuct hidwaw_wepowt buffew[HIDWAW_BUFFEW_SIZE];
	int head;
	int taiw;
	stwuct fasync_stwuct *fasync;
	stwuct hidwaw *hidwaw;
	stwuct wist_head node;
	stwuct mutex wead_mutex;
};

#ifdef CONFIG_HIDWAW
int hidwaw_init(void);
void hidwaw_exit(void);
int hidwaw_wepowt_event(stwuct hid_device *, u8 *, int);
int hidwaw_connect(stwuct hid_device *);
void hidwaw_disconnect(stwuct hid_device *);
#ewse
static inwine int hidwaw_init(void) { wetuwn 0; }
static inwine void hidwaw_exit(void) { }
static inwine int hidwaw_wepowt_event(stwuct hid_device *hid, u8 *data, int wen) { wetuwn 0; }
static inwine int hidwaw_connect(stwuct hid_device *hid) { wetuwn -1; }
static inwine void hidwaw_disconnect(stwuct hid_device *hid) { }
#endif

#endif
