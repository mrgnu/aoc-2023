#include "day_9.hh"

#include <numeric>
#include <ranges>

using namespace std;
using namespace utils;

namespace {

using namespace day_9;

timeline_t parse_line(const line_t& line) {
  const parts_t parts = split_string(line, regex("[[:blank:]]+"));
  auto nums = parts | views::transform([](const part_t& part) -> long {
                return stol(part);
              });
  return timeline_t(nums.begin(), nums.end());
}

bool all_zero(const timeline_t& timeline) {
  auto f = timeline | views::filter([](const value_t& v) { return v != 0; });
  return f.empty();
}

using prediction_stack_t = vector<timeline_t>;

prediction_stack_t build_prediction_stack(const timeline_t& timeline) {
  vector<timeline_t> predictions;
  predictions.reserve(timeline.size());
  predictions.push_back(timeline);

  while (!all_zero(predictions.back())) {
    const timeline_t& prev = predictions.back();
    timeline_t prediction;
    prediction.reserve(prev.size() - 1);
    for (timeline_t::size_type i = 0; i < prev.size() - 1; ++i) {
      const value_t delta = prev[i + 1] - prev[i];
      prediction.push_back(delta);
    }
    predictions.push_back(prediction);
  }

  return predictions;
}

value_t predict(const timeline_t& timeline) {
  vector<timeline_t> predictions = build_prediction_stack(timeline);

  value_t last_val = 0;
  for (int i = predictions.size() - 1; i >= 0; --i) {
    timeline_t& prediction = predictions[i];
    prediction.push_back(prediction.back() + last_val);
    last_val = prediction.back();
  }

  return predictions.front().back();
}

}  // namespace

namespace day_9 {

input_t parse_input(const lines_t& lines) {
  auto timelines = lines | views::transform(parse_line);
  return input_t(timelines.begin(), timelines.end());
}

value_t predict(const timeline_t& timeline) { return ::predict(timeline); }

result_t part_1(const lines_t& lines) {
  const input_t input = parse_input(lines);
  auto ps = input | views::transform(predict);
  return accumulate(ps.begin(), ps.end(), 0);
}

}  // namespace day_9
