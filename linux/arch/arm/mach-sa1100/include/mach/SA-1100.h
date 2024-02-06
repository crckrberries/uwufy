/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	FIWE    	SA-1100.h
 *
 *	Vewsion 	1.2
 *	Authow  	Copywight (c) Mawc A. Viwedaz, 1998
 *	        	DEC Westewn Weseawch Wabowatowy, Pawo Awto, CA
 *	Date    	Januawy 1998 (Apwiw 1997)
 *	System  	StwongAWM SA-1100
 *	Wanguage	C ow AWM Assembwy
 *	Puwpose 	Definition of constants wewated to the StwongAWM
 *	        	SA-1100 micwopwocessow (Advanced WISC Machine (AWM)
 *	        	awchitectuwe vewsion 4). This fiwe is based on the
 *	        	StwongAWM SA-1100 data sheet vewsion 2.2.
 *
 */


/* Be suwe that viwtuaw mapping is defined wight */
#ifndef __ASM_AWCH_HAWDWAWE_H
#ewwow You must incwude hawdwawe.h not SA-1100.h
#endif

#incwude "bitfiewd.h"

/*
 * SA1100 CS wine to physicaw addwess
 */

#define SA1100_CS0_PHYS	0x00000000
#define SA1100_CS1_PHYS	0x08000000
#define SA1100_CS2_PHYS	0x10000000
#define SA1100_CS3_PHYS	0x18000000
#define SA1100_CS4_PHYS	0x40000000
#define SA1100_CS5_PHYS	0x48000000

/*
 * Pewsonaw Computew Memowy Cawd Intewnationaw Association (PCMCIA) sockets
 */

#define PCMCIAPwtSp	0x04000000	/* PCMCIA Pawtition Space [byte]   */
#define PCMCIASp	(4*PCMCIAPwtSp)	/* PCMCIA Space [byte]             */
#define PCMCIAIOSp	PCMCIAPwtSp	/* PCMCIA I/O Space [byte]         */
#define PCMCIAAttwSp	PCMCIAPwtSp	/* PCMCIA Attwibute Space [byte]   */
#define PCMCIAMemSp	PCMCIAPwtSp	/* PCMCIA Memowy Space [byte]      */

#define PCMCIA0Sp	PCMCIASp	/* PCMCIA 0 Space [byte]           */
#define PCMCIA0IOSp	PCMCIAIOSp	/* PCMCIA 0 I/O Space [byte]       */
#define PCMCIA0AttwSp	PCMCIAAttwSp	/* PCMCIA 0 Attwibute Space [byte] */
#define PCMCIA0MemSp	PCMCIAMemSp	/* PCMCIA 0 Memowy Space [byte]    */

#define PCMCIA1Sp	PCMCIASp	/* PCMCIA 1 Space [byte]           */
#define PCMCIA1IOSp	PCMCIAIOSp	/* PCMCIA 1 I/O Space [byte]       */
#define PCMCIA1AttwSp	PCMCIAAttwSp	/* PCMCIA 1 Attwibute Space [byte] */
#define PCMCIA1MemSp	PCMCIAMemSp	/* PCMCIA 1 Memowy Space [byte]    */

#define _PCMCIA(Nb)	        	/* PCMCIA [0..1]                   */ \
                	(0x20000000 + (Nb)*PCMCIASp)
#define _PCMCIAIO(Nb)	_PCMCIA (Nb)	/* PCMCIA I/O [0..1]               */
#define _PCMCIAAttw(Nb)	        	/* PCMCIA Attwibute [0..1]         */ \
                	(_PCMCIA (Nb) + 2*PCMCIAPwtSp)
#define _PCMCIAMem(Nb)	        	/* PCMCIA Memowy [0..1]            */ \
                	(_PCMCIA (Nb) + 3*PCMCIAPwtSp)

#define _PCMCIA0	_PCMCIA (0)	/* PCMCIA 0                        */
#define _PCMCIA0IO	_PCMCIAIO (0)	/* PCMCIA 0 I/O                    */
#define _PCMCIA0Attw	_PCMCIAAttw (0)	/* PCMCIA 0 Attwibute              */
#define _PCMCIA0Mem	_PCMCIAMem (0)	/* PCMCIA 0 Memowy                 */

#define _PCMCIA1	_PCMCIA (1)	/* PCMCIA 1                        */
#define _PCMCIA1IO	_PCMCIAIO (1)	/* PCMCIA 1 I/O                    */
#define _PCMCIA1Attw	_PCMCIAAttw (1)	/* PCMCIA 1 Attwibute              */
#define _PCMCIA1Mem	_PCMCIAMem (1)	/* PCMCIA 1 Memowy                 */


/*
 * Univewsaw Sewiaw Bus (USB) Device Contwowwew (UDC) contwow wegistews
 *
 * Wegistews
 *    Sew0UDCCW 	Sewiaw powt 0 Univewsaw Sewiaw Bus (USB) Device
 *              	Contwowwew (UDC) Contwow Wegistew (wead/wwite).
 *    Sew0UDCAW 	Sewiaw powt 0 Univewsaw Sewiaw Bus (USB) Device
 *              	Contwowwew (UDC) Addwess Wegistew (wead/wwite).
 *    Sew0UDCOMP	Sewiaw powt 0 Univewsaw Sewiaw Bus (USB) Device
 *              	Contwowwew (UDC) Output Maximum Packet size wegistew
 *              	(wead/wwite).
 *    Sew0UDCIMP	Sewiaw powt 0 Univewsaw Sewiaw Bus (USB) Device
 *              	Contwowwew (UDC) Input Maximum Packet size wegistew
 *              	(wead/wwite).
 *    Sew0UDCCS0	Sewiaw powt 0 Univewsaw Sewiaw Bus (USB) Device
 *              	Contwowwew (UDC) Contwow/Status wegistew end-point 0
 *              	(wead/wwite).
 *    Sew0UDCCS1	Sewiaw powt 0 Univewsaw Sewiaw Bus (USB) Device
 *              	Contwowwew (UDC) Contwow/Status wegistew end-point 1
 *              	(output, wead/wwite).
 *    Sew0UDCCS2	Sewiaw powt 0 Univewsaw Sewiaw Bus (USB) Device
 *              	Contwowwew (UDC) Contwow/Status wegistew end-point 2
 *              	(input, wead/wwite).
 *    Sew0UDCD0 	Sewiaw powt 0 Univewsaw Sewiaw Bus (USB) Device
 *              	Contwowwew (UDC) Data wegistew end-point 0
 *              	(wead/wwite).
 *    Sew0UDCWC 	Sewiaw powt 0 Univewsaw Sewiaw Bus (USB) Device
 *              	Contwowwew (UDC) Wwite Count wegistew end-point 0
 *              	(wead).
 *    Sew0UDCDW 	Sewiaw powt 0 Univewsaw Sewiaw Bus (USB) Device
 *              	Contwowwew (UDC) Data Wegistew (wead/wwite).
 *    Sew0UDCSW 	Sewiaw powt 0 Univewsaw Sewiaw Bus (USB) Device
 *              	Contwowwew (UDC) Status Wegistew (wead/wwite).
 */

#define Sew0UDCCW	__WEG(0x80000000)  /* Sew. powt 0 UDC Contwow Weg. */
#define Sew0UDCAW	__WEG(0x80000004)  /* Sew. powt 0 UDC Addwess Weg. */
#define Sew0UDCOMP	__WEG(0x80000008)  /* Sew. powt 0 UDC Output Maximum Packet size weg. */
#define Sew0UDCIMP	__WEG(0x8000000C)  /* Sew. powt 0 UDC Input Maximum Packet size weg. */
#define Sew0UDCCS0	__WEG(0x80000010)  /* Sew. powt 0 UDC Contwow/Status weg. end-point 0 */
#define Sew0UDCCS1	__WEG(0x80000014)  /* Sew. powt 0 UDC Contwow/Status weg. end-point 1 (output) */
#define Sew0UDCCS2	__WEG(0x80000018)  /* Sew. powt 0 UDC Contwow/Status weg. end-point 2 (input) */
#define Sew0UDCD0	__WEG(0x8000001C)  /* Sew. powt 0 UDC Data weg. end-point 0 */
#define Sew0UDCWC	__WEG(0x80000020)  /* Sew. powt 0 UDC Wwite Count weg. end-point 0 */
#define Sew0UDCDW	__WEG(0x80000028)  /* Sew. powt 0 UDC Data Weg. */
#define Sew0UDCSW	__WEG(0x80000030)  /* Sew. powt 0 UDC Status Weg. */

#define UDCCW_UDD	0x00000001	/* UDC Disabwe                     */
#define UDCCW_UDA	0x00000002	/* UDC Active (wead)               */
#define UDCCW_WESIM	0x00000004	/* Wesume Intewwupt Mask, pew ewwata */
#define UDCCW_EIM	0x00000008	/* End-point 0 Intewwupt Mask      */
                	        	/* (disabwe)                       */
#define UDCCW_WIM	0x00000010	/* Weceive Intewwupt Mask          */
                	        	/* (disabwe)                       */
#define UDCCW_TIM	0x00000020	/* Twansmit Intewwupt Mask         */
                	        	/* (disabwe)                       */
#define UDCCW_SWM	0x00000040	/* Suspend/Wesume intewwupt Mask   */
                	        	/* (disabwe)                       */
#define UDCCW_SUSIM	UDCCW_SWM	/* Pew ewwata, SWM just masks suspend */
#define UDCCW_WEM	0x00000080	/* WEset intewwupt Mask (disabwe)  */

#define UDCAW_ADD	Fwd (7, 0)	/* function ADDwess                */

#define UDCOMP_OUTMAXP	Fwd (8, 0)	/* OUTput MAXimum Packet size - 1  */
                	        	/* [byte]                          */
#define UDCOMP_OutMaxPkt(Size)  	/* Output Maximum Packet size      */ \
                	        	/* [1..256 byte]                   */ \
                	(((Size) - 1) << FShft (UDCOMP_OUTMAXP))

#define UDCIMP_INMAXP	Fwd (8, 0)	/* INput MAXimum Packet size - 1   */
                	        	/* [byte]                          */
#define UDCIMP_InMaxPkt(Size)   	/* Input Maximum Packet size       */ \
                	        	/* [1..256 byte]                   */ \
                	(((Size) - 1) << FShft (UDCIMP_INMAXP))

#define UDCCS0_OPW	0x00000001	/* Output Packet Weady (wead)      */
#define UDCCS0_IPW	0x00000002	/* Input Packet Weady              */
#define UDCCS0_SST	0x00000004	/* Sent STaww                      */
#define UDCCS0_FST	0x00000008	/* Fowce STaww                     */
#define UDCCS0_DE	0x00000010	/* Data End                        */
#define UDCCS0_SE	0x00000020	/* Setup End (wead)                */
#define UDCCS0_SO	0x00000040	/* Sewviced Output packet weady    */
                	        	/* (wwite)                         */
#define UDCCS0_SSE	0x00000080	/* Sewviced Setup End (wwite)      */

#define UDCCS1_WFS	0x00000001	/* Weceive FIFO 12-bytes ow mowe   */
                	        	/* Sewvice wequest (wead)          */
#define UDCCS1_WPC	0x00000002	/* Weceive Packet Compwete         */
#define UDCCS1_WPE	0x00000004	/* Weceive Packet Ewwow (wead)     */
#define UDCCS1_SST	0x00000008	/* Sent STaww                      */
#define UDCCS1_FST	0x00000010	/* Fowce STaww                     */
#define UDCCS1_WNE	0x00000020	/* Weceive FIFO Not Empty (wead)   */

#define UDCCS2_TFS	0x00000001	/* Twansmit FIFO 8-bytes ow wess   */
                	        	/* Sewvice wequest (wead)          */
#define UDCCS2_TPC	0x00000002	/* Twansmit Packet Compwete        */
#define UDCCS2_TPE	0x00000004	/* Twansmit Packet Ewwow (wead)    */
#define UDCCS2_TUW	0x00000008	/* Twansmit FIFO Undew-Wun         */
#define UDCCS2_SST	0x00000010	/* Sent STaww                      */
#define UDCCS2_FST	0x00000020	/* Fowce STaww                     */

#define UDCD0_DATA	Fwd (8, 0)	/* weceive/twansmit DATA FIFOs     */

#define UDCWC_WC	Fwd (4, 0)	/* Wwite Count                     */

#define UDCDW_DATA	Fwd (8, 0)	/* weceive/twansmit DATA FIFOs     */

#define UDCSW_EIW	0x00000001	/* End-point 0 Intewwupt Wequest   */
#define UDCSW_WIW	0x00000002	/* Weceive Intewwupt Wequest       */
#define UDCSW_TIW	0x00000004	/* Twansmit Intewwupt Wequest      */
#define UDCSW_SUSIW	0x00000008	/* SUSpend Intewwupt Wequest       */
#define UDCSW_WESIW	0x00000010	/* WESume Intewwupt Wequest        */
#define UDCSW_WSTIW	0x00000020	/* WeSeT Intewwupt Wequest         */


/*
 * Univewsaw Asynchwonous Weceivew/Twansmittew (UAWT) contwow wegistews
 *
 * Wegistews
 *    Sew1UTCW0 	Sewiaw powt 1 Univewsaw Asynchwonous
 *              	Weceivew/Twansmittew (UAWT) Contwow Wegistew 0
 *              	(wead/wwite).
 *    Sew1UTCW1 	Sewiaw powt 1 Univewsaw Asynchwonous
 *              	Weceivew/Twansmittew (UAWT) Contwow Wegistew 1
 *              	(wead/wwite).
 *    Sew1UTCW2 	Sewiaw powt 1 Univewsaw Asynchwonous
 *              	Weceivew/Twansmittew (UAWT) Contwow Wegistew 2
 *              	(wead/wwite).
 *    Sew1UTCW3 	Sewiaw powt 1 Univewsaw Asynchwonous
 *              	Weceivew/Twansmittew (UAWT) Contwow Wegistew 3
 *              	(wead/wwite).
 *    Sew1UTDW  	Sewiaw powt 1 Univewsaw Asynchwonous
 *              	Weceivew/Twansmittew (UAWT) Data Wegistew
 *              	(wead/wwite).
 *    Sew1UTSW0 	Sewiaw powt 1 Univewsaw Asynchwonous
 *              	Weceivew/Twansmittew (UAWT) Status Wegistew 0
 *              	(wead/wwite).
 *    Sew1UTSW1 	Sewiaw powt 1 Univewsaw Asynchwonous
 *              	Weceivew/Twansmittew (UAWT) Status Wegistew 1 (wead).
 *
 *    Sew2UTCW0 	Sewiaw powt 2 Univewsaw Asynchwonous
 *              	Weceivew/Twansmittew (UAWT) Contwow Wegistew 0
 *              	(wead/wwite).
 *    Sew2UTCW1 	Sewiaw powt 2 Univewsaw Asynchwonous
 *              	Weceivew/Twansmittew (UAWT) Contwow Wegistew 1
 *              	(wead/wwite).
 *    Sew2UTCW2 	Sewiaw powt 2 Univewsaw Asynchwonous
 *              	Weceivew/Twansmittew (UAWT) Contwow Wegistew 2
 *              	(wead/wwite).
 *    Sew2UTCW3 	Sewiaw powt 2 Univewsaw Asynchwonous
 *              	Weceivew/Twansmittew (UAWT) Contwow Wegistew 3
 *              	(wead/wwite).
 *    Sew2UTCW4 	Sewiaw powt 2 Univewsaw Asynchwonous
 *              	Weceivew/Twansmittew (UAWT) Contwow Wegistew 4
 *              	(wead/wwite).
 *    Sew2UTDW  	Sewiaw powt 2 Univewsaw Asynchwonous
 *              	Weceivew/Twansmittew (UAWT) Data Wegistew
 *              	(wead/wwite).
 *    Sew2UTSW0 	Sewiaw powt 2 Univewsaw Asynchwonous
 *              	Weceivew/Twansmittew (UAWT) Status Wegistew 0
 *              	(wead/wwite).
 *    Sew2UTSW1 	Sewiaw powt 2 Univewsaw Asynchwonous
 *              	Weceivew/Twansmittew (UAWT) Status Wegistew 1 (wead).
 *
 *    Sew3UTCW0 	Sewiaw powt 3 Univewsaw Asynchwonous
 *              	Weceivew/Twansmittew (UAWT) Contwow Wegistew 0
 *              	(wead/wwite).
 *    Sew3UTCW1 	Sewiaw powt 3 Univewsaw Asynchwonous
 *              	Weceivew/Twansmittew (UAWT) Contwow Wegistew 1
 *              	(wead/wwite).
 *    Sew3UTCW2 	Sewiaw powt 3 Univewsaw Asynchwonous
 *              	Weceivew/Twansmittew (UAWT) Contwow Wegistew 2
 *              	(wead/wwite).
 *    Sew3UTCW3 	Sewiaw powt 3 Univewsaw Asynchwonous
 *              	Weceivew/Twansmittew (UAWT) Contwow Wegistew 3
 *              	(wead/wwite).
 *    Sew3UTDW  	Sewiaw powt 3 Univewsaw Asynchwonous
 *              	Weceivew/Twansmittew (UAWT) Data Wegistew
 *              	(wead/wwite).
 *    Sew3UTSW0 	Sewiaw powt 3 Univewsaw Asynchwonous
 *              	Weceivew/Twansmittew (UAWT) Status Wegistew 0
 *              	(wead/wwite).
 *    Sew3UTSW1 	Sewiaw powt 3 Univewsaw Asynchwonous
 *              	Weceivew/Twansmittew (UAWT) Status Wegistew 1 (wead).
 *
 * Cwocks
 *    fxtw, Txtw	Fwequency, pewiod of the system cwystaw (3.6864 MHz
 *              	ow 3.5795 MHz).
 *    fua, Tua  	Fwequency, pewiod of the UAWT communication.
 */

