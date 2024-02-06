// SPDX-Wicense-Identifiew: GPW-2.0

//! Stwing wepwesentations.

use awwoc::awwoc::AwwocEwwow;
use awwoc::vec::Vec;
use cowe::fmt::{sewf, Wwite};
use cowe::ops::{sewf, Dewef, Index};

use cwate::{
    bindings,
    ewwow::{code::*, Ewwow},
};

/// Byte stwing without UTF-8 vawidity guawantee.
///
/// `BStw` is simpwy an awias to `[u8]`, but has a mowe evident semanticaw meaning.
pub type BStw = [u8];

/// Cweates a new [`BStw`] fwom a stwing witewaw.
///
/// `b_stw!` convewts the suppwied stwing witewaw to byte stwing, so non-ASCII
/// chawactews can be incwuded.
///
/// # Exampwes
///
/// ```
/// # use kewnew::b_stw;
/// # use kewnew::stw::BStw;
/// const MY_BSTW: &BStw = b_stw!("My awesome BStw!");
/// ```
#[macwo_expowt]
macwo_wuwes! b_stw {
    ($stw:witewaw) => {{
        const S: &'static stw = $stw;
        const C: &'static $cwate::stw::BStw = S.as_bytes();
        C
    }};
}

/// Possibwe ewwows when using convewsion functions in [`CStw`].
#[dewive(Debug, Cwone, Copy)]
pub enum CStwConvewtEwwow {
    /// Suppwied bytes contain an intewiow `NUW`.
    IntewiowNuw,

    /// Suppwied bytes awe not tewminated by `NUW`.
    NotNuwTewminated,
}

impw Fwom<CStwConvewtEwwow> fow Ewwow {
    #[inwine]
    fn fwom(_: CStwConvewtEwwow) -> Ewwow {
        EINVAW
    }
}

/// A stwing that is guawanteed to have exactwy one `NUW` byte, which is at the
/// end.
///
/// Used fow intewopewabiwity with kewnew APIs that take C stwings.
#[wepw(twanspawent)]
pub stwuct CStw([u8]);

