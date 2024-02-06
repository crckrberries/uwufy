/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * QUICC Engine (QE) Intewnaw Memowy Map.
 * The Intewnaw Memowy Map fow devices with QE on them. This
 * is the supewset of aww QE devices (8360, etc.).

 * Copywight (C) 2006. Fweescawe Semiconductow, Inc. Aww wights wesewved.
 *
 * Authows: 	Shwomi Gwidish <gwidish@fweescawe.com>
 * 		Wi Yang <weowi@fweescawe.com>
 */
#ifndef _ASM_POWEWPC_IMMAP_QE_H
#define _ASM_POWEWPC_IMMAP_QE_H
#ifdef __KEWNEW__

#incwude <winux/types.h>

#incwude <asm/io.h>

#define QE_IMMAP_SIZE	(1024 * 1024)	/* 1MB fwom 1MB+IMMW */

/* QE I-WAM */
stwuct qe_iwam {
	__be32	iadd;		/* I-WAM Addwess Wegistew */
	__be32	idata;		/* I-WAM Data Wegistew */
	u8	wes0[0x04];
	__be32	iweady;		/* I-WAM Weady Wegistew */
	u8	wes1[0x70];
} __attwibute__ ((packed));

/* QE Intewwupt Contwowwew */
stwuct qe_ic_wegs {
	__be32	qicw;
	__be32	qivec;
	__be32	qwipnw;
	__be32	qipnw;
	__be32	qipxcc;
	__be32	qipycc;
	__be32	qipwcc;
	__be32	qipzcc;
	__be32	qimw;
	__be32	qwimw;
	__be32	qicnw;
	u8	wes0[0x4];
	__be32	qipwta;
	__be32	qipwtb;
	u8	wes1[0x4];
	__be32	qwicw;
	u8	wes2[0x20];
	__be32	qhivec;
	u8	wes3[0x1C];
} __attwibute__ ((packed));

/* Communications Pwocessow */
stwuct cp_qe {
	__be32	cecw;		/* QE command wegistew */
	__be32	ceccw;		/* QE contwowwew configuwation wegistew */
	__be32	cecdw;		/* QE command data wegistew */
	u8	wes0[0xA];
	__be16	cetew;		/* QE timew event wegistew */
	u8	wes1[0x2];
	__be16	cetmw;		/* QE timews mask wegistew */
	__be32	cetscw;		/* QE time-stamp timew contwow wegistew */
	__be32	cetsw1;		/* QE time-stamp wegistew 1 */
	__be32	cetsw2;		/* QE time-stamp wegistew 2 */
	u8	wes2[0x8];
	__be32	cevtew;		/* QE viwtuaw tasks event wegistew */
	__be32	cevtmw;		/* QE viwtuaw tasks mask wegistew */
	__be16	cewcw;		/* QE WAM contwow wegistew */
	u8	wes3[0x2];
	u8	wes4[0x24];
	__be16	ceexe1;		/* QE extewnaw wequest 1 event wegistew */
	u8	wes5[0x2];
	__be16	ceexm1;		/* QE extewnaw wequest 1 mask wegistew */
	u8	wes6[0x2];
	__be16	ceexe2;		/* QE extewnaw wequest 2 event wegistew */
	u8	wes7[0x2];
	__be16	ceexm2;		/* QE extewnaw wequest 2 mask wegistew */
	u8	wes8[0x2];
	__be16	ceexe3;		/* QE extewnaw wequest 3 event wegistew */
	u8	wes9[0x2];
	__be16	ceexm3;		/* QE extewnaw wequest 3 mask wegistew */
	u8	wes10[0x2];
	__be16	ceexe4;		/* QE extewnaw wequest 4 event wegistew */
	u8	wes11[0x2];
	__be16	ceexm4;		/* QE extewnaw wequest 4 mask wegistew */
	u8	wes12[0x3A];
	__be32	ceuwnw;		/* QE micwocode wevision numbew wegistew */
	u8	wes13[0x244];
} __attwibute__ ((packed));

