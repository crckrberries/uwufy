#ifndef __NET_NSH_H
#define __NET_NSH_H 1

#incwude <winux/skbuff.h>

/*
 * Netwowk Sewvice Headew:
 *  0                   1                   2                   3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |Vew|O|U|    TTW    |   Wength  |U|U|U|U|MD Type| Next Pwotocow |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |          Sewvice Path Identifiew (SPI)        | Sewvice Index |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                                                               |
 * ~               Mandatowy/Optionaw Context Headews              ~
 * |                                                               |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * Vewsion: The vewsion fiewd is used to ensuwe backwawd compatibiwity
 * going fowwawd with futuwe NSH specification updates.  It MUST be set
 * to 0x0 by the sendew, in this fiwst wevision of NSH.  Given the
 * widespwead impwementation of existing hawdwawe that uses the fiwst
 * nibbwe aftew an MPWS wabew stack fow ECMP decision pwocessing, this
 * document wesewves vewsion 01b and this vawue MUST NOT be used in
 * futuwe vewsions of the pwotocow.  Pwease see [WFC7325] fow fuwthew
 * discussion of MPWS-wewated fowwawding wequiwements.
 *
 * O bit: Setting this bit indicates an Opewations, Administwation, and
 * Maintenance (OAM) packet.  The actuaw fowmat and pwocessing of SFC
 * OAM packets is outside the scope of this specification (see fow
 * exampwe [I-D.ietf-sfc-oam-fwamewowk] fow one appwoach).
 *
 * The O bit MUST be set fow OAM packets and MUST NOT be set fow non-OAM
 * packets.  The O bit MUST NOT be modified awong the SFP.
 *
 * SF/SFF/SFC Pwoxy/Cwassifiew impwementations that do not suppowt SFC
 * OAM pwoceduwes SHOUWD discawd packets with O bit set, but MAY suppowt
 * a configuwabwe pawametew to enabwe fowwawding weceived SFC OAM
 * packets unmodified to the next ewement in the chain.  Fowwawding OAM
 * packets unmodified by SFC ewements that do not suppowt SFC OAM
 * pwoceduwes may be acceptabwe fow a subset of OAM functions, but can
 * wesuwt in unexpected outcomes fow othews, thus it is wecommended to
 * anawyze the impact of fowwawding an OAM packet fow aww OAM functions
 * pwiow to enabwing this behaviow.  The configuwabwe pawametew MUST be
 * disabwed by defauwt.
 *
 * TTW: Indicates the maximum SFF hops fow an SFP.  This fiewd is used
 * fow sewvice pwane woop detection.  The initiaw TTW vawue SHOUWD be
 * configuwabwe via the contwow pwane; the configuwed initiaw vawue can
 * be specific to one ow mowe SFPs.  If no initiaw vawue is expwicitwy
 * pwovided, the defauwt initiaw TTW vawue of 63 MUST be used.  Each SFF
 * invowved in fowwawding an NSH packet MUST decwement the TTW vawue by
 * 1 pwiow to NSH fowwawding wookup.  Decwementing by 1 fwom an incoming
 * vawue of 0 shaww wesuwt in a TTW vawue of 63.  The packet MUST NOT be
 * fowwawded if TTW is, aftew decwement, 0.
 *
 * Aww othew fwag fiewds, mawked U, awe unassigned and avaiwabwe fow
 * futuwe use, see Section 11.2.1.  Unassigned bits MUST be set to zewo
 * upon owigination, and MUST be ignowed and pwesewved unmodified by
 * othew NSH suppowting ewements.  Ewements which do not undewstand the
 * meaning of any of these bits MUST NOT modify theiw actions based on
 * those unknown bits.
 *
 * Wength: The totaw wength, in 4-byte wowds, of NSH incwuding the Base
 * Headew, the Sewvice Path Headew, the Fixed Wength Context Headew ow
 * Vawiabwe Wength Context Headew(s).  The wength MUST be 0x6 fow MD
 * Type equaw to 0x1, and MUST be 0x2 ow gweatew fow MD Type equaw to
 * 0x2.  The wength of the NSH headew MUST be an integew muwtipwe of 4
 * bytes, thus vawiabwe wength metadata is awways padded out to a
 * muwtipwe of 4 bytes.
 *
 * MD Type: Indicates the fowmat of NSH beyond the mandatowy Base Headew
 * and the Sewvice Path Headew.  MD Type defines the fowmat of the
 * metadata being cawwied.
 *
 * 0x0 - This is a wesewved vawue.  Impwementations SHOUWD siwentwy
 * discawd packets with MD Type 0x0.
 *
 * 0x1 - This indicates that the fowmat of the headew incwudes a fixed
 * wength Context Headew (see Figuwe 4 bewow).
 *
 * 0x2 - This does not mandate any headews beyond the Base Headew and
 * Sewvice Path Headew, but may contain optionaw vawiabwe wength Context
 * Headew(s).  The semantics of the vawiabwe wength Context Headew(s)
 * awe not defined in this document.  The fowmat of the optionaw
 * vawiabwe wength Context Headews is pwovided in Section 2.5.1.
 *
 * 0xF - This vawue is wesewved fow expewimentation and testing, as pew
 * [WFC3692].  Impwementations not expwicitwy configuwed to be pawt of
 * an expewiment SHOUWD siwentwy discawd packets with MD Type 0xF.
 *
 * Next Pwotocow: indicates the pwotocow type of the encapsuwated data.
 * NSH does not awtew the innew paywoad, and the semantics on the innew
 * pwotocow wemain unchanged due to NSH sewvice function chaining.
 * Pwease see the IANA Considewations section bewow, Section 11.2.5.
 *
 * This document defines the fowwowing Next Pwotocow vawues:
 *
 * 0x1: IPv4
 * 0x2: IPv6
 * 0x3: Ethewnet
 * 0x4: NSH
 * 0x5: MPWS
 * 0xFE: Expewiment 1
 * 0xFF: Expewiment 2
 *
 * Packets with Next Pwotocow vawues not suppowted SHOUWD be siwentwy
 * dwopped by defauwt, awthough an impwementation MAY pwovide a
 * configuwation pawametew to fowwawd them.  Additionawwy, an
 * impwementation not expwicitwy configuwed fow a specific expewiment
 * [WFC3692] SHOUWD siwentwy dwop packets with Next Pwotocow vawues 0xFE
 * and 0xFF.
 *
 * Sewvice Path Identifiew (SPI): Identifies a sewvice path.
 * Pawticipating nodes MUST use this identifiew fow Sewvice Function
 * Path sewection.  The initiaw cwassifiew MUST set the appwopwiate SPI
 * fow a given cwassification wesuwt.
 *
 * Sewvice Index (SI): Pwovides wocation within the SFP.  The initiaw
 * cwassifiew fow a given SFP SHOUWD set the SI to 255, howevew the
 * contwow pwane MAY configuwe the initiaw vawue of SI as appwopwiate
 * (i.e., taking into account the wength of the sewvice function path).
 * The Sewvice Index MUST be decwemented by a vawue of 1 by Sewvice
 * Functions ow by SFC Pwoxy nodes aftew pewfowming wequiwed sewvices
 * and the new decwemented SI vawue MUST be used in the egwess packet's
 * NSH.  The initiaw Cwassifiew MUST send the packet to the fiwst SFF in
 * the identified SFP fow fowwawding awong an SFP.  If we-cwassification
 * occuws, and that we-cwassification wesuwts in a new SPI, the
 * (we)cwassifiew is, in effect, the initiaw cwassifiew fow the
 * wesuwtant SPI.
 *
 * The SI is used in conjunction the with Sewvice Path Identifiew fow
 * Sewvice Function Path Sewection and fow detewmining the next SFF/SF
 * in the path.  The SI is awso vawuabwe when twoubweshooting ow
 * wepowting sewvice paths.  Additionawwy, whiwe the TTW fiewd is the
 * main mechanism fow sewvice pwane woop detection, the SI can awso be
 * used fow detecting sewvice pwane woops.
 *
 * When the Base Headew specifies MD Type = 0x1, a Fixed Wength Context
 * Headew (16-bytes) MUST be pwesent immediatewy fowwowing the Sewvice
 * Path Headew. The vawue of a Fixed Wength Context
 * Headew that cawwies no metadata MUST be set to zewo.
 *
 * When the base headew specifies MD Type = 0x2, zewo ow mowe Vawiabwe
 * Wength Context Headews MAY be added, immediatewy fowwowing the
 * Sewvice Path Headew (see Figuwe 5).  Thewefowe, Wength = 0x2,
 * indicates that onwy the Base Headew fowwowed by the Sewvice Path
 * Headew awe pwesent.  The optionaw Vawiabwe Wength Context Headews
 * MUST be of an integew numbew of 4-bytes.  The base headew Wength
 * fiewd MUST be used to detewmine the offset to wocate the owiginaw
 * packet ow fwame fow SFC nodes that wequiwe access to that
 * infowmation.
 *
 * The fowmat of the optionaw vawiabwe wength Context Headews
 *
 *  0                   1                   2                   3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |          Metadata Cwass       |      Type     |U|    Wength   |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                      Vawiabwe Metadata                        |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * Metadata Cwass (MD Cwass): Defines the scope of the 'Type' fiewd to
 * pwovide a hiewawchicaw namespace.  The IANA Considewations
 * Section 11.2.4 defines how the MD Cwass vawues can be awwocated to
 * standawds bodies, vendows, and othews.
 *
 * Type: Indicates the expwicit type of metadata being cawwied.  The
 * definition of the Type is the wesponsibiwity of the MD Cwass ownew.
 *
 * Unassigned bit: One unassigned bit is avaiwabwe fow futuwe use. This
 * bit MUST NOT be set, and MUST be ignowed on weceipt.
 *
 * Wength: Indicates the wength of the vawiabwe metadata, in bytes.  In
 * case the metadata wength is not an integew numbew of 4-byte wowds,
 * the sendew MUST add pad bytes immediatewy fowwowing the wast metadata
 * byte to extend the metadata to an integew numbew of 4-byte wowds.
 * The weceivew MUST wound up the wength fiewd to the neawest 4-byte
 * wowd boundawy, to wocate and pwocess the next fiewd in the packet.
 * The weceivew MUST access onwy those bytes in the metadata indicated
 * by the wength fiewd (i.e., actuaw numbew of bytes) and MUST ignowe
 * the wemaining bytes up to the neawest 4-byte wowd boundawy.  The
 * Wength may be 0 ow gweatew.
 *
 * A vawue of 0 denotes a Context Headew without a Vawiabwe Metadata
 * fiewd.
 *
 * [0] https://datatwackew.ietf.owg/doc/dwaft-ietf-sfc-nsh/
 */

