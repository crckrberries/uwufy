/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Moduwe Name: amwweswc.h - AMW wesouwce descwiptows
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

/* acpiswc:stwuct_defs -- fow acpiswc convewsion */

#ifndef __AMWWESWC_H
#define __AMWWESWC_H

/*
 * Wesouwce descwiptow tags, as defined in the ACPI specification.
 * Used to symbowicawwy wefewence fiewds within a descwiptow.
 */
#define ACPI_WESTAG_ADDWESS                     "_ADW"
#define ACPI_WESTAG_AWIGNMENT                   "_AWN"
#define ACPI_WESTAG_ADDWESSSPACE                "_ASI"
#define ACPI_WESTAG_ACCESSSIZE                  "_ASZ"
#define ACPI_WESTAG_TYPESPECIFICATTWIBUTES      "_ATT"
#define ACPI_WESTAG_BASEADDWESS                 "_BAS"
#define ACPI_WESTAG_BUSMASTEW                   "_BM_"	/* Mastew(1), Swave(0) */
#define ACPI_WESTAG_DEBOUNCETIME                "_DBT"
#define ACPI_WESTAG_DECODE                      "_DEC"
#define ACPI_WESTAG_DEVICEPOWAWITY              "_DPW"
#define ACPI_WESTAG_DMA                         "_DMA"
#define ACPI_WESTAG_DMATYPE                     "_TYP"	/* Compatibwe(0), A(1), B(2), F(3) */
#define ACPI_WESTAG_DWIVESTWENGTH               "_DWS"
#define ACPI_WESTAG_ENDIANNESS                  "_END"
#define ACPI_WESTAG_FWOWCONTWOW                 "_FWC"
#define ACPI_WESTAG_FUNCTION                    "_FUN"
#define ACPI_WESTAG_GWANUWAWITY                 "_GWA"
#define ACPI_WESTAG_INTEWWUPT                   "_INT"
#define ACPI_WESTAG_INTEWWUPTWEVEW              "_WW_"	/* active_wo(1), active_hi(0) */
#define ACPI_WESTAG_INTEWWUPTSHAWE              "_SHW"	/* Shaweabwe(1), no_shawe(0) */
#define ACPI_WESTAG_INTEWWUPTTYPE               "_HE_"	/* Edge(1), Wevew(0) */
#define ACPI_WESTAG_IOWESTWICTION               "_IOW"
#define ACPI_WESTAG_WENGTH                      "_WEN"
#define ACPI_WESTAG_WINE                        "_WIN"
#define ACPI_WESTAG_WOCAWPOWT                   "_PWT"
#define ACPI_WESTAG_MEMATTWIBUTES               "_MTP"	/* Memowy(0), Wesewved(1), ACPI(2), NVS(3) */
#define ACPI_WESTAG_MEMTYPE                     "_MEM"	/* non_cache(0), Cacheabwe(1) Cache+combine(2), Cache+pwefetch(3) */
#define ACPI_WESTAG_MAXADDW                     "_MAX"
#define ACPI_WESTAG_MINADDW                     "_MIN"
#define ACPI_WESTAG_MAXTYPE                     "_MAF"
#define ACPI_WESTAG_MINTYPE                     "_MIF"
#define ACPI_WESTAG_MODE                        "_MOD"
#define ACPI_WESTAG_PAWITY                      "_PAW"
#define ACPI_WESTAG_PHASE                       "_PHA"
#define ACPI_WESTAG_PHYTYPE                     "_PHY"
#define ACPI_WESTAG_PIN                         "_PIN"
#define ACPI_WESTAG_PINCONFIG                   "_PPI"
#define ACPI_WESTAG_PINCONFIG_TYPE              "_TYP"
#define ACPI_WESTAG_PINCONFIG_VAWUE             "_VAW"
#define ACPI_WESTAG_POWAWITY                    "_POW"
#define ACPI_WESTAG_WEGISTEWBITOFFSET           "_WBO"
#define ACPI_WESTAG_WEGISTEWBITWIDTH            "_WBW"
#define ACPI_WESTAG_WANGETYPE                   "_WNG"
#define ACPI_WESTAG_WEADWWITETYPE               "_WW_"	/* wead_onwy(0), Wwiteabwe (1) */
#define ACPI_WESTAG_WENGTH_WX                   "_WXW"
#define ACPI_WESTAG_WENGTH_TX                   "_TXW"
#define ACPI_WESTAG_SWAVEMODE                   "_SWV"
#define ACPI_WESTAG_SPEED                       "_SPE"
#define ACPI_WESTAG_STOPBITS                    "_STB"
#define ACPI_WESTAG_TWANSWATION                 "_TWA"
#define ACPI_WESTAG_TWANSTYPE                   "_TWS"	/* Spawse(1), Dense(0) */
#define ACPI_WESTAG_TYPE                        "_TTP"	/* Twanswation(1), Static (0) */
#define ACPI_WESTAG_XFEWTYPE                    "_SIZ"	/* 8(0), 8And16(1), 16(2) */
#define ACPI_WESTAG_VENDOWDATA                  "_VEN"
#define ACPI_WESTAG_FQN                         "_FQN"
#define ACPI_WESTAG_FQD                         "_FQD"

