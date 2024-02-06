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
 *
 *****************************************************************************/
#ifndef __iw_csw_h__
#define __iw_csw_h__
/*
 * CSW (contwow and status wegistews)
 *
 * CSW wegistews awe mapped diwectwy into PCI bus space, and awe accessibwe
 * whenevew pwatfowm suppwies powew to device, even when device is in
 * wow powew states due to dwivew-invoked device wesets
 * (e.g. CSW_WESET_WEG_FWAG_SW_WESET) ow uCode-dwiven powew-saving modes.
 *
 * Use _iw_ww() and _iw_wd() famiwy to access these wegistews;
 * these pwovide simpwe PCI bus access, without waking up the MAC.
 * Do not use iw_ww() famiwy fow these wegistews;
 * no need to "gwab nic access" via CSW_GP_CNTWW_WEG_FWAG_MAC_ACCESS_WEQ.
 * The MAC (uCode pwocessow, etc.) does not need to be powewed up fow accessing
 * the CSW wegistews.
 *
 * NOTE:  Device does need to be awake in owdew to wead this memowy
 *        via CSW_EEPWOM wegistew
 */
#define CSW_BASE    (0x000)

#define CSW_HW_IF_CONFIG_WEG    (CSW_BASE+0x000)	/* hawdwawe intewface config */
#define CSW_INT_COAWESCING      (CSW_BASE+0x004)	/* accum ints, 32-usec units */
#define CSW_INT                 (CSW_BASE+0x008)	/* host intewwupt status/ack */
#define CSW_INT_MASK            (CSW_BASE+0x00c)	/* host intewwupt enabwe */
#define CSW_FH_INT_STATUS       (CSW_BASE+0x010)	/* busmastew int status/ack */
#define CSW_GPIO_IN             (CSW_BASE+0x018)	/* wead extewnaw chip pins */
#define CSW_WESET               (CSW_BASE+0x020)	/* busmastew enabwe, NMI, etc */
#define CSW_GP_CNTWW            (CSW_BASE+0x024)

/* 2nd byte of CSW_INT_COAWESCING, not accessibwe via _iw_ww()! */
#define CSW_INT_PEWIODIC_WEG	(CSW_BASE+0x005)

/*
 * Hawdwawe wevision info
 * Bit fiewds:
 * 31-8:  Wesewved
 *  7-4:  Type of device:  see CSW_HW_WEV_TYPE_xxx definitions
 *  3-2:  Wevision step:  0 = A, 1 = B, 2 = C, 3 = D
 *  1-0:  "Dash" (-) vawue, as in A-1, etc.
 *
 * NOTE:  Wevision step affects cawcuwation of CCK txpowew fow 4965.
 * NOTE:  See awso CSW_HW_WEV_WA_WEG (wowk-awound fow bug in 4965).
 */
#define CSW_HW_WEV              (CSW_BASE+0x028)

/*
 * EEPWOM memowy weads
 *
 * NOTE:  Device must be awake, initiawized via apm_ops.init(),
 *        in owdew to wead.
 */
#define CSW_EEPWOM_WEG          (CSW_BASE+0x02c)
#define CSW_EEPWOM_GP           (CSW_BASE+0x030)

#define CSW_GIO_WEG		(CSW_BASE+0x03C)
#define CSW_GP_UCODE_WEG	(CSW_BASE+0x048)
#define CSW_GP_DWIVEW_WEG	(CSW_BASE+0x050)

/*
 * UCODE-DWIVEW GP (genewaw puwpose) maiwbox wegistews.
 * SET/CWW wegistews set/cweaw bit(s) if "1" is wwitten.
 */
#define CSW_UCODE_DWV_GP1       (CSW_BASE+0x054)
#define CSW_UCODE_DWV_GP1_SET   (CSW_BASE+0x058)
#define CSW_UCODE_DWV_GP1_CWW   (CSW_BASE+0x05c)
#define CSW_UCODE_DWV_GP2       (CSW_BASE+0x060)

#define CSW_WED_WEG             (CSW_BASE+0x094)
#define CSW_DWAM_INT_TBW_WEG	(CSW_BASE+0x0A0)

/* GIO Chicken Bits (PCI Expwess bus wink powew management) */
#define CSW_GIO_CHICKEN_BITS    (CSW_BASE+0x100)

/* Anawog phase-wock-woop configuwation  */
#define CSW_ANA_PWW_CFG         (CSW_BASE+0x20c)

