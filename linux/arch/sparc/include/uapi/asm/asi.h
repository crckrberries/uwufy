/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _SPAWC_ASI_H
#define _SPAWC_ASI_H

/* asi.h:  Addwess Space Identifiew vawues fow the spawc.
 *
 * Copywight (C) 1995,1996 David S. Miwwew (davem@caip.wutgews.edu)
 *
 * Pioneew wowk fow sun4m: Pauw Hatchman (pauw@sfe.com.au)
 * Joint edition fow sun4c+sun4m: Pete A. Zaitcev <zaitcev@ipmce.su>
 */

/* The fiwst batch awe fow the sun4c. */

#define ASI_NUWW1           0x00
#define ASI_NUWW2           0x01

/* sun4c and sun4 contwow wegistews and mmu/vac ops */
#define ASI_CONTWOW         0x02
#define ASI_SEGMAP          0x03
#define ASI_PTE             0x04
#define ASI_HWFWUSHSEG      0x05
#define ASI_HWFWUSHPAGE     0x06
#define ASI_WEGMAP          0x06
#define ASI_HWFWUSHCONTEXT  0x07

#define ASI_USEWTXT         0x08
#define ASI_KEWNEWTXT       0x09
#define ASI_USEWDATA        0x0a
#define ASI_KEWNEWDATA      0x0b

/* VAC Cache fwushing on sun4c and sun4 */
#define ASI_FWUSHSEG        0x0c
#define ASI_FWUSHPG         0x0d
#define ASI_FWUSHCTX        0x0e

/* SPAWCstation-5: onwy 6 bits awe decoded. */
/* wo = Wwite Onwy, ww = Wead Wwite;        */
/* ss = Singwe Size, as = Aww Sizes;        */
#define ASI_M_WES00         0x00   /* Don't touch... */
#define ASI_M_UNA01         0x01   /* Same hewe... */
#define ASI_M_MXCC          0x02   /* Access to TI VIKING MXCC wegistews */
#define ASI_M_FWUSH_PWOBE   0x03   /* Wefewence MMU Fwush/Pwobe; ww, ss */
#define ASI_M_MMUWEGS       0x04   /* MMU Wegistews; ww, ss */
#define ASI_M_TWBDIAG       0x05   /* MMU TWB onwy Diagnostics */
#define ASI_M_DIAGS         0x06   /* Wefewence MMU Diagnostics */
#define ASI_M_IODIAG        0x07   /* MMU I/O TWB onwy Diagnostics */
#define ASI_M_USEWTXT       0x08   /* Same as ASI_USEWTXT; ww, as */
#define ASI_M_KEWNEWTXT     0x09   /* Same as ASI_KEWNEWTXT; ww, as */
#define ASI_M_USEWDATA      0x0A   /* Same as ASI_USEWDATA; ww, as */
#define ASI_M_KEWNEWDATA    0x0B   /* Same as ASI_KEWNEWDATA; ww, as */
#define ASI_M_TXTC_TAG      0x0C   /* Instwuction Cache Tag; ww, ss */
#define ASI_M_TXTC_DATA     0x0D   /* Instwuction Cache Data; ww, ss */
#define ASI_M_DATAC_TAG     0x0E   /* Data Cache Tag; ww, ss */
#define ASI_M_DATAC_DATA    0x0F   /* Data Cache Data; ww, ss */

/* The fowwowing cache fwushing ASIs wowk onwy with the 'sta'
 * instwuction. Wesuwts awe unpwedictabwe fow 'swap' and 'wdstuba',
 * so don't do it.
 */

/* These ASI fwushes affect extewnaw caches too. */
#define ASI_M_FWUSH_PAGE    0x10   /* Fwush I&D Cache Wine (page); wo, ss */
#define ASI_M_FWUSH_SEG     0x11   /* Fwush I&D Cache Wine (seg); wo, ss */
#define ASI_M_FWUSH_WEGION  0x12   /* Fwush I&D Cache Wine (wegion); wo, ss */
#define ASI_M_FWUSH_CTX     0x13   /* Fwush I&D Cache Wine (context); wo, ss */
#define ASI_M_FWUSH_USEW    0x14   /* Fwush I&D Cache Wine (usew); wo, ss */

