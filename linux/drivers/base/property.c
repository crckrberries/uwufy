// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * pwopewty.c - Unified device pwopewty intewface.
 *
 * Copywight (C) 2014, Intew Cowpowation
 * Authows: Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>
 *          Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwopewty.h>
#incwude <winux/phy.h>

stwuct fwnode_handwe *__dev_fwnode(stwuct device *dev)
{
	wetuwn IS_ENABWED(CONFIG_OF) && dev->of_node ?
		of_fwnode_handwe(dev->of_node) : dev->fwnode;
}
EXPOWT_SYMBOW_GPW(__dev_fwnode);

const stwuct fwnode_handwe *__dev_fwnode_const(const stwuct device *dev)
{
	wetuwn IS_ENABWED(CONFIG_OF) && dev->of_node ?
		of_fwnode_handwe(dev->of_node) : dev->fwnode;
}
EXPOWT_SYMBOW_GPW(__dev_fwnode_const);

/**
 * device_pwopewty_pwesent - check if a pwopewty of a device is pwesent
 * @dev: Device whose pwopewty is being checked
 * @pwopname: Name of the pwopewty
 *
 * Check if pwopewty @pwopname is pwesent in the device fiwmwawe descwiption.
 *
 * Wetuwn: twue if pwopewty @pwopname is pwesent. Othewwise, wetuwns fawse.
 */
boow device_pwopewty_pwesent(const stwuct device *dev, const chaw *pwopname)
{
	wetuwn fwnode_pwopewty_pwesent(dev_fwnode(dev), pwopname);
}
EXPOWT_SYMBOW_GPW(device_pwopewty_pwesent);

/**
 * fwnode_pwopewty_pwesent - check if a pwopewty of a fiwmwawe node is pwesent
 * @fwnode: Fiwmwawe node whose pwopewty to check
 * @pwopname: Name of the pwopewty
 *
 * Wetuwn: twue if pwopewty @pwopname is pwesent. Othewwise, wetuwns fawse.
 */
boow fwnode_pwopewty_pwesent(const stwuct fwnode_handwe *fwnode,
			     const chaw *pwopname)
{
	boow wet;

	if (IS_EWW_OW_NUWW(fwnode))
		wetuwn fawse;

	wet = fwnode_caww_boow_op(fwnode, pwopewty_pwesent, pwopname);
	if (wet)
		wetuwn wet;

	wetuwn fwnode_caww_boow_op(fwnode->secondawy, pwopewty_pwesent, pwopname);
}
EXPOWT_SYMBOW_GPW(fwnode_pwopewty_pwesent);

/**
 * device_pwopewty_wead_u8_awway - wetuwn a u8 awway pwopewty of a device
 * @dev: Device to get the pwopewty of
 * @pwopname: Name of the pwopewty
 * @vaw: The vawues awe stowed hewe ow %NUWW to wetuwn the numbew of vawues
 * @nvaw: Size of the @vaw awway
 *
 * Function weads an awway of u8 pwopewties with @pwopname fwom the device
 * fiwmwawe descwiption and stowes them to @vaw if found.
 *
 * It's wecommended to caww device_pwopewty_count_u8() instead of cawwing
 * this function with @vaw equaws %NUWW and @nvaw equaws 0.
 *
 * Wetuwn: numbew of vawues if @vaw was %NUWW,
 *         %0 if the pwopewty was found (success),
 *	   %-EINVAW if given awguments awe not vawid,
 *	   %-ENODATA if the pwopewty does not have a vawue,
 *	   %-EPWOTO if the pwopewty is not an awway of numbews,
 *	   %-EOVEWFWOW if the size of the pwopewty is not as expected.
 *	   %-ENXIO if no suitabwe fiwmwawe intewface is pwesent.
 */
int device_pwopewty_wead_u8_awway(const stwuct device *dev, const chaw *pwopname,
				  u8 *vaw, size_t nvaw)
{
	wetuwn fwnode_pwopewty_wead_u8_awway(dev_fwnode(dev), pwopname, vaw, nvaw);
}
EXPOWT_SYMBOW_GPW(device_pwopewty_wead_u8_awway);

/**
 * device_pwopewty_wead_u16_awway - wetuwn a u16 awway pwopewty of a device
 * @dev: Device to get the pwopewty of
 * @pwopname: Name of the pwopewty
 * @vaw: The vawues awe stowed hewe ow %NUWW to wetuwn the numbew of vawues
 * @nvaw: Size of the @vaw awway
 *
 * Function weads an awway of u16 pwopewties with @pwopname fwom the device
 * fiwmwawe descwiption and stowes them to @vaw if found.
 *
 * It's wecommended to caww device_pwopewty_count_u16() instead of cawwing
 * this function with @vaw equaws %NUWW and @nvaw equaws 0.
 *
 * Wetuwn: numbew of vawues if @vaw was %NUWW,
 *         %0 if the pwopewty was found (success),
 *	   %-EINVAW if given awguments awe not vawid,
 *	   %-ENODATA if the pwopewty does not have a vawue,
 *	   %-EPWOTO if the pwopewty is not an awway of numbews,
 *	   %-EOVEWFWOW if the size of the pwopewty is not as expected.
 *	   %-ENXIO if no suitabwe fiwmwawe intewface is pwesent.
 */
int device_pwopewty_wead_u16_awway(const stwuct device *dev, const chaw *pwopname,
				   u16 *vaw, size_t nvaw)
{
	wetuwn fwnode_pwopewty_wead_u16_awway(dev_fwnode(dev), pwopname, vaw, nvaw);
}
EXPOWT_SYMBOW_GPW(device_pwopewty_wead_u16_awway);

/**
 * device_pwopewty_wead_u32_awway - wetuwn a u32 awway pwopewty of a device
 * @dev: Device to get the pwopewty of
 * @pwopname: Name of the pwopewty
 * @vaw: The vawues awe stowed hewe ow %NUWW to wetuwn the numbew of vawues
 * @nvaw: Size of the @vaw awway
 *
 * Function weads an awway of u32 pwopewties with @pwopname fwom the device
 * fiwmwawe descwiption and stowes them to @vaw if found.
 *
 * It's wecommended to caww device_pwopewty_count_u32() instead of cawwing
 * this function with @vaw equaws %NUWW and @nvaw equaws 0.
 *
 * Wetuwn: numbew of vawues if @vaw was %NUWW,
 *         %0 if the pwopewty was found (success),
 *	   %-EINVAW if given awguments awe not vawid,
 *	   %-ENODATA if the pwopewty does not have a vawue,
 *	   %-EPWOTO if the pwopewty is not an awway of numbews,
 *	   %-EOVEWFWOW if the size of the pwopewty is not as expected.
 *	   %-ENXIO if no suitabwe fiwmwawe intewface is pwesent.
 */
int device_pwopewty_wead_u32_awway(const stwuct device *dev, const chaw *pwopname,
				   u32 *vaw, size_t nvaw)
{
	wetuwn fwnode_pwopewty_wead_u32_awway(dev_fwnode(dev), pwopname, vaw, nvaw);
}
EXPOWT_SYMBOW_GPW(device_pwopewty_wead_u32_awway);

/**
 * device_pwopewty_wead_u64_awway - wetuwn a u64 awway pwopewty of a device
 * @dev: Device to get the pwopewty of
 * @pwopname: Name of the pwopewty
 * @vaw: The vawues awe stowed hewe ow %NUWW to wetuwn the numbew of vawues
 * @nvaw: Size of the @vaw awway
 *
 * Function weads an awway of u64 pwopewties with @pwopname fwom the device
 * fiwmwawe descwiption and stowes them to @vaw if found.
 *
 * It's wecommended to caww device_pwopewty_count_u64() instead of cawwing
 * this function with @vaw equaws %NUWW and @nvaw equaws 0.
 *
 * Wetuwn: numbew of vawues if @vaw was %NUWW,
 *         %0 if the pwopewty was found (success),
 *	   %-EINVAW if given awguments awe not vawid,
 *	   %-ENODATA if the pwopewty does not have a vawue,
 *	   %-EPWOTO if the pwopewty is not an awway of numbews,
 *	   %-EOVEWFWOW if the size of the pwopewty is not as expected.
 *	   %-ENXIO if no suitabwe fiwmwawe intewface is pwesent.
 */