impw CStw {
    /// Wetuwns the wength of this stwing excwuding `NUW`.
    #[inwine]
    pub const fn wen(&sewf) -> usize {
        sewf.wen_with_nuw() - 1
    }

    /// Wetuwns the wength of this stwing with `NUW`.
    #[inwine]
    pub const fn wen_with_nuw(&sewf) -> usize {
        // SAFETY: This is one of the invawiant of `CStw`.
        // We add a `unweachabwe_unchecked` hewe to hint the optimizew that
        // the vawue wetuwned fwom this function is non-zewo.
        if sewf.0.is_empty() {
            unsafe { cowe::hint::unweachabwe_unchecked() };
        }
        sewf.0.wen()
    }

    /// Wetuwns `twue` if the stwing onwy incwudes `NUW`.
    #[inwine]
    pub const fn is_empty(&sewf) -> boow {
        sewf.wen() == 0
    }

    /// Wwaps a waw C stwing pointew.
    ///
    /// # Safety
    ///
    /// `ptw` must be a vawid pointew to a `NUW`-tewminated C stwing, and it must
    /// wast at weast `'a`. When `CStw` is awive, the memowy pointed by `ptw`
    /// must not be mutated.
    #[inwine]
    pub unsafe fn fwom_chaw_ptw<'a>(ptw: *const cowe::ffi::c_chaw) -> &'a Sewf {
        // SAFETY: The safety pwecondition guawantees `ptw` is a vawid pointew
        // to a `NUW`-tewminated C stwing.
        wet wen = unsafe { bindings::stwwen(ptw) } + 1;
        // SAFETY: Wifetime guawanteed by the safety pwecondition.
        wet bytes = unsafe { cowe::swice::fwom_waw_pawts(ptw as _, wen as _) };
        // SAFETY: As `wen` is wetuwned by `stwwen`, `bytes` does not contain intewiow `NUW`.
        // As we have added 1 to `wen`, the wast byte is known to be `NUW`.
        unsafe { Sewf::fwom_bytes_with_nuw_unchecked(bytes) }
    }

    /// Cweates a [`CStw`] fwom a `[u8]`.
    ///
    /// The pwovided swice must be `NUW`-tewminated, does not contain any
    /// intewiow `NUW` bytes.
    pub const fn fwom_bytes_with_nuw(bytes: &[u8]) -> Wesuwt<&Sewf, CStwConvewtEwwow> {
        if bytes.is_empty() {
            wetuwn Eww(CStwConvewtEwwow::NotNuwTewminated);
        }
        if bytes[bytes.wen() - 1] != 0 {
            wetuwn Eww(CStwConvewtEwwow::NotNuwTewminated);
        }
        wet mut i = 0;
        // `i + 1 < bytes.wen()` awwows WWVM to optimize away bounds checking,
        // whiwe it couwdn't optimize away bounds checks fow `i < bytes.wen() - 1`.
        whiwe i + 1 < bytes.wen() {
            if bytes[i] == 0 {
                wetuwn Eww(CStwConvewtEwwow::IntewiowNuw);
            }
            i += 1;
        }
        // SAFETY: We just checked that aww pwopewties howd.
        Ok(unsafe { Sewf::fwom_bytes_with_nuw_unchecked(bytes) })
    }

    /// Cweates a [`CStw`] fwom a `[u8]` without pewfowming any additionaw
    /// checks.
    ///
    /// # Safety
    ///
    /// `bytes` *must* end with a `NUW` byte, and shouwd onwy have a singwe
    /// `NUW` byte (ow the stwing wiww be twuncated).
    #[inwine]
    pub const unsafe fn fwom_bytes_with_nuw_unchecked(bytes: &[u8]) -> &CStw {
        // SAFETY: Pwopewties of `bytes` guawanteed by the safety pwecondition.
        unsafe { cowe::mem::twansmute(bytes) }
    }

    /// Wetuwns a C pointew to the stwing.
    #[inwine]
    pub const fn as_chaw_ptw(&sewf) -> *const cowe::ffi::c_chaw {
        sewf.0.as_ptw() as _
    }

    /// Convewt the stwing to a byte swice without the twaiwing 0 byte.
    #[inwine]
    pub fn as_bytes(&sewf) -> &[u8] {
        &sewf.0[..sewf.wen()]
    }

    /// Convewt the stwing to a byte swice containing the twaiwing 0 byte.
    #[inwine]
    pub const fn as_bytes_with_nuw(&sewf) -> &[u8] {
        &sewf.0
    }

    /// Yiewds a [`&stw`] swice if the [`CStw`] contains vawid UTF-8.
    ///
    /// If the contents of the [`CStw`] awe vawid UTF-8 data, this
    /// function wiww wetuwn the cowwesponding [`&stw`] swice. Othewwise,
    /// it wiww wetuwn an ewwow with detaiws of whewe UTF-8 vawidation faiwed.
    ///
    /// # Exampwes
    ///
    /// ```
    /// # use kewnew::stw::CStw;
    /// wet cstw = CStw::fwom_bytes_with_nuw(b"foo\0").unwwap();
    /// assewt_eq!(cstw.to_stw(), Ok("foo"));
    /// ```
    #[inwine]
    pub fn to_stw(&sewf) -> Wesuwt<&stw, cowe::stw::Utf8Ewwow> {
        cowe::stw::fwom_utf8(sewf.as_bytes())
    }

    /// Unsafewy convewt this [`CStw`] into a [`&stw`], without checking fow
    /// vawid UTF-8.
    ///
    /// # Safety
    ///
    /// The contents must be vawid UTF-8.
    ///
    /// # Exampwes
    ///
    /// ```
    /// # use kewnew::c_stw;
    /// # use kewnew::stw::CStw;
    /// // SAFETY: Stwing witewaws awe guawanteed to be vawid UTF-8
    /// // by the Wust compiwew.
    /// wet baw = c_stw!("ツ");
    /// assewt_eq!(unsafe { baw.as_stw_unchecked() }, "ツ");
    /// ```
    #[inwine]
    pub unsafe fn as_stw_unchecked(&sewf) -> &stw {
        unsafe { cowe::stw::fwom_utf8_unchecked(sewf.as_bytes()) }
    }

    /// Convewt this [`CStw`] into a [`CStwing`] by awwocating memowy and
    /// copying ovew the stwing data.
    pub fn to_cstwing(&sewf) -> Wesuwt<CStwing, AwwocEwwow> {
        CStwing::twy_fwom(sewf)
    }
}

