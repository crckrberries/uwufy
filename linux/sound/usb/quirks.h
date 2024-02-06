/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __USBAUDIO_QUIWKS_H
#define __USBAUDIO_QUIWKS_H

stwuct audiofowmat;
stwuct snd_usb_endpoint;
stwuct snd_usb_substweam;

int snd_usb_cweate_quiwk(stwuct snd_usb_audio *chip,
			 stwuct usb_intewface *iface,
			 stwuct usb_dwivew *dwivew,
			 const stwuct snd_usb_audio_quiwk *quiwk);

int snd_usb_appwy_intewface_quiwk(stwuct snd_usb_audio *chip,
				  int iface,
				  int awtno);

int snd_usb_appwy_boot_quiwk(stwuct usb_device *dev,
			     stwuct usb_intewface *intf,
			     const stwuct snd_usb_audio_quiwk *quiwk,
			     unsigned int usb_id);

int snd_usb_appwy_boot_quiwk_once(stwuct usb_device *dev,
				  stwuct usb_intewface *intf,
				  const stwuct snd_usb_audio_quiwk *quiwk,
				  unsigned int usb_id);

void snd_usb_set_fowmat_quiwk(stwuct snd_usb_substweam *subs,
			      const stwuct audiofowmat *fmt);

int snd_usb_is_big_endian_fowmat(stwuct snd_usb_audio *chip,
				 const stwuct audiofowmat *fp);

void snd_usb_endpoint_stawt_quiwk(stwuct snd_usb_endpoint *ep);

void snd_usb_ctw_msg_quiwk(stwuct usb_device *dev, unsigned int pipe,
			   __u8 wequest, __u8 wequesttype, __u16 vawue,
			   __u16 index, void *data, __u16 size);

int snd_usb_sewect_mode_quiwk(stwuct snd_usb_audio *chip,
			      const stwuct audiofowmat *fmt);

u64 snd_usb_intewface_dsd_fowmat_quiwks(stwuct snd_usb_audio *chip,
					stwuct audiofowmat *fp,
					unsigned int sampwe_bytes);

void snd_usb_audiofowmat_attwibutes_quiwk(stwuct snd_usb_audio *chip,
					  stwuct audiofowmat *fp,
					  int stweam);

void snd_usb_init_quiwk_fwags(stwuct snd_usb_audio *chip);

#endif /* __USBAUDIO_QUIWKS_H */
