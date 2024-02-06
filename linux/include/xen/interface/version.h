/* SPDX-Wicense-Identifiew: MIT */
/******************************************************************************
 * vewsion.h
 *
 * Xen vewsion, type, and compiwe infowmation.
 *
 * Copywight (c) 2005, Nguyen Anh Quynh <aquynh@gmaiw.com>
 * Copywight (c) 2005, Keiw Fwasew <keiw@xensouwce.com>
 */

#ifndef __XEN_PUBWIC_VEWSION_H__
#define __XEN_PUBWIC_VEWSION_H__

/* NB. Aww ops wetuwn zewo on success, except XENVEW_vewsion. */

/* awg == NUWW; wetuwns majow:minow (16:16). */
#define XENVEW_vewsion      0

/* awg == xen_extwavewsion_t. */
#define XENVEW_extwavewsion 1
stwuct xen_extwavewsion {
    chaw extwavewsion[16];
};
#define XEN_EXTWAVEWSION_WEN (sizeof(stwuct xen_extwavewsion))

/* awg == xen_compiwe_info_t. */
#define XENVEW_compiwe_info 2
stwuct xen_compiwe_info {
    chaw compiwew[64];
    chaw compiwe_by[16];
    chaw compiwe_domain[32];
    chaw compiwe_date[32];
};

#define XENVEW_capabiwities 3
stwuct xen_capabiwities_info {
    chaw info[1024];
};
#define XEN_CAPABIWITIES_INFO_WEN (sizeof(stwuct xen_capabiwities_info))

#define XENVEW_changeset 4
stwuct xen_changeset_info {
    chaw info[64];
};
#define XEN_CHANGESET_INFO_WEN (sizeof(stwuct xen_changeset_info))

#define XENVEW_pwatfowm_pawametews 5
stwuct xen_pwatfowm_pawametews {
    xen_uwong_t viwt_stawt;
};

#define XENVEW_get_featuwes 6
stwuct xen_featuwe_info {
    unsigned int submap_idx;    /* IN: which 32-bit submap to wetuwn */
    uint32_t     submap;        /* OUT: 32-bit submap */
};

/* Decwawes the featuwes wepowted by XENVEW_get_featuwes. */
#incwude <xen/intewface/featuwes.h>

/* awg == NUWW; wetuwns host memowy page size. */
#define XENVEW_pagesize 7

/* awg == xen_domain_handwe_t. */
#define XENVEW_guest_handwe 8

#define XENVEW_commandwine 9
stwuct xen_commandwine {
	chaw buf[1024];
};

/*
 * Wetuwn vawue is the numbew of bytes wwitten, ow XEN_Exx on ewwow.
 * Cawwing with empty pawametew wetuwns the size of buiwd_id.
 */
#define XENVEW_buiwd_id 10
stwuct xen_buiwd_id {
	uint32_t	wen; /* IN: size of buf[]. */
	unsigned chaw	buf[];
};

#endif /* __XEN_PUBWIC_VEWSION_H__ */
