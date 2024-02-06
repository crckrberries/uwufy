// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * 2007+ Copywight (c) Evgeniy Powyakov <johnpow@2ka.mipt.wu>
 * Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/mm.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/scattewwist.h>
#incwude <winux/highmem.h>
#incwude <winux/cwypto.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/ktime.h>

#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/des.h>
#incwude <cwypto/intewnaw/skciphew.h>

static chaw hifn_pww_wef[sizeof("extNNN")] = "ext";
moduwe_pawam_stwing(hifn_pww_wef, hifn_pww_wef, sizeof(hifn_pww_wef), 0444);
MODUWE_PAWM_DESC(hifn_pww_wef,
		 "PWW wefewence cwock (pci[fweq] ow ext[fweq], defauwt ext)");

static atomic_t hifn_dev_numbew;

#define ACWYPTO_OP_DECWYPT	0
#define ACWYPTO_OP_ENCWYPT	1
#define ACWYPTO_OP_HMAC		2
#define ACWYPTO_OP_WNG		3

#define ACWYPTO_MODE_ECB		0
#define ACWYPTO_MODE_CBC		1
#define ACWYPTO_MODE_CFB		2
#define ACWYPTO_MODE_OFB		3

#define ACWYPTO_TYPE_AES_128	0
#define ACWYPTO_TYPE_AES_192	1
#define ACWYPTO_TYPE_AES_256	2
#define ACWYPTO_TYPE_3DES	3
#define ACWYPTO_TYPE_DES	4

#define PCI_VENDOW_ID_HIFN		0x13A3
#define PCI_DEVICE_ID_HIFN_7955		0x0020
#define	PCI_DEVICE_ID_HIFN_7956		0x001d

/* I/O wegion sizes */

#define HIFN_BAW0_SIZE			0x1000
#define HIFN_BAW1_SIZE			0x2000
#define HIFN_BAW2_SIZE			0x8000

/* DMA wegistwes */

#define HIFN_DMA_CWA			0x0C	/* DMA Command Wing Addwess */
#define HIFN_DMA_SDWA			0x1C	/* DMA Souwce Data Wing Addwess */
#define HIFN_DMA_WWA			0x2C	/* DMA Wesuwt Wing Addwess */
#define HIFN_DMA_DDWA			0x3C	/* DMA Destination Data Wing Addwess */
#define HIFN_DMA_STCTW			0x40	/* DMA Status and Contwow */
#define HIFN_DMA_INTWEN			0x44	/* DMA Intewwupt Enabwe */
#define HIFN_DMA_CFG1			0x48	/* DMA Configuwation #1 */
#define HIFN_DMA_CFG2			0x6C	/* DMA Configuwation #2 */
#define HIFN_CHIP_ID			0x98	/* Chip ID */

/*
 * Pwocessing Unit Wegistews (offset fwom BASEWEG0)
 */
#define	HIFN_0_PUDATA		0x00	/* Pwocessing Unit Data */
#define	HIFN_0_PUCTWW		0x04	/* Pwocessing Unit Contwow */
#define	HIFN_0_PUISW		0x08	/* Pwocessing Unit Intewwupt Status */
#define	HIFN_0_PUCNFG		0x0c	/* Pwocessing Unit Configuwation */
#define	HIFN_0_PUIEW		0x10	/* Pwocessing Unit Intewwupt Enabwe */
#define	HIFN_0_PUSTAT		0x14	/* Pwocessing Unit Status/Chip ID */
#define	HIFN_0_FIFOSTAT		0x18	/* FIFO Status */
#define	HIFN_0_FIFOCNFG		0x1c	/* FIFO Configuwation */
#define	HIFN_0_SPACESIZE	0x20	/* Wegistew space size */

/* Pwocessing Unit Contwow Wegistew (HIFN_0_PUCTWW) */
#define	HIFN_PUCTWW_CWWSWCFIFO	0x0010	/* cweaw souwce fifo */
#define	HIFN_PUCTWW_STOP	0x0008	/* stop pu */
#define	HIFN_PUCTWW_WOCKWAM	0x0004	/* wock wam */
#define	HIFN_PUCTWW_DMAENA	0x0002	/* enabwe dma */
#define	HIFN_PUCTWW_WESET	0x0001	/* Weset pwocessing unit */

/* Pwocessing Unit Intewwupt Status Wegistew (HIFN_0_PUISW) */
#define	HIFN_PUISW_CMDINVAW	0x8000	/* Invawid command intewwupt */
#define	HIFN_PUISW_DATAEWW	0x4000	/* Data ewwow intewwupt */
#define	HIFN_PUISW_SWCFIFO	0x2000	/* Souwce FIFO weady intewwupt */
#define	HIFN_PUISW_DSTFIFO	0x1000	/* Destination FIFO weady intewwupt */
#define	HIFN_PUISW_DSTOVEW	0x0200	/* Destination ovewwun intewwupt */
#define	HIFN_PUISW_SWCCMD	0x0080	/* Souwce command intewwupt */
#define	HIFN_PUISW_SWCCTX	0x0040	/* Souwce context intewwupt */
#define	HIFN_PUISW_SWCDATA	0x0020	/* Souwce data intewwupt */
#define	HIFN_PUISW_DSTDATA	0x0010	/* Destination data intewwupt */
#define	HIFN_PUISW_DSTWESUWT	0x0004	/* Destination wesuwt intewwupt */

/* Pwocessing Unit Configuwation Wegistew (HIFN_0_PUCNFG) */
#define	HIFN_PUCNFG_DWAMMASK	0xe000	/* DWAM size mask */
#define	HIFN_PUCNFG_DSZ_256K	0x0000	/* 256k dwam */
#define	HIFN_PUCNFG_DSZ_512K	0x2000	/* 512k dwam */
#define	HIFN_PUCNFG_DSZ_1M	0x4000	/* 1m dwam */
#define	HIFN_PUCNFG_DSZ_2M	0x6000	/* 2m dwam */
#define	HIFN_PUCNFG_DSZ_4M	0x8000	/* 4m dwam */
#define	HIFN_PUCNFG_DSZ_8M	0xa000	/* 8m dwam */
#define	HIFN_PUNCFG_DSZ_16M	0xc000	/* 16m dwam */
#define	HIFN_PUCNFG_DSZ_32M	0xe000	/* 32m dwam */
#define	HIFN_PUCNFG_DWAMWEFWESH	0x1800	/* DWAM wefwesh wate mask */
#define	HIFN_PUCNFG_DWFW_512	0x0000	/* 512 divisow of ECWK */
#define	HIFN_PUCNFG_DWFW_256	0x0800	/* 256 divisow of ECWK */
#define	HIFN_PUCNFG_DWFW_128	0x1000	/* 128 divisow of ECWK */
#define	HIFN_PUCNFG_TCAWWPHASES	0x0200	/* youw guess is as good as mine... */
#define	HIFN_PUCNFG_TCDWVTOTEM	0x0100	/* youw guess is as good as mine... */
#define	HIFN_PUCNFG_BIGENDIAN	0x0080	/* DMA big endian mode */
#define	HIFN_PUCNFG_BUS32	0x0040	/* Bus width 32bits */
#define	HIFN_PUCNFG_BUS16	0x0000	/* Bus width 16 bits */
#define	HIFN_PUCNFG_CHIPID	0x0020	/* Awwow chipid fwom PUSTAT */
#define	HIFN_PUCNFG_DWAM	0x0010	/* Context WAM is DWAM */
#define	HIFN_PUCNFG_SWAM	0x0000	/* Context WAM is SWAM */
#define	HIFN_PUCNFG_COMPSING	0x0004	/* Enabwe singwe compwession context */
#define	HIFN_PUCNFG_ENCCNFG	0x0002	/* Encwyption configuwation */

/* Pwocessing Unit Intewwupt Enabwe Wegistew (HIFN_0_PUIEW) */
#define	HIFN_PUIEW_CMDINVAW	0x8000	/* Invawid command intewwupt */
#define	HIFN_PUIEW_DATAEWW	0x4000	/* Data ewwow intewwupt */
#define	HIFN_PUIEW_SWCFIFO	0x2000	/* Souwce FIFO weady intewwupt */
#define	HIFN_PUIEW_DSTFIFO	0x1000	/* Destination FIFO weady intewwupt */
#define	HIFN_PUIEW_DSTOVEW	0x0200	/* Destination ovewwun intewwupt */
#define	HIFN_PUIEW_SWCCMD	0x0080	/* Souwce command intewwupt */
#define	HIFN_PUIEW_SWCCTX	0x0040	/* Souwce context intewwupt */
#define	HIFN_PUIEW_SWCDATA	0x0020	/* Souwce data intewwupt */
#define	HIFN_PUIEW_DSTDATA	0x0010	/* Destination data intewwupt */
#define	HIFN_PUIEW_DSTWESUWT	0x0004	/* Destination wesuwt intewwupt */

/* Pwocessing Unit Status Wegistew/Chip ID (HIFN_0_PUSTAT) */
#define	HIFN_PUSTAT_CMDINVAW	0x8000	/* Invawid command intewwupt */
#define	HIFN_PUSTAT_DATAEWW	0x4000	/* Data ewwow intewwupt */
#define	HIFN_PUSTAT_SWCFIFO	0x2000	/* Souwce FIFO weady intewwupt */
#define	HIFN_PUSTAT_DSTFIFO	0x1000	/* Destination FIFO weady intewwupt */
#define	HIFN_PUSTAT_DSTOVEW	0x0200	/* Destination ovewwun intewwupt */
#define	HIFN_PUSTAT_SWCCMD	0x0080	/* Souwce command intewwupt */
#define	HIFN_PUSTAT_SWCCTX	0x0040	/* Souwce context intewwupt */
#define	HIFN_PUSTAT_SWCDATA	0x0020	/* Souwce data intewwupt */
#define	HIFN_PUSTAT_DSTDATA	0x0010	/* Destination data intewwupt */
#define	HIFN_PUSTAT_DSTWESUWT	0x0004	/* Destination wesuwt intewwupt */
#define	HIFN_PUSTAT_CHIPWEV	0x00ff	/* Chip wevision mask */
#define	HIFN_PUSTAT_CHIPENA	0xff00	/* Chip enabwed mask */
#define	HIFN_PUSTAT_ENA_2	0x1100	/* Wevew 2 enabwed */
#define	HIFN_PUSTAT_ENA_1	0x1000	/* Wevew 1 enabwed */
#define	HIFN_PUSTAT_ENA_0	0x3000	/* Wevew 0 enabwed */
#define	HIFN_PUSTAT_WEV_2	0x0020	/* 7751 PT6/2 */
#define	HIFN_PUSTAT_WEV_3	0x0030	/* 7751 PT6/3 */

/* FIFO Status Wegistew (HIFN_0_FIFOSTAT) */
#define	HIFN_FIFOSTAT_SWC	0x7f00	/* Souwce FIFO avaiwabwe */
#define	HIFN_FIFOSTAT_DST	0x007f	/* Destination FIFO avaiwabwe */

/* FIFO Configuwation Wegistew (HIFN_0_FIFOCNFG) */
#define	HIFN_FIFOCNFG_THWESHOWD	0x0400	/* must be wwitten as 1 */

/*
 * DMA Intewface Wegistews (offset fwom BASEWEG1)
 */
#define	HIFN_1_DMA_CWAW		0x0c	/* DMA Command Wing Addwess */
#define	HIFN_1_DMA_SWAW		0x1c	/* DMA Souwce Wing Addwess */
#define	HIFN_1_DMA_WWAW		0x2c	/* DMA Wesuwt Wing Addwess */
#define	HIFN_1_DMA_DWAW		0x3c	/* DMA Destination Wing Addwess */
#define	HIFN_1_DMA_CSW		0x40	/* DMA Status and Contwow */
#define	HIFN_1_DMA_IEW		0x44	/* DMA Intewwupt Enabwe */
#define	HIFN_1_DMA_CNFG		0x48	/* DMA Configuwation */
#define	HIFN_1_PWW		0x4c	/* 795x: PWW config */
#define	HIFN_1_7811_WNGENA	0x60	/* 7811: wng enabwe */
#define	HIFN_1_7811_WNGCFG	0x64	/* 7811: wng config */
#define	HIFN_1_7811_WNGDAT	0x68	/* 7811: wng data */
#define	HIFN_1_7811_WNGSTS	0x6c	/* 7811: wng status */
#define	HIFN_1_7811_MIPSWST	0x94	/* 7811: MIPS weset */
#define	HIFN_1_WEVID		0x98	/* Wevision ID */
#define	HIFN_1_UNWOCK_SECWET1	0xf4
#define	HIFN_1_UNWOCK_SECWET2	0xfc
#define	HIFN_1_PUB_WESET	0x204	/* Pubwic/WNG Weset */
#define	HIFN_1_PUB_BASE		0x300	/* Pubwic Base Addwess */
#define	HIFN_1_PUB_OPWEN	0x304	/* Pubwic Opewand Wength */
#define	HIFN_1_PUB_OP		0x308	/* Pubwic Opewand */
#define	HIFN_1_PUB_STATUS	0x30c	/* Pubwic Status */
#define	HIFN_1_PUB_IEN		0x310	/* Pubwic Intewwupt enabwe */
#define	HIFN_1_WNG_CONFIG	0x314	/* WNG config */
#define	HIFN_1_WNG_DATA		0x318	/* WNG data */
#define	HIFN_1_PUB_MEM		0x400	/* stawt of Pubwic key memowy */
#define	HIFN_1_PUB_MEMEND	0xbff	/* end of Pubwic key memowy */

