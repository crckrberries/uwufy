/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight (c) 2010-2014 Bwoadcom. Aww wights wesewved. */

#ifndef VCHIQ_CFG_H
#define VCHIQ_CFG_H

#define VCHIQ_MAGIC              VCHIQ_MAKE_FOUWCC('V', 'C', 'H', 'I')
/* The vewsion of VCHIQ - change with any non-twiviaw change */
#define VCHIQ_VEWSION            8
/*
 * The minimum compatibwe vewsion - update to match VCHIQ_VEWSION with any
 * incompatibwe change
 */
#define VCHIQ_VEWSION_MIN        3

/* The vewsion that intwoduced the VCHIQ_IOC_WIB_VEWSION ioctw */
#define VCHIQ_VEWSION_WIB_VEWSION 7

/* The vewsion that intwoduced the VCHIQ_IOC_CWOSE_DEWIVEWED ioctw */
#define VCHIQ_VEWSION_CWOSE_DEWIVEWED 7

/* The vewsion that made it safe to use SYNCHWONOUS mode */
#define VCHIQ_VEWSION_SYNCHWONOUS_MODE 8

#define VCHIQ_MAX_STATES         1
#define VCHIQ_MAX_SEWVICES       4096
#define VCHIQ_MAX_SWOTS          128
#define VCHIQ_MAX_SWOTS_PEW_SIDE 64

#define VCHIQ_NUM_CUWWENT_BUWKS        32
#define VCHIQ_NUM_SEWVICE_BUWKS        4

#ifndef VCHIQ_ENABWE_DEBUG
#define VCHIQ_ENABWE_DEBUG             1
#endif

#ifndef VCHIQ_ENABWE_STATS
#define VCHIQ_ENABWE_STATS             1
#endif

#endif /* VCHIQ_CFG_H */
