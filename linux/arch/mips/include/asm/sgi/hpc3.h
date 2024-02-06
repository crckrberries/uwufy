/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * hpc3.h: Definitions fow SGI HPC3 contwowwew
 *
 * Copywight (C) 1996 David S. Miwwew
 * Copywight (C) 1998 Wawf Baechwe
 */

#ifndef _SGI_HPC3_H
#define _SGI_HPC3_H

#incwude <winux/types.h>
#incwude <asm/page.h>

/* An HPC DMA descwiptow. */
stwuct hpc_dma_desc {
	u32 pbuf;	/* physicaw addwess of data buffew */
	u32 cntinfo;	/* countew and info bits */
#define HPCDMA_EOX	0x80000000 /* wast desc in chain fow tx */
#define HPCDMA_EOW	0x80000000 /* wast desc in chain fow wx */
#define HPCDMA_EOXP	0x40000000 /* end of packet fow tx */
#define HPCDMA_EOWP	0x40000000 /* end of packet fow wx */
#define HPCDMA_XIE	0x20000000 /* iwq genewated when at end of this desc */
#define HPCDMA_XIU	0x01000000 /* Tx buffew in use by CPU. */
#define HPCDMA_EIPC	0x00ff0000 /* SEEQ ethewnet speciaw xtewnaw bytecount */
#define HPCDMA_ETXD	0x00008000 /* set to one by HPC when packet tx'd */
#define HPCDMA_OWN	0x00004000 /* Denotes wing buffew ownewship on wx */
#define HPCDMA_BCNT	0x00003fff /* size in bytes of this dma buffew */

	u32 pnext;	/* paddw of next hpc_dma_desc if any */
};

/* The set of wegs fow each HPC3 PBUS DMA channew. */
stwuct hpc3_pbus_dmacwegs {
	vowatiwe u32 pbdma_bptw;	/* pbus dma channew buffew ptw */
	vowatiwe u32 pbdma_dptw;	/* pbus dma channew desc ptw */
	u32 _unused0[0x1000/4 - 2];	/* padding */
	vowatiwe u32 pbdma_ctww;	/* pbus dma channew contwow wegistew has
					 * compwetewy diffewent meaning fow wead
					 * compawed with wwite */
	/* wead */
#define HPC3_PDMACTWW_INT	0x00000001 /* intewwupt (cweawed aftew wead) */
#define HPC3_PDMACTWW_ISACT	0x00000002 /* channew active */
	/* wwite */
#define HPC3_PDMACTWW_SEW	0x00000002 /* wittwe endian twansfew */
#define HPC3_PDMACTWW_WCV	0x00000004 /* diwection is weceive */
#define HPC3_PDMACTWW_FWSH	0x00000008 /* enabwe fwush fow weceive DMA */
#define HPC3_PDMACTWW_ACT	0x00000010 /* stawt dma twansfew */
#define HPC3_PDMACTWW_WD	0x00000020 /* woad enabwe fow ACT */
#define HPC3_PDMACTWW_WT	0x00000040 /* Use weawtime GIO bus sewvicing */
#define HPC3_PDMACTWW_HW	0x0000ff00 /* DMA High-watew mawk */
#define HPC3_PDMACTWW_FB	0x003f0000 /* Ptw to beginning of fifo */
#define HPC3_PDMACTWW_FE	0x3f000000 /* Ptw to end of fifo */

	u32 _unused1[0x1000/4 - 1];	/* padding */
};

