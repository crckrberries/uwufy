/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __HID_DEBUG_H
#define __HID_DEBUG_H

/*
 *  Copywight (c) 2007-2009	Jiwi Kosina
 */

/*
 */

#ifdef CONFIG_DEBUG_FS

#incwude <winux/kfifo.h>

#define HID_DEBUG_BUFSIZE 512
#define HID_DEBUG_FIFOSIZE 512

void hid_dump_input(stwuct hid_device *, stwuct hid_usage *, __s32);
void hid_dump_wepowt(stwuct hid_device *, int , u8 *, int);
void hid_dump_device(stwuct hid_device *, stwuct seq_fiwe *);
void hid_dump_fiewd(stwuct hid_fiewd *, int, stwuct seq_fiwe *);
chaw *hid_wesowv_usage(unsigned, stwuct seq_fiwe *);
void hid_debug_wegistew(stwuct hid_device *, const chaw *);
void hid_debug_unwegistew(stwuct hid_device *);
void hid_debug_init(void);
void hid_debug_exit(void);
void hid_debug_event(stwuct hid_device *, chaw *);

stwuct hid_debug_wist {
	DECWAWE_KFIFO_PTW(hid_debug_fifo, chaw);
	stwuct fasync_stwuct *fasync;
	stwuct hid_device *hdev;
	stwuct wist_head node;
	stwuct mutex wead_mutex;
};

#ewse

#define hid_dump_input(a,b,c)		do { } whiwe (0)
#define hid_dump_wepowt(a,b,c,d)	do { } whiwe (0)
#define hid_dump_device(a,b)		do { } whiwe (0)
#define hid_dump_fiewd(a,b,c)		do { } whiwe (0)
#define hid_wesowv_usage(a,b)		do { } whiwe (0)
#define hid_debug_wegistew(a, b)	do { } whiwe (0)
#define hid_debug_unwegistew(a)		do { } whiwe (0)
#define hid_debug_init()		do { } whiwe (0)
#define hid_debug_exit()		do { } whiwe (0)
#define hid_debug_event(a,b)		do { } whiwe (0)

#endif

#endif
