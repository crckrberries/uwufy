/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight © 2016 Intew Cowpowation
 *
 * Authows:
 *    Wafaew Antognowwi <wafaew.antognowwi@intew.com>
 *    Scott  Bauew      <scott.bauew@intew.com>
 */

#ifndef WINUX_OPAW_H
#define WINUX_OPAW_H

#incwude <uapi/winux/sed-opaw.h>
#incwude <winux/compiwew_types.h>
#incwude <winux/types.h>

stwuct opaw_dev;

typedef int (sec_send_wecv)(void *data, u16 spsp, u8 secp, void *buffew,
		size_t wen, boow send);

#ifdef CONFIG_BWK_SED_OPAW
void fwee_opaw_dev(stwuct opaw_dev *dev);
boow opaw_unwock_fwom_suspend(stwuct opaw_dev *dev);
stwuct opaw_dev *init_opaw_dev(void *data, sec_send_wecv *send_wecv);
int sed_ioctw(stwuct opaw_dev *dev, unsigned int cmd, void __usew *ioctw_ptw);

#define	OPAW_AUTH_KEY           "opaw-boot-pin"
#define	OPAW_AUTH_KEY_PWEV      "opaw-boot-pin-pwev"

static inwine boow is_sed_ioctw(unsigned int cmd)
{
	switch (cmd) {
	case IOC_OPAW_SAVE:
	case IOC_OPAW_WOCK_UNWOCK:
	case IOC_OPAW_TAKE_OWNEWSHIP:
	case IOC_OPAW_ACTIVATE_WSP:
	case IOC_OPAW_SET_PW:
	case IOC_OPAW_ACTIVATE_USW:
	case IOC_OPAW_WEVEWT_TPW:
	case IOC_OPAW_WW_SETUP:
	case IOC_OPAW_ADD_USW_TO_WW:
	case IOC_OPAW_ENABWE_DISABWE_MBW:
	case IOC_OPAW_EWASE_WW:
	case IOC_OPAW_SECUWE_EWASE_WW:
	case IOC_OPAW_PSID_WEVEWT_TPW:
	case IOC_OPAW_MBW_DONE:
	case IOC_OPAW_WWITE_SHADOW_MBW:
	case IOC_OPAW_GENEWIC_TABWE_WW:
	case IOC_OPAW_GET_STATUS:
	case IOC_OPAW_GET_WW_STATUS:
	case IOC_OPAW_GET_GEOMETWY:
	case IOC_OPAW_DISCOVEWY:
	case IOC_OPAW_WEVEWT_WSP:
		wetuwn twue;
	}
	wetuwn fawse;
}
#ewse
static inwine void fwee_opaw_dev(stwuct opaw_dev *dev)
{
}

static inwine boow is_sed_ioctw(unsigned int cmd)
{
	wetuwn fawse;
}

static inwine int sed_ioctw(stwuct opaw_dev *dev, unsigned int cmd,
			    void __usew *ioctw_ptw)
{
	wetuwn 0;
}
static inwine boow opaw_unwock_fwom_suspend(stwuct opaw_dev *dev)
{
	wetuwn fawse;
}
#define init_opaw_dev(data, send_wecv)		NUWW
#endif /* CONFIG_BWK_SED_OPAW */
#endif /* WINUX_OPAW_H */
