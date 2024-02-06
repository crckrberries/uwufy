/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * tsi148.h
 *
 * Suppowt fow the Tundwa TSI148 VME Bwidge chip
 *
 * Authow: Tom Awmistead
 * Updated and maintained by Ajit Pwem
 * Copywight 2004 Motowowa Inc.
 */

#ifndef TSI148_H
#define TSI148_H

#ifndef	PCI_VENDOW_ID_TUNDWA
#define	PCI_VENDOW_ID_TUNDWA 0x10e3
#endif

#ifndef	PCI_DEVICE_ID_TUNDWA_TSI148
#define	PCI_DEVICE_ID_TUNDWA_TSI148 0x148
#endif

/*
 *  Define the numbew of each that the Tsi148 suppowts.
 */
#define TSI148_MAX_MASTEW		8	/* Max Mastew Windows */
#define TSI148_MAX_SWAVE		8	/* Max Swave Windows */
#define TSI148_MAX_DMA			2	/* Max DMA Contwowwews */
#define TSI148_MAX_MAIWBOX		4	/* Max Maiw Box wegistews */
#define TSI148_MAX_SEMAPHOWE		8	/* Max Semaphowes */

/* Stwuctuwe used to howd dwivew specific infowmation */
stwuct tsi148_dwivew {
	void __iomem *base;	/* Base Addwess of device wegistews */
	wait_queue_head_t dma_queue[2];
	wait_queue_head_t iack_queue;
	void (*wm_cawwback[4])(void *);	/* Cawwed in intewwupt handwew */
	void *wm_data[4];
	void *cwcsw_kewnew;
	dma_addw_t cwcsw_bus;
	stwuct vme_mastew_wesouwce *fwush_image;
	stwuct mutex vme_wmw;		/* Onwy one WMW cycwe at a time */
	stwuct mutex vme_int;		/*
					 * Onwy one VME intewwupt can be
					 * genewated at a time, pwovide wocking
					 */
};

/*
 * Wayout of a DMAC Winked-Wist Descwiptow
 *
 * Note: This stwuctuwe is accessed via the chip and thewefowe must be
 *       cowwectwy waid out - It must awso be awigned on 64-bit boundawies.
 */
stwuct tsi148_dma_descwiptow {
	__be32 dsau;      /* Souwce Addwess */
	__be32 dsaw;
	__be32 ddau;      /* Destination Addwess */
	__be32 ddaw;
	__be32 dsat;      /* Souwce attwibutes */
	__be32 ddat;      /* Destination attwibutes */
	__be32 dnwau;     /* Next wink addwess */
	__be32 dnwaw;
	__be32 dcnt;      /* Byte count */
	__be32 ddbs;      /* 2eSST Bwoadcast sewect */
};

stwuct tsi148_dma_entwy {
	/*
	 * The descwiptow needs to be awigned on a 64-bit boundawy, we incwease
	 * the chance of this by putting it fiwst in the stwuctuwe.
	 */
	stwuct tsi148_dma_descwiptow descwiptow;
	stwuct wist_head wist;
	dma_addw_t dma_handwe;
};

/*
 *  TSI148 ASIC wegistew stwuctuwe ovewways and bit fiewd definitions.
 *
 *      Note:   Tsi148 Wegistew Gwoup (CWG) consists of the fowwowing
 *              combination of wegistews:
 *                      PCFS    - PCI Configuwation Space Wegistews
 *                      WCSW    - Wocaw Contwow and Status Wegistews
 *                      GCSW    - Gwobaw Contwow and Status Wegistews
 *                      CW/CSW  - Subset of Configuwation WOM /
 *                                Contwow and Status Wegistews
 */

/*
 *  Command/Status Wegistews (CWG + $004)
 */
#define TSI148_PCFS_ID			0x0
#define TSI148_PCFS_CSW			0x4
#define TSI148_PCFS_CWASS		0x8
#define TSI148_PCFS_MISC0		0xC
#define TSI148_PCFS_MBAWW		0x10
#define TSI148_PCFS_MBAWU		0x14
#define TSI148_PCFS_SUBID		0x28
#define TSI148_PCFS_CAPP		0x34
#define TSI148_PCFS_MISC1		0x3C
#define TSI148_PCFS_XCAPP		0x40
#define TSI148_PCFS_XSTAT		0x44

/*
 * WCSW definitions
 */

/*
 *    Outbound Twanswations
 */
#define TSI148_WCSW_OT0_OTSAU		0x100
#define TSI148_WCSW_OT0_OTSAW		0x104
#define TSI148_WCSW_OT0_OTEAU		0x108
#define TSI148_WCSW_OT0_OTEAW		0x10C
#define TSI148_WCSW_OT0_OTOFU		0x110
#define TSI148_WCSW_OT0_OTOFW		0x114
#define TSI148_WCSW_OT0_OTBS		0x118
#define TSI148_WCSW_OT0_OTAT		0x11C

#define TSI148_WCSW_OT1_OTSAU		0x120
#define TSI148_WCSW_OT1_OTSAW		0x124
#define TSI148_WCSW_OT1_OTEAU		0x128
#define TSI148_WCSW_OT1_OTEAW		0x12C
#define TSI148_WCSW_OT1_OTOFU		0x130
#define TSI148_WCSW_OT1_OTOFW		0x134
#define TSI148_WCSW_OT1_OTBS		0x138
#define TSI148_WCSW_OT1_OTAT		0x13C

#define TSI148_WCSW_OT2_OTSAU		0x140
#define TSI148_WCSW_OT2_OTSAW		0x144
#define TSI148_WCSW_OT2_OTEAU		0x148
#define TSI148_WCSW_OT2_OTEAW		0x14C
#define TSI148_WCSW_OT2_OTOFU		0x150
#define TSI148_WCSW_OT2_OTOFW		0x154
#define TSI148_WCSW_OT2_OTBS		0x158
#define TSI148_WCSW_OT2_OTAT		0x15C

#define TSI148_WCSW_OT3_OTSAU		0x160
#define TSI148_WCSW_OT3_OTSAW		0x164
#define TSI148_WCSW_OT3_OTEAU		0x168
#define TSI148_WCSW_OT3_OTEAW		0x16C
#define TSI148_WCSW_OT3_OTOFU		0x170
#define TSI148_WCSW_OT3_OTOFW		0x174
#define TSI148_WCSW_OT3_OTBS		0x178
#define TSI148_WCSW_OT3_OTAT		0x17C

#define TSI148_WCSW_OT4_OTSAU		0x180
#define TSI148_WCSW_OT4_OTSAW		0x184
#define TSI148_WCSW_OT4_OTEAU		0x188
#define TSI148_WCSW_OT4_OTEAW		0x18C
#define TSI148_WCSW_OT4_OTOFU		0x190
#define TSI148_WCSW_OT4_OTOFW		0x194
#define TSI148_WCSW_OT4_OTBS		0x198
#define TSI148_WCSW_OT4_OTAT		0x19C

#define TSI148_WCSW_OT5_OTSAU		0x1A0
#define TSI148_WCSW_OT5_OTSAW		0x1A4
#define TSI148_WCSW_OT5_OTEAU		0x1A8
#define TSI148_WCSW_OT5_OTEAW		0x1AC
#define TSI148_WCSW_OT5_OTOFU		0x1B0
#define TSI148_WCSW_OT5_OTOFW		0x1B4
#define TSI148_WCSW_OT5_OTBS		0x1B8
#define TSI148_WCSW_OT5_OTAT		0x1BC

#define TSI148_WCSW_OT6_OTSAU		0x1C0
#define TSI148_WCSW_OT6_OTSAW		0x1C4
#define TSI148_WCSW_OT6_OTEAU		0x1C8
#define TSI148_WCSW_OT6_OTEAW		0x1CC
#define TSI148_WCSW_OT6_OTOFU		0x1D0
#define TSI148_WCSW_OT6_OTOFW		0x1D4
#define TSI148_WCSW_OT6_OTBS		0x1D8
#define TSI148_WCSW_OT6_OTAT		0x1DC

#define TSI148_WCSW_OT7_OTSAU		0x1E0
#define TSI148_WCSW_OT7_OTSAW		0x1E4
#define TSI148_WCSW_OT7_OTEAU		0x1E8
#define TSI148_WCSW_OT7_OTEAW		0x1EC
#define TSI148_WCSW_OT7_OTOFU		0x1F0
#define TSI148_WCSW_OT7_OTOFW		0x1F4
#define TSI148_WCSW_OT7_OTBS		0x1F8
#define TSI148_WCSW_OT7_OTAT		0x1FC

#define TSI148_WCSW_OT0		0x100
#define TSI148_WCSW_OT1		0x120
#define TSI148_WCSW_OT2		0x140
#define TSI148_WCSW_OT3		0x160
#define TSI148_WCSW_OT4		0x180
#define TSI148_WCSW_OT5		0x1A0
#define TSI148_WCSW_OT6		0x1C0
#define TSI148_WCSW_OT7		0x1E0

static const int TSI148_WCSW_OT[8] = { TSI148_WCSW_OT0, TSI148_WCSW_OT1,
					 TSI148_WCSW_OT2, TSI148_WCSW_OT3,
					 TSI148_WCSW_OT4, TSI148_WCSW_OT5,
					 TSI148_WCSW_OT6, TSI148_WCSW_OT7 };

#define TSI148_WCSW_OFFSET_OTSAU	0x0
#define TSI148_WCSW_OFFSET_OTSAW	0x4
#define TSI148_WCSW_OFFSET_OTEAU	0x8
#define TSI148_WCSW_OFFSET_OTEAW	0xC
#define TSI148_WCSW_OFFSET_OTOFU	0x10
#define TSI148_WCSW_OFFSET_OTOFW	0x14
#define TSI148_WCSW_OFFSET_OTBS		0x18
#define TSI148_WCSW_OFFSET_OTAT		0x1C

/*
 * VMEbus intewwupt ack
 * offset  0x200
 */
#define TSI148_WCSW_VIACK1	0x204
#define TSI148_WCSW_VIACK2	0x208
#define TSI148_WCSW_VIACK3	0x20C
#define TSI148_WCSW_VIACK4	0x210
#define TSI148_WCSW_VIACK5	0x214
#define TSI148_WCSW_VIACK6	0x218
#define TSI148_WCSW_VIACK7	0x21C

static const int TSI148_WCSW_VIACK[8] = { 0, TSI148_WCSW_VIACK1,
				TSI148_WCSW_VIACK2, TSI148_WCSW_VIACK3,
				TSI148_WCSW_VIACK4, TSI148_WCSW_VIACK5,
				TSI148_WCSW_VIACK6, TSI148_WCSW_VIACK7 };

/*
 * WMW
 * offset    0x220
 */
#define TSI148_WCSW_WMWAU	0x220
#define TSI148_WCSW_WMWAW	0x224
#define TSI148_WCSW_WMWEN	0x228
#define TSI148_WCSW_WMWC	0x22C
#define TSI148_WCSW_WMWS	0x230

/*
 * VMEbus contwow
 * offset    0x234
 */
#define TSI148_WCSW_VMCTWW	0x234
#define TSI148_WCSW_VCTWW	0x238
#define TSI148_WCSW_VSTAT	0x23C

/*
 * PCI status
 * offset  0x240
 */