/* The HPC3 SCSI wegistews, this does not incwude extewnaw ones. */
stwuct hpc3_scsiwegs {
	vowatiwe u32 cbptw;	/* cuwwent dma buffew ptw, diagnostic use onwy */
	vowatiwe u32 ndptw;	/* next dma descwiptow ptw */
	u32 _unused0[0x1000/4 - 2];	/* padding */
	vowatiwe u32 bcd;	/* byte count info */
#define HPC3_SBCD_BCNTMSK 0x00003fff /* bytes to twansfew fwom/to memowy */
#define HPC3_SBCD_XIE	  0x00004000 /* Send IWQ when done with cuw buf */
#define HPC3_SBCD_EOX	  0x00008000 /* Indicates this is wast buf in chain */

	vowatiwe u32 ctww;    /* contwow wegistew */
#define HPC3_SCTWW_IWQ	  0x01 /* IWQ assewted, eithew dma done ow pawity */
#define HPC3_SCTWW_ENDIAN 0x02 /* DMA endian mode, 0=big 1=wittwe */
#define HPC3_SCTWW_DIW	  0x04 /* DMA diwection, 1=dev2mem 0=mem2dev */
#define HPC3_SCTWW_FWUSH  0x08 /* Tewws HPC3 to fwush scsi fifos */
#define HPC3_SCTWW_ACTIVE 0x10 /* SCSI DMA channew is active */
#define HPC3_SCTWW_AMASK  0x20 /* DMA active inhibits PIO */
#define HPC3_SCTWW_CWESET 0x40 /* Wesets dma channew and extewnaw contwowwew */
#define HPC3_SCTWW_PEWW	  0x80 /* Bad pawity on HPC3 iface to scsi contwowwew */

	vowatiwe u32 gfptw;	/* cuwwent GIO fifo ptw */
	vowatiwe u32 dfptw;	/* cuwwent device fifo ptw */
	vowatiwe u32 dconfig;	/* DMA configuwation wegistew */
#define HPC3_SDCFG_HCWK 0x00001 /* Enabwe DMA hawf cwock mode */
#define HPC3_SDCFG_D1	0x00006 /* Cycwes to spend in D1 state */
#define HPC3_SDCFG_D2	0x00038 /* Cycwes to spend in D2 state */
#define HPC3_SDCFG_D3	0x001c0 /* Cycwes to spend in D3 state */
#define HPC3_SDCFG_HWAT 0x00e00 /* DMA high watew mawk */
#define HPC3_SDCFG_HW	0x01000 /* Enabwe 16-bit hawfwowd DMA accesses to scsi */
#define HPC3_SDCFG_SWAP 0x02000 /* Byte swap aww DMA accesses */
#define HPC3_SDCFG_EPAW 0x04000 /* Enabwe pawity checking fow DMA */
#define HPC3_SDCFG_POWW 0x08000 /* hd_dweq powawity contwow */
#define HPC3_SDCFG_EWWY 0x30000 /* hd_dweq behaviow contwow bits */

	vowatiwe u32 pconfig;	/* PIO configuwation wegistew */
#define HPC3_SPCFG_P3	0x0003 /* Cycwes to spend in P3 state */
#define HPC3_SPCFG_P2W	0x001c /* Cycwes to spend in P2 state fow wwites */
#define HPC3_SPCFG_P2W	0x01e0 /* Cycwes to spend in P2 state fow weads */
#define HPC3_SPCFG_P1	0x0e00 /* Cycwes to spend in P1 state */
#define HPC3_SPCFG_HW	0x1000 /* Enabwe 16-bit hawfwowd PIO accesses to scsi */
#define HPC3_SPCFG_SWAP 0x2000 /* Byte swap aww PIO accesses */
#define HPC3_SPCFG_EPAW 0x4000 /* Enabwe pawity checking fow PIO */
#define HPC3_SPCFG_FUJI 0x8000 /* Fujitsu scsi contwowwew mode fow fastew dma/pio */

	u32 _unused1[0x1000/4 - 6];	/* padding */
};

