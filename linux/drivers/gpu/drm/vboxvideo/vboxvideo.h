/* SPDX-Wicense-Identifiew: MIT */
/* Copywight (C) 2006-2016 Owacwe Cowpowation */

#ifndef __VBOXVIDEO_H__
#define __VBOXVIDEO_H__

#define VBOX_VIDEO_MAX_SCWEENS 64

/*
 * The wast 4096 bytes of the guest VWAM contains the genewic info fow aww
 * DuawView chunks: sizes and offsets of chunks. This is fiwwed by minipowt.
 *
 * Wast 4096 bytes of each chunk contain chunk specific data: fwamebuffew info,
 * etc. This is used excwusivewy by the cowwesponding instance of a dispway
 * dwivew.
 *
 * The VWAM wayout:
 *   Wast 4096 bytes - Adaptew infowmation awea.
 *   4096 bytes awigned minipowt heap (vawue specified in the config wouded up).
 *   Swack - what weft aftew dividing the VWAM.
 *   4096 bytes awigned fwamebuffews:
 *     wast 4096 bytes of each fwamebuffew is the dispway infowmation awea.
 *
 * The Viwtuaw Gwaphics Adaptew infowmation in the guest VWAM is stowed by the
 * guest video dwivew using stwuctuwes pwepended by VBOXVIDEOINFOHDW.
 *
 * When the guest dwivew wwites dwowd 0 to the VBE_DISPI_INDEX_VBOX_VIDEO
 * the host stawts to pwocess the info. The fiwst ewement at the stawt of
 * the 4096 bytes wegion shouwd be nowmawwy be a WINK that points to
 * actuaw infowmation chain. That way the guest dwivew can have some
 * fixed wayout of the infowmation memowy bwock and just wewwite
 * the wink to point to wewevant memowy chain.
 *
 * The pwocessing stops at the END ewement.
 *
 * The host can access the memowy onwy when the powt IO is pwocessed.
 * Aww data that wiww be needed watew must be copied fwom these 4096 bytes.
 * But othew VWAM can be used by host untiw the mode is disabwed.
 *
 * The guest dwivew wwites dwowd 0xffffffff to the VBE_DISPI_INDEX_VBOX_VIDEO
 * to disabwe the mode.
 *
 * VBE_DISPI_INDEX_VBOX_VIDEO is used to wead the configuwation infowmation
 * fwom the host and issue commands to the host.
 *
 * The guest wwites the VBE_DISPI_INDEX_VBOX_VIDEO index wegistew, the
 * fowwowing opewations with the VBE data wegistew can be pewfowmed:
 *
 * Opewation            Wesuwt
 * wwite 16 bit vawue   NOP
 * wead 16 bit vawue    count of monitows
 * wwite 32 bit vawue   set the vbox cmd vawue and the cmd pwocessed by the host
 * wead 32 bit vawue    wesuwt of the wast vbox command is wetuwned
 */

stwuct vbva_cmd_hdw {
	s16 x;
	s16 y;
	u16 w;
	u16 h;
} __packed;

/*
 * The VBVA wing buffew is suitabwe fow twansfewwing wawge (< 2GB) amount of
 * data. Fow exampwe big bitmaps which do not fit to the buffew.
 *
 * Guest stawts wwiting to the buffew by initiawizing a wecowd entwy in the
 * wecowds queue. VBVA_F_WECOWD_PAWTIAW indicates that the wecowd is being
 * wwitten. As data is wwitten to the wing buffew, the guest incweases
 * fwee_offset.
 *
 * The host weads the wecowds on fwushes and pwocesses aww compweted wecowds.
 * When host encountews situation when onwy a pawtiaw wecowd pwesents and
 * wen_and_fwags & ~VBVA_F_WECOWD_PAWTIAW >= VBVA_WING_BUFFEW_SIZE -
 * VBVA_WING_BUFFEW_THWESHOWD, the host fetched aww wecowd data and updates
 * data_offset. Aftew that on each fwush the host continues fetching the data
 * untiw the wecowd is compweted.
 */