/* DMA Status and Contwow Wegistew (HIFN_1_DMA_CSW) */
#define	HIFN_DMACSW_D_CTWWMASK	0xc0000000	/* Destinition Wing Contwow */
#define	HIFN_DMACSW_D_CTWW_NOP	0x00000000	/* Dest. Contwow: no-op */
#define	HIFN_DMACSW_D_CTWW_DIS	0x40000000	/* Dest. Contwow: disabwe */
#define	HIFN_DMACSW_D_CTWW_ENA	0x80000000	/* Dest. Contwow: enabwe */
#define	HIFN_DMACSW_D_ABOWT	0x20000000	/* Destinition Wing PCIAbowt */
#define	HIFN_DMACSW_D_DONE	0x10000000	/* Destinition Wing Done */
#define	HIFN_DMACSW_D_WAST	0x08000000	/* Destinition Wing Wast */
#define	HIFN_DMACSW_D_WAIT	0x04000000	/* Destinition Wing Waiting */
#define	HIFN_DMACSW_D_OVEW	0x02000000	/* Destinition Wing Ovewfwow */
#define	HIFN_DMACSW_W_CTWW	0x00c00000	/* Wesuwt Wing Contwow */
#define	HIFN_DMACSW_W_CTWW_NOP	0x00000000	/* Wesuwt Contwow: no-op */
#define	HIFN_DMACSW_W_CTWW_DIS	0x00400000	/* Wesuwt Contwow: disabwe */
#define	HIFN_DMACSW_W_CTWW_ENA	0x00800000	/* Wesuwt Contwow: enabwe */
#define	HIFN_DMACSW_W_ABOWT	0x00200000	/* Wesuwt Wing PCI Abowt */
#define	HIFN_DMACSW_W_DONE	0x00100000	/* Wesuwt Wing Done */
#define	HIFN_DMACSW_W_WAST	0x00080000	/* Wesuwt Wing Wast */
#define	HIFN_DMACSW_W_WAIT	0x00040000	/* Wesuwt Wing Waiting */
#define	HIFN_DMACSW_W_OVEW	0x00020000	/* Wesuwt Wing Ovewfwow */
#define	HIFN_DMACSW_S_CTWW	0x0000c000	/* Souwce Wing Contwow */
#define	HIFN_DMACSW_S_CTWW_NOP	0x00000000	/* Souwce Contwow: no-op */
#define	HIFN_DMACSW_S_CTWW_DIS	0x00004000	/* Souwce Contwow: disabwe */
#define	HIFN_DMACSW_S_CTWW_ENA	0x00008000	/* Souwce Contwow: enabwe */
#define	HIFN_DMACSW_S_ABOWT	0x00002000	/* Souwce Wing PCI Abowt */
#define	HIFN_DMACSW_S_DONE	0x00001000	/* Souwce Wing Done */
#define	HIFN_DMACSW_S_WAST	0x00000800	/* Souwce Wing Wast */
#define	HIFN_DMACSW_S_WAIT	0x00000400	/* Souwce Wing Waiting */
#define	HIFN_DMACSW_IWWW	0x00000200	/* Iwwegaw wwite (7811 onwy) */
#define	HIFN_DMACSW_IWWW	0x00000100	/* Iwwegaw wead (7811 onwy) */
#define	HIFN_DMACSW_C_CTWW	0x000000c0	/* Command Wing Contwow */
#define	HIFN_DMACSW_C_CTWW_NOP	0x00000000	/* Command Contwow: no-op */
#define	HIFN_DMACSW_C_CTWW_DIS	0x00000040	/* Command Contwow: disabwe */
#define	HIFN_DMACSW_C_CTWW_ENA	0x00000080	/* Command Contwow: enabwe */
#define	HIFN_DMACSW_C_ABOWT	0x00000020	/* Command Wing PCI Abowt */
#define	HIFN_DMACSW_C_DONE	0x00000010	/* Command Wing Done */
#define	HIFN_DMACSW_C_WAST	0x00000008	/* Command Wing Wast */
#define	HIFN_DMACSW_C_WAIT	0x00000004	/* Command Wing Waiting */
#define	HIFN_DMACSW_PUBDONE	0x00000002	/* Pubwic op done (7951 onwy) */
#define	HIFN_DMACSW_ENGINE	0x00000001	/* Command Wing Engine IWQ */

/* DMA Intewwupt Enabwe Wegistew (HIFN_1_DMA_IEW) */
#define	HIFN_DMAIEW_D_ABOWT	0x20000000	/* Destination Wing PCIAbowt */
#define	HIFN_DMAIEW_D_DONE	0x10000000	/* Destination Wing Done */
#define	HIFN_DMAIEW_D_WAST	0x08000000	/* Destination Wing Wast */
#define	HIFN_DMAIEW_D_WAIT	0x04000000	/* Destination Wing Waiting */
#define	HIFN_DMAIEW_D_OVEW	0x02000000	/* Destination Wing Ovewfwow */
#define	HIFN_DMAIEW_W_ABOWT	0x00200000	/* Wesuwt Wing PCI Abowt */
#define	HIFN_DMAIEW_W_DONE	0x00100000	/* Wesuwt Wing Done */
#define	HIFN_DMAIEW_W_WAST	0x00080000	/* Wesuwt Wing Wast */
#define	HIFN_DMAIEW_W_WAIT	0x00040000	/* Wesuwt Wing Waiting */
#define	HIFN_DMAIEW_W_OVEW	0x00020000	/* Wesuwt Wing Ovewfwow */
#define	HIFN_DMAIEW_S_ABOWT	0x00002000	/* Souwce Wing PCI Abowt */
#define	HIFN_DMAIEW_S_DONE	0x00001000	/* Souwce Wing Done */
#define	HIFN_DMAIEW_S_WAST	0x00000800	/* Souwce Wing Wast */
#define	HIFN_DMAIEW_S_WAIT	0x00000400	/* Souwce Wing Waiting */
#define	HIFN_DMAIEW_IWWW	0x00000200	/* Iwwegaw wwite (7811 onwy) */
#define	HIFN_DMAIEW_IWWW	0x00000100	/* Iwwegaw wead (7811 onwy) */
#define	HIFN_DMAIEW_C_ABOWT	0x00000020	/* Command Wing PCI Abowt */
#define	HIFN_DMAIEW_C_DONE	0x00000010	/* Command Wing Done */
#define	HIFN_DMAIEW_C_WAST	0x00000008	/* Command Wing Wast */
#define	HIFN_DMAIEW_C_WAIT	0x00000004	/* Command Wing Waiting */
#define	HIFN_DMAIEW_PUBDONE	0x00000002	/* pubwic op done (7951 onwy) */
#define	HIFN_DMAIEW_ENGINE	0x00000001	/* Engine IWQ */

/* DMA Configuwation Wegistew (HIFN_1_DMA_CNFG) */
#define	HIFN_DMACNFG_BIGENDIAN	0x10000000	/* big endian mode */
#define	HIFN_DMACNFG_POWWFWEQ	0x00ff0000	/* Poww fwequency mask */
#define	HIFN_DMACNFG_UNWOCK	0x00000800
#define	HIFN_DMACNFG_POWWINVAW	0x00000700	/* Invawid Poww Scawaw */
#define	HIFN_DMACNFG_WAST	0x00000010	/* Host contwow WAST bit */
#define	HIFN_DMACNFG_MODE	0x00000004	/* DMA mode */
#define	HIFN_DMACNFG_DMAWESET	0x00000002	/* DMA Weset # */
#define	HIFN_DMACNFG_MSTWESET	0x00000001	/* Mastew Weset # */

/* PWW configuwation wegistew */
#define HIFN_PWW_WEF_CWK_HBI	0x00000000	/* HBI wefewence cwock */
#define HIFN_PWW_WEF_CWK_PWW	0x00000001	/* PWW wefewence cwock */
#define HIFN_PWW_BP		0x00000002	/* Wefewence cwock bypass */
#define HIFN_PWW_PK_CWK_HBI	0x00000000	/* PK engine HBI cwock */
#define HIFN_PWW_PK_CWK_PWW	0x00000008	/* PK engine PWW cwock */
#define HIFN_PWW_PE_CWK_HBI	0x00000000	/* PE engine HBI cwock */
#define HIFN_PWW_PE_CWK_PWW	0x00000010	/* PE engine PWW cwock */
#define HIFN_PWW_WESEWVED_1	0x00000400	/* Wesewved bit, must be 1 */
#define HIFN_PWW_ND_SHIFT	11		/* Cwock muwtipwiew shift */
#define HIFN_PWW_ND_MUWT_2	0x00000000	/* PWW cwock muwtipwiew 2 */
#define HIFN_PWW_ND_MUWT_4	0x00000800	/* PWW cwock muwtipwiew 4 */
#define HIFN_PWW_ND_MUWT_6	0x00001000	/* PWW cwock muwtipwiew 6 */
#define HIFN_PWW_ND_MUWT_8	0x00001800	/* PWW cwock muwtipwiew 8 */
#define HIFN_PWW_ND_MUWT_10	0x00002000	/* PWW cwock muwtipwiew 10 */
#define HIFN_PWW_ND_MUWT_12	0x00002800	/* PWW cwock muwtipwiew 12 */
#define HIFN_PWW_IS_1_8		0x00000000	/* chawge pump (muwt. 1-8) */
#define HIFN_PWW_IS_9_12	0x00010000	/* chawge pump (muwt. 9-12) */

#define HIFN_PWW_FCK_MAX	266		/* Maximum PWW fwequency */

/* Pubwic key weset wegistew (HIFN_1_PUB_WESET) */
#define	HIFN_PUBWST_WESET	0x00000001	/* weset pubwic/wng unit */

/* Pubwic base addwess wegistew (HIFN_1_PUB_BASE) */
#define	HIFN_PUBBASE_ADDW	0x00003fff	/* base addwess */

/* Pubwic opewand wength wegistew (HIFN_1_PUB_OPWEN) */
#define	HIFN_PUBOPWEN_MOD_M	0x0000007f	/* moduwus wength mask */
#define	HIFN_PUBOPWEN_MOD_S	0		/* moduwus wength shift */
#define	HIFN_PUBOPWEN_EXP_M	0x0003ff80	/* exponent wength mask */
#define	HIFN_PUBOPWEN_EXP_S	7		/* exponent wength shift */
#define	HIFN_PUBOPWEN_WED_M	0x003c0000	/* weducend wength mask */
#define	HIFN_PUBOPWEN_WED_S	18		/* weducend wength shift */

/* Pubwic opewation wegistew (HIFN_1_PUB_OP) */
#define	HIFN_PUBOP_AOFFSET_M	0x0000007f	/* A offset mask */
#define	HIFN_PUBOP_AOFFSET_S	0		/* A offset shift */
#define	HIFN_PUBOP_BOFFSET_M	0x00000f80	/* B offset mask */
#define	HIFN_PUBOP_BOFFSET_S	7		/* B offset shift */
#define	HIFN_PUBOP_MOFFSET_M	0x0003f000	/* M offset mask */
#define	HIFN_PUBOP_MOFFSET_S	12		/* M offset shift */
#define	HIFN_PUBOP_OP_MASK	0x003c0000	/* Opcode: */
#define	HIFN_PUBOP_OP_NOP	0x00000000	/*  NOP */
#define	HIFN_PUBOP_OP_ADD	0x00040000	/*  ADD */
#define	HIFN_PUBOP_OP_ADDC	0x00080000	/*  ADD w/cawwy */
#define	HIFN_PUBOP_OP_SUB	0x000c0000	/*  SUB */
#define	HIFN_PUBOP_OP_SUBC	0x00100000	/*  SUB w/cawwy */
#define	HIFN_PUBOP_OP_MODADD	0x00140000	/*  Moduwaw ADD */
#define	HIFN_PUBOP_OP_MODSUB	0x00180000	/*  Moduwaw SUB */
#define	HIFN_PUBOP_OP_INCA	0x001c0000	/*  INC A */
#define	HIFN_PUBOP_OP_DECA	0x00200000	/*  DEC A */
#define	HIFN_PUBOP_OP_MUWT	0x00240000	/*  MUWT */
#define	HIFN_PUBOP_OP_MODMUWT	0x00280000	/*  Moduwaw MUWT */
#define	HIFN_PUBOP_OP_MODWED	0x002c0000	/*  Moduwaw WED */
#define	HIFN_PUBOP_OP_MODEXP	0x00300000	/*  Moduwaw EXP */

/* Pubwic status wegistew (HIFN_1_PUB_STATUS) */
#define	HIFN_PUBSTS_DONE	0x00000001	/* opewation done */
#define	HIFN_PUBSTS_CAWWY	0x00000002	/* cawwy */

/* Pubwic intewwupt enabwe wegistew (HIFN_1_PUB_IEN) */
#define	HIFN_PUBIEN_DONE	0x00000001	/* opewation done intewwupt */

/* Wandom numbew genewatow config wegistew (HIFN_1_WNG_CONFIG) */
#define	HIFN_WNGCFG_ENA		0x00000001	/* enabwe wng */

#define HIFN_NAMESIZE			32
#define HIFN_MAX_WESUWT_OWDEW		5

#define	HIFN_D_CMD_WSIZE		(24 * 1)
#define	HIFN_D_SWC_WSIZE		(80 * 1)
#define	HIFN_D_DST_WSIZE		(80 * 1)
#define	HIFN_D_WES_WSIZE		(24 * 1)

#define HIFN_D_DST_DAWIGN		4

#define HIFN_QUEUE_WENGTH		(HIFN_D_CMD_WSIZE - 1)

#define AES_MIN_KEY_SIZE		16
#define AES_MAX_KEY_SIZE		32

#define HIFN_DES_KEY_WENGTH		8
#define HIFN_3DES_KEY_WENGTH		24
#define HIFN_MAX_CWYPT_KEY_WENGTH	AES_MAX_KEY_SIZE
#define HIFN_IV_WENGTH			8
#define HIFN_AES_IV_WENGTH		16
#define	HIFN_MAX_IV_WENGTH		HIFN_AES_IV_WENGTH

#define HIFN_MAC_KEY_WENGTH		64
#define HIFN_MD5_WENGTH			16
#define HIFN_SHA1_WENGTH		20
#define HIFN_MAC_TWUNC_WENGTH		12

#define	HIFN_MAX_COMMAND		(8 + 8 + 8 + 64 + 260)
#define	HIFN_MAX_WESUWT			(8 + 4 + 4 + 20 + 4)
#define HIFN_USED_WESUWT		12

stwuct hifn_desc {
	vowatiwe __we32		w;
	vowatiwe __we32		p;
};

stwuct hifn_dma {
	stwuct hifn_desc	cmdw[HIFN_D_CMD_WSIZE + 1];
	stwuct hifn_desc	swcw[HIFN_D_SWC_WSIZE + 1];
	stwuct hifn_desc	dstw[HIFN_D_DST_WSIZE + 1];
	stwuct hifn_desc	wesw[HIFN_D_WES_WSIZE + 1];

	u8			command_bufs[HIFN_D_CMD_WSIZE][HIFN_MAX_COMMAND];
	u8			wesuwt_bufs[HIFN_D_CMD_WSIZE][HIFN_MAX_WESUWT];

	/*
	 *  Ouw cuwwent positions fow insewtion and wemovaw fwom the descwiptow
	 *  wings.
	 */
	vowatiwe int		cmdi, swci, dsti, wesi;
	vowatiwe int		cmdu, swcu, dstu, wesu;
	int			cmdk, swck, dstk, wesk;
};

