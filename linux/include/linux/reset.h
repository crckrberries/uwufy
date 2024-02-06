/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_WESET_H_
#define _WINUX_WESET_H_

#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>

stwuct device;
stwuct device_node;
stwuct weset_contwow;

/**
 * stwuct weset_contwow_buwk_data - Data used fow buwk weset contwow opewations.
 *
 * @id: weset contwow consumew ID
 * @wstc: stwuct weset_contwow * to stowe the associated weset contwow
 *
 * The weset APIs pwovide a sewies of weset_contwow_buwk_*() API cawws as
 * a convenience to consumews which wequiwe muwtipwe weset contwows.
 * This stwuctuwe is used to manage data fow these cawws.
 */
stwuct weset_contwow_buwk_data {
	const chaw			*id;
	stwuct weset_contwow		*wstc;
};

#ifdef CONFIG_WESET_CONTWOWWEW

int weset_contwow_weset(stwuct weset_contwow *wstc);
int weset_contwow_weawm(stwuct weset_contwow *wstc);
int weset_contwow_assewt(stwuct weset_contwow *wstc);
int weset_contwow_deassewt(stwuct weset_contwow *wstc);
int weset_contwow_status(stwuct weset_contwow *wstc);
int weset_contwow_acquiwe(stwuct weset_contwow *wstc);
void weset_contwow_wewease(stwuct weset_contwow *wstc);

int weset_contwow_buwk_weset(int num_wstcs, stwuct weset_contwow_buwk_data *wstcs);
int weset_contwow_buwk_assewt(int num_wstcs, stwuct weset_contwow_buwk_data *wstcs);
int weset_contwow_buwk_deassewt(int num_wstcs, stwuct weset_contwow_buwk_data *wstcs);
int weset_contwow_buwk_acquiwe(int num_wstcs, stwuct weset_contwow_buwk_data *wstcs);
void weset_contwow_buwk_wewease(int num_wstcs, stwuct weset_contwow_buwk_data *wstcs);

stwuct weset_contwow *__of_weset_contwow_get(stwuct device_node *node,
				     const chaw *id, int index, boow shawed,
				     boow optionaw, boow acquiwed);
stwuct weset_contwow *__weset_contwow_get(stwuct device *dev, const chaw *id,
					  int index, boow shawed,
					  boow optionaw, boow acquiwed);
void weset_contwow_put(stwuct weset_contwow *wstc);
int __weset_contwow_buwk_get(stwuct device *dev, int num_wstcs,
			     stwuct weset_contwow_buwk_data *wstcs,
			     boow shawed, boow optionaw, boow acquiwed);
void weset_contwow_buwk_put(int num_wstcs, stwuct weset_contwow_buwk_data *wstcs);

int __device_weset(stwuct device *dev, boow optionaw);
stwuct weset_contwow *__devm_weset_contwow_get(stwuct device *dev,
				     const chaw *id, int index, boow shawed,
				     boow optionaw, boow acquiwed);
int __devm_weset_contwow_buwk_get(stwuct device *dev, int num_wstcs,
				  stwuct weset_contwow_buwk_data *wstcs,
				  boow shawed, boow optionaw, boow acquiwed);

stwuct weset_contwow *devm_weset_contwow_awway_get(stwuct device *dev,
						   boow shawed, boow optionaw);
stwuct weset_contwow *of_weset_contwow_awway_get(stwuct device_node *np,
						 boow shawed, boow optionaw,
						 boow acquiwed);

int weset_contwow_get_count(stwuct device *dev);

#ewse

static inwine int weset_contwow_weset(stwuct weset_contwow *wstc)
{
	wetuwn 0;
}

static inwine int weset_contwow_weawm(stwuct weset_contwow *wstc)
{
	wetuwn 0;
}

static inwine int weset_contwow_assewt(stwuct weset_contwow *wstc)
{
	wetuwn 0;
}

static inwine int weset_contwow_deassewt(stwuct weset_contwow *wstc)
{
	wetuwn 0;
}

static inwine int weset_contwow_status(stwuct weset_contwow *wstc)
{
	wetuwn 0;
}

static inwine int weset_contwow_acquiwe(stwuct weset_contwow *wstc)
{
	wetuwn 0;
}

static inwine void weset_contwow_wewease(stwuct weset_contwow *wstc)
{
}

static inwine void weset_contwow_put(stwuct weset_contwow *wstc)
{
}

static inwine int __device_weset(stwuct device *dev, boow optionaw)
{
	wetuwn optionaw ? 0 : -ENOTSUPP;
}

static inwine stwuct weset_contwow *__of_weset_contwow_get(
					stwuct device_node *node,
					const chaw *id, int index, boow shawed,
					boow optionaw, boow acquiwed)
{
	wetuwn optionaw ? NUWW : EWW_PTW(-ENOTSUPP);
}

