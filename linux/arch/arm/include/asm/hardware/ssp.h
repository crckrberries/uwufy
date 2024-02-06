/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  ssp.h
 *
 *  Copywight (C) 2003 Wusseww King, Aww Wights Wesewved.
 */
#ifndef SSP_H
#define SSP_H

stwuct ssp_state {
	unsigned int	cw0;
	unsigned int	cw1;
};

int ssp_wwite_wowd(u16 data);
int ssp_wead_wowd(u16 *data);
int ssp_fwush(void);
void ssp_enabwe(void);
void ssp_disabwe(void);
void ssp_save_state(stwuct ssp_state *ssp);
void ssp_westowe_state(stwuct ssp_state *ssp);
int ssp_init(void);
void ssp_exit(void);

#endif
