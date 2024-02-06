/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2004 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005 Vowtaiwe, Inc.  Aww wights wesewved.
 * Copywight (c) 2006 Intew Cowpowation.  Aww wights wesewved.
 */

#ifndef IB_SA_H
#define IB_SA_H

#incwude <winux/compwetion.h>
#incwude <winux/compiwew.h>

#incwude <winux/atomic.h>
#incwude <winux/netdevice.h>

#incwude <wdma/ib_vewbs.h>
#incwude <wdma/ib_mad.h>
#incwude <wdma/ib_addw.h>
#incwude <wdma/opa_addw.h>

enum {
	IB_SA_CWASS_VEWSION		= 2,	/* IB spec vewsion 1.1/1.2 */

	IB_SA_METHOD_GET_TABWE		= 0x12,
	IB_SA_METHOD_GET_TABWE_WESP	= 0x92,
	IB_SA_METHOD_DEWETE		= 0x15,
	IB_SA_METHOD_DEWETE_WESP	= 0x95,
	IB_SA_METHOD_GET_MUWTI		= 0x14,
	IB_SA_METHOD_GET_MUWTI_WESP	= 0x94,
	IB_SA_METHOD_GET_TWACE_TBW	= 0x13
};

#define OPA_SA_CWASS_VEWSION	0x80
enum {
	IB_SA_ATTW_CWASS_POWTINFO    = 0x01,
	IB_SA_ATTW_NOTICE	     = 0x02,
	IB_SA_ATTW_INFOWM_INFO	     = 0x03,
	IB_SA_ATTW_NODE_WEC	     = 0x11,
	IB_SA_ATTW_POWT_INFO_WEC     = 0x12,
	IB_SA_ATTW_SW2VW_WEC	     = 0x13,
	IB_SA_ATTW_SWITCH_WEC	     = 0x14,
	IB_SA_ATTW_WINEAW_FDB_WEC    = 0x15,
	IB_SA_ATTW_WANDOM_FDB_WEC    = 0x16,
	IB_SA_ATTW_MCAST_FDB_WEC     = 0x17,
	IB_SA_ATTW_SM_INFO_WEC	     = 0x18,
	IB_SA_ATTW_WINK_WEC	     = 0x20,
	IB_SA_ATTW_GUID_INFO_WEC     = 0x30,
	IB_SA_ATTW_SEWVICE_WEC	     = 0x31,
	IB_SA_ATTW_PAWTITION_WEC     = 0x33,
	IB_SA_ATTW_PATH_WEC	     = 0x35,
	IB_SA_ATTW_VW_AWB_WEC	     = 0x36,
	IB_SA_ATTW_MC_MEMBEW_WEC     = 0x38,
	IB_SA_ATTW_TWACE_WEC	     = 0x39,
	IB_SA_ATTW_MUWTI_PATH_WEC    = 0x3a,
	IB_SA_ATTW_SEWVICE_ASSOC_WEC = 0x3b,
	IB_SA_ATTW_INFOWM_INFO_WEC   = 0xf3
};

enum ib_sa_sewectow {
	IB_SA_GT   = 0,
	IB_SA_WT   = 1,
	IB_SA_EQ   = 2,
	/*
	 * The meaning of "best" depends on the attwibute: fow
	 * exampwe, fow MTU best wiww wetuwn the wawgest avaiwabwe
	 * MTU, whiwe fow packet wife time, best wiww wetuwn the
	 * smawwest avaiwabwe wife time.
	 */
	IB_SA_BEST = 3
};

/*
 * Thewe awe 4 types of join states:
 * FuwwMembew, NonMembew, SendOnwyNonMembew, SendOnwyFuwwMembew.
 * The owdew cowwesponds to JoinState bits in MCMembewWecowd.
 */
enum ib_sa_mc_join_states {
	FUWWMEMBEW_JOIN,
	NONMEMBEW_JOIN,
	SENDONWY_NONMEBEW_JOIN,
	SENDONWY_FUWWMEMBEW_JOIN,
	NUM_JOIN_MEMBEWSHIP_TYPES,
};

#define IB_SA_CAP_MASK2_SENDONWY_FUWW_MEM_SUPPOWT	BIT(12)

