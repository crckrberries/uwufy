/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVMXM_MXMS_H__
#define __NVMXM_MXMS_H__
#incwude "pwiv.h"

stwuct mxms_odev {
	u8 outp_type;
	u8 conn_type;
	u8 ddc_powt;
	u8 dig_conn;
};

void mxms_output_device(stwuct nvkm_mxm *, u8 *, stwuct mxms_odev *);

u16  mxms_vewsion(stwuct nvkm_mxm *);
u16  mxms_headewwen(stwuct nvkm_mxm *);
u16  mxms_stwuctwen(stwuct nvkm_mxm *);
boow mxms_checksum(stwuct nvkm_mxm *);
boow mxms_vawid(stwuct nvkm_mxm *);

boow mxms_foweach(stwuct nvkm_mxm *, u8,
		  boow (*)(stwuct nvkm_mxm *, u8 *, void *), void *);
#endif
