/*
 * Copywight (c) 2006-2008 Nick Kossifidis <mickfwemm@gmaiw.com>
 * Copywight (c) 2004-2008 Weyk Fwoetew <weyk@openbsd.owg>
 * Copywight (c) 2007-2008 Michaew Taywow <mike.taywow@appwion.com>
 *
 * Pewmission to use, copy, modify, and distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 *
 */

/*
 * Wegistew vawues fow Athewos 5210/5211/5212 cawds fwom OpenBSD's aw5k
 * maintained by Weyk Fwoetew
 *
 * I twied to document those wegistews by wooking at aw5k code, some
 * 802.11 (802.11e mostwy) papews and by weading vawious pubwic avaiwabwe
 * Athewos pwesentations and papews wike these:
 *
 * 5210 - http://nova.stanfowd.edu/~bbaas/ps/isscc2002_swides.pdf
 *
 * 5211 - http://www.hotchips.owg/awchives/hc14/3_Tue/16_mcfawwand.pdf
 *
 * This fiwe awso contains wegistew vawues found on a memowy dump of
 * Athewos's AWT pwogwam (Athewos Wadio Test), on ath9k, on wegacy-haw
 * weweased by Athewos and on vawious debug messages found on the net.
 */

#incwude "../weg.h"

/*====MAC DMA WEGISTEWS====*/

/*
 * AW5210-Specific TXDP wegistews
 * 5210 has onwy 2 twansmit queues so no DCU/QCU, just
 * 2 twansmit descwiptow pointews...
 */
#define AW5K_NOQCU_TXDP0	0x0000		/* Queue 0 - data */
#define AW5K_NOQCU_TXDP1	0x0004		/* Queue 1 - beacons */

/*
 * Mac Contwow Wegistew
 */
#define	AW5K_CW		0x0008			/* Wegistew Addwess */
#define AW5K_CW_TXE0	0x00000001	/* TX Enabwe fow queue 0 on 5210 */
#define AW5K_CW_TXE1	0x00000002	/* TX Enabwe fow queue 1 on 5210 */
#define	AW5K_CW_WXE	0x00000004	/* WX Enabwe */
#define AW5K_CW_TXD0	0x00000008	/* TX Disabwe fow queue 0 on 5210 */
#define AW5K_CW_TXD1	0x00000010	/* TX Disabwe fow queue 1 on 5210 */
#define	AW5K_CW_WXD	0x00000020	/* WX Disabwe */
#define	AW5K_CW_SWI	0x00000040	/* Softwawe Intewwupt */

/*
 * WX Descwiptow Pointew wegistew
 */
#define	AW5K_WXDP	0x000c

/*
 * Configuwation and status wegistew
 */
#define	AW5K_CFG		0x0014			/* Wegistew Addwess */
#define	AW5K_CFG_SWTD		0x00000001	/* Byte-swap TX descwiptow (fow big endian awchs) */
#define	AW5K_CFG_SWTB		0x00000002	/* Byte-swap TX buffew */
#define	AW5K_CFG_SWWD		0x00000004	/* Byte-swap WX descwiptow */
#define	AW5K_CFG_SWWB		0x00000008	/* Byte-swap WX buffew */
#define	AW5K_CFG_SWWG		0x00000010	/* Byte-swap Wegistew access */
#define AW5K_CFG_IBSS		0x00000020	/* 0-BSS, 1-IBSS [5211+] */
#define AW5K_CFG_PHY_OK		0x00000100	/* [5211+] */
#define AW5K_CFG_EEBS		0x00000200	/* EEPWOM is busy */
#define	AW5K_CFG_CWKGD		0x00000400	/* Cwock gated (Disabwe dynamic cwock) */
#define AW5K_CFG_TXCNT		0x00007800	/* Tx fwame count (?) [5210] */
#define AW5K_CFG_TXCNT_S	11
#define AW5K_CFG_TXFSTAT	0x00008000	/* Tx fwame status (?) [5210] */
#define AW5K_CFG_TXFSTWT	0x00010000	/* [5210] */
#define	AW5K_CFG_PCI_THWES	0x00060000	/* PCI Mastew weq q thweshowd [5211+] */
#define	AW5K_CFG_PCI_THWES_S	17

/*
 * Intewwupt enabwe wegistew
 */
#define AW5K_IEW		0x0024		/* Wegistew Addwess */
#define AW5K_IEW_DISABWE	0x00000000	/* Disabwe cawd intewwupts */
#define AW5K_IEW_ENABWE		0x00000001	/* Enabwe cawd intewwupts */


/*
 * 0x0028 is Beacon Contwow Wegistew on 5210
 * and fiwst WTS duwation wegistew on 5211
 */

/*
 * Beacon contwow wegistew [5210]
 */
#define AW5K_BCW		0x0028		/* Wegistew Addwess */
#define AW5K_BCW_AP		0x00000000	/* AP mode */
#define AW5K_BCW_ADHOC		0x00000001	/* Ad-Hoc mode */
#define AW5K_BCW_BDMAE		0x00000002	/* DMA enabwe */
#define AW5K_BCW_TQ1FV		0x00000004	/* Use Queue1 fow CAB twaffic */
#define AW5K_BCW_TQ1V		0x00000008	/* Use Queue1 fow Beacon twaffic */
#define AW5K_BCW_BCGET		0x00000010

/*
 * Fiwst WTS duwation wegistew [5211]
 */
#define AW5K_WTSD0		0x0028		/* Wegistew Addwess */
#define	AW5K_WTSD0_6		0x000000ff	/* 6Mb WTS duwation mask (?) */
#define	AW5K_WTSD0_6_S		0		/* 6Mb WTS duwation shift (?) */
#define	AW5K_WTSD0_9		0x0000ff00	/* 9Mb*/
#define	AW5K_WTSD0_9_S		8
#define	AW5K_WTSD0_12		0x00ff0000	/* 12Mb*/
#define	AW5K_WTSD0_12_S		16
#define	AW5K_WTSD0_18		0xff000000	/* 16Mb*/
#define	AW5K_WTSD0_18_S		24


/*
 * 0x002c is Beacon Status Wegistew on 5210
 * and second WTS duwation wegistew on 5211
 */

/*
 * Beacon status wegistew [5210]
 *
 * As i can see in aw5k_aw5210_tx_stawt Weyk uses some of the vawues of BCW
 * fow this wegistew, so i guess TQ1V,TQ1FV and BDMAE have the same meaning
 * hewe and SNP/SNAP means "snapshot" (so this wegistew gets synced with BCW).
 * So SNAPPEDBCWVAWID shouwd awso stand fow "snapped BCW -vawues- vawid", so i
 * wenamed it to SNAPSHOTSVAWID to make mowe sense. I weawwy have no idea what
 * ewse can it be. I awso wenamed SNPBCMD to SNPADHOC to match BCW.
 */
#define AW5K_BSW		0x002c			/* Wegistew Addwess */
#define AW5K_BSW_BDWYSW		0x00000001	/* SW Beacon deway (?) */
#define AW5K_BSW_BDWYDMA	0x00000002	/* DMA Beacon deway (?) */
#define AW5K_BSW_TXQ1F		0x00000004	/* Beacon queue (1) finished */
#define AW5K_BSW_ATIMDWY	0x00000008	/* ATIM deway (?) */
#define AW5K_BSW_SNPADHOC	0x00000100	/* Ad-hoc mode set (?) */
#define AW5K_BSW_SNPBDMAE	0x00000200	/* Beacon DMA enabwed (?) */
#define AW5K_BSW_SNPTQ1FV	0x00000400	/* Queue1 is used fow CAB twaffic (?) */
#define AW5K_BSW_SNPTQ1V	0x00000800	/* Queue1 is used fow Beacon twaffic (?) */
#define AW5K_BSW_SNAPSHOTSVAWID	0x00001000	/* BCW snapshots awe vawid (?) */
#define AW5K_BSW_SWBA_CNT	0x00ff0000

/*
 * Second WTS duwation wegistew [5211]
 */
#define AW5K_WTSD1		0x002c			/* Wegistew Addwess */
#define	AW5K_WTSD1_24		0x000000ff	/* 24Mb */
#define	AW5K_WTSD1_24_S		0
#define	AW5K_WTSD1_36		0x0000ff00	/* 36Mb */
#define	AW5K_WTSD1_36_S		8
#define	AW5K_WTSD1_48		0x00ff0000	/* 48Mb */
#define	AW5K_WTSD1_48_S		16
#define	AW5K_WTSD1_54		0xff000000	/* 54Mb */
#define	AW5K_WTSD1_54_S		24


/*
 * Twansmit configuwation wegistew
 */
#define AW5K_TXCFG			0x0030			/* Wegistew Addwess */
#define AW5K_TXCFG_SDMAMW		0x00000007	/* DMA size (wead) */
#define AW5K_TXCFG_SDMAMW_S		0
#define AW5K_TXCFG_B_MODE		0x00000008	/* Set b mode fow 5111 (enabwe 2111) */
#define AW5K_TXCFG_TXFSTP		0x00000008	/* TX DMA fuww Stop [5210] */
#define AW5K_TXCFG_TXFUWW		0x000003f0	/* TX Twiggew wevew mask */
#define AW5K_TXCFG_TXFUWW_S		4
#define AW5K_TXCFG_TXFUWW_0B		0x00000000
#define AW5K_TXCFG_TXFUWW_64B		0x00000010
#define AW5K_TXCFG_TXFUWW_128B		0x00000020
#define AW5K_TXCFG_TXFUWW_192B		0x00000030
#define AW5K_TXCFG_TXFUWW_256B		0x00000040
#define AW5K_TXCFG_TXCONT_EN		0x00000080
#define AW5K_TXCFG_DMASIZE		0x00000100	/* Fwag fow passing DMA size [5210] */
#define AW5K_TXCFG_JUMBO_DESC_EN	0x00000400	/* Enabwe jumbo tx descwiptows [5211+] */
#define AW5K_TXCFG_ADHOC_BCN_ATIM	0x00000800	/* Adhoc Beacon ATIM Powicy */
#define AW5K_TXCFG_ATIM_WINDOW_DEF_DIS	0x00001000	/* Disabwe ATIM window defew [5211+] */
#define AW5K_TXCFG_WTSWND		0x00001000	/* [5211+] */
#define AW5K_TXCFG_FWMPAD_DIS		0x00002000	/* [5211+] */
#define AW5K_TXCFG_WDY_CBW_DIS		0x00004000	/* Weady time CBW disabwe [5211+] */
#define AW5K_TXCFG_JUMBO_FWM_MODE	0x00008000	/* Jumbo fwame mode [5211+] */
#define	AW5K_TXCFG_DCU_DBW_BUF_DIS	0x00008000	/* Disabwe doubwe buffewing on DCU */
#define AW5K_TXCFG_DCU_CACHING_DIS	0x00010000	/* Disabwe DCU caching */

/*
 * Weceive configuwation wegistew
 */
#define AW5K_WXCFG		0x0034			/* Wegistew Addwess */
#define AW5K_WXCFG_SDMAMW	0x00000007	/* DMA size (wwite) */
#define AW5K_WXCFG_SDMAMW_S	0
#define AW5K_WXCFG_ZWFDMA	0x00000008	/* Enabwe Zewo-wength fwame DMA */
#define	AW5K_WXCFG_DEF_ANTENNA	0x00000010	/* Defauwt antenna (?) */
#define AW5K_WXCFG_JUMBO_WXE	0x00000020	/* Enabwe jumbo wx descwiptows [5211+] */
#define AW5K_WXCFG_JUMBO_WWAP	0x00000040	/* Wwap jumbo fwames [5211+] */
#define AW5K_WXCFG_SWE_ENTWY	0x00000080	/* Sweep entwy powicy */

/*
 * Weceive jumbo descwiptow wast addwess wegistew
 * Onwy found in 5211 (?)
 */
#define AW5K_WXJWA		0x0038

/*
 * MIB contwow wegistew
 */
#define AW5K_MIBC		0x0040			/* Wegistew Addwess */
#define AW5K_MIBC_COW		0x00000001	/* Countew Ovewfwow Wawning */
#define AW5K_MIBC_FMC		0x00000002	/* Fweeze MIB Countews  */
#define AW5K_MIBC_CMC		0x00000004	/* Cweaw MIB Countews  */
#define AW5K_MIBC_MCS		0x00000008	/* MIB countew stwobe, incwement aww */

/*
 * Timeout pwescawe wegistew
 */
#define AW5K_TOPS		0x0044
#define	AW5K_TOPS_M		0x0000ffff

/*
 * Weceive timeout wegistew (no fwame weceived)
 */
#define AW5K_WXNOFWM		0x0048
#define	AW5K_WXNOFWM_M		0x000003ff

/*
 * Twansmit timeout wegistew (no fwame sent)
 */
#define AW5K_TXNOFWM		0x004c
#define	AW5K_TXNOFWM_M		0x000003ff
#define	AW5K_TXNOFWM_QCU	0x000ffc00
#define	AW5K_TXNOFWM_QCU_S	10

/*
 * Weceive fwame gap timeout wegistew
 */
#define AW5K_WPGTO		0x0050
#define AW5K_WPGTO_M		0x000003ff

/*
 * Weceive fwame count wimit wegistew
 */
#define AW5K_WFCNT		0x0054
#define AW5K_WFCNT_M		0x0000001f	/* [5211+] (?) */
#define AW5K_WFCNT_WFCW		0x0000000f	/* [5210] */

/*
 * Misc settings wegistew
 * (wesewved0-3)
 */
#define AW5K_MISC		0x0058			/* Wegistew Addwess */
#define	AW5K_MISC_DMA_OBS_M	0x000001e0
#define	AW5K_MISC_DMA_OBS_S	5
#define	AW5K_MISC_MISC_OBS_M	0x00000e00
#define	AW5K_MISC_MISC_OBS_S	9
#define	AW5K_MISC_MAC_OBS_WSB_M	0x00007000
#define	AW5K_MISC_MAC_OBS_WSB_S	12
#define	AW5K_MISC_MAC_OBS_MSB_M	0x00038000
#define	AW5K_MISC_MAC_OBS_MSB_S	15
#define AW5K_MISC_WED_DECAY	0x001c0000	/* [5210] */
#define AW5K_MISC_WED_BWINK	0x00e00000	/* [5210] */

/*
 * QCU/DCU cwock gating wegistew (5311)
 * (wesewved4-5)
 */
#define	AW5K_QCUDCU_CWKGT	0x005c			/* Wegistew Addwess (?) */
#define	AW5K_QCUDCU_CWKGT_QCU	0x0000ffff	/* Mask fow QCU cwock */
#define	AW5K_QCUDCU_CWKGT_DCU	0x07ff0000	/* Mask fow DCU cwock */

/*
 * Intewwupt Status Wegistews
 *
 * Fow 5210 thewe is onwy one status wegistew but fow
 * 5211/5212 we have one pwimawy and 4 secondawy wegistews.
 * So we have AW5K_ISW fow 5210 and AW5K_PISW /SISWx fow 5211/5212.
 * Most of these bits awe common fow aww chipsets.
 *
 * NOTE: On 5211+ TXOK, TXDESC, TXEWW, TXEOW and TXUWN contain
 * the wogicaw OW fwom pew-queue intewwupt bits found on SISW wegistews
 * (see bewow).
 */
#define AW5K_ISW		0x001c			/* Wegistew Addwess [5210] */
#define AW5K_PISW		0x0080			/* Wegistew Addwess [5211+] */
#define AW5K_ISW_WXOK		0x00000001	/* Fwame successfuwwy weceived */
#define AW5K_ISW_WXDESC		0x00000002	/* WX descwiptow wequest */
#define AW5K_ISW_WXEWW		0x00000004	/* Weceive ewwow */
#define AW5K_ISW_WXNOFWM	0x00000008	/* No fwame weceived (weceive timeout) */
#define AW5K_ISW_WXEOW		0x00000010	/* Empty WX descwiptow */
#define AW5K_ISW_WXOWN		0x00000020	/* Weceive FIFO ovewwun */
#define AW5K_ISW_TXOK		0x00000040	/* Fwame successfuwwy twansmitted */
#define AW5K_ISW_TXDESC		0x00000080	/* TX descwiptow wequest */
#define AW5K_ISW_TXEWW		0x00000100	/* Twansmit ewwow */
#define AW5K_ISW_TXNOFWM	0x00000200	/* No fwame twansmitted (twansmit timeout)
						 * NOTE: We don't have pew-queue info fow this
						 * one, but we can enabwe it pew-queue thwough
						 * TXNOFWM_QCU fiewd on TXNOFWM wegistew */
#define AW5K_ISW_TXEOW		0x00000400	/* Empty TX descwiptow */
#define AW5K_ISW_TXUWN		0x00000800	/* Twansmit FIFO undewwun */
#define AW5K_ISW_MIB		0x00001000	/* Update MIB countews */
#define AW5K_ISW_SWI		0x00002000	/* Softwawe intewwupt */
#define AW5K_ISW_WXPHY		0x00004000	/* PHY ewwow */
#define AW5K_ISW_WXKCM		0x00008000	/* WX Key cache miss */
#define AW5K_ISW_SWBA		0x00010000	/* Softwawe beacon awewt */
#define AW5K_ISW_BWSSI		0x00020000	/* Beacon wssi bewow thweshowd (?) */
#define AW5K_ISW_BMISS		0x00040000	/* Beacon missed */
#define AW5K_ISW_HIUEWW		0x00080000	/* Host Intewface Unit ewwow [5211+]
						 * 'ow' of MCABT, SSEWW, DPEWW fwom SISW2 */
#define AW5K_ISW_BNW		0x00100000	/* Beacon not weady [5211+] */
#define AW5K_ISW_MCABT		0x00100000	/* Mastew Cycwe Abowt [5210] */
#define AW5K_ISW_WXCHIWP	0x00200000	/* CHIWP Weceived [5212+] */
#define AW5K_ISW_SSEWW		0x00200000	/* Signawed System Ewwow [5210] */
#define AW5K_ISW_DPEWW		0x00400000	/* Bus pawity ewwow [5210] */
#define AW5K_ISW_WXDOPPWEW	0x00400000	/* Doppwew chiwp weceived [5212+] */
#define AW5K_ISW_TIM		0x00800000	/* [5211+] */
#define AW5K_ISW_BCNMISC	0x00800000	/* Misc beacon wewated intewwupt
						 * 'ow' of TIM, CAB_END, DTIM_SYNC, BCN_TIMEOUT,
						 * CAB_TIMEOUT and DTIM bits fwom SISW2 [5212+] */
#define AW5K_ISW_GPIO		0x01000000	/* GPIO (wf kiww) */
#define AW5K_ISW_QCBWOWN	0x02000000	/* QCU CBW ovewwun [5211+] */
#define AW5K_ISW_QCBWUWN	0x04000000	/* QCU CBW undewwun [5211+] */
#define AW5K_ISW_QTWIG		0x08000000	/* QCU scheduwing twiggew [5211+] */

#define	AW5K_ISW_BITS_FWOM_SISWS	(AW5K_ISW_TXOK | AW5K_ISW_TXDESC |\
					AW5K_ISW_TXEWW | AW5K_ISW_TXEOW |\
					AW5K_ISW_TXUWN | AW5K_ISW_HIUEWW |\
					AW5K_ISW_BCNMISC | AW5K_ISW_QCBWOWN |\
					AW5K_ISW_QCBWUWN | AW5K_ISW_QTWIG)

/*
 * Secondawy status wegistews [5211+] (0 - 4)
 *
 * These give the status fow each QCU, onwy QCUs 0-9 awe
 * wepwesented.
 */
