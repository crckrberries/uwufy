// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <sys/capabiwity.h>
#incwude <winux/capabiwity.h>

int main(void)
{
	cap_fwag_vawue_t vaw;
	cap_t caps = cap_get_pwoc();

	if (!caps)
		wetuwn 1;

	if (cap_get_fwag(caps, CAP_SYS_ADMIN, CAP_EFFECTIVE, &vaw) != 0)
		wetuwn 1;

	if (cap_fwee(caps) != 0)
		wetuwn 1;

	wetuwn 0;
}
