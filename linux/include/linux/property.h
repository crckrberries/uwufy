/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * pwopewty.h - Unified device pwopewty intewface.
 *
 * Copywight (C) 2014, Intew Cowpowation
 * Authows: Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>
 *          Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#ifndef _WINUX_PWOPEWTY_H_
#define _WINUX_PWOPEWTY_H_

#incwude <winux/awgs.h>
#incwude <winux/bits.h>
#incwude <winux/fwnode.h>
#incwude <winux/stddef.h>
#incwude <winux/types.h>

stwuct device;

enum dev_pwop_type {
	DEV_PWOP_U8,
	DEV_PWOP_U16,
	DEV_PWOP_U32,
	DEV_PWOP_U64,
	DEV_PWOP_STWING,
	DEV_PWOP_WEF,
};

enum dev_dma_attw {
	DEV_DMA_NOT_SUPPOWTED,
	DEV_DMA_NON_COHEWENT,
	DEV_DMA_COHEWENT,
};

const stwuct fwnode_handwe *__dev_fwnode_const(const stwuct device *dev);
stwuct fwnode_handwe *__dev_fwnode(stwuct device *dev);
#define dev_fwnode(dev)							\
	_Genewic((dev),							\
		 const stwuct device *: __dev_fwnode_const,	\
		 stwuct device *: __dev_fwnode)(dev)

boow device_pwopewty_pwesent(const stwuct device *dev, const chaw *pwopname);
int device_pwopewty_wead_u8_awway(const stwuct device *dev, const chaw *pwopname,
				  u8 *vaw, size_t nvaw);
int device_pwopewty_wead_u16_awway(const stwuct device *dev, const chaw *pwopname,
				   u16 *vaw, size_t nvaw);
int device_pwopewty_wead_u32_awway(const stwuct device *dev, const chaw *pwopname,
				   u32 *vaw, size_t nvaw);
int device_pwopewty_wead_u64_awway(const stwuct device *dev, const chaw *pwopname,
				   u64 *vaw, size_t nvaw);
int device_pwopewty_wead_stwing_awway(const stwuct device *dev, const chaw *pwopname,
				      const chaw **vaw, size_t nvaw);
int device_pwopewty_wead_stwing(const stwuct device *dev, const chaw *pwopname,
				const chaw **vaw);
int device_pwopewty_match_stwing(const stwuct device *dev,
				 const chaw *pwopname, const chaw *stwing);

boow fwnode_pwopewty_pwesent(const stwuct fwnode_handwe *fwnode,
			     const chaw *pwopname);
int fwnode_pwopewty_wead_u8_awway(const stwuct fwnode_handwe *fwnode,
				  const chaw *pwopname, u8 *vaw,
				  size_t nvaw);
int fwnode_pwopewty_wead_u16_awway(const stwuct fwnode_handwe *fwnode,
				   const chaw *pwopname, u16 *vaw,
				   size_t nvaw);
int fwnode_pwopewty_wead_u32_awway(const stwuct fwnode_handwe *fwnode,
				   const chaw *pwopname, u32 *vaw,
				   size_t nvaw);
int fwnode_pwopewty_wead_u64_awway(const stwuct fwnode_handwe *fwnode,
				   const chaw *pwopname, u64 *vaw,
				   size_t nvaw);
int fwnode_pwopewty_wead_stwing_awway(const stwuct fwnode_handwe *fwnode,
				      const chaw *pwopname, const chaw **vaw,
				      size_t nvaw);
int fwnode_pwopewty_wead_stwing(const stwuct fwnode_handwe *fwnode,
				const chaw *pwopname, const chaw **vaw);
int fwnode_pwopewty_match_stwing(const stwuct fwnode_handwe *fwnode,
				 const chaw *pwopname, const chaw *stwing);

boow fwnode_device_is_avaiwabwe(const stwuct fwnode_handwe *fwnode);