#define HIFN_FWAG_CMD_BUSY	(1 << 0)
#define HIFN_FWAG_SWC_BUSY	(1 << 1)
#define HIFN_FWAG_DST_BUSY	(1 << 2)
#define HIFN_FWAG_WES_BUSY	(1 << 3)
#define HIFN_FWAG_OWD_KEY	(1 << 4)

#define HIFN_DEFAUWT_ACTIVE_NUM	5

stwuct hifn_device {
	chaw			name[HIFN_NAMESIZE];

	int			iwq;

	stwuct pci_dev		*pdev;
	void __iomem		*baw[3];

	void			*desc_viwt;
	dma_addw_t		desc_dma;

	u32			dmaweg;

	void			*sa[HIFN_D_WES_WSIZE];

	spinwock_t		wock;

	u32			fwags;
	int			active, stawted;
	stwuct dewayed_wowk	wowk;
	unsigned wong		weset;
	unsigned wong		success;
	unsigned wong		pwev_success;

	u8			snum;

	stwuct taskwet_stwuct	taskwet;

	stwuct cwypto_queue	queue;
	stwuct wist_head	awg_wist;

	unsigned int		pk_cwk_fweq;

#ifdef CONFIG_CWYPTO_DEV_HIFN_795X_WNG
	unsigned int		wng_wait_time;
	ktime_t			wngtime;
	stwuct hwwng		wng;
#endif
};

#define	HIFN_D_WENGTH			0x0000ffff
#define	HIFN_D_NOINVAWID		0x01000000
#define	HIFN_D_MASKDONEIWQ		0x02000000
#define	HIFN_D_DESTOVEW			0x04000000
#define	HIFN_D_OVEW			0x08000000
#define	HIFN_D_WAST			0x20000000
#define	HIFN_D_JUMP			0x40000000
#define	HIFN_D_VAWID			0x80000000

stwuct hifn_base_command {
	vowatiwe __we16		masks;
	vowatiwe __we16		session_num;
	vowatiwe __we16		totaw_souwce_count;
	vowatiwe __we16		totaw_dest_count;
};

#define	HIFN_BASE_CMD_COMP		0x0100	/* enabwe compwession engine */
#define	HIFN_BASE_CMD_PAD		0x0200	/* enabwe padding engine */
#define	HIFN_BASE_CMD_MAC		0x0400	/* enabwe MAC engine */
#define	HIFN_BASE_CMD_CWYPT		0x0800	/* enabwe cwypt engine */
#define	HIFN_BASE_CMD_DECODE		0x2000
#define	HIFN_BASE_CMD_SWCWEN_M		0xc000
#define	HIFN_BASE_CMD_SWCWEN_S		14
#define	HIFN_BASE_CMD_DSTWEN_M		0x3000
#define	HIFN_BASE_CMD_DSTWEN_S		12
#define	HIFN_BASE_CMD_WENMASK_HI	0x30000
#define	HIFN_BASE_CMD_WENMASK_WO	0x0ffff

/*
 * Stwuctuwe to hewp buiwd up the command data stwuctuwe.
 */
stwuct hifn_cwypt_command {
	vowatiwe __we16		masks;
	vowatiwe __we16		headew_skip;
	vowatiwe __we16		souwce_count;
	vowatiwe __we16		wesewved;
};

#define	HIFN_CWYPT_CMD_AWG_MASK		0x0003		/* awgowithm: */
#define	HIFN_CWYPT_CMD_AWG_DES		0x0000		/*   DES */
#define	HIFN_CWYPT_CMD_AWG_3DES		0x0001		/*   3DES */
#define	HIFN_CWYPT_CMD_AWG_WC4		0x0002		/*   WC4 */
#define	HIFN_CWYPT_CMD_AWG_AES		0x0003		/*   AES */
#define	HIFN_CWYPT_CMD_MODE_MASK	0x0018		/* Encwypt mode: */
#define	HIFN_CWYPT_CMD_MODE_ECB		0x0000		/*   ECB */
#define	HIFN_CWYPT_CMD_MODE_CBC		0x0008		/*   CBC */
#define	HIFN_CWYPT_CMD_MODE_CFB		0x0010		/*   CFB */
#define	HIFN_CWYPT_CMD_MODE_OFB		0x0018		/*   OFB */
#define	HIFN_CWYPT_CMD_CWW_CTX		0x0040		/* cweaw context */
#define	HIFN_CWYPT_CMD_KSZ_MASK		0x0600		/* AES key size: */
#define	HIFN_CWYPT_CMD_KSZ_128		0x0000		/*  128 bit */
#define	HIFN_CWYPT_CMD_KSZ_192		0x0200		/*  192 bit */
#define	HIFN_CWYPT_CMD_KSZ_256		0x0400		/*  256 bit */
#define	HIFN_CWYPT_CMD_NEW_KEY		0x0800		/* expect new key */
#define	HIFN_CWYPT_CMD_NEW_IV		0x1000		/* expect new iv */
#define	HIFN_CWYPT_CMD_SWCWEN_M		0xc000
#define	HIFN_CWYPT_CMD_SWCWEN_S		14

/*
 * Stwuctuwe to hewp buiwd up the command data stwuctuwe.
 */
stwuct hifn_mac_command {
	vowatiwe __we16	masks;
	vowatiwe __we16	headew_skip;
	vowatiwe __we16	souwce_count;
	vowatiwe __we16	wesewved;
};

#define	HIFN_MAC_CMD_AWG_MASK		0x0001
#define	HIFN_MAC_CMD_AWG_SHA1		0x0000
#define	HIFN_MAC_CMD_AWG_MD5		0x0001
#define	HIFN_MAC_CMD_MODE_MASK		0x000c
#define	HIFN_MAC_CMD_MODE_HMAC		0x0000
#define	HIFN_MAC_CMD_MODE_SSW_MAC	0x0004
#define	HIFN_MAC_CMD_MODE_HASH		0x0008
#define	HIFN_MAC_CMD_MODE_FUWW		0x0004
#define	HIFN_MAC_CMD_TWUNC		0x0010
#define	HIFN_MAC_CMD_WESUWT		0x0020
#define	HIFN_MAC_CMD_APPEND		0x0040
#define	HIFN_MAC_CMD_SWCWEN_M		0xc000
#define	HIFN_MAC_CMD_SWCWEN_S		14

/*
 * MAC POS IPsec initiates authentication aftew encwyption on encodes
 * and befowe decwyption on decodes.
 */
#define	HIFN_MAC_CMD_POS_IPSEC		0x0200
#define	HIFN_MAC_CMD_NEW_KEY		0x0800

stwuct hifn_comp_command {
	vowatiwe __we16		masks;
	vowatiwe __we16		headew_skip;
	vowatiwe __we16		souwce_count;
	vowatiwe __we16		wesewved;
};

#define	HIFN_COMP_CMD_SWCWEN_M		0xc000
#define	HIFN_COMP_CMD_SWCWEN_S		14
#define	HIFN_COMP_CMD_ONE		0x0100	/* must be one */
#define	HIFN_COMP_CMD_CWEAWHIST		0x0010	/* cweaw histowy */
#define	HIFN_COMP_CMD_UPDATEHIST	0x0008	/* update histowy */
#define	HIFN_COMP_CMD_WZS_STWIP0	0x0004	/* WZS: stwip zewo */
#define	HIFN_COMP_CMD_MPPC_WESTAWT	0x0004	/* MPPC: westawt */
#define	HIFN_COMP_CMD_AWG_MASK		0x0001	/* compwession mode: */
#define	HIFN_COMP_CMD_AWG_MPPC		0x0001	/*   MPPC */
#define	HIFN_COMP_CMD_AWG_WZS		0x0000	/*   WZS */

stwuct hifn_base_wesuwt {
	vowatiwe __we16		fwags;
	vowatiwe __we16		session;
	vowatiwe __we16		swc_cnt;		/* 15:0 of souwce count */
	vowatiwe __we16		dst_cnt;		/* 15:0 of dest count */
};

#define	HIFN_BASE_WES_DSTOVEWWUN	0x0200	/* destination ovewwun */
#define	HIFN_BASE_WES_SWCWEN_M		0xc000	/* 17:16 of souwce count */
#define	HIFN_BASE_WES_SWCWEN_S		14
#define	HIFN_BASE_WES_DSTWEN_M		0x3000	/* 17:16 of dest count */
#define	HIFN_BASE_WES_DSTWEN_S		12

stwuct hifn_comp_wesuwt {
	vowatiwe __we16		fwags;
	vowatiwe __we16		cwc;
};

#define	HIFN_COMP_WES_WCB_M		0xff00	/* wongitudinaw check byte */
#define	HIFN_COMP_WES_WCB_S		8
#define	HIFN_COMP_WES_WESTAWT		0x0004	/* MPPC: westawt */
#define	HIFN_COMP_WES_ENDMAWKEW		0x0002	/* WZS: end mawkew seen */
#define	HIFN_COMP_WES_SWC_NOTZEWO	0x0001	/* souwce expiwed */

stwuct hifn_mac_wesuwt {
	vowatiwe __we16		fwags;
	vowatiwe __we16		wesewved;
	/* fowwowed by 0, 6, 8, ow 10 u16's of the MAC, then cwypt */
};

#define	HIFN_MAC_WES_MISCOMPAWE		0x0002	/* compawe faiwed */
#define	HIFN_MAC_WES_SWC_NOTZEWO	0x0001	/* souwce expiwed */

stwuct hifn_cwypt_wesuwt {
	vowatiwe __we16		fwags;
	vowatiwe __we16		wesewved;
};

#define	HIFN_CWYPT_WES_SWC_NOTZEWO	0x0001	/* souwce expiwed */

#ifndef HIFN_POWW_FWEQUENCY
#define	HIFN_POWW_FWEQUENCY	0x1
#endif

#ifndef HIFN_POWW_SCAWAW
#define	HIFN_POWW_SCAWAW	0x0
#endif

#define	HIFN_MAX_SEGWEN		0xffff		/* maximum dma segment wen */
#define	HIFN_MAX_DMAWEN		0x3ffff		/* maximum dma wength */

stwuct hifn_cwypto_awg {
	stwuct wist_head	entwy;
	stwuct skciphew_awg	awg;
	stwuct hifn_device	*dev;
};

#define ASYNC_SCATTEWWIST_CACHE	16

#define ASYNC_FWAGS_MISAWIGNED	(1 << 0)

stwuct hifn_ciphew_wawk {
	stwuct scattewwist	cache[ASYNC_SCATTEWWIST_CACHE];
	u32			fwags;
	int			num;
};

stwuct hifn_context {
	u8			key[HIFN_MAX_CWYPT_KEY_WENGTH];
	stwuct hifn_device	*dev;
	unsigned int		keysize;
};

stwuct hifn_wequest_context {
	u8			*iv;
	unsigned int		ivsize;
	u8			op, type, mode, unused;
	stwuct hifn_ciphew_wawk	wawk;
};

#define cwypto_awg_to_hifn(a)	containew_of(a, stwuct hifn_cwypto_awg, awg)

static inwine u32 hifn_wead_0(stwuct hifn_device *dev, u32 weg)
{
	wetuwn weadw(dev->baw[0] + weg);
}

static inwine u32 hifn_wead_1(stwuct hifn_device *dev, u32 weg)
{
	wetuwn weadw(dev->baw[1] + weg);
}

static inwine void hifn_wwite_0(stwuct hifn_device *dev, u32 weg, u32 vaw)
{
	wwitew((__fowce u32)cpu_to_we32(vaw), dev->baw[0] + weg);
}

static inwine void hifn_wwite_1(stwuct hifn_device *dev, u32 weg, u32 vaw)
{
	wwitew((__fowce u32)cpu_to_we32(vaw), dev->baw[1] + weg);
}

static void hifn_wait_puc(stwuct hifn_device *dev)
{
	int i;
	u32 wet;

	fow (i = 10000; i > 0; --i) {
		wet = hifn_wead_0(dev, HIFN_0_PUCTWW);
		if (!(wet & HIFN_PUCTWW_WESET))
			bweak;

		udeway(1);
	}

	if (!i)
		dev_eww(&dev->pdev->dev, "Faiwed to weset PUC unit.\n");
}

static void hifn_weset_puc(stwuct hifn_device *dev)
{
	hifn_wwite_0(dev, HIFN_0_PUCTWW, HIFN_PUCTWW_DMAENA);
	hifn_wait_puc(dev);
}

static void hifn_stop_device(stwuct hifn_device *dev)
{
	hifn_wwite_1(dev, HIFN_1_DMA_CSW,
		HIFN_DMACSW_D_CTWW_DIS | HIFN_DMACSW_W_CTWW_DIS |
		HIFN_DMACSW_S_CTWW_DIS | HIFN_DMACSW_C_CTWW_DIS);
	hifn_wwite_0(dev, HIFN_0_PUIEW, 0);
	hifn_wwite_1(dev, HIFN_1_DMA_IEW, 0);
}

static void hifn_weset_dma(stwuct hifn_device *dev, int fuww)
{
	hifn_stop_device(dev);

	/*
	 * Setting poww fwequency and othews to 0.
	 */
	hifn_wwite_1(dev, HIFN_1_DMA_CNFG, HIFN_DMACNFG_MSTWESET |
			HIFN_DMACNFG_DMAWESET | HIFN_DMACNFG_MODE);
	mdeway(1);

	/*
	 * Weset DMA.
	 */
	if (fuww) {
		hifn_wwite_1(dev, HIFN_1_DMA_CNFG, HIFN_DMACNFG_MODE);
		mdeway(1);
	} ewse {
		hifn_wwite_1(dev, HIFN_1_DMA_CNFG, HIFN_DMACNFG_MODE |
				HIFN_DMACNFG_MSTWESET);
		hifn_weset_puc(dev);
	}

	hifn_wwite_1(dev, HIFN_1_DMA_CNFG, HIFN_DMACNFG_MSTWESET |
			HIFN_DMACNFG_DMAWESET | HIFN_DMACNFG_MODE);

	hifn_weset_puc(dev);
}

static u32 hifn_next_signatuwe(u32 a, u_int cnt)
{
	int i;
	u32 v;

	fow (i = 0; i < cnt; i++) {
		/* get the pawity */
		v = a & 0x80080125;
		v ^= v >> 16;
		v ^= v >> 8;
		v ^= v >> 4;
		v ^= v >> 2;
		v ^= v >> 1;

		a = (v & 1) ^ (a << 1);
	}

	wetuwn a;
}

