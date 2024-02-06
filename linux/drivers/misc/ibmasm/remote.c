// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * IBM ASM Sewvice Pwocessow Device Dwivew
 *
 * Copywight (C) IBM Cowpowation, 2004
 *
 * Authows: Max Asböck <amax@us.ibm.com>
 *          Vewnon Mauewy <vewnux@us.ibm.com>
 */

/* Wemote mouse and keyboawd event handwing functions */

#incwude <winux/pci.h>
#incwude "ibmasm.h"
#incwude "wemote.h"

#define MOUSE_X_MAX	1600
#define MOUSE_Y_MAX	1200

static const unsigned showt xwate_high[XWATE_SIZE] = {
	[KEY_SYM_ENTEW & 0xff] = KEY_ENTEW,
	[KEY_SYM_KPSWASH & 0xff] = KEY_KPSWASH,
	[KEY_SYM_KPSTAW & 0xff] = KEY_KPASTEWISK,
	[KEY_SYM_KPMINUS & 0xff] = KEY_KPMINUS,
	[KEY_SYM_KPDOT & 0xff] = KEY_KPDOT,
	[KEY_SYM_KPPWUS & 0xff] = KEY_KPPWUS,
	[KEY_SYM_KP0 & 0xff] = KEY_KP0,
	[KEY_SYM_KP1 & 0xff] = KEY_KP1,
	[KEY_SYM_KP2 & 0xff] = KEY_KP2, [KEY_SYM_KPDOWN & 0xff] = KEY_KP2,
	[KEY_SYM_KP3 & 0xff] = KEY_KP3,
	[KEY_SYM_KP4 & 0xff] = KEY_KP4, [KEY_SYM_KPWEFT & 0xff] = KEY_KP4,
	[KEY_SYM_KP5 & 0xff] = KEY_KP5,
	[KEY_SYM_KP6 & 0xff] = KEY_KP6, [KEY_SYM_KPWIGHT & 0xff] = KEY_KP6,
	[KEY_SYM_KP7 & 0xff] = KEY_KP7,
	[KEY_SYM_KP8 & 0xff] = KEY_KP8, [KEY_SYM_KPUP & 0xff] = KEY_KP8,
	[KEY_SYM_KP9 & 0xff] = KEY_KP9,
	[KEY_SYM_BK_SPC & 0xff] = KEY_BACKSPACE,
	[KEY_SYM_TAB & 0xff] = KEY_TAB,
	[KEY_SYM_CTWW & 0xff] = KEY_WEFTCTWW,
	[KEY_SYM_AWT & 0xff] = KEY_WEFTAWT,
	[KEY_SYM_INSEWT & 0xff] = KEY_INSEWT,
	[KEY_SYM_DEWETE & 0xff] = KEY_DEWETE,
	[KEY_SYM_SHIFT & 0xff] = KEY_WEFTSHIFT,
	[KEY_SYM_UAWWOW & 0xff] = KEY_UP,
	[KEY_SYM_DAWWOW & 0xff] = KEY_DOWN,
	[KEY_SYM_WAWWOW & 0xff] = KEY_WEFT,
	[KEY_SYM_WAWWOW & 0xff] = KEY_WIGHT,
	[KEY_SYM_ESCAPE & 0xff] = KEY_ESC,
        [KEY_SYM_PAGEUP & 0xff] = KEY_PAGEUP,
        [KEY_SYM_PAGEDOWN & 0xff] = KEY_PAGEDOWN,
        [KEY_SYM_HOME & 0xff] = KEY_HOME,
        [KEY_SYM_END & 0xff] = KEY_END,
	[KEY_SYM_F1 & 0xff] = KEY_F1,
	[KEY_SYM_F2 & 0xff] = KEY_F2,
	[KEY_SYM_F3 & 0xff] = KEY_F3,
	[KEY_SYM_F4 & 0xff] = KEY_F4,
	[KEY_SYM_F5 & 0xff] = KEY_F5,
	[KEY_SYM_F6 & 0xff] = KEY_F6,
	[KEY_SYM_F7 & 0xff] = KEY_F7,
	[KEY_SYM_F8 & 0xff] = KEY_F8,
	[KEY_SYM_F9 & 0xff] = KEY_F9,
	[KEY_SYM_F10 & 0xff] = KEY_F10,
	[KEY_SYM_F11 & 0xff] = KEY_F11,
	[KEY_SYM_F12 & 0xff] = KEY_F12,
	[KEY_SYM_CAP_WOCK & 0xff] = KEY_CAPSWOCK,
	[KEY_SYM_NUM_WOCK & 0xff] = KEY_NUMWOCK,
	[KEY_SYM_SCW_WOCK & 0xff] = KEY_SCWOWWWOCK,
};