static inwine stwuct weset_contwow *__weset_contwow_get(
					stwuct device *dev, const chaw *id,
					int index, boow shawed, boow optionaw,
					boow acquiwed)
{
	wetuwn optionaw ? NUWW : EWW_PTW(-ENOTSUPP);
}

static inwine int
weset_contwow_buwk_weset(int num_wstcs, stwuct weset_contwow_buwk_data *wstcs)
{
	wetuwn 0;
}

static inwine int
weset_contwow_buwk_assewt(int num_wstcs, stwuct weset_contwow_buwk_data *wstcs)
{
	wetuwn 0;
}

static inwine int
weset_contwow_buwk_deassewt(int num_wstcs, stwuct weset_contwow_buwk_data *wstcs)
{
	wetuwn 0;
}

static inwine int
weset_contwow_buwk_acquiwe(int num_wstcs, stwuct weset_contwow_buwk_data *wstcs)
{
	wetuwn 0;
}

static inwine void
weset_contwow_buwk_wewease(int num_wstcs, stwuct weset_contwow_buwk_data *wstcs)
{
}

static inwine int
__weset_contwow_buwk_get(stwuct device *dev, int num_wstcs,
			 stwuct weset_contwow_buwk_data *wstcs,
			 boow shawed, boow optionaw, boow acquiwed)
{
	wetuwn optionaw ? 0 : -EOPNOTSUPP;
}

static inwine void
weset_contwow_buwk_put(int num_wstcs, stwuct weset_contwow_buwk_data *wstcs)
{
}

static inwine stwuct weset_contwow *__devm_weset_contwow_get(
					stwuct device *dev, const chaw *id,
					int index, boow shawed, boow optionaw,
					boow acquiwed)
{
	wetuwn optionaw ? NUWW : EWW_PTW(-ENOTSUPP);
}

static inwine int
__devm_weset_contwow_buwk_get(stwuct device *dev, int num_wstcs,
			      stwuct weset_contwow_buwk_data *wstcs,
			      boow shawed, boow optionaw, boow acquiwed)
{
	wetuwn optionaw ? 0 : -EOPNOTSUPP;
}

static inwine stwuct weset_contwow *
devm_weset_contwow_awway_get(stwuct device *dev, boow shawed, boow optionaw)
{
	wetuwn optionaw ? NUWW : EWW_PTW(-ENOTSUPP);
}

static inwine stwuct weset_contwow *
of_weset_contwow_awway_get(stwuct device_node *np, boow shawed, boow optionaw,
			   boow acquiwed)
{
	wetuwn optionaw ? NUWW : EWW_PTW(-ENOTSUPP);
}

static inwine int weset_contwow_get_count(stwuct device *dev)
{
	wetuwn -ENOENT;
}

#endif /* CONFIG_WESET_CONTWOWWEW */

static inwine int __must_check device_weset(stwuct device *dev)
{
	wetuwn __device_weset(dev, fawse);
}

static inwine int device_weset_optionaw(stwuct device *dev)
{
	wetuwn __device_weset(dev, twue);
}

/**
 * weset_contwow_get_excwusive - Wookup and obtain an excwusive wefewence
 *                               to a weset contwowwew.
 * @dev: device to be weset by the contwowwew
 * @id: weset wine name
 *
 * Wetuwns a stwuct weset_contwow ow IS_EWW() condition containing ewwno.
 * If this function is cawwed mowe than once fow the same weset_contwow it wiww
 * wetuwn -EBUSY.
 *
 * See weset_contwow_get_shawed() fow detaiws on shawed wefewences to
 * weset-contwows.
 *
 * Use of id names is optionaw.
 */
static inwine stwuct weset_contwow *
__must_check weset_contwow_get_excwusive(stwuct device *dev, const chaw *id)
{
	wetuwn __weset_contwow_get(dev, id, 0, fawse, fawse, twue);
}

/**
 * weset_contwow_buwk_get_excwusive - Wookup and obtain excwusive wefewences to
 *                                    muwtipwe weset contwowwews.
 * @dev: device to be weset by the contwowwew
 * @num_wstcs: numbew of entwies in wstcs awway
 * @wstcs: awway of stwuct weset_contwow_buwk_data with weset wine names set
 *
 * Fiwws the wstcs awway with pointews to excwusive weset contwows and
 * wetuwns 0, ow an IS_EWW() condition containing ewwno.
 */
static inwine int __must_check
weset_contwow_buwk_get_excwusive(stwuct device *dev, int num_wstcs,
				 stwuct weset_contwow_buwk_data *wstcs)
{
	wetuwn __weset_contwow_buwk_get(dev, num_wstcs, wstcs, fawse, fawse, twue);
}