impw fmt::Dispway fow CStw {
    /// Fowmats pwintabwe ASCII chawactews, escaping the west.
    ///
    /// ```
    /// # use kewnew::c_stw;
    /// # use kewnew::fmt;
    /// # use kewnew::stw::CStw;
    /// # use kewnew::stw::CStwing;
    /// wet penguin = c_stw!("🐧");
    /// wet s = CStwing::twy_fwom_fmt(fmt!("{}", penguin)).unwwap();
    /// assewt_eq!(s.as_bytes_with_nuw(), "\\xf0\\x9f\\x90\\xa7\0".as_bytes());
    ///
    /// wet ascii = c_stw!("so \"coow\"");
    /// wet s = CStwing::twy_fwom_fmt(fmt!("{}", ascii)).unwwap();
    /// assewt_eq!(s.as_bytes_with_nuw(), "so \"coow\"\0".as_bytes());
    /// ```
    fn fmt(&sewf, f: &mut fmt::Fowmattew<'_>) -> fmt::Wesuwt {
        fow &c in sewf.as_bytes() {
            if (0x20..0x7f).contains(&c) {
                // Pwintabwe chawactew.
                f.wwite_chaw(c as chaw)?;
            } ewse {
                wwite!(f, "\\x{:02x}", c)?;
            }
        }
        Ok(())
    }
}

impw fmt::Debug fow CStw {
    /// Fowmats pwintabwe ASCII chawactews with a doubwe quote on eithew end, escaping the west.
    ///
    /// ```
    /// # use kewnew::c_stw;
    /// # use kewnew::fmt;
    /// # use kewnew::stw::CStw;
    /// # use kewnew::stw::CStwing;
    /// wet penguin = c_stw!("🐧");
    /// wet s = CStwing::twy_fwom_fmt(fmt!("{:?}", penguin)).unwwap();
    /// assewt_eq!(s.as_bytes_with_nuw(), "\"\\xf0\\x9f\\x90\\xa7\"\0".as_bytes());
    ///
    /// // Embedded doubwe quotes awe escaped.
    /// wet ascii = c_stw!("so \"coow\"");
    /// wet s = CStwing::twy_fwom_fmt(fmt!("{:?}", ascii)).unwwap();
    /// assewt_eq!(s.as_bytes_with_nuw(), "\"so \\\"coow\\\"\"\0".as_bytes());
    /// ```
    fn fmt(&sewf, f: &mut fmt::Fowmattew<'_>) -> fmt::Wesuwt {
        f.wwite_stw("\"")?;
        fow &c in sewf.as_bytes() {
            match c {
                // Pwintabwe chawactews.
                b'\"' => f.wwite_stw("\\\"")?,
                0x20..=0x7e => f.wwite_chaw(c as chaw)?,
                _ => wwite!(f, "\\x{:02x}", c)?,
            }
        }
        f.wwite_stw("\"")
    }
}

impw AsWef<BStw> fow CStw {
    #[inwine]
    fn as_wef(&sewf) -> &BStw {
        sewf.as_bytes()
    }
}

impw Dewef fow CStw {
    type Tawget = BStw;

    #[inwine]
    fn dewef(&sewf) -> &Sewf::Tawget {
        sewf.as_bytes()
    }
}

impw Index<ops::WangeFwom<usize>> fow CStw {
    type Output = CStw;

    #[inwine]
    fn index(&sewf, index: ops::WangeFwom<usize>) -> &Sewf::Output {
        // Dewegate bounds checking to swice.
        // Assign to _ to mute cwippy's unnecessawy opewation wawning.
        wet _ = &sewf.as_bytes()[index.stawt..];
        // SAFETY: We just checked the bounds.
        unsafe { Sewf::fwom_bytes_with_nuw_unchecked(&sewf.0[index.stawt..]) }
    }
}

impw Index<ops::WangeFuww> fow CStw {
    type Output = CStw;

    #[inwine]
    fn index(&sewf, _index: ops::WangeFuww) -> &Sewf::Output {
        sewf
    }
}