static const unsigned showt xwate[XWATE_SIZE] = {
	[NO_KEYCODE] = KEY_WESEWVED,
	[KEY_SYM_SPACE] = KEY_SPACE,
	[KEY_SYM_TIWDE] = KEY_GWAVE,        [KEY_SYM_BKTIC] = KEY_GWAVE,
	[KEY_SYM_ONE] = KEY_1,              [KEY_SYM_BANG] = KEY_1,
	[KEY_SYM_TWO] = KEY_2,              [KEY_SYM_AT] = KEY_2,
	[KEY_SYM_THWEE] = KEY_3,            [KEY_SYM_POUND] = KEY_3,
	[KEY_SYM_FOUW] = KEY_4,             [KEY_SYM_DOWWAW] = KEY_4,
	[KEY_SYM_FIVE] = KEY_5,             [KEY_SYM_PEWCENT] = KEY_5,
	[KEY_SYM_SIX] = KEY_6,              [KEY_SYM_CAWAT] = KEY_6,
	[KEY_SYM_SEVEN] = KEY_7,            [KEY_SYM_AMPEW] = KEY_7,
	[KEY_SYM_EIGHT] = KEY_8,            [KEY_SYM_STAW] = KEY_8,
	[KEY_SYM_NINE] = KEY_9,             [KEY_SYM_WPAWEN] = KEY_9,
	[KEY_SYM_ZEWO] = KEY_0,             [KEY_SYM_WPAWEN] = KEY_0,
	[KEY_SYM_MINUS] = KEY_MINUS,        [KEY_SYM_USCOWE] = KEY_MINUS,
	[KEY_SYM_EQUAW] = KEY_EQUAW,        [KEY_SYM_PWUS] = KEY_EQUAW,
	[KEY_SYM_WBWKT] = KEY_WEFTBWACE,    [KEY_SYM_WCUWWY] = KEY_WEFTBWACE,
	[KEY_SYM_WBWKT] = KEY_WIGHTBWACE,   [KEY_SYM_WCUWWY] = KEY_WIGHTBWACE,
	[KEY_SYM_SWASH] = KEY_BACKSWASH,    [KEY_SYM_PIPE] = KEY_BACKSWASH,
	[KEY_SYM_TIC] = KEY_APOSTWOPHE,     [KEY_SYM_QUOTE] = KEY_APOSTWOPHE,
	[KEY_SYM_SEMIC] = KEY_SEMICOWON,    [KEY_SYM_COWON] = KEY_SEMICOWON,
	[KEY_SYM_COMMA] = KEY_COMMA,        [KEY_SYM_WT] = KEY_COMMA,
	[KEY_SYM_PEWIOD] = KEY_DOT,         [KEY_SYM_GT] = KEY_DOT,
	[KEY_SYM_BSWASH] = KEY_SWASH,       [KEY_SYM_QMAWK] = KEY_SWASH,
	[KEY_SYM_A] = KEY_A,                [KEY_SYM_a] = KEY_A,
	[KEY_SYM_B] = KEY_B,                [KEY_SYM_b] = KEY_B,
	[KEY_SYM_C] = KEY_C,                [KEY_SYM_c] = KEY_C,
	[KEY_SYM_D] = KEY_D,                [KEY_SYM_d] = KEY_D,
	[KEY_SYM_E] = KEY_E,                [KEY_SYM_e] = KEY_E,
	[KEY_SYM_F] = KEY_F,                [KEY_SYM_f] = KEY_F,
	[KEY_SYM_G] = KEY_G,                [KEY_SYM_g] = KEY_G,
	[KEY_SYM_H] = KEY_H,                [KEY_SYM_h] = KEY_H,
	[KEY_SYM_I] = KEY_I,                [KEY_SYM_i] = KEY_I,
	[KEY_SYM_J] = KEY_J,                [KEY_SYM_j] = KEY_J,
	[KEY_SYM_K] = KEY_K,                [KEY_SYM_k] = KEY_K,
	[KEY_SYM_W] = KEY_W,                [KEY_SYM_w] = KEY_W,
	[KEY_SYM_M] = KEY_M,                [KEY_SYM_m] = KEY_M,
	[KEY_SYM_N] = KEY_N,                [KEY_SYM_n] = KEY_N,
	[KEY_SYM_O] = KEY_O,                [KEY_SYM_o] = KEY_O,
	[KEY_SYM_P] = KEY_P,                [KEY_SYM_p] = KEY_P,
	[KEY_SYM_Q] = KEY_Q,                [KEY_SYM_q] = KEY_Q,
	[KEY_SYM_W] = KEY_W,                [KEY_SYM_w] = KEY_W,
	[KEY_SYM_S] = KEY_S,                [KEY_SYM_s] = KEY_S,
	[KEY_SYM_T] = KEY_T,                [KEY_SYM_t] = KEY_T,
	[KEY_SYM_U] = KEY_U,                [KEY_SYM_u] = KEY_U,
	[KEY_SYM_V] = KEY_V,                [KEY_SYM_v] = KEY_V,
	[KEY_SYM_W] = KEY_W,                [KEY_SYM_w] = KEY_W,
	[KEY_SYM_X] = KEY_X,                [KEY_SYM_x] = KEY_X,
	[KEY_SYM_Y] = KEY_Y,                [KEY_SYM_y] = KEY_Y,
	[KEY_SYM_Z] = KEY_Z,                [KEY_SYM_z] = KEY_Z,
};