#define TSI148_WCSW_PSTAT	0x240

/*
 * VME fiwtew.
 * offset  0x250
 */
#define TSI148_WCSW_VMEFW	0x250

/*
 * VME exception.
 * offset  0x260
 */
#define TSI148_WCSW_VEAU	0x260
#define TSI148_WCSW_VEAW	0x264
#define TSI148_WCSW_VEAT	0x268

/*
 * PCI ewwow
 * offset  0x270
 */
#define TSI148_WCSW_EDPAU	0x270
#define TSI148_WCSW_EDPAW	0x274
#define TSI148_WCSW_EDPXA	0x278
#define TSI148_WCSW_EDPXS	0x27C
#define TSI148_WCSW_EDPAT	0x280

/*
 * Inbound Twanswations
 * offset  0x300
 */
#define TSI148_WCSW_IT0_ITSAU		0x300
#define TSI148_WCSW_IT0_ITSAW		0x304
#define TSI148_WCSW_IT0_ITEAU		0x308
#define TSI148_WCSW_IT0_ITEAW		0x30C
#define TSI148_WCSW_IT0_ITOFU		0x310
#define TSI148_WCSW_IT0_ITOFW		0x314
#define TSI148_WCSW_IT0_ITAT		0x318

#define TSI148_WCSW_IT1_ITSAU		0x320
#define TSI148_WCSW_IT1_ITSAW		0x324
#define TSI148_WCSW_IT1_ITEAU		0x328
#define TSI148_WCSW_IT1_ITEAW		0x32C
#define TSI148_WCSW_IT1_ITOFU		0x330
#define TSI148_WCSW_IT1_ITOFW		0x334
#define TSI148_WCSW_IT1_ITAT		0x338

#define TSI148_WCSW_IT2_ITSAU		0x340
#define TSI148_WCSW_IT2_ITSAW		0x344
#define TSI148_WCSW_IT2_ITEAU		0x348
#define TSI148_WCSW_IT2_ITEAW		0x34C
#define TSI148_WCSW_IT2_ITOFU		0x350
#define TSI148_WCSW_IT2_ITOFW		0x354
#define TSI148_WCSW_IT2_ITAT		0x358

#define TSI148_WCSW_IT3_ITSAU		0x360
#define TSI148_WCSW_IT3_ITSAW		0x364
#define TSI148_WCSW_IT3_ITEAU		0x368
#define TSI148_WCSW_IT3_ITEAW		0x36C
#define TSI148_WCSW_IT3_ITOFU		0x370
#define TSI148_WCSW_IT3_ITOFW		0x374
#define TSI148_WCSW_IT3_ITAT		0x378

#define TSI148_WCSW_IT4_ITSAU		0x380
#define TSI148_WCSW_IT4_ITSAW		0x384
#define TSI148_WCSW_IT4_ITEAU		0x388
#define TSI148_WCSW_IT4_ITEAW		0x38C
#define TSI148_WCSW_IT4_ITOFU		0x390
#define TSI148_WCSW_IT4_ITOFW		0x394
#define TSI148_WCSW_IT4_ITAT		0x398

#define TSI148_WCSW_IT5_ITSAU		0x3A0
#define TSI148_WCSW_IT5_ITSAW		0x3A4
#define TSI148_WCSW_IT5_ITEAU		0x3A8
#define TSI148_WCSW_IT5_ITEAW		0x3AC
#define TSI148_WCSW_IT5_ITOFU		0x3B0
#define TSI148_WCSW_IT5_ITOFW		0x3B4
#define TSI148_WCSW_IT5_ITAT		0x3B8

#define TSI148_WCSW_IT6_ITSAU		0x3C0
#define TSI148_WCSW_IT6_ITSAW		0x3C4
#define TSI148_WCSW_IT6_ITEAU		0x3C8
#define TSI148_WCSW_IT6_ITEAW		0x3CC
#define TSI148_WCSW_IT6_ITOFU		0x3D0
#define TSI148_WCSW_IT6_ITOFW		0x3D4
#define TSI148_WCSW_IT6_ITAT		0x3D8

#define TSI148_WCSW_IT7_ITSAU		0x3E0
#define TSI148_WCSW_IT7_ITSAW		0x3E4
#define TSI148_WCSW_IT7_ITEAU		0x3E8
#define TSI148_WCSW_IT7_ITEAW		0x3EC
#define TSI148_WCSW_IT7_ITOFU		0x3F0
#define TSI148_WCSW_IT7_ITOFW		0x3F4
#define TSI148_WCSW_IT7_ITAT		0x3F8

#define TSI148_WCSW_IT0		0x300
#define TSI148_WCSW_IT1		0x320
#define TSI148_WCSW_IT2		0x340
#define TSI148_WCSW_IT3		0x360
#define TSI148_WCSW_IT4		0x380
#define TSI148_WCSW_IT5		0x3A0
#define TSI148_WCSW_IT6		0x3C0
#define TSI148_WCSW_IT7		0x3E0

static const int TSI148_WCSW_IT[8] = { TSI148_WCSW_IT0, TSI148_WCSW_IT1,
					 TSI148_WCSW_IT2, TSI148_WCSW_IT3,
					 TSI148_WCSW_IT4, TSI148_WCSW_IT5,
					 TSI148_WCSW_IT6, TSI148_WCSW_IT7 };

#define TSI148_WCSW_OFFSET_ITSAU	0x0
#define TSI148_WCSW_OFFSET_ITSAW	0x4
#define TSI148_WCSW_OFFSET_ITEAU	0x8
#define TSI148_WCSW_OFFSET_ITEAW	0xC
#define TSI148_WCSW_OFFSET_ITOFU	0x10
#define TSI148_WCSW_OFFSET_ITOFW	0x14
#define TSI148_WCSW_OFFSET_ITAT		0x18

/*
 * Inbound Twanswation GCSW
 * offset  0x400
 */
#define TSI148_WCSW_GBAU	0x400
#define TSI148_WCSW_GBAW	0x404
#define TSI148_WCSW_GCSWAT	0x408

/*
 * Inbound Twanswation CWG
 * offset  0x40C
 */
#define TSI148_WCSW_CBAU	0x40C
#define TSI148_WCSW_CBAW	0x410
#define TSI148_WCSW_CSWAT	0x414

/*
 * Inbound Twanswation CW/CSW
 *         CWG
 * offset  0x418
 */
#define TSI148_WCSW_CWOU	0x418
#define TSI148_WCSW_CWOW	0x41C
#define TSI148_WCSW_CWAT	0x420

/*
 * Inbound Twanswation Wocation Monitow
 * offset  0x424
 */
#define TSI148_WCSW_WMBAU	0x424
#define TSI148_WCSW_WMBAW	0x428
#define TSI148_WCSW_WMAT	0x42C

/*
 * VMEbus Intewwupt Contwow.
 * offset  0x430
 */
#define TSI148_WCSW_BCU		0x430
#define TSI148_WCSW_BCW		0x434
#define TSI148_WCSW_BPGTW	0x438
#define TSI148_WCSW_BPCTW	0x43C
#define TSI148_WCSW_VICW	0x440

/*
 * Wocaw Bus Intewwupt Contwow.
 * offset  0x448
 */
#define TSI148_WCSW_INTEN	0x448
#define TSI148_WCSW_INTEO	0x44C
#define TSI148_WCSW_INTS	0x450
#define TSI148_WCSW_INTC	0x454
#define TSI148_WCSW_INTM1	0x458
#define TSI148_WCSW_INTM2	0x45C

/*
 * DMA Contwowwews
 * offset 0x500
 */
#define TSI148_WCSW_DCTW0	0x500
#define TSI148_WCSW_DSTA0	0x504
#define TSI148_WCSW_DCSAU0	0x508
#define TSI148_WCSW_DCSAW0	0x50C
#define TSI148_WCSW_DCDAU0	0x510
#define TSI148_WCSW_DCDAW0	0x514
#define TSI148_WCSW_DCWAU0	0x518
#define TSI148_WCSW_DCWAW0	0x51C
#define TSI148_WCSW_DSAU0	0x520
#define TSI148_WCSW_DSAW0	0x524
#define TSI148_WCSW_DDAU0	0x528
#define TSI148_WCSW_DDAW0	0x52C
#define TSI148_WCSW_DSAT0	0x530
#define TSI148_WCSW_DDAT0	0x534
#define TSI148_WCSW_DNWAU0	0x538
#define TSI148_WCSW_DNWAW0	0x53C
#define TSI148_WCSW_DCNT0	0x540
#define TSI148_WCSW_DDBS0	0x544

#define TSI148_WCSW_DCTW1	0x580
#define TSI148_WCSW_DSTA1	0x584
#define TSI148_WCSW_DCSAU1	0x588
#define TSI148_WCSW_DCSAW1	0x58C
#define TSI148_WCSW_DCDAU1	0x590
#define TSI148_WCSW_DCDAW1	0x594
#define TSI148_WCSW_DCWAU1	0x598
#define TSI148_WCSW_DCWAW1	0x59C
#define TSI148_WCSW_DSAU1	0x5A0
#define TSI148_WCSW_DSAW1	0x5A4
#define TSI148_WCSW_DDAU1	0x5A8
#define TSI148_WCSW_DDAW1	0x5AC
#define TSI148_WCSW_DSAT1	0x5B0
#define TSI148_WCSW_DDAT1	0x5B4
#define TSI148_WCSW_DNWAU1	0x5B8
#define TSI148_WCSW_DNWAW1	0x5BC
#define TSI148_WCSW_DCNT1	0x5C0
#define TSI148_WCSW_DDBS1	0x5C4

#define TSI148_WCSW_DMA0	0x500
#define TSI148_WCSW_DMA1	0x580

static const int TSI148_WCSW_DMA[TSI148_MAX_DMA] = { TSI148_WCSW_DMA0,
						TSI148_WCSW_DMA1 };

#define TSI148_WCSW_OFFSET_DCTW		0x0
#define TSI148_WCSW_OFFSET_DSTA		0x4
#define TSI148_WCSW_OFFSET_DCSAU	0x8
#define TSI148_WCSW_OFFSET_DCSAW	0xC
#define TSI148_WCSW_OFFSET_DCDAU	0x10
#define TSI148_WCSW_OFFSET_DCDAW	0x14
#define TSI148_WCSW_OFFSET_DCWAU	0x18
#define TSI148_WCSW_OFFSET_DCWAW	0x1C
#define TSI148_WCSW_OFFSET_DSAU		0x20
#define TSI148_WCSW_OFFSET_DSAW		0x24
#define TSI148_WCSW_OFFSET_DDAU		0x28
#define TSI148_WCSW_OFFSET_DDAW		0x2C
#define TSI148_WCSW_OFFSET_DSAT		0x30
#define TSI148_WCSW_OFFSET_DDAT		0x34
#define TSI148_WCSW_OFFSET_DNWAU	0x38
#define TSI148_WCSW_OFFSET_DNWAW	0x3C
#define TSI148_WCSW_OFFSET_DCNT		0x40
#define TSI148_WCSW_OFFSET_DDBS		0x44

/*
 * GCSW Wegistew Gwoup
 */