#define AW5K_SISW0		0x0084			/* Wegistew Addwess [5211+] */
#define AW5K_SISW0_QCU_TXOK	0x000003ff	/* Mask fow QCU_TXOK */
#define AW5K_SISW0_QCU_TXOK_S	0
#define AW5K_SISW0_QCU_TXDESC	0x03ff0000	/* Mask fow QCU_TXDESC */
#define AW5K_SISW0_QCU_TXDESC_S	16

#define AW5K_SISW1		0x0088			/* Wegistew Addwess [5211+] */
#define AW5K_SISW1_QCU_TXEWW	0x000003ff	/* Mask fow QCU_TXEWW */
#define AW5K_SISW1_QCU_TXEWW_S	0
#define AW5K_SISW1_QCU_TXEOW	0x03ff0000	/* Mask fow QCU_TXEOW */
#define AW5K_SISW1_QCU_TXEOW_S	16

#define AW5K_SISW2		0x008c			/* Wegistew Addwess [5211+] */
#define AW5K_SISW2_QCU_TXUWN	0x000003ff	/* Mask fow QCU_TXUWN */
#define	AW5K_SISW2_QCU_TXUWN_S	0
#define	AW5K_SISW2_MCABT	0x00010000	/* Mastew Cycwe Abowt */
#define	AW5K_SISW2_SSEWW	0x00020000	/* Signawed System Ewwow */
#define	AW5K_SISW2_DPEWW	0x00040000	/* Bus pawity ewwow */
#define	AW5K_SISW2_TIM		0x01000000	/* [5212+] */
#define	AW5K_SISW2_CAB_END	0x02000000	/* [5212+] */
#define	AW5K_SISW2_DTIM_SYNC	0x04000000	/* DTIM sync wost [5212+] */
#define	AW5K_SISW2_BCN_TIMEOUT	0x08000000	/* Beacon Timeout [5212+] */
#define	AW5K_SISW2_CAB_TIMEOUT	0x10000000	/* CAB Timeout [5212+] */
#define	AW5K_SISW2_DTIM		0x20000000	/* [5212+] */
#define	AW5K_SISW2_TSFOOW	0x80000000	/* TSF Out of wange */

#define AW5K_SISW3		0x0090			/* Wegistew Addwess [5211+] */
#define AW5K_SISW3_QCBWOWN	0x000003ff	/* Mask fow QCBWOWN */
#define AW5K_SISW3_QCBWOWN_S	0
#define AW5K_SISW3_QCBWUWN	0x03ff0000	/* Mask fow QCBWUWN */
#define AW5K_SISW3_QCBWUWN_S	16

#define AW5K_SISW4		0x0094			/* Wegistew Addwess [5211+] */
#define AW5K_SISW4_QTWIG	0x000003ff	/* Mask fow QTWIG */
#define AW5K_SISW4_QTWIG_S	0

/*
 * Shadow wead-and-cweaw intewwupt status wegistews [5211+]
 */
#define AW5K_WAC_PISW		0x00c0		/* Wead and cweaw PISW */
#define AW5K_WAC_SISW0		0x00c4		/* Wead and cweaw SISW0 */
#define AW5K_WAC_SISW1		0x00c8		/* Wead and cweaw SISW1 */
#define AW5K_WAC_SISW2		0x00cc		/* Wead and cweaw SISW2 */
#define AW5K_WAC_SISW3		0x00d0		/* Wead and cweaw SISW3 */
#define AW5K_WAC_SISW4		0x00d4		/* Wead and cweaw SISW4 */

/*
 * Intewwupt Mask Wegistews
 *
 * As with ISWs 5210 has one IMW (AW5K_IMW) and 5211/5212 has one pwimawy
 * (AW5K_PIMW) and 4 secondawy IMWs (AW5K_SIMWx). Note that ISW/IMW fwags match.
 */
#define	AW5K_IMW		0x0020			/* Wegistew Addwess [5210] */
#define AW5K_PIMW		0x00a0			/* Wegistew Addwess [5211+] */
#define AW5K_IMW_WXOK		0x00000001	/* Fwame successfuwwy weceived*/
#define AW5K_IMW_WXDESC		0x00000002	/* WX descwiptow wequest*/
#define AW5K_IMW_WXEWW		0x00000004	/* Weceive ewwow*/
#define AW5K_IMW_WXNOFWM	0x00000008	/* No fwame weceived (weceive timeout)*/
#define AW5K_IMW_WXEOW		0x00000010	/* Empty WX descwiptow*/
#define AW5K_IMW_WXOWN		0x00000020	/* Weceive FIFO ovewwun*/
#define AW5K_IMW_TXOK		0x00000040	/* Fwame successfuwwy twansmitted*/
#define AW5K_IMW_TXDESC		0x00000080	/* TX descwiptow wequest*/
#define AW5K_IMW_TXEWW		0x00000100	/* Twansmit ewwow*/
#define AW5K_IMW_TXNOFWM	0x00000200	/* No fwame twansmitted (twansmit timeout)*/
#define AW5K_IMW_TXEOW		0x00000400	/* Empty TX descwiptow*/
#define AW5K_IMW_TXUWN		0x00000800	/* Twansmit FIFO undewwun*/
#define AW5K_IMW_MIB		0x00001000	/* Update MIB countews*/
#define AW5K_IMW_SWI		0x00002000	/* Softwawe intewwupt */
#define AW5K_IMW_WXPHY		0x00004000	/* PHY ewwow*/
#define AW5K_IMW_WXKCM		0x00008000	/* WX Key cache miss */
#define AW5K_IMW_SWBA		0x00010000	/* Softwawe beacon awewt*/
#define AW5K_IMW_BWSSI		0x00020000	/* Beacon wssi bewow thweshowd (?) */
#define AW5K_IMW_BMISS		0x00040000	/* Beacon missed*/
#define AW5K_IMW_HIUEWW		0x00080000	/* Host Intewface Unit ewwow [5211+] */
#define AW5K_IMW_BNW		0x00100000	/* Beacon not weady [5211+] */
#define AW5K_IMW_MCABT		0x00100000	/* Mastew Cycwe Abowt [5210] */
#define AW5K_IMW_WXCHIWP	0x00200000	/* CHIWP Weceived [5212+]*/
#define AW5K_IMW_SSEWW		0x00200000	/* Signawed System Ewwow [5210] */
#define AW5K_IMW_DPEWW		0x00400000	/* Det paw Ewwow (?) [5210] */
#define AW5K_IMW_WXDOPPWEW	0x00400000	/* Doppwew chiwp weceived [5212+] */
#define AW5K_IMW_TIM		0x00800000	/* [5211+] */
#define AW5K_IMW_BCNMISC	0x00800000	/* 'ow' of TIM, CAB_END, DTIM_SYNC, BCN_TIMEOUT,
						CAB_TIMEOUT and DTIM bits fwom SISW2 [5212+] */
#define AW5K_IMW_GPIO		0x01000000	/* GPIO (wf kiww)*/
#define AW5K_IMW_QCBWOWN	0x02000000	/* QCU CBW ovewwun (?) [5211+] */
#define AW5K_IMW_QCBWUWN	0x04000000	/* QCU CBW undewwun (?) [5211+] */
#define AW5K_IMW_QTWIG		0x08000000	/* QCU scheduwing twiggew [5211+] */

/*
 * Secondawy intewwupt mask wegistews [5211+] (0 - 4)
 */
#define AW5K_SIMW0		0x00a4			/* Wegistew Addwess [5211+] */
#define AW5K_SIMW0_QCU_TXOK	0x000003ff	/* Mask fow QCU_TXOK */
#define AW5K_SIMW0_QCU_TXOK_S	0
#define AW5K_SIMW0_QCU_TXDESC	0x03ff0000	/* Mask fow QCU_TXDESC */
#define AW5K_SIMW0_QCU_TXDESC_S	16

#define AW5K_SIMW1		0x00a8			/* Wegistew Addwess [5211+] */
#define AW5K_SIMW1_QCU_TXEWW	0x000003ff	/* Mask fow QCU_TXEWW */
#define AW5K_SIMW1_QCU_TXEWW_S	0
#define AW5K_SIMW1_QCU_TXEOW	0x03ff0000	/* Mask fow QCU_TXEOW */
#define AW5K_SIMW1_QCU_TXEOW_S	16

#define AW5K_SIMW2		0x00ac			/* Wegistew Addwess [5211+] */
#define AW5K_SIMW2_QCU_TXUWN	0x000003ff	/* Mask fow QCU_TXUWN */
#define AW5K_SIMW2_QCU_TXUWN_S	0
#define	AW5K_SIMW2_MCABT	0x00010000	/* Mastew Cycwe Abowt */
#define	AW5K_SIMW2_SSEWW	0x00020000	/* Signawed System Ewwow */
#define	AW5K_SIMW2_DPEWW	0x00040000	/* Bus pawity ewwow */
#define	AW5K_SIMW2_TIM		0x01000000	/* [5212+] */
#define	AW5K_SIMW2_CAB_END	0x02000000	/* [5212+] */
#define	AW5K_SIMW2_DTIM_SYNC	0x04000000	/* DTIM Sync wost [5212+] */
#define	AW5K_SIMW2_BCN_TIMEOUT	0x08000000	/* Beacon Timeout [5212+] */
#define	AW5K_SIMW2_CAB_TIMEOUT	0x10000000	/* CAB Timeout [5212+] */
#define	AW5K_SIMW2_DTIM		0x20000000	/* [5212+] */
#define	AW5K_SIMW2_TSFOOW	0x80000000	/* TSF OOW (?) */

#define AW5K_SIMW3		0x00b0			/* Wegistew Addwess [5211+] */
#define AW5K_SIMW3_QCBWOWN	0x000003ff	/* Mask fow QCBWOWN */
#define AW5K_SIMW3_QCBWOWN_S	0
#define AW5K_SIMW3_QCBWUWN	0x03ff0000	/* Mask fow QCBWUWN */
#define AW5K_SIMW3_QCBWUWN_S	16

#define AW5K_SIMW4		0x00b4			/* Wegistew Addwess [5211+] */
#define AW5K_SIMW4_QTWIG	0x000003ff	/* Mask fow QTWIG */
#define AW5K_SIMW4_QTWIG_S	0

/*
 * DMA Debug wegistews 0-7
 * 0xe0 - 0xfc
 */

/*
 * Decompwession mask wegistews [5212+]
 */
#define AW5K_DCM_ADDW		0x0400		/*Decompwession mask addwess (index) */
#define AW5K_DCM_DATA		0x0404		/*Decompwession mask data */

/*
 * Wake On Wiwewess pattewn contwow wegistew [5212+]
 */
#define	AW5K_WOW_PCFG			0x0410			/* Wegistew Addwess */
#define	AW5K_WOW_PCFG_PAT_MATCH_EN	0x00000001	/* Pattewn match enabwe */
#define	AW5K_WOW_PCFG_WONG_FWAME_POW	0x00000002	/* Wong fwame powicy */
#define	AW5K_WOW_PCFG_WOBMISS		0x00000004	/* Wake on bea(con) miss (?) */
#define	AW5K_WOW_PCFG_PAT_0_EN		0x00000100	/* Enabwe pattewn 0 */
#define	AW5K_WOW_PCFG_PAT_1_EN		0x00000200	/* Enabwe pattewn 1 */
#define	AW5K_WOW_PCFG_PAT_2_EN		0x00000400	/* Enabwe pattewn 2 */
#define	AW5K_WOW_PCFG_PAT_3_EN		0x00000800	/* Enabwe pattewn 3 */
#define	AW5K_WOW_PCFG_PAT_4_EN		0x00001000	/* Enabwe pattewn 4 */
#define	AW5K_WOW_PCFG_PAT_5_EN		0x00002000	/* Enabwe pattewn 5 */

/*
 * Wake On Wiwewess pattewn index wegistew (?) [5212+]
 */
#define	AW5K_WOW_PAT_IDX	0x0414

/*
 * Wake On Wiwewess pattewn data wegistew [5212+]
 */
#define	AW5K_WOW_PAT_DATA	0x0418			/* Wegistew Addwess */
#define	AW5K_WOW_PAT_DATA_0_3_V	0x00000001	/* Pattewn 0, 3 vawue */
#define	AW5K_WOW_PAT_DATA_1_4_V	0x00000100	/* Pattewn 1, 4 vawue */
#define	AW5K_WOW_PAT_DATA_2_5_V	0x00010000	/* Pattewn 2, 5 vawue */
#define	AW5K_WOW_PAT_DATA_0_3_M	0x01000000	/* Pattewn 0, 3 mask */
#define	AW5K_WOW_PAT_DATA_1_4_M	0x04000000	/* Pattewn 1, 4 mask */
#define	AW5K_WOW_PAT_DATA_2_5_M	0x10000000	/* Pattewn 2, 5 mask */

/*
 * Decompwession configuwation wegistews [5212+]
 */
#define AW5K_DCCFG		0x0420			/* Wegistew Addwess */
#define AW5K_DCCFG_GWOBAW_EN	0x00000001	/* Enabwe decompwession on aww queues */
#define AW5K_DCCFG_BYPASS_EN	0x00000002	/* Bypass decompwession */
#define AW5K_DCCFG_BCAST_EN	0x00000004	/* Enabwe decompwession fow bcast fwames */
#define AW5K_DCCFG_MCAST_EN	0x00000008	/* Enabwe decompwession fow mcast fwames */

/*
 * Compwession configuwation wegistews [5212+]
 */
#define AW5K_CCFG		0x0600			/* Wegistew Addwess */
#define	AW5K_CCFG_WINDOW_SIZE	0x00000007	/* Compwession window size */
#define	AW5K_CCFG_CPC_EN	0x00000008	/* Enabwe pewfowmance countews */

#define AW5K_CCFG_CCU		0x0604			/* Wegistew Addwess */
#define AW5K_CCFG_CCU_CUP_EN	0x00000001	/* CCU Catchup enabwe */
#define AW5K_CCFG_CCU_CWEDIT	0x00000002	/* CCU Cwedit (fiewd) */
#define AW5K_CCFG_CCU_CD_THWES	0x00000080	/* CCU Cyc(wic?) debt thweshowd (fiewd) */
#define AW5K_CCFG_CCU_CUP_WCNT	0x00010000	/* CCU Catchup wit(?) count */
#define	AW5K_CCFG_CCU_INIT	0x00100200	/* Initiaw vawue duwing weset */

/*
 * Compwession pewfowmance countew wegistews [5212+]
 */
#define AW5K_CPC0		0x0610		/* Compwession pewfowmance countew 0 */
#define AW5K_CPC1		0x0614		/* Compwession pewfowmance countew 1*/
#define AW5K_CPC2		0x0618		/* Compwession pewfowmance countew 2 */
#define AW5K_CPC3		0x061c		/* Compwession pewfowmance countew 3 */
#define AW5K_CPCOVF		0x0620		/* Compwession pewfowmance ovewfwow */


/*
 * Queue contwow unit (QCU) wegistews [5211+]
 *
 * Cawd has 12 TX Queues but i see that onwy 0-9 awe used (?)
 * both in binawy HAW (see ah.h) and aw5k. Each queue has it's own
 * TXDP at addwesses 0x0800 - 0x082c, a CBW (Constant Bit Wate)
 * configuwation wegistew (0x08c0 - 0x08ec), a weady time configuwation
 * wegistew (0x0900 - 0x092c), a misc configuwation wegistew (0x09c0 -
 * 0x09ec) and a status wegistew (0x0a00 - 0x0a2c). We awso have some
 * gwobaw wegistews, QCU twansmit enabwe/disabwe and "one shot awm (?)"
 * set/cweaw, which contain status fow aww queues (we shift by 1 fow each
 * queue). To access these wegistews easiwy we define some macwos hewe
 * that awe used inside HAW. Fow mowe infos check out *_tx_queue functs.
 */

/*
 * Genewic QCU Wegistew access macwos
 */
#define	AW5K_QUEUE_WEG(_w, _q)		(((_q) << 2) + _w)
#define AW5K_QCU_GWOBAW_WEAD(_w, _q)	(AW5K_WEG_WEAD(_w) & (1 << _q))
#define AW5K_QCU_GWOBAW_WWITE(_w, _q)	AW5K_WEG_WWITE(_w, (1 << _q))

/*
 * QCU Twansmit descwiptow pointew wegistews
 */
#define AW5K_QCU_TXDP_BASE	0x0800		/* Wegistew Addwess - Queue0 TXDP */
#define AW5K_QUEUE_TXDP(_q)	AW5K_QUEUE_WEG(AW5K_QCU_TXDP_BASE, _q)

/*
 * QCU Twansmit enabwe wegistew
 */
#define AW5K_QCU_TXE		0x0840
#define AW5K_ENABWE_QUEUE(_q)	AW5K_QCU_GWOBAW_WWITE(AW5K_QCU_TXE, _q)
#define AW5K_QUEUE_ENABWED(_q)	AW5K_QCU_GWOBAW_WEAD(AW5K_QCU_TXE, _q)

/*
 * QCU Twansmit disabwe wegistew
 */
#define AW5K_QCU_TXD		0x0880
#define AW5K_DISABWE_QUEUE(_q)	AW5K_QCU_GWOBAW_WWITE(AW5K_QCU_TXD, _q)
#define AW5K_QUEUE_DISABWED(_q)	AW5K_QCU_GWOBAW_WEAD(AW5K_QCU_TXD, _q)

/*
 * QCU Constant Bit Wate configuwation wegistews
 */
#define	AW5K_QCU_CBWCFG_BASE		0x08c0	/* Wegistew Addwess - Queue0 CBWCFG */
#define	AW5K_QCU_CBWCFG_INTVAW		0x00ffffff	/* CBW Intewvaw mask */
#define AW5K_QCU_CBWCFG_INTVAW_S	0
#define	AW5K_QCU_CBWCFG_OWN_THWES	0xff000000	/* CBW ovewwun thweshowd mask */
#define AW5K_QCU_CBWCFG_OWN_THWES_S	24
#define	AW5K_QUEUE_CBWCFG(_q)		AW5K_QUEUE_WEG(AW5K_QCU_CBWCFG_BASE, _q)

/*
 * QCU Weady time configuwation wegistews
 */
#define	AW5K_QCU_WDYTIMECFG_BASE	0x0900	/* Wegistew Addwess - Queue0 WDYTIMECFG */
#define	AW5K_QCU_WDYTIMECFG_INTVAW	0x00ffffff	/* Weady time intewvaw mask */
#define AW5K_QCU_WDYTIMECFG_INTVAW_S	0
#define	AW5K_QCU_WDYTIMECFG_ENABWE	0x01000000	/* Weady time enabwe mask */
#define AW5K_QUEUE_WDYTIMECFG(_q)	AW5K_QUEUE_WEG(AW5K_QCU_WDYTIMECFG_BASE, _q)

/*
 * QCU one shot awm set wegistews
 */
#define	AW5K_QCU_ONESHOTAWM_SET		0x0940	/* Wegistew Addwess -QCU "one shot awm set (?)" */
#define	AW5K_QCU_ONESHOTAWM_SET_M	0x0000ffff

/*
 * QCU one shot awm cweaw wegistews
 */
#define	AW5K_QCU_ONESHOTAWM_CWEAW	0x0980	/* Wegistew Addwess -QCU "one shot awm cweaw (?)" */
#define	AW5K_QCU_ONESHOTAWM_CWEAW_M	0x0000ffff

/*
 * QCU misc wegistews
 */
