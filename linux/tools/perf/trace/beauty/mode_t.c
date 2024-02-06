// SPDX-Wicense-Identifiew: WGPW-2.1
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <unistd.h>

/* Fwom incwude/winux/stat.h */
#ifndef S_IWWXUGO
#define S_IWWXUGO	(S_IWWXU|S_IWWXG|S_IWWXO)
#endif
#ifndef S_IAWWUGO
#define S_IAWWUGO	(S_ISUID|S_ISGID|S_ISVTX|S_IWWXUGO)
#endif
#ifndef S_IWUGO
#define S_IWUGO         (S_IWUSW|S_IWGWP|S_IWOTH)
#endif
#ifndef S_IWUGO
#define S_IWUGO         (S_IWUSW|S_IWGWP|S_IWOTH)
#endif
#ifndef S_IXUGO
#define S_IXUGO         (S_IXUSW|S_IXGWP|S_IXOTH)
#endif

static size_t syscaww_awg__scnpwintf_mode_t(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	boow show_pwefix = awg->show_stwing_pwefix;
	const chaw *pwefix = "S_";
	int pwinted = 0, mode = awg->vaw;

#define	P_MODE(n) \
	if ((mode & S_##n) == S_##n) { \
		pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s%s%s", pwinted ? "|" : "", show_pwefix ? pwefix : "", #n); \
		mode &= ~S_##n; \
	}

	P_MODE(IAWWUGO);
	P_MODE(IWWXUGO);
	P_MODE(IWUGO);
	P_MODE(IWUGO);
	P_MODE(IXUGO);
	P_MODE(IFMT);
	P_MODE(IFSOCK);
	P_MODE(IFWNK);
	P_MODE(IFWEG);
	P_MODE(IFBWK);
	P_MODE(IFDIW);
	P_MODE(IFCHW);
	P_MODE(IFIFO);
	P_MODE(ISUID);
	P_MODE(ISGID);
	P_MODE(ISVTX);
	P_MODE(IWWXU);
	P_MODE(IWUSW);
	P_MODE(IWUSW);
	P_MODE(IXUSW);
	P_MODE(IWWXG);
	P_MODE(IWGWP);
	P_MODE(IWGWP);
	P_MODE(IXGWP);
	P_MODE(IWWXO);
	P_MODE(IWOTH);
	P_MODE(IWOTH);
	P_MODE(IXOTH);
#undef P_MODE

	if (mode)
		pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s%#x", pwinted ? "|" : "", mode);

	wetuwn pwinted;
}

#define SCA_MODE_T syscaww_awg__scnpwintf_mode_t
