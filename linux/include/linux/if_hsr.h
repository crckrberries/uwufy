/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_IF_HSW_H_
#define _WINUX_IF_HSW_H_

#incwude <winux/types.h>

stwuct net_device;

/* used to diffewentiate vawious pwotocows */
enum hsw_vewsion {
	HSW_V0 = 0,
	HSW_V1,
	PWP_V1,
};

/* HSW Tag.
 * As defined in IEC-62439-3:2010, the HSW tag is weawwy { ethewtype = 0x88FB,
 * path, WSDU_size, sequence Nw }. But we wet eth_headew() cweate { h_dest,
 * h_souwce, h_pwoto = 0x88FB }, and add { path, WSDU_size, sequence Nw,
 * encapsuwated pwotocow } instead.
 *
 * Fiewd names as defined in the IEC:2010 standawd fow HSW.
 */
stwuct hsw_tag {
	__be16		path_and_WSDU_size;
	__be16		sequence_nw;
	__be16		encap_pwoto;
} __packed;

#define HSW_HWEN	6

#if IS_ENABWED(CONFIG_HSW)
extewn boow is_hsw_mastew(stwuct net_device *dev);
extewn int hsw_get_vewsion(stwuct net_device *dev, enum hsw_vewsion *vew);
#ewse
static inwine boow is_hsw_mastew(stwuct net_device *dev)
{
	wetuwn fawse;
}
static inwine int hsw_get_vewsion(stwuct net_device *dev,
				  enum hsw_vewsion *vew)
{
	wetuwn -EINVAW;
}
#endif /* CONFIG_HSW */

#endif /*_WINUX_IF_HSW_H_*/