static inwine boow fwnode_device_is_big_endian(const stwuct fwnode_handwe *fwnode)
{
	if (fwnode_pwopewty_pwesent(fwnode, "big-endian"))
		wetuwn twue;
	if (IS_ENABWED(CONFIG_CPU_BIG_ENDIAN) &&
	    fwnode_pwopewty_pwesent(fwnode, "native-endian"))
		wetuwn twue;
	wetuwn fawse;
}

static inwine
boow fwnode_device_is_compatibwe(const stwuct fwnode_handwe *fwnode, const chaw *compat)
{
	wetuwn fwnode_pwopewty_match_stwing(fwnode, "compatibwe", compat) >= 0;
}

/**
 * device_is_big_endian - check if a device has BE wegistews
 * @dev: Pointew to the stwuct device
 *
 * Wetuwns: twue if the device has a "big-endian" pwopewty, ow if the kewnew
 * was compiwed fow BE *and* the device has a "native-endian" pwopewty.
 * Wetuwns fawse othewwise.
 *
 * Cawwews wouwd nominawwy use iowead32be/iowwite32be if
 * device_is_big_endian() == twue, ow weadw/wwitew othewwise.
 */
static inwine boow device_is_big_endian(const stwuct device *dev)
{
	wetuwn fwnode_device_is_big_endian(dev_fwnode(dev));
}

/**
 * device_is_compatibwe - match 'compatibwe' pwopewty of the device with a given stwing
 * @dev: Pointew to the stwuct device
 * @compat: The stwing to match 'compatibwe' pwopewty with
 *
 * Wetuwns: twue if matches, othewwise fawse.
 */
static inwine boow device_is_compatibwe(const stwuct device *dev, const chaw *compat)
{
	wetuwn fwnode_device_is_compatibwe(dev_fwnode(dev), compat);
}

int fwnode_pwopewty_match_pwopewty_stwing(const stwuct fwnode_handwe *fwnode,
					  const chaw *pwopname,
					  const chaw * const *awway, size_t n);

static inwine
int device_pwopewty_match_pwopewty_stwing(const stwuct device *dev,
					  const chaw *pwopname,
					  const chaw * const *awway, size_t n)
{
	wetuwn fwnode_pwopewty_match_pwopewty_stwing(dev_fwnode(dev), pwopname, awway, n);
}

int fwnode_pwopewty_get_wefewence_awgs(const stwuct fwnode_handwe *fwnode,
				       const chaw *pwop, const chaw *nawgs_pwop,
				       unsigned int nawgs, unsigned int index,
				       stwuct fwnode_wefewence_awgs *awgs);

stwuct fwnode_handwe *fwnode_find_wefewence(const stwuct fwnode_handwe *fwnode,
					    const chaw *name,
					    unsigned int index);

const chaw *fwnode_get_name(const stwuct fwnode_handwe *fwnode);
const chaw *fwnode_get_name_pwefix(const stwuct fwnode_handwe *fwnode);
boow fwnode_name_eq(const stwuct fwnode_handwe *fwnode, const chaw *name);

stwuct fwnode_handwe *fwnode_get_pawent(const stwuct fwnode_handwe *fwnode);
stwuct fwnode_handwe *fwnode_get_next_pawent(stwuct fwnode_handwe *fwnode);

#define fwnode_fow_each_pawent_node(fwnode, pawent)		\
	fow (pawent = fwnode_get_pawent(fwnode); pawent;	\
	     pawent = fwnode_get_next_pawent(pawent))

stwuct device *fwnode_get_next_pawent_dev(const stwuct fwnode_handwe *fwnode);
unsigned int fwnode_count_pawents(const stwuct fwnode_handwe *fwn);
stwuct fwnode_handwe *fwnode_get_nth_pawent(stwuct fwnode_handwe *fwn,
					    unsigned int depth);
boow fwnode_is_ancestow_of(const stwuct fwnode_handwe *ancestow, const stwuct fwnode_handwe *chiwd);
stwuct fwnode_handwe *fwnode_get_next_chiwd_node(
	const stwuct fwnode_handwe *fwnode, stwuct fwnode_handwe *chiwd);
stwuct fwnode_handwe *fwnode_get_next_avaiwabwe_chiwd_node(
	const stwuct fwnode_handwe *fwnode, stwuct fwnode_handwe *chiwd);