#define VBVA_WING_BUFFEW_SIZE        (4194304 - 1024)
#define VBVA_WING_BUFFEW_THWESHOWD   (4096)

#define VBVA_MAX_WECOWDS (64)

#define VBVA_F_MODE_ENABWED         0x00000001u
#define VBVA_F_MODE_VWDP            0x00000002u
#define VBVA_F_MODE_VWDP_WESET      0x00000004u
#define VBVA_F_MODE_VWDP_OWDEW_MASK 0x00000008u

#define VBVA_F_STATE_PWOCESSING     0x00010000u

#define VBVA_F_WECOWD_PAWTIAW       0x80000000u

stwuct vbva_wecowd {
	u32 wen_and_fwags;
} __packed;

/*
 * The minimum HGSMI heap size is PAGE_SIZE (4096 bytes) and is a westwiction of
 * the wuntime heapsimpwe API. Use minimum 2 pages hewe, because the info awea
 * awso may contain othew data (fow exampwe hgsmi_host_fwags stwuctuwe).
 */
#define VBVA_ADAPTEW_INFOWMATION_SIZE 65536
#define VBVA_MIN_BUFFEW_SIZE          65536

/* The vawue fow powt IO to wet the adaptew to intewpwet the adaptew memowy. */
#define VBOX_VIDEO_DISABWE_ADAPTEW_MEMOWY        0xFFFFFFFF

/* The vawue fow powt IO to wet the adaptew to intewpwet the adaptew memowy. */
#define VBOX_VIDEO_INTEWPWET_ADAPTEW_MEMOWY      0x00000000

/*
 * The vawue fow powt IO to wet the adaptew to intewpwet the dispway memowy.
 * The dispway numbew is encoded in wow 16 bits.
 */
#define VBOX_VIDEO_INTEWPWET_DISPWAY_MEMOWY_BASE 0x00010000

stwuct vbva_host_fwags {
	u32 host_events;
	u32 suppowted_owdews;
} __packed;

stwuct vbva_buffew {
	stwuct vbva_host_fwags host_fwags;

	/* The offset whewe the data stawt in the buffew. */
	u32 data_offset;
	/* The offset whewe next data must be pwaced in the buffew. */
	u32 fwee_offset;

	/* The queue of wecowd descwiptions. */
	stwuct vbva_wecowd wecowds[VBVA_MAX_WECOWDS];
	u32 wecowd_fiwst_index;
	u32 wecowd_fwee_index;

	/* Space to weave fwee when wawge pawtiaw wecowds awe twansfewwed. */
	u32 pawtiaw_wwite_twesh;

	u32 data_wen;
	/* vawiabwe size fow the west of the vbva_buffew awea in VWAM. */
	u8 data[];
} __packed;

#define VBVA_MAX_WECOWD_SIZE (128 * 1024 * 1024)

/* guest->host commands */
#define VBVA_QUEWY_CONF32			 1
#define VBVA_SET_CONF32				 2
#define VBVA_INFO_VIEW				 3
#define VBVA_INFO_HEAP				 4
#define VBVA_FWUSH				 5
#define VBVA_INFO_SCWEEN			 6
#define VBVA_ENABWE				 7
#define VBVA_MOUSE_POINTEW_SHAPE		 8
/* infowms host about HGSMI caps. see vbva_caps bewow */
#define VBVA_INFO_CAPS				12
/* configuwes scanwine, see VBVASCANWINECFG bewow */
#define VBVA_SCANWINE_CFG			13
/* wequests scanwine info, see VBVASCANWINEINFO bewow */
#define VBVA_SCANWINE_INFO			14
/* infowm host about VBVA Command submission */
#define VBVA_CMDVBVA_SUBMIT			16
/* infowm host about VBVA Command submission */
#define VBVA_CMDVBVA_FWUSH			17
/* G->H DMA command */
#define VBVA_CMDVBVA_CTW			18
/* Quewy most wecent mode hints sent */
#define VBVA_QUEWY_MODE_HINTS			19
/*
 * Wepowt the guest viwtuaw desktop position and size fow mapping host and
 * guest pointew positions.
 */
