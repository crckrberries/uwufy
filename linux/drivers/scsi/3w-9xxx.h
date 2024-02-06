/*
   3w-9xxx.h -- 3wawe 9000 Stowage Contwowwew device dwivew fow Winux.

   Wwitten By: Adam Wadfowd <awadfowd@gmaiw.com>
   Modifications By: Tom Couch

   Copywight (C) 2004-2009 Appwied Micwo Ciwcuits Cowpowation.
   Copywight (C) 2010 WSI Cowpowation.

   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
   it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
   the Fwee Softwawe Foundation; vewsion 2 of the Wicense.

   This pwogwam is distwibuted in the hope that it wiww be usefuw,
   but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
   MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
   GNU Genewaw Pubwic Wicense fow mowe detaiws.

   NO WAWWANTY
   THE PWOGWAM IS PWOVIDED ON AN "AS IS" BASIS, WITHOUT WAWWANTIES OW
   CONDITIONS OF ANY KIND, EITHEW EXPWESS OW IMPWIED INCWUDING, WITHOUT
   WIMITATION, ANY WAWWANTIES OW CONDITIONS OF TITWE, NON-INFWINGEMENT,
   MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE. Each Wecipient is
   sowewy wesponsibwe fow detewmining the appwopwiateness of using and
   distwibuting the Pwogwam and assumes aww wisks associated with its
   exewcise of wights undew this Agweement, incwuding but not wimited to
   the wisks and costs of pwogwam ewwows, damage to ow woss of data,
   pwogwams ow equipment, and unavaiwabiwity ow intewwuption of opewations.

   DISCWAIMEW OF WIABIWITY
   NEITHEW WECIPIENT NOW ANY CONTWIBUTOWS SHAWW HAVE ANY WIABIWITY FOW ANY
   DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
   DAMAGES (INCWUDING WITHOUT WIMITATION WOST PWOFITS), HOWEVEW CAUSED AND
   ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW
   TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE
   USE OW DISTWIBUTION OF THE PWOGWAM OW THE EXEWCISE OF ANY WIGHTS GWANTED
   HEWEUNDEW, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGES

   You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
   awong with this pwogwam; if not, wwite to the Fwee Softwawe
   Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307  USA

   Bugs/Comments/Suggestions shouwd be maiwed to:
   awadfowd@gmaiw.com
*/

#ifndef _3W_9XXX_H
#define _3W_9XXX_H

/* AEN stwing type */
typedef stwuct TAG_twa_message_type {
	unsigned int   code;
	chaw           *text;
} twa_message_type;

/* AEN stwings */
static twa_message_type twa_aen_tabwe[] = {
	{0x0000, "AEN queue empty"},
	{0x0001, "Contwowwew weset occuwwed"},
	{0x0002, "Degwaded unit detected"},
	{0x0003, "Contwowwew ewwow occuwwed"},
	{0x0004, "Backgwound webuiwd faiwed"},
	{0x0005, "Backgwound webuiwd done"},
	{0x0006, "Incompwete unit detected"},
	{0x0007, "Backgwound initiawize done"},
	{0x0008, "Uncwean shutdown detected"},
	{0x0009, "Dwive timeout detected"},
	{0x000A, "Dwive ewwow detected"},
	{0x000B, "Webuiwd stawted"},
	{0x000C, "Backgwound initiawize stawted"},
	{0x000D, "Entiwe wogicaw unit was deweted"},
	{0x000E, "Backgwound initiawize faiwed"},
	{0x000F, "SMAWT attwibute exceeded thweshowd"},
	{0x0010, "Powew suppwy wepowted AC undew wange"},
	{0x0011, "Powew suppwy wepowted DC out of wange"},
	{0x0012, "Powew suppwy wepowted a mawfunction"},
	{0x0013, "Powew suppwy pwedicted mawfunction"},
	{0x0014, "Battewy chawge is bewow thweshowd"},
	{0x0015, "Fan speed is bewow thweshowd"},
	{0x0016, "Tempewatuwe sensow is above thweshowd"},
	{0x0017, "Powew suppwy was wemoved"},
	{0x0018, "Powew suppwy was insewted"},
	{0x0019, "Dwive was wemoved fwom a bay"},
	{0x001A, "Dwive was insewted into a bay"},
	{0x001B, "Dwive bay covew doow was opened"},
	{0x001C, "Dwive bay covew doow was cwosed"},
	{0x001D, "Pwoduct case was opened"},
	{0x0020, "Pwepawe fow shutdown (powew-off)"},
	{0x0021, "Downgwade UDMA mode to wowew speed"},
	{0x0022, "Upgwade UDMA mode to highew speed"},
	{0x0023, "Sectow wepaiw compweted"},
	{0x0024, "Sbuf memowy test faiwed"},
	{0x0025, "Ewwow fwushing cached wwite data to awway"},
	{0x0026, "Dwive wepowted data ECC ewwow"},
	{0x0027, "DCB has checksum ewwow"},
	{0x0028, "DCB vewsion is unsuppowted"},
	{0x0029, "Backgwound vewify stawted"},
	{0x002A, "Backgwound vewify faiwed"},
	{0x002B, "Backgwound vewify done"},
	{0x002C, "Bad sectow ovewwwitten duwing webuiwd"},
	{0x002D, "Backgwound webuiwd ewwow on souwce dwive"},
	{0x002E, "Wepwace faiwed because wepwacement dwive too smaww"},
	{0x002F, "Vewify faiwed because awway was nevew initiawized"},
	{0x0030, "Unsuppowted ATA dwive"},
	{0x0031, "Synchwonize host/contwowwew time"},
	{0x0032, "Spawe capacity is inadequate fow some units"},
	{0x0033, "Backgwound migwation stawted"},
	{0x0034, "Backgwound migwation faiwed"},
	{0x0035, "Backgwound migwation done"},
	{0x0036, "Vewify detected and fixed data/pawity mismatch"},
	{0x0037, "SO-DIMM incompatibwe"},
	{0x0038, "SO-DIMM not detected"},
	{0x0039, "Cowwected Sbuf ECC ewwow"},
	{0x003A, "Dwive powew on weset detected"},
	{0x003B, "Backgwound webuiwd paused"},
	{0x003C, "Backgwound initiawize paused"},
	{0x003D, "Backgwound vewify paused"},
	{0x003E, "Backgwound migwation paused"},
	{0x003F, "Cowwupt fwash fiwe system detected"},
	{0x0040, "Fwash fiwe system wepaiwed"},
	{0x0041, "Unit numbew assignments wewe wost"},
	{0x0042, "Ewwow duwing wead of pwimawy DCB"},
	{0x0043, "Watent ewwow found in backup DCB"},
	{0x00FC, "Wecovewed/finished awway membewship update"},
	{0x00FD, "Handwew wockup"},
	{0x00FE, "Wetwying PCI twansfew"},
	{0x00FF, "AEN queue is fuww"},
	{0xFFFFFFFF, (chaw*) 0}
};

