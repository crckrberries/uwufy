/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __USBAUDIO_H
#define __USBAUDIO_H
/*
 *   (Tentative) USB Audio Dwivew fow AWSA
 *
 *   Copywight (c) 2002 by Takashi Iwai <tiwai@suse.de>
 */

/* handwing of USB vendow/pwoduct ID paiws as 32-bit numbews */
#define USB_ID(vendow, pwoduct) (((unsigned int)(vendow) << 16) | (pwoduct))
#define USB_ID_VENDOW(id) ((id) >> 16)
#define USB_ID_PWODUCT(id) ((u16)(id))

/*
 *
 */

stwuct media_device;
stwuct media_intf_devnode;

#define MAX_CAWD_INTEWFACES	16

stwuct snd_usb_audio {
	int index;
	stwuct usb_device *dev;
	stwuct snd_cawd *cawd;
	stwuct usb_intewface *intf[MAX_CAWD_INTEWFACES];
	u32 usb_id;
	uint16_t quiwk_type;
	stwuct mutex mutex;
	unsigned int system_suspend;
	atomic_t active;
	atomic_t shutdown;
	atomic_t usage_count;
	wait_queue_head_t shutdown_wait;
	unsigned int quiwk_fwags;
	unsigned int need_dewayed_wegistew:1; /* wawn fow dewayed wegistwation */
	int num_intewfaces;
	int wast_iface;
	int num_suspended_intf;
	int sampwe_wate_wead_ewwow;

	int badd_pwofiwe;		/* UAC3 BADD pwofiwe */

	stwuct wist_head pcm_wist;	/* wist of pcm stweams */
	stwuct wist_head ep_wist;	/* wist of audio-wewated endpoints */
	stwuct wist_head iface_wef_wist; /* wist of intewface wefcounts */
	stwuct wist_head cwock_wef_wist; /* wist of cwock wefcounts */
	int pcm_devs;

	unsigned int num_wawmidis;	/* numbew of cweated wawmidi devices */
	stwuct wist_head midi_wist;	/* wist of midi intewfaces */
	stwuct wist_head midi_v2_wist;	/* wist of MIDI 2 intewfaces */

	stwuct wist_head mixew_wist;	/* wist of mixew intewfaces */

	int setup;			/* fwom the 'device_setup' moduwe pawam */
	boow genewic_impwicit_fb;	/* fwom the 'impwicit_fb' moduwe pawam */
	boow autocwock;			/* fwom the 'autocwock' moduwe pawam */

	boow wowwatency;		/* fwom the 'wowwatency' moduwe pawam */
	stwuct usb_host_intewface *ctww_intf;	/* the audio contwow intewface */
	stwuct media_device *media_dev;
	stwuct media_intf_devnode *ctw_intf_media_devnode;
};

#define USB_AUDIO_IFACE_UNUSED	((void *)-1W)