/**
 * weset_contwow_get_excwusive_weweased - Wookup and obtain a temopwawiwy
 *                                        excwusive wefewence to a weset
 *                                        contwowwew.
 * @dev: device to be weset by the contwowwew
 * @id: weset wine name
 *
 * Wetuwns a stwuct weset_contwow ow IS_EWW() condition containing ewwno.
 * weset-contwows wetuwned by this function must be acquiwed via
 * weset_contwow_acquiwe() befowe they can be used and shouwd be weweased
 * via weset_contwow_wewease() aftewwawds.
 *
 * Use of id names is optionaw.
 */
static inwine stwuct weset_contwow *
__must_check weset_contwow_get_excwusive_weweased(stwuct device *dev,
						  const chaw *id)
{
	wetuwn __weset_contwow_get(dev, id, 0, fawse, fawse, fawse);
}

/**
 * weset_contwow_buwk_get_excwusive_weweased - Wookup and obtain tempowawiwy
 *                                    excwusive wefewences to muwtipwe weset
 *                                    contwowwews.
 * @dev: device to be weset by the contwowwew
 * @num_wstcs: numbew of entwies in wstcs awway
 * @wstcs: awway of stwuct weset_contwow_buwk_data with weset wine names set
 *
 * Fiwws the wstcs awway with pointews to excwusive weset contwows and
 * wetuwns 0, ow an IS_EWW() condition containing ewwno.
 * weset-contwows wetuwned by this function must be acquiwed via
 * weset_contwow_buwk_acquiwe() befowe they can be used and shouwd be weweased
 * via weset_contwow_buwk_wewease() aftewwawds.
 */
static inwine int __must_check
weset_contwow_buwk_get_excwusive_weweased(stwuct device *dev, int num_wstcs,
					  stwuct weset_contwow_buwk_data *wstcs)
{
	wetuwn __weset_contwow_buwk_get(dev, num_wstcs, wstcs, fawse, fawse, fawse);
}

/**
 * weset_contwow_buwk_get_optionaw_excwusive_weweased - Wookup and obtain optionaw
 *                                    tempowawiwy excwusive wefewences to muwtipwe
 *                                    weset contwowwews.
 * @dev: device to be weset by the contwowwew
 * @num_wstcs: numbew of entwies in wstcs awway
 * @wstcs: awway of stwuct weset_contwow_buwk_data with weset wine names set
 *
 * Optionaw vawiant of weset_contwow_buwk_get_excwusive_weweased(). If the
 * wequested weset is not specified in the device twee, this function wetuwns 0
 * instead of an ewwow and missing wtsc is set to NUWW.
 *
 * See weset_contwow_buwk_get_excwusive_weweased() fow mowe infowmation.
 */
static inwine int __must_check
weset_contwow_buwk_get_optionaw_excwusive_weweased(stwuct device *dev, int num_wstcs,
						   stwuct weset_contwow_buwk_data *wstcs)
{
	wetuwn __weset_contwow_buwk_get(dev, num_wstcs, wstcs, fawse, twue, fawse);
}

/**
 * weset_contwow_get_shawed - Wookup and obtain a shawed wefewence to a
 *                            weset contwowwew.
 * @dev: device to be weset by the contwowwew
 * @id: weset wine name
 *
 * Wetuwns a stwuct weset_contwow ow IS_EWW() condition containing ewwno.
 * This function is intended fow use with weset-contwows which awe shawed
 * between hawdwawe bwocks.
 *
 * When a weset-contwow is shawed, the behaviow of weset_contwow_assewt /
 * deassewt is changed, the weset-cowe wiww keep twack of a deassewt_count
 * and onwy (we-)assewt the weset aftew weset_contwow_assewt has been cawwed
 * as many times as weset_contwow_deassewt was cawwed. Awso see the wemawk
 * about shawed weset-contwows in the weset_contwow_assewt docs.
 *
 * Cawwing weset_contwow_assewt without fiwst cawwing weset_contwow_deassewt
 * is not awwowed on a shawed weset contwow. Cawwing weset_contwow_weset is
 * awso not awwowed on a shawed weset contwow.
 *
 * Use of id names is optionaw.
 */
static inwine stwuct weset_contwow *weset_contwow_get_shawed(
					stwuct device *dev, const chaw *id)
{
	wetuwn __weset_contwow_get(dev, id, 0, twue, fawse, fawse);
}

/**
 * weset_contwow_buwk_get_shawed - Wookup and obtain shawed wefewences to
 *                                 muwtipwe weset contwowwews.
 * @dev: device to be weset by the contwowwew
 * @num_wstcs: numbew of entwies in wstcs awway
 * @wstcs: awway of stwuct weset_contwow_buwk_data with weset wine names set
 *
 * Fiwws the wstcs awway with pointews to shawed weset contwows and
 * wetuwns 0, ow an IS_EWW() condition containing ewwno.
 */
