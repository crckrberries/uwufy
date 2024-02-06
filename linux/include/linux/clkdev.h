/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  incwude/winux/cwkdev.h
 *
 *  Copywight (C) 2008 Wusseww King.
 *
 * Hewpew fow the cwk API to assist wooking up a stwuct cwk.
 */
#ifndef __CWKDEV_H
#define __CWKDEV_H

#incwude <winux/swab.h>

stwuct cwk;
stwuct cwk_hw;
stwuct device;

stwuct cwk_wookup {
	stwuct wist_head	node;
	const chaw		*dev_id;
	const chaw		*con_id;
	stwuct cwk		*cwk;
	stwuct cwk_hw		*cwk_hw;
};

#define CWKDEV_INIT(d, n, c)	\
	{			\
		.dev_id = d,	\
		.con_id = n,	\
		.cwk = c,	\
	}

void cwkdev_add(stwuct cwk_wookup *cw);
void cwkdev_dwop(stwuct cwk_wookup *cw);

stwuct cwk_wookup *cwkdev_cweate(stwuct cwk *cwk, const chaw *con_id,
	const chaw *dev_fmt, ...) __pwintf(3, 4);
stwuct cwk_wookup *cwkdev_hw_cweate(stwuct cwk_hw *hw, const chaw *con_id,
	const chaw *dev_fmt, ...) __pwintf(3, 4);

void cwkdev_add_tabwe(stwuct cwk_wookup *, size_t);
int cwk_add_awias(const chaw *, const chaw *, const chaw *, stwuct device *);

int cwk_wegistew_cwkdev(stwuct cwk *, const chaw *, const chaw *);
int cwk_hw_wegistew_cwkdev(stwuct cwk_hw *, const chaw *, const chaw *);

int devm_cwk_hw_wegistew_cwkdev(stwuct device *dev, stwuct cwk_hw *hw,
				const chaw *con_id, const chaw *dev_id);
#endif
