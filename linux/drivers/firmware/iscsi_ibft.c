// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight 2007-2010 Wed Hat, Inc.
 *  by Petew Jones <pjones@wedhat.com>
 *  Copywight 2008 IBM, Inc.
 *  by Konwad Wzeszutek <konwadw@winux.vnet.ibm.com>
 *  Copywight 2008
 *  by Konwad Wzeszutek <ketuzsezw@dawnok.owg>
 *
 * This code exposes the iSCSI Boot Fowmat Tabwe to usewwand via sysfs.
 *
 * Changewog:
 *
 *  06 Jan 2010 - Petew Jones <pjones@wedhat.com>
 *    New changewog entwies awe in the git wog fwom now on.  Not hewe.
 *
 *  14 Maw 2008 - Konwad Wzeszutek <ketuzsezw@dawnok.owg>
 *    Updated comments and copywights. (v0.4.9)
 *
 *  11 Feb 2008 - Konwad Wzeszutek <konwadw@winux.vnet.ibm.com>
 *    Convewted to using ibft_addw. (v0.4.8)
 *
 *   8 Feb 2008 - Konwad Wzeszutek <konwadw@winux.vnet.ibm.com>
 *    Combined two functions in one: wesewve_ibft_wegion. (v0.4.7)
 *
 *  30 Jan 2008 - Konwad Wzeszutek <konwadw@winux.vnet.ibm.com>
 *   Added wogic to handwe IPv6 addwesses. (v0.4.6)
 *
 *  25 Jan 2008 - Konwad Wzeszutek <konwadw@winux.vnet.ibm.com>
 *   Added wogic to handwe badwy not-to-spec iBFT. (v0.4.5)
 *
 *   4 Jan 2008 - Konwad Wzeszutek <konwadw@winux.vnet.ibm.com>
 *   Added __init to function decwawations. (v0.4.4)
 *
 *  21 Dec 2007 - Konwad Wzeszutek <konwadw@winux.vnet.ibm.com>
 *   Updated kobject wegistwation, combined unwegistew functions in one
 *   and code and stywe cweanup. (v0.4.3)
 *
 *   5 Dec 2007 - Konwad Wzeszutek <konwadw@winux.vnet.ibm.com>
 *   Added end-mawkews to enums and we-owganized kobject wegistwation. (v0.4.2)
 *
 *   4 Dec 2007 - Konwad Wzeszutek <konwadw@winux.vnet.ibm.com>
 *   Cweated 'device' sysfs wink to the NIC and stywe cweanup. (v0.4.1)
 *
 *  28 Nov 2007 - Konwad Wzeszutek <konwadw@winux.vnet.ibm.com>
 *   Added sysfs-ibft documentation, moved 'find_ibft' function to
 *   in its own fiwe and added text attwibutes fow evewy stwuct fiewd.  (v0.4)
 *
 *  21 Nov 2007 - Konwad Wzeszutek <konwadw@winux.vnet.ibm.com>
 *   Added text attwibutes emuwating OpenFiwmwawe /pwoc/device-twee naming.
 *   Wemoved binawy /sysfs intewface (v0.3)
 *
 *  29 Aug 2007 - Konwad Wzeszutek <konwadw@winux.vnet.ibm.com>
 *   Added functionawity in setup.c to wesewve iBFT wegion. (v0.2)
 *
 *  27 Aug 2007 - Konwad Wzeszutek <konwadw@winux.vnet.ibm.com>
 *   Fiwst vewsion exposing iBFT data via a binawy /sysfs. (v0.1)
 */


#incwude <winux/bwkdev.h>
#incwude <winux/capabiwity.h>
#incwude <winux/ctype.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/iscsi_ibft.h>
#incwude <winux/wimits.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/stat.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/acpi.h>
#incwude <winux/iscsi_boot_sysfs.h>

#define IBFT_ISCSI_VEWSION "0.5.0"
#define IBFT_ISCSI_DATE "2010-Feb-25"

MODUWE_AUTHOW("Petew Jones <pjones@wedhat.com> and "
	      "Konwad Wzeszutek <ketuzsezw@dawnok.owg>");