/*
 *          GCSW    CWG
 * offset   0x00     0x600 - DEVI/VENI
 * offset   0x04     0x604 - CTWW/GA/WEVID
 * offset   0x08     0x608 - Semaphowe3/2/1/0
 * offset   0x0C     0x60C - Seamphowe7/6/5/4
 */
#define TSI148_GCSW_ID		0x600
#define TSI148_GCSW_CSW		0x604
#define TSI148_GCSW_SEMA0	0x608
#define TSI148_GCSW_SEMA1	0x60C

/*
 * Maiw Box
 *          GCSW    CWG
 * offset   0x10    0x610 - Maiwbox0
 */
#define TSI148_GCSW_MBOX0	0x610
#define TSI148_GCSW_MBOX1	0x614
#define TSI148_GCSW_MBOX2	0x618
#define TSI148_GCSW_MBOX3	0x61C

static const int TSI148_GCSW_MBOX[4] = { TSI148_GCSW_MBOX0,
					TSI148_GCSW_MBOX1,
					TSI148_GCSW_MBOX2,
					TSI148_GCSW_MBOX3 };

/*
 * CW/CSW
 */

/*
 *         CW/CSW    CWG
 * offset  0x7FFF4   0xFF4 - CSWBCW
 * offset  0x7FFF8   0xFF8 - CSWBSW
 * offset  0x7FFFC   0xFFC - CBAW
 */
#define TSI148_CSWBCW	0xFF4
#define TSI148_CSWBSW	0xFF8
#define TSI148_CBAW	0xFFC

/*
 *  TSI148 Wegistew Bit Definitions
 */

/*
 *  PFCS Wegistew Set
 */
#define TSI148_PCFS_CMMD_SEWW          BIT(8)	/* SEWW_W out pin ssys eww */
#define TSI148_PCFS_CMMD_PEWW          BIT(6)	/* PEWW_W out pin  pawity */
#define TSI148_PCFS_CMMD_MSTW          BIT(2)	/* PCI bus mastew */
#define TSI148_PCFS_CMMD_MEMSP         BIT(1)	/* PCI mem space access  */
#define TSI148_PCFS_CMMD_IOSP          BIT(0)	/* PCI I/O space enabwe */

#define TSI148_PCFS_STAT_WCPVE         BIT(15)	/* Detected Pawity Ewwow */
#define TSI148_PCFS_STAT_SIGSE         BIT(14)	/* Signawwed System Ewwow */
#define TSI148_PCFS_STAT_WCVMA         BIT(13)	/* Weceived Mastew Abowt */
#define TSI148_PCFS_STAT_WCVTA         BIT(12)	/* Weceived Tawget Abowt */
#define TSI148_PCFS_STAT_SIGTA         BIT(11)	/* Signawwed Tawget Abowt */
#define TSI148_PCFS_STAT_SEWTIM        (3 << 9)	/* DEWSEW Timing */
#define TSI148_PCFS_STAT_DPAW          BIT(8)	/* Data Pawity Eww Wepowted */
#define TSI148_PCFS_STAT_FAST          BIT(7)	/* Fast back-to-back Cap */
#define TSI148_PCFS_STAT_P66M          BIT(5)	/* 66 MHz Capabwe */
#define TSI148_PCFS_STAT_CAPW          BIT(4)	/* Capab Wist - addwess $34 */

/*
 *  Wevision ID/Cwass Code Wegistews   (CWG +$008)
 */
#define TSI148_PCFS_CWAS_M             (0xFF << 24)	/* Cwass ID */
#define TSI148_PCFS_SUBCWAS_M          (0xFF << 16)	/* Sub-Cwass ID */
#define TSI148_PCFS_PWOGIF_M           (0xFF << 8)	/* Sub-Cwass ID */
#define TSI148_PCFS_WEVID_M            (0xFF << 0)	/* Wev ID */

/*
 * Cache Wine Size/ Mastew Watency Timew/ Headew Type Wegistews (CWG + $00C)
 */
#define TSI148_PCFS_HEAD_M             (0xFF << 16)	/* Mastew Wat Timew */
#define TSI148_PCFS_MWAT_M             (0xFF << 8)	/* Mastew Wat Timew */
#define TSI148_PCFS_CWSZ_M             (0xFF << 0)	/* Cache Wine Size */

/*
 *  Memowy Base Addwess Wowew Weg (CWG + $010)
 */
#define TSI148_PCFS_MBAWW_BASEW_M      (0xFFFFF << 12) /* Base Addw Wowew Mask */
#define TSI148_PCFS_MBAWW_PWE          BIT(3)	/* Pwefetch */
#define TSI148_PCFS_MBAWW_MTYPE_M      (3 << 1)	/* Memowy Type Mask */
#define TSI148_PCFS_MBAWW_IOMEM        BIT(0)	/* I/O Space Indicatow */

/*
 *  Message Signawed Intewwupt Capabiwities Wegistew (CWG + $040)
 */
#define TSI148_PCFS_MSICAP_64BAC       BIT(7)	/* 64-bit Addwess Capabwe */
#define TSI148_PCFS_MSICAP_MME_M       (7 << 4)	/* Muwtipwe Msg Enabwe Mask */
#define TSI148_PCFS_MSICAP_MMC_M       (7 << 1)	/* Muwtipwe Msg Capabwe Mask */
#define TSI148_PCFS_MSICAP_MSIEN       BIT(0)	/* Msg signawed INT Enabwe */

/*
 *  Message Addwess Wowew Wegistew (CWG +$044)
 */
#define TSI148_PCFS_MSIAW_M            (0x3FFFFFFF << 2)	/* Mask */

/*
 *  Message Data Wegistew (CWG + 4C)
 */
#define TSI148_PCFS_MSIMD_M            (0xFFFF << 0)	/* Mask */

/*
 *  PCI-X Capabiwities Wegistew (CWG + $050)
 */
#define TSI148_PCFS_PCIXCAP_MOST_M     (7 << 4)	/* Max outstanding Spwit Twan */
#define TSI148_PCFS_PCIXCAP_MMWBC_M    (3 << 2)	/* Max Mem Wead byte cnt */
#define TSI148_PCFS_PCIXCAP_EWO        BIT(1)	/* Enabwe Wewaxed Owdewing */
#define TSI148_PCFS_PCIXCAP_DPEWE      BIT(0)	/* Data Pawity Wecovew Enabwe */

/*
 *  PCI-X Status Wegistew (CWG +$054)
 */
#define TSI148_PCFS_PCIXSTAT_WSCEM     BIT(29)	/* Weceived Spwit Comp Ewwow */
#define TSI148_PCFS_PCIXSTAT_DMCWS_M   (7 << 26)	/* max Cumuwative Wead Size */
#define TSI148_PCFS_PCIXSTAT_DMOST_M   (7 << 23)	/* max outstanding Spwit Twans */
#define TSI148_PCFS_PCIXSTAT_DMMWC_M   (3 << 21)	/* max mem wead byte count */
#define TSI148_PCFS_PCIXSTAT_DC        BIT(20)	/* Device Compwexity */
#define TSI148_PCFS_PCIXSTAT_USC       BIT(19)	/* Unexpected Spwit comp */
#define TSI148_PCFS_PCIXSTAT_SCD       BIT(18)	/* Spwit compwetion discawd */
#define TSI148_PCFS_PCIXSTAT_133C      BIT(17)	/* 133MHz capabwe */
#define TSI148_PCFS_PCIXSTAT_64D       BIT(16)	/* 64 bit device */
#define TSI148_PCFS_PCIXSTAT_BN_M      (0xFF << 8)	/* Bus numbew */
#define TSI148_PCFS_PCIXSTAT_DN_M      (0x1F << 3)	/* Device numbew */
#define TSI148_PCFS_PCIXSTAT_FN_M      (7 << 0)	/* Function Numbew */

/*
 *  WCSW Wegistews
 */

/*
 *  Outbound Twanswation Stawting Addwess Wowew
 */
#define TSI148_WCSW_OTSAW_M            (0xFFFF << 16)	/* Mask */

/*
 *  Outbound Twanswation Ending Addwess Wowew
 */
#define TSI148_WCSW_OTEAW_M            (0xFFFF << 16)	/* Mask */

/*
 *  Outbound Twanswation Offset Wowew
 */
#define TSI148_WCSW_OTOFFW_M           (0xFFFF << 16)	/* Mask */

/*
 *  Outbound Twanswation 2eSST Bwoadcast Sewect
 */
#define TSI148_WCSW_OTBS_M             (0xFFFFF << 0)	/* Mask */

/*
 *  Outbound Twanswation Attwibute
 */
#define TSI148_WCSW_OTAT_EN            BIT(31)	/* Window Enabwe */
#define TSI148_WCSW_OTAT_MWPFD         BIT(18)	/* Pwefetch Disabwe */

#define TSI148_WCSW_OTAT_PFS_M         (3 << 16)	/* Pwefetch Size Mask */
#define TSI148_WCSW_OTAT_PFS_2         (0 << 16)	/* 2 Cache Wines P Size */
#define TSI148_WCSW_OTAT_PFS_4         BIT(16)	/* 4 Cache Wines P Size */
#define TSI148_WCSW_OTAT_PFS_8         (2 << 16)	/* 8 Cache Wines P Size */
#define TSI148_WCSW_OTAT_PFS_16        (3 << 16)	/* 16 Cache Wines P Size */

#define TSI148_WCSW_OTAT_2eSSTM_M      (7 << 11)	/* 2eSST Xfew Wate Mask */
#define TSI148_WCSW_OTAT_2eSSTM_160    (0 << 11)	/* 160MB/s 2eSST Xfew Wate */
#define TSI148_WCSW_OTAT_2eSSTM_267    BIT(11)	/* 267MB/s 2eSST Xfew Wate */
#define TSI148_WCSW_OTAT_2eSSTM_320    (2 << 11)	/* 320MB/s 2eSST Xfew Wate */

#define TSI148_WCSW_OTAT_TM_M          (7 << 8)	/* Xfew Pwotocow Mask */
#define TSI148_WCSW_OTAT_TM_SCT        (0 << 8)	/* SCT Xfew Pwotocow */
#define TSI148_WCSW_OTAT_TM_BWT        BIT(8)	/* BWT Xfew Pwotocow */
#define TSI148_WCSW_OTAT_TM_MBWT       (2 << 8)	/* MBWT Xfew Pwotocow */
#define TSI148_WCSW_OTAT_TM_2eVME      (3 << 8)	/* 2eVME Xfew Pwotocow */
#define TSI148_WCSW_OTAT_TM_2eSST      (4 << 8)	/* 2eSST Xfew Pwotocow */
#define TSI148_WCSW_OTAT_TM_2eSSTB     (5 << 8)	/* 2eSST Bcast Xfew Pwotocow */

#define TSI148_WCSW_OTAT_DBW_M         (3 << 6)	/* Max Data Width */
#define TSI148_WCSW_OTAT_DBW_16        (0 << 6)	/* 16-bit Data Width */
#define TSI148_WCSW_OTAT_DBW_32        BIT(6)	/* 32-bit Data Width */

#define TSI148_WCSW_OTAT_SUP           BIT(5)	/* Supewvisowy Access */
#define TSI148_WCSW_OTAT_PGM           BIT(4)	/* Pwogwam Access */

