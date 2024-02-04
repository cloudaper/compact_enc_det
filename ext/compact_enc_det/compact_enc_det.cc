#include <ruby.h>
#include "compact_enc_det/compact_enc_det/compact_enc_det.h"

// CompactEncDet::DetectEncoding wrapper for Ruby
static VALUE detect_encoding(int argc, VALUE *argv, VALUE self)
{
  VALUE ruby_text,
      ruby_text_length,
      url_hint,
      http_charset_hint,
      meta_charset_hint,
      encoding_hint,
      language_hint,
      corpus_type,
      ignore_7bit_mail_encodings;

  // Parse the Ruby arguments
  rb_scan_args(argc, argv, "27",
               &ruby_text,
               &ruby_text_length,
               &url_hint,
               &http_charset_hint,
               &meta_charset_hint,
               &encoding_hint,
               &language_hint,
               &corpus_type,
               &ignore_7bit_mail_encodings);

  // Convert the Ruby values to C types
  const char *text = StringValueCStr(ruby_text);
  const int text_length = NUM2INT(ruby_text_length);

  // Declare the output variables
  int bytes_consumed;
  bool is_reliable;

  // Detect the encoding using CompactEncDet::DetectEncoding
  Encoding encoding = CompactEncDet::DetectEncoding(
      text, text_length,
      NIL_P(url_hint) ? nullptr : StringValueCStr(url_hint),
      NIL_P(http_charset_hint) ? nullptr : StringValueCStr(http_charset_hint),
      NIL_P(meta_charset_hint) ? nullptr : StringValueCStr(meta_charset_hint),
      NIL_P(encoding_hint) ? UNKNOWN_ENCODING : NUM2INT(encoding_hint),
      NIL_P(language_hint) ? UNKNOWN_LANGUAGE : static_cast<Language>(NUM2INT(language_hint)),
      NIL_P(corpus_type) ? CompactEncDet::WEB_CORPUS : static_cast<CompactEncDet::TextCorpusType>(NUM2INT(corpus_type)),
      NIL_P(ignore_7bit_mail_encodings) ? false : RTEST(ignore_7bit_mail_encodings),
      &bytes_consumed,
      &is_reliable);

  // Return the encoding enum integer, bytes consumed integer
  // and is reliable boolean in an array
  VALUE result = rb_ary_new();
  rb_ary_push(result, rb_int_new(encoding));
  rb_ary_push(result, rb_int_new(bytes_consumed));
  rb_ary_push(result, is_reliable ? Qtrue : Qfalse);
  return result;
}

extern "C" void Init_compact_enc_det()
{
  VALUE module = rb_define_module("CompactEncDet");
  rb_define_module_function(module, "detect_encoding", RUBY_METHOD_FUNC(detect_encoding), -1);
}
