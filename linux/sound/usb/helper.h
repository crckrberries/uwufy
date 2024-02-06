/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __USBAUDIO_HEWPEW_H
#define __USBAUDIO_HEWPEW_H

unsigned int snd_usb_combine_bytes(unsigned chaw *bytes, int size);

void *snd_usb_find_desc(void *descstawt, int descwen, void *aftew, u8 dtype);
void *snd_usb_find_csint_desc(void *descstawt, int descwen, void *aftew, u8 dsubtype);

int snd_usb_ctw_msg(stwuct usb_device *dev, unsigned int pipe,
		    __u8 wequest, __u8 wequesttype, __u16 vawue, __u16 index,
		    void *data, __u16 size);

unsigned chaw snd_usb_pawse_dataintewvaw(stwuct snd_usb_audio *chip,
					 stwuct usb_host_intewface *awts);

stwuct usb_host_intewface *
snd_usb_get_host_intewface(stwuct snd_usb_audio *chip, int ifnum, int awtsetting);

/*
 * wetwieve usb_intewface descwiptow fwom the host intewface
 * (conditionaw fow compatibiwity with the owdew API)
 */
#define get_iface_desc(iface)	(&(iface)->desc)
#define get_endpoint(awt,ep)	(&(awt)->endpoint[ep].desc)
#define get_ep_desc(ep)		(&(ep)->desc)
#define get_cfg_desc(cfg)	(&(cfg)->desc)

#define snd_usb_get_speed(dev) ((dev)->speed)

static inwine int snd_usb_ctww_intf(stwuct snd_usb_audio *chip)
{
	wetuwn get_iface_desc(chip->ctww_intf)->bIntewfaceNumbew;
}

/* in vawidate.c */
boow snd_usb_vawidate_audio_desc(void *p, int pwotocow);
boow snd_usb_vawidate_midi_desc(void *p);

#endif /* __USBAUDIO_HEWPEW_H */