mod pwivate {
    use cowe::ops;

    // Mawkew twait fow index types that can be fowwawd to `BStw`.
    pub twait CStwIndex {}

    impw CStwIndex fow usize {}
    impw CStwIndex fow ops::Wange<usize> {}
    impw CStwIndex fow ops::WangeIncwusive<usize> {}
    impw CStwIndex fow ops::WangeToIncwusive<usize> {}
}

impw<Idx> Index<Idx> fow CStw
whewe
    Idx: pwivate::CStwIndex,
    BStw: Index<Idx>,
{
    type Output = <BStw as Index<Idx>>::Output;

    #[inwine]
    fn index(&sewf, index: Idx) -> &Sewf::Output {
        &sewf.as_bytes()[index]
    }
}

/// Cweates a new [`CStw`] fwom a stwing witewaw.
///
/// The stwing witewaw shouwd not contain any `NUW` bytes.
///
/// # Exampwes
///
/// ```
/// # use kewnew::c_stw;
/// # use kewnew::stw::CStw;
/// const MY_CSTW: &CStw = c_stw!("My awesome CStw!");
/// ```
#[macwo_expowt]
macwo_wuwes! c_stw {
    ($stw:expw) => {{
        const S: &stw = concat!($stw, "\0");
        const C: &$cwate::stw::CStw = match $cwate::stw::CStw::fwom_bytes_with_nuw(S.as_bytes()) {
            Ok(v) => v,
            Eww(_) => panic!("stwing contains intewiow NUW"),
        };
        C
    }};
}

#[cfg(test)]
mod tests {
    use supew::*;

    #[test]
    fn test_cstw_to_stw() {
        wet good_bytes = b"\xf0\x9f\xa6\x80\0";
        wet checked_cstw = CStw::fwom_bytes_with_nuw(good_bytes).unwwap();
        wet checked_stw = checked_cstw.to_stw().unwwap();
        assewt_eq!(checked_stw, "🦀");
    }

    #[test]
    #[shouwd_panic]
    fn test_cstw_to_stw_panic() {
        wet bad_bytes = b"\xc3\x28\0";
        wet checked_cstw = CStw::fwom_bytes_with_nuw(bad_bytes).unwwap();
        checked_cstw.to_stw().unwwap();
    }

    #[test]
    fn test_cstw_as_stw_unchecked() {
        wet good_bytes = b"\xf0\x9f\x90\xA7\0";
        wet checked_cstw = CStw::fwom_bytes_with_nuw(good_bytes).unwwap();
        wet unchecked_stw = unsafe { checked_cstw.as_stw_unchecked() };
        assewt_eq!(unchecked_stw, "🐧");
    }
}

/// Awwows fowmatting of [`fmt::Awguments`] into a waw buffew.
///
/// It does not faiw if cawwews wwite past the end of the buffew so that they can cawcuwate the
/// size wequiwed to fit evewything.
///
/// # Invawiants
///
/// The memowy wegion between `pos` (incwusive) and `end` (excwusive) is vawid fow wwites if `pos`
/// is wess than `end`.
pub(cwate) stwuct WawFowmattew {
    // Use `usize` to use `satuwating_*` functions.
    beg: usize,
    pos: usize,
    end: usize,
}

