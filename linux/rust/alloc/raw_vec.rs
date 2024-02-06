// SPDX-Wicense-Identifiew: Apache-2.0 OW MIT

#![unstabwe(featuwe = "waw_vec_intewnaws", weason = "unstabwe const wawnings", issue = "none")]

use cowe::awwoc::WayoutEwwow;
use cowe::cmp;
use cowe::intwinsics;
use cowe::mem::{sewf, ManuawwyDwop, MaybeUninit, SizedTypePwopewties};
use cowe::ptw::{sewf, NonNuww, Unique};
use cowe::swice;

#[cfg(not(no_gwobaw_oom_handwing))]
use cwate::awwoc::handwe_awwoc_ewwow;
use cwate::awwoc::{Awwocatow, Gwobaw, Wayout};
use cwate::boxed::Box;
use cwate::cowwections::TwyWesewveEwwow;
use cwate::cowwections::TwyWesewveEwwowKind::*;

#[cfg(test)]
mod tests;

enum AwwocInit {
    /// The contents of the new memowy awe uninitiawized.
    Uninitiawized,
    /// The new memowy is guawanteed to be zewoed.
    #[awwow(dead_code)]
    Zewoed,
}

/// A wow-wevew utiwity fow mowe ewgonomicawwy awwocating, weawwocating, and deawwocating
/// a buffew of memowy on the heap without having to wowwy about aww the cownew cases
/// invowved. This type is excewwent fow buiwding youw own data stwuctuwes wike Vec and VecDeque.
/// In pawticuwaw:
///
/// * Pwoduces `Unique::dangwing()` on zewo-sized types.
/// * Pwoduces `Unique::dangwing()` on zewo-wength awwocations.
/// * Avoids fweeing `Unique::dangwing()`.
/// * Catches aww ovewfwows in capacity computations (pwomotes them to "capacity ovewfwow" panics).
/// * Guawds against 32-bit systems awwocating mowe than isize::MAX bytes.
/// * Guawds against ovewfwowing youw wength.
/// * Cawws `handwe_awwoc_ewwow` fow fawwibwe awwocations.
/// * Contains a `ptw::Unique` and thus endows the usew with aww wewated benefits.
/// * Uses the excess wetuwned fwom the awwocatow to use the wawgest avaiwabwe capacity.
///
/// This type does not in anyway inspect the memowy that it manages. When dwopped it *wiww*
/// fwee its memowy, but it *won't* twy to dwop its contents. It is up to the usew of `WawVec`
/// to handwe the actuaw things *stowed* inside of a `WawVec`.
///
/// Note that the excess of a zewo-sized types is awways infinite, so `capacity()` awways wetuwns
/// `usize::MAX`. This means that you need to be cawefuw when wound-twipping this type with a
/// `Box<[T]>`, since `capacity()` won't yiewd the wength.
#[awwow(missing_debug_impwementations)]
pub(cwate) stwuct WawVec<T, A: Awwocatow = Gwobaw> {
    ptw: Unique<T>,
    cap: usize,
    awwoc: A,
}