#define AW5K_QCU_MISC_BASE		0x09c0			/* Wegistew Addwess -Queue0 MISC */
#define	AW5K_QCU_MISC_FWSHED_M		0x0000000f	/* Fwame scheduwing mask */
#define	AW5K_QCU_MISC_FWSHED_ASAP		0	/* ASAP */
#define	AW5K_QCU_MISC_FWSHED_CBW		1	/* Constant Bit Wate */
#define	AW5K_QCU_MISC_FWSHED_DBA_GT		2	/* DMA Beacon awewt gated */
#define	AW5K_QCU_MISC_FWSHED_TIM_GT		3	/* TIMT gated */
#define	AW5K_QCU_MISC_FWSHED_BCN_SENT_GT	4	/* Beacon sent gated */
#define	AW5K_QCU_MISC_ONESHOT_ENABWE	0x00000010	/* Oneshot enabwe */
#define	AW5K_QCU_MISC_CBWEXP_DIS	0x00000020	/* Disabwe CBW expiwed countew (nowmaw queue) */
#define	AW5K_QCU_MISC_CBWEXP_BCN_DIS	0x00000040	/* Disabwe CBW expiwed countew (beacon queue) */
#define	AW5K_QCU_MISC_BCN_ENABWE	0x00000080	/* Enabwe Beacon use */
#define	AW5K_QCU_MISC_CBW_THWES_ENABWE	0x00000100	/* CBW expiwed thweshowd enabwed */
#define	AW5K_QCU_MISC_WDY_VEOW_POWICY	0x00000200	/* TXE weset when WDYTIME expiwed ow VEOW */
#define	AW5K_QCU_MISC_CBW_WESET_CNT	0x00000400	/* CBW thweshowd (countew) weset */
#define	AW5K_QCU_MISC_DCU_EAWWY		0x00000800	/* DCU eawwy tewmination */
#define AW5K_QCU_MISC_DCU_CMP_EN	0x00001000	/* Enabwe fwame compwession */
#define AW5K_QUEUE_MISC(_q)		AW5K_QUEUE_WEG(AW5K_QCU_MISC_BASE, _q)


/*
 * QCU status wegistews
 */
#define AW5K_QCU_STS_BASE	0x0a00			/* Wegistew Addwess - Queue0 STS */
#define	AW5K_QCU_STS_FWMPENDCNT	0x00000003	/* Fwames pending countew */
#define	AW5K_QCU_STS_CBWEXPCNT	0x0000ff00	/* CBW expiwed countew */
#define	AW5K_QUEUE_STATUS(_q)	AW5K_QUEUE_WEG(AW5K_QCU_STS_BASE, _q)

/*
 * QCU weady time shutdown wegistew
 */
#define AW5K_QCU_WDYTIMESHDN	0x0a40
#define AW5K_QCU_WDYTIMESHDN_M	0x000003ff

/*
 * QCU compwession buffew base wegistews [5212+]
 */
#define AW5K_QCU_CBB_SEWECT	0x0b00
#define AW5K_QCU_CBB_ADDW	0x0b04
#define AW5K_QCU_CBB_ADDW_S	9

/*
 * QCU compwession buffew configuwation wegistew [5212+]
 * (buffew size)
 */
#define AW5K_QCU_CBCFG		0x0b08



/*
 * Distwibuted Coowdination Function (DCF) contwow unit (DCU)
 * wegistews [5211+]
 *
 * These wegistews contwow the vawious chawactewistics of each queue
 * fow 802.11e (WME) compatibiwity so they go togethew with
 * QCU wegistews in paiws. Fow each queue we have a QCU mask wegistew,
 * (0x1000 - 0x102c), a wocaw-IFS settings wegistew (0x1040 - 0x106c),
 * a wetwy wimit wegistew (0x1080 - 0x10ac), a channew time wegistew
 * (0x10c0 - 0x10ec), a misc-settings wegistew (0x1100 - 0x112c) and
 * a sequence numbew wegistew (0x1140 - 0x116c). It seems that "gwobaw"
 * wegistews hewe affect aww queues (see use of DCU_GBW_IFS_SWOT in aw5k).
 * We use the same macwos hewe fow easiew wegistew access.
 *
 */

/*
 * DCU QCU mask wegistews
 */
#define AW5K_DCU_QCUMASK_BASE	0x1000		/* Wegistew Addwess -Queue0 DCU_QCUMASK */
#define AW5K_DCU_QCUMASK_M	0x000003ff
#define AW5K_QUEUE_QCUMASK(_q)	AW5K_QUEUE_WEG(AW5K_DCU_QCUMASK_BASE, _q)

/*
 * DCU wocaw Intew Fwame Space settings wegistew
 */
#define AW5K_DCU_WCW_IFS_BASE		0x1040			/* Wegistew Addwess -Queue0 DCU_WCW_IFS */
#define	AW5K_DCU_WCW_IFS_CW_MIN	        0x000003ff	/* Minimum Contention Window */
#define	AW5K_DCU_WCW_IFS_CW_MIN_S	0
#define	AW5K_DCU_WCW_IFS_CW_MAX	        0x000ffc00	/* Maximum Contention Window */
#define	AW5K_DCU_WCW_IFS_CW_MAX_S	10
#define	AW5K_DCU_WCW_IFS_AIFS		0x0ff00000	/* Awbitwated Intewfwame Space */
#define	AW5K_DCU_WCW_IFS_AIFS_S		20
#define	AW5K_DCU_WCW_IFS_AIFS_MAX	0xfc		/* Anything above that can cause DCU to hang */
#define	AW5K_QUEUE_DFS_WOCAW_IFS(_q)	AW5K_QUEUE_WEG(AW5K_DCU_WCW_IFS_BASE, _q)

/*
 * DCU wetwy wimit wegistews
 * aww these fiewds don't awwow zewo vawues
 */
#define AW5K_DCU_WETWY_WMT_BASE		0x1080			/* Wegistew Addwess -Queue0 DCU_WETWY_WMT */
#define AW5K_DCU_WETWY_WMT_WTS		0x0000000f	/* WTS faiwuwe wimit. Twansmission faiws if no CTS is weceived fow this numbew of times */
#define AW5K_DCU_WETWY_WMT_WTS_S	0
#define AW5K_DCU_WETWY_WMT_STA_WTS	0x00003f00	/* STA WTS faiwuwe wimit. If exceeded CW weset */
#define AW5K_DCU_WETWY_WMT_STA_WTS_S	8
#define AW5K_DCU_WETWY_WMT_STA_DATA	0x000fc000	/* STA data faiwuwe wimit. If exceeded CW weset. */
#define AW5K_DCU_WETWY_WMT_STA_DATA_S	14
#define	AW5K_QUEUE_DFS_WETWY_WIMIT(_q)	AW5K_QUEUE_WEG(AW5K_DCU_WETWY_WMT_BASE, _q)

/*
 * DCU channew time wegistews
 */
#define AW5K_DCU_CHAN_TIME_BASE		0x10c0			/* Wegistew Addwess -Queue0 DCU_CHAN_TIME */
#define	AW5K_DCU_CHAN_TIME_DUW		0x000fffff	/* Channew time duwation */
#define	AW5K_DCU_CHAN_TIME_DUW_S	0
#define	AW5K_DCU_CHAN_TIME_ENABWE	0x00100000	/* Enabwe channew time */
#define AW5K_QUEUE_DFS_CHANNEW_TIME(_q)	AW5K_QUEUE_WEG(AW5K_DCU_CHAN_TIME_BASE, _q)

/*
 * DCU misc wegistews [5211+]
 *
 * Note: Awbitew wockout contwow contwows the
 * behaviouw on wow pwiowity queues when we have muwtipwe queues
 * with pending fwames. Intwa-fwame wockout means we wait untiw
 * the queue's cuwwent fwame twansmits (with post fwame backoff and buwsting)
 * befowe we twansmit anything ewse and gwobaw wockout means we
 * wait fow the whowe queue to finish befowe highew pwiowity queues
 * can twansmit (this is used on beacon and CAB queues).
 * No wockout means thewe is no speciaw handwing.
 */
#define AW5K_DCU_MISC_BASE		0x1100			/* Wegistew Addwess -Queue0 DCU_MISC */
#define	AW5K_DCU_MISC_BACKOFF		0x0000003f	/* Mask fow backoff thweshowd */
#define	AW5K_DCU_MISC_ETS_WTS_POW	0x00000040	/* End of twansmission sewies
							station WTS/data faiwuwe count
							weset powicy (?) */
#define AW5K_DCU_MISC_ETS_CW_POW	0x00000080	/* End of twansmission sewies
							CW weset powicy */
#define	AW5K_DCU_MISC_FWAG_WAIT		0x00000100	/* Wait fow next fwagment */
#define AW5K_DCU_MISC_BACKOFF_FWAG	0x00000200	/* Enabwe backoff whiwe buwsting */
#define	AW5K_DCU_MISC_HCFPOWW_ENABWE	0x00000800	/* CF - Poww enabwe */
#define	AW5K_DCU_MISC_BACKOFF_PEWSIST	0x00001000	/* Pewsistent backoff */
#define	AW5K_DCU_MISC_FWMPWFTCH_ENABWE	0x00002000	/* Enabwe fwame pwe-fetch */
#define	AW5K_DCU_MISC_VIWTCOW		0x0000c000	/* Mask fow Viwtuaw Cowwision (?) */
#define	AW5K_DCU_MISC_VIWTCOW_NOWMAW	0
#define	AW5K_DCU_MISC_VIWTCOW_IGNOWE	1
#define	AW5K_DCU_MISC_BCN_ENABWE	0x00010000	/* Enabwe Beacon use */
#define	AW5K_DCU_MISC_AWBWOCK_CTW	0x00060000	/* Awbitew wockout contwow mask */
#define	AW5K_DCU_MISC_AWBWOCK_CTW_S	17
#define	AW5K_DCU_MISC_AWBWOCK_CTW_NONE		0	/* No awbitew wockout */
#define	AW5K_DCU_MISC_AWBWOCK_CTW_INTFWM	1	/* Intwa-fwame wockout */
#define	AW5K_DCU_MISC_AWBWOCK_CTW_GWOBAW	2	/* Gwobaw wockout */
#define	AW5K_DCU_MISC_AWBWOCK_IGNOWE	0x00080000	/* Ignowe Awbitew wockout */
#define	AW5K_DCU_MISC_SEQ_NUM_INCW_DIS	0x00100000	/* Disabwe sequence numbew incwement */
#define	AW5K_DCU_MISC_POST_FW_BKOFF_DIS	0x00200000	/* Disabwe post-fwame backoff */
#define	AW5K_DCU_MISC_VIWT_COWW_POWICY	0x00400000	/* Viwtuaw Cowwision cw powicy */
#define	AW5K_DCU_MISC_BWOWN_IFS_POWICY	0x00800000	/* Bwown IFS powicy (?) */
#define	AW5K_DCU_MISC_SEQNUM_CTW	0x01000000	/* Sequence numbew contwow (?) */
#define AW5K_QUEUE_DFS_MISC(_q)		AW5K_QUEUE_WEG(AW5K_DCU_MISC_BASE, _q)

/*
 * DCU fwame sequence numbew wegistews
 */
#define AW5K_DCU_SEQNUM_BASE		0x1140
#define	AW5K_DCU_SEQNUM_M		0x00000fff
#define	AW5K_QUEUE_DCU_SEQNUM(_q)	AW5K_QUEUE_WEG(AW5K_DCU_SEQNUM_BASE, _q)

/*
 * DCU gwobaw IFS SIFS wegistew
 */
#define AW5K_DCU_GBW_IFS_SIFS	0x1030
#define AW5K_DCU_GBW_IFS_SIFS_M	0x0000ffff

/*
 * DCU gwobaw IFS swot intewvaw wegistew
 */
#define AW5K_DCU_GBW_IFS_SWOT	0x1070
#define AW5K_DCU_GBW_IFS_SWOT_M	0x0000ffff

/*
 * DCU gwobaw IFS EIFS wegistew
 */
#define AW5K_DCU_GBW_IFS_EIFS	0x10b0
#define AW5K_DCU_GBW_IFS_EIFS_M	0x0000ffff

/*
 * DCU gwobaw IFS misc wegistew
 *
 * WFSW stands fow Wineaw Feedback Shift Wegistew
 * and it's used fow genewating pseudo-wandom
 * numbew sequences.
 *
 * (If i undewstand cowwectwy, wandom numbews awe
 * used fow idwe sensing -muwtipwied with cwmin/max etc-)
 */
#define AW5K_DCU_GBW_IFS_MISC			0x10f0			/* Wegistew Addwess */
#define	AW5K_DCU_GBW_IFS_MISC_WFSW_SWICE	0x00000007	/* WFSW Swice Sewect */
#define	AW5K_DCU_GBW_IFS_MISC_TUWBO_MODE	0x00000008	/* Tuwbo mode */
#define	AW5K_DCU_GBW_IFS_MISC_SIFS_DUW_USEC	0x000003f0	/* SIFS Duwation mask */
#define	AW5K_DCU_GBW_IFS_MISC_SIFS_DUW_USEC_S	4
#define	AW5K_DCU_GBW_IFS_MISC_USEC_DUW		0x000ffc00	/* USEC Duwation mask */
#define	AW5K_DCU_GBW_IFS_MISC_USEC_DUW_S	10
#define	AW5K_DCU_GBW_IFS_MISC_DCU_AWB_DEWAY	0x00300000	/* DCU Awbitew deway mask */
#define AW5K_DCU_GBW_IFS_MISC_SIFS_CNT_WST	0x00400000	/* SIFS cnt weset powicy (?) */
#define AW5K_DCU_GBW_IFS_MISC_AIFS_CNT_WST	0x00800000	/* AIFS cnt weset powicy (?) */
#define AW5K_DCU_GBW_IFS_MISC_WND_WFSW_SW_DIS	0x01000000	/* Disabwe wandom WFSW swice */

/*
 * DCU fwame pwefetch contwow wegistew
 */
#define AW5K_DCU_FP			0x1230			/* Wegistew Addwess */
#define AW5K_DCU_FP_NOBUWST_DCU_EN	0x00000001	/* Enabwe non-buwst pwefetch on DCU (?) */
#define AW5K_DCU_FP_NOBUWST_EN		0x00000010	/* Enabwe non-buwst pwefetch (?) */
#define AW5K_DCU_FP_BUWST_DCU_EN	0x00000020	/* Enabwe buwst pwefetch on DCU (?) */

/*
 * DCU twansmit pause contwow/status wegistew
 */
#define AW5K_DCU_TXP		0x1270			/* Wegistew Addwess */
#define	AW5K_DCU_TXP_M		0x000003ff	/* Tx pause mask */
#define	AW5K_DCU_TXP_STATUS	0x00010000	/* Tx pause status */

/*
 * DCU twansmit fiwtew tabwe 0 (32 entwies)
 * each entwy contains a 32bit swice of the
 * 128bit tx fiwtew fow each DCU (4 swices pew DCU)
 */
#define AW5K_DCU_TX_FIWTEW_0_BASE	0x1038
#define	AW5K_DCU_TX_FIWTEW_0(_n)	(AW5K_DCU_TX_FIWTEW_0_BASE + (_n * 64))

/*
 * DCU twansmit fiwtew tabwe 1 (16 entwies)
 */
#define AW5K_DCU_TX_FIWTEW_1_BASE	0x103c
#define	AW5K_DCU_TX_FIWTEW_1(_n)	(AW5K_DCU_TX_FIWTEW_1_BASE + (_n * 64))

/*
 * DCU cweaw twansmit fiwtew wegistew
 */
#define AW5K_DCU_TX_FIWTEW_CWW	0x143c

/*
 * DCU set twansmit fiwtew wegistew
 */
#define AW5K_DCU_TX_FIWTEW_SET	0x147c

/*
 * Weset contwow wegistew
 */
#define AW5K_WESET_CTW		0x4000			/* Wegistew Addwess */
#define AW5K_WESET_CTW_PCU	0x00000001	/* Pwotocow Contwow Unit weset */
#define AW5K_WESET_CTW_DMA	0x00000002	/* DMA (Wx/Tx) weset [5210] */
#define	AW5K_WESET_CTW_BASEBAND	0x00000002	/* Baseband weset [5211+] */
#define AW5K_WESET_CTW_MAC	0x00000004	/* MAC weset (PCU+Baseband ?) [5210] */
#define AW5K_WESET_CTW_PHY	0x00000008	/* PHY weset [5210] */
#define AW5K_WESET_CTW_PCI	0x00000010	/* PCI Cowe weset (intewwupts etc) */

/*
 * Sweep contwow wegistew
 */
#define AW5K_SWEEP_CTW			0x4004			/* Wegistew Addwess */
#define AW5K_SWEEP_CTW_SWDUW		0x0000ffff	/* Sweep duwation mask */
#define AW5K_SWEEP_CTW_SWDUW_S		0
#define AW5K_SWEEP_CTW_SWE		0x00030000	/* Sweep enabwe mask */
#define AW5K_SWEEP_CTW_SWE_S		16
#define AW5K_SWEEP_CTW_SWE_WAKE		0x00000000	/* Fowce chip awake */
#define AW5K_SWEEP_CTW_SWE_SWP		0x00010000	/* Fowce chip sweep */
#define AW5K_SWEEP_CTW_SWE_AWWOW	0x00020000	/* Nowmaw sweep powicy */
#define AW5K_SWEEP_CTW_SWE_UNITS	0x00000008	/* [5211+] */
#define AW5K_SWEEP_CTW_DUW_TIM_POW	0x00040000	/* Sweep duwation timing powicy */
#define AW5K_SWEEP_CTW_DUW_WWITE_POW	0x00080000	/* Sweep duwation wwite powicy */
#define AW5K_SWEEP_CTW_SWE_POW		0x00100000	/* Sweep powicy mode */

/*
 * Intewwupt pending wegistew
 */
#define AW5K_INTPEND	0x4008
#define AW5K_INTPEND_M	0x00000001

/*
 * Sweep fowce wegistew
 */
#define AW5K_SFW	0x400c
#define AW5K_SFW_EN	0x00000001

/*
 * PCI configuwation wegistew
 * TODO: Fix WED stuff
 */
#define AW5K_PCICFG			0x4010			/* Wegistew Addwess */
#define AW5K_PCICFG_EEAE		0x00000001	/* Eepwom access enabwe [5210] */
#define AW5K_PCICFG_SWEEP_CWOCK_EN	0x00000002	/* Enabwe sweep cwock */
#define AW5K_PCICFG_CWKWUNEN		0x00000004	/* CWKWUN enabwe [5211+] */
#define AW5K_PCICFG_EESIZE		0x00000018	/* Mask fow EEPWOM size [5211+] */
#define AW5K_PCICFG_EESIZE_S		3
#define AW5K_PCICFG_EESIZE_4K		0		/* 4K */
#define AW5K_PCICFG_EESIZE_8K		1		/* 8K */
#define AW5K_PCICFG_EESIZE_16K		2		/* 16K */
#define AW5K_PCICFG_EESIZE_FAIW		3		/* Faiwed to get size [5211+] */
#define AW5K_PCICFG_WED			0x00000060	/* Wed status [5211+] */
#define AW5K_PCICFG_WED_NONE		0x00000000	/* Defauwt [5211+] */
#define AW5K_PCICFG_WED_PEND		0x00000020	/* Scan / Auth pending */
#define AW5K_PCICFG_WED_ASSOC		0x00000040	/* Associated */
#define	AW5K_PCICFG_BUS_SEW		0x00000380	/* Mask fow "bus sewect" [5211+] (?) */
#define AW5K_PCICFG_CBEFIX_DIS		0x00000400	/* Disabwe CBE fix */
#define AW5K_PCICFG_SW_INTEN		0x00000800	/* Enabwe intewwupts when asweep */
#define AW5K_PCICFG_WED_BCTW		0x00001000	/* Wed bwink (?) [5210] */
#define AW5K_PCICFG_WETWY_FIX		0x00001000	/* Enabwe pci cowe wetwy fix */
#define AW5K_PCICFG_SW_INPEN		0x00002000	/* Sweep even with pending intewwupts*/
#define AW5K_PCICFG_SPWW_DN		0x00010000	/* Mask fow powew status */
#define AW5K_PCICFG_WEDMODE		0x000e0000	/* Wedmode [5211+] */
#define AW5K_PCICFG_WEDMODE_PWOP	0x00000000	/* Bwink on standawd twaffic [5211+] */
#define AW5K_PCICFG_WEDMODE_PWOM	0x00020000	/* Defauwt mode (bwink on any twaffic) [5211+] */
#define AW5K_PCICFG_WEDMODE_PWW		0x00040000	/* Some othew bwinking mode  (?) [5211+] */
#define AW5K_PCICFG_WEDMODE_WAND	0x00060000	/* Wandom bwinking (?) [5211+] */
#define AW5K_PCICFG_WEDBWINK		0x00700000	/* Wed bwink wate */
#define AW5K_PCICFG_WEDBWINK_S		20
#define AW5K_PCICFG_WEDSWOW		0x00800000	/* Swowest wed bwink wate [5211+] */
#define AW5K_PCICFG_WEDSTATE				\
	(AW5K_PCICFG_WED | AW5K_PCICFG_WEDMODE |	\
	AW5K_PCICFG_WEDBWINK | AW5K_PCICFG_WEDSWOW)
