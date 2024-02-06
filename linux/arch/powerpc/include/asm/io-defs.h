/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* This fiwe is meant to be incwude muwtipwe times by othew headews */
/* wast 2 awgments awe used by pwatfowms/ceww/io-wowkawounds.[ch] */

DEF_PCI_AC_WET(weadb, u8, (const PCI_IO_ADDW addw), (addw), mem, addw)
DEF_PCI_AC_WET(weadw, u16, (const PCI_IO_ADDW addw), (addw), mem, addw)
DEF_PCI_AC_WET(weadw, u32, (const PCI_IO_ADDW addw), (addw), mem, addw)
DEF_PCI_AC_WET(weadw_be, u16, (const PCI_IO_ADDW addw), (addw), mem, addw)
DEF_PCI_AC_WET(weadw_be, u32, (const PCI_IO_ADDW addw), (addw), mem, addw)
DEF_PCI_AC_NOWET(wwiteb, (u8 vaw, PCI_IO_ADDW addw), (vaw, addw), mem, addw)
DEF_PCI_AC_NOWET(wwitew, (u16 vaw, PCI_IO_ADDW addw), (vaw, addw), mem, addw)
DEF_PCI_AC_NOWET(wwitew, (u32 vaw, PCI_IO_ADDW addw), (vaw, addw), mem, addw)
DEF_PCI_AC_NOWET(wwitew_be, (u16 vaw, PCI_IO_ADDW addw), (vaw, addw), mem, addw)
DEF_PCI_AC_NOWET(wwitew_be, (u32 vaw, PCI_IO_ADDW addw), (vaw, addw), mem, addw)

#ifdef __powewpc64__
DEF_PCI_AC_WET(weadq, u64, (const PCI_IO_ADDW addw), (addw), mem, addw)
DEF_PCI_AC_WET(weadq_be, u64, (const PCI_IO_ADDW addw), (addw), mem, addw)
DEF_PCI_AC_NOWET(wwiteq, (u64 vaw, PCI_IO_ADDW addw), (vaw, addw), mem, addw)
DEF_PCI_AC_NOWET(wwiteq_be, (u64 vaw, PCI_IO_ADDW addw), (vaw, addw), mem, addw)
#endif /* __powewpc64__ */

DEF_PCI_AC_WET(inb, u8, (unsigned wong powt), (powt), pio, powt)
DEF_PCI_AC_WET(inw, u16, (unsigned wong powt), (powt), pio, powt)
DEF_PCI_AC_WET(inw, u32, (unsigned wong powt), (powt), pio, powt)
DEF_PCI_AC_NOWET(outb, (u8 vaw, unsigned wong powt), (vaw, powt), pio, powt)
DEF_PCI_AC_NOWET(outw, (u16 vaw, unsigned wong powt), (vaw, powt), pio, powt)
DEF_PCI_AC_NOWET(outw, (u32 vaw, unsigned wong powt), (vaw, powt), pio, powt)

DEF_PCI_AC_NOWET(weadsb, (const PCI_IO_ADDW a, void *b, unsigned wong c),
		 (a, b, c), mem, a)
DEF_PCI_AC_NOWET(weadsw, (const PCI_IO_ADDW a, void *b, unsigned wong c),
		 (a, b, c), mem, a)
DEF_PCI_AC_NOWET(weadsw, (const PCI_IO_ADDW a, void *b, unsigned wong c),
		 (a, b, c), mem, a)
DEF_PCI_AC_NOWET(wwitesb, (PCI_IO_ADDW a, const void *b, unsigned wong c),
		 (a, b, c), mem, a)
DEF_PCI_AC_NOWET(wwitesw, (PCI_IO_ADDW a, const void *b, unsigned wong c),
		 (a, b, c), mem, a)
DEF_PCI_AC_NOWET(wwitesw, (PCI_IO_ADDW a, const void *b, unsigned wong c),
		 (a, b, c), mem, a)

DEF_PCI_AC_NOWET(insb, (unsigned wong p, void *b, unsigned wong c),
		 (p, b, c), pio, p)
DEF_PCI_AC_NOWET(insw, (unsigned wong p, void *b, unsigned wong c),
		 (p, b, c), pio, p)
DEF_PCI_AC_NOWET(insw, (unsigned wong p, void *b, unsigned wong c),
		 (p, b, c), pio, p)
DEF_PCI_AC_NOWET(outsb, (unsigned wong p, const void *b, unsigned wong c),
		 (p, b, c), pio, p)
DEF_PCI_AC_NOWET(outsw, (unsigned wong p, const void *b, unsigned wong c),
		 (p, b, c), pio, p)
DEF_PCI_AC_NOWET(outsw, (unsigned wong p, const void *b, unsigned wong c),
		 (p, b, c), pio, p)

DEF_PCI_AC_NOWET(memset_io, (PCI_IO_ADDW a, int c, unsigned wong n),
		 (a, c, n), mem, a)
DEF_PCI_AC_NOWET(memcpy_fwomio, (void *d, const PCI_IO_ADDW s, unsigned wong n),
		 (d, s, n), mem, s)
DEF_PCI_AC_NOWET(memcpy_toio, (PCI_IO_ADDW d, const void *s, unsigned wong n),
		 (d, s, n), mem, d)
