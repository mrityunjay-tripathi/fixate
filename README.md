# Fixate
__Fixate__ is a header-only, ultra-low-latency, and high-performance library, purpose-built for financial messaging in latency-sensitive environments.
Designed to outperform QuickFIX and OnixS, it offers type-safe message construction and parsing with extensive use of template metaprogramming and
(almost) compile-time evaluation for optimal efficiency, making it a robust solution for high-frequency trading and real-time financial systems.
Its single-copy read and parse mechanism ensures least data movement, minimizing cache misses and memory overhead.
The engine supports multiple transport protocols, including TCP, UDP, Secure TCP, and file-based I/O, providing flexibility for integration into
diverse infrastructures. Advanced compile-time tag validation and custom tag extensibility allow for seamless adaptation to proprietary FIX dialects.

## Build and Installation
Configure the build process by executing `configure.sh` script.
```
./configure.sh
```
See various configuration options using:
```
./configure.sh --help
```
After configuration, invoke `make` command to build the test and benchmark suite, and install at the configured location.
```
make
make install
```

## Documentation and Usage
You can build doxygen documentation locally by setting `build_docs` to 1 while configuring.
```
./configure.sh --build_docs=1
```

## Benchmarks
Coming soon...

## License
fixate is free software; you may redistribute it and/or modify it under the
terms of the [BSD 2-Clause "Simplified" License](LICENSE). You should have received a copy of the
BSD 2-Clause "Simplified" License along with fixate. If not, see
http://www.opensource.org/licenses/BSD-2-Clause for more information.


## Contributing
The `dev` branch is the one where all contributions are merged before reaching `main`.
If you plan to propose a pull request, please commit into the `dev` branch, or its own feature branch.
Direct commit to `main` branch is not permitted.
