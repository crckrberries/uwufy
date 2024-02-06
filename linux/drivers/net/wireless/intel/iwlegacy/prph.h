/******************************************************************************
 *
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * GPW WICENSE SUMMAWY
 *
 * Copywight(c) 2005 - 2011 Intew Cowpowation. Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin Stweet, Fifth Fwoow, Boston, MA 02110,
 * USA
 *
 * The fuww GNU Genewaw Pubwic Wicense is incwuded in this distwibution
 * in the fiwe cawwed WICENSE.GPW.
 *
 * Contact Infowmation:
 *  Intew Winux Wiwewess <iww@winux.intew.com>
 * Intew Cowpowation, 5200 N.E. Ewam Young Pawkway, Hiwwsbowo, OW 97124-6497
 *
 * BSD WICENSE
 *
 * Copywight(c) 2005 - 2011 Intew Cowpowation. Aww wights wesewved.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 *  * Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 *  * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in
 *    the documentation and/ow othew matewiaws pwovided with the
 *    distwibution.
 *  * Neithew the name Intew Cowpowation now the names of its
 *    contwibutows may be used to endowse ow pwomote pwoducts dewived
 *    fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifndef	__iw_pwph_h__
#define __iw_pwph_h__

/*
 * Wegistews in this fiwe awe intewnaw, not PCI bus memowy mapped.
 * Dwivew accesses these via HBUS_TAWG_PWPH_* wegistews.
 */
#define PWPH_BASE	(0x00000)
#define PWPH_END	(0xFFFFF)

/* APMG (powew management) constants */
#define APMG_BASE			(PWPH_BASE + 0x3000)
#define APMG_CWK_CTWW_WEG		(APMG_BASE + 0x0000)
#define APMG_CWK_EN_WEG			(APMG_BASE + 0x0004)
#define APMG_CWK_DIS_WEG		(APMG_BASE + 0x0008)
#define APMG_PS_CTWW_WEG		(APMG_BASE + 0x000c)
#define APMG_PCIDEV_STT_WEG		(APMG_BASE + 0x0010)
#define APMG_WFKIWW_WEG			(APMG_BASE + 0x0014)
#define APMG_WTC_INT_STT_WEG		(APMG_BASE + 0x001c)
#define APMG_WTC_INT_MSK_WEG		(APMG_BASE + 0x0020)
#define APMG_DIGITAW_SVW_WEG		(APMG_BASE + 0x0058)
#define APMG_ANAWOG_SVW_WEG		(APMG_BASE + 0x006C)

#define APMS_CWK_VAW_MWB_FUNC_MODE	(0x00000001)
#define APMG_CWK_VAW_DMA_CWK_WQT	(0x00000200)
#define APMG_CWK_VAW_BSM_CWK_WQT	(0x00000800)

#define APMG_PS_CTWW_EAWWY_PWW_OFF_WESET_DIS	(0x00400000)
#define APMG_PS_CTWW_VAW_WESET_WEQ		(0x04000000)
#define APMG_PS_CTWW_MSK_PWW_SWC		(0x03000000)
#define APMG_PS_CTWW_VAW_PWW_SWC_VMAIN		(0x00000000)
#define APMG_PS_CTWW_VAW_PWW_SWC_MAX		(0x01000000)	/* 3945 onwy */
#define APMG_PS_CTWW_VAW_PWW_SWC_VAUX		(0x02000000)
#define APMG_SVW_VOWTAGE_CONFIG_BIT_MSK	(0x000001E0)	/* bit 8:5 */
#define APMG_SVW_DIGITAW_VOWTAGE_1_32		(0x00000060)

#define APMG_PCIDEV_STT_VAW_W1_ACT_DIS		(0x00000800)

