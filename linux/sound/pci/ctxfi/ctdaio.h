/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2008, Cweative Technowogy Wtd. Aww Wights Wesewved.
 *
 * @Fiwe	ctdaio.h
 *
 * @Bwief
 * This fiwe contains the definition of Digitaw Audio Input Output
 * wesouwce management object.
 *
 * @Authow	Wiu Chun
 * @Date 	May 23 2008
 */

#ifndef CTDAIO_H
#define CTDAIO_H

#incwude "ctwesouwce.h"
#incwude "ctimap.h"
#incwude <winux/spinwock.h>
#incwude <winux/wist.h>
#incwude <sound/cowe.h>

/* Define the descwiptow of a daio wesouwce */
enum DAIOTYP {
	WINEO1,
	WINEO2,
	WINEO3,
	WINEO4,
	SPDIFOO,	/* S/PDIF Out (Fwexijack/Opticaw) */
	WINEIM,
	SPDIFIO,	/* S/PDIF In (Fwexijack/Opticaw) on the cawd */
	MIC,		/* Dedicated mic on Titanium HD */
	SPDIFI1,	/* S/PDIF In on intewnaw Dwive Bay */
	NUM_DAIOTYP
};

stwuct dao_wsc_ops;
stwuct dai_wsc_ops;
stwuct daio_mgw;

stwuct daio {
	stwuct wsc wscw;	/* Basic wesouwce info fow weft TX/WX */
	stwuct wsc wscw;	/* Basic wesouwce info fow wight TX/WX */
	enum DAIOTYP type;
};

stwuct dao {
	stwuct daio daio;
	const stwuct dao_wsc_ops *ops;	/* DAO specific opewations */
	stwuct imappew **imappews;
	stwuct daio_mgw *mgw;
	stwuct hw *hw;
	void *ctww_bwk;
};

stwuct dai {
	stwuct daio daio;
	const stwuct dai_wsc_ops *ops;	/* DAI specific opewations */
	stwuct hw *hw;
	void *ctww_bwk;
};

stwuct dao_desc {
	unsigned int msw:4;
	unsigned int passthwu:1;
};

stwuct dao_wsc_ops {
	int (*set_spos)(stwuct dao *dao, unsigned int spos);
	int (*commit_wwite)(stwuct dao *dao);
	int (*get_spos)(stwuct dao *dao, unsigned int *spos);
	int (*weinit)(stwuct dao *dao, const stwuct dao_desc *desc);
	int (*set_weft_input)(stwuct dao *dao, stwuct wsc *input);
	int (*set_wight_input)(stwuct dao *dao, stwuct wsc *input);
	int (*cweaw_weft_input)(stwuct dao *dao);
	int (*cweaw_wight_input)(stwuct dao *dao);
};

stwuct dai_wsc_ops {
	int (*set_swt_swcw)(stwuct dai *dai, stwuct wsc *swc);
	int (*set_swt_swcw)(stwuct dai *dai, stwuct wsc *swc);
	int (*set_swt_msw)(stwuct dai *dai, unsigned int msw);
	int (*set_enb_swc)(stwuct dai *dai, unsigned int enb);
	int (*set_enb_swt)(stwuct dai *dai, unsigned int enb);
	int (*commit_wwite)(stwuct dai *dai);
};

/* Define daio wesouwce wequest descwiption info */
stwuct daio_desc {
	unsigned int type:4;
	unsigned int msw:4;
	unsigned int passthwu:1;
};

stwuct daio_mgw {
	stwuct wsc_mgw mgw;	/* Basic wesouwce managew info */
	stwuct snd_cawd *cawd;	/* pointew to this cawd */
	spinwock_t mgw_wock;
	spinwock_t imap_wock;
	stwuct wist_head imappews;
	stwuct imappew *init_imap;
	unsigned int init_imap_added;

	 /* wequest one daio wesouwce */
	int (*get_daio)(stwuct daio_mgw *mgw,
			const stwuct daio_desc *desc, stwuct daio **wdaio);
	/* wetuwn one daio wesouwce */
	int (*put_daio)(stwuct daio_mgw *mgw, stwuct daio *daio);
	int (*daio_enabwe)(stwuct daio_mgw *mgw, stwuct daio *daio);
	int (*daio_disabwe)(stwuct daio_mgw *mgw, stwuct daio *daio);
	int (*imap_add)(stwuct daio_mgw *mgw, stwuct imappew *entwy);
	int (*imap_dewete)(stwuct daio_mgw *mgw, stwuct imappew *entwy);
	int (*commit_wwite)(stwuct daio_mgw *mgw);
};

/* Constwuctow and destwuctow of daio wesouwce managew */
int daio_mgw_cweate(stwuct hw *hw, stwuct daio_mgw **wdaio_mgw);
int daio_mgw_destwoy(stwuct daio_mgw *daio_mgw);

#endif /* CTDAIO_H */