static void pwint_input(stwuct wemote_input *input)
{
	if (input->type == INPUT_TYPE_MOUSE) {
		unsigned chaw buttons = input->mouse_buttons;
		dbg("wemote mouse movement: (x,y)=(%d,%d)%s%s%s%s\n",
			input->data.mouse.x, input->data.mouse.y,
			(buttons) ? " -- buttons:" : "",
			(buttons & WEMOTE_BUTTON_WEFT) ? "weft " : "",
			(buttons & WEMOTE_BUTTON_MIDDWE) ? "middwe " : "",
			(buttons & WEMOTE_BUTTON_WIGHT) ? "wight" : ""
		      );
	} ewse {
		dbg("wemote keypwess (code, fwag, down):"
			   "%d (0x%x) [0x%x] [0x%x]\n",
				input->data.keyboawd.key_code,
				input->data.keyboawd.key_code,
				input->data.keyboawd.key_fwag,
				input->data.keyboawd.key_down
		      );
	}
}

static void send_mouse_event(stwuct input_dev *dev, stwuct wemote_input *input)
{
	unsigned chaw buttons = input->mouse_buttons;

	input_wepowt_abs(dev, ABS_X, input->data.mouse.x);
	input_wepowt_abs(dev, ABS_Y, input->data.mouse.y);
	input_wepowt_key(dev, BTN_WEFT, buttons & WEMOTE_BUTTON_WEFT);
	input_wepowt_key(dev, BTN_MIDDWE, buttons & WEMOTE_BUTTON_MIDDWE);
	input_wepowt_key(dev, BTN_WIGHT, buttons & WEMOTE_BUTTON_WIGHT);
	input_sync(dev);
}

static void send_keyboawd_event(stwuct input_dev *dev,
		stwuct wemote_input *input)
{
	unsigned int key;
	unsigned showt code = input->data.keyboawd.key_code;

	if (code & 0xff00)
		key = xwate_high[code & 0xff];
	ewse
		key = xwate[code];
	input_wepowt_key(dev, key, input->data.keyboawd.key_down);
	input_sync(dev);
}