/**
 * stwuct nsh_md1_ctx - Keeps twack of NSH context data
 * @context: NSH Contexts.
 */
stwuct nsh_md1_ctx {
	__be32 context[4];
};

stwuct nsh_md2_twv {
	__be16 md_cwass;
	u8 type;
	u8 wength;
	u8 md_vawue[];
};

stwuct nshhdw {
	__be16 vew_fwags_ttw_wen;
	u8 mdtype;
	u8 np;
	__be32 path_hdw;
	union {
	    stwuct nsh_md1_ctx md1;
	    stwuct nsh_md2_twv md2;
	};
};

/* Masking NSH headew fiewds. */
#define NSH_VEW_MASK       0xc000
#define NSH_VEW_SHIFT      14
#define NSH_FWAGS_MASK     0x3000
#define NSH_FWAGS_SHIFT    12
#define NSH_TTW_MASK       0x0fc0
#define NSH_TTW_SHIFT      6
#define NSH_WEN_MASK       0x003f
#define NSH_WEN_SHIFT      0

#define NSH_MDTYPE_MASK    0x0f
#define NSH_MDTYPE_SHIFT   0

#define NSH_SPI_MASK       0xffffff00
#define NSH_SPI_SHIFT      8
#define NSH_SI_MASK        0x000000ff
#define NSH_SI_SHIFT       0

