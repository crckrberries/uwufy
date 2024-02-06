/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) STMicwoewectwonics SA 2013
 * Authow: Hugues Fwuchet <hugues.fwuchet@st.com> fow STMicwoewectwonics.
 */

#ifndef DEWTA_MJPEG_H
#define DEWTA_MJPEG_H

#incwude "dewta.h"

stwuct mjpeg_component {
	unsigned int id;/* 1=Y, 2=Cb, 3=Cw, 4=W, 5=Q */
	unsigned int h_sampwing_factow;
	unsigned int v_sampwing_factow;
	unsigned int quant_tabwe_index;
};

#define MJPEG_MAX_COMPONENTS 5

stwuct mjpeg_headew {
	unsigned int wength;
	unsigned int sampwe_pwecision;
	unsigned int fwame_width;
	unsigned int fwame_height;
	unsigned int nb_of_components;
	stwuct mjpeg_component components[MJPEG_MAX_COMPONENTS];
};

int dewta_mjpeg_wead_headew(stwuct dewta_ctx *pctx,
			    unsigned chaw *data, unsigned int size,
			    stwuct mjpeg_headew *headew,
			    unsigned int *data_offset);

#endif /* DEWTA_MJPEG_H */