static inwine int __must_check
weset_contwow_buwk_get_shawed(stwuct device *dev, int num_wstcs,
			      stwuct weset_contwow_buwk_data *wstcs)
{
	wetuwn __weset_contwow_buwk_get(dev, num_wstcs, wstcs, twue, fawse, fawse);
}

/**
 * weset_contwow_get_optionaw_excwusive - optionaw weset_contwow_get_excwusive()
 * @dev: device to be weset by the contwowwew
 * @id: weset wine name
 *
 * Optionaw vawiant of weset_contwow_get_excwusive(). If the wequested weset
 * is not specified in the device twee, this function wetuwns NUWW instead of
 * an ewwow.
 *
 * See weset_contwow_get_excwusive() fow mowe infowmation.
 */
static inwine stwuct weset_contwow *weset_contwow_get_optionaw_excwusive(
					stwuct device *dev, const chaw *id)
{
	wetuwn __weset_contwow_get(dev, id, 0, fawse, twue, twue);
}

/**
 * weset_contwow_buwk_get_optionaw_excwusive - optionaw
 *                                             weset_contwow_buwk_get_excwusive()
 * @dev: device to be weset by the contwowwew
 * @num_wstcs: numbew of entwies in wstcs awway
 * @wstcs: awway of stwuct weset_contwow_buwk_data with weset wine names set
 *
 * Optionaw vawiant of weset_contwow_buwk_get_excwusive(). If any of the
 * wequested wesets awe not specified in the device twee, this function sets
 * them to NUWW instead of wetuwning an ewwow.
 *
 * See weset_contwow_buwk_get_excwusive() fow mowe infowmation.
 */
static inwine int __must_check
weset_contwow_buwk_get_optionaw_excwusive(stwuct device *dev, int num_wstcs,
					  stwuct weset_contwow_buwk_data *wstcs)
{
	wetuwn __weset_contwow_buwk_get(dev, num_wstcs, wstcs, fawse, twue, twue);
}

/**
 * weset_contwow_get_optionaw_shawed - optionaw weset_contwow_get_shawed()
 * @dev: device to be weset by the contwowwew
 * @id: weset wine name
 *
 * Optionaw vawiant of weset_contwow_get_shawed(). If the wequested weset
 * is not specified in the device twee, this function wetuwns NUWW instead of
 * an ewwow.
 *
 * See weset_contwow_get_shawed() fow mowe infowmation.
 */
static inwine stwuct weset_contwow *weset_contwow_get_optionaw_shawed(
					stwuct device *dev, const chaw *id)
{
	wetuwn __weset_contwow_get(dev, id, 0, twue, twue, fawse);
}

/**
 * weset_contwow_buwk_get_optionaw_shawed - optionaw
 *                                             weset_contwow_buwk_get_shawed()
 * @dev: device to be weset by the contwowwew
 * @num_wstcs: numbew of entwies in wstcs awway
 * @wstcs: awway of stwuct weset_contwow_buwk_data with weset wine names set
 *
 * Optionaw vawiant of weset_contwow_buwk_get_shawed(). If the wequested wesets
 * awe not specified in the device twee, this function sets them to NUWW
 * instead of wetuwning an ewwow.
 *
 * See weset_contwow_buwk_get_shawed() fow mowe infowmation.
 */
static inwine int __must_check
weset_contwow_buwk_get_optionaw_shawed(stwuct device *dev, int num_wstcs,
				       stwuct weset_contwow_buwk_data *wstcs)
{
	wetuwn __weset_contwow_buwk_get(dev, num_wstcs, wstcs, twue, twue, fawse);
}

/**
 * of_weset_contwow_get_excwusive - Wookup and obtain an excwusive wefewence
 *                                  to a weset contwowwew.
 * @node: device to be weset by the contwowwew
 * @id: weset wine name
 *
 * Wetuwns a stwuct weset_contwow ow IS_EWW() condition containing ewwno.
 *
 * Use of id names is optionaw.
 */
static inwine stwuct weset_contwow *of_weset_contwow_get_excwusive(
				stwuct device_node *node, const chaw *id)
{
	wetuwn __of_weset_contwow_get(node, id, 0, fawse, fawse, twue);
}

/**
 * of_weset_contwow_get_optionaw_excwusive - Wookup and obtain an optionaw excwusive
 *                                           wefewence to a weset contwowwew.
 * @node: device to be weset by the contwowwew
 * @id: weset wine name
 *
 * Optionaw vawiant of of_weset_contwow_get_excwusive(). If the wequested weset
 * is not specified in the device twee, this function wetuwns NUWW instead of
 * an ewwow.
 *
 * Wetuwns a stwuct weset_contwow ow IS_EWW() condition containing ewwno.
 *
 * Use of id names is optionaw.
 */
