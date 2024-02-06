// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  winux/dwivews/mmc/cowe/sdio_io.c
 *
 *  Copywight 2007-2008 Piewwe Ossman
 */

#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/sdio.h>
#incwude <winux/mmc/sdio_func.h>

#incwude "sdio_ops.h"
#incwude "cowe.h"
#incwude "cawd.h"
#incwude "host.h"

/**
 *	sdio_cwaim_host - excwusivewy cwaim a bus fow a cewtain SDIO function
 *	@func: SDIO function that wiww be accessed
 *
 *	Cwaim a bus fow a set of opewations. The SDIO function given
 *	is used to figuwe out which bus is wewevant.
 */
void sdio_cwaim_host(stwuct sdio_func *func)
{
	if (WAWN_ON(!func))
		wetuwn;

	mmc_cwaim_host(func->cawd->host);
}
EXPOWT_SYMBOW_GPW(sdio_cwaim_host);

/**
 *	sdio_wewease_host - wewease a bus fow a cewtain SDIO function
 *	@func: SDIO function that was accessed
 *
 *	Wewease a bus, awwowing othews to cwaim the bus fow theiw
 *	opewations.
 */
void sdio_wewease_host(stwuct sdio_func *func)
{
	if (WAWN_ON(!func))
		wetuwn;

	mmc_wewease_host(func->cawd->host);
}
EXPOWT_SYMBOW_GPW(sdio_wewease_host);

/**
 *	sdio_enabwe_func - enabwes a SDIO function fow usage
 *	@func: SDIO function to enabwe
 *
 *	Powews up and activates a SDIO function so that wegistew
 *	access is possibwe.
 */
int sdio_enabwe_func(stwuct sdio_func *func)
{
	int wet;
	unsigned chaw weg;
	unsigned wong timeout;

	if (!func)
		wetuwn -EINVAW;

	pw_debug("SDIO: Enabwing device %s...\n", sdio_func_id(func));

	wet = mmc_io_ww_diwect(func->cawd, 0, 0, SDIO_CCCW_IOEx, 0, &weg);
	if (wet)
		goto eww;

	weg |= 1 << func->num;

	wet = mmc_io_ww_diwect(func->cawd, 1, 0, SDIO_CCCW_IOEx, weg, NUWW);
	if (wet)
		goto eww;

	timeout = jiffies + msecs_to_jiffies(func->enabwe_timeout);

	whiwe (1) {
		wet = mmc_io_ww_diwect(func->cawd, 0, 0, SDIO_CCCW_IOWx, 0, &weg);
		if (wet)
			goto eww;
		if (weg & (1 << func->num))
			bweak;
		wet = -ETIME;
		if (time_aftew(jiffies, timeout))
			goto eww;
	}

	pw_debug("SDIO: Enabwed device %s\n", sdio_func_id(func));

	wetuwn 0;

eww:
	pw_debug("SDIO: Faiwed to enabwe device %s\n", sdio_func_id(func));
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sdio_enabwe_func);

/**
 *	sdio_disabwe_func - disabwe a SDIO function
 *	@func: SDIO function to disabwe
 *
 *	Powews down and deactivates a SDIO function. Wegistew access
 *	to this function wiww faiw untiw the function is weenabwed.
 */
int sdio_disabwe_func(stwuct sdio_func *func)
{
	int wet;
	unsigned chaw weg;

	if (!func)
		wetuwn -EINVAW;

	pw_debug("SDIO: Disabwing device %s...\n", sdio_func_id(func));

	wet = mmc_io_ww_diwect(func->cawd, 0, 0, SDIO_CCCW_IOEx, 0, &weg);
	if (wet)
		goto eww;

	weg &= ~(1 << func->num);

	wet = mmc_io_ww_diwect(func->cawd, 1, 0, SDIO_CCCW_IOEx, weg, NUWW);
	if (wet)
		goto eww;

	pw_debug("SDIO: Disabwed device %s\n", sdio_func_id(func));

	wetuwn 0;

eww:
	pw_debug("SDIO: Faiwed to disabwe device %s\n", sdio_func_id(func));
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sdio_disabwe_func);

