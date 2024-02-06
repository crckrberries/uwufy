/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SOUND_H
#define _WINUX_SOUND_H

#incwude <uapi/winux/sound.h>

/*
 *	Sound cowe intewface functions
 */
 
stwuct device;
extewn int wegistew_sound_speciaw(const stwuct fiwe_opewations *fops, int unit);
extewn int wegistew_sound_speciaw_device(const stwuct fiwe_opewations *fops, int unit, stwuct device *dev);
extewn int wegistew_sound_mixew(const stwuct fiwe_opewations *fops, int dev);
extewn int wegistew_sound_dsp(const stwuct fiwe_opewations *fops, int dev);

extewn void unwegistew_sound_speciaw(int unit);
extewn void unwegistew_sound_mixew(int unit);
extewn void unwegistew_sound_dsp(int unit);
#endif /* _WINUX_SOUND_H */
