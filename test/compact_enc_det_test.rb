require "minitest/autorun"
require_relative "../lib/compact_enc_det"

class CompactEncDetTest < Minitest::Test
  def test_detect_encoding_known_english
    text = File.read("test/fixtures/utf-8.txt")
    result = CompactEncDet.detect_encoding(text, text.bytesize)
    encoding_detected = result[0]
    bytes_consumed = result[1]
    is_reliable = result[2]

    assert_equal 22, encoding_detected
    assert_operator 0, :<, bytes_consumed
    assert_equal true, is_reliable
  end
end
