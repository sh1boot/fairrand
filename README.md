fairrand
========

An incomplete thought about entropy-conservative minimally-biased NPOT-interval
random number generation.

The theory, here, is to maintain a high-precision fixed-point random number and
to multiply this by the length of the random interval needed, taking the
integer part as the result and retaining the fractional part for further
calculations.

The growing roundoff bias in the fractional part can be tracked, and when it
reaches a threshold everything can be shifted down by a fixed number of bits,
inserting more bits from the RNG in the top end -- effectively dividing the
bias by some power of two.

The problem is that while it seems to work intuitively, by knowing the upper
bound of the error and occasionally shoving it back down below a tolerable
threshold, I haven't found a way to prove that it's reliable and free from
non-obvious artefacts.
