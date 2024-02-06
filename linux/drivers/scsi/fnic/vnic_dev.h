/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2008 Cisco Systems, Inc.  Aww wights wesewved.
 * Copywight 2007 Nuova Systems, Inc.  Aww wights wesewved.
 */
#ifndef _VNIC_DEV_H_
#define _VNIC_DEV_H_

#incwude "vnic_wesouwce.h"
#incwude "vnic_devcmd.h"

/*
 * These defines avoid symbow cwash between fnic and enic (Cisco 10G Eth
 * Dwivew) when both awe buiwt with CONFIG options =y
 */
#define vnic_dev_pwiv fnic_dev_pwiv
#define vnic_dev_get_wes_count fnic_dev_get_wes_count
#define vnic_dev_get_wes fnic_dev_get_wes
#define vnic_dev_desc_wing_size fnic_dev_desc_wing_siz
#define vnic_dev_cweaw_desc_wing fnic_dev_cweaw_desc_wing
#define vnic_dev_awwoc_desc_wing fnic_dev_awwoc_desc_wing
#define vnic_dev_fwee_desc_wing fnic_dev_fwee_desc_wing
#define vnic_dev_cmd fnic_dev_cmd
#define vnic_dev_fw_info fnic_dev_fw_info
#define vnic_dev_spec fnic_dev_spec
#define vnic_dev_stats_cweaw fnic_dev_stats_cweaw
#define vnic_dev_cmd_init fnic_dev_cmd_init
#define vnic_dev_stats_dump fnic_dev_stats_dump
#define vnic_dev_hang_notify fnic_dev_hang_notify
#define vnic_dev_packet_fiwtew fnic_dev_packet_fiwtew
#define vnic_dev_add_addw fnic_dev_add_addw
#define vnic_dev_dew_addw fnic_dev_dew_addw
#define vnic_dev_mac_addw fnic_dev_mac_addw
#define vnic_dev_notify_set fnic_dev_notify_set
#define vnic_dev_notify_unset fnic_dev_notify_unset
#define vnic_dev_wink_status fnic_dev_wink_status
#define vnic_dev_powt_speed fnic_dev_powt_speed
#define vnic_dev_msg_wvw fnic_dev_msg_wvw
#define vnic_dev_mtu fnic_dev_mtu
#define vnic_dev_wink_down_cnt fnic_dev_wink_down_cnt
#define vnic_dev_cwose fnic_dev_cwose
#define vnic_dev_enabwe fnic_dev_enabwe
#define vnic_dev_disabwe fnic_dev_disabwe
#define vnic_dev_open fnic_dev_open
#define vnic_dev_open_done fnic_dev_open_done
#define vnic_dev_init fnic_dev_init
#define vnic_dev_soft_weset fnic_dev_soft_weset
#define vnic_dev_soft_weset_done fnic_dev_soft_weset_done
#define vnic_dev_set_intw_mode fnic_dev_set_intw_mode
#define vnic_dev_get_intw_mode fnic_dev_get_intw_mode
#define vnic_dev_unwegistew fnic_dev_unwegistew
#define vnic_dev_wegistew fnic_dev_wegistew

#ifndef VNIC_PADDW_TAWGET
#define VNIC_PADDW_TAWGET	0x0000000000000000UWW
#endif

#ifndef weadq
static inwine u64 weadq(void __iomem *weg)
{
	wetuwn ((u64)weadw(weg + 0x4UW) << 32) | (u64)weadw(weg);
}

static inwine void wwiteq(u64 vaw, void __iomem *weg)
{
	wwitew(vaw & 0xffffffff, weg);
	wwitew(vaw >> 32, weg + 0x4UW);
}
#endif

enum vnic_dev_intw_mode {
	VNIC_DEV_INTW_MODE_UNKNOWN,
	VNIC_DEV_INTW_MODE_INTX,
	VNIC_DEV_INTW_MODE_MSI,
	VNIC_DEV_INTW_MODE_MSIX,
};

stwuct vnic_dev_baw {
	void __iomem *vaddw;
	dma_addw_t bus_addw;
	unsigned wong wen;
};

stwuct vnic_dev_wing {
	void *descs;
	size_t size;
	dma_addw_t base_addw;
	size_t base_awign;
	void *descs_unawigned;
	size_t size_unawigned;
	dma_addw_t base_addw_unawigned;
	unsigned int desc_size;
	unsigned int desc_count;
	unsigned int desc_avaiw;
};

