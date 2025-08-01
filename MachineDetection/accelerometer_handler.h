/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef TENSORFLOW_LITE_MICRO_EXAMPLES_MAGIC_WAND_ACCELEROMETER_HANDLER_H_
#define TENSORFLOW_LITE_MICRO_EXAMPLES_MAGIC_WAND_ACCELEROMETER_HANDLER_H_

#define kChannelNumber 3

#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"


#include <string.h>

#define EXECUTION_TIME 0

#if EXECUTION_TIME
#include "tensorflow/lite/micro/micro_time.h"
#include <climits>

#define TF_LITE_MICRO_EXECUTION_TIME_BEGIN                                             \
  int32_t start_ticks;                                                                 \
  int32_t duration_ticks;                                                              \
  int32_t duration_ms;

#define TF_LITE_MICRO_EXECUTION_TIME(reporter, func)                                   \
  if (tflite::ticks_per_second() == 0) {                                               \
    TF_LITE_REPORT_ERROR(reporter, "no timer implementation found");                   \
  }                                                                                    \
  start_ticks = tflite::GetCurrentTimeTicks();                                         \
  func;                                                                                \
  duration_ticks = tflite::GetCurrentTimeTicks() - start_ticks;                        \
  if (duration_ticks > INT_MAX / 1000) {                                               \
    duration_ms = duration_ticks / (tflite::ticks_per_second() / 1000);                \
  }                                                                                    \
  else {                                                                               \
    duration_ms = (duration_ticks * 1000) / tflite::ticks_per_second();                \
  }                                                                                    \
  TF_LITE_REPORT_ERROR(reporter, "%s took %d ticks (%d ms)", #func, duration_ticks,    \
                       duration_ms);

#define TF_LITE_MICRO_EXECUTION_TIME_SNIPPET_START(reporter)                           \
  if (tflite::ticks_per_second() == 0) {                                               \
    TF_LITE_REPORT_ERROR(reporter, "no timer implementation found");                   \
  }                                                                                    \
  start_ticks = tflite::GetCurrentTimeTicks();

#define TF_LITE_MICRO_EXECUTION_TIME_SNIPPET_END(reporter, desc)                       \
  duration_ticks = tflite::GetCurrentTimeTicks() - start_ticks;                        \
  if (duration_ticks > INT_MAX / 1000) {                                               \
    duration_ms = duration_ticks / (tflite::ticks_per_second() / 1000);                \
  }                                                                                    \
  else {                                                                               \
    duration_ms = (duration_ticks * 1000) / tflite::ticks_per_second();                \
  }                                                                                    \
  TF_LITE_REPORT_ERROR(reporter, "%s took %d ticks (%d ms)", desc, duration_ticks,     \
                       duration_ms);
#endif

extern int begin_index;
extern TfLiteStatus SetupAccelerometer(tflite::ErrorReporter* error_reporter);
extern bool ReadAccelerometer(tflite::ErrorReporter* error_reporter,
                              float *input, int length);

#endif  // TENSORFLOW_LITE_MICRO_EXAMPLES_MAGIC_WAND_ACCELEROMETER_HANDLER_H_
