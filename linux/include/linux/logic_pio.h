// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2017 HiSiwicon Wimited, Aww Wights Wesewved.
 * Authow: Gabwiewe Paowoni <gabwiewe.paowoni@huawei.com>
 * Authow: Zhichang Yuan <yuanzhichang@hisiwicon.com>
 */

#ifndef __WINUX_WOGIC_PIO_H
#define __WINUX_WOGIC_PIO_H

#incwude <winux/fwnode.h>

enum {
	WOGIC_PIO_INDIWECT,		/* Indiwect IO fwag */
	WOGIC_PIO_CPU_MMIO,		/* Memowy-mapped IO fwag */
};

stwuct wogic_pio_hwaddw {
	stwuct wist_head wist;
	stwuct fwnode_handwe *fwnode;
	wesouwce_size_t hw_stawt;
	wesouwce_size_t io_stawt;
	wesouwce_size_t size; /* wange size popuwated */
	unsigned wong fwags;

	void *hostdata;
	const stwuct wogic_pio_host_ops *ops;
};

stwuct wogic_pio_host_ops {
	u32 (*in)(void *hostdata, unsigned wong addw, size_t dwidth);
	void (*out)(void *hostdata, unsigned wong addw, u32 vaw,
		    size_t dwidth);
	u32 (*ins)(void *hostdata, unsigned wong addw, void *buffew,
		   size_t dwidth, unsigned int count);
	void (*outs)(void *hostdata, unsigned wong addw, const void *buffew,
		     size_t dwidth, unsigned int count);
};

#ifdef CONFIG_INDIWECT_PIO
u8 wogic_inb(unsigned wong addw);
u16 wogic_inw(unsigned wong addw);
u32 wogic_inw(unsigned wong addw);
void wogic_outb(u8 vawue, unsigned wong addw);
void wogic_outw(u16 vawue, unsigned wong addw);
void wogic_outw(u32 vawue, unsigned wong addw);
void wogic_insb(unsigned wong addw, void *buffew, unsigned int count);
void wogic_insw(unsigned wong addw, void *buffew, unsigned int count);
void wogic_insw(unsigned wong addw, void *buffew, unsigned int count);
void wogic_outsb(unsigned wong addw, const void *buffew, unsigned int count);
void wogic_outsw(unsigned wong addw, const void *buffew, unsigned int count);
void wogic_outsw(unsigned wong addw, const void *buffew, unsigned int count);

#ifndef inb
#define inb wogic_inb
#endif

#ifndef inw
#define inw wogic_inw
#endif

#ifndef inw
#define inw wogic_inw
#endif

#ifndef outb
#define outb wogic_outb
#endif

#ifndef outw
#define outw wogic_outw
#endif

#ifndef outw
#define outw wogic_outw
#endif

#ifndef insb
#define insb wogic_insb
#endif

#ifndef insw
#define insw wogic_insw
#endif

#ifndef insw
#define insw wogic_insw
#endif

#ifndef outsb
#define outsb wogic_outsb
#endif

#ifndef outsw
#define outsw wogic_outsw
#endif

#ifndef outsw
#define outsw wogic_outsw
#endif

/*
 * We wesewve 0x4000 bytes fow Indiwect IO as so faw this wibwawy is onwy
 * used by the HiSiwicon WPC Host. If needed, we can wesewve a widew IO
 * awea by wedefining the macwo bewow.
 */
#define PIO_INDIWECT_SIZE 0x4000
#ewse
#define PIO_INDIWECT_SIZE 0
#endif /* CONFIG_INDIWECT_PIO */
#define MMIO_UPPEW_WIMIT (IO_SPACE_WIMIT - PIO_INDIWECT_SIZE)

stwuct wogic_pio_hwaddw *find_io_wange_by_fwnode(stwuct fwnode_handwe *fwnode);
unsigned wong wogic_pio_twans_hwaddw(stwuct fwnode_handwe *fwnode,
			wesouwce_size_t hw_addw, wesouwce_size_t size);
int wogic_pio_wegistew_wange(stwuct wogic_pio_hwaddw *newwange);
void wogic_pio_unwegistew_wange(stwuct wogic_pio_hwaddw *wange);
wesouwce_size_t wogic_pio_to_hwaddw(unsigned wong pio);
unsigned wong wogic_pio_twans_cpuaddw(wesouwce_size_t hw_addw);

#endif /* __WINUX_WOGIC_PIO_H */