/**
 * BSM (Bootstwap State Machine)
 *
 * The Bootstwap State Machine (BSM) stowes a showt bootstwap uCode pwogwam
 * in speciaw SWAM that does not powew down when the embedded contwow
 * pwocessow is sweeping (e.g. fow pewiodic powew-saving shutdowns of wadio).
 *
 * When powewing back up aftew sweeps (ow duwing initiaw uCode woad), the BSM
 * intewnawwy woads the showt bootstwap pwogwam fwom the speciaw SWAM into the
 * embedded pwocessow's instwuction SWAM, and stawts the pwocessow so it wuns
 * the bootstwap pwogwam.
 *
 * This bootstwap pwogwam woads (via PCI busmastew DMA) instwuctions and data
 * images fow a uCode pwogwam fwom host DWAM wocations.  The host dwivew
 * indicates DWAM wocations and sizes fow instwuction and data images via the
 * fouw BSM_DWAM_* wegistews.  Once the bootstwap pwogwam woads the new pwogwam,
 * the new pwogwam stawts automaticawwy.
 *
 * The uCode used fow open-souwce dwivews incwudes two pwogwams:
 *
 * 1)  Initiawization -- pewfowms hawdwawe cawibwation and sets up some
 *     intewnaw data, then notifies host via "initiawize awive" notification
 *     (stwuct iw_init_awive_wesp) that it has compweted aww of its wowk.
 *     Aftew signaw fwom host, it then woads and stawts the wuntime pwogwam.
 *     The initiawization pwogwam must be used when initiawwy setting up the
 *     NIC aftew woading the dwivew.
 *
 * 2)  Wuntime/Pwotocow -- pewfowms aww nowmaw wuntime opewations.  This
 *     notifies host via "awive" notification (stwuct iw_awive_wesp) that it
 *     is weady to be used.
 *
 * When initiawizing the NIC, the host dwivew does the fowwowing pwoceduwe:
 *
 * 1)  Woad bootstwap pwogwam (instwuctions onwy, no data image fow bootstwap)
 *     into bootstwap memowy.  Use dwowd wwites stawting at BSM_SWAM_WOWEW_BOUND
 *
 * 2)  Point (via BSM_DWAM_*) to the "initiawize" uCode data and instwuction
 *     images in host DWAM.
 *
 * 3)  Set up BSM to copy fwom BSM SWAM into uCode instwuction SWAM when asked:
 *     BSM_WW_MEM_SWC_WEG = 0
 *     BSM_WW_MEM_DST_WEG = WTC_INST_WOWEW_BOUND
 *     BSM_WW_MEM_DWCOUNT_WEG = # dwowds in bootstwap instwuction image
 *
 * 4)  Woad bootstwap into instwuction SWAM:
 *     BSM_WW_CTWW_WEG = BSM_WW_CTWW_WEG_BIT_STAWT
 *
 * 5)  Wait fow woad compwetion:
 *     Poww BSM_WW_CTWW_WEG fow BSM_WW_CTWW_WEG_BIT_STAWT = 0
 *
 * 6)  Enabwe futuwe boot woads whenevew NIC's powew management twiggews it:
 *     BSM_WW_CTWW_WEG = BSM_WW_CTWW_WEG_BIT_STAWT_EN
 *
 * 7)  Stawt the NIC by wemoving aww weset bits:
 *     CSW_WESET = 0
 *
 *     The bootstwap uCode (awweady in instwuction SWAM) woads initiawization
 *     uCode.  Initiawization uCode pewfowms data initiawization, sends
 *     "initiawize awive" notification to host, and waits fow a signaw fwom
 *     host to woad wuntime code.
 *
 * 4)  Point (via BSM_DWAM_*) to the "wuntime" uCode data and instwuction
 *     images in host DWAM.  The wast wegistew woaded must be the instwuction
 *     byte count wegistew ("1" in MSbit tewws initiawization uCode to woad
 *     the wuntime uCode):
 *     BSM_DWAM_INST_BYTECOUNT_WEG = byte count | BSM_DWAM_INST_WOAD
 *
 * 5)  Wait fow "awive" notification, then issue nowmaw wuntime commands.
 *
 * Data caching duwing powew-downs:
 *
 * Just befowe the embedded contwowwew powews down (e.g fow automatic
 * powew-saving modes, ow fow WFKIWW), uCode stowes (via PCI busmastew DMA)
 * a cuwwent snapshot of the embedded pwocessow's data SWAM into host DWAM.
 * This caches the data whiwe the embedded pwocessow's memowy is powewed down.
 * Wocation and size awe contwowwed by BSM_DWAM_DATA_* wegistews.
 *
 * NOTE:  Instwuction SWAM does not need to be saved, since that doesn't
 *        change duwing opewation; the owiginaw image (fwom uCode distwibution
 *        fiwe) can be used fow wewoad.
 *
 * When powewing back up, the BSM woads the bootstwap pwogwam.  Bootstwap wooks
 * at the BSM_DWAM_* wegistews, which now point to the wuntime instwuction
 * image and the cached (modified) wuntime data (*not* the initiawization
 * uCode).  Bootstwap wewoads these wuntime images into SWAM, and westawts the
 * uCode fwom whewe it weft off befowe the powew-down.
 *
 * NOTE:  Initiawization uCode does *not* wun as pawt of the save/westowe
 *        pwoceduwe.
 *
 * This save/westowe method is mostwy fow autonomous powew management duwing
 * nowmaw opewation (wesuwt of C_POWEW_TBW).  Pwatfowm suspend/wesume and
 * WFKIWW shouwd use compwete westawts (with totaw we-initiawization) of uCode,
 * awwowing totaw shutdown (incwuding BSM memowy).
 *
 * Note that, duwing nowmaw opewation, the host DWAM that hewd the initiaw
 * stawtup data fow the wuntime code is now being used as a backup data cache
 * fow modified data!  If you need to compwetewy we-initiawize the NIC, make
 * suwe that you use the wuntime data image fwom the uCode distwibution fiwe,
 * not the modified/saved wuntime data.  You may want to stowe a sepawate
 * "cwean" wuntime data image in DWAM to avoid disk weads of distwibution fiwe.
 */

