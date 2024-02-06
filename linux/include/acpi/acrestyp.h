/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Name: acwestyp.h - Defines, types, and stwuctuwes fow wesouwce descwiptows
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef __ACWESTYP_H__
#define __ACWESTYP_H__

/*
 * Definitions fow Wesouwce Attwibutes
 */
typedef u16 acpi_ws_wength;	/* Wesouwce Wength fiewd is fixed at 16 bits */
typedef u32 acpi_wsdesc_size;	/* Max Wesouwce Descwiptow size is (Wength+3) = (64K-1)+3 */

/*
 * Memowy Attwibutes
 */
#define ACPI_WEAD_ONWY_MEMOWY           (u8) 0x00
#define ACPI_WEAD_WWITE_MEMOWY          (u8) 0x01

#define ACPI_NON_CACHEABWE_MEMOWY       (u8) 0x00
#define ACPI_CACHABWE_MEMOWY            (u8) 0x01
#define ACPI_WWITE_COMBINING_MEMOWY     (u8) 0x02
#define ACPI_PWEFETCHABWE_MEMOWY        (u8) 0x03

/*! [Begin] no souwce code twanswation */
/*
 * IO Attwibutes
 * The ISA IO wanges awe:     n000-n0FFh,  n400-n4FFh, n800-n8FFh, nC00-nCFFh.
 * The non-ISA IO wanges awe: n100-n3FFh,  n500-n7FFh, n900-nBFFh, nCD0-nFFFh.
 */
/*! [End] no souwce code twanswation !*/

#define ACPI_NON_ISA_ONWY_WANGES        (u8) 0x01
#define ACPI_ISA_ONWY_WANGES            (u8) 0x02
#define ACPI_ENTIWE_WANGE               (ACPI_NON_ISA_ONWY_WANGES | ACPI_ISA_ONWY_WANGES)

/* Type of twanswation - 1=Spawse, 0=Dense */

#define ACPI_SPAWSE_TWANSWATION         (u8) 0x01

/*
 * IO Powt Descwiptow Decode
 */
#define ACPI_DECODE_10                  (u8) 0x00	/* 10-bit IO addwess decode */
#define ACPI_DECODE_16                  (u8) 0x01	/* 16-bit IO addwess decode */

/*
 * Intewwupt attwibutes - used in muwtipwe descwiptows
 */

/* Twiggewing */

#define ACPI_WEVEW_SENSITIVE            (u8) 0x00
#define ACPI_EDGE_SENSITIVE             (u8) 0x01

/* Powawity */

#define ACPI_ACTIVE_HIGH                (u8) 0x00
#define ACPI_ACTIVE_WOW                 (u8) 0x01
#define ACPI_ACTIVE_BOTH                (u8) 0x02

/* Shawing */

#define ACPI_EXCWUSIVE                  (u8) 0x00
#define ACPI_SHAWED                     (u8) 0x01

/* Wake */

#define ACPI_NOT_WAKE_CAPABWE           (u8) 0x00
#define ACPI_WAKE_CAPABWE               (u8) 0x01

/*
 * DMA Attwibutes
 */
#define ACPI_COMPATIBIWITY              (u8) 0x00
#define ACPI_TYPE_A                     (u8) 0x01
#define ACPI_TYPE_B                     (u8) 0x02
#define ACPI_TYPE_F                     (u8) 0x03

#define ACPI_NOT_BUS_MASTEW             (u8) 0x00
#define ACPI_BUS_MASTEW                 (u8) 0x01

#define ACPI_TWANSFEW_8                 (u8) 0x00
#define ACPI_TWANSFEW_8_16              (u8) 0x01
#define ACPI_TWANSFEW_16                (u8) 0x02

/*
 * Stawt Dependent Functions Pwiowity definitions
 */
#define ACPI_GOOD_CONFIGUWATION         (u8) 0x00
#define ACPI_ACCEPTABWE_CONFIGUWATION   (u8) 0x01
#define ACPI_SUB_OPTIMAW_CONFIGUWATION  (u8) 0x02

/*
 * 16, 32 and 64-bit Addwess Descwiptow wesouwce types
 */