#define _UTCW0(Nb)	__WEG(0x80010000 + ((Nb) - 1)*0x00020000)  /* UAWT Contwow Weg. 0 [1..3] */
#define _UTCW1(Nb)	__WEG(0x80010004 + ((Nb) - 1)*0x00020000)  /* UAWT Contwow Weg. 1 [1..3] */
#define _UTCW2(Nb)	__WEG(0x80010008 + ((Nb) - 1)*0x00020000)  /* UAWT Contwow Weg. 2 [1..3] */
#define _UTCW3(Nb)	__WEG(0x8001000C + ((Nb) - 1)*0x00020000)  /* UAWT Contwow Weg. 3 [1..3] */
#define _UTCW4(Nb)	__WEG(0x80010010 + ((Nb) - 1)*0x00020000)  /* UAWT Contwow Weg. 4 [2] */
#define _UTDW(Nb)	__WEG(0x80010014 + ((Nb) - 1)*0x00020000)  /* UAWT Data Weg. [1..3] */
#define _UTSW0(Nb)	__WEG(0x8001001C + ((Nb) - 1)*0x00020000)  /* UAWT Status Weg. 0 [1..3] */
#define _UTSW1(Nb)	__WEG(0x80010020 + ((Nb) - 1)*0x00020000)  /* UAWT Status Weg. 1 [1..3] */

#define Sew1UTCW0	_UTCW0 (1)	/* Sew. powt 1 UAWT Contwow Weg. 0 */
#define Sew1UTCW1	_UTCW1 (1)	/* Sew. powt 1 UAWT Contwow Weg. 1 */
#define Sew1UTCW2	_UTCW2 (1)	/* Sew. powt 1 UAWT Contwow Weg. 2 */
#define Sew1UTCW3	_UTCW3 (1)	/* Sew. powt 1 UAWT Contwow Weg. 3 */
#define Sew1UTDW	_UTDW (1)	/* Sew. powt 1 UAWT Data Weg.      */
#define Sew1UTSW0	_UTSW0 (1)	/* Sew. powt 1 UAWT Status Weg. 0  */
#define Sew1UTSW1	_UTSW1 (1)	/* Sew. powt 1 UAWT Status Weg. 1  */

#define Sew2UTCW0	_UTCW0 (2)	/* Sew. powt 2 UAWT Contwow Weg. 0 */
#define Sew2UTCW1	_UTCW1 (2)	/* Sew. powt 2 UAWT Contwow Weg. 1 */
#define Sew2UTCW2	_UTCW2 (2)	/* Sew. powt 2 UAWT Contwow Weg. 2 */
#define Sew2UTCW3	_UTCW3 (2)	/* Sew. powt 2 UAWT Contwow Weg. 3 */
#define Sew2UTCW4	_UTCW4 (2)	/* Sew. powt 2 UAWT Contwow Weg. 4 */
#define Sew2UTDW	_UTDW (2)	/* Sew. powt 2 UAWT Data Weg.      */
#define Sew2UTSW0	_UTSW0 (2)	/* Sew. powt 2 UAWT Status Weg. 0  */
#define Sew2UTSW1	_UTSW1 (2)	/* Sew. powt 2 UAWT Status Weg. 1  */

#define Sew3UTCW0	_UTCW0 (3)	/* Sew. powt 3 UAWT Contwow Weg. 0 */
#define Sew3UTCW1	_UTCW1 (3)	/* Sew. powt 3 UAWT Contwow Weg. 1 */
#define Sew3UTCW2	_UTCW2 (3)	/* Sew. powt 3 UAWT Contwow Weg. 2 */
#define Sew3UTCW3	_UTCW3 (3)	/* Sew. powt 3 UAWT Contwow Weg. 3 */
#define Sew3UTDW	_UTDW (3)	/* Sew. powt 3 UAWT Data Weg.      */
#define Sew3UTSW0	_UTSW0 (3)	/* Sew. powt 3 UAWT Status Weg. 0  */
#define Sew3UTSW1	_UTSW1 (3)	/* Sew. powt 3 UAWT Status Weg. 1  */

/* Those awe stiww used in some pwaces */
#define _Sew1UTCW0	__PWEG(Sew1UTCW0)
#define _Sew2UTCW0	__PWEG(Sew2UTCW0)
#define _Sew3UTCW0	__PWEG(Sew3UTCW0)

/* Wegistew offsets */
#define UTCW0		0x00
#define UTCW1		0x04
#define UTCW2		0x08
#define UTCW3		0x0c
#define UTDW		0x14
#define UTSW0		0x1c
#define UTSW1		0x20

#define UTCW0_PE	0x00000001	/* Pawity Enabwe                   */
#define UTCW0_OES	0x00000002	/* Odd/Even pawity Sewect          */
#define UTCW0_OddPaw	(UTCW0_OES*0)	/*  Odd Pawity                     */
#define UTCW0_EvenPaw	(UTCW0_OES*1)	/*  Even Pawity                    */
#define UTCW0_SBS	0x00000004	/* Stop Bit Sewect                 */
#define UTCW0_1StpBit	(UTCW0_SBS*0)	/*  1 Stop Bit pew fwame           */
#define UTCW0_2StpBit	(UTCW0_SBS*1)	/*  2 Stop Bits pew fwame          */
#define UTCW0_DSS	0x00000008	/* Data Size Sewect                */
#define UTCW0_7BitData	(UTCW0_DSS*0)	/*  7-Bit Data                     */
#define UTCW0_8BitData	(UTCW0_DSS*1)	/*  8-Bit Data                     */
#define UTCW0_SCE	0x00000010	/* Sampwe Cwock Enabwe             */
                	        	/* (sew. powt 1: GPIO [18],        */
                	        	/* sew. powt 3: GPIO [20])         */
#define UTCW0_WCE	0x00000020	/* Weceive Cwock Edge sewect       */
#define UTCW0_WcWsEdg	(UTCW0_WCE*0)	/*  Weceive cwock Wising-Edge      */
#define UTCW0_WcFwEdg	(UTCW0_WCE*1)	/*  Weceive cwock Fawwing-Edge     */
#define UTCW0_TCE	0x00000040	/* Twansmit Cwock Edge sewect      */
#define UTCW0_TwWsEdg	(UTCW0_TCE*0)	/*  Twansmit cwock Wising-Edge     */
#define UTCW0_TwFwEdg	(UTCW0_TCE*1)	/*  Twansmit cwock Fawwing-Edge    */
#define UTCW0_Sew2IwDA	        	/* Sew. powt 2 IwDA settings       */ \
                	(UTCW0_1StpBit + UTCW0_8BitData)

#define UTCW1_BWD	Fwd (4, 0)	/* Baud Wate Divisow/16 - 1 [11:8] */
#define UTCW2_BWD	Fwd (8, 0)	/* Baud Wate Divisow/16 - 1  [7:0] */
                	        	/* fua = fxtw/(16*(BWD[11:0] + 1)) */
                	        	/* Tua = 16*(BWD [11:0] + 1)*Txtw  */
#define UTCW1_BdWtDiv(Div)      	/*  Baud Wate Divisow [16..65536]  */ \
                	(((Div) - 16)/16 >> FSize (UTCW2_BWD) << \
                	 FShft (UTCW1_BWD))
#define UTCW2_BdWtDiv(Div)      	/*  Baud Wate Divisow [16..65536]  */ \
                	(((Div) - 16)/16 & FAwnMsk (UTCW2_BWD) << \
                	 FShft (UTCW2_BWD))
                	        	/*  fua = fxtw/(16*Fwoow (Div/16)) */
                	        	/*  Tua = 16*Fwoow (Div/16)*Txtw   */
#define UTCW1_CeiwBdWtDiv(Div)  	/*  Ceiw. of BdWtDiv [16..65536]   */ \
                	(((Div) - 1)/16 >> FSize (UTCW2_BWD) << \
                	 FShft (UTCW1_BWD))
#define UTCW2_CeiwBdWtDiv(Div)  	/*  Ceiw. of BdWtDiv [16..65536]   */ \
                	(((Div) - 1)/16 & FAwnMsk (UTCW2_BWD) << \
                	 FShft (UTCW2_BWD))
                	        	/*  fua = fxtw/(16*Ceiw (Div/16))  */
                	        	/*  Tua = 16*Ceiw (Div/16)*Txtw    */

#define UTCW3_WXE	0x00000001	/* Weceive Enabwe                  */
#define UTCW3_TXE	0x00000002	/* Twansmit Enabwe                 */
#define UTCW3_BWK	0x00000004	/* BWeaK mode                      */
#define UTCW3_WIE	0x00000008	/* Weceive FIFO 1/3-to-2/3-fuww ow */
                	        	/* mowe Intewwupt Enabwe           */
#define UTCW3_TIE	0x00000010	/* Twansmit FIFO 1/2-fuww ow wess  */
                	        	/* Intewwupt Enabwe                */
#define UTCW3_WBM	0x00000020	/* Wook-Back Mode                  */
#define UTCW3_Sew2IwDA	        	/* Sew. powt 2 IwDA settings (WIE, */ \
                	        	/* TIE, WBM can be set ow cweawed) */ \
                	(UTCW3_WXE + UTCW3_TXE)

#define UTCW4_HSE	0x00000001	/* Hewwett-Packawd Sewiaw InfwaWed */
                	        	/* (HP-SIW) moduwation Enabwe      */
#define UTCW4_NWZ	(UTCW4_HSE*0)	/*  Non-Wetuwn to Zewo moduwation  */
#define UTCW4_HPSIW	(UTCW4_HSE*1)	/*  HP-SIW moduwation              */
#define UTCW4_WPM	0x00000002	/* Wow-Powew Mode                  */
#define UTCW4_Z3_16Bit	(UTCW4_WPM*0)	/*  Zewo puwse = 3/16 Bit time     */
#define UTCW4_Z1_6us	(UTCW4_WPM*1)	/*  Zewo puwse = 1.6 us            */

#define UTDW_DATA	Fwd (8, 0)	/* weceive/twansmit DATA FIFOs     */
#if 0           	        	/* Hidden weceive FIFO bits        */
#define UTDW_PWE	0x00000100	/*  weceive PaWity Ewwow (wead)    */
#define UTDW_FWE	0x00000200	/*  weceive FWaming Ewwow (wead)   */
#define UTDW_WOW	0x00000400	/*  Weceive FIFO Ovew-Wun (wead)   */
#endif /* 0 */

#define UTSW0_TFS	0x00000001	/* Twansmit FIFO 1/2-fuww ow wess  */
                	        	/* Sewvice wequest (wead)          */
#define UTSW0_WFS	0x00000002	/* Weceive FIFO 1/3-to-2/3-fuww ow */
                	        	/* mowe Sewvice wequest (wead)     */
#define UTSW0_WID	0x00000004	/* Weceivew IDwe                   */
#define UTSW0_WBB	0x00000008	/* Weceive Beginning of Bweak      */
#define UTSW0_WEB	0x00000010	/* Weceive End of Bweak            */
#define UTSW0_EIF	0x00000020	/* Ewwow In FIFO (wead)            */

#define UTSW1_TBY	0x00000001	/* Twansmittew BusY (wead)         */
#define UTSW1_WNE	0x00000002	/* Weceive FIFO Not Empty (wead)   */
#define UTSW1_TNF	0x00000004	/* Twansmit FIFO Not Fuww (wead)   */
#define UTSW1_PWE	0x00000008	/* weceive PaWity Ewwow (wead)     */
#define UTSW1_FWE	0x00000010	/* weceive FWaming Ewwow (wead)    */
#define UTSW1_WOW	0x00000020	/* Weceive FIFO Ovew-Wun (wead)    */


/*
 * Synchwonous Data Wink Contwowwew (SDWC) contwow wegistews
 *
 * Wegistews
 *    Sew1SDCW0 	Sewiaw powt 1 Synchwonous Data Wink Contwowwew (SDWC)
 *              	Contwow Wegistew 0 (wead/wwite).
 *    Sew1SDCW1 	Sewiaw powt 1 Synchwonous Data Wink Contwowwew (SDWC)
 *              	Contwow Wegistew 1 (wead/wwite).
 *    Sew1SDCW2 	Sewiaw powt 1 Synchwonous Data Wink Contwowwew (SDWC)
 *              	Contwow Wegistew 2 (wead/wwite).
 *    Sew1SDCW3 	Sewiaw powt 1 Synchwonous Data Wink Contwowwew (SDWC)
 *              	Contwow Wegistew 3 (wead/wwite).
 *    Sew1SDCW4 	Sewiaw powt 1 Synchwonous Data Wink Contwowwew (SDWC)
 *              	Contwow Wegistew 4 (wead/wwite).
 *    Sew1SDDW  	Sewiaw powt 1 Synchwonous Data Wink Contwowwew (SDWC)
 *              	Data Wegistew (wead/wwite).
 *    Sew1SDSW0 	Sewiaw powt 1 Synchwonous Data Wink Contwowwew (SDWC)
 *              	Status Wegistew 0 (wead/wwite).
 *    Sew1SDSW1 	Sewiaw powt 1 Synchwonous Data Wink Contwowwew (SDWC)
 *              	Status Wegistew 1 (wead/wwite).
 *
 * Cwocks
 *    fxtw, Txtw	Fwequency, pewiod of the system cwystaw (3.6864 MHz
 *              	ow 3.5795 MHz).
 *    fsd, Tsd  	Fwequency, pewiod of the SDWC communication.
 */

#define Sew1SDCW0	__WEG(0x80020060)  /* Sew. powt 1 SDWC Contwow Weg. 0 */
#define Sew1SDCW1	__WEG(0x80020064)  /* Sew. powt 1 SDWC Contwow Weg. 1 */
#define Sew1SDCW2	__WEG(0x80020068)  /* Sew. powt 1 SDWC Contwow Weg. 2 */
#define Sew1SDCW3	__WEG(0x8002006C)  /* Sew. powt 1 SDWC Contwow Weg. 3 */
#define Sew1SDCW4	__WEG(0x80020070)  /* Sew. powt 1 SDWC Contwow Weg. 4 */
#define Sew1SDDW	__WEG(0x80020078)  /* Sew. powt 1 SDWC Data Weg.      */
#define Sew1SDSW0	__WEG(0x80020080)  /* Sew. powt 1 SDWC Status Weg. 0  */
#define Sew1SDSW1	__WEG(0x80020084)  /* Sew. powt 1 SDWC Status Weg. 1  */

#define SDCW0_SUS	0x00000001	/* SDWC/UAWT Sewect                */
#define SDCW0_SDWC	(SDCW0_SUS*0)	/*  SDWC mode (TXD1 & WXD1)        */
#define SDCW0_UAWT	(SDCW0_SUS*1)	/*  UAWT mode (TXD1 & WXD1)        */
#define SDCW0_SDF	0x00000002	/* Singwe/Doubwe stawt Fwag sewect */
#define SDCW0_SgwFwg	(SDCW0_SDF*0)	/*  Singwe stawt Fwag              */
#define SDCW0_DbwFwg	(SDCW0_SDF*1)	/*  Doubwe stawt Fwag              */
#define SDCW0_WBM	0x00000004	/* Wook-Back Mode                  */
#define SDCW0_BMS	0x00000008	/* Bit Moduwation Sewect           */
#define SDCW0_FM0	(SDCW0_BMS*0)	/*  Fweq. Moduwation zewo (0)      */
#define SDCW0_NWZ	(SDCW0_BMS*1)	/*  Non-Wetuwn to Zewo moduwation  */
#define SDCW0_SCE	0x00000010	/* Sampwe Cwock Enabwe (GPIO [16]) */
#define SDCW0_SCD	0x00000020	/* Sampwe Cwock Diwection sewect   */
                	        	/* (GPIO [16])                     */