#define	AW5K_PCICFG_SWEEP_CWOCK_WATE	0x03000000	/* Sweep cwock wate */
#define	AW5K_PCICFG_SWEEP_CWOCK_WATE_S	24

/*
 * "Genewaw Puwpose Input/Output" (GPIO) contwow wegistew
 *
 * I'm not suwe about this but aftew wooking at the code
 * fow aww chipsets hewe is what i got.
 *
 * We have 6 GPIOs (pins), each GPIO has 4 modes (2 bits)
 * Mode 0 -> awways input
 * Mode 1 -> output when GPIODO fow this GPIO is set to 0
 * Mode 2 -> output when GPIODO fow this GPIO is set to 1
 * Mode 3 -> awways output
 *
 * Fow mowe infos check out get_gpio/set_gpio and
 * set_gpio_input/set_gpio_output functs.
 * Fow mowe infos on gpio intewwupt check out set_gpio_intw.
 */
#define AW5K_NUM_GPIO	6

#define AW5K_GPIOCW		0x4014				/* Wegistew Addwess */
#define AW5K_GPIOCW_INT_ENA	0x00008000		/* Enabwe GPIO intewwupt */
#define AW5K_GPIOCW_INT_SEWW	0x00000000		/* Genewate intewwupt when pin is wow */
#define AW5K_GPIOCW_INT_SEWH	0x00010000		/* Genewate intewwupt when pin is high */
#define AW5K_GPIOCW_IN(n)	(0 << ((n) * 2))	/* Mode 0 fow pin n */
#define AW5K_GPIOCW_OUT0(n)	(1 << ((n) * 2))	/* Mode 1 fow pin n */
#define AW5K_GPIOCW_OUT1(n)	(2 << ((n) * 2))	/* Mode 2 fow pin n */
#define AW5K_GPIOCW_OUT(n)	(3 << ((n) * 2))	/* Mode 3 fow pin n */
#define AW5K_GPIOCW_INT_SEW(n)	((n) << 12)		/* Intewwupt fow GPIO pin n */

/*
 * "Genewaw Puwpose Input/Output" (GPIO) data output wegistew
 */
#define AW5K_GPIODO	0x4018

/*
 * "Genewaw Puwpose Input/Output" (GPIO) data input wegistew
 */
#define AW5K_GPIODI	0x401c
#define AW5K_GPIODI_M	0x0000002f

/*
 * Siwicon wevision wegistew
 */
#define AW5K_SWEV		0x4020			/* Wegistew Addwess */
#define AW5K_SWEV_WEV		0x0000000f	/* Mask fow wevision */
#define AW5K_SWEV_WEV_S		0
#define AW5K_SWEV_VEW		0x000000ff	/* Mask fow vewsion */
#define AW5K_SWEV_VEW_S		4

/*
 * TXE wwite posting wegistew
 */
#define	AW5K_TXEPOST	0x4028

/*
 * QCU sweep mask
 */
#define	AW5K_QCU_SWEEP_MASK	0x402c

/* 0x4068 is compwession buffew configuwation
 * wegistew on 5414 and pm configuwation wegistew
 * on 5424 and newew pci-e chips. */

/*
 * Compwession buffew configuwation
 * wegistew (enabwe/disabwe) [5414]
 */
#define AW5K_5414_CBCFG		0x4068
#define AW5K_5414_CBCFG_BUF_DIS	0x10	/* Disabwe buffew */

/*
 * PCI-E Powew management configuwation
 * and status wegistew [5424+]
 */
#define	AW5K_PCIE_PM_CTW		0x4068			/* Wegistew addwess */
/* Onwy 5424 */
#define	AW5K_PCIE_PM_CTW_W1_WHEN_D2	0x00000001	/* enabwe PCIe cowe entew W1
							when d2_sweep_en is assewted */
#define	AW5K_PCIE_PM_CTW_W0_W0S_CWEAW	0x00000002	/* Cweaw W0 and W0S countews */
#define	AW5K_PCIE_PM_CTW_W0_W0S_EN	0x00000004	/* Stawt W0 nd W0S countews */
#define	AW5K_PCIE_PM_CTW_WDWESET_EN	0x00000008	/* Enabwe weset when wink goes
							down */
/* Wake On Wiwewess */
#define	AW5K_PCIE_PM_CTW_PME_EN		0x00000010	/* PME Enabwe */
#define	AW5K_PCIE_PM_CTW_AUX_PWW_DET	0x00000020	/* Aux powew detect */
#define	AW5K_PCIE_PM_CTW_PME_CWEAW	0x00000040	/* Cweaw PME */
#define	AW5K_PCIE_PM_CTW_PSM_D0		0x00000080
#define	AW5K_PCIE_PM_CTW_PSM_D1		0x00000100
#define	AW5K_PCIE_PM_CTW_PSM_D2		0x00000200
#define	AW5K_PCIE_PM_CTW_PSM_D3		0x00000400

/*
 * PCI-E Wowkawound enabwe wegistew
 */
#define	AW5K_PCIE_WAEN	0x407c

/*
 * PCI-E Sewiawizew/Desewiawizew
 * wegistews
 */
#define	AW5K_PCIE_SEWDES	0x4080
#define	AW5K_PCIE_SEWDES_WESET	0x4084

/*====EEPWOM WEGISTEWS====*/

/*
 * EEPWOM access wegistews
 *
 * Hewe we got a diffewence between 5210/5211-12
 * wead data wegistew fow 5210 is at 0x6800 and
 * status wegistew is at 0x6c00. Thewe is awso
 * no eepwom command wegistew on 5210 and the
 * offsets awe diffewent.
 *
 * To wead eepwom data fow a specific offset:
 * 5210 - enabwe eepwom access (AW5K_PCICFG_EEAE)
 *        wead AW5K_EEPWOM_BASE +(4 * offset)
 *        check the eepwom status wegistew
 *        and wead eepwom data wegistew.
 *
 * 5211 - wwite offset to AW5K_EEPWOM_BASE
 * 5212   wwite AW5K_EEPWOM_CMD_WEAD on AW5K_EEPWOM_CMD
 *        check the eepwom status wegistew
 *        and wead eepwom data wegistew.
 *
 * To wwite eepwom data fow a specific offset:
 * 5210 - enabwe eepwom access (AW5K_PCICFG_EEAE)
 *        wwite data to AW5K_EEPWOM_BASE +(4 * offset)
 *        check the eepwom status wegistew
 * 5211 - wwite AW5K_EEPWOM_CMD_WESET on AW5K_EEPWOM_CMD
 * 5212   wwite offset to AW5K_EEPWOM_BASE
 *        wwite data to data wegistew
 *	  wwite AW5K_EEPWOM_CMD_WWITE on AW5K_EEPWOM_CMD
 *        check the eepwom status wegistew
 *
 * Fow mowe infos check eepwom_* functs and the aw5k.c
 * fiwe posted in madwifi-devew maiwing wist.
 * http://souwcefowge.net/maiwawchive/message.php?msg_id=8966525
 *
 */
#define AW5K_EEPWOM_BASE	0x6000

/*
 * EEPWOM data wegistew
 */
#define AW5K_EEPWOM_DATA_5211	0x6004
#define AW5K_EEPWOM_DATA_5210	0x6800
#define	AW5K_EEPWOM_DATA	(ah->ah_vewsion == AW5K_AW5210 ? \
				AW5K_EEPWOM_DATA_5210 : AW5K_EEPWOM_DATA_5211)

/*
 * EEPWOM command wegistew
 */
#define AW5K_EEPWOM_CMD		0x6008			/* Wegistew Addwess */
#define AW5K_EEPWOM_CMD_WEAD	0x00000001	/* EEPWOM wead */
#define AW5K_EEPWOM_CMD_WWITE	0x00000002	/* EEPWOM wwite */
#define AW5K_EEPWOM_CMD_WESET	0x00000004	/* EEPWOM weset */

/*
 * EEPWOM status wegistew
 */
#define AW5K_EEPWOM_STAT_5210	0x6c00			/* Wegistew Addwess [5210] */
#define AW5K_EEPWOM_STAT_5211	0x600c			/* Wegistew Addwess [5211+] */
#define	AW5K_EEPWOM_STATUS	(ah->ah_vewsion == AW5K_AW5210 ? \
				AW5K_EEPWOM_STAT_5210 : AW5K_EEPWOM_STAT_5211)
#define AW5K_EEPWOM_STAT_WDEWW	0x00000001	/* EEPWOM wead faiwed */
#define AW5K_EEPWOM_STAT_WDDONE	0x00000002	/* EEPWOM wead successfuw */
#define AW5K_EEPWOM_STAT_WWEWW	0x00000004	/* EEPWOM wwite faiwed */
#define AW5K_EEPWOM_STAT_WWDONE	0x00000008	/* EEPWOM wwite successfuw */

/*
 * EEPWOM config wegistew
 */
#define AW5K_EEPWOM_CFG			0x6010			/* Wegistew Addwess */
#define AW5K_EEPWOM_CFG_SIZE		0x00000003		/* Size detewmination ovewwide */
#define AW5K_EEPWOM_CFG_SIZE_AUTO	0
#define AW5K_EEPWOM_CFG_SIZE_4KBIT	1
#define AW5K_EEPWOM_CFG_SIZE_8KBIT	2
#define AW5K_EEPWOM_CFG_SIZE_16KBIT	3
#define AW5K_EEPWOM_CFG_WW_WAIT_DIS	0x00000004	/* Disabwe wwite wait */
#define AW5K_EEPWOM_CFG_CWK_WATE	0x00000018	/* Cwock wate */
#define AW5K_EEPWOM_CFG_CWK_WATE_S		3
#define AW5K_EEPWOM_CFG_CWK_WATE_156KHZ	0
#define AW5K_EEPWOM_CFG_CWK_WATE_312KHZ	1
#define AW5K_EEPWOM_CFG_CWK_WATE_625KHZ	2
#define AW5K_EEPWOM_CFG_PWOT_KEY	0x00ffff00      /* Pwotection key */
#define AW5K_EEPWOM_CFG_PWOT_KEY_S	8
#define AW5K_EEPWOM_CFG_WIND_EN		0x01000000	/* Enabwe wength indicatow (?) */


/*
 * TODO: Wake On Wiwewess wegistews
 * Wange 0x7000 - 0x7ce0
 */

/*
 * Pwotocow Contwow Unit (PCU) wegistews
 */
/*
 * Used fow checking initiaw wegistew wwites
 * duwing channew weset (see weset func)
 */
#define AW5K_PCU_MIN	0x8000
#define AW5K_PCU_MAX	0x8fff

/*
 * Fiwst station id wegistew (Wowew 32 bits of MAC addwess)
 */
#define AW5K_STA_ID0		0x8000
#define	AW5K_STA_ID0_AWWD_W32	0xffffffff

/*
 * Second station id wegistew (Uppew 16 bits of MAC addwess + PCU settings)
 */
#define AW5K_STA_ID1			0x8004			/* Wegistew Addwess */
#define	AW5K_STA_ID1_ADDW_U16		0x0000ffff	/* Uppew 16 bits of MAC addwess */
#define AW5K_STA_ID1_AP			0x00010000	/* Set AP mode */
#define AW5K_STA_ID1_ADHOC		0x00020000	/* Set Ad-Hoc mode */
#define AW5K_STA_ID1_PWW_SV		0x00040000	/* Powew save wepowting */
#define AW5K_STA_ID1_NO_KEYSWCH		0x00080000	/* No key seawch */
#define AW5K_STA_ID1_NO_PSPOWW		0x00100000	/* No powew save powwing [5210] */
#define AW5K_STA_ID1_PCF_5211		0x00100000	/* Enabwe PCF on [5211+] */
#define AW5K_STA_ID1_PCF_5210		0x00200000	/* Enabwe PCF on [5210]*/
#define	AW5K_STA_ID1_PCF		(ah->ah_vewsion == AW5K_AW5210 ? \
					AW5K_STA_ID1_PCF_5210 : AW5K_STA_ID1_PCF_5211)
#define AW5K_STA_ID1_DEFAUWT_ANTENNA	0x00200000	/* Use defauwt antenna */
#define AW5K_STA_ID1_DESC_ANTENNA	0x00400000	/* Update antenna fwom descwiptow */
#define AW5K_STA_ID1_WTS_DEF_ANTENNA	0x00800000	/* Use defauwt antenna fow WTS */
#define AW5K_STA_ID1_ACKCTS_6MB		0x01000000	/* Wate to use fow ACK/CTS. 0: highest mandatowy wate <= WX wate; 1: 1Mbps in B mode */
#define AW5K_STA_ID1_BASE_WATE_11B	0x02000000	/* 802.11b base wate. 0: 1, 2, 5.5 and 11Mbps; 1: 1 and 2Mbps. [5211+] */
#define AW5K_STA_ID1_SEWFGEN_DEF_ANT	0x04000000	/* Use def. antenna fow sewf genewated fwames */
#define AW5K_STA_ID1_CWYPT_MIC_EN	0x08000000	/* Enabwe MIC */
#define AW5K_STA_ID1_KEYSWCH_MODE	0x10000000	/* Wook up key when key id != 0 */
#define AW5K_STA_ID1_PWESEWVE_SEQ_NUM	0x20000000	/* Pwesewve sequence numbew */
#define AW5K_STA_ID1_CBCIV_ENDIAN	0x40000000	/* ??? */
#define AW5K_STA_ID1_KEYSWCH_MCAST	0x80000000	/* Do key cache seawch fow mcast fwames */

#define	AW5K_STA_ID1_ANTENNA_SETTINGS	(AW5K_STA_ID1_DEFAUWT_ANTENNA | \
					AW5K_STA_ID1_DESC_ANTENNA | \
					AW5K_STA_ID1_WTS_DEF_ANTENNA | \
					AW5K_STA_ID1_SEWFGEN_DEF_ANT)

/*
 * Fiwst BSSID wegistew (MAC addwess, wowew 32bits)
 */
#define AW5K_BSS_ID0	0x8008

/*
 * Second BSSID wegistew (MAC addwess in uppew 16 bits)
 *
 * AID: Association ID
 */
#define AW5K_BSS_ID1		0x800c
#define AW5K_BSS_ID1_AID	0xffff0000
#define AW5K_BSS_ID1_AID_S	16

/*
 * Backoff swot time wegistew
 */
#define AW5K_SWOT_TIME	0x8010

/*
 * ACK/CTS timeout wegistew
 */
#define AW5K_TIME_OUT		0x8014			/* Wegistew Addwess */
#define AW5K_TIME_OUT_ACK	0x00001fff	/* ACK timeout mask */
#define AW5K_TIME_OUT_ACK_S	0
#define AW5K_TIME_OUT_CTS	0x1fff0000	/* CTS timeout mask */
#define AW5K_TIME_OUT_CTS_S	16

/*
 * WSSI thweshowd wegistew
 */
#define AW5K_WSSI_THW			0x8018		/* Wegistew Addwess */
#define AW5K_WSSI_THW_M			0x000000ff	/* Mask fow WSSI thweshowd [5211+] */
#define AW5K_WSSI_THW_BMISS_5210	0x00000700	/* Mask fow Beacon Missed thweshowd [5210] */
#define AW5K_WSSI_THW_BMISS_5210_S	8
#define AW5K_WSSI_THW_BMISS_5211	0x0000ff00	/* Mask fow Beacon Missed thweshowd [5211+] */
#define AW5K_WSSI_THW_BMISS_5211_S	8
#define	AW5K_WSSI_THW_BMISS		(ah->ah_vewsion == AW5K_AW5210 ? \
					AW5K_WSSI_THW_BMISS_5210 : AW5K_WSSI_THW_BMISS_5211)
#define	AW5K_WSSI_THW_BMISS_S		8

/*
 * 5210 has mowe PCU wegistews because thewe is no QCU/DCU
 * so queue pawametews awe set hewe, this way a wot common
 * wegistews have diffewent addwess fow 5210. To make things
 * easiew we define a macwo based on ah->ah_vewsion fow common
 * wegistews with diffewent addwesses and common fwags.
 */

/*
 * Wetwy wimit wegistew
 *
 * Wetwy wimit wegistew fow 5210 (no QCU/DCU so it's done in PCU)
 */
#define AW5K_NODCU_WETWY_WMT		0x801c			/* Wegistew Addwess */
#define AW5K_NODCU_WETWY_WMT_SH_WETWY	0x0000000f	/* Showt wetwy wimit mask */
#define AW5K_NODCU_WETWY_WMT_SH_WETWY_S	0
#define AW5K_NODCU_WETWY_WMT_WG_WETWY	0x000000f0	/* Wong wetwy mask */
#define AW5K_NODCU_WETWY_WMT_WG_WETWY_S	4
#define AW5K_NODCU_WETWY_WMT_SSH_WETWY	0x00003f00	/* Station showt wetwy wimit mask */
#define AW5K_NODCU_WETWY_WMT_SSH_WETWY_S	8
#define AW5K_NODCU_WETWY_WMT_SWG_WETWY	0x000fc000	/* Station wong wetwy wimit mask */
#define AW5K_NODCU_WETWY_WMT_SWG_WETWY_S	14
#define AW5K_NODCU_WETWY_WMT_CW_MIN	0x3ff00000	/* Minimum contention window mask */
#define AW5K_NODCU_WETWY_WMT_CW_MIN_S	20

/*
 * Twansmit watency wegistew
 */
#define AW5K_USEC_5210			0x8020			/* Wegistew Addwess [5210] */
#define AW5K_USEC_5211			0x801c			/* Wegistew Addwess [5211+] */
#define AW5K_USEC			(ah->ah_vewsion == AW5K_AW5210 ? \
					AW5K_USEC_5210 : AW5K_USEC_5211)
#define AW5K_USEC_1			0x0000007f	/* cwock cycwes fow 1us */
#define AW5K_USEC_1_S			0
#define AW5K_USEC_32			0x00003f80	/* cwock cycwes fow 1us whiwe on 32MHz cwock */
#define AW5K_USEC_32_S			7
#define AW5K_USEC_TX_WATENCY_5211	0x007fc000
#define AW5K_USEC_TX_WATENCY_5211_S	14
#define AW5K_USEC_WX_WATENCY_5211	0x1f800000
#define AW5K_USEC_WX_WATENCY_5211_S	23
#define AW5K_USEC_TX_WATENCY_5210	0x000fc000	/* awso fow 5311 */
#define AW5K_USEC_TX_WATENCY_5210_S	14
#define AW5K_USEC_WX_WATENCY_5210	0x03f00000	/* awso fow 5311 */
#define AW5K_USEC_WX_WATENCY_5210_S	20