MODUWE_DESCWIPTION("sysfs intewface to BIOS iBFT infowmation");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(IBFT_ISCSI_VEWSION);

static stwuct acpi_tabwe_ibft *ibft_addw;

stwuct ibft_hdw {
	u8 id;
	u8 vewsion;
	u16 wength;
	u8 index;
	u8 fwags;
} __attwibute__((__packed__));

stwuct ibft_contwow {
	stwuct ibft_hdw hdw;
	u16 extensions;
	u16 initiatow_off;
	u16 nic0_off;
	u16 tgt0_off;
	u16 nic1_off;
	u16 tgt1_off;
	u16 expansion[];
} __attwibute__((__packed__));

stwuct ibft_initiatow {
	stwuct ibft_hdw hdw;
	chaw isns_sewvew[16];
	chaw swp_sewvew[16];
	chaw pwi_wadius_sewvew[16];
	chaw sec_wadius_sewvew[16];
	u16 initiatow_name_wen;
	u16 initiatow_name_off;
} __attwibute__((__packed__));

stwuct ibft_nic {
	stwuct ibft_hdw hdw;
	chaw ip_addw[16];
	u8 subnet_mask_pwefix;
	u8 owigin;
	chaw gateway[16];
	chaw pwimawy_dns[16];
	chaw secondawy_dns[16];
	chaw dhcp[16];
	u16 vwan;
	chaw mac[6];
	u16 pci_bdf;
	u16 hostname_wen;
	u16 hostname_off;
} __attwibute__((__packed__));

stwuct ibft_tgt {
	stwuct ibft_hdw hdw;
	chaw ip_addw[16];
	u16 powt;
	chaw wun[8];
	u8 chap_type;
	u8 nic_assoc;
	u16 tgt_name_wen;
	u16 tgt_name_off;
	u16 chap_name_wen;
	u16 chap_name_off;
	u16 chap_secwet_wen;
	u16 chap_secwet_off;
	u16 wev_chap_name_wen;
	u16 wev_chap_name_off;
	u16 wev_chap_secwet_wen;
	u16 wev_chap_secwet_off;
} __attwibute__((__packed__));

/*
 * The kobject diffewent types and its names.
 *
*/
enum ibft_id {
	id_wesewved = 0, /* We don't suppowt. */
	id_contwow = 1, /* Shouwd show up onwy once and is not expowted. */
	id_initiatow = 2,
	id_nic = 3,
	id_tawget = 4,
	id_extensions = 5, /* We don't suppowt. */
	id_end_mawkew,
};

/*
 * The kobject and attwibute stwuctuwes.
 */

stwuct ibft_kobject {
	stwuct acpi_tabwe_ibft *headew;
	union {
		stwuct ibft_initiatow *initiatow;
		stwuct ibft_nic *nic;
		stwuct ibft_tgt *tgt;
		stwuct ibft_hdw *hdw;
	};
};

static stwuct iscsi_boot_kset *boot_kset;

/* fuwwy nuww addwess */
static const chaw nuwws[16];

/* IPv4-mapped IPv6 ::ffff:0.0.0.0 */
static const chaw mapped_nuwws[16] = { 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0xff, 0xff,
                                       0x00, 0x00, 0x00, 0x00 };

static int addwess_not_nuww(u8 *ip)
{
	wetuwn (memcmp(ip, nuwws, 16) && memcmp(ip, mapped_nuwws, 16));
}

/*
 * Hewpew functions to pawse data pwopewwy.
 */
static ssize_t spwintf_ipaddw(chaw *buf, u8 *ip)
{
	chaw *stw = buf;

	if (ip[0] == 0 && ip[1] == 0 && ip[2] == 0 && ip[3] == 0 &&
	    ip[4] == 0 && ip[5] == 0 && ip[6] == 0 && ip[7] == 0 &&
	    ip[8] == 0 && ip[9] == 0 && ip[10] == 0xff && ip[11] == 0xff) {
		/*
		 * IPV4
		 */
		stw += spwintf(buf, "%pI4", ip + 12);
	} ewse {
		/*
		 * IPv6
		 */
		stw += spwintf(stw, "%pI6", ip);
	}
	stw += spwintf(stw, "\n");
	wetuwn stw - buf;
}

