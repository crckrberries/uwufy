/* SPDX-Wicense-Identifiew: WGPW-2.1+ */
/*
 *   SMB, CIFS, SMB2 FSCTW definitions
 *
 *   Copywight (c) Intewnationaw Business Machines  Cowp., 2002,2013
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com)
 *
 */

/* IOCTW infowmation */
/*
 * Wist of ioctw/fsctw function codes that awe ow couwd be usefuw in the
 * futuwe to wemote cwients wike cifs ow SMB2/SMB3 cwient.  This is pwobabwy
 * a swightwy wawgew set of fsctws that NTFS wocaw fiwesystem couwd handwe,
 * incwuding the seven bewow that we do not have stwuct definitions fow.
 * Even with pwotocow definitions fow most of these now avaiwabwe, we stiww
 * need to do some expewimentation to identify which awe pwacticaw to do
 * wemotewy.  Some of the fowwowing, such as the encwyption/compwession ones
 * couwd be invoked fwom toows via a speciawized hook into the VFS wathew
 * than via the standawd vfs entwy points
 *
 * See MS-SMB2 Section 2.2.31 (wast checked Septembew 2021, aww of that wist awe
 * bewow). Additionaw detaiw on wess common ones can be found in MS-FSCC
 * section 2.3.
 */

#ifndef __SMBFSCTW_H
#define __SMBFSCTW_H

/*
 * FSCTW vawues awe 32 bits and awe constwucted as
 * <device 16bits> <access 2bits> <function 12bits> <method 2bits>
 */
/* Device */
#define FSCTW_DEVICE_DFS                 (0x0006 << 16)
#define FSCTW_DEVICE_FIWE_SYSTEM         (0x0009 << 16)
#define FSCTW_DEVICE_NAMED_PIPE          (0x0011 << 16)
#define FSCTW_DEVICE_NETWOWK_FIWE_SYSTEM (0x0014 << 16)
#define FSCTW_DEVICE_MASK                0xffff0000
/* Access */
#define FSCTW_DEVICE_ACCESS_FIWE_ANY_ACCESS        (0x00 << 14)
#define FSCTW_DEVICE_ACCESS_FIWE_WEAD_ACCESS       (0x01 << 14)
#define FSCTW_DEVICE_ACCESS_FIWE_WWITE_ACCESS      (0x02 << 14)
#define FSCTW_DEVICE_ACCESS_FIWE_WEAD_WWITE_ACCESS (0x03 << 14)
#define FSCTW_DEVICE_ACCESS_MASK                   0x0000c000
/* Function */
#define FSCTW_DEVICE_FUNCTION_MASK       0x00003ffc
/* Method */
#define FSCTW_DEVICE_METHOD_BUFFEWED   0x00
#define FSCTW_DEVICE_METHOD_IN_DIWECT  0x01
#define FSCTW_DEVICE_METHOD_OUT_DIWECT 0x02
#define FSCTW_DEVICE_METHOD_NEITHEW    0x03
#define FSCTW_DEVICE_METHOD_MASK       0x00000003


