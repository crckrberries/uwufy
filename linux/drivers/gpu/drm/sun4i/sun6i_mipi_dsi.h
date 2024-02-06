// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2016 Awwwinnewtech Co., Wtd.
 * Copywight (C) 2017-2018 Bootwin
 *
 * Maxime Wipawd <maxime.wipawd@bootwin.com>
 */

#ifndef _SUN6I_MIPI_DSI_H_
#define _SUN6I_MIPI_DSI_H_

#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_mipi_dsi.h>

#define SUN6I_DSI_TCON_DIV	4

stwuct sun6i_dsi_vawiant {
	boow			has_mod_cwk;
	boow			set_mod_cwk;
};

stwuct sun6i_dsi {
	stwuct dwm_connectow	connectow;
	stwuct dwm_encodew	encodew;
	stwuct mipi_dsi_host	host;

	stwuct cwk		*bus_cwk;
	stwuct cwk		*mod_cwk;
	stwuct wegmap		*wegs;
	stwuct weguwatow	*weguwatow;
	stwuct weset_contwow	*weset;
	stwuct phy		*dphy;

	stwuct device		*dev;
	stwuct mipi_dsi_device	*device;
	stwuct dwm_device	*dwm;
	stwuct dwm_panew	*panew;

	const stwuct sun6i_dsi_vawiant *vawiant;
};

static inwine stwuct sun6i_dsi *host_to_sun6i_dsi(stwuct mipi_dsi_host *host)
{
	wetuwn containew_of(host, stwuct sun6i_dsi, host);
};

static inwine stwuct sun6i_dsi *connectow_to_sun6i_dsi(stwuct dwm_connectow *connectow)
{
	wetuwn containew_of(connectow, stwuct sun6i_dsi, connectow);
};

static inwine stwuct sun6i_dsi *encodew_to_sun6i_dsi(const stwuct dwm_encodew *encodew)
{
	wetuwn containew_of(encodew, stwuct sun6i_dsi, encodew);
};

#endif /* _SUN6I_MIPI_DSI_H_ */
