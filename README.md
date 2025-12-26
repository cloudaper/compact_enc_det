# Compact Encoding Detection for Ruby

Ruby bindings for [Google's Compact Encoding Detection](https://github.com/google/compact_enc_det) (CED for short) C++ library

> [!NOTE]
> Bindings temporarily use a [fork of the C++ library](https://github.com/cloudaper/compact_enc_det_fork/commit/e4eda3204bab019564b96c522baae93ee2fffdc8), which fixes the minimum CMake version for the build to pass on modern environments.

## Usage

You will need [curl](https://curl.se) and [CMake](https://cmake.org) to build the C++ native extension.

>  macOS
> 
> You can use [Homebrew](https://brew.sh) to install it:
> 
> ```console
> brew install cmake
> ```

Then you can install the gem from [RubyGems.org](https://rubygems.org/gems/compact_enc_det).

> Either add this to your Gemfile:
>
> ```ruby
> gem 'compact_enc_det', '~> 1.0'
> ```
> or run the following command to install it:
>
> ```console
> gem install compact_enc_det
> ```

Now you can detect the encoding via the `CompactEncDet.detect_encoding`, which is a thin wrapper around `CompactEncDet::DetectEncoding` and `MimeEncodingName` functions from the C++ library.

> ```ruby
> file = File.read("unknown-encoding.txt", mode: "rb")
> result = CompactEncDet.detect_encoding(file)
> result.encoding
> # => #<Encoding:Windows-1250>
> result.bytes_consumed
> # => 239
> result.is_reliable?
> # => true
> ```

## Contributing

Any contributions are welcome! Feel free to open an issue or a pull request.

### Repository

The [google/compact_enc_det](https://github.com/google/compact_enc_det) repository is linked as a Git submodule at `ext/compact_enc_det/compact_enc_det`.

> You need to clone the repository with `--recurse-submodules` flag:
> 
> ```console
> git clone --recurse-submodules git@github.com:cloudaper/compact_enc_det.git
> ```
> 
> Or initialize and update the submodule after cloning with the following commands:
> 
> ```console
> git submodule init && git submodule update
> ```

### Testing

Tests located at `tests` use the [minitest](https://github.com/minitest/minitest) framework.

> Run the tests via test Rake task:
> 
> ```console
> rake test
> ```
> 
> The gem will be compiled to `lib/compact_enc_det/compact_enc_det.bundle` first.

## License

This gem is released under [MIT license](LICENSE), while the original Google's [Compact Encoding Detection library](https://github.com/google/compact_enc_det) source code, located at `ext/compact_enc_det/compact_enc_det`, is under the [Apache-2.0](LICENSE-APACHE) license.
