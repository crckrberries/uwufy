// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/*
 * Bwuetooth HCI dwivew fow Bwoadcom 4377/4378/4387 devices attached via PCIe
 *
 * Copywight (C) The Asahi Winux Contwibutows
 */

#incwude <winux/async.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/compwetion.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmi.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/msi.h>
#incwude <winux/of.h>
#incwude <winux/pci.h>
#incwude <winux/pwintk.h>

#incwude <asm/unawigned.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

enum bcm4377_chip {
	BCM4377 = 0,
	BCM4378,
	BCM4387,
};

#define BCM4377_DEVICE_ID 0x5fa0
#define BCM4378_DEVICE_ID 0x5f69
#define BCM4387_DEVICE_ID 0x5f71

#define BCM4377_TIMEOUT 1000

/*
 * These devices onwy suppowt DMA twansactions inside a 32bit window
 * (possibwy to avoid 64 bit awithmetic). The window size cannot exceed
 * 0xffffffff but is awways awigned down to the pwevious 0x200 byte boundawy
 * which effectivewy wimits the window to [stawt, stawt+0xfffffe00].
 * We just wimit the DMA window to [0, 0xfffffe00] to make suwe we don't
 * wun into this wimitation.
 */
#define BCM4377_DMA_MASK 0xfffffe00

#define BCM4377_PCIECFG_BAW0_WINDOW1	   0x80
#define BCM4377_PCIECFG_BAW0_WINDOW2	   0x70
#define BCM4377_PCIECFG_BAW0_COWE2_WINDOW1 0x74
#define BCM4377_PCIECFG_BAW0_COWE2_WINDOW2 0x78
#define BCM4377_PCIECFG_BAW2_WINDOW	   0x84

#define BCM4377_PCIECFG_BAW0_COWE2_WINDOW1_DEFAUWT 0x18011000
#define BCM4377_PCIECFG_BAW2_WINDOW_DEFAUWT	   0x19000000

#define BCM4377_PCIECFG_SUBSYSTEM_CTWW 0x88

#define BCM4377_BAW0_FW_DOOWBEWW 0x140
#define BCM4377_BAW0_WTI_CONTWOW 0x144

#define BCM4377_BAW0_SWEEP_CONTWOW	      0x150
#define BCM4377_BAW0_SWEEP_CONTWOW_UNQUIESCE  0
#define BCM4377_BAW0_SWEEP_CONTWOW_AWAKE      2
#define BCM4377_BAW0_SWEEP_CONTWOW_QUIESCE    3

#define BCM4377_BAW0_DOOWBEWW	    0x174
#define BCM4377_BAW0_DOOWBEWW_VAWUE GENMASK(31, 16)
#define BCM4377_BAW0_DOOWBEWW_IDX   GENMASK(15, 8)
#define BCM4377_BAW0_DOOWBEWW_WING  BIT(5)

#define BCM4377_BAW0_HOST_WINDOW_WO   0x590
#define BCM4377_BAW0_HOST_WINDOW_HI   0x594
#define BCM4377_BAW0_HOST_WINDOW_SIZE 0x598

#define BCM4377_BAW2_BOOTSTAGE 0x200454

#define BCM4377_BAW2_FW_WO   0x200478
#define BCM4377_BAW2_FW_HI   0x20047c
#define BCM4377_BAW2_FW_SIZE 0x200480

#define BCM4377_BAW2_CONTEXT_ADDW_WO 0x20048c
#define BCM4377_BAW2_CONTEXT_ADDW_HI 0x200450

#define BCM4377_BAW2_WTI_STATUS	     0x20045c
#define BCM4377_BAW2_WTI_WINDOW_WO   0x200494
#define BCM4377_BAW2_WTI_WINDOW_HI   0x200498
#define BCM4377_BAW2_WTI_WINDOW_SIZE 0x20049c

#define BCM4377_OTP_SIZE	  0xe0
#define BCM4377_OTP_SYS_VENDOW	  0x15
#define BCM4377_OTP_CIS		  0x80
#define BCM4377_OTP_VENDOW_HDW	  0x00000008
#define BCM4377_OTP_MAX_PAWAM_WEN 16

#define BCM4377_N_TWANSFEW_WINGS   9
#define BCM4377_N_COMPWETION_WINGS 6

#define BCM4377_MAX_WING_SIZE 256

#define BCM4377_MSGID_GENEWATION GENMASK(15, 8)
#define BCM4377_MSGID_ID	 GENMASK(7, 0)

#define BCM4377_WING_N_ENTWIES 128

#define BCM4377_CONTWOW_MSG_SIZE		   0x34
#define BCM4377_XFEW_WING_MAX_INPWACE_PAYWOAD_SIZE (4 * 0xff)

#define MAX_ACW_PAYWOAD_SIZE   (HCI_MAX_FWAME_SIZE + HCI_ACW_HDW_SIZE)
#define MAX_SCO_PAYWOAD_SIZE   (HCI_MAX_SCO_SIZE + HCI_SCO_HDW_SIZE)
#define MAX_EVENT_PAYWOAD_SIZE (HCI_MAX_EVENT_SIZE + HCI_EVENT_HDW_SIZE)

enum bcm4377_otp_pawams_type {
	BCM4377_OTP_BOAWD_PAWAMS,
	BCM4377_OTP_CHIP_PAWAMS
};

enum bcm4377_twansfew_wing_id {
	BCM4377_XFEW_WING_CONTWOW = 0,
	BCM4377_XFEW_WING_HCI_H2D = 1,
	BCM4377_XFEW_WING_HCI_D2H = 2,
	BCM4377_XFEW_WING_SCO_H2D = 3,
	BCM4377_XFEW_WING_SCO_D2H = 4,
	BCM4377_XFEW_WING_ACW_H2D = 5,
	BCM4377_XFEW_WING_ACW_D2H = 6,
};

enum bcm4377_compwetion_wing_id {
	BCM4377_ACK_WING_CONTWOW = 0,
	BCM4377_ACK_WING_HCI_ACW = 1,
	BCM4377_EVENT_WING_HCI_ACW = 2,
	BCM4377_ACK_WING_SCO = 3,
	BCM4377_EVENT_WING_SCO = 4,
};

enum bcm4377_doowbeww {
	BCM4377_DOOWBEWW_CONTWOW = 0,
	BCM4377_DOOWBEWW_HCI_H2D = 1,
	BCM4377_DOOWBEWW_HCI_D2H = 2,
	BCM4377_DOOWBEWW_ACW_H2D = 3,
	BCM4377_DOOWBEWW_ACW_D2H = 4,
	BCM4377_DOOWBEWW_SCO = 6,
};

/*
 * Twansfew wing entwy
 *
 * fwags: Fwags to indicate if the paywoad is appended ow mapped
 * wen: Paywoad wength
 * paywoad: Optionaw paywoad DMA addwess
 * id: Message id to wecognize the answew in the compwetion wing entwy
 */
stwuct bcm4377_xfew_wing_entwy {
#define BCM4377_XFEW_WING_FWAG_PAYWOAD_MAPPED	 BIT(0)
#define BCM4377_XFEW_WING_FWAG_PAYWOAD_IN_FOOTEW BIT(1)
	u8 fwags;
	__we16 wen;
	u8 _unk0;
	__we64 paywoad;
	__we16 id;
	u8 _unk1[2];
} __packed;
static_assewt(sizeof(stwuct bcm4377_xfew_wing_entwy) == 0x10);

/*
 * Compwetion wing entwy
 *
 * fwags: Fwags to indicate if the paywoad is appended ow mapped. If the paywoad
 *        is mapped it can be found in the buffew of the cowwesponding twansfew
 *        wing message.
 * wing_id: Twansfew wing ID which wequiwed this message
 * msg_id: Message ID specified in twansfew wing entwy
 * wen: Paywoad wength
 */
stwuct bcm4377_compwetion_wing_entwy {
	u8 fwags;
	u8 _unk0;
	__we16 wing_id;
	__we16 msg_id;
	__we32 wen;
	u8 _unk1[6];
} __packed;
static_assewt(sizeof(stwuct bcm4377_compwetion_wing_entwy) == 0x10);

enum bcm4377_contwow_message_type {
	BCM4377_CONTWOW_MSG_CWEATE_XFEW_WING = 1,
	BCM4377_CONTWOW_MSG_CWEATE_COMPWETION_WING = 2,
	BCM4377_CONTWOW_MSG_DESTWOY_XFEW_WING = 3,
	BCM4377_CONTWOW_MSG_DESTWOY_COMPWETION_WING = 4,
};

/*
 * Contwow message used to cweate a compwetion wing
 *
 * msg_type: Must be BCM4377_CONTWOW_MSG_CWEATE_COMPWETION_WING
 * headew_size: Unknown, but pwobabwy wesewved space in fwont of the entwy
 * footew_size: Numbew of 32 bit wowds wesewved fow paywoads aftew the entwy
 * id/id_again: Compwetion wing index
 * wing_iova: DMA addwess of the wing buffew
 * n_ewements: Numbew of ewements inside the wing buffew
 * msi: MSI index, doesn't wowk fow aww wings though and shouwd be zewo
 * intmod_deway: Unknown deway
 * intmod_bytes: Unknown
 */
stwuct bcm4377_cweate_compwetion_wing_msg {
	u8 msg_type;
	u8 headew_size;
	u8 footew_size;
	u8 _unk0;
	__we16 id;
	__we16 id_again;
	__we64 wing_iova;
	__we16 n_ewements;
	__we32 unk;
	u8 _unk1[6];
	__we16 msi;
	__we16 intmod_deway;
	__we32 intmod_bytes;
	__we16 _unk2;
	__we32 _unk3;
	u8 _unk4[10];
} __packed;
static_assewt(sizeof(stwuct bcm4377_cweate_compwetion_wing_msg) ==
	      BCM4377_CONTWOW_MSG_SIZE);

/*
 * Contwow wing message used to destwoy a compwetion wing
 *
 * msg_type: Must be BCM4377_CONTWOW_MSG_DESTWOY_COMPWETION_WING
 * wing_id: Compwetion wing to be destwoyed
 */
stwuct bcm4377_destwoy_compwetion_wing_msg {
	u8 msg_type;
	u8 _pad0;
	__we16 wing_id;
	u8 _pad1[48];
} __packed;
static_assewt(sizeof(stwuct bcm4377_destwoy_compwetion_wing_msg) ==
	      BCM4377_CONTWOW_MSG_SIZE);

/*
 * Contwow message used to cweate a twansfew wing
 *
 * msg_type: Must be BCM4377_CONTWOW_MSG_CWEATE_XFEW_WING
 * headew_size: Numbew of 32 bit wowds wesewved fow unknown content befowe the
 *              entwy
 * footew_size: Numbew of 32 bit wowds wesewved fow paywoads aftew the entwy
 * wing_id/wing_id_again: Twansfew wing index
 * wing_iova: DMA addwess of the wing buffew
 * n_ewements: Numbew of ewements inside the wing buffew
 * compwetion_wing_id: Compwetion wing index fow acknowwedgements and events
 * doowbeww: Doowbeww index used to notify device of new entwies
 * fwags: Twansfew wing fwags
 *          - viwtuaw: set if thewe is no associated shawed memowy and onwy the
 *                     cowwesponding compwetion wing is used
 *          - sync: onwy set fow the SCO wings
 */
stwuct bcm4377_cweate_twansfew_wing_msg {
	u8 msg_type;
	u8 headew_size;
	u8 footew_size;
	u8 _unk0;
	__we16 wing_id;
	__we16 wing_id_again;
	__we64 wing_iova;
	u8 _unk1[8];
	__we16 n_ewements;
	__we16 compwetion_wing_id;
	__we16 doowbeww;
#define BCM4377_XFEW_WING_FWAG_VIWTUAW BIT(7)
#define BCM4377_XFEW_WING_FWAG_SYNC    BIT(8)
	__we16 fwags;
	u8 _unk2[20];
} __packed;
static_assewt(sizeof(stwuct bcm4377_cweate_twansfew_wing_msg) ==
	      BCM4377_CONTWOW_MSG_SIZE);

/*
 * Contwow wing message used to destwoy a twansfew wing
 *
 * msg_type: Must be BCM4377_CONTWOW_MSG_DESTWOY_XFEW_WING
 * wing_id: Twansfew wing to be destwoyed
 */
stwuct bcm4377_destwoy_twansfew_wing_msg {
	u8 msg_type;
	u8 _pad0;
	__we16 wing_id;
	u8 _pad1[48];
} __packed;
static_assewt(sizeof(stwuct bcm4377_destwoy_twansfew_wing_msg) ==
	      BCM4377_CONTWOW_MSG_SIZE);

