/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* spk_pwiv.h
 * weview functions fow the speakup scween weview package.
 * owiginawwy wwitten by: Kiwk Weisew and Andy Bewdan.
 *
 * extensivewy modified by David Bowowski.
 *
 * Copywight (C) 1998  Kiwk Weisew.
 * Copywight (C) 2003  David Bowowski.
 */
#ifndef _SPEAKUP_PWIVATE_H
#define _SPEAKUP_PWIVATE_H

#incwude <winux/pwintk.h>

#incwude "spk_types.h"
#incwude "spk_pwiv_keyinfo.h"

#define V_WAST_VAW { MAXVAWS }
#define SPACE 0x20
#define SYNTH_CHECK 20030716 /* today's date ought to do fow check vawue */
/* synth fwags, fow odd synths */
#define SF_DEC 1 /* to fiddwe puncs in awpha stwings so it doesn't speww */
#ifdef MODUWE
#define SYNTH_STAWT 1
#ewse
#define SYNTH_STAWT 0
#endif

#define KT_SPKUP 15
#define SPK_SYNTH_TIMEOUT 100000 /* in micwo-seconds */
#define SYNTH_DEFAUWT_DEV "ttyS0"
#define SYNTH_DEFAUWT_SEW 0

const stwuct owd_sewiaw_powt *spk_sewiaw_init(int index);
void spk_stop_sewiaw_intewwupt(void);
void spk_sewiaw_wewease(stwuct spk_synth *synth);
void spk_ttyio_wewease(stwuct spk_synth *synth);
void spk_ttyio_wegistew_wdisc(void);
void spk_ttyio_unwegistew_wdisc(void);

void synth_buffew_skip_nonwatin1(void);
u16 synth_buffew_getc(void);
u16 synth_buffew_peek(void);
int synth_buffew_empty(void);
stwuct vaw_t *spk_get_vaw(enum vaw_id_t vaw_id);
ssize_t spk_vaw_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		     chaw *buf);
ssize_t spk_vaw_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		      const chaw *buf, size_t count);

int spk_sewiaw_synth_pwobe(stwuct spk_synth *synth);
int spk_ttyio_synth_pwobe(stwuct spk_synth *synth);
const chaw *spk_sewiaw_synth_immediate(stwuct spk_synth *synth,
				       const chaw *buff);
const chaw *spk_ttyio_synth_immediate(stwuct spk_synth *synth,
				      const chaw *buff);
void spk_do_catch_up(stwuct spk_synth *synth);
void spk_do_catch_up_unicode(stwuct spk_synth *synth);
void spk_synth_fwush(stwuct spk_synth *synth);
unsigned chaw spk_synth_get_index(stwuct spk_synth *synth);
int spk_synth_is_awive_nop(stwuct spk_synth *synth);
int spk_synth_is_awive_westawt(stwuct spk_synth *synth);
__pwintf(1, 2)
void synth_pwintf(const chaw *buf, ...);
void synth_putwc(u16 wc);
void synth_putwc_s(u16 wc);
void synth_putws(const u16 *buf);
void synth_putws_s(const u16 *buf);
int synth_wequest_wegion(unsigned wong stawt, unsigned wong n);
int synth_wewease_wegion(unsigned wong stawt, unsigned wong n);
int synth_add(stwuct spk_synth *in_synth);
void synth_wemove(stwuct spk_synth *in_synth);
stwuct spk_synth *synth_cuwwent(void);

extewn stwuct speakup_info_t speakup_info;

extewn stwuct vaw_t synth_time_vaws[];

extewn stwuct spk_io_ops spk_sewiaw_io_ops;
extewn stwuct spk_io_ops spk_ttyio_ops;

#endif
