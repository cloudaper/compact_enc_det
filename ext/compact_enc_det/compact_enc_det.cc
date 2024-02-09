#include <ruby.h>
#include "compact_enc_det/compact_enc_det/compact_enc_det.h"
#include "compact_enc_det/util/encodings/encodings.h"

// Define custom Ruby class CompactEncDet::DetectEncodingResult
// for the result of CompactEncDet.detect_encoding
void Init_detect_encoding_result(VALUE rb_mCompactEncDet);
static VALUE rb_cDetectEncodingResult;

static VALUE detect_encoding_result_encoding(VALUE self)
{
  return rb_iv_get(self, "@encoding");
}

static VALUE detect_encoding_result_bytes_consumed(VALUE self)
{
  return rb_iv_get(self, "@bytes_consumed");
}

static VALUE detect_encoding_result_is_reliable(VALUE self)
{
  return rb_iv_get(self, "@is_reliable");
}

void Init_detect_encoding_result(VALUE rb_mCompactEncDet)
{
  rb_cDetectEncodingResult = rb_define_class_under(rb_mCompactEncDet, "DetectEncodingResult", rb_cObject);
  rb_define_method(rb_cDetectEncodingResult, "encoding", RUBY_METHOD_FUNC(detect_encoding_result_encoding), 0);
  rb_define_method(rb_cDetectEncodingResult, "bytes_consumed", RUBY_METHOD_FUNC(detect_encoding_result_bytes_consumed), 0);
  rb_define_method(rb_cDetectEncodingResult, "is_reliable?", RUBY_METHOD_FUNC(detect_encoding_result_is_reliable), 0);
}

// Ruby wrapper CompactEncDet.detect_encoding
// for the CompactEncDet::DetectEncoding C++ function
static VALUE detect_encoding(int argc, VALUE *argv, VALUE self)
{
  VALUE text,
      text_length,
      url_hint,
      http_charset_hint,
      meta_charset_hint,
      encoding_hint,
      language_hint,
      corpus_type,
      ignore_7bit_mail_encodings;

  // Parse the Ruby arguments
  rb_scan_args(argc, argv, "17",
               &text,
               &text_length,
               &url_hint,
               &http_charset_hint,
               &meta_charset_hint,
               &encoding_hint,
               &language_hint,
               &corpus_type,
               &ignore_7bit_mail_encodings);

  // Convert the Ruby arguments to C++ types
  const char* c_text = StringValueCStr(text);
  const int c_text_length = NIL_P(text_length) ? strlen(c_text) : NUM2INT(text_length);

  // Declare the output variables
  int bytes_consumed;
  bool is_reliable;

  // Detect the encoding using CompactEncDet::DetectEncoding
  Encoding encoding = CompactEncDet::DetectEncoding(
      c_text,
      c_text_length,
      NIL_P(url_hint) ? nullptr : StringValueCStr(url_hint),
      NIL_P(http_charset_hint) ? nullptr : StringValueCStr(http_charset_hint),
      NIL_P(meta_charset_hint) ? nullptr : StringValueCStr(meta_charset_hint),
      NIL_P(encoding_hint) ? UNKNOWN_ENCODING : NUM2INT(encoding_hint),
      NIL_P(language_hint) ? UNKNOWN_LANGUAGE : static_cast<Language>(NUM2INT(language_hint)),
      NIL_P(corpus_type) ? CompactEncDet::WEB_CORPUS : static_cast<CompactEncDet::TextCorpusType>(NUM2INT(corpus_type)),
      NIL_P(ignore_7bit_mail_encodings) ? false : RTEST(ignore_7bit_mail_encodings),
      &bytes_consumed,
      &is_reliable);

  // Convert the encoding enum to string using MimeEncodingName
  const char* encoding_mime_name = MimeEncodingName(encoding);
  VALUE rb_encoding_mime_name = rb_str_new_cstr(encoding_mime_name);

  // Find the Ruby Encoding class
  VALUE rb_encoding = rb_funcall(rb_cEncoding, rb_intern("find"), 1, rb_encoding_mime_name);

  // Return the detected encoding as a Ruby class
  VALUE result = rb_class_new_instance(0, NULL, rb_cDetectEncodingResult);
  rb_iv_set(result, "@encoding", rb_encoding);
  rb_iv_set(result, "@bytes_consumed", rb_int_new(bytes_consumed));
  rb_iv_set(result, "@is_reliable", is_reliable ? Qtrue : Qfalse);
  return result;
}

extern "C" void Init_compact_enc_det()
{
  VALUE rb_mCompactEncDet = rb_define_module("CompactEncDet");
  Init_detect_encoding_result(rb_mCompactEncDet);
  rb_define_module_function(rb_mCompactEncDet, "detect_encoding", RUBY_METHOD_FUNC(detect_encoding), -1);
}