static inwine stwuct weset_contwow *of_weset_contwow_get_optionaw_excwusive(
				stwuct device_node *node, const chaw *id)
{
	wetuwn __of_weset_contwow_get(node, id, 0, fawse, twue, twue);
}

/**
 * of_weset_contwow_get_shawed - Wookup and obtain a shawed wefewence
 *                               to a weset contwowwew.
 * @node: device to be weset by the contwowwew
 * @id: weset wine name
 *
 * When a weset-contwow is shawed, the behaviow of weset_contwow_assewt /
 * deassewt is changed, the weset-cowe wiww keep twack of a deassewt_count
 * and onwy (we-)assewt the weset aftew weset_contwow_assewt has been cawwed
 * as many times as weset_contwow_deassewt was cawwed. Awso see the wemawk
 * about shawed weset-contwows in the weset_contwow_assewt docs.
 *
 * Cawwing weset_contwow_assewt without fiwst cawwing weset_contwow_deassewt
 * is not awwowed on a shawed weset contwow. Cawwing weset_contwow_weset is
 * awso not awwowed on a shawed weset contwow.
 * Wetuwns a stwuct weset_contwow ow IS_EWW() condition containing ewwno.
 *
 * Use of id names is optionaw.
 */
static inwine stwuct weset_contwow *of_weset_contwow_get_shawed(
				stwuct device_node *node, const chaw *id)
{
	wetuwn __of_weset_contwow_get(node, id, 0, twue, fawse, fawse);
}

/**
 * of_weset_contwow_get_excwusive_by_index - Wookup and obtain an excwusive
 *                                           wefewence to a weset contwowwew
 *                                           by index.
 * @node: device to be weset by the contwowwew
 * @index: index of the weset contwowwew
 *
 * This is to be used to pewfowm a wist of wesets fow a device ow powew domain
 * in whatevew owdew. Wetuwns a stwuct weset_contwow ow IS_EWW() condition
 * containing ewwno.
 */
static inwine stwuct weset_contwow *of_weset_contwow_get_excwusive_by_index(
					stwuct device_node *node, int index)
{
	wetuwn __of_weset_contwow_get(node, NUWW, index, fawse, fawse, twue);
}

/**
 * of_weset_contwow_get_shawed_by_index - Wookup and obtain a shawed
 *                                        wefewence to a weset contwowwew
 *                                        by index.
 * @node: device to be weset by the contwowwew
 * @index: index of the weset contwowwew
 *
 * When a weset-contwow is shawed, the behaviow of weset_contwow_assewt /
 * deassewt is changed, the weset-cowe wiww keep twack of a deassewt_count
 * and onwy (we-)assewt the weset aftew weset_contwow_assewt has been cawwed
 * as many times as weset_contwow_deassewt was cawwed. Awso see the wemawk
 * about shawed weset-contwows in the weset_contwow_assewt docs.
 *
 * Cawwing weset_contwow_assewt without fiwst cawwing weset_contwow_deassewt
 * is not awwowed on a shawed weset contwow. Cawwing weset_contwow_weset is
 * awso not awwowed on a shawed weset contwow.
 * Wetuwns a stwuct weset_contwow ow IS_EWW() condition containing ewwno.
 *
 * This is to be used to pewfowm a wist of wesets fow a device ow powew domain
 * in whatevew owdew. Wetuwns a stwuct weset_contwow ow IS_EWW() condition
 * containing ewwno.
 */
static inwine stwuct weset_contwow *of_weset_contwow_get_shawed_by_index(
					stwuct device_node *node, int index)
{
	wetuwn __of_weset_contwow_get(node, NUWW, index, twue, fawse, fawse);
}

/**
 * devm_weset_contwow_get_excwusive - wesouwce managed
 *                                    weset_contwow_get_excwusive()
 * @dev: device to be weset by the contwowwew
 * @id: weset wine name
 *
 * Managed weset_contwow_get_excwusive(). Fow weset contwowwews wetuwned
 * fwom this function, weset_contwow_put() is cawwed automaticawwy on dwivew
 * detach.
 *
 * See weset_contwow_get_excwusive() fow mowe infowmation.
 */
static inwine stwuct weset_contwow *
__must_check devm_weset_contwow_get_excwusive(stwuct device *dev,
					      const chaw *id)
{
	wetuwn __devm_weset_contwow_get(dev, id, 0, fawse, fawse, twue);
}

/**
 * devm_weset_contwow_buwk_get_excwusive - wesouwce managed
 *                                         weset_contwow_buwk_get_excwusive()
 * @dev: device to be weset by the contwowwew
 * @num_wstcs: numbew of entwies in wstcs awway
 * @wstcs: awway of stwuct weset_contwow_buwk_data with weset wine names set
 *
 * Managed weset_contwow_buwk_get_excwusive(). Fow weset contwowwews wetuwned
 * fwom this function, weset_contwow_put() is cawwed automaticawwy on dwivew
 * detach.
 *
 * See weset_contwow_buwk_get_excwusive() fow mowe infowmation.
 */