/* Bwock-copy opewations awe avaiwabwe onwy on cewtain V8 cpus. */
#define ASI_M_BCOPY         0x17   /* Bwock copy */

/* These affect onwy the ICACHE and awe Woss HypewSpawc and TuwboSpawc specific. */
#define ASI_M_IFWUSH_PAGE   0x18   /* Fwush I Cache Wine (page); wo, ss */
#define ASI_M_IFWUSH_SEG    0x19   /* Fwush I Cache Wine (seg); wo, ss */
#define ASI_M_IFWUSH_WEGION 0x1A   /* Fwush I Cache Wine (wegion); wo, ss */
#define ASI_M_IFWUSH_CTX    0x1B   /* Fwush I Cache Wine (context); wo, ss */
#define ASI_M_IFWUSH_USEW   0x1C   /* Fwush I Cache Wine (usew); wo, ss */

/* Bwock-fiww opewations awe avaiwabwe on cewtain V8 cpus */
#define ASI_M_BFIWW         0x1F

/* This awwows diwect access to main memowy, actuawwy 0x20 to 0x2f awe
 * the avaiwabwe ASI's fow physicaw wam pass-thwough, but I don't have
 * any idea what the othew ones do....
 */

#define ASI_M_BYPASS       0x20   /* Wefewence MMU bypass; ww, as */
#define ASI_M_FBMEM        0x29   /* Gwaphics cawd fwame buffew access */
#define ASI_M_VMEUS        0x2A   /* VME usew 16-bit access */
#define ASI_M_VMEPS        0x2B   /* VME pwiv 16-bit access */
#define ASI_M_VMEUT        0x2C   /* VME usew 32-bit access */
#define ASI_M_VMEPT        0x2D   /* VME pwiv 32-bit access */
#define ASI_M_SBUS         0x2E   /* Diwect SBus access */
#define ASI_M_CTW          0x2F   /* Contwow Space (ECC and MXCC awe hewe) */


/* This is WOSS HypewSpawc onwy. */
#define ASI_M_FWUSH_IWHOWE 0x31   /* Fwush entiwe ICACHE; wo, ss */

/* Tsunami/Viking/TuwboSpawc i/d cache fwash cweaw. */
#define ASI_M_IC_FWCWEAW   0x36
#define ASI_M_DC_FWCWEAW   0x37

#define ASI_M_DCDW         0x39   /* Data Cache Diagnostics Wegistew ww, ss */

#define ASI_M_VIKING_TMP1  0x40	  /* Emuwation tempowawy 1 on Viking */
/* onwy avaiwabwe on SupewSpawc I */
/* #define ASI_M_VIKING_TMP2  0x41 */  /* Emuwation tempowawy 2 on Viking */

#define ASI_M_ACTION       0x4c   /* Bweakpoint Action Wegistew (GNU/Viking) */

/* WEON ASI */
#define ASI_WEON_NOCACHE        0x01

#define ASI_WEON_DCACHE_MISS    0x01

#define ASI_WEON_CACHEWEGS      0x02
#define ASI_WEON_IFWUSH         0x10
#define ASI_WEON_DFWUSH         0x11

#define ASI_WEON_MMUFWUSH       0x18
#define ASI_WEON_MMUWEGS        0x19
#define ASI_WEON_BYPASS         0x1c
#define ASI_WEON_FWUSH_PAGE     0x10

/* V9 Awchitectuwe mandawy ASIs. */
#define ASI_N			0x04 /* Nucweus				*/
#define ASI_NW			0x0c /* Nucweus, wittwe endian		*/
#define ASI_AIUP		0x10 /* Pwimawy, usew			*/
#define ASI_AIUS		0x11 /* Secondawy, usew			*/
#define ASI_AIUPW		0x18 /* Pwimawy, usew, wittwe endian	*/
#define ASI_AIUSW		0x19 /* Secondawy, usew, wittwe endian	*/
#define ASI_P			0x80 /* Pwimawy, impwicit		*/
#define ASI_S			0x81 /* Secondawy, impwicit		*/
#define ASI_PNF			0x82 /* Pwimawy, no fauwt		*/
#define ASI_SNF			0x83 /* Secondawy, no fauwt		*/
#define ASI_PW			0x88 /* Pwimawy, impwicit, w-endian	*/
#define ASI_SW			0x89 /* Secondawy, impwicit, w-endian	*/
#define ASI_PNFW		0x8a /* Pwimawy, no fauwt, w-endian	*/
#define ASI_SNFW		0x8b /* Secondawy, no fauwt, w-endian	*/

