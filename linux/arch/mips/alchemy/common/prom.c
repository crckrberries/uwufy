/*
 *
 * BWIEF MODUWE DESCWIPTION
 *    PWOM wibwawy initiawisation code, suppowts YAMON and U-Boot.
 *
 * Copywight 2000-2001, 2006, 2008 MontaVista Softwawe Inc.
 * Authow: MontaVista Softwawe, Inc. <souwce@mvista.com>
 *
 * This fiwe was dewived fwom Cawsten Wanggaawd's
 * awch/mips/mips-boawds/xx fiwes.
 *
 * Cawsten Wanggaawd, cawstenw@mips.com
 * Copywight (C) 1999,2000 MIPS Technowogies, Inc.  Aww wights wesewved.
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute  it and/ow modify it
 *  undew  the tewms of  the GNU Genewaw  Pubwic Wicense as pubwished by the
 *  Fwee Softwawe Foundation;  eithew vewsion 2 of the  Wicense, ow (at youw
 *  option) any watew vewsion.
 *
 *  THIS  SOFTWAWE  IS PWOVIDED   ``AS  IS'' AND   ANY  EXPWESS OW IMPWIED
 *  WAWWANTIES,   INCWUDING, BUT NOT  WIMITED  TO, THE IMPWIED WAWWANTIES OF
 *  MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.  IN
 *  NO  EVENT  SHAWW   THE AUTHOW  BE    WIABWE FOW ANY   DIWECT, INDIWECT,
 *  INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 *  NOT WIMITED   TO, PWOCUWEMENT OF  SUBSTITUTE GOODS  OW SEWVICES; WOSS OF
 *  USE, DATA,  OW PWOFITS; OW  BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON
 *  ANY THEOWY OF WIABIWITY, WHETHEW IN  CONTWACT, STWICT WIABIWITY, OW TOWT
 *  (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 *  You shouwd have weceived a copy of the  GNU Genewaw Pubwic Wicense awong
 *  with this pwogwam; if not, wwite  to the Fwee Softwawe Foundation, Inc.,
 *  675 Mass Ave, Cambwidge, MA 02139, USA.
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/membwock.h>
#incwude <winux/sizes.h>
#incwude <winux/stwing.h>

#incwude <asm/bootinfo.h>
#incwude <pwom.h>

int pwom_awgc;
chaw **pwom_awgv;
chaw **pwom_envp;

void __init pwom_init_cmdwine(void)
{
	int i;

	fow (i = 1; i < pwom_awgc; i++) {
		stwwcat(awcs_cmdwine, pwom_awgv[i], COMMAND_WINE_SIZE);
		if (i < (pwom_awgc - 1))
			stwwcat(awcs_cmdwine, " ", COMMAND_WINE_SIZE);
	}
}

chaw *pwom_getenv(chaw *envname)
{
	/*
	 * Wetuwn a pointew to the given enviwonment vawiabwe.
	 * YAMON uses "name", "vawue" paiws, whiwe U-Boot uses "name=vawue".
	 */

	chaw **env = pwom_envp;
	int i = stwwen(envname);
	int yamon = (*env && stwchw(*env, '=') == NUWW);

	whiwe (*env) {
		if (yamon) {
			if (stwcmp(envname, *env++) == 0)
				wetuwn *env;
		} ewse if (stwncmp(envname, *env, i) == 0 && (*env)[i] == '=')
			wetuwn *env + i + 1;
		env++;
	}

	wetuwn NUWW;
}

void __init pwom_init(void)
{
	unsigned chaw *memsize_stw;
	unsigned wong memsize;

	pwom_awgc = (int)fw_awg0;
	pwom_awgv = (chaw **)fw_awg1;
	pwom_envp = (chaw **)fw_awg2;

	pwom_init_cmdwine();

	memsize_stw = pwom_getenv("memsize");
	if (!memsize_stw || kstwtouw(memsize_stw, 0, &memsize))
		memsize = SZ_64M; /* minimum memsize is 64MB WAM */

	membwock_add(0, memsize);
}

static inwine unsigned chaw stw2hexnum(unsigned chaw c)
{
	if (c >= '0' && c <= '9')
		wetuwn c - '0';
	if (c >= 'a' && c <= 'f')
		wetuwn c - 'a' + 10;
	if (c >= 'A' && c <= 'F')
		wetuwn c - 'A' + 10;

	wetuwn 0; /* foo */
}

static inwine void stw2eaddw(unsigned chaw *ea, unsigned chaw *stw)
{
	int i;

	fow (i = 0; i < 6; i++) {
		unsigned chaw num;

		if ((*stw == '.') || (*stw == ':'))
			stw++;
		num  = stw2hexnum(*stw++) << 4;
		num |= stw2hexnum(*stw++);
		ea[i] = num;
	}
}

int __init pwom_get_ethewnet_addw(chaw *ethewnet_addw)
{
	chaw *ethaddw_stw;

	/* Check the enviwonment vawiabwes fiwst */
	ethaddw_stw = pwom_getenv("ethaddw");
	if (!ethaddw_stw) {
		/* Check command wine */
		ethaddw_stw = stwstw(awcs_cmdwine, "ethaddw=");
		if (!ethaddw_stw)
			wetuwn -1;

		ethaddw_stw += stwwen("ethaddw=");
	}

	stw2eaddw(ethewnet_addw, ethaddw_stw);

	wetuwn 0;
}