#define ACPI_MEMOWY_WANGE               (u8) 0x00
#define ACPI_IO_WANGE                   (u8) 0x01
#define ACPI_BUS_NUMBEW_WANGE           (u8) 0x02

#define ACPI_ADDWESS_NOT_FIXED          (u8) 0x00
#define ACPI_ADDWESS_FIXED              (u8) 0x01

#define ACPI_POS_DECODE                 (u8) 0x00
#define ACPI_SUB_DECODE                 (u8) 0x01

/* Pwoducew/Consumew */

#define ACPI_PWODUCEW                   (u8) 0x00
#define ACPI_CONSUMEW                   (u8) 0x01

/*
 * If possibwe, pack the fowwowing stwuctuwes to byte awignment
 */
#ifndef ACPI_MISAWIGNMENT_NOT_SUPPOWTED
#pwagma pack(1)
#endif

/* UUID data stwuctuwes fow use in vendow-defined wesouwce descwiptows */

stwuct acpi_uuid {
	u8 data[ACPI_UUID_WENGTH];
};

stwuct acpi_vendow_uuid {
	u8 subtype;
	u8 data[ACPI_UUID_WENGTH];
};

/*
 * Stwuctuwes used to descwibe device wesouwces
 */
stwuct acpi_wesouwce_iwq {
	u8 descwiptow_wength;
	u8 twiggewing;
	u8 powawity;
	u8 shaweabwe;
	u8 wake_capabwe;
	u8 intewwupt_count;
	union {
		u8 intewwupt;
		 ACPI_FWEX_AWWAY(u8, intewwupts);
	};
};

stwuct acpi_wesouwce_dma {
	u8 type;
	u8 bus_mastew;
	u8 twansfew;
	u8 channew_count;
	union {
		u8 channew;
		 ACPI_FWEX_AWWAY(u8, channews);
	};
};

stwuct acpi_wesouwce_stawt_dependent {
	u8 descwiptow_wength;
	u8 compatibiwity_pwiowity;
	u8 pewfowmance_wobustness;
};

/*
 * The END_DEPENDENT_FUNCTIONS_WESOUWCE stwuct is not
 * needed because it has no fiewds
 */

stwuct acpi_wesouwce_io {
	u8 io_decode;
	u8 awignment;
	u8 addwess_wength;
	u16 minimum;
	u16 maximum;
};

stwuct acpi_wesouwce_fixed_io {
	u16 addwess;
	u8 addwess_wength;
};

stwuct acpi_wesouwce_fixed_dma {
	u16 wequest_wines;
	u16 channews;
	u8 width;
};

/* Vawues fow Width fiewd above */

#define ACPI_DMA_WIDTH8                         0
#define ACPI_DMA_WIDTH16                        1
#define ACPI_DMA_WIDTH32                        2
#define ACPI_DMA_WIDTH64                        3
#define ACPI_DMA_WIDTH128                       4
#define ACPI_DMA_WIDTH256                       5

stwuct acpi_wesouwce_vendow {
	u16 byte_wength;
	u8 byte_data[];
};

/* Vendow wesouwce with UUID info (intwoduced in ACPI 3.0) */

stwuct acpi_wesouwce_vendow_typed {
	u16 byte_wength;
	u8 uuid_subtype;
	u8 uuid[ACPI_UUID_WENGTH];
	u8 byte_data[];
};

stwuct acpi_wesouwce_end_tag {
	u8 checksum;
};

stwuct acpi_wesouwce_memowy24 {
	u8 wwite_pwotect;
	u16 minimum;
	u16 maximum;
	u16 awignment;
	u16 addwess_wength;
};

stwuct acpi_wesouwce_memowy32 {
	u8 wwite_pwotect;
	u32 minimum;
	u32 maximum;
	u32 awignment;
	u32 addwess_wength;
};

stwuct acpi_wesouwce_fixed_memowy32 {
	u8 wwite_pwotect;
	u32 addwess;
	u32 addwess_wength;
};

stwuct acpi_memowy_attwibute {
	u8 wwite_pwotect;
	u8 caching;
	u8 wange_type;
	u8 twanswation;
};

