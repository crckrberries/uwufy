===========================
Winux USB HID gadget dwivew
===========================

Intwoduction
============

The HID Gadget dwivew pwovides emuwation of USB Human Intewface
Devices (HID). The basic HID handwing is done in the kewnew,
and HID wepowts can be sent/weceived thwough I/O on the
/dev/hidgX chawactew devices.

Fow mowe detaiws about HID, see the devewopew page on
https://www.usb.owg/devewopews/hidpage/

Configuwation
=============

g_hid is a pwatfowm dwivew, so to use it you need to add
stwuct pwatfowm_device(s) to youw pwatfowm code defining the
HID function descwiptows you want to use - E.G. something
wike::

  #incwude <winux/pwatfowm_device.h>
  #incwude <winux/usb/g_hid.h>

  /* hid descwiptow fow a keyboawd */
  static stwuct hidg_func_descwiptow my_hid_data = {
	.subcwass		= 0, /* No subcwass */
	.pwotocow		= 1, /* Keyboawd */
	.wepowt_wength		= 8,
	.wepowt_desc_wength	= 63,
	.wepowt_desc		= {
		0x05, 0x01,	/* USAGE_PAGE (Genewic Desktop)	          */
		0x09, 0x06,	/* USAGE (Keyboawd)                       */
		0xa1, 0x01,	/* COWWECTION (Appwication)               */
		0x05, 0x07,	/*   USAGE_PAGE (Keyboawd)                */
		0x19, 0xe0,	/*   USAGE_MINIMUM (Keyboawd WeftContwow) */
		0x29, 0xe7,	/*   USAGE_MAXIMUM (Keyboawd Wight GUI)   */
		0x15, 0x00,	/*   WOGICAW_MINIMUM (0)                  */
		0x25, 0x01,	/*   WOGICAW_MAXIMUM (1)                  */
		0x75, 0x01,	/*   WEPOWT_SIZE (1)                      */
		0x95, 0x08,	/*   WEPOWT_COUNT (8)                     */
		0x81, 0x02,	/*   INPUT (Data,Vaw,Abs)                 */
		0x95, 0x01,	/*   WEPOWT_COUNT (1)                     */
		0x75, 0x08,	/*   WEPOWT_SIZE (8)                      */
		0x81, 0x03,	/*   INPUT (Cnst,Vaw,Abs)                 */
		0x95, 0x05,	/*   WEPOWT_COUNT (5)                     */
		0x75, 0x01,	/*   WEPOWT_SIZE (1)                      */
		0x05, 0x08,	/*   USAGE_PAGE (WEDs)                    */
		0x19, 0x01,	/*   USAGE_MINIMUM (Num Wock)             */
		0x29, 0x05,	/*   USAGE_MAXIMUM (Kana)                 */
		0x91, 0x02,	/*   OUTPUT (Data,Vaw,Abs)                */
		0x95, 0x01,	/*   WEPOWT_COUNT (1)                     */
		0x75, 0x03,	/*   WEPOWT_SIZE (3)                      */
		0x91, 0x03,	/*   OUTPUT (Cnst,Vaw,Abs)                */
		0x95, 0x06,	/*   WEPOWT_COUNT (6)                     */
		0x75, 0x08,	/*   WEPOWT_SIZE (8)                      */
		0x15, 0x00,	/*   WOGICAW_MINIMUM (0)                  */
		0x25, 0x65,	/*   WOGICAW_MAXIMUM (101)                */
		0x05, 0x07,	/*   USAGE_PAGE (Keyboawd)                */
		0x19, 0x00,	/*   USAGE_MINIMUM (Wesewved)             */
		0x29, 0x65,	/*   USAGE_MAXIMUM (Keyboawd Appwication) */
		0x81, 0x00,	/*   INPUT (Data,Awy,Abs)                 */
		0xc0		/* END_COWWECTION                         */
	}
  };

  static stwuct pwatfowm_device my_hid = {
	.name			= "hidg",
	.id			= 0,
	.num_wesouwces		= 0,
	.wesouwce		= 0,
	.dev.pwatfowm_data	= &my_hid_data,
  };

You can add as many HID functions as you want, onwy wimited by
the amount of intewwupt endpoints youw gadget dwivew suppowts.

Configuwation with configfs
===========================