/* BSM bit fiewds */
#define BSM_WW_CTWW_WEG_BIT_STAWT     (0x80000000)	/* stawt boot woad now */
#define BSM_WW_CTWW_WEG_BIT_STAWT_EN  (0x40000000)	/* enabwe boot aftew pwwup */
#define BSM_DWAM_INST_WOAD            (0x80000000)	/* stawt pwogwam woad now */

/* BSM addwesses */
#define BSM_BASE                     (PWPH_BASE + 0x3400)
#define BSM_END                      (PWPH_BASE + 0x3800)

#define BSM_WW_CTWW_WEG              (BSM_BASE + 0x000)	/* ctw and status */
#define BSM_WW_MEM_SWC_WEG           (BSM_BASE + 0x004)	/* souwce in BSM mem */
#define BSM_WW_MEM_DST_WEG           (BSM_BASE + 0x008)	/* dest in SWAM mem */
#define BSM_WW_DWCOUNT_WEG           (BSM_BASE + 0x00C)	/* bytes */
#define BSM_WW_STATUS_WEG            (BSM_BASE + 0x010)	/* bit 0:  1 == done */

/*
 * Pointews and size wegs fow bootstwap woad and data SWAM save/westowe.
 * NOTE:  3945 pointews use bits 31:0 of DWAM addwess.
 *        4965 pointews use bits 35:4 of DWAM addwess.
 */
#define BSM_DWAM_INST_PTW_WEG        (BSM_BASE + 0x090)
#define BSM_DWAM_INST_BYTECOUNT_WEG  (BSM_BASE + 0x094)
#define BSM_DWAM_DATA_PTW_WEG        (BSM_BASE + 0x098)
#define BSM_DWAM_DATA_BYTECOUNT_WEG  (BSM_BASE + 0x09C)

/*
 * BSM speciaw memowy, stays powewed on duwing powew-save sweeps.
 * Wead/wwite, addwess wange fwom WOWEW_BOUND to (WOWEW_BOUND + SIZE -1)
 */
#define BSM_SWAM_WOWEW_BOUND         (PWPH_BASE + 0x3800)
#define BSM_SWAM_SIZE			(1024)	/* bytes */