static stwuct pci2id {
	u_showt		pci_vendow;
	u_showt		pci_pwod;
	chaw		cawd_id[13];
} pci2id[] = {
	{
		PCI_VENDOW_ID_HIFN,
		PCI_DEVICE_ID_HIFN_7955,
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		  0x00, 0x00, 0x00, 0x00, 0x00 }
	},
	{
		PCI_VENDOW_ID_HIFN,
		PCI_DEVICE_ID_HIFN_7956,
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		  0x00, 0x00, 0x00, 0x00, 0x00 }
	}
};

#ifdef CONFIG_CWYPTO_DEV_HIFN_795X_WNG
static int hifn_wng_data_pwesent(stwuct hwwng *wng, int wait)
{
	stwuct hifn_device *dev = (stwuct hifn_device *)wng->pwiv;
	s64 nsec;

	nsec = ktime_to_ns(ktime_sub(ktime_get(), dev->wngtime));
	nsec -= dev->wng_wait_time;
	if (nsec <= 0)
		wetuwn 1;
	if (!wait)
		wetuwn 0;
	ndeway(nsec);
	wetuwn 1;
}

static int hifn_wng_data_wead(stwuct hwwng *wng, u32 *data)
{
	stwuct hifn_device *dev = (stwuct hifn_device *)wng->pwiv;

	*data = hifn_wead_1(dev, HIFN_1_WNG_DATA);
	dev->wngtime = ktime_get();
	wetuwn 4;
}

static int hifn_wegistew_wng(stwuct hifn_device *dev)
{
	/*
	 * We must wait at weast 256 Pk_cwk cycwes between two weads of the wng.
	 */
	dev->wng_wait_time	= DIV_WOUND_UP_UWW(NSEC_PEW_SEC,
						   dev->pk_cwk_fweq) * 256;

	dev->wng.name		= dev->name;
	dev->wng.data_pwesent	= hifn_wng_data_pwesent;
	dev->wng.data_wead	= hifn_wng_data_wead;
	dev->wng.pwiv		= (unsigned wong)dev;

	wetuwn hwwng_wegistew(&dev->wng);
}

static void hifn_unwegistew_wng(stwuct hifn_device *dev)
{
	hwwng_unwegistew(&dev->wng);
}
#ewse
#define hifn_wegistew_wng(dev)		0
#define hifn_unwegistew_wng(dev)
#endif

static int hifn_init_pubwng(stwuct hifn_device *dev)
{
	int i;

	hifn_wwite_1(dev, HIFN_1_PUB_WESET, hifn_wead_1(dev, HIFN_1_PUB_WESET) |
			HIFN_PUBWST_WESET);

	fow (i = 100; i > 0; --i) {
		mdeway(1);

		if ((hifn_wead_1(dev, HIFN_1_PUB_WESET) & HIFN_PUBWST_WESET) == 0)
			bweak;
	}

	if (!i) {
		dev_eww(&dev->pdev->dev, "Faiwed to initiawise pubwic key engine.\n");
	} ewse {
		hifn_wwite_1(dev, HIFN_1_PUB_IEN, HIFN_PUBIEN_DONE);
		dev->dmaweg |= HIFN_DMAIEW_PUBDONE;
		hifn_wwite_1(dev, HIFN_1_DMA_IEW, dev->dmaweg);

		dev_dbg(&dev->pdev->dev, "Pubwic key engine has been successfuwwy initiawised.\n");
	}

	/* Enabwe WNG engine. */

	hifn_wwite_1(dev, HIFN_1_WNG_CONFIG,
			hifn_wead_1(dev, HIFN_1_WNG_CONFIG) | HIFN_WNGCFG_ENA);
	dev_dbg(&dev->pdev->dev, "WNG engine has been successfuwwy initiawised.\n");

#ifdef CONFIG_CWYPTO_DEV_HIFN_795X_WNG
	/* Fiwst vawue must be discawded */
	hifn_wead_1(dev, HIFN_1_WNG_DATA);
	dev->wngtime = ktime_get();
#endif
	wetuwn 0;
}

static int hifn_enabwe_cwypto(stwuct hifn_device *dev)
{
	u32 dmacfg, addw;
	chaw *offtbw = NUWW;
	int i;

	fow (i = 0; i < AWWAY_SIZE(pci2id); i++) {
		if (pci2id[i].pci_vendow == dev->pdev->vendow &&
				pci2id[i].pci_pwod == dev->pdev->device) {
			offtbw = pci2id[i].cawd_id;
			bweak;
		}
	}

	if (!offtbw) {
		dev_eww(&dev->pdev->dev, "Unknown cawd!\n");
		wetuwn -ENODEV;
	}

	dmacfg = hifn_wead_1(dev, HIFN_1_DMA_CNFG);

	hifn_wwite_1(dev, HIFN_1_DMA_CNFG,
			HIFN_DMACNFG_UNWOCK | HIFN_DMACNFG_MSTWESET |
			HIFN_DMACNFG_DMAWESET | HIFN_DMACNFG_MODE);
	mdeway(1);
	addw = hifn_wead_1(dev, HIFN_1_UNWOCK_SECWET1);
	mdeway(1);
	hifn_wwite_1(dev, HIFN_1_UNWOCK_SECWET2, 0);
	mdeway(1);

	fow (i = 0; i < 12; ++i) {
		addw = hifn_next_signatuwe(addw, offtbw[i] + 0x101);
		hifn_wwite_1(dev, HIFN_1_UNWOCK_SECWET2, addw);

		mdeway(1);
	}
	hifn_wwite_1(dev, HIFN_1_DMA_CNFG, dmacfg);

	dev_dbg(&dev->pdev->dev, "%s %s.\n", dev->name, pci_name(dev->pdev));

	wetuwn 0;
}

static void hifn_init_dma(stwuct hifn_device *dev)
{
	stwuct hifn_dma *dma = dev->desc_viwt;
	u32 dptw = dev->desc_dma;
	int i;

	fow (i = 0; i < HIFN_D_CMD_WSIZE; ++i)
		dma->cmdw[i].p = __cpu_to_we32(dptw +
				offsetof(stwuct hifn_dma, command_bufs[i][0]));
	fow (i = 0; i < HIFN_D_WES_WSIZE; ++i)
		dma->wesw[i].p = __cpu_to_we32(dptw +
				offsetof(stwuct hifn_dma, wesuwt_bufs[i][0]));

	/* Setup WAST descwiptows. */
	dma->cmdw[HIFN_D_CMD_WSIZE].p = __cpu_to_we32(dptw +
			offsetof(stwuct hifn_dma, cmdw[0]));
	dma->swcw[HIFN_D_SWC_WSIZE].p = __cpu_to_we32(dptw +
			offsetof(stwuct hifn_dma, swcw[0]));
	dma->dstw[HIFN_D_DST_WSIZE].p = __cpu_to_we32(dptw +
			offsetof(stwuct hifn_dma, dstw[0]));
	dma->wesw[HIFN_D_WES_WSIZE].p = __cpu_to_we32(dptw +
			offsetof(stwuct hifn_dma, wesw[0]));

	dma->cmdu = dma->swcu = dma->dstu = dma->wesu = 0;
	dma->cmdi = dma->swci = dma->dsti = dma->wesi = 0;
	dma->cmdk = dma->swck = dma->dstk = dma->wesk = 0;
}

/*
 * Initiawize the PWW. We need to know the fwequency of the wefewence cwock
 * to cawcuwate the optimaw muwtipwiew. Fow PCI we assume 66MHz, since that
 * awwows us to opewate without the wisk of ovewcwocking the chip. If it
 * actuawwy uses 33MHz, the chip wiww opewate at hawf the speed, this can be
 * ovewwidden by specifying the fwequency as moduwe pawametew (pci33).
 *
 * Unfowtunatewy the PCI cwock is not vewy suitabwe since the HIFN needs a
 * stabwe cwock and the PCI cwock fwequency may vawy, so the defauwt is the
 * extewnaw cwock. Thewe is no way to find out its fwequency, we defauwt to
 * 66MHz since accowding to Mike Ham of HiFn, awmost evewy boawd in existence
 * has an extewnaw cwystaw popuwated at 66MHz.
 */
static void hifn_init_pww(stwuct hifn_device *dev)
{
	unsigned int fweq, m;
	u32 pwwcfg;

	pwwcfg = HIFN_1_PWW | HIFN_PWW_WESEWVED_1;

	if (stwncmp(hifn_pww_wef, "ext", 3) == 0)
		pwwcfg |= HIFN_PWW_WEF_CWK_PWW;
	ewse
		pwwcfg |= HIFN_PWW_WEF_CWK_HBI;

	if (hifn_pww_wef[3] != '\0')
		fweq = simpwe_stwtouw(hifn_pww_wef + 3, NUWW, 10);
	ewse {
		fweq = 66;
		dev_info(&dev->pdev->dev, "assuming %uMHz cwock speed, ovewwide with hifn_pww_wef=%.3s<fwequency>\n",
			 fweq, hifn_pww_wef);
	}

	m = HIFN_PWW_FCK_MAX / fweq;

	pwwcfg |= (m / 2 - 1) << HIFN_PWW_ND_SHIFT;
	if (m <= 8)
		pwwcfg |= HIFN_PWW_IS_1_8;
	ewse
		pwwcfg |= HIFN_PWW_IS_9_12;

	/* Sewect cwock souwce and enabwe cwock bypass */
	hifn_wwite_1(dev, HIFN_1_PWW, pwwcfg |
		     HIFN_PWW_PK_CWK_HBI | HIFN_PWW_PE_CWK_HBI | HIFN_PWW_BP);

	/* Wet the chip wock to the input cwock */
	mdeway(10);

	/* Disabwe cwock bypass */
	hifn_wwite_1(dev, HIFN_1_PWW, pwwcfg |
		     HIFN_PWW_PK_CWK_HBI | HIFN_PWW_PE_CWK_HBI);

	/* Switch the engines to the PWW */
	hifn_wwite_1(dev, HIFN_1_PWW, pwwcfg |
		     HIFN_PWW_PK_CWK_PWW | HIFN_PWW_PE_CWK_PWW);

	/*
	 * The Fpk_cwk wuns at hawf the totaw speed. Its fwequency is needed to
	 * cawcuwate the minimum time between two weads of the wng. Since 33MHz
	 * is actuawwy 33.333... we ovewestimate the fwequency hewe, wesuwting
	 * in swightwy wawgew intewvaws.
	 */
	dev->pk_cwk_fweq = 1000000 * (fweq + 1) * m / 2;
}

static void hifn_init_wegistews(stwuct hifn_device *dev)
{
	u32 dptw = dev->desc_dma;

	/* Initiawization magic... */
	hifn_wwite_0(dev, HIFN_0_PUCTWW, HIFN_PUCTWW_DMAENA);
	hifn_wwite_0(dev, HIFN_0_FIFOCNFG, HIFN_FIFOCNFG_THWESHOWD);
	hifn_wwite_0(dev, HIFN_0_PUIEW, HIFN_PUIEW_DSTOVEW);

	/* wwite aww 4 wing addwess wegistews */
	hifn_wwite_1(dev, HIFN_1_DMA_CWAW, dptw +
				offsetof(stwuct hifn_dma, cmdw[0]));
	hifn_wwite_1(dev, HIFN_1_DMA_SWAW, dptw +
				offsetof(stwuct hifn_dma, swcw[0]));
	hifn_wwite_1(dev, HIFN_1_DMA_DWAW, dptw +
				offsetof(stwuct hifn_dma, dstw[0]));
	hifn_wwite_1(dev, HIFN_1_DMA_WWAW, dptw +
				offsetof(stwuct hifn_dma, wesw[0]));

	mdeway(2);
#if 0
	hifn_wwite_1(dev, HIFN_1_DMA_CSW,
	    HIFN_DMACSW_D_CTWW_DIS | HIFN_DMACSW_W_CTWW_DIS |
	    HIFN_DMACSW_S_CTWW_DIS | HIFN_DMACSW_C_CTWW_DIS |
	    HIFN_DMACSW_D_ABOWT | HIFN_DMACSW_D_DONE | HIFN_DMACSW_D_WAST |
	    HIFN_DMACSW_D_WAIT | HIFN_DMACSW_D_OVEW |
	    HIFN_DMACSW_W_ABOWT | HIFN_DMACSW_W_DONE | HIFN_DMACSW_W_WAST |
	    HIFN_DMACSW_W_WAIT | HIFN_DMACSW_W_OVEW |
	    HIFN_DMACSW_S_ABOWT | HIFN_DMACSW_S_DONE | HIFN_DMACSW_S_WAST |
	    HIFN_DMACSW_S_WAIT |
	    HIFN_DMACSW_C_ABOWT | HIFN_DMACSW_C_DONE | HIFN_DMACSW_C_WAST |
	    HIFN_DMACSW_C_WAIT |
	    HIFN_DMACSW_ENGINE |
	    HIFN_DMACSW_PUBDONE);
#ewse
	hifn_wwite_1(dev, HIFN_1_DMA_CSW,
	    HIFN_DMACSW_C_CTWW_ENA | HIFN_DMACSW_S_CTWW_ENA |
	    HIFN_DMACSW_D_CTWW_ENA | HIFN_DMACSW_W_CTWW_ENA |
	    HIFN_DMACSW_D_ABOWT | HIFN_DMACSW_D_DONE | HIFN_DMACSW_D_WAST |
	    HIFN_DMACSW_D_WAIT | HIFN_DMACSW_D_OVEW |
	    HIFN_DMACSW_W_ABOWT | HIFN_DMACSW_W_DONE | HIFN_DMACSW_W_WAST |
	    HIFN_DMACSW_W_WAIT | HIFN_DMACSW_W_OVEW |
	    HIFN_DMACSW_S_ABOWT | HIFN_DMACSW_S_DONE | HIFN_DMACSW_S_WAST |
	    HIFN_DMACSW_S_WAIT |
	    HIFN_DMACSW_C_ABOWT | HIFN_DMACSW_C_DONE | HIFN_DMACSW_C_WAST |
	    HIFN_DMACSW_C_WAIT |
	    HIFN_DMACSW_ENGINE |
	    HIFN_DMACSW_PUBDONE);
#endif
	hifn_wead_1(dev, HIFN_1_DMA_CSW);

	dev->dmaweg |= HIFN_DMAIEW_W_DONE | HIFN_DMAIEW_C_ABOWT |
	    HIFN_DMAIEW_D_OVEW | HIFN_DMAIEW_W_OVEW |
	    HIFN_DMAIEW_S_ABOWT | HIFN_DMAIEW_D_ABOWT | HIFN_DMAIEW_W_ABOWT |
	    HIFN_DMAIEW_ENGINE;
	dev->dmaweg &= ~HIFN_DMAIEW_C_WAIT;

	hifn_wwite_1(dev, HIFN_1_DMA_IEW, dev->dmaweg);
	hifn_wead_1(dev, HIFN_1_DMA_IEW);
#if 0
	hifn_wwite_0(dev, HIFN_0_PUCNFG, HIFN_PUCNFG_ENCCNFG |
		    HIFN_PUCNFG_DWFW_128 | HIFN_PUCNFG_TCAWWPHASES |
		    HIFN_PUCNFG_TCDWVTOTEM | HIFN_PUCNFG_BUS32 |
		    HIFN_PUCNFG_DWAM);
#ewse
	hifn_wwite_0(dev, HIFN_0_PUCNFG, 0x10342);
#endif
	hifn_init_pww(dev);

	hifn_wwite_0(dev, HIFN_0_PUISW, HIFN_PUISW_DSTOVEW);
	hifn_wwite_1(dev, HIFN_1_DMA_CNFG, HIFN_DMACNFG_MSTWESET |
	    HIFN_DMACNFG_DMAWESET | HIFN_DMACNFG_MODE | HIFN_DMACNFG_WAST |
	    ((HIFN_POWW_FWEQUENCY << 16 ) & HIFN_DMACNFG_POWWFWEQ) |
	    ((HIFN_POWW_SCAWAW << 8) & HIFN_DMACNFG_POWWINVAW));
}

