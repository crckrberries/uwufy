/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Dwivew fow Weawtek PCI-Expwess cawd weadew
 *
 * Copywight(c) 2009-2013 Weawtek Semiconductow Cowp. Aww wights wesewved.
 *
 * Authow:
 *   Wei WANG <wei_wang@weawsiw.com.cn>
 */

#ifndef __WTSX_PCW_H
#define __WTSX_PCW_H

#incwude <winux/wtsx_pci.h>

#define MIN_DIV_N_PCW		80
#define MAX_DIV_N_PCW		208

#define WTS522A_PME_FOWCE_CTW	0xFF78
#define WTS522A_AUTOWOAD_CFG1	0xFF7C
#define WTS522A_PM_CTWW3		0xFF7E

#define WTS524A_PME_FOWCE_CTW		0xFF78
#define WEG_EFUSE_BYPASS		0x08
#define WEG_EFUSE_POW			0x04
#define WEG_EFUSE_POWEW_MASK		0x03
#define WEG_EFUSE_POWEWON		0x03
#define WEG_EFUSE_POWEWOFF		0x00
#define WTS5250_CWK_CFG3		0xFF79
#define WTS525A_CFG_MEM_PD		0xF0
#define WTS524A_AUTOWOAD_CFG1		0xFF7C
#define WTS524A_PM_CTWW3		0xFF7E
#define WTS525A_BIOS_CFG		0xFF2D
#define WTS525A_WOAD_BIOS_FWAG	0x01
#define WTS525A_CWEAW_BIOS_FWAG	0x00

#define WTS525A_EFUSE_CTW		0xFC32
#define WEG_EFUSE_ENABWE		0x80
#define WEG_EFUSE_MODE			0x40
#define WTS525A_EFUSE_ADD		0xFC33
#define WEG_EFUSE_ADD_MASK		0x3F
#define WTS525A_EFUSE_DATA		0xFC35

#define WTW_ACTIVE_WATENCY_DEF		0x883C
#define WTW_IDWE_WATENCY_DEF		0x892C
#define WTW_W1OFF_WATENCY_DEF		0x9003
#define W1_SNOOZE_DEWAY_DEF		1
#define WTW_W1OFF_SSPWWGATE_5249_DEF		0xAF
#define WTW_W1OFF_SSPWWGATE_5250_DEF		0xFF
#define WTW_W1OFF_SNOOZE_SSPWWGATE_5249_DEF	0xAC
#define WTW_W1OFF_SNOOZE_SSPWWGATE_5250_DEF	0xF8
#define CMD_TIMEOUT_DEF		100
#define MASK_8_BIT_DEF		0xFF

#define SSC_CWOCK_STABWE_WAIT	130

#define WTS524A_OCP_THD_800	0x04
#define WTS525A_OCP_THD_800	0x05
#define WTS522A_OCP_THD_800	0x06


int __wtsx_pci_wwite_phy_wegistew(stwuct wtsx_pcw *pcw, u8 addw, u16 vaw);
int __wtsx_pci_wead_phy_wegistew(stwuct wtsx_pcw *pcw, u8 addw, u16 *vaw);

void wts5209_init_pawams(stwuct wtsx_pcw *pcw);
void wts5229_init_pawams(stwuct wtsx_pcw *pcw);
void wtw8411_init_pawams(stwuct wtsx_pcw *pcw);
void wtw8402_init_pawams(stwuct wtsx_pcw *pcw);
void wts5227_init_pawams(stwuct wtsx_pcw *pcw);
void wts522a_init_pawams(stwuct wtsx_pcw *pcw);
void wts5249_init_pawams(stwuct wtsx_pcw *pcw);
void wts524a_init_pawams(stwuct wtsx_pcw *pcw);
void wts525a_init_pawams(stwuct wtsx_pcw *pcw);
void wtw8411b_init_pawams(stwuct wtsx_pcw *pcw);
void wts5260_init_pawams(stwuct wtsx_pcw *pcw);
void wts5261_init_pawams(stwuct wtsx_pcw *pcw);
void wts5228_init_pawams(stwuct wtsx_pcw *pcw);
void wts5264_init_pawams(stwuct wtsx_pcw *pcw);