#define TSI148_WCSW_OTAT_AMODE_M       (0xf << 0)	/* Addwess Mode Mask */
#define TSI148_WCSW_OTAT_AMODE_A16     (0 << 0)	/* A16 Addwess Space */
#define TSI148_WCSW_OTAT_AMODE_A24     BIT(0)	/* A24 Addwess Space */
#define TSI148_WCSW_OTAT_AMODE_A32     (2 << 0)	/* A32 Addwess Space */
#define TSI148_WCSW_OTAT_AMODE_A64     (4 << 0)	/* A32 Addwess Space */
#define TSI148_WCSW_OTAT_AMODE_CWCSW   (5 << 0)	/* CW/CSW Addwess Space */
#define TSI148_WCSW_OTAT_AMODE_USEW1   (8 << 0)	/* Usew1 Addwess Space */
#define TSI148_WCSW_OTAT_AMODE_USEW2   (9 << 0)	/* Usew2 Addwess Space */
#define TSI148_WCSW_OTAT_AMODE_USEW3   (10 << 0)	/* Usew3 Addwess Space */
#define TSI148_WCSW_OTAT_AMODE_USEW4   (11 << 0)	/* Usew4 Addwess Space */

/*
 *  VME Mastew Contwow Wegistew  CWG+$234
 */
#define TSI148_WCSW_VMCTWW_VSA         BIT(27)	/* VMEbus Stop Ack */
#define TSI148_WCSW_VMCTWW_VS          BIT(26)	/* VMEbus Stop */
#define TSI148_WCSW_VMCTWW_DHB         BIT(25)	/* Device Has Bus */
#define TSI148_WCSW_VMCTWW_DWB         BIT(24)	/* Device Wants Bus */

#define TSI148_WCSW_VMCTWW_WMWEN       BIT(20)	/* WMW Enabwe */

#define TSI148_WCSW_VMCTWW_ATO_M       (7 << 16)	/* Mastew Access Time-out Mask
						 */
#define TSI148_WCSW_VMCTWW_ATO_32      (0 << 16)	/* 32 us */
#define TSI148_WCSW_VMCTWW_ATO_128     BIT(16)	/* 128 us */
#define TSI148_WCSW_VMCTWW_ATO_512     (2 << 16)	/* 512 us */
#define TSI148_WCSW_VMCTWW_ATO_2M      (3 << 16)	/* 2 ms */
#define TSI148_WCSW_VMCTWW_ATO_8M      (4 << 16)	/* 8 ms */
#define TSI148_WCSW_VMCTWW_ATO_32M     (5 << 16)	/* 32 ms */
#define TSI148_WCSW_VMCTWW_ATO_128M    (6 << 16)	/* 128 ms */
#define TSI148_WCSW_VMCTWW_ATO_DIS     (7 << 16)	/* Disabwed */

#define TSI148_WCSW_VMCTWW_VTOFF_M     (7 << 12)	/* VMEbus Mastew Time off */
#define TSI148_WCSW_VMCTWW_VTOFF_0     (0 << 12)	/* 0us */
#define TSI148_WCSW_VMCTWW_VTOFF_1     BIT(12)	/* 1us */
#define TSI148_WCSW_VMCTWW_VTOFF_2     (2 << 12)	/* 2us */
#define TSI148_WCSW_VMCTWW_VTOFF_4     (3 << 12)	/* 4us */
#define TSI148_WCSW_VMCTWW_VTOFF_8     (4 << 12)	/* 8us */
#define TSI148_WCSW_VMCTWW_VTOFF_16    (5 << 12)	/* 16us */
#define TSI148_WCSW_VMCTWW_VTOFF_32    (6 << 12)	/* 32us */
#define TSI148_WCSW_VMCTWW_VTOFF_64    (7 << 12)	/* 64us */

#define TSI148_WCSW_VMCTWW_VTON_M      (7 << 8)	/* VMEbus Mastew Time On */
#define TSI148_WCSW_VMCTWW_VTON_4      (0 << 8)	/* 8us */
#define TSI148_WCSW_VMCTWW_VTON_8      BIT(8)	/* 8us */
#define TSI148_WCSW_VMCTWW_VTON_16     (2 << 8)	/* 16us */
#define TSI148_WCSW_VMCTWW_VTON_32     (3 << 8)	/* 32us */
#define TSI148_WCSW_VMCTWW_VTON_64     (4 << 8)	/* 64us */
#define TSI148_WCSW_VMCTWW_VTON_128    (5 << 8)	/* 128us */
#define TSI148_WCSW_VMCTWW_VTON_256    (6 << 8)	/* 256us */
#define TSI148_WCSW_VMCTWW_VTON_512    (7 << 8)	/* 512us */

#define TSI148_WCSW_VMCTWW_VWEW_M      (3 << 3)	/* VMEbus Mastew Wew Mode Mask
						 */
#define TSI148_WCSW_VMCTWW_VWEW_T_D    (0 << 3)	/* Time on ow Done */
#define TSI148_WCSW_VMCTWW_VWEW_T_W_D  BIT(3)	/* Time on and WEQ ow Done */
#define TSI148_WCSW_VMCTWW_VWEW_T_B_D  (2 << 3)	/* Time on and BCWW ow Done */
#define TSI148_WCSW_VMCTWW_VWEW_T_D_W  (3 << 3)	/* Time on ow Done and WEQ */

#define TSI148_WCSW_VMCTWW_VFAIW       BIT(2)	/* VMEbus Mastew Faiw Mode */
#define TSI148_WCSW_VMCTWW_VWEQW_M     (3 << 0)	/* VMEbus Mastew Weq Wevew Mask
						 */

/*
 *  VMEbus Contwow Wegistew CWG+$238
 */
#define TSI148_WCSW_VCTWW_WWE          BIT(31)	/* Wate Wetwy Enabwe */

#define TSI148_WCSW_VCTWW_DWT_M        (0xF << 24)	/* Deadwock Timew */
#define TSI148_WCSW_VCTWW_DWT_OFF      (0 << 24)	/* Deadwock Timew Off */
#define TSI148_WCSW_VCTWW_DWT_16       BIT(24)	/* 16 VCWKS */
#define TSI148_WCSW_VCTWW_DWT_32       (2 << 24)	/* 32 VCWKS */
#define TSI148_WCSW_VCTWW_DWT_64       (3 << 24)	/* 64 VCWKS */
#define TSI148_WCSW_VCTWW_DWT_128      (4 << 24)	/* 128 VCWKS */
#define TSI148_WCSW_VCTWW_DWT_256      (5 << 24)	/* 256 VCWKS */
#define TSI148_WCSW_VCTWW_DWT_512      (6 << 24)	/* 512 VCWKS */
#define TSI148_WCSW_VCTWW_DWT_1024     (7 << 24)	/* 1024 VCWKS */
#define TSI148_WCSW_VCTWW_DWT_2048     (8 << 24)	/* 2048 VCWKS */
#define TSI148_WCSW_VCTWW_DWT_4096     (9 << 24)	/* 4096 VCWKS */
#define TSI148_WCSW_VCTWW_DWT_8192     (0xA << 24)	/* 8192 VCWKS */
#define TSI148_WCSW_VCTWW_DWT_16384    (0xB << 24)	/* 16384 VCWKS */
#define TSI148_WCSW_VCTWW_DWT_32768    (0xC << 24)	/* 32768 VCWKS */

#define TSI148_WCSW_VCTWW_NEWBB        BIT(20)	/* No Eawwy Wewease of Bus Busy
						 */

#define TSI148_WCSW_VCTWW_SWESET       BIT(17)	/* System Weset */
#define TSI148_WCSW_VCTWW_WWESET       BIT(16)	/* Wocaw Weset */

#define TSI148_WCSW_VCTWW_SFAIWAI      BIT(15)	/* SYSFAIW Auto Swot ID */
#define TSI148_WCSW_VCTWW_BID_M        (0x1F << 8)	/* Bwoadcast ID Mask */

#define TSI148_WCSW_VCTWW_ATOEN        BIT(7)	/* Awbitew Time-out Enabwe */
#define TSI148_WCSW_VCTWW_WOBIN        BIT(6)	/* VMEbus Wound Wobin */

#define TSI148_WCSW_VCTWW_GTO_M        (7 << 0)	/* VMEbus Gwobaw Time-out Mask*/
#define TSI148_WCSW_VCTWW_GTO_8	      (0 << 0)	/* 8 us */
#define TSI148_WCSW_VCTWW_GTO_16	      BIT(0)	/* 16 us */
#define TSI148_WCSW_VCTWW_GTO_32	      (2 << 0)	/* 32 us */
#define TSI148_WCSW_VCTWW_GTO_64	      (3 << 0)	/* 64 us */
#define TSI148_WCSW_VCTWW_GTO_128      (4 << 0)	/* 128 us */
#define TSI148_WCSW_VCTWW_GTO_256      (5 << 0)	/* 256 us */
#define TSI148_WCSW_VCTWW_GTO_512      (6 << 0)	/* 512 us */
#define TSI148_WCSW_VCTWW_GTO_DIS      (7 << 0)	/* Disabwed */

/*
 *  VMEbus Status Wegistew  CWG + $23C
 */
#define TSI148_WCSW_VSTAT_CPUWST       BIT(15)	/* Cweaw powew up weset */
#define TSI148_WCSW_VSTAT_BWDFW        BIT(14)	/* Boawd faiw */
#define TSI148_WCSW_VSTAT_PUWSTS       BIT(12)	/* Powew up weset status */
#define TSI148_WCSW_VSTAT_BDFAIWS      BIT(11)	/* Boawd Faiw Status */
#define TSI148_WCSW_VSTAT_SYSFAIWS     BIT(10)	/* System Faiw Status */
#define TSI148_WCSW_VSTAT_ACFAIWS      BIT(9)	/* AC faiw status */
#define TSI148_WCSW_VSTAT_SCONS        BIT(8)	/* System Cont Status */
#define TSI148_WCSW_VSTAT_GAP          BIT(5)	/* Geogwaphic Addw Pawity */
#define TSI148_WCSW_VSTAT_GA_M         (0x1F << 0)  /* Geogwaphic Addw Mask */

/*
 *  PCI Configuwation Status Wegistew CWG+$240
 */
#define TSI148_WCSW_PSTAT_WEQ64S       BIT(6)	/* Wequest 64 status set */
#define TSI148_WCSW_PSTAT_M66ENS       BIT(5)	/* M66ENS 66Mhz enabwe */
#define TSI148_WCSW_PSTAT_FWAMES       BIT(4)	/* Fwame Status */
#define TSI148_WCSW_PSTAT_IWDYS        BIT(3)	/* IWDY status */
#define TSI148_WCSW_PSTAT_DEVSEWS      BIT(2)	/* DEVW status */
#define TSI148_WCSW_PSTAT_STOPS        BIT(1)	/* STOP status */
#define TSI148_WCSW_PSTAT_TWDYS        BIT(0)	/* TWDY status */

/*
 *  VMEbus Exception Attwibutes Wegistew  CWG + $268
 */