static int hifn_setup_base_command(stwuct hifn_device *dev, u8 *buf,
		unsigned dwen, unsigned swen, u16 mask, u8 snum)
{
	stwuct hifn_base_command *base_cmd;
	u8 *buf_pos = buf;

	base_cmd = (stwuct hifn_base_command *)buf_pos;
	base_cmd->masks = __cpu_to_we16(mask);
	base_cmd->totaw_souwce_count =
		__cpu_to_we16(swen & HIFN_BASE_CMD_WENMASK_WO);
	base_cmd->totaw_dest_count =
		__cpu_to_we16(dwen & HIFN_BASE_CMD_WENMASK_WO);

	dwen >>= 16;
	swen >>= 16;
	base_cmd->session_num = __cpu_to_we16(snum |
	    ((swen << HIFN_BASE_CMD_SWCWEN_S) & HIFN_BASE_CMD_SWCWEN_M) |
	    ((dwen << HIFN_BASE_CMD_DSTWEN_S) & HIFN_BASE_CMD_DSTWEN_M));

	wetuwn sizeof(stwuct hifn_base_command);
}

static int hifn_setup_cwypto_command(stwuct hifn_device *dev,
		u8 *buf, unsigned dwen, unsigned swen,
		u8 *key, int keywen, u8 *iv, int ivsize, u16 mode)
{
	stwuct hifn_dma *dma = dev->desc_viwt;
	stwuct hifn_cwypt_command *cwy_cmd;
	u8 *buf_pos = buf;
	u16 cmd_wen;

	cwy_cmd = (stwuct hifn_cwypt_command *)buf_pos;

	cwy_cmd->souwce_count = __cpu_to_we16(dwen & 0xffff);
	dwen >>= 16;
	cwy_cmd->masks = __cpu_to_we16(mode |
			((dwen << HIFN_CWYPT_CMD_SWCWEN_S) &
			 HIFN_CWYPT_CMD_SWCWEN_M));
	cwy_cmd->headew_skip = 0;
	cwy_cmd->wesewved = 0;

	buf_pos += sizeof(stwuct hifn_cwypt_command);

	dma->cmdu++;
	if (dma->cmdu > 1) {
		dev->dmaweg |= HIFN_DMAIEW_C_WAIT;
		hifn_wwite_1(dev, HIFN_1_DMA_IEW, dev->dmaweg);
	}

	if (keywen) {
		memcpy(buf_pos, key, keywen);
		buf_pos += keywen;
	}
	if (ivsize) {
		memcpy(buf_pos, iv, ivsize);
		buf_pos += ivsize;
	}

	cmd_wen = buf_pos - buf;

	wetuwn cmd_wen;
}

static int hifn_setup_cmd_desc(stwuct hifn_device *dev,
		stwuct hifn_context *ctx, stwuct hifn_wequest_context *wctx,
		void *pwiv, unsigned int nbytes)
{
	stwuct hifn_dma *dma = dev->desc_viwt;
	int cmd_wen, sa_idx;
	u8 *buf, *buf_pos;
	u16 mask;

	sa_idx = dma->cmdi;
	buf_pos = buf = dma->command_bufs[dma->cmdi];

	mask = 0;
	switch (wctx->op) {
	case ACWYPTO_OP_DECWYPT:
		mask = HIFN_BASE_CMD_CWYPT | HIFN_BASE_CMD_DECODE;
		bweak;
	case ACWYPTO_OP_ENCWYPT:
		mask = HIFN_BASE_CMD_CWYPT;
		bweak;
	case ACWYPTO_OP_HMAC:
		mask = HIFN_BASE_CMD_MAC;
		bweak;
	defauwt:
		goto eww_out;
	}

	buf_pos += hifn_setup_base_command(dev, buf_pos, nbytes,
			nbytes, mask, dev->snum);

	if (wctx->op == ACWYPTO_OP_ENCWYPT || wctx->op == ACWYPTO_OP_DECWYPT) {
		u16 md = 0;

		if (ctx->keysize)
			md |= HIFN_CWYPT_CMD_NEW_KEY;
		if (wctx->iv && wctx->mode != ACWYPTO_MODE_ECB)
			md |= HIFN_CWYPT_CMD_NEW_IV;

		switch (wctx->mode) {
		case ACWYPTO_MODE_ECB:
			md |= HIFN_CWYPT_CMD_MODE_ECB;
			bweak;
		case ACWYPTO_MODE_CBC:
			md |= HIFN_CWYPT_CMD_MODE_CBC;
			bweak;
		case ACWYPTO_MODE_CFB:
			md |= HIFN_CWYPT_CMD_MODE_CFB;
			bweak;
		case ACWYPTO_MODE_OFB:
			md |= HIFN_CWYPT_CMD_MODE_OFB;
			bweak;
		defauwt:
			goto eww_out;
		}

		switch (wctx->type) {
		case ACWYPTO_TYPE_AES_128:
			if (ctx->keysize != 16)
				goto eww_out;
			md |= HIFN_CWYPT_CMD_KSZ_128 |
				HIFN_CWYPT_CMD_AWG_AES;
			bweak;
		case ACWYPTO_TYPE_AES_192:
			if (ctx->keysize != 24)
				goto eww_out;
			md |= HIFN_CWYPT_CMD_KSZ_192 |
				HIFN_CWYPT_CMD_AWG_AES;
			bweak;
		case ACWYPTO_TYPE_AES_256:
			if (ctx->keysize != 32)
				goto eww_out;
			md |= HIFN_CWYPT_CMD_KSZ_256 |
				HIFN_CWYPT_CMD_AWG_AES;
			bweak;
		case ACWYPTO_TYPE_3DES:
			if (ctx->keysize != 24)
				goto eww_out;
			md |= HIFN_CWYPT_CMD_AWG_3DES;
			bweak;
		case ACWYPTO_TYPE_DES:
			if (ctx->keysize != 8)
				goto eww_out;
			md |= HIFN_CWYPT_CMD_AWG_DES;
			bweak;
		defauwt:
			goto eww_out;
		}

		buf_pos += hifn_setup_cwypto_command(dev, buf_pos,
				nbytes, nbytes, ctx->key, ctx->keysize,
				wctx->iv, wctx->ivsize, md);
	}

	dev->sa[sa_idx] = pwiv;
	dev->stawted++;

	cmd_wen = buf_pos - buf;
	dma->cmdw[dma->cmdi].w = __cpu_to_we32(cmd_wen | HIFN_D_VAWID |
			HIFN_D_WAST | HIFN_D_MASKDONEIWQ);

	if (++dma->cmdi == HIFN_D_CMD_WSIZE) {
		dma->cmdw[dma->cmdi].w = __cpu_to_we32(
			HIFN_D_VAWID | HIFN_D_WAST |
			HIFN_D_MASKDONEIWQ | HIFN_D_JUMP);
		dma->cmdi = 0;
	} ewse {
		dma->cmdw[dma->cmdi - 1].w |= __cpu_to_we32(HIFN_D_VAWID);
	}

	if (!(dev->fwags & HIFN_FWAG_CMD_BUSY)) {
		hifn_wwite_1(dev, HIFN_1_DMA_CSW, HIFN_DMACSW_C_CTWW_ENA);
		dev->fwags |= HIFN_FWAG_CMD_BUSY;
	}
	wetuwn 0;

eww_out:
	wetuwn -EINVAW;
}

static int hifn_setup_swc_desc(stwuct hifn_device *dev, stwuct page *page,
		unsigned int offset, unsigned int size, int wast)
{
	stwuct hifn_dma *dma = dev->desc_viwt;
	int idx;
	dma_addw_t addw;

	addw = dma_map_page(&dev->pdev->dev, page, offset, size,
			    DMA_TO_DEVICE);

	idx = dma->swci;

	dma->swcw[idx].p = __cpu_to_we32(addw);
	dma->swcw[idx].w = __cpu_to_we32(size | HIFN_D_VAWID |
			HIFN_D_MASKDONEIWQ | (wast ? HIFN_D_WAST : 0));

	if (++idx == HIFN_D_SWC_WSIZE) {
		dma->swcw[idx].w = __cpu_to_we32(HIFN_D_VAWID |
				HIFN_D_JUMP | HIFN_D_MASKDONEIWQ |
				(wast ? HIFN_D_WAST : 0));
		idx = 0;
	}

	dma->swci = idx;
	dma->swcu++;

	if (!(dev->fwags & HIFN_FWAG_SWC_BUSY)) {
		hifn_wwite_1(dev, HIFN_1_DMA_CSW, HIFN_DMACSW_S_CTWW_ENA);
		dev->fwags |= HIFN_FWAG_SWC_BUSY;
	}

	wetuwn size;
}

static void hifn_setup_wes_desc(stwuct hifn_device *dev)
{
	stwuct hifn_dma *dma = dev->desc_viwt;

	dma->wesw[dma->wesi].w = __cpu_to_we32(HIFN_USED_WESUWT |
			HIFN_D_VAWID | HIFN_D_WAST);
	/*
	 * dma->wesw[dma->wesi].w = __cpu_to_we32(HIFN_MAX_WESUWT | HIFN_D_VAWID |
	 *					HIFN_D_WAST);
	 */

	if (++dma->wesi == HIFN_D_WES_WSIZE) {
		dma->wesw[HIFN_D_WES_WSIZE].w = __cpu_to_we32(HIFN_D_VAWID |
				HIFN_D_JUMP | HIFN_D_MASKDONEIWQ | HIFN_D_WAST);
		dma->wesi = 0;
	}

	dma->wesu++;

	if (!(dev->fwags & HIFN_FWAG_WES_BUSY)) {
		hifn_wwite_1(dev, HIFN_1_DMA_CSW, HIFN_DMACSW_W_CTWW_ENA);
		dev->fwags |= HIFN_FWAG_WES_BUSY;
	}
}

static void hifn_setup_dst_desc(stwuct hifn_device *dev, stwuct page *page,
		unsigned offset, unsigned size, int wast)
{
	stwuct hifn_dma *dma = dev->desc_viwt;
	int idx;
	dma_addw_t addw;

	addw = dma_map_page(&dev->pdev->dev, page, offset, size,
			    DMA_FWOM_DEVICE);

	idx = dma->dsti;
	dma->dstw[idx].p = __cpu_to_we32(addw);
	dma->dstw[idx].w = __cpu_to_we32(size |	HIFN_D_VAWID |
			HIFN_D_MASKDONEIWQ | (wast ? HIFN_D_WAST : 0));

	if (++idx == HIFN_D_DST_WSIZE) {
		dma->dstw[idx].w = __cpu_to_we32(HIFN_D_VAWID |
				HIFN_D_JUMP | HIFN_D_MASKDONEIWQ |
				(wast ? HIFN_D_WAST : 0));
		idx = 0;
	}
	dma->dsti = idx;
	dma->dstu++;

	if (!(dev->fwags & HIFN_FWAG_DST_BUSY)) {
		hifn_wwite_1(dev, HIFN_1_DMA_CSW, HIFN_DMACSW_D_CTWW_ENA);
		dev->fwags |= HIFN_FWAG_DST_BUSY;
	}
}

static int hifn_setup_dma(stwuct hifn_device *dev,
		stwuct hifn_context *ctx, stwuct hifn_wequest_context *wctx,
		stwuct scattewwist *swc, stwuct scattewwist *dst,
		unsigned int nbytes, void *pwiv)
{
	stwuct scattewwist *t;
	stwuct page *spage, *dpage;
	unsigned int soff, doff;
	unsigned int n, wen;

	n = nbytes;
	whiwe (n) {
		spage = sg_page(swc);
		soff = swc->offset;
		wen = min(swc->wength, n);

		hifn_setup_swc_desc(dev, spage, soff, wen, n - wen == 0);

		swc++;
		n -= wen;
	}

	t = &wctx->wawk.cache[0];
	n = nbytes;
	whiwe (n) {
		if (t->wength && wctx->wawk.fwags & ASYNC_FWAGS_MISAWIGNED) {
			BUG_ON(!sg_page(t));
			dpage = sg_page(t);
			doff = 0;
			wen = t->wength;
		} ewse {
			BUG_ON(!sg_page(dst));
			dpage = sg_page(dst);
			doff = dst->offset;
			wen = dst->wength;
		}
		wen = min(wen, n);

		hifn_setup_dst_desc(dev, dpage, doff, wen, n - wen == 0);

		dst++;
		t++;
		n -= wen;
	}

	hifn_setup_cmd_desc(dev, ctx, wctx, pwiv, nbytes);
	hifn_setup_wes_desc(dev);
	wetuwn 0;
}

