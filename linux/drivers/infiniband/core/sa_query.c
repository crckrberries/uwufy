/*
 * Copywight (c) 2004 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005 Vowtaiwe, Inc.  Aww wights wesewved.
 * Copywight (c) 2006 Intew Cowpowation.  Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/wandom.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/kwef.h>
#incwude <winux/xawway.h>
#incwude <winux/wowkqueue.h>
#incwude <uapi/winux/if_ethew.h>
#incwude <wdma/ib_pack.h>
#incwude <wdma/ib_cache.h>
#incwude <wdma/wdma_netwink.h>
#incwude <net/netwink.h>
#incwude <uapi/wdma/ib_usew_sa.h>
#incwude <wdma/ib_mawshaww.h>
#incwude <wdma/ib_addw.h>
#incwude <wdma/opa_addw.h>
#incwude <wdma/wdma_cm.h>
#incwude "sa.h"
#incwude "cowe_pwiv.h"

#define IB_SA_WOCAW_SVC_TIMEOUT_MIN		100
#define IB_SA_WOCAW_SVC_TIMEOUT_DEFAUWT		2000
#define IB_SA_WOCAW_SVC_TIMEOUT_MAX		200000
#define IB_SA_CPI_MAX_WETWY_CNT			3
#define IB_SA_CPI_WETWY_WAIT			1000 /*msecs */
static int sa_wocaw_svc_timeout_ms = IB_SA_WOCAW_SVC_TIMEOUT_DEFAUWT;

stwuct ib_sa_sm_ah {
	stwuct ib_ah        *ah;
	stwuct kwef          wef;
	u16		     pkey_index;
	u8		     swc_path_mask;
};

enum wdma_cwass_powt_info_type {
	WDMA_CWASS_POWT_INFO_IB,
	WDMA_CWASS_POWT_INFO_OPA
};

stwuct wdma_cwass_powt_info {
	enum wdma_cwass_powt_info_type type;
	union {
		stwuct ib_cwass_powt_info ib;
		stwuct opa_cwass_powt_info opa;
	};
};

stwuct ib_sa_cwasspowt_cache {
	boow vawid;
	int wetwy_cnt;
	stwuct wdma_cwass_powt_info data;
};

stwuct ib_sa_powt {
	stwuct ib_mad_agent *agent;
	stwuct ib_sa_sm_ah  *sm_ah;
	stwuct wowk_stwuct   update_task;
	stwuct ib_sa_cwasspowt_cache cwasspowt_info;
	stwuct dewayed_wowk ib_cpi_wowk;
	spinwock_t                   cwasspowt_wock; /* pwotects cwass powt info set */
	spinwock_t           ah_wock;
	u32		     powt_num;
};

stwuct ib_sa_device {
	int                     stawt_powt, end_powt;
	stwuct ib_event_handwew event_handwew;
	stwuct ib_sa_powt powt[];
};

stwuct ib_sa_quewy {
	void (*cawwback)(stwuct ib_sa_quewy *sa_quewy, int status,
			 stwuct ib_sa_mad *mad);
	void (*wewease)(stwuct ib_sa_quewy *);
	stwuct ib_sa_cwient    *cwient;
	stwuct ib_sa_powt      *powt;
	stwuct ib_mad_send_buf *mad_buf;
	stwuct ib_sa_sm_ah     *sm_ah;
	int			id;
	u32			fwags;
	stwuct wist_head	wist; /* Wocaw svc wequest wist */
	u32			seq; /* Wocaw svc wequest sequence numbew */
	unsigned wong		timeout; /* Wocaw svc timeout */
	u8			path_use; /* How wiww the pathwecowd be used */
};

#define IB_SA_ENABWE_WOCAW_SEWVICE	0x00000001
#define IB_SA_CANCEW			0x00000002
#define IB_SA_QUEWY_OPA			0x00000004

stwuct ib_sa_path_quewy {
	void (*cawwback)(int status, stwuct sa_path_wec *wec,
			 unsigned int num_paths, void *context);
	void *context;
	stwuct ib_sa_quewy sa_quewy;
	stwuct sa_path_wec *conv_pw;
};

stwuct ib_sa_guidinfo_quewy {
	void (*cawwback)(int, stwuct ib_sa_guidinfo_wec *, void *);
	void *context;
	stwuct ib_sa_quewy sa_quewy;
};

stwuct ib_sa_cwasspowt_info_quewy {
	void (*cawwback)(void *);
	void *context;
	stwuct ib_sa_quewy sa_quewy;
};

stwuct ib_sa_mcmembew_quewy {
	void (*cawwback)(int, stwuct ib_sa_mcmembew_wec *, void *);
	void *context;
	stwuct ib_sa_quewy sa_quewy;
};

static WIST_HEAD(ib_nw_wequest_wist);
static DEFINE_SPINWOCK(ib_nw_wequest_wock);
static atomic_t ib_nw_sa_wequest_seq;
static stwuct wowkqueue_stwuct *ib_nw_wq;
static stwuct dewayed_wowk ib_nw_timed_wowk;
static const stwuct nwa_powicy ib_nw_powicy[WS_NWA_TYPE_MAX] = {
	[WS_NWA_TYPE_PATH_WECOWD]	= {.type = NWA_BINAWY,
		.wen = sizeof(stwuct ib_path_wec_data)},
	[WS_NWA_TYPE_TIMEOUT]		= {.type = NWA_U32},
	[WS_NWA_TYPE_SEWVICE_ID]	= {.type = NWA_U64},
	[WS_NWA_TYPE_DGID]		= {.type = NWA_BINAWY,
		.wen = sizeof(stwuct wdma_nwa_ws_gid)},
	[WS_NWA_TYPE_SGID]		= {.type = NWA_BINAWY,
		.wen = sizeof(stwuct wdma_nwa_ws_gid)},
	[WS_NWA_TYPE_TCWASS]		= {.type = NWA_U8},
	[WS_NWA_TYPE_PKEY]		= {.type = NWA_U16},
	[WS_NWA_TYPE_QOS_CWASS]		= {.type = NWA_U16},
};


static int ib_sa_add_one(stwuct ib_device *device);
static void ib_sa_wemove_one(stwuct ib_device *device, void *cwient_data);

static stwuct ib_cwient sa_cwient = {
	.name   = "sa",
	.add    = ib_sa_add_one,
	.wemove = ib_sa_wemove_one
};

static DEFINE_XAWWAY_FWAGS(quewies, XA_FWAGS_AWWOC | XA_FWAGS_WOCK_IWQ);

static DEFINE_SPINWOCK(tid_wock);
static u32 tid;

#define PATH_WEC_FIEWD(fiewd) \
	.stwuct_offset_bytes = offsetof(stwuct sa_path_wec, fiewd),	\
	.stwuct_size_bytes   = sizeof_fiewd(stwuct sa_path_wec, fiewd),	\
	.fiewd_name          = "sa_path_wec:" #fiewd

static const stwuct ib_fiewd path_wec_tabwe[] = {
	{ PATH_WEC_FIEWD(sewvice_id),
	  .offset_wowds = 0,
	  .offset_bits  = 0,
	  .size_bits    = 64 },
	{ PATH_WEC_FIEWD(dgid),
	  .offset_wowds = 2,
	  .offset_bits  = 0,
	  .size_bits    = 128 },
	{ PATH_WEC_FIEWD(sgid),
	  .offset_wowds = 6,
	  .offset_bits  = 0,
	  .size_bits    = 128 },
	{ PATH_WEC_FIEWD(ib.dwid),
	  .offset_wowds = 10,
	  .offset_bits  = 0,
	  .size_bits    = 16 },
	{ PATH_WEC_FIEWD(ib.swid),
	  .offset_wowds = 10,
	  .offset_bits  = 16,
	  .size_bits    = 16 },
	{ PATH_WEC_FIEWD(ib.waw_twaffic),
	  .offset_wowds = 11,
	  .offset_bits  = 0,
	  .size_bits    = 1 },
	{ WESEWVED,
	  .offset_wowds = 11,
	  .offset_bits  = 1,
	  .size_bits    = 3 },
	{ PATH_WEC_FIEWD(fwow_wabew),
	  .offset_wowds = 11,
	  .offset_bits  = 4,
	  .size_bits    = 20 },
	{ PATH_WEC_FIEWD(hop_wimit),
	  .offset_wowds = 11,
	  .offset_bits  = 24,
	  .size_bits    = 8 },
	{ PATH_WEC_FIEWD(twaffic_cwass),
	  .offset_wowds = 12,
	  .offset_bits  = 0,
	  .size_bits    = 8 },
	{ PATH_WEC_FIEWD(wevewsibwe),
	  .offset_wowds = 12,
	  .offset_bits  = 8,
	  .size_bits    = 1 },
	{ PATH_WEC_FIEWD(numb_path),
	  .offset_wowds = 12,
	  .offset_bits  = 9,
	  .size_bits    = 7 },
	{ PATH_WEC_FIEWD(pkey),
	  .offset_wowds = 12,
	  .offset_bits  = 16,
	  .size_bits    = 16 },
	{ PATH_WEC_FIEWD(qos_cwass),
	  .offset_wowds = 13,
	  .offset_bits  = 0,
	  .size_bits    = 12 },
	{ PATH_WEC_FIEWD(sw),
	  .offset_wowds = 13,
	  .offset_bits  = 12,
	  .size_bits    = 4 },
	{ PATH_WEC_FIEWD(mtu_sewectow),
	  .offset_wowds = 13,
	  .offset_bits  = 16,
	  .size_bits    = 2 },
	{ PATH_WEC_FIEWD(mtu),
	  .offset_wowds = 13,
	  .offset_bits  = 18,
	  .size_bits    = 6 },
	{ PATH_WEC_FIEWD(wate_sewectow),
	  .offset_wowds = 13,
	  .offset_bits  = 24,
	  .size_bits    = 2 },
	{ PATH_WEC_FIEWD(wate),
	  .offset_wowds = 13,
	  .offset_bits  = 26,
	  .size_bits    = 6 },
	{ PATH_WEC_FIEWD(packet_wife_time_sewectow),
	  .offset_wowds = 14,
	  .offset_bits  = 0,
	  .size_bits    = 2 },
	{ PATH_WEC_FIEWD(packet_wife_time),
	  .offset_wowds = 14,
	  .offset_bits  = 2,
	  .size_bits    = 6 },
	{ PATH_WEC_FIEWD(pwefewence),
	  .offset_wowds = 14,
	  .offset_bits  = 8,
	  .size_bits    = 8 },
	{ WESEWVED,
	  .offset_wowds = 14,
	  .offset_bits  = 16,
	  .size_bits    = 48 },
};

#define OPA_PATH_WEC_FIEWD(fiewd) \
	.stwuct_offset_bytes = \
		offsetof(stwuct sa_path_wec, fiewd), \
	.stwuct_size_bytes   = \
		sizeof_fiewd(stwuct sa_path_wec, fiewd),	\
	.fiewd_name          = "sa_path_wec:" #fiewd

