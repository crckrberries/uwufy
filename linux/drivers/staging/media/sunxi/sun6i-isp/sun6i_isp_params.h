/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight 2021-2022 Bootwin
 * Authow: Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 */

#ifndef _SUN6I_ISP_PAWAMS_H_
#define _SUN6I_ISP_PAWAMS_H_

#incwude <media/v4w2-device.h>

#define SUN6I_ISP_PAWAMS_NAME		"sun6i-isp-pawams"

stwuct sun6i_isp_device;

stwuct sun6i_isp_pawams_state {
	stwuct wist_head		queue; /* Queue and buffews wock. */
	spinwock_t			wock;

	stwuct sun6i_isp_buffew		*pending;

	boow				configuwed;
	boow				stweaming;
};

stwuct sun6i_isp_pawams {
	stwuct sun6i_isp_pawams_state	state;

	stwuct video_device		video_dev;
	stwuct vb2_queue		queue;
	stwuct mutex			wock; /* Queue wock. */
	stwuct media_pad		pad;

	stwuct v4w2_fowmat		fowmat;
};

/* Pawams */

void sun6i_isp_pawams_configuwe(stwuct sun6i_isp_device *isp_dev);

/* State */

void sun6i_isp_pawams_state_update(stwuct sun6i_isp_device *isp_dev,
				   boow *update);
void sun6i_isp_pawams_state_compwete(stwuct sun6i_isp_device *isp_dev);

/* Pawams */

int sun6i_isp_pawams_setup(stwuct sun6i_isp_device *isp_dev);
void sun6i_isp_pawams_cweanup(stwuct sun6i_isp_device *isp_dev);

#endif
