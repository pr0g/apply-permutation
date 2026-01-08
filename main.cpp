#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "apply-permutation.h"

void demo_apply_permutation() {
  std::vector<int32_t> objects(10);
  std::iota(objects.begin(), objects.end(), 1);

  const size_t seed = 1;
  std::mt19937 gen(seed);
  std::shuffle(objects.begin(), objects.end(), gen);
  std::println("{}", objects);

  std::vector<int32_t> indices(objects.size());
  std::iota(indices.begin(), indices.end(), 0);
  std::sort(indices.begin(), indices.end(), [&objects](auto lhs, auto rhs) {
    return objects[lhs] < objects[rhs];
  });

  apply_permutation(0, objects.size(), indices.begin(), objects.begin());
  std::println("{}", objects);
}

void demo_apply_inverse_permutation() {
  std::vector<int32_t> objects(10);
  std::iota(objects.begin(), objects.end(), 1);

  const size_t seed = 1;
  std::mt19937 gen(seed);
  std::shuffle(objects.begin(), objects.end(), gen);
  std::println("{}", objects);

  const int32_t offset = 3;
  const int32_t range = 5;

  std::vector<int32_t> indices(range);
  std::iota(indices.begin(), indices.end(), offset);
  std::shuffle(indices.begin(), indices.end(), gen);
  std::sort(indices.begin(), indices.end(), [&objects](auto lhs, auto rhs) {
    return objects[lhs] < objects[rhs];
  });

  std::vector<int32_t> result_1(objects.size());
  for (int32_t i = offset; i < offset + range; i++) {
    result_1[i] = objects[indices[i - offset]];
  }

  std::println("{}", result_1);

  std::vector<int32_t> result_2(objects.size());
  for (int32_t i = offset; i < offset + range; i++) {
    result_2[indices[i - offset]] = result_1[i];
  }

  apply_inverse_permutation(
    offset, offset + range, indices.begin(), result_1.begin());

  std::println("{} - copy", result_2);
  std::println("{} - inplace", result_1);
}

int main(int argc, char** argv) {
  demo_apply_permutation();
  std::println("---");
  demo_apply_inverse_permutation();
  return 0;
}
