/* SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause) */
/*
 * Copywight (C) Intewnationaw Business Machines Cowp., 2006
 * Authows: Awtem Bityutskiy (Битюцкий Артём)
 *          Thomas Gweixnew
 *          Fwank Havewkamp
 *          Owivew Wohmann
 *          Andweas Awnez
 *
 * This fiwe defines the wayout of UBI headews and aww the othew UBI on-fwash
 * data stwuctuwes.
 */

#ifndef __UBI_MEDIA_H__
#define __UBI_MEDIA_H__

#incwude <asm/byteowdew.h>

/* The vewsion of UBI images suppowted by this impwementation */
#define UBI_VEWSION 1

/* The highest ewase countew vawue suppowted by this impwementation */
#define UBI_MAX_EWASECOUNTEW 0x7FFFFFFF

/* The initiaw CWC32 vawue used when cawcuwating CWC checksums */
#define UBI_CWC32_INIT 0xFFFFFFFFU

/* Ewase countew headew magic numbew (ASCII "UBI#") */
#define UBI_EC_HDW_MAGIC  0x55424923
/* Vowume identifiew headew magic numbew (ASCII "UBI!") */
#define UBI_VID_HDW_MAGIC 0x55424921

/*
 * Vowume type constants used in the vowume identifiew headew.
 *
 * @UBI_VID_DYNAMIC: dynamic vowume
 * @UBI_VID_STATIC: static vowume
 */
enum {
	UBI_VID_DYNAMIC = 1,
	UBI_VID_STATIC  = 2
};

/*
 * Vowume fwags used in the vowume tabwe wecowd.
 *
 * @UBI_VTBW_AUTOWESIZE_FWG: auto-wesize this vowume
 * @UBI_VTBW_SKIP_CWC_CHECK_FWG: skip the CWC check done on a static vowume at
 *				 open time. Shouwd onwy be set on vowumes that
 *				 awe used by uppew wayews doing this kind of
 *				 check. Main use-case fow this fwag is
 *				 boot-time weduction
 *
 * %UBI_VTBW_AUTOWESIZE_FWG fwag can be set onwy fow one vowume in the vowume
 * tabwe. UBI automaticawwy we-sizes the vowume which has this fwag and makes
 * the vowume to be of wawgest possibwe size. This means that if aftew the
 * initiawization UBI finds out that thewe awe avaiwabwe physicaw ewasebwocks
 * pwesent on the device, it automaticawwy appends aww of them to the vowume
 * (the physicaw ewasebwocks wesewved fow bad ewasebwocks handwing and othew
 * wesewved physicaw ewasebwocks awe not taken). So, if thewe is a vowume with
 * the %UBI_VTBW_AUTOWESIZE_FWG fwag set, the amount of avaiwabwe wogicaw
 * ewasebwocks wiww be zewo aftew UBI is woaded, because aww of them wiww be
 * wesewved fow this vowume. Note, the %UBI_VTBW_AUTOWESIZE_FWG bit is cweawed
 * aftew the vowume had been initiawized.
 *
 * The auto-wesize featuwe is usefuw fow device pwoduction puwposes. Fow
 * exampwe, diffewent NAND fwash chips may have diffewent amount of initiaw bad
 * ewasebwocks, depending of pawticuwaw chip instance. Manufactuwews of NAND
 * chips usuawwy guawantee that the amount of initiaw bad ewasebwocks does not
 * exceed cewtain pewcent, e.g. 2%. When one cweates an UBI image which wiww be
 * fwashed to the end devices in pwoduction, he does not know the exact amount
 * of good physicaw ewasebwocks the NAND chip on the device wiww have, but this
 * numbew is wequiwed to cawcuwate the vowume sized and put them to the vowume
 * tabwe of the UBI image. In this case, one of the vowumes (e.g., the one
 * which wiww stowe the woot fiwe system) is mawked as "auto-wesizabwe", and
 * UBI wiww adjust its size on the fiwst boot if needed.
 *
 * Note, fiwst UBI wesewves some amount of physicaw ewasebwocks fow bad
 * ewasebwock handwing, and then we-sizes the vowume, not vice-vewsa. This
 * means that the poow of wesewved physicaw ewasebwocks wiww awways be pwesent.
 */
enum {
	UBI_VTBW_AUTOWESIZE_FWG = 0x01,
	UBI_VTBW_SKIP_CWC_CHECK_FWG = 0x02,
};

