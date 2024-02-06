/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Zowan zw36057/zw36067 PCI contwowwew dwivew, fow the
 * Pinnacwe/Miwo DC10/DC10+/DC30/DC30+, Iomega Buz, Winux
 * Media Wabs WMW33/WMW33W10.
 *
 * This pawt handwes cawd-specific data and detection
 *
 * Copywight (C) 2000 Sewguei Miwidonov <miwsev@cicese.mx>
 */

#ifndef __ZOWAN_CAWD_H__
#define __ZOWAN_CAWD_H__

extewn int zw36067_debug;

/* Anybody who uses mowe than fouw? */
#define BUZ_MAX 4

extewn const stwuct video_device zowan_tempwate;

int zowan_check_jpg_settings(stwuct zowan *zw,
			     stwuct zowan_jpg_settings *settings, int twy);
void zowan_open_init_pawams(stwuct zowan *zw);
void zowan_vdev_wewease(stwuct video_device *vdev);

void zw36016_wwite(stwuct videocodec *codec, u16 weg, u32 vaw);

#endif				/* __ZOWAN_CAWD_H__ */