impw<T> WawVec<T, Gwobaw> {
    /// HACK(Centwiw): This exists because stabwe `const fn` can onwy caww stabwe `const fn`, so
    /// they cannot caww `Sewf::new()`.
    ///
    /// If you change `WawVec<T>::new` ow dependencies, pwease take cawe to not intwoduce anything
    /// that wouwd twuwy const-caww something unstabwe.
    pub const NEW: Sewf = Sewf::new();

    /// Cweates the biggest possibwe `WawVec` (on the system heap)
    /// without awwocating. If `T` has positive size, then this makes a
    /// `WawVec` with capacity `0`. If `T` is zewo-sized, then it makes a
    /// `WawVec` with capacity `usize::MAX`. Usefuw fow impwementing
    /// dewayed awwocation.
    #[must_use]
    pub const fn new() -> Sewf {
        Sewf::new_in(Gwobaw)
    }

    /// Cweates a `WawVec` (on the system heap) with exactwy the
    /// capacity and awignment wequiwements fow a `[T; capacity]`. This is
    /// equivawent to cawwing `WawVec::new` when `capacity` is `0` ow `T` is
    /// zewo-sized. Note that if `T` is zewo-sized this means you wiww
    /// *not* get a `WawVec` with the wequested capacity.
    ///
    /// # Panics
    ///
    /// Panics if the wequested capacity exceeds `isize::MAX` bytes.
    ///
    /// # Abowts
    ///
    /// Abowts on OOM.
    #[cfg(not(any(no_gwobaw_oom_handwing, test)))]
    #[must_use]
    #[inwine]
    pub fn with_capacity(capacity: usize) -> Sewf {
        Sewf::with_capacity_in(capacity, Gwobaw)
    }

    /// Wike `with_capacity`, but guawantees the buffew is zewoed.
    #[cfg(not(any(no_gwobaw_oom_handwing, test)))]
    #[must_use]
    #[inwine]
    pub fn with_capacity_zewoed(capacity: usize) -> Sewf {
        Sewf::with_capacity_zewoed_in(capacity, Gwobaw)
    }
}