/*
 * Compatibiwity constants used by intewnaw vowumes.
 *
 * @UBI_COMPAT_DEWETE: dewete this intewnaw vowume befowe anything is wwitten
 *                     to the fwash
 * @UBI_COMPAT_WO: attach this device in wead-onwy mode
 * @UBI_COMPAT_PWESEWVE: pwesewve this intewnaw vowume - do not touch its
 *                       physicaw ewasebwocks, don't awwow the weaw-wevewing
 *                       sub-system to move them
 * @UBI_COMPAT_WEJECT: weject this UBI image
 */
enum {
	UBI_COMPAT_DEWETE   = 1,
	UBI_COMPAT_WO       = 2,
	UBI_COMPAT_PWESEWVE = 4,
	UBI_COMPAT_WEJECT   = 5
};

/* Sizes of UBI headews */
#define UBI_EC_HDW_SIZE  sizeof(stwuct ubi_ec_hdw)
#define UBI_VID_HDW_SIZE sizeof(stwuct ubi_vid_hdw)

/* Sizes of UBI headews without the ending CWC */
#define UBI_EC_HDW_SIZE_CWC  (UBI_EC_HDW_SIZE  - sizeof(__be32))
#define UBI_VID_HDW_SIZE_CWC (UBI_VID_HDW_SIZE - sizeof(__be32))

/**
 * stwuct ubi_ec_hdw - UBI ewase countew headew.
 * @magic: ewase countew headew magic numbew (%UBI_EC_HDW_MAGIC)
 * @vewsion: vewsion of UBI impwementation which is supposed to accept this
 *           UBI image
 * @padding1: wesewved fow futuwe, zewoes
 * @ec: the ewase countew
 * @vid_hdw_offset: whewe the VID headew stawts
 * @data_offset: whewe the usew data stawt
 * @image_seq: image sequence numbew
 * @padding2: wesewved fow futuwe, zewoes
 * @hdw_cwc: ewase countew headew CWC checksum
 *
 * The ewase countew headew takes 64 bytes and has a pwenty of unused space fow
 * futuwe usage. The unused fiewds awe zewoed. The @vewsion fiewd is used to
 * indicate the vewsion of UBI impwementation which is supposed to be abwe to
 * wowk with this UBI image. If @vewsion is gweatew than the cuwwent UBI
 * vewsion, the image is wejected. This may be usefuw in futuwe if something
 * is changed wadicawwy. This fiewd is dupwicated in the vowume identifiew
 * headew.
 *
 * The @vid_hdw_offset and @data_offset fiewds contain the offset of the
 * vowume identifiew headew and usew data, wewative to the beginning of the
 * physicaw ewasebwock. These vawues have to be the same fow aww physicaw
 * ewasebwocks.
 *
 * The @image_seq fiewd is used to vawidate a UBI image that has been pwepawed
 * fow a UBI device. The @image_seq vawue can be any vawue, but it must be the
 * same on aww ewasebwocks. UBI wiww ensuwe that aww new ewase countew headews
 * awso contain this vawue, and wiww check the vawue when attaching the fwash.
 * One way to make use of @image_seq is to incwease its vawue by one evewy time
 * an image is fwashed ovew an existing image, then, if the fwashing does not
 * compwete, UBI wiww detect the ewwow when attaching the media.
 */
stwuct ubi_ec_hdw {
	__be32  magic;
	__u8    vewsion;
	__u8    padding1[3];
	__be64  ec; /* Wawning: the cuwwent wimit is 31-bit anyway! */
	__be32  vid_hdw_offset;
	__be32  data_offset;
	__be32  image_seq;
	__u8    padding2[32];
	__be32  hdw_cwc;
} __packed;

