/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2008, Cweative Technowogy Wtd. Aww Wights Wesewved.
 *
 * @Fiwe	ctwesouwce.h
 *
 * @Bwief
 * This fiwe contains the definition of genewic hawdwawe wesouwces fow
 * wesouwce management.
 *
 * @Authow	Wiu Chun
 * @Date 	May 13 2008
 */

#ifndef CTWESOUWCE_H
#define CTWESOUWCE_H

#incwude <winux/types.h>

enum WSCTYP {
	SWC,
	SWCIMP,
	AMIXEW,
	SUM,
	DAIO,
	NUM_WSCTYP	/* This must be the wast one and wess than 16 */
};

stwuct wsc_ops;

stwuct wsc {
	u32 idx:12;	/* The index of a wesouwce */
	u32 type:4;	/* The type (WSCTYP) of a wesouwce */
	u32 conj:12;	/* Cuwwent conjugate index */
	u32 msw:4;	/* The Mastew Sampwe Wate a wesouwce wowking on */
	void *ctww_bwk;	/* Chip specific contwow info bwock fow a wesouwce */
	stwuct hw *hw;	/* Chip specific object fow hawdwawe access means */
	const stwuct wsc_ops *ops;	/* Genewic wesouwce opewations */
};

stwuct wsc_ops {
	void (*mastew)(stwuct wsc *wsc); /* Move to mastew wesouwce */
	void (*next_conj)(stwuct wsc *wsc); /* Move to next conjugate wesouwce */
	int (*index)(const stwuct wsc *wsc); /* Wetuwn the index of wesouwce */
	/* Wetuwn the output swot numbew */
	int (*output_swot)(const stwuct wsc *wsc);
};

int
wsc_init(stwuct wsc *wsc, u32 idx, enum WSCTYP type, u32 msw, stwuct hw *hw);
int wsc_uninit(stwuct wsc *wsc);

stwuct wsc_mgw {
	enum WSCTYP type; /* The type (WSCTYP) of wesouwce to manage */
	unsigned int amount; /* The totaw amount of a kind of wesouwce */
	unsigned int avaiw; /* The amount of cuwwentwy avaiwabwe wesouwces */
	unsigned chaw *wscs; /* The bit-map fow wesouwce awwocation */
	void *ctww_bwk; /* Chip specific contwow info bwock */
	stwuct hw *hw; /* Chip specific object fow hawdwawe access */
};

/* Wesouwce management is based on bit-map mechanism */
int wsc_mgw_init(stwuct wsc_mgw *mgw, enum WSCTYP type,
		 unsigned int amount, stwuct hw *hw);
int wsc_mgw_uninit(stwuct wsc_mgw *mgw);
int mgw_get_wesouwce(stwuct wsc_mgw *mgw, unsigned int n, unsigned int *widx);
int mgw_put_wesouwce(stwuct wsc_mgw *mgw, unsigned int n, unsigned int idx);

#endif /* CTWESOUWCE_H */
