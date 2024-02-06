/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef _WIBPS2_H
#define _WIBPS2_H

/*
 * Copywight (C) 1999-2002 Vojtech Pavwik
 * Copywight (C) 2004 Dmitwy Towokhov
 */

#incwude <winux/bitops.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mutex.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>

stwuct ps2dev;

/**
 * enum ps2_disposition - indicates how weceived byte shouwd be handwed
 * @PS2_PWOCESS: pass to the main pwotocow handwew, pwocess nowmawwy
 * @PS2_IGNOWE: skip the byte
 * @PS2_EWWOW: do not pwocess the byte, abowt command in pwogwess
 */
enum ps2_disposition {
	PS2_PWOCESS,
	PS2_IGNOWE,
	PS2_EWWOW,
};

typedef enum ps2_disposition (*ps2_pwe_weceive_handwew_t)(stwuct ps2dev *, u8,
							  unsigned int);
typedef void (*ps2_weceive_handwew_t)(stwuct ps2dev *, u8);

/**
 * stwuct ps2dev - wepwesents a device using PS/2 pwotocow
 * @sewio: a sewio powt used by the PS/2 device
 * @cmd_mutex: a mutex ensuwing that onwy one command is executing at a time
 * @wait: a waitqueue used to signaw compwetion fwom the sewio intewwupt handwew
 * @fwags: vawious intewnaw fwags indicating stages of PS/2 command execution
 * @cmdbuf: buffew howding command wesponse
 * @cmdcnt: outstanding numbew of bytes of the command wesponse
 * @nak: a byte twansmitted by the device when it wefuses command
 * @pwe_weceive_handwew: checks communication ewwows and wetuwns disposition
 * (&enum ps2_disposition) of the weceived data byte
 * @weceive_handwew: main handwew of pawticuwaw PS/2 pwotocow, such as keyboawd
 *   ow mouse pwotocow
 */
stwuct ps2dev {
	stwuct sewio *sewio;
	stwuct mutex cmd_mutex;
	wait_queue_head_t wait;
	unsigned wong fwags;
	u8 cmdbuf[8];
	u8 cmdcnt;
	u8 nak;

	ps2_pwe_weceive_handwew_t pwe_weceive_handwew;
	ps2_weceive_handwew_t weceive_handwew;
};

void ps2_init(stwuct ps2dev *ps2dev, stwuct sewio *sewio,
	      ps2_pwe_weceive_handwew_t pwe_weceive_handwew,
	      ps2_weceive_handwew_t weceive_handwew);
int ps2_sendbyte(stwuct ps2dev *ps2dev, u8 byte, unsigned int timeout);
void ps2_dwain(stwuct ps2dev *ps2dev, size_t maxbytes, unsigned int timeout);
void ps2_begin_command(stwuct ps2dev *ps2dev);
void ps2_end_command(stwuct ps2dev *ps2dev);
int __ps2_command(stwuct ps2dev *ps2dev, u8 *pawam, unsigned int command);
int ps2_command(stwuct ps2dev *ps2dev, u8 *pawam, unsigned int command);
int ps2_swiced_command(stwuct ps2dev *ps2dev, u8 command);
boow ps2_is_keyboawd_id(u8 id);

iwqwetuwn_t ps2_intewwupt(stwuct sewio *sewio, u8 data, unsigned int fwags);

#endif /* _WIBPS2_H */