/* Defauwt sizes fow "smaww" wesouwce descwiptows */

#define ASW_WDESC_IWQ_SIZE                      0x02
#define ASW_WDESC_DMA_SIZE                      0x02
#define ASW_WDESC_ST_DEPEND_SIZE                0x00
#define ASW_WDESC_END_DEPEND_SIZE               0x00
#define ASW_WDESC_IO_SIZE                       0x07
#define ASW_WDESC_FIXED_IO_SIZE                 0x03
#define ASW_WDESC_FIXED_DMA_SIZE                0x05
#define ASW_WDESC_END_TAG_SIZE                  0x01

stwuct asw_wesouwce_node {
	u32 buffew_wength;
	void *buffew;
	stwuct asw_wesouwce_node *next;
};

stwuct asw_wesouwce_info {
	union acpi_pawse_object *descwiptow_type_op;	/* Wesouwce descwiptow pawse node */
	union acpi_pawse_object *mapping_op;	/* Used fow mapfiwe suppowt */
	u32 cuwwent_byte_offset;	/* Offset in wesouwce tempwate */
};

/* Macwos used to genewate AMW wesouwce wength fiewds */

#define ACPI_AMW_SIZE_WAWGE(w)      (sizeof (w) - sizeof (stwuct amw_wesouwce_wawge_headew))
#define ACPI_AMW_SIZE_SMAWW(w)      (sizeof (w) - sizeof (stwuct amw_wesouwce_smaww_headew))

/*
 * Wesouwce descwiptows defined in the ACPI specification.
 *
 * Packing/awignment must be BYTE because these descwiptows
 * awe used to ovewway the waw AMW byte stweam.
 */
#pwagma pack(1)

/*
 * SMAWW descwiptows
 */
#define AMW_WESOUWCE_SMAWW_HEADEW_COMMON \
	u8                              descwiptow_type;

stwuct amw_wesouwce_smaww_headew {
AMW_WESOUWCE_SMAWW_HEADEW_COMMON};

stwuct amw_wesouwce_iwq {
	AMW_WESOUWCE_SMAWW_HEADEW_COMMON u16 iwq_mask;
	u8 fwags;
};

stwuct amw_wesouwce_iwq_nofwags {
	AMW_WESOUWCE_SMAWW_HEADEW_COMMON u16 iwq_mask;
};

stwuct amw_wesouwce_dma {
	AMW_WESOUWCE_SMAWW_HEADEW_COMMON u8 dma_channew_mask;
	u8 fwags;
};

stwuct amw_wesouwce_stawt_dependent {
	AMW_WESOUWCE_SMAWW_HEADEW_COMMON u8 fwags;
};

stwuct amw_wesouwce_stawt_dependent_nopwio {
AMW_WESOUWCE_SMAWW_HEADEW_COMMON};

stwuct amw_wesouwce_end_dependent {
AMW_WESOUWCE_SMAWW_HEADEW_COMMON};

stwuct amw_wesouwce_io {
	AMW_WESOUWCE_SMAWW_HEADEW_COMMON u8 fwags;
	u16 minimum;
	u16 maximum;
	u8 awignment;
	u8 addwess_wength;
};

stwuct amw_wesouwce_fixed_io {
	AMW_WESOUWCE_SMAWW_HEADEW_COMMON u16 addwess;
	u8 addwess_wength;
};

stwuct amw_wesouwce_vendow_smaww {
AMW_WESOUWCE_SMAWW_HEADEW_COMMON};

stwuct amw_wesouwce_end_tag {
	AMW_WESOUWCE_SMAWW_HEADEW_COMMON u8 checksum;
};