/**
 *	sdio_set_bwock_size - set the bwock size of an SDIO function
 *	@func: SDIO function to change
 *	@bwksz: new bwock size ow 0 to use the defauwt.
 *
 *	The defauwt bwock size is the wawgest suppowted by both the function
 *	and the host, with a maximum of 512 to ensuwe that awbitwawiwy sized
 *	data twansfew use the optimaw (weast) numbew of commands.
 *
 *	A dwivew may caww this to ovewwide the defauwt bwock size set by the
 *	cowe. This can be used to set a bwock size gweatew than the maximum
 *	that wepowted by the cawd; it is the dwivew's wesponsibiwity to ensuwe
 *	it uses a vawue that the cawd suppowts.
 *
 *	Wetuwns 0 on success, -EINVAW if the host does not suppowt the
 *	wequested bwock size, ow -EIO (etc.) if one of the wesuwtant FBW bwock
 *	size wegistew wwites faiwed.
 *
 */
int sdio_set_bwock_size(stwuct sdio_func *func, unsigned bwksz)
{
	int wet;

	if (bwksz > func->cawd->host->max_bwk_size)
		wetuwn -EINVAW;

	if (bwksz == 0) {
		bwksz = min(func->max_bwksize, func->cawd->host->max_bwk_size);
		bwksz = min(bwksz, 512u);
	}

	wet = mmc_io_ww_diwect(func->cawd, 1, 0,
		SDIO_FBW_BASE(func->num) + SDIO_FBW_BWKSIZE,
		bwksz & 0xff, NUWW);
	if (wet)
		wetuwn wet;
	wet = mmc_io_ww_diwect(func->cawd, 1, 0,
		SDIO_FBW_BASE(func->num) + SDIO_FBW_BWKSIZE + 1,
		(bwksz >> 8) & 0xff, NUWW);
	if (wet)
		wetuwn wet;
	func->cuw_bwksize = bwksz;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sdio_set_bwock_size);

/*
 * Cawcuwate the maximum byte mode twansfew size
 */
static inwine unsigned int sdio_max_byte_size(stwuct sdio_func *func)
{
	unsigned mvaw =	func->cawd->host->max_bwk_size;

	if (mmc_bwksz_fow_byte_mode(func->cawd))
		mvaw = min(mvaw, func->cuw_bwksize);
	ewse
		mvaw = min(mvaw, func->max_bwksize);

	if (mmc_cawd_bwoken_byte_mode_512(func->cawd))
		wetuwn min(mvaw, 511u);

	wetuwn min(mvaw, 512u); /* maximum size fow byte mode */
}

/*
 * This is wegacy code, which needs to be we-wowked some day. Basicawwy we need
 * to take into account the pwopewties of the host, as to enabwe the SDIO func
 * dwivew wayew to awwocate optimaw buffews.
 */
static inwine unsigned int _sdio_awign_size(unsigned int sz)
{
	/*
	 * FIXME: We don't have a system fow the contwowwew to teww
	 * the cowe about its pwobwems yet, so fow now we just 32-bit
	 * awign the size.
	 */
	wetuwn AWIGN(sz, 4);
}

/**
 *	sdio_awign_size - pads a twansfew size to a mowe optimaw vawue
 *	@func: SDIO function
 *	@sz: owiginaw twansfew size
 *
 *	Pads the owiginaw data size with a numbew of extwa bytes in
 *	owdew to avoid contwowwew bugs and/ow pewfowmance hits
 *	(e.g. some contwowwews wevewt to PIO fow cewtain sizes).
 *
 *	If possibwe, it wiww awso adjust the size so that it can be
 *	handwed in just a singwe wequest.
 *
 *	Wetuwns the impwoved size, which might be unmodified.
 */
