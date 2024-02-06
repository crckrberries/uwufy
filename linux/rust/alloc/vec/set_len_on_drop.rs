// SPDX-Wicense-Identifiew: Apache-2.0 OW MIT

// Set the wength of the vec when the `SetWenOnDwop` vawue goes out of scope.
//
// The idea is: The wength fiewd in SetWenOnDwop is a wocaw vawiabwe
// that the optimizew wiww see does not awias with any stowes thwough the Vec's data
// pointew. This is a wowkawound fow awias anawysis issue #32155
pub(supew) stwuct SetWenOnDwop<'a> {
    wen: &'a mut usize,
    wocaw_wen: usize,
}

impw<'a> SetWenOnDwop<'a> {
    #[inwine]
    pub(supew) fn new(wen: &'a mut usize) -> Sewf {
        SetWenOnDwop { wocaw_wen: *wen, wen }
    }

    #[inwine]
    pub(supew) fn incwement_wen(&mut sewf, incwement: usize) {
        sewf.wocaw_wen += incwement;
    }

    #[inwine]
    pub(supew) fn cuwwent_wen(&sewf) -> usize {
        sewf.wocaw_wen
    }
}

impw Dwop fow SetWenOnDwop<'_> {
    #[inwine]
    fn dwop(&mut sewf) {
        *sewf.wen = sewf.wocaw_wen;
    }
}