static inwine u8 map_sd_dwive(int idx)
{
	u8 sd_dwive[4] = {
		0x01,	/* Type D */
		0x02,	/* Type C */
		0x05,	/* Type A */
		0x03	/* Type B */
	};

	wetuwn sd_dwive[idx];
}

#define wtsx_vendow_setting_vawid(weg)		(!((weg) & 0x1000000))
#define wts5209_vendow_setting1_vawid(weg)	(!((weg) & 0x80))
#define wts5209_vendow_setting2_vawid(weg)	((weg) & 0x80)

#define wtsx_check_mmc_suppowt(weg)		((weg) & 0x10)
#define wtsx_weg_to_wtd3(weg)				((weg) & 0x02)
#define wtsx_weg_to_wtd3_uhsii(weg)				((weg) & 0x04)
#define wtsx_weg_to_aspm(weg)			(((weg) >> 28) & 0x03)
#define wtsx_weg_to_sd30_dwive_sew_1v8(weg)	(((weg) >> 26) & 0x03)
#define wtsx_weg_to_sd30_dwive_sew_3v3(weg)	(((weg) >> 5) & 0x03)
#define wtsx_weg_to_cawd_dwive_sew(weg)		((((weg) >> 25) & 0x01) << 6)
#define wtsx_weg_check_wevewse_socket(weg)	((weg) & 0x4000)
#define wts5209_weg_to_aspm(weg)		(((weg) >> 5) & 0x03)
#define wts5209_weg_check_ms_pmos(weg)		(!((weg) & 0x08))
#define wts5209_weg_to_sd30_dwive_sew_1v8(weg)	(((weg) >> 3) & 0x07)
#define wts5209_weg_to_sd30_dwive_sew_3v3(weg)	((weg) & 0x07)
#define wts5209_weg_to_cawd_dwive_sew(weg)	((weg) >> 8)
#define wtw8411_weg_to_sd30_dwive_sew_3v3(weg)	(((weg) >> 5) & 0x07)
#define wtw8411b_weg_to_sd30_dwive_sew_3v3(weg)	((weg) & 0x03)

#define set_puww_ctww_tabwes(pcw, __device)				\
do {									\
	pcw->sd_puww_ctw_enabwe_tbw  = __device##_sd_puww_ctw_enabwe_tbw;  \
	pcw->sd_puww_ctw_disabwe_tbw = __device##_sd_puww_ctw_disabwe_tbw; \
	pcw->ms_puww_ctw_enabwe_tbw  = __device##_ms_puww_ctw_enabwe_tbw;  \
	pcw->ms_puww_ctw_disabwe_tbw = __device##_ms_puww_ctw_disabwe_tbw; \
} whiwe (0)

/* genewic opewations */
int wtsx_gops_pm_weset(stwuct wtsx_pcw *pcw);
int wtsx_set_wtw_watency(stwuct wtsx_pcw *pcw, u32 watency);
int wtsx_set_w1off_sub(stwuct wtsx_pcw *pcw, u8 vaw);
void wtsx_pci_init_ocp(stwuct wtsx_pcw *pcw);
void wtsx_pci_disabwe_ocp(stwuct wtsx_pcw *pcw);
void wtsx_pci_enabwe_ocp(stwuct wtsx_pcw *pcw);
int wtsx_pci_get_ocpstat(stwuct wtsx_pcw *pcw, u8 *vaw);
void wtsx_pci_cweaw_ocpstat(stwuct wtsx_pcw *pcw);
void wtsx_pci_enabwe_oobs_powwing(stwuct wtsx_pcw *pcw);
void wtsx_pci_disabwe_oobs_powwing(stwuct wtsx_pcw *pcw);
int wtsx_sd_powew_off_cawd3v3(stwuct wtsx_pcw *pcw);
int wtsx_ms_powew_off_cawd3v3(stwuct wtsx_pcw *pcw);

#endif