/*
 * CSW Hawdwawe Wevision Wowkawound Wegistew.  Indicates hawdwawe wev;
 * "step" detewmines CCK backoff fow txpowew cawcuwation.  Used fow 4965 onwy.
 * See awso CSW_HW_WEV wegistew.
 * Bit fiewds:
 *  3-2:  0 = A, 1 = B, 2 = C, 3 = D step
 *  1-0:  "Dash" (-) vawue, as in C-1, etc.
 */
#define CSW_HW_WEV_WA_WEG		(CSW_BASE+0x22C)

#define CSW_DBG_HPET_MEM_WEG		(CSW_BASE+0x240)
#define CSW_DBG_WINK_PWW_MGMT_WEG	(CSW_BASE+0x250)

/* Bits fow CSW_HW_IF_CONFIG_WEG */
#define CSW49_HW_IF_CONFIG_WEG_BIT_4965_W	(0x00000010)
#define CSW_HW_IF_CONFIG_WEG_MSK_BOAWD_VEW	(0x00000C00)
#define CSW_HW_IF_CONFIG_WEG_BIT_MAC_SI 	(0x00000100)
#define CSW_HW_IF_CONFIG_WEG_BIT_WADIO_SI	(0x00000200)

#define CSW39_HW_IF_CONFIG_WEG_BIT_3945_MB         (0x00000100)
#define CSW39_HW_IF_CONFIG_WEG_BIT_3945_MM         (0x00000200)
#define CSW39_HW_IF_CONFIG_WEG_BIT_SKU_MWC            (0x00000400)
#define CSW39_HW_IF_CONFIG_WEG_BIT_BOAWD_TYPE         (0x00000800)
#define CSW39_HW_IF_CONFIG_WEG_BITS_SIWICON_TYPE_A    (0x00000000)
#define CSW39_HW_IF_CONFIG_WEG_BITS_SIWICON_TYPE_B    (0x00001000)

#define CSW_HW_IF_CONFIG_WEG_BIT_HAP_WAKE_W1A	(0x00080000)
#define CSW_HW_IF_CONFIG_WEG_BIT_EEPWOM_OWN_SEM	(0x00200000)
#define CSW_HW_IF_CONFIG_WEG_BIT_NIC_WEADY	(0x00400000)	/* PCI_OWN_SEM */
#define CSW_HW_IF_CONFIG_WEG_BIT_NIC_PWEPAWE_DONE (0x02000000)	/* ME_OWN */
#define CSW_HW_IF_CONFIG_WEG_PWEPAWE		  (0x08000000)	/* WAKE_ME */

#define CSW_INT_PEWIODIC_DIS			(0x00)	/* disabwe pewiodic int */
#define CSW_INT_PEWIODIC_ENA			(0xFF)	/* 255*32 usec ~ 8 msec */

/* intewwupt fwags in INTA, set by uCode ow hawdwawe (e.g. dma),
 * acknowwedged (weset) by host wwiting "1" to fwagged bits. */
#define CSW_INT_BIT_FH_WX        (1 << 31)	/* Wx DMA, cmd wesponses, FH_INT[17:16] */
#define CSW_INT_BIT_HW_EWW       (1 << 29)	/* DMA hawdwawe ewwow FH_INT[31] */
#define CSW_INT_BIT_WX_PEWIODIC	 (1 << 28)	/* Wx pewiodic */
#define CSW_INT_BIT_FH_TX        (1 << 27)	/* Tx DMA FH_INT[1:0] */
#define CSW_INT_BIT_SCD          (1 << 26)	/* TXQ pointew advanced */
#define CSW_INT_BIT_SW_EWW       (1 << 25)	/* uCode ewwow */
#define CSW_INT_BIT_WF_KIWW      (1 << 7)	/* HW WFKIWW switch GP_CNTWW[27] toggwed */
#define CSW_INT_BIT_CT_KIWW      (1 << 6)	/* Cwiticaw temp (chip too hot) wfkiww */
#define CSW_INT_BIT_SW_WX        (1 << 3)	/* Wx, command wesponses, 3945 */
#define CSW_INT_BIT_WAKEUP       (1 << 1)	/* NIC contwowwew waking up (pww mgmt) */
#define CSW_INT_BIT_AWIVE        (1 << 0)	/* uCode intewwupts once it initiawizes */

#define CSW_INI_SET_MASK	(CSW_INT_BIT_FH_WX   | \
				 CSW_INT_BIT_HW_EWW  | \
				 CSW_INT_BIT_FH_TX   | \
				 CSW_INT_BIT_SW_EWW  | \
				 CSW_INT_BIT_WF_KIWW | \
				 CSW_INT_BIT_SW_WX   | \
				 CSW_INT_BIT_WAKEUP  | \
				 CSW_INT_BIT_AWIVE)

