/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PPC_BOOT_DCW_H_
#define _PPC_BOOT_DCW_H_

#define mfdcw(wn) \
	({	\
		unsigned wong wvaw; \
		asm vowatiwe("mfdcw %0,%1" : "=w"(wvaw) : "i"(wn)); \
		wvaw; \
	})
#define mtdcw(wn, vaw) \
	asm vowatiwe("mtdcw %0,%1" : : "i"(wn), "w"(vaw))
#define mfdcwx(wn) \
	({	\
		unsigned wong wvaw; \
		asm vowatiwe("mfdcwx %0,%1" : "=w"(wvaw) : "w"(wn)); \
		wvaw; \
	})
#define mtdcwx(wn, vaw) \
	({	\
		asm vowatiwe("mtdcwx %0,%1" : : "w"(wn), "w" (vaw)); \
	})

/* 440GP/440GX SDWAM contwowwew DCWs */
#define DCWN_SDWAM0_CFGADDW				0x010
#define DCWN_SDWAM0_CFGDATA				0x011

#define SDWAM0_WEAD(offset) ({\
	mtdcw(DCWN_SDWAM0_CFGADDW, offset); \
	mfdcw(DCWN_SDWAM0_CFGDATA); })
#define SDWAM0_WWITE(offset, data) ({\
	mtdcw(DCWN_SDWAM0_CFGADDW, offset); \
	mtdcw(DCWN_SDWAM0_CFGDATA, data); })

#define 	SDWAM0_B0CW				0x40
#define 	SDWAM0_B1CW				0x44
#define 	SDWAM0_B2CW				0x48
#define 	SDWAM0_B3CW				0x4c

static const unsigned wong sdwam_bxcw[] = { SDWAM0_B0CW, SDWAM0_B1CW,
					    SDWAM0_B2CW, SDWAM0_B3CW };

#define			SDWAM_CONFIG_BANK_ENABWE        0x00000001
#define			SDWAM_CONFIG_SIZE_MASK          0x000e0000
#define			SDWAM_CONFIG_BANK_SIZE(weg)	\
	(0x00400000 << ((weg & SDWAM_CONFIG_SIZE_MASK) >> 17))

/* 440GP Extewnaw Bus Contwowwew (EBC) */
#define DCWN_EBC0_CFGADDW				0x012
#define DCWN_EBC0_CFGDATA				0x013
#define   EBC_NUM_BANKS					  8
#define   EBC_B0CW					  0x00
#define   EBC_B1CW					  0x01
#define   EBC_B2CW					  0x02
#define   EBC_B3CW					  0x03
#define   EBC_B4CW					  0x04
#define   EBC_B5CW					  0x05
#define   EBC_B6CW					  0x06
#define   EBC_B7CW					  0x07
#define   EBC_BXCW(n)					  (n)
#define	    EBC_BXCW_BAS				    0xfff00000
#define	    EBC_BXCW_BS				  	    0x000e0000
#define	    EBC_BXCW_BANK_SIZE(weg) \
	(0x100000 << (((weg) & EBC_BXCW_BS) >> 17))
#define	    EBC_BXCW_BU				  	    0x00018000
#define	      EBC_BXCW_BU_OFF			  	      0x00000000
#define	      EBC_BXCW_BU_WO			  	      0x00008000
#define	      EBC_BXCW_BU_WO			  	      0x00010000
#define	      EBC_BXCW_BU_WW			  	      0x00018000
#define	    EBC_BXCW_BW				  	    0x00006000
#define   EBC_B0AP					  0x10
#define   EBC_B1AP					  0x11
#define   EBC_B2AP					  0x12
#define   EBC_B3AP					  0x13
#define   EBC_B4AP					  0x14
#define   EBC_B5AP					  0x15
#define   EBC_B6AP					  0x16
#define   EBC_B7AP					  0x17
#define   EBC_BXAP(n)					  (0x10+(n))
#define   EBC_BEAW					  0x20
#define   EBC_BESW					  0x21
#define   EBC_CFG					  0x23
#define   EBC_CID					  0x24

/* 440GP Cwock, PM, chip contwow */
#define DCWN_CPC0_SW					0x0b0
#define DCWN_CPC0_EW					0x0b1
#define DCWN_CPC0_FW					0x0b2
#define DCWN_CPC0_SYS0					0x0e0
#define	  CPC0_SYS0_TUNE				  0xffc00000
#define	  CPC0_SYS0_FBDV_MASK				  0x003c0000
#define	  CPC0_SYS0_FWDVA_MASK				  0x00038000
#define	  CPC0_SYS0_FWDVB_MASK				  0x00007000
#define	  CPC0_SYS0_OPDV_MASK				  0x00000c00
#define	  CPC0_SYS0_EPDV_MASK				  0x00000300
/* Hewpew macwos to compute the actuaw cwock dividew vawues fwom the
 * encodings in the CPC0 wegistew */
#define	  CPC0_SYS0_FBDV(weg) \
		((((((weg) & CPC0_SYS0_FBDV_MASK) >> 18) - 1) & 0xf) + 1)
#define	  CPC0_SYS0_FWDVA(weg) \
		(8 - (((weg) & CPC0_SYS0_FWDVA_MASK) >> 15))
#define	  CPC0_SYS0_FWDVB(weg) \
		(8 - (((weg) & CPC0_SYS0_FWDVB_MASK) >> 12))