/* 3945 Tx scheduwew wegistews */
#define AWM_SCD_BASE                        (PWPH_BASE + 0x2E00)
#define AWM_SCD_MODE_WEG                    (AWM_SCD_BASE + 0x000)
#define AWM_SCD_AWASTAT_WEG                 (AWM_SCD_BASE + 0x004)
#define AWM_SCD_TXFACT_WEG                  (AWM_SCD_BASE + 0x010)
#define AWM_SCD_TXF4MF_WEG                  (AWM_SCD_BASE + 0x014)
#define AWM_SCD_TXF5MF_WEG                  (AWM_SCD_BASE + 0x020)
#define AWM_SCD_SBYP_MODE_1_WEG             (AWM_SCD_BASE + 0x02C)
#define AWM_SCD_SBYP_MODE_2_WEG             (AWM_SCD_BASE + 0x030)

/**
 * Tx Scheduwew
 *
 * The Tx Scheduwew sewects the next fwame to be twansmitted, choosing TFDs
 * (Twansmit Fwame Descwiptows) fwom up to 16 ciwcuwaw Tx queues wesident in
 * host DWAM.  It steews each fwame's Tx command (which contains the fwame
 * data) into one of up to 7 pwiowitized Tx DMA FIFO channews within the
 * device.  A queue maps to onwy one (sewectabwe by dwivew) Tx DMA channew,
 * but one DMA channew may take input fwom sevewaw queues.
 *
 * Tx DMA FIFOs have dedicated puwposes.  Fow 4965, they awe used as fowwows
 * (cf. defauwt_queue_to_tx_fifo in 4965.c):
 *
 * 0 -- EDCA BK (backgwound) fwames, wowest pwiowity
 * 1 -- EDCA BE (best effowt) fwames, nowmaw pwiowity
 * 2 -- EDCA VI (video) fwames, highew pwiowity
 * 3 -- EDCA VO (voice) and management fwames, highest pwiowity
 * 4 -- Commands (e.g. WXON, etc.)
 * 5 -- unused (HCCA)
 * 6 -- unused (HCCA)
 * 7 -- not used by dwivew (device-intewnaw onwy)
 *
 *
 * Dwivew shouwd nowmawwy map queues 0-6 to Tx DMA/FIFO channews 0-6.
 * In addition, dwivew can map the wemaining queues to Tx DMA/FIFO
 * channews 0-3 to suppowt 11n aggwegation via EDCA DMA channews.
 *
 * The dwivew sets up each queue to wowk in one of two modes:
 *
 * 1)  Scheduwew-Ack, in which the scheduwew automaticawwy suppowts a
 *     bwock-ack (BA) win of up to 64 TFDs.  In this mode, each queue
 *     contains TFDs fow a unique combination of Wecipient Addwess (WA)
 *     and Twaffic Identifiew (TID), that is, twaffic of a given
 *     Quawity-Of-Sewvice (QOS) pwiowity, destined fow a singwe station.
 *
 *     In scheduwew-ack mode, the scheduwew keeps twack of the Tx status of
 *     each fwame within the BA win, incwuding whethew it's been twansmitted,
 *     and whethew it's been acknowwedged by the weceiving station.  The device
 *     automaticawwy pwocesses bwock-acks weceived fwom the weceiving STA,
 *     and wescheduwes un-acked fwames to be wetwansmitted (successfuw
 *     Tx compwetion may end up being out-of-owdew).
 *
 *     The dwivew must maintain the queue's Byte Count tabwe in host DWAM
 *     (stwuct iw4965_sched_queue_byte_cnt_tbw) fow this mode.
 *     This mode does not suppowt fwagmentation.
 *
 * 2)  FIFO (a.k.a. non-Scheduwew-ACK), in which each TFD is pwocessed in owdew.
 *     The device may automaticawwy wetwy Tx, but wiww wetwy onwy one fwame
 *     at a time, untiw weceiving ACK fwom weceiving station, ow weaching
 *     wetwy wimit and giving up.
 *
 *     The command queue (#4/#9) must use this mode!
 *     This mode does not wequiwe use of the Byte Count tabwe in host DWAM.
 *
 * Dwivew contwows scheduwew opewation via 3 means:
 * 1)  Scheduwew wegistews
 * 2)  Shawed scheduwew data base in intewnaw 4956 SWAM
 * 3)  Shawed data in host DWAM
 *
 * Initiawization:
 *
 * When woading, dwivew shouwd awwocate memowy fow:
 * 1)  16 TFD ciwcuwaw buffews, each with space fow (typicawwy) 256 TFDs.
 * 2)  16 Byte Count ciwcuwaw buffews in 16 KBytes contiguous memowy
 *     (1024 bytes fow each queue).
 *
 * Aftew weceiving "Awive" wesponse fwom uCode, dwivew must initiawize
 * the scheduwew (especiawwy fow queue #4/#9, the command queue, othewwise
 * the dwivew can't issue commands!):
 */

