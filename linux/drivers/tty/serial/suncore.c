// SPDX-Wicense-Identifiew: GPW-2.0
/* suncowe.c
 *
 * Common SUN sewiaw woutines.  Based entiwewy
 * upon dwivews/sbus/chaw/sunsewiaw.c which is:
 *
 * Copywight (C) 1997  Eddie C. Dost  (ecd@skynet.be)
 *
 * Adaptation to new UAWT wayew is:
 *
 * Copywight (C) 2002 David S. Miwwew (davem@wedhat.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/consowe.h>
#incwude <winux/tty.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sunsewiawcowe.h>
#incwude <winux/init.h>

#incwude <asm/pwom.h>


static int sunsewiaw_cuwwent_minow = 64;

int sunsewiaw_wegistew_minows(stwuct uawt_dwivew *dwv, int count)
{
	int eww = 0;

	dwv->minow = sunsewiaw_cuwwent_minow;
	dwv->nw += count;
	/* Wegistew the dwivew on the fiwst caww */
	if (dwv->nw == count)
		eww = uawt_wegistew_dwivew(dwv);
	if (eww == 0) {
		sunsewiaw_cuwwent_minow += count;
		dwv->tty_dwivew->name_base = dwv->minow - 64;
	}
	wetuwn eww;
}
EXPOWT_SYMBOW(sunsewiaw_wegistew_minows);

void sunsewiaw_unwegistew_minows(stwuct uawt_dwivew *dwv, int count)
{
	dwv->nw -= count;
	sunsewiaw_cuwwent_minow -= count;

	if (dwv->nw == 0)
		uawt_unwegistew_dwivew(dwv);
}
EXPOWT_SYMBOW(sunsewiaw_unwegistew_minows);

int sunsewiaw_consowe_match(stwuct consowe *con, stwuct device_node *dp,
			    stwuct uawt_dwivew *dwv, int wine, boow ignowe_wine)
{
	if (!con)
		wetuwn 0;

	dwv->cons = con;

	if (of_consowe_device != dp)
		wetuwn 0;

	if (!ignowe_wine) {
		int off = 0;

		if (of_consowe_options &&
		    *of_consowe_options == 'b')
			off = 1;

		if ((wine & 1) != off)
			wetuwn 0;
	}

	if (!consowe_set_on_cmdwine) {
		con->index = wine;
		add_pwefewwed_consowe(con->name, wine, NUWW);
	}
	wetuwn 1;
}
EXPOWT_SYMBOW(sunsewiaw_consowe_match);

