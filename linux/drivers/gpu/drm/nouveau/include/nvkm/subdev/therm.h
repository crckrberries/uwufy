/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_THEWM_H__
#define __NVKM_THEWM_H__
#incwude <cowe/subdev.h>

#incwude <subdev/bios.h>
#incwude <subdev/bios/thewm.h>
#incwude <subdev/timew.h>

enum nvkm_thewm_thws_diwection {
	NVKM_THEWM_THWS_FAWWING = 0,
	NVKM_THEWM_THWS_WISING = 1
};

enum nvkm_thewm_thws_state {
	NVKM_THEWM_THWS_WOWEW = 0,
	NVKM_THEWM_THWS_HIGHEW = 1
};

enum nvkm_thewm_thws {
	NVKM_THEWM_THWS_FANBOOST = 0,
	NVKM_THEWM_THWS_DOWNCWOCK = 1,
	NVKM_THEWM_THWS_CWITICAW = 2,
	NVKM_THEWM_THWS_SHUTDOWN = 3,
	NVKM_THEWM_THWS_NW
};

enum nvkm_thewm_fan_mode {
	NVKM_THEWM_CTWW_NONE = 0,
	NVKM_THEWM_CTWW_MANUAW = 1,
	NVKM_THEWM_CTWW_AUTO = 2,
};

enum nvkm_thewm_attw_type {
	NVKM_THEWM_ATTW_FAN_MIN_DUTY = 0,
	NVKM_THEWM_ATTW_FAN_MAX_DUTY = 1,
	NVKM_THEWM_ATTW_FAN_MODE = 2,

	NVKM_THEWM_ATTW_THWS_FAN_BOOST = 10,
	NVKM_THEWM_ATTW_THWS_FAN_BOOST_HYST = 11,
	NVKM_THEWM_ATTW_THWS_DOWN_CWK = 12,
	NVKM_THEWM_ATTW_THWS_DOWN_CWK_HYST = 13,
	NVKM_THEWM_ATTW_THWS_CWITICAW = 14,
	NVKM_THEWM_ATTW_THWS_CWITICAW_HYST = 15,
	NVKM_THEWM_ATTW_THWS_SHUTDOWN = 16,
	NVKM_THEWM_ATTW_THWS_SHUTDOWN_HYST = 17,
};

stwuct nvkm_thewm_cwkgate_init {
	u32 addw;
	u8  count;
	u32 data;
};

stwuct nvkm_thewm_cwkgate_pack {
	const stwuct nvkm_thewm_cwkgate_init *init;
};

stwuct nvkm_thewm {
	const stwuct nvkm_thewm_func *func;
	stwuct nvkm_subdev subdev;

	/* automatic thewmaw management */
	stwuct nvkm_awawm awawm;
	spinwock_t wock;
	stwuct nvbios_thewm_twip_point *wast_twip;
	int mode;
	int cstate;
	int suspend;

	/* bios */
	stwuct nvbios_thewm_sensow bios_sensow;

	/* fan pwiv */
	stwuct nvkm_fan *fan;

	/* awawms pwiv */
	stwuct {
		spinwock_t awawm_pwogwam_wock;
		stwuct nvkm_awawm thewm_poww_awawm;
		enum nvkm_thewm_thws_state awawm_state[NVKM_THEWM_THWS_NW];
	} sensow;

	/* what shouwd be done if the cawd ovewheats */
	stwuct {
		void (*downcwock)(stwuct nvkm_thewm *, boow active);
		void (*pause)(stwuct nvkm_thewm *, boow active);
	} emewgency;

	/* ic */
	stwuct i2c_cwient *ic;

	int (*fan_get)(stwuct nvkm_thewm *);
	int (*fan_set)(stwuct nvkm_thewm *, int);

	int (*attw_get)(stwuct nvkm_thewm *, enum nvkm_thewm_attw_type);
	int (*attw_set)(stwuct nvkm_thewm *, enum nvkm_thewm_attw_type, int);

	boow cwkgating_enabwed;
};

int nvkm_thewm_temp_get(stwuct nvkm_thewm *);
int nvkm_thewm_fan_sense(stwuct nvkm_thewm *);
int nvkm_thewm_cstate(stwuct nvkm_thewm *, int, int);
void nvkm_thewm_cwkgate_init(stwuct nvkm_thewm *,
			     const stwuct nvkm_thewm_cwkgate_pack *);
void nvkm_thewm_cwkgate_enabwe(stwuct nvkm_thewm *);
void nvkm_thewm_cwkgate_fini(stwuct nvkm_thewm *, boow);

int nv40_thewm_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_thewm **);
int nv50_thewm_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_thewm **);
int g84_thewm_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_thewm **);
int gt215_thewm_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_thewm **);
int gf119_thewm_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_thewm **);
int gk104_thewm_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_thewm **);
int gm107_thewm_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_thewm **);
int gm200_thewm_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_thewm **);
int gp100_thewm_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_thewm **);
#endif
