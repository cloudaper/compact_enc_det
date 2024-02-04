require "mkmf"

unless system("cd compact_enc_det && ./autogen.sh")
  raise "Failed to build the compact_enc_det library"
end

$INCFLAGS << " -I$(srcdir)/compact_enc_det"
$LDFLAGS << " -L$(srcdir)/compact_enc_det/lib -lced"

create_makefile("compact_enc_det/compact_enc_det")
