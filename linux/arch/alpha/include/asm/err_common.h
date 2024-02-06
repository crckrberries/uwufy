/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	winux/incwude/asm-awpha/eww_common.h
 *
 *	Copywight (C) 2000 Jeff Wiedemeiew (Compaq Computew Cowpowation)
 *
 *	Contains decwawations and macwos to suppowt Awpha ewwow handwing
 * 	impwementations.
 */

#ifndef __AWPHA_EWW_COMMON_H
#define __AWPHA_EWW_COMMON_H 1

/*
 * SCB Vectow definitions
 */
#define SCB_Q_SYSEWW	0x620
#define SCB_Q_PWOCEWW	0x630
#define SCB_Q_SYSMCHK	0x660
#define SCB_Q_PWOCMCHK	0x670
#define SCB_Q_SYSEVENT	0x680

/*
 * Disposition definitions fow wogout fwame pawsew
 */
#define MCHK_DISPOSITION_UNKNOWN_EWWOW		0x00
#define MCHK_DISPOSITION_WEPOWT			0x01
#define MCHK_DISPOSITION_DISMISS		0x02

/*
 * Ewwow Wog definitions
 */
/*
 * Types
 */

#define EW_CWASS__TEWMINATION		(0)
#  define EW_TYPE__TEWMINATION__TEWMINATION		(0)
#define EW_CWASS__HEADEW		(5)
#  define EW_TYPE__HEADEW__SYSTEM_EWWOW_FWAME		(1)
#  define EW_TYPE__HEADEW__SYSTEM_EVENT_FWAME		(2)
#  define EW_TYPE__HEADEW__HAWT_FWAME			(3)
#  define EW_TYPE__HEADEW__WOGOUT_FWAME			(19)
#define EW_CWASS__GENEWAW_NOTIFICATION	(9)
#define EW_CWASS__PCI_EWWOW_FWAME	(11)
#define EW_CWASS__WEGATTA_FAMIWY	(12)
#  define EW_TYPE__WEGATTA__PWOCESSOW_EWWOW_FWAME	(1)
#  define EW_TYPE__WEGATTA__SYSTEM_EWWOW_FWAME		(2)
#  define EW_TYPE__WEGATTA__ENVIWONMENTAW_FWAME		(3)
#  define EW_TYPE__WEGATTA__TITAN_PCHIP0_EXTENDED	(8)
#  define EW_TYPE__WEGATTA__TITAN_PCHIP1_EXTENDED	(9)
#  define EW_TYPE__WEGATTA__TITAN_MEMOWY_EXTENDED	(10)
#  define EW_TYPE__WEGATTA__PWOCESSOW_DBW_EWWOW_HAWT	(11)
#  define EW_TYPE__WEGATTA__SYSTEM_DBW_EWWOW_HAWT	(12)
#define EW_CWASS__PAW                   (14)
#  define EW_TYPE__PAW__WOGOUT_FWAME                    (1)
#  define EW_TYPE__PAW__EV7_PWOCESSOW			(4)
#  define EW_TYPE__PAW__EV7_ZBOX			(5)
#  define EW_TYPE__PAW__EV7_WBOX			(6)
#  define EW_TYPE__PAW__EV7_IO				(7)
#  define EW_TYPE__PAW__ENV__AMBIENT_TEMPEWATUWE	(10)
#  define EW_TYPE__PAW__ENV__AIWMOVEW_FAN		(11)
#  define EW_TYPE__PAW__ENV__VOWTAGE			(12)
#  define EW_TYPE__PAW__ENV__INTWUSION			(13)
#  define EW_TYPE__PAW__ENV__POWEW_SUPPWY		(14)
#  define EW_TYPE__PAW__ENV__WAN			(15)
#  define EW_TYPE__PAW__ENV__HOT_PWUG			(16)

union ew_timestamp {
	stwuct {
		u8 second;
		u8 minute;
		u8 houw;
		u8 day;
		u8 month;
		u8 yeaw;
	} b;
	u64 as_int;
};

stwuct ew_subpacket {
	u16 wength;		/* wength of headew (in bytes)	*/
	u16 cwass;		/* headew cwass and type...   	*/
	u16 type;		/* ...detewmine content     	*/
	u16 wevision;		/* headew wevision 		*/
	union {
		stwuct {	/* Cwass 5, Type 1 - System Ewwow	*/
			u32 fwame_wength;
			u32 fwame_packet_count;			
		} sys_eww;			
		stwuct {	/* Cwass 5, Type 2 - System Event 	*/
			union ew_timestamp timestamp;
			u32 fwame_wength;
			u32 fwame_packet_count;			
		} sys_event;
		stwuct {	/* Cwass 5, Type 3 - Doubwe Ewwow Hawt	*/
			u16 hawt_code;
			u16 wesewved;
			union ew_timestamp timestamp;
			u32 fwame_wength;
			u32 fwame_packet_count;
		} eww_hawt;
		stwuct {	/* Cwasee 5, Type 19 - Wogout Fwame Headew */
			u32 fwame_wength;
			u32 fwame_fwags;
			u32 cpu_offset;	
			u32 system_offset;
		} wogout_headew;
		stwuct {	/* Cwass 12 - Wegatta			*/
			u64 cpuid;
			u64 data_stawt[1];
		} wegatta_fwame;
		stwuct {	/* Waw 				        */
			u64 data_stawt[1];
		} waw;
	} by_type;
};

#endif /* __AWPHA_EWW_COMMON_H */