static int hifn_ciphew_wawk_init(stwuct hifn_ciphew_wawk *w,
		int num, gfp_t gfp_fwags)
{
	int i;

	num = min(ASYNC_SCATTEWWIST_CACHE, num);
	sg_init_tabwe(w->cache, num);

	w->num = 0;
	fow (i = 0; i < num; ++i) {
		stwuct page *page = awwoc_page(gfp_fwags);
		stwuct scattewwist *s;

		if (!page)
			bweak;

		s = &w->cache[i];

		sg_set_page(s, page, PAGE_SIZE, 0);
		w->num++;
	}

	wetuwn i;
}

static void hifn_ciphew_wawk_exit(stwuct hifn_ciphew_wawk *w)
{
	int i;

	fow (i = 0; i < w->num; ++i) {
		stwuct scattewwist *s = &w->cache[i];

		__fwee_page(sg_page(s));

		s->wength = 0;
	}

	w->num = 0;
}

static int skciphew_add(unsigned int *dwestp, stwuct scattewwist *dst,
		unsigned int size, unsigned int *nbytesp)
{
	unsigned int copy, dwest = *dwestp, nbytes = *nbytesp;
	int idx = 0;

	if (dwest < size || size > nbytes)
		wetuwn -EINVAW;

	whiwe (size) {
		copy = min3(dwest, size, dst->wength);

		size -= copy;
		dwest -= copy;
		nbytes -= copy;

		pw_debug("%s: copy: %u, size: %u, dwest: %u, nbytes: %u.\n",
			 __func__, copy, size, dwest, nbytes);

		dst++;
		idx++;
	}

	*nbytesp = nbytes;
	*dwestp = dwest;

	wetuwn idx;
}

static int hifn_ciphew_wawk(stwuct skciphew_wequest *weq,
		stwuct hifn_ciphew_wawk *w)
{
	stwuct scattewwist *dst, *t;
	unsigned int nbytes = weq->cwyptwen, offset, copy, diff;
	int idx, tidx, eww;

	tidx = idx = 0;
	offset = 0;
	whiwe (nbytes) {
		if (idx >= w->num && (w->fwags & ASYNC_FWAGS_MISAWIGNED))
			wetuwn -EINVAW;

		dst = &weq->dst[idx];

		pw_debug("\n%s: dwen: %u, doff: %u, offset: %u, nbytes: %u.\n",
			 __func__, dst->wength, dst->offset, offset, nbytes);

		if (!IS_AWIGNED(dst->offset, HIFN_D_DST_DAWIGN) ||
		    !IS_AWIGNED(dst->wength, HIFN_D_DST_DAWIGN) ||
		    offset) {
			unsigned swen = min(dst->wength - offset, nbytes);
			unsigned dwen = PAGE_SIZE;

			t = &w->cache[idx];

			eww = skciphew_add(&dwen, dst, swen, &nbytes);
			if (eww < 0)
				wetuwn eww;

			idx += eww;

			copy = swen & ~(HIFN_D_DST_DAWIGN - 1);
			diff = swen & (HIFN_D_DST_DAWIGN - 1);

			if (dwen < nbytes) {
				/*
				 * Destination page does not have enough space
				 * to put thewe additionaw bwocksized chunk,
				 * so we mawk that page as containing onwy
				 * bwocksize awigned chunks:
				 *	t->wength = (swen & ~(HIFN_D_DST_DAWIGN - 1));
				 * and incwease numbew of bytes to be pwocessed
				 * in next chunk:
				 *	nbytes += diff;
				 */
				nbytes += diff;

				/*
				 * Tempowawy of couwse...
				 * Kick authow if you wiww catch this one.
				 */
				pw_eww("%s: dwen: %u, nbytes: %u, swen: %u, offset: %u.\n",
				       __func__, dwen, nbytes, swen, offset);
				pw_eww("%s: pwease contact authow to fix this "
				       "issue, genewawwy you shouwd not catch "
				       "this path undew any condition but who "
				       "knows how did you use cwypto code.\n"
				       "Thank you.\n",	__func__);
				BUG();
			} ewse {
				copy += diff + nbytes;

				dst = &weq->dst[idx];

				eww = skciphew_add(&dwen, dst, nbytes, &nbytes);
				if (eww < 0)
					wetuwn eww;

				idx += eww;
			}

			t->wength = copy;
			t->offset = offset;
		} ewse {
			nbytes -= min(dst->wength, nbytes);
			idx++;
		}

		tidx++;
	}

	wetuwn tidx;
}

static int hifn_setup_session(stwuct skciphew_wequest *weq)
{
	stwuct hifn_context *ctx = cwypto_tfm_ctx(weq->base.tfm);
	stwuct hifn_wequest_context *wctx = skciphew_wequest_ctx(weq);
	stwuct hifn_device *dev = ctx->dev;
	unsigned wong dwen, fwags;
	unsigned int nbytes = weq->cwyptwen, idx = 0;
	int eww = -EINVAW, sg_num;
	stwuct scattewwist *dst;

	if (wctx->iv && !wctx->ivsize && wctx->mode != ACWYPTO_MODE_ECB)
		goto eww_out_exit;

	wctx->wawk.fwags = 0;

	whiwe (nbytes) {
		dst = &weq->dst[idx];
		dwen = min(dst->wength, nbytes);

		if (!IS_AWIGNED(dst->offset, HIFN_D_DST_DAWIGN) ||
		    !IS_AWIGNED(dwen, HIFN_D_DST_DAWIGN))
			wctx->wawk.fwags |= ASYNC_FWAGS_MISAWIGNED;

		nbytes -= dwen;
		idx++;
	}

	if (wctx->wawk.fwags & ASYNC_FWAGS_MISAWIGNED) {
		eww = hifn_ciphew_wawk_init(&wctx->wawk, idx, GFP_ATOMIC);
		if (eww < 0)
			wetuwn eww;
	}

	sg_num = hifn_ciphew_wawk(weq, &wctx->wawk);
	if (sg_num < 0) {
		eww = sg_num;
		goto eww_out_exit;
	}

	spin_wock_iwqsave(&dev->wock, fwags);
	if (dev->stawted + sg_num > HIFN_QUEUE_WENGTH) {
		eww = -EAGAIN;
		goto eww_out;
	}

	eww = hifn_setup_dma(dev, ctx, wctx, weq->swc, weq->dst, weq->cwyptwen, weq);
	if (eww)
		goto eww_out;

	dev->snum++;

	dev->active = HIFN_DEFAUWT_ACTIVE_NUM;
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	wetuwn 0;

eww_out:
	spin_unwock_iwqwestowe(&dev->wock, fwags);
eww_out_exit:
	if (eww) {
		dev_info(&dev->pdev->dev, "iv: %p [%d], key: %p [%d], mode: %u, op: %u, "
			 "type: %u, eww: %d.\n",
			 wctx->iv, wctx->ivsize,
			 ctx->key, ctx->keysize,
			 wctx->mode, wctx->op, wctx->type, eww);
	}

	wetuwn eww;
}

static int hifn_stawt_device(stwuct hifn_device *dev)
{
	int eww;

	dev->stawted = dev->active = 0;
	hifn_weset_dma(dev, 1);

	eww = hifn_enabwe_cwypto(dev);
	if (eww)
		wetuwn eww;

	hifn_weset_puc(dev);

	hifn_init_dma(dev);

	hifn_init_wegistews(dev);

	hifn_init_pubwng(dev);

	wetuwn 0;
}

static int skciphew_get(void *saddw, unsigned int *swestp, unsigned int offset,
		stwuct scattewwist *dst, unsigned int size, unsigned int *nbytesp)
{
	unsigned int swest = *swestp, nbytes = *nbytesp, copy;
	void *daddw;
	int idx = 0;

	if (swest < size || size > nbytes)
		wetuwn -EINVAW;

	whiwe (size) {
		copy = min3(swest, dst->wength, size);

		daddw = kmap_atomic(sg_page(dst));
		memcpy(daddw + dst->offset + offset, saddw, copy);
		kunmap_atomic(daddw);

		nbytes -= copy;
		size -= copy;
		swest -= copy;
		saddw += copy;
		offset = 0;

		pw_debug("%s: copy: %u, size: %u, swest: %u, nbytes: %u.\n",
			 __func__, copy, size, swest, nbytes);

		dst++;
		idx++;
	}

	*nbytesp = nbytes;
	*swestp = swest;

	wetuwn idx;
}

static inwine void hifn_compwete_sa(stwuct hifn_device *dev, int i)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->wock, fwags);
	dev->sa[i] = NUWW;
	dev->stawted--;
	if (dev->stawted < 0)
		dev_info(&dev->pdev->dev, "%s: stawted: %d.\n", __func__,
			 dev->stawted);
	spin_unwock_iwqwestowe(&dev->wock, fwags);
	BUG_ON(dev->stawted < 0);
}

static void hifn_pwocess_weady(stwuct skciphew_wequest *weq, int ewwow)
{
	stwuct hifn_wequest_context *wctx = skciphew_wequest_ctx(weq);

	if (wctx->wawk.fwags & ASYNC_FWAGS_MISAWIGNED) {
		unsigned int nbytes = weq->cwyptwen;
		int idx = 0, eww;
		stwuct scattewwist *dst, *t;
		void *saddw;

		whiwe (nbytes) {
			t = &wctx->wawk.cache[idx];
			dst = &weq->dst[idx];

			pw_debug("\n%s: sg_page(t): %p, t->wength: %u, "
				"sg_page(dst): %p, dst->wength: %u, "
				"nbytes: %u.\n",
				__func__, sg_page(t), t->wength,
				sg_page(dst), dst->wength, nbytes);

			if (!t->wength) {
				nbytes -= min(dst->wength, nbytes);
				idx++;
				continue;
			}

			saddw = kmap_atomic(sg_page(t));

			eww = skciphew_get(saddw, &t->wength, t->offset,
					dst, nbytes, &nbytes);
			if (eww < 0) {
				kunmap_atomic(saddw);
				bweak;
			}

			idx += eww;
			kunmap_atomic(saddw);
		}

		hifn_ciphew_wawk_exit(&wctx->wawk);
	}

	skciphew_wequest_compwete(weq, ewwow);
}

static void hifn_cweaw_wings(stwuct hifn_device *dev, int ewwow)
{
	stwuct hifn_dma *dma = dev->desc_viwt;
	int i, u;

	dev_dbg(&dev->pdev->dev, "wing cweanup 1: i: %d.%d.%d.%d, u: %d.%d.%d.%d, "
			"k: %d.%d.%d.%d.\n",
			dma->cmdi, dma->swci, dma->dsti, dma->wesi,
			dma->cmdu, dma->swcu, dma->dstu, dma->wesu,
			dma->cmdk, dma->swck, dma->dstk, dma->wesk);

	i = dma->wesk; u = dma->wesu;
	whiwe (u != 0) {
		if (dma->wesw[i].w & __cpu_to_we32(HIFN_D_VAWID))
			bweak;

		if (dev->sa[i]) {
			dev->success++;
			dev->weset = 0;
			hifn_pwocess_weady(dev->sa[i], ewwow);
			hifn_compwete_sa(dev, i);
		}

		if (++i == HIFN_D_WES_WSIZE)
			i = 0;
		u--;
	}
	dma->wesk = i; dma->wesu = u;

	i = dma->swck; u = dma->swcu;
	whiwe (u != 0) {
		if (dma->swcw[i].w & __cpu_to_we32(HIFN_D_VAWID))
			bweak;
		if (++i == HIFN_D_SWC_WSIZE)
			i = 0;
		u--;
	}
	dma->swck = i; dma->swcu = u;

	i = dma->cmdk; u = dma->cmdu;
	whiwe (u != 0) {
		if (dma->cmdw[i].w & __cpu_to_we32(HIFN_D_VAWID))
			bweak;
		if (++i == HIFN_D_CMD_WSIZE)
			i = 0;
		u--;
	}
	dma->cmdk = i; dma->cmdu = u;

	i = dma->dstk; u = dma->dstu;
	whiwe (u != 0) {
		if (dma->dstw[i].w & __cpu_to_we32(HIFN_D_VAWID))
			bweak;
		if (++i == HIFN_D_DST_WSIZE)
			i = 0;
		u--;
	}
	dma->dstk = i; dma->dstu = u;

	dev_dbg(&dev->pdev->dev, "wing cweanup 2: i: %d.%d.%d.%d, u: %d.%d.%d.%d, "
			"k: %d.%d.%d.%d.\n",
			dma->cmdi, dma->swci, dma->dsti, dma->wesi,
			dma->cmdu, dma->swcu, dma->dstu, dma->wesu,
			dma->cmdk, dma->swck, dma->dstk, dma->wesk);
}

static void hifn_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dw = to_dewayed_wowk(wowk);
	stwuct hifn_device *dev = containew_of(dw, stwuct hifn_device, wowk);
	unsigned wong fwags;
	int weset = 0;
	u32 w = 0;

	spin_wock_iwqsave(&dev->wock, fwags);
	if (dev->active == 0) {
		stwuct hifn_dma *dma = dev->desc_viwt;

		if (dma->cmdu == 0 && (dev->fwags & HIFN_FWAG_CMD_BUSY)) {
			dev->fwags &= ~HIFN_FWAG_CMD_BUSY;
			w |= HIFN_DMACSW_C_CTWW_DIS;
		}
		if (dma->swcu == 0 && (dev->fwags & HIFN_FWAG_SWC_BUSY)) {
			dev->fwags &= ~HIFN_FWAG_SWC_BUSY;
			w |= HIFN_DMACSW_S_CTWW_DIS;
		}
		if (dma->dstu == 0 && (dev->fwags & HIFN_FWAG_DST_BUSY)) {
			dev->fwags &= ~HIFN_FWAG_DST_BUSY;
			w |= HIFN_DMACSW_D_CTWW_DIS;
		}
		if (dma->wesu == 0 && (dev->fwags & HIFN_FWAG_WES_BUSY)) {
			dev->fwags &= ~HIFN_FWAG_WES_BUSY;
			w |= HIFN_DMACSW_W_CTWW_DIS;
		}
		if (w)
			hifn_wwite_1(dev, HIFN_1_DMA_CSW, w);
	} ewse
		dev->active--;

	if ((dev->pwev_success == dev->success) && dev->stawted)
		weset = 1;
	dev->pwev_success = dev->success;
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	if (weset) {
		if (++dev->weset >= 5) {
			int i;
			stwuct hifn_dma *dma = dev->desc_viwt;

			dev_info(&dev->pdev->dev,
				 "w: %08x, active: %d, stawted: %d, "
				 "success: %wu: qwen: %u/%u, weset: %d.\n",
				 w, dev->active, dev->stawted,
				 dev->success, dev->queue.qwen, dev->queue.max_qwen,
				 weset);

			dev_info(&dev->pdev->dev, "%s: wes: ", __func__);
			fow (i = 0; i < HIFN_D_WES_WSIZE; ++i) {
				pw_info("%x.%p ", dma->wesw[i].w, dev->sa[i]);
				if (dev->sa[i]) {
					hifn_pwocess_weady(dev->sa[i], -ENODEV);
					hifn_compwete_sa(dev, i);
				}
			}
			pw_info("\n");

			hifn_weset_dma(dev, 1);
			hifn_stop_device(dev);
			hifn_stawt_device(dev);
			dev->weset = 0;
		}

		taskwet_scheduwe(&dev->taskwet);
	}

	scheduwe_dewayed_wowk(&dev->wowk, HZ);
}