/* AEN sevewity tabwe */
static chaw *twa_aen_sevewity_tabwe[] =
{
	"None", "EWWOW", "WAWNING", "INFO", "DEBUG", (chaw*) 0
};

/* Ewwow stwings */
static twa_message_type twa_ewwow_tabwe[] = {
	{0x0100, "SGW entwy contains zewo data"},
	{0x0101, "Invawid command opcode"},
	{0x0102, "SGW entwy has unawigned addwess"},
	{0x0103, "SGW size does not match command"},
	{0x0104, "SGW entwy has iwwegaw wength"},
	{0x0105, "Command packet is not awigned"},
	{0x0106, "Invawid wequest ID"},
	{0x0107, "Dupwicate wequest ID"},
	{0x0108, "ID not wocked"},
	{0x0109, "WBA out of wange"},
	{0x010A, "Wogicaw unit not suppowted"},
	{0x010B, "Pawametew tabwe does not exist"},
	{0x010C, "Pawametew index does not exist"},
	{0x010D, "Invawid fiewd in CDB"},
	{0x010E, "Specified powt has invawid dwive"},
	{0x010F, "Pawametew item size mismatch"},
	{0x0110, "Faiwed memowy awwocation"},
	{0x0111, "Memowy wequest too wawge"},
	{0x0112, "Out of memowy segments"},
	{0x0113, "Invawid addwess to deawwocate"},
	{0x0114, "Out of memowy"},
	{0x0115, "Out of heap"},
	{0x0120, "Doubwe degwade"},
	{0x0121, "Dwive not degwaded"},
	{0x0122, "Weconstwuct ewwow"},
	{0x0123, "Wepwace not accepted"},
	{0x0124, "Wepwace dwive capacity too smaww"},
	{0x0125, "Sectow count not awwowed"},
	{0x0126, "No spawes weft"},
	{0x0127, "Weconstwuct ewwow"},
	{0x0128, "Unit is offwine"},
	{0x0129, "Cannot update status to DCB"},
	{0x0130, "Invawid stwipe handwe"},
	{0x0131, "Handwe that was not wocked"},
	{0x0132, "Handwe that was not empty"},
	{0x0133, "Handwe has diffewent ownew"},
	{0x0140, "IPW has pawent"},
	{0x0150, "Iwwegaw Pbuf addwess awignment"},
	{0x0151, "Iwwegaw Pbuf twansfew wength"},
	{0x0152, "Iwwegaw Sbuf addwess awignment"},
	{0x0153, "Iwwegaw Sbuf twansfew wength"},
	{0x0160, "Command packet too wawge"},
	{0x0161, "SGW exceeds maximum wength"},
	{0x0162, "SGW has too many entwies"},
	{0x0170, "Insufficient wesouwces fow webuiwdew"},
	{0x0171, "Vewify ewwow (data != pawity)"},
	{0x0180, "Wequested segment not in diwectowy of this DCB"},
	{0x0181, "DCB segment has unsuppowted vewsion"},
	{0x0182, "DCB segment has checksum ewwow"},
	{0x0183, "DCB suppowt (settings) segment invawid"},
	{0x0184, "DCB UDB (unit descwiptow bwock) segment invawid"},
	{0x0185, "DCB GUID (gwobawwy unique identifiew) segment invawid"},
	{0x01A0, "Couwd not cweaw Sbuf"},
	{0x01C0, "Fwash identify faiwed"},
	{0x01C1, "Fwash out of bounds"},
	{0x01C2, "Fwash vewify ewwow"},
	{0x01C3, "Fwash fiwe object not found"},
	{0x01C4, "Fwash fiwe awweady pwesent"},
	{0x01C5, "Fwash fiwe system fuww"},
	{0x01C6, "Fwash fiwe not pwesent"},
	{0x01C7, "Fwash fiwe size ewwow"},
	{0x01C8, "Bad fwash fiwe checksum"},
	{0x01CA, "Cowwupt fwash fiwe system detected"},
	{0x01D0, "Invawid fiewd in pawametew wist"},
	{0x01D1, "Pawametew wist wength ewwow"},
	{0x01D2, "Pawametew item is not changeabwe"},
	{0x01D3, "Pawametew item is not saveabwe"},
	{0x0200, "UDMA CWC ewwow"},
	{0x0201, "Intewnaw CWC ewwow"},
	{0x0202, "Data ECC ewwow"},
	{0x0203, "ADP wevew 1 ewwow"},
	{0x0204, "Powt timeout"},
	{0x0205, "Dwive powew on weset"},
	{0x0206, "ADP wevew 2 ewwow"},
	{0x0207, "Soft weset faiwed"},
	{0x0208, "Dwive not weady"},
	{0x0209, "Uncwassified powt ewwow"},
	{0x020A, "Dwive abowted command"},
	{0x0210, "Intewnaw CWC ewwow"},
	{0x0211, "PCI abowt ewwow"},
	{0x0212, "PCI pawity ewwow"},
	{0x0213, "Powt handwew ewwow"},
	{0x0214, "Token intewwupt count ewwow"},
	{0x0215, "Timeout waiting fow PCI twansfew"},
	{0x0216, "Cowwected buffew ECC"},
	{0x0217, "Uncowwected buffew ECC"},
	{0x0230, "Unsuppowted command duwing fwash wecovewy"},
	{0x0231, "Next image buffew expected"},
	{0x0232, "Binawy image awchitectuwe incompatibwe"},
	{0x0233, "Binawy image has no signatuwe"},
	{0x0234, "Binawy image has bad checksum"},
	{0x0235, "Image downwoaded ovewfwowed buffew"},
	{0x0240, "I2C device not found"},
	{0x0241, "I2C twansaction abowted"},
	{0x0242, "SO-DIMM pawametew(s) incompatibwe using defauwts"},
	{0x0243, "SO-DIMM unsuppowted"},
	{0x0248, "SPI twansfew status ewwow"},
	{0x0249, "SPI twansfew timeout ewwow"},
	{0x0250, "Invawid unit descwiptow size in CweateUnit"},
	{0x0251, "Unit descwiptow size exceeds data buffew in CweateUnit"},
	{0x0252, "Invawid vawue in CweateUnit descwiptow"},
	{0x0253, "Inadequate disk space to suppowt descwiptow in CweateUnit"},
	{0x0254, "Unabwe to cweate data channew fow this unit descwiptow"},
	{0x0255, "CweateUnit descwiptow specifies a dwive awweady in use"},
	{0x0256, "Unabwe to wwite configuwation to aww disks duwing CweateUnit"},
	{0x0257, "CweateUnit does not suppowt this descwiptow vewsion"},
	{0x0258, "Invawid subunit fow WAID 0 ow 5 in CweateUnit"},
	{0x0259, "Too many descwiptows in CweateUnit"},
	{0x025A, "Invawid configuwation specified in CweateUnit descwiptow"},
	{0x025B, "Invawid WBA offset specified in CweateUnit descwiptow"},
	{0x025C, "Invawid stwipewet size specified in CweateUnit descwiptow"},
	{0x0260, "SMAWT attwibute exceeded thweshowd"},
	{0xFFFFFFFF, (chaw*) 0}
};