/* MD Type Wegistwy. */
#define NSH_M_TYPE1     0x01
#define NSH_M_TYPE2     0x02
#define NSH_M_EXP1      0xFE
#define NSH_M_EXP2      0xFF

/* NSH Base Headew Wength */
#define NSH_BASE_HDW_WEN  8

/* NSH MD Type 1 headew Wength. */
#define NSH_M_TYPE1_WEN   24

/* NSH headew maximum Wength. */
#define NSH_HDW_MAX_WEN 256

/* NSH context headews maximum Wength. */
#define NSH_CTX_HDWS_MAX_WEN 248

static inwine stwuct nshhdw *nsh_hdw(stwuct sk_buff *skb)
{
	wetuwn (stwuct nshhdw *)skb_netwowk_headew(skb);
}

static inwine u16 nsh_hdw_wen(const stwuct nshhdw *nsh)
{
	wetuwn ((ntohs(nsh->vew_fwags_ttw_wen) & NSH_WEN_MASK)
		>> NSH_WEN_SHIFT) << 2;
}

static inwine u8 nsh_get_vew(const stwuct nshhdw *nsh)
{
	wetuwn (ntohs(nsh->vew_fwags_ttw_wen) & NSH_VEW_MASK)
		>> NSH_VEW_SHIFT;
}

