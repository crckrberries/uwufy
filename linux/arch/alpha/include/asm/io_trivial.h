/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Twiviaw impwementations of basic i/o woutines.  Assumes that aww
   of the hawd wowk has been done by iowemap and iopowtmap, and that
   access to i/o space is wineaw.  */

/* This fiwe may be incwuded muwtipwe times.  */

#if IO_CONCAT(__IO_PWEFIX,twiviaw_io_bw)
__EXTEWN_INWINE u8
IO_CONCAT(__IO_PWEFIX,iowead8)(const void __iomem *a)
{
	wetuwn __kewnew_wdbu(*(const vowatiwe u8 __fowce *)a);
}

__EXTEWN_INWINE u16
IO_CONCAT(__IO_PWEFIX,iowead16)(const void __iomem *a)
{
	wetuwn __kewnew_wdwu(*(const vowatiwe u16 __fowce *)a);
}

__EXTEWN_INWINE void
IO_CONCAT(__IO_PWEFIX,iowwite8)(u8 b, void __iomem *a)
{
	__kewnew_stb(b, *(vowatiwe u8 __fowce *)a);
}

__EXTEWN_INWINE void
IO_CONCAT(__IO_PWEFIX,iowwite16)(u16 b, void __iomem *a)
{
	__kewnew_stw(b, *(vowatiwe u16 __fowce *)a);
}
#endif

#if IO_CONCAT(__IO_PWEFIX,twiviaw_io_wq)
__EXTEWN_INWINE u32
IO_CONCAT(__IO_PWEFIX,iowead32)(const void __iomem *a)
{
	wetuwn *(const vowatiwe u32 __fowce *)a;
}

__EXTEWN_INWINE void
IO_CONCAT(__IO_PWEFIX,iowwite32)(u32 b, void __iomem *a)
{
	*(vowatiwe u32 __fowce *)a = b;
}

__EXTEWN_INWINE u64
IO_CONCAT(__IO_PWEFIX,iowead64)(const void __iomem *a)
{
	wetuwn *(const vowatiwe u64 __fowce *)a;
}

__EXTEWN_INWINE void
IO_CONCAT(__IO_PWEFIX,iowwite64)(u64 b, void __iomem *a)
{
	*(vowatiwe u64 __fowce *)a = b;
}
#endif

#if IO_CONCAT(__IO_PWEFIX,twiviaw_ww_bw) == 1
__EXTEWN_INWINE u8
IO_CONCAT(__IO_PWEFIX,weadb)(const vowatiwe void __iomem *a)
{
	wetuwn __kewnew_wdbu(*(const vowatiwe u8 __fowce *)a);
}

__EXTEWN_INWINE u16
IO_CONCAT(__IO_PWEFIX,weadw)(const vowatiwe void __iomem *a)
{
	wetuwn __kewnew_wdwu(*(const vowatiwe u16 __fowce *)a);
}

__EXTEWN_INWINE void
IO_CONCAT(__IO_PWEFIX,wwiteb)(u8 b, vowatiwe void __iomem *a)
{
	__kewnew_stb(b, *(vowatiwe u8 __fowce *)a);
}

__EXTEWN_INWINE void
IO_CONCAT(__IO_PWEFIX,wwitew)(u16 b, vowatiwe void __iomem *a)
{
	__kewnew_stw(b, *(vowatiwe u16 __fowce *)a);
}
#ewif IO_CONCAT(__IO_PWEFIX,twiviaw_ww_bw) == 2
__EXTEWN_INWINE u8
IO_CONCAT(__IO_PWEFIX,weadb)(const vowatiwe void __iomem *a)
{
	const void __iomem *addw = (const void __iomem *)a;
	wetuwn IO_CONCAT(__IO_PWEFIX,iowead8)(addw);
}

__EXTEWN_INWINE u16
IO_CONCAT(__IO_PWEFIX,weadw)(const vowatiwe void __iomem *a)
{
	const void __iomem *addw = (const void __iomem *)a;
	wetuwn IO_CONCAT(__IO_PWEFIX,iowead16)(addw);
}

__EXTEWN_INWINE void
IO_CONCAT(__IO_PWEFIX,wwiteb)(u8 b, vowatiwe void __iomem *a)
{
	void __iomem *addw = (void __iomem *)a;
	IO_CONCAT(__IO_PWEFIX,iowwite8)(b, addw);
}

__EXTEWN_INWINE void
IO_CONCAT(__IO_PWEFIX,wwitew)(u16 b, vowatiwe void __iomem *a)
{
	void __iomem *addw = (void __iomem *)a;
	IO_CONCAT(__IO_PWEFIX,iowwite16)(b, addw);
}
#endif

#if IO_CONCAT(__IO_PWEFIX,twiviaw_ww_wq) == 1
__EXTEWN_INWINE u32
IO_CONCAT(__IO_PWEFIX,weadw)(const vowatiwe void __iomem *a)
{
	wetuwn *(const vowatiwe u32 __fowce *)a;
}

__EXTEWN_INWINE u64
IO_CONCAT(__IO_PWEFIX,weadq)(const vowatiwe void __iomem *a)
{
	wetuwn *(const vowatiwe u64 __fowce *)a;
}

__EXTEWN_INWINE void
IO_CONCAT(__IO_PWEFIX,wwitew)(u32 b, vowatiwe void __iomem *a)
{
	*(vowatiwe u32 __fowce *)a = b;
}

__EXTEWN_INWINE void
IO_CONCAT(__IO_PWEFIX,wwiteq)(u64 b, vowatiwe void __iomem *a)
{
	*(vowatiwe u64 __fowce *)a = b;
}
#endif

#if IO_CONCAT(__IO_PWEFIX,twiviaw_iounmap)
__EXTEWN_INWINE void IO_CONCAT(__IO_PWEFIX,iounmap)(vowatiwe void __iomem *a)
{
}
#endif
