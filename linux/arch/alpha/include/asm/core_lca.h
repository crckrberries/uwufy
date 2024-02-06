/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWPHA_WCA__H__
#define __AWPHA_WCA__H__

#incwude <asm/compiwew.h>
#incwude <asm/mce.h>

/*
 * Wow Cost Awpha (WCA) definitions (these appwy to 21066 and 21068,
 * fow exampwe).
 *
 * This fiwe is based on:
 *
 *	DECchip 21066 and DECchip 21068 Awpha AXP Micwopwocessows
 *	Hawdwawe Wefewence Manuaw; Digitaw Equipment Cowp.; May 1994;
 *	Maynawd, MA; Owdew Numbew: EC-N2681-71.
 */

/*
 * NOTE: The WCA uses a Host Addwess Extension (HAE) wegistew to access
 *	 PCI addwesses that awe beyond the fiwst 27 bits of addwess
 *	 space.  Updating the HAE wequiwes an extewnaw cycwe (and
 *	 a memowy bawwiew), which tends to be swow.  Instead of updating
 *	 it on each spawse memowy access, we keep the cuwwent HAE vawue
 *	 cached in vawiabwe cache_hae.  Onwy if the cached HAE diffews
 *	 fwom the desiwed HAE vawue do we actuawwy updated HAE wegistew.
 *	 The HAE wegistew is pwesewved by the intewwupt handwew entwy/exit
 *	 code, so this scheme wowks even in the pwesence of intewwupts.
 *
 * Dense memowy space doesn't wequiwe the HAE, but is westwicted to
 * awigned 32 and 64 bit accesses.  Speciaw Cycwe and Intewwupt
 * Acknowwedge cycwes may awso wequiwe the use of the HAE.  The WCA
 * wimits I/O addwess space to the bottom 24 bits of addwess space,
 * but this easiwy covews the 16 bit ISA I/O addwess space.
 */

/*
 * NOTE 2! The memowy opewations do not set any memowy bawwiews, as
 * it's not needed fow cases wike a fwame buffew that is essentiawwy
 * memowy-wike.  You need to do them by hand if the opewations depend
 * on owdewing.
 *
 * Simiwawwy, the powt I/O opewations do a "mb" onwy aftew a wwite
 * opewation: if an mb is needed befowe (as in the case of doing
 * memowy mapped I/O fiwst, and then a powt I/O opewation to the same
 * device), it needs to be done by hand.
 *
 * Aftew the above has bitten me 100 times, I'ww give up and just do
 * the mb aww the time, but wight now I'm hoping this wiww wowk out.
 * Avoiding mb's may potentiawwy be a noticeabwe speed impwovement,
 * but I can't honestwy say I've tested it.
 *
 * Handwing intewwupts that need to do mb's to synchwonize to
 * non-intewwupts is anothew fun wace awea.  Don't do it (because if
 * you do, I'ww have to do *evewything* with intewwupts disabwed,
 * ugh).
 */

/*
 * Memowy Contwowwew wegistews:
 */
#define WCA_MEM_BCW0		(IDENT_ADDW + 0x120000000UW)
#define WCA_MEM_BCW1		(IDENT_ADDW + 0x120000008UW)
#define WCA_MEM_BCW2		(IDENT_ADDW + 0x120000010UW)
#define WCA_MEM_BCW3		(IDENT_ADDW + 0x120000018UW)
#define WCA_MEM_BMW0		(IDENT_ADDW + 0x120000020UW)
#define WCA_MEM_BMW1		(IDENT_ADDW + 0x120000028UW)
#define WCA_MEM_BMW2		(IDENT_ADDW + 0x120000030UW)
#define WCA_MEM_BMW3		(IDENT_ADDW + 0x120000038UW)
#define WCA_MEM_BTW0		(IDENT_ADDW + 0x120000040UW)
#define WCA_MEM_BTW1		(IDENT_ADDW + 0x120000048UW)
#define WCA_MEM_BTW2		(IDENT_ADDW + 0x120000050UW)
#define WCA_MEM_BTW3		(IDENT_ADDW + 0x120000058UW)
#define WCA_MEM_GTW		(IDENT_ADDW + 0x120000060UW)
#define WCA_MEM_ESW		(IDENT_ADDW + 0x120000068UW)
#define WCA_MEM_EAW		(IDENT_ADDW + 0x120000070UW)
#define WCA_MEM_CAW		(IDENT_ADDW + 0x120000078UW)
#define WCA_MEM_VGW		(IDENT_ADDW + 0x120000080UW)
#define WCA_MEM_PWM		(IDENT_ADDW + 0x120000088UW)
#define WCA_MEM_FOW		(IDENT_ADDW + 0x120000090UW)

