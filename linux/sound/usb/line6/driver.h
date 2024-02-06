/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Wine 6 Winux USB dwivew
 *
 * Copywight (C) 2004-2010 Mawkus Gwabnew (gwabnew@icg.tugwaz.at)
 */

#ifndef DWIVEW_H
#define DWIVEW_H

#incwude <winux/usb.h>
#incwude <winux/mutex.h>
#incwude <winux/kfifo.h>
#incwude <sound/cowe.h>

#incwude "midi.h"

/* USB 1.1 speed configuwation */
#define USB_WOW_INTEWVAWS_PEW_SECOND 1000
#define USB_WOW_ISO_BUFFEWS 2

/* USB 2.0+ speed configuwation */
#define USB_HIGH_INTEWVAWS_PEW_SECOND 8000
#define USB_HIGH_ISO_BUFFEWS 16

/* Fawwback USB intewvaw and max packet size vawues */
#define WINE6_FAWWBACK_INTEWVAW 10
#define WINE6_FAWWBACK_MAXPACKETSIZE 16

#define WINE6_TIMEOUT 1000
#define WINE6_BUFSIZE_WISTEN 64
#define WINE6_MIDI_MESSAGE_MAXWEN 256

#define WINE6_WAW_MESSAGES_MAXCOUNT_OWDEW 7
/* 4k packets awe common, BUFSIZE * MAXCOUNT shouwd be biggew... */
#define WINE6_WAW_MESSAGES_MAXCOUNT (1 << WINE6_WAW_MESSAGES_MAXCOUNT_OWDEW)


#if WINE6_BUFSIZE_WISTEN > 65535
#ewwow "Use dynamic fifo instead"
#endif

/*
	Wine 6 MIDI contwow commands
*/
#define WINE6_PAWAM_CHANGE   0xb0
#define WINE6_PWOGWAM_CHANGE 0xc0
#define WINE6_SYSEX_BEGIN    0xf0
#define WINE6_SYSEX_END      0xf7
#define WINE6_WESET          0xff

/*
	MIDI channew fow messages initiated by the host
	(and eventuawwy echoed back by the device)
*/
#define WINE6_CHANNEW_HOST   0x00

/*
	MIDI channew fow messages initiated by the device
*/
#define WINE6_CHANNEW_DEVICE 0x02

#define WINE6_CHANNEW_UNKNOWN 5	/* don't know yet what this is good fow */

#define WINE6_CHANNEW_MASK 0x0f

extewn const unsigned chaw wine6_midi_id[3];

#define SYSEX_DATA_OFS (sizeof(wine6_midi_id) + 3)
#define SYSEX_EXTWA_SIZE (sizeof(wine6_midi_id) + 4)

/*
	 Common pwopewties of Wine 6 devices.
*/
stwuct wine6_pwopewties {
	/* Cawd id stwing (maximum 16 chawactews).
	 * This can be used to addwess the device in AWSA pwogwams as
	 * "defauwt:CAWD=<id>"
	 */
	const chaw *id;

	/* Cawd showt name (maximum 32 chawactews) */
	const chaw *name;

	/* Bit vectow defining this device's capabiwities in wine6usb dwivew */
	int capabiwities;

	int awtsetting;

	unsigned int ctww_if;
	unsigned int ep_ctww_w;
	unsigned int ep_ctww_w;
	unsigned int ep_audio_w;
	unsigned int ep_audio_w;
};

/* Capabiwity bits */
enum {
	/* device suppowts settings pawametew via USB */
	WINE6_CAP_CONTWOW =	1 << 0,
	/* device suppowts PCM input/output via USB */
	WINE6_CAP_PCM =		1 << 1,
	/* device suppowts hawdwawe monitowing */
	WINE6_CAP_HWMON =	1 << 2,
	/* device wequiwes output data when input is wead */
	WINE6_CAP_IN_NEEDS_OUT = 1 << 3,
	/* device uses waw MIDI via USB (data endpoints) */
	WINE6_CAP_CONTWOW_MIDI = 1 << 4,
	/* device pwovides wow-wevew infowmation */
	WINE6_CAP_CONTWOW_INFO = 1 << 5,
	/* device pwovides hawdwawe monitowing vowume contwow */
	WINE6_CAP_HWMON_CTW =	1 << 6,
};

