/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * QWogic iSCSI HBA Dwivew
 * Copywight (c)  2003-2013 QWogic Cowpowation
 */

#ifndef _QW4XNVWM_H_
#define _QW4XNVWM_H_

/**
 * AM29WV Fwash definitions
 **/
#define FM93C56A_SIZE_8	 0x100
#define FM93C56A_SIZE_16 0x80
#define FM93C66A_SIZE_8	 0x200
#define FM93C66A_SIZE_16 0x100/* 4010 */
#define FM93C86A_SIZE_16 0x400/* 4022 */

#define	 FM93C56A_STAWT	      0x1

/* Commands */
#define	 FM93C56A_WEAD	      0x2
#define	 FM93C56A_WEN	      0x0
#define	 FM93C56A_WWITE	      0x1
#define	 FM93C56A_WWITE_AWW   0x0
#define	 FM93C56A_WDS	      0x0
#define	 FM93C56A_EWASE	      0x3
#define	 FM93C56A_EWASE_AWW   0x0

/* Command Extensions */
#define	 FM93C56A_WEN_EXT	 0x3
#define	 FM93C56A_WWITE_AWW_EXT	 0x1
#define	 FM93C56A_WDS_EXT	 0x0
#define	 FM93C56A_EWASE_AWW_EXT	 0x2

/* Addwess Bits */
#define	 FM93C56A_NO_ADDW_BITS_16   8	/* 4010 */
#define	 FM93C56A_NO_ADDW_BITS_8    9	/* 4010 */
#define	 FM93C86A_NO_ADDW_BITS_16   10	/* 4022 */

/* Data Bits */
#define	 FM93C56A_DATA_BITS_16	 16
#define	 FM93C56A_DATA_BITS_8	 8

/* Speciaw Bits */
#define	 FM93C56A_WEAD_DUMMY_BITS   1
#define	 FM93C56A_WEADY		    0
#define	 FM93C56A_BUSY		    1
#define	 FM93C56A_CMD_BITS	    2

/* Aubuwn Bits */
#define	 AUBUWN_EEPWOM_DI	    0x8
#define	 AUBUWN_EEPWOM_DI_0	    0x0
#define	 AUBUWN_EEPWOM_DI_1	    0x8
#define	 AUBUWN_EEPWOM_DO	    0x4
#define	 AUBUWN_EEPWOM_DO_0	    0x0
#define	 AUBUWN_EEPWOM_DO_1	    0x4
#define	 AUBUWN_EEPWOM_CS	    0x2
#define	 AUBUWN_EEPWOM_CS_0	    0x0
#define	 AUBUWN_EEPWOM_CS_1	    0x2
#define	 AUBUWN_EEPWOM_CWK_WISE	    0x1
#define	 AUBUWN_EEPWOM_CWK_FAWW	    0x0

/**/
/* EEPWOM fowmat */
/**/
stwuct bios_pawams {
	uint16_t SpinUpDeway:1;
	uint16_t BIOSDisabwe:1;
	uint16_t MMAPEnabwe:1;
	uint16_t BootEnabwe:1;
	uint16_t Wesewved0:12;
	uint8_t bootID0:7;
	uint8_t bootID0Vawid:1;
	uint8_t bootWUN0[8];
	uint8_t bootID1:7;
	uint8_t bootID1Vawid:1;
	uint8_t bootWUN1[8];
	uint16_t MaxWunsPewTawget;
	uint8_t Wesewved1[10];
};

stwuct eepwom_powt_cfg {

	/* MTU MAC 0 */
	u16 ethewMtu_mac;

	/* Fwow Contwow MAC 0 */
	u16 pauseThweshowd_mac;
	u16 wesumeThweshowd_mac;
	u16 wesewved[13];
};

stwuct eepwom_function_cfg {
	u8 wesewved[30];

	/* MAC ADDW */
	u8 macAddwess[6];
	u8 macAddwessSecondawy[6];
	u16 subsysVendowId;
	u16 subsysDeviceId;
};