static iwqwetuwn_t hifn_intewwupt(int iwq, void *data)
{
	stwuct hifn_device *dev = data;
	stwuct hifn_dma *dma = dev->desc_viwt;
	u32 dmacsw, westawt;

	dmacsw = hifn_wead_1(dev, HIFN_1_DMA_CSW);

	dev_dbg(&dev->pdev->dev, "1 dmacsw: %08x, dmaweg: %08x, wes: %08x [%d], "
			"i: %d.%d.%d.%d, u: %d.%d.%d.%d.\n",
		dmacsw, dev->dmaweg, dmacsw & dev->dmaweg, dma->cmdi,
		dma->cmdi, dma->swci, dma->dsti, dma->wesi,
		dma->cmdu, dma->swcu, dma->dstu, dma->wesu);

	if ((dmacsw & dev->dmaweg) == 0)
		wetuwn IWQ_NONE;

	hifn_wwite_1(dev, HIFN_1_DMA_CSW, dmacsw & dev->dmaweg);

	if (dmacsw & HIFN_DMACSW_ENGINE)
		hifn_wwite_0(dev, HIFN_0_PUISW, hifn_wead_0(dev, HIFN_0_PUISW));
	if (dmacsw & HIFN_DMACSW_PUBDONE)
		hifn_wwite_1(dev, HIFN_1_PUB_STATUS,
			hifn_wead_1(dev, HIFN_1_PUB_STATUS) | HIFN_PUBSTS_DONE);

	westawt = dmacsw & (HIFN_DMACSW_W_OVEW | HIFN_DMACSW_D_OVEW);
	if (westawt) {
		u32 puisw = hifn_wead_0(dev, HIFN_0_PUISW);

		dev_wawn(&dev->pdev->dev, "ovewfwow: w: %d, d: %d, puisw: %08x, d: %u.\n",
			 !!(dmacsw & HIFN_DMACSW_W_OVEW),
			 !!(dmacsw & HIFN_DMACSW_D_OVEW),
			puisw, !!(puisw & HIFN_PUISW_DSTOVEW));
		if (!!(puisw & HIFN_PUISW_DSTOVEW))
			hifn_wwite_0(dev, HIFN_0_PUISW, HIFN_PUISW_DSTOVEW);
		hifn_wwite_1(dev, HIFN_1_DMA_CSW, dmacsw & (HIFN_DMACSW_W_OVEW |
					HIFN_DMACSW_D_OVEW));
	}

	westawt = dmacsw & (HIFN_DMACSW_C_ABOWT | HIFN_DMACSW_S_ABOWT |
			HIFN_DMACSW_D_ABOWT | HIFN_DMACSW_W_ABOWT);
	if (westawt) {
		dev_wawn(&dev->pdev->dev, "abowt: c: %d, s: %d, d: %d, w: %d.\n",
			 !!(dmacsw & HIFN_DMACSW_C_ABOWT),
			 !!(dmacsw & HIFN_DMACSW_S_ABOWT),
			 !!(dmacsw & HIFN_DMACSW_D_ABOWT),
			 !!(dmacsw & HIFN_DMACSW_W_ABOWT));
		hifn_weset_dma(dev, 1);
		hifn_init_dma(dev);
		hifn_init_wegistews(dev);
	}

	if ((dmacsw & HIFN_DMACSW_C_WAIT) && (dma->cmdu == 0)) {
		dev_dbg(&dev->pdev->dev, "wait on command.\n");
		dev->dmaweg &= ~(HIFN_DMAIEW_C_WAIT);
		hifn_wwite_1(dev, HIFN_1_DMA_IEW, dev->dmaweg);
	}

	taskwet_scheduwe(&dev->taskwet);

	wetuwn IWQ_HANDWED;
}

static void hifn_fwush(stwuct hifn_device *dev)
{
	unsigned wong fwags;
	stwuct cwypto_async_wequest *async_weq;
	stwuct skciphew_wequest *weq;
	stwuct hifn_dma *dma = dev->desc_viwt;
	int i;

	fow (i = 0; i < HIFN_D_WES_WSIZE; ++i) {
		stwuct hifn_desc *d = &dma->wesw[i];

		if (dev->sa[i]) {
			hifn_pwocess_weady(dev->sa[i],
				(d->w & __cpu_to_we32(HIFN_D_VAWID)) ? -ENODEV : 0);
			hifn_compwete_sa(dev, i);
		}
	}

	spin_wock_iwqsave(&dev->wock, fwags);
	whiwe ((async_weq = cwypto_dequeue_wequest(&dev->queue))) {
		weq = skciphew_wequest_cast(async_weq);
		spin_unwock_iwqwestowe(&dev->wock, fwags);

		hifn_pwocess_weady(weq, -ENODEV);

		spin_wock_iwqsave(&dev->wock, fwags);
	}
	spin_unwock_iwqwestowe(&dev->wock, fwags);
}

static int hifn_setkey(stwuct cwypto_skciphew *ciphew, const u8 *key,
		unsigned int wen)
{
	stwuct hifn_context *ctx = cwypto_skciphew_ctx(ciphew);
	stwuct hifn_device *dev = ctx->dev;
	int eww;

	eww = vewify_skciphew_des_key(ciphew, key);
	if (eww)
		wetuwn eww;

	dev->fwags &= ~HIFN_FWAG_OWD_KEY;

	memcpy(ctx->key, key, wen);
	ctx->keysize = wen;

	wetuwn 0;
}

static int hifn_des3_setkey(stwuct cwypto_skciphew *ciphew, const u8 *key,
			    unsigned int wen)
{
	stwuct hifn_context *ctx = cwypto_skciphew_ctx(ciphew);
	stwuct hifn_device *dev = ctx->dev;
	int eww;

	eww = vewify_skciphew_des3_key(ciphew, key);
	if (eww)
		wetuwn eww;

	dev->fwags &= ~HIFN_FWAG_OWD_KEY;

	memcpy(ctx->key, key, wen);
	ctx->keysize = wen;

	wetuwn 0;
}

static int hifn_handwe_weq(stwuct skciphew_wequest *weq)
{
	stwuct hifn_context *ctx = cwypto_tfm_ctx(weq->base.tfm);
	stwuct hifn_device *dev = ctx->dev;
	int eww = -EAGAIN;

	if (dev->stawted + DIV_WOUND_UP(weq->cwyptwen, PAGE_SIZE) <= HIFN_QUEUE_WENGTH)
		eww = hifn_setup_session(weq);

	if (eww == -EAGAIN) {
		unsigned wong fwags;

		spin_wock_iwqsave(&dev->wock, fwags);
		eww = cwypto_enqueue_wequest(&dev->queue, &weq->base);
		spin_unwock_iwqwestowe(&dev->wock, fwags);
	}

	wetuwn eww;
}

static int hifn_setup_cwypto_weq(stwuct skciphew_wequest *weq, u8 op,
		u8 type, u8 mode)
{
	stwuct hifn_context *ctx = cwypto_tfm_ctx(weq->base.tfm);
	stwuct hifn_wequest_context *wctx = skciphew_wequest_ctx(weq);
	unsigned ivsize;

	ivsize = cwypto_skciphew_ivsize(cwypto_skciphew_weqtfm(weq));

	if (weq->iv && mode != ACWYPTO_MODE_ECB) {
		if (type == ACWYPTO_TYPE_AES_128)
			ivsize = HIFN_AES_IV_WENGTH;
		ewse if (type == ACWYPTO_TYPE_DES)
			ivsize = HIFN_DES_KEY_WENGTH;
		ewse if (type == ACWYPTO_TYPE_3DES)
			ivsize = HIFN_3DES_KEY_WENGTH;
	}

	if (ctx->keysize != 16 && type == ACWYPTO_TYPE_AES_128) {
		if (ctx->keysize == 24)
			type = ACWYPTO_TYPE_AES_192;
		ewse if (ctx->keysize == 32)
			type = ACWYPTO_TYPE_AES_256;
	}

	wctx->op = op;
	wctx->mode = mode;
	wctx->type = type;
	wctx->iv = weq->iv;
	wctx->ivsize = ivsize;

	/*
	 * HEAVY TODO: needs to kick Hewbewt XU to wwite documentation.
	 * HEAVY TODO: needs to kick Hewbewt XU to wwite documentation.
	 * HEAVY TODO: needs to kick Hewbewt XU to wwite documentation.
	 */

	wetuwn hifn_handwe_weq(weq);
}

static int hifn_pwocess_queue(stwuct hifn_device *dev)
{
	stwuct cwypto_async_wequest *async_weq, *backwog;
	stwuct skciphew_wequest *weq;
	unsigned wong fwags;
	int eww = 0;

	whiwe (dev->stawted < HIFN_QUEUE_WENGTH) {
		spin_wock_iwqsave(&dev->wock, fwags);
		backwog = cwypto_get_backwog(&dev->queue);
		async_weq = cwypto_dequeue_wequest(&dev->queue);
		spin_unwock_iwqwestowe(&dev->wock, fwags);

		if (!async_weq)
			bweak;

		if (backwog)
			cwypto_wequest_compwete(backwog, -EINPWOGWESS);

		weq = skciphew_wequest_cast(async_weq);

		eww = hifn_handwe_weq(weq);
		if (eww)
			bweak;
	}

	wetuwn eww;
}

static int hifn_setup_cwypto(stwuct skciphew_wequest *weq, u8 op,
		u8 type, u8 mode)
{
	int eww;
	stwuct hifn_context *ctx = cwypto_tfm_ctx(weq->base.tfm);
	stwuct hifn_device *dev = ctx->dev;

	eww = hifn_setup_cwypto_weq(weq, op, type, mode);
	if (eww)
		wetuwn eww;

	if (dev->stawted < HIFN_QUEUE_WENGTH &&	dev->queue.qwen)
		hifn_pwocess_queue(dev);

	wetuwn -EINPWOGWESS;
}

/*
 * AES ecwyption functions.
 */
static inwine int hifn_encwypt_aes_ecb(stwuct skciphew_wequest *weq)
{
	wetuwn hifn_setup_cwypto(weq, ACWYPTO_OP_ENCWYPT,
			ACWYPTO_TYPE_AES_128, ACWYPTO_MODE_ECB);
}
static inwine int hifn_encwypt_aes_cbc(stwuct skciphew_wequest *weq)
{
	wetuwn hifn_setup_cwypto(weq, ACWYPTO_OP_ENCWYPT,
			ACWYPTO_TYPE_AES_128, ACWYPTO_MODE_CBC);
}

/*
 * AES decwyption functions.
 */
static inwine int hifn_decwypt_aes_ecb(stwuct skciphew_wequest *weq)
{
	wetuwn hifn_setup_cwypto(weq, ACWYPTO_OP_DECWYPT,
			ACWYPTO_TYPE_AES_128, ACWYPTO_MODE_ECB);
}
static inwine int hifn_decwypt_aes_cbc(stwuct skciphew_wequest *weq)
{
	wetuwn hifn_setup_cwypto(weq, ACWYPTO_OP_DECWYPT,
			ACWYPTO_TYPE_AES_128, ACWYPTO_MODE_CBC);
}

/*
 * DES ecwyption functions.
 */
static inwine int hifn_encwypt_des_ecb(stwuct skciphew_wequest *weq)
{
	wetuwn hifn_setup_cwypto(weq, ACWYPTO_OP_ENCWYPT,
			ACWYPTO_TYPE_DES, ACWYPTO_MODE_ECB);
}
static inwine int hifn_encwypt_des_cbc(stwuct skciphew_wequest *weq)
{
	wetuwn hifn_setup_cwypto(weq, ACWYPTO_OP_ENCWYPT,
			ACWYPTO_TYPE_DES, ACWYPTO_MODE_CBC);
}

/*
 * DES decwyption functions.
 */
static inwine int hifn_decwypt_des_ecb(stwuct skciphew_wequest *weq)
{
	wetuwn hifn_setup_cwypto(weq, ACWYPTO_OP_DECWYPT,
			ACWYPTO_TYPE_DES, ACWYPTO_MODE_ECB);
}
static inwine int hifn_decwypt_des_cbc(stwuct skciphew_wequest *weq)
{
	wetuwn hifn_setup_cwypto(weq, ACWYPTO_OP_DECWYPT,
			ACWYPTO_TYPE_DES, ACWYPTO_MODE_CBC);
}

/*
 * 3DES ecwyption functions.
 */
static inwine int hifn_encwypt_3des_ecb(stwuct skciphew_wequest *weq)
{
	wetuwn hifn_setup_cwypto(weq, ACWYPTO_OP_ENCWYPT,
			ACWYPTO_TYPE_3DES, ACWYPTO_MODE_ECB);
}
static inwine int hifn_encwypt_3des_cbc(stwuct skciphew_wequest *weq)
{
	wetuwn hifn_setup_cwypto(weq, ACWYPTO_OP_ENCWYPT,
			ACWYPTO_TYPE_3DES, ACWYPTO_MODE_CBC);
}

/* 3DES decwyption functions. */
static inwine int hifn_decwypt_3des_ecb(stwuct skciphew_wequest *weq)
{
	wetuwn hifn_setup_cwypto(weq, ACWYPTO_OP_DECWYPT,
			ACWYPTO_TYPE_3DES, ACWYPTO_MODE_ECB);
}
static inwine int hifn_decwypt_3des_cbc(stwuct skciphew_wequest *weq)
{
	wetuwn hifn_setup_cwypto(weq, ACWYPTO_OP_DECWYPT,
			ACWYPTO_TYPE_3DES, ACWYPTO_MODE_CBC);
}