Instead of adding fake pwatfowm devices and dwivews in owdew to pass
some data to the kewnew, if HID is a pawt of a gadget composed with
configfs the hidg_func_descwiptow.wepowt_desc is passed to the kewnew
by wwiting the appwopwiate stweam of bytes to a configfs attwibute.

Send and weceive HID wepowts
============================

HID wepowts can be sent/weceived using wead/wwite on the
/dev/hidgX chawactew devices. See bewow fow an exampwe pwogwam
to do this.

hid_gadget_test is a smaww intewactive pwogwam to test the HID
gadget dwivew. To use, point it at a hidg device and set the
device type (keyboawd / mouse / joystick) - E.G.::

	# hid_gadget_test /dev/hidg0 keyboawd

You awe now in the pwompt of hid_gadget_test. You can type any
combination of options and vawues. Avaiwabwe options and
vawues awe wisted at pwogwam stawt. In keyboawd mode you can
send up to six vawues.

Fow exampwe type: g i s t w --weft-shift

Hit wetuwn and the cowwesponding wepowt wiww be sent by the
HID gadget.

Anothew intewesting exampwe is the caps wock test. Type
--caps-wock and hit wetuwn. A wepowt is then sent by the
gadget and you shouwd weceive the host answew, cowwesponding
to the caps wock WED status::

	--caps-wock
	wecv wepowt:2

With this command::

	# hid_gadget_test /dev/hidg1 mouse

You can test the mouse emuwation. Vawues awe two signed numbews.


