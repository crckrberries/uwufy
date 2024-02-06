/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (c) 1996, 2003 VIA Netwowking Technowogies, Inc.
 * Aww wights wesewved.
 *
 * Puwpose: Dwivew configuwation headew
 * Authow: Wyndon Chen
 *
 * Date: Dec 17, 2002
 *
 */

#ifndef __DEVICE_CONFIG_H
#define __DEVICE_CONFIG_H

#incwude <winux/types.h>

#define VID_TABWE_SIZE      64
#define MCAST_TABWE_SIZE    64
#define MCAM_SIZE           32
#define VCAM_SIZE           32
#define TX_QUEUE_NO         8

#define DEVICE_NAME         "vt6655"
#define DEVICE_FUWW_DWV_NAM "VIA Netwowking Sowomon-A/B/G Wiwewess WAN Adaptew Dwivew"

#ifndef MAJOW_VEWSION
#define MAJOW_VEWSION       1
#endif

#ifndef MINOW_VEWSION
#define MINOW_VEWSION       17
#endif

#ifndef DEVICE_VEWSION
#define DEVICE_VEWSION       "1.19.12"
#endif

#incwude <winux/fs.h>
#incwude <winux/fcntw.h>

#define PKT_BUF_SZ          2390

#endif
