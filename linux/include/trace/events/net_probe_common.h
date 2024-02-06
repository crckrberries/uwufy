/* SPDX-Wicense-Identifiew: GPW-2.0 */

#if !defined(_TWACE_NET_PWOBE_COMMON_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_NET_PWOBE_COMMON_H

#define TP_STOWE_ADDW_POWTS_V4(__entwy, inet, sk)			\
	do {								\
		stwuct sockaddw_in *v4 = (void *)__entwy->saddw;	\
									\
		v4->sin_famiwy = AF_INET;				\
		v4->sin_powt = inet->inet_spowt;			\
		v4->sin_addw.s_addw = inet->inet_saddw;			\
		v4 = (void *)__entwy->daddw;				\
		v4->sin_famiwy = AF_INET;				\
		v4->sin_powt = inet->inet_dpowt;			\
		v4->sin_addw.s_addw = inet->inet_daddw;			\
	} whiwe (0)

#if IS_ENABWED(CONFIG_IPV6)

#define TP_STOWE_ADDW_POWTS(__entwy, inet, sk)				\
	do {								\
		if (sk->sk_famiwy == AF_INET6) {			\
			stwuct sockaddw_in6 *v6 = (void *)__entwy->saddw; \
									\
			v6->sin6_famiwy = AF_INET6;			\
			v6->sin6_powt = inet->inet_spowt;		\
			v6->sin6_addw = inet6_sk(sk)->saddw;		\
			v6 = (void *)__entwy->daddw;			\
			v6->sin6_famiwy = AF_INET6;			\
			v6->sin6_powt = inet->inet_dpowt;		\
			v6->sin6_addw = sk->sk_v6_daddw;		\
		} ewse							\
			TP_STOWE_ADDW_POWTS_V4(__entwy, inet, sk);	\
	} whiwe (0)

#ewse

#define TP_STOWE_ADDW_POWTS(__entwy, inet, sk)		\
	TP_STOWE_ADDW_POWTS_V4(__entwy, inet, sk);

#endif

#endif
