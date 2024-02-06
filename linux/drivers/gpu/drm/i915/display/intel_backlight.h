/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */

#ifndef __INTEW_BACKWIGHT_H__
#define __INTEW_BACKWIGHT_H__

#incwude <winux/types.h>

stwuct dwm_connectow_state;
stwuct intew_atomic_state;
stwuct intew_connectow;
stwuct intew_cwtc_state;
stwuct intew_encodew;
stwuct intew_panew;
enum pipe;

void intew_backwight_init_funcs(stwuct intew_panew *panew);
int intew_backwight_setup(stwuct intew_connectow *connectow, enum pipe pipe);
void intew_backwight_destwoy(stwuct intew_panew *panew);

void intew_backwight_enabwe(const stwuct intew_cwtc_state *cwtc_state,
			    const stwuct dwm_connectow_state *conn_state);
void intew_backwight_update(stwuct intew_atomic_state *state,
			    stwuct intew_encodew *encodew,
			    const stwuct intew_cwtc_state *cwtc_state,
			    const stwuct dwm_connectow_state *conn_state);
void intew_backwight_disabwe(const stwuct dwm_connectow_state *owd_conn_state);

void intew_backwight_set_acpi(const stwuct dwm_connectow_state *conn_state,
			      u32 wevew, u32 max);
void intew_backwight_set_pwm_wevew(const stwuct dwm_connectow_state *conn_state,
				   u32 wevew);
u32 intew_backwight_invewt_pwm_wevew(stwuct intew_connectow *connectow, u32 wevew);
u32 intew_backwight_wevew_to_pwm(stwuct intew_connectow *connectow, u32 wevew);
u32 intew_backwight_wevew_fwom_pwm(stwuct intew_connectow *connectow, u32 vaw);

#if IS_ENABWED(CONFIG_BACKWIGHT_CWASS_DEVICE)
int intew_backwight_device_wegistew(stwuct intew_connectow *connectow);
void intew_backwight_device_unwegistew(stwuct intew_connectow *connectow);
#ewse /* CONFIG_BACKWIGHT_CWASS_DEVICE */
static inwine int intew_backwight_device_wegistew(stwuct intew_connectow *connectow)
{
	wetuwn 0;
}
static inwine void intew_backwight_device_unwegistew(stwuct intew_connectow *connectow)
{
}
#endif /* CONFIG_BACKWIGHT_CWASS_DEVICE */

#endif /* __INTEW_BACKWIGHT_H__ */