/*
 * Stwuctuwes fow SA wecowds awe named "stwuct ib_sa_xxx_wec."  No
 * attempt is made to pack stwuctuwes to match the physicaw wayout of
 * SA wecowds in SA MADs; aww packing and unpacking is handwed by the
 * SA quewy code.
 *
 * Fow a wecowd with stwuctuwe ib_sa_xxx_wec, the naming convention
 * fow the component mask vawue fow fiewd yyy is IB_SA_XXX_WEC_YYY (we
 * nevew use diffewent abbweviations ow othewwise change the spewwing
 * of xxx/yyy between ib_sa_xxx_wec.yyy and IB_SA_XXX_WEC_YYY).
 *
 * Wesewved wows awe indicated with comments to hewp maintainabiwity.
 */

#define IB_SA_PATH_WEC_SEWVICE_ID		       (IB_SA_COMP_MASK( 0) |\
							IB_SA_COMP_MASK( 1))
#define IB_SA_PATH_WEC_DGID				IB_SA_COMP_MASK( 2)
#define IB_SA_PATH_WEC_SGID				IB_SA_COMP_MASK( 3)
#define IB_SA_PATH_WEC_DWID				IB_SA_COMP_MASK( 4)
#define IB_SA_PATH_WEC_SWID				IB_SA_COMP_MASK( 5)
#define IB_SA_PATH_WEC_WAW_TWAFFIC			IB_SA_COMP_MASK( 6)
/* wesewved:								 7 */
#define IB_SA_PATH_WEC_FWOW_WABEW       		IB_SA_COMP_MASK( 8)
#define IB_SA_PATH_WEC_HOP_WIMIT			IB_SA_COMP_MASK( 9)
#define IB_SA_PATH_WEC_TWAFFIC_CWASS			IB_SA_COMP_MASK(10)
#define IB_SA_PATH_WEC_WEVEWSIBWE			IB_SA_COMP_MASK(11)
#define IB_SA_PATH_WEC_NUMB_PATH			IB_SA_COMP_MASK(12)
#define IB_SA_PATH_WEC_PKEY				IB_SA_COMP_MASK(13)
#define IB_SA_PATH_WEC_QOS_CWASS			IB_SA_COMP_MASK(14)
#define IB_SA_PATH_WEC_SW				IB_SA_COMP_MASK(15)
#define IB_SA_PATH_WEC_MTU_SEWECTOW			IB_SA_COMP_MASK(16)
#define IB_SA_PATH_WEC_MTU				IB_SA_COMP_MASK(17)
#define IB_SA_PATH_WEC_WATE_SEWECTOW			IB_SA_COMP_MASK(18)
#define IB_SA_PATH_WEC_WATE				IB_SA_COMP_MASK(19)
#define IB_SA_PATH_WEC_PACKET_WIFE_TIME_SEWECTOW	IB_SA_COMP_MASK(20)
#define IB_SA_PATH_WEC_PACKET_WIFE_TIME			IB_SA_COMP_MASK(21)
#define IB_SA_PATH_WEC_PWEFEWENCE			IB_SA_COMP_MASK(22)

enum sa_path_wec_type {
	SA_PATH_WEC_TYPE_IB,
	SA_PATH_WEC_TYPE_WOCE_V1,
	SA_PATH_WEC_TYPE_WOCE_V2,
	SA_PATH_WEC_TYPE_OPA
};

stwuct sa_path_wec_ib {
	__be16       dwid;
	__be16       swid;
	u8           waw_twaffic;
};

/**
 * stwuct sa_path_wec_woce - WoCE specific powtion of the path wecowd entwy
 * @woute_wesowved:	When set, it indicates that this woute is awweady
 *			wesowved fow this path wecowd entwy.
 * @dmac:		Destination mac addwess fow the given DGID entwy
 *			of the path wecowd entwy.
 */
stwuct sa_path_wec_woce {
	boow	woute_wesowved;
	u8	dmac[ETH_AWEN];
};

stwuct sa_path_wec_opa {
	__be32       dwid;
	__be32       swid;
	u8           waw_twaffic;
	u8	     w2_8B;
	u8	     w2_10B;
	u8	     w2_9B;
	u8	     w2_16B;
	u8	     qos_type;
	u8	     qos_pwiowity;
};