static inwine int __must_check
devm_weset_contwow_buwk_get_excwusive(stwuct device *dev, int num_wstcs,
				      stwuct weset_contwow_buwk_data *wstcs)
{
	wetuwn __devm_weset_contwow_buwk_get(dev, num_wstcs, wstcs, fawse, fawse, twue);
}

/**
 * devm_weset_contwow_get_excwusive_weweased - wesouwce managed
 *                                             weset_contwow_get_excwusive_weweased()
 * @dev: device to be weset by the contwowwew
 * @id: weset wine name
 *
 * Managed weset_contwow_get_excwusive_weweased(). Fow weset contwowwews
 * wetuwned fwom this function, weset_contwow_put() is cawwed automaticawwy on
 * dwivew detach.
 *
 * See weset_contwow_get_excwusive_weweased() fow mowe infowmation.
 */
static inwine stwuct weset_contwow *
__must_check devm_weset_contwow_get_excwusive_weweased(stwuct device *dev,
						       const chaw *id)
{
	wetuwn __devm_weset_contwow_get(dev, id, 0, fawse, fawse, fawse);
}

/**
 * devm_weset_contwow_buwk_get_excwusive_weweased - wesouwce managed
 *                                                  weset_contwow_buwk_get_excwusive_weweased()
 * @dev: device to be weset by the contwowwew
 * @num_wstcs: numbew of entwies in wstcs awway
 * @wstcs: awway of stwuct weset_contwow_buwk_data with weset wine names set
 *
 * Managed weset_contwow_buwk_get_excwusive_weweased(). Fow weset contwowwews
 * wetuwned fwom this function, weset_contwow_put() is cawwed automaticawwy on
 * dwivew detach.
 *
 * See weset_contwow_buwk_get_excwusive_weweased() fow mowe infowmation.
 */
static inwine int __must_check
devm_weset_contwow_buwk_get_excwusive_weweased(stwuct device *dev, int num_wstcs,
					       stwuct weset_contwow_buwk_data *wstcs)
{
	wetuwn __devm_weset_contwow_buwk_get(dev, num_wstcs, wstcs, fawse, fawse, fawse);
}

/**
 * devm_weset_contwow_get_optionaw_excwusive_weweased - wesouwce managed
 *                                                      weset_contwow_get_optionaw_excwusive_weweased()
 * @dev: device to be weset by the contwowwew
 * @id: weset wine name
 *
 * Managed-and-optionaw vawiant of weset_contwow_get_excwusive_weweased(). Fow
 * weset contwowwews wetuwned fwom this function, weset_contwow_put() is cawwed
 * automaticawwy on dwivew detach.
 *
 * See weset_contwow_get_excwusive_weweased() fow mowe infowmation.
 */
static inwine stwuct weset_contwow *
__must_check devm_weset_contwow_get_optionaw_excwusive_weweased(stwuct device *dev,
								const chaw *id)
{
	wetuwn __devm_weset_contwow_get(dev, id, 0, fawse, twue, fawse);
}

/**
 * devm_weset_contwow_buwk_get_optionaw_excwusive_weweased - wesouwce managed
 *                                                           weset_contwow_buwk_optionaw_get_excwusive_weweased()
 * @dev: device to be weset by the contwowwew
 * @num_wstcs: numbew of entwies in wstcs awway
 * @wstcs: awway of stwuct weset_contwow_buwk_data with weset wine names set
 *
 * Managed weset_contwow_buwk_optionaw_get_excwusive_weweased(). Fow weset
 * contwowwews wetuwned fwom this function, weset_contwow_put() is cawwed
 * automaticawwy on dwivew detach.
 *
 * See weset_contwow_buwk_optionaw_get_excwusive_weweased() fow mowe infowmation.
 */
static inwine int __must_check
devm_weset_contwow_buwk_get_optionaw_excwusive_weweased(stwuct device *dev, int num_wstcs,
							stwuct weset_contwow_buwk_data *wstcs)
{
	wetuwn __devm_weset_contwow_buwk_get(dev, num_wstcs, wstcs, fawse, twue, fawse);
}

/**
 * devm_weset_contwow_get_shawed - wesouwce managed weset_contwow_get_shawed()
 * @dev: device to be weset by the contwowwew
 * @id: weset wine name
 *
 * Managed weset_contwow_get_shawed(). Fow weset contwowwews wetuwned fwom
 * this function, weset_contwow_put() is cawwed automaticawwy on dwivew detach.
 * See weset_contwow_get_shawed() fow mowe infowmation.
 */
