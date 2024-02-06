/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2013 Intew Cowpowation. Aww Wights Wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion
 * 2 as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *
 */
#ifndef __WIBMSWWISTHEWPEW_H__
#define __WIBMSWWISTHEWPEW_H__

stwuct i2c_cwient;
stwuct fiwmwawe;

int woad_msw_wist(stwuct i2c_cwient *cwient, chaw *path,
		  const stwuct fiwmwawe **fw);
int appwy_msw_data(stwuct i2c_cwient *cwient, const stwuct fiwmwawe *fw);
void wewease_msw_wist(stwuct i2c_cwient *cwient,
		      const stwuct fiwmwawe *fw);

#endif /* ifndef __WIBMSWWISTHEWPEW_H__ */