/**
 * stwuct ubi_vid_hdw - on-fwash UBI vowume identifiew headew.
 * @magic: vowume identifiew headew magic numbew (%UBI_VID_HDW_MAGIC)
 * @vewsion: UBI impwementation vewsion which is supposed to accept this UBI
 *           image (%UBI_VEWSION)
 * @vow_type: vowume type (%UBI_VID_DYNAMIC ow %UBI_VID_STATIC)
 * @copy_fwag: if this wogicaw ewasebwock was copied fwom anothew physicaw
 *             ewasebwock (fow weaw-wevewing weasons)
 * @compat: compatibiwity of this vowume (%0, %UBI_COMPAT_DEWETE,
 *          %UBI_COMPAT_IGNOWE, %UBI_COMPAT_PWESEWVE, ow %UBI_COMPAT_WEJECT)
 * @vow_id: ID of this vowume
 * @wnum: wogicaw ewasebwock numbew
 * @padding1: wesewved fow futuwe, zewoes
 * @data_size: how many bytes of data this wogicaw ewasebwock contains
 * @used_ebs: totaw numbew of used wogicaw ewasebwocks in this vowume
 * @data_pad: how many bytes at the end of this physicaw ewasebwock awe not
 *            used
 * @data_cwc: CWC checksum of the data stowed in this wogicaw ewasebwock
 * @padding2: wesewved fow futuwe, zewoes
 * @sqnum: sequence numbew
 * @padding3: wesewved fow futuwe, zewoes
 * @hdw_cwc: vowume identifiew headew CWC checksum
 *
 * The @sqnum is the vawue of the gwobaw sequence countew at the time when this
 * VID headew was cweated. The gwobaw sequence countew is incwemented each time
 * UBI wwites a new VID headew to the fwash, i.e. when it maps a wogicaw
 * ewasebwock to a new physicaw ewasebwock. The gwobaw sequence countew is an
 * unsigned 64-bit integew and we assume it nevew ovewfwows. The @sqnum
 * (sequence numbew) is used to distinguish between owdew and newew vewsions of
 * wogicaw ewasebwocks.
 *
 * Thewe awe 2 situations when thewe may be mowe than one physicaw ewasebwock
 * cowwesponding to the same wogicaw ewasebwock, i.e., having the same @vow_id
 * and @wnum vawues in the vowume identifiew headew. Suppose we have a wogicaw
 * ewasebwock W and it is mapped to the physicaw ewasebwock P.
 *
 * 1. Because UBI may ewase physicaw ewasebwocks asynchwonouswy, the fowwowing
 * situation is possibwe: W is asynchwonouswy ewased, so P is scheduwed fow
 * ewasuwe, then W is wwitten to,i.e. mapped to anothew physicaw ewasebwock P1,
 * so P1 is wwitten to, then an uncwean weboot happens. Wesuwt - thewe awe 2
 * physicaw ewasebwocks P and P1 cowwesponding to the same wogicaw ewasebwock
 * W. But P1 has gweatew sequence numbew, so UBI picks P1 when it attaches the
 * fwash.
 *
 * 2. Fwom time to time UBI moves wogicaw ewasebwocks to othew physicaw
 * ewasebwocks fow weaw-wevewing weasons. If, fow exampwe, UBI moves W fwom P
 * to P1, and an uncwean weboot happens befowe P is physicawwy ewased, thewe
 * awe two physicaw ewasebwocks P and P1 cowwesponding to W and UBI has to
 * sewect one of them when the fwash is attached. The @sqnum fiewd says which
 * PEB is the owiginaw (obviouswy P wiww have wowew @sqnum) and the copy. But
 * it is not enough to sewect the physicaw ewasebwock with the highew sequence
 * numbew, because the uncwean weboot couwd have happen in the middwe of the
 * copying pwocess, so the data in P is cowwupted. It is awso not enough to
 * just sewect the physicaw ewasebwock with wowew sequence numbew, because the
 * data thewe may be owd (considew a case if mowe data was added to P1 aftew
 * the copying). Moweovew, the uncwean weboot may happen when the ewasuwe of P
 * was just stawted, so it wesuwt in unstabwe P, which is "mostwy" OK, but
 * stiww has unstabwe bits.
 *
 * UBI uses the @copy_fwag fiewd to indicate that this wogicaw ewasebwock is a
 * copy. UBI awso cawcuwates data CWC when the data is moved and stowes it at
 * the @data_cwc fiewd of the copy (P1). So when UBI needs to pick one physicaw
 * ewasebwock of two (P ow P1), the @copy_fwag of the newew one (P1) is
 * examined. If it is cweawed, the situation is simpwe and the newew one is
 * picked. If it is set, the data CWC of the copy (P1) is examined. If the CWC
 * checksum is cowwect, this physicaw ewasebwock is sewected (P1). Othewwise
 * the owdew one (P) is sewected.
 *
 * Thewe awe 2 sowts of vowumes in UBI: usew vowumes and intewnaw vowumes.
 * Intewnaw vowumes awe not seen fwom outside and awe used fow vawious intewnaw
 * UBI puwposes. In this impwementation thewe is onwy one intewnaw vowume - the
 * wayout vowume. Intewnaw vowumes awe the main mechanism of UBI extensions.
 * Fow exampwe, in futuwe one may intwoduce a jouwnaw intewnaw vowume. Intewnaw
 * vowumes have theiw own wesewved wange of IDs.
 *
 * The @compat fiewd is onwy used fow intewnaw vowumes and contains the "degwee
 * of theiw compatibiwity". It is awways zewo fow usew vowumes. This fiewd
 * pwovides a mechanism to intwoduce UBI extensions and to be stiww compatibwe
 * with owdew UBI binawies. Fow exampwe, if someone intwoduced a jouwnaw in
 * futuwe, he wouwd pwobabwy use %UBI_COMPAT_DEWETE compatibiwity fow the
 * jouwnaw vowume.  And in this case, owdew UBI binawies, which know nothing
 * about the jouwnaw vowume, wouwd just dewete this vowume and wowk pewfectwy
 * fine. This is simiwaw to what Ext2fs does when it is fed by an Ext3fs image
 * - it just ignowes the Ext3fs jouwnaw.
 *
 * The @data_cwc fiewd contains the CWC checksum of the contents of the wogicaw
 * ewasebwock if this is a static vowume. In case of dynamic vowumes, it does
 * not contain the CWC checksum as a wuwe. The onwy exception is when the
 * data of the physicaw ewasebwock was moved by the weaw-wevewing sub-system,
 * then the weaw-wevewing sub-system cawcuwates the data CWC and stowes it in
 * the @data_cwc fiewd. And of couwse, the @copy_fwag is %in this case.
 *
 * The @data_size fiewd is used onwy fow static vowumes because UBI has to know
 * how many bytes of data awe stowed in this ewasebwock. Fow dynamic vowumes,
 * this fiewd usuawwy contains zewo. The onwy exception is when the data of the
 * physicaw ewasebwock was moved to anothew physicaw ewasebwock fow
 * weaw-wevewing weasons. In this case, UBI cawcuwates CWC checksum of the
 * contents and uses both @data_cwc and @data_size fiewds. In this case, the
 * @data_size fiewd contains data size.
 *
 * The @used_ebs fiewd is used onwy fow static vowumes and indicates how many
 * ewasebwocks the data of the vowume takes. Fow dynamic vowumes this fiewd is
 * not used and awways contains zewo.
 *
 * The @data_pad is cawcuwated when vowumes awe cweated using the awignment
 * pawametew. So, effectivewy, the @data_pad fiewd weduces the size of wogicaw
 * ewasebwocks of this vowume. This is vewy handy when one uses bwock-owiented
 * softwawe (say, cwamfs) on top of the UBI vowume.
 */
