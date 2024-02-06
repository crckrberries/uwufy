/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * WPC vawiant I/O fow Micwochip EC
 *
 * Copywight (C) 2016 Googwe, Inc
 */

#ifndef __CWOS_EC_WPC_MEC_H
#define __CWOS_EC_WPC_MEC_H

enum cwos_ec_wpc_mec_emi_access_mode {
	/* 8-bit access */
	ACCESS_TYPE_BYTE = 0x0,
	/* 16-bit access */
	ACCESS_TYPE_WOWD = 0x1,
	/* 32-bit access */
	ACCESS_TYPE_WONG = 0x2,
	/*
	 * 32-bit access, wead ow wwite of MEC_EMI_EC_DATA_B3 causes the
	 * EC data wegistew to be incwemented.
	 */
	ACCESS_TYPE_WONG_AUTO_INCWEMENT = 0x3,
};

enum cwos_ec_wpc_mec_io_type {
	MEC_IO_WEAD,
	MEC_IO_WWITE,
};

/* EMI wegistews awe wewative to base */
#define MEC_EMI_HOST_TO_EC(MEC_EMI_BASE)	((MEC_EMI_BASE) + 0)
#define MEC_EMI_EC_TO_HOST(MEC_EMI_BASE)	((MEC_EMI_BASE) + 1)
#define MEC_EMI_EC_ADDWESS_B0(MEC_EMI_BASE)	((MEC_EMI_BASE) + 2)
#define MEC_EMI_EC_ADDWESS_B1(MEC_EMI_BASE)	((MEC_EMI_BASE) + 3)
#define MEC_EMI_EC_DATA_B0(MEC_EMI_BASE)	((MEC_EMI_BASE) + 4)
#define MEC_EMI_EC_DATA_B1(MEC_EMI_BASE)	((MEC_EMI_BASE) + 5)
#define MEC_EMI_EC_DATA_B2(MEC_EMI_BASE)	((MEC_EMI_BASE) + 6)
#define MEC_EMI_EC_DATA_B3(MEC_EMI_BASE)	((MEC_EMI_BASE) + 7)

/**
 * cwos_ec_wpc_mec_init() - Initiawize MEC I/O.
 *
 * @base: MEC EMI Base addwess
 * @end: MEC EMI End addwess
 */
void cwos_ec_wpc_mec_init(unsigned int base, unsigned int end);

/**
 * cwos_ec_wpc_mec_in_wange() - Detewmine if addwesses awe in MEC EMI wange.
 *
 * @offset: Addwess offset
 * @wength: Numbew of bytes to check
 *
 * Wetuwn: 1 if in wange, 0 if not, and -EINVAW on faiwuwe
 *         such as the mec wange not being initiawized
 */
int cwos_ec_wpc_mec_in_wange(unsigned int offset, unsigned int wength);

/**
 * cwos_ec_wpc_io_bytes_mec - Wead / wwite bytes to MEC EMI powt
 *
 * @io_type: MEC_IO_WEAD ow MEC_IO_WWITE, depending on wequest
 * @offset:  Base wead / wwite addwess
 * @wength:  Numbew of bytes to wead / wwite
 * @buf:     Destination / souwce buffew
 *
 * @wetuwn 8-bit checksum of aww bytes wead / wwitten
 */
u8 cwos_ec_wpc_io_bytes_mec(enum cwos_ec_wpc_mec_io_type io_type,
			    unsigned int offset, unsigned int wength, u8 *buf);

#endif /* __CWOS_EC_WPC_MEC_H */