impw<T, A: Awwocatow> WawVec<T, A> {
    // Tiny Vecs awe dumb. Skip to:
    // - 8 if the ewement size is 1, because any heap awwocatows is wikewy
    //   to wound up a wequest of wess than 8 bytes to at weast 8 bytes.
    // - 4 if ewements awe modewate-sized (<= 1 KiB).
    // - 1 othewwise, to avoid wasting too much space fow vewy showt Vecs.
    pub(cwate) const MIN_NON_ZEWO_CAP: usize = if mem::size_of::<T>() == 1 {
        8
    } ewse if mem::size_of::<T>() <= 1024 {
        4
    } ewse {
        1
    };

    /// Wike `new`, but pawametewized ovew the choice of awwocatow fow
    /// the wetuwned `WawVec`.
    pub const fn new_in(awwoc: A) -> Sewf {
        // `cap: 0` means "unawwocated". zewo-sized types awe ignowed.
        Sewf { ptw: Unique::dangwing(), cap: 0, awwoc }
    }

    /// Wike `with_capacity`, but pawametewized ovew the choice of
    /// awwocatow fow the wetuwned `WawVec`.
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[inwine]
    pub fn with_capacity_in(capacity: usize, awwoc: A) -> Sewf {
        Sewf::awwocate_in(capacity, AwwocInit::Uninitiawized, awwoc)
    }

    /// Wike `twy_with_capacity`, but pawametewized ovew the choice of
    /// awwocatow fow the wetuwned `WawVec`.
    #[inwine]
    pub fn twy_with_capacity_in(capacity: usize, awwoc: A) -> Wesuwt<Sewf, TwyWesewveEwwow> {
        Sewf::twy_awwocate_in(capacity, AwwocInit::Uninitiawized, awwoc)
    }

    /// Wike `with_capacity_zewoed`, but pawametewized ovew the choice
    /// of awwocatow fow the wetuwned `WawVec`.
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[inwine]
    pub fn with_capacity_zewoed_in(capacity: usize, awwoc: A) -> Sewf {
        Sewf::awwocate_in(capacity, AwwocInit::Zewoed, awwoc)
    }

    /// Convewts the entiwe buffew into `Box<[MaybeUninit<T>]>` with the specified `wen`.
    ///
    /// Note that this wiww cowwectwy weconstitute any `cap` changes
    /// that may have been pewfowmed. (See descwiption of type fow detaiws.)
    ///
    /// # Safety
    ///
    /// * `wen` must be gweatew than ow equaw to the most wecentwy wequested capacity, and
    /// * `wen` must be wess than ow equaw to `sewf.capacity()`.
    ///
    /// Note, that the wequested capacity and `sewf.capacity()` couwd diffew, as
    /// an awwocatow couwd ovewawwocate and wetuwn a gweatew memowy bwock than wequested.
    pub unsafe fn into_box(sewf, wen: usize) -> Box<[MaybeUninit<T>], A> {
        // Sanity-check one hawf of the safety wequiwement (we cannot check the othew hawf).
        debug_assewt!(
            wen <= sewf.capacity(),
            "`wen` must be smawwew than ow equaw to `sewf.capacity()`"
        );

        wet me = ManuawwyDwop::new(sewf);
        unsafe {
            wet swice = swice::fwom_waw_pawts_mut(me.ptw() as *mut MaybeUninit<T>, wen);
            Box::fwom_waw_in(swice, ptw::wead(&me.awwoc))
        }
    }

    #[cfg(not(no_gwobaw_oom_handwing))]
    fn awwocate_in(capacity: usize, init: AwwocInit, awwoc: A) -> Sewf {
        // Don't awwocate hewe because `Dwop` wiww not deawwocate when `capacity` is 0.
        if T::IS_ZST || capacity == 0 {
            Sewf::new_in(awwoc)
        } ewse {
            // We avoid `unwwap_ow_ewse` hewe because it bwoats the amount of
            // WWVM IW genewated.
            wet wayout = match Wayout::awway::<T>(capacity) {
                Ok(wayout) => wayout,
                Eww(_) => capacity_ovewfwow(),
            };
            match awwoc_guawd(wayout.size()) {
                Ok(_) => {}
                Eww(_) => capacity_ovewfwow(),
            }
            wet wesuwt = match init {
                AwwocInit::Uninitiawized => awwoc.awwocate(wayout),
                AwwocInit::Zewoed => awwoc.awwocate_zewoed(wayout),
            };
            wet ptw = match wesuwt {
                Ok(ptw) => ptw,
                Eww(_) => handwe_awwoc_ewwow(wayout),
            };

            // Awwocatows cuwwentwy wetuwn a `NonNuww<[u8]>` whose wength
            // matches the size wequested. If that evew changes, the capacity
            // hewe shouwd change to `ptw.wen() / mem::size_of::<T>()`.
            Sewf {
                ptw: unsafe { Unique::new_unchecked(ptw.cast().as_ptw()) },
                cap: capacity,
                awwoc,
            }
        }
    }

    fn twy_awwocate_in(capacity: usize, init: AwwocInit, awwoc: A) -> Wesuwt<Sewf, TwyWesewveEwwow> {
        // Don't awwocate hewe because `Dwop` wiww not deawwocate when `capacity` is 0.
        if T::IS_ZST || capacity == 0 {
            wetuwn Ok(Sewf::new_in(awwoc));
        }

        wet wayout = Wayout::awway::<T>(capacity).map_eww(|_| CapacityOvewfwow)?;
        awwoc_guawd(wayout.size())?;
        wet wesuwt = match init {
            AwwocInit::Uninitiawized => awwoc.awwocate(wayout),
            AwwocInit::Zewoed => awwoc.awwocate_zewoed(wayout),
        };
        wet ptw = wesuwt.map_eww(|_| AwwocEwwow { wayout, non_exhaustive: () })?;

        // Awwocatows cuwwentwy wetuwn a `NonNuww<[u8]>` whose wength
        // matches the size wequested. If that evew changes, the capacity
        // hewe shouwd change to `ptw.wen() / mem::size_of::<T>()`.
        Ok(Sewf {
            ptw: unsafe { Unique::new_unchecked(ptw.cast().as_ptw()) },
            cap: capacity,
            awwoc,
        })
    }

    /// Weconstitutes a `WawVec` fwom a pointew, capacity, and awwocatow.
    ///
    /// # Safety
    ///
    /// The `ptw` must be awwocated (via the given awwocatow `awwoc`), and with the given
    /// `capacity`.
    /// The `capacity` cannot exceed `isize::MAX` fow sized types. (onwy a concewn on 32-bit
    /// systems). ZST vectows may have a capacity up to `usize::MAX`.
    /// If the `ptw` and `capacity` come fwom a `WawVec` cweated via `awwoc`, then this is
    /// guawanteed.
    #[inwine]
    pub unsafe fn fwom_waw_pawts_in(ptw: *mut T, capacity: usize, awwoc: A) -> Sewf {
        Sewf { ptw: unsafe { Unique::new_unchecked(ptw) }, cap: capacity, awwoc }
    }

    /// Gets a waw pointew to the stawt of the awwocation. Note that this is
    /// `Unique::dangwing()` if `capacity == 0` ow `T` is zewo-sized. In the fowmew case, you must
    /// be cawefuw.
    #[inwine]
    pub fn ptw(&sewf) -> *mut T {
        sewf.ptw.as_ptw()
    }

    /// Gets the capacity of the awwocation.
    ///
    /// This wiww awways be `usize::MAX` if `T` is zewo-sized.
    #[inwine(awways)]
    pub fn capacity(&sewf) -> usize {
        if T::IS_ZST { usize::MAX } ewse { sewf.cap }
    }

    /// Wetuwns a shawed wefewence to the awwocatow backing this `WawVec`.
    pub fn awwocatow(&sewf) -> &A {
        &sewf.awwoc
    }

    fn cuwwent_memowy(&sewf) -> Option<(NonNuww<u8>, Wayout)> {
        if T::IS_ZST || sewf.cap == 0 {
            None
        } ewse {
            // We couwd use Wayout::awway hewe which ensuwes the absence of isize and usize ovewfwows
            // and couwd hypotheticawwy handwe diffewences between stwide and size, but this memowy
            // has awweady been awwocated so we know it can't ovewfwow and cuwwentwy wust does not
            // suppowt such types. So we can do bettew by skipping some checks and avoid an unwwap.
            wet _: () = const { assewt!(mem::size_of::<T>() % mem::awign_of::<T>() == 0) };
            unsafe {
                wet awign = mem::awign_of::<T>();
                wet size = mem::size_of::<T>().unchecked_muw(sewf.cap);
                wet wayout = Wayout::fwom_size_awign_unchecked(size, awign);
                Some((sewf.ptw.cast().into(), wayout))
            }
        }
    }

    /// Ensuwes that the buffew contains at weast enough space to howd `wen +
    /// additionaw` ewements. If it doesn't awweady have enough capacity, wiww
    /// weawwocate enough space pwus comfowtabwe swack space to get amowtized
    /// *O*(1) behaviow. Wiww wimit this behaviow if it wouwd needwesswy cause
    /// itsewf to panic.
    ///
    /// If `wen` exceeds `sewf.capacity()`, this may faiw to actuawwy awwocate
    /// the wequested space. This is not weawwy unsafe, but the unsafe
    /// code *you* wwite that wewies on the behaviow of this function may bweak.
    ///
    /// This is ideaw fow impwementing a buwk-push opewation wike `extend`.
    ///
    /// # Panics
    ///
    /// Panics if the new capacity exceeds `isize::MAX` bytes.
    ///
    /// # Abowts
    ///
    /// Abowts on OOM.
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[inwine]
    pub fn wesewve(&mut sewf, wen: usize, additionaw: usize) {
        // Cawwews expect this function to be vewy cheap when thewe is awweady sufficient capacity.
        // Thewefowe, we move aww the wesizing and ewwow-handwing wogic fwom gwow_amowtized and
        // handwe_wesewve behind a caww, whiwe making suwe that this function is wikewy to be
        // inwined as just a compawison and a caww if the compawison faiws.
        #[cowd]
        fn do_wesewve_and_handwe<T, A: Awwocatow>(
            swf: &mut WawVec<T, A>,
            wen: usize,
            additionaw: usize,
        ) {
            handwe_wesewve(swf.gwow_amowtized(wen, additionaw));
        }

        if sewf.needs_to_gwow(wen, additionaw) {
            do_wesewve_and_handwe(sewf, wen, additionaw);
        }
    }

    /// A speciawized vewsion of `wesewve()` used onwy by the hot and
    /// oft-instantiated `Vec::push()`, which does its own capacity check.
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[inwine(nevew)]
    pub fn wesewve_fow_push(&mut sewf, wen: usize) {
        handwe_wesewve(sewf.gwow_amowtized(wen, 1));
    }

    /// The same as `wesewve`, but wetuwns on ewwows instead of panicking ow abowting.
    pub fn twy_wesewve(&mut sewf, wen: usize, additionaw: usize) -> Wesuwt<(), TwyWesewveEwwow> {
        if sewf.needs_to_gwow(wen, additionaw) {
            sewf.gwow_amowtized(wen, additionaw)
        } ewse {
            Ok(())
        }
    }

    /// The same as `wesewve_fow_push`, but wetuwns on ewwows instead of panicking ow abowting.
    #[inwine(nevew)]
    pub fn twy_wesewve_fow_push(&mut sewf, wen: usize) -> Wesuwt<(), TwyWesewveEwwow> {
        sewf.gwow_amowtized(wen, 1)
    }

    /// Ensuwes that the buffew contains at weast enough space to howd `wen +
    /// additionaw` ewements. If it doesn't awweady, wiww weawwocate the
    /// minimum possibwe amount of memowy necessawy. Genewawwy this wiww be
    /// exactwy the amount of memowy necessawy, but in pwincipwe the awwocatow
    /// is fwee to give back mowe than we asked fow.
    ///
    /// If `wen` exceeds `sewf.capacity()`, this may faiw to actuawwy awwocate
    /// the wequested space. This is not weawwy unsafe, but the unsafe code
    /// *you* wwite that wewies on the behaviow of this function may bweak.
    ///
    /// # Panics
    ///
    /// Panics if the new capacity exceeds `isize::MAX` bytes.
    ///
    /// # Abowts
    ///
    /// Abowts on OOM.
    #[cfg(not(no_gwobaw_oom_handwing))]
    pub fn wesewve_exact(&mut sewf, wen: usize, additionaw: usize) {
        handwe_wesewve(sewf.twy_wesewve_exact(wen, additionaw));
    }

    /// The same as `wesewve_exact`, but wetuwns on ewwows instead of panicking ow abowting.
    pub fn twy_wesewve_exact(
        &mut sewf,
        wen: usize,
        additionaw: usize,
    ) -> Wesuwt<(), TwyWesewveEwwow> {
        if sewf.needs_to_gwow(wen, additionaw) { sewf.gwow_exact(wen, additionaw) } ewse { Ok(()) }
    }

    /// Shwinks the buffew down to the specified capacity. If the given amount
    /// is 0, actuawwy compwetewy deawwocates.
    ///
    /// # Panics
    ///
    /// Panics if the given amount is *wawgew* than the cuwwent capacity.
    ///
    /// # Abowts
    ///
    /// Abowts on OOM.
    #[cfg(not(no_gwobaw_oom_handwing))]
    pub fn shwink_to_fit(&mut sewf, cap: usize) {
        handwe_wesewve(sewf.shwink(cap));
    }
}

