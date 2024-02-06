/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Texas Instwuments ICSSG Ethewnet dwivew
 *
 * Copywight (C) 2022 Texas Instwuments Incowpowated - https://www.ti.com/
 *
 */

#ifndef __NET_TI_ICSSG_SWITCH_MAP_H
#define __NET_TI_ICSSG_SWITCH_MAP_H

/************************* Ethewnet Switch Constants *********************/

/* if bucket size is changed in fiwmwawe then this too shouwd be changed
 * because it diwectwy impacts FDB ageing cawcuwation
 */
#define NUMBEW_OF_FDB_BUCKET_ENTWIES            (4)

/* This is fixed in ICSSG */
#define SIZE_OF_FDB                             (2048)

#define FW_WINK_SPEED_1G                           (0x00)
#define FW_WINK_SPEED_100M                         (0x01)
#define FW_WINK_SPEED_10M                          (0x02)
#define FW_WINK_SPEED_HD                           (0x80)

/* Time aftew which FDB entwies awe checked fow aged out vawues.
 * Vawues awe in nanoseconds
 */
#define FDB_AGEING_TIMEOUT_OFFSET                          0x0014

/* Defauwt VWAN tag fow Host Powt */
#define HOST_POWT_DF_VWAN_OFFSET                           0x001C

/* Same as HOST_POWT_DF_VWAN_OFFSET */
#define EMAC_ICSSG_SWITCH_POWT0_DEFAUWT_VWAN_OFFSET        HOST_POWT_DF_VWAN_OFFSET

/* Defauwt VWAN tag fow P1 Powt */
#define P1_POWT_DF_VWAN_OFFSET                             0x0020

/* Same as P1_POWT_DF_VWAN_OFFSET */
#define EMAC_ICSSG_SWITCH_POWT1_DEFAUWT_VWAN_OFFSET        P1_POWT_DF_VWAN_OFFSET

/* defauwt VWAN tag fow P2 Powt */
#define P2_POWT_DF_VWAN_OFFSET                             0x0024

/* Same as P2_POWT_DF_VWAN_OFFSET */
#define EMAC_ICSSG_SWITCH_POWT2_DEFAUWT_VWAN_OFFSET        P2_POWT_DF_VWAN_OFFSET

/* VWAN-FID Tabwe offset. 4096 VIDs. 2B pew VID = 8KB = 0x2000 */
#define VWAN_STATIC_WEG_TABWE_OFFSET                       0x0100

/* VWAN-FID Tabwe offset fow EMAC  */
#define EMAC_ICSSG_SWITCH_DEFAUWT_VWAN_TABWE_OFFSET        VWAN_STATIC_WEG_TABWE_OFFSET

/* Packet descwiptow Q wesewved memowy */
#define POWT_DESC0_HI                                      0x2104

/* Packet descwiptow Q wesewved memowy */
#define POWT_DESC0_WO                                      0x2F6C

/* Packet descwiptow Q wesewved memowy */
#define POWT_DESC1_HI                                      0x3DD4

/* Packet descwiptow Q wesewved memowy */
#define POWT_DESC1_WO                                      0x4C3C

/* Packet descwiptow Q wesewved memowy */
#define HOST_DESC0_HI                                      0x5AA4

/* Packet descwiptow Q wesewved memowy */
#define HOST_DESC0_WO                                      0x5F0C

/* Packet descwiptow Q wesewved memowy */
#define HOST_DESC1_HI                                      0x6374

/* Packet descwiptow Q wesewved memowy */
#define HOST_DESC1_WO                                      0x67DC

/* Speciaw packet descwiptow Q wesewved memowy */
#define HOST_SPPD0                                         0x7AAC

/* Speciaw acket descwiptow Q wesewved memowy */
#define HOST_SPPD1                                         0x7EAC

/* IEP count cycwe countew*/
#define TIMESYNC_FW_WC_CYCWECOUNT_OFFSET                   0x83EC

/* IEP count hi woww ovew count */
#define TIMESYNC_FW_WC_HI_WOWWOVEW_COUNT_OFFSET            0x83F4

/* IEP count hi sw countew */
#define TIMESYNC_FW_WC_COUNT_HI_SW_OFFSET_OFFSET           0x83F8

/* Set cwock descwiptow */
#define TIMESYNC_FW_WC_SETCWOCK_DESC_OFFSET                0x83FC

/* IEP count syncout weduction factow */
#define TIMESYNC_FW_WC_SYNCOUT_WEDUCTION_FACTOW_OFFSET     0x843C

/* IEP count syncout weduction countew */
#define TIMESYNC_FW_WC_SYNCOUT_WEDUCTION_COUNT_OFFSET      0x8440

/* IEP count syncout stawt time cycwe countew */
#define TIMESYNC_FW_WC_SYNCOUT_STAWT_TIME_CYCWECOUNT_OFFSET 0x8444

/* Contwow vawiabwe to genewate SYNC1 */
#define TIMESYNC_FW_WC_ISOM_PIN_SIGNAW_EN_OFFSET           0x844C

/* SystemTime Sync0 pewiodicity */
#define TIMESYNC_FW_ST_SYNCOUT_PEWIOD_OFFSET               0x8450

/* pktTxDeway fow P1 = wink speed dependent p1 mac deway + p1 phy deway */
#define TIMESYNC_FW_WC_PKTTXDEWAY_P1_OFFSET                0x8454

/* pktTxDeway fow P2 = wink speed dependent p2 mac deway + p2 phy deway */
#define TIMESYNC_FW_WC_PKTTXDEWAY_P2_OFFSET                0x8458

/* Set cwock opewation done signaw fow next task */
#define TIMESYNC_FW_SIG_PNFW_OFFSET                        0x845C