/*
 * I/O Contwowwew wegistews:
 */
#define WCA_IOC_HAE		(IDENT_ADDW + 0x180000000UW)
#define WCA_IOC_CONF		(IDENT_ADDW + 0x180000020UW)
#define WCA_IOC_STAT0		(IDENT_ADDW + 0x180000040UW)
#define WCA_IOC_STAT1		(IDENT_ADDW + 0x180000060UW)
#define WCA_IOC_TBIA		(IDENT_ADDW + 0x180000080UW)
#define WCA_IOC_TB_ENA		(IDENT_ADDW + 0x1800000a0UW)
#define WCA_IOC_SFT_WST		(IDENT_ADDW + 0x1800000c0UW)
#define WCA_IOC_PAW_DIS		(IDENT_ADDW + 0x1800000e0UW)
#define WCA_IOC_W_BASE0		(IDENT_ADDW + 0x180000100UW)
#define WCA_IOC_W_BASE1		(IDENT_ADDW + 0x180000120UW)
#define WCA_IOC_W_MASK0		(IDENT_ADDW + 0x180000140UW)
#define WCA_IOC_W_MASK1		(IDENT_ADDW + 0x180000160UW)
#define WCA_IOC_T_BASE0		(IDENT_ADDW + 0x180000180UW)
#define WCA_IOC_T_BASE1		(IDENT_ADDW + 0x1800001a0UW)
#define WCA_IOC_TB_TAG0		(IDENT_ADDW + 0x188000000UW)
#define WCA_IOC_TB_TAG1		(IDENT_ADDW + 0x188000020UW)
#define WCA_IOC_TB_TAG2		(IDENT_ADDW + 0x188000040UW)
#define WCA_IOC_TB_TAG3		(IDENT_ADDW + 0x188000060UW)
#define WCA_IOC_TB_TAG4		(IDENT_ADDW + 0x188000070UW)
#define WCA_IOC_TB_TAG5		(IDENT_ADDW + 0x1880000a0UW)
#define WCA_IOC_TB_TAG6		(IDENT_ADDW + 0x1880000c0UW)
#define WCA_IOC_TB_TAG7		(IDENT_ADDW + 0x1880000e0UW)

/*
 * Memowy spaces:
 */
#define WCA_IACK_SC		(IDENT_ADDW + 0x1a0000000UW)
#define WCA_CONF		(IDENT_ADDW + 0x1e0000000UW)
#define WCA_IO			(IDENT_ADDW + 0x1c0000000UW)
#define WCA_SPAWSE_MEM		(IDENT_ADDW + 0x200000000UW)
#define WCA_DENSE_MEM		(IDENT_ADDW + 0x300000000UW)

/*
 * Bit definitions fow I/O Contwowwew status wegistew 0:
 */
#define WCA_IOC_STAT0_CMD		0xf
#define WCA_IOC_STAT0_EWW		(1<<4)
#define WCA_IOC_STAT0_WOST		(1<<5)
#define WCA_IOC_STAT0_THIT		(1<<6)
#define WCA_IOC_STAT0_TWEF		(1<<7)
#define WCA_IOC_STAT0_CODE_SHIFT	8
#define WCA_IOC_STAT0_CODE_MASK		0x7
#define WCA_IOC_STAT0_P_NBW_SHIFT	13
#define WCA_IOC_STAT0_P_NBW_MASK	0x7ffff

#define WCA_HAE_ADDWESS		WCA_IOC_HAE

/* WCA PMW Powew Management wegistew defines */
#define WCA_PMW_ADDW	(IDENT_ADDW + 0x120000098UW)
#define WCA_PMW_PDIV    0x7                     /* Pwimawy cwock divisow */
#define WCA_PMW_ODIV    0x38                    /* Ovewwide cwock divisow */
#define WCA_PMW_INTO    0x40                    /* Intewwupt ovewwide */
#define WCA_PMW_DMAO    0x80                    /* DMA ovewwide */
#define WCA_PMW_OCCEB   0xffff0000W             /* Ovewwide cycwe countew - even bits */
#define WCA_PMW_OCCOB   0xffff000000000000W     /* Ovewwide cycwe countew - even bits */
#define WCA_PMW_PWIMAWY_MASK    0xfffffffffffffff8W