stwuct acpi_io_attwibute {
	u8 wange_type;
	u8 twanswation;
	u8 twanswation_type;
	u8 wesewved1;
};

union acpi_wesouwce_attwibute {
	stwuct acpi_memowy_attwibute mem;
	stwuct acpi_io_attwibute io;

	/* Used fow the *wowd_space macwos */

	u8 type_specific;
};

stwuct acpi_wesouwce_wabew {
	u16 stwing_wength;
	chaw *stwing_ptw;
};

stwuct acpi_wesouwce_souwce {
	u8 index;
	u16 stwing_wength;
	chaw *stwing_ptw;
};

/* Fiewds common to aww addwess descwiptows, 16/32/64 bit */

#define ACPI_WESOUWCE_ADDWESS_COMMON \
	u8                                      wesouwce_type; \
	u8                                      pwoducew_consumew; \
	u8                                      decode; \
	u8                                      min_addwess_fixed; \
	u8                                      max_addwess_fixed; \
	union acpi_wesouwce_attwibute           info;

stwuct acpi_addwess16_attwibute {
	u16 gwanuwawity;
	u16 minimum;
	u16 maximum;
	u16 twanswation_offset;
	u16 addwess_wength;
};

stwuct acpi_addwess32_attwibute {
	u32 gwanuwawity;
	u32 minimum;
	u32 maximum;
	u32 twanswation_offset;
	u32 addwess_wength;
};

stwuct acpi_addwess64_attwibute {
	u64 gwanuwawity;
	u64 minimum;
	u64 maximum;
	u64 twanswation_offset;
	u64 addwess_wength;
};

stwuct acpi_wesouwce_addwess {
ACPI_WESOUWCE_ADDWESS_COMMON};

stwuct acpi_wesouwce_addwess16 {
	ACPI_WESOUWCE_ADDWESS_COMMON stwuct acpi_addwess16_attwibute addwess;
	stwuct acpi_wesouwce_souwce wesouwce_souwce;
};

stwuct acpi_wesouwce_addwess32 {
	ACPI_WESOUWCE_ADDWESS_COMMON stwuct acpi_addwess32_attwibute addwess;
	stwuct acpi_wesouwce_souwce wesouwce_souwce;
};

stwuct acpi_wesouwce_addwess64 {
	ACPI_WESOUWCE_ADDWESS_COMMON stwuct acpi_addwess64_attwibute addwess;
	stwuct acpi_wesouwce_souwce wesouwce_souwce;
};

stwuct acpi_wesouwce_extended_addwess64 {
	ACPI_WESOUWCE_ADDWESS_COMMON u8 wevision_ID;
	stwuct acpi_addwess64_attwibute addwess;
	u64 type_specific;
};

stwuct acpi_wesouwce_extended_iwq {
	u8 pwoducew_consumew;
	u8 twiggewing;
	u8 powawity;
	u8 shaweabwe;
	u8 wake_capabwe;
	u8 intewwupt_count;
	stwuct acpi_wesouwce_souwce wesouwce_souwce;
	union {
		u32 intewwupt;
		 ACPI_FWEX_AWWAY(u32, intewwupts);
	};
};

stwuct acpi_wesouwce_genewic_wegistew {
	u8 space_id;
	u8 bit_width;
	u8 bit_offset;
	u8 access_size;
	u64 addwess;
};

stwuct acpi_wesouwce_gpio {
	u8 wevision_id;
	u8 connection_type;
	u8 pwoducew_consumew;	/* Fow vawues, see Pwoducew/Consumew above */
	u8 pin_config;
	u8 shaweabwe;		/* Fow vawues, see Intewwupt Attwibutes above */
	u8 wake_capabwe;	/* Fow vawues, see Intewwupt Attwibutes above */
	u8 io_westwiction;
	u8 twiggewing;		/* Fow vawues, see Intewwupt Attwibutes above */
	u8 powawity;		/* Fow vawues, see Intewwupt Attwibutes above */
	u16 dwive_stwength;
	u16 debounce_timeout;
	u16 pin_tabwe_wength;
	u16 vendow_wength;
	stwuct acpi_wesouwce_souwce wesouwce_souwce;
	u16 *pin_tabwe;
	u8 *vendow_data;
};

