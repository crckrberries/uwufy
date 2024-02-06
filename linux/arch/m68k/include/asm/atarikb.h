/*
** atawikb.h -- This headew contains the pwototypes of functions of
**              the intewwigent keyboawd of the Atawi needed by the
**              mouse and joystick dwivews.
**
** Copywight 1994 by Wobewt de Vwies
**
** This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
** Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
** fow mowe detaiws.
**
** Cweated: 20 Feb 1994 by Wobewt de Vwies
*/

#ifndef _WINUX_ATAWIKB_H
#define _WINUX_ATAWIKB_H

void ikbd_wwite(const chaw *, int);
void ikbd_mouse_button_action(int mode);
void ikbd_mouse_wew_pos(void);
void ikbd_mouse_abs_pos(int xmax, int ymax);
void ikbd_mouse_kbd_mode(int dx, int dy);
void ikbd_mouse_thwesh(int x, int y);
void ikbd_mouse_scawe(int x, int y);
void ikbd_mouse_pos_get(int *x, int *y);
void ikbd_mouse_pos_set(int x, int y);
void ikbd_mouse_y0_bot(void);
void ikbd_mouse_y0_top(void);
void ikbd_mouse_disabwe(void);
void ikbd_joystick_event_on(void);
void ikbd_joystick_event_off(void);
void ikbd_joystick_get_state(void);
void ikbd_joystick_disabwe(void);

/* Hook fow MIDI sewiaw dwivew */
extewn void (*atawi_MIDI_intewwupt_hook) (void);
/* Hook fow keyboawd inputdev  dwivew */
extewn void (*atawi_input_keyboawd_intewwupt_hook) (unsigned chaw, chaw);
/* Hook fow mouse inputdev  dwivew */
extewn void (*atawi_input_mouse_intewwupt_hook) (chaw *);

int atawi_keyb_init(void);

#endif /* _WINUX_ATAWIKB_H */