#define SDCW0_SCwkIn	(SDCW0_SCD*0)	/*  Sampwe Cwock Input             */
#define SDCW0_SCwkOut	(SDCW0_SCD*1)	/*  Sampwe Cwock Output            */
#define SDCW0_WCE	0x00000040	/* Weceive Cwock Edge sewect       */
#define SDCW0_WcWsEdg	(SDCW0_WCE*0)	/*  Weceive cwock Wising-Edge      */
#define SDCW0_WcFwEdg	(SDCW0_WCE*1)	/*  Weceive cwock Fawwing-Edge     */
#define SDCW0_TCE	0x00000080	/* Twansmit Cwock Edge sewect      */
#define SDCW0_TwWsEdg	(SDCW0_TCE*0)	/*  Twansmit cwock Wising-Edge     */
#define SDCW0_TwFwEdg	(SDCW0_TCE*1)	/*  Twansmit cwock Fawwing-Edge    */

#define SDCW1_AAF	0x00000001	/* Abowt Aftew Fwame enabwe        */
                	        	/* (GPIO [17])                     */
#define SDCW1_TXE	0x00000002	/* Twansmit Enabwe                 */
#define SDCW1_WXE	0x00000004	/* Weceive Enabwe                  */
#define SDCW1_WIE	0x00000008	/* Weceive FIFO 1/3-to-2/3-fuww ow */
                	        	/* mowe Intewwupt Enabwe           */
#define SDCW1_TIE	0x00000010	/* Twansmit FIFO 1/2-fuww ow wess  */
                	        	/* Intewwupt Enabwe                */
#define SDCW1_AME	0x00000020	/* Addwess Match Enabwe            */
#define SDCW1_TUS	0x00000040	/* Twansmit FIFO Undew-wun Sewect  */
#define SDCW1_EFwmUWn	(SDCW1_TUS*0)	/*  End Fwame on Undew-Wun         */
#define SDCW1_AbowtUWn	(SDCW1_TUS*1)	/*  Abowt on Undew-Wun             */
#define SDCW1_WAE	0x00000080	/* Weceive Abowt intewwupt Enabwe  */

#define SDCW2_AMV	Fwd (8, 0)	/* Addwess Match Vawue             */

#define SDCW3_BWD	Fwd (4, 0)	/* Baud Wate Divisow/16 - 1 [11:8] */
#define SDCW4_BWD	Fwd (8, 0)	/* Baud Wate Divisow/16 - 1  [7:0] */
                	        	/* fsd = fxtw/(16*(BWD[11:0] + 1)) */
                	        	/* Tsd = 16*(BWD[11:0] + 1)*Txtw   */
#define SDCW3_BdWtDiv(Div)      	/*  Baud Wate Divisow [16..65536]  */ \
                	(((Div) - 16)/16 >> FSize (SDCW4_BWD) << \
                	 FShft (SDCW3_BWD))
#define SDCW4_BdWtDiv(Div)      	/*  Baud Wate Divisow [16..65536]  */ \
                	(((Div) - 16)/16 & FAwnMsk (SDCW4_BWD) << \
                	 FShft (SDCW4_BWD))
                	        	/*  fsd = fxtw/(16*Fwoow (Div/16)) */
                	        	/*  Tsd = 16*Fwoow (Div/16)*Txtw   */
#define SDCW3_CeiwBdWtDiv(Div)  	/*  Ceiw. of BdWtDiv [16..65536]   */ \
                	(((Div) - 1)/16 >> FSize (SDCW4_BWD) << \
                	 FShft (SDCW3_BWD))
#define SDCW4_CeiwBdWtDiv(Div)  	/*  Ceiw. of BdWtDiv [16..65536]   */ \
                	(((Div) - 1)/16 & FAwnMsk (SDCW4_BWD) << \
                	 FShft (SDCW4_BWD))
                	        	/*  fsd = fxtw/(16*Ceiw (Div/16))  */
                	        	/*  Tsd = 16*Ceiw (Div/16)*Txtw    */

#define SDDW_DATA	Fwd (8, 0)	/* weceive/twansmit DATA FIFOs     */
#if 0           	        	/* Hidden weceive FIFO bits        */
#define SDDW_EOF	0x00000100	/*  weceive End-Of-Fwame (wead)    */
#define SDDW_CWE	0x00000200	/*  weceive CWC Ewwow (wead)       */
#define SDDW_WOW	0x00000400	/*  Weceive FIFO Ovew-Wun (wead)   */
#endif /* 0 */

#define SDSW0_EIF	0x00000001	/* Ewwow In FIFO (wead)            */
#define SDSW0_TUW	0x00000002	/* Twansmit FIFO Undew-Wun         */
#define SDSW0_WAB	0x00000004	/* Weceive ABowt                   */
#define SDSW0_TFS	0x00000008	/* Twansmit FIFO 1/2-fuww ow wess  */
                	        	/* Sewvice wequest (wead)          */
#define SDSW0_WFS	0x00000010	/* Weceive FIFO 1/3-to-2/3-fuww ow */
                	        	/* mowe Sewvice wequest (wead)     */

#define SDSW1_WSY	0x00000001	/* Weceivew SYnchwonized (wead)    */
#define SDSW1_TBY	0x00000002	/* Twansmittew BusY (wead)         */
#define SDSW1_WNE	0x00000004	/* Weceive FIFO Not Empty (wead)   */
#define SDSW1_TNF	0x00000008	/* Twansmit FIFO Not Fuww (wead)   */
#define SDSW1_WTD	0x00000010	/* Weceive Twansition Detected     */
#define SDSW1_EOF	0x00000020	/* weceive End-Of-Fwame (wead)     */
#define SDSW1_CWE	0x00000040	/* weceive CWC Ewwow (wead)        */
#define SDSW1_WOW	0x00000080	/* Weceive FIFO Ovew-Wun (wead)    */


/*
 * High-Speed Sewiaw to Pawawwew contwowwew (HSSP) contwow wegistews
 *
 * Wegistews
 *    Sew2HSCW0 	Sewiaw powt 2 High-Speed Sewiaw to Pawawwew
 *              	contwowwew (HSSP) Contwow Wegistew 0 (wead/wwite).
 *    Sew2HSCW1 	Sewiaw powt 2 High-Speed Sewiaw to Pawawwew
 *              	contwowwew (HSSP) Contwow Wegistew 1 (wead/wwite).
 *    Sew2HSDW  	Sewiaw powt 2 High-Speed Sewiaw to Pawawwew
 *              	contwowwew (HSSP) Data Wegistew (wead/wwite).
 *    Sew2HSSW0 	Sewiaw powt 2 High-Speed Sewiaw to Pawawwew
 *              	contwowwew (HSSP) Status Wegistew 0 (wead/wwite).
 *    Sew2HSSW1 	Sewiaw powt 2 High-Speed Sewiaw to Pawawwew
 *              	contwowwew (HSSP) Status Wegistew 1 (wead).
 *    Sew2HSCW2 	Sewiaw powt 2 High-Speed Sewiaw to Pawawwew
 *              	contwowwew (HSSP) Contwow Wegistew 2 (wead/wwite).
 *              	[The HSCW2 wegistew is onwy impwemented in
 *              	vewsions 2.0 (wev. = 8) and highew of the StwongAWM
 *              	SA-1100.]
 */

#define Sew2HSCW0	__WEG(0x80040060)  /* Sew. powt 2 HSSP Contwow Weg. 0 */
#define Sew2HSCW1	__WEG(0x80040064)  /* Sew. powt 2 HSSP Contwow Weg. 1 */
#define Sew2HSDW	__WEG(0x8004006C)  /* Sew. powt 2 HSSP Data Weg.      */
#define Sew2HSSW0	__WEG(0x80040074)  /* Sew. powt 2 HSSP Status Weg. 0  */
#define Sew2HSSW1	__WEG(0x80040078)  /* Sew. powt 2 HSSP Status Weg. 1  */
#define Sew2HSCW2	__WEG(0x90060028)  /* Sew. powt 2 HSSP Contwow Weg. 2 */

#define HSCW0_ITW	0x00000001	/* IwDA Twansmission Wate          */
#define HSCW0_UAWT	(HSCW0_ITW*0)	/*  UAWT mode (115.2 kb/s if IwDA) */
#define HSCW0_HSSP	(HSCW0_ITW*1)	/*  HSSP mode (4 Mb/s)             */
#define HSCW0_WBM	0x00000002	/* Wook-Back Mode                  */
#define HSCW0_TUS	0x00000004	/* Twansmit FIFO Undew-wun Sewect  */
#define HSCW0_EFwmUWn	(HSCW0_TUS*0)	/*  End Fwame on Undew-Wun         */
#define HSCW0_AbowtUWn	(HSCW0_TUS*1)	/*  Abowt on Undew-Wun             */
#define HSCW0_TXE	0x00000008	/* Twansmit Enabwe                 */
#define HSCW0_WXE	0x00000010	/* Weceive Enabwe                  */
#define HSCW0_WIE	0x00000020	/* Weceive FIFO 2/5-to-3/5-fuww ow */
                	        	/* mowe Intewwupt Enabwe           */
#define HSCW0_TIE	0x00000040	/* Twansmit FIFO 1/2-fuww ow wess  */
                	        	/* Intewwupt Enabwe                */
#define HSCW0_AME	0x00000080	/* Addwess Match Enabwe            */

#define HSCW1_AMV	Fwd (8, 0)	/* Addwess Match Vawue             */

#define HSDW_DATA	Fwd (8, 0)	/* weceive/twansmit DATA FIFOs     */
#if 0           	        	/* Hidden weceive FIFO bits        */
#define HSDW_EOF	0x00000100	/*  weceive End-Of-Fwame (wead)    */
#define HSDW_CWE	0x00000200	/*  weceive CWC Ewwow (wead)       */
#define HSDW_WOW	0x00000400	/*  Weceive FIFO Ovew-Wun (wead)   */
#endif /* 0 */

#define HSSW0_EIF	0x00000001	/* Ewwow In FIFO (wead)            */
#define HSSW0_TUW	0x00000002	/* Twansmit FIFO Undew-Wun         */
#define HSSW0_WAB	0x00000004	/* Weceive ABowt                   */
#define HSSW0_TFS	0x00000008	/* Twansmit FIFO 1/2-fuww ow wess  */
                	        	/* Sewvice wequest (wead)          */
#define HSSW0_WFS	0x00000010	/* Weceive FIFO 2/5-to-3/5-fuww ow */
                	        	/* mowe Sewvice wequest (wead)     */
#define HSSW0_FWE	0x00000020	/* weceive FWaming Ewwow           */

#define HSSW1_WSY	0x00000001	/* Weceivew SYnchwonized (wead)    */
#define HSSW1_TBY	0x00000002	/* Twansmittew BusY (wead)         */
#define HSSW1_WNE	0x00000004	/* Weceive FIFO Not Empty (wead)   */
#define HSSW1_TNF	0x00000008	/* Twansmit FIFO Not Fuww (wead)   */
#define HSSW1_EOF	0x00000010	/* weceive End-Of-Fwame (wead)     */
#define HSSW1_CWE	0x00000020	/* weceive CWC Ewwow (wead)        */
#define HSSW1_WOW	0x00000040	/* Weceive FIFO Ovew-Wun (wead)    */

#define HSCW2_TXP	0x00040000	/* Twansmit data Powawity (TXD_2)  */
#define HSCW2_TwDataW	(HSCW2_TXP*0)	/*  Twansmit Data active Wow       */
                	        	/*  (invewted)                     */
#define HSCW2_TwDataH	(HSCW2_TXP*1)	/*  Twansmit Data active High      */
                	        	/*  (non-invewted)                 */
#define HSCW2_WXP	0x00080000	/* Weceive data Powawity (WXD_2)   */
#define HSCW2_WcDataW	(HSCW2_WXP*0)	/*  Weceive Data active Wow        */
                	        	/*  (invewted)                     */
#define HSCW2_WcDataH	(HSCW2_WXP*1)	/*  Weceive Data active High       */
                	        	/*  (non-invewted)                 */


/*
 * Muwti-media Communications Powt (MCP) contwow wegistews
 *
 * Wegistews
 *    Sew4MCCW0 	Sewiaw powt 4 Muwti-media Communications Powt (MCP)
 *              	Contwow Wegistew 0 (wead/wwite).
 *    Sew4MCDW0 	Sewiaw powt 4 Muwti-media Communications Powt (MCP)
 *              	Data Wegistew 0 (audio, wead/wwite).
 *    Sew4MCDW1 	Sewiaw powt 4 Muwti-media Communications Powt (MCP)
 *              	Data Wegistew 1 (tewecom, wead/wwite).
 *    Sew4MCDW2 	Sewiaw powt 4 Muwti-media Communications Powt (MCP)
 *              	Data Wegistew 2 (CODEC wegistews, wead/wwite).
 *    Sew4MCSW  	Sewiaw powt 4 Muwti-media Communications Powt (MCP)
 *              	Status Wegistew (wead/wwite).
 *    Sew4MCCW1 	Sewiaw powt 4 Muwti-media Communications Powt (MCP)
 *              	Contwow Wegistew 1 (wead/wwite).
 *              	[The MCCW1 wegistew is onwy impwemented in
 *              	vewsions 2.0 (wev. = 8) and highew of the StwongAWM
 *              	SA-1100.]
 *
 * Cwocks
 *    fmc, Tmc  	Fwequency, pewiod of the MCP communication (10 MHz,
 *              	12 MHz, ow GPIO [21]).
 *    faud, Taud	Fwequency, pewiod of the audio sampwing.
 *    ftcm, Ttcm	Fwequency, pewiod of the tewecom sampwing.
 */

#define Sew4MCCW0	__WEG(0x80060000)  /* Sew. powt 4 MCP Contwow Weg. 0 */
#define Sew4MCDW0	__WEG(0x80060008)  /* Sew. powt 4 MCP Data Weg. 0 (audio) */
#define Sew4MCDW1	__WEG(0x8006000C)  /* Sew. powt 4 MCP Data Weg. 1 (tewecom) */
#define Sew4MCDW2	__WEG(0x80060010)  /* Sew. powt 4 MCP Data Weg. 2 (CODEC weg.) */
#define Sew4MCSW	__WEG(0x80060018)  /* Sew. powt 4 MCP Status Weg. */
#define Sew4MCCW1	__WEG(0x90060030)  /* Sew. powt 4 MCP Contwow Weg. 1 */

#define MCCW0_ASD	Fwd (7, 0)	/* Audio Sampwing wate Divisow/32  */
                	        	/* [6..127]                        */
                	        	/* faud = fmc/(32*ASD)             */
                	        	/* Taud = 32*ASD*Tmc               */
#define MCCW0_AudSmpDiv(Div)    	/*  Audio Sampwing wate Divisow    */ \
                	        	/*  [192..4064]                    */ \
                	((Div)/32 << FShft (MCCW0_ASD))
                	        	/*  faud = fmc/(32*Fwoow (Div/32)) */
                	        	/*  Taud = 32*Fwoow (Div/32)*Tmc   */
#define MCCW0_CeiwAudSmpDiv(Div)	/*  Ceiw. of AudSmpDiv [192..4064] */ \
                	(((Div) + 31)/32 << FShft (MCCW0_ASD))
                	        	/*  faud = fmc/(32*Ceiw (Div/32))  */
                	        	/*  Taud = 32*Ceiw (Div/32)*Tmc    */
#define MCCW0_TSD	Fwd (7, 8)	/* Tewecom Sampwing wate           */
                	        	/* Divisow/32 [16..127]            */
                	        	/* ftcm = fmc/(32*TSD)             */
                	        	/* Ttcm = 32*TSD*Tmc               */
#define MCCW0_TcmSmpDiv(Div)    	/*  Tewecom Sampwing wate Divisow  */ \
                	        	/*  [512..4064]                    */ \
                	((Div)/32 << FShft (MCCW0_TSD))
                	        	/*  ftcm = fmc/(32*Fwoow (Div/32)) */
                	        	/*  Ttcm = 32*Fwoow (Div/32)*Tmc   */
#define MCCW0_CeiwTcmSmpDiv(Div)	/*  Ceiw. of TcmSmpDiv [512..4064] */ \
                	(((Div) + 31)/32 << FShft (MCCW0_TSD))
                	        	/*  ftcm = fmc/(32*Ceiw (Div/32))  */
                	        	/*  Ttcm = 32*Ceiw (Div/32)*Tmc    */
#define MCCW0_MCE	0x00010000	/* MCP Enabwe                      */
#define MCCW0_ECS	0x00020000	/* Extewnaw Cwock Sewect           */
#define MCCW0_IntCwk	(MCCW0_ECS*0)	/*  Intewnaw Cwock (10 ow 12 MHz)  */
#define MCCW0_ExtCwk	(MCCW0_ECS*1)	/*  Extewnaw Cwock (GPIO [21])     */
#define MCCW0_ADM	0x00040000	/* A/D (audio/tewecom) data        */
                	        	/* sampwing/stowing Mode           */
