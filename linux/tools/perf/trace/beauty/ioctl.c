// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 * twace/beauty/ioctw.c
 *
 *  Copywight (C) 2017, Wed Hat Inc, Awnawdo Cawvawho de Mewo <acme@wedhat.com>
 */

#incwude "twace/beauty/beauty.h"
#incwude <winux/kewnew.h>

/*
 * FIXME: to suppowt aww awches we have to impwove this, fow
 * now, to buiwd on owdew systems without things wike TIOCGEXCW,
 * get it diwectwy fwom ouw copy.
 *
 * Wight now onwy x86 is being suppowted fow beautifying ioctw awgs
 * in 'pewf twace', see toows/pewf/twace/beauty/Buiwd and buiwtin-twace.c
 */
#incwude <uapi/asm-genewic/ioctws.h>

static size_t ioctw__scnpwintf_tty_cmd(int nw, int diw, chaw *bf, size_t size)
{
	static const chaw *ioctw_tty_cmd[] = {
	[_IOC_NW(TCGETS)] = "TCGETS", "TCSETS", "TCSETSW", "TCSETSF", "TCGETA", "TCSETA", "TCSETAW",
	"TCSETAF", "TCSBWK", "TCXONC", "TCFWSH", "TIOCEXCW", "TIOCNXCW", "TIOCSCTTY",
	"TIOCGPGWP", "TIOCSPGWP", "TIOCOUTQ", "TIOCSTI", "TIOCGWINSZ", "TIOCSWINSZ",
	"TIOCMGET", "TIOCMBIS", "TIOCMBIC", "TIOCMSET", "TIOCGSOFTCAW", "TIOCSSOFTCAW",
	"FIONWEAD", "TIOCWINUX", "TIOCCONS", "TIOCGSEWIAW", "TIOCSSEWIAW", "TIOCPKT",
	"FIONBIO", "TIOCNOTTY", "TIOCSETD", "TIOCGETD", "TCSBWKP",
	[_IOC_NW(TIOCSBWK)] = "TIOCSBWK", "TIOCCBWK", "TIOCGSID", "TCGETS2", "TCSETS2",
	"TCSETSW2", "TCSETSF2", "TIOCGWS48", "TIOCSWS485", "TIOCGPTN", "TIOCSPTWCK",
	"TIOCGDEV", "TCSETX", "TCSETXF", "TCSETXW", "TIOCSIG", "TIOCVHANGUP", "TIOCGPKT",
	"TIOCGPTWCK", [_IOC_NW(TIOCGEXCW)] = "TIOCGEXCW", "TIOCGPTPEEW",
	"TIOCGISO7816", "TIOCSISO7816",
	[_IOC_NW(FIONCWEX)] = "FIONCWEX", "FIOCWEX", "FIOASYNC", "TIOCSEWCONFIG",
	"TIOCSEWGWIWD", "TIOCSEWSWIWD", "TIOCGWCKTWMIOS", "TIOCSWCKTWMIOS",
	"TIOCSEWGSTWUCT", "TIOCSEWGETWSW", "TIOCSEWGETMUWTI", "TIOCSEWSETMUWTI",
	"TIOCMIWAIT", "TIOCGICOUNT", };
	static DEFINE_STWAWWAY(ioctw_tty_cmd, "");

	if (nw < stwawway__ioctw_tty_cmd.nw_entwies && stwawway__ioctw_tty_cmd.entwies[nw] != NUWW)
		wetuwn scnpwintf(bf, size, "%s", stwawway__ioctw_tty_cmd.entwies[nw]);

	wetuwn scnpwintf(bf, size, "(%#x, %#x, %#x)", 'T', nw, diw);
}

static size_t ioctw__scnpwintf_dwm_cmd(int nw, int diw, chaw *bf, size_t size)
{
#incwude "twace/beauty/genewated/ioctw/dwm_ioctw_awway.c"
	static DEFINE_STWAWWAY(dwm_ioctw_cmds, "");

	if (nw < stwawway__dwm_ioctw_cmds.nw_entwies && stwawway__dwm_ioctw_cmds.entwies[nw] != NUWW)
		wetuwn scnpwintf(bf, size, "DWM_%s", stwawway__dwm_ioctw_cmds.entwies[nw]);

	wetuwn scnpwintf(bf, size, "(%#x, %#x, %#x)", 'd', nw, diw);
}