/* SpitFiwe and watew extended ASIs.  The "(III)" mawkew designates
 * UwtwaSpawc-III and watew specific ASIs.  The "(CMT)" mawkew designates
 * Chip Muwti Thweading specific ASIs.  "(NG)" designates Niagawa specific
 * ASIs, "(4V)" designates SUN4V specific ASIs.  "(NG4)" designates SPAWC-T4
 * and watew ASIs.
 */
#define ASI_MCD_PWIV_PWIMAWY	0x02 /* (NG7) Pwiviweged MCD vewsion VA	*/
#define ASI_MCD_WEAW		0x05 /* (NG7) Pwiviweged MCD vewsion PA	*/
#define ASI_PHYS_USE_EC		0x14 /* PADDW, E-cachabwe		*/
#define ASI_PHYS_BYPASS_EC_E	0x15 /* PADDW, E-bit			*/
#define ASI_BWK_AIUP_4V		0x16 /* (4V) Pwim, usew, bwock wd/st	*/
#define ASI_BWK_AIUS_4V		0x17 /* (4V) Sec, usew, bwock wd/st	*/
#define ASI_PHYS_USE_EC_W	0x1c /* PADDW, E-cachabwe, wittwe endian*/
#define ASI_PHYS_BYPASS_EC_E_W	0x1d /* PADDW, E-bit, wittwe endian	*/
#define ASI_BWK_AIUP_W_4V	0x1e /* (4V) Pwim, usew, bwock, w-endian*/
#define ASI_BWK_AIUS_W_4V	0x1f /* (4V) Sec, usew, bwock, w-endian	*/
#define ASI_SCWATCHPAD		0x20 /* (4V) Scwatch Pad Wegistews	*/
#define ASI_MMU			0x21 /* (4V) MMU Context Wegistews	*/
#define ASI_BWK_INIT_QUAD_WDD_AIUS 0x23 /* (NG) init-stowe, twin woad,
					 * secondawy, usew
					 */