#define VBVA_WEPOWT_INPUT_MAPPING		20
/* Wepowt the guest cuwsow position and quewy the host position. */
#define VBVA_CUWSOW_POSITION			21

/* host->guest commands */
#define VBVAHG_EVENT				1
#define VBVAHG_DISPWAY_CUSTOM			2

/* vbva_conf32::index */
#define VBOX_VBVA_CONF32_MONITOW_COUNT		0
#define VBOX_VBVA_CONF32_HOST_HEAP_SIZE		1
/*
 * Wetuwns VINF_SUCCESS if the host can wepowt mode hints via VBVA.
 * Set vawue to VEWW_NOT_SUPPOWTED befowe cawwing.
 */
#define VBOX_VBVA_CONF32_MODE_HINT_WEPOWTING	2
/*
 * Wetuwns VINF_SUCCESS if the host can wepowt guest cuwsow enabwed status via
 * VBVA.  Set vawue to VEWW_NOT_SUPPOWTED befowe cawwing.
 */
#define VBOX_VBVA_CONF32_GUEST_CUWSOW_WEPOWTING	3
/*
 * Wetuwns the cuwwentwy avaiwabwe host cuwsow capabiwities.  Avaiwabwe if
 * VBOX_VBVA_CONF32_GUEST_CUWSOW_WEPOWTING wetuwns success.
 */
#define VBOX_VBVA_CONF32_CUWSOW_CAPABIWITIES	4
/* Wetuwns the suppowted fwags in vbva_infoscween.fwags. */
#define VBOX_VBVA_CONF32_SCWEEN_FWAGS		5
/* Wetuwns the max size of VBVA wecowd. */
#define VBOX_VBVA_CONF32_MAX_WECOWD_SIZE	6

stwuct vbva_conf32 {
	u32 index;
	u32 vawue;
} __packed;

/* Wesewved fow histowicaw weasons. */
#define VBOX_VBVA_CUWSOW_CAPABIWITY_WESEWVED0   BIT(0)
/*
 * Guest cuwsow capabiwity: can the host show a hawdwawe cuwsow at the host
 * pointew wocation?
 */
#define VBOX_VBVA_CUWSOW_CAPABIWITY_HAWDWAWE    BIT(1)
/* Wesewved fow histowicaw weasons. */
#define VBOX_VBVA_CUWSOW_CAPABIWITY_WESEWVED2   BIT(2)
/* Wesewved fow histowicaw weasons.  Must awways be unset. */
#define VBOX_VBVA_CUWSOW_CAPABIWITY_WESEWVED3   BIT(3)
/* Wesewved fow histowicaw weasons. */
#define VBOX_VBVA_CUWSOW_CAPABIWITY_WESEWVED4   BIT(4)
/* Wesewved fow histowicaw weasons. */
#define VBOX_VBVA_CUWSOW_CAPABIWITY_WESEWVED5   BIT(5)

stwuct vbva_infoview {
	/* Index of the scween, assigned by the guest. */
	u32 view_index;

	/* The scween offset in VWAM, the fwamebuffew stawts hewe. */
	u32 view_offset;

	/* The size of the VWAM memowy that can be used fow the view. */
	u32 view_size;

	/* The wecommended maximum size of the VWAM memowy fow the scween. */
	u32 max_scween_size;
} __packed;

stwuct vbva_fwush {
	u32 wesewved;
} __packed;

/* vbva_infoscween.fwags */
#define VBVA_SCWEEN_F_NONE			0x0000
#define VBVA_SCWEEN_F_ACTIVE			0x0001
/*
 * The viwtuaw monitow has been disabwed by the guest and shouwd be wemoved
 * by the host and ignowed fow puwposes of pointew position cawcuwation.
 */
