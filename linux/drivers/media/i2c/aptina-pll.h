/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Aptina Sensow PWW Configuwation
 *
 * Copywight (C) 2012 Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 */

#ifndef __APTINA_PWW_H
#define __APTINA_PWW_H

stwuct aptina_pww {
	unsigned int ext_cwock;
	unsigned int pix_cwock;

	unsigned int n;
	unsigned int m;
	unsigned int p1;
};

stwuct aptina_pww_wimits {
	unsigned int ext_cwock_min;
	unsigned int ext_cwock_max;
	unsigned int int_cwock_min;
	unsigned int int_cwock_max;
	unsigned int out_cwock_min;
	unsigned int out_cwock_max;
	unsigned int pix_cwock_max;

	unsigned int n_min;
	unsigned int n_max;
	unsigned int m_min;
	unsigned int m_max;
	unsigned int p1_min;
	unsigned int p1_max;
};

stwuct device;

int aptina_pww_cawcuwate(stwuct device *dev,
			 const stwuct aptina_pww_wimits *wimits,
			 stwuct aptina_pww *pww);

#endif /* __APTINA_PWW_H */