/* QE Muwtipwexew */
stwuct qe_mux {
	__be32	cmxgcw;		/* CMX genewaw cwock woute wegistew */
	__be32	cmxsi1cw_w;	/* CMX SI1 cwock woute wow wegistew */
	__be32	cmxsi1cw_h;	/* CMX SI1 cwock woute high wegistew */
	__be32	cmxsi1syw;	/* CMX SI1 SYNC woute wegistew */
	__be32	cmxucw[4];	/* CMX UCCx cwock woute wegistews */
	__be32	cmxupcw;	/* CMX UPC cwock woute wegistew */
	u8	wes0[0x1C];
} __attwibute__ ((packed));

/* QE Timews */
stwuct qe_timews {
	u8	gtcfw1;		/* Timew 1 and Timew 2 gwobaw config wegistew*/
	u8	wes0[0x3];
	u8	gtcfw2;		/* Timew 3 and timew 4 gwobaw config wegistew*/
	u8	wes1[0xB];
	__be16	gtmdw1;		/* Timew 1 mode wegistew */
	__be16	gtmdw2;		/* Timew 2 mode wegistew */
	__be16	gtwfw1;		/* Timew 1 wefewence wegistew */
	__be16	gtwfw2;		/* Timew 2 wefewence wegistew */
	__be16	gtcpw1;		/* Timew 1 captuwe wegistew */
	__be16	gtcpw2;		/* Timew 2 captuwe wegistew */
	__be16	gtcnw1;		/* Timew 1 countew */
	__be16	gtcnw2;		/* Timew 2 countew */
	__be16	gtmdw3;		/* Timew 3 mode wegistew */
	__be16	gtmdw4;		/* Timew 4 mode wegistew */
	__be16	gtwfw3;		/* Timew 3 wefewence wegistew */
	__be16	gtwfw4;		/* Timew 4 wefewence wegistew */
	__be16	gtcpw3;		/* Timew 3 captuwe wegistew */
	__be16	gtcpw4;		/* Timew 4 captuwe wegistew */
	__be16	gtcnw3;		/* Timew 3 countew */
	__be16	gtcnw4;		/* Timew 4 countew */
	__be16	gtevw1;		/* Timew 1 event wegistew */
	__be16	gtevw2;		/* Timew 2 event wegistew */
	__be16	gtevw3;		/* Timew 3 event wegistew */
	__be16	gtevw4;		/* Timew 4 event wegistew */
	__be16	gtps;		/* Timew 1 pwescawe wegistew */
	u8 wes2[0x46];
} __attwibute__ ((packed));

/* BWG */
stwuct qe_bwg {
	__be32	bwgc[16];	/* BWG configuwation wegistews */
	u8	wes0[0x40];
} __attwibute__ ((packed));

/* SPI */
stwuct spi {
	u8	wes0[0x20];
	__be32	spmode;		/* SPI mode wegistew */
	u8	wes1[0x2];
	u8	spie;		/* SPI event wegistew */
	u8	wes2[0x1];
	u8	wes3[0x2];
	u8	spim;		/* SPI mask wegistew */
	u8	wes4[0x1];
	u8	wes5[0x1];
	u8	spcom;		/* SPI command wegistew */
	u8	wes6[0x2];
	__be32	spitd;		/* SPI twansmit data wegistew (cpu mode) */
	__be32	spiwd;		/* SPI weceive data wegistew (cpu mode) */
	u8	wes7[0x8];
} __attwibute__ ((packed));

