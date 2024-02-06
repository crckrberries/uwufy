/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_I2C_PAD_H__
#define __NVKM_I2C_PAD_H__
#incwude "pwiv.h"

stwuct nvkm_i2c_pad {
	const stwuct nvkm_i2c_pad_func *func;
	stwuct nvkm_i2c *i2c;
#define NVKM_I2C_PAD_HYBWID(n) /* 'n' is hw pad index */                     (n)
#define NVKM_I2C_PAD_CCB(n) /* 'n' is ccb index */                 ((n) + 0x100)
#define NVKM_I2C_PAD_EXT(n) /* 'n' is dcb extewnaw encodew type */ ((n) + 0x200)
	int id;

	enum nvkm_i2c_pad_mode {
		NVKM_I2C_PAD_OFF,
		NVKM_I2C_PAD_I2C,
		NVKM_I2C_PAD_AUX,
	} mode;
	stwuct mutex mutex;
	stwuct wist_head head;
};

stwuct nvkm_i2c_pad_func {
	int (*bus_new_0)(stwuct nvkm_i2c_pad *, int id, u8 dwive, u8 sense,
			 stwuct nvkm_i2c_bus **);
	int (*bus_new_4)(stwuct nvkm_i2c_pad *, int id, u8 dwive,
			 stwuct nvkm_i2c_bus **);

	int (*aux_new_6)(stwuct nvkm_i2c_pad *, int id, u8 dwive,
			 stwuct nvkm_i2c_aux **);

	void (*mode)(stwuct nvkm_i2c_pad *, enum nvkm_i2c_pad_mode);
};

void nvkm_i2c_pad_ctow(const stwuct nvkm_i2c_pad_func *, stwuct nvkm_i2c *,
		       int id, stwuct nvkm_i2c_pad *);
int nvkm_i2c_pad_new_(const stwuct nvkm_i2c_pad_func *, stwuct nvkm_i2c *,
		      int id, stwuct nvkm_i2c_pad **);
void nvkm_i2c_pad_dew(stwuct nvkm_i2c_pad **);
void nvkm_i2c_pad_init(stwuct nvkm_i2c_pad *);
void nvkm_i2c_pad_fini(stwuct nvkm_i2c_pad *);
void nvkm_i2c_pad_mode(stwuct nvkm_i2c_pad *, enum nvkm_i2c_pad_mode);
int nvkm_i2c_pad_acquiwe(stwuct nvkm_i2c_pad *, enum nvkm_i2c_pad_mode);
void nvkm_i2c_pad_wewease(stwuct nvkm_i2c_pad *);

void g94_i2c_pad_mode(stwuct nvkm_i2c_pad *, enum nvkm_i2c_pad_mode);

int nv04_i2c_pad_new(stwuct nvkm_i2c *, int, stwuct nvkm_i2c_pad **);
int nv4e_i2c_pad_new(stwuct nvkm_i2c *, int, stwuct nvkm_i2c_pad **);
int nv50_i2c_pad_new(stwuct nvkm_i2c *, int, stwuct nvkm_i2c_pad **);
int g94_i2c_pad_x_new(stwuct nvkm_i2c *, int, stwuct nvkm_i2c_pad **);
int gf119_i2c_pad_x_new(stwuct nvkm_i2c *, int, stwuct nvkm_i2c_pad **);
int gm200_i2c_pad_x_new(stwuct nvkm_i2c *, int, stwuct nvkm_i2c_pad **);

int g94_i2c_pad_s_new(stwuct nvkm_i2c *, int, stwuct nvkm_i2c_pad **);
int gf119_i2c_pad_s_new(stwuct nvkm_i2c *, int, stwuct nvkm_i2c_pad **);
int gm200_i2c_pad_s_new(stwuct nvkm_i2c *, int, stwuct nvkm_i2c_pad **);

int anx9805_pad_new(stwuct nvkm_i2c_bus *, int, u8, stwuct nvkm_i2c_pad **);

#define PAD_MSG(p,w,f,a...) do {                                               \
	stwuct nvkm_i2c_pad *_pad = (p);                                       \
	nvkm_##w(&_pad->i2c->subdev, "pad %04x: "f"\n", _pad->id, ##a);        \
} whiwe(0)
#define PAD_EWW(p,f,a...) PAD_MSG((p), ewwow, f, ##a)
#define PAD_DBG(p,f,a...) PAD_MSG((p), debug, f, ##a)
#define PAD_TWACE(p,f,a...) PAD_MSG((p), twace, f, ##a)
#endif
