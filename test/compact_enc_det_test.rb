require "minitest/autorun"
require_relative "../lib/compact_enc_det"

class CompactEncDetTest < Minitest::Test
  def test_detect_encoding_known_english
    text = File.read("test/fixtures/utf-8.txt")
    result = CompactEncDet.detect_encoding(text, text.bytesize)

    assert_equal Encoding::UTF_8, result.encoding
    assert_operator 0, :<, result.bytes_consumed
    assert_equal true, result.is_reliable?
  end
end