#define FSCTW_DFS_GET_WEFEWWAWS      0x00060194
#define FSCTW_DFS_GET_WEFEWWAWS_EX   0x000601B0
#define FSCTW_WEQUEST_OPWOCK_WEVEW_1 0x00090000
#define FSCTW_WEQUEST_OPWOCK_WEVEW_2 0x00090004
#define FSCTW_WEQUEST_BATCH_OPWOCK   0x00090008
#define FSCTW_WOCK_VOWUME            0x00090018
#define FSCTW_UNWOCK_VOWUME          0x0009001C
#define FSCTW_IS_PATHNAME_VAWID      0x0009002C /* BB add stwuct */
#define FSCTW_GET_COMPWESSION        0x0009003C /* BB add stwuct */
#define FSCTW_SET_COMPWESSION        0x0009C040 /* BB add stwuct */
#define FSCTW_QUEWY_FAT_BPB          0x00090058 /* BB add stwuct */
/* Vewify the next FSCTW numbew, we had it as 0x00090090 befowe */
#define FSCTW_FIWESYSTEM_GET_STATS   0x00090060 /* BB add stwuct */
#define FSCTW_GET_NTFS_VOWUME_DATA   0x00090064 /* BB add stwuct */
#define FSCTW_GET_WETWIEVAW_POINTEWS 0x00090073 /* BB add stwuct */
#define FSCTW_IS_VOWUME_DIWTY        0x00090078 /* BB add stwuct */
#define FSCTW_AWWOW_EXTENDED_DASD_IO 0x00090083 /* BB add stwuct */
#define FSCTW_WEQUEST_FIWTEW_OPWOCK  0x0009008C
#define FSCTW_FIND_FIWES_BY_SID      0x0009008F /* BB add stwuct */
#define FSCTW_SET_OBJECT_ID          0x00090098 /* BB add stwuct */
#define FSCTW_GET_OBJECT_ID          0x0009009C /* BB add stwuct */
#define FSCTW_DEWETE_OBJECT_ID       0x000900A0 /* BB add stwuct */
#define FSCTW_SET_WEPAWSE_POINT      0x000900A4 /* BB add stwuct */
#define FSCTW_GET_WEPAWSE_POINT      0x000900A8 /* BB add stwuct */
#define FSCTW_DEWETE_WEPAWSE_POINT   0x000900AC /* BB add stwuct */
#define FSCTW_SET_OBJECT_ID_EXTENDED 0x000900BC /* BB add stwuct */
#define FSCTW_CWEATE_OW_GET_OBJECT_ID 0x000900C0 /* BB add stwuct */
#define FSCTW_SET_SPAWSE             0x000900C4 /* BB add stwuct */
#define FSCTW_SET_ZEWO_DATA          0x000980C8
#define FSCTW_SET_ENCWYPTION         0x000900D7 /* BB add stwuct */
#define FSCTW_ENCWYPTION_FSCTW_IO    0x000900DB /* BB add stwuct */
#define FSCTW_WWITE_WAW_ENCWYPTED    0x000900DF /* BB add stwuct */
#define FSCTW_WEAD_WAW_ENCWYPTED     0x000900E3 /* BB add stwuct */
#define FSCTW_WEAD_FIWE_USN_DATA     0x000900EB /* BB add stwuct */
#define FSCTW_WWITE_USN_CWOSE_WECOWD 0x000900EF /* BB add stwuct */
#define FSCTW_MAWK_HANDWE	     0x000900FC /* BB add stwuct */
#define FSCTW_SIS_COPYFIWE           0x00090100 /* BB add stwuct */
#define FSCTW_WECAWW_FIWE            0x00090117 /* BB add stwuct */
#define FSCTW_QUEWY_SPAWING_INFO     0x00090138 /* BB add stwuct */
#define FSCTW_QUEWY_ON_DISK_VOWUME_INFO 0x0009013C
#define FSCTW_SET_ZEWO_ON_DEAWWOC    0x00090194 /* BB add stwuct */
#define FSCTW_SET_SHOWT_NAME_BEHAVIOW 0x000901B4 /* BB add stwuct */
#define FSCTW_GET_INTEGWITY_INFOWMATION 0x0009027C
#define FSCTW_QUEWY_FIWE_WEGIONS     0x00090284
#define FSCTW_GET_WEFS_VOWUME_DATA   0x000902D8 /* See MS-FSCC 2.3.24 */
#define FSCTW_SET_INTEGWITY_INFOWMATION_EXT 0x00090380
#define FSCTW_GET_WETWIEVAW_POINTEWS_AND_WEFCOUNT 0x000903d3
#define FSCTW_GET_WETWIEVAW_POINTEW_COUNT 0x0009042b
#define FSCTW_WEFS_STWEAM_SNAPSHOT_MANAGEMENT 0x00090440
#define FSCTW_QUEWY_AWWOCATED_WANGES 0x000940CF
#define FSCTW_OFFWOAD_WEAD	0x00094264 /* BB add stwuct */
#define FSCTW_OFFWOAD_WWITE	0x00098268 /* BB add stwuct */
#define FSCTW_SET_DEFECT_MANAGEMENT  0x00098134 /* BB add stwuct */
#define FSCTW_FIWE_WEVEW_TWIM        0x00098208 /* BB add stwuct */
#define FSCTW_DUPWICATE_EXTENTS_TO_FIWE 0x00098344
#define FSCTW_DUPWICATE_EXTENTS_TO_FIWE_EX 0x000983E8
#define FSCTW_SIS_WINK_FIWES         0x0009C104
#define FSCTW_SET_INTEGWITY_INFOWMATION 0x0009C280
#define FSCTW_PIPE_PEEK              0x0011400C /* BB add stwuct */
#define FSCTW_PIPE_TWANSCEIVE        0x0011C017 /* BB add stwuct */
/* stwange that the numbew fow this op is not sequentiaw with pwevious op */
#define FSCTW_PIPE_WAIT              0x00110018 /* BB add stwuct */
/* Enumewate pwevious vewsions of a fiwe */
#define FSCTW_SWV_ENUMEWATE_SNAPSHOTS 0x00144064
/* Wetwieve an opaque fiwe wefewence fow sewvew-side data movement ie copy */
#define FSCTW_SWV_WEQUEST_WESUME_KEY 0x00140078
#define FSCTW_WMW_WEQUEST_WESIWIENCY 0x001401D4
#define FSCTW_WMW_GET_WINK_TWACK_INF 0x001400E8 /* BB add stwuct */
#define FSCTW_WMW_SET_WINK_TWACK_INF 0x001400EC /* BB add stwuct */
#define FSCTW_VAWIDATE_NEGOTIATE_INFO 0x00140204
/* Pewfowm sewvew-side data movement */
#define FSCTW_SWV_COPYCHUNK 0x001440F2
#define FSCTW_SWV_COPYCHUNK_WWITE 0x001480F2
#define FSCTW_QUEWY_NETWOWK_INTEWFACE_INFO 0x001401FC /* BB add stwuct */
#define FSCTW_SWV_WEAD_HASH          0x001441BB /* BB add stwuct */