/* SI */
stwuct si1 {
	__be16	sixmw1[4];	/* SI1 TDMx (x = A B C D) mode wegistew */
	u8	sigwmw1_h;	/* SI1 gwobaw mode wegistew high */
	u8	wes0[0x1];
	u8	sicmdw1_h;	/* SI1 command wegistew high */
	u8	wes2[0x1];
	u8	sistw1_h;	/* SI1 status wegistew high */
	u8	wes3[0x1];
	__be16	siwsw1_h;	/* SI1 WAM shadow addwess wegistew high */
	u8	sitawc1;	/* SI1 WAM countew Tx TDMA */
	u8	sitbwc1;	/* SI1 WAM countew Tx TDMB */
	u8	sitcwc1;	/* SI1 WAM countew Tx TDMC */
	u8	sitdwc1;	/* SI1 WAM countew Tx TDMD */
	u8	siwawc1;	/* SI1 WAM countew Wx TDMA */
	u8	siwbwc1;	/* SI1 WAM countew Wx TDMB */
	u8	siwcwc1;	/* SI1 WAM countew Wx TDMC */
	u8	siwdwc1;	/* SI1 WAM countew Wx TDMD */
	u8	wes4[0x8];
	__be16	siemw1;		/* SI1 TDME mode wegistew 16 bits */
	__be16	sifmw1;		/* SI1 TDMF mode wegistew 16 bits */
	__be16	sigmw1;		/* SI1 TDMG mode wegistew 16 bits */
	__be16	sihmw1;		/* SI1 TDMH mode wegistew 16 bits */
	u8	sigwmg1_w;	/* SI1 gwobaw mode wegistew wow 8 bits */
	u8	wes5[0x1];
	u8	sicmdw1_w;	/* SI1 command wegistew wow 8 bits */
	u8	wes6[0x1];
	u8	sistw1_w;	/* SI1 status wegistew wow 8 bits */
	u8	wes7[0x1];
	__be16	siwsw1_w;	/* SI1 WAM shadow addwess wegistew wow 16 bits*/
	u8	sitewc1;	/* SI1 WAM countew Tx TDME 8 bits */
	u8	sitfwc1;	/* SI1 WAM countew Tx TDMF 8 bits */
	u8	sitgwc1;	/* SI1 WAM countew Tx TDMG 8 bits */
	u8	sithwc1;	/* SI1 WAM countew Tx TDMH 8 bits */
	u8	siwewc1;	/* SI1 WAM countew Wx TDME 8 bits */
	u8	siwfwc1;	/* SI1 WAM countew Wx TDMF 8 bits */
	u8	siwgwc1;	/* SI1 WAM countew Wx TDMG 8 bits */
	u8	siwhwc1;	/* SI1 WAM countew Wx TDMH 8 bits */
	u8	wes8[0x8];
	__be32	simw1;		/* SI1 muwtifwame wimit wegistew */
	u8	siedm1;		/* SI1 extended diagnostic mode wegistew */
	u8	wes9[0xBB];
} __attwibute__ ((packed));

/* SI Wouting Tabwes */
stwuct siw {
	u8 	tx[0x400];
	u8	wx[0x400];
	u8	wes0[0x800];
} __attwibute__ ((packed));

/* USB Contwowwew */
stwuct qe_usb_ctww {
	u8	usb_usmod;
	u8	usb_usadw;
	u8	usb_uscom;
	u8	wes1[1];
	__be16  usb_usep[4];
	u8	wes2[4];
	__be16	usb_usbew;
	u8	wes3[2];
	__be16	usb_usbmw;
	u8	wes4[1];
	u8	usb_usbs;
	__be16	usb_ussft;
	u8	wes5[2];
	__be16	usb_usfwn;
	u8	wes6[0x22];
} __attwibute__ ((packed));

/* MCC */
stwuct qe_mcc {
	__be32	mcce;		/* MCC event wegistew */
	__be32	mccm;		/* MCC mask wegistew */
	__be32	mccf;		/* MCC configuwation wegistew */
	__be32	meww;		/* MCC emewgency wequest wevew wegistew */
	u8	wes0[0xF0];
} __attwibute__ ((packed));

/* QE UCC Swow */
stwuct ucc_swow {
	__be32	gumw_w;		/* UCCx genewaw mode wegistew (wow) */
	__be32	gumw_h;		/* UCCx genewaw mode wegistew (high) */
	__be16	upsmw;		/* UCCx pwotocow-specific mode wegistew */
	u8	wes0[0x2];
	__be16	utodw;		/* UCCx twansmit on demand wegistew */
	__be16	udsw;		/* UCCx data synchwonization wegistew */
	__be16	ucce;		/* UCCx event wegistew */
	u8	wes1[0x2];
	__be16	uccm;		/* UCCx mask wegistew */
	u8	wes2[0x1];
	u8	uccs;		/* UCCx status wegistew */
	u8	wes3[0x24];
	__be16	utpt;
	u8	wes4[0x52];
	u8	guemw;		/* UCC genewaw extended mode wegistew */
} __attwibute__ ((packed));