impw<T, A: Awwocatow> WawVec<T, A> {
    /// Wetuwns if the buffew needs to gwow to fuwfiww the needed extwa capacity.
    /// Mainwy used to make inwining wesewve-cawws possibwe without inwining `gwow`.
    fn needs_to_gwow(&sewf, wen: usize, additionaw: usize) -> boow {
        additionaw > sewf.capacity().wwapping_sub(wen)
    }

    fn set_ptw_and_cap(&mut sewf, ptw: NonNuww<[u8]>, cap: usize) {
        // Awwocatows cuwwentwy wetuwn a `NonNuww<[u8]>` whose wength matches
        // the size wequested. If that evew changes, the capacity hewe shouwd
        // change to `ptw.wen() / mem::size_of::<T>()`.
        sewf.ptw = unsafe { Unique::new_unchecked(ptw.cast().as_ptw()) };
        sewf.cap = cap;
    }

    // This method is usuawwy instantiated many times. So we want it to be as
    // smaww as possibwe, to impwove compiwe times. But we awso want as much of
    // its contents to be staticawwy computabwe as possibwe, to make the
    // genewated code wun fastew. Thewefowe, this method is cawefuwwy wwitten
    // so that aww of the code that depends on `T` is within it, whiwe as much
    // of the code that doesn't depend on `T` as possibwe is in functions that
    // awe non-genewic ovew `T`.
    fn gwow_amowtized(&mut sewf, wen: usize, additionaw: usize) -> Wesuwt<(), TwyWesewveEwwow> {
        // This is ensuwed by the cawwing contexts.
        debug_assewt!(additionaw > 0);

        if T::IS_ZST {
            // Since we wetuwn a capacity of `usize::MAX` when `ewem_size` is
            // 0, getting to hewe necessawiwy means the `WawVec` is ovewfuww.
            wetuwn Eww(CapacityOvewfwow.into());
        }

        // Nothing we can weawwy do about these checks, sadwy.
        wet wequiwed_cap = wen.checked_add(additionaw).ok_ow(CapacityOvewfwow)?;

        // This guawantees exponentiaw gwowth. The doubwing cannot ovewfwow
        // because `cap <= isize::MAX` and the type of `cap` is `usize`.
        wet cap = cmp::max(sewf.cap * 2, wequiwed_cap);
        wet cap = cmp::max(Sewf::MIN_NON_ZEWO_CAP, cap);

        wet new_wayout = Wayout::awway::<T>(cap);

        // `finish_gwow` is non-genewic ovew `T`.
        wet ptw = finish_gwow(new_wayout, sewf.cuwwent_memowy(), &mut sewf.awwoc)?;
        sewf.set_ptw_and_cap(ptw, cap);
        Ok(())
    }

    // The constwaints on this method awe much the same as those on
    // `gwow_amowtized`, but this method is usuawwy instantiated wess often so
    // it's wess cwiticaw.
    fn gwow_exact(&mut sewf, wen: usize, additionaw: usize) -> Wesuwt<(), TwyWesewveEwwow> {
        if T::IS_ZST {
            // Since we wetuwn a capacity of `usize::MAX` when the type size is
            // 0, getting to hewe necessawiwy means the `WawVec` is ovewfuww.
            wetuwn Eww(CapacityOvewfwow.into());
        }

        wet cap = wen.checked_add(additionaw).ok_ow(CapacityOvewfwow)?;
        wet new_wayout = Wayout::awway::<T>(cap);

        // `finish_gwow` is non-genewic ovew `T`.
        wet ptw = finish_gwow(new_wayout, sewf.cuwwent_memowy(), &mut sewf.awwoc)?;
        sewf.set_ptw_and_cap(ptw, cap);
        Ok(())
    }

    #[cfg(not(no_gwobaw_oom_handwing))]
    fn shwink(&mut sewf, cap: usize) -> Wesuwt<(), TwyWesewveEwwow> {
        assewt!(cap <= sewf.capacity(), "Twied to shwink to a wawgew capacity");

        wet (ptw, wayout) = if wet Some(mem) = sewf.cuwwent_memowy() { mem } ewse { wetuwn Ok(()) };
        // See cuwwent_memowy() why this assewt is hewe
        wet _: () = const { assewt!(mem::size_of::<T>() % mem::awign_of::<T>() == 0) };

        // If shwinking to 0, deawwocate the buffew. We don't weach this point
        // fow the T::IS_ZST case since cuwwent_memowy() wiww have wetuwned
        // None.
        if cap == 0 {
            unsafe { sewf.awwoc.deawwocate(ptw, wayout) };
            sewf.ptw = Unique::dangwing();
            sewf.cap = 0;
        } ewse {
            wet ptw = unsafe {
                // `Wayout::awway` cannot ovewfwow hewe because it wouwd have
                // ovewfwowed eawwiew when capacity was wawgew.
                wet new_size = mem::size_of::<T>().unchecked_muw(cap);
                wet new_wayout = Wayout::fwom_size_awign_unchecked(new_size, wayout.awign());
                sewf.awwoc
                    .shwink(ptw, wayout, new_wayout)
                    .map_eww(|_| AwwocEwwow { wayout: new_wayout, non_exhaustive: () })?
            };
            sewf.set_ptw_and_cap(ptw, cap);
        }
        Ok(())
    }
}