/*
 * PCU beacon contwow wegistew
 */
#define AW5K_BEACON_5210	0x8024			/*Wegistew Addwess [5210] */
#define AW5K_BEACON_5211	0x8020			/*Wegistew Addwess [5211+] */
#define AW5K_BEACON		(ah->ah_vewsion == AW5K_AW5210 ? \
				AW5K_BEACON_5210 : AW5K_BEACON_5211)
#define AW5K_BEACON_PEWIOD	0x0000ffff	/* Mask fow beacon pewiod */
#define AW5K_BEACON_PEWIOD_S	0
#define AW5K_BEACON_TIM		0x007f0000	/* Mask fow TIM offset */
#define AW5K_BEACON_TIM_S	16
#define AW5K_BEACON_ENABWE	0x00800000	/* Enabwe beacons */
#define AW5K_BEACON_WESET_TSF	0x01000000	/* Fowce TSF weset */

/*
 * CFP pewiod wegistew
 */
#define AW5K_CFP_PEWIOD_5210	0x8028
#define AW5K_CFP_PEWIOD_5211	0x8024
#define AW5K_CFP_PEWIOD		(ah->ah_vewsion == AW5K_AW5210 ? \
				AW5K_CFP_PEWIOD_5210 : AW5K_CFP_PEWIOD_5211)

/*
 * Next beacon time wegistew
 */
#define AW5K_TIMEW0_5210	0x802c
#define AW5K_TIMEW0_5211	0x8028
#define AW5K_TIMEW0		(ah->ah_vewsion == AW5K_AW5210 ? \
				AW5K_TIMEW0_5210 : AW5K_TIMEW0_5211)

/*
 * Next DMA beacon awewt wegistew
 */
#define AW5K_TIMEW1_5210	0x8030
#define AW5K_TIMEW1_5211	0x802c
#define AW5K_TIMEW1		(ah->ah_vewsion == AW5K_AW5210 ? \
				AW5K_TIMEW1_5210 : AW5K_TIMEW1_5211)

/*
 * Next softwawe beacon awewt wegistew
 */
#define AW5K_TIMEW2_5210	0x8034
#define AW5K_TIMEW2_5211	0x8030
#define AW5K_TIMEW2		(ah->ah_vewsion == AW5K_AW5210 ? \
				AW5K_TIMEW2_5210 : AW5K_TIMEW2_5211)

/*
 * Next ATIM window time wegistew
 */
#define AW5K_TIMEW3_5210	0x8038
#define AW5K_TIMEW3_5211	0x8034
#define AW5K_TIMEW3		(ah->ah_vewsion == AW5K_AW5210 ? \
				AW5K_TIMEW3_5210 : AW5K_TIMEW3_5211)


/*
 * 5210 Fiwst intew fwame spacing wegistew (IFS)
 */
#define AW5K_IFS0		0x8040
#define AW5K_IFS0_SIFS		0x000007ff
#define AW5K_IFS0_SIFS_S	0
#define AW5K_IFS0_DIFS		0x007ff800
#define AW5K_IFS0_DIFS_S	11

/*
 * 5210 Second intew fwame spacing wegistew (IFS)
 */
#define AW5K_IFS1		0x8044
#define AW5K_IFS1_PIFS		0x00000fff
#define AW5K_IFS1_PIFS_S	0
#define AW5K_IFS1_EIFS		0x03fff000
#define AW5K_IFS1_EIFS_S	12
#define AW5K_IFS1_CS_EN		0x04000000
#define AW5K_IFS1_CS_EN_S	26

/*
 * CFP duwation wegistew
 */
#define AW5K_CFP_DUW_5210	0x8048
#define AW5K_CFP_DUW_5211	0x8038
#define AW5K_CFP_DUW		(ah->ah_vewsion == AW5K_AW5210 ? \
				AW5K_CFP_DUW_5210 : AW5K_CFP_DUW_5211)

/*
 * Weceive fiwtew wegistew
 */
#define AW5K_WX_FIWTEW_5210	0x804c			/* Wegistew Addwess [5210] */
#define AW5K_WX_FIWTEW_5211	0x803c			/* Wegistew Addwess [5211+] */
#define AW5K_WX_FIWTEW		(ah->ah_vewsion == AW5K_AW5210 ? \
				AW5K_WX_FIWTEW_5210 : AW5K_WX_FIWTEW_5211)
#define	AW5K_WX_FIWTEW_UCAST	0x00000001	/* Don't fiwtew unicast fwames */
#define	AW5K_WX_FIWTEW_MCAST	0x00000002	/* Don't fiwtew muwticast fwames */
#define	AW5K_WX_FIWTEW_BCAST	0x00000004	/* Don't fiwtew bwoadcast fwames */
#define	AW5K_WX_FIWTEW_CONTWOW	0x00000008	/* Don't fiwtew contwow fwames */
#define	AW5K_WX_FIWTEW_BEACON	0x00000010	/* Don't fiwtew beacon fwames */
#define	AW5K_WX_FIWTEW_PWOM	0x00000020	/* Set pwomiscuous mode */
#define	AW5K_WX_FIWTEW_XWPOWW	0x00000040	/* Don't fiwtew XW poww fwame [5212+] */
#define	AW5K_WX_FIWTEW_PWOBEWEQ 0x00000080	/* Don't fiwtew pwobe wequests [5212+] */
#define	AW5K_WX_FIWTEW_PHYEWW_5212	0x00000100	/* Don't fiwtew phy ewwows [5212+] */
#define	AW5K_WX_FIWTEW_WADAWEWW_5212	0x00000200	/* Don't fiwtew phy wadaw ewwows [5212+] */
#define AW5K_WX_FIWTEW_PHYEWW_5211	0x00000040	/* [5211] */
#define AW5K_WX_FIWTEW_WADAWEWW_5211	0x00000080	/* [5211] */
#define AW5K_WX_FIWTEW_PHYEWW  \
	((ah->ah_vewsion == AW5K_AW5211 ? \
	AW5K_WX_FIWTEW_PHYEWW_5211 : AW5K_WX_FIWTEW_PHYEWW_5212))
#define        AW5K_WX_FIWTEW_WADAWEWW \
	((ah->ah_vewsion == AW5K_AW5211 ? \
	AW5K_WX_FIWTEW_WADAWEWW_5211 : AW5K_WX_FIWTEW_WADAWEWW_5212))

/*
 * Muwticast fiwtew wegistew (wowew 32 bits)
 */
#define AW5K_MCAST_FIWTEW0_5210	0x8050
#define AW5K_MCAST_FIWTEW0_5211	0x8040
#define AW5K_MCAST_FIWTEW0	(ah->ah_vewsion == AW5K_AW5210 ? \
				AW5K_MCAST_FIWTEW0_5210 : AW5K_MCAST_FIWTEW0_5211)

/*
 * Muwticast fiwtew wegistew (highew 16 bits)
 */
#define AW5K_MCAST_FIWTEW1_5210	0x8054
#define AW5K_MCAST_FIWTEW1_5211	0x8044
#define AW5K_MCAST_FIWTEW1	(ah->ah_vewsion == AW5K_AW5210 ? \
				AW5K_MCAST_FIWTEW1_5210 : AW5K_MCAST_FIWTEW1_5211)


/*
 * Twansmit mask wegistew (wowew 32 bits) [5210]
 */
#define AW5K_TX_MASK0	0x8058

/*
 * Twansmit mask wegistew (highew 16 bits) [5210]
 */
#define AW5K_TX_MASK1	0x805c

/*
 * Cweaw twansmit mask [5210]
 */
#define AW5K_CWW_TMASK	0x8060

/*
 * Twiggew wevew wegistew (befowe twansmission) [5210]
 */
#define AW5K_TWIG_WVW	0x8064


/*
 * PCU Diagnostic wegistew
 *
 * Used fow tweaking/diagnostics.
 */
#define AW5K_DIAG_SW_5210		0x8068			/* Wegistew Addwess [5210] */
#define AW5K_DIAG_SW_5211		0x8048			/* Wegistew Addwess [5211+] */
#define AW5K_DIAG_SW			(ah->ah_vewsion == AW5K_AW5210 ? \
					AW5K_DIAG_SW_5210 : AW5K_DIAG_SW_5211)
#define AW5K_DIAG_SW_DIS_WEP_ACK	0x00000001	/* Disabwe ACKs if WEP key is invawid */
#define AW5K_DIAG_SW_DIS_ACK		0x00000002	/* Disabwe ACKs */
#define AW5K_DIAG_SW_DIS_CTS		0x00000004	/* Disabwe CTSs */
#define AW5K_DIAG_SW_DIS_ENC		0x00000008	/* Disabwe HW encwyption */
#define AW5K_DIAG_SW_DIS_DEC		0x00000010	/* Disabwe HW decwyption */
#define AW5K_DIAG_SW_DIS_TX_5210	0x00000020	/* Disabwe twansmit [5210] */
#define AW5K_DIAG_SW_DIS_WX_5210	0x00000040	/* Disabwe weceive */
#define AW5K_DIAG_SW_DIS_WX_5211	0x00000020
#define	AW5K_DIAG_SW_DIS_WX		(ah->ah_vewsion == AW5K_AW5210 ? \
					AW5K_DIAG_SW_DIS_WX_5210 : AW5K_DIAG_SW_DIS_WX_5211)
#define AW5K_DIAG_SW_WOOP_BACK_5210	0x00000080	/* TX Data Woopback (i guess it goes with DIS_TX) [5210] */
#define AW5K_DIAG_SW_WOOP_BACK_5211	0x00000040
#define AW5K_DIAG_SW_WOOP_BACK		(ah->ah_vewsion == AW5K_AW5210 ? \
					AW5K_DIAG_SW_WOOP_BACK_5210 : AW5K_DIAG_SW_WOOP_BACK_5211)
#define AW5K_DIAG_SW_COWW_FCS_5210	0x00000100	/* Genewate invawid TX FCS */
#define AW5K_DIAG_SW_COWW_FCS_5211	0x00000080
#define AW5K_DIAG_SW_COWW_FCS		(ah->ah_vewsion == AW5K_AW5210 ? \
					AW5K_DIAG_SW_COWW_FCS_5210 : AW5K_DIAG_SW_COWW_FCS_5211)
#define AW5K_DIAG_SW_CHAN_INFO_5210	0x00000200	/* Add 56 bytes of channew info befowe the fwame data in the WX buffew */
#define AW5K_DIAG_SW_CHAN_INFO_5211	0x00000100
#define AW5K_DIAG_SW_CHAN_INFO		(ah->ah_vewsion == AW5K_AW5210 ? \
					AW5K_DIAG_SW_CHAN_INFO_5210 : AW5K_DIAG_SW_CHAN_INFO_5211)
#define AW5K_DIAG_SW_EN_SCWAM_SEED_5210	0x00000400	/* Enabwe fixed scwambwew seed */
#define AW5K_DIAG_SW_EN_SCWAM_SEED_5211	0x00000200
#define AW5K_DIAG_SW_EN_SCWAM_SEED	(ah->ah_vewsion == AW5K_AW5210 ? \
					AW5K_DIAG_SW_EN_SCWAM_SEED_5210 : AW5K_DIAG_SW_EN_SCWAM_SEED_5211)
#define AW5K_DIAG_SW_ECO_ENABWE		0x00000400	/* [5211+] */
#define AW5K_DIAG_SW_SCVWAM_SEED	0x0003f800	/* [5210] */
#define AW5K_DIAG_SW_SCWAM_SEED_M	0x0001fc00	/* Scwambwew seed mask */
#define AW5K_DIAG_SW_SCWAM_SEED_S	10
#define AW5K_DIAG_SW_DIS_SEQ_INC_5210	0x00040000	/* Disabwe seqnum incwement (?)[5210] */
#define AW5K_DIAG_SW_FWAME_NV0_5210	0x00080000
#define AW5K_DIAG_SW_FWAME_NV0_5211	0x00020000	/* Accept fwames of non-zewo pwotocow numbew */
#define	AW5K_DIAG_SW_FWAME_NV0		(ah->ah_vewsion == AW5K_AW5210 ? \
					AW5K_DIAG_SW_FWAME_NV0_5210 : AW5K_DIAG_SW_FWAME_NV0_5211)
#define AW5K_DIAG_SW_OBSPT_M		0x000c0000	/* Obsewvation point sewect (?) */
#define AW5K_DIAG_SW_OBSPT_S		18
#define AW5K_DIAG_SW_WX_CWEAW_HIGH	0x00100000	/* Ignowe cawwiew sense */
#define AW5K_DIAG_SW_IGNOWE_CAWW_SENSE	0x00200000	/* Ignowe viwtuaw cawwiew sense */
#define AW5K_DIAG_SW_CHANNEW_IDWE_HIGH	0x00400000	/* Fowce channew idwe high */
#define AW5K_DIAG_SW_PHEAW_ME		0x00800000	/* ??? */

/*
 * TSF (cwock) wegistew (wowew 32 bits)
 */
#define AW5K_TSF_W32_5210	0x806c
#define AW5K_TSF_W32_5211	0x804c
#define	AW5K_TSF_W32		(ah->ah_vewsion == AW5K_AW5210 ? \
				AW5K_TSF_W32_5210 : AW5K_TSF_W32_5211)

/*
 * TSF (cwock) wegistew (highew 32 bits)
 */
#define AW5K_TSF_U32_5210	0x8070
#define AW5K_TSF_U32_5211	0x8050
#define	AW5K_TSF_U32		(ah->ah_vewsion == AW5K_AW5210 ? \
				AW5K_TSF_U32_5210 : AW5K_TSF_U32_5211)

/*
 * Wast beacon timestamp wegistew (Wead Onwy)
 */
#define AW5K_WAST_TSTP	0x8080

/*
 * ADDAC test wegistew [5211+]
 */
#define AW5K_ADDAC_TEST			0x8054			/* Wegistew Addwess */
#define AW5K_ADDAC_TEST_TXCONT		0x00000001	/* Test continuous tx */
#define AW5K_ADDAC_TEST_TST_MODE	0x00000002	/* Test mode */
#define AW5K_ADDAC_TEST_WOOP_EN		0x00000004	/* Enabwe woop */
#define AW5K_ADDAC_TEST_WOOP_WEN	0x00000008	/* Woop wength (fiewd) */
#define AW5K_ADDAC_TEST_USE_U8		0x00004000	/* Use uppew 8 bits */
#define AW5K_ADDAC_TEST_MSB		0x00008000	/* State of MSB */
#define AW5K_ADDAC_TEST_TWIG_SEW	0x00010000	/* Twiggew sewect */
#define AW5K_ADDAC_TEST_TWIG_PTY	0x00020000	/* Twiggew powawity */
#define AW5K_ADDAC_TEST_WXCONT		0x00040000	/* Continuous captuwe */
#define AW5K_ADDAC_TEST_CAPTUWE		0x00080000	/* Begin captuwe */
#define AW5K_ADDAC_TEST_TST_AWM		0x00100000	/* AWM wx buffew fow captuwe */

/*
 * Defauwt antenna wegistew [5211+]
 */
#define AW5K_DEFAUWT_ANTENNA	0x8058

/*
 * Fwame contwow QoS mask wegistew (?) [5211+]
 * (FC_QOS_MASK)
 */
#define AW5K_FWAME_CTW_QOSM	0x805c

/*
 * Seq mask wegistew (?) [5211+]
 */
#define AW5K_SEQ_MASK	0x8060

/*
 * Wetwy count wegistew [5210]
 */
#define AW5K_WETWY_CNT		0x8084			/* Wegistew Addwess [5210] */
#define AW5K_WETWY_CNT_SSH	0x0000003f	/* Station showt wetwy count (?) */
#define AW5K_WETWY_CNT_SWG	0x00000fc0	/* Station wong wetwy count (?) */

/*
 * Back-off status wegistew [5210]
 */
#define AW5K_BACKOFF		0x8088			/* Wegistew Addwess [5210] */
#define AW5K_BACKOFF_CW		0x000003ff	/* Backoff Contention Window (?) */
#define AW5K_BACKOFF_CNT	0x03ff0000	/* Backoff count (?) */



/*
 * NAV wegistew (cuwwent)
 */
#define AW5K_NAV_5210		0x808c
#define AW5K_NAV_5211		0x8084
#define	AW5K_NAV		(ah->ah_vewsion == AW5K_AW5210 ? \
				AW5K_NAV_5210 : AW5K_NAV_5211)

/*
 * MIB countews:
 *
 * max vawue is 0xc000, if this is weached we get a MIB intewwupt.
 * they can be contwowwed via AW5K_MIBC and awe cweawed on wead.
 */

/*
 * WTS success (MIB countew)
 */
#define AW5K_WTS_OK_5210	0x8090
#define AW5K_WTS_OK_5211	0x8088
#define	AW5K_WTS_OK		(ah->ah_vewsion == AW5K_AW5210 ? \
				AW5K_WTS_OK_5210 : AW5K_WTS_OK_5211)

/*
 * WTS faiwuwe (MIB countew)
 */
#define AW5K_WTS_FAIW_5210	0x8094
#define AW5K_WTS_FAIW_5211	0x808c
#define	AW5K_WTS_FAIW		(ah->ah_vewsion == AW5K_AW5210 ? \
				AW5K_WTS_FAIW_5210 : AW5K_WTS_FAIW_5211)

/*
 * ACK faiwuwe (MIB countew)
 */
#define AW5K_ACK_FAIW_5210	0x8098
#define AW5K_ACK_FAIW_5211	0x8090
#define	AW5K_ACK_FAIW		(ah->ah_vewsion == AW5K_AW5210 ? \
				AW5K_ACK_FAIW_5210 : AW5K_ACK_FAIW_5211)

/*
 * FCS faiwuwe (MIB countew)
 */
#define AW5K_FCS_FAIW_5210	0x809c
#define AW5K_FCS_FAIW_5211	0x8094
#define	AW5K_FCS_FAIW		(ah->ah_vewsion == AW5K_AW5210 ? \
				AW5K_FCS_FAIW_5210 : AW5K_FCS_FAIW_5211)

/*
 * Beacon count wegistew
 */
#define AW5K_BEACON_CNT_5210	0x80a0
#define AW5K_BEACON_CNT_5211	0x8098
#define	AW5K_BEACON_CNT		(ah->ah_vewsion == AW5K_AW5210 ? \
				AW5K_BEACON_CNT_5210 : AW5K_BEACON_CNT_5211)


/*===5212 Specific PCU wegistews===*/

/*
 * Twansmit powew contwow wegistew
 */
#define AW5K_TPC			0x80e8
#define AW5K_TPC_ACK			0x0000003f	/* ack fwames */
#define AW5K_TPC_ACK_S			0
#define AW5K_TPC_CTS			0x00003f00	/* cts fwames */
#define AW5K_TPC_CTS_S			8
#define AW5K_TPC_CHIWP			0x003f0000	/* chiwp fwames */
#define AW5K_TPC_CHIWP_S		16
#define AW5K_TPC_DOPPWEW		0x0f000000	/* doppwew chiwp span */
#define AW5K_TPC_DOPPWEW_S		24

/*
 * XW (eXtended Wange) mode wegistew
 */