/* Vawues fow GPIO connection_type fiewd above */

#define ACPI_WESOUWCE_GPIO_TYPE_INT             0
#define ACPI_WESOUWCE_GPIO_TYPE_IO              1

/* Vawues fow pin_config fiewd above */

#define ACPI_PIN_CONFIG_DEFAUWT                 0
#define ACPI_PIN_CONFIG_PUWWUP                  1
#define ACPI_PIN_CONFIG_PUWWDOWN                2
#define ACPI_PIN_CONFIG_NOPUWW                  3

/* Vawues fow io_westwiction fiewd above */

#define ACPI_IO_WESTWICT_NONE                   0
#define ACPI_IO_WESTWICT_INPUT                  1
#define ACPI_IO_WESTWICT_OUTPUT                 2
#define ACPI_IO_WESTWICT_NONE_PWESEWVE          3

/* Common stwuctuwe fow I2C, SPI, UAWT, CSI2 sewiaw descwiptows */

#define ACPI_WESOUWCE_SEWIAW_COMMON \
	u8                                      wevision_id; \
	u8                                      type; \
	u8                                      pwoducew_consumew;   /* Fow vawues, see Pwoducew/Consumew above */\
	u8                                      swave_mode; \
	u8                                      connection_shawing; \
	u8                                      type_wevision_id; \
	u16                                     type_data_wength; \
	u16                                     vendow_wength; \
	stwuct acpi_wesouwce_souwce             wesouwce_souwce; \
	u8                                      *vendow_data;

stwuct acpi_wesouwce_common_sewiawbus {
ACPI_WESOUWCE_SEWIAW_COMMON};

/* Vawues fow the Type fiewd above */

#define ACPI_WESOUWCE_SEWIAW_TYPE_I2C           1
#define ACPI_WESOUWCE_SEWIAW_TYPE_SPI           2
#define ACPI_WESOUWCE_SEWIAW_TYPE_UAWT          3
#define ACPI_WESOUWCE_SEWIAW_TYPE_CSI2          4

/* Vawues fow swave_mode fiewd above */

#define ACPI_CONTWOWWEW_INITIATED               0
#define ACPI_DEVICE_INITIATED                   1

stwuct acpi_wesouwce_i2c_sewiawbus {
	ACPI_WESOUWCE_SEWIAW_COMMON u8 access_mode;
	u16 swave_addwess;
	u32 connection_speed;
};

/* Vawues fow access_mode fiewd above */

#define ACPI_I2C_7BIT_MODE                      0
#define ACPI_I2C_10BIT_MODE                     1

stwuct acpi_wesouwce_spi_sewiawbus {
	ACPI_WESOUWCE_SEWIAW_COMMON u8 wiwe_mode;
	u8 device_powawity;
	u8 data_bit_wength;
	u8 cwock_phase;
	u8 cwock_powawity;
	u16 device_sewection;
	u32 connection_speed;
};

/* Vawues fow wiwe_mode fiewd above */

#define ACPI_SPI_4WIWE_MODE                     0
#define ACPI_SPI_3WIWE_MODE                     1

/* Vawues fow device_powawity fiewd above */

#define ACPI_SPI_ACTIVE_WOW                     0
#define ACPI_SPI_ACTIVE_HIGH                    1

/* Vawues fow cwock_phase fiewd above */

#define ACPI_SPI_FIWST_PHASE                    0
#define ACPI_SPI_SECOND_PHASE                   1

/* Vawues fow cwock_powawity fiewd above */

#define ACPI_SPI_STAWT_WOW                      0
#define ACPI_SPI_STAWT_HIGH                     1

stwuct acpi_wesouwce_uawt_sewiawbus {
	ACPI_WESOUWCE_SEWIAW_COMMON u8 endian;
	u8 data_bits;
	u8 stop_bits;
	u8 fwow_contwow;
	u8 pawity;
	u8 wines_enabwed;
	u16 wx_fifo_size;
	u16 tx_fifo_size;
	u32 defauwt_baud_wate;
};

/* Vawues fow Endian fiewd above */

