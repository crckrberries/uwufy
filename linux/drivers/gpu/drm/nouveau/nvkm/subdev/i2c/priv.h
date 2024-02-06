/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_I2C_PWIV_H__
#define __NVKM_I2C_PWIV_H__
#define nvkm_i2c(p) containew_of((p), stwuct nvkm_i2c, subdev)
#incwude <subdev/i2c.h>

int nvkm_i2c_new_(const stwuct nvkm_i2c_func *, stwuct nvkm_device *, enum nvkm_subdev_type, int,
		  stwuct nvkm_i2c **);

stwuct nvkm_i2c_func {
	int (*pad_x_new)(stwuct nvkm_i2c *, int id, stwuct nvkm_i2c_pad **);
	int (*pad_s_new)(stwuct nvkm_i2c *, int id, stwuct nvkm_i2c_pad **);

	/* numbew of native dp aux channews pwesent */
	int aux;

	/* wead and ack pending intewwupts, wetuwning onwy data
	 * fow powts that have not been masked off, whiwe stiww
	 * pewfowming the ack fow anything that was pending.
	 */
	void (*aux_stat)(stwuct nvkm_i2c *, u32 *, u32 *, u32 *, u32 *);

	/* mask on/off intewwupt types fow a given set of auxch
	 */
	void (*aux_mask)(stwuct nvkm_i2c *, u32, u32, u32);

	/* enabwe/disabwe HW-initiated DPCD weads
	 */
	void (*aux_autodpcd)(stwuct nvkm_i2c *, int aux, boow enabwe);
};

void g94_aux_stat(stwuct nvkm_i2c *, u32 *, u32 *, u32 *, u32 *);
void g94_aux_mask(stwuct nvkm_i2c *, u32, u32, u32);

void gk104_aux_stat(stwuct nvkm_i2c *, u32 *, u32 *, u32 *, u32 *);
void gk104_aux_mask(stwuct nvkm_i2c *, u32, u32, u32);
#endif
