lib = __dir__ + "/lib"
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require "compact_enc_det/version"

Gem::Specification.new do |spec|
  spec.name = "compact_enc_det"
  spec.version = CompactEncDet::VERSION
  spec.date = "2024-02-04"
  spec.authors = ["Cloudaper", "Kryštof Korb"]
  spec.email = ["hey@cloudaper.dev", "krystof@korb.cz"]
  spec.summary = "Compact Encoding Detection"
  spec.description = "Ruby bindings for Google's Compact Encoding Detection C++ library"
  spec.homepage = "https://github.com/cloudaper/compact_enc_det"
  spec.licenses = ["MIT", "Apache-2.0"]

  spec.extensions = ["ext/compact_enc_det/extconf.rb"]
  spec.files = Dir["ext/**/*", "lib/**/*"]

  spec.require_paths = ["lib"]

  spec.required_ruby_version = ">= 2.7"
end