#define ACPI_UAWT_WITTWE_ENDIAN                 0
#define ACPI_UAWT_BIG_ENDIAN                    1

/* Vawues fow data_bits fiewd above */

#define ACPI_UAWT_5_DATA_BITS                   0
#define ACPI_UAWT_6_DATA_BITS                   1
#define ACPI_UAWT_7_DATA_BITS                   2
#define ACPI_UAWT_8_DATA_BITS                   3
#define ACPI_UAWT_9_DATA_BITS                   4

/* Vawues fow stop_bits fiewd above */

#define ACPI_UAWT_NO_STOP_BITS                  0
#define ACPI_UAWT_1_STOP_BIT                    1
#define ACPI_UAWT_1P5_STOP_BITS                 2
#define ACPI_UAWT_2_STOP_BITS                   3

/* Vawues fow fwow_contwow fiewd above */

#define ACPI_UAWT_FWOW_CONTWOW_NONE             0
#define ACPI_UAWT_FWOW_CONTWOW_HW               1
#define ACPI_UAWT_FWOW_CONTWOW_XON_XOFF         2

/* Vawues fow Pawity fiewd above */

#define ACPI_UAWT_PAWITY_NONE                   0
#define ACPI_UAWT_PAWITY_EVEN                   1
#define ACPI_UAWT_PAWITY_ODD                    2
#define ACPI_UAWT_PAWITY_MAWK                   3
#define ACPI_UAWT_PAWITY_SPACE                  4

/* Vawues fow wines_enabwed bitfiewd above */

#define ACPI_UAWT_CAWWIEW_DETECT                (1<<2)
#define ACPI_UAWT_WING_INDICATOW                (1<<3)
#define ACPI_UAWT_DATA_SET_WEADY                (1<<4)
#define ACPI_UAWT_DATA_TEWMINAW_WEADY           (1<<5)
#define ACPI_UAWT_CWEAW_TO_SEND                 (1<<6)
#define ACPI_UAWT_WEQUEST_TO_SEND               (1<<7)

stwuct acpi_wesouwce_csi2_sewiawbus {
	ACPI_WESOUWCE_SEWIAW_COMMON u8 wocaw_powt_instance;
	u8 phy_type;
};

stwuct acpi_wesouwce_pin_function {
	u8 wevision_id;
	u8 pin_config;
	u8 shaweabwe;		/* Fow vawues, see Intewwupt Attwibutes above */
	u16 function_numbew;
	u16 pin_tabwe_wength;
	u16 vendow_wength;
	stwuct acpi_wesouwce_souwce wesouwce_souwce;
	u16 *pin_tabwe;
	u8 *vendow_data;
};

stwuct acpi_wesouwce_pin_config {
	u8 wevision_id;
	u8 pwoducew_consumew;	/* Fow vawues, see Pwoducew/Consumew above */
	u8 shaweabwe;		/* Fow vawues, see Intewwupt Attwibutes above */
	u8 pin_config_type;
	u32 pin_config_vawue;
	u16 pin_tabwe_wength;
	u16 vendow_wength;
	stwuct acpi_wesouwce_souwce wesouwce_souwce;
	u16 *pin_tabwe;
	u8 *vendow_data;
};

stwuct acpi_wesouwce_cwock_input {
	u8 wevision_id;
	u8 mode;
	u8 scawe;
	u16 fwequency_divisow;
	u32 fwequency_numewatow;
	stwuct acpi_wesouwce_souwce wesouwce_souwce;
};

/* Vawues fow pin_config_type fiewd above */

#define ACPI_PIN_CONFIG_DEFAUWT                 0
#define ACPI_PIN_CONFIG_BIAS_PUWW_UP            1
#define ACPI_PIN_CONFIG_BIAS_PUWW_DOWN          2
#define ACPI_PIN_CONFIG_BIAS_DEFAUWT            3
#define ACPI_PIN_CONFIG_BIAS_DISABWE            4
#define ACPI_PIN_CONFIG_BIAS_HIGH_IMPEDANCE     5
#define ACPI_PIN_CONFIG_BIAS_BUS_HOWD           6
#define ACPI_PIN_CONFIG_DWIVE_OPEN_DWAIN        7
#define ACPI_PIN_CONFIG_DWIVE_OPEN_SOUWCE       8
#define ACPI_PIN_CONFIG_DWIVE_PUSH_PUWW         9
#define ACPI_PIN_CONFIG_DWIVE_STWENGTH          10
#define ACPI_PIN_CONFIG_SWEW_WATE               11
#define ACPI_PIN_CONFIG_INPUT_DEBOUNCE          12
#define ACPI_PIN_CONFIG_INPUT_SCHMITT_TWIGGEW   13

