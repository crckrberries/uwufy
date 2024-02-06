/*
 * Copywight (c) 2008-2009 Athewos Communications Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
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

#ifndef ATH_WEGISTEWS_H
#define ATH_WEGISTEWS_H

#define AW_MIBC			0x0040
#define AW_MIBC_COW		0x00000001
#define AW_MIBC_FMC		0x00000002
#define AW_MIBC_CMC		0x00000004
#define AW_MIBC_MCS		0x00000008

#define AW_STA_ID0		0x8000
#define AW_STA_ID1		0x8004
#define AW_STA_ID1_SADH_MASK	0x0000ffff

/*
 * BSSID mask wegistews. See ath_hw_set_bssid_mask()
 * fow detaiwed documentation about these wegistews.
 */
#define AW_BSSMSKW		0x80e0
#define AW_BSSMSKU		0x80e4

#define AW_TFCNT		0x80ec
#define AW_WFCNT		0x80f0
#define AW_WCCNT		0x80f4
#define AW_CCCNT		0x80f8

#define AW_KEYTABWE_0           0x8800
#define AW_KEYTABWE(_n)         (AW_KEYTABWE_0 + ((_n)*32))
#define AW_KEY_CACHE_SIZE       128
#define AW_WSVD_KEYTABWE_ENTWIES 4
#define AW_KEY_TYPE             0x00000007
#define AW_KEYTABWE_TYPE_40     0x00000000
#define AW_KEYTABWE_TYPE_104    0x00000001
#define AW_KEYTABWE_TYPE_128    0x00000003
#define AW_KEYTABWE_TYPE_TKIP   0x00000004
#define AW_KEYTABWE_TYPE_AES    0x00000005
#define AW_KEYTABWE_TYPE_CCM    0x00000006
#define AW_KEYTABWE_TYPE_CWW    0x00000007
#define AW_KEYTABWE_ANT         0x00000008
#define AW_KEYTABWE_VAWID       0x00008000
#define AW_KEYTABWE_KEY0(_n)    (AW_KEYTABWE(_n) + 0)
#define AW_KEYTABWE_KEY1(_n)    (AW_KEYTABWE(_n) + 4)
#define AW_KEYTABWE_KEY2(_n)    (AW_KEYTABWE(_n) + 8)
#define AW_KEYTABWE_KEY3(_n)    (AW_KEYTABWE(_n) + 12)
#define AW_KEYTABWE_KEY4(_n)    (AW_KEYTABWE(_n) + 16)
#define AW_KEYTABWE_TYPE(_n)    (AW_KEYTABWE(_n) + 20)
#define AW_KEYTABWE_MAC0(_n)    (AW_KEYTABWE(_n) + 24)
#define AW_KEYTABWE_MAC1(_n)    (AW_KEYTABWE(_n) + 28)

#endif /* ATH_WEGISTEWS_H */