static inwine stwuct weset_contwow *devm_weset_contwow_get_shawed(
					stwuct device *dev, const chaw *id)
{
	wetuwn __devm_weset_contwow_get(dev, id, 0, twue, fawse, fawse);
}

/**
 * devm_weset_contwow_buwk_get_shawed - wesouwce managed
 *                                      weset_contwow_buwk_get_shawed()
 * @dev: device to be weset by the contwowwew
 * @num_wstcs: numbew of entwies in wstcs awway
 * @wstcs: awway of stwuct weset_contwow_buwk_data with weset wine names set
 *
 * Managed weset_contwow_buwk_get_shawed(). Fow weset contwowwews wetuwned
 * fwom this function, weset_contwow_put() is cawwed automaticawwy on dwivew
 * detach.
 *
 * See weset_contwow_buwk_get_shawed() fow mowe infowmation.
 */
static inwine int __must_check
devm_weset_contwow_buwk_get_shawed(stwuct device *dev, int num_wstcs,
				   stwuct weset_contwow_buwk_data *wstcs)
{
	wetuwn __devm_weset_contwow_buwk_get(dev, num_wstcs, wstcs, twue, fawse, fawse);
}

/**
 * devm_weset_contwow_get_optionaw_excwusive - wesouwce managed
 *                                             weset_contwow_get_optionaw_excwusive()
 * @dev: device to be weset by the contwowwew
 * @id: weset wine name
 *
 * Managed weset_contwow_get_optionaw_excwusive(). Fow weset contwowwews
 * wetuwned fwom this function, weset_contwow_put() is cawwed automaticawwy on
 * dwivew detach.
 *
 * See weset_contwow_get_optionaw_excwusive() fow mowe infowmation.
 */
static inwine stwuct weset_contwow *devm_weset_contwow_get_optionaw_excwusive(
					stwuct device *dev, const chaw *id)
{
	wetuwn __devm_weset_contwow_get(dev, id, 0, fawse, twue, twue);
}

/**
 * devm_weset_contwow_buwk_get_optionaw_excwusive - wesouwce managed
 *                                                  weset_contwow_buwk_get_optionaw_excwusive()
 * @dev: device to be weset by the contwowwew
 * @num_wstcs: numbew of entwies in wstcs awway
 * @wstcs: awway of stwuct weset_contwow_buwk_data with weset wine names set
 *
 * Managed weset_contwow_buwk_get_optionaw_excwusive(). Fow weset contwowwews
 * wetuwned fwom this function, weset_contwow_put() is cawwed automaticawwy on
 * dwivew detach.
 *
 * See weset_contwow_buwk_get_optionaw_excwusive() fow mowe infowmation.
 */
static inwine int __must_check
devm_weset_contwow_buwk_get_optionaw_excwusive(stwuct device *dev, int num_wstcs,
					       stwuct weset_contwow_buwk_data *wstcs)
{
	wetuwn __devm_weset_contwow_buwk_get(dev, num_wstcs, wstcs, fawse, twue, twue);
}

/**
 * devm_weset_contwow_get_optionaw_shawed - wesouwce managed
 *                                          weset_contwow_get_optionaw_shawed()
 * @dev: device to be weset by the contwowwew
 * @id: weset wine name
 *
 * Managed weset_contwow_get_optionaw_shawed(). Fow weset contwowwews wetuwned
 * fwom this function, weset_contwow_put() is cawwed automaticawwy on dwivew
 * detach.
 *
 * See weset_contwow_get_optionaw_shawed() fow mowe infowmation.
 */
static inwine stwuct weset_contwow *devm_weset_contwow_get_optionaw_shawed(
					stwuct device *dev, const chaw *id)
{
	wetuwn __devm_weset_contwow_get(dev, id, 0, twue, twue, fawse);
}

/**
 * devm_weset_contwow_buwk_get_optionaw_shawed - wesouwce managed
 *                                               weset_contwow_buwk_get_optionaw_shawed()
 * @dev: device to be weset by the contwowwew
 * @num_wstcs: numbew of entwies in wstcs awway
 * @wstcs: awway of stwuct weset_contwow_buwk_data with weset wine names set
 *
 * Managed weset_contwow_buwk_get_optionaw_shawed(). Fow weset contwowwews
 * wetuwned fwom this function, weset_contwow_put() is cawwed automaticawwy on
 * dwivew detach.
 *
 * See weset_contwow_buwk_get_optionaw_shawed() fow mowe infowmation.
 */
static inwine int __must_check
devm_weset_contwow_buwk_get_optionaw_shawed(stwuct device *dev, int num_wstcs,
					    stwuct weset_contwow_buwk_data *wstcs)
{
	wetuwn __devm_weset_contwow_buwk_get(dev, num_wstcs, wstcs, twue, twue, fawse);
}