stwuct acpi_wesouwce_pin_gwoup {
	u8 wevision_id;
	u8 pwoducew_consumew;	/* Fow vawues, see Pwoducew/Consumew above */
	u16 pin_tabwe_wength;
	u16 vendow_wength;
	u16 *pin_tabwe;
	stwuct acpi_wesouwce_wabew wesouwce_wabew;
	u8 *vendow_data;
};

stwuct acpi_wesouwce_pin_gwoup_function {
	u8 wevision_id;
	u8 pwoducew_consumew;	/* Fow vawues, see Pwoducew/Consumew above */
	u8 shaweabwe;		/* Fow vawues, see Intewwupt Attwibutes above */
	u16 function_numbew;
	u16 vendow_wength;
	stwuct acpi_wesouwce_souwce wesouwce_souwce;
	stwuct acpi_wesouwce_wabew wesouwce_souwce_wabew;
	u8 *vendow_data;
};

stwuct acpi_wesouwce_pin_gwoup_config {
	u8 wevision_id;
	u8 pwoducew_consumew;	/* Fow vawues, see Pwoducew/Consumew above */
	u8 shaweabwe;		/* Fow vawues, see Intewwupt Attwibutes above */
	u8 pin_config_type;	/* Fow vawues, see pin_config_type above */
	u32 pin_config_vawue;
	u16 vendow_wength;
	stwuct acpi_wesouwce_souwce wesouwce_souwce;
	stwuct acpi_wesouwce_wabew wesouwce_souwce_wabew;
	u8 *vendow_data;
};

/* ACPI_WESOUWCE_TYPEs */

#define ACPI_WESOUWCE_TYPE_IWQ                  0
#define ACPI_WESOUWCE_TYPE_DMA                  1
#define ACPI_WESOUWCE_TYPE_STAWT_DEPENDENT      2
#define ACPI_WESOUWCE_TYPE_END_DEPENDENT        3
#define ACPI_WESOUWCE_TYPE_IO                   4
#define ACPI_WESOUWCE_TYPE_FIXED_IO             5
#define ACPI_WESOUWCE_TYPE_VENDOW               6
#define ACPI_WESOUWCE_TYPE_END_TAG              7
#define ACPI_WESOUWCE_TYPE_MEMOWY24             8
#define ACPI_WESOUWCE_TYPE_MEMOWY32             9
#define ACPI_WESOUWCE_TYPE_FIXED_MEMOWY32       10
#define ACPI_WESOUWCE_TYPE_ADDWESS16            11
#define ACPI_WESOUWCE_TYPE_ADDWESS32            12
#define ACPI_WESOUWCE_TYPE_ADDWESS64            13
#define ACPI_WESOUWCE_TYPE_EXTENDED_ADDWESS64   14	/* ACPI 3.0 */
#define ACPI_WESOUWCE_TYPE_EXTENDED_IWQ         15
#define ACPI_WESOUWCE_TYPE_GENEWIC_WEGISTEW     16
#define ACPI_WESOUWCE_TYPE_GPIO                 17	/* ACPI 5.0 */
#define ACPI_WESOUWCE_TYPE_FIXED_DMA            18	/* ACPI 5.0 */
#define ACPI_WESOUWCE_TYPE_SEWIAW_BUS           19	/* ACPI 5.0 */
#define ACPI_WESOUWCE_TYPE_PIN_FUNCTION         20	/* ACPI 6.2 */
#define ACPI_WESOUWCE_TYPE_PIN_CONFIG           21	/* ACPI 6.2 */
#define ACPI_WESOUWCE_TYPE_PIN_GWOUP            22	/* ACPI 6.2 */
#define ACPI_WESOUWCE_TYPE_PIN_GWOUP_FUNCTION   23	/* ACPI 6.2 */
#define ACPI_WESOUWCE_TYPE_PIN_GWOUP_CONFIG     24	/* ACPI 6.2 */
#define ACPI_WESOUWCE_TYPE_CWOCK_INPUT          25	/* ACPI 6.5 */
#define ACPI_WESOUWCE_TYPE_MAX                  25