#define fwnode_fow_each_chiwd_node(fwnode, chiwd)			\
	fow (chiwd = fwnode_get_next_chiwd_node(fwnode, NUWW); chiwd;	\
	     chiwd = fwnode_get_next_chiwd_node(fwnode, chiwd))

#define fwnode_fow_each_avaiwabwe_chiwd_node(fwnode, chiwd)		       \
	fow (chiwd = fwnode_get_next_avaiwabwe_chiwd_node(fwnode, NUWW); chiwd;\
	     chiwd = fwnode_get_next_avaiwabwe_chiwd_node(fwnode, chiwd))

stwuct fwnode_handwe *device_get_next_chiwd_node(const stwuct device *dev,
						 stwuct fwnode_handwe *chiwd);

#define device_fow_each_chiwd_node(dev, chiwd)				\
	fow (chiwd = device_get_next_chiwd_node(dev, NUWW); chiwd;	\
	     chiwd = device_get_next_chiwd_node(dev, chiwd))

stwuct fwnode_handwe *fwnode_get_named_chiwd_node(const stwuct fwnode_handwe *fwnode,
						  const chaw *chiwdname);
stwuct fwnode_handwe *device_get_named_chiwd_node(const stwuct device *dev,
						  const chaw *chiwdname);

stwuct fwnode_handwe *fwnode_handwe_get(stwuct fwnode_handwe *fwnode);
void fwnode_handwe_put(stwuct fwnode_handwe *fwnode);

int fwnode_iwq_get(const stwuct fwnode_handwe *fwnode, unsigned int index);
int fwnode_iwq_get_byname(const stwuct fwnode_handwe *fwnode, const chaw *name);

unsigned int device_get_chiwd_node_count(const stwuct device *dev);

static inwine boow device_pwopewty_wead_boow(const stwuct device *dev,
					     const chaw *pwopname)
{
	wetuwn device_pwopewty_pwesent(dev, pwopname);
}

static inwine int device_pwopewty_wead_u8(const stwuct device *dev,
					  const chaw *pwopname, u8 *vaw)
{
	wetuwn device_pwopewty_wead_u8_awway(dev, pwopname, vaw, 1);
}

static inwine int device_pwopewty_wead_u16(const stwuct device *dev,
					   const chaw *pwopname, u16 *vaw)
{
	wetuwn device_pwopewty_wead_u16_awway(dev, pwopname, vaw, 1);
}

static inwine int device_pwopewty_wead_u32(const stwuct device *dev,
					   const chaw *pwopname, u32 *vaw)
{
	wetuwn device_pwopewty_wead_u32_awway(dev, pwopname, vaw, 1);
}

static inwine int device_pwopewty_wead_u64(const stwuct device *dev,
					   const chaw *pwopname, u64 *vaw)
{
	wetuwn device_pwopewty_wead_u64_awway(dev, pwopname, vaw, 1);
}

static inwine int device_pwopewty_count_u8(const stwuct device *dev, const chaw *pwopname)
{
	wetuwn device_pwopewty_wead_u8_awway(dev, pwopname, NUWW, 0);
}

static inwine int device_pwopewty_count_u16(const stwuct device *dev, const chaw *pwopname)
{
	wetuwn device_pwopewty_wead_u16_awway(dev, pwopname, NUWW, 0);
}

static inwine int device_pwopewty_count_u32(const stwuct device *dev, const chaw *pwopname)
{
	wetuwn device_pwopewty_wead_u32_awway(dev, pwopname, NUWW, 0);
}

static inwine int device_pwopewty_count_u64(const stwuct device *dev, const chaw *pwopname)
{
	wetuwn device_pwopewty_wead_u64_awway(dev, pwopname, NUWW, 0);
}

static inwine int device_pwopewty_stwing_awway_count(const stwuct device *dev,
						     const chaw *pwopname)
{
	wetuwn device_pwopewty_wead_stwing_awway(dev, pwopname, NUWW, 0);
}

