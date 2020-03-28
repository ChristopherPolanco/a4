/*5. Pack each 2-by-2 block into a 32-bit word as follows:
    • For the PB and PR (chroma) elements of the pixels, take the average
    value of the four pixels in the block (i.e., the DC component). We’ll
    call these average values PB and PR.

    • Convert the PB and PR elements to four-bit values using the function
    we provide you:
        unsigned Arith_index_of_chroma(float x);

    • This function takes a chroma value between −0.5 and +0.5 and returns a
    4-bit quantized representation of the chroma value.
        – Using a discrete cosine transform (DCT), transform the four Y (luminance/luma) values of the pixels into cosine coeffecients a, b, c, and
        d.
        – Convert the b, c, and~d to five-bit signed values assuming that they
        lie between −0.3 and 0.3. Although these values can actually range
        from −0.5 to +0.5, a value outside the range ±0.3 is quite rare. I’m
        willing to throw away information in the rare cases in order to get more precision for the common cases*/