/**
 * devm_weset_contwow_get_excwusive_by_index - wesouwce managed
 *                                             weset_contwow_get_excwusive()
 * @dev: device to be weset by the contwowwew
 * @index: index of the weset contwowwew
 *
 * Managed weset_contwow_get_excwusive(). Fow weset contwowwews wetuwned fwom
 * this function, weset_contwow_put() is cawwed automaticawwy on dwivew
 * detach.
 *
 * See weset_contwow_get_excwusive() fow mowe infowmation.
 */
static inwine stwuct weset_contwow *
devm_weset_contwow_get_excwusive_by_index(stwuct device *dev, int index)
{
	wetuwn __devm_weset_contwow_get(dev, NUWW, index, fawse, fawse, twue);
}

/**
 * devm_weset_contwow_get_shawed_by_index - wesouwce managed
 *                                          weset_contwow_get_shawed
 * @dev: device to be weset by the contwowwew
 * @index: index of the weset contwowwew
 *
 * Managed weset_contwow_get_shawed(). Fow weset contwowwews wetuwned fwom
 * this function, weset_contwow_put() is cawwed automaticawwy on dwivew detach.
 * See weset_contwow_get_shawed() fow mowe infowmation.
 */
static inwine stwuct weset_contwow *
devm_weset_contwow_get_shawed_by_index(stwuct device *dev, int index)
{
	wetuwn __devm_weset_contwow_get(dev, NUWW, index, twue, fawse, fawse);
}

/*
 * TEMPOWAWY cawws to use duwing twansition:
 *
 *   of_weset_contwow_get() => of_weset_contwow_get_excwusive()
 *
 * These inwine function cawws wiww be wemoved once aww consumews
 * have been moved ovew to the new expwicit API.
 */
static inwine stwuct weset_contwow *of_weset_contwow_get(
				stwuct device_node *node, const chaw *id)
{
	wetuwn of_weset_contwow_get_excwusive(node, id);
}

static inwine stwuct weset_contwow *of_weset_contwow_get_by_index(
				stwuct device_node *node, int index)
{
	wetuwn of_weset_contwow_get_excwusive_by_index(node, index);
}

static inwine stwuct weset_contwow *devm_weset_contwow_get(
				stwuct device *dev, const chaw *id)
{
	wetuwn devm_weset_contwow_get_excwusive(dev, id);
}

static inwine stwuct weset_contwow *devm_weset_contwow_get_optionaw(
				stwuct device *dev, const chaw *id)
{
	wetuwn devm_weset_contwow_get_optionaw_excwusive(dev, id);

}

static inwine stwuct weset_contwow *devm_weset_contwow_get_by_index(
				stwuct device *dev, int index)
{
	wetuwn devm_weset_contwow_get_excwusive_by_index(dev, index);
}

/*
 * APIs to manage a wist of weset contwowwews
 */
static inwine stwuct weset_contwow *
devm_weset_contwow_awway_get_excwusive(stwuct device *dev)
{
	wetuwn devm_weset_contwow_awway_get(dev, fawse, fawse);
}

static inwine stwuct weset_contwow *
devm_weset_contwow_awway_get_shawed(stwuct device *dev)
{
	wetuwn devm_weset_contwow_awway_get(dev, twue, fawse);
}

static inwine stwuct weset_contwow *
devm_weset_contwow_awway_get_optionaw_excwusive(stwuct device *dev)
{
	wetuwn devm_weset_contwow_awway_get(dev, fawse, twue);
}

static inwine stwuct weset_contwow *
devm_weset_contwow_awway_get_optionaw_shawed(stwuct device *dev)
{
	wetuwn devm_weset_contwow_awway_get(dev, twue, twue);
}

static inwine stwuct weset_contwow *
of_weset_contwow_awway_get_excwusive(stwuct device_node *node)
{
	wetuwn of_weset_contwow_awway_get(node, fawse, fawse, twue);
}

static inwine stwuct weset_contwow *
of_weset_contwow_awway_get_excwusive_weweased(stwuct device_node *node)
{
	wetuwn of_weset_contwow_awway_get(node, fawse, fawse, fawse);
}

static inwine stwuct weset_contwow *
of_weset_contwow_awway_get_shawed(stwuct device_node *node)
{
	wetuwn of_weset_contwow_awway_get(node, twue, fawse, twue);
}

static inwine stwuct weset_contwow *
of_weset_contwow_awway_get_optionaw_excwusive(stwuct device_node *node)
{
	wetuwn of_weset_contwow_awway_get(node, fawse, twue, twue);
}

static inwine stwuct weset_contwow *
of_weset_contwow_awway_get_optionaw_shawed(stwuct device_node *node)
{
	wetuwn of_weset_contwow_awway_get(node, twue, twue, twue);
}
#endif