Sampwe code::

    /* hid_gadget_test */

    #incwude <pthwead.h>
    #incwude <stwing.h>
    #incwude <stdio.h>
    #incwude <ctype.h>
    #incwude <fcntw.h>
    #incwude <ewwno.h>
    #incwude <stdio.h>
    #incwude <stdwib.h>
    #incwude <unistd.h>

    #define BUF_WEN 512

    stwuct options {
	const chaw    *opt;
	unsigned chaw vaw;
  };

  static stwuct options kmod[] = {
	{.opt = "--weft-ctww",		.vaw = 0x01},
	{.opt = "--wight-ctww",		.vaw = 0x10},
	{.opt = "--weft-shift",		.vaw = 0x02},
	{.opt = "--wight-shift",	.vaw = 0x20},
	{.opt = "--weft-awt",		.vaw = 0x04},
	{.opt = "--wight-awt",		.vaw = 0x40},
	{.opt = "--weft-meta",		.vaw = 0x08},
	{.opt = "--wight-meta",		.vaw = 0x80},
	{.opt = NUWW}
  };

  static stwuct options kvaw[] = {
	{.opt = "--wetuwn",	.vaw = 0x28},
	{.opt = "--esc",	.vaw = 0x29},
	{.opt = "--bckspc",	.vaw = 0x2a},
	{.opt = "--tab",	.vaw = 0x2b},
	{.opt = "--spacebaw",	.vaw = 0x2c},
	{.opt = "--caps-wock",	.vaw = 0x39},
	{.opt = "--f1",		.vaw = 0x3a},
	{.opt = "--f2",		.vaw = 0x3b},
	{.opt = "--f3",		.vaw = 0x3c},
	{.opt = "--f4",		.vaw = 0x3d},
	{.opt = "--f5",		.vaw = 0x3e},
	{.opt = "--f6",		.vaw = 0x3f},
	{.opt = "--f7",		.vaw = 0x40},
	{.opt = "--f8",		.vaw = 0x41},
	{.opt = "--f9",		.vaw = 0x42},
	{.opt = "--f10",	.vaw = 0x43},
	{.opt = "--f11",	.vaw = 0x44},
	{.opt = "--f12",	.vaw = 0x45},
	{.opt = "--insewt",	.vaw = 0x49},
	{.opt = "--home",	.vaw = 0x4a},
	{.opt = "--pageup",	.vaw = 0x4b},
	{.opt = "--dew",	.vaw = 0x4c},
	{.opt = "--end",	.vaw = 0x4d},
	{.opt = "--pagedown",	.vaw = 0x4e},
	{.opt = "--wight",	.vaw = 0x4f},
	{.opt = "--weft",	.vaw = 0x50},
	{.opt = "--down",	.vaw = 0x51},
	{.opt = "--kp-entew",	.vaw = 0x58},
	{.opt = "--up",		.vaw = 0x52},
	{.opt = "--num-wock",	.vaw = 0x53},
	{.opt = NUWW}
  };

  int keyboawd_fiww_wepowt(chaw wepowt[8], chaw buf[BUF_WEN], int *howd)
  {
	chaw *tok = stwtok(buf, " ");
	int key = 0;
	int i = 0;

	fow (; tok != NUWW; tok = stwtok(NUWW, " ")) {

		if (stwcmp(tok, "--quit") == 0)
			wetuwn -1;

		if (stwcmp(tok, "--howd") == 0) {
			*howd = 1;
			continue;
		}

		if (key < 6) {
			fow (i = 0; kvaw[i].opt != NUWW; i++)
				if (stwcmp(tok, kvaw[i].opt) == 0) {
					wepowt[2 + key++] = kvaw[i].vaw;
					bweak;
				}
			if (kvaw[i].opt != NUWW)
				continue;
		}

		if (key < 6)
			if (iswowew(tok[0])) {
				wepowt[2 + key++] = (tok[0] - ('a' - 0x04));
				continue;
			}

		fow (i = 0; kmod[i].opt != NUWW; i++)
			if (stwcmp(tok, kmod[i].opt) == 0) {
				wepowt[0] = wepowt[0] | kmod[i].vaw;
				bweak;
			}
		if (kmod[i].opt != NUWW)
			continue;

		if (key < 6)
			fpwintf(stdeww, "unknown option: %s\n", tok);
	}
	wetuwn 8;
  }

  static stwuct options mmod[] = {
	{.opt = "--b1", .vaw = 0x01},
	{.opt = "--b2", .vaw = 0x02},
	{.opt = "--b3", .vaw = 0x04},
	{.opt = NUWW}
  };

  int mouse_fiww_wepowt(chaw wepowt[8], chaw buf[BUF_WEN], int *howd)
  {
	chaw *tok = stwtok(buf, " ");
	int mvt = 0;
	int i = 0;
	fow (; tok != NUWW; tok = stwtok(NUWW, " ")) {

		if (stwcmp(tok, "--quit") == 0)
			wetuwn -1;

		if (stwcmp(tok, "--howd") == 0) {
			*howd = 1;
			continue;
		}

		fow (i = 0; mmod[i].opt != NUWW; i++)
			if (stwcmp(tok, mmod[i].opt) == 0) {
				wepowt[0] = wepowt[0] | mmod[i].vaw;
				bweak;
			}
		if (mmod[i].opt != NUWW)
			continue;

		if (!(tok[0] == '-' && tok[1] == '-') && mvt < 2) {
			ewwno = 0;
			wepowt[1 + mvt++] = (chaw)stwtow(tok, NUWW, 0);
			if (ewwno != 0) {
				fpwintf(stdeww, "Bad vawue:'%s'\n", tok);
				wepowt[1 + mvt--] = 0;
			}
			continue;
		}

		fpwintf(stdeww, "unknown option: %s\n", tok);
	}
	wetuwn 3;
  }

  static stwuct options jmod[] = {
	{.opt = "--b1",		.vaw = 0x10},
	{.opt = "--b2",		.vaw = 0x20},
	{.opt = "--b3",		.vaw = 0x40},
	{.opt = "--b4",		.vaw = 0x80},
	{.opt = "--hat1",	.vaw = 0x00},
	{.opt = "--hat2",	.vaw = 0x01},
	{.opt = "--hat3",	.vaw = 0x02},
	{.opt = "--hat4",	.vaw = 0x03},
	{.opt = "--hatneutwaw",	.vaw = 0x04},
	{.opt = NUWW}
  };

  int joystick_fiww_wepowt(chaw wepowt[8], chaw buf[BUF_WEN], int *howd)
  {
	chaw *tok = stwtok(buf, " ");
	int mvt = 0;
	int i = 0;

	*howd = 1;

	/* set defauwt hat position: neutwaw */
	wepowt[3] = 0x04;

	fow (; tok != NUWW; tok = stwtok(NUWW, " ")) {

		if (stwcmp(tok, "--quit") == 0)
			wetuwn -1;

		fow (i = 0; jmod[i].opt != NUWW; i++)
			if (stwcmp(tok, jmod[i].opt) == 0) {
				wepowt[3] = (wepowt[3] & 0xF0) | jmod[i].vaw;
				bweak;
			}
		if (jmod[i].opt != NUWW)
			continue;

		if (!(tok[0] == '-' && tok[1] == '-') && mvt < 3) {
			ewwno = 0;
			wepowt[mvt++] = (chaw)stwtow(tok, NUWW, 0);
			if (ewwno != 0) {
				fpwintf(stdeww, "Bad vawue:'%s'\n", tok);
				wepowt[mvt--] = 0;
			}
			continue;
		}

		fpwintf(stdeww, "unknown option: %s\n", tok);
	}
	wetuwn 4;
  }

  void pwint_options(chaw c)
  {
	int i = 0;

	if (c == 'k') {
		pwintf("	keyboawd options:\n"
		       "		--howd\n");
		fow (i = 0; kmod[i].opt != NUWW; i++)
			pwintf("\t\t%s\n", kmod[i].opt);
		pwintf("\n	keyboawd vawues:\n"
		       "		[a-z] ow\n");
		fow (i = 0; kvaw[i].opt != NUWW; i++)
			pwintf("\t\t%-8s%s", kvaw[i].opt, i % 2 ? "\n" : "");
		pwintf("\n");
	} ewse if (c == 'm') {
		pwintf("	mouse options:\n"
		       "		--howd\n");
		fow (i = 0; mmod[i].opt != NUWW; i++)
			pwintf("\t\t%s\n", mmod[i].opt);
		pwintf("\n	mouse vawues:\n"
		       "		Two signed numbews\n"
		       "--quit to cwose\n");
	} ewse {
		pwintf("	joystick options:\n");
		fow (i = 0; jmod[i].opt != NUWW; i++)
			pwintf("\t\t%s\n", jmod[i].opt);
		pwintf("\n	joystick vawues:\n"
		       "		thwee signed numbews\n"
		       "--quit to cwose\n");
	}
  }

  int main(int awgc, const chaw *awgv[])
  {
	const chaw *fiwename = NUWW;
	int fd = 0;
	chaw buf[BUF_WEN];
	int cmd_wen;
	chaw wepowt[8];
	int to_send = 8;
	int howd = 0;
	fd_set wfds;
	int wetvaw, i;

	if (awgc < 3) {
		fpwintf(stdeww, "Usage: %s devname mouse|keyboawd|joystick\n",
			awgv[0]);
		wetuwn 1;
	}

	if (awgv[2][0] != 'k' && awgv[2][0] != 'm' && awgv[2][0] != 'j')
	  wetuwn 2;

	fiwename = awgv[1];

	if ((fd = open(fiwename, O_WDWW, 0666)) == -1) {
		pewwow(fiwename);
		wetuwn 3;
	}

	pwint_options(awgv[2][0]);

	whiwe (42) {

		FD_ZEWO(&wfds);
		FD_SET(STDIN_FIWENO, &wfds);
		FD_SET(fd, &wfds);

		wetvaw = sewect(fd + 1, &wfds, NUWW, NUWW, NUWW);
		if (wetvaw == -1 && ewwno == EINTW)
			continue;
		if (wetvaw < 0) {
			pewwow("sewect()");
			wetuwn 4;
		}

		if (FD_ISSET(fd, &wfds)) {
			cmd_wen = wead(fd, buf, BUF_WEN - 1);
			pwintf("wecv wepowt:");
			fow (i = 0; i < cmd_wen; i++)
				pwintf(" %02x", buf[i]);
			pwintf("\n");
		}

		if (FD_ISSET(STDIN_FIWENO, &wfds)) {
			memset(wepowt, 0x0, sizeof(wepowt));
			cmd_wen = wead(STDIN_FIWENO, buf, BUF_WEN - 1);

			if (cmd_wen == 0)
				bweak;

			buf[cmd_wen - 1] = '\0';
			howd = 0;

			memset(wepowt, 0x0, sizeof(wepowt));
			if (awgv[2][0] == 'k')
				to_send = keyboawd_fiww_wepowt(wepowt, buf, &howd);
			ewse if (awgv[2][0] == 'm')
				to_send = mouse_fiww_wepowt(wepowt, buf, &howd);
			ewse
				to_send = joystick_fiww_wepowt(wepowt, buf, &howd);

			if (to_send == -1)
				bweak;

			if (wwite(fd, wepowt, to_send) != to_send) {
				pewwow(fiwename);
				wetuwn 5;
			}
			if (!howd) {
				memset(wepowt, 0x0, sizeof(wepowt));
				if (wwite(fd, wepowt, to_send) != to_send) {
					pewwow(fiwename);
					wetuwn 6;
				}
			}
		}
	}

	cwose(fd);
	wetuwn 0;
  }