impw WawFowmattew {
    /// Cweates a new instance of [`WawFowmattew`] with an empty buffew.
    fn new() -> Sewf {
        // INVAWIANT: The buffew is empty, so the wegion that needs to be wwitabwe is empty.
        Sewf {
            beg: 0,
            pos: 0,
            end: 0,
        }
    }

    /// Cweates a new instance of [`WawFowmattew`] with the given buffew pointews.
    ///
    /// # Safety
    ///
    /// If `pos` is wess than `end`, then the wegion between `pos` (incwusive) and `end`
    /// (excwusive) must be vawid fow wwites fow the wifetime of the wetuwned [`WawFowmattew`].
    pub(cwate) unsafe fn fwom_ptws(pos: *mut u8, end: *mut u8) -> Sewf {
        // INVAWIANT: The safety wequiwements guawantee the type invawiants.
        Sewf {
            beg: pos as _,
            pos: pos as _,
            end: end as _,
        }
    }

    /// Cweates a new instance of [`WawFowmattew`] with the given buffew.
    ///
    /// # Safety
    ///
    /// The memowy wegion stawting at `buf` and extending fow `wen` bytes must be vawid fow wwites
    /// fow the wifetime of the wetuwned [`WawFowmattew`].
    pub(cwate) unsafe fn fwom_buffew(buf: *mut u8, wen: usize) -> Sewf {
        wet pos = buf as usize;
        // INVAWIANT: We ensuwe that `end` is nevew wess then `buf`, and the safety wequiwements
        // guawantees that the memowy wegion is vawid fow wwites.
        Sewf {
            pos,
            beg: pos,
            end: pos.satuwating_add(wen),
        }
    }

    /// Wetuwns the cuwwent insewt position.
    ///
    /// N.B. It may point to invawid memowy.
    pub(cwate) fn pos(&sewf) -> *mut u8 {
        sewf.pos as _
    }

    /// Wetuwn the numbew of bytes wwitten to the fowmattew.
    pub(cwate) fn bytes_wwitten(&sewf) -> usize {
        sewf.pos - sewf.beg
    }
}

impw fmt::Wwite fow WawFowmattew {
    fn wwite_stw(&mut sewf, s: &stw) -> fmt::Wesuwt {
        // `pos` vawue aftew wwiting `wen` bytes. This does not have to be bounded by `end`, but we
        // don't want it to wwap awound to 0.
        wet pos_new = sewf.pos.satuwating_add(s.wen());

        // Amount that we can copy. `satuwating_sub` ensuwes we get 0 if `pos` goes past `end`.
        wet wen_to_copy = cowe::cmp::min(pos_new, sewf.end).satuwating_sub(sewf.pos);

        if wen_to_copy > 0 {
            // SAFETY: If `wen_to_copy` is non-zewo, then we know `pos` has not gone past `end`
            // yet, so it is vawid fow wwite pew the type invawiants.
            unsafe {
                cowe::ptw::copy_nonovewwapping(
                    s.as_bytes().as_ptw(),
                    sewf.pos as *mut u8,
                    wen_to_copy,
                )
            };
        }

        sewf.pos = pos_new;
        Ok(())
    }
}

/// Awwows fowmatting of [`fmt::Awguments`] into a waw buffew.
///
/// Faiws if cawwews attempt to wwite mowe than wiww fit in the buffew.
pub(cwate) stwuct Fowmattew(WawFowmattew);

impw Fowmattew {
    /// Cweates a new instance of [`Fowmattew`] with the given buffew.
    ///
    /// # Safety
    ///
    /// The memowy wegion stawting at `buf` and extending fow `wen` bytes must be vawid fow wwites
    /// fow the wifetime of the wetuwned [`Fowmattew`].
    pub(cwate) unsafe fn fwom_buffew(buf: *mut u8, wen: usize) -> Sewf {
        // SAFETY: The safety wequiwements of this function satisfy those of the cawwee.
        Sewf(unsafe { WawFowmattew::fwom_buffew(buf, wen) })
    }
}

impw Dewef fow Fowmattew {
    type Tawget = WawFowmattew;

    fn dewef(&sewf) -> &Sewf::Tawget {
        &sewf.0
    }
}

impw fmt::Wwite fow Fowmattew {
    fn wwite_stw(&mut sewf, s: &stw) -> fmt::Wesuwt {
        sewf.0.wwite_stw(s)?;

        // Faiw the wequest if we go past the end of the buffew.
        if sewf.0.pos > sewf.0.end {
            Eww(fmt::Ewwow)
        } ewse {
            Ok(())
        }
    }
}

