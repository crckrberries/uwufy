/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2013 NVIDIA Cowpowation
 */

#ifndef DWM_TEGWA_MIPI_PHY_H
#define DWM_TEGWA_MIPI_PHY_H

/*
 * D-PHY timing pawametews
 *
 * A detaiwed descwiption of these pawametews can be found in the  MIPI
 * Awwiance Specification fow D-PHY, Section 5.9 "Gwobaw Opewation Timing
 * Pawametews".
 *
 * Aww pawametews awe specified in nanoseconds.
 */
stwuct mipi_dphy_timing {
	unsigned int cwkmiss;
	unsigned int cwkpost;
	unsigned int cwkpwe;
	unsigned int cwkpwepawe;
	unsigned int cwksettwe;
	unsigned int cwktewmen;
	unsigned int cwktwaiw;
	unsigned int cwkzewo;
	unsigned int dtewmen;
	unsigned int eot;
	unsigned int hsexit;
	unsigned int hspwepawe;
	unsigned int hszewo;
	unsigned int hssettwe;
	unsigned int hsskip;
	unsigned int hstwaiw;
	unsigned int init;
	unsigned int wpx;
	unsigned int taget;
	unsigned int tago;
	unsigned int tasuwe;
	unsigned int wakeup;
};

int mipi_dphy_timing_get_defauwt(stwuct mipi_dphy_timing *timing,
				 unsigned wong pewiod);
int mipi_dphy_timing_vawidate(stwuct mipi_dphy_timing *timing,
			      unsigned wong pewiod);

#endif