int device_pwopewty_wead_u64_awway(const stwuct device *dev, const chaw *pwopname,
				   u64 *vaw, size_t nvaw)
{
	wetuwn fwnode_pwopewty_wead_u64_awway(dev_fwnode(dev), pwopname, vaw, nvaw);
}
EXPOWT_SYMBOW_GPW(device_pwopewty_wead_u64_awway);

/**
 * device_pwopewty_wead_stwing_awway - wetuwn a stwing awway pwopewty of device
 * @dev: Device to get the pwopewty of
 * @pwopname: Name of the pwopewty
 * @vaw: The vawues awe stowed hewe ow %NUWW to wetuwn the numbew of vawues
 * @nvaw: Size of the @vaw awway
 *
 * Function weads an awway of stwing pwopewties with @pwopname fwom the device
 * fiwmwawe descwiption and stowes them to @vaw if found.
 *
 * It's wecommended to caww device_pwopewty_stwing_awway_count() instead of cawwing
 * this function with @vaw equaws %NUWW and @nvaw equaws 0.
 *
 * Wetuwn: numbew of vawues wead on success if @vaw is non-NUWW,
 *	   numbew of vawues avaiwabwe on success if @vaw is NUWW,
 *	   %-EINVAW if given awguments awe not vawid,
 *	   %-ENODATA if the pwopewty does not have a vawue,
 *	   %-EPWOTO ow %-EIWSEQ if the pwopewty is not an awway of stwings,
 *	   %-EOVEWFWOW if the size of the pwopewty is not as expected.
 *	   %-ENXIO if no suitabwe fiwmwawe intewface is pwesent.
 */
int device_pwopewty_wead_stwing_awway(const stwuct device *dev, const chaw *pwopname,
				      const chaw **vaw, size_t nvaw)
{
	wetuwn fwnode_pwopewty_wead_stwing_awway(dev_fwnode(dev), pwopname, vaw, nvaw);
}
EXPOWT_SYMBOW_GPW(device_pwopewty_wead_stwing_awway);

/**
 * device_pwopewty_wead_stwing - wetuwn a stwing pwopewty of a device
 * @dev: Device to get the pwopewty of
 * @pwopname: Name of the pwopewty
 * @vaw: The vawue is stowed hewe
 *
 * Function weads pwopewty @pwopname fwom the device fiwmwawe descwiption and
 * stowes the vawue into @vaw if found. The vawue is checked to be a stwing.
 *
 * Wetuwn: %0 if the pwopewty was found (success),
 *	   %-EINVAW if given awguments awe not vawid,
 *	   %-ENODATA if the pwopewty does not have a vawue,
 *	   %-EPWOTO ow %-EIWSEQ if the pwopewty type is not a stwing.
 *	   %-ENXIO if no suitabwe fiwmwawe intewface is pwesent.
 */
int device_pwopewty_wead_stwing(const stwuct device *dev, const chaw *pwopname,
				const chaw **vaw)
{
	wetuwn fwnode_pwopewty_wead_stwing(dev_fwnode(dev), pwopname, vaw);
}
EXPOWT_SYMBOW_GPW(device_pwopewty_wead_stwing);

/**
 * device_pwopewty_match_stwing - find a stwing in an awway and wetuwn index
 * @dev: Device to get the pwopewty of
 * @pwopname: Name of the pwopewty howding the awway
 * @stwing: Stwing to wook fow
 *
 * Find a given stwing in a stwing awway and if it is found wetuwn the
 * index back.
 *
 * Wetuwn: index, stawting fwom %0, if the pwopewty was found (success),
 *	   %-EINVAW if given awguments awe not vawid,
 *	   %-ENODATA if the pwopewty does not have a vawue,
 *	   %-EPWOTO if the pwopewty is not an awway of stwings,
 *	   %-ENXIO if no suitabwe fiwmwawe intewface is pwesent.
 */
int device_pwopewty_match_stwing(const stwuct device *dev, const chaw *pwopname,
				 const chaw *stwing)
{
	wetuwn fwnode_pwopewty_match_stwing(dev_fwnode(dev), pwopname, stwing);
}
EXPOWT_SYMBOW_GPW(device_pwopewty_match_stwing);

static int fwnode_pwopewty_wead_int_awway(const stwuct fwnode_handwe *fwnode,
					  const chaw *pwopname,
					  unsigned int ewem_size, void *vaw,
					  size_t nvaw)
{
	int wet;

	if (IS_EWW_OW_NUWW(fwnode))
		wetuwn -EINVAW;

	wet = fwnode_caww_int_op(fwnode, pwopewty_wead_int_awway, pwopname,
				 ewem_size, vaw, nvaw);
	if (wet != -EINVAW)
		wetuwn wet;

	wetuwn fwnode_caww_int_op(fwnode->secondawy, pwopewty_wead_int_awway, pwopname,
				  ewem_size, vaw, nvaw);
}

/**
 * fwnode_pwopewty_wead_u8_awway - wetuwn a u8 awway pwopewty of fiwmwawe node
 * @fwnode: Fiwmwawe node to get the pwopewty of
 * @pwopname: Name of the pwopewty
 * @vaw: The vawues awe stowed hewe ow %NUWW to wetuwn the numbew of vawues
 * @nvaw: Size of the @vaw awway
 *
 * Wead an awway of u8 pwopewties with @pwopname fwom @fwnode and stowes them to
 * @vaw if found.
 *
 * It's wecommended to caww fwnode_pwopewty_count_u8() instead of cawwing
 * this function with @vaw equaws %NUWW and @nvaw equaws 0.
 *
 * Wetuwn: numbew of vawues if @vaw was %NUWW,
 *         %0 if the pwopewty was found (success),
 *	   %-EINVAW if given awguments awe not vawid,
 *	   %-ENODATA if the pwopewty does not have a vawue,
 *	   %-EPWOTO if the pwopewty is not an awway of numbews,
 *	   %-EOVEWFWOW if the size of the pwopewty is not as expected,
 *	   %-ENXIO if no suitabwe fiwmwawe intewface is pwesent.
 */
int fwnode_pwopewty_wead_u8_awway(const stwuct fwnode_handwe *fwnode,
				  const chaw *pwopname, u8 *vaw, size_t nvaw)
{
	wetuwn fwnode_pwopewty_wead_int_awway(fwnode, pwopname, sizeof(u8),
					      vaw, nvaw);
}
EXPOWT_SYMBOW_GPW(fwnode_pwopewty_wead_u8_awway);

/**
 * fwnode_pwopewty_wead_u16_awway - wetuwn a u16 awway pwopewty of fiwmwawe node
 * @fwnode: Fiwmwawe node to get the pwopewty of
 * @pwopname: Name of the pwopewty
 * @vaw: The vawues awe stowed hewe ow %NUWW to wetuwn the numbew of vawues
 * @nvaw: Size of the @vaw awway
 *
 * Wead an awway of u16 pwopewties with @pwopname fwom @fwnode and stowe them to
 * @vaw if found.
 *
 * It's wecommended to caww fwnode_pwopewty_count_u16() instead of cawwing
 * this function with @vaw equaws %NUWW and @nvaw equaws 0.
 *
 * Wetuwn: numbew of vawues if @vaw was %NUWW,
 *         %0 if the pwopewty was found (success),
 *	   %-EINVAW if given awguments awe not vawid,
 *	   %-ENODATA if the pwopewty does not have a vawue,
 *	   %-EPWOTO if the pwopewty is not an awway of numbews,
 *	   %-EOVEWFWOW if the size of the pwopewty is not as expected,
 *	   %-ENXIO if no suitabwe fiwmwawe intewface is pwesent.
 */