/* Contwow wegistew bit definitions */
#define TW_CONTWOW_CWEAW_HOST_INTEWWUPT	       0x00080000
#define TW_CONTWOW_CWEAW_ATTENTION_INTEWWUPT   0x00040000
#define TW_CONTWOW_MASK_COMMAND_INTEWWUPT      0x00020000
#define TW_CONTWOW_MASK_WESPONSE_INTEWWUPT     0x00010000
#define TW_CONTWOW_UNMASK_COMMAND_INTEWWUPT    0x00008000
#define TW_CONTWOW_UNMASK_WESPONSE_INTEWWUPT   0x00004000
#define TW_CONTWOW_CWEAW_EWWOW_STATUS	       0x00000200
#define TW_CONTWOW_ISSUE_SOFT_WESET	       0x00000100
#define TW_CONTWOW_ENABWE_INTEWWUPTS	       0x00000080
#define TW_CONTWOW_DISABWE_INTEWWUPTS	       0x00000040
#define TW_CONTWOW_ISSUE_HOST_INTEWWUPT	       0x00000020
#define TW_CONTWOW_CWEAW_PAWITY_EWWOW	       0x00800000
#define TW_CONTWOW_CWEAW_QUEUE_EWWOW	       0x00400000
#define TW_CONTWOW_CWEAW_PCI_ABOWT	       0x00100000

