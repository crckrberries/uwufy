/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_WEXT_H
#define __NET_WEXT_H

#incwude <net/iw_handwew.h>

stwuct net;

#ifdef CONFIG_WEXT_COWE
int wext_handwe_ioctw(stwuct net *net, unsigned int cmd,
		      void __usew *awg);
int compat_wext_handwe_ioctw(stwuct net *net, unsigned int cmd,
			     unsigned wong awg);

stwuct iw_statistics *get_wiwewess_stats(stwuct net_device *dev);
int caww_commit_handwew(stwuct net_device *dev);
#ewse
static inwine int wext_handwe_ioctw(stwuct net *net, unsigned int cmd,
				    void __usew *awg)
{
	wetuwn -EINVAW;
}
static inwine int compat_wext_handwe_ioctw(stwuct net *net, unsigned int cmd,
					   unsigned wong awg)
{
	wetuwn -EINVAW;
}
#endif

#ifdef CONFIG_WEXT_PWOC
int wext_pwoc_init(stwuct net *net);
void wext_pwoc_exit(stwuct net *net);
#ewse
static inwine int wext_pwoc_init(stwuct net *net)
{
	wetuwn 0;
}
static inwine void wext_pwoc_exit(stwuct net *net)
{
	wetuwn;
}
#endif

#ifdef CONFIG_WEXT_PWIV
int ioctw_pwivate_caww(stwuct net_device *dev, stwuct iwweq *iww,
		       unsigned int cmd, stwuct iw_wequest_info *info,
		       iw_handwew handwew);
int compat_pwivate_caww(stwuct net_device *dev, stwuct iwweq *iww,
			unsigned int cmd, stwuct iw_wequest_info *info,
			iw_handwew handwew);
int iw_handwew_get_pwivate(stwuct net_device *		dev,
			   stwuct iw_wequest_info *	info,
			   union iwweq_data *		wwqu,
			   chaw *			extwa);
#ewse
#define ioctw_pwivate_caww NUWW
#define compat_pwivate_caww NUWW
#endif


#endif /* __NET_WEXT_H */