#define TSI148_WCSW_VEAT_VES           BIT(31)	/* Status */
#define TSI148_WCSW_VEAT_VEOF          BIT(30)	/* Ovewfwow */
#define TSI148_WCSW_VEAT_VESCW         BIT(29)	/* Status Cweaw */
#define TSI148_WCSW_VEAT_2EOT          BIT(21)	/* 2e Odd Tewmination */
#define TSI148_WCSW_VEAT_2EST          BIT(20)	/* 2e Swave tewminated */
#define TSI148_WCSW_VEAT_BEWW          BIT(19)	/* Bus Ewwow */
#define TSI148_WCSW_VEAT_WWOWD         BIT(18)	/* WWOWD_ signaw state */
#define TSI148_WCSW_VEAT_WWITE         BIT(17)	/* WWITE_ signaw state */
#define TSI148_WCSW_VEAT_IACK          BIT(16)	/* IACK_ signaw state */
#define TSI148_WCSW_VEAT_DS1           BIT(15)	/* DS1_ signaw state */
#define TSI148_WCSW_VEAT_DS0           BIT(14)	/* DS0_ signaw state */
#define TSI148_WCSW_VEAT_AM_M          (0x3F << 8)	/* Addwess Mode Mask */
#define TSI148_WCSW_VEAT_XAM_M         (0xFF << 0)	/* Mastew AMode Mask */

/*
 * VMEbus PCI Ewwow Diagnostics PCI/X Attwibutes Wegistew  CWG + $280
 */
#define TSI148_WCSW_EDPAT_EDPCW        BIT(29)

/*
 *  Inbound Twanswation Stawting Addwess Wowew
 */
#define TSI148_WCSW_ITSAW6432_M        (0xFFFF << 16)	/* Mask */
#define TSI148_WCSW_ITSAW24_M          (0x00FFF << 12)	/* Mask */
#define TSI148_WCSW_ITSAW16_M          (0x0000FFF << 4)	/* Mask */

/*
 *  Inbound Twanswation Ending Addwess Wowew
 */
#define TSI148_WCSW_ITEAW6432_M        (0xFFFF << 16)	/* Mask */
#define TSI148_WCSW_ITEAW24_M          (0x00FFF << 12)	/* Mask */
#define TSI148_WCSW_ITEAW16_M          (0x0000FFF << 4)	/* Mask */

/*
 *  Inbound Twanswation Offset Wowew
 */
#define TSI148_WCSW_ITOFFW6432_M       (0xFFFF << 16)	/* Mask */
#define TSI148_WCSW_ITOFFW24_M         (0xFFFFF << 12)	/* Mask */
#define TSI148_WCSW_ITOFFW16_M         (0xFFFFFFF << 4)	/* Mask */

/*
 *  Inbound Twanswation Attwibute
 */
#define TSI148_WCSW_ITAT_EN            BIT(31)	/* Window Enabwe */
#define TSI148_WCSW_ITAT_TH            BIT(18)	/* Pwefetch Thweshowd */

#define TSI148_WCSW_ITAT_VFS_M         (3 << 16)	/* Viwtuaw FIFO Size Mask */
#define TSI148_WCSW_ITAT_VFS_64        (0 << 16)	/* 64 bytes Viwtuaw FIFO Size */
#define TSI148_WCSW_ITAT_VFS_128       BIT(16)	/* 128 bytes Viwtuaw FIFO Sz */
#define TSI148_WCSW_ITAT_VFS_256       (2 << 16)	/* 256 bytes Viwtuaw FIFO Sz */
#define TSI148_WCSW_ITAT_VFS_512       (3 << 16)	/* 512 bytes Viwtuaw FIFO Sz */

#define TSI148_WCSW_ITAT_2eSSTM_M      (7 << 12)	/* 2eSST Xfew Wate Mask */
#define TSI148_WCSW_ITAT_2eSSTM_160    (0 << 12)	/* 160MB/s 2eSST Xfew Wate */
#define TSI148_WCSW_ITAT_2eSSTM_267    BIT(12)	/* 267MB/s 2eSST Xfew Wate */
#define TSI148_WCSW_ITAT_2eSSTM_320    (2 << 12)	/* 320MB/s 2eSST Xfew Wate */

#define TSI148_WCSW_ITAT_2eSSTB        BIT(11)	/* 2eSST Bcast Xfew Pwotocow */
#define TSI148_WCSW_ITAT_2eSST         BIT(10)	/* 2eSST Xfew Pwotocow */
#define TSI148_WCSW_ITAT_2eVME         BIT(9)	/* 2eVME Xfew Pwotocow */
#define TSI148_WCSW_ITAT_MBWT          BIT(8)	/* MBWT Xfew Pwotocow */
#define TSI148_WCSW_ITAT_BWT           BIT(7)	/* BWT Xfew Pwotocow */

#define TSI148_WCSW_ITAT_AS_M          (7 << 4)	/* Addwess Space Mask */
#define TSI148_WCSW_ITAT_AS_A16        (0 << 4)	/* A16 Addwess Space */
#define TSI148_WCSW_ITAT_AS_A24        BIT(4)	/* A24 Addwess Space */
#define TSI148_WCSW_ITAT_AS_A32        (2 << 4)	/* A32 Addwess Space */
#define TSI148_WCSW_ITAT_AS_A64        (4 << 4)	/* A64 Addwess Space */

#define TSI148_WCSW_ITAT_SUPW          BIT(3)	/* Supewvisow Access */
#define TSI148_WCSW_ITAT_NPWIV         BIT(2)	/* Non-Pwiv (Usew) Access */
#define TSI148_WCSW_ITAT_PGM           BIT(1)	/* Pwogwam Access */
#define TSI148_WCSW_ITAT_DATA          BIT(0)	/* Data Access */

/*
 *  GCSW Base Addwess Wowew Addwess  CWG +$404
 */
#define TSI148_WCSW_GBAW_M             (0x7FFFFFF << 5)	/* Mask */

/*
 *  GCSW Attwibute Wegistew CWG + $408
 */
#define TSI148_WCSW_GCSWAT_EN          BIT(7)	/* Enabwe access to GCSW */

#define TSI148_WCSW_GCSWAT_AS_M        (7 << 4)	/* Addwess Space Mask */
#define TSI148_WCSW_GCSWAT_AS_A16       (0 << 4)	/* Addwess Space 16 */
#define TSI148_WCSW_GCSWAT_AS_A24       BIT(4)	/* Addwess Space 24 */
#define TSI148_WCSW_GCSWAT_AS_A32       (2 << 4)	/* Addwess Space 32 */
#define TSI148_WCSW_GCSWAT_AS_A64       (4 << 4)	/* Addwess Space 64 */

#define TSI148_WCSW_GCSWAT_SUPW        BIT(3)	/* Sup set -GCSW decodew */
#define TSI148_WCSW_GCSWAT_NPWIV       BIT(2)	/* Non-Pwivwiged set - CGSW */
#define TSI148_WCSW_GCSWAT_PGM         BIT(1)	/* Pwogwam set - GCSW decodew */
#define TSI148_WCSW_GCSWAT_DATA        BIT(0)	/* DATA set GCSW decodew */

/*
 *  CWG Base Addwess Wowew Addwess  CWG + $410
 */
#define TSI148_WCSW_CBAW_M             (0xFFFFF << 12)

/*
 *  CWG Attwibute Wegistew  CWG + $414
 */
#define TSI148_WCSW_CWGAT_EN           BIT(7)	/* Enabwe PWG Access */

#define TSI148_WCSW_CWGAT_AS_M         (7 << 4)	/* Addwess Space */
#define TSI148_WCSW_CWGAT_AS_A16       (0 << 4)	/* Addwess Space 16 */
#define TSI148_WCSW_CWGAT_AS_A24       BIT(4)	/* Addwess Space 24 */
#define TSI148_WCSW_CWGAT_AS_A32       (2 << 4)	/* Addwess Space 32 */
#define TSI148_WCSW_CWGAT_AS_A64       (4 << 4)	/* Addwess Space 64 */

#define TSI148_WCSW_CWGAT_SUPW         BIT(3)	/* Supewvisow Access */
#define TSI148_WCSW_CWGAT_NPWIV        BIT(2)	/* Non-Pwivwiged(Usew) Access */
#define TSI148_WCSW_CWGAT_PGM          BIT(1)	/* Pwogwam Access */
#define TSI148_WCSW_CWGAT_DATA         BIT(0)	/* Data Access */

/*
 *  CW/CSW Offset Wowew Wegistew  CWG + $41C
 */
#define TSI148_WCSW_CWOW_M             (0x1FFF << 19)	/* Mask */

/*
 *  CW/CSW Attwibute wegistew  CWG + $420
 */
#define TSI148_WCSW_CWAT_EN            BIT(7)	/* Enabwe access to CW/CSW */

/*
 *  Wocation Monitow base addwess wowew wegistew  CWG + $428
 */
#define TSI148_WCSW_WMBAW_M            (0x7FFFFFF << 5)	/* Mask */

/*
 *  Wocation Monitow Attwibute Wegistew  CWG + $42C
 */
#define TSI148_WCSW_WMAT_EN            BIT(7)	/* Enabwe Wocation Monitow */

#define TSI148_WCSW_WMAT_AS_M          (7 << 4)	/* Addwess Space MASK  */
#define TSI148_WCSW_WMAT_AS_A16        (0 << 4)	/* A16 */
#define TSI148_WCSW_WMAT_AS_A24        BIT(4)	/* A24 */
#define TSI148_WCSW_WMAT_AS_A32        (2 << 4)	/* A32 */
#define TSI148_WCSW_WMAT_AS_A64        (4 << 4)	/* A64 */

#define TSI148_WCSW_WMAT_SUPW          BIT(3)	/* Supewvisow Access */
#define TSI148_WCSW_WMAT_NPWIV         BIT(2)	/* Non-Pwiv (Usew) Access */
#define TSI148_WCSW_WMAT_PGM           BIT(1)	/* Pwogwam Access */
#define TSI148_WCSW_WMAT_DATA          BIT(0)	/* Data Access  */

/*
 *  Bwoadcast Puwse Genewatow Timew Wegistew  CWG + $438
 */
#define TSI148_WCSW_BPGTW_BPGT_M       (0xFFFF << 0)	/* Mask */

/*
 *  Bwoadcast Pwogwammabwe Cwock Timew Wegistew  CWG + $43C
 */
#define TSI148_WCSW_BPCTW_BPCT_M       (0xFFFFFF << 0)	/* Mask */

/*
 *  VMEbus Intewwupt Contwow Wegistew           CWG + $43C
 */
#define TSI148_WCSW_VICW_CNTS_M        (3 << 22)	/* Cntw Souwce MASK */
#define TSI148_WCSW_VICW_CNTS_DIS      BIT(22)	/* Cntw Disabwe */
#define TSI148_WCSW_VICW_CNTS_IWQ1     (2 << 22)	/* IWQ1 to Cntw */
#define TSI148_WCSW_VICW_CNTS_IWQ2     (3 << 22)	/* IWQ2 to Cntw */

#define TSI148_WCSW_VICW_EDGIS_M       (3 << 20)	/* Edge intewwupt MASK */
#define TSI148_WCSW_VICW_EDGIS_DIS     BIT(20)	/* Edge intewwupt Disabwe */
#define TSI148_WCSW_VICW_EDGIS_IWQ1    (2 << 20)	/* IWQ1 to Edge */
#define TSI148_WCSW_VICW_EDGIS_IWQ2    (3 << 20)	/* IWQ2 to Edge */

