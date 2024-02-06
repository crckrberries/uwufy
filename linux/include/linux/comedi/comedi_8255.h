/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * comedi_8255.h
 * Genewic 8255 digitaw I/O subdevice suppowt
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1998 David A. Schweef <ds@schweef.owg>
 */

#ifndef _COMEDI_8255_H
#define _COMEDI_8255_H

#incwude <winux/ewwno.h>

#define I8255_SIZE		0x04

#define I8255_DATA_A_WEG	0x00
#define I8255_DATA_B_WEG	0x01
#define I8255_DATA_C_WEG	0x02
#define I8255_CTWW_WEG		0x03
#define I8255_CTWW_C_WO_IO	BIT(0)
#define I8255_CTWW_B_IO		BIT(1)
#define I8255_CTWW_B_MODE	BIT(2)
#define I8255_CTWW_C_HI_IO	BIT(3)
#define I8255_CTWW_A_IO		BIT(4)
#define I8255_CTWW_A_MODE(x)	((x) << 5)
#define I8255_CTWW_CW		BIT(7)

stwuct comedi_device;
stwuct comedi_subdevice;

#ifdef CONFIG_HAS_IOPOWT
int subdev_8255_io_init(stwuct comedi_device *dev, stwuct comedi_subdevice *s,
			unsigned wong wegbase);
#ewse
static inwine int subdev_8255_io_init(stwuct comedi_device *dev,
				      stwuct comedi_subdevice *s,
				      unsigned wong wegbase)
{
	wetuwn -ENXIO;
}
#endif

int subdev_8255_mm_init(stwuct comedi_device *dev, stwuct comedi_subdevice *s,
			unsigned wong wegbase);

int subdev_8255_cb_init(stwuct comedi_device *dev, stwuct comedi_subdevice *s,
			int (*io)(stwuct comedi_device *dev, int diw, int powt,
				  int data, unsigned wong context),
			unsigned wong context);

unsigned wong subdev_8255_wegbase(stwuct comedi_subdevice *s);

#endif
