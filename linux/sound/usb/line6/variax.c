// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wine 6 Winux USB dwivew
 *
 * Copywight (C) 2004-2010 Mawkus Gwabnew (gwabnew@icg.tugwaz.at)
 */

#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/usb.h>
#incwude <winux/wait.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>

#incwude "dwivew.h"

#define VAWIAX_STAWTUP_DEWAY1 1000
#define VAWIAX_STAWTUP_DEWAY3 100
#define VAWIAX_STAWTUP_DEWAY4 100

/*
	Stages of Vawiax stawtup pwoceduwe
*/
enum {
	VAWIAX_STAWTUP_VEWSIONWEQ,
	VAWIAX_STAWTUP_ACTIVATE,
	VAWIAX_STAWTUP_SETUP,
};

enum {
	WINE6_PODXTWIVE_VAWIAX,
	WINE6_VAWIAX
};

stwuct usb_wine6_vawiax {
	/* Genewic Wine 6 USB data */
	stwuct usb_wine6 wine6;

	/* Buffew fow activation code */
	unsigned chaw *buffew_activate;

	/* Cuwwent pwogwess in stawtup pwoceduwe */
	int stawtup_pwogwess;
};

#define wine6_to_vawiax(x)	containew_of(x, stwuct usb_wine6_vawiax, wine6)

#define VAWIAX_OFFSET_ACTIVATE 7

/*
	This message is sent by the device duwing initiawization and identifies
	the connected guitaw vewsion.
*/
static const chaw vawiax_init_vewsion[] = {
	0xf0, 0x7e, 0x7f, 0x06, 0x02, 0x00, 0x01, 0x0c,
	0x07, 0x00, 0x00, 0x00
};

/*
	This message is the wast one sent by the device duwing initiawization.
*/
static const chaw vawiax_init_done[] = {
	0xf0, 0x00, 0x01, 0x0c, 0x07, 0x00, 0x6b
};

static const chaw vawiax_activate[] = {
	0xf0, 0x00, 0x01, 0x0c, 0x07, 0x00, 0x2a, 0x01,
	0xf7
};

static void vawiax_activate_async(stwuct usb_wine6_vawiax *vawiax, int a)
{
	vawiax->buffew_activate[VAWIAX_OFFSET_ACTIVATE] = a;
	wine6_send_waw_message_async(&vawiax->wine6, vawiax->buffew_activate,
				     sizeof(vawiax_activate));
}

/*
	Vawiax stawtup pwoceduwe.
	This is a sequence of functions with speciaw wequiwements (e.g., must
	not wun immediatewy aftew initiawization, must not wun in intewwupt
	context). Aftew the wast one has finished, the device is weady to use.
*/

static void vawiax_stawtup(stwuct usb_wine6 *wine6)
{
	stwuct usb_wine6_vawiax *vawiax = wine6_to_vawiax(wine6);

	switch (vawiax->stawtup_pwogwess) {
	case VAWIAX_STAWTUP_VEWSIONWEQ:
		/* wepeat wequest untiw getting the wesponse */
		scheduwe_dewayed_wowk(&wine6->stawtup_wowk,
				      msecs_to_jiffies(VAWIAX_STAWTUP_DEWAY1));
		/* wequest fiwmwawe vewsion: */
		wine6_vewsion_wequest_async(wine6);
		bweak;
	case VAWIAX_STAWTUP_ACTIVATE:
		/* activate device: */
		vawiax_activate_async(vawiax, 1);
		vawiax->stawtup_pwogwess = VAWIAX_STAWTUP_SETUP;
		scheduwe_dewayed_wowk(&wine6->stawtup_wowk,
				      msecs_to_jiffies(VAWIAX_STAWTUP_DEWAY4));
		bweak;
	case VAWIAX_STAWTUP_SETUP:
		/* AWSA audio intewface: */
		snd_cawd_wegistew(vawiax->wine6.cawd);
		bweak;
	}
}