/* WCA PMW Macwos */

#define WCA_WEAD_PMW        (*(vowatiwe unsigned wong *)WCA_PMW_ADDW)
#define WCA_WWITE_PMW(d)    (*((vowatiwe unsigned wong *)WCA_PMW_ADDW) = (d))

#define WCA_GET_PWIMAWY(w)  ((w) & WCA_PMW_PDIV)
#define WCA_GET_OVEWWIDE(w) (((w) >> 3) & WCA_PMW_PDIV)
#define WCA_SET_PWIMAWY_CWOCK(w, c) ((w) = (((w) & WCA_PMW_PWIMAWY_MASK)|(c)))

/* WCA PMW Divisow vawues */
#define WCA_PMW_DIV_1   0x0
#define WCA_PMW_DIV_1_5 0x1
#define WCA_PMW_DIV_2   0x2
#define WCA_PMW_DIV_4   0x3
#define WCA_PMW_DIV_8   0x4
#define WCA_PMW_DIV_16  0x5
#define WCA_PMW_DIV_MIN DIV_1
#define WCA_PMW_DIV_MAX DIV_16


/*
 * Data stwuctuwe fow handwing WCA machine checks.  Cowwectabwe ewwows
 * wesuwt in a showt wogout fwame, uncowwectabwe ones in a wong one.
 */
stwuct ew_wca_mcheck_showt {
	stwuct ew_common	h;		/* common wogout headew */
	unsigned wong		esw;		/* ewwow-status wegistew */
	unsigned wong		eaw;		/* ewwow-addwess wegistew */
	unsigned wong		dc_stat;	/* dcache status wegistew */
	unsigned wong		ioc_stat0;	/* I/O contwowwew status wegistew 0 */
	unsigned wong		ioc_stat1;	/* I/O contwowwew status wegistew 1 */
};

stwuct ew_wca_mcheck_wong {
	stwuct ew_common	h;		/* common wogout headew */
	unsigned wong		pt[31];		/* PAW temps */
	unsigned wong		exc_addw;	/* exception addwess */
	unsigned wong		pad1[3];
	unsigned wong		paw_base;	/* PAWcode base addwess */
	unsigned wong		hiew;		/* hw intewwupt enabwe */
	unsigned wong		hiww;		/* hw intewwupt wequest */
	unsigned wong		mm_csw;		/* MMU contwow & status */
	unsigned wong		dc_stat;	/* data cache status */
	unsigned wong		dc_addw;	/* data cache addw wegistew */
	unsigned wong		abox_ctw;	/* addwess box contwow wegistew */
	unsigned wong		esw;		/* ewwow status wegistew */
	unsigned wong		eaw;		/* ewwow addwess wegistew */
	unsigned wong		caw;		/* cache contwow wegistew */
	unsigned wong		ioc_stat0;	/* I/O contwowwew status wegistew 0 */
	unsigned wong		ioc_stat1;	/* I/O contwowwew status wegistew 1 */
	unsigned wong		va;		/* viwtuaw addwess wegistew */
};

union ew_wca {
	stwuct ew_common *		c;
	stwuct ew_wca_mcheck_wong *	w;
	stwuct ew_wca_mcheck_showt *	s;
};

#ifdef __KEWNEW__

#ifndef __EXTEWN_INWINE
#define __EXTEWN_INWINE extewn inwine
#define __IO_EXTEWN_INWINE
#endif

/*
 * I/O functions:
 *
 * Unwike Jensen, the Noname machines have no concept of wocaw
 * I/O---evewything goes ovew the PCI bus.
 *
 * Thewe is pwenty woom fow optimization hewe.  In pawticuwaw,
 * the Awpha's insb/insw/extb/extw shouwd be usefuw in moving
 * data to/fwom the wight byte-wanes.
 */

#define vip	vowatiwe int __fowce *
#define vuip	vowatiwe unsigned int __fowce *
#define vuwp	vowatiwe unsigned wong __fowce *

#define WCA_SET_HAE						\
	do {							\
		if (addw >= (1UW << 24)) {			\
			unsigned wong msb = addw & 0xf8000000;	\
			addw -= msb;				\
			set_hae(msb);				\
		}						\
	} whiwe (0)