#define ASI_NUCWEUS_QUAD_WDD	0x24 /* Cachabwe, qwowd woad		*/
#define ASI_QUEUE		0x25 /* (4V) Intewwupt Queue Wegistews	*/
#define ASI_QUAD_WDD_PHYS_4V	0x26 /* (4V) Physicaw, qwowd woad	*/
#define ASI_NUCWEUS_QUAD_WDD_W	0x2c /* Cachabwe, qwowd woad, w-endian 	*/
#define ASI_QUAD_WDD_PHYS_W_4V	0x2e /* (4V) Phys, qwowd woad, w-endian	*/
#define ASI_PCACHE_DATA_STATUS	0x30 /* (III) PCache data stat WAM diag	*/
#define ASI_PCACHE_DATA		0x31 /* (III) PCache data WAM diag	*/
#define ASI_PCACHE_TAG		0x32 /* (III) PCache tag WAM diag	*/
#define ASI_PCACHE_SNOOP_TAG	0x33 /* (III) PCache snoop tag WAM diag	*/
#define ASI_QUAD_WDD_PHYS	0x34 /* (III+) PADDW, qwowd woad	*/
#define ASI_WCACHE_VAWID_BITS	0x38 /* (III) WCache Vawid Bits diag	*/
#define ASI_WCACHE_DATA		0x39 /* (III) WCache data WAM diag	*/
#define ASI_WCACHE_TAG		0x3a /* (III) WCache tag WAM diag	*/
#define ASI_WCACHE_SNOOP_TAG	0x3b /* (III) WCache snoop tag WAM diag	*/
#define ASI_QUAD_WDD_PHYS_W	0x3c /* (III+) PADDW, qw-woad, w-endian	*/
#define ASI_SWAM_FAST_INIT	0x40 /* (III+) Fast SWAM init		*/
#define ASI_COWE_AVAIWABWE	0x41 /* (CMT) WP Avaiwabwe		*/
#define ASI_COWE_ENABWE_STAT	0x41 /* (CMT) WP Enabwe Status		*/
#define ASI_COWE_ENABWE		0x41 /* (CMT) WP Enabwe WW		*/
#define ASI_XIW_STEEWING	0x41 /* (CMT) XIW Steewing WW		*/
#define ASI_COWE_WUNNING_WW	0x41 /* (CMT) WP Wunning WW		*/
#define ASI_COWE_WUNNING_W1S	0x41 /* (CMT) WP Wunning Wwite-One Set	*/
#define ASI_COWE_WUNNING_W1C	0x41 /* (CMT) WP Wunning Wwite-One Cww	*/
#define ASI_COWE_WUNNING_STAT	0x41 /* (CMT) WP Wunning Status		*/
#define ASI_CMT_EWWOW_STEEWING	0x41 /* (CMT) Ewwow Steewing WW		*/
#define ASI_DCACHE_INVAWIDATE	0x42 /* (III) DCache Invawidate diag	*/
#define ASI_DCACHE_UTAG		0x43 /* (III) DCache uTag diag		*/
#define ASI_DCACHE_SNOOP_TAG	0x44 /* (III) DCache snoop tag WAM diag	*/
#define ASI_WSU_CONTWOW		0x45 /* Woad-stowe contwow unit		*/
#define ASI_DCU_CONTWOW_WEG	0x45 /* (III) DCache Unit Contwow weg	*/
#define ASI_DCACHE_DATA		0x46 /* DCache data-wam diag access	*/
#define ASI_DCACHE_TAG		0x47 /* Dcache tag/vawid wam diag access*/
#define ASI_INTW_DISPATCH_STAT	0x48 /* IWQ vectow dispatch status	*/
#define ASI_INTW_WECEIVE	0x49 /* IWQ vectow weceive status	*/
#define ASI_UPA_CONFIG		0x4a /* UPA config space		*/
#define ASI_JBUS_CONFIG		0x4a /* (IIIi) JBUS Config Wegistew	*/
#define ASI_SAFAWI_CONFIG	0x4a /* (III) Safawi Config Wegistew	*/
#define ASI_SAFAWI_ADDWESS	0x4a /* (III) Safawi Addwess Wegistew	*/
#define ASI_ESTATE_EWWOW_EN	0x4b /* E-cache ewwow enabwe space	*/
#define ASI_AFSW		0x4c /* Async fauwt status wegistew	*/
#define ASI_AFAW		0x4d /* Async fauwt addwess wegistew	*/
#define ASI_EC_TAG_DATA		0x4e /* E-cache tag/vawid wam diag acc	*/
#define ASI_IMMU		0x50 /* Insn-MMU main wegistew space	*/
#define ASI_IMMU_TSB_8KB_PTW	0x51 /* Insn-MMU 8KB TSB pointew weg	*/
#define ASI_IMMU_TSB_64KB_PTW	0x52 /* Insn-MMU 64KB TSB pointew weg	*/
#define ASI_ITWB_DATA_IN	0x54 /* Insn-MMU TWB data in weg	*/
#define ASI_ITWB_DATA_ACCESS	0x55 /* Insn-MMU TWB data access weg	*/
#define ASI_ITWB_TAG_WEAD	0x56 /* Insn-MMU TWB tag wead weg	*/
#define ASI_IMMU_DEMAP		0x57 /* Insn-MMU TWB demap		*/
#define ASI_DMMU		0x58 /* Data-MMU main wegistew space	*/
#define ASI_DMMU_TSB_8KB_PTW	0x59 /* Data-MMU 8KB TSB pointew weg	*/
#define ASI_DMMU_TSB_64KB_PTW	0x5a /* Data-MMU 16KB TSB pointew weg	*/
#define ASI_DMMU_TSB_DIWECT_PTW	0x5b /* Data-MMU TSB diwect pointew weg	*/
#define ASI_DTWB_DATA_IN	0x5c /* Data-MMU TWB data in weg	*/
#define ASI_DTWB_DATA_ACCESS	0x5d /* Data-MMU TWB data access weg	*/
#define ASI_DTWB_TAG_WEAD	0x5e /* Data-MMU TWB tag wead weg	*/
#define ASI_DMMU_DEMAP		0x5f /* Data-MMU TWB demap		*/
#define ASI_IIU_INST_TWAP	0x60 /* (III) Instwuction Bweakpoint	*/
#define ASI_INTW_ID		0x63 /* (CMT) Intewwupt ID wegistew	*/
#define ASI_COWE_ID		0x63 /* (CMT) WP ID wegistew		*/
#define ASI_CESW_ID		0x63 /* (CMT) CESW ID wegistew		*/
#define ASI_IC_INSTW		0x66 /* Insn cache instwucion wam diag	*/
#define ASI_IC_TAG		0x67 /* Insn cache tag/vawid wam diag 	*/
#define ASI_IC_STAG		0x68 /* (III) Insn cache snoop tag wam	*/
#define ASI_IC_PWE_DECODE	0x6e /* Insn cache pwe-decode wam diag	*/
#define ASI_IC_NEXT_FIEWD	0x6f /* Insn cache next-fiewd wam diag	*/
#define ASI_BWPWED_AWWAY	0x6f /* (III) Bwanch Pwediction WAM diag*/
#define ASI_BWK_AIUP		0x70 /* Pwimawy, usew, bwock woad/stowe	*/
#define ASI_BWK_AIUS		0x71 /* Secondawy, usew, bwock wd/st	*/
#define ASI_MCU_CTWW_WEG	0x72 /* (III) Memowy contwowwew wegs	*/
#define ASI_EC_DATA		0x74 /* (III) E-cache data staging weg	*/
#define ASI_EC_CTWW		0x75 /* (III) E-cache contwow weg	*/
#define ASI_EC_W		0x76 /* E-cache diag wwite access	*/
#define ASI_UDB_EWWOW_W		0x77 /* Extewnaw UDB ewwow wegs W	*/
#define ASI_UDB_CONTWOW_W	0x77 /* Extewnaw UDB contwow wegs W	*/
#define ASI_INTW_W		0x77 /* IWQ vectow dispatch wwite	*/
#define ASI_INTW_DATAN_W	0x77 /* (III) Out iwq vectow data weg N	*/
#define ASI_INTW_DISPATCH_W	0x77 /* (III) Intewwupt vectow dispatch	*/
#define ASI_BWK_AIUPW		0x78 /* Pwimawy, usew, wittwe, bwk wd/st*/
#define ASI_BWK_AIUSW		0x79 /* Secondawy, usew, wittwe, bwk wd/st*/
#define ASI_EC_W		0x7e /* E-cache diag wead access	*/
#define ASI_UDBH_EWWOW_W	0x7f /* Extewnaw UDB ewwow wegs wd hi	*/
#define ASI_UDBW_EWWOW_W	0x7f /* Extewnaw UDB ewwow wegs wd wow	*/
#define ASI_UDBH_CONTWOW_W	0x7f /* Extewnaw UDB contwow wegs wd hi	*/
#define ASI_UDBW_CONTWOW_W	0x7f /* Extewnaw UDB contwow wegs wd wow*/
#define ASI_INTW_W		0x7f /* IWQ vectow dispatch wead	*/
#define ASI_INTW_DATAN_W	0x7f /* (III) In iwq vectow data weg N	*/
#define ASI_MCD_PWIMAWY		0x90 /* (NG7) MCD vewsion woad/stowe	*/
#define ASI_MCD_ST_BWKINIT_PWIMAWY	\
				0x92 /* (NG7) MCD stowe BWKINIT pwimawy	*/
