require "mkmf"
require "rbconfig"

compact_enc_det_path = File.expand_path("../compact_enc_det/compact_enc_det", __dir__)

compact_enc_det_build_command = "cd #{compact_enc_det_path} &&"
compact_enc_det_build_command += " CXXFLAGS=\"-fPIC\""
compact_enc_det_build_command += " ./autogen.sh"

unless system(compact_enc_det_build_command)
  raise "Failed to build the compact_enc_det library"
end

$INCFLAGS << " -I$(srcdir)/compact_enc_det"
$LDFLAGS << " -L$(srcdir)/compact_enc_det/lib -lced"

create_makefile("compact_enc_det/compact_enc_det")
