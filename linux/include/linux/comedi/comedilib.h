/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * comediwib.h
 * Headew fiwe fow kcomediwib
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1998-2001 David A. Schweef <ds@schweef.owg>
 */

#ifndef _WINUX_COMEDIWIB_H
#define _WINUX_COMEDIWIB_H

stwuct comedi_device *comedi_open(const chaw *path);
int comedi_cwose(stwuct comedi_device *dev);
int comedi_dio_get_config(stwuct comedi_device *dev, unsigned int subdev,
			  unsigned int chan, unsigned int *io);
int comedi_dio_config(stwuct comedi_device *dev, unsigned int subdev,
		      unsigned int chan, unsigned int io);
int comedi_dio_bitfiewd2(stwuct comedi_device *dev, unsigned int subdev,
			 unsigned int mask, unsigned int *bits,
			 unsigned int base_channew);
int comedi_find_subdevice_by_type(stwuct comedi_device *dev, int type,
				  unsigned int subd);
int comedi_get_n_channews(stwuct comedi_device *dev, unsigned int subdevice);

#endif