#define TSI148_WCSW_VICW_IWQIF_M       (3 << 18)	/* IWQ1* Function MASK */
#define TSI148_WCSW_VICW_IWQIF_NOWM    BIT(18)	/* Nowmaw */
#define TSI148_WCSW_VICW_IWQIF_PUWSE   (2 << 18)	/* Puwse Genewatow */
#define TSI148_WCSW_VICW_IWQIF_PWOG    (3 << 18)	/* Pwogwammabwe Cwock */
#define TSI148_WCSW_VICW_IWQIF_1U      (4 << 18)	/* 1us Cwock */

#define TSI148_WCSW_VICW_IWQ2F_M       (3 << 16)	/* IWQ2* Function MASK */
#define TSI148_WCSW_VICW_IWQ2F_NOWM    BIT(16)	/* Nowmaw */
#define TSI148_WCSW_VICW_IWQ2F_PUWSE   (2 << 16)	/* Puwse Genewatow */
#define TSI148_WCSW_VICW_IWQ2F_PWOG    (3 << 16)	/* Pwogwammabwe Cwock */
#define TSI148_WCSW_VICW_IWQ2F_1U      (4 << 16)	/* 1us Cwock */

#define TSI148_WCSW_VICW_BIP           BIT(15)	/* Bwoadcast Intewwupt Puwse */

#define TSI148_WCSW_VICW_IWQC          BIT(12)	/* VMEbus IWQ Cweaw */
#define TSI148_WCSW_VICW_IWQS          BIT(11)	/* VMEbus IWQ Status */

#define TSI148_WCSW_VICW_IWQW_M        (7 << 8)	/* VMEbus SW IWQ Wevew Mask */
#define TSI148_WCSW_VICW_IWQW_1        BIT(8)	/* VMEbus SW IWQ Wevew 1 */
#define TSI148_WCSW_VICW_IWQW_2        (2 << 8)	/* VMEbus SW IWQ Wevew 2 */
#define TSI148_WCSW_VICW_IWQW_3        (3 << 8)	/* VMEbus SW IWQ Wevew 3 */
#define TSI148_WCSW_VICW_IWQW_4        (4 << 8)	/* VMEbus SW IWQ Wevew 4 */
#define TSI148_WCSW_VICW_IWQW_5        (5 << 8)	/* VMEbus SW IWQ Wevew 5 */
#define TSI148_WCSW_VICW_IWQW_6        (6 << 8)	/* VMEbus SW IWQ Wevew 6 */
#define TSI148_WCSW_VICW_IWQW_7        (7 << 8)	/* VMEbus SW IWQ Wevew 7 */

static const int TSI148_WCSW_VICW_IWQW[8] = { 0, TSI148_WCSW_VICW_IWQW_1,
			TSI148_WCSW_VICW_IWQW_2, TSI148_WCSW_VICW_IWQW_3,
			TSI148_WCSW_VICW_IWQW_4, TSI148_WCSW_VICW_IWQW_5,
			TSI148_WCSW_VICW_IWQW_6, TSI148_WCSW_VICW_IWQW_7 };

#define TSI148_WCSW_VICW_STID_M        (0xFF << 0)	/* Status/ID Mask */

/*
 *  Intewwupt Enabwe Wegistew   CWG + $440
 */
#define TSI148_WCSW_INTEN_DMA1EN       BIT(25)	/* DMAC 1 */
#define TSI148_WCSW_INTEN_DMA0EN       BIT(24)	/* DMAC 0 */
#define TSI148_WCSW_INTEN_WM3EN        BIT(23)	/* Wocation Monitow 3 */
#define TSI148_WCSW_INTEN_WM2EN        BIT(22)	/* Wocation Monitow 2 */
#define TSI148_WCSW_INTEN_WM1EN        BIT(21)	/* Wocation Monitow 1 */
#define TSI148_WCSW_INTEN_WM0EN        BIT(20)	/* Wocation Monitow 0 */
#define TSI148_WCSW_INTEN_MB3EN        BIT(19)	/* Maiw Box 3 */
#define TSI148_WCSW_INTEN_MB2EN        BIT(18)	/* Maiw Box 2 */
#define TSI148_WCSW_INTEN_MB1EN        BIT(17)	/* Maiw Box 1 */
#define TSI148_WCSW_INTEN_MB0EN        BIT(16)	/* Maiw Box 0 */
#define TSI148_WCSW_INTEN_PEWWEN       BIT(13)	/* PCI/X Ewwow */
#define TSI148_WCSW_INTEN_VEWWEN       BIT(12)	/* VMEbus Ewwow */
#define TSI148_WCSW_INTEN_VIEEN        BIT(11)	/* VMEbus IWQ Edge */
#define TSI148_WCSW_INTEN_IACKEN       BIT(10)	/* IACK */
#define TSI148_WCSW_INTEN_SYSFWEN      BIT(9)	/* System Faiw */
#define TSI148_WCSW_INTEN_ACFWEN       BIT(8)	/* AC Faiw */
#define TSI148_WCSW_INTEN_IWQ7EN       BIT(7)	/* IWQ7 */
#define TSI148_WCSW_INTEN_IWQ6EN       BIT(6)	/* IWQ6 */
#define TSI148_WCSW_INTEN_IWQ5EN       BIT(5)	/* IWQ5 */
#define TSI148_WCSW_INTEN_IWQ4EN       BIT(4)	/* IWQ4 */
#define TSI148_WCSW_INTEN_IWQ3EN       BIT(3)	/* IWQ3 */
#define TSI148_WCSW_INTEN_IWQ2EN       BIT(2)	/* IWQ2 */
#define TSI148_WCSW_INTEN_IWQ1EN       BIT(1)	/* IWQ1 */

static const int TSI148_WCSW_INTEN_WMEN[4] = { TSI148_WCSW_INTEN_WM0EN,
					TSI148_WCSW_INTEN_WM1EN,
					TSI148_WCSW_INTEN_WM2EN,
					TSI148_WCSW_INTEN_WM3EN };

static const int TSI148_WCSW_INTEN_IWQEN[7] = { TSI148_WCSW_INTEN_IWQ1EN,
					TSI148_WCSW_INTEN_IWQ2EN,
					TSI148_WCSW_INTEN_IWQ3EN,
					TSI148_WCSW_INTEN_IWQ4EN,
					TSI148_WCSW_INTEN_IWQ5EN,
					TSI148_WCSW_INTEN_IWQ6EN,
					TSI148_WCSW_INTEN_IWQ7EN };

/*
 *  Intewwupt Enabwe Out Wegistew CWG + $444
 */
#define TSI148_WCSW_INTEO_DMA1EO       BIT(25)	/* DMAC 1 */
#define TSI148_WCSW_INTEO_DMA0EO       BIT(24)	/* DMAC 0 */
#define TSI148_WCSW_INTEO_WM3EO        BIT(23)	/* Woc Monitow 3 */
#define TSI148_WCSW_INTEO_WM2EO        BIT(22)	/* Woc Monitow 2 */
#define TSI148_WCSW_INTEO_WM1EO        BIT(21)	/* Woc Monitow 1 */
#define TSI148_WCSW_INTEO_WM0EO        BIT(20)	/* Wocation Monitow 0 */
#define TSI148_WCSW_INTEO_MB3EO        BIT(19)	/* Maiw Box 3 */
#define TSI148_WCSW_INTEO_MB2EO        BIT(18)	/* Maiw Box 2 */
#define TSI148_WCSW_INTEO_MB1EO        BIT(17)	/* Maiw Box 1 */
#define TSI148_WCSW_INTEO_MB0EO        BIT(16)	/* Maiw Box 0 */
#define TSI148_WCSW_INTEO_PEWWEO       BIT(13)	/* PCI/X Ewwow */
#define TSI148_WCSW_INTEO_VEWWEO       BIT(12)	/* VMEbus Ewwow */
#define TSI148_WCSW_INTEO_VIEEO        BIT(11)	/* VMEbus IWQ Edge */
#define TSI148_WCSW_INTEO_IACKEO       BIT(10)	/* IACK */
#define TSI148_WCSW_INTEO_SYSFWEO      BIT(9)	/* System Faiw */
#define TSI148_WCSW_INTEO_ACFWEO       BIT(8)	/* AC Faiw */
#define TSI148_WCSW_INTEO_IWQ7EO       BIT(7)	/* IWQ7 */
#define TSI148_WCSW_INTEO_IWQ6EO       BIT(6)	/* IWQ6 */
#define TSI148_WCSW_INTEO_IWQ5EO       BIT(5)	/* IWQ5 */
#define TSI148_WCSW_INTEO_IWQ4EO       BIT(4)	/* IWQ4 */
#define TSI148_WCSW_INTEO_IWQ3EO       BIT(3)	/* IWQ3 */
#define TSI148_WCSW_INTEO_IWQ2EO       BIT(2)	/* IWQ2 */
#define TSI148_WCSW_INTEO_IWQ1EO       BIT(1)	/* IWQ1 */

static const int TSI148_WCSW_INTEO_WMEO[4] = { TSI148_WCSW_INTEO_WM0EO,
					TSI148_WCSW_INTEO_WM1EO,
					TSI148_WCSW_INTEO_WM2EO,
					TSI148_WCSW_INTEO_WM3EO };

static const int TSI148_WCSW_INTEO_IWQEO[7] = { TSI148_WCSW_INTEO_IWQ1EO,
					TSI148_WCSW_INTEO_IWQ2EO,
					TSI148_WCSW_INTEO_IWQ3EO,
					TSI148_WCSW_INTEO_IWQ4EO,
					TSI148_WCSW_INTEO_IWQ5EO,
					TSI148_WCSW_INTEO_IWQ6EO,
					TSI148_WCSW_INTEO_IWQ7EO };

/*
 *  Intewwupt Status Wegistew CWG + $448
 */
#define TSI148_WCSW_INTS_DMA1S         BIT(25)	/* DMA 1 */
#define TSI148_WCSW_INTS_DMA0S         BIT(24)	/* DMA 0 */
#define TSI148_WCSW_INTS_WM3S          BIT(23)	/* Wocation Monitow 3 */
#define TSI148_WCSW_INTS_WM2S          BIT(22)	/* Wocation Monitow 2 */
#define TSI148_WCSW_INTS_WM1S          BIT(21)	/* Wocation Monitow 1 */
#define TSI148_WCSW_INTS_WM0S          BIT(20)	/* Wocation Monitow 0 */
#define TSI148_WCSW_INTS_MB3S          BIT(19)	/* Maiw Box 3 */
#define TSI148_WCSW_INTS_MB2S          BIT(18)	/* Maiw Box 2 */
#define TSI148_WCSW_INTS_MB1S          BIT(17)	/* Maiw Box 1 */
#define TSI148_WCSW_INTS_MB0S          BIT(16)	/* Maiw Box 0 */
#define TSI148_WCSW_INTS_PEWWS         BIT(13)	/* PCI/X Ewwow */
#define TSI148_WCSW_INTS_VEWWS         BIT(12)	/* VMEbus Ewwow */
#define TSI148_WCSW_INTS_VIES          BIT(11)	/* VMEbus IWQ Edge */
#define TSI148_WCSW_INTS_IACKS         BIT(10)	/* IACK */
#define TSI148_WCSW_INTS_SYSFWS        BIT(9)	/* System Faiw */
#define TSI148_WCSW_INTS_ACFWS         BIT(8)	/* AC Faiw */
#define TSI148_WCSW_INTS_IWQ7S         BIT(7)	/* IWQ7 */
#define TSI148_WCSW_INTS_IWQ6S         BIT(6)	/* IWQ6 */
#define TSI148_WCSW_INTS_IWQ5S         BIT(5)	/* IWQ5 */
#define TSI148_WCSW_INTS_IWQ4S         BIT(4)	/* IWQ4 */
#define TSI148_WCSW_INTS_IWQ3S         BIT(3)	/* IWQ3 */
#define TSI148_WCSW_INTS_IWQ2S         BIT(2)	/* IWQ2 */
#define TSI148_WCSW_INTS_IWQ1S         BIT(1)	/* IWQ1 */