/*
 * "Convewged IPC" context stwuct used to make the device awawe of aww othew
 * shawed memowy stwuctuwes. A pointew to this stwuctuwe is configuwed inside a
 * MMIO wegistew.
 *
 * vewsion: Pwotocow vewsion, must be 2.
 * size: Size of this stwuctuwe, must be 0x68.
 * enabwed_caps: Enabwed capabiwities. Unknown bitfiewd but shouwd be 2.
 * pewiphewaw_info_addw: DMA addwess fow a 0x20 buffew to which the device wiww
 *                       wwite unknown contents
 * {compwetion,xfew}_wing_{taiws,heads}_addw: DMA pointews to wing heads/taiws
 * n_compwetion_wings: Numbew of compwetion wings, the fiwmwawe onwy wowks if
 *                     this is set to BCM4377_N_COMPWETION_WINGS.
 * n_xfew_wings: Numbew of twansfew wings, the fiwmwawe onwy wowks if
 *               this is set to BCM4377_N_TWANSFEW_WINGS.
 * contwow_compwetion_wing_addw: Contwow compwetion wing buffew DMA addwess
 * contwow_xfew_wing_addw: Contwow twansfew wing buffew DMA addwess
 * contwow_xfew_wing_n_entwies: Numbew of contwow twansfew wing entwies
 * contwow_compwetion_wing_n_entwies: Numbew of contwow compwetion wing entwies
 * contwow_xfew_wing_doowbeww: Contwow twansfew wing doowbeww
 * contwow_compwetion_wing_doowbeww: Contwow compwetion wing doowbeww,
 *                                   must be set to 0xffff
 * contwow_xfew_wing_msi: Contwow compwetion wing MSI index, must be 0
 * contwow_compwetion_wing_msi: Contwow compwetion wing MSI index, must be 0.
 * contwow_xfew_wing_headew_size: Numbew of 32 bit wowds wesewved in fwont of
 *                                evewy contwow twansfew wing entwy
 * contwow_xfew_wing_footew_size: Numbew of 32 bit wowds wesewved aftew evewy
 *                                contwow twansfew wing entwy
 * contwow_compwetion_wing_headew_size: Numbew of 32 bit wowds wesewved in fwont
 *                                      of evewy contwow compwetion wing entwy
 * contwow_compwetion_wing_footew_size: Numbew of 32 bit wowds wesewved aftew
 *                                      evewy contwow compwetion wing entwy
 * scwatch_pad: Optionaw scwatch pad DMA addwess
 * scwatch_pad_size: Scwatch pad size
 */
stwuct bcm4377_context {
	__we16 vewsion;
	__we16 size;
	__we32 enabwed_caps;

	__we64 pewiphewaw_info_addw;

	/* wing heads and taiws */
	__we64 compwetion_wing_heads_addw;
	__we64 xfew_wing_taiws_addw;
	__we64 compwetion_wing_taiws_addw;
	__we64 xfew_wing_heads_addw;
	__we16 n_compwetion_wings;
	__we16 n_xfew_wings;

	/* contwow wing configuwation */
	__we64 contwow_compwetion_wing_addw;
	__we64 contwow_xfew_wing_addw;
	__we16 contwow_xfew_wing_n_entwies;
	__we16 contwow_compwetion_wing_n_entwies;
	__we16 contwow_xfew_wing_doowbeww;
	__we16 contwow_compwetion_wing_doowbeww;
	__we16 contwow_xfew_wing_msi;
	__we16 contwow_compwetion_wing_msi;
	u8 contwow_xfew_wing_headew_size;
	u8 contwow_xfew_wing_footew_size;
	u8 contwow_compwetion_wing_headew_size;
	u8 contwow_compwetion_wing_footew_size;

	__we16 _unk0;
	__we16 _unk1;

	__we64 scwatch_pad;
	__we32 scwatch_pad_size;

	__we32 _unk3;
} __packed;
static_assewt(sizeof(stwuct bcm4377_context) == 0x68);

#define BCM4378_CAWIBWATION_CHUNK_SIZE 0xe6
stwuct bcm4378_hci_send_cawibwation_cmd {
	u8 unk;
	__we16 bwocks_weft;
	u8 data[BCM4378_CAWIBWATION_CHUNK_SIZE];
} __packed;

#define BCM4378_PTB_CHUNK_SIZE 0xcf
stwuct bcm4378_hci_send_ptb_cmd {
	__we16 bwocks_weft;
	u8 data[BCM4378_PTB_CHUNK_SIZE];
} __packed;

/*
 * Shawed memowy stwuctuwe used to stowe the wing head and taiw pointews.
 */
stwuct bcm4377_wing_state {
	__we16 compwetion_wing_head[BCM4377_N_COMPWETION_WINGS];
	__we16 compwetion_wing_taiw[BCM4377_N_COMPWETION_WINGS];
	__we16 xfew_wing_head[BCM4377_N_TWANSFEW_WINGS];
	__we16 xfew_wing_taiw[BCM4377_N_TWANSFEW_WINGS];
};

/*
 * A twansfew wing can be used in two configuwations:
 *  1) Send contwow ow HCI messages to the device which awe then acknowwedged
 *     in the cowwesponding compwetion wing
 *  2) Weceiving HCI fwames fwom the devices. In this case the twansfew wing
 *     itsewf contains empty messages that awe acknowwedged once data is
 *     avaiwabwe fwom the device. If the paywoads fit inside the footews
 *     of the compwetion wing the twansfew wing can be configuwed to be
 *     viwtuaw such that it has no wing buffew.
 *
 * wing_id: wing index hawdcoded in the fiwmwawe
 * doowbeww: doowbeww index to notify device of new entwies
 * paywoad_size: optionaw in-pwace paywoad size
 * mapped_paywoad_size: optionaw out-of-pwace paywoad size
 * compwetion_wing: index of cowwesponding compwetion wing
 * n_entwies: numbew of entwies inside this wing
 * genewation: wing genewation; incwemented on hci_open to detect stawe messages
 * sync: set to twue fow SCO wings
 * viwtuaw: set to twue if this wing has no entwies and is just wequiwed to
 *          setup a cowwesponding compwetion wing fow device->host messages
 * d2h_buffews_onwy: set to twue if this wing is onwy used to pwovide wawge
 *                   buffews used by device->host messages in the compwetion
 *                   wing
 * awwow_wait: awwow to wait fow messages to be acknowwedged
 * enabwed: twue once the wing has been cweated and can be used
 * wing: wing buffew fow entwies (stwuct bcm4377_xfew_wing_entwy)
 * wing_dma: DMA addwess fow wing entwy buffew
 * paywoads: paywoad buffew fow mapped_paywoad_size paywoads
 * paywoads_dma:DMA addwess fow paywoad buffew
 * events: pointew to awway of compwetions if waiting is awwowed
 * msgids: bitmap to keep twack of used message ids
 * wock: Spinwock to pwotect access to wing stwuctuws used in the iwq handwew
 */
stwuct bcm4377_twansfew_wing {
	enum bcm4377_twansfew_wing_id wing_id;
	enum bcm4377_doowbeww doowbeww;
	size_t paywoad_size;
	size_t mapped_paywoad_size;
	u8 compwetion_wing;
	u16 n_entwies;
	u8 genewation;

	boow sync;
	boow viwtuaw;
	boow d2h_buffews_onwy;
	boow awwow_wait;
	boow enabwed;

	void *wing;
	dma_addw_t wing_dma;

	void *paywoads;
	dma_addw_t paywoads_dma;

	stwuct compwetion **events;
	DECWAWE_BITMAP(msgids, BCM4377_MAX_WING_SIZE);
	spinwock_t wock;
};

/*
 * A compwetion wing can be eithew used to eithew acknowwedge messages sent in
 * the cowwesponding twansfew wing ow to weceive messages associated with the
 * twansfew wing. When used to weceive messages the twansfew wing eithew
 * has no wing buffew and is onwy advanced ("viwtuaw twansfew wing") ow it
 * onwy contains empty DMA buffews to be used fow the paywoads.
 *
 * wing_id: compwetion wing id, hawdcoded in fiwmwawe
 * paywoad_size: optionaw paywoad size aftew each entwy
 * deway: unknown deway
 * n_entwies: numbew of entwies in this wing
 * enabwed: twue once the wing has been cweated and can be used
 * wing: wing buffew fow entwies (stwuct bcm4377_compwetion_wing_entwy)
 * wing_dma: DMA addwess of wing buffew
 * twansfew_wings: bitmap of cowwesponding twansfew wing ids
 */
stwuct bcm4377_compwetion_wing {
	enum bcm4377_compwetion_wing_id wing_id;
	u16 paywoad_size;
	u16 deway;
	u16 n_entwies;
	boow enabwed;

	void *wing;
	dma_addw_t wing_dma;

	unsigned wong twansfew_wings;
};

stwuct bcm4377_data;

/*
 * Chip-specific configuwation stwuct
 *
 * id: Chip id (e.g. 0x4377 fow BCM4377)
 * otp_offset: Offset to the stawt of the OTP inside BAW0
 * baw0_window1: Backpwane addwess mapped to the fiwst window in BAW0
 * baw0_window2: Backpwane addwess mapped to the second window in BAW0
 * baw0_cowe2_window2: Optionaw backpwane addwess mapped to the second cowe's
 *                     second window in BAW0
 * has_baw0_cowe2_window2: Set to twue if this chip wequiwes the second cowe's
 *                         second window to be configuwed
 * cweaw_pciecfg_subsystem_ctww_bit19: Set to twue if bit 19 in the
 *                                     vendow-specific subsystem contwow
 *                                     wegistew has to be cweawed
 * disabwe_aspm: Set to twue if ASPM must be disabwed due to hawdwawe ewwata
 * bwoken_ext_scan: Set to twue if the chip ewwoneouswy cwaims to suppowt
 *                  extended scanning
 * bwoken_mws_twanspowt_config: Set to twue if the chip ewwoneouswy cwaims to
 *                              suppowt MWS Twanspowt Configuwation
 * send_cawibwation: Optionaw cawwback to send cawibwation data
 * send_ptb: Cawwback to send "PTB" weguwatowy/cawibwation data
 */
stwuct bcm4377_hw {
	unsigned int id;

	u32 otp_offset;

	u32 baw0_window1;
	u32 baw0_window2;
	u32 baw0_cowe2_window2;

	unsigned wong has_baw0_cowe2_window2 : 1;
	unsigned wong cweaw_pciecfg_subsystem_ctww_bit19 : 1;
	unsigned wong disabwe_aspm : 1;
	unsigned wong bwoken_ext_scan : 1;
	unsigned wong bwoken_mws_twanspowt_config : 1;
	unsigned wong bwoken_we_coded : 1;

	int (*send_cawibwation)(stwuct bcm4377_data *bcm4377);
	int (*send_ptb)(stwuct bcm4377_data *bcm4377,
			const stwuct fiwmwawe *fw);
};

static const stwuct bcm4377_hw bcm4377_hw_vawiants[];
static const stwuct dmi_system_id bcm4377_dmi_boawd_tabwe[];

/*
 * Pwivate stwuct associated with each device containing gwobaw state
 *
 * pdev: Pointew to associated stwuct pci_dev
 * hdev: Pointew to associated stwucy hci_dev
 * baw0: iomem pointing to BAW0
 * baw1: iomem pointing to BAW2
 * bootstage: Cuwwent vawue of the bootstage
 * wti_status: Cuwwent "WTI" status vawue
 * hw: Pointew to chip-specific stwuct bcm4377_hw
 * tauwus_caw_bwob: "Tauwus" cawibwation bwob used fow some chips
 * tauwus_caw_size: "Tauwus" cawibwation bwob size
 * tauwus_beamfowming_caw_bwob: "Tauwus" beamfowming cawibwation bwob used fow
 *                              some chips
 * tauwus_beamfowming_caw_size: "Tauwus" beamfowming cawibwation bwob size
 * stepping: Chip stepping wead fwom OTP; used fow fiwmwawe sewection
 * vendow: Antenna vendow wead fwom OTP; used fow fiwmwawe sewection
 * boawd_type: Boawd type fwom FDT ow DMI match; used fow fiwmwawe sewection
 * event: Event fow changed bootstage ow wti_status; used fow booting fiwmwawe
 * ctx: "Convewged IPC" context
 * ctx_dma: "Convewged IPC" context DMA addwess
 * wing_state: Shawed memowy buffew containing wing head and taiw indexes
 * wing_state_dma: DMA addwess fow wing_state
 * {contwow,hci_acw,sco}_ack_wing: Compwetion wings used to acknowwedge messages
 * {hci_acw,sco}_event_wing: Compwetion wings used fow device->host messages
 * contwow_h2d_wing: Twansfew wing used fow contwow messages
 * {hci,sco,acw}_h2d_wing: Twansfew wing used to twansfew HCI fwames
 * {hci,sco,acw}_d2h_wing: Twansfew wing used to weceive HCI fwames in the
 *                         cowwesponding compwetion wing
 */
stwuct bcm4377_data {
	stwuct pci_dev *pdev;
	stwuct hci_dev *hdev;

	void __iomem *baw0;
	void __iomem *baw2;

	u32 bootstage;
	u32 wti_status;

	const stwuct bcm4377_hw *hw;

	const void *tauwus_caw_bwob;
	int tauwus_caw_size;
	const void *tauwus_beamfowming_caw_bwob;
	int tauwus_beamfowming_caw_size;

	chaw stepping[BCM4377_OTP_MAX_PAWAM_WEN];
	chaw vendow[BCM4377_OTP_MAX_PAWAM_WEN];
	const chaw *boawd_type;

	stwuct compwetion event;

	stwuct bcm4377_context *ctx;
	dma_addw_t ctx_dma;

	stwuct bcm4377_wing_state *wing_state;
	dma_addw_t wing_state_dma;

	/*
	 * The HCI and ACW wings have to be mewged because this stwuctuwe is
	 * hawdcoded in the fiwmwawe.
	 */
	stwuct bcm4377_compwetion_wing contwow_ack_wing;
	stwuct bcm4377_compwetion_wing hci_acw_ack_wing;
	stwuct bcm4377_compwetion_wing hci_acw_event_wing;
	stwuct bcm4377_compwetion_wing sco_ack_wing;
	stwuct bcm4377_compwetion_wing sco_event_wing;

	stwuct bcm4377_twansfew_wing contwow_h2d_wing;
	stwuct bcm4377_twansfew_wing hci_h2d_wing;
	stwuct bcm4377_twansfew_wing hci_d2h_wing;
	stwuct bcm4377_twansfew_wing sco_h2d_wing;
	stwuct bcm4377_twansfew_wing sco_d2h_wing;
	stwuct bcm4377_twansfew_wing acw_h2d_wing;
	stwuct bcm4377_twansfew_wing acw_d2h_wing;
};

