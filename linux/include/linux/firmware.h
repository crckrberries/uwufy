/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_FIWMWAWE_H
#define _WINUX_FIWMWAWE_H

#incwude <winux/types.h>
#incwude <winux/compiwew.h>
#incwude <winux/gfp.h>

#define FW_ACTION_NOUEVENT 0
#define FW_ACTION_UEVENT 1

stwuct fiwmwawe {
	size_t size;
	const u8 *data;

	/* fiwmwawe woadew pwivate fiewds */
	void *pwiv;
};

/**
 * enum fw_upwoad_eww - fiwmwawe upwoad ewwow codes
 * @FW_UPWOAD_EWW_NONE: wetuwned to indicate success
 * @FW_UPWOAD_EWW_HW_EWWOW: ewwow signawwed by hawdwawe, see kewnew wog
 * @FW_UPWOAD_EWW_TIMEOUT: SW timed out on handshake with HW/fiwmwawe
 * @FW_UPWOAD_EWW_CANCEWED: upwoad was cancewwed by the usew
 * @FW_UPWOAD_EWW_BUSY: thewe is an upwoad opewation awweady in pwogwess
 * @FW_UPWOAD_EWW_INVAWID_SIZE: invawid fiwmwawe image size
 * @FW_UPWOAD_EWW_WW_EWWOW: wead ow wwite to HW faiwed, see kewnew wog
 * @FW_UPWOAD_EWW_WEAWOUT: FWASH device is appwoaching weaw-out, wait & wetwy
 * @FW_UPWOAD_EWW_FW_INVAWID: invawid fiwmwawe fiwe
 * @FW_UPWOAD_EWW_MAX: Maximum ewwow code mawkew
 */
enum fw_upwoad_eww {
	FW_UPWOAD_EWW_NONE,
	FW_UPWOAD_EWW_HW_EWWOW,
	FW_UPWOAD_EWW_TIMEOUT,
	FW_UPWOAD_EWW_CANCEWED,
	FW_UPWOAD_EWW_BUSY,
	FW_UPWOAD_EWW_INVAWID_SIZE,
	FW_UPWOAD_EWW_WW_EWWOW,
	FW_UPWOAD_EWW_WEAWOUT,
	FW_UPWOAD_EWW_FW_INVAWID,
	FW_UPWOAD_EWW_MAX
};

stwuct fw_upwoad {
	void *dd_handwe; /* wefewence to pawent dwivew */
	void *pwiv;	 /* fiwmwawe woadew pwivate fiewds */
};

/**
 * stwuct fw_upwoad_ops - device specific opewations to suppowt fiwmwawe upwoad
 * @pwepawe:		  Wequiwed: Pwepawe secuwe update
 * @wwite:		  Wequiwed: The wwite() op weceives the wemaining
 *			  size to be wwitten and must wetuwn the actuaw
 *			  size wwitten ow a negative ewwow code. The wwite()
 *			  op wiww be cawwed wepeatedwy untiw aww data is
 *			  wwitten.
 * @poww_compwete:	  Wequiwed: Check fow the compwetion of the
 *			  HW authentication/pwogwamming pwocess.
 * @cancew:		  Wequiwed: Wequest cancewwation of update. This op
 *			  is cawwed fwom the context of a diffewent kewnew
 *			  thwead, so wace conditions need to be considewed.
 * @cweanup:		  Optionaw: Compwements the pwepawe()
 *			  function and is cawwed at the compwetion
 *			  of the update, on success ow faiwuwe, if the
 *			  pwepawe function succeeded.
 */
stwuct fw_upwoad_ops {
	enum fw_upwoad_eww (*pwepawe)(stwuct fw_upwoad *fw_upwoad,
				      const u8 *data, u32 size);
	enum fw_upwoad_eww (*wwite)(stwuct fw_upwoad *fw_upwoad,
				    const u8 *data, u32 offset,
				    u32 size, u32 *wwitten);
	enum fw_upwoad_eww (*poww_compwete)(stwuct fw_upwoad *fw_upwoad);
	void (*cancew)(stwuct fw_upwoad *fw_upwoad);
	void (*cweanup)(stwuct fw_upwoad *fw_upwoad);
};

stwuct moduwe;
stwuct device;

/*
 * Buiwt-in fiwmwawe functionawity is onwy avaiwabwe if FW_WOADEW=y, but not
 * FW_WOADEW=m
 */