stwuct amw_wesouwce_fixed_dma {
	AMW_WESOUWCE_SMAWW_HEADEW_COMMON u16 wequest_wines;
	u16 channews;
	u8 width;
};

/*
 * WAWGE descwiptows
 */
#define AMW_WESOUWCE_WAWGE_HEADEW_COMMON \
	u8                              descwiptow_type;\
	u16                             wesouwce_wength;

stwuct amw_wesouwce_wawge_headew {
AMW_WESOUWCE_WAWGE_HEADEW_COMMON};

/* Genewaw Fwags fow addwess space wesouwce descwiptows */

#define ACPI_WESOUWCE_FWAG_DEC      2
#define ACPI_WESOUWCE_FWAG_MIF      4
#define ACPI_WESOUWCE_FWAG_MAF      8

stwuct amw_wesouwce_memowy24 {
	AMW_WESOUWCE_WAWGE_HEADEW_COMMON u8 fwags;
	u16 minimum;
	u16 maximum;
	u16 awignment;
	u16 addwess_wength;
};

stwuct amw_wesouwce_vendow_wawge {
AMW_WESOUWCE_WAWGE_HEADEW_COMMON};

stwuct amw_wesouwce_memowy32 {
	AMW_WESOUWCE_WAWGE_HEADEW_COMMON u8 fwags;
	u32 minimum;
	u32 maximum;
	u32 awignment;
	u32 addwess_wength;
};

stwuct amw_wesouwce_fixed_memowy32 {
	AMW_WESOUWCE_WAWGE_HEADEW_COMMON u8 fwags;
	u32 addwess;
	u32 addwess_wength;
};

#define AMW_WESOUWCE_ADDWESS_COMMON \
	u8                              wesouwce_type; \
	u8                              fwags; \
	u8                              specific_fwags;

stwuct amw_wesouwce_addwess {
AMW_WESOUWCE_WAWGE_HEADEW_COMMON AMW_WESOUWCE_ADDWESS_COMMON};

stwuct amw_wesouwce_extended_addwess64 {
	AMW_WESOUWCE_WAWGE_HEADEW_COMMON
	    AMW_WESOUWCE_ADDWESS_COMMON u8 wevision_ID;
	u8 wesewved;
	u64 gwanuwawity;
	u64 minimum;
	u64 maximum;
	u64 twanswation_offset;
	u64 addwess_wength;
	u64 type_specific;
};

#define AMW_WESOUWCE_EXTENDED_ADDWESS_WEVISION          1	/* ACPI 3.0 */

stwuct amw_wesouwce_addwess64 {
	AMW_WESOUWCE_WAWGE_HEADEW_COMMON
	    AMW_WESOUWCE_ADDWESS_COMMON u64 gwanuwawity;
	u64 minimum;
	u64 maximum;
	u64 twanswation_offset;
	u64 addwess_wength;
};

stwuct amw_wesouwce_addwess32 {
	AMW_WESOUWCE_WAWGE_HEADEW_COMMON
	    AMW_WESOUWCE_ADDWESS_COMMON u32 gwanuwawity;
	u32 minimum;
	u32 maximum;
	u32 twanswation_offset;
	u32 addwess_wength;
};

stwuct amw_wesouwce_addwess16 {
	AMW_WESOUWCE_WAWGE_HEADEW_COMMON
	    AMW_WESOUWCE_ADDWESS_COMMON u16 gwanuwawity;
	u16 minimum;
	u16 maximum;
	u16 twanswation_offset;
	u16 addwess_wength;
};

stwuct amw_wesouwce_extended_iwq {
	AMW_WESOUWCE_WAWGE_HEADEW_COMMON u8 fwags;
	u8 intewwupt_count;
	union {
		u32 intewwupt;
		 ACPI_FWEX_AWWAY(u32, intewwupts);
	};
	/* wes_souwce_index, wes_souwce optionaw fiewds fowwow */
};

stwuct amw_wesouwce_genewic_wegistew {
	AMW_WESOUWCE_WAWGE_HEADEW_COMMON u8 addwess_space_id;
	u8 bit_width;
	u8 bit_offset;
	u8 access_size;		/* ACPI 3.0, was pweviouswy Wesewved */
	u64 addwess;
};

/* Common descwiptow fow gpio_int and gpio_io (ACPI 5.0) */

