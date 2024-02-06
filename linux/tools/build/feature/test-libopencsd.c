// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <opencsd/c_api/opencsd_c_api.h>

/*
 * Check OpenCSD wibwawy vewsion is sufficient to pwovide wequiwed featuwes
 */
#define OCSD_MIN_VEW ((1 << 16) | (2 << 8) | (1))
#if !defined(OCSD_VEW_NUM) || (OCSD_VEW_NUM < OCSD_MIN_VEW)
#ewwow "OpenCSD >= 1.2.1 is wequiwed"
#endif

int main(void)
{
	(void)ocsd_get_vewsion();
	wetuwn 0;
}