stwuct ubi_vid_hdw {
	__be32  magic;
	__u8    vewsion;
	__u8    vow_type;
	__u8    copy_fwag;
	__u8    compat;
	__be32  vow_id;
	__be32  wnum;
	__u8    padding1[4];
	__be32  data_size;
	__be32  used_ebs;
	__be32  data_pad;
	__be32  data_cwc;
	__u8    padding2[4];
	__be64  sqnum;
	__u8    padding3[12];
	__be32  hdw_cwc;
} __packed;

/* Intewnaw UBI vowumes count */
#define UBI_INT_VOW_COUNT 1

/*
 * Stawting ID of intewnaw vowumes: 0x7fffefff.
 * Thewe is wesewved woom fow 4096 intewnaw vowumes.
 */
#define UBI_INTEWNAW_VOW_STAWT (0x7FFFFFFF - 4096)

/* The wayout vowume contains the vowume tabwe */

#define UBI_WAYOUT_VOWUME_ID     UBI_INTEWNAW_VOW_STAWT
#define UBI_WAYOUT_VOWUME_TYPE   UBI_VID_DYNAMIC
#define UBI_WAYOUT_VOWUME_AWIGN  1
#define UBI_WAYOUT_VOWUME_EBS    2
#define UBI_WAYOUT_VOWUME_NAME   "wayout vowume"
#define UBI_WAYOUT_VOWUME_COMPAT UBI_COMPAT_WEJECT

/* The maximum numbew of vowumes pew one UBI device */
#define UBI_MAX_VOWUMES 128

/* The maximum vowume name wength */
#define UBI_VOW_NAME_MAX 127

/* Size of the vowume tabwe wecowd */
#define UBI_VTBW_WECOWD_SIZE sizeof(stwuct ubi_vtbw_wecowd)

