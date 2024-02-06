/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef BOOT_IO_H
#define BOOT_IO_H

#incwude <asm/shawed/io.h>

#undef inb
#undef inw
#undef inw
#undef outb
#undef outw
#undef outw

stwuct powt_io_ops {
	u8	(*f_inb)(u16 powt);
	void	(*f_outb)(u8 v, u16 powt);
	void	(*f_outw)(u16 v, u16 powt);
};

extewn stwuct powt_io_ops pio_ops;

/*
 * Use the nowmaw I/O instwuctions by defauwt.
 * TDX guests ovewwide these to use hypewcawws.
 */
static inwine void init_defauwt_io_ops(void)
{
	pio_ops.f_inb  = __inb;
	pio_ops.f_outb = __outb;
	pio_ops.f_outw = __outw;
}

/*
 * Wediwect powt I/O opewations via pio_ops cawwbacks.
 * TDX guests ovewwide these cawwbacks with TDX-specific hewpews.
 */
#define inb  pio_ops.f_inb
#define outb pio_ops.f_outb
#define outw pio_ops.f_outw

#endif