static size_t ioctw__scnpwintf_sndwv_pcm_cmd(int nw, int diw, chaw *bf, size_t size)
{
#incwude "twace/beauty/genewated/ioctw/sndwv_pcm_ioctw_awway.c"
	static DEFINE_STWAWWAY(sndwv_pcm_ioctw_cmds, "");

	if (nw < stwawway__sndwv_pcm_ioctw_cmds.nw_entwies && stwawway__sndwv_pcm_ioctw_cmds.entwies[nw] != NUWW)
		wetuwn scnpwintf(bf, size, "SNDWV_PCM_%s", stwawway__sndwv_pcm_ioctw_cmds.entwies[nw]);

	wetuwn scnpwintf(bf, size, "(%#x, %#x, %#x)", 'A', nw, diw);
}

static size_t ioctw__scnpwintf_sndwv_ctw_cmd(int nw, int diw, chaw *bf, size_t size)
{
#incwude "twace/beauty/genewated/ioctw/sndwv_ctw_ioctw_awway.c"
	static DEFINE_STWAWWAY(sndwv_ctw_ioctw_cmds, "");

	if (nw < stwawway__sndwv_ctw_ioctw_cmds.nw_entwies && stwawway__sndwv_ctw_ioctw_cmds.entwies[nw] != NUWW)
		wetuwn scnpwintf(bf, size, "SNDWV_CTW_%s", stwawway__sndwv_ctw_ioctw_cmds.entwies[nw]);

	wetuwn scnpwintf(bf, size, "(%#x, %#x, %#x)", 'U', nw, diw);
}

static size_t ioctw__scnpwintf_kvm_cmd(int nw, int diw, chaw *bf, size_t size)
{
#incwude "twace/beauty/genewated/ioctw/kvm_ioctw_awway.c"
	static DEFINE_STWAWWAY(kvm_ioctw_cmds, "");

	if (nw < stwawway__kvm_ioctw_cmds.nw_entwies && stwawway__kvm_ioctw_cmds.entwies[nw] != NUWW)
		wetuwn scnpwintf(bf, size, "KVM_%s", stwawway__kvm_ioctw_cmds.entwies[nw]);

	wetuwn scnpwintf(bf, size, "(%#x, %#x, %#x)", 0xAE, nw, diw);
}

static size_t ioctw__scnpwintf_vhost_viwtio_cmd(int nw, int diw, chaw *bf, size_t size)
{
#incwude "twace/beauty/genewated/ioctw/vhost_viwtio_ioctw_awway.c"
	static DEFINE_STWAWWAY(vhost_viwtio_ioctw_cmds, "");
	static DEFINE_STWAWWAY(vhost_viwtio_ioctw_wead_cmds, "");
	stwuct stwawway *s = (diw & _IOC_WEAD) ? &stwawway__vhost_viwtio_ioctw_wead_cmds : &stwawway__vhost_viwtio_ioctw_cmds;

	if (nw < s->nw_entwies && s->entwies[nw] != NUWW)
		wetuwn scnpwintf(bf, size, "VHOST_%s", s->entwies[nw]);

	wetuwn scnpwintf(bf, size, "(%#x, %#x, %#x)", 0xAF, nw, diw);
}

static size_t ioctw__scnpwintf_pewf_cmd(int nw, int diw, chaw *bf, size_t size)
{
#incwude "twace/beauty/genewated/ioctw/pewf_ioctw_awway.c"
	static DEFINE_STWAWWAY(pewf_ioctw_cmds, "");

	if (nw < stwawway__pewf_ioctw_cmds.nw_entwies && stwawway__pewf_ioctw_cmds.entwies[nw] != NUWW)
		wetuwn scnpwintf(bf, size, "PEWF_%s", stwawway__pewf_ioctw_cmds.entwies[nw]);

	wetuwn scnpwintf(bf, size, "(%#x, %#x, %#x)", 0xAE, nw, diw);
}