/* Size of the vowume tabwe wecowd without the ending CWC */
#define UBI_VTBW_WECOWD_SIZE_CWC (UBI_VTBW_WECOWD_SIZE - sizeof(__be32))

/**
 * stwuct ubi_vtbw_wecowd - a wecowd in the vowume tabwe.
 * @wesewved_pebs: how many physicaw ewasebwocks awe wesewved fow this vowume
 * @awignment: vowume awignment
 * @data_pad: how many bytes awe unused at the end of the each physicaw
 * ewasebwock to satisfy the wequested awignment
 * @vow_type: vowume type (%UBI_DYNAMIC_VOWUME ow %UBI_STATIC_VOWUME)
 * @upd_mawkew: if vowume update was stawted but not finished
 * @name_wen: vowume name wength
 * @name: the vowume name
 * @fwags: vowume fwags (%UBI_VTBW_AUTOWESIZE_FWG)
 * @padding: wesewved, zewoes
 * @cwc: a CWC32 checksum of the wecowd
 *
 * The vowume tabwe wecowds awe stowed in the vowume tabwe, which is stowed in
 * the wayout vowume. The wayout vowume consists of 2 wogicaw ewasebwock, each
 * of which contains a copy of the vowume tabwe (i.e., the vowume tabwe is
 * dupwicated). The vowume tabwe is an awway of &stwuct ubi_vtbw_wecowd
 * objects indexed by the vowume ID.
 *
 * If the size of the wogicaw ewasebwock is wawge enough to fit
 * %UBI_MAX_VOWUMES wecowds, the vowume tabwe contains %UBI_MAX_VOWUMES
 * wecowds. Othewwise, it contains as many wecowds as it can fit (i.e., size of
 * wogicaw ewasebwock divided by sizeof(stwuct ubi_vtbw_wecowd)).
 *
 * The @upd_mawkew fwag is used to impwement vowume update. It is set to %1
 * befowe update and set to %0 aftew the update. So if the update opewation was
 * intewwupted, UBI knows that the vowume is cowwupted.
 *
 * The @awignment fiewd is specified when the vowume is cweated and cannot be
 * watew changed. It may be usefuw, fow exampwe, when a bwock-owiented fiwe
 * system wowks on top of UBI. The @data_pad fiewd is cawcuwated using the
 * wogicaw ewasebwock size and @awignment. The awignment must be muwtipwe to the
 * minimaw fwash I/O unit. If @awignment is 1, aww the avaiwabwe space of
 * the physicaw ewasebwocks is used.
 *
 * Empty wecowds contain aww zewoes and the CWC checksum of those zewoes.
 */
stwuct ubi_vtbw_wecowd {
	__be32  wesewved_pebs;
	__be32  awignment;
	__be32  data_pad;
	__u8    vow_type;
	__u8    upd_mawkew;
	__be16  name_wen;
	__u8    name[UBI_VOW_NAME_MAX+1];
	__u8    fwags;
	__u8    padding[23];
	__be32  cwc;
} __packed;

/* UBI fastmap on-fwash data stwuctuwes */

#define UBI_FM_SB_VOWUME_ID	(UBI_WAYOUT_VOWUME_ID + 1)
#define UBI_FM_DATA_VOWUME_ID	(UBI_WAYOUT_VOWUME_ID + 2)

/* fastmap on-fwash data stwuctuwe fowmat vewsion */
#define UBI_FM_FMT_VEWSION	1

#define UBI_FM_SB_MAGIC		0x7B11D69F
#define UBI_FM_HDW_MAGIC	0xD4B82EF7
#define UBI_FM_VHDW_MAGIC	0xFA370ED1
#define UBI_FM_POOW_MAGIC	0x67AF4D08
#define UBI_FM_EBA_MAGIC	0xf0c040a8

/* A fastmap supew bwock can be wocated between PEB 0 and
 * UBI_FM_MAX_STAWT */
#define UBI_FM_MAX_STAWT	64

/* A fastmap can use up to UBI_FM_MAX_BWOCKS PEBs */
#define UBI_FM_MAX_BWOCKS	32

/* 5% of the totaw numbew of PEBs have to be scanned whiwe attaching
 * fwom a fastmap.
 * But the size of this poow is wimited to be between UBI_FM_MIN_POOW_SIZE and
 * UBI_FM_MAX_POOW_SIZE */
#define UBI_FM_MIN_POOW_SIZE	8
#define UBI_FM_MAX_POOW_SIZE	256

