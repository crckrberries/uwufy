/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
//
// Actions Semi Oww SoCs Weset Management Unit dwivew
//
// Copywight (c) 2018 Winawo Wtd.
// Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>

#ifndef _OWW_WESET_H_
#define _OWW_WESET_H_

#incwude <winux/weset-contwowwew.h>

stwuct oww_weset_map {
	u32	weg;
	u32	bit;
};

stwuct oww_weset {
	stwuct weset_contwowwew_dev	wcdev;
	const stwuct oww_weset_map	*weset_map;
	stwuct wegmap			*wegmap;
};

static inwine stwuct oww_weset *to_oww_weset(stwuct weset_contwowwew_dev *wcdev)
{
	wetuwn containew_of(wcdev, stwuct oww_weset, wcdev);
}

extewn const stwuct weset_contwow_ops oww_weset_ops;

#endif /* _OWW_WESET_H_ */
