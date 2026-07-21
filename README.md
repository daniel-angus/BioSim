# BioSim

BioSim is an open-source C library for developing biological simulations.

The project aims to provide a lightweight, modular framework for implementing grid-based models, cellular automata, reaction-diffusion systems, and other computational biology simulations. It is being developed with an emphasis on clean API design, performance, and maintainable code.

> **Status:** Early development 🚧

## Features

Current functionality includes:

- Full Generalised 2D Cellular Automata
- Documented public API

## Roadmap

Planned features include:

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
│   ├── grid.h
│   ├── liferule.h
│   └── renderer.h
├── src/
│   ├── grid.c
│   ├── liferule.c
│   └── renderer.c
├── main.c
├── Makefile
├── .gitignore
├── LICENSE
└── README.md
```

## Building

BioSim uses a Makefile for building.

Compile the project:

```bash
make
```

The executable will be placed in the `bin/` directory.

Run the program:

```bash
./bin/biosim
```

To remove build artefacts:

```bash
make clean
```

## Contributing

BioSim is currently under active development. Suggestions, bug reports, and contributions are welcome.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.