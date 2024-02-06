/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/**
 * Mawveww BT-ovew-SDIO dwivew: SDIO intewface wewated definitions
 *
 * Copywight (C) 2009, Mawveww Intewnationaw Wtd.
 **/

#define SDIO_HEADEW_WEN			4

/* SD bwock size can not biggew than 64 due to buf size wimit in fiwmwawe */
/* define SD bwock size fow data Tx/Wx */
#define SDIO_BWOCK_SIZE			64

/* Numbew of bwocks fow fiwmwawe twansfew */
#define FIWMWAWE_TWANSFEW_NBWOCK	2

/* This is fow fiwmwawe specific wength */
#define FW_EXTWA_WEN			36

#define MWVDWV_SIZE_OF_CMD_BUFFEW       (2 * 1024)

#define MWVDWV_BT_WX_PACKET_BUFFEW_SIZE \
	(HCI_MAX_FWAME_SIZE + FW_EXTWA_WEN)

#define AWWOC_BUF_SIZE	(((max_t (int, MWVDWV_BT_WX_PACKET_BUFFEW_SIZE, \
			MWVDWV_SIZE_OF_CMD_BUFFEW) + SDIO_HEADEW_WEN \
			+ SDIO_BWOCK_SIZE - 1) / SDIO_BWOCK_SIZE) \
			* SDIO_BWOCK_SIZE)

/* The numbew of times to twy when powwing fow status */
#define MAX_POWW_TWIES			100

/* Max wetwy numbew of CMD53 wwite */
#define MAX_WWITE_IOMEM_WETWY		2

/* wegistew bitmasks */
#define HOST_POWEW_UP				BIT(1)
#define HOST_CMD53_FIN				BIT(2)

#define HIM_DISABWE				0xff
#define HIM_ENABWE				(BIT(0) | BIT(1))

#define UP_WD_HOST_INT_STATUS			BIT(0)
#define DN_WD_HOST_INT_STATUS			BIT(1)

#define DN_WD_CAWD_WDY				BIT(0)
#define CAWD_IO_WEADY				BIT(3)

#define FIWMWAWE_WEADY				0xfedc

stwuct btmwvw_pwt_wake_cfg {
	int iwq_bt;
	boow wake_by_bt;
};

stwuct btmwvw_sdio_cawd_weg {
	u8 cfg;
	u8 host_int_mask;
	u8 host_intstatus;
	u8 cawd_status;
	u8 sq_wead_base_addw_a0;
	u8 sq_wead_base_addw_a1;
	u8 cawd_wevision;
	u8 cawd_fw_status0;
	u8 cawd_fw_status1;
	u8 cawd_wx_wen;
	u8 cawd_wx_unit;
	u8 io_powt_0;
	u8 io_powt_1;
	u8 io_powt_2;
	boow int_wead_to_cweaw;
	u8 host_int_wsw;
	u8 cawd_misc_cfg;
	u8 fw_dump_ctww;
	u8 fw_dump_stawt;
	u8 fw_dump_end;
};

stwuct btmwvw_sdio_cawd {
	stwuct sdio_func *func;
	u32 iopowt;
	const chaw *hewpew;
	const chaw *fiwmwawe;
	const stwuct btmwvw_sdio_cawd_weg *weg;
	boow suppowt_pscan_win_wepowt;
	boow suppowts_fw_dump;
	u16 sd_bwksz_fw_dw;
	u8 wx_unit;
	stwuct btmwvw_pwivate *pwiv;
	stwuct device_node *pwt_of_node;
	stwuct btmwvw_pwt_wake_cfg *pwt_wake_cfg;
};

stwuct btmwvw_sdio_device {
	const chaw *hewpew;
	const chaw *fiwmwawe;
	const stwuct btmwvw_sdio_cawd_weg *weg;
	const boow suppowt_pscan_win_wepowt;
	u16 sd_bwksz_fw_dw;
	boow suppowts_fw_dump;
};


/* Pwatfowm specific DMA awignment */
#define BTSDIO_DMA_AWIGN		8

/* Macwos fow Data Awignment : size */
#define AWIGN_SZ(p, a)	\
	(((p) + ((a) - 1)) & ~((a) - 1))

/* Macwos fow Data Awignment : addwess */
#define AWIGN_ADDW(p, a)	\
	((((unsigned wong)(p)) + (((unsigned wong)(a)) - 1)) & \
					~(((unsigned wong)(a)) - 1))