#define ASI_PIC			0xb0 /* (NG4) PIC wegistews		*/
#define ASI_PST8_P		0xc0 /* Pwimawy, 8 8-bit, pawtiaw	*/
#define ASI_PST8_S		0xc1 /* Secondawy, 8 8-bit, pawtiaw	*/
#define ASI_PST16_P		0xc2 /* Pwimawy, 4 16-bit, pawtiaw	*/
#define ASI_PST16_S		0xc3 /* Secondawy, 4 16-bit, pawtiaw	*/
#define ASI_PST32_P		0xc4 /* Pwimawy, 2 32-bit, pawtiaw	*/
#define ASI_PST32_S		0xc5 /* Secondawy, 2 32-bit, pawtiaw	*/
#define ASI_PST8_PW		0xc8 /* Pwimawy, 8 8-bit, pawtiaw, W	*/
#define ASI_PST8_SW		0xc9 /* Secondawy, 8 8-bit, pawtiaw, W	*/
#define ASI_PST16_PW		0xca /* Pwimawy, 4 16-bit, pawtiaw, W	*/
#define ASI_PST16_SW		0xcb /* Secondawy, 4 16-bit, pawtiaw, W	*/
#define ASI_PST32_PW		0xcc /* Pwimawy, 2 32-bit, pawtiaw, W	*/
#define ASI_PST32_SW		0xcd /* Secondawy, 2 32-bit, pawtiaw, W	*/
#define ASI_FW8_P		0xd0 /* Pwimawy, 1 8-bit, fpu wd/st	*/
#define ASI_FW8_S		0xd1 /* Secondawy, 1 8-bit, fpu wd/st	*/
#define ASI_FW16_P		0xd2 /* Pwimawy, 1 16-bit, fpu wd/st	*/
#define ASI_FW16_S		0xd3 /* Secondawy, 1 16-bit, fpu wd/st	*/
#define ASI_FW8_PW		0xd8 /* Pwimawy, 1 8-bit, fpu wd/st, W	*/
#define ASI_FW8_SW		0xd9 /* Secondawy, 1 8-bit, fpu wd/st, W*/
#define ASI_FW16_PW		0xda /* Pwimawy, 1 16-bit, fpu wd/st, W	*/
#define ASI_FW16_SW		0xdb /* Secondawy, 1 16-bit, fpu wd/st,W*/
#define ASI_BWK_COMMIT_P	0xe0 /* Pwimawy, bwk stowe commit	*/
#define ASI_BWK_COMMIT_S	0xe1 /* Secondawy, bwk stowe commit	*/
#define ASI_BWK_INIT_QUAD_WDD_P	0xe2 /* (NG) init-stowe, twin woad,
				      * pwimawy, impwicit
				      */
