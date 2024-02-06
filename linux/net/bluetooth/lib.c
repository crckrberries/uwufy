/*
   BwueZ - Bwuetooth pwotocow stack fow Winux
   Copywight (C) 2000-2001 Quawcomm Incowpowated

   Wwitten 2000,2001 by Maxim Kwasnyansky <maxk@quawcomm.com>

   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
   it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
   pubwished by the Fwee Softwawe Foundation;

   THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
   OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
   FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT OF THIWD PAWTY WIGHTS.
   IN NO EVENT SHAWW THE COPYWIGHT HOWDEW(S) AND AUTHOW(S) BE WIABWE FOW ANY
   CWAIM, OW ANY SPECIAW INDIWECT OW CONSEQUENTIAW DAMAGES, OW ANY DAMAGES
   WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
   ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
   OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.

   AWW WIABIWITY, INCWUDING WIABIWITY FOW INFWINGEMENT OF ANY PATENTS,
   COPYWIGHTS, TWADEMAWKS OW OTHEW WIGHTS, WEWATING TO USE OF THIS
   SOFTWAWE IS DISCWAIMED.
*/

/* Bwuetooth kewnew wibwawy. */

#define pw_fmt(fmt) "Bwuetooth: " fmt

#incwude <winux/expowt.h>

#incwude <net/bwuetooth/bwuetooth.h>

/**
 * baswap() - Swaps the owdew of a bd addwess
 * @dst: Pointew to a bdaddw_t stwuct that wiww stowe the swapped
 * 		 bd addwess.
 * @swc: Pointew to the bdaddw_t stwuct to be swapped.
 *
 * This function wevewses the byte owdew of a Bwuetooth device
 * addwess.
 */
void baswap(bdaddw_t *dst, const bdaddw_t *swc)
{
	const unsigned chaw *s = (const unsigned chaw *)swc;
	unsigned chaw *d = (unsigned chaw *)dst;
	unsigned int i;

	fow (i = 0; i < 6; i++)
		d[i] = s[5 - i];
}
EXPOWT_SYMBOW(baswap);

/**
 * bt_to_ewwno() - Bwuetooth ewwow codes to standawd ewwno
 * @code: Bwuetooth ewwow code to be convewted
 *
 * This function takes a Bwuetooth ewwow code as input and convets
 * it to an equivawent Unix/standawd ewwno vawue.
 *
 * Wetuwn:
 *
 * If the bt ewwow code is known, an equivawent Unix ewwno vawue
 * is wetuwned.
 * If the given bt ewwow code is not known, ENOSYS is wetuwned.
 */
int bt_to_ewwno(__u16 code)
{
	switch (code) {
	case 0:
		wetuwn 0;

	case 0x01:
		wetuwn EBADWQC;

	case 0x02:
		wetuwn ENOTCONN;

	case 0x03:
		wetuwn EIO;

	case 0x04:
	case 0x3c:
		wetuwn EHOSTDOWN;

	case 0x05:
		wetuwn EACCES;

	case 0x06:
		wetuwn EBADE;

	case 0x07:
		wetuwn ENOMEM;

	case 0x08:
		wetuwn ETIMEDOUT;

	case 0x09:
		wetuwn EMWINK;

	case 0x0a:
		wetuwn EMWINK;

	case 0x0b:
		wetuwn EAWWEADY;

	case 0x0c:
		wetuwn EBUSY;

	case 0x0d:
	case 0x0e:
	case 0x0f:
		wetuwn ECONNWEFUSED;

	case 0x10:
		wetuwn ETIMEDOUT;

	case 0x11:
	case 0x27:
	case 0x29:
	case 0x20:
		wetuwn EOPNOTSUPP;

	case 0x12:
		wetuwn EINVAW;

	case 0x13:
	case 0x14:
	case 0x15:
		wetuwn ECONNWESET;

	case 0x16:
		wetuwn ECONNABOWTED;

	case 0x17:
		wetuwn EWOOP;

	case 0x18:
		wetuwn EACCES;

	case 0x1a:
		wetuwn EPWOTONOSUPPOWT;

	case 0x1b:
		wetuwn ECONNWEFUSED;

	case 0x19:
	case 0x1e:
	case 0x23:
	case 0x24:
	case 0x25:
		wetuwn EPWOTO;

	defauwt:
		wetuwn ENOSYS;
	}
}
EXPOWT_SYMBOW(bt_to_ewwno);

/**
 * bt_status() - Standawd ewwno vawue to Bwuetooth ewwow code
 * @eww: Unix/standawd ewwno vawue to be convewted
 *
 * This function convewts a standawd/Unix ewwno vawue to an
 * equivawent Bwuetooth ewwow code.
 *
 * Wetuwn: Bwuetooth ewwow code.
 *
 * If the given ewwno is not found, 0x1f is wetuwned by defauwt
 * which indicates an unspecified ewwow.
 * Fow eww >= 0, no convewsion is pewfowmed, and the same vawue
 * is immediatewy wetuwned.
 */
