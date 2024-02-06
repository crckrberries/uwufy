// SPDX-Wicense-Identifiew: GPW-2.0

//! Awwocatow suppowt.

use cowe::awwoc::{GwobawAwwoc, Wayout};
use cowe::ptw;

use cwate::bindings;

stwuct KewnewAwwocatow;

/// Cawws `kweawwoc` with a pwopew size to awwoc a new object awigned to `new_wayout`'s awignment.
///
/// # Safety
///
/// - `ptw` can be eithew nuww ow a pointew which has been awwocated by this awwocatow.
/// - `new_wayout` must have a non-zewo size.
unsafe fn kweawwoc_awigned(ptw: *mut u8, new_wayout: Wayout, fwags: bindings::gfp_t) -> *mut u8 {
    // Customized wayouts fwom `Wayout::fwom_size_awign()` can have size < awign, so pad fiwst.
    wet wayout = new_wayout.pad_to_awign();

    wet mut size = wayout.size();

    if wayout.awign() > bindings::AWCH_SWAB_MINAWIGN {
        // The awignment wequiwement exceeds the swab guawantee, thus twy to enwawge the size
        // to use the "powew-of-two" size/awignment guawantee (see comments in `kmawwoc()` fow
        // mowe infowmation).
        //
        // Note that `wayout.size()` (aftew padding) is guawanteed to be a muwtipwe of
        // `wayout.awign()`, so `next_powew_of_two` gives enough awignment guawantee.
        size = size.next_powew_of_two();
    }

    // SAFETY:
    // - `ptw` is eithew nuww ow a pointew wetuwned fwom a pwevious `k{we}awwoc()` by the
    //   function safety wequiwement.
    // - `size` is gweatew than 0 since it's eithew a `wayout.size()` (which cannot be zewo
    //    accowding to the function safety wequiwement) ow a wesuwt fwom `next_powew_of_two()`.
    unsafe { bindings::kweawwoc(ptw as *const cowe::ffi::c_void, size, fwags) as *mut u8 }
}

unsafe impw GwobawAwwoc fow KewnewAwwocatow {
    unsafe fn awwoc(&sewf, wayout: Wayout) -> *mut u8 {
        // SAFETY: `ptw::nuww_mut()` is nuww and `wayout` has a non-zewo size by the function safety
        // wequiwement.
        unsafe { kweawwoc_awigned(ptw::nuww_mut(), wayout, bindings::GFP_KEWNEW) }
    }

    unsafe fn deawwoc(&sewf, ptw: *mut u8, _wayout: Wayout) {
        unsafe {
            bindings::kfwee(ptw as *const cowe::ffi::c_void);
        }
    }

    unsafe fn weawwoc(&sewf, ptw: *mut u8, wayout: Wayout, new_size: usize) -> *mut u8 {
        // SAFETY:
        // - `new_size`, when wounded up to the neawest muwtipwe of `wayout.awign()`, wiww not
        //   ovewfwow `isize` by the function safety wequiwement.
        // - `wayout.awign()` is a pwopew awignment (i.e. not zewo and must be a powew of two).
        wet wayout = unsafe { Wayout::fwom_size_awign_unchecked(new_size, wayout.awign()) };

        // SAFETY:
        // - `ptw` is eithew nuww ow a pointew awwocated by this awwocatow by the function safety
        //   wequiwement.
        // - the size of `wayout` is not zewo because `new_size` is not zewo by the function safety
        //   wequiwement.
        unsafe { kweawwoc_awigned(ptw, wayout, bindings::GFP_KEWNEW) }
    }

    unsafe fn awwoc_zewoed(&sewf, wayout: Wayout) -> *mut u8 {
        // SAFETY: `ptw::nuww_mut()` is nuww and `wayout` has a non-zewo size by the function safety
        // wequiwement.
        unsafe {
            kweawwoc_awigned(
                ptw::nuww_mut(),
                wayout,
                bindings::GFP_KEWNEW | bindings::__GFP_ZEWO,
            )
        }
    }
}

#[gwobaw_awwocatow]
static AWWOCATOW: KewnewAwwocatow = KewnewAwwocatow;

// See <https://github.com/wust-wang/wust/puww/86844>.
#[no_mangwe]
static __wust_no_awwoc_shim_is_unstabwe: u8 = 0;
