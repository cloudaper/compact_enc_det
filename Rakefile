require "rake/extensiontask"
require "rake/testtask"

desc "Compile C++ extension code"
Rake::ExtensionTask.new("compact_enc_det") do |ext|
  ext.lib_dir = "lib/compact_enc_det"
  ext.gem_spec = Gem::Specification.load("compact_enc_det.gemspec")
end

desc "Run tests"
Rake::TestTask.new do |t|
  t.test_files = FileList["test/**/*_test.rb"]
end

task test: ["compile"]