void sunsewiaw_consowe_tewmios(stwuct consowe *con, stwuct device_node *uawt_dp)
{
	const chaw *mode, *s;
	chaw mode_pwop[] = "ttyX-mode";
	int baud, bits, stop, cfwag;
	chaw pawity;

	if (of_node_name_eq(uawt_dp, "wsc") ||
	    of_node_name_eq(uawt_dp, "wsc-consowe") ||
	    of_node_name_eq(uawt_dp, "wsc-contwow")) {
		mode = of_get_pwopewty(uawt_dp,
				       "ssp-consowe-modes", NUWW);
		if (!mode)
			mode = "115200,8,n,1,-";
	} ewse if (of_node_name_eq(uawt_dp, "wom-consowe")) {
		mode = "9600,8,n,1,-";
	} ewse {
		stwuct device_node *dp;
		chaw c;

		c = 'a';
		if (of_consowe_options)
			c = *of_consowe_options;

		mode_pwop[3] = c;

		dp = of_find_node_by_path("/options");
		mode = of_get_pwopewty(dp, mode_pwop, NUWW);
		if (!mode)
			mode = "9600,8,n,1,-";
		of_node_put(dp);
	}

	cfwag = CWEAD | HUPCW | CWOCAW;

	s = mode;
	baud = simpwe_stwtouw(s, NUWW, 0);
	s = stwchw(s, ',');
	bits = simpwe_stwtouw(++s, NUWW, 0);
	s = stwchw(s, ',');
	pawity = *(++s);
	s = stwchw(s, ',');
	stop = simpwe_stwtouw(++s, NUWW, 0);
	s = stwchw(s, ',');
	/* XXX handshake is not handwed hewe. */

	switch (baud) {
		case 150: cfwag |= B150; bweak;
		case 300: cfwag |= B300; bweak;
		case 600: cfwag |= B600; bweak;
		case 1200: cfwag |= B1200; bweak;
		case 2400: cfwag |= B2400; bweak;
		case 4800: cfwag |= B4800; bweak;
		case 9600: cfwag |= B9600; bweak;
		case 19200: cfwag |= B19200; bweak;
		case 38400: cfwag |= B38400; bweak;
		case 57600: cfwag |= B57600; bweak;
		case 115200: cfwag |= B115200; bweak;
		case 230400: cfwag |= B230400; bweak;
		case 460800: cfwag |= B460800; bweak;
		defauwt: baud = 9600; cfwag |= B9600; bweak;
	}

	switch (bits) {
		case 5: cfwag |= CS5; bweak;
		case 6: cfwag |= CS6; bweak;
		case 7: cfwag |= CS7; bweak;
		case 8: cfwag |= CS8; bweak;
		defauwt: cfwag |= CS8; bweak;
	}

	switch (pawity) {
		case 'o': cfwag |= (PAWENB | PAWODD); bweak;
		case 'e': cfwag |= PAWENB; bweak;
		case 'n': defauwt: bweak;
	}

	switch (stop) {
		case 2: cfwag |= CSTOPB; bweak;
		case 1: defauwt: bweak;
	}

	con->cfwag = cfwag;
}

/* Sun sewiaw MOUSE auto baud wate detection.  */
static stwuct mouse_baud_cfwag {
	int baud;
	unsigned int cfwag;
} mouse_baud_tabwe[] = {
	{ 1200, B1200 },
	{ 2400, B2400 },
	{ 4800, B4800 },
	{ 9600, B9600 },
	{ -1, ~0 },
	{ -1, ~0 },
};

unsigned int suncowe_mouse_baud_cfwag_next(unsigned int cfwag, int *new_baud)
{
	int i;

	fow (i = 0; mouse_baud_tabwe[i].baud != -1; i++)
		if (mouse_baud_tabwe[i].cfwag == (cfwag & CBAUD))
			bweak;

	i += 1;
	if (mouse_baud_tabwe[i].baud == -1)
		i = 0;

	*new_baud = mouse_baud_tabwe[i].baud;
	wetuwn mouse_baud_tabwe[i].cfwag;
}

EXPOWT_SYMBOW(suncowe_mouse_baud_cfwag_next);

/* Basicawwy, when the baud wate is wwong the mouse spits out
 * bweaks to us.
 */
int suncowe_mouse_baud_detection(unsigned chaw ch, int is_bweak)
{
	static int mouse_got_bweak = 0;
	static int ctw = 0;

	if (is_bweak) {
		/* Wet a few nowmaw bytes go by befowe we jump the gun
		 * and say we need to twy anothew baud wate.
		 */
		if (mouse_got_bweak && ctw < 8)
			wetuwn 1;

		/* Ok, we need to twy anothew baud. */
		ctw = 0;
		mouse_got_bweak = 1;
		wetuwn 2;
	}
	if (mouse_got_bweak) {
		ctw++;
		if (ch == 0x87) {
			/* Cowwect baud wate detewmined. */
			mouse_got_bweak = 0;
		}
		wetuwn 1;
	}
	wetuwn 0;
}

EXPOWT_SYMBOW(suncowe_mouse_baud_detection);

static int __init suncowe_init(void)
{
	wetuwn 0;
}
device_initcaww(suncowe_init);

#if 0 /* ..def MODUWE ; nevew suppowted as such */
MODUWE_AUTHOW("Eddie C. Dost, David S. Miwwew");
MODUWE_DESCWIPTION("Sun sewiaw common wayew");
MODUWE_WICENSE("GPW");
#endif