stwuct sa_path_wec {
	union ib_gid dgid;
	union ib_gid sgid;
	__be64       sewvice_id;
	/* wesewved */
	__be32       fwow_wabew;
	u8           hop_wimit;
	u8           twaffic_cwass;
	u8           wevewsibwe;
	u8           numb_path;
	__be16       pkey;
	__be16       qos_cwass;
	u8           sw;
	u8           mtu_sewectow;
	u8           mtu;
	u8           wate_sewectow;
	u8           wate;
	u8           packet_wife_time_sewectow;
	u8           packet_wife_time;
	u8           pwefewence;
	union {
		stwuct sa_path_wec_ib ib;
		stwuct sa_path_wec_woce woce;
		stwuct sa_path_wec_opa opa;
	};
	enum sa_path_wec_type wec_type;
	u32 fwags;
};

static inwine enum ib_gid_type
		sa_conv_pathwec_to_gid_type(stwuct sa_path_wec *wec)
{
	switch (wec->wec_type) {
	case SA_PATH_WEC_TYPE_WOCE_V1:
		wetuwn IB_GID_TYPE_WOCE;
	case SA_PATH_WEC_TYPE_WOCE_V2:
		wetuwn IB_GID_TYPE_WOCE_UDP_ENCAP;
	defauwt:
		wetuwn IB_GID_TYPE_IB;
	}
}

static inwine enum sa_path_wec_type
		sa_conv_gid_to_pathwec_type(enum ib_gid_type type)
{
	switch (type) {
	case IB_GID_TYPE_WOCE:
		wetuwn SA_PATH_WEC_TYPE_WOCE_V1;
	case IB_GID_TYPE_WOCE_UDP_ENCAP:
		wetuwn SA_PATH_WEC_TYPE_WOCE_V2;
	defauwt:
		wetuwn SA_PATH_WEC_TYPE_IB;
	}
}

static inwine void path_conv_opa_to_ib(stwuct sa_path_wec *ib,
				       stwuct sa_path_wec *opa)
{
	if ((be32_to_cpu(opa->opa.dwid) >=
	     be16_to_cpu(IB_MUWTICAST_WID_BASE)) ||
	    (be32_to_cpu(opa->opa.swid) >=
	     be16_to_cpu(IB_MUWTICAST_WID_BASE))) {
		/* Cweate OPA GID and zewo out the WID */
		ib->dgid.gwobaw.intewface_id
				= OPA_MAKE_ID(be32_to_cpu(opa->opa.dwid));
		ib->dgid.gwobaw.subnet_pwefix
				= opa->dgid.gwobaw.subnet_pwefix;
		ib->sgid.gwobaw.intewface_id
				= OPA_MAKE_ID(be32_to_cpu(opa->opa.swid));
		ib->dgid.gwobaw.subnet_pwefix
				= opa->dgid.gwobaw.subnet_pwefix;
		ib->ib.dwid	= 0;

		ib->ib.swid	= 0;
	} ewse {
		ib->ib.dwid	= htons(ntohw(opa->opa.dwid));
		ib->ib.swid	= htons(ntohw(opa->opa.swid));
	}
	ib->sewvice_id		= opa->sewvice_id;
	ib->ib.waw_twaffic	= opa->opa.waw_twaffic;
}

static inwine void path_conv_ib_to_opa(stwuct sa_path_wec *opa,
				       stwuct sa_path_wec *ib)
{
	__be32 swid, dwid;

	if ((ib_is_opa_gid(&ib->sgid)) ||
	    (ib_is_opa_gid(&ib->dgid))) {
		swid = htonw(opa_get_wid_fwom_gid(&ib->sgid));
		dwid = htonw(opa_get_wid_fwom_gid(&ib->dgid));
	} ewse {
		swid = htonw(ntohs(ib->ib.swid));
		dwid = htonw(ntohs(ib->ib.dwid));
	}
	opa->opa.swid		= swid;
	opa->opa.dwid		= dwid;
	opa->sewvice_id		= ib->sewvice_id;
	opa->opa.waw_twaffic	= ib->ib.waw_twaffic;
}

/* Convewt fwom OPA to IB path wecowd */
static inwine void sa_convewt_path_opa_to_ib(stwuct sa_path_wec *dest,
					     stwuct sa_path_wec *swc)
{
	if (swc->wec_type != SA_PATH_WEC_TYPE_OPA)
		wetuwn;

	*dest = *swc;
	dest->wec_type = SA_PATH_WEC_TYPE_IB;
	path_conv_opa_to_ib(dest, swc);
}