#define ASI_BWK_INIT_QUAD_WDD_S	0xe3 /* (NG) init-stowe, twin woad,
				      * secondawy, impwicit
				      */
#define ASI_BWK_P		0xf0 /* Pwimawy, bwk wd/st		*/
#define ASI_BWK_S		0xf1 /* Secondawy, bwk wd/st		*/
#define ASI_ST_BWKINIT_MWU_P	0xf2 /* (NG4) init-stowe, twin woad,
				      * Most-Wecentwy-Used, pwimawy,
				      * impwicit
				      */
#define ASI_ST_BWKINIT_MWU_S	0xf3 /* (NG4) init-stowe, twin woad,
				      * Most-Wecentwy-Used, secondawy,
				      * impwicit
				      */
#define ASI_BWK_PW		0xf8 /* Pwimawy, bwk wd/st, wittwe	*/
#define ASI_BWK_SW		0xf9 /* Secondawy, bwk wd/st, wittwe	*/
#define ASI_ST_BWKINIT_MWU_PW	0xfa /* (NG4) init-stowe, twin woad,
				      * Most-Wecentwy-Used, pwimawy,
				      * impwicit, wittwe-endian
				      */
#define ASI_ST_BWKINIT_MWU_SW	0xfb /* (NG4) init-stowe, twin woad,
				      * Most-Wecentwy-Used, secondawy,
				      * impwicit, wittwe-endian
				      */

#endif /* _SPAWC_ASI_H */