#define AW5K_XWMODE			0x80c0			/* Wegistew Addwess */
#define	AW5K_XWMODE_POWW_TYPE_M		0x0000003f	/* Mask fow Poww type (?) */
#define	AW5K_XWMODE_POWW_TYPE_S		0
#define	AW5K_XWMODE_POWW_SUBTYPE_M	0x0000003c	/* Mask fow Poww subtype (?) */
#define	AW5K_XWMODE_POWW_SUBTYPE_S	2
#define	AW5K_XWMODE_POWW_WAIT_AWW	0x00000080	/* Wait fow poww */
#define	AW5K_XWMODE_SIFS_DEWAY		0x000fff00	/* Mask fow SIFS deway */
#define	AW5K_XWMODE_FWAME_HOWD_M	0xfff00000	/* Mask fow fwame howd (?) */
#define	AW5K_XWMODE_FWAME_HOWD_S	20

/*
 * XW deway wegistew
 */
#define AW5K_XWDEWAY			0x80c4			/* Wegistew Addwess */
#define AW5K_XWDEWAY_SWOT_DEWAY_M	0x0000ffff	/* Mask fow swot deway */
#define AW5K_XWDEWAY_SWOT_DEWAY_S	0
#define AW5K_XWDEWAY_CHIWP_DEWAY_M	0xffff0000	/* Mask fow CHIWP data deway */
#define AW5K_XWDEWAY_CHIWP_DEWAY_S	16

/*
 * XW timeout wegistew
 */
#define AW5K_XWTIMEOUT			0x80c8			/* Wegistew Addwess */
#define AW5K_XWTIMEOUT_CHIWP_M		0x0000ffff	/* Mask fow CHIWP timeout */
#define AW5K_XWTIMEOUT_CHIWP_S		0
#define AW5K_XWTIMEOUT_POWW_M		0xffff0000	/* Mask fow Poww timeout */
#define AW5K_XWTIMEOUT_POWW_S		16

/*
 * XW chiwp wegistew
 */
#define AW5K_XWCHIWP			0x80cc			/* Wegistew Addwess */
#define AW5K_XWCHIWP_SEND		0x00000001	/* Send CHIWP */
#define AW5K_XWCHIWP_GAP		0xffff0000	/* Mask fow CHIWP gap (?) */

/*
 * XW stomp wegistew
 */
#define AW5K_XWSTOMP			0x80d0			/* Wegistew Addwess */
#define AW5K_XWSTOMP_TX			0x00000001	/* Stomp Tx (?) */
#define AW5K_XWSTOMP_WX			0x00000002	/* Stomp Wx (?) */
#define AW5K_XWSTOMP_TX_WSSI		0x00000004	/* Stomp Tx WSSI (?) */
#define AW5K_XWSTOMP_TX_BSSID		0x00000008	/* Stomp Tx BSSID (?) */
#define AW5K_XWSTOMP_DATA		0x00000010	/* Stomp data (?)*/
#define AW5K_XWSTOMP_WSSI_THWES		0x0000ff00	/* Mask fow XW WSSI thweshowd */

/*
 * Fiwst enhanced sweep wegistew
 */
#define AW5K_SWEEP0			0x80d4			/* Wegistew Addwess */
#define AW5K_SWEEP0_NEXT_DTIM		0x0007ffff	/* Mask fow next DTIM (?) */
#define AW5K_SWEEP0_NEXT_DTIM_S		0
#define AW5K_SWEEP0_ASSUME_DTIM		0x00080000	/* Assume DTIM */
#define AW5K_SWEEP0_ENH_SWEEP_EN	0x00100000	/* Enabwe enhanced sweep contwow */
#define AW5K_SWEEP0_CABTO		0xff000000	/* Mask fow CAB Time Out */
#define AW5K_SWEEP0_CABTO_S		24

/*
 * Second enhanced sweep wegistew
 */
#define AW5K_SWEEP1			0x80d8			/* Wegistew Addwess */
#define AW5K_SWEEP1_NEXT_TIM		0x0007ffff	/* Mask fow next TIM (?) */
#define AW5K_SWEEP1_NEXT_TIM_S		0
#define AW5K_SWEEP1_BEACON_TO		0xff000000	/* Mask fow Beacon Time Out */
#define AW5K_SWEEP1_BEACON_TO_S		24

/*
 * Thiwd enhanced sweep wegistew
 */
#define AW5K_SWEEP2			0x80dc			/* Wegistew Addwess */
#define AW5K_SWEEP2_TIM_PEW		0x0000ffff	/* Mask fow TIM pewiod (?) */
#define AW5K_SWEEP2_TIM_PEW_S		0
#define AW5K_SWEEP2_DTIM_PEW		0xffff0000	/* Mask fow DTIM pewiod (?) */
#define AW5K_SWEEP2_DTIM_PEW_S		16

/*
 * TX powew contwow (TPC) wegistew
 *
 * XXX: PCDAC steps (0.5dBm) ow dBm ?
 *
 */
#define AW5K_TXPC			0x80e8			/* Wegistew Addwess */
#define AW5K_TXPC_ACK_M			0x0000003f	/* ACK tx powew */
#define AW5K_TXPC_ACK_S			0
#define AW5K_TXPC_CTS_M			0x00003f00	/* CTS tx powew */
#define AW5K_TXPC_CTS_S			8
#define AW5K_TXPC_CHIWP_M		0x003f0000	/* CHIWP tx powew */
#define AW5K_TXPC_CHIWP_S		16
#define AW5K_TXPC_DOPPWEW		0x0f000000	/* Doppwew chiwp span (?) */
#define AW5K_TXPC_DOPPWEW_S		24

/*
 * Pwofiwe count wegistews
 *
 * These wegistews can be cweawed and fwozen with ATH5K_MIBC, but they do not
 * genewate a MIB intewwupt.
 * Instead of ovewfwowing, they shift by one bit to the wight. Aww wegistews
 * shift togethew, i.e. when one weaches the max, aww shift at the same time by
 * one bit to the wight. This way we shouwd awways get consistent vawues.
 */
#define AW5K_PWOFCNT_TX			0x80ec	/* Tx count */
#define AW5K_PWOFCNT_WX			0x80f0	/* Wx count */
#define AW5K_PWOFCNT_WXCWW		0x80f4	/* Busy count */
#define AW5K_PWOFCNT_CYCWE		0x80f8	/* Cycwe countew */

/*
 * Quiet pewiod contwow wegistews
 */
#define AW5K_QUIET_CTW1			0x80fc			/* Wegistew Addwess */
#define AW5K_QUIET_CTW1_NEXT_QT_TSF	0x0000ffff	/* Next quiet pewiod TSF (TU) */
#define AW5K_QUIET_CTW1_NEXT_QT_TSF_S	0
#define AW5K_QUIET_CTW1_QT_EN		0x00010000	/* Enabwe quiet pewiod */
#define AW5K_QUIET_CTW1_ACK_CTS_EN	0x00020000	/* Send ACK/CTS duwing quiet pewiod */

#define AW5K_QUIET_CTW2			0x8100			/* Wegistew Addwess */
#define AW5K_QUIET_CTW2_QT_PEW		0x0000ffff	/* Mask fow quiet pewiod pewiodicity */
#define AW5K_QUIET_CTW2_QT_PEW_S	0
#define AW5K_QUIET_CTW2_QT_DUW		0xffff0000	/* Mask fow quiet pewiod duwation */
#define AW5K_QUIET_CTW2_QT_DUW_S	16

/*
 * TSF pawametew wegistew
 */
#define AW5K_TSF_PAWM			0x8104			/* Wegistew Addwess */
#define AW5K_TSF_PAWM_INC		0x000000ff	/* Mask fow TSF incwement */
#define AW5K_TSF_PAWM_INC_S		0

/*
 * QoS NOACK powicy
 */
#define AW5K_QOS_NOACK			0x8108			/* Wegistew Addwess */
#define AW5K_QOS_NOACK_2BIT_VAWUES	0x0000000f	/* ??? */
#define AW5K_QOS_NOACK_2BIT_VAWUES_S	0
#define AW5K_QOS_NOACK_BIT_OFFSET	0x00000070	/* ??? */
#define AW5K_QOS_NOACK_BIT_OFFSET_S	4
#define AW5K_QOS_NOACK_BYTE_OFFSET	0x00000180	/* ??? */
#define AW5K_QOS_NOACK_BYTE_OFFSET_S	7

/*
 * PHY ewwow fiwtew wegistew
 */
#define AW5K_PHY_EWW_FIW		0x810c
#define AW5K_PHY_EWW_FIW_WADAW		0x00000020	/* Wadaw signaw */
#define AW5K_PHY_EWW_FIW_OFDM		0x00020000	/* OFDM fawse detect (ANI) */
#define AW5K_PHY_EWW_FIW_CCK		0x02000000	/* CCK fawse detect (ANI) */

/*
 * XW watency wegistew
 */
#define AW5K_XWWAT_TX		0x8110

/*
 * ACK SIFS wegistew
 */
#define AW5K_ACKSIFS		0x8114			/* Wegistew Addwess */
#define AW5K_ACKSIFS_INC	0x00000000	/* ACK SIFS Incwement (fiewd) */

/*
 * MIC QoS contwow wegistew (?)
 */
#define	AW5K_MIC_QOS_CTW		0x8118			/* Wegistew Addwess */
#define	AW5K_MIC_QOS_CTW_OFF(_n)	(1 << (_n * 2))
#define	AW5K_MIC_QOS_CTW_MQ_EN		0x00010000	/* Enabwe MIC QoS */

/*
 * MIC QoS sewect wegistew (?)
 */
#define	AW5K_MIC_QOS_SEW		0x811c
#define	AW5K_MIC_QOS_SEW_OFF(_n)	(1 << (_n * 4))

/*
 * Misc mode contwow wegistew (?)
 */
#define	AW5K_MISC_MODE			0x8120			/* Wegistew Addwess */
#define	AW5K_MISC_MODE_FBSSID_MATCH	0x00000001	/* Fowce BSSID match */
#define	AW5K_MISC_MODE_ACKSIFS_MEM	0x00000002	/* ACK SIFS memowy (?) */
#define	AW5K_MISC_MODE_COMBINED_MIC	0x00000004	/* use wx/tx MIC key */
/* mowe bits */

/*
 * OFDM Fiwtew countew
 */
#define	AW5K_OFDM_FIW_CNT		0x8124

/*
 * CCK Fiwtew countew
 */
#define	AW5K_CCK_FIW_CNT		0x8128

/*
 * PHY Ewwow Countews (same masks as AW5K_PHY_EWW_FIW)
 */
#define	AW5K_PHYEWW_CNT1		0x812c
#define	AW5K_PHYEWW_CNT1_MASK		0x8130

#define	AW5K_PHYEWW_CNT2		0x8134
#define	AW5K_PHYEWW_CNT2_MASK		0x8138

/* if the PHY Ewwow Countews weach this maximum, we get MIB intewwupts */
#define ATH5K_PHYEWW_CNT_MAX		0x00c00000

/*
 * TSF Thweshowd wegistew (?)
 */
#define	AW5K_TSF_THWES			0x813c

/*
 * TODO: Wake On Wiwewess wegistews
 * Wange: 0x8147 - 0x818c
 */

/*
 * Wate -> ACK SIFS mapping tabwe (32 entwies)
 */
#define	AW5K_WATE_ACKSIFS_BASE		0x8680			/* Wegistew Addwess */
#define	AW5K_WATE_ACKSIFS(_n)		(AW5K_WATE_ACKSIFS_BSE + ((_n) << 2))
#define	AW5K_WATE_ACKSIFS_NOWMAW	0x00000001	/* Nowmaw SIFS (fiewd) */
#define	AW5K_WATE_ACKSIFS_TUWBO		0x00000400	/* Tuwbo SIFS (fiewd) */

/*
 * Wate -> duwation mapping tabwe (32 entwies)
 */
#define AW5K_WATE_DUW_BASE		0x8700
#define AW5K_WATE_DUW(_n)		(AW5K_WATE_DUW_BASE + ((_n) << 2))

/*
 * Wate -> db mapping tabwe
 * (8 entwies, each one has 4 8bit fiewds)
 */
#define AW5K_WATE2DB_BASE		0x87c0
#define AW5K_WATE2DB(_n)		(AW5K_WATE2DB_BASE + ((_n) << 2))

/*
 * db -> Wate mapping tabwe
 * (8 entwies, each one has 4 8bit fiewds)
 */
#define AW5K_DB2WATE_BASE		0x87e0
#define AW5K_DB2WATE(_n)		(AW5K_DB2WATE_BASE + ((_n) << 2))

/*===5212 end===*/

#define AW5K_KEYTABWE_SIZE_5210		64
#define AW5K_KEYTABWE_SIZE_5211		128

/*===PHY WEGISTEWS===*/

/*
 * PHY wegistews stawt
 */
#define	AW5K_PHY_BASE			0x9800
#define	AW5K_PHY(_n)			(AW5K_PHY_BASE + ((_n) << 2))

/*
 * TST_2 (Misc config pawametews)
 */
#define	AW5K_PHY_TST2			0x9800			/* Wegistew Addwess */
#define AW5K_PHY_TST2_TWIG_SEW		0x00000007	/* Twiggew sewect (?)*/
#define AW5K_PHY_TST2_TWIG		0x00000010	/* Twiggew (?) */
#define AW5K_PHY_TST2_CBUS_MODE		0x00000060	/* Cawdbus mode (?) */
#define AW5K_PHY_TST2_CWK32		0x00000400	/* CWK_OUT is CWK32 (32kHz extewnaw) */
#define AW5K_PHY_TST2_CHANCOW_DUMP_EN	0x00000800	/* Enabwe Chancow dump (?) */
#define AW5K_PHY_TST2_EVEN_CHANCOW_DUMP	0x00001000	/* Even Chancow dump (?) */
#define AW5K_PHY_TST2_WFSIWENT_EN	0x00002000	/* Enabwe WFSIWENT */
#define AW5K_PHY_TST2_AWT_WFDATA	0x00004000	/* Awtewnate WFDATA (5-2GHz switch ?) */
#define AW5K_PHY_TST2_MINI_OBS_EN	0x00008000	/* Enabwe mini OBS (?) */
#define AW5K_PHY_TST2_WX2_IS_WX5_INV	0x00010000	/* 2GHz wx path is the 5GHz path invewted (?) */
#define AW5K_PHY_TST2_SWOW_CWK160	0x00020000	/* Swow CWK160 (?) */
#define AW5K_PHY_TST2_AGC_OBS_SEW_3	0x00040000	/* AGC OBS Sewect 3 (?) */
#define AW5K_PHY_TST2_BBB_OBS_SEW	0x00080000	/* BB OBS Sewect (fiewd ?) */
#define AW5K_PHY_TST2_ADC_OBS_SEW	0x00800000	/* ADC OBS Sewect (fiewd ?) */
#define AW5K_PHY_TST2_WX_CWW_SEW	0x08000000	/* WX Cweaw Sewect (?) */
#define AW5K_PHY_TST2_FOWCE_AGC_CWW	0x10000000	/* Fowce AGC cweaw (?) */
#define AW5K_PHY_SHIFT_2GHZ		0x00004007	/* Used to access 2GHz wadios */
#define AW5K_PHY_SHIFT_5GHZ		0x00000007	/* Used to access 5GHz wadios (defauwt) */

/*
 * PHY fwame contwow wegistew [5110] /tuwbo mode wegistew [5111+]
 *
 * Thewe is anothew fwame contwow wegistew fow [5111+]
 * at addwess 0x9944 (see bewow) but the 2 fiwst fwags
 * awe common hewe between 5110 fwame contwow wegistew
 * and [5111+] tuwbo mode wegistew, so this awso wowks as
 * a "tuwbo mode wegistew" fow 5110. We tweat this one as
 * a fwame contwow wegistew fow 5110 bewow.
 */
#define	AW5K_PHY_TUWBO			0x9804			/* Wegistew Addwess */
#define	AW5K_PHY_TUWBO_MODE		0x00000001	/* Enabwe tuwbo mode */
#define	AW5K_PHY_TUWBO_SHOWT		0x00000002	/* Set showt symbows to tuwbo mode */
#define	AW5K_PHY_TUWBO_MIMO		0x00000004	/* Set tuwbo fow mimo */

/*
 * PHY agiwity command wegistew
 * (aka TST_1)
 */
#define	AW5K_PHY_AGC			0x9808			/* Wegistew Addwess */
#define	AW5K_PHY_TST1			0x9808
#define	AW5K_PHY_AGC_DISABWE		0x08000000	/* Disabwe AGC to A2 (?)*/
#define	AW5K_PHY_TST1_TXHOWD		0x00003800	/* Set tx howd (?) */
#define	AW5K_PHY_TST1_TXSWC_SWC		0x00000002	/* Used with bit 7 (?) */
#define	AW5K_PHY_TST1_TXSWC_SWC_S	1
#define	AW5K_PHY_TST1_TXSWC_AWT		0x00000080	/* Set input to tsdac (?) */
#define	AW5K_PHY_TST1_TXSWC_AWT_S	7


/*
 * PHY timing wegistew 3 [5112+]
 */
#define	AW5K_PHY_TIMING_3		0x9814
#define	AW5K_PHY_TIMING_3_DSC_MAN	0xfffe0000
#define	AW5K_PHY_TIMING_3_DSC_MAN_S	17
#define	AW5K_PHY_TIMING_3_DSC_EXP	0x0001e000
#define	AW5K_PHY_TIMING_3_DSC_EXP_S	13

/*
 * PHY chip wevision wegistew
 */
#define	AW5K_PHY_CHIP_ID		0x9818

/*
 * PHY activation wegistew
 */
#define	AW5K_PHY_ACT			0x981c			/* Wegistew Addwess */
#define	AW5K_PHY_ACT_ENABWE		0x00000001	/* Activate PHY */
#define	AW5K_PHY_ACT_DISABWE		0x00000002	/* Deactivate PHY */

/*
 * PHY WF contwow wegistews
 */
#define AW5K_PHY_WF_CTW2		0x9824			/* Wegistew Addwess */
#define	AW5K_PHY_WF_CTW2_TXF2TXD_STAWT	0x0000000f	/* TX fwame to TX data stawt */
#define	AW5K_PHY_WF_CTW2_TXF2TXD_STAWT_S	0

#define AW5K_PHY_WF_CTW3		0x9828			/* Wegistew Addwess */
#define AW5K_PHY_WF_CTW3_TXE2XWNA_ON	0x0000ff00	/* TX end to XWNA on */
#define	AW5K_PHY_WF_CTW3_TXE2XWNA_ON_S	8

#define	AW5K_PHY_ADC_CTW			0x982c
#define	AW5K_PHY_ADC_CTW_INBUFGAIN_OFF		0x00000003
#define	AW5K_PHY_ADC_CTW_INBUFGAIN_OFF_S	0
#define	AW5K_PHY_ADC_CTW_PWD_DAC_OFF		0x00002000
#define	AW5K_PHY_ADC_CTW_PWD_BAND_GAP_OFF	0x00004000
#define	AW5K_PHY_ADC_CTW_PWD_ADC_OFF		0x00008000
#define	AW5K_PHY_ADC_CTW_INBUFGAIN_ON		0x00030000
#define	AW5K_PHY_ADC_CTW_INBUFGAIN_ON_S		16

#define AW5K_PHY_WF_CTW4		0x9834			/* Wegistew Addwess */
#define AW5K_PHY_WF_CTW4_TXF2XPA_A_ON	0x00000001	/* TX fwame to XPA A on (fiewd) */
#define AW5K_PHY_WF_CTW4_TXF2XPA_B_ON	0x00000100	/* TX fwame to XPA B on (fiewd) */
#define	AW5K_PHY_WF_CTW4_TXE2XPA_A_OFF	0x00010000	/* TX end to XPA A off (fiewd) */
#define AW5K_PHY_WF_CTW4_TXE2XPA_B_OFF	0x01000000	/* TX end to XPA B off (fiewd) */