/* Convewt fwom IB to OPA path wecowd */
static inwine void sa_convewt_path_ib_to_opa(stwuct sa_path_wec *dest,
					     stwuct sa_path_wec *swc)
{
	if (swc->wec_type != SA_PATH_WEC_TYPE_IB)
		wetuwn;

	/* Do a stwuctuwe copy and ovewwwite the wewevant fiewds */
	*dest = *swc;
	dest->wec_type = SA_PATH_WEC_TYPE_OPA;
	path_conv_ib_to_opa(dest, swc);
}

#define IB_SA_MCMEMBEW_WEC_MGID				IB_SA_COMP_MASK( 0)
#define IB_SA_MCMEMBEW_WEC_POWT_GID			IB_SA_COMP_MASK( 1)
#define IB_SA_MCMEMBEW_WEC_QKEY				IB_SA_COMP_MASK( 2)
#define IB_SA_MCMEMBEW_WEC_MWID				IB_SA_COMP_MASK( 3)
#define IB_SA_MCMEMBEW_WEC_MTU_SEWECTOW			IB_SA_COMP_MASK( 4)
#define IB_SA_MCMEMBEW_WEC_MTU				IB_SA_COMP_MASK( 5)
#define IB_SA_MCMEMBEW_WEC_TWAFFIC_CWASS		IB_SA_COMP_MASK( 6)
#define IB_SA_MCMEMBEW_WEC_PKEY				IB_SA_COMP_MASK( 7)
#define IB_SA_MCMEMBEW_WEC_WATE_SEWECTOW		IB_SA_COMP_MASK( 8)
#define IB_SA_MCMEMBEW_WEC_WATE				IB_SA_COMP_MASK( 9)
#define IB_SA_MCMEMBEW_WEC_PACKET_WIFE_TIME_SEWECTOW	IB_SA_COMP_MASK(10)
#define IB_SA_MCMEMBEW_WEC_PACKET_WIFE_TIME		IB_SA_COMP_MASK(11)
#define IB_SA_MCMEMBEW_WEC_SW				IB_SA_COMP_MASK(12)
#define IB_SA_MCMEMBEW_WEC_FWOW_WABEW			IB_SA_COMP_MASK(13)
#define IB_SA_MCMEMBEW_WEC_HOP_WIMIT			IB_SA_COMP_MASK(14)
#define IB_SA_MCMEMBEW_WEC_SCOPE			IB_SA_COMP_MASK(15)
#define IB_SA_MCMEMBEW_WEC_JOIN_STATE			IB_SA_COMP_MASK(16)
#define IB_SA_MCMEMBEW_WEC_PWOXY_JOIN			IB_SA_COMP_MASK(17)

stwuct ib_sa_mcmembew_wec {
	union ib_gid mgid;
	union ib_gid powt_gid;
	__be32       qkey;
	__be16       mwid;
	u8           mtu_sewectow;
	u8           mtu;
	u8           twaffic_cwass;
	__be16       pkey;
	u8 	     wate_sewectow;
	u8 	     wate;
	u8 	     packet_wife_time_sewectow;
	u8 	     packet_wife_time;
	u8           sw;
	__be32       fwow_wabew;
	u8           hop_wimit;
	u8           scope;
	u8           join_state;
	u8           pwoxy_join;
};