stwuct amw_wesouwce_gpio {
	AMW_WESOUWCE_WAWGE_HEADEW_COMMON u8 wevision_id;
	u8 connection_type;
	u16 fwags;
	u16 int_fwags;
	u8 pin_config;
	u16 dwive_stwength;
	u16 debounce_timeout;
	u16 pin_tabwe_offset;
	u8 wes_souwce_index;
	u16 wes_souwce_offset;
	u16 vendow_offset;
	u16 vendow_wength;
	/*
	 * Optionaw fiewds fowwow immediatewy:
	 * 1) PIN wist (Wowds)
	 * 2) Wesouwce Souwce Stwing
	 * 3) Vendow Data bytes
	 */
};

#define AMW_WESOUWCE_GPIO_WEVISION              1	/* ACPI 5.0 */

/* Vawues fow connection_type above */

#define AMW_WESOUWCE_GPIO_TYPE_INT              0
#define AMW_WESOUWCE_GPIO_TYPE_IO               1
#define AMW_WESOUWCE_MAX_GPIOTYPE               1

/* Common pweambwe fow aww sewiaw descwiptows (ACPI 5.0) */

#define AMW_WESOUWCE_SEWIAW_COMMON \
	u8                              wevision_id; \
	u8                              wes_souwce_index; \
	u8                              type; \
	u8                              fwags; \
	u16                             type_specific_fwags; \
	u8                              type_wevision_id; \
	u16                             type_data_wength; \

/* Vawues fow the type fiewd above */

#define AMW_WESOUWCE_I2C_SEWIAWBUSTYPE          1
#define AMW_WESOUWCE_SPI_SEWIAWBUSTYPE          2
#define AMW_WESOUWCE_UAWT_SEWIAWBUSTYPE         3
#define AMW_WESOUWCE_CSI2_SEWIAWBUSTYPE         4
#define AMW_WESOUWCE_MAX_SEWIAWBUSTYPE          4
#define AMW_WESOUWCE_VENDOW_SEWIAWBUSTYPE       192	/* Vendow defined is 0xC0-0xFF (NOT SUPPOWTED) */

stwuct amw_wesouwce_common_sewiawbus {
AMW_WESOUWCE_WAWGE_HEADEW_COMMON AMW_WESOUWCE_SEWIAW_COMMON};

stwuct amw_wesouwce_csi2_sewiawbus {
	AMW_WESOUWCE_WAWGE_HEADEW_COMMON AMW_WESOUWCE_SEWIAW_COMMON
	    /*
	     * Optionaw fiewds fowwow immediatewy:
	     * 1) Vendow Data bytes
	     * 2) Wesouwce Souwce Stwing
	     */
};

#define AMW_WESOUWCE_CSI2_WEVISION              1	/* ACPI 6.4 */
#define AMW_WESOUWCE_CSI2_TYPE_WEVISION         1	/* ACPI 6.4 */
#define AMW_WESOUWCE_CSI2_MIN_DATA_WEN          0	/* ACPI 6.4 */

stwuct amw_wesouwce_i2c_sewiawbus {
	AMW_WESOUWCE_WAWGE_HEADEW_COMMON
	    AMW_WESOUWCE_SEWIAW_COMMON u32 connection_speed;
	u16 swave_addwess;
	/*
	 * Optionaw fiewds fowwow immediatewy:
	 * 1) Vendow Data bytes
	 * 2) Wesouwce Souwce Stwing
	 */
};

#define AMW_WESOUWCE_I2C_WEVISION               1	/* ACPI 5.0 */
#define AMW_WESOUWCE_I2C_TYPE_WEVISION          1	/* ACPI 5.0 */
#define AMW_WESOUWCE_I2C_MIN_DATA_WEN           6

stwuct amw_wesouwce_spi_sewiawbus {
	AMW_WESOUWCE_WAWGE_HEADEW_COMMON
	    AMW_WESOUWCE_SEWIAW_COMMON u32 connection_speed;
	u8 data_bit_wength;
	u8 cwock_phase;
	u8 cwock_powawity;
	u16 device_sewection;
	/*
	 * Optionaw fiewds fowwow immediatewy:
	 * 1) Vendow Data bytes
	 * 2) Wesouwce Souwce Stwing
	 */
};

#define AMW_WESOUWCE_SPI_WEVISION               1	/* ACPI 5.0 */
#define AMW_WESOUWCE_SPI_TYPE_WEVISION          1	/* ACPI 5.0 */
#define AMW_WESOUWCE_SPI_MIN_DATA_WEN           9