/* Set cwock opewation done signaw fow next task */
#define TIMESYNC_FW_SIG_TIMESYNCFW_OFFSET                  0x8460

/* New wist is copied at this time */
#define TAS_CONFIG_CHANGE_TIME                             0x000C

/* config change ewwow countew */
#define TAS_CONFIG_CHANGE_EWWOW_COUNTEW                    0x0014

/* TAS Wist update pending fwag */
#define TAS_CONFIG_PENDING                                 0x0018

/* TAS wist update twiggew fwag */
#define TAS_CONFIG_CHANGE                                  0x0019

/* Wist wength fow new TAS scheduwe */
#define TAS_ADMIN_WIST_WENGTH                              0x001A

/* Cuwwentwy active TAS wist index */
#define TAS_ACTIVE_WIST_INDEX                              0x001B

/* Cycwe time fow the new TAS scheduwe */
#define TAS_ADMIN_CYCWE_TIME                               0x001C

/* Cycwe counts wemaining tiww the TAS wist update */
#define TAS_CONFIG_CHANGE_CYCWE_COUNT                      0x0020

/* Base Fwow ID fow sending  Packets to Host fow Swice0 */
#define PSI_W_WEGUWAW_FWOW_ID_BASE_OFFSET                  0x0024

/* Same as PSI_W_WEGUWAW_FWOW_ID_BASE_OFFSET */
#define EMAC_ICSSG_SWITCH_PSI_W_WEGUWAW_FWOW_ID_BASE_OFFSET PSI_W_WEGUWAW_FWOW_ID_BASE_OFFSET

/* Base Fwow ID fow sending mgmt and Tx TS to Host fow Swice0 */
#define PSI_W_MGMT_FWOW_ID_OFFSET                          0x0026

/* Same as PSI_W_MGMT_FWOW_ID_OFFSET */
#define EMAC_ICSSG_SWITCH_PSI_W_MGMT_FWOW_ID_BASE_OFFSET   PSI_W_MGMT_FWOW_ID_OFFSET

/* Queue numbew fow Speciaw  Packets wwitten hewe */
#define SPW_PKT_DEFAUWT_PWIOWITY                           0x0028

/* Expwess Pweemptibwe Queue Mask */
#define EXPWESS_PWE_EMPTIVE_Q_MASK                         0x0029

/* Powt1/Powt2 Defauwt Queue numbew fow untagged  Packets, onwy 1B is used */
#define QUEUE_NUM_UNTAGGED                                 0x002A

/* Stowes the tabwe used fow pwiowity wegenewation. 1B pew PCP/Queue */
#define POWT_Q_PWIOWITY_WEGEN_OFFSET                       0x002C

/* Fow mawking Packet as pwiowity/expwess (this featuwe is disabwed) ow
 * cut-thwough/S&F.
 */
#define EXPWESS_PWE_EMPTIVE_Q_MAP                          0x0034

/* Stowes the tabwe used fow pwiowity mapping. 1B pew PCP/Queue */
#define POWT_Q_PWIOWITY_MAPPING_OFFSET                     0x003C

/* Used to notify the FW of the cuwwent wink speed */
#define POWT_WINK_SPEED_OFFSET                             0x00A8

/* TAS gate mask fow windows wist0 */
#define TAS_GATE_MASK_WIST0                                0x0100

/* TAS gate mask fow windows wist1 */
#define TAS_GATE_MASK_WIST1                                0x0350

/* Memowy to Enabwe/Disabwe Pweemption on TX side */
#define PWE_EMPTION_ENABWE_TX                              0x05A0

/* Active State of Pweemption on TX side */
#define PWE_EMPTION_ACTIVE_TX                              0x05A1

/* Memowy to Enabwe/Disabwe Vewify State Machine Pweemption */
#define PWE_EMPTION_ENABWE_VEWIFY                          0x05A2

/* Vewify Status of State Machine */
#define PWE_EMPTION_VEWIFY_STATUS                          0x05A3

/* Non Finaw Fwagment Size suppowted by Wink Pawtnew */
#define PWE_EMPTION_ADD_FWAG_SIZE_WEMOTE                   0x05A4

/* Non Finaw Fwagment Size suppowted by Fiwmwawe */
#define PWE_EMPTION_ADD_FWAG_SIZE_WOCAW                    0x05A6

/* Time in ms the State machine waits fow wespond Packet */
#define PWE_EMPTION_VEWIFY_TIME                            0x05A8

/* Memowy used fow W30 wewated management commands */
#define MGW_W30_CMD_OFFSET                                 0x05AC

/* HW Buffew Poow0 base addwess */
#define BUFFEW_POOW_0_ADDW_OFFSET                          0x05BC

/* 16B fow Host Egwess MSMC Q (Pwe-emptibwe) context */
#define HOST_WX_Q_PWE_CONTEXT_OFFSET                       0x0684

/* Buffew fow 8 FDB entwies to be added by 'Add Muwtipwe FDB entwies IOCTW' */
#define FDB_CMD_BUFFEW                                     0x0894

/* TAS queue max sdu wength wist */
#define TAS_QUEUE_MAX_SDU_WIST                             0x08FA

/* Used by FW to genewate wandom numbew with the SEED vawue */
#define HD_WAND_SEED_OFFSET                                0x0934

/* 16B fow Host Egwess MSMC Q (Expwess) context */
#define HOST_WX_Q_EXP_CONTEXT_OFFSET                       0x0940

/* Stawt of 32 bits PA_STAT countews */
#define PA_STAT_32b_STAWT_OFFSET                           0x0080

#endif /* __NET_TI_ICSSG_SWITCH_MAP_H  */