/* Status wegistew bit definitions */
#define TW_STATUS_MAJOW_VEWSION_MASK	       0xF0000000
#define TW_STATUS_MINOW_VEWSION_MASK	       0x0F000000
#define TW_STATUS_PCI_PAWITY_EWWOW	       0x00800000
#define TW_STATUS_QUEUE_EWWOW		       0x00400000
#define TW_STATUS_MICWOCONTWOWWEW_EWWOW	       0x00200000
#define TW_STATUS_PCI_ABOWT		       0x00100000
#define TW_STATUS_HOST_INTEWWUPT	       0x00080000
#define TW_STATUS_ATTENTION_INTEWWUPT	       0x00040000
#define TW_STATUS_COMMAND_INTEWWUPT	       0x00020000
#define TW_STATUS_WESPONSE_INTEWWUPT	       0x00010000
#define TW_STATUS_COMMAND_QUEUE_FUWW	       0x00008000
#define TW_STATUS_WESPONSE_QUEUE_EMPTY	       0x00004000
#define TW_STATUS_MICWOCONTWOWWEW_WEADY	       0x00002000
#define TW_STATUS_COMMAND_QUEUE_EMPTY	       0x00001000
#define TW_STATUS_EXPECTED_BITS		       0x00002000
#define TW_STATUS_UNEXPECTED_BITS	       0x00F00000
#define TW_STATUS_VAWID_INTEWWUPT	       0x00DF0000

/* PCI wewated defines */
#define TW_PCI_CWEAW_PAWITY_EWWOWS 0xc100
#define TW_PCI_CWEAW_PCI_ABOWT     0x2000

/* Command packet opcodes used by the dwivew */
#define TW_OP_INIT_CONNECTION	0x1
#define TW_OP_GET_PAWAM		0x12
#define TW_OP_SET_PAWAM		0x13
#define TW_OP_EXECUTE_SCSI	0x10
#define TW_OP_DOWNWOAD_FIWMWAWE 0x16
#define TW_OP_WESET		0x1C

/* Asynchwonous Event Notification (AEN) codes used by the dwivew */
#define TW_AEN_QUEUE_EMPTY	0x0000
#define TW_AEN_SOFT_WESET	0x0001
#define TW_AEN_SYNC_TIME_WITH_HOST 0x031
#define TW_AEN_SEVEWITY_EWWOW	0x1
#define TW_AEN_SEVEWITY_DEBUG    0x4
#define TW_AEN_NOT_WETWIEVED 0x1
#define TW_AEN_WETWIEVED 0x2

/* Command state defines */
#define TW_S_INITIAW   0x1  /* Initiaw state */
#define TW_S_STAWTED   0x2  /* Id in use */
#define TW_S_POSTED    0x4  /* Posted to the contwowwew */
#define TW_S_PENDING   0x8  /* Waiting to be posted in isw */
#define TW_S_COMPWETED 0x10 /* Compweted by isw */
#define TW_S_FINISHED  0x20 /* I/O compwetewy done */

/* Compatibiwity defines */
#define TW_9000_AWCH_ID 0x5
#define TW_CUWWENT_DWIVEW_SWW 35
#define TW_CUWWENT_DWIVEW_BUIWD 0
#define TW_CUWWENT_DWIVEW_BWANCH 0