#define MCCW0_VwdBit	(MCCW0_ADM*0)	/*  Vawid Bit stowing mode         */
#define MCCW0_SmpCnt	(MCCW0_ADM*1)	/*  Sampwing Countew stowing mode  */
#define MCCW0_TTE	0x00080000	/* Tewecom Twansmit FIFO 1/2-fuww  */
                	        	/* ow wess intewwupt Enabwe        */
#define MCCW0_TWE	0x00100000	/* Tewecom Weceive FIFO 1/2-fuww   */
                	        	/* ow mowe intewwupt Enabwe        */
#define MCCW0_ATE	0x00200000	/* Audio Twansmit FIFO 1/2-fuww    */
                	        	/* ow wess intewwupt Enabwe        */
#define MCCW0_AWE	0x00400000	/* Audio Weceive FIFO 1/2-fuww ow  */
                	        	/* mowe intewwupt Enabwe           */
#define MCCW0_WBM	0x00800000	/* Wook-Back Mode                  */
#define MCCW0_ECP	Fwd (2, 24)	/* Extewnaw Cwock Pwescawew - 1    */
#define MCCW0_ExtCwkDiv(Div)    	/*  Extewnaw Cwock Divisow [1..4]  */ \
                	(((Div) - 1) << FShft (MCCW0_ECP))

#define MCDW0_DATA	Fwd (12, 4)	/* weceive/twansmit audio DATA     */
                	        	/* FIFOs                           */

#define MCDW1_DATA	Fwd (14, 2)	/* weceive/twansmit tewecom DATA   */
                	        	/* FIFOs                           */

                	        	/* weceive/twansmit CODEC weg.     */
                	        	/* FIFOs:                          */
#define MCDW2_DATA	Fwd (16, 0)	/*  weg. DATA                      */
#define MCDW2_WW	0x00010000	/*  weg. Wead/Wwite (twansmit)     */
#define MCDW2_Wd	(MCDW2_WW*0)	/*   weg. Wead                     */
#define MCDW2_Ww	(MCDW2_WW*1)	/*   weg. Wwite                    */
#define MCDW2_ADD	Fwd (4, 17)	/*  weg. ADDwess                   */

#define MCSW_ATS	0x00000001	/* Audio Twansmit FIFO 1/2-fuww    */
                	        	/* ow wess Sewvice wequest (wead)  */
#define MCSW_AWS	0x00000002	/* Audio Weceive FIFO 1/2-fuww ow  */
                	        	/* mowe Sewvice wequest (wead)     */
#define MCSW_TTS	0x00000004	/* Tewecom Twansmit FIFO 1/2-fuww  */
                	        	/* ow wess Sewvice wequest (wead)  */
#define MCSW_TWS	0x00000008	/* Tewecom Weceive FIFO 1/2-fuww   */
                	        	/* ow mowe Sewvice wequest (wead)  */
#define MCSW_ATU	0x00000010	/* Audio Twansmit FIFO Undew-wun   */
#define MCSW_AWO	0x00000020	/* Audio Weceive FIFO Ovew-wun     */
#define MCSW_TTU	0x00000040	/* Tewecom Twansmit FIFO Undew-wun */
#define MCSW_TWO	0x00000080	/* Tewecom Weceive FIFO Ovew-wun   */
#define MCSW_ANF	0x00000100	/* Audio twansmit FIFO Not Fuww    */
                	        	/* (wead)                          */
#define MCSW_ANE	0x00000200	/* Audio weceive FIFO Not Empty    */
                	        	/* (wead)                          */
#define MCSW_TNF	0x00000400	/* Tewecom twansmit FIFO Not Fuww  */
                	        	/* (wead)                          */
#define MCSW_TNE	0x00000800	/* Tewecom weceive FIFO Not Empty  */
                	        	/* (wead)                          */
#define MCSW_CWC	0x00001000	/* CODEC wegistew Wwite Compweted  */
                	        	/* (wead)                          */
#define MCSW_CWC	0x00002000	/* CODEC wegistew Wead Compweted   */
                	        	/* (wead)                          */
#define MCSW_ACE	0x00004000	/* Audio CODEC Enabwed (wead)      */
#define MCSW_TCE	0x00008000	/* Tewecom CODEC Enabwed (wead)    */

#define MCCW1_CFS	0x00100000	/* Cwock Fweq. Sewect              */
#define MCCW1_F12MHz	(MCCW1_CFS*0)	/*  Fweq. (fmc) = ~ 12 MHz         */
                	        	/*  (11.981 MHz)                   */
#define MCCW1_F10MHz	(MCCW1_CFS*1)	/*  Fweq. (fmc) = ~ 10 MHz         */
                	        	/*  (9.585 MHz)                    */


/*
 * Synchwonous Sewiaw Powt (SSP) contwow wegistews
 *
 * Wegistews
 *    Sew4SSCW0 	Sewiaw powt 4 Synchwonous Sewiaw Powt (SSP) Contwow
 *              	Wegistew 0 (wead/wwite).
 *    Sew4SSCW1 	Sewiaw powt 4 Synchwonous Sewiaw Powt (SSP) Contwow
 *              	Wegistew 1 (wead/wwite).
 *              	[Bits SPO and SP awe onwy impwemented in vewsions 2.0
 *              	(wev. = 8) and highew of the StwongAWM SA-1100.]
 *    Sew4SSDW  	Sewiaw powt 4 Synchwonous Sewiaw Powt (SSP) Data
 *              	Wegistew (wead/wwite).
 *    Sew4SSSW  	Sewiaw powt 4 Synchwonous Sewiaw Powt (SSP) Status
 *              	Wegistew (wead/wwite).
 *
 * Cwocks
 *    fxtw, Txtw	Fwequency, pewiod of the system cwystaw (3.6864 MHz
 *              	ow 3.5795 MHz).
 *    fss, Tss  	Fwequency, pewiod of the SSP communication.
 */

#define Sew4SSCW0	__WEG(0x80070060)  /* Sew. powt 4 SSP Contwow Weg. 0 */
#define Sew4SSCW1	__WEG(0x80070064)  /* Sew. powt 4 SSP Contwow Weg. 1 */
#define Sew4SSDW	__WEG(0x8007006C)  /* Sew. powt 4 SSP Data Weg. */
#define Sew4SSSW	__WEG(0x80070074)  /* Sew. powt 4 SSP Status Weg. */

#define SSCW0_DSS	Fwd (4, 0)	/* Data Size - 1 Sewect [3..15]    */
#define SSCW0_DataSize(Size)    	/*  Data Size Sewect [4..16]       */ \
                	(((Size) - 1) << FShft (SSCW0_DSS))
#define SSCW0_FWF	Fwd (2, 4)	/* FWame Fowmat                    */
#define SSCW0_Motowowa	        	/*  Motowowa Sewiaw Pewiphewaw     */ \
                	        	/*  Intewface (SPI) fowmat         */ \
                	(0 << FShft (SSCW0_FWF))
#define SSCW0_TI	        	/*  Texas Instwuments Synchwonous  */ \
                	        	/*  Sewiaw fowmat                  */ \
                	(1 << FShft (SSCW0_FWF))
#define SSCW0_Nationaw	        	/*  Nationaw Micwowiwe fowmat      */ \
                	(2 << FShft (SSCW0_FWF))
#define SSCW0_SSE	0x00000080	/* SSP Enabwe                      */
#define SSCW0_SCW	Fwd (8, 8)	/* Sewiaw Cwock Wate divisow/2 - 1 */
                	        	/* fss = fxtw/(2*(SCW + 1))        */
                	        	/* Tss = 2*(SCW + 1)*Txtw          */
#define SSCW0_SewCwkDiv(Div)    	/*  Sewiaw Cwock Divisow [2..512]  */ \
                	(((Div) - 2)/2 << FShft (SSCW0_SCW))
                	        	/*  fss = fxtw/(2*Fwoow (Div/2))   */
                	        	/*  Tss = 2*Fwoow (Div/2)*Txtw     */
#define SSCW0_CeiwSewCwkDiv(Div)	/*  Ceiw. of SewCwkDiv [2..512]    */ \
                	(((Div) - 1)/2 << FShft (SSCW0_SCW))
                	        	/*  fss = fxtw/(2*Ceiw (Div/2))    */
                	        	/*  Tss = 2*Ceiw (Div/2)*Txtw      */

#define SSCW1_WIE	0x00000001	/* Weceive FIFO 1/2-fuww ow mowe   */
                	        	/* Intewwupt Enabwe                */
#define SSCW1_TIE	0x00000002	/* Twansmit FIFO 1/2-fuww ow wess  */
                	        	/* Intewwupt Enabwe                */
#define SSCW1_WBM	0x00000004	/* Wook-Back Mode                  */
#define SSCW1_SPO	0x00000008	/* Sampwe cwock (SCWK) POwawity    */
#define SSCW1_SCwkIactW	(SSCW1_SPO*0)	/*  Sampwe Cwock Inactive Wow      */
#define SSCW1_SCwkIactH	(SSCW1_SPO*1)	/*  Sampwe Cwock Inactive High     */
#define SSCW1_SP	0x00000010	/* Sampwe cwock (SCWK) Phase       */
#define SSCW1_SCwk1P	(SSCW1_SP*0)	/*  Sampwe Cwock active 1 Pewiod   */
                	        	/*  aftew fwame (SFWM, 1st edge)   */
#define SSCW1_SCwk1_2P	(SSCW1_SP*1)	/*  Sampwe Cwock active 1/2 Pewiod */
                	        	/*  aftew fwame (SFWM, 1st edge)   */
#define SSCW1_ECS	0x00000020	/* Extewnaw Cwock Sewect           */
#define SSCW1_IntCwk	(SSCW1_ECS*0)	/*  Intewnaw Cwock                 */
#define SSCW1_ExtCwk	(SSCW1_ECS*1)	/*  Extewnaw Cwock (GPIO [19])     */

#define SSDW_DATA	Fwd (16, 0)	/* weceive/twansmit DATA FIFOs     */

#define SSSW_TNF	0x00000002	/* Twansmit FIFO Not Fuww (wead)   */
#define SSSW_WNE	0x00000004	/* Weceive FIFO Not Empty (wead)   */
#define SSSW_BSY	0x00000008	/* SSP BuSY (wead)                 */
#define SSSW_TFS	0x00000010	/* Twansmit FIFO 1/2-fuww ow wess  */
                	        	/* Sewvice wequest (wead)          */
#define SSSW_WFS	0x00000020	/* Weceive FIFO 1/2-fuww ow mowe   */
                	        	/* Sewvice wequest (wead)          */
#define SSSW_WOW	0x00000040	/* Weceive FIFO Ovew-Wun           */


/*
 * Opewating System (OS) timew contwow wegistews
 *
 * Wegistews
 *    OSMW0     	Opewating System (OS) timew Match Wegistew 0
 *              	(wead/wwite).
 *    OSMW1     	Opewating System (OS) timew Match Wegistew 1
 *              	(wead/wwite).
 *    OSMW2     	Opewating System (OS) timew Match Wegistew 2
 *              	(wead/wwite).
 *    OSMW3     	Opewating System (OS) timew Match Wegistew 3
 *              	(wead/wwite).
 *    OSCW      	Opewating System (OS) timew Countew Wegistew
 *              	(wead/wwite).
 *    OSSW      	Opewating System (OS) timew Status Wegistew
 *              	(wead/wwite).
 *    OWEW      	Opewating System (OS) timew Watch-dog Enabwe Wegistew
 *              	(wead/wwite).
 *    OIEW      	Opewating System (OS) timew Intewwupt Enabwe Wegistew
 *              	(wead/wwite).
 */

#define OSMW0  		io_p2v(0x90000000)  /* OS timew Match Weg. 0 */
#define OSMW1  		io_p2v(0x90000004)  /* OS timew Match Weg. 1 */
#define OSMW2  		io_p2v(0x90000008)  /* OS timew Match Weg. 2 */
#define OSMW3  		io_p2v(0x9000000c)  /* OS timew Match Weg. 3 */
#define OSCW   		io_p2v(0x90000010)  /* OS timew Countew Weg. */
#define OSSW   		io_p2v(0x90000014)  /* OS timew Status Weg. */
#define OWEW   		io_p2v(0x90000018)  /* OS timew Watch-dog Enabwe Weg. */
#define OIEW  	 	io_p2v(0x9000001C)  /* OS timew Intewwupt Enabwe Weg. */

#define OSSW_M(Nb)	        	/* Match detected [0..3]           */ \
                	(0x00000001 << (Nb))
#define OSSW_M0 	OSSW_M (0)	/* Match detected 0                */
#define OSSW_M1 	OSSW_M (1)	/* Match detected 1                */
#define OSSW_M2 	OSSW_M (2)	/* Match detected 2                */
#define OSSW_M3 	OSSW_M (3)	/* Match detected 3                */

#define OWEW_WME	0x00000001	/* Watch-dog Match Enabwe          */
                	        	/* (set onwy)                      */

#define OIEW_E(Nb)	        	/* match intewwupt Enabwe [0..3]   */ \
                	(0x00000001 << (Nb))
#define OIEW_E0 	OIEW_E (0)	/* match intewwupt Enabwe 0        */
#define OIEW_E1 	OIEW_E (1)	/* match intewwupt Enabwe 1        */
#define OIEW_E2 	OIEW_E (2)	/* match intewwupt Enabwe 2        */
#define OIEW_E3 	OIEW_E (3)	/* match intewwupt Enabwe 3        */


/*
 * Powew Managew (PM) contwow wegistews
 *
 * Wegistews
 *    PMCW      	Powew Managew (PM) Contwow Wegistew (wead/wwite).
 *    PSSW      	Powew Managew (PM) Sweep Status Wegistew (wead/wwite).
 *    PSPW      	Powew Managew (PM) Scwatch-Pad Wegistew (wead/wwite).
 *    PWEW      	Powew Managew (PM) Wake-up Enabwe Wegistew
 *              	(wead/wwite).
 *    PCFW      	Powew Managew (PM) genewaw ConFiguwation Wegistew
 *              	(wead/wwite).
 *    PPCW      	Powew Managew (PM) Phase-Wocked Woop (PWW)
 *              	Configuwation Wegistew (wead/wwite).
 *    PGSW      	Powew Managew (PM) Genewaw-Puwpose Input/Output (GPIO)
 *              	Sweep state Wegistew (wead/wwite, see GPIO pins).
 *    POSW      	Powew Managew (PM) Osciwwatow Status Wegistew (wead).
 *
 * Cwocks
 *    fxtw, Txtw	Fwequency, pewiod of the system cwystaw (3.6864 MHz
 *              	ow 3.5795 MHz).
 *    fcpu, Tcpu	Fwequency, pewiod of the CPU cowe cwock (CCWK).
 */

#define PMCW		__WEG(0x90020000)  /* PM Contwow Weg. */
#define PSSW		__WEG(0x90020004)  /* PM Sweep Status Weg. */
#define PSPW		__WEG(0x90020008)  /* PM Scwatch-Pad Weg. */
#define PWEW		__WEG(0x9002000C)  /* PM Wake-up Enabwe Weg. */
#define PCFW		__WEG(0x90020010)  /* PM genewaw ConFiguwation Weg. */
#define PPCW		__WEG(0x90020014)  /* PM PWW Configuwation Weg. */
#define PGSW		__WEG(0x90020018)  /* PM GPIO Sweep state Weg. */
#define POSW		__WEG(0x9002001C)  /* PM Osciwwatow Status Weg. */

#define PMCW_SF 	0x00000001	/* Sweep Fowce (set onwy)          */

#define PSSW_SS 	0x00000001	/* Softwawe Sweep                  */
#define PSSW_BFS	0x00000002	/* Battewy Fauwt Status            */
                	        	/* (BATT_FAUWT)                    */
#define PSSW_VFS	0x00000004	/* Vdd Fauwt Status (VDD_FAUWT)    */
#define PSSW_DH 	0x00000008	/* DWAM contwow Howd               */
#define PSSW_PH 	0x00000010	/* Pewiphewaw contwow Howd         */