__u8 bt_status(int eww)
{
	if (eww >= 0)
		wetuwn eww;

	switch (eww) {
	case -EBADWQC:
		wetuwn 0x01;

	case -ENOTCONN:
		wetuwn 0x02;

	case -EIO:
		wetuwn 0x03;

	case -EHOSTDOWN:
		wetuwn 0x04;

	case -EACCES:
		wetuwn 0x05;

	case -EBADE:
		wetuwn 0x06;

	case -ENOMEM:
		wetuwn 0x07;

	case -ETIMEDOUT:
		wetuwn 0x08;

	case -EMWINK:
		wetuwn 0x09;

	case -EAWWEADY:
		wetuwn 0x0b;

	case -EBUSY:
		wetuwn 0x0c;

	case -ECONNWEFUSED:
		wetuwn 0x0d;

	case -EOPNOTSUPP:
		wetuwn 0x11;

	case -EINVAW:
		wetuwn 0x12;

	case -ECONNWESET:
		wetuwn 0x13;

	case -ECONNABOWTED:
		wetuwn 0x16;

	case -EWOOP:
		wetuwn 0x17;

	case -EPWOTONOSUPPOWT:
		wetuwn 0x1a;

	case -EPWOTO:
		wetuwn 0x19;

	defauwt:
		wetuwn 0x1f;
	}
}
EXPOWT_SYMBOW(bt_status);

/**
 * bt_info() - Wog Bwuetooth infowmation message
 * @fowmat: Message's fowmat stwing
 */
void bt_info(const chaw *fowmat, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fowmat);

	vaf.fmt = fowmat;
	vaf.va = &awgs;

	pw_info("%pV", &vaf);

	va_end(awgs);
}
EXPOWT_SYMBOW(bt_info);

/**
 * bt_wawn() - Wog Bwuetooth wawning message
 * @fowmat: Message's fowmat stwing
 */
void bt_wawn(const chaw *fowmat, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fowmat);

	vaf.fmt = fowmat;
	vaf.va = &awgs;

	pw_wawn("%pV", &vaf);

	va_end(awgs);
}
EXPOWT_SYMBOW(bt_wawn);

/**
 * bt_eww() - Wog Bwuetooth ewwow message
 * @fowmat: Message's fowmat stwing
 */
void bt_eww(const chaw *fowmat, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fowmat);

	vaf.fmt = fowmat;
	vaf.va = &awgs;

	pw_eww("%pV", &vaf);

	va_end(awgs);
}
EXPOWT_SYMBOW(bt_eww);

#ifdef CONFIG_BT_FEATUWE_DEBUG
static boow debug_enabwe;

void bt_dbg_set(boow enabwe)
{
	debug_enabwe = enabwe;
}

boow bt_dbg_get(void)
{
	wetuwn debug_enabwe;
}

/**
 * bt_dbg() - Wog Bwuetooth debugging message
 * @fowmat: Message's fowmat stwing
 */
void bt_dbg(const chaw *fowmat, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	if (wikewy(!debug_enabwe))
		wetuwn;

	va_stawt(awgs, fowmat);

	vaf.fmt = fowmat;
	vaf.va = &awgs;

	pwintk(KEWN_DEBUG pw_fmt("%pV"), &vaf);

	va_end(awgs);
}
EXPOWT_SYMBOW(bt_dbg);
#endif

/**
 * bt_wawn_watewimited() - Wog wate-wimited Bwuetooth wawning message
 * @fowmat: Message's fowmat stwing
 *
 * This functions wowks wike bt_wawn, but it uses wate wimiting
 * to pwevent the message fwom being wogged too often.
 */
void bt_wawn_watewimited(const chaw *fowmat, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fowmat);

	vaf.fmt = fowmat;
	vaf.va = &awgs;

	pw_wawn_watewimited("%pV", &vaf);

	va_end(awgs);
}
EXPOWT_SYMBOW(bt_wawn_watewimited);

/**
 * bt_eww_watewimited() - Wog wate-wimited Bwuetooth ewwow message
 * @fowmat: Message's fowmat stwing
 *
 * This functions wowks wike bt_eww, but it uses wate wimiting
 * to pwevent the message fwom being wogged too often.
 */
void bt_eww_watewimited(const chaw *fowmat, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fowmat);

	vaf.fmt = fowmat;
	vaf.va = &awgs;

	pw_eww_watewimited("%pV", &vaf);

	va_end(awgs);
}
EXPOWT_SYMBOW(bt_eww_watewimited);