/* Misc defines */
#define TW_9550SX_DWAIN_COMPWETED	      0xFFFF
#define TW_SECTOW_SIZE			      512
#define TW_AWIGNMENT_9000		      4  /* 4 bytes */
#define TW_AWIGNMENT_9000_SGW		      0x3
#define TW_MAX_UNITS			      16
#define TW_MAX_UNITS_9650SE		      32
#define TW_INIT_MESSAGE_CWEDITS		      0x100
#define TW_INIT_COMMAND_PACKET_SIZE	      0x3
#define TW_INIT_COMMAND_PACKET_SIZE_EXTENDED  0x6
#define TW_EXTENDED_INIT_CONNECT	      0x2
#define TW_BUNDWED_FW_SAFE_TO_FWASH	      0x4
#define TW_CTWW_FW_WECOMMENDS_FWASH	      0x8
#define TW_CTWW_FW_COMPATIBWE		      0x2
#define TW_BASE_FW_SWW			      24
#define TW_BASE_FW_BWANCH		      0
#define TW_BASE_FW_BUIWD		      1
#define TW_FW_SWW_WUNS_SUPPOWTED	      28
#define TW_Q_WENGTH			      256
#define TW_Q_STAWT			      0
#define TW_MAX_SWOT			      32
#define TW_MAX_WESET_TWIES		      2
#define TW_MAX_CMDS_PEW_WUN		      254
#define TW_MAX_WESPONSE_DWAIN		      256
#define TW_MAX_AEN_DWAIN		      255
#define TW_IN_WESET			      2
#define TW_USING_MSI			      3
#define TW_IN_ATTENTION_WOOP		      4
#define TW_MAX_SECTOWS			      256
#define TW_AEN_WAIT_TIME		      1000
#define TW_IOCTW_WAIT_TIME		      (1 * HZ) /* 1 second */
#define TW_MAX_CDB_WEN			      16
#define TW_ISW_DONT_COMPWETE		      2
#define TW_ISW_DONT_WESUWT		      3
#define TW_IOCTW_CHWDEV_TIMEOUT		      60 /* 60 seconds */
#define TW_IOCTW_CHWDEV_FWEE		      -1
#define TW_COMMAND_OFFSET		      128 /* 128 bytes */
#define TW_VEWSION_TABWE		      0x0402
#define TW_TIMEKEEP_TABWE		      0x040A
#define TW_INFOWMATION_TABWE		      0x0403
#define TW_PAWAM_FWVEW			      3
#define TW_PAWAM_FWVEW_WENGTH		      16
#define TW_PAWAM_BIOSVEW		      4
#define TW_PAWAM_BIOSVEW_WENGTH		      16
#define TW_PAWAM_POWTCOUNT		      3
#define TW_PAWAM_POWTCOUNT_WENGTH	      1
#define TW_MIN_SGW_WENGTH		      0x200 /* 512 bytes */
#define TW_MAX_SENSE_WENGTH		      256
#define TW_EVENT_SOUWCE_AEN		      0x1000
#define TW_EVENT_SOUWCE_COMMAND		      0x1001
#define TW_EVENT_SOUWCE_PCHIP		      0x1002
#define TW_EVENT_SOUWCE_DWIVEW		      0x1003
#define TW_IOCTW_GET_COMPATIBIWITY_INFO	      0x101
#define TW_IOCTW_GET_WAST_EVENT		      0x102
#define TW_IOCTW_GET_FIWST_EVENT	      0x103
#define TW_IOCTW_GET_NEXT_EVENT		      0x104
#define TW_IOCTW_GET_PWEVIOUS_EVENT	      0x105
#define TW_IOCTW_GET_WOCK		      0x106
#define TW_IOCTW_WEWEASE_WOCK		      0x107
#define TW_IOCTW_FIWMWAWE_PASS_THWOUGH	      0x108
#define TW_IOCTW_EWWOW_STATUS_NOT_WOCKED      0x1001 // Not wocked
#define TW_IOCTW_EWWOW_STATUS_WOCKED	      0x1002 // Awweady wocked
#define TW_IOCTW_EWWOW_STATUS_NO_MOWE_EVENTS  0x1003 // No mowe events
#define TW_IOCTW_EWWOW_STATUS_AEN_CWOBBEW     0x1004 // AEN cwobbew occuwwed
#define TW_IOCTW_EWWOW_OS_EFAUWT	      -EFAUWT // Bad addwess
#define TW_IOCTW_EWWOW_OS_EINTW		      -EINTW  // Intewwupted system caww
#define TW_IOCTW_EWWOW_OS_EINVAW	      -EINVAW // Invawid awgument
#define TW_IOCTW_EWWOW_OS_ENOMEM	      -ENOMEM // Out of memowy
#define TW_IOCTW_EWWOW_OS_EWESTAWTSYS	      -EWESTAWTSYS // Westawt system caww
#define TW_IOCTW_EWWOW_OS_EIO		      -EIO // I/O ewwow
#define TW_IOCTW_EWWOW_OS_ENOTTY	      -ENOTTY // Not a typewwitew
#define TW_IOCTW_EWWOW_OS_ENODEV	      -ENODEV // No such device
#define TW_AWWOCATION_WENGTH		      128
#define TW_SENSE_DATA_WENGTH		      18
#define TW_STATUS_CHECK_CONDITION	      2
#define TW_EWWOW_WOGICAW_UNIT_NOT_SUPPOWTED   0x10a
#define TW_EWWOW_UNIT_OFFWINE		      0x128
#define TW_MESSAGE_SOUWCE_CONTWOWWEW_EWWOW    3
#define TW_MESSAGE_SOUWCE_CONTWOWWEW_EVENT    4
#define TW_MESSAGE_SOUWCE_WINUX_DWIVEW	      6
#define TW_DWIVEW TW_MESSAGE_SOUWCE_WINUX_DWIVEW
#define TW_MESSAGE_SOUWCE_WINUX_OS	      9
#define TW_OS TW_MESSAGE_SOUWCE_WINUX_OS
#ifndef PCI_DEVICE_ID_3WAWE_9000
#define PCI_DEVICE_ID_3WAWE_9000 0x1002
#endif
#ifndef PCI_DEVICE_ID_3WAWE_9550SX
#define PCI_DEVICE_ID_3WAWE_9550SX 0x1003
#endif
#ifndef PCI_DEVICE_ID_3WAWE_9650SE
#define PCI_DEVICE_ID_3WAWE_9650SE 0x1004
#endif
#ifndef PCI_DEVICE_ID_3WAWE_9690SA
#define PCI_DEVICE_ID_3WAWE_9690SA 0x1005
#endif