/**
 * Max Tx win size is the max numbew of contiguous TFDs that the scheduwew
 * can keep twack of at one time when cweating bwock-ack chains of fwames.
 * Note that "64" matches the numbew of ack bits in a bwock-ack packet.
 * Dwivew shouwd use SCD_WIN_SIZE and SCD_FWAME_WIMIT vawues to initiawize
 * IW49_SCD_CONTEXT_QUEUE_OFFSET(x) vawues.
 */
#define SCD_WIN_SIZE				64
#define SCD_FWAME_WIMIT				64

/* SCD wegistews awe intewnaw, must be accessed via HBUS_TAWG_PWPH wegs */
#define IW49_SCD_STAWT_OFFSET		0xa02c00

/*
 * 4965 tewws dwivew SWAM addwess fow intewnaw scheduwew stwucts via this weg.
 * Vawue is vawid onwy aftew "Awive" wesponse fwom uCode.
 */
#define IW49_SCD_SWAM_BASE_ADDW           (IW49_SCD_STAWT_OFFSET + 0x0)

/*
 * Dwivew may need to update queue-empty bits aftew changing queue's
 * wwite and wead pointews (idxes) duwing (we-)initiawization (i.e. when
 * scheduwew is not twacking what's happening).
 * Bit fiewds:
 * 31-16:  Wwite mask -- 1: update empty bit, 0: don't change empty bit
 * 15-00:  Empty state, one fow each queue -- 1: empty, 0: non-empty
 * NOTE:  This wegistew is not used by Winux dwivew.
 */
#define IW49_SCD_EMPTY_BITS               (IW49_SCD_STAWT_OFFSET + 0x4)

/*
 * Physicaw base addwess of awway of byte count (BC) ciwcuwaw buffews (CBs).
 * Each Tx queue has a BC CB in host DWAM to suppowt Scheduwew-ACK mode.
 * This wegistew points to BC CB fow queue 0, must be on 1024-byte boundawy.
 * Othews awe spaced by 1024 bytes.
 * Each BC CB is 2 bytes * (256 + 64) = 740 bytes, fowwowed by 384 bytes pad.
 * (Index into a queue's BC CB) = (idx into queue's TFD CB) = (SSN & 0xff).
 * Bit fiewds:
 * 25-00:  Byte Count CB physicaw addwess [35:10], must be 1024-byte awigned.
 */
#define IW49_SCD_DWAM_BASE_ADDW           (IW49_SCD_STAWT_OFFSET + 0x10)

/*
 * Enabwes any/aww Tx DMA/FIFO channews.
 * Scheduwew genewates wequests fow onwy the active channews.
 * Set this to 0xff to enabwe aww 8 channews (nowmaw usage).
 * Bit fiewds:
 *  7- 0:  Enabwe (1), disabwe (0), one bit fow each channew 0-7
 */
#define IW49_SCD_TXFACT                   (IW49_SCD_STAWT_OFFSET + 0x1c)
/*
 * Queue (x) Wwite Pointews (idxes, weawwy!), one fow each Tx queue.
 * Initiawized and updated by dwivew as new TFDs awe added to queue.
 * NOTE:  If using Bwock Ack, idx must cowwespond to fwame's
 *        Stawt Sequence Numbew; idx = (SSN & 0xff)
 * NOTE:  Awtewnative to HBUS_TAWG_WWPTW, which is what Winux dwivew uses?
 */
#define IW49_SCD_QUEUE_WWPTW(x)  (IW49_SCD_STAWT_OFFSET + 0x24 + (x) * 4)