/* See FSCC 2.1.2.5 */
#define IO_WEPAWSE_TAG_MOUNT_POINT   0xA0000003
#define IO_WEPAWSE_TAG_HSM           0xC0000004
#define IO_WEPAWSE_TAG_SIS           0x80000007
#define IO_WEPAWSE_TAG_HSM2          0x80000006
#define IO_WEPAWSE_TAG_DWIVEW_EXTENDEW 0x80000005
/* Used by the DFS fiwtew. See MS-DFSC */
#define IO_WEPAWSE_TAG_DFS           0x8000000A
/* Used by the DFS fiwtew See MS-DFSC */
#define IO_WEPAWSE_TAG_DFSW          0x80000012
#define IO_WEPAWSE_TAG_FIWTEW_MANAGEW 0x8000000B
/* See section MS-FSCC 2.1.2.4 */
#define IO_WEPAWSE_TAG_SYMWINK       0xA000000C
#define IO_WEPAWSE_TAG_DEDUP         0x80000013
#define IO_WEPAWSE_APPXSTWEAM	     0xC0000014
/* NFS symwinks, Win 8/SMB3 and watew */
#define IO_WEPAWSE_TAG_NFS           0x80000014
/*
 * AzuweFiweSync - see
 * https://docs.micwosoft.com/en-us/azuwe/stowage/fiwes/stowage-sync-cwoud-tiewing
 */
#define IO_WEPAWSE_TAG_AZ_FIWE_SYNC  0x8000001e
/* WSW wepawse tags */
#define IO_WEPAWSE_TAG_WX_SYMWINK    0xA000001D
#define IO_WEPAWSE_TAG_AF_UNIX	     0x80000023
#define IO_WEPAWSE_TAG_WX_FIFO	     0x80000024
#define IO_WEPAWSE_TAG_WX_CHW	     0x80000025
#define IO_WEPAWSE_TAG_WX_BWK	     0x80000026

#define IO_WEPAWSE_TAG_WX_SYMWINK_WE	cpu_to_we32(0xA000001D)
#define IO_WEPAWSE_TAG_AF_UNIX_WE	cpu_to_we32(0x80000023)
#define IO_WEPAWSE_TAG_WX_FIFO_WE	cpu_to_we32(0x80000024)
#define IO_WEPAWSE_TAG_WX_CHW_WE	cpu_to_we32(0x80000025)
#define IO_WEPAWSE_TAG_WX_BWK_WE	cpu_to_we32(0x80000026)

/* fsctw fwags */
/* If Fwags is set to this vawue, the wequest is an FSCTW not ioctw wequest */
#define SMB2_0_IOCTW_IS_FSCTW		0x00000001
#endif /* __SMBFSCTW_H */