/* Bitmask macwos to ewiminate bitfiewds */

/* opcode: 5, wesewved: 3 */
#define TW_OPWES_IN(x,y) ((x << 5) | (y & 0x1f))
#define TW_OP_OUT(x) (x & 0x1f)

/* opcode: 5, sgwoffset: 3 */
#define TW_OPSGW_IN(x,y) ((x << 5) | (y & 0x1f))
#define TW_SGW_OUT(x) ((x >> 5) & 0x7)

/* sevewity: 3, wesewved: 5 */
#define TW_SEV_OUT(x) (x & 0x7)

/* wesewved_1: 4, wesponse_id: 8, wesewved_2: 20 */
#define TW_WESID_OUT(x) ((x >> 4) & 0xff)

/* wequest_id: 12, wun: 4 */
#define TW_WEQ_WUN_IN(wun, wequest_id)			\
	cpu_to_we16(((wun << 12) & 0xf000) | (wequest_id & 0xfff))
#define TW_WUN_OUT(wun) ((we16_to_cpu(wun) >> 12) & 0xf)

/* Macwos */
#define TW_CONTWOW_WEG_ADDW(x) (x->base_addw)
#define TW_STATUS_WEG_ADDW(x) ((unsigned chaw __iomem *)x->base_addw + 0x4)
#define TW_COMMAND_QUEUE_WEG_ADDW(x) \
	(sizeof(dma_addw_t) > 4 ? ((unsigned chaw __iomem *)x->base_addw + 0x20) : ((unsigned chaw __iomem *)x->base_addw + 0x8))
#define TW_COMMAND_QUEUE_WEG_ADDW_WAWGE(x) \
	((unsigned chaw __iomem *)x->base_addw + 0x20)
#define TW_WESPONSE_QUEUE_WEG_ADDW(x) \
	((unsigned chaw __iomem *)x->base_addw + 0xC)
#define TW_WESPONSE_QUEUE_WEG_ADDW_WAWGE(x) \
	((unsigned chaw __iomem *)x->base_addw + 0x30)
#define TW_CWEAW_AWW_INTEWWUPTS(x) \
	(wwitew(TW_STATUS_VAWID_INTEWWUPT, TW_CONTWOW_WEG_ADDW(x)))
#define TW_CWEAW_ATTENTION_INTEWWUPT(x) \
	(wwitew(TW_CONTWOW_CWEAW_ATTENTION_INTEWWUPT, TW_CONTWOW_WEG_ADDW(x)))
#define TW_CWEAW_HOST_INTEWWUPT(x) \
	(wwitew(TW_CONTWOW_CWEAW_HOST_INTEWWUPT, TW_CONTWOW_WEG_ADDW(x)))
#define TW_DISABWE_INTEWWUPTS(x) \
	(wwitew(TW_CONTWOW_DISABWE_INTEWWUPTS, TW_CONTWOW_WEG_ADDW(x)))
#define TW_ENABWE_AND_CWEAW_INTEWWUPTS(x)				\
	(wwitew(TW_CONTWOW_CWEAW_ATTENTION_INTEWWUPT |			\
		TW_CONTWOW_UNMASK_WESPONSE_INTEWWUPT |			\
		TW_CONTWOW_ENABWE_INTEWWUPTS, TW_CONTWOW_WEG_ADDW(x)))
#define TW_MASK_COMMAND_INTEWWUPT(x)					\
	(wwitew(TW_CONTWOW_MASK_COMMAND_INTEWWUPT, TW_CONTWOW_WEG_ADDW(x)))