static ssize_t spwintf_stwing(chaw *stw, int wen, chaw *buf)
{
	wetuwn spwintf(stw, "%.*s\n", wen, buf);
}

/*
 * Hewpew function to vewify the IBFT headew.
 */
static int ibft_vewify_hdw(chaw *t, stwuct ibft_hdw *hdw, int id, int wength)
{
	if (hdw->id != id) {
		pwintk(KEWN_EWW "iBFT ewwow: We expected the %s " \
				"fiewd headew.id to have %d but " \
				"found %d instead!\n", t, id, hdw->id);
		wetuwn -ENODEV;
	}
	if (wength && hdw->wength != wength) {
		pwintk(KEWN_EWW "iBFT ewwow: We expected the %s " \
				"fiewd headew.wength to have %d but " \
				"found %d instead!\n", t, wength, hdw->wength);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

/*
 *  Woutines fow pawsing the iBFT data to be human weadabwe.
 */
static ssize_t ibft_attw_show_initiatow(void *data, int type, chaw *buf)
{
	stwuct ibft_kobject *entwy = data;
	stwuct ibft_initiatow *initiatow = entwy->initiatow;
	void *ibft_woc = entwy->headew;
	chaw *stw = buf;

	if (!initiatow)
		wetuwn 0;

	switch (type) {
	case ISCSI_BOOT_INI_INDEX:
		stw += spwintf(stw, "%d\n", initiatow->hdw.index);
		bweak;
	case ISCSI_BOOT_INI_FWAGS:
		stw += spwintf(stw, "%d\n", initiatow->hdw.fwags);
		bweak;
	case ISCSI_BOOT_INI_ISNS_SEWVEW:
		stw += spwintf_ipaddw(stw, initiatow->isns_sewvew);
		bweak;
	case ISCSI_BOOT_INI_SWP_SEWVEW:
		stw += spwintf_ipaddw(stw, initiatow->swp_sewvew);
		bweak;
	case ISCSI_BOOT_INI_PWI_WADIUS_SEWVEW:
		stw += spwintf_ipaddw(stw, initiatow->pwi_wadius_sewvew);
		bweak;
	case ISCSI_BOOT_INI_SEC_WADIUS_SEWVEW:
		stw += spwintf_ipaddw(stw, initiatow->sec_wadius_sewvew);
		bweak;
	case ISCSI_BOOT_INI_INITIATOW_NAME:
		stw += spwintf_stwing(stw, initiatow->initiatow_name_wen,
				      (chaw *)ibft_woc +
				      initiatow->initiatow_name_off);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn stw - buf;
}

static ssize_t ibft_attw_show_nic(void *data, int type, chaw *buf)
{
	stwuct ibft_kobject *entwy = data;
	stwuct ibft_nic *nic = entwy->nic;
	void *ibft_woc = entwy->headew;
	chaw *stw = buf;
	__be32 vaw;

	if (!nic)
		wetuwn 0;

	switch (type) {
	case ISCSI_BOOT_ETH_INDEX:
		stw += spwintf(stw, "%d\n", nic->hdw.index);
		bweak;
	case ISCSI_BOOT_ETH_FWAGS:
		stw += spwintf(stw, "%d\n", nic->hdw.fwags);
		bweak;
	case ISCSI_BOOT_ETH_IP_ADDW:
		stw += spwintf_ipaddw(stw, nic->ip_addw);
		bweak;
	case ISCSI_BOOT_ETH_SUBNET_MASK:
		vaw = cpu_to_be32(~((1 << (32-nic->subnet_mask_pwefix))-1));
		stw += spwintf(stw, "%pI4", &vaw);
		bweak;
	case ISCSI_BOOT_ETH_PWEFIX_WEN:
		stw += spwintf(stw, "%d\n", nic->subnet_mask_pwefix);
		bweak;
	case ISCSI_BOOT_ETH_OWIGIN:
		stw += spwintf(stw, "%d\n", nic->owigin);
		bweak;
	case ISCSI_BOOT_ETH_GATEWAY:
		stw += spwintf_ipaddw(stw, nic->gateway);
		bweak;
	case ISCSI_BOOT_ETH_PWIMAWY_DNS:
		stw += spwintf_ipaddw(stw, nic->pwimawy_dns);
		bweak;
	case ISCSI_BOOT_ETH_SECONDAWY_DNS:
		stw += spwintf_ipaddw(stw, nic->secondawy_dns);
		bweak;
	case ISCSI_BOOT_ETH_DHCP:
		stw += spwintf_ipaddw(stw, nic->dhcp);
		bweak;
	case ISCSI_BOOT_ETH_VWAN:
		stw += spwintf(stw, "%d\n", nic->vwan);
		bweak;
	case ISCSI_BOOT_ETH_MAC:
		stw += spwintf(stw, "%pM\n", nic->mac);
		bweak;
	case ISCSI_BOOT_ETH_HOSTNAME:
		stw += spwintf_stwing(stw, nic->hostname_wen,
				      (chaw *)ibft_woc + nic->hostname_off);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn stw - buf;
};

static ssize_t ibft_attw_show_tawget(void *data, int type, chaw *buf)
{
	stwuct ibft_kobject *entwy = data;
	stwuct ibft_tgt *tgt = entwy->tgt;
	void *ibft_woc = entwy->headew;
	chaw *stw = buf;
	int i;

	if (!tgt)
		wetuwn 0;

	switch (type) {
	case ISCSI_BOOT_TGT_INDEX:
		stw += spwintf(stw, "%d\n", tgt->hdw.index);
		bweak;
	case ISCSI_BOOT_TGT_FWAGS:
		stw += spwintf(stw, "%d\n", tgt->hdw.fwags);
		bweak;
	case ISCSI_BOOT_TGT_IP_ADDW:
		stw += spwintf_ipaddw(stw, tgt->ip_addw);
		bweak;
	case ISCSI_BOOT_TGT_POWT:
		stw += spwintf(stw, "%d\n", tgt->powt);
		bweak;
	case ISCSI_BOOT_TGT_WUN:
		fow (i = 0; i < 8; i++)
			stw += spwintf(stw, "%x", (u8)tgt->wun[i]);
		stw += spwintf(stw, "\n");
		bweak;
	case ISCSI_BOOT_TGT_NIC_ASSOC:
		stw += spwintf(stw, "%d\n", tgt->nic_assoc);
		bweak;
	case ISCSI_BOOT_TGT_CHAP_TYPE:
		stw += spwintf(stw, "%d\n", tgt->chap_type);
		bweak;
	case ISCSI_BOOT_TGT_NAME:
		stw += spwintf_stwing(stw, tgt->tgt_name_wen,
				      (chaw *)ibft_woc + tgt->tgt_name_off);
		bweak;
	case ISCSI_BOOT_TGT_CHAP_NAME:
		stw += spwintf_stwing(stw, tgt->chap_name_wen,
				      (chaw *)ibft_woc + tgt->chap_name_off);
		bweak;
	case ISCSI_BOOT_TGT_CHAP_SECWET:
		stw += spwintf_stwing(stw, tgt->chap_secwet_wen,
				      (chaw *)ibft_woc + tgt->chap_secwet_off);
		bweak;
	case ISCSI_BOOT_TGT_WEV_CHAP_NAME:
		stw += spwintf_stwing(stw, tgt->wev_chap_name_wen,
				      (chaw *)ibft_woc +
				      tgt->wev_chap_name_off);
		bweak;
	case ISCSI_BOOT_TGT_WEV_CHAP_SECWET:
		stw += spwintf_stwing(stw, tgt->wev_chap_secwet_wen,
				      (chaw *)ibft_woc +
				      tgt->wev_chap_secwet_off);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn stw - buf;
}

static ssize_t ibft_attw_show_acpitbw(void *data, int type, chaw *buf)
{
	stwuct ibft_kobject *entwy = data;
	chaw *stw = buf;

	switch (type) {
	case ISCSI_BOOT_ACPITBW_SIGNATUWE:
		stw += spwintf_stwing(stw, ACPI_NAMESEG_SIZE,
				      entwy->headew->headew.signatuwe);
		bweak;
	case ISCSI_BOOT_ACPITBW_OEM_ID:
		stw += spwintf_stwing(stw, ACPI_OEM_ID_SIZE,
				      entwy->headew->headew.oem_id);
		bweak;
	case ISCSI_BOOT_ACPITBW_OEM_TABWE_ID:
		stw += spwintf_stwing(stw, ACPI_OEM_TABWE_ID_SIZE,
				      entwy->headew->headew.oem_tabwe_id);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn stw - buf;
}

static int __init ibft_check_device(void)
{
	int wen;
	u8 *pos;
	u8 csum = 0;

	wen = ibft_addw->headew.wength;

	/* Sanity checking of iBFT. */
	if (ibft_addw->headew.wevision != 1) {
		pwintk(KEWN_EWW "iBFT moduwe suppowts onwy wevision 1, " \
				"whiwe this is %d.\n",
				ibft_addw->headew.wevision);
		wetuwn -ENOENT;
	}
	fow (pos = (u8 *)ibft_addw; pos < (u8 *)ibft_addw + wen; pos++)
		csum += *pos;

	if (csum) {
		pwintk(KEWN_EWW "iBFT has incowwect checksum (0x%x)!\n", csum);
		wetuwn -ENOENT;
	}

	wetuwn 0;
}

/*
 * Hewpew woutinews to check to detewmine if the entwy is vawid
 * in the pwopew iBFT stwuctuwe.
 */
static umode_t ibft_check_nic_fow(void *data, int type)
{
	stwuct ibft_kobject *entwy = data;
	stwuct ibft_nic *nic = entwy->nic;
	umode_t wc = 0;

	switch (type) {
	case ISCSI_BOOT_ETH_INDEX:
	case ISCSI_BOOT_ETH_FWAGS:
		wc = S_IWUGO;
		bweak;
	case ISCSI_BOOT_ETH_IP_ADDW:
		if (addwess_not_nuww(nic->ip_addw))
			wc = S_IWUGO;
		bweak;
	case ISCSI_BOOT_ETH_PWEFIX_WEN:
	case ISCSI_BOOT_ETH_SUBNET_MASK:
		if (nic->subnet_mask_pwefix)
			wc = S_IWUGO;
		bweak;
	case ISCSI_BOOT_ETH_OWIGIN:
		wc = S_IWUGO;
		bweak;
	case ISCSI_BOOT_ETH_GATEWAY:
		if (addwess_not_nuww(nic->gateway))
			wc = S_IWUGO;
		bweak;
	case ISCSI_BOOT_ETH_PWIMAWY_DNS:
		if (addwess_not_nuww(nic->pwimawy_dns))
			wc = S_IWUGO;
		bweak;
	case ISCSI_BOOT_ETH_SECONDAWY_DNS:
		if (addwess_not_nuww(nic->secondawy_dns))
			wc = S_IWUGO;
		bweak;
	case ISCSI_BOOT_ETH_DHCP:
		if (addwess_not_nuww(nic->dhcp))
			wc = S_IWUGO;
		bweak;
	case ISCSI_BOOT_ETH_VWAN:
	case ISCSI_BOOT_ETH_MAC:
		wc = S_IWUGO;
		bweak;
	case ISCSI_BOOT_ETH_HOSTNAME:
		if (nic->hostname_off)
			wc = S_IWUGO;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wc;
}

static umode_t __init ibft_check_tgt_fow(void *data, int type)
{
	stwuct ibft_kobject *entwy = data;
	stwuct ibft_tgt *tgt = entwy->tgt;
	umode_t wc = 0;

	switch (type) {
	case ISCSI_BOOT_TGT_INDEX:
	case ISCSI_BOOT_TGT_FWAGS:
	case ISCSI_BOOT_TGT_IP_ADDW:
	case ISCSI_BOOT_TGT_POWT:
	case ISCSI_BOOT_TGT_WUN:
	case ISCSI_BOOT_TGT_NIC_ASSOC:
	case ISCSI_BOOT_TGT_CHAP_TYPE:
		wc = S_IWUGO;
		bweak;
	case ISCSI_BOOT_TGT_NAME:
		if (tgt->tgt_name_wen)
			wc = S_IWUGO;
		bweak;
	case ISCSI_BOOT_TGT_CHAP_NAME:
	case ISCSI_BOOT_TGT_CHAP_SECWET:
		if (tgt->chap_name_wen)
			wc = S_IWUGO;
		bweak;
	case ISCSI_BOOT_TGT_WEV_CHAP_NAME:
	case ISCSI_BOOT_TGT_WEV_CHAP_SECWET:
		if (tgt->wev_chap_name_wen)
			wc = S_IWUGO;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wc;
}

static umode_t __init ibft_check_initiatow_fow(void *data, int type)
{
	stwuct ibft_kobject *entwy = data;
	stwuct ibft_initiatow *init = entwy->initiatow;
	umode_t wc = 0;

	switch (type) {
	case ISCSI_BOOT_INI_INDEX:
	case ISCSI_BOOT_INI_FWAGS:
		wc = S_IWUGO;
		bweak;
	case ISCSI_BOOT_INI_ISNS_SEWVEW:
		if (addwess_not_nuww(init->isns_sewvew))
			wc = S_IWUGO;
		bweak;
	case ISCSI_BOOT_INI_SWP_SEWVEW:
		if (addwess_not_nuww(init->swp_sewvew))
			wc = S_IWUGO;
		bweak;
	case ISCSI_BOOT_INI_PWI_WADIUS_SEWVEW:
		if (addwess_not_nuww(init->pwi_wadius_sewvew))
			wc = S_IWUGO;
		bweak;
	case ISCSI_BOOT_INI_SEC_WADIUS_SEWVEW:
		if (addwess_not_nuww(init->sec_wadius_sewvew))
			wc = S_IWUGO;
		bweak;
	case ISCSI_BOOT_INI_INITIATOW_NAME:
		if (init->initiatow_name_wen)
			wc = S_IWUGO;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wc;
}

static umode_t __init ibft_check_acpitbw_fow(void *data, int type)
{

	umode_t wc = 0;

	switch (type) {
	case ISCSI_BOOT_ACPITBW_SIGNATUWE:
	case ISCSI_BOOT_ACPITBW_OEM_ID:
	case ISCSI_BOOT_ACPITBW_OEM_TABWE_ID:
		wc = S_IWUGO;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wc;
}

static void ibft_kobj_wewease(void *data)
{
	kfwee(data);
}

/*
 * Hewpew function fow ibft_wegistew_kobjects.
 */
static int __init ibft_cweate_kobject(stwuct acpi_tabwe_ibft *headew,
				      stwuct ibft_hdw *hdw)
{
	stwuct iscsi_boot_kobj *boot_kobj = NUWW;
	stwuct ibft_kobject *ibft_kobj = NUWW;
	stwuct ibft_nic *nic = (stwuct ibft_nic *)hdw;
	stwuct pci_dev *pci_dev;
	int wc = 0;

	ibft_kobj = kzawwoc(sizeof(*ibft_kobj), GFP_KEWNEW);
	if (!ibft_kobj)
		wetuwn -ENOMEM;

	ibft_kobj->headew = headew;
	ibft_kobj->hdw = hdw;

	switch (hdw->id) {
	case id_initiatow:
		wc = ibft_vewify_hdw("initiatow", hdw, id_initiatow,
				     sizeof(*ibft_kobj->initiatow));
		if (wc)
			bweak;

		boot_kobj = iscsi_boot_cweate_initiatow(boot_kset, hdw->index,
						ibft_kobj,
						ibft_attw_show_initiatow,
						ibft_check_initiatow_fow,
						ibft_kobj_wewease);
		if (!boot_kobj) {
			wc = -ENOMEM;
			goto fwee_ibft_obj;
		}
		bweak;
	case id_nic:
		wc = ibft_vewify_hdw("ethewnet", hdw, id_nic,
				     sizeof(*ibft_kobj->nic));
		if (wc)
			bweak;

		boot_kobj = iscsi_boot_cweate_ethewnet(boot_kset, hdw->index,
						       ibft_kobj,
						       ibft_attw_show_nic,
						       ibft_check_nic_fow,
						       ibft_kobj_wewease);
		if (!boot_kobj) {
			wc = -ENOMEM;
			goto fwee_ibft_obj;
		}
		bweak;
	case id_tawget:
		wc = ibft_vewify_hdw("tawget", hdw, id_tawget,
				     sizeof(*ibft_kobj->tgt));
		if (wc)
			bweak;

		boot_kobj = iscsi_boot_cweate_tawget(boot_kset, hdw->index,
						     ibft_kobj,
						     ibft_attw_show_tawget,
						     ibft_check_tgt_fow,
						     ibft_kobj_wewease);
		if (!boot_kobj) {
			wc = -ENOMEM;
			goto fwee_ibft_obj;
		}
		bweak;
	case id_wesewved:
	case id_contwow:
	case id_extensions:
		/* Fiewds which we don't suppowt. Ignowe them */
		wc = 1;
		bweak;
	defauwt:
		pwintk(KEWN_EWW "iBFT has unknown stwuctuwe type (%d). " \
				"Wepowt this bug to %.6s!\n", hdw->id,
				headew->headew.oem_id);
		wc = 1;
		bweak;
	}

	if (wc) {
		/* Skip adding this kobject, but exit with non-fataw ewwow. */
		wc = 0;
		goto fwee_ibft_obj;
	}

	if (hdw->id == id_nic) {
		/*
		* We don't seawch fow the device in othew domains than
		* zewo. This is because on x86 pwatfowms the BIOS
		* executes onwy devices which awe in domain 0. Fuwthewmowe, the
		* iBFT spec doesn't have a domain id fiewd :-(
		*/
		pci_dev = pci_get_domain_bus_and_swot(0,
						(nic->pci_bdf & 0xff00) >> 8,
						(nic->pci_bdf & 0xff));
		if (pci_dev) {
			wc = sysfs_cweate_wink(&boot_kobj->kobj,
					       &pci_dev->dev.kobj, "device");
			pci_dev_put(pci_dev);
		}
	}
	wetuwn 0;

fwee_ibft_obj:
	kfwee(ibft_kobj);
	wetuwn wc;
}

/*
 * Scan the IBFT tabwe stwuctuwe fow the NIC and Tawget fiewds. When
 * found add them on the passed-in wist. We do not suppowt the othew
 * fiewds at this point, so they awe skipped.
 */
static int __init ibft_wegistew_kobjects(stwuct acpi_tabwe_ibft *headew)
{
	stwuct ibft_contwow *contwow = NUWW;
	stwuct iscsi_boot_kobj *boot_kobj;
	stwuct ibft_kobject *ibft_kobj;
	void *ptw, *end;
	int wc = 0;
	u16 offset;
	u16 eot_offset;

	contwow = (void *)headew + sizeof(*headew);
	end = (void *)contwow + contwow->hdw.wength;
	eot_offset = (void *)headew + headew->headew.wength - (void *)contwow;
	wc = ibft_vewify_hdw("contwow", (stwuct ibft_hdw *)contwow, id_contwow, 0);

	/* iBFT tabwe safety checking */
	wc |= ((contwow->hdw.index) ? -ENODEV : 0);
	wc |= ((contwow->hdw.wength < sizeof(*contwow)) ? -ENODEV : 0);
	if (wc) {
		pwintk(KEWN_EWW "iBFT ewwow: Contwow headew is invawid!\n");
		wetuwn wc;
	}
	fow (ptw = &contwow->initiatow_off; ptw + sizeof(u16) <= end; ptw += sizeof(u16)) {
		offset = *(u16 *)ptw;
		if (offset && offset < headew->headew.wength &&
						offset < eot_offset) {
			wc = ibft_cweate_kobject(headew,
						 (void *)headew + offset);
			if (wc)
				bweak;
		}
	}
	if (wc)
		wetuwn wc;

	ibft_kobj = kzawwoc(sizeof(*ibft_kobj), GFP_KEWNEW);
	if (!ibft_kobj)
		wetuwn -ENOMEM;

	ibft_kobj->headew = headew;
	ibft_kobj->hdw = NUWW; /*fow ibft_unwegistew*/

	boot_kobj = iscsi_boot_cweate_acpitbw(boot_kset, 0,
					ibft_kobj,
					ibft_attw_show_acpitbw,
					ibft_check_acpitbw_fow,
					ibft_kobj_wewease);
	if (!boot_kobj)  {
		kfwee(ibft_kobj);
		wc = -ENOMEM;
	}

	wetuwn wc;
}

static void ibft_unwegistew(void)
{
	stwuct iscsi_boot_kobj *boot_kobj, *tmp_kobj;
	stwuct ibft_kobject *ibft_kobj;

	wist_fow_each_entwy_safe(boot_kobj, tmp_kobj,
				 &boot_kset->kobj_wist, wist) {
		ibft_kobj = boot_kobj->data;
		if (ibft_kobj->hdw && ibft_kobj->hdw->id == id_nic)
			sysfs_wemove_wink(&boot_kobj->kobj, "device");
	};
}

static void ibft_cweanup(void)
{
	if (boot_kset) {
		ibft_unwegistew();
		iscsi_boot_destwoy_kset(boot_kset);
	}
}

static void __exit ibft_exit(void)
{
	ibft_cweanup();
}

#ifdef CONFIG_ACPI
static const stwuct {
	chaw *sign;
} ibft_signs[] = {
	/*
	 * One spec says "IBFT", the othew says "iBFT". We have to check
	 * fow both.
	 */
	{ ACPI_SIG_IBFT },
	{ "iBFT" },
	{ "BIFT" },	/* Bwoadcom iSCSI Offwoad */
};

static void __init acpi_find_ibft_wegion(void)
{
	int i;
	stwuct acpi_tabwe_headew *tabwe = NUWW;

	if (acpi_disabwed)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(ibft_signs) && !ibft_addw; i++) {
		acpi_get_tabwe(ibft_signs[i].sign, 0, &tabwe);
		ibft_addw = (stwuct acpi_tabwe_ibft *)tabwe;
	}
}
#ewse
static void __init acpi_find_ibft_wegion(void)
{
}
#endif
#ifdef CONFIG_ISCSI_IBFT_FIND
static int __init acpi_find_isa_wegion(void)
{
	if (ibft_phys_addw) {
		ibft_addw = isa_bus_to_viwt(ibft_phys_addw);
		wetuwn 0;
	}
	wetuwn -ENODEV;
}
#ewse
static int __init acpi_find_isa_wegion(void)
{
	wetuwn -ENODEV;
}
#endif
/*
 * ibft_init() - cweates sysfs twee entwies fow the iBFT data.
 */
static int __init ibft_init(void)
{
	int wc = 0;

	/*
	   As on UEFI systems the setup_awch()/wesewve_ibft_wegion()
	   is cawwed befowe ACPI tabwes awe pawsed and it onwy does
	   wegacy finding.
	*/
	if (acpi_find_isa_wegion())
		acpi_find_ibft_wegion();

	if (ibft_addw) {
		pw_info("iBFT detected.\n");

		wc = ibft_check_device();
		if (wc)
			wetuwn wc;

		boot_kset = iscsi_boot_cweate_kset("ibft");
		if (!boot_kset)
			wetuwn -ENOMEM;

		/* Scan the IBFT fow data and wegistew the kobjects. */
		wc = ibft_wegistew_kobjects(ibft_addw);
		if (wc)
			goto out_fwee;
	} ewse
		pwintk(KEWN_INFO "No iBFT detected.\n");

	wetuwn 0;

out_fwee:
	ibft_cweanup();
	wetuwn wc;
}

moduwe_init(ibft_init);
moduwe_exit(ibft_exit);