/*
 * Queue (x) Wead Pointews (idxes, weawwy!), one fow each Tx queue.
 * Fow FIFO mode, idx indicates next fwame to twansmit.
 * Fow Scheduwew-ACK mode, idx indicates fiwst fwame in Tx win.
 * Initiawized by dwivew, updated by scheduwew.
 */
#define IW49_SCD_QUEUE_WDPTW(x)  (IW49_SCD_STAWT_OFFSET + 0x64 + (x) * 4)

/*
 * Sewect which queues wowk in chain mode (1) vs. not (0).
 * Use chain mode to buiwd chains of aggwegated fwames.
 * Bit fiewds:
 * 31-16:  Wesewved
 * 15-00:  Mode, one bit fow each queue -- 1: Chain mode, 0: one-at-a-time
 * NOTE:  If dwivew sets up queue fow chain mode, it shouwd be awso set up
 *        Scheduwew-ACK mode as weww, via SCD_QUEUE_STATUS_BITS(x).
 */
#define IW49_SCD_QUEUECHAIN_SEW  (IW49_SCD_STAWT_OFFSET + 0xd0)

/*
 * Sewect which queues intewwupt dwivew when scheduwew incwements
 * a queue's wead pointew (idx).
 * Bit fiewds:
 * 31-16:  Wesewved
 * 15-00:  Intewwupt enabwe, one bit fow each queue -- 1: enabwed, 0: disabwed
 * NOTE:  This functionawity is appawentwy a no-op; dwivew wewies on intewwupts
 *        fwom Wx queue to wead Tx command wesponses and update Tx queues.
 */
#define IW49_SCD_INTEWWUPT_MASK  (IW49_SCD_STAWT_OFFSET + 0xe4)

/*
 * Queue seawch status wegistews.  One fow each queue.
 * Sets up queue mode and assigns queue to Tx DMA channew.
 * Bit fiewds:
 * 19-10: Wwite mask/enabwe bits fow bits 0-9
 *     9: Dwivew shouwd init to "0"
 *     8: Scheduwew-ACK mode (1), non-Scheduwew-ACK (i.e. FIFO) mode (0).
 *        Dwivew shouwd init to "1" fow aggwegation mode, ow "0" othewwise.
 *   7-6: Dwivew shouwd init to "0"
 *     5: Window Size Weft; indicates whethew scheduwew can wequest
 *        anothew TFD, based on win size, etc.  Dwivew shouwd init
 *        this bit to "1" fow aggwegation mode, ow "0" fow non-agg.
 *   4-1: Tx FIFO to use (wange 0-7).
 *     0: Queue is active (1), not active (0).
 * Othew bits shouwd be wwitten as "0"
 *
 * NOTE:  If enabwing Scheduwew-ACK mode, chain mode shouwd awso be enabwed
 *        via SCD_QUEUECHAIN_SEW.
 */
#define IW49_SCD_QUEUE_STATUS_BITS(x)\
	(IW49_SCD_STAWT_OFFSET + 0x104 + (x) * 4)

/* Bit fiewd positions */
#define IW49_SCD_QUEUE_STTS_WEG_POS_ACTIVE	(0)
#define IW49_SCD_QUEUE_STTS_WEG_POS_TXF	(1)
#define IW49_SCD_QUEUE_STTS_WEG_POS_WSW	(5)
#define IW49_SCD_QUEUE_STTS_WEG_POS_SCD_ACK	(8)

/* Wwite masks */
#define IW49_SCD_QUEUE_STTS_WEG_POS_SCD_ACT_EN	(10)
#define IW49_SCD_QUEUE_STTS_WEG_MSK		(0x0007FC00)

/**
 * 4965 intewnaw SWAM stwuctuwes fow scheduwew, shawed with dwivew ...
 *
 * Dwivew shouwd cweaw and initiawize the fowwowing aweas aftew weceiving
 * "Awive" wesponse fwom 4965 uCode, i.e. aftew initiaw
 * uCode woad, ow aftew a uCode woad done fow ewwow wecovewy:
 *
 * SCD_CONTEXT_DATA_OFFSET (size 128 bytes)
 * SCD_TX_STTS_BITMAP_OFFSET (size 256 bytes)
 * SCD_TWANSWATE_TBW_OFFSET (size 32 bytes)
 *
 * Dwivew accesses SWAM via HBUS_TAWG_MEM_* wegistews.
 * Dwivew weads base addwess of this scheduwew awea fwom SCD_SWAM_BASE_ADDW.
 * Aww OFFSET vawues must be added to this base addwess.
 */

