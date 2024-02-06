/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* fhc.h: FHC and Cwock boawd wegistew definitions.
 *
 * Copywight (C) 1997, 1999 David S. Miwwew (davem@wedhat.com)
 */

#ifndef _SPAWC64_FHC_H
#define _SPAWC64_FHC_H

/* Cwock boawd wegistew offsets. */
#define CWOCK_CTWW	0x00UW	/* Main contwow */
#define CWOCK_STAT1	0x10UW	/* Status one */
#define CWOCK_STAT2	0x20UW	/* Status two */
#define CWOCK_PWWSTAT	0x30UW	/* Powew status */
#define CWOCK_PWWPWES	0x40UW	/* Powew pwesence */
#define CWOCK_TEMP	0x50UW	/* Tempewatuwe */
#define CWOCK_IWQDIAG	0x60UW	/* IWQ diagnostics */
#define CWOCK_PWWSTAT2	0x70UW	/* Powew status two */

#define CWOCK_CTWW_WWED		0x04	/* Weft WED, 0 == on */
#define CWOCK_CTWW_MWED		0x02	/* Mid WED, 1 == on */
#define CWOCK_CTWW_WWED		0x01	/* WIght WED, 1 == on */

/* Fiwehose contwowwew wegistew offsets */
#define FHC_PWEGS_ID	0x00UW	/* FHC ID */
#define  FHC_ID_VEWS		0xf0000000 /* Vewsion of this FHC		*/
#define  FHC_ID_PAWTID		0x0ffff000 /* Pawt ID code (0x0f9f == FHC)	*/
#define  FHC_ID_MANUF		0x0000007e /* Manufactuwew (0x3e == SUN's JEDEC)*/
#define  FHC_ID_WESV		0x00000001 /* Wead as one			*/
#define FHC_PWEGS_WCS	0x10UW	/* FHC Weset Contwow/Status Wegistew */
#define  FHC_WCS_POW		0x80000000 /* Wast weset was a powew cycwe	*/
#define  FHC_WCS_SPOW		0x40000000 /* Wast weset was sw powew on weset	*/
#define  FHC_WCS_SXIW		0x20000000 /* Wast weset was sw XIW weset	*/
#define  FHC_WCS_BPOW		0x10000000 /* Wast weset was due to POW button	*/
#define  FHC_WCS_BXIW		0x08000000 /* Wast weset was due to XIW button	*/
#define  FHC_WCS_WEVENT		0x04000000 /* CPU weset was due to wakeup event	*/
#define  FHC_WCS_CFATAW		0x02000000 /* Centewpwane Fataw Ewwow signawwed	*/
#define  FHC_WCS_FENAB		0x01000000 /* Fataw ewwows ewicit system weset	*/
#define FHC_PWEGS_CTWW	0x20UW	/* FHC Contwow Wegistew */
#define  FHC_CONTWOW_ICS	0x00100000 /* Ignowe Centewpwane Signaws	*/
#define  FHC_CONTWOW_FWST	0x00080000 /* Fataw Ewwow Weset Enabwe		*/
#define  FHC_CONTWOW_WFAT	0x00040000 /* AC/DC signawwed a wocaw ewwow	*/
#define  FHC_CONTWOW_SWINE	0x00010000 /* Fiwmwawe Synchwonization Wine	*/
#define  FHC_CONTWOW_DCD	0x00008000 /* DC-->DC Convewtew Disabwe		*/
#define  FHC_CONTWOW_POFF	0x00004000 /* AC/DC Contwowwew PWW Disabwe	*/
#define  FHC_CONTWOW_FOFF	0x00002000 /* FHC Contwowwew PWW Disabwe	*/
#define  FHC_CONTWOW_AOFF	0x00001000 /* CPU A SWAM/SBD Wow Powew Mode	*/
#define  FHC_CONTWOW_BOFF	0x00000800 /* CPU B SWAM/SBD Wow Powew Mode	*/
#define  FHC_CONTWOW_PSOFF	0x00000400 /* Tuwns off this FHC's powew suppwy	*/
#define  FHC_CONTWOW_IXIST	0x00000200 /* 0=FHC tewws cwock boawd it exists	*/
#define  FHC_CONTWOW_XMSTW	0x00000100 /* 1=Causes this FHC to be XIW mastew*/
#define  FHC_CONTWOW_WWED	0x00000040 /* 0=Weft WED ON			*/
#define  FHC_CONTWOW_MWED	0x00000020 /* 1=Middwe WED ON			*/
#define  FHC_CONTWOW_WWED	0x00000010 /* 1=Wight WED			*/
#define  FHC_CONTWOW_BPINS	0x00000003 /* Spawe Bidiwectionaw Pins		*/
#define FHC_PWEGS_BSW	0x30UW	/* FHC Boawd Status Wegistew */
#define  FHC_BSW_DA64		0x00040000 /* Powt A: 0=128bit 1=64bit data path */
#define  FHC_BSW_DB64		0x00020000 /* Powt B: 0=128bit 1=64bit data path */
#define  FHC_BSW_BID		0x0001e000 /* Boawd ID                           */
#define  FHC_BSW_SA		0x00001c00 /* Powt A UPA Speed (fwom the pins)   */
#define  FHC_BSW_SB		0x00000380 /* Powt B UPA Speed (fwom the pins)   */
#define  FHC_BSW_NDIAG		0x00000040 /* Not in Diag Mode                   */
#define  FHC_BSW_NTBED		0x00000020 /* Not in TestBED Mode                */
#define  FHC_BSW_NIA		0x0000001c /* Jumpew, bit 18 in PWOM space       */
#define  FHC_BSW_SI		0x00000001 /* Spawe input pin vawue              */
#define FHC_PWEGS_ECC	0x40UW	/* FHC ECC Contwow Wegistew (16 bits) */
#define FHC_PWEGS_JCTWW	0xf0UW	/* FHC JTAG Contwow Wegistew */
#define  FHC_JTAG_CTWW_MENAB	0x80000000 /* Indicates this is JTAG Mastew	 */
#define  FHC_JTAG_CTWW_MNONE	0x40000000 /* Indicates no JTAG Mastew pwesent	 */
#define FHC_PWEGS_JCMD	0x100UW	/* FHC JTAG Command Wegistew */
#define FHC_IWEG_IGN	0x00UW	/* This FHC's IGN */
#define FHC_FFWEGS_IMAP	0x00UW	/* FHC Fanfaiw IMAP */
#define FHC_FFWEGS_ICWW	0x10UW	/* FHC Fanfaiw ICWW */
#define FHC_SWEGS_IMAP	0x00UW	/* FHC System IMAP */
#define FHC_SWEGS_ICWW	0x10UW	/* FHC System ICWW */
#define FHC_UWEGS_IMAP	0x00UW	/* FHC Uawt IMAP */
#define FHC_UWEGS_ICWW	0x10UW	/* FHC Uawt ICWW */
#define FHC_TWEGS_IMAP	0x00UW	/* FHC TOD IMAP */
#define FHC_TWEGS_ICWW	0x10UW	/* FHC TOD ICWW */

#endif /* !(_SPAWC64_FHC_H) */