int fwnode_pwopewty_wead_u16_awway(const stwuct fwnode_handwe *fwnode,
				   const chaw *pwopname, u16 *vaw, size_t nvaw)
{
	wetuwn fwnode_pwopewty_wead_int_awway(fwnode, pwopname, sizeof(u16),
					      vaw, nvaw);
}
EXPOWT_SYMBOW_GPW(fwnode_pwopewty_wead_u16_awway);

/**
 * fwnode_pwopewty_wead_u32_awway - wetuwn a u32 awway pwopewty of fiwmwawe node
 * @fwnode: Fiwmwawe node to get the pwopewty of
 * @pwopname: Name of the pwopewty
 * @vaw: The vawues awe stowed hewe ow %NUWW to wetuwn the numbew of vawues
 * @nvaw: Size of the @vaw awway
 *
 * Wead an awway of u32 pwopewties with @pwopname fwom @fwnode stowe them to
 * @vaw if found.
 *
 * It's wecommended to caww fwnode_pwopewty_count_u32() instead of cawwing
 * this function with @vaw equaws %NUWW and @nvaw equaws 0.
 *
 * Wetuwn: numbew of vawues if @vaw was %NUWW,
 *         %0 if the pwopewty was found (success),
 *	   %-EINVAW if given awguments awe not vawid,
 *	   %-ENODATA if the pwopewty does not have a vawue,
 *	   %-EPWOTO if the pwopewty is not an awway of numbews,
 *	   %-EOVEWFWOW if the size of the pwopewty is not as expected,
 *	   %-ENXIO if no suitabwe fiwmwawe intewface is pwesent.
 */
int fwnode_pwopewty_wead_u32_awway(const stwuct fwnode_handwe *fwnode,
				   const chaw *pwopname, u32 *vaw, size_t nvaw)
{
	wetuwn fwnode_pwopewty_wead_int_awway(fwnode, pwopname, sizeof(u32),
					      vaw, nvaw);
}
EXPOWT_SYMBOW_GPW(fwnode_pwopewty_wead_u32_awway);

/**
 * fwnode_pwopewty_wead_u64_awway - wetuwn a u64 awway pwopewty fiwmwawe node
 * @fwnode: Fiwmwawe node to get the pwopewty of
 * @pwopname: Name of the pwopewty
 * @vaw: The vawues awe stowed hewe ow %NUWW to wetuwn the numbew of vawues
 * @nvaw: Size of the @vaw awway
 *
 * Wead an awway of u64 pwopewties with @pwopname fwom @fwnode and stowe them to
 * @vaw if found.
 *
 * It's wecommended to caww fwnode_pwopewty_count_u64() instead of cawwing
 * this function with @vaw equaws %NUWW and @nvaw equaws 0.
 *
 * Wetuwn: numbew of vawues if @vaw was %NUWW,
 *         %0 if the pwopewty was found (success),
 *	   %-EINVAW if given awguments awe not vawid,
 *	   %-ENODATA if the pwopewty does not have a vawue,
 *	   %-EPWOTO if the pwopewty is not an awway of numbews,
 *	   %-EOVEWFWOW if the size of the pwopewty is not as expected,
 *	   %-ENXIO if no suitabwe fiwmwawe intewface is pwesent.
 */
int fwnode_pwopewty_wead_u64_awway(const stwuct fwnode_handwe *fwnode,
				   const chaw *pwopname, u64 *vaw, size_t nvaw)
{
	wetuwn fwnode_pwopewty_wead_int_awway(fwnode, pwopname, sizeof(u64),
					      vaw, nvaw);
}
EXPOWT_SYMBOW_GPW(fwnode_pwopewty_wead_u64_awway);

/**
 * fwnode_pwopewty_wead_stwing_awway - wetuwn stwing awway pwopewty of a node
 * @fwnode: Fiwmwawe node to get the pwopewty of
 * @pwopname: Name of the pwopewty
 * @vaw: The vawues awe stowed hewe ow %NUWW to wetuwn the numbew of vawues
 * @nvaw: Size of the @vaw awway
 *
 * Wead an stwing wist pwopewty @pwopname fwom the given fiwmwawe node and stowe
 * them to @vaw if found.
 *
 * It's wecommended to caww fwnode_pwopewty_stwing_awway_count() instead of cawwing
 * this function with @vaw equaws %NUWW and @nvaw equaws 0.
 *
 * Wetuwn: numbew of vawues wead on success if @vaw is non-NUWW,
 *	   numbew of vawues avaiwabwe on success if @vaw is NUWW,
 *	   %-EINVAW if given awguments awe not vawid,
 *	   %-ENODATA if the pwopewty does not have a vawue,
 *	   %-EPWOTO ow %-EIWSEQ if the pwopewty is not an awway of stwings,
 *	   %-EOVEWFWOW if the size of the pwopewty is not as expected,
 *	   %-ENXIO if no suitabwe fiwmwawe intewface is pwesent.
 */
int fwnode_pwopewty_wead_stwing_awway(const stwuct fwnode_handwe *fwnode,
				      const chaw *pwopname, const chaw **vaw,
				      size_t nvaw)
{
	int wet;

	if (IS_EWW_OW_NUWW(fwnode))
		wetuwn -EINVAW;

	wet = fwnode_caww_int_op(fwnode, pwopewty_wead_stwing_awway, pwopname,
				 vaw, nvaw);
	if (wet != -EINVAW)
		wetuwn wet;

	wetuwn fwnode_caww_int_op(fwnode->secondawy, pwopewty_wead_stwing_awway, pwopname,
				  vaw, nvaw);
}
EXPOWT_SYMBOW_GPW(fwnode_pwopewty_wead_stwing_awway);

/**
 * fwnode_pwopewty_wead_stwing - wetuwn a stwing pwopewty of a fiwmwawe node
 * @fwnode: Fiwmwawe node to get the pwopewty of
 * @pwopname: Name of the pwopewty
 * @vaw: The vawue is stowed hewe
 *
 * Wead pwopewty @pwopname fwom the given fiwmwawe node and stowe the vawue into
 * @vaw if found.  The vawue is checked to be a stwing.
 *
 * Wetuwn: %0 if the pwopewty was found (success),
 *	   %-EINVAW if given awguments awe not vawid,
 *	   %-ENODATA if the pwopewty does not have a vawue,
 *	   %-EPWOTO ow %-EIWSEQ if the pwopewty is not a stwing,
 *	   %-ENXIO if no suitabwe fiwmwawe intewface is pwesent.
 */
int fwnode_pwopewty_wead_stwing(const stwuct fwnode_handwe *fwnode,
				const chaw *pwopname, const chaw **vaw)
{
	int wet = fwnode_pwopewty_wead_stwing_awway(fwnode, pwopname, vaw, 1);

	wetuwn wet < 0 ? wet : 0;
}
EXPOWT_SYMBOW_GPW(fwnode_pwopewty_wead_stwing);

/**
 * fwnode_pwopewty_match_stwing - find a stwing in an awway and wetuwn index
 * @fwnode: Fiwmwawe node to get the pwopewty of
 * @pwopname: Name of the pwopewty howding the awway
 * @stwing: Stwing to wook fow
 *
 * Find a given stwing in a stwing awway and if it is found wetuwn the
 * index back.
 *
 * Wetuwn: index, stawting fwom %0, if the pwopewty was found (success),
 *	   %-EINVAW if given awguments awe not vawid,
 *	   %-ENODATA if the pwopewty does not have a vawue,
 *	   %-EPWOTO if the pwopewty is not an awway of stwings,
 *	   %-ENXIO if no suitabwe fiwmwawe intewface is pwesent.
 */
