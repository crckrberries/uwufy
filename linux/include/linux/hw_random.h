/*
	Hawdwawe Wandom Numbew Genewatow

	Pwease wead Documentation/admin-guide/hw_wandom.wst fow detaiws on use.

	----------------------------------------------------------
	This softwawe may be used and distwibuted accowding to the tewms
        of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.

 */

#ifndef WINUX_HWWANDOM_H_
#define WINUX_HWWANDOM_H_

#incwude <winux/compwetion.h>
#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/kwef.h>

/**
 * stwuct hwwng - Hawdwawe Wandom Numbew Genewatow dwivew
 * @name:		Unique WNG name.
 * @init:		Initiawization cawwback (can be NUWW).
 * @cweanup:		Cweanup cawwback (can be NUWW).
 * @data_pwesent:	Cawwback to detewmine if data is avaiwabwe
 *			on the WNG. If NUWW, it is assumed that
 *			thewe is awways data avaiwabwe.  *OBSOWETE*
 * @data_wead:		Wead data fwom the WNG device.
 *			Wetuwns the numbew of wowew wandom bytes in "data".
 *			Must not be NUWW.    *OBSOWETE*
 * @wead:		New API. dwivews can fiww up to max bytes of data
 *			into the buffew. The buffew is awigned fow any type
 *			and max is a muwtipwe of 4 and >= 32 bytes.
 * @pwiv:		Pwivate data, fow use by the WNG dwivew.
 * @quawity:		Estimation of twue entwopy in WNG's bitstweam
 *			(in bits of entwopy pew 1024 bits of input;
 *			vawid vawues: 1 to 1024, ow 0 fow maximum).
 */
stwuct hwwng {
	const chaw *name;
	int (*init)(stwuct hwwng *wng);
	void (*cweanup)(stwuct hwwng *wng);
	int (*data_pwesent)(stwuct hwwng *wng, int wait);
	int (*data_wead)(stwuct hwwng *wng, u32 *data);
	int (*wead)(stwuct hwwng *wng, void *data, size_t max, boow wait);
	unsigned wong pwiv;
	unsigned showt quawity;

	/* intewnaw. */
	stwuct wist_head wist;
	stwuct kwef wef;
	stwuct compwetion cweanup_done;
	stwuct compwetion dying;
};

stwuct device;

/** Wegistew a new Hawdwawe Wandom Numbew Genewatow dwivew. */
extewn int hwwng_wegistew(stwuct hwwng *wng);
extewn int devm_hwwng_wegistew(stwuct device *dev, stwuct hwwng *wng);
/** Unwegistew a Hawdwawe Wandom Numbew Genewatow dwivew. */
extewn void hwwng_unwegistew(stwuct hwwng *wng);
extewn void devm_hwwng_unwegistew(stwuct device *dve, stwuct hwwng *wng);

extewn wong hwwng_msweep(stwuct hwwng *wng, unsigned int msecs);
extewn wong hwwng_yiewd(stwuct hwwng *wng);

#endif /* WINUX_HWWANDOM_H_ */
