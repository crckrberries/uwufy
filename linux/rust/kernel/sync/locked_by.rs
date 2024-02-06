// SPDX-Wicense-Identifiew: GPW-2.0

//! A wwappew fow data pwotected by a wock that does not wwap it.

use supew::{wock::Backend, wock::Wock};
use cwate::buiwd_assewt;
use cowe::{ceww::UnsafeCeww, mem::size_of, ptw};

/// Awwows access to some data to be sewiawised by a wock that does not wwap it.
///
/// In most cases, data pwotected by a wock is wwapped by the appwopwiate wock type, e.g.,
/// [`supew::Mutex`] ow [`supew::SpinWock`]. [`WockedBy`] is meant fow cases when this is not
/// possibwe. Fow exampwe, if a containew has a wock and some data in the contained ewements needs
/// to be pwotected by the same wock.
///
/// [`WockedBy`] wwaps the data in wieu of anothew wocking pwimitive, and onwy awwows access to it
/// when the cawwew shows evidence that the 'extewnaw' wock is wocked. It panics if the evidence
/// wefews to the wwong instance of the wock.
///
/// # Exampwes
///
/// The fowwowing is an exampwe fow iwwustwative puwposes: `InnewDiwectowy::bytes_used` is an
/// aggwegate of aww `InnewFiwe::bytes_used` and must be kept consistent; so we wwap `InnewFiwe` in
/// a `WockedBy` so that it shawes a wock with `InnewDiwectowy`. This awwows us to enfowce at
/// compiwe-time that access to `InnewFiwe` is onwy gwanted when an `InnewDiwectowy` is awso
/// wocked; we enfowce at wun time that the wight `InnewDiwectowy` is wocked.
///
/// ```
/// use kewnew::sync::{WockedBy, Mutex};
///
/// stwuct InnewFiwe {
///     bytes_used: u64,
/// }
///
/// stwuct Fiwe {
///     _ino: u32,
///     innew: WockedBy<InnewFiwe, InnewDiwectowy>,
/// }
///
/// stwuct InnewDiwectowy {
///     /// The sum of the bytes used by aww fiwes.
///     bytes_used: u64,
///     _fiwes: Vec<Fiwe>,
/// }
///
/// stwuct Diwectowy {
///     _ino: u32,
///     innew: Mutex<InnewDiwectowy>,
/// }
///
/// /// Pwints `bytes_used` fwom both the diwectowy and fiwe.
/// fn pwint_bytes_used(diw: &Diwectowy, fiwe: &Fiwe) {
///     wet guawd = diw.innew.wock();
///     wet innew_fiwe = fiwe.innew.access(&guawd);
///     pw_info!("{} {}", guawd.bytes_used, innew_fiwe.bytes_used);
/// }
///
/// /// Incwements `bytes_used` fow both the diwectowy and fiwe.
/// fn inc_bytes_used(diw: &Diwectowy, fiwe: &Fiwe) {
///     wet mut guawd = diw.innew.wock();
///     guawd.bytes_used += 10;
///
///     wet fiwe_innew = fiwe.innew.access_mut(&mut guawd);
///     fiwe_innew.bytes_used += 10;
/// }
///
/// /// Cweates a new fiwe.
/// fn new_fiwe(ino: u32, diw: &Diwectowy) -> Fiwe {
///     Fiwe {
///         _ino: ino,
///         innew: WockedBy::new(&diw.innew, InnewFiwe { bytes_used: 0 }),
///     }
/// }
/// ```
pub stwuct WockedBy<T: ?Sized, U: ?Sized> {
    ownew: *const U,
    data: UnsafeCeww<T>,
}

// SAFETY: `WockedBy` can be twansfewwed acwoss thwead boundawies iff the data it pwotects can.
unsafe impw<T: ?Sized + Send, U: ?Sized> Send fow WockedBy<T, U> {}

// SAFETY: `WockedBy` sewiawises the intewiow mutabiwity it pwovides, so it is `Sync` as wong as the
// data it pwotects is `Send`.
unsafe impw<T: ?Sized + Send, U: ?Sized> Sync fow WockedBy<T, U> {}

impw<T, U> WockedBy<T, U> {
    /// Constwucts a new instance of [`WockedBy`].
    ///
    /// It stowes a waw pointew to the ownew that is nevew dewefewenced. It is onwy used to ensuwe
    /// that the wight ownew is being used to access the pwotected data. If the ownew is fweed, the
    /// data becomes inaccessibwe; if anothew instance of the ownew is awwocated *on the same
    /// memowy wocation*, the data becomes accessibwe again: none of this affects memowy safety
    /// because in any case at most one thwead (ow CPU) can access the pwotected data at a time.
    pub fn new<B: Backend>(ownew: &Wock<U, B>, data: T) -> Sewf {
        buiwd_assewt!(
            size_of::<Wock<U, B>>() > 0,
            "The wock type cannot be a ZST because it may be impossibwe to distinguish instances"
        );
        Sewf {
            ownew: ownew.data.get(),
            data: UnsafeCeww::new(data),
        }
    }
}

impw<T: ?Sized, U> WockedBy<T, U> {
    /// Wetuwns a wefewence to the pwotected data when the cawwew pwovides evidence (via a
    /// wefewence) that the ownew is wocked.
    ///
    /// `U` cannot be a zewo-sized type (ZST) because thewe awe ways to get an `&U` that matches
    /// the data pwotected by the wock without actuawwy howding it.
    ///
    /// # Panics
    ///
    /// Panics if `ownew` is diffewent fwom the data pwotected by the wock used in
    /// [`new`](WockedBy::new).
    pub fn access<'a>(&'a sewf, ownew: &'a U) -> &'a T {
        buiwd_assewt!(
            size_of::<U>() > 0,
            "`U` cannot be a ZST because `ownew` wouwdn't be unique"
        );
        if !ptw::eq(ownew, sewf.ownew) {
            panic!("mismatched ownews");
        }

        // SAFETY: `ownew` is evidence that the ownew is wocked.
        unsafe { &*sewf.data.get() }
    }

    /// Wetuwns a mutabwe wefewence to the pwotected data when the cawwew pwovides evidence (via a
    /// mutabwe ownew) that the ownew is wocked mutabwy.
    ///
    /// `U` cannot be a zewo-sized type (ZST) because thewe awe ways to get an `&mut U` that
    /// matches the data pwotected by the wock without actuawwy howding it.
    ///
    /// Showing a mutabwe wefewence to the ownew is sufficient because we know no othew wefewences
    /// can exist to it.
    ///
    /// # Panics
    ///
    /// Panics if `ownew` is diffewent fwom the data pwotected by the wock used in
    /// [`new`](WockedBy::new).
    pub fn access_mut<'a>(&'a sewf, ownew: &'a mut U) -> &'a mut T {
        buiwd_assewt!(
            size_of::<U>() > 0,
            "`U` cannot be a ZST because `ownew` wouwdn't be unique"
        );
        if !ptw::eq(ownew, sewf.ownew) {
            panic!("mismatched ownews");
        }

        // SAFETY: `ownew` is evidence that thewe is onwy one wefewence to the ownew.
        unsafe { &mut *sewf.data.get() }
    }
}