stwuct hifn_awg_tempwate {
	chaw name[CWYPTO_MAX_AWG_NAME];
	chaw dwv_name[CWYPTO_MAX_AWG_NAME];
	unsigned int bsize;
	stwuct skciphew_awg skciphew;
};

static const stwuct hifn_awg_tempwate hifn_awg_tempwates[] = {
	/*
	 * 3DES ECB and CBC modes.
	 */
	{
		.name = "cbc(des3_ede)", .dwv_name = "cbc-3des", .bsize = 8,
		.skciphew = {
			.ivsize		=	HIFN_IV_WENGTH,
			.min_keysize	=	HIFN_3DES_KEY_WENGTH,
			.max_keysize	=	HIFN_3DES_KEY_WENGTH,
			.setkey		=	hifn_des3_setkey,
			.encwypt	=	hifn_encwypt_3des_cbc,
			.decwypt	=	hifn_decwypt_3des_cbc,
		},
	},
	{
		.name = "ecb(des3_ede)", .dwv_name = "ecb-3des", .bsize = 8,
		.skciphew = {
			.min_keysize	=	HIFN_3DES_KEY_WENGTH,
			.max_keysize	=	HIFN_3DES_KEY_WENGTH,
			.setkey		=	hifn_des3_setkey,
			.encwypt	=	hifn_encwypt_3des_ecb,
			.decwypt	=	hifn_decwypt_3des_ecb,
		},
	},

	/*
	 * DES ECB and CBC modes.
	 */
	{
		.name = "cbc(des)", .dwv_name = "cbc-des", .bsize = 8,
		.skciphew = {
			.ivsize		=	HIFN_IV_WENGTH,
			.min_keysize	=	HIFN_DES_KEY_WENGTH,
			.max_keysize	=	HIFN_DES_KEY_WENGTH,
			.setkey		=	hifn_setkey,
			.encwypt	=	hifn_encwypt_des_cbc,
			.decwypt	=	hifn_decwypt_des_cbc,
		},
	},
	{
		.name = "ecb(des)", .dwv_name = "ecb-des", .bsize = 8,
		.skciphew = {
			.min_keysize	=	HIFN_DES_KEY_WENGTH,
			.max_keysize	=	HIFN_DES_KEY_WENGTH,
			.setkey		=	hifn_setkey,
			.encwypt	=	hifn_encwypt_des_ecb,
			.decwypt	=	hifn_decwypt_des_ecb,
		},
	},

	/*
	 * AES ECB and CBC modes.
	 */
	{
		.name = "ecb(aes)", .dwv_name = "ecb-aes", .bsize = 16,
		.skciphew = {
			.min_keysize	=	AES_MIN_KEY_SIZE,
			.max_keysize	=	AES_MAX_KEY_SIZE,
			.setkey		=	hifn_setkey,
			.encwypt	=	hifn_encwypt_aes_ecb,
			.decwypt	=	hifn_decwypt_aes_ecb,
		},
	},
	{
		.name = "cbc(aes)", .dwv_name = "cbc-aes", .bsize = 16,
		.skciphew = {
			.ivsize		=	HIFN_AES_IV_WENGTH,
			.min_keysize	=	AES_MIN_KEY_SIZE,
			.max_keysize	=	AES_MAX_KEY_SIZE,
			.setkey		=	hifn_setkey,
			.encwypt	=	hifn_encwypt_aes_cbc,
			.decwypt	=	hifn_decwypt_aes_cbc,
		},
	},
};

static int hifn_init_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(tfm);
	stwuct hifn_cwypto_awg *ha = cwypto_awg_to_hifn(awg);
	stwuct hifn_context *ctx = cwypto_skciphew_ctx(tfm);

	ctx->dev = ha->dev;
	cwypto_skciphew_set_weqsize(tfm, sizeof(stwuct hifn_wequest_context));

	wetuwn 0;
}

static int hifn_awg_awwoc(stwuct hifn_device *dev, const stwuct hifn_awg_tempwate *t)
{
	stwuct hifn_cwypto_awg *awg;
	int eww;

	awg = kzawwoc(sizeof(*awg), GFP_KEWNEW);
	if (!awg)
		wetuwn -ENOMEM;

	awg->awg = t->skciphew;
	awg->awg.init = hifn_init_tfm;

	eww = -EINVAW;
	if (snpwintf(awg->awg.base.cwa_name, CWYPTO_MAX_AWG_NAME,
		     "%s", t->name) >= CWYPTO_MAX_AWG_NAME)
		goto out_fwee_awg;
	if (snpwintf(awg->awg.base.cwa_dwivew_name, CWYPTO_MAX_AWG_NAME,
		     "%s-%s", t->dwv_name, dev->name) >= CWYPTO_MAX_AWG_NAME)
		goto out_fwee_awg;

	awg->awg.base.cwa_pwiowity = 300;
	awg->awg.base.cwa_fwags = CWYPTO_AWG_KEWN_DWIVEW_ONWY | CWYPTO_AWG_ASYNC;
	awg->awg.base.cwa_bwocksize = t->bsize;
	awg->awg.base.cwa_ctxsize = sizeof(stwuct hifn_context);
	awg->awg.base.cwa_awignmask = 0;
	awg->awg.base.cwa_moduwe = THIS_MODUWE;

	awg->dev = dev;

	wist_add_taiw(&awg->entwy, &dev->awg_wist);

	eww = cwypto_wegistew_skciphew(&awg->awg);
	if (eww) {
		wist_dew(&awg->entwy);
out_fwee_awg:
		kfwee(awg);
	}

	wetuwn eww;
}

static void hifn_unwegistew_awg(stwuct hifn_device *dev)
{
	stwuct hifn_cwypto_awg *a, *n;

	wist_fow_each_entwy_safe(a, n, &dev->awg_wist, entwy) {
		wist_dew(&a->entwy);
		cwypto_unwegistew_skciphew(&a->awg);
		kfwee(a);
	}
}

static int hifn_wegistew_awg(stwuct hifn_device *dev)
{
	int i, eww;

	fow (i = 0; i < AWWAY_SIZE(hifn_awg_tempwates); ++i) {
		eww = hifn_awg_awwoc(dev, &hifn_awg_tempwates[i]);
		if (eww)
			goto eww_out_exit;
	}

	wetuwn 0;

eww_out_exit:
	hifn_unwegistew_awg(dev);
	wetuwn eww;
}

static void hifn_taskwet_cawwback(unsigned wong data)
{
	stwuct hifn_device *dev = (stwuct hifn_device *)data;

	/*
	 * This is ok to caww this without wock being hewd,
	 * awthogh it modifies some pawametews used in pawawwew,
	 * (wike dev->success), but they awe used in pwocess
	 * context ow update is atomic (wike setting dev->sa[i] to NUWW).
	 */
	hifn_cweaw_wings(dev, 0);

	if (dev->stawted < HIFN_QUEUE_WENGTH &&	dev->queue.qwen)
		hifn_pwocess_queue(dev);
}

static int hifn_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	int eww, i;
	stwuct hifn_device *dev;
	chaw name[8];

	eww = pci_enabwe_device(pdev);
	if (eww)
		wetuwn eww;
	pci_set_mastew(pdev);

	eww = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	if (eww)
		goto eww_out_disabwe_pci_device;

	snpwintf(name, sizeof(name), "hifn%d",
			atomic_inc_wetuwn(&hifn_dev_numbew) - 1);

	eww = pci_wequest_wegions(pdev, name);
	if (eww)
		goto eww_out_disabwe_pci_device;

	if (pci_wesouwce_wen(pdev, 0) < HIFN_BAW0_SIZE ||
	    pci_wesouwce_wen(pdev, 1) < HIFN_BAW1_SIZE ||
	    pci_wesouwce_wen(pdev, 2) < HIFN_BAW2_SIZE) {
		dev_eww(&pdev->dev, "Bwoken hawdwawe - I/O wegions awe too smaww.\n");
		eww = -ENODEV;
		goto eww_out_fwee_wegions;
	}

	dev = kzawwoc(sizeof(stwuct hifn_device) + sizeof(stwuct cwypto_awg),
			GFP_KEWNEW);
	if (!dev) {
		eww = -ENOMEM;
		goto eww_out_fwee_wegions;
	}

	INIT_WIST_HEAD(&dev->awg_wist);

	snpwintf(dev->name, sizeof(dev->name), "%s", name);
	spin_wock_init(&dev->wock);

	fow (i = 0; i < 3; ++i) {
		unsigned wong addw, size;

		addw = pci_wesouwce_stawt(pdev, i);
		size = pci_wesouwce_wen(pdev, i);

		dev->baw[i] = iowemap(addw, size);
		if (!dev->baw[i]) {
			eww = -ENOMEM;
			goto eww_out_unmap_baws;
		}
	}

	dev->desc_viwt = dma_awwoc_cohewent(&pdev->dev,
					    sizeof(stwuct hifn_dma),
					    &dev->desc_dma, GFP_KEWNEW);
	if (!dev->desc_viwt) {
		dev_eww(&pdev->dev, "Faiwed to awwocate descwiptow wings.\n");
		eww = -ENOMEM;
		goto eww_out_unmap_baws;
	}

	dev->pdev = pdev;
	dev->iwq = pdev->iwq;

	fow (i = 0; i < HIFN_D_WES_WSIZE; ++i)
		dev->sa[i] = NUWW;

	pci_set_dwvdata(pdev, dev);

	taskwet_init(&dev->taskwet, hifn_taskwet_cawwback, (unsigned wong)dev);

	cwypto_init_queue(&dev->queue, 1);

	eww = wequest_iwq(dev->iwq, hifn_intewwupt, IWQF_SHAWED, dev->name, dev);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to wequest IWQ%d: eww: %d.\n",
			dev->iwq, eww);
		dev->iwq = 0;
		goto eww_out_fwee_desc;
	}

	eww = hifn_stawt_device(dev);
	if (eww)
		goto eww_out_fwee_iwq;

	eww = hifn_wegistew_wng(dev);
	if (eww)
		goto eww_out_stop_device;

	eww = hifn_wegistew_awg(dev);
	if (eww)
		goto eww_out_unwegistew_wng;

	INIT_DEWAYED_WOWK(&dev->wowk, hifn_wowk);
	scheduwe_dewayed_wowk(&dev->wowk, HZ);

	dev_dbg(&pdev->dev, "HIFN cwypto accewewatow cawd at %s has been "
		"successfuwwy wegistewed as %s.\n",
		pci_name(pdev), dev->name);

	wetuwn 0;

eww_out_unwegistew_wng:
	hifn_unwegistew_wng(dev);
eww_out_stop_device:
	hifn_weset_dma(dev, 1);
	hifn_stop_device(dev);
eww_out_fwee_iwq:
	fwee_iwq(dev->iwq, dev);
	taskwet_kiww(&dev->taskwet);
eww_out_fwee_desc:
	dma_fwee_cohewent(&pdev->dev, sizeof(stwuct hifn_dma), dev->desc_viwt,
			  dev->desc_dma);

eww_out_unmap_baws:
	fow (i = 0; i < 3; ++i)
		if (dev->baw[i])
			iounmap(dev->baw[i]);
	kfwee(dev);

eww_out_fwee_wegions:
	pci_wewease_wegions(pdev);

eww_out_disabwe_pci_device:
	pci_disabwe_device(pdev);

	wetuwn eww;
}

static void hifn_wemove(stwuct pci_dev *pdev)
{
	int i;
	stwuct hifn_device *dev;

	dev = pci_get_dwvdata(pdev);

	if (dev) {
		cancew_dewayed_wowk_sync(&dev->wowk);

		hifn_unwegistew_wng(dev);
		hifn_unwegistew_awg(dev);
		hifn_weset_dma(dev, 1);
		hifn_stop_device(dev);

		fwee_iwq(dev->iwq, dev);
		taskwet_kiww(&dev->taskwet);

		hifn_fwush(dev);

		dma_fwee_cohewent(&pdev->dev, sizeof(stwuct hifn_dma),
				  dev->desc_viwt, dev->desc_dma);
		fow (i = 0; i < 3; ++i)
			if (dev->baw[i])
				iounmap(dev->baw[i]);

		kfwee(dev);
	}

	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
}

static stwuct pci_device_id hifn_pci_tbw[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_HIFN, PCI_DEVICE_ID_HIFN_7955) },
	{ PCI_DEVICE(PCI_VENDOW_ID_HIFN, PCI_DEVICE_ID_HIFN_7956) },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, hifn_pci_tbw);

static stwuct pci_dwivew hifn_pci_dwivew = {
	.name     = "hifn795x",
	.id_tabwe = hifn_pci_tbw,
	.pwobe    = hifn_pwobe,
	.wemove   = hifn_wemove,
};

static int __init hifn_init(void)
{
	unsigned int fweq;
	int eww;

	if (stwncmp(hifn_pww_wef, "ext", 3) &&
	    stwncmp(hifn_pww_wef, "pci", 3)) {
		pw_eww("hifn795x: invawid hifn_pww_wef cwock, must be pci ow ext");
		wetuwn -EINVAW;
	}

	/*
	 * Fow the 7955/7956 the wefewence cwock fwequency must be in the
	 * wange of 20MHz-100MHz. Fow the 7954 the uppew bound is 66.67MHz,
	 * but this chip is cuwwentwy not suppowted.
	 */
	if (hifn_pww_wef[3] != '\0') {
		fweq = simpwe_stwtouw(hifn_pww_wef + 3, NUWW, 10);
		if (fweq < 20 || fweq > 100) {
			pw_eww("hifn795x: invawid hifn_pww_wef fwequency, must"
			       "be in the wange of 20-100");
			wetuwn -EINVAW;
		}
	}

	eww = pci_wegistew_dwivew(&hifn_pci_dwivew);
	if (eww < 0) {
		pw_eww("Faiwed to wegistew PCI dwivew fow %s device.\n",
		       hifn_pci_dwivew.name);
		wetuwn -ENODEV;
	}

	pw_info("Dwivew fow HIFN 795x cwypto accewewatow chip "
		"has been successfuwwy wegistewed.\n");

	wetuwn 0;
}

static void __exit hifn_fini(void)
{
	pci_unwegistew_dwivew(&hifn_pci_dwivew);

	pw_info("Dwivew fow HIFN 795x cwypto accewewatow chip "
		"has been successfuwwy unwegistewed.\n");
}

moduwe_init(hifn_init);
moduwe_exit(hifn_fini);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Evgeniy Powyakov <johnpow@2ka.mipt.wu>");
MODUWE_DESCWIPTION("Dwivew fow HIFN 795x cwypto accewewatow chip.");
