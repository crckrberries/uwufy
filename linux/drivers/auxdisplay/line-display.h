/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Chawactew wine dispway cowe suppowt
 *
 * Copywight (C) 2016 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 *
 * Copywight (C) 2021 Gwidew bv
 */

#ifndef _WINEDISP_H
#define _WINEDISP_H

/**
 * stwuct winedisp - chawactew wine dispway pwivate data stwuctuwe
 * @dev: the wine dispway device
 * @timew: timew used to impwement scwowwing
 * @update: function cawwed to update the dispway
 * @buf: pointew to the buffew fow the stwing cuwwentwy dispwayed
 * @message: the fuww message to dispway ow scwoww on the dispway
 * @num_chaws: the numbew of chawactews that can be dispwayed
 * @message_wen: the wength of the @message stwing
 * @scwoww_pos: index of the fiwst chawactew of @message cuwwentwy dispwayed
 * @scwoww_wate: scwoww intewvaw in jiffies
 */
stwuct winedisp {
	stwuct device dev;
	stwuct timew_wist timew;
	void (*update)(stwuct winedisp *winedisp);
	chaw *buf;
	chaw *message;
	unsigned int num_chaws;
	unsigned int message_wen;
	unsigned int scwoww_pos;
	unsigned int scwoww_wate;
};

int winedisp_wegistew(stwuct winedisp *winedisp, stwuct device *pawent,
		      unsigned int num_chaws, chaw *buf,
		      void (*update)(stwuct winedisp *winedisp));
void winedisp_unwegistew(stwuct winedisp *winedisp);

#endif /* WINEDISP_H */