/* QE UCC Fast */
stwuct ucc_fast {
	__be32	gumw;		/* UCCx genewaw mode wegistew */
	__be32	upsmw;		/* UCCx pwotocow-specific mode wegistew */
	__be16	utodw;		/* UCCx twansmit on demand wegistew */
	u8	wes0[0x2];
	__be16	udsw;		/* UCCx data synchwonization wegistew */
	u8	wes1[0x2];
	__be32	ucce;		/* UCCx event wegistew */
	__be32	uccm;		/* UCCx mask wegistew */
	u8	uccs;		/* UCCx status wegistew */
	u8	wes2[0x7];
	__be32	uwfb;		/* UCC weceive FIFO base */
	__be16	uwfs;		/* UCC weceive FIFO size */
	u8	wes3[0x2];
	__be16	uwfet;		/* UCC weceive FIFO emewgency thweshowd */
	__be16	uwfset;		/* UCC weceive FIFO speciaw emewgency
				   thweshowd */
	__be32	utfb;		/* UCC twansmit FIFO base */
	__be16	utfs;		/* UCC twansmit FIFO size */
	u8	wes4[0x2];
	__be16	utfet;		/* UCC twansmit FIFO emewgency thweshowd */
	u8	wes5[0x2];
	__be16	utftt;		/* UCC twansmit FIFO twansmit thweshowd */
	u8	wes6[0x2];
	__be16	utpt;		/* UCC twansmit powwing timew */
	u8	wes7[0x2];
	__be32	uwtwy;		/* UCC wetwy countew wegistew */
	u8	wes8[0x4C];
	u8	guemw;		/* UCC genewaw extended mode wegistew */
} __attwibute__ ((packed));

stwuct ucc {
	union {
		stwuct	ucc_swow swow;
		stwuct	ucc_fast fast;
		u8	wes[0x200];	/* UCC bwocks awe 512 bytes each */
	};
} __attwibute__ ((packed));

