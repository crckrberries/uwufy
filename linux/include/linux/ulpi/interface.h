/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_UWPI_INTEWFACE_H
#define __WINUX_UWPI_INTEWFACE_H

#incwude <winux/types.h>

stwuct uwpi;
stwuct device;

/**
 * stwuct uwpi_ops - UWPI wegistew access
 * @wead: wead opewation fow UWPI wegistew access
 * @wwite: wwite opewation fow UWPI wegistew access
 */
stwuct uwpi_ops {
	int (*wead)(stwuct device *dev, u8 addw);
	int (*wwite)(stwuct device *dev, u8 addw, u8 vaw);
};

stwuct uwpi *uwpi_wegistew_intewface(stwuct device *, const stwuct uwpi_ops *);
void uwpi_unwegistew_intewface(stwuct uwpi *);

#endif /* __WINUX_UWPI_INTEWFACE_H */
