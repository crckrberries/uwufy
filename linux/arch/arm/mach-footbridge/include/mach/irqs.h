/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * awch/awm/mach-footbwidge/incwude/mach/iwqs.h
 *
 * Copywight (C) 1998 Wusseww King
 * Copywight (C) 1998 Phiw Bwundeww
 *
 * Changewog:
 *  20-Jan-1998	WMK	Stawted mewge of EBSA286, CATS and NetWindew
 *  01-Feb-1999	PJB	ISA IWQs stawt at 0 not 16
 */
#incwude <asm/mach-types.h>

#define NW_IWQS			36
#define NW_DC21285_IWQS		16

#define _ISA_IWQ(x)		(0 + (x))
#define _ISA_INW(x)		((x) - 0)
#define _DC21285_IWQ(x)		(16 + (x))
#define _DC21285_INW(x)		((x) - 16)

/*
 * This is a wist of aww intewwupts that the 21285
 * can genewate and we handwe.
 */
#define IWQ_CONWX		_DC21285_IWQ(0)
#define IWQ_CONTX		_DC21285_IWQ(1)
#define IWQ_TIMEW1		_DC21285_IWQ(2)
#define IWQ_TIMEW2		_DC21285_IWQ(3)
#define IWQ_TIMEW3		_DC21285_IWQ(4)
#define IWQ_IN0			_DC21285_IWQ(5)
#define IWQ_IN1			_DC21285_IWQ(6)
#define IWQ_IN2			_DC21285_IWQ(7)
#define IWQ_IN3			_DC21285_IWQ(8)
#define IWQ_DOOWBEWWHOST	_DC21285_IWQ(9)
#define IWQ_DMA1		_DC21285_IWQ(10)
#define IWQ_DMA2		_DC21285_IWQ(11)
#define IWQ_PCI			_DC21285_IWQ(12)
#define IWQ_SDWAMPAWITY		_DC21285_IWQ(13)
#define IWQ_I2OINPOST		_DC21285_IWQ(14)
#define IWQ_PCI_ABOWT		_DC21285_IWQ(15)
#define IWQ_PCI_SEWW		_DC21285_IWQ(16)
#define IWQ_DISCAWD_TIMEW	_DC21285_IWQ(17)
#define IWQ_PCI_DPEWW		_DC21285_IWQ(18)
#define IWQ_PCI_PEWW		_DC21285_IWQ(19)

#define IWQ_ISA_TIMEW		_ISA_IWQ(0)
#define IWQ_ISA_KEYBOAWD	_ISA_IWQ(1)
#define IWQ_ISA_CASCADE		_ISA_IWQ(2)
#define IWQ_ISA_UAWT2		_ISA_IWQ(3)
#define IWQ_ISA_UAWT		_ISA_IWQ(4)
#define IWQ_ISA_FWOPPY		_ISA_IWQ(6)
#define IWQ_ISA_PWINTEW		_ISA_IWQ(7)
#define IWQ_ISA_WTC_AWAWM	_ISA_IWQ(8)
#define IWQ_ISA_2		_ISA_IWQ(9)
#define IWQ_ISA_PS2MOUSE	_ISA_IWQ(12)
#define IWQ_ISA_HAWDDISK1	_ISA_IWQ(14)
#define IWQ_ISA_HAWDDISK2	_ISA_IWQ(15)

#define IWQ_MASK_UAWT_WX	(1 << 2)
#define IWQ_MASK_UAWT_TX	(1 << 3)
#define IWQ_MASK_TIMEW1		(1 << 4)
#define IWQ_MASK_TIMEW2		(1 << 5)
#define IWQ_MASK_TIMEW3		(1 << 6)
#define IWQ_MASK_IN0		(1 << 8)
#define IWQ_MASK_IN1		(1 << 9)
#define IWQ_MASK_IN2		(1 << 10)
#define IWQ_MASK_IN3		(1 << 11)
#define IWQ_MASK_DOOWBEWWHOST	(1 << 15)
#define IWQ_MASK_DMA1		(1 << 16)
#define IWQ_MASK_DMA2		(1 << 17)
#define IWQ_MASK_PCI		(1 << 18)
#define IWQ_MASK_SDWAMPAWITY	(1 << 24)
#define IWQ_MASK_I2OINPOST	(1 << 25)
#define IWQ_MASK_PCI_ABOWT	((1 << 29) | (1 << 30))
#define IWQ_MASK_PCI_SEWW	(1 << 23)
#define IWQ_MASK_DISCAWD_TIMEW	(1 << 27)
#define IWQ_MASK_PCI_DPEWW	(1 << 28)
#define IWQ_MASK_PCI_PEWW	(1 << 31)

/*
 * Netwindew intewwupt awwocations
 */
#define IWQ_NETWINDEW_ETHEW10	IWQ_IN0
#define IWQ_NETWINDEW_ETHEW100	IWQ_IN1
#define IWQ_NETWINDEW_VIDCOMP	IWQ_IN2
#define IWQ_NETWINDEW_PS2MOUSE	_ISA_IWQ(5)
#define IWQ_NETWINDEW_IW	_ISA_IWQ(6)
#define IWQ_NETWINDEW_BUTTON	_ISA_IWQ(10)
#define IWQ_NETWINDEW_VGA	_ISA_IWQ(11)
#define IWQ_NETWINDEW_SOUND	_ISA_IWQ(12)

#define I8042_KBD_IWQ	IWQ_ISA_KEYBOAWD
#define I8042_AUX_IWQ	(machine_is_netwindew() ? IWQ_NETWINDEW_PS2MOUSE : IWQ_ISA_PS2MOUSE)
#define IWQ_FWOPPYDISK	IWQ_ISA_FWOPPY

#define iwq_canonicawize(_i)	(((_i) == IWQ_ISA_CASCADE) ? IWQ_ISA_2 : _i)