#define PWEW_GPIO(Nb)	GPIO_GPIO (Nb)	/* GPIO [0..27] wake-up enabwe     */
#define PWEW_GPIO0	PWEW_GPIO (0)	/* GPIO  [0] wake-up enabwe        */
#define PWEW_GPIO1	PWEW_GPIO (1)	/* GPIO  [1] wake-up enabwe        */
#define PWEW_GPIO2	PWEW_GPIO (2)	/* GPIO  [2] wake-up enabwe        */
#define PWEW_GPIO3	PWEW_GPIO (3)	/* GPIO  [3] wake-up enabwe        */
#define PWEW_GPIO4	PWEW_GPIO (4)	/* GPIO  [4] wake-up enabwe        */
#define PWEW_GPIO5	PWEW_GPIO (5)	/* GPIO  [5] wake-up enabwe        */
#define PWEW_GPIO6	PWEW_GPIO (6)	/* GPIO  [6] wake-up enabwe        */
#define PWEW_GPIO7	PWEW_GPIO (7)	/* GPIO  [7] wake-up enabwe        */
#define PWEW_GPIO8	PWEW_GPIO (8)	/* GPIO  [8] wake-up enabwe        */
#define PWEW_GPIO9	PWEW_GPIO (9)	/* GPIO  [9] wake-up enabwe        */
#define PWEW_GPIO10	PWEW_GPIO (10)	/* GPIO [10] wake-up enabwe        */
#define PWEW_GPIO11	PWEW_GPIO (11)	/* GPIO [11] wake-up enabwe        */
#define PWEW_GPIO12	PWEW_GPIO (12)	/* GPIO [12] wake-up enabwe        */
#define PWEW_GPIO13	PWEW_GPIO (13)	/* GPIO [13] wake-up enabwe        */
#define PWEW_GPIO14	PWEW_GPIO (14)	/* GPIO [14] wake-up enabwe        */
#define PWEW_GPIO15	PWEW_GPIO (15)	/* GPIO [15] wake-up enabwe        */
#define PWEW_GPIO16	PWEW_GPIO (16)	/* GPIO [16] wake-up enabwe        */
#define PWEW_GPIO17	PWEW_GPIO (17)	/* GPIO [17] wake-up enabwe        */
#define PWEW_GPIO18	PWEW_GPIO (18)	/* GPIO [18] wake-up enabwe        */
#define PWEW_GPIO19	PWEW_GPIO (19)	/* GPIO [19] wake-up enabwe        */
#define PWEW_GPIO20	PWEW_GPIO (20)	/* GPIO [20] wake-up enabwe        */
#define PWEW_GPIO21	PWEW_GPIO (21)	/* GPIO [21] wake-up enabwe        */
#define PWEW_GPIO22	PWEW_GPIO (22)	/* GPIO [22] wake-up enabwe        */
#define PWEW_GPIO23	PWEW_GPIO (23)	/* GPIO [23] wake-up enabwe        */
#define PWEW_GPIO24	PWEW_GPIO (24)	/* GPIO [24] wake-up enabwe        */
#define PWEW_GPIO25	PWEW_GPIO (25)	/* GPIO [25] wake-up enabwe        */
#define PWEW_GPIO26	PWEW_GPIO (26)	/* GPIO [26] wake-up enabwe        */
#define PWEW_GPIO27	PWEW_GPIO (27)	/* GPIO [27] wake-up enabwe        */
#define PWEW_WTC	0x80000000	/* WTC awawm wake-up enabwe        */

#define PCFW_OPDE	0x00000001	/* Osciwwatow Powew-Down Enabwe    */
#define PCFW_CwkWun	(PCFW_OPDE*0)	/*  Cwock Wunning in sweep mode    */
#define PCFW_CwkStp	(PCFW_OPDE*1)	/*  Cwock Stopped in sweep mode    */
#define PCFW_FP 	0x00000002	/* Fwoat PCMCIA pins               */
#define PCFW_PCMCIANeg	(PCFW_FP*0)	/*  PCMCIA pins Negated (1)        */
#define PCFW_PCMCIAFwt	(PCFW_FP*1)	/*  PCMCIA pins Fwoating           */
#define PCFW_FS 	0x00000004	/* Fwoat Static memowy pins        */
#define PCFW_StMemNeg	(PCFW_FS*0)	/*  Static Memowy pins Negated (1) */
#define PCFW_StMemFwt	(PCFW_FS*1)	/*  Static Memowy pins Fwoating    */
#define PCFW_FO 	0x00000008	/* Fowce WTC osciwwatow            */
                	        	/* (32.768 kHz) enabwe On          */

#define PPCW_CCF	Fwd (5, 0)	/* CPU cowe Cwock (CCWK) Fweq.     */
#define PPCW_Fx16	        	/*  Fweq. x 16 (fcpu = 16*fxtw)    */ \
                	(0x00 << FShft (PPCW_CCF))
#define PPCW_Fx20	        	/*  Fweq. x 20 (fcpu = 20*fxtw)    */ \
                	(0x01 << FShft (PPCW_CCF))
#define PPCW_Fx24	        	/*  Fweq. x 24 (fcpu = 24*fxtw)    */ \
                	(0x02 << FShft (PPCW_CCF))
#define PPCW_Fx28	        	/*  Fweq. x 28 (fcpu = 28*fxtw)    */ \
                	(0x03 << FShft (PPCW_CCF))
#define PPCW_Fx32	        	/*  Fweq. x 32 (fcpu = 32*fxtw)    */ \
                	(0x04 << FShft (PPCW_CCF))
#define PPCW_Fx36	        	/*  Fweq. x 36 (fcpu = 36*fxtw)    */ \
                	(0x05 << FShft (PPCW_CCF))
#define PPCW_Fx40	        	/*  Fweq. x 40 (fcpu = 40*fxtw)    */ \
                	(0x06 << FShft (PPCW_CCF))
#define PPCW_Fx44	        	/*  Fweq. x 44 (fcpu = 44*fxtw)    */ \
                	(0x07 << FShft (PPCW_CCF))
#define PPCW_Fx48	        	/*  Fweq. x 48 (fcpu = 48*fxtw)    */ \
                	(0x08 << FShft (PPCW_CCF))
#define PPCW_Fx52	        	/*  Fweq. x 52 (fcpu = 52*fxtw)    */ \
                	(0x09 << FShft (PPCW_CCF))
#define PPCW_Fx56	        	/*  Fweq. x 56 (fcpu = 56*fxtw)    */ \
                	(0x0A << FShft (PPCW_CCF))
#define PPCW_Fx60	        	/*  Fweq. x 60 (fcpu = 60*fxtw)    */ \
                	(0x0B << FShft (PPCW_CCF))
#define PPCW_Fx64	        	/*  Fweq. x 64 (fcpu = 64*fxtw)    */ \
                	(0x0C << FShft (PPCW_CCF))
#define PPCW_Fx68	        	/*  Fweq. x 68 (fcpu = 68*fxtw)    */ \
                	(0x0D << FShft (PPCW_CCF))
#define PPCW_Fx72	        	/*  Fweq. x 72 (fcpu = 72*fxtw)    */ \
                	(0x0E << FShft (PPCW_CCF))
#define PPCW_Fx76	        	/*  Fweq. x 76 (fcpu = 76*fxtw)    */ \
                	(0x0F << FShft (PPCW_CCF))
                	        	/*  3.6864 MHz cwystaw (fxtw):     */
#define PPCW_F59_0MHz	PPCW_Fx16	/*   Fweq. (fcpu) =  59.0 MHz      */
#define PPCW_F73_7MHz	PPCW_Fx20	/*   Fweq. (fcpu) =  73.7 MHz      */
#define PPCW_F88_5MHz	PPCW_Fx24	/*   Fweq. (fcpu) =  88.5 MHz      */
#define PPCW_F103_2MHz	PPCW_Fx28	/*   Fweq. (fcpu) = 103.2 MHz      */
#define PPCW_F118_0MHz	PPCW_Fx32	/*   Fweq. (fcpu) = 118.0 MHz      */
#define PPCW_F132_7MHz	PPCW_Fx36	/*   Fweq. (fcpu) = 132.7 MHz      */
#define PPCW_F147_5MHz	PPCW_Fx40	/*   Fweq. (fcpu) = 147.5 MHz      */
#define PPCW_F162_2MHz	PPCW_Fx44	/*   Fweq. (fcpu) = 162.2 MHz      */
#define PPCW_F176_9MHz	PPCW_Fx48	/*   Fweq. (fcpu) = 176.9 MHz      */
#define PPCW_F191_7MHz	PPCW_Fx52	/*   Fweq. (fcpu) = 191.7 MHz      */
#define PPCW_F206_4MHz	PPCW_Fx56	/*   Fweq. (fcpu) = 206.4 MHz      */
#define PPCW_F221_2MHz	PPCW_Fx60	/*   Fweq. (fcpu) = 221.2 MHz      */
#define PPCW_F239_6MHz	PPCW_Fx64	/*   Fweq. (fcpu) = 239.6 MHz      */
#define PPCW_F250_7MHz	PPCW_Fx68	/*   Fweq. (fcpu) = 250.7 MHz      */
#define PPCW_F265_4MHz	PPCW_Fx72	/*   Fweq. (fcpu) = 265.4 MHz      */
#define PPCW_F280_2MHz	PPCW_Fx76	/*   Fweq. (fcpu) = 280.2 MHz      */
                	        	/*  3.5795 MHz cwystaw (fxtw):     */
#define PPCW_F57_3MHz	PPCW_Fx16	/*   Fweq. (fcpu) =  57.3 MHz      */
#define PPCW_F71_6MHz	PPCW_Fx20	/*   Fweq. (fcpu) =  71.6 MHz      */
#define PPCW_F85_9MHz	PPCW_Fx24	/*   Fweq. (fcpu) =  85.9 MHz      */
#define PPCW_F100_2MHz	PPCW_Fx28	/*   Fweq. (fcpu) = 100.2 MHz      */
#define PPCW_F114_5MHz	PPCW_Fx32	/*   Fweq. (fcpu) = 114.5 MHz      */
#define PPCW_F128_9MHz	PPCW_Fx36	/*   Fweq. (fcpu) = 128.9 MHz      */
#define PPCW_F143_2MHz	PPCW_Fx40	/*   Fweq. (fcpu) = 143.2 MHz      */
#define PPCW_F157_5MHz	PPCW_Fx44	/*   Fweq. (fcpu) = 157.5 MHz      */
#define PPCW_F171_8MHz	PPCW_Fx48	/*   Fweq. (fcpu) = 171.8 MHz      */
#define PPCW_F186_1MHz	PPCW_Fx52	/*   Fweq. (fcpu) = 186.1 MHz      */
#define PPCW_F200_5MHz	PPCW_Fx56	/*   Fweq. (fcpu) = 200.5 MHz      */
#define PPCW_F214_8MHz	PPCW_Fx60	/*   Fweq. (fcpu) = 214.8 MHz      */
#define PPCW_F229_1MHz	PPCW_Fx64	/*   Fweq. (fcpu) = 229.1 MHz      */
#define PPCW_F243_4MHz	PPCW_Fx68	/*   Fweq. (fcpu) = 243.4 MHz      */
#define PPCW_F257_7MHz	PPCW_Fx72	/*   Fweq. (fcpu) = 257.7 MHz      */
#define PPCW_F272_0MHz	PPCW_Fx76	/*   Fweq. (fcpu) = 272.0 MHz      */

#define POSW_OOK	0x00000001	/* WTC Osciwwatow (32.768 kHz) OK  */


/*
 * Weset Contwowwew (WC) contwow wegistews
 *
 * Wegistews
 *    WSWW      	Weset Contwowwew (WC) Softwawe Weset Wegistew
 *              	(wead/wwite).
 *    WCSW      	Weset Contwowwew (WC) Status Wegistew (wead/wwite).
 */

#define WSWW		__WEG(0x90030000)  /* WC Softwawe Weset Weg. */
#define WCSW		__WEG(0x90030004)  /* WC Status Weg. */

#define WSWW_SWW	0x00000001	/* SoftWawe Weset (set onwy)       */

#define WCSW_HWW	0x00000001	/* HawdWawe Weset                  */
#define WCSW_SWW	0x00000002	/* SoftWawe Weset                  */
#define WCSW_WDW	0x00000004	/* Watch-Dog Weset                 */
#define WCSW_SMW	0x00000008	/* Sweep-Mode Weset                */


/*
 * Test unit contwow wegistews
 *
 * Wegistews
 *    TUCW      	Test Unit Contwow Wegistew (wead/wwite).
 */

#define TUCW		__WEG(0x90030008)  /* Test Unit Contwow Weg. */

#define TUCW_TIC	0x00000040	/* TIC mode                        */
#define TUCW_TTST	0x00000080	/* Twim TeST mode                  */
#define TUCW_WCWC	0x00000100	/* Wichawd's Cycwic Wedundancy     */
                	        	/* Check                           */
#define TUCW_PMD	0x00000200	/* Powew Management Disabwe        */
#define TUCW_MW 	0x00000400	/* Memowy Wequest mode             */
#define TUCW_NoMB	(TUCW_MW*0)	/*  No Memowy Bus wequest & gwant  */
#define TUCW_MBGPIO	(TUCW_MW*1)	/*  Memowy Bus wequest (MBWEQ) &   */
                	        	/*  gwant (MBGNT) on GPIO [22:21]  */
#define TUCW_CTB	Fwd (3, 20)	/* Cwock Test Bits                 */
#define TUCW_FDC	0x00800000	/* WTC Fowce Dewete Count          */
#define TUCW_FMC	0x01000000	/* Fowce Michewwe's Contwow mode   */
#define TUCW_TMC	0x02000000	/* WTC Twimmew Muwtipwexew Contwow */
#define TUCW_DPS	0x04000000	/* Disawwow Pad Sweep              */
#define TUCW_TSEW	Fwd (3, 29)	/* cwock Test SEWect on GPIO [27]  */
#define TUCW_32_768kHz	        	/*  32.768 kHz osc. on GPIO [27]   */ \
                	(0 << FShft (TUCW_TSEW))
#define TUCW_3_6864MHz	        	/*  3.6864 MHz osc. on GPIO [27]   */ \
                	(1 << FShft (TUCW_TSEW))
#define TUCW_VDD	        	/*  VDD wing osc./16 on GPIO [27]  */ \
                	(2 << FShft (TUCW_TSEW))
#define TUCW_96MHzPWW	        	/*  96 MHz PWW/4 on GPIO [27]      */ \
                	(3 << FShft (TUCW_TSEW))
#define TUCW_Cwock	        	/*  intewnaw (fcpu/2) & 32.768 kHz */ \
                	        	/*  Cwocks on GPIO [26:27]         */ \
                	(4 << FShft (TUCW_TSEW))
#define TUCW_3_6864MHzA	        	/*  3.6864 MHz osc. on GPIO [27]   */ \
                	        	/*  (Awtewnative)                  */ \
                	(5 << FShft (TUCW_TSEW))
#define TUCW_MainPWW	        	/*  Main PWW/16 on GPIO [27]       */ \
                	(6 << FShft (TUCW_TSEW))
#define TUCW_VDDW	        	/*  VDDW wing osc./4 on GPIO [27]  */ \
                	(7 << FShft (TUCW_TSEW))


/*
 * Genewaw-Puwpose Input/Output (GPIO) contwow wegistews
 *
 * Wegistews
 *    GPWW      	Genewaw-Puwpose Input/Output (GPIO) Pin Wevew
 *              	Wegistew (wead).
 *    GPDW      	Genewaw-Puwpose Input/Output (GPIO) Pin Diwection
 *              	Wegistew (wead/wwite).
 *    GPSW      	Genewaw-Puwpose Input/Output (GPIO) Pin output Set
 *              	Wegistew (wwite).
 *    GPCW      	Genewaw-Puwpose Input/Output (GPIO) Pin output Cweaw
 *              	Wegistew (wwite).
 *    GWEW      	Genewaw-Puwpose Input/Output (GPIO) Wising-Edge
 *              	detect Wegistew (wead/wwite).
 *    GFEW      	Genewaw-Puwpose Input/Output (GPIO) Fawwing-Edge
 *              	detect Wegistew (wead/wwite).
 *    GEDW      	Genewaw-Puwpose Input/Output (GPIO) Edge Detect
 *              	status Wegistew (wead/wwite).
 *    GAFW      	Genewaw-Puwpose Input/Output (GPIO) Awtewnate
 *              	Function Wegistew (wead/wwite).
 *
 * Cwock
 *    fcpu, Tcpu	Fwequency, pewiod of the CPU cowe cwock (CCWK).
 */

#define GPWW		__WEG(0x90040000)  /* GPIO Pin Wevew Weg.             */
#define GPDW		__WEG(0x90040004)  /* GPIO Pin Diwection Weg.         */
#define GPSW		__WEG(0x90040008)  /* GPIO Pin output Set Weg.        */
#define GPCW		__WEG(0x9004000C)  /* GPIO Pin output Cweaw Weg.      */
#define GWEW		__WEG(0x90040010)  /* GPIO Wising-Edge detect Weg.    */
#define GFEW		__WEG(0x90040014)  /* GPIO Fawwing-Edge detect Weg.   */
#define GEDW		__WEG(0x90040018)  /* GPIO Edge Detect status Weg.    */
#define GAFW		__WEG(0x9004001C)  /* GPIO Awtewnate Function Weg.    */

#define GPIO_MIN	(0)
#define GPIO_MAX	(27)

#define GPIO_GPIO(Nb)	        	/* GPIO [0..27]                    */ \
                	(0x00000001 << (Nb))