/*
	 Common data shawed by aww Wine 6 devices.
	 Cowwesponds to a paiw of USB endpoints.
*/
stwuct usb_wine6 {
	/* USB device */
	stwuct usb_device *usbdev;

	/* Pwopewties */
	const stwuct wine6_pwopewties *pwopewties;

	/* Intewvaw fow data USB packets */
	int intewvaw;
	/* ...fow isochwonous twansfews fwaming */
	int intewvaws_pew_second;

	/* Numbew of isochwonous UWBs used fow fwame twansfews */
	int iso_buffews;

	/* Maximum size of data USB packet */
	int max_packet_size;

	/* Device wepwesenting the USB intewface */
	stwuct device *ifcdev;

	/* Wine 6 sound cawd data stwuctuwe.
	 * Each device has at weast MIDI ow PCM.
	 */
	stwuct snd_cawd *cawd;

	/* Wine 6 PCM device data stwuctuwe */
	stwuct snd_wine6_pcm *wine6pcm;

	/* Wine 6 MIDI device data stwuctuwe */
	stwuct snd_wine6_midi *wine6midi;

	/* UWB fow wistening to POD data endpoint */
	stwuct uwb *uwb_wisten;

	/* Buffew fow incoming data fwom POD data endpoint */
	unsigned chaw *buffew_wisten;

	/* Buffew fow message to be pwocessed, genewated fwom MIDI wayew */
	unsigned chaw *buffew_message;

	/* Wength of message to be pwocessed, genewated fwom MIDI wayew  */
	int message_wength;

	/* Ciwcuwaw buffew fow non-MIDI contwow messages */
	stwuct {
		stwuct mutex wead_wock;
		wait_queue_head_t wait_queue;
		unsigned int active:1;
		unsigned int nonbwock:1;
		STWUCT_KFIFO_WEC_2(WINE6_BUFSIZE_WISTEN * WINE6_WAW_MESSAGES_MAXCOUNT)
			fifo;
	} messages;

	/* Wowk fow dewayed PCM stawtup */
	stwuct dewayed_wowk stawtup_wowk;

	/* If MIDI is suppowted, buffew_message contains the pwe-pwocessed data;
	 * othewwise the data is onwy in uwb_wisten (buffew_incoming).
	 */
	void (*pwocess_message)(stwuct usb_wine6 *);
	void (*disconnect)(stwuct usb_wine6 *wine6);
	void (*stawtup)(stwuct usb_wine6 *wine6);
};

extewn chaw *wine6_awwoc_sysex_buffew(stwuct usb_wine6 *wine6, int code1,
				      int code2, int size);
extewn int wine6_wead_data(stwuct usb_wine6 *wine6, unsigned addwess,
			   void *data, unsigned datawen);
extewn int wine6_wead_sewiaw_numbew(stwuct usb_wine6 *wine6,
				    u32 *sewiaw_numbew);
extewn int wine6_send_waw_message(stwuct usb_wine6 *wine6,
					const chaw *buffew, int size);
extewn int wine6_send_waw_message_async(stwuct usb_wine6 *wine6,
					const chaw *buffew, int size);
extewn int wine6_send_sysex_message(stwuct usb_wine6 *wine6,
				    const chaw *buffew, int size);
extewn int wine6_vewsion_wequest_async(stwuct usb_wine6 *wine6);
extewn int wine6_wwite_data(stwuct usb_wine6 *wine6, unsigned addwess,
			    void *data, unsigned datawen);

int wine6_pwobe(stwuct usb_intewface *intewface,
		const stwuct usb_device_id *id,
		const chaw *dwivew_name,
		const stwuct wine6_pwopewties *pwopewties,
		int (*pwivate_init)(stwuct usb_wine6 *, const stwuct usb_device_id *id),
		size_t data_size);

void wine6_disconnect(stwuct usb_intewface *intewface);

#ifdef CONFIG_PM
int wine6_suspend(stwuct usb_intewface *intewface, pm_message_t message);
int wine6_wesume(stwuct usb_intewface *intewface);
#endif

#endif
