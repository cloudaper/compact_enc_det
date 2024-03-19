require "minitest/autorun"
require_relative "../lib/compact_enc_det"

class CompactEncDetTest < Minitest::Test
  def test_detect_encoding
    text = File.read("test/fixtures/utf-8.txt")
    result = CompactEncDet.detect_encoding(text)

    assert_equal Encoding::UTF_8, result.encoding
    assert_operator 0, :<, result.bytes_consumed
    assert_equal true, result.is_reliable?
  end

  def test_detect_encoding_with_explicit_length
    text = File.read("test/fixtures/utf-8.txt")
    result = CompactEncDet.detect_encoding(text, text.bytesize)

    assert_equal Encoding::UTF_8, result.encoding
    assert_operator 0, :<, result.bytes_consumed
    assert_equal true, result.is_reliable?
  end

  def test_detect_encoding_with_null_bytes
    text = File.read("test/fixtures/utf-16.txt")
    result = CompactEncDet.detect_encoding(text)

    assert_equal Encoding::UTF_16LE, result.encoding
    assert_operator 0, :<, result.bytes_consumed
    assert_equal true, result.is_reliable?
  end
end