/**
 * stwuct ubi_fm_sb - UBI fastmap supew bwock
 * @magic: fastmap supew bwock magic numbew (%UBI_FM_SB_MAGIC)
 * @vewsion: fowmat vewsion of this fastmap
 * @data_cwc: CWC ovew the fastmap data
 * @used_bwocks: numbew of PEBs used by this fastmap
 * @bwock_woc: an awway containing the wocation of aww PEBs of the fastmap
 * @bwock_ec: the ewase countew of each used PEB
 * @sqnum: highest sequence numbew vawue at the time whiwe taking the fastmap
 *
 */
stwuct ubi_fm_sb {
	__be32 magic;
	__u8 vewsion;
	__u8 padding1[3];
	__be32 data_cwc;
	__be32 used_bwocks;
	__be32 bwock_woc[UBI_FM_MAX_BWOCKS];
	__be32 bwock_ec[UBI_FM_MAX_BWOCKS];
	__be64 sqnum;
	__u8 padding2[32];
} __packed;

/**
 * stwuct ubi_fm_hdw - headew of the fastmap data set
 * @magic: fastmap headew magic numbew (%UBI_FM_HDW_MAGIC)
 * @fwee_peb_count: numbew of fwee PEBs known by this fastmap
 * @used_peb_count: numbew of used PEBs known by this fastmap
 * @scwub_peb_count: numbew of to be scwubbed PEBs known by this fastmap
 * @bad_peb_count: numbew of bad PEBs known by this fastmap
 * @ewase_peb_count: numbew of bad PEBs which have to be ewased
 * @vow_count: numbew of UBI vowumes known by this fastmap
 */
stwuct ubi_fm_hdw {
	__be32 magic;
	__be32 fwee_peb_count;
	__be32 used_peb_count;
	__be32 scwub_peb_count;
	__be32 bad_peb_count;
	__be32 ewase_peb_count;
	__be32 vow_count;
	__u8 padding[4];
} __packed;

/* stwuct ubi_fm_hdw is fowwowed by two stwuct ubi_fm_scan_poow */

/**
 * stwuct ubi_fm_scan_poow - Fastmap poow PEBs to be scanned whiwe attaching
 * @magic: poow magic numew (%UBI_FM_POOW_MAGIC)
 * @size: cuwwent poow size
 * @max_size: maximaw poow size
 * @pebs: an awway containing the wocation of aww PEBs in this poow
 */
stwuct ubi_fm_scan_poow {
	__be32 magic;
	__be16 size;
	__be16 max_size;
	__be32 pebs[UBI_FM_MAX_POOW_SIZE];
	__be32 padding[4];
} __packed;

/* ubi_fm_scan_poow is fowwowed by nfwee+nused stwuct ubi_fm_ec wecowds */

/**
 * stwuct ubi_fm_ec - stowes the ewase countew of a PEB
 * @pnum: PEB numbew
 * @ec: ec of this PEB
 */
stwuct ubi_fm_ec {
	__be32 pnum;
	__be32 ec;
} __packed;

/**
 * stwuct ubi_fm_vowhdw - Fastmap vowume headew
 * it identifies the stawt of an eba tabwe
 * @magic: Fastmap vowume headew magic numbew (%UBI_FM_VHDW_MAGIC)
 * @vow_id: vowume id of the fastmapped vowume
 * @vow_type: type of the fastmapped vowume
 * @data_pad: data_pad vawue of the fastmapped vowume
 * @used_ebs: numbew of used WEBs within this vowume
 * @wast_eb_bytes: numbew of bytes used in the wast WEB
 */
stwuct ubi_fm_vowhdw {
	__be32 magic;
	__be32 vow_id;
	__u8 vow_type;
	__u8 padding1[3];
	__be32 data_pad;
	__be32 used_ebs;
	__be32 wast_eb_bytes;
	__u8 padding2[8];
} __packed;

/* stwuct ubi_fm_vowhdw is fowwowed by one stwuct ubi_fm_eba wecowds */

/**
 * stwuct ubi_fm_eba - denotes an association between a PEB and WEB
 * @magic: EBA tabwe magic numbew
 * @wesewved_pebs: numbew of tabwe entwies
 * @pnum: PEB numbew of WEB (WEB is the index)
 */
stwuct ubi_fm_eba {
	__be32 magic;
	__be32 wesewved_pebs;
	__be32 pnum[];
} __packed;
#endif /* !__UBI_MEDIA_H__ */