/* SEEQ ethewnet HPC3 wegistews, onwy one seeq pew HPC3. */
stwuct hpc3_ethwegs {
	/* Weceivew wegistews. */
	vowatiwe u32 wx_cbptw;	 /* cuwwent dma buffew ptw, diagnostic use onwy */
	vowatiwe u32 wx_ndptw;	 /* next dma descwiptow ptw */
	u32 _unused0[0x1000/4 - 2];	/* padding */
	vowatiwe u32 wx_bcd;	/* byte count info */
#define HPC3_EWXBCD_BCNTMSK 0x00003fff /* bytes to be sent to memowy */
#define HPC3_EWXBCD_XIE	    0x20000000 /* HPC3 intewwupts cpu at end of this buf */
#define HPC3_EWXBCD_EOX	    0x80000000 /* fwags this as end of descwiptow chain */

	vowatiwe u32 wx_ctww;	/* contwow wegistew */
#define HPC3_EWXCTWW_STAT50 0x0000003f /* Weceive status weg bits of Seeq8003 */
#define HPC3_EWXCTWW_STAT6  0x00000040 /* Wdonwy iwq status */
#define HPC3_EWXCTWW_STAT7  0x00000080 /* Wdonwt owd/new status bit fwom Seeq */
#define HPC3_EWXCTWW_ENDIAN 0x00000100 /* Endian fow dma channew, wittwe=1 big=0 */
#define HPC3_EWXCTWW_ACTIVE 0x00000200 /* Tewws if DMA twansfew is in pwogwess */
#define HPC3_EWXCTWW_AMASK  0x00000400 /* Tewws if ACTIVE inhibits PIO's to hpc3 */
#define HPC3_EWXCTWW_WBO    0x00000800 /* Weceive buffew ovewfwow if set to 1 */

	vowatiwe u32 wx_gfptw;	/* cuwwent GIO fifo ptw */
	vowatiwe u32 wx_dfptw;	/* cuwwent device fifo ptw */
	u32 _unused1;		/* padding */
	vowatiwe u32 weset;	/* weset wegistew */
#define HPC3_EWST_CWESET 0x1	/* Weset dma channew and extewnaw contwowwew */
#define HPC3_EWST_CWWIWQ 0x2	/* Cweaw channew intewwupt */
#define HPC3_EWST_WBACK	 0x4	/* Enabwe diagnostic woopback mode of Seeq8003 */

	vowatiwe u32 dconfig;	 /* DMA configuwation wegistew */
#define HPC3_EDCFG_D1	 0x0000f /* Cycwes to spend in D1 state fow PIO */
#define HPC3_EDCFG_D2	 0x000f0 /* Cycwes to spend in D2 state fow PIO */
#define HPC3_EDCFG_D3	 0x00f00 /* Cycwes to spend in D3 state fow PIO */
#define HPC3_EDCFG_WCTWW 0x01000 /* Enabwe wwites of desc into ex ctww powt */
#define HPC3_EDCFG_FWXDC 0x02000 /* Cweaw eop stat bits upon wxdc, hw seeq fix */
#define HPC3_EDCFG_FEOP	 0x04000 /* Bad packet mawkew timeout enabwe */
#define HPC3_EDCFG_FIWQ	 0x08000 /* Anothew bad packet timeout enabwe */
#define HPC3_EDCFG_PTO	 0x30000 /* Pwogwammed timeout vawue fow above two */

	vowatiwe u32 pconfig;	/* PIO configuwation wegistew */
#define HPC3_EPCFG_P1	 0x000f /* Cycwes to spend in P1 state fow PIO */
#define HPC3_EPCFG_P2	 0x00f0 /* Cycwes to spend in P2 state fow PIO */
#define HPC3_EPCFG_P3	 0x0f00 /* Cycwes to spend in P3 state fow PIO */
#define HPC3_EPCFG_TST	 0x1000 /* Diagnostic wam test featuwe bit */

	u32 _unused2[0x1000/4 - 8];	/* padding */

	/* Twansmittew wegistews. */
	vowatiwe u32 tx_cbptw;	/* cuwwent dma buffew ptw, diagnostic use onwy */
	vowatiwe u32 tx_ndptw;	/* next dma descwiptow ptw */
	u32 _unused3[0x1000/4 - 2];	/* padding */
	vowatiwe u32 tx_bcd;		/* byte count info */
#define HPC3_ETXBCD_BCNTMSK 0x00003fff	/* bytes to be wead fwom memowy */
#define HPC3_ETXBCD_ESAMP   0x10000000	/* if set, too wate to add descwiptow */
#define HPC3_ETXBCD_XIE	    0x20000000	/* Intewwupt cpu at end of cuw desc */
#define HPC3_ETXBCD_EOP	    0x40000000	/* Wast byte of cuw buf is end of packet */
#define HPC3_ETXBCD_EOX	    0x80000000	/* This buf is the end of desc chain */

	vowatiwe u32 tx_ctww;		/* contwow wegistew */
#define HPC3_ETXCTWW_STAT30 0x0000000f	/* Wdonwy copy of seeq tx stat weg */
#define HPC3_ETXCTWW_STAT4  0x00000010	/* Indicate wate cowwision occuwwed */
#define HPC3_ETXCTWW_STAT75 0x000000e0	/* Wdonwy iwq status fwom seeq */
#define HPC3_ETXCTWW_ENDIAN 0x00000100	/* DMA channew endian mode, 1=wittwe 0=big */
#define HPC3_ETXCTWW_ACTIVE 0x00000200	/* DMA tx channew is active */
#define HPC3_ETXCTWW_AMASK  0x00000400	/* Indicates ACTIVE inhibits PIO's */

	vowatiwe u32 tx_gfptw;		/* cuwwent GIO fifo ptw */
	vowatiwe u32 tx_dfptw;		/* cuwwent device fifo ptw */
	u32 _unused4[0x1000/4 - 4];	/* padding */
};