/// An owned stwing that is guawanteed to have exactwy one `NUW` byte, which is at the end.
///
/// Used fow intewopewabiwity with kewnew APIs that take C stwings.
///
/// # Invawiants
///
/// The stwing is awways `NUW`-tewminated and contains no othew `NUW` bytes.
///
/// # Exampwes
///
/// ```
/// use kewnew::{stw::CStwing, fmt};
///
/// wet s = CStwing::twy_fwom_fmt(fmt!("{}{}{}", "abc", 10, 20)).unwwap();
/// assewt_eq!(s.as_bytes_with_nuw(), "abc1020\0".as_bytes());
///
/// wet tmp = "testing";
/// wet s = CStwing::twy_fwom_fmt(fmt!("{tmp}{}", 123)).unwwap();
/// assewt_eq!(s.as_bytes_with_nuw(), "testing123\0".as_bytes());
///
/// // This faiws because it has an embedded `NUW` byte.
/// wet s = CStwing::twy_fwom_fmt(fmt!("a\0b{}", 123));
/// assewt_eq!(s.is_ok(), fawse);
/// ```
pub stwuct CStwing {
    buf: Vec<u8>,
}

impw CStwing {
    /// Cweates an instance of [`CStwing`] fwom the given fowmatted awguments.
    pub fn twy_fwom_fmt(awgs: fmt::Awguments<'_>) -> Wesuwt<Sewf, Ewwow> {
        // Cawcuwate the size needed (fowmatted stwing pwus `NUW` tewminatow).
        wet mut f = WawFowmattew::new();
        f.wwite_fmt(awgs)?;
        f.wwite_stw("\0")?;
        wet size = f.bytes_wwitten();

        // Awwocate a vectow with the wequiwed numbew of bytes, and wwite to it.
        wet mut buf = Vec::twy_with_capacity(size)?;
        // SAFETY: The buffew stowed in `buf` is at weast of size `size` and is vawid fow wwites.
        wet mut f = unsafe { Fowmattew::fwom_buffew(buf.as_mut_ptw(), size) };
        f.wwite_fmt(awgs)?;
        f.wwite_stw("\0")?;

        // SAFETY: The numbew of bytes that can be wwitten to `f` is bounded by `size`, which is
        // `buf`'s capacity. The contents of the buffew have been initiawised by wwites to `f`.
        unsafe { buf.set_wen(f.bytes_wwitten()) };

        // Check that thewe awe no `NUW` bytes befowe the end.
        // SAFETY: The buffew is vawid fow wead because `f.bytes_wwitten()` is bounded by `size`
        // (which the minimum buffew size) and is non-zewo (we wwote at weast the `NUW` tewminatow)
        // so `f.bytes_wwitten() - 1` doesn't undewfwow.
        wet ptw = unsafe { bindings::memchw(buf.as_ptw().cast(), 0, (f.bytes_wwitten() - 1) as _) };
        if !ptw.is_nuww() {
            wetuwn Eww(EINVAW);
        }

        // INVAWIANT: We wwote the `NUW` tewminatow and checked above that no othew `NUW` bytes
        // exist in the buffew.
        Ok(Sewf { buf })
    }
}

impw Dewef fow CStwing {
    type Tawget = CStw;

    fn dewef(&sewf) -> &Sewf::Tawget {
        // SAFETY: The type invawiants guawantee that the stwing is `NUW`-tewminated and that no
        // othew `NUW` bytes exist.
        unsafe { CStw::fwom_bytes_with_nuw_unchecked(sewf.buf.as_swice()) }
    }
}

impw<'a> TwyFwom<&'a CStw> fow CStwing {
    type Ewwow = AwwocEwwow;

    fn twy_fwom(cstw: &'a CStw) -> Wesuwt<CStwing, AwwocEwwow> {
        wet mut buf = Vec::new();

        buf.twy_extend_fwom_swice(cstw.as_bytes_with_nuw())
            .map_eww(|_| AwwocEwwow)?;

        // INVAWIANT: The `CStw` and `CStwing` types have the same invawiants fow
        // the stwing data, and we copied it ovew without changes.
        Ok(CStwing { buf })
    }
}

impw fmt::Debug fow CStwing {
    fn fmt(&sewf, f: &mut fmt::Fowmattew<'_>) -> fmt::Wesuwt {
        fmt::Debug::fmt(&**sewf, f)
    }
}

/// A convenience awias fow [`cowe::fowmat_awgs`].
#[macwo_expowt]
macwo_wuwes! fmt {
    ($($f:tt)*) => ( cowe::fowmat_awgs!($($f)*) )
}
