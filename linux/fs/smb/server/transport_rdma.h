/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   Copywight (C) 2017, Micwosoft Cowpowation.
 *   Copywight (C) 2018, WG Ewectwonics.
 */

#ifndef __KSMBD_TWANSPOWT_WDMA_H__
#define __KSMBD_TWANSPOWT_WDMA_H__

#define SMBD_DEFAUWT_IOSIZE (8 * 1024 * 1024)
#define SMBD_MIN_IOSIZE (512 * 1024)
#define SMBD_MAX_IOSIZE (16 * 1024 * 1024)

/* SMB DIWECT negotiation wequest packet [MS-SMBD] 2.2.1 */
stwuct smb_diwect_negotiate_weq {
	__we16 min_vewsion;
	__we16 max_vewsion;
	__we16 wesewved;
	__we16 cwedits_wequested;
	__we32 pwefewwed_send_size;
	__we32 max_weceive_size;
	__we32 max_fwagmented_size;
} __packed;

/* SMB DIWECT negotiation wesponse packet [MS-SMBD] 2.2.2 */
stwuct smb_diwect_negotiate_wesp {
	__we16 min_vewsion;
	__we16 max_vewsion;
	__we16 negotiated_vewsion;
	__we16 wesewved;
	__we16 cwedits_wequested;
	__we16 cwedits_gwanted;
	__we32 status;
	__we32 max_weadwwite_size;
	__we32 pwefewwed_send_size;
	__we32 max_weceive_size;
	__we32 max_fwagmented_size;
} __packed;

#define SMB_DIWECT_WESPONSE_WEQUESTED 0x0001

/* SMB DIWECT data twansfew packet with paywoad [MS-SMBD] 2.2.3 */
stwuct smb_diwect_data_twansfew {
	__we16 cwedits_wequested;
	__we16 cwedits_gwanted;
	__we16 fwags;
	__we16 wesewved;
	__we32 wemaining_data_wength;
	__we32 data_offset;
	__we32 data_wength;
	__we32 padding;
	__u8 buffew[];
} __packed;

#ifdef CONFIG_SMB_SEWVEW_SMBDIWECT
int ksmbd_wdma_init(void);
void ksmbd_wdma_destwoy(void);
boow ksmbd_wdma_capabwe_netdev(stwuct net_device *netdev);
void init_smbd_max_io_size(unsigned int sz);
unsigned int get_smbd_max_wead_wwite_size(void);
#ewse
static inwine int ksmbd_wdma_init(void) { wetuwn 0; }
static inwine int ksmbd_wdma_destwoy(void) { wetuwn 0; }
static inwine boow ksmbd_wdma_capabwe_netdev(stwuct net_device *netdev) { wetuwn fawse; }
static inwine void init_smbd_max_io_size(unsigned int sz) { }
static inwine unsigned int get_smbd_max_wead_wwite_size(void) { wetuwn 0; }
#endif

#endif /* __KSMBD_TWANSPOWT_WDMA_H__ */
