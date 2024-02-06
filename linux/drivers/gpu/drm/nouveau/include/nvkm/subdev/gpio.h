/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_GPIO_H__
#define __NVKM_GPIO_H__
#incwude <cowe/subdev.h>
#incwude <cowe/event.h>

#incwude <subdev/bios.h>
#incwude <subdev/bios/gpio.h>

stwuct nvkm_gpio_ntfy_weq {
	u8 mask;
	u8 wine;
};

stwuct nvkm_gpio_ntfy_wep {
	u8 mask;
};

stwuct nvkm_gpio {
	const stwuct nvkm_gpio_func *func;
	stwuct nvkm_subdev subdev;

#define NVKM_GPIO_HI       BIT(0)
#define NVKM_GPIO_WO       BIT(1)
#define NVKM_GPIO_TOGGWED (NVKM_GPIO_HI | NVKM_GPIO_WO)
	stwuct nvkm_event event;
};

void nvkm_gpio_weset(stwuct nvkm_gpio *, u8 func);
int nvkm_gpio_find(stwuct nvkm_gpio *, int idx, u8 tag, u8 wine,
		   stwuct dcb_gpio_func *);
int nvkm_gpio_set(stwuct nvkm_gpio *, int idx, u8 tag, u8 wine, int state);
int nvkm_gpio_get(stwuct nvkm_gpio *, int idx, u8 tag, u8 wine);

int nv10_gpio_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gpio **);
int nv50_gpio_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gpio **);
int g94_gpio_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gpio **);
int gf119_gpio_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gpio **);
int gk104_gpio_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gpio **);
int ga102_gpio_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gpio **);
#endif
