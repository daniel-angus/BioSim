# BioSim

BioSim is an open-source C library for developing biological simulations.

The project aims to provide a lightweight, modular framework for implementing grid-based models, cellular automata, reaction-diffusion systems, and other computational biology simulations. It is being developed with an emphasis on clean API design, performance, and maintainable code.

> **Status:** Early development 🚧

## Features

Current functionality includes:

- Dynamic grid allocation
- Automatic memory management
- Contiguous (flat-array) grid storage
- Bounds validation
- Documented public API

## Roadmap

Planned features include:

- Grid manipulation utilities
- Multiple biological simulation models
- Example applications
- Unit tests
- Benchmarking
- Build system support (CMake)
- Generated API documentation

## Project Structure

```
BioSim/
├── include/
│   └── grid.h
├── src/
│   └── grid.c
├── main.c
├── .gitignore
├── LICENSE
└── README.md
```

## Building

Compile with GCC:

```bash
gcc -Wall -Wextra -Wpedantic -std=c17 main.c grid.c -o main \
```

Run:

```bash
./main
```

## Contributing

BioSim is currently under active development. Suggestions, bug reports, and contributions are welcome.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.