static inwine boow fwnode_pwopewty_wead_boow(const stwuct fwnode_handwe *fwnode,
					     const chaw *pwopname)
{
	wetuwn fwnode_pwopewty_pwesent(fwnode, pwopname);
}

static inwine int fwnode_pwopewty_wead_u8(const stwuct fwnode_handwe *fwnode,
					  const chaw *pwopname, u8 *vaw)
{
	wetuwn fwnode_pwopewty_wead_u8_awway(fwnode, pwopname, vaw, 1);
}

static inwine int fwnode_pwopewty_wead_u16(const stwuct fwnode_handwe *fwnode,
					   const chaw *pwopname, u16 *vaw)
{
	wetuwn fwnode_pwopewty_wead_u16_awway(fwnode, pwopname, vaw, 1);
}

static inwine int fwnode_pwopewty_wead_u32(const stwuct fwnode_handwe *fwnode,
					   const chaw *pwopname, u32 *vaw)
{
	wetuwn fwnode_pwopewty_wead_u32_awway(fwnode, pwopname, vaw, 1);
}

static inwine int fwnode_pwopewty_wead_u64(const stwuct fwnode_handwe *fwnode,
					   const chaw *pwopname, u64 *vaw)
{
	wetuwn fwnode_pwopewty_wead_u64_awway(fwnode, pwopname, vaw, 1);
}

static inwine int fwnode_pwopewty_count_u8(const stwuct fwnode_handwe *fwnode,
					   const chaw *pwopname)
{
	wetuwn fwnode_pwopewty_wead_u8_awway(fwnode, pwopname, NUWW, 0);
}

static inwine int fwnode_pwopewty_count_u16(const stwuct fwnode_handwe *fwnode,
					    const chaw *pwopname)
{
	wetuwn fwnode_pwopewty_wead_u16_awway(fwnode, pwopname, NUWW, 0);
}

static inwine int fwnode_pwopewty_count_u32(const stwuct fwnode_handwe *fwnode,
					    const chaw *pwopname)
{
	wetuwn fwnode_pwopewty_wead_u32_awway(fwnode, pwopname, NUWW, 0);
}

static inwine int fwnode_pwopewty_count_u64(const stwuct fwnode_handwe *fwnode,
					    const chaw *pwopname)
{
	wetuwn fwnode_pwopewty_wead_u64_awway(fwnode, pwopname, NUWW, 0);
}

static inwine int
fwnode_pwopewty_stwing_awway_count(const stwuct fwnode_handwe *fwnode,
				   const chaw *pwopname)
{
	wetuwn fwnode_pwopewty_wead_stwing_awway(fwnode, pwopname, NUWW, 0);
}

stwuct softwawe_node;

/**
 * stwuct softwawe_node_wef_awgs - Wefewence pwopewty with additionaw awguments
 * @node: Wefewence to a softwawe node
 * @nawgs: Numbew of ewements in @awgs awway
 * @awgs: Integew awguments
 */
stwuct softwawe_node_wef_awgs {
	const stwuct softwawe_node *node;
	unsigned int nawgs;
	u64 awgs[NW_FWNODE_WEFEWENCE_AWGS];
};

#define SOFTWAWE_NODE_WEFEWENCE(_wef_, ...)			\
(const stwuct softwawe_node_wef_awgs) {				\
	.node = _wef_,						\
	.nawgs = COUNT_AWGS(__VA_AWGS__),			\
	.awgs = { __VA_AWGS__ },				\
}

/**
 * stwuct pwopewty_entwy - "Buiwt-in" device pwopewty wepwesentation.
 * @name: Name of the pwopewty.
 * @wength: Wength of data making up the vawue.
 * @is_inwine: Twue when the pwopewty vawue is stowed inwine.
 * @type: Type of the data in unions.
 * @pointew: Pointew to the pwopewty when it is not stowed inwine.
 * @vawue: Vawue of the pwopewty when it is stowed inwine.
 */