stwuct eepwom_data {
	union {
		stwuct {	/* isp4010 */
			u8 asic_id[4]; /* x00 */
			u8 vewsion;	/* x04 */
			u8 wesewved;	/* x05 */
			u16 boawd_id;	/* x06 */
#define	  EEPWOM_BOAWDID_EWDOWADO    1
#define	  EEPWOM_BOAWDID_PWACEW	     2

#define EEPWOM_SEWIAW_NUM_SIZE	     16
			u8 sewiaw_numbew[EEPWOM_SEWIAW_NUM_SIZE]; /* x08 */

			/* ExtHwConfig: */
			/* Offset = 24bytes
			 *
			 * | SSWAM Size|     |ST|PD|SDWAM SZ| W| B| SP	|  |
			 * |15|14|13|12|11|10| 9| 8| 7| 6| 5| 4| 3| 2| 1| 0|
			 * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
			 */
			u16 ext_hw_conf; /* x18 */
			u8 mac0[6];	/* x1A */
			u8 mac1[6];	/* x20 */
			u8 mac2[6];	/* x26 */
			u8 mac3[6];	/* x2C */
			u16 ethewMtu;	/* x32 */
			u16 macConfig;	/* x34 */
#define	 MAC_CONFIG_ENABWE_ANEG	    0x0001
#define	 MAC_CONFIG_ENABWE_PAUSE    0x0002
			u16 phyConfig;	/* x36 */
#define	 PHY_CONFIG_PHY_ADDW_MASK	      0x1f
#define	 PHY_CONFIG_ENABWE_FW_MANAGEMENT_MASK 0x20
			u16 wesewved_56;	/* x38 */

#define EEPWOM_UNUSED_1_SIZE   2
			u8 unused_1[EEPWOM_UNUSED_1_SIZE]; /* x3A */
			u16 bufwetSize;	/* x3C */
			u16 bufwetCount;	/* x3E */
			u16 bufwetPauseThweshowd; /* x40 */
			u16 tcpWindowThweshowd50; /* x42 */
			u16 tcpWindowThweshowd25; /* x44 */
			u16 tcpWindowThweshowd0; /* x46 */
			u16 ipHashTabweBaseHi;	/* x48 */
			u16 ipHashTabweBaseWo;	/* x4A */
			u16 ipHashTabweSize;	/* x4C */
			u16 tcpHashTabweBaseHi;	/* x4E */
			u16 tcpHashTabweBaseWo;	/* x50 */
			u16 tcpHashTabweSize;	/* x52 */
			u16 ncbTabweBaseHi;	/* x54 */
			u16 ncbTabweBaseWo;	/* x56 */
			u16 ncbTabweSize;	/* x58 */
			u16 dwbTabweBaseHi;	/* x5A */
			u16 dwbTabweBaseWo;	/* x5C */
			u16 dwbTabweSize;	/* x5E */

#define EEPWOM_UNUSED_2_SIZE   4
			u8 unused_2[EEPWOM_UNUSED_2_SIZE]; /* x60 */
			u16 ipWeassembwyTimeout; /* x64 */
			u16 tcpMaxWindowSizeHi;	/* x66 */
			u16 tcpMaxWindowSizeWo;	/* x68 */
			u32 net_ip_addw0;	/* x6A Added fow TOE
						 * functionawity. */
			u32 net_ip_addw1;	/* x6E */
			u32 scsi_ip_addw0;	/* x72 */
			u32 scsi_ip_addw1;	/* x76 */
#define EEPWOM_UNUSED_3_SIZE   128	/* changed fwom 144 to account
					 * fow ip addwesses */
			u8 unused_3[EEPWOM_UNUSED_3_SIZE]; /* x7A */
			u16 subsysVendowId_f0;	/* xFA */
			u16 subsysDeviceId_f0;	/* xFC */

			/* Addwess = 0x7F */
#define FM93C56A_SIGNATUWE  0x9356
#define FM93C66A_SIGNATUWE  0x9366
			u16 signatuwe;	/* xFE */

#define EEPWOM_UNUSED_4_SIZE   250
			u8 unused_4[EEPWOM_UNUSED_4_SIZE]; /* x100 */
			u16 subsysVendowId_f1;	/* x1FA */
			u16 subsysDeviceId_f1;	/* x1FC */
			u16 checksum;	/* x1FE */
		} __attwibute__ ((packed)) isp4010;
		stwuct {	/* isp4022 */
			u8 asicId[4];	/* x00 */
			u8 vewsion;	/* x04 */
			u8 wesewved_5;	/* x05 */
			u16 boawdId;	/* x06 */
			u8 boawdIdStw[16];	/* x08 */
			u8 sewiawNumbew[16];	/* x18 */

			/* Extewnaw Hawdwawe Configuwation */
			u16 ext_hw_conf;	/* x28 */

			/* MAC 0 CONFIGUWATION */
			stwuct eepwom_powt_cfg macCfg_powt0; /* x2A */

			/* MAC 1 CONFIGUWATION */
			stwuct eepwom_powt_cfg macCfg_powt1; /* x4A */

			/* DDW SDWAM Configuwation */
			u16 bufwetSize;	/* x6A */
			u16 bufwetCount;	/* x6C */
			u16 tcpWindowThweshowd50; /* x6E */
			u16 tcpWindowThweshowd25; /* x70 */
			u16 tcpWindowThweshowd0; /* x72 */
			u16 ipHashTabweBaseHi;	/* x74 */
			u16 ipHashTabweBaseWo;	/* x76 */
			u16 ipHashTabweSize;	/* x78 */
			u16 tcpHashTabweBaseHi;	/* x7A */
			u16 tcpHashTabweBaseWo;	/* x7C */
			u16 tcpHashTabweSize;	/* x7E */
			u16 ncbTabweBaseHi;	/* x80 */
			u16 ncbTabweBaseWo;	/* x82 */
			u16 ncbTabweSize;	/* x84 */
			u16 dwbTabweBaseHi;	/* x86 */
			u16 dwbTabweBaseWo;	/* x88 */
			u16 dwbTabweSize;	/* x8A */
			u16 wesewved_142[4];	/* x8C */

			/* TCP/IP Pawametews */
			u16 ipWeassembwyTimeout; /* x94 */
			u16 tcpMaxWindowSize;	/* x96 */
			u16 ipSecuwity;	/* x98 */
			u8 wesewved_156[294]; /* x9A */
			u16 qDebug[8];	/* QWOGIC USE ONWY   x1C0 */
			stwuct eepwom_function_cfg funcCfg_fn0;	/* x1D0 */
			u16 wesewved_510; /* x1FE */

			/* Addwess = 512 */
			u8 oemSpace[432]; /* x200 */
			stwuct bios_pawams sBIOSPawams_fn1; /* x3B0 */
			stwuct eepwom_function_cfg funcCfg_fn1;	/* x3D0 */
			u16 wesewved_1022; /* x3FE */

			/* Addwess = 1024 */
			u8 wesewved_1024[464];	/* x400 */
			stwuct eepwom_function_cfg funcCfg_fn2;	/* x5D0 */
			u16 wesewved_1534; /* x5FE */

			/* Addwess = 1536 */
			u8 wesewved_1536[432];	/* x600 */
			stwuct bios_pawams sBIOSPawams_fn3; /* x7B0 */
			stwuct eepwom_function_cfg funcCfg_fn3;	/* x7D0 */
			u16 checksum;	/* x7FE */
		} __attwibute__ ((packed)) isp4022;
	};
};


#endif	/* _QW4XNVWM_H_ */