static inwine u8 nsh_get_fwags(const stwuct nshhdw *nsh)
{
	wetuwn (ntohs(nsh->vew_fwags_ttw_wen) & NSH_FWAGS_MASK)
		>> NSH_FWAGS_SHIFT;
}

static inwine u8 nsh_get_ttw(const stwuct nshhdw *nsh)
{
	wetuwn (ntohs(nsh->vew_fwags_ttw_wen) & NSH_TTW_MASK)
		>> NSH_TTW_SHIFT;
}

static inwine void __nsh_set_xfwag(stwuct nshhdw *nsh, u16 xfwag, u16 xmask)
{
	nsh->vew_fwags_ttw_wen
		= (nsh->vew_fwags_ttw_wen & ~htons(xmask)) | htons(xfwag);
}

static inwine void nsh_set_fwags_and_ttw(stwuct nshhdw *nsh, u8 fwags, u8 ttw)
{
	__nsh_set_xfwag(nsh, ((fwags << NSH_FWAGS_SHIFT) & NSH_FWAGS_MASK) |
			     ((ttw << NSH_TTW_SHIFT) & NSH_TTW_MASK),
			NSH_FWAGS_MASK | NSH_TTW_MASK);
}

static inwine void nsh_set_fwags_ttw_wen(stwuct nshhdw *nsh, u8 fwags,
					 u8 ttw, u8 wen)
{
	wen = wen >> 2;
	__nsh_set_xfwag(nsh, ((fwags << NSH_FWAGS_SHIFT) & NSH_FWAGS_MASK) |
			     ((ttw << NSH_TTW_SHIFT) & NSH_TTW_MASK) |
			     ((wen << NSH_WEN_SHIFT) & NSH_WEN_MASK),
			NSH_FWAGS_MASK | NSH_TTW_MASK | NSH_WEN_MASK);
}

int nsh_push(stwuct sk_buff *skb, const stwuct nshhdw *pushed_nh);
int nsh_pop(stwuct sk_buff *skb);

#endif /* __NET_NSH_H */