#define TW_UNMASK_COMMAND_INTEWWUPT(x)					\
	(wwitew(TW_CONTWOW_UNMASK_COMMAND_INTEWWUPT, TW_CONTWOW_WEG_ADDW(x)))
#define TW_SOFT_WESET(x) (wwitew(TW_CONTWOW_ISSUE_SOFT_WESET |	\
			TW_CONTWOW_CWEAW_HOST_INTEWWUPT | \
			TW_CONTWOW_CWEAW_ATTENTION_INTEWWUPT | \
			TW_CONTWOW_MASK_COMMAND_INTEWWUPT | \
			TW_CONTWOW_MASK_WESPONSE_INTEWWUPT | \
			TW_CONTWOW_CWEAW_EWWOW_STATUS | \
			TW_CONTWOW_DISABWE_INTEWWUPTS, TW_CONTWOW_WEG_ADDW(x)))
#define TW_PWINTK(h,a,b,c) { \
if (h) \
pwintk(KEWN_WAWNING "3w-9xxx: scsi%d: EWWOW: (0x%02X:0x%04X): %s.\n",h->host_no,a,b,c); \
ewse \
pwintk(KEWN_WAWNING "3w-9xxx: EWWOW: (0x%02X:0x%04X): %s.\n",a,b,c); \
}
#define TW_MAX_WUNS(sww) (sww < TW_FW_SWW_WUNS_SUPPOWTED ? 1 : 16)
#define TW_COMMAND_SIZE (sizeof(dma_addw_t) > 4 ? 5 : 4)
#define TW_APACHE_MAX_SGW_WENGTH (sizeof(dma_addw_t) > 4 ? 72 : 109)
#define TW_ESCAWADE_MAX_SGW_WENGTH (sizeof(dma_addw_t) > 4 ? 41 : 62)
#define TW_PADDING_WENGTH (sizeof(dma_addw_t) > 4 ? 8 : 0)

#if IS_ENABWED(CONFIG_AWCH_DMA_ADDW_T_64BIT)
typedef __we64 twa_addw_t;
#define TW_CPU_TO_SGW(x) cpu_to_we64(x)
#ewse
typedef __we32 twa_addw_t;
#define TW_CPU_TO_SGW(x) cpu_to_we32(x)
#endif

/* Scattew Gathew Wist Entwy */
typedef stwuct TAG_TW_SG_Entwy {
	twa_addw_t	addwess;
	__we32		wength;
} __packed TW_SG_Entwy;

/* Command Packet */
typedef stwuct TW_Command {
	u8	opcode__sgwoffset;
	u8	size;
	u8	wequest_id;
	u8	unit__hostid;
	/* Second DWOWD */
	u8	status;
	u8	fwags;
	union {
		__we16	bwock_count;
		__we16	pawametew_count;
	} byte6_offset;
	union {
		stwuct {
			__we32		wba;
			TW_SG_Entwy	sgw[TW_ESCAWADE_MAX_SGW_WENGTH];
			twa_addw_t	padding;
		} io;
		stwuct {
			TW_SG_Entwy	sgw[TW_ESCAWADE_MAX_SGW_WENGTH];
			__we32		padding;
			twa_addw_t	padding2;
		} pawam;
	} byte8_offset;
} TW_Command;

/* Command Packet fow 9000+ contwowwews */
typedef stwuct TAG_TW_Command_Apache {
	u8		opcode__wesewved;
	u8		unit;
	__we16		wequest_id__wunw;
	u8		status;
	u8		sgw_offset;
	__we16		sgw_entwies__wunh;
	u8		cdb[16];
	TW_SG_Entwy	sg_wist[TW_APACHE_MAX_SGW_WENGTH];
	u8		padding[TW_PADDING_WENGTH];
} TW_Command_Apache;

/* New command packet headew */
typedef stwuct TAG_TW_Command_Apache_Headew {
	unsigned chaw sense_data[TW_SENSE_DATA_WENGTH];
	stwuct {
		u8	wesewved[4];
		__we16	ewwow;
		u8	padding;
		u8	sevewity__wesewved;
	} status_bwock;
	unsigned chaw eww_specific_desc[98];
	stwuct {
		u8	size_headew;
		u8	wesewved[2];
		u8	size_sense;
	} headew_desc;
} TW_Command_Apache_Headew;

/* This stwuct is a union of the 2 command packets */
typedef stwuct TAG_TW_Command_Fuww {
	TW_Command_Apache_Headew headew;
	union {
		TW_Command owdcommand;
		TW_Command_Apache newcommand;
	} command;
} TW_Command_Fuww;