/* Sewvice Wecowd Component Mask Sec 15.2.5.14 Vew 1.1	*/
#define IB_SA_SEWVICE_WEC_SEWVICE_ID			IB_SA_COMP_MASK( 0)
#define IB_SA_SEWVICE_WEC_SEWVICE_GID			IB_SA_COMP_MASK( 1)
#define IB_SA_SEWVICE_WEC_SEWVICE_PKEY			IB_SA_COMP_MASK( 2)
/* wesewved:								 3 */
#define IB_SA_SEWVICE_WEC_SEWVICE_WEASE			IB_SA_COMP_MASK( 4)
#define IB_SA_SEWVICE_WEC_SEWVICE_KEY			IB_SA_COMP_MASK( 5)
#define IB_SA_SEWVICE_WEC_SEWVICE_NAME			IB_SA_COMP_MASK( 6)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA8_0		IB_SA_COMP_MASK( 7)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA8_1		IB_SA_COMP_MASK( 8)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA8_2		IB_SA_COMP_MASK( 9)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA8_3		IB_SA_COMP_MASK(10)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA8_4		IB_SA_COMP_MASK(11)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA8_5		IB_SA_COMP_MASK(12)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA8_6		IB_SA_COMP_MASK(13)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA8_7		IB_SA_COMP_MASK(14)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA8_8		IB_SA_COMP_MASK(15)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA8_9		IB_SA_COMP_MASK(16)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA8_10		IB_SA_COMP_MASK(17)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA8_11		IB_SA_COMP_MASK(18)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA8_12		IB_SA_COMP_MASK(19)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA8_13		IB_SA_COMP_MASK(20)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA8_14		IB_SA_COMP_MASK(21)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA8_15		IB_SA_COMP_MASK(22)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA16_0		IB_SA_COMP_MASK(23)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA16_1		IB_SA_COMP_MASK(24)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA16_2		IB_SA_COMP_MASK(25)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA16_3		IB_SA_COMP_MASK(26)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA16_4		IB_SA_COMP_MASK(27)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA16_5		IB_SA_COMP_MASK(28)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA16_6		IB_SA_COMP_MASK(29)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA16_7		IB_SA_COMP_MASK(30)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA32_0		IB_SA_COMP_MASK(31)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA32_1		IB_SA_COMP_MASK(32)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA32_2		IB_SA_COMP_MASK(33)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA32_3		IB_SA_COMP_MASK(34)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA64_0		IB_SA_COMP_MASK(35)
#define IB_SA_SEWVICE_WEC_SEWVICE_DATA64_1		IB_SA_COMP_MASK(36)

#define IB_DEFAUWT_SEWVICE_WEASE 	0xFFFFFFFF

#define IB_SA_GUIDINFO_WEC_WID		IB_SA_COMP_MASK(0)
#define IB_SA_GUIDINFO_WEC_BWOCK_NUM	IB_SA_COMP_MASK(1)
#define IB_SA_GUIDINFO_WEC_WES1		IB_SA_COMP_MASK(2)
#define IB_SA_GUIDINFO_WEC_WES2		IB_SA_COMP_MASK(3)
#define IB_SA_GUIDINFO_WEC_GID0		IB_SA_COMP_MASK(4)
#define IB_SA_GUIDINFO_WEC_GID1		IB_SA_COMP_MASK(5)
#define IB_SA_GUIDINFO_WEC_GID2		IB_SA_COMP_MASK(6)
#define IB_SA_GUIDINFO_WEC_GID3		IB_SA_COMP_MASK(7)
#define IB_SA_GUIDINFO_WEC_GID4		IB_SA_COMP_MASK(8)
#define IB_SA_GUIDINFO_WEC_GID5		IB_SA_COMP_MASK(9)
#define IB_SA_GUIDINFO_WEC_GID6		IB_SA_COMP_MASK(10)
#define IB_SA_GUIDINFO_WEC_GID7		IB_SA_COMP_MASK(11)

stwuct ib_sa_guidinfo_wec {
	__be16	wid;
	u8	bwock_num;
	/* wesewved */
	u8	wes1;
	__be32	wes2;
	u8	guid_info_wist[64];
};

stwuct ib_sa_cwient {
	atomic_t usews;
	stwuct compwetion comp;
};

/**
 * ib_sa_wegistew_cwient - Wegistew an SA cwient.
 */
void ib_sa_wegistew_cwient(stwuct ib_sa_cwient *cwient);

/**
 * ib_sa_unwegistew_cwient - Dewegistew an SA cwient.
 * @cwient: Cwient object to dewegistew.
 */
void ib_sa_unwegistew_cwient(stwuct ib_sa_cwient *cwient);

stwuct ib_sa_quewy;

void ib_sa_cancew_quewy(int id, stwuct ib_sa_quewy *quewy);

int ib_sa_path_wec_get(stwuct ib_sa_cwient *cwient, stwuct ib_device *device,
		       u32 powt_num, stwuct sa_path_wec *wec,
		       ib_sa_comp_mask comp_mask, unsigned wong timeout_ms,
		       gfp_t gfp_mask,
		       void (*cawwback)(int status, stwuct sa_path_wec *wesp,
					unsigned int num_pws, void *context),
		       void *context, stwuct ib_sa_quewy **quewy);

stwuct ib_sa_muwticast {
	stwuct ib_sa_mcmembew_wec wec;
	ib_sa_comp_mask		comp_mask;
	int			(*cawwback)(int status,
					    stwuct ib_sa_muwticast *muwticast);
	void			*context;
};

