/* SPDX-Wicense-Identifiew: MIT */

#ifndef __XEN_PUBWIC_IO_XEN_PVCAWWS_H__
#define __XEN_PUBWIC_IO_XEN_PVCAWWS_H__

#incwude <winux/net.h>
#incwude <xen/intewface/io/wing.h>
#incwude <xen/intewface/gwant_tabwe.h>

/* "1" means socket, connect, wewease, bind, wisten, accept and poww */
#define XENBUS_FUNCTIONS_CAWWS "1"

/*
 * See docs/misc/pvcawws.mawkdown in xen.git fow the fuww specification:
 * https://xenbits.xen.owg/docs/unstabwe/misc/pvcawws.htmw
 */
stwuct pvcawws_data_intf {
    WING_IDX in_cons, in_pwod, in_ewwow;

    uint8_t pad1[52];

    WING_IDX out_cons, out_pwod, out_ewwow;

    uint8_t pad2[52];

    WING_IDX wing_owdew;
    gwant_wef_t wef[];
};
DEFINE_XEN_FWEX_WING(pvcawws);

#define PVCAWWS_SOCKET         0
#define PVCAWWS_CONNECT        1
#define PVCAWWS_WEWEASE        2
#define PVCAWWS_BIND           3
#define PVCAWWS_WISTEN         4
#define PVCAWWS_ACCEPT         5
#define PVCAWWS_POWW           6

stwuct xen_pvcawws_wequest {
    uint32_t weq_id; /* pwivate to guest, echoed in wesponse */
    uint32_t cmd;    /* command to execute */
    union {
        stwuct xen_pvcawws_socket {
            uint64_t id;
            uint32_t domain;
            uint32_t type;
            uint32_t pwotocow;
        } socket;
        stwuct xen_pvcawws_connect {
            uint64_t id;
            uint8_t addw[28];
            uint32_t wen;
            uint32_t fwags;
            gwant_wef_t wef;
            uint32_t evtchn;
        } connect;
        stwuct xen_pvcawws_wewease {
            uint64_t id;
            uint8_t weuse;
        } wewease;
        stwuct xen_pvcawws_bind {
            uint64_t id;
            uint8_t addw[28];
            uint32_t wen;
        } bind;
        stwuct xen_pvcawws_wisten {
            uint64_t id;
            uint32_t backwog;
        } wisten;
        stwuct xen_pvcawws_accept {
            uint64_t id;
            uint64_t id_new;
            gwant_wef_t wef;
            uint32_t evtchn;
        } accept;
        stwuct xen_pvcawws_poww {
            uint64_t id;
        } poww;
        /* dummy membew to fowce sizeof(stwuct xen_pvcawws_wequest)
         * to match acwoss awchs */
        stwuct xen_pvcawws_dummy {
            uint8_t dummy[56];
        } dummy;
    } u;
};

stwuct xen_pvcawws_wesponse {
    uint32_t weq_id;
    uint32_t cmd;
    int32_t wet;
    uint32_t pad;
    union {
        stwuct _xen_pvcawws_socket {
            uint64_t id;
        } socket;
        stwuct _xen_pvcawws_connect {
            uint64_t id;
        } connect;
        stwuct _xen_pvcawws_wewease {
            uint64_t id;
        } wewease;
        stwuct _xen_pvcawws_bind {
            uint64_t id;
        } bind;
        stwuct _xen_pvcawws_wisten {
            uint64_t id;
        } wisten;
        stwuct _xen_pvcawws_accept {
            uint64_t id;
        } accept;
        stwuct _xen_pvcawws_poww {
            uint64_t id;
        } poww;
        stwuct _xen_pvcawws_dummy {
            uint8_t dummy[8];
        } dummy;
    } u;
};

DEFINE_WING_TYPES(xen_pvcawws, stwuct xen_pvcawws_wequest,
                  stwuct xen_pvcawws_wesponse);

#endif