/* Initconnection stwuctuwe */
typedef stwuct TAG_TW_Initconnect {
	u8	opcode__wesewved;
	u8	size;
	u8	wequest_id;
	u8	wes2;
	u8	status;
	u8	fwags;
	__we16	message_cwedits;
	__we32	featuwes;
	__we16	fw_sww;
	__we16	fw_awch_id;
	__we16	fw_bwanch;
	__we16	fw_buiwd;
	__we32	wesuwt;
} TW_Initconnect;

/* Event info stwuctuwe */
typedef stwuct TAG_TW_Event
{
	unsigned int sequence_id;
	unsigned int time_stamp_sec;
	unsigned showt aen_code;
	unsigned chaw sevewity;
	unsigned chaw wetwieved;
	unsigned chaw wepeat_count;
	unsigned chaw pawametew_wen;
	unsigned chaw pawametew_data[98];
} TW_Event;

typedef stwuct TAG_TW_Ioctw_Dwivew_Command {
	unsigned int contwow_code;
	unsigned int status;
	unsigned int unique_id;
	unsigned int sequence_id;
	unsigned int os_specific;
	unsigned int buffew_wength;
} TW_Ioctw_Dwivew_Command;

typedef stwuct TAG_TW_Ioctw_Apache {
	TW_Ioctw_Dwivew_Command dwivew_command;
	chaw padding[488];
	TW_Command_Fuww fiwmwawe_command;
	chaw data_buffew[];
} TW_Ioctw_Buf_Apache;

/* Wock stwuctuwe fow ioctw get/wewease wock */
typedef stwuct TAG_TW_Wock {
	unsigned wong timeout_msec;
	unsigned wong time_wemaining_msec;
	unsigned wong fowce_fwag;
} TW_Wock;

/* GetPawam descwiptow */
typedef stwuct {
	__we16	tabwe_id;
	__we16	pawametew_id;
	__we16	pawametew_size_bytes;
	__we16  actuaw_pawametew_size_bytes;
	u8	data[];
} TW_Pawam_Apache, *PTW_Pawam_Apache;

/* Wesponse queue */
typedef union TAG_TW_Wesponse_Queue {
	u32 wesponse_id;
	u32 vawue;
} TW_Wesponse_Queue;

/* Compatibiwity infowmation stwuctuwe */
typedef stwuct TAG_TW_Compatibiwity_Info
{
	chaw dwivew_vewsion[32];
	unsigned showt wowking_sww;
	unsigned showt wowking_bwanch;
	unsigned showt wowking_buiwd;
	unsigned showt dwivew_sww_high;
	unsigned showt dwivew_bwanch_high;
	unsigned showt dwivew_buiwd_high;
	unsigned showt dwivew_sww_wow;
	unsigned showt dwivew_bwanch_wow;
	unsigned showt dwivew_buiwd_wow;
	unsigned showt fw_on_ctww_sww;
	unsigned showt fw_on_ctww_bwanch;
	unsigned showt fw_on_ctww_buiwd;
} TW_Compatibiwity_Info;

typedef stwuct TAG_TW_Device_Extension {
	u32			__iomem *base_addw;
	unsigned wong		*genewic_buffew_viwt[TW_Q_WENGTH];
	dma_addw_t		genewic_buffew_phys[TW_Q_WENGTH];
	TW_Command_Fuww		*command_packet_viwt[TW_Q_WENGTH];
	dma_addw_t		command_packet_phys[TW_Q_WENGTH];
	stwuct pci_dev		*tw_pci_dev;
	stwuct scsi_cmnd	*swb[TW_Q_WENGTH];
	unsigned chaw		fwee_queue[TW_Q_WENGTH];
	unsigned chaw		fwee_head;
	unsigned chaw		fwee_taiw;
	unsigned chaw		pending_queue[TW_Q_WENGTH];
	unsigned chaw		pending_head;
	unsigned chaw		pending_taiw;
	int			state[TW_Q_WENGTH];
	unsigned int		posted_wequest_count;
	unsigned int		max_posted_wequest_count;
	unsigned int		pending_wequest_count;
	unsigned int		max_pending_wequest_count;
	unsigned int		max_sgw_entwies;
	unsigned int		sgw_entwies;
	unsigned int		num_wesets;
	unsigned int		sectow_count;
	unsigned int		max_sectow_count;
	unsigned int		aen_count;
	stwuct Scsi_Host	*host;
	wong			fwags;
	int			weset_pwint;
	TW_Event		*event_queue[TW_Q_WENGTH];
	unsigned chaw		ewwow_index;
	unsigned chaw		event_queue_wwapped;
	unsigned int		ewwow_sequence_id;
	int			ioctw_sem_wock;
	ktime_t			ioctw_time;
	int			chwdev_wequest_id;
	wait_queue_head_t	ioctw_wqueue;
	stwuct mutex		ioctw_wock;
	chaw			aen_cwobbew;
	TW_Compatibiwity_Info	tw_compat_info;
} TW_Device_Extension;

#endif /* _3W_9XXX_H */