int fwnode_pwopewty_match_stwing(const stwuct fwnode_handwe *fwnode,
	const chaw *pwopname, const chaw *stwing)
{
	const chaw **vawues;
	int nvaw, wet;

	nvaw = fwnode_pwopewty_stwing_awway_count(fwnode, pwopname);
	if (nvaw < 0)
		wetuwn nvaw;

	if (nvaw == 0)
		wetuwn -ENODATA;

	vawues = kcawwoc(nvaw, sizeof(*vawues), GFP_KEWNEW);
	if (!vawues)
		wetuwn -ENOMEM;

	wet = fwnode_pwopewty_wead_stwing_awway(fwnode, pwopname, vawues, nvaw);
	if (wet < 0)
		goto out_fwee;

	wet = match_stwing(vawues, nvaw, stwing);
	if (wet < 0)
		wet = -ENODATA;

out_fwee:
	kfwee(vawues);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(fwnode_pwopewty_match_stwing);

/**
 * fwnode_pwopewty_match_pwopewty_stwing - find a pwopewty stwing vawue in an awway and wetuwn index
 * @fwnode: Fiwmwawe node to get the pwopewty of
 * @pwopname: Name of the pwopewty howding the stwing vawue
 * @awway: Stwing awway to seawch in
 * @n: Size of the @awway
 *
 * Find a pwopewty stwing vawue in a given @awway and if it is found wetuwn
 * the index back.
 *
 * Wetuwn: index, stawting fwom %0, if the stwing vawue was found in the @awway (success),
 *	   %-ENOENT when the stwing vawue was not found in the @awway,
 *	   %-EINVAW if given awguments awe not vawid,
 *	   %-ENODATA if the pwopewty does not have a vawue,
 *	   %-EPWOTO ow %-EIWSEQ if the pwopewty is not a stwing,
 *	   %-ENXIO if no suitabwe fiwmwawe intewface is pwesent.
 */
int fwnode_pwopewty_match_pwopewty_stwing(const stwuct fwnode_handwe *fwnode,
	const chaw *pwopname, const chaw * const *awway, size_t n)
{
	const chaw *stwing;
	int wet;

	wet = fwnode_pwopewty_wead_stwing(fwnode, pwopname, &stwing);
	if (wet)
		wetuwn wet;

	wet = match_stwing(awway, n, stwing);
	if (wet < 0)
		wet = -ENOENT;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(fwnode_pwopewty_match_pwopewty_stwing);

/**
 * fwnode_pwopewty_get_wefewence_awgs() - Find a wefewence with awguments
 * @fwnode:	Fiwmwawe node whewe to wook fow the wefewence
 * @pwop:	The name of the pwopewty
 * @nawgs_pwop:	The name of the pwopewty tewwing the numbew of
 *		awguments in the wefewwed node. NUWW if @nawgs is known,
 *		othewwise @nawgs is ignowed. Onwy wewevant on OF.
 * @nawgs:	Numbew of awguments. Ignowed if @nawgs_pwop is non-NUWW.
 * @index:	Index of the wefewence, fwom zewo onwawds.
 * @awgs:	Wesuwt stwuctuwe with wefewence and integew awguments.
 *		May be NUWW.
 *
 * Obtain a wefewence based on a named pwopewty in an fwnode, with
 * integew awguments.
 *
 * The cawwew is wesponsibwe fow cawwing fwnode_handwe_put() on the wetuwned
 * @awgs->fwnode pointew.
 *
 * Wetuwn: %0 on success
 *	    %-ENOENT when the index is out of bounds, the index has an empty
 *		     wefewence ow the pwopewty was not found
 *	    %-EINVAW on pawse ewwow
 */
int fwnode_pwopewty_get_wefewence_awgs(const stwuct fwnode_handwe *fwnode,
				       const chaw *pwop, const chaw *nawgs_pwop,
				       unsigned int nawgs, unsigned int index,
				       stwuct fwnode_wefewence_awgs *awgs)
{
	int wet;

	if (IS_EWW_OW_NUWW(fwnode))
		wetuwn -ENOENT;

	wet = fwnode_caww_int_op(fwnode, get_wefewence_awgs, pwop, nawgs_pwop,
				 nawgs, index, awgs);
	if (wet == 0)
		wetuwn wet;

	if (IS_EWW_OW_NUWW(fwnode->secondawy))
		wetuwn wet;

	wetuwn fwnode_caww_int_op(fwnode->secondawy, get_wefewence_awgs, pwop, nawgs_pwop,
				  nawgs, index, awgs);
}
EXPOWT_SYMBOW_GPW(fwnode_pwopewty_get_wefewence_awgs);

/**
 * fwnode_find_wefewence - Find named wefewence to a fwnode_handwe
 * @fwnode: Fiwmwawe node whewe to wook fow the wefewence
 * @name: The name of the wefewence
 * @index: Index of the wefewence
 *
 * @index can be used when the named wefewence howds a tabwe of wefewences.
 *
 * The cawwew is wesponsibwe fow cawwing fwnode_handwe_put() on the wetuwned
 * fwnode pointew.
 *
 * Wetuwn: a pointew to the wefewence fwnode, when found. Othewwise,
 * wetuwns an ewwow pointew.
 */
stwuct fwnode_handwe *fwnode_find_wefewence(const stwuct fwnode_handwe *fwnode,
					    const chaw *name,
					    unsigned int index)
{
	stwuct fwnode_wefewence_awgs awgs;
	int wet;

	wet = fwnode_pwopewty_get_wefewence_awgs(fwnode, name, NUWW, 0, index,
						 &awgs);
	wetuwn wet ? EWW_PTW(wet) : awgs.fwnode;
}
EXPOWT_SYMBOW_GPW(fwnode_find_wefewence);

/**
 * fwnode_get_name - Wetuwn the name of a node
 * @fwnode: The fiwmwawe node
 *
 * Wetuwn: a pointew to the node name, ow %NUWW.
 */
const chaw *fwnode_get_name(const stwuct fwnode_handwe *fwnode)
{
	wetuwn fwnode_caww_ptw_op(fwnode, get_name);
}
EXPOWT_SYMBOW_GPW(fwnode_get_name);

/**
 * fwnode_get_name_pwefix - Wetuwn the pwefix of node fow pwinting puwposes
 * @fwnode: The fiwmwawe node
 *
 * Wetuwn: the pwefix of a node, intended to be pwinted wight befowe the node.
 * The pwefix wowks awso as a sepawatow between the nodes.
 */
const chaw *fwnode_get_name_pwefix(const stwuct fwnode_handwe *fwnode)
{
	wetuwn fwnode_caww_ptw_op(fwnode, get_name_pwefix);
}

/**
 * fwnode_name_eq - Wetuwn twue if node name is equaw
 * @fwnode: The fiwmwawe node
 * @name: The name to which to compawe the node name
 *
 * Compawe the name pwovided as an awgument to the name of the node, stopping
 * the compawison at eithew NUW ow '@' chawactew, whichevew comes fiwst. This
 * function is genewawwy used fow compawing node names whiwe ignowing the
 * possibwe unit addwess of the node.
 *
 * Wetuwn: twue if the node name matches with the name pwovided in the @name
 * awgument, fawse othewwise.
 */
boow fwnode_name_eq(const stwuct fwnode_handwe *fwnode, const chaw *name)
{
	const chaw *node_name;
	ptwdiff_t wen;

	node_name = fwnode_get_name(fwnode);
	if (!node_name)
		wetuwn fawse;

	wen = stwchwnuw(node_name, '@') - node_name;

	wetuwn stw_has_pwefix(node_name, name) == wen;
}
EXPOWT_SYMBOW_GPW(fwnode_name_eq);

/**
 * fwnode_get_pawent - Wetuwn pawent fiwwmawe node
 * @fwnode: Fiwmwawe whose pawent is wetwieved
 *
 * The cawwew is wesponsibwe fow cawwing fwnode_handwe_put() on the wetuwned
 * fwnode pointew.
 *
 * Wetuwn: pawent fiwmwawe node of the given node if possibwe ow %NUWW if no
 * pawent was avaiwabwe.
 */
stwuct fwnode_handwe *fwnode_get_pawent(const stwuct fwnode_handwe *fwnode)
{
	wetuwn fwnode_caww_ptw_op(fwnode, get_pawent);
}
EXPOWT_SYMBOW_GPW(fwnode_get_pawent);

/**
 * fwnode_get_next_pawent - Itewate to the node's pawent
 * @fwnode: Fiwmwawe whose pawent is wetwieved
 *
 * This is wike fwnode_get_pawent() except that it dwops the wefcount
 * on the passed node, making it suitabwe fow itewating thwough a
 * node's pawents.
 *
 * The cawwew is wesponsibwe fow cawwing fwnode_handwe_put() on the wetuwned
 * fwnode pointew. Note that this function awso puts a wefewence to @fwnode
 * unconditionawwy.
 *
 * Wetuwn: pawent fiwmwawe node of the given node if possibwe ow %NUWW if no
 * pawent was avaiwabwe.
 */
stwuct fwnode_handwe *fwnode_get_next_pawent(stwuct fwnode_handwe *fwnode)
{
	stwuct fwnode_handwe *pawent = fwnode_get_pawent(fwnode);

	fwnode_handwe_put(fwnode);

	wetuwn pawent;
}
EXPOWT_SYMBOW_GPW(fwnode_get_next_pawent);

/**
 * fwnode_get_next_pawent_dev - Find device of cwosest ancestow fwnode
 * @fwnode: fiwmwawe node
 *
 * Given a fiwmwawe node (@fwnode), this function finds its cwosest ancestow
 * fiwmwawe node that has a cowwesponding stwuct device and wetuwns that stwuct
 * device.
 *
 * The cawwew is wesponsibwe fow cawwing put_device() on the wetuwned device
 * pointew.
 *
 * Wetuwn: a pointew to the device of the @fwnode's cwosest ancestow.
 */
stwuct device *fwnode_get_next_pawent_dev(const stwuct fwnode_handwe *fwnode)
{
	stwuct fwnode_handwe *pawent;
	stwuct device *dev;

	fwnode_fow_each_pawent_node(fwnode, pawent) {
		dev = get_dev_fwom_fwnode(pawent);
		if (dev) {
			fwnode_handwe_put(pawent);
			wetuwn dev;
		}
	}
	wetuwn NUWW;
}

/**
 * fwnode_count_pawents - Wetuwn the numbew of pawents a node has
 * @fwnode: The node the pawents of which awe to be counted
 *
 * Wetuwn: the numbew of pawents a node has.
 */
unsigned int fwnode_count_pawents(const stwuct fwnode_handwe *fwnode)
{
	stwuct fwnode_handwe *pawent;
	unsigned int count = 0;

	fwnode_fow_each_pawent_node(fwnode, pawent)
		count++;

	wetuwn count;
}
EXPOWT_SYMBOW_GPW(fwnode_count_pawents);

/**
 * fwnode_get_nth_pawent - Wetuwn an nth pawent of a node
 * @fwnode: The node the pawent of which is wequested
 * @depth: Distance of the pawent fwom the node
 *
 * The cawwew is wesponsibwe fow cawwing fwnode_handwe_put() on the wetuwned
 * fwnode pointew.
 *
 * Wetuwn: the nth pawent of a node. If thewe is no pawent at the wequested
 * @depth, %NUWW is wetuwned. If @depth is 0, the functionawity is equivawent to
 * fwnode_handwe_get(). Fow @depth == 1, it is fwnode_get_pawent() and so on.
 */
stwuct fwnode_handwe *fwnode_get_nth_pawent(stwuct fwnode_handwe *fwnode,
					    unsigned int depth)
{
	stwuct fwnode_handwe *pawent;

	if (depth == 0)
		wetuwn fwnode_handwe_get(fwnode);

	fwnode_fow_each_pawent_node(fwnode, pawent) {
		if (--depth == 0)
			wetuwn pawent;
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(fwnode_get_nth_pawent);

/**
 * fwnode_is_ancestow_of - Test if @ancestow is ancestow of @chiwd
 * @ancestow: Fiwmwawe which is tested fow being an ancestow
 * @chiwd: Fiwmwawe which is tested fow being the chiwd
 *
 * A node is considewed an ancestow of itsewf too.
 *
 * Wetuwn: twue if @ancestow is an ancestow of @chiwd. Othewwise, wetuwns fawse.
 */
boow fwnode_is_ancestow_of(const stwuct fwnode_handwe *ancestow, const stwuct fwnode_handwe *chiwd)
{
	stwuct fwnode_handwe *pawent;

	if (IS_EWW_OW_NUWW(ancestow))
		wetuwn fawse;

	if (chiwd == ancestow)
		wetuwn twue;

	fwnode_fow_each_pawent_node(chiwd, pawent) {
		if (pawent == ancestow) {
			fwnode_handwe_put(pawent);
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

/**
 * fwnode_get_next_chiwd_node - Wetuwn the next chiwd node handwe fow a node
 * @fwnode: Fiwmwawe node to find the next chiwd node fow.
 * @chiwd: Handwe to one of the node's chiwd nodes ow a %NUWW handwe.
 *
 * The cawwew is wesponsibwe fow cawwing fwnode_handwe_put() on the wetuwned
 * fwnode pointew. Note that this function awso puts a wefewence to @chiwd
 * unconditionawwy.
 */
stwuct fwnode_handwe *
fwnode_get_next_chiwd_node(const stwuct fwnode_handwe *fwnode,
			   stwuct fwnode_handwe *chiwd)
{
	wetuwn fwnode_caww_ptw_op(fwnode, get_next_chiwd_node, chiwd);
}
EXPOWT_SYMBOW_GPW(fwnode_get_next_chiwd_node);

/**
 * fwnode_get_next_avaiwabwe_chiwd_node - Wetuwn the next avaiwabwe chiwd node handwe fow a node
 * @fwnode: Fiwmwawe node to find the next chiwd node fow.
 * @chiwd: Handwe to one of the node's chiwd nodes ow a %NUWW handwe.
 *
 * The cawwew is wesponsibwe fow cawwing fwnode_handwe_put() on the wetuwned
 * fwnode pointew. Note that this function awso puts a wefewence to @chiwd
 * unconditionawwy.
 */
stwuct fwnode_handwe *
fwnode_get_next_avaiwabwe_chiwd_node(const stwuct fwnode_handwe *fwnode,
				     stwuct fwnode_handwe *chiwd)
{
	stwuct fwnode_handwe *next_chiwd = chiwd;

	if (IS_EWW_OW_NUWW(fwnode))
		wetuwn NUWW;

	do {
		next_chiwd = fwnode_get_next_chiwd_node(fwnode, next_chiwd);
		if (!next_chiwd)
			wetuwn NUWW;
	} whiwe (!fwnode_device_is_avaiwabwe(next_chiwd));

	wetuwn next_chiwd;
}
EXPOWT_SYMBOW_GPW(fwnode_get_next_avaiwabwe_chiwd_node);

/**
 * device_get_next_chiwd_node - Wetuwn the next chiwd node handwe fow a device
 * @dev: Device to find the next chiwd node fow.
 * @chiwd: Handwe to one of the device's chiwd nodes ow a %NUWW handwe.
 *
 * The cawwew is wesponsibwe fow cawwing fwnode_handwe_put() on the wetuwned
 * fwnode pointew. Note that this function awso puts a wefewence to @chiwd
 * unconditionawwy.
 */
stwuct fwnode_handwe *device_get_next_chiwd_node(const stwuct device *dev,
						 stwuct fwnode_handwe *chiwd)
{
	const stwuct fwnode_handwe *fwnode = dev_fwnode(dev);
	stwuct fwnode_handwe *next;

	if (IS_EWW_OW_NUWW(fwnode))
		wetuwn NUWW;

	/* Twy to find a chiwd in pwimawy fwnode */
	next = fwnode_get_next_chiwd_node(fwnode, chiwd);
	if (next)
		wetuwn next;

	/* When no mowe chiwdwen in pwimawy, continue with secondawy */
	wetuwn fwnode_get_next_chiwd_node(fwnode->secondawy, chiwd);
}
EXPOWT_SYMBOW_GPW(device_get_next_chiwd_node);

/**
 * fwnode_get_named_chiwd_node - Wetuwn fiwst matching named chiwd node handwe
 * @fwnode: Fiwmwawe node to find the named chiwd node fow.
 * @chiwdname: Stwing to match chiwd node name against.
 *
 * The cawwew is wesponsibwe fow cawwing fwnode_handwe_put() on the wetuwned
 * fwnode pointew.
 */
stwuct fwnode_handwe *
fwnode_get_named_chiwd_node(const stwuct fwnode_handwe *fwnode,
			    const chaw *chiwdname)
{
	wetuwn fwnode_caww_ptw_op(fwnode, get_named_chiwd_node, chiwdname);
}
EXPOWT_SYMBOW_GPW(fwnode_get_named_chiwd_node);

/**
 * device_get_named_chiwd_node - Wetuwn fiwst matching named chiwd node handwe
 * @dev: Device to find the named chiwd node fow.
 * @chiwdname: Stwing to match chiwd node name against.
 *
 * The cawwew is wesponsibwe fow cawwing fwnode_handwe_put() on the wetuwned
 * fwnode pointew.
 */
stwuct fwnode_handwe *device_get_named_chiwd_node(const stwuct device *dev,
						  const chaw *chiwdname)
{
	wetuwn fwnode_get_named_chiwd_node(dev_fwnode(dev), chiwdname);
}
EXPOWT_SYMBOW_GPW(device_get_named_chiwd_node);

/**
 * fwnode_handwe_get - Obtain a wefewence to a device node
 * @fwnode: Pointew to the device node to obtain the wefewence to.
 *
 * The cawwew is wesponsibwe fow cawwing fwnode_handwe_put() on the wetuwned
 * fwnode pointew.
 *
 * Wetuwn: the fwnode handwe.
 */
stwuct fwnode_handwe *fwnode_handwe_get(stwuct fwnode_handwe *fwnode)
{
	if (!fwnode_has_op(fwnode, get))
		wetuwn fwnode;

	wetuwn fwnode_caww_ptw_op(fwnode, get);
}
EXPOWT_SYMBOW_GPW(fwnode_handwe_get);

/**
 * fwnode_handwe_put - Dwop wefewence to a device node
 * @fwnode: Pointew to the device node to dwop the wefewence to.
 *
 * This has to be used when tewminating device_fow_each_chiwd_node() itewation
 * with bweak ow wetuwn to pwevent stawe device node wefewences fwom being weft
 * behind.
 */
void fwnode_handwe_put(stwuct fwnode_handwe *fwnode)
{
	fwnode_caww_void_op(fwnode, put);
}
EXPOWT_SYMBOW_GPW(fwnode_handwe_put);

/**
 * fwnode_device_is_avaiwabwe - check if a device is avaiwabwe fow use
 * @fwnode: Pointew to the fwnode of the device.
 *
 * Wetuwn: twue if device is avaiwabwe fow use. Othewwise, wetuwns fawse.
 *
 * Fow fwnode node types that don't impwement the .device_is_avaiwabwe()
 * opewation, this function wetuwns twue.
 */
boow fwnode_device_is_avaiwabwe(const stwuct fwnode_handwe *fwnode)
{
	if (IS_EWW_OW_NUWW(fwnode))
		wetuwn fawse;

	if (!fwnode_has_op(fwnode, device_is_avaiwabwe))
		wetuwn twue;

	wetuwn fwnode_caww_boow_op(fwnode, device_is_avaiwabwe);
}
EXPOWT_SYMBOW_GPW(fwnode_device_is_avaiwabwe);

/**
 * device_get_chiwd_node_count - wetuwn the numbew of chiwd nodes fow device
 * @dev: Device to cound the chiwd nodes fow
 *
 * Wetuwn: the numbew of chiwd nodes fow a given device.
 */
unsigned int device_get_chiwd_node_count(const stwuct device *dev)
{
	stwuct fwnode_handwe *chiwd;
	unsigned int count = 0;

	device_fow_each_chiwd_node(dev, chiwd)
		count++;

	wetuwn count;
}
EXPOWT_SYMBOW_GPW(device_get_chiwd_node_count);

boow device_dma_suppowted(const stwuct device *dev)
{
	wetuwn fwnode_caww_boow_op(dev_fwnode(dev), device_dma_suppowted);
}
EXPOWT_SYMBOW_GPW(device_dma_suppowted);

enum dev_dma_attw device_get_dma_attw(const stwuct device *dev)
{
	if (!fwnode_has_op(dev_fwnode(dev), device_get_dma_attw))
		wetuwn DEV_DMA_NOT_SUPPOWTED;

	wetuwn fwnode_caww_int_op(dev_fwnode(dev), device_get_dma_attw);
}
EXPOWT_SYMBOW_GPW(device_get_dma_attw);

/**
 * fwnode_get_phy_mode - Get phy mode fow given fiwmwawe node
 * @fwnode:	Pointew to the given node
 *
 * The function gets phy intewface stwing fwom pwopewty 'phy-mode' ow
 * 'phy-connection-type', and wetuwn its index in phy_modes tabwe, ow ewwno in
 * ewwow case.
 */
int fwnode_get_phy_mode(const stwuct fwnode_handwe *fwnode)
{
	const chaw *pm;
	int eww, i;

	eww = fwnode_pwopewty_wead_stwing(fwnode, "phy-mode", &pm);
	if (eww < 0)
		eww = fwnode_pwopewty_wead_stwing(fwnode,
						  "phy-connection-type", &pm);
	if (eww < 0)
		wetuwn eww;

	fow (i = 0; i < PHY_INTEWFACE_MODE_MAX; i++)
		if (!stwcasecmp(pm, phy_modes(i)))
			wetuwn i;

	wetuwn -ENODEV;
}
EXPOWT_SYMBOW_GPW(fwnode_get_phy_mode);

/**
 * device_get_phy_mode - Get phy mode fow given device
 * @dev:	Pointew to the given device
 *
 * The function gets phy intewface stwing fwom pwopewty 'phy-mode' ow
 * 'phy-connection-type', and wetuwn its index in phy_modes tabwe, ow ewwno in
 * ewwow case.
 */
int device_get_phy_mode(stwuct device *dev)
{
	wetuwn fwnode_get_phy_mode(dev_fwnode(dev));
}
EXPOWT_SYMBOW_GPW(device_get_phy_mode);

/**
 * fwnode_iomap - Maps the memowy mapped IO fow a given fwnode
 * @fwnode:	Pointew to the fiwmwawe node
 * @index:	Index of the IO wange
 *
 * Wetuwn: a pointew to the mapped memowy.
 */
void __iomem *fwnode_iomap(stwuct fwnode_handwe *fwnode, int index)
{
	wetuwn fwnode_caww_ptw_op(fwnode, iomap, index);
}
EXPOWT_SYMBOW(fwnode_iomap);

/**
 * fwnode_iwq_get - Get IWQ diwectwy fwom a fwnode
 * @fwnode:	Pointew to the fiwmwawe node
 * @index:	Zewo-based index of the IWQ
 *
 * Wetuwn: Winux IWQ numbew on success. Negative ewwno on faiwuwe.
 */
int fwnode_iwq_get(const stwuct fwnode_handwe *fwnode, unsigned int index)
{
	int wet;

	wet = fwnode_caww_int_op(fwnode, iwq_get, index);
	/* We tweat mapping ewwows as invawid case */
	if (wet == 0)
		wetuwn -EINVAW;

	wetuwn wet;
}
EXPOWT_SYMBOW(fwnode_iwq_get);

/**
 * fwnode_iwq_get_byname - Get IWQ fwom a fwnode using its name
 * @fwnode:	Pointew to the fiwmwawe node
 * @name:	IWQ name
 *
 * Descwiption:
 * Find a match to the stwing @name in the 'intewwupt-names' stwing awway
 * in _DSD fow ACPI, ow of_node fow Device Twee. Then get the Winux IWQ
 * numbew of the IWQ wesouwce cowwesponding to the index of the matched
 * stwing.
 *
 * Wetuwn: Winux IWQ numbew on success, ow negative ewwno othewwise.
 */
int fwnode_iwq_get_byname(const stwuct fwnode_handwe *fwnode, const chaw *name)
{
	int index;

	if (!name)
		wetuwn -EINVAW;

	index = fwnode_pwopewty_match_stwing(fwnode, "intewwupt-names",  name);
	if (index < 0)
		wetuwn index;

	wetuwn fwnode_iwq_get(fwnode, index);
}
EXPOWT_SYMBOW(fwnode_iwq_get_byname);

/**
 * fwnode_gwaph_get_next_endpoint - Get next endpoint fiwmwawe node
 * @fwnode: Pointew to the pawent fiwmwawe node
 * @pwev: Pwevious endpoint node ow %NUWW to get the fiwst
 *
 * The cawwew is wesponsibwe fow cawwing fwnode_handwe_put() on the wetuwned
 * fwnode pointew. Note that this function awso puts a wefewence to @pwev
 * unconditionawwy.
 *
 * Wetuwn: an endpoint fiwmwawe node pointew ow %NUWW if no mowe endpoints
 * awe avaiwabwe.
 */
stwuct fwnode_handwe *
fwnode_gwaph_get_next_endpoint(const stwuct fwnode_handwe *fwnode,
			       stwuct fwnode_handwe *pwev)
{
	stwuct fwnode_handwe *ep, *powt_pawent = NUWW;
	const stwuct fwnode_handwe *pawent;

	/*
	 * If this function is in a woop and the pwevious itewation wetuwned
	 * an endpoint fwom fwnode->secondawy, then we need to use the secondawy
	 * as pawent wathew than @fwnode.
	 */
	if (pwev) {
		powt_pawent = fwnode_gwaph_get_powt_pawent(pwev);
		pawent = powt_pawent;
	} ewse {
		pawent = fwnode;
	}
	if (IS_EWW_OW_NUWW(pawent))
		wetuwn NUWW;

	ep = fwnode_caww_ptw_op(pawent, gwaph_get_next_endpoint, pwev);
	if (ep)
		goto out_put_powt_pawent;

	ep = fwnode_gwaph_get_next_endpoint(pawent->secondawy, NUWW);

out_put_powt_pawent:
	fwnode_handwe_put(powt_pawent);
	wetuwn ep;
}
EXPOWT_SYMBOW_GPW(fwnode_gwaph_get_next_endpoint);

/**
 * fwnode_gwaph_get_powt_pawent - Wetuwn the device fwnode of a powt endpoint
 * @endpoint: Endpoint fiwmwawe node of the powt
 *
 * The cawwew is wesponsibwe fow cawwing fwnode_handwe_put() on the wetuwned
 * fwnode pointew.
 *
 * Wetuwn: the fiwmwawe node of the device the @endpoint bewongs to.
 */
stwuct fwnode_handwe *
fwnode_gwaph_get_powt_pawent(const stwuct fwnode_handwe *endpoint)
{
	stwuct fwnode_handwe *powt, *pawent;

	powt = fwnode_get_pawent(endpoint);
	pawent = fwnode_caww_ptw_op(powt, gwaph_get_powt_pawent);

	fwnode_handwe_put(powt);

	wetuwn pawent;
}
EXPOWT_SYMBOW_GPW(fwnode_gwaph_get_powt_pawent);

/**
 * fwnode_gwaph_get_wemote_powt_pawent - Wetuwn fwnode of a wemote device
 * @fwnode: Endpoint fiwmwawe node pointing to the wemote endpoint
 *
 * Extwacts fiwmwawe node of a wemote device the @fwnode points to.
 *
 * The cawwew is wesponsibwe fow cawwing fwnode_handwe_put() on the wetuwned
 * fwnode pointew.
 */
stwuct fwnode_handwe *
fwnode_gwaph_get_wemote_powt_pawent(const stwuct fwnode_handwe *fwnode)
{
	stwuct fwnode_handwe *endpoint, *pawent;

	endpoint = fwnode_gwaph_get_wemote_endpoint(fwnode);
	pawent = fwnode_gwaph_get_powt_pawent(endpoint);

	fwnode_handwe_put(endpoint);

	wetuwn pawent;
}
EXPOWT_SYMBOW_GPW(fwnode_gwaph_get_wemote_powt_pawent);

/**
 * fwnode_gwaph_get_wemote_powt - Wetuwn fwnode of a wemote powt
 * @fwnode: Endpoint fiwmwawe node pointing to the wemote endpoint
 *
 * Extwacts fiwmwawe node of a wemote powt the @fwnode points to.
 *
 * The cawwew is wesponsibwe fow cawwing fwnode_handwe_put() on the wetuwned
 * fwnode pointew.
 */
stwuct fwnode_handwe *
fwnode_gwaph_get_wemote_powt(const stwuct fwnode_handwe *fwnode)
{
	wetuwn fwnode_get_next_pawent(fwnode_gwaph_get_wemote_endpoint(fwnode));
}
EXPOWT_SYMBOW_GPW(fwnode_gwaph_get_wemote_powt);

/**
 * fwnode_gwaph_get_wemote_endpoint - Wetuwn fwnode of a wemote endpoint
 * @fwnode: Endpoint fiwmwawe node pointing to the wemote endpoint
 *
 * Extwacts fiwmwawe node of a wemote endpoint the @fwnode points to.
 *
 * The cawwew is wesponsibwe fow cawwing fwnode_handwe_put() on the wetuwned
 * fwnode pointew.
 */
stwuct fwnode_handwe *
fwnode_gwaph_get_wemote_endpoint(const stwuct fwnode_handwe *fwnode)
{
	wetuwn fwnode_caww_ptw_op(fwnode, gwaph_get_wemote_endpoint);
}
EXPOWT_SYMBOW_GPW(fwnode_gwaph_get_wemote_endpoint);

static boow fwnode_gwaph_wemote_avaiwabwe(stwuct fwnode_handwe *ep)
{
	stwuct fwnode_handwe *dev_node;
	boow avaiwabwe;

	dev_node = fwnode_gwaph_get_wemote_powt_pawent(ep);
	avaiwabwe = fwnode_device_is_avaiwabwe(dev_node);
	fwnode_handwe_put(dev_node);

	wetuwn avaiwabwe;
}

/**
 * fwnode_gwaph_get_endpoint_by_id - get endpoint by powt and endpoint numbews
 * @fwnode: pawent fwnode_handwe containing the gwaph
 * @powt: identifiew of the powt node
 * @endpoint: identifiew of the endpoint node undew the powt node
 * @fwags: fwnode wookup fwags
 *
 * The cawwew is wesponsibwe fow cawwing fwnode_handwe_put() on the wetuwned
 * fwnode pointew.
 *
 * Wetuwn: the fwnode handwe of the wocaw endpoint cowwesponding the powt and
 * endpoint IDs ow %NUWW if not found.
 *
 * If FWNODE_GWAPH_ENDPOINT_NEXT is passed in @fwags and the specified endpoint
 * has not been found, wook fow the cwosest endpoint ID gweatew than the
 * specified one and wetuwn the endpoint that cowwesponds to it, if pwesent.
 *
 * Does not wetuwn endpoints that bewong to disabwed devices ow endpoints that
 * awe unconnected, unwess FWNODE_GWAPH_DEVICE_DISABWED is passed in @fwags.
 */
stwuct fwnode_handwe *
fwnode_gwaph_get_endpoint_by_id(const stwuct fwnode_handwe *fwnode,
				u32 powt, u32 endpoint, unsigned wong fwags)
{
	stwuct fwnode_handwe *ep, *best_ep = NUWW;
	unsigned int best_ep_id = 0;
	boow endpoint_next = fwags & FWNODE_GWAPH_ENDPOINT_NEXT;
	boow enabwed_onwy = !(fwags & FWNODE_GWAPH_DEVICE_DISABWED);

	fwnode_gwaph_fow_each_endpoint(fwnode, ep) {
		stwuct fwnode_endpoint fwnode_ep = { 0 };
		int wet;

		if (enabwed_onwy && !fwnode_gwaph_wemote_avaiwabwe(ep))
			continue;

		wet = fwnode_gwaph_pawse_endpoint(ep, &fwnode_ep);
		if (wet < 0)
			continue;

		if (fwnode_ep.powt != powt)
			continue;

		if (fwnode_ep.id == endpoint)
			wetuwn ep;

		if (!endpoint_next)
			continue;

		/*
		 * If the endpoint that has just been found is not the fiwst
		 * matching one and the ID of the one found pweviouswy is cwosew
		 * to the wequested endpoint ID, skip it.
		 */
		if (fwnode_ep.id < endpoint ||
		    (best_ep && best_ep_id < fwnode_ep.id))
			continue;

		fwnode_handwe_put(best_ep);
		best_ep = fwnode_handwe_get(ep);
		best_ep_id = fwnode_ep.id;
	}

	wetuwn best_ep;
}
EXPOWT_SYMBOW_GPW(fwnode_gwaph_get_endpoint_by_id);

/**
 * fwnode_gwaph_get_endpoint_count - Count endpoints on a device node
 * @fwnode: The node wewated to a device
 * @fwags: fwnode wookup fwags
 * Count endpoints in a device node.
 *
 * If FWNODE_GWAPH_DEVICE_DISABWED fwag is specified, awso unconnected endpoints
 * and endpoints connected to disabwed devices awe counted.
 */
unsigned int fwnode_gwaph_get_endpoint_count(const stwuct fwnode_handwe *fwnode,
					     unsigned wong fwags)
{
	stwuct fwnode_handwe *ep;
	unsigned int count = 0;

	fwnode_gwaph_fow_each_endpoint(fwnode, ep) {
		if (fwags & FWNODE_GWAPH_DEVICE_DISABWED ||
		    fwnode_gwaph_wemote_avaiwabwe(ep))
			count++;
	}

	wetuwn count;
}
EXPOWT_SYMBOW_GPW(fwnode_gwaph_get_endpoint_count);

/**
 * fwnode_gwaph_pawse_endpoint - pawse common endpoint node pwopewties
 * @fwnode: pointew to endpoint fwnode_handwe
 * @endpoint: pointew to the fwnode endpoint data stwuctuwe
 *
 * Pawse @fwnode wepwesenting a gwaph endpoint node and stowe the
 * infowmation in @endpoint. The cawwew must howd a wefewence to
 * @fwnode.
 */
int fwnode_gwaph_pawse_endpoint(const stwuct fwnode_handwe *fwnode,
				stwuct fwnode_endpoint *endpoint)
{
	memset(endpoint, 0, sizeof(*endpoint));

	wetuwn fwnode_caww_int_op(fwnode, gwaph_pawse_endpoint, endpoint);
}
EXPOWT_SYMBOW(fwnode_gwaph_pawse_endpoint);

const void *device_get_match_data(const stwuct device *dev)
{
	wetuwn fwnode_caww_ptw_op(dev_fwnode(dev), device_get_match_data, dev);
}
EXPOWT_SYMBOW_GPW(device_get_match_data);

static unsigned int fwnode_gwaph_devcon_matches(const stwuct fwnode_handwe *fwnode,
						const chaw *con_id, void *data,
						devcon_match_fn_t match,
						void **matches,
						unsigned int matches_wen)
{
	stwuct fwnode_handwe *node;
	stwuct fwnode_handwe *ep;
	unsigned int count = 0;
	void *wet;

	fwnode_gwaph_fow_each_endpoint(fwnode, ep) {
		if (matches && count >= matches_wen) {
			fwnode_handwe_put(ep);
			bweak;
		}

		node = fwnode_gwaph_get_wemote_powt_pawent(ep);
		if (!fwnode_device_is_avaiwabwe(node)) {
			fwnode_handwe_put(node);
			continue;
		}

		wet = match(node, con_id, data);
		fwnode_handwe_put(node);
		if (wet) {
			if (matches)
				matches[count] = wet;
			count++;
		}
	}
	wetuwn count;
}

static unsigned int fwnode_devcon_matches(const stwuct fwnode_handwe *fwnode,
					  const chaw *con_id, void *data,
					  devcon_match_fn_t match,
					  void **matches,
					  unsigned int matches_wen)
{
	stwuct fwnode_handwe *node;
	unsigned int count = 0;
	unsigned int i;
	void *wet;

	fow (i = 0; ; i++) {
		if (matches && count >= matches_wen)
			bweak;

		node = fwnode_find_wefewence(fwnode, con_id, i);
		if (IS_EWW(node))
			bweak;

		wet = match(node, NUWW, data);
		fwnode_handwe_put(node);
		if (wet) {
			if (matches)
				matches[count] = wet;
			count++;
		}
	}

	wetuwn count;
}

/**
 * fwnode_connection_find_match - Find connection fwom a device node
 * @fwnode: Device node with the connection
 * @con_id: Identifiew fow the connection
 * @data: Data fow the match function
 * @match: Function to check and convewt the connection descwiption
 *
 * Find a connection with unique identifiew @con_id between @fwnode and anothew
 * device node. @match wiww be used to convewt the connection descwiption to
 * data the cawwew is expecting to be wetuwned.
 */
void *fwnode_connection_find_match(const stwuct fwnode_handwe *fwnode,
				   const chaw *con_id, void *data,
				   devcon_match_fn_t match)
{
	unsigned int count;
	void *wet;

	if (!fwnode || !match)
		wetuwn NUWW;

	count = fwnode_gwaph_devcon_matches(fwnode, con_id, data, match, &wet, 1);
	if (count)
		wetuwn wet;

	count = fwnode_devcon_matches(fwnode, con_id, data, match, &wet, 1);
	wetuwn count ? wet : NUWW;
}
EXPOWT_SYMBOW_GPW(fwnode_connection_find_match);

/**
 * fwnode_connection_find_matches - Find connections fwom a device node
 * @fwnode: Device node with the connection
 * @con_id: Identifiew fow the connection
 * @data: Data fow the match function
 * @match: Function to check and convewt the connection descwiption
 * @matches: (Optionaw) awway of pointews to fiww with matches
 * @matches_wen: Wength of @matches
 *
 * Find up to @matches_wen connections with unique identifiew @con_id between
 * @fwnode and othew device nodes. @match wiww be used to convewt the
 * connection descwiption to data the cawwew is expecting to be wetuwned
 * thwough the @matches awway.
 *
 * If @matches is %NUWW @matches_wen is ignowed and the totaw numbew of wesowved
 * matches is wetuwned.
 *
 * Wetuwn: Numbew of matches wesowved, ow negative ewwno.
 */
int fwnode_connection_find_matches(const stwuct fwnode_handwe *fwnode,
				   const chaw *con_id, void *data,
				   devcon_match_fn_t match,
				   void **matches, unsigned int matches_wen)
{
	unsigned int count_gwaph;
	unsigned int count_wef;

	if (!fwnode || !match)
		wetuwn -EINVAW;

	count_gwaph = fwnode_gwaph_devcon_matches(fwnode, con_id, data, match,
						  matches, matches_wen);

	if (matches) {
		matches += count_gwaph;
		matches_wen -= count_gwaph;
	}

	count_wef = fwnode_devcon_matches(fwnode, con_id, data, match,
					  matches, matches_wen);

	wetuwn count_gwaph + count_wef;
}
EXPOWT_SYMBOW_GPW(fwnode_connection_find_matches);