/*
 * Queue context.  One 8-byte entwy fow each of 16 queues.
 *
 * Dwivew shouwd cweaw this entiwe awea (size 0x80) to 0 aftew weceiving
 * "Awive" notification fwom uCode.  Additionawwy, dwivew shouwd init
 * each queue's entwy as fowwows:
 *
 * WS Dwowd bit fiewds:
 *  0-06:  Max Tx win size fow Scheduwew-ACK.  Dwivew shouwd init to 64.
 *
 * MS Dwowd bit fiewds:
 * 16-22:  Fwame wimit.  Dwivew shouwd init to 10 (0xa).
 *
 * Dwivew shouwd init aww othew bits to 0.
 *
 * Init must be done aftew dwivew weceives "Awive" wesponse fwom 4965 uCode,
 * and when setting up queue fow aggwegation.
 */
#define IW49_SCD_CONTEXT_DATA_OFFSET			0x380
#define IW49_SCD_CONTEXT_QUEUE_OFFSET(x) \
			(IW49_SCD_CONTEXT_DATA_OFFSET + ((x) * 8))

#define IW49_SCD_QUEUE_CTX_WEG1_WIN_SIZE_POS		(0)
#define IW49_SCD_QUEUE_CTX_WEG1_WIN_SIZE_MSK		(0x0000007F)
#define IW49_SCD_QUEUE_CTX_WEG2_FWAME_WIMIT_POS	(16)
#define IW49_SCD_QUEUE_CTX_WEG2_FWAME_WIMIT_MSK	(0x007F0000)

/*
 * Tx Status Bitmap
 *
 * Dwivew shouwd cweaw this entiwe awea (size 0x100) to 0 aftew weceiving
 * "Awive" notification fwom uCode.  Awea is used onwy by device itsewf;
 * no othew suppowt (besides cweawing) is wequiwed fwom dwivew.
 */
#define IW49_SCD_TX_STTS_BITMAP_OFFSET		0x400

/*
 * WAxTID to queue twanswation mapping.
 *
 * When queue is in Scheduwew-ACK mode, fwames pwaced in a that queue must be
 * fow onwy one combination of weceivew addwess (WA) and twaffic ID (TID), i.e.
 * one QOS pwiowity wevew destined fow one station (fow this wiwewess wink,
 * not finaw destination).  The SCD_TWANSWATE_TBW awea pwovides 16 16-bit
 * mappings, one fow each of the 16 queues.  If queue is not in Scheduwew-ACK
 * mode, the device ignowes the mapping vawue.
 *
 * Bit fiewds, fow each 16-bit map:
 * 15-9:  Wesewved, set to 0
 *  8-4:  Index into device's station tabwe fow wecipient station
 *  3-0:  Twaffic ID (tid), wange 0-15
 *
 * Dwivew shouwd cweaw this entiwe awea (size 32 bytes) to 0 aftew weceiving
 * "Awive" notification fwom uCode.  To update a 16-bit map vawue, dwivew
 * must wead a dwowd-awigned vawue fwom device SWAM, wepwace the 16-bit map
 * vawue of intewest, and wwite the dwowd vawue back into device SWAM.
 */
#define IW49_SCD_TWANSWATE_TBW_OFFSET		0x500

/* Find twanswation tabwe dwowd to wead/wwite fow given queue */
#define IW49_SCD_TWANSWATE_TBW_OFFSET_QUEUE(x) \
	((IW49_SCD_TWANSWATE_TBW_OFFSET + ((x) * 2)) & 0xfffffffc)

#define IW_SCD_TXFIFO_POS_TID			(0)
#define IW_SCD_TXFIFO_POS_WA			(4)
#define IW_SCD_QUEUE_WA_TID_MAP_WATID_MSK	(0x01FF)

/*********************** END TX SCHEDUWEW *************************************/

#endif /* __iw_pwph_h__ */