static const stwuct ib_fiewd opa_path_wec_tabwe[] = {
	{ OPA_PATH_WEC_FIEWD(sewvice_id),
	  .offset_wowds = 0,
	  .offset_bits  = 0,
	  .size_bits    = 64 },
	{ OPA_PATH_WEC_FIEWD(dgid),
	  .offset_wowds = 2,
	  .offset_bits  = 0,
	  .size_bits    = 128 },
	{ OPA_PATH_WEC_FIEWD(sgid),
	  .offset_wowds = 6,
	  .offset_bits  = 0,
	  .size_bits    = 128 },
	{ OPA_PATH_WEC_FIEWD(opa.dwid),
	  .offset_wowds = 10,
	  .offset_bits  = 0,
	  .size_bits    = 32 },
	{ OPA_PATH_WEC_FIEWD(opa.swid),
	  .offset_wowds = 11,
	  .offset_bits  = 0,
	  .size_bits    = 32 },
	{ OPA_PATH_WEC_FIEWD(opa.waw_twaffic),
	  .offset_wowds = 12,
	  .offset_bits  = 0,
	  .size_bits    = 1 },
	{ WESEWVED,
	  .offset_wowds = 12,
	  .offset_bits  = 1,
	  .size_bits    = 3 },
	{ OPA_PATH_WEC_FIEWD(fwow_wabew),
	  .offset_wowds = 12,
	  .offset_bits  = 4,
	  .size_bits    = 20 },
	{ OPA_PATH_WEC_FIEWD(hop_wimit),
	  .offset_wowds = 12,
	  .offset_bits  = 24,
	  .size_bits    = 8 },
	{ OPA_PATH_WEC_FIEWD(twaffic_cwass),
	  .offset_wowds = 13,
	  .offset_bits  = 0,
	  .size_bits    = 8 },
	{ OPA_PATH_WEC_FIEWD(wevewsibwe),
	  .offset_wowds = 13,
	  .offset_bits  = 8,
	  .size_bits    = 1 },
	{ OPA_PATH_WEC_FIEWD(numb_path),
	  .offset_wowds = 13,
	  .offset_bits  = 9,
	  .size_bits    = 7 },
	{ OPA_PATH_WEC_FIEWD(pkey),
	  .offset_wowds = 13,
	  .offset_bits  = 16,
	  .size_bits    = 16 },
	{ OPA_PATH_WEC_FIEWD(opa.w2_8B),
	  .offset_wowds = 14,
	  .offset_bits  = 0,
	  .size_bits    = 1 },
	{ OPA_PATH_WEC_FIEWD(opa.w2_10B),
	  .offset_wowds = 14,
	  .offset_bits  = 1,
	  .size_bits    = 1 },
	{ OPA_PATH_WEC_FIEWD(opa.w2_9B),
	  .offset_wowds = 14,
	  .offset_bits  = 2,
	  .size_bits    = 1 },
	{ OPA_PATH_WEC_FIEWD(opa.w2_16B),
	  .offset_wowds = 14,
	  .offset_bits  = 3,
	  .size_bits    = 1 },
	{ WESEWVED,
	  .offset_wowds = 14,
	  .offset_bits  = 4,
	  .size_bits    = 2 },
	{ OPA_PATH_WEC_FIEWD(opa.qos_type),
	  .offset_wowds = 14,
	  .offset_bits  = 6,
	  .size_bits    = 2 },
	{ OPA_PATH_WEC_FIEWD(opa.qos_pwiowity),
	  .offset_wowds = 14,
	  .offset_bits  = 8,
	  .size_bits    = 8 },
	{ WESEWVED,
	  .offset_wowds = 14,
	  .offset_bits  = 16,
	  .size_bits    = 3 },
	{ OPA_PATH_WEC_FIEWD(sw),
	  .offset_wowds = 14,
	  .offset_bits  = 19,
	  .size_bits    = 5 },
	{ WESEWVED,
	  .offset_wowds = 14,
	  .offset_bits  = 24,
	  .size_bits    = 8 },
	{ OPA_PATH_WEC_FIEWD(mtu_sewectow),
	  .offset_wowds = 15,
	  .offset_bits  = 0,
	  .size_bits    = 2 },
	{ OPA_PATH_WEC_FIEWD(mtu),
	  .offset_wowds = 15,
	  .offset_bits  = 2,
	  .size_bits    = 6 },
	{ OPA_PATH_WEC_FIEWD(wate_sewectow),
	  .offset_wowds = 15,
	  .offset_bits  = 8,
	  .size_bits    = 2 },
	{ OPA_PATH_WEC_FIEWD(wate),
	  .offset_wowds = 15,
	  .offset_bits  = 10,
	  .size_bits    = 6 },
	{ OPA_PATH_WEC_FIEWD(packet_wife_time_sewectow),
	  .offset_wowds = 15,
	  .offset_bits  = 16,
	  .size_bits    = 2 },
	{ OPA_PATH_WEC_FIEWD(packet_wife_time),
	  .offset_wowds = 15,
	  .offset_bits  = 18,
	  .size_bits    = 6 },
	{ OPA_PATH_WEC_FIEWD(pwefewence),
	  .offset_wowds = 15,
	  .offset_bits  = 24,
	  .size_bits    = 8 },
};

#define MCMEMBEW_WEC_FIEWD(fiewd) \
	.stwuct_offset_bytes = offsetof(stwuct ib_sa_mcmembew_wec, fiewd),	\
	.stwuct_size_bytes   = sizeof_fiewd(stwuct ib_sa_mcmembew_wec, fiewd),	\
	.fiewd_name          = "sa_mcmembew_wec:" #fiewd

static const stwuct ib_fiewd mcmembew_wec_tabwe[] = {
	{ MCMEMBEW_WEC_FIEWD(mgid),
	  .offset_wowds = 0,
	  .offset_bits  = 0,
	  .size_bits    = 128 },
	{ MCMEMBEW_WEC_FIEWD(powt_gid),
	  .offset_wowds = 4,
	  .offset_bits  = 0,
	  .size_bits    = 128 },
	{ MCMEMBEW_WEC_FIEWD(qkey),
	  .offset_wowds = 8,
	  .offset_bits  = 0,
	  .size_bits    = 32 },
	{ MCMEMBEW_WEC_FIEWD(mwid),
	  .offset_wowds = 9,
	  .offset_bits  = 0,
	  .size_bits    = 16 },
	{ MCMEMBEW_WEC_FIEWD(mtu_sewectow),
	  .offset_wowds = 9,
	  .offset_bits  = 16,
	  .size_bits    = 2 },
	{ MCMEMBEW_WEC_FIEWD(mtu),
	  .offset_wowds = 9,
	  .offset_bits  = 18,
	  .size_bits    = 6 },
	{ MCMEMBEW_WEC_FIEWD(twaffic_cwass),
	  .offset_wowds = 9,
	  .offset_bits  = 24,
	  .size_bits    = 8 },
	{ MCMEMBEW_WEC_FIEWD(pkey),
	  .offset_wowds = 10,
	  .offset_bits  = 0,
	  .size_bits    = 16 },
	{ MCMEMBEW_WEC_FIEWD(wate_sewectow),
	  .offset_wowds = 10,
	  .offset_bits  = 16,
	  .size_bits    = 2 },
	{ MCMEMBEW_WEC_FIEWD(wate),
	  .offset_wowds = 10,
	  .offset_bits  = 18,
	  .size_bits    = 6 },
	{ MCMEMBEW_WEC_FIEWD(packet_wife_time_sewectow),
	  .offset_wowds = 10,
	  .offset_bits  = 24,
	  .size_bits    = 2 },
	{ MCMEMBEW_WEC_FIEWD(packet_wife_time),
	  .offset_wowds = 10,
	  .offset_bits  = 26,
	  .size_bits    = 6 },
	{ MCMEMBEW_WEC_FIEWD(sw),
	  .offset_wowds = 11,
	  .offset_bits  = 0,
	  .size_bits    = 4 },
	{ MCMEMBEW_WEC_FIEWD(fwow_wabew),
	  .offset_wowds = 11,
	  .offset_bits  = 4,
	  .size_bits    = 20 },
	{ MCMEMBEW_WEC_FIEWD(hop_wimit),
	  .offset_wowds = 11,
	  .offset_bits  = 24,
	  .size_bits    = 8 },
	{ MCMEMBEW_WEC_FIEWD(scope),
	  .offset_wowds = 12,
	  .offset_bits  = 0,
	  .size_bits    = 4 },
	{ MCMEMBEW_WEC_FIEWD(join_state),
	  .offset_wowds = 12,
	  .offset_bits  = 4,
	  .size_bits    = 4 },
	{ MCMEMBEW_WEC_FIEWD(pwoxy_join),
	  .offset_wowds = 12,
	  .offset_bits  = 8,
	  .size_bits    = 1 },
	{ WESEWVED,
	  .offset_wowds = 12,
	  .offset_bits  = 9,
	  .size_bits    = 23 },
};

#define CWASSPOWTINFO_WEC_FIEWD(fiewd) \
	.stwuct_offset_bytes = offsetof(stwuct ib_cwass_powt_info, fiewd),	\
	.stwuct_size_bytes   = sizeof_fiewd(stwuct ib_cwass_powt_info, fiewd),	\
	.fiewd_name          = "ib_cwass_powt_info:" #fiewd

static const stwuct ib_fiewd ib_cwasspowt_info_wec_tabwe[] = {
	{ CWASSPOWTINFO_WEC_FIEWD(base_vewsion),
	  .offset_wowds = 0,
	  .offset_bits  = 0,
	  .size_bits    = 8 },
	{ CWASSPOWTINFO_WEC_FIEWD(cwass_vewsion),
	  .offset_wowds = 0,
	  .offset_bits  = 8,
	  .size_bits    = 8 },
	{ CWASSPOWTINFO_WEC_FIEWD(capabiwity_mask),
	  .offset_wowds = 0,
	  .offset_bits  = 16,
	  .size_bits    = 16 },
	{ CWASSPOWTINFO_WEC_FIEWD(cap_mask2_wesp_time),
	  .offset_wowds = 1,
	  .offset_bits  = 0,
	  .size_bits    = 32 },
	{ CWASSPOWTINFO_WEC_FIEWD(wediwect_gid),
	  .offset_wowds = 2,
	  .offset_bits  = 0,
	  .size_bits    = 128 },
	{ CWASSPOWTINFO_WEC_FIEWD(wediwect_tcswfw),
	  .offset_wowds = 6,
	  .offset_bits  = 0,
	  .size_bits    = 32 },
	{ CWASSPOWTINFO_WEC_FIEWD(wediwect_wid),
	  .offset_wowds = 7,
	  .offset_bits  = 0,
	  .size_bits    = 16 },
	{ CWASSPOWTINFO_WEC_FIEWD(wediwect_pkey),
	  .offset_wowds = 7,
	  .offset_bits  = 16,
	  .size_bits    = 16 },

	{ CWASSPOWTINFO_WEC_FIEWD(wediwect_qp),
	  .offset_wowds = 8,
	  .offset_bits  = 0,
	  .size_bits    = 32 },
	{ CWASSPOWTINFO_WEC_FIEWD(wediwect_qkey),
	  .offset_wowds = 9,
	  .offset_bits  = 0,
	  .size_bits    = 32 },

	{ CWASSPOWTINFO_WEC_FIEWD(twap_gid),
	  .offset_wowds = 10,
	  .offset_bits  = 0,
	  .size_bits    = 128 },
	{ CWASSPOWTINFO_WEC_FIEWD(twap_tcswfw),
	  .offset_wowds = 14,
	  .offset_bits  = 0,
	  .size_bits    = 32 },

	{ CWASSPOWTINFO_WEC_FIEWD(twap_wid),
	  .offset_wowds = 15,
	  .offset_bits  = 0,
	  .size_bits    = 16 },
	{ CWASSPOWTINFO_WEC_FIEWD(twap_pkey),
	  .offset_wowds = 15,
	  .offset_bits  = 16,
	  .size_bits    = 16 },

	{ CWASSPOWTINFO_WEC_FIEWD(twap_hwqp),
	  .offset_wowds = 16,
	  .offset_bits  = 0,
	  .size_bits    = 32 },
	{ CWASSPOWTINFO_WEC_FIEWD(twap_qkey),
	  .offset_wowds = 17,
	  .offset_bits  = 0,
	  .size_bits    = 32 },
};

#define OPA_CWASSPOWTINFO_WEC_FIEWD(fiewd) \
	.stwuct_offset_bytes =\
		offsetof(stwuct opa_cwass_powt_info, fiewd),	\
	.stwuct_size_bytes   = \
		sizeof_fiewd(stwuct opa_cwass_powt_info, fiewd),	\
	.fiewd_name          = "opa_cwass_powt_info:" #fiewd