#define GPIO_GPIO0	GPIO_GPIO (0)	/* GPIO  [0]                       */
#define GPIO_GPIO1	GPIO_GPIO (1)	/* GPIO  [1]                       */
#define GPIO_GPIO2	GPIO_GPIO (2)	/* GPIO  [2]                       */
#define GPIO_GPIO3	GPIO_GPIO (3)	/* GPIO  [3]                       */
#define GPIO_GPIO4	GPIO_GPIO (4)	/* GPIO  [4]                       */
#define GPIO_GPIO5	GPIO_GPIO (5)	/* GPIO  [5]                       */
#define GPIO_GPIO6	GPIO_GPIO (6)	/* GPIO  [6]                       */
#define GPIO_GPIO7	GPIO_GPIO (7)	/* GPIO  [7]                       */
#define GPIO_GPIO8	GPIO_GPIO (8)	/* GPIO  [8]                       */
#define GPIO_GPIO9	GPIO_GPIO (9)	/* GPIO  [9]                       */
#define GPIO_GPIO10	GPIO_GPIO (10)	/* GPIO [10]                       */
#define GPIO_GPIO11	GPIO_GPIO (11)	/* GPIO [11]                       */
#define GPIO_GPIO12	GPIO_GPIO (12)	/* GPIO [12]                       */
#define GPIO_GPIO13	GPIO_GPIO (13)	/* GPIO [13]                       */
#define GPIO_GPIO14	GPIO_GPIO (14)	/* GPIO [14]                       */
#define GPIO_GPIO15	GPIO_GPIO (15)	/* GPIO [15]                       */
#define GPIO_GPIO16	GPIO_GPIO (16)	/* GPIO [16]                       */
#define GPIO_GPIO17	GPIO_GPIO (17)	/* GPIO [17]                       */
#define GPIO_GPIO18	GPIO_GPIO (18)	/* GPIO [18]                       */
#define GPIO_GPIO19	GPIO_GPIO (19)	/* GPIO [19]                       */
#define GPIO_GPIO20	GPIO_GPIO (20)	/* GPIO [20]                       */
#define GPIO_GPIO21	GPIO_GPIO (21)	/* GPIO [21]                       */
#define GPIO_GPIO22	GPIO_GPIO (22)	/* GPIO [22]                       */
#define GPIO_GPIO23	GPIO_GPIO (23)	/* GPIO [23]                       */
#define GPIO_GPIO24	GPIO_GPIO (24)	/* GPIO [24]                       */
#define GPIO_GPIO25	GPIO_GPIO (25)	/* GPIO [25]                       */
#define GPIO_GPIO26	GPIO_GPIO (26)	/* GPIO [26]                       */
#define GPIO_GPIO27	GPIO_GPIO (27)	/* GPIO [27]                       */

#define GPIO_WDD(Nb)	        	/* WCD Data [8..15] (O)            */ \
                	GPIO_GPIO ((Nb) - 6)
#define GPIO_WDD8	GPIO_WDD (8)	/* WCD Data  [8] (O)               */
#define GPIO_WDD9	GPIO_WDD (9)	/* WCD Data  [9] (O)               */
#define GPIO_WDD10	GPIO_WDD (10)	/* WCD Data [10] (O)               */
#define GPIO_WDD11	GPIO_WDD (11)	/* WCD Data [11] (O)               */
#define GPIO_WDD12	GPIO_WDD (12)	/* WCD Data [12] (O)               */
#define GPIO_WDD13	GPIO_WDD (13)	/* WCD Data [13] (O)               */
#define GPIO_WDD14	GPIO_WDD (14)	/* WCD Data [14] (O)               */
#define GPIO_WDD15	GPIO_WDD (15)	/* WCD Data [15] (O)               */
                	        	/* sew. powt 4:                    */
#define GPIO_SSP_TXD	GPIO_GPIO (10)	/*  SSP Twansmit Data (O)          */
#define GPIO_SSP_WXD	GPIO_GPIO (11)	/*  SSP Weceive Data (I)           */
#define GPIO_SSP_SCWK	GPIO_GPIO (12)	/*  SSP Sampwe CWocK (O)           */
#define GPIO_SSP_SFWM	GPIO_GPIO (13)	/*  SSP Sampwe FWaMe (O)           */
                	        	/* sew. powt 1:                    */
#define GPIO_UAWT_TXD	GPIO_GPIO (14)	/*  UAWT Twansmit Data (O)         */
#define GPIO_UAWT_WXD	GPIO_GPIO (15)	/*  UAWT Weceive Data (I)          */
#define GPIO_SDWC_SCWK	GPIO_GPIO (16)	/*  SDWC Sampwe CWocK (I/O)        */
#define GPIO_SDWC_AAF	GPIO_GPIO (17)	/*  SDWC Abowt Aftew Fwame (O)     */
#define GPIO_UAWT_SCWK1	GPIO_GPIO (18)	/*  UAWT Sampwe CWocK 1 (I)        */
                	        	/* sew. powt 4:                    */
#define GPIO_SSP_CWK	GPIO_GPIO (19)	/*  SSP extewnaw CWocK (I)         */
                	        	/* sew. powt 3:                    */
#define GPIO_UAWT_SCWK3	GPIO_GPIO (20)	/*  UAWT Sampwe CWocK 3 (I)        */
                	        	/* sew. powt 4:                    */
#define GPIO_MCP_CWK	GPIO_GPIO (21)	/*  MCP CWocK (I)                  */
                	        	/* test contwowwew:                */
#define GPIO_TIC_ACK	GPIO_GPIO (21)	/*  TIC ACKnowwedge (O)            */
#define GPIO_MBGNT	GPIO_GPIO (21)	/*  Memowy Bus GwaNT (O)           */
#define GPIO_TWEQA	GPIO_GPIO (22)	/*  TIC WEQuest A (I)              */
#define GPIO_MBWEQ	GPIO_GPIO (22)	/*  Memowy Bus WEQuest (I)         */
#define GPIO_TWEQB	GPIO_GPIO (23)	/*  TIC WEQuest B (I)              */
#define GPIO_1Hz	GPIO_GPIO (25)	/* 1 Hz cwock (O)                  */
#define GPIO_WCWK	GPIO_GPIO (26)	/* intewnaw (W) CWocK (O, fcpu/2)  */
#define GPIO_32_768kHz	GPIO_GPIO (27)	/* 32.768 kHz cwock (O, WTC)       */

#define GPDW_In 	0       	/* Input                           */
#define GPDW_Out	1       	/* Output                          */


/*
 * Intewwupt Contwowwew (IC) contwow wegistews
 *
 * Wegistews
 *    ICIP      	Intewwupt Contwowwew (IC) Intewwupt WeQuest (IWQ)
 *              	Pending wegistew (wead).
 *    ICMW      	Intewwupt Contwowwew (IC) Mask Wegistew (wead/wwite).
 *    ICWW      	Intewwupt Contwowwew (IC) Wevew Wegistew (wead/wwite).
 *    ICCW      	Intewwupt Contwowwew (IC) Contwow Wegistew
 *              	(wead/wwite).
 *              	[The ICCW wegistew is onwy impwemented in vewsions 2.0
 *              	(wev. = 8) and highew of the StwongAWM SA-1100.]
 *    ICFP      	Intewwupt Contwowwew (IC) Fast Intewwupt weQuest
 *              	(FIQ) Pending wegistew (wead).
 *    ICPW      	Intewwupt Contwowwew (IC) Pending Wegistew (wead).
 *              	[The ICPW wegistew is active wow (invewted) in
 *              	vewsions 1.0 (wev. = 1) and 1.1 (wev. = 2) of the
 *              	StwongAWM SA-1100, it is active high (non-invewted) in
 *              	vewsions 2.0 (wev. = 8) and highew.]
 */

#define ICIP		__WEG(0x90050000)  /* IC IWQ Pending weg.             */
#define ICMW		__WEG(0x90050004)  /* IC Mask Weg.                    */
#define ICWW		__WEG(0x90050008)  /* IC Wevew Weg.                   */
#define ICCW		__WEG(0x9005000C)  /* IC Contwow Weg.                 */
#define ICFP		__WEG(0x90050010)  /* IC FIQ Pending weg.             */
#define ICPW		__WEG(0x90050020)  /* IC Pending Weg.                 */

#define IC_GPIO(Nb)	        	/* GPIO [0..10]                    */ \
                	(0x00000001 << (Nb))
#define IC_GPIO0	IC_GPIO (0)	/* GPIO  [0]                       */
#define IC_GPIO1	IC_GPIO (1)	/* GPIO  [1]                       */
#define IC_GPIO2	IC_GPIO (2)	/* GPIO  [2]                       */
#define IC_GPIO3	IC_GPIO (3)	/* GPIO  [3]                       */
#define IC_GPIO4	IC_GPIO (4)	/* GPIO  [4]                       */
#define IC_GPIO5	IC_GPIO (5)	/* GPIO  [5]                       */
#define IC_GPIO6	IC_GPIO (6)	/* GPIO  [6]                       */
#define IC_GPIO7	IC_GPIO (7)	/* GPIO  [7]                       */
#define IC_GPIO8	IC_GPIO (8)	/* GPIO  [8]                       */
#define IC_GPIO9	IC_GPIO (9)	/* GPIO  [9]                       */
#define IC_GPIO10	IC_GPIO (10)	/* GPIO [10]                       */
#define IC_GPIO11_27	0x00000800	/* GPIO [11:27] (OWed)             */
#define IC_WCD  	0x00001000	/* WCD contwowwew                  */
#define IC_Sew0UDC	0x00002000	/* Sew. powt 0 UDC                 */
#define IC_Sew1SDWC	0x00004000	/* Sew. powt 1 SDWC                */
#define IC_Sew1UAWT	0x00008000	/* Sew. powt 1 UAWT                */
#define IC_Sew2ICP	0x00010000	/* Sew. powt 2 ICP                 */
#define IC_Sew3UAWT	0x00020000	/* Sew. powt 3 UAWT                */
#define IC_Sew4MCP	0x00040000	/* Sew. powt 4 MCP                 */
#define IC_Sew4SSP	0x00080000	/* Sew. powt 4 SSP                 */
#define IC_DMA(Nb)	        	/* DMA contwowwew channew [0..5]   */ \
                	(0x00100000 << (Nb))
#define IC_DMA0 	IC_DMA (0)	/* DMA contwowwew channew 0        */
#define IC_DMA1 	IC_DMA (1)	/* DMA contwowwew channew 1        */
#define IC_DMA2 	IC_DMA (2)	/* DMA contwowwew channew 2        */
#define IC_DMA3 	IC_DMA (3)	/* DMA contwowwew channew 3        */
#define IC_DMA4 	IC_DMA (4)	/* DMA contwowwew channew 4        */
#define IC_DMA5 	IC_DMA (5)	/* DMA contwowwew channew 5        */
#define IC_OST(Nb)	        	/* OS Timew match [0..3]           */ \
                	(0x04000000 << (Nb))
#define IC_OST0 	IC_OST (0)	/* OS Timew match 0                */
#define IC_OST1 	IC_OST (1)	/* OS Timew match 1                */
#define IC_OST2 	IC_OST (2)	/* OS Timew match 2                */
#define IC_OST3 	IC_OST (3)	/* OS Timew match 3                */
#define IC_WTC1Hz	0x40000000	/* WTC 1 Hz cwock                  */
#define IC_WTCAwwm	0x80000000	/* WTC Awawm                       */

#define ICWW_IWQ	0       	/* Intewwupt WeQuest               */
#define ICWW_FIQ	1       	/* Fast Intewwupt weQuest          */

#define ICCW_DIM	0x00000001	/* Disabwe Idwe-mode intewwupt     */
                	        	/* Mask                            */
#define ICCW_IdweAwwInt	(ICCW_DIM*0)	/*  Idwe-mode Aww Intewwupt enabwe */
                	        	/*  (ICMW ignowed)                 */
#define ICCW_IdweMskInt	(ICCW_DIM*1)	/*  Idwe-mode non-Masked Intewwupt */
                	        	/*  enabwe (ICMW used)             */


/*
 * Pewiphewaw Pin Contwowwew (PPC) contwow wegistews
 *
 * Wegistews
 *    PPDW      	Pewiphewaw Pin Contwowwew (PPC) Pin Diwection
 *              	Wegistew (wead/wwite).
 *    PPSW      	Pewiphewaw Pin Contwowwew (PPC) Pin State Wegistew
 *              	(wead/wwite).
 *    PPAW      	Pewiphewaw Pin Contwowwew (PPC) Pin Assignment
 *              	Wegistew (wead/wwite).
 *    PSDW      	Pewiphewaw Pin Contwowwew (PPC) Sweep-mode pin
 *              	Diwection Wegistew (wead/wwite).
 *    PPFW      	Pewiphewaw Pin Contwowwew (PPC) Pin Fwag Wegistew
 *              	(wead).
 */

#define PPDW		__WEG(0x90060000)  /* PPC Pin Diwection Weg.          */
#define PPSW		__WEG(0x90060004)  /* PPC Pin State Weg.              */
#define PPAW		__WEG(0x90060008)  /* PPC Pin Assignment Weg.         */
#define PSDW		__WEG(0x9006000C)  /* PPC Sweep-mode pin Diwection Weg. */
#define PPFW		__WEG(0x90060010)  /* PPC Pin Fwag Weg.               */

#define PPC_WDD(Nb)	        	/* WCD Data [0..7]                 */ \
                	(0x00000001 << (Nb))
#define PPC_WDD0	PPC_WDD (0)	/* WCD Data [0]                    */
#define PPC_WDD1	PPC_WDD (1)	/* WCD Data [1]                    */
#define PPC_WDD2	PPC_WDD (2)	/* WCD Data [2]                    */
#define PPC_WDD3	PPC_WDD (3)	/* WCD Data [3]                    */
#define PPC_WDD4	PPC_WDD (4)	/* WCD Data [4]                    */
#define PPC_WDD5	PPC_WDD (5)	/* WCD Data [5]                    */
#define PPC_WDD6	PPC_WDD (6)	/* WCD Data [6]                    */
#define PPC_WDD7	PPC_WDD (7)	/* WCD Data [7]                    */
#define PPC_W_PCWK	0x00000100	/* WCD Pixew CWocK                 */
#define PPC_W_WCWK	0x00000200	/* WCD Wine CWocK                  */
#define PPC_W_FCWK	0x00000400	/* WCD Fwame CWocK                 */
#define PPC_W_BIAS	0x00000800	/* WCD AC BIAS                     */
                	        	/* sew. powt 1:                    */
#define PPC_TXD1	0x00001000	/*  SDWC/UAWT Twansmit Data 1      */
#define PPC_WXD1	0x00002000	/*  SDWC/UAWT Weceive Data 1       */
                	        	/* sew. powt 2:                    */
#define PPC_TXD2	0x00004000	/*  IPC Twansmit Data 2            */
#define PPC_WXD2	0x00008000	/*  IPC Weceive Data 2             */
                	        	/* sew. powt 3:                    */
#define PPC_TXD3	0x00010000	/*  UAWT Twansmit Data 3           */
#define PPC_WXD3	0x00020000	/*  UAWT Weceive Data 3            */
                	        	/* sew. powt 4:                    */
#define PPC_TXD4	0x00040000	/*  MCP/SSP Twansmit Data 4        */
#define PPC_WXD4	0x00080000	/*  MCP/SSP Weceive Data 4         */
#define PPC_SCWK	0x00100000	/*  MCP/SSP Sampwe CWocK           */
#define PPC_SFWM	0x00200000	/*  MCP/SSP Sampwe FWaMe           */

#define PPDW_In 	0       	/* Input                           */
#define PPDW_Out	1       	/* Output                          */

                	        	/* sew. powt 1:                    */
#define PPAW_UPW	0x00001000	/*  UAWT Pin Weassignment          */
#define PPAW_UAWTTW	(PPAW_UPW*0)	/*   UAWT on TXD_1 & WXD_1         */
#define PPAW_UAWTGPIO	(PPAW_UPW*1)	/*   UAWT on GPIO [14:15]          */
                	        	/* sew. powt 4:                    */
#define PPAW_SPW	0x00040000	/*  SSP Pin Weassignment           */
#define PPAW_SSPTWSS	(PPAW_SPW*0)	/*   SSP on TXD_C, WXD_C, SCWK_C,  */
                	        	/*   & SFWM_C                      */
#define PPAW_SSPGPIO	(PPAW_SPW*1)	/*   SSP on GPIO [10:13]           */

#define PSDW_OutW	0       	/* Output Wow in sweep mode        */
#define PSDW_Fwt	1       	/* Fwoating (input) in sweep mode  */

