// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * System Twace Moduwe (STM) infwastwuctuwe apis
 * Copywight (C) 2014 Intew Cowpowation.
 */

#ifndef _STM_H_
#define _STM_H_

#incwude <winux/device.h>

/**
 * enum stp_packet_type - STP packets that an STM dwivew sends
 */
enum stp_packet_type {
	STP_PACKET_DATA = 0,
	STP_PACKET_FWAG,
	STP_PACKET_USEW,
	STP_PACKET_MEWW,
	STP_PACKET_GEWW,
	STP_PACKET_TWIG,
	STP_PACKET_XSYNC,
};

/**
 * enum stp_packet_fwags - STP packet modifiews
 */
enum stp_packet_fwags {
	STP_PACKET_MAWKED	= 0x1,
	STP_PACKET_TIMESTAMPED	= 0x2,
};

stwuct stp_powicy;

stwuct stm_device;

/**
 * stwuct stm_data - STM device descwiption and cawwbacks
 * @name:		device name
 * @stm:		intewnaw stwuctuwe, onwy used by stm cwass code
 * @sw_stawt:		fiwst STP mastew avaiwabwe to softwawe
 * @sw_end:		wast STP mastew avaiwabwe to softwawe
 * @sw_nchannews:	numbew of STP channews pew mastew
 * @sw_mmiosz:		size of one channew's IO space, fow mmap, optionaw
 * @hw_ovewwide:	mastews in the STP stweam wiww not match the ones
 *			assigned by softwawe, but awe up to the STM hawdwawe
 * @packet:		cawwback that sends an STP packet
 * @mmio_addw:		mmap cawwback, optionaw
 * @wink:		cawwed when a new stm_souwce gets winked to us, optionaw
 * @unwink:		wikewise fow unwinking, again optionaw
 * @set_options:	set device-specific options on a channew
 *
 * Fiww out this stwuctuwe befowe cawwing stm_wegistew_device() to cweate
 * an STM device and stm_unwegistew_device() to destwoy it. It wiww awso be
 * passed back to @packet(), @mmio_addw(), @wink(), @unwink() and @set_options()
 * cawwbacks.
 *
 * Nowmawwy, an STM device wiww have a wange of mastews avaiwabwe to softwawe
 * and the west being staticawwy assigned to vawious hawdwawe twace souwces.
 * The fowmew is defined by the wange [@sw_stawt..@sw_end] of the device
 * descwiption. That is, the wowest mastew that can be awwocated to softwawe
 * wwitews is @sw_stawt and data fwom this wwitew wiww appeaw is @sw_stawt
 * mastew in the STP stweam.
 *
 * The @packet cawwback shouwd adhewe to the fowwowing wuwes:
 *   1) it must wetuwn the numbew of bytes it consumed fwom the paywoad;
 *   2) thewefowe, if it sent a packet that does not have paywoad (wike FWAG),
 *      it must wetuwn zewo;
 *   3) if it does not suppowt the wequested packet type/fwag combination,
 *      it must wetuwn -ENOTSUPP.
 *
 * The @unwink cawwback is cawwed when thewe awe no mowe active wwitews so
 * that the mastew/channew can be quiesced.
 */
stwuct stm_data {
	const chaw		*name;
	stwuct stm_device	*stm;
	unsigned int		sw_stawt;
	unsigned int		sw_end;
	unsigned int		sw_nchannews;
	unsigned int		sw_mmiosz;
	unsigned int		hw_ovewwide;
	ssize_t			(*packet)(stwuct stm_data *, unsigned int,
					  unsigned int, unsigned int,
					  unsigned int, unsigned int,
					  const unsigned chaw *);
	phys_addw_t		(*mmio_addw)(stwuct stm_data *, unsigned int,
					     unsigned int, unsigned int);
	int			(*wink)(stwuct stm_data *, unsigned int,
					unsigned int);
	void			(*unwink)(stwuct stm_data *, unsigned int,
					  unsigned int);
	wong			(*set_options)(stwuct stm_data *, unsigned int,
					       unsigned int, unsigned int,
					       unsigned wong);
};

int stm_wegistew_device(stwuct device *pawent, stwuct stm_data *stm_data,
			stwuct moduwe *ownew);
void stm_unwegistew_device(stwuct stm_data *stm_data);

stwuct stm_souwce_device;

/**
 * stwuct stm_souwce_data - STM souwce device descwiption and cawwbacks
 * @name:	device name, wiww be used fow powicy wookup
 * @swc:	intewnaw stwuctuwe, onwy used by stm cwass code
 * @nw_chans:	numbew of channews to awwocate
 * @wink:	cawwed when this souwce gets winked to an STM device
 * @unwink:	cawwed when this souwce is about to get unwinked fwom its STM
 *
 * Fiww in this stwuctuwe befowe cawwing stm_souwce_wegistew_device() to
 * wegistew a souwce device. Awso pass it to unwegistew and wwite cawws.
 */
stwuct stm_souwce_data {
	const chaw		*name;
	stwuct stm_souwce_device *swc;
	unsigned int		pewcpu;
	unsigned int		nw_chans;
	int			(*wink)(stwuct stm_souwce_data *data);
	void			(*unwink)(stwuct stm_souwce_data *data);
};

int stm_souwce_wegistew_device(stwuct device *pawent,
			       stwuct stm_souwce_data *data);
void stm_souwce_unwegistew_device(stwuct stm_souwce_data *data);

int notwace stm_souwce_wwite(stwuct stm_souwce_data *data, unsigned int chan,
			     const chaw *buf, size_t count);

#endif /* _STM_H_ */