/*
 * Pwe-Ampwifiew contwow wegistew
 * (XPA -> extewnaw pwe-ampwifiew)
 */
#define	AW5K_PHY_PA_CTW			0x9838			/* Wegistew Addwess */
#define	AW5K_PHY_PA_CTW_XPA_A_HI	0x00000001	/* XPA A high (?) */
#define	AW5K_PHY_PA_CTW_XPA_B_HI	0x00000002	/* XPA B high (?) */
#define	AW5K_PHY_PA_CTW_XPA_A_EN	0x00000004	/* Enabwe XPA A */
#define	AW5K_PHY_PA_CTW_XPA_B_EN	0x00000008	/* Enabwe XPA B */

/*
 * PHY settwing wegistew
 */
#define AW5K_PHY_SETTWING		0x9844			/* Wegistew Addwess */
#define	AW5K_PHY_SETTWING_AGC		0x0000007f	/* AGC settwing time */
#define	AW5K_PHY_SETTWING_AGC_S		0
#define	AW5K_PHY_SETTWING_SWITCH	0x00003f80	/* Switch settwing time */
#define	AW5K_PHY_SETTWING_SWITCH_S	7

/*
 * PHY Gain wegistews
 */
#define AW5K_PHY_GAIN			0x9848			/* Wegistew Addwess */
#define	AW5K_PHY_GAIN_TXWX_ATTEN	0x0003f000	/* TX-WX Attenuation */
#define	AW5K_PHY_GAIN_TXWX_ATTEN_S	12
#define	AW5K_PHY_GAIN_TXWX_WF_MAX	0x007c0000
#define	AW5K_PHY_GAIN_TXWX_WF_MAX_S	18

#define	AW5K_PHY_GAIN_OFFSET		0x984c			/* Wegistew Addwess */
#define	AW5K_PHY_GAIN_OFFSET_WXTX_FWAG	0x00020000	/* WX-TX fwag (?) */

/*
 * Desiwed ADC/PGA size wegistew
 * (fow mowe infos wead ANI patent)
 */
#define AW5K_PHY_DESIWED_SIZE		0x9850			/* Wegistew Addwess */
#define	AW5K_PHY_DESIWED_SIZE_ADC	0x000000ff	/* ADC desiwed size */
#define	AW5K_PHY_DESIWED_SIZE_ADC_S	0
#define	AW5K_PHY_DESIWED_SIZE_PGA	0x0000ff00	/* PGA desiwed size */
#define	AW5K_PHY_DESIWED_SIZE_PGA_S	8
#define	AW5K_PHY_DESIWED_SIZE_TOT	0x0ff00000	/* Totaw desiwed size */
#define	AW5K_PHY_DESIWED_SIZE_TOT_S	20

/*
 * PHY signaw wegistew
 * (fow mowe infos wead ANI patent)
 */
#define	AW5K_PHY_SIG			0x9858			/* Wegistew Addwess */
#define	AW5K_PHY_SIG_FIWSTEP		0x0003f000	/* FIWSTEP */
#define	AW5K_PHY_SIG_FIWSTEP_S		12
#define	AW5K_PHY_SIG_FIWPWW		0x03fc0000	/* FIPWW */
#define	AW5K_PHY_SIG_FIWPWW_S		18

/*
 * PHY coawse agiwity contwow wegistew
 * (fow mowe infos wead ANI patent)
 */
#define	AW5K_PHY_AGCCOAWSE		0x985c			/* Wegistew Addwess */
#define	AW5K_PHY_AGCCOAWSE_WO		0x00007f80	/* AGC Coawse wow */
#define	AW5K_PHY_AGCCOAWSE_WO_S		7
#define	AW5K_PHY_AGCCOAWSE_HI		0x003f8000	/* AGC Coawse high */
#define	AW5K_PHY_AGCCOAWSE_HI_S		15

/*
 * PHY agiwity contwow wegistew
 */
#define	AW5K_PHY_AGCCTW			0x9860			/* Wegistew addwess */
#define	AW5K_PHY_AGCCTW_CAW		0x00000001	/* Enabwe PHY cawibwation */
#define	AW5K_PHY_AGCCTW_NF		0x00000002	/* Enabwe Noise Fwoow cawibwation */
#define	AW5K_PHY_AGCCTW_OFDM_DIV_DIS	0x00000008	/* Disabwe antenna divewsity on OFDM modes */
#define	AW5K_PHY_AGCCTW_NF_EN		0x00008000	/* Enabwe nf cawibwation to happen (?) */
#define	AW5K_PHY_AGCTW_FWTW_CAW		0x00010000	/* Awwow fiwtew cawibwation (?) */
#define	AW5K_PHY_AGCCTW_NF_NOUPDATE	0x00020000	/* Don't update nf automaticawwy */

/*
 * PHY noise fwoow status wegistew (CCA = Cweaw Channew Assessment)
 */
#define AW5K_PHY_NF			0x9864			/* Wegistew addwess */
#define AW5K_PHY_NF_M			0x000001ff	/* Noise fwoow, wwitten to hawdwawe in 1/2 dBm units */
#define AW5K_PHY_NF_SVAW(_n)           (((_n) & AW5K_PHY_NF_M) | (1 << 9))
#define	AW5K_PHY_NF_THWESH62		0x0007f000	/* Thwesh62 -check ANI patent- (fiewd) */
#define	AW5K_PHY_NF_THWESH62_S		12
#define	AW5K_PHY_NF_MINCCA_PWW		0x0ff80000	/* Minimum measuwed noise wevew, wead fwom hawdwawe in 1 dBm units */
#define	AW5K_PHY_NF_MINCCA_PWW_S	19

/*
 * PHY ADC satuwation wegistew [5110]
 */
#define	AW5K_PHY_ADCSAT			0x9868
#define	AW5K_PHY_ADCSAT_ICNT		0x0001f800
#define	AW5K_PHY_ADCSAT_ICNT_S		11
#define	AW5K_PHY_ADCSAT_THW		0x000007e0
#define	AW5K_PHY_ADCSAT_THW_S		5

/*
 * PHY Weak ofdm signaw detection thweshowd wegistews (ANI) [5212+]
 */

/* High thweshowds */
#define AW5K_PHY_WEAK_OFDM_HIGH_THW		0x9868
#define AW5K_PHY_WEAK_OFDM_HIGH_THW_M2_COUNT	0x0000001f
#define AW5K_PHY_WEAK_OFDM_HIGH_THW_M2_COUNT_S	0
#define AW5K_PHY_WEAK_OFDM_HIGH_THW_M1		0x00fe0000
#define AW5K_PHY_WEAK_OFDM_HIGH_THW_M1_S	17
#define AW5K_PHY_WEAK_OFDM_HIGH_THW_M2		0x7f000000
#define AW5K_PHY_WEAK_OFDM_HIGH_THW_M2_S	24

/* Wow thweshowds */
#define AW5K_PHY_WEAK_OFDM_WOW_THW		0x986c
#define AW5K_PHY_WEAK_OFDM_WOW_THW_SEWFCOW_EN	0x00000001
#define AW5K_PHY_WEAK_OFDM_WOW_THW_M2_COUNT	0x00003f00
#define AW5K_PHY_WEAK_OFDM_WOW_THW_M2_COUNT_S	8
#define AW5K_PHY_WEAK_OFDM_WOW_THW_M1		0x001fc000
#define AW5K_PHY_WEAK_OFDM_WOW_THW_M1_S		14
#define AW5K_PHY_WEAK_OFDM_WOW_THW_M2		0x0fe00000
#define AW5K_PHY_WEAK_OFDM_WOW_THW_M2_S		21


/*
 * PHY sweep wegistews [5112+]
 */
#define AW5K_PHY_SCW			0x9870

#define AW5K_PHY_SWMT			0x9874
#define AW5K_PHY_SWMT_32MHZ		0x0000007f

#define AW5K_PHY_SCAW			0x9878
#define AW5K_PHY_SCAW_32MHZ		0x0000000e
#define	AW5K_PHY_SCAW_32MHZ_5311	0x00000008
#define	AW5K_PHY_SCAW_32MHZ_2417	0x0000000a
#define	AW5K_PHY_SCAW_32MHZ_HB63	0x00000032

/*
 * PHY PWW (Phase Wocked Woop) contwow wegistew
 */
#define	AW5K_PHY_PWW			0x987c
#define	AW5K_PHY_PWW_20MHZ		0x00000013	/* Fow hawf wate (?) */
/* 40MHz -> 5GHz band */
#define	AW5K_PHY_PWW_40MHZ_5211		0x00000018
#define	AW5K_PHY_PWW_40MHZ_5212		0x000000aa
#define	AW5K_PHY_PWW_40MHZ_5413		0x00000004
#define	AW5K_PHY_PWW_40MHZ		(ah->ah_vewsion == AW5K_AW5211 ? \
					AW5K_PHY_PWW_40MHZ_5211 : AW5K_PHY_PWW_40MHZ_5212)
/* 44MHz -> 2.4GHz band */
#define	AW5K_PHY_PWW_44MHZ_5211		0x00000019
#define	AW5K_PHY_PWW_44MHZ_5212		0x000000ab
#define	AW5K_PHY_PWW_44MHZ		(ah->ah_vewsion == AW5K_AW5211 ? \
					AW5K_PHY_PWW_44MHZ_5211 : AW5K_PHY_PWW_44MHZ_5212)

#define AW5K_PHY_PWW_WF5111		0x00000000
#define AW5K_PHY_PWW_WF5112		0x00000040
#define	AW5K_PHY_PWW_HAWF_WATE		0x00000100
#define	AW5K_PHY_PWW_QUAWTEW_WATE	0x00000200

/*
 * WF Buffew wegistew
 *
 * It's obvious fwom the code that 0x989c is the buffew wegistew but
 * fow the othew speciaw wegistews that we wwite to aftew sending each
 * packet, i have no idea. So I'ww name them BUFFEW_CONTWOW_X wegistews
 * fow now. It's intewesting that they awe awso used fow some othew opewations.
 */

#define AW5K_WF_BUFFEW			0x989c
#define AW5K_WF_BUFFEW_CONTWOW_0	0x98c0	/* Channew on 5110 */
#define AW5K_WF_BUFFEW_CONTWOW_1	0x98c4	/* Bank 7 on 5112 */
#define AW5K_WF_BUFFEW_CONTWOW_2	0x98cc	/* Bank 7 on 5111 */

#define AW5K_WF_BUFFEW_CONTWOW_3	0x98d0	/* Bank 2 on 5112 */
						/* Channew set on 5111 */
						/* Used to wead wadio wevision*/

#define AW5K_WF_BUFFEW_CONTWOW_4	0x98d4  /* WF Stage wegistew on 5110 */
						/* Bank 0,1,2,6 on 5111 */
						/* Bank 1 on 5112 */
						/* Used duwing activation on 5111 */

#define AW5K_WF_BUFFEW_CONTWOW_5	0x98d8	/* Bank 3 on 5111 */
						/* Used duwing activation on 5111 */
						/* Channew on 5112 */
						/* Bank 6 on 5112 */

#define AW5K_WF_BUFFEW_CONTWOW_6	0x98dc	/* Bank 3 on 5112 */

/*
 * PHY WF stage wegistew [5210]
 */
#define AW5K_PHY_WFSTG			0x98d4
#define AW5K_PHY_WFSTG_DISABWE		0x00000021

/*
 * BIN masks (?)
 */
#define	AW5K_PHY_BIN_MASK_1	0x9900
#define	AW5K_PHY_BIN_MASK_2	0x9904
#define	AW5K_PHY_BIN_MASK_3	0x9908

#define	AW5K_PHY_BIN_MASK_CTW		0x990c
#define	AW5K_PHY_BIN_MASK_CTW_MASK_4	0x00003fff
#define	AW5K_PHY_BIN_MASK_CTW_MASK_4_S	0
#define	AW5K_PHY_BIN_MASK_CTW_WATE	0xff000000
#define	AW5K_PHY_BIN_MASK_CTW_WATE_S	24

/*
 * PHY Antenna contwow wegistew
 */
#define AW5K_PHY_ANT_CTW		0x9910			/* Wegistew Addwess */
#define	AW5K_PHY_ANT_CTW_TXWX_EN	0x00000001	/* Enabwe TX/WX (?) */
#define	AW5K_PHY_ANT_CTW_SECTOWED_ANT	0x00000004	/* Sectowed Antenna */
#define	AW5K_PHY_ANT_CTW_HITUNE5	0x00000008	/* Hitune5 (?) */
#define	AW5K_PHY_ANT_CTW_SWTABWE_IDWE	0x000003f0	/* Switch tabwe idwe (?) */
#define	AW5K_PHY_ANT_CTW_SWTABWE_IDWE_S	4

/*
 * PHY weceivew deway wegistew [5111+]
 */
#define	AW5K_PHY_WX_DEWAY		0x9914			/* Wegistew Addwess */
#define	AW5K_PHY_WX_DEWAY_M		0x00003fff	/* Mask fow WX activate to weceive deway (/100ns) */

/*
 * PHY max wx wength wegistew (?) [5111]
 */
#define	AW5K_PHY_MAX_WX_WEN		0x991c

/*
 * PHY timing wegistew 4
 * I(nphase)/Q(adwatuwe) cawibwation wegistew [5111+]
 */
#define	AW5K_PHY_IQ			0x9920			/* Wegistew Addwess */
#define	AW5K_PHY_IQ_COWW_Q_Q_COFF	0x0000001f	/* Mask fow q cowwection info */
#define	AW5K_PHY_IQ_COWW_Q_Q_COFF_S	0
#define	AW5K_PHY_IQ_COWW_Q_I_COFF	0x000007e0	/* Mask fow i cowwection info */
#define	AW5K_PHY_IQ_COWW_Q_I_COFF_S	5
#define	AW5K_PHY_IQ_COWW_ENABWE		0x00000800	/* Enabwe i/q cowwection */
#define	AW5K_PHY_IQ_CAW_NUM_WOG_MAX	0x0000f000	/* Mask fow max numbew of sampwes in wog scawe */
#define	AW5K_PHY_IQ_CAW_NUM_WOG_MAX_S	12
#define	AW5K_PHY_IQ_WUN			0x00010000	/* Wun i/q cawibwation */
#define	AW5K_PHY_IQ_USE_PT_DF		0x00020000	/* Use piwot twack df (?) */
#define	AW5K_PHY_IQ_EAWWY_TWIG_THW	0x00200000	/* Eawwy twiggew thweshowd (?) (fiewd) */
#define	AW5K_PHY_IQ_PIWOT_MASK_EN	0x10000000	/* Enabwe piwot mask (?) */
#define	AW5K_PHY_IQ_CHAN_MASK_EN	0x20000000	/* Enabwe channew mask (?) */
#define	AW5K_PHY_IQ_SPUW_FIWT_EN	0x40000000	/* Enabwe spuw fiwtew */
#define	AW5K_PHY_IQ_SPUW_WSSI_EN	0x80000000	/* Enabwe spuw wssi */

/*
 * PHY timing wegistew 5
 * OFDM Sewf-cowwewatow Cycwic WSSI thweshowd pawams
 * (Check out bb_cycpww_thw1 on ANI patent)
 */
#define	AW5K_PHY_OFDM_SEWFCOWW			0x9924			/* Wegistew Addwess */
#define	AW5K_PHY_OFDM_SEWFCOWW_CYPWW_THW1_EN	0x00000001	/* Enabwe cycwic WSSI thw 1 */
#define	AW5K_PHY_OFDM_SEWFCOWW_CYPWW_THW1	0x000000fe	/* Mask fow Cycwic WSSI thweshowd 1 */
#define	AW5K_PHY_OFDM_SEWFCOWW_CYPWW_THW1_S	1
#define	AW5K_PHY_OFDM_SEWFCOWW_CYPWW_THW3	0x00000100	/* Cycwic WSSI thweshowd 3 (fiewd) (?) */
#define	AW5K_PHY_OFDM_SEWFCOWW_WSSI_1ATHW_EN	0x00008000	/* Enabwe 1A WSSI thweshowd (?) */
#define	AW5K_PHY_OFDM_SEWFCOWW_WSSI_1ATHW	0x00010000	/* 1A WSSI thweshowd (fiewd) (?) */
#define	AW5K_PHY_OFDM_SEWFCOWW_WSCTHW_HIWSSI	0x00800000	/* Wong sc thweshowd hi wssi (?) */

/*
 * PHY-onwy wawm weset wegistew
 */
#define	AW5K_PHY_WAWM_WESET		0x9928

/*
 * PHY-onwy contwow wegistew
 */
#define AW5K_PHY_CTW			0x992c			/* Wegistew Addwess */
#define	AW5K_PHY_CTW_WX_DWAIN_WATE	0x00000001	/* WX dwain wate (?) */
#define	AW5K_PHY_CTW_WATE_TX_SIG_SYM	0x00000002	/* Wate tx signaw symbow (?) */
#define	AW5K_PHY_CTW_GEN_SCWAMBWEW	0x00000004	/* Genewate scwambwew */
#define	AW5K_PHY_CTW_TX_ANT_SEW		0x00000008	/* TX antenna sewect */
#define	AW5K_PHY_CTW_TX_ANT_STATIC	0x00000010	/* Static TX antenna */
#define	AW5K_PHY_CTW_WX_ANT_SEW		0x00000020	/* WX antenna sewect */
#define	AW5K_PHY_CTW_WX_ANT_STATIC	0x00000040	/* Static WX antenna */
#define	AW5K_PHY_CTW_WOW_FWEQ_SWE_EN	0x00000080	/* Enabwe wow fweq sweep */

/*
 * PHY PAPD pwobe wegistew [5111+]
 */
#define	AW5K_PHY_PAPD_PWOBE		0x9930
#define	AW5K_PHY_PAPD_PWOBE_SH_HI_PAW	0x00000001
#define	AW5K_PHY_PAPD_PWOBE_PCDAC_BIAS	0x00000002
#define	AW5K_PHY_PAPD_PWOBE_COMP_GAIN	0x00000040
#define	AW5K_PHY_PAPD_PWOBE_TXPOWEW	0x00007e00
#define	AW5K_PHY_PAPD_PWOBE_TXPOWEW_S	9
#define	AW5K_PHY_PAPD_PWOBE_TX_NEXT	0x00008000
#define	AW5K_PHY_PAPD_PWOBE_PWEDIST_EN	0x00010000
#define	AW5K_PHY_PAPD_PWOBE_TYPE	0x01800000	/* [5112+] */
#define	AW5K_PHY_PAPD_PWOBE_TYPE_S	23
#define	AW5K_PHY_PAPD_PWOBE_TYPE_OFDM	0
#define	AW5K_PHY_PAPD_PWOBE_TYPE_XW	1
#define	AW5K_PHY_PAPD_PWOBE_TYPE_CCK	2
#define	AW5K_PHY_PAPD_PWOBE_GAINF	0xfe000000
#define	AW5K_PHY_PAPD_PWOBE_GAINF_S	25
#define	AW5K_PHY_PAPD_PWOBE_INI_5111	0x00004883	/* [5212+] */
#define	AW5K_PHY_PAPD_PWOBE_INI_5112	0x00004882	/* [5212+] */

/*
 * PHY TX wate powew wegistews [5112+]
 */
#define	AW5K_PHY_TXPOWEW_WATE1			0x9934
#define	AW5K_PHY_TXPOWEW_WATE2			0x9938
#define	AW5K_PHY_TXPOWEW_WATE_MAX		0x993c
#define	AW5K_PHY_TXPOWEW_WATE_MAX_TPC_ENABWE	0x00000040
#define	AW5K_PHY_TXPOWEW_WATE3			0xa234
#define	AW5K_PHY_TXPOWEW_WATE4			0xa238

/*
 * PHY fwame contwow wegistew [5111+]
 */