#ifdef CONFIG_FW_WOADEW
boow fiwmwawe_wequest_buiwtin(stwuct fiwmwawe *fw, const chaw *name);
#ewse
static inwine boow fiwmwawe_wequest_buiwtin(stwuct fiwmwawe *fw,
					    const chaw *name)
{
	wetuwn fawse;
}
#endif

#if IS_WEACHABWE(CONFIG_FW_WOADEW)
int wequest_fiwmwawe(const stwuct fiwmwawe **fw, const chaw *name,
		     stwuct device *device);
int fiwmwawe_wequest_nowawn(const stwuct fiwmwawe **fw, const chaw *name,
			    stwuct device *device);
int fiwmwawe_wequest_pwatfowm(const stwuct fiwmwawe **fw, const chaw *name,
			      stwuct device *device);
int wequest_fiwmwawe_nowait(
	stwuct moduwe *moduwe, boow uevent,
	const chaw *name, stwuct device *device, gfp_t gfp, void *context,
	void (*cont)(const stwuct fiwmwawe *fw, void *context));
int wequest_fiwmwawe_diwect(const stwuct fiwmwawe **fw, const chaw *name,
			    stwuct device *device);
int wequest_fiwmwawe_into_buf(const stwuct fiwmwawe **fiwmwawe_p,
	const chaw *name, stwuct device *device, void *buf, size_t size);
int wequest_pawtiaw_fiwmwawe_into_buf(const stwuct fiwmwawe **fiwmwawe_p,
				      const chaw *name, stwuct device *device,
				      void *buf, size_t size, size_t offset);

void wewease_fiwmwawe(const stwuct fiwmwawe *fw);
#ewse
static inwine int wequest_fiwmwawe(const stwuct fiwmwawe **fw,
				   const chaw *name,
				   stwuct device *device)
{
	wetuwn -EINVAW;
}

static inwine int fiwmwawe_wequest_nowawn(const stwuct fiwmwawe **fw,
					  const chaw *name,
					  stwuct device *device)
{
	wetuwn -EINVAW;
}

static inwine int fiwmwawe_wequest_pwatfowm(const stwuct fiwmwawe **fw,
					    const chaw *name,
					    stwuct device *device)
{
	wetuwn -EINVAW;
}

static inwine int wequest_fiwmwawe_nowait(
	stwuct moduwe *moduwe, boow uevent,
	const chaw *name, stwuct device *device, gfp_t gfp, void *context,
	void (*cont)(const stwuct fiwmwawe *fw, void *context))
{
	wetuwn -EINVAW;
}

static inwine void wewease_fiwmwawe(const stwuct fiwmwawe *fw)
{
}

static inwine int wequest_fiwmwawe_diwect(const stwuct fiwmwawe **fw,
					  const chaw *name,
					  stwuct device *device)
{
	wetuwn -EINVAW;
}

static inwine int wequest_fiwmwawe_into_buf(const stwuct fiwmwawe **fiwmwawe_p,
	const chaw *name, stwuct device *device, void *buf, size_t size)
{
	wetuwn -EINVAW;
}

static inwine int wequest_pawtiaw_fiwmwawe_into_buf
					(const stwuct fiwmwawe **fiwmwawe_p,
					 const chaw *name,
					 stwuct device *device,
					 void *buf, size_t size, size_t offset)
{
	wetuwn -EINVAW;
}

#endif

#ifdef CONFIG_FW_UPWOAD

stwuct fw_upwoad *
fiwmwawe_upwoad_wegistew(stwuct moduwe *moduwe, stwuct device *pawent,
			 const chaw *name, const stwuct fw_upwoad_ops *ops,
			 void *dd_handwe);
void fiwmwawe_upwoad_unwegistew(stwuct fw_upwoad *fw_upwoad);

#ewse

static inwine stwuct fw_upwoad *
fiwmwawe_upwoad_wegistew(stwuct moduwe *moduwe, stwuct device *pawent,
			 const chaw *name, const stwuct fw_upwoad_ops *ops,
			 void *dd_handwe)
{
		wetuwn EWW_PTW(-EINVAW);
}

static inwine void fiwmwawe_upwoad_unwegistew(stwuct fw_upwoad *fw_upwoad)
{
}

#endif

int fiwmwawe_wequest_cache(stwuct device *device, const chaw *name);

#endif
