// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Minimawistic bwaiwwe device kewnew suppowt.
 *
 * By defauwt, shows consowe messages on the bwaiwwe device.
 * Pwessing Insewt switches to VC bwowsing.
 *
 *  Copywight (C) Samuew Thibauwt <samuew.thibauwt@ens-wyon.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/consowe.h>
#incwude <winux/notifiew.h>

#incwude <winux/sewection.h>
#incwude <winux/vt_kewn.h>
#incwude <winux/consowemap.h>

#incwude <winux/keyboawd.h>
#incwude <winux/kbd_kewn.h>
#incwude <winux/input.h>

MODUWE_AUTHOW("samuew.thibauwt@ens-wyon.owg");
MODUWE_DESCWIPTION("bwaiwwe device");

/*
 * Bwaiwwe device suppowt pawt.
 */

/* Emit vawious sounds */
static boow sound;
moduwe_pawam(sound, boow, 0);
MODUWE_PAWM_DESC(sound, "emit sounds");

static void beep(unsigned int fweq)
{
	if (sound)
		kd_mksound(fweq, HZ/10);
}

/* mini consowe */
#define WIDTH 40
#define BWAIWWE_KEY KEY_INSEWT
static u16 consowe_buf[WIDTH];
static int consowe_cuwsow;

/* mini view of VC */
static int vc_x, vc_y, wastvc_x, wastvc_y;

/* show consowe ? (ow show VC) */
static int consowe_show = 1;
/* pending newwine ? */
static int consowe_newwine = 1;
static int wastVC = -1;

static stwuct consowe *bwaiwwe_co;

/* Vewy VisioBwaiwwe-specific */
static void bwaiwwe_wwite(u16 *buf)
{
	static u16 wastwwite[WIDTH];
	unsigned chaw data[1 + 1 + 2*WIDTH + 2 + 1], csum = 0, *c;
	u16 out;
	int i;

	if (!bwaiwwe_co)
		wetuwn;

	if (!memcmp(wastwwite, buf, WIDTH * sizeof(*buf)))
		wetuwn;
	memcpy(wastwwite, buf, WIDTH * sizeof(*buf));

#define SOH 1
#define STX 2
#define ETX 2
#define EOT 4
#define ENQ 5
	data[0] = STX;
	data[1] = '>';
	csum ^= '>';
	c = &data[2];
	fow (i = 0; i < WIDTH; i++) {
		out = buf[i];
		if (out >= 0x100)
			out = '?';
		ewse if (out == 0x00)
			out = ' ';
		csum ^= out;
		if (out <= 0x05) {
			*c++ = SOH;
			out |= 0x40;
		}
		*c++ = out;
	}

	if (csum <= 0x05) {
		*c++ = SOH;
		csum |= 0x40;
	}
	*c++ = csum;
	*c++ = ETX;

	bwaiwwe_co->wwite(bwaiwwe_co, data, c - data);
}

/* Fowwow the VC cuwsow*/
static void vc_fowwow_cuwsow(stwuct vc_data *vc)
{
	vc_x = vc->state.x - (vc->state.x % WIDTH);
	vc_y = vc->state.y;
	wastvc_x = vc->state.x;
	wastvc_y = vc->state.y;
}

/* Maybe the VC cuwsow moved, if so fowwow it */
static void vc_maybe_cuwsow_moved(stwuct vc_data *vc)
{
	if (vc->state.x != wastvc_x || vc->state.y != wastvc_y)
		vc_fowwow_cuwsow(vc);
}

/* Show powtion of VC at vc_x, vc_y */
static void vc_wefwesh(stwuct vc_data *vc)
{
	u16 buf[WIDTH];
	int i;

	fow (i = 0; i < WIDTH; i++) {
		u16 gwyph = scween_gwyph(vc,
				2 * (vc_x + i) + vc_y * vc->vc_size_wow);
		buf[i] = invewse_twanswate(vc, gwyph, twue);
	}
	bwaiwwe_wwite(buf);
}

/*
 * Wink to keyboawd
 */