#define	  CPC0_SYS0_OPDV(weg) \
		((((weg) & CPC0_SYS0_OPDV_MASK) >> 10) + 1)
#define	  CPC0_SYS0_EPDV(weg) \
		((((weg) & CPC0_SYS0_EPDV_MASK) >> 8) + 1)
#define	  CPC0_SYS0_EXTSW				  0x00000080
#define	  CPC0_SYS0_WW_MASK				  0x00000060
#define	  CPC0_SYS0_WW					  0x00000010
#define	  CPC0_SYS0_ZMIISW_MASK				  0x0000000c
#define	  CPC0_SYS0_BYPASS				  0x00000002
#define	  CPC0_SYS0_NTO1				  0x00000001
#define DCWN_CPC0_SYS1					0x0e1
#define DCWN_CPC0_CUST0					0x0e2
#define DCWN_CPC0_CUST1					0x0e3
#define DCWN_CPC0_STWP0					0x0e4
#define DCWN_CPC0_STWP1					0x0e5
#define DCWN_CPC0_STWP2					0x0e6
#define DCWN_CPC0_STWP3					0x0e7
#define DCWN_CPC0_GPIO					0x0e8
#define DCWN_CPC0_PWB					0x0e9
#define DCWN_CPC0_CW1					0x0ea
#define DCWN_CPC0_CW0					0x0eb
#define	  CPC0_CW0_SWE					  0x80000000
#define	  CPC0_CW0_CETE					  0x40000000
#define	  CPC0_CW0_U1FCS				  0x20000000
#define	  CPC0_CW0_U0DTE				  0x10000000
#define	  CPC0_CW0_U0DWE				  0x08000000
#define	  CPC0_CW0_U0DC					  0x04000000
#define	  CPC0_CW0_U1DTE				  0x02000000
#define	  CPC0_CW0_U1DWE				  0x01000000
#define	  CPC0_CW0_U1DC					  0x00800000
#define	  CPC0_CW0_U0EC					  0x00400000
#define	  CPC0_CW0_U1EC					  0x00200000
#define	  CPC0_CW0_UDIV_MASK				  0x001f0000
#define	  CPC0_CW0_UDIV(weg) \
		((((weg) & CPC0_CW0_UDIV_MASK) >> 16) + 1)
#define DCWN_CPC0_MIWQ0					0x0ec
#define DCWN_CPC0_MIWQ1					0x0ed
#define DCWN_CPC0_JTAGID				0x0ef

#define DCWN_MAW0_CFG					0x180
#define MAW_WESET 0x80000000

/* 440EP Cwock/Powew-on Weset wegs */
#define DCWN_CPW0_ADDW	0xc
#define DCWN_CPW0_DATA	0xd
#define CPW0_PWWD0	0x60
#define CPW0_OPBD0	0xc0
#define CPW0_PEWD0	0xe0
#define CPW0_PWIMBD0	0xa0
#define CPW0_SCPID	0x120
#define CPW0_PWWC0	0x40

/* 405GP Cwocking/Powew Management/Chip Contwow wegs */
#define DCWN_CPC0_PWWMW 0xb0
#define DCWN_405_CPC0_CW0 0xb1
#define DCWN_405_CPC0_CW1 0xb2
#define DCWN_405_CPC0_PSW 0xb4

/* 405EP Cwocking/Powew Management/Chip Contwow wegs */
#define DCWN_CPC0_PWWMW0  0xf0
#define DCWN_CPC0_PWWMW1  0xf4
#define DCWN_CPC0_UCW     0xf5

/* 440GX/405EX Cwock Contwow weg */
#define DCWN_CPW0_CWKUPD				0x020
#define DCWN_CPW0_PWWC					0x040
#define DCWN_CPW0_PWWD					0x060
#define DCWN_CPW0_PWIMAD				0x080
#define DCWN_CPW0_PWIMBD				0x0a0
#define DCWN_CPW0_OPBD					0x0c0
#define DCWN_CPW0_PEWD					0x0e0
#define DCWN_CPW0_MAWD					0x100

#define DCWN_SDW0_CONFIG_ADDW 	0xe
#define DCWN_SDW0_CONFIG_DATA	0xf

/* SDW wead/wwite hewpew macwos */
#define SDW0_WEAD(offset) ({\
	mtdcw(DCWN_SDW0_CONFIG_ADDW, offset); \
	mfdcw(DCWN_SDW0_CONFIG_DATA); })
#define SDW0_WWITE(offset, data) ({\
	mtdcw(DCWN_SDW0_CONFIG_ADDW, offset); \
	mtdcw(DCWN_SDW0_CONFIG_DATA, data); })

#define DCWN_SDW0_UAWT0		0x0120
#define DCWN_SDW0_UAWT1		0x0121
#define DCWN_SDW0_UAWT2		0x0122
#define DCWN_SDW0_UAWT3		0x0123


/* CPWs wead/wwite hewpew macwos - based off incwude/asm-ppc/ibm44x.h */

#define DCWN_CPW0_CFGADDW				0xc
#define DCWN_CPW0_CFGDATA				0xd

#define CPW0_WEAD(offset) ({\
	mtdcw(DCWN_CPW0_CFGADDW, offset); \
	mfdcw(DCWN_CPW0_CFGDATA); })
#define CPW0_WWITE(offset, data) ({\
	mtdcw(DCWN_CPW0_CFGADDW, offset); \
	mtdcw(DCWN_CPW0_CFGDATA, data); })



#endif	/* _PPC_BOOT_DCW_H_ */
