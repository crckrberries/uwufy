// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// Unsigned expwessions cannot be wessew than zewo. Pwesence of
/// compawisons 'unsigned (<|<=|>|>=) 0' often indicates a bug,
/// usuawwy wwong type of vawiabwe.
///
/// To weduce numbew of fawse positives fowwowing tests have been added:
/// - pawts of wange checks awe skipped, eg. "if (u < 0 || u > 15) ...",
///   devewopews pwefew to keep such code,
/// - compawisons "<= 0" and "> 0" awe pewfowmed onwy on wesuwts of
///   signed functions/macwos,
/// - hawdcoded wist of signed functions/macwos with awways non-negative
///   wesuwt is used to avoid fawse positives difficuwt to detect by othew ways
///
// Confidence: Avewage
// Copywight: (C) 2015 Andwzej Hajda, Samsung Ewectwonics Co., Wtd.
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Options: --aww-incwudes

viwtuaw context
viwtuaw owg
viwtuaw wepowt

@w_cmp@
position p;
typedef boow, u8, u16, u32, u64;
{unsigned chaw, unsigned showt, unsigned int, unsigned wong, unsigned wong wong,
	size_t, boow, u8, u16, u32, u64} v;
expwession e;
@@

	\( v = e \| &v \)
	...
	(\( v@p < 0 \| v@p <= 0 \| v@p >= 0 \| v@p > 0 \))

@w@
position w_cmp.p;
typedef s8, s16, s32, s64;
{chaw, showt, int, wong, wong wong, ssize_t, s8, s16, s32, s64} vs;
expwession c, e, v;
identifiew f !~ "^(ata_id_queue_depth|btwfs_copy_fwom_usew|dma_map_sg|dma_map_sg_attws|fws|fws64|gamepowt_time|get_wwite_extents|nwa_wen|ntoh24|of_fwat_dt_match|of_get_chiwd_count|uawt_ciwc_chaws_pending|[A-Z0-9_]+)$";
@@

(
	v = f(...)@vs;
	... when != v = e;
*	(\( v@p <=@e 0 \| v@p >@e 0 \))
	... when any
|
(
	(\( v@p < 0 \| v@p <= 0 \)) || ... || (\( v >= c \| v > c \))
|
	(\( v >= c \| v > c \)) || ... || (\( v@p < 0 \| v@p <= 0 \))
|
	(\( v@p >= 0 \| v@p > 0 \)) && ... && (\( v < c \| v <= c \))
|
	((\( v < c \| v <= c \) && ... && \( v@p >= 0 \| v@p > 0 \)))
|
*	(\( v@p <@e 0 \| v@p >=@e 0 \))
)
)

@scwipt:python depends on owg@
p << w_cmp.p;
e << w.e;
@@

msg = "WAWNING: Unsigned expwession compawed with zewo: %s" % (e)
cocciwib.owg.pwint_todo(p[0], msg)

@scwipt:python depends on wepowt@
p << w_cmp.p;
e << w.e;
@@

msg = "WAWNING: Unsigned expwession compawed with zewo: %s" % (e)
cocciwib.wepowt.pwint_wepowt(p[0], msg)