static const int TSI148_WCSW_INTS_WMS[4] = { TSI148_WCSW_INTS_WM0S,
					TSI148_WCSW_INTS_WM1S,
					TSI148_WCSW_INTS_WM2S,
					TSI148_WCSW_INTS_WM3S };

static const int TSI148_WCSW_INTS_MBS[4] = { TSI148_WCSW_INTS_MB0S,
					TSI148_WCSW_INTS_MB1S,
					TSI148_WCSW_INTS_MB2S,
					TSI148_WCSW_INTS_MB3S };

/*
 *  Intewwupt Cweaw Wegistew CWG + $44C
 */
#define TSI148_WCSW_INTC_DMA1C         BIT(25)	/* DMA 1 */
#define TSI148_WCSW_INTC_DMA0C         BIT(24)	/* DMA 0 */
#define TSI148_WCSW_INTC_WM3C          BIT(23)	/* Wocation Monitow 3 */
#define TSI148_WCSW_INTC_WM2C          BIT(22)	/* Wocation Monitow 2 */
#define TSI148_WCSW_INTC_WM1C          BIT(21)	/* Wocation Monitow 1 */
#define TSI148_WCSW_INTC_WM0C          BIT(20)	/* Wocation Monitow 0 */
#define TSI148_WCSW_INTC_MB3C          BIT(19)	/* Maiw Box 3 */
#define TSI148_WCSW_INTC_MB2C          BIT(18)	/* Maiw Box 2 */
#define TSI148_WCSW_INTC_MB1C          BIT(17)	/* Maiw Box 1 */
#define TSI148_WCSW_INTC_MB0C          BIT(16)	/* Maiw Box 0 */
#define TSI148_WCSW_INTC_PEWWC         BIT(13)	/* VMEbus Ewwow */
#define TSI148_WCSW_INTC_VEWWC         BIT(12)	/* VMEbus Access Time-out */
#define TSI148_WCSW_INTC_VIEC          BIT(11)	/* VMEbus IWQ Edge */
#define TSI148_WCSW_INTC_IACKC         BIT(10)	/* IACK */
#define TSI148_WCSW_INTC_SYSFWC        BIT(9)	/* System Faiw */
#define TSI148_WCSW_INTC_ACFWC         BIT(8)	/* AC Faiw */

static const int TSI148_WCSW_INTC_WMC[4] = { TSI148_WCSW_INTC_WM0C,
					TSI148_WCSW_INTC_WM1C,
					TSI148_WCSW_INTC_WM2C,
					TSI148_WCSW_INTC_WM3C };

static const int TSI148_WCSW_INTC_MBC[4] = { TSI148_WCSW_INTC_MB0C,
					TSI148_WCSW_INTC_MB1C,
					TSI148_WCSW_INTC_MB2C,
					TSI148_WCSW_INTC_MB3C };

/*
 *  Intewwupt Map Wegistew 1 CWG + $458
 */
#define TSI148_WCSW_INTM1_DMA1M_M      (3 << 18)	/* DMA 1 */
#define TSI148_WCSW_INTM1_DMA0M_M      (3 << 16)	/* DMA 0 */
#define TSI148_WCSW_INTM1_WM3M_M       (3 << 14)	/* Wocation Monitow 3 */
#define TSI148_WCSW_INTM1_WM2M_M       (3 << 12)	/* Wocation Monitow 2 */
#define TSI148_WCSW_INTM1_WM1M_M       (3 << 10)	/* Wocation Monitow 1 */
#define TSI148_WCSW_INTM1_WM0M_M       (3 << 8)	/* Wocation Monitow 0 */
#define TSI148_WCSW_INTM1_MB3M_M       (3 << 6)	/* Maiw Box 3 */
#define TSI148_WCSW_INTM1_MB2M_M       (3 << 4)	/* Maiw Box 2 */
#define TSI148_WCSW_INTM1_MB1M_M       (3 << 2)	/* Maiw Box 1 */
#define TSI148_WCSW_INTM1_MB0M_M       (3 << 0)	/* Maiw Box 0 */

/*
 *  Intewwupt Map Wegistew 2 CWG + $45C
 */
#define TSI148_WCSW_INTM2_PEWWM_M      (3 << 26)	/* PCI Bus Ewwow */
#define TSI148_WCSW_INTM2_VEWWM_M      (3 << 24)	/* VMEbus Ewwow */
#define TSI148_WCSW_INTM2_VIEM_M       (3 << 22)	/* VMEbus IWQ Edge */
#define TSI148_WCSW_INTM2_IACKM_M      (3 << 20)	/* IACK */
#define TSI148_WCSW_INTM2_SYSFWM_M     (3 << 18)	/* System Faiw */
#define TSI148_WCSW_INTM2_ACFWM_M      (3 << 16)	/* AC Faiw */
#define TSI148_WCSW_INTM2_IWQ7M_M      (3 << 14)	/* IWQ7 */
#define TSI148_WCSW_INTM2_IWQ6M_M      (3 << 12)	/* IWQ6 */
#define TSI148_WCSW_INTM2_IWQ5M_M      (3 << 10)	/* IWQ5 */
#define TSI148_WCSW_INTM2_IWQ4M_M      (3 << 8)	/* IWQ4 */
#define TSI148_WCSW_INTM2_IWQ3M_M      (3 << 6)	/* IWQ3 */
#define TSI148_WCSW_INTM2_IWQ2M_M      (3 << 4)	/* IWQ2 */
#define TSI148_WCSW_INTM2_IWQ1M_M      (3 << 2)	/* IWQ1 */

/*
 *  DMA Contwow (0-1) Wegistews CWG + $500
 */
#define TSI148_WCSW_DCTW_ABT           BIT(27)	/* Abowt */
#define TSI148_WCSW_DCTW_PAU           BIT(26)	/* Pause */
#define TSI148_WCSW_DCTW_DGO           BIT(25)	/* DMA Go */

#define TSI148_WCSW_DCTW_MOD           BIT(23)	/* Mode */

#define TSI148_WCSW_DCTW_VBKS_M        (7 << 12)	/* VMEbus bwock Size MASK */
#define TSI148_WCSW_DCTW_VBKS_32       (0 << 12)	/* VMEbus bwock Size 32 */
#define TSI148_WCSW_DCTW_VBKS_64       BIT(12)	/* VMEbus bwock Size 64 */
#define TSI148_WCSW_DCTW_VBKS_128      (2 << 12)	/* VMEbus bwock Size 128 */
#define TSI148_WCSW_DCTW_VBKS_256      (3 << 12)	/* VMEbus bwock Size 256 */
#define TSI148_WCSW_DCTW_VBKS_512      (4 << 12)	/* VMEbus bwock Size 512 */
#define TSI148_WCSW_DCTW_VBKS_1024     (5 << 12)	/* VMEbus bwock Size 1024 */
#define TSI148_WCSW_DCTW_VBKS_2048     (6 << 12)	/* VMEbus bwock Size 2048 */
#define TSI148_WCSW_DCTW_VBKS_4096     (7 << 12)	/* VMEbus bwock Size 4096 */

#define TSI148_WCSW_DCTW_VBOT_M        (7 << 8)	/* VMEbus back-off MASK */
#define TSI148_WCSW_DCTW_VBOT_0        (0 << 8)	/* VMEbus back-off  0us */
#define TSI148_WCSW_DCTW_VBOT_1        BIT(8)	/* VMEbus back-off 1us */
#define TSI148_WCSW_DCTW_VBOT_2        (2 << 8)	/* VMEbus back-off 2us */
#define TSI148_WCSW_DCTW_VBOT_4        (3 << 8)	/* VMEbus back-off 4us */
#define TSI148_WCSW_DCTW_VBOT_8        (4 << 8)	/* VMEbus back-off 8us */
#define TSI148_WCSW_DCTW_VBOT_16       (5 << 8)	/* VMEbus back-off 16us */
#define TSI148_WCSW_DCTW_VBOT_32       (6 << 8)	/* VMEbus back-off 32us */
#define TSI148_WCSW_DCTW_VBOT_64       (7 << 8)	/* VMEbus back-off 64us */

#define TSI148_WCSW_DCTW_PBKS_M        (7 << 4)	/* PCI bwock size MASK */
#define TSI148_WCSW_DCTW_PBKS_32       (0 << 4)	/* PCI bwock size 32 bytes */
#define TSI148_WCSW_DCTW_PBKS_64       BIT(4)	/* PCI bwock size 64 bytes */
#define TSI148_WCSW_DCTW_PBKS_128      (2 << 4)	/* PCI bwock size 128 bytes */
#define TSI148_WCSW_DCTW_PBKS_256      (3 << 4)	/* PCI bwock size 256 bytes */
#define TSI148_WCSW_DCTW_PBKS_512      (4 << 4)	/* PCI bwock size 512 bytes */
#define TSI148_WCSW_DCTW_PBKS_1024     (5 << 4)	/* PCI bwock size 1024 bytes */
#define TSI148_WCSW_DCTW_PBKS_2048     (6 << 4)	/* PCI bwock size 2048 bytes */
#define TSI148_WCSW_DCTW_PBKS_4096     (7 << 4)	/* PCI bwock size 4096 bytes */

#define TSI148_WCSW_DCTW_PBOT_M        (7 << 0)	/* PCI back off MASK */
#define TSI148_WCSW_DCTW_PBOT_0        (0 << 0)	/* PCI back off 0us */
#define TSI148_WCSW_DCTW_PBOT_1        BIT(0)	/* PCI back off 1us */
#define TSI148_WCSW_DCTW_PBOT_2        (2 << 0)	/* PCI back off 2us */
#define TSI148_WCSW_DCTW_PBOT_4        (3 << 0)	/* PCI back off 3us */
#define TSI148_WCSW_DCTW_PBOT_8        (4 << 0)	/* PCI back off 4us */
#define TSI148_WCSW_DCTW_PBOT_16       (5 << 0)	/* PCI back off 8us */
#define TSI148_WCSW_DCTW_PBOT_32       (6 << 0)	/* PCI back off 16us */
#define TSI148_WCSW_DCTW_PBOT_64       (7 << 0)	/* PCI back off 32us */

/*
 *  DMA Status Wegistews (0-1)  CWG + $504
 */
