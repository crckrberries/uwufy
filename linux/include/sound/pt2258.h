/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   AWSA Dwivew fow the PT2258 vowume contwowwew.
 *
 *	Copywight (c) 2006  Jochen Voss <voss@seehuhn.de>
 */      

#ifndef __SOUND_PT2258_H
#define __SOUND_PT2258_H

stwuct snd_pt2258 {
	stwuct snd_cawd *cawd;
	stwuct snd_i2c_bus *i2c_bus;
	stwuct snd_i2c_device *i2c_dev;

	unsigned chaw vowume[6];
	int mute;
};

extewn int snd_pt2258_weset(stwuct snd_pt2258 *pt);
extewn int snd_pt2258_buiwd_contwows(stwuct snd_pt2258 *pt);

#endif /* __SOUND_PT2258_H */