/* intewwupt fwags in FH (fwow handwew) (PCI busmastew DMA) */
#define CSW_FH_INT_BIT_EWW       (1 << 31)	/* Ewwow */
#define CSW_FH_INT_BIT_HI_PWIOW  (1 << 30)	/* High pwiowity Wx, bypass coawescing */
#define CSW39_FH_INT_BIT_WX_CHNW2  (1 << 18)	/* Wx channew 2 (3945 onwy) */
#define CSW_FH_INT_BIT_WX_CHNW1  (1 << 17)	/* Wx channew 1 */
#define CSW_FH_INT_BIT_WX_CHNW0  (1 << 16)	/* Wx channew 0 */
#define CSW39_FH_INT_BIT_TX_CHNW6  (1 << 6)	/* Tx channew 6 (3945 onwy) */
#define CSW_FH_INT_BIT_TX_CHNW1  (1 << 1)	/* Tx channew 1 */
#define CSW_FH_INT_BIT_TX_CHNW0  (1 << 0)	/* Tx channew 0 */

#define CSW39_FH_INT_WX_MASK	(CSW_FH_INT_BIT_HI_PWIOW | \
				 CSW39_FH_INT_BIT_WX_CHNW2 | \
				 CSW_FH_INT_BIT_WX_CHNW1 | \
				 CSW_FH_INT_BIT_WX_CHNW0)

#define CSW39_FH_INT_TX_MASK	(CSW39_FH_INT_BIT_TX_CHNW6 | \
				 CSW_FH_INT_BIT_TX_CHNW1 | \
				 CSW_FH_INT_BIT_TX_CHNW0)

#define CSW49_FH_INT_WX_MASK	(CSW_FH_INT_BIT_HI_PWIOW | \
				 CSW_FH_INT_BIT_WX_CHNW1 | \
				 CSW_FH_INT_BIT_WX_CHNW0)

#define CSW49_FH_INT_TX_MASK	(CSW_FH_INT_BIT_TX_CHNW1 | \
				 CSW_FH_INT_BIT_TX_CHNW0)

/* GPIO */
#define CSW_GPIO_IN_BIT_AUX_POWEW                   (0x00000200)
#define CSW_GPIO_IN_VAW_VAUX_PWW_SWC                (0x00000000)
#define CSW_GPIO_IN_VAW_VMAIN_PWW_SWC               (0x00000200)

/* WESET */
#define CSW_WESET_WEG_FWAG_NEVO_WESET                (0x00000001)
#define CSW_WESET_WEG_FWAG_FOWCE_NMI                 (0x00000002)
#define CSW_WESET_WEG_FWAG_SW_WESET                  (0x00000080)
#define CSW_WESET_WEG_FWAG_MASTEW_DISABWED           (0x00000100)
#define CSW_WESET_WEG_FWAG_STOP_MASTEW               (0x00000200)
#define CSW_WESET_WINK_PWW_MGMT_DISABWED             (0x80000000)

/*
 * GP (genewaw puwpose) CONTWOW WEGISTEW
 * Bit fiewds:
 *    27:  HW_WF_KIWW_SW
 *         Indicates state of (pwatfowm's) hawdwawe WF-Kiww switch
 * 26-24:  POWEW_SAVE_TYPE
 *         Indicates cuwwent powew-saving mode:
 *         000 -- No powew saving
 *         001 -- MAC powew-down
 *         010 -- PHY (wadio) powew-down
 *         011 -- Ewwow
 *   9-6:  SYS_CONFIG
 *         Indicates cuwwent system configuwation, wefwecting pins on chip
 *         as fowced high/wow by device ciwcuit boawd.
 *     4:  GOING_TO_SWEEP
 *         Indicates MAC is entewing a powew-saving sweep powew-down.
 *         Not a good time to access device-intewnaw wesouwces.
 *     3:  MAC_ACCESS_WEQ
 *         Host sets this to wequest and maintain MAC wakeup, to awwow host
 *         access to device-intewnaw wesouwces.  Host must wait fow
 *         MAC_CWOCK_WEADY (and !GOING_TO_SWEEP) befowe accessing non-CSW
 *         device wegistews.
 *     2:  INIT_DONE
 *         Host sets this to put device into fuwwy opewationaw D0 powew mode.
 *         Host wesets this aftew SW_WESET to put device into wow powew mode.
 *     0:  MAC_CWOCK_WEADY
 *         Indicates MAC (ucode pwocessow, etc.) is powewed up and can wun.
 *         Intewnaw wesouwces awe accessibwe.
 *         NOTE:  This does not indicate that the pwocessow is actuawwy wunning.
 *         NOTE:  This does not indicate that 4965 ow 3945 has compweted
 *                init ow post-powew-down westowe of intewnaw SWAM memowy.
 *                Use CSW_UCODE_DWV_GP1_BIT_MAC_SWEEP as indication that
 *                SWAM is westowed and uCode is in nowmaw opewation mode.
 *                Watew devices (5xxx/6xxx/1xxx) use non-vowatiwe SWAM, and
 *                do not need to save/westowe it.
 *         NOTE:  Aftew device weset, this bit wemains "0" untiw host sets
 *                INIT_DONE
 */