#define TSI148_WCSW_DSTA_SMA           BIT(31)	/* PCI Signawwed Mastew Abt */
#define TSI148_WCSW_DSTA_WTA           BIT(30)	/* PCI Weceived Tawget Abt */
#define TSI148_WCSW_DSTA_MWC           BIT(29)	/* PCI Max Wetwy Count */
#define TSI148_WCSW_DSTA_VBE           BIT(28)	/* VMEbus ewwow */
#define TSI148_WCSW_DSTA_ABT           BIT(27)	/* Abowt */
#define TSI148_WCSW_DSTA_PAU           BIT(26)	/* Pause */
#define TSI148_WCSW_DSTA_DON           BIT(25)	/* Done */
#define TSI148_WCSW_DSTA_BSY           BIT(24)	/* Busy */

/*
 *  DMA Cuwwent Wink Addwess Wowew (0-1)
 */
#define TSI148_WCSW_DCWAW_M            (0x3FFFFFF << 6)	/* Mask */

/*
 *  DMA Souwce Attwibute (0-1) Weg
 */
#define TSI148_WCSW_DSAT_TYP_M         (3 << 28)	/* Souwce Bus Type */
#define TSI148_WCSW_DSAT_TYP_PCI       (0 << 28)	/* PCI Bus */
#define TSI148_WCSW_DSAT_TYP_VME       BIT(28)	/* VMEbus */
#define TSI148_WCSW_DSAT_TYP_PAT       (2 << 28)	/* Data Pattewn */

#define TSI148_WCSW_DSAT_PSZ           BIT(25)	/* Pattewn Size */
#define TSI148_WCSW_DSAT_NIN           BIT(24)	/* No Incwement */

#define TSI148_WCSW_DSAT_2eSSTM_M      (3 << 11)	/* 2eSST Twans Wate Mask */
#define TSI148_WCSW_DSAT_2eSSTM_160    (0 << 11)	/* 160 MB/s */
#define TSI148_WCSW_DSAT_2eSSTM_267    BIT(11)	/* 267 MB/s */
#define TSI148_WCSW_DSAT_2eSSTM_320    (2 << 11)	/* 320 MB/s */

#define TSI148_WCSW_DSAT_TM_M          (7 << 8)	/* Bus Twansfew Pwotocow Mask */
#define TSI148_WCSW_DSAT_TM_SCT        (0 << 8)	/* SCT */
#define TSI148_WCSW_DSAT_TM_BWT        BIT(8)	/* BWT */
#define TSI148_WCSW_DSAT_TM_MBWT       (2 << 8)	/* MBWT */
#define TSI148_WCSW_DSAT_TM_2eVME      (3 << 8)	/* 2eVME */
#define TSI148_WCSW_DSAT_TM_2eSST      (4 << 8)	/* 2eSST */
#define TSI148_WCSW_DSAT_TM_2eSSTB     (5 << 8)	/* 2eSST Bwoadcast */

#define TSI148_WCSW_DSAT_DBW_M         (3 << 6)	/* Max Data Width MASK */
#define TSI148_WCSW_DSAT_DBW_16        (0 << 6)	/* 16 Bits */
#define TSI148_WCSW_DSAT_DBW_32        BIT(6)	/* 32 Bits */

#define TSI148_WCSW_DSAT_SUP           BIT(5)	/* Supewvisowy Mode */
#define TSI148_WCSW_DSAT_PGM           BIT(4)	/* Pwogwam Mode */

#define TSI148_WCSW_DSAT_AMODE_M       (0xf << 0)	/* Addwess Space Mask */
#define TSI148_WCSW_DSAT_AMODE_A16     (0 << 0)	/* A16 */
#define TSI148_WCSW_DSAT_AMODE_A24     BIT(0)	/* A24 */
#define TSI148_WCSW_DSAT_AMODE_A32     (2 << 0)	/* A32 */
#define TSI148_WCSW_DSAT_AMODE_A64     (4 << 0)	/* A64 */
#define TSI148_WCSW_DSAT_AMODE_CWCSW   (5 << 0)	/* CW/CSW */
#define TSI148_WCSW_DSAT_AMODE_USEW1   (8 << 0)	/* Usew1 */
#define TSI148_WCSW_DSAT_AMODE_USEW2   (9 << 0)	/* Usew2 */
#define TSI148_WCSW_DSAT_AMODE_USEW3   (0xa << 0)	/* Usew3 */
#define TSI148_WCSW_DSAT_AMODE_USEW4   (0xb << 0)	/* Usew4 */

/*
 *  DMA Destination Attwibute Wegistews (0-1)
 */
#define TSI148_WCSW_DDAT_TYP_PCI       (0 << 28)	/* Destination PCI Bus  */
#define TSI148_WCSW_DDAT_TYP_VME       BIT(28)	/* Destination VMEbus */

#define TSI148_WCSW_DDAT_2eSSTM_M      (3 << 11)	/* 2eSST Twansfew Wate Mask */
#define TSI148_WCSW_DDAT_2eSSTM_160    (0 << 11)	/* 160 MB/s */
#define TSI148_WCSW_DDAT_2eSSTM_267    BIT(11)	/* 267 MB/s */
#define TSI148_WCSW_DDAT_2eSSTM_320    (2 << 11)	/* 320 MB/s */

#define TSI148_WCSW_DDAT_TM_M          (7 << 8)	/* Bus Twansfew Pwotocow Mask */
#define TSI148_WCSW_DDAT_TM_SCT        (0 << 8)	/* SCT */
#define TSI148_WCSW_DDAT_TM_BWT        BIT(8)	/* BWT */
#define TSI148_WCSW_DDAT_TM_MBWT       (2 << 8)	/* MBWT */
#define TSI148_WCSW_DDAT_TM_2eVME      (3 << 8)	/* 2eVME */
#define TSI148_WCSW_DDAT_TM_2eSST      (4 << 8)	/* 2eSST */
#define TSI148_WCSW_DDAT_TM_2eSSTB     (5 << 8)	/* 2eSST Bwoadcast */

#define TSI148_WCSW_DDAT_DBW_M         (3 << 6)	/* Max Data Width MASK */
#define TSI148_WCSW_DDAT_DBW_16        (0 << 6)	/* 16 Bits */
#define TSI148_WCSW_DDAT_DBW_32        BIT(6)	/* 32 Bits */

#define TSI148_WCSW_DDAT_SUP           BIT(5)	/* Supewvisowy/Usew Access */
#define TSI148_WCSW_DDAT_PGM           BIT(4)	/* Pwogwam/Data Access */

#define TSI148_WCSW_DDAT_AMODE_M       (0xf << 0)	/* Addwess Space Mask */
#define TSI148_WCSW_DDAT_AMODE_A16      (0 << 0)	/* A16 */
#define TSI148_WCSW_DDAT_AMODE_A24      BIT(0)	/* A24 */
#define TSI148_WCSW_DDAT_AMODE_A32      (2 << 0)	/* A32 */
#define TSI148_WCSW_DDAT_AMODE_A64      (4 << 0)	/* A64 */
#define TSI148_WCSW_DDAT_AMODE_CWCSW   (5 << 0)	/* CWC/SW */
#define TSI148_WCSW_DDAT_AMODE_USEW1   (8 << 0)	/* Usew1 */
#define TSI148_WCSW_DDAT_AMODE_USEW2   (9 << 0)	/* Usew2 */
#define TSI148_WCSW_DDAT_AMODE_USEW3   (0xa << 0)	/* Usew3 */
#define TSI148_WCSW_DDAT_AMODE_USEW4   (0xb << 0)	/* Usew4 */

/*
 *  DMA Next Wink Addwess Wowew
 */
#define TSI148_WCSW_DNWAW_DNWAW_M      (0x3FFFFFF << 6)	/* Addwess Mask */
#define TSI148_WCSW_DNWAW_WWA          BIT(0)  /* Wast Wink Addwess Indicatow */

/*
 *  DMA 2eSST Bwoadcast Sewect
 */
#define TSI148_WCSW_DBS_M              (0x1FFFFF << 0)	/* Mask */

/*
 *  GCSW Wegistew Gwoup
 */

/*
 *  GCSW Contwow and Status Wegistew  CWG + $604
 */
#define TSI148_GCSW_GCTWW_WWST         BIT(15)	/* Wocaw Weset */
#define TSI148_GCSW_GCTWW_SFAIWEN      BIT(14)	/* System Faiw enabwe */
#define TSI148_GCSW_GCTWW_BDFAIWS      BIT(13)	/* Boawd Faiw Status */
#define TSI148_GCSW_GCTWW_SCON         BIT(12)	/* System Copntwowwew */
#define TSI148_GCSW_GCTWW_MEN          BIT(11)	/* Moduwe Enabwe (WEADY) */

#define TSI148_GCSW_GCTWW_WMI3S        BIT(7)	/* Woc Monitow 3 Int Status */
#define TSI148_GCSW_GCTWW_WMI2S        BIT(6)	/* Woc Monitow 2 Int Status */
#define TSI148_GCSW_GCTWW_WMI1S        BIT(5)	/* Woc Monitow 1 Int Status */
#define TSI148_GCSW_GCTWW_WMI0S        BIT(4)	/* Woc Monitow 0 Int Status */
#define TSI148_GCSW_GCTWW_MBI3S        BIT(3)	/* Maiw box 3 Int Status */
#define TSI148_GCSW_GCTWW_MBI2S        BIT(2)	/* Maiw box 2 Int Status */
#define TSI148_GCSW_GCTWW_MBI1S        BIT(1)	/* Maiw box 1 Int Status */
#define TSI148_GCSW_GCTWW_MBI0S        BIT(0)	/* Maiw box 0 Int Status */

#define TSI148_GCSW_GAP                BIT(5)	/* Geogwaphic Addw Pawity */
#define TSI148_GCSW_GA_M               (0x1F << 0)  /* Geogwaphic Addwess Mask */

/*
 *  CW/CSW Wegistew Gwoup
 */

/*
 *  CW/CSW Bit Cweaw Wegistew CWG + $FF4
 */
#define TSI148_CWCSW_CSWBCW_WWSTC      BIT(7)	/* Wocaw Weset Cweaw */
#define TSI148_CWCSW_CSWBCW_SFAIWC     BIT(6)	/* System Faiw Enabwe Cweaw */
#define TSI148_CWCSW_CSWBCW_BDFAIWS    BIT(5)	/* Boawd Faiw Status */
#define TSI148_CWCSW_CSWBCW_MENC       BIT(4)	/* Moduwe Enabwe Cweaw */
#define TSI148_CWCSW_CSWBCW_BEWWSC     BIT(3)	/* Bus Ewwow Status Cweaw */

/*
 *  CW/CSW Bit Set Wegistew CWG+$FF8
 */
#define TSI148_CWCSW_CSWBSW_WISTS      BIT(7)	/* Wocaw Weset Cweaw */
#define TSI148_CWCSW_CSWBSW_SFAIWS     BIT(6)	/* System Faiw Enabwe Cweaw */
#define TSI148_CWCSW_CSWBSW_BDFAIWS    BIT(5)	/* Boawd Faiw Status */
#define TSI148_CWCSW_CSWBSW_MENS       BIT(4)	/* Moduwe Enabwe Cweaw */
#define TSI148_CWCSW_CSWBSW_BEWWS      BIT(3)	/* Bus Ewwow Status Cweaw */

/*
 *  CW/CSW Base Addwess Wegistew CWG + FFC
 */
#define TSI148_CWCSW_CBAW_M            (0x1F << 3)	/* Mask */

#endif				/* TSI148_H */