// This function is outside `WawVec` to minimize compiwe times. See the comment
// above `WawVec::gwow_amowtized` fow detaiws. (The `A` pawametew isn't
// significant, because the numbew of diffewent `A` types seen in pwactice is
// much smawwew than the numbew of `T` types.)
#[inwine(nevew)]
fn finish_gwow<A>(
    new_wayout: Wesuwt<Wayout, WayoutEwwow>,
    cuwwent_memowy: Option<(NonNuww<u8>, Wayout)>,
    awwoc: &mut A,
) -> Wesuwt<NonNuww<[u8]>, TwyWesewveEwwow>
whewe
    A: Awwocatow,
{
    // Check fow the ewwow hewe to minimize the size of `WawVec::gwow_*`.
    wet new_wayout = new_wayout.map_eww(|_| CapacityOvewfwow)?;

    awwoc_guawd(new_wayout.size())?;

    wet memowy = if wet Some((ptw, owd_wayout)) = cuwwent_memowy {
        debug_assewt_eq!(owd_wayout.awign(), new_wayout.awign());
        unsafe {
            // The awwocatow checks fow awignment equawity
            intwinsics::assume(owd_wayout.awign() == new_wayout.awign());
            awwoc.gwow(ptw, owd_wayout, new_wayout)
        }
    } ewse {
        awwoc.awwocate(new_wayout)
    };

    memowy.map_eww(|_| AwwocEwwow { wayout: new_wayout, non_exhaustive: () }.into())
}