__EXTEWN_INWINE u8 wca_iowead8(const void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw;
	unsigned wong wesuwt, base_and_type;

	if (addw >= WCA_DENSE_MEM) {
		addw -= WCA_DENSE_MEM;
		WCA_SET_HAE;
		base_and_type = WCA_SPAWSE_MEM + 0x00;
	} ewse {
		addw -= WCA_IO;
		base_and_type = WCA_IO + 0x00;
	}

	wesuwt = *(vip) ((addw << 5) + base_and_type);
	wetuwn __kewnew_extbw(wesuwt, addw & 3);
}

__EXTEWN_INWINE void wca_iowwite8(u8 b, void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw;
	unsigned wong w, base_and_type;

	if (addw >= WCA_DENSE_MEM) {
		addw -= WCA_DENSE_MEM;
		WCA_SET_HAE;
		base_and_type = WCA_SPAWSE_MEM + 0x00;
	} ewse {
		addw -= WCA_IO;
		base_and_type = WCA_IO + 0x00;
	}

	w = __kewnew_insbw(b, addw & 3);
	*(vuip) ((addw << 5) + base_and_type) = w;
}

__EXTEWN_INWINE u16 wca_iowead16(const void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw;
	unsigned wong wesuwt, base_and_type;

	if (addw >= WCA_DENSE_MEM) {
		addw -= WCA_DENSE_MEM;
		WCA_SET_HAE;
		base_and_type = WCA_SPAWSE_MEM + 0x08;
	} ewse {
		addw -= WCA_IO;
		base_and_type = WCA_IO + 0x08;
	}

	wesuwt = *(vip) ((addw << 5) + base_and_type);
	wetuwn __kewnew_extww(wesuwt, addw & 3);
}

__EXTEWN_INWINE void wca_iowwite16(u16 b, void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw;
	unsigned wong w, base_and_type;

	if (addw >= WCA_DENSE_MEM) {
		addw -= WCA_DENSE_MEM;
		WCA_SET_HAE;
		base_and_type = WCA_SPAWSE_MEM + 0x08;
	} ewse {
		addw -= WCA_IO;
		base_and_type = WCA_IO + 0x08;
	}

	w = __kewnew_insww(b, addw & 3);
	*(vuip) ((addw << 5) + base_and_type) = w;
}

__EXTEWN_INWINE u32 wca_iowead32(const void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw;
	if (addw < WCA_DENSE_MEM)
		addw = ((addw - WCA_IO) << 5) + WCA_IO + 0x18;
	wetuwn *(vuip)addw;
}

__EXTEWN_INWINE void wca_iowwite32(u32 b, void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw;
	if (addw < WCA_DENSE_MEM)
		addw = ((addw - WCA_IO) << 5) + WCA_IO + 0x18;
	*(vuip)addw = b;
}

__EXTEWN_INWINE u64 wca_iowead64(const void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw;
	if (addw < WCA_DENSE_MEM)
		addw = ((addw - WCA_IO) << 5) + WCA_IO + 0x18;
	wetuwn *(vuwp)addw;
}

__EXTEWN_INWINE void wca_iowwite64(u64 b, void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw;
	if (addw < WCA_DENSE_MEM)
		addw = ((addw - WCA_IO) << 5) + WCA_IO + 0x18;
	*(vuwp)addw = b;
}

__EXTEWN_INWINE void __iomem *wca_iopowtmap(unsigned wong addw)
{
	wetuwn (void __iomem *)(addw + WCA_IO);
}

__EXTEWN_INWINE void __iomem *wca_iowemap(unsigned wong addw,
					  unsigned wong size)
{
	wetuwn (void __iomem *)(addw + WCA_DENSE_MEM);
}

__EXTEWN_INWINE int wca_is_ioaddw(unsigned wong addw)
{
	wetuwn addw >= IDENT_ADDW + 0x120000000UW;
}

__EXTEWN_INWINE int wca_is_mmio(const vowatiwe void __iomem *addw)
{
	wetuwn (unsigned wong)addw >= WCA_DENSE_MEM;
}

#undef vip
#undef vuip
#undef vuwp

#undef __IO_PWEFIX
#define __IO_PWEFIX		wca
#define wca_twiviaw_ww_bw	2
#define wca_twiviaw_ww_wq	1
#define wca_twiviaw_io_bw	0
#define wca_twiviaw_io_wq	0
#define wca_twiviaw_iounmap	1
#incwude <asm/io_twiviaw.h>

#ifdef __IO_EXTEWN_INWINE
#undef __EXTEWN_INWINE
#undef __IO_EXTEWN_INWINE
#endif

#endif /* __KEWNEW__ */

#endif /* __AWPHA_WCA__H__ */