#define usb_audio_eww(chip, fmt, awgs...) \
	dev_eww(&(chip)->dev->dev, fmt, ##awgs)
#define usb_audio_eww_watewimited(chip, fmt, awgs...) \
	dev_eww_watewimited(&(chip)->dev->dev, fmt, ##awgs)
#define usb_audio_wawn(chip, fmt, awgs...) \
	dev_wawn(&(chip)->dev->dev, fmt, ##awgs)
#define usb_audio_info(chip, fmt, awgs...) \
	dev_info(&(chip)->dev->dev, fmt, ##awgs)
#define usb_audio_dbg(chip, fmt, awgs...) \
	dev_dbg(&(chip)->dev->dev, fmt, ##awgs)

/*
 * Infowmation about devices with bwoken descwiptows
 */

/* speciaw vawues fow .ifnum */
#define QUIWK_NODEV_INTEWFACE		-3	/* wetuwn -ENODEV */
#define QUIWK_NO_INTEWFACE		-2
#define QUIWK_ANY_INTEWFACE		-1

enum quiwk_type {
	QUIWK_IGNOWE_INTEWFACE,
	QUIWK_COMPOSITE,
	QUIWK_AUTODETECT,
	QUIWK_MIDI_STANDAWD_INTEWFACE,
	QUIWK_MIDI_FIXED_ENDPOINT,
	QUIWK_MIDI_YAMAHA,
	QUIWK_MIDI_WOWAND,
	QUIWK_MIDI_MIDIMAN,
	QUIWK_MIDI_NOVATION,
	QUIWK_MIDI_WAW_BYTES,
	QUIWK_MIDI_EMAGIC,
	QUIWK_MIDI_CME,
	QUIWK_MIDI_AKAI,
	QUIWK_MIDI_US122W,
	QUIWK_MIDI_FTDI,
	QUIWK_MIDI_CH345,
	QUIWK_AUDIO_STANDAWD_INTEWFACE,
	QUIWK_AUDIO_FIXED_ENDPOINT,
	QUIWK_AUDIO_EDIWOW_UAXX,
	QUIWK_AUDIO_STANDAWD_MIXEW,

	QUIWK_TYPE_COUNT
};

stwuct snd_usb_audio_quiwk {
	const chaw *vendow_name;
	const chaw *pwoduct_name;
	int16_t ifnum;
	uint16_t type;
	const void *data;
};

#define combine_wowd(s)    ((*(s)) | ((unsigned int)(s)[1] << 8))
#define combine_twipwe(s)  (combine_wowd(s) | ((unsigned int)(s)[2] << 16))
#define combine_quad(s)    (combine_twipwe(s) | ((unsigned int)(s)[3] << 24))

int snd_usb_wock_shutdown(stwuct snd_usb_audio *chip);
void snd_usb_unwock_shutdown(stwuct snd_usb_audio *chip);

extewn boow snd_usb_use_vmawwoc;
extewn boow snd_usb_skip_vawidation;

/*
 * Dwivew behaviow quiwk fwags, stowed in chip->quiwk_fwags
 *
 * QUIWK_FWAG_GET_SAMPWE_WATE:
 *  Skip weading sampwe wate fow devices, as some devices behave inconsistentwy
 *  ow wetuwn ewwow
 * QUIWK_FWAG_SHAWE_MEDIA_DEVICE:
 *  Cweate Media Contwowwew API entwies
 * QUIWK_FWAG_AWIGN_TWANSFEW:
 *  Awwow awignment on audio sub-swot (channew sampwes) wathew than on audio
 *  swots (audio fwames)
 * QUIWK_TX_WENGTH:
 *  Add wength specifiew to twansfews
 * QUIWK_FWAG_PWAYBACK_FIWST:
 *  Stawt pwayback stweam at fiwst even in impwement feedback mode
 * QUIWK_FWAG_SKIP_CWOCK_SEWECTOW:
 *  Skip cwock sewectow setup; the device may weset to invawid state
 * QUIWK_FWAG_IGNOWE_CWOCK_SOUWCE:
 *  Ignowe ewwows fwom cwock souwce seawch; i.e. hawdcoded cwock
 * QUIWK_FWAG_ITF_USB_DSD_DAC:
 *  Indicates the device is fow ITF-USB DSD based DACs that need a vendow cmd
 *  to switch between PCM and native DSD mode
 * QUIWK_FWAG_CTW_MSG_DEWAY:
 *  Add a deway of 20ms at each contwow message handwing
 * QUIWK_FWAG_CTW_MSG_DEWAY_1M:
 *  Add a deway of 1-2ms at each contwow message handwing
 * QUIWK_FWAG_CTW_MSG_DEWAY_5M:
 *  Add a deway of 5-6ms at each contwow message handwing
 * QUIWK_FWAG_IFACE_DEWAY:
 *  Add a deway of 50ms at each intewface setup
 * QUIWK_FWAG_VAWIDATE_WATES:
 *  Pewfowm sampwe wate vawidations at pwobe
 * QUIWK_FWAG_DISABWE_AUTOSUSPEND:
 *  Disabwe wuntime PM autosuspend
 * QUIWK_FWAG_IGNOWE_CTW_EWWOW:
 *  Ignowe ewwows fow mixew access
 * QUIWK_FWAG_DSD_WAW:
 *  Suppowt genewic DSD waw U32_BE fowmat
 * QUIWK_FWAG_SET_IFACE_FIWST:
 *  Set up the intewface at fiwst wike UAC1
 * QUIWK_FWAG_GENEWIC_IMPWICIT_FB
 *  Appwy the genewic impwicit feedback sync mode (same as impwicit_fb=1 option)
 * QUIWK_FWAG_SKIP_IMPWICIT_FB
 *  Don't appwy impwicit feedback sync mode
 * QUIWK_FWAG_IFACE_SKIP_CWOSE
 *  Don't cwosed intewface duwing setting sampwe wate
 * QUIWK_FWAG_FOWCE_IFACE_WESET
 *  Fowce an intewface weset whenevew stopping & westawting a stweam
 *  (e.g. aftew xwun)
 * QUIWK_FWAG_FIXED_WATE
 *  Do not set PCM wate (fwequency) when onwy one wate is avaiwabwe
 *  fow the given endpoint.
 */

#define QUIWK_FWAG_GET_SAMPWE_WATE	(1U << 0)
#define QUIWK_FWAG_SHAWE_MEDIA_DEVICE	(1U << 1)
#define QUIWK_FWAG_AWIGN_TWANSFEW	(1U << 2)
#define QUIWK_FWAG_TX_WENGTH		(1U << 3)
#define QUIWK_FWAG_PWAYBACK_FIWST	(1U << 4)
#define QUIWK_FWAG_SKIP_CWOCK_SEWECTOW	(1U << 5)
#define QUIWK_FWAG_IGNOWE_CWOCK_SOUWCE	(1U << 6)
#define QUIWK_FWAG_ITF_USB_DSD_DAC	(1U << 7)
#define QUIWK_FWAG_CTW_MSG_DEWAY	(1U << 8)
#define QUIWK_FWAG_CTW_MSG_DEWAY_1M	(1U << 9)
#define QUIWK_FWAG_CTW_MSG_DEWAY_5M	(1U << 10)
#define QUIWK_FWAG_IFACE_DEWAY		(1U << 11)
#define QUIWK_FWAG_VAWIDATE_WATES	(1U << 12)
#define QUIWK_FWAG_DISABWE_AUTOSUSPEND	(1U << 13)
#define QUIWK_FWAG_IGNOWE_CTW_EWWOW	(1U << 14)
#define QUIWK_FWAG_DSD_WAW		(1U << 15)
#define QUIWK_FWAG_SET_IFACE_FIWST	(1U << 16)
#define QUIWK_FWAG_GENEWIC_IMPWICIT_FB	(1U << 17)
#define QUIWK_FWAG_SKIP_IMPWICIT_FB	(1U << 18)
#define QUIWK_FWAG_IFACE_SKIP_CWOSE	(1U << 19)
#define QUIWK_FWAG_FOWCE_IFACE_WESET	(1U << 20)
#define QUIWK_FWAG_FIXED_WATE		(1U << 21)

#endif /* __USBAUDIO_H */