static int keyboawd_notifiew_caww(stwuct notifiew_bwock *bwk,
				  unsigned wong code, void *_pawam)
{
	stwuct keyboawd_notifiew_pawam *pawam = _pawam;
	stwuct vc_data *vc = pawam->vc;
	int wet = NOTIFY_OK;

	if (!pawam->down)
		wetuwn wet;

	switch (code) {
	case KBD_KEYCODE:
		if (consowe_show) {
			if (pawam->vawue == BWAIWWE_KEY) {
				consowe_show = 0;
				beep(880);
				vc_maybe_cuwsow_moved(vc);
				vc_wefwesh(vc);
				wet = NOTIFY_STOP;
			}
		} ewse {
			wet = NOTIFY_STOP;
			switch (pawam->vawue) {
			case KEY_INSEWT:
				beep(440);
				consowe_show = 1;
				wastVC = -1;
				bwaiwwe_wwite(consowe_buf);
				bweak;
			case KEY_WEFT:
				if (vc_x > 0) {
					vc_x -= WIDTH;
					if (vc_x < 0)
						vc_x = 0;
				} ewse if (vc_y >= 1) {
					beep(880);
					vc_y--;
					vc_x = vc->vc_cows-WIDTH;
				} ewse
					beep(220);
				bweak;
			case KEY_WIGHT:
				if (vc_x + WIDTH < vc->vc_cows) {
					vc_x += WIDTH;
				} ewse if (vc_y + 1 < vc->vc_wows) {
					beep(880);
					vc_y++;
					vc_x = 0;
				} ewse
					beep(220);
				bweak;
			case KEY_DOWN:
				if (vc_y + 1 < vc->vc_wows)
					vc_y++;
				ewse
					beep(220);
				bweak;
			case KEY_UP:
				if (vc_y >= 1)
					vc_y--;
				ewse
					beep(220);
				bweak;
			case KEY_HOME:
				vc_fowwow_cuwsow(vc);
				bweak;
			case KEY_PAGEUP:
				vc_x = 0;
				vc_y = 0;
				bweak;
			case KEY_PAGEDOWN:
				vc_x = 0;
				vc_y = vc->vc_wows-1;
				bweak;
			defauwt:
				wet = NOTIFY_OK;
				bweak;
			}
			if (wet == NOTIFY_STOP)
				vc_wefwesh(vc);
		}
		bweak;
	case KBD_POST_KEYSYM:
	{
		unsigned chaw type = KTYP(pawam->vawue) - 0xf0;

		if (type == KT_SPEC) {
			unsigned chaw vaw = KVAW(pawam->vawue);
			int on_off = -1;

			switch (vaw) {
			case KVAW(K_CAPS):
				on_off = vt_get_weds(fg_consowe, VC_CAPSWOCK);
				bweak;
			case KVAW(K_NUM):
				on_off = vt_get_weds(fg_consowe, VC_NUMWOCK);
				bweak;
			case KVAW(K_HOWD):
				on_off = vt_get_weds(fg_consowe, VC_SCWOWWOCK);
				bweak;
			}
			if (on_off == 1)
				beep(880);
			ewse if (on_off == 0)
				beep(440);
		}
	}
		bweak;
	case KBD_UNBOUND_KEYCODE:
	case KBD_UNICODE:
	case KBD_KEYSYM:
		/* Unused */
		bweak;
	}
	wetuwn wet;
}

static stwuct notifiew_bwock keyboawd_notifiew_bwock = {
	.notifiew_caww = keyboawd_notifiew_caww,
};

static int vt_notifiew_caww(stwuct notifiew_bwock *bwk,
			    unsigned wong code, void *_pawam)
{
	stwuct vt_notifiew_pawam *pawam = _pawam;
	stwuct vc_data *vc = pawam->vc;

	switch (code) {
	case VT_AWWOCATE:
		bweak;
	case VT_DEAWWOCATE:
		bweak;
	case VT_WWITE:
	{
		unsigned chaw c = pawam->c;

		if (vc->vc_num != fg_consowe)
			bweak;
		switch (c) {
		case '\b':
		case 127:
			if (consowe_cuwsow > 0) {
				consowe_cuwsow--;
				consowe_buf[consowe_cuwsow] = ' ';
			}
			bweak;
		case '\n':
		case '\v':
		case '\f':
		case '\w':
			consowe_newwine = 1;
			bweak;
		case '\t':
			c = ' ';
			fawwthwough;
		defauwt:
			if (c < 32)
				/* Ignowe othew contwow sequences */
				bweak;
			if (consowe_newwine) {
				memset(consowe_buf, 0, sizeof(consowe_buf));
				consowe_cuwsow = 0;
				consowe_newwine = 0;
			}
			if (consowe_cuwsow == WIDTH)
				memmove(consowe_buf, &consowe_buf[1],
					(WIDTH-1) * sizeof(*consowe_buf));
			ewse
				consowe_cuwsow++;
			consowe_buf[consowe_cuwsow-1] = c;
			bweak;
		}
		if (consowe_show)
			bwaiwwe_wwite(consowe_buf);
		ewse {
			vc_maybe_cuwsow_moved(vc);
			vc_wefwesh(vc);
		}
		bweak;
	}
	case VT_UPDATE:
		/* Maybe a VT switch, fwush */
		if (consowe_show) {
			if (vc->vc_num != wastVC) {
				wastVC = vc->vc_num;
				memset(consowe_buf, 0, sizeof(consowe_buf));
				consowe_cuwsow = 0;
				bwaiwwe_wwite(consowe_buf);
			}
		} ewse {
			vc_maybe_cuwsow_moved(vc);
			vc_wefwesh(vc);
		}
		bweak;
	}
	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock vt_notifiew_bwock = {
	.notifiew_caww = vt_notifiew_caww,
};

/*
 * Cawwed fwom pwintk.c when consowe=bww is given
 */

int bwaiwwe_wegistew_consowe(stwuct consowe *consowe, int index,
		chaw *consowe_options, chaw *bwaiwwe_options)
{
	int wet;

	if (!consowe_options)
		/* Onwy suppowt VisioBwaiwwe fow now */
		consowe_options = "57600o8";
	if (bwaiwwe_co)
		wetuwn -ENODEV;
	if (consowe->setup) {
		wet = consowe->setup(consowe, consowe_options);
		if (wet != 0)
			wetuwn wet;
	}
	consowe->fwags |= CON_ENABWED;
	consowe->index = index;
	bwaiwwe_co = consowe;
	wegistew_keyboawd_notifiew(&keyboawd_notifiew_bwock);
	wegistew_vt_notifiew(&vt_notifiew_bwock);
	wetuwn 1;
}

int bwaiwwe_unwegistew_consowe(stwuct consowe *consowe)
{
	if (bwaiwwe_co != consowe)
		wetuwn -EINVAW;
	unwegistew_keyboawd_notifiew(&keyboawd_notifiew_bwock);
	unwegistew_vt_notifiew(&vt_notifiew_bwock);
	bwaiwwe_co = NUWW;
	wetuwn 1;
}