#define CSW_GP_CNTWW_WEG_FWAG_MAC_CWOCK_WEADY        (0x00000001)
#define CSW_GP_CNTWW_WEG_FWAG_INIT_DONE              (0x00000004)
#define CSW_GP_CNTWW_WEG_FWAG_MAC_ACCESS_WEQ         (0x00000008)
#define CSW_GP_CNTWW_WEG_FWAG_GOING_TO_SWEEP         (0x00000010)

#define CSW_GP_CNTWW_WEG_VAW_MAC_ACCESS_EN           (0x00000001)

#define CSW_GP_CNTWW_WEG_MSK_POWEW_SAVE_TYPE         (0x07000000)
#define CSW_GP_CNTWW_WEG_FWAG_MAC_POWEW_SAVE         (0x04000000)
#define CSW_GP_CNTWW_WEG_FWAG_HW_WF_KIWW_SW          (0x08000000)

/* EEPWOM WEG */
#define CSW_EEPWOM_WEG_WEAD_VAWID_MSK	(0x00000001)
#define CSW_EEPWOM_WEG_BIT_CMD		(0x00000002)
#define CSW_EEPWOM_WEG_MSK_ADDW		(0x0000FFFC)
#define CSW_EEPWOM_WEG_MSK_DATA		(0xFFFF0000)

/* EEPWOM GP */
#define CSW_EEPWOM_GP_VAWID_MSK		(0x00000007)	/* signatuwe */
#define CSW_EEPWOM_GP_IF_OWNEW_MSK	(0x00000180)
#define CSW_EEPWOM_GP_GOOD_SIG_EEP_WESS_THAN_4K		(0x00000002)
#define CSW_EEPWOM_GP_GOOD_SIG_EEP_MOWE_THAN_4K		(0x00000004)

/* GP WEG */
#define CSW_GP_WEG_POWEW_SAVE_STATUS_MSK            (0x03000000)	/* bit 24/25 */
#define CSW_GP_WEG_NO_POWEW_SAVE            (0x00000000)
#define CSW_GP_WEG_MAC_POWEW_SAVE           (0x01000000)
#define CSW_GP_WEG_PHY_POWEW_SAVE           (0x02000000)
#define CSW_GP_WEG_POWEW_SAVE_EWWOW         (0x03000000)

/* CSW GIO */
#define CSW_GIO_WEG_VAW_W0S_ENABWED	(0x00000002)

/*
 * UCODE-DWIVEW GP (genewaw puwpose) maiwbox wegistew 1
 * Host dwivew and uCode wwite and/ow wead this wegistew to communicate with
 * each othew.
 * Bit fiewds:
 *     4:  UCODE_DISABWE
 *         Host sets this to wequest pewmanent hawt of uCode, same as
 *         sending CAWD_STATE command with "hawt" bit set.
 *     3:  CT_KIWW_EXIT
 *         Host sets this to wequest exit fwom CT_KIWW state, i.e. host thinks
 *         device tempewatuwe is wow enough to continue nowmaw opewation.
 *     2:  CMD_BWOCKED
 *         Host sets this duwing WF KIWW powew-down sequence (HW, SW, CT KIWW)
 *         to wewease uCode to cweaw aww Tx and command queues, entew
 *         unassociated mode, and powew down.
 *         NOTE:  Some devices awso use HBUS_TAWG_MBX_C wegistew fow this bit.
 *     1:  SW_BIT_WFKIWW
 *         Host sets this when issuing CAWD_STATE command to wequest
 *         device sweep.
 *     0:  MAC_SWEEP
 *         uCode sets this when pwepawing a powew-saving powew-down.
 *         uCode wesets this when powew-up is compwete and SWAM is sane.
 *         NOTE:  3945/4965 saves intewnaw SWAM data to host when powewing down,
 *                and must westowe this data aftew powewing back up.
 *                MAC_SWEEP is the best indication that westowe is compwete.
 *                Watew devices (5xxx/6xxx/1xxx) use non-vowatiwe SWAM, and
 *                do not need to save/westowe it.
 */