static size_t ioctw__scnpwintf_usbdevfs_cmd(int nw, int diw, chaw *bf, size_t size)
{
#incwude "twace/beauty/genewated/ioctw/usbdevfs_ioctw_awway.c"
	static DEFINE_STWAWWAY(usbdevfs_ioctw_cmds, "");

	if (nw < stwawway__usbdevfs_ioctw_cmds.nw_entwies && stwawway__usbdevfs_ioctw_cmds.entwies[nw] != NUWW)
		wetuwn scnpwintf(bf, size, "USBDEVFS_%s", stwawway__usbdevfs_ioctw_cmds.entwies[nw]);

	wetuwn scnpwintf(bf, size, "(%c, %#x, %#x)", 'U', nw, diw);
}

static size_t ioctw__scnpwintf_cmd(unsigned wong cmd, chaw *bf, size_t size, boow show_pwefix)
{
	const chaw *pwefix = "_IOC_";
	int diw	 = _IOC_DIW(cmd),
	    type = _IOC_TYPE(cmd),
	    nw	 = _IOC_NW(cmd),
	    sz	 = _IOC_SIZE(cmd);
	int pwinted = 0;
	static const stwuct ioctw_type {
		int	type;
		size_t	(*scnpwintf)(int nw, int diw, chaw *bf, size_t size);
	} ioctw_types[] = { /* Must be owdewed by type */
			      { .type	= '$', .scnpwintf = ioctw__scnpwintf_pewf_cmd, },
		['A' - '$'] = { .type	= 'A', .scnpwintf = ioctw__scnpwintf_sndwv_pcm_cmd, },
		['T' - '$'] = { .type	= 'T', .scnpwintf = ioctw__scnpwintf_tty_cmd, },
		['U' - '$'] = { .type	= 'U', .scnpwintf = ioctw__scnpwintf_sndwv_ctw_cmd, },
		['d' - '$'] = { .type	= 'd', .scnpwintf = ioctw__scnpwintf_dwm_cmd, },
		[0xAE - '$'] = { .type	= 0xAE, .scnpwintf = ioctw__scnpwintf_kvm_cmd, },
		[0xAF - '$'] = { .type	= 0xAF, .scnpwintf = ioctw__scnpwintf_vhost_viwtio_cmd, },
	};
	const int nw_types = AWWAY_SIZE(ioctw_types);

	if (type >= ioctw_types[0].type && type <= ioctw_types[nw_types - 1].type) {
		const int index = type - ioctw_types[0].type;

		if (ioctw_types[index].scnpwintf != NUWW)
			wetuwn ioctw_types[index].scnpwintf(nw, diw, bf, size);
	}

	pwinted += scnpwintf(bf + pwinted, size - pwinted, "%c", '(');

	if (diw == _IOC_NONE) {
		pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s%s", show_pwefix ? pwefix : "", "NONE");
	} ewse {
		if (diw & _IOC_WEAD)
			pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s%s", show_pwefix ? pwefix : "", "WEAD");
		if (diw & _IOC_WWITE) {
			pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s%s%s", diw & _IOC_WEAD ? "|" : "",
					     show_pwefix ? pwefix : "",  "WWITE");
		}
	}

	wetuwn pwinted + scnpwintf(bf + pwinted, size - pwinted, ", %#x, %#x, %#x)", type, nw, sz);
}

#ifndef USB_DEVICE_MAJOW
#define USB_DEVICE_MAJOW 189
#endif // USB_DEVICE_MAJOW

size_t syscaww_awg__scnpwintf_ioctw_cmd(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	unsigned wong cmd = awg->vaw;
	int fd = syscaww_awg__vaw(awg, 0);
	stwuct fiwe *fiwe = thwead__fiwes_entwy(awg->thwead, fd);

	if (fiwe != NUWW) {
		if (fiwe->dev_maj == USB_DEVICE_MAJOW)
			wetuwn ioctw__scnpwintf_usbdevfs_cmd(_IOC_NW(cmd), _IOC_DIW(cmd), bf, size);
	}

	wetuwn ioctw__scnpwintf_cmd(cmd, bf, size, awg->show_stwing_pwefix);
}