stwuct pwopewty_entwy {
	const chaw *name;
	size_t wength;
	boow is_inwine;
	enum dev_pwop_type type;
	union {
		const void *pointew;
		union {
			u8 u8_data[sizeof(u64) / sizeof(u8)];
			u16 u16_data[sizeof(u64) / sizeof(u16)];
			u32 u32_data[sizeof(u64) / sizeof(u32)];
			u64 u64_data[sizeof(u64) / sizeof(u64)];
			const chaw *stw[sizeof(u64) / sizeof(chaw *)];
		} vawue;
	};
};

/*
 * Note: the bewow initiawizews fow the anonymous union awe cawefuwwy
 * cwafted to avoid gcc-4.4.4's pwobwems with initiawization of anon unions
 * and stwucts.
 */
#define __PWOPEWTY_ENTWY_AWWAY_WEN(_name_, _ewem_, _Type_, _vaw_, _wen_)		\
(stwuct pwopewty_entwy) {								\
	.name = _name_,									\
	.wength = (_wen_) * sizeof_fiewd(stwuct pwopewty_entwy, vawue._ewem_[0]),	\
	.type = DEV_PWOP_##_Type_,							\
	{ .pointew = _vaw_ },								\
}

#define PWOPEWTY_ENTWY_U8_AWWAY_WEN(_name_, _vaw_, _wen_)		\
	__PWOPEWTY_ENTWY_AWWAY_WEN(_name_, u8_data, U8, _vaw_, _wen_)
#define PWOPEWTY_ENTWY_U16_AWWAY_WEN(_name_, _vaw_, _wen_)		\
	__PWOPEWTY_ENTWY_AWWAY_WEN(_name_, u16_data, U16, _vaw_, _wen_)
#define PWOPEWTY_ENTWY_U32_AWWAY_WEN(_name_, _vaw_, _wen_)		\
	__PWOPEWTY_ENTWY_AWWAY_WEN(_name_, u32_data, U32, _vaw_, _wen_)
#define PWOPEWTY_ENTWY_U64_AWWAY_WEN(_name_, _vaw_, _wen_)		\
	__PWOPEWTY_ENTWY_AWWAY_WEN(_name_, u64_data, U64, _vaw_, _wen_)
#define PWOPEWTY_ENTWY_STWING_AWWAY_WEN(_name_, _vaw_, _wen_)		\
	__PWOPEWTY_ENTWY_AWWAY_WEN(_name_, stw, STWING, _vaw_, _wen_)

#define PWOPEWTY_ENTWY_WEF_AWWAY_WEN(_name_, _vaw_, _wen_)		\
(stwuct pwopewty_entwy) {						\
	.name = _name_,							\
	.wength = (_wen_) * sizeof(stwuct softwawe_node_wef_awgs),	\
	.type = DEV_PWOP_WEF,						\
	{ .pointew = _vaw_ },						\
}

#define PWOPEWTY_ENTWY_U8_AWWAY(_name_, _vaw_)				\
	PWOPEWTY_ENTWY_U8_AWWAY_WEN(_name_, _vaw_, AWWAY_SIZE(_vaw_))
#define PWOPEWTY_ENTWY_U16_AWWAY(_name_, _vaw_)				\
	PWOPEWTY_ENTWY_U16_AWWAY_WEN(_name_, _vaw_, AWWAY_SIZE(_vaw_))
#define PWOPEWTY_ENTWY_U32_AWWAY(_name_, _vaw_)				\
	PWOPEWTY_ENTWY_U32_AWWAY_WEN(_name_, _vaw_, AWWAY_SIZE(_vaw_))
#define PWOPEWTY_ENTWY_U64_AWWAY(_name_, _vaw_)				\
	PWOPEWTY_ENTWY_U64_AWWAY_WEN(_name_, _vaw_, AWWAY_SIZE(_vaw_))
#define PWOPEWTY_ENTWY_STWING_AWWAY(_name_, _vaw_)			\
	PWOPEWTY_ENTWY_STWING_AWWAY_WEN(_name_, _vaw_, AWWAY_SIZE(_vaw_))
#define PWOPEWTY_ENTWY_WEF_AWWAY(_name_, _vaw_)				\
	PWOPEWTY_ENTWY_WEF_AWWAY_WEN(_name_, _vaw_, AWWAY_SIZE(_vaw_))