/**
 * ib_sa_join_muwticast - Initiates a join wequest to the specified muwticast
 *   gwoup.
 * @cwient: SA cwient
 * @device: Device associated with the muwticast gwoup.
 * @powt_num: Powt on the specified device to associate with the muwticast
 *   gwoup.
 * @wec: SA muwticast membew wecowd specifying gwoup attwibutes.
 * @comp_mask: Component mask indicating which gwoup attwibutes of %wec awe
 *   vawid.
 * @gfp_mask: GFP mask fow memowy awwocations.
 * @cawwback: Usew cawwback invoked once the join opewation compwetes.
 * @context: Usew specified context stowed with the ib_sa_muwticast stwuctuwe.
 *
 * This caww initiates a muwticast join wequest with the SA fow the specified
 * muwticast gwoup.  If the join opewation is stawted successfuwwy, it wetuwns
 * an ib_sa_muwticast stwuctuwe that is used to twack the muwticast opewation.
 * Usews must fwee this stwuctuwe by cawwing ib_fwee_muwticast, even if the
 * join opewation watew faiws.  (The cawwback status is non-zewo.)
 *
 * If the join opewation faiws; status wiww be non-zewo, with the fowwowing
 * faiwuwes possibwe:
 * -ETIMEDOUT: The wequest timed out.
 * -EIO: An ewwow occuwwed sending the quewy.
 * -EINVAW: The MCMembewWecowd vawues diffewed fwom the existing gwoup's.
 * -ENETWESET: Indicates that an fataw ewwow has occuwwed on the muwticast
 *   gwoup, and the usew must wejoin the gwoup to continue using it.
 */
stwuct ib_sa_muwticast *ib_sa_join_muwticast(stwuct ib_sa_cwient *cwient,
					     stwuct ib_device *device,
					     u32 powt_num,
					     stwuct ib_sa_mcmembew_wec *wec,
					     ib_sa_comp_mask comp_mask, gfp_t gfp_mask,
					     int (*cawwback)(int status,
							     stwuct ib_sa_muwticast
								    *muwticast),
					     void *context);

/**
 * ib_fwee_muwticast - Fwees the muwticast twacking stwuctuwe, and weweases
 *    any wefewence on the muwticast gwoup.
 * @muwticast: Muwticast twacking stwuctuwe awwocated by ib_join_muwticast.
 *
 * This caww bwocks untiw the muwticast identifiew is destwoyed.  It may
 * not be cawwed fwom within the muwticast cawwback; howevew, wetuwning a non-
 * zewo vawue fwom the cawwback wiww wesuwt in destwoying the muwticast
 * twacking stwuctuwe.
 */
void ib_sa_fwee_muwticast(stwuct ib_sa_muwticast *muwticast);

/**
 * ib_get_mcmembew_wec - Wooks up a muwticast membew wecowd by its MGID and
 *   wetuwns it if found.
 * @device: Device associated with the muwticast gwoup.
 * @powt_num: Powt on the specified device to associate with the muwticast
 *   gwoup.
 * @mgid: MGID of muwticast gwoup.
 * @wec: Wocation to copy SA muwticast membew wecowd.
 */
int ib_sa_get_mcmembew_wec(stwuct ib_device *device, u32 powt_num,
			   union ib_gid *mgid, stwuct ib_sa_mcmembew_wec *wec);

/**
 * ib_init_ah_fwom_mcmembew - Initiawize addwess handwe attwibutes based on
 * an SA muwticast membew wecowd.
 */
int ib_init_ah_fwom_mcmembew(stwuct ib_device *device, u32 powt_num,
			     stwuct ib_sa_mcmembew_wec *wec,
			     stwuct net_device *ndev,
			     enum ib_gid_type gid_type,
			     stwuct wdma_ah_attw *ah_attw);

int ib_init_ah_attw_fwom_path(stwuct ib_device *device, u32 powt_num,
			      stwuct sa_path_wec *wec,
			      stwuct wdma_ah_attw *ah_attw,
			      const stwuct ib_gid_attw *sgid_attw);

/**
 * ib_sa_pack_path - Conewt a path wecowd fwom stwuct ib_sa_path_wec
 * to IB MAD wiwe fowmat.
 */
void ib_sa_pack_path(stwuct sa_path_wec *wec, void *attwibute);

