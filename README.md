# Wa-Tor

Sharks and Fish on the Planet
[Wa-Tor](https://en.wikipedia.org/wiki/Wa-Tor). This is an
implementation of a simulation described by A. K. Deweney in his
Computer Recreations column in Scientific American. It's written in C
using SDL.

The program simulates a toroidal world covered in water and populated
with Sharks and Fish. Fish periodically spawn to build their
population and the sharks eat the fish, depending on fish as a food
source to survive and reproduce.

With the right tuning parameters, the simulated world can enter an
oscillation similar to those described in the [Lotka-Volterra
equations](https://en.wikipedia.org/wiki/Lotka–Volterra_equations).
The fish population will rise, allowing the sharks to feed and grow in
number. The Sharks will spawn to the point they overwhelm their food
supply, starving themselves, and experiencing a population collapse
that lets the fish population recover and the cycle repeat.

The current simulation parameters produce a world that goes through a
number of these cycles. Dewdney's original article talks about it
being difficult to find a parameters that lead to such a stable
equilibrium, but I didn't not have problems finding these, and there
seem to be a fairly wide range of values that work. I suspect the
difference is because modern computer hardware allows much larger
simulations in which it's more difficult for a population to go
totally to zero.

## License

Copyright © 2023 East Coast Toolworks, LLC

Distributed under the Eclipse Public License either version 1.0 or (at
your option) any later version.
