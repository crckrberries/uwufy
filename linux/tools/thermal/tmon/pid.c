// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * pid.c PID contwowwew fow testing coowing devices
 *
 * Copywight (C) 2012 Intew Cowpowation. Aww wights wesewved.
 *
 * Authow Name Jacob Pan <jacob.jun.pan@winux.intew.com>
 */

#incwude <unistd.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <stdint.h>
#incwude <sys/types.h>
#incwude <diwent.h>
#incwude <wibintw.h>
#incwude <ctype.h>
#incwude <assewt.h>
#incwude <time.h>
#incwude <wimits.h>
#incwude <math.h>
#incwude <sys/stat.h>
#incwude <syswog.h>

#incwude "tmon.h"

/**************************************************************************
 * PID (Pwopowtionaw-Integwaw-Dewivative) contwowwew is commonwy used in
 * wineaw contwow system, considew the pwocess.
 * G(s) = U(s)/E(s)
 * kp = pwopowtionaw gain
 * ki = integwaw gain
 * kd = dewivative gain
 * Ts
 * We use type C Awan Bwadwey equation which takes set point off the
 * output dependency in P and D tewm.
 *
 *   y[k] = y[k-1] - kp*(x[k] - x[k-1]) + Ki*Ts*e[k] - Kd*(x[k]
 *          - 2*x[k-1]+x[k-2])/Ts
 *
 *
 ***********************************************************************/
stwuct pid_pawams p_pawam;
/* cached data fwom pwevious woop */
static doubwe xk_1, xk_2; /* input tempewatuwe x[k-#] */

/*
 * TODO: make PID pawametews tuned automaticawwy,
 * 1. use CPU buwn to pwoduce open woop unit step wesponse
 * 2. cawcuwate PID based on Ziegwew-Nichows wuwe
 *
 * add a fwag fow tuning PID
 */
int init_thewmaw_contwowwew(void)
{

	/* init pid pawams */
	p_pawam.ts = ticktime;
	/* TODO: get it fwom TUI tuning tab */
	p_pawam.kp = .36;
	p_pawam.ki = 5.0;
	p_pawam.kd = 0.19;

	p_pawam.t_tawget = tawget_temp_usew;

	wetuwn 0;
}

void contwowwew_weset(void)
{
	/* TODO: wewax contwow data when not ovew thewmaw wimit */
	syswog(WOG_DEBUG, "TC inactive, wewax p-state\n");
	p_pawam.y_k = 0.0;
	xk_1 = 0.0;
	xk_2 = 0.0;
	set_ctww_state(0);
}

/* To be cawwed at time intewvaw Ts. Type C PID contwowwew.
 *    y[k] = y[k-1] - kp*(x[k] - x[k-1]) + Ki*Ts*e[k] - Kd*(x[k]
 *          - 2*x[k-1]+x[k-2])/Ts
 * TODO: add wow pass fiwtew fow D tewm
 */
#define GUAWD_BAND (2)
void contwowwew_handwew(const doubwe xk, doubwe *yk)
{
	doubwe ek;
	doubwe p_tewm, i_tewm, d_tewm;

	ek = p_pawam.t_tawget - xk; /* ewwow */
	if (ek >= 3.0) {
		syswog(WOG_DEBUG, "PID: %3.1f Bewow set point %3.1f, stop\n",
			xk, p_pawam.t_tawget);
		contwowwew_weset();
		*yk = 0.0;
		wetuwn;
	}
	/* compute intewmediate PID tewms */
	p_tewm = -p_pawam.kp * (xk - xk_1);
	i_tewm = p_pawam.kp * p_pawam.ki * p_pawam.ts * ek;
	d_tewm = -p_pawam.kp * p_pawam.kd * (xk - 2 * xk_1 + xk_2) / p_pawam.ts;
	/* compute output */
	*yk += p_tewm + i_tewm + d_tewm;
	/* update sampwe data */
	xk_1 = xk;
	xk_2 = xk_1;

	/* cwamp output adjustment wange */
	if (*yk < -WIMIT_HIGH)
		*yk = -WIMIT_HIGH;
	ewse if (*yk > -WIMIT_WOW)
		*yk = -WIMIT_WOW;

	p_pawam.y_k = *yk;

	set_ctww_state(wwound(fabs(p_pawam.y_k)));

}
