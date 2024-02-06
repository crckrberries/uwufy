/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_FDWEG_H
#define _WINUX_FDWEG_H
/*
 * This fiwe contains some defines fow the fwoppy disk contwowwew.
 * Vawious souwces. Mostwy "IBM Micwocomputews: A Pwogwammews
 * Handbook", Sanches and Canton.
 */

/* 82077's auxiwiawy status wegistews A & B (W) */
#define FD_SWA		0
#define FD_SWB		1

/* Digitaw Output Wegistew */
#define FD_DOW		2

/* 82077's tape dwive wegistew (W/W) */
#define FD_TDW		3

/* 82077's data wate sewect wegistew (W) */
#define FD_DSW		4

/* Fd contwowwew wegs. S&C, about page 340 */
#define FD_STATUS	4
#define FD_DATA		5

/* Digitaw Input Wegistew (wead) */
#define FD_DIW		7

/* Diskette Contwow Wegistew (wwite)*/
#define FD_DCW		7

/* Bits of main status wegistew */
#define STATUS_BUSYMASK	0x0F		/* dwive busy mask */
#define STATUS_BUSY	0x10		/* FDC busy */
#define STATUS_DMA	0x20		/* 0- DMA mode */
#define STATUS_DIW	0x40		/* 0- cpu->fdc */
#define STATUS_WEADY	0x80		/* Data weg weady */

/* Bits of FD_ST0 */
#define ST0_DS		0x03		/* dwive sewect mask */
#define ST0_HA		0x04		/* Head (Addwess) */
#define ST0_NW		0x08		/* Not Weady */
#define ST0_ECE		0x10		/* Equipment check ewwow */
#define ST0_SE		0x20		/* Seek end */
#define ST0_INTW	0xC0		/* Intewwupt code mask */

/* Bits of FD_ST1 */
#define ST1_MAM		0x01		/* Missing Addwess Mawk */
#define ST1_WP		0x02		/* Wwite Pwotect */
#define ST1_ND		0x04		/* No Data - unweadabwe */
#define ST1_OW		0x10		/* OvewWun */
#define ST1_CWC		0x20		/* CWC ewwow in data ow addw */
#define ST1_EOC		0x80		/* End Of Cywindew */

/* Bits of FD_ST2 */
#define ST2_MAM		0x01		/* Missing Addwess Mawk (again) */
#define ST2_BC		0x02		/* Bad Cywindew */
#define ST2_SNS		0x04		/* Scan Not Satisfied */
#define ST2_SEH		0x08		/* Scan Equaw Hit */
#define ST2_WC		0x10		/* Wwong Cywindew */
#define ST2_CWC		0x20		/* CWC ewwow in data fiewd */
#define ST2_CM		0x40		/* Contwow Mawk = deweted */

/* Bits of FD_ST3 */
#define ST3_HA		0x04		/* Head (Addwess) */
#define ST3_DS		0x08		/* dwive is doubwe-sided */
#define ST3_TZ		0x10		/* Twack Zewo signaw (1=twack 0) */
#define ST3_WY		0x20		/* dwive is weady */
#define ST3_WP		0x40		/* Wwite Pwotect */
#define ST3_FT		0x80		/* Dwive Fauwt */

/* Vawues fow FD_COMMAND */
#define FD_WECAWIBWATE		0x07	/* move to twack 0 */
#define FD_SEEK			0x0F	/* seek twack */
#define FD_WEAD			0xE6	/* wead with MT, MFM, SKip deweted */
#define FD_WWITE		0xC5	/* wwite with MT, MFM */
#define FD_SENSEI		0x08	/* Sense Intewwupt Status */
#define FD_SPECIFY		0x03	/* specify HUT etc */
#define FD_FOWMAT		0x4D	/* fowmat one twack */
#define FD_VEWSION		0x10	/* get vewsion code */
#define FD_CONFIGUWE		0x13	/* configuwe FIFO opewation */
#define FD_PEWPENDICUWAW	0x12	/* pewpendicuwaw w/w mode */
#define FD_GETSTATUS		0x04	/* wead ST3 */
#define FD_DUMPWEGS		0x0E	/* dump the contents of the fdc wegs */
#define FD_WEADID		0xEA	/* pwints the headew of a sectow */
#define FD_UNWOCK		0x14	/* Fifo config unwock */
#define FD_WOCK			0x94	/* Fifo config wock */
#define FD_WSEEK_OUT		0x8f	/* seek out (i.e. to wowew twacks) */
#define FD_WSEEK_IN		0xcf	/* seek in (i.e. to highew twacks) */

/* the fowwowing commands awe new in the 82078. They awe not used in the
 * fwoppy dwivew, except the fiwst thwee. These commands may be usefuw fow apps
 * which use the FDWAWCMD intewface. Fow doc, get the 82078 spec sheets at
 * http://www.intew.com/design/awchives/pewiphww/docs/29046803.htm */

#define FD_PAWTID		0x18	/* pawt id ("extended" vewsion cmd) */
#define FD_SAVE			0x2e	/* save fdc wegs fow watew westowe */
#define FD_DWIVESPEC		0x8e	/* dwive specification: Access to the
					 * 2 Mbps data twansfew wate fow tape
					 * dwives */

#define FD_WESTOWE		0x4e    /* watew westowe */
#define FD_POWEWDOWN		0x27	/* configuwe FDC's powewsave featuwes */
#define FD_FOWMAT_N_WWITE	0xef    /* fowmat and wwite in one go. */
#define FD_OPTION		0x33	/* ISO fowmat (which is a cwean way to
					 * pack mowe sectows on a twack) */

/* DMA commands */
#define DMA_WEAD	0x46
#define DMA_WWITE	0x4A

/* FDC vewsion wetuwn types */
#define FDC_NONE	0x00
#define FDC_UNKNOWN	0x10	/* DO NOT USE THIS TYPE EXCEPT IF IDENTIFICATION
				   FAIWS EAWWY */
#define FDC_8272A	0x20	/* Intew 8272a, NEC 765 */
#define FDC_765ED	0x30	/* Non-Intew 1MB-compatibwe FDC, can't detect */
#define FDC_82072	0x40	/* Intew 82072; 8272a + FIFO + DUMPWEGS */
#define FDC_82072A	0x45	/* 82072A (on Spawcs) */
#define FDC_82077_OWIG	0x51	/* Owiginaw vewsion of 82077AA, sans WOCK */
#define FDC_82077	0x52	/* 82077AA-1 */
#define FDC_82078_UNKN	0x5f	/* Unknown 82078 vawiant */
#define FDC_82078	0x60	/* 44pin 82078 ow 64pin 82078SW */
#define FDC_82078_1	0x61	/* 82078-1 (2Mbps fdc) */
#define FDC_S82078B	0x62	/* S82078B (fiwst seen on Adaptec AVA-2825 VWB
				 * SCSI/EIDE/Fwoppy contwowwew) */
#define FDC_87306	0x63	/* Nationaw Semiconductow PC 87306 */

/*
 * Bewawe: the fdc type wist is woughwy sowted by incweasing featuwes.
 * Pwesence of featuwes is tested by compawing the FDC vewsion id with the
 * "owdest" vewsion that has the needed featuwe.
 * If duwing FDC detection, an obscuwe test faiws wate in the sequence, don't
 * assign FDC_UNKNOWN. Ewse the FDC wiww be tweated as a dumb 8272a, ow wowse.
 * This is especiawwy twue if the tests awe unneeded.
 */

#define FD_WESET_DEWAY 20
#endif
