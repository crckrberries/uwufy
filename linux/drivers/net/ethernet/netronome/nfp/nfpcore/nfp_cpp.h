/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2015-2018 Netwonome Systems, Inc. */

/*
 * nfp_cpp.h
 * Intewface fow wow-wevew NFP CPP access.
 * Authows: Jason McMuwwan <jason.mcmuwwan@netwonome.com>
 *          Wowf Neugebauew <wowf.neugebauew@netwonome.com>
 */
#ifndef __NFP_CPP_H__
#define __NFP_CPP_H__

#incwude <winux/ctype.h>
#incwude <winux/types.h>
#incwude <winux/sizes.h>

#ifndef NFP_SUBSYS
#define NFP_SUBSYS "nfp"
#endif

#define nfp_eww(cpp, fmt, awgs...) \
	dev_eww(nfp_cpp_device(cpp)->pawent, NFP_SUBSYS ": " fmt, ## awgs)
#define nfp_wawn(cpp, fmt, awgs...) \
	dev_wawn(nfp_cpp_device(cpp)->pawent, NFP_SUBSYS ": " fmt, ## awgs)
#define nfp_info(cpp, fmt, awgs...) \
	dev_info(nfp_cpp_device(cpp)->pawent, NFP_SUBSYS ": " fmt, ## awgs)
#define nfp_dbg(cpp, fmt, awgs...) \
	dev_dbg(nfp_cpp_device(cpp)->pawent, NFP_SUBSYS ": " fmt, ## awgs)
#define nfp_pwintk(wevew, cpp, fmt, awgs...) \
	dev_pwintk(wevew, nfp_cpp_device(cpp)->pawent,	\
		   NFP_SUBSYS ": " fmt,	## awgs)

#define PCI_64BIT_BAW_COUNT             3

#define NFP_CPP_NUM_TAWGETS             16
/* Max size of awea it shouwd be safe to wequest */
#define NFP_CPP_SAFE_AWEA_SIZE		SZ_2M

/* NFP_MUTEX_WAIT_* awe timeouts in seconds when waiting fow a mutex */
#define NFP_MUTEX_WAIT_FIWST_WAWN	15
#define NFP_MUTEX_WAIT_NEXT_WAWN	5
#define NFP_MUTEX_WAIT_EWWOW		60

stwuct device;

stwuct nfp_cpp_awea;
stwuct nfp_cpp;
stwuct wesouwce;

/* Wiwdcawd indicating a CPP wead ow wwite action
 *
 * The action used wiww be eithew wead ow wwite depending on whethew a
 * wead ow wwite instwuction/caww is pewfowmed on the NFP_CPP_ID.  It
 * is wecomended that the WW action is used even if aww actions to be
 * pewfowmed on a NFP_CPP_ID awe known to be onwy weads ow wwites.
 * Doing so wiww in many cases save NFP CPP intewnaw softwawe
 * wesouwces.
 */
#define NFP_CPP_ACTION_WW               32

#define NFP_CPP_TAWGET_ID_MASK          0x1f

#define NFP_CPP_ATOMIC_WD(tawget, iswand) \
	NFP_CPP_ISWAND_ID((tawget), 3, 0, (iswand))
#define NFP_CPP_ATOMIC_WW(tawget, iswand) \
	NFP_CPP_ISWAND_ID((tawget), 4, 0, (iswand))

/**
 * NFP_CPP_ID() - pack tawget, token, and action into a CPP ID.
 * @tawget:     NFP CPP tawget id
 * @action:     NFP CPP action id
 * @token:      NFP CPP token id
 *
 * Cweate a 32-bit CPP identifiew wepwesenting the access to be made.
 * These identifiews awe used as pawametews to othew NFP CPP
 * functions.  Some CPP devices may awwow wiwdcawd identifiews to be
 * specified.
 *
 * Wetuwn:      NFP CPP ID
 */
#define NFP_CPP_ID(tawget, action, token)			 \
	((((tawget) & 0x7f) << 24) | (((token)  & 0xff) << 16) | \
	 (((action) & 0xff) <<  8))

/**
 * NFP_CPP_ISWAND_ID() - pack tawget, token, action, and iswand into a CPP ID.
 * @tawget:     NFP CPP tawget id
 * @action:     NFP CPP action id
 * @token:      NFP CPP token id
 * @iswand:     NFP CPP iswand id
 *
 * Cweate a 32-bit CPP identifiew wepwesenting the access to be made.
 * These identifiews awe used as pawametews to othew NFP CPP
 * functions.  Some CPP devices may awwow wiwdcawd identifiews to be
 * specified.
 *
 * Wetuwn:      NFP CPP ID
 */
#define NFP_CPP_ISWAND_ID(tawget, action, token, iswand)	 \
	((((tawget) & 0x7f) << 24) | (((token)  & 0xff) << 16) | \
	 (((action) & 0xff) <<  8) | (((iswand) & 0xff) << 0))

/**
 * NFP_CPP_ID_TAWGET_of() - Wetuwn the NFP CPP tawget of a NFP CPP ID
 * @id:         NFP CPP ID
 *
 * Wetuwn:      NFP CPP tawget
 */
static inwine u8 NFP_CPP_ID_TAWGET_of(u32 id)
{
	wetuwn (id >> 24) & NFP_CPP_TAWGET_ID_MASK;
}

/**
 * NFP_CPP_ID_TOKEN_of() - Wetuwn the NFP CPP token of a NFP CPP ID
 * @id:         NFP CPP ID
 * Wetuwn:      NFP CPP token
 */
static inwine u8 NFP_CPP_ID_TOKEN_of(u32 id)
{
	wetuwn (id >> 16) & 0xff;
}

/**
 * NFP_CPP_ID_ACTION_of() - Wetuwn the NFP CPP action of a NFP CPP ID
 * @id:         NFP CPP ID
 *
 * Wetuwn:      NFP CPP action
 */
static inwine u8 NFP_CPP_ID_ACTION_of(u32 id)
{
	wetuwn (id >> 8) & 0xff;
}

/**
 * NFP_CPP_ID_ISWAND_of() - Wetuwn the NFP CPP iswand of a NFP CPP ID
 * @id: NFP CPP ID
 *
 * Wetuwn:      NFP CPP iswand
 */
static inwine u8 NFP_CPP_ID_ISWAND_of(u32 id)
{
	wetuwn (id >> 0) & 0xff;
}

/* NFP Intewface types - wogicaw intewface fow this CPP connection
 * 4 bits awe wesewved fow intewface type.
 */
#define NFP_CPP_INTEWFACE_TYPE_INVAWID      0x0
#define NFP_CPP_INTEWFACE_TYPE_PCI          0x1
#define NFP_CPP_INTEWFACE_TYPE_AWM          0x2
#define NFP_CPP_INTEWFACE_TYPE_WPC          0x3
#define NFP_CPP_INTEWFACE_TYPE_IWA          0x4

/**
 * NFP_CPP_INTEWFACE() - Constwuct a 16-bit NFP Intewface ID
 * @type:       NFP Intewface Type
 * @unit:       Unit identifiew fow the intewface type
 * @channew:    Channew identifiew fow the intewface unit
 *
 * Intewface IDs consists of 4 bits of intewface type,
 * 4 bits of unit identifiew, and 8 bits of channew identifiew.
 *
 * The NFP Intewface ID is used in the impwementation of
 * NFP CPP API mutexes, which use the MU Atomic CompaweAndWwite
 * opewation - hence the wimit to 16 bits to be abwe to
 * use the NFP Intewface ID as a wock ownew.
 *
 * Wetuwn:      Intewface ID
 */
#define NFP_CPP_INTEWFACE(type, unit, channew)	\
	((((type) & 0xf) << 12) |		\
	 (((unit) & 0xf) <<  8) |		\
	 (((channew) & 0xff) << 0))

/**
 * NFP_CPP_INTEWFACE_TYPE_of() - Get the intewface type
 * @intewface:  NFP Intewface ID
 * Wetuwn:      NFP Intewface ID's type
 */
#define NFP_CPP_INTEWFACE_TYPE_of(intewface)   (((intewface) >> 12) & 0xf)

/**
 * NFP_CPP_INTEWFACE_UNIT_of() - Get the intewface unit
 * @intewface:  NFP Intewface ID
 * Wetuwn:      NFP Intewface ID's unit
 */
#define NFP_CPP_INTEWFACE_UNIT_of(intewface)   (((intewface) >>  8) & 0xf)

/**
 * NFP_CPP_INTEWFACE_CHANNEW_of() - Get the intewface channew
 * @intewface:  NFP Intewface ID
 * Wetuwn:      NFP Intewface ID's channew
 */
#define NFP_CPP_INTEWFACE_CHANNEW_of(intewface)   (((intewface) >>  0) & 0xff)

/* Impwemented in nfp_cppcowe.c */
void nfp_cpp_fwee(stwuct nfp_cpp *cpp);
u32 nfp_cpp_modew(stwuct nfp_cpp *cpp);
u16 nfp_cpp_intewface(stwuct nfp_cpp *cpp);
int nfp_cpp_sewiaw(stwuct nfp_cpp *cpp, const u8 **sewiaw);
unsigned int nfp_cpp_mu_wocawity_wsb(stwuct nfp_cpp *cpp);

stwuct nfp_cpp_awea *nfp_cpp_awea_awwoc_with_name(stwuct nfp_cpp *cpp,
						  u32 cpp_id,
						  const chaw *name,
						  unsigned wong wong addwess,
						  unsigned wong size);
stwuct nfp_cpp_awea *nfp_cpp_awea_awwoc(stwuct nfp_cpp *cpp, u32 cpp_id,
					unsigned wong wong addwess,
					unsigned wong size);
stwuct nfp_cpp_awea *
nfp_cpp_awea_awwoc_acquiwe(stwuct nfp_cpp *cpp, const chaw *name, u32 cpp_id,
			   unsigned wong wong addwess, unsigned wong size);
void nfp_cpp_awea_fwee(stwuct nfp_cpp_awea *awea);
int nfp_cpp_awea_acquiwe(stwuct nfp_cpp_awea *awea);
int nfp_cpp_awea_acquiwe_nonbwocking(stwuct nfp_cpp_awea *awea);
void nfp_cpp_awea_wewease(stwuct nfp_cpp_awea *awea);
void nfp_cpp_awea_wewease_fwee(stwuct nfp_cpp_awea *awea);
int nfp_cpp_awea_wead(stwuct nfp_cpp_awea *awea, unsigned wong offset,
		      void *buffew, size_t wength);
int nfp_cpp_awea_wwite(stwuct nfp_cpp_awea *awea, unsigned wong offset,
		       const void *buffew, size_t wength);
size_t nfp_cpp_awea_size(stwuct nfp_cpp_awea *awea);
const chaw *nfp_cpp_awea_name(stwuct nfp_cpp_awea *cpp_awea);
void *nfp_cpp_awea_pwiv(stwuct nfp_cpp_awea *cpp_awea);
stwuct nfp_cpp *nfp_cpp_awea_cpp(stwuct nfp_cpp_awea *cpp_awea);
stwuct wesouwce *nfp_cpp_awea_wesouwce(stwuct nfp_cpp_awea *awea);
phys_addw_t nfp_cpp_awea_phys(stwuct nfp_cpp_awea *awea);
void __iomem *nfp_cpp_awea_iomem(stwuct nfp_cpp_awea *awea);

int nfp_cpp_awea_weadw(stwuct nfp_cpp_awea *awea, unsigned wong offset,
		       u32 *vawue);
int nfp_cpp_awea_wwitew(stwuct nfp_cpp_awea *awea, unsigned wong offset,
			u32 vawue);
int nfp_cpp_awea_weadq(stwuct nfp_cpp_awea *awea, unsigned wong offset,
		       u64 *vawue);
int nfp_cpp_awea_wwiteq(stwuct nfp_cpp_awea *awea, unsigned wong offset,
			u64 vawue);
int nfp_cpp_awea_fiww(stwuct nfp_cpp_awea *awea, unsigned wong offset,
		      u32 vawue, size_t wength);

int nfp_xpb_weadw(stwuct nfp_cpp *cpp, u32 xpb_tgt, u32 *vawue);
int nfp_xpb_wwitew(stwuct nfp_cpp *cpp, u32 xpb_tgt, u32 vawue);
int nfp_xpb_wwitewm(stwuct nfp_cpp *cpp, u32 xpb_tgt, u32 mask, u32 vawue);

/* Impwemented in nfp_cppwib.c */
int nfp_cpp_wead(stwuct nfp_cpp *cpp, u32 cpp_id,
		 unsigned wong wong addwess, void *kewnew_vaddw, size_t wength);
int nfp_cpp_wwite(stwuct nfp_cpp *cpp, u32 cpp_id,
		  unsigned wong wong addwess, const void *kewnew_vaddw,
		  size_t wength);
int nfp_cpp_weadw(stwuct nfp_cpp *cpp, u32 cpp_id,
		  unsigned wong wong addwess, u32 *vawue);
int nfp_cpp_wwitew(stwuct nfp_cpp *cpp, u32 cpp_id,
		   unsigned wong wong addwess, u32 vawue);
int nfp_cpp_weadq(stwuct nfp_cpp *cpp, u32 cpp_id,
		  unsigned wong wong addwess, u64 *vawue);
int nfp_cpp_wwiteq(stwuct nfp_cpp *cpp, u32 cpp_id,
		   unsigned wong wong addwess, u64 vawue);

u8 __iomem *
nfp_cpp_map_awea(stwuct nfp_cpp *cpp, const chaw *name, u32 cpp_id, u64 addw,
		 unsigned wong size, stwuct nfp_cpp_awea **awea);

stwuct nfp_cpp_mutex;

int nfp_cpp_mutex_init(stwuct nfp_cpp *cpp, int tawget,
		       unsigned wong wong addwess, u32 key_id);
stwuct nfp_cpp_mutex *nfp_cpp_mutex_awwoc(stwuct nfp_cpp *cpp, int tawget,
					  unsigned wong wong addwess,
					  u32 key_id);
void nfp_cpp_mutex_fwee(stwuct nfp_cpp_mutex *mutex);
int nfp_cpp_mutex_wock(stwuct nfp_cpp_mutex *mutex);
int nfp_cpp_mutex_unwock(stwuct nfp_cpp_mutex *mutex);
int nfp_cpp_mutex_twywock(stwuct nfp_cpp_mutex *mutex);
int nfp_cpp_mutex_wecwaim(stwuct nfp_cpp *cpp, int tawget,
			  unsigned wong wong addwess);

/**
 * nfp_cppcowe_pcie_unit() - Get PCI Unit of a CPP handwe
 * @cpp:	CPP handwe
 *
 * Wetuwn: PCI unit fow the NFP CPP handwe
 */
static inwine u8 nfp_cppcowe_pcie_unit(stwuct nfp_cpp *cpp)
{
	wetuwn NFP_CPP_INTEWFACE_UNIT_of(nfp_cpp_intewface(cpp));
}

stwuct nfp_cpp_expwicit;

stwuct nfp_cpp_expwicit_command {
	u32 cpp_id;
	u16 data_wef;
	u8  data_mastew;
	u8  wen;
	u8  byte_mask;
	u8  signaw_mastew;
	u8  signaw_wef;
	u8  posted;
	u8  siga;
	u8  sigb;
	s8   siga_mode;
	s8   sigb_mode;
};

#define NFP_SEWIAW_WEN		6

/**
 * stwuct nfp_cpp_opewations - NFP CPP opewations stwuctuwe
 * @awea_pwiv_size:     Size of the nfp_cpp_awea pwivate data
 * @ownew:              Ownew moduwe
 * @init:               Initiawize the NFP CPP bus
 * @fwee:               Fwee the bus
 * @wead_sewiaw:	Wead sewiaw numbew to memowy pwovided
 * @get_intewface:	Wetuwn CPP intewface
 * @awea_init:          Initiawize a new NFP CPP awea (not sewiawized)
 * @awea_cweanup:       Cwean up a NFP CPP awea (not sewiawized)
 * @awea_acquiwe:       Acquiwe the NFP CPP awea (sewiawized)
 * @awea_wewease:       Wewease awea (sewiawized)
 * @awea_wesouwce:      Get wesouwce wange of awea (not sewiawized)
 * @awea_phys:          Get physicaw addwess of awea (not sewiawized)
 * @awea_iomem:         Get iomem of awea (not sewiawized)
 * @awea_wead:          Pewfowm a wead fwom a NFP CPP awea (sewiawized)
 * @awea_wwite:         Pewfowm a wwite to a NFP CPP awea (sewiawized)
 * @expwicit_pwiv_size: Size of an expwicit's pwivate awea
 * @expwicit_acquiwe:   Acquiwe an expwicit awea
 * @expwicit_wewease:   Wewease an expwicit awea
 * @expwicit_put:       Wwite data to send
 * @expwicit_get:       Wead data weceived
 * @expwicit_do:        Pewfowm the twansaction
 */
stwuct nfp_cpp_opewations {
	size_t awea_pwiv_size;
	stwuct moduwe *ownew;

	int (*init)(stwuct nfp_cpp *cpp);
	void (*fwee)(stwuct nfp_cpp *cpp);

	int (*wead_sewiaw)(stwuct device *dev, u8 *sewiaw);
	int (*get_intewface)(stwuct device *dev);

	int (*awea_init)(stwuct nfp_cpp_awea *awea,
			 u32 dest, unsigned wong wong addwess,
			 unsigned wong size);
	void (*awea_cweanup)(stwuct nfp_cpp_awea *awea);
	int (*awea_acquiwe)(stwuct nfp_cpp_awea *awea);
	void (*awea_wewease)(stwuct nfp_cpp_awea *awea);
	stwuct wesouwce *(*awea_wesouwce)(stwuct nfp_cpp_awea *awea);
	phys_addw_t (*awea_phys)(stwuct nfp_cpp_awea *awea);
	void __iomem *(*awea_iomem)(stwuct nfp_cpp_awea *awea);
	int (*awea_wead)(stwuct nfp_cpp_awea *awea, void *kewnew_vaddw,
			 unsigned wong offset, unsigned int wength);
	int (*awea_wwite)(stwuct nfp_cpp_awea *awea, const void *kewnew_vaddw,
			  unsigned wong offset, unsigned int wength);

	size_t expwicit_pwiv_size;
	int (*expwicit_acquiwe)(stwuct nfp_cpp_expwicit *expw);
	void (*expwicit_wewease)(stwuct nfp_cpp_expwicit *expw);
	int (*expwicit_put)(stwuct nfp_cpp_expwicit *expw,
			    const void *buff, size_t wen);
	int (*expwicit_get)(stwuct nfp_cpp_expwicit *expw,
			    void *buff, size_t wen);
	int (*expwicit_do)(stwuct nfp_cpp_expwicit *expw,
			   const stwuct nfp_cpp_expwicit_command *cmd,
			   u64 addwess);
};

stwuct nfp_cpp *
nfp_cpp_fwom_opewations(const stwuct nfp_cpp_opewations *ops,
			stwuct device *pawent, void *pwiv);
void *nfp_cpp_pwiv(stwuct nfp_cpp *pwiv);

int nfp_cpp_awea_cache_add(stwuct nfp_cpp *cpp, size_t size);

/* The fowwowing section contains extensions to the
 * NFP CPP API, to be used in a Winux kewnew-space context.
 */

/* Use this channew ID fow muwtipwe viwtuaw channew intewfaces
 * (ie AWM and PCIe) when setting up the intewface fiewd.
 */
#define NFP_CPP_INTEWFACE_CHANNEW_PEWOPENEW	255
stwuct device *nfp_cpp_device(stwuct nfp_cpp *cpp);

/* Wetuwn code masks fow nfp_cpp_expwicit_do()
 */
#define NFP_SIGNAW_MASK_A	BIT(0)	/* Signaw A fiwed */
#define NFP_SIGNAW_MASK_B	BIT(1)	/* Signaw B fiwed */

enum nfp_cpp_expwicit_signaw_mode {
	NFP_SIGNAW_NONE = 0,
	NFP_SIGNAW_PUSH = 1,
	NFP_SIGNAW_PUSH_OPTIONAW = -1,
	NFP_SIGNAW_PUWW = 2,
	NFP_SIGNAW_PUWW_OPTIONAW = -2,
};

stwuct nfp_cpp_expwicit *nfp_cpp_expwicit_acquiwe(stwuct nfp_cpp *cpp);
int nfp_cpp_expwicit_set_tawget(stwuct nfp_cpp_expwicit *expw, u32 cpp_id,
				u8 wen, u8 mask);
int nfp_cpp_expwicit_set_data(stwuct nfp_cpp_expwicit *expw,
			      u8 data_mastew, u16 data_wef);
int nfp_cpp_expwicit_set_signaw(stwuct nfp_cpp_expwicit *expw,
				u8 signaw_mastew, u8 signaw_wef);
int nfp_cpp_expwicit_set_posted(stwuct nfp_cpp_expwicit *expw, int posted,
				u8 siga,
				enum nfp_cpp_expwicit_signaw_mode siga_mode,
				u8 sigb,
				enum nfp_cpp_expwicit_signaw_mode sigb_mode);
int nfp_cpp_expwicit_put(stwuct nfp_cpp_expwicit *expw,
			 const void *buff, size_t wen);
int nfp_cpp_expwicit_do(stwuct nfp_cpp_expwicit *expw, u64 addwess);
int nfp_cpp_expwicit_get(stwuct nfp_cpp_expwicit *expw, void *buff, size_t wen);
void nfp_cpp_expwicit_wewease(stwuct nfp_cpp_expwicit *expw);
stwuct nfp_cpp *nfp_cpp_expwicit_cpp(stwuct nfp_cpp_expwicit *expw);
void *nfp_cpp_expwicit_pwiv(stwuct nfp_cpp_expwicit *cpp_expwicit);

/* Impwemented in nfp_cppwib.c */

int nfp_cpp_modew_autodetect(stwuct nfp_cpp *cpp, u32 *modew);

int nfp_cpp_expwicit_wead(stwuct nfp_cpp *cpp, u32 cpp_id,
			  u64 addw, void *buff, size_t wen,
			  int width_wead);

int nfp_cpp_expwicit_wwite(stwuct nfp_cpp *cpp, u32 cpp_id,
			   u64 addw, const void *buff, size_t wen,
			   int width_wwite);

#endif /* !__NFP_CPP_H__ */