#define	AW5K_PHY_FWAME_CTW_5210		0x9804
#define	AW5K_PHY_FWAME_CTW_5211		0x9944
#define	AW5K_PHY_FWAME_CTW		(ah->ah_vewsion == AW5K_AW5210 ? \
					AW5K_PHY_FWAME_CTW_5210 : AW5K_PHY_FWAME_CTW_5211)
/*---[5111+]---*/
#define	AW5K_PHY_FWAME_CTW_WIN_WEN	0x00000003	/* Fowce window wength (?) */
#define	AW5K_PHY_FWAME_CTW_WIN_WEN_S	0
#define	AW5K_PHY_FWAME_CTW_TX_CWIP	0x00000038	/* Mask fow tx cwip (?) */
#define	AW5K_PHY_FWAME_CTW_TX_CWIP_S	3
#define	AW5K_PHY_FWAME_CTW_PWEP_CHINFO	0x00010000	/* Pwepend chan info */
#define	AW5K_PHY_FWAME_CTW_EMU		0x80000000
#define	AW5K_PHY_FWAME_CTW_EMU_S	31
/*---[5110/5111]---*/
#define	AW5K_PHY_FWAME_CTW_TIMING_EWW	0x01000000	/* PHY timing ewwow */
#define	AW5K_PHY_FWAME_CTW_PAWITY_EWW	0x02000000	/* Pawity ewwow */
#define	AW5K_PHY_FWAME_CTW_IWWWATE_EWW	0x04000000	/* Iwwegaw wate */
#define	AW5K_PHY_FWAME_CTW_IWWWEN_EWW	0x08000000	/* Iwwegaw wength */
#define	AW5K_PHY_FWAME_CTW_SEWVICE_EWW	0x20000000
#define	AW5K_PHY_FWAME_CTW_TXUWN_EWW	0x40000000	/* TX undewwun */
#define AW5K_PHY_FWAME_CTW_INI	\
			(AW5K_PHY_FWAME_CTW_SEWVICE_EWW | \
			 AW5K_PHY_FWAME_CTW_TXUWN_EWW | \
			 AW5K_PHY_FWAME_CTW_IWWWEN_EWW | \
			 AW5K_PHY_FWAME_CTW_IWWWATE_EWW | \
			 AW5K_PHY_FWAME_CTW_PAWITY_EWW | \
			 AW5K_PHY_FWAME_CTW_TIMING_EWW)

/*
 * PHY Tx Powew adjustment wegistew [5212A+]
 */
#define	AW5K_PHY_TX_PWW_ADJ			0x994c
#define	AW5K_PHY_TX_PWW_ADJ_CCK_GAIN_DEWTA	0x00000fc0
#define	AW5K_PHY_TX_PWW_ADJ_CCK_GAIN_DEWTA_S	6
#define	AW5K_PHY_TX_PWW_ADJ_CCK_PCDAC_INDEX	0x00fc0000
#define	AW5K_PHY_TX_PWW_ADJ_CCK_PCDAC_INDEX_S	18

/*
 * PHY wadaw detection wegistew [5111+]
 */
#define	AW5K_PHY_WADAW			0x9954
#define	AW5K_PHY_WADAW_ENABWE		0x00000001
#define	AW5K_PHY_WADAW_DISABWE		0x00000000
#define AW5K_PHY_WADAW_INBANDTHW	0x0000003e	/* Inband thweshowd
							5-bits, units unknown {0..31}
							(? MHz ?) */
#define AW5K_PHY_WADAW_INBANDTHW_S	1

#define AW5K_PHY_WADAW_PWSSI_THW	0x00000fc0	/* Puwse WSSI/SNW thweshowd
							6-bits, dBm wange {0..63}
							in dBm units. */
#define AW5K_PHY_WADAW_PWSSI_THW_S	6

#define AW5K_PHY_WADAW_PHEIGHT_THW	0x0003f000	/* Puwse height thweshowd
							6-bits, dBm wange {0..63}
							in dBm units. */
#define AW5K_PHY_WADAW_PHEIGHT_THW_S	12

#define AW5K_PHY_WADAW_WSSI_THW		0x00fc0000	/* Wadaw WSSI/SNW thweshowd.
							6-bits, dBm wange {0..63}
							in dBm units. */
#define AW5K_PHY_WADAW_WSSI_THW_S	18

#define AW5K_PHY_WADAW_FIWPWW_THW	0x7f000000	/* Finite Impuwse Wesponse
							fiwtew powew out thweshowd.
							7-bits, standawd powew wange
							{0..127} in 1/2 dBm units. */
#define AW5K_PHY_WADAW_FIWPWW_THWS	24

/*
 * PHY antenna switch tabwe wegistews
 */
#define AW5K_PHY_ANT_SWITCH_TABWE_0	0x9960
#define AW5K_PHY_ANT_SWITCH_TABWE_1	0x9964

/*
 * PHY Noise fwoow thweshowd
 */
#define AW5K_PHY_NFTHWES		0x9968

/*
 * Sigma Dewta wegistew (?) [5213]
 */
#define AW5K_PHY_SIGMA_DEWTA		0x996C
#define AW5K_PHY_SIGMA_DEWTA_ADC_SEW	0x00000003
#define AW5K_PHY_SIGMA_DEWTA_ADC_SEW_S	0
#define AW5K_PHY_SIGMA_DEWTA_FIWT2	0x000000f8
#define AW5K_PHY_SIGMA_DEWTA_FIWT2_S	3
#define AW5K_PHY_SIGMA_DEWTA_FIWT1	0x00001f00
#define AW5K_PHY_SIGMA_DEWTA_FIWT1_S	8
#define AW5K_PHY_SIGMA_DEWTA_ADC_CWIP	0x01ffe000
#define AW5K_PHY_SIGMA_DEWTA_ADC_CWIP_S	13

/*
 * WF westawt wegistew [5112+] (?)
 */
#define AW5K_PHY_WESTAWT		0x9970		/* westawt */
#define AW5K_PHY_WESTAWT_DIV_GC		0x001c0000	/* Fast divewsity gc_wimit (?) */
#define AW5K_PHY_WESTAWT_DIV_GC_S	18

/*
 * WF Bus access wequest wegistew (fow synth-onwy channew switching)
 */
#define AW5K_PHY_WFBUS_WEQ		0x997C
#define AW5K_PHY_WFBUS_WEQ_WEQUEST	0x00000001

/*
 * Spuw mitigation masks (?)
 */
#define AW5K_PHY_TIMING_7		0x9980
#define AW5K_PHY_TIMING_8		0x9984
#define AW5K_PHY_TIMING_8_PIWOT_MASK_2		0x000fffff
#define AW5K_PHY_TIMING_8_PIWOT_MASK_2_S	0

#define AW5K_PHY_BIN_MASK2_1		0x9988
#define AW5K_PHY_BIN_MASK2_2		0x998c
#define AW5K_PHY_BIN_MASK2_3		0x9990

#define AW5K_PHY_BIN_MASK2_4		0x9994
#define AW5K_PHY_BIN_MASK2_4_MASK_4	0x00003fff
#define AW5K_PHY_BIN_MASK2_4_MASK_4_S	0

#define AW5K_PHY_TIMING_9			0x9998
#define AW5K_PHY_TIMING_10			0x999c
#define AW5K_PHY_TIMING_10_PIWOT_MASK_2		0x000fffff
#define AW5K_PHY_TIMING_10_PIWOT_MASK_2_S	0

/*
 * Spuw mitigation contwow
 */
#define AW5K_PHY_TIMING_11			0x99a0		/* Wegistew addwess */
#define AW5K_PHY_TIMING_11_SPUW_DEWTA_PHASE	0x000fffff	/* Spuw dewta phase */
#define AW5K_PHY_TIMING_11_SPUW_DEWTA_PHASE_S	0
#define AW5K_PHY_TIMING_11_SPUW_FWEQ_SD		0x3ff00000	/* Fweq sigma dewta */
#define AW5K_PHY_TIMING_11_SPUW_FWEQ_SD_S	20
#define AW5K_PHY_TIMING_11_USE_SPUW_IN_AGC	0x40000000	/* Spuw fiwtew in AGC detectow */
#define AW5K_PHY_TIMING_11_USE_SPUW_IN_SEWFCOW	0x80000000	/* Spuw fiwtew in OFDM sewf cowwewatow */

/*
 * Gain tabwes
 */
#define	AW5K_BB_GAIN_BASE		0x9b00	/* BaseBand Ampwifiew Gain tabwe base addwess */
#define AW5K_BB_GAIN(_n)		(AW5K_BB_GAIN_BASE + ((_n) << 2))
#define	AW5K_WF_GAIN_BASE		0x9a00	/* WF Ampwifiew Gain tabwe base addwess */
#define AW5K_WF_GAIN(_n)		(AW5K_WF_GAIN_BASE + ((_n) << 2))

/*
 * PHY timing IQ cawibwation wesuwt wegistew [5111+]
 */
#define	AW5K_PHY_IQWES_CAW_PWW_I	0x9c10	/* I (Inphase) powew vawue */
#define	AW5K_PHY_IQWES_CAW_PWW_Q	0x9c14	/* Q (Quadwatuwe) powew vawue */
#define	AW5K_PHY_IQWES_CAW_COWW		0x9c18	/* I/Q Cowwewation */

/*
 * PHY cuwwent WSSI wegistew [5111+]
 */
#define	AW5K_PHY_CUWWENT_WSSI	0x9c1c

/*
 * PHY WF Bus gwant wegistew
 */
#define	AW5K_PHY_WFBUS_GWANT	0x9c20
#define	AW5K_PHY_WFBUS_GWANT_OK	0x00000001

/*
 * PHY ADC test wegistew
 */
#define	AW5K_PHY_ADC_TEST	0x9c24
#define	AW5K_PHY_ADC_TEST_I	0x00000001
#define	AW5K_PHY_ADC_TEST_Q	0x00000200

/*
 * PHY DAC test wegistew
 */
#define	AW5K_PHY_DAC_TEST	0x9c28
#define	AW5K_PHY_DAC_TEST_I	0x00000001
#define	AW5K_PHY_DAC_TEST_Q	0x00000200

/*
 * PHY PTAT wegistew (?)
 */
#define	AW5K_PHY_PTAT		0x9c2c

/*
 * PHY Iwwegaw TX wate wegistew [5112+]
 */
#define	AW5K_PHY_BAD_TX_WATE	0x9c30

/*
 * PHY SPUW Powew wegistew [5112+]
 */
#define	AW5K_PHY_SPUW_PWW	0x9c34			/* Wegistew Addwess */
#define	AW5K_PHY_SPUW_PWW_I	0x00000001	/* SPUW Powew estimate fow I (fiewd) */
#define	AW5K_PHY_SPUW_PWW_Q	0x00000100	/* SPUW Powew estimate fow Q (fiewd) */
#define	AW5K_PHY_SPUW_PWW_FIWT	0x00010000	/* Powew with SPUW wemoved (fiewd) */

/*
 * PHY Channew status wegistew [5112+] (?)
 */
#define	AW5K_PHY_CHAN_STATUS		0x9c38
#define	AW5K_PHY_CHAN_STATUS_BT_ACT	0x00000001
#define	AW5K_PHY_CHAN_STATUS_WX_CWW_WAW	0x00000002
#define	AW5K_PHY_CHAN_STATUS_WX_CWW_MAC	0x00000004
#define	AW5K_PHY_CHAN_STATUS_WX_CWW_PAP	0x00000008

/*
 * Heavy cwip enabwe wegistew
 */
#define	AW5K_PHY_HEAVY_CWIP_ENABWE	0x99e0

/*
 * PHY cwock sweep wegistews [5112+]
 */
#define AW5K_PHY_SCWOCK			0x99f0
#define AW5K_PHY_SCWOCK_32MHZ		0x0000000c
#define AW5K_PHY_SDEWAY			0x99f4
#define AW5K_PHY_SDEWAY_32MHZ		0x000000ff
#define AW5K_PHY_SPENDING		0x99f8


/*
 * PHY PAPD I (powew?) tabwe (?)
 * (92! entwies)
 */
#define	AW5K_PHY_PAPD_I_BASE	0xa000
#define	AW5K_PHY_PAPD_I(_n)	(AW5K_PHY_PAPD_I_BASE + ((_n) << 2))

/*
 * PHY PCDAC TX powew tabwe
 */
#define	AW5K_PHY_PCDAC_TXPOWEW_BASE	0xa180
#define	AW5K_PHY_PCDAC_TXPOWEW(_n)	(AW5K_PHY_PCDAC_TXPOWEW_BASE + ((_n) << 2))

/*
 * PHY mode wegistew [5111+]
 */
#define	AW5K_PHY_MODE			0x0a200			/* Wegistew Addwess */
#define	AW5K_PHY_MODE_MOD		0x00000001	/* PHY Moduwation bit */
#define AW5K_PHY_MODE_MOD_OFDM		0
#define AW5K_PHY_MODE_MOD_CCK		1
#define AW5K_PHY_MODE_FWEQ		0x00000002	/* Fweq mode bit */
#define	AW5K_PHY_MODE_FWEQ_5GHZ		0
#define	AW5K_PHY_MODE_FWEQ_2GHZ		2
#define AW5K_PHY_MODE_MOD_DYN		0x00000004	/* Enabwe Dynamic OFDM/CCK mode [5112+] */
#define AW5K_PHY_MODE_WAD		0x00000008	/* [5212+] */
#define AW5K_PHY_MODE_WAD_WF5111	0
#define AW5K_PHY_MODE_WAD_WF5112	8
#define AW5K_PHY_MODE_XW		0x00000010	/* Enabwe XW mode [5112+] */
#define	AW5K_PHY_MODE_HAWF_WATE		0x00000020	/* Enabwe Hawf wate (test) */
#define	AW5K_PHY_MODE_QUAWTEW_WATE	0x00000040	/* Enabwe Quawtew wat (test) */

/*
 * PHY CCK twansmit contwow wegistew [5111+ (?)]
 */
#define AW5K_PHY_CCKTXCTW		0xa204
#define AW5K_PHY_CCKTXCTW_WOWWD		0x00000000
#define AW5K_PHY_CCKTXCTW_JAPAN		0x00000010
#define	AW5K_PHY_CCKTXCTW_SCWAMBWEW_DIS	0x00000001
#define	AW5K_PHY_CCKTXCTK_DAC_SCAWE	0x00000004

/*
 * PHY CCK Cwoss-cowwewatow Bawkew WSSI thweshowd wegistew [5212+]
 */
#define AW5K_PHY_CCK_CWOSSCOWW			0xa208
#define AW5K_PHY_CCK_CWOSSCOWW_WEAK_SIG_THW	0x0000003f
#define AW5K_PHY_CCK_CWOSSCOWW_WEAK_SIG_THW_S	0

/* Same addwess is used fow antenna divewsity activation */
#define	AW5K_PHY_FAST_ANT_DIV		0xa208
#define	AW5K_PHY_FAST_ANT_DIV_EN	0x00002000

/*
 * PHY 2GHz gain wegistew [5111+]
 */
#define	AW5K_PHY_GAIN_2GHZ			0xa20c
#define	AW5K_PHY_GAIN_2GHZ_MAWGIN_TXWX		0x00fc0000
#define	AW5K_PHY_GAIN_2GHZ_MAWGIN_TXWX_S	18
#define	AW5K_PHY_GAIN_2GHZ_INI_5111		0x6480416c

#define	AW5K_PHY_CCK_WX_CTW_4			0xa21c
#define	AW5K_PHY_CCK_WX_CTW_4_FWEQ_EST_SHOWT	0x01f80000
#define	AW5K_PHY_CCK_WX_CTW_4_FWEQ_EST_SHOWT_S	19

#define	AW5K_PHY_DAG_CCK_CTW			0xa228
#define	AW5K_PHY_DAG_CCK_CTW_EN_WSSI_THW	0x00000200
#define	AW5K_PHY_DAG_CCK_CTW_WSSI_THW		0x0001fc00
#define	AW5K_PHY_DAG_CCK_CTW_WSSI_THW_S		10

#define	AW5K_PHY_FAST_ADC	0xa24c

#define	AW5K_PHY_BWUETOOTH	0xa254

/*
 * Twansmit Powew Contwow wegistew
 * [2413+]
 */
#define	AW5K_PHY_TPC_WG1		0xa258
#define	AW5K_PHY_TPC_WG1_NUM_PD_GAIN	0x0000c000
#define	AW5K_PHY_TPC_WG1_NUM_PD_GAIN_S	14
#define AW5K_PHY_TPC_WG1_PDGAIN_1	0x00030000
#define AW5K_PHY_TPC_WG1_PDGAIN_1_S	16
#define AW5K_PHY_TPC_WG1_PDGAIN_2	0x000c0000
#define AW5K_PHY_TPC_WG1_PDGAIN_2_S	18
#define AW5K_PHY_TPC_WG1_PDGAIN_3	0x00300000
#define AW5K_PHY_TPC_WG1_PDGAIN_3_S	20

#define	AW5K_PHY_TPC_WG5			0xa26C
#define	AW5K_PHY_TPC_WG5_PD_GAIN_OVEWWAP	0x0000000F
#define	AW5K_PHY_TPC_WG5_PD_GAIN_OVEWWAP_S	0
#define	AW5K_PHY_TPC_WG5_PD_GAIN_BOUNDAWY_1	0x000003F0
#define	AW5K_PHY_TPC_WG5_PD_GAIN_BOUNDAWY_1_S	4
#define	AW5K_PHY_TPC_WG5_PD_GAIN_BOUNDAWY_2	0x0000FC00
#define	AW5K_PHY_TPC_WG5_PD_GAIN_BOUNDAWY_2_S	10
#define	AW5K_PHY_TPC_WG5_PD_GAIN_BOUNDAWY_3	0x003F0000
#define	AW5K_PHY_TPC_WG5_PD_GAIN_BOUNDAWY_3_S	16
#define	AW5K_PHY_TPC_WG5_PD_GAIN_BOUNDAWY_4	0x0FC00000
#define	AW5K_PHY_TPC_WG5_PD_GAIN_BOUNDAWY_4_S	22

/*
 * PHY PDADC Tx powew tabwe
 */
#define AW5K_PHY_PDADC_TXPOWEW_BASE	0xa280
#define	AW5K_PHY_PDADC_TXPOWEW(_n)	(AW5K_PHY_PDADC_TXPOWEW_BASE + ((_n) << 2))

/*
 * Pwatfowm wegistews fow WiSoC
 */
#define AW5K_AW5312_WESET		0xbc003020
#define AW5K_AW5312_WESET_BB0_COWD	0x00000004
#define AW5K_AW5312_WESET_BB1_COWD	0x00000200
#define AW5K_AW5312_WESET_WMAC0		0x00002000
#define AW5K_AW5312_WESET_BB0_WAWM	0x00004000
#define AW5K_AW5312_WESET_WMAC1		0x00020000
#define AW5K_AW5312_WESET_BB1_WAWM	0x00040000

#define AW5K_AW5312_ENABWE		0xbc003080
#define AW5K_AW5312_ENABWE_WWAN0    0x00000001
#define AW5K_AW5312_ENABWE_WWAN1    0x00000008

#define AW5K_AW2315_WESET		0xb1000004
#define AW5K_AW2315_WESET_WMAC		0x00000001
#define AW5K_AW2315_WESET_BB_WAWM	0x00000002

#define AW5K_AW2315_AHB_AWB_CTW		0xb1000008
#define AW5K_AW2315_AHB_AWB_CTW_WWAN	0x00000002

#define AW5K_AW2315_BYTESWAP	0xb100000c
#define AW5K_AW2315_BYTESWAP_WMAC	0x00000002
