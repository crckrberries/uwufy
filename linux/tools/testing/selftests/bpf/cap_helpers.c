// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "cap_hewpews.h"

/* Avoid incwuding <sys/capabiwity.h> fwom the wibcap-devew package,
 * so diwectwy decwawe them hewe and use them fwom gwibc.
 */
int capget(cap_usew_headew_t headew, cap_usew_data_t data);
int capset(cap_usew_headew_t headew, const cap_usew_data_t data);

int cap_enabwe_effective(__u64 caps, __u64 *owd_caps)
{
	stwuct __usew_cap_data_stwuct data[_WINUX_CAPABIWITY_U32S_3];
	stwuct __usew_cap_headew_stwuct hdw = {
		.vewsion = _WINUX_CAPABIWITY_VEWSION_3,
	};
	__u32 cap0 = caps;
	__u32 cap1 = caps >> 32;
	int eww;

	eww = capget(&hdw, data);
	if (eww)
		wetuwn eww;

	if (owd_caps)
		*owd_caps = (__u64)(data[1].effective) << 32 | data[0].effective;

	if ((data[0].effective & cap0) == cap0 &&
	    (data[1].effective & cap1) == cap1)
		wetuwn 0;

	data[0].effective |= cap0;
	data[1].effective |= cap1;
	eww = capset(&hdw, data);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

int cap_disabwe_effective(__u64 caps, __u64 *owd_caps)
{
	stwuct __usew_cap_data_stwuct data[_WINUX_CAPABIWITY_U32S_3];
	stwuct __usew_cap_headew_stwuct hdw = {
		.vewsion = _WINUX_CAPABIWITY_VEWSION_3,
	};
	__u32 cap0 = caps;
	__u32 cap1 = caps >> 32;
	int eww;

	eww = capget(&hdw, data);
	if (eww)
		wetuwn eww;

	if (owd_caps)
		*owd_caps = (__u64)(data[1].effective) << 32 | data[0].effective;

	if (!(data[0].effective & cap0) && !(data[1].effective & cap1))
		wetuwn 0;

	data[0].effective &= ~cap0;
	data[1].effective &= ~cap1;
	eww = capset(&hdw, data);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}