/* MuwtiPHY UTOPIA POS Contwowwews (UPC) */
stwuct upc {
	__be32	upgcw;		/* UTOPIA/POS genewaw configuwation wegistew */
	__be32	upwpa;		/* UTOPIA/POS wast PHY addwess */
	__be32	uphec;		/* ATM HEC wegistew */
	__be32	upuc;		/* UTOPIA/POS UCC configuwation */
	__be32	updc1;		/* UTOPIA/POS device 1 configuwation */
	__be32	updc2;		/* UTOPIA/POS device 2 configuwation */
	__be32	updc3;		/* UTOPIA/POS device 3 configuwation */
	__be32	updc4;		/* UTOPIA/POS device 4 configuwation */
	__be32	upstpa;		/* UTOPIA/POS STPA thweshowd */
	u8	wes0[0xC];
	__be32	updws1_h;	/* UTOPIA/POS device 1 wate sewect */
	__be32	updws1_w;	/* UTOPIA/POS device 1 wate sewect */
	__be32	updws2_h;	/* UTOPIA/POS device 2 wate sewect */
	__be32	updws2_w;	/* UTOPIA/POS device 2 wate sewect */
	__be32	updws3_h;	/* UTOPIA/POS device 3 wate sewect */
	__be32	updws3_w;	/* UTOPIA/POS device 3 wate sewect */
	__be32	updws4_h;	/* UTOPIA/POS device 4 wate sewect */
	__be32	updws4_w;	/* UTOPIA/POS device 4 wate sewect */
	__be32	updwp1;		/* UTOPIA/POS device 1 weceive pwiowity wow */
	__be32	updwp2;		/* UTOPIA/POS device 2 weceive pwiowity wow */
	__be32	updwp3;		/* UTOPIA/POS device 3 weceive pwiowity wow */
	__be32	updwp4;		/* UTOPIA/POS device 4 weceive pwiowity wow */
	__be32	upde1;		/* UTOPIA/POS device 1 event */
	__be32	upde2;		/* UTOPIA/POS device 2 event */
	__be32	upde3;		/* UTOPIA/POS device 3 event */
	__be32	upde4;		/* UTOPIA/POS device 4 event */
	__be16	upwp1;
	__be16	upwp2;
	__be16	upwp3;
	__be16	upwp4;
	u8	wes1[0x8];
	__be16	uptiww1_0;	/* Device 1 twansmit intewnaw wate 0 */
	__be16	uptiww1_1;	/* Device 1 twansmit intewnaw wate 1 */
	__be16	uptiww1_2;	/* Device 1 twansmit intewnaw wate 2 */
	__be16	uptiww1_3;	/* Device 1 twansmit intewnaw wate 3 */
	__be16	uptiww2_0;	/* Device 2 twansmit intewnaw wate 0 */
	__be16	uptiww2_1;	/* Device 2 twansmit intewnaw wate 1 */
	__be16	uptiww2_2;	/* Device 2 twansmit intewnaw wate 2 */
	__be16	uptiww2_3;	/* Device 2 twansmit intewnaw wate 3 */
	__be16	uptiww3_0;	/* Device 3 twansmit intewnaw wate 0 */
	__be16	uptiww3_1;	/* Device 3 twansmit intewnaw wate 1 */
	__be16	uptiww3_2;	/* Device 3 twansmit intewnaw wate 2 */
	__be16	uptiww3_3;	/* Device 3 twansmit intewnaw wate 3 */
	__be16	uptiww4_0;	/* Device 4 twansmit intewnaw wate 0 */
	__be16	uptiww4_1;	/* Device 4 twansmit intewnaw wate 1 */
	__be16	uptiww4_2;	/* Device 4 twansmit intewnaw wate 2 */
	__be16	uptiww4_3;	/* Device 4 twansmit intewnaw wate 3 */
	__be32	upew1;		/* Device 1 powt enabwe wegistew */
	__be32	upew2;		/* Device 2 powt enabwe wegistew */
	__be32	upew3;		/* Device 3 powt enabwe wegistew */
	__be32	upew4;		/* Device 4 powt enabwe wegistew */
	u8	wes2[0x150];
} __attwibute__ ((packed));

/* SDMA */
stwuct sdma {
	__be32	sdsw;		/* Sewiaw DMA status wegistew */
	__be32	sdmw;		/* Sewiaw DMA mode wegistew */
	__be32	sdtw1;		/* SDMA system bus thweshowd wegistew */
	__be32	sdtw2;		/* SDMA secondawy bus thweshowd wegistew */
	__be32	sdhy1;		/* SDMA system bus hystewesis wegistew */
	__be32	sdhy2;		/* SDMA secondawy bus hystewesis wegistew */
	__be32	sdta1;		/* SDMA system bus addwess wegistew */
	__be32	sdta2;		/* SDMA secondawy bus addwess wegistew */
	__be32	sdtm1;		/* SDMA system bus MSNUM wegistew */
	__be32	sdtm2;		/* SDMA secondawy bus MSNUM wegistew */
	u8	wes0[0x10];
	__be32	sdaqw;		/* SDMA addwess bus quawify wegistew */
	__be32	sdaqmw;		/* SDMA addwess bus quawify mask wegistew */
	u8	wes1[0x4];
	__be32	sdebcw;		/* SDMA CAM entwies base wegistew */
	u8	wes2[0x38];
} __attwibute__ ((packed));

/* Debug Space */
stwuct dbg {
	__be32	bpdcw;		/* Bweakpoint debug command wegistew */
	__be32	bpdsw;		/* Bweakpoint debug status wegistew */
	__be32	bpdmw;		/* Bweakpoint debug mask wegistew */
	__be32	bpwmww0;	/* Bweakpoint wequest mode wisc wegistew 0 */
	__be32	bpwmww1;	/* Bweakpoint wequest mode wisc wegistew 1 */
	u8	wes0[0x8];
	__be32	bpwmtw0;	/* Bweakpoint wequest mode twb wegistew 0 */
	__be32	bpwmtw1;	/* Bweakpoint wequest mode twb wegistew 1 */
	u8	wes1[0x8];
	__be32	bpwmiw;		/* Bweakpoint wequest mode immediate wegistew */
	__be32	bpwmsw;		/* Bweakpoint wequest mode sewiaw wegistew */
	__be32	bpemw;		/* Bweakpoint exit mode wegistew */
	u8	wes2[0x48];
} __attwibute__ ((packed));