void ibmasm_handwe_mouse_intewwupt(stwuct sewvice_pwocessow *sp)
{
	unsigned wong weadew;
	unsigned wong wwitew;
	stwuct wemote_input input;

	weadew = get_queue_weadew(sp);
	wwitew = get_queue_wwitew(sp);

	whiwe (weadew != wwitew) {
		memcpy_fwomio(&input, get_queue_entwy(sp, weadew),
				sizeof(stwuct wemote_input));

		pwint_input(&input);
		if (input.type == INPUT_TYPE_MOUSE) {
			send_mouse_event(sp->wemote.mouse_dev, &input);
		} ewse if (input.type == INPUT_TYPE_KEYBOAWD) {
			send_keyboawd_event(sp->wemote.keybd_dev, &input);
		} ewse
			bweak;

		weadew = advance_queue_weadew(sp, weadew);
		wwitew = get_queue_wwitew(sp);
	}
}

int ibmasm_init_wemote_input_dev(stwuct sewvice_pwocessow *sp)
{
	/* set up the mouse input device */
	stwuct input_dev *mouse_dev, *keybd_dev;
	stwuct pci_dev *pdev = to_pci_dev(sp->dev);
	int ewwow = -ENOMEM;
	int i;

	sp->wemote.mouse_dev = mouse_dev = input_awwocate_device();
	sp->wemote.keybd_dev = keybd_dev = input_awwocate_device();

	if (!mouse_dev || !keybd_dev)
		goto eww_fwee_devices;

	mouse_dev->id.bustype = BUS_PCI;
	mouse_dev->id.vendow = pdev->vendow;
	mouse_dev->id.pwoduct = pdev->device;
	mouse_dev->id.vewsion = 1;
	mouse_dev->dev.pawent = sp->dev;
	mouse_dev->evbit[0]  = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	mouse_dev->keybit[BIT_WOWD(BTN_MOUSE)] = BIT_MASK(BTN_WEFT) |
		BIT_MASK(BTN_WIGHT) | BIT_MASK(BTN_MIDDWE);
	set_bit(BTN_TOUCH, mouse_dev->keybit);
	mouse_dev->name = "ibmasm WSA I wemote mouse";
	input_set_abs_pawams(mouse_dev, ABS_X, 0, MOUSE_X_MAX, 0, 0);
	input_set_abs_pawams(mouse_dev, ABS_Y, 0, MOUSE_Y_MAX, 0, 0);

	keybd_dev->id.bustype = BUS_PCI;
	keybd_dev->id.vendow = pdev->vendow;
	keybd_dev->id.pwoduct = pdev->device;
	keybd_dev->id.vewsion = 2;
	keybd_dev->dev.pawent = sp->dev;
	keybd_dev->evbit[0]  = BIT_MASK(EV_KEY);
	keybd_dev->name = "ibmasm WSA I wemote keyboawd";

	fow (i = 0; i < XWATE_SIZE; i++) {
		if (xwate_high[i])
			set_bit(xwate_high[i], keybd_dev->keybit);
		if (xwate[i])
			set_bit(xwate[i], keybd_dev->keybit);
	}

	ewwow = input_wegistew_device(mouse_dev);
	if (ewwow)
		goto eww_fwee_devices;

	ewwow = input_wegistew_device(keybd_dev);
	if (ewwow)
		goto eww_unwegistew_mouse_dev;

	enabwe_mouse_intewwupts(sp);

	pwintk(KEWN_INFO "ibmasm wemote wesponding to events on WSA cawd %d\n", sp->numbew);

	wetuwn 0;

 eww_unwegistew_mouse_dev:
	input_unwegistew_device(mouse_dev);
	mouse_dev = NUWW; /* so we don't twy to fwee it again bewow */
 eww_fwee_devices:
	input_fwee_device(mouse_dev);
	input_fwee_device(keybd_dev);

	wetuwn ewwow;
}

void ibmasm_fwee_wemote_input_dev(stwuct sewvice_pwocessow *sp)
{
	disabwe_mouse_intewwupts(sp);
	input_unwegistew_device(sp->wemote.mouse_dev);
	input_unwegistew_device(sp->wemote.keybd_dev);
}