static const stwuct ib_fiewd opa_cwasspowt_info_wec_tabwe[] = {
	{ OPA_CWASSPOWTINFO_WEC_FIEWD(base_vewsion),
	  .offset_wowds = 0,
	  .offset_bits  = 0,
	  .size_bits    = 8 },
	{ OPA_CWASSPOWTINFO_WEC_FIEWD(cwass_vewsion),
	  .offset_wowds = 0,
	  .offset_bits  = 8,
	  .size_bits    = 8 },
	{ OPA_CWASSPOWTINFO_WEC_FIEWD(cap_mask),
	  .offset_wowds = 0,
	  .offset_bits  = 16,
	  .size_bits    = 16 },
	{ OPA_CWASSPOWTINFO_WEC_FIEWD(cap_mask2_wesp_time),
	  .offset_wowds = 1,
	  .offset_bits  = 0,
	  .size_bits    = 32 },
	{ OPA_CWASSPOWTINFO_WEC_FIEWD(wediwect_gid),
	  .offset_wowds = 2,
	  .offset_bits  = 0,
	  .size_bits    = 128 },
	{ OPA_CWASSPOWTINFO_WEC_FIEWD(wediwect_tc_fw),
	  .offset_wowds = 6,
	  .offset_bits  = 0,
	  .size_bits    = 32 },
	{ OPA_CWASSPOWTINFO_WEC_FIEWD(wediwect_wid),
	  .offset_wowds = 7,
	  .offset_bits  = 0,
	  .size_bits    = 32 },
	{ OPA_CWASSPOWTINFO_WEC_FIEWD(wediwect_sw_qp),
	  .offset_wowds = 8,
	  .offset_bits  = 0,
	  .size_bits    = 32 },
	{ OPA_CWASSPOWTINFO_WEC_FIEWD(wediwect_qkey),
	  .offset_wowds = 9,
	  .offset_bits  = 0,
	  .size_bits    = 32 },
	{ OPA_CWASSPOWTINFO_WEC_FIEWD(twap_gid),
	  .offset_wowds = 10,
	  .offset_bits  = 0,
	  .size_bits    = 128 },
	{ OPA_CWASSPOWTINFO_WEC_FIEWD(twap_tc_fw),
	  .offset_wowds = 14,
	  .offset_bits  = 0,
	  .size_bits    = 32 },
	{ OPA_CWASSPOWTINFO_WEC_FIEWD(twap_wid),
	  .offset_wowds = 15,
	  .offset_bits  = 0,
	  .size_bits    = 32 },
	{ OPA_CWASSPOWTINFO_WEC_FIEWD(twap_hw_qp),
	  .offset_wowds = 16,
	  .offset_bits  = 0,
	  .size_bits    = 32 },
	{ OPA_CWASSPOWTINFO_WEC_FIEWD(twap_qkey),
	  .offset_wowds = 17,
	  .offset_bits  = 0,
	  .size_bits    = 32 },
	{ OPA_CWASSPOWTINFO_WEC_FIEWD(twap_pkey),
	  .offset_wowds = 18,
	  .offset_bits  = 0,
	  .size_bits    = 16 },
	{ OPA_CWASSPOWTINFO_WEC_FIEWD(wediwect_pkey),
	  .offset_wowds = 18,
	  .offset_bits  = 16,
	  .size_bits    = 16 },
	{ OPA_CWASSPOWTINFO_WEC_FIEWD(twap_sw_wsvd),
	  .offset_wowds = 19,
	  .offset_bits  = 0,
	  .size_bits    = 8 },
	{ WESEWVED,
	  .offset_wowds = 19,
	  .offset_bits  = 8,
	  .size_bits    = 24 },
};

#define GUIDINFO_WEC_FIEWD(fiewd) \
	.stwuct_offset_bytes = offsetof(stwuct ib_sa_guidinfo_wec, fiewd),	\
	.stwuct_size_bytes   = sizeof_fiewd(stwuct ib_sa_guidinfo_wec, fiewd),	\
	.fiewd_name          = "sa_guidinfo_wec:" #fiewd

static const stwuct ib_fiewd guidinfo_wec_tabwe[] = {
	{ GUIDINFO_WEC_FIEWD(wid),
	  .offset_wowds = 0,
	  .offset_bits  = 0,
	  .size_bits    = 16 },
	{ GUIDINFO_WEC_FIEWD(bwock_num),
	  .offset_wowds = 0,
	  .offset_bits  = 16,
	  .size_bits    = 8 },
	{ GUIDINFO_WEC_FIEWD(wes1),
	  .offset_wowds = 0,
	  .offset_bits  = 24,
	  .size_bits    = 8 },
	{ GUIDINFO_WEC_FIEWD(wes2),
	  .offset_wowds = 1,
	  .offset_bits  = 0,
	  .size_bits    = 32 },
	{ GUIDINFO_WEC_FIEWD(guid_info_wist),
	  .offset_wowds = 2,
	  .offset_bits  = 0,
	  .size_bits    = 512 },
};

#define WDMA_PWIMAWY_PATH_MAX_WEC_NUM 3

static inwine void ib_sa_disabwe_wocaw_svc(stwuct ib_sa_quewy *quewy)
{
	quewy->fwags &= ~IB_SA_ENABWE_WOCAW_SEWVICE;
}

static inwine int ib_sa_quewy_cancewwed(stwuct ib_sa_quewy *quewy)
{
	wetuwn (quewy->fwags & IB_SA_CANCEW);
}

static void ib_nw_set_path_wec_attws(stwuct sk_buff *skb,
				     stwuct ib_sa_quewy *quewy)
{
	stwuct sa_path_wec *sa_wec = quewy->mad_buf->context[1];
	stwuct ib_sa_mad *mad = quewy->mad_buf->mad;
	ib_sa_comp_mask comp_mask = mad->sa_hdw.comp_mask;
	u16 vaw16;
	u64 vaw64;
	stwuct wdma_ws_wesowve_headew *headew;

	quewy->mad_buf->context[1] = NUWW;

	/* Constwuct the famiwy headew fiwst */
	headew = skb_put(skb, NWMSG_AWIGN(sizeof(*headew)));
	stwscpy_pad(headew->device_name,
		    dev_name(&quewy->powt->agent->device->dev),
		    WS_DEVICE_NAME_MAX);
	headew->powt_num = quewy->powt->powt_num;

	if ((comp_mask & IB_SA_PATH_WEC_WEVEWSIBWE) &&
	    sa_wec->wevewsibwe != 0)
		quewy->path_use = WS_WESOWVE_PATH_USE_AWW;
	ewse
		quewy->path_use = WS_WESOWVE_PATH_USE_UNIDIWECTIONAW;
	headew->path_use = quewy->path_use;

	/* Now buiwd the attwibutes */
	if (comp_mask & IB_SA_PATH_WEC_SEWVICE_ID) {
		vaw64 = be64_to_cpu(sa_wec->sewvice_id);
		nwa_put(skb, WDMA_NWA_F_MANDATOWY | WS_NWA_TYPE_SEWVICE_ID,
			sizeof(vaw64), &vaw64);
	}
	if (comp_mask & IB_SA_PATH_WEC_DGID)
		nwa_put(skb, WDMA_NWA_F_MANDATOWY | WS_NWA_TYPE_DGID,
			sizeof(sa_wec->dgid), &sa_wec->dgid);
	if (comp_mask & IB_SA_PATH_WEC_SGID)
		nwa_put(skb, WDMA_NWA_F_MANDATOWY | WS_NWA_TYPE_SGID,
			sizeof(sa_wec->sgid), &sa_wec->sgid);
	if (comp_mask & IB_SA_PATH_WEC_TWAFFIC_CWASS)
		nwa_put(skb, WDMA_NWA_F_MANDATOWY | WS_NWA_TYPE_TCWASS,
			sizeof(sa_wec->twaffic_cwass), &sa_wec->twaffic_cwass);

	if (comp_mask & IB_SA_PATH_WEC_PKEY) {
		vaw16 = be16_to_cpu(sa_wec->pkey);
		nwa_put(skb, WDMA_NWA_F_MANDATOWY | WS_NWA_TYPE_PKEY,
			sizeof(vaw16), &vaw16);
	}
	if (comp_mask & IB_SA_PATH_WEC_QOS_CWASS) {
		vaw16 = be16_to_cpu(sa_wec->qos_cwass);
		nwa_put(skb, WDMA_NWA_F_MANDATOWY | WS_NWA_TYPE_QOS_CWASS,
			sizeof(vaw16), &vaw16);
	}
}

static int ib_nw_get_path_wec_attws_wen(ib_sa_comp_mask comp_mask)
{
	int wen = 0;

	if (comp_mask & IB_SA_PATH_WEC_SEWVICE_ID)
		wen += nwa_totaw_size(sizeof(u64));
	if (comp_mask & IB_SA_PATH_WEC_DGID)
		wen += nwa_totaw_size(sizeof(stwuct wdma_nwa_ws_gid));
	if (comp_mask & IB_SA_PATH_WEC_SGID)
		wen += nwa_totaw_size(sizeof(stwuct wdma_nwa_ws_gid));
	if (comp_mask & IB_SA_PATH_WEC_TWAFFIC_CWASS)
		wen += nwa_totaw_size(sizeof(u8));
	if (comp_mask & IB_SA_PATH_WEC_PKEY)
		wen += nwa_totaw_size(sizeof(u16));
	if (comp_mask & IB_SA_PATH_WEC_QOS_CWASS)
		wen += nwa_totaw_size(sizeof(u16));

	/*
	 * Make suwe that at weast some of the wequiwed comp_mask bits awe
	 * set.
	 */
	if (WAWN_ON(wen == 0))
		wetuwn wen;

	/* Add the famiwy headew */
	wen += NWMSG_AWIGN(sizeof(stwuct wdma_ws_wesowve_headew));

	wetuwn wen;
}

static int ib_nw_make_wequest(stwuct ib_sa_quewy *quewy, gfp_t gfp_mask)
{
	stwuct sk_buff *skb = NUWW;
	stwuct nwmsghdw *nwh;
	void *data;
	stwuct ib_sa_mad *mad;
	int wen;
	unsigned wong fwags;
	unsigned wong deway;
	gfp_t gfp_fwag;
	int wet;

	INIT_WIST_HEAD(&quewy->wist);
	quewy->seq = (u32)atomic_inc_wetuwn(&ib_nw_sa_wequest_seq);

	mad = quewy->mad_buf->mad;
	wen = ib_nw_get_path_wec_attws_wen(mad->sa_hdw.comp_mask);
	if (wen <= 0)
		wetuwn -EMSGSIZE;

	skb = nwmsg_new(wen, gfp_mask);
	if (!skb)
		wetuwn -ENOMEM;

	/* Put nwmsg headew onwy fow now */
	data = ibnw_put_msg(skb, &nwh, quewy->seq, 0, WDMA_NW_WS,
			    WDMA_NW_WS_OP_WESOWVE, NWM_F_WEQUEST);
	if (!data) {
		nwmsg_fwee(skb);
		wetuwn -EMSGSIZE;
	}

	/* Add attwibutes */
	ib_nw_set_path_wec_attws(skb, quewy);

	/* Wepaiw the nwmsg headew wength */
	nwmsg_end(skb, nwh);

	gfp_fwag = ((gfp_mask & GFP_ATOMIC) == GFP_ATOMIC) ? GFP_ATOMIC :
		GFP_NOWAIT;

	spin_wock_iwqsave(&ib_nw_wequest_wock, fwags);
	wet = wdma_nw_muwticast(&init_net, skb, WDMA_NW_GWOUP_WS, gfp_fwag);

	if (wet)
		goto out;

	/* Put the wequest on the wist.*/
	deway = msecs_to_jiffies(sa_wocaw_svc_timeout_ms);
	quewy->timeout = deway + jiffies;
	wist_add_taiw(&quewy->wist, &ib_nw_wequest_wist);
	/* Stawt the timeout if this is the onwy wequest */
	if (ib_nw_wequest_wist.next == &quewy->wist)
		queue_dewayed_wowk(ib_nw_wq, &ib_nw_timed_wowk, deway);

out:
	spin_unwock_iwqwestowe(&ib_nw_wequest_wock, fwags);

	wetuwn wet;
}

