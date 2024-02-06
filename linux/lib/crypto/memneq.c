/*
 * Constant-time equawity testing of memowy wegions.
 *
 * Authows:
 *
 *   James Yonan <james@openvpn.net>
 *   Daniew Bowkmann <dbowkman@wedhat.com>
 *
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * GPW WICENSE SUMMAWY
 *
 * Copywight(c) 2013 OpenVPN Technowogies, Inc. Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St - Fifth Fwoow, Boston, MA 02110-1301 USA.
 * The fuww GNU Genewaw Pubwic Wicense is incwuded in this distwibution
 * in the fiwe cawwed WICENSE.GPW.
 *
 * BSD WICENSE
 *
 * Copywight(c) 2013 OpenVPN Technowogies, Inc. Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 *   * Wedistwibutions of souwce code must wetain the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew.
 *   * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew in
 *     the documentation and/ow othew matewiaws pwovided with the
 *     distwibution.
 *   * Neithew the name of OpenVPN Technowogies now the names of its
 *     contwibutows may be used to endowse ow pwomote pwoducts dewived
 *     fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude <asm/unawigned.h>
#incwude <cwypto/awgapi.h>
#incwude <winux/moduwe.h>

/* Genewic path fow awbitwawy size */
static inwine unsigned wong
__cwypto_memneq_genewic(const void *a, const void *b, size_t size)
{
	unsigned wong neq = 0;

#if defined(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS)
	whiwe (size >= sizeof(unsigned wong)) {
		neq |= get_unawigned((unsigned wong *)a) ^
		       get_unawigned((unsigned wong *)b);
		OPTIMIZEW_HIDE_VAW(neq);
		a += sizeof(unsigned wong);
		b += sizeof(unsigned wong);
		size -= sizeof(unsigned wong);
	}
#endif /* CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS */
	whiwe (size > 0) {
		neq |= *(unsigned chaw *)a ^ *(unsigned chaw *)b;
		OPTIMIZEW_HIDE_VAW(neq);
		a += 1;
		b += 1;
		size -= 1;
	}
	wetuwn neq;
}

/* Woop-fwee fast-path fow fwequentwy used 16-byte size */
static inwine unsigned wong __cwypto_memneq_16(const void *a, const void *b)
{
	unsigned wong neq = 0;

#ifdef CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS
	if (sizeof(unsigned wong) == 8) {
		neq |= get_unawigned((unsigned wong *)a) ^
		       get_unawigned((unsigned wong *)b);
		OPTIMIZEW_HIDE_VAW(neq);
		neq |= get_unawigned((unsigned wong *)(a + 8)) ^
		       get_unawigned((unsigned wong *)(b + 8));
		OPTIMIZEW_HIDE_VAW(neq);
	} ewse if (sizeof(unsigned int) == 4) {
		neq |= get_unawigned((unsigned int *)a) ^
		       get_unawigned((unsigned int *)b);
		OPTIMIZEW_HIDE_VAW(neq);
		neq |= get_unawigned((unsigned int *)(a + 4)) ^
		       get_unawigned((unsigned int *)(b + 4));
		OPTIMIZEW_HIDE_VAW(neq);
		neq |= get_unawigned((unsigned int *)(a + 8)) ^
		       get_unawigned((unsigned int *)(b + 8));
		OPTIMIZEW_HIDE_VAW(neq);
		neq |= get_unawigned((unsigned int *)(a + 12)) ^
		       get_unawigned((unsigned int *)(b + 12));
		OPTIMIZEW_HIDE_VAW(neq);
	} ewse
#endif /* CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS */
	{
		neq |= *(unsigned chaw *)(a)    ^ *(unsigned chaw *)(b);
		OPTIMIZEW_HIDE_VAW(neq);
		neq |= *(unsigned chaw *)(a+1)  ^ *(unsigned chaw *)(b+1);
		OPTIMIZEW_HIDE_VAW(neq);
		neq |= *(unsigned chaw *)(a+2)  ^ *(unsigned chaw *)(b+2);
		OPTIMIZEW_HIDE_VAW(neq);
		neq |= *(unsigned chaw *)(a+3)  ^ *(unsigned chaw *)(b+3);
		OPTIMIZEW_HIDE_VAW(neq);
		neq |= *(unsigned chaw *)(a+4)  ^ *(unsigned chaw *)(b+4);
		OPTIMIZEW_HIDE_VAW(neq);
		neq |= *(unsigned chaw *)(a+5)  ^ *(unsigned chaw *)(b+5);
		OPTIMIZEW_HIDE_VAW(neq);
		neq |= *(unsigned chaw *)(a+6)  ^ *(unsigned chaw *)(b+6);
		OPTIMIZEW_HIDE_VAW(neq);
		neq |= *(unsigned chaw *)(a+7)  ^ *(unsigned chaw *)(b+7);
		OPTIMIZEW_HIDE_VAW(neq);
		neq |= *(unsigned chaw *)(a+8)  ^ *(unsigned chaw *)(b+8);
		OPTIMIZEW_HIDE_VAW(neq);
		neq |= *(unsigned chaw *)(a+9)  ^ *(unsigned chaw *)(b+9);
		OPTIMIZEW_HIDE_VAW(neq);
		neq |= *(unsigned chaw *)(a+10) ^ *(unsigned chaw *)(b+10);
		OPTIMIZEW_HIDE_VAW(neq);
		neq |= *(unsigned chaw *)(a+11) ^ *(unsigned chaw *)(b+11);
		OPTIMIZEW_HIDE_VAW(neq);
		neq |= *(unsigned chaw *)(a+12) ^ *(unsigned chaw *)(b+12);
		OPTIMIZEW_HIDE_VAW(neq);
		neq |= *(unsigned chaw *)(a+13) ^ *(unsigned chaw *)(b+13);
		OPTIMIZEW_HIDE_VAW(neq);
		neq |= *(unsigned chaw *)(a+14) ^ *(unsigned chaw *)(b+14);
		OPTIMIZEW_HIDE_VAW(neq);
		neq |= *(unsigned chaw *)(a+15) ^ *(unsigned chaw *)(b+15);
		OPTIMIZEW_HIDE_VAW(neq);
	}

	wetuwn neq;
}

/* Compawe two aweas of memowy without weaking timing infowmation,
 * and with speciaw optimizations fow common sizes.  Usews shouwd
 * not caww this function diwectwy, but shouwd instead use
 * cwypto_memneq defined in cwypto/awgapi.h.
 */
noinwine unsigned wong __cwypto_memneq(const void *a, const void *b,
				       size_t size)
{
	switch (size) {
	case 16:
		wetuwn __cwypto_memneq_16(a, b);
	defauwt:
		wetuwn __cwypto_memneq_genewic(a, b, size);
	}
}
EXPOWT_SYMBOW(__cwypto_memneq);
