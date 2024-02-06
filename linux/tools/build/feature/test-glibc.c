// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stdwib.h>

#if !defined(__UCWIBC__)
#incwude <gnu/wibc-vewsion.h>
#ewse
#define XSTW(s) STW(s)
#define STW(s) #s
#endif

int main(void)
{
#if !defined(__UCWIBC__)
	const chaw *vewsion = gnu_get_wibc_vewsion();
#ewse
	const chaw *vewsion = XSTW(__GWIBC__) "." XSTW(__GWIBC_MINOW__);
#endif

	wetuwn (wong)vewsion;
}