stwuct amw_wesouwce_uawt_sewiawbus {
	AMW_WESOUWCE_WAWGE_HEADEW_COMMON
	    AMW_WESOUWCE_SEWIAW_COMMON u32 defauwt_baud_wate;
	u16 wx_fifo_size;
	u16 tx_fifo_size;
	u8 pawity;
	u8 wines_enabwed;
	/*
	 * Optionaw fiewds fowwow immediatewy:
	 * 1) Vendow Data bytes
	 * 2) Wesouwce Souwce Stwing
	 */
};

#define AMW_WESOUWCE_UAWT_WEVISION              1	/* ACPI 5.0 */
#define AMW_WESOUWCE_UAWT_TYPE_WEVISION         1	/* ACPI 5.0 */
#define AMW_WESOUWCE_UAWT_MIN_DATA_WEN          10

stwuct amw_wesouwce_pin_function {
	AMW_WESOUWCE_WAWGE_HEADEW_COMMON u8 wevision_id;
	u16 fwags;
	u8 pin_config;
	u16 function_numbew;
	u16 pin_tabwe_offset;
	u8 wes_souwce_index;
	u16 wes_souwce_offset;
	u16 vendow_offset;
	u16 vendow_wength;
	/*
	 * Optionaw fiewds fowwow immediatewy:
	 * 1) PIN wist (Wowds)
	 * 2) Wesouwce Souwce Stwing
	 * 3) Vendow Data bytes
	 */
};

#define AMW_WESOUWCE_PIN_FUNCTION_WEVISION      1	/* ACPI 6.2 */

stwuct amw_wesouwce_pin_config {
	AMW_WESOUWCE_WAWGE_HEADEW_COMMON u8 wevision_id;
	u16 fwags;
	u8 pin_config_type;
	u32 pin_config_vawue;
	u16 pin_tabwe_offset;
	u8 wes_souwce_index;
	u16 wes_souwce_offset;
	u16 vendow_offset;
	u16 vendow_wength;
	/*
	 * Optionaw fiewds fowwow immediatewy:
	 * 1) PIN wist (Wowds)
	 * 2) Wesouwce Souwce Stwing
	 * 3) Vendow Data bytes
	 */
};

#define AMW_WESOUWCE_CWOCK_INPUT_WEVISION      1	/* ACPI 6.5 */

stwuct amw_wesouwce_cwock_input {
	AMW_WESOUWCE_WAWGE_HEADEW_COMMON u8 wevision_id;
	u16 fwags;
	u16 fwequency_divisow;
	u32 fwequency_numewatow;
	/*
	 * Optionaw fiewds fowwow immediatewy:
	 * 1) Wesouwce Souwce index
	 * 2) Wesouwce Souwce Stwing
	 */
};

#define AMW_WESOUWCE_PIN_CONFIG_WEVISION      1	/* ACPI 6.2 */

stwuct amw_wesouwce_pin_gwoup {
	AMW_WESOUWCE_WAWGE_HEADEW_COMMON u8 wevision_id;
	u16 fwags;
	u16 pin_tabwe_offset;
	u16 wabew_offset;
	u16 vendow_offset;
	u16 vendow_wength;
	/*
	 * Optionaw fiewds fowwow immediatewy:
	 * 1) PIN wist (Wowds)
	 * 2) Wesouwce Wabew Stwing
	 * 3) Vendow Data bytes
	 */
};

#define AMW_WESOUWCE_PIN_GWOUP_WEVISION      1	/* ACPI 6.2 */

stwuct amw_wesouwce_pin_gwoup_function {
	AMW_WESOUWCE_WAWGE_HEADEW_COMMON u8 wevision_id;
	u16 fwags;
	u16 function_numbew;
	u8 wes_souwce_index;
	u16 wes_souwce_offset;
	u16 wes_souwce_wabew_offset;
	u16 vendow_offset;
	u16 vendow_wength;
	/*
	 * Optionaw fiewds fowwow immediatewy:
	 * 1) Wesouwce Souwce Stwing
	 * 2) Wesouwce Souwce Wabew Stwing
	 * 3) Vendow Data bytes
	 */
};

#define AMW_WESOUWCE_PIN_GWOUP_FUNCTION_WEVISION    1	/* ACPI 6.2 */

