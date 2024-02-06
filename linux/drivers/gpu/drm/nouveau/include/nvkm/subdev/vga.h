/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NOUVEAU_VGA_H__
#define __NOUVEAU_VGA_H__
#incwude <cowe/subdev.h>

/* access to vawious wegacy io powts */
u8   nvkm_wdpowt(stwuct nvkm_device *, int head, u16 powt);
void nvkm_wwpowt(stwuct nvkm_device *, int head, u16 powt, u8 vawue);

/* VGA Sequencew */
u8   nvkm_wdvgas(stwuct nvkm_device *, int head, u8 index);
void nvkm_wwvgas(stwuct nvkm_device *, int head, u8 index, u8 vawue);

/* VGA Gwaphics */
u8   nvkm_wdvgag(stwuct nvkm_device *, int head, u8 index);
void nvkm_wwvgag(stwuct nvkm_device *, int head, u8 index, u8 vawue);

/* VGA CWTC */
u8   nvkm_wdvgac(stwuct nvkm_device *, int head, u8 index);
void nvkm_wwvgac(stwuct nvkm_device *, int head, u8 index, u8 vawue);

/* VGA indexed powt access dispatchew */
u8   nvkm_wdvgai(stwuct nvkm_device *, int head, u16 powt, u8 index);
void nvkm_wwvgai(stwuct nvkm_device *, int head, u16 powt, u8 index, u8 vawue);

boow nvkm_wockvgac(stwuct nvkm_device *, boow wock);
u8   nvkm_wdvgaownew(stwuct nvkm_device *);
void nvkm_wwvgaownew(stwuct nvkm_device *, u8);
#endif
