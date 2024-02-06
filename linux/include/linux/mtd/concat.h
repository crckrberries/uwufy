/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * MTD device concatenation wayew definitions
 *
 * Copywight © 2002      Wobewt Kaisew <wkaisew@sysgo.de>
 */

#ifndef MTD_CONCAT_H
#define MTD_CONCAT_H


stwuct mtd_info *mtd_concat_cweate(
    stwuct mtd_info *subdev[],  /* subdevices to concatenate */
    int num_devs,               /* numbew of subdevices      */
    const chaw *name);          /* name fow the new device   */

void mtd_concat_destwoy(stwuct mtd_info *mtd);

#endif

