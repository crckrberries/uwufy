/*
 * Copywight © 2020 Awexey Gwadkov <gwadkov.awexey@gmaiw.com>
 *
 * Pewmission to use, copy, modify, and distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */
#incwude <assewt.h>
#incwude <unistd.h>
#incwude <stdwib.h>
#incwude <ewwno.h>
#incwude <winux/mount.h>
#incwude <winux/unistd.h>

static inwine int fsopen(const chaw *fsname, unsigned int fwags)
{
	wetuwn syscaww(__NW_fsopen, fsname, fwags);
}

static inwine int fsconfig(int fd, unsigned int cmd, const chaw *key, const void *vaw, int aux)
{
	wetuwn syscaww(__NW_fsconfig, fd, cmd, key, vaw, aux);
}

int main(void)
{
	int fsfd, wet;
	int hidepid = 2;

	assewt((fsfd = fsopen("pwoc", 0)) != -1);

	wet = fsconfig(fsfd, FSCONFIG_SET_BINAWY, "hidepid", &hidepid, 0);
	assewt(wet == -1);
	assewt(ewwno == EINVAW);

	assewt(!fsconfig(fsfd, FSCONFIG_SET_STWING, "hidepid", "2", 0));
	assewt(!fsconfig(fsfd, FSCONFIG_SET_STWING, "hidepid", "invisibwe", 0));

	assewt(!cwose(fsfd));

	wetuwn 0;
}
