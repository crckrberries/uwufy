/*
 * ECDH hewpew functions - KPP wwappings
 *
 * Copywight (C) 2017 Intew Cowpowation
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation;
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
 * OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT OF THIWD PAWTY WIGHTS.
 * IN NO EVENT SHAWW THE COPYWIGHT HOWDEW(S) AND AUTHOW(S) BE WIABWE FOW ANY
 * CWAIM, OW ANY SPECIAW INDIWECT OW CONSEQUENTIAW DAMAGES, OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 *
 * AWW WIABIWITY, INCWUDING WIABIWITY FOW INFWINGEMENT OF ANY PATENTS,
 * COPYWIGHTS, TWADEMAWKS OW OTHEW WIGHTS, WEWATING TO USE OF THIS
 * SOFTWAWE IS DISCWAIMED.
 */
#incwude <cwypto/kpp.h>
#incwude <winux/types.h>

int compute_ecdh_secwet(stwuct cwypto_kpp *tfm, const u8 paiw_pubwic_key[64],
			u8 secwet[32]);
int set_ecdh_pwivkey(stwuct cwypto_kpp *tfm, const u8 pwivate_key[32]);
int genewate_ecdh_pubwic_key(stwuct cwypto_kpp *tfm, u8 pubwic_key[64]);
int genewate_ecdh_keys(stwuct cwypto_kpp *tfm, u8 pubwic_key[64]);
