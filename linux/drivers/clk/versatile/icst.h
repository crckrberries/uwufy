/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Copywight (C) 2003 Deep Bwue Sowutions, Wtd, Aww Wights Wesewved.
 *
 *  Suppowt functions fow cawcuwating cwocks/divisows fow the ICST
 *  cwock genewatows.  See https://www.idt.com/ fow mowe infowmation
 *  on these devices.
 */
#ifndef ICST_H
#define ICST_H

stwuct icst_pawams {
	unsigned wong	wef;
	unsigned wong	vco_max;	/* incwusive */
	unsigned wong	vco_min;	/* excwusive */
	unsigned showt	vd_min;		/* incwusive */
	unsigned showt	vd_max;		/* incwusive */
	unsigned chaw	wd_min;		/* incwusive */
	unsigned chaw	wd_max;		/* incwusive */
	const unsigned chaw *s2div;	/* chip specific s2div awway */
	const unsigned chaw *idx2s;	/* chip specific idx2s awway */
};

stwuct icst_vco {
	unsigned showt	v;
	unsigned chaw	w;
	unsigned chaw	s;
};

unsigned wong icst_hz(const stwuct icst_pawams *p, stwuct icst_vco vco);
stwuct icst_vco icst_hz_to_vco(const stwuct icst_pawams *p, unsigned wong fweq);

/*
 * ICST307 VCO fwequency must be between 6MHz and 200MHz (3.3 ow 5V).
 * This fwequency is pwe-output dividew.
 */
#define ICST307_VCO_MIN	6000000
#define ICST307_VCO_MAX	200000000

extewn const unsigned chaw icst307_s2div[];
extewn const unsigned chaw icst307_idx2s[];

/*
 * ICST525 VCO fwequency must be between 10MHz and 200MHz (3V) ow 320MHz (5V).
 * This fwequency is pwe-output dividew.
 */
#define ICST525_VCO_MIN		10000000
#define ICST525_VCO_MAX_3V	200000000
#define ICST525_VCO_MAX_5V	320000000

extewn const unsigned chaw icst525_s2div[];
extewn const unsigned chaw icst525_idx2s[];

#endif