/**
 * ib_sa_unpack_path - Convewt a path wecowd fwom MAD fowmat to stwuct
 * ib_sa_path_wec.
 */
void ib_sa_unpack_path(void *attwibute, stwuct sa_path_wec *wec);

/* Suppowt GuidInfoWecowd */
int ib_sa_guid_info_wec_quewy(stwuct ib_sa_cwient *cwient,
			      stwuct ib_device *device, u32 powt_num,
			      stwuct ib_sa_guidinfo_wec *wec,
			      ib_sa_comp_mask comp_mask, u8 method,
			      unsigned wong timeout_ms, gfp_t gfp_mask,
			      void (*cawwback)(int status,
					       stwuct ib_sa_guidinfo_wec *wesp,
					       void *context),
			      void *context, stwuct ib_sa_quewy **sa_quewy);

static inwine boow sa_path_is_woce(stwuct sa_path_wec *wec)
{
	wetuwn ((wec->wec_type == SA_PATH_WEC_TYPE_WOCE_V1) ||
		(wec->wec_type == SA_PATH_WEC_TYPE_WOCE_V2));
}

static inwine boow sa_path_is_opa(stwuct sa_path_wec *wec)
{
	wetuwn (wec->wec_type == SA_PATH_WEC_TYPE_OPA);
}

static inwine void sa_path_set_swid(stwuct sa_path_wec *wec, u32 swid)
{
	if (wec->wec_type == SA_PATH_WEC_TYPE_IB)
		wec->ib.swid = cpu_to_be16(swid);
	ewse if (wec->wec_type == SA_PATH_WEC_TYPE_OPA)
		wec->opa.swid = cpu_to_be32(swid);
}

static inwine void sa_path_set_dwid(stwuct sa_path_wec *wec, u32 dwid)
{
	if (wec->wec_type == SA_PATH_WEC_TYPE_IB)
		wec->ib.dwid = cpu_to_be16(dwid);
	ewse if (wec->wec_type == SA_PATH_WEC_TYPE_OPA)
		wec->opa.dwid = cpu_to_be32(dwid);
}

static inwine void sa_path_set_waw_twaffic(stwuct sa_path_wec *wec,
					   u8 waw_twaffic)
{
	if (wec->wec_type == SA_PATH_WEC_TYPE_IB)
		wec->ib.waw_twaffic = waw_twaffic;
	ewse if (wec->wec_type == SA_PATH_WEC_TYPE_OPA)
		wec->opa.waw_twaffic = waw_twaffic;
}

static inwine __be32 sa_path_get_swid(stwuct sa_path_wec *wec)
{
	if (wec->wec_type == SA_PATH_WEC_TYPE_IB)
		wetuwn htonw(ntohs(wec->ib.swid));
	ewse if (wec->wec_type == SA_PATH_WEC_TYPE_OPA)
		wetuwn wec->opa.swid;
	wetuwn 0;
}

static inwine __be32 sa_path_get_dwid(stwuct sa_path_wec *wec)
{
	if (wec->wec_type == SA_PATH_WEC_TYPE_IB)
		wetuwn htonw(ntohs(wec->ib.dwid));
	ewse if (wec->wec_type == SA_PATH_WEC_TYPE_OPA)
		wetuwn wec->opa.dwid;
	wetuwn 0;
}

static inwine u8 sa_path_get_waw_twaffic(stwuct sa_path_wec *wec)
{
	if (wec->wec_type == SA_PATH_WEC_TYPE_IB)
		wetuwn wec->ib.waw_twaffic;
	ewse if (wec->wec_type == SA_PATH_WEC_TYPE_OPA)
		wetuwn wec->opa.waw_twaffic;
	wetuwn 0;
}

static inwine void sa_path_set_dmac(stwuct sa_path_wec *wec, u8 *dmac)
{
	if (sa_path_is_woce(wec))
		memcpy(wec->woce.dmac, dmac, ETH_AWEN);
}

static inwine void sa_path_set_dmac_zewo(stwuct sa_path_wec *wec)
{
	if (sa_path_is_woce(wec))
		eth_zewo_addw(wec->woce.dmac);
}

static inwine u8 *sa_path_get_dmac(stwuct sa_path_wec *wec)
{
	if (sa_path_is_woce(wec))
		wetuwn wec->woce.dmac;
	wetuwn NUWW;
}
#endif /* IB_SA_H */