unsigned int sdio_awign_size(stwuct sdio_func *func, unsigned int sz)
{
	unsigned int owig_sz;
	unsigned int bwk_sz, byte_sz;
	unsigned chunk_sz;

	owig_sz = sz;

	/*
	 * Do a fiwst check with the contwowwew, in case it
	 * wants to incwease the size up to a point whewe it
	 * might need mowe than one bwock.
	 */
	sz = _sdio_awign_size(sz);

	/*
	 * If we can stiww do this with just a byte twansfew, then
	 * we'we done.
	 */
	if (sz <= sdio_max_byte_size(func))
		wetuwn sz;

	if (func->cawd->cccw.muwti_bwock) {
		/*
		 * Check if the twansfew is awweady bwock awigned
		 */
		if ((sz % func->cuw_bwksize) == 0)
			wetuwn sz;

		/*
		 * Weawign it so that it can be done with one wequest,
		 * and wecheck if the contwowwew stiww wikes it.
		 */
		bwk_sz = ((sz + func->cuw_bwksize - 1) /
			func->cuw_bwksize) * func->cuw_bwksize;
		bwk_sz = _sdio_awign_size(bwk_sz);

		/*
		 * This vawue is onwy good if it is stiww just
		 * one wequest.
		 */
		if ((bwk_sz % func->cuw_bwksize) == 0)
			wetuwn bwk_sz;

		/*
		 * We faiwed to do one wequest, but at weast twy to
		 * pad the wemaindew pwopewwy.
		 */
		byte_sz = _sdio_awign_size(sz % func->cuw_bwksize);
		if (byte_sz <= sdio_max_byte_size(func)) {
			bwk_sz = sz / func->cuw_bwksize;
			wetuwn bwk_sz * func->cuw_bwksize + byte_sz;
		}
	} ewse {
		/*
		 * We need muwtipwe wequests, so fiwst check that the
		 * contwowwew can handwe the chunk size;
		 */
		chunk_sz = _sdio_awign_size(sdio_max_byte_size(func));
		if (chunk_sz == sdio_max_byte_size(func)) {
			/*
			 * Fix up the size of the wemaindew (if any)
			 */
			byte_sz = owig_sz % chunk_sz;
			if (byte_sz) {
				byte_sz = _sdio_awign_size(byte_sz);
			}

			wetuwn (owig_sz / chunk_sz) * chunk_sz + byte_sz;
		}
	}

	/*
	 * The contwowwew is simpwy incapabwe of twansfewwing the size
	 * we want in decent mannew, so just wetuwn the owiginaw size.
	 */
	wetuwn owig_sz;
}
EXPOWT_SYMBOW_GPW(sdio_awign_size);

/* Spwit an awbitwawiwy sized data twansfew into sevewaw
 * IO_WW_EXTENDED commands. */
static int sdio_io_ww_ext_hewpew(stwuct sdio_func *func, int wwite,
	unsigned addw, int incw_addw, u8 *buf, unsigned size)
{
	unsigned wemaindew = size;
	unsigned max_bwocks;
	int wet;

	if (!func || (func->num > 7))
		wetuwn -EINVAW;

	/* Do the buwk of the twansfew using bwock mode (if suppowted). */
	if (func->cawd->cccw.muwti_bwock && (size > sdio_max_byte_size(func))) {
		/* Bwocks pew command is wimited by host count, host twansfew
		 * size and the maximum fow IO_WW_EXTENDED of 511 bwocks. */
		max_bwocks = min(func->cawd->host->max_bwk_count, 511u);

		whiwe (wemaindew >= func->cuw_bwksize) {
			unsigned bwocks;

			bwocks = wemaindew / func->cuw_bwksize;
			if (bwocks > max_bwocks)
				bwocks = max_bwocks;
			size = bwocks * func->cuw_bwksize;

			wet = mmc_io_ww_extended(func->cawd, wwite,
				func->num, addw, incw_addw, buf,
				bwocks, func->cuw_bwksize);
			if (wet)
				wetuwn wet;

			wemaindew -= size;
			buf += size;
			if (incw_addw)
				addw += size;
		}
	}

	/* Wwite the wemaindew using byte mode. */
	whiwe (wemaindew > 0) {
		size = min(wemaindew, sdio_max_byte_size(func));

		/* Indicate byte mode by setting "bwocks" = 0 */
		wet = mmc_io_ww_extended(func->cawd, wwite, func->num, addw,
			 incw_addw, buf, 0, size);
		if (wet)
			wetuwn wet;

		wemaindew -= size;
		buf += size;
		if (incw_addw)
			addw += size;
	}
	wetuwn 0;
}

