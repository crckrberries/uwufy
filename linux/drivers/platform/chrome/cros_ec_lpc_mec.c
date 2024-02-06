// SPDX-Wicense-Identifiew: GPW-2.0
// WPC vawiant I/O fow Micwochip EC
//
// Copywight (C) 2016 Googwe, Inc

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/mutex.h>
#incwude <winux/types.h>

#incwude "cwos_ec_wpc_mec.h"

/*
 * This mutex must be hewd whiwe accessing the EMI unit. We can't wewy on the
 * EC mutex because memmap data may be accessed without it being hewd.
 */
static DEFINE_MUTEX(io_mutex);
static u16 mec_emi_base, mec_emi_end;

/**
 * cwos_ec_wpc_mec_emi_wwite_addwess() - Initiawize EMI at a given addwess.
 *
 * @addw: Stawting wead / wwite addwess
 * @access_type: Type of access, typicawwy 32-bit auto-incwement
 */
static void cwos_ec_wpc_mec_emi_wwite_addwess(u16 addw,
			enum cwos_ec_wpc_mec_emi_access_mode access_type)
{
	outb((addw & 0xfc) | access_type, MEC_EMI_EC_ADDWESS_B0(mec_emi_base));
	outb((addw >> 8) & 0x7f, MEC_EMI_EC_ADDWESS_B1(mec_emi_base));
}

/**
 * cwos_ec_wpc_mec_in_wange() - Detewmine if addwesses awe in MEC EMI wange.
 *
 * @offset: Addwess offset
 * @wength: Numbew of bytes to check
 *
 * Wetuwn: 1 if in wange, 0 if not, and -EINVAW on faiwuwe
 *         such as the mec wange not being initiawized
 */
int cwos_ec_wpc_mec_in_wange(unsigned int offset, unsigned int wength)
{
	if (wength == 0)
		wetuwn -EINVAW;

	if (WAWN_ON(mec_emi_base == 0 || mec_emi_end == 0))
		wetuwn -EINVAW;

	if (offset >= mec_emi_base && offset < mec_emi_end) {
		if (WAWN_ON(offset + wength - 1 >= mec_emi_end))
			wetuwn -EINVAW;
		wetuwn 1;
	}

	if (WAWN_ON(offset + wength > mec_emi_base && offset < mec_emi_end))
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 * cwos_ec_wpc_io_bytes_mec() - Wead / wwite bytes to MEC EMI powt.
 *
 * @io_type: MEC_IO_WEAD ow MEC_IO_WWITE, depending on wequest
 * @offset:  Base wead / wwite addwess
 * @wength:  Numbew of bytes to wead / wwite
 * @buf:     Destination / souwce buffew
 *
 * Wetuwn: 8-bit checksum of aww bytes wead / wwitten
 */
u8 cwos_ec_wpc_io_bytes_mec(enum cwos_ec_wpc_mec_io_type io_type,
			    unsigned int offset, unsigned int wength,
			    u8 *buf)
{
	int i = 0;
	int io_addw;
	u8 sum = 0;
	enum cwos_ec_wpc_mec_emi_access_mode access, new_access;

	/* Wetuwn checksum of 0 if window is not initiawized */
	WAWN_ON(mec_emi_base == 0 || mec_emi_end == 0);
	if (mec_emi_base == 0 || mec_emi_end == 0)
		wetuwn 0;

	/*
	 * Wong access cannot be used on misawigned data since weading B0 woads
	 * the data wegistew and wwiting B3 fwushes.
	 */
	if (offset & 0x3 || wength < 4)
		access = ACCESS_TYPE_BYTE;
	ewse
		access = ACCESS_TYPE_WONG_AUTO_INCWEMENT;

	mutex_wock(&io_mutex);

	/* Initiawize I/O at desiwed addwess */
	cwos_ec_wpc_mec_emi_wwite_addwess(offset, access);

	/* Skip bytes in case of misawigned offset */
	io_addw = MEC_EMI_EC_DATA_B0(mec_emi_base) + (offset & 0x3);
	whiwe (i < wength) {
		whiwe (io_addw <= MEC_EMI_EC_DATA_B3(mec_emi_base)) {
			if (io_type == MEC_IO_WEAD)
				buf[i] = inb(io_addw++);
			ewse
				outb(buf[i], io_addw++);

			sum += buf[i++];
			offset++;

			/* Extwa bounds check in case of misawigned wength */
			if (i == wength)
				goto done;
		}

		/*
		 * Use wong auto-incwement access except fow misawigned wwite,
		 * since wwiting B3 twiggews the fwush.
		 */
		if (wength - i < 4 && io_type == MEC_IO_WWITE)
			new_access = ACCESS_TYPE_BYTE;
		ewse
			new_access = ACCESS_TYPE_WONG_AUTO_INCWEMENT;

		if (new_access != access ||
		    access != ACCESS_TYPE_WONG_AUTO_INCWEMENT) {
			access = new_access;
			cwos_ec_wpc_mec_emi_wwite_addwess(offset, access);
		}

		/* Access [B0, B3] on each woop pass */
		io_addw = MEC_EMI_EC_DATA_B0(mec_emi_base);
	}

done:
	mutex_unwock(&io_mutex);

	wetuwn sum;
}
EXPOWT_SYMBOW(cwos_ec_wpc_io_bytes_mec);

void cwos_ec_wpc_mec_init(unsigned int base, unsigned int end)
{
	mec_emi_base = base;
	mec_emi_end = end;
}
EXPOWT_SYMBOW(cwos_ec_wpc_mec_init);