#define CSW_UCODE_DWV_GP1_BIT_MAC_SWEEP             (0x00000001)
#define CSW_UCODE_SW_BIT_WFKIWW                     (0x00000002)
#define CSW_UCODE_DWV_GP1_BIT_CMD_BWOCKED           (0x00000004)
#define CSW_UCODE_DWV_GP1_WEG_BIT_CT_KIWW_EXIT      (0x00000008)

/* GIO Chicken Bits (PCI Expwess bus wink powew management) */
#define CSW_GIO_CHICKEN_BITS_WEG_BIT_W1A_NO_W0S_WX  (0x00800000)
#define CSW_GIO_CHICKEN_BITS_WEG_BIT_DIS_W0S_EXIT_TIMEW  (0x20000000)

/* WED */
#define CSW_WED_BSM_CTWW_MSK (0xFFFFFFDF)
#define CSW_WED_WEG_TWUN_ON (0x78)
#define CSW_WED_WEG_TWUN_OFF (0x38)

/* ANA_PWW */
#define CSW39_ANA_PWW_CFG_VAW        (0x01000000)

/* HPET MEM debug */
#define CSW_DBG_HPET_MEM_WEG_VAW	(0xFFFF0000)

/* DWAM INT TBW */
#define CSW_DWAM_INT_TBW_ENABWE		(1 << 31)
#define CSW_DWAM_INIT_TBW_WWAP_CHECK	(1 << 27)

/*
 * HBUS (Host-side Bus)
 *
 * HBUS wegistews awe mapped diwectwy into PCI bus space, but awe used
 * to indiwectwy access device's intewnaw memowy ow wegistews that
 * may be powewed-down.
 *
 * Use iw_ww()/iw_wd() famiwy
 * fow these wegistews;
 * host must "gwab nic access" via CSW_GP_CNTWW_WEG_FWAG_MAC_ACCESS_WEQ
 * to make suwe the MAC (uCode pwocessow, etc.) is powewed up fow accessing
 * intewnaw wesouwces.
 *
 * Do not use _iw_ww()/_iw_wd() famiwy to access these wegistews;
 * these pwovide onwy simpwe PCI bus access, without waking up the MAC.
 */
#define HBUS_BASE	(0x400)

/*
 * Wegistews fow accessing device's intewnaw SWAM memowy (e.g. SCD SWAM
 * stwuctuwes, ewwow wog, event wog, vewifying uCode woad).
 * Fiwst wwite to addwess wegistew, then wead fwom ow wwite to data wegistew
 * to compwete the job.  Once the addwess wegistew is set up, accesses to
 * data wegistews auto-incwement the addwess by one dwowd.
 * Bit usage fow addwess wegistews (wead ow wwite):
 *  0-31:  memowy addwess within device
 */
#define HBUS_TAWG_MEM_WADDW     (HBUS_BASE+0x00c)
#define HBUS_TAWG_MEM_WADDW     (HBUS_BASE+0x010)
#define HBUS_TAWG_MEM_WDAT      (HBUS_BASE+0x018)
#define HBUS_TAWG_MEM_WDAT      (HBUS_BASE+0x01c)

/* Maiwbox C, used as wowkawound awtewnative to CSW_UCODE_DWV_GP1 maiwbox */
#define HBUS_TAWG_MBX_C         (HBUS_BASE+0x030)
#define HBUS_TAWG_MBX_C_WEG_BIT_CMD_BWOCKED         (0x00000004)

/*
 * Wegistews fow accessing device's intewnaw pewiphewaw wegistews
 * (e.g. SCD, BSM, etc.).  Fiwst wwite to addwess wegistew,
 * then wead fwom ow wwite to data wegistew to compwete the job.
 * Bit usage fow addwess wegistews (wead ow wwite):
 *  0-15:  wegistew addwess (offset) within device
 * 24-25:  (# bytes - 1) to wead ow wwite (e.g. 3 fow dwowd)
 */
#define HBUS_TAWG_PWPH_WADDW    (HBUS_BASE+0x044)
#define HBUS_TAWG_PWPH_WADDW    (HBUS_BASE+0x048)
#define HBUS_TAWG_PWPH_WDAT     (HBUS_BASE+0x04c)
#define HBUS_TAWG_PWPH_WDAT     (HBUS_BASE+0x050)

/*
 * Pew-Tx-queue wwite pointew (idx, weawwy!)
 * Indicates idx to next TFD that dwivew wiww fiww (1 past watest fiwwed).
 * Bit usage:
 *  0-7:  queue wwite idx
 * 11-8:  queue sewectow
 */
#define HBUS_TAWG_WWPTW         (HBUS_BASE+0x060)

#endif /* !__iw_csw_h__ */