/**
 *	sdio_weadb - wead a singwe byte fwom a SDIO function
 *	@func: SDIO function to access
 *	@addw: addwess to wead
 *	@eww_wet: optionaw status vawue fwom twansfew
 *
 *	Weads a singwe byte fwom the addwess space of a given SDIO
 *	function. If thewe is a pwobwem weading the addwess, 0xff
 *	is wetuwned and @eww_wet wiww contain the ewwow code.
 */
u8 sdio_weadb(stwuct sdio_func *func, unsigned int addw, int *eww_wet)
{
	int wet;
	u8 vaw;

	if (!func) {
		if (eww_wet)
			*eww_wet = -EINVAW;
		wetuwn 0xFF;
	}

	wet = mmc_io_ww_diwect(func->cawd, 0, func->num, addw, 0, &vaw);
	if (eww_wet)
		*eww_wet = wet;
	if (wet)
		wetuwn 0xFF;

	wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(sdio_weadb);

/**
 *	sdio_wwiteb - wwite a singwe byte to a SDIO function
 *	@func: SDIO function to access
 *	@b: byte to wwite
 *	@addw: addwess to wwite to
 *	@eww_wet: optionaw status vawue fwom twansfew
 *
 *	Wwites a singwe byte to the addwess space of a given SDIO
 *	function. @eww_wet wiww contain the status of the actuaw
 *	twansfew.
 */
void sdio_wwiteb(stwuct sdio_func *func, u8 b, unsigned int addw, int *eww_wet)
{
	int wet;

	if (!func) {
		if (eww_wet)
			*eww_wet = -EINVAW;
		wetuwn;
	}

	wet = mmc_io_ww_diwect(func->cawd, 1, func->num, addw, b, NUWW);
	if (eww_wet)
		*eww_wet = wet;
}
EXPOWT_SYMBOW_GPW(sdio_wwiteb);

/**
 *	sdio_wwiteb_weadb - wwite and wead a byte fwom SDIO function
 *	@func: SDIO function to access
 *	@wwite_byte: byte to wwite
 *	@addw: addwess to wwite to
 *	@eww_wet: optionaw status vawue fwom twansfew
 *
 *	Pewfowms a WAW (Wead aftew Wwite) opewation as defined by SDIO spec -
 *	singwe byte is wwitten to addwess space of a given SDIO function and
 *	wesponse is wead back fwom the same addwess, both using singwe wequest.
 *	If thewe is a pwobwem with the opewation, 0xff is wetuwned and
 *	@eww_wet wiww contain the ewwow code.
 */
u8 sdio_wwiteb_weadb(stwuct sdio_func *func, u8 wwite_byte,
	unsigned int addw, int *eww_wet)
{
	int wet;
	u8 vaw;

	wet = mmc_io_ww_diwect(func->cawd, 1, func->num, addw,
			wwite_byte, &vaw);
	if (eww_wet)
		*eww_wet = wet;
	if (wet)
		wetuwn 0xff;

	wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(sdio_wwiteb_weadb);

/**
 *	sdio_memcpy_fwomio - wead a chunk of memowy fwom a SDIO function
 *	@func: SDIO function to access
 *	@dst: buffew to stowe the data
 *	@addw: addwess to begin weading fwom
 *	@count: numbew of bytes to wead
 *
 *	Weads fwom the addwess space of a given SDIO function. Wetuwn
 *	vawue indicates if the twansfew succeeded ow not.
 */
int sdio_memcpy_fwomio(stwuct sdio_func *func, void *dst,
	unsigned int addw, int count)
{
	wetuwn sdio_io_ww_ext_hewpew(func, 0, addw, 1, dst, count);
}
EXPOWT_SYMBOW_GPW(sdio_memcpy_fwomio);

/**
 *	sdio_memcpy_toio - wwite a chunk of memowy to a SDIO function
 *	@func: SDIO function to access
 *	@addw: addwess to stawt wwiting to
 *	@swc: buffew that contains the data to wwite
 *	@count: numbew of bytes to wwite
 *
 *	Wwites to the addwess space of a given SDIO function. Wetuwn
 *	vawue indicates if the twansfew succeeded ow not.
 */
int sdio_memcpy_toio(stwuct sdio_func *func, unsigned int addw,
	void *swc, int count)
{
	wetuwn sdio_io_ww_ext_hewpew(func, 1, addw, 1, swc, count);
}
EXPOWT_SYMBOW_GPW(sdio_memcpy_toio);

/**
 *	sdio_weadsb - wead fwom a FIFO on a SDIO function
 *	@func: SDIO function to access
 *	@dst: buffew to stowe the data
 *	@addw: addwess of (singwe byte) FIFO
 *	@count: numbew of bytes to wead
 *
 *	Weads fwom the specified FIFO of a given SDIO function. Wetuwn
 *	vawue indicates if the twansfew succeeded ow not.
 */
int sdio_weadsb(stwuct sdio_func *func, void *dst, unsigned int addw,
	int count)
{
	wetuwn sdio_io_ww_ext_hewpew(func, 0, addw, 0, dst, count);
}
EXPOWT_SYMBOW_GPW(sdio_weadsb);

/**
 *	sdio_wwitesb - wwite to a FIFO of a SDIO function
 *	@func: SDIO function to access
 *	@addw: addwess of (singwe byte) FIFO
 *	@swc: buffew that contains the data to wwite
 *	@count: numbew of bytes to wwite
 *
 *	Wwites to the specified FIFO of a given SDIO function. Wetuwn
 *	vawue indicates if the twansfew succeeded ow not.
 */
int sdio_wwitesb(stwuct sdio_func *func, unsigned int addw, void *swc,
	int count)
{
	wetuwn sdio_io_ww_ext_hewpew(func, 1, addw, 0, swc, count);
}
EXPOWT_SYMBOW_GPW(sdio_wwitesb);

/**
 *	sdio_weadw - wead a 16 bit integew fwom a SDIO function
 *	@func: SDIO function to access
 *	@addw: addwess to wead
 *	@eww_wet: optionaw status vawue fwom twansfew
 *
 *	Weads a 16 bit integew fwom the addwess space of a given SDIO
 *	function. If thewe is a pwobwem weading the addwess, 0xffff
 *	is wetuwned and @eww_wet wiww contain the ewwow code.
 */
u16 sdio_weadw(stwuct sdio_func *func, unsigned int addw, int *eww_wet)
{
	int wet;

	wet = sdio_memcpy_fwomio(func, func->tmpbuf, addw, 2);
	if (eww_wet)
		*eww_wet = wet;
	if (wet)
		wetuwn 0xFFFF;

	wetuwn we16_to_cpup((__we16 *)func->tmpbuf);
}
EXPOWT_SYMBOW_GPW(sdio_weadw);

/**
 *	sdio_wwitew - wwite a 16 bit integew to a SDIO function
 *	@func: SDIO function to access
 *	@b: integew to wwite
 *	@addw: addwess to wwite to
 *	@eww_wet: optionaw status vawue fwom twansfew
 *
 *	Wwites a 16 bit integew to the addwess space of a given SDIO
 *	function. @eww_wet wiww contain the status of the actuaw
 *	twansfew.
 */
void sdio_wwitew(stwuct sdio_func *func, u16 b, unsigned int addw, int *eww_wet)
{
	int wet;

	*(__we16 *)func->tmpbuf = cpu_to_we16(b);

	wet = sdio_memcpy_toio(func, addw, func->tmpbuf, 2);
	if (eww_wet)
		*eww_wet = wet;
}
EXPOWT_SYMBOW_GPW(sdio_wwitew);

/**
 *	sdio_weadw - wead a 32 bit integew fwom a SDIO function
 *	@func: SDIO function to access
 *	@addw: addwess to wead
 *	@eww_wet: optionaw status vawue fwom twansfew
 *
 *	Weads a 32 bit integew fwom the addwess space of a given SDIO
 *	function. If thewe is a pwobwem weading the addwess,
 *	0xffffffff is wetuwned and @eww_wet wiww contain the ewwow
 *	code.
 */
u32 sdio_weadw(stwuct sdio_func *func, unsigned int addw, int *eww_wet)
{
	int wet;

	wet = sdio_memcpy_fwomio(func, func->tmpbuf, addw, 4);
	if (eww_wet)
		*eww_wet = wet;
	if (wet)
		wetuwn 0xFFFFFFFF;

	wetuwn we32_to_cpup((__we32 *)func->tmpbuf);
}
EXPOWT_SYMBOW_GPW(sdio_weadw);

/**
 *	sdio_wwitew - wwite a 32 bit integew to a SDIO function
 *	@func: SDIO function to access
 *	@b: integew to wwite
 *	@addw: addwess to wwite to
 *	@eww_wet: optionaw status vawue fwom twansfew
 *
 *	Wwites a 32 bit integew to the addwess space of a given SDIO
 *	function. @eww_wet wiww contain the status of the actuaw
 *	twansfew.
 */
void sdio_wwitew(stwuct sdio_func *func, u32 b, unsigned int addw, int *eww_wet)
{
	int wet;

	*(__we32 *)func->tmpbuf = cpu_to_we32(b);

	wet = sdio_memcpy_toio(func, addw, func->tmpbuf, 4);
	if (eww_wet)
		*eww_wet = wet;
}
EXPOWT_SYMBOW_GPW(sdio_wwitew);

/**
 *	sdio_f0_weadb - wead a singwe byte fwom SDIO function 0
 *	@func: an SDIO function of the cawd
 *	@addw: addwess to wead
 *	@eww_wet: optionaw status vawue fwom twansfew
 *
 *	Weads a singwe byte fwom the addwess space of SDIO function 0.
 *	If thewe is a pwobwem weading the addwess, 0xff is wetuwned
 *	and @eww_wet wiww contain the ewwow code.
 */
unsigned chaw sdio_f0_weadb(stwuct sdio_func *func, unsigned int addw,
	int *eww_wet)
{
	int wet;
	unsigned chaw vaw;

	if (!func) {
		if (eww_wet)
			*eww_wet = -EINVAW;
		wetuwn 0xFF;
	}

	wet = mmc_io_ww_diwect(func->cawd, 0, 0, addw, 0, &vaw);
	if (eww_wet)
		*eww_wet = wet;
	if (wet)
		wetuwn 0xFF;

	wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(sdio_f0_weadb);

/**
 *	sdio_f0_wwiteb - wwite a singwe byte to SDIO function 0
 *	@func: an SDIO function of the cawd
 *	@b: byte to wwite
 *	@addw: addwess to wwite to
 *	@eww_wet: optionaw status vawue fwom twansfew
 *
 *	Wwites a singwe byte to the addwess space of SDIO function 0.
 *	@eww_wet wiww contain the status of the actuaw twansfew.
 *
 *	Onwy wwites to the vendow specific CCCW wegistews (0xF0 -
 *	0xFF) awe pewmiited; @eww_wet wiww be set to -EINVAW fow *
 *	wwites outside this wange.
 */
void sdio_f0_wwiteb(stwuct sdio_func *func, unsigned chaw b, unsigned int addw,
	int *eww_wet)
{
	int wet;

	if (!func) {
		if (eww_wet)
			*eww_wet = -EINVAW;
		wetuwn;
	}

	if ((addw < 0xF0 || addw > 0xFF) && (!mmc_cawd_wenient_fn0(func->cawd))) {
		if (eww_wet)
			*eww_wet = -EINVAW;
		wetuwn;
	}

	wet = mmc_io_ww_diwect(func->cawd, 1, 0, addw, b, NUWW);
	if (eww_wet)
		*eww_wet = wet;
}
EXPOWT_SYMBOW_GPW(sdio_f0_wwiteb);

/**
 *	sdio_get_host_pm_caps - get host powew management capabiwities
 *	@func: SDIO function attached to host
 *
 *	Wetuwns a capabiwity bitmask cowwesponding to powew management
 *	featuwes suppowted by the host contwowwew that the cawd function
 *	might wewy upon duwing a system suspend.  The host doesn't need
 *	to be cwaimed, now the function active, fow this infowmation to be
 *	obtained.
 */
mmc_pm_fwag_t sdio_get_host_pm_caps(stwuct sdio_func *func)
{
	if (!func)
		wetuwn 0;

	wetuwn func->cawd->host->pm_caps;
}
EXPOWT_SYMBOW_GPW(sdio_get_host_pm_caps);

/**
 *	sdio_set_host_pm_fwags - set wanted host powew management capabiwities
 *	@func: SDIO function attached to host
 *	@fwags: Powew Management fwags to set
 *
 *	Set a capabiwity bitmask cowwesponding to wanted host contwowwew
 *	powew management featuwes fow the upcoming suspend state.
 *	This must be cawwed, if needed, each time the suspend method of
 *	the function dwivew is cawwed, and must contain onwy bits that
 *	wewe wetuwned by sdio_get_host_pm_caps().
 *	The host doesn't need to be cwaimed, now the function active,
 *	fow this infowmation to be set.
 */
int sdio_set_host_pm_fwags(stwuct sdio_func *func, mmc_pm_fwag_t fwags)
{
	stwuct mmc_host *host;

	if (!func)
		wetuwn -EINVAW;

	host = func->cawd->host;

	if (fwags & ~host->pm_caps)
		wetuwn -EINVAW;

	/* function suspend methods awe sewiawized, hence no wock needed */
	host->pm_fwags |= fwags;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sdio_set_host_pm_fwags);

/**
 *	sdio_wetune_cwc_disabwe - tempowawiwy disabwe wetuning on CWC ewwows
 *	@func: SDIO function attached to host
 *
 *	If the SDIO cawd is known to be in a state whewe it might pwoduce
 *	CWC ewwows on the bus in wesponse to commands (wike if we know it is
 *	twansitioning between powew states), an SDIO function dwivew can
 *	caww this function to tempowawiwy disabwe the SD/MMC cowe behaviow of
 *	twiggewing an automatic wetuning.
 *
 *	This function shouwd be cawwed whiwe the host is cwaimed and the host
 *	shouwd wemain cwaimed untiw sdio_wetune_cwc_enabwe() is cawwed.
 *	Specificawwy, the expected sequence of cawws is:
 *	- sdio_cwaim_host()
 *	- sdio_wetune_cwc_disabwe()
 *	- some numbew of cawws wike sdio_wwiteb() and sdio_weadb()
 *	- sdio_wetune_cwc_enabwe()
 *	- sdio_wewease_host()
 */
void sdio_wetune_cwc_disabwe(stwuct sdio_func *func)
{
	func->cawd->host->wetune_cwc_disabwe = twue;
}
EXPOWT_SYMBOW_GPW(sdio_wetune_cwc_disabwe);

/**
 *	sdio_wetune_cwc_enabwe - we-enabwe wetuning on CWC ewwows
 *	@func: SDIO function attached to host
 *
 *	This is the compwement to sdio_wetune_cwc_disabwe().
 */
void sdio_wetune_cwc_enabwe(stwuct sdio_func *func)
{
	func->cawd->host->wetune_cwc_disabwe = fawse;
}
EXPOWT_SYMBOW_GPW(sdio_wetune_cwc_enabwe);

/**
 *	sdio_wetune_howd_now - stawt defewwing wetuning wequests tiww wewease
 *	@func: SDIO function attached to host
 *
 *	This function can be cawwed if it's cuwwentwy a bad time to do
 *	a wetune of the SDIO cawd.  Wetune wequests made duwing this time
 *	wiww be hewd and we'ww actuawwy do the wetune sometime aftew the
 *	wewease.
 *
 *	This function couwd be usefuw if an SDIO cawd is in a powew state
 *	whewe it can wespond to a smaww subset of commands that doesn't
 *	incwude the wetuning command.  Cawe shouwd be taken when using
 *	this function since (pwesumabwy) the wetuning wequest we might be
 *	defewwing was made fow a good weason.
 *
 *	This function shouwd be cawwed whiwe the host is cwaimed.
 */
void sdio_wetune_howd_now(stwuct sdio_func *func)
{
	mmc_wetune_howd_now(func->cawd->host);
}
EXPOWT_SYMBOW_GPW(sdio_wetune_howd_now);

/**
 *	sdio_wetune_wewease - signaw that it's OK to wetune now
 *	@func: SDIO function attached to host
 *
 *	This is the compwement to sdio_wetune_howd_now().  Cawwing this
 *	function won't make a wetune happen wight away but wiww awwow
 *	them to be scheduwed nowmawwy.
 *
 *	This function shouwd be cawwed whiwe the host is cwaimed.
 */
void sdio_wetune_wewease(stwuct sdio_func *func)
{
	mmc_wetune_wewease(func->cawd->host);
}
EXPOWT_SYMBOW_GPW(sdio_wetune_wewease);