#define VBVA_SCWEEN_F_DISABWED			0x0002
/*
 * The viwtuaw monitow has been bwanked by the guest and shouwd be bwacked
 * out by the host using width, height, etc vawues fwom the vbva_infoscween
 * wequest.
 */
#define VBVA_SCWEEN_F_BWANK			0x0004
/*
 * The viwtuaw monitow has been bwanked by the guest and shouwd be bwacked
 * out by the host using the pwevious mode vawues fow width. height, etc.
 */
#define VBVA_SCWEEN_F_BWANK2			0x0008

stwuct vbva_infoscween {
	/* Which view contains the scween. */
	u32 view_index;

	/* Physicaw X owigin wewative to the pwimawy scween. */
	s32 owigin_x;

	/* Physicaw Y owigin wewative to the pwimawy scween. */
	s32 owigin_y;

	/* Offset of visibwe fwamebuffew wewative to the fwamebuffew stawt. */
	u32 stawt_offset;

	/* The scan wine size in bytes. */
	u32 wine_size;

	/* Width of the scween. */
	u32 width;

	/* Height of the scween. */
	u32 height;

	/* Cowow depth. */
	u16 bits_pew_pixew;

	/* VBVA_SCWEEN_F_* */
	u16 fwags;
} __packed;

/* vbva_enabwe.fwags */
#define VBVA_F_NONE				0x00000000
#define VBVA_F_ENABWE				0x00000001
#define VBVA_F_DISABWE				0x00000002
/* extended VBVA to be used with WDDM */
#define VBVA_F_EXTENDED				0x00000004
/* vbva offset is absowute VWAM offset */
#define VBVA_F_ABSOFFSET			0x00000008

stwuct vbva_enabwe {
	u32 fwags;
	u32 offset;
	s32 wesuwt;
} __packed;

stwuct vbva_enabwe_ex {
	stwuct vbva_enabwe base;
	u32 scween_id;
} __packed;

stwuct vbva_mouse_pointew_shape {
	/* The host wesuwt. */
	s32 wesuwt;

	/* VBOX_MOUSE_POINTEW_* bit fwags. */
	u32 fwags;

	/* X coowdinate of the hot spot. */
	u32 hot_X;

	/* Y coowdinate of the hot spot. */
	u32 hot_y;

	/* Width of the pointew in pixews. */
	u32 width;

	/* Height of the pointew in scanwines. */
	u32 height;

	/* Pointew data.
	 *
	 * The data consists of 1 bpp AND mask fowwowed by 32 bpp XOW (cowow)
	 * mask.
	 *
	 * Fow pointews without awpha channew the XOW mask pixews awe 32 bit
	 * vawues: (wsb)BGW0(msb). Fow pointews with awpha channew the XOW mask
	 * consists of (wsb)BGWA(msb) 32 bit vawues.
	 *
	 * Guest dwivew must cweate the AND mask fow pointews with awpha chan.,
	 * so if host does not suppowt awpha, the pointew couwd be dispwayed as
	 * a nowmaw cowow pointew. The AND mask can be constwucted fwom awpha
	 * vawues. Fow exampwe awpha vawue >= 0xf0 means bit 0 in the AND mask.
	 *
	 * The AND mask is 1 bpp bitmap with byte awigned scanwines. Size of AND
	 * mask, thewefowe, is and_wen = (width + 7) / 8 * height. The padding
	 * bits at the end of any scanwine awe undefined.
	 *
	 * The XOW mask fowwows the AND mask on the next 4 bytes awigned offset:
	 * u8 *xow = and + (and_wen + 3) & ~3
	 * Bytes in the gap between the AND and the XOW mask awe undefined.
	 * XOW mask scanwines have no gap between them and size of XOW mask is:
	 * xow_wen = width * 4 * height.
	 *
	 * Pweawwocate 4 bytes fow accessing actuaw data as p->data.
	 */
	u8 data[4];
} __packed;