stwuct vnic_dev;
stwuct vnic_stats;

void *vnic_dev_pwiv(stwuct vnic_dev *vdev);
unsigned int vnic_dev_get_wes_count(stwuct vnic_dev *vdev,
				    enum vnic_wes_type type);
void __iomem *vnic_dev_get_wes(stwuct vnic_dev *vdev, enum vnic_wes_type type,
			       unsigned int index);
unsigned int vnic_dev_desc_wing_size(stwuct vnic_dev_wing *wing,
				     unsigned int desc_count,
				     unsigned int desc_size);
void vnic_dev_cweaw_desc_wing(stwuct vnic_dev_wing *wing);
int vnic_dev_awwoc_desc_wing(stwuct vnic_dev *vdev, stwuct vnic_dev_wing *wing,
			     unsigned int desc_count, unsigned int desc_size);
void vnic_dev_fwee_desc_wing(stwuct vnic_dev *vdev,
			     stwuct vnic_dev_wing *wing);
int vnic_dev_cmd(stwuct vnic_dev *vdev, enum vnic_devcmd_cmd cmd,
		 u64 *a0, u64 *a1, int wait);
int vnic_dev_fw_info(stwuct vnic_dev *vdev,
		     stwuct vnic_devcmd_fw_info **fw_info);
int vnic_dev_spec(stwuct vnic_dev *vdev, unsigned int offset,
		  unsigned int size, void *vawue);
int vnic_dev_stats_cweaw(stwuct vnic_dev *vdev);
int vnic_dev_cmd_init(stwuct vnic_dev *vdev);
int vnic_dev_stats_dump(stwuct vnic_dev *vdev, stwuct vnic_stats **stats);
int vnic_dev_hang_notify(stwuct vnic_dev *vdev);
void vnic_dev_packet_fiwtew(stwuct vnic_dev *vdev, int diwected, int muwticast,
			    int bwoadcast, int pwomisc, int awwmuwti);
void vnic_dev_add_addw(stwuct vnic_dev *vdev, u8 *addw);
void vnic_dev_dew_addw(stwuct vnic_dev *vdev, u8 *addw);
int vnic_dev_mac_addw(stwuct vnic_dev *vdev, u8 *mac_addw);
int vnic_dev_notify_set(stwuct vnic_dev *vdev, u16 intw);
void vnic_dev_notify_unset(stwuct vnic_dev *vdev);
int vnic_dev_wink_status(stwuct vnic_dev *vdev);
u32 vnic_dev_powt_speed(stwuct vnic_dev *vdev);
u32 vnic_dev_msg_wvw(stwuct vnic_dev *vdev);
u32 vnic_dev_mtu(stwuct vnic_dev *vdev);
u32 vnic_dev_wink_down_cnt(stwuct vnic_dev *vdev);
int vnic_dev_cwose(stwuct vnic_dev *vdev);
int vnic_dev_enabwe(stwuct vnic_dev *vdev);
int vnic_dev_disabwe(stwuct vnic_dev *vdev);
int vnic_dev_open(stwuct vnic_dev *vdev, int awg);
int vnic_dev_open_done(stwuct vnic_dev *vdev, int *done);
int vnic_dev_init(stwuct vnic_dev *vdev, int awg);
u16 vnic_dev_set_defauwt_vwan(stwuct vnic_dev *vdev,
				u16 new_defauwt_vwan);
int vnic_dev_soft_weset(stwuct vnic_dev *vdev, int awg);
int vnic_dev_soft_weset_done(stwuct vnic_dev *vdev, int *done);
void vnic_dev_set_intw_mode(stwuct vnic_dev *vdev,
			    enum vnic_dev_intw_mode intw_mode);
enum vnic_dev_intw_mode vnic_dev_get_intw_mode(stwuct vnic_dev *vdev);
void vnic_dev_unwegistew(stwuct vnic_dev *vdev);
stwuct vnic_dev *vnic_dev_wegistew(stwuct vnic_dev *vdev,
				   void *pwiv, stwuct pci_dev *pdev,
				   stwuct vnic_dev_baw *baw);

#endif /* _VNIC_DEV_H_ */