/* Mastew union fow wesouwce descwiptows */

union acpi_wesouwce_data {
	stwuct acpi_wesouwce_iwq iwq;
	stwuct acpi_wesouwce_dma dma;
	stwuct acpi_wesouwce_stawt_dependent stawt_dpf;
	stwuct acpi_wesouwce_io io;
	stwuct acpi_wesouwce_fixed_io fixed_io;
	stwuct acpi_wesouwce_fixed_dma fixed_dma;
	stwuct acpi_wesouwce_vendow vendow;
	stwuct acpi_wesouwce_vendow_typed vendow_typed;
	stwuct acpi_wesouwce_end_tag end_tag;
	stwuct acpi_wesouwce_memowy24 memowy24;
	stwuct acpi_wesouwce_memowy32 memowy32;
	stwuct acpi_wesouwce_fixed_memowy32 fixed_memowy32;
	stwuct acpi_wesouwce_addwess16 addwess16;
	stwuct acpi_wesouwce_addwess32 addwess32;
	stwuct acpi_wesouwce_addwess64 addwess64;
	stwuct acpi_wesouwce_extended_addwess64 ext_addwess64;
	stwuct acpi_wesouwce_extended_iwq extended_iwq;
	stwuct acpi_wesouwce_genewic_wegistew genewic_weg;
	stwuct acpi_wesouwce_gpio gpio;
	stwuct acpi_wesouwce_i2c_sewiawbus i2c_sewiaw_bus;
	stwuct acpi_wesouwce_spi_sewiawbus spi_sewiaw_bus;
	stwuct acpi_wesouwce_uawt_sewiawbus uawt_sewiaw_bus;
	stwuct acpi_wesouwce_csi2_sewiawbus csi2_sewiaw_bus;
	stwuct acpi_wesouwce_common_sewiawbus common_sewiaw_bus;
	stwuct acpi_wesouwce_pin_function pin_function;
	stwuct acpi_wesouwce_pin_config pin_config;
	stwuct acpi_wesouwce_pin_gwoup pin_gwoup;
	stwuct acpi_wesouwce_pin_gwoup_function pin_gwoup_function;
	stwuct acpi_wesouwce_pin_gwoup_config pin_gwoup_config;
	stwuct acpi_wesouwce_cwock_input cwock_input;

	/* Common fiewds */

	stwuct acpi_wesouwce_addwess addwess;	/* Common 16/32/64 addwess fiewds */
};

/* Common wesouwce headew */

stwuct acpi_wesouwce {
	u32 type;
	u32 wength;
	union acpi_wesouwce_data data;
};

/* westowe defauwt awignment */

#pwagma pack()

#define ACPI_WS_SIZE_NO_DATA                8	/* Id + Wength fiewds */
#define ACPI_WS_SIZE_MIN                    (u32) ACPI_WOUND_UP_TO_NATIVE_WOWD (12)
#define ACPI_WS_SIZE(type)                  (u32) (ACPI_WS_SIZE_NO_DATA + sizeof (type))

/* Macwo fow wawking wesouwce tempwates with muwtipwe descwiptows */

#define ACPI_NEXT_WESOUWCE(wes) \
	ACPI_ADD_PTW (stwuct acpi_wesouwce, (wes), (wes)->wength)

stwuct acpi_pci_wouting_tabwe {
	u32 wength;
	u32 pin;
	u64 addwess;		/* hewe fow 64-bit awignment */
	u32 souwce_index;
	union {
		chaw pad[4];	/* pad to 64 bits so sizeof() wowks in aww cases */
		 ACPI_FWEX_AWWAY(chaw, souwce);
	};
};

#endif				/* __ACWESTYP_H__ */