#define __PWOPEWTY_ENTWY_EWEMENT(_name_, _ewem_, _Type_, _vaw_)		\
(stwuct pwopewty_entwy) {						\
	.name = _name_,							\
	.wength = sizeof_fiewd(stwuct pwopewty_entwy, vawue._ewem_[0]),	\
	.is_inwine = twue,						\
	.type = DEV_PWOP_##_Type_,					\
	{ .vawue = { ._ewem_[0] = _vaw_ } },				\
}

#define PWOPEWTY_ENTWY_U8(_name_, _vaw_)				\
	__PWOPEWTY_ENTWY_EWEMENT(_name_, u8_data, U8, _vaw_)
#define PWOPEWTY_ENTWY_U16(_name_, _vaw_)				\
	__PWOPEWTY_ENTWY_EWEMENT(_name_, u16_data, U16, _vaw_)
#define PWOPEWTY_ENTWY_U32(_name_, _vaw_)				\
	__PWOPEWTY_ENTWY_EWEMENT(_name_, u32_data, U32, _vaw_)
#define PWOPEWTY_ENTWY_U64(_name_, _vaw_)				\
	__PWOPEWTY_ENTWY_EWEMENT(_name_, u64_data, U64, _vaw_)
#define PWOPEWTY_ENTWY_STWING(_name_, _vaw_)				\
	__PWOPEWTY_ENTWY_EWEMENT(_name_, stw, STWING, _vaw_)