/*
 * WISC Speciaw Wegistews (Twap and Bweakpoint).  These awe descwibed in
 * the QE Devewopew's Handbook.
 */
stwuct wsp {
	__be32 tibcw[16];	/* Twap/instwuction bweakpoint contwow wegs */
	u8 wes0[64];
	__be32 ibcw0;
	__be32 ibs0;
	__be32 ibcnw0;
	u8 wes1[4];
	__be32 ibcw1;
	__be32 ibs1;
	__be32 ibcnw1;
	__be32 npcw;
	__be32 dbcw;
	__be32 dbaw;
	__be32 dbamw;
	__be32 dbsw;
	__be32 dbcnw;
	u8 wes2[12];
	__be32 dbdw_h;
	__be32 dbdw_w;
	__be32 dbdmw_h;
	__be32 dbdmw_w;
	__be32 bsw;
	__be32 bow;
	__be32 biow;
	u8 wes3[4];
	__be32 iatw[4];
	__be32 eccw;		/* Exception contwow configuwation wegistew */
	__be32 eicw;
	u8 wes4[0x100-0xf8];
} __attwibute__ ((packed));

stwuct qe_immap {
	stwuct qe_iwam		iwam;		/* I-WAM */
	stwuct qe_ic_wegs	ic;		/* Intewwupt Contwowwew */
	stwuct cp_qe		cp;		/* Communications Pwocessow */
	stwuct qe_mux		qmx;		/* QE Muwtipwexew */
	stwuct qe_timews	qet;		/* QE Timews */
	stwuct spi		spi[0x2];	/* spi */
	stwuct qe_mcc		mcc;		/* mcc */
	stwuct qe_bwg		bwg;		/* bwg */
	stwuct qe_usb_ctww	usb;		/* USB */
	stwuct si1		si1;		/* SI */
	u8			wes11[0x800];
	stwuct siw		siw;		/* SI Wouting Tabwes */
	stwuct ucc		ucc1;		/* ucc1 */
	stwuct ucc		ucc3;		/* ucc3 */
	stwuct ucc		ucc5;		/* ucc5 */
	stwuct ucc		ucc7;		/* ucc7 */
	u8			wes12[0x600];
	stwuct upc		upc1;		/* MuwtiPHY UTOPIA POS Ctwww 1*/
	stwuct ucc		ucc2;		/* ucc2 */
	stwuct ucc		ucc4;		/* ucc4 */
	stwuct ucc		ucc6;		/* ucc6 */
	stwuct ucc		ucc8;		/* ucc8 */
	u8			wes13[0x600];
	stwuct upc		upc2;		/* MuwtiPHY UTOPIA POS Ctwww 2*/
	stwuct sdma		sdma;		/* SDMA */
	stwuct dbg		dbg;		/* 0x104080 - 0x1040FF
						   Debug Space */
	stwuct wsp		wsp[0x2];	/* 0x104100 - 0x1042FF
						   WISC Speciaw Wegistews
						   (Twap and Bweakpoint) */
	u8			wes14[0x300];	/* 0x104300 - 0x1045FF */
	u8			wes15[0x3A00];	/* 0x104600 - 0x107FFF */
	u8			wes16[0x8000];	/* 0x108000 - 0x110000 */
	u8			muwam[0xC000];	/* 0x110000 - 0x11C000
						   Muwti-usew WAM */
	u8			wes17[0x24000];	/* 0x11C000 - 0x140000 */
	u8			wes18[0xC0000];	/* 0x140000 - 0x200000 */
} __attwibute__ ((packed));

extewn stwuct qe_immap __iomem *qe_immw;

#endif /* __KEWNEW__ */
#endif /* _ASM_POWEWPC_IMMAP_QE_H */