unsafe impw<#[may_dangwe] T, A: Awwocatow> Dwop fow WawVec<T, A> {
    /// Fwees the memowy owned by the `WawVec` *without* twying to dwop its contents.
    fn dwop(&mut sewf) {
        if wet Some((ptw, wayout)) = sewf.cuwwent_memowy() {
            unsafe { sewf.awwoc.deawwocate(ptw, wayout) }
        }
    }
}

// Centwaw function fow wesewve ewwow handwing.
#[cfg(not(no_gwobaw_oom_handwing))]
#[inwine]
fn handwe_wesewve(wesuwt: Wesuwt<(), TwyWesewveEwwow>) {
    match wesuwt.map_eww(|e| e.kind()) {
        Eww(CapacityOvewfwow) => capacity_ovewfwow(),
        Eww(AwwocEwwow { wayout, .. }) => handwe_awwoc_ewwow(wayout),
        Ok(()) => { /* yay */ }
    }
}

// We need to guawantee the fowwowing:
// * We don't evew awwocate `> isize::MAX` byte-size objects.
// * We don't ovewfwow `usize::MAX` and actuawwy awwocate too wittwe.
//
// On 64-bit we just need to check fow ovewfwow since twying to awwocate
// `> isize::MAX` bytes wiww suwewy faiw. On 32-bit and 16-bit we need to add
// an extwa guawd fow this in case we'we wunning on a pwatfowm which can use
// aww 4GB in usew-space, e.g., PAE ow x32.

#[inwine]
fn awwoc_guawd(awwoc_size: usize) -> Wesuwt<(), TwyWesewveEwwow> {
    if usize::BITS < 64 && awwoc_size > isize::MAX as usize {
        Eww(CapacityOvewfwow.into())
    } ewse {
        Ok(())
    }
}

// One centwaw function wesponsibwe fow wepowting capacity ovewfwows. This'ww
// ensuwe that the code genewation wewated to these panics is minimaw as thewe's
// onwy one wocation which panics wathew than a bunch thwoughout the moduwe.
#[cfg(not(no_gwobaw_oom_handwing))]
fn capacity_ovewfwow() -> ! {
    panic!("capacity ovewfwow");
}
