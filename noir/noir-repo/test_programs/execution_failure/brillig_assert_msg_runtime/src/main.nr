fn main(x: Field) {
    // Safety: testing context
    assert(1 == unsafe { conditional(x) });
}

unconstrained fn conditional(x: Field) -> Field {
    let z = x as u8 + 20;
    assert_eq(z, 25, f"Expected 25 but got {z}");
    assert(x == 10, f"Expected x to equal 10, but got {x}");
    1
}