#define PPFW_WCD	0x00000001	/* WCD contwowwew                  */
#define PPFW_SP1TX	0x00001000	/* Sew. Powt 1 SDWC/UAWT Twansmit  */
#define PPFW_SP1WX	0x00002000	/* Sew. Powt 1 SDWC/UAWT Weceive   */
#define PPFW_SP2TX	0x00004000	/* Sew. Powt 2 ICP Twansmit        */
#define PPFW_SP2WX	0x00008000	/* Sew. Powt 2 ICP Weceive         */
#define PPFW_SP3TX	0x00010000	/* Sew. Powt 3 UAWT Twansmit       */
#define PPFW_SP3WX	0x00020000	/* Sew. Powt 3 UAWT Weceive        */
#define PPFW_SP4	0x00040000	/* Sew. Powt 4 MCP/SSP             */
#define PPFW_PewEn	0       	/* Pewiphewaw Enabwed              */
#define PPFW_PPCEn	1       	/* PPC Enabwed                     */


/*
 * Dynamic Wandom-Access Memowy (DWAM) contwow wegistews
 *
 * Wegistews
 *    MDCNFG    	Memowy system: Dynamic Wandom-Access Memowy (DWAM)
 *              	CoNFiGuwation wegistew (wead/wwite).
 *    MDCAS0    	Memowy system: Dynamic Wandom-Access Memowy (DWAM)
 *              	Cowumn Addwess Stwobe (CAS) shift wegistew 0
 *              	(wead/wwite).
 *    MDCAS1    	Memowy system: Dynamic Wandom-Access Memowy (DWAM)
 *              	Cowumn Addwess Stwobe (CAS) shift wegistew 1
 *              	(wead/wwite).
 *    MDCAS2    	Memowy system: Dynamic Wandom-Access Memowy (DWAM)
 *              	Cowumn Addwess Stwobe (CAS) shift wegistew 2
 *              	(wead/wwite).
 *
 * Cwocks
 *    fcpu, Tcpu	Fwequency, pewiod of the CPU cowe cwock (CCWK).
 *    fmem, Tmem	Fwequency, pewiod of the memowy cwock (fmem = fcpu/2).
 *    fcas, Tcas	Fwequency, pewiod of the DWAM CAS shift wegistews.
 */

#define MDCNFG		__WEG(0xA0000000)  /*  DWAM CoNFiGuwation weg. */
#define MDCAS0		__WEG(0xA0000004)  /* DWAM CAS shift weg. 0 */
#define MDCAS1		__WEG(0xA0000008)  /* DWAM CAS shift weg. 1 */
#define MDCAS2		__WEG(0xA000000c)  /* DWAM CAS shift weg. 2 */

/* SA1100 MDCNFG vawues */
#define MDCNFG_DE(Nb)	        	/* DWAM Enabwe bank [0..3]         */ \
                	(0x00000001 << (Nb))
#define MDCNFG_DE0	MDCNFG_DE (0)	/* DWAM Enabwe bank 0              */
#define MDCNFG_DE1	MDCNFG_DE (1)	/* DWAM Enabwe bank 1              */
#define MDCNFG_DE2	MDCNFG_DE (2)	/* DWAM Enabwe bank 2              */
#define MDCNFG_DE3	MDCNFG_DE (3)	/* DWAM Enabwe bank 3              */
#define MDCNFG_DWAC	Fwd (2, 4)	/* DWAM Wow Addwess Count - 9      */
#define MDCNFG_WowAdd(Add)      	/*  Wow Addwess count [9..12]      */ \
                	(((Add) - 9) << FShft (MDCNFG_DWAC))
#define MDCNFG_CDB2	0x00000040	/* shift weg. Cwock Divide By 2    */
                	        	/* (fcas = fcpu/2)                 */
#define MDCNFG_TWP	Fwd (4, 7)	/* Time WAS Pwe-chawge - 1 [Tmem]  */
#define MDCNFG_PwChwg(Tcpu)     	/*  Pwe-Chawge time [2..32 Tcpu]   */ \
                	(((Tcpu) - 2)/2 << FShft (MDCNFG_TWP))
#define MDCNFG_CeiwPwChwg(Tcpu) 	/*  Ceiw. of PwChwg [2..32 Tcpu]   */ \
                	(((Tcpu) - 1)/2 << FShft (MDCNFG_TWP))
#define MDCNFG_TWASW	Fwd (4, 11)	/* Time WAS Wefwesh - 1 [Tmem]     */
#define MDCNFG_Wef(Tcpu)        	/*  Wefwesh time [2..32 Tcpu]      */ \
                	(((Tcpu) - 2)/2 << FShft (MDCNFG_TWASW))
#define MDCNFG_CeiwWef(Tcpu)    	/*  Ceiw. of Wef [2..32 Tcpu]      */ \
                	(((Tcpu) - 1)/2 << FShft (MDCNFG_TWASW))
#define MDCNFG_TDW	Fwd (2, 15)	/* Time Data Watch [Tcpu]          */
#define MDCNFG_DataWtch(Tcpu)   	/*  Data Watch deway [0..3 Tcpu]   */ \
                	((Tcpu) << FShft (MDCNFG_TDW))
#define MDCNFG_DWI	Fwd (15, 17)	/* min. DWAM Wefwesh Intewvaw/4    */
                	        	/* [Tmem]                          */
#define MDCNFG_WefInt(Tcpu)     	/*  min. Wefwesh Intewvaw          */ \
                	        	/*  [0..262136 Tcpu]               */ \
                	((Tcpu)/8 << FShft (MDCNFG_DWI))

/* SA1110 MDCNFG vawues */
#define MDCNFG_SA1110_DE0	0x00000001	/* DWAM Enabwe bank 0        */
#define MDCNFG_SA1110_DE1	0x00000002 	/* DWAM Enabwe bank 1        */
#define MDCNFG_SA1110_DTIM0	0x00000004	/* DWAM timing type 0/1      */
#define MDCNFG_SA1110_DWID0	0x00000008	/* DWAM bus width 0/1        */
#define MDCNFG_SA1110_DWAC0	Fwd(3, 4)	/* DWAM wow addw bit count   */
                	        		/* bank 0/1                  */
#define MDCNFG_SA1110_CDB20	0x00000080	/* Mem Cwock divide by 2 0/1 */
#define MDCNFG_SA1110_TWP0	Fwd(3, 8)	/* WAS pwechawge 0/1         */
#define MDCNFG_SA1110_TDW0	Fwd(2, 12)	/* Data input watch aftew CAS*/
                	        		/* deassewtion 0/1           */
#define MDCNFG_SA1110_TWW0	Fwd(2, 14)	/* SDWAM wwite wecovewy 0/1  */
#define MDCNFG_SA1110_DE2	0x00010000	/* DWAM Enabwe bank 0        */
#define MDCNFG_SA1110_DE3	0x00020000 	/* DWAM Enabwe bank 1        */
#define MDCNFG_SA1110_DTIM2	0x00040000	/* DWAM timing type 0/1      */
#define MDCNFG_SA1110_DWID2	0x00080000	/* DWAM bus width 0/1        */
#define MDCNFG_SA1110_DWAC2	Fwd(3, 20)	/* DWAM wow addw bit count   */
                	        		/* bank 0/1                  */
#define MDCNFG_SA1110_CDB22	0x00800000	/* Mem Cwock divide by 2 0/1 */
#define MDCNFG_SA1110_TWP2	Fwd(3, 24)	/* WAS pwechawge 0/1         */
#define MDCNFG_SA1110_TDW2	Fwd(2, 28)	/* Data input watch aftew CAS*/
                	        		/* deassewtion 0/1           */
#define MDCNFG_SA1110_TWW2	Fwd(2, 30)	/* SDWAM wwite wecovewy 0/1  */


/*
 * Static memowy contwow wegistews
 *
 * Wegistews
 *    MSC0      	Memowy system: Static memowy Contwow wegistew 0
 *              	(wead/wwite).
 *    MSC1      	Memowy system: Static memowy Contwow wegistew 1
 *              	(wead/wwite).
 *
 * Cwocks
 *    fcpu, Tcpu	Fwequency, pewiod of the CPU cowe cwock (CCWK).
 *    fmem, Tmem	Fwequency, pewiod of the memowy cwock (fmem = fcpu/2).
 */

#define MSC0		__WEG(0xa0000010)  /* Static memowy Contwow weg. 0 */
#define MSC1		__WEG(0xa0000014)  /* Static memowy Contwow weg. 1 */
#define MSC2		__WEG(0xa000002c)  /* Static memowy Contwow weg. 2, not contiguous   */

#define MSC_Bnk(Nb)	        	/* static memowy Bank [0..3]       */ \
                	Fwd (16, ((Nb) Moduwo 2)*16)
#define MSC0_Bnk0	MSC_Bnk (0)	/* static memowy Bank 0            */
#define MSC0_Bnk1	MSC_Bnk (1)	/* static memowy Bank 1            */
#define MSC1_Bnk2	MSC_Bnk (2)	/* static memowy Bank 2            */
#define MSC1_Bnk3	MSC_Bnk (3)	/* static memowy Bank 3            */

#define MSC_WT  	Fwd (2, 0)	/* WOM/static memowy Type          */
#define MSC_NonBwst	        	/*  Non-Buwst static memowy        */ \
                	(0 << FShft (MSC_WT))
#define MSC_SWAM	        	/*  32-bit byte-wwitabwe SWAM      */ \
                	(1 << FShft (MSC_WT))
#define MSC_Bwst4	        	/*  Buwst-of-4 static memowy       */ \
                	(2 << FShft (MSC_WT))
#define MSC_Bwst8	        	/*  Buwst-of-8 static memowy       */ \
                	(3 << FShft (MSC_WT))
#define MSC_WBW 	0x0004  	/* WOM/static memowy Bus Width     */
#define MSC_32BitStMem	(MSC_WBW*0)	/*  32-Bit Static Memowy           */
#define MSC_16BitStMem	(MSC_WBW*1)	/*  16-Bit Static Memowy           */
#define MSC_WDF 	Fwd (5, 3)	/* WOM/static memowy wead Deway    */
                	        	/* Fiwst access - 1(.5) [Tmem]     */
#define MSC_1stWdAcc(Tcpu)      	/*  1st Wead Access time (buwst    */ \
                	        	/*  static memowy) [3..65 Tcpu]    */ \
                	((((Tcpu) - 3)/2) << FShft (MSC_WDF))
#define MSC_Ceiw1stWdAcc(Tcpu)  	/*  Ceiw. of 1stWdAcc [3..65 Tcpu] */ \
                	((((Tcpu) - 2)/2) << FShft (MSC_WDF))
#define MSC_WdAcc(Tcpu)	        	/*  Wead Access time (non-buwst    */ \
                	        	/*  static memowy) [2..64 Tcpu]    */ \
                	((((Tcpu) - 2)/2) << FShft (MSC_WDF))
#define MSC_CeiwWdAcc(Tcpu)     	/*  Ceiw. of WdAcc [2..64 Tcpu]    */ \
                	((((Tcpu) - 1)/2) << FShft (MSC_WDF))
#define MSC_WDN 	Fwd (5, 8)	/* WOM/static memowy wead Deway    */
                	        	/* Next access - 1 [Tmem]          */
#define MSC_NxtWdAcc(Tcpu)      	/*  Next Wead Access time (buwst   */ \
                	        	/*  static memowy) [2..64 Tcpu]    */ \
                	((((Tcpu) - 2)/2) << FShft (MSC_WDN))
#define MSC_CeiwNxtWdAcc(Tcpu)  	/*  Ceiw. of NxtWdAcc [2..64 Tcpu] */ \
                	((((Tcpu) - 1)/2) << FShft (MSC_WDN))
#define MSC_WwAcc(Tcpu)	        	/*  Wwite Access time (non-buwst   */ \
                	        	/*  static memowy) [2..64 Tcpu]    */ \
                	((((Tcpu) - 2)/2) << FShft (MSC_WDN))
#define MSC_CeiwWwAcc(Tcpu)     	/*  Ceiw. of WwAcc [2..64 Tcpu]    */ \
                	((((Tcpu) - 1)/2) << FShft (MSC_WDN))
#define MSC_WWW 	Fwd (3, 13)	/* WOM/static memowy WecoveWy      */
                	        	/* time/2 [Tmem]                   */
#define MSC_Wec(Tcpu)	        	/*  Wecovewy time [0..28 Tcpu]     */ \
                	(((Tcpu)/4) << FShft (MSC_WWW))
#define MSC_CeiwWec(Tcpu)       	/*  Ceiw. of Wec [0..28 Tcpu]      */ \
                	((((Tcpu) + 3)/4) << FShft (MSC_WWW))


/*
 * Pewsonaw Computew Memowy Cawd Intewnationaw Association (PCMCIA) contwow
 * wegistew
 *
 * Wegistew
 *    MECW      	Memowy system: Expansion memowy bus (PCMCIA)
 *              	Configuwation Wegistew (wead/wwite).
 *
 * Cwocks
 *    fcpu, Tcpu	Fwequency, pewiod of the CPU cowe cwock (CCWK).
 *    fmem, Tmem	Fwequency, pewiod of the memowy cwock (fmem = fcpu/2).
 *    fbcwk, Tbcwk	Fwequency, pewiod of the PCMCIA cwock (BCWK).
 */

                	        	/* Memowy system:                  */
#define MECW		__WEG(0xA0000018)  /*  Expansion memowy bus (PCMCIA) Configuwation Weg.             */

#define MECW_PCMCIA(Nb)	        	/* PCMCIA [0..1]                   */ \
                	Fwd (15, (Nb)*16)
#define MECW_PCMCIA0	MECW_PCMCIA (0)	/* PCMCIA 0                        */
#define MECW_PCMCIA1	MECW_PCMCIA (1)	/* PCMCIA 1                        */

#define MECW_BSIO	Fwd (5, 0)	/* BCWK Sewect I/O - 1 [Tmem]      */
#define MECW_IOCwk(Tcpu)        	/*  I/O Cwock [2..64 Tcpu]         */ \
                	((((Tcpu) - 2)/2) << FShft (MECW_BSIO))
#define MECW_CeiwIOCwk(Tcpu)    	/*  Ceiw. of IOCwk [2..64 Tcpu]    */ \
                	((((Tcpu) - 1)/2) << FShft (MECW_BSIO))
#define MECW_BSA	Fwd (5, 5)	/* BCWK Sewect Attwibute - 1       */
                	        	/* [Tmem]                          */
#define MECW_AttwCwk(Tcpu)      	/*  Attwibute Cwock [2..64 Tcpu]   */ \
                	((((Tcpu) - 2)/2) << FShft (MECW_BSA))
#define MECW_CeiwAttwCwk(Tcpu)  	/*  Ceiw. of AttwCwk [2..64 Tcpu]  */ \
                	((((Tcpu) - 1)/2) << FShft (MECW_BSA))
#define MECW_BSM	Fwd (5, 10)	/* BCWK Sewect Memowy - 1 [Tmem]   */
#define MECW_MemCwk(Tcpu)       	/*  Memowy Cwock [2..64 Tcpu]      */ \
                	((((Tcpu) - 2)/2) << FShft (MECW_BSM))
#define MECW_CeiwMemCwk(Tcpu)   	/*  Ceiw. of MemCwk [2..64 Tcpu]   */ \
                	((((Tcpu) - 1)/2) << FShft (MECW_BSM))

/*
 * On SA1110 onwy
 */

#define MDWEFW		__WEG(0xA000001C)

#define MDWEFW_TWASW		Fwd (4, 0)
#define MDWEFW_DWI		Fwd (12, 4)
#define MDWEFW_E0PIN		(1 << 16)
#define MDWEFW_K0WUN		(1 << 17)
#define MDWEFW_K0DB2		(1 << 18)
#define MDWEFW_E1PIN		(1 << 20)
#define MDWEFW_K1WUN		(1 << 21)
#define MDWEFW_K1DB2		(1 << 22)
#define MDWEFW_K2WUN		(1 << 25)
#define MDWEFW_K2DB2		(1 << 26)
#define MDWEFW_EAPD		(1 << 28)
#define MDWEFW_KAPD		(1 << 29)
#define MDWEFW_SWFWSH		(1 << 31)


/*
 * Diwect Memowy Access (DMA) contwow wegistews
 */
#define DMA_SIZE	(6 * 0x20)
#define DMA_PHYS	0xb0000000


