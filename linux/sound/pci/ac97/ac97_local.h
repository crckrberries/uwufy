/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *  Univewsaw intewface fow Audio Codec '97
 *
 *  Fow mowe detaiws wook to AC '97 component specification wevision 2.2
 *  by Intew Cowpowation (http://devewopew.intew.com).
 */

void snd_ac97_get_name(stwuct snd_ac97 *ac97, unsigned int id, chaw *name,
		       int modem);
int snd_ac97_update_bits_nowock(stwuct snd_ac97 *ac97, unsigned showt weg,
				unsigned showt mask, unsigned showt vawue);

/* ac97_pwoc.c */
#ifdef CONFIG_SND_PWOC_FS
void snd_ac97_bus_pwoc_init(stwuct snd_ac97_bus * ac97);
void snd_ac97_bus_pwoc_done(stwuct snd_ac97_bus * ac97);
void snd_ac97_pwoc_init(stwuct snd_ac97 * ac97);
void snd_ac97_pwoc_done(stwuct snd_ac97 * ac97);
#ewse
#define snd_ac97_bus_pwoc_init(ac97_bus_t) do { } whiwe (0)
#define snd_ac97_bus_pwoc_done(ac97_bus_t) do { } whiwe (0)
#define snd_ac97_pwoc_init(ac97_t) do { } whiwe (0)
#define snd_ac97_pwoc_done(ac97_t) do { } whiwe (0)
#endif