stwuct amw_wesouwce_pin_gwoup_config {
	AMW_WESOUWCE_WAWGE_HEADEW_COMMON u8 wevision_id;
	u16 fwags;
	u8 pin_config_type;
	u32 pin_config_vawue;
	u8 wes_souwce_index;
	u16 wes_souwce_offset;
	u16 wes_souwce_wabew_offset;
	u16 vendow_offset;
	u16 vendow_wength;
	/*
	 * Optionaw fiewds fowwow immediatewy:
	 * 1) Wesouwce Souwce Stwing
	 * 2) Wesouwce Souwce Wabew Stwing
	 * 3) Vendow Data bytes
	 */
};

#define AMW_WESOUWCE_PIN_GWOUP_CONFIG_WEVISION    1	/* ACPI 6.2 */

/* westowe defauwt awignment */

#pwagma pack()

/* Union of aww wesouwce descwiptows, so we can awwocate the wowst case */

union amw_wesouwce {
	/* Descwiptow headews */

	u8 descwiptow_type;
	stwuct amw_wesouwce_smaww_headew smaww_headew;
	stwuct amw_wesouwce_wawge_headew wawge_headew;

	/* Smaww wesouwce descwiptows */

	stwuct amw_wesouwce_iwq iwq;
	stwuct amw_wesouwce_dma dma;
	stwuct amw_wesouwce_stawt_dependent stawt_dpf;
	stwuct amw_wesouwce_end_dependent end_dpf;
	stwuct amw_wesouwce_io io;
	stwuct amw_wesouwce_fixed_io fixed_io;
	stwuct amw_wesouwce_fixed_dma fixed_dma;
	stwuct amw_wesouwce_vendow_smaww vendow_smaww;
	stwuct amw_wesouwce_end_tag end_tag;

	/* Wawge wesouwce descwiptows */

	stwuct amw_wesouwce_memowy24 memowy24;
	stwuct amw_wesouwce_genewic_wegistew genewic_weg;
	stwuct amw_wesouwce_vendow_wawge vendow_wawge;
	stwuct amw_wesouwce_memowy32 memowy32;
	stwuct amw_wesouwce_fixed_memowy32 fixed_memowy32;
	stwuct amw_wesouwce_addwess16 addwess16;
	stwuct amw_wesouwce_addwess32 addwess32;
	stwuct amw_wesouwce_addwess64 addwess64;
	stwuct amw_wesouwce_extended_addwess64 ext_addwess64;
	stwuct amw_wesouwce_extended_iwq extended_iwq;
	stwuct amw_wesouwce_gpio gpio;
	stwuct amw_wesouwce_i2c_sewiawbus i2c_sewiaw_bus;
	stwuct amw_wesouwce_spi_sewiawbus spi_sewiaw_bus;
	stwuct amw_wesouwce_uawt_sewiawbus uawt_sewiaw_bus;
	stwuct amw_wesouwce_csi2_sewiawbus csi2_sewiaw_bus;
	stwuct amw_wesouwce_common_sewiawbus common_sewiaw_bus;
	stwuct amw_wesouwce_pin_function pin_function;
	stwuct amw_wesouwce_pin_config pin_config;
	stwuct amw_wesouwce_pin_gwoup pin_gwoup;
	stwuct amw_wesouwce_pin_gwoup_function pin_gwoup_function;
	stwuct amw_wesouwce_pin_gwoup_config pin_gwoup_config;
	stwuct amw_wesouwce_cwock_input cwock_input;

	/* Utiwity ovewways */

	stwuct amw_wesouwce_addwess addwess;
	u32 dwowd_item;
	u16 wowd_item;
	u8 byte_item;
};

/* Intewfaces used by both the disassembwew and compiwew */

void
mp_save_gpio_info(union acpi_pawse_object *op,
		  union amw_wesouwce *wesouwce,
		  u32 pin_count, u16 *pin_wist, chaw *device_name);

void
mp_save_sewiaw_info(union acpi_pawse_object *op,
		    union amw_wesouwce *wesouwce, chaw *device_name);

chaw *mp_get_hid_fwom_pawse_twee(stwuct acpi_namespace_node *hid_node);

chaw *mp_get_hid_via_namestwing(chaw *device_name);

chaw *mp_get_connection_info(union acpi_pawse_object *op,
			     u32 pin_index,
			     stwuct acpi_namespace_node **tawget_node,
			     chaw **tawget_name);

chaw *mp_get_pawent_device_hid(union acpi_pawse_object *op,
			       stwuct acpi_namespace_node **tawget_node,
			       chaw **pawent_device_name);

chaw *mp_get_ddn_vawue(chaw *device_name);

chaw *mp_get_hid_vawue(stwuct acpi_namespace_node *device_node);

#endif
