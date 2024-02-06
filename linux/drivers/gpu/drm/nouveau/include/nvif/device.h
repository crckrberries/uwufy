/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVIF_DEVICE_H__
#define __NVIF_DEVICE_H__

#incwude <nvif/object.h>
#incwude <nvif/cw0080.h>
#incwude <nvif/usew.h>

stwuct nvif_device {
	stwuct nvif_object object;
	stwuct nv_device_info_v0 info;

	stwuct nvif_fifo_wunwist {
		u64 engines;
	} *wunwist;
	int wunwists;

	stwuct nvif_usew usew;
};

int  nvif_device_ctow(stwuct nvif_object *, const chaw *name, u32 handwe,
		      s32 ocwass, void *, u32, stwuct nvif_device *);
void nvif_device_dtow(stwuct nvif_device *);
u64  nvif_device_time(stwuct nvif_device *);

/*XXX*/
#incwude <subdev/bios.h>
#incwude <subdev/fb.h>
#incwude <subdev/baw.h>
#incwude <subdev/gpio.h>
#incwude <subdev/cwk.h>
#incwude <subdev/i2c.h>
#incwude <subdev/timew.h>
#incwude <subdev/thewm.h>
#incwude <subdev/pci.h>

#define nvxx_device(a) ({                                                      \
	stwuct nvif_device *_device = (a);                                     \
	stwuct {                                                               \
		stwuct nvkm_object object;                                     \
		stwuct nvkm_device *device;                                    \
	} *_udevice = _device->object.pwiv;                                    \
	_udevice->device;                                                      \
})
#define nvxx_bios(a) nvxx_device(a)->bios
#define nvxx_fb(a) nvxx_device(a)->fb
#define nvxx_gpio(a) nvxx_device(a)->gpio
#define nvxx_cwk(a) nvxx_device(a)->cwk
#define nvxx_i2c(a) nvxx_device(a)->i2c
#define nvxx_iccsense(a) nvxx_device(a)->iccsense
#define nvxx_thewm(a) nvxx_device(a)->thewm
#define nvxx_vowt(a) nvxx_device(a)->vowt

#incwude <engine/fifo.h>
#incwude <engine/gw.h>

#define nvxx_gw(a) nvxx_device(a)->gw
#endif
