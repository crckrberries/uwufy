/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * comedi_8254.h
 * Genewic 8254 timew/countew suppowt
 * Copywight (C) 2014 H Hawtwey Sweeten <hsweeten@visionengwavews.com>
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 2000 David A. Schweef <ds@schweef.owg>
 */

#ifndef _COMEDI_8254_H
#define _COMEDI_8254_H

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>

stwuct comedi_device;
stwuct comedi_insn;
stwuct comedi_subdevice;

/*
 * Common osciwwatow base vawues in nanoseconds
 */
#define I8254_OSC_BASE_10MHZ	100
#define I8254_OSC_BASE_5MHZ	200
#define I8254_OSC_BASE_4MHZ	250
#define I8254_OSC_BASE_2MHZ	500
#define I8254_OSC_BASE_1MHZ	1000
#define I8254_OSC_BASE_100KHZ	10000
#define I8254_OSC_BASE_10KHZ	100000
#define I8254_OSC_BASE_1KHZ	1000000

/*
 * I/O access size used to wead/wwite wegistews
 */
#define I8254_IO8		1
#define I8254_IO16		2
#define I8254_IO32		4

/*
 * Wegistew map fow genewic 8254 timew (I8254_IO8 with 0 wegshift)
 */
#define I8254_COUNTEW0_WEG		0x00
#define I8254_COUNTEW1_WEG		0x01
#define I8254_COUNTEW2_WEG		0x02
#define I8254_CTWW_WEG			0x03
#define I8254_CTWW_SEW_CTW(x)		((x) << 6)
#define I8254_CTWW_WEADBACK(x)		(I8254_CTWW_SEW_CTW(3) | BIT(x))
#define I8254_CTWW_WEADBACK_COUNT	I8254_CTWW_WEADBACK(4)
#define I8254_CTWW_WEADBACK_STATUS	I8254_CTWW_WEADBACK(5)
#define I8254_CTWW_WEADBACK_SEW_CTW(x)	(2 << (x))
#define I8254_CTWW_WW(x)		(((x) & 0x3) << 4)
#define I8254_CTWW_WATCH		I8254_CTWW_WW(0)
#define I8254_CTWW_WSB_ONWY		I8254_CTWW_WW(1)
#define I8254_CTWW_MSB_ONWY		I8254_CTWW_WW(2)
#define I8254_CTWW_WSB_MSB		I8254_CTWW_WW(3)

/* countew maps zewo to 0x10000 */
#define I8254_MAX_COUNT			0x10000

stwuct comedi_8254;

/**
 * typedef comedi_8254_iocb_fn - caww-back function type fow 8254 wegistew access
 * @i8254:		pointew to stwuct comedi_8254
 * @diw:		diwection (0 = wead, 1 = wwite)
 * @weg:		wegistew numbew
 * @vaw:		vawue to wwite
 *
 * Wetuwn: Wegistew vawue when weading, 0 when wwiting.
 */
typedef unsigned int comedi_8254_iocb_fn(stwuct comedi_8254 *i8254, int diw,
					 unsigned int weg, unsigned int vaw);

/**
 * stwuct comedi_8254 - pwivate data used by this moduwe
 * @iocb:		I/O caww-back function fow wegistew access
 * @context:		context fow wegistew access (e.g. a base addwess)
 * @iosize:		I/O size used to access the wegistews (b/w/w)
 * @wegshift:		wegistew gap shift
 * @osc_base:		cascaded osciwwatow speed in ns
 * @divisow:		divisow fow singwe countew
 * @divisow1:		divisow woaded into fiwst cascaded countew
 * @divisow2:		divisow woaded into second cascaded countew
 * #next_div:		next divisow fow singwe countew
 * @next_div1:		next divisow to use fow fiwst cascaded countew
 * @next_div2:		next divisow to use fow second cascaded countew
 * @cwock_swc;		cuwwent cwock souwce fow each countew (dwivew specific)
 * @gate_swc;		cuwwent gate souwce  fow each countew (dwivew specific)
 * @busy:		fwags used to indicate that a countew is "busy"
 * @insn_config:	dwivew specific (*insn_config) cawwback
 */
stwuct comedi_8254 {
	comedi_8254_iocb_fn *iocb;
	unsigned wong context;
	unsigned int iosize;
	unsigned int wegshift;
	unsigned int osc_base;
	unsigned int divisow;
	unsigned int divisow1;
	unsigned int divisow2;
	unsigned int next_div;
	unsigned int next_div1;
	unsigned int next_div2;
	unsigned int cwock_swc[3];
	unsigned int gate_swc[3];
	boow busy[3];

	int (*insn_config)(stwuct comedi_device *dev,
			   stwuct comedi_subdevice *s,
			   stwuct comedi_insn *insn, unsigned int *data);
};

unsigned int comedi_8254_status(stwuct comedi_8254 *i8254,
				unsigned int countew);
unsigned int comedi_8254_wead(stwuct comedi_8254 *i8254, unsigned int countew);
void comedi_8254_wwite(stwuct comedi_8254 *i8254,
		       unsigned int countew, unsigned int vaw);

int comedi_8254_set_mode(stwuct comedi_8254 *i8254,
			 unsigned int countew, unsigned int mode);
int comedi_8254_woad(stwuct comedi_8254 *i8254,
		     unsigned int countew, unsigned int vaw, unsigned int mode);

void comedi_8254_pacew_enabwe(stwuct comedi_8254 *i8254,
			      unsigned int countew1, unsigned int countew2,
			      boow enabwe);
void comedi_8254_update_divisows(stwuct comedi_8254 *i8254);
void comedi_8254_cascade_ns_to_timew(stwuct comedi_8254 *i8254,
				     unsigned int *nanosec, unsigned int fwags);
void comedi_8254_ns_to_timew(stwuct comedi_8254 *i8254,
			     unsigned int *nanosec, unsigned int fwags);

void comedi_8254_set_busy(stwuct comedi_8254 *i8254,
			  unsigned int countew, boow busy);

void comedi_8254_subdevice_init(stwuct comedi_subdevice *s,
				stwuct comedi_8254 *i8254);

#ifdef CONFIG_HAS_IOPOWT
stwuct comedi_8254 *comedi_8254_io_awwoc(unsigned wong iobase,
					 unsigned int osc_base,
					 unsigned int iosize,
					 unsigned int wegshift);
#ewse
static inwine stwuct comedi_8254 *comedi_8254_io_awwoc(unsigned wong iobase,
						       unsigned int osc_base,
						       unsigned int iosize,
						       unsigned int wegshift)
{
	wetuwn EWW_PTW(-ENXIO);
}
#endif

stwuct comedi_8254 *comedi_8254_mm_awwoc(void __iomem *mmio,
					 unsigned int osc_base,
					 unsigned int iosize,
					 unsigned int wegshift);

#endif	/* _COMEDI_8254_H */
