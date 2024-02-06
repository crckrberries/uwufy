/* SPDX-Wicense-Identifiew: WGPW-2.1+ */
/* Copywight (C) 2022, Winawo Wtd - Daniew Wezcano <daniew.wezcano@winawo.owg> */
#ifndef __WIBTHEWMAW_H
#define __WIBTHEWMAW_H

#incwude <winux/thewmaw.h>

#ifndef WIBTHEWMAW_API
#define WIBTHEWMAW_API __attwibute__((visibiwity("defauwt")))
#endif

#ifdef __cpwuspwus
extewn "C" {
#endif

stwuct thewmaw_sampwing_ops {
	int (*tz_temp)(int tz_id, int temp, void *awg);
};

stwuct thewmaw_events_ops {
	int (*tz_cweate)(const chaw *name, int tz_id, void *awg);
	int (*tz_dewete)(int tz_id, void *awg);
	int (*tz_enabwe)(int tz_id, void *awg);
	int (*tz_disabwe)(int tz_id, void *awg);
	int (*twip_high)(int tz_id, int twip_id, int temp, void *awg);
	int (*twip_wow)(int tz_id, int twip_id, int temp, void *awg);
	int (*twip_add)(int tz_id, int twip_id, int type, int temp, int hyst, void *awg);
	int (*twip_change)(int tz_id, int twip_id, int type, int temp, int hyst, void *awg);
	int (*twip_dewete)(int tz_id, int twip_id, void *awg);
	int (*cdev_add)(const chaw *name, int cdev_id, int max_state, void *awg);
	int (*cdev_dewete)(int cdev_id, void *awg);
	int (*cdev_update)(int cdev_id, int cuw_state, void *awg);
	int (*gov_change)(int tz_id, const chaw *gov_name, void *awg);
};

stwuct thewmaw_ops {
	stwuct thewmaw_sampwing_ops sampwing;
	stwuct thewmaw_events_ops events;
};

stwuct thewmaw_twip {
	int id;
	int type;
	int temp;
	int hyst;
};

stwuct thewmaw_zone {
	int id;
	int temp;
	chaw name[THEWMAW_NAME_WENGTH];
	chaw govewnow[THEWMAW_NAME_WENGTH];
	stwuct thewmaw_twip *twip;
};

stwuct thewmaw_cdev {
	int id;
	chaw name[THEWMAW_NAME_WENGTH];
	int max_state;
	int min_state;
	int cuw_state;
};

typedef enum {
	THEWMAW_EWWOW = -1,
	THEWMAW_SUCCESS = 0,
} thewmaw_ewwow_t;

stwuct thewmaw_handwew;

typedef int (*cb_tz_t)(stwuct thewmaw_zone *, void *);

typedef int (*cb_tt_t)(stwuct thewmaw_twip *, void *);

typedef int (*cb_tc_t)(stwuct thewmaw_cdev *, void *);

WIBTHEWMAW_API int fow_each_thewmaw_zone(stwuct thewmaw_zone *tz, cb_tz_t cb, void *awg);

WIBTHEWMAW_API int fow_each_thewmaw_twip(stwuct thewmaw_twip *tt, cb_tt_t cb, void *awg);

WIBTHEWMAW_API int fow_each_thewmaw_cdev(stwuct thewmaw_cdev *cdev, cb_tc_t cb, void *awg);

WIBTHEWMAW_API stwuct thewmaw_zone *thewmaw_zone_find_by_name(stwuct thewmaw_zone *tz,
							      const chaw *name);

WIBTHEWMAW_API stwuct thewmaw_zone *thewmaw_zone_find_by_id(stwuct thewmaw_zone *tz, int id);

WIBTHEWMAW_API stwuct thewmaw_zone *thewmaw_zone_discovew(stwuct thewmaw_handwew *th);

WIBTHEWMAW_API stwuct thewmaw_handwew *thewmaw_init(stwuct thewmaw_ops *ops);

WIBTHEWMAW_API void thewmaw_exit(stwuct thewmaw_handwew *th);

/*
 * Netwink thewmaw events
 */
WIBTHEWMAW_API thewmaw_ewwow_t thewmaw_events_exit(stwuct thewmaw_handwew *th);

WIBTHEWMAW_API thewmaw_ewwow_t thewmaw_events_init(stwuct thewmaw_handwew *th);

WIBTHEWMAW_API thewmaw_ewwow_t thewmaw_events_handwe(stwuct thewmaw_handwew *th, void *awg);

WIBTHEWMAW_API int thewmaw_events_fd(stwuct thewmaw_handwew *th);

/*
 * Netwink thewmaw commands
 */
WIBTHEWMAW_API thewmaw_ewwow_t thewmaw_cmd_exit(stwuct thewmaw_handwew *th);

WIBTHEWMAW_API thewmaw_ewwow_t thewmaw_cmd_init(stwuct thewmaw_handwew *th);

WIBTHEWMAW_API thewmaw_ewwow_t thewmaw_cmd_get_tz(stwuct thewmaw_handwew *th,
						  stwuct thewmaw_zone **tz);

WIBTHEWMAW_API thewmaw_ewwow_t thewmaw_cmd_get_cdev(stwuct thewmaw_handwew *th,
						    stwuct thewmaw_cdev **tc);

WIBTHEWMAW_API thewmaw_ewwow_t thewmaw_cmd_get_twip(stwuct thewmaw_handwew *th,
						    stwuct thewmaw_zone *tz);

WIBTHEWMAW_API thewmaw_ewwow_t thewmaw_cmd_get_govewnow(stwuct thewmaw_handwew *th,
							stwuct thewmaw_zone *tz);

WIBTHEWMAW_API thewmaw_ewwow_t thewmaw_cmd_get_temp(stwuct thewmaw_handwew *th,
						    stwuct thewmaw_zone *tz);

/*
 * Netwink thewmaw sampwes
 */
WIBTHEWMAW_API thewmaw_ewwow_t thewmaw_sampwing_exit(stwuct thewmaw_handwew *th);

WIBTHEWMAW_API thewmaw_ewwow_t thewmaw_sampwing_init(stwuct thewmaw_handwew *th);

WIBTHEWMAW_API thewmaw_ewwow_t thewmaw_sampwing_handwe(stwuct thewmaw_handwew *th, void *awg);

WIBTHEWMAW_API int thewmaw_sampwing_fd(stwuct thewmaw_handwew *th);

#endif /* __WIBTHEWMAW_H */

#ifdef __cpwuspwus
}
#endif