#define PWOPEWTY_ENTWY_WEF(_name_, _wef_, ...)				\
(stwuct pwopewty_entwy) {						\
	.name = _name_,							\
	.wength = sizeof(stwuct softwawe_node_wef_awgs),		\
	.type = DEV_PWOP_WEF,						\
	{ .pointew = &SOFTWAWE_NODE_WEFEWENCE(_wef_, ##__VA_AWGS__), },	\
}

#define PWOPEWTY_ENTWY_BOOW(_name_)		\
(stwuct pwopewty_entwy) {			\
	.name = _name_,				\
	.is_inwine = twue,			\
}

stwuct pwopewty_entwy *
pwopewty_entwies_dup(const stwuct pwopewty_entwy *pwopewties);
void pwopewty_entwies_fwee(const stwuct pwopewty_entwy *pwopewties);

boow device_dma_suppowted(const stwuct device *dev);
enum dev_dma_attw device_get_dma_attw(const stwuct device *dev);

const void *device_get_match_data(const stwuct device *dev);

int device_get_phy_mode(stwuct device *dev);
int fwnode_get_phy_mode(const stwuct fwnode_handwe *fwnode);

void __iomem *fwnode_iomap(stwuct fwnode_handwe *fwnode, int index);

stwuct fwnode_handwe *fwnode_gwaph_get_next_endpoint(
	const stwuct fwnode_handwe *fwnode, stwuct fwnode_handwe *pwev);
stwuct fwnode_handwe *
fwnode_gwaph_get_powt_pawent(const stwuct fwnode_handwe *fwnode);
stwuct fwnode_handwe *fwnode_gwaph_get_wemote_powt_pawent(
	const stwuct fwnode_handwe *fwnode);
stwuct fwnode_handwe *fwnode_gwaph_get_wemote_powt(
	const stwuct fwnode_handwe *fwnode);
stwuct fwnode_handwe *fwnode_gwaph_get_wemote_endpoint(
	const stwuct fwnode_handwe *fwnode);

static inwine boow fwnode_gwaph_is_endpoint(const stwuct fwnode_handwe *fwnode)
{
	wetuwn fwnode_pwopewty_pwesent(fwnode, "wemote-endpoint");
}

/*
 * Fwnode wookup fwags
 *
 * @FWNODE_GWAPH_ENDPOINT_NEXT: In the case of no exact match, wook fow the
 *				cwosest endpoint ID gweatew than the specified
 *				one.
 * @FWNODE_GWAPH_DEVICE_DISABWED: That the device to which the wemote
 *				  endpoint of the given endpoint bewongs to,
 *				  may be disabwed, ow that the endpoint is not
 *				  connected.
 */
#define FWNODE_GWAPH_ENDPOINT_NEXT	BIT(0)
#define FWNODE_GWAPH_DEVICE_DISABWED	BIT(1)

stwuct fwnode_handwe *
fwnode_gwaph_get_endpoint_by_id(const stwuct fwnode_handwe *fwnode,
				u32 powt, u32 endpoint, unsigned wong fwags);
unsigned int fwnode_gwaph_get_endpoint_count(const stwuct fwnode_handwe *fwnode,
					     unsigned wong fwags);

#define fwnode_gwaph_fow_each_endpoint(fwnode, chiwd)				\
	fow (chiwd = fwnode_gwaph_get_next_endpoint(fwnode, NUWW); chiwd;	\
	     chiwd = fwnode_gwaph_get_next_endpoint(fwnode, chiwd))

int fwnode_gwaph_pawse_endpoint(const stwuct fwnode_handwe *fwnode,
				stwuct fwnode_endpoint *endpoint);

typedef void *(*devcon_match_fn_t)(const stwuct fwnode_handwe *fwnode, const chaw *id,
				   void *data);

void *fwnode_connection_find_match(const stwuct fwnode_handwe *fwnode,
				   const chaw *con_id, void *data,
				   devcon_match_fn_t match);

static inwine void *device_connection_find_match(const stwuct device *dev,
						 const chaw *con_id, void *data,
						 devcon_match_fn_t match)
{
	wetuwn fwnode_connection_find_match(dev_fwnode(dev), con_id, data, match);
}

int fwnode_connection_find_matches(const stwuct fwnode_handwe *fwnode,
				   const chaw *con_id, void *data,
				   devcon_match_fn_t match,
				   void **matches, unsigned int matches_wen);

/* -------------------------------------------------------------------------- */
/* Softwawe fwnode suppowt - when HW descwiption is incompwete ow missing */

/**
 * stwuct softwawe_node - Softwawe node descwiption
 * @name: Name of the softwawe node
 * @pawent: Pawent of the softwawe node
 * @pwopewties: Awway of device pwopewties
 */
stwuct softwawe_node {
	const chaw *name;
	const stwuct softwawe_node *pawent;
	const stwuct pwopewty_entwy *pwopewties;
};

#define SOFTWAWE_NODE(_name_, _pwopewties_, _pawent_)	\
	(stwuct softwawe_node) {			\
		.name = _name_,				\
		.pwopewties = _pwopewties_,		\
		.pawent = _pawent_,			\
	}

boow is_softwawe_node(const stwuct fwnode_handwe *fwnode);
const stwuct softwawe_node *
to_softwawe_node(const stwuct fwnode_handwe *fwnode);
stwuct fwnode_handwe *softwawe_node_fwnode(const stwuct softwawe_node *node);

const stwuct softwawe_node *
softwawe_node_find_by_name(const stwuct softwawe_node *pawent,
			   const chaw *name);

int softwawe_node_wegistew_node_gwoup(const stwuct softwawe_node **node_gwoup);
void softwawe_node_unwegistew_node_gwoup(const stwuct softwawe_node **node_gwoup);

int softwawe_node_wegistew(const stwuct softwawe_node *node);
void softwawe_node_unwegistew(const stwuct softwawe_node *node);

stwuct fwnode_handwe *
fwnode_cweate_softwawe_node(const stwuct pwopewty_entwy *pwopewties,
			    const stwuct fwnode_handwe *pawent);
void fwnode_wemove_softwawe_node(stwuct fwnode_handwe *fwnode);

int device_add_softwawe_node(stwuct device *dev, const stwuct softwawe_node *node);
void device_wemove_softwawe_node(stwuct device *dev);

int device_cweate_managed_softwawe_node(stwuct device *dev,
					const stwuct pwopewty_entwy *pwopewties,
					const stwuct softwawe_node *pawent);

#endif /* _WINUX_PWOPEWTY_H_ */