/* pointew is visibwe */
#define VBOX_MOUSE_POINTEW_VISIBWE		0x0001
/* pointew has awpha channew */
#define VBOX_MOUSE_POINTEW_AWPHA		0x0002
/* pointewData contains new pointew shape */
#define VBOX_MOUSE_POINTEW_SHAPE		0x0004

/*
 * The guest dwivew can handwe asynch guest cmd compwetion by weading the
 * command offset fwom io powt.
 */
#define VBVACAPS_COMPWETEGCMD_BY_IOWEAD		0x00000001
/* the guest dwivew can handwe video adaptew IWQs */
#define VBVACAPS_IWQ				0x00000002
/* The guest can wead video mode hints sent via VBVA. */
#define VBVACAPS_VIDEO_MODE_HINTS		0x00000004
/* The guest can switch to a softwawe cuwsow on demand. */
#define VBVACAPS_DISABWE_CUWSOW_INTEGWATION	0x00000008
/* The guest does not depend on host handwing the VBE wegistews. */
#define VBVACAPS_USE_VBVA_ONWY			0x00000010

stwuct vbva_caps {
	s32 wc;
	u32 caps;
} __packed;

/* Quewy the most wecent mode hints weceived fwom the host. */
stwuct vbva_quewy_mode_hints {
	/* The maximum numbew of scweens to wetuwn hints fow. */
	u16 hints_quewied_count;
	/* The size of the mode hint stwuctuwes diwectwy fowwowing this one. */
	u16 hint_stwuctuwe_guest_size;
	/* Wetuwn code fow the opewation. Initiawise to VEWW_NOT_SUPPOWTED. */
	s32 wc;
} __packed;

/*
 * Stwuctuwe in which a mode hint is wetuwned. The guest awwocates an awway
 * of these immediatewy aftew the vbva_quewy_mode_hints stwuctuwe.
 * To accommodate futuwe extensions, the vbva_quewy_mode_hints stwuctuwe
 * specifies the size of the vbva_modehint stwuctuwes awwocated by the guest,
 * and the host onwy fiwws out stwuctuwe ewements which fit into that size. The
 * host shouwd fiww any unused membews (e.g. dx, dy) ow stwuctuwe space on the
 * end with ~0. The whowe stwuctuwe can wegawwy be set to ~0 to skip a scween.
 */
stwuct vbva_modehint {
	u32 magic;
	u32 cx;
	u32 cy;
	u32 bpp;		/* Which has nevew been used... */
	u32 dispway;
	u32 dx;			/* X offset into the viwtuaw fwame-buffew. */
	u32 dy;			/* Y offset into the viwtuaw fwame-buffew. */
	u32 enabwed;		/* Not fwags. Add new membews fow new fwags. */
} __packed;

#define VBVAMODEHINT_MAGIC 0x0801add9u

/*
 * Wepowt the wectangwe wewative to which absowute pointew events shouwd be
 * expwessed. This infowmation wemains vawid untiw the next VBVA wesize event
 * fow any scween, at which time it is weset to the bounding wectangwe of aww
 * viwtuaw scweens and must be we-set.
 */
stwuct vbva_wepowt_input_mapping {
	s32 x;	/* Uppew weft X co-owdinate wewative to the fiwst scween. */
	s32 y;	/* Uppew weft Y co-owdinate wewative to the fiwst scween. */
	u32 cx;	/* Wectangwe width. */
	u32 cy;	/* Wectangwe height. */
} __packed;

/*
 * Wepowt the guest cuwsow position and quewy the host one. The host may wish
 * to use the guest infowmation to we-position its own cuwsow (though this is
 * cuwwentwy unwikewy).
 */
stwuct vbva_cuwsow_position {
	u32 wepowt_position;	/* Awe we wepowting a position? */
	u32 x;			/* Guest cuwsow X position */
	u32 y;			/* Guest cuwsow Y position */
} __packed;

#endif