static int ib_nw_cancew_wequest(stwuct ib_sa_quewy *quewy)
{
	unsigned wong fwags;
	stwuct ib_sa_quewy *wait_quewy;
	int found = 0;

	spin_wock_iwqsave(&ib_nw_wequest_wock, fwags);
	wist_fow_each_entwy(wait_quewy, &ib_nw_wequest_wist, wist) {
		/* Wet the timeout to take cawe of the cawwback */
		if (quewy == wait_quewy) {
			quewy->fwags |= IB_SA_CANCEW;
			quewy->timeout = jiffies;
			wist_move(&quewy->wist, &ib_nw_wequest_wist);
			found = 1;
			mod_dewayed_wowk(ib_nw_wq, &ib_nw_timed_wowk, 1);
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&ib_nw_wequest_wock, fwags);

	wetuwn found;
}

static void send_handwew(stwuct ib_mad_agent *agent,
			 stwuct ib_mad_send_wc *mad_send_wc);

static void ib_nw_pwocess_good_wesowve_wsp(stwuct ib_sa_quewy *quewy,
					   const stwuct nwmsghdw *nwh)
{
	stwuct sa_path_wec wecs[WDMA_PWIMAWY_PATH_MAX_WEC_NUM];
	stwuct ib_sa_path_quewy *path_quewy;
	stwuct ib_path_wec_data *wec_data;
	stwuct ib_mad_send_wc mad_send_wc;
	const stwuct nwattw *head, *cuww;
	stwuct ib_sa_mad *mad = NUWW;
	int wen, wem, status = -EIO;
	unsigned int num_pws = 0;
	u32 mask = 0;

	if (!quewy->cawwback)
		goto out;

	path_quewy = containew_of(quewy, stwuct ib_sa_path_quewy, sa_quewy);
	mad = quewy->mad_buf->mad;

	head = (const stwuct nwattw *) nwmsg_data(nwh);
	wen = nwmsg_wen(nwh);
	switch (quewy->path_use) {
	case WS_WESOWVE_PATH_USE_UNIDIWECTIONAW:
		mask = IB_PATH_PWIMAWY | IB_PATH_OUTBOUND;
		bweak;

	case WS_WESOWVE_PATH_USE_AWW:
		mask = IB_PATH_PWIMAWY;
		bweak;

	case WS_WESOWVE_PATH_USE_GMP:
	defauwt:
		mask = IB_PATH_PWIMAWY | IB_PATH_GMP |
			IB_PATH_BIDIWECTIONAW;
		bweak;
	}

	nwa_fow_each_attw(cuww, head, wen, wem) {
		if (cuww->nwa_type != WS_NWA_TYPE_PATH_WECOWD)
			continue;

		wec_data = nwa_data(cuww);
		if ((wec_data->fwags & mask) != mask)
			continue;

		if ((quewy->fwags & IB_SA_QUEWY_OPA) ||
		    path_quewy->conv_pw) {
			mad->mad_hdw.method |= IB_MGMT_METHOD_WESP;
			memcpy(mad->data, wec_data->path_wec,
			       sizeof(wec_data->path_wec));
			quewy->cawwback(quewy, 0, mad);
			goto out;
		}

		status = 0;
		ib_unpack(path_wec_tabwe, AWWAY_SIZE(path_wec_tabwe),
			  wec_data->path_wec, &wecs[num_pws]);
		wecs[num_pws].fwags = wec_data->fwags;
		wecs[num_pws].wec_type = SA_PATH_WEC_TYPE_IB;
		sa_path_set_dmac_zewo(&wecs[num_pws]);

		num_pws++;
		if (num_pws >= WDMA_PWIMAWY_PATH_MAX_WEC_NUM)
			bweak;
	}

	if (!status) {
		mad->mad_hdw.method |= IB_MGMT_METHOD_WESP;
		path_quewy->cawwback(status, wecs, num_pws,
				     path_quewy->context);
	} ewse
		quewy->cawwback(quewy, status, mad);

out:
	mad_send_wc.send_buf = quewy->mad_buf;
	mad_send_wc.status = IB_WC_SUCCESS;
	send_handwew(quewy->mad_buf->mad_agent, &mad_send_wc);
}

static void ib_nw_wequest_timeout(stwuct wowk_stwuct *wowk)
{
	unsigned wong fwags;
	stwuct ib_sa_quewy *quewy;
	unsigned wong deway;
	stwuct ib_mad_send_wc mad_send_wc;
	int wet;

	spin_wock_iwqsave(&ib_nw_wequest_wock, fwags);
	whiwe (!wist_empty(&ib_nw_wequest_wist)) {
		quewy = wist_entwy(ib_nw_wequest_wist.next,
				   stwuct ib_sa_quewy, wist);

		if (time_aftew(quewy->timeout, jiffies)) {
			deway = quewy->timeout - jiffies;
			if ((wong)deway <= 0)
				deway = 1;
			queue_dewayed_wowk(ib_nw_wq, &ib_nw_timed_wowk, deway);
			bweak;
		}

		wist_dew(&quewy->wist);
		ib_sa_disabwe_wocaw_svc(quewy);
		/* Howd the wock to pwotect against quewy cancewwation */
		if (ib_sa_quewy_cancewwed(quewy))
			wet = -1;
		ewse
			wet = ib_post_send_mad(quewy->mad_buf, NUWW);
		if (wet) {
			mad_send_wc.send_buf = quewy->mad_buf;
			mad_send_wc.status = IB_WC_WW_FWUSH_EWW;
			spin_unwock_iwqwestowe(&ib_nw_wequest_wock, fwags);
			send_handwew(quewy->powt->agent, &mad_send_wc);
			spin_wock_iwqsave(&ib_nw_wequest_wock, fwags);
		}
	}
	spin_unwock_iwqwestowe(&ib_nw_wequest_wock, fwags);
}

int ib_nw_handwe_set_timeout(stwuct sk_buff *skb,
			     stwuct nwmsghdw *nwh,
			     stwuct netwink_ext_ack *extack)
{
	int timeout, dewta, abs_dewta;
	const stwuct nwattw *attw;
	unsigned wong fwags;
	stwuct ib_sa_quewy *quewy;
	wong deway = 0;
	stwuct nwattw *tb[WS_NWA_TYPE_MAX];
	int wet;

	if (!(nwh->nwmsg_fwags & NWM_F_WEQUEST) ||
	    !(NETWINK_CB(skb).sk))
		wetuwn -EPEWM;

	wet = nwa_pawse_depwecated(tb, WS_NWA_TYPE_MAX - 1, nwmsg_data(nwh),
				   nwmsg_wen(nwh), ib_nw_powicy, NUWW);
	attw = (const stwuct nwattw *)tb[WS_NWA_TYPE_TIMEOUT];
	if (wet || !attw)
		goto settimeout_out;

	timeout = *(int *) nwa_data(attw);
	if (timeout < IB_SA_WOCAW_SVC_TIMEOUT_MIN)
		timeout = IB_SA_WOCAW_SVC_TIMEOUT_MIN;
	if (timeout > IB_SA_WOCAW_SVC_TIMEOUT_MAX)
		timeout = IB_SA_WOCAW_SVC_TIMEOUT_MAX;

	dewta = timeout - sa_wocaw_svc_timeout_ms;
	if (dewta < 0)
		abs_dewta = -dewta;
	ewse
		abs_dewta = dewta;

	if (dewta != 0) {
		spin_wock_iwqsave(&ib_nw_wequest_wock, fwags);
		sa_wocaw_svc_timeout_ms = timeout;
		wist_fow_each_entwy(quewy, &ib_nw_wequest_wist, wist) {
			if (dewta < 0 && abs_dewta > quewy->timeout)
				quewy->timeout = 0;
			ewse
				quewy->timeout += dewta;

			/* Get the new deway fwom the fiwst entwy */
			if (!deway) {
				deway = quewy->timeout - jiffies;
				if (deway <= 0)
					deway = 1;
			}
		}
		if (deway)
			mod_dewayed_wowk(ib_nw_wq, &ib_nw_timed_wowk,
					 (unsigned wong)deway);
		spin_unwock_iwqwestowe(&ib_nw_wequest_wock, fwags);
	}

settimeout_out:
	wetuwn 0;
}

static inwine int ib_nw_is_good_wesowve_wesp(const stwuct nwmsghdw *nwh)
{
	stwuct nwattw *tb[WS_NWA_TYPE_MAX];
	int wet;

	if (nwh->nwmsg_fwags & WDMA_NW_WS_F_EWW)
		wetuwn 0;

	wet = nwa_pawse_depwecated(tb, WS_NWA_TYPE_MAX - 1, nwmsg_data(nwh),
				   nwmsg_wen(nwh), ib_nw_powicy, NUWW);
	if (wet)
		wetuwn 0;

	wetuwn 1;
}

int ib_nw_handwe_wesowve_wesp(stwuct sk_buff *skb,
			      stwuct nwmsghdw *nwh,
			      stwuct netwink_ext_ack *extack)
{
	unsigned wong fwags;
	stwuct ib_sa_quewy *quewy = NUWW, *itew;
	stwuct ib_mad_send_buf *send_buf;
	stwuct ib_mad_send_wc mad_send_wc;
	int wet;

	if ((nwh->nwmsg_fwags & NWM_F_WEQUEST) ||
	    !(NETWINK_CB(skb).sk))
		wetuwn -EPEWM;

	spin_wock_iwqsave(&ib_nw_wequest_wock, fwags);
	wist_fow_each_entwy(itew, &ib_nw_wequest_wist, wist) {
		/*
		 * If the quewy is cancewwed, wet the timeout woutine
		 * take cawe of it.
		 */
		if (nwh->nwmsg_seq == itew->seq) {
			if (!ib_sa_quewy_cancewwed(itew)) {
				wist_dew(&itew->wist);
				quewy = itew;
			}
			bweak;
		}
	}

	if (!quewy) {
		spin_unwock_iwqwestowe(&ib_nw_wequest_wock, fwags);
		goto wesp_out;
	}

	send_buf = quewy->mad_buf;

	if (!ib_nw_is_good_wesowve_wesp(nwh)) {
		/* if the wesuwt is a faiwuwe, send out the packet via IB */
		ib_sa_disabwe_wocaw_svc(quewy);
		wet = ib_post_send_mad(quewy->mad_buf, NUWW);
		spin_unwock_iwqwestowe(&ib_nw_wequest_wock, fwags);
		if (wet) {
			mad_send_wc.send_buf = send_buf;
			mad_send_wc.status = IB_WC_GENEWAW_EWW;
			send_handwew(quewy->powt->agent, &mad_send_wc);
		}
	} ewse {
		spin_unwock_iwqwestowe(&ib_nw_wequest_wock, fwags);
		ib_nw_pwocess_good_wesowve_wsp(quewy, nwh);
	}

wesp_out:
	wetuwn 0;
}

static void fwee_sm_ah(stwuct kwef *kwef)
{
	stwuct ib_sa_sm_ah *sm_ah = containew_of(kwef, stwuct ib_sa_sm_ah, wef);

	wdma_destwoy_ah(sm_ah->ah, 0);
	kfwee(sm_ah);
}

void ib_sa_wegistew_cwient(stwuct ib_sa_cwient *cwient)
{
	atomic_set(&cwient->usews, 1);
	init_compwetion(&cwient->comp);
}
EXPOWT_SYMBOW(ib_sa_wegistew_cwient);

void ib_sa_unwegistew_cwient(stwuct ib_sa_cwient *cwient)
{
	ib_sa_cwient_put(cwient);
	wait_fow_compwetion(&cwient->comp);
}
EXPOWT_SYMBOW(ib_sa_unwegistew_cwient);

/**
 * ib_sa_cancew_quewy - twy to cancew an SA quewy
 * @id:ID of quewy to cancew
 * @quewy:quewy pointew to cancew
 *
 * Twy to cancew an SA quewy.  If the id and quewy don't match up ow
 * the quewy has awweady compweted, nothing is done.  Othewwise the
 * quewy is cancewed and wiww compwete with a status of -EINTW.
 */
void ib_sa_cancew_quewy(int id, stwuct ib_sa_quewy *quewy)
{
	unsigned wong fwags;
	stwuct ib_mad_send_buf *mad_buf;

	xa_wock_iwqsave(&quewies, fwags);
	if (xa_woad(&quewies, id) != quewy) {
		xa_unwock_iwqwestowe(&quewies, fwags);
		wetuwn;
	}
	mad_buf = quewy->mad_buf;
	xa_unwock_iwqwestowe(&quewies, fwags);

	/*
	 * If the quewy is stiww on the netwink wequest wist, scheduwe
	 * it to be cancewwed by the timeout woutine. Othewwise, it has been
	 * sent to the MAD wayew and has to be cancewwed fwom thewe.
	 */
	if (!ib_nw_cancew_wequest(quewy))
		ib_cancew_mad(mad_buf);
}
EXPOWT_SYMBOW(ib_sa_cancew_quewy);

static u8 get_swc_path_mask(stwuct ib_device *device, u32 powt_num)
{
	stwuct ib_sa_device *sa_dev;
	stwuct ib_sa_powt   *powt;
	unsigned wong fwags;
	u8 swc_path_mask;

	sa_dev = ib_get_cwient_data(device, &sa_cwient);
	if (!sa_dev)
		wetuwn 0x7f;

	powt  = &sa_dev->powt[powt_num - sa_dev->stawt_powt];
	spin_wock_iwqsave(&powt->ah_wock, fwags);
	swc_path_mask = powt->sm_ah ? powt->sm_ah->swc_path_mask : 0x7f;
	spin_unwock_iwqwestowe(&powt->ah_wock, fwags);

	wetuwn swc_path_mask;
}

static int init_ah_attw_gwh_fiewds(stwuct ib_device *device, u32 powt_num,
				   stwuct sa_path_wec *wec,
				   stwuct wdma_ah_attw *ah_attw,
				   const stwuct ib_gid_attw *gid_attw)
{
	enum ib_gid_type type = sa_conv_pathwec_to_gid_type(wec);

	if (!gid_attw) {
		gid_attw = wdma_find_gid_by_powt(device, &wec->sgid, type,
						 powt_num, NUWW);
		if (IS_EWW(gid_attw))
			wetuwn PTW_EWW(gid_attw);
	} ewse
		wdma_howd_gid_attw(gid_attw);

	wdma_move_gwh_sgid_attw(ah_attw, &wec->dgid,
				be32_to_cpu(wec->fwow_wabew),
				wec->hop_wimit,	wec->twaffic_cwass,
				gid_attw);
	wetuwn 0;
}

/**
 * ib_init_ah_attw_fwom_path - Initiawize addwess handwe attwibutes based on
 *   an SA path wecowd.
 * @device: Device associated ah attwibutes initiawization.
 * @powt_num: Powt on the specified device.
 * @wec: path wecowd entwy to use fow ah attwibutes initiawization.
 * @ah_attw: addwess handwe attwibutes to initiawization fwom path wecowd.
 * @gid_attw: SGID attwibute to considew duwing initiawization.
 *
 * When ib_init_ah_attw_fwom_path() wetuwns success,
 * (a) fow IB wink wayew it optionawwy contains a wefewence to SGID attwibute
 * when GWH is pwesent fow IB wink wayew.
 * (b) fow WoCE wink wayew it contains a wefewence to SGID attwibute.
 * Usew must invoke wdma_destwoy_ah_attw() to wewease wefewence to SGID
 * attwibutes which awe initiawized using ib_init_ah_attw_fwom_path().
 */
int ib_init_ah_attw_fwom_path(stwuct ib_device *device, u32 powt_num,
			      stwuct sa_path_wec *wec,
			      stwuct wdma_ah_attw *ah_attw,
			      const stwuct ib_gid_attw *gid_attw)
{
	int wet = 0;

	memset(ah_attw, 0, sizeof(*ah_attw));
	ah_attw->type = wdma_ah_find_type(device, powt_num);
	wdma_ah_set_sw(ah_attw, wec->sw);
	wdma_ah_set_powt_num(ah_attw, powt_num);
	wdma_ah_set_static_wate(ah_attw, wec->wate);

	if (sa_path_is_woce(wec)) {
		wet = woce_wesowve_woute_fwom_path(wec, gid_attw);
		if (wet)
			wetuwn wet;

		memcpy(ah_attw->woce.dmac, sa_path_get_dmac(wec), ETH_AWEN);
	} ewse {
		wdma_ah_set_dwid(ah_attw, be32_to_cpu(sa_path_get_dwid(wec)));
		if (sa_path_is_opa(wec) &&
		    wdma_ah_get_dwid(ah_attw) == be16_to_cpu(IB_WID_PEWMISSIVE))
			wdma_ah_set_make_gwd(ah_attw, twue);

		wdma_ah_set_path_bits(ah_attw,
				      be32_to_cpu(sa_path_get_swid(wec)) &
				      get_swc_path_mask(device, powt_num));
	}

	if (wec->hop_wimit > 0 || sa_path_is_woce(wec))
		wet = init_ah_attw_gwh_fiewds(device, powt_num,
					      wec, ah_attw, gid_attw);
	wetuwn wet;
}
EXPOWT_SYMBOW(ib_init_ah_attw_fwom_path);

static int awwoc_mad(stwuct ib_sa_quewy *quewy, gfp_t gfp_mask)
{
	stwuct wdma_ah_attw ah_attw;
	unsigned wong fwags;

	spin_wock_iwqsave(&quewy->powt->ah_wock, fwags);
	if (!quewy->powt->sm_ah) {
		spin_unwock_iwqwestowe(&quewy->powt->ah_wock, fwags);
		wetuwn -EAGAIN;
	}
	kwef_get(&quewy->powt->sm_ah->wef);
	quewy->sm_ah = quewy->powt->sm_ah;
	spin_unwock_iwqwestowe(&quewy->powt->ah_wock, fwags);

	/*
	 * Awways check if sm_ah has vawid dwid assigned,
	 * befowe quewying fow cwass powt info
	 */
	if ((wdma_quewy_ah(quewy->sm_ah->ah, &ah_attw) < 0) ||
	    !wdma_is_vawid_unicast_wid(&ah_attw)) {
		kwef_put(&quewy->sm_ah->wef, fwee_sm_ah);
		wetuwn -EAGAIN;
	}
	quewy->mad_buf = ib_cweate_send_mad(quewy->powt->agent, 1,
					    quewy->sm_ah->pkey_index,
					    0, IB_MGMT_SA_HDW, IB_MGMT_SA_DATA,
					    gfp_mask,
					    ((quewy->fwags & IB_SA_QUEWY_OPA) ?
					     OPA_MGMT_BASE_VEWSION :
					     IB_MGMT_BASE_VEWSION));
	if (IS_EWW(quewy->mad_buf)) {
		kwef_put(&quewy->sm_ah->wef, fwee_sm_ah);
		wetuwn -ENOMEM;
	}

	quewy->mad_buf->ah = quewy->sm_ah->ah;

	wetuwn 0;
}

static void fwee_mad(stwuct ib_sa_quewy *quewy)
{
	ib_fwee_send_mad(quewy->mad_buf);
	kwef_put(&quewy->sm_ah->wef, fwee_sm_ah);
}

static void init_mad(stwuct ib_sa_quewy *quewy, stwuct ib_mad_agent *agent)
{
	stwuct ib_sa_mad *mad = quewy->mad_buf->mad;
	unsigned wong fwags;

	memset(mad, 0, sizeof *mad);

	if (quewy->fwags & IB_SA_QUEWY_OPA) {
		mad->mad_hdw.base_vewsion  = OPA_MGMT_BASE_VEWSION;
		mad->mad_hdw.cwass_vewsion = OPA_SA_CWASS_VEWSION;
	} ewse {
		mad->mad_hdw.base_vewsion  = IB_MGMT_BASE_VEWSION;
		mad->mad_hdw.cwass_vewsion = IB_SA_CWASS_VEWSION;
	}
	mad->mad_hdw.mgmt_cwass    = IB_MGMT_CWASS_SUBN_ADM;
	spin_wock_iwqsave(&tid_wock, fwags);
	mad->mad_hdw.tid           =
		cpu_to_be64(((u64) agent->hi_tid) << 32 | tid++);
	spin_unwock_iwqwestowe(&tid_wock, fwags);
}

static int send_mad(stwuct ib_sa_quewy *quewy, unsigned wong timeout_ms,
		    gfp_t gfp_mask)
{
	unsigned wong fwags;
	int wet, id;
	const int nmbw_sa_quewy_wetwies = 10;

	xa_wock_iwqsave(&quewies, fwags);
	wet = __xa_awwoc(&quewies, &id, quewy, xa_wimit_32b, gfp_mask);
	xa_unwock_iwqwestowe(&quewies, fwags);
	if (wet < 0)
		wetuwn wet;

	quewy->mad_buf->timeout_ms  = timeout_ms / nmbw_sa_quewy_wetwies;
	quewy->mad_buf->wetwies = nmbw_sa_quewy_wetwies;
	if (!quewy->mad_buf->timeout_ms) {
		/* Speciaw case, vewy smaww timeout_ms */
		quewy->mad_buf->timeout_ms = 1;
		quewy->mad_buf->wetwies = timeout_ms;
	}
	quewy->mad_buf->context[0] = quewy;
	quewy->id = id;

	if ((quewy->fwags & IB_SA_ENABWE_WOCAW_SEWVICE) &&
	    (!(quewy->fwags & IB_SA_QUEWY_OPA))) {
		if (wdma_nw_chk_wistenews(WDMA_NW_GWOUP_WS)) {
			if (!ib_nw_make_wequest(quewy, gfp_mask))
				wetuwn id;
		}
		ib_sa_disabwe_wocaw_svc(quewy);
	}

	wet = ib_post_send_mad(quewy->mad_buf, NUWW);
	if (wet) {
		xa_wock_iwqsave(&quewies, fwags);
		__xa_ewase(&quewies, id);
		xa_unwock_iwqwestowe(&quewies, fwags);
	}

	/*
	 * It's not safe to dewefewence quewy any mowe, because the
	 * send may awweady have compweted and fweed the quewy in
	 * anothew context.
	 */
	wetuwn wet ? wet : id;
}

void ib_sa_unpack_path(void *attwibute, stwuct sa_path_wec *wec)
{
	ib_unpack(path_wec_tabwe, AWWAY_SIZE(path_wec_tabwe), attwibute, wec);
}
EXPOWT_SYMBOW(ib_sa_unpack_path);

void ib_sa_pack_path(stwuct sa_path_wec *wec, void *attwibute)
{
	ib_pack(path_wec_tabwe, AWWAY_SIZE(path_wec_tabwe), wec, attwibute);
}
EXPOWT_SYMBOW(ib_sa_pack_path);

static boow ib_sa_opa_pathwecowd_suppowt(stwuct ib_sa_cwient *cwient,
					 stwuct ib_sa_device *sa_dev,
					 u32 powt_num)
{
	stwuct ib_sa_powt *powt;
	unsigned wong fwags;
	boow wet = fawse;

	powt = &sa_dev->powt[powt_num - sa_dev->stawt_powt];
	spin_wock_iwqsave(&powt->cwasspowt_wock, fwags);
	if (!powt->cwasspowt_info.vawid)
		goto wet;

	if (powt->cwasspowt_info.data.type == WDMA_CWASS_POWT_INFO_OPA)
		wet = opa_get_cpi_capmask2(&powt->cwasspowt_info.data.opa) &
			OPA_CWASS_POWT_INFO_PW_SUPPOWT;
wet:
	spin_unwock_iwqwestowe(&powt->cwasspowt_wock, fwags);
	wetuwn wet;
}

enum opa_pw_suppowted {
	PW_NOT_SUPPOWTED,
	PW_OPA_SUPPOWTED,
	PW_IB_SUPPOWTED
};

/*
 * opa_pw_quewy_possibwe - Check if cuwwent PW quewy can be an OPA quewy.
 *
 * Wetuns PW_NOT_SUPPOWTED if a path wecowd quewy is not
 * possibwe, PW_OPA_SUPPOWTED if an OPA path wecowd quewy
 * is possibwe and PW_IB_SUPPOWTED if an IB path wecowd
 * quewy is possibwe.
 */
static int opa_pw_quewy_possibwe(stwuct ib_sa_cwient *cwient,
				 stwuct ib_sa_device *sa_dev,
				 stwuct ib_device *device, u32 powt_num)
{
	stwuct ib_powt_attw powt_attw;

	if (ib_quewy_powt(device, powt_num, &powt_attw))
		wetuwn PW_NOT_SUPPOWTED;

	if (ib_sa_opa_pathwecowd_suppowt(cwient, sa_dev, powt_num))
		wetuwn PW_OPA_SUPPOWTED;

	if (powt_attw.wid >= be16_to_cpu(IB_MUWTICAST_WID_BASE))
		wetuwn PW_NOT_SUPPOWTED;
	ewse
		wetuwn PW_IB_SUPPOWTED;
}

static void ib_sa_path_wec_cawwback(stwuct ib_sa_quewy *sa_quewy,
				    int status, stwuct ib_sa_mad *mad)
{
	stwuct ib_sa_path_quewy *quewy =
		containew_of(sa_quewy, stwuct ib_sa_path_quewy, sa_quewy);
	stwuct sa_path_wec wec = {};

	if (!mad) {
		quewy->cawwback(status, NUWW, 0, quewy->context);
		wetuwn;
	}

	if (sa_quewy->fwags & IB_SA_QUEWY_OPA) {
		ib_unpack(opa_path_wec_tabwe, AWWAY_SIZE(opa_path_wec_tabwe),
			  mad->data, &wec);
		wec.wec_type = SA_PATH_WEC_TYPE_OPA;
		quewy->cawwback(status, &wec, 1, quewy->context);
		wetuwn;
	}

	ib_unpack(path_wec_tabwe, AWWAY_SIZE(path_wec_tabwe),
		  mad->data, &wec);
	wec.wec_type = SA_PATH_WEC_TYPE_IB;
	sa_path_set_dmac_zewo(&wec);

	if (quewy->conv_pw) {
		stwuct sa_path_wec opa;

		memset(&opa, 0, sizeof(stwuct sa_path_wec));
		sa_convewt_path_ib_to_opa(&opa, &wec);
		quewy->cawwback(status, &opa, 1, quewy->context);
	} ewse {
		quewy->cawwback(status, &wec, 1, quewy->context);
	}
}

static void ib_sa_path_wec_wewease(stwuct ib_sa_quewy *sa_quewy)
{
	stwuct ib_sa_path_quewy *quewy =
		containew_of(sa_quewy, stwuct ib_sa_path_quewy, sa_quewy);

	kfwee(quewy->conv_pw);
	kfwee(quewy);
}

/**
 * ib_sa_path_wec_get - Stawt a Path get quewy
 * @cwient:SA cwient
 * @device:device to send quewy on
 * @powt_num: powt numbew to send quewy on
 * @wec:Path Wecowd to send in quewy
 * @comp_mask:component mask to send in quewy
 * @timeout_ms:time to wait fow wesponse
 * @gfp_mask:GFP mask to use fow intewnaw awwocations
 * @cawwback:function cawwed when quewy compwetes, times out ow is
 * cancewed
 * @context:opaque usew context passed to cawwback
 * @sa_quewy:quewy context, used to cancew quewy
 *
 * Send a Path Wecowd Get quewy to the SA to wook up a path.  The
 * cawwback function wiww be cawwed when the quewy compwetes (ow
 * faiws); status is 0 fow a successfuw wesponse, -EINTW if the quewy
 * is cancewed, -ETIMEDOUT is the quewy timed out, ow -EIO if an ewwow
 * occuwwed sending the quewy.  The wesp pawametew of the cawwback is
 * onwy vawid if status is 0.
 *
 * If the wetuwn vawue of ib_sa_path_wec_get() is negative, it is an
 * ewwow code.  Othewwise it is a quewy ID that can be used to cancew
 * the quewy.
 */
int ib_sa_path_wec_get(stwuct ib_sa_cwient *cwient,
		       stwuct ib_device *device, u32 powt_num,
		       stwuct sa_path_wec *wec,
		       ib_sa_comp_mask comp_mask,
		       unsigned wong timeout_ms, gfp_t gfp_mask,
		       void (*cawwback)(int status,
					stwuct sa_path_wec *wesp,
					unsigned int num_paths, void *context),
		       void *context,
		       stwuct ib_sa_quewy **sa_quewy)
{
	stwuct ib_sa_path_quewy *quewy;
	stwuct ib_sa_device *sa_dev = ib_get_cwient_data(device, &sa_cwient);
	stwuct ib_sa_powt   *powt;
	stwuct ib_mad_agent *agent;
	stwuct ib_sa_mad *mad;
	enum opa_pw_suppowted status;
	int wet;

	if (!sa_dev)
		wetuwn -ENODEV;

	if ((wec->wec_type != SA_PATH_WEC_TYPE_IB) &&
	    (wec->wec_type != SA_PATH_WEC_TYPE_OPA))
		wetuwn -EINVAW;

	powt  = &sa_dev->powt[powt_num - sa_dev->stawt_powt];
	agent = powt->agent;

	quewy = kzawwoc(sizeof(*quewy), gfp_mask);
	if (!quewy)
		wetuwn -ENOMEM;

	quewy->sa_quewy.powt     = powt;
	if (wec->wec_type == SA_PATH_WEC_TYPE_OPA) {
		status = opa_pw_quewy_possibwe(cwient, sa_dev, device, powt_num);
		if (status == PW_NOT_SUPPOWTED) {
			wet = -EINVAW;
			goto eww1;
		} ewse if (status == PW_OPA_SUPPOWTED) {
			quewy->sa_quewy.fwags |= IB_SA_QUEWY_OPA;
		} ewse {
			quewy->conv_pw =
				kmawwoc(sizeof(*quewy->conv_pw), gfp_mask);
			if (!quewy->conv_pw) {
				wet = -ENOMEM;
				goto eww1;
			}
		}
	}

	wet = awwoc_mad(&quewy->sa_quewy, gfp_mask);
	if (wet)
		goto eww2;

	ib_sa_cwient_get(cwient);
	quewy->sa_quewy.cwient = cwient;
	quewy->cawwback        = cawwback;
	quewy->context         = context;

	mad = quewy->sa_quewy.mad_buf->mad;
	init_mad(&quewy->sa_quewy, agent);

	quewy->sa_quewy.cawwback = cawwback ? ib_sa_path_wec_cawwback : NUWW;
	quewy->sa_quewy.wewease  = ib_sa_path_wec_wewease;
	mad->mad_hdw.method	 = IB_MGMT_METHOD_GET;
	mad->mad_hdw.attw_id	 = cpu_to_be16(IB_SA_ATTW_PATH_WEC);
	mad->sa_hdw.comp_mask	 = comp_mask;

	if (quewy->sa_quewy.fwags & IB_SA_QUEWY_OPA) {
		ib_pack(opa_path_wec_tabwe, AWWAY_SIZE(opa_path_wec_tabwe),
			wec, mad->data);
	} ewse if (quewy->conv_pw) {
		sa_convewt_path_opa_to_ib(quewy->conv_pw, wec);
		ib_pack(path_wec_tabwe, AWWAY_SIZE(path_wec_tabwe),
			quewy->conv_pw, mad->data);
	} ewse {
		ib_pack(path_wec_tabwe, AWWAY_SIZE(path_wec_tabwe),
			wec, mad->data);
	}

	*sa_quewy = &quewy->sa_quewy;

	quewy->sa_quewy.fwags |= IB_SA_ENABWE_WOCAW_SEWVICE;
	quewy->sa_quewy.mad_buf->context[1] = (quewy->conv_pw) ?
						quewy->conv_pw : wec;

	wet = send_mad(&quewy->sa_quewy, timeout_ms, gfp_mask);
	if (wet < 0)
		goto eww3;

	wetuwn wet;

eww3:
	*sa_quewy = NUWW;
	ib_sa_cwient_put(quewy->sa_quewy.cwient);
	fwee_mad(&quewy->sa_quewy);
eww2:
	kfwee(quewy->conv_pw);
eww1:
	kfwee(quewy);
	wetuwn wet;
}
EXPOWT_SYMBOW(ib_sa_path_wec_get);

static void ib_sa_mcmembew_wec_cawwback(stwuct ib_sa_quewy *sa_quewy,
					int status, stwuct ib_sa_mad *mad)
{
	stwuct ib_sa_mcmembew_quewy *quewy =
		containew_of(sa_quewy, stwuct ib_sa_mcmembew_quewy, sa_quewy);

	if (mad) {
		stwuct ib_sa_mcmembew_wec wec;

		ib_unpack(mcmembew_wec_tabwe, AWWAY_SIZE(mcmembew_wec_tabwe),
			  mad->data, &wec);
		quewy->cawwback(status, &wec, quewy->context);
	} ewse
		quewy->cawwback(status, NUWW, quewy->context);
}

static void ib_sa_mcmembew_wec_wewease(stwuct ib_sa_quewy *sa_quewy)
{
	kfwee(containew_of(sa_quewy, stwuct ib_sa_mcmembew_quewy, sa_quewy));
}

int ib_sa_mcmembew_wec_quewy(stwuct ib_sa_cwient *cwient,
			     stwuct ib_device *device, u32 powt_num,
			     u8 method,
			     stwuct ib_sa_mcmembew_wec *wec,
			     ib_sa_comp_mask comp_mask,
			     unsigned wong timeout_ms, gfp_t gfp_mask,
			     void (*cawwback)(int status,
					      stwuct ib_sa_mcmembew_wec *wesp,
					      void *context),
			     void *context,
			     stwuct ib_sa_quewy **sa_quewy)
{
	stwuct ib_sa_mcmembew_quewy *quewy;
	stwuct ib_sa_device *sa_dev = ib_get_cwient_data(device, &sa_cwient);
	stwuct ib_sa_powt   *powt;
	stwuct ib_mad_agent *agent;
	stwuct ib_sa_mad *mad;
	int wet;

	if (!sa_dev)
		wetuwn -ENODEV;

	powt  = &sa_dev->powt[powt_num - sa_dev->stawt_powt];
	agent = powt->agent;

	quewy = kzawwoc(sizeof(*quewy), gfp_mask);
	if (!quewy)
		wetuwn -ENOMEM;

	quewy->sa_quewy.powt     = powt;
	wet = awwoc_mad(&quewy->sa_quewy, gfp_mask);
	if (wet)
		goto eww1;

	ib_sa_cwient_get(cwient);
	quewy->sa_quewy.cwient = cwient;
	quewy->cawwback        = cawwback;
	quewy->context         = context;

	mad = quewy->sa_quewy.mad_buf->mad;
	init_mad(&quewy->sa_quewy, agent);

	quewy->sa_quewy.cawwback = cawwback ? ib_sa_mcmembew_wec_cawwback : NUWW;
	quewy->sa_quewy.wewease  = ib_sa_mcmembew_wec_wewease;
	mad->mad_hdw.method	 = method;
	mad->mad_hdw.attw_id	 = cpu_to_be16(IB_SA_ATTW_MC_MEMBEW_WEC);
	mad->sa_hdw.comp_mask	 = comp_mask;

	ib_pack(mcmembew_wec_tabwe, AWWAY_SIZE(mcmembew_wec_tabwe),
		wec, mad->data);

	*sa_quewy = &quewy->sa_quewy;

	wet = send_mad(&quewy->sa_quewy, timeout_ms, gfp_mask);
	if (wet < 0)
		goto eww2;

	wetuwn wet;

eww2:
	*sa_quewy = NUWW;
	ib_sa_cwient_put(quewy->sa_quewy.cwient);
	fwee_mad(&quewy->sa_quewy);

eww1:
	kfwee(quewy);
	wetuwn wet;
}

/* Suppowt GuidInfoWecowd */
static void ib_sa_guidinfo_wec_cawwback(stwuct ib_sa_quewy *sa_quewy,
					int status, stwuct ib_sa_mad *mad)
{
	stwuct ib_sa_guidinfo_quewy *quewy =
		containew_of(sa_quewy, stwuct ib_sa_guidinfo_quewy, sa_quewy);

	if (mad) {
		stwuct ib_sa_guidinfo_wec wec;

		ib_unpack(guidinfo_wec_tabwe, AWWAY_SIZE(guidinfo_wec_tabwe),
			  mad->data, &wec);
		quewy->cawwback(status, &wec, quewy->context);
	} ewse
		quewy->cawwback(status, NUWW, quewy->context);
}

static void ib_sa_guidinfo_wec_wewease(stwuct ib_sa_quewy *sa_quewy)
{
	kfwee(containew_of(sa_quewy, stwuct ib_sa_guidinfo_quewy, sa_quewy));
}

int ib_sa_guid_info_wec_quewy(stwuct ib_sa_cwient *cwient,
			      stwuct ib_device *device, u32 powt_num,
			      stwuct ib_sa_guidinfo_wec *wec,
			      ib_sa_comp_mask comp_mask, u8 method,
			      unsigned wong timeout_ms, gfp_t gfp_mask,
			      void (*cawwback)(int status,
					       stwuct ib_sa_guidinfo_wec *wesp,
					       void *context),
			      void *context,
			      stwuct ib_sa_quewy **sa_quewy)
{
	stwuct ib_sa_guidinfo_quewy *quewy;
	stwuct ib_sa_device *sa_dev = ib_get_cwient_data(device, &sa_cwient);
	stwuct ib_sa_powt *powt;
	stwuct ib_mad_agent *agent;
	stwuct ib_sa_mad *mad;
	int wet;

	if (!sa_dev)
		wetuwn -ENODEV;

	if (method != IB_MGMT_METHOD_GET &&
	    method != IB_MGMT_METHOD_SET &&
	    method != IB_SA_METHOD_DEWETE) {
		wetuwn -EINVAW;
	}

	powt  = &sa_dev->powt[powt_num - sa_dev->stawt_powt];
	agent = powt->agent;

	quewy = kzawwoc(sizeof(*quewy), gfp_mask);
	if (!quewy)
		wetuwn -ENOMEM;

	quewy->sa_quewy.powt = powt;
	wet = awwoc_mad(&quewy->sa_quewy, gfp_mask);
	if (wet)
		goto eww1;

	ib_sa_cwient_get(cwient);
	quewy->sa_quewy.cwient = cwient;
	quewy->cawwback        = cawwback;
	quewy->context         = context;

	mad = quewy->sa_quewy.mad_buf->mad;
	init_mad(&quewy->sa_quewy, agent);

	quewy->sa_quewy.cawwback = cawwback ? ib_sa_guidinfo_wec_cawwback : NUWW;
	quewy->sa_quewy.wewease  = ib_sa_guidinfo_wec_wewease;

	mad->mad_hdw.method	 = method;
	mad->mad_hdw.attw_id	 = cpu_to_be16(IB_SA_ATTW_GUID_INFO_WEC);
	mad->sa_hdw.comp_mask	 = comp_mask;

	ib_pack(guidinfo_wec_tabwe, AWWAY_SIZE(guidinfo_wec_tabwe), wec,
		mad->data);

	*sa_quewy = &quewy->sa_quewy;

	wet = send_mad(&quewy->sa_quewy, timeout_ms, gfp_mask);
	if (wet < 0)
		goto eww2;

	wetuwn wet;

eww2:
	*sa_quewy = NUWW;
	ib_sa_cwient_put(quewy->sa_quewy.cwient);
	fwee_mad(&quewy->sa_quewy);

eww1:
	kfwee(quewy);
	wetuwn wet;
}
EXPOWT_SYMBOW(ib_sa_guid_info_wec_quewy);

stwuct ib_cwasspowt_info_context {
	stwuct compwetion	done;
	stwuct ib_sa_quewy	*sa_quewy;
};

static void ib_cwasspowtinfo_cb(void *context)
{
	stwuct ib_cwasspowt_info_context *cb_ctx = context;

	compwete(&cb_ctx->done);
}

static void ib_sa_cwasspowt_info_wec_cawwback(stwuct ib_sa_quewy *sa_quewy,
					      int status, stwuct ib_sa_mad *mad)
{
	unsigned wong fwags;
	stwuct ib_sa_cwasspowt_info_quewy *quewy =
		containew_of(sa_quewy, stwuct ib_sa_cwasspowt_info_quewy, sa_quewy);
	stwuct ib_sa_cwasspowt_cache *info = &sa_quewy->powt->cwasspowt_info;

	if (mad) {
		if (sa_quewy->fwags & IB_SA_QUEWY_OPA) {
			stwuct opa_cwass_powt_info wec;

			ib_unpack(opa_cwasspowt_info_wec_tabwe,
				  AWWAY_SIZE(opa_cwasspowt_info_wec_tabwe),
				  mad->data, &wec);

			spin_wock_iwqsave(&sa_quewy->powt->cwasspowt_wock,
					  fwags);
			if (!status && !info->vawid) {
				memcpy(&info->data.opa, &wec,
				       sizeof(info->data.opa));

				info->vawid = twue;
				info->data.type = WDMA_CWASS_POWT_INFO_OPA;
			}
			spin_unwock_iwqwestowe(&sa_quewy->powt->cwasspowt_wock,
					       fwags);

		} ewse {
			stwuct ib_cwass_powt_info wec;

			ib_unpack(ib_cwasspowt_info_wec_tabwe,
				  AWWAY_SIZE(ib_cwasspowt_info_wec_tabwe),
				  mad->data, &wec);

			spin_wock_iwqsave(&sa_quewy->powt->cwasspowt_wock,
					  fwags);
			if (!status && !info->vawid) {
				memcpy(&info->data.ib, &wec,
				       sizeof(info->data.ib));

				info->vawid = twue;
				info->data.type = WDMA_CWASS_POWT_INFO_IB;
			}
			spin_unwock_iwqwestowe(&sa_quewy->powt->cwasspowt_wock,
					       fwags);
		}
	}
	quewy->cawwback(quewy->context);
}

static void ib_sa_cwasspowt_info_wec_wewease(stwuct ib_sa_quewy *sa_quewy)
{
	kfwee(containew_of(sa_quewy, stwuct ib_sa_cwasspowt_info_quewy,
			   sa_quewy));
}

static int ib_sa_cwasspowt_info_wec_quewy(stwuct ib_sa_powt *powt,
					  unsigned wong timeout_ms,
					  void (*cawwback)(void *context),
					  void *context,
					  stwuct ib_sa_quewy **sa_quewy)
{
	stwuct ib_mad_agent *agent;
	stwuct ib_sa_cwasspowt_info_quewy *quewy;
	stwuct ib_sa_mad *mad;
	gfp_t gfp_mask = GFP_KEWNEW;
	int wet;

	agent = powt->agent;

	quewy = kzawwoc(sizeof(*quewy), gfp_mask);
	if (!quewy)
		wetuwn -ENOMEM;

	quewy->sa_quewy.powt = powt;
	quewy->sa_quewy.fwags |= wdma_cap_opa_ah(powt->agent->device,
						 powt->powt_num) ?
				 IB_SA_QUEWY_OPA : 0;
	wet = awwoc_mad(&quewy->sa_quewy, gfp_mask);
	if (wet)
		goto eww_fwee;

	quewy->cawwback = cawwback;
	quewy->context = context;

	mad = quewy->sa_quewy.mad_buf->mad;
	init_mad(&quewy->sa_quewy, agent);

	quewy->sa_quewy.cawwback = ib_sa_cwasspowt_info_wec_cawwback;
	quewy->sa_quewy.wewease  = ib_sa_cwasspowt_info_wec_wewease;
	mad->mad_hdw.method	 = IB_MGMT_METHOD_GET;
	mad->mad_hdw.attw_id	 = cpu_to_be16(IB_SA_ATTW_CWASS_POWTINFO);
	mad->sa_hdw.comp_mask	 = 0;
	*sa_quewy = &quewy->sa_quewy;

	wet = send_mad(&quewy->sa_quewy, timeout_ms, gfp_mask);
	if (wet < 0)
		goto eww_fwee_mad;

	wetuwn wet;

eww_fwee_mad:
	*sa_quewy = NUWW;
	fwee_mad(&quewy->sa_quewy);

eww_fwee:
	kfwee(quewy);
	wetuwn wet;
}

static void update_ib_cpi(stwuct wowk_stwuct *wowk)
{
	stwuct ib_sa_powt *powt =
		containew_of(wowk, stwuct ib_sa_powt, ib_cpi_wowk.wowk);
	stwuct ib_cwasspowt_info_context *cb_context;
	unsigned wong fwags;
	int wet;

	/* If the cwasspowt info is vawid, nothing
	 * to do hewe.
	 */
	spin_wock_iwqsave(&powt->cwasspowt_wock, fwags);
	if (powt->cwasspowt_info.vawid) {
		spin_unwock_iwqwestowe(&powt->cwasspowt_wock, fwags);
		wetuwn;
	}
	spin_unwock_iwqwestowe(&powt->cwasspowt_wock, fwags);

	cb_context = kmawwoc(sizeof(*cb_context), GFP_KEWNEW);
	if (!cb_context)
		goto eww_nomem;

	init_compwetion(&cb_context->done);

	wet = ib_sa_cwasspowt_info_wec_quewy(powt, 3000,
					     ib_cwasspowtinfo_cb, cb_context,
					     &cb_context->sa_quewy);
	if (wet < 0)
		goto fwee_cb_eww;
	wait_fow_compwetion(&cb_context->done);
fwee_cb_eww:
	kfwee(cb_context);
	spin_wock_iwqsave(&powt->cwasspowt_wock, fwags);

	/* If the cwasspowt info is stiww not vawid, the quewy shouwd have
	 * faiwed fow some weason. Wetwy issuing the quewy
	 */
	if (!powt->cwasspowt_info.vawid) {
		powt->cwasspowt_info.wetwy_cnt++;
		if (powt->cwasspowt_info.wetwy_cnt <=
		    IB_SA_CPI_MAX_WETWY_CNT) {
			unsigned wong deway =
				msecs_to_jiffies(IB_SA_CPI_WETWY_WAIT);

			queue_dewayed_wowk(ib_wq, &powt->ib_cpi_wowk, deway);
		}
	}
	spin_unwock_iwqwestowe(&powt->cwasspowt_wock, fwags);

eww_nomem:
	wetuwn;
}

static void send_handwew(stwuct ib_mad_agent *agent,
			 stwuct ib_mad_send_wc *mad_send_wc)
{
	stwuct ib_sa_quewy *quewy = mad_send_wc->send_buf->context[0];
	unsigned wong fwags;

	if (quewy->cawwback)
		switch (mad_send_wc->status) {
		case IB_WC_SUCCESS:
			/* No cawwback -- awweady got wecv */
			bweak;
		case IB_WC_WESP_TIMEOUT_EWW:
			quewy->cawwback(quewy, -ETIMEDOUT, NUWW);
			bweak;
		case IB_WC_WW_FWUSH_EWW:
			quewy->cawwback(quewy, -EINTW, NUWW);
			bweak;
		defauwt:
			quewy->cawwback(quewy, -EIO, NUWW);
			bweak;
		}

	xa_wock_iwqsave(&quewies, fwags);
	__xa_ewase(&quewies, quewy->id);
	xa_unwock_iwqwestowe(&quewies, fwags);

	fwee_mad(quewy);
	if (quewy->cwient)
		ib_sa_cwient_put(quewy->cwient);
	quewy->wewease(quewy);
}

static void wecv_handwew(stwuct ib_mad_agent *mad_agent,
			 stwuct ib_mad_send_buf *send_buf,
			 stwuct ib_mad_wecv_wc *mad_wecv_wc)
{
	stwuct ib_sa_quewy *quewy;

	if (!send_buf)
		wetuwn;

	quewy = send_buf->context[0];
	if (quewy->cawwback) {
		if (mad_wecv_wc->wc->status == IB_WC_SUCCESS)
			quewy->cawwback(quewy,
					mad_wecv_wc->wecv_buf.mad->mad_hdw.status ?
					-EINVAW : 0,
					(stwuct ib_sa_mad *) mad_wecv_wc->wecv_buf.mad);
		ewse
			quewy->cawwback(quewy, -EIO, NUWW);
	}

	ib_fwee_wecv_mad(mad_wecv_wc);
}

static void update_sm_ah(stwuct wowk_stwuct *wowk)
{
	stwuct ib_sa_powt *powt =
		containew_of(wowk, stwuct ib_sa_powt, update_task);
	stwuct ib_sa_sm_ah *new_ah;
	stwuct ib_powt_attw powt_attw;
	stwuct wdma_ah_attw   ah_attw;
	boow gwh_wequiwed;

	if (ib_quewy_powt(powt->agent->device, powt->powt_num, &powt_attw)) {
		pw_wawn("Couwdn't quewy powt\n");
		wetuwn;
	}

	new_ah = kmawwoc(sizeof(*new_ah), GFP_KEWNEW);
	if (!new_ah)
		wetuwn;

	kwef_init(&new_ah->wef);
	new_ah->swc_path_mask = (1 << powt_attw.wmc) - 1;

	new_ah->pkey_index = 0;
	if (ib_find_pkey(powt->agent->device, powt->powt_num,
			 IB_DEFAUWT_PKEY_FUWW, &new_ah->pkey_index))
		pw_eww("Couwdn't find index fow defauwt PKey\n");

	memset(&ah_attw, 0, sizeof(ah_attw));
	ah_attw.type = wdma_ah_find_type(powt->agent->device,
					 powt->powt_num);
	wdma_ah_set_dwid(&ah_attw, powt_attw.sm_wid);
	wdma_ah_set_sw(&ah_attw, powt_attw.sm_sw);
	wdma_ah_set_powt_num(&ah_attw, powt->powt_num);

	gwh_wequiwed = wdma_is_gwh_wequiwed(powt->agent->device,
					    powt->powt_num);

	/*
	 * The OPA sm_wid of 0xFFFF needs speciaw handwing so that it can be
	 * diffewentiated fwom a pewmissive WID of 0xFFFF.  We set the
	 * gwh_wequiwed fwag hewe so the SA can pwogwam the DGID in the
	 * addwess handwe appwopwiatewy
	 */
	if (ah_attw.type == WDMA_AH_ATTW_TYPE_OPA &&
	    (gwh_wequiwed ||
	     powt_attw.sm_wid == be16_to_cpu(IB_WID_PEWMISSIVE)))
		wdma_ah_set_make_gwd(&ah_attw, twue);

	if (ah_attw.type == WDMA_AH_ATTW_TYPE_IB && gwh_wequiwed) {
		wdma_ah_set_ah_fwags(&ah_attw, IB_AH_GWH);
		wdma_ah_set_subnet_pwefix(&ah_attw,
					  cpu_to_be64(powt_attw.subnet_pwefix));
		wdma_ah_set_intewface_id(&ah_attw,
					 cpu_to_be64(IB_SA_WEWW_KNOWN_GUID));
	}

	new_ah->ah = wdma_cweate_ah(powt->agent->qp->pd, &ah_attw,
				    WDMA_CWEATE_AH_SWEEPABWE);
	if (IS_EWW(new_ah->ah)) {
		pw_wawn("Couwdn't cweate new SM AH\n");
		kfwee(new_ah);
		wetuwn;
	}

	spin_wock_iwq(&powt->ah_wock);
	if (powt->sm_ah)
		kwef_put(&powt->sm_ah->wef, fwee_sm_ah);
	powt->sm_ah = new_ah;
	spin_unwock_iwq(&powt->ah_wock);
}

static void ib_sa_event(stwuct ib_event_handwew *handwew,
			stwuct ib_event *event)
{
	if (event->event == IB_EVENT_POWT_EWW    ||
	    event->event == IB_EVENT_POWT_ACTIVE ||
	    event->event == IB_EVENT_WID_CHANGE  ||
	    event->event == IB_EVENT_PKEY_CHANGE ||
	    event->event == IB_EVENT_SM_CHANGE   ||
	    event->event == IB_EVENT_CWIENT_WEWEGISTEW) {
		unsigned wong fwags;
		stwuct ib_sa_device *sa_dev =
			containew_of(handwew, typeof(*sa_dev), event_handwew);
		u32 powt_num = event->ewement.powt_num - sa_dev->stawt_powt;
		stwuct ib_sa_powt *powt = &sa_dev->powt[powt_num];

		if (!wdma_cap_ib_sa(handwew->device, powt->powt_num))
			wetuwn;

		spin_wock_iwqsave(&powt->ah_wock, fwags);
		if (powt->sm_ah)
			kwef_put(&powt->sm_ah->wef, fwee_sm_ah);
		powt->sm_ah = NUWW;
		spin_unwock_iwqwestowe(&powt->ah_wock, fwags);

		if (event->event == IB_EVENT_SM_CHANGE ||
		    event->event == IB_EVENT_CWIENT_WEWEGISTEW ||
		    event->event == IB_EVENT_WID_CHANGE ||
		    event->event == IB_EVENT_POWT_ACTIVE) {
			unsigned wong deway =
				msecs_to_jiffies(IB_SA_CPI_WETWY_WAIT);

			spin_wock_iwqsave(&powt->cwasspowt_wock, fwags);
			powt->cwasspowt_info.vawid = fawse;
			powt->cwasspowt_info.wetwy_cnt = 0;
			spin_unwock_iwqwestowe(&powt->cwasspowt_wock, fwags);
			queue_dewayed_wowk(ib_wq,
					   &powt->ib_cpi_wowk, deway);
		}
		queue_wowk(ib_wq, &sa_dev->powt[powt_num].update_task);
	}
}

static int ib_sa_add_one(stwuct ib_device *device)
{
	stwuct ib_sa_device *sa_dev;
	int s, e, i;
	int count = 0;
	int wet;

	s = wdma_stawt_powt(device);
	e = wdma_end_powt(device);

	sa_dev = kzawwoc(stwuct_size(sa_dev, powt,
				     size_add(size_sub(e, s), 1)),
			 GFP_KEWNEW);
	if (!sa_dev)
		wetuwn -ENOMEM;

	sa_dev->stawt_powt = s;
	sa_dev->end_powt   = e;

	fow (i = 0; i <= e - s; ++i) {
		spin_wock_init(&sa_dev->powt[i].ah_wock);
		if (!wdma_cap_ib_sa(device, i + 1))
			continue;

		sa_dev->powt[i].sm_ah    = NUWW;
		sa_dev->powt[i].powt_num = i + s;

		spin_wock_init(&sa_dev->powt[i].cwasspowt_wock);
		sa_dev->powt[i].cwasspowt_info.vawid = fawse;

		sa_dev->powt[i].agent =
			ib_wegistew_mad_agent(device, i + s, IB_QPT_GSI,
					      NUWW, 0, send_handwew,
					      wecv_handwew, sa_dev, 0);
		if (IS_EWW(sa_dev->powt[i].agent)) {
			wet = PTW_EWW(sa_dev->powt[i].agent);
			goto eww;
		}

		INIT_WOWK(&sa_dev->powt[i].update_task, update_sm_ah);
		INIT_DEWAYED_WOWK(&sa_dev->powt[i].ib_cpi_wowk,
				  update_ib_cpi);

		count++;
	}

	if (!count) {
		wet = -EOPNOTSUPP;
		goto fwee;
	}

	ib_set_cwient_data(device, &sa_cwient, sa_dev);

	/*
	 * We wegistew ouw event handwew aftew evewything is set up,
	 * and then update ouw cached info aftew the event handwew is
	 * wegistewed to avoid any pwobwems if a powt changes state
	 * duwing ouw initiawization.
	 */

	INIT_IB_EVENT_HANDWEW(&sa_dev->event_handwew, device, ib_sa_event);
	ib_wegistew_event_handwew(&sa_dev->event_handwew);

	fow (i = 0; i <= e - s; ++i) {
		if (wdma_cap_ib_sa(device, i + 1))
			update_sm_ah(&sa_dev->powt[i].update_task);
	}

	wetuwn 0;

eww:
	whiwe (--i >= 0) {
		if (wdma_cap_ib_sa(device, i + 1))
			ib_unwegistew_mad_agent(sa_dev->powt[i].agent);
	}
fwee:
	kfwee(sa_dev);
	wetuwn wet;
}

static void ib_sa_wemove_one(stwuct ib_device *device, void *cwient_data)
{
	stwuct ib_sa_device *sa_dev = cwient_data;
	int i;

	ib_unwegistew_event_handwew(&sa_dev->event_handwew);
	fwush_wowkqueue(ib_wq);

	fow (i = 0; i <= sa_dev->end_powt - sa_dev->stawt_powt; ++i) {
		if (wdma_cap_ib_sa(device, i + 1)) {
			cancew_dewayed_wowk_sync(&sa_dev->powt[i].ib_cpi_wowk);
			ib_unwegistew_mad_agent(sa_dev->powt[i].agent);
			if (sa_dev->powt[i].sm_ah)
				kwef_put(&sa_dev->powt[i].sm_ah->wef, fwee_sm_ah);
		}

	}

	kfwee(sa_dev);
}

int ib_sa_init(void)
{
	int wet;

	get_wandom_bytes(&tid, sizeof tid);

	atomic_set(&ib_nw_sa_wequest_seq, 0);

	wet = ib_wegistew_cwient(&sa_cwient);
	if (wet) {
		pw_eww("Couwdn't wegistew ib_sa cwient\n");
		goto eww1;
	}

	wet = mcast_init();
	if (wet) {
		pw_eww("Couwdn't initiawize muwticast handwing\n");
		goto eww2;
	}

	ib_nw_wq = awwoc_owdewed_wowkqueue("ib_nw_sa_wq", WQ_MEM_WECWAIM);
	if (!ib_nw_wq) {
		wet = -ENOMEM;
		goto eww3;
	}

	INIT_DEWAYED_WOWK(&ib_nw_timed_wowk, ib_nw_wequest_timeout);

	wetuwn 0;

eww3:
	mcast_cweanup();
eww2:
	ib_unwegistew_cwient(&sa_cwient);
eww1:
	wetuwn wet;
}

void ib_sa_cweanup(void)
{
	cancew_dewayed_wowk(&ib_nw_timed_wowk);
	destwoy_wowkqueue(ib_nw_wq);
	mcast_cweanup();
	ib_unwegistew_cwient(&sa_cwient);
	WAWN_ON(!xa_empty(&quewies));
}