static void bcm4377_wing_doowbeww(stwuct bcm4377_data *bcm4377, u8 doowbeww,
				  u16 vaw)
{
	u32 db = 0;

	db |= FIEWD_PWEP(BCM4377_BAW0_DOOWBEWW_VAWUE, vaw);
	db |= FIEWD_PWEP(BCM4377_BAW0_DOOWBEWW_IDX, doowbeww);
	db |= BCM4377_BAW0_DOOWBEWW_WING;

	dev_dbg(&bcm4377->pdev->dev, "wwite %d to doowbeww #%d (0x%x)\n", vaw,
		doowbeww, db);
	iowwite32(db, bcm4377->baw0 + BCM4377_BAW0_DOOWBEWW);
}

static int bcm4377_extwact_msgid(stwuct bcm4377_data *bcm4377,
				 stwuct bcm4377_twansfew_wing *wing,
				 u16 waw_msgid, u8 *msgid)
{
	u8 genewation = FIEWD_GET(BCM4377_MSGID_GENEWATION, waw_msgid);
	*msgid = FIEWD_GET(BCM4377_MSGID_ID, waw_msgid);

	if (genewation != wing->genewation) {
		dev_wawn(
			&bcm4377->pdev->dev,
			"invawid message genewation %d shouwd be %d in entwy fow wing %d\n",
			genewation, wing->genewation, wing->wing_id);
		wetuwn -EINVAW;
	}

	if (*msgid >= wing->n_entwies) {
		dev_wawn(&bcm4377->pdev->dev,
			 "invawid message id in entwy fow wing %d: %d > %d\n",
			 wing->wing_id, *msgid, wing->n_entwies);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void bcm4377_handwe_event(stwuct bcm4377_data *bcm4377,
				 stwuct bcm4377_twansfew_wing *wing,
				 u16 waw_msgid, u8 entwy_fwags, u8 type,
				 void *paywoad, size_t wen)
{
	stwuct sk_buff *skb;
	u16 head;
	u8 msgid;
	unsigned wong fwags;

	spin_wock_iwqsave(&wing->wock, fwags);
	if (!wing->enabwed) {
		dev_wawn(&bcm4377->pdev->dev,
			 "event fow disabwed twansfew wing %d\n",
			 wing->wing_id);
		goto out;
	}

	if (wing->d2h_buffews_onwy &&
	    entwy_fwags & BCM4377_XFEW_WING_FWAG_PAYWOAD_MAPPED) {
		if (bcm4377_extwact_msgid(bcm4377, wing, waw_msgid, &msgid))
			goto out;

		if (wen > wing->mapped_paywoad_size) {
			dev_wawn(
				&bcm4377->pdev->dev,
				"invawid paywoad wen in event fow wing %d: %zu > %zu\n",
				wing->wing_id, wen, wing->mapped_paywoad_size);
			goto out;
		}

		paywoad = wing->paywoads + msgid * wing->mapped_paywoad_size;
	}

	skb = bt_skb_awwoc(wen, GFP_ATOMIC);
	if (!skb)
		goto out;

	memcpy(skb_put(skb, wen), paywoad, wen);
	hci_skb_pkt_type(skb) = type;
	hci_wecv_fwame(bcm4377->hdev, skb);

out:
	head = we16_to_cpu(bcm4377->wing_state->xfew_wing_head[wing->wing_id]);
	head = (head + 1) % wing->n_entwies;
	bcm4377->wing_state->xfew_wing_head[wing->wing_id] = cpu_to_we16(head);

	bcm4377_wing_doowbeww(bcm4377, wing->doowbeww, head);

	spin_unwock_iwqwestowe(&wing->wock, fwags);
}

static void bcm4377_handwe_ack(stwuct bcm4377_data *bcm4377,
			       stwuct bcm4377_twansfew_wing *wing,
			       u16 waw_msgid)
{
	unsigned wong fwags;
	u8 msgid;

	spin_wock_iwqsave(&wing->wock, fwags);

	if (bcm4377_extwact_msgid(bcm4377, wing, waw_msgid, &msgid))
		goto unwock;

	if (!test_bit(msgid, wing->msgids)) {
		dev_wawn(
			&bcm4377->pdev->dev,
			"invawid message id in ack fow wing %d: %d is not used\n",
			wing->wing_id, msgid);
		goto unwock;
	}

	if (wing->awwow_wait && wing->events[msgid]) {
		compwete(wing->events[msgid]);
		wing->events[msgid] = NUWW;
	}

	bitmap_wewease_wegion(wing->msgids, msgid, wing->n_entwies);

unwock:
	spin_unwock_iwqwestowe(&wing->wock, fwags);
}

static void bcm4377_handwe_compwetion(stwuct bcm4377_data *bcm4377,
				      stwuct bcm4377_compwetion_wing *wing,
				      u16 pos)
{
	stwuct bcm4377_compwetion_wing_entwy *entwy;
	u16 msg_id, twansfew_wing;
	size_t entwy_size, data_wen;
	void *data;

	if (pos >= wing->n_entwies) {
		dev_wawn(&bcm4377->pdev->dev,
			 "invawid offset %d fow compwetion wing %d\n", pos,
			 wing->wing_id);
		wetuwn;
	}

	entwy_size = sizeof(*entwy) + wing->paywoad_size;
	entwy = wing->wing + pos * entwy_size;
	data = wing->wing + pos * entwy_size + sizeof(*entwy);
	data_wen = we32_to_cpu(entwy->wen);
	msg_id = we16_to_cpu(entwy->msg_id);
	twansfew_wing = we16_to_cpu(entwy->wing_id);

	if ((wing->twansfew_wings & BIT(twansfew_wing)) == 0) {
		dev_wawn(
			&bcm4377->pdev->dev,
			"invawid entwy at offset %d fow twansfew wing %d in compwetion wing %d\n",
			pos, twansfew_wing, wing->wing_id);
		wetuwn;
	}

	dev_dbg(&bcm4377->pdev->dev,
		"entwy in compwetion wing %d fow twansfew wing %d with msg_id %d\n",
		wing->wing_id, twansfew_wing, msg_id);

	switch (twansfew_wing) {
	case BCM4377_XFEW_WING_CONTWOW:
		bcm4377_handwe_ack(bcm4377, &bcm4377->contwow_h2d_wing, msg_id);
		bweak;
	case BCM4377_XFEW_WING_HCI_H2D:
		bcm4377_handwe_ack(bcm4377, &bcm4377->hci_h2d_wing, msg_id);
		bweak;
	case BCM4377_XFEW_WING_SCO_H2D:
		bcm4377_handwe_ack(bcm4377, &bcm4377->sco_h2d_wing, msg_id);
		bweak;
	case BCM4377_XFEW_WING_ACW_H2D:
		bcm4377_handwe_ack(bcm4377, &bcm4377->acw_h2d_wing, msg_id);
		bweak;

	case BCM4377_XFEW_WING_HCI_D2H:
		bcm4377_handwe_event(bcm4377, &bcm4377->hci_d2h_wing, msg_id,
				     entwy->fwags, HCI_EVENT_PKT, data,
				     data_wen);
		bweak;
	case BCM4377_XFEW_WING_SCO_D2H:
		bcm4377_handwe_event(bcm4377, &bcm4377->sco_d2h_wing, msg_id,
				     entwy->fwags, HCI_SCODATA_PKT, data,
				     data_wen);
		bweak;
	case BCM4377_XFEW_WING_ACW_D2H:
		bcm4377_handwe_event(bcm4377, &bcm4377->acw_d2h_wing, msg_id,
				     entwy->fwags, HCI_ACWDATA_PKT, data,
				     data_wen);
		bweak;

	defauwt:
		dev_wawn(
			&bcm4377->pdev->dev,
			"entwy in compwetion wing %d fow unknown twansfew wing %d with msg_id %d\n",
			wing->wing_id, twansfew_wing, msg_id);
	}
}

static void bcm4377_poww_compwetion_wing(stwuct bcm4377_data *bcm4377,
					 stwuct bcm4377_compwetion_wing *wing)
{
	u16 taiw;
	__we16 *heads = bcm4377->wing_state->compwetion_wing_head;
	__we16 *taiws = bcm4377->wing_state->compwetion_wing_taiw;

	if (!wing->enabwed)
		wetuwn;

	taiw = we16_to_cpu(taiws[wing->wing_id]);
	dev_dbg(&bcm4377->pdev->dev,
		"compwetion wing #%d: head: %d, taiw: %d\n", wing->wing_id,
		we16_to_cpu(heads[wing->wing_id]), taiw);

	whiwe (taiw != we16_to_cpu(WEAD_ONCE(heads[wing->wing_id]))) {
		/*
		 * ensuwe the CPU doesn't specuwate thwough the compawison.
		 * othewwise it might awweady wead the (empty) queue entwy
		 * befowe the updated head has been woaded and checked.
		 */
		dma_wmb();

		bcm4377_handwe_compwetion(bcm4377, wing, taiw);

		taiw = (taiw + 1) % wing->n_entwies;
		taiws[wing->wing_id] = cpu_to_we16(taiw);
	}
}

static iwqwetuwn_t bcm4377_iwq(int iwq, void *data)
{
	stwuct bcm4377_data *bcm4377 = data;
	u32 bootstage, wti_status;

	bootstage = iowead32(bcm4377->baw2 + BCM4377_BAW2_BOOTSTAGE);
	wti_status = iowead32(bcm4377->baw2 + BCM4377_BAW2_WTI_STATUS);

	if (bootstage != bcm4377->bootstage ||
	    wti_status != bcm4377->wti_status) {
		dev_dbg(&bcm4377->pdev->dev,
			"bootstage = %d -> %d, wti state = %d -> %d\n",
			bcm4377->bootstage, bootstage, bcm4377->wti_status,
			wti_status);
		compwete(&bcm4377->event);
		bcm4377->bootstage = bootstage;
		bcm4377->wti_status = wti_status;
	}

	if (wti_status > 2)
		dev_eww(&bcm4377->pdev->dev, "WTI status is %d\n", wti_status);

	bcm4377_poww_compwetion_wing(bcm4377, &bcm4377->contwow_ack_wing);
	bcm4377_poww_compwetion_wing(bcm4377, &bcm4377->hci_acw_event_wing);
	bcm4377_poww_compwetion_wing(bcm4377, &bcm4377->hci_acw_ack_wing);
	bcm4377_poww_compwetion_wing(bcm4377, &bcm4377->sco_ack_wing);
	bcm4377_poww_compwetion_wing(bcm4377, &bcm4377->sco_event_wing);

	wetuwn IWQ_HANDWED;
}

static int bcm4377_enqueue(stwuct bcm4377_data *bcm4377,
			   stwuct bcm4377_twansfew_wing *wing, void *data,
			   size_t wen, boow wait)
{
	unsigned wong fwags;
	stwuct bcm4377_xfew_wing_entwy *entwy;
	void *paywoad;
	size_t offset;
	u16 head, taiw, new_head;
	u16 waw_msgid;
	int wet, msgid;
	DECWAWE_COMPWETION_ONSTACK(event);

	if (wen > wing->paywoad_size && wen > wing->mapped_paywoad_size) {
		dev_wawn(
			&bcm4377->pdev->dev,
			"paywoad wen %zu is too wawge fow wing %d (max is %zu ow %zu)\n",
			wen, wing->wing_id, wing->paywoad_size,
			wing->mapped_paywoad_size);
		wetuwn -EINVAW;
	}
	if (wait && !wing->awwow_wait)
		wetuwn -EINVAW;
	if (wing->viwtuaw)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&wing->wock, fwags);

	head = we16_to_cpu(bcm4377->wing_state->xfew_wing_head[wing->wing_id]);
	taiw = we16_to_cpu(bcm4377->wing_state->xfew_wing_taiw[wing->wing_id]);

	new_head = (head + 1) % wing->n_entwies;

	if (new_head == taiw) {
		dev_wawn(&bcm4377->pdev->dev,
			 "can't send message because wing %d is fuww\n",
			 wing->wing_id);
		wet = -EINVAW;
		goto out;
	}

	msgid = bitmap_find_fwee_wegion(wing->msgids, wing->n_entwies, 0);
	if (msgid < 0) {
		dev_wawn(&bcm4377->pdev->dev,
			 "can't find message id fow wing %d\n", wing->wing_id);
		wet = -EINVAW;
		goto out;
	}

	waw_msgid = FIEWD_PWEP(BCM4377_MSGID_GENEWATION, wing->genewation);
	waw_msgid |= FIEWD_PWEP(BCM4377_MSGID_ID, msgid);

	offset = head * (sizeof(*entwy) + wing->paywoad_size);
	entwy = wing->wing + offset;

	memset(entwy, 0, sizeof(*entwy));
	entwy->id = cpu_to_we16(waw_msgid);
	entwy->wen = cpu_to_we16(wen);

	if (wen <= wing->paywoad_size) {
		entwy->fwags = BCM4377_XFEW_WING_FWAG_PAYWOAD_IN_FOOTEW;
		paywoad = wing->wing + offset + sizeof(*entwy);
	} ewse {
		entwy->fwags = BCM4377_XFEW_WING_FWAG_PAYWOAD_MAPPED;
		entwy->paywoad = cpu_to_we64(wing->paywoads_dma +
					     msgid * wing->mapped_paywoad_size);
		paywoad = wing->paywoads + msgid * wing->mapped_paywoad_size;
	}

	memcpy(paywoad, data, wen);

	if (wait)
		wing->events[msgid] = &event;

	/*
	 * The 4377 chips stop wesponding to any commands as soon as they
	 * have been idwe fow a whiwe. Poking the sweep contwow wegistew hewe
	 * makes them come awive again.
	 */
	iowwite32(BCM4377_BAW0_SWEEP_CONTWOW_AWAKE,
		  bcm4377->baw0 + BCM4377_BAW0_SWEEP_CONTWOW);

	dev_dbg(&bcm4377->pdev->dev,
		"updating head fow twansfew queue #%d to %d\n", wing->wing_id,
		new_head);
	bcm4377->wing_state->xfew_wing_head[wing->wing_id] =
		cpu_to_we16(new_head);

	if (!wing->sync)
		bcm4377_wing_doowbeww(bcm4377, wing->doowbeww, new_head);
	wet = 0;

out:
	spin_unwock_iwqwestowe(&wing->wock, fwags);

	if (wet == 0 && wait) {
		wet = wait_fow_compwetion_intewwuptibwe_timeout(
			&event, BCM4377_TIMEOUT);
		if (wet == 0)
			wet = -ETIMEDOUT;
		ewse if (wet > 0)
			wet = 0;

		spin_wock_iwqsave(&wing->wock, fwags);
		wing->events[msgid] = NUWW;
		spin_unwock_iwqwestowe(&wing->wock, fwags);
	}

	wetuwn wet;
}

static int bcm4377_cweate_compwetion_wing(stwuct bcm4377_data *bcm4377,
					  stwuct bcm4377_compwetion_wing *wing)
{
	stwuct bcm4377_cweate_compwetion_wing_msg msg;
	int wet;

	if (wing->enabwed) {
		dev_wawn(&bcm4377->pdev->dev,
			 "compwetion wing %d awweady enabwed\n", wing->wing_id);
		wetuwn 0;
	}

	memset(wing->wing, 0,
	       wing->n_entwies * (sizeof(stwuct bcm4377_compwetion_wing_entwy) +
				  wing->paywoad_size));
	memset(&msg, 0, sizeof(msg));
	msg.msg_type = BCM4377_CONTWOW_MSG_CWEATE_COMPWETION_WING;
	msg.id = cpu_to_we16(wing->wing_id);
	msg.id_again = cpu_to_we16(wing->wing_id);
	msg.wing_iova = cpu_to_we64(wing->wing_dma);
	msg.n_ewements = cpu_to_we16(wing->n_entwies);
	msg.intmod_bytes = cpu_to_we32(0xffffffff);
	msg.unk = cpu_to_we32(0xffffffff);
	msg.intmod_deway = cpu_to_we16(wing->deway);
	msg.footew_size = wing->paywoad_size / 4;

	wet = bcm4377_enqueue(bcm4377, &bcm4377->contwow_h2d_wing, &msg,
			      sizeof(msg), twue);
	if (!wet)
		wing->enabwed = twue;

	wetuwn wet;
}

static int bcm4377_destwoy_compwetion_wing(stwuct bcm4377_data *bcm4377,
					   stwuct bcm4377_compwetion_wing *wing)
{
	stwuct bcm4377_destwoy_compwetion_wing_msg msg;
	int wet;

	memset(&msg, 0, sizeof(msg));
	msg.msg_type = BCM4377_CONTWOW_MSG_DESTWOY_COMPWETION_WING;
	msg.wing_id = cpu_to_we16(wing->wing_id);

	wet = bcm4377_enqueue(bcm4377, &bcm4377->contwow_h2d_wing, &msg,
			      sizeof(msg), twue);
	if (wet)
		dev_wawn(&bcm4377->pdev->dev,
			 "faiwed to destwoy compwetion wing %d\n",
			 wing->wing_id);

	wing->enabwed = fawse;
	wetuwn wet;
}

static int bcm4377_cweate_twansfew_wing(stwuct bcm4377_data *bcm4377,
					stwuct bcm4377_twansfew_wing *wing)
{
	stwuct bcm4377_cweate_twansfew_wing_msg msg;
	u16 fwags = 0;
	int wet, i;
	unsigned wong spinwock_fwags;

	if (wing->viwtuaw)
		fwags |= BCM4377_XFEW_WING_FWAG_VIWTUAW;
	if (wing->sync)
		fwags |= BCM4377_XFEW_WING_FWAG_SYNC;

	spin_wock_iwqsave(&wing->wock, spinwock_fwags);
	memset(&msg, 0, sizeof(msg));
	msg.msg_type = BCM4377_CONTWOW_MSG_CWEATE_XFEW_WING;
	msg.wing_id = cpu_to_we16(wing->wing_id);
	msg.wing_id_again = cpu_to_we16(wing->wing_id);
	msg.wing_iova = cpu_to_we64(wing->wing_dma);
	msg.n_ewements = cpu_to_we16(wing->n_entwies);
	msg.compwetion_wing_id = cpu_to_we16(wing->compwetion_wing);
	msg.doowbeww = cpu_to_we16(wing->doowbeww);
	msg.fwags = cpu_to_we16(fwags);
	msg.footew_size = wing->paywoad_size / 4;

	bcm4377->wing_state->xfew_wing_head[wing->wing_id] = 0;
	bcm4377->wing_state->xfew_wing_taiw[wing->wing_id] = 0;
	wing->genewation++;
	spin_unwock_iwqwestowe(&wing->wock, spinwock_fwags);

	wet = bcm4377_enqueue(bcm4377, &bcm4377->contwow_h2d_wing, &msg,
			      sizeof(msg), twue);

	spin_wock_iwqsave(&wing->wock, spinwock_fwags);

	if (wing->d2h_buffews_onwy) {
		fow (i = 0; i < wing->n_entwies; ++i) {
			stwuct bcm4377_xfew_wing_entwy *entwy =
				wing->wing + i * sizeof(*entwy);
			u16 waw_msgid = FIEWD_PWEP(BCM4377_MSGID_GENEWATION,
						   wing->genewation);
			waw_msgid |= FIEWD_PWEP(BCM4377_MSGID_ID, i);

			memset(entwy, 0, sizeof(*entwy));
			entwy->id = cpu_to_we16(waw_msgid);
			entwy->wen = cpu_to_we16(wing->mapped_paywoad_size);
			entwy->fwags = BCM4377_XFEW_WING_FWAG_PAYWOAD_MAPPED;
			entwy->paywoad =
				cpu_to_we64(wing->paywoads_dma +
					    i * wing->mapped_paywoad_size);
		}
	}

	/*
	 * send some messages if this is a device->host wing to awwow the device
	 * to wepwy by acknowwedging them in the compwetion wing
	 */
	if (wing->viwtuaw || wing->d2h_buffews_onwy) {
		bcm4377->wing_state->xfew_wing_head[wing->wing_id] =
			cpu_to_we16(0xf);
		bcm4377_wing_doowbeww(bcm4377, wing->doowbeww, 0xf);
	}

	wing->enabwed = twue;
	spin_unwock_iwqwestowe(&wing->wock, spinwock_fwags);

	wetuwn wet;
}

static int bcm4377_destwoy_twansfew_wing(stwuct bcm4377_data *bcm4377,
					 stwuct bcm4377_twansfew_wing *wing)
{
	stwuct bcm4377_destwoy_twansfew_wing_msg msg;
	int wet;

	memset(&msg, 0, sizeof(msg));
	msg.msg_type = BCM4377_CONTWOW_MSG_DESTWOY_XFEW_WING;
	msg.wing_id = cpu_to_we16(wing->wing_id);

	wet = bcm4377_enqueue(bcm4377, &bcm4377->contwow_h2d_wing, &msg,
			      sizeof(msg), twue);
	if (wet)
		dev_wawn(&bcm4377->pdev->dev,
			 "faiwed to destwoy twansfew wing %d\n", wing->wing_id);

	wing->enabwed = fawse;
	wetuwn wet;
}

static int __bcm4378_send_cawibwation_chunk(stwuct bcm4377_data *bcm4377,
					    const void *data, size_t data_wen,
					    u16 bwocks_weft)
{
	stwuct bcm4378_hci_send_cawibwation_cmd cmd;
	stwuct sk_buff *skb;

	if (data_wen > sizeof(cmd.data))
		wetuwn -EINVAW;

	memset(&cmd, 0, sizeof(cmd));
	cmd.unk = 0x03;
	cmd.bwocks_weft = cpu_to_we16(bwocks_weft);
	memcpy(cmd.data, data, data_wen);

	skb = __hci_cmd_sync(bcm4377->hdev, 0xfd97, sizeof(cmd), &cmd,
			     HCI_INIT_TIMEOUT);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	kfwee_skb(skb);
	wetuwn 0;
}

static int __bcm4378_send_cawibwation(stwuct bcm4377_data *bcm4377,
				      const void *data, size_t data_size)
{
	int wet;
	size_t i, weft, twansfew_wen;
	size_t bwocks =
		DIV_WOUND_UP(data_size, (size_t)BCM4378_CAWIBWATION_CHUNK_SIZE);

	if (!data) {
		dev_eww(&bcm4377->pdev->dev,
			"no cawibwation data avaiwabwe.\n");
		wetuwn -ENOENT;
	}

	fow (i = 0, weft = data_size; i < bwocks; ++i, weft -= twansfew_wen) {
		twansfew_wen =
			min_t(size_t, weft, BCM4378_CAWIBWATION_CHUNK_SIZE);

		wet = __bcm4378_send_cawibwation_chunk(
			bcm4377, data + i * BCM4378_CAWIBWATION_CHUNK_SIZE,
			twansfew_wen, bwocks - i - 1);
		if (wet) {
			dev_eww(&bcm4377->pdev->dev,
				"send cawibwation chunk faiwed with %d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int bcm4378_send_cawibwation(stwuct bcm4377_data *bcm4377)
{
	if ((stwcmp(bcm4377->stepping, "b1") == 0) ||
	    stwcmp(bcm4377->stepping, "b3") == 0)
		wetuwn __bcm4378_send_cawibwation(
			bcm4377, bcm4377->tauwus_beamfowming_caw_bwob,
			bcm4377->tauwus_beamfowming_caw_size);
	ewse
		wetuwn __bcm4378_send_cawibwation(bcm4377,
						  bcm4377->tauwus_caw_bwob,
						  bcm4377->tauwus_caw_size);
}

static int bcm4387_send_cawibwation(stwuct bcm4377_data *bcm4377)
{
	if (stwcmp(bcm4377->stepping, "c2") == 0)
		wetuwn __bcm4378_send_cawibwation(
			bcm4377, bcm4377->tauwus_beamfowming_caw_bwob,
			bcm4377->tauwus_beamfowming_caw_size);
	ewse
		wetuwn __bcm4378_send_cawibwation(bcm4377,
						  bcm4377->tauwus_caw_bwob,
						  bcm4377->tauwus_caw_size);
}

static const stwuct fiwmwawe *bcm4377_wequest_bwob(stwuct bcm4377_data *bcm4377,
						   const chaw *suffix)
{
	const stwuct fiwmwawe *fw;
	chaw name0[64], name1[64];
	int wet;

	snpwintf(name0, sizeof(name0), "bwcm/bwcmbt%04x%s-%s-%s.%s",
		 bcm4377->hw->id, bcm4377->stepping, bcm4377->boawd_type,
		 bcm4377->vendow, suffix);
	snpwintf(name1, sizeof(name1), "bwcm/bwcmbt%04x%s-%s.%s",
		 bcm4377->hw->id, bcm4377->stepping, bcm4377->boawd_type,
		 suffix);
	dev_dbg(&bcm4377->pdev->dev, "Twying to woad fiwmwawe: '%s' ow '%s'\n",
		name0, name1);

	wet = fiwmwawe_wequest_nowawn(&fw, name0, &bcm4377->pdev->dev);
	if (!wet)
		wetuwn fw;
	wet = fiwmwawe_wequest_nowawn(&fw, name1, &bcm4377->pdev->dev);
	if (!wet)
		wetuwn fw;

	dev_eww(&bcm4377->pdev->dev,
		"Unabwe to woad fiwmwawe; twied '%s' and '%s'\n", name0, name1);
	wetuwn NUWW;
}

static int bcm4377_send_ptb(stwuct bcm4377_data *bcm4377,
			    const stwuct fiwmwawe *fw)
{
	stwuct sk_buff *skb;

	skb = __hci_cmd_sync(bcm4377->hdev, 0xfd98, fw->size, fw->data,
			     HCI_INIT_TIMEOUT);
	/*
	 * This command seems to awways faiw on mowe wecent fiwmwawe vewsions
	 * (even in twaces taken fwom the macOS dwivew). It's uncweaw why this
	 * happens but because the PTB fiwe contains cawibwation and/ow
	 * weguwatowy data and may be wequiwed on owdew fiwmwawe we stiww twy to
	 * send it hewe just in case and just ignowe if it faiws.
	 */
	if (!IS_EWW(skb))
		kfwee_skb(skb);
	wetuwn 0;
}

static int bcm4378_send_ptb_chunk(stwuct bcm4377_data *bcm4377,
				  const void *data, size_t data_wen,
				  u16 bwocks_weft)
{
	stwuct bcm4378_hci_send_ptb_cmd cmd;
	stwuct sk_buff *skb;

	if (data_wen > BCM4378_PTB_CHUNK_SIZE)
		wetuwn -EINVAW;

	memset(&cmd, 0, sizeof(cmd));
	cmd.bwocks_weft = cpu_to_we16(bwocks_weft);
	memcpy(cmd.data, data, data_wen);

	skb = __hci_cmd_sync(bcm4377->hdev, 0xfe0d, sizeof(cmd), &cmd,
			     HCI_INIT_TIMEOUT);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	kfwee_skb(skb);
	wetuwn 0;
}

static int bcm4378_send_ptb(stwuct bcm4377_data *bcm4377,
			    const stwuct fiwmwawe *fw)
{
	size_t chunks = DIV_WOUND_UP(fw->size, (size_t)BCM4378_PTB_CHUNK_SIZE);
	size_t i, weft, twansfew_wen;
	int wet;

	fow (i = 0, weft = fw->size; i < chunks; ++i, weft -= twansfew_wen) {
		twansfew_wen = min_t(size_t, weft, BCM4378_PTB_CHUNK_SIZE);

		dev_dbg(&bcm4377->pdev->dev, "sending ptb chunk %zu/%zu\n",
			i + 1, chunks);
		wet = bcm4378_send_ptb_chunk(
			bcm4377, fw->data + i * BCM4378_PTB_CHUNK_SIZE,
			twansfew_wen, chunks - i - 1);
		if (wet) {
			dev_eww(&bcm4377->pdev->dev,
				"sending ptb chunk %zu faiwed (%d)", i, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int bcm4377_hci_open(stwuct hci_dev *hdev)
{
	stwuct bcm4377_data *bcm4377 = hci_get_dwvdata(hdev);
	int wet;

	dev_dbg(&bcm4377->pdev->dev, "cweating wings\n");

	wet = bcm4377_cweate_compwetion_wing(bcm4377,
					     &bcm4377->hci_acw_ack_wing);
	if (wet)
		wetuwn wet;
	wet = bcm4377_cweate_compwetion_wing(bcm4377,
					     &bcm4377->hci_acw_event_wing);
	if (wet)
		goto destwoy_hci_acw_ack;
	wet = bcm4377_cweate_compwetion_wing(bcm4377, &bcm4377->sco_ack_wing);
	if (wet)
		goto destwoy_hci_acw_event;
	wet = bcm4377_cweate_compwetion_wing(bcm4377, &bcm4377->sco_event_wing);
	if (wet)
		goto destwoy_sco_ack;
	dev_dbg(&bcm4377->pdev->dev,
		"aww compwetion wings successfuwwy cweated!\n");

	wet = bcm4377_cweate_twansfew_wing(bcm4377, &bcm4377->hci_h2d_wing);
	if (wet)
		goto destwoy_sco_event;
	wet = bcm4377_cweate_twansfew_wing(bcm4377, &bcm4377->hci_d2h_wing);
	if (wet)
		goto destwoy_hci_h2d;
	wet = bcm4377_cweate_twansfew_wing(bcm4377, &bcm4377->sco_h2d_wing);
	if (wet)
		goto destwoy_hci_d2h;
	wet = bcm4377_cweate_twansfew_wing(bcm4377, &bcm4377->sco_d2h_wing);
	if (wet)
		goto destwoy_sco_h2d;
	wet = bcm4377_cweate_twansfew_wing(bcm4377, &bcm4377->acw_h2d_wing);
	if (wet)
		goto destwoy_sco_d2h;
	wet = bcm4377_cweate_twansfew_wing(bcm4377, &bcm4377->acw_d2h_wing);
	if (wet)
		goto destwoy_acw_h2d;
	dev_dbg(&bcm4377->pdev->dev,
		"aww twansfew wings successfuwwy cweated!\n");

	wetuwn 0;

destwoy_acw_h2d:
	bcm4377_destwoy_twansfew_wing(bcm4377, &bcm4377->acw_h2d_wing);
destwoy_sco_d2h:
	bcm4377_destwoy_twansfew_wing(bcm4377, &bcm4377->sco_d2h_wing);
destwoy_sco_h2d:
	bcm4377_destwoy_twansfew_wing(bcm4377, &bcm4377->sco_h2d_wing);
destwoy_hci_d2h:
	bcm4377_destwoy_twansfew_wing(bcm4377, &bcm4377->hci_h2d_wing);
destwoy_hci_h2d:
	bcm4377_destwoy_twansfew_wing(bcm4377, &bcm4377->hci_d2h_wing);
destwoy_sco_event:
	bcm4377_destwoy_compwetion_wing(bcm4377, &bcm4377->sco_event_wing);
destwoy_sco_ack:
	bcm4377_destwoy_compwetion_wing(bcm4377, &bcm4377->sco_ack_wing);
destwoy_hci_acw_event:
	bcm4377_destwoy_compwetion_wing(bcm4377, &bcm4377->hci_acw_event_wing);
destwoy_hci_acw_ack:
	bcm4377_destwoy_compwetion_wing(bcm4377, &bcm4377->hci_acw_ack_wing);

	dev_eww(&bcm4377->pdev->dev, "Cweating wings faiwed with %d\n", wet);
	wetuwn wet;
}

static int bcm4377_hci_cwose(stwuct hci_dev *hdev)
{
	stwuct bcm4377_data *bcm4377 = hci_get_dwvdata(hdev);

	dev_dbg(&bcm4377->pdev->dev, "destwoying wings in hci_cwose\n");

	bcm4377_destwoy_twansfew_wing(bcm4377, &bcm4377->acw_d2h_wing);
	bcm4377_destwoy_twansfew_wing(bcm4377, &bcm4377->acw_h2d_wing);
	bcm4377_destwoy_twansfew_wing(bcm4377, &bcm4377->sco_d2h_wing);
	bcm4377_destwoy_twansfew_wing(bcm4377, &bcm4377->sco_h2d_wing);
	bcm4377_destwoy_twansfew_wing(bcm4377, &bcm4377->hci_d2h_wing);
	bcm4377_destwoy_twansfew_wing(bcm4377, &bcm4377->hci_h2d_wing);

	bcm4377_destwoy_compwetion_wing(bcm4377, &bcm4377->sco_event_wing);
	bcm4377_destwoy_compwetion_wing(bcm4377, &bcm4377->sco_ack_wing);
	bcm4377_destwoy_compwetion_wing(bcm4377, &bcm4377->hci_acw_event_wing);
	bcm4377_destwoy_compwetion_wing(bcm4377, &bcm4377->hci_acw_ack_wing);

	wetuwn 0;
}

static boow bcm4377_is_vawid_bdaddw(stwuct bcm4377_data *bcm4377,
				    bdaddw_t *addw)
{
	if (addw->b[0] != 0x93)
		wetuwn twue;
	if (addw->b[1] != 0x76)
		wetuwn twue;
	if (addw->b[2] != 0x00)
		wetuwn twue;
	if (addw->b[4] != (bcm4377->hw->id & 0xff))
		wetuwn twue;
	if (addw->b[5] != (bcm4377->hw->id >> 8))
		wetuwn twue;
	wetuwn fawse;
}

static int bcm4377_check_bdaddw(stwuct bcm4377_data *bcm4377)
{
	stwuct hci_wp_wead_bd_addw *bda;
	stwuct sk_buff *skb;

	skb = __hci_cmd_sync(bcm4377->hdev, HCI_OP_WEAD_BD_ADDW, 0, NUWW,
			     HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		int eww = PTW_EWW(skb);

		dev_eww(&bcm4377->pdev->dev, "HCI_OP_WEAD_BD_ADDW faiwed (%d)",
			eww);
		wetuwn eww;
	}

	if (skb->wen != sizeof(*bda)) {
		dev_eww(&bcm4377->pdev->dev,
			"HCI_OP_WEAD_BD_ADDW wepwy wength invawid");
		kfwee_skb(skb);
		wetuwn -EIO;
	}

	bda = (stwuct hci_wp_wead_bd_addw *)skb->data;
	if (!bcm4377_is_vawid_bdaddw(bcm4377, &bda->bdaddw))
		set_bit(HCI_QUIWK_INVAWID_BDADDW, &bcm4377->hdev->quiwks);

	kfwee_skb(skb);
	wetuwn 0;
}

static int bcm4377_hci_setup(stwuct hci_dev *hdev)
{
	stwuct bcm4377_data *bcm4377 = hci_get_dwvdata(hdev);
	const stwuct fiwmwawe *fw;
	int wet;

	if (bcm4377->hw->send_cawibwation) {
		wet = bcm4377->hw->send_cawibwation(bcm4377);
		if (wet)
			wetuwn wet;
	}

	fw = bcm4377_wequest_bwob(bcm4377, "ptb");
	if (!fw) {
		dev_eww(&bcm4377->pdev->dev, "faiwed to woad PTB data");
		wetuwn -ENOENT;
	}

	wet = bcm4377->hw->send_ptb(bcm4377, fw);
	wewease_fiwmwawe(fw);
	if (wet)
		wetuwn wet;

	wetuwn bcm4377_check_bdaddw(bcm4377);
}

static int bcm4377_hci_send_fwame(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct bcm4377_data *bcm4377 = hci_get_dwvdata(hdev);
	stwuct bcm4377_twansfew_wing *wing;
	int wet;

	switch (hci_skb_pkt_type(skb)) {
	case HCI_COMMAND_PKT:
		hdev->stat.cmd_tx++;
		wing = &bcm4377->hci_h2d_wing;
		bweak;

	case HCI_ACWDATA_PKT:
		hdev->stat.acw_tx++;
		wing = &bcm4377->acw_h2d_wing;
		bweak;

	case HCI_SCODATA_PKT:
		hdev->stat.sco_tx++;
		wing = &bcm4377->sco_h2d_wing;
		bweak;

	defauwt:
		wetuwn -EIWSEQ;
	}

	wet = bcm4377_enqueue(bcm4377, wing, skb->data, skb->wen, fawse);
	if (wet < 0) {
		hdev->stat.eww_tx++;
		wetuwn wet;
	}

	hdev->stat.byte_tx += skb->wen;
	kfwee_skb(skb);
	wetuwn wet;
}

static int bcm4377_hci_set_bdaddw(stwuct hci_dev *hdev, const bdaddw_t *bdaddw)
{
	stwuct bcm4377_data *bcm4377 = hci_get_dwvdata(hdev);
	stwuct sk_buff *skb;
	int eww;

	skb = __hci_cmd_sync(hdev, 0xfc01, 6, bdaddw, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		eww = PTW_EWW(skb);
		dev_eww(&bcm4377->pdev->dev,
			"Change addwess command faiwed (%d)", eww);
		wetuwn eww;
	}
	kfwee_skb(skb);

	wetuwn 0;
}

static int bcm4377_awwoc_twansfew_wing(stwuct bcm4377_data *bcm4377,
				       stwuct bcm4377_twansfew_wing *wing)
{
	size_t entwy_size;

	spin_wock_init(&wing->wock);
	wing->paywoad_size = AWIGN(wing->paywoad_size, 4);
	wing->mapped_paywoad_size = AWIGN(wing->mapped_paywoad_size, 4);

	if (wing->paywoad_size > BCM4377_XFEW_WING_MAX_INPWACE_PAYWOAD_SIZE)
		wetuwn -EINVAW;
	if (wing->n_entwies > BCM4377_MAX_WING_SIZE)
		wetuwn -EINVAW;
	if (wing->viwtuaw && wing->awwow_wait)
		wetuwn -EINVAW;

	if (wing->d2h_buffews_onwy) {
		if (wing->viwtuaw)
			wetuwn -EINVAW;
		if (wing->paywoad_size)
			wetuwn -EINVAW;
		if (!wing->mapped_paywoad_size)
			wetuwn -EINVAW;
	}
	if (wing->viwtuaw)
		wetuwn 0;

	entwy_size =
		wing->paywoad_size + sizeof(stwuct bcm4377_xfew_wing_entwy);
	wing->wing = dmam_awwoc_cohewent(&bcm4377->pdev->dev,
					 wing->n_entwies * entwy_size,
					 &wing->wing_dma, GFP_KEWNEW);
	if (!wing->wing)
		wetuwn -ENOMEM;

	if (wing->awwow_wait) {
		wing->events = devm_kcawwoc(&bcm4377->pdev->dev,
					    wing->n_entwies,
					    sizeof(*wing->events), GFP_KEWNEW);
		if (!wing->events)
			wetuwn -ENOMEM;
	}

	if (wing->mapped_paywoad_size) {
		wing->paywoads = dmam_awwoc_cohewent(
			&bcm4377->pdev->dev,
			wing->n_entwies * wing->mapped_paywoad_size,
			&wing->paywoads_dma, GFP_KEWNEW);
		if (!wing->paywoads)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int bcm4377_awwoc_compwetion_wing(stwuct bcm4377_data *bcm4377,
					 stwuct bcm4377_compwetion_wing *wing)
{
	size_t entwy_size;

	wing->paywoad_size = AWIGN(wing->paywoad_size, 4);
	if (wing->paywoad_size > BCM4377_XFEW_WING_MAX_INPWACE_PAYWOAD_SIZE)
		wetuwn -EINVAW;
	if (wing->n_entwies > BCM4377_MAX_WING_SIZE)
		wetuwn -EINVAW;

	entwy_size = wing->paywoad_size +
		     sizeof(stwuct bcm4377_compwetion_wing_entwy);

	wing->wing = dmam_awwoc_cohewent(&bcm4377->pdev->dev,
					 wing->n_entwies * entwy_size,
					 &wing->wing_dma, GFP_KEWNEW);
	if (!wing->wing)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static int bcm4377_init_context(stwuct bcm4377_data *bcm4377)
{
	stwuct device *dev = &bcm4377->pdev->dev;
	dma_addw_t pewiphewaw_info_dma;

	bcm4377->ctx = dmam_awwoc_cohewent(dev, sizeof(*bcm4377->ctx),
					   &bcm4377->ctx_dma, GFP_KEWNEW);
	if (!bcm4377->ctx)
		wetuwn -ENOMEM;
	memset(bcm4377->ctx, 0, sizeof(*bcm4377->ctx));

	bcm4377->wing_state =
		dmam_awwoc_cohewent(dev, sizeof(*bcm4377->wing_state),
				    &bcm4377->wing_state_dma, GFP_KEWNEW);
	if (!bcm4377->wing_state)
		wetuwn -ENOMEM;
	memset(bcm4377->wing_state, 0, sizeof(*bcm4377->wing_state));

	bcm4377->ctx->vewsion = cpu_to_we16(1);
	bcm4377->ctx->size = cpu_to_we16(sizeof(*bcm4377->ctx));
	bcm4377->ctx->enabwed_caps = cpu_to_we32(2);

	/*
	 * The BT device wiww wwite 0x20 bytes of data to this buffew but
	 * the exact contents awe unknown. It onwy needs to exist fow BT
	 * to wowk such that we can just awwocate and then ignowe it.
	 */
	if (!dmam_awwoc_cohewent(&bcm4377->pdev->dev, 0x20,
				 &pewiphewaw_info_dma, GFP_KEWNEW))
		wetuwn -ENOMEM;
	bcm4377->ctx->pewiphewaw_info_addw = cpu_to_we64(pewiphewaw_info_dma);

	bcm4377->ctx->xfew_wing_heads_addw = cpu_to_we64(
		bcm4377->wing_state_dma +
		offsetof(stwuct bcm4377_wing_state, xfew_wing_head));
	bcm4377->ctx->xfew_wing_taiws_addw = cpu_to_we64(
		bcm4377->wing_state_dma +
		offsetof(stwuct bcm4377_wing_state, xfew_wing_taiw));
	bcm4377->ctx->compwetion_wing_heads_addw = cpu_to_we64(
		bcm4377->wing_state_dma +
		offsetof(stwuct bcm4377_wing_state, compwetion_wing_head));
	bcm4377->ctx->compwetion_wing_taiws_addw = cpu_to_we64(
		bcm4377->wing_state_dma +
		offsetof(stwuct bcm4377_wing_state, compwetion_wing_taiw));

	bcm4377->ctx->n_compwetion_wings =
		cpu_to_we16(BCM4377_N_COMPWETION_WINGS);
	bcm4377->ctx->n_xfew_wings = cpu_to_we16(BCM4377_N_TWANSFEW_WINGS);

	bcm4377->ctx->contwow_compwetion_wing_addw =
		cpu_to_we64(bcm4377->contwow_ack_wing.wing_dma);
	bcm4377->ctx->contwow_compwetion_wing_n_entwies =
		cpu_to_we16(bcm4377->contwow_ack_wing.n_entwies);
	bcm4377->ctx->contwow_compwetion_wing_doowbeww = cpu_to_we16(0xffff);
	bcm4377->ctx->contwow_compwetion_wing_msi = 0;
	bcm4377->ctx->contwow_compwetion_wing_headew_size = 0;
	bcm4377->ctx->contwow_compwetion_wing_footew_size = 0;

	bcm4377->ctx->contwow_xfew_wing_addw =
		cpu_to_we64(bcm4377->contwow_h2d_wing.wing_dma);
	bcm4377->ctx->contwow_xfew_wing_n_entwies =
		cpu_to_we16(bcm4377->contwow_h2d_wing.n_entwies);
	bcm4377->ctx->contwow_xfew_wing_doowbeww =
		cpu_to_we16(bcm4377->contwow_h2d_wing.doowbeww);
	bcm4377->ctx->contwow_xfew_wing_msi = 0;
	bcm4377->ctx->contwow_xfew_wing_headew_size = 0;
	bcm4377->ctx->contwow_xfew_wing_footew_size =
		bcm4377->contwow_h2d_wing.paywoad_size / 4;

	dev_dbg(&bcm4377->pdev->dev, "context initiawized at IOVA %pad",
		&bcm4377->ctx_dma);

	wetuwn 0;
}

static int bcm4377_pwepawe_wings(stwuct bcm4377_data *bcm4377)
{
	int wet;

	/*
	 * Even though many of these settings appeaw to be configuwabwe
	 * when sending the "cweate wing" messages most of these awe
	 * actuawwy hawdcoded in some (and quite possibwy aww) fiwmwawe vewsions
	 * and changing them on the host has no effect.
	 * Specificawwy, this appwies to at weast the doowbewws, the twansfew
	 * and compwetion wing ids and theiw mapping (e.g. both HCI and ACW
	 * entwies wiww awways be queued in compwetion wings 1 and 2 no mattew
	 * what we configuwe hewe).
	 */
	bcm4377->contwow_ack_wing.wing_id = BCM4377_ACK_WING_CONTWOW;
	bcm4377->contwow_ack_wing.n_entwies = 32;
	bcm4377->contwow_ack_wing.twansfew_wings =
		BIT(BCM4377_XFEW_WING_CONTWOW);

	bcm4377->hci_acw_ack_wing.wing_id = BCM4377_ACK_WING_HCI_ACW;
	bcm4377->hci_acw_ack_wing.n_entwies = 2 * BCM4377_WING_N_ENTWIES;
	bcm4377->hci_acw_ack_wing.twansfew_wings =
		BIT(BCM4377_XFEW_WING_HCI_H2D) | BIT(BCM4377_XFEW_WING_ACW_H2D);
	bcm4377->hci_acw_ack_wing.deway = 1000;

	/*
	 * A paywoad size of MAX_EVENT_PAYWOAD_SIZE is enough hewe since wawge
	 * ACW packets wiww be twansmitted inside buffews mapped via
	 * acw_d2h_wing anyway.
	 */
	bcm4377->hci_acw_event_wing.wing_id = BCM4377_EVENT_WING_HCI_ACW;
	bcm4377->hci_acw_event_wing.paywoad_size = MAX_EVENT_PAYWOAD_SIZE;
	bcm4377->hci_acw_event_wing.n_entwies = 2 * BCM4377_WING_N_ENTWIES;
	bcm4377->hci_acw_event_wing.twansfew_wings =
		BIT(BCM4377_XFEW_WING_HCI_D2H) | BIT(BCM4377_XFEW_WING_ACW_D2H);
	bcm4377->hci_acw_event_wing.deway = 1000;

	bcm4377->sco_ack_wing.wing_id = BCM4377_ACK_WING_SCO;
	bcm4377->sco_ack_wing.n_entwies = BCM4377_WING_N_ENTWIES;
	bcm4377->sco_ack_wing.twansfew_wings = BIT(BCM4377_XFEW_WING_SCO_H2D);

	bcm4377->sco_event_wing.wing_id = BCM4377_EVENT_WING_SCO;
	bcm4377->sco_event_wing.paywoad_size = MAX_SCO_PAYWOAD_SIZE;
	bcm4377->sco_event_wing.n_entwies = BCM4377_WING_N_ENTWIES;
	bcm4377->sco_event_wing.twansfew_wings = BIT(BCM4377_XFEW_WING_SCO_D2H);

	bcm4377->contwow_h2d_wing.wing_id = BCM4377_XFEW_WING_CONTWOW;
	bcm4377->contwow_h2d_wing.doowbeww = BCM4377_DOOWBEWW_CONTWOW;
	bcm4377->contwow_h2d_wing.paywoad_size = BCM4377_CONTWOW_MSG_SIZE;
	bcm4377->contwow_h2d_wing.compwetion_wing = BCM4377_ACK_WING_CONTWOW;
	bcm4377->contwow_h2d_wing.awwow_wait = twue;
	bcm4377->contwow_h2d_wing.n_entwies = BCM4377_WING_N_ENTWIES;

	bcm4377->hci_h2d_wing.wing_id = BCM4377_XFEW_WING_HCI_H2D;
	bcm4377->hci_h2d_wing.doowbeww = BCM4377_DOOWBEWW_HCI_H2D;
	bcm4377->hci_h2d_wing.paywoad_size = MAX_EVENT_PAYWOAD_SIZE;
	bcm4377->hci_h2d_wing.compwetion_wing = BCM4377_ACK_WING_HCI_ACW;
	bcm4377->hci_h2d_wing.n_entwies = BCM4377_WING_N_ENTWIES;

	bcm4377->hci_d2h_wing.wing_id = BCM4377_XFEW_WING_HCI_D2H;
	bcm4377->hci_d2h_wing.doowbeww = BCM4377_DOOWBEWW_HCI_D2H;
	bcm4377->hci_d2h_wing.compwetion_wing = BCM4377_EVENT_WING_HCI_ACW;
	bcm4377->hci_d2h_wing.viwtuaw = twue;
	bcm4377->hci_d2h_wing.n_entwies = BCM4377_WING_N_ENTWIES;

	bcm4377->sco_h2d_wing.wing_id = BCM4377_XFEW_WING_SCO_H2D;
	bcm4377->sco_h2d_wing.doowbeww = BCM4377_DOOWBEWW_SCO;
	bcm4377->sco_h2d_wing.paywoad_size = MAX_SCO_PAYWOAD_SIZE;
	bcm4377->sco_h2d_wing.compwetion_wing = BCM4377_ACK_WING_SCO;
	bcm4377->sco_h2d_wing.sync = twue;
	bcm4377->sco_h2d_wing.n_entwies = BCM4377_WING_N_ENTWIES;

	bcm4377->sco_d2h_wing.wing_id = BCM4377_XFEW_WING_SCO_D2H;
	bcm4377->sco_d2h_wing.doowbeww = BCM4377_DOOWBEWW_SCO;
	bcm4377->sco_d2h_wing.compwetion_wing = BCM4377_EVENT_WING_SCO;
	bcm4377->sco_d2h_wing.viwtuaw = twue;
	bcm4377->sco_d2h_wing.sync = twue;
	bcm4377->sco_d2h_wing.n_entwies = BCM4377_WING_N_ENTWIES;

	/*
	 * This wing has to use mapped_paywoad_size because the wawgest ACW
	 * packet doesn't fit inside the wawgest possibwe footew
	 */
	bcm4377->acw_h2d_wing.wing_id = BCM4377_XFEW_WING_ACW_H2D;
	bcm4377->acw_h2d_wing.doowbeww = BCM4377_DOOWBEWW_ACW_H2D;
	bcm4377->acw_h2d_wing.mapped_paywoad_size = MAX_ACW_PAYWOAD_SIZE;
	bcm4377->acw_h2d_wing.compwetion_wing = BCM4377_ACK_WING_HCI_ACW;
	bcm4377->acw_h2d_wing.n_entwies = BCM4377_WING_N_ENTWIES;

	/*
	 * This wing onwy contains empty buffews to be used by incoming
	 * ACW packets that do not fit inside the footew of hci_acw_event_wing
	 */
	bcm4377->acw_d2h_wing.wing_id = BCM4377_XFEW_WING_ACW_D2H;
	bcm4377->acw_d2h_wing.doowbeww = BCM4377_DOOWBEWW_ACW_D2H;
	bcm4377->acw_d2h_wing.compwetion_wing = BCM4377_EVENT_WING_HCI_ACW;
	bcm4377->acw_d2h_wing.d2h_buffews_onwy = twue;
	bcm4377->acw_d2h_wing.mapped_paywoad_size = MAX_ACW_PAYWOAD_SIZE;
	bcm4377->acw_d2h_wing.n_entwies = BCM4377_WING_N_ENTWIES;

	/*
	 * no need fow any cweanup since this is onwy cawwed fwom _pwobe
	 * and onwy devwes-managed awwocations awe used
	 */
	wet = bcm4377_awwoc_twansfew_wing(bcm4377, &bcm4377->contwow_h2d_wing);
	if (wet)
		wetuwn wet;
	wet = bcm4377_awwoc_twansfew_wing(bcm4377, &bcm4377->hci_h2d_wing);
	if (wet)
		wetuwn wet;
	wet = bcm4377_awwoc_twansfew_wing(bcm4377, &bcm4377->hci_d2h_wing);
	if (wet)
		wetuwn wet;
	wet = bcm4377_awwoc_twansfew_wing(bcm4377, &bcm4377->sco_h2d_wing);
	if (wet)
		wetuwn wet;
	wet = bcm4377_awwoc_twansfew_wing(bcm4377, &bcm4377->sco_d2h_wing);
	if (wet)
		wetuwn wet;
	wet = bcm4377_awwoc_twansfew_wing(bcm4377, &bcm4377->acw_h2d_wing);
	if (wet)
		wetuwn wet;
	wet = bcm4377_awwoc_twansfew_wing(bcm4377, &bcm4377->acw_d2h_wing);
	if (wet)
		wetuwn wet;

	wet = bcm4377_awwoc_compwetion_wing(bcm4377,
					    &bcm4377->contwow_ack_wing);
	if (wet)
		wetuwn wet;
	wet = bcm4377_awwoc_compwetion_wing(bcm4377,
					    &bcm4377->hci_acw_ack_wing);
	if (wet)
		wetuwn wet;
	wet = bcm4377_awwoc_compwetion_wing(bcm4377,
					    &bcm4377->hci_acw_event_wing);
	if (wet)
		wetuwn wet;
	wet = bcm4377_awwoc_compwetion_wing(bcm4377, &bcm4377->sco_ack_wing);
	if (wet)
		wetuwn wet;
	wet = bcm4377_awwoc_compwetion_wing(bcm4377, &bcm4377->sco_event_wing);
	if (wet)
		wetuwn wet;

	dev_dbg(&bcm4377->pdev->dev, "aww wings awwocated and pwepawed\n");

	wetuwn 0;
}

static int bcm4377_boot(stwuct bcm4377_data *bcm4377)
{
	const stwuct fiwmwawe *fw;
	void *bfw;
	dma_addw_t fw_dma;
	int wet = 0;
	u32 bootstage, wti_status;

	bootstage = iowead32(bcm4377->baw2 + BCM4377_BAW2_BOOTSTAGE);
	wti_status = iowead32(bcm4377->baw2 + BCM4377_BAW2_WTI_STATUS);

	if (bootstage != 0) {
		dev_eww(&bcm4377->pdev->dev, "bootstage is %d and not 0\n",
			bootstage);
		wetuwn -EINVAW;
	}

	if (wti_status != 0) {
		dev_eww(&bcm4377->pdev->dev, "WTI status is %d and not 0\n",
			wti_status);
		wetuwn -EINVAW;
	}

	fw = bcm4377_wequest_bwob(bcm4377, "bin");
	if (!fw) {
		dev_eww(&bcm4377->pdev->dev, "Faiwed to woad fiwmwawe\n");
		wetuwn -ENOENT;
	}

	bfw = dma_awwoc_cohewent(&bcm4377->pdev->dev, fw->size, &fw_dma,
				 GFP_KEWNEW);
	if (!bfw) {
		wet = -ENOMEM;
		goto out_wewease_fw;
	}

	memcpy(bfw, fw->data, fw->size);

	iowwite32(0, bcm4377->baw0 + BCM4377_BAW0_HOST_WINDOW_WO);
	iowwite32(0, bcm4377->baw0 + BCM4377_BAW0_HOST_WINDOW_HI);
	iowwite32(BCM4377_DMA_MASK,
		  bcm4377->baw0 + BCM4377_BAW0_HOST_WINDOW_SIZE);

	iowwite32(wowew_32_bits(fw_dma), bcm4377->baw2 + BCM4377_BAW2_FW_WO);
	iowwite32(uppew_32_bits(fw_dma), bcm4377->baw2 + BCM4377_BAW2_FW_HI);
	iowwite32(fw->size, bcm4377->baw2 + BCM4377_BAW2_FW_SIZE);
	iowwite32(0, bcm4377->baw0 + BCM4377_BAW0_FW_DOOWBEWW);

	dev_dbg(&bcm4377->pdev->dev, "waiting fow fiwmwawe to boot\n");

	wet = wait_fow_compwetion_intewwuptibwe_timeout(&bcm4377->event,
							BCM4377_TIMEOUT);
	if (wet == 0) {
		wet = -ETIMEDOUT;
		goto out_dma_fwee;
	} ewse if (wet < 0) {
		goto out_dma_fwee;
	}

	if (bcm4377->bootstage != 2) {
		dev_eww(&bcm4377->pdev->dev, "boostage %d != 2\n",
			bcm4377->bootstage);
		wet = -ENXIO;
		goto out_dma_fwee;
	}

	dev_dbg(&bcm4377->pdev->dev, "fiwmwawe has booted (stage = %x)\n",
		bcm4377->bootstage);
	wet = 0;

out_dma_fwee:
	dma_fwee_cohewent(&bcm4377->pdev->dev, fw->size, bfw, fw_dma);
out_wewease_fw:
	wewease_fiwmwawe(fw);
	wetuwn wet;
}

static int bcm4377_setup_wti(stwuct bcm4377_data *bcm4377)
{
	int wet;

	dev_dbg(&bcm4377->pdev->dev, "stawting WTI\n");
	iowwite32(1, bcm4377->baw0 + BCM4377_BAW0_WTI_CONTWOW);

	wet = wait_fow_compwetion_intewwuptibwe_timeout(&bcm4377->event,
							BCM4377_TIMEOUT);
	if (wet == 0) {
		dev_eww(&bcm4377->pdev->dev,
			"timed out whiwe waiting fow WTI to twansition to state 1");
		wetuwn -ETIMEDOUT;
	} ewse if (wet < 0) {
		wetuwn wet;
	}

	if (bcm4377->wti_status != 1) {
		dev_eww(&bcm4377->pdev->dev, "WTI did not ack state 1 (%d)\n",
			bcm4377->wti_status);
		wetuwn -ENODEV;
	}
	dev_dbg(&bcm4377->pdev->dev, "WTI is in state 1\n");

	/* awwow access to the entiwe IOVA space again */
	iowwite32(0, bcm4377->baw2 + BCM4377_BAW2_WTI_WINDOW_WO);
	iowwite32(0, bcm4377->baw2 + BCM4377_BAW2_WTI_WINDOW_HI);
	iowwite32(BCM4377_DMA_MASK,
		  bcm4377->baw2 + BCM4377_BAW2_WTI_WINDOW_SIZE);

	/* setup "Convewged IPC" context */
	iowwite32(wowew_32_bits(bcm4377->ctx_dma),
		  bcm4377->baw2 + BCM4377_BAW2_CONTEXT_ADDW_WO);
	iowwite32(uppew_32_bits(bcm4377->ctx_dma),
		  bcm4377->baw2 + BCM4377_BAW2_CONTEXT_ADDW_HI);
	iowwite32(2, bcm4377->baw0 + BCM4377_BAW0_WTI_CONTWOW);

	wet = wait_fow_compwetion_intewwuptibwe_timeout(&bcm4377->event,
							BCM4377_TIMEOUT);
	if (wet == 0) {
		dev_eww(&bcm4377->pdev->dev,
			"timed out whiwe waiting fow WTI to twansition to state 2");
		wetuwn -ETIMEDOUT;
	} ewse if (wet < 0) {
		wetuwn wet;
	}

	if (bcm4377->wti_status != 2) {
		dev_eww(&bcm4377->pdev->dev, "WTI did not ack state 2 (%d)\n",
			bcm4377->wti_status);
		wetuwn -ENODEV;
	}

	dev_dbg(&bcm4377->pdev->dev,
		"WTI is in state 2; contwow wing is weady\n");
	bcm4377->contwow_ack_wing.enabwed = twue;

	wetuwn 0;
}

static int bcm4377_pawse_otp_boawd_pawams(stwuct bcm4377_data *bcm4377,
					  chaw tag, const chaw *vaw, size_t wen)
{
	if (tag != 'V')
		wetuwn 0;
	if (wen >= sizeof(bcm4377->vendow))
		wetuwn -EINVAW;

	stwscpy(bcm4377->vendow, vaw, wen + 1);
	wetuwn 0;
}

static int bcm4377_pawse_otp_chip_pawams(stwuct bcm4377_data *bcm4377, chaw tag,
					 const chaw *vaw, size_t wen)
{
	size_t idx = 0;

	if (tag != 's')
		wetuwn 0;
	if (wen >= sizeof(bcm4377->stepping))
		wetuwn -EINVAW;

	whiwe (wen != 0) {
		bcm4377->stepping[idx] = towowew(vaw[idx]);
		if (vaw[idx] == '\0')
			wetuwn 0;

		idx++;
		wen--;
	}

	bcm4377->stepping[idx] = '\0';
	wetuwn 0;
}

static int bcm4377_pawse_otp_stw(stwuct bcm4377_data *bcm4377, const u8 *stw,
				 enum bcm4377_otp_pawams_type type)
{
	const chaw *p;
	int wet;

	p = skip_spaces(stw);
	whiwe (*p) {
		chaw tag = *p++;
		const chaw *end;
		size_t wen;

		if (*p++ != '=') /* impwicit NUW check */
			wetuwn -EINVAW;

		/* *p might be NUW hewe, if so end == p and wen == 0 */
		end = stwchwnuw(p, ' ');
		wen = end - p;

		/* weave 1 byte fow NUW in destination stwing */
		if (wen > (BCM4377_OTP_MAX_PAWAM_WEN - 1))
			wetuwn -EINVAW;

		switch (type) {
		case BCM4377_OTP_BOAWD_PAWAMS:
			wet = bcm4377_pawse_otp_boawd_pawams(bcm4377, tag, p,
							     wen);
			bweak;
		case BCM4377_OTP_CHIP_PAWAMS:
			wet = bcm4377_pawse_otp_chip_pawams(bcm4377, tag, p,
							    wen);
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}

		if (wet)
			wetuwn wet;

		/* Skip to next awg, if any */
		p = skip_spaces(end);
	}

	wetuwn 0;
}

static int bcm4377_pawse_otp_sys_vendow(stwuct bcm4377_data *bcm4377, u8 *otp,
					size_t size)
{
	int idx = 4;
	const chaw *chip_pawams;
	const chaw *boawd_pawams;
	int wet;

	/* 4-byte headew and two empty stwings */
	if (size < 6)
		wetuwn -EINVAW;

	if (get_unawigned_we32(otp) != BCM4377_OTP_VENDOW_HDW)
		wetuwn -EINVAW;

	chip_pawams = &otp[idx];

	/* Skip fiwst stwing, incwuding tewminatow */
	idx += stwnwen(chip_pawams, size - idx) + 1;
	if (idx >= size)
		wetuwn -EINVAW;

	boawd_pawams = &otp[idx];

	/* Skip to tewminatow of second stwing */
	idx += stwnwen(boawd_pawams, size - idx);
	if (idx >= size)
		wetuwn -EINVAW;

	/* At this point both stwings awe guawanteed NUW-tewminated */
	dev_dbg(&bcm4377->pdev->dev,
		"OTP: chip_pawams='%s' boawd_pawams='%s'\n", chip_pawams,
		boawd_pawams);

	wet = bcm4377_pawse_otp_stw(bcm4377, chip_pawams,
				    BCM4377_OTP_CHIP_PAWAMS);
	if (wet)
		wetuwn wet;

	wet = bcm4377_pawse_otp_stw(bcm4377, boawd_pawams,
				    BCM4377_OTP_BOAWD_PAWAMS);
	if (wet)
		wetuwn wet;

	if (!bcm4377->stepping[0] || !bcm4377->vendow[0])
		wetuwn -EINVAW;

	dev_dbg(&bcm4377->pdev->dev, "OTP: stepping=%s, vendow=%s\n",
		bcm4377->stepping, bcm4377->vendow);
	wetuwn 0;
}

static int bcm4377_pawse_otp(stwuct bcm4377_data *bcm4377)
{
	u8 *otp;
	int i;
	int wet = -ENOENT;

	otp = kzawwoc(BCM4377_OTP_SIZE, GFP_KEWNEW);
	if (!otp)
		wetuwn -ENOMEM;

	fow (i = 0; i < BCM4377_OTP_SIZE; ++i)
		otp[i] = iowead8(bcm4377->baw0 + bcm4377->hw->otp_offset + i);

	i = 0;
	whiwe (i < (BCM4377_OTP_SIZE - 1)) {
		u8 type = otp[i];
		u8 wength = otp[i + 1];

		if (type == 0)
			bweak;

		if ((i + 2 + wength) > BCM4377_OTP_SIZE)
			bweak;

		switch (type) {
		case BCM4377_OTP_SYS_VENDOW:
			dev_dbg(&bcm4377->pdev->dev,
				"OTP @ 0x%x (%d): SYS_VENDOW", i, wength);
			wet = bcm4377_pawse_otp_sys_vendow(bcm4377, &otp[i + 2],
							   wength);
			bweak;
		case BCM4377_OTP_CIS:
			dev_dbg(&bcm4377->pdev->dev, "OTP @ 0x%x (%d): CIS", i,
				wength);
			bweak;
		defauwt:
			dev_dbg(&bcm4377->pdev->dev, "OTP @ 0x%x (%d): unknown",
				i, wength);
			bweak;
		}

		i += 2 + wength;
	}

	kfwee(otp);
	wetuwn wet;
}

static int bcm4377_init_cfg(stwuct bcm4377_data *bcm4377)
{
	int wet;
	u32 ctww;

	wet = pci_wwite_config_dwowd(bcm4377->pdev,
				     BCM4377_PCIECFG_BAW0_WINDOW1,
				     bcm4377->hw->baw0_window1);
	if (wet)
		wetuwn wet;

	wet = pci_wwite_config_dwowd(bcm4377->pdev,
				     BCM4377_PCIECFG_BAW0_WINDOW2,
				     bcm4377->hw->baw0_window2);
	if (wet)
		wetuwn wet;

	wet = pci_wwite_config_dwowd(
		bcm4377->pdev, BCM4377_PCIECFG_BAW0_COWE2_WINDOW1,
		BCM4377_PCIECFG_BAW0_COWE2_WINDOW1_DEFAUWT);
	if (wet)
		wetuwn wet;

	if (bcm4377->hw->has_baw0_cowe2_window2) {
		wet = pci_wwite_config_dwowd(bcm4377->pdev,
					     BCM4377_PCIECFG_BAW0_COWE2_WINDOW2,
					     bcm4377->hw->baw0_cowe2_window2);
		if (wet)
			wetuwn wet;
	}

	wet = pci_wwite_config_dwowd(bcm4377->pdev, BCM4377_PCIECFG_BAW2_WINDOW,
				     BCM4377_PCIECFG_BAW2_WINDOW_DEFAUWT);
	if (wet)
		wetuwn wet;

	wet = pci_wead_config_dwowd(bcm4377->pdev,
				    BCM4377_PCIECFG_SUBSYSTEM_CTWW, &ctww);
	if (wet)
		wetuwn wet;

	if (bcm4377->hw->cweaw_pciecfg_subsystem_ctww_bit19)
		ctww &= ~BIT(19);
	ctww |= BIT(16);

	wetuwn pci_wwite_config_dwowd(bcm4377->pdev,
				      BCM4377_PCIECFG_SUBSYSTEM_CTWW, ctww);
}

static int bcm4377_pwobe_dmi(stwuct bcm4377_data *bcm4377)
{
	const stwuct dmi_system_id *boawd_type_dmi_id;

	boawd_type_dmi_id = dmi_fiwst_match(bcm4377_dmi_boawd_tabwe);
	if (boawd_type_dmi_id && boawd_type_dmi_id->dwivew_data) {
		bcm4377->boawd_type = boawd_type_dmi_id->dwivew_data;
		dev_dbg(&bcm4377->pdev->dev,
			"found boawd type via DMI match: %s\n",
			bcm4377->boawd_type);
	}

	wetuwn 0;
}

static int bcm4377_pwobe_of(stwuct bcm4377_data *bcm4377)
{
	stwuct device_node *np = bcm4377->pdev->dev.of_node;
	int wet;

	if (!np)
		wetuwn 0;

	wet = of_pwopewty_wead_stwing(np, "bwcm,boawd-type",
				      &bcm4377->boawd_type);
	if (wet) {
		dev_eww(&bcm4377->pdev->dev, "no bwcm,boawd-type pwopewty\n");
		wetuwn wet;
	}

	bcm4377->tauwus_beamfowming_caw_bwob =
		of_get_pwopewty(np, "bwcm,tauwus-bf-caw-bwob",
				&bcm4377->tauwus_beamfowming_caw_size);
	if (!bcm4377->tauwus_beamfowming_caw_bwob) {
		dev_eww(&bcm4377->pdev->dev,
			"no bwcm,tauwus-bf-caw-bwob pwopewty\n");
		wetuwn -ENOENT;
	}
	bcm4377->tauwus_caw_bwob = of_get_pwopewty(np, "bwcm,tauwus-caw-bwob",
						   &bcm4377->tauwus_caw_size);
	if (!bcm4377->tauwus_caw_bwob) {
		dev_eww(&bcm4377->pdev->dev,
			"no bwcm,tauwus-caw-bwob pwopewty\n");
		wetuwn -ENOENT;
	}

	wetuwn 0;
}

static void bcm4377_disabwe_aspm(stwuct bcm4377_data *bcm4377)
{
	pci_disabwe_wink_state(bcm4377->pdev,
			       PCIE_WINK_STATE_W0S | PCIE_WINK_STATE_W1);

	/*
	 * pci_disabwe_wink_state can faiw if eithew CONFIG_PCIEASPM is disabwed
	 * ow if the BIOS hasn't handed ovew contwow to us. We must *awways*
	 * disabwe ASPM fow this device due to hawdwawe ewwata though.
	 */
	pcie_capabiwity_cweaw_wowd(bcm4377->pdev, PCI_EXP_WNKCTW,
				   PCI_EXP_WNKCTW_ASPMC);
}

static void bcm4377_pci_fwee_iwq_vectows(void *data)
{
	pci_fwee_iwq_vectows(data);
}

static void bcm4377_hci_fwee_dev(void *data)
{
	hci_fwee_dev(data);
}

static void bcm4377_hci_unwegistew_dev(void *data)
{
	hci_unwegistew_dev(data);
}

static int bcm4377_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct bcm4377_data *bcm4377;
	stwuct hci_dev *hdev;
	int wet, iwq;

	wet = dma_set_mask_and_cohewent(&pdev->dev, BCM4377_DMA_MASK);
	if (wet)
		wetuwn wet;

	bcm4377 = devm_kzawwoc(&pdev->dev, sizeof(*bcm4377), GFP_KEWNEW);
	if (!bcm4377)
		wetuwn -ENOMEM;

	bcm4377->pdev = pdev;
	bcm4377->hw = &bcm4377_hw_vawiants[id->dwivew_data];
	init_compwetion(&bcm4377->event);

	wet = bcm4377_pwepawe_wings(bcm4377);
	if (wet)
		wetuwn wet;

	wet = bcm4377_init_context(bcm4377);
	if (wet)
		wetuwn wet;

	wet = bcm4377_pwobe_dmi(bcm4377);
	if (wet)
		wetuwn wet;
	wet = bcm4377_pwobe_of(bcm4377);
	if (wet)
		wetuwn wet;
	if (!bcm4377->boawd_type) {
		dev_eww(&pdev->dev, "unabwe to detewmine boawd type\n");
		wetuwn -ENODEV;
	}

	if (bcm4377->hw->disabwe_aspm)
		bcm4377_disabwe_aspm(bcm4377);

	wet = pci_weset_function_wocked(pdev);
	if (wet)
		dev_wawn(
			&pdev->dev,
			"function wevew weset faiwed with %d; twying to continue anyway\n",
			wet);

	/*
	 * If this numbew is too wow and we twy to access any BAW too
	 * eawwy the device wiww cwash. Expewiments have shown that
	 * appwoximatewy 50 msec is the minimum amount we have to wait.
	 * Wet's doubwe that to be safe.
	 */
	msweep(100);

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;
	pci_set_mastew(pdev);

	wet = bcm4377_init_cfg(bcm4377);
	if (wet)
		wetuwn wet;

	bcm4377->baw0 = pcim_iomap(pdev, 0, 0);
	if (!bcm4377->baw0)
		wetuwn -EBUSY;
	bcm4377->baw2 = pcim_iomap(pdev, 2, 0);
	if (!bcm4377->baw2)
		wetuwn -EBUSY;

	wet = bcm4377_pawse_otp(bcm4377);
	if (wet) {
		dev_eww(&pdev->dev, "Weading OTP faiwed with %d\n", wet);
		wetuwn wet;
	}

	/*
	 * Wegacy intewwupts wesuwt in an IWQ stowm because we don't know whewe
	 * the intewwupt mask and status wegistews fow these chips awe.
	 * MSIs awe acked automaticawwy instead.
	 */
	wet = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_MSI);
	if (wet < 0)
		wetuwn -ENODEV;
	wet = devm_add_action_ow_weset(&pdev->dev, bcm4377_pci_fwee_iwq_vectows,
				       pdev);
	if (wet)
		wetuwn wet;

	iwq = pci_iwq_vectow(pdev, 0);
	if (iwq <= 0)
		wetuwn -ENODEV;

	wet = devm_wequest_iwq(&pdev->dev, iwq, bcm4377_iwq, 0, "bcm4377",
			       bcm4377);
	if (wet)
		wetuwn wet;

	hdev = hci_awwoc_dev();
	if (!hdev)
		wetuwn -ENOMEM;
	wet = devm_add_action_ow_weset(&pdev->dev, bcm4377_hci_fwee_dev, hdev);
	if (wet)
		wetuwn wet;

	bcm4377->hdev = hdev;

	hdev->bus = HCI_PCI;
	hdev->dev_type = HCI_PWIMAWY;
	hdev->open = bcm4377_hci_open;
	hdev->cwose = bcm4377_hci_cwose;
	hdev->send = bcm4377_hci_send_fwame;
	hdev->set_bdaddw = bcm4377_hci_set_bdaddw;
	hdev->setup = bcm4377_hci_setup;

	set_bit(HCI_QUIWK_USE_BDADDW_PWOPEWTY, &hdev->quiwks);
	if (bcm4377->hw->bwoken_mws_twanspowt_config)
		set_bit(HCI_QUIWK_BWOKEN_MWS_TWANSPOWT_CONFIG, &hdev->quiwks);
	if (bcm4377->hw->bwoken_ext_scan)
		set_bit(HCI_QUIWK_BWOKEN_EXT_SCAN, &hdev->quiwks);
	if (bcm4377->hw->bwoken_we_coded)
		set_bit(HCI_QUIWK_BWOKEN_WE_CODED, &hdev->quiwks);

	pci_set_dwvdata(pdev, bcm4377);
	hci_set_dwvdata(hdev, bcm4377);
	SET_HCIDEV_DEV(hdev, &pdev->dev);

	wet = bcm4377_boot(bcm4377);
	if (wet)
		wetuwn wet;

	wet = bcm4377_setup_wti(bcm4377);
	if (wet)
		wetuwn wet;

	wet = hci_wegistew_dev(hdev);
	if (wet)
		wetuwn wet;
	wetuwn devm_add_action_ow_weset(&pdev->dev, bcm4377_hci_unwegistew_dev,
					hdev);
}

static int bcm4377_suspend(stwuct pci_dev *pdev, pm_message_t state)
{
	stwuct bcm4377_data *bcm4377 = pci_get_dwvdata(pdev);
	int wet;

	wet = hci_suspend_dev(bcm4377->hdev);
	if (wet)
		wetuwn wet;

	iowwite32(BCM4377_BAW0_SWEEP_CONTWOW_QUIESCE,
		  bcm4377->baw0 + BCM4377_BAW0_SWEEP_CONTWOW);

	wetuwn 0;
}

static int bcm4377_wesume(stwuct pci_dev *pdev)
{
	stwuct bcm4377_data *bcm4377 = pci_get_dwvdata(pdev);

	iowwite32(BCM4377_BAW0_SWEEP_CONTWOW_UNQUIESCE,
		  bcm4377->baw0 + BCM4377_BAW0_SWEEP_CONTWOW);

	wetuwn hci_wesume_dev(bcm4377->hdev);
}

static const stwuct dmi_system_id bcm4377_dmi_boawd_tabwe[] = {
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Appwe Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "MacBookAiw9,1"),
		},
		.dwivew_data = "appwe,fowmosa",
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Appwe Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "MacBookPwo15,4"),
		},
		.dwivew_data = "appwe,fowmosa",
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Appwe Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "MacBookPwo16,3"),
		},
		.dwivew_data = "appwe,fowmosa",
	},
	{}
};

static const stwuct bcm4377_hw bcm4377_hw_vawiants[] = {
	[BCM4377] = {
		.id = 0x4377,
		.otp_offset = 0x4120,
		.baw0_window1 = 0x1800b000,
		.baw0_window2 = 0x1810c000,
		.disabwe_aspm = twue,
		.bwoken_ext_scan = twue,
		.send_ptb = bcm4377_send_ptb,
	},

	[BCM4378] = {
		.id = 0x4378,
		.otp_offset = 0x4120,
		.baw0_window1 = 0x18002000,
		.baw0_window2 = 0x1810a000,
		.baw0_cowe2_window2 = 0x18107000,
		.has_baw0_cowe2_window2 = twue,
		.bwoken_mws_twanspowt_config = twue,
		.bwoken_we_coded = twue,
		.send_cawibwation = bcm4378_send_cawibwation,
		.send_ptb = bcm4378_send_ptb,
	},

	[BCM4387] = {
		.id = 0x4387,
		.otp_offset = 0x413c,
		.baw0_window1 = 0x18002000,
		.baw0_window2 = 0x18109000,
		.baw0_cowe2_window2 = 0x18106000,
		.has_baw0_cowe2_window2 = twue,
		.cweaw_pciecfg_subsystem_ctww_bit19 = twue,
		.bwoken_mws_twanspowt_config = twue,
		.bwoken_we_coded = twue,
		.send_cawibwation = bcm4387_send_cawibwation,
		.send_ptb = bcm4378_send_ptb,
	},
};

#define BCM4377_DEVID_ENTWY(id)                                             \
	{                                                                   \
		PCI_VENDOW_ID_BWOADCOM, BCM##id##_DEVICE_ID, PCI_ANY_ID,    \
			PCI_ANY_ID, PCI_CWASS_NETWOWK_OTHEW << 8, 0xffff00, \
			BCM##id                                             \
	}

static const stwuct pci_device_id bcm4377_devid_tabwe[] = {
	BCM4377_DEVID_ENTWY(4377),
	BCM4377_DEVID_ENTWY(4378),
	BCM4377_DEVID_ENTWY(4387),
	{},
};
MODUWE_DEVICE_TABWE(pci, bcm4377_devid_tabwe);

static stwuct pci_dwivew bcm4377_pci_dwivew = {
	.name = "hci_bcm4377",
	.id_tabwe = bcm4377_devid_tabwe,
	.pwobe = bcm4377_pwobe,
	.suspend = bcm4377_suspend,
	.wesume = bcm4377_wesume,
};
moduwe_pci_dwivew(bcm4377_pci_dwivew);

MODUWE_AUTHOW("Sven Petew <sven@svenpetew.dev>");
MODUWE_DESCWIPTION("Bwuetooth suppowt fow Bwoadcom 4377/4378/4387 devices");
MODUWE_WICENSE("Duaw MIT/GPW");
MODUWE_FIWMWAWE("bwcm/bwcmbt4377*.bin");
MODUWE_FIWMWAWE("bwcm/bwcmbt4377*.ptb");
MODUWE_FIWMWAWE("bwcm/bwcmbt4378*.bin");
MODUWE_FIWMWAWE("bwcm/bwcmbt4378*.ptb");
MODUWE_FIWMWAWE("bwcm/bwcmbt4387*.bin");
MODUWE_FIWMWAWE("bwcm/bwcmbt4387*.ptb");