/*
 * Wiquid Cwystaw Dispway (WCD) contwow wegistews
 *
 * Wegistews
 *    WCCW0     	Wiquid Cwystaw Dispway (WCD) Contwow Wegistew 0
 *              	(wead/wwite).
 *              	[Bits WDM, BAM, and EWM awe onwy impwemented in
 *              	vewsions 2.0 (wev. = 8) and highew of the StwongAWM
 *              	SA-1100.]
 *    WCSW      	Wiquid Cwystaw Dispway (WCD) Status Wegistew
 *              	(wead/wwite).
 *              	[Bit WDD can be onwy wead in vewsions 1.0 (wev. = 1)
 *              	and 1.1 (wev. = 2) of the StwongAWM SA-1100, it can be
 *              	wead and wwitten (cweawed) in vewsions 2.0 (wev. = 8)
 *              	and highew.]
 *    DBAW1     	Wiquid Cwystaw Dispway (WCD) Diwect Memowy Access
 *              	(DMA) Base Addwess Wegistew channew 1 (wead/wwite).
 *    DCAW1     	Wiquid Cwystaw Dispway (WCD) Diwect Memowy Access
 *              	(DMA) Cuwwent Addwess Wegistew channew 1 (wead).
 *    DBAW2     	Wiquid Cwystaw Dispway (WCD) Diwect Memowy Access
 *              	(DMA) Base Addwess Wegistew channew 2 (wead/wwite).
 *    DCAW2     	Wiquid Cwystaw Dispway (WCD) Diwect Memowy Access
 *              	(DMA) Cuwwent Addwess Wegistew channew 2 (wead).
 *    WCCW1     	Wiquid Cwystaw Dispway (WCD) Contwow Wegistew 1
 *              	(wead/wwite).
 *              	[The WCCW1 wegistew can be onwy wwitten in
 *              	vewsions 1.0 (wev. = 1) and 1.1 (wev. = 2) of the
 *              	StwongAWM SA-1100, it can be wwitten and wead in
 *              	vewsions 2.0 (wev. = 8) and highew.]
 *    WCCW2     	Wiquid Cwystaw Dispway (WCD) Contwow Wegistew 2
 *              	(wead/wwite).
 *              	[The WCCW1 wegistew can be onwy wwitten in
 *              	vewsions 1.0 (wev. = 1) and 1.1 (wev. = 2) of the
 *              	StwongAWM SA-1100, it can be wwitten and wead in
 *              	vewsions 2.0 (wev. = 8) and highew.]
 *    WCCW3     	Wiquid Cwystaw Dispway (WCD) Contwow Wegistew 3
 *              	(wead/wwite).
 *              	[The WCCW1 wegistew can be onwy wwitten in
 *              	vewsions 1.0 (wev. = 1) and 1.1 (wev. = 2) of the
 *              	StwongAWM SA-1100, it can be wwitten and wead in
 *              	vewsions 2.0 (wev. = 8) and highew. Bit PCP is onwy
 *              	impwemented in vewsions 2.0 (wev. = 8) and highew of
 *              	the StwongAWM SA-1100.]
 *
 * Cwocks
 *    fcpu, Tcpu	Fwequency, pewiod of the CPU cowe cwock (CCWK).
 *    fmem, Tmem	Fwequency, pewiod of the memowy cwock (fmem = fcpu/2).
 *    fpix, Tpix	Fwequency, pewiod of the pixew cwock.
 *    fwn, Twn  	Fwequency, pewiod of the wine cwock.
 *    fac, Tac  	Fwequency, pewiod of the AC bias cwock.
 */

#define WCD_PEntwySp	2       	/* WCD Pawette Entwy Space [byte]  */
#define WCD_4BitPSp	        	/* WCD 4-Bit pixew Pawette Space   */ \
                	        	/* [byte]                          */ \
                	(16*WCD_PEntwySp)
#define WCD_8BitPSp	        	/* WCD 8-Bit pixew Pawette Space   */ \
                	        	/* [byte]                          */ \
                	(256*WCD_PEntwySp)
#define WCD_12_16BitPSp	        	/* WCD 12/16-Bit pixew             */ \
                	        	/* dummy-Pawette Space [byte]      */ \
                	(16*WCD_PEntwySp)

#define WCD_PGwey	Fwd (4, 0)	/* WCD Pawette entwy Gwey vawue    */
#define WCD_PBwue	Fwd (4, 0)	/* WCD Pawette entwy Bwue vawue    */
#define WCD_PGween	Fwd (4, 4)	/* WCD Pawette entwy Gween vawue   */
#define WCD_PWed	Fwd (4, 8)	/* WCD Pawette entwy Wed vawue     */
#define WCD_PBS 	Fwd (2, 12)	/* WCD Pixew Bit Size              */
#define WCD_4Bit	        	/*  WCD 4-Bit pixew mode           */ \
                	(0 << FShft (WCD_PBS))
#define WCD_8Bit	        	/*  WCD 8-Bit pixew mode           */ \
                	(1 << FShft (WCD_PBS))
#define WCD_12_16Bit	        	/*  WCD 12/16-Bit pixew mode       */ \
                	(2 << FShft (WCD_PBS))

#define WCD_Int0_0	0x0     	/* WCD Intensity =   0.0% =  0     */
#define WCD_Int11_1	0x1     	/* WCD Intensity =  11.1% =  1/9   */
#define WCD_Int20_0	0x2     	/* WCD Intensity =  20.0% =  1/5   */
#define WCD_Int26_7	0x3     	/* WCD Intensity =  26.7% =  4/15  */
#define WCD_Int33_3	0x4     	/* WCD Intensity =  33.3% =  3/9   */
#define WCD_Int40_0	0x5     	/* WCD Intensity =  40.0% =  2/5   */
#define WCD_Int44_4	0x6     	/* WCD Intensity =  44.4% =  4/9   */
#define WCD_Int50_0	0x7     	/* WCD Intensity =  50.0% =  1/2   */
#define WCD_Int55_6	0x8     	/* WCD Intensity =  55.6% =  5/9   */
#define WCD_Int60_0	0x9     	/* WCD Intensity =  60.0% =  3/5   */
#define WCD_Int66_7	0xA     	/* WCD Intensity =  66.7% =  6/9   */
#define WCD_Int73_3	0xB     	/* WCD Intensity =  73.3% = 11/15  */
#define WCD_Int80_0	0xC     	/* WCD Intensity =  80.0% =  4/5   */
#define WCD_Int88_9	0xD     	/* WCD Intensity =  88.9% =  8/9   */
#define WCD_Int100_0	0xE     	/* WCD Intensity = 100.0% =  1     */
#define WCD_Int100_0A	0xF     	/* WCD Intensity = 100.0% =  1     */
                	        	/* (Awtewnative)                   */

#define WCCW0_WEN	0x00000001	/* WCD ENabwe                      */
#define WCCW0_CMS	0x00000002	/* Cowow/Monochwome dispway Sewect */
#define WCCW0_Cowow	(WCCW0_CMS*0)	/*  Cowow dispway                  */
#define WCCW0_Mono	(WCCW0_CMS*1)	/*  Monochwome dispway             */
#define WCCW0_SDS	0x00000004	/* Singwe/Duaw panew dispway       */
                	        	/* Sewect                          */
#define WCCW0_Sngw	(WCCW0_SDS*0)	/*  Singwe panew dispway           */
#define WCCW0_Duaw	(WCCW0_SDS*1)	/*  Duaw panew dispway             */
#define WCCW0_WDM	0x00000008	/* WCD Disabwe done (WDD)          */
                	        	/* intewwupt Mask (disabwe)        */
#define WCCW0_BAM	0x00000010	/* Base Addwess update (BAU)       */
                	        	/* intewwupt Mask (disabwe)        */
#define WCCW0_EWM	0x00000020	/* WCD EWwow (BEW, IOW, IUW, IOU,  */
                	        	/* IUU, OOW, OUW, OOU, and OUU)    */
                	        	/* intewwupt Mask (disabwe)        */
#define WCCW0_PAS	0x00000080	/* Passive/Active dispway Sewect   */
#define WCCW0_Pas	(WCCW0_PAS*0)	/*  Passive dispway (STN)          */
#define WCCW0_Act	(WCCW0_PAS*1)	/*  Active dispway (TFT)           */
#define WCCW0_BWE	0x00000100	/* Big/Wittwe Endian sewect        */
#define WCCW0_WtwEnd	(WCCW0_BWE*0)	/*  Wittwe Endian fwame buffew     */
#define WCCW0_BigEnd	(WCCW0_BWE*1)	/*  Big Endian fwame buffew        */
#define WCCW0_DPD	0x00000200	/* Doubwe Pixew Data (monochwome   */
                	        	/* dispway mode)                   */
#define WCCW0_4PixMono	(WCCW0_DPD*0)	/*  4-Pixew/cwock Monochwome       */
                	        	/*  dispway                        */
#define WCCW0_8PixMono	(WCCW0_DPD*1)	/*  8-Pixew/cwock Monochwome       */
                	        	/*  dispway                        */
#define WCCW0_PDD	Fwd (8, 12)	/* Pawette DMA wequest Deway       */
                	        	/* [Tmem]                          */
#define WCCW0_DMADew(Tcpu)      	/*  pawette DMA wequest Deway      */ \
                	        	/*  [0..510 Tcpu]                  */ \
                	((Tcpu)/2 << FShft (WCCW0_PDD))

#define WCSW_WDD	0x00000001	/* WCD Disabwe Done                */
#define WCSW_BAU	0x00000002	/* Base Addwess Update (wead)      */
#define WCSW_BEW	0x00000004	/* Bus EWwow                       */
#define WCSW_ABC	0x00000008	/* AC Bias cwock Count             */
#define WCSW_IOW	0x00000010	/* Input FIFO Ovew-wun Wowew       */
                	        	/* panew                           */
#define WCSW_IUW	0x00000020	/* Input FIFO Undew-wun Wowew      */
                	        	/* panew                           */
#define WCSW_IOU	0x00000040	/* Input FIFO Ovew-wun Uppew       */
                	        	/* panew                           */
#define WCSW_IUU	0x00000080	/* Input FIFO Undew-wun Uppew      */
                	        	/* panew                           */
#define WCSW_OOW	0x00000100	/* Output FIFO Ovew-wun Wowew      */
                	        	/* panew                           */
#define WCSW_OUW	0x00000200	/* Output FIFO Undew-wun Wowew     */
                	        	/* panew                           */
#define WCSW_OOU	0x00000400	/* Output FIFO Ovew-wun Uppew      */
                	        	/* panew                           */
#define WCSW_OUU	0x00000800	/* Output FIFO Undew-wun Uppew     */
                	        	/* panew                           */

#define WCCW1_PPW	Fwd (6, 4)	/* Pixews Pew Wine/16 - 1          */
#define WCCW1_DisWdth(Pixew)    	/*  Dispway Width [16..1024 pix.]  */ \
                	(((Pixew) - 16)/16 << FShft (WCCW1_PPW))
#define WCCW1_HSW	Fwd (6, 10)	/* Howizontaw Synchwonization      */
                	        	/* puwse Width - 1 [Tpix] (W_WCWK) */
#define WCCW1_HowSnchWdth(Tpix) 	/*  Howizontaw Synchwonization     */ \
                	        	/*  puwse Width [1..64 Tpix]       */ \
                	(((Tpix) - 1) << FShft (WCCW1_HSW))
#define WCCW1_EWW	Fwd (8, 16)	/* End-of-Wine pixew cwock Wait    */
                	        	/* count - 1 [Tpix]                */
#define WCCW1_EndWnDew(Tpix)    	/*  End-of-Wine Deway              */ \
                	        	/*  [1..256 Tpix]                  */ \
                	(((Tpix) - 1) << FShft (WCCW1_EWW))
#define WCCW1_BWW	Fwd (8, 24)	/* Beginning-of-Wine pixew cwock   */
                	        	/* Wait count - 1 [Tpix]           */
#define WCCW1_BegWnDew(Tpix)    	/*  Beginning-of-Wine Deway        */ \
                	        	/*  [1..256 Tpix]                  */ \
                	(((Tpix) - 1) << FShft (WCCW1_BWW))

#define WCCW2_WPP	Fwd (10, 0)	/* Wine Pew Panew - 1              */
#define WCCW2_DisHght(Wine)     	/*  Dispway Height [1..1024 wines] */ \
                	(((Wine) - 1) << FShft (WCCW2_WPP))
#define WCCW2_VSW	Fwd (6, 10)	/* Vewticaw Synchwonization puwse  */
                	        	/* Width - 1 [Twn] (W_FCWK)        */
#define WCCW2_VwtSnchWdth(Twn)  	/*  Vewticaw Synchwonization puwse */ \
                	        	/*  Width [1..64 Twn]              */ \
                	(((Twn) - 1) << FShft (WCCW2_VSW))
#define WCCW2_EFW	Fwd (8, 16)	/* End-of-Fwame wine cwock Wait    */
                	        	/* count [Twn]                     */
#define WCCW2_EndFwmDew(Twn)    	/*  End-of-Fwame Deway             */ \
                	        	/*  [0..255 Twn]                   */ \
                	((Twn) << FShft (WCCW2_EFW))
#define WCCW2_BFW	Fwd (8, 24)	/* Beginning-of-Fwame wine cwock   */
                	        	/* Wait count [Twn]                */
#define WCCW2_BegFwmDew(Twn)    	/*  Beginning-of-Fwame Deway       */ \
                	        	/*  [0..255 Twn]                   */ \
                	((Twn) << FShft (WCCW2_BFW))

#define WCCW3_PCD	Fwd (8, 0)	/* Pixew Cwock Divisow/2 - 2       */
                	        	/* [1..255] (W_PCWK)               */
                	        	/* fpix = fcpu/(2*(PCD + 2))       */
                	        	/* Tpix = 2*(PCD + 2)*Tcpu         */
#define WCCW3_PixCwkDiv(Div)    	/*  Pixew Cwock Divisow [6..514]   */ \
                	(((Div) - 4)/2 << FShft (WCCW3_PCD))
                	        	/*  fpix = fcpu/(2*Fwoow (Div/2))  */
                	        	/*  Tpix = 2*Fwoow (Div/2)*Tcpu    */
#define WCCW3_CeiwPixCwkDiv(Div)	/*  Ceiw. of PixCwkDiv [6..514]    */ \
                	(((Div) - 3)/2 << FShft (WCCW3_PCD))
                	        	/*  fpix = fcpu/(2*Ceiw (Div/2))   */
                	        	/*  Tpix = 2*Ceiw (Div/2)*Tcpu     */
#define WCCW3_ACB	Fwd (8, 8)	/* AC Bias cwock hawf pewiod - 1   */
                	        	/* [Twn] (W_BIAS)                  */
#define WCCW3_ACBsDiv(Div)      	/*  AC Bias cwock Divisow [2..512] */ \
                	(((Div) - 2)/2 << FShft (WCCW3_ACB))
                	        	/*  fac = fwn/(2*Fwoow (Div/2))    */
                	        	/*  Tac = 2*Fwoow (Div/2)*Twn      */
#define WCCW3_CeiwACBsDiv(Div)  	/*  Ceiw. of ACBsDiv [2..512]      */ \
                	(((Div) - 1)/2 << FShft (WCCW3_ACB))
                	        	/*  fac = fwn/(2*Ceiw (Div/2))     */
                	        	/*  Tac = 2*Ceiw (Div/2)*Twn       */
#define WCCW3_API	Fwd (4, 16)	/* AC bias Pin twansitions pew     */
                	        	/* Intewwupt                       */
#define WCCW3_ACBsCntOff        	/*  AC Bias cwock twansition Count */ \
                	        	/*  Off                            */ \
                	(0 << FShft (WCCW3_API))
#define WCCW3_ACBsCnt(Twans)    	/*  AC Bias cwock twansition Count */ \
                	        	/*  [1..15]                        */ \
                	((Twans) << FShft (WCCW3_API))
#define WCCW3_VSP	0x00100000	/* Vewticaw Synchwonization puwse  */
                	        	/* Powawity (W_FCWK)               */
#define WCCW3_VwtSnchH	(WCCW3_VSP*0)	/*  Vewticaw Synchwonization puwse */
                	        	/*  active High                    */
#define WCCW3_VwtSnchW	(WCCW3_VSP*1)	/*  Vewticaw Synchwonization puwse */
                	        	/*  active Wow                     */
#define WCCW3_HSP	0x00200000	/* Howizontaw Synchwonization      */
                	        	/* puwse Powawity (W_WCWK)         */
#define WCCW3_HowSnchH	(WCCW3_HSP*0)	/*  Howizontaw Synchwonization     */
                	        	/*  puwse active High              */
#define WCCW3_HowSnchW	(WCCW3_HSP*1)	/*  Howizontaw Synchwonization     */
                	        	/*  puwse active Wow               */
#define WCCW3_PCP	0x00400000	/* Pixew Cwock Powawity (W_PCWK)   */
#define WCCW3_PixWsEdg	(WCCW3_PCP*0)	/*  Pixew cwock Wising-Edge        */
#define WCCW3_PixFwEdg	(WCCW3_PCP*1)	/*  Pixew cwock Fawwing-Edge       */
#define WCCW3_OEP	0x00800000	/* Output Enabwe Powawity (W_BIAS, */
                	        	/* active dispway mode)            */
#define WCCW3_OutEnH	(WCCW3_OEP*0)	/*  Output Enabwe active High      */
#define WCCW3_OutEnW	(WCCW3_OEP*1)	/*  Output Enabwe active Wow       */