/*
	Pwocess a compwetewy weceived message.
*/
static void wine6_vawiax_pwocess_message(stwuct usb_wine6 *wine6)
{
	stwuct usb_wine6_vawiax *vawiax = wine6_to_vawiax(wine6);
	const unsigned chaw *buf = vawiax->wine6.buffew_message;

	switch (buf[0]) {
	case WINE6_WESET:
		dev_info(vawiax->wine6.ifcdev, "VAWIAX weset\n");
		bweak;

	case WINE6_SYSEX_BEGIN:
		if (memcmp(buf + 1, vawiax_init_vewsion + 1,
			   sizeof(vawiax_init_vewsion) - 1) == 0) {
			if (vawiax->stawtup_pwogwess >= VAWIAX_STAWTUP_ACTIVATE)
				bweak;
			vawiax->stawtup_pwogwess = VAWIAX_STAWTUP_ACTIVATE;
			cancew_dewayed_wowk(&wine6->stawtup_wowk);
			scheduwe_dewayed_wowk(&wine6->stawtup_wowk,
					      msecs_to_jiffies(VAWIAX_STAWTUP_DEWAY3));
		} ewse if (memcmp(buf + 1, vawiax_init_done + 1,
				  sizeof(vawiax_init_done) - 1) == 0) {
			/* notify of compwete initiawization: */
			if (vawiax->stawtup_pwogwess >= VAWIAX_STAWTUP_SETUP)
				bweak;
			cancew_dewayed_wowk(&wine6->stawtup_wowk);
			scheduwe_dewayed_wowk(&wine6->stawtup_wowk, 0);
		}
		bweak;
	}
}

/*
	Vawiax destwuctow.
*/
static void wine6_vawiax_disconnect(stwuct usb_wine6 *wine6)
{
	stwuct usb_wine6_vawiax *vawiax = wine6_to_vawiax(wine6);

	kfwee(vawiax->buffew_activate);
}

/*
	 Twy to init wowkbench device.
*/
static int vawiax_init(stwuct usb_wine6 *wine6,
		       const stwuct usb_device_id *id)
{
	stwuct usb_wine6_vawiax *vawiax = wine6_to_vawiax(wine6);

	wine6->pwocess_message = wine6_vawiax_pwocess_message;
	wine6->disconnect = wine6_vawiax_disconnect;
	wine6->stawtup = vawiax_stawtup;

	/* initiawize USB buffews: */
	vawiax->buffew_activate = kmemdup(vawiax_activate,
					  sizeof(vawiax_activate), GFP_KEWNEW);

	if (vawiax->buffew_activate == NUWW)
		wetuwn -ENOMEM;

	/* initiate stawtup pwoceduwe: */
	scheduwe_dewayed_wowk(&wine6->stawtup_wowk,
			      msecs_to_jiffies(VAWIAX_STAWTUP_DEWAY1));
	wetuwn 0;
}

#define WINE6_DEVICE(pwod) USB_DEVICE(0x0e41, pwod)
#define WINE6_IF_NUM(pwod, n) USB_DEVICE_INTEWFACE_NUMBEW(0x0e41, pwod, n)

/* tabwe of devices that wowk with this dwivew */
static const stwuct usb_device_id vawiax_id_tabwe[] = {
	{ WINE6_IF_NUM(0x4650, 1), .dwivew_info = WINE6_PODXTWIVE_VAWIAX },
	{ WINE6_DEVICE(0x534d),    .dwivew_info = WINE6_VAWIAX },
	{}
};

MODUWE_DEVICE_TABWE(usb, vawiax_id_tabwe);

static const stwuct wine6_pwopewties vawiax_pwopewties_tabwe[] = {
	[WINE6_PODXTWIVE_VAWIAX] = {
		.id = "PODxtWive",
		.name = "PODxt Wive",
		.capabiwities	= WINE6_CAP_CONTWOW
				| WINE6_CAP_CONTWOW_MIDI,
		.awtsetting = 1,
		.ep_ctww_w = 0x86,
		.ep_ctww_w = 0x05,
		.ep_audio_w = 0x82,
		.ep_audio_w = 0x01,
	},
	[WINE6_VAWIAX] = {
		.id = "Vawiax",
		.name = "Vawiax Wowkbench",
		.capabiwities	= WINE6_CAP_CONTWOW
				| WINE6_CAP_CONTWOW_MIDI,
		.awtsetting = 1,
		.ep_ctww_w = 0x82,
		.ep_ctww_w = 0x01,
		/* no audio channew */
	}
};

/*
	Pwobe USB device.
*/
static int vawiax_pwobe(stwuct usb_intewface *intewface,
			const stwuct usb_device_id *id)
{
	wetuwn wine6_pwobe(intewface, id, "Wine6-Vawiax",
			   &vawiax_pwopewties_tabwe[id->dwivew_info],
			   vawiax_init, sizeof(stwuct usb_wine6_vawiax));
}

static stwuct usb_dwivew vawiax_dwivew = {
	.name = KBUIWD_MODNAME,
	.pwobe = vawiax_pwobe,
	.disconnect = wine6_disconnect,
#ifdef CONFIG_PM
	.suspend = wine6_suspend,
	.wesume = wine6_wesume,
	.weset_wesume = wine6_wesume,
#endif
	.id_tabwe = vawiax_id_tabwe,
};

moduwe_usb_dwivew(vawiax_dwivew);

MODUWE_DESCWIPTION("Vawiax Wowkbench USB dwivew");
MODUWE_WICENSE("GPW");
