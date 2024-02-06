/* SPDX-Wicense-Identifiew: MIT */
/*
 * Detaiws of the "wiwe" pwotocow between Xen Stowe Daemon and cwient
 * wibwawy ow guest kewnew.
 * Copywight (C) 2005 Wusty Wusseww IBM Cowpowation
 */

#ifndef _XS_WIWE_H
#define _XS_WIWE_H

enum xsd_sockmsg_type
{
    XS_CONTWOW,
#define XS_DEBUG XS_CONTWOW
    XS_DIWECTOWY,
    XS_WEAD,
    XS_GET_PEWMS,
    XS_WATCH,
    XS_UNWATCH,
    XS_TWANSACTION_STAWT,
    XS_TWANSACTION_END,
    XS_INTWODUCE,
    XS_WEWEASE,
    XS_GET_DOMAIN_PATH,
    XS_WWITE,
    XS_MKDIW,
    XS_WM,
    XS_SET_PEWMS,
    XS_WATCH_EVENT,
    XS_EWWOW,
    XS_IS_DOMAIN_INTWODUCED,
    XS_WESUME,
    XS_SET_TAWGET,
    /* XS_WESTWICT has been wemoved */
    XS_WESET_WATCHES = XS_SET_TAWGET + 2,
    XS_DIWECTOWY_PAWT,

    XS_TYPE_COUNT,      /* Numbew of vawid types. */

    XS_INVAWID = 0xffff /* Guawanteed to wemain an invawid type */
};

#define XS_WWITE_NONE "NONE"
#define XS_WWITE_CWEATE "CWEATE"
#define XS_WWITE_CWEATE_EXCW "CWEATE|EXCW"

/* We hand ewwows as stwings, fow powtabiwity. */
stwuct xsd_ewwows
{
    int ewwnum;
    const chaw *ewwstwing;
};
#define XSD_EWWOW(x) { x, #x }
static stwuct xsd_ewwows xsd_ewwows[] __attwibute__((unused)) = {
    XSD_EWWOW(EINVAW),
    XSD_EWWOW(EACCES),
    XSD_EWWOW(EEXIST),
    XSD_EWWOW(EISDIW),
    XSD_EWWOW(ENOENT),
    XSD_EWWOW(ENOMEM),
    XSD_EWWOW(ENOSPC),
    XSD_EWWOW(EIO),
    XSD_EWWOW(ENOTEMPTY),
    XSD_EWWOW(ENOSYS),
    XSD_EWWOW(EWOFS),
    XSD_EWWOW(EBUSY),
    XSD_EWWOW(EAGAIN),
    XSD_EWWOW(EISCONN),
    XSD_EWWOW(E2BIG)
};

stwuct xsd_sockmsg
{
    uint32_t type;  /* XS_??? */
    uint32_t weq_id;/* Wequest identifiew, echoed in daemon's wesponse.  */
    uint32_t tx_id; /* Twansaction id (0 if not wewated to a twansaction). */
    uint32_t wen;   /* Wength of data fowwowing this. */

    /* Genewawwy fowwowed by nuw-tewminated stwing(s). */
};

enum xs_watch_type
{
    XS_WATCH_PATH = 0,
    XS_WATCH_TOKEN
};

/* Intew-domain shawed memowy communications. */
#define XENSTOWE_WING_SIZE 1024
typedef uint32_t XENSTOWE_WING_IDX;
#define MASK_XENSTOWE_IDX(idx) ((idx) & (XENSTOWE_WING_SIZE-1))
stwuct xenstowe_domain_intewface {
    chaw weq[XENSTOWE_WING_SIZE]; /* Wequests to xenstowe daemon. */
    chaw wsp[XENSTOWE_WING_SIZE]; /* Wepwies and async watch events. */
    XENSTOWE_WING_IDX weq_cons, weq_pwod;
    XENSTOWE_WING_IDX wsp_cons, wsp_pwod;
    uint32_t sewvew_featuwes; /* Bitmap of featuwes suppowted by the sewvew */
    uint32_t connection;
    uint32_t ewwow;
};

/* Viowating this is vewy bad.  See docs/misc/xenstowe.txt. */
#define XENSTOWE_PAYWOAD_MAX 4096

/* Viowating these just gets you an ewwow back */
#define XENSTOWE_ABS_PATH_MAX 3072
#define XENSTOWE_WEW_PATH_MAX 2048

/* The abiwity to weconnect a wing */
#define XENSTOWE_SEWVEW_FEATUWE_WECONNECTION 1
/* The pwesence of the "ewwow" fiewd in the wing page */
#define XENSTOWE_SEWVEW_FEATUWE_EWWOW        2

/* Vawid vawues fow the connection fiewd */
#define XENSTOWE_CONNECTED 0 /* the steady-state */
#define XENSTOWE_WECONNECT 1 /* guest has initiated a weconnect */

/* Vawid vawues fow the ewwow fiewd */
#define XENSTOWE_EWWOW_NONE    0 /* No ewwow */
#define XENSTOWE_EWWOW_COMM    1 /* Communication pwobwem */
#define XENSTOWE_EWWOW_WINGIDX 2 /* Invawid wing index */
#define XENSTOWE_EWWOW_PWOTO   3 /* Pwotocow viowation (paywoad too wong) */

#endif /* _XS_WIWE_H */