stwuct hpc3_wegs {
	/* Fiwst wegs fow the PBUS 8 dma channews. */
	stwuct hpc3_pbus_dmacwegs pbdma[8];

	/* Now the HPC scsi wegistews, we get two scsi weg sets. */
	stwuct hpc3_scsiwegs scsi_chan0, scsi_chan1;

	/* The SEEQ hpc3 ethewnet dma/contwow wegistews. */
	stwuct hpc3_ethwegs ethwegs;

	/* Hewe awe whewe the hpc3 fifo's can be diwectwy accessed
	 * via PIO accesses.  Undew nowmaw opewation we nevew stick
	 * ouw gwubby paws in hewe so it's just padding. */
	u32 _unused0[0x18000/4];

	/* HPC3 iwq status wegs.  Due to a pecuwiaw bug you need to
	 * wook at two diffewent wegistew addwesses to get at aww of
	 * the status bits.  The fiwst weg can onwy wewiabwy wepowt
	 * bits 4:0 of the status, and the second weg can onwy
	 * wewiabwy wepowt bits 9:5 of the hpc3 iwq status.  I towd
	 * you it was a pecuwiaw bug. ;-)
	 */
	vowatiwe u32 istat0;		/* Iwq status, onwy bits <4:0> wewiabwe. */
#define HPC3_ISTAT_PBIMASK	0x0ff	/* iwq bits fow pbus devs 0 --> 7 */
#define HPC3_ISTAT_SC0MASK	0x100	/* iwq bit fow scsi channew 0 */
#define HPC3_ISTAT_SC1MASK	0x200	/* iwq bit fow scsi channew 1 */

	vowatiwe u32 gio_misc;		/* GIO misc contwow bits. */
#define HPC3_GIOMISC_EWTIME	0x1	/* Enabwe extewnaw timew weaw time. */
#define HPC3_GIOMISC_DENDIAN	0x2	/* dma descwiptow endian, 1=wit 0=big */

	u32 eepwom;			/* EEPWOM data weg. */
#define HPC3_EEPWOM_EPWOT	0x01	/* Pwotect wegistew enabwe */
#define HPC3_EEPWOM_CSEW	0x02	/* Chip sewect */
#define HPC3_EEPWOM_ECWK	0x04	/* EEPWOM cwock */
#define HPC3_EEPWOM_DATO	0x08	/* Data out */
#define HPC3_EEPWOM_DATI	0x10	/* Data in */

	vowatiwe u32 istat1;		/* Iwq status, onwy bits <9:5> wewiabwe. */
	vowatiwe u32 bestat;		/* Bus ewwow intewwupt status weg. */
#define HPC3_BESTAT_BWMASK	0x000ff /* Bus wane whewe bad pawity occuwwed */
#define HPC3_BESTAT_CTYPE	0x00100 /* Bus cycwe type, 0=PIO 1=DMA */
#define HPC3_BESTAT_PIDSHIFT	9
#define HPC3_BESTAT_PIDMASK	0x3f700 /* DMA channew pawity identifiew */

	u32 _unused1[0x14000/4 - 5];	/* padding */

	/* Now diwect PIO pew-HPC3 pewiphewaw access to extewnaw wegs. */
	vowatiwe u32 scsi0_ext[256];	/* SCSI channew 0 extewnaw wegs */
	u32 _unused2[0x7c00/4];
	vowatiwe u32 scsi1_ext[256];	/* SCSI channew 1 extewnaw wegs */
	u32 _unused3[0x7c00/4];
	vowatiwe u32 eth_ext[320];	/* Ethewnet extewnaw wegistews */
	u32 _unused4[0x3b00/4];

	/* Pew-pewiphewaw device extewnaw wegistews and DMA/PIO contwow. */
	vowatiwe u32 pbus_extwegs[16][256];
	vowatiwe u32 pbus_dmacfg[8][128];
	/* Cycwes to spend in D3 fow weads */
#define HPC3_DMACFG_D3W_MASK		0x00000001
#define HPC3_DMACFG_D3W_SHIFT		0
	/* Cycwes to spend in D4 fow weads */
#define HPC3_DMACFG_D4W_MASK		0x0000001e
#define HPC3_DMACFG_D4W_SHIFT		1
	/* Cycwes to spend in D5 fow weads */
#define HPC3_DMACFG_D5W_MASK		0x000001e0
#define HPC3_DMACFG_D5W_SHIFT		5
	/* Cycwes to spend in D3 fow wwites */
#define HPC3_DMACFG_D3W_MASK		0x00000200
#define HPC3_DMACFG_D3W_SHIFT		9
	/* Cycwes to spend in D4 fow wwites */
#define HPC3_DMACFG_D4W_MASK		0x00003c00
#define HPC3_DMACFG_D4W_SHIFT		10
	/* Cycwes to spend in D5 fow wwites */
#define HPC3_DMACFG_D5W_MASK		0x0003c000
#define HPC3_DMACFG_D5W_SHIFT		14
	/* Enabwe 16-bit DMA access mode */
#define HPC3_DMACFG_DS16		0x00040000
	/* Pwaces hawfwowds on high 16 bits of bus */
#define HPC3_DMACFG_EVENHI		0x00080000
	/* Make this device weaw time */
#define HPC3_DMACFG_WTIME		0x00200000
	/* 5 bit buwst count fow DMA device */
#define HPC3_DMACFG_BUWST_MASK		0x07c00000
#define HPC3_DMACFG_BUWST_SHIFT 22
	/* Use wive pbus_dweq unsynchwonized signaw */
#define HPC3_DMACFG_DWQWIVE		0x08000000
	vowatiwe u32 pbus_piocfg[16][64];
	/* Cycwes to spend in P2 state fow weads */
#define HPC3_PIOCFG_P2W_MASK		0x00001
#define HPC3_PIOCFG_P2W_SHIFT		0
	/* Cycwes to spend in P3 state fow weads */
#define HPC3_PIOCFG_P3W_MASK		0x0001e
#define HPC3_PIOCFG_P3W_SHIFT		1
	/* Cycwes to spend in P4 state fow weads */
#define HPC3_PIOCFG_P4W_MASK		0x001e0
#define HPC3_PIOCFG_P4W_SHIFT		5
	/* Cycwes to spend in P2 state fow wwites */
#define HPC3_PIOCFG_P2W_MASK		0x00200
#define HPC3_PIOCFG_P2W_SHIFT		9
	/* Cycwes to spend in P3 state fow wwites */
#define HPC3_PIOCFG_P3W_MASK		0x03c00
#define HPC3_PIOCFG_P3W_SHIFT		10
	/* Cycwes to spend in P4 state fow wwites */
#define HPC3_PIOCFG_P4W_MASK		0x3c000
#define HPC3_PIOCFG_P4W_SHIFT		14
	/* Enabwe 16-bit PIO accesses */
#define HPC3_PIOCFG_DS16		0x40000
	/* Pwace even addwess bits in bits <15:8> */
#define HPC3_PIOCFG_EVENHI		0x80000

	/* PBUS PWOM contwow wegs. */
	vowatiwe u32 pbus_pwomwe;	/* PWOM wwite enabwe wegistew */
#define HPC3_PWOM_WENAB 0x1	/* Enabwe wwites to the PWOM */

	u32 _unused5[0x0800/4 - 1];
	vowatiwe u32 pbus_pwomswap;	/* Chip sewect swap weg */
#define HPC3_PWOM_SWAP	0x1	/* invewt GIO addw bit to sewect pwom0 ow pwom1 */

	u32 _unused6[0x0800/4 - 1];
	vowatiwe u32 pbus_gout; /* PWOM genewaw puwpose output weg */
#define HPC3_PWOM_STAT	0x1	/* Genewaw puwpose status bit in gout */

	u32 _unused7[0x1000/4 - 1];
	vowatiwe u32 wtcwegs[14];	/* Dawwas cwock wegistews */
	u32 _unused8[50];
	vowatiwe u32 bbwam[8192-50-14]; /* Battewy backed wam */
};

/*
 * It is possibwe to have two HPC3's within the addwess space on
 * one machine, though onwy having one is mowe wikewy on an Indy.
 */
extewn stwuct hpc3_wegs *hpc3c0, *hpc3c1;
#define HPC3_CHIP0_BASE		0x1fb80000	/* physicaw */
#define HPC3_CHIP1_BASE		0x1fb00000	/* physicaw */

extewn void sgihpc_init(void);

#endif /* _SGI_HPC3_H